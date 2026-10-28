# Plugins / MovieRenderPipelineEditor

- module root: `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor`
- headers: 76; symbols: 1294
- symbol kinds: class=88, delegate=16, enum=2, enumerator=9, function=195, macro=25, member=298, namespace=10, prototype=640, struct=9, variable=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AutomationMessages, BlueprintGraph, CinematicCamera, ConsoleVariablesEditor, CoreUObject, DeveloperSettings, EditorFramework, EditorStyle, Engine, GraphEditor, Imath, InputCore, Json, JsonUtilities, Kismet, KismetWidgets, LevelSequence, LevelSequenceEditor, MessageLog, MovieSceneCapture, MovieSceneCaptureDialog, NamingTokensUI, OpenColorIO, OpenColorIOEditor, Projects, ScreenShotComparisonTools, Sequencer, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets, UEOpenExr, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: ContentBrowser, Core, EditorSubsystem, EditorWidgets, FunctionalTesting, MovieRenderPipelineCore, MovieRenderPipelineRenderPasses, MovieRenderPipelineSettings, MovieScene, MovieSceneTools, MovieSceneTracks, PropertyEditor, Settings, TimeManagement

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/AssetDefinition_PipelinePrimaryConfig.h` (Private)


#### class `UAssetDefinition_PipelinePrimaryConfig`  
`class UAssetDefinition_PipelinePrimaryConfig : public UAssetDefinitionDefault`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/AssetDefinition_PipelineQueue.h` (Private)


#### class `UAssetDefinition_PipelineQueue`  
`class UAssetDefinition_PipelineQueue : public UAssetDefinitionDefault`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/AssetDefinition_PipelineShotConfig.h` (Private)


#### class `UAssetDefinition_PipelineShotConfig`  
`class UAssetDefinition_PipelineShotConfig : public UAssetDefinitionDefault`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/ConsoleVariableCustomization.h` (Private)


#### class `FConsoleVariablesDetailsCustomization`  
`class FConsoleVariablesDetailsCustomization : public IPropertyTypeCustomization`  
_L15-281_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes how console variables are displayed in the details pane.
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _protected function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L93 _protected function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L99 _protected function_ `UMoviePipelineConsoleVariableSetting* GetCVarSettingFromHandle(const TSharedPtr<IPropertyHandle>& PropertyHandle) const` — Get a CVar settings object from a property handle. Returned pointer may be invalid if the object does not exist.
- L119 _protected function_ `FMoviePipelineConsoleVariableEntry* GetEntryForHandle(const TSharedPtr<IPropertyHandle>& PropertyHandle) const` — Get a CVar entry object from a property handle. Returned pointer may be invalid if the object does not exist.
- L140 _protected function_ `TWeakPtr<FConsoleVariablesEditorCommandInfo> GetCommandInfoForConsoleVariableEntry(const FMoviePipelineConsoleVariableEntry* InEntry) const`
- L146 _protected function_ `ECheckBoxState GetIsEnabledCheckBoxState(TSharedRef<IPropertyHandle> PropertyHandle) const`
- L157 _protected function_ `void OnIsEnabledCheckBoxStateChanged(ECheckBoxState NewState, TSharedRef<IPropertyHandle> PropertyHandle)`
- L166 _protected function_ `bool IsEnabled(TSharedRef<IPropertyHandle> InIsEnabledPropertyHandle) const`
- L177 _protected function_ `FText GetConsoleVariableText(TSharedRef<IPropertyHandle> PropertyHandle) const`
- L188 _protected function_ `void OnConsoleVariableNameTextChanged(const FText& NewText, TSharedRef<IPropertyHandle> PropertyHandle)`
- L196 _protected function_ `float GetConsoleVariableValue(TSharedRef<IPropertyHandle> PropertyHandle) const`
- L240 _protected function_ `void OnConsoleVariableValueChanged(float Value, TSharedRef<IPropertyHandle> PropertyHandle)`
- L248 _protected function_ `void OnConsoleVariableValueCommitted(float Value, ETextCommit::Type CommitType, TSharedRef<IPropertyHandle> PropertyHandle)`
- L253 _protected function_ `FText GetConsoleVariableTooltip(TSharedRef<IPropertyHandle> StructPropertyHandle) const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "SMoviePipelineEditor"`
- L33 _function_ `` (scope `FConsoleVariablesDetailsCustomization::CustomizeHeader`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/ConsoleVariableSettingCustomization.h` (Private)


#### class `FConsoleVariablesSettingDetailsCustomization`  
`class FConsoleVariablesSettingDetailsCustomization : public IDetailCustomization`  
_L24-176_
- inherits: `IDetailCustomization`
- desc: Customize how properties in UMoviePipelineConsoleVariableSetting appear in the details panel.
- L27 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L32 _public function_ `static void AddConsoleVariablePresetRowsToGroup(const TScriptInterface<IMovieSceneConsoleVariableTrackInterface>& InCVarPreset, IDetailGroup& InGroup, IDetailLayoutBuilder* InDetailBuilder, const TAttribute<bool>& InRowEnabledAttr, const FGetCVarMenu& InGetCVarMenuDelegate)`
- L91 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`
- L110 _protected function_ `UMoviePipelineConsoleVariableSetting* GetCVarSettingFromHandle(const TSharedPtr<IPropertyHandle>& PropertyHandle) const`
- L129 _protected function_ `void GeneratePresetGroup(TSharedRef<IPropertyHandle> ElementProperty, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout)`

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "SMoviePipelineEditor"`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FGetCVarMenu, const FString&);` — Delegate that gets the menu widget associated with a specific cvar.
- L21 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FGetCVarMenu, const FString&);` — Delegate that gets the menu widget associated with a specific cvar.
- L104 _function_ `` (scope `FConsoleVariablesSettingDetailsCustomization::CustomizeDetails`)
- L162 _function_ `` (scope `FConsoleVariablesSettingDetailsCustomization::GeneratePresetGroup`)
- L167 _function_ `` (scope `FConsoleVariablesSettingDetailsCustomization::GeneratePresetGroup::__anonbddfc8600202`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphApplyCVarPresetNodeCustomization.h` (Private)


#### class `FMovieGraphApplyCVarPresetNodeCustomization`  
`class FMovieGraphApplyCVarPresetNodeCustomization : public IDetailCustomization`  
_L23-181_
- inherits: `IDetailCustomization`
- desc: Customize how the Apply Console Variable Preset node appears in the details panel.
- L26 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L33 _protected function_ `static void CreateOverrideViaSetCVarValueNode(const TWeakObjectPtr<UMovieGraphApplyCVarPresetNode> InPresetNode, const FString& InCVarName)` — Creates a new Set CVar Value node (overriding the cvar with the provided name) connected to the given preset node.
- L85 _protected function_ `static TSharedRef<SWidget> CreateCVarOverrideMenu(const FString& InCVarName, TWeakObjectPtr<UMovieGraphApplyCVarPresetNode> InPresetNode)` — Creates the override menu for a specific cvar row.
- L105 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L110 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`

#### Free symbols / members of external scopes

- L20 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`
- L72 _function_ `ConsoleVariables.FindByPredicate([&InCVarName](const TTuple<FString, FString>& InPair) { return InPair.Key == InCVarName; });` (scope `FMovieGraphApplyCVarPresetNodeCustomization::CreateOverrideViaSetCVarValueNode`)
- L92 _function_ `` (scope `FMovieGraphApplyCVarPresetNodeCustomization::CreateCVarOverrideMenu`)
- L119 _function_ `` (scope `FMovieGraphApplyCVarPresetNodeCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphCollectionsCustomization.h` (Private)


#### class `FMovieGraphCollectionDragDropOp`  
`class FMovieGraphCollectionDragDropOp : public FDecoratedDragDropOp`  
_L16-47_
- inherits: `FDecoratedDragDropOp`
- desc: Drag/drop operation that contains data about a condition group or condition group query being dragged.
- L19 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FMovieGraphCollectionDragDropOp, FDecoratedDragDropOp);`
- L21 _public prototype_ `FMovieGraphCollectionDragDropOp(const bool bIsConditionGroup, const int32 InitialIndex, TWeakObjectPtr<UMovieGraphConditionGroup> InWeakOwningConditionGroup = nullptr);`
- L24 _public prototype_ `void Init();` — Initialize the operation.
- L27 _public prototype_ `void SetValidTarget(const bool bIsValidTarget);` — Set whether the operation is currently valid or not.
- L30 _public prototype_ `int32 GetIndex() const;` — The index of the condition group or condition group query being dragged.
- L33 _public prototype_ `bool IsConditionGroup() const;` — Whether this operation represents a condition group (true) or condition group query (false).
- L36 _public prototype_ `TWeakObjectPtr<UMovieGraphConditionGroup> GetOwningConditionGroup() const;` — Get the condition group that owns the query being dragged (nullptr for dragging a condition group).
- L40 _private member_ `bool bIsConditionGroup;` — Whether this is a condition group (true) or condition group query (false) being dragged.
- L43 _private member_ `int32 InitialIndex;` — The index of the condition group or condition group query being dragged.
- L46 _private member_ `TWeakObjectPtr<UMovieGraphConditionGroup> OwningConditionGroup;` — The condition group that owns the query being dragged (this being valid implies !bIsConditionGroup).

#### class `FMovieGraphCollectionDragDropHandler`  
`class FMovieGraphCollectionDragDropHandler : public IDetailDragDropHandler`  
_L50-79_
- inherits: `IDetailDragDropHandler`
- desc: Handler for customizing the drag/drop functionality of condition groups and condition group queries.
- L53 _public prototype_ `FMovieGraphCollectionDragDropHandler(const bool bIsConditionGroup, IDetailLayoutBuilder* InDetailBuilder, UMovieGraphCollection* InCollection, const int32 ConditionGroupIndex, TWeakObjectPtr<UMovieGraphConditionGroup> InWeakConditionGroup, const int32 ConditionGroupQueryIndex);`
- L56 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation() const override;`
- L57 _public prototype_ `virtual bool AcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const override;`
- L58 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone) const override;`
- L63 _private member_ `bool bIsConditionGroup;` — Whether the handler is targeting a condition group (true) or query (false).
- L66 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;` — The layout builder that the handler was created from.
- L69 _private member_ `TWeakObjectPtr<UMovieGraphCollection> WeakCollection;` — The collection that owns the condition group (or query).
- L72 _private member_ `int32 ConditionGroupIndex;` — The index of the condition group targeted by the handler.
- L75 _private member_ `TWeakObjectPtr<UMovieGraphConditionGroup> WeakConditionGroup;` — The condition group that is targeted by the handler.
- L78 _private member_ `int32 ConditionGroupQueryIndex;` — The index of the query targeted by the handler.

#### class `FMovieGraphConditionGroupQueryBuilder`  
`class FMovieGraphConditionGroupQueryBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FMovieGraphConditionGroupQueryBuilder>`  
_L82-111_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FMovieGraphConditionGroupQueryBuilder>`
- desc: Custom node builder for condition group queries. Displays each query as a child.
- L85 _public prototype_ `FMovieGraphConditionGroupQueryBuilder(IDetailLayoutBuilder* InDetailBuilder, TSharedRef<IPropertyHandle> InConditionGroupQueryProperty, int32 ConditionGroupQueryIndex, const TWeakObjectPtr<UMovieGraphConditionGroup>& InWeakConditionGroup);`
- L88 _public prototype_ `virtual FName GetName() const override;`
- L89 _public function_ `virtual bool InitiallyCollapsed() const override`
- L90 _public function_ `virtual bool RequiresTick() const override`
- L91 _public function_ `virtual void Tick(float DeltaTime) override`
- L92 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L93 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L97 _private prototype_ `void AddQueryTypeWidgets(TWeakObjectPtr<UMovieGraphConditionGroupQueryBase> WeakQuery, IDetailChildrenBuilder& ChildrenBuilder) const;`
- L101 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;` — The layout builder that this node builder was created from.
- L104 _private member_ `TSharedPtr<IPropertyHandle> ConditionGroupQueryProperty;` — The property for the condition group query being displayed.
- L107 _private member_ `int32 ConditionGroupQueryIndex;` — The index of the query represented by this builder.
- L110 _private member_ `TWeakObjectPtr<UMovieGraphConditionGroup> WeakConditionGroup;` — The condition group that the query belongs to.

#### class `FMovieGraphConditionGroupBuilder`  
`class FMovieGraphConditionGroupBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FMovieGraphConditionGroupBuilder>`  
_L114-141_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FMovieGraphConditionGroupBuilder>`
- desc: Custom node builder for condition groups. The condition group is added as the header, and children are added as FMovieGraphConditionGroupQueryBuilder rows.
- L117 _public prototype_ `FMovieGraphConditionGroupBuilder(IDetailLayoutBuilder* InDetailBuilder, TSharedRef<IPropertyHandle> InConditionGroupProperty, const uint32 InConditionGroupIndex, TWeakObjectPtr<UMovieGraphCollection>& InWeakCollection);`
- L120 _public prototype_ `virtual FName GetName() const override;`
- L121 _public function_ `virtual bool InitiallyCollapsed() const override`
- L122 _public function_ `virtual bool RequiresTick() const override`
- L123 _public function_ `virtual void Tick(float DeltaTime) override`
- L124 _public function_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override`
- L125 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L126 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L131 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;` — The layout builder that this node builder was created from.
- L134 _private member_ `TSharedPtr<IPropertyHandle> ConditionGroupProperty;` — The property for the condition group being displayed.
- L137 _private member_ `uint32 ConditionGroupIndex;` — The index of the condition group represented by this builder.
- L140 _private member_ `TWeakObjectPtr<UMovieGraphCollection> WeakCollection;` — The collection that the condition groups belong to.

#### class `SMovieGraphCollectionTreeOpTypeWidget`  
`class SMovieGraphCollectionTreeOpTypeWidget final : public SCompoundWidget`  
_L146-186_
- inherits: `SCompoundWidget`
- desc: A widget which controls the op type for a condition group or condition group query.
- L149 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphCollectionTreeOpTypeWidget)`
- L150 _public prototype_ `SLATE_ATTRIBUTE(bool, IsConditionGroup) SLATE_ATTRIBUTE(TWeakObjectPtr<UMovieGraphConditionGroup>, WeakConditionGroup) SLATE_ATTRIBUTE(TWeakObjectPtr<UMovieGraphConditionGroupQueryBase>, WeakConditionGroupQuery) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L159 _private member_ `bool bIsConditionGroup = false;` — Whether this widget is associated with a condition group (else a condition group query).
- L162 _private member_ `TWeakObjectPtr<UMovieGraphConditionGroup> WeakConditionGroup;` — The condition group associated with this widget (if any).
- L165 _private member_ `TWeakObjectPtr<UMovieGraphConditionGroupQueryBase> WeakConditionGroupQuery;` — The condition group query associated with this widget (if any).
- L170 _private prototype_ `template<typename T> static TArray<FName>* GetOpTypes();` — Gets the names of all op types available.
- L173 _private prototype_ `TSharedRef<SWidget> GetOpTypeContents(const FName& InOpName, const bool bIsConditionGroupOp) const;` — Gets a widget (icon + name) representing the given op.
- L176 _private prototype_ `bool IsWidgetEnabled() const;` — Whether this widget is currently enabled.
- L179 _private prototype_ `void SetOpType(const FName InNewOpType, ESelectInfo::Type SelectInfo) const;` — Sets the op type for the condition group or condition group query.
- L182 _private prototype_ `FName GetCurrentConditionGroupOpType() const;` — Gets the currently-assigned op type for the condition group.
- L185 _private prototype_ `FName GetCurrentConditionGroupQueryOpType() const;` — Gets the currently-assigned op type for the condition group query.

#### class `SMovieGraphCollectionTreeAddQueryContentWidget`  
`class SMovieGraphCollectionTreeAddQueryContentWidget final : public SCompoundWidget`  
_L192-200_
- inherits: `SCompoundWidget`
- desc: A widget which displays the "Add" menu for a condition group query, allowing the user to add content to the query (like an actor). The appearance of the widget and behavior of the menu is largely delegated to the query itself.
- L195 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphCollectionTreeAddQueryContentWidget)`
- L196 _public prototype_ `SLATE_ATTRIBUTE(TWeakObjectPtr<UMovieGraphConditionGroupQueryBase>, WeakQuery) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

#### class `SMovieGraphCollectionTreeQueryTypeSelectorWidget`  
`class SMovieGraphCollectionTreeQueryTypeSelectorWidget final : public SCompoundWidget`  
_L205-243_
- inherits: `SCompoundWidget`
- desc: A ComboBox widget which displays the available condition group query types and updates the condition group when one is selected.
- L208 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnQueryTypeChanged, TWeakObjectPtr<UMovieGraphConditionGroupQueryBase>);`
- L210 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphCollectionTreeQueryTypeSelectorWidget)`
- L211 _public prototype_ `SLATE_ATTRIBUTE(TWeakObjectPtr<UMovieGraphConditionGroup>, WeakConditionGroup) SLATE_ATTRIBUTE(TWeakObjectPtr<UMovieGraphConditionGroupQueryBase>, WeakQuery) SLATE_EVENT(FOnQueryTypeChanged, OnQueryTypeChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L220 _private prototype_ `static TArray<UClass*>* GetAvailableQueryTypes();` — Gets the query types which are available to be selected and added to the condition group.
- L223 _private prototype_ `TSharedRef<SWidget> GetQueryTypeContents(UClass* InTypeClass) const;` — Gets the widget that displays an individual query type.
- L226 _private prototype_ `FText GetCurrentQueryTypeDisplayName() const;` — Gets the display name of the currently selected query.
- L229 _private prototype_ `UClass* GetCurrentQueryType() const;` — Gets the UClass associated with the currently selected query.
- L232 _private prototype_ `void SetQueryType(UClass* InNewQueryType, ESelectInfo::Type SelectInfo);` — Updates the query to the query type which was selected.
- L236 _private member_ `TWeakObjectPtr<UMovieGraphConditionGroup> WeakConditionGroup = nullptr;` — The condition group that the query belongs to.
- L239 _private member_ `TWeakObjectPtr<UMovieGraphConditionGroupQueryBase> WeakQuery = nullptr;` — The condition group query associated with this widget.
- L242 _private member_ `FOnQueryTypeChanged OnQueryTypeChanged;` — Called when the query type changes.

#### class `FMovieGraphCollectionsCustomization`  
`class FMovieGraphCollectionsCustomization final : public IDetailCustomization`  
_L246-263_
- inherits: `IDetailCustomization`
- desc: Customize how the Collection node appears in the details panel.
- L249 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L253 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L254 _protected prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L259 _private member_ `TWeakObjectPtr<UMovieGraphCollection> WeakCollection;` — The collection being displayed.
- L262 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailBuilder;` — The details builder associated with the customization.

#### Free symbols / members of external scopes

- L208 _delegate_ `DECLARE_DELEGATE_OneParam(FOnQueryTypeChanged, TWeakObjectPtr<UMovieGraphConditionGroupQueryBase>);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphCustomizationUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieRenderPipelineEditor` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::MovieRenderPipelineEditor`)
- L16 _prototype_ `void AddVariableAssignments(TArray<TObjectPtr<UMovieJobVariableAssignmentContainer>>& InVariableAssignments, IDetailCategoryBuilder& InCategory, IDetailLayoutBuilder* InDetailBuilder);` (scope `UE::MovieRenderPipelineEditor::Private`) — Adds InVariableAssignments to the given InCategory. For each graph that is used within InVariableAssignments, a dedicated sub-category (named the name of the graph) is added under the given category.
- L19 _prototype_ `void AddTokenAutocompleteToPropertyRow(IDetailPropertyRow* InPropertyRow);` (scope `UE::MovieRenderPipelineEditor::Private`) — Adds the Naming Tokens token autocomplete widget to the given property row.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphExecuteScriptNodeCustomization.h` (Private)


#### class `FMovieGraphExecuteScriptNodeCustomization`  
`class FMovieGraphExecuteScriptNodeCustomization : public IDetailCustomization`  
_L13-73_
- inherits: `IDetailCustomization`
- desc: Customize how the Execute Script node appears in the details panel.
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L23 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L28 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`
- L36 _function_ `` (scope `FMovieGraphExecuteScriptNodeCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphLightModifierCustomization.h` (Private)


#### class `FMovieGraphLightModifierCustomization`  
`class FMovieGraphLightModifierCustomization final : public IDetailCustomization`  
_L14-76_
- inherits: `IDetailCustomization`
- desc: Customize how the Light Modifier node appears in the details panel.
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L21 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L22 _protected prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L39 _private prototype_ `TWeakInterfacePtr<IMovieGraphModifierNodeInterface> GetSelectedModifierNode() const;` — Gets the selected modifier node that this customization is displaying.
- L42 _private prototype_ `TSharedRef<SWidget> GetCustomMenuContents(const TWeakInterfacePtr<IMovieGraphModifierNodeInterface> InWeakModifierNode) const;` — Gets the contents of the "Custom" menu.
- L48 _private prototype_ `void InitializeIntensityProperty(const FName& InIntensityPropertyName, const FName& InIntensityUnitsPropertyName);` — Initializes the Intensity-related property to display correctly with its associated Intensity Units property. This mostly initializes the metadata on the Intensity-related property, but may initialize other aspects of the property as well.
- L54 _private prototype_ `void ShowPropertyConditionally(FName IntensityPropertyName, EMovieGraphLightModifierIntensityMethod ShowWithMethod);` — Adds a Visibility lambda to the given property, which will conditionally show the property only if the node's Intensity Method matches the value provided in ShowWithMethod (eg, only show the property when the Intensity Method is set to PointRectSpot).
- L57 _private prototype_ `void OnIntensityUnitsValuePreChange(FName IntensityUnitsPropertyName);` — Handles value pre-change logic for the Intensity Units property.
- L60 _private prototype_ `void OnIntensityUnitsValueChange(FName IntensityPropertyName, FName IntensityUnitsPropertyName) const;` — Handles value-change logic for the Intensity Units property.
- L65 _private prototype_ `TArray<FCustomLightingPropertyInfo> GetCustomLightingProperties() const;` — Gets all of the properties that should be displayed in the "Custom" properties menu.
- L69 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailBuilder;` — The details builder associated with the customization.
- L72 _private member_ `TSharedPtr<SMovieGraphModifierCollectionsList> CollectionsList;` — Displays the collections which have been chosen.
- L75 _private member_ `ELightUnits PreviousIntensityUnits = ELightUnits::Candelas;` — The value of the Intensity Units property before it changes.

#### struct `FMovieGraphLightModifierCustomization::FCustomLightingPropertyInfo`  
`struct FCustomLightingPropertyInfo`  
_L27-36_
- desc: Stores information about a property returned from GetCustomLightingProperties().
- L29 _public prototype_ `FCustomLightingPropertyInfo() = delete;`
- L30 _public prototype_ `FCustomLightingPropertyInfo(UClass* LightActorClass, UClass* LightComponentClass, FProperty* LightProperty, const FString& LightPropertyCategory);`
- L32 _public member_ `UClass* LightActorClass = nullptr;`
- L33 _public member_ `UClass* LightComponentClass = nullptr;`
- L34 _public member_ `FProperty* LightProperty = nullptr;`
- L35 _public member_ `FString LightPropertyCategory;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphMaterialParameterCollectionModifierNodeCustomization.h` (Private)


#### class `FMovieGraphMaterialParameterCollectionModifierNodeCustomization`  
`class FMovieGraphMaterialParameterCollectionModifierNodeCustomization : public IDetailCustomization`  
_L16-99_
- inherits: `IDetailCustomization`
- desc: Customizes how the Material Parameter Collection Modifier node appears in the details panel.
- L19 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L26 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L31 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`
- L45 _function_ `` (scope `FMovieGraphMaterialParameterCollectionModifierNodeCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphMemberCustomization.h` (Private)


#### class `FMovieGraphMemberCustomization`  
`class FMovieGraphMemberCustomization : public IDetailCustomization`  
_L22-292_
- inherits: `IDetailCustomization`
- desc: Customize how members for a graph appear in the details panel.
- L25 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L32 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L37 _protected function_ `void OnNameChanged(const FText& InText, UMovieGraphMember* MovieGraphMember) const`
- L48 _protected function_ `void OnNameCommitted(const FText& InText, ETextCommit::Type Arg, UMovieGraphMember* MovieGraphMember) const`
- L58 _protected function_ `bool IsPinTypeAllowed(const FEdGraphPinType& InPinType) const`
- L69 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`
- L291 _private member_ `TSharedPtr<SEditableTextBox> NameEditableTextBox;` — Text box for the "Name" property.

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`
- L78 _function_ `` (scope `FMovieGraphMemberCustomization::CustomizeDetails`)
- L163 _function_ `.Text_Lambda([MemberObject]() { return FText::FromString(MemberObject->GetMemberName()); }) .OnTextChanged(this, &FMovieGraphMemberCustomization::OnNameChanged, MemberObject) .OnTextCommitted(this, &FMovieGraphMemberCustomization::OnNameCommitted, MemberObject) .SelectAllTextWhenFocused(true) .Font(IDetailLayoutBuilder::GetDetailFont()) ];` (scope `FMovieGraphMemberCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphMetadataAttributeCustomization.h` (Private)


#### class `FMovieGraphMetadataAttributeCustomization`  
`class FMovieGraphMetadataAttributeCustomization : public IPropertyTypeCustomization`  
_L17-120_
- inherits: `IPropertyTypeCustomization`
- desc: Customize how a metadata attribute (FMovieGraphMetadataAttribute) appears in the details panel.
- L21 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L27 _protected member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L29 _protected function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L86 _protected function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L90 _protected function_ `ECheckBoxState IsCheckBoxChecked(TSharedRef<IPropertyHandle> PropertyHandle) const`
- L101 _protected function_ `void OnCheckBoxCheckStateChanged(ECheckBoxState NewState, TSharedRef<IPropertyHandle> PropertyHandle)`
- L110 _protected function_ `bool IsEnabled(TSharedRef<IPropertyHandle> InIsEnabledPropertyHandle) const`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "FMovieGraphMetadataAttributeCustomization"`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphModifiersCustomization.h` (Private)


#### class `FMovieGraphModifiersCustomization`  
`class FMovieGraphModifiersCustomization final : public IDetailCustomization`  
_L12-33_
- inherits: `IDetailCustomization`
- desc: Customize how the Modifier node appears in the details panel.
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L19 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L20 _protected prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L25 _private prototype_ `TWeakInterfacePtr<IMovieGraphModifierNodeInterface> GetSelectedModifierNode() const;` — Gets the selected modifier node that this customization is displaying.
- L29 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailBuilder;` — The details builder associated with the customization.
- L32 _private member_ `TSharedPtr<SMovieGraphModifierCollectionsList> CollectionsList;` — Displays the collections which have been chosen.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphMultiLayerEXRNodeCustomization.h` (Private)


#### class `FMovieGraphMultiLayerEXRNodeCustomization`  
`class FMovieGraphMultiLayerEXRNodeCustomization : public IDetailCustomization`  
_L13-74_
- inherits: `IDetailCustomization`
- desc: Customizes how EXR output node properties appear in the details panel.
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L23 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L28 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`

#### Free symbols / members of external scopes

- L39 _function_ `` (scope `FMovieGraphMultiLayerEXRNodeCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphNamedResolutionCustomization.h` (Private)


#### class `FMovieGraphNamedResolutionCustomization`  
`class FMovieGraphNamedResolutionCustomization : public IPropertyTypeCustomization`  
_L13-157_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes how named resolutions are displayed in the details pane.
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L29 _protected prototype_ `void UpdateComboBoxOptions();` — Update ComboBoxOptions with the latest values in the Project Settings, and adds the "Custom" entry as well.
- L36 _protected prototype_ `FText GetWidgetTextForOption(const FName InOption, const bool bSuppressResolution) const;` — Gets the text that should be displayed in the widget for the specified option. In the form of "{name} - {x}x{y}" unless bSuppressResolution is true, at which point it will just be in the form of "{name}"
- L38 _protected prototype_ `FText GetWidgetTextForCurrent() const;` — The above, but for the currently selected (ie: "root" of combo box).
- L40 _protected prototype_ `FText GetWidgetTooltipTextForOption(const FName InOption) const;` — Gets the description property for the specified option
- L42 _protected prototype_ `FText GetWidgetTooltipTextForCurrent() const;` — The above, but for the currently selected (ie: "root" of combo box).
- L45 _protected function_ `FSlateFontInfo GetWidgetFontForOptions() const`
- L51 _protected prototype_ `TSharedRef<SWidget> MakeWidgetForOptionInDropdown(FName InOption) const;` — Called to generate a widget for each entry in the dropdown when you open the dropdown.
- L53 _protected prototype_ `TSharedRef<SWidget> MakeWidgetForSelectedItem() const;` — Called to generate the widget for the "root" of the combo box that is always visible.
- L56 _protected prototype_ `TSharedRef<SWidget> CreateComboBoxWidget();` — Create the actual ComboBox Widget
- L59 _protected prototype_ `void BindToOnProjectSettingsModified();` — Binds to the Project Settings to know when a user has added or removed a preset.
- L62 _protected prototype_ `const FSlateBrush* GetAspectRatioLockBrush() const;` — Get the icon to use for the Aspect Ratio Locked widget, could be a locked or unlocked icon.
- L65 _protected prototype_ `FText GetAspectRatioLockTooltipText() const;` — Get the current tooltip for the aspect ratio lock
- L68 _protected prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L71 _protected prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L77 _protected prototype_ `void UpdateAspectRatioLockImage();` — Update the aspect ratio lock image based on current lock setting.
- L80 _protected prototype_ `void ToggleAspectRatioLock();` — On click, toggle the current lock state.
- L83 _protected prototype_ `TSharedRef<SWidget> MakeAspectRatioLockWidget();` — Create the Aspect Ratio Lock widget that is added in the customization.
- L86 _protected prototype_ `float CalculateAspectRatio();` — Calculates the aspect ratio of the current resolution.
- L93 _protected prototype_ `FIntPoint GetEffectiveResolution() const;` — Gets the effective resolution for the current resolution. For profiles this looks it up in the Project Settings, so that if the project setting has been changed since the resolution was last updated, we reflect the correct value. MRQ will also look it up from the Project Setting at runtime.
- L96 _protected prototype_ `void OnCustomSliderBeginMovement();` — Called when dragging the slider starts. Used to open a transaction to encapsulate all changes into one.
- L98 _protected prototype_ `void OnCustomSliderEndMovement(uint32 NewValue);` — Called when the slider stops dragging. Closes the transaction.
- L101 _protected prototype_ `int32 GetCurrentlySelectedResolutionByAxis(const EAxis::Type Axis);` — Gets the resolution for the given axis.
- L104 _protected prototype_ `void OnCustomSliderValueChanged(uint32 NewValue, EAxis::Type Axis);` — Called when dragging the slider, or after typing in a number and hitting enter.
- L107 _protected prototype_ `void AddCustomRowForResolutionAxis( EAxis::Type Axis, IDetailChildrenBuilder& StructBuilder, const FString& FilterString, TSharedRef<SWidget> NameContentWidget, TSharedPtr<SWidget> AspectRatioLockExtensionWidget = nullptr);` — Adds a row to the customization for the given axis.
- L113 _protected prototype_ `void OnProjectSettingsChanged(UObject*, FPropertyChangedEvent& PropertyChangedEvent);` — Callback bound when project setting changes.
- L116 _protected prototype_ `void OnComboBoxSelectionChanged(const FName NewValue, ESelectInfo::Type InType);` — Called when the user selects a new preset from the combo box dropdown.
- L119 _protected member_ `TSharedPtr<SWidget> ComboBoxWidget;` — The widget that allows the end user to select the output resolution
- L122 _protected member_ `TSharedPtr<SImage> AspectRatioLockImage;` — The image that indicates whether the aspect ratio is locked.
- L125 _protected member_ `TWeakPtr<IPropertyHandle> StructPropertyHandle;` — Weak ptr to the handle of the struct which owns this customization
- L128 _protected member_ `TSharedPtr<IPropertyHandle> ResolutionXPropertyHandle;` — Handle to the "Resolution.X" property on the edited object.
- L130 _protected member_ `TSharedPtr<IPropertyHandle> ResolutionYPropertyHandle;` — Handle to the "Resolution.Y" property on the edited object.
- L132 _protected member_ `TSharedPtr<IPropertyHandle> ProfileNamePropertyHandle;` — Handle to the "ProfileName" property on the edited object.
- L140 _protected member_ `TOptional<float> LockedAspectRatio;` — The aspect ratio of the currently selected resolution. Updates when the aspect ratio lock is applied, a named resolution is selected, or when the 'Custom' resolution values are changed. Used to track if Aspect ratio lock is enabled or not.
- L146 _protected member_ `TArray<FName> ComboBoxOptions;` — The options for the combo box, populated from UMovieGraphProjectSettings::DefaultNamedResolutions. A 'custom' entry is added to the end of the list, representing an arbitrary user-defined resolution.
- L151 _protected member_ `FDelegateHandle OnProjectSettingsModifiedHandle;` — A binding that updates the ComboBoxOptions when UMovieGraphProjectSettings::DefaultNamedResolutions changes
- L156 _protected member_ `TUniquePtr<FScopedTransaction> InteractiveResolutionEditTransaction;` — If valid, this means that a slide operation is currently in progress and that the changes will be encapsulated into this transaction.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphNodeCustomization.h` (Private)


#### class `FMovieGraphNodeCustomization`  
`class FMovieGraphNodeCustomization : public IDetailCustomization`  
_L15-120_
- inherits: `IDetailCustomization`
- desc: Customize how graph nodes appear in the details panel.
- L18 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L25 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L30 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`
- L79 _private function_ `void AddTokenAutocompleteWidgetToAllEligibleProperties(IDetailLayoutBuilder& DetailBuilder)` — Adds the token autocomplete widget to all properties that have the MrgTokenAutocomplete UPROPERTY metadata.

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphPathTracedRendererNodeCustomization.h` (Private)


#### class `FMovieGraphPathTracedRendererNodeCustomization`  
`class FMovieGraphPathTracedRendererNodeCustomization : public IDetailCustomization`  
_L14-75_
- inherits: `IDetailCustomization`
- desc: Customize how the Path Traced Renderer node appears in the details panel.
- L17 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L24 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L29 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`
- L34 _function_ `` (scope `FMovieGraphPathTracedRendererNodeCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphPostProcessPassCustomization.h` (Private)


#### class `FMovieGraphPostProcessPassCustomization`  
`class FMovieGraphPostProcessPassCustomization final : public IPropertyTypeCustomization`  
_L15-67_
- inherits: `IPropertyTypeCustomization`
- desc: Customize how post process passes appear in the details panel.
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _protected function_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L41 _protected function_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphQuickRenderSettingsCustomization.h` (Private)


#### class `FMovieGraphQuickRenderSettingsCustomization`  
`class FMovieGraphQuickRenderSettingsCustomization : public IDetailCustomization`  
_L25-206_
- inherits: `IDetailCustomization`
- desc: Customize how properties for QuickRenderSettings appear in the details panel.
- L28 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L33 _public prototype_ `virtual ~FMovieGraphQuickRenderSettingsCustomization() override = default;`
- L35 _public function_ `virtual void PendingDelete() override`
- L50 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override`
- L56 _protected function_ `void RefreshLayout(const FString&, UPackage*, FObjectPostSaveContext) const`
- L64 _protected function_ `void RefreshLayout() const`
- L70 _protected function_ `void UpdateFrameRangePropertyEnableState() const`
- L97 _protected function_ `void AddPostRenderPlayOptionsButton() const` — Adds a button next to the post-render behavior drop-down to open the editor preferences that dictate how media is played back.
- L147 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override`
- L202 _private member_ `IDetailLayoutBuilder* DetailBuilder = nullptr;` — The details builder associated with the customization.
- L205 _private member_ `TWeakObjectPtr<UMovieGraphQuickRenderModeSettings> QuickRenderModeSettings = nullptr;` — The quick render mode settings being displayed.

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineQuickRenderSettings"`
- L73 _function_ `` (scope `FMovieGraphQuickRenderSettingsCustomization::UpdateFrameRangePropertyEnableState`)
- L131 _function_ `` (scope `FMovieGraphQuickRenderSettingsCustomization::AddPostRenderPlayOptionsButton`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphSelectNodeCustomization.h` (Private)


#### class `FMovieGraphSelectNodeCustomization`  
`class FMovieGraphSelectNodeCustomization : public IDetailCustomization`  
_L22-179_
- inherits: `IDetailCustomization`
- desc: Customize how the Select node appears in the details panel.
- L25 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L32 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L37 _protected function_ `bool IsTypeAllowed(const FEdGraphPinType& PinType) const`
- L55 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`
- L60 _function_ `` (scope `FMovieGraphSelectNodeCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphSetCVarValueNodeCustomization.h` (Private)


#### class `FMovieGraphSetCVarValueNodeCustomization`  
`class FMovieGraphSetCVarValueNodeCustomization : public IDetailCustomization`  
_L17-90_
- inherits: `IDetailCustomization`
- desc: Customize how the Set Console Variable Value node appears in the details panel.
- L20 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L26 _protected function_ `FText GetConsoleVariableText(TSharedRef<IPropertyHandle> PropertyHandle) const`
- L38 _protected function_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override`
- L43 _protected function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`
- L71 _function_ `` (scope `FMovieGraphSetCVarValueNodeCustomization::CustomizeDetails`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphShowFlagsCustomization.h` (Private)


#### class `FMovieGraphShowFlagsCustomization`  
`class FMovieGraphShowFlagsCustomization : public IPropertyTypeCustomization`  
_L20-179_
- inherits: `IPropertyTypeCustomization`
- desc: Customize how show flags appear in the details panel.
- L23 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L30 _protected function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L32 _protected function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "MoviePipelineEditor"`
- L123 _function_ `` (scope `FMovieGraphShowFlagsCustomization::CustomizeChildren`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/Graph/MovieGraphVersioningSettingsCustomization.h` (Private)


#### class `FMovieGraphVersioningSettingsCustomization`  
`class FMovieGraphVersioningSettingsCustomization : public IPropertyTypeCustomization`  
_L16-105_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes how Versioning Settings are displayed in the details pane.
- L19 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L27 _protected function_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L101 _protected function_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override` — Skip customizing children

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "FMovieGraphVersioningSettingsCustomization"`
- L55 _function_ `` (scope `FMovieGraphVersioningSettingsCustomization::CustomizeHeader`)

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/JobCustomization.h` (Private)


#### class `FJobDetailsCustomization`  
`class FJobDetailsCustomization : public IDetailCustomization`  
_L24-61_
- inherits: `IDetailCustomization`
- desc: Detail customization for jobs and shots in the queue panel. Surfaces the Basic configuration mode UI (segmented control, output/rendering categories, shot override toggles) in addition to the existing Graph/Preset variable assignments.
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L28 _public prototype_ `virtual ~FJobDetailsCustomization() override = default;`
- L30 _public prototype_ `virtual void PendingDelete() override;`
- L34 _protected prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L35 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L39 _private prototype_ `void RefreshLayout(const FString&, UPackage*, FObjectPostSaveContext) const;`
- L40 _private prototype_ `void RefreshLayout(UMoviePipelineExecutorShot*, UMovieGraphConfig*) const;`
- L41 _private prototype_ `void RefreshLayout(UMoviePipelineExecutorJob*, UMovieGraphConfig*) const;`
- L42 _private prototype_ `void RefreshLayout(UMoviePipelineExecutorJob*, EMoviePipelineConfigMode) const;`
- L45 _private prototype_ `void AddConfigurationModeRow(IDetailCategoryBuilder& InCategory);` — Adds the Configuration mode row (segmented control + mode-dependent sub-widget) for primary jobs.
- L48 _private prototype_ `void AddBasicConfigOutputTypeProperties(IDetailLayoutBuilder& InDetailBuilder, UMoviePipelineBasicConfig* InActiveConfig, bool bIsShot);` — Adds the Output category with output type buttons, gear menu, and per-property override toggles.
- L51 _private prototype_ `void AddBasicConfigRenderingProperties(IDetailLayoutBuilder& InDetailBuilder, UMoviePipelineBasicConfig* InActiveConfig, bool bIsShot);` — Adds the Rendering category with renderer toggles and per-renderer sub-groups.
- L54 _private member_ `IDetailLayoutBuilder* DetailBuilder = nullptr;` — The details builder associated with the customization.
- L57 _private member_ `TWeakObjectPtr<UMoviePipelineExecutorJob> SelectedJob;` — The primary job that's selected in the UI (can be null).
- L60 _private member_ `TWeakObjectPtr<UMoviePipelineExecutorShot> SelectedShot;` — The shot that's selected in the UI (can be null if a job is selected).

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/MoviePipelineNameEditSinks.h` (Private)


#### class `FMoviePipelineJobNameEditSink`  
`class FMoviePipelineJobNameEditSink : public UE::EditorWidgets::IObjectNameEditSink`  
_L9-44_
- inherits: `UE::EditorWidgets::IObjectNameEditSink`
- desc: Provides an editable JobName in the details panel name area for UMoviePipelineExecutorJob.
- L12 _public function_ `virtual UClass* GetSupportedClass() const override`
- L17 _public function_ `virtual FText GetObjectDisplayName(UObject* Object) const override`
- L23 _public function_ `virtual bool IsObjectDisplayNameReadOnly(UObject* Object) const override`
- L28 _public function_ `virtual bool SetObjectDisplayName(UObject* Object, FString DisplayName) override`
- L40 _public function_ `virtual FText GetObjectNameTooltip(UObject* Object) const override`

#### class `FMoviePipelineShotNameEditSink`  
`class FMoviePipelineShotNameEditSink : public UE::EditorWidgets::IObjectNameEditSink`  
_L47-70_
- inherits: `UE::EditorWidgets::IObjectNameEditSink`
- desc: Provides a read-only OuterName + InnerName display in the details panel name area for UMoviePipelineExecutorShot.
- L50 _public function_ `virtual UClass* GetSupportedClass() const override`
- L55 _public function_ `virtual FText GetObjectDisplayName(UObject* Object) const override`
- L61 _public function_ `virtual bool IsObjectDisplayNameReadOnly(UObject* Object) const override`
- L66 _public function_ `virtual FText GetObjectNameTooltip(UObject* Object) const override`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Customizations/PostProcessPassCustomization.h` (Private)


#### class `FPostProcessPassCustomization_MRQ`  
`class FPostProcessPassCustomization_MRQ : public IPropertyTypeCustomization`  
_L14-62_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes how post process passes are displayed (for MRQ, not MRG).
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L24 _protected function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L38 _protected function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "SMoviePipelineEditor"`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/AssetDefinition_MovieGraphConfig.h` (Private)


#### class `UAssetDefinition_MovieGraphConfig`  
`class UAssetDefinition_MovieGraphConfig : public UAssetDefinitionDefault`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieEdGraph.h` (Private)


#### class `UMoviePipelineEdGraph`  
`class UMoviePipelineEdGraph : public UEdGraph`  
_L18-65_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- desc: This is the editor-only graph representation of the UMovieGraphConfig. This contains editor only nodes (which have information about their X/Y position graphs, their widgets, etc.) where each node in this ed graph is tied to a node in the runtime UMovieGraphConfig.
- L31 _public prototype_ `void InitFromRuntimeGraph(UMovieGraphConfig* InGraph);` — Initialize this Editor Graph from a Runtime Graph. This is typically called when the editor representation of the runtime graph is initially created (in order to ensure there are editor equivalents of all runtime nodes, connections, etc). However, it can also be called to ensure that all runtime objects have editor equivalents even after initial editor graph creation. This can be useful when, for example, nodes are created via the Python API (which creates runtime nodes), and editor nodes need to be created afterwards.
- L34 _public prototype_ `void RegisterDelegates(UMovieGraphConfig* InGraph);` — Register delegates that relate to the runtime graph.
- L37 _public prototype_ `class UMovieGraphConfig* GetPipelineGraph() const;` — Returns the runtime UMovieGraphConfig that contains this editor graph
- L40 _public prototype_ `void CreateLinks(UMoviePipelineEdGraphNodeBase* InGraphNode, bool bCreateInboundLinks, bool bCreateOutboundLinks);` — Creates the links/edges between nodes in the graph
- L43 _public prototype_ `void ReconstructGraph();` — Completely reconstruct the graph. This is a big hammer and should be used sparingly.
- L46 _protected prototype_ `void CreateLinks(UMoviePipelineEdGraphNodeBase* InGraphNode, bool bCreateInboundLinks, bool bCreateOutboundLinks, const TMap<UMovieGraphNode*, UMoviePipelineEdGraphNodeBase*>& RuntimeNodeToEdNodeMap);`
- L53 _protected prototype_ `void OnGraphConfigChanged();` — Handler which deals with changes made to the runtime graph. This will most likely be replaced with more specific handlers in the future when the graph is more fully-featured.
- L56 _protected prototype_ `void OnGraphNodesDeleted(TArray<UMovieGraphNode*> DeletedNodes);` — Handler which deals with deleted nodes in the runtime graph. The GUIDs provided are those of the deleted runtime nodes.
- L59 _protected member_ `bool bInitialized = false;`
- L64 _private prototype_ `template <typename T> UMoviePipelineEdGraphNodeBase* CreateNodeFromRuntimeNode(UMovieGraphNode* InRuntimeNode);` — Create a new editor node of type T from the given runtime node.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieEdGraphConnectionPolicy.h` (Private)


#### class `FMovieEdGraphConnectionDrawingPolicy`  
`class FMovieEdGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L11-22_
- inherits: `FConnectionDrawingPolicy`
- desc: Connection drawing policy for the render graph.
- L14 _public prototype_ `FMovieEdGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L17 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;`
- L21 _private member_ `UMoviePipelineEdGraph* MovieEdGraph;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieEdGraphInputNode.h` (Private)


#### class `UMoviePipelineEdGraphNodeInput`  
`class UMoviePipelineEdGraphNodeInput : public UMoviePipelineEdGraphNodeBase`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `UMoviePipelineEdGraphNodeBase`
- L16 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L17 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L18 _public function_ `virtual bool CanUserDeleteNode() const override`
- L20 _public function_ `virtual bool CanDuplicateNode() const override` — This is set to true so that the node is deserialized on paste, required for CanPasteHere to be called.
- L22 _public function_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override` — And this is set to false so the paste doesn't actually go through, and instead we get the editor prompt notifying user.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieEdGraphNode.h` (Private)


#### class `UMoviePipelineEdGraphNodeBase`  
`class UMoviePipelineEdGraphNodeBase : public UEdGraphNode`  
_L13-96_
- reflection: `UCLASS(Abstract)`
- inherits: `UEdGraphNode`
- L17 _public function_ `UMovieGraphNode* GetRuntimeNode() const`
- L19 _public prototype_ `void Construct(UMovieGraphNode* InRuntimeNode);`
- L21 _public prototype_ `void OnRuntimeNodeChanged(const UMovieGraphNode* InChangedNode);`
- L24 _public prototype_ `virtual void PostLoad() override;`
- L25 _public prototype_ `virtual void ReconstructNode() override;`
- L26 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L27 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L28 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L29 _public prototype_ `virtual bool ShowPaletteIconOnNode() const override;`
- L30 _public prototype_ `virtual void OnUpdateCommentText(const FString& NewComment) override;`
- L31 _public prototype_ `virtual void OnCommentBubbleToggled(bool bInCommentBubbleVisible) override;`
- L32 _public prototype_ `virtual void PrepareForCopying() override;`
- L33 _public prototype_ `virtual void PostPasteNode() override;`
- L34 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L37 _public prototype_ `static FEdGraphPinType GetPinType(EMovieGraphValueType ValueType, bool bIsBranch, bool bIsWildcard, const UObject* InValueTypeObject = nullptr);`
- L38 _public prototype_ `static FEdGraphPinType GetPinType(const UMovieGraphPin* InPin);`
- L39 _public prototype_ `static EMovieGraphValueType GetValueTypeFromPinType(const FEdGraphPinType& InPinType);`
- L42 _public prototype_ `virtual void PostCopy();` — Called after PrepareForCopying to restore changes made during preparation.
- L43 _public prototype_ `virtual void PostPaste();`
- L46 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L50 _protected prototype_ `virtual bool ShouldCreatePin(const UMovieGraphPin* InPin) const;`
- L51 _protected prototype_ `void RebuildRuntimeEdgesFromPins();`
- L53 _protected prototype_ `void CreatePins(const TArray<UMovieGraphPin*>& InInputPins, const TArray<UMovieGraphPin*>& InOutputPins);`
- L56 _protected prototype_ `virtual FString GetPinTooltip(const UMovieGraphPin* InPin) const;` — Gets the tooltip for the given pin.
- L59 _protected prototype_ `void ReconstructPins();` — Recreate the pins on this node, discarding all existing pins.
- L62 _protected prototype_ `void UpdatePosition() const;` — Update the position of the underlying runtime node to match the editor node.
- L68 _protected prototype_ `void UpdateCommentBubblePinned() const;` — Update the comment bubble pin state on the underlying runtime node to match the editor node. Note that comment bubble visibility state and comment text are handled by UEdGraphNode overrides.
- L73 _protected prototype_ `void UpdateEnableState() const;` — Update the enable state of the underlying runtime node to match the editor node.
- L76 _protected prototype_ `void RegisterDelegates();` — Registers any delegates needed by the node.
- L81 _protected member_ `TObjectPtr<UMovieGraphNode> RuntimeNode;` — `UPROPERTY()` — The runtime node that this editor node represents.
- L88 _protected member_ `FString OriginPluginName;` — `UPROPERTY()` — Cached friendly name of the plugin that this node originated from. In the event that the origin plugin is unloaded, we can provide the name of the plugin as a hint. The runtime node will be null in this scenario, so specifying the name of the plugin could be very helpful.
- L91 _protected member_ `bool bDisableReconstructNode = false;` — Should we early out in ReconstructNode(), skipping restoring the connections to other nodes. Set during Copy/Paste.
- L95 _protected member_ `FSoftObjectPath OriginGraph;` — `UPROPERTY(SkipSerialization)` — The graph that this node originated from during a copy/paste operation. This value should never be used outside of copy/paste logic.

#### class `UMoviePipelineEdGraphNode`  
`class UMoviePipelineEdGraphNode : public UMoviePipelineEdGraphNodeBase`  
_L99-123_
- reflection: `UCLASS()`
- inherits: `UMoviePipelineEdGraphNodeBase`
- L105 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L106 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L107 _public prototype_ `virtual FText GetTooltipText() const override;`
- L108 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L113 _protected prototype_ `void TogglePromotePropertyToPin(const FName PropertyName) const;` — Toggle the promotion of the property with the given name to a pin.
- L116 _private prototype_ `void GetPropertyPromotionContextMenuActions(UToolMenu* Menu, const UGraphNodeContextMenuContext* Context) const;`
- L122 _private prototype_ `void PromotePropertyToVariable(const FMovieGraphPropertyInfo& TargetProperty) const;` — Promote the property identified by TargetProperty to a variable. This means 1) creating a new variable w/ the type associated with the target property, 2) creating a new variable node linked to this new variable, and 3) connecting the variable node to TargetProperty's pin.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieEdGraphOutputNode.h` (Private)


#### class `UMoviePipelineEdGraphNodeOutput`  
`class UMoviePipelineEdGraphNodeOutput : public UMoviePipelineEdGraphNodeBase`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UMoviePipelineEdGraphNodeBase`
- L15 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L16 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L17 _public function_ `virtual bool CanUserDeleteNode() const override`
- L19 _public function_ `virtual bool CanDuplicateNode() const override` — This is set to true so that the node is deserialized on paste, required for CanPasteHere to be called
- L21 _public function_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override` — And this is set to false so the paste doesn't actually go through, and instead we get the editor prompt notifying user.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieEdGraphRerouteNode.h` (Private)


#### class `UMoviePipelineEdGraphRerouteNode`  
`class UMoviePipelineEdGraphRerouteNode : public UMoviePipelineEdGraphNode`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UMoviePipelineEdGraphNode`
- desc: A node which reroutes connections in order to organize the graph cleanly.
- L17 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L18 _public prototype_ `virtual UEdGraphPin* GetPassThroughPin(const UEdGraphPin* FromPin) const override;`
- L19 _public prototype_ `virtual bool ShouldDrawNodeAsControlPointOnly(int32& OutInputPinIndex, int32& OutOutputPinIndex) const override;`
- L20 _public prototype_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;`
- L21 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieEdGraphVariableNode.h` (Private)


#### class `UMoviePipelineEdGraphVariableNode`  
`class UMoviePipelineEdGraphVariableNode : public UMoviePipelineEdGraphNodeBase`  
_L11-31_
- reflection: `UCLASS()`
- inherits: `UMoviePipelineEdGraphNodeBase`
- desc: An editor node which represents an accessor for a variable defined on the graph.
- L17 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L18 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L19 _public prototype_ `virtual bool CanPasteHere(const UEdGraph* TargetGraph) const override;`
- L20 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _protected prototype_ `virtual FString GetPinTooltip(const UMovieGraphPin* InPin) const override;`
- L30 _private prototype_ `FString GetVariableDescription() const;` — Get the description (if any) for the variable this node represents.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieGraphAssetToolkit.h` (Private)


#### class `SMovieGraphSyncCollectionToOutlinerButton`  
`class SMovieGraphSyncCollectionToOutlinerButton final : public SCompoundWidget`  
_L9-26_
- inherits: `SCompoundWidget`
- desc: Evaluates a collection and syncs the matched actors to the Outliner selection.
- L12 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphSyncCollectionToOutlinerButton)`
- L14 _public prototype_ `SLATE_ATTRIBUTE(TArray<TWeakObjectPtr<UObject>>, SelectedNodes) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The nodes selected in the graph.
- L21 _private prototype_ `void EvaluateCollectionAndSelect() const;` — Evaluates the collection and selects all matches in the Outliner.
- L25 _private member_ `TAttribute<TArray<TWeakObjectPtr<UObject>>> SelectedNodesAttribute;` — The nodes which are currently selected in the graph.

#### class `FMovieGraphAssetToolkit`  
`class FMovieGraphAssetToolkit : public FAssetEditorToolkit`  
_L28-126_
- inherits: `FAssetEditorToolkit`
- L31 _public prototype_ `FMovieGraphAssetToolkit();`
- L32 _public prototype_ `virtual ~FMovieGraphAssetToolkit() override = default;`
- L35 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L36 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L37 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L38 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L39 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L40 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L41 _public prototype_ `virtual void OnAssetsSavedAs(const TArray<UObject*>& SavedObjects) override;`
- L42 _public prototype_ `virtual void OnClose() override;`
- L46 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L49 _public prototype_ `void InitMovieGraphAssetToolkit(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, class UMovieGraphConfig* InitGraph);`
- L52 _private prototype_ `TSharedRef<SDockTab> SpawnTab_RenderGraphEditor(const FSpawnTabArgs& Args);`
- L53 _private prototype_ `TSharedRef<SDockTab> SpawnTab_RenderGraphMembers(const FSpawnTabArgs& Args);`
- L54 _private prototype_ `TSharedRef<SDockTab> SpawnTab_RenderGraphDetails(const FSpawnTabArgs& Args);`
- L55 _private prototype_ `TSharedRef<SDockTab> SpawnTab_RenderGraphActiveRenderSettings(const FSpawnTabArgs& Args);`
- L58 _private prototype_ `void RegisterDetailsViewSections();` — Register sections used by the graph's details panel.
- L61 _private prototype_ `void BindGraphCommands();` — Register commands used by the editor.
- L64 _private prototype_ `void ExtendToolkitMenu() const;` — Adds additional commands to the toolkit's menu.
- L67 _private prototype_ `void DeleteSelectedMembers();` — Deletes the member(s) which are currently selected.
- L70 _private prototype_ `bool CanDeleteSelectedMembers();` — Determines if the selected member(s) can be deleted.
- L73 _private prototype_ `void DuplicateSelectedMembers();` — Duplicates the member(s) which are currently selected.
- L76 _private prototype_ `bool CanDuplicateSelectedMembers();` — Determines if the selected member(s) can be duplicated.
- L79 _private prototype_ `bool IsDuplicateVisible();` — Determines if the Duplicate action is visible for the selected members.
- L82 _private prototype_ `void OnZoomToWindow() const;` — Frames the entire graph so it is visible.
- L85 _private prototype_ `bool CanZoomToWindow() const;` — Determines if the entire graph can be framed.
- L88 _private prototype_ `void OnZoomToSelection() const;` — Frames the selected node(s) so they are visible.
- L91 _private prototype_ `bool CanZoomToSelection() const;` — Determines if the selected node(s) can be framed.
- L94 _private prototype_ `void PersistEditorOnlyNodes() const;` — Copies editor-only nodes to the underlying runtime graph so they can be restored later.
- L97 _private prototype_ `TSharedRef<SWidget> GetDefaultGraphEditWarning() const;` — Generate the widget that displays a warning banner if the default graph is being edited.
- L101 _private member_ `TSharedPtr<IDetailsView> SelectedGraphObjectsDetailsWidget;` — The details panel for the selected object(s) in the graph
- L104 _private member_ `TSharedPtr<SWidget> NameAreaCustomContent;` — Custom widgetry shown above the filter box in the details panel.
- L107 _private member_ `TSharedPtr<class SMoviePipelineGraphPanel> MovieGraphWidget;` — The widget that contains the main node graph
- L110 _private member_ `TSharedPtr<class SMovieGraphMembersTabContent> MembersTabContent;` — The widget which encapsulates all of the content in the Members tab
- L113 _private member_ `TSharedPtr<class SMovieGraphActiveRenderSettingsTabContent> ActiveRenderSettingsTabContent;` — The widget which encapsulates all of the content in the Active Render Settings tab
- L116 _private member_ `TObjectPtr<UMovieGraphConfig> InitialGraph;` — The graph that the editor was initialized with
- L119 _private member_ `bool bIsInternalSelectionChange;` — Flag which is set when a selection change is not triggered by the user
- L121 _private member_ `static const FName AppIdentifier;`
- L122 _private member_ `static const FName GraphTabId;`
- L123 _private member_ `static const FName DetailsTabId;`
- L124 _private member_ `static const FName MembersTabId;`
- L125 _private member_ `static const FName ActiveRenderSettingsTabId;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieGraphPinFactory.h` (Private)


#### class `FMovieGraphPanelPinFactory`  
`class FMovieGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L9-15_
- inherits: `FGraphPanelPinFactory`
- desc: Pin factory for the render graph.
- L13 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MovieGraphSchema.h` (Private)


#### class `UMovieGraphSchema`  
`class UMovieGraphSchema : public UEdGraphSchema`  
_L13-95_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L19 _public prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L20 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L21 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L22 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* InA, UEdGraphPin* InB) const override;`
- L23 _public prototype_ `static FLinearColor GetTypeColor(const FName& InPinCategory, const FName& InPinSubCategory);`
- L24 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L25 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const override;`
- L26 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const override;`
- L27 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L28 _public prototype_ `virtual bool SupportsPinTypeContainer(TWeakPtr<const FEdGraphSchemaAction> SchemaAction, const FEdGraphPinType& PinType, const EPinContainerType& ContainerType) const override;`
- L29 _public prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L30 _public prototype_ `virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;`
- L31 _public prototype_ `virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;`
- L32 _public prototype_ `virtual void SetPinBeingDroppedOnNode(UEdGraphPin* InSourcePin) const override;`
- L33 _public prototype_ `virtual bool SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* Node) const override;`
- L34 _public prototype_ `virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2f& GraphPosition) const override;`
- L35 _public prototype_ `virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;`
- L36 _public prototype_ `virtual int32 GetCurrentVisualizationCacheID() const override;`
- L37 _public prototype_ `virtual void ForceVisualizationCacheClear() const override;`
- L40 _public prototype_ `static void InitMoviePipelineNodeClasses();`
- L46 _public prototype_ `static const TArray<UClass*>& GetNodeClasses();` — Gets all node classes that the graph is aware of and are usable within the graph (including those from plugins). Should only be called after all plugins that contain nodes have been loaded.
- L53 _private prototype_ `bool IsConnectionToBranchAllowed(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin, FText& OutError) const;` — Determines if the connection between InputPin and OutputPin follows branch restriction rules. OutError is populated with an error if the connection should be rejected and the function will return false.
- L58 _private prototype_ `void AddExtraMenuActions(FGraphActionMenuBuilder& ActionMenuBuilder) const;` — Adds extra menu actions to the context/palette menu.
- L64 _private prototype_ `TSharedRef<FMovieGraphSchemaAction_NewComment> CreateCommentMenuAction() const;` — Returns a menu action for creating a new comment in the graph. Note that this is not the same as adding a new comment to the graph via hotkey.
- L68 _public member_ `static const FName PC_Branch;` — Allowed "PinCategory" values for use on EdGraphPin
- L69 _public member_ `static const FName PC_Wildcard;`
- L70 _public member_ `static const FName PC_Boolean;`
- L71 _public member_ `static const FName PC_Byte;`
- L72 _public member_ `static const FName PC_Integer;`
- L73 _public member_ `static const FName PC_Int64;`
- L74 _public member_ `static const FName PC_Real;`
- L75 _public member_ `static const FName PC_Float;`
- L76 _public member_ `static const FName PC_Double;`
- L77 _public member_ `static const FName PC_Name;`
- L78 _public member_ `static const FName PC_String;`
- L79 _public member_ `static const FName PC_Text;`
- L80 _public member_ `static const FName PC_Enum;`
- L81 _public member_ `static const FName PC_Struct;`
- L82 _public member_ `static const FName PC_Object;`
- L83 _public member_ `static const FName PC_SoftObject;`
- L84 _public member_ `static const FName PC_Class;`
- L85 _public member_ `static const FName PC_SoftClass;`
- L88 _private member_ `static TArray<UClass*> MoviePipelineNodeClasses;`
- L91 _private member_ `mutable int32 CurrentCacheRefreshID = 0;` — Counter incremented when cached visualization data (tooltips, titles, etc.) should be refreshed.
- L94 _private member_ `mutable UEdGraphPin* PinBeingDropped = nullptr;` — The pin that is being dropped on another node during a drag-drop operation. Controlled by SupportsDropPinOnNode().

#### struct `FMovieGraphSchemaAction`  
`struct FMovieGraphSchemaAction : public FEdGraphSchemaAction`  
_L99-126_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Base class for schema actions in the graph.
- L106 _public prototype_ `virtual ~FMovieGraphSchemaAction() override = default;`
- L108 _public function_ `static FName StaticGetTypeId()`
- L114 _public member_ `static const FText UserVariablesCategory;`
- L115 _public member_ `static const FText GlobalVariablesCategory;`
- L117 _public prototype_ `virtual void MovePersistentItemToCategory(const FText& NewCategoryName) override;`
- L118 _public prototype_ `virtual bool ReorderToBeforeAction(TSharedRef<FEdGraphSchemaAction> OtherAction) override;`
- L122 _public member_ `TObjectPtr<UObject> ActionTarget = nullptr;` — `UPROPERTY()` — The object the action relates to.
- L125 _public member_ `TSubclassOf<UMovieGraphNode> NodeClass;` — `UPROPERTY()`

#### struct `FMovieGraphSchemaAction_NewNode`  
`struct FMovieGraphSchemaAction_NewNode : public FMovieGraphSchemaAction`  
_L130-152_
- reflection: `USTRUCT()`
- inherits: `FMovieGraphSchemaAction`
- desc: Schema action for creating a new node in the graph.
- L134 _public function_ `FMovieGraphSchemaAction_NewNode() : FMovieGraphSchemaAction()`
- L138 _public prototype_ `FMovieGraphSchemaAction_NewNode(FText InNodeCategory, FText InDisplayName, FText InToolTip, int32 InGrouping, FText InKeywords);`
- L140 _public prototype_ `virtual ~FMovieGraphSchemaAction_NewNode() override = default;`
- L142 _public function_ `static FName StaticGetTypeId()`
- L150 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMovieGraphSchemaAction_NewVariableNode`  
`struct FMovieGraphSchemaAction_NewVariableNode : public FMovieGraphSchemaAction`  
_L156-183_
- reflection: `USTRUCT()`
- inherits: `FMovieGraphSchemaAction`
- desc: Schema action for creating a new variable node in the graph.
- L160 _public function_ `static FName StaticGetTypeId()`
- L166 _public function_ `FMovieGraphSchemaAction_NewVariableNode() : FMovieGraphSchemaAction()`
- L170 _public prototype_ `FMovieGraphSchemaAction_NewVariableNode(FText InNodeCategory, FText InDisplayName, FGuid InVariableGuid, FText InToolTip);`
- L172 _public prototype_ `virtual ~FMovieGraphSchemaAction_NewVariableNode() override = default;`
- L176 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L182 _private member_ `FGuid VariableGuid;` — `UPROPERTY()` — GUID of the runtime variable this action relates to.

#### struct `FMovieGraphSchemaAction_NewComment`  
`struct FMovieGraphSchemaAction_NewComment : public FMovieGraphSchemaAction`  
_L187-209_
- reflection: `USTRUCT()`
- inherits: `FMovieGraphSchemaAction`
- desc: Schema action for creating a new comment node in the graph.
- L191 _public function_ `static FName StaticGetTypeId()`
- L200 _public function_ `FMovieGraphSchemaAction_NewComment() : FMovieGraphSchemaAction()`
- L205 _public function_ `virtual FName GetTypeId() const override`
- L207 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/MoviePipelineEdGraphSubgraphNode.h` (Private)


#### class `UMoviePipelineEdGraphSubgraphNode`  
`class UMoviePipelineEdGraphSubgraphNode : public UMoviePipelineEdGraphNode`  
_L11-19_
- reflection: `UCLASS()`
- inherits: `UMoviePipelineEdGraphNode`
- L17 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/SMovieGraphActiveRenderSettingsTabContent.h` (Private)


#### class `FActiveRenderSettingsTreeElement`  
`class FActiveRenderSettingsTreeElement : public TSharedFromThis<FActiveRenderSettingsTreeElement>`  
_L19-83_
- inherits: `TSharedFromThis<FActiveRenderSettingsTreeElement>`
- desc: Represents the data of one element displayed in the tree, which is one of the types in EElementType. Provides a way of getting the children under the element.
- L31 _public member_ `static const FName RootName_Globals;`
- L32 _public member_ `static const FName RootName_Branches;`
- L34 _public prototype_ `FActiveRenderSettingsTreeElement(const FName& InName, const EElementType InType);`
- L37 _public prototype_ `FString GetValue() const;` — If this element represents a property, returns the string representation of the value. Otherwise returns an empty string.
- L40 _public prototype_ `bool IsBranchRenderable() const;` — Determines if this element is a branch, and the branch has renderable output.
- L47 _public prototype_ `const TArray<TSharedPtr<FActiveRenderSettingsTreeElement>>& GetChildren() const;` — Gets the child elements nested under this element. Returns a cached result if available, otherwise calculates the children and returns the result. Call ClearCachedChildren() if the cache needs to be cleared (eg, when the tree is being refreshed).
- L50 _public prototype_ `void ClearCachedChildren() const;` — Clears the cached result of GetChildren().
- L53 _public prototype_ `uint32 GetHash() const;` — Gets the hash that uniquely identifies this element in the tree.
- L57 _public member_ `FName Name;` — The name of the element as it appears in the tree.
- L60 _public member_ `EElementType Type = EElementType::Root;` — The type of item in the tree this element represents.
- L66 _public member_ `TObjectPtr<UMovieGraphNode> SettingsNode = nullptr;` — If this element represents a node in the graph, this is the pointer to that node. If the element represents a property, this is the pointer to the owning node.
- L69 _public member_ `const FProperty* SettingsProperty = nullptr;` — If this element represents a property on a node, this is the pointer to that property.
- L72 _public member_ `TWeakObjectPtr<UMovieGraphEvaluatedConfig> FlattenedGraph = nullptr;` — The result of the graph traversal.
- L75 _public member_ `TWeakPtr<const FActiveRenderSettingsTreeElement> ParentElement = nullptr;` — This element's parent element in the tree.
- L79 _private member_ `mutable TArray<TSharedPtr<FActiveRenderSettingsTreeElement>> ChildrenCache;` — The (cached) child elements nested under this element.
- L82 _private member_ `mutable uint32 ElementHash = 0;` — The (cached) hash of this element.

#### enum `FActiveRenderSettingsTreeElement::EElementType`  
`enum class EElementType : uint8`  
_L23-29_
- desc: The type of this element.
- L25 _public enumerator_ `Root` — A root element; does not represent any actual data within the graph
- L26 _public enumerator_ `NamedBranch` — Represents a named branch (output) within the graph
- L27 _public enumerator_ `Node` — Represents a settings node within the graph
- L28 _public enumerator_ `Property` — Represents a property under an element with type EElementType::Node

#### class `SMovieGraphActiveRenderSettingsTreeItem`  
`class SMovieGraphActiveRenderSettingsTreeItem : public SMultiColumnTableRow<TSharedPtr<FActiveRenderSettingsTreeElement>>`  
_L88-106_
- inherits: `SMultiColumnTableRow<TSharedPtr<FActiveRenderSettingsTreeElement>>`
- desc: The widget that is responsible for generating the per-column content for each element in the tree.
- L90 _private function_ `SLATE_BEGIN_ARGS(SMovieGraphActiveRenderSettingsTreeItem)`
- L91 _private prototype_ `SLATE_END_ARGS() static const FName ColumnID_Name;`
- L94 _private member_ `static const FName ColumnID_Value;`
- L96 _private prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, const TSharedPtr<FActiveRenderSettingsTreeElement>& InTreeElement);`
- L100 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L105 _private member_ `TWeakPtr<FActiveRenderSettingsTreeElement> WeakTreeElement;` — The element that this tree item is displaying.

#### class `SMovieGraphActiveRenderSettingsTabContent`  
`class SMovieGraphActiveRenderSettingsTabContent : public SCompoundWidget`  
_L111-187_
- inherits: `SCompoundWidget`
- desc: Contents of the "Active Render Settings" tab in the graph asset editor.
- L114 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphActiveRenderSettingsTabContent) : _Graph(nullptr)`
- L120 _public prototype_ `SLATE_ARGUMENT(class UMovieGraphConfig*, Graph) SLATE_END_ARGS();` — The graph that is currently displayed.
- L124 _public prototype_ `void Construct(const FArguments& InArgs);`
- L128 _private prototype_ `void TraverseGraph();` — Traverses the graph. Populates the FlattenedGraph member and refreshes the UI view.
- L131 _private prototype_ `FReply OnEvaluateGraphClicked();` — Handles the button click for evaluating the graph.
- L134 _private prototype_ `TSharedRef<SWidget> GenerateEvaluationContextMenu();` — Generates the menu for the Evaluation Context button.
- L137 _private prototype_ `void OnExpansionChanged(TSharedPtr<FActiveRenderSettingsTreeElement> InElement, bool bInExpanded);` — Handles the expansion state change of an element in the tree.
- L140 _private prototype_ `void RestoreExpansionStateRecursive(const TSharedPtr<FActiveRenderSettingsTreeElement>& InElement);` — Recursively restores the cached expansion state of the tree, starting at the specified element.
- L143 _private prototype_ `TSharedRef<ITableRow> GenerateTreeRow(TSharedPtr<FActiveRenderSettingsTreeElement> InTreeElement, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row in the tree widget based on the provided element.
- L146 _private prototype_ `void GetChildrenForTree(TSharedPtr<FActiveRenderSettingsTreeElement> InItem, TArray<TSharedPtr<FActiveRenderSettingsTreeElement>>& OutChildren);` — Gets the child elements in the tree for the provided element.
- L149 _private prototype_ `FText GetQueueButtonText() const;` — Gets the text that is displayed on the queue picker button (in the evaluation context menu).
- L152 _private prototype_ `TSharedRef<SWidget> MakeQueueButtonMenuContents();` — Generates the menu contents for the queue picker button. Populates the QueuePickerWidget member.
- L155 _private prototype_ `void HandleJobSelected(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);` — Handles a new job selection in the evaluation context menu.
- L159 _private member_ `TWeakObjectPtr<UMovieGraphConfig> CurrentGraph = nullptr;` — The runtime graph that this UI gets data from.
- L162 _private member_ `TSharedPtr<STreeView<TSharedPtr<FActiveRenderSettingsTreeElement>>> TreeView = nullptr;` — The main tree widget displayed in the tab.
- L165 _private member_ `TSet<uint32> ExpandedElements;` — The hashes of elements that are currently expanded in the tree.
- L168 _private member_ `TStrongObjectPtr<UMovieGraphEvaluatedConfig> FlattenedGraph = nullptr;` — The last result of a graph traversal.
- L171 _private member_ `TArray<TSharedPtr<FActiveRenderSettingsTreeElement>> RootElements;` — The root-most elements in the tree, which are always present.
- L174 _private member_ `TSharedPtr<SWidget> QueuePickerWidget = nullptr;` — The widget that houses the queue asset picker.
- L177 _private member_ `TWeakObjectPtr<UMoviePipelineQueue> TraversalQueue = nullptr;` — The queue that is selected in the evaluation context settings.
- L180 _private member_ `TWeakObjectPtr<UMoviePipelineExecutorJob> TraversalJob = nullptr;` — The job that is selected in the evaluation context settings.
- L183 _private member_ `TArray<TSharedPtr<FString>> AvailableJobsInQueue;` — The jobs that are available to be selected in the evaluation context settings.
- L186 _private member_ `FString TraversalError;` — An error that was set during traversal. This will show up in the UI and prevent the tree from being shown.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Graph/SMovieGraphMembersTabContent.h` (Private)


#### class `SMovieGraphMembersTabContent`  
`class SMovieGraphMembersTabContent : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L20-121_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: Contents of the "Members" tab in the graph asset editor.
- L23 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnActionSelected, const TArray<TSharedPtr<FEdGraphSchemaAction>>&, ESelectInfo::Type);`
- L25 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphMembersTabContent) : _Graph(nullptr) , _Editor(nullptr)`
- L32 _public prototype_ `SLATE_EVENT(FOnActionSelected, OnActionSelected) SLATE_ARGUMENT(class UMovieGraphConfig*, Graph) SLATE_ARGUMENT(TSharedPtr<FAssetEditorToolkit>, Editor) SLATE_END_ARGS();` — An event which is triggered when an action is selected.
- L42 _public prototype_ `void Construct(const FArguments& InArgs);`
- L45 _public prototype_ `FReply OnActionDragged(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, const FPointerEvent& MouseEvent);` — Handler for when an action in the action menu is dragged.
- L48 _public prototype_ `FReply OnCategoryDragged(const FText& InCategory, const FPointerEvent& MouseEvent);` — Handler for when a category in the action menu is dragged.
- L51 _public prototype_ `TSharedRef<SWidget> CreateActionWidget(FCreateWidgetForActionData* CreateWidgetForActionData) const;` — Creates the widget for an action within the action menu.
- L54 _public prototype_ `void ClearSelection() const;` — Resets the selected members in the UI.
- L57 _public prototype_ `void DeleteSelectedMembers();` — Deletes the member(s) which are currently selected from the graph and the UI.
- L60 _public prototype_ `bool CanDeleteSelectedMembers() const;` — Determines if all selected member(s) can be deleted.
- L63 _public prototype_ `void DuplicateSelectedMembers();` — Duplicates the member(s) which are currently selected in the UI.
- L66 _public prototype_ `bool CanDuplicateSelectedMembers() const;` — Determines if at least one selected member can be duplicated.
- L69 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L70 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L87 _private member_ `static const TArray<FText> ActionMenuSectionNames;` — The names of the sections in the action widget.
- L89 _private prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);`
- L90 _private prototype_ `void CollectStaticSections(TArray<int32>& StaticSectionIDs);`
- L91 _private prototype_ `FText GetSectionTitle(int32 InSectionID);`
- L92 _private prototype_ `TSharedRef<SWidget> GetSectionWidget(TSharedRef<SWidget> RowWidget, int32 InSectionID);`
- L95 _private prototype_ `bool ActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName) const;` — Returns true if the action matches the specified name, else false.
- L98 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Handler which deals with populating the context menu.
- L101 _private prototype_ `FReply OnAddButtonClickedOnSection(const int32 InSectionID);` — Handler which deals with clicking the add button for an action section.
- L104 _private prototype_ `void RefreshMemberActions(class UMovieGraphMember* UpdatedMember = nullptr);` — Refresh/regenerate the action menu when the given member is updated.
- L108 _private member_ `TWeakPtr<FAssetEditorToolkit> EditorToolkit;` — The editor that this widget is associated with.
- L111 _private member_ `TSharedPtr<SGraphActionMenu> ActionMenu;` — The action menu displayed in the UI which allows for creation/manipulation of graph members (eg, variables).
- L114 _private member_ `TObjectPtr<UMovieGraphConfig> CurrentGraph;` — The runtime graph that this UI gets/sets data on.
- L117 _private member_ `FOnActionSelected OnActionSelected;` — Delegate to call when an action is selected
- L120 _private member_ `TMap<TWeakObjectPtr<UMovieGraphMember>, FDelegateHandle> MemberChangedHandles;` — Handles to delegates handling member changes.

#### enum `SMovieGraphMembersTabContent::EActionSection`  
`enum class EActionSection : uint8`  
_L75-84_
- desc: The section identifier in the action widget.
- L77 _public enumerator_ `Invalid`
- L79 _public enumerator_ `Inputs`
- L80 _public enumerator_ `Outputs`
- L81 _public enumerator_ `Variables`
- L83 _public enumerator_ `COUNT`

#### class `FMovieGraphDragAction_Variable`  
`class FMovieGraphDragAction_Variable : public FGraphSchemaActionDragDropAction`  
_L124-145_
- inherits: `FGraphSchemaActionDragDropAction`
- desc: Drag-and-drop action which handles variable members.
- L127 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FMovieGraphDragAction_Variable, FGraphSchemaActionDragDropAction) static TSharedRef<FMovieGraphDragAction_Variable> New( TSharedPtr<FEdGraphSchemaAction> InAction, UMovieGraphVariable* InVariable);`
- L132 _public prototype_ `virtual void HoverTargetChanged() override;`
- L133 _public prototype_ `virtual FReply DroppedOnAction(TSharedRef<FEdGraphSchemaAction> Action) override;`
- L134 _public prototype_ `virtual FReply DroppedOnCategory(FText Category) override;`
- L135 _public prototype_ `virtual FReply DroppedOnPanel( const TSharedRef<SWidget>& InPanel, const FVector2f& InScreenPosition, const FVector2f& InGraphPosition, UEdGraph& InGraph) override;`
- L139 _protected prototype_ `virtual void GetDefaultStatusSymbol( const FSlateBrush*& OutPrimaryBrush, FSlateColor& OutIconColor, FSlateBrush const*& OutSecondaryBrush, FSlateColor& OutSecondaryColor) const override;`
- L144 _private member_ `TWeakObjectPtr<UMovieGraphVariable> WeakVariable;` — The variable member that the drag-and-drop is associated with.

#### class `FMovieGraphDragAction_Category`  
`class FMovieGraphDragAction_Category : public FGraphSchemaActionDragDropAction`  
_L148-164_
- inherits: `FGraphSchemaActionDragDropAction`
- desc: Drag-and-drop action which handles variable categories.
- L151 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FMovieGraphDragAction_Category, FGraphSchemaActionDragDropAction) static TSharedRef<FMovieGraphDragAction_Category> New(const FText& InCategory, UMovieGraphConfig* InGraph);`
- L155 _public prototype_ `virtual void HoverTargetChanged() override;`
- L156 _public prototype_ `virtual FReply DroppedOnCategory(FText Category) override;`
- L160 _public member_ `FText DraggedCategory;` — The category that is being dragged.
- L163 _public member_ `UMovieGraphConfig* GraphConfig = nullptr;` — The graph associated with the drag/drop action.

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnActionSelected, const TArray<TSharedPtr<FEdGraphSchemaAction>>&, ESelectInfo::Type);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelineAssetEditor.h` (Private)


#### class `UMoviePipelineAssetEditor`  
`class UMoviePipelineAssetEditor : public UAssetEditor`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UAssetEditor`
- L16 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L17 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;`
- L19 _public prototype_ `void SetObjectToEdit(UObject* InObject);`
- L22 _private member_ `TObjectPtr<UObject> ObjectToEdit;` — `UPROPERTY(Transient)`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelineCommands.h` (Private)


#### class `FMoviePipelineCommands`  
`class FMoviePipelineCommands : public TCommands<FMoviePipelineCommands>`  
_L8-21_
- inherits: `TCommands<FMoviePipelineCommands>`
- L11 _public prototype_ `FMoviePipelineCommands();`
- L13 _public member_ `TSharedPtr<FUICommandInfo> ResetStatus;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> ZoomToWindow;` — Graph commands
- L17 _public member_ `TSharedPtr<FUICommandInfo> ZoomToSelection;`
- L20 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelineConfigAssetEditor.h` (Private)


#### class `FMoviePipelineConfigAssetEditor`  
`class FMoviePipelineConfigAssetEditor : public FBaseAssetToolkit`  
_L11-29_
- inherits: `FBaseAssetToolkit`
- L15 _public prototype_ `FMoviePipelineConfigAssetEditor(UAssetEditor* InOwningAssetEditor);`
- L16 _public prototype_ `virtual ~FMoviePipelineConfigAssetEditor() = default;`
- L19 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;` — FBaseAssetToolkit interface
- L20 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L21 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L24 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ConfigEditor(const FSpawnTabArgs& Args);`
- L27 _private member_ `static const FName ContentTabId;`
- L28 _private member_ `TSharedPtr<class SMoviePipelineConfigPanel> ConfigEditorPanel;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelineFunctionalTestBase.h` (Private)


#### class `AMoviePipelineFunctionalTestBase`  
`class AMoviePipelineFunctionalTestBase : public AFunctionalTest`  
_L24-91_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `AFunctionalTest`
- desc: Base class for Movie Pipeline functional tests which render pre-made queues and compare their output against pre-existing render outputs.
- L29 _public prototype_ `AMoviePipelineFunctionalTestBase();`
- L33 _protected prototype_ `virtual void PrepareTest() override;` — AFunctionalTest
- L34 _protected prototype_ `virtual bool IsReady_Implementation() override;`
- L35 _protected prototype_ `virtual void StartTest() override;`
- L37 _protected function_ `virtual bool IsEditorOnlyLoadedInPIE() const override`
- L42 _protected prototype_ `void OnJobShotFinished(FMoviePipelineOutputData InOutputData);`
- L43 _protected prototype_ `void OnMoviePipelineFinished(FMoviePipelineOutputData InOutputData);`
- L44 _protected prototype_ `void CompareRenderOutputToGroundTruth(FMoviePipelineOutputData InOutputData);`
- L52 _private prototype_ `FIntPoint GetExpectedOutputResolution(const FMoviePipelineOutputData& InOutputData, FString& OutErrorMsg) const;` — Gets the resolution that the test-generated images are expected to be. If there was an error getting this, OutErrorMsg will be populated with the error message, and the returned point will be (0, 0).
- L60 _private prototype_ `template<typename IdentifierType, typename OutputDataType> void UpdateGroundTruthToTestImageMap( const TMap<IdentifierType, OutputDataType>& InGroundTruthData, const TMap<IdentifierType, OutputDataType>& InTestData, const FString& InReportDirectory, TMap<FString, FString>& OutGroundTruthToTestImageMap);` — Updates OutGroundTruthToTestImageMap by linking frames in InGroundTruthData to those in InTestData. Keys in OutGroundTruthToTestImageMap are the ground-truth frame path (absolute), and values are the test-generated frame path (absolute).
- L69 _protected member_ `TObjectPtr<UMoviePipelineQueue> QueuePreset;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movie Pipeline")`
- L72 _protected member_ `EImageTolerancePreset ImageToleranceLevel;` — `UPROPERTY(EditAnywhere, Category = "Movie Pipeline")`
- L75 _protected member_ `FImageTolerance CustomImageTolerance;` — `UPROPERTY(EditAnywhere, Category = "Movie Pipeline")`
- L83 _protected member_ `bool bPerformDiff;` — `UPROPERTY(EditAnywhere, Category = "Movie Pipeline")` — Boolean flag to toggle screenshot pixel comparison of rendered versus ground truth images. True - screenshot pixel comparison will be performed. False - screenshot pixel comparison will not be performed.  Expects ground truth images to exist to verify that the required number of images were rendered, even if those ground truth images are not used in diffs.
- L87 _protected member_ `TObjectPtr<UMoviePipelineBase> ActiveMoviePipeline;` — `UPROPERTY(Transient)`
- L90 _protected member_ `TObjectPtr<UMoviePipelineQueue> ActiveQueue;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelinePIEExecutorSettings.h` (Private)


#### class `UMoviePipelinePIEExecutorSettings`  
`class UMoviePipelinePIEExecutorSettings : public UDeveloperSettings`  
_L12-42_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = Editor, defaultconfig, meta = (DisplayName = "Movie Pipeline In Editor"))`
- inherits: `UDeveloperSettings`
- desc: This is the implementation responsible for executing the rendering of multiple movie pipelines within the editor using PIE.
- L18 _public function_ `virtual FName GetContainerName() const override` — Gets the settings container name for the settings, either Project or Editor
- L20 _public function_ `virtual FName GetCategoryName() const override` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L29 _public member_ `int32 InitialDelayFrameCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, meta = (UIMin = "0", ClampMin = "0", UIMax = "150"), Category = "Startup")` — How long should we wait after being initialized to start doing any work? This can be used to work around situations where the game is not fully loaded by the time the pipeline is automatically started and it is important that the game is fully loaded before we do any work (such as evaluating frames for warm-up).
- L41 _public member_ `bool bResizePIEWindowToOutputResolution = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Startup")` — Should the PIE Window be created at the same resolution as the MRQ Output? By default we create the window at 720p for a nicer user experience, but this can be used to work around a widget scaling issue with UMG Widgets when using the UI Renderer setting. PIE is still limited by your monitor's resolution so you will need a monitor at least as big as your requested output for this to work (or can be combined with launching the editor with -ForceRes). Warning: Don't use this setting in combination with HighResTiling, as the main backbuffer will have to get resized to your final output resolution which will be too large.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelinePostRenderFileDisplayProcessor.h` (Private)


#### class `UMoviePipelineOutputDataContainer`  
`class UMoviePipelineOutputDataContainer : public UObject`  
_L14-22_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: UObject wrapper for the FMoviePipelineOutputData struct so it can be saved in a UPackage.
- L21 _public member_ `TArray<FMoviePipelineOutputData> OutputData;` — `UPROPERTY()` — The output data that the pipeline generated. Each entry in the array is the output data for one job.

#### class `FMoviePipelinePostRenderFileDisplayProcessor`  
`class FMoviePipelinePostRenderFileDisplayProcessor`  
_L25-135_
- desc: Handles sorting through all of the images/videos generated by a render(s), and opening them according to post-render editor preferences.
- L28 _public prototype_ `explicit FMoviePipelinePostRenderFileDisplayProcessor(const FMovieGraphPostRenderSettings& InPostRenderSettings);`
- L34 _public prototype_ `void AddFiles(const FMoviePipelineOutputData& InRenderOutputData);` — Adds a set of files to the processor. This should only be called once per job, otherwise duplicate data may be added. Both graph and preset output data is supported.
- L37 _public prototype_ `void OpenFiles() const;` — Opens/displays rendered images/videos according to the post-render settings the class was initialized with.
- L43 _public prototype_ `static void OpenPreviousFiles(const FMovieGraphPostRenderSettings& InPostRenderSettings);` — Open the files that OpenFiles() last opened, using the provided post-render settings (the previous files can be played back with different settings than they were originally opened with).
- L46 _public prototype_ `static bool CanOpenPreviousFiles();` — Determines if OpenPreviousFiles() has any files that it can open.
- L72 _private prototype_ `FFilesToOpen FindFilesToOpen(FMoviePipelineOutputData& InPipelineOutputData) const;` — Sorts through all of the given rendered data and determines which images/videos should be opened.
- L75 _private prototype_ `void GetFilteredFilesToOpen(const FFilesToOpen& InFilesToOpen, TArray<FString>& OutFilteredFilesToOpen, const FMovieGraphPostRenderVideoPlayOptions*& OutFilteredPlayOptions) const;` — Reduces the files returned to FindFilesToOpen() to a set of files that can be opened in the same application.
- L78 _private prototype_ `void GroupFilesByShot( FMoviePipelineOutputData& InPipelineOutputData, TArray<TMap<FString, TArray<FString>>>& InImagesGroupedByShot, TArray<TMap<FString, TArray<FString>>>& InFrameTemplateImagesGroupedByShot, TArray<TMap<FString, TArray<FString>>>& InVideosGroupedByShot) const;` — Group all pipeline output data by shot (and additionally extension within each shot) for three categories: images, frame-templated images, and movies.
- L85 _private prototype_ `void GroupFilesByShot_Graph( FMoviePipelineOutputData& InPipelineOutputData, TArray<TMap<FString, TArray<FString>>>& InImagesGroupedByShot, TArray<TMap<FString, TArray<FString>>>& InFrameTemplateImagesGroupedByShot, TArray<TMap<FString, TArray<FString>>>& InVideosGroupedByShot) const;` — Helper that implements graph-based logic for GroupFilesByShot().
- L92 _private prototype_ `void GroupFilesByShot_Preset( FMoviePipelineOutputData& InPipelineOutputData, TArray<TMap<FString, TArray<FString>>>& InImagesGroupedByShot, TArray<TMap<FString, TArray<FString>>>& InFrameTemplateImagesGroupedByShot, TArray<TMap<FString, TArray<FString>>>& InVideosGroupedByShot) const;` — Helper that implements preset-based logic for GroupFilesByShot().
- L98 _private prototype_ `void GetHighestPriorityExtensions( const TArray<TMap<FString, TArray<FString>>>& InImagesGroupedByShot, const TArray<TMap<FString, TArray<FString>>>& InVideosGroupedByShot, FString& OutHighestPriorityImageExtension, FString& OutHighestPriorityVideoExtension) const;`
- L105 _private prototype_ `void LaunchFilesWithSettings(const TArray<FString>& InFilesToOpen, const FMovieGraphPostRenderVideoPlayOptions* InPlayOptions, const TTuple<FString, FString>& InFrameRangeToOpen) const;` — Opens the given files according to the playback settings provided. The frame range of files to open must be specified, but can be empty strings (to open all frames).
- L111 _private prototype_ `int32 GetExtensionPriorityIndex(const FString& InExtension) const;` — Gets the extension's priority according to the Output Type Priority Order list, or 10000 if the extension was not found. A lower index indicates higher priority.
- L114 _private prototype_ `void GetStartAndEndFrames(const FString& InTemplatedPath, const TArray<FString>& InImagePaths, FFilesToOpen& InOutFilesToOpen) const;` — Gets the start and end frame of the images provided, based on the frame-templated path. The string and int-based frame numbers in InOutFilesToOpen are updated.
- L117 _private prototype_ `static void PersistOutputData(const TArray<FMoviePipelineOutputData>& InOutputData);` — Persists the provided pipeline output data (one array entry per job) to disk at /Temp/MovieRenderPipeline/MostRecentOutputData.
- L123 _private prototype_ `static UMoviePipelineOutputDataContainer* GetPersistedOutputData();` — Gets the most recently persisted pipeline output data (see PersistOutputData()). Note that if data has not been persisted yet, this method will still return a valid pointer to an output data container (however, it will not contain any file paths within it).
- L127 _private member_ `inline static const FString PersistedOutputDataPackagePath = TEXT("/Te` — The package path for the output data persisted across editor sessions (see PersistOutputData()).
- L130 _private member_ `FMovieGraphPostRenderSettings PostRenderSettings;` — The post-render settings the class was initialized with. Usually sourced from the editor preferences.
- L134 _private member_ `mutable TArray<FMoviePipelineOutputData> PipelineOutputData;` — Pipeline output data sourced from AddFiles(). Each entry in the array is one call from AddFiles().

#### struct `FMoviePipelinePostRenderFileDisplayProcessor::FFilesToOpen`  
`struct FFilesToOpen`  
_L50-69_
- desc: Keeps track of the working set of images/videos that should be opened, and any other associated transient data.
- L52 _public member_ `TArray<FString> Images;`
- L53 _public member_ `TArray<FString> AppleProResMovies;`
- L54 _public member_ `TArray<FString> AvidDNxHRMovies;`
- L55 _public member_ `TArray<FString> MP4Movies;`
- L61 _public member_ `FString StartFrameString;` — The start and end frame of the first image sequence contained in Images. Representing these as strings is a little strange. It's to preserve the padding found in the source filename so it doesn't have to be re-derived later in the pipeline (where determining what that padding is may be tricky). For example, instead of storing an int-based start frame of 10, we can store it as "0010", which is how it appears in the filename.
- L62 _public member_ `FString EndFrameString;`
- L64 _public member_ `int32 StartFrame = TNumericLimits<int32>::Min();`
- L65 _public member_ `int32 EndFrame = TNumericLimits<int32>::Min();`
- L67 _public member_ `FString HighestPriorityImageExtension;`
- L68 _public member_ `FString HighestPriorityVideoExtension;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelineQuickRenderMenu.h` (Private)


#### class `FMoviePipelineQuickRenderMenu`  
`class FMoviePipelineQuickRenderMenu`  
_L15-61_
- desc: Generates the Quick Render button, options menu, and settings dialog.
- L18 _public prototype_ `FMoviePipelineQuickRenderMenu() = default;`
- L21 _public prototype_ `static void AddQuickRenderButtonToToolMenu(UToolMenu* InMenu);` — Adds the Quick Render button to the specified tool menu.
- L24 _public prototype_ `static void RemoveQuickRenderButtonToolMenu();` — Removes the Quick Render button from level editor toolbar.
- L27 _private prototype_ `static void LoadQuickRenderSettings();`
- L29 _private prototype_ `static void QuickRenderButtonPressed();`
- L31 _private prototype_ `static TSharedRef<SWidget> GenerateQuickRenderOptionsMenu();`
- L32 _private prototype_ `static void OpenQuickRenderSettingsWindow(const FToolMenuContext& InToolMenuContext);`
- L33 _private prototype_ `static TSharedRef<SWidget> GenerateQuickRenderSettingsWindowToolbar();`
- L35 _private prototype_ `static void GenerateModesMenuSection(UToolMenu* InMenu);`
- L36 _private prototype_ `static void GenerateQuickRenderMenuSection(UToolMenu* InMenu);`
- L37 _private prototype_ `static void GenerateQuickRenderConfigurationMenuSection(UToolMenu* InMenu);`
- L38 _private prototype_ `static void GenerateOutputMenuSection(UToolMenu* InMenu);`
- L39 _private prototype_ `static void GenerateSettingsMenuSection(UToolMenu* InMenu);`
- L41 _private prototype_ `static FSlateIcon GetIconForQuickRenderMode(EMovieGraphQuickRenderMode QuickRenderMode);`
- L44 _private prototype_ `static void InitQuickRenderModeSettingsFromMode(const EMovieGraphQuickRenderMode QuickRenderMode);` — Populates the QuickRenderModeSettings member with the settings for the provided mode.
- L47 _private prototype_ `static void UpdateVariableAssignmentsForCurrentGraph();` — Updates the variable assignments for the graph preset in the currently active mode.
- L51 _private member_ `inline static TWeakPtr<SWindow> WeakQuickRenderSettingsWindow;` — Weak pointer to the Settings window widget.
- L54 _private member_ `inline static TWeakPtr<class IDetailsView> WeakDetailsPanel;` — Weak pointer to the details panel within the Settings window.
- L57 _private member_ `inline static TStrongObjectPtr<UMovieGraphQuickRenderModeSettings> QuickRenderModeSettings = nullptr;` — The settings for the currently-active mode within Quick Render.
- L60 _private member_ `inline static TArray<TSharedPtr<FName>> QuickRenderModes;` — All of the different mode names that are available to be used.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelineQuickRenderUIState.h` (Private)


#### struct `FMoviePipelineQuickRenderUIState`  
`struct FMoviePipelineQuickRenderUIState`  
_L14-62_
- desc: UI state management for Quick Render. Some of these setting values returned here may differ from what Quick Render is actively using. For example, the mode returned here may be different if Quick Render was started from scripting with a mode that differs from the UI's current mode. Also note that the settings here are distinct from the settings in UMovieGraphQuickRenderSettings. Those are persisted to an asset, whereas these are persisted to an INI.
- L17 _public prototype_ `static EMovieGraphQuickRenderButtonMode GetQuickRenderButtonMode();` — Gets the mode that the Quick Render button is currently in.
- L20 _public prototype_ `static void SetQuickRenderButtonMode(const EMovieGraphQuickRenderButtonMode NewButtonMode);` — Sets the mode that the Quick Render button is currently using.
- L26 _public prototype_ `static EMovieGraphQuickRenderMode GetQuickRenderMode();` — Gets the mode that Quick Render will use when starting a new render. Sometimes called the "system" render mode, as opposed to the "window" render mode (see GetWindowQuickRenderMode()).
- L29 _public prototype_ `static void SetQuickRenderMode(const EMovieGraphQuickRenderMode NewMode);` — Sets the mode that Quick Render will use when starting a new render.
- L36 _public prototype_ `static EMovieGraphQuickRenderMode GetWindowQuickRenderMode();` — Gets the render mode that the Quick Render settings window currently displays. This is different than GetQuickRenderMode(), or the "system" render mode. When the settings window opens, this mode is independent of the system render mode. When a render starts, the window mode is copied to the system render mode. This setting is transient and not persisted across editor sessions.
- L39 _public prototype_ `static void SetWindowQuickRenderMode(const EMovieGraphQuickRenderMode NewMode);` — Sets the "window" render mode. See notes on GetWindowQuickRenderMode().
- L42 _public prototype_ `static bool GetShouldShowSettingsBeforeRender();` — Gets whether Quick Render should show the Settings dialog before a render starts.
- L45 _public prototype_ `static void SetShouldShowSettingsBeforeRender(const bool bNewValue);` — Sets whether Quick Render should show the Settings dialog before a render starts.
- L49 _private member_ `inline static const TCHAR* QuickRenderIniSection = TEXT("Mov` — The name of the section that Quick Render UI settings are stored in within the target ini file.
- L52 _private member_ `inline static const TCHAR* QuickRenderIniSettingName_ButtonMode = TEXT("But` — Ini setting name for: What mode the Quick Render button is using.
- L55 _private member_ `inline static const TCHAR* QuickRenderIniSettingName_Mode = TEXT("Mod` — Ini setting name for: The mode that Quick Render will use when a render begins. Generally dictates the level sequence and camera(s) that will be used.
- L58 _private member_ `inline static const TCHAR* QuickRenderIniSettingName_ShowSettingsBeforeQuickRender = TEXT("bSh` — Ini setting name for: Whether the settings dialog should be shown before a Quick Render is started.
- L61 _private member_ `static inline EMovieGraphQuickRenderMode WindowRenderMode = EMovieGraphQuickRenderMode::CurrentViewport;` — The transient "window" quick render mode. This is not persisted to ini.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MovieRenderPipelineEditorModule.h` (Private)


#### class `FMovieRenderPipelineEditorModule`  
`class FMovieRenderPipelineEditorModule : public IMovieRenderPipelineEditorModule`  
_L13-44_
- inherits: `IMovieRenderPipelineEditorModule`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private prototype_ `void RegisterSettings();`
- L23 _private prototype_ `void UnregisterSettings();`
- L25 _private prototype_ `void RegisterMovieRenderer();`
- L26 _private prototype_ `void UnregisterMovieRenderer();`
- L28 _private prototype_ `void RegisterTypeCustomizations();`
- L29 _private prototype_ `void UnregisterTypeCustomizations();`
- L31 _private prototype_ `void RegisterToolbarItem();`
- L32 _private prototype_ `void UnregisterToolbarItem();`
- L34 _private member_ `FDelegateHandle MovieRendererDelegate;`
- L37 _private member_ `TSharedPtr<FMovieGraphPanelPinFactory> GraphPanelPinFactory;` — Pin factory for the render graph.
- L40 _private member_ `TSharedPtr<FMoviePipelineJobNameEditSink> JobNameEditSink;` — ObjectNameEditSink for UMoviePipelineExecutorJob instances in the details panel.
- L43 _private member_ `TSharedPtr<FMoviePipelineShotNameEditSink> ShotNameEditSink;` — ObjectNameEditSink for UMoviePipelineExecutorShot instances in the details panel.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MovieRenderPipelineEditorUtils.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace MovieRenderPipelineEditor` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::MovieRenderPipelineEditor`)
- L8 _prototype_ `bool PerformLocalRender();` (scope `UE::MovieRenderPipelineEditor::Private`) — Performs a local render using the queue currently loaded up in the Movie Render Queue editor. Returns true if a render was started, else false.
- L11 _prototype_ `bool CanPerformLocalRender();` (scope `UE::MovieRenderPipelineEditor::Private`) — Determines if a local render is currently able to be performed.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MovieRenderPipelineStyle.h` (Private)


#### class `FMovieRenderPipelineStyle`  
`class FMovieRenderPipelineStyle : public FSlateStyleSet`  
_L11-24_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the Movie Render Pipeline UI
- L15 _public member_ `static FName StyleName;`
- L18 _public prototype_ `static FMovieRenderPipelineStyle& Get();` — Access the singleton instance for this style set
- L22 _private prototype_ `FMovieRenderPipelineStyle();`
- L23 _private prototype_ `~FMovieRenderPipelineStyle();`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/Graph/SMovieGraphConfigPanel.h` (Private)


#### class `SMoviePipelineGraphPanel`  
`class SMoviePipelineGraphPanel : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L26-146_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- desc: Outermost widget that is used for adding and removing jobs from the Movie Pipeline Queue Subsystem.
- L29 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGraphSelectionChanged, TArray<UObject*>);`
- L31 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineGraphPanel) : _Graph(nullptr)`
- L36 _public prototype_ `SLATE_EVENT(FOnGraphSelectionChanged, OnGraphSelectionChanged) SLATE_ARGUMENT(class UMovieGraphConfig*, Graph) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _public prototype_ `void ClearGraphSelection() const;` — Clears the selection in the graph widget being displayed.
- L49 _public prototype_ `TWeakPtr<SGraphEditor> GetGraphEditor() const;` — Gets the graph editor that's contained within this widget.
- L52 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;` — FEditorUndoClient interface
- L53 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L54 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L58 _private prototype_ `FReply OnRenderLocalRequested();`
- L59 _private prototype_ `bool IsRenderLocalEnabled() const;`
- L60 _private prototype_ `FReply OnRenderRemoteRequested();`
- L61 _private prototype_ `bool IsRenderRemoteEnabled() const;`
- L64 _private prototype_ `void OnEditJobConfigRequested(TWeakObjectPtr<UMoviePipelineExecutorJob> InJob, TWeakObjectPtr<UMoviePipelineExecutorShot> InShot);` — When they want to edit the current configuration for the job
- L66 _private prototype_ `void OnJobPresetChosen(TWeakObjectPtr<UMoviePipelineExecutorJob> InJob, TWeakObjectPtr<UMoviePipelineExecutorShot> InShot);` — When an existing preset is chosen for the specified job.
- L67 _private prototype_ `void OnConfigUpdatedForJob(TWeakObjectPtr<UMoviePipelineExecutorJob> InJob, TWeakObjectPtr<UMoviePipelineExecutorShot> InShot, UMoviePipelineConfigBase* InConfig);`
- L68 _private prototype_ `void OnConfigUpdatedForJobToPreset(TWeakObjectPtr<UMoviePipelineExecutorJob> InJob, TWeakObjectPtr<UMoviePipelineExecutorShot> InShot, UMoviePipelineConfigBase* InConfig);`
- L69 _private prototype_ `void OnConfigWindowClosed();`
- L71 _private prototype_ `void OnSelectionChanged(const TArray<UMoviePipelineExecutorJob*>& InSelectedJobs, const TArray<UMoviePipelineExecutorShot*>& InSelectedShots);`
- L72 _private prototype_ `TArray<UMovieGraphNode*> GetSelectedModelNodes() const;`
- L74 _private prototype_ `TSharedRef<SWidget> OnGenerateSavedQueuesMenu();`
- L75 _private prototype_ `bool OpenSaveDialog(const FString& InDefaultPath, const FString& InNewNameSuggestion, FString& OutPackageName);`
- L76 _private prototype_ `bool GetSavePresetPackageName(const FString& InExistingName, FString& OutName);`
- L77 _private prototype_ `void OnSaveAsAsset();`
- L78 _private prototype_ `void OnImportSavedQueueAssest(const FAssetData& InPresetAsset);`
- L80 _private prototype_ `void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);`
- L81 _private prototype_ `void OnNodeDoubleClicked(class UEdGraphNode* Node);`
- L82 _private prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);`
- L85 _private prototype_ `FGraphAppearanceInfo GetGraphAppearanceInfo() const;` — Provides appearance info to the graph widget.
- L87 _private member_ `TObjectPtr<class UMovieGraphConfig> CurrentGraph;`
- L91 _private prototype_ `void MakeEditorCommands();` — UMoviePipelineConfigBase* AllocateTransientPreset();
- L94 _private prototype_ `void OnCreateComment() const;` — Creates a new, empty comment in the graph around the currently selected nodes.
- L96 _private prototype_ `void SelectAllNodes();`
- L97 _private prototype_ `bool CanSelectAllNodes() const;`
- L98 _private prototype_ `bool CanDeleteSelectedNodes() const;`
- L99 _private prototype_ `void DeleteSelectedNodes();`
- L100 _private prototype_ `void CopySelectedNodes();`
- L101 _private prototype_ `bool CanCopySelectedNodes() const;`
- L102 _private prototype_ `void CutSelectedNodes();`
- L103 _private prototype_ `bool CanCutSelectedNodes() const;`
- L104 _private prototype_ `void PasteNodes();`
- L105 _private prototype_ `void PasteNodesHere(const FVector2D& Location);`
- L106 _private prototype_ `bool CanPasteNodes() const;`
- L107 _private prototype_ `void DuplicateNodes();`
- L108 _private prototype_ `bool CanDuplicateNodes() const;`
- L111 _private prototype_ `void SetEnabledStateForSelectedNodes(const ENodeEnabledState NewState) const;` — Set the enabled state for the currently selected nodes.
- L118 _private prototype_ `ECheckBoxState CheckEnabledStateForSelectedNodes(const ENodeEnabledState EnabledStateToCheck) const;` — Attempt to match the given enable state for currently-selected nodes. If StateToCheck matches all selected nodes, returns ECheckBoxState::Checked or ECheckBoxState::Unchecked; if there is a mismatch, returns ECheckBoxState::Undetermined.
- L121 _private prototype_ `bool CanDisableSelectedNodes() const;` — Determines if all of the selected nodes can have their enable/disable state toggled.
- L123 _private prototype_ `void OnAlignTop();`
- L124 _private prototype_ `void OnAlignMiddle();`
- L125 _private prototype_ `void OnAlignBottom();`
- L126 _private prototype_ `void OnAlignLeft();`
- L127 _private prototype_ `void OnAlignCenter();`
- L128 _private prototype_ `void OnAlignRight();`
- L129 _private prototype_ `void OnStraightenConnections();`
- L130 _private prototype_ `void OnDistributeNodesH();`
- L131 _private prototype_ `void OnDistributeNodesV();`
- L135 _private member_ `TSharedPtr<SMoviePipelineQueueEditor> PipelineQueueEditorWidget;` — The main movie pipeline queue editor widget
- L138 _private member_ `TSharedPtr<SGraphEditor> GraphEditorWidget;` — The graph widget displayed in this panel.
- L140 _private member_ `TWeakPtr<SWindow> WeakEditorWindow;`
- L142 _private member_ `int32 NumSelectedJobs;`
- L144 _private member_ `FOnGraphSelectionChanged OnGraphSelectionChangedEvent;`
- L145 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGraphSelectionChanged, TArray<UObject*>);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/MoviePipelineQueuePanelUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MovieRenderPipelineEditor` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::MovieRenderPipelineEditor`)
- L19 _prototype_ `UMovieGraphConfig* GenerateNewShotSubgraph(const UMoviePipelineExecutorJob* InJob, UMoviePipelineExecutorShot* InShot);` (scope `UE::MovieRenderPipelineEditor::Private`) — Generates and returns a new shot subgraph based on the given job and shot. Returns nullptr if there was an issue creating the graph. If the graph was successfully created, it will be assigned to the shot.
- L22 _prototype_ `void SaveTransientQueueToAsset(UMoviePipelineQueue* DestinationQueue);` (scope `UE::MovieRenderPipelineEditor::Private`) — Copies the transient queue to the destination queue asset, registers it, and prompts for save.
- L25 _prototype_ `void SaveQueue();` (scope `UE::MovieRenderPipelineEditor::Private`) — Saves the queue. If it has no known origin, falls through to SaveQueueAs().
- L28 _prototype_ `void SaveQueueAs();` (scope `UE::MovieRenderPipelineEditor::Private`) — Prompts the user for a new package name and saves the queue as a new asset.
- L31 _prototype_ `void ImportSavedQueueAsset(const FAssetData& InPresetAsset);` (scope `UE::MovieRenderPipelineEditor::Private`) — Loads a previously saved queue asset via the subsystem. Does NOT dismiss menus -- callers handle that.
- L34 _prototype_ `bool IsQueueDirty();` (scope `UE::MovieRenderPipelineEditor::Private`) — Returns true if the current queue has been modified since the last save.
- L37 _prototype_ `UMoviePipelineQueue* GetQueueOrigin();` (scope `UE::MovieRenderPipelineEditor::Private`) — Returns the origin queue asset for the currently loaded queue, or nullptr.
- L40 _prototype_ `FString GetQueueOriginName();` (scope `UE::MovieRenderPipelineEditor::Private`) — Returns the short package name of the queue origin, or an empty string.
- L43 _prototype_ `bool OpenSaveDialog(const FString& InDefaultPath, const FString& InNewNameSuggestion, FString& OutPackageName);` (scope `UE::MovieRenderPipelineEditor::Private`) — Opens a save-asset dialog for a queue. Returns true if the user selected a valid path.
- L46 _prototype_ `bool GetSavePresetPackageName(const FString& InExistingName, FString& OutName);` (scope `UE::MovieRenderPipelineEditor::Private`) — Determines the package name when saving a queue preset. Returns true on success.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/MoviePipelineWidgetConstants.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace MoviePipeline`
- L10 _variable_ `static FMargin ButtonOffset(FMargin(0.f, 0.f, 4.f, 0.f));` (scope `MoviePipeline`) — Button offset to apply to buttons on movie pipeline panel toolbars
- L13 _variable_ `static FMargin ButtonPadding(4.f);` (scope `MoviePipeline`) — Button padding to apply to buttons inside movie pipeline panel toolbars

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineAfterRenderWidget.h` (Private)


#### class `SMoviePipelineAfterRenderWidget`  
`class SMoviePipelineAfterRenderWidget : public SCompoundWidget`  
_L14-24_
- inherits: `SCompoundWidget`
- desc: Compact toolbar widget that shows the "After Render" behavior dropdown and a settings button to open the post-render preferences.
- L17 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineAfterRenderWidget)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _private member_ `TSharedPtr<ISinglePropertyView> PostRenderBehaviorWidget;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineConfigEditor.h` (Private)


#### class `SMoviePipelineConfigEditor`  
`class SMoviePipelineConfigEditor : public SCompoundWidget`  
_L25-95_
- inherits: `SCompoundWidget`
- desc: Widget used to edit a Movie Render Pipeline Shot Config.
- L29 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineConfigEditor) : _PipelineConfig(nullptr) , _OwningJob(nullptr)`
- L34 _public prototype_ `SLATE_ATTRIBUTE(UMoviePipelineConfigBase*, PipelineConfig) SLATE_ATTRIBUTE(UMoviePipelineExecutorJob*, OwningJob) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L44 _public prototype_ `TSharedRef<SWidget> MakeAddSettingButton();` — Construct a button that can add sources to this widget's preset
- L48 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L55 _private prototype_ `void CheckForNewSettingsObject();` — Check to see whether the configuration we're editing has changed, and propagate that change if necessary
- L60 _private prototype_ `void UpdateDetails();` — Update the details panel for the current selection
- L64 _private prototype_ `TSharedRef<SWidget> OnGenerateSettingsMenu();`
- L66 _private prototype_ `void AddSettingFromClass(TSubclassOf<UMoviePipelineSetting> SettingClass);`
- L67 _private prototype_ `bool CanAddSettingFromClass(TSubclassOf<UMoviePipelineSetting> SettingClass);`
- L69 _private function_ `void OnSettingsSelectionChanged(TSharedPtr<IMoviePipelineSettingTreeItem>, ESelectInfo::Type)`
- L70 _private prototype_ `FText GetSettingsFooterText() const;`
- L71 _private prototype_ `EVisibility IsSettingFooterVisible() const;`
- L73 _private prototype_ `EVisibility IsValidationWarningVisible() const;`
- L74 _private prototype_ `FText GetValidationWarningText() const;`
- L75 _private prototype_ `void OnBlueprintReinstanced();`
- L78 _private member_ `bool bRequestDetailsRefresh;`
- L84 _private member_ `TAttribute<UMoviePipelineConfigBase*> PipelineConfigAttribute;` — Edited Pipeline
- L85 _private member_ `TWeakObjectPtr<UMoviePipelineConfigBase> CachedPipelineConfig;`
- L88 _private member_ `TAttribute<UMoviePipelineExecutorJob*> OwningJobAttribute;` — Owning Job
- L89 _private member_ `TWeakObjectPtr<UMoviePipelineExecutorJob> CachedOwningJob;`
- L92 _private member_ `TSharedPtr<SMoviePipelineConfigSettings> SettingsWidget;`
- L93 _private member_ `TSharedPtr<SScrollBox> DetailsBox;`
- L94 _private member_ `TMap<FObjectKey, TSharedPtr<IDetailsView>> ClassToDetailsView;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineConfigPanel.h` (Private)


#### class `SMoviePipelineConfigPanel`  
`class SMoviePipelineConfigPanel : public SCompoundWidget, public FGCObject`  
_L21-137_
- inherits: `SCompoundWidget,FGCObject`
- desc: Outermost widget that is used for setting up a new movie render pipeline config. Operates on a transient UMovieRenderShotConfig that is internally owned and maintained
- L25 _public prototype_ `~SMoviePipelineConfigPanel();`
- L27 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineConfigPanel) : _BasePreset(nullptr) , _BaseConfig(nullptr) , _AssetToEdit(nullptr)`
- L33 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UMoviePipelineExecutorJob>, Job) SLATE_ARGUMENT(TWeakObjectPtr<UMoviePipelineExecutorShot>, Shot) SLATE_EVENT(FOnMoviePipelineConfigChanged, OnConfigurationModified) SLATE_EVENT(FOnMoviePipelineConfigChanged, OnConfigurationSetToPreset) SLATE_ARGUMENT(UMoviePipelineConfigBase*, BasePreset) SLATE_ARGUMENT(UMoviePipelineConfigBase*, BaseConfig) SLATE_ARGUMENT(UMoviePipelineConfigBase*, AssetToEdit) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSubclassOf<UMoviePipelineConfigBase> InConfigType);`
- L55 _public prototype_ `UMoviePipelineConfigBase* GetPipelineConfig() const;`
- L56 _public prototype_ `UMoviePipelineExecutorJob* GetOwningJob() const;`
- L57 _public prototype_ `UMoviePipelineExecutorShot* GetOwningShot() const;`
- L60 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L61 _private function_ `virtual FString GetReferencerName() const override`
- L67 _private prototype_ `bool GetSavePresetPackageName(const FString& InExistingName, FString& OutName);` — Attempts to work with the user to find a suitable package path to save the asset under.
- L69 _private prototype_ `bool OpenSaveDialog(const FString& InDefaultPath, const FString& InNewNameSuggestion, FString& OutPackageName);`
- L72 _private prototype_ `TSharedRef<SWidget> OnGeneratePresetsMenu();` — Generate the widget that is visible in the Choose Preset dropdown.
- L74 _private prototype_ `FText GetPresetsMenuButtonText() const;`
- L75 _private prototype_ `FText GetConfigTypeLabel() const;`
- L77 _private prototype_ `FReply OnCancelChanges();`
- L78 _private prototype_ `FReply OnConfirmChanges();`
- L79 _private prototype_ `bool CanAcceptChanges() const;`
- L83 _private prototype_ `UMoviePipelineConfigBase* AllocateTransientPreset();` — Allocates a transient preset so that the user can use the pipeline without saving it to an asset first.
- L86 _private prototype_ `void OnAnyObjectModified(UObject* InModifiedObject);` — Called when any object has Modify() called on it. Used to track if user edits transient object after exporting a preset.
- L89 _private prototype_ `void OnImportPreset(const FAssetData& InPresetAsset);` — When a user wants to import an existing preset asset over the current config.
- L92 _private prototype_ `bool CanSavePreset() const;` — Returns true if the user can save the current preset, else false.
- L95 _private prototype_ `void OnSavePreset();` — Saves the current preset to its existing asset, or triggers a "Save As" if a transient preset is being saved.
- L98 _private prototype_ `void OnSaveAsPreset();` — Saves the current preset out to a new or existing asset.
- L101 _private prototype_ `void SaveTransientPresetToAsset(UMoviePipelineConfigBase* DestinationPreset);` — Saves the transient preset to DestinationPreset.
- L103 _private prototype_ `FText GetValidationWarningText() const;`
- L106 _public prototype_ `TSharedRef<SWidget> MakeSettingsWidget();`
- L109 _private prototype_ `bool IsConfigDirty() const;`
- L110 _private prototype_ `UMoviePipelineConfigBase* GetConfigOrigin() const;`
- L111 _private prototype_ `FString GetConfigOriginName() const;`
- L115 _private member_ `TObjectPtr<UMoviePipelineConfigBase> TransientPreset = nullptr;` — The transient preset that we use - kept alive by AddReferencedObjects
- L118 _private member_ `TSoftObjectPtr<UMoviePipelineConfigBase> OriginPreset;` — The preset that is in use, if any. Will be null if the preset was never saved and is only transient.
- L121 _private member_ `bool bHasModifiedLoadedPreset = false;` — Whether the preset (transient or otherwise) has been modified while loaded in this panel.
- L124 _private member_ `TWeakObjectPtr<UMoviePipelineExecutorJob> WeakJob;` — The job this editing panel is for. Kept alive externally.
- L127 _private member_ `TWeakObjectPtr<UMoviePipelineExecutorShot> WeakShot;` — The job this editing panel is for. Kept alive externally.
- L130 _private member_ `TSharedPtr<SMoviePipelineConfigEditor> MoviePipelineEditorWidget;` — The main movie pipeline editor widget
- L133 _private member_ `TSubclassOf<UMoviePipelineConfigBase> ConfigAssetType;` — What type of asset are we editing? Could be a primary config or a per-shot override config.
- L135 _private member_ `FOnMoviePipelineConfigChanged OnConfigurationModified;`
- L136 _private member_ `FOnMoviePipelineConfigChanged OnConfigurationSetToPreset;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnMoviePipelineConfigChanged, TWeakObjectPtr<UMoviePipelineExecutorJob>, TWeakObjectPtr<UMoviePipelineExecutorShot>, UMoviePipelineConfigBase*) class SMoviePipelineConfigPanel : public SCompoundWidget, public FGCObject { public: ~SMoviePipelineConfigPanel(); SLATE_BEGIN_ARGS(SMoviePipelineConfigPanel) : _BasePreset(nullptr) , _BaseConfig(nullptr) , _AssetToEdit(nullptr) {} SLATE_ARGUMENT(TWeakObjectPtr<UMoviePipelineExecutorJob>, Job) SLATE_ARGUMENT(TWeakObjectPtr<UMoviePipelineExecutorShot>, Shot) SLATE_EVENT(FOnMoviePipelineConfigChanged, OnConfigurationModified) SLATE_EVENT(FOnMoviePipelineConfigChanged, OnConfigurationSetToPreset) SLATE_ARGUMENT(UMoviePipelineConfigBase*, BasePreset) SLATE_ARGUMENT(UMoviePipelineConfigBase*, BaseConfig) SLATE_ARGUMENT(UMoviePipelineConfigBase*, AssetToEdit) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSubclassOf<UMoviePipelineConfigBase> InConfigType); UMoviePipelineConfigBase* GetPipelineConfig() const;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineConfigSettings.h` (Private)


#### class `SMoviePipelineConfigSettings`  
`class SMoviePipelineConfigSettings : public SCompoundWidget, public FEditorUndoClient`  
_L29-77_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Main widget for the Movie Render Shot Config panel
- L33 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineConfigSettings)`
- L34 _public prototype_ `SLATE_EVENT(FOnSettingSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L39 _public prototype_ `void SetShotConfigObject(UMoviePipelineConfigBase* InShotConfig);`
- L41 _public prototype_ `void GetSelectedSettings(TArray<UMoviePipelineSetting*>& OutSettings) const;`
- L42 _public prototype_ `void SetSelectedSettings(const TArray<UMoviePipelineSetting*>& Settings);`
- L43 _public function_ `void InvalidateCachedSettingsSerialNumber()`
- L46 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L47 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L48 _private prototype_ `void SetSelectedSettings_Impl(const TArray<UMoviePipelineSetting*>& Settings);`
- L51 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient
- L52 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L57 _private prototype_ `void ReconstructTree();`
- L59 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<IMoviePipelineSettingTreeItem> Item, const TSharedRef<STableViewBase>& Tree);`
- L61 _private prototype_ `void OnGetChildren(TSharedPtr<IMoviePipelineSettingTreeItem> Item, TArray<TSharedPtr<IMoviePipelineSettingTreeItem>>& OutChildItems);`
- L63 _private prototype_ `void OnDeleteSelected();`
- L64 _private prototype_ `bool IsSelectableOrNavigable(TSharedPtr<IMoviePipelineSettingTreeItem> Item) const;`
- L67 _private member_ `TArray<UMoviePipelineSetting*> PendingSettingsToSelect;`
- L69 _private member_ `uint32 CachedSettingsSerialNumber;`
- L70 _private member_ `TWeakObjectPtr<UMoviePipelineConfigBase> WeakShotConfig;`
- L72 _private member_ `TArray<TSharedPtr<IMoviePipelineSettingTreeItem>> RootNodes;`
- L73 _private member_ `TMap<FObjectKey, TSharedPtr<FMoviePipelineSettingTreeItem>> SettingToTreeItem;`
- L74 _private member_ `TSharedPtr<STreeView<TSharedPtr<IMoviePipelineSettingTreeItem>>> TreeView;`
- L76 _private member_ `TSharedPtr<FUICommandList> CommandList;`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnSettingSelectionChanged, TSharedPtr<IMoviePipelineSettingTreeItem>, ESelectInfo::Type ) class SMoviePipelineConfigSettings : public SCompoundWidget, public FEditorUndoClient { public: SLATE_BEGIN_ARGS(SMoviePipelineConfigSettings){} SLATE_EVENT(FOnSettingSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void SetShotConfigObject(UMoviePipelineConfigBase* InShotConfig); void GetSelectedSettings(TArray<UMoviePipelineSetting*>& OutSettings) const; void SetSelectedSettings(const TArray<UMoviePipelineSetting*>& Settings); void InvalidateCachedSettingsSerialNumber() { CachedSettingsSerialNumber = -1; } private: virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override; virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override; void SetSelectedSettings_Impl(const TArray<UMoviePipelineSetting*>& Settings);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineConfigTabContent.h` (Private)


#### class `SMoviePipelineConfigTabContent`  
`class SMoviePipelineConfigTabContent : public SCompoundWidget`  
_L11-28_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineConfigTabContent)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void SetupForPipeline(UMoviePipelineConfigBase* BasePreset);` — Set this tab up for a specific Pipeline preset. Passing nullptr will initialize a default pipeline.
- L24 _private prototype_ `EActiveTimerReturnType OnActiveTimer(double InCurrentTime, float InDeltaTime);`
- L27 _private member_ `TWeakPtr<SMoviePipelineConfigPanel> WeakPanel;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineFormatTokenAutoCompleteBox.h` (Private)


#### class `SMoviePipelineFormatTokenAutoCompleteBox`  
`class SMoviePipelineFormatTokenAutoCompleteBox : public SCompoundWidget`  
_L14-74_
- inherits: `SCompoundWidget`
- desc: This is a specific auto-complete widget made for the MoviePipeline that isn't very flexible. It's similar to SSuggestionTextBox, but SSuggestionTextBox doesn't handle more than one word/suggestions mid string. This widget is hardcoded to look for '{' characters (for {format_tokens}) and then auto completes them from a list and fixes up the {} braces.
- L18 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineFormatTokenAutoCompleteBox)`
- L20 _public prototype_ `SLATE_ARGUMENT(FText, InitialText) SLATE_ARGUMENT(FText, HintText) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, TextHandle) SLATE_ATTRIBUTE(TArray<FString>, Suggestions) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `virtual void OnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;` — SWidget interface
- L30 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;`
- L33 _public prototype_ `void SetText(const FText& InText);`
- L35 _public prototype_ `void OnItemClicked(TSharedPtr<FString>);`
- L37 _public prototype_ `static void FindAutoCompletableTextAtPos(const FString& InWholeString, int32 InCursorPos, FString& OutStr, bool& bShowAutoComplete);`
- L39 _public prototype_ `void ReplaceRelevantTextWithSuggestion(const FString& InSuggestionText);`
- L41 _public prototype_ `void HandleTextBoxTextChanged(const FText& InText);`
- L43 _public prototype_ `void HandleTextBoxTextCommitted(const FText& InText, ETextCommit::Type CommitInfo) const;`
- L45 _public prototype_ `void FilterVisibleSuggestions(const FString& StrToMatch, const bool bForceShowAll);`
- L47 _public prototype_ `void CloseMenuAndReset();`
- L49 _public prototype_ `void SetActiveSuggestionIndex(int32 InIndex);`
- L51 _public prototype_ `TSharedRef<ITableRow> HandleSuggestionListViewGenerateRow(TSharedPtr<FString> Text, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L56 _public prototype_ `static TArray<FString> GetFileNameFormatSuggestions();` — A helper to get file name format suggestions. Can be passed to the "Suggestions" argument.
- L60 _private prototype_ `static void GetBracePositionsForCursor(const FString& InText, int32 CursorPos, int32& OutStartingBracePos, int32& OutEndBracePos);` — Get the relevant brace positions for the given cursor position within the text.
- L63 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> SuggestionListView;`
- L64 _private member_ `TSharedPtr<SMultiLineEditableTextBox> TextBox;`
- L65 _private member_ `TSharedPtr<SMenuAnchor> MenuAnchor;`
- L66 _private member_ `TSharedPtr<SVerticalBox> VerticalBox;`
- L67 _private member_ `TSharedPtr<IPropertyHandle> TextHandle;`
- L70 _private member_ `TArray<FString> AllSuggestions;` — The pool of suggestions to show
- L72 _private member_ `TArray<TSharedPtr<FString>> Suggestions;` — The currently filtered suggestion list
- L73 _private member_ `int32 CurrentSuggestionIndex = -1;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineQueueEditor.h` (Private)


#### class `SMoviePipelineQueueEditor`  
`class SMoviePipelineQueueEditor : public SCompoundWidget, public FEditorUndoClient`  
_L33-110_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Widget used to edit a Movie Pipeline Queue
- L38 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineQueueEditor)`
- L40 _public prototype_ `SLATE_EVENT(FOnMoviePipelineEditConfig, OnEditConfigRequested) SLATE_EVENT(FOnMoviePipelineEditConfig, OnPresetChosen) SLATE_EVENT(FOnMoviePipelineJobSelection, OnJobSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L47 _public prototype_ `TSharedRef<SWidget> MakeAddSequenceJobButton();`
- L48 _public prototype_ `TSharedRef<SWidget> RemoveSelectedJobButton();`
- L49 _public prototype_ `TSharedRef<SWidget> OnGenerateNewJobFromAssetMenu();`
- L51 _public function_ `TArray<TSharedPtr<IMoviePipelineQueueTreeItem>> GetSelectedItems() const`
- L52 _public function_ `void SetSelectedJobs(const TArray<UMoviePipelineExecutorJob*>& InJobs)`
- L55 _public prototype_ `TArray<UMoviePipelineExecutorJob*> GetSelectedJobs() const;` — Returns the currently selected jobs.
- L58 _public prototype_ `static void AssignDefaultGraphPresetToJob(UMoviePipelineExecutorJob* InJob);` — Get the default graph preset from the project settings and assign it to the given job
- L62 _private prototype_ `FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget Interface
- L63 _private prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L67 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient
- L68 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L73 _private prototype_ `void OnCreateJobFromAsset(const FAssetData& InAsset);`
- L75 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<IMoviePipelineQueueTreeItem> Item, const TSharedRef<STableViewBase>& Tree);`
- L77 _private prototype_ `void OnGetChildren(TSharedPtr<IMoviePipelineQueueTreeItem> Item, TArray<TSharedPtr<IMoviePipelineQueueTreeItem>>& OutChildItems);`
- L79 _private prototype_ `FReply OnDragDropTarget(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L81 _private prototype_ `bool CanDragDropTarget(TSharedPtr<FDragDropOperation> InOperation);`
- L83 _private prototype_ `TSharedPtr<SWidget> GetContextMenuContent();`
- L85 _private prototype_ `void OnDeleteSelected();`
- L86 _private prototype_ `bool CanDeleteSelected() const;`
- L87 _private prototype_ `FReply DeleteSelected();`
- L89 _private prototype_ `void OnDuplicateSelected();`
- L90 _private prototype_ `bool CanDuplicateSelected() const;`
- L92 _private prototype_ `void OnResetStatus();`
- L94 _private prototype_ `void ReconstructTree();`
- L95 _private prototype_ `void SetSelectedJobs_Impl(const TArray<UMoviePipelineExecutorJob*>& InJobs);`
- L96 _private prototype_ `void OnJobSelectionChanged_Impl(TSharedPtr<IMoviePipelineQueueTreeItem> TreeItem, ESelectInfo::Type SelectInfo);`
- L99 _private prototype_ `void OnQueueLoaded();` — Called when a new queue is loaded in the queue subsystem.
- L102 _private member_ `TArray<TSharedPtr<IMoviePipelineQueueTreeItem>> RootNodes;`
- L103 _private member_ `TSharedPtr<STreeView<TSharedPtr<IMoviePipelineQueueTreeItem>>> TreeView;`
- L104 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L105 _private member_ `uint32 CachedQueueSerialNumber;`
- L106 _private member_ `TArray<UMoviePipelineExecutorJob*> PendingJobsToSelect;`
- L107 _private member_ `FOnMoviePipelineEditConfig OnEditConfigRequested;`
- L108 _private member_ `FOnMoviePipelineEditConfig OnPresetChosen;`
- L109 _private member_ `FOnMoviePipelineJobSelection OnJobSelectionChanged;`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMoviePipelineEditConfig, TWeakObjectPtr<UMoviePipelineExecutorJob>, TWeakObjectPtr<UMoviePipelineExecutorShot>) DECLARE_DELEGATE_TwoParams(FOnMoviePipelineJobSelection, const TArray<UMoviePipelineExecutorJob*>&, const TArray<UMoviePipelineExecutorShot*>&) class SMoviePipelineQueueEditor : public SCompoundWidget, public FEditorUndoClient { public: SLATE_BEGIN_ARGS(SMoviePipelineQueueEditor) {} SLATE_EVENT(FOnMoviePipelineEditConfig, OnEditConfigRequested) SLATE_EVENT(FOnMoviePipelineEditConfig, OnPresetChosen) SLATE_EVENT(FOnMoviePipelineJobSelection, OnJobSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs); TSharedRef<SWidget> MakeAddSequenceJobButton(); TSharedRef<SWidget> RemoveSelectedJobButton(); TSharedRef<SWidget> OnGenerateNewJobFromAssetMenu(); TArray<TSharedPtr<IMoviePipelineQueueTreeItem>> GetSelectedItems() const { return TreeView->GetSelectedItems(); } void SetSelectedJobs(const TArray<UMoviePipelineExecutorJob*>& InJobs) { PendingJobsToSelect = InJobs; } TArray<UMoviePipelineExecutorJob*> GetSelectedJobs() const; static void AssignDefaultGraphPresetToJob(UMoviePipelineExecutorJob* InJob); private:`
- L28 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMoviePipelineJobSelection, const TArray<UMoviePipelineExecutorJob*>&, const TArray<UMoviePipelineExecutorShot*>&) class SMoviePipelineQueueEditor : public SCompoundWidget, public FEditorUndoClient { public: SLATE_BEGIN_ARGS(SMoviePipelineQueueEditor) {} SLATE_EVENT(FOnMoviePipelineEditConfig, OnEditConfigRequested) SLATE_EVENT(FOnMoviePipelineEditConfig, OnPresetChosen) SLATE_EVENT(FOnMoviePipelineJobSelection, OnJobSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs); TSharedRef<SWidget> MakeAddSequenceJobButton(); TSharedRef<SWidget> RemoveSelectedJobButton(); TSharedRef<SWidget> OnGenerateNewJobFromAssetMenu(); TArray<TSharedPtr<IMoviePipelineQueueTreeItem>> GetSelectedItems() const { return TreeView->GetSelectedItems(); } void SetSelectedJobs(const TArray<UMoviePipelineExecutorJob*>& InJobs) { PendingJobsToSelect = InJobs; } TArray<UMoviePipelineExecutorJob*> GetSelectedJobs() const; static void AssignDefaultGraphPresetToJob(UMoviePipelineExecutorJob* InJob); private:`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineQueuePanel.h` (Private)


#### class `SMoviePipelineQueuePanel`  
`class SMoviePipelineQueuePanel : public SCompoundWidget`  
_L22-123_
- inherits: `SCompoundWidget`
- desc: Provides the UI for managing render jobs: adding/removing sequences, editing graph/basic/legacy configs, saving/loading queue presets, and dispatching local or remote renders.
- L25 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineQueuePanel)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _private prototype_ `void OnRenderLocalRequested();` — Kicks off a local (in-process) render of the queue.
- L33 _private prototype_ `bool IsRenderLocalEnabled() const;`
- L36 _private prototype_ `void OnRenderRemoteRequested();` — Kicks off a remote render of the queue via the configured executor.
- L37 _private prototype_ `bool IsRenderRemoteEnabled() const;`
- L40 _private prototype_ `bool IsRenderEnabled() const;` — Returns true if any render option (local or remote) is currently available.
- L43 _private prototype_ `TSharedRef<SWidget> OnGenerateRenderMenu();` — Builds the render mode dropdown menu (local/remote).
- L46 _private prototype_ `void OnRenderClicked();` — Invokes the effective render mode shown on the primary render button.
- L49 _private prototype_ `void OnRenderModeMenuEntryChosen(bool bIsLocal);` — Records the chosen render mode.
- L52 _private prototype_ `FText GetRenderButtonLabel() const;` — Returns the last-chosen render mode for display on the Render button.
- L55 _private prototype_ `bool ShouldRenderLocal() const;` — Returns whether a render (via the Render button) should perform a local render (vs. a remote render).
- L58 _private prototype_ `void OnEditJobConfigRequested(TWeakObjectPtr<UMoviePipelineExecutorJob> InJob, TWeakObjectPtr<UMoviePipelineExecutorShot> InShot);` — Opens the config editor (graph or legacy) for the given job/shot.
- L61 _private prototype_ `void OnJobPresetChosen(TWeakObjectPtr<UMoviePipelineExecutorJob> InJob, TWeakObjectPtr<UMoviePipelineExecutorShot> InShot);` — Called when an existing preset is chosen for a job or shot.
- L64 _private prototype_ `void OnConfigUpdatedForJob(TWeakObjectPtr<UMoviePipelineExecutorJob> InJob, TWeakObjectPtr<UMoviePipelineExecutorShot> InShot, UMoviePipelineConfigBase* InConfig);` — Applies a modified config back to the owning job/shot.
- L67 _private prototype_ `void OnConfigUpdatedForJobToPreset(TWeakObjectPtr<UMoviePipelineExecutorJob> InJob, TWeakObjectPtr<UMoviePipelineExecutorShot> InShot, UMoviePipelineConfigBase* InConfig);` — Applies a preset-based config back to the owning job/shot.
- L70 _private prototype_ `void OnConfigWindowClosed();` — Destroys the currently open config editor window.
- L73 _private prototype_ `void OnSelectionChanged(const TArray<UMoviePipelineExecutorJob*>& InSelectedJobs, const TArray<UMoviePipelineExecutorShot*>& InSelectedShots);` — Responds to job/shot selection changes in the queue editor.
- L76 _private prototype_ `int32 GetDetailsViewWidgetIndex() const;` — Returns the widget-switcher index: 0 for details view, 1 for "no selection" placeholder.
- L77 _private prototype_ `bool IsDetailsViewEnabled() const;`
- L80 _private prototype_ `TSharedRef<SWidget> OnGenerateSavedQueuesMenu();` — Builds the save/load queue dropdown menu.
- L81 _private prototype_ `FText GetQueueMenuButtonText() const;`
- L84 _private prototype_ `void OnSaveButtonClicked();` — Saves the queue (Save As if unsaved, Save if already saved).
- L87 _private prototype_ `void OnFindInContentBrowserClicked();` — Selects the selected job's level sequence in the Content Browser.
- L90 _private prototype_ `bool IsFindInContentBrowserEnabled() const;` — Returns true when a job with a valid sequence is selected.
- L93 _private prototype_ `TSharedRef<SWidget> MakeToolbar();` — Builds the main toolbar using FToolBarBuilder.
- L96 _private prototype_ `void OnDetailsSplitterFinishedResizing();` — Persists the details splitter slot value to GEditorPerProjectIni when the user finishes dragging.
- L99 _private prototype_ `void OnSaveAsset();` — Thin wrappers that delegate to utils and handle Slate-specific concerns (e.g. menu dismissal).
- L100 _private prototype_ `void OnSaveAsAsset();`
- L101 _private prototype_ `void OnImportSavedQueueAsset(const FAssetData& InPresetAsset) const;`
- L102 _private prototype_ `bool IsQueueDirty() const;`
- L103 _private prototype_ `FString GetQueueOriginName() const;`
- L107 _private member_ `TSharedPtr<SMoviePipelineQueueEditor> PipelineQueueEditorWidget;` — The main queue editor list widget.
- L110 _private member_ `TSharedPtr<IDetailsView> JobDetailsPanelWidget;` — Details panel showing properties for the selected job(s) or shot(s).
- L113 _private member_ `TWeakPtr<SWindow> WeakEditorWindow;` — The config-editor child window, if one is currently open.
- L116 _private member_ `int32 NumSelectedJobs = 0;` — Cached count of selected jobs, used to drive the details-view widget switcher.
- L119 _private member_ `TSharedPtr<class SSplitter> QueueDetailsSplitter;` — Splitter that divides the queue tree (left) and the job details panel (right).
- L122 _private member_ `float DetailsSplitterValue = 0.4f;` — Fraction (0..1) of horizontal space allocated to the details panel. Usually sourced from GEditorPerProjectIni.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/Widgets/SMoviePipelineQueueTabContent.h` (Private)


#### class `SMoviePipelineQueueTabContent`  
`class SMoviePipelineQueueTabContent : public SCompoundWidget`  
_L10-21_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SMoviePipelineQueueTabContent)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _private member_ `TWeakPtr<SMoviePipelineQueuePanel> WeakPanel;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/Graph/MovieGraphConfigFactory.h` (Public)


#### class `UMovieGraphConfigFactory`  
`class UMovieGraphConfigFactory : public UFactory`  
_L13-37_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UFactory`
- L17 _public prototype_ `UMovieGraphConfigFactory();`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L28 _private prototype_ `void AddSubgraphNodeToGraph(UMovieGraphConfig* InTargetGraph) const;` — If the factory was created with an InitialSubgraphAsset, adds a subgraph node pointing to InitialSubgraphAsset to the target graph, and connects it up to the Inputs and Outputs nodes.
- L36 _public member_ `TObjectPtr<UMovieGraphConfig> InitialSubgraphAsset = nullptr;` — `UPROPERTY(Transient)` — If set, creates an empty graph with one subgraph node (where the subgraph points to this graph). If not set, the factory will create a graph from the template like normal.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/Graph/MovieGraphQuickRender.h` (Public)


#### class `UMovieGraphQuickRenderSubsystem`  
`class UMovieGraphQuickRenderSubsystem : public UEditorSubsystem`  
_L25-238_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Provides the ability to perform a "Quick Render". A Quick Render is a render which requires no conventional Movie Render Queue setup, like creating a queue, adding a job(s) to it, specifying the level sequence to use, providing a custom configuration or graph, etc. Quick Renders are designed to get you a render as fast as possible while providing minimal configuration input, for use in things like approving animation.
- L32 _public prototype_ `void BeginQuickRender(const EMovieGraphQuickRenderMode InQuickRenderMode, const UMovieGraphQuickRenderModeSettings* InQuickRenderSettings);` — `UFUNCTION(BlueprintCallable, Category="Quick Render")` — Begins a quick render using the provided mode and settings.
- L39 _public prototype_ `void PlayLastRender();` — `UFUNCTION(BlueprintCallable, Category="Quick Render")` — Plays the last render that Quick Render generated, using the settings specified in Editor Preferences. If no render has been generated in this editor session yet, this does nothing.
- L43 _public prototype_ `bool CanPlayLastRender();` — `UFUNCTION(BlueprintCallable, Category="Quick Render")` — Determines if the last render can be played (ie, whether a render has been performed in the current editor session or not).
- L50 _public prototype_ `void OpenOutputDirectory(const UMovieGraphQuickRenderModeSettings* InQuickRenderSettings);` — `UFUNCTION(BlueprintCallable, Category="Quick Render")` — Opens the output directory that Quick Render will save media into. This is sourced from the graph that is used for rendering, which is why settings need to be provided.
- L104 _private prototype_ `UMovieGraphConfig* GetQuickRenderGraph(UMovieGraphConfig* InUserSpecifiedGraph, TMap<TObjectPtr<UMovieGraphConfig>, TObjectPtr<UMovieGraphConfig>>& OutOriginalToDupeMap);` — Gets the graph that should be used for the quick render. This will be a duplicate of either the user-specified graph or the default quick render graph. OutOriginalToDupeMap will provide a mapping of the pre-duplicate -> duplicate graphs (may contain multiple graphs if subgraphs are involved).
- L107 _private prototype_ `bool GenerateAndPopulateQueue(TObjectPtr<UMoviePipelineQueue>& OutQueue, TObjectPtr<UMoviePipelineExecutorJob>& OutJob, TObjectPtr<const UMovieGraphQuickRenderModeSettings> InQuickRenderSettings);` — Generates a new queue for use with Quick Render. Adds a job to the queue, specifies the graph, and all other setup required to get the queue operational.
- L110 _private prototype_ `void PerformPostRenderCleanup();` — Performs the required post-render clean-up, mostly clearing out temporary data members.
- L113 _private prototype_ `void ApplyQuickRenderUpdatesToDuplicateGraph(const UWorld* InEditorWorld);` — Applies all necessary updates to the duplicated graph to prepare it for a quick render (adjusting start/end frames, etc).
- L116 _private prototype_ `void ApplyQuickRenderUpdatesToDuplicateGraph_ApplyEditorVisibility(const UWorld* InEditorWorld);` — Helper for ApplyQuickRenderUpdatesToDuplicateGraph() that applies actor editor visibility (by injecting a visibility modifier into the graph).
- L119 _private prototype_ `void ApplyQuickRenderUpdatesToDuplicateGraph_ApplyEditorOnlyActorVisibility(const UWorld* InEditorWorld);` — Helper for ApplyQuickRenderUpdatesToDuplicateGraph() that applies editor-only actor visibility (by injecting a visibility modifier into the graph).
- L122 _private prototype_ `void ApplyQuickRenderUpdatesToDuplicateGraph_ApplyOcio(const FOpenColorIODisplayConfiguration* InOcioConfiguration);` — Helper for ApplyQuickRenderUpdatesToDuplicateGraph() that applies viewport OCIO (by injecting overrides to file output and renderer nodes into the graph).
- L125 _private prototype_ `void ApplyQuickRenderUpdatesToDuplicateGraph_Scalability();` — Helper for ApplyQuickRenderUpdatesToDuplicateGraph() that applies viewport scalability if the graph didn't specify an explicit scalability setting.
- L133 _private prototype_ `template <typename QueryType> QueryType* AddNewCollectionWithVisibilityModifier(const FString& InOperationName, const bool bModifierShouldHide, const bool bProcessEditorOnlyActors = false);` — Adds a new collection + visibility modifier to the graph used for Quick Render. The operation name should be unique. The modifier can be specified to either hide or show the actors in the collection, and can optionally process editor-only actors. Returns the collection query, which can then be updated to include the actors that should be affected.
- L136 _private prototype_ `UMovieGraphNode* InjectNodeIntoBranch(const TSubclassOf<UMovieGraphNode> NodeType, const FName& InBranchName) const;` — Injects a new node in the furthest-downstream position within the specified branch in the duplicated graph.
- L139 _private prototype_ `bool AreModePrerequisitesMet() const;` — Determines if the prerequisites for the given mode are met.
- L142 _private prototype_ `void CachePrePieData(UWorld* InEditorWorld);` — Caches any necessary data before PIE starts. Stored in the CachedPrePieData member variable.
- L145 _private prototype_ `void RestorePreRenderState();` — Handles restoring data after PIE ends.
- L151 _private prototype_ `ULevelSequence* SetUpRenderingLevelSequence() const;` — Returns the current level sequence active in Sequencer, or sets up a new level sequence for rendering (depending on the mode that Quick Render is using).
- L157 _private prototype_ `ULevelSequence* SetUpUtilityLevelSequence() const;` — Returns a new level sequence used for utility purposes (like overriding the camera in use, or changing level visibility). It will be injected into the rendering level sequence as a subsequence.
- L163 _private prototype_ `bool SetUpAllLevelSequences();` — Populates both the rendering and utility level sequences, and assigns them to the relevant members. Returns true if everything could be set up, otherwise false.
- L166 _private prototype_ `UWorld* GetWorldOfType(const EWorldType::Type WorldType) const;` — Gets the first world found of the specified type.
- L172 _private prototype_ `TRange<FFrameNumber> GetPlaybackRange();` — Gets the explicitly-set playback range of the level sequence being rendered (set either by a selection in Sequencer, or custom start/end frames). If using the unaltered playback range of the level sequence, this will return an empty range.
- L178 _private prototype_ `FFrameNumber ConvertSubSequenceFrameToRootFrame(const int32 FrameNum) const;` — Converts a frame number in the focused level sequence to the equivalent in the root level sequence. If the focused and root level sequences are the same, this just returns the provided frame number. The "focused" level sequence might be a subsequence, for example.
- L181 _private prototype_ `void PerformPreRenderSetup(UWorld* InEditorWorld);` — Does any setup needed in the PIE world prior to the render starting.
- L184 _private prototype_ `bool IsViewportLookFlagActive(const EMovieGraphQuickRenderViewportLookFlags ViewportLookFlag) const;` — Determines if the given viewport look flag is currently active.
- L189 _private member_ `TObjectPtr<UMoviePipelineQueue> TemporaryQueue = nullptr;` — `UPROPERTY(Transient)` — The temporary queue that is used by quick render.
- L193 _private member_ `TObjectPtr<UMoviePipelinePIEExecutor> TemporaryExecutor = nullptr;` — `UPROPERTY(Transient)` — The temporary executor that drives the quick render.
- L197 _private member_ `TObjectPtr<UMovieGraphConfig> TemporaryGraph = nullptr;` — `UPROPERTY(Transient)` — The temporary graph that is used by quick render. Usually a duplicate of a graph created outside of quick render, but will be modified by quick render.
- L201 _private member_ `TObjectPtr<UMovieGraphEvaluatedConfig> TemporaryEvaluatedGraph = nullptr;` — `UPROPERTY(Transient)` — The temporary evaluated graph that is generated before a render starts; some setup processes need to inspect it.
- L205 _private member_ `TMap<TObjectPtr<UMovieGraphConfig>, TObjectPtr<UMovieGraphConfig>> OriginalGraphToDupeMap;` — `UPROPERTY(Transient)` — Maps a graph to its duplicate (which is done during render setup). Includes subgraphs.
- L212 _private member_ `TObjectPtr<ULevelSequence> RenderingLevelSequence = nullptr;` — `UPROPERTY(Transient)` — The level sequence that is used for rendering (ie, provided directly to MRG to render from). Sometimes this will be the current level sequence in Sequencer, and other times it may be a temporary level sequence solely for use in Quick Render. It depends on the mode that is being used.
- L219 _private member_ `TObjectPtr<ULevelSequence> UtilityLevelSequence = nullptr;` — `UPROPERTY(Transient)` — The level sequence that is being used by Quick Render for utility purposes. This is not directly rendered from, but may be included in another level sequence to manipulate it (for example). For most modes, this will remain unused.
- L227 _private member_ `EMovieGraphQuickRenderMode QuickRenderMode = EMovieGraphQuickRenderMode::CurrentViewport;` — `UPROPERTY(Transient)` — The mode that Quick Render is actively using in a render. This may be different from the mode that's set in the INI file, which indicates the mode that the UI is using (which could differ if Quick Render is triggered with scripting, for example). See QuickRenderModeSettings for mode configuration settings.
- L234 _private member_ `TObjectPtr<const UMovieGraphQuickRenderModeSettings> QuickRenderModeSettings = nullptr;` — `UPROPERTY(Transient)` — The mode settings Quick Render was initialized with. These are cached here to grab a reference to them before the render begins so the executor callbacks still have access to them later.
- L237 _private member_ `FCachedPrePieData CachedPrePieData;` — Any data that needed to be cached prior to starting PIE.

#### struct `UMovieGraphQuickRenderSubsystem::FCachedPrePieData`  
`struct FCachedPrePieData`  
_L54-98_
- desc: Data that was cached prior to PIE starting.
- L60 _public member_ `TArray<TWeakObjectPtr<class ALevelSequenceActor>> ModifiedLevelSequenceActors;` — Level sequence actors which had their AutoPlay setting turned ON prior to PIE (this setting needs to be turned OFF during PIE). This setting will be restored to ON after PIE ends.
- L63 _public member_ `TArray<TWeakObjectPtr<ACameraActor>> SelectedCameras;` — The cameras that were selected. When PIE starts, the Outliner selection is cleared out, so it needs to be cached prior to PIE.
- L66 _public member_ `TArray<TWeakObjectPtr<AActor>> TemporarilyNonTransientActors;` — Actors that have been temporarily flagged as RF_NonPIEDuplicateTransient. This enables them to be copied to the PIE world when they typically would not.
- L69 _public member_ `TArray<TWeakObjectPtr<UActorComponent>> TemporarilyNonTransientComponents;` — Components that have been temporarily flagged as RF_NonPIEDuplicateTransient. This enables them to be copied to the PIE world when they typically would not.
- L72 _public member_ `TStrongObjectPtr<AActor> ViewportActorLock = nullptr;` — The actor that the viewport is locked to (also referred to as the pilot camera). Nullptr if no actor lock is active.
- L75 _public member_ `FTransform ViewportActorLockWorldTransform = FTransform::Identity;` — Cached world transform of the viewport actor lock (pilot camera).
- L78 _public member_ `bool bUseViewportActorLockWorldTransform = false;` — Whether the viewport actor lock world transform should actually be used.
- L84 _public member_ `TStrongObjectPtr<UCameraComponent> ViewportActorLockCameraComponent = nullptr;` — If the viewport is locked to an actor (see ViewportActorLock), this is the specific camera component that it is locked to. May be nullptr if the viewport is locked to a non-camera actor (like a light).
- L97 _public member_ `} ViewportCamera;`

#### struct `UMovieGraphQuickRenderSubsystem::FCachedPrePieData::FViewportCameraData`  
`struct FViewportCameraData`  
_L88-97_
- desc: Cached viewport camera properties for the non-piloted camera path. These are captured at BeginQuickRender time so the viewport does not need to be active/visible when the PIE world is set up later.
- L90 _public member_ `FVector Location = FVector::ZeroVector;`
- L91 _public member_ `FRotator Rotation = FRotator::ZeroRotator;`
- L92 _public member_ `float FOV = 90.f;`
- L93 _public member_ `float AspectRatio = 1.78f;`
- L94 _public member_ `float OrthoWidth = 0.f;`
- L95 _public member_ `bool bIsPerspective = true;`
- L96 _public member_ `bool bIsValid = false;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/IMovieRenderPipelineEditorModule.h` (Public)


#### class `IMovieRenderPipelineEditorModule`  
`class IMovieRenderPipelineEditorModule : public IModuleInterface`  
_L11-25_
- inherits: `IModuleInterface`
- desc: Public module interface for the Movie Render Pipeline module
- L15 _public member_ `static FName MoviePipelineQueueTabName;` — The tab name for the movie render queue editor tab
- L18 _public member_ `static FText MoviePipelineQueueTabLabel;` — The default label for the movie render queue editor tab.
- L21 _public member_ `static FName MoviePipelineConfigEditorTabName;` — The tab name for the movie render config editor tab
- L24 _public member_ `static FText MoviePipelineConfigEditorTabLabel;` — The default label for the movie render config editor tab.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/MoviePipelineConfigFactory.h` (Public)


#### class `UMoviePipelinePrimaryConfigFactory`  
`class UMoviePipelinePrimaryConfigFactory : public UFactory`  
_L12-21_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UFactory`
- desc: Forward Declare
- L16 _public prototype_ `UMoviePipelinePrimaryConfigFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L19 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

#### class `UMoviePipelineShotConfigFactory`  
`class UMoviePipelineShotConfigFactory : public UFactory`  
_L25-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UFactory`
- desc: Forward Declare
- L29 _public prototype_ `UMoviePipelineShotConfigFactory();`
- L31 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L32 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/MoviePipelineEditorBlueprintLibrary.h` (Public)


#### class `UMoviePipelineEditorBlueprintLibrary`  
`class UMoviePipelineEditorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L23-98_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="MoviePipelineEditorLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L29 _public prototype_ `static bool ExportConfigToAsset(const UMoviePipelinePrimaryConfig* InConfig, const FString& InPackagePath, const FString& InFileName, const bool bInSaveAsset, UMoviePipelinePrimaryConfig*& OutAsset, FText& OutErrorReason);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L33 _public prototype_ `static bool IsMapValidForRemoteRender(const TArray<UMoviePipelineExecutorJob*>& InJobs);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Checks to see if any of the Jobs try to point to maps that wouldn't be valid on a remote render (ie: unsaved maps)
- L37 _public prototype_ `static void WarnUserOfUnsavedMap();` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Pop a dialog box that specifies that they cannot render due to never saved map. Only shows OK button.
- L41 _public prototype_ `static UMoviePipelineQueue* SaveQueueToManifestFile(UMoviePipelineQueue* InPipelineQueue, FString& OutManifestFilePath);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Take the specified Queue, duplicate it and write it to disk in the ../Saved/MovieRenderPipeline/ folder. Returns the duplicated queue.
- L45 _public prototype_ `static FString ConvertManifestFileToString(const FString& InManifestFilePath);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Loads the specified manifest file and converts it into an FString to be embedded with HTTP REST requests. Use in combination with SaveQueueToManifestFile.
- L49 _public prototype_ `static UMoviePipelineExecutorJob* CreateJobFromSequence(UMoviePipelineQueue* InPipelineQueue, const ULevelSequence* InSequence);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Create a job from a level sequence. Sets the map as the currently editor world, the author, the sequence and the job name as the sequence name on the new job. Returns the newly created job.
- L53 _public prototype_ `static void ApplyDefaultConfigurationTypeToJob(UMoviePipelineExecutorJob* InJob);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Applies the user's default configuration type to the given job.
- L57 _public prototype_ `static void AssignDefaultGraphPresetToJob(UMoviePipelineExecutorJob* InJob, const bool bCreateTransaction = true);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline", meta = (AdvancedDisplay="bCreateTransaction"))` — Assigns the project's default graph configuration to the given job, and switches it to graph configuration mode.
- L66 _public prototype_ `static void EnsureJobHasDefaultSettings(UMoviePipelineExecutorJob* InJob, bool bForce = false);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Ensure the job has the settings specified by the project settings added. Idempotent per-job: once defaults have been applied, subsequent calls are no-ops so that settings the user has deliberately removed won't be resurrected. Pass bForce=true to re-apply after an explicit configuration reset (e.g. SetConfiguration to a fresh empty config).
- L70 _public prototype_ `static bool GetDisplayOutputPathFromJob(UMoviePipelineExecutorJob* InJob, FString& OutOutputPath);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Returns display string for output directory for this job. Does not resolve the full path from tokens.
- L78 _public prototype_ `static FString ResolveOutputDirectoryFromJob(UMoviePipelineExecutorJob* InJob);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Resolves as much of the output directory for this job into a usable directory path as possible. Cannot resolve anything that relies on shot name, frame numbers, etc. Returns an empty string upon failure. @see TryResolveOutputDirectoryFromJob() for the same function which also provides the failure reason
- L85 _public prototype_ `static FString TryResolveOutputDirectoryFromJob(UMoviePipelineExecutorJob* InJob, FText& OutError);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — The same as ResolveOutputDirectoryFromJob: returns the resolved output directory, but reports an error string via OutError if resolution failed (e.g. graph traversal could not be completed). Returns an empty string on failure.
- L97 _public prototype_ `static bool SaveBasicConfigAsGraphConfig(UMoviePipelineExecutorJob* InJob);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Generates a UMovieGraphConfig from the job's Basic config. Prompts the user to choose a save location via a Save Asset dialog, saves the asset to disk, then switches the job to Graph configuration mode using the newly saved asset. @param InJob  The job to convert. Must be using Basic configuration mode. @return true if the graph was saved and the job was switched; false if the job is not in Basic mode, graph generation or asset creation failed, the user canceled, or the save failed.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/MoviePipelineNewProcessExecutor.h` (Public)


#### class `UMoviePipelineNewProcessExecutor`  
`class UMoviePipelineNewProcessExecutor : public UMoviePipelineExecutorBase`  
_L17-37_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineExecutorBase`
- desc: This is the implementation responsible for executing the rendering of multiple movie pipelines on the local machine in an external process. This simply handles launching and managing the external processes and acts as a proxy to them where possible. This internally uses the UMoviePipelineInProcessExecutor on the launched instances.
- L22 _private prototype_ `virtual void Execute_Implementation(UMoviePipelineQueue* InPipelineQueue) override;` — UMoviePipelineExecutorBase Interface
- L23 _private function_ `virtual bool IsRendering_Implementation() const override`
- L26 _private function_ `virtual void CancelCurrentJob_Implementation() override` — Canceling current job is equivalent to canceling all jobs for this executor
- L27 _private prototype_ `virtual void CancelAllJobs_Implementation() override;`
- L31 _protected prototype_ `void CheckForProcessFinished();`
- L35 _protected member_ `FProcHandle ProcessHandle;` — A handle to the currently running process (if any) for the active job.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/MoviePipelinePIEExecutor.h` (Public)


#### class `UMoviePipelinePIEExecutor`  
`class UMoviePipelinePIEExecutor : public UMoviePipelineLinearExecutorBase`  
_L29-194_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMoviePipelineLinearExecutorBase`
- desc: This is the implementation responsible for executing the rendering of multiple movie pipelines in the currently running Editor process. This involves launching a Play in Editor session for each Movie Pipeline to process.
- L34 _public prototype_ `UMoviePipelinePIEExecutor();`
- L39 _public function_ `FOnMoviePipelineIndividualJobFinishedNative& OnIndividualJobFinished()` — `UE_DEPRECATED(4.27, "Use OnIndividualJobWorkFinished() instead.")` — Deprecated. Use OnIndividualJobWorkFinished instead.
- L45 _public function_ `FMoviePipelineWorkFinishedNative& OnIndividualJobWorkFinished()` — Native C++ event to listen to for when an individual job has been finished.
- L51 _public function_ `FMoviePipelineWorkFinishedNative& OnIndividualShotWorkFinished()` — Native C++ event to listen to for when an individual shot has been finished. Only called if the UMoviePipeline is set up correctly, see its headers for details. This usually means setting bFlushDiskWritesPerShot to true in the UMoviePipelineOutputSetting for each job before rendering.
- L57 _public function_ `FOnMoviePipelineIndividualJobStartedNative& OnIndividualJobStarted()` — Called right before the specified job is started. This is your last chance to modify the Job Properties before things are initialized from it.
- L63 _public function_ `void SetInitializationTime(const FDateTime& InInitializationTime)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")`
- L67 _public function_ `void SetIsRenderingOffscreen(const bool bInRenderOffscreen)` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Should it render without any UI elements showing up (such as the rendering progress window)?
- L71 _public function_ `bool IsRenderingOffscreen() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Will it render without any UI elements showing up (such as the rendering progress window)?
- L78 _public prototype_ `void SetAllowUsingUnsavedLevels(const bool bShouldAllow);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline")` — Set whether the executor should be allowed to use unsaved levels when rendering (by default, this is not permitted). There are some very specific circumstances where this may be OK. Do not set this unless you're certain it will not cause issues in your use case.
- L82 _protected prototype_ `virtual void Start(const UMoviePipelineExecutorJob* InJob) override;`
- L83 _protected prototype_ `virtual void BeginDestroy() override;`
- L84 _protected prototype_ `virtual void OnExecutorFinishedImpl() override;`
- L88 _protected prototype_ `virtual bool GetSupportsPostRenderActions_Implementation() override;`
- L95 _protected prototype_ `void OnIndividualJobFinishedImpl(FMoviePipelineOutputData InOutputData);` — This should be called after PIE has been shut down for an individual job and it is generally safer to make modifications to the editor world.
- L99 _protected prototype_ `void OnIndividualJobStartedImpl(UMoviePipelineExecutorJob* InJob);` — This is called after PIE starts up but before UMoviePIpeline::Initialize() is called.
- L102 _private prototype_ `void OnPIEStartupFinished(bool);` — Called when PIE finishes booting up and it is safe for us to spawn an object into that world.
- L105 _private prototype_ `void OnTick();` — If they're using delayed initialization, this is called each frame to process the countdown until start, also updates Window Title each frame.
- L108 _private prototype_ `void OnPIEEnded(bool);` — Called before PIE tears down the world during shutdown. Used to detect cancel-via-escape/stop PIE.
- L110 _private prototype_ `void OnPIEMoviePipelineFinished(FMoviePipelineOutputData InOutputData);` — Called when the instance of the pipeline in the PIE world has finished.
- L111 _private prototype_ `void OnJobShotFinished(FMoviePipelineOutputData InOutputData);`
- L114 _private prototype_ `void DelayedFinishNotification();` — Called a short period of time after OnPIEMoviePipelineFinished to allow Editor the time to fully close PIE before we make a new request.
- L116 _private member_ `bool bRenderOffscreen;`
- L118 _private member_ `int32 RemainingInitializationFrames;` — If using delayed initialization, how many frames are left before we call Initialize. Will be -1 if not actively counting down.
- L119 _private member_ `bool bPreviousUseFixedTimeStep;`
- L120 _private member_ `double PreviousFixedTimeStepDelta;`
- L121 _private member_ `TWeakPtr<class SWindow> WeakCustomWindow;`
- L122 _private member_ `TOptional<FDateTime> CustomInitializationTime;`
- L123 _private member_ `FMoviePipelineOutputData CachedOutputDataParams;`
- L126 _private member_ `bool bAllowUnsavedLevels;` — Whether unsaved levels can be rendered from.
- L129 _private member_ `TArray<FMoviePipelineOutputData> AllJobOutputData;` — Output data generated from all jobs in the queue (one entry in the array for each job). May be a mix of graph and preset output data.
- L132 _private member_ `TArray<FString> ResolvedOutputDirectories;` — The resolved output directories for all jobs that have been rendered.
- L137 _private member_ `FOnMoviePipelineIndividualJobFinished OnIndividualJobFinishedDelegate;` — `UE_DEPRECATED(4.27, "Use OnIndividualJobWorkFinishedDelegate instead.")` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — Deprecated. use OnIndividualJobWorkFinishedDelegate instead.
- L139 _private member_ `FOnMoviePipelineIndividualJobFinishedNative OnIndividualJobFinishedDelegateNative;`
- L144 _private member_ `FMoviePipelineWorkFinished OnIndividualJobWorkFinishedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — Called after each job is finished in the queue. Params struct contains an output of all files written.
- L151 _private member_ `FMoviePipelineWorkFinished OnIndividualShotWorkFinishedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — Called after each shot is finished for a particular render. Params struct contains an output of files written for this shot. Only called if the UMoviePipeline is set up correctly, requires a flag in the output setting to be set.
- L157 _private member_ `FOnMoviePipelineIndividualJobStarted OnIndividualJobStartedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Movie Render Pipeline")` — Called right before this job is used to initialize a UMoviePipeline.
- L159 _private member_ `FMoviePipelineWorkFinishedNative OnIndividualJobWorkFinishedDelegateNative;`
- L160 _private member_ `FMoviePipelineWorkFinishedNative OnIndividualShotWorkFinishedDelegateNative;`
- L161 _private member_ `FOnMoviePipelineIndividualJobStartedNative OnIndividualJobStartedDelegateNative;`
- L193 _private member_ `FValidationMessageGatherer ValidationMessageGatherer;`

#### class `UMoviePipelinePIEExecutor::FValidationMessageGatherer`  
`class FValidationMessageGatherer : public FOutputDevice`  
_L163-191_
- inherits: `FOutputDevice`
- L167 _public prototype_ `FValidationMessageGatherer();`
- L169 _public function_ `void StartGathering()`
- L176 _public function_ `void StopGathering()`
- L181 _public prototype_ `virtual void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category) override;`
- L183 _public function_ `void OpenLog()`
- L189 _private member_ `TUniquePtr<FMessageLog> ExecutorLog;`
- L190 _private member_ `const static TArray<FString> AllowList;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineIndividualJobFinishedNative, UMoviePipelineExecutorJob* , bool );` — These are deprecated, see OnIndividualShotWorkFinishedDelegate which contains both the job and the data actually rendered.
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineIndividualJobFinishedNative, UMoviePipelineExecutorJob* , bool );` — These are deprecated, see OnIndividualShotWorkFinishedDelegate which contains both the job and the data actually rendered.
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineIndividualJobFinished, UMoviePipelineExecutorJob*, FinishedJob, bool, bSuccess);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoviePipelineIndividualJobFinished, UMoviePipelineExecutorJob*, FinishedJob, bool, bSuccess);`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoviePipelineIndividualJobStartedNative, UMoviePipelineExecutorJob* );` — These are called right before UMoviePipeline::Initialize(). They only contain the job because no work has been done yet.
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoviePipelineIndividualJobStartedNative, UMoviePipelineExecutorJob* );` — These are called right before UMoviePipeline::Initialize(). They only contain the job because no work has been done yet.
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoviePipelineIndividualJobStarted, UMoviePipelineExecutorJob*, StartedJob);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoviePipelineIndividualJobStarted, UMoviePipelineExecutorJob*, StartedJob);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/MoviePipelineQueueSubsystem.h` (Public)


#### class `UMoviePipelineQueueSubsystem`  
`class UMoviePipelineQueueSubsystem : public UEditorSubsystem`  
_L14-113_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UEditorSubsystem`
- L20 _public function_ `UMoviePipelineQueueSubsystem()`
- L27 _public function_ `UMoviePipelineQueue* GetQueue() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns the queue of Movie Pipelines that need to be rendered.
- L41 _public prototype_ `bool LoadQueue(UMoviePipelineQueue* QueueToLoad, const bool bPromptOnReplacingDirtyQueue = true);` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Loads a new queue by copying it into the queue subsystem's current transient queue (the one returned by GetQueue()). If bPromptOnReplacingDirtyQueue is true and the current queue has been modified since being loaded, a dialog will prompt the user if they want to discard their changes. If this dialog is rejected, or there was an error loading the queue, returns false, else returns true. Note that bPromptOnReplacingDirtyQueue is effectively ignored if the application is in "unattended" mode because the dialog is auto-accepted.
- L48 _public prototype_ `bool IsQueueDirty() const;` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns true if the current queue has been modified since it was loaded, else returns false. Note that the empty queue that is in use upon the initial load of MRQ is not considered dirty.
- L52 _public function_ `UMoviePipelineExecutorBase* GetActiveExecutor() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline")` — Returns the active executor (if there is one). This can be used to subscribe to events on an already in-progress render. May be null.
- L67 _public prototype_ `UMoviePipelineExecutorBase* RenderQueueWithExecutor(TSubclassOf<UMoviePipelineExecutorBase> InExecutorType);` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InExecutorType"), Category = "Movie Render Pipeline|Rendering")` — Starts processing the current queue with the supplied executor class. This starts an async process which may or may not run in a separate process (or on separate machines), determined by the executor implementation. The executor should report progress for jobs depending on the implementation. @param InExecutorType	A subclass of UMoviePipelineExecutorBase. An instance of this class is created and started. @return A pointer to the instance of the class created. This instance will be kept alive by the Queue Subsystem until it has finished (or been canceled). Register for progress reports and various callbacks on this instance.
- L71 _public prototype_ `UMoviePipelineExecutorBase* RenderQueueInstanceWithExecutor(UMoviePipelineQueue* InQueue, TSubclassOf<UMoviePipelineExecutorBase> InExecutorType);` — `UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InExecutorType"), Category = "Movie Render Pipeline|Rendering")` — Like RenderQueueWithExecutor(), but a specific queue instance is used rather than the current queue.
- L81 _public prototype_ `void RenderQueueWithExecutorInstance(UMoviePipelineExecutorBase* InExecutor);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Rendering")` — Starts processing the current queue with the supplied executor. This starts an async process which may or may not run in a separate process (or on separate machines), determined by the executor implementation. The executor should report progress for jobs depending on the implementation. @param InExecutor	Instance of a subclass of UMoviePipelineExecutorBase.
- L85 _public prototype_ `void RenderQueueInstanceWithExecutorInstance(UMoviePipelineQueue* InQueue, UMoviePipelineExecutorBase* InExecutor);` — `UFUNCTION(BlueprintCallable, Category = "Movie Render Pipeline|Rendering")` — Like RenderQueueWithExecutorInstance(), but a specific queue instance is used rather than the current queue.
- L93 _public function_ `bool IsRendering() const` — `UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline|Rendering")` — Returns true if there is an active executor working on producing a movie. This could be actively rendering frames, or working on post processing (finalizing file writes, etc.). Use GetActiveExecutor() and query it directly for more information, progress updates, etc.
- L100 _public member_ `FOnMoviePipelineQueueLoaded OnQueueLoaded;` — Called when a queue is loaded into the system.
- L104 _private prototype_ `void OnExecutorFinished(UMoviePipelineExecutorBase* InPipelineExecutor, bool bSuccess);` — Called when the executor is finished so that we can release it and stop reporting IsRendering() == true.
- L105 _private prototype_ `void OnSequencerContextBinding(bool& bAllowBinding);`
- L109 _private member_ `TObjectPtr<UMoviePipelineExecutorBase> ActiveExecutor;` — `UPROPERTY(Transient)`
- L112 _private member_ `TObjectPtr<UMoviePipelineQueue> CurrentQueue;` — `UPROPERTY(Transient, Instanced)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIERENDERPIPELINEEDITOR_API`
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMoviePipelineQueueLoaded) UCLASS(MinimalAPI, BlueprintType) class UMoviePipelineQueueSubsystem : public UEditorSubsystem { GENERATED_BODY() public: UMoviePipelineQueueSubsystem() { CurrentQueue = CreateDefaultSubobject<UMoviePipelineQueue>("EditorMoviePipelineQueue"); } UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline") UMoviePipelineQueue* GetQueue() const { return CurrentQueue; } UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline") bool LoadQueue(UMoviePipelineQueue* QueueToLoad, const bool bPromptOnReplacingDirtyQueue = true); UFUNCTION(BlueprintPure, Category = "Movie Render Pipeline") bool IsQueueDirty() const;`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/MovieRenderPipelineSettings.h` (Public)


#### class `UMovieRenderPipelineProjectSettings`  
`class UMovieRenderPipelineProjectSettings : public UObject`  
_L20-100_
- reflection: `UCLASS(BlueprintType, config=Editor, defaultconfig, MinimalAPI)`
- inherits: `UObject`
- desc: Universal Movie Render Pipeline settings that apply to the whole project.
- L25 _public prototype_ `UMovieRenderPipelineProjectSettings();`
- L33 _public member_ `FSoftClassPath DefaultPipeline;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, NoClear, meta = (MetaClass = "/Script/MovieRenderPipelineCore.MoviePipelineBase"), Category="Movie Render Pipeline", DisplayName = "Default Configuration Pipeline")` — This allows you to implement your own Pipeline to handle timing and rendering of a movie. Changing this will allow you to re-use the existing UI/Executors while providing your own logic for producing a single render.
- L39 _public member_ `FDirectoryPath PresetSaveDir;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Movie Render Pipeline", DisplayName = "Preset Save Location")` — Which directory should we try to save presets in by default?
- L46 _public member_ `TSoftObjectPtr<UMoviePipelinePrimaryConfig> LastPresetOrigin;` — `UPROPERTY(Transient, BlueprintReadWrite, Category = "Movie Render Pipeline")` — What was the last configuration preset the user used? Can be null.
- L55 _public member_ `FSoftClassPath DefaultLocalExecutor;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (MetaClass = "/Script/MovieRenderPipelineCore.MoviePipelineExecutorBase"), Category="Movie Render Pipeline")` — When the user uses the UI to request we render a movie locally, which implementation should we use to execute the queue of things they want rendered. This allows you to implement your own executor which does different logic. See UMoviePipelineExecutorBase for more information. This is used for the Render button on the UI.
- L64 _public member_ `FSoftClassPath DefaultRemoteExecutor;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (MetaClass = "/Script/MovieRenderPipelineCore.MoviePipelineExecutorBase"), Category = "Movie Render Pipeline")` — When the user uses the UI to request we render a movie remotely, which implementation should we use to execute the queue of things they want rendered. This allows you to implement your own executor which does different logic. See UMoviePipelineExecutorBase for more information. This is used for the Render Remotely button on the UI.
- L72 _public member_ `FSoftClassPath DefaultExecutorJob;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta = (MetaClass = "/Script/MovieRenderPipelineCore.MoviePipelineExecutorJob"), Category="Movie Render Pipeline")` — Which Job class should we create by default when adding a job? This allows you to make custom jobs that will have editable properties in the UI for special handling with your executor. This can be made dynamic if you add jobs to the queue programatically instead of through the UI.
- L76 _public member_ `TSoftObjectPtr<UMovieGraphConfig> DefaultGraph;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="Movie Render Pipeline")` — The graph that newly-created graph assets will be based off of.
- L81 _public member_ `TSoftObjectPtr<UMovieGraphConfig> DefaultQuickRenderGraph;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="Movie Render Pipeline")` — The graph that quick renders will use.
- L92 _public member_ `TArray<FSoftClassPath> DefaultClasses;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Movie Render Pipeline", meta = (MetaClass = "/Script/MovieRenderPipelineCore.MoviePipelineSetting"), DisplayName = "Default Job Settings Classes")` — The settings specified here will automatically be added to a Movie Pipeline Primary Configuration when using the UI. This does not apply to scripting and does not apply to runtime. It is only a convenience function so that when a job is created, it can be pre-filled with some settings to make the render functional out of the gate. It can also be used to automatically add your own setting to jobs. This only applies to jobs created via the UI. If you do not use the UI (ie: Scripting/Python) you will need to add settings by hand for each job you create.
- L96 _public prototype_ `static FSoftObjectPath GetDefaultGraphPath();` — Gets the path to the default graph asset supplied by MRQ.
- L99 _public prototype_ `static FSoftObjectPath GetDefaultQuickRenderGraphPath();` — Gets the path to the default quick render graph asset supplied by MRQ.

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/Widgets/Graph/SModifierCollectionsHeader.h` (Public)


#### class `SMovieGraphCollectionsHeaderWidget`  
`class SMovieGraphCollectionsHeaderWidget final : public SCompoundWidget`  
_L13-34_
- inherits: `SCompoundWidget`
- desc: A widget which displays the header for modifier collections in the details panel.
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCollectionPicked, FName);`
- L18 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphCollectionsHeaderWidget)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(TWeakInterfacePtr<IMovieGraphModifierNodeInterface>, WeakModifierInterface) SLATE_EVENT(FOnCollectionPicked, OnCollectionPicked);` — The modifier node that is associated with the collections.
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _private member_ `TWeakInterfacePtr<IMovieGraphModifierNodeInterface> WeakModifierInterface;` — The modifier node associated with this widget (if any).
- L33 _private member_ `FOnCollectionPicked OnCollectionPicked;` — Called when a collection is picked in the list.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCollectionPicked, FName);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/Widgets/Graph/SMovieGraphCollectionPicker.h` (Public)


#### class `SMovieGraphCollectionPicker`  
`class SMovieGraphCollectionPicker final : public SMovieGraphSimplePicker<FName>`  
_L12-45_
- inherits: `SMovieGraphSimplePicker<FName>`
- desc: Discovers collections that are pickable from a specific graph, and presents them in a list.
- L15 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCollectionPicked, FName);`
- L16 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilter, FName);`
- L18 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphCollectionPicker)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(UMovieGraphConfig*, Graph) SLATE_EVENT(FOnCollectionPicked, OnCollectionPicked);` — The graph to begin discovering collections from.
- L27 _public prototype_ `SLATE_EVENT(FOnFilter, OnFilter);` — Optional filter that can prevent discovered collections from showing up in the list.
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `void UpdateDataSource();` — Discovers all available collections, and refreshes the data the list is displaying.
- L38 _private member_ `UMovieGraphConfig* CurrentGraph = nullptr;` — The current graph being viewed. The data source will be populated from this graph.
- L41 _private member_ `FOnCollectionPicked OnCollectionPicked;` — Called when a collection is picked in the list.
- L44 _private member_ `FOnFilter OnFilter;` — Optional filter that can prevent discovered collections from showing up in the list.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCollectionPicked, FName);`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilter, FName);`

### `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/Widgets/Graph/SMovieGraphModifierCollectionsList.h` (Public)


#### class `SMovieGraphModifierCollectionsList`  
`class SMovieGraphModifierCollectionsList final : public SCompoundWidget`  
_L11-39_
- inherits: `SCompoundWidget`
- desc: Lists out the collections that have been chosen for a specific modifier node.
- L14 _public function_ `SLATE_BEGIN_ARGS(SMovieGraphModifierCollectionsList)`
- L16 _public prototype_ `SLATE_ATTRIBUTE(TWeakInterfacePtr<IMovieGraphModifierNodeInterface>, WeakModifierInterface) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The modifier node that is associated with the collections.
- L22 _public prototype_ `void Refresh();` — Refreshes the widget and its internal data source.
- L25 _private prototype_ `static FText GetCollectionRowText(const FName CollectionName);`
- L28 _private prototype_ `void RefreshListDataSource();` — Refreshes the list's data source to reflect the data model.
- L32 _private member_ `TArray<FName> ListDataSource;` — The data source for the list view. Modifiers don't expose a direct pointer to the array of collections, which is required by the list view.
- L35 _private member_ `TWeakInterfacePtr<IMovieGraphModifierNodeInterface> WeakModifierInterface;` — The modifier node associated with this widget (if any).
- L38 _private member_ `TSharedPtr<SMovieGraphSimpleList<FName>> CollectionsList;` — Displays the collections which have been chosen.
