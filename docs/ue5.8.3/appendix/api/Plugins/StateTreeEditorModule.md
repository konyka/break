# Plugins / StateTreeEditorModule

- module root: `Plugins/Runtime/StateTree/Source/StateTreeEditorModule`
- headers: 97; symbols: 2821
- symbol kinds: class=100, delegate=24, enum=19, enumerator=86, externvar=4, function=271, macro=30, member=725, namespace=159, prototype=1332, struct=62, typedef=9
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, AssetDefinition, DetailCustomizations, DeveloperSettings, EditorInteractiveToolsFramework, EditorWidgets, GameplayInsights, GraphEditor, InteractiveToolsFramework, Kismet, KismetCompiler, KismetWidgets, PropertyPath, RenderCore, RewindDebuggerInterface, SourceCodeAccess, ToolMenus, ToolWidgets, TraceLog, TraceServices
- PrivateIncludePathModuleNames: MessageLog
- PublicDependencyModuleNames: AssetTools, BlueprintGraph, Core, CoreUObject, EditorFramework, EditorStyle, EditorSubsystem, Engine, GameplayTags, InputCore, Projects, PropertyAccessEditor, PropertyBindingUtils, PropertyBindingUtilsEditor, PropertyEditor, Slate, SlateCore, SourceControl, StateTreeDeveloper, StateTreeModule, StructUtilsEditor, UnrealEd

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/AssetDefinition_StateTree.h` (Private)


#### class `UAssetDefinition_StateTree`  
`class UAssetDefinition_StateTree : public UAssetDefinitionDefault`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _protected prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _protected prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _protected prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/AsyncStateTreeDiff.h` (Private)


#### class `UE::StateTree::Diff::FAsyncDiff`  
`class FAsyncDiff : public TAsyncTreeDifferences<TWeakObjectPtr<UStateTreeState>>`  
_L15-29_
- inherits: `TAsyncTreeDifferences<TWeakObjectPtr<UStateTreeState>>`
- L18 _public prototype_ `FAsyncDiff(const TSharedRef<SStateTreeView>& LeftTree, const TSharedRef<SStateTreeView>& RightTree);`
- L20 _public prototype_ `void GetStateTreeDifferences(TArray<FSingleDiffEntry>& OutDiffEntries) const;`
- L23 _private prototype_ `void GetStatesDifferences(TArray<FSingleDiffEntry>& OutDiffEntries) const;`
- L25 _private prototype_ `static TAttribute<TArray<TWeakObjectPtr<UStateTreeState>>> RootNodesAttribute(TWeakPtr<SStateTreeView> StateTreeView);`
- L27 _private member_ `TSharedPtr<SStateTreeView> LeftView;`
- L28 _private member_ `TSharedPtr<SStateTreeView> RightView;`

#### class `TTreeDiffSpecification`  
`template <> class TTreeDiffSpecification<TWeakObjectPtr<UStateTreeState>>`  
_L34-52_
- L37 _public prototype_ `bool AreValuesEqual(const TWeakObjectPtr<UStateTreeState>& StateTreeNodeA, const TWeakObjectPtr<UStateTreeState>& StateTreeNodeB, TArray<FPropertySoftPath>* OutDifferingProperties = nullptr) const;`
- L39 _public prototype_ `bool AreMatching(const TWeakObjectPtr<UStateTreeState>& StateTreeNodeA, const TWeakObjectPtr<UStateTreeState>& StateTreeNodeB, TArray<FPropertySoftPath>* OutDifferingProperties = nullptr) const;`
- L41 _public prototype_ `void GetChildren(const TWeakObjectPtr<UStateTreeState>& InParent, TArray<TWeakObjectPtr<UStateTreeState>>& OutChildren) const;`
- L43 _public function_ `bool ShouldMatchByValue(const TWeakObjectPtr<UStateTreeState>&) const`
- L48 _public function_ `bool ShouldInheritEqualFromChildren(const TWeakObjectPtr<UStateTreeState>&, const TWeakObjectPtr<UStateTreeState>&) const`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace StateTree` (scope `UE`)
- L11 _namespace_ `namespace Diff` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Commandlets/StateTreeCompileAllCommandlet.h` (Private)


#### class `UStateTreeCompileAllCommandlet`  
`class UStateTreeCompileAllCommandlet : public UCommandlet`  
_L16-30_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Commandlet to recompile all StateTree assets in the project
- L20 _public prototype_ `UStateTreeCompileAllCommandlet(const FObjectInitializer& ObjectInitializer);`
- L23 _public prototype_ `virtual int32 Main(const FString& Params) override;`
- L27 _protected prototype_ `bool CompileAndSaveStateTree(TNonNullPtr<UStateTree> StateTree) const;`
- L29 _protected member_ `ISourceControlProvider* SourceControlProvider = nullptr;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeAnyEnumDetails.h` (Private)


#### class `FStateTreeAnyEnumDetails`  
`class FStateTreeAnyEnumDetails : public IPropertyTypeCustomization`  
_L15-35_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L25 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _private prototype_ `FText GetDescription() const;`
- L28 _private prototype_ `TSharedRef<SWidget> OnGetComboContent() const;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> ValueProperty;`
- L31 _private member_ `TSharedPtr<IPropertyHandle> EnumProperty;`
- L33 _private member_ `class IPropertyUtilities* PropUtils;`
- L34 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeBindingExtension.h` (Private)


#### class `FStateTreeBindingExtension`  
`class FStateTreeBindingExtension : public FPropertyBindingExtension`  
_L23-37_
- inherits: `FPropertyBindingExtension`
- L26 _private prototype_ `virtual TSharedPtr<UE::PropertyBinding::FCachedBindingData> CreateCachedBindingData(IPropertyBindingBindingCollectionOwner* InBindingsOwner, const FPropertyBindingPath& InTargetPath, const TSharedPtr<IPropertyHandle>& InPropertyHandle, TConstArrayView<TInstancedStruct<FPropertyBindingBindableStructDescriptor>> InAccessibleStructs) const override;`
- L27 _private prototype_ `virtual bool CanBindToProperty(const FPropertyBindingPath& InTargetPath, const IPropertyHandle& InPropertyHandle) const override;`
- L28 _private prototype_ `virtual bool GetPromotionToParameterOverrideInternal(const FProperty& InProperty, bool& bOutOverride) const override;`
- L29 _private prototype_ `virtual void UpdateContextStruct(TConstStructView<FPropertyBindingBindableStructDescriptor> InStructDesc,FBindingContextStruct& InOutContextStruct, TMap<FString, FText>& InOutSectionNames) const override;`
- L30 _private function_ `virtual bool CanBindToArrayElements() const override`
- L34 _private prototype_ `virtual TNotNull<const UEdGraphSchema_K2*> GetEdGraphSchema() const override;`
- L35 _private prototype_ `virtual void CustomizeDetailWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, IPropertyBindingBindingCollectionOwner* InBindingsOwner, TSharedPtr<IPropertyHandle> InPropertyHandle, const FPropertyBindingPath& InTargetPath, TSharedPtr<UE::PropertyBinding::FCachedBindingData> InCachedBindingData) const override;`
- L36 _private prototype_ `virtual void CustomizePropertyBindingWidgetArgs(FPropertyBindingWidgetArgs& Args, IPropertyBindingBindingCollectionOwner* InBindingsOwner, const FPropertyBindingPath& InTargetPath, TSharedPtr<UE::PropertyBinding::FCachedBindingData> InCachedBindingData) override;`

#### class `FStateTreeBindingsChildrenCustomization`  
`class FStateTreeBindingsChildrenCustomization : public IDetailPropertyChildrenCustomizationHandler`  
_L40-45_
- inherits: `IDetailPropertyChildrenCustomizationHandler`
- desc: Overrides bound property's children composition.
- L43 _public prototype_ `virtual bool ShouldCustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle) override;`
- L44 _public prototype_ `virtual void CustomizeChildren(IDetailChildrenBuilder& ChildrenBuilder, TSharedPtr<IPropertyHandle> InPropertyHandle) override;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace StateTree` (scope `UE`)
- L17 _namespace_ `namespace PropertyBinding` (scope `UE::StateTree`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateTreePropertyBindingChanged, const FPropertyBindingPath& , const FPropertyBindingPath& );`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateTreePropertyBindingChanged, const FPropertyBindingPath& , const FPropertyBindingPath& );` (scope `UE::StateTree::PropertyBinding`)
- L20 _externvar_ `extern FOnStateTreePropertyBindingChanged OnStateTreePropertyBindingChanged;` (scope `UE::StateTree::PropertyBinding`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeBlueprintPropertyRefDetails.h` (Private)


#### class `FStateTreeBlueprintPropertyRefDetails`  
`class FStateTreeBlueprintPropertyRefDetails : public IPropertyTypeCustomization`  
_L17-28_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FStateTreeBlueprintPropertyRef.
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L27 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

#### class `UStateTreePropertyRefSchema`  
`class UStateTreePropertyRefSchema : public UEdGraphSchema_K2`  
_L34-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema_K2`
- desc: Specific property ref schema to allow customizing the requirements (e.g. supported containers).
- L38 _public prototype_ `virtual bool SupportsPinTypeContainer(TWeakPtr<const FEdGraphSchemaAction> SchemaAction, const FEdGraphPinType& PinType, const EPinContainerType& ContainerType) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeEditorColorDetails.h` (Private)


#### class `FStateTreeEditorColorRefDetails`  
`class FStateTreeEditorColorRefDetails : public IPropertyTypeCustomization`  
_L14-26_
- inherits: `IPropertyTypeCustomization`
- desc: Property Type Customization for FStateTreeEditorColorRef
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L25 _private prototype_ `UStateTreeEditorData* GetEditorData(const TSharedRef<IPropertyHandle>& PropertyHandle) const;`

#### class `FStateTreeEditorColorDetails`  
`class FStateTreeEditorColorDetails : public IPropertyTypeCustomization`  
_L29-59_
- inherits: `IPropertyTypeCustomization`
- desc: Property Type Customization for FStateTreeEditorColor
- L33 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L36 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L37 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L40 _private prototype_ `FLinearColor* GetColorPtr() const;`
- L42 _private prototype_ `FLinearColor GetColor() const;`
- L43 _private prototype_ `void SetColor(FLinearColor Color);`
- L45 _private prototype_ `void OnColorCommitted(FLinearColor Color);`
- L47 _private prototype_ `void OnColorCancelled(FLinearColor Color);`
- L49 _private prototype_ `FReply OnColorButtonClicked();`
- L51 _private prototype_ `void CreateColorPickerWindow();`
- L54 _private member_ `TSharedPtr<FScopedTransaction> ColorPickerTransaction;` — Current Transaction taking place when selecting a color from the picker
- L56 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L57 _private member_ `TSharedPtr<IPropertyHandle> ColorPropertyHandle;`
- L58 _private member_ `TSharedPtr<SWidget> ColorButtonWidget;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeEditorDataDetails.h` (Private)


#### class `FStateTreeEditorDataDetails`  
`class FStateTreeEditorDataDetails : public IDetailCustomization, FSelfRegisteringEditorUndoClient`  
_L13-36_
- inherits: `IDetailCustomization,FSelfRegisteringEditorUndoClient`
- L16 _private typedef_ `using Super = IDetailCustomization;`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _public prototype_ `virtual void PendingDelete() override;`
- L27 _protected prototype_ `void MakeArrayCategory(IDetailLayoutBuilder& DetailBuilder, FName CategoryName, const FText& DisplayName, int32 SortOrder, TSharedPtr<IPropertyHandle> PropertyHandle);`
- L30 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L31 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L33 _protected member_ `bool bPendingDelete = false;`
- L35 _protected member_ `TWeakPtr<IPropertyUtilities> WeakPropertyUtilities;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeEditorNodeDetails.h` (Private)


#### class `FStateTreeEditorNodeDetails`  
`class FStateTreeEditorNodeDetails : public IPropertyTypeCustomization`  
_L37-168_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for nodes (Conditions, Evaluators and Tasks) in StateTreeState.
- L41 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L43 _public prototype_ `virtual ~FStateTreeEditorNodeDetails();`
- L46 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L47 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L50 _private prototype_ `void MakeFlagsWidget();`
- L52 _private prototype_ `bool ShouldResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L53 _private prototype_ `void ResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L54 _private prototype_ `void OnCopyNode();`
- L55 _private prototype_ `void OnCopyAllNodes();`
- L56 _private prototype_ `void OnPasteNodes();`
- L57 _private prototype_ `TSharedPtr<IPropertyHandle> GetInstancedObjectValueHandle(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L59 _private prototype_ `FOptionalSize GetIndentSize() const;`
- L60 _private prototype_ `FReply HandleIndentPlus();`
- L61 _private prototype_ `FReply HandleIndentMinus();`
- L63 _private prototype_ `int32 GetIndent() const;`
- L64 _private prototype_ `void SetIndent(const int32 Indent) const;`
- L65 _private prototype_ `bool IsIndent(const int32 Indent) const;`
- L67 _private prototype_ `FSlateColor GetContentRowColor() const;`
- L69 _private prototype_ `FText GetOperandText() const;`
- L70 _private prototype_ `FText GetConditionOperandText() const;`
- L71 _private prototype_ `FText GetConsiderationOperandText() const;`
- L72 _private prototype_ `FSlateColor GetOperandColor() const;`
- L73 _private prototype_ `TSharedRef<SWidget> OnGetOperandContent() const;`
- L74 _private prototype_ `TSharedRef<SWidget> GetConditionOperandContent() const;`
- L75 _private prototype_ `TSharedRef<SWidget> GetConsiderationOperandContent() const;`
- L76 _private prototype_ `bool IsOperandEnabled() const;`
- L78 _private prototype_ `void SetOperand(const EStateTreeExpressionOperand Operand) const;`
- L79 _private prototype_ `bool IsOperand(const EStateTreeExpressionOperand Operand) const;`
- L81 _private prototype_ `bool IsFirstItem() const;`
- L82 _private prototype_ `int32 GetCurrIndent() const;`
- L83 _private prototype_ `int32 GetNextIndent() const;`
- L85 _private prototype_ `FText GetOpenParens() const;`
- L86 _private prototype_ `FText GetCloseParens() const;`
- L88 _private prototype_ `EVisibility IsConditionVisible() const;`
- L89 _private prototype_ `EVisibility IsConsiderationVisible() const;`
- L90 _private prototype_ `EVisibility IsOperandVisible() const;`
- L91 _private prototype_ `EVisibility AreIndentButtonsVisible() const;`
- L92 _private prototype_ `EVisibility AreParensVisible() const;`
- L93 _private prototype_ `EVisibility AreFlagsVisible() const;`
- L95 _private prototype_ `EVisibility IsIconVisible() const;`
- L96 _private prototype_ `const FSlateBrush* GetIcon() const;`
- L97 _private prototype_ `FSlateColor GetIconColor() const;`
- L99 _private prototype_ `FReply OnDescriptionClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;`
- L100 _private prototype_ `FText GetNodeDescription() const;`
- L101 _private prototype_ `EVisibility IsNodeDescriptionVisible() const;`
- L103 _private prototype_ `FText GetNodeTooltip() const;`
- L105 _private prototype_ `FReply OnRowMouseDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L106 _private prototype_ `FReply OnRowMouseUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L108 _private prototype_ `FText GetName() const;`
- L109 _private prototype_ `bool HandleVerifyNameChanged(const FText& InText, FText& OutErrorMessage) const;`
- L110 _private prototype_ `void HandleNameCommitted(const FText& NewLabel, ETextCommit::Type CommitType) const;`
- L112 _private prototype_ `FReply HandleToggleCompletionTaskClicked();`
- L113 _private prototype_ `FText GetToggleCompletionTaskTooltip() const;`
- L114 _private prototype_ `FSlateColor GetToggleCompletionTaskColor() const;`
- L115 _private prototype_ `const FSlateBrush* GetToggleCompletionTaskIcon() const;`
- L116 _private prototype_ `EVisibility GetToggleCompletionTaskVisibility() const;`
- L118 _private prototype_ `FText GetNodePickerTooltip() const;`
- L119 _private prototype_ `void OnNodePicked(const UStruct* InStruct) const;`
- L121 _private prototype_ `void OnIdentifierChanged(const UStateTree& StateTree);`
- L122 _private prototype_ `void OnBindingChanged(const FPropertyBindingPath& SourcePath, const FPropertyBindingPath& TargetPath);`
- L123 _private prototype_ `void FindOuterObjects();`
- L125 _private prototype_ `FReply OnBrowseToSource() const;`
- L126 _private prototype_ `FReply OnBrowseToNodeBlueprint() const;`
- L127 _private prototype_ `FReply OnEditNodeBlueprint() const;`
- L128 _private prototype_ `EVisibility IsBrowseToSourceVisible() const;`
- L129 _private prototype_ `EVisibility IsBrowseToNodeBlueprintVisible() const;`
- L130 _private prototype_ `EVisibility IsEditNodeBlueprintVisible() const;`
- L132 _private prototype_ `TSharedRef<SWidget> GenerateOptionsMenu();`
- L133 _private prototype_ `void GeneratePickerMenu(class FMenuBuilder& InMenuBuilder);`
- L134 _private prototype_ `void OnDeleteNode() const;`
- L135 _private prototype_ `void OnDeleteAllNodes() const;`
- L136 _private prototype_ `void OnDuplicateNode() const;`
- L137 _private prototype_ `void OnRenameNode() const;`
- L138 _private prototype_ `void HandleAssetChanged();`
- L140 _private member_ `TWeakObjectPtr<UScriptStruct> BaseScriptStruct;`
- L141 _private member_ `TWeakObjectPtr<UClass> BaseClass;`
- L142 _private member_ `TSharedPtr<SWidgetSwitcher> NameSwitcher;`
- L143 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameEdit;`
- L144 _private member_ `TSharedPtr<SBorder> RowBorder;`
- L145 _private member_ `TSharedPtr<SBorder> FlagsContainer;`
- L147 _private member_ `TWeakObjectPtr<UStateTreeEditorData> EditorData;`
- L148 _private member_ `TWeakObjectPtr<UStateTree> StateTree;`
- L149 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L151 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`
- L152 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L153 _private member_ `TSharedPtr<IPropertyHandle> NodeProperty;`
- L154 _private member_ `TSharedPtr<IPropertyHandle> InstanceProperty;`
- L155 _private member_ `TSharedPtr<IPropertyHandle> InstanceObjectProperty;`
- L156 _private member_ `TSharedPtr<IPropertyHandle> ExecutionRuntimeDataProperty;`
- L157 _private member_ `TSharedPtr<IPropertyHandle> ExecutionRuntimeDataObjectProperty;`
- L158 _private member_ `TSharedPtr<IPropertyHandle> IDProperty;`
- L160 _private member_ `TSharedPtr<IPropertyHandle> IndentProperty;`
- L161 _private member_ `TSharedPtr<IPropertyHandle> OperandProperty;`
- L163 _private member_ `TSharedPtr<IPropertyHandle> ParentProperty;`
- L164 _private member_ `TSharedPtr<IPropertyHandleArray> ParentArrayProperty;`
- L166 _private member_ `FDelegateHandle OnBindingChangedHandle;`
- L167 _private member_ `FDelegateHandle OnChangedAssetHandle;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeEditorNodeUtils.h` (Private)


#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace StateTreeEditor` (scope `UE`)
- L23 _namespace_ `namespace EditorNodeUtils` (scope `UE::StateTreeEditor`)
- L29 _prototype_ `const FStateTreeEditorNode* GetCommonNode(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — @param StructProperty property pointing to a FStateTreeEditorNode. @return StateTree editor node that is common for all edited instances.
- L35 _prototype_ `FStateTreeEditorNode* GetMutableCommonNode(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return mutable StateTree editor node that is common for all edited instances.
- L43 _prototype_ `void GetNodeBaseScriptStructAndClass(const TSharedPtr<IPropertyHandle>& StructProperty, UScriptStruct*& OutBaseScriptStruct, UClass*& OutBaseClass);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Returns class and/or struct defined in property's "BaseClass" and "BaseStruct" metadata. @param StructProperty Property handle where the meta data is looked at. @param OutBaseScriptStruct ScriptStruct pointer or null if not found or set. @param OutBaseClass Class pointer or null if not found or set.
- L50 _prototype_ `EVisibility IsConditionVisible(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Returns visibility status depending if the node is a Condition. @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return visibility status.
- L57 _prototype_ `EVisibility IsConsiderationVisible(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Returns visibility status depending if the node is a Consideration. @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return visibility status.
- L64 _prototype_ `EStateTreeConditionEvaluationMode GetConditionEvaluationMode(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Returns condition evaluation method of a node. @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return condition evaluation method or Evaluated if not valid node.
- L70 _prototype_ `bool IsTaskDisabled(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return Whether specified task node is marked as disable. Will return false if node is not a valid task.
- L76 _prototype_ `bool IsTaskEnabled(const FStateTreeEditorNode& EditorNode);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return Whether the specified task node is marked as enabled. Will return false if node is not a valid task.
- L79 _prototype_ `bool IsTaskConsideredForCompletion(const FStateTreeEditorNode& EditorNode);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — @return Whether the specified task is marked as ConsideredForCompletion.  Will return false if node is not a valid task.
- L82 _prototype_ `void SetTaskConsideredForCompletion(FStateTreeEditorNode& EditorNode, bool bIsConsidered);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Set the ConsideredForCompletion flag on the specified task.
- L85 _prototype_ `bool CanEditTaskConsideredForCompletion(const FStateTreeEditorNode& EditorNode);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — @return Whether the ConsideredForCompletion flag can be edited on the specified task.
- L93 _prototype_ `void ModifyNodeInTransaction(const FText& Description, const TSharedPtr<IPropertyHandle>& StructProperty, TFunctionRef<void(const TSharedPtr<IPropertyHandle>&)> Func);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Execute the provided function within a Transaction @param Description Description to associate to the transaction @param StructProperty Property handle of the StateTreeEditorNode(s) @param Func Function that will be execute in the transaction on a valid Editor node property
- L100 _prototype_ `FSlateIcon ParseIcon(const FName IconName);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Parses Slate Icon from a name. @param IconName In format StyleSetName | StyleName | [SmallStyleName | StatusOverlayStyleName] @return Slate icon from parsed name.
- L107 _prototype_ `FSlateIcon GetIcon(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Returns slate icon associated with specified node. @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return Slate icon from parsed from node's icon name.
- L114 _prototype_ `FSlateColor GetIconColor(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Returns color of icon associated with specified node. @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return Icon color, or foreground if not set.
- L121 _prototype_ `EVisibility IsIconVisible(const TSharedPtr<IPropertyHandle>& StructProperty);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Return visibility status depending on if the specified node has an icon. @param StructProperty Property handle pointing to a FStateTreeEditorNode. @return Visible, if the node has icon.
- L128 _prototype_ `void SetNodeType(const TSharedPtr<IPropertyHandle>& StructProperty, const UStruct* NewType);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Sets the type of a node. Creates a transaction. @param StructProperty Property handle pointing to a FStateTreeEditorNode. @param NewType New node type to set.
- L136 _prototype_ `void InstantiateStructSubobjects(UObject& OuterObject, FStructView Struct);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Recursively instantiates instanced objects of a given struct. It is needed to fixup nodes pasted from clipboard, which seem to give shallow copy. @param OuterObject the object the instanced objects should be outered to @param Struct the struct with the instanced objects
- L143 _prototype_ `void ConditionalUpdateNodeInstanceData(FStateTreeEditorNode& EditorNode, UObject& InstanceOuter);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Handles updating the Node Instance Data if there is a type mismatch @param EditorNode the node to check @param InstanceOuter the outer to use if the instance data is a uobject, or there are instanced uobjects within the instance data
- L153 _prototype_ `TSharedRef<SComboButton> CreateAddNodePickerComboButton(const FText& TooltipText, FLinearColor Color, TSharedPtr<IPropertyHandle> ArrayPropertyHandle, TSharedRef<IPropertyUtilities> PropUtils);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Creates widget combon button with plus icon (+), which summons node picker and adds the selected node to specified array. @param TooltipText Tool tip to show on he button. @param Color Color of the icon on the button. @param ArrayPropertyHandle Property handle pointing to a TArray<FStateTreeEditorNode>. @param PropUtils Property utils, used to check edit status and to refresh the array after add. @return shared ref to the created combo button.
- L168 _prototype_ `IDetailCategoryBuilder& MakeArrayCategory( IDetailLayoutBuilder& DetailBuilder, const TSharedPtr<IPropertyHandle>& ArrayPropertyHandle, FName CategoryName, const FText& CategoryDisplayName, FName IconName, FLinearColor IconColor, FLinearColor AddIconColor, const FText& AddButtonTooltipText, int32 SortOrder);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Creates a category and sets the contents of the row to: [Icon] [DisplayName]  [+]. @param DetailBuilder Detail builder where the category is added. @param ArrayPropertyHandle Property handle pointing to a TArray<FStateTreeEditorNode>. @param CategoryName Name of the category to create. @param CategoryDisplayName Display name of the category. @param IconName Name to the icon resource to show in front of the category display name. @param IconColor Color of icon resource. @param AddIconColor Color of the add icon. @param AddButtonTooltipText Tooltip text to show on the add buttons. @param SortOrder Category sort order (categories with smaller sort order appear earlier in details panel). @return Reference to the category builder of the category just created.
- L192 _prototype_ `IDetailCategoryBuilder& MakeArrayCategoryHeader( IDetailLayoutBuilder& DetailBuilder, const TSharedPtr<IPropertyHandle>& ArrayPropertyHandle, FName CategoryName, const FText& CategoryDisplayName, FName IconName, FLinearColor IconColor, const TSharedPtr<SWidget> Extension, FLinearColor AddIconColor, const FText& AddButtonTooltipText, int32 SortOrder);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Creates a category and sets the contents of the row to: [Icon] [DisplayName]  [+]. @param DetailBuilder Detail builder where the category is added. @param ArrayPropertyHandle Property handle pointing to a TArray<FStateTreeEditorNode>. @param CategoryName Name of the category to create. @param CategoryDisplayName Display name of the category. @param IconName Name to the icon resource to show in front of the category display name. @param IconColor Color of icon resource. @param AddIconColor Color of the add icon. @param AddButtonTooltipText Tooltip text to show on the add buttons. @param SortOrder Category sort order (categories with smaller sort order appear earlier in details panel). @return Reference to the category builder of the category just created.
- L209 _prototype_ `void MakeArrayItems(IDetailCategoryBuilder& Category, const TSharedPtr<IPropertyHandle>& ArrayPropertyHandle);` (scope `UE::StateTreeEditor::EditorNodeUtils`) — Creates the items of a category. @param Category Builder created by the header. @param ArrayPropertyHandle Property handle pointing to a TArray<FStateTreeEditorNode>.

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeEnumValueScorePairArrayBuilder.h` (Private)


#### class `FStateTreeEnumValueScorePairArrayBuilder`  
`class FStateTreeEnumValueScorePairArrayBuilder : public FDetailArrayBuilder , public TSharedFromThis<FStateTreeEnumValueScorePairArrayBuilder>`  
_L13-28_
- inherits: `FDetailArrayBuilder,TSharedFromThis<FStateTreeEnumValueScorePairArrayBuilder>`
- desc: Details customization for arrays composed of <EnumValue, Score> properties with a provided Enum Type.
- L17 _public prototype_ `FStateTreeEnumValueScorePairArrayBuilder(TSharedRef<IPropertyHandle> InBasePropertyHandle, const UEnum* InEnumType, bool InGenerateHeader = true, bool InDisplayResetToDefault = true, bool InDisplayElementNum = true);`
- L19 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L21 _private prototype_ `void CustomizePairRowWidget(TSharedRef<IPropertyHandle> PairPropertyHandle, IDetailChildrenBuilder& ChildrenBuilder);`
- L22 _private prototype_ `FText GetEnumEntryDescription(TSharedRef<IPropertyHandle> PairPropertyHandle) const;`
- L23 _private prototype_ `TSharedRef<SWidget> GetEnumEntryComboContent(TSharedPtr<IPropertyHandle> EnumValuePropertyHandle, TSharedPtr<IPropertyHandle> EnumNamePropertyHandle) const;`
- L26 _private member_ `TStrongObjectPtr<const UEnum> EnumType;`
- L27 _private member_ `TSharedPtr<IPropertyHandleArray> PairArrayProperty;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeEnumValueScorePairsDetails.h` (Private)


#### class `FStateTreeEnumValueScorePairsDetails`  
`class FStateTreeEnumValueScorePairsDetails : public IPropertyTypeCustomization`  
_L15-32_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L25 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _private prototype_ `FText GetDescription() const;`
- L28 _private prototype_ `TSharedRef<SWidget> OnGetComboContent() const;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> EnumProperty;`
- L31 _private member_ `TSharedPtr<IPropertyHandle> PairsProperty;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeEventDescDetails.h` (Private)


#### class `FStateTreeEventDescDetails`  
`class FStateTreeEventDescDetails : public IPropertyTypeCustomization`  
_L15-22_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FStateTreeEventDesc.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeReferenceDetails.h` (Private)


#### class `FStateTreeReferenceDetails`  
`class FStateTreeReferenceDetails : public IPropertyTypeCustomization`  
_L14-42_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FStateTreeReference.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L29 _private prototype_ `void OnTreeCompiled(const UStateTree& StateTree) const;` — Callback registered to StateTree post compilation delegate used to synchronize parameters. @param StateTree The StateTree asset that got compiled.
- L35 _private prototype_ `void SyncParameters(const UStateTree* StateTreeToSync = nullptr) const;` — Synchronizes parameters with StateTree asset parameters if needed. @param StateTreeToSync Optional StateTree asset used to filter which parameters should be synced. A null value indicates that all parameters should be synced.
- L37 _private prototype_ `static FString GetSchemaPath(IPropertyHandle& StructPropertyHandle);`
- L39 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> ParametersHandle;`
- L41 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeReferenceOverridesDetails.h` (Private)


#### class `FStateTreeReferenceOverridesDetails`  
`class FStateTreeReferenceOverridesDetails : public IPropertyTypeCustomization`  
_L13-28_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FNestedStateTreeReference.
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L25 _private member_ `TSharedPtr<IPropertyHandle> OverrideItemsHandle;`
- L27 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeStateDetails.h` (Private)


#### class `FStateTreeStateDetails`  
`class FStateTreeStateDetails : public IDetailCustomization, FSelfRegisteringEditorUndoClient`  
_L20-49_
- inherits: `IDetailCustomization,FSelfRegisteringEditorUndoClient`
- L23 _private typedef_ `using Super = IDetailCustomization;`
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L30 _public prototype_ `virtual void PendingDelete() override;`
- L31 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L35 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L36 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L39 _private prototype_ `EVisibility HandleDisableLinkedAssetOverrideVisibility() const;`
- L42 _protected member_ `TWeakPtr<IPropertyUtilities> WeakPropertyUtilities;`
- L43 _protected member_ `TWeakObjectPtr<UStateTreeEditorData> WeakEditorData;`
- L44 _protected member_ `TWeakObjectPtr<UStateTreeState> WeakState;`
- L46 _protected member_ `TStrongObjectPtr<UStateTreeFactory> OverrideFactoryForLinkedAsset;`
- L48 _protected member_ `bool bIsPendingDelete = false;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeStateLinkDetails.h` (Private)


#### class `FStateTreeStateLinkDetails`  
`class FStateTreeStateLinkDetails : public IPropertyTypeCustomization`  
_L24-60_
- inherits: `IPropertyTypeCustomization`
- L28 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L31 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L35 _private prototype_ `TSharedRef<SWidget> GenerateStatePicker();`
- L36 _private prototype_ `FText GetCurrentStateDesc() const;`
- L37 _private prototype_ `const FSlateBrush* GetCurrentStateIcon() const;`
- L38 _private prototype_ `FSlateColor GetCurrentStateColor() const;`
- L39 _private prototype_ `bool IsValidLink() const;`
- L40 _private prototype_ `TOptional<EStateTreeTransitionType> GetTransitionType() const;`
- L41 _private prototype_ `void OnStateSelected(TConstArrayView<FGuid> SelectedStateIDs);`
- L42 _private prototype_ `void SetTransitionByType(const EStateTreeTransitionType TransitionType);`
- L43 _private prototype_ `const UStateTreeState* GetState() const;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;`
- L46 _private member_ `TSharedPtr<IPropertyHandle> IDProperty;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> LinkTypeProperty;`
- L49 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L51 _private member_ `TWeakObjectPtr<const UStateTreeEditorData> WeakEditorData = nullptr;`
- L54 _private member_ `bool bDirectStatesOnly = false;` — If set, hide selecting meta states like Next or (tree) Succeeded.
- L56 _private member_ `bool bSubtreesOnly = false;` — If set, allow to select only states marked as subtrees.
- L58 _private member_ `class IPropertyUtilities* PropUtils = nullptr;`
- L59 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeStateParametersDetails.h` (Private)


#### class `FStateTreeStateParametersDetails`  
`class FStateTreeStateParametersDetails : public IPropertyTypeCustomization`  
_L19-45_
- inherits: `IPropertyTypeCustomization`
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L31 _private prototype_ `void FindOuterObjects();`
- L33 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> ParametersProperty;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> FixedLayoutProperty;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> IDProperty;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L40 _private member_ `bool bFixedLayout = false;`
- L42 _private member_ `TWeakObjectPtr<UStateTreeEditorData> WeakEditorData = nullptr;`
- L43 _private member_ `TWeakObjectPtr<UStateTree> WeakStateTree = nullptr;`
- L44 _private member_ `TWeakObjectPtr<UStateTreeState> WeakState = nullptr;`

#### class `FStateTreeStateParametersInstanceDataDetails`  
`class FStateTreeStateParametersInstanceDataDetails : public FPropertyBagInstanceDataDetails`  
_L48-72_
- inherits: `FPropertyBagInstanceDataDetails`
- L51 _public prototype_ `FStateTreeStateParametersInstanceDataDetails( const TSharedPtr<IPropertyHandle>& InStructProperty, const TSharedPtr<IPropertyHandle>& InParametersStructProperty, const TSharedPtr<IPropertyUtilities>& InPropUtils, const bool bInFixedLayout, FGuid InID, TWeakObjectPtr<UStateTreeEditorData> InEditorData, TWeakObjectPtr<UStateTreeState> InState);`
- L60 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow) override;`
- L62 _public prototype_ `virtual bool HasPropertyOverrides() const override;`
- L63 _public prototype_ `virtual void PreChangeOverrides() override;`
- L64 _public prototype_ `virtual void PostChangeOverrides() override;`
- L65 _public prototype_ `virtual void EnumeratePropertyBags(TSharedPtr<IPropertyHandle> PropertyBagHandle, const EnumeratePropertyBagFuncRef& Func) const override;`
- L68 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L69 _private member_ `TWeakObjectPtr<UStateTreeEditorData> WeakEditorData;`
- L70 _private member_ `TWeakObjectPtr<UStateTreeState> WeakState;`
- L71 _private member_ `FGuid ID;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/StateTreeTransitionDetails.h` (Private)


#### class `FStateTreeTransitionDetails`  
`class FStateTreeTransitionDetails : public IPropertyTypeCustomization`  
_L25-86_
- inherits: `IPropertyTypeCustomization`
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L32 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L33 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L37 _private prototype_ `UStateTreeState* GetOwningStateTreeState() const;`
- L38 _private prototype_ `UStateTreeEditorData* GetEditorData() const;`
- L40 _private prototype_ `FText GetDescription() const;`
- L42 _private prototype_ `FStateTreeStateLink GetTargetState() const;`
- L43 _private prototype_ `EStateTreeTransitionTrigger GetTrigger() const;`
- L44 _private prototype_ `bool GetDelayTransition() const;`
- L46 _private prototype_ `void OnCopyTransition() const;`
- L47 _private prototype_ `void OnCopyAllTransitions() const;`
- L49 _private prototype_ `void OnPasteTransitions() const;`
- L51 _private prototype_ `FSlateColor GetContentRowColor() const;`
- L53 _private prototype_ `FReply OnRowMouseDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L54 _private prototype_ `FReply OnRowMouseUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L55 _private prototype_ `TSharedRef<SWidget> GenerateOptionsMenu();`
- L56 _private prototype_ `void OnDeleteTransition() const;`
- L57 _private prototype_ `void OnDeleteAllTransitions() const;`
- L58 _private prototype_ `void OnDuplicateTransition() const;`
- L60 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L61 _private member_ `TSharedPtr<IPropertyHandle> TriggerProperty;`
- L62 _private member_ `TSharedPtr<IPropertyHandle> PriorityProperty;`
- L63 _private member_ `TSharedPtr<IPropertyHandle> RequiredEventProperty;`
- L64 _private member_ `TSharedPtr<IPropertyHandle> DelegateListener;`
- L65 _private member_ `TSharedPtr<IPropertyHandle> StateProperty;`
- L66 _private member_ `TSharedPtr<IPropertyHandle> DelayTransitionProperty;`
- L67 _private member_ `TSharedPtr<IPropertyHandle> TransitionReactivateProperty;`
- L68 _private member_ `TSharedPtr<IPropertyHandle> DelayDurationProperty;`
- L69 _private member_ `TSharedPtr<IPropertyHandle> DelayRandomVarianceProperty;`
- L70 _private member_ `TSharedPtr<IPropertyHandle> ConditionsProperty;`
- L71 _private member_ `TSharedPtr<IPropertyHandle> IDProperty;`
- L73 _private member_ `TSharedPtr<SBorder> RowBorder;`
- L75 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`
- L76 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L78 _private member_ `TSharedPtr<IPropertyHandle> ParentProperty;`
- L79 _private member_ `TSharedPtr<IPropertyHandleArray> ParentArrayProperty;`
- L82 _private member_ `FStateTreeStateLink CachedLastTargetState = {};` — Used to avoid having to re-compute if target state within this state's nested state hierachy.
- L85 _private member_ `bool bCachedIsTargetStateInNestedState = false;` — True if our last target state was in the nested state hierachy

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/Widgets/SAddTransitionMenu.h` (Private)


#### class `UE::StateTree::Editor::SAddTransitionMenu`  
`class SAddTransitionMenu : public SCompactTreeEditorView`  
_L24-63_
- inherits: `SCompactTreeEditorView`
- desc: State picker popup for creating a transition to a selected state. Extends SCompactTreeEditorView with a per-row trigger-type flyout: - Left-clicking a state row adds a transition with the default trigger and dismisses the menu. - Hovering a state row opens a chevron flyout listing all trigger types at the picker's right edge. Clicking a trigger type adds a transition with that trigger + state and dismisses the menu.
- L28 _public function_ `SLATE_BEGIN_ARGS(SAddTransitionMenu) : _OwnerState(nullptr) , _ViewModel(nullptr)`
- L32 _public prototype_ `SLATE_ARGUMENT(UStateTreeState*, OwnerState) SLATE_ARGUMENT(TSharedPtr<FStateTreeViewModel>, ViewModel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _protected prototype_ `virtual TSharedRef<STableRow<TSharedPtr<FStateItem>>> GenerateStateItemRowInternal( TSharedPtr<FStateItem> Item, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<SHorizontalBox> Container) override;`
- L50 _private prototype_ `static void AddTransition(TWeakPtr<FStateTreeViewModel> InViewModel , TWeakObjectPtr<UStateTreeState> InWeakOwnerState , TNotNull<UStateTreeState*> TargetState , EStateTreeTransitionTrigger Trigger);` — Adds a GotoState transition from OwnerState to TargetState with the given trigger, then dismisses all menus.
- L56 _private prototype_ `void CreateStateTransitionWithDefaultTrigger(TConstArrayView<FGuid> SelectedStateIDs) const;` — When the user clicks a state row directly, add a transition with the default trigger.
- L59 _private prototype_ `void HandleOnMouseEnterStateRow(const FGeometry& MyGeometry, const FPointerEvent& , const FGuid InStateID);` — Callback for when the main state selector row has mouse entry, Spawn submenu on hover.
- L61 _private member_ `TWeakObjectPtr<UStateTreeState> WeakOwnerState = nullptr;`
- L62 _private member_ `TWeakPtr<FStateTreeViewModel> WeakViewModel = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StateTree` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/Widgets/SCompactTreeEditorView.h` (Private)


#### struct `UE::StateTree::Editor::CompactTreeView::FStateItemLinkData`  
`struct FStateItemLinkData : public FStateItemCustomData`  
_L27-44_
- reflection: `USTRUCT()`
- inherits: `FStateItemCustomData`
- L38 _public prototype_ `FSlateColor GetBorderColor() const;`
- L40 _public member_ `uint8 LinkState = LinkState_None;`
- L41 _public member_ `bool bIsSubTree = false;`
- L42 _public member_ `bool bIsLinked = false;`
- L43 _public member_ `FText LinkedDesc;`

#### enum `UE::StateTree::Editor::CompactTreeView::FStateItemLinkData::ELinkState`  
`enum ELinkState`  
_L31-36_
- L33 _public enumerator_ `LinkState_None = 0x00`
- L34 _public enumerator_ `LinkState_LinkingIn = 0x01`
- L35 _public enumerator_ `LinkState_LinkedOut = 0x02`

#### class `UE::StateTree::Editor::SCompactTreeEditorView`  
`class SCompactTreeEditorView : public SCompactTreeView`  
_L51-108_
- inherits: `SCompactTreeView`
- desc: Widget that displays a list of State Tree nodes which match base types and specified schema. Can be used e.g. in popup menus to select node types.
- L55 _public function_ `SLATE_BEGIN_ARGS(SCompactTreeEditorView) : _StateTreeEditorData(nullptr) , _SelectionMode(ESelectionMode::Single) , _SelectableStatesOnly(false) , _SubtreesOnly(false) , _ShowLinkedStates(false)`
- L62 _public prototype_ `SLATE_ARGUMENT(const UStateTreeEditorData*, StateTreeEditorData) SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode) SLATE_ARGUMENT(bool, SelectableStatesOnly) SLATE_ARGUMENT(bool, SubtreesOnly) SLATE_ARGUMENT(bool, ShowLinkedStates) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FStateTreeViewModel>& InViewModel = nullptr);`
- L73 _public prototype_ `void Refresh(const UStateTreeEditorData* NewStateTreeEditorData = nullptr);`
- L78 _protected prototype_ `virtual TSharedRef<FStateItem> CreateStateItemInternal() const override;`
- L79 _protected prototype_ `virtual void CacheStatesInternal() override;`
- L80 _protected prototype_ `virtual TSharedRef<STableRow<TSharedPtr<FStateItem>>> GenerateStateItemRowInternal(TSharedPtr<FStateItem> Item, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<SHorizontalBox> Container) override;`
- L82 _protected prototype_ `virtual void OnSelectionChangedInternal(TConstArrayView<TSharedPtr<FStateItem>> SelectedStates) override;`
- L83 _protected prototype_ `virtual void OnUpdatingFilteredRootInternal() override;`
- L88 _private prototype_ `void CacheState(TSharedPtr<FStateItem> ParentNode, const UStateTreeState* State);`
- L89 _private prototype_ `void ResetLinkedStates();`
- L91 _private prototype_ `FReply HandleDragDetected(const FGeometry&, const FPointerEvent&) const;`
- L92 _private prototype_ `void HandleDragLeave(const FDragDropEvent& DragDropEvent) const;`
- L93 _private prototype_ `TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FStateItem> TargetState) const;`
- L94 _private prototype_ `FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FStateItem> TargetState) const;`
- L96 _private member_ `TWeakObjectPtr<const UStateTreeEditorData> WeakStateTreeEditorData = nullptr;`
- L97 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L98 _private member_ `TArray<TWeakPtr<FStateItem>> PreviousLinkedStates;`
- L101 _private member_ `bool bSubtreesOnly = false;` — If set, allow to select only states marked as subtrees.
- L104 _private member_ `bool bSelectableStatesOnly = false;` — If set, states without any selection behavior won't be included in the tree view.
- L107 _private member_ `bool bShowLinkedStates = false;` — If set, linked states will be displayed using a colored border in the tree view.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ESelectionMode`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace StateTree` (scope `UE`)
- L21 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L24 _namespace_ `namespace CompactTreeView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/Widgets/SStateTreeContextMenuButton.h` (Private)


#### class `SStateTreeContextMenuButton`  
`class SStateTreeContextMenuButton : public SButton`  
_L14-63_
- inherits: `SButton`
- L17 _public function_ `SLATE_BEGIN_ARGS(SStateTreeContextMenuButton) : _Content() , _ButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FButtonStyle >("Button")) , _ContentPadding(FMargin(4.0f, 2.0f)) , _bAllowDragAndDrop(false)`
- L26 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ARGUMENT(bool, bAllowDragAndDrop) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FStateTreeViewModel>& InStateTreeViewModel, const TWeakObjectPtr<UStateTreeState> InOwnerState, const FGuid& InSourceID, bool InbIsTransition = false);` — Slot for this button's content (optional)
- L42 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L43 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _public prototype_ `TSharedRef<SWidget> MakeContextMenu() const;`
- L49 _private prototype_ `FReply HandleButtonClicked();`
- L51 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L52 _private member_ `TWeakObjectPtr<UStateTreeState> OwnerStateWeak;`
- L53 _private member_ `FGuid NodeID;`
- L55 _private member_ `uint8 bIsTransition : 1;`
- L57 _private member_ `uint8 bIsStateTransition : 1;` — We have State Transition, Task Transition and Default Transition back to root
- L59 _private member_ `uint8 bSkipDefaultClickAction : 1 = false;`
- L62 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/Widgets/SStateTreeEditorColorComboBox.h` (Private)


#### class `SStateTreeEditorColorComboBox`  
`class SStateTreeEditorColorComboBox : public SCompoundWidget`  
_L19-53_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SStateTreeEditorColorComboBox)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IPropertyHandle> InColorRefHandle, UStateTreeEditorData* InEditorData);`
- L28 _private prototype_ `const FStateTreeEditorColor* FindColorEntry(const FStateTreeEditorColorRef& ColorRef) const;`
- L30 _private prototype_ `FText GetDisplayName(FStateTreeEditorColorRef ColorRef) const;`
- L31 _private prototype_ `FLinearColor GetColor(FStateTreeEditorColorRef ColorRef) const;`
- L33 _private prototype_ `TSharedRef<SWidget> GenerateColorOptionWidget(TSharedPtr<FStateTreeEditorColorRef> ColorRef);`
- L34 _private prototype_ `TSharedRef<SWidget> GenerateColorWidget(const FStateTreeEditorColorRef& ColorRef);`
- L36 _private prototype_ `void RefreshColorOptions();`
- L38 _private prototype_ `void OnSelectionChanged(TSharedPtr<FStateTreeEditorColorRef> SelectedColorRefOption, ESelectInfo::Type SelectInfo);`
- L40 _private prototype_ `void UpdatedSelectedColorWidget();`
- L42 _private member_ `TWeakObjectPtr<UStateTreeEditorData> WeakEditorData;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> ColorRefHandle;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> ColorIDHandle;`
- L47 _private member_ `TSharedPtr<SBorder> SelectedColorBorder;`
- L48 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FStateTreeEditorColorRef>>> ColorComboBox;`
- L50 _private member_ `TArray<TSharedPtr<FStateTreeEditorColorRef>> ColorRefOptions;`
- L52 _private member_ `FStateTreeEditorColorRef SelectedColorRef;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Customizations/Widgets/SStateTreeNodeTypePicker.h` (Private)


#### class `SStateTreeNodeTypePicker`  
`class SStateTreeNodeTypePicker : public SCompoundWidget`  
_L20-101_
- inherits: `SCompoundWidget`
- desc: Widget that displays a list of State Tree nodes which match base types and specified schema. Can be used e.g. in popup menus to select node types.
- L24 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnNodeStructPicked, const UStruct*);`
- L26 _public function_ `SLATE_BEGIN_ARGS(SStateTreeNodeTypePicker) : _CurrentStruct(nullptr) , _BaseScriptStruct(nullptr) , _BaseClass(nullptr) , _Schema(nullptr)`
- L33 _public prototype_ `SLATE_ARGUMENT(const UStruct*, CurrentStruct) SLATE_ARGUMENT(const UScriptStruct*, BaseScriptStruct) SLATE_ARGUMENT(const UClass*, BaseClass) SLATE_ARGUMENT(const UStateTreeSchema*, Schema) SLATE_ARGUMENT(FOnNodeStructPicked, OnNodeTypePicked) SLATE_END_ARGS() SStateTreeNodeTypePicker();` — Currently selected struct, initially highlighted.
- L47 _public prototype_ `void Construct(const FArguments& InArgs);`
- L50 _public prototype_ `TSharedPtr<SWidget> GetWidgetToFocusOnOpen();` — @returns widget to focus (search box) when the picker is opened.
- L72 _private prototype_ `static void SortNodeTypesFunctionItemsRecursive(TArray<TSharedPtr<FStateTreeNodeTypeItem>>& Items);`
- L73 _private prototype_ `static TSharedPtr<FStateTreeNodeTypeItem> FindOrCreateItemForCategory(TArray<TSharedPtr<FStateTreeNodeTypeItem>>& Items, TArrayView<FString> CategoryPath);`
- L74 _private prototype_ `void AddNode(const UStruct* Struct);`
- L75 _private prototype_ `void CacheNodeTypes(const UStateTreeSchema* Schema, const UScriptStruct* BaseScriptStruct, const UClass* BaseClass);`
- L77 _private prototype_ `TSharedRef<ITableRow> GenerateNodeTypeRow(TSharedPtr<FStateTreeNodeTypeItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L78 _private prototype_ `void GetNodeTypeChildren(TSharedPtr<FStateTreeNodeTypeItem> Item, TArray<TSharedPtr<FStateTreeNodeTypeItem>>& OutItems) const;`
- L79 _private prototype_ `void OnNodeTypeSelected(TSharedPtr<FStateTreeNodeTypeItem> SelectedItem, ESelectInfo::Type);`
- L80 _private prototype_ `void OnNodeTypeExpansionChanged(TSharedPtr<FStateTreeNodeTypeItem> ExpandedItem, bool bInExpanded);`
- L81 _private prototype_ `void OnSearchBoxTextChanged(const FText& NewText);`
- L82 _private prototype_ `int32 FilterNodeTypesChildren(const TArray<FString>& FilterStrings, const bool bParentMatches, const TArray<TSharedPtr<FStateTreeNodeTypeItem>>& SourceArray, TArray<TSharedPtr<FStateTreeNodeTypeItem>>& OutDestArray);`
- L83 _private prototype_ `void ExpandAll(const TArray<TSharedPtr<FStateTreeNodeTypeItem>>& Items);`
- L84 _private prototype_ `TArray<TSharedPtr<FStateTreeNodeTypeItem>> GetPathToItemStruct(const UStruct* Struct) const;`
- L86 _private prototype_ `void RestoreExpansionState();`
- L88 _private member_ `TSharedPtr<FStateTreeNodeTypeItem> RootNode;`
- L89 _private member_ `TSharedPtr<FStateTreeNodeTypeItem> FilteredRootNode;`
- L91 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L92 _private member_ `TSharedPtr<STreeView<TSharedPtr<FStateTreeNodeTypeItem>>> NodeTypeTree;`
- L93 _private member_ `bool bIsRestoringExpansion = false;`
- L95 _private member_ `FOnNodeStructPicked OnNodeStructPicked;`
- L97 _private member_ `FObjectKey CategoryKey;`
- L100 _private member_ `static TMap<FObjectKey, FCategoryExpansionState> CategoryExpansionStates;` — Save expansion state for each base node type. The expansion state does not persist between editor sessions.

#### struct `SStateTreeNodeTypePicker::FStateTreeNodeTypeItem`  
`struct FStateTreeNodeTypeItem`  
_L54-64_
- desc: Stores a category path segment, or a node type.
- L56 _public function_ `bool IsCategory() const`
- L57 _public function_ `FString GetCategoryName()`
- L59 _public member_ `TArray<FString> CategoryPath;`
- L60 _public member_ `const UStruct* Struct = nullptr;`
- L61 _public member_ `FSlateIcon Icon;`
- L62 _public member_ `FSlateColor IconColor;`
- L63 _public member_ `TArray<TSharedPtr<FStateTreeNodeTypeItem>> Children;`

#### struct `SStateTreeNodeTypePicker::FCategoryExpansionState`  
`struct FCategoryExpansionState`  
_L67-70_
- desc: Stores per session node expansion state for a node type.
- L69 _public member_ `TSet<FString> CollapsedCategories;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNodeStructPicked, const UStruct*);`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/SStateTreeDebuggerEventTimelineView.h` (Private)


#### class `SStateTreeDebuggerEventTimelineView`  
`class SStateTreeDebuggerEventTimelineView : public SCompoundWidget`  
_L18-81_
- inherits: `SCompoundWidget`
- desc: Displays a sequence of points and windows for a statetree debugger instance timeline. This is a slightly modified version of the SEventTimelineView used by RewindDebugger so it should make it easier to eventually merge the tools.
- L45 _public function_ `SLATE_BEGIN_ARGS(SStateTreeDebuggerEventTimelineView) : _ViewRange(TRange<double>(0,10)) , _DesiredSize(FVector2D(100.f,20.f))`
- L50 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View time range
- L53 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<FTimelineEventData>, EventData);` — Data for events to render
- L56 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, DesiredSize);` — Desired widget size
- L58 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L70 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L71 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L73 _protected prototype_ `int32 PaintEvents(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const;`
- L75 _protected member_ `TAttribute<TRange<double>> ViewRange;`
- L76 _protected member_ `TAttribute<TSharedPtr<FTimelineEventData>> EventData;`
- L77 _protected member_ `TAttribute<FVector2D> DesiredSize;`
- L79 _protected member_ `const FSlateBrush* EventBrush = nullptr;`
- L80 _protected member_ `const FSlateBrush* EventBorderBrush = nullptr;`

#### struct `SStateTreeDebuggerEventTimelineView::FTimelineEventData`  
`struct FTimelineEventData`  
_L21-43_
- L41 _public member_ `TArray<EventPoint> Points;`
- L42 _public member_ `TArray<EventWindow> Windows;`

#### struct `SStateTreeDebuggerEventTimelineView::FTimelineEventData::EventPoint`  
`struct EventPoint`  
_L24-30_
- L26 _public member_ `double Time;`
- L27 _public member_ `FText Type;`
- L28 _public member_ `FText Description;`
- L29 _public member_ `FLinearColor Color;`

#### struct `SStateTreeDebuggerEventTimelineView::FTimelineEventData::EventWindow`  
`struct EventWindow`  
_L32-39_
- L34 _public member_ `double TimeStart;`
- L35 _public member_ `double TimeEnd;`
- L36 _public member_ `FText Type;`
- L37 _public member_ `FText Description;`
- L38 _public member_ `FLinearColor Color;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/SStateTreeDebuggerInstanceTree.h` (Private)


#### class `SStateTreeDebuggerInstanceTree`  
`class SStateTreeDebuggerInstanceTree : public SCompoundWidget`  
_L16-54_
- inherits: `SCompoundWidget`
- L18 _private typedef_ `using FOnSelectionChanged = STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>::FOnSelectionChanged;`
- L19 _private typedef_ `using FOnMouseButtonDoubleClick = STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>::FOnMouseButtonDoubleClick;`
- L22 _public function_ `SLATE_BEGIN_ARGS(SStateTreeDebuggerInstanceTree)`
- L23 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>*, InstanceTracks);`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr< SScrollBar >, ExternalScrollBar);`
- L25 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnMouseButtonDoubleClick, OnMouseButtonDoubleClick) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FSimpleDelegate, OnExpansionChanged) SLATE_EVENT(FOnTableViewScrolled, OnScrolled) SLATE_END_ARGS() SStateTreeDebuggerInstanceTree();`
- L33 _public prototype_ `virtual ~SStateTreeDebuggerInstanceTree();`
- L35 _public prototype_ `void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `void Refresh();`
- L38 _public prototype_ `void RestoreExpansion();`
- L40 _public prototype_ `TSharedPtr<RewindDebugger::FRewindDebuggerTrack> GetSelection() const;`
- L41 _public prototype_ `void SetSelection(const TSharedPtr<RewindDebugger::FRewindDebuggerTrack>& SelectedItem) const;`
- L42 _public prototype_ `void ScrollTo(const TSharedPtr<RewindDebugger::FRewindDebuggerTrack>& SelectedItem) const;`
- L43 _public prototype_ `void ScrollTo(double ScrollOffset) const;`
- L46 _private prototype_ `TSharedRef<ITableRow> GenerateTreeRow(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L47 _private prototype_ `void TreeExpansionChanged(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> Item, bool bShouldBeExpanded) const;`
- L49 _private member_ `TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>* InstanceTracks = nullptr;`
- L51 _private member_ `TSharedPtr<STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>> TreeView;`
- L53 _private member_ `FSimpleDelegate OnExpansionChanged;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace RewindDebugger`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/SStateTreeDebuggerTimelines.h` (Private)


#### class `SStateTreeDebuggerTimelines`  
`class SStateTreeDebuggerTimelines : public SSimpleTimeSlider`  
_L17-85_
- inherits: `SSimpleTimeSlider`
- L19 _private typedef_ `using FOnSelectionChanged = STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>::FOnSelectionChanged;`
- L21 _public function_ `SLATE_BEGIN_ARGS(SStateTreeDebuggerTimelines)`
- L23 _public prototype_ `SLATE_ARGUMENT( TArray< TSharedPtr< RewindDebugger::FRewindDebuggerTrack > >*, InstanceTracks );`
- L24 _public prototype_ `SLATE_ARGUMENT( TSharedPtr<SScrollBar>, ExternalScrollbar) SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FOnTableViewScrolled, OnScrolled) SLATE_EVENT( FSimpleDelegate, OnExpansionChanged ) SLATE_ATTRIBUTE(double, ScrubPosition);`
- L34 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ViewRange);` — View time range
- L37 _public prototype_ `SLATE_ATTRIBUTE(TRange<double>, ClampRange);` — Clamp time range
- L40 _public prototype_ `SLATE_EVENT(FOnScrubPositionChanged, OnScrubPositionChanged);` — Called when the scrub position changes
- L43 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnBeginScrubberMovement);` — Called right before the scrubber begins to move
- L46 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnEndScrubberMovement);` — Called right after the scrubber handle is released by the user
- L49 _public prototype_ `SLATE_EVENT(FOnRangeChanged, OnViewRangeChanged);` — Called when the view range changes
- L56 _public prototype_ `SStateTreeDebuggerTimelines();` — Default constructor.
- L57 _public prototype_ `virtual ~SStateTreeDebuggerTimelines();`
- L64 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the application. @param InArgs The Slate argument list.
- L66 _public prototype_ `void Refresh();`
- L67 _public prototype_ `void RestoreExpansion();`
- L69 _public prototype_ `void SetSelection(const TSharedPtr<RewindDebugger::FRewindDebuggerTrack>& SelectedItem);`
- L70 _public prototype_ `void ScrollTo(double ScrollOffset);`
- L72 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L75 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L78 _private prototype_ `TSharedRef<ITableRow> GenerateTreeRow(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L79 _private prototype_ `void TreeExpansionChanged(TSharedPtr<RewindDebugger::FRewindDebuggerTrack> InItem, bool bShouldBeExpanded);`
- L81 _private member_ `TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>* InstanceTracks = nullptr;`
- L82 _private member_ `TSharedPtr<STreeView<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>>> InstanceTreeView;`
- L84 _private member_ `FSimpleDelegate OnExpansionChanged;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RewindDebugger`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/SStateTreeDebuggerView.h` (Private)


#### class `SStateTreeDebuggerView`  
`class SStateTreeDebuggerView : public SCompoundWidget`  
_L40-206_
- inherits: `SCompoundWidget`
- desc: Widget holding the timelines for all statetree instances matching a given asset in addition to some frame details panels.
- L43 _public function_ `SLATE_BEGIN_ARGS(SStateTreeDebuggerView)`
- L46 _public prototype_ `~SStateTreeDebuggerView();`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, TNotNull<const UStateTree*> InStateTree, const TSharedRef<FStateTreeViewModel>& InStateTreeViewModel, const TSharedRef<FUICommandList>& InCommandList);`
- L50 _public function_ `[[nodiscard]] TSharedPtr<FStateTreeDebugger> GetDebugger() const`
- L55 _public function_ `[[nodiscard]] double GetExtrapolatedRecordedWorldTime() const`
- L61 _private prototype_ `void ConstructLegacyView(const TSharedRef<FUICommandList>& InCommandList);`
- L62 _private prototype_ `void ConstructView(const TSharedRef<FUICommandList>& InCommandList);`
- L64 _private prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L65 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L67 _private prototype_ `void RefreshTracks();`
- L69 _private prototype_ `void TrackCursor();`
- L71 _private prototype_ `TSharedRef<SWidget> OnGetDebuggerTracesMenu() const;`
- L73 _private prototype_ `void OnPIEStarted(bool bIsSimulating);`
- L74 _private prototype_ `void OnPIEStopped(bool bIsSimulating);`
- L75 _private prototype_ `void OnPIEPaused(bool bIsSimulating) const;`
- L76 _private prototype_ `void OnPIEResumed(bool bIsSimulating) const;`
- L77 _private prototype_ `void OnPIESingleStepped(bool bIsSimulating) const;`
- L79 _private prototype_ `void OnBreakpointHit(const FStateTreeInstanceDebugId InstanceId, const FStateTreeDebuggerBreakpoint Breakpoint, const TSharedRef<FUICommandList> ActionList) const;`
- L80 _private prototype_ `void OnNewSession();`
- L81 _private prototype_ `void OnNewInstance(FStateTreeInstanceDebugId InstanceId);`
- L84 _private prototype_ `void BindDebuggerToolbarCommands(const TSharedRef<FUICommandList>& ToolkitCommands);` — Legacy debugger commands
- L87 _private prototype_ `void BindDebuggingToolbarCommands(const TSharedRef<FUICommandList> ToolkitCommands);` — RewindDebugger sync commands
- L89 _private prototype_ `static bool CanOpenRewindDebugger();`
- L90 _private prototype_ `static void OpenRewindDebugger();`
- L92 _private prototype_ `bool CanUseScrubButtons() const;`
- L94 _private function_ `bool CanStartRecording() const`
- L99 _private prototype_ `void StartRecording();`
- L101 _private function_ `bool IsRecording() const`
- L106 _private function_ `bool CanStopRecording() const`
- L111 _private prototype_ `void StopRecording();`
- L113 _private prototype_ `void HandleTracesStateChanged(EStateTreeTraceStatus TraceStatus);`
- L114 _private prototype_ `void HandleTracesStopped();`
- L116 _private prototype_ `bool CanResumeDebuggerAnalysis() const;`
- L117 _private prototype_ `void ResumeDebuggerAnalysis() const;`
- L119 _private prototype_ `bool CanResetTracks() const;`
- L120 _private prototype_ `void ResetTracks();`
- L122 _private prototype_ `bool CanStepBackToPreviousStateWithEvents() const;`
- L123 _private prototype_ `void StepBackToPreviousStateWithEvents();`
- L125 _private prototype_ `bool CanStepForwardToNextStateWithEvents() const;`
- L126 _private prototype_ `void StepForwardToNextStateWithEvents();`
- L128 _private prototype_ `bool CanStepBackToPreviousStateChange() const;`
- L129 _private prototype_ `void StepBackToPreviousStateChange();`
- L131 _private prototype_ `bool CanStepForwardToNextStateChange() const;`
- L132 _private prototype_ `void StepForwardToNextStateChange();`
- L135 _private prototype_ `void OnTimeLineScrubPositionChanged(double Time, bool bIsScrubbing);` — Callback from timeline widgets to update the debugger scrub state.
- L138 _private prototype_ `void OnDebuggerScrubStateChanged(const UE::StateTreeDebugger::FScrubState& ScrubState);` — Callback used to reflect debugger scrub state in the UI.
- L140 _private member_ `TSharedPtr<FStateTreeDebugger> Debugger;`
- L141 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L142 _private member_ `TWeakObjectPtr<const UStateTree> StateTree;`
- L143 _private member_ `TWeakObjectPtr<UStateTreeEditorData> StateTreeEditorData;`
- L144 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L147 _private member_ `TArray<TSharedPtr<RewindDebugger::FRewindDebuggerTrack>> InstanceOwnerTracks;` — Tracks for all statetree instance owners producing trace events for the associated state tree asset.
- L154 _private member_ `TSharedPtr<SStateTreeDebuggerInstanceTree> InstancesTreeView;` — Tree view displaying the instance names and synced with InstanceTimelinesTreeView. Note that this is currently used as a list view but kept the tree view to be close to the rewind debugger track implementation.
- L161 _private member_ `TSharedPtr<SStateTreeDebuggerTimelines> InstanceTimelinesTreeView;` — Tree view displaying the instance timelines and synced with InstancesTreeView. Note that this is currently used as a list view but kept the tree view to be close to the rewind debugger track implementation.
- L164 _private member_ `TSharedPtr<SSplitter> HeaderSplitter;` — Splitter between instances selector and simple time slider. Used with TreeViewsSplitter to keep header and content in sync
- L167 _private member_ `TSharedPtr<SSplitter> TreeViewsSplitter;` — Splitter between instances names and their timelines. Used with HeaderSplitter to keep header and content in sync
- L170 _private member_ `TSharedPtr<UE::StateTreeDebugger::SFrameEventsView> EventsView;` — Tree view displaying the frame events of the instance associated to the selected track.
- L173 _private member_ `TAttribute<double> ScrubTimeAttribute;` — Attribute provided by the debugger scrub position to control cursor and timelines positions.
- L176 _private member_ `TRange<double> ViewRange = TRange<double>(0.0, 10.0);` — Range controlled by the timeline widgets and used to adjust cursor position and track content.
- L179 _private member_ `double MaxTrackRecordingDuration = 0.0;` — In case tracks are not reset when a new analysis session is started we keep track of the longest duration to adjust our clamp range.
- L182 _private member_ `double LastUpdatedTrackRecordingDuration = 0.0;` — The recording duration time the UI was last updated from the debugger. Used to detect if new data has been collect while the UI was inactive.
- L188 _private member_ `double ExtrapolatedRecordedWorldTime = 0.0;` — Extrapolated world time used to make the timeline progress until the debugger receives a new event that will update its last processed world time.
- L191 _private member_ `bool bDisplayMigrationToRewindDebuggerWarning = true;` — Whether the "Migration To Rewind Debugger" is visible.
- L195 _private member_ `FDelegateHandle BeginPIEHandle;`
- L196 _private member_ `FDelegateHandle PausePIEHandle;`
- L197 _private member_ `FDelegateHandle ResumePIEHandle;`
- L198 _private member_ `FDelegateHandle SingleStepPIEHandle;`
- L199 _private member_ `FDelegateHandle ShutdownPIEHandle;`
- L202 _private member_ `bool bRecording = false;` — Indicates that a live session was started (record button or auto record in PIE) to generate StateTree traces.
- L205 _private member_ `bool bAutoScroll = true;` — True if the timelines scrolls automatically.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace RewindDebugger`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace StateTreeDebugger` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/StateTreeDebuggerCommands.h` (Private)


#### class `FStateTreeDebuggerCommands`  
`class FStateTreeDebuggerCommands : public TCommands<FStateTreeDebuggerCommands>`  
_L12-29_
- inherits: `TCommands<FStateTreeDebuggerCommands>`
- desc: StateTree Debugger command set.
- L15 _public prototype_ `FStateTreeDebuggerCommands();`
- L18 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> StartRecording;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> StopRecording;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> PreviousFrameWithStateChange;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> PreviousFrameWithEvents;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> NextFrameWithEvents;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> NextFrameWithStateChange;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ResumeDebuggerAnalysis;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ResetTracks;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> OpenRewindDebugger;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/StateTreeDebuggerTrack.h` (Private)


#### struct `UE::StateTreeDebugger::FInstanceTrackHelper`  
`struct FInstanceTrackHelper : public TSharedFromThis<FInstanceTrackHelper>`  
_L20-84_
- inherits: `TSharedFromThis<FInstanceTrackHelper>`
- desc: Helper struct for debuggers relying on StateTree instance tracks
- L22 _public prototype_ `explicit FInstanceTrackHelper(const FStateTreeInstanceDebugId InInstanceId, const TRange<double>& InViewRange);`
- L24 _public function_ `TSharedPtr<SStateTreeDebuggerEventTimelineView::FTimelineEventData> GetTimelineData() const`
- L34 _public prototype_ `bool RebuildEventData( TNotNull<const UStateTree*> InStateTree , const FInstanceEventCollection& InEventCollection , const double InRecordingDuration , const double InScrubTime , FStateTreeTraceActiveStates* OutLastActiveStates = nullptr , const bool bInIsStaleTrack = false) const;` — Rebuild the timeline data from the provided Event collection @return Whether the number of points, or windows, in the timeline data changed since the last update.
- L42 _public function_ `FStateTreeInstanceDebugId GetInstanceId() const`
- L47 _public function_ `const FStateTreeTraceActiveStates& GetActiveStates() const`
- L52 _public function_ `void SetActiveStates(const FStateTreeTraceActiveStates& InActiveStates)`
- L57 _public function_ `TSharedPtr<SWidget> CreateTimelineView()`
- L80 _protected member_ `FStateTreeInstanceDebugId InstanceId;`
- L81 _protected member_ `TSharedPtr<SStateTreeDebuggerEventTimelineView::FTimelineEventData> TimelineData;`
- L82 _protected member_ `const TRange<double>& ViewRange;`
- L83 _protected member_ `FStateTreeTraceActiveStates ActiveStates;`

#### struct `FStateTreeDebuggerBaseTrack`  
`struct FStateTreeDebuggerBaseTrack : RewindDebugger::FRewindDebuggerTrack`  
_L90-129_
- inherits: `RewindDebugger::FRewindDebuggerTrack`
- desc: Base struct for Debugger tracks to append some functionalities not available in RewindDebuggerTrack
- L92 _public function_ `explicit FStateTreeDebuggerBaseTrack(const FSlateIcon& Icon, const FText& TrackName) : Icon(Icon) , TrackName(TrackName)`
- L98 _public function_ `virtual bool IsStale() const`
- L103 _public function_ `virtual void MarkAsStale(const double InStaleTime)`
- L107 _public function_ `virtual void OnSelected()`
- L112 _protected function_ `virtual FSlateIcon GetIconInternal() override`
- L117 _protected function_ `virtual FName GetNameInternal() const override`
- L122 _protected function_ `virtual FText GetDisplayNameInternal() const override`
- L127 _protected member_ `FSlateIcon Icon;`
- L128 _protected member_ `FText TrackName;`

#### struct `FStateTreeDebuggerInstanceTrack`  
`struct FStateTreeDebuggerInstanceTrack : FStateTreeDebuggerBaseTrack`  
_L132-173_
- inherits: `FStateTreeDebuggerBaseTrack`
- desc: Track used to represent timeline events for a single StateTree instance.
- L134 _public prototype_ `explicit FStateTreeDebuggerInstanceTrack( const TSharedRef<SStateTreeDebuggerView>& InDebuggerView, const TSharedRef<FStateTreeDebugger>& InDebugger, const FStateTreeInstanceDebugId InInstanceId, const FText& InName, const TRange<double>& InViewRange);`
- L141 _public prototype_ `virtual void OnSelected() override;`
- L143 _public function_ `void MarkAsActive()`
- L148 _public function_ `virtual void MarkAsStale(const double InStaleTime) override`
- L157 _public function_ `virtual bool IsStale() const override`
- L163 _protected prototype_ `virtual bool UpdateInternal() override;`
- L164 _protected prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L168 _private member_ `TWeakPtr<SStateTreeDebuggerView> StateTreeDebuggerView;`
- L169 _private member_ `TWeakPtr<FStateTreeDebugger> StateTreeDebugger;`
- L170 _private member_ `TSharedRef<UE::StateTreeDebugger::FInstanceTrackHelper> InstanceTrackHelper;`
- L171 _private member_ `TSharedPtr<const UE::StateTreeDebugger::FInstanceDescriptor> Descriptor;`
- L172 _private member_ `double StaleTime = UE::StateTreeDebugger::FInstanceDescriptor::ActiveInstanceEndTime;`

#### struct `FStateTreeDebuggerOwnerTrack`  
`struct FStateTreeDebuggerOwnerTrack : FStateTreeDebuggerBaseTrack`  
_L177-200_
- inherits: `FStateTreeDebuggerBaseTrack`
- desc: Parent track of all the statetree instance tracks sharing the same execution context owner
- L179 _public prototype_ `explicit FStateTreeDebuggerOwnerTrack(const FText& InInstanceName);`
- L181 _public function_ `void AddSubTrack(const TSharedPtr<FStateTreeDebuggerInstanceTrack>& InSubTrack)`
- L186 _public function_ `int32 NumSubTracks() const`
- L191 _public prototype_ `virtual void MarkAsStale(double InStaleTime) override;`
- L192 _public prototype_ `virtual bool IsStale() const override;`
- L195 _protected prototype_ `virtual bool UpdateInternal() override;`
- L196 _protected prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L199 _private member_ `TArray<TSharedPtr<FStateTreeDebuggerInstanceTrack>> SubTracks;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTreeDebugger` (scope `UE`)
- L61 _function_ `` (scope `UE::StateTreeDebugger::FInstanceTrackHelper::CreateTimelineView`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/StateTreeDebuggerUIExtensions.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace StateTreeEditor` (scope `UE`)
- L18 _namespace_ `namespace DebuggerExtensions` (scope `UE::StateTreeEditor`)
- L21 _prototype_ `TSharedRef<SWidget> CreateStateWidget(TSharedPtr<IPropertyHandle> StateEnabledProperty, const TSharedPtr<FStateTreeViewModel>& InStateTreeViewModel);` (scope `UE::StateTreeEditor::DebuggerExtensions`)
- L22 _prototype_ `void AppendStateMenuItems(FMenuBuilder& InMenuBuilder, TSharedPtr<IPropertyHandle> StateEnabledProperty, const TSharedPtr<FStateTreeViewModel>& InStateTreeViewModel);` (scope `UE::StateTreeEditor::DebuggerExtensions`)
- L24 _prototype_ `TSharedRef<SWidget> CreateEditorNodeWidget(const TSharedPtr<IPropertyHandle>& StructPropertyHandle, const TSharedPtr<FStateTreeViewModel>& InStateTreeViewModel);` (scope `UE::StateTreeEditor::DebuggerExtensions`)
- L25 _prototype_ `void AppendEditorNodeMenuItems(FMenuBuilder& InMenuBuilder, const TSharedPtr<IPropertyHandle>& StructPropertyHandle, const TSharedPtr<FStateTreeViewModel>& InStateTreeViewModel);` (scope `UE::StateTreeEditor::DebuggerExtensions`)
- L26 _prototype_ `bool IsEditorNodeEnabled(const TSharedPtr<IPropertyHandle>& StructPropertyHandle);` (scope `UE::StateTreeEditor::DebuggerExtensions`)
- L28 _prototype_ `TSharedRef<SWidget> CreateTransitionWidget(const TSharedPtr<IPropertyHandle>& StructPropertyHandle, const TSharedPtr<FStateTreeViewModel>& InStateTreeViewModel);` (scope `UE::StateTreeEditor::DebuggerExtensions`)
- L29 _prototype_ `void AppendTransitionMenuItems(FMenuBuilder& InMenuBuilder, const TSharedPtr<IPropertyHandle>& StructPropertyHandle, const TSharedPtr<FStateTreeViewModel>& InStateTreeViewModel);` (scope `UE::StateTreeEditor::DebuggerExtensions`)
- L30 _prototype_ `bool IsTransitionEnabled(const TSharedPtr<IPropertyHandle>& StructPropertyHandle);` (scope `UE::StateTreeEditor::DebuggerExtensions`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/StateTreeRewindDebuggerExtensions.h` (Private)


#### class `UE::StateTreeDebugger::FRewindDebuggerPlaybackExtension`  
`class FRewindDebuggerPlaybackExtension final : public IRewindDebuggerExtension`  
_L12-21_
- inherits: `IRewindDebuggerExtension`
- L14 _private prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`
- L15 _private prototype_ `virtual void AnalysisSessionOpened(IRewindDebugger* RewindDebugger) override;`
- L16 _private prototype_ `virtual void AnalysisSessionClosed(IRewindDebugger* RewindDebugger) override;`
- L17 _private prototype_ `virtual void Clear(IRewindDebugger* RewindDebugger) override;`
- L20 _private member_ `double LastScrubTime = 0.0;` — Last scrub time we received. Used to avoid redundant updates.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StateTreeDebugger` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/Debugger/StateTreeRewindDebuggerTrack.h` (Private)


#### struct `UE::StateTreeDebugger::FRewindDebuggerTrackCreator`  
`struct FRewindDebuggerTrackCreator final : RewindDebugger::IRewindDebuggerTrackCreator`  
_L23-35_
- inherits: `RewindDebugger::IRewindDebuggerTrackCreator`
- desc: RewindDebugger track creator for StateTree instances
- L26 _protected prototype_ `virtual FName GetTargetTypeNameInternal() const override;`
- L27 _protected function_ `virtual FName GetNameInternal() const override`
- L31 _protected prototype_ `virtual void GetTrackTypesInternal(TArray<RewindDebugger::FRewindDebuggerTrackType>& Types) const override;`
- L32 _protected prototype_ `virtual TSharedPtr<RewindDebugger::FRewindDebuggerTrack> CreateTrackInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L33 _protected prototype_ `virtual bool HasDebugInfoInternal(const RewindDebugger::FObjectId& InObjectId) const override;`
- L34 _protected prototype_ `virtual bool IsCreatingPrimaryChildTrackInternal() const override;`

#### struct `UE::StateTreeDebugger::FRewindDebuggerTrack`  
`struct FRewindDebuggerTrack : RewindDebugger::FRewindDebuggerTrack, ITraceReader`  
_L41-76_
- inherits: `RewindDebugger::FRewindDebuggerTrack,ITraceReader`
- desc: RewindDebugger track representing a single StateTree instance
- L43 _public prototype_ `explicit FRewindDebuggerTrack(const RewindDebugger::FObjectId& InObjectId);`
- L47 _private prototype_ `virtual FInstanceEventCollection* GetOrCreateEventCollection(FStateTreeInstanceDebugId InstanceId) override;`
- L51 _private prototype_ `virtual bool UpdateInternal() override;`
- L52 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L53 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L54 _private prototype_ `virtual FText GetDisplayNameInternal() const override;`
- L55 _private prototype_ `virtual FSlateIcon GetIconInternal() override;`
- L56 _private prototype_ `virtual FName GetNameInternal() const override;`
- L57 _private prototype_ `virtual uint64 GetObjectIdInternal() const override;`
- L58 _private prototype_ `virtual bool HandleDoubleClickInternal() override;`
- L59 _private prototype_ `virtual FText GetStepCommandTooltipInternal(RewindDebugger::EStepMode) const override;`
- L60 _private prototype_ `virtual TOptional<double> GetStepFrameTimeInternal(RewindDebugger::EStepMode, const FScrubTimeInformation&) const override;`
- L63 _private member_ `FInstanceEventCollection EventCollection;`
- L64 _private member_ `TSharedRef<FInstanceTrackHelper> InstanceTrackHelper;`
- L65 _private member_ `TSharedPtr<const FInstanceDescriptor> Descriptor;`
- L66 _private member_ `TSharedPtr<StateTree::Editor::SCompactTreeDebuggerView> CompactTreeView;`
- L67 _private member_ `TSharedPtr<SFrameEventsView> EventsView;`
- L68 _private member_ `FSlateIcon Icon;`
- L69 _private member_ `RewindDebugger::FObjectId ObjectId;`
- L72 _private member_ `double LastTraceReadTime = 0;` — Last time in the recording that we used to fetch events, and that we will use for the next read.
- L75 _private member_ `double LastUpdateScrubTime = 0;` — Last scrub time used to rebuild the event data.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace StateTree` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace StateTreeDebugger` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/FindTools/SStateTreeFind.h` (Private)


#### class `UE::StateTreeEditor::SFindInAsset`  
`class SFindInAsset : public SCompoundWidget`  
_L22-144_
- inherits: `SCompoundWidget`
- desc: Widget to display and find inside a StateTree asset.
- L59 _private typedef_ `using STreeViewType = STreeView<TSharedPtr<FFindResult>>;`
- L62 _public function_ `SLATE_BEGIN_ARGS(SFindInAsset)`
- L63 _public prototype_ `SLATE_ARGUMENT_DEFAULT(bool, bShowSearchBar) = true;`
- L64 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IStateTreeEditorHost> EditorHost);`
- L68 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L70 _public prototype_ `void MakeQuery(FStringView SearchString);`
- L72 _public prototype_ `void ClearResults();`
- L76 _private prototype_ `void MakeQueryDelayed();` — Delay the query to allow for async or multiple assets search.
- L77 _private prototype_ `void TriggerQueryDelayed();`
- L80 _private prototype_ `void RegisterCommands();` — Register commands used by the widget.
- L81 _private prototype_ `void HandleCopyAction();`
- L82 _private prototype_ `void HandleSelectAllAction();`
- L83 _private prototype_ `void RecursiveSelectAllAction(const TSharedPtr<FFindResult>&);`
- L86 _private prototype_ `EVisibility HandleGetSearchingWidgetVisiblity() const;` — Celled to check the visibility of the result.
- L89 _private prototype_ `void HandleSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user changes commits text to the search box
- L95 _private prototype_ `FReply HandleLockButtonClicked();` — Called when the lock button is clicked in a global find results tab
- L98 _private prototype_ `const FSlateBrush* HandleGetLockButtonImage() const;` — Returns the image used for the lock button in a global find results tab
- L101 _private prototype_ `void HandleGetTreeChildren(TSharedPtr<FFindResult> InItem, TArray<TSharedPtr<FFindResult>>& OutChildren);` — Get the children of a row
- L104 _private prototype_ `void HandleTreeSelectionDoubleClicked(TSharedPtr<FFindResult> Item);` — Called when user double clicks on a new result
- L107 _private prototype_ `TSharedRef<ITableRow> HandleTreeGenerateRow(TSharedPtr<FFindResult> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L110 _private prototype_ `TSharedPtr<SWidget> HandleTreeContextMenuOpening();` — Callback to build the context menu when right clicking in the tree
- L113 _private prototype_ `void ExpandAll(const TSharedPtr<FFindResult>& Entry);` — Expand all item in the tree.
- L116 _private member_ `TWeakPtr<IStateTreeEditorHost> EditorHost;`
- L119 _private member_ `TSet<FObjectKey> ProcessedStateTrees;` — Tree processed during .
- L122 _private member_ `TArray<FObjectKey> StateTreesToProcess;` — Object to search.
- L124 _private member_ `FString SearchString;`
- L125 _private member_ `bool bSearching = false;`
- L128 _private member_ `TSharedPtr<SSearchBox> SearchTextField;` — The search text box.
- L131 _private member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results.
- L134 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commands handled by this widget.
- L137 _private member_ `TArray<TSharedPtr<FFindResult>> ItemsFound;` — This buffer stores the currently displayed results.
- L140 _private member_ `FString SearchValue;` — The string to search for.
- L143 _private member_ `FText HighlightText;` — The string to highlight in the results.

#### class `UE::StateTreeEditor::SFindInAsset::FFindResult`  
`class FFindResult`  
_L26-58_
- desc: Item that matched the search results
- L29 _public member_ `TArray<TSharedPtr<FFindResult>> Children;`
- L30 _public member_ `TWeakPtr<FFindResult> Parent;`
- L33 _public member_ `const FSlateBrush* IconBrush = nullptr;` — The brush for the icon.
- L34 _public member_ `FSlateColor IconColor;`
- L37 _public member_ `FName Name;` — Valid when the type is State, Node or Value.
- L40 _public member_ `FText PropertyName;` — Valid when the type is Value.
- L41 _public member_ `FString Value;`
- L44 _public member_ `FGuid ID;` — Valid when type is State or Node
- L47 _public member_ `TWeakObjectPtr<UStateTree> StateTree;` — Valid when type is StateTree
- L57 _public member_ `EResultType Type = EResultType::StateTree;` — The type of the result.

#### enum `UE::StateTreeEditor::SFindInAsset::FFindResult::EResultType`  
`enum class EResultType : uint8`  
_L49-55_
- L51 _public enumerator_ `StateTree`
- L52 _public enumerator_ `State`
- L53 _public enumerator_ `Node`
- L54 _public enumerator_ `Value`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace StateTreeEditor` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/K2Node_StateTreeBlueprintPropertyRef.h` (Private)


#### class `FKCHandler_StateTreeBlueprintPropertyRefGet`  
`class FKCHandler_StateTreeBlueprintPropertyRefGet : public FNodeHandlingFunctor`  
_L8-17_
- inherits: `FNodeHandlingFunctor`
- L12 _public prototype_ `virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L13 _public prototype_ `virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override;`
- L16 _private member_ `TMap<UEdGraphNode*, FBPTerminal*> TemporaryBoolTerminals;`

#### class `UK2Node_StateTreeBlueprintPropertyRef`  
`class UK2Node_StateTreeBlueprintPropertyRef : public UK2Node`  
_L20-43_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- L25 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `FText GetTooltipText() const override;`
- L27 _public prototype_ `FText GetMenuCategory() const override;`
- L29 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L30 _public prototype_ `virtual void ReconstructNode() override;`
- L31 _public prototype_ `virtual void ClearCachedBlueprintData(UBlueprint* Blueprint) override;`
- L33 _public prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L35 _public function_ `virtual FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override`
- L41 _protected prototype_ `void UpdateOutputPin() const;`
- L42 _protected prototype_ `void AllocateDefaultPins() override;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/K2Node_StateTreeNodeGetPropertyDescription.h` (Private)


#### class `UK2Node_StateTreeNodeGetPropertyDescription`  
`class UK2Node_StateTreeNodeGetPropertyDescription : public UK2Node`  
_L16-39_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- desc: Returns description for a specific property in the class. If the property has a binding, the binding string will be returned. Otherwise the current value of the property is returned.
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _public prototype_ `virtual FText GetTooltipText() const override;`
- L23 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L25 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L26 _public function_ `virtual bool IsNodePure() const override`
- L27 _public function_ `virtual bool ShouldShowNodeProperties() const override`
- L28 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L29 _public prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L32 _protected prototype_ `virtual void AllocateDefaultPins() override;`
- L36 _protected member_ `FMemberReference Variable;` — `UPROPERTY(EditAnywhere, Category = "Node", meta=(PropertyReference, AllowOnlyVisibleProperties))` — Property of the class to describe.

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/K2Node_StateTreeReference.h` (Private)


#### class `UK2Node_MakeStateTreeReference`  
`class UK2Node_MakeStateTreeReference : public UK2Node`  
_L13-73_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- L18 _public prototype_ `UK2Node_MakeStateTreeReference();`
- L19 _public prototype_ `virtual void BeginDestroy() override;`
- L21 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _public prototype_ `virtual FText GetTooltipText() const override;`
- L23 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L24 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L25 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const;`
- L27 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L28 _public prototype_ `virtual ERedirectType DoPinsMatchForReconstruction(const UEdGraphPin* NewPin, int32 NewPinIndex, const UEdGraphPin* OldPin, int32 OldPinIndex) const override;`
- L29 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L30 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L32 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L33 _public prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;`
- L34 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L36 _public prototype_ `virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L38 _public function_ `virtual bool NodeCausesStructuralBlueprintChange() const override`
- L43 _public function_ `virtual bool IsNodePure() const override`
- L48 _public function_ `virtual bool DrawNodeAsVariable() const override`
- L53 _public function_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override`
- L59 _private prototype_ `void CreatePropertyPins();`
- L60 _private prototype_ `UStateTree* GetStateTreeDefaultValue() const;`
- L61 _private prototype_ `void SetStateTree(UStateTree* InStateTree);`
- L62 _private prototype_ `void HandleStateTreeCompiled(const UStateTree& StateTree);`
- L67 _private member_ `TArray<FOptionalPinFromProperty> ShowPinForProperties;` — `UPROPERTY()` — Created pins from the state tree properties
- L70 _private member_ `TObjectPtr<UStateTree> StateTree;` — `UPROPERTY()` — State tree asset set in the pin and saved here to rebuild the property pins.
- L72 _private member_ `FDelegateHandle ParametersChangedHandle;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/SStateTreeDiff.h` (Private)


#### struct `UE::StateTree::Diff::FDiffPanel`  
`struct FDiffPanel`  
_L26-43_
- desc: Panel used to display the state tree
- L29 _public member_ `TStrongObjectPtr<const UStateTree> StateTree = nullptr;` — The asset that owns the state tree view we are showing
- L32 _public member_ `FRevisionInfo RevisionInfo;` — Revision information for this asset
- L35 _public member_ `bool bShowAssetName = true;` — True if we should show a name identifying which asset this panel is displaying
- L38 _public member_ `TSharedPtr<SWidget> OverlayRevisionInfo;` — The widget that contains the revision info in graph mode
- L42 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this diff panel

#### class `UE::StateTree::Diff::SDiffWidget`  
`class SDiffWidget : public SCompoundWidget`  
_L46-144_
- inherits: `SCompoundWidget`
- desc: Visual Diff between two StateTree assets
- L49 _public function_ `SLATE_BEGIN_ARGS(SDiffWidget)`
- L50 _public prototype_ `SLATE_ARGUMENT(const UStateTree*, OldAsset) SLATE_ARGUMENT(const UStateTree*, NewAsset) SLATE_ARGUMENT(struct FRevisionInfo, OldRevision) SLATE_ARGUMENT(struct FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() SDiffWidget();`
- L59 _public prototype_ `void Construct(const FArguments& InArgs);`
- L60 _public prototype_ `virtual ~SDiffWidget();`
- L63 _public prototype_ `static TSharedRef<SDiffWidget> CreateDiffWindow(FText WindowTitle, TNotNull<const UStateTree*> OldStateTree, TNotNull<const UStateTree*> NewStateTree, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision);` — Helper function to create a window that holds a diff widget
- L66 _public prototype_ `static TSharedRef<SDiffWidget> CreateDiffWindow(TNotNull<const UStateTree*> OldStateTree, TNotNull<const UStateTree*> NewStateTree, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision, const UClass* StateTreeClass);` — Helper function to create a window that holds a diff widget (default window title)
- L70 _protected prototype_ `void NextDiff() const;` — Called when user clicks button to go to next difference
- L73 _protected prototype_ `void PrevDiff() const;` — Called when user clicks button to go to prev difference
- L76 _protected prototype_ `bool HasNextDiff() const;` — Called to determine whether we have a list of differences to cycle through
- L77 _protected prototype_ `bool HasPrevDiff() const;`
- L80 _protected prototype_ `void GenerateDifferencesList();` — Function used to generate the list of differences and the widgets needed to calculate that list
- L83 _protected prototype_ `void HandleAssetEditorRequestClose(UObject* Asset, EAssetEditorCloseReason CloseReason);` — Called when editor may need to be closed
- L91 _protected prototype_ `void GenerateDiffPanel();`
- L93 _protected prototype_ `void HandleStateDiffEntryFocused(const FSingleDiffEntry& StateDiff);`
- L95 _protected prototype_ `void SetDetailsDiff(const UStateTreeState* OldState = nullptr, const UStateTreeState* NewState = nullptr);`
- L97 _protected prototype_ `static void AddStateTreeExtensionToDetailsView(const TSharedRef<IDetailsView>& DetailsView);`
- L99 _protected prototype_ `void AddBindingDiffToDiffEntries(TArray<FSingleObjectDiffEntry>& OutEntries);`
- L101 _protected prototype_ `static TSharedRef<SWidget> GenerateCustomDiffEntryWidget(const FSingleObjectDiffEntry& DiffEntry, FText& ObjectName, const UStateTreeState* OldState, const UStateTreeState* NewState);`
- L103 _protected prototype_ `static void OrganizeDiffEntries(TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>& OutDiffTreeEntries, const TArray<FSingleObjectDiffEntry>& DiffEntries, TFunctionRef<TSharedPtr<FBlueprintDifferenceTreeEntry>(const FSingleObjectDiffEntry&)> GenerateDiffTreeEntry, TFunctionRef<TSharedPtr<FBlueprintDifferenceTreeEntry>(FText&)> GenerateCategoryEntry, const UStateTreeState* OldState, const UStateTreeState* NewState);`
- L108 _protected prototype_ `bool ShouldHighlightRow(const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>& DiffNode);`
- L110 _protected prototype_ `static FLinearColor GetRowHighlightColor(const TUniquePtr<FAsyncDetailViewDiff::DiffNodeType>& DiffNode);`
- L113 _protected member_ `FDiffPanel OldAssetPanel;` — The panel used to show the old revision
- L116 _protected member_ `FDiffPanel NewAssetPanel;` — The panel used to show the new revision
- L118 _protected member_ `TSharedPtr<SBox> DetailsViewContents;`
- L120 _protected member_ `TSharedPtr<SSplitter> TopRevisionInfoWidget;`
- L122 _protected member_ `TArray<FSingleDiffEntry> StateBindingDiffs;`
- L125 _protected member_ `TArray<TSharedPtr<class FBlueprintDifferenceTreeEntry>> Differences;` — List of all differences, cached so that we can iterate only the differences and not labels, etc.
- L128 _protected member_ `TSharedPtr<STreeView<TSharedPtr<FBlueprintDifferenceTreeEntry>>> DifferencesTreeView;` — Tree view that displays the differences, cached for the buttons that iterate the differences:
- L131 _protected member_ `FStateTreePanel StateTreePanel;` — Stored reference to widget used to display the StateTree
- L134 _protected member_ `TWeakPtr<SWindow> WeakParentWindow;` — A pointer to the window holding this
- L136 _protected member_ `FDelegateHandle AssetEditorCloseHandle;`
- L139 _private member_ `static inline const FLazyName ConditionName = FLazyName("Ent`
- L140 _private member_ `static inline const FLazyName TaskName = FLazyName("Tas`
- L141 _private member_ `static inline const FLazyName TransitionName = FLazyName("Tra`
- L142 _private member_ `static inline const FLazyName ConsiderationName = FLazyName("Con`
- L143 _private member_ `static inline const FLazyName ParameterName = FLazyName("Par`

#### struct `UE::StateTree::Diff::SDiffWidget::FStateTreePanel`  
`struct FStateTreePanel`  
_L85-89_
- L87 _public member_ `TSharedPtr<SDiffSplitter> Splitter;`
- L88 _public member_ `TSharedPtr<FDiffControl> DiffControl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace StateTree` (scope `UE`)
- L17 _namespace_ `namespace Diff` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/SStateTreeExpanderArrow.h` (Private)


#### class `SStateTreeExpanderArrow`  
`class SStateTreeExpanderArrow : public SCompoundWidget`  
_L20-85_
- inherits: `SCompoundWidget`
- desc: Bespoke implementation of expander arrow for State Tree.
- L24 _public function_ `SLATE_BEGIN_ARGS( SStateTreeExpanderArrow ) : _StyleSet(&FCoreStyle::Get()) , _IndentAmount(10) , _BaseIndentLevel(0) , _Image(nullptr) , _ImageSize(16.f, 16.f) , _ImagePadding(FMargin())`
- L32 _public prototype_ `SLATE_ARGUMENT(const ISlateStyle*, StyleSet) SLATE_ARGUMENT(float, IndentAmount) SLATE_ARGUMENT(int32, BaseIndentLevel) SLATE_ATTRIBUTE(const FSlateBrush*, Image) SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity) SLATE_ARGUMENT(FVector2f, ImageSize) SLATE_ARGUMENT(FSlateColor, WireColorAndOpacity) SLATE_ARGUMENT(FMargin, ImagePadding) SLATE_END_ARGS() SStateTreeExpanderArrow();`
- L44 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedPtr<class ITableRow>& TableRow );`
- L48 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L51 _protected prototype_ `FReply OnArrowClicked();` — Invoked when the expanded button is clicked (toggle item expansion)
- L54 _protected prototype_ `EVisibility GetExpanderVisibility() const;` — @return Visible when has children; invisible otherwise
- L57 _protected prototype_ `const FSlateBrush* GetExpanderImage() const;` — @return the name of an image that should be shown as the expander arrow
- L60 _protected prototype_ `FMargin GetExpanderPadding() const;` — @return the margin corresponding to how far this item is indented
- L63 _protected member_ `TWeakPtr<class ITableRow> OwnerRowPtr;` — Pointer to the owning row.
- L66 _protected member_ `float IndentAmount = 10.0f;` — The amount of space to indent at each level
- L69 _protected member_ `int32 BaseIndentLevel = 0;` — The level in the tree that begins the indention amount
- L72 _protected member_ `FSlateColor WireColor;` — Color for the wires
- L75 _protected member_ `FVector2f ImageSize = FVector2f(16, 16);` — Size of the expander image.
- L78 _protected member_ `FMargin ImagePadding;` — Padding for the expander image.
- L81 _protected member_ `TSharedPtr<SButton> ExpanderArrow;` — A reference to the expander button
- L84 _protected member_ `const ISlateStyle* StyleSet = nullptr;` — The slate style to use

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/SStateTreeOutliner.h` (Private)


#### class `SStateTreeOutliner`  
`class SStateTreeOutliner : public SCompoundWidget`  
_L19-73_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SStateTreeOutliner)`
- L25 _public prototype_ `SStateTreeOutliner();`
- L28 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FStateTreeViewModel> StateTreeViewModel, const TSharedRef<FUICommandList>& InCommandList);`
- L32 _private prototype_ `void HandleModelAssetChanged();` — ViewModel handlers
- L33 _private prototype_ `void HandleModelStatesRemoved(const TSet<UStateTreeState*>& AffectedParents);`
- L34 _private prototype_ `void HandleModelStatesMoved(const TSet<UStateTreeState*>& AffectedParents, const TSet<UStateTreeState*>& MovedStates);`
- L35 _private prototype_ `void HandleModelStateAdded(UStateTreeState* ParentState, UStateTreeState* NewState);`
- L36 _private prototype_ `void HandleModelStatesChanged(const TSet<UStateTreeState*>& AffectedStates, const FPropertyChangedEvent& PropertyChangedEvent);`
- L37 _private prototype_ `void HandleModelSelectionChanged(const TArray<TWeakObjectPtr<UStateTreeState>>& SelectedStates);`
- L38 _private prototype_ `void HandleTreeViewSelectionChanged(TConstArrayView<FGuid> SelectedStateIDs);`
- L39 _private prototype_ `void HandleVisualThemeChanged(const UStateTree& StateTree);`
- L41 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L42 _private prototype_ `TSharedPtr<SWidget> HandleContextMenuOpening();`
- L46 _private prototype_ `UStateTreeState* GetFirstSelectedState() const;` — Action handlers @todo: these are also defined in the SStateTreeView, figure out how to share code.
- L47 _private prototype_ `void HandleAddSiblingState();`
- L48 _private prototype_ `void HandleAddChildState();`
- L49 _private prototype_ `void HandleCutSelectedStates();`
- L50 _private prototype_ `void HandleCopySelectedStates();`
- L51 _private prototype_ `void HandlePasteStatesAsSiblings();`
- L52 _private prototype_ `void HandlePasteStatesAsChildren();`
- L53 _private prototype_ `void HandleDuplicateSelectedStates();`
- L54 _private prototype_ `void HandleDeleteStates();`
- L55 _private prototype_ `void HandleEnableSelectedStates();`
- L56 _private prototype_ `void HandleDisableSelectedStates();`
- L58 _private prototype_ `bool HasSelection() const;`
- L59 _private prototype_ `bool CanPaste() const;`
- L60 _private prototype_ `bool CanEnableStates() const;`
- L61 _private prototype_ `bool CanDisableStates() const;`
- L63 _private prototype_ `void BindCommands();`
- L65 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L67 _private member_ `TSharedPtr<UE::StateTree::Editor::SCompactTreeEditorView> CompactTreeView;`
- L69 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L71 _private member_ `bool bItemsDirty = false;`
- L72 _private member_ `bool bUpdatingSelection = false;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTree` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/SStateTreeSplitter.h` (Private)


#### class `UE::StateTree::Diff::SDiffSplitter`  
`class SDiffSplitter : public SCompoundWidget`  
_L16-72_
- inherits: `SCompoundWidget`
- desc: Splitter that allows you to provide an FAsyncStateTreeViewDiff to connect like-properties between two or more state tree panels
- L33 _public prototype_ `static FSlot::FSlotArguments Slot();`
- L35 _public function_ `SLATE_BEGIN_ARGS(SDiffSplitter)`
- L38 _public prototype_ `SLATE_SLOT_ARGUMENT(FSlot, Slots) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `void AddSlot(const FSlot::FSlotArguments& SlotArgs, int32 Index = INDEX_NONE);`
- L45 _public prototype_ `void HandleSelectionChanged(const FStateSoftPath& StatePath, const FStateSoftPath& SecondaryStatePath);`
- L48 _protected prototype_ `void HandleSelectionChanged(const TArray<TWeakObjectPtr<UStateTreeState>>& SelectedStates);`
- L68 _private member_ `TArray<FPanel> Panels;`
- L69 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L71 _private member_ `FStateSoftPath SelectedState;`

#### class `UE::StateTree::Diff::SDiffSplitter::FSlot`  
`class FSlot : public TSlotBase<FSlot>`  
_L19-32_
- inherits: `TSlotBase<FSlot>`
- L22 _public prototype_ `FSlot() = default;`

#### struct `UE::StateTree::Diff::SDiffSplitter::FPanel`  
`struct FPanel`  
_L51-66_
- L53 _public function_ `FPanel(const TSharedPtr<SStateTreeView>& StateTreeView, const UStateTree* StateTree, const TAttribute<bool>& bIsReadonly, const TAttribute<TSharedPtr<FAsyncDiff>>& DiffRight) : StateTreeView(StateTreeView) , StateTree(StateTree) , IsReadonly(bIsReadonly) , DiffRight(DiffRight)`
- L62 _public member_ `TSharedPtr<SStateTreeView> StateTreeView;`
- L63 _public member_ `const UStateTree* StateTree = nullptr;`
- L64 _public member_ `TAttribute<bool> IsReadonly;`
- L65 _public member_ `TAttribute<TSharedPtr<FAsyncDiff>> DiffRight;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace StateTree` (scope `UE`)
- L11 _namespace_ `namespace Diff` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/SStateTreeView.h` (Private)


#### class `SStateTreeView`  
`class SStateTreeView : public SCompoundWidget`  
_L18-100_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SStateTreeView)`
- L24 _public prototype_ `SStateTreeView();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FStateTreeViewModel> StateTreeViewModel, const TSharedRef<FUICommandList>& InCommandList);`
- L29 _public prototype_ `void SavePersistentExpandedStates();`
- L31 _public prototype_ `TSharedPtr<FStateTreeViewModel> GetViewModel() const;`
- L33 _public prototype_ `void SetSelection(const TArray<TWeakObjectPtr<UStateTreeState>>& SelectedStates) const;`
- L36 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L37 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L39 _private prototype_ `void UpdateTree(bool bExpandPersistent = false);`
- L42 _private prototype_ `void HandleUserSettingsChanged();`
- L45 _private prototype_ `void HandleModelAssetChanged();`
- L46 _private prototype_ `void HandleModelStatesRemoved(const TSet<UStateTreeState*>& AffectedParents);`
- L47 _private prototype_ `void HandleModelStatesMoved(const TSet<UStateTreeState*>& AffectedParents, const TSet<UStateTreeState*>& MovedStates);`
- L48 _private prototype_ `void HandleModelStateAdded(UStateTreeState* ParentState, UStateTreeState* NewState);`
- L49 _private prototype_ `void HandleModelStatesChanged(const TSet<UStateTreeState*>& AffectedStates, const FPropertyChangedEvent& PropertyChangedEvent);`
- L50 _private prototype_ `void HandleModelStateNodesChanged(const UStateTreeState* AffectedState);`
- L51 _private prototype_ `void HandleModelSelectionChanged(const TArray<TWeakObjectPtr<UStateTreeState>>& SelectedStates);`
- L54 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TWeakObjectPtr<UStateTreeState> InState, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L55 _private prototype_ `void HandleGetChildren(TWeakObjectPtr<UStateTreeState> InParent, TArray<TWeakObjectPtr<UStateTreeState>>& OutChildren);`
- L56 _private prototype_ `void HandleTreeSelectionChanged(TWeakObjectPtr<UStateTreeState> InSelectedItem, ESelectInfo::Type SelectionType);`
- L57 _private prototype_ `void HandleTreeExpansionChanged(TWeakObjectPtr<UStateTreeState> InSelectedItem, bool bExpanded);`
- L59 _private prototype_ `TSharedPtr<SWidget> HandleContextMenuOpening();`
- L60 _private prototype_ `TSharedRef<SWidget> HandleGenerateSettingsMenu();`
- L64 _private prototype_ `UStateTreeState* GetFirstSelectedState() const;`
- L65 _private prototype_ `FReply HandleAddStateButton();`
- L66 _private prototype_ `void HandleAddSiblingState();`
- L67 _private prototype_ `void HandleAddChildState();`
- L68 _private prototype_ `void HandleCutSelectedStates();`
- L69 _private prototype_ `void HandleCopySelectedStates();`
- L70 _private prototype_ `void HandlePasteStatesAsSiblings();`
- L71 _private prototype_ `void HandlePasteStatesAsChildren();`
- L72 _private prototype_ `void HandleDuplicateSelectedStates();`
- L73 _private prototype_ `void HandlePasteNodesToState();`
- L74 _private prototype_ `void HandleRenameState();`
- L75 _private prototype_ `void HandleDeleteStates();`
- L76 _private prototype_ `void HandleEnableSelectedStates();`
- L77 _private prototype_ `void HandleDisableSelectedStates();`
- L79 _private prototype_ `bool HasSelection() const;`
- L80 _private prototype_ `bool CanPasteStates() const;`
- L81 _private prototype_ `bool CanEnableStates() const;`
- L82 _private prototype_ `bool CanDisableStates() const;`
- L83 _private prototype_ `bool CanPasteNodesToSelectedStates() const;`
- L85 _private prototype_ `void BindCommands();`
- L87 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L89 _private member_ `TSharedPtr<STreeView<TWeakObjectPtr<UStateTreeState>>> TreeView;`
- L90 _private member_ `TSharedPtr<SScrollBar> ExternalScrollbar;`
- L91 _private member_ `TSharedPtr<SScrollBox> ViewBox;`
- L92 _private member_ `TArray<TWeakObjectPtr<UStateTreeState>> Subtrees;`
- L94 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L96 _private member_ `UStateTreeState* RequestedRenameState;`
- L97 _private member_ `FDelegateHandle SettingsChangedHandle;`
- L98 _private member_ `bool bItemsDirty;`
- L99 _private member_ `bool bUpdatingSelection;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ESelectInfo`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/SStateTreeViewRow.h` (Private)


#### class `SStateTreeViewRow`  
`class SStateTreeViewRow : public STableRow<TWeakObjectPtr<UStateTreeState>>`  
_L22-139_
- inherits: `STableRow<TWeakObjectPtr<UStateTreeState>>`
- L26 _public function_ `SLATE_BEGIN_ARGS(SStateTreeViewRow)`
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TWeakObjectPtr<UStateTreeState> InState, const TSharedPtr<SScrollBox>& ViewBox, TSharedPtr<FStateTreeViewModel> InStateTreeViewModel);`
- L32 _public prototype_ `~SStateTreeViewRow();`
- L34 _public prototype_ `void RequestRename() const;`
- L57 _private prototype_ `TSharedRef<SWidget> MakeTasksWidget(const TSharedPtr<SScrollBox>& ViewBox);`
- L58 _private prototype_ `TSharedRef<SWidget> MakeConditionsWidget(const TSharedPtr<SScrollBox>& ViewBox);`
- L59 _private prototype_ `void MakeTransitionsWidget();`
- L60 _private prototype_ `TSharedRef<SWidget> MakeTransitionWidget(const EStateTreeTransitionTrigger Trigger, const FSlateBrush* Icon);`
- L61 _private prototype_ `TSharedRef<SWidget> MakeTransitionWidgetInternal(const EStateTreeTransitionTrigger Trigger, const FTransitionDescFilterOptions FilterOptions = {});`
- L62 _private prototype_ `void MakeFlagsWidget();`
- L64 _private prototype_ `FSlateColor GetTitleColor(const float Alpha = 1.0f, const float Lighten = 0.0f) const;`
- L65 _private prototype_ `FSlateColor GetActiveStateColor() const;`
- L66 _private prototype_ `FText GetStateDesc() const;`
- L67 _private prototype_ `FText GetStateIDDesc() const;`
- L69 _private prototype_ `FSlateColor GetSubTreeMarkerColor() const;`
- L70 _private prototype_ `EVisibility GetSubTreeVisibility() const;`
- L72 _private prototype_ `EVisibility GetConditionVisibility() const;`
- L73 _private prototype_ `EVisibility GetStateBreakpointVisibility() const;`
- L74 _private prototype_ `FText GetStateBreakpointTooltipText() const;`
- L76 _private prototype_ `const FSlateBrush* GetSelectorIcon() const;`
- L77 _private prototype_ `FText GetSelectorTooltip() const;`
- L78 _private prototype_ `FText GetStateTypeTooltip() const;`
- L80 _private prototype_ `const FStateTreeEditorNode* GetTaskNodeByID(FGuid TaskID) const;`
- L81 _private prototype_ `EVisibility GetTaskIconVisibility(FGuid TaskID) const;`
- L82 _private prototype_ `const FSlateBrush* GetTaskIcon(FGuid TaskID) const;`
- L83 _private prototype_ `FSlateColor GetTaskIconColor(FGuid TaskID) const;`
- L84 _private prototype_ `FText GetTaskDesc(FGuid TaskID, EStateTreeNodeFormatting Formatting) const;`
- L86 _private prototype_ `const FStateTreeEditorNode* GetConditionNodeByID(FGuid ConditionID) const;`
- L87 _private prototype_ `EVisibility GetConditionIconVisibility(FGuid ConditionID) const;`
- L88 _private prototype_ `const FSlateBrush* GetConditionIcon(FGuid ConditionID) const;`
- L89 _private prototype_ `FSlateColor GetConditionIconColor(FGuid ConditionID) const;`
- L90 _private prototype_ `FText GetConditionDesc(FGuid ConditionID, EStateTreeNodeFormatting Formatting) const;`
- L92 _private prototype_ `FText GetOperandText(const int32 ConditionIndex) const;`
- L93 _private prototype_ `FText GetOpenParens(const int32 ConditionIndex) const;`
- L94 _private prototype_ `FText GetCloseParens(const int32 ConditionIndex) const;`
- L96 _private prototype_ `EVisibility GetLinkedStateVisibility() const;`
- L97 _private prototype_ `FText GetLinkedStateDesc() const;`
- L99 _private prototype_ `bool GetStateWarnings(FText* OutText) const;`
- L100 _private prototype_ `EVisibility GetWarningsVisibility() const;`
- L101 _private prototype_ `FText GetWarningsTooltipText() const;`
- L103 _private prototype_ `EVisibility GetStateDescriptionVisibility() const;`
- L104 _private prototype_ `FText GetStateDescription() const;`
- L106 _private prototype_ `EVisibility GetTransitionDashVisibility() const;`
- L108 _private prototype_ `FText GetLinkTooltip(const FStateTreeStateLink& Link, const FGuid NodeID) const;`
- L109 _private prototype_ `FText GetTransitionsDesc(const EStateTreeTransitionTrigger Trigger, const FTransitionDescFilterOptions FilterOptions = {}) const;`
- L110 _private prototype_ `const FSlateBrush* GetTransitionsIcon(const EStateTreeTransitionTrigger Trigger) const;`
- L111 _private prototype_ `EVisibility GetTransitionsVisibility(const EStateTreeTransitionTrigger Trigger) const;`
- L112 _private prototype_ `EVisibility GetTransitionsBreakpointVisibility(const EStateTreeTransitionTrigger Trigger) const;`
- L114 _private prototype_ `bool HasParentTransitionForTrigger(const UStateTreeState& State, const EStateTreeTransitionTrigger Trigger) const;`
- L116 _private prototype_ `bool IsRootState() const;`
- L117 _private prototype_ `bool IsLeafState() const;`
- L118 _private prototype_ `bool IsStateSelected() const;`
- L120 _private prototype_ `bool HandleVerifyNodeLabelTextChanged(const FText& InText, FText& OutErrorMessage) const;`
- L121 _private prototype_ `void HandleNodeLabelTextCommitted(const FText& NewLabel, ETextCommit::Type CommitType) const;`
- L123 _private prototype_ `FReply HandleDragDetected(const FGeometry&, const FPointerEvent&) const;`
- L124 _private prototype_ `void HandleDragLeave(const FDragDropEvent& DragDropEvent) const;`
- L125 _private prototype_ `TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TWeakObjectPtr<UStateTreeState> TargetState) const;`
- L126 _private prototype_ `FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TWeakObjectPtr<UStateTreeState> TargetState) const;`
- L128 _private prototype_ `void HandleAssetChanged();`
- L129 _private prototype_ `void HandleStatesChanged(const TSet<UStateTreeState*>& ChangedStates, const FPropertyChangedEvent& PropertyChangedEvent);`
- L130 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L131 _private member_ `TWeakObjectPtr<UStateTreeState> WeakState;`
- L132 _private member_ `TWeakObjectPtr<UStateTreeEditorData> WeakEditorData;`
- L133 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameTextBlock;`
- L134 _private member_ `TSharedPtr<SBorder> FlagsContainer;`
- L135 _private member_ `TSharedPtr<SHorizontalBox> TransitionsContainer;`
- L137 _private member_ `FDelegateHandle AssetChangedHandle;`
- L138 _private member_ `FDelegateHandle StatesChangedHandle;`

#### enum `SStateTreeViewRow::ETransitionDescRequirement`  
`enum class ETransitionDescRequirement : uint8`  
_L37-42_
- L39 _public enumerator_ `Any`
- L40 _public enumerator_ `RequiredTrue`
- L41 _public enumerator_ `RequiredFalse`

#### struct `SStateTreeViewRow::FTransitionDescFilterOptions`  
`struct FTransitionDescFilterOptions`  
_L49-55_
- desc: Filtering options used to build the description of the transitions. The default setup includes only enabled transition, with or without breakpoints and requires exact trigger match (no partial mask)
- L51 _public function_ `FTransitionDescFilterOptions()`
- L52 _public member_ `ETransitionDescRequirement Enabled = ETransitionDescRequirement::RequiredTrue;`
- L53 _public member_ `ETransitionDescRequirement WithBreakpoint = ETransitionDescRequirement::Any;`
- L54 _public member_ `bool bUseMask = false;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StandaloneStateTreeEditorHost.h` (Private)


#### class `FStandaloneStateTreeEditorHost`  
`class FStandaloneStateTreeEditorHost : public IStateTreeEditorHost`  
_L9-29_
- inherits: `IStateTreeEditorHost`
- L12 _public prototype_ `void Init(const TWeakPtr<FStateTreeEditor>& InWeakStateTreeEditor);`
- L15 _public prototype_ `virtual UStateTree* GetStateTree() const override;`
- L16 _public prototype_ `virtual FSimpleMulticastDelegate& OnStateTreeChanged() override;`
- L17 _public prototype_ `virtual TSharedPtr<IDetailsView> GetAssetDetailsView() override;`
- L18 _public prototype_ `virtual TSharedPtr<IDetailsView> GetDetailsView() override;`
- L19 _public prototype_ `virtual TSharedPtr<UE::StateTreeEditor::FWorkspaceTabHost> GetTabHost() const override;`
- L20 _public prototype_ `virtual bool ShouldShowCompileButton() const override;`
- L21 _public prototype_ `virtual bool CanToolkitSpawnWorkspaceTab() const override;`
- L22 _public prototype_ `virtual FName GetCompilerLogName() const override;`
- L23 _public prototype_ `virtual FName GetCompilerTabName() const override;`
- L26 _protected member_ `TWeakPtr<FStateTreeEditor> WeakStateTreeEditor;`
- L27 _protected member_ `FSimpleMulticastDelegate OnStateTreeChangedDelegate;`
- L28 _protected member_ `TSharedPtr<UE::StateTreeEditor::FWorkspaceTabHost> TabHost;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/Layout/ExtendableNodeTypes.h` (Private)


#### enum `EExtendableNodeLOD`  
`enum class EExtendableNodeLOD : uint8`  
_L13-22_
- reflection: `UENUM(Experimental)`
- desc: Experimental. LOD / displayed info that an extendable node may support.
- L15 _public enumerator_ `Hidden` — View provides no context, if appropriate should not even give a placeholder
- L16 _public enumerator_ `Collapsed` — View provides no context, but visible as placeholder for when LOD changes
- L17 _public enumerator_ `Minimal` — View provides minimal context deemed needed
- L18 _public enumerator_ `Medium` — View is filtered, giving some but not all detail
- L19 _public enumerator_ `Full` — View would not reasonably show more info
- L20 _public enumerator_ `Unused UMETA(Hidden)` — Indicate node itself does not change based on LOD. Node may still accept LOD to pass onto children.
- L21 _public enumerator_ `Default UMETA(Hidden)` — Indicate no preference at API level, exact behavior implementation specific

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/Layout/SExtendableNode.h` (Private)


#### enum `UE::StateTree::Editor::StateCentricView::EExtensionLocation`  
`enum class EExtensionLocation : uint8`  
_L32-53_
- desc: Experimental. Location for a node extension.
- L34 _public enumerator_ `Bottom` — Below the node
- L35 _public enumerator_ `Left` — Left of node
- L36 _public enumerator_ `Right` — Right of node
- L37 _public enumerator_ `Top` — Above the node
- L39 _public enumerator_ `SubHeader` — Between main node header and body
- L40 _public enumerator_ `Footnote` — Below the main node body.
- L42 _public enumerator_ `Foreground` — Overlay in front of node.
- L43 _public enumerator_ `Background` — Overlay behind node.
- L49 _public enumerator_ `SplitBottom` — Below the node
- L50 _public enumerator_ `SplitLeft` — Left of node
- L51 _public enumerator_ `SplitRight` — Right of node
- L52 _public enumerator_ `SplitTop` — Above the node

#### enum `UE::StateTree::Editor::StateCentricView::EExtensionAddLocationBehavior`  
`enum class EExtensionAddLocationBehavior : uint8`  
_L57-66_
- desc: Experimental. How a newly added extension should behave if there are any special considerations.
- L59 _public enumerator_ `Default` — Dynamic default depending on what the given location is
- L61 _public enumerator_ `Wrap` — (Default) If current layout doesn't support location, wrap with a layout that does
- L62 _public enumerator_ `UseInnerLayout` — If current layout doesn't support location, use first inner layout that does or create one
- L64 _public enumerator_ `OverlayMainNode` — (Default) Add this overlay just for the main node, excluding extensions
- L65 _public enumerator_ `OverlayEntireNode` — Add this overlay for the entire node including extensions (IE: Entire widget).

#### struct `UE::StateTree::Editor::StateCentricView::FExtendableNodeConfig`  
`struct FExtendableNodeConfig`  
_L80-87_
- desc: Experimental. Config / params struct for extendable nodes. Persists as long as the widget exists. Delegates may re-execute deferred as LOD changes.
- L83 _public member_ `TArray<FAddExtensionDelegate> ExternalExtensions;` — External extensions for this node. Provided at construction and also gathered in SExtendableNode::Construct_GatherExtensionsFromExternalSubsystems.
- L86 _public member_ `EExtendableNodeLOD InitialLOD = EExtendableNodeLOD::Default;` — Initial LOD for this widget. Only used if non-default. If default wil get over-written to Construct time initial value.

#### struct `UE::StateTree::Editor::StateCentricView::FExtensionAddLayoutInfo`  
`struct FExtensionAddLayoutInfo`  
_L91-125_
- desc: Experimental. Struct holding layout info used when adding extensions
- L94 _public member_ `TOptional<FSizeParam> SizeParam;` — Sizing rules, auto = desired size / stretch = fill / strench content = desired size + fill
- L97 _public member_ `TAttribute<float> MinSize;` — Min size of this widget
- L100 _public member_ `TAttribute<float> MaxSize;` — Max size of this widget
- L103 _public member_ `TAttribute<FMargin> Padding;` — Padding of extension
- L106 _public member_ `TOptional<EHorizontalAlignment> HAlign;` — Horizontal Alignment
- L109 _public member_ `TOptional<EVerticalAlignment> VAlign;` — Vertical Alignment
- L115 _public member_ `int32 OverlayOffset = 0;` — Layer ID Offset applied to overlay. Used to get consistent widget overlap behavior across contiguous entries in stack boxes. Only applies to main node layout at the moment.
- L118 _public member_ `TAttribute<SSplitter::ESizeRule> SplitterSizeRule;` — Splitter Sizing Rule
- L121 _public member_ `TAttribute<float> SplitterValue;` — Splitter Ratio Value
- L124 _public member_ `TOptional<SSplitter::FOnSlotResized> SplitterOnSlotResized;` — Splitter On Resize Callback

#### struct `UE::StateTree::Editor::StateCentricView::FExtensionAddNodeParams`  
`struct FExtensionAddNodeParams`  
_L129-142_
- desc: Experimental. Struct holding params for adding a node extension widget. Supports argument chaining via `FScopedExtensionAddNodeParams`.
- L132 _public member_ `EExtensionLocation Location = EExtensionLocation::SubHeader;` — Location to add extension
- L135 _public member_ `EExtensionAddLocationBehavior AddLocationBehavior = EExtensionAddLocationBehavior::Default;` — Any specific behavior to consider when adding to vien location
- L138 _public member_ `int8 AddIndex = INDEX_NONE;` — If positive, index to add widget for given location (Ex: Left 0 will be 1st left widget)
- L141 _public member_ `FExtensionAddLayoutInfo LayoutInfo = {};` — Size info when adding extension

#### class `UE::StateTree::Editor::StateCentricView::SExtendableNode`  
`class SExtendableNode : public SCompoundWidget`  
_L165-326_
- inherits: `SCompoundWidget`
- desc: Experimental. Widget with a central Main Node (Header / Body), that can be extended horizontally / vertically / etc. Also provides conditional node & extension re-generation based on LOD. Simplified Node <Extension> Diagram: *---------------------------------*        *---------*-------------*---------* |           <Top>                 |        |         | <Top>       |         | *---------*-------------*---------*        |         *-------------*         | |         | Header      |         |        |         | Header      |         | |         *-------------*         |        |         *-------------*         | | <Left>  | <SubHeader> | <Right> |   or   | <Left>  | <SubHeader> | <Right> | |         *-------------*         |        |         *-------------*         | |         | Body        |         |        |         | Body        |         | *---------*-------------*---------*        |         *-------------*         | |           <Bottom>              |        |         | <Bottom>    |         | *---------------------------------*        *---------*-------------*---------* The corners are order dependant. See `EExtensionAddLocationBehavior` for details.
- L170 _public function_ `SLATE_BEGIN_ARGS(SExtendableNode) : _Config(FExtendableNodeConfig())`
- L186 _public prototype_ `void Construct(const FArguments& InArgs);`
- L189 _public prototype_ `void AddExtension(TSharedRef<SWidget> ExtensionWidget, const FExtensionAddNodeParams& ExtensionParams);` — Adds the given extension widget, constructing layout widgets as needed to support location
- L192 _public prototype_ `FScopedExtensionAddNodeParams AddExtension(TSharedRef<SWidget> ExtensionWidget);` — Add extension, supports argument chaining syntax to build params. Includes slate-style methods like AutoSize / FillSize / etc.
- L199 _public prototype_ `void SetMainNodeLayoutInfo(const FExtensionAddLayoutInfo& InLayoutInfo);` — Adding Layout incompatible extensions requires 2 slots. Main Node & Extension. This can be used to layout the main node slot. If not set for cardinal extensions will re-use the extension layout for the main node. Ex: Fill next to fill, desired size next to desired size. @TODO: Get rid of this reuse behavior. Or make it an option that is disabled by default / can be disabled. The automatic change something else is confusing.
- L202 _public prototype_ `[[nodiscard]] FScopedMainNodeLayoutInfo SetScopedMainNodeLayoutInfo();` — Same as above, but resets the value once return value goes out of scope
- L205 _public prototype_ `virtual void RegenerateWidgetForLOD(const EExtendableNodeLOD InLOD);` — Regenerates this widget for the given LOD, also updates current LOD.
- L208 _public prototype_ `EExtendableNodeLOD GetCurrentLOD() const;` — Get current LOD of this widget
- L214 _public prototype_ `virtual FName GetNodeName() const = 0;` — Get the unique name for this node, used as a key so that external systems can extend this node. If you need access to this key to extend then we suggest just hardcoding a copy locally.
- L219 _protected prototype_ `virtual void Construct_GatherExtensionsFromExternalSubsystems();` — One time gather of subsystem externally registered extensions for this node, cached into node config.
- L222 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD();` — One time init for anything persistent for the node across LODs, pre LOD generation.
- L228 _protected prototype_ `virtual void Construct_GenerateMainNode(const EExtendableNodeLOD InLOD);` — Generation widget header & body based on LOD. Also initally populates ChildSlot Should not consider extensions as those are transient between LODs & will be re-added if needed.
- L231 _protected prototype_ `virtual void Construct_GenerateBuiltInExtensions(const EExtendableNodeLOD InLOD);` — Generation of built in extensions based on LOD.
- L234 _protected prototype_ `virtual void Construct_GenerateExternalExtensions(const EExtendableNodeLOD InLOD);` — Generation of external extensions based on LOD.
- L237 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeHeader(const EExtendableNodeLOD InLOD);` — Builds header for this node based on LOD
- L240 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeBody(const EExtendableNodeLOD InLOD);` — Builds body for this node based on LOD
- L243 _protected prototype_ `void ResetCachedNodeAndLayout();` — Resets values stored during node construction, used to ensure a blank state when LOD changes
- L248 _protected member_ `FExtendableNodeConfig Config = {};` — Persistent config for this node, such as extension delegates.
- L251 _protected member_ `EExtendableNodeLOD CurrentLOD = EExtendableNodeLOD::Unused;` — Current LOD for this node.
- L254 _protected member_ `TSharedPtr<SWidget> NodeHeaderWidget = nullptr;` — Widget used for header, if any. Will not use SNullWidget.
- L257 _protected member_ `TSharedPtr<SWidget> NodeBodyWidget = nullptr;` — Widget used for body, if any. Will not use SNullWidget.
- L260 _protected member_ `TSharedPtr<SStackBox> MainNodeBox = nullptr;` — Container for header, subheader, and body.
- L263 _protected member_ `TSharedPtr<SStackBox> SubHeaderBox = nullptr;` — Widget for SubHeader extensions, nullptr till a single subheader extension exists.
- L266 _protected member_ `TSharedPtr<SStackBox> FootnoteBox = nullptr;` — Widget for Footnote extensions, nullptr till a single subheader extension exists.
- L269 _protected member_ `TAttribute<FMargin> NodeHeaderPadding;` — Padding for header
- L272 _protected member_ `TAttribute<FMargin> NodeBodyPadding;` — Padding for body
- L275 _protected member_ `TOptional<FSizeParam> NodeHeaderSizeParam;` — Sizing for header
- L278 _protected member_ `TOptional<FSizeParam> NodeBodySizeParam;` — Sizing for body
- L283 _private member_ `FExtensionAddLayoutInfo MainNodeLayoutInfo = {};` — This supports custom layout for the main node slot, used for main node on for first time new layouts.
- L286 _private member_ `TSharedPtr<SStackBox> CurrentLayoutBox = nullptr;` — Widget for current layout, nullptr till a horizontal / vertical extension is added
- L289 _private member_ `TSharedPtr<SSplitter> CurrentSplitterBox = nullptr;` — @TODO: Remove. Box holding current top level splitter.
- L292 _private member_ `TSharedPtr<SStackBox> InnerLayoutBox = nullptr;` — Widget for first inner layout, nullptr till an extension with an incomptible location is added
- L295 _private member_ `TSharedPtr<SOverlay> EntireNodeOverlay = nullptr;` — Widget for entire node overlays (includes extensions), nullptr till a foreground / background extension is added
- L298 _private member_ `TSharedPtr<SOverlay> MainNodeOverlay = nullptr;` — Widget for main node overlays, nullptr till a foreground / background extension is added
- L301 _private member_ `SStackBox::FSlot* MainNodeLayoutSlot = nullptr;` — Innermost layout slot holding main node or widget containing it. Remains constant once created no matter future extensions.
- L304 _private member_ `SSplitter::FSlot* MainNodeSplitterSlot = nullptr;` — @TODO: Remove. Innermost splitter slot holding main node or widget containing it.
- L307 _private member_ `SOverlay::FOverlaySlot* EntireNodeOverlaySlot = nullptr;` — Innermost overlay slot holding entire node Remains constant once created no matter future extensions.
- L310 _private member_ `int8 MainNodeCurrentLayoutIndex = INDEX_NONE;` — Index to main node or widget containing it in the current layout
- L313 _private member_ `int8 MainNodeInnerLayoutIndex = INDEX_NONE;` — Index to main node or widget containing it in the first inner layout
- L316 _private member_ `int8 EntireNodeLowestZOrder = INDEX_NONE;` — ZOrder for the furthest entire node background overlay (includes extensions). Used to continously insert behind the current background.
- L319 _private member_ `int8 MainNodeLowestZOrder = INDEX_NONE;` — ZOrder for the furthest main node background overlay. Used to continously insert behind the current background
- L323 _private member_ `TArray<TPair<FExtensionAddNodeParams, TSharedPtr<SWidget>>> AddedExtensions;` — Trace of all extensions added in order

#### struct `UE::StateTree::Editor::StateCentricView::FScopedExtensionAddNodeParams`  
`struct FScopedExtensionAddNodeParams : public FExtensionAddNodeParams`  
_L330-442_
- inherits: `FExtensionAddNodeParams`
- desc: Experimental. Scoped struct to hold add param methods & support function chaining syntax.
- L333 _public function_ `FScopedExtensionAddNodeParams(TSharedRef<SExtendableNode> InAddNode, TSharedPtr<SWidget> InExtensionWidget) : AddNode(InAddNode) , ExtensionWidget(InExtensionWidget)`
- L339 _public prototype_ `FScopedExtensionAddNodeParams() = delete;`
- L340 _public prototype_ `FScopedExtensionAddNodeParams(const FScopedExtensionAddNodeParams&) = delete;`
- L341 _public prototype_ `FScopedExtensionAddNodeParams& operator=(const FScopedExtensionAddNodeParams&) = delete;`
- L342 _public prototype_ `FScopedExtensionAddNodeParams(FScopedExtensionAddNodeParams&&) = default;`
- L343 _public prototype_ `FScopedExtensionAddNodeParams& operator=(FScopedExtensionAddNodeParams&&) = default;`
- L345 _public function_ `virtual ~FScopedExtensionAddNodeParams()`
- L355 _public function_ `FScopedExtensionAddNodeParams& SetLocation(const EExtensionLocation InLocation)`
- L361 _public function_ `FScopedExtensionAddNodeParams& SetAddLocationBehavior(const EExtensionAddLocationBehavior InAddLocationBehavior)`
- L367 _public function_ `FScopedExtensionAddNodeParams& SetAddIndex(const int8 InAddIndex)`
- L373 _public function_ `FScopedExtensionAddNodeParams& SetAutoSize()`
- L379 _public function_ `FScopedExtensionAddNodeParams& SetFillSize(TAttribute<float> InStretchCoefficient)`
- L385 _public function_ `FScopedExtensionAddNodeParams& SetFillContentSize(TAttribute<float> InStretchCoefficient, TAttribute<float> InShrinkStretchCoefficient = TAttribute<float>())`
- L391 _public function_ `FScopedExtensionAddNodeParams& SetMinSize(TAttribute<float> InMinSize)`
- L397 _public function_ `FScopedExtensionAddNodeParams& SetMaxSize(TAttribute<float> InMaxSize)`
- L403 _public function_ `FScopedExtensionAddNodeParams& SetPadding(TAttribute<FMargin> InPadding)`
- L409 _public function_ `FScopedExtensionAddNodeParams& SetHAlign(TOptional<EHorizontalAlignment> InHAlign)`
- L415 _public function_ `FScopedExtensionAddNodeParams& SetVAlign(TOptional<EVerticalAlignment> InVAlign)`
- L421 _public function_ `FScopedExtensionAddNodeParams& SetSplitterSizeRule(TAttribute<SSplitter::ESizeRule> InSplitterSizeRule)`
- L427 _public function_ `FScopedExtensionAddNodeParams& SetSplitterValue(TAttribute<float> InSplitterValue)`
- L433 _public function_ `FScopedExtensionAddNodeParams& SetSplitterOnSlotResized(TOptional<SSplitter::FOnSlotResized> InSplitterOnSlotResized)`
- L440 _private member_ `TSharedPtr<SExtendableNode> AddNode = nullptr;`
- L441 _private member_ `TSharedPtr<SWidget> ExtensionWidget = nullptr;`

#### struct `UE::StateTree::Editor::StateCentricView::FScopedMainNodeLayoutInfo`  
`struct FScopedMainNodeLayoutInfo`  
_L446-567_
- desc: Experimental. Scoped struct to toggle main node size info & support function chaining syntax.
- L453 _protected function_ `FScopedMainNodeLayoutInfo(TSharedRef<SExtendableNode> InAddNode) : AddNode(InAddNode) , bCanRestore(false)`
- L462 _public prototype_ `FScopedMainNodeLayoutInfo() = delete;`
- L463 _public function_ `FScopedMainNodeLayoutInfo(const FScopedMainNodeLayoutInfo& Other)`
- L468 _public function_ `FScopedMainNodeLayoutInfo& operator=(const FScopedMainNodeLayoutInfo& Other)`
- L478 _public prototype_ `FScopedMainNodeLayoutInfo(FScopedMainNodeLayoutInfo&& Other) = default;`
- L479 _public prototype_ `FScopedMainNodeLayoutInfo& operator=(FScopedMainNodeLayoutInfo&& Other) = default;`
- L481 _public function_ `virtual ~FScopedMainNodeLayoutInfo()`
- L491 _public function_ `FScopedMainNodeLayoutInfo& SetAutoSize()`
- L497 _public function_ `FScopedMainNodeLayoutInfo& SetFillSize(TAttribute<float> InStretchCoefficient)`
- L503 _public function_ `FScopedMainNodeLayoutInfo& SetFillContentSize(TAttribute<float> InStretchCoefficient, TAttribute<float> InShrinkStretchCoefficient = TAttribute<float>())`
- L509 _public function_ `FScopedMainNodeLayoutInfo& SetMinSize(TAttribute<float> InMinSize)`
- L515 _public function_ `FScopedMainNodeLayoutInfo& SetMaxSize(TAttribute<float> InMaxSize)`
- L521 _public function_ `FScopedMainNodeLayoutInfo& SetPadding(TAttribute<FMargin> InPadding)`
- L527 _public function_ `FScopedMainNodeLayoutInfo& SetHAlign(TOptional<EHorizontalAlignment> InHAlign)`
- L533 _public function_ `FScopedMainNodeLayoutInfo& SetVAlign(TOptional<EVerticalAlignment> InVAlign)`
- L539 _public function_ `FScopedMainNodeLayoutInfo& SetOverlayOffset(int32 InOverlayOffset)`
- L545 _public function_ `FScopedMainNodeLayoutInfo& SetSplitterSizeRule(TAttribute<SSplitter::ESizeRule> InSplitterSizeRule)`
- L551 _public function_ `FScopedMainNodeLayoutInfo& SetSplitterValue(TAttribute<float> InSplitterValue)`
- L557 _public function_ `FScopedMainNodeLayoutInfo& SetSplitterOnSlotResized(TOptional<SSplitter::FOnSlotResized> InSplitterOnSlotResized)`
- L564 _private member_ `TSharedPtr<SExtendableNode> AddNode = nullptr;`
- L565 _private member_ `FExtensionAddLayoutInfo PrevAddSizeInfo = FExtensionAddLayoutInfo();`
- L566 _private member_ `bool bCanRestore = false;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_EXTENDABLE_NODE_DEBUG 1`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace StateTree` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L20 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace StateTree` (scope `UE`)
- L27 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L27 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)
- L76 _typedef_ `using FAddExtensionDelegate = TDelegate<void(TSharedRef<SExtendableNode> , const EExtendableNodeLOD )>;` (scope `UE::StateTree::Editor::StateCentricView`) — Experimental. Callback node will fire when it is ready for generate external extensions If you need domain specific info beyond LOD to determine if an extension is needed. Please subclass & cast ExtendableNode with that info. @param ExtendableNode	- Node to extend by programatically calling `SExtendableNode::AddExtension` based on provided LOD, @param LOD				- Convenience param. LOD for the current node. Same as ExtendableNode's LOD.

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/StateCentricViewPerUserSettings.h` (Private)


#### struct `FStateCentricViewPerUserSetting`  
`struct FStateCentricViewPerUserSetting`  
_L24-148_
- reflection: `USTRUCT(Experimental, MinimalAPI)`
- desc: Experimental. Settings per user. This exists locally per user per schema. But also per state tree. Per state tree this is used to maintain consistent immediate behavior when clicking across states. Per user this is used to configure a default behavior when no per-state-tree setting has been set.
- L36 _private member_ `TOptional<EExtendableNodeLOD> ParentHireachyLOD = {};` — `UPROPERTY(EditAnywhere, Category="Layout", Config, meta = (ValidEnumValues = "Collapsed, Minimal, Full"))` — Amount of info to show for every parent state in the hierachy.
- L40 _private member_ `TOptional<EExtendableNodeLOD> InTransitionViewLOD = {};` — `UPROPERTY(EditAnywhere, Category = "Layout", Config, meta = (ValidEnumValues = "Minimal, Full"))` — Amount of info to show for incoming transitions to this state.
- L44 _private member_ `TOptional<EExtendableNodeLOD> OutTransitionLOD = {};` — `UPROPERTY(EditAnywhere, Category = "Layout", Config, meta = (ValidEnumValues = "Minimal, Full"))` — Amount of info to show for outgoing transitions from this state.
- L48 _private member_ `TOptional<uint32> NumParentsShown = {};` — `UPROPERTY(EditAnywhere, Category="Layout", Config)` — Number of parents to show if they exist.
- L52 _private member_ `TOptional<bool> bHideParentTransitions = {};` — `UPROPERTY(EditAnywhere, Category = "Layout", Config)` — True if we should hide parents in transition view.
- L56 _public function_ `TOptional<EExtendableNodeLOD> GetParentHireachyLOD() const`
- L61 _public function_ `TOptional<EExtendableNodeLOD> GetInTransitionLOD() const`
- L66 _public function_ `TOptional<EExtendableNodeLOD> GetOutTransitionLOD() const`
- L71 _public function_ `TOptional<uint32> GetNumParentsShown() const`
- L76 _public function_ `TOptional<bool> GetHideParentTransitions() const`
- L81 _public function_ `void SetParentHireachyLOD(TOptional<EExtendableNodeLOD> InLOD)`
- L92 _public function_ `void SetInTransitionLOD(TOptional<EExtendableNodeLOD> InLOD)`
- L103 _public function_ `void SetOutTransitionLOD(TOptional<EExtendableNodeLOD> InLOD)`
- L114 _public function_ `void SetNumParentsShown(TOptional<uint32> InNumParentShown)`
- L123 _public function_ `void SetHideParentTransitions(TOptional<bool> bInHideParentTransitions)`
- L135 _public member_ `FOnStateCentricViewLOD_Changed OnParentHireachyLOD_Changed;` — Callback whenever default parent hierarchy LOD changed.
- L138 _public member_ `FOnStateCentricViewLOD_Changed OnInTransitionViewLOD_Changed;` — Callback whenever the LOD for 'In' transition view has changed.
- L141 _public member_ `FOnStateCentricViewLOD_Changed OnOutTransitionViewLOD_Changed;` — Callback whenever the LOD for 'Out' transition view has changed.
- L144 _public member_ `FOnStateCentricViewIntValue_Changed OnNumParentsShownChanged;` — Callback whenever num parents shown has changed.
- L147 _public member_ `FOnStateCentricViewBoolValue_Changed OnHideParentTransitionsChanged;` — Callback whenever hide parent transitions has changed.

#### class `UStateCentricViewPerUserSettings`  
`class UStateCentricViewPerUserSettings : public UDeveloperSettings`  
_L156-204_
- reflection: `UCLASS(Experimental, MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- desc: Experimental. Settings for the state centric view per schema per user per schema. These settings provide defaults to reset to along with defaults for newly opened statetrees.
- L162 _public prototype_ `UStateCentricViewPerUserSettings();`
- L164 _public function_ `static const UStateCentricViewPerUserSettings& Get()`
- L169 _public function_ `static UStateCentricViewPerUserSettings& GetMutable()`
- L174 _public prototype_ `static const FStateCentricViewPerUserSetting& GetSchemaSettingsDefaultFallback(const FStateTreeViewModel* ViewModel);`
- L176 _public function_ `static const FStateCentricViewPerUserSetting& GetSchemaSettingsDefaultFallback(const TSubclassOf<UStateTreeSchema> InSchema)`
- L190 _public member_ `TMap<TSoftClassPtr<UStateTreeSchema>, FStateCentricViewPerUserSetting> PerSchemaSettings;` — `UPROPERTY(EditAnywhere, Category="Appearance", Config, meta = (AllowAbstract = "true", EditCondition = "StateTreeEditorModule.StateCentricViewSettings.IsStateCentricViewEnabled", EditConditionHides))` — Per schema settings. Defined per schema since we have no need for an editor schema to be defined.
- L196 _protected prototype_ `virtual FText GetSectionText() const override;`
- L197 _protected prototype_ `virtual FText GetSectionDescription() const override;`
- L202 _protected prototype_ `virtual FName GetCategoryName() const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateCentricViewLOD_Changed, TOptional<EExtendableNodeLOD> );`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateCentricViewLOD_Changed, TOptional<EExtendableNodeLOD> );`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateCentricViewIntValue_Changed, TOptional<uint32> );`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateCentricViewIntValue_Changed, TOptional<uint32> );`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateCentricViewBoolValue_Changed, TOptional<bool> );`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateCentricViewBoolValue_Changed, TOptional<bool> );`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/StateCentricViewSettings.h` (Private)


#### struct `FStateCentricViewPerSchemaSetting`  
`struct FStateCentricViewPerSchemaSetting`  
_L20-74_
- reflection: `USTRUCT(Experimental, MinimalAPI)`
- desc: Experimental. Settings per schema. Mainly focused on styling & layout.
- L31 _public member_ `bool bEnableHierarchyDrivenColors = false;` — `UPROPERTY(EditAnywhere, Category="Style")` — True if state centric view colors based on hireachy rather than User Defined colors @TODO: Also this should be part of base ST.
- L42 _public member_ `bool bJustifyCentralViewTransitions = false;` — `UPROPERTY(EditAnywhere, Category = "Layout")` — True if central / leafmost view should have transitions justified instead of top aligned
- L46 _public member_ `bool bWordWrapTransitionStates = true;` — `UPROPERTY(EditAnywhere, Category = "Layout")` — True if states in transitions should have word wrap on
- L50 _public member_ `bool bWordWrapChildStates = false;` — `UPROPERTY(EditAnywhere, Category = "Layout")` — True if child states should have word wrap on
- L54 _public member_ `bool bEnableFullParentDetailExpansion = true;` — `UPROPERTY(EditAnywhere, Category="Layout")` — True if state centric view allows for full detail expansion of parents, else max expansion is entry conditions
- L58 _public member_ `bool bEnableOutlinerRightOfStateCentric = false;` — `UPROPERTY(EditAnywhere, Category="Layout")` — At the moment we only allow state centric to be toggled left or right of the outliner.
- L62 _public member_ `bool bEnableFillOnTransitionNodes = true;` — `UPROPERTY(EditAnywhere, Category="Layout")` — True if transition nodes have fill based width. Enabled by default to avoid confusing amounts of random negative space.
- L66 _public member_ `float TransitionNodeBridgeWidth = 48.0f;` — `UPROPERTY(EditAnywhere, Category = "Layout")` — Width for bridge connecting transitions nodes to center nodes
- L73 _public member_ `uint32 MaxNumParentsToShow = 4;` — `UPROPERTY(EditAnywhere, Category="Layout", meta=(UIMin="1", UIMax="50"))` — Max number of parents we allow users to show. At the moment we do not encourage changing this as showing too many parents can detract from the intended workflow of focusing on the central state and jumping around if needed.

#### class `UStateCentricViewSettings`  
`class UStateCentricViewSettings : public UDeveloperSettings`  
_L84-138_
- reflection: `UCLASS(Experimental, MinimalAPI, config = EditorSettings, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: Experimental. May be removed at any time and API may change at any time. Toggle via: StateTree.Editor.Experimental.EnableStateCentricView Settings for the state centric view per schema. As state centric is early in dev, there are many toggles.
- L90 _public prototype_ `UStateCentricViewSettings();`
- L92 _public function_ `static const UStateCentricViewSettings& Get()`
- L97 _public function_ `static UStateCentricViewSettings& GetMutable()`
- L102 _public prototype_ `static const FStateCentricViewPerSchemaSetting& GetSchemaSettingsDefaultFallback(const FStateTreeViewModel* ViewModel);`
- L104 _public function_ `static const FStateCentricViewPerSchemaSetting& GetSchemaSettingsDefaultFallback(const TSubclassOf<UStateTreeSchema> InSchema)`
- L118 _public member_ `TMap<TSoftClassPtr<UStateTreeSchema>, FStateCentricViewPerSchemaSetting> PerSchemaSettings;` — `UPROPERTY(EditAnywhere, Category="Appearance", Config, meta = (AllowAbstract = "true", EditCondition = "StateTreeEditorModule.StateCentricViewSettings.IsStateCentricViewEnabled", EditConditionHides))` — Per schema settings. Defined per schema since we have no need for an editor schema to be defined.
- L124 _public prototype_ `static bool IsStateCentricViewEnabled();` — `UFUNCTION()` — Static version of state centric enabled check, exists to hide based on edit condition
- L130 _protected prototype_ `virtual FText GetSectionText() const override;`
- L131 _protected prototype_ `virtual FText GetSectionDescription() const override;`
- L136 _protected prototype_ `virtual FName GetCategoryName() const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SFakeTransitionInfoNode.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::SFakeTransitionInfoNode`  
`class SFakeTransitionInfoNode : public SStateTreeExtendableNode`  
_L24-58_
- inherits: `SStateTreeExtendableNode`
- desc: Experimental. Node used to show some info in transition area that isn't a real transition.
- L30 _protected prototype_ `virtual EStateTransitionDirection GetTransitionDirection() const = 0;` — Get if we are intended to be shown at in or out transtions.
- L33 _protected prototype_ `virtual const UStateTreeState* GetFakeTranstionInfoState() const = 0;` — Get State to show for this node.
- L36 _protected prototype_ `virtual const FSlateBrush* GetFakeTranstionInfoBrush() const = 0;` — Get Icon to use in header for this node.
- L39 _protected prototype_ `virtual FText GetFakeTranstionInfoText() const = 0;` — Get Text to show for this node
- L42 _protected function_ `virtual FText GetFakeTranstionInfoToolTipText() const` — Get Text to show for this node
- L50 _protected prototype_ `virtual void Construct_GenerateBuiltInExtensions(const EExtendableNodeLOD InLOD) override;`
- L51 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeHeader(const EExtendableNodeLOD InLOD) override;`
- L52 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeBody(const EExtendableNodeLOD InLOD) override;`
- L57 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateBrush;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace StateTree` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L17 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SImplicitRootTransitionNode.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::SImplicitRootTransitionNode`  
`class SImplicitRootTransitionNode : public SFakeTransitionInfoNode`  
_L16-39_
- inherits: `SFakeTransitionInfoNode`
- desc: Experimental. Node used to show the implicit transtion to root on complete.
- L21 _public member_ `static const FName NodeID;`
- L26 _public prototype_ `virtual FName GetNodeName() const override;`
- L32 _protected prototype_ `virtual EStateTransitionDirection GetTransitionDirection() const override;`
- L33 _protected prototype_ `virtual const UStateTreeState* GetFakeTranstionInfoState() const override;`
- L34 _protected prototype_ `virtual const FSlateBrush* GetFakeTranstionInfoBrush() const override;`
- L35 _protected prototype_ `virtual FText GetFakeTranstionInfoText() const override;`
- L36 _protected prototype_ `virtual FText GetFakeTranstionInfoToolTipText() const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StateTree` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L9 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SMainStateTransitionExtensionNode.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::SMainStateTransitionExtensionNode`  
`class SMainStateTransitionExtensionNode : public SStateTreeExtendableNode`  
_L21-82_
- inherits: `SStateTreeExtendableNode`
- desc: Experimental. Node used as an extension for In / Out transitions on the main state.
- L30 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`
- L31 _protected prototype_ `virtual void Construct_GenerateBuiltInExtensions(const EExtendableNodeLOD InLOD) override;`
- L32 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeHeader(const EExtendableNodeLOD InLOD) override;`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeBody(const EExtendableNodeLOD InLOD) override;`
- L39 _protected member_ `EStateTransitionDirection TransitionDirection = EStateTransitionDirection::Out;` — If we are showing in / out transitions. Init in child classes.
- L44 _private prototype_ `FReply HandleOnCollapseClicked();` — Callback for collapse button
- L47 _private prototype_ `FReply HandleOnAddTransitionClicked();` — Callback for top right button
- L50 _private prototype_ `FReply HandleTransitionAreaRightClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Callback for right-click anywhere in the body - opens an 'Add Transition' context menu.
- L53 _private prototype_ `TSharedRef<SWidget> BuildTransitionStatePicker();` — Builds the state-picker widget embedded in the 'Add Transition' context menu.
- L56 _private prototype_ `void HandleOnTransitionViewLOD_SettingsChanged(TOptional<EExtendableNodeLOD> InLOD);` — Callback for when LOD settings change
- L59 _private prototype_ `void HandleOnTransitionsNumChanged(const UStateTreeState* , const TSet<FGuid>& );` — Callback for transtions added / removed
- L62 _private prototype_ `FSlateColor GetAddTransitionColor() const;` — Minor UI / UX callbacks
- L63 _private prototype_ `FSlateColor GetHideButtonColor() const;`
- L65 _private prototype_ `void UpdateHideButtonAttributes();`
- L66 _private prototype_ `FMargin GetHideButtonPadding() const;`
- L67 _private prototype_ `EHorizontalAlignment GetHideButtonAlignment() const;`
- L68 _private prototype_ `TOptional<FSlateRenderTransform> GetHideButtonRenderTransform() const;`
- L72 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateOutlineBrush;`
- L73 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateBackgroundBrush;`
- L74 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateHeaderBackgroundBrush;`
- L76 _private member_ `TSharedPtr<SButton> AddTransitionButton;`
- L77 _private member_ `TSharedPtr<SButton> HideButton;`
- L79 _private member_ `FMargin HideButtonPadding = FMargin();`
- L80 _private member_ `EHorizontalAlignment HideButtonAlignment = HAlign_Fill;`
- L81 _private member_ `FSlateRenderTransform HideButtonRenderTransform = FSlateRenderTransform();`

#### class `UE::StateTree::Editor::StateCentricView::SMainStateInTransitionExtensionNode`  
`class SMainStateInTransitionExtensionNode : public SMainStateTransitionExtensionNode`  
_L88-107_
- inherits: `SMainStateTransitionExtensionNode`
- desc: Experimental. Specialization of SMainStateTransitionExtensionNode for 'In' transitions
- L93 _public member_ `static const FName NodeID;`
- L98 _public prototype_ `virtual FName GetNodeName() const override;`
- L104 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`

#### class `UE::StateTree::Editor::StateCentricView::SMainStateOutTransitionExtensionNode`  
`class SMainStateOutTransitionExtensionNode : public SMainStateTransitionExtensionNode`  
_L113-132_
- inherits: `SMainStateTransitionExtensionNode`
- desc: Experimental. Specialization of SMainStateTransitionExtensionNode for 'Out' transitions
- L118 _public member_ `static const FName NodeID;`
- L123 _public prototype_ `virtual FName GetNodeName() const override;`
- L129 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTree` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L14 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SParentSelectionNode.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::SParentSelectionNode`  
`class SParentSelectionNode : public SFakeTransitionInfoNode`  
_L16-39_
- inherits: `SFakeTransitionInfoNode`
- desc: Experimental. Node used to show a single state's parent selection behavior
- L21 _public member_ `static const FName NodeID;`
- L26 _public prototype_ `virtual FName GetNodeName() const override;`
- L32 _protected prototype_ `virtual EStateTransitionDirection GetTransitionDirection() const override;`
- L33 _protected prototype_ `virtual const UStateTreeState* GetFakeTranstionInfoState() const override;`
- L34 _protected prototype_ `virtual const FSlateBrush* GetFakeTranstionInfoBrush() const override;`
- L35 _protected prototype_ `virtual FText GetFakeTranstionInfoText() const override;`
- L36 _protected prototype_ `virtual FText GetFakeTranstionInfoToolTipText() const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StateTree` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L9 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SParentStateExtensionNode.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::SParentStateExtensionNode`  
`class SParentStateExtensionNode : public SStateTreeExtendableNode`  
_L20-57_
- inherits: `SStateTreeExtendableNode`
- desc: Experimental. Node used an an extension to show parent states
- L25 _public member_ `static const FName NodeID;`
- L30 _public prototype_ `virtual FName GetNodeName() const override;`
- L36 _protected prototype_ `virtual void Construct_GenerateBuiltInExtensions(const EExtendableNodeLOD InLOD) override;`
- L37 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeHeader(const EExtendableNodeLOD InLOD) override;`
- L38 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeBody(const EExtendableNodeLOD InLOD) override;`
- L44 _private prototype_ `FReply HandleOnChangeLOD_Clicked();` — Callback for top right button
- L47 _private prototype_ `FSlateColor GetExpandButtonColor() const;` — Minor UI / UX callbacks
- L51 _private member_ `TArray<TSharedPtr<FDeferredCleanupSlateBrush>> ChildStateBrushes;`
- L52 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateOutlineBrush;`
- L53 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateHeaderBackgroundBrush;`
- L54 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateFootnoteBackgroundBrush;`
- L56 _private member_ `TSharedPtr<SButton> ChangeLOD_Button;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StateTree` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L13 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SParentStateTransitionExtensionNode.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::SParentStateTransitionExtensionNode`  
`class SParentStateTransitionExtensionNode : public SStateTreeExtendableNode`  
_L21-62_
- inherits: `SStateTreeExtendableNode`
- desc: Experimental. Node used as an extension for In / Out transitions on the main state.
- L31 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`
- L32 _protected prototype_ `virtual void Construct_GenerateBuiltInExtensions(const EExtendableNodeLOD InLOD) override;`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeHeader(const EExtendableNodeLOD InLOD) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeBody(const EExtendableNodeLOD InLOD) override;`
- L40 _protected member_ `EStateTransitionDirection TransitionDirection = EStateTransitionDirection::Out;` — If we are showing in / out transitions. Init in child classes.
- L45 _private prototype_ `FReply HandleOnAddTransitionClicked();` — Callback for top right button
- L48 _private prototype_ `void HandleOnTransitionViewLOD_SettingsChanged(TOptional<EExtendableNodeLOD> InLOD);` — Callback for when LOD settings change
- L51 _private prototype_ `void HandleOnTransitionsNumChanged(const UStateTreeState* , const TSet<FGuid>& );` — Callback for transtions added / removed
- L54 _private prototype_ `FSlateColor GetAddTransitionColor() const;` — Minor UI / UX callbacks
- L58 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateOutlineBrush;`
- L59 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateHeaderBackgroundMutedBrush;`
- L61 _private member_ `TSharedPtr<SButton> AddTransitionButton;`

#### class `UE::StateTree::Editor::StateCentricView::SParentStateInTransitionExtensionNode`  
`class SParentStateInTransitionExtensionNode : public SParentStateTransitionExtensionNode`  
_L68-87_
- inherits: `SParentStateTransitionExtensionNode`
- desc: Experimental. Specialization of SParentStateTransitionExtensionNode for 'In' transitions
- L73 _public member_ `static const FName NodeID;`
- L78 _public prototype_ `virtual FName GetNodeName() const override;`
- L84 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`

#### class `UE::StateTree::Editor::StateCentricView::SParentStateOutTransitionExtensionNode`  
`class SParentStateOutTransitionExtensionNode : public SParentStateTransitionExtensionNode`  
_L93-112_
- inherits: `SParentStateTransitionExtensionNode`
- desc: Experimental. Specialization of SParentStateTransitionExtensionNode for 'Out' transitions
- L98 _public member_ `static const FName NodeID;`
- L103 _public prototype_ `virtual FName GetNodeName() const override;`
- L109 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTree` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L14 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SStateCentricToolbar.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::SStateCentricToolbar`  
`class SStateCentricToolbar : public SCompoundWidget`  
_L22-42_
- inherits: `SCompoundWidget`
- desc: Experimental. Toolbar to set options for state centric Current plan is placeholder to test out workflows. Long term state centric will need to inject into different toolbars.
- L25 _public function_ `SLATE_USER_ARGS(SStateCentricToolbar)`
- L26 _public prototype_ `SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs, TSharedRef<FStateTreeViewModel> InViewModel);`
- L33 _private member_ `TSharedPtr<FStateTreeViewModel> ViewModel = nullptr;` — ViewModel for this ST
- L36 _private member_ `uint32 CachedNumParentsShown = 0;` — Cached number of parents set to be shown for this state tree
- L40 _private prototype_ `void HandleNumParentsSliderChanged(uint32 NewValue);`
- L41 _private prototype_ `uint32 HandleNumParentsSliderValue() const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StateTree` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L13 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SStateCentricViewMainStateNode.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::SStateCentricViewMainStateNode`  
`class SStateCentricViewMainStateNode : public SStateTreeExtendableNode`  
_L18-66_
- inherits: `SStateTreeExtendableNode`
- desc: Experimental. Node for the main selected state in state centric view
- L23 _public member_ `static const FName NodeID;`
- L29 _public prototype_ `virtual FName GetNodeName() const override;`
- L35 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`
- L36 _protected prototype_ `virtual void Construct_GenerateBuiltInExtensions(const EExtendableNodeLOD InLOD) override;`
- L37 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeHeader(const EExtendableNodeLOD InLOD) override;`
- L38 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeBody(const EExtendableNodeLOD InLOD) override;`
- L44 _protected prototype_ `void HandleOnSelectionChanged(const TArray<TWeakObjectPtr<UStateTreeState>>& SelectedStates);` — Callback whenever selected state changes.
- L47 _protected prototype_ `void HandleOnParentHireachyLOD_Changed(TOptional<EExtendableNodeLOD> InLOD);` — Callback whenever parent state exapnsion changes
- L50 _protected prototype_ `void HandleOnNumParentsShownChanged(TOptional<uint32> InNumParentShown);` — Callback whenever num parents shown changes
- L53 _protected prototype_ `void HandleOnStateAdded(UStateTreeState* , UStateTreeState* );` — Callback whenever states added
- L56 _protected prototype_ `void HandleOnStateRemoved(const TSet<UStateTreeState*>& );` — Callback whenever states removed
- L59 _protected prototype_ `void HandleOnStateMoved(const TSet<UStateTreeState*>& , const TSet<UStateTreeState*>& );` — Callback whenever states moved
- L63 _private member_ `TArray<TSharedPtr<FDeferredCleanupSlateBrush>> ChildStateBrushes;`
- L64 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateOutlineBrush;`
- L65 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> StateHeaderBackgroundBrush;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace StateTree` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L11 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/SStateTreeExtendableNode.h` (Private)


#### enum `UE::StateTree::Editor::StateCentricView::EStateTransitionDirection`  
`enum class EStateTransitionDirection : uint8`  
_L29-33_
- desc: Experimental. If a state transition is in / out relative to main central state
- L31 _public enumerator_ `In` — Transition into central state
- L32 _public enumerator_ `Out` — Transition out of central state

#### class `UE::StateTree::Editor::StateCentricView::SStateTreeExtendableNode`  
`class SStateTreeExtendableNode : public SExtendableNode`  
_L60-90_
- inherits: `SExtendableNode`
- desc: Experimental. Extendable node StateTree specialization. Guarantees access to a ST ViewModel & gathers external extensions on a per-schema basis. Also gets relevant view state during construction;
- L73 _public prototype_ `void Construct(const SExtendableNode::FArguments& InArgs , TSharedRef<FStateTreeViewModel> InViewModel , TNotNull<UStateTreeState*> InViewState);` — @param InViewModel	ViewModel for the StateTree @param InViewState	State this node should try to provide a view for.
- L80 _protected prototype_ `virtual void Construct_GatherExtensionsFromExternalSubsystems() override;`
- L86 _protected member_ `TSharedPtr<FStateTreeViewModel> ViewModel = nullptr;` — ViewModel for the ST this node interacts with
- L89 _protected member_ `TWeakObjectPtr<UStateTreeState> ViewState = nullptr;` — View State. May be a different state at different parts of state centric view. Ex: Parent state for parent widgets.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace StateTree` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L17 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace StateTree` (scope `UE`)
- L22 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L22 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)
- L49 _typedef_ `using FAddStateTreeExtensionDelegate = TDelegate<void(TSharedRef<SExtendableNode> , const EExtendableNodeLOD , TSharedRef<FStateTreeViewModel> , TNotNull<UStateTreeState*> )>;` (scope `UE::StateTree::Editor::StateCentricView`) — Experimental. ST specific callback for extensions. These extensions will only get added if the schema they are registered against matches the schema for our current ViewModel. Note: Impl detail. We will internally wrap the extension delegate given into one that conforms to the default extension interface. @param ExtendableNode	- Node to extend by programatically calling `SExtendableNode::AddExtension` based on provided LOD, @param LOD				- Convenience param. LOD for the current node. Same as ExtendableNode's LOD. @param ViewModel			- ViewModel for the current state tree @param ViewState			- State that this extension should specialize view around, may be different than the central state (IE: If showing a parent state). @TODO: Currently not used.

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/STransitionNode.h` (Private)


#### class `UE::StateTree::Editor::StateCentricView::STransitionNode`  
`class STransitionNode : public SStateTreeExtendableNode`  
_L27-84_
- inherits: `SStateTreeExtendableNode`
- desc: Experimental. Node used to show a single state transition
- L34 _public prototype_ `void Construct(const SExtendableNode::FArguments& InArgs , TSharedRef<FStateTreeViewModel> InViewModel , TNotNull<UStateTreeState*> InViewState , TNotNull<FStateTreeTransition*> InTransition);`
- L42 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`
- L43 _protected prototype_ `virtual void Construct_GenerateBuiltInExtensions(const EExtendableNodeLOD InLOD) override;`
- L44 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeHeader(const EExtendableNodeLOD InLOD) override;`
- L45 _protected prototype_ `virtual TSharedRef<SWidget> Construct_GenerateNodeBody(const EExtendableNodeLOD InLOD) override;`
- L51 _protected prototype_ `void RefreshNodeDelayed();` — Method to refresh this node delayed
- L54 _protected prototype_ `void HandleOnTransitionModified(const UStateTreeState* OwningState, const FGuid& InTransitionID);` — Callback for transtion modified
- L57 _protected prototype_ `void HandleOnHideParentTransitionsChanged(TOptional<bool> );` — Callback for hide parents modified
- L60 _protected prototype_ `FReply HandleOnDeleteTransitionClicked();` — Callback for delete transition button
- L63 _protected prototype_ `FSlateColor GetDeleteTransitionColor() const;` — Minor UI / UX callbacks
- L71 _protected member_ `FGuid TransitionID = FGuid();` — Transition we represent, guaranteed to exist as long as this node does via value change callbacks @TODO: Make that guarantee true.
- L74 _protected member_ `EStateTransitionDirection TransitionDirection = EStateTransitionDirection::Out;` — If we are showing in / out transitions. Init in child classes.
- L78 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> TransitionParentStateBrush;`
- L79 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> TransitionStateBrush;`
- L80 _private member_ `TSharedPtr<FDeferredCleanupSlateBrush> TransitionStateBackgroundBrush;`
- L82 _private member_ `TSharedPtr<IStructureDetailsView> TransitionDetailsView;`
- L83 _private member_ `TSharedPtr<SButton> DeleteTransitionButton;`

#### class `UE::StateTree::Editor::StateCentricView::SInTransitionNode`  
`class SInTransitionNode : public STransitionNode`  
_L90-109_
- inherits: `STransitionNode`
- desc: Experimental. Specialization of STransitionNode for 'In' transitions
- L95 _public member_ `static const FName NodeID;`
- L100 _public prototype_ `virtual FName GetNodeName() const override;`
- L106 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`

#### class `UE::StateTree::Editor::StateCentricView::SOutTransitionNode`  
`class SOutTransitionNode : public STransitionNode`  
_L115-134_
- inherits: `STransitionNode`
- desc: Experimental. Specialization of STransitionNode for 'Out' transitions
- L120 _public member_ `static const FName NodeID;`
- L125 _public prototype_ `virtual FName GetNodeName() const override;`
- L131 _protected prototype_ `virtual void Construct_InitializeNodePersistentPreLOD() override;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace StateTree` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L20 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/View/StateCentricViewUtils.h` (Private)


#### struct `UE::StateTree::Editor::StateCentricView::FStateCentricViewUtils`  
`struct FStateCentricViewUtils`  
_L29-76_
- desc: Experimental. General Utils for state centric view widget creation. Currrently contains widget creation that is reused at different places. We prefer duplicated logic be here so it can be re-used in arbitray places if needed. All widget generation related methods must accept a LOD.
- L32 _public prototype_ `static TSharedRef<SWidget> GenerateTransitionsViewWidget(const EExtendableNodeLOD LOD , TSharedRef<FStateTreeViewModel> ViewModel , TNotNull<UStateTreeState*> ViewState , const EStateTransitionDirection TransitionDirection);` — Build a view of transitions for given LOD / state / direction
- L38 _public prototype_ `static TSharedRef<SButton> GenerateGotoStateButton(const EExtendableNodeLOD LOD , TSharedRef<FStateTreeViewModel> ViewModel , TNotNull<const UStateTreeState*> ViewState);` — Build a transparent button that jumps to given state
- L43 _public prototype_ `static void AddChildStateFootnoteExtensions(const EExtendableNodeLOD InLOD , TNotNull<SStateTreeExtendableNode*> InSourceNode , TArray<TSharedPtr<FDeferredCleanupSlateBrush>>& OutSlateBrushResouces);` — Adds list of child state extensions at footnote for Full LOD
- L48 _public prototype_ `static TOptional<EExtendableNodeLOD> GetDesiredParentLOD(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<UStateTreeState*> ParentState);` — Gets desired parent LOD based on various settings
- L51 _public prototype_ `static uint32 GetNumParentsToShow(TSharedRef<FStateTreeViewModel> ViewModel);` — Gets number of parents to show
- L54 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateHalfTopOutline(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);` — Helpers to get brushes based on if state is parent / leaf w/ appropriate colors
- L55 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateHalfTopOutlineMuted(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L56 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateHalfTopOutlineCollapsed(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L57 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateOutline(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L58 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateOutlineMuted(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L60 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateHeaderBackground(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State, TOptional<FVector2f> ImageSize = {});`
- L61 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateHeaderBackgroundMuted(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L62 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateHeaderBackgroundCollapsed(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L64 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateBackgroundMutedOutlined(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L65 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateBackgroundCollapsedOutlined(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L67 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateFootnoteBackground(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L69 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateSubnodeBackgroundOutlined(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L70 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateSubnodeBackground(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L71 _public prototype_ `[[nodiscard]] static TSharedPtr<FDeferredCleanupSlateBrush> MakeStateCollapsedBackground(TSharedRef<FStateTreeViewModel> ViewModel, TNotNull<const UStateTreeState*> State);`
- L74 _public prototype_ `static const FSlateBrush* GetSubNodeBackground();` — Helpers to get standard state centric brushes
- L75 _public prototype_ `static const FSlateBrush* GetSubNodeFootnoteBackground();`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace StateTree` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L20 _namespace_ `namespace StateCentricView` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/ViewModel/StateCentricViewEditorDataExtension.h` (Private)


#### class `UStateCentricViewEditorDataExtension`  
`class UStateCentricViewEditorDataExtension : public UStateTreeEditorDataExtension`  
_L21-83_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UStateTreeEditorDataExtension`
- desc: Experimental. Extension to store temporary editor data for state centric view & view interactions
- L27 _public prototype_ `UStateCentricViewEditorDataExtension();`
- L31 _public member_ `FStateCentricViewPerUserSetting PerStateTreeUserSettings;` — `UPROPERTY(EditAnywhere, Category = "Appearance", meta = (EditCondition = "StateTreeEditorModule.StateCentricViewSettings.IsStateCentricViewEnabled", EditConditionHides))` — User settings for this specific state tree. Ensures consistent behavior when opening different states in this state tree.
- L42 _public member_ `TMap<FGuid, EExtendableNodeLOD> LastUserSetParentStateLOD;` — `UPROPERTY(Transient)` — LOD to show this parent state at. We use this to ensure the view remains consistent when clicking between different states with the same parent & when clicking back & forth. @TODO: This is a map, but it would be more idiomatic for it to exist as an editor data extension on a state. Currently that doesn't exist. See if ST owners are interested in that being added. Ex: This map becomes ugly when a state is deleted, with correct ownership this is not an issue.
- L45 _public member_ `bool bShouldStoreParentExpansion = true;` — `UPROPERTY(Transient)`
- L49 _public member_ `float LeftSpacerSplitterValue = 0.025f;`
- L50 _public member_ `float InTransitionSplitterValue = 0.1875f;`
- L51 _public member_ `float MainNodeSplitterValue = 0.375f;`
- L52 _public member_ `float OutTransitionSplitterValue = 0.4375f;`
- L53 _public member_ `float RightSpacerSplitterValue = 0.025f;`
- L55 _public member_ `SSplitter::ESizeRule InTransitionSplitterSizeRule;`
- L56 _public member_ `SSplitter::ESizeRule OutTransitionSplitterSizeRule;`
- L60 _public prototype_ `void ResetSplitters();`
- L62 _public prototype_ `float HandleGetLeftSpacerSplitterValue() const;`
- L63 _public prototype_ `float HandleGetInTransitionSplitterValue() const;`
- L64 _public prototype_ `float HandleGetMainNodeSplitterValue() const;`
- L65 _public prototype_ `float HandleGetOutTransitionSplitterValue() const;`
- L66 _public prototype_ `float HandleGetRightSpacerSplitterValue() const;`
- L68 _public prototype_ `SSplitter::ESizeRule GetInTransitionSplitterSizeRule() const;`
- L69 _public prototype_ `SSplitter::ESizeRule GetOutTransitionSplitterSizeRule() const;`
- L71 _public prototype_ `void HandleOnLeftSpacerSplitterResized(float InSize);`
- L72 _public prototype_ `void HandleOnInTransitionSplitterResized(float InSize);`
- L73 _public prototype_ `void HandleOnMainNodeSplitterResized(float InSize);`
- L74 _public prototype_ `void HandleOnOutTransitionSplitterResized(float InSize);`
- L75 _public prototype_ `void HandleOnRightSpacerSplitterResized(float InSize);`
- L79 _protected function_ `UStateTreeEditorData* GetStateTreeEditorData() const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeDescriptionHelpers.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace StateTree` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L18 _prototype_ `FText GetStateLinkDesc(const UStateTreeEditorData* EditorData, const FStateTreeStateLink& Link, EStateTreeNodeFormatting Formatting, bool bShowStatePath = false);` (scope `UE::StateTree::Editor`)
- L19 _prototype_ `const FSlateBrush* GetStateLinkIcon(const UStateTreeEditorData* EditorData, const FStateTreeStateLink& Link);` (scope `UE::StateTree::Editor`)
- L20 _prototype_ `FSlateColor GetStateLinkColor(const UStateTreeEditorData* EditorData, const FStateTreeStateLink& Link);` (scope `UE::StateTree::Editor`)
- L22 _prototype_ `FText GetTransitionDesc(const UStateTreeEditorData* EditorData, const FStateTreeTransition& Transition, EStateTreeNodeFormatting Formatting, bool bShowStatePath = false);` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeDiffControl.h` (Private)


#### class `UE::StateTree::Diff::FDiffWidgets`  
`class FDiffWidgets`  
_L26-37_
- L29 _public prototype_ `explicit FDiffWidgets(const UStateTree* InStateTree);`
- L32 _public prototype_ `TSharedRef<SStateTreeView> GetStateTreeWidget() const;` — Returns actual widget that is used to display trees
- L35 _private member_ `TSharedPtr<SStateTreeView> StateTreeTreeView;`
- L36 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`

#### class `UE::StateTree::Diff::FDiffControl`  
`class FDiffControl : public TSharedFromThis<FDiffControl>`  
_L41-84_
- inherits: `TSharedFromThis<FDiffControl>`
- L44 _public prototype_ `FDiffControl() = delete;`
- L45 _public prototype_ `FDiffControl(const FDiffControl& Other) = delete;`
- L46 _public prototype_ `FDiffControl(const FDiffControl&& Other) = delete;`
- L47 _public prototype_ `FDiffControl(const UStateTree* InOldObject, const UStateTree* InNewObject, const FOnDiffEntryFocused& InSelectionCallback);`
- L48 _public prototype_ `~FDiffControl();`
- L50 _public prototype_ `TSharedRef<SStateTreeView> GetDetailsWidget(const UStateTree* Object) const;`
- L52 _public function_ `FOnStateDiffEntryFocused& GetOnStateDiffEntryFocused()`
- L57 _public prototype_ `void GenerateTreeEntries(TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>& OutDifferences);`
- L58 _public function_ `TConstArrayView<FSingleDiffEntry> GetBindingDifferences() const`
- L64 _protected member_ `static FText RightRevision;`
- L65 _protected prototype_ `static TSharedRef<SWidget> GenerateSingleEntryWidget(FSingleDiffEntry DiffEntry, FText ObjectName);`
- L67 _protected prototype_ `TSharedRef<SStateTreeView> InsertObject(TNotNull<const UStateTree*> StateTree);`
- L69 _protected prototype_ `void OnSelectDiffEntry(const FSingleDiffEntry StateDiff);`
- L71 _protected member_ `FOnDiffEntryFocused OnDiffEntryFocused;`
- L72 _protected member_ `FOnStateDiffEntryFocused OnStateDiffEntryFocused;`
- L74 _protected member_ `TArray<TStrongObjectPtr<const UStateTree>> DisplayedAssets;`
- L81 _protected member_ `TMap<FObjectKey, FStateTreeTreeDiffPairs> StateTreeDifferences;`
- L82 _protected member_ `TArray<FSingleDiffEntry> BindingDiffs;`
- L83 _protected member_ `TMap<FObjectKey, FDiffWidgets> StateTreeDiffWidgets;`

#### struct `UE::StateTree::Diff::FDiffControl::FStateTreeTreeDiffPairs`  
`struct FStateTreeTreeDiffPairs`  
_L76-80_
- L78 _public member_ `TSharedPtr<FAsyncDiff> Left;`
- L79 _public member_ `TSharedPtr<FAsyncDiff> Right;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace StateTree` (scope `UE`)
- L22 _namespace_ `namespace Diff` (scope `UE::StateTree`)
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateDiffEntryFocused, const FSingleDiffEntry&) class FDiffControl : public TSharedFromThis<FDiffControl> { public: FDiffControl() = delete; FDiffControl(const FDiffControl& Other) = delete; FDiffControl(const FDiffControl&& Other) = delete; FDiffControl(const UStateTree* InOldObject, const UStateTree* InNewObject, const FOnDiffEntryFocused& InSelectionCallback); ~FDiffControl(); TSharedRef<SStateTreeView> GetDetailsWidget(const UStateTree* Object) const; FOnStateDiffEntryFocused& GetOnStateDiffEntryFocused() { return OnStateDiffEntryFocused; }; void GenerateTreeEntries(TArray<TSharedPtr<FBlueprintDifferenceTreeEntry>>& OutDifferences); TConstArrayView<FSingleDiffEntry> GetBindingDifferences() const { return BindingDiffs; } protected: static FText RightRevision; static TSharedRef<SWidget> GenerateSingleEntryWidget(FSingleDiffEntry DiffEntry, FText ObjectName); TSharedRef<SStateTreeView> InsertObject(TNotNull<const UStateTree*> StateTree); void OnSelectDiffEntry(const FSingleDiffEntry StateDiff); FOnDiffEntryFocused OnDiffEntryFocused; FOnStateDiffEntryFocused OnStateDiffEntryFocused; TArray<TStrongObjectPtr<const UStateTree>> DisplayedAssets; struct FStateTreeTreeDiffPairs { TSharedPtr<FAsyncDiff> Left;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeDiffHelper.h` (Private)


#### enum `UE::StateTree::Diff::EStateDiffType`  
`enum class EStateDiffType : uint8`  
_L13-33_
- L15 _public enumerator_ `Invalid`
- L17 _public enumerator_ `Identical`
- L19 _public enumerator_ `StateAddedToA`
- L20 _public enumerator_ `StateAddedToB`
- L21 _public enumerator_ `StateChanged`
- L23 _public enumerator_ `StateEnabled`
- L24 _public enumerator_ `StateDisabled`
- L26 _public enumerator_ `StateMoved`
- L28 _public enumerator_ `StateTreePropertiesChanged`
- L30 _public enumerator_ `BindingAddedToA`
- L31 _public enumerator_ `BindingAddedToB`
- L32 _public enumerator_ `BindingChanged`

#### struct `UE::StateTree::Diff::FStateSoftPath`  
`struct FStateSoftPath`  
_L35-105_
- L37 _public prototype_ `FStateSoftPath() = default;`
- L38 _public prototype_ `explicit FStateSoftPath(TNotNull<const UStateTreeState*> InState);`
- L40 _public prototype_ `UStateTreeState* ResolvePath(TNotNull<const UStateTree*> StateTree) const;`
- L41 _public prototype_ `UStateTreeState* ResolvePath(TNotNull<const UStateTreeEditorData*> EditorData) const;`
- L42 _public prototype_ `FString ToDisplayName(bool Short = false) const;`
- L49 _public function_ `bool IsSubStateMatch(const FStateSoftPath& BaseStatePath) const` — Indicates whether a given path is a base path of the current path. @param BaseStatePath The path to look for as a base common path @return Whether the path has the provided path as base path or not
- L67 _public function_ `bool operator==(FStateSoftPath const& RHS) const`
- L72 _public function_ `bool operator!=(FStateSoftPath const& RHS) const`
- L77 _public function_ `explicit operator bool() const`
- L83 _private prototype_ `void PostOrderChain(const UStateTreeState* CurBackwardsState);`
- L104 _private member_ `TArray<FChainElement> StateChain;`

#### struct `UE::StateTree::Diff::FStateSoftPath::FChainElement`  
`struct FChainElement`  
_L85-103_
- L87 _public member_ `FName StateName;`
- L88 _public member_ `FString DisplayString;`
- L89 _public member_ `FGuid ID;`
- L91 _public prototype_ `FChainElement() = default;`
- L92 _public prototype_ `explicit FChainElement(const UStateTreeState* State);`
- L94 _public function_ `bool operator==(FChainElement const& RHS) const`
- L99 _public function_ `bool operator!=(FChainElement const& RHS) const`

#### struct `UE::StateTree::Diff::FSingleDiffEntry`  
`struct FSingleDiffEntry`  
_L107-131_
- L109 _public function_ `FSingleDiffEntry(const FStateSoftPath& InIdentifier, const FStateSoftPath& InSecondaryIdentifier, const EStateDiffType InDiffType, const FPropertySoftPath& InBindingPath) : Identifier(InIdentifier) , SecondaryIdentifier(InSecondaryIdentifier) , BindingPath(InBindingPath) , DiffType(InDiffType)`
- L117 _public function_ `FSingleDiffEntry(const FStateSoftPath& InIdentifier, const FStateSoftPath& InSecondaryIdentifier, const EStateDiffType InDiffType) : FSingleDiffEntry(InIdentifier, InSecondaryIdentifier, InDiffType, FPropertySoftPath())`
- L122 _public function_ `FSingleDiffEntry(const FStateSoftPath& InIdentifier, const EStateDiffType InDiffType) : FSingleDiffEntry(InIdentifier, FStateSoftPath(), InDiffType)`
- L127 _public member_ `FStateSoftPath Identifier;`
- L128 _public member_ `FStateSoftPath SecondaryIdentifier;`
- L129 _public member_ `FPropertySoftPath BindingPath;`
- L130 _public member_ `EStateDiffType DiffType = EStateDiffType::Invalid;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace StateTree` (scope `UE`)
- L10 _namespace_ `namespace Diff` (scope `UE::StateTree`)
- L133 _prototype_ `FText GetStateTreeDiffMessage(const FSingleDiffEntry& Difference, FText ObjectName, bool bShort = false);` (scope `UE::StateTree::Diff`)
- L135 _prototype_ `FLinearColor GetStateTreeDiffMessageColor(const FSingleDiffEntry& Difference);` (scope `UE::StateTree::Diff`)
- L137 _prototype_ `FText GetStateDiffMessage(const FSingleObjectDiffEntry& Difference, FText PropertyName);` (scope `UE::StateTree::Diff`)
- L139 _prototype_ `FLinearColor GetStateDiffMessageColor(const FSingleObjectDiffEntry& Difference);` (scope `UE::StateTree::Diff`)
- L141 _prototype_ `bool IsBindingDiff(EStateDiffType DiffType);` (scope `UE::StateTree::Diff`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeDragDrop.h` (Private)


#### class `FStateTreeSelectedDragDrop`  
`class FStateTreeSelectedDragDrop : public FDecoratedDragDropOp`  
_L11-54_
- inherits: `FDecoratedDragDropOp`
- L14 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FActionTreeViewDragDrop, FDecoratedDragDropOp);`
- L16 _public function_ `static TSharedRef<FStateTreeSelectedDragDrop> New(TSharedPtr<FStateTreeViewModel> InViewModel)`
- L25 _public function_ `static TSharedRef<FStateTreeSelectedDragDrop> New(TSharedPtr<FStateTreeViewModel> InViewModel, FGuid NodeID, TWeakObjectPtr<UStateTreeState> OriginState, bool bIsControlKeyDown)`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L39 _public function_ `void SetCanDrop(const bool bState)`
- L44 _public function_ `bool IsDraggingNode() const`
- L49 _public member_ `TSharedPtr<FStateTreeViewModel> ViewModel;`
- L50 _public member_ `TWeakObjectPtr<UStateTreeState> OriginState;`
- L51 _public member_ `FGuid NodeID;`
- L52 _public member_ `bool bIsControlKeyDown = false;`
- L53 _public member_ `bool bCanDrop = false;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeEditor.h` (Private)


#### class `FStateTreeEditor`  
`class FStateTreeEditor : public IStateTreeEditor, public FSelfRegisteringEditorUndoClient, public FGCObject`  
_L24-109_
- inherits: `IStateTreeEditor,FSelfRegisteringEditorUndoClient,FGCObject`
- L30 _public member_ `static const FName LayoutLeftStackId;`
- L31 _public member_ `static const FName LayoutBottomMiddleStackId;`
- L32 _public member_ `static const FName CompilerLogListingName;`
- L33 _public member_ `static const FName CompilerResultsTabId;`
- L35 _public function_ `FStateTreeEditor() : TreeViewCommandList(new FUICommandList())`
- L37 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L38 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L40 _public prototype_ `void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UStateTree* StateTree);`
- L43 _public prototype_ `virtual void PostInitAssetEditor() override;`
- L44 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L45 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L46 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L50 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L51 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L52 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L53 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L54 _public prototype_ `virtual void OnClose() override;`
- L57 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L58 _public function_ `virtual FString GetReferencerName() const override`
- L65 _protected prototype_ `virtual void SaveAsset_Execute() override;` — Called when "Save" is clicked for this asset
- L69 _private prototype_ `TSharedRef<SDockTab> SpawnTab_StateTreeView(const FSpawnTabArgs& Args);` — Spawns the tab with the update graph inside
- L70 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SelectionDetails(const FSpawnTabArgs& Args);`
- L71 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetDetails(const FSpawnTabArgs& Args);`
- L72 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CompilerResults(const FSpawnTabArgs& Args) const;`
- L74 _private prototype_ `void RegisterMenu();`
- L75 _private prototype_ `void RegisterToolbar();`
- L78 _private member_ `TObjectPtr<UStateTree> StateTree = nullptr;` — State Tree being edited
- L81 _private member_ `TSharedRef<FUICommandList> TreeViewCommandList;` — The command list used by the tree view. Stored here, so that other windows (e.g. debugger) can add commands to it, even if the tree view is not spawned yet.
- L84 _private member_ `TSharedPtr<IDetailsView> SelectionDetailsView;` — Selection Property View
- L87 _private member_ `TSharedPtr<IDetailsView> AssetDetailsView;` — Asset Property View
- L90 _private member_ `TSharedPtr<class SStateTreeView> StateTreeView;` — Tree View
- L93 _private member_ `TSharedPtr<class SStateTreeOutliner> StateTreeOutliner;` — Tree Outliner
- L96 _private member_ `TSharedPtr<SWidget> CompilerResults;` — Compiler Results log
- L97 _private member_ `TSharedPtr<IMessageLogListing> CompilerResultsListing;`
- L99 _private member_ `TSharedPtr<FStateTreeViewModel> StateTreeViewModel;`
- L101 _private member_ `TSharedPtr<FStateTreeEditorModeUILayer> ModeUILayer;`
- L102 _private member_ `TSharedPtr<IToolkit> HostedToolkit;`
- L103 _private member_ `TSharedPtr<FWorkspaceItem> WorkspaceMenuCategory;`
- L104 _private member_ `TSharedPtr<FStandaloneStateTreeEditorHost> EditorHost;`
- L106 _private member_ `static const FName StateTreeViewTabId;`
- L107 _private member_ `static const FName SelectionDetailsTabId;`
- L108 _private member_ `static const FName AssetDetailsTabId;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace StateTree` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L21 _externvar_ `extern bool GbDisplayItemIds;` (scope `UE::StateTree::Editor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeEditorCommands.h` (Private)


#### class `FStateTreeEditorCommands`  
`class FStateTreeEditorCommands : public TCommands<FStateTreeEditorCommands>`  
_L11-42_
- inherits: `TCommands<FStateTreeEditorCommands>`
- desc: StateTree editor command set.
- L14 _public prototype_ `FStateTreeEditorCommands();`
- L17 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> overrides
- L19 _public member_ `TSharedPtr<FUICommandInfo> Compile;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_Never;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_SuccessOnly;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> SaveOnCompile_Always;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> LogCompilationResult;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> LogDependencies;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> AddSiblingState;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> AddChildState;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> RenameState;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> CutStates;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> CopyStates;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> PasteStatesAsSiblings;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> PasteStatesAsChildren;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> PasteNodesToSelectedStates;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> DuplicateStates;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> DeleteStates;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> EnableStates;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> EnableOnEnterStateBreakpoint;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> EnableOnExitStateBreakpoint;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeEditorDataClipboardHelpers.h` (Private)


#### struct `UE::StateTreeEditor::FClipboardEditorData`  
`struct FClipboardEditorData`  
_L29-90_
- reflection: `USTRUCT()`
- L33 _public prototype_ `void ProcessBuffer(const UScriptStruct* InTargetType, TNotNull<UStateTreeEditorData*> InEditorData, TNotNull<UObject*> InOwner);`
- L35 _public function_ `bool IsValid() const`
- L40 _public prototype_ `void Append(TNotNull<const UStateTreeEditorData*> InStateTree, TConstArrayView<FStateTreeEditorNode> InEditorNodes);`
- L41 _public prototype_ `void Append(TNotNull<const UStateTreeEditorData*> InStateTree, TConstArrayView<FStateTreeTransition> InTransitions);`
- L42 _public prototype_ `void Append(TNotNull<const UStateTreeEditorData*> InStateTree, TConstArrayView<const FPropertyBindingBinding*> InBindingPtrs);`
- L44 _public prototype_ `void Reset();`
- L46 _public function_ `TArrayView<FStateTreeEditorNode> GetEditorNodesInBuffer()`
- L51 _public function_ `TConstArrayView<FStateTreeEditorNode> GetEditorNodesInBuffer() const`
- L56 _public function_ `TArrayView<FStateTreeTransition> GetTransitionsInBuffer()`
- L61 _public function_ `TConstArrayView<FStateTreeTransition> GetTransitionsInBuffer() const`
- L66 _public function_ `TArrayView<FStateTreePropertyPathBinding> GetBindingsInBuffer()`
- L71 _public function_ `TConstArrayView<FStateTreePropertyPathBinding> GetBindingsInBuffer() const`
- L77 _private prototype_ `void CollectBindingsForEditorNodes(TNotNull<const UStateTreeEditorData*> InStateTree, TConstArrayView<FStateTreeEditorNode> InEditorNodes);`
- L78 _private prototype_ `void CollectBindingsForTransitions(TNotNull<const UStateTreeEditorData*> InStateTree, TConstArrayView<FStateTreeTransition> InEditorNodes);`
- L81 _private member_ `TArray<FStateTreeEditorNode> EditorNodesBuffer;` — `UPROPERTY()`
- L84 _private member_ `TArray<FStateTreeTransition> TransitionsBuffer;` — `UPROPERTY()`
- L87 _private member_ `TArray<FStateTreePropertyPathBinding> BindingsBuffer;` — `UPROPERTY()`
- L89 _private member_ `bool bBufferProcessed = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StateTreeEditor` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace StateTreeEditor` (scope `UE`)
- L21 _prototype_ `void ExportTextAsClipboardEditorData(const FClipboardEditorData& InClipboardEditorData);` (scope `UE::StateTreeEditor`)
- L23 _prototype_ `bool ImportTextAsClipboardEditorData(const UScriptStruct* InTargetType, TNotNull<UStateTreeEditorData*> InTargetTree, TNotNull<UObject*> InOwner, FClipboardEditorData& OutClipboardEditorData, bool bProcessBuffer = true);` (scope `UE::StateTreeEditor`)
- L26 _prototype_ `void AddErrorNotification(const FText& InText, float InExpiredDuration = 5.f);` (scope `UE::StateTreeEditor`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeEditorUILayer.h` (Private)


#### class `FStateTreeEditorModeUILayer`  
`class FStateTreeEditorModeUILayer : public FAssetEditorModeUILayer`  
_L9-20_
- inherits: `FAssetEditorModeUILayer`
- L12 _public prototype_ `FStateTreeEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L13 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L14 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L15 _public prototype_ `virtual TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`
- L17 _public prototype_ `void SetModeMenuCategory(const TSharedPtr<FWorkspaceItem>& MenuCategoryIn);`
- L19 _protected member_ `TSharedPtr<FWorkspaceItem> MenuCategory;`

#### class `UStateTreeEditorUISubsystem`  
`class UStateTreeEditorUISubsystem : public UAssetEditorUISubsystem`  
_L23-31_
- reflection: `UCLASS()`
- inherits: `UAssetEditorUISubsystem`
- L28 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L29 _public prototype_ `virtual void Deinitialize() override;`
- L30 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeEditorUserSettings.h` (Private)


#### enum `EStateTreeEditorUserSettingsNodeType`  
`enum class EStateTreeEditorUserSettingsNodeType : uint8`  
_L9-20_
- reflection: `UENUM(meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L11 _public enumerator_ `None = 0 << 0 UMETA(Hidden)`
- L12 _public enumerator_ `Condition = 1 << 0`
- L13 _public enumerator_ `Task = 1 << 1`
- L14 _public enumerator_ `Transition = 1 << 2`
- L15 _public enumerator_ `Flag = 1 << 3`
- L16 _public enumerator_ `Parameter = 1 << 4`
- L17 _public enumerator_ `Utility = 1 << 5`
- L18 _public enumerator_ `Evaluator = 1 << 6`
- L19 _public enumerator_ `All = (Condition | Task | Transition | Flag | Parameter | Utility | Evaluator) UMETA(Hidden)`

#### class `UStateTreeEditorUserSettings`  
`class UStateTreeEditorUserSettings : public UDeveloperSettings`  
_L25-87_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, DisplayName="StateTree User Settings")`
- inherits: `UDeveloperSettings`
- desc: User settings for the StateTree editor
- L30 _public prototype_ `UStateTreeEditorUserSettings() = default;`
- L32 _public function_ `EStateTreeEditorUserSettingsNodeType GetStatesViewDisplayNodeType() const`
- L36 _public prototype_ `void SetStatesViewDisplayNodeType(EStateTreeEditorUserSettingsNodeType Value);`
- L38 _public function_ `EStateTreeEditorUserSettingsNodeType GetDetailsViewDisplayCount() const`
- L42 _public prototype_ `void SetDetailsViewDisplayCount(EStateTreeEditorUserSettingsNodeType Value);`
- L44 _public function_ `float GetStatesViewStateRowHeight() const`
- L49 _public function_ `float GetStatesViewNodeRowHeight() const`
- L54 _public function_ `bool GetDisplayMigrationToRewindDebuggerWarning() const`
- L59 _public prototype_ `void SetDisplayMigrationToRewindDebuggerWarning(bool bNewValue);`
- L62 _public member_ `FSimpleMulticastDelegate OnSettingsChanged;` — Broadcast when a setting changes.
- L65 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L70 _private member_ `EStateTreeEditorUserSettingsNodeType StatesViewDisplayNodeType = EStateTreeEditorUserSettingsNodeType::All;` — `UPROPERTY(config, EditAnywhere, Category = "State View", meta = (DisplayName = "Display Node"))` — Which additional node type to display in the States View.
- L74 _private member_ `float StatesViewStateRowHeight = 32.0f;` — `UPROPERTY(config, EditAnywhere, Category = "State View", meta = (DisplayName = "State Height", ClampMin = 8.0f))` — Height of a state in the States View.
- L78 _private member_ `float StatesViewNodeRowHeight = 16.0f;` — `UPROPERTY(config, EditAnywhere, Category = "State View", meta = (DisplayName = "Node Height", ClampMin = 8.0f))` — Height of a node in the States View.
- L82 _private member_ `EStateTreeEditorUserSettingsNodeType DetailsViewDisplayCount = EStateTreeEditorUserSettingsNodeType::All;` — `UPROPERTY(config, EditAnywhere, Category = "Details View", meta = (DisplayName = "Display Count"))` — True if we should show the count for that node in details.
- L86 _private member_ `bool bDisplayMigrationToRewindDebuggerWarning = true;` — `UPROPERTY(config)` — Display the debugger migration warning.

#### Free symbols / members of external scopes

- L21 _prototype_ `ENUM_CLASS_FLAGS(EStateTreeEditorUserSettingsNodeType);`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeGraphSchema.h` (Private)


#### class `UE::StateTree::Editor::UEdGraphSchema_StateTree`  
`class UEdGraphSchema_StateTree : public UEdGraphSchema_K2`  
_L12-15_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema_K2`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StateTree` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeObjectHash.h` (Private)


#### class `FStateTreeObjectCRC32`  
`class FStateTreeObjectCRC32 : public FArchiveObjectCrc32`  
_L14-19_
- inherits: `FArchiveObjectCrc32`
- desc: Archive based object hashing to be used with StateTree data calculation. If a property has "IncludeInHash" meta tag, any of its child properties will be included in the hash. Editor only since it relies on meta data.
- L18 _public prototype_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override;`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreePropertyHelpers.h` (Private)


#### struct `FStateTreeEditPropertyPath`  
`struct FStateTreeEditPropertyPath`  
_L217-267_
- desc: Helper class to deal with relative property paths in PostEditChangeChainProperty().
- L236 _public prototype_ `FStateTreeEditPropertyPath() = default;`
- L239 _public prototype_ `explicit FStateTreeEditPropertyPath(const UStruct* BaseStruct, FStringView InPath);` — Makes property path relative to BaseStruct. Checks if the path is not part of the type.
- L242 _public prototype_ `explicit FStateTreeEditPropertyPath(const FPropertyChangedChainEvent& PropertyChangedEvent);` — Makes property path from property change event.
- L245 _public prototype_ `explicit FStateTreeEditPropertyPath(const FEditPropertyChain& PropertyChain);` — Makes property path from property chain.
- L251 _public prototype_ `void MakeEditPropertyChain(FEditPropertyChain& OutPropertyChain) const;` — Makes property chain from property path. Copy Ctor of FEditPropertyChain is implicitly deleted so a conversion operator is not available here
- L254 _public prototype_ `bool ContainsPath(const FStateTreeEditPropertyPath& InPath) const;` — @return true if the property path contains specified path.
- L257 _public prototype_ `bool IsPathExact(const FStateTreeEditPropertyPath& InPath) const;` — @return true if the property path is exactly the specified path.
- L260 _public function_ `int32 GetPropertyArrayIndex(const FStateTreeEditPropertyPath& InPath) const` — @return array index at specified property, or INDEX_NONE, if the property is not array or property not found.
- L266 _private member_ `TArray<FStateTreeEditPropertySegment> Path;`

#### struct `FStateTreeEditPropertyPath::FStateTreeEditPropertySegment`  
`struct FStateTreeEditPropertySegment`  
_L220-233_
- L222 _public prototype_ `FStateTreeEditPropertySegment() = default;`
- L223 _public function_ `FStateTreeEditPropertySegment(FProperty* InProperty, const FName InPropertyName, const int32 InArrayIndex = INDEX_NONE) : Property(InProperty) , PropertyName(InPropertyName) , ArrayIndex(InArrayIndex)`
- L230 _public member_ `FProperty* Property = nullptr;`
- L231 _public member_ `FName PropertyName = FName();`
- L232 _public member_ `int32 ArrayIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "StateTreeEditor"`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace StateTree` (scope `UE`)
- L19 _namespace_ `namespace PropertyHelpers` (scope `UE::StateTree`)
- L25 _prototype_ `void DispatchPostEditToNodes(UObject& Owner, FPropertyChangedChainEvent& PropertyChangedEvent, UStateTreeEditorData& EditorData);` (scope `UE::StateTree::PropertyHelpers`) — Dispatches PostEditChange to all FState Assumes property chain head is member property of Owner.
- L30 _prototype_ `void ModifyStateInPreAndPostEdit( const FText& TransactionDescription, TNotNull<UStateTreeState*> State, TNotNull<UStateTreeEditorData*> EditorData, FStringView RelativeNodePath, TFunctionRef<void(TNotNull<UStateTreeState*>, TNotNull<UStateTreeEditorData*>, const FStateTreeEditPropertyPath&)> Func, int32 ArrayIndex = INDEX_NONE, EPropertyChangeType::Type ChangeType = EPropertyChangeType::ValueSet);` (scope `UE::StateTree::PropertyHelpers`) — Modify a StateTreeState in PreEdit and PostEdit callbacks in a transaction.
- L40 _prototype_ `FGuid MakeDeterministicID(const UObject& Owner, const FString& PropertyPath, const uint64 Seed);` (scope `UE::StateTree::PropertyHelpers`) — Makes deterministic ID from the owners property path, a property path (or any string), and a seed value (e.g. array index).
- L44 _function_ `template<typename T> bool IsScriptStruct(const TSharedPtr<IPropertyHandle>& PropertyHandle)` (scope `UE::StateTree::PropertyHelpers`) — @return true if the property handle points to struct property of specified type.
- L63 _prototype_ `bool HasOptionalMetadata(const FProperty& Property);` (scope `UE::StateTree::PropertyHelpers`) — @return true if provided Property contains "Optional" metadata
- L71 _function_ `template<typename T> FPropertyAccess::Result GetStructValue(const TSharedPtr<const IPropertyHandle>& ValueProperty, T& OutValue)` (scope `UE::StateTree::PropertyHelpers`) — Gets a struct value from property handle, checks type before access. Expects T is struct. @param ValueProperty Handle to property where value is got from. @return Requested value as optional, in case of multiple values the optional is unset.
- L122 _function_ `template<typename T> const T* GetStructPtr(const TSharedPtr<const IPropertyHandle>& ValueProperty)` (scope `UE::StateTree::PropertyHelpers`) — Returns const pointer to struct container in the property. @param ValueProperty Handle to property where value is got from. @return Pointer to the struct, or nullptr if type does not match or multiple values.
- L152 _function_ `template<typename T> FPropertyAccess::Result SetStructValue(const TSharedPtr<IPropertyHandle>& ValueProperty, const T& NewValue, EPropertyValueSetFlags::Type Flags = 0)` (scope `UE::StateTree::PropertyHelpers`) — Sets a struct property to specific value, checks type before access. Expects T is struct. @param ValueProperty Handle to property where value is got from. @return Requested value as optional, in case of multiple values the optional is unset.

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/TextStyleDecorator.h` (Private)


#### class `FTextStyleDecorator`  
`class FTextStyleDecorator : public ITextDecorator`  
_L12-42_
- inherits: `ITextDecorator`
- desc: Simple decorator for SRichTextBlock, which allows to map simple/shorthand tags to specific style names. The decorator also strips away any tags, e.g. in case the initial text came with nested tags.
- L16 _public prototype_ `static TSharedRef<FTextStyleDecorator> Create(FString InName, const FTextBlockStyle& TextStyle);`
- L18 _public prototype_ `virtual bool Supports(const FTextRunParseResults& RunInfo, const FString& Text) const override;`
- L20 _public prototype_ `virtual TSharedRef<ISlateRun> Create( const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef<FString>& ModelText, const ISlateStyle* Style) override;`
- L29 _private function_ `FTextStyleDecorator(FString&& InName, const FTextBlockStyle& InTextStyle) : DecoratorName(MoveTemp(InName)) , TextStyle(InTextStyle)`
- L38 _private member_ `FString DecoratorName;` — Name of this decorator
- L41 _private member_ `FTextBlockStyle TextStyle;` — Color of this decorator

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/IStateTreeEditor.h` (Public)


#### class `IStateTreeEditor`  
`class IStateTreeEditor : public FAssetEditorToolkit`  
_L9-13_
- inherits: `FAssetEditorToolkit`
- desc: StateTree Editor public interface

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/IStateTreeEditorHost.h` (Public)


#### class `IStateTreeEditorHost`  
`class IStateTreeEditorHost : public TSharedFromThis<IStateTreeEditorHost>`  
_L20-37_
- inherits: `TSharedFromThis<IStateTreeEditorHost>`
- desc: Interface required for re-using StateTreeEditor mode across different AssetEditors
- L23 _public prototype_ `IStateTreeEditorHost() = default;`
- L24 _public prototype_ `virtual ~IStateTreeEditorHost() = default;`
- L26 _public prototype_ `virtual FName GetCompilerLogName() const = 0;`
- L27 _public prototype_ `virtual FName GetCompilerTabName() const = 0;`
- L28 _public prototype_ `virtual bool ShouldShowCompileButton() const = 0;`
- L29 _public prototype_ `virtual bool CanToolkitSpawnWorkspaceTab() const = 0;`
- L31 _public prototype_ `virtual UStateTree* GetStateTree() const = 0;`
- L32 _public prototype_ `virtual FSimpleMulticastDelegate& OnStateTreeChanged() = 0;`
- L34 _public prototype_ `virtual TSharedPtr<IDetailsView> GetAssetDetailsView() = 0;`
- L35 _public prototype_ `virtual TSharedPtr<IDetailsView> GetDetailsView() = 0;`
- L36 _public prototype_ `virtual TSharedPtr<UE::StateTreeEditor::FWorkspaceTabHost> GetTabHost() const = 0;`

#### class `UStateTreeEditorContext`  
`class UStateTreeEditorContext : public UObject`  
_L40-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L44 _public member_ `TSharedPtr<IStateTreeEditorHost> EditorHostInterface;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace StateTreeEditor` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeCompiler.h` (Public)


#### struct `UE::StateTree::Compiler::FPostInternalContext`  
`struct FPostInternalContext`  
_L32-41_
- desc: Compiler context for when the state tree fully compiled and succeeded. This is the last compilation step.
- L34 _public prototype_ `virtual ~FPostInternalContext() = default;`
- L36 _public prototype_ `virtual TNotNull<const UStateTree*> GetStateTree() const = 0;`
- L37 _public prototype_ `virtual TNotNull<const UStateTreeEditorData*> GetEditorData() const = 0;`
- L38 _public prototype_ `virtual FStateTreeCompilerLog& GetLog() const = 0;`
- L40 _public prototype_ `virtual UStateTreeExtension* AddExtension(TNotNull<TSubclassOf<UStateTreeExtension>> ExtensionType) const = 0;`

#### struct `FStateTreeCompiler`  
`struct FStateTreeCompiler`  
_L48-183_
- desc: Helper class to convert StateTree editor representation into a compact data. Holds data needed during compiling.
- L52 _public function_ `explicit FStateTreeCompiler(FStateTreeCompilerLog& InLog) : Log(InLog)`
- L58 _public prototype_ `bool CompilePublic(TNotNull<UStateTree*> StateTree);` — Compile the public step of a state tree asset.
- L61 _public prototype_ `bool CompileInternal(TNotNull<UStateTree*> StateTree);` — Compile the internal step of a state tree asset.
- L64 _public prototype_ `bool Compile(TNotNull<UStateTree*> StateTree);` — Compile the public and internal steps of a state tree asset.
- L67 _public prototype_ `bool Compile(UStateTree& InStateTree);` — Compile the public and internal steps of a state tree asset.
- L70 _public prototype_ `static void CheckCompiledStateTreeOuters(TNotNull<const UStateTree*> InStateTree, FStateTreeCompilerLog& InLog);` — Tests that all instanced sub-objects in the compiled StateTree have correct outers. Reports errors to the compiler log.
- L76 _public prototype_ `static void AppendToStateTreeClassSchema(FAppendToClassSchemaContext& Context);` — Append config values that can change how state tree asset compiles when cooked. When the context is different from the previous result, then a cook is needed.
- L79 _private prototype_ `bool PreCompile(TNotNull<UStateTree*> StateTree);`
- L80 _private prototype_ `bool CompileInternalImpl();`
- L81 _private prototype_ `bool FailCompilation(UStateTree::ECompileStatus Status) const;`
- L84 _private prototype_ `bool ResolveTransitionStateAndFallback(const UStateTreeState* SourceState, const FStateTreeStateLink& Link, FStateTreeStateHandle& OutTransitionHandle, EStateTreeSelectionFallback& OutFallback) const;` — Resolves the state a transition points to, and the optional fallback for failing to enter the state. SourceState is nullptr for global tasks.
- L85 _private prototype_ `FStateTreeStateHandle GetStateHandle(const FGuid& StateID) const;`
- L86 _private prototype_ `UStateTreeState* GetState(const FGuid& StateID) const;`
- L88 _private prototype_ `void GatherBindingSources();`
- L90 _private prototype_ `bool CreateParameters();`
- L91 _private prototype_ `bool CreateStates();`
- L92 _private prototype_ `bool CreateStateRecursive(UStateTreeState& State, const FStateTreeStateHandle Parent);`
- L93 _private prototype_ `bool CreateEvaluators();`
- L94 _private prototype_ `bool CreateGlobalTasks();`
- L95 _private prototype_ `bool CreateStateTasksAndParameters();`
- L97 _private prototype_ `bool CreateStateTransitions();`
- L98 _private prototype_ `bool CreateStateEnterConditions(int32 StateIndex);`
- L100 _private prototype_ `bool CreateStateConsiderations();`
- L101 _private prototype_ `bool CreateStateConsideration(int32 StateIndex);`
- L103 _private prototype_ `bool CreateBindingsForNodes(TConstArrayView<FStateTreeEditorNode> EditorNodes, FStateTreeIndex16 NodesBegin, TArray<FInstancedStruct>& Instances);`
- L104 _private prototype_ `bool CreateBindingsForStruct(const FStateTreeBindableStructDesc& TargetStruct, FStateTreeDataView TargetValue, FStateTreeIndex16 PropertyFuncsBegin, FStateTreeIndex16 PropertyFuncsEnd, FStateTreeIndex16& OutBatchIndex, FStateTreeIndex16* OutOutputBindingBatchIndex = nullptr);`
- L106 _private prototype_ `bool CreatePropertyFunctionsForStruct(FGuid StructID);`
- L107 _private prototype_ `bool CreatePropertyFunction(const FStateTreeEditorNode& FuncEditorNode);`
- L109 _private prototype_ `bool CreateConditions(UStateTreeState& State, const FString& StatePath, TConstArrayView<FStateTreeEditorNode> Conditions);`
- L110 _private prototype_ `bool CreateCondition(UStateTreeState& State, const FString& StatePath, const FStateTreeEditorNode& CondNode, const EStateTreeExpressionOperand Operand, const int8 DeltaIndent);`
- L111 _private prototype_ `bool CreateConsiderations(UStateTreeState& State, const FString& StatePath, TConstArrayView<FStateTreeEditorNode> Considerations);`
- L112 _private prototype_ `bool CreateConsideration(UStateTreeState& State, const FString& StatePath, const FStateTreeEditorNode& ConsiderationNode, const EStateTreeExpressionOperand Operand, const int8 DeltaIndent);`
- L113 _private prototype_ `bool CreateTask(UStateTreeState* State, const FStateTreeEditorNode& TaskNode, const FStateTreeDataHandle TaskDataHandle);`
- L114 _private prototype_ `bool CreateEvaluator(const FStateTreeEditorNode& EvalNode, const FStateTreeDataHandle EvalDataHandle);`
- L116 _private prototype_ `bool CreateTaskCompletionDispatchers();`
- L118 _private prototype_ `FInstancedStruct* CreateNode(UStateTreeState* State, const FStateTreeEditorNode& EditorNode, FStateTreeBindableStructDesc& InstanceDesc, const FStateTreeDataHandle DataHandle, TArray<FInstancedStruct>& InstancedStructContainer);`
- L119 _private prototype_ `FInstancedStruct* CreateNodeWithSharedInstanceData(UStateTreeState* State, const FStateTreeEditorNode& EditorNode, FStateTreeBindableStructDesc& InstanceDesc);`
- L120 _private prototype_ `TOptional<FStateTreeDataView> CreateNodeInstanceData(const FStateTreeEditorNode& EditorNode, FStateTreeNodeBase& Node, FStateTreeBindableStructDesc& InstanceDesc, const FStateTreeDataHandle DataHandle, TArray<FInstancedStruct>& InstancedStructContainer);`
- L131 _private prototype_ `bool GetAndValidateBindings(const FStateTreeBindableStructDesc& TargetStruct, FStateTreeDataView TargetValue, FValidatedPathBindings& OutValidatedBindings) const;`
- L132 _private prototype_ `bool ValidateStructRef(const FStateTreeBindableStructDesc& SourceStruct, const FPropertyBindingPath& SourcePath, const FStateTreeBindableStructDesc& TargetStruct, const FPropertyBindingPath& TargetPath) const;`
- L134 _private prototype_ `bool ValidateBindingOnNode(const FStateTreeBindableStructDesc& TargetStruct, const FPropertyBindingPath& TargetPath) const;`
- L135 _private prototype_ `bool CompileAndValidateNode(const UStateTreeState* SourceState, const FStateTreeBindableStructDesc& InstanceDesc, FStructView NodeView, const FStateTreeDataView InstanceData);`
- L137 _private prototype_ `void InstantiateStructSubobjects(FStructView Struct);`
- L139 _private prototype_ `bool NotifyInternalPost();`
- L141 _private prototype_ `void CreateBindingSourceStructsForNode(const FStateTreeEditorNode& EditorNode, const FStateTreeBindableStructDesc& InstanceDesc);`
- L143 _private prototype_ `const FString& GetStatePath(int32 StateIndex) const;`
- L146 _private member_ `FStateTreeCompilerLog& Log;`
- L147 _private member_ `TObjectPtr<UStateTree> StateTree = nullptr;`
- L148 _private member_ `TObjectPtr<UStateTreeEditorData> EditorData = nullptr;`
- L149 _private member_ `TMap<FGuid, int32> IDToNode;`
- L150 _private member_ `TMap<FGuid, int32> IDToState;`
- L151 _private member_ `TMap<FGuid, int32> IDToTransition;`
- L152 _private member_ `TMap<FGuid, const FStateTreeDataView > IDToStructValue;`
- L153 _private member_ `TMap<FStateTreeStateHandle, int32> StateHandleToFrameIndex;`
- L154 _private member_ `TMultiMap<FGuid, const FPropertyBindingBinding*> BindingsByTargetStructID;`
- L155 _private member_ `TArray<TObjectPtr<UStateTreeState>> SourceStates;`
- L156 _private member_ `TArray<FString> StatePaths;`
- L158 _private member_ `TArray<FInstancedStruct> Nodes;`
- L159 _private member_ `TArray<FInstancedStruct> InstanceStructs;`
- L160 _private member_ `TArray<FInstancedStruct> SharedInstanceStructs;`
- L161 _private member_ `TArray<FInstancedStruct> EvaluationScopeStructs;`
- L162 _private member_ `TArray<FInstancedStruct> ExecutionRuntimeStructs;`
- L168 _private member_ `int32 EditorBindingsNum = 0;` — Number of binding in the editor data. Used to check that pointer in BindingsByTargetStructID are valid.
- L171 _private member_ `int32 GlobalTaskEndBit = 0;` — Cached result of MakeCompletionTasksMask for global tasks. Indicates where state tasks should start.
- L173 _private member_ `FStateTreePropertyBindingCompiler BindingsCompiler;`
- L176 _private member_ `TSet<FGuid> TaskCompletionDispatcherIDs;` — All struct IDs that are used as task completion delegate dispatcher (from all bindings).
- L179 _private member_ `TOptional<uint32> EditorDataHash;` — The state tree hash.
- L182 _private member_ `bool bCompiled = false;` — The Compile function executed.

#### struct `FStateTreeCompiler::FValidatedPathBindings`  
`struct FValidatedPathBindings`  
_L122-129_
- L124 _public member_ `TArray<FStateTreePropertyPathBinding> CopyBindings;`
- L125 _public member_ `TArray<FStateTreePropertyPathBinding> OutputCopyBindings;`
- L126 _public member_ `TArray<FStateTreePropertyPathBinding> DelegateDispatchers;`
- L127 _public member_ `TArray<FStateTreePropertyPathBinding> DelegateListeners;`
- L128 _public member_ `TArray<FStateTreePropertyPathBinding> ReferenceBindings;`

#### struct `UE::StateTree::Compiler::FValidationResult`  
`struct FValidationResult`  
_L188-210_
- L190 _public prototype_ `FValidationResult() = default;`
- L191 _public function_ `FValidationResult(const bool bInResult, const int32 InValue, const int32 InMaxValue) : bResult(bInResult), Value(InValue), MaxValue(InMaxValue)`
- L194 _public function_ `bool DidSucceed() const` — Validation succeeded
- L197 _public function_ `bool DidFail() const` — Validation failed
- L205 _public prototype_ `void Log(FStateTreeCompilerLog& Log, const TCHAR* ContextText, const FStateTreeBindableStructDesc& ContextStruct = FStateTreeBindableStructDesc()) const;` — Logs common validation for IsValidIndex16(), IsValidIndex8(), IsValidCount16(), IsValidCount8(). @param Log reference to the compiler log. @param ContextText Text identifier for the context where the test is done. @param ContextStruct Struct identifier for the context where the test is done.
- L207 _public member_ `bool bResult = true;`
- L208 _public member_ `int32 Value = 0;`
- L209 _public member_ `int32 MaxValue = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace StateTree` (scope `UE`)
- L26 _namespace_ `namespace Compiler` (scope `UE::StateTree`)
- L186 _namespace_ `namespace UE`
- L186 _namespace_ `namespace StateTree` (scope `UE`)
- L186 _namespace_ `namespace Compiler` (scope `UE::StateTree`)
- L217 _function_ `inline FValidationResult IsValidIndex16(const int32 Index)` (scope `UE::StateTree::Compiler`) — Checks if given index can be represented as uint16, including MAX_uint16 as INDEX_NONE. @param Index Index to test @return validation result.
- L227 _function_ `inline FValidationResult IsValidIndex8(const int32 Index)` (scope `UE::StateTree::Compiler`) — Checks if given index can be represented as uint8, including MAX_uint8 as INDEX_NONE. @param Index Index to test @return true if the index is valid.
- L237 _function_ `inline FValidationResult IsValidCount16(const int32 Count)` (scope `UE::StateTree::Compiler`) — Checks if given count can be represented as uint16. @param Count Count to test @return true if the count is valid.
- L247 _function_ `inline FValidationResult IsValidCount8(const int32 Count)` (scope `UE::StateTree::Compiler`) — Checks if given count can be represented as uint8. @param Count Count to test @return true if the count is valid.
- L258 _prototype_ `const UScriptStruct* GetBaseStructFromMetaData(const FProperty* Property, FString& OutBaseStructName);` (scope `UE::StateTree::Compiler`) — Returns UScriptStruct defined in "BaseStruct" metadata of given property. @param Property Handle to property where value is got from. @param OutBaseStructName Handle to property where value is got from. @return Script struct defined by the BaseStruct or nullptr if not found.

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeCompilerLog.h` (Public)


#### struct `FStateTreeCompilerLogMessage`  
`struct FStateTreeCompilerLogMessage`  
_L15-43_
- reflection: `USTRUCT()`
- desc: StateTree compiler log message
- L19 _public prototype_ `FStateTreeCompilerLogMessage() = default;`
- L20 _public function_ `FStateTreeCompilerLogMessage(const EMessageSeverity::Type InSeverity, const UStateTreeState* InState, const FStateTreeBindableStructDesc& InItem, const FString& InMessage) : Severity(InSeverity) , State(InState) , Item(InItem) , Message(InMessage)`
- L30 _public member_ `int32 Severity = EMessageSeverity::Error;` — `UPROPERTY()` — Severity of the message.
- L34 _public member_ `TObjectPtr<const UStateTreeState> State = nullptr;` — `UPROPERTY()` — (optional) The StateTree state the message refers to.
- L38 _public member_ `FStateTreeBindableStructDesc Item;` — `UPROPERTY()` — (optional) The State tee item (condition/evaluator/task) the message refers to.
- L42 _public member_ `FString Message;` — `UPROPERTY()` — The message

#### struct `FStateTreeCompilerLog`  
`struct FStateTreeCompilerLog`  
_L47-117_
- reflection: `USTRUCT()`
- desc: Message log for StateTree compilation
- L52 _public function_ `void PushState(const UStateTreeState* InState)` — Pushes State to be reported along with the message.
- L58 _public function_ `void PopState(const UStateTreeState* InState)` — Pops State to be reported along with the message. @see FStateTreeCompilerLogStateScope
- L66 _public function_ `const UStateTreeState* CurrentState() const` — Returns current state context.
- L74 _public function_ `void Report(EMessageSeverity::Type InSeverity, const FStateTreeBindableStructDesc& InItem, const FString& InMessage)` — Reports a message. @param InSeverity Severity of the message. @param InItem StateTree item (condition/evaluator/task) the message affects. @param InMessage Message to display.
- L81 _public function_ `template <typename... Types> void Reportf(EMessageSeverity::Type InSeverity, const FStateTreeBindableStructDesc& InItem, UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args)` — Formatted version of the Report().
- L91 _public function_ `template <typename... Types> void Reportf(EMessageSeverity::Type InSeverity, UE::Core::TCheckedFormatString<FString::FmtCharType, Types...> Fmt, Types... Args)` — Formatted version of the Report(), omits Item for convenience.
- L97 _public prototype_ `TArray<TSharedRef<FTokenizedMessage>> ToTokenizedMessages() const;` — Generates tokenized messages from the messages in this log
- L100 _public prototype_ `void AppendToLog(class IMessageLogListing* LogListing) const;` — Appends StateTree log to log listing.
- L103 _public prototype_ `void DumpToLog(const FLogCategoryBase& Category) const;` — Dumps StateTree log to log.
- L109 _public prototype_ `void DumpToLog(const UStateTree* Asset, const FLogCategoryBase& Category) const;` — Dumps StateTree log to log. Append the asset to the log if there are any messages.
- L113 _protected member_ `TArray<TObjectPtr<const UStateTreeState>> StateStack;` — `UPROPERTY()`
- L116 _protected member_ `TArray<FStateTreeCompilerLogMessage> Messages;` — `UPROPERTY()`

#### struct `FStateTreeCompilerLogStateScope`  
`struct FStateTreeCompilerLogStateScope`  
_L120-136_
- desc: Helper struct to manage reported state within a scope.
- L122 _public function_ `FStateTreeCompilerLogStateScope(const UStateTreeState* InState, FStateTreeCompilerLog& InLog) : Log(InLog) , State(InState)`
- L129 _public function_ `~FStateTreeCompilerLogStateScope()`
- L134 _public member_ `FStateTreeCompilerLog& Log;`
- L135 _public member_ `const UStateTreeState* State = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeCompilerManager.h` (Public)


#### class `UE::StateTree::Compiler::FCompilerManager`  
`class FCompilerManager final`  
_L15-68_
- L18 _public prototype_ `static void Startup();`
- L19 _public prototype_ `static void Shutdown();`
- L28 _public prototype_ `static void QueueForCompilation(TNotNull<UStateTree*> StateTree);` — Queue the compilation of a dirty state tree asset for later. The public step will be compiled synchronously if it is dirty. The internal step will be compiled when requested by the game or asynchronously. Queuing state tree asset can be disabled with cvar. When disabled, this function behaves like CompileSynchronously. @note Can only compile on the game thread or async loading thread.
- L35 _public prototype_ `static void FlushCompilationQueue();` — Compile the internal steps of all queued state tree assets. Sort them to compile them with regard to their dependencies. @note Can only flush on the game thread.
- L43 _public prototype_ `static bool CompileSynchronously(TNotNull<UStateTree*> StateTree);` — Compile the public and internal steps of a state tree asset. It will compile all the pending state tree asset dependencies if they are queued. @return whether the compilation succeeded or failed. @note Can only compile on the game thread or async loading thread.
- L44 _public prototype_ `static bool CompileSynchronously(TNotNull<UStateTree*> StateTree, FStateTreeCompilerLog& Log);`
- L52 _public prototype_ `static TOptional<bool> CompileIfNeededSynchronously(TNotNull<UStateTree*> StateTree);` — Compile the public and internal steps of a state tree asset only if the editor data changed. It will compile all the pending state tree asset dependencies if they are queued. @return whether the compilation succeeded or failed. The optional is not set if a compilation was not necessary. @note Can only compile on the game thread or async loading thread.
- L59 _public prototype_ `static void CacheEditorBindingExternalDependencies(TNotNull<UStateTreeEditorData*> EditorData);` — Cache dependent external objects for tree's editor bindings. This includes any objects outside StateTree and CoreModule, that editor bindings are dependent on. This function gets called when EditorData updates its bindings.
- L62 _public prototype_ `static void MarkAsModified(TNotNull<UStateTree*> StateTree);` — Track a state tree as dirty for compilation.
- L65 _private prototype_ `FCompilerManager() = delete;`
- L66 _private prototype_ `FCompilerManager(const FCompilerManager&) = delete;`
- L67 _private prototype_ `FCompilerManager& operator= (const FCompilerManager&) = delete;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StateTree` (scope `UE`)
- L9 _namespace_ `namespace Compiler` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditingSubsystem.h` (Public)


#### class `UStateTreeEditingSubsystem`  
`class UStateTreeEditingSubsystem : public UEditorSubsystem`  
_L20-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- L24 _public prototype_ `UStateTreeEditingSubsystem();`
- L25 _public prototype_ `virtual void BeginDestroy() override;`
- L27 _public prototype_ `TSharedPtr<FStateTreeViewModel> FindViewModel(TNotNull<const UStateTree*> InStateTree) const;`
- L28 _public prototype_ `TSharedRef<FStateTreeViewModel> FindOrAddViewModel(TNotNull<UStateTree*> InStateTree);`
- L31 _public prototype_ `static TSharedRef<SWidget> GetStateTreeView(TSharedRef<FStateTreeViewModel> InViewModel, const TSharedRef<FUICommandList>& TreeViewCommandList);` — Create a state tree view widget for the viewmodel.
- L37 _public prototype_ `static bool CompileStateTree(TNotNull<UStateTree*> InStateTree, FStateTreeCompilerLog& InOutLog);` — Compile the state tree asset. It will compile the public and internal steps.
- L40 _public prototype_ `static bool NeedsRecompile(TNotNull<const UStateTree*> InStateTree);` — Whether the state tree asset is dirty and requires a compilation.
- L47 _public prototype_ `static void MarkAsPubliclyModified(TNotNull<UStateTree*> InStateTree);` — Mark the public and the internal steps of the state tree asset as dirty. It will require the state tree to be compiled before it can be used. It will affect the other assets that reference the state tree asset.
- L53 _public prototype_ `static void MarkAsModified(TNotNull<UStateTree*> InStateTree);` — Mark the internal step of the state tree asset as dirty. It will require the state tree to be compiled before it can be used.
- L60 _public prototype_ `static void ValidateStateTree(TNotNull<UStateTree*> InStateTree);` — Validates and applies the schema restrictions on the StateTree. Also serves as the "safety net" of fixing up editor data following an editor operation. Updates state's link, removes the unused node while validating the StateTree asset.
- L63 _public prototype_ `static uint32 CalculateStateTreeHash(TNotNull<const UStateTree*> InStateTree);` — Calculates editor data hash of the asset.
- L66 _private prototype_ `void HandlePostGarbageCollect();`
- L67 _private prototype_ `void HandlePostCompile(const UStateTree& InStateTree);`
- L70 _protected member_ `TMap<FObjectKey, TSharedPtr<FStateTreeViewModel>> StateTreeViewModels;`
- L71 _protected member_ `FDelegateHandle PostGarbageCollectHandle;`
- L72 _protected member_ `FDelegateHandle PostCompileHandle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorData.h` (Public)


#### struct `FStateTreeEditorBreakpoint`  
`struct FStateTreeEditorBreakpoint`  
_L34-52_
- reflection: `USTRUCT()`
- L38 _public prototype_ `FStateTreeEditorBreakpoint() = default;`
- L39 _public function_ `explicit FStateTreeEditorBreakpoint(const FGuid& ID, const EStateTreeBreakpointType BreakpointType) : ID(ID) , BreakpointType(BreakpointType)`
- L47 _public member_ `FGuid ID;` — `UPROPERTY()` — Unique Id of the Node or State associated to the breakpoint.
- L51 _public member_ `EStateTreeBreakpointType BreakpointType = EStateTreeBreakpointType::Unset;` — `UPROPERTY()` — The event type that should trigger the breakpoint (e.g. OnEnter, OnExit, etc.).

#### enum `EStateTreeVisitor`  
`enum class EStateTreeVisitor : uint8`  
_L55-59_
- reflection: `UENUM()`
- L57 _public enumerator_ `Continue`
- L58 _public enumerator_ `Break`

#### class `UStateTreeEditorData`  
`class UStateTreeEditorData : public UObject, public IStateTreeEditorPropertyBindingsOwner`  
_L65-457_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, Within = "StateTree", meta = (DisallowLevelActorReference = true))`
- inherits: `UObject,IStateTreeEditorPropertyBindingsOwner`
- desc: Edit time data for StateTree asset. This data gets baked into runtime format before being used by the StateTreeInstance.
- L70 _public prototype_ `UStateTreeEditorData();`
- L74 _public prototype_ `static UStateTreeEditorData* GetEditorData(UStateTree* StateTree);` — `UFUNCTION(BlueprintCallable, Category = "StateTree")` — @return The editor data for a StateTree asset, or nullptr if unavailable.
- L76 _public prototype_ `virtual void PostInitProperties() override;`
- L77 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L80 _public prototype_ `virtual void GetBindableStructs(const FGuid TargetStructID, TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& OutStructDescs) const override;`
- L81 _public prototype_ `virtual bool GetBindableStructByID(const FGuid StructID, TInstancedStruct<FPropertyBindingBindableStructDescriptor>& OutStructDesc) const override;`
- L82 _public prototype_ `virtual bool GetBindingDataViewByID(const FGuid StructID, FPropertyBindingDataView& OutDataView) const override;`
- L83 _public function_ `virtual const FStateTreeEditorPropertyBindings* GetPropertyEditorBindings() const override`
- L88 _public function_ `virtual FPropertyBindingBindingCollection* GetEditorPropertyBindings() override`
- L93 _public function_ `virtual const FPropertyBindingBindingCollection* GetEditorPropertyBindings() const override`
- L98 _public function_ `virtual FStateTreeEditorPropertyBindings* GetPropertyEditorBindings() override`
- L103 _public prototype_ `virtual FStateTreeBindableStructDesc FindContextData(const UStruct* ObjectType, const FString ObjectNameHint) const override;`
- L105 _public prototype_ `virtual bool CanCreateParameter(const FGuid InStructID) const override;`
- L106 _public prototype_ `virtual void CreateParametersForStruct(const FGuid InStructID, TArrayView<UE::PropertyBinding::FPropertyCreationDescriptor> InOutCreationDescs) override;`
- L109 _public prototype_ `virtual void OnPropertyBindingChanged(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) override;` — todo: (jira UE-337309) we have many sites that manipulate state/node which will change bindings, but not calling this function. Currently it is only called when you change binding from the details view
- L111 _public prototype_ `virtual void AppendBindablePropertyFunctionStructs(TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& InOutStructs) const override;`
- L120 _public prototype_ `FText GetNodeDescription(const FStateTreeEditorNode& Node, const EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const;` — `UFUNCTION(BlueprintCallable, Category = "StateTree")` — Returns the description for the node for UI. Handles the name override logic, figures out required data for the GetDescription() call, and handles the fallbacks. @return description for the node.
- L123 _public prototype_ `void OnParametersChanged(const UStateTree& StateTree);`
- L124 _public prototype_ `void OnStateParametersChanged(const UStateTree& StateTree, const FGuid StateID);`
- L125 _public prototype_ `virtual void BeginDestroy() override;`
- L126 _public prototype_ `virtual void PostLoad() override;`
- L127 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L128 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L132 _public function_ `FGuid GetRootParametersGuid() const` — @return the public parameters ID that could be used for bindings within the Tree.
- L138 _public function_ `virtual const FInstancedPropertyBag& GetRootParametersPropertyBag() const` — @return the public parameters that could be used for bindings within the Tree.
- L144 _public prototype_ `const UStateTreeState* GetStateByStructID(const FGuid TargetStructID) const;` — @returns parent state of a struct, or nullptr if not found.
- L147 _public prototype_ `const UStateTreeState* GetStateByID(const FGuid StateID) const;` — @returns state based on its ID, or nullptr if not found.
- L150 _public prototype_ `UStateTreeState* GetMutableStateByID(const FGuid StateID);` — @returns mutable state based on its ID, or nullptr if not found.
- L153 _public prototype_ `void GetAllStructValues(TMap<FGuid, const FStateTreeDataView>& OutAllValues) const;` — @returns the IDs and instance values of all bindable structs in the StateTree.
- L156 _public prototype_ `void GetAllStructValues(TMap<FGuid, const FPropertyBindingDataView>& OutAllValues) const;` — @returns the IDs and instance values of all bindable structs in the StateTree.
- L162 _public prototype_ `EStateTreeVisitor VisitHierarchy(TFunctionRef<EStateTreeVisitor(UStateTreeState& State, UStateTreeState* ParentState)> InFunc) const;` — Iterates over all structs that are related to binding @param InFunc function called at each node, should return Continue if visiting is continued or Break to stop.
- L168 _public prototype_ `EStateTreeVisitor VisitGlobalNodes(TFunctionRef<EStateTreeVisitor(const UStateTreeState* State, const FStateTreeBindableStructDesc& Desc, const FStateTreeDataView Value)> InFunc) const;` — Iterates over all structs at the global level (context, tree parameters, evaluators, global tasks) that are related to binding. @param InFunc function called at each node, should return Continue if visiting is continued or Break to stop.
- L174 _public prototype_ `EStateTreeVisitor VisitHierarchyNodes(TFunctionRef<EStateTreeVisitor(const UStateTreeState* State, const FStateTreeBindableStructDesc& Desc, const FStateTreeDataView Value)> InFunc) const;` — Iterates over all structs in the state hierarchy that are related to binding. @param InFunc function called at each node, should return Continue if visiting is continued or Break to stop.
- L180 _public prototype_ `EStateTreeVisitor VisitAllNodes(TFunctionRef<EStateTreeVisitor(const UStateTreeState* State, const FStateTreeBindableStructDesc& Desc, const FStateTreeDataView Value)> InFunc) const;` — Iterates over all structs that are related to binding. @param InFunc function called at each node, should return Continue if visiting is continued or Break to stop.
- L186 _public prototype_ `EStateTreeVisitor VisitStateNodes(const UStateTreeState& State, TFunctionRef<EStateTreeVisitor(const UStateTreeState* State, const FStateTreeBindableStructDesc& Desc, const FStateTreeDataView Value)> InFunc) const;` — Iterates over all nodes in a given state. @param InFunc function called at each node, should return Continue if visiting is continued or Break to stop.
- L192 _public prototype_ `EStateTreeVisitor VisitStructBoundPropertyFunctions(FGuid StructID, const FString& StatePath, TFunctionRef<EStateTreeVisitor(const FStateTreeEditorNode& EditorNode, const FStateTreeBindableStructDesc& Desc, const FStateTreeDataView Value)> InFunc) const;` — Iterates recursively over all property functions of the provided node. Also nested ones. @param InFunc function called at each node, should return Continue if visiting is continued or Break to stop.
- L198 _public prototype_ `EStateTreeVisitor VisitStateBindings(TNotNull<const UStateTreeState*> State, TFunctionRef<EStateTreeVisitor(TNotNull<const UStateTreeState*> State, const FStateTreePropertyPathBinding& Binding, const FStateTreeBindableStructDesc& BindingTargetNodeDesc, const FStateTreeDataView BindingTargetNodeValue)> InFunc) const;` — Iterates over all bindings whose target path is in a given state. @param InFunc function called at each binding, should return Continue if visiting is continued or Break to stop.
- L206 _public prototype_ `void GetAccessibleStructsInExecutionPath(const TConstArrayView<const UStateTreeState*> Path, const FGuid TargetStructID, TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& OutStructDescs) const;` — Returns array of nodes along the execution path, up to the TargetStruct. @param Path The states to visit during the check @param TargetStructID The ID of the node where to stop. @param OutStructDescs Array of nodes accessible on the given path.
- L213 _public prototype_ `virtual EStateTreeVisitor EnumerateBindablePropertyFunctionNodes(TFunctionRef<EStateTreeVisitor(const UScriptStruct* NodeStruct, const FStateTreeBindableStructDesc& Desc, const FStateTreeDataView Value)> InFunc) const override;` — Iterates over all template property function nodes. Note it is different from calling VisitStructBoundPropertyFunctions which returns the instanced property functions for a node. @param InFunc function called at each node, should return Continue if visiting is continued or Break to stop.
- L216 _public function_ `void GetAccessibleStruct(const TConstArrayView<const UStateTreeState*> Path, const FGuid TargetStructID, TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& OutStructDescs) const` — `UE_DEPRECATED(5.6, "Use GetAccessibleStructsInExecutionPath instead")`
- L223 _public function_ `template<typename ExtensionType> ExtensionType* GetExtension()` — Find the first extension of the requested type.
- L230 _public function_ `template<typename ExtensionType> ExtensionType* GetOrCreateExtension()` — Find the first extension of the requested type or create it on this editor data if it doesn't exist.
- L247 _public prototype_ `UStateTreeEditorDataExtension* K2_GetExtension(TSubclassOf<UStateTreeEditorDataExtension> ExtensionType);` — `UFUNCTION(BlueprintCallable, Category = "StateTree|Extension", Meta = (DisplayName="Get Extension", DeterminesOutputType = "ExtensionType"))` — Find the first extension of the requested type.
- L250 _public prototype_ `void ReparentStates();` — Make sure the child and parent states are pointing to each other.
- L252 _public prototype_ `void FixDuplicateIDs();` — Fix any nodes or bindings with duplicated ID.
- L255 _public function_ `void UpdateBindingsInstanceStructs()` — `UE_DEPRECATED(5.8, "Use UpdateEditorBindings instead")`
- L261 _public prototype_ `void UpdateBindings();` — Update the editor binding segments and cache editor bindings dependency.
- L264 _public prototype_ `void RemoveInvalidBindings();` — Remove invalid editor property bindings.
- L272 _public function_ `UStateTreeState& AddSubTree(const FName Name, EStateTreeStateType StateType = EStateTreeStateType::State)` — Adds new Subtree with specified name. @return Pointer to the new Subtree.
- L286 _public function_ `UStateTreeState& AddRootState()` — Adds new Subtree named "Root". @return Pointer to the new Subtree.
- L296 _public function_ `template<typename T, typename... TArgs> TStateTreeEditorNode<T>& AddEvaluator(TArgs&&... InArgs)` — Adds Evaluator of specified type. @return reference to the new Evaluator.
- L309 _public function_ `template<typename T, typename... TArgs> TStateTreeEditorNode<T>& AddGlobalTask(TArgs&&... InArgs)` — Adds Global Task of specified type. @return reference to the new task.
- L320 _public function_ `void AddPropertyBinding(const FPropertyBindingPath& SourcePath, const FPropertyBindingPath& TargetPath)` — Adds property binding between two structs.
- L328 _public function_ `void AddPropertyBinding(const UScriptStruct* PropertyFunctionNodeStruct, TConstArrayView<FPropertyBindingPathSegment> SourcePathSegments, const FPropertyBindingPath& TargetPath)` — Adds property binding to PropertyFunction of provided type.
- L336 _public function_ `void RemovePropertyBinding(const FPropertyBindingPath& TargetPath)` — Removes property binding of target path.
- L345 _public function_ `bool AddPropertyBinding(const FStateTreeEditorNode& SourceNode, const FString SourcePathStr, const FStateTreeEditorNode& TargetNode, const FString TargetPathStr)` — Adds property binding between two structs.
- L360 _public prototype_ `bool HasAnyBreakpoint(FGuid ID) const;`
- L361 _public prototype_ `bool HasBreakpoint(FGuid ID, EStateTreeBreakpointType BreakpointType) const;`
- L362 _public prototype_ `const FStateTreeEditorBreakpoint* GetBreakpoint(FGuid ID, EStateTreeBreakpointType BreakpointType) const;`
- L363 _public prototype_ `void AddBreakpoint(FGuid ID, EStateTreeBreakpointType BreakpointType);`
- L364 _public prototype_ `bool RemoveBreakpoint(FGuid ID, EStateTreeBreakpointType BreakpointType);`
- L365 _public prototype_ `void RemoveAllBreakpoints();`
- L373 _public function_ `const FStateTreeEditorColor* FindColor(const FStateTreeEditorColorRef& ColorRef) const` — Attempts to find a Color matching the provided Color Key
- L378 _public prototype_ `virtual void CreateRootProperties(TArrayView<UE::PropertyBinding::FPropertyCreationDescriptor> InOutCreationDescs);`
- L381 _private prototype_ `void FixObjectNodes();`
- L382 _private prototype_ `void DuplicateIDs();`
- L383 _private prototype_ `void CallPostLoadOnNodes();`
- L384 _private prototype_ `void OnNodeAdded(FStateTreeEditorNode& EditorNode);`
- L387 _private member_ `FDelegateHandle OnParametersChangedHandle;`
- L388 _private member_ `FDelegateHandle OnStateParametersChangedHandle;`
- L394 _public member_ `TObjectPtr<UStateTreeSchema> Schema = nullptr;` — `UPROPERTY(EditDefaultsOnly, Instanced, Category = "Common", NoClear)` — Schema describing which inputs, evaluators, and tasks a StateTree can contain.
- L398 _public member_ `TObjectPtr<UStateTreeEditorSchema> EditorSchema = nullptr;` — `UPROPERTY(Instanced, NoClear)` — Schema describing how the editor schema is customized.
- L402 _public member_ `TArray<TObjectPtr<UStateTreeEditorDataExtension>> Extensions;` — `UPROPERTY(EditDefaultsOnly, Instanced, Category = "Extension", NoClear)` — The editor data extensions. A place to add extra information for plugins.
- L407 _public member_ `FStateTreeStateParameters RootParameters;` — `UE_DEPRECATED(5.6, "Public access to RootParameters is deprecated. Use GetRootParametersPropertyBag")` — `UPROPERTY(meta = (DeprecatedProperty))` — Public parameters that could be used for bindings within the Tree.
- L412 _private member_ `FGuid RootParametersGuid;` — `UPROPERTY()` — Public parameters ID that could be used for bindings within the Tree.
- L416 _private member_ `FInstancedPropertyBag RootParameterPropertyBag;` — `UPROPERTY(EditDefaultsOnly, Category = Parameters)` — Public parameters property bag that could be used for bindings within the Tree.
- L420 _public member_ `TArray<FStateTreeEditorNode> Evaluators;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Evaluators", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeEvaluatorBase", BaseClass = "/Script/StateTreeModule.StateTreeEvaluatorBlueprintBase"))`
- L423 _public member_ `TArray<FStateTreeEditorNode> GlobalTasks;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Global Tasks", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeTaskBase", BaseClass = "/Script/StateTreeModule.StateTreeTaskBlueprintBase"))`
- L426 _public member_ `EStateTreeTaskCompletionType GlobalTasksCompletion = EStateTreeTaskCompletionType::Any;` — `UPROPERTY(EditDefaultsOnly, Category = "Global Tasks")`
- L429 _public member_ `FStateTreeEditorPropertyBindings EditorBindings;` — `UPROPERTY()`
- L433 _public member_ `TSet<FStateTreeEditorColor> Colors;` — `UPROPERTY(EditDefaultsOnly, Category = "Theme")` — Color Options to assign to a State
- L437 _public member_ `TArray<TObjectPtr<UStateTreeState>> SubTrees;` — `UPROPERTY(Instanced, BlueprintReadOnly, Category = "StateTree")` — Top level States.
- L446 _public member_ `TArray<FStateTreeEditorBreakpoint> Breakpoints;` — `UPROPERTY(Transient)` — Transient list of breakpoints added in the debugging session. These will be lost if the asset gets reloaded. If there is eventually a change to make those persist with the asset we need to prune all dangling breakpoints after states/tasks got removed.
- L453 _public member_ `TArray<FStateTreeEditorDelegateDispatcherCompiledBinding> CompiledDispatchers;` — `UPROPERTY(DuplicateTransient)` — List of the previous compiled delegate dispatchers. Saved in the editor data to be duplicated transient.

#### class `UQAStateTreeEditorData`  
`class UQAStateTreeEditorData : public UStateTreeEditorData`  
_L461-464_
- reflection: `UCLASS()`
- inherits: `UStateTreeEditorData`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace StateTree` (scope `UE`)
- L19 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L22 _externvar_ `extern const FString GlobalStateName;` (scope `UE::StateTree::Editor`) — Name used to describe container of global items (other items use the path to the container State).
- L25 _externvar_ `extern const FString PropertyFunctionStateName;` (scope `UE::StateTree::Editor`) — Name used to describe container of property functions.
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace StateTree` (scope `UE`)
- L28 _namespace_ `namespace Compiler` (scope `UE::StateTree`)
- L28 _namespace_ `namespace Private` (scope `UE::StateTree::Compiler`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorDataExtension.h` (Public)


#### class `UStateTreeEditorDataExtension`  
`class UStateTreeEditorDataExtension : public UObject`  
_L21-64_
- reflection: `UCLASS(Abstract, DefaultToInstanced, EditInlineNew, Within=StateTreeEditorData, MinimalAPI)`
- inherits: `UObject`
- desc: Extension for the editor data of the state tree asset.
- L31 _public function_ `virtual void PreValidate()` — Validates and applies the editor data extension restrictions on the state tree owned by the extension. This is before the engine validation. The Schema and EditorData will be correctly set. You are allowed to modify the editor data.
- L40 _public function_ `virtual void Validate()` — Validates and applies the editor data extension restrictions on the state tree owned by the extension. Also serves as the "safety net" of fixing up editor data following an editor operation. You are allowed to modify the editor data.
- L49 _public function_ `virtual bool HandlePostInternalCompile(const UE::StateTree::Compiler::FPostInternalContext& Context)` — Handled after the asset had properly compiled its public and internal data. You are allowed to modify the state tree. You should not modify the editor data. It might create an infinite loop.
- L55 _public function_ `virtual void CustomizeDetails(TNonNullPtr<UStateTreeState> State, IDetailLayoutBuilder& DetailBuilder)` — Customize the detail view for the selected state.
- L60 _protected function_ `UStateTreeEditorData* GetStateTreeEditorData() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace StateTree` (scope `UE`)
- L8 _namespace_ `namespace Compiler` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorMode.h` (Public)


#### class `UStateTreeEditorMode`  
`class UStateTreeEditorMode : public UEdMode`  
_L19-109_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UEdMode`
- L23 _public member_ `const static FEditorModeID EM_StateTree;`
- L25 _public prototype_ `UStateTreeEditorMode();`
- L27 _public prototype_ `virtual void Enter() override;`
- L28 _public prototype_ `virtual void Exit() override;`
- L29 _public prototype_ `virtual void CreateToolkit() override;`
- L30 _public prototype_ `virtual void BindCommands() override;`
- L33 _protected prototype_ `void OnStateTreeChanged();`
- L34 _protected prototype_ `void BindToolkitCommands(const TSharedRef<FUICommandList>& ToolkitCommands);`
- L36 _protected prototype_ `void OnPropertyBindingChanged(const FPropertyBindingPath& SourcePath, const FPropertyBindingPath& TargetPath);`
- L37 _protected prototype_ `void OnIdentifierChanged(const UStateTree& InStateTree);`
- L38 _protected prototype_ `void OnSchemaChanged(const UStateTree& InStateTree);`
- L39 _protected prototype_ `void ForceRefreshDetailsView() const;`
- L40 _protected prototype_ `void OnRefreshDetailsView(const UStateTree& InStateTree) const;`
- L41 _protected prototype_ `void OnStateParametersChanged(const UStateTree& InStateTree, const FGuid ChangedStateID) const;`
- L43 _protected prototype_ `void HandleMessageTokenClicked(const TSharedRef<IMessageToken>& InMessageToken) const;`
- L45 _protected prototype_ `void OnAssetFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent) const;`
- L46 _protected prototype_ `void OnSelectionFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L48 _protected prototype_ `void Compile();`
- L49 _protected prototype_ `bool CanCompile() const;`
- L50 _protected prototype_ `bool IsCompileVisible() const;`
- L52 _protected prototype_ `bool HasValidStateTree() const;`
- L54 _protected prototype_ `void HandleModelAssetChanged();`
- L55 _protected prototype_ `void HandleModelSelectionChanged(const TArray<TWeakObjectPtr<UStateTreeState>>& SelectedStates) const;`
- L56 _protected prototype_ `void HandleModelBringNodeToFocus(const UStateTreeState* State, const FGuid NodeID) const;`
- L57 _protected prototype_ `void HandleModelBringBindingPathToFocus(const UStateTreeState* State, const FPropertyBindingPath& InBindingPath) const;`
- L59 _protected function_ `void HandleStateAdded(UStateTreeState* , UStateTreeState*)`
- L64 _protected function_ `void HandleStatesRemoved(const TSet<UStateTreeState*>&)`
- L69 _protected function_ `void HandleOnStatesMoved(const TSet<UStateTreeState*>&, const TSet<UStateTreeState*>&)`
- L74 _protected function_ `void HandleOnStateNodesChanged(const UStateTreeState*)`
- L83 _protected prototype_ `void UpdateAsset();` — Resolve the internal editor data and fixup the StateTree nodes.
- L85 _protected prototype_ `TSharedPtr<IDetailsView> GetDetailsView() const;`
- L86 _protected prototype_ `TSharedPtr<IDetailsView> GetAssetDetailsView() const;`
- L88 _protected prototype_ `TSharedPtr<IMessageLogListing> GetMessageLogListing() const;`
- L89 _protected prototype_ `void ShowCompilerTab() const;`
- L91 _protected prototype_ `UStateTree* GetStateTree() const;`
- L97 _protected member_ `uint32 EditorDataHash = 0;` — `UE_DEPRECATED(5.8, "UStateTree::IsEditorDataDirty")`
- L99 _protected member_ `bool bLastCompileSucceeded = true;` — `UE_DEPRECATED(5.8, "UStateTree::CompileStatus")`
- L100 _protected member_ `bool bForceAssetDetailViewToRefresh = false;`
- L102 _protected member_ `mutable FTimerHandle SetObjectTimerHandle;`
- L103 _protected member_ `mutable FTimerHandle HighlightTimerHandle;`
- L105 _protected member_ `TWeakObjectPtr<UStateTree> CachedStateTree = nullptr;`
- L107 _protected member_ `TSharedPtr<FStateTreeBindingExtension> DetailsViewExtensionHandler;`
- L108 _protected member_ `TSharedPtr<FStateTreeBindingsChildrenCustomization> DetailsViewChildrenCustomizationHandler;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorModeToolkit.h` (Public)


#### class `FStateTreeEditorModeToolkit`  
`class FStateTreeEditorModeToolkit : public FModeToolkit`  
_L19-73_
- inherits: `FModeToolkit`
- L23 _public prototype_ `FStateTreeEditorModeToolkit(UStateTreeEditorMode* InEditorMode);`
- L26 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L27 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L29 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;`
- L30 _public prototype_ `virtual void InvokeUI() override;`
- L31 _public prototype_ `virtual void RequestModeUITabs() override;`
- L33 _public prototype_ `virtual void ExtendSecondaryModeToolbar(UToolMenu* InModeToolbarMenu) override;`
- L35 _public prototype_ `UStateTree* GetStateTree() const;`
- L36 _public prototype_ `void OnStateTreeChanged();`
- L39 _protected prototype_ `FSlateIcon GetCompileStatusImage() const;`
- L41 _protected prototype_ `static FSlateIcon GetNewTaskButtonImage();`
- L42 _protected prototype_ `TSharedRef<SWidget> GenerateTaskBPBaseClassesMenu() const;`
- L44 _protected prototype_ `static FSlateIcon GetNewConditionButtonImage();`
- L45 _protected prototype_ `TSharedRef<SWidget> GenerateConditionBPBaseClassesMenu() const;`
- L47 _protected prototype_ `static FSlateIcon GetNewConsiderationButtonImage();`
- L48 _protected prototype_ `TSharedRef<SWidget> GenerateConsiderationBPBaseClassesMenu() const;`
- L50 _protected prototype_ `void OnNodeBPBaseClassPicked(UClass* NodeClass) const;`
- L52 _protected prototype_ `FText GetStatisticsText() const;`
- L53 _protected prototype_ `const FPropertyBindingBindingCollection* GetBindingCollection() const;`
- L55 _protected prototype_ `void UpdateStateTreeOutliner();`
- L57 _protected prototype_ `void HandleTabSpawned(UE::StateTreeEditor::FSpawnedWorkspaceTab SpawnedTab);`
- L58 _protected prototype_ `void HandleTabClosed(UE::StateTreeEditor::FSpawnedWorkspaceTab SpawnedTab);`
- L61 _protected member_ `TWeakObjectPtr<UStateTreeEditorMode> WeakEditorMode;`
- L62 _protected member_ `TSharedPtr<IStateTreeEditorHost> EditorHost;`
- L65 _protected member_ `TSharedPtr<SWidget> StateTreeOutliner = nullptr;` — Tree Outliner
- L66 _protected member_ `TWeakPtr<SDockTab> WeakOutlinerTab = nullptr;`
- L69 _protected prototype_ `void UpdateDebuggerView();`
- L70 _protected member_ `TWeakPtr<SDockTab> WeakDebuggerTab = nullptr;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTreeEditor` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorModule.h` (Public)


#### class `FStateTreeEditorModule`  
`class FStateTreeEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L40-176_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: The public interface to this module
- L44 _public prototype_ `virtual void StartupModule() override;`
- L45 _public prototype_ `virtual void ShutdownModule() override;`
- L49 _public prototype_ `static FStateTreeEditorModule& GetModule();` — Gets this module, will attempt to load and should always exist.
- L52 _public prototype_ `static FStateTreeEditorModule* GetModulePtr();` — Gets this module, will not attempt to load and may not exist.
- L55 _public prototype_ `virtual TSharedRef<IStateTreeEditor> CreateStateTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UStateTree* StateTree);` — Creates an instance of StateTree editor. Only virtual so that it can be called across the DLL boundary.
- L58 _public prototype_ `static void SetDetailPropertyHandlers(IDetailsView& DetailsView);` — Sets the Details View with required State Tree Detail Property Handlers
- L60 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override`
- L64 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L69 _public prototype_ `TSharedPtr<FStateTreeNodeClassCache> GetNodeClassCache();`
- L71 _public prototype_ `DECLARE_EVENT_OneParam(FStateTreeEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L72 _public function_ `FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions()`
- L77 _public prototype_ `DECLARE_EVENT_TwoParams(FStateTreeEditorModule, FOnAssetRegistryTags, TNotNull<const UStateTree*> , FAssetRegistryTagsContext& );`
- L79 _public function_ `FOnAssetRegistryTags& OnAssetRegistryTags()` — Handle GetAssetRegistryTags for a state tree asset.
- L84 _public prototype_ `DECLARE_EVENT_OneParam(FStateTreeEditorModule, FValidateStateTree, TNotNull<UStateTree*> StateTree);`
- L92 _public function_ `FValidateStateTree& OnPreValidateStateTree()` — Handle the validation a state tree asset. This is before the engine validation. The Schema and EditorData will be correctly set. You are allowed to modify the editor data. @note Use the UStateTreeEditorDataExtension::PreValidate for controlling a single asset. @note Use the UStateTreeEditorSchema::PreValidate for controlling a type of state tree asset.
- L104 _public function_ `FValidateStateTree& OnValidateStateTree()` — Handle the validation a state tree asset. Also serves as the "safety net" of fixing up editor data following an editor operation. You are allowed to modify the editor data. @note Use the UStateTreeEditorDataExtension::Validate for controlling a single asset. @note Use the UStateTreeEditorSchema::Validate for controlling a type of state tree asset.
- L109 _public prototype_ `DECLARE_EVENT_OneParam(FStateTreeEditorModule, FPostInternalCompile, const UE::StateTree::Compiler::FPostInternalContext&);`
- L116 _public function_ `FPostInternalCompile& OnPostInternalCompile()` — Handle post internal compilation for a state tree asset. The state tree asset compiled successfully. @note Use the UStateTreeEditorDataExtension::HandlePostInternalCompile for controlling a single asset. @note Use the UStateTreeEditorSchema::HandlePostInternalCompile for controlling a type of state tree asset.
- L122 _public prototype_ `void RegisterEditorDataClass(TNonNullSubclassOf<const UStateTreeSchema> Schema, TNonNullSubclassOf<const UStateTreeEditorData> EditorData);` — Register the editor data type for a specific schema.
- L124 _public prototype_ `void UnregisterEditorDataClass(TNonNullSubclassOf<const UStateTreeSchema> Schema);` — Unregister the editor data type for a specific schema.
- L126 _public prototype_ `TNonNullSubclassOf<UStateTreeEditorData> GetEditorDataClass(TNonNullSubclassOf<const UStateTreeSchema> Schema) const;` — Get the editor data type for a specific schema.
- L129 _public prototype_ `void RegisterEditorSchemaClass(TNonNullSubclassOf<const UStateTreeSchema> Schema, TNonNullSubclassOf<const UStateTreeEditorSchema> EditorSchema);` — Register the editor schema type for a specific schema.
- L131 _public prototype_ `void UnregisterEditorSchemaClass(TNonNullSubclassOf<const UStateTreeSchema> Schema);` — Unregister the editor schema type for a specific schema.
- L133 _public prototype_ `TNonNullSubclassOf<UStateTreeEditorSchema> GetEditorSchemaClass(TNonNullSubclassOf<const UStateTreeSchema> Schema) const;` — Get the editor schema type for a specific schema.
- L136 _private prototype_ `uint32 HandleRequestEditorHash(const UStateTree& InStateTree);`
- L137 _private prototype_ `void HandleCompileIfChanged(TNotNull<UStateTree*> InStateTree);`
- L138 _private prototype_ `void HandleRequestAssetRegistryTags(TNotNull<const UStateTree*> InStateTree, FAssetRegistryTagsContext& Context);`
- L139 _private prototype_ `void HandleStateTreeAssetLoaded(TNotNull<UStateTree*> InStateTree);`
- L140 _private prototype_ `void HandleStateTreeEditorBindingUpdated(TNotNull<UStateTreeEditorData*> InStateTreeEditorData);`
- L141 _private prototype_ `void HandleAppendToStateTreeClassSchema(FAppendToClassSchemaContext& Context);`
- L144 _protected member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L145 _protected member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L146 _protected member_ `TSharedPtr<FStateTreeNodeClassCache> NodeClassCache;`
- L155 _protected member_ `TArray<FEditorTypes> EditorTypes;`
- L158 _protected member_ `TPimplPtr<UE::StateTreeDebugger::FRewindDebuggerPlaybackExtension> RewindDebuggerPlaybackExtension;`
- L159 _protected member_ `TPimplPtr<UE::StateTreeDebugger::FRewindDebuggerTrackCreator> RewindDebuggerTrackCreator;`
- L162 _protected member_ `FDelegateHandle OnPostEngineInitHandle;`
- L164 _protected member_ `FDelegateHandle OnUserDefinedStructReinstancedHandle;` — `UE_DEPRECATED(5.7, "OnUserDefinedStructReinstancedHandle is not used.")`
- L165 _protected member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;`
- L168 _protected member_ `FBlueprintEditorModule::FAdditionalCategoryHandle ContextCategoryHandle;` — Handle for unregistering the categories registered with FBlueprintEditorModule.
- L169 _protected member_ `FBlueprintEditorModule::FAdditionalCategoryHandle InputCategoryHandle;`
- L170 _protected member_ `FBlueprintEditorModule::FAdditionalCategoryHandle OutputCategoryHandle;`
- L172 _protected member_ `FOnAssetRegistryTags AssetRegistryTags;`
- L173 _protected member_ `FValidateStateTree PreValidateStateTree;`
- L174 _protected member_ `FValidateStateTree ValidateStateTree;`
- L175 _protected member_ `FPostInternalCompile PostInternalCompile;`

#### struct `FStateTreeEditorModule::FEditorTypes`  
`struct FEditorTypes`  
_L148-154_
- L150 _public member_ `TWeakObjectPtr<const UClass> Schema;`
- L151 _public member_ `TWeakObjectPtr<const UClass> EditorData;`
- L152 _public member_ `TWeakObjectPtr<const UClass> EditorSchema;`
- L153 _public prototype_ `bool HasData() const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace StateTree` (scope `UE`)
- L23 _namespace_ `namespace Compiler` (scope `UE::StateTree`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace StateTreeDebugger` (scope `UE`)
- L35 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStateTreeEditor, Log, All);`
- L71 _delegate_ `DECLARE_EVENT_OneParam(FStateTreeEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L77 _delegate_ `DECLARE_EVENT_TwoParams(FStateTreeEditorModule, FOnAssetRegistryTags, TNotNull<const UStateTree*> , FAssetRegistryTagsContext& );`
- L84 _delegate_ `DECLARE_EVENT_OneParam(FStateTreeEditorModule, FValidateStateTree, TNotNull<UStateTree*> StateTree);`
- L109 _delegate_ `DECLARE_EVENT_OneParam(FStateTreeEditorModule, FPostInternalCompile, const UE::StateTree::Compiler::FPostInternalContext&);`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorNode.h` (Public)


#### enum `EStateTreeNodeType`  
`enum class EStateTreeNodeType : uint8`  
_L12-20_
- reflection: `UENUM()`
- L14 _public enumerator_ `EnterCondition`
- L15 _public enumerator_ `Evaluator`
- L16 _public enumerator_ `Task`
- L17 _public enumerator_ `TransitionCondition`
- L18 _public enumerator_ `StateParameters`
- L19 _public enumerator_ `PropertyFunction`

#### struct `FStateTreeEditorNode`  
`struct FStateTreeEditorNode`  
_L26-165_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base for Evaluator, Task, Condition, Consideration Utilities, Property Function nodes.
- L31 _public prototype_ `void Reset();` — Resets node and instance fields to their default values.
- L39 _public function_ `template<typename T, typename... TArgs> void InitializeAs(TNotNull<UObject*> InOuter, TArgs&&... InArgs)` — Initializes the node as the given type, resetting any previous state. Handles both instance data and execution runtime data types. @param InOuter Outer object used when creating UObject instance or execution runtime data.
- L54 _public prototype_ `void InitializeAs(TNotNull<UObject*> InOuter, TNotNull<const UScriptStruct*> InNodeStruct);` — Initializes the node with the given struct type, resetting any previous state. Non-templated counterpart to the templated InitializeAs, for use when the node type is only known at runtime. Handles both instance data and execution runtime data types. @param InOuter Outer object used when creating UObject instance or execution runtime data. @param InNodeStruct Node struct type to initialize with.
- L57 _public prototype_ `void ReallocInstanceData(TNotNull<UObject*> InOuter);` — Resets and reallocates instance and execution runtime data to match the current node type, preserving the node ID.
- L72 _public prototype_ `bool FixObjectInstances(TSet<UObject*>& SeenObjects, TNotNull<UObject*> Outer);` — Fixes UObject instance data of the node, ensuring proper outers and making duplicates unique. Creates any missing instance or execution runtime data. SeenObjects is threaded through all nodes in a single traversal so that shared UObject references (e.g. from copy-paste) are detected and made unique on the spot, without a separate pre-pass to collect reference counts. Each node adds its live instance objects to the set after processing, so any later node holding the same pointer can immediately DuplicateObject it. @param SeenObjects Set of UObject instances already assigned to earlier nodes. Updated in place. @param Outer Outer used for re-parenting and creating new instances. @return true if any changes were made.
- L75 _private prototype_ `void InitializeInstanceData(TNotNull<UObject*> InOuter);`
- L83 _public prototype_ `FName GetName() const;` — This is used to name nodes for runtime, as well as for error reporting. If the node has a specified name, used that, or else of return the display name of the node. @return name of the node.
- L89 _public prototype_ `void SetNodeName(FName NewName);` — Sets the name of the node. Resets the cached node name if the name changed. @param NewName Name to set on the node.
- L95 _public function_ `TStructView<FStateTreeNodeBase> GetNode() const` — Get DataView for the node template. @return DataView for the node template
- L104 _public function_ `FGuid GetNodeID() const` — Get ID for the node template, which is different from the ID for the Instance. @return ID for the node template
- L113 _public function_ `FGuid GetInstanceDataID() const` — Get ID for the node instance data, which is different from the ID for the template. @return ID for the instance data
- L118 _public function_ `FStateTreeDataView GetInstance() const`
- L123 _public function_ `FStateTreeDataView GetInstance()`
- L128 _public function_ `FStateTreeDataView GetExecutionRuntimeData() const`
- L133 _public function_ `FStateTreeDataView GetExecutionRuntimeData()`
- L139 _public member_ `FInstancedStruct Node;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Node)`
- L142 _public member_ `FInstancedStruct Instance;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Node)`
- L145 _public member_ `TObjectPtr<UObject> InstanceObject = nullptr;` — `UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Node)`
- L148 _public member_ `FInstancedStruct ExecutionRuntimeData;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Node)`
- L151 _public member_ `TObjectPtr<UObject> ExecutionRuntimeDataObject = nullptr;` — `UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Node)`
- L155 _public member_ `FGuid ID;` — `UPROPERTY(EditDefaultsOnly, Category = Node)` — ID for the node instance.
- L158 _public member_ `uint8 ExpressionIndent = 0;` — `UPROPERTY(EditDefaultsOnly, Category = Node)`
- L161 _public member_ `EStateTreeExpressionOperand ExpressionOperand = EStateTreeExpressionOperand::And;` — `UPROPERTY(EditDefaultsOnly, Category = Node)`
- L164 _private member_ `mutable TOptional<FName> CachedNodeName;`

#### struct `TStateTreeEditorNode`  
`template <typename T> struct TStateTreeEditorNode : public FStateTreeEditorNode`  
_L168-183_
- inherits: `FStateTreeEditorNode`
- L170 _public typedef_ `using NodeType = T;`
- L171 _public function_ `inline T& GetNode()`
- L175 _public function_ `inline typename T::FInstanceDataType& GetInstanceData()`
- L179 _public function_ `inline typename T::FExecutionRuntimeDataType& GetExecutionRuntimeData()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorPropertyBindings.h` (Public)


#### struct `FStateTreeEditorPropertyBindings`  
`struct FStateTreeEditorPropertyBindings : public FPropertyBindingBindingCollection`  
_L23-137_
- reflection: `USTRUCT()`
- inherits: `FPropertyBindingBindingCollection`
- desc: Editor representation of all property bindings in a StateTree
- L28 _public function_ `TConstArrayView<FStateTreePropertyPathBinding> GetBindings() const` — @return const array view to all bindings.
- L34 _public function_ `TArrayView<FStateTreePropertyPathBinding> GetMutableBindings()` — @return array view to all bindings.
- L39 _public function_ `void AddStateTreeBinding(FStateTreePropertyPathBinding&& InBinding)`
- L46 _public prototype_ `virtual int32 GetNumBindableStructDescriptors() const override;`
- L47 _public prototype_ `virtual const FPropertyBindingBindableStructDescriptor* GetBindableStructDescriptorFromHandle(FConstStructView InSourceHandleView) const override;`
- L49 _public prototype_ `virtual int32 GetNumBindings() const override;`
- L50 _public prototype_ `virtual void ForEachBinding(TFunctionRef<void(const FPropertyBindingBinding& Binding)> InFunction) const override;`
- L51 _public prototype_ `virtual void ForEachBinding(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd, TFunctionRef<void(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const override;`
- L52 _public prototype_ `virtual void ForEachMutableBinding(TFunctionRef<void(FPropertyBindingBinding& Binding)> InFunction) override;`
- L53 _public prototype_ `virtual void VisitBindings(TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding)> InFunction) const override;`
- L54 _public prototype_ `virtual void VisitBindings(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd, TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const override;`
- L55 _public prototype_ `virtual void VisitMutableBindings(TFunctionRef<EVisitResult(FPropertyBindingBinding& Binding)> InFunction) override;`
- L65 _public prototype_ `FPropertyBindingPath AddFunctionBinding(const UScriptStruct* InPropertyFunctionNodeStruct, TConstArrayView<FPropertyBindingPathSegment> InSourcePathSegments, const FPropertyBindingPath& InTargetPath);` — Adds binding between PropertyFunction of the provided type and destination path. @param InPropertyFunctionNodeStruct Struct of PropertyFunction. @param InSourcePathSegments Binding source property path segments. @param InTargetPath Binding target property path. @return Constructed binding source property path.
- L74 _public prototype_ `const FStateTreePropertyPathBinding* AddOutputBinding(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath);` — Adds an output binding between source and target path. Output Binding will copy value from target to source @param InSourcePath Binding source property path segments. @param InTargetPath Binding target property path. @return Constructed Binding.
- L84 _public prototype_ `const FStateTreePropertyPathBinding* AddTaskCompletionBinding(const FGuid& SourceTask, const FPropertyBindingPath& TargetPath, UE::StateTree::ETaskCompletionCondition Completion);` — Adds a task completion binding between a task and target delegate listener. Task completion binding, generate a delegate dispatcher when compiled. @param SourceTask The task that will broadcast the delegate. @param TargetPath Listener target property path. @param Completion The condition for the task to broadcast the delegate. @return Constructed Binding.
- L91 _public prototype_ `bool IsDependentOn(TConstArrayView<UStruct*> InStructsDependedOn) const;` — Check if any editor binding is dependent on any of the structs @param InStructsDependedOn Structs to check if any editor binding is dependent on @return true if any editor binding is dependent on any of the passed in structs
- L96 _public prototype_ `TArray<TNotNull<const UStruct*>> GatherDependencies() const;` — Collect all the structs that this editor bindings are dependent on
- L99 _public function_ `template<typename Predicate> TArray<TNotNull<const UStruct*>> GatherDependenciesByPredicate(Predicate Pred) const`
- L122 _public prototype_ `void CacheDependency(const TConstArrayView<TNotNull<const UStruct*>> InDependentStructs);` — Set Dependency for Editor Bindings @param InDependentStructs Structs editor bindings are dependent on
- L125 _protected prototype_ `virtual FPropertyBindingBinding* AddBindingInternal(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) override;`
- L126 _protected prototype_ `virtual void CopyBindingsInternal(const FGuid InFromStructID, const FGuid InToStructID) override;`
- L127 _protected prototype_ `virtual void RemoveBindingsInternal(TFunctionRef<bool(FPropertyBindingBinding&)> InPredicate) override;`
- L128 _protected prototype_ `virtual bool HasBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const override;`
- L129 _protected prototype_ `virtual const FPropertyBindingBinding* FindBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const override;`
- L134 _private member_ `TArray<FStateTreePropertyPathBinding> PropertyBindings;` — `UPROPERTY()`
- L136 _private member_ `TSet<TObjectKey<const UStruct>> CachedDependencies;`

#### class `UStateTreeEditorPropertyBindingsOwner`  
`class UStateTreeEditorPropertyBindingsOwner : public UPropertyBindingBindingCollectionOwner`  
_L141-144_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UPropertyBindingBindingCollectionOwner`

#### class `IStateTreeEditorPropertyBindingsOwner`  
`class IStateTreeEditorPropertyBindingsOwner : public IPropertyBindingBindingCollectionOwner`  
_L146-165_
- inherits: `IPropertyBindingBindingCollectionOwner`
- L156 _public prototype_ `virtual FStateTreeBindableStructDesc FindContextData(const UStruct* ObjectType, const FString ObjectNameHint) const PURE_VIRTUAL(IStateTreeEditorPropertyBindingsOwner::FindContextData, return {}; );` — Finds a bindable context struct based on name and type. @param ObjectType Object type to match @param ObjectNameHint Name to use if multiple context objects of same type are found.
- L159 _public prototype_ `virtual FStateTreeEditorPropertyBindings* GetPropertyEditorBindings() PURE_VIRTUAL(IStateTreeEditorPropertyBindingsOwner::GetPropertyEditorBindings, return nullptr; );` — @return Pointer to editor property bindings.
- L162 _public prototype_ `virtual const FStateTreeEditorPropertyBindings* GetPropertyEditorBindings() const PURE_VIRTUAL(IStateTreeEditorPropertyBindingsOwner::GetPropertyEditorBindings, return nullptr; );` — @return Pointer to editor property bindings.
- L164 _public prototype_ `virtual EStateTreeVisitor EnumerateBindablePropertyFunctionNodes(TFunctionRef<EStateTreeVisitor(const UScriptStruct* NodeStruct, const FStateTreeBindableStructDesc& Desc, const FStateTreeDataView Value)> InFunc) const PURE_VIRTUAL(IStateTreeEditorPropertyBindingsOwner::EnumerateBindablePropertyFunctionNodes, return static_cast<EStateTreeVisitor>(0); );`

#### struct `FStateTreeBindingLookup`  
`struct FStateTreeBindingLookup : public IStateTreeBindingLookup`  
_L171-182_
- inherits: `IStateTreeBindingLookup`
- desc: TODO: We should merge this with IStateTreeEditorPropertyBindingsOwner and FStateTreeEditorPropertyBindings. Currently FStateTreeEditorPropertyBindings is meant to be used as a member for just to store things, IStateTreeEditorPropertyBindingsOwner is meant return model specific stuff, and IStateTreeBindingLookup is used in non-editor code and it cannot be in FStateTreeEditorPropertyBindings because bindings don't know about the owner.
- L173 _public prototype_ `FStateTreeBindingLookup(const IStateTreeEditorPropertyBindingsOwner* InBindingOwner);`
- L175 _public member_ `const IStateTreeEditorPropertyBindingsOwner* BindingOwner = nullptr;`
- L177 _public prototype_ `virtual const FPropertyBindingPath* GetPropertyBindingSource(const FPropertyBindingPath& InTargetPath) const override;`
- L178 _public prototype_ `virtual FText GetPropertyPathDisplayName(const FPropertyBindingPath& InTargetPath, EStateTreeNodeFormatting Formatting) const override;`
- L179 _public prototype_ `virtual FText GetBindingSourceDisplayName(const FPropertyBindingPath& InTargetPath, EStateTreeNodeFormatting Formatting) const override;`
- L180 _public prototype_ `virtual const FProperty* GetPropertyPathLeafProperty(const FPropertyBindingPath& InPath) const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorSchema.h` (Public)


#### enum `EStateTreeTransitionEditingRules`  
`enum class EStateTreeTransitionEditingRules : uint32`  
_L19-29_
- reflection: `UENUM()`
- desc: Rules specific to editing Transitions.
- L22 _public enumerator_ `None = 0` — Previous (UE 5.7) rules
- L26 _public enumerator_ `AllowReactivation = 1 << 0` — When enabled, user can specify re-activation in the editor. See FStateTreeTransition::ReactivateTargetState for more info.
- L28 _public enumerator_ `Default = None`

#### class `UStateTreeEditorSchema`  
`class UStateTreeEditorSchema : public UObject`  
_L35-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Schema describing how a StateTree is edited.
- L41 _public function_ `virtual bool AllowExtensions() const` — @returns True if modifying extensions in the editor is allowed. An extension can be added by code.
- L52 _public function_ `virtual TOptional<FString> GetParametersSchemaClass() const` — @returns the path name of a Property Bag Schema class used by the state tree schema. It is used by the Global Parameters and the State Parameters. The format is "/Script/MyModule.MySchema".
- L62 _public function_ `virtual void PreValidate(TNotNull<UStateTree*> StateTree)` — Validates and applies the schema restrictions on the StateTree. This is before the engine validation. The EditorData will be correctly set.
- L70 _public prototype_ `virtual void Validate(TNotNull<UStateTree*> StateTree);` — Validates and applies the schema restrictions on the StateTree. Also serves as the "safety net" of fixing up editor data following an editor operation.
- L77 _public function_ `virtual bool HandlePostInternalCompile(const UE::StateTree::Compiler::FPostInternalContext& Context)` — Handle compilation for the owning state tree asset. The state tree asset compiled successfully.
- L83 _public function_ `virtual EStateTreeTransitionEditingRules GetTransitionEditingRules(TNotNull<UStateTreeEditorData*> StateTree) const` — Get editing rules for transitions

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace StateTree` (scope `UE`)
- L12 _namespace_ `namespace Compiler` (scope `UE::StateTree`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorSettings.h` (Public)


#### enum `EStateTreeSaveOnCompile`  
`enum class EStateTreeSaveOnCompile : uint8`  
_L11-16_
- reflection: `UENUM()`
- L13 _public enumerator_ `Never UMETA(DisplayName = "Never")`
- L14 _public enumerator_ `SuccessOnly UMETA(DisplayName = "On Success Only")`
- L15 _public enumerator_ `Always UMETA(DisplayName = "Always")`

#### enum `EStateTreeDebuggerTrackNameVerbosity`  
`enum class EStateTreeDebuggerTrackNameVerbosity : uint8`  
_L19-26_
- reflection: `UENUM()`
- L22 _public enumerator_ `Compact UMETA(DisplayName = "Compact")` — Display only the StateTree asset name (e.g. "MyStateTree").
- L25 _public enumerator_ `Verbose UMETA(DisplayName = "Verbose")` — Display the instance name and asset name (e.g. "MyInstance StateTree (MyStateTree)").

#### class `UStateTreeEditorSettings`  
`class UStateTreeEditorSettings : public UDeveloperSettings`  
_L29-76_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- L33 _private function_ `static UStateTreeEditorSettings& Get()`
- L40 _private member_ `EStateTreeSaveOnCompile SaveOnCompile = EStateTreeSaveOnCompile::Never;` — `UPROPERTY(EditAnywhere, config, Category = "Compiler")` — Determines when to save StateTrees post-compile
- L44 _private member_ `EStateTreeDebuggerTrackNameVerbosity DebuggerTrackNameVerbosity = EStateTreeDebuggerTrackNameVerbosity::Compact;` — `UPROPERTY(EditAnywhere, config, Category = "Debugger")` — Controls how StateTree tracks are labeled in the Rewind Debugger. Compact shows only the asset name; Verbose also includes the instance name.
- L52 _private member_ `bool bEnableLegacyDebuggerWindow = false;` — `UPROPERTY(EditAnywhere, config, Category = "Debugger")` — If enabled, debugger window in the StateTree Asset Editor will display all widgets related to the legacy debugger (recording controls, timelines, frame details, etc.). Otherwise, it will display options to link to open RewindDebugger and select a given instance
- L56 _private member_ `bool bShouldDebuggerAutoRecordOnPIE = true;` — `UPROPERTY(EditAnywhere, config, Category = "Debugger", meta = (EditCondition = "bEnableLegacyDebuggerWindow", EditConditionHides))` — If enabled, debugger starts recording information at the start of each PIE session.
- L60 _private member_ `bool bShouldDebuggerResetDataOnNewPIESession = false;` — `UPROPERTY(EditAnywhere, config, Category = "Debugger", meta = (EditCondition = "bEnableLegacyDebuggerWindow", EditConditionHides))` — If enabled, debugger will clear previous tracks at the start of each PIE session.
- L67 _private member_ `bool bRetainNodePropertyValues = false;` — `UPROPERTY(EditAnywhere, config, Experimental, Category = "Experimental")` — If enabled, changing the class of a node will try to copy over values of properties with the same name and type. i.e. if you change one condition for another, and both have a "Target" BB key selector, it'll be kept.
- L71 _protected prototype_ `virtual FText GetSectionText() const override;`
- L72 _protected prototype_ `virtual FText GetSectionDescription() const override;`
- L75 _protected prototype_ `virtual FName GetCategoryName() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorStyle.h` (Public)


#### class `FStateTreeEditorStyle`  
`class FStateTreeEditorStyle : public FStateTreeStyle`  
_L14-29_
- inherits: `FStateTreeStyle`
- L17 _public prototype_ `static FStateTreeEditorStyle& Get();`
- L19 _public prototype_ `static const FSlateBrush* GetBrushForSelectionBehaviorType(EStateTreeStateSelectionBehavior InSelectionBehavior, bool bInHasChildren, EStateTreeStateType InStateType);`
- L24 _protected prototype_ `static void Register();`
- L25 _protected prototype_ `static void Unregister();`
- L28 _private prototype_ `FStateTreeEditorStyle();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorTypes.h` (Public)


#### struct `FStateTreeEditorColorRef`  
`struct FStateTreeEditorColorRef`  
_L18-41_
- reflection: `USTRUCT()`
- desc: Id Struct to uniquely identify an FStateTreeEditorColor instance. An existing FStateTreeEditorColor instance can be found via UStateTreeEditorData::FindColor
- L22 _public prototype_ `FStateTreeEditorColorRef() = default;`
- L24 _public function_ `explicit FStateTreeEditorColorRef(const FGuid& ID) : ID(ID)`
- L29 _public function_ `bool operator==(const FStateTreeEditorColorRef& Other) const`
- L40 _public member_ `FGuid ID;` — `UPROPERTY(EditDefaultsOnly, Category = "Theme")`

#### struct `FStateTreeEditorColor`  
`struct FStateTreeEditorColor`  
_L47-88_
- reflection: `USTRUCT()`
- desc: Struct describing a Color, its display name and a unique identifier to get an instance via UStateTreeEditorData::FindColor
- L51 _public function_ `FStateTreeEditorColor() : ColorRef(FGuid::NewGuid())`
- L56 _public function_ `explicit FStateTreeEditorColor(const FStateTreeEditorColorRef& ColorRef) : ColorRef(ColorRef)`
- L67 _public prototype_ `bool ExportTextItem(FString& OutValueString, const FStateTreeEditorColor& DefaultValue, UObject* OwnerObject, int32 PortFlags, UObject* ExportRootScope) const;` — Export Text Item override where properties marked with meta-data "StructExportTransient" are excluded from the exported string This is so that copy/pasting State Tree Color entries don't have the effect of also copying over these properties into a new entry. Since it works with meta-data, it's editor-only. Side note: The existing "TextExportTransient" / "DuplicateTransient" specifiers apply for uclass properties only
- L69 _public function_ `bool operator==(const FStateTreeEditorColor& Other) const`
- L81 _public member_ `FStateTreeEditorColorRef ColorRef;` — `UPROPERTY(meta=(StructExportTransient))` — ID unique per State Tree Color Entry. Marked as struct export transient so that copy-pasting this entry does not result in the same repeating ID
- L84 _public member_ `FString DisplayName;` — `UPROPERTY(EditDefaultsOnly, Category = "Theme")`
- L87 _public member_ `FLinearColor Color = FLinearColor(0.4f, 0.4f, 0.4f);` — `UPROPERTY(EditDefaultsOnly, Category = "Theme", meta=(HideAlphaChannel))`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeEditorColor> : TStructOpsTypeTraitsBase2<FStateTreeEditorColor>`  
_L91-97_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeEditorColor>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L94-96_

#### struct `FStateTreeEditorDelegateDispatcherCompiledBinding`  
`struct FStateTreeEditorDelegateDispatcherCompiledBinding`  
_L104-113_
- reflection: `USTRUCT()`
- desc: Struct describing a compiled delegate dispatcher. To help with delta cooking/compilation. We want the same generated ID every time the asset compiles.
- L109 _public member_ `FPropertyBindingPath DispatcherPath;` — `UPROPERTY()`
- L112 _public member_ `FStateTreeDelegateDispatcher ID;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L34 _function_ `friend uint32 GetTypeHash(const FStateTreeEditorColorRef& ColorRef)`
- L74 _function_ `friend uint32 GetTypeHash(const FStateTreeEditorColor& InColor)`
- L95 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon9349a8180103`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorWorkspaceTabHost.h` (Public)


#### struct `UE::StateTreeEditor::FMinorWorkspaceTabConfig`  
`struct FMinorWorkspaceTabConfig`  
_L15-22_
- L17 _public member_ `FName ID;`
- L18 _public member_ `FText Label;`
- L19 _public member_ `FText Tooltip;`
- L20 _public member_ `FSlateIcon Icon;`
- L21 _public member_ `FName UISystemID;`

#### struct `UE::StateTreeEditor::FSpawnedWorkspaceTab`  
`struct FSpawnedWorkspaceTab`  
_L24-28_
- L26 _public member_ `FName TabID;`
- L27 _public member_ `TWeakPtr<SDockTab> DockTab;`

#### class `UE::StateTreeEditor::FWorkspaceTabHost`  
`class FWorkspaceTabHost : public TSharedFromThis<FWorkspaceTabHost>`  
_L31-61_
- inherits: `TSharedFromThis<FWorkspaceTabHost>`
- desc: Interface required for re-using the same tab management across different AssetEditors
- L34 _public member_ `static const FLazyName BindingTabId;`
- L35 _public member_ `static const FLazyName DebuggerTabId;`
- L36 _public member_ `static const FLazyName OutlinerTabId;`
- L37 _public member_ `static const FLazyName SearchTabId;`
- L38 _public member_ `static const FLazyName StatisticsTabId;`
- L41 _public prototype_ `virtual ~FWorkspaceTabHost() = default;`
- L43 _public prototype_ `FOnSpawnTab CreateSpawnDelegate(FName TabID);`
- L44 _public prototype_ `TConstArrayView<FMinorWorkspaceTabConfig> GetTabConfigs() const;`
- L46 _public function_ `TConstArrayView<FSpawnedWorkspaceTab> GetSpawnedTabs() const`
- L51 _public prototype_ `TSharedRef<SDockTab> Spawn(FName TabID);`
- L53 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWorkspaceSpawnTab, FSpawnedWorkspaceTab);`
- L54 _public member_ `FOnWorkspaceSpawnTab OnTabSpawned;`
- L55 _public member_ `FOnWorkspaceSpawnTab OnTabClosed;`
- L58 _private prototype_ `TSharedRef<SDockTab> HandleSpawnDelegate(const FSpawnTabArgs& Args, FName TabID);`
- L59 _private prototype_ `void HandleTabClosed(TSharedRef<SDockTab>);`
- L60 _private member_ `TArray<FSpawnedWorkspaceTab> SpawnedTabs;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StateTreeEditor` (scope `UE`)
- L53 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnWorkspaceSpawnTab, FSpawnedWorkspaceTab);`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeFactory.h` (Public)


#### class `UStateTreeFactory`  
`class UStateTreeFactory : public UFactory`  
_L17-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L22 _private prototype_ `virtual bool ConfigureProperties() override;`
- L23 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L26 _private prototype_ `void SetSchemaClass(const TObjectPtr<UClass>& InSchemaClass);`
- L31 _protected member_ `TObjectPtr<UClass> StateTreeSchemaClass;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeNodeClassCache.h` (Public)


#### struct `FStateTreeNodeClassData`  
`struct FStateTreeNodeClassData`  
_L20-69_
- reflection: `USTRUCT()`
- desc: Describes a class or struct. If the class or struct is from a package that is not yet loaded, the data will update on GetStruct/Class/Scripstruct()
- L24 _public prototype_ `FStateTreeNodeClassData() = default;`
- L25 _public prototype_ `FStateTreeNodeClassData(TNotNull<UStruct*> InStruct);`
- L26 _public prototype_ `FStateTreeNodeClassData(const FTopLevelAssetPath& AssetPath);`
- L29 _public prototype_ `FStateTreeNodeClassData(const FString& InClassAssetName, const FString& InClassPackage, const FName InStructName, UStruct* InStruct);` — `UE_DEPRECATED(5.7, "Use the constructor with FTopLevelAssetPath")`
- L32 _public function_ `FName GetStructName() const` — `UE_DEPRECATED(5.7, "Use GetStructPath")`
- L37 _public function_ `const FTopLevelAssetPath& GetStructPath() const`
- L42 _public prototype_ `UStruct* GetStruct(bool bSilent = false);`
- L44 _public function_ `TWeakObjectPtr<UStruct> GetWeakStruct() const`
- L49 _public function_ `UClass* GetClass(bool bSilent = false)`
- L53 _public function_ `UScriptStruct* GetScriptStruct(bool bSilent = false)`
- L58 _public prototype_ `const UStruct* GetInstanceDataStruct(bool bSilent = false);`
- L62 _private member_ `FTopLevelAssetPath StructAssetPath;` — struct or class asset path.
- L65 _private member_ `TWeakObjectPtr<UStruct> CachedStruct;` — Pointer to described struct or class.
- L68 _private member_ `TWeakObjectPtr<const UStruct> CachedInstanceDataStruct;` — Pointer to described node's instance data struct or class.

#### struct `FStateTreeNodeClassCache`  
`struct FStateTreeNodeClassCache`  
_L75-139_
- desc: Caches specified classes or structs and reacts to engine events to keep the lists always up to date. All the derived classes or structs are kept in the cache.
- L77 _public prototype_ `FStateTreeNodeClassCache();`
- L78 _public prototype_ `~FStateTreeNodeClassCache();`
- L81 _public prototype_ `void AddRootStruct(TNotNull<UStruct*> RootStruct);` — Adds a Struct to keep track of
- L84 _public function_ `void AddRootClass(TNotNull<UClass*> RootClass)` — Adds a Class to keep track of
- L90 _public function_ `void AddRootScriptStruct(TNotNull<UScriptStruct*> RootStruct)` — Adds a ScriptStruct to keep track of
- L96 _public prototype_ `void GetStructs(TNotNull<const UStruct*> BaseStruct, TArray<TSharedPtr<FStateTreeNodeClassData>>& AvailableClasses);` — Returns know derived Structs based on provided base. If the base Struct is not added as root Struct, nothing is returned.
- L99 _public function_ `void GetClasses(TNotNull<const UStruct*> BaseClass, TArray<TSharedPtr<FStateTreeNodeClassData>>& AvailableClasses)` — Returns know derived Classes based on provided base. If the base Class is not added as root Class, nothing is returned.
- L105 _public function_ `void GetScripStructs(TNotNull<const UScriptStruct*> BaseStruct, TArray<TSharedPtr<FStateTreeNodeClassData>>& AvailableClasses)` — Returns know derived ScriptStructs based on provided base. If the base struct is not added as root ScriptStruct, nothing is returned.
- L111 _public prototype_ `void InvalidateCache();` — Invalidates the cache, it will be rebuild on next access.
- L114 _protected prototype_ `void OnAssetAdded(const FAssetData& AssetData);`
- L115 _protected prototype_ `void OnAssetRemoved(const FAssetData& AssetData);`
- L116 _protected prototype_ `void OnReloadComplete(EReloadCompleteReason Reason);`
- L133 _private prototype_ `void UpdateBlueprintClass(const FAssetData& AssetData);`
- L134 _private prototype_ `void CacheClasses();`
- L135 _private prototype_ `void CacheClasses(FRootClassContainer& RootClass);`
- L137 _private member_ `TArray<FRootClassContainer> RootClasses;`
- L138 _private member_ `TMap<FString, int32> ClassNameToRootIndex;`

#### struct `FStateTreeNodeClassCache::FRootClassContainer`  
`struct FRootClassContainer`  
_L119-131_
- L121 _public prototype_ `FRootClassContainer() = default;`
- L122 _public function_ `FRootClassContainer(TNotNull<UStruct*> InBaseStruct, int32 InIndex) : BaseStruct(InBaseStruct) , Index(InIndex)`
- L127 _public member_ `TWeakObjectPtr<const UStruct> BaseStruct;`
- L128 _public member_ `TArray<TSharedPtr<FStateTreeNodeClassData>> ClassData;`
- L129 _public member_ `int32 Index = 0;`
- L130 _public member_ `bool bUpdated = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STATETREEEDITORMODULE_API`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreePropertyBindingCompiler.h` (Public)


#### struct `FStateTreePropertyBindingCompiler`  
`struct FStateTreePropertyBindingCompiler`  
_L21-146_
- reflection: `USTRUCT()`
- desc: Helper class to compile editor representation of property bindings into runtime representation. TODO: Better error reporting, something that can be shown in the UI.
- L30 _public prototype_ `[[nodiscard]] bool Init(FStateTreePropertyBindings& InPropertyBindings, FStateTreeCompilerLog& InLog);` — Initializes the compiler to compile copies to specified Property Bindings. @param PropertyBindings - Reference to the Property Bindings where all the batches will be stored. @return true on success.
- L41 _public prototype_ `[[nodiscard]] bool CompileBatch(const FStateTreeBindableStructDesc& TargetStruct, TConstArrayView<FStateTreePropertyPathBinding> PropertyBindings, FStateTreeIndex16 PropertyFuncsBegin, FStateTreeIndex16 PropertyFuncsEnd, int32& OutBatchIndex);` — Compiles a batch of property copies. @param TargetStruct - Description of the structs which contains the target properties. @param PropertyBindings - Array of bindings to compile, all bindings that point to TargetStructs will be added to the batch. @param PropertyFuncsBegin - Index of the first PropertyFunction belonging to this batch. @param PropertyFuncsEnd - Index of the last PropertyFunction belonging to this batch. @param OutBatchIndex - Resulting batch index, if index is INDEX_NONE, no bindings were found and no batch was generated. @return True on success, false on failure.
- L51 _public prototype_ `[[nodiscard]] bool CompileDelegateDispatchers(const FStateTreeBindableStructDesc& SourceStruct, TConstArrayView<FStateTreeEditorDelegateDispatcherCompiledBinding> PreviousDistpatchers, TConstArrayView<FStateTreePropertyPathBinding> DelegateSourceBindings, FStateTreeDataView InstanceDataView);` — Compiles delegates dispatcher for selected struct. @param SourceStruct - Description of the structs which contains the delegate dispatchers. @param PreviousDistpatchers - Array of previous dispatchers IDs. @param DelegateSourceBindings - Array of bindings dispatcher to compile. @param InstanceDataView - View to the instance data @return True on success, false on failure.
- L59 _public prototype_ `[[nodiscard]] bool CompileTaskCompletionDelegateDispatchers(const FStateTreeBindableStructDesc& SourceStruct, TConstArrayView<FStateTreePropertyPathBinding> AllBindings);` — Compiles delegates dispatcher for selected struct. @param SourceStruct - Description of the structs which is the delegate dispatchers when it completes. @param AllBindings - Array of all the bindings. @return True on success, false on failure.
- L68 _public prototype_ `[[nodiscard]] bool CompileDelegateListeners(const FStateTreeBindableStructDesc& TargetStruct, TConstArrayView<FStateTreePropertyPathBinding> DelegateSourceBindings, FStateTreeDataView InstanceDataView);` — Compiles delegates listener for selected struct. @param TargetStruct - Description of the structs which contains the delegate listeners. @param DelegateTargetBindings - Array of bindings listeners to compile. @param InstanceDataView - View to the instance data @return True on success, false on failure.
- L77 _public prototype_ `[[nodiscard]] bool CompileReferences(const FStateTreeBindableStructDesc& TargetStruct, TConstArrayView<FStateTreePropertyPathBinding> PropertyReferenceBindings, FStateTreeDataView InstanceDataView, const TMap<FGuid, const FStateTreeDataView>& IDToStructValue);` — Compiles references for selected struct @param TargetStruct - Description of the structs which contains the target properties. @param PropertyReferenceBindings - Array of bindings to compile, all bindings that point to TargetStructs will be added. @param InstanceDataView - view to the instance data @return True on success, false on failure.
- L80 _public prototype_ `void Finalize();` — Finalizes compilation, should be called once all batches are compiled.
- L88 _public prototype_ `int32 AddSourceStruct(const FStateTreeBindableStructDesc& SourceStruct);` — Adds source struct. When compiling a batch, the bindings can be between any of the defined source structs, and the target struct. Source structs can be added between calls to Compilebatch(). @param SourceStruct - Description of the source struct to add. @return Source struct index.
- L91 _public prototype_ `FStateTreeDelegateDispatcher GetDispatcherFromPath(const FPropertyBindingPath& PathToDispatcher) const;` — @return delegate dispatcher residing behind given path.
- L94 _public prototype_ `FStateTreeDelegateDispatcher GetTaskCompletionDispatcher(FGuid TaskNodeID, UE::StateTree::ETaskCompletionCondition Condition) const;` — @return the task completion delegate dispatcher given task node ID and condition.
- L97 _public prototype_ `FStateTreeDelegateDispatcher GetDispatcherFromBinding(const FStateTreePropertyPathBinding& Binding) const;` — @return the delegate dispatcher (can be a task completion) given the binding.
- L100 _public prototype_ `TConstArrayView<FStateTreeEditorDelegateDispatcherCompiledBinding> GetCompiledDelegateDispatchers() const;` — @return the list of compiled delegate dispatcher.
- L110 _public prototype_ `TConstArrayView<FTaskCompletionDispatcher> GetCompiledTaskCompletionDispatchers() const;` — @return the list of compiled task completion delegate dispatcher.
- L112 _public function_ `const FStateTreeBindableStructDesc* GetSourceStructDescByID(const FGuid& ID) const`
- L119 _public prototype_ `FStateTreeIndex16 GetDispatcherIDFromPath(const FStateTreePropertyPath& PathToDispatcher) const;` — `UE_DEPRECATED(5.6, "Use the version taking FPropertyBindingPath instead")`
- L127 _public member_ `TArray<FStateTreeBindableStructDesc> SourceStructs;` — `UPROPERTY()`
- L136 _public member_ `TArray<FCompiledReference> CompiledReferences;`
- L139 _public member_ `TArray<FStateTreeEditorDelegateDispatcherCompiledBinding> CompiledDelegateDispatchers;` — Dispatcher used by bindings.
- L140 _public member_ `TArray<FTaskCompletionDispatcher> CompiledTaskCompletionDelegateDispatchers;`
- L141 _public member_ `int32 ListenersNum = 0;`
- L143 _public member_ `FStateTreePropertyBindings* PropertyBindings = nullptr;`
- L145 _public member_ `FStateTreeCompilerLog* Log = nullptr;`

#### struct `FStateTreePropertyBindingCompiler::FTaskCompletionDispatcher`  
`struct FTaskCompletionDispatcher`  
_L102-107_
- L104 _public member_ `FGuid TaskNodeID;`
- L105 _public member_ `FStateTreeDelegateDispatcher Dispatcher;`
- L106 _public member_ `UE::StateTree::ETaskCompletionCondition Condition = UE::StateTree::ETaskCompletionCondition::Completes;`

#### struct `FStateTreePropertyBindingCompiler::FCompiledReference`  
`struct FCompiledReference`  
_L130-134_
- desc: Representation of compiled reference.
- L132 _public member_ `FPropertyBindingPath Path;`
- L133 _public member_ `FStateTreeIndex16 Index;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L114 _function_ `return SourceStructs.FindByPredicate([ID](const FStateTreeBindableStructDesc& Structs) { return (Structs.ID == ID); });` (scope `FStateTreePropertyBindingCompiler::GetSourceStructDescByID`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeState.h` (Public)


#### struct `FStateTreeEventDesc`  
`struct FStateTreeEventDesc`  
_L21-65_
- reflection: `USTRUCT()`
- desc: Editor representation of an event description.
- L25 _public prototype_ `FStateTreeEventDesc() = default;`
- L27 _public function_ `FStateTreeEventDesc(FGameplayTag InTag) : Tag(InTag)`
- L33 _public member_ `FGameplayTag Tag;` — `UPROPERTY(EditDefaultsOnly, Category = "Event")` — Event Tag.
- L37 _public member_ `TObjectPtr<const UScriptStruct> PayloadStruct;` — `UPROPERTY(EditDefaultsOnly, Category = "Event")` — Event Payload Struct.
- L41 _public member_ `bool bConsumeEventOnSelect = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Event")` — If set to true, the event is consumed (later state selection cannot react to it) if state selection can be made.
- L43 _public function_ `bool IsValid() const`
- L48 _public function_ `FStateTreeEvent& GetTemporaryEvent()`
- L56 _public function_ `bool operator==(const FStateTreeEventDesc& Other) const`
- L64 _private member_ `FStateTreeEvent TemporaryEvent;` — `UPROPERTY(Transient)` — Temporary event used as a source value in bindings.

#### struct `FStateTreeTransitionDelegateListener`  
`struct FStateTreeTransitionDelegateListener`  
_L71-74_
- reflection: `USTRUCT()`
- desc: StateTree's internal delegate listener used exclusively in transitions.

#### struct `FStateTreeTransition`  
`struct FStateTreeTransition`  
_L80-198_
- reflection: `USTRUCT(BlueprintType)`
- desc: Editor representation of a transition in StateTree
- L86 _public prototype_ `FStateTreeTransition() = default;` — Macro needed to avoid deprecation errors with members being copied or created.
- L87 _public prototype_ `FStateTreeTransition(const EStateTreeTransitionTrigger InTrigger, const EStateTreeTransitionType InType, const UStateTreeState* InState = nullptr);`
- L88 _public prototype_ `FStateTreeTransition(const EStateTreeTransitionTrigger InTrigger, const FGameplayTag InEventTag, const EStateTreeTransitionType InType, const UStateTreeState* InState = nullptr);`
- L89 _public prototype_ `FStateTreeTransition(const FStateTreeTransition&) = default;`
- L90 _public prototype_ `FStateTreeTransition(FStateTreeTransition&&) = default;`
- L91 _public prototype_ `FStateTreeTransition& operator=(const FStateTreeTransition&) = default;`
- L92 _public prototype_ `FStateTreeTransition& operator=(FStateTreeTransition&&) = default;`
- L96 _public function_ `template<typename T, typename... TArgs> TStateTreeEditorNode<T>& AddConditionWithOuter(TNotNull<UStateTreeState*> InState, TArgs&&... InArgs)`
- L106 _public function_ `TStateTreeEditorNode<T>& AddCondition(TArgs&&... InArgs)` — `UE_DEPRECATED(5.8, "Use AddConditionWithOuter that takes a TNotNull<UStateTreeState*> Outer.")`
- L123 _public function_ `FGuid GetEventID() const`
- L128 _public function_ `bool operator==(const FStateTreeTransition& Other) const`
- L133 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L136 _private prototype_ `void OnNodeAdded(TNotNull<UStateTreeState*> InState, FStateTreeEditorNode& EditorNode);`
- L141 _public member_ `EStateTreeTransitionTrigger Trigger = EStateTreeTransitionTrigger::OnStateCompleted;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transition")` — When to try trigger the transition.
- L145 _public member_ `FStateTreeEventDesc RequiredEvent;` — `UPROPERTY(EditDefaultsOnly, Category = "Transition", DisplayName = "Required Event")` — Defines the event required to be present during state selection for the transition to trigger.
- L149 _public member_ `FStateTreeStateLink State;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transition", meta=(DisplayName="Transition To"))` — Transition target state.
- L152 _public member_ `FGuid ID;` — `UPROPERTY(EditDefaultsOnly, Category = "Transition")`
- L156 _public member_ `FStateTreeTransitionDelegateListener DelegateListener;` — `UPROPERTY(EditDefaultsOnly, Category = "Transition", DisplayName = "Delegate")` — Listener to the selected delegate dispatcher.
- L164 _public member_ `EStateTreeTransitionPriority Priority = EStateTreeTransitionPriority::Normal;` — `UPROPERTY(EditDefaultsOnly, Category = "Transition")` — Transition priority when multiple transitions happen at the same time. During transition handling, the transitions are visited from leaf to root. The first visited transition, of highest priority, that leads to a state selection, will be activated.
- L168 _public member_ `bool bDelayTransition = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Transition")` — Delay the triggering of the transition.
- L172 _public member_ `float DelayDuration = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Transition", meta = (EditCondition = "bDelayTransition", UIMin = "0", ClampMin = "0", UIMax = "25", ClampMax = "25", ForceUnits="s"))` — Transition delay duration in seconds.
- L176 _public member_ `float DelayRandomVariance = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Transition", meta = (EditCondition = "bDelayTransition", UIMin = "0", ClampMin = "0", UIMax = "25", ClampMax = "25", ForceUnits="s"))` — Transition delay random variance in seconds.
- L180 _public member_ `TArray<FStateTreeEditorNode> Conditions;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transition", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeConditionBase", BaseClass = "/Script/StateTreeModule.StateTreeConditionBlueprintBase"))` — Expression of conditions that need to evaluate to true to allow transition to be triggered.
- L187 _public member_ `EStateTreeTransitionChangeTypeRules ReactivateTargetState = EStateTreeTransitionChangeTypeRules::Default;` — `UPROPERTY(EditDefaultsOnly, Category = "Transition", meta = (HideEditConditionToggle))` — The target state and all the following states will be reactivated. Their instance data will be reinstantiated and will receive EnterState. Note: Only enabled when target state is within the nested state (Parent or self). As this only changes behavior for nested states.
- L191 _public member_ `bool bTransitionEnabled = true;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")` — True if the Transition is Enabled (i.e. not explicitly disabled in the asset).
- L196 _public member_ `FGameplayTag EventTag_DEPRECATED;` — `UE_DEPRECATED(all, "Use RequiredEvent.Tag instead.")` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStateTreeTransition> : public TStructOpsTypeTraitsBase2<FStateTreeTransition>`  
_L201-207_
- inherits: `TStructOpsTypeTraitsBase2<FStateTreeTransition>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L204-206_

#### struct `FStateTreeStateParameters`  
`struct FStateTreeStateParameters`  
_L211-237_
- reflection: `USTRUCT()`
- L215 _public function_ `void ResetParametersAndOverrides()`
- L223 _public prototype_ `void RemoveUnusedOverrides();` — Removes overrides that do appear in Parameters.
- L226 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditDefaultsOnly, Category = Parameters)`
- L230 _public member_ `TArray<FGuid> PropertyOverrides;` — `UPROPERTY()` — Overrides for parameters.
- L233 _public member_ `bool bFixedLayout = false;` — `UPROPERTY(EditDefaultsOnly, Category = Parameters)`
- L236 _public member_ `FGuid ID;` — `UPROPERTY(EditDefaultsOnly, Category = Parameters, meta = (IgnoreForMemberInitializationTest))`

#### class `UStateTreeState`  
`class UStateTreeState : public UObject, public IStateTreeSchemaProvider`  
_L243-517_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisallowLevelActorReference = true))`
- inherits: `UObject,IStateTreeSchemaProvider`
- desc: Editor representation of a state in StateTree
- L248 _public prototype_ `UStateTreeState(const FObjectInitializer& ObjectInitializer);`
- L251 _public prototype_ `virtual void PostInitProperties() override;`
- L252 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;`
- L253 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L254 _public prototype_ `virtual void PostLoad() override;`
- L255 _public prototype_ `void UpdateParametersFromLinkedSubtree();`
- L256 _public prototype_ `void OnTreeCompiled(const UStateTree& StateTree);`
- L258 _public prototype_ `const UStateTreeState* GetRootState() const;`
- L259 _public prototype_ `UStateTreeState* GetNextSiblingState() const;`
- L260 _public prototype_ `UStateTreeState* GetNextSelectableSiblingState() const;`
- L263 _public prototype_ `FString GetPath() const;` — @return the path of the state as string.
- L266 _public function_ `bool IsParametersPropertyOverridden(const FGuid PropertyID) const` — @return true if the property of specified ID is overridden.
- L272 _public prototype_ `void SetParametersPropertyOverridden(const FGuid PropertyID, const bool bIsOverridden);` — Sets the override status of specified property by ID.
- L275 _public prototype_ `const FInstancedPropertyBag* GetDefaultParameters() const;` — @returns Default parameters from linked state or asset).
- L279 _public prototype_ `FStateTreeStateLink GetLinkToState() const;` — @return state link to this state.
- L282 _public prototype_ `UStateTreeState& AddChildState(const FName ChildName, const EStateTreeStateType StateType = EStateTreeStateType::State);` — Adds child state with specified name.
- L289 _public function_ `template<typename T, typename... TArgs> TStateTreeEditorNode<T>& AddEnterCondition(TArgs&&... InArgs)` — Adds enter condition of specified type. @return reference to the new condition.
- L302 _public function_ `template<typename T, typename... TArgs> TStateTreeEditorNode<T>& AddConsideration(TArgs&&... InArgs)` — Adds enter utility consideration of specified type. @return reference to the new consideration.
- L315 _public function_ `template<typename T, typename... TArgs> TStateTreeEditorNode<T>& AddTask(TArgs&&... InArgs)` — Adds Task of specified type. @return reference to the new Task.
- L324 _private prototype_ `void OnNodeAdded(FStateTreeEditorNode& EditorNode);`
- L328 _public prototype_ `void SetLinkedState(FStateTreeStateLink InStateLink);` — Sets linked state and updates parameters to match the linked state.
- L331 _public prototype_ `void SetLinkedStateAsset(UStateTree* InLinkedAsset);` — Sets linked asset and updates parameters to match the linked asset.
- L337 _public prototype_ `FStateTreeTransition& AddTransition(const EStateTreeTransitionTrigger InTrigger, const EStateTreeTransitionType InType, const UStateTreeState* InState = nullptr);` — Adds Transition. @return reference to the new Transition.
- L342 _public prototype_ `FStateTreeTransition& AddTransition(const EStateTreeTransitionTrigger InTrigger, const FGameplayTag InEventTag, const EStateTreeTransitionType InType, const UStateTreeState* InState = nullptr);` — Adds Transition. @return reference to the new Transition.
- L345 _private prototype_ `void AddTransitionImpl(FStateTreeTransition& Transition);`
- L349 _public function_ `const FStateTreeTransition* GetTransitionByID(const FGuid TransitionID) const`
- L357 _public function_ `const FStateTreeEditorNode* GetNodeByID(const FGuid NodeID) const`
- L389 _public function_ `FGuid GetEventID() const`
- L396 _public prototype_ `virtual TSubclassOf<UStateTreeSchema> GetSchema() const override;` — @return Class of schema used by the state tree containing this state.
- L404 _public member_ `FName Name;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")` — Display name of the State
- L408 _public member_ `FString Description;` — `UPROPERTY(EditDefaultsOnly, Category = "State", meta=(MultiLine))` — Description of the State
- L412 _public member_ `FGameplayTag Tag;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")` — GameplayTag describing the State
- L416 _public member_ `FStateTreeEditorColorRef ColorRef;` — `UPROPERTY(EditDefaultsOnly, Category = "State", DisplayName = "Color")` — Display color of the State
- L420 _public member_ `EStateTreeStateType Type = EStateTreeStateType::State;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")` — Type the State, allows e.g. states to be linked to other States.
- L424 _public member_ `EStateTreeStateSelectionBehavior SelectionBehavior = EStateTreeStateSelectionBehavior::TrySelectChildrenInOrder;` — `UPROPERTY(EditDefaultsOnly, Category = "State")` — How to treat child states when this State is selected.
- L428 _public member_ `EStateTreeTaskCompletionType TasksCompletion = EStateTreeTaskCompletionType::Any;` — `UPROPERTY(EditDefaultsOnly, Category = "State")` — How tasks will complete the state. Only tasks that are considered for completion can complete the state.
- L432 _public member_ `FStateTreeStateLink LinkedSubtree;` — `UPROPERTY(EditDefaultsOnly, Category = "State", Meta=(DirectStatesOnly, SubtreesOnly))` — Subtree to run as extension of this State.
- L436 _public member_ `TObjectPtr<UStateTree> LinkedAsset = nullptr;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")` — Another State Tree asset to run as extension of this State.
- L446 _public member_ `float CustomTickRate = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "State", meta = (EditCondition = "bHasCustomTickRate", ClampMin = 0.0f))` — Tick rate in seconds the state tasks and transitions should tick. If set the state cannot sleep. If set all the other states (children or parents) will also tick at that rate. If more than one active states has a custom tick rate then the smallest custom tick rate wins. If not set, the state will tick every frame unless the state tree is allowed to sleep.
- L450 _public member_ `bool bHasCustomTickRate = false;` — `UPROPERTY(EditDefaultsOnly, Category = "State", meta=(InlineEditConditionToggle))` — Activate the CustomTickRate.
- L457 _public member_ `bool bCopyParameterBindingsOnTick = false;` — `UPROPERTY(EditDefaultsOnly, Category = "State")` — If true, state parameter bindings are copied each task tick, not only when the state is entered or exited. Has no effect on ScheduledTick.
- L461 _public member_ `FStateTreeStateParameters Parameters;` — `UPROPERTY(EditDefaultsOnly, Category = "State")` — Parameters of this state. If the state is linked to another state or asset, the parameters are for the linked state.
- L465 _public member_ `bool bCheckPrerequisitesWhenActivatingChildDirectly = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Enter Conditions")` — Should state's required event and enter conditions be evaluated when transition leads directly to it's child.
- L468 _public member_ `bool bHasRequiredEventToEnter = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Enter Conditions", meta=(InlineEditConditionToggle))`
- L472 _public member_ `FStateTreeEventDesc RequiredEventToEnter;` — `UPROPERTY(EditDefaultsOnly, Category = "Enter Conditions", meta = (EditCondition = "bHasRequiredEventToEnter"))` — Defines the event required to be present during state selection for the state to be selected.
- L476 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditDefaultsOnly, Category = "Utility", meta=(ClampMin=0))` — Weight used to scale the normalized final utility score for this state
- L480 _public member_ `TArray<FStateTreeEditorNode> EnterConditions;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enter Conditions", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeConditionBase", BaseClass = "/Script/StateTreeModule.StateTreeConditionBlueprintBase"))` — Expression of enter conditions that needs to evaluate true to allow the state to be selected.
- L483 _public member_ `TArray<FStateTreeEditorNode> Tasks;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tasks", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeTaskBase", BaseClass = "/Script/StateTreeModule.StateTreeTaskBlueprintBase"))`
- L487 _public member_ `TArray<FStateTreeEditorNode> Considerations;` — `UPROPERTY(EditDefaultsOnly, Category = "Utility", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeConsiderationBase", BaseClass = "/Script/StateTreeModule.StateTreeConsiderationBlueprintBase"))` — Expression used to calculate a selection utility score for state weighing.
- L491 _public member_ `FStateTreeEditorNode SingleTask;` — `UPROPERTY(EditDefaultsOnly, Category = "Task", meta = (BaseStruct = "/Script/StateTreeModule.StateTreeTaskBase", BaseClass = "/Script/StateTreeModule.StateTreeTaskBlueprintBase"))` — Single item used when schema calls for single task per state.
- L494 _public member_ `TArray<FStateTreeTransition> Transitions;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transitions")`
- L497 _public member_ `TArray<TObjectPtr<UStateTreeState>> Children;` — `UPROPERTY(Instanced, BlueprintReadOnly, Category = "State")`
- L500 _public member_ `FGuid ID;` — `UPROPERTY(EditDefaultsOnly, Category = "State", meta = (IgnoreForMemberInitializationTest))`
- L503 _public member_ `bool bExpanded = true;` — `UPROPERTY(meta = (ExcludeFromHash))`
- L506 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditDefaultsOnly, Category = "State")`
- L509 _public member_ `TObjectPtr<UStateTreeState> Parent = nullptr;` — `UPROPERTY(meta = (ExcludeFromHash))`
- L514 _private member_ `TArray<FStateTreeTransition> PreEditTransitions;` — Transaction temporary. Transitions we captured in PreEdit for remove / move comparision
- L516 _private member_ `FDelegateHandle PostCompileHandle;` — Handle for the UE::StateTree::Delegates::OnPostCompile delegate

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L205 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon2cbe525d0103`)
- L352 _function_ `` (scope `UStateTreeState::GetTransitionByID`)

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeTransitionViewModel.h` (Public)


#### struct `FStateTreeTransitionViewModel`  
`struct FStateTreeTransitionViewModel`  
_L16-67_
- desc: Viewmodel for editing state transtions.
- L18 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransitionsAdded, const UStateTreeState* , const TSet<FGuid>& );`
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransitionsRemoved, const UStateTreeState* , const TSet<FGuid>& );`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransitionsMoved, const UStateTreeState* , const TSet<FGuid>& );`
- L21 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransitionModified, const UStateTreeState* , const FGuid& );`
- L26 _public prototype_ `void HandleOnTransitionsAdded(const UStateTreeState* OwningState, const TSet<FGuid>& TransitionIDs) const;` — Fired externally to let the view model know a transition(s) was added.
- L29 _public prototype_ `void HandleOnTransitionsRemoved(const UStateTreeState* OwningState, const TSet<FGuid>& TransitionIDs) const;` — Fired externally to let the view model know a transition(s) was removed.
- L32 _public prototype_ `void HandleOnTransitionsMoved(const UStateTreeState* OwningState, const TSet<FGuid>& TransitionIDs) const;` — Fired externally to let the view model know a transition(s) was moved.
- L35 _public prototype_ `void HandleOnTransitionModified(const UStateTreeState* OwningState, const FGuid& TransitionID) const;` — Fired externally to let the view model know a transition was modified.
- L38 _public function_ `FOnTransitionsAdded& GetOnTransitionsAdded()` — Called each time a transition(s) is added
- L44 _public function_ `FOnTransitionsRemoved& GetOnTransitionsRemoved()` — Called each time a transition(s) is removed.
- L50 _public function_ `FOnTransitionsRemoved& GetOnTransitionsMoved()` — Called each time a transition(s) is moved.
- L56 _public function_ `FOnTransitionModified& GetOnTransitionModified()` — Called each time a transition is modified
- L63 _protected member_ `FOnTransitionsAdded OnTransitionsAdded;`
- L64 _protected member_ `FOnTransitionsRemoved OnTransitionsRemoved;`
- L65 _protected member_ `FOnTransitionsMoved OnTransitionsMoved;`
- L66 _protected member_ `FOnTransitionModified OnTransitionModified;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransitionsAdded, const UStateTreeState* , const TSet<FGuid>& );`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransitionsRemoved, const UStateTreeState* , const TSet<FGuid>& );`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransitionsMoved, const UStateTreeState* , const TSet<FGuid>& );`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTransitionModified, const UStateTreeState* , const FGuid& );`

### `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeViewModel.h` (Public)


#### enum `EStateTreeViewModelInsert`  
`enum class EStateTreeViewModelInsert : uint8`  
_L43-48_
- L45 _public enumerator_ `Before`
- L46 _public enumerator_ `After`
- L47 _public enumerator_ `Into`

#### enum `EStateTreeViewModelColorAdjustment`  
`enum class EStateTreeViewModelColorAdjustment : uint8`  
_L50-57_
- L52 _public enumerator_ `Normal`
- L53 _public enumerator_ `Bright`
- L54 _public enumerator_ `Brighter`
- L55 _public enumerator_ `Dark`
- L56 _public enumerator_ `Darker`

#### enum `FStateTreeViewModelInsert`  
`enum class UE_DEPRECATED(5.6, "Use the enum with the E prefix") FStateTreeViewModelInsert : uint8`  
_L59-64_
- L61 _public enumerator_ `Before`
- L62 _public enumerator_ `After`
- L63 _public enumerator_ `Into`

#### class `FStateTreeViewModel`  
`class FStateTreeViewModel : public FEditorUndoClient, public TSharedFromThis<FStateTreeViewModel>`  
_L69-326_
- inherits: `FEditorUndoClient,TSharedFromThis<FStateTreeViewModel>`
- desc: ModelView for editing StateTreeEditorData.
- L73 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAssetChanged);`
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatesChanged, const TSet<UStateTreeState*>& , const FPropertyChangedEvent& );`
- L75 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateAdded, UStateTreeState* , UStateTreeState* );`
- L76 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatesRemoved, const TSet<UStateTreeState*>& );`
- L77 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatesMoved, const TSet<UStateTreeState*>& , const TSet<UStateTreeState*>& );`
- L78 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateNodesChanged, const UStateTreeState* );`
- L79 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, const TArray<TWeakObjectPtr<UStateTreeState>>& );`
- L80 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBringNodeToFocus, const UStateTreeState* , const FGuid );`
- L81 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBringBindingPathToFocus, const UStateTreeState* , const FPropertyBindingPath& );`
- L83 _public prototype_ `FStateTreeViewModel();`
- L86 _public prototype_ `void Init(UStateTreeEditorData* InTreeData);`
- L89 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L90 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L93 _public prototype_ `void ClearSelection();` — Selection handling.
- L94 _public prototype_ `void SetSelection(UStateTreeState* Selected);`
- L95 _public prototype_ `void SetSelection(const TArray<TWeakObjectPtr<UStateTreeState>>& InSelection);`
- L96 _public prototype_ `bool IsSelected(const UStateTreeState* State) const;`
- L97 _public prototype_ `bool IsChildOfSelection(const UStateTreeState* State) const;`
- L98 _public prototype_ `void GetSelectedStates(TArray<UStateTreeState*>& OutSelectedStates) const;`
- L99 _public prototype_ `void GetSelectedStates(TArray<TWeakObjectPtr<UStateTreeState>>& OutSelectedStates) const;`
- L100 _public prototype_ `bool HasSelection() const;`
- L101 _public prototype_ `UStateTreeState* GetLastSelectedState() const;`
- L103 _public prototype_ `void BringNodeToFocus(UStateTreeState* State, const FGuid NodeID);`
- L104 _public prototype_ `void BringBindingPathToFocus(const FPropertyBindingPath& InBindingPath);`
- L107 _public prototype_ `UStateTreeState* GetViewState() const;` — The view state is the last selected state, or first root if that is invalid. Nullptr if neither of those exist.
- L110 _public prototype_ `const UStateTree* GetStateTree() const;` — Returns associated state tree asset.
- L112 _public prototype_ `const UStateTreeEditorData* GetStateTreeEditorData() const;`
- L113 _public prototype_ `const UStateTreeSchema* GetStateTreeSchema() const;`
- L115 _public prototype_ `const UStateTreeState* GetStateByID(const FGuid StateID) const;`
- L116 _public prototype_ `UStateTreeState* GetMutableStateByID(const FGuid StateID) const;`
- L118 _public prototype_ `const FStateTreeTransition* GetTransitionByID(const FGuid TransitionID) const;`
- L119 _public prototype_ `FStateTreeTransition* GetMutableTransitionByID(const FGuid TransitionID) const;`
- L122 _public prototype_ `TArray<TObjectPtr<UStateTreeState>>* GetSubTrees() const;` — Returns array of subtrees to edit.
- L123 _public prototype_ `int32 GetSubTreeCount() const;`
- L124 _public prototype_ `void GetSubTrees(TArray<TWeakObjectPtr<UStateTreeState>>& OutSubtrees) const;`
- L127 _public prototype_ `void GetLinkStates(FGuid StateID, TArray<FGuid>& LinkingIn, TArray<FGuid>& LinkedOut) const;` — Find the states that are linked to the provided StateID.
- L130 _public prototype_ `UStateTreeState* GetTransitionToState(TNotNull<const UStateTreeState*> TransitionOwningState, FGuid TransitionID) const;` — Find the states that the transition go to.
- L133 _public prototype_ `void SetPersistentExpandedStates(TSet<TWeakObjectPtr<UStateTreeState>>& InExpandedStates);` — Gets and sets StateTree view expansion state store in the asset.
- L134 _public prototype_ `void GetPersistentExpandedStates(TSet<TWeakObjectPtr<UStateTreeState>>& OutExpandedStates);`
- L137 _public prototype_ `void AddState(UStateTreeState* AfterState);` — State manipulation
- L138 _public prototype_ `void AddChildState(UStateTreeState* ParentState);`
- L139 _public prototype_ `void RenameState(UStateTreeState* State, FName NewName);`
- L140 _public prototype_ `void RemoveSelectedStates();`
- L141 _public prototype_ `void CopySelectedStates();`
- L142 _public prototype_ `bool CanPasteStatesFromClipboard() const;`
- L143 _public prototype_ `void PasteStatesFromClipboard(UStateTreeState* AfterState);`
- L144 _public prototype_ `void PasteStatesAsChildrenFromClipboard(UStateTreeState* ParentState);`
- L145 _public prototype_ `void DuplicateSelectedStates();`
- L146 _public prototype_ `void MoveSelectedStatesBefore(UStateTreeState* TargetState);`
- L147 _public prototype_ `void MoveSelectedStatesAfter(UStateTreeState* TargetState);`
- L148 _public prototype_ `void MoveSelectedStatesInto(UStateTreeState* TargetState);`
- L149 _public prototype_ `bool CanEnableStates() const;`
- L150 _public prototype_ `bool CanDisableStates() const;`
- L151 _public prototype_ `bool CanPasteNodesToSelectedStates() const;`
- L152 _public prototype_ `void SetSelectedStatesEnabled(bool bEnable);`
- L155 _public prototype_ `void ForEachParent(TNotNull<UStateTreeState*> State, TFunctionRef<EStateTreeVisitor(UStateTreeState& ParentState)> InFunc) const;` — State utility methods
- L156 _public prototype_ `void ForEachInTransition(TNotNull<UStateTreeState*> State, TFunctionRef<EStateTreeVisitor(FStateTreeTransition& TransitionToState)> InFunc) const;`
- L157 _public prototype_ `void ForEachOutTransition(TNotNull<UStateTreeState*> State, TFunctionRef<EStateTreeVisitor(FStateTreeTransition& TransitionFromState)> InFunc) const;`
- L158 _public prototype_ `void ForEachChild(TNotNull<UStateTreeState*> State, TFunctionRef<EStateTreeVisitor(UStateTreeState& ChildState)> InFunc) const;`
- L160 _public prototype_ `TArray<UStateTreeState*> GetStateParents(TNotNull<UStateTreeState*> State) const;`
- L161 _public prototype_ `TArray<FStateTreeTransition*> GetStateInTransitions(TNotNull<UStateTreeState*> State) const;`
- L162 _public prototype_ `TArray<FStateTreeTransition*> GetStateOutTransitions(TNotNull<UStateTreeState*> State) const;`
- L163 _public prototype_ `TArray<UStateTreeState*> GetStateChildren(TNotNull<UStateTreeState*> State) const;`
- L165 _public prototype_ `const UStateTreeState* GetSourceStateFromTransition(TNotNull<const FStateTreeTransition*> Transition) const;`
- L166 _public prototype_ `const UStateTreeState* GetSourceParentStateFromTransition(TNotNull<const FStateTreeTransition*> Transition) const;`
- L167 _public prototype_ `const UStateTreeState* GetTargetStateFromTransition(TNotNull<const FStateTreeTransition*> Transition) const;`
- L168 _public prototype_ `const UStateTreeState* GetTargetParentStateFromTransition(TNotNull<const FStateTreeTransition*> Transition) const;`
- L171 _public prototype_ `FStateTreeTransition& AddTransition(TNotNull<UStateTreeState*> State, const EStateTreeTransitionTrigger InTrigger, const EStateTreeTransitionType InType, const UStateTreeState* InState = nullptr) const;` — Transition Manipulation
- L172 _public prototype_ `FStateTreeTransition& AddTransition(TNotNull<UStateTreeState*> State, const EStateTreeTransitionTrigger InTrigger, const FGameplayTag InEventTag, const EStateTreeTransitionType InType, const UStateTreeState* InState = nullptr) const;`
- L173 _public prototype_ `void RemoveTransition(TNotNull<UStateTreeState*> State, const FGuid TransitionID);`
- L176 _public prototype_ `FLinearColor GetStateColor(TNotNull<const UStateTreeState*> State, EStateTreeViewModelColorAdjustment ColorAdjustment = EStateTreeViewModelColorAdjustment::Normal) const;` — Color manipulation
- L177 _public prototype_ `FLinearColor GetHierarchyBasedHighlightColor(TNotNull<const UStateTreeState*> State, EStateTreeViewModelColorAdjustment ColorAdjustment = EStateTreeViewModelColorAdjustment::Normal) const;`
- L178 _public prototype_ `FLinearColor GetHierarchyBasedBackgroundColor(TNotNull<const UStateTreeState*> State, EStateTreeViewModelColorAdjustment ColorAdjustment = EStateTreeViewModelColorAdjustment::Normal) const;`
- L180 _public prototype_ `FLinearColor GetColorAdjusted(const FLinearColor& InColor, EStateTreeViewModelColorAdjustment ColorAdjustment) const;`
- L182 _public prototype_ `const FSlateBrush* GetSelectorIcon(TNotNull<const UStateTreeState*> State) const;`
- L183 _public prototype_ `FText GetNodeDescription(const FStateTreeEditorNode& Node, const EStateTreeNodeFormatting Formatting) const;`
- L187 _public prototype_ `void DeleteNode(TWeakObjectPtr<UStateTreeState> State, const FGuid& ID);` — EditorNode and Transition manipulation @todo: support ReplaceWith and Rename
- L188 _public prototype_ `void DeleteAllNodes(TWeakObjectPtr<UStateTreeState> State, const FGuid& ID);`
- L189 _public prototype_ `void CopyNode(TWeakObjectPtr<UStateTreeState> State, const FGuid& ID);`
- L190 _public prototype_ `void CopyAllNodes(TWeakObjectPtr<UStateTreeState> State, const FGuid& ID);`
- L191 _public prototype_ `void PasteNode(TWeakObjectPtr<UStateTreeState> State, const FGuid& ID);`
- L192 _public prototype_ `void PasteNodesToSelectedStates();`
- L193 _public prototype_ `void PasteNodesToStates(TConstArrayView<UStateTreeState*> States);`
- L194 _public prototype_ `void MoveNode(TWeakObjectPtr<UStateTreeState> From, TWeakObjectPtr<UStateTreeState> To, const FGuid& ID);`
- L195 _public prototype_ `void DuplicateNode(TWeakObjectPtr<UStateTreeState> State, const FGuid& ID);`
- L198 _public prototype_ `void NotifyAssetChangedExternally() const;` — Force to update the view externally.
- L199 _public prototype_ `void NotifyStatesChangedExternally(const TSet<UStateTreeState*>& ChangedStates, const FPropertyChangedEvent& PropertyChangedEvent) const;`
- L203 _public prototype_ `bool HasBreakpoint(FGuid ID, EStateTreeBreakpointType Type);`
- L204 _public prototype_ `bool CanProcessBreakpoints() const;`
- L205 _public prototype_ `bool CanAddStateBreakpoint(EStateTreeBreakpointType Type) const;`
- L206 _public prototype_ `bool CanRemoveStateBreakpoint(EStateTreeBreakpointType Type) const;`
- L207 _public prototype_ `ECheckBoxState GetStateBreakpointCheckState(EStateTreeBreakpointType Type) const;`
- L208 _public prototype_ `void HandleEnableStateBreakpoint(EStateTreeBreakpointType Type);`
- L209 _public prototype_ `void ToggleStateBreakpoints(TConstArrayView<TWeakObjectPtr<>> States, EStateTreeBreakpointType Type);`
- L210 _public prototype_ `void ToggleTaskBreakpoint(FGuid ID, EStateTreeBreakpointType Type);`
- L211 _public prototype_ `void ToggleTransitionBreakpoint(TConstArrayView<TNotNull<const FStateTreeTransition*>> Transitions, ECheckBoxState ToggledState);`
- L213 _public prototype_ `UStateTreeState* FindStateAssociatedToBreakpoint(FStateTreeDebuggerBreakpoint Breakpoint) const;`
- L215 _public function_ `TSharedRef<FStateTreeDebugger> GetDebugger() const`
- L220 _public prototype_ `void RemoveAllBreakpoints();`
- L221 _public prototype_ `void RefreshDebuggerBreakpoints();`
- L224 _public prototype_ `bool IsStateActiveInDebugger(const UStateTreeState& State) const;`
- L227 _public function_ `FOnAssetChanged& GetOnAssetChanged()` — Called when the whole asset is updated (i.e. undo/redo).
- L233 _public function_ `FOnStatesChanged& GetOnStatesChanged()` — Called when States are changed (i.e. change name or properties).
- L239 _public function_ `FOnStateAdded& GetOnStateAdded()` — Called each time a state is added.
- L245 _public function_ `FOnStatesRemoved& GetOnStatesRemoved()` — Called each time a states are removed.
- L251 _public function_ `FOnStatesMoved& GetOnStatesMoved()` — Called each time a state is removed.
- L257 _public function_ `FOnStateNodesChanged& GetOnStateNodesChanged()` — Called each time a state's Editor nodes or transitions are changed except from the DetailsView.
- L263 _public function_ `FOnSelectionChanged& GetOnSelectionChanged()` — Called each time the selection changes.
- L268 _public function_ `FOnBringNodeToFocus& GetOnBringNodeToFocus()`
- L273 _public function_ `FOnBringBindingPathToFocus& GetOnBringBindingPathToFocus()`
- L279 _public function_ `FStateTreeTransitionViewModel& GetTransitionViewModel()` — Get View Model for transitions. Holds various callbacks for transtions added / modified / etc.
- L284 _public function_ `const FStateTreeTransitionViewModel& GetTransitionViewModel() const`
- L290 _protected prototype_ `void GetExpandedStatesRecursive(UStateTreeState* State, TSet<TWeakObjectPtr<UStateTreeState>>& ExpandedStates);`
- L292 _protected prototype_ `void MoveSelectedStates(UStateTreeState* TargetState, const EStateTreeViewModelInsert RelativeLocation);`
- L294 _protected prototype_ `void PasteStatesAsChildrenFromText(const FString& TextToImport, UStateTreeState* ParentState, const int32 IndexToInsertAt);`
- L296 _protected prototype_ `void HandleIdentifierChanged(const UStateTree& StateTree) const;`
- L298 _protected prototype_ `void BindToDebuggerDelegates();`
- L300 _protected prototype_ `void PasteNodesToState(TNotNull<UStateTreeEditorData*> InEditorData, TNotNull<UStateTreeState*> InState, UE::StateTreeEditor::FClipboardEditorData& InProcessedClipboard);`
- L302 _protected member_ `TWeakObjectPtr<UStateTreeEditorData> TreeDataWeak;`
- L303 _protected member_ `TSet<TWeakObjectPtr<UStateTreeState>> SelectedStates;`
- L304 _protected member_ `FGuid LastSelectedState;`
- L307 _protected prototype_ `void HandleBreakpointsChanged(const UStateTree& StateTree);`
- L308 _protected prototype_ `void HandlePostCompile(const UStateTree& StateTree);`
- L310 _protected member_ `TSharedRef<FStateTreeDebugger> Debugger;`
- L311 _protected member_ `TArray<FGuid> ActiveStates;`
- L314 _protected member_ `FOnAssetChanged OnAssetChanged;`
- L315 _protected member_ `FOnStatesChanged OnStatesChanged;`
- L316 _protected member_ `FOnStateAdded OnStateAdded;`
- L317 _protected member_ `FOnStatesRemoved OnStatesRemoved;`
- L318 _protected member_ `FOnStatesMoved OnStatesMoved;`
- L319 _protected member_ `FOnStateNodesChanged OnStateNodesChanged;`
- L320 _protected member_ `FOnSelectionChanged OnSelectionChanged;`
- L321 _protected member_ `FOnBringNodeToFocus OnBringNodeToFocus;`
- L322 _protected member_ `FOnBringBindingPathToFocus OnBringBindingPathToFocus;`
- L325 _protected member_ `FStateTreeTransitionViewModel TransitionViewModel;` — Viewmodel for transition modifications

#### class `UStateTreeClipboardBindings`  
`class UStateTreeClipboardBindings : public UObject`  
_L330-336_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UObject`
- desc: Helper class to allow to copy bindings into clipboard.
- L335 _public member_ `TArray<FStateTreePropertyPathBinding> Bindings;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API STATETREEEDITORMODULE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTreeEditor` (scope `UE`)
- L73 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAssetChanged);`
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatesChanged, const TSet<UStateTreeState*>& , const FPropertyChangedEvent& );`
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateAdded, UStateTreeState* , UStateTreeState* );`
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatesRemoved, const TSet<UStateTreeState*>& );`
- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatesMoved, const TSet<UStateTreeState*>& , const TSet<UStateTreeState*>& );`
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateNodesChanged, const UStateTreeState* );`
- L79 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChanged, const TArray<TWeakObjectPtr<UStateTreeState>>& );`
- L80 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBringNodeToFocus, const UStateTreeState* , const FGuid );`
- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBringBindingPathToFocus, const UStateTreeState* , const FPropertyBindingPath& );`
