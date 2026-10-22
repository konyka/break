# Plugins / OptimusEditor

- module root: `Plugins/Animation/DeformerGraph/Source/OptimusEditor`
- headers: 40; symbols: 869
- symbol kinds: class=54, delegate=13, enum=4, enumerator=16, function=79, macro=1, member=201, namespace=1, prototype=480, struct=18, typedef=2
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, AssetTools, BlueprintGraph, ComputeFramework, Core, CoreUObject, EditorFramework, Engine, GraphEditor, InputCore, KismetCompiler, MessageLog, OptimusCore, OptimusDeveloper, Persona, PropertyEditor, RHI, Slate, SlateCore, SourceCodeAccess, StructUtilsEditor, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusDeformerAssetActions.h` (Private)


#### class `FOptimusDeformerAssetActions`  
`class FOptimusDeformerAssetActions : public FAssetTypeActions_Base`  
_L10-33_
- inherits: `FAssetTypeActions_Base`
- L14 _public prototype_ `FOptimusDeformerAssetActions(EAssetTypeCategories::Type InAssetCategoryBit = EAssetTypeCategories::Animation);`
- L18 _protected prototype_ `FText GetName() const override;` — IAssetTypeActions overrides
- L19 _protected prototype_ `FColor GetTypeColor() const override;`
- L20 _protected prototype_ `UClass* GetSupportedClass() const override;`
- L21 _protected prototype_ `void OpenAssetEditor( const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>() ) override;`
- L25 _protected prototype_ `uint32 GetCategories() override;`
- L26 _protected prototype_ `const TArray<FText>& GetSubMenus() const override;`
- L27 _protected prototype_ `TSharedPtr<SWidget> GetThumbnailOverlay( const FAssetData& AssetData ) const override;`
- L32 _private member_ `EAssetTypeCategories::Type AssetCategoryBit;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusDeformerFactory.h` (Private)


#### class `UOptimusDeformerFactory`  
`class UOptimusDeformerFactory : public UFactory`  
_L14-41_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Implements a factory for UOptimusDeformer objects.
- L19 _public prototype_ `UOptimusDeformerFactory();`
- L22 _public function_ `FString GetDefaultNewAssetName() const override` — UFactory overrides
- L27 _public prototype_ `UObject* FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* OutWarn ) override;`
- L37 _public prototype_ `uint32 GetMenuCategories() const override;` — Which category this object belongs to in the "New Asset" menu.
- L40 _public prototype_ `bool ShouldShowInNewMenu() const override;` — Whether the object should be shown in the "New Asset" menu in the asset browser.

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusDetailsCustomization.h` (Private)


#### class `FOptimusDataTypeRefCustomization`  
`class FOptimusDataTypeRefCustomization : public IPropertyTypeCustomization`  
_L25-62_
- inherits: `IPropertyTypeCustomization`
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L32 _public prototype_ `void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;` — IPropertyTypeCustomization overrides
- L38 _public prototype_ `void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`
- L44 _public function_ `void SetUsageMaskOverride(EOptimusDataTypeUsageFlags InOverride)`
- L51 _private prototype_ `FOptimusDataTypeHandle GetCurrentDataType() const;`
- L52 _private prototype_ `void OnDataTypeChanged(FOptimusDataTypeHandle InDataType);`
- L54 _private prototype_ `FText GetDeclarationText() const;`
- L56 _private member_ `TSharedPtr<IPropertyHandle> TypeNameProperty;`
- L57 _private member_ `TSharedPtr<IPropertyHandle> TypeObjectProperty;`
- L58 _private member_ `TAttribute<FOptimusDataTypeHandle> CurrentDataType;`
- L60 _private member_ `EOptimusDataTypeUsageFlags UsageMaskOverride = EOptimusDataTypeUsageFlags::None;`

#### class `FOptimusExecutionDomainCustomization`  
`class FOptimusExecutionDomainCustomization : public IPropertyTypeCustomization`  
_L65-121_
- inherits: `IPropertyTypeCustomization`
- L69 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L71 _public prototype_ `FOptimusExecutionDomainCustomization();`
- L74 _public prototype_ `void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L79 _public function_ `void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L97 _private prototype_ `FText FormatContextName( FName InName ) const;`
- L101 _private prototype_ `void UpdateContextNames();`
- L103 _private prototype_ `static void SetExecutionDomain( TSharedRef<IPropertyHandle> InPropertyHandle, const FOptimusExecutionDomain& InExecutionDomain, DomainFlags InSetFlags = DomainAll );`
- L109 _private prototype_ `static TOptional<FOptimusExecutionDomain> TryGetSingleExecutionDomain( TSharedRef<IPropertyHandle> InPropertyHandle, DomainFlags InCompareFlags = DomainAll, bool bInCheckMultiples = true );`
- L115 _private member_ `TSharedPtr<SComboBox<FName>> ComboBox;`
- L116 _private member_ `TSharedPtr<SEditableTextBox> ExpressionTextBox;`
- L118 _private member_ `TArray<FName> ContextNames;`
- L120 _private member_ `TArray<TWeakObjectPtr<UObject>> WeakOwningObjects;`

#### enum `FOptimusExecutionDomainCustomization::DomainFlags`  
`enum DomainFlags`  
_L85-92_
- L87 _public enumerator_ `DomainType = 0x1`
- L88 _public enumerator_ `DomainName = 0x2`
- L89 _public enumerator_ `DomainExpression = 0x4`
- L91 _public enumerator_ `DomainAll = DomainType + DomainName + DomainExpression`

#### class `FOptimusDataDomainCustomization`  
`class FOptimusDataDomainCustomization : public IPropertyTypeCustomization`  
_L126-192_
- inherits: `IPropertyTypeCustomization`
- L130 _public prototype_ `DECLARE_EVENT_OneParam(FOptimusDataDomainCustomization, FOnDataDomainChanged, const FOptimusDataDomain& );`
- L132 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L134 _public prototype_ `FOptimusDataDomainCustomization();`
- L137 _public prototype_ `void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L142 _public function_ `void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L148 _public prototype_ `void SetAllowParameters(const bool bInAllowParameters);`
- L150 _public member_ `FOnDataDomainChanged OnDataDomainChangedDelegate;`
- L164 _private prototype_ `FText FormatDomainDimensionNames( TSharedRef<TArray<FName>> InDimensionNames ) const;`
- L168 _private prototype_ `void GenerateDimensionNames( const TArray<UObject*>& InOwningObjects );`
- L172 _private prototype_ `static TOptional<FOptimusDataDomain> TryGetSingleDataDomain( TSharedRef<IPropertyHandle> InPropertyHandle, DomainFlags InCompareFlags = DomainAll, bool bInCheckMultiples = true );`
- L178 _private prototype_ `void SetDataDomain( TSharedRef<IPropertyHandle> InPropertyHandle, const FOptimusDataDomain& InDataDomain, DomainFlags InSetFlags = DomainAll );`
- L184 _private member_ `TSharedRef<TArray<FName>> ParameterMarker;`
- L185 _private member_ `TSharedRef<TArray<FName>> ExpressionMarker;`
- L187 _private member_ `TSharedPtr<SComboBox<TSharedRef<TArray<FName>>>> DimensionalComboBox;`
- L188 _private member_ `TSharedPtr<SEditableTextBox> ExpressionTextBox;`
- L190 _private member_ `TArray<TSharedRef<TArray<FName>>> DomainDimensionNames;`
- L191 _private member_ `bool bAllowParameters = false;`

#### enum `FOptimusDataDomainCustomization::DomainFlags`  
`enum DomainFlags`  
_L152-160_
- L154 _public enumerator_ `DomainType = 0x1`
- L155 _public enumerator_ `DomainDimensions = 0x2`
- L156 _public enumerator_ `DomainMultiplier = 0x4`
- L157 _public enumerator_ `DomainExpression = 0x8`
- L159 _public enumerator_ `DomainAll = DomainType + DomainDimensions + DomainMultiplier + DomainExpression`

#### class `FOptimusShaderTextCustomization`  
`class FOptimusShaderTextCustomization : public IPropertyTypeCustomization`  
_L196-228_
- inherits: `IPropertyTypeCustomization`
- L200 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L202 _public prototype_ `FOptimusShaderTextCustomization();`
- L205 _public prototype_ `void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L210 _public function_ `void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L216 _private member_ `TSharedRef<FOptimusHLSLSyntaxHighlighter> SyntaxHighlighter;`
- L218 _private member_ `TSharedPtr<IPropertyHandle> DeclarationsProperty;`
- L219 _private member_ `TSharedPtr<IPropertyHandle> ShaderTextProperty;`
- L221 _private member_ `TSharedPtr<SExpandableArea> ExpandableArea;`
- L222 _private member_ `TSharedPtr<SScrollBar> HorizontalScrollbar;`
- L223 _private member_ `TSharedPtr<SScrollBar> VerticalScrollbar;`
- L225 _private member_ `TSharedPtr<SMultiLineEditableText> ShaderEditor;`
- L227 _private prototype_ `FText GetShaderText() const;`

#### class `FOptimusParameterBindingCustomization`  
`class FOptimusParameterBindingCustomization : public IPropertyTypeCustomization`  
_L231-263_
- inherits: `IPropertyTypeCustomization`
- L247 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L248 _public prototype_ `static EVisibility IsAtomicCheckBoxVisible(const TArray<TWeakObjectPtr<UObject>>& InSelectedObjects, TSharedRef<IPropertyHandle> InPropertyHandle);`
- L249 _public prototype_ `static EVisibility IsSupportReadCheckBoxVisible(const TArray<TWeakObjectPtr<UObject>>& InSelectedObjects, TSharedRef<IPropertyHandle> InPropertyHandle);`
- L251 _public prototype_ `FOptimusParameterBindingCustomization();`
- L254 _public prototype_ `void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L259 _public prototype_ `void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

#### struct `FOptimusParameterBindingCustomization::FColumnSizeData`  
`struct FColumnSizeData`  
_L234-245_
- L236 _public function_ `FColumnSizeData() : DataTypeColumnSize(0.5f) , DataDomainColumnSize(0.5f)`
- L238 _public function_ `float GetDataTypeColumnSize() const`
- L239 _public function_ `void OnDataTypeColumnResized(float InSize)`
- L240 _public function_ `float GetDataDomainColumnSize() const`
- L241 _public function_ `void OnDataDomainColumnResized(float InSize)`
- L243 _public member_ `float DataTypeColumnSize;`
- L244 _public member_ `float DataDomainColumnSize;`

#### class `FOptimusParameterBindingArrayBuilder`  
`class FOptimusParameterBindingArrayBuilder : public FDetailArrayBuilder , public TSharedFromThis<FOptimusParameterBindingArrayBuilder>`  
_L266-295_
- inherits: `FDetailArrayBuilder,TSharedFromThis<FOptimusParameterBindingArrayBuilder>`
- L271 _public prototype_ `static TSharedRef<FOptimusParameterBindingArrayBuilder> MakeInstance( TSharedRef<IPropertyHandle> InPropertyHandle, TSharedPtr<FOptimusParameterBindingCustomization::FColumnSizeData> InColumnSizeData, const bool bInAllowParameters);`
- L276 _public prototype_ `FOptimusParameterBindingArrayBuilder( TSharedRef<IPropertyHandle> InPropertyHandle, TSharedPtr<FOptimusParameterBindingCustomization::FColumnSizeData> InColumnSizeData, const bool bInAllowParameters);`
- L282 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;` — FDetailArrayBuilder Interface
- L285 _public prototype_ `void GenerateWrapperStructHeaderRowContent(FDetailWidgetRow& NodeRow, TSharedRef<SWidget> NameContent);` — Used by FOptimusParameterBindingArrayCustomization
- L288 _private prototype_ `void OnGenerateEntry(TSharedRef<IPropertyHandle> ElementProperty, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder) const;`
- L290 _private member_ `TSharedPtr<IPropertyHandleArray> ArrayProperty;`
- L292 _private member_ `TSharedPtr<FOptimusParameterBindingCustomization::FColumnSizeData> ColumnSizeData;`
- L294 _private member_ `bool bAllowParameters = false;`

#### class `FOptimusParameterBindingArrayCustomization`  
`class FOptimusParameterBindingArrayCustomization : public IPropertyTypeCustomization`  
_L298-322_
- inherits: `IPropertyTypeCustomization`
- L301 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L306 _public prototype_ `FOptimusParameterBindingArrayCustomization();`
- L309 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L314 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L320 _private member_ `TSharedPtr<FOptimusParameterBindingArrayBuilder> ArrayBuilder;`
- L321 _private member_ `TSharedRef<FOptimusParameterBindingCustomization::FColumnSizeData> ColumnSizeData;`

#### class `FOptimusValueContainerStructCustomization`  
`class FOptimusValueContainerStructCustomization : public IPropertyTypeCustomization`  
_L325-348_
- inherits: `IPropertyTypeCustomization`
- L328 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L333 _public prototype_ `FOptimusValueContainerStructCustomization();`
- L335 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L340 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L345 _private member_ `TSharedPtr<IPropertyHandle> InnerPropertyHandle;`
- L347 _private member_ `TSharedPtr<IPropertyTypeCustomization> PropertyBagCustomization;`

#### class `FOptimusValidatedNameCustomization`  
`class FOptimusValidatedNameCustomization : public IPropertyTypeCustomization`  
_L351-369_
- inherits: `IPropertyTypeCustomization`
- L354 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L356 _public prototype_ `FOptimusValidatedNameCustomization();`
- L359 _public prototype_ `void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L364 _public function_ `void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`

#### class `FOptimusSourceDetailsCustomization`  
`class FOptimusSourceDetailsCustomization : public IDetailCustomization`  
_L373-394_
- inherits: `IDetailCustomization`
- desc: UI customization for UOptimusSource
- L377 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L380 _protected prototype_ `FOptimusSourceDetailsCustomization();`
- L383 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L387 _private member_ `UOptimusSource* OptimusSource = nullptr;`
- L389 _private member_ `TSharedRef<FOptimusHLSLSyntaxHighlighter> SyntaxHighlighter;`
- L390 _private member_ `TSharedPtr<SOptimusShaderTextDocumentTextBox> SourceTextBox;`
- L392 _private prototype_ `FText GetText() const;`
- L393 _private prototype_ `void OnTextChanged(const FText& InValue);`

#### class `FOptimusComponentSourceBindingDetailsCustomization`  
`class FOptimusComponentSourceBindingDetailsCustomization : public IDetailCustomization`  
_L398-418_
- inherits: `IDetailCustomization`
- desc: UI customization for UOptimusComponentSourceBinding
- L401 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L404 _protected prototype_ `FOptimusComponentSourceBindingDetailsCustomization();`
- L407 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L411 _protected prototype_ `void ComponentSourceChanged(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — Handle combo box selection.
- L415 _private member_ `UOptimusComponentSourceBinding* OptimusSourceBinding = nullptr;` — SourceBinding being edited.
- L417 _private member_ `TArray<TSharedPtr<FString>> ComponentSources;` — Array of combo box entries.

#### class `FOptimusResourceDescriptionDetailsCustomization`  
`class FOptimusResourceDescriptionDetailsCustomization : public IDetailCustomization`  
_L422-435_
- inherits: `IDetailCustomization`
- desc: UI customization for UOptimusResourceDescription
- L426 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L430 _protected prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L434 _private member_ `TArray<UOptimusComponentSourceBinding*> ComponentBindings;`

#### class `FOptimusDeformerInstanceComponentBindingCustomization`  
`class FOptimusDeformerInstanceComponentBindingCustomization : public IPropertyTypeCustomization`  
_L440-467_
- inherits: `IPropertyTypeCustomization`
- desc: UI customization for FOptimusDeformerInstanceComponentBinding
- L444 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L447 _protected prototype_ `FOptimusDeformerInstanceComponentBindingCustomization() = default;`
- L450 _protected prototype_ `void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — -- IPropertyTypeCustomization overrides
- L455 _protected function_ `void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L461 _protected prototype_ `void ComponentsReplaced(const TMap<UObject*, UObject*>& InReplacementMap);`
- L464 _private member_ `TArray<FName> ComponentNames;`
- L465 _private typedef_ `using FComponentHandle = TSharedPtr<FSoftObjectPath>;`
- L466 _private member_ `TArray<FComponentHandle> ComponentHandles;`

#### Free symbols / members of external scopes

- L123 _prototype_ `ENUM_CLASS_FLAGS(FOptimusExecutionDomainCustomization::DomainFlags);`
- L130 _delegate_ `DECLARE_EVENT_OneParam(FOptimusDataDomainCustomization, FOnDataDomainChanged, const FOptimusDataDomain& );`
- L194 _prototype_ `ENUM_CLASS_FLAGS(FOptimusDataDomainCustomization::DomainFlags);`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditor.h` (Private)


#### class `FOptimusEditor`  
`class FOptimusEditor : public IOptimusEditor, public FGCObject, public FNotifyHook`  
_L40-297_
- inherits: `IOptimusEditor,FGCObject,FNotifyHook`
- L46 _public prototype_ `FOptimusEditor();`
- L49 _public prototype_ `void Construct( const EToolkitMode::Type InMode, const TSharedPtr< class IToolkitHost >& InToolkitHost, UOptimusDeformer* InDeformerObject );`
- L57 _public function_ `UOptimusEditorGraph* GetGraph() const` — @brief Returns the graph that this editor operates on. @return The graph that this editor operates on.
- L63 _public function_ `template<typename Interface> Interface* GetDeformerInterface()`
- L67 _public prototype_ `UOptimusDeformer* GetDeformer() const;`
- L69 _public function_ `TSharedRef<IPersonaToolkit> GetPersonaToolkit() const override`
- L74 _public prototype_ `TSharedRef<IMessageLogListing> GetMessageLog() const;`
- L76 _public prototype_ `FText GetGraphCollectionRootName() const;`
- L78 _public prototype_ `UOptimusActionStack* GetActionStack() const;`
- L82 _public prototype_ `void InspectObject(UObject* InObject);` — @brief Set object to view in the details panel. @param InObject  The object to view and edit in the details panel.
- L86 _public prototype_ `void InspectObjects(const TArray<UObject *> &InObjects);` — @brief Set a group of object to view in the details panel. @param InObject  The objects to view and edit in the details panel.
- L89 _public prototype_ `FName GetToolkitFName() const override;` — IToolkit overrides
- L90 _public prototype_ `FText GetBaseToolkitName() const override;`
- L91 _public prototype_ `FString GetWorldCentricTabPrefix() const override;`
- L92 _public prototype_ `FLinearColor GetWorldCentricTabColorScale() const override;`
- L95 _public prototype_ `void OnClose() override;`
- L99 _public prototype_ `bool SetEditGraph(UOptimusNodeGraph *InNodeGraph);` — --
- L101 _public prototype_ `DECLARE_EVENT( FOptimusEditor, FOnRefreshEvent );`
- L102 _public function_ `FOnRefreshEvent& OnRefresh()`
- L105 _public prototype_ `void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject overrides
- L106 _public function_ `virtual FString GetReferencerName() const override`
- L114 _private prototype_ `void Compile();` — Editor commands
- L115 _private prototype_ `void ZoomToFitGraph();`
- L117 _private prototype_ `bool CanCompile() const;`
- L119 _private prototype_ `void CompileBegin(UOptimusDeformer* InDeformer);`
- L120 _private prototype_ `void CompileEnd(UOptimusDeformer* InDeformer);`
- L123 _private prototype_ `void OnCompileMessage(FOptimusCompilerDiagnostic const& Diagnostic);` — Called for every compilation result. There may be multiple calls for each Compile.
- L125 _private prototype_ `void InstallDataProviders();`
- L126 _private prototype_ `void RemoveDataProviders();`
- L132 _private prototype_ `void SelectAllNodes();` — Select all nodes in the visible graph
- L135 _private prototype_ `bool CanSelectAllNodes() const;` — Returns \c true if all the nodes can be selected.
- L138 _private prototype_ `void DeleteSelectedNodes();` — Delete all selected nodes in the graph
- L141 _private prototype_ `bool CanDeleteSelectedNodes() const;` — Returns \c true if all the nodes can be selected.
- L143 _private prototype_ `void CopySelectedNodes() const;`
- L144 _private prototype_ `bool CanCopyNodes() const;`
- L146 _private prototype_ `void CutSelectedNodes() const;`
- L147 _private prototype_ `bool CanCutNodes() const;`
- L149 _private prototype_ `void PasteNodes() const;`
- L150 _private prototype_ `bool CanPasteNodes();`
- L152 _private prototype_ `void DuplicateNodes() const;`
- L153 _private prototype_ `bool CanDuplicateNodes() const;`
- L155 _private prototype_ `void PackageNodes();`
- L156 _private prototype_ `bool CanPackageNodes() const;`
- L158 _private prototype_ `void UnpackageNodes();`
- L159 _private prototype_ `bool CanUnpackageNodes() const;`
- L161 _private prototype_ `void CollapseNodesToFunction();`
- L162 _private prototype_ `void CollapseNodesToSubGraph();`
- L163 _private prototype_ `bool CanCollapseNodes() const;`
- L165 _private prototype_ `void ExpandCollapsedNode();`
- L166 _private prototype_ `bool CanExpandCollapsedNode() const;`
- L168 _private prototype_ `void ConvertToFunction();`
- L169 _private prototype_ `bool CanConvertToFunction() const;`
- L171 _private prototype_ `void ConvertToSubGraph();`
- L172 _private prototype_ `bool CanConvertToSubGraph() const;`
- L174 _private prototype_ `void OnCreateComment();`
- L176 _private prototype_ `void OnFindInDeformer();`
- L180 _private prototype_ `void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);` — Graph event listeners
- L181 _private prototype_ `void OnNodeDoubleClicked(class UEdGraphNode* Node);`
- L182 _private prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);`
- L183 _private prototype_ `bool OnVerifyNodeTextCommit(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage);`
- L184 _private prototype_ `FReply OnSpawnGraphNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UEdGraph* InGraph);`
- L189 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnGraphNotified, EOptimusGraphNotifyType , UOptimusNodeGraph* , UObject* );` — Utility for other widgets to subscribe to Graph Notifies
- L190 _public prototype_ `void SubscribeToGraphNotifies(UOptimusNodeGraph* Graph, const FOnGraphNotified& OnGraphNotifiedDelegate);`
- L191 _public prototype_ `void UnsubscribeToGraphNotifies(FDelegateHandle DelegateHandle);`
- L195 _public prototype_ `DECLARE_EVENT_OneParam(FOptimusEditor, FOnSelectedNodesChanged, const TArray<TWeakObjectPtr<UObject>>&);` — Broadcast Graph Event
- L196 _public function_ `FOnSelectedNodesChanged& OnSelectedNodesChanged()`
- L199 _public prototype_ `DECLARE_EVENT(FOptimusEditor, FOnDiagnosticsUpdated);` — Broadcast Diagnostic Event
- L200 _public function_ `FOnDiagnosticsUpdated& OnDiagnosticsUpdated()`
- L202 _public function_ `virtual void AddCompilationDiagnostic(const FOptimusCompilerDiagnostic& InDiagnostic)`
- L203 _public function_ `virtual const TArray<FOptimusCompilerDiagnostic>& GetCompilationDiagnostics() const`
- L207 _private prototype_ `void RegisterToolbar();` — Toolbar and command helpers
- L209 _private prototype_ `void BindCommands();`
- L213 _public prototype_ `void HandlePreviewSceneCreated(const TSharedRef<IPersonaPreviewScene>& InPreviewScene);` — Handlers for created tabs
- L214 _public prototype_ `void HandlePreviewMeshChanged(USkeletalMesh* InOldPreviewMesh, USkeletalMesh* InNewPreviewMesh);`
- L215 _public prototype_ `void HandleDetailsCreated(const TSharedRef<IDetailsView>& InDetailsView);`
- L216 _public prototype_ `void HandleViewportCreated(const TSharedRef<IPersonaViewport>& InPersonaViewport);`
- L219 _public function_ `TSharedPtr<SGraphEditor> GetGraphEditorWidget() const` — KILL ME
- L222 _public function_ `TSharedPtr<SFindInDeformer> GetFindResultsWidget() const` — @TODO: Remove below if above gets removed
- L224 _public prototype_ `bool GetBoundsForSelectedNodes(FSlateRect& Rect);`
- L227 _private prototype_ `void CreateMessageLog();`
- L228 _private prototype_ `void HandleMessageTokenClicked(const TSharedRef<class IMessageToken>& InMessageToken);`
- L229 _private prototype_ `void CreateWidgets();`
- L230 _private prototype_ `TSharedRef<SGraphEditor> CreateGraphEditorWidget();`
- L231 _private prototype_ `FGraphAppearanceInfo GetGraphAppearance() const;`
- L232 _private prototype_ `bool IsGraphReadOnly() const;`
- L233 _private prototype_ `bool IsGraphEditable() const;`
- L234 _private prototype_ `bool IsPropertyReadOnly(const FPropertyAndParent& InPropertyAndParent) const;`
- L236 _private prototype_ `TArray<UOptimusNode*> GetSelectedModelNodes() const;`
- L238 _private prototype_ `void StoreCurrentViewLocation();`
- L240 _private prototype_ `void OnDeformerModified( EOptimusGlobalNotifyType InNotifyType, UObject *InModifiedObject );`
- L246 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);` — Called when the inspector has changed a value.
- L248 _private prototype_ `void OnDataTypeChanged();`
- L251 _private prototype_ `FSlateIcon GetCompileStatusIcon() const;`
- L252 _private prototype_ `FText GetCompileStatusTooltip() const;`
- L256 _private member_ `TSharedPtr<IPersonaToolkit> PersonaToolkit;` — Persona toolkit for the skelmesh preview
- L259 _private member_ `TSharedPtr<IPersonaViewport> ViewportWidget;` — -- Widgets
- L260 _private member_ `TSharedPtr<SFindInDeformer> FindResults;`
- L261 _private member_ `TSharedPtr<SGraphEditor> GraphEditorWidget;`
- L262 _private member_ `TSharedPtr<IDetailsView> PropertyDetailsWidget;`
- L263 _private member_ `TSharedPtr<IDetailsView> PreviewDetailsWidget;`
- L264 _private member_ `TSharedPtr<SWidget> CompilerResultsWidget;`
- L265 _private member_ `TSharedPtr<IMessageLogListing> CompilerResultsListing;`
- L267 _private member_ `UOptimusDeformer* DeformerObject = nullptr;`
- L268 _private member_ `UOptimusEditorGraph* EditorGraph = nullptr;`
- L269 _private member_ `UOptimusNodeGraph* PreviousEditedNodeGraph = nullptr;`
- L270 _private member_ `UOptimusNodeGraph* UpdateGraph = nullptr;`
- L271 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;`
- L274 _private member_ `UDebugSkelMeshComponent* SkeletalMeshComponent = nullptr;` — Compute Graph Component and data providers.
- L275 _private member_ `UOptimusMeshDeformer* MeshDeformer = nullptr;`
- L279 _private member_ `TSharedPtr<IEditableSkeleton> EditableSkeleton;` — An editability wrapper around USkeleton. Used by the Persona viewport for picking and manipulation.
- L288 _private member_ `TArray<FCapsuleInfo> CapsuleInfos;`
- L290 _private member_ `TArray<FOptimusCompilerDiagnostic> Diagnostics;`
- L292 _private member_ `FOnRefreshEvent RefreshEvent;`
- L293 _private member_ `FOnSelectedNodesChanged SelectedNodesChangedEvent;`
- L294 _private member_ `FOnDiagnosticsUpdated DiagnosticsUpdatedEvent;`
- L296 _private member_ `TMap<FDelegateHandle, TSet<TWeakObjectPtr<UOptimusNodeGraph>>> GraphSubscribers;`

#### struct `FOptimusEditor::FCapsuleInfo`  
`struct FCapsuleInfo`  
_L282-286_
- desc: Bone selection data
- L284 _public member_ `FName Name;`
- L285 _public member_ `int32 Index;`

#### Free symbols / members of external scopes

- L101 _delegate_ `DECLARE_EVENT( FOptimusEditor, FOnRefreshEvent );`
- L189 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnGraphNotified, EOptimusGraphNotifyType , UOptimusNodeGraph* , UObject* );` — Utility for other widgets to subscribe to Graph Notifies
- L195 _delegate_ `DECLARE_EVENT_OneParam(FOptimusEditor, FOnSelectedNodesChanged, const TArray<TWeakObjectPtr<UObject>>&);` — Broadcast Graph Event
- L199 _delegate_ `DECLARE_EVENT(FOptimusEditor, FOnDiagnosticsUpdated);` — Broadcast Diagnostic Event

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorCommands.h` (Private)


#### class `FOptimusEditorCommands`  
`class FOptimusEditorCommands : public TCommands<FOptimusEditorCommands>`  
_L9-20_
- inherits: `TCommands<FOptimusEditorCommands>`
- desc: Optimus editor command set.
- L13 _public prototype_ `FOptimusEditorCommands();`
- L16 _public prototype_ `void RegisterCommands() override;` — TCommands<> overrides
- L18 _public member_ `TSharedPtr<FUICommandInfo> Compile;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFitGraph;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorDelegates.h` (Private)


#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOptimusOpenGraphEvent, UOptimusNodeGraph*);` — A simple delegate that fires when the Optimus when a specific graph should be opened.
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOptimusOpenGraphEvent, UOptimusNodeGraph*);` — A simple delegate that fires when the Optimus when a specific graph should be opened.

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraph.h` (Private)


#### class `UOptimusEditorGraph`  
`class UOptimusEditorGraph : public UEdGraph`  
_L20-83_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- L25 _public prototype_ `UOptimusEditorGraph();`
- L27 _public prototype_ `void InitFromNodeGraph(UOptimusNodeGraph* InNodeGraph);`
- L29 _public prototype_ `void Reset();`
- L31 _public function_ `UOptimusNodeGraph* GetModelGraph() const`
- L33 _public prototype_ `UEdGraphNode* FindGraphNodeFromModelNode(const UOptimusNode* InModelNode);`
- L34 _public prototype_ `UOptimusNode* FindModelNodeFromGraphNode(const UEdGraphNode* InGraphNode);`
- L36 _public prototype_ `UOptimusEditorGraphNode* FindOptimusGraphNodeFromModelNode(const UOptimusNode* InModelNode);`
- L38 _public function_ `const TSet<UEdGraphNode*> &GetSelectedNodes() const`
- L40 _public prototype_ `const TArray<UOptimusNode*> GetSelectedModelNodes() const;`
- L42 _public prototype_ `void HandleGraphNodeMoved();`
- L44 _public prototype_ `bool GetBoundsForSelectedNodes(FSlateRect& Rect);`
- L47 _public prototype_ `void RefreshVisualNode(UOptimusEditorGraphNode *InGraphNode);` — Do a visual refresh of the node.
- L50 _public prototype_ `static const FSlateBrush* GetGraphTypeIcon(const UOptimusNodeGraph* InModelGraph);`
- L55 _protected function_ `void SetSelectedNodes(const TSet<UEdGraphNode*>& InSelectedNodes)`
- L61 _private prototype_ `void HandleThisGraphModified( const FEdGraphEditAction &InEditAction );`
- L65 _private prototype_ `void HandleNodeGraphModified( EOptimusGraphNotifyType InNotifyType, UOptimusNodeGraph *InNodeGraph, UObject *InSubject );`
- L71 _private prototype_ `UEdGraphNode* AddGraphNodeFromModelNode(UOptimusNode* InModelNode);`
- L73 _private prototype_ `bool RemoveGraphNode(UEdGraphNode* NodeToRemove, bool bBreakAllLinks = true);`
- L75 _private member_ `TObjectPtr<UOptimusNodeGraph> NodeGraph;`
- L77 _private member_ `TSet<UEdGraphNode*> SelectedNodes;`
- L79 _private member_ `TMap<TWeakObjectPtr<UEdGraphNode>, TWeakObjectPtr<UOptimusNode>> GraphNodeToModelNodeMap;`
- L80 _private member_ `TMap<TWeakObjectPtr<UOptimusNode>, TWeakObjectPtr<UEdGraphNode>> ModelNodeToGraphNodeMap;`
- L82 _private member_ `TWeakPtr<FOptimusEditor> WeakEditor;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraphCommands.h` (Private)


#### class `FOptimusEditorGraphCommands`  
`class FOptimusEditorGraphCommands : public TCommands<FOptimusEditorGraphCommands>`  
_L7-27_
- inherits: `TCommands<FOptimusEditorGraphCommands>`
- L11 _public prototype_ `FOptimusEditorGraphCommands();`
- L14 _public prototype_ `void RegisterCommands() override;` — TCommands<> overrides
- L16 _public member_ `TSharedPtr<FUICommandInfo> ConvertToKernelFunction;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> ConvertFromKernelFunction;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> CollapseNodesToFunction;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> CollapseNodesToSubGraph;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ExpandCollapsedNode;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ConvertToFunction;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ConvertToSubGraph;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> FindInDeformer;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraphConnectionDrawingPolicy.h` (Private)


#### class `FOptimusEditorGraphConnectionDrawingPolicy`  
`class FOptimusEditorGraphConnectionDrawingPolicy final : public FConnectionDrawingPolicy`  
_L7-34_
- inherits: `FConnectionDrawingPolicy`
- L11 _public prototype_ `FOptimusEditorGraphConnectionDrawingPolicy( int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj );`
- L20 _public prototype_ `~FOptimusEditorGraphConnectionDrawingPolicy() override = default;`
- L23 _public prototype_ `void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;`
- L24 _public prototype_ `void DetermineLinkGeometry(FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget, UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FArrangedWidget*& StartWidgetGeometry, FArrangedWidget*& EndWidgetGeometry) override;`
- L27 _protected prototype_ `void BuildPinToPinWidgetMap(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries) override;`
- L28 _protected prototype_ `void DrawPinGeometries(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries, FArrangedChildren& ArrangedNodes) override;`
- L31 _private prototype_ `void AddSubPinsToWidgetMap(UEdGraphPin* InPinObj, TSharedPtr<SGraphPin>& InGraphPinWidget);`
- L33 _private member_ `UEdGraph* Graph;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraphNode.h` (Private)


#### class `UOptimusEditorGraphNode`  
`class UOptimusEditorGraphNode : public UEdGraphNode`  
_L19-103_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- L24 _public member_ `static FName GroupTypeName;`
- L26 _public prototype_ `void Construct(UOptimusNode* InNode);`
- L28 _public prototype_ `UOptimusNodePin* FindModelPinFromGraphPin(const UEdGraphPin* InGraphPin) const;`
- L29 _public prototype_ `UEdGraphPin* FindGraphPinFromModelPin(const UOptimusNodePin* InModelPin) const;`
- L33 _public prototype_ `void SynchronizeGraphPinNameWithModelPin(const UOptimusNodePin* InModelPin);` — Synchronize the stored name/value/type on the graph pin with the value stored on the node. If the pin has sub-pins, the value update is done recursively.
- L34 _public prototype_ `void SynchronizeGraphPinValueWithModelPin(const UOptimusNodePin* InModelPin);`
- L35 _public prototype_ `void SynchronizeGraphPinTypeWithModelPin(const UOptimusNodePin* InModelPin);`
- L36 _public prototype_ `void SynchronizeGraphPinExpansionWithModelPin(const UOptimusNodePin* InModelPin);`
- L38 _public prototype_ `void SyncGraphNodeNameWithModelNodeName();`
- L39 _public prototype_ `void SyncDiagnosticStateWithModelNode();`
- L41 _public function_ `FOptimusNodeTitleDirtied& OnNodeTitleDirtied()`
- L43 _public function_ `FOptimusNodePinsChanged& OnNodePinsChanged()`
- L44 _public function_ `FOptimusNodePinExpansionChanged& OnNodePinExpansionChanged()`
- L47 _public prototype_ `bool CanDuplicateNode() const override;` — UEdGraphNode overrides
- L48 _public prototype_ `bool CanUserDeleteNode() const override;`
- L49 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L50 _public prototype_ `void GetNodeContextMenuActions(UToolMenu* InMenu, UGraphNodeContextMenuContext* InContext) const override;`
- L51 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L52 _public prototype_ `FText GetTooltipText() const override;`
- L56 _public member_ `TObjectPtr<UOptimusNode> ModelNode = nullptr;` — `UPROPERTY()` — FIXME: Move to private and add accessor function.
- L62 _protected function_ `const TArray<UOptimusNodePin*>& GetTopLevelInputPins() const`
- L63 _protected function_ `const TArray<UOptimusNodePin*>& GetTopLevelOutputPins() const`
- L66 _protected prototype_ `bool ModelPinAdded( const UOptimusNodePin* InModelPin );` — Called when a model pin is added after the node creation
- L71 _protected prototype_ `bool ModelPinRemoved( const UOptimusNodePin* InModelPin );` — Called when a model pin is being removed
- L76 _protected prototype_ `bool ModelPinMoved( const UOptimusNodePin* InModelPin );` — Called after a model pin has been moved
- L81 _private prototype_ `void UpdateTopLevelPins();`
- L83 _private prototype_ `bool CreateGraphPinFromModelPin( const UOptimusNodePin* InModelPin, EEdGraphPinDirection InDirection, UEdGraphPin* InParentPin = nullptr);`
- L88 _private prototype_ `void RemoveGraphSubPins( UEdGraphPin *InParentPin );`
- L92 _private member_ `TMap<FName, UOptimusNodePin*> PathToModelPinMap;`
- L93 _private member_ `TMap<FName, UEdGraphPin*> PathToGraphPinMap;`
- L97 _private member_ `TArray<UOptimusNodePin*> TopLevelInputPins;` — These need to be always-living arrays because of the way STreeView works. See SOptimusEditorGraphNode for usage.
- L98 _private member_ `TArray<UOptimusNodePin*> TopLevelOutputPins;`
- L100 _private member_ `FOptimusNodeTitleDirtied NodeTitleDirtied;`
- L101 _private member_ `FOptimusNodePinsChanged NodePinsChanged;`
- L102 _private member_ `FOptimusNodePinExpansionChanged NodePinExpansionChanged;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE(FOptimusNodeTitleDirtied);`
- L14 _prototype_ `DECLARE_DELEGATE(FOptimusNodeTitleDirtied);`
- L15 _delegate_ `DECLARE_DELEGATE(FOptimusNodePinsChanged);`
- L15 _prototype_ `DECLARE_DELEGATE(FOptimusNodePinsChanged);`
- L16 _delegate_ `DECLARE_DELEGATE(FOptimusNodePinExpansionChanged);`
- L16 _prototype_ `DECLARE_DELEGATE(FOptimusNodePinExpansionChanged);`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraphNodeFactory.h` (Private)


#### class `FOptimusEditorGraphNodeFactory`  
`class FOptimusEditorGraphNodeFactory : public FGraphPanelNodeFactory`  
_L7-10_
- inherits: `FGraphPanelNodeFactory`
- L9 _private prototype_ `virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* InNode) const override;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraphNode_Comment.h` (Private)


#### class `UOptimusEditorGraphNode_Comment`  
`class UOptimusEditorGraphNode_Comment : public UEdGraphNode_Comment`  
_L15-33_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode_Comment`
- L20 _public prototype_ `void Construct(UOptimusNode_Comment* InCommentNode);`
- L21 _public prototype_ `void OnModelNodePropertyChanged(UOptimusNode_Comment* InCommentNode);`
- L23 _public prototype_ `void OnPositionChanged();`
- L25 _public prototype_ `void ResizeNode(const FVector2f& NewSize) override;`
- L26 _public prototype_ `void PostPlacedNewNode() override;`
- L28 _public function_ `FOptimusCommentNodeSizeChanged& GetOnSizeChanged()`
- L29 _public function_ `FOptimusCommentNodePositionChanged& GetOnPositionChanged()`
- L31 _private member_ `FOptimusCommentNodeSizeChanged OnSizeChangedDelegate;`
- L32 _private member_ `FOptimusCommentNodePositionChanged OnPositionChangedDelegate;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE(FOptimusCommentNodeSizeChanged);`
- L11 _prototype_ `DECLARE_DELEGATE(FOptimusCommentNodeSizeChanged);`
- L12 _delegate_ `DECLARE_DELEGATE(FOptimusCommentNodePositionChanged);`
- L12 _prototype_ `DECLARE_DELEGATE(FOptimusCommentNodePositionChanged);`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraphPinFactory.h` (Private)


#### class `FOptimusEditorGraphPinFactory`  
`class FOptimusEditorGraphPinFactory : public FGraphPanelPinFactory`  
_L8-14_
- inherits: `FGraphPanelPinFactory`
- L13 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;` — FGraphPanelPinFactory interface

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraphSchema.h` (Private)


#### class `UOptimusEditorGraphSchema`  
`class UOptimusEditorGraphSchema : public UEdGraphSchema`  
_L17-54_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L22 _public member_ `static const FName GraphName_OptimusDeformer;`
- L24 _public prototype_ `UOptimusEditorGraphSchema();`
- L26 _public prototype_ `void GetGraphActions( FGraphActionListBuilderBase& IoActionBuilder, const UEdGraphPin *InFromPin, const UEdGraph* InGraph) const;`
- L32 _public prototype_ `static FEdGraphPinType GetPinTypeFromDataType(FOptimusDataTypeHandle InDataType);`
- L33 _public prototype_ `static const FSlateBrush *GetIconFromPinType(const FEdGraphPinType& InPinType);`
- L34 _public prototype_ `static FLinearColor GetColorFromPinType(const FEdGraphPinType& InPinType);`
- L37 _public prototype_ `FText GetPinDisplayName(const UEdGraphPin* Pin) const override;` — UEdGraphSchema overrides
- L38 _public prototype_ `bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L39 _public prototype_ `const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L40 _public prototype_ `void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L41 _public prototype_ `void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L42 _public prototype_ `FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L43 _public prototype_ `void GetGraphContextActions(FGraphContextMenuBuilder& IoContextMenuBuilder) const override;`
- L44 _public prototype_ `bool SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* Node) const override;`
- L46 _public prototype_ `void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L48 _public prototype_ `void TrySetDefaultValue(UEdGraphPin& Pin, const FString& NewDefaultValue, bool bMarkAsModified = true) const override;`
- L50 _public prototype_ `FLinearColor GetPinTypeColor(const FEdGraphPinType& InPinType) const override;`
- L53 _public function_ `bool ShouldAlwaysPurgeOnModification() const override` — Don't re-create the entire graph on node add/remove.

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorGraphSchemaActions.h` (Private)


#### enum `EOptimusSchemaItemGroup`  
`enum class EOptimusSchemaItemGroup`  
_L24-31_
- L26 _public enumerator_ `InvalidGroup = 0`
- L27 _public enumerator_ `Graphs`
- L28 _public enumerator_ `Bindings`
- L29 _public enumerator_ `Variables`
- L30 _public enumerator_ `Resources`

#### struct `FOptimusGraphSchemaAction_NewNode`  
`struct FOptimusGraphSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L36-52_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a new Optimus node to the graph
- L45 _public member_ `TSubclassOf<UOptimusNode> NodeClass;` — `UPROPERTY()`
- L47 _public function_ `static FName StaticGetTypeId()`
- L48 _public function_ `FName GetTypeId() const override`
- L51 _public prototype_ `UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction overrides

#### struct `FOptimusGraphSchemaAction_NewConstantValueNode`  
`struct FOptimusGraphSchemaAction_NewConstantValueNode : public FEdGraphSchemaAction`  
_L55-71_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L64 _public member_ `FOptimusDataTypeRef DataType;` — `UPROPERTY()`
- L66 _public function_ `static FName StaticGetTypeId()`
- L67 _public function_ `FName GetTypeId() const override`
- L70 _public prototype_ `UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;` — FEdGraphSchemaAction overrides

#### struct `FOptimusGraphSchemaAction_NewDataInterfaceNode`  
`struct FOptimusGraphSchemaAction_NewDataInterfaceNode : public FEdGraphSchemaAction`  
_L74-90_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L83 _public member_ `TSubclassOf<UOptimusComputeDataInterface> DataInterfaceClass;` — `UPROPERTY()`
- L85 _public function_ `static FName StaticGetTypeId()`
- L86 _public function_ `FName GetTypeId() const override`
- L89 _public prototype_ `UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bInSelectNewNode = true) override;` — FEdGraphSchemaAction overrides

#### struct `FOptimusGraphSchemaAction_NewLoopTerminalNodes`  
`struct FOptimusGraphSchemaAction_NewLoopTerminalNodes : public FEdGraphSchemaAction`  
_L94-106_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L101 _public function_ `static FName StaticGetTypeId()`
- L102 _public function_ `FName GetTypeId() const override`
- L105 _public prototype_ `UEdGraphNode* PerformAction(class UEdGraph* InParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bInSelectNewNode = true) override;` — FEdGraphSchemaAction overrides

#### struct `FOptimusGraphSchemaAction_NewCommentNode`  
`struct FOptimusGraphSchemaAction_NewCommentNode : public FEdGraphSchemaAction`  
_L109-122_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L116 _public function_ `static FName StaticGetTypeId()`
- L117 _public function_ `FName GetTypeId() const override`
- L121 _public prototype_ `UEdGraphNode* PerformAction(class UEdGraph* InParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bInSelectNewNode = true) override;`

#### struct `FOptimusGraphSchemaAction_NewFunctionReferenceNode`  
`struct FOptimusGraphSchemaAction_NewFunctionReferenceNode: public FEdGraphSchemaAction`  
_L125-142_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L133 _public member_ `TSoftObjectPtr<UOptimusDeformer> AssetPath;`
- L135 _public member_ `FGuid FunctionGraphGuid;`
- L137 _public function_ `static FName StaticGetTypeId()`
- L138 _public function_ `FName GetTypeId() const override`
- L141 _public prototype_ `UEdGraphNode* PerformAction(class UEdGraph* InParentGraph, UEdGraphPin* InFromPin, const FVector2f& InLocation, bool bInSelectNewNode = true) override;` — FEdGraphSchemaAction overrides

#### struct `FOptimusSchemaAction_Graph`  
`struct FOptimusSchemaAction_Graph : public FEdGraphSchemaAction`  
_L146-170_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Reference to a UOptimusNodeGraph.
- L151 _public function_ `static FName StaticGetTypeId()`
- L156 _public function_ `FName GetTypeId() const override`
- L158 _public member_ `FString GraphPath;`
- L160 _public member_ `EOptimusNodeGraphType GraphType;`
- L162 _public prototype_ `FOptimusSchemaAction_Graph() = default;`
- L164 _public prototype_ `FOptimusSchemaAction_Graph( UOptimusNodeGraph* InGraph, const FText& InCategory = FText::GetEmpty());`
- L169 _public function_ `bool IsParentable() const override` — FEdGraphSchemaAction overrides

#### struct `FOptimusSchemaAction_Binding`  
`struct FOptimusSchemaAction_Binding : public FEdGraphSchemaAction`  
_L175-193_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Reference to a UOptimusComponentSourceBinding.
- L179 _public function_ `static FName StaticGetTypeId()`
- L184 _public function_ `FName GetTypeId() const override`
- L186 _public member_ `FName BindingName;`
- L188 _public prototype_ `FOptimusSchemaAction_Binding() = default;`
- L190 _public prototype_ `FOptimusSchemaAction_Binding( UOptimusComponentSourceBinding* InBinding );`
- L192 _public function_ `bool IsParentable() const override` — FEdGraphSchemaAction overrides

#### struct `FOptimusSchemaAction_Resource`  
`struct FOptimusSchemaAction_Resource : public FEdGraphSchemaAction`  
_L198-217_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Reference to a UOptimusResourceDescription.
- L202 _public function_ `static FName StaticGetTypeId()`
- L207 _public function_ `FName GetTypeId() const override`
- L209 _public member_ `FName ResourceName;`
- L211 _public prototype_ `FOptimusSchemaAction_Resource() = default;`
- L213 _public prototype_ `FOptimusSchemaAction_Resource( UOptimusResourceDescription* InResource );`
- L216 _public function_ `bool IsParentable() const override` — FEdGraphSchemaAction overrides

#### struct `FOptimusSchemaAction_Variable`  
`struct FOptimusSchemaAction_Variable : public FEdGraphSchemaAction`  
_L222-241_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Reference to a UOptimusVariableDescription.
- L226 _public function_ `static FName StaticGetTypeId()`
- L231 _public function_ `FName GetTypeId() const override`
- L233 _public member_ `FName VariableName;`
- L235 _public prototype_ `FOptimusSchemaAction_Variable() = default;`
- L237 _public prototype_ `FOptimusSchemaAction_Variable( UOptimusVariableDescription* InVariable );`
- L240 _public function_ `bool IsParentable() const override` — FEdGraphSchemaAction overrides

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorHelpers.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace OptimusEditor`
- L16 _prototype_ `UOptimusNode* GetModelNodeFromGraphPin(const UEdGraphPin* InGraphPin);` (scope `OptimusEditor`)
- L18 _prototype_ `UOptimusNodePin* GetModelPinFromGraphPin(const UEdGraphPin* InGraphPin);` (scope `OptimusEditor`)
- L20 _prototype_ `UOptimusNode* FindModelNodeFromGraphNode(const UEdGraphNode* InGraphNode);` (scope `OptimusEditor`)
- L22 _prototype_ `FName GetAdderPinName(EEdGraphPinDirection InDirection);` (scope `OptimusEditor`)
- L24 _prototype_ `FText GetAdderPinFriendlyName(EEdGraphPinDirection InDirection);` (scope `OptimusEditor`)
- L26 _prototype_ `FName GetAdderPinCategoryName();` (scope `OptimusEditor`)
- L28 _prototype_ `bool IsAdderPin(const UEdGraphPin* InGraphPin);` (scope `OptimusEditor`)
- L30 _prototype_ `bool IsAdderPinType(const FEdGraphPinType& InPinType);` (scope `OptimusEditor`)
- L32 _prototype_ `UOptimusNode* CreateCommentNode(UOptimusEditorGraph* InGraph, const FVector2D& InPosition);` (scope `OptimusEditor`)

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorMode.h` (Private)


#### class `FOptimusEditorMode`  
`class FOptimusEditorMode : public FApplicationMode`  
_L12-29_
- inherits: `FApplicationMode`
- L15 _public member_ `static FName ModeId;`
- L17 _public prototype_ `FOptimusEditorMode(TSharedRef<FOptimusEditor> InEditorApp);`
- L20 _public prototype_ `void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode overrides
- L23 _protected prototype_ `static TSharedRef<FTabManager::FLayout> CreatePaneLayout();`
- L25 _protected member_ `FWorkflowAllowedTabSet TabFactories;`
- L28 _private member_ `TWeakPtr<FOptimusEditor> EditorPtr;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorModule.h` (Private)


#### class `FOptimusEditorModule`  
`class FOptimusEditorModule : public IOptimusEditorModule`  
_L12-49_
- inherits: `IOptimusEditorModule`
- L15 _public prototype_ `FOptimusEditorModule();`
- L18 _public prototype_ `void StartupModule() override;` — IModuleInterface implementations
- L19 _public prototype_ `void ShutdownModule() override;`
- L22 _public prototype_ `TSharedRef<IOptimusEditor> CreateEditor( const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UOptimusDeformer* DeformerObject ) override;` — IOptimusEditorModule implementations
- L28 _public prototype_ `FOptimusEditorClipboard& GetClipboard() const override;`
- L31 _public prototype_ `virtual void PreChange(const UUserDefinedStruct* Changed, FStructureEditorUtils::EStructureEditorChangeInfo ChangedType) override;` — FStructureEditorUtils::INotifyOnStructChanged overrides to react to user defined struct member changes
- L32 _public prototype_ `virtual void PostChange(const UUserDefinedStruct* Changed, FStructureEditorUtils::EStructureEditorChangeInfo ChangedType) override;`
- L35 _private prototype_ `void RegisterPropertyCustomizations();`
- L36 _private prototype_ `void UnregisterPropertyCustomizations();`
- L38 _private member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;`
- L40 _private member_ `TSharedPtr<FOptimusEditorGraphNodeFactory> GraphNodeFactory;`
- L41 _private member_ `TSharedPtr<FOptimusEditorGraphPinFactory> GraphPinFactory;`
- L43 _private member_ `TArray<FName> CustomizedProperties;`
- L44 _private member_ `TArray<FName> CustomizedClasses;`
- L46 _private member_ `TSharedRef<FOptimusEditorClipboard> Clipboard;`
- L48 _private member_ `int32 UserDefinedStructsPendingPostChange = 0;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorStyle.h` (Private)


#### class `FOptimusEditorStyle`  
`class FOptimusEditorStyle : public FSlateStyleSet`  
_L8-22_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `static FOptimusEditorStyle& Get();`
- L17 _protected prototype_ `static void Register();`
- L18 _protected prototype_ `static void Unregister();`
- L21 _private prototype_ `FOptimusEditorStyle();`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusEditorTabSummoners.h` (Private)


#### struct `FOptimusEditorNodePaletteTabSummoner`  
`struct FOptimusEditorNodePaletteTabSummoner : public FWorkflowTabFactory`  
_L9-20_
- inherits: `FWorkflowTabFactory`
- L12 _public member_ `static const FName TabId;`
- L14 _public prototype_ `explicit FOptimusEditorNodePaletteTabSummoner(TSharedRef<FOptimusEditor> InEditorApp);`
- L16 _public prototype_ `TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L19 _protected member_ `TWeakPtr<FOptimusEditor> EditorPtr;`

#### struct `FOptimusEditorExplorerTabSummoner`  
`struct FOptimusEditorExplorerTabSummoner : public FWorkflowTabFactory`  
_L23-34_
- inherits: `FWorkflowTabFactory`
- L26 _public member_ `static const FName TabId;`
- L28 _public prototype_ `explicit FOptimusEditorExplorerTabSummoner(TSharedRef<FOptimusEditor> InEditorApp);`
- L30 _public prototype_ `TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L33 _protected member_ `TWeakPtr<FOptimusEditor> EditorPtr;`

#### struct `FOptimusEditorGraphTabSummoner`  
`struct FOptimusEditorGraphTabSummoner : public FWorkflowTabFactory`  
_L37-48_
- inherits: `FWorkflowTabFactory`
- L40 _public member_ `static const FName TabId;`
- L42 _public prototype_ `explicit FOptimusEditorGraphTabSummoner(TSharedRef<FOptimusEditor> InEditorApp);`
- L44 _public prototype_ `TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L47 _protected member_ `TWeakPtr<FOptimusEditor> EditorPtr;`

#### struct `FOptimusEditorFindTabSummoner`  
`struct FOptimusEditorFindTabSummoner : public FWorkflowTabFactory`  
_L51-62_
- inherits: `FWorkflowTabFactory`
- L54 _public member_ `static const FName TabId;`
- L56 _public prototype_ `explicit FOptimusEditorFindTabSummoner(TSharedRef<FOptimusEditor> InEditorApp);`
- L58 _public prototype_ `TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L61 _protected member_ `TWeakPtr<FOptimusEditor> EditorPtr;`

#### struct `FOptimusEditorCompilerOutputTabSummoner`  
`struct FOptimusEditorCompilerOutputTabSummoner : public FWorkflowTabFactory`  
_L66-77_
- inherits: `FWorkflowTabFactory`
- L69 _public member_ `static const FName TabId;`
- L71 _public prototype_ `explicit FOptimusEditorCompilerOutputTabSummoner(TSharedRef<FOptimusEditor> InEditorApp);`
- L73 _public prototype_ `TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L76 _protected member_ `TWeakPtr<FOptimusEditor> EditorPtr;`

#### struct `FOptimusEditorShaderTextEditorTabSummoner`  
`struct FOptimusEditorShaderTextEditorTabSummoner : public FWorkflowTabFactory`  
_L81-93_
- inherits: `FWorkflowTabFactory`
- L84 _public member_ `static const FName TabId;`
- L86 _public prototype_ `explicit FOptimusEditorShaderTextEditorTabSummoner(TSharedRef<FOptimusEditor> InEditorApp);`
- L89 _public prototype_ `virtual TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& SpawnArgs, TWeakPtr<FTabManager> WeakTabManager) const override;` — Callback function for spawning the tab
- L92 _protected member_ `TWeakPtr<FOptimusEditor> EditorPtr;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusHLSLSyntaxHighlighter.h` (Private)


#### class `FOptimusHLSLSyntaxHighlighter`  
`class FOptimusHLSLSyntaxHighlighter : public FHLSLSyntaxHighlighterMarshaller`  
_L16-37_
- inherits: `FHLSLSyntaxHighlighterMarshaller`
- desc: Get/set the raw text to/from a text layout, and also inject syntax highlighting for our rich-text markup
- L20 _public prototype_ `static TSharedRef<FOptimusHLSLSyntaxHighlighter> Create(const FSyntaxTextStyle& InSyntaxTextStyle = GetSyntaxTextStyle());`
- L21 _public prototype_ `static FSyntaxTextStyle GetSyntaxTextStyle();`
- L23 _public prototype_ `void SetCompilerMessages(const TArray<FOptimusCompilerDiagnostic> &InCompilerMessages);`
- L27 _protected prototype_ `FOptimusHLSLSyntaxHighlighter(TSharedPtr<ISyntaxTokenizer> InTokenizer, const FSyntaxTextStyle& InSyntaxTextStyle);`
- L29 _protected prototype_ `virtual void ParseTokens(const FString& SourceString, FTextLayout& TargetTextLayout, TArray<ISyntaxTokenizer::FTokenizedLine> TokenizedLines) override;`
- L30 _protected prototype_ `virtual FTextLayout::FNewLineData ProcessTokenizedLine(const ISyntaxTokenizer::FTokenizedLine& TokenizedLine, const int32& LineNumber, const FString& SourceString, EParseState& CurrentParseState) override;`
- L32 _protected member_ `TMultiMap<int32 , FOptimusCompilerDiagnostic> CompilerMessages;`
- L36 _private member_ `TArray<FTextLineHighlight> LineHighlightsToAdd;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusNameValidator.h` (Private)


#### class `FOptimusNameValidator`  
`class FOptimusNameValidator : public INameValidatorInterface`  
_L11-33_
- inherits: `INameValidatorInterface`
- L15 _public prototype_ `FOptimusNameValidator(const UObject *InOuter, const UClass* InObjectClass, FName InExistingName);`
- L20 _public function_ `static const TCHAR *InvalidCharacters()` — Disallowed characters in a graph/variable/buffer name. Period is disallowed since it's a path separator (like with BP), and slash is also disallowed since we use it for constructing name paths for undo, space is also not allowed since it complicates unique name checking
- L23 _public prototype_ `EValidatorResult IsValid(const FName& InName, bool bInOriginal = false) override;` — INameValidatorInterface overrides
- L25 _public prototype_ `EValidatorResult IsValid(const FString& InName, bool bInOriginal = false) override;`
- L29 _private member_ `TSet<FName> Names;` — Existing names to validate against.
- L32 _private member_ `FName ExistingName;` — The current name.

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusSourceAssetActions.h` (Private)


#### class `FOptimusSourceAssetActions`  
`class FOptimusSourceAssetActions : public FAssetTypeActions_Base`  
_L8-25_
- inherits: `FAssetTypeActions_Base`
- L12 _public prototype_ `FOptimusSourceAssetActions(EAssetTypeCategories::Type InAssetCategoryBit = EAssetTypeCategories::Animation);`
- L16 _protected prototype_ `FText GetName() const override;`
- L17 _protected prototype_ `FColor GetTypeColor() const override;`
- L18 _protected prototype_ `UClass* GetSupportedClass() const override;`
- L19 _protected prototype_ `uint32 GetCategories() override;`
- L20 _protected prototype_ `const TArray<FText>& GetSubMenus() const override;`
- L24 _private member_ `EAssetTypeCategories::Type AssetCategoryBit;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/OptimusSourceFactory.h` (Private)


#### class `UOptimusSourceFactory`  
`class UOptimusSourceFactory : public UFactory`  
_L9-24_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L14 _public prototype_ `UOptimusSourceFactory();`
- L16 _public prototype_ `virtual UObject* FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn ) override;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusDataTypeSelector.h` (Private)


#### class `SOptimusDataTypeSelector`  
`class SOptimusDataTypeSelector : public SCompoundWidget`  
_L27-90_
- inherits: `SCompoundWidget`
- L37 _public function_ `SLATE_BEGIN_ARGS( SOptimusDataTypeSelector ) : _ViewType(EViewType::IconAndText), _bViewOnly(false), _UsageMask(EOptimusDataTypeUsageFlags::None), _Font(FAppStyle::GetFontStyle(TEXT("NormalFont")))`
- L52 _public prototype_ `void Construct(const FArguments &InArgs);`
- L56 _private prototype_ `const FSlateBrush* GetTypeIconImage(FOptimusDataTypeHandle InDataType) const;`
- L57 _private function_ `const FSlateBrush* GetTypeIconImage() const`
- L59 _private prototype_ `FSlateColor GetTypeIconColor(FOptimusDataTypeHandle InDataType) const;`
- L60 _private function_ `FSlateColor GetTypeIconColor() const`
- L61 _private prototype_ `FText GetTypeDescription(FOptimusDataTypeHandle InDataType) const;`
- L62 _private function_ `FText GetTypeDescription() const`
- L63 _private prototype_ `FText GetTypeTooltip(FOptimusDataTypeHandle InDataType) const;`
- L64 _private prototype_ `FText GetTypeTooltip() const;`
- L66 _private prototype_ `TSharedRef<SWidget> GetMenuContent();`
- L68 _private prototype_ `TSharedRef<ITableRow> GenerateTypeListRow(FOptimusDataTypeHandle InItem, const TSharedRef<STableViewBase>& InOwnerList);`
- L69 _private prototype_ `void OnTypeSelectionChanged(FOptimusDataTypeHandle InSelection, ESelectInfo::Type InSelectInfo);`
- L71 _private prototype_ `void OnFilterTextChanged(const FText& InNewText);`
- L72 _private prototype_ `void OnFilterTextCommitted(const FText& InNewText, ETextCommit::Type InCommitInfo);`
- L74 _private prototype_ `TArray<FOptimusDataTypeHandle> GetFilteredItems(const TArray<FOptimusDataTypeHandle> &InItems, const FText &InSearchText) const;`
- L76 _private member_ `TAttribute<FOptimusDataTypeHandle> CurrentDataType;`
- L77 _private member_ `EViewType ViewType;`
- L78 _private member_ `bool bViewOnly;`
- L79 _private member_ `TAttribute<EOptimusDataTypeUsageFlags> UsageMask;`
- L80 _private member_ `FOnDataTypeChanged OnDataTypeChanged;`
- L82 _private member_ `TSharedPtr<SComboButton> TypeComboButton;`
- L83 _private member_ `TSharedPtr<SMenuOwner> MenuContent;`
- L84 _private member_ `TSharedPtr<SDataTypeListView> TypeListView;`
- L85 _private member_ `TSharedPtr<SSearchBox> FilterBox;`
- L86 _private member_ `FText FilterText;`
- L88 _private member_ `TArray<FOptimusDataTypeHandle> AllDataTypeItems;`
- L89 _private member_ `TArray<FOptimusDataTypeHandle> ViewDataTypeItems;`

#### enum `SOptimusDataTypeSelector::EViewType`  
`enum class EViewType`  
_L31-35_
- L33 _public enumerator_ `IconOnly`
- L34 _public enumerator_ `IconAndText`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDataTypeChanged, FOptimusDataTypeHandle) using SDataTypeListView = SListView<FOptimusDataTypeHandle>;`
- L24 _typedef_ `using SDataTypeListView = SListView<FOptimusDataTypeHandle>;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusEditorGraphExplorer.h` (Private)


#### class `FOptimusEditorGraphExplorerCommands`  
`class FOptimusEditorGraphExplorerCommands : public TCommands<FOptimusEditorGraphExplorerCommands>`  
_L24-40_
- inherits: `TCommands<FOptimusEditorGraphExplorerCommands>`
- L27 _public prototype_ `FOptimusEditorGraphExplorerCommands();`
- L29 _public member_ `TSharedPtr<FUICommandInfo> OpenGraph;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> CreateSetupGraph;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> CreateTriggerGraph;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> CreateBinding;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> CreateResource;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> CreateVariable;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> DeleteEntry;`
- L39 _public prototype_ `void RegisterCommands() override;`

#### class `SOptimusEditorGraphExplorer`  
`class SOptimusEditorGraphExplorer : public SCompoundWidget`  
_L42-146_
- inherits: `SCompoundWidget`
- L46 _public function_ `SLATE_BEGIN_ARGS(SOptimusEditorGraphExplorer)`
- L47 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FOptimusEditor> InOptimusEditor);`
- L50 _public prototype_ `~SOptimusEditorGraphExplorer();`
- L53 _public prototype_ `void Refresh();` — Refresh the graph action menu.
- L54 _public function_ `void SetFocusedGraph(UOptimusEditorGraph* InEditorGraph)`
- L58 _public prototype_ `void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L61 _private prototype_ `void RegisterCommands();`
- L62 _private prototype_ `void CreateWidgets();`
- L64 _private prototype_ `TSharedRef<SWidget> CreateAddNewMenuWidget();`
- L66 _private prototype_ `void BuildAddNewMenu(FMenuBuilder& MenuBuilder);`
- L68 _private prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData);`
- L69 _private prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);`
- L70 _private prototype_ `void CollectChildGraphActions(FGraphActionListBuilderBase& OutAllActions, const UOptimusNodeGraph* InParentGraph, const FText& InParentGraphCategory);`
- L71 _private prototype_ `void CollectStaticSections(TArray<int32>& StaticSectionIDs);`
- L73 _private prototype_ `FReply OnActionDragged(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, const FPointerEvent& MouseEvent);`
- L74 _private prototype_ `FReply OnCategoryDragged(const FText& InCategory, const FPointerEvent& MouseEvent);`
- L75 _private prototype_ `void OnActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, ESelectInfo::Type InSelectionType);`
- L77 _private prototype_ `void OnActionDoubleClicked(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions);`
- L78 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L79 _private prototype_ `void OnCategoryNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit, TWeakPtr<struct FGraphActionNode> InAction);`
- L80 _private prototype_ `bool CanRequestRenameOnActionNode(TWeakPtr<FGraphActionNode> InSelectedNode) const;`
- L81 _private prototype_ `bool CanRenameAction(TSharedPtr<FEdGraphSchemaAction> InAction) const;`
- L84 _private prototype_ `FText OnGetSectionTitle(int32 InSectionID);`
- L85 _private prototype_ `TSharedRef<SWidget> OnGetSectionWidget(TSharedRef<SWidget> RowWidget, int32 InSectionID);`
- L87 _private prototype_ `FReply OnAddButtonClickedOnSection(int32 InSectionID);`
- L88 _private prototype_ `bool CanAddNewElementToSection(int32 InSectionID) const;`
- L91 _private prototype_ `void OnToggleShowEmptySections();` — Support functions for view options for Show Empty Sections
- L92 _private prototype_ `bool IsShowingEmptySections() const;`
- L95 _private function_ `template<typename SchemaActionType> SchemaActionType* SelectionAsType() const`
- L100 _private prototype_ `TSharedPtr<FEdGraphSchemaAction> GetFirstSelectedAction( FName InTypeName ) const;`
- L105 _private prototype_ `void OnOpenGraph();` — Command functions
- L106 _private prototype_ `bool CanOpenGraph();`
- L108 _private prototype_ `void OnCreateSetupGraph();`
- L109 _private prototype_ `bool CanCreateSetupGraph();`
- L111 _private prototype_ `void OnCreateTriggerGraph();`
- L112 _private prototype_ `bool CanCreateTriggerGraph();`
- L114 _private prototype_ `void OnCreateBinding(const UOptimusComponentSource* InComponentSource);`
- L115 _private prototype_ `bool CanCreateBinding();`
- L117 _private prototype_ `void OnCreateResource();`
- L118 _private prototype_ `bool CanCreateResource();`
- L120 _private prototype_ `void OnCreateVariable();`
- L121 _private prototype_ `bool CanCreateVariable();`
- L123 _private prototype_ `void OnDeleteEntry();`
- L124 _private prototype_ `bool CanDeleteEntry();`
- L126 _private prototype_ `void OnRenameEntry();`
- L127 _private prototype_ `bool CanRenameEntry();`
- L129 _private prototype_ `bool IsEditingMode() const;`
- L131 _private prototype_ `bool SelectionHasContextMenu() const;`
- L133 _private member_ `TWeakPtr<FOptimusEditor> OptimusEditor;`
- L136 _private member_ `UOptimusEditorGraph *EditorGraph;` — FIXME: Get from the editor?
- L138 _private member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L140 _private member_ `TSharedPtr<SSearchBox> FilterBox;`
- L143 _private member_ `bool bNeedsRefresh;` — On demand refresh requests prior to tick.
- L145 _private member_ `bool bShowEmptySections = true;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusEditorGraphExplorerActions.h` (Private)


#### class `FOptimusEditorGraphDragAction_Binding`  
`class FOptimusEditorGraphDragAction_Binding : public FGraphSchemaActionDragDropAction`  
_L15-36_
- inherits: `FGraphSchemaActionDragDropAction`
- L19 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FOptimusEditorGraphDragAction_Binding, FGraphSchemaActionDragDropAction) static TSharedRef<FOptimusEditorGraphDragAction_Binding> New( TSharedPtr<FEdGraphSchemaAction> InAction, UOptimusComponentSourceBinding *InBinding );`
- L27 _public prototype_ `FReply DroppedOnPanel( const TSharedRef<SWidget>& InPanel, const FVector2f& InScreenPosition, const FVector2f& InGraphPosition, UEdGraph& InGraph ) override;` — FGraphEditorDragDropAction overrides
- L35 _private member_ `TWeakObjectPtr<UOptimusComponentSourceBinding> WeakBinding;`

#### class `FOptimusEditorGraphDragAction_Variable`  
`class FOptimusEditorGraphDragAction_Variable : public FGraphSchemaActionDragDropAction`  
_L39-71_
- inherits: `FGraphSchemaActionDragDropAction`
- L43 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FOptimusEditorGraphDragAction_Variable, FGraphSchemaActionDragDropAction) static TSharedRef<FOptimusEditorGraphDragAction_Variable> New( TSharedPtr<FEdGraphSchemaAction> InAction, UOptimusVariableDescription *InVariableDesc );`
- L51 _public prototype_ `void HoverTargetChanged() override;` — FGraphEditorDragDropAction overrides
- L52 _public prototype_ `FReply DroppedOnPanel( const TSharedRef<SWidget>& InPanel, const FVector2f& InScreenPosition, const FVector2f& InGraphPosition, UEdGraph& InGraph ) override;`
- L61 _protected prototype_ `void GetDefaultStatusSymbol( const FSlateBrush*& OutPrimaryBrush, FSlateColor& OutIconColor, FSlateBrush const*& OutSecondaryBrush, FSlateColor& OutSecondaryColor ) const override;`
- L70 _private member_ `TWeakObjectPtr<UOptimusVariableDescription> WeakVariableDesc;`

#### class `FOptimusEditorGraphDragAction_Resource`  
`class FOptimusEditorGraphDragAction_Resource : public FGraphSchemaActionDragDropAction`  
_L75-104_
- inherits: `FGraphSchemaActionDragDropAction`
- L79 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FOptimusEditorGraphDragAction_Resource, FGraphSchemaActionDragDropAction) static TSharedRef<FOptimusEditorGraphDragAction_Resource> New( TSharedPtr<FEdGraphSchemaAction> InAction, UOptimusResourceDescription* InResourceDesc);`
- L86 _public prototype_ `void HoverTargetChanged() override;` — FGraphEditorDragDropAction overrides
- L87 _public prototype_ `FReply DroppedOnPanel( const TSharedRef<SWidget>& InPanel, const FVector2f& InScreenPosition, const FVector2f& InGraphPosition, UEdGraph& InGraph) override;`
- L95 _protected prototype_ `void GetDefaultStatusSymbol( const FSlateBrush*& OutPrimaryBrush, FSlateColor& OutIconColor, FSlateBrush const*& OutSecondaryBrush, FSlateColor& OutSecondaryColor) const override;`
- L103 _private member_ `TWeakObjectPtr<UOptimusResourceDescription> WeakResourceDesc;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusEditorGraphExplorerItem.h` (Private)


#### class `SOptimusEditorGraphExplorerItem`  
`class SOptimusEditorGraphExplorerItem : public SGraphPaletteItem`  
_L15-45_
- inherits: `SGraphPaletteItem`
- L19 _public function_ `SLATE_BEGIN_ARGS(SOptimusEditorGraphExplorerItem)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData, TWeakPtr<FOptimusEditor> InOptimusEditor);`
- L29 _public prototype_ `TSharedRef<SWidget> CreateIconWidget(FCreateWidgetForActionData* const InCreateData, TAttribute<bool> bInIsReadOnly);`
- L36 _public prototype_ `TSharedRef<SWidget> CreateTextSlotWidget(FCreateWidgetForActionData* const InCreateData, TAttribute<bool> bIsReadOnly) override;` — SGraphPaletteItem overrides
- L37 _public prototype_ `FText GetDisplayText() const override;`
- L38 _public prototype_ `bool OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage) override;`
- L39 _public prototype_ `void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit) override;`
- L43 _private member_ `FNodeTextCache MenuDescriptionCache;`
- L44 _private member_ `TWeakPtr<FOptimusEditor> OptimusEditor;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusEditorGraphNode.h` (Private)


#### class `SOptimusEditorGraphNode`  
`class SOptimusEditorGraphNode : public SGraphNode`  
_L16-90_
- inherits: `SGraphNode`
- L20 _public function_ `SLATE_BEGIN_ARGS(SOptimusEditorGraphNode) : _GraphNode(nullptr)`
- L23 _public prototype_ `SLATE_ARGUMENT(UOptimusEditorGraphNode*, GraphNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void EndUserInteraction() const override;` — SGraphNode overrides
- L30 _public prototype_ `void CreateStandardPinWidget(UEdGraphPin* CurPin) override;`
- L31 _public prototype_ `void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L32 _public prototype_ `TSharedPtr<SGraphPin> GetHoveredPin(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const override;`
- L33 _public prototype_ `void RefreshErrorInfo() override;`
- L34 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L35 _public prototype_ `void UpdateGraphNode() override;`
- L38 _private prototype_ `UOptimusEditorGraphNode *GetEditorGraphNode() const;`
- L39 _private prototype_ `UOptimusNode* GetModelNode() const;`
- L40 _private prototype_ `TSharedPtr<SGraphPin> GetPinWidget(UEdGraphPin* InGraphPin);`
- L41 _private prototype_ `void UpdatePinIcon(const TSharedRef<SGraphPin>& PinToAdd) const;`
- L43 _private prototype_ `void UpdatePinExpansionFromGraphPins();`
- L44 _private prototype_ `void SyncPinWidgetsWithGraphPins();`
- L46 _private prototype_ `EVisibility GetTitleVisibility() const;`
- L49 _private prototype_ `TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;` — SGraphNode protected overrides
- L52 _private prototype_ `EVisibility GetInputTreeVisibility() const;` — STreeView helper functions
- L53 _private prototype_ `EVisibility GetOutputTreeVisibility() const;`
- L54 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(UOptimusNodePin* InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L55 _private prototype_ `TSharedPtr<IToolTip> MakePinToolTip(UOptimusNodePin* InItem) const;`
- L56 _private prototype_ `void HandleGetChildrenForTree(UOptimusNodePin* InItem, TArray<UOptimusNodePin*>& OutChildren);`
- L57 _private prototype_ `void HandleExpansionChanged(UOptimusNodePin* InItem, bool bExpanded);`
- L59 _private prototype_ `FText GetPinLabel(TWeakPtr<SGraphPin> InWeakGraphPin) const;`
- L61 _private member_ `TSharedPtr<SNodeTitle> NodeTitle;`
- L64 _private member_ `TSharedPtr<STreeView<UOptimusNodePin*>> InputTree;` — Collapsible input pins
- L67 _private member_ `TSharedPtr<STreeView<UOptimusNodePin*>> OutputTree;` — Collapsible input pins
- L69 _private member_ `TSharedPtr<SScrollBar> TreeScrollBar;`
- L71 _private member_ `TMap<const UEdGraphPin*, TWeakPtr<SGraphPin>> PinWidgetMap;`
- L75 _private member_ `TArray<TSharedRef<SWidget>> HoverWidgetLabels;` — A paired list of widgets to map from labels to pin to support labels participating in pin hovering.
- L76 _private member_ `TArray<TSharedRef<SGraphPin>> HoverWidgetPins;`
- L80 _private member_ `TMap<const UEdGraphPin *, TSharedRef<SGraphPin>> PinsToKeep;` — Pins to keep after calling SyncPinWidgetsWithGraphPins. We recycle these pins in CreateStandardPinWidget.
- L85 _private member_ `TSet<UEdGraphPin *> PinsToDelete;` — Delayed pin deletion. To deal with the fact that pin deletion cannot occur until we have re-generated the pin list. SOptimusEditorGraphNode has already relinquished them but we still have a pointer to them in our pin widget.
- L89 _private member_ `int32 CachedErrorType = -1;` — Cached error type to compare against the UEdGraphNode to see if we need to refresh our error state.

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusEditorGraphNode_Comment.h` (Private)


#### class `SOptimusEditorGraphNode_Comment`  
`class SOptimusEditorGraphNode_Comment : public SGraphNodeComment`  
_L12-27_
- inherits: `SGraphNodeComment`
- L16 _public function_ `SLATE_BEGIN_ARGS(SOptimusEditorGraphNode_Comment)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UOptimusEditorGraphNode_Comment* InGraphNode);`
- L21 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L22 _public prototype_ `void EndUserInteraction() const override;`
- L24 _private prototype_ `void OnSizeChanged();`
- L25 _private prototype_ `void OnPositionChanged();`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusGraphTitleBar.h` (Private)


#### class `SOptimusGraphTitleBar`  
`class SOptimusGraphTitleBar : public SCompoundWidget`  
_L18-57_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SOptimusGraphTitleBar)`
- L23 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FOptimusEditor>, OptimusEditor) SLATE_EVENT(FOptimusOpenGraphEvent, OnGraphCrumbClickedEvent) SLATE_END_ARGS() ~SOptimusGraphTitleBar() override;`
- L29 _public prototype_ `void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `void Refresh();` — Forcibly refresh the title bar
- L35 _private prototype_ `void BuildBreadcrumbTrail(UOptimusNodeGraph* InGraph);`
- L37 _private prototype_ `const FSlateBrush* GetGraphTypeIcon() const;`
- L39 _private prototype_ `static FText GetGraphTitle(const UOptimusNodeGraph* InGraph);`
- L41 _private prototype_ `void OnBreadcrumbClicked(UOptimusNodeGraph* const& InModelGraph) const;`
- L43 _private prototype_ `FText GetDeformerTitle() const;`
- L44 _private prototype_ `EVisibility IsDeformerTitleVisible() const;`
- L47 _private member_ `TWeakPtr<FOptimusEditor> OptimusEditor;` — The owning graph editor widget.
- L50 _private member_ `TSharedPtr<SScrollBox> BreadcrumbTrailScrollBox;` — The scroll box that kicks in if the trail exceeds the widget's visible box.
- L53 _private member_ `TSharedPtr< SBreadcrumbTrail<UOptimusNodeGraph*> > BreadcrumbTrail;` — Breadcrumb trail widget
- L56 _private member_ `FOptimusOpenGraphEvent OnGraphCrumbClickedEvent;` — Callback for switching graph levels.

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusNodePalette.h` (Private)


#### class `SOptimusNodePaletteItem`  
`class SOptimusNodePaletteItem : public SGraphPaletteItem`  
_L15-28_
- inherits: `SGraphPaletteItem`
- desc: Widget for displaying a single item
- L18 _public function_ `SLATE_BEGIN_ARGS(SOptimusNodePaletteItem)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData);`
- L25 _private prototype_ `TSharedRef<SWidget> CreateHotkeyDisplayWidget(const FSlateFontInfo& NameFont, const TSharedPtr<const FInputChord> HotkeyChord);` — Create the hotkey display widget
- L27 _private prototype_ `virtual FText GetItemTooltip() const override;`

#### class `SOptimusNodePalette`  
`class SOptimusNodePalette : public SGraphPalette`  
_L32-61_
- inherits: `SGraphPalette`
- L37 _public function_ `SLATE_BEGIN_ARGS(SOptimusNodePalette)`
- L38 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FOptimusEditor> InEditor);`
- L43 _public prototype_ `void Refresh();` — Forcibly refresh
- L47 _protected prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData) override;` — SGraphPalette overrides
- L48 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;`
- L52 _private prototype_ `void GraphCollectionNotify(EOptimusGlobalNotifyType InType, UObject* InObject);`
- L55 _private member_ `TWeakPtr<FOptimusEditor> OwningEditor;` — The owning editor
- L57 _private member_ `TArray< TSharedPtr<FString> > CategoryNames;`
- L60 _private member_ `TSharedPtr<STextComboBox> CategoryComboBox;` — Combo box used to select category

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusShaderTextDocumentTab.h` (Private)


#### class `SOptimusShaderTextDocumentTab`  
`class SOptimusShaderTextDocumentTab : public SCompoundWidget`  
_L21-56_
- inherits: `SCompoundWidget`
- L24 _public prototype_ `SOptimusShaderTextDocumentTab();`
- L27 _public function_ `SLATE_BEGIN_ARGS(SOptimusShaderTextDocumentTab)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UObject* InShaderTextProviderObject, TWeakPtr<FOptimusEditor> InEditor, TSharedRef<SDockTab> InDocumentHostTab);`
- L33 _private prototype_ `TSharedRef<SWidget> ConstructNonExpandableHeaderWidget(const SExpandableArea::FArguments& InArgs) const;`
- L34 _private prototype_ `SSplitter::ESizeRule GetDeclarationsSectionSizeRule() const;`
- L36 _private prototype_ `bool HasValidShaderTextProvider() const;`
- L37 _private prototype_ `IOptimusShaderTextProvider* GetProviderInterface() const;`
- L38 _private prototype_ `FText GetDeclarationsAsText() const;`
- L39 _private prototype_ `FText GetShaderTextAsText() const;`
- L40 _private prototype_ `void OnShaderTextChanged(const FText& InText) const;`
- L41 _private prototype_ `void OnDiagnosticsUpdated() const;`
- L42 _private prototype_ `bool IsShaderTextReadOnly() const;`
- L44 _private member_ `TSharedRef<FOptimusHLSLSyntaxHighlighter> SyntaxHighlighterDeclarations;`
- L45 _private member_ `TSharedRef<FOptimusHLSLSyntaxHighlighter> SyntaxHighlighterShaderText;`
- L47 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L49 _private member_ `TWeakObjectPtr<UObject> ShaderTextProviderObject;`
- L50 _private member_ `TWeakPtr<FOptimusEditor> OwningEditor;`
- L52 _private member_ `TSharedPtr<SExpandableArea> DeclarationsExpandableArea;`
- L54 _private member_ `TSharedPtr<SOptimusShaderTextDocumentTextBox> DeclarationsTextBox;` — ptr needed for text search
- L55 _private member_ `TSharedPtr<SOptimusShaderTextDocumentTextBox> ShaderTextTextBox;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusShaderTextDocumentTextBox.h` (Private)


#### class `FOptimusShaderTextEditorDocumentTextBoxCommands`  
`class FOptimusShaderTextEditorDocumentTextBoxCommands : public TCommands<FOptimusShaderTextEditorDocumentTextBoxCommands>`  
_L18-32_
- inherits: `TCommands<FOptimusShaderTextEditorDocumentTextBoxCommands>`
- L22 _public prototype_ `FOptimusShaderTextEditorDocumentTextBoxCommands();`
- L25 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> overrides
- L27 _public member_ `TSharedPtr<FUICommandInfo> Search;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> NextOccurrence;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> PreviousOccurrence;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ToggleComment;`

#### class `SOptimusShaderTextDocumentTextBox`  
`class SOptimusShaderTextDocumentTextBox : public SCompoundWidget`  
_L34-107_
- inherits: `SCompoundWidget`
- L38 _public prototype_ `SOptimusShaderTextDocumentTextBox();`
- L41 _public function_ `SLATE_BEGIN_ARGS(SOptimusShaderTextDocumentTextBox)`
- L43 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FText, SearchText) SLATE_ARGUMENT(TSharedPtr< ITextLayoutMarshaller >, Marshaller) SLATE_ATTRIBUTE(bool, IsReadOnly) SLATE_EVENT(FOnTextChanged, OnTextChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The initial text that will appear in the widget.
- L61 _public prototype_ `void Refresh() const;`
- L67 _private prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — use Preview Key Down so that the commands related to this tab is given the priority
- L69 _private prototype_ `void RegisterCommands();`
- L71 _private prototype_ `bool HandleEscape();`
- L73 _private prototype_ `void ShowSearchBar();`
- L74 _private prototype_ `bool HideSearchBar();`
- L76 _private prototype_ `void OnTriggerSearch();`
- L77 _private prototype_ `void OnSearchTextChanged(const FText& InTextToSearch);`
- L78 _private prototype_ `void OnSearchTextCommitted(const FText& InTextToSearch, ETextCommit::Type InCommitType);`
- L79 _private prototype_ `TOptional<SSearchBox::FSearchResultData> GetSearchResultData() const;`
- L80 _private prototype_ `void OnSearchResultNavigationButtonClicked(SSearchBox::SearchDirection InDirection);`
- L81 _private prototype_ `void OnGoToNextOccurrence();`
- L82 _private prototype_ `void OnGoToPreviousOccurrence();`
- L84 _private prototype_ `FReply OnTextKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InCharacterEvent) const;`
- L87 _private prototype_ `void OnToggleComment() const;`
- L89 _private prototype_ `FReply OnTextKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) const;`
- L93 _private prototype_ `void HandleAutoIndent() const;` — Figure out if we need to auto-indent.
- L95 _private member_ `TSharedPtr<SVerticalBox> TabBody;`
- L97 _private member_ `TSharedPtr<SMultiLineEditableText> Text;`
- L99 _private member_ `bool bIsSearchBarHidden;`
- L100 _private member_ `TSharedPtr<SOptimusShaderTextSearchWidget> SearchBar;`
- L104 _private member_ `TSharedRef<FUICommandList> TopLevelCommandList;` — Top level command list is processed during preview key down such that its commands are given the priority
- L106 _private member_ `TSharedRef<FUICommandList> TextCommandList;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusShaderTextEditor.h` (Private)


#### class `SOptimusShaderTextEditor`  
`class SOptimusShaderTextEditor : public SCompoundWidget`  
_L17-45_
- inherits: `SCompoundWidget`
- L20 _public member_ `static const FName DocumentTabId;`
- L21 _public prototype_ `static TArray<FName> GetAllTabIds();`
- L22 _public prototype_ `static void OnHostTabClosed(TSharedRef<SDockTab> InShaderTextEditorHostTab);`
- L26 _public function_ `SLATE_BEGIN_ARGS(SOptimusShaderTextEditor)`
- L27 _public prototype_ `SLATE_END_ARGS()`
- L34 _public member_ `TWeakPtr<FOptimusEditor> OwningEditor;` — The owning editor
- L37 _private prototype_ `void HandleSelectedNodesChanged(const TArray<TWeakObjectPtr<UObject>>& InSelectedObjects) const;`
- L38 _private prototype_ `void HandleGraphNotified(EOptimusGraphNotifyType InNotifyType, UOptimusNodeGraph* InGraph, UObject* InSubject) const;`
- L40 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L42 _private member_ `TSharedPtr<FDocumentTracker> DocumentTracker;`
- L44 _private member_ `FOptimusEditor::FOnGraphNotified OnGraphNotifyDelegate;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Private/Widgets/SOptimusShaderTextSearchWidget.h` (Private)


#### class `SOptimusShaderTextSearchWidget`  
`class SOptimusShaderTextSearchWidget : public SCompoundWidget`  
_L13-50_
- inherits: `SCompoundWidget`
- L16 _public prototype_ `SOptimusShaderTextSearchWidget();`
- L19 _public function_ `SLATE_BEGIN_ARGS(SOptimusShaderTextSearchWidget)`
- L22 _public prototype_ `SLATE_EVENT(FOnTextChanged, OnTextChanged ) SLATE_EVENT( FOnTextCommitted, OnTextCommitted ) SLATE_EVENT(SSearchBox::FOnSearch, OnResultNavigationButtonClicked ) SLATE_ATTRIBUTE(TOptional<SSearchBox::FSearchResultData>, SearchResultData ) SLATE_EVENT(FOnKeyDown, OnKeyDownHandler) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Invoked whenever the text changes
- L40 _public prototype_ `void FocusSearchBox() const;`
- L42 _public prototype_ `void TriggerSearch(const FText& InNewSearchText) const;`
- L44 _public prototype_ `void ClearSearchText();`
- L47 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L48 _private member_ `FText LastSearchedText;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Public/FindInDeformer.h` (Public)


#### class `FFindInDeformerResult`  
`class FFindInDeformerResult : public FFindInGraphResult`  
_L12-21_
- inherits: `FFindInGraphResult`
- desc: Item that matched the search results
- L16 _public prototype_ `FFindInDeformerResult(const FFindInGraphResult::FCreateParams& InCreateParams);`
- L19 _public prototype_ `virtual void JumpToNode(TWeakPtr<FAssetEditorToolkit> AssetEditorToolkit, const UEdGraphNode* InNode) const override;`

#### class `SFindInDeformer`  
`class SFindInDeformer : public SFindInGraph`  
_L25-35_
- inherits: `SFindInGraph`
- desc: Widget for searching for items that are part of a Deformer Graph
- L31 _protected prototype_ `virtual TSharedPtr<FFindInGraphResult> MakeSearchResult(const FFindInGraphResult::FCreateParams& InParams) override;`
- L32 _protected prototype_ `virtual const UEdGraph* GetGraph() override;`
- L33 _protected prototype_ `virtual bool MatchTokensInNode(const UEdGraphNode* Node, const TArray<FString>& Tokens) override;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Public/IOptimusEditor.h` (Public)


#### class `IOptimusEditor`  
`class IOptimusEditor : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit`  
_L8-16_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit`
- L15 _public prototype_ `virtual ~IOptimusEditor() override = default;`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Public/IOptimusEditorModule.h` (Public)


#### class `IOptimusEditorModule`  
`class IOptimusEditorModule : public IModuleInterface`  
_L17-38_
- inherits: `IModuleInterface,FStructureEditorUtils::INotifyOnStructChanged`
- L24 _public function_ `static IOptimusEditorModule& Get()`
- L34 _public prototype_ `virtual TSharedRef<IOptimusEditor> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UOptimusDeformer* DeformerObject) = 0;` — Creates an instance of a Control Rig editor. @param Mode				Mode that this editor should operate in @param InitToolkitHost	When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param DeformerObject	The deformer object to start editing. @return Interface to the new Optimus Deformer editor
- L37 _public prototype_ `virtual FOptimusEditorClipboard& GetClipboard() const = 0;` — Returns the shared clipboard for the deformer graph.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOptimusEditor, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOptimusEditor, Log, All);`

### `Plugins/Animation/DeformerGraph/Source/OptimusEditor/Public/OptimusEditorClipboard.h` (Public)


#### class `FOptimusEditorClipboard`  
`class FOptimusEditorClipboard`  
_L17-35_
- L20 _public prototype_ `static void SetClipboardFromNodes(const TArray<UOptimusNode*>& InNodes);`
- L23 _public prototype_ `static UOptimusNodeGraph* GetGraphFromClipboardContent( UPackage* InTargetPackage );` — Creates a self-contained
- L27 _public prototype_ `static bool HasValidClipboardContent();`
- L30 _private prototype_ `static bool CanCreateObjectsFromText(const TCHAR* InBuffer);`
- L32 _private prototype_ `static bool ProcessObjectBuffer(UPackage* InPackage, UObject* InRootOuter, const TCHAR* InBuffer);`
- L33 _private prototype_ `static bool CanCreateClass(const UClass* ObjectClass);`
- L34 _private prototype_ `static bool ProcessPostCreateObject(UObject* InRootOuter, UObject* InNewObject);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API OPTIMUSEDITOR_API`
