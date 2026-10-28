# Plugins / MetasoundEditor

- module root: `Plugins/Runtime/Metasound/Source/MetasoundEditor`
- headers: 47; symbols: 2512
- symbol kinds: class=120, delegate=22, enum=8, enumerator=28, function=197, macro=17, member=561, namespace=83, prototype=1385, struct=71, typedef=15, variable=5
- PrivateDependencyModuleNames: AppFramework, AssetTools, AudioExtensions, AudioSynesthesia, ContentBrowser, ContentBrowserAssetDataSource, ContentBrowserData, EditorWidgets, Kismet, KismetWidgets, MetasoundEngine, MetasoundFrontend, MetasoundGenerator, MetasoundGraphCore, MetasoundStandardNodes, Projects, SignalProcessing, SubobjectEditor, ToolMenus, ToolWidgets, WaveTable, WaveTableEditor
- PublicDependencyModuleNames: ApplicationCore, AssetDefinition, AudioAnalyzer, AudioEditor, AudioMixer, AudioWidgets, ClassViewer, ContentBrowser, Core, CoreUObject, DetailCustomizations, EditorFramework, EditorStyle, EditorSubsystem, Engine, GraphEditor, InputCore, ModelViewViewModel, PropertyEditor, RenderCore, Slate, SlateCore, StructUtilsEditor, UMG, UnrealEd

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetaSoundGraphPanelPinFactory.h` (Private)


#### class `Metasound::Editor::FMetaSoundGraphPanelPinFactory`  
`class FMetaSoundGraphPanelPinFactory : public IMetaSoundGraphPanelPinFactory`  
_L9-72_
- inherits: `IMetaSoundGraphPanelPinFactory`
- L12 _public prototype_ `FMetaSoundGraphPanelPinFactory();`
- L13 _public prototype_ `virtual ~FMetaSoundGraphPanelPinFactory() = default;`
- L15 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override;`
- L17 _public prototype_ `virtual const FEdGraphPinType* FindPinType(FName InDataTypeName) const override;`
- L21 _public prototype_ `static TSharedRef<FMetaSoundGraphPanelPinFactory> GetChecked();` — Convenience getter for returning concrete private implementation from owning editor module and casting accordingly.
- L23 _public prototype_ `virtual bool GetCustomPinIcons(UEdGraphPin* InPin, const FSlateBrush*& OutConnectedIcon, const FSlateBrush*& OutDisconnectedIcon) const override;`
- L24 _public prototype_ `virtual bool GetCustomPinIcons(FName InDataType, const FSlateBrush*& OutConnectedIcon, const FSlateBrush*& OutDisconnectedIcon) const override;`
- L26 _public prototype_ `virtual FLinearColor GetPinColor(const FEdGraphPinType& InPinType) const override;`
- L28 _public prototype_ `virtual void RegisterCategoryPin(FName InPinCategory, FOnCreateMetaSoundPinWidget InDelegate) override;`
- L29 _public prototype_ `virtual void UnregisterCategoryPin(FName InPinCategory) override;`
- L31 _public prototype_ `virtual void RegisterDataTypePin(FName InDataTypeName, FOnCreateMetaSoundPinWidget InDelegate) override;`
- L32 _public prototype_ `virtual void UnregisterDataTypePin(FName InDataTypeName) override;`
- L34 _public prototype_ `virtual void RegisterPin(FName InDataTypeName, const FGraphPinParams& Params = FGraphPinParams { }) override;`
- L35 _public prototype_ `virtual void UnregisterPin(FName InDataTypeName) override;`
- L38 _public member_ `static const FName PinCategoryAudio;` — Pin category constants
- L39 _public member_ `static const FName PinCategoryBoolean;`
- L40 _public member_ `static const FName PinCategoryFloat;`
- L41 _public member_ `static const FName PinCategoryInt32;`
- L42 _public member_ `static const FName PinCategoryObject;`
- L43 _public member_ `static const FName PinCategoryString;`
- L44 _public member_ `static const FName PinCategoryTime;`
- L45 _public member_ `static const FName PinCategoryTimeArray;`
- L46 _public member_ `static const FName PinCategoryTrigger;`
- L47 _public member_ `static const FName PinCategoryWaveTable;`
- L50 _public prototype_ `static bool IsInternalMetaSoundPinCategory(FName InPinCategoryName);` — Returns whether the given name is an internally-managed MetaSound pin category
- L53 _private prototype_ `void RegisterCorePinTypes();`
- L56 _private member_ `TMap<FName, FOnCreateMetaSoundPinWidget> CategoryToWidgetDelegateMap;` — Map from pin category to widget creation delegate
- L59 _private member_ `TMap<FName, FOnCreateMetaSoundPinWidget> DataTypeToWidgetDelegateMap;` — Map from data type name to widget creation delegate (higher priority than category)
- L68 _private member_ `TMap<FName, FPinConfiguration> PinTypes;`
- L71 _private member_ `TMap<FName, FLinearColor> CustomCategoryColors;` — Cached custom pin category colors for O(1) lookup in GetPinColor

#### struct `Metasound::Editor::FMetaSoundGraphPanelPinFactory::FPinConfiguration`  
`struct FPinConfiguration`  
_L61-67_
- L63 _public member_ `FEdGraphPinType PinType;`
- L64 _public member_ `TOptional<FLinearColor> PinColor;`
- L65 _public member_ `const FSlateBrush* PinConnectedIcon = nullptr;`
- L66 _public member_ `const FSlateBrush* PinDisconnectedIcon = nullptr;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L7 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundAssetDefinitions.h` (Private)


#### class `UAssetDefinition_MetaSoundPatch`  
`class UAssetDefinition_MetaSoundPatch : public UAssetDefinition_SoundAssetBase`  
_L12-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SoundAssetBase`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L24 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L25 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L28 _public prototype_ `virtual TArray<FToolMenuSection*> RebuildSoundContextMenuSections() const override;`

#### class `UAssetDefinition_MetaSoundSource`  
`class UAssetDefinition_MetaSoundSource : public UAssetDefinition_SoundBase`  
_L32-65_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_SoundBase`
- L38 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L39 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L40 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L41 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L42 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L44 _public prototype_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& InAssetData) const override;`
- L45 _public prototype_ `virtual bool GetThumbnailActionOverlay(const FAssetData& InAssetData, FAssetActionThumbnailOverlayInfo& OutActionOverlayInfo) const override;`
- L46 _public prototype_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L47 _public prototype_ `virtual void GetAssetActionButtonExtensions(const FAssetData& InAssetData, TArray<FAssetButtonActionExtension>& OutExtensions) const override;`
- L49 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L50 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L53 _public prototype_ `virtual TArray<FToolMenuSection*> RebuildSoundContextMenuSections() const override;`
- L56 _public prototype_ `static void ExecutePlaySound(const FToolMenuContext& InContext);` — Menu Extension statics
- L57 _public prototype_ `static void ExecuteStopSound(const FToolMenuContext& InContext);`
- L58 _public prototype_ `static bool CanExecutePlayCommand(const FToolMenuContext& InContext);`
- L59 _public prototype_ `static ECheckBoxState IsActionCheckedMute(const FToolMenuContext& InContext);`
- L60 _public prototype_ `static ECheckBoxState IsActionCheckedSolo(const FToolMenuContext& InContext);`
- L61 _public prototype_ `static void ExecuteMuteSound(const FToolMenuContext& InContext);`
- L62 _public prototype_ `static void ExecuteSoloSound(const FToolMenuContext& InContext);`
- L63 _public prototype_ `static bool CanExecuteMuteCommand(const FToolMenuContext& InContext);`
- L64 _public prototype_ `static bool CanExecuteSoloCommand(const FToolMenuContext& InContext);`

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundDetailCustomization.h` (Private)


#### class `Metasound::Editor::FMetaSoundDetailCustomizationBase`  
`class FMetaSoundDetailCustomizationBase : public IDetailCustomization`  
_L26-42_
- inherits: `IDetailCustomization`
- L29 _public prototype_ `virtual ~FMetaSoundDetailCustomizationBase() = default;`
- L32 _public prototype_ `bool IsGraphEditable() const;` — `UE_DEPRECATED(5.8, "Use virtual IsEditable instead")`
- L33 _public function_ `bool IsFormatEditable() const`
- L35 _public prototype_ `virtual bool IsEditable() const;`
- L38 _protected prototype_ `UObject* GetMetaSound() const;`
- L39 _protected prototype_ `void InitBuilder(UObject& MetaSound);`
- L41 _protected member_ `TStrongObjectPtr<UMetaSoundBuilderBase> Builder;`

#### class `Metasound::Editor::FMetasoundDetailCustomization`  
`class FMetasoundDetailCustomization : public FMetaSoundDetailCustomizationBase`  
_L44-63_
- inherits: `FMetaSoundDetailCustomizationBase`
- L47 _public prototype_ `FMetasoundDetailCustomization(FName InDocumentPropertyName);`
- L48 _public prototype_ `virtual ~FMetasoundDetailCustomization() = default;`
- L51 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L55 _private prototype_ `FName GetTemplatePropertyPath() const;`
- L56 _private prototype_ `FName GetInterfaceVersionsPropertyPath() const;`
- L57 _private prototype_ `FName GetRootClassPropertyPath() const;`
- L58 _private prototype_ `FName GetMetadataPropertyPath() const;`
- L60 _private member_ `FName DocumentPropertyName;`
- L61 _private member_ `TArray<TSharedPtr<int64>> OutputFormatOptions;`
- L62 _private member_ `TSharedPtr<SComboBox<TSharedPtr<int64>>> OutputFormatCombo;`

#### class `Metasound::Editor::FMetasoundPagesDetailCustomization`  
`class FMetasoundPagesDetailCustomization : public FMetaSoundDetailCustomizationBase`  
_L65-110_
- inherits: `FMetaSoundDetailCustomizationBase`
- L68 _public prototype_ `FMetasoundPagesDetailCustomization();`
- L71 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — FMetaSoundDetailCustomizationBase interface
- L72 _public prototype_ `virtual bool IsEditable() const override;`
- L76 _private prototype_ `const FMetasoundFrontendDocument& GetConstDocumentChecked() const;`
- L77 _private prototype_ `UObject& GetMetaSoundChecked() const;`
- L78 _private prototype_ `bool IsBuilderValid() const;`
- L79 _private prototype_ `void RebuildImplemented();`
- L80 _private prototype_ `void RefreshView();`
- L81 _private prototype_ `void UpdateItemNames();`
- L83 _private member_ `TArray<TSharedPtr<FString>> AddableItems;`
- L85 _private member_ `TSet<FName> ImplementedNames;`
- L86 _private member_ `TSharedPtr<SSearchableComboBox> ComboBox;`
- L87 _private member_ `TSharedPtr<SVerticalBox> EntryWidgets;`
- L88 _private member_ `FName BuildPageName;`
- L109 _private member_ `TSharedPtr<FPageListener> PageListener;`

#### class `Metasound::Editor::FMetasoundPagesDetailCustomization::FPageListener`  
`class FPageListener : public Frontend::IDocumentBuilderTransactionListener`  
_L90-108_
- inherits: `Frontend::IDocumentBuilderTransactionListener`
- L92 _private member_ `TWeakPtr<FMetasoundPagesDetailCustomization> Parent;`
- L95 _public prototype_ `FPageListener() = default;`
- L96 _public function_ `FPageListener(TSharedRef<FMetasoundPagesDetailCustomization> InParent) : Parent(InParent)`
- L101 _public prototype_ `virtual ~FPageListener() = default;`
- L104 _private prototype_ `virtual void OnBuilderReloaded(Frontend::FDocumentModifyDelegates& OutDelegates) override;`
- L105 _private prototype_ `void OnPageAdded(const Frontend::FDocumentMutatePageArgs& Args);`
- L106 _private prototype_ `void OnPageSet(const Frontend::FDocumentMutatePageArgs& Args);`
- L107 _private prototype_ `void OnRemovingPage(const Frontend::FDocumentMutatePageArgs& Args);`

#### class `Metasound::Editor::FMetasoundInterfacesDetailCustomization`  
`class FMetasoundInterfacesDetailCustomization : public FMetaSoundDetailCustomizationBase`  
_L112-128_
- inherits: `FMetaSoundDetailCustomizationBase`
- L116 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L119 _public prototype_ `virtual bool IsEditable() const override;`
- L122 _private prototype_ `void UpdateInterfaceNames();`
- L124 _private member_ `TArray<TSharedPtr<FString>> AddableInterfaceNames;`
- L126 _private member_ `TSet<FName> ImplementedInterfaceNames;`
- L127 _private member_ `TSharedPtr<SSearchableComboBox> InterfaceComboBox;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace Editor` (scope `Metasound`)
- L24 _prototype_ `const FName GetMissingPageName(const FGuid& InPageID);` (scope `Metasound::Editor`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundDynamicInterfaceNodeConfigurationCustomization.h` (Private)


#### class `Metasound::Editor::FDynamicInterfaceNodeConfigurationCustomization`  
`class FDynamicInterfaceNodeConfigurationCustomization : public FMetaSoundNodeConfigurationCustomization`  
_L13-47_
- inherits: `FMetaSoundNodeConfigurationCustomization`
- desc: Details customization for FMetaSoundDynamicInterfaceNodeConfiguration. Displays sub-interface instance counts as clamped spinboxes and variant type selections as combo box dropdowns. Sub-interface names and variant names are shown as read-only labels.
- L16 _public prototype_ `FDynamicInterfaceNodeConfigurationCustomization(TSharedPtr<IPropertyHandle> InStructProperty, TWeakObjectPtr<UMetasoundEditorGraphNode> InNode);`
- L19 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildBuilder) override;`
- L26 _public function_ `virtual bool RequiresTick() const override` — Disable tick-based regeneration. The base class (FInstancedStructDataDetails) ticks to detect struct type changes via CachedInstanceTypes, but since this override of GenerateChildContent does not call the base class implementation, CachedInstanceTypes is never set, causing infinite per-frame regeneration. Node configuration type changes are driven by explicit user interaction (spinbox commits, combo selection) rather than external struct type swaps.
- L31 _private prototype_ `bool CacheClassInterfaceDescriptions();` — Look up the FClassInterface from the node registry for the graph node's underlying class.
- L34 _private prototype_ `void SetSubInterfaceCount(FName SubInterfaceName, uint32 NewCount);` — Modify the configuration's TMap and trigger a node interface update.
- L35 _private prototype_ `void SetVariantSelection(FName VariantName, FName NewDataType);`
- L38 _private prototype_ `uint32 GetSubInterfaceCount(FName SubInterfaceName, uint32 InDefault) const;` — Read current value from the configuration's TMap.
- L39 _private prototype_ `FName GetVariantSelection(FName VariantName) const;`
- L42 _private member_ `TArray<FSubInterfaceDescription> SubInterfaceDescriptions;` — Cached descriptions from the FClassInterface.
- L43 _private member_ `TArray<FVariantDescription> VariantDescriptions;`
- L46 _private member_ `TArray<TArray<TSharedPtr<FName>>> VariantOptionArrays;` — Variant option sources for combo boxes (kept alive for SComboBox).

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L7 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditor.h` (Private)


#### class `UMetasoundEditorViewBase`  
`class UMetasoundEditorViewBase : public UObject`  
_L75-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base implementation for editor wrappers that provide edit customizations
- L80 _public function_ `void SetMetasound(UObject* InMetasound)`
- L81 _public function_ `const UObject* GetMetasound() const`
- L82 _public function_ `UObject* GetMetasound()`
- L85 _private member_ `TWeakObjectPtr<UObject> Metasound;`

#### class `UMetasoundInterfacesView`  
`class UMetasoundInterfacesView : public UMetasoundEditorViewBase`  
_L91-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorViewBase`
- desc: Simple class for the interfaces details tab to keep track of its corresponding Metasound

#### class `UMetasoundPagesView`  
`class UMetasoundPagesView : public UMetasoundEditorViewBase`  
_L97-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorViewBase`

#### enum `Metasound::Editor::ENodeSection`  
`enum class ENodeSection : uint8`  
_L115-123_
- desc: Enums to use when grouping the members in the list panel. Enum order dictates visible order.
- L117 _public enumerator_ `None`
- L118 _public enumerator_ `Inputs`
- L119 _public enumerator_ `Outputs`
- L120 _public enumerator_ `Variables`
- L122 _public enumerator_ `COUNT`

#### class `Metasound::Editor::FEditor`  
`class FEditor : public IMetasoundEditor, public FNotifyHook, public FEditorUndoClient, public FTickableEditorObject`  
_L125-704_
- inherits: `IMetasoundEditor,FNotifyHook,FEditorUndoClient,FTickableEditorObject`
- L128 _public member_ `static const FLazyName EditorName;`
- L130 _public prototype_ `FEditor();`
- L131 _public prototype_ `virtual ~FEditor();`
- L133 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L134 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L136 _public prototype_ `TSharedPtr<SGraphEditor> GetGraphEditor() const;`
- L139 _public prototype_ `void InitMetasoundEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);` — Edits the specified Metasound object
- L141 _public prototype_ `UAudioComponent* GetAudioComponent() const;`
- L143 _public prototype_ `const Frontend::FMetaSoundTemplate* GetDocumentTemplate() const;`
- L144 _public prototype_ `FMetaSoundFrontendDocumentBuilder* GetFrontendBuilder() const;`
- L147 _public prototype_ `virtual UObject* GetMetasoundObject() const override;` — IMetasoundEditor interface
- L148 _public prototype_ `virtual void SetSelection(const TArray<UObject*>& SelectedObjects, bool bInvokeTabOnSelectionSet = true) override;`
- L149 _public prototype_ `virtual bool GetBoundsForSelectedNodes(FSlateRect& Rect, float Padding) override;`
- L152 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L153 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L154 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L155 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L156 _public prototype_ `virtual const FSlateBrush* GetDefaultTabIcon() const override;`
- L157 _public prototype_ `virtual FLinearColor GetDefaultTabColor() const override;`
- L160 _public prototype_ `virtual FName GetEditorName() const override;` — IAssetEditorInstance interface
- L162 _public function_ `virtual FString GetDocumentationLink() const override`
- L168 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L169 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L172 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject Interface
- L173 _public prototype_ `virtual TStatId GetStatId() const override;`
- L174 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L176 _public prototype_ `virtual void Play() override;`
- L177 _public prototype_ `virtual void Stop() override;`
- L180 _public prototype_ `static bool IgnoreDocTemplateVisibilitySettings();` — Returns whether or not template visibility settings should be ignored (for debugging/development)
- L183 _public prototype_ `static bool IsLiveAuditionEnabled();` — Returns whether or not live audition is enabled for previewing
- L185 _public prototype_ `virtual bool IsPlaying() const override;`
- L188 _public prototype_ `bool CanPasteNodes();` — Whether pasting the current data on the clipboard to the focused graph is permissible
- L191 _public prototype_ `void DuplicateNodes();` — Duplicates the selected node(s) in the graph
- L194 _public prototype_ `void RefreshDetails();` — Forces all UX pertaining to the root graph's details panel to be refreshed.
- L197 _public prototype_ `void PasteNodes(const FVector2D* InLocation = nullptr);` — Pastes node(s) from the clipboard to the graph
- L198 _public prototype_ `void PasteNodes(const FVector2D* InLocation, const FText& InTransactionText);`
- L201 _public prototype_ `FGraphConnectionManager& GetConnectionManager();` — Returns Graph Connection Manager associated with this editor
- L202 _public prototype_ `const FGraphConnectionManager& GetConnectionManager() const;`
- L205 _public prototype_ `UMetasoundEditorGraphMember* RefreshGraphMemberMenu();` — Forces all UX pertaining to the root graph's interface to be refreshed, returning the first selected member.
- L208 _public prototype_ `void UpdateSelectedNodeClasses();` — Updates selected node classes to highest class found in the MetaSound Class Registry.
- L211 _public prototype_ `bool IsAuditionable() const;` — Whether or not MetaSound can be auditioned
- L214 _public prototype_ `bool IsGraphEditable() const;` — Whether the displayed graph is marked as editable
- L216 _public prototype_ `void ClearSelectionAndSelectNode(UEdGraphNode* Node);`
- L218 _public prototype_ `int32 GetNumNodesSelected() const;`
- L221 _public prototype_ `void CreateAnalyzers(UMetaSoundSource& MetaSoundSource);` — Creates analyzers
- L224 _public prototype_ `void DestroyAnalyzers();` — Destroys analyzers
- L228 _public function_ `template<typename TNodeType = UMetasoundEditorGraphNode> void JumpToNodes(const TArray<TNodeType*>& InNodes)` — Jumps to the given nodes on the graph (templated to support arrays of various MetaSound graph node types)
- L263 _public prototype_ `void SetDelayedRename();`
- L265 _public prototype_ `void SetDroppedObjectsInfo(FDroppedObjectsInfo InInfo);`
- L266 _public prototype_ `const TOptional<FDroppedObjectsInfo>& GetDroppedObjectsInfo() const;`
- L268 _public prototype_ `void ClearDroppedObjectsInfo();`
- L271 _public prototype_ `void ReloadAllDocTemplateTabs();` — Reloads all document template tabs
- L275 _protected prototype_ `bool CanRenameOnActionNode(TWeakPtr<FGraphActionNode> InSelectedNode) const;` — Callbacks for action tree
- L276 _protected prototype_ `bool CanAddNewElementToSection(int32 InSectionID) const;`
- L277 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);`
- L278 _protected prototype_ `void CollectStaticSections(TArray<int32>& StaticSectionIDs);`
- L279 _protected prototype_ `TSharedRef<SWidget> CreateAddButton(int32 InSectionID, FText AddNewText, FName MetaDataTag);`
- L280 _protected prototype_ `FText GetFilterText() const;`
- L281 _protected prototype_ `bool HandleActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName) const;`
- L282 _protected prototype_ `FReply OnActionDragged(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, const FPointerEvent& MouseEvent);`
- L283 _protected prototype_ `void OnMemberActionDoubleClicked(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions);`
- L284 _protected prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);`
- L285 _protected prototype_ `void OnActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, ESelectInfo::Type InSelectionType);`
- L286 _protected prototype_ `FReply OnAddButtonClickedOnSection(int32 InSectionID);`
- L287 _protected prototype_ `TSharedRef<SWidget> OnGetMenuSectionWidget(TSharedRef<SWidget> RowWidget, int32 InSectionID);`
- L288 _protected prototype_ `FText GetSectionTitle(ENodeSection InSection) const;`
- L289 _protected prototype_ `FText OnGetSectionTitle(int32 InSectionID);`
- L290 _protected prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(struct FCreateWidgetForActionData* const InCreateData);`
- L291 _protected prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L294 _protected prototype_ `void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L296 _protected prototype_ `FGraphAppearanceInfo GetGraphAppearance() const;`
- L298 _protected prototype_ `UMetasoundEditorGraph& GetMetaSoundGraphChecked();`
- L299 _protected prototype_ `UMetasoundEditorGraph* GetMetaSoundGraph();`
- L301 _protected prototype_ `FText GetGraphStatusDescription() const;`
- L302 _protected prototype_ `const FSlateIcon& GetPlayIcon() const;`
- L303 _protected prototype_ `const FSlateIcon& GetStopIcon() const;`
- L312 _protected prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);` — Called when a node's title is committed for a rename @param	NewText				New title text @param	CommitInfo			How text was committed @param	NodeBeingChanged	The node being changed
- L315 _protected prototype_ `void DeleteSelected();` — Deletes from the Metasound Menu (i.e. input or output) if in focus, or the currently selected nodes if the graph editor is in focus.
- L317 _protected prototype_ `void DeleteInterfaceItem(TSharedPtr<FMetasoundGraphMemberSchemaAction> ActionToDelete);`
- L320 _protected prototype_ `void DeleteSelectedNodes();` — Delete the currently selected nodes
- L323 _protected prototype_ `void DeleteSelectedInterfaceItems();` — Delete the currently selected interface items
- L326 _protected prototype_ `void CutSelectedNodes();` — Cut the currently selected nodes
- L329 _protected prototype_ `void CopySelectedNodes() const;` — Copy the currently selected nodes
- L332 _protected prototype_ `bool CanDuplicateNodes() const;` — Whether or not the currently selected node(s) can be duplicated
- L335 _protected prototype_ `bool CanDeleteNodes() const;` — Whether the currently selected node(s) can be deleted
- L338 _protected prototype_ `bool CanDeleteInterfaceItems() const;` — Whether the currently selected interface item(s) can be deleted
- L341 _protected prototype_ `bool CanRenameSelectedNodes() const;` — Whether at least one of the currently selected node(s) can be renamed.
- L344 _protected prototype_ `void RenameSelectedNode();` — Rename selected node (currently applies to comments and member nodes).
- L347 _protected prototype_ `bool CanRenameSelectedInterfaceItems() const;` — Whether at least one of the currently selected interface item(s) can be renamed.
- L350 _protected prototype_ `void RenameSelectedInterfaceItem();` — Rename selected interface item.
- L353 _protected prototype_ `bool CanDuplicateSelectedMemberItems() const;` — Whether the currently selected Member item(s) can be duplicated.
- L356 _protected prototype_ `void DuplicateSelectedMemberItems();` — Duplicate selected Member items.
- L359 _protected prototype_ `bool CanCopySelectedMemberItems() const;` — Whether the currently selected Member item(s) can be copied.
- L362 _protected prototype_ `void CopySelectedMemberItems();` — Copy selected Member items.
- L365 _protected prototype_ `bool CanCutSelectedMemberItems() const;` — Whether the currently selected Member item(s) can be cut.
- L368 _protected prototype_ `void CutSelectedMemberItems();` — Cut selected Member items.
- L371 _protected prototype_ `bool CanPasteSelectedMemberItems() const;` — Whether the currently selected Member item(s) can be pasted.
- L374 _protected prototype_ `void CopySelectionAsConfiguratorCodeToClipboard() const;` — Copies the selected nodes, shared connections, and required interfaces to the clipboard as configurator c++
- L377 _protected prototype_ `void PasteSelectedMemberItems();` — Paste selected Member items.
- L380 _protected prototype_ `bool CanJumpToNodesForSelectedInterfaceItem() const;` — Whether there are nodes to jump to for the currently selected interface item.
- L383 _protected prototype_ `void JumpToNodesForSelectedInterfaceItem();` — Jumps to the nodes corresponding to the first valid currently selected interface item.
- L386 _protected prototype_ `void DeleteAllUnusedInSection();` — Delete all unused members from the selected section
- L389 _protected prototype_ `bool CanDeleteUnusedMembers() const;` — Whether the selection is not to a valid member
- L392 _protected prototype_ `void UndoGraphAction();` — Called to undo the last action
- L395 _protected prototype_ `void RedoGraphAction();` — Called to redo the last undone action
- L397 _protected prototype_ `void RefreshEditorContext(UObject& MetaSound);`
- L400 _protected prototype_ `void ShowFindInMetaSound();` — Show and focus the Find in MetaSound tab.
- L403 _protected prototype_ `void FindSelectedNodeInGraph();` — Find selected node from Graph
- L406 _protected prototype_ `void HideUnconnectedPins();` — Hide pins without connection
- L409 _protected prototype_ `void ShowUnconnectedPins();` — Show pins without connection
- L412 _protected prototype_ `bool CanPromoteToInput();` — Checks if pin can be promoted
- L415 _protected prototype_ `void PromoteToInput();` — Promotes pin to graph input
- L418 _protected prototype_ `bool CanPromoteToOutput();` — Checks if pin can be promoted
- L421 _protected prototype_ `void PromoteToOutput();` — Promotes pin to graph output
- L424 _protected prototype_ `bool CanPromoteToVariable();` — Checks if pin can be promoted
- L427 _protected prototype_ `void PromoteToVariable();` — Promotes pin to graph variable
- L430 _protected prototype_ `bool CanPromoteToDeferredVariable();` — Checks if pin can be promoted
- L433 _protected prototype_ `void PromoteToDeferredVariable();` — Promotes pin to graph deferred variable
- L436 _protected prototype_ `bool CanPromoteAllToInputs();` — Checks if node's inputs can be promoted
- L439 _protected prototype_ `void PromoteAllToInputs();` — Promotes node's inputs to unique graph inputs
- L442 _protected prototype_ `bool CanPromoteAllToCommonInputs();` — Checks if node's inputs can be promoted
- L445 _protected prototype_ `void PromoteAllToCommonInputs();` — Promotes node's inputs to shared graph inputs
- L448 _private prototype_ `int32 PromotableSelectedNodes();`
- L451 _private prototype_ `void RebuildUserWidgets( UWorld& World, UAudioWidgetSubsystem& WidgetSubsystem, TSubclassOf<UInterface> InterfaceClass, TFunction<bool(UUserWidget*)>Filter, TFunction<FMetaSoundTemplateWidgetTabInfo(UUserWidget*)>OnTabConstruct, FGuid TargetBlueprintId = FGuid());` — If target BP Id set, only rebuilds the widget associated with that BP.
- L459 _private prototype_ `void RefreshExecVisibility(const FGuid& InPageID) const;`
- L462 _private prototype_ `void RefreshPagesView();` — Forces refresh of pages view.
- L465 _private prototype_ `void RefreshInterfaceView();` — Forces refresh of interfaces view.
- L467 _private prototype_ `void RemoveInvalidSelection();`
- L469 _private prototype_ `void UpdateEnabledTabs();`
- L471 _private prototype_ `void SetPreviewID(uint32 InPreviewID);`
- L473 _private prototype_ `void ExportNodesToText(FString& OutText) const;`
- L475 _private prototype_ `void SyncAuditionState(bool bSetAuditionFocus = true);`
- L478 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface
- L481 _private prototype_ `void CreateInternalWidgets(UObject& MetaSound);` — Creates all internal widgets for the tabs to point at
- L483 _private prototype_ `void RebuildDocTemplateUserWidgets(const FGuid& TargetBlueprintId = FGuid());`
- L487 _private prototype_ `void ChangeDocTemplateWidgetWorld(UWorld* World, EMapChangeType MapChangeType);` — For teardown and regeneration of user document template widget on world change Based on UEditorUtilityWidgetBlueprint::ChangeTabWorld
- L490 _private prototype_ `void OnDocTemplateWidgetBlueprintCompiled(UBlueprint* Blueprint);` — Reload document template widget tab on associated widget blueprint recompile
- L493 _private prototype_ `void ExtendToolbarInternal();` — Builds the toolbar widget for the Metasound editor
- L496 _private prototype_ `void BindGraphCommands();` — Binds new graph commands to delegates
- L498 _private prototype_ `FSlateIcon GetImportStatusImage() const;`
- L500 _private prototype_ `FSlateIcon GetExportStatusImage() const;`
- L503 _private prototype_ `void Import();` — TODO: Move import/export out of editor and into import/export asset actions
- L504 _private prototype_ `void Export();`
- L507 _private prototype_ `void ExecuteNode();` — Toolbar command methods
- L510 _private prototype_ `bool CanExecuteNode() const;` — Whether we can play the current selection of nodes
- L513 _private prototype_ `void TogglePlayback();` — Either play the Metasound or stop currently playing sound
- L516 _private prototype_ `bool CanToggleShowHideGraph() const;` — Whether or not to show the toggle for showing/hiding a graph (i.e. is or is not a MetaSound with a template set)
- L519 _private prototype_ `void ToggleShowHideGraph();` — Toggles showing the graph for the given configured MetaSound
- L522 _private prototype_ `void ExecuteNode(UEdGraphNode* Node);` — Executes specified node (If supported)
- L525 _private prototype_ `void SyncInBrowser();` — Sync the content browser to the current selection of nodes
- L528 _private prototype_ `void ShowConvertFromConfigDialog();` — Shows dialog confirming converting from configured document to make parent MetaSound openly modifiable.
- L531 _private prototype_ `bool ShowPageGraphDetails() const;` — Whether or not page details should be visible/enabled.
- L534 _private prototype_ `TSharedRef<SWidget> CreateAuditionMenuOptions();` — Creates audition menu options
- L537 _private prototype_ `TSharedRef<SWidget> CreateTemplateMenuOptions();` — Creates template menu options
- L540 _private prototype_ `void CreateAuditionPageSubMenuOptions(FMenuBuilder& MenuBuilder);` — Creates page menu options
- L543 _private prototype_ `void CreateTemplateSubMenuOptions(FMenuBuilder& MenuBuilder);` — Creates template menu options
- L546 _private prototype_ `void EditSourceSettings();` — Show the Metasound object's Source settings in the Details panel
- L549 _private prototype_ `void EditMetasoundSettings();` — Show the Metasound object's settings in the Details panel
- L551 _private member_ `TSharedPtr<FTabManager::FStack> GraphCanvasTabStack;`
- L554 _private prototype_ `void AddInput();` — Add an input to the currently selected node
- L557 _private prototype_ `bool CanAddInput() const;` — Whether we can add an input to the currently selected node
- L560 _private prototype_ `void OnCreateComment();` — Create comment node on graph
- L563 _private prototype_ `void CreateGraphEditorWidget(UObject& MetaSound);` — Create new graph editor widget
- L565 _private prototype_ `void EditObjectSettings();`
- L567 _private prototype_ `void NotifyAssetLoadingComplete();`
- L568 _private prototype_ `void NotifyAssetLoadingInProgress(int32 NumProcessing);`
- L569 _private prototype_ `void NotifyDocumentVersioned();`
- L570 _private prototype_ `void NotifyNodePasteFailure_MultipleVariableSetters();`
- L571 _private prototype_ `void NotifyNodePasteFailure_ReferenceLoop();`
- L572 _private prototype_ `void NotifyNodePasteFailure_MultipleOutputs();`
- L574 _private prototype_ `TUniquePtr<FGraphConnectionManager> RebuildConnectionManager(UAudioComponent* PreviewComponent = nullptr) const;`
- L577 _private prototype_ `void UpdatePageInfo(bool bIsPlaying);` — Updates the page info widget.
- L580 _private prototype_ `void UpdateRenderInfo(bool bIsPlaying, float InDeltaTime = 0.0f);` — Updates the render info widget.
- L583 _private member_ `TMap<FName, TWeakPtr<SDockableTab>> SpawnedToolPanels;` — List of open tool panels; used to ensure only one exists at any one time
- L586 _private member_ `TSharedPtr<SGraphEditor> MetasoundGraphEditor;` — New Graph Editor
- L589 _private member_ `TSharedPtr<IDetailsView> MetasoundDetails;` — Details tab
- L592 _private member_ `TSharedPtr<IDetailsView> PagesDetails;` — Pages tab
- L593 _private member_ `TStrongObjectPtr<UMetasoundPagesView> PagesView;`
- L596 _private member_ `TSharedPtr<IDetailsView> InterfacesDetails;` — Interfaces tab
- L597 _private member_ `TStrongObjectPtr<UMetasoundInterfacesView> InterfacesView;`
- L600 _private member_ `TSharedPtr<SGraphActionMenu> GraphMembersMenu;` — Metasound graph members menu
- L603 _private member_ `TSharedPtr<AudioWidgets::FAudioAnalyzerRack> AnalyzerRack;` — Displayed in the analyzer tab for visualizing preview output.
- L606 _private member_ `TSharedPtr<SFindInMetasound> FindWidget;` — Find in MetaSound widget.
- L609 _private member_ `TSharedPtr<SMetasoundPalette> Palette;` — Palette of Node types
- L612 _private member_ `TSharedPtr<SPageStats> PageStatsWidget;` — Widget showing page info regarding page info that overlays the graph tab content
- L615 _private member_ `TSharedPtr<SRenderStats> RenderStatsWidget;` — Widget showing render performance information that overlays the graph
- L626 _private typedef_ `using FBlueprintId = FGuid;`
- L627 _private typedef_ `using FBPIdWidgetDataPair = TPair<FBlueprintId, FUserWidgetData>;`
- L630 _private member_ `TMap<FBlueprintId, FUserWidgetData> DocTemplateWidgetData;` — User defined widget data displayed when editing a document template with user widgets enabled.
- L632 _private member_ `FWorkflowAllowedTabSet DocTemplateTabSet;`
- L649 _private member_ `TUniquePtr<FGraphConnectionManager> GraphConnectionManager;`
- L652 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this editor
- L655 _private member_ `TStrongObjectPtr<UMetaSoundBuilderBase> Builder;` — Pointer to builder being actively used to mutate MetaSound asset
- L658 _private member_ `bool bPassedValidation = true;` — Whether or not metasound being edited is valid
- L661 _private member_ `FString NodeTextToPaste;` — Text content used when either duplicating or pasting from clipboard (avoids deserializing twice)
- L665 _private member_ `bool bManuallyClearingGraphSelection = false;` — Boolean state for when selection change handle should not respond due to selection state being manually applied in code
- L668 _private member_ `int32 HighestMessageSeverity = EMessageSeverity::Info;` — Highest message severity set on last validation pass of graph.
- L671 _private member_ `FText GraphStatusDescriptionOverride;` — If set, used to inform user of validation results on hover of play icon.
- L673 _private member_ `TSharedPtr<SNotificationItem> LoadingNotificationPtr;`
- L675 _private member_ `bool bMemberRenameRequested = false;`
- L677 _private member_ `bool bRefreshGraph = false;`
- L700 _private member_ `TSharedPtr<FDocumentListener> DocListener;`
- L703 _private member_ `TOptional<FDroppedObjectsInfo> DroppedObjectsInfo;` — Objects that are currently being dropped onto the editor

#### struct `Metasound::Editor::FEditor::FUserWidgetData`  
`struct FUserWidgetData`  
_L617-625_
- L619 _public member_ `TSubclassOf<UInterface> Class;`
- L620 _public member_ `FDelegateHandle RecompileHandle;`
- L621 _public member_ `TStrongObjectPtr<UUserWidget> Widget;`
- L622 _public member_ `FMetaSoundTemplateWidgetTabInfo TabInfo;`
- L624 _public prototype_ `void SetAuditionState(UAudioComponent* AudioComponent, bool bIsAuditioning) const;`

#### struct `Metasound::Editor::FEditor::FTemplateWidgetSummoner`  
`struct FTemplateWidgetSummoner : public FWorkflowTabFactory`  
_L634-647_
- inherits: `FWorkflowTabFactory`
- L637 _public prototype_ `FTemplateWidgetSummoner(FName FactoryName, FBlueprintId InBlueprintId, TSharedPtr<class FAssetEditorToolkit> InHostingApp);`
- L639 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L640 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L641 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L644 _private prototype_ `TSharedPtr<FEditor> GetParentEditor() const;`
- L645 _private prototype_ `const FUserWidgetData* GetWidgetData() const;`
- L646 _private member_ `FBlueprintId BlueprintId;`

#### class `Metasound::Editor::FEditor::FDocumentListener`  
`class FDocumentListener : public Frontend::IDocumentBuilderTransactionListener`  
_L679-698_
- inherits: `Frontend::IDocumentBuilderTransactionListener`
- L681 _private member_ `TWeakPtr<FEditor> Parent;`
- L684 _public prototype_ `FDocumentListener() = default;`
- L685 _public function_ `FDocumentListener(TSharedRef<FEditor> InParent) : Parent(InParent)`
- L690 _public prototype_ `virtual ~FDocumentListener() = default;`
- L693 _private prototype_ `virtual void OnBuilderReloaded(Frontend::FDocumentModifyDelegates& OutDelegates) override;`
- L694 _private prototype_ `void OnDocumentTemplateChanged(const Frontend::FDocumentTemplateChangedArgs& Args);`
- L695 _private prototype_ `void OnPageSet(const Frontend::FDocumentMutatePageArgs& Args);`
- L696 _private prototype_ `void OnInputDefaultChanged(const Frontend::FDocumentArrayPagedInputArgs& Args);`
- L697 _private prototype_ `void OnMemberMetadataSet(FGuid MemberID);`

#### Free symbols / members of external scopes

- L61 _namespace_ `namespace AudioWidgets`
- L66 _namespace_ `namespace Metasound`
- L66 _namespace_ `namespace Editor` (scope `Metasound`)
- L102 _namespace_ `namespace Metasound`
- L102 _namespace_ `namespace Editor` (scope `Metasound`)
- L104 _prototype_ `bool IsPreviewingPageInputDefault(const FMetaSoundFrontendDocumentBuilder& Builder, const FMetasoundFrontendClassInput& InClassInput, const FGuid& InPageID);` (scope `Metasound::Editor`)
- L105 _prototype_ `bool IsPreviewingPageGraph(const FMetaSoundFrontendDocumentBuilder& Builder, const FGuid& InPageID);` (scope `Metasound::Editor`)
- L107 _prototype_ `bool IsPageAuditioningEnabled(const FMetaSoundFrontendDocumentBuilder& Builder, bool bHasProjectPageValues);` (scope `Metasound::Editor`)
- L108 _prototype_ `bool IsPageGraphEditingEnabled(const FMetaSoundFrontendDocumentBuilder& Builder, bool bHasProjectPageValues);` (scope `Metasound::Editor`)
- L109 _prototype_ `bool IsInputPageEditingEnabled(const FMetaSoundFrontendDocumentBuilder& Builder, bool bHasProjectPageValues);` (scope `Metasound::Editor`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditorDocumentClipboardUtils.h` (Private)


#### struct `Metasound::Editor::FDocumentPasteNotifications`  
`struct FDocumentPasteNotifications`  
_L22-27_
- L24 _public member_ `bool bPastedNodesAddMultipleVariableSetters = false;`
- L25 _public member_ `bool bPastedNodesCreateLoop = false;`
- L26 _public member_ `bool bPastedNodesAddMultipleOutputNodes = false;`

#### struct `Metasound::Editor::FDocumentClipboardUtils`  
`struct FDocumentClipboardUtils`  
_L29-58_
- L31 _public prototype_ `static TArray<UEdGraphNode*> PasteClipboardString(const FText& InTransactionText, const FString& InClipboardString, const FVector2D& InLocation, UObject& OutMetaSound, FDocumentPasteNotifications& OutNotifications);`
- L34 _public prototype_ `static void CopyMemberToClipboard(class UMetasoundEditorGraphMember* Content);` — Copy MetasoundMember to Clipboard
- L36 _public prototype_ `static FMetasoundFrontendGraphLayer CopySelectionToLayer(const FMetaSoundFrontendDocumentBuilder& Builder, const FGraphPanelSelectionSet& Selection);`
- L39 _public prototype_ `static const UMetasoundEditorGraphMember* GetMemberFromClipboard();` — Return MetasoundMember that is in Clipboard, if any
- L42 _public prototype_ `static const bool CanImportMemberFromText(const FString& TextToImport);` — Whether the string can be imported to a MetasoundMember
- L45 _private prototype_ `static void ProcessPastedCommentNodes(FMetaSoundFrontendDocumentBuilder& Builder, FMetasoundAssetBase& OutAsset, const TArrayView<UMetasoundEditorGraphCommentNode*> CommentNodes);`
- L47 _private prototype_ `static void ProcessPastedExternalNodes(FMetaSoundFrontendDocumentBuilder& Builder, FMetasoundAssetBase& OutAsset, TArray<UMetasoundEditorGraphNode*>& OutPastedNodes, FDocumentPasteNotifications& OutNotifications);`
- L49 _private prototype_ `static void ProcessPastedInputNodes(FMetaSoundFrontendDocumentBuilder& Builder, FMetasoundAssetBase& OutAsset, TArray<UMetasoundEditorGraphNode*>& OutPastedNodes);`
- L51 _private prototype_ `static void ProcessPastedNodePositions(FMetaSoundFrontendDocumentBuilder& OutAsset, const FVector2D& InLocation, TArray<UMetasoundEditorGraphNode*>& OutPastedNodes, const TArrayView<UMetasoundEditorGraphCommentNode*> CommentNodes);`
- L53 _private prototype_ `static void ProcessPastedNodeConnections(FMetasoundAssetBase& OutAsset, TArray<UMetasoundEditorGraphNode*>& OutPastedNodes);`
- L55 _private prototype_ `static void ProcessPastedOutputNodes(FMetaSoundFrontendDocumentBuilder& Builder, FMetasoundAssetBase& OutAsset, TArray<UMetasoundEditorGraphNode*>& OutPastedNodes, FDocumentPasteNotifications& OutNotifications);`
- L57 _private prototype_ `static void ProcessPastedVariableNodes(FMetasoundAssetBase& OutAsset, TArray<UMetasoundEditorGraphNode*>& OutPastedNodes, FDocumentPasteNotifications& OutNotifications);`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Metasound`
- L20 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditorGraphBuilder.h` (Private)


#### class `Metasound::Editor::FGraphBuilder`  
`class FGraphBuilder`  
_L49-277_
- L52 _public member_ `static const FText FunctionMenuName;`
- L53 _public member_ `static const FText GraphMenuName;`
- L56 _public prototype_ `static TSharedPtr<FEditor> GetEditorForMetasound(const UObject& InMetaSound);` — Convenience functions for retrieving the editor for the given UObject
- L57 _public prototype_ `static TSharedPtr<FEditor> GetEditorForGraph(const UEdGraph& InEdGraph);`
- L58 _public prototype_ `static TSharedPtr<FEditor> GetEditorForNode(const UEdGraphNode& InEdNode);`
- L59 _public prototype_ `static TSharedPtr<FEditor> GetEditorForPin(const UEdGraphPin& InEdPin);`
- L62 _public prototype_ `static FGraphValidationResults ValidateGraph(UObject& InMetaSound);` — Validates MetaSound graph, returning the highest EMessageSeverity integer value
- L66 _public prototype_ `static bool RecurseGetDocumentModified(FMetasoundAssetBase& InAssetBase);` — Recursively checks whether the provided Asset's Document is marked as modified since last EdGraph synchronization, or if any of its referenced asset graphs have been marked as modified.
- L69 _public function_ `static Frontend::FMetaSoundAssetRegistrationOptions GetDefaultRegistrationOptions()` — Returns default registration options when registering from this graph builder API.
- L80 _public prototype_ `static void RegisterGraphWithFrontend(UObject& InMetaSound, Frontend::FMetaSoundAssetRegistrationOptions RegOptions = GetDefaultRegistrationOptions());` — Wraps RegisterGraphWithFrontend logic in Frontend with any additional logic required to refresh editor & respective editor object state. @param InMetaSound - MetaSound to register @param RegOptions - Registration options utilized
- L83 _public prototype_ `static bool CanInspectPin(const UEdGraphPin* InPin);` — Determines if pin supports inspection/probe view.
- L88 _public prototype_ `static FText GetDisplayName(const FMetasoundFrontendClassMetadata& InClassMetadata, FName InNodeName, bool bInIncludeNamespace);` — Returns a display name for a node. If the node has an empty or whitespace only DisplayName, first attempts to use the asset name if class is defined in an asset, and finally the NodeName is used.
- L93 _public prototype_ `static FText GetDisplayName(const Frontend::INodeController& InFrontendNode, bool bInIncludeNamespace);` — Returns a display name for a node. If the node has an empty or whitespace only DisplayName, first attempts to use the asset name if class is defined in an asset, and finally the NodeName is used.
- L97 _public prototype_ `static FText GetDisplayName(const Frontend::IInputController& InFrontendInput);` — Returns a display name for an input. If the input has an empty or whitespace only DisplayName, then the VertexName is used.
- L101 _public prototype_ `static FText GetDisplayName(const Frontend::IOutputController& InFrontendOutput);` — Returns a display name for a output. If the output has an empty or whitespace only DisplayName, then the VertexName is used.
- L105 _public prototype_ `static FText GetDisplayName(const Frontend::IVariableController& InFrontendVariable, bool bInIncludeNamespace = false);` — Returns a display name for a variable. If the variable has an empty or whitespace only DisplayName, then the VariableName is used.
- L108 _public prototype_ `static UMetasoundEditorGraphCommentNode* CreateCommentNode(UObject& InMetaSound, bool bInSelectNewNode = true, FGuid InCommentID = FGuid::NewGuid());` — Adds a new EdGraph comment node associated with the given MetaSoundFrontendGraph comment ID
- L111 _public prototype_ `static UMetasoundEditorGraphExternalNode* AddExternalNode(UObject& InMetaSound, const FGuid& InNodeID, const FMetasoundFrontendClassMetadata& InMetadata, bool bInSelectNewNode = true);` — Adds a corresponding UMetasoundEditorGraphExternalNode for the provided node handle.
- L114 _public prototype_ `static UMetasoundEditorGraphExternalNode* AddTemplateNode(UObject& InMetaSound, const FGuid& InNodeID, const FMetasoundFrontendClassMetadata& InMetadata, bool bInSelectNewNode = true);` — Adds an editor graph node that corresponds with an instance of a node that is defined by an external MetaSound node class.
- L118 _public prototype_ `static UMetasoundEditorGraphExternalNode* AddExternalNode(UObject& InMetaSound, const FMetasoundFrontendClassMetadata& InMetadata, bool bInSelectNewNode = true);` — Adds an externally-defined node with the given class info to both the editor and document graphs. Generates analogous FNodeHandle.
- L120 _public prototype_ `static Frontend::FNodeHandle AddExternalNodeHandle(UObject& InMetaSound, const FMetasoundFrontendClassName& InClassName);`
- L123 _public prototype_ `static UMetasoundEditorGraphVariableNode* AddVariableNode(UObject& InMetaSound, const FGuid& InNodeID, bool bInSelectNewNode = true);` — Adds an variable editor node with the given variable node (ex. mutator, accessor) to the editor graph.
- L126 _public prototype_ `static UMetasoundEditorGraphInputNode* AddInputNode(UObject& InMetaSound, const FGuid& InInputTemplateNodeID, bool bInSelectNewNode = true);` — Adds an input node to the editor graph that corresponds to the provided input template node in the document with the given ID.
- L129 _public prototype_ `static UMetasoundEditorGraphOutputNode* AddOutputNode(UObject& InMetaSound, const FGuid& InNodeID, bool bInSelectNewNode = true);` — Adds an output node to the editor graph that corresponds to the provided output node ID.
- L132 _public prototype_ `static FMetasoundAssetBase& GetOutermostMetaSoundChecked(UObject& InSubObject);` — Convenience method for walking to the outermost object and transforming to a base MetaSound
- L133 _public prototype_ `static const FMetasoundAssetBase& GetOutermostConstMetaSoundChecked(const UObject& InSubObject);`
- L138 _public prototype_ `static bool ConnectNodes(UEdGraphPin& InInputPin, UEdGraphPin& InOutputPin, bool bInConnectEdPins);` — Attempts to connect Frontend node counterparts together for provided pins.  Returns true if succeeded, and breaks pin link and returns false if failed.  If bConnectEdPins is set, will attempt to connect the Editor Graph representation of the pins.
- L141 _public prototype_ `static FMetasoundFrontendClassInput CreateUniqueClassInput( UObject& InMetaSound, const FCreateNodeVertexParams& InVertexParams, const TArray<FMetasoundFrontendClassInputDefault>& InDefaultLiterals = { }, const FName* InNameBase = nullptr);` — Creates a unique class input with the given default data.
- L148 _public prototype_ `static FMetasoundFrontendClassOutput CreateUniqueClassOutput( UObject& InMetaSound, const FCreateNodeVertexParams& InVertexParams, const FName* InNameBase = nullptr);` — Creates a unique class output with the given default data.
- L156 _public prototype_ `static void DisconnectPinVertex(UEdGraphPin& InPin);` — Disconnects pin's associated frontend vertex from any linked input or output nodes, and reflects change in the Frontend graph. Does *not* disconnect the EdGraph pins.
- L158 _public prototype_ `static UMetaSoundBuilderBase& GetBuilderFromPinChecked(const UEdGraphPin& InPin);`
- L160 _public prototype_ `static TArray<FString> GetDataTypeNameCategories(const FName& InDataTypeName);`
- L164 _public prototype_ `static Frontend::FInputHandle GetInputHandleFromPin(const UEdGraphPin* InPin);` — Get the input handle from an input pin.  Ensures pin is an input pin. TODO: use IDs to connect rather than names. Likely need an UMetasoundEditorGraphPin
- L165 _public prototype_ `static Frontend::FConstInputHandle GetConstInputHandleFromPin(const UEdGraphPin* InPin);`
- L167 _public prototype_ `static FName GetPinDataType(const UEdGraphPin* InPin);`
- L168 _public prototype_ `static FMetasoundFrontendVertexHandle GetPinVertexHandle(const FMetaSoundFrontendDocumentBuilder& InBuilder, const UEdGraphPin* InPin);`
- L169 _public prototype_ `static const FMetasoundFrontendVertex* GetPinVertex(const FMetaSoundFrontendDocumentBuilder& InBuilder, const UEdGraphPin* InPin, const FMetasoundFrontendNode** Node = nullptr);`
- L173 _public prototype_ `static Frontend::FOutputHandle GetOutputHandleFromPin(const UEdGraphPin* InPin);` — Get the output handle from an output pin.  Ensures pin is an output pin. TODO: use IDs to connect rather than names. Likely need an UMetasoundEditorGraphPin
- L174 _public prototype_ `static Frontend::FConstOutputHandle GetConstOutputHandleFromPin(const UEdGraphPin* InPin);`
- L176 _public prototype_ `static bool IsPreviewingMetaSound(const UObject& InObject);`
- L178 _public prototype_ `static UEdGraphPin* FindReroutedOutputPin(UEdGraphPin* InPin);`
- L179 _public prototype_ `static const UEdGraphPin* FindReroutedOutputPin(const UEdGraphPin* InPin);`
- L183 _public prototype_ `static Frontend::FConstOutputHandle FindReroutedConstOutputHandleFromPin(const UEdGraphPin* InPin);` — Find the "concrete" output handle associated with an output pin.  If the given output pin is on a reroute node, will recursively search for the non-rerouted output its representing.
- L187 _public prototype_ `static void FindReroutedInputPins(UEdGraphPin* InPinToCheck, TArray<UEdGraphPin*>& InOutInputPins);` — Find the "concrete" input handle associated with an output pin.  If the given input pin is on a reroute node, will recursively search for all the non-rerouted input pins its representing.
- L190 _public prototype_ `static bool GetPinLiteral(const UEdGraphPin& InInputPin, FMetasoundFrontendLiteral& OutLiteralDefault);` — Returns the default literal stored on the respective Frontend Node's Input.
- L193 _public prototype_ `static bool DeleteNode(UEdGraphNode& InNode, bool bRemoveUnusedDependencies = true);` — Deletes both the editor graph & frontend nodes from respective graphs
- L197 _public prototype_ `static bool BindEditorGraph(const FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraph** OutGraph = nullptr);` — Returns Editor Graph associated with the given builder's MetaSound object. If the editor graph was created, initialized, and bound to builder's MetaSound object, returns true (false if it already existed).  Sets (optional) pointer to the bound graph.
- L200 _public prototype_ `static void RefreshPinMetadata(UEdGraphPin& InPin, bool bAdvancedView = false);` — Refreshes pin state from class FrontendClassVertexMetadata
- L209 _public prototype_ `static bool SynchronizeGraph(FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraph& OutGraph, bool bSkipIfModifyContextUnchanged = true);` — Adds and removes nodes, pins and connections so that the UEdGraph of the MetaSound matches the FMetasoundFrontendDocument model. Validates the graph (and those referenced recursively). @param InBuilder - Builder to synchronize ed graph with. @param OutGraph - Graph to mutate to conform to provided builder's selected build graph @param bSkipIfModifyContextUnchanged - If true, recursively checks deprecated document modification for builder's document and all referenced documents, and skips EdGraph synchronization if no modifications are logged. @return whether or not EditorGraph synchronization was performed.
- L212 _public prototype_ `static void SynchronizeNodes(const FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraph& OutGraph);` — Synchronizes editor nodes with frontend nodes, removing editor nodes that are not represented in the frontend, and adding editor nodes to represent missing frontend nodes.
- L217 _public prototype_ `static bool SynchronizeOutputNodes(const FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraph& OutGraph);` — Synchronizes and reports to log whether or not an output node's associated FrontendNode ID has changed and therefore been updated through node versioning. @return True if the UMetasoundEditorGraphNode was altered. False otherwise.
- L222 _public prototype_ `static bool SynchronizeNodePins( const FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraphNode& InEditorNode, const FMetasoundFrontendNode& InNode, const FMetasoundFrontendClass& InClass, bool bRemoveUnusedPins = true);` — Adds and removes pins so that the UMetasoundEditorGraphNode matches the InNode. @return True if the UMetasoundEditorGraphNode was altered. False otherwise.
- L229 _public prototype_ `static bool SynchronizeComments(const FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraph& OutGraph);`
- L235 _public prototype_ `static bool SynchronizeConnections(const FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraph& OutGraph);` — Adds and removes connections so that the UEdGraph of the MetaSound has the same connections as the FMetasoundFrontendDocument graph. @return True if the UEdGraph was altered. False otherwise.
- L238 _public prototype_ `static bool SynchronizePinLiteral(const FMetaSoundFrontendDocumentBuilder& InBuilder, UEdGraphPin& InPin);` — Synchronizes literal for a given input with the EdGraph's pin value.
- L241 _public prototype_ `static bool SynchronizePinType(const IMetasoundEditorModule& InEditorModule, UEdGraphPin& InPin, const FName InDataType);` — Synchronizes pin type for a given pin with that registered with the MetaSound editor module provided.
- L246 _public prototype_ `static bool SynchronizeGraphMembers(const FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraph& OutGraph);` — Synchronizes inputs, variables, and outputs for the given MetaSound. @return True if the UEdGraph was altered. False otherwise.
- L252 _public typedef_ `using FDepthFirstVisitFunction = TFunctionRef<TSet<UEdGraphNode*> (UEdGraphNode*)>;` — Function signature for visiting a node doing depth first traversal. Functions accept a UEdGraphNode* and return a TSet<UEdGraphNode*> which represent all the children of the node.
- L259 _public prototype_ `static void DepthFirstTraversal(UEdGraphNode* InInitialNode, FDepthFirstVisitFunction InVisitFunction);` — Traverse depth first starting at the InInitialNode and calling the InVisitFunction for each node. This implementation avoids recursive function calls to support deep graphs.
- L263 _private prototype_ `static UEdGraphPin* AddPinToNode( const IMetasoundEditorModule& EditorModule, const FMetaSoundFrontendDocumentBuilder& InBuilder, UMetasoundEditorGraphNode& InEditorNode, const FMetasoundFrontendClass& InClass, const FMetasoundFrontendNode& InNode, const FMetasoundFrontendVertex& InVertex, EEdGraphPinDirection Direction);` — Adds an input or output UEdGraphPin to a UMetasoundEditorGraphNode
- L273 _private prototype_ `static bool IsMatchingInputAndPin(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FMetasoundFrontendVertex& InVertex, const UEdGraphPin& InEditorPin);` — Returns true if the given input vertex and UEdGraphPin match each other.
- L276 _private prototype_ `static bool IsMatchingOutputAndPin(const FMetaSoundFrontendDocumentBuilder& InBuilder, const FMetasoundFrontendVertex& InVertex, const UEdGraphPin& InEditorPin);` — Returns true if the given output vertex and UEdGraphPin match each other.

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace Metasound`
- L42 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditorGraphConnectionDrawingPolicy.h` (Private)


#### struct `Metasound::Editor::FDrawConnectionData`  
`struct FDrawConnectionData`  
_L32-64_
- L34 _public member_ `FDeprecateSlateVector2D P0;`
- L35 _public member_ `FDeprecateSlateVector2D P0Tangent;`
- L36 _public member_ `FDeprecateSlateVector2D P1;`
- L37 _public member_ `FDeprecateSlateVector2D P1Tangent;`
- L39 _public member_ `FConnectionParams Params;`
- L41 _public member_ `FBox2f Bounds;`
- L43 _public member_ `const UEdGraphPin* OutputPin = nullptr;`
- L44 _public member_ `const FMetasoundFrontendVertex* OutputVertex = nullptr;`
- L45 _public member_ `const FMetasoundFrontendNode* OutputNode = nullptr;`
- L47 _public member_ `bool bCloseToSpline = false;`
- L48 _public member_ `float ClosestDistanceSquared = TNumericLimits<float>::Max();`
- L51 _public member_ `float QueryDistanceTriggerThresholdSquared = 0.0f;` — Distance to consider as an overlap
- L55 _public member_ `float QueryDistanceForCloseSquared = 0.0f;` — Distance to pass the bounding box cull test. This is used for the bCloseToSpline output that can be used as a dead zone to avoid mistakes caused by missing a double-click on a connection.
- L57 _public member_ `FDeprecateSlateVector2D ClosestPoint;`
- L59 _public member_ `const FMetasoundFrontendEdgeStyle* EdgeStyle = nullptr;`
- L61 _public prototype_ `FDrawConnectionData(const UE::Slate::FDeprecateVector2DParameter& InStart, const UE::Slate::FDeprecateVector2DParameter& InEnd, const FEditor& Editor, const UE::Slate::FDeprecateVector2DParameter& InSplineTangent, const FConnectionParams& InParams, const UGraphEditorSettings& InSettings, const UE::Slate::FDeprecateVector2DParameter& InMousePosition);`
- L63 _public prototype_ `void UpdateSplineOverlap(FGraphSplineOverlapResult& OutResult) const;`

#### struct `Metasound::Editor::FGraphConnectionDrawingPolicyFactory`  
`struct FGraphConnectionDrawingPolicyFactory : public FGraphPanelPinConnectionFactory`  
_L66-81_
- inherits: `FGraphPanelPinConnectionFactory`
- L69 _public prototype_ `virtual ~FGraphConnectionDrawingPolicyFactory() = default;`
- L72 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionPolicy( const UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const override;` — FGraphPanelPinConnectionFactory

#### class `Metasound::Editor::FGraphConnectionDrawingPolicy`  
`class FGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L84-148_
- inherits: `FConnectionDrawingPolicy`
- desc: Draws the connections for a UMetasoundEditorGraph using a UMetasoundEditorGraphSchema
- L95 _protected typedef_ `using FExecPairingMap = TMap<UEdGraphNode*, FTimePair>;` — Map of pairings
- L98 _protected member_ `TMap<UEdGraphNode*, FExecPairingMap> PredecessorNodes;` — Map of nodes that preceded before a given node in the execution sequence (one entry for each pairing)
- L100 _protected member_ `UEdGraph* GraphObj = nullptr;`
- L102 _protected member_ `FLinearColor ActiveColor;`
- L103 _protected member_ `FLinearColor InactiveColor;`
- L105 _protected member_ `int32 WireAnimationLayerID = 0;`
- L107 _protected member_ `FMetasoundAnalyzerAnimationSettings AnalyzerSettings;`
- L109 _protected member_ `TWeakPtr<FEditor> MetasoundEditor;`
- L112 _public prototype_ `FGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L115 _public prototype_ `virtual void DrawConnection(int32 LayerId, const FVector2f& Start, const FVector2f& End, const FConnectionParams& InParams) override;` — FConnectionDrawingPolicy interface
- L116 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* InPinA, UEdGraphPin* InPinB, FConnectionParams& OutParams) override;`
- L119 _public prototype_ `virtual void DrawAnimatedSpline(const FDrawConnectionData& InData);`
- L120 _public prototype_ `virtual void DrawSpline(const FDrawConnectionData& InData);`
- L121 _public prototype_ `virtual void DrawConnectionSpline(int32 InLayerId, const FDrawConnectionData& InData);`
- L124 _public prototype_ `void ApplyHoverDeemphasisMetaSound(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, const bool bIsPlaying, float& Thickness, FLinearColor& WireColor);` — Copied from FConnectionDrawingPolicy::ApplyHoverDeemphasis, with modification to only apply thickness emphasis when not playing
- L126 _public prototype_ `const TSharedPtr<const FEditor> GetEditor() const;`
- L127 _public prototype_ `TSharedPtr<FEditor> GetEditor();`
- L143 _protected prototype_ `void ScaleEnvelopeWireThickness(FConnectionParams& OutParams) const;`
- L145 _protected prototype_ `virtual void DrawConnectionSignal(const FDrawConnectionSignalData& InParams);`
- L146 _protected prototype_ `virtual void DrawConnectionSignal_Envelope(const FDrawConnectionSignalData& InParams, FName InAnalyzerName);`
- L147 _protected prototype_ `virtual void DrawConnection_MidpointImage(int32 InLayerId, const FInterpCurve<float>& SplineReparamTable, float InSplineLength, const FDrawConnectionData& InData);`

#### struct `Metasound::Editor::FGraphConnectionDrawingPolicy::FTimePair`  
`struct FTimePair`  
_L88-92_
- desc: Times for one execution pair within the current graph
- L90 _public member_ `double PredExecTime = 0.0;`
- L91 _public member_ `double ThisExecTime = 0.0;`

#### struct `Metasound::Editor::FGraphConnectionDrawingPolicy::FDrawConnectionSignalData`  
`struct FDrawConnectionSignalData`  
_L131-141_
- L133 _public member_ `const float AppTime = 0.0f;`
- L134 _public member_ `const int32 LayerId = 0;`
- L135 _public member_ `const FInterpCurve<float>& SplineReparamTable;`
- L136 _public member_ `const float SplineLength = 0.0f;`
- L137 _public member_ `const FDrawConnectionData& ConnectionData;`
- L139 _public member_ `float SpacingFactor = 64.0f;`
- L140 _public member_ `float SpeedFactor = 192.0f;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace Metasound`
- L26 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditorGraphConnectionManager.h` (Private)


#### class `Metasound::Editor::FFloatMovingWindow`  
`class FFloatMovingWindow`  
_L26-78_
- L28 _private member_ `TArray<float> Data;`
- L29 _private member_ `int32 WriteIndex = -1;`
- L32 _public function_ `bool IsEmpty() const`
- L37 _public function_ `int32 Num() const`
- L42 _public function_ `void SetNumZeroed(int32 InNum)`
- L60 _public function_ `void SetValue(float InValue)`
- L71 _public function_ `float GetValueWrapped(int32 Index) const`

#### class `Metasound::Editor::FGraphConnectionManager`  
`class FGraphConnectionManager`  
_L80-238_
- L82 _private prototype_ `FGraphConnectionManager(const FGraphConnectionManager&) = delete;`
- L85 _public prototype_ `FGraphConnectionManager() = default;`
- L86 _public prototype_ `~FGraphConnectionManager() = default;`
- L88 _public prototype_ `FGraphConnectionManager(const FMetasoundAssetBase& InAssetBase, const UAudioComponent& InAudioComponent, uint64 InTransmitterID, const FOperatorSettings& InOperatorSettings);`
- L89 _public prototype_ `bool GetValue(const FGuid& InNodeID, FVertexName InOutputName, float& OutValue) const;`
- L90 _public prototype_ `bool GetValue(const FGuid& InNodeID, FVertexName InOutputName, bool& OutValue) const;`
- L91 _public prototype_ `bool GetValue(const FGuid& InNodeID, FVertexName InOutputName, int32& OutValue) const;`
- L92 _public prototype_ `bool GetValue(const FGuid& InNodeID, FVertexName InOutputName, FString& OutValue) const;`
- L94 _public prototype_ `const FFloatMovingWindow* GetValueWindow(const FGuid& InNodeID, FVertexName InOutputName, FName InAnalyzerName) const;`
- L96 _public prototype_ `bool IsTracked(const FGuid& InNodeID, FVertexName InOutputName, FName InAnalyzerName) const;`
- L100 _public prototype_ `void TrackValue(const FGuid& InNodeID, FVertexName InOutputName, FName InAnalyzerName, int32 InWindowSize);` — Marks to track (if not yet tracked) & sets the window size of cached values. Retains existing values provided from update up to given size.
- L103 _public prototype_ `FGuid AddAudioBusWriter(const FGuid& InNodeID, FVertexName InOutputName, Audio::FDeviceId InDeviceID, const UAudioBus* InAudioBus);` — Send the audio from the given node output to the given bus. If successful, an AnalyzerInstanceID will be returned.
- L106 _public prototype_ `void RemoveAudioBusWriter(const FGuid& InAnalyzerInstanceID);` — Remove the specified analyzer. InAnalyzerInstanceID is an FGuid that was previously returned from a call to AddAudioBusWriter(...).
- L109 _public prototype_ `bool HasAudioBusWriter(const FGuid& InAnalyzerInstanceID) const;` — Does this connection manager have the specified analyzer? InAnalyzerInstanceID is an FGuid that was previously returned from a call to AddAudioBusWriter(...).
- L111 _public prototype_ `void Update(float InDeltaTime);`
- L114 _public function_ `template <typename TAnalyzerName> float UpdateValueWindow(const FGuid& InNodeID, FVertexName InOutputName)`
- L122 _private function_ `template <typename ForwardValueAnalyzerClass> FString GetAnalyzerKey(const FGuid& InNodeID, FVertexName InOutputName) const`
- L151 _private function_ `template<typename TVertexAnalyzerValue, typename TDataType> bool GetPrimativeValue(const FGuid& InNodeID, FVertexName InOutputName, const TMap<FString, TDataType>& InDataMap, TDataType& OutValue) const`
- L167 _private prototype_ `float UpdateValueWindow(const FGuid& InNodeID, FVertexName InOutputName, FName InAnalyzerName, FName InAnalyzerOutputName);` — Updates the value window, returning the most recent value
- L170 _private function_ `template <typename ForwardValueAnalyzerClass, typename AnalyzerOutputDataType> void UpdateConnections(float InDeltaTime, TFunctionRef<void(const Frontend::FAnalyzerAddress& , const AnalyzerOutputDataType& )> InUpdateFunction)`
- L192 _private function_ `template <typename ForwardValueAnalyzerClass, typename AnalyzerOutputDataType> void UpdateConnections(float InDeltaTime, TMap<FString, AnalyzerOutputDataType>& OutMap)`
- L207 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FWindowValueKey& Key)`
- L228 _private member_ `TMap<FWindowValueKey, FFloatMovingWindow> WindowedValues;`
- L230 _private member_ `TWeakObjectPtr<const UAudioComponent> AudioComponent;`
- L231 _private member_ `TMap<FString, Audio::FVolumeFader> ConnectionFaders;`
- L233 _private member_ `TMap<FString, int32> IntConnectionValues;`
- L234 _private member_ `TMap<FString, bool> BoolConnectionValues;`
- L235 _private member_ `TMap<FString, FString> StringConnectionValues;`
- L237 _private member_ `TUniquePtr<Frontend::FMetasoundGraphAnalyzerView> GraphAnalyzerView;`

#### struct `Metasound::Editor::FGraphConnectionManager::FWindowValueKey`  
`struct FWindowValueKey`  
_L201-224_
- L203 _public member_ `const FGuid NodeID;`
- L204 _public member_ `const FName OutputName;`
- L205 _public member_ `const FName AnalyzerName;`
- L215 _public function_ `FORCEINLINE bool operator==(const FWindowValueKey& Other) const`
- L220 _public function_ `FORCEINLINE bool operator!=(const FWindowValueKey& Other) const`

#### struct `Metasound::Editor::FGraphConnectionManager::FAudioBufferKey`  
`struct FAudioBufferKey : FWindowValueKey`  
_L226-226_
- inherits: `FWindowValueKey`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Metasound`
- L24 _namespace_ `namespace Editor` (scope `Metasound`)
- L133 _function_ `` (scope `Metasound::Editor::FGraphConnectionManager::GetAnalyzerKey`)
- L195 _function_ `` (scope `Metasound::Editor::FGraphConnectionManager::UpdateConnections`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditorGraphNodeFactory.h` (Private)


#### class `FMetasoundGraphNodeFactory`  
`class FMetasoundGraphNodeFactory : public FGraphPanelNodeFactory`  
_L20-55_
- inherits: `FGraphPanelNodeFactory`
- L22 _private function_ `virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* InNode) const override`

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditorGraphNodeVisualization.h` (Private)


#### class `Metasound::Editor::FGraphNodeVisualizationRegistry`  
`class FGraphNodeVisualizationRegistry`  
_L12-26_
- L15 _public prototype_ `static FGraphNodeVisualizationRegistry& Get();`
- L16 _public prototype_ `static void TearDown();`
- L19 _public prototype_ `void RegisterVisualization(FName Key, FOnCreateGraphNodeVisualizationWidget OnCreateGraphNodeVisualizationWidget);` — For the given key, register a delegate that can be used for creating node visualization widgets.
- L22 _public prototype_ `TSharedPtr<SWidget> CreateVisualizationWidget(FName Key, const FCreateGraphNodeVisualizationWidgetParams& Params);` — Creates a visualization widget if a delegate has been registered with the given key.
- L25 _private member_ `TMap<FName, FOnCreateGraphNodeVisualizationWidget> RegisteredVisualizationDelegates;`

#### class `Metasound::Editor::FGraphNodeVisualizationUtils`  
`class FGraphNodeVisualizationUtils`  
_L28-110_
- L33 _public function_ `template<class T> static bool TryGetPinValue(const UMetasoundEditorGraphNode& MetaSoundNode, FName PinName, T& OutValue)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L10 _namespace_ `namespace Editor` (scope `Metasound`)
- L36 _function_ `` (scope `Metasound::Editor::FGraphNodeVisualizationUtils::TryGetPinValue`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditorSettings.h` (Private)


#### enum `EMetasoundActiveAnalyzerEnvelopeDirection`  
`enum class EMetasoundActiveAnalyzerEnvelopeDirection : uint8`  
_L34-38_
- reflection: `UENUM()`
- L36 _public enumerator_ `FromSourceOutput`
- L37 _public enumerator_ `FromDestinationInput`

#### enum `EMetasoundMemberDefaultWidget`  
`enum class EMetasoundMemberDefaultWidget : uint8`  
_L41-46_
- reflection: `UENUM()`
- L43 _public enumerator_ `None`
- L44 _public enumerator_ `Slider`
- L45 _public enumerator_ `RadialSlider UMETA(DisplayName = "Knob")`

#### enum `EMetasoundBoolMemberDefaultWidget`  
`enum class EMetasoundBoolMemberDefaultWidget : uint8`  
_L49-53_
- reflection: `UENUM()`
- L51 _public enumerator_ `None`
- L52 _public enumerator_ `Button`

#### enum `EMetasoundActiveDetailView`  
`enum class EMetasoundActiveDetailView : uint8`  
_L56-60_
- reflection: `UENUM()`
- L58 _public enumerator_ `Metasound`
- L59 _public enumerator_ `General`

#### enum `EAuditionPageMode`  
`enum class EAuditionPageMode : uint8`  
_L63-70_
- reflection: `UENUM()`
- L66 _public enumerator_ `Focused` — Sets Audition Page automatically to graph page focused in asset editor
- L69 _public enumerator_ `User` — Audition Page is specified by user (does not automatically change when graph page is focused)

#### struct `FMetasoundAnalyzerAnimationSettings`  
`struct FMetasoundAnalyzerAnimationSettings`  
_L73-106_
- reflection: `USTRUCT()`
- L79 _public member_ `bool bAnimateConnections = true;` — `UPROPERTY(EditAnywhere, config, Category = GraphAnimation, meta = (DisplayName = "Animate Connections (Beta)"))` — Whether or not animated connections are enabled.
- L83 _public member_ `float EnvelopeWireThickness = 1.0f;` — `UPROPERTY(EditAnywhere, config, Category = GraphAnimation, meta = (EditCondition = "bAnimateConnections", UIMin = 1, UIMax = 2, ClampMin = 1))` — Thickness of default envelope analyzer wire thickness when connection analyzer is active.
- L87 _public member_ `float EnvelopeSpeed = 0.95f;` — `UPROPERTY(EditAnywhere, config, Category = GraphAnimation, meta = (EditCondition = "bAnimateConnections", ClampMin = 0, ClampMax = 1))` — Speed of default envelope analyzer drawing over wire when connection analyzer is active, where 0 is full visual history (slowest progress) and 1 is no visual history (fastest progress).
- L93 _public member_ `EMetasoundActiveAnalyzerEnvelopeDirection EnvelopeDirection = EMetasoundActiveAnalyzerEnvelopeDirection::FromSourceOutput;` — `UPROPERTY(EditAnywhere, config, Category = GraphAnimation, meta = (EditCondition = "bAnimateConnections", ClampMin = 0, ClampMax = 1))` — Whether analyzer envelopes draw from a source output (default) or from the destination input. From the destination input may not give the expected illusion of audio processing flowing left-to-right, but results in a waveform with earlier events on the left and later on the right (like a traditional timeline with a moving play head).
- L97 _public member_ `float NumericWireThickness = 5.0f;` — `UPROPERTY(EditAnywhere, config, Category = GraphAnimation, meta = (EditCondition = "bAnimateConnections", UIMin = 1, UIMax = 10, ClampMin = 1))` — Thickness of default numeric analyzer wire thickness when connection analyzer is active.
- L101 _public member_ `float WireScalarMin = 1.0f;` — `UPROPERTY(EditAnywhere, config, Category = GraphAnimation, meta = (EditCondition = "bAnimateConnections", UIMin = 1, UIMax = 5, ClampMin = 1))` — Minimum height scalar of wire signal analyzers (ex. audio, triggers).
- L105 _public member_ `float WireScalarMax = 4.5f;` — `UPROPERTY(EditAnywhere, config, Category = GraphAnimation, meta = (EditCondition = "bAnimateConnections", UIMin = 1, UIMax = 5, ClampMin = 1))` — Maximum height scalar of wire signal analyzers (ex. audio, triggers).

#### class `UMetasoundEditorSettings`  
`class UMetasoundEditorSettings : public UObject`  
_L109-353_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L115 _public member_ `static const FName DefaultAuditionPlatform;` — Represents auditioning any platform using the default target/cook settings
- L118 _public member_ `static const FName EditorAuditionPlatform;` — Represents auditioning as the editor, ignoring any explicit target/cook settings
- L123 _public member_ `bool bPinMetaSoundPatchInAssetMenu = false;` — `UPROPERTY(EditAnywhere, config, meta = (ConfigRestartRequired = true), Category = AssetMenu)` — Whether to pin the MetaSound Patch asset type when creating new assets. Requires editor restart for change to take effect.
- L128 _public member_ `bool bPinMetaSoundSourceInAssetMenu = true;` — `UPROPERTY(EditAnywhere, config, meta = (ConfigRestartRequired = true), Category = AssetMenu)` — Whether to pin the MetaSound Source asset type when creating new assets. Requires editor restart for change to take effect.
- L134 _public member_ `bool bApplyAuditionSettingsInPIE = true;` — `UPROPERTY(EditAnywhere, config, Category = "Audition (Experimental)")` — If true, uses editor page/platform audition settings in PIE. If false, uses project's defined values (see project 'MetaSound' setting 'TargetPage', which can be manipulated via code/Blueprint.)
- L140 _public member_ `FString DefaultAuthor;` — `UPROPERTY(EditAnywhere, config, Category = General)` — Default author title to use when authoring a new MetaSound.  If empty, uses machine name by default.
- L145 _private member_ `EAuditionPageMode AuditionPageMode = EAuditionPageMode::Focused;` — `UPROPERTY(EditAnywhere, config, Category = "Audition (Experimental)", meta = (DisplayName = "Page Audition Mode"))` — Currently set page audition mode. Set by the MetaSound Asset Editor.
- L153 _private member_ `FName AuditionPlatform = EditorAuditionPlatform;` — `UPROPERTY(EditAnywhere, config, Category = "Audition (Experimental)", meta = (DisplayName = "Page Audition Platform", GetOptions = "MetasoundEditor.MetasoundEditorSettings.GetAuditionPlatformNames"))` — Name of platform to mock when previewing playback. This will limit playback to fallback only to paged data that are cooked for the given platform. (see project 'MetaSound' Settings --> 'Page Settings' array for order) If set to 'Editor', ignores cook settings and allows fallback to all page.
- L165 _private member_ `FName AuditionPage = Metasound::Frontend::DefaultPageName;` — `UPROPERTY(EditAnywhere, config, Category = "Audition (Experimental)", meta = ( EditCondition = "AuditionPageMode == EAuditionPageMode::User", EditConditionHides = true, GetOptions = "MetasoundEditor.MetasoundEditorSettings.GetAuditionPageNames"))` — Name of the page to audition in editor. If unimplemented on the auditioned MetaSound, uses order of cooked pages (see project 'MetaSound' Settings --> 'Page Settings' array for order) falling back to lower index-ordered page implemented in MetaSound asset.
- L169 _public prototype_ `void SetAuditionPageMode(EAuditionPageMode InMode);` — Currently set page audition mode.
- L170 _public prototype_ `EAuditionPageMode GetAuditionPageMode() const;`
- L177 _public prototype_ `void SetAuditionPlatform(FName InPlatform);` — Name of platform to mock when previewing playback. This will limit playback to fallback only to paged data that are cooked for the given platform. (see project 'MetaSound' Settings --> 'Page Settings' array for order) If set to 'Editor', ignores cook settings and allows fallback to all page.
- L184 _public prototype_ `FName GetAuditionPlatform() const;` — Name of platform to mock when previewing playback. This will limit playback to fallback only to paged data that are cooked for the given platform. (see project 'MetaSound' Settings --> 'Page Settings' array for order) If set to 'Editor', ignores cook settings and allows fallback to all page.
- L190 _public prototype_ `void SetAuditionPage(FName InPage);` — Name of the page to audition in editor. If unimplemented on the auditioned MetaSound, uses order of cooked pages (see project 'MetaSound' Settings --> 'Page Settings' array for order) falling back to lower index-ordered page implemented in MetaSound asset.
- L196 _public prototype_ `FName GetAuditionPage() const;` — Name of the page to audition in editor. If unimplemented on the auditioned MetaSound, uses order of cooked pages (see project 'MetaSound' Settings --> 'Page Settings' array for order) falling back to lower index-ordered page implemented in MetaSound asset.
- L201 _public member_ `TMap<FName, FLinearColor> CustomPinTypeColors;` — `UE_DEPRECATED(5.8, "Custom pin colors are now managed by FMetaSoundGraphPanelPinFactory. Use IMetaSoundGraphPanelPinFactory::GetPinColor instead.")`
- L205 _public member_ `FLinearColor DefaultPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Default pin type color
- L209 _public member_ `FLinearColor AudioPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Audio pin type color
- L213 _public member_ `FLinearColor BooleanPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Boolean pin type color
- L217 _public member_ `FLinearColor FloatPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Floating-point pin type color
- L221 _public member_ `FLinearColor IntPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Integer pin type color
- L225 _public member_ `FLinearColor ObjectPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Object pin type color
- L229 _public member_ `FLinearColor StringPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — String pin type color
- L233 _public member_ `FLinearColor TimePinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Time pin type color
- L237 _public member_ `FLinearColor TriggerPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Trigger pin type color
- L241 _public member_ `FLinearColor WaveTablePinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category = PinColors)` — WaveTable pin type color
- L245 _public member_ `FLinearColor NativeNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category = NodeTitleColors)` — Native node class title color
- L249 _public member_ `FLinearColor AssetReferenceNodeTitleColor;` — `UE_DEPRECATED(5.8, "Asset nodes now use their corresponding asset type color.")` — Title color for references to MetaSound assets
- L253 _public member_ `FLinearColor InputNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category = NodeTitleColors)` — Input node title color
- L257 _public member_ `FLinearColor OutputNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category = NodeTitleColors)` — Output node title color
- L261 _public member_ `FLinearColor VariableNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category = NodeTitleColors)` — Variable node title color
- L265 _public member_ `FSpectrogramRackUnitSettings SpectrogramSettings;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram, meta = (ShowOnlyInnerProperties))` — Settings for metasound output spectrogram widget
- L269 _public member_ `FSpectrumAnalyzerRackUnitSettings SpectrumAnalyzerSettings;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer, meta = (ShowOnlyInnerProperties))` — Settings for metasound output spectrum analyzer widget
- L273 _public member_ `FLoudnessMeterRackUnitSettings LoudnessMeterSettings;` — `UPROPERTY(EditAnywhere, config, Category = LoudnessMeter, meta = (ShowOnlyInnerProperties))` — Settings for metasound output loudness meter widget
- L277 _public member_ `EMetasoundMemberDefaultWidget DefaultInputWidgetType = EMetasoundMemberDefaultWidget::RadialSlider;` — `UPROPERTY(EditAnywhere, config, Category = General)` — Widget type to show on input nodes by default
- L281 _public member_ `FMetasoundAnalyzerAnimationSettings AnalyzerAnimationSettings;` — `UPROPERTY(EditAnywhere, config, Category = GraphAnimation, meta = (ShowOnlyInnerProperties))` — Settings for visualizing analyzed MetaSound connections
- L285 _public member_ `EMetasoundActiveDetailView DetailView = EMetasoundActiveDetailView::General;` — `UPROPERTY(Transient)` — Determines which details view to show in Metasounds Editor
- L289 _public member_ `bool bUseAudioMaterialWidgets = false;` — `UPROPERTY(EditAnywhere, config, DisplayName = "Use Audio Material Widgets", Category = "Widget Styling (Experimental)")` — Whether the AudioMaterialWidgets are used when possible in Metasound Editor
- L293 _public member_ `FSoftObjectPath KnobStyleOverride;` — `UPROPERTY(EditAnywhere, config, Category = "Widget Styling (Experimental)", meta = (AllowedClasses = "/Script/SlateCore.SlateWidgetStyleAsset", EditCondition = "bUseAudioMaterialWidgets", DisplayName = "Knob Style"))` — Override the Knob Style used in the Metasound Editor.
- L297 _public member_ `FSoftObjectPath SliderStyleOverride;` — `UPROPERTY(EditAnywhere, config, Category = "Widget Styling (Experimental)", meta = (AllowedClasses = "/Script/SlateCore.SlateWidgetStyleAsset", EditCondition = "bUseAudioMaterialWidgets", DisplayName = "Slider Style"))` — Override the Slider Style used in the Metasound Editor.
- L301 _public member_ `FSoftObjectPath ButtonStyleOverride;` — `UPROPERTY(EditAnywhere, config, Category = "Widget Styling (Experimental)", meta = (AllowedClasses = "/Script/SlateCore.SlateWidgetStyleAsset", EditCondition = "bUseAudioMaterialWidgets", DisplayName = "Button Style"))` — Override the Button Style used in the Metasound Editor.
- L305 _public member_ `FSoftObjectPath MeterStyleOverride;` — `UPROPERTY(EditAnywhere, config, Category = "Widget Styling (Experimental)", meta = (AllowedClasses = "/Script/SlateCore.SlateWidgetStyleAsset", EditCondition = "bUseAudioMaterialWidgets", DisplayName = "Meter Style"))` — Override the Meter Style used in the Metasound Editor.
- L308 _public member_ `static constexpr int32 MaxRecentEntriesEver = 200;` — MaxRecentEntries can go up to this number (limit must be known, for ordering Common actions in graph action menu above Recent ones)
- L314 _public member_ `int32 MaxRecentEntries = 20;` — `UPROPERTY(EditAnywhere, config, Category = General, meta = (ClampMin = 1))` — The maximum number of Recent entries kept in the Metasound Editor action menu (ie., graph context menu). Older entries are overwritten by newer entries, and reusing one put it back at the top.
- L319 _private member_ `TArray<FString> RecentMetaSoundsGraphActions;` — `UPROPERTY(config)` — Higher index means more recent
- L322 _private member_ `TSet<FString> FavoriteMetaSoundsGraphActions;` — `UPROPERTY(config)` — TODO: Implement profiles, like for blueprint favorites
- L325 _public prototype_ `void AddRecentlyUsedMetaSoundsGraphAction(FString&& ActionKey);`
- L326 _public prototype_ `int32 FindRecentlyUsedMetaSoundsGraphAction(const FString& ActionKey) const;`
- L327 _public prototype_ `void AddFavoriteMetaSoundsGraphAction(FString&& ActionKey);`
- L328 _public prototype_ `void RemoveFavoriteMetaSoundsGraphAction(const FString& ActionKey);`
- L329 _public prototype_ `bool IsFavoriteMetaSoundsGraphAction(const FString& ActionKey) const;`
- L333 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L338 _public prototype_ `Metasound::Engine::FTargetPageOverride GetPageForAudition() const;` — Returns the page override data derived from the AuditionPlatform and AuditionPage
- L340 _public prototype_ `Metasound::Engine::FTargetPageOverride ResolveAuditionPage(const TArray<FGuid>& InPageIDs) const;`
- L343 _public prototype_ `FGuid ResolveAuditionPage(const TArray<FGuid>& InPageIDs, const FGuid& InAuditionPageID) const;` — Given the provided AuditionPageID, returns the resolved PageID from the provided array of values based on fallback logic.
- L346 _public prototype_ `FGuid ResolveAuditionPage(const FMetasoundFrontendClassInput& InClassInput, const FGuid& InAuditionPageID) const;` — Given the provided class input and AuditionPageID, returns the resolved PageID from the provided array of values based on fallback logic.
- L349 _public prototype_ `static TArray<FName> GetAuditionPageNames();` — `UFUNCTION()`
- L352 _public prototype_ `static TArray<FName> GetAuditionPlatformNames();` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L27 _namespace_ `namespace Metasound`
- L27 _namespace_ `namespace Engine` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundNodeDetailCustomization.h` (Private)


#### class `Metasound::Editor::FGraphMemberEditableTextBase`  
`class FGraphMemberEditableTextBase : public IEditableTextProperty`  
_L46-85_
- inherits: `IEditableTextProperty`
- L49 _protected member_ `TWeakObjectPtr<UMetasoundEditorGraphMember> GraphMember;`
- L50 _protected member_ `FText ToolTip;`
- L53 _public function_ `FGraphMemberEditableTextBase(TWeakObjectPtr<UMetasoundEditorGraphMember> InGraphMember, const FText& InToolTip) : GraphMember(InGraphMember) , ToolTip(InToolTip)`
- L59 _public prototype_ `virtual ~FGraphMemberEditableTextBase() = default;`
- L61 _public function_ `virtual bool IsMultiLineText() const override`
- L62 _public function_ `virtual bool IsPassword() const override`
- L63 _public function_ `virtual bool IsReadOnly() const override`
- L64 _public function_ `virtual int32 GetNumTexts() const override`
- L65 _public function_ `virtual bool IsValidText(const FText& InText, FText& OutErrorMsg) const override`
- L67 _public function_ `virtual FText GetToolTipText() const override`
- L72 _public function_ `virtual bool IsDefaultValue() const override`
- L78 _public function_ `virtual void GetStableTextId(const int32 InIndex, const ETextPropertyEditAction InEditAction, const FString& InTextSource, const FString& InProposedNamespace, const FString& InProposedKey, FString& OutStableNamespace, FString& OutStableKey) const override`

#### class `Metasound::Editor::FGraphMemberEditableTextDescription`  
`class FGraphMemberEditableTextDescription : public FGraphMemberEditableTextBase`  
_L87-118_
- inherits: `FGraphMemberEditableTextBase`
- L90 _public function_ `FGraphMemberEditableTextDescription(TWeakObjectPtr<UMetasoundEditorGraphMember> InGraphMember, const FText& InToolTip) : FGraphMemberEditableTextBase(InGraphMember, InToolTip)`
- L95 _public prototype_ `virtual ~FGraphMemberEditableTextDescription() = default;`
- L97 _public function_ `virtual FText GetText(const int32 InIndex) const override`
- L109 _public function_ `virtual void SetText(const int32 InIndex, const FText& InText) override`

#### class `Metasound::Editor::FGraphMemberEditableTextDisplayName`  
`class FGraphMemberEditableTextDisplayName : public FGraphMemberEditableTextBase`  
_L120-164_
- inherits: `FGraphMemberEditableTextBase`
- L123 _public function_ `FGraphMemberEditableTextDisplayName(TWeakObjectPtr<UMetasoundEditorGraphMember> InGraphMember, const FText& InToolTip) : FGraphMemberEditableTextBase(InGraphMember, InToolTip)`
- L128 _public prototype_ `virtual ~FGraphMemberEditableTextDisplayName() = default;`
- L130 _public function_ `virtual FText GetText(const int32 InIndex) const override`
- L152 _public function_ `virtual void SetText(const int32 InIndex, const FText& InText) override`

#### class `Metasound::Editor::FMetasoundFloatLiteralCustomization`  
`class FMetasoundFloatLiteralCustomization : public FMetasoundDefaultLiteralCustomizationBase`  
_L178-193_
- inherits: `FMetasoundDefaultLiteralCustomizationBase`
- L180 _private member_ `TWeakObjectPtr<UMetasoundEditorGraphMemberDefaultFloat> FloatLiteral;`
- L183 _private member_ `FDelegateHandle OnClampChangedDelegateHandle;` — Delegate for clamping the input value or not
- L186 _public function_ `FMetasoundFloatLiteralCustomization(IDetailCategoryBuilder& InDefaultCategoryBuilder) : FMetasoundDefaultLiteralCustomizationBase(InDefaultCategoryBuilder)`
- L190 _public prototype_ `virtual ~FMetasoundFloatLiteralCustomization();`
- L192 _public prototype_ `virtual void CustomizeDefaults(UMetasoundEditorGraphMemberDefaultLiteral& InLiteral, IDetailLayoutBuilder& InDetailLayout) override;`

#### class `Metasound::Editor::FMetasoundBoolLiteralCustomization`  
`class FMetasoundBoolLiteralCustomization : public FMetasoundDefaultLiteralCustomizationBase`  
_L195-208_
- inherits: `FMetasoundDefaultLiteralCustomizationBase`
- L197 _private member_ `TWeakObjectPtr<UMetasoundEditorGraphMemberDefaultBool> BoolLiteral;`
- L200 _public function_ `FMetasoundBoolLiteralCustomization(IDetailCategoryBuilder& InDefaultCategoryBuilder) : FMetasoundDefaultLiteralCustomizationBase(InDefaultCategoryBuilder)`
- L204 _public prototype_ `virtual ~FMetasoundBoolLiteralCustomization();`
- L206 _public prototype_ `virtual void CustomizeDefaults(UMetasoundEditorGraphMemberDefaultLiteral& InLiteral, IDetailLayoutBuilder& InDetailLayout) override;`
- L207 _public prototype_ `virtual TAttribute<EVisibility> GetDefaultVisibility() const override;`

#### class `Metasound::Editor::FMetasoundObjectArrayLiteralCustomization`  
`class FMetasoundObjectArrayLiteralCustomization : public FMetasoundDefaultLiteralCustomizationBase`  
_L212-224_
- inherits: `FMetasoundDefaultLiteralCustomizationBase`
- desc: Customization to support drag-and-drop of Proxy UObject types on underlying members that are structs. Struct ownership of objects required to customize asset filters based on dynamic UObject MetaSound Registry DataTypes.
- L215 _public function_ `FMetasoundObjectArrayLiteralCustomization(IDetailCategoryBuilder& InDefaultCategoryBuilder) : FMetasoundDefaultLiteralCustomizationBase(InDefaultCategoryBuilder)`
- L220 _public prototype_ `virtual ~FMetasoundObjectArrayLiteralCustomization() = default;`
- L222 _public prototype_ `virtual void BuildDefaultValueWidget(IDetailPropertyRow& ValueRow, TSharedPtr<IPropertyHandle> ValueProperty) override;`
- L223 _public prototype_ `virtual void CustomizeDefaults(UMetasoundEditorGraphMemberDefaultLiteral& InLiteral, IDetailLayoutBuilder& InDetailLayout) override;`

#### class `Metasound::Editor::FMetasoundDefaultLiteralCustomizationFactory`  
`class FMetasoundDefaultLiteralCustomizationFactory : public IMemberDefaultLiteralCustomizationFactory`  
_L226-233_
- inherits: `IMemberDefaultLiteralCustomizationFactory`
- L229 _public function_ `virtual TUniquePtr<FMetasoundDefaultLiteralCustomizationBase> CreateLiteralCustomization(IDetailCategoryBuilder& DefaultCategoryBuilder) const override`

#### class `Metasound::Editor::FMetasoundFloatLiteralCustomizationFactory`  
`class FMetasoundFloatLiteralCustomizationFactory : public IMemberDefaultLiteralCustomizationFactory`  
_L236-243_
- inherits: `IMemberDefaultLiteralCustomizationFactory`
- desc: Customization to support float widgets (ex. sliders, knobs)
- L239 _public function_ `virtual TUniquePtr<FMetasoundDefaultLiteralCustomizationBase> CreateLiteralCustomization(IDetailCategoryBuilder& DefaultCategoryBuilder) const override`

#### class `Metasound::Editor::FMetasoundBoolLiteralCustomizationFactory`  
`class FMetasoundBoolLiteralCustomizationFactory : public IMemberDefaultLiteralCustomizationFactory`  
_L246-253_
- inherits: `IMemberDefaultLiteralCustomizationFactory`
- desc: Customization to support bool widgets (ex. Buttons)
- L249 _public function_ `virtual TUniquePtr<FMetasoundDefaultLiteralCustomizationBase> CreateLiteralCustomization(IDetailCategoryBuilder& DefaultCategoryBuilder) const override`

#### class `Metasound::Editor::FMetasoundObjectArrayLiteralCustomizationFactory`  
`class FMetasoundObjectArrayLiteralCustomizationFactory : public IMemberDefaultLiteralCustomizationFactory`  
_L255-262_
- inherits: `IMemberDefaultLiteralCustomizationFactory`
- L258 _public function_ `virtual TUniquePtr<FMetasoundDefaultLiteralCustomizationBase> CreateLiteralCustomization(IDetailCategoryBuilder& DefaultCategoryBuilder) const override`

#### class `Metasound::Editor::FMetasoundDefaultMemberElementDetailCustomizationBase`  
`class FMetasoundDefaultMemberElementDetailCustomizationBase : public IPropertyTypeCustomization`  
_L264-283_
- inherits: `IPropertyTypeCustomization`
- L268 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L269 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L273 _protected function_ `virtual FText GetPropertyNameOverride() const`
- L276 _protected prototype_ `virtual TSharedRef<SWidget> CreateStructureWidget(TSharedPtr<IPropertyHandle>& PropertyHandle) const = 0;` — TODO: Merge with FMetasoundDefaultLiteralCustomizationBaseFactory
- L278 _protected member_ `Frontend::FDataTypeRegistryInfo DataTypeInfo;`
- L281 _private prototype_ `TSharedRef<SWidget> CreateNameWidget(TSharedPtr<IPropertyHandle> StructPropertyHandle) const;`
- L282 _private prototype_ `TSharedRef<SWidget> CreateValueWidget(TSharedPtr<IPropertyHandleArray> ParentArrayProperty, TSharedPtr<IPropertyHandle> StructPropertyHandle) const;`

#### class `Metasound::Editor::FMetasoundMemberDefaultBoolDetailCustomization`  
`class FMetasoundMemberDefaultBoolDetailCustomization : public FMetasoundDefaultMemberElementDetailCustomizationBase`  
_L285-290_
- inherits: `FMetasoundDefaultMemberElementDetailCustomizationBase`
- L288 _protected prototype_ `virtual FText GetPropertyNameOverride() const override;`
- L289 _protected prototype_ `virtual TSharedRef<SWidget> CreateStructureWidget(TSharedPtr<IPropertyHandle>& StructPropertyHandle) const override;`

#### class `Metasound::Editor::FMetasoundMemberDefaultIntDetailCustomization`  
`class FMetasoundMemberDefaultIntDetailCustomization : public FMetasoundDefaultMemberElementDetailCustomizationBase`  
_L292-296_
- inherits: `FMetasoundDefaultMemberElementDetailCustomizationBase`
- L295 _protected prototype_ `virtual TSharedRef<SWidget> CreateStructureWidget(TSharedPtr<IPropertyHandle>& StructPropertyHandle) const override;`

#### class `Metasound::Editor::FMetasoundMemberDefaultObjectDetailCustomization`  
`class FMetasoundMemberDefaultObjectDetailCustomization : public FMetasoundDefaultMemberElementDetailCustomizationBase`  
_L298-302_
- inherits: `FMetasoundDefaultMemberElementDetailCustomizationBase`
- L301 _protected prototype_ `virtual TSharedRef<SWidget> CreateStructureWidget(TSharedPtr<IPropertyHandle>& StructPropertyHandle) const override;`

#### class `Metasound::Editor::FMetasoundDataTypeSelector`  
`class FMetasoundDataTypeSelector`  
_L304-323_
- L307 _public prototype_ `void AddDataTypeSelector(IDetailLayoutBuilder& InDetailLayoutBuilder, const FText& InRowName, TWeakObjectPtr<UMetasoundEditorGraphMember> InGraphMember, bool bInIsInterfaceMember);`
- L308 _public prototype_ `void OnDataTypeArrayChanged(TWeakObjectPtr<UMetasoundEditorGraphMember> InGraphMember, ECheckBoxState InNewState);`
- L311 _protected prototype_ `ECheckBoxState OnGetDataTypeArrayCheckState(TWeakObjectPtr<UMetasoundEditorGraphMember> InGraphMember) const;`
- L312 _protected prototype_ `void OnDataTypeSelected(FName InSelectedTypeName);`
- L313 _protected prototype_ `FName GetDataType() const;`
- L316 _private member_ `TWeakObjectPtr<UMetasoundEditorGraphMember> GraphMember;`
- L317 _private member_ `TSharedPtr<SCheckBox> DataTypeArrayCheckbox;`
- L318 _private member_ `TSharedPtr<SSearchableComboBox> DataTypeComboBox;`
- L319 _private member_ `TArray<TSharedPtr<FString>> ComboOptions;`
- L321 _private member_ `FName BaseTypeName;`
- L322 _private member_ `FName ArrayTypeName;`

#### class `Metasound::Editor::FMetaSoundNodeDetailCustomization`  
`class FMetaSoundNodeDetailCustomization : public IDetailCustomization`  
_L325-330_
- inherits: `IDetailCustomization`
- L328 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;` — IDetailCustomization interface

#### class `Metasound::Editor::FMetasoundMemberDetailCustomization`  
`class FMetasoundMemberDetailCustomization : public IDetailCustomization`  
_L332-389_
- inherits: `IDetailCustomization`
- L335 _public function_ `virtual ~FMetasoundMemberDetailCustomization()`
- L341 _protected function_ `static IDetailCategoryBuilder& GetDefaultCategoryBuilder(IDetailLayoutBuilder& InDetailLayout)`
- L346 _protected function_ `static IDetailCategoryBuilder& GetGeneralCategoryBuilder(IDetailLayoutBuilder& InDetailLayout)`
- L351 _protected prototype_ `void UpdateRenameDelegate(UMetasoundEditorGraphMember& InMember);`
- L352 _protected prototype_ `void CacheMemberData(IDetailLayoutBuilder& InDetailLayout);`
- L354 _protected prototype_ `virtual void CustomizeDefaultCategory(IDetailLayoutBuilder& InDetailLayout);`
- L355 _protected prototype_ `virtual void CustomizeGeneralCategory(IDetailLayoutBuilder& InDetailLayout);`
- L356 _protected function_ `virtual void ConfigureLiteralCustomization(FMetasoundDefaultLiteralCustomizationBase&)`
- L358 _protected function_ `virtual EVisibility GetDefaultVisibility() const`
- L359 _protected function_ `virtual TAttribute<bool> GetEnabled() const`
- L361 _protected function_ `virtual bool IsInterfaceMember() const`
- L364 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;` — IDetailCustomization interface
- L367 _protected prototype_ `void OnNameChanged(const FText& InNewName);`
- L368 _protected prototype_ `FText GetName() const;`
- L369 _protected prototype_ `bool IsGraphEditable() const;`
- L370 _protected prototype_ `FText GetDisplayName() const;`
- L371 _protected prototype_ `void OnTooltipCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);`
- L372 _protected prototype_ `FText GetTooltip() const;`
- L373 _protected prototype_ `void OnNameCommitted(const FText& InNewName, ETextCommit::Type InTextCommit);`
- L376 _protected prototype_ `FMetaSoundFrontendDocumentBuilder* GetBuilder() const;`
- L378 _protected member_ `TWeakObjectPtr<UMetasoundEditorGraphMember> GraphMember;`
- L380 _protected member_ `TSharedPtr<SEditableTextBox> NameEditableTextBox;`
- L381 _protected member_ `FMetasoundDataTypeSelector DataTypeSelector;`
- L383 _protected member_ `bool bIsNameInvalid = false;`
- L385 _protected member_ `FDelegateHandle RenameRequestedHandle;`
- L388 _private member_ `TUniquePtr<FMetasoundDefaultLiteralCustomizationBase> LiteralCustomization;`

#### class `Metasound::Editor::FMetasoundVertexDetailCustomization`  
`class FMetasoundVertexDetailCustomization : public FMetasoundMemberDetailCustomization`  
_L391-418_
- inherits: `FMetasoundMemberDetailCustomization`
- L394 _public prototype_ `virtual ~FMetasoundVertexDetailCustomization() = default;`
- L397 _protected prototype_ `virtual void CustomizeGeneralCategory(IDetailLayoutBuilder& InDetailLayout) override;`
- L398 _protected prototype_ `virtual EVisibility GetDefaultVisibility() const;`
- L399 _protected prototype_ `virtual bool IsInterfaceMember() const override;`
- L401 _protected prototype_ `void AddConstructorPinRow(IDetailLayoutBuilder& InDetailLayout);`
- L402 _protected prototype_ `ECheckBoxState OnGetConstructorPinCheckboxState(TWeakObjectPtr<UMetasoundEditorGraphVertex> InGraphMember) const;`
- L403 _protected prototype_ `void OnConstructorPinStateChanged(TWeakObjectPtr<UMetasoundEditorGraphVertex> InGraphMember, ECheckBoxState InNewState);`
- L405 _protected prototype_ `const Frontend::FTemplateVertexMetadata* GetConstTemplateMetadata() const;`
- L406 _protected prototype_ `Frontend::FTemplateVertexMetadata* GetTemplateMetadata() const;`
- L408 _protected member_ `TSharedPtr<SCheckBox> ConstructorPinCheckbox;`
- L411 _protected prototype_ `void AddAdvancedPinRow(IDetailLayoutBuilder& InDetailLayout);`
- L412 _protected prototype_ `ECheckBoxState OnGetAdvancedPinCheckboxState(TWeakObjectPtr<UMetasoundEditorGraphVertex> InGraphMember) const;`
- L413 _protected prototype_ `void OnAdvancedPinStateChanged(TWeakObjectPtr<UMetasoundEditorGraphVertex> InGraphMember, ECheckBoxState InNewState);`
- L415 _protected member_ `TSharedPtr<SCheckBox> AdvancedPinCheckbox;`

#### class `Metasound::Editor::FMetasoundInputDetailCustomization`  
`class FMetasoundInputDetailCustomization : public FMetasoundVertexDetailCustomization`  
_L420-431_
- inherits: `FMetasoundVertexDetailCustomization`
- L423 _public prototype_ `virtual ~FMetasoundInputDetailCustomization() = default;`
- L425 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayout) override;`
- L426 _public prototype_ `virtual void ConfigureLiteralCustomization(FMetasoundDefaultLiteralCustomizationBase& InLiteralCustomization) override;`
- L427 _public prototype_ `virtual TAttribute<bool> GetEnabled() const override;`
- L430 _private member_ `TAttribute<bool> Enabled;`

#### class `Metasound::Editor::FMetasoundVariableDetailCustomization`  
`class FMetasoundVariableDetailCustomization : public FMetasoundMemberDetailCustomization`  
_L433-436_
- inherits: `FMetasoundMemberDetailCustomization`
- L435 _private prototype_ `EVisibility GetDefaultVisibility() const override;`

#### class `Metasound::Editor::FMetaSoundNodeExtensionHandler`  
`class FMetaSoundNodeExtensionHandler : public IDetailPropertyExtensionHandler`  
_L440-446_
- inherits: `IDetailPropertyExtensionHandler`
- L444 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const override;` — IDetailPropertyExtensionHandler interface
- L445 _public prototype_ `virtual void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle) override;`

#### Free symbols / members of external scopes

- L39 _macro_ `#define LOCTEXT_NAMESPACE "MetaSoundEditor"`
- L42 _namespace_ `namespace Metasound`
- L44 _namespace_ `namespace Editor` (scope `Metasound`)
- L167 _namespace_ `namespace MemberCustomizationStyle` (scope `Metasound::Editor`)
- L170 _variable_ `static constexpr float DetailsTitleMaxWidth = 300.f;` (scope `Metasound::Editor::MemberCustomizationStyle`) — Maximum size of the details title panel
- L172 _variable_ `static constexpr float DetailsTitleWrapPadding = 32.0f;` (scope `Metasound::Editor::MemberCustomizationStyle`) — magic number retrieved from SGraphNodeComment::GetWrapAt()
- L174 _variable_ `static const FText DataTypeNameText = LOCTEXT("Node_Da` (scope `Metasound::Editor::MemberCustomizationStyle`)
- L175 _variable_ `static const FText DefaultPropertyText = LOCTEXT("Node_De` (scope `Metasound::Editor::MemberCustomizationStyle`)
- L438 _typedef_ `using FMetasoundOutputDetailCustomization = FMetasoundVertexDetailCustomization;` (scope `Metasound::Editor`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundPinAudioInspector.h` (Private)


#### class `Metasound::Editor::FMetasoundPinAudioInspector`  
`class FMetasoundPinAudioInspector`  
_L23-40_
- L26 _public prototype_ `explicit FMetasoundPinAudioInspector(FEdGraphPinReference InPinRef);`
- L27 _public prototype_ `virtual ~FMetasoundPinAudioInspector();`
- L29 _public prototype_ `TSharedPtr<SMetasoundPinAudioInspector> GetWidget();`
- L32 _private prototype_ `const UMetasoundEditorGraphNode& GetReroutedNode() const;`
- L33 _private prototype_ `FGraphConnectionManager* GetConnectionManager();`
- L35 _private member_ `UEdGraphPin* GraphPinObj = nullptr;`
- L37 _private member_ `TSharedPtr<AudioWidgets::FAudioOscilloscope> Oscilloscope = nullptr;`
- L38 _private member_ `TSharedPtr<SMetasoundPinAudioInspector> PinAudioInspectorWidget = nullptr;`
- L39 _private member_ `FGuid AnalyzerInstanceID;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L12 _namespace_ `namespace AudioWidgets`
- L19 _namespace_ `namespace Metasound`
- L21 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundActionMenu.h` (Private)


#### class `Metasound::Editor::SMetasoundActionMenuExpanderArrow`  
`class SMetasoundActionMenuExpanderArrow : public SExpanderArrow`  
_L27-43_
- inherits: `SExpanderArrow`
- desc: Custom expander to specify our desired padding
- L29 _private function_ `SLATE_BEGIN_ARGS(SMetasoundActionMenuExpanderArrow)`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const FCustomExpanderData& ActionMenuData);`
- L40 _private prototype_ `FMargin GetCustomIndentPadding() const;`
- L42 _private member_ `TWeakPtr<FEdGraphSchemaAction> ActionPtr;`

#### class `Metasound::Editor::SMetasoundActionMenu`  
`class SMetasoundActionMenu : public SBorder`  
_L45-91_
- inherits: `SBorder`
- L49 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FClosedReason, bool , bool , bool );` — Delegate for the OnCloseReason event which is always raised when the SMetasoundActionMenu closes
- L51 _public function_ `SLATE_BEGIN_ARGS(SMetasoundActionMenu) : _Graph(static_cast<UEdGraph*>(nullptr)) , _NewNodePosition(FVector2f::ZeroVector) , _AutoExpandActionMenu(false)`
- L57 _public prototype_ `SLATE_ARGUMENT(UEdGraph*, Graph) SLATE_ARGUMENT(FDeprecateSlateVector2D, NewNodePosition) SLATE_ARGUMENT(TArray<UEdGraphPin*>, DraggedFromPins) SLATE_ARGUMENT(SGraphEditor::FActionMenuClosed, OnClosedCallback) SLATE_ARGUMENT(bool, AutoExpandActionMenu) SLATE_EVENT(FClosedReason, OnCloseReason) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L67 _public prototype_ `~SMetasoundActionMenu();`
- L69 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();`
- L72 _protected prototype_ `void OnActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& SelectedAction, ESelectInfo::Type InSelectionType);`
- L74 _protected prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(struct FCreateWidgetForActionData* const InCreateData);`
- L77 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);` — Callback used to populate all actions list in SGraphActionMenu
- L80 _private member_ `UEdGraph* Graph = nullptr;`
- L81 _private member_ `bool bAutoExpandActionMenu = false;`
- L82 _private member_ `bool bActionExecuted = false;`
- L84 _private member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L85 _private member_ `FDeprecateSlateVector2D NewNodePosition = FVector2f::ZeroVector;`
- L87 _private member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L88 _private member_ `FClosedReason OnCloseReasonCallback;`
- L90 _private member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Metasound`
- L24 _namespace_ `namespace Editor` (scope `Metasound`)
- L49 _delegate_ `DECLARE_DELEGATE_ThreeParams(FClosedReason, bool , bool , bool );` — Delegate for the OnCloseReason event which is always raised when the SMetasoundActionMenu closes

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundFilterFrequencyResponsePlots.h` (Private)


#### class `Metasound::Editor::SMetaSoundFilterFrequencyResponsePlot`  
`class SMetaSoundFilterFrequencyResponsePlot : public SCompoundWidget`  
_L22-52_
- inherits: `SCompoundWidget`
- desc: Abstract class implementing shared functionality for any Metasound basic filter. Allows for displaying a frequency response plot of the filter.
- L25 _public prototype_ `void Construct();`
- L26 _public prototype_ `virtual ~SMetaSoundFilterFrequencyResponsePlot();`
- L30 _protected prototype_ `virtual bool UpdateFilterParams() = 0;` — Update function for derived classes to update their state each frame. Implementations should return true if they have the required information to plot a frequency response, or false otherwise.
- L33 _protected prototype_ `virtual void ArrayCalculateFilterResponseInPlace(TArrayView<float> InOutComplexValues) const = 0;` — Derived classes should apply the filter transfer function to each z-domain value in the given array (complex numbers given as interleaved floats).
- L36 _protected function_ `virtual void ExtendSpectrumPlotContextMenu(FMenuBuilder& MenuBuilder)` — Derived classes can optionally add items to the spectrum plot menu by overriding this member function.
- L39 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L42 _protected member_ `static const float SampleRate;`
- L45 _private prototype_ `FAudioPowerSpectrumData GetAudioSpectrumData();`
- L47 _private member_ `TSharedPtr<SAudioSpectrumPlot> FrequencyResponsePlot;`
- L48 _private member_ `TSharedPtr<const FExtensionBase> ContextMenuExtension;`
- L49 _private member_ `TArray<float> CenterFrequencies;`
- L50 _private member_ `TArray<float> SquaredMagnitudes;`
- L51 _private member_ `bool bHasFilterParams = false;`

#### class `Metasound::Editor::SMetaSoundBiquadFilterFrequencyResponsePlot`  
`class SMetaSoundBiquadFilterFrequencyResponsePlot : public SMetaSoundFilterFrequencyResponsePlot`  
_L55-79_
- inherits: `SMetaSoundFilterFrequencyResponsePlot`
- L58 _public function_ `SLATE_BEGIN_ARGS(SMetaSoundBiquadFilterFrequencyResponsePlot)`
- L60 _public prototype_ `SLATE_ATTRIBUTE(TOptional<Audio::EBiquadFilter::Type>, FilterType) SLATE_ATTRIBUTE(TOptional<float>, CutoffFrequency) SLATE_ATTRIBUTE(TOptional<float>, Bandwidth) SLATE_ATTRIBUTE(TOptional<float>, GainDb) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L69 _protected prototype_ `virtual bool UpdateFilterParams() override;`
- L70 _protected prototype_ `virtual void ArrayCalculateFilterResponseInPlace(TArrayView<float> InOutComplexValues) const override;`
- L73 _private member_ `Audio::FBiquadFilter Filter;`
- L75 _private member_ `TAttribute<TOptional<Audio::EBiquadFilter::Type>> FilterType;`
- L76 _private member_ `TAttribute<TOptional<float>> CutoffFrequency;`
- L77 _private member_ `TAttribute<TOptional<float>> Bandwidth;`
- L78 _private member_ `TAttribute<TOptional<float>> GainDb;`

#### class `Metasound::Editor::SMetaSoundLadderFilterFrequencyResponsePlot`  
`class SMetaSoundLadderFilterFrequencyResponsePlot : public SMetaSoundFilterFrequencyResponsePlot`  
_L82-102_
- inherits: `SMetaSoundFilterFrequencyResponsePlot`
- L85 _public function_ `SLATE_BEGIN_ARGS(SMetaSoundLadderFilterFrequencyResponsePlot)`
- L87 _public prototype_ `SLATE_ATTRIBUTE(TOptional<float>, CutoffFrequency) SLATE_ATTRIBUTE(TOptional<float>, Resonance) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L94 _protected prototype_ `virtual bool UpdateFilterParams() override;`
- L95 _protected prototype_ `virtual void ArrayCalculateFilterResponseInPlace(TArrayView<float> InOutComplexValues) const override;`
- L98 _private member_ `Audio::FLadderFilter Filter;`
- L100 _private member_ `TAttribute<TOptional<float>> CutoffFrequency;`
- L101 _private member_ `TAttribute<TOptional<float>> Resonance;`

#### class `Metasound::Editor::SMetaSoundOnePoleHighPassFilterFrequencyResponsePlot`  
`class SMetaSoundOnePoleHighPassFilterFrequencyResponsePlot : public SMetaSoundFilterFrequencyResponsePlot`  
_L105-122_
- inherits: `SMetaSoundFilterFrequencyResponsePlot`
- L108 _public function_ `SLATE_BEGIN_ARGS(SMetaSoundOnePoleHighPassFilterFrequencyResponsePlot)`
- L110 _public prototype_ `SLATE_ATTRIBUTE(TOptional<float>, CutoffFrequency) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L116 _protected prototype_ `virtual bool UpdateFilterParams() override;`
- L117 _protected prototype_ `virtual void ArrayCalculateFilterResponseInPlace(TArrayView<float> InOutComplexValues) const override;`
- L120 _private member_ `Audio::FInterpolatedHPF Filter;`
- L121 _private member_ `TAttribute<TOptional<float>> CutoffFrequency;`

#### class `Metasound::Editor::SMetaSoundOnePoleLowPassFilterFrequencyResponsePlot`  
`class SMetaSoundOnePoleLowPassFilterFrequencyResponsePlot : public SMetaSoundFilterFrequencyResponsePlot`  
_L125-142_
- inherits: `SMetaSoundFilterFrequencyResponsePlot`
- L128 _public function_ `SLATE_BEGIN_ARGS(SMetaSoundOnePoleLowPassFilterFrequencyResponsePlot)`
- L130 _public prototype_ `SLATE_ATTRIBUTE(TOptional<float>, CutoffFrequency) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L136 _protected prototype_ `virtual bool UpdateFilterParams() override;`
- L137 _protected prototype_ `virtual void ArrayCalculateFilterResponseInPlace(TArrayView<float> InOutComplexValues) const override;`
- L140 _private member_ `Audio::FInterpolatedLPF Filter;`
- L141 _private member_ `TAttribute<TOptional<float>> CutoffFrequency;`

#### class `Metasound::Editor::SMetaSoundStateVariableFilterFrequencyResponsePlot`  
`class SMetaSoundStateVariableFilterFrequencyResponsePlot : public SMetaSoundFilterFrequencyResponsePlot`  
_L145-179_
- inherits: `SMetaSoundFilterFrequencyResponsePlot`
- L148 _public prototype_ `SMetaSoundStateVariableFilterFrequencyResponsePlot();`
- L150 _public function_ `SLATE_BEGIN_ARGS(SMetaSoundStateVariableFilterFrequencyResponsePlot)`
- L152 _public prototype_ `SLATE_ATTRIBUTE(TOptional<float>, CutoffFrequency) SLATE_ATTRIBUTE(TOptional<float>, Resonance) SLATE_ATTRIBUTE(TOptional<float>, BandStopControl) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UMetasoundEditorGraphNode* InMetaSoundNode);`
- L160 _protected prototype_ `virtual bool UpdateFilterParams() override;`
- L161 _protected prototype_ `virtual void ArrayCalculateFilterResponseInPlace(TArrayView<float> InOutComplexValues) const override;`
- L162 _protected prototype_ `virtual void ExtendSpectrumPlotContextMenu(FMenuBuilder& MenuBuilder) override;`
- L165 _private prototype_ `void BuildFilterOutputSubMenu(FMenuBuilder& SubMenu);`
- L167 _private member_ `static const FName LowPassFilter;`
- L168 _private member_ `static const FName HighPassFilter;`
- L169 _private member_ `static const FName BandPass;`
- L170 _private member_ `static const FName BandStop;`
- L172 _private member_ `TWeakObjectPtr<UMetasoundEditorGraphNode> MetaSoundNode;`
- L173 _private member_ `Audio::FStateVariableFilter Filter;`
- L174 _private member_ `FName DisplayedFilterResponse;`
- L176 _private member_ `TAttribute<TOptional<float>> CutoffFrequency;`
- L177 _private member_ `TAttribute<TOptional<float>> Resonance;`
- L178 _private member_ `TAttribute<TOptional<float>> BandStopControl;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Editor` (scope `Metasound`)
- L13 _prototype_ `TSharedRef<SWidget> CreateMetaSoundBiquadFilterGraphNodeVisualizationWidget(const FCreateGraphNodeVisualizationWidgetParams& InParams);` (scope `Metasound::Editor`)
- L14 _prototype_ `TSharedRef<SWidget> CreateMetaSoundLadderFilterGraphNodeVisualizationWidget(const FCreateGraphNodeVisualizationWidgetParams& InParams);` (scope `Metasound::Editor`)
- L15 _prototype_ `TSharedRef<SWidget> CreateMetaSoundOnePoleHighPassFilterGraphNodeVisualizationWidget(const FCreateGraphNodeVisualizationWidgetParams& InParams);` (scope `Metasound::Editor`)
- L16 _prototype_ `TSharedRef<SWidget> CreateMetaSoundOnePoleLowPassFilterGraphNodeVisualizationWidget(const FCreateGraphNodeVisualizationWidgetParams& InParams);` (scope `Metasound::Editor`)
- L17 _prototype_ `TSharedRef<SWidget> CreateMetaSoundStateVariableFilterGraphNodeVisualizationWidget(const FCreateGraphNodeVisualizationWidgetParams& InParams);` (scope `Metasound::Editor`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundGraphEnumPin.h` (Private)


#### class `Metasound::Editor::SMetasoundGraphEnumPin`  
`class SMetasoundGraphEnumPin : public TMetasoundGraphPin<SGraphPin>`  
_L21-47_
- inherits: `TMetasoundGraphPin<SGraphPin>`
- L23 _private function_ `SLATE_BEGIN_ARGS(SMetasoundGraphEnumPin)`
- L26 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L30 _private prototype_ `static TSharedPtr<const Metasound::Frontend::IEnumDataTypeInterface> FindEnumInterfaceFromPin(UEdGraphPin* InPin);`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L36 _private member_ `TSharedPtr<SPinComboBox> ComboBox;`
- L38 _private prototype_ `FString OnGetText() const;`
- L40 _private prototype_ `void GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes);`
- L42 _private prototype_ `void ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo);`
- L44 _private prototype_ `FText OnGetFriendlyName(int32 EnumIndex);`
- L46 _private prototype_ `FText OnGetTooltip(int32 EnumIndex);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L14 _namespace_ `namespace Frontend` (scope `Metasound`)
- L19 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundGraphNode.h` (Private)


#### class `Metasound::Editor::SMetaSoundGraphNode`  
`class SMetaSoundGraphNode : public SGraphNode`  
_L28-117_
- inherits: `SGraphNode`
- L31 _public function_ `SLATE_BEGIN_ARGS(SMetaSoundGraphNode)`
- L36 _public prototype_ `virtual ~SMetaSoundGraphNode();`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, class UEdGraphNode* InNode);`
- L41 _protected prototype_ `bool IsVariableAccessor() const;`
- L42 _protected prototype_ `bool IsVariableMutator() const;`
- L45 _protected prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;` — SGraphNode Interface
- L46 _protected prototype_ `virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;`
- L47 _protected prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;`
- L48 _protected prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* InPin) const override;`
- L49 _protected prototype_ `virtual void CreateStandardPinWidget(UEdGraphPin* InPin) override;`
- L50 _protected prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L51 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L52 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;`
- L53 _protected prototype_ `virtual const FSlateBrush* GetNodeBodyBrush() const override;`
- L54 _protected prototype_ `virtual FText GetNodeTooltip() const override;`
- L55 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleRightWidget() override;`
- L56 _protected prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`
- L57 _protected prototype_ `virtual FReply OnAddPin() override;`
- L58 _protected prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L59 _protected prototype_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;`
- L60 _protected prototype_ `virtual void GetOverlayBrushes(bool bSelected, const FVector2f& WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const override;`
- L61 _protected prototype_ `virtual void OnCommentBubbleToggled(bool bInCommentBubbleVisible) override;`
- L62 _protected prototype_ `virtual void OnCommentTextCommitted(const FText& NewComment, ETextCommit::Type CommitInfo) override;`
- L63 _protected prototype_ `virtual void OnAdvancedViewChanged(const ECheckBoxState NewCheckedState) override;`
- L65 _protected prototype_ `FLinearColor GetNodeTitleColorOverride() const;`
- L67 _protected prototype_ `FName GetLiteralDataType() const;`
- L68 _protected prototype_ `UMetasoundEditorGraphNode& GetMetaSoundNode() const;`
- L71 _public prototype_ `static void ExecuteTrigger(UMetasoundEditorGraphMemberDefaultLiteral& Literal);`
- L72 _public prototype_ `static TSharedRef<SWidget> CreateTriggerSimulationWidget(UMetasoundEditorGraphMemberDefaultLiteral& Literal, TAttribute<EVisibility>&& InVisibility, TAttribute<bool>&& InEnablement, const FText* InToolTip = nullptr);`
- L75 _private prototype_ `void BeginOrUpdateValueTransaction(TWeakObjectPtr<UMetasoundEditorGraphMember> GraphMemberPtr, TFunctionRef<void(const FGuid& , UMetasoundEditorGraphMember& )> SetValue);`
- L76 _private prototype_ `void FinalizeValueTransaction(TWeakObjectPtr<UMetasoundEditorGraphMember> GraphMemberPtr, TFunctionRef<void(const FGuid& , UMetasoundEditorGraphMember& , bool )> SetValue);`
- L78 _private prototype_ `TSharedRef<SWidget> CreateTitleIcon() const;`
- L81 _private prototype_ `TAttribute<bool> GetInputWidgetEnabled() const;` — Returns attribute that returns whether or not the input widget should be enabled.
- L84 _private prototype_ `FText GetInputWidgetTooltip() const;` — Returns the input widget tooltip text.
- L87 _private prototype_ `UMetasoundEditorGraphMember* GetMetaSoundMember();` — If this node represents a graph member node, returns corresponding member.
- L90 _private prototype_ `UMetasoundEditorGraphMemberNode* GetMetaSoundMemberNode() const;` — If this node represents a graph member node, returns cast node.
- L92 _private prototype_ `TAttribute<EVisibility> GetSimulationVisibilityAttribute() const;`
- L95 _private prototype_ `TSharedPtr<SWidget> CreateInputNodeContentArea(const FMetaSoundFrontendDocumentBuilder& InBuilder, TSharedRef<SHorizontalBox> ContentBox);` — Input node should be moved to own implementation
- L98 _private member_ `TSharedPtr<SAudioInputWidget> FloatInputWidget;` — Slider widget for float input
- L101 _private member_ `TSharedPtr<SAudioMaterialButton> MaterialButtonWidget;` — Button Widget for bool input.
- L104 _private member_ `FDelegateHandle InputButtonOnStateChangedDelegateHandle;` — Handle for on state changed delegate for Button
- L107 _private member_ `FDelegateHandle InputSliderOnValueChangedDelegateHandle;` — Handle for on value changed delegate for input slider
- L110 _private member_ `FDelegateHandle InputSliderOnRangeChangedDelegateHandle;` — Handle for on input slider range changed
- L114 _private member_ `bool bIsInputWidgetTransacting = false;` — Whether the input widget is currently transacting for keeping track of transaction state across delegates to only commit transaction on value commit
- L116 _private member_ `EMetasoundFrontendClassType ClassType;`

#### class `Metasound::Editor::SMetaSoundGraphNodeKnot`  
`class SMetaSoundGraphNodeKnot : public SGraphNodeKnot`  
_L119-135_
- inherits: `SGraphNodeKnot`
- L122 _public function_ `SLATE_BEGIN_ARGS(SMetaSoundGraphNode)`
- L126 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UEdGraphNode* InNode);`
- L130 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L131 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty) override;`
- L133 _public prototype_ `UMetasoundEditorGraphNode& GetMetaSoundNode();`
- L134 _public prototype_ `const UMetasoundEditorGraphNode& GetMetaSoundNode() const;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace Metasound`
- L26 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundGraphNodeComment.h` (Private)


#### class `Metasound::Editor::SMetasoundGraphNodeComment`  
`class SMetasoundGraphNodeComment : public SGraphNodeComment`  
_L11-17_
- inherits: `SGraphNodeComment`
- L15 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;` — SNodePanel::SNode interface

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundGraphPin.h` (Private)


#### class `Metasound::Editor::TMetasoundGraphPin`  
`template <typename ParentPinType> class TMetasoundGraphPin : public ParentPinType`  
_L39-535_
- inherits: `ParentPinType`
- L41 _private member_ `TSharedPtr<SMetasoundPinValueInspector> PinInspector;`
- L43 _private member_ `TSharedPtr<FMetasoundPinAudioInspector> PinAudioInspector;`
- L46 _private member_ `mutable TWeakObjectPtr<UMetaSoundBuilderBase> BuilderPtr;` — Cached builder pointer for fast access
- L49 _protected function_ `virtual bool CanInspectPin(const UEdGraphPin* InPin)`
- L54 _protected function_ `static TWeakPtr<FPinValueInspectorTooltip> OpenPinInspector(UEdGraphPin& InPin, TSharedPtr<SMetasoundPinValueInspector>& OutPinInspector)`
- L67 _protected function_ `void UpdatePinInspector( UEdGraphPin& InPin, const bool bIsHoveringPin, TSharedPtr<SMetasoundPinValueInspector>& OutPinInspector, TWeakPtr<FPinValueInspectorTooltip>& OutInspectorTooltip, TFunctionRef<void(FVector2f&)> InGetTooltipLocation)`
- L123 _protected function_ `static TWeakPtr<FPinValueInspectorTooltip> OpenPinAudioInspector(UEdGraphPin& InPin, TSharedPtr<FMetasoundPinAudioInspector>& OutPinAudioInspector)`
- L137 _protected function_ `void UpdatePinAudioInspector(UEdGraphPin& InPin, const bool bIsHoveringPin, TSharedPtr<FMetasoundPinAudioInspector>& OutPinAudioInspector, TWeakPtr<FPinValueInspectorTooltip>& OutInspectorTooltip, TFunctionRef<void(FVector2f&)> InGetTooltipLocation)`
- L184 _protected function_ `void CacheAccessType()`
- L218 _protected function_ `void CacheNodeOffset(const FGeometry& AllottedGeometry)`
- L225 _protected member_ `EMetasoundFrontendVertexAccessType AccessType = EMetasoundFrontendVertexAccessType::Unset;`
- L228 _public function_ `SLATE_BEGIN_ARGS(TMetasoundGraphPin<ParentPinType>)`
- L233 _public prototype_ `virtual ~TMetasoundGraphPin() = default;`
- L235 _public function_ `const UMetasoundEditorGraphNode* GetOwningMetaSoundNode() const`
- L246 _public function_ `UMetaSoundBuilderBase& GetBuilderChecked() const`
- L253 _public function_ `UMetaSoundBuilderBase* GetBuilder() const`
- L270 _public function_ `const FMetasoundFrontendNode* GetFrontendNode() const`
- L286 _public function_ `const FMetasoundFrontendVertex* GetFrontendVertex() const`
- L301 _public function_ `const FMetasoundFrontendNode& GetFrontendNodeChecked() const`
- L308 _public function_ `bool ShowDefaultValueWidget() const`
- L337 _public function_ `TSharedRef<SWidget> CreateResetToDefaultWidget()`
- L440 _public function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override`
- L473 _public function_ `virtual const FSlateBrush* GetPinIcon() const override`
- L497 _public function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override`

#### class `Metasound::Editor::SMetasoundGraphPin`  
`class SMetasoundGraphPin : public TMetasoundGraphPin<SGraphPin>`  
_L537-547_
- inherits: `TMetasoundGraphPin<SGraphPin>`
- L540 _public prototype_ `virtual ~SMetasoundGraphPin() = default;`
- L542 _public function_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`

#### class `Metasound::Editor::SMetasoundGraphPinBool`  
`class SMetasoundGraphPinBool : public TMetasoundGraphPin<SGraphPinBool>`  
_L549-559_
- inherits: `TMetasoundGraphPin<SGraphPinBool>`
- L552 _public prototype_ `virtual ~SMetasoundGraphPinBool() = default;`
- L554 _public function_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`

#### class `Metasound::Editor::SMetasoundGraphPinFloat`  
`class SMetasoundGraphPinFloat : public TMetasoundGraphPin<SGraphPinNum<float>>`  
_L561-571_
- inherits: `TMetasoundGraphPin<SGraphPinNum<float>>`
- L564 _public prototype_ `virtual ~SMetasoundGraphPinFloat() = default;`
- L566 _public function_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`

#### class `Metasound::Editor::SMetasoundGraphPinInteger`  
`class SMetasoundGraphPinInteger : public TMetasoundGraphPin<SGraphPinInteger>`  
_L573-583_
- inherits: `TMetasoundGraphPin<SGraphPinInteger>`
- L576 _public prototype_ `virtual ~SMetasoundGraphPinInteger() = default;`
- L578 _public function_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`

#### class `Metasound::Editor::SMetasoundGraphPinObject`  
`class SMetasoundGraphPinObject : public TMetasoundGraphPin<SGraphPinObject>`  
_L585-595_
- inherits: `TMetasoundGraphPin<SGraphPinObject>`
- L588 _public prototype_ `virtual ~SMetasoundGraphPinObject() = default;`
- L590 _public function_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`

#### class `Metasound::Editor::SMetasoundGraphPinString`  
`class SMetasoundGraphPinString : public TMetasoundGraphPin<SGraphPinString>`  
_L597-607_
- inherits: `TMetasoundGraphPin<SGraphPinString>`
- L600 _public prototype_ `virtual ~SMetasoundGraphPinString() = default;`
- L602 _public function_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`

#### class `Metasound::Editor::SMetaSoundGraphPinKnot`  
`class SMetaSoundGraphPinKnot : public TMetasoundGraphPin<SGraphPinKnot>`  
_L609-626_
- inherits: `TMetasoundGraphPin<SGraphPinKnot>`
- L612 _public prototype_ `virtual ~SMetaSoundGraphPinKnot() = default;`
- L614 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L616 _public prototype_ `virtual FSlateColor GetPinColor() const override;`
- L618 _public prototype_ `virtual const FSlateBrush* GetPinIcon() const override;`
- L621 _protected prototype_ `virtual bool CanInspectPin(const UEdGraphPin* InPin) override;`
- L623 _protected prototype_ `void CacheHasRequiredConnections();`
- L625 _protected member_ `bool bHasRequiredConnections = false;`

#### Free symbols / members of external scopes

- L31 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundEditor"`
- L34 _namespace_ `namespace Metasound`
- L36 _namespace_ `namespace Editor` (scope `Metasound`)
- L344 _function_ `` (scope `Metasound::Editor::TMetasoundGraphPin::CreateResetToDefaultWidget`)
- L510 _function_ `` (scope `Metasound::Editor::TMetasoundGraphPin::Tick`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundInputBrowser.h` (Private)


#### struct `Metasound::Editor::FInputBrowserColumnDef`  
`struct FInputBrowserColumnDef`  
_L21-31_
- desc: Describes a single column in the MetaSound Input Browser (one per unique input name across all loaded assets).
- L23 _public member_ `FName InputName;`
- L24 _public member_ `FName TypeName;`
- L25 _public member_ `EMetasoundFrontendLiteralType LiteralType = EMetasoundFrontendLiteralType::None;`
- L27 _public function_ `bool operator==(const FInputBrowserColumnDef& Other) const`

#### struct `Metasound::Editor::FInputBrowserCellData`  
`struct FInputBrowserCellData`  
_L34-41_
- desc: Per-cell data for a single (asset, input) pair.
- L36 _public member_ `FMetasoundFrontendLiteral Value;`
- L37 _public member_ `FGuid NodeID;`
- L38 _public member_ `bool bIsPreset = false;`
- L39 _public member_ `bool bOverridesDefault = false;`
- L40 _public member_ `bool bInputExists = false;`

#### struct `Metasound::Editor::FInputBrowserRow`  
`struct FInputBrowserRow`  
_L44-62_
- desc: One row in the Input Browser, representing a single MetaSound asset.
- L46 _public member_ `TWeakObjectPtr<UObject> Asset;`
- L47 _public member_ `FString AssetName;`
- L48 _public member_ `TMap<FName, FInputBrowserCellData> Cells;`
- L49 _public member_ `bool bHasVisibleInputs = true;`
- L52 _public prototype_ `IMetaSoundDocumentInterface* GetDocumentInterface() const;` — Returns the document interface for this row's asset, or null if invalid.
- L55 _public prototype_ `static void ReadCellData( FInputBrowserCellData& OutCell, const FMetasoundFrontendClassInput& Input, const FMetaSoundFrontendPresetTemplate* PresetTemplate);` — Populate a cell's data from a class input and optional preset template.
- L61 _public prototype_ `static TArray<FInputBrowserColumnDef> BuildRow(TSharedPtr<FInputBrowserRow>& OutRow, UObject* InAsset);` — Populate this row's cell data from the given MetaSound asset. Returns the set of column defs found.

#### class `Metasound::Editor::SMetasoundInputBrowser`  
`class SMetasoundInputBrowser : public SCompoundWidget`  
_L68-160_
- inherits: `SCompoundWidget`
- desc: A bulk-editing tool for MetaSound input values, similar to the Property Matrix. Displays a table with rows = assets and columns = inputs.
- L71 _public member_ `static const FName TabId;`
- L73 _public function_ `SLATE_BEGIN_ARGS(SMetasoundInputBrowser)`
- L74 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L77 _public prototype_ `virtual ~SMetasoundInputBrowser();`
- L79 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L82 _public prototype_ `void SetAssets(const TArray<TWeakObjectPtr<UObject>>& InAssets);` — Populate the browser with the given MetaSound assets.
- L86 _private prototype_ `void RebuildData();` — Rebuild rows and column union from the current asset set.
- L89 _private prototype_ `void RebuildColumns();` — Rebuild the SHeaderRow columns from FilteredColumns.
- L92 _private prototype_ `void ApplyFilters();` — Apply name/type filters to AllColumns to produce FilteredColumns.
- L97 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FInputBrowserRow> InRow, const TSharedRef<STableViewBase>& OwnerTable);` — SListView callbacks.
- L100 _private prototype_ `TSharedRef<SWidget> GenerateCellWidget(const TSharedRef<FInputBrowserRow>& InRow, const FInputBrowserColumnDef& InColumnDef);` — Generate a cell widget for a given row and column.
- L103 _private prototype_ `void CommitCellValue(const TSharedRef<FInputBrowserRow>& InRow, FName InputName, const FMetasoundFrontendLiteral& NewValue);` — Commit an edited value back to the asset.
- L106 _private prototype_ `void ResetToDefault(const TSharedRef<FInputBrowserRow>& InRow, FName InputName);` — Reset a preset input to its inherited default value.
- L109 _private prototype_ `void BeginOverride(const TSharedRef<FInputBrowserRow>& InRow, FName InputName);` — Begin overriding an inherited preset input (copies the inherited value as an explicit override).
- L112 _private prototype_ `void OnNameFilterChanged(const FText& InText);` — Filter callback.
- L115 _private prototype_ `TSharedPtr<SWidget> OnAssetContextMenuOpening();` — Context menu for right-clicking on an asset row.
- L118 _private prototype_ `void RefreshRow(const TSharedRef<FInputBrowserRow>& InRow);` — Refresh a single row's cell data from its asset.
- L121 _private prototype_ `void RefreshAllRows();` — Refresh all rows from their assets. Called when the widget regains focus.
- L124 _private prototype_ `void SubscribeToBuilder(FMetaSoundFrontendDocumentBuilder& Builder, const TSharedRef<FInputBrowserRow>& InRow);` — Subscribe to OnInputDefaultChanged on a builder if not already subscribed.
- L127 _private prototype_ `void ScanAndSubscribeBuilders();` — Scan all rows for existing builders and subscribe to their delegates.
- L130 _private prototype_ `void UnsubscribeAllBuilders();` — Unsubscribe from all builder delegates and clear the subscriptions map.
- L133 _private prototype_ `void TogglePin(FName InputName);` — Pin column callbacks.
- L134 _private prototype_ `bool IsPinned(FName InputName) const;`
- L135 _private prototype_ `TSharedRef<ITableRow> OnGeneratePinRow(TSharedPtr<FInputBrowserColumnDef> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L138 _private member_ `TArray<TWeakObjectPtr<UObject>> SourceAssets;` — Data
- L139 _private member_ `TArray<TSharedPtr<FInputBrowserRow>> Rows;`
- L140 _private member_ `TArray<FInputBrowserColumnDef> AllColumns;`
- L141 _private member_ `TArray<FInputBrowserColumnDef> FilteredColumns;`
- L144 _private member_ `FString NameFilter;` — Filter state
- L147 _private member_ `TSet<FName> PinnedInputNames;` — Pin state
- L148 _private member_ `bool bHasExplicitPins = false;` — When false, all columns are shown
- L149 _private member_ `TArray<TSharedPtr<FInputBrowserColumnDef>> FilteredPinListItems;`
- L153 _private member_ `TMap<FObjectKey, FDelegateHandle> SubscribedBuilders;` — Assets whose builders we've subscribed to, mapped to delegate handles for cleanup. Keyed on FObjectKey (not builder pointer) so we don't hold raw pointers that could dangle.
- L154 _private member_ `FDelegateHandle PostUndoRedoHandle;`
- L157 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;` — Widgets
- L158 _private member_ `TSharedPtr<SListView<TSharedPtr<FInputBrowserRow>>> ListView;`
- L159 _private member_ `TSharedPtr<SListView<TSharedPtr<FInputBrowserColumnDef>>> PinListView;`

#### class `Metasound::Editor::SMetasoundInputBrowserTableRow`  
`class SMetasoundInputBrowserTableRow : public SMultiColumnTableRow<TSharedPtr<FInputBrowserRow>>`  
_L163-177_
- inherits: `SMultiColumnTableRow<TSharedPtr<FInputBrowserRow>>`
- desc: Multi-column table row for the Input Browser.
- L166 _public function_ `SLATE_BEGIN_ARGS(SMetasoundInputBrowserTableRow)`
- L167 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FInputBrowserRow>, RowData) SLATE_ARGUMENT(SMetasoundInputBrowser*, Browser) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable);`
- L172 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L175 _private member_ `TSharedPtr<FInputBrowserRow> RowData;`
- L176 _private member_ `SMetasoundInputBrowser* Browser = nullptr;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Metasound`
- L17 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundPalette.h` (Private)


#### class `SMetasoundPalette`  
`class SMetasoundPalette : public SGraphPalette`  
_L12-23_
- inherits: `SGraphPalette`
- L15 _public function_ `SLATE_BEGIN_ARGS( SMetasoundPalette )`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _protected prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;` — Callback used to populate all actions list in SGraphActionMenu

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundPinAudioInspector.h` (Private)


#### class `Metasound::Editor::SMetasoundPinAudioInspector`  
`class SMetasoundPinAudioInspector : public SPinValueInspector`  
_L15-27_
- inherits: `SPinValueInspector`
- L19 _public function_ `SLATE_BEGIN_ARGS(SMetasoundPinAudioInspector) : _VisualizationWidget(SNullWidget::NullWidget)`
- L23 _public prototype_ `SLATE_ARGUMENT(TSharedRef<SWidget>, VisualizationWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L11 _namespace_ `namespace Metasound`
- L13 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundPinValueInspector.h` (Private)


#### struct `Metasound::Editor::FMetasoundNumericDebugLineItem`  
`struct FMetasoundNumericDebugLineItem : public FDebugLineItem`  
_L33-103_
- inherits: `FDebugLineItem`
- L35 _public typedef_ `using FGetValueStringFunction = TFunction<FString(const FGraphConnectionManager&, const FGuid& , const FName )>;`
- L39 _private member_ `UEdGraphPin* GraphPinObj = nullptr;` — The GraphPin that this debug line is reporting.
- L42 _private member_ `FGetValueStringFunction GetValueStringFunction;` — Function used to get the string value from the connection manager.
- L44 _private prototype_ `FColorPickerArgs InitPickerArgs();`
- L47 _protected member_ `TArray<FMetasoundFrontendLiteral> ColorLiterals;`
- L49 _protected member_ `FString Message;`
- L50 _protected member_ `FText DisplayName;`
- L52 _protected member_ `TSharedPtr<SWidget> ValueWidget;`
- L54 _protected member_ `bool bIsValueColorizationEnabled = false;`
- L57 _public prototype_ `FMetasoundNumericDebugLineItem(UEdGraphPin* InGraphPinObj, FGetValueStringFunction&& InGetValueStringFunction);`
- L58 _public prototype_ `virtual ~FMetasoundNumericDebugLineItem() = default;`
- L60 _public prototype_ `const UMetasoundEditorGraphNode* GetReroutedNode() const;`
- L62 _public prototype_ `const UMetasoundEditorGraphNode& GetReroutedNodeChecked() const;`
- L64 _public prototype_ `UObject* GetOutermostObject();`
- L66 _public prototype_ `Frontend::FConstOutputHandle GetConstReroutedOutputHandle() const;`
- L68 _public prototype_ `Frontend::FConstGraphHandle GetConstGraphHandle() const;`
- L70 _public prototype_ `const FGraphConnectionManager* GetConnectionManager() const;`
- L72 _public prototype_ `const FMetasoundFrontendEdgeStyle* FindConstEdgeStyle() const;`
- L74 _public prototype_ `void Update();`
- L76 _public prototype_ `virtual FText GetDescription() const override;`
- L78 _public prototype_ `virtual TSharedRef<SWidget> GenerateNameWidget(TSharedPtr<FString> InSearchString) override;`
- L80 _public prototype_ `virtual TSharedRef<SWidget> GenerateValueWidget(TSharedPtr<FString> InSearchString) override;`
- L83 _protected prototype_ `virtual void AddValueColorizationWidgets(TSharedPtr<SVerticalBox> VerticalBox);`
- L85 _protected prototype_ `virtual FDebugLineItem* Duplicate() const override;`
- L87 _protected prototype_ `virtual bool Compare(const FDebugLineItem* BaseOther) const override;`
- L89 _protected prototype_ `virtual uint32 GetHash() const override;`
- L92 _private prototype_ `FLinearColor GetEdgeStyleColorAtIndex(int32 InIndex) const;`
- L93 _private prototype_ `FMetasoundFrontendEdgeStyle* FindOrAddEdgeStyle();`
- L94 _private prototype_ `FMetasoundFrontendEdgeStyle* FindEdgeStyle();`
- L95 _private prototype_ `bool GetNodeIDAndOutputName(FGuid& OutNodeID, FName& OutName) const;`
- L97 _private prototype_ `void DisableValueColorization();`
- L98 _private prototype_ `void EnableValueColorization();`
- L100 _private prototype_ `void OnColorCommitted(FLinearColor InColor, int32 InIndex);`
- L101 _private prototype_ `FReply OnColorBoxClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, const FLinearColor& InInitColor, int32 InIndex);`
- L102 _private prototype_ `void OnValueCommitted(const FText& InValueText, FMetasoundFrontendLiteral& OutNewLiteral, int32 InIndex);`

#### class `Metasound::Editor::SMetasoundPinValueInspector`  
`class SMetasoundPinValueInspector : public SPinValueInspector`  
_L105-120_
- inherits: `SPinValueInspector`
- L107 _private member_ `TSharedPtr<FMetasoundNumericDebugLineItem> LineItem;`
- L110 _public function_ `SLATE_BEGIN_ARGS(SMetasoundPinValueInspector)`
- L113 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L117 _public prototype_ `void UpdateMessage();`
- L119 _public prototype_ `virtual void PopulateTreeView() override;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L29 _namespace_ `namespace Metasound`
- L31 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundSpectrumAnalyzerGraphNode.h` (Private)


#### class `Metasound::Editor::SMetaSoundSpectrumAnalyzerGraphNode`  
`class SMetaSoundSpectrumAnalyzerGraphNode : public SMetaSoundGraphNode`  
_L14-29_
- inherits: `SMetaSoundGraphNode`
- L17 _public prototype_ `virtual ~SMetaSoundSpectrumAnalyzerGraphNode();`
- L20 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L24 _protected prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L27 _private member_ `TSharedPtr<AudioWidgets::FAudioSpectrumAnalyzer> SpectrumAnalyzer;`
- L28 _private member_ `FGuid AnalyzerInstanceID;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AudioWidgets`
- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/SMetasoundStats.h` (Private)


#### class `Metasound::Editor::SPageStats`  
`class SPageStats : public SVerticalBox`  
_L23-43_
- inherits: `SVerticalBox`
- desc: Widget for displaying page stats of a previewing MetaSound.
- L26 _public function_ `SLATE_BEGIN_ARGS(SPageStats)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `void SetExecVisibility(TAttribute<EVisibility> InVisibility);`
- L31 _public prototype_ `void Update(const FMetaSoundPageSettings* AuditionPageSettings, const FMetaSoundPageSettings* GraphPageSettings, const FSlateColor* ActiveColor);`
- L33 _public prototype_ `const FGuid& GetDisplayedPageID() const;`
- L34 _public prototype_ `FName GetDisplayedPageName() const;`
- L37 _private member_ `TSharedPtr<SImage> ExecImageWidget;`
- L38 _private member_ `TSharedPtr<STextBlock> GraphPageTextWidget;`
- L39 _private member_ `TSharedPtr<STextBlock> AuditionPageTextWidget;`
- L41 _private member_ `FGuid DisplayedPageID;`
- L42 _private member_ `FName DisplayedPageName;`

#### class `Metasound::Editor::SRenderStats`  
`class SRenderStats : public SVerticalBox`  
_L47-67_
- inherits: `SVerticalBox`
- desc: Widget for displaying render stats of a previewing MetaSound.
- L50 _public function_ `SLATE_BEGIN_ARGS( SRenderStats)`
- L51 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L54 _public prototype_ `void Update(bool bIsPlaying, double InDeltaTime, const UMetaSoundSource* InSource);`
- L57 _private member_ `TSharedPtr<STextBlock> AuditionPageWidget;`
- L58 _private member_ `TSharedPtr<STextBlock> AuditionPlatformWidget;`
- L59 _private member_ `TSharedPtr<STextBlock> PlayTimeWidget;`
- L60 _private member_ `TSharedPtr<STextBlock> RenderStatsCostWidget;`
- L61 _private member_ `TSharedPtr<STextBlock> RenderStatsCPUWidget;`
- L63 _private member_ `bool bPreviousIsPlaying = false;`
- L64 _private member_ `double MaxCPUCoreUtilization = 0.0;`
- L65 _private member_ `double PlayTime = 0.0;`
- L66 _private member_ `float MaxRelativeRenderCost = 0.f;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Metasound`
- L20 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/FindInMetasound.h` (Public)


#### class `Metasound::Editor::FFindInMetasoundResult`  
`class FFindInMetasoundResult`  
_L19-81_
- desc: Item that matched the search results
- L23 _public prototype_ `FFindInMetasoundResult(const FString& InResultName);` — Create a root (or only text) result
- L26 _public prototype_ `FFindInMetasoundResult(const FString& InResultName, TSharedPtr<FFindInMetasoundResult>& InParent, UClass* InClass, int InDuplicationIndex);` — Create a listing for a search result
- L29 _public prototype_ `FFindInMetasoundResult(const FString& InResultName, TSharedPtr<FFindInMetasoundResult>& InParent, UEdGraphPin* InPin);` — Create a listing for a pin result
- L32 _public prototype_ `FFindInMetasoundResult(const FString& InResultName, TSharedPtr<FFindInMetasoundResult>& InParent, UEdGraphNode* InNode);` — Create a listing for a node result
- L35 _public prototype_ `FReply OnClick(TWeakPtr<class FEditor> MetasoundEditor);` — Called when user clicks on the search item
- L38 _public prototype_ `FText GetCategory() const;` — Get Category for this search result
- L41 _public prototype_ `TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L44 _public prototype_ `FString GetCommentText() const;` — Gets the comment on this node if any
- L47 _public prototype_ `FText GetValueText();` — Gets the value of the pin or node if any
- L50 _public prototype_ `FText GetValueTooltipText();` — Gets the value tooltip (longer version of value text) of the pin or node if any
- L53 _public member_ `TArray<TSharedPtr<FFindInMetasoundResult>> Children;` — Any children listed under this category
- L56 _public member_ `TWeakPtr<FFindInMetasoundResult> Parent;` — Search result Parent
- L59 _public member_ `FString Value;` — The meta string that was stored in the asset registry for this item
- L62 _public member_ `int DuplicationIndex;` — The graph may have multiple instances of whatever we are looking for, this tells us which instance # we refer to
- L65 _public member_ `UClass* Class;` — The class this item refers to
- L68 _public member_ `FEdGraphPinReference Pin;` — The pin that this search result refers to
- L71 _public member_ `TWeakObjectPtr<UEdGraphNode> GraphNode;` — The graph node that this search result refers to (if not by asset registry or UK2Node)
- L74 _public member_ `FString CommentText;` — Display text for comment information
- L77 _public member_ `FText ValueText;` — Cache value text
- L80 _public prototype_ `static const UMetasoundEditorGraphMember* GetMetaSoundGraphMember(const UEdGraphNode* EdGraphNode);` — Helper function to get MetaSound graph member from an ed graph node

#### class `Metasound::Editor::SFindInMetasound`  
`class SFindInMetasound : public SCompoundWidget`  
_L85-156_
- inherits: `SCompoundWidget`
- desc: Widget for searching for items that are part of a UEdGraph
- L88 _public function_ `SLATE_BEGIN_ARGS(SFindInMetasound)`
- L89 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FEditor> InMetaSoundEditor);`
- L94 _public prototype_ `void FocusForUse();` — Focuses this widget's search box
- L96 _public prototype_ `void FocusForUse(const FString& NewSearchTerms);` — Focuses this widget's search box, and Initiates a search with given SearchTerms
- L99 _protected typedef_ `typedef TSharedPtr<FFindInMetasoundResult> FSearchResult;`
- L100 _protected typedef_ `typedef STreeView<FSearchResult> STreeViewType;`
- L103 _protected prototype_ `void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L106 _protected prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user changes commits text to the search box
- L109 _protected prototype_ `void OnGetChildren(FSearchResult InItem, TArray<FSearchResult>& OutChildren);` — Get the children of a row
- L112 _protected prototype_ `void OnTreeSelectionChanged(FSearchResult Item, ESelectInfo::Type SelectInfo);` — Called when user clicks on a new result
- L115 _protected prototype_ `void OnTreeSelectionDoubleClick(FSearchResult Item);` — Called when user double clicks on a new result
- L118 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSearchResult InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L121 _protected prototype_ `void InitiateSearch();` — Begins the search based on the SearchValue
- L124 _protected prototype_ `void MatchTokens(const TArray<FString>& Tokens);` — Find any results that contain all of the tokens
- L127 _protected prototype_ `void MatchTokensInGraph(const UEdGraph* Graph, const TArray<FString>& Tokens);` — Find any results that contain all of the tokens in provided graph and subgraphs
- L130 _protected prototype_ `static bool StringMatchesSearchTokens(const TArray<FString>& Tokens, const FString& ComparisonString);` — Determines if a string matches the search tokens
- L133 _protected member_ `TWeakPtr<class FEditor> MetaSoundEditorPtr;` — Pointer back to the MetaSound editor that owns us
- L136 _protected member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results
- L139 _protected member_ `TSharedPtr<class SSearchBox> SearchTextField;` — The search text box
- L142 _protected member_ `TArray<FSearchResult> ItemsFound;` — This buffer stores the currently displayed results
- L145 _protected member_ `FSearchResult RootSearchResult;` — we need to keep a handle on the root result, because it won't show up in the tree
- L148 _protected member_ `FText HighlightText;` — The string to highlight in the results
- L151 _protected member_ `FString SearchValue;` — The string to search for
- L154 _protected member_ `uint32 FoundNodeCount = 0;` — Counters for number of results of each type
- L155 _protected member_ `uint32 FoundPinCount = 0;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Metasound`
- L16 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/IMetaSoundGraphPanelPinFactory.h` (Public)


#### struct `Metasound::Editor::FGraphPinParams`  
`struct FGraphPinParams`  
_L23-30_
- desc: Params for registering an external pin type. Used with IMetaSoundGraphPanelPinFactory::RegisterPin to provide optional styling data (category, color, and icons) for a registered data type.
- L25 _public member_ `FName PinCategory = { };`
- L26 _public member_ `FName PinSubCategory = { };`
- L27 _public member_ `const FLinearColor* PinColor = nullptr;`
- L28 _public member_ `const FSlateBrush* PinConnectedIcon = nullptr;`
- L29 _public member_ `const FSlateBrush* PinDisconnectedIcon = nullptr;`

#### class `Metasound::Editor::IMetaSoundGraphPanelPinFactory`  
`class IMetaSoundGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L46-82_
- inherits: `FGraphPanelPinFactory`
- desc: Factory for creating MetaSound Editor Graph pin icons and widgets. Provides a single registration API for external plugins to register custom pin types with optional styling (category, color, icons). Internal core MetaSound pin types (Boolean, Float, Trigger, etc.) are registered automatically at startup. Lifecycle: - Register pins in your module's StartupModule() after MetaSoundEditor is loaded. - Unregister pins in your module's ShutdownModule(). Guard with FModuleManager::Get().IsModuleLoaded(IMetasoundEditorModule::ModuleName) in case MetaSoundEditor shuts down before your module. - All Register/Unregister calls must be made on the game thread.
- L52 _public prototype_ `virtual void RegisterCategoryPin(FName InPinCategory, FOnCreateMetaSoundPinWidget InCreateDelegate) = 0;` — Register a pin widget factory for a specific pin category. Categories are broader classifications like Boolean, Float, Int32, etc. Category delegates are used as a fallback when no data-type-specific delegate is found.
- L55 _public prototype_ `virtual void UnregisterCategoryPin(FName InPinCategory) = 0;` — Unregister a pin widget factory for a pin category.
- L59 _public prototype_ `virtual void RegisterDataTypePin(FName InDataTypeName, FOnCreateMetaSoundPinWidget InCreateDelegate) = 0;` — Register a pin widget factory for a specific data type. Data type registrations take priority over category registrations in the widget creation lookup.
- L62 _public prototype_ `virtual void UnregisterDataTypePin(FName InDataTypeName) = 0;` — Unregister a pin widget factory for a data type.
- L65 _public prototype_ `virtual void RegisterPin(FName InDataTypeName, const FGraphPinParams& Params = FGraphPinParams { }) = 0;` — Register a pin type for a MetaSound data type with optional styling parameters.
- L68 _public prototype_ `virtual void UnregisterPin(FName InDataTypeName) = 0;` — Unregister a previously registered pin type.
- L71 _public prototype_ `virtual const FEdGraphPinType* FindPinType(FName InDataTypeName) const = 0;` — Find the pin type configuration for a registered data type. Returns nullptr if not registered.
- L74 _public prototype_ `virtual bool GetCustomPinIcons(UEdGraphPin* InPin, const FSlateBrush*& OutConnectedIcon, const FSlateBrush*& OutDisconnectedIcon) const = 0;` — Get custom pin icons for a registered data type via pin reference.
- L77 _public prototype_ `virtual bool GetCustomPinIcons(FName InDataType, const FSlateBrush*& OutConnectedIcon, const FSlateBrush*& OutDisconnectedIcon) const = 0;` — Get custom pin icons for a registered data type by name.
- L81 _public prototype_ `virtual FLinearColor GetPinColor(const FEdGraphPinType& InPinType) const = 0;` — Get pin color for a pin type. Checks built-in categories (from UMetasoundEditorSettings), then registered custom colors, then falls back to DefaultPinTypeColor.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Editor` (scope `Metasound`)
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SGraphPin>, FOnCreateMetaSoundPinWidget, UEdGraphPin*);` — Delegate for creating a custom MetaSound pin widget
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SGraphPin>, FOnCreateMetaSoundPinWidget, UEdGraphPin*);` (scope `Metasound::Editor`) — Delegate for creating a custom MetaSound pin widget

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/IMetasoundEditor.h` (Public)


#### class `IMetasoundEditor`  
`class IMetasoundEditor : public FAssetEditorToolkit`  
_L11-31_
- inherits: `FAssetEditorToolkit`
- L15 _public prototype_ `virtual UObject* GetMetasoundObject() const = 0;` — Returns the editor's assigned MetaSound UObject.
- L18 _public prototype_ `virtual void SetSelection(const TArray<UObject*>& SelectedObjects, bool bInvokeTabOnSelectionSet = true) = 0;` — Sets the selected object(s).
- L21 _public prototype_ `virtual bool GetBoundsForSelectedNodes(FSlateRect& OutRect, float Padding) = 0;` — Returns the bounds for the selected node(s).
- L24 _public prototype_ `virtual void Play() = 0;` — Plays the associated preview UAudioComponent & update editor state to reflect.
- L27 _public prototype_ `virtual void Stop() = 0;` — Stop the associated preview UAudioComponent & update editor state to reflect.
- L30 _public prototype_ `virtual bool IsPlaying() const = 0;` — Whether or not the given editor is current associated with a UAudioComponent that is actively playing.

#### struct `Metasound::Editor::FDroppedObjectsInfo`  
`struct FDroppedObjectsInfo`  
_L36-41_
- desc: For tracking objects being dropped onto the editor graph
- L38 _public member_ `TArray<UObject*> DroppedObjects;`
- L39 _public member_ `FModifierKeysState ModifierKeys;`
- L40 _public member_ `FName TypeName;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace Metasound`
- L33 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundDefaultLiteralCustomization.h` (Public)


#### class `Metasound::Editor::FMetasoundDefaultLiteralCustomizationBase`  
`class FMetasoundDefaultLiteralCustomizationBase`  
_L32-74_
- L35 _protected member_ `IDetailCategoryBuilder* DefaultCategoryBuilder = nullptr;`
- L38 _public typedef_ `using FOnDefaultPageRowAdded = TFunction<void(IDetailPropertyRow& , TSharedRef<IPropertyHandle> )>;`
- L40 _public prototype_ `FMetasoundDefaultLiteralCustomizationBase(IDetailCategoryBuilder& InDefaultCategoryBuilder);`
- L41 _public prototype_ `virtual ~FMetasoundDefaultLiteralCustomizationBase();`
- L43 _public prototype_ `virtual void CustomizeDefaults(UMetasoundEditorGraphMemberDefaultLiteral& InLiteral, IDetailLayoutBuilder& InDetailLayout);`
- L46 _public prototype_ `virtual TArray<IDetailPropertyRow*> CustomizeLiteral(UMetasoundEditorGraphMemberDefaultLiteral& InLiteral, IDetailLayoutBuilder& InDetailLayout);` — `UE_DEPRECATED(5.5, "Use CustomizeDefaults instead and provide returned customized handles")`
- L48 _public prototype_ `virtual TAttribute<EVisibility> GetDefaultVisibility() const;`
- L49 _public prototype_ `virtual TAttribute<bool> GetEnabled() const;`
- L51 _public prototype_ `virtual void SetDefaultVisibility(TAttribute<EVisibility> VisibilityAttribute);`
- L52 _public prototype_ `virtual void SetEnabled(TAttribute<bool> EnableAttribute);`
- L53 _public prototype_ `virtual void SetResetOverride(const TOptional<FResetToDefaultOverride>& InResetOverride);`
- L56 _protected prototype_ `void CustomizePageDefaultRows(UMetasoundEditorGraphMemberDefaultLiteral& InLiteral, IDetailLayoutBuilder& InDetailLayout);`
- L57 _protected prototype_ `virtual void BuildDefaultValueWidget(IDetailPropertyRow& ValueRow, TSharedPtr<IPropertyHandle> ValueProperty);`
- L59 _protected member_ `TArray<TSharedPtr<IPropertyHandle>> DefaultProperties;`
- L62 _private prototype_ `TSharedRef<SWidget> BuildPageDefaultNameWidget(UMetasoundEditorGraphMemberDefaultLiteral& Literal, TSharedRef<IPropertyHandle> ElementProperty);`
- L63 _private prototype_ `void BuildPageDefaultComboBox(UMetasoundEditorGraphMemberDefaultLiteral& Literal, FText RowName);`
- L64 _private prototype_ `void UpdatePagePickerNames(TWeakObjectPtr<UMetasoundEditorGraphMemberDefaultLiteral> LiteralPtr);`
- L66 _private member_ `TArray<TSharedPtr<FString>> AddablePageStringNames;`
- L67 _private member_ `TSet<FName> ImplementedPageNames;`
- L68 _private member_ `TSharedPtr<SSearchableComboBox> PageDefaultComboBox;`
- L69 _private member_ `FDelegateHandle OnPageSettingsUpdatedHandle;`
- L71 _private member_ `TAttribute<bool> Enabled;`
- L72 _private member_ `TAttribute<EVisibility> Visibility;`
- L73 _private member_ `TOptional<FResetToDefaultOverride> ResetOverride;`

#### class `Metasound::Editor::IMemberDefaultLiteralCustomizationFactory`  
`class IMemberDefaultLiteralCustomizationFactory`  
_L76-82_
- L79 _public prototype_ `virtual ~IMemberDefaultLiteralCustomizationFactory() = default;`
- L81 _public prototype_ `virtual TUniquePtr<FMetasoundDefaultLiteralCustomizationBase> CreateLiteralCustomization(IDetailCategoryBuilder& DefaultCategoryBuilder) const = 0;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L25 _namespace_ `namespace Metasound`
- L25 _namespace_ `namespace Editor` (scope `Metasound`)
- L27 _namespace_ `namespace LiteralCustomization` (scope `Metasound::Editor`)
- L29 _prototype_ `FGuid GetGuidPropertyValue(TSharedPtr<IPropertyHandle> GuidProperty);` (scope `Metasound::Editor::LiteralCustomization`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorBuilderListener.h` (Public)


#### struct `FGraphInputDefaultChangedArgs`  
`struct FGraphInputDefaultChangedArgs`  
_L14-29_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `FName InputName;` — `UPROPERTY(BlueprintReadWrite, Category = "Audio|MetaSound|BuilderListener")`
- L22 _public member_ `FName PageName;` — `UPROPERTY(BlueprintReadWrite, Category = "Audio|MetaSound|BuilderListener")`
- L25 _public member_ `FMetasoundFrontendLiteral Literal;` — `UPROPERTY(BlueprintReadWrite, Category = "Audio|MetaSound|BuilderListener")`
- L28 _public member_ `EMetaSoundLiteralChangeType ChangeType = EMetaSoundLiteralChangeType::Invalid;` — `UPROPERTY(BlueprintReadWrite, Category = "Audio|MetaSound|BuilderListener")`

#### class `UMetaSoundEditorBuilderListener`  
`class UMetaSoundEditorBuilderListener : public UObject`  
_L46-245_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L51 _public prototype_ `virtual ~UMetaSoundEditorBuilderListener() = default;`
- L54 _public prototype_ `void Init(const TWeakObjectPtr<UMetaSoundBuilderBase> InBuilder);`
- L56 _public prototype_ `void OnDocumentDisplayNameChanged();`
- L57 _public prototype_ `void OnDocumentDescriptionChanged();`
- L58 _public prototype_ `void OnDocumentAuthorChanged();`
- L59 _public prototype_ `void OnDocumentKeywordsChanged();`
- L60 _public prototype_ `void OnDocumentCategoryHierarchyChanged();`
- L61 _public prototype_ `void OnDocumentIsDeprecatedChanged();`
- L63 _public prototype_ `void OnPageAdded(const Metasound::Frontend::FDocumentMutatePageArgs& PageArgs);`
- L64 _public prototype_ `void OnRemovingPage(const Metasound::Frontend::FDocumentMutatePageArgs& PageArgs);`
- L65 _public prototype_ `void OnBuildPageChanged(const Metasound::Frontend::FDocumentMutatePageArgs& PageArgs);`
- L67 _public prototype_ `void OnGraphInputAdded(int32 Index);`
- L68 _public prototype_ `void OnRemovingGraphInput(int32 Index);`
- L69 _public prototype_ `void OnGraphInputNameChanged(FName OldName, FName NewName);`
- L70 _public prototype_ `void OnGraphInputDisplayNameChanged(int32 Index);`
- L71 _public prototype_ `void OnGraphInputDataTypeChanged(int32 Index);`
- L72 _public prototype_ `void OnGraphInputDescriptionChanged(int32 Index);`
- L73 _public prototype_ `void OnGraphInputSortOrderIndexChanged(int32 Index);`
- L74 _public prototype_ `void OnGraphInputIsConstructorPinChanged(int32 Index);`
- L75 _public prototype_ `void OnGraphInputIsAdvancedDisplayChanged(int32 Index);`
- L77 _public prototype_ `void OnGraphInputDefaultChanged(int32 Index);` — `UE_DEPRECATED(5.8, "Use the input default changed delegate that includes additional args")`
- L78 _public prototype_ `void OnGraphInputDefaultChanged(const Metasound::Frontend::FDocumentArrayPagedInputArgs& Args);`
- L79 _public prototype_ `void OnGraphInputInheritsDefaultChanged(int32 Index);`
- L81 _public prototype_ `void OnGraphOutputAdded(int32 Index);`
- L82 _public prototype_ `void OnRemovingGraphOutput(int32 Index);`
- L83 _public prototype_ `void OnGraphOutputNameChanged(FName OldName, FName NewName);`
- L84 _public prototype_ `void OnGraphOutputDisplayNameChanged(int32 Index);`
- L85 _public prototype_ `void OnGraphOutputDataTypeChanged(int32 Index);`
- L86 _public prototype_ `void OnGraphOutputDescriptionChanged(int32 Index);`
- L87 _public prototype_ `void OnGraphOutputSortOrderIndexChanged(int32 Index);`
- L88 _public prototype_ `void OnGraphOutputIsConstructorPinChanged(int32 Index);`
- L89 _public prototype_ `void OnGraphOutputIsAdvancedDisplayChanged(int32 Index);`
- L92 _public prototype_ `void RemoveAllDelegates();` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|BuilderListener")`
- L96 _public member_ `FOnMetaSoundBuilderDocumentMetadataTextChanged OnDocumentDisplayNameChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Document Display Name Changed")` — Metadata
- L99 _public member_ `FOnMetaSoundBuilderDocumentMetadataTextChanged OnDocumentDescriptionChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Document Description Changed")`
- L102 _public member_ `FOnMetaSoundBuilderDocumentMetadataStringChanged OnDocumentAuthorChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Document Author Changed")`
- L105 _public member_ `FOnMetaSoundBuilderDocumentMetadataTextArrayChanged OnDocumentKeywordsChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Document Keywords Changed")`
- L108 _public member_ `FOnMetaSoundBuilderDocumentMetadataTextArrayChanged OnDocumentCategoryHierarchyChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Document Category Hierarchy Changed")`
- L111 _public member_ `FOnMetaSoundBuilderDocumentMetadataBoolChanged OnDocumentIsDeprecatedChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Document Is Deprecated Changed")`
- L115 _public member_ `FOnMetaSoundBuilderPageMutate OnPageAddedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Page Added")` — Pages
- L118 _public member_ `FOnMetaSoundBuilderPageMutate OnRemovingPageDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Page Removed")`
- L121 _public member_ `FOnMetaSoundBuilderPageMutate OnBuildPageChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener", DisplayName = "On Build Page Changed")`
- L125 _public member_ `FOnMetaSoundBuilderGraphInterfaceMutate OnGraphInputAddedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Added")` — Graph Interface
- L128 _public member_ `FOnMetaSoundBuilderGraphInterfaceMutate OnRemovingGraphInputDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Removed")`
- L131 _public member_ `FOnMetaSoundBuilderGraphVertexRename OnGraphInputNameChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Name Changed")`
- L134 _public member_ `FOnMetaSoundBuilderGraphVertexTextChanged OnGraphInputDisplayNameChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Display Name Changed")`
- L137 _public member_ `FOnMetaSoundBuilderGraphInterfaceMutate OnGraphInputDataTypeChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Data Type Changed")`
- L140 _public member_ `FOnMetaSoundBuilderGraphVertexTextChanged OnGraphInputDescriptionChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Description Changed")`
- L143 _public member_ `FOnMetaSoundBuilderGraphVertexIntChanged OnGraphInputSortOrderIndexChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Sort Order Index Changed")`
- L146 _public member_ `FOnMetaSoundBuilderGraphVertexBoolChanged OnGraphInputIsConstructorPinChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Is Constructor Pin Changed")`
- L149 _public member_ `FOnMetaSoundBuilderGraphVertexBoolChanged OnGraphInputIsAdvancedDisplayChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Is Advanced Display Changed")`
- L153 _public member_ `FOnMetaSoundBuilderGraphLiteralMutate OnGraphInputDefaultChangedDelegate;` — `UE_DEPRECATED(5.8, "Use the GraphInputDefaultChanged delegate that includes additional args")` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "[Deprecated] On Graph Input Default Changed")`
- L156 _public member_ `FOnMetaSoundBuilderGraphInputDefaultChanged OnGraphInputDefaultChangedWithArgsDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Default Changed")`
- L159 _public member_ `FOnMetaSoundBuilderGraphVertexBoolChanged OnGraphInputInheritsDefaultChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|InputDelegates", DisplayName = "On Graph Input Inherits Default Changed")`
- L162 _public member_ `FOnMetaSoundBuilderGraphInterfaceMutate OnGraphOutputAddedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Added")`
- L165 _public member_ `FOnMetaSoundBuilderGraphInterfaceMutate OnRemovingGraphOutputDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Removed")`
- L168 _public member_ `FOnMetaSoundBuilderGraphVertexRename OnGraphOutputNameChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Name Changed")`
- L171 _public member_ `FOnMetaSoundBuilderGraphVertexTextChanged OnGraphOutputDisplayNameChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Display Name Changed")`
- L174 _public member_ `FOnMetaSoundBuilderGraphInterfaceMutate OnGraphOutputDataTypeChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Data Type Changed")`
- L177 _public member_ `FOnMetaSoundBuilderGraphVertexTextChanged OnGraphOutputDescriptionChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Description Changed")`
- L180 _public member_ `FOnMetaSoundBuilderGraphVertexIntChanged OnGraphOutputSortOrderIndexChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Sort Order Index Changed")`
- L183 _public member_ `FOnMetaSoundBuilderGraphVertexBoolChanged OnGraphOutputIsConstructorPinChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Is Constructor Pin Changed")`
- L186 _public member_ `FOnMetaSoundBuilderGraphVertexBoolChanged OnGraphOutputIsAdvancedDisplayChangedDelegate;` — `UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Audio|MetaSound|BuilderListener|OutputDelegates", DisplayName = "On Graph Output Is Advanced Display Changed")`
- L190 _private member_ `FDelegateHandle OnDocumentDisplayNameChangedHandle;` — Handles for document delegates
- L191 _private member_ `FDelegateHandle OnDocumentDescriptionChangedHandle;`
- L192 _private member_ `FDelegateHandle OnDocumentAuthorChangedHandle;`
- L193 _private member_ `FDelegateHandle OnDocumentKeywordsChangedHandle;`
- L194 _private member_ `FDelegateHandle OnDocumentCategoryHierarchyChangedHandle;`
- L195 _private member_ `FDelegateHandle OnDocumentIsDeprecatedChangedHandle;`
- L197 _private member_ `FDelegateHandle OnPageAddedHandle;`
- L198 _private member_ `FDelegateHandle OnRemovingPageHandle;`
- L199 _private member_ `FDelegateHandle OnBuildPageChangedHandle;`
- L201 _private member_ `FDelegateHandle OnInputAddedHandle;`
- L202 _private member_ `FDelegateHandle OnRemovingInputHandle;`
- L203 _private member_ `FDelegateHandle OnInputNameChangedHandle;`
- L204 _private member_ `FDelegateHandle OnInputDisplayNameChangedHandle;`
- L205 _private member_ `FDelegateHandle OnInputDataTypeChangedHandle;`
- L206 _private member_ `FDelegateHandle OnInputDescriptionChangedHandle;`
- L207 _private member_ `FDelegateHandle OnInputSortOrderIndexChangedHandle;`
- L208 _private member_ `FDelegateHandle OnInputIsConstructorPinChangedHandle;`
- L209 _private member_ `FDelegateHandle OnInputIsAdvancedDisplayChangedHandle;`
- L210 _private member_ `FDelegateHandle OnInputDefaultChangedHandle;`
- L211 _private member_ `FDelegateHandle OnInputInheritsDefaultChangedHandle;`
- L213 _private member_ `FDelegateHandle OnOutputAddedHandle;`
- L214 _private member_ `FDelegateHandle OnRemovingOutputHandle;`
- L215 _private member_ `FDelegateHandle OnOutputNameChangedHandle;`
- L216 _private member_ `FDelegateHandle OnOutputDisplayNameChangedHandle;`
- L217 _private member_ `FDelegateHandle OnOutputDataTypeChangedHandle;`
- L218 _private member_ `FDelegateHandle OnOutputDescriptionChangedHandle;`
- L219 _private member_ `FDelegateHandle OnOutputSortOrderIndexChangedHandle;`
- L220 _private member_ `FDelegateHandle OnOutputIsConstructorPinChangedHandle;`
- L221 _private member_ `FDelegateHandle OnOutputIsAdvancedDisplayChangedHandle;`
- L223 _private member_ `TWeakObjectPtr<UMetaSoundBuilderBase> Builder;`
- L244 _private member_ `TSharedPtr<FEditorBuilderListener> BuilderListener;`

#### class `UMetaSoundEditorBuilderListener::FEditorBuilderListener`  
`class FEditorBuilderListener : public Metasound::Frontend::IDocumentBuilderTransactionListener`  
_L225-242_
- inherits: `Metasound::Frontend::IDocumentBuilderTransactionListener`
- L229 _public prototype_ `FEditorBuilderListener() = default;`
- L230 _public function_ `FEditorBuilderListener(TObjectPtr<UMetaSoundEditorBuilderListener> InParent) : Parent(InParent)`
- L235 _public prototype_ `virtual ~FEditorBuilderListener() = default;`
- L238 _public prototype_ `virtual void OnBuilderReloaded(Metasound::Frontend::FDocumentModifyDelegates& OutDelegates) override;` — IDocumentBuilderTransactionListener
- L241 _private member_ `TObjectPtr<UMetaSoundEditorBuilderListener> Parent;`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderDocumentMetadataTextChanged, FText, NewText);` — BP Delegates for builder changes
- L32 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderDocumentMetadataTextChanged, FText, NewText);` — BP Delegates for builder changes
- L33 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderDocumentMetadataTextArrayChanged, TArray<FText>, NewTextArray);`
- L33 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderDocumentMetadataTextArrayChanged, TArray<FText>, NewTextArray);`
- L34 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderDocumentMetadataStringChanged, FString, NewString);`
- L34 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderDocumentMetadataStringChanged, FString, NewString);`
- L35 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderDocumentMetadataBoolChanged, bool, NewBool);`
- L35 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderDocumentMetadataBoolChanged, bool, NewBool);`
- L36 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderPageMutate, FName, PageName);`
- L36 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderPageMutate, FName, PageName);`
- L37 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphInterfaceMutate, FName, VertexName, FName, DataType);`
- L37 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphInterfaceMutate, FName, VertexName, FName, DataType);`
- L38 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMetaSoundBuilderGraphLiteralMutate, FName, VertexName, FMetasoundFrontendLiteral, LiteralValue, FName, PageName);`
- L38 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMetaSoundBuilderGraphLiteralMutate, FName, VertexName, FMetasoundFrontendLiteral, LiteralValue, FName, PageName);`
- L39 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderGraphInputDefaultChanged, const FGraphInputDefaultChangedArgs&, GraphInputDefaultChangedArgs);`
- L39 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaSoundBuilderGraphInputDefaultChanged, const FGraphInputDefaultChangedArgs&, GraphInputDefaultChangedArgs);`
- L40 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphVertexRename, FName, OldName, FName, NewName);`
- L40 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphVertexRename, FName, OldName, FName, NewName);`
- L41 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphVertexBoolChanged, FName, VertexName, bool, bNewBool);`
- L41 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphVertexBoolChanged, FName, VertexName, bool, bNewBool);`
- L42 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphVertexIntChanged, FName, VertexName, int32, NewInt);`
- L42 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphVertexIntChanged, FName, VertexName, int32, NewInt);`
- L43 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphVertexTextChanged, FName, VertexName, FText, NewText);`
- L43 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetaSoundBuilderGraphVertexTextChanged, FName, VertexName, FText, NewText);`

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorCommands.h` (Public)


#### class `Metasound::Editor::FEditorCommands`  
`class FEditorCommands : public TCommands<FEditorCommands>`  
_L13-87_
- inherits: `TCommands<FEditorCommands>`
- L17 _public function_ `FEditorCommands() : TCommands<FEditorCommands>("MetaSoundEditor", NSLOCTEXT("Contexts", "MetaSoundEditor", "MetaSound Graph Editor"), NAME_None, "MetaSoundStyle")` — Constructor
- L23 _public member_ `TSharedPtr<FUICommandInfo> Play;` — Plays the Metasound
- L26 _public member_ `TSharedPtr<FUICommandInfo> Stop;` — Stops the currently playing Metasound
- L29 _public member_ `TSharedPtr<FUICommandInfo> Import;` — Imports the Metasound from Json
- L32 _public member_ `TSharedPtr<FUICommandInfo> Export;` — Exports the Metasound
- L35 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayback;` — Plays stops the currently playing Metasound
- L38 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowGraph;` — Toggles showing the graph for the given configured MetaSound
- L41 _public member_ `TSharedPtr<FUICommandInfo> BrowserSync;` — Selects the Metasound in the content browser. If referencing Metasound nodes are selected, selects referenced assets instead.
- L44 _public member_ `TSharedPtr<FUICommandInfo> BreakLink;` — Breaks the node input/output link
- L47 _public member_ `TSharedPtr<FUICommandInfo> AddInput;` — Adds an input to the node
- L50 _public member_ `TSharedPtr<FUICommandInfo> EditSourceSettings;` — Shows the MetasoundSource's specific settings in the Details panel (if of respective type)
- L53 _public member_ `TSharedPtr<FUICommandInfo> EditMetasoundSettings;` — Shows the Metasound's top-level general object settings in the Details panel
- L56 _public member_ `TSharedPtr<FUICommandInfo> UpdateNodeClass;` — Run updates on selected node(s) class(es) if required by any subset of selected nodes
- L59 _public member_ `TSharedPtr<FUICommandInfo> Delete;` — Delete selected items.
- L62 _public member_ `TSharedPtr<FUICommandInfo> FindInMetaSound;` — Show the Find in MetaSound window.
- L65 _public member_ `TSharedPtr<FUICommandInfo> PromoteToInput;` — Promotes pin to graph input
- L68 _public member_ `TSharedPtr<FUICommandInfo> PromoteToOutput;` — Promotes pin to graph output
- L71 _public member_ `TSharedPtr<FUICommandInfo> PromoteToVariable;` — Promotes pin to graph variable
- L74 _public member_ `TSharedPtr<FUICommandInfo> PromoteToDeferredVariable;` — Promotes pin to deferred graph variable
- L77 _public member_ `TSharedPtr<FUICommandInfo> PromoteAllToInput;` — Promotes all unconnected node inputs to graph inputs.
- L80 _public member_ `TSharedPtr<FUICommandInfo> PromoteAllToCommonInputs;` — Promotes all unconnected node inputs to shared graph inputs.
- L83 _public member_ `TSharedPtr<FUICommandInfo> CopySelectionAsConfiguratorCodeToClipboard;` — Copies the selected nodes, shared connections, and required interfaces to the clipboard as configurator c++
- L86 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L11 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorGraph.h` (Public)


#### struct `Metasound::Editor::FCreateNodeVertexParams`  
`struct FCreateNodeVertexParams`  
_L40-44_
- L42 _public member_ `FName DataType;`
- L43 _public member_ `EMetasoundFrontendVertexAccessType AccessType = EMetasoundFrontendVertexAccessType::Reference;`

#### struct `FMetasoundEditorGraphMemberBreadcrumb`  
`struct FMetasoundEditorGraphMemberBreadcrumb`  
_L49-58_
- reflection: `USTRUCT()`
- L54 _public member_ `FName MemberName;` — `UPROPERTY()`
- L57 _public member_ `FText Description;` — `UPROPERTY()`

#### struct `FMetasoundEditorGraphVertexBreadcrumb`  
`struct FMetasoundEditorGraphVertexBreadcrumb : public FMetasoundEditorGraphMemberBreadcrumb`  
_L61-76_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorGraphMemberBreadcrumb`
- L66 _public member_ `EMetasoundFrontendVertexAccessType AccessType = EMetasoundFrontendVertexAccessType::Unset;` — `UPROPERTY()`
- L69 _public member_ `TMap<FGuid, FMetasoundFrontendLiteral> DefaultLiterals;` — `UPROPERTY()`
- L72 _public member_ `bool bIsAdvancedDisplay = false;` — `UPROPERTY()`
- L75 _public member_ `int32 SortOrderIndex = 0;` — `UPROPERTY()`

#### struct `FMetasoundEditorGraphVariableBreadcrumb`  
`struct FMetasoundEditorGraphVariableBreadcrumb : public FMetasoundEditorGraphMemberBreadcrumb`  
_L79-85_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorGraphMemberBreadcrumb`
- L84 _public member_ `FMetasoundFrontendLiteral DefaultLiteral;` — `UPROPERTY()`

#### class `UMetasoundEditorGraphMemberDefaultLiteral`  
`class UMetasoundEditorGraphMemberDefaultLiteral : public UMetaSoundFrontendMemberMetadata`  
_L91-149_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaSoundFrontendMemberMetadata`
- L99 _public function_ `template <typename T> T GetDefaultAs(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) const` — Returns the default literal casted as the given template type. Asserts if literal is not provided type and enforces type is supported by literal.
- L110 _public prototype_ `virtual void ForceRefresh();`
- L111 _public prototype_ `virtual FName GetDataType() const;`
- L112 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const;`
- L113 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID);`
- L114 _public function_ `virtual void Initialize()`
- L115 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const;`
- L116 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID);`
- L117 _public prototype_ `virtual void ResetDefaults();`
- L118 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID = Metasound::Frontend::DefaultPageID);`
- L119 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const;`
- L121 _public function_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const`
- L129 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L130 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L131 _public prototype_ `virtual void PostEditUndo() override;`
- L136 _public function_ `virtual bool Synchronize()` — Synchronizes local transient editor-only member data with changes made to the associated Frontend Document member. Returns whether or not object was modified.
- L138 _public prototype_ `UMetasoundEditorGraphMember* FindMember() const;`
- L140 _public function_ `static FName GetDefaultsPropertyName()`
- L146 _protected function_ `virtual void ResolvePageDefaults()`
- L147 _protected function_ `virtual void SortPageDefaults()`
- L148 _protected prototype_ `bool TryGetPreviewPageID(FGuid& OutPreviewPageID) const;`

#### class `UMetasoundEditorGraphMember`  
`class UMetasoundEditorGraphMember : public UObject`  
_L154-259_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: UMetasoundEditorGraphMember is a base class for non-node graph level members such as inputs, outputs and variables.
- L160 _public member_ `FOnMetasoundMemberRenameRequested OnRenameRequested;` — Delegate called when a rename is requested on a renameable member node.
- L163 _public prototype_ `virtual Metasound::Editor::ENodeSection GetSectionID() const PURE_VIRTUAL(UMetasoundEditorGraphMember::GetSectionID, return Metasound::Editor::ENodeSection::None; );` — Return the section of where this member belongs.
- L166 _public prototype_ `virtual TArray<UMetasoundEditorGraphMemberNode*> GetNodes() const PURE_VIRTUAL(UMetasoundEditorGraphMember::GetNodes, return TArray<UMetasoundEditorGraphMemberNode*>(); );` — Return the nodes associated with this member
- L169 _public prototype_ `virtual void SetDataType(FName InNewType, bool bPostTransaction = true) PURE_VIRTUAL(UMetasoundEditorGraphMember::SetDataType, );` — Sets the datatype on the member.
- L173 _public prototype_ `virtual bool CanRename(const FText& InNewName, FText& OutError) const PURE_VIRTUAL(UMetasoundEditorGraphMember::CanRename, return false; );` — If the Member Name can be changed to InNewName, returns true, otherwise returns false with an error.
- L176 _public prototype_ `virtual void SetDisplayName(const FText& InNewName, bool bPostTransaction) PURE_VIRTUAL(UMetasoundEditorGraphMember::SetDisplayName, );` — Set the display name
- L179 _public prototype_ `virtual FText GetDisplayName() const PURE_VIRTUAL(UMetasoundEditorGraphMember::GetDisplayName, return FText::GetEmpty(); );` — Get the member display name
- L182 _public prototype_ `virtual void SetMemberName(const FName& InNewName, bool bPostTransaction) PURE_VIRTUAL(UMetasoundEditorGraphMember::SetMemberName, );` — Set the member name
- L185 _public prototype_ `virtual FName GetMemberName() const PURE_VIRTUAL(UMetasoundEditorGraphMember::GetMemberName, return FName(); );` — Gets the members name
- L188 _public prototype_ `virtual FGuid GetMemberID() const PURE_VIRTUAL(UMetasoundEditorGraphMember::GetMemberID, return FGuid(); );` — Get ID for this member
- L191 _public prototype_ `virtual void SetDescription(const FText& InDescription, bool bPostTransaction) PURE_VIRTUAL(UMetasoundEditorGraphMember::SetDescription, );` — Set the member description
- L194 _public prototype_ `virtual FText GetDescription() const PURE_VIRTUAL(UMetasoundEditorGraphMember::GetDescription, return FText::GetEmpty(); );` — Get the member description
- L197 _public prototype_ `virtual const FText& GetGraphMemberLabel() const PURE_VIRTUAL(UMetasoundEditorGraphMember::GetGraphMemberLabel, return FText::GetEmpty(); );` — Returns the label of the derived member type (e.g. Input/Output/Variable)
- L200 _public prototype_ `virtual void ResetToClassDefault() PURE_VIRTUAL(UMetasoundEditorGraphMember::ResetToClassDefault, );` — Resets the member to the class default.
- L205 _public prototype_ `virtual void UpdateFrontendDefaultLiteral(bool bPostTransaction, const FGuid* InPageID = nullptr, EMetaSoundLiteralChangeType InChangeType = EMetaSoundLiteralChangeType::Set) PURE_VIRTUAL(UMetasoundEditorGraphMember::UpdateFrontendDefaultLiteral, );` — Update the frontend with the given member's default UObject value. @param bPostTransaction - Post as editor transaction if true
- L208 _public prototype_ `virtual bool Synchronize();` — Synchronizes cached data with the frontend representation on the represented document.
- L210 _public prototype_ `FMetaSoundFrontendDocumentBuilder& GetFrontendBuilderChecked() const;`
- L214 _public prototype_ `UMetasoundEditorGraph* GetOwningGraph();` — Returns the parent MetaSound Graph. If the Outer object of the member is non a UMetasoundEditorGraph, returns a nullptr.
- L218 _public prototype_ `const UMetasoundEditorGraph* GetOwningGraph() const;` — Returns the parent MetaSound Graph. If the Outer object of the member is non a UMetasoundEditorGraph, returns a nullptr.
- L221 _public prototype_ `virtual bool CanRename() const PURE_VIRTUAL(UMetasoundEditorGraphMember::CanRename, return false;);` — Whether this member can be renamed.
- L224 _public function_ `virtual bool IsDefaultPaged() const` — Whether the displayed default supports paged values or is a single default value (i.e. characterized per page).
- L227 _public function_ `virtual void CacheBreadcrumb()` — Cache breadcrumb data before copying member to the clipboard
- L230 _public prototype_ `virtual void PostEditUndo() override;`
- L234 _public prototype_ `FName GetDataType() const;` — Returns the current data type
- L236 _public function_ `static FName GetLiteralPropertyName()`
- L242 _public function_ `UMetasoundEditorGraphMemberDefaultLiteral* GetLiteral() const` — Returns literal associated with the given member
- L246 _public prototype_ `void InitializeLiteral(bool bForceRebind=false);` — Creates new literal if there is none or conforms literal object type to member's DataType if not matching. If force rebind is true, will always attempt to reinitialize with updated data from frontend literal.
- L251 _protected member_ `TObjectPtr<UMetasoundEditorGraphMemberDefaultLiteral> Literal;` — `UPROPERTY()` — Default literal value of member
- L255 _protected member_ `FName TypeName;` — `UPROPERTY()` — Metasound Data Type.

#### class `UMetasoundEditorGraphVertex`  
`class UMetasoundEditorGraphVertex : public UMetasoundEditorGraphMember`  
_L263-349_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UMetasoundEditorGraphMember`
- desc: Base class for an input or output of the graph.
- L268 _protected prototype_ `const FMetasoundFrontendNode* GetFrontendNode() const;`
- L271 _protected prototype_ `bool NameContainsInterfaceNamespace(FMetasoundFrontendInterface* OutInterface) const;` — If the vertex's name contains an interface namespace, return true and set OutInterface to that interface if provided.
- L278 _public prototype_ `void InitMember(FName InDataType, const FMetasoundFrontendLiteral& InDefaultLiteral, FGuid InNodeID, FMetasoundFrontendClassName&& InClassName);` — Initializes all properties with the given parameters required to identify the frontend member from this editor graph member.
- L282 _public member_ `FGuid NodeID;` — `UPROPERTY()` — ID of Metasound Frontend node.
- L286 _public member_ `FMetasoundFrontendClassName ClassName;` — `UPROPERTY()` — Class name of Metasound Frontend node.
- L289 _public prototype_ `virtual FGuid GetMemberID() const override;` — ~Begin UMetasoundEditorGraphMember interface
- L290 _public prototype_ `virtual FName GetMemberName() const override;`
- L291 _public prototype_ `virtual FText GetDisplayName() const override;`
- L293 _public prototype_ `virtual bool CanRename(const FText& InNewName, FText& OutError) const override;`
- L294 _public prototype_ `virtual TArray<UMetasoundEditorGraphMemberNode*> GetNodes() const override;`
- L295 _public prototype_ `virtual void SetDescription(const FText& InDescription, bool bPostTransaction) override;`
- L296 _public prototype_ `virtual void SetMemberName(const FName& InNewName, bool bPostTransaction) override;`
- L297 _public prototype_ `virtual bool Synchronize() override;`
- L298 _public prototype_ `virtual void CacheBreadcrumb() override;`
- L302 _public function_ `const FMetasoundEditorGraphVertexBreadcrumb& GetBreadcrumb() const` — Returns Breadcrumb data of this Vertex
- L305 _public prototype_ `virtual const FMetasoundFrontendVersion& GetInterfaceVersion() const;` — Version of interface membership, or invalid version if not an interface member.
- L308 _public prototype_ `virtual bool IsInterfaceMember(FMetasoundFrontendInterface* OutInterface = nullptr) const;` — Returns true if member is part of an interface. If supplied interface pointer, sets pointer's data to the interface vertex is member of.
- L311 _public prototype_ `virtual EMetasoundFrontendClassType GetClassType() const PURE_VIRTUAL(UMetasoundEditorGraphVertex::GetClassType, return EMetasoundFrontendClassType::Invalid; ) virtual const FMetasoundFrontendClassVertex* GetFrontendClassVertex() const PURE_VIRTUAL(UMetasoundEditorGraphVertex::GetFrontendClassVertex, return nullptr; );` — Returns the Metasound class type of the associated node
- L316 _public prototype_ `virtual int32 GetSortOrderIndex() const PURE_VIRTUAL(UMetasoundEditorGraphVertex::GetSortOrderIndex, return 0; ) virtual void SetDataType(FName DataType, bool bPostTransaction = true) PURE_VIRTUAL(UMetasoundEditorGraphVertex::SetDataType, ) virtual void SetSortOrderIndex(int32 InSortOrderIndex) PURE_VIRTUAL(UMetasoundEditorGraphVertex::SetSortOrderIndex, ) virtual void SetVertexAccessType(EMetasoundFrontendVertexAccessType InNewAccessType, bool bPostTransaction = true) PURE_VIRTUAL(UMetasoundEditorGraphVertex::SetVertexAccessType, ) #if WITH_EDITORONLY_DATA bool SetIsAdvancedDisplay(const bool IsAdvancedDisplay);` — Returns the SortOrderIndex assigned to this member.
- L333 _public prototype_ `Metasound::Frontend::FNodeHandle GetNodeHandle();` — `UE_DEPRECATED(5.6, "Node Handles are actively being deprecated, use the MetaSound Frontend Document Builder API")`
- L336 _public prototype_ `Metasound::Frontend::FConstNodeHandle GetConstNodeHandle() const;` — Returns the node handle associated with the vertex.
- L338 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const PURE_VIRTUAL(UMetasoundEditorGraphVertex::GetVertexAccessType, return EMetasoundFrontendVertexAccessType::Reference; );`
- L340 _public prototype_ `virtual bool CanRename() const override;`
- L345 _protected prototype_ `void SetMemberNameInternal(const FName& InNewName, bool bPropagateToPinNames, bool bPostTransaction);`
- L348 _protected member_ `FMetasoundEditorGraphVertexBreadcrumb Breadcrumb;` — `UPROPERTY()`

#### class `UMetasoundEditorGraphInput`  
`class UMetasoundEditorGraphInput : public UMetasoundEditorGraphVertex`  
_L352-382_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphVertex`
- L357 _public prototype_ `virtual FText GetDescription() const override;`
- L358 _public prototype_ `virtual const FMetasoundFrontendClassVertex* GetFrontendClassVertex() const override;`
- L359 _public prototype_ `virtual int32 GetSortOrderIndex() const override;`
- L360 _public prototype_ `virtual void SetSortOrderIndex(int32 InSortOrderIndex) override;`
- L361 _public prototype_ `virtual TArray<UMetasoundEditorGraphMemberNode*> GetNodes() const override;`
- L363 _public prototype_ `virtual const FText& GetGraphMemberLabel() const override;`
- L364 _public prototype_ `virtual bool IsDefaultPaged() const override;`
- L365 _public prototype_ `virtual bool IsInterfaceMember(FMetasoundFrontendInterface* OutInterface = nullptr) const override;`
- L366 _public prototype_ `virtual void ResetToClassDefault() override;`
- L367 _public prototype_ `virtual void SetDataType(FName InNewType, bool bPostTransaction) override;`
- L368 _public prototype_ `virtual void SetDescription(const FText& InDescription, bool bPostTransaction) override;`
- L369 _public prototype_ `virtual void SetDisplayName(const FText& InNewName, bool bPostTransaction) override;`
- L370 _public prototype_ `virtual void SetMemberName(const FName& InNewName, bool bPostTransaction) override;`
- L371 _public prototype_ `virtual void SetVertexAccessType(EMetasoundFrontendVertexAccessType InNewAccessType, bool bPostTransaction) override;`
- L372 _public prototype_ `virtual bool Synchronize() override;`
- L373 _public prototype_ `virtual void CacheBreadcrumb() override;`
- L374 _public prototype_ `virtual void UpdateFrontendDefaultLiteral(bool bPostTransaction, const FGuid* InPageID = nullptr, EMetaSoundLiteralChangeType InChangeType = EMetaSoundLiteralChangeType::Set) override;`
- L375 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override;`
- L378 _protected prototype_ `virtual bool RenameFrontendMemberInternal(FMetaSoundFrontendDocumentBuilder& Builder, FName OldName, FName InNewName) const override;`
- L380 _protected function_ `virtual EMetasoundFrontendClassType GetClassType() const override`
- L381 _protected prototype_ `virtual Metasound::Editor::ENodeSection GetSectionID() const override;`

#### class `UMetasoundEditorGraphOutput`  
`class UMetasoundEditorGraphOutput : public UMetasoundEditorGraphVertex`  
_L386-411_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphVertex`
- L391 _public prototype_ `virtual FText GetDescription() const override;`
- L392 _public prototype_ `virtual const FMetasoundFrontendClassVertex* GetFrontendClassVertex() const override;`
- L393 _public prototype_ `virtual int32 GetSortOrderIndex() const override;`
- L394 _public prototype_ `virtual bool IsInterfaceMember(FMetasoundFrontendInterface* OutInterface = nullptr) const override;`
- L395 _public prototype_ `virtual void SetSortOrderIndex(int32 InSortOrderIndex) override;`
- L396 _public prototype_ `virtual const FText& GetGraphMemberLabel() const override;`
- L397 _public prototype_ `virtual void ResetToClassDefault() override;`
- L398 _public prototype_ `virtual void SetDataType(FName InNewType, bool bPostTransaction) override;`
- L399 _public prototype_ `virtual void SetDescription(const FText& InDescription, bool bPostTransaction) override;`
- L400 _public prototype_ `virtual void SetDisplayName(const FText& InNewName, bool bPostTransaction) override;`
- L401 _public prototype_ `virtual void SetVertexAccessType(EMetasoundFrontendVertexAccessType InNewAccessType, bool bPostTransaction) override;`
- L402 _public prototype_ `virtual bool Synchronize() override;`
- L403 _public prototype_ `virtual void UpdateFrontendDefaultLiteral(bool bPostTransaction, const FGuid* InPageID = nullptr, EMetaSoundLiteralChangeType InChangeType = EMetaSoundLiteralChangeType::Set) override;`
- L404 _public prototype_ `virtual EMetasoundFrontendVertexAccessType GetVertexAccessType() const override;`
- L407 _protected prototype_ `virtual bool RenameFrontendMemberInternal(FMetaSoundFrontendDocumentBuilder& Builder, FName OldName, FName InNewName) const override;`
- L409 _protected function_ `virtual EMetasoundFrontendClassType GetClassType() const override`
- L410 _protected prototype_ `virtual Metasound::Editor::ENodeSection GetSectionID() const override;`

#### class `UMetasoundEditorGraphVariable`  
`class UMetasoundEditorGraphVariable : public UMetasoundEditorGraphMember`  
_L414-486_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMember`
- L419 _private member_ `FGuid VariableID;` — `UPROPERTY()`
- L422 _public prototype_ `void InitMember(FName InDataType, const FMetasoundFrontendLiteral& InDefaultLiteral, FGuid InVariableID);`
- L425 _public prototype_ `virtual Metasound::Editor::ENodeSection GetSectionID() const override;` — ~Begin UMetasoundEditorGraphMember interface
- L426 _public prototype_ `virtual void SetDataType(FName InNewType, bool bPostTransaction = true) override;`
- L428 _public prototype_ `virtual FText GetDescription() const override;`
- L429 _public prototype_ `virtual void SetDescription(const FText& InDescription, bool bPostTransaction) override;`
- L431 _public prototype_ `virtual FGuid GetMemberID() const override;`
- L432 _public prototype_ `virtual bool CanRename(const FText& InNewName, FText& OutError) const override;`
- L433 _public prototype_ `virtual void SetMemberName(const FName& InNewName, bool bPostTransaction) override;`
- L434 _public prototype_ `virtual FName GetMemberName() const override;`
- L436 _public prototype_ `virtual FText GetDisplayName() const override;`
- L437 _public prototype_ `virtual void SetDisplayName(const FText& InNewName, bool bPostTransaction) override;`
- L439 _public prototype_ `virtual void ResetToClassDefault() override;`
- L440 _public prototype_ `virtual bool Synchronize() override;`
- L441 _public prototype_ `virtual void CacheBreadcrumb() override;`
- L442 _public prototype_ `virtual void UpdateFrontendDefaultLiteral(bool bPostTransaction, const FGuid* InPageID = nullptr, EMetaSoundLiteralChangeType InChangeType = EMetaSoundLiteralChangeType::Set) override;`
- L444 _public prototype_ `virtual TArray<UMetasoundEditorGraphMemberNode*> GetNodes() const override;`
- L446 _public prototype_ `virtual const FText& GetGraphMemberLabel() const override;`
- L449 _public prototype_ `const FGuid& GetVariableID() const;`
- L450 _public prototype_ `const FMetasoundFrontendVariable* GetFrontendVariable() const;`
- L453 _public function_ `const FMetasoundEditorGraphVariableBreadcrumb& GetBreadcrumb() const` — Returns Breadcrumb data of this Variable
- L456 _public prototype_ `Metasound::Frontend::FVariableHandle GetVariableHandle();` — `UE_DEPRECATED(5.6, "Use MetasoundFrontendDocumentBuilder to edit variables")`
- L458 _public prototype_ `Metasound::Frontend::FConstVariableHandle GetConstVariableHandle() const;`
- L460 _public prototype_ `virtual bool CanRename() const override;`
- L465 _protected member_ `FMetasoundEditorGraphVariableBreadcrumb Breadcrumb;` — `UPROPERTY()`
- L483 _private prototype_ `FVariableEditorNodes GetVariableNodes() const;`
- L484 _private prototype_ `FVariableNodeLocations GetVariableNodeLocations() const;`
- L485 _private prototype_ `void AddVariableNodes(UObject& InMetaSound, const FVariableNodeLocations& InNodeLocs);`

#### struct `UMetasoundEditorGraphVariable::FVariableEditorNodes`  
`struct FVariableEditorNodes`  
_L468-473_
- L470 _public member_ `UMetasoundEditorGraphMemberNode* MutatorNode = nullptr;`
- L471 _public member_ `TArray<UMetasoundEditorGraphMemberNode*> AccessorNodes;`
- L472 _public member_ `TArray<UMetasoundEditorGraphMemberNode*> DeferredAccessorNodes;`

#### struct `UMetasoundEditorGraphVariable::FVariableNodeLocations`  
`struct FVariableNodeLocations`  
_L475-481_
- L478 _public member_ `TOptional<FVector2D> MutatorLocation;`
- L479 _public member_ `TArray<FVector2D> AccessorLocations;`
- L480 _public member_ `TArray<FVector2D> DeferredAccessorLocations;`

#### class `UMetasoundEditorGraph`  
`class UMetasoundEditorGraph : public UMetasoundEditorGraphBase`  
_L489-621_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphBase`
- L495 _public prototype_ `UMetasoundEditorGraphInputNode* CreateInputNode(Metasound::Frontend::FNodeHandle InNodeHandle, bool bInSelectNewNode);` — `UE_DEPRECATED(5.5, "Input node creation is no longer supported publically via the MetasoundEditorGraph.")`
- L498 _public prototype_ `Metasound::Frontend::FDocumentHandle GetDocumentHandle();` — `UE_DEPRECATED(5.6, "Document Handles are actively being deprecated, use the MetaSound Frontend Document Builder API")`
- L500 _public prototype_ `Metasound::Frontend::FConstDocumentHandle GetDocumentHandle() const;`
- L503 _public prototype_ `Metasound::Frontend::FGraphHandle GetGraphHandle();` — `UE_DEPRECATED(5.6, "Document Handles are actively being deprecated, use the MetaSound Frontend Document Builder API")`
- L505 _public prototype_ `Metasound::Frontend::FConstGraphHandle GetGraphHandle() const;`
- L507 _public prototype_ `virtual void PreSave(FObjectPreSaveContext InSaveContext) override;`
- L509 _public prototype_ `UMetaSoundBuilderBase& GetBuilderChecked() const;`
- L510 _public prototype_ `UObject* GetMetasound() const;`
- L511 _public prototype_ `UObject& GetMetasoundChecked() const;`
- L513 _public prototype_ `void IterateInputs(TFunctionRef<void(UMetasoundEditorGraphInput&)> InFunction) const;`
- L514 _public prototype_ `void IterateOutputs(TFunctionRef<void(UMetasoundEditorGraphOutput&)> InFunction) const;`
- L515 _public prototype_ `void IterateVariables(TFunctionRef<void(UMetasoundEditorGraphVariable&)> InFunction) const;`
- L516 _public prototype_ `void IterateMembers(TFunctionRef<void(UMetasoundEditorGraphMember&)> InFunction) const;`
- L518 _public prototype_ `bool ContainsInput(const UMetasoundEditorGraphInput& InInput) const;`
- L519 _public prototype_ `bool ContainsOutput(const UMetasoundEditorGraphOutput& InOutput) const;`
- L520 _public prototype_ `bool ContainsVariable(const UMetasoundEditorGraphVariable& InVariable) const;`
- L522 _public prototype_ `void SetPreviewID(uint32 InPreviewID);`
- L523 _public prototype_ `bool IsPreviewing() const;`
- L524 _public prototype_ `bool IsEditable() const;`
- L527 _public prototype_ `virtual void RegisterGraphWithFrontend(Metasound::Frontend::FMetaSoundAssetRegistrationOptions* RegOptions = nullptr) override;` — UMetasoundEditorGraphBase Implementation
- L528 _public prototype_ `virtual void MigrateEditorDocumentData(FMetaSoundFrontendDocumentBuilder& OutBuilder) override;`
- L531 _private prototype_ `void ValidateInternal(Metasound::Editor::FGraphValidationResults& OutResults);`
- L535 _private member_ `uint32 PreviewID = INDEX_NONE;` — Preview ID is the Unique ID provided by the UObject that implements a sound's ParameterInterface when a sound begins playing.
- L541 _private member_ `bool bForceRefreshNodes = false;` — Used as a means of forcing the graph to rebuild nodes on next tick. TODO: Will no longer require this once all editor metadata is migrated to the frontend & the system can adequately rely on the changeIDs as a mechanism for selectively updating nodes.
- L544 _private member_ `TArray<TObjectPtr<UMetasoundEditorGraphInput>> Inputs;` — `UPROPERTY()`
- L547 _private member_ `TArray<TObjectPtr<UMetasoundEditorGraphOutput>> Outputs;` — `UPROPERTY()`
- L550 _private member_ `TArray<TObjectPtr<UMetasoundEditorGraphVariable>> Variables;` — `UPROPERTY()`
- L553 _public prototype_ `UMetasoundEditorGraphInput* FindInput(FGuid InNodeID) const;`
- L554 _public prototype_ `UMetasoundEditorGraphInput* FindInput(FName InName) const;`
- L555 _public prototype_ `UMetasoundEditorGraphInput* FindOrAddInput(const FGuid& InNodeID);`
- L558 _public prototype_ `UMetasoundEditorGraphInput* FindOrAddInput(Metasound::Frontend::FConstNodeHandle InNodeHandle);` — `UE_DEPRECATED(5.6, "ConstNodeHandle is being deprecated, use overload which is provided NodeID instead")`
- L560 _public prototype_ `UMetasoundEditorGraphOutput* FindOutput(FGuid InNodeID) const;`
- L561 _public prototype_ `UMetasoundEditorGraphOutput* FindOutput(FName InName) const;`
- L562 _public prototype_ `UMetasoundEditorGraphOutput* FindOrAddOutput(const FGuid& InNodeID);`
- L565 _public prototype_ `UMetasoundEditorGraphOutput* FindOrAddOutput(Metasound::Frontend::FConstNodeHandle InNodeHandle);` — `UE_DEPRECATED(5.6, "ConstNodeHandle is being deprecated, use overload which is provided NodeID instead")`
- L567 _public prototype_ `UMetasoundEditorGraphVariable* FindVariable(const FGuid& InVariableID) const;`
- L568 _public prototype_ `UMetasoundEditorGraphVariable* FindOrAddVariable(FName VariableName);`
- L571 _public prototype_ `UMetasoundEditorGraphVariable* FindOrAddVariable(const Metasound::Frontend::FConstVariableHandle& InVariableHandle);` — `UE_DEPRECATED(5.6, "ConstVariableHandle is being deprecated, use overload which is provided VariableName instead")`
- L573 _public prototype_ `UMetasoundEditorGraphMember* FindMember(FGuid InMemberID) const;`
- L574 _public prototype_ `UMetasoundEditorGraphMember* FindAdjacentMember(const UMetasoundEditorGraphMember& InMember);`
- L584 _private function_ `template<typename T> TObjectPtr<T> FindAdjacentMemberFromSorted(const TArray<TObjectPtr<T>>& InMembers, TFunction<bool(const TObjectPtr<UMetasoundEditorGraphMember>&)> InPredicate)` — Sorts the incoming members by their MemberName and returns next element after sorting. Will not affect the order of the original list. @param InMembers - Members to sort @param InPredicate - Member to search for @return the adjacent member from the sorted members
- L610 _public function_ `bool RemoveMember(UMetasoundEditorGraphMember& InGraphMember)` — `UE_DEPRECATED(5.5, "Use the associated Frontend builder and synchronize the graph to remove a given editor member.")`
- L613 _public function_ `bool RemoveMemberNodes(UMetasoundEditorGraphMember& InGraphMember)` — `UE_DEPRECATED(5.5, "Use the associated Frontend builder and synchronize the graph to remove all editor member nodes.")`
- L616 _public function_ `bool RemoveFrontendMember(UMetasoundEditorGraphMember& InGraphMember)` — `UE_DEPRECATED(5.5, "Use the associated Frontend builder and synchronize the graph to remove all editor member nodes")`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L34 _namespace_ `namespace Metasound`
- L36 _namespace_ `namespace Editor` (scope `Metasound`)
- L87 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetasoundMemberNameChanged, FGuid );`
- L87 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetasoundMemberNameChanged, FGuid );`
- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnMetasoundMemberRenameRequested);`
- L88 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnMetasoundMemberRenameRequested);`
- L587 _function_ `` (scope `UMetasoundEditorGraph::FindAdjacentMemberFromSorted`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorGraphCommentNode.h` (Public)


#### class `UMetasoundEditorGraphCommentNode`  
`class UMetasoundEditorGraphCommentNode : public UEdGraphNode_Comment`  
_L28-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode_Comment`
- L34 _public prototype_ `static void ConvertToFrontendComment(const UEdGraphNode_Comment& InEdNode, FMetaSoundFrontendGraphComment& OutComment);` — Convenience function to convert underlying ed-graph properties to a frontend graph comment
- L37 _public prototype_ `static void ConvertFromFrontendComment(const FMetaSoundFrontendGraphComment& InComment, UEdGraphNode_Comment& OutEdNode);` — Convenience function to convert underlying ed-graph properties from a frontend graph comment
- L40 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L44 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L45 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L46 _public prototype_ `virtual void ResizeNode(const FVector2f& NewSize) override;`
- L50 _public prototype_ `void SetBounds(const class FSlateRect& Rect);` — Set the Bounds for the comment node
- L52 _public prototype_ `UMetaSoundBuilderBase& GetBuilderChecked() const;`
- L55 _public prototype_ `FGuid GetCommentID() const;` — Get/Set frontend comment ID
- L56 _public prototype_ `void SetCommentID(const FGuid& InGuid);`
- L59 _public prototype_ `UObject& GetMetasoundChecked() const;` — Get this node's MetaSound
- L61 _public prototype_ `bool RemoveFromDocument() const;`
- L64 _public prototype_ `void UpdateFrontendNodeLocation();` — Update the frontend location with this editor node location
- L67 _private prototype_ `FMetasoundAssetBase& GetAssetChecked();`
- L70 _private member_ `FGuid CommentID;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Metasound`
- L21 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorGraphInputNode.h` (Public)


#### class `UMetasoundEditorGraphInputNode`  
`class UMetasoundEditorGraphInputNode : public UMetasoundEditorGraphMemberNode`  
_L23-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberNode`
- L28 _public prototype_ `virtual ~UMetasoundEditorGraphInputNode() = default;`
- L31 _public member_ `TObjectPtr<UMetasoundEditorGraphInput> Input;` — `UPROPERTY()`
- L34 _public member_ `FGuid NodeID;` — `UPROPERTY()`
- L37 _public prototype_ `const FMetasoundEditorGraphVertexNodeBreadcrumb& GetBreadcrumb() const;`
- L39 _public prototype_ `virtual void CacheTitle() override;`
- L41 _public prototype_ `virtual void CacheBreadcrumb() override;`
- L42 _public prototype_ `virtual UMetasoundEditorGraphMember* GetMember() const override;`
- L43 _public prototype_ `virtual void ReconstructNode() override;`
- L45 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const;`
- L46 _public prototype_ `virtual FMetasoundFrontendClassName GetClassName() const;`
- L48 _public prototype_ `virtual FText GetDisplayName() const override;`
- L49 _public prototype_ `virtual FGuid GetNodeID() const override;`
- L50 _public prototype_ `virtual FLinearColor GetNodeTitleTextColor() const override;`
- L51 _public prototype_ `virtual const FSlateBrush* GetNodeTitleIconBrush() const override;`
- L52 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& OutHoverText) const override;`
- L53 _public prototype_ `virtual void Validate(const FMetaSoundFrontendDocumentBuilder& InBuilder, Metasound::Editor::FGraphNodeValidationResult& OutResult) const override;`
- L54 _public prototype_ `virtual bool EnableInteractWidgets() const override;`
- L55 _public prototype_ `virtual FText GetTooltipText() const override;`
- L60 _protected member_ `FMetasoundEditorGraphVertexNodeBreadcrumb Breadcrumb;` — `UPROPERTY()` — Breadcrumb used if associated FrontendNode cannot be found or has been unlinked

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METASOUNDEDITOR_API`

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorGraphMemberDefaults.h` (Public)


#### struct `FMetasoundEditorMemberPageDefault`  
`struct FMetasoundEditorMemberPageDefault`  
_L36-59_
- reflection: `USTRUCT()`
- desc: Editor-only page default for more desirable customization behavior in representing Frontend Literal value. Should never be serialized as generation is non-deterministic.
- L40 _public prototype_ `FMetasoundEditorMemberPageDefault() = default;`
- L41 _public function_ `FMetasoundEditorMemberPageDefault(const FGuid& InPageID) : PageID(InPageID)`
- L49 _public prototype_ `static const FGuid& GetNewEntryID();` — Unique ID used to determine if this default is a newly created and uninitialized member of a given collection.  ID is transient per application cycle, so non-deterministic between editor sessions.
- L53 _public member_ `FName PageName;` — `UPROPERTY(VisibleAnywhere, Category = DefaultValue)` — Selectable PageName
- L58 _public member_ `FGuid PageID = GetNewEntryID();` — `UPROPERTY(Transient, VisibleAnywhere, Category = DefaultValue)` — Used for hash and mirrors document-stored value. Defaults to random value to allow for assignment in post-edit change. Allows for name collisions if user is amidst renaming or rebasing values

#### struct `FMetasoundEditorGraphMemberDefaultBoolRef`  
`struct FMetasoundEditorGraphMemberDefaultBoolRef`  
_L67-73_
- reflection: `USTRUCT()`
- desc: Broken out to be able to customize and swap enum behavior for boolean literal behavior (ex. for triggers)
- L72 _public member_ `bool Value = false;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### struct `FMetasoundEditorMemberPageDefaultBool`  
`struct FMetasoundEditorMemberPageDefaultBool : public FMetasoundEditorMemberPageDefault`  
_L77-89_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L81 _public prototype_ `FMetasoundEditorMemberPageDefaultBool() = default;`
- L82 _public function_ `FMetasoundEditorMemberPageDefaultBool(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L88 _public member_ `FMetasoundEditorGraphMemberDefaultBoolRef Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### class `UMetasoundEditorGraphMemberDefaultBool`  
`class UMetasoundEditorGraphMemberDefaultBool : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L93-128_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L99 _private member_ `TArray<FMetasoundEditorMemberPageDefaultBool> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L102 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultBool() = default;`
- L105 _public member_ `FMetasoundEditorGraphMemberDefaultBoolRef Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L108 _public member_ `EMetasoundBoolMemberDefaultWidget WidgetType = EMetasoundBoolMemberDefaultWidget::None;` — `UPROPERTY(EditAnywhere, Category = Widget, meta = (DisplayName = "Widget"))`
- L110 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L111 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L112 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L113 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L114 _public prototype_ `virtual void ResetDefaults() override;`
- L115 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L116 _public prototype_ `virtual bool Synchronize() override;`
- L117 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L118 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L121 _public function_ `void SetDefault(const bool InDefault)` — `UE_DEPRECATED(5.5, "Use SetFromLiteral instead and broadcast state change delegate explicitly where desired")`
- L123 _public member_ `FOnMetasoundBoolStateChangedEvent OnDefaultStateChanged;`
- L126 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L127 _protected prototype_ `virtual void SortPageDefaults() override;`

#### struct `FMetasoundEditorMemberPageDefaultBoolArray`  
`struct FMetasoundEditorMemberPageDefaultBoolArray : public FMetasoundEditorMemberPageDefault`  
_L132-144_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L136 _public prototype_ `FMetasoundEditorMemberPageDefaultBoolArray() = default;`
- L137 _public function_ `FMetasoundEditorMemberPageDefaultBoolArray(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L143 _public member_ `TArray<FMetasoundEditorGraphMemberDefaultBoolRef> Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### class `UMetasoundEditorGraphMemberDefaultBoolArray`  
`class UMetasoundEditorGraphMemberDefaultBoolArray : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L148-175_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L154 _private member_ `TArray<FMetasoundEditorMemberPageDefaultBoolArray> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L157 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultBoolArray() = default;`
- L160 _public member_ `TArray<FMetasoundEditorGraphMemberDefaultBoolRef> Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L162 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L163 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L164 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L165 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L166 _public prototype_ `virtual void ResetDefaults() override;`
- L167 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L168 _public prototype_ `virtual bool Synchronize() override;`
- L169 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L170 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L173 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L174 _protected prototype_ `virtual void SortPageDefaults() override;`

#### struct `FMetasoundEditorGraphMemberDefaultIntRef`  
`struct FMetasoundEditorGraphMemberDefaultIntRef`  
_L180-186_
- reflection: `USTRUCT()`
- desc: Broken out to be able to customize and swap enum behavior for basic integer literal behavior
- L185 _public member_ `int32 Value = 0;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### struct `FMetasoundEditorMemberPageDefaultInt`  
`struct FMetasoundEditorMemberPageDefaultInt : public FMetasoundEditorMemberPageDefault`  
_L190-202_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L194 _public prototype_ `FMetasoundEditorMemberPageDefaultInt() = default;`
- L195 _public function_ `FMetasoundEditorMemberPageDefaultInt(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L201 _public member_ `FMetasoundEditorGraphMemberDefaultIntRef Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue)`

#### class `UMetasoundEditorGraphMemberDefaultInt`  
`class UMetasoundEditorGraphMemberDefaultInt : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L206-233_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L212 _private member_ `TArray<FMetasoundEditorMemberPageDefaultInt> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L215 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultInt() = default;`
- L218 _public member_ `FMetasoundEditorGraphMemberDefaultIntRef Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L220 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L221 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L222 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L223 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L224 _public prototype_ `virtual void ResetDefaults() override;`
- L225 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L226 _public prototype_ `virtual bool Synchronize() override;`
- L227 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L228 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L231 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L232 _protected prototype_ `virtual void SortPageDefaults() override;`

#### struct `FMetasoundEditorMemberPageDefaultIntArray`  
`struct FMetasoundEditorMemberPageDefaultIntArray : public FMetasoundEditorMemberPageDefault`  
_L237-249_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L241 _public prototype_ `FMetasoundEditorMemberPageDefaultIntArray() = default;`
- L242 _public function_ `FMetasoundEditorMemberPageDefaultIntArray(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L248 _public member_ `TArray<FMetasoundEditorGraphMemberDefaultIntRef> Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### class `UMetasoundEditorGraphMemberDefaultIntArray`  
`class UMetasoundEditorGraphMemberDefaultIntArray : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L253-280_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L259 _private member_ `TArray<FMetasoundEditorMemberPageDefaultIntArray> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L262 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultIntArray() = default;`
- L265 _public member_ `TArray<FMetasoundEditorGraphMemberDefaultIntRef> Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L267 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L268 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L269 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L270 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L271 _public prototype_ `virtual void ResetDefaults() override;`
- L272 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L273 _public prototype_ `virtual bool Synchronize() override;`
- L274 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L275 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L278 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L279 _protected prototype_ `virtual void SortPageDefaults() override;`

#### enum `EMetasoundMemberDefaultWidgetValueType`  
`enum class UE_DEPRECATED(5.5, "EMetasoundMemberDefaultWidgetValueType is deprecated, use EAudioUnitsValueType instead") EMetasoundMemberDefaultWidgetValueType : uint8`  
_L290-295_
- reflection: `UENUM()`
- L292 _public enumerator_ `Linear`
- L293 _public enumerator_ `Frequency UMETA(DisplayName = "Frequency (Log)")`
- L294 _public enumerator_ `Volume`

#### struct `FMetasoundEditorMemberPageDefaultFloat`  
`struct FMetasoundEditorMemberPageDefaultFloat : public FMetasoundEditorMemberPageDefault`  
_L299-311_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L303 _public prototype_ `FMetasoundEditorMemberPageDefaultFloat() = default;`
- L304 _public function_ `FMetasoundEditorMemberPageDefaultFloat(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L310 _public member_ `float Value = 0.0f;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### class `UMetasoundEditorGraphMemberDefaultFloat`  
`class UMetasoundEditorGraphMemberDefaultFloat : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L315-391_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L321 _private member_ `float Default = 0.f;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L324 _private member_ `TArray<FMetasoundEditorMemberPageDefaultFloat> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L327 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultFloat() = default;`
- L330 _public member_ `bool ClampDefault = false;` — `UPROPERTY(EditAnywhere, Category = DefaultValue)`
- L333 _public member_ `FVector2D Range = FVector2D(0.0f, 1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DefaultValue)`
- L336 _public member_ `EMetasoundMemberDefaultWidget WidgetType = EMetasoundMemberDefaultWidget::None;` — `UPROPERTY(EditAnywhere, Category = Widget, meta=(DisplayName = "Widget"))`
- L339 _public member_ `TEnumAsByte<EOrientation> WidgetOrientation = EOrientation::Orient_Horizontal;` — `UPROPERTY(EditAnywhere, Category = Widget, meta=(DisplayName = "Orientation", EditCondition = "WidgetType == EMetasoundMemberDefaultWidget::Slider", EditConditionHides))`
- L345 _public member_ `EMetasoundMemberDefaultWidgetValueType WidgetValueType_DEPRECATED = EMetasoundMemberDefaultWidgetValueType::Linear;` — `UE_DEPRECATED(5.5, "WidgetValueType has been deprecated. Use WidgetUnitValueType instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "WidgetValueType has been deprecated. Use WidgetUnitValueType instead."))`
- L350 _public member_ `EAudioUnitsValueType WidgetUnitValueType = EAudioUnitsValueType::Linear;` — `UPROPERTY(EditAnywhere, Category = Widget, meta = (DisplayName = "Value Type", EditCondition = "WidgetType != EMetasoundMemberDefaultWidget::None", EditConditionHides))`
- L354 _public member_ `bool VolumeWidgetUseLinearOutput = true;` — `UPROPERTY(EditAnywhere, Category = Widget, meta = (DisplayName = "Output Linear"))` — If true, output linear value. Otherwise, output dB value. The volume widget itself will always display the value in dB. The Default Value and Range are linear.
- L358 _public member_ `FVector2D VolumeWidgetDecibelRange = FVector2D(SAudioVolumeRadialSlider::MinDbValue, 0.0f);` — `UPROPERTY(EditAnywhere, Category = Widget, meta = (DisplayName = "Range in dB", EditCondition = "VolumeWidgetUseLinearOutput", EditConditionHides))` — Range in decibels. This will be converted to the linear range in the Default Value category.
- L360 _public member_ `FOnMetasoundInputValueChangedEvent OnDefaultValueChanged;`
- L361 _public member_ `FOnMetasoundRangeChangedEvent OnRangeChanged;`
- L362 _public member_ `FOnMetasoundInputClampDefaultChangedEvent OnClampChanged;`
- L364 _public prototype_ `virtual void ForceRefresh() override;`
- L365 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L366 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L367 _public prototype_ `virtual void Initialize() override;`
- L368 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L369 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L370 _public prototype_ `virtual void ResetDefaults() override;`
- L371 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L372 _public prototype_ `virtual bool Synchronize() override;`
- L373 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L374 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L375 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L378 _public prototype_ `virtual bool MigrateProperties() override;`
- L382 _public prototype_ `void SetInitialRange();` — Set Range to reasonable limit given current Default value
- L384 _public prototype_ `FVector2D GetRange() const;`
- L385 _public prototype_ `void SetRange(const FVector2D InRange);`
- L388 _protected prototype_ `void ClampDefaults();`
- L389 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L390 _protected prototype_ `virtual void SortPageDefaults() override;`

#### struct `FMetasoundEditorMemberPageDefaultFloatArray`  
`struct FMetasoundEditorMemberPageDefaultFloatArray : public FMetasoundEditorMemberPageDefault`  
_L395-407_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L399 _public prototype_ `FMetasoundEditorMemberPageDefaultFloatArray() = default;`
- L400 _public function_ `FMetasoundEditorMemberPageDefaultFloatArray(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L406 _public member_ `TArray<float> Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### class `UMetasoundEditorGraphMemberDefaultFloatArray`  
`class UMetasoundEditorGraphMemberDefaultFloatArray : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L411-438_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L417 _private member_ `TArray<FMetasoundEditorMemberPageDefaultFloatArray> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L420 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultFloatArray() = default;`
- L423 _public member_ `TArray<float> Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L425 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L426 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L427 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L428 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L429 _public prototype_ `virtual void ResetDefaults() override;`
- L430 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L431 _public prototype_ `virtual bool Synchronize() override;`
- L432 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L433 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L436 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L437 _protected prototype_ `virtual void SortPageDefaults() override;`

#### struct `FMetasoundEditorMemberPageDefaultString`  
`struct FMetasoundEditorMemberPageDefaultString : public FMetasoundEditorMemberPageDefault`  
_L442-454_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L446 _public prototype_ `FMetasoundEditorMemberPageDefaultString() = default;`
- L447 _public function_ `FMetasoundEditorMemberPageDefaultString(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L453 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### class `UMetasoundEditorGraphMemberDefaultString`  
`class UMetasoundEditorGraphMemberDefaultString : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L458-485_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L463 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultString() = default;`
- L466 _public member_ `FString Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L470 _private member_ `TArray<FMetasoundEditorMemberPageDefaultString> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L472 _private prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L473 _private prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L474 _private prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L475 _private prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L476 _private prototype_ `virtual void ResetDefaults() override;`
- L477 _private prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L478 _private prototype_ `virtual bool Synchronize() override;`
- L479 _private prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L480 _private prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L483 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L484 _protected prototype_ `virtual void SortPageDefaults() override;`

#### struct `FMetasoundEditorMemberPageDefaultStringArray`  
`struct FMetasoundEditorMemberPageDefaultStringArray : public FMetasoundEditorMemberPageDefault`  
_L489-501_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L493 _public prototype_ `FMetasoundEditorMemberPageDefaultStringArray() = default;`
- L494 _public function_ `FMetasoundEditorMemberPageDefaultStringArray(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L500 _public member_ `TArray<FString> Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### class `UMetasoundEditorGraphMemberDefaultStringArray`  
`class UMetasoundEditorGraphMemberDefaultStringArray : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L505-532_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L511 _private member_ `TArray<FMetasoundEditorMemberPageDefaultStringArray> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L514 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultStringArray() = default;`
- L517 _public member_ `TArray<FString> Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L519 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L520 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L521 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L522 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L523 _public prototype_ `virtual void ResetDefaults() override;`
- L524 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L525 _public prototype_ `virtual bool Synchronize() override;`
- L526 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L527 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L530 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L531 _protected prototype_ `virtual void SortPageDefaults() override;`

#### struct `FMetasoundEditorGraphMemberDefaultObjectRef`  
`struct FMetasoundEditorGraphMemberDefaultObjectRef`  
_L536-542_
- reflection: `USTRUCT()`
- desc: Broken out to be able to customize and swap AllowedClass based on provided object proxy
- L541 _public member_ `TObjectPtr<UObject> Object = nullptr;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### struct `FMetasoundEditorMemberPageDefaultObjectRef`  
`struct FMetasoundEditorMemberPageDefaultObjectRef : public FMetasoundEditorMemberPageDefault`  
_L545-557_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L549 _public prototype_ `FMetasoundEditorMemberPageDefaultObjectRef() = default;`
- L550 _public function_ `FMetasoundEditorMemberPageDefaultObjectRef(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L556 _public member_ `FMetasoundEditorGraphMemberDefaultObjectRef Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue)`

#### class `UMetasoundEditorGraphMemberDefaultObject`  
`class UMetasoundEditorGraphMemberDefaultObject : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L560-586_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L565 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultObject() = default;`
- L568 _public member_ `FMetasoundEditorGraphMemberDefaultObjectRef Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L571 _public member_ `TArray<FMetasoundEditorMemberPageDefaultObjectRef> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L573 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L574 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L575 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L576 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L577 _public prototype_ `virtual void ResetDefaults() override;`
- L578 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L579 _public prototype_ `virtual bool Synchronize() override;`
- L580 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L581 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`
- L584 _protected prototype_ `virtual void ResolvePageDefaults() override;`
- L585 _protected prototype_ `virtual void SortPageDefaults() override;`

#### struct `FMetasoundEditorMemberPageDefaultObjectArray`  
`struct FMetasoundEditorMemberPageDefaultObjectArray : public FMetasoundEditorMemberPageDefault`  
_L589-601_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorMemberPageDefault`
- L593 _public prototype_ `FMetasoundEditorMemberPageDefaultObjectArray() = default;`
- L594 _public function_ `FMetasoundEditorMemberPageDefaultObjectArray(const FGuid& InPageID) : FMetasoundEditorMemberPageDefault(InPageID)`
- L600 _public member_ `TArray<FMetasoundEditorGraphMemberDefaultObjectRef> Value;` — `UPROPERTY(EditAnywhere, Category = DefaultValue, meta = (DisplayName = "Default"))`

#### class `UMetasoundEditorGraphMemberDefaultObjectArray`  
`class UMetasoundEditorGraphMemberDefaultObjectArray : public UMetasoundEditorGraphMemberDefaultLiteral`  
_L604-628_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberDefaultLiteral`
- L609 _private member_ `TArray<FMetasoundEditorMemberPageDefaultObjectArray> Defaults;` — `UPROPERTY(EditAnywhere, Transient, Category = DefaultValue, meta = (NoResetToDefault, NoElementDuplicate, EditFixedOrder))`
- L612 _public prototype_ `virtual ~UMetasoundEditorGraphMemberDefaultObjectArray() = default;`
- L615 _public member_ `TArray<FMetasoundEditorGraphMemberDefaultObjectRef> Default;` — `UPROPERTY(meta = (Deprecated = 5.5, DeprecationMessage = "Default is no longer serialized and is privately managed to support per-page default values"))`
- L617 _public prototype_ `virtual EMetasoundFrontendLiteralType GetLiteralType() const override;`
- L618 _public prototype_ `virtual void InitDefault(const FGuid& InPageID = Metasound::Frontend::DefaultPageID) override;`
- L619 _public prototype_ `virtual void IterateDefaults(TFunctionRef<void(const FGuid&, FMetasoundFrontendLiteral)> Iter) const override;`
- L620 _public prototype_ `virtual bool RemoveDefault(const FGuid& InPageID) override;`
- L621 _public prototype_ `virtual void ResetDefaults() override;`
- L622 _public prototype_ `virtual void ResolvePageDefaults() override;`
- L623 _public prototype_ `virtual void SetFromLiteral(const FMetasoundFrontendLiteral& InLiteral, const FGuid& InPageID) override;`
- L624 _public prototype_ `virtual void SortPageDefaults() override;`
- L625 _public prototype_ `virtual bool Synchronize() override;`
- L626 _public prototype_ `virtual bool TryFindDefault(FMetasoundFrontendLiteral& OutLiteral, const FGuid* InPageID = nullptr) const override;`
- L627 _public prototype_ `virtual void UpdatePreviewInstance(const Metasound::FVertexName& InParameterName, TScriptInterface<IAudioParameterControllerInterface>& InParameterInterface) const override;`

#### Free symbols / members of external scopes

- L63 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetasoundBoolStateChangedEvent, bool, const FGuid& );` — For bool input widget
- L63 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetasoundBoolStateChangedEvent, bool, const FGuid& );` — For bool input widget
- L284 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetasoundInputValueChangedEvent, FGuid , float );` — For input widget
- L284 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetasoundInputValueChangedEvent, FGuid , float );` — For input widget
- L285 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetasoundRangeChangedEvent, FVector2D);`
- L285 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetasoundRangeChangedEvent, FVector2D);`
- L286 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetasoundInputClampDefaultChangedEvent, bool);`
- L286 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMetasoundInputClampDefaultChangedEvent, bool);`

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorGraphNode.h` (Public)


#### struct `FMetasoundEditorGraphNodeBreadcrumb`  
`struct FMetasoundEditorGraphNodeBreadcrumb`  
_L46-65_
- reflection: `USTRUCT()`
- L51 _public member_ `FMetasoundFrontendClassName ClassName;` — `UPROPERTY()`
- L54 _public member_ `bool bIsClassNative = true;` — `UPROPERTY()`
- L57 _public member_ `TInstancedStruct<FMetaSoundFrontendNodeConfiguration> NodeConfiguration;` — `UPROPERTY()`
- L61 _public member_ `TOptional<FNodeTemplateGenerateInterfaceParams> TemplateParams;` — `UPROPERTY()` — For use with template nodes only
- L64 _public member_ `FMetasoundFrontendVersionNumber Version;` — `UPROPERTY()`

#### struct `FMetasoundEditorGraphMemberNodeBreadcrumb`  
`struct FMetasoundEditorGraphMemberNodeBreadcrumb : public FMetasoundEditorGraphNodeBreadcrumb`  
_L68-86_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorGraphNodeBreadcrumb`
- L73 _public member_ `FName MemberName;` — `UPROPERTY()`
- L76 _public member_ `FName DataType;` — `UPROPERTY()`
- L79 _public member_ `TMap<FGuid, FMetasoundFrontendLiteral> DefaultLiterals;` — `UPROPERTY()`
- L82 _public member_ `FMetasoundFrontendVertexMetadata VertexMetadata;` — `UPROPERTY()`
- L85 _public member_ `TOptional<FSoftObjectPath> MemberMetadataPath;` — `UPROPERTY()`

#### struct `FMetasoundEditorGraphVertexNodeBreadcrumb`  
`struct FMetasoundEditorGraphVertexNodeBreadcrumb : public FMetasoundEditorGraphMemberNodeBreadcrumb`  
_L89-95_
- reflection: `USTRUCT()`
- inherits: `FMetasoundEditorGraphMemberNodeBreadcrumb`
- L94 _public member_ `EMetasoundFrontendVertexAccessType AccessType = EMetasoundFrontendVertexAccessType::Unset;` — `UPROPERTY()`

#### class `UMetasoundEditorGraphNode`  
`class UMetasoundEditorGraphNode : public UEdGraphNode`  
_L98-256_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L104 _public prototype_ `void CreateInputPin();` — Create a new input pin for this node
- L107 _public prototype_ `int32 EstimateNodeWidth() const;` — Estimate the width of this Node from the length of its title
- L109 _public prototype_ `void IteratePins(TUniqueFunction<void(UEdGraphPin& , int32 )> Func, EEdGraphPinDirection InPinDirection = EGPD_MAX);`
- L112 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L113 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L114 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L115 _public prototype_ `virtual bool CanUserDeleteNode() const override;`
- L116 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L117 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& OutHoverText) const override;`
- L118 _public prototype_ `virtual FString GetDocumentationExcerptName() const override;`
- L119 _public prototype_ `virtual FString GetDocumentationLink() const override;`
- L120 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L121 _public prototype_ `virtual FText GetTooltipText() const override;`
- L122 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L123 _public prototype_ `virtual void ReconstructNode() override;`
- L124 _public prototype_ `virtual FString GetPinMetaData(FName InPinName, FName InKey) override;`
- L125 _public prototype_ `virtual void OnUpdateCommentText(const FString& NewComment) override;`
- L129 _public prototype_ `virtual void PreSave(FObjectPreSaveContext InSaveContext) override;` — UObject interface
- L131 _public prototype_ `virtual void PostLoad() override;`
- L132 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InEvent) override;`
- L133 _public prototype_ `virtual void PostEditUndo() override;`
- L135 _public prototype_ `virtual void PostEditImport() override;`
- L136 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L139 _public function_ `virtual bool ShouldShowTitleIcon() const`
- L140 _public prototype_ `virtual const FSlateBrush* GetNodeTitleIconBrush() const;`
- L141 _public function_ `virtual FLinearColor GetNodeTitleIconColor() const`
- L142 _public function_ `virtual FText GetNodeTitleIconTooltipText() const`
- L143 _public function_ `virtual FName GetCornerIcon() const`
- L144 _public function_ `virtual bool CanAddInputPin() const`
- L146 _public prototype_ `UMetaSoundBuilderBase& GetBuilderChecked() const;`
- L151 _public prototype_ `const FMetasoundFrontendClass* GetFrontendClass() const;` — Returns document's cached Frontend Node Class (as defined by the document's dependency array). If node or class is not found on document, returns null.
- L155 _public prototype_ `const FMetasoundFrontendNode* GetFrontendNode() const;` — Returns document's cached Frontend Node. If node is not found on document, returns null.
- L156 _public prototype_ `const FMetasoundFrontendNode& GetFrontendNodeChecked() const;`
- L158 _public prototype_ `virtual const FMetasoundEditorGraphNodeBreadcrumb& GetBreadcrumb() const;`
- L164 _public function_ `virtual void CacheBreadcrumb()` — Caches any "breadcrumb" data associated with a particular MetaSound Editor node. Called when copying edgraph data to the clipboard or validating for fast access. Also generally provides a mechanism for MetaSound nodes to cache Frontend data for use to look-up Frontend data if re-associated should the associated document data/node becomes unlinked.
- L166 _public prototype_ `UObject* GetMetasound() const;`
- L167 _public prototype_ `UObject& GetMetasoundChecked() const;`
- L169 _public prototype_ `const FMetasoundFrontendClass* GetNodeFrontendClass() const;`
- L170 _public prototype_ `const UClass* GetNodeAssetClass() const;`
- L172 _public prototype_ `virtual bool RemoveFromDocument() const;`
- L175 _public prototype_ `void SetNodeLocation(const FVector2D& InLocation);` — `UE_DEPRECATED(5.4, "Use UpdateFrontendNodeLocation and/or SyncLocationFromFrontendNode")`
- L178 _public prototype_ `void SyncCommentFromFrontendNode();` — Finds the associated node with the given ID and sets this EdGraphNode's comment and comment visibility boolean.
- L182 _public prototype_ `bool SyncLocationFromFrontendNode(bool bUpdateEditorNodeID = false);` — Finds the associated node with the given ID and sets this EdGraphNode's location. Returns whether or not node ID entry exists and if location was set.
- L185 _public prototype_ `void UpdateFrontendNodeLocation(const FVector2D& InLocation);` — Helper function that sets the associated frontend node's location. Does NOT set this EdGraphNode's location.
- L187 _public prototype_ `Metasound::Frontend::FGraphHandle GetRootGraphHandle() const;`
- L188 _public prototype_ `Metasound::Frontend::FConstGraphHandle GetConstRootGraphHandle() const;`
- L191 _public prototype_ `Metasound::Frontend::FNodeHandle GetNodeHandle() const;` — `UE_DEPRECATED(5.6, "Node Handles are actively being deprecated, use the MetaSound Frontend Document Builder API")`
- L193 _public prototype_ `Metasound::Frontend::FConstNodeHandle GetConstNodeHandle() const;`
- L194 _public prototype_ `Metasound::Frontend::FDataTypeRegistryInfo GetPinDataTypeInfo(const UEdGraphPin& InPin) const;`
- L196 _public prototype_ `TSet<FString> GetDisallowedPinClassNames(const UEdGraphPin& InPin) const;`
- L198 _public function_ `virtual FGuid GetNodeID() const`
- L199 _public prototype_ `virtual FText GetDisplayName() const;`
- L200 _public prototype_ `virtual void CacheTitle();`
- L203 _public function_ `virtual void Validate(Metasound::Editor::FGraphNodeValidationResult& OutResult)` — `UE_DEPRECATED(5.7, "Use const version that is passed builder")`
- L205 _public prototype_ `virtual void Validate(const FMetaSoundFrontendDocumentBuilder& Builder, Metasound::Editor::FGraphNodeValidationResult& OutResult) const;`
- L208 _public prototype_ `void SyncChangeIDs();` — Mark node for refresh
- L210 _public function_ `FText GetCachedTitle() const`
- L213 _public prototype_ `bool ContainsClassChange() const;` — Returns whether or not the class interface, metadata, or style has been changed since the last node refresh
- L216 _public prototype_ `bool TryGetPinVisualizationValue(FName InPinName, bool& OutValue) const;` — Graph node visualization widgets can attempt to get the current value of the given named input pin. For connected input pins, a value may not be returned unless sound preview is active.
- L217 _public prototype_ `bool TryGetPinVisualizationValue(FName InPinName, int32& OutValue) const;`
- L218 _public prototype_ `bool TryGetPinVisualizationValue(FName InPinName, float& OutValue) const;`
- L221 _public function_ `template<class T> inline TOptional<T> GetPinVisualizationValue(FName InPinName) const`
- L244 _protected member_ `FGuid InterfaceChangeID;`
- L245 _protected member_ `FGuid MetadataChangeID;`
- L246 _protected member_ `FGuid StyleChangeID;`
- L250 _protected member_ `FText CachedTitle;` — Not be serialized to avoid text desync as the registry can provide a new name if the external definition changes between application sessions.
- L252 _protected prototype_ `static bool ShowNodeDebugData();`
- L255 _protected function_ `virtual void SetNodeID(FGuid InNodeID)` — `UE_DEPRECATED(5.4, "Now set directly on implementing nodes")`

#### class `UMetasoundEditorGraphMemberNode`  
`class UMetasoundEditorGraphMemberNode : public UMetasoundEditorGraphNode`  
_L260-283_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UMetasoundEditorGraphNode`
- desc: Node that represents a graph member
- L266 _public function_ `virtual UMetasoundEditorGraphMember* GetMember() const PURE_VIRTUAL(UMetasoundEditorGraphMemberNode::GetMember, return nullptr;)` — Whether or not the member node supports interactivity on the graph node
- L276 _public prototype_ `static bool ClampFloatLiteral(const UMetasoundEditorGraphMemberDefaultFloat* DefaultFloatLiteral, FMetasoundFrontendLiteral& LiteralValue);` — Clamp float literal value based on the given default float literal. Returns whether the literal was clamped.
- L279 _protected prototype_ `virtual FString GetFindReferenceSearchString_Impl(EGetFindReferenceSearchStringFlags InFlags) const override;`
- L281 _protected prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L282 _protected prototype_ `virtual FLinearColor GetNodeTitleIconColor() const override;`

#### class `UMetasoundEditorGraphOutputNode`  
`class UMetasoundEditorGraphOutputNode : public UMetasoundEditorGraphMemberNode`  
_L287-330_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberNode`
- desc: Node that represents a graph output
- L293 _public member_ `TObjectPtr<UMetasoundEditorGraphOutput> Output;` — `UPROPERTY()`
- L295 _public prototype_ `const FMetasoundEditorGraphVertexNodeBreadcrumb& GetBreadcrumb() const;`
- L297 _public prototype_ `virtual void CacheBreadcrumb() override;`
- L299 _public prototype_ `virtual FGuid GetNodeID() const override;`
- L300 _public prototype_ `virtual UMetasoundEditorGraphMember* GetMember() const override;`
- L307 _public prototype_ `virtual bool CanUserDeleteNode() const override;` — Disallow deleting outputs as they require being connected to some part of the graph by the Frontend Graph Builder (which is enforced even when the Editor Graph Node does not have a visible input by way of a literal input.
- L309 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* InPin) override;`
- L310 _public prototype_ `virtual void ReconstructNode() override;`
- L311 _public prototype_ `virtual bool RemoveFromDocument() const override;`
- L314 _public prototype_ `virtual bool EnableInteractWidgets() const override;` — Disables interact widgets (ex. sliders, knobs) when input is connected
- L316 _public prototype_ `virtual void Validate(const FMetaSoundFrontendDocumentBuilder& InBuilder, Metasound::Editor::FGraphNodeValidationResult& OutResult) const override;`
- L321 _protected member_ `FMetasoundEditorGraphVertexNodeBreadcrumb Breadcrumb;` — `UPROPERTY()` — Breadcrumb used if associated FrontendNode cannot be found or has been unlinked
- L323 _protected prototype_ `virtual FLinearColor GetNodeTitleTextColor() const override;`
- L324 _protected prototype_ `virtual const FSlateBrush* GetNodeTitleIconBrush() const override;`
- L325 _protected prototype_ `virtual void SetNodeID(FGuid InNodeID) override;`

#### class `UMetasoundEditorGraphExternalNode`  
`class UMetasoundEditorGraphExternalNode : public UMetasoundEditorGraphNode`  
_L333-376_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphNode`
- L339 _protected member_ `FMetasoundEditorGraphNodeBreadcrumb Breadcrumb;` — `UPROPERTY()`
- L342 _protected member_ `FMetasoundFrontendClassName ClassName;` — `UPROPERTY(meta = (Deprecated = "5.4", DeprecationMessage = "Use Breadcrumb value when manipulating clipboard data or validating. Otherwise, look-up frontend node's associated class directly"))`
- L345 _protected member_ `FGuid NodeID;` — `UPROPERTY()`
- L348 _protected member_ `bool bIsClassNative = true;` — `UPROPERTY(meta = (Deprecated = "5.4", DeprecationMessage = "Use Breadcrumb value when manipulating clipboard data or validating, Otherwise, look-up frontend node's associated class directly"))`
- L351 _public prototype_ `virtual const FMetasoundEditorGraphNodeBreadcrumb& GetBreadcrumb() const override;`
- L352 _public function_ `virtual FGuid GetNodeID() const override`
- L353 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L354 _public prototype_ `virtual const FSlateBrush* GetNodeTitleIconBrush() const override;`
- L355 _public prototype_ `virtual FText GetNodeTitleIconTooltipText() const override;`
- L356 _public prototype_ `virtual bool ShouldDrawNodeAsControlPointOnly(int32& OutInputPinIndex, int32& OutOutputPinIndex) const override;`
- L358 _public prototype_ `virtual void ReconstructNode() override;`
- L359 _public prototype_ `virtual void CacheBreadcrumb() override;`
- L360 _public prototype_ `virtual void CacheTitle() override;`
- L361 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& OutHoverText) const override;`
- L363 _public prototype_ `FMetasoundFrontendVersionNumber FindHighestVersionInRegistry() const;`
- L364 _public prototype_ `bool CanAutoUpdate() const;`
- L367 _public prototype_ `virtual void Validate(const FMetaSoundFrontendDocumentBuilder& InBuilder, Metasound::Editor::FGraphNodeValidationResult& OutResult) const override;` — Validates node and returns whether or not the node is valid.
- L370 _public prototype_ `void HideUnconnectedPins(const bool InHidePins);` — Set Unconnected Pins hidden/Unhidden

#### class `UMetasoundEditorGraphVariableNode`  
`class UMetasoundEditorGraphVariableNode : public UMetasoundEditorGraphMemberNode`  
_L380-430_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetasoundEditorGraphMemberNode`
- desc: Represents any of the several variable node types (Accessor, DeferredAccessor, Mutator).
- L387 _protected member_ `EMetasoundFrontendClassType ClassType;` — `UPROPERTY()` — Class type of the frontend node (Accessor, DeferredAccessor or Mutator)
- L391 _protected member_ `FMetasoundFrontendClassName ClassName;` — `UPROPERTY()` — Class name of the frontend node.
- L395 _protected member_ `FGuid NodeID;` — `UPROPERTY()` — ID of the frontend node.
- L400 _public member_ `TObjectPtr<UMetasoundEditorGraphVariable> Variable;` — `UPROPERTY()` — Associated graph variable.
- L403 _public function_ `virtual void CacheTitle() override` — Variables do not have titles to distinguish more visually from vertex types
- L405 _public prototype_ `virtual const FMetasoundEditorGraphNodeBreadcrumb& GetBreadcrumb() const override;`
- L407 _public prototype_ `virtual void CacheBreadcrumb() override;`
- L408 _public prototype_ `virtual UMetasoundEditorGraphMember* GetMember() const override;`
- L409 _public prototype_ `virtual bool EnableInteractWidgets() const override;`
- L411 _public prototype_ `virtual FGuid GetNodeID() const override;`
- L412 _public prototype_ `virtual FName GetCornerIcon() const override;`
- L413 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& OutHoverText) const override;`
- L414 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L416 _public prototype_ `virtual EMetasoundFrontendClassType GetClassType() const;`
- L421 _protected member_ `FMetasoundEditorGraphMemberNodeBreadcrumb Breadcrumb;` — `UPROPERTY()` — Breadcrumb used if associated FrontendNode cannot be found or has been unlinked
- L423 _protected prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L424 _protected prototype_ `virtual const FSlateBrush* GetNodeTitleIconBrush() const override;`
- L425 _protected prototype_ `virtual void SetNodeID(FGuid InNodeID) override;`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace EMessageSeverity`
- L33 _namespace_ `namespace Metasound`
- L33 _namespace_ `namespace Editor` (scope `Metasound`)
- L41 _typedef_ `using FSortedClassVersionMap = TMap<FName, TArray<FMetasoundFrontendVersionNumber>>;` (scope `Metasound::Editor`) — Map of class names to sorted array of registered version numbers

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorGraphSchema.h` (Public)


#### enum `Metasound::Editor::EPrimaryContextGroup`  
`enum class EPrimaryContextGroup : uint8`  
_L32-45_
- desc: Ordered such that highest priority is highest value
- L34 _public enumerator_ `Conversions = 0`
- L35 _public enumerator_ `Graphs`
- L36 _public enumerator_ `Functions`
- L37 _public enumerator_ `Outputs`
- L38 _public enumerator_ `Inputs`
- L39 _public enumerator_ `Variables`
- L40 _public enumerator_ `Favorites`
- L43 _public enumerator_ `Recents` — This MUST be the last one before Common, because the space between them is reserved for Recent actions ordered by most recent.
- L44 _public enumerator_ `Common = 255`

#### class `Metasound::Editor::ISchemaQueryResult`  
`class ISchemaQueryResult`  
_L49-67_
- L52 _public prototype_ `virtual ~ISchemaQueryResult() = default;`
- L54 _public prototype_ `virtual bool CanConnectInputOfTypeAndAccess(FName TypeName, EMetasoundFrontendVertexAccessType AccessType) const = 0;`
- L55 _public prototype_ `virtual bool CanConnectOutputOfTypeAndAccess(FName TypeName, EMetasoundFrontendVertexAccessType AccessType) const = 0;`
- L57 _public prototype_ `virtual FMetasoundFrontendClassMetadata GenerateClassMetadata() const = 0;`
- L58 _public prototype_ `virtual EMetasoundFrontendClassAccessFlags GetAccessFlags() const = 0;`
- L59 _public prototype_ `virtual FMetaSoundAssetKey GetAssetKey() const = 0;`
- L60 _public prototype_ `virtual const TArray<FText>& GetCategoryHierarchy() const = 0;`
- L61 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L62 _public prototype_ `virtual const TArray<FText>& GetKeywords() const = 0;`
- L63 _public prototype_ `virtual EMetasoundFrontendClassType GetRegistryClassType() const = 0;`
- L64 _public prototype_ `virtual FText GetTooltip() const = 0;`
- L66 _public prototype_ `virtual bool IsNative() const = 0;`

#### struct `Metasound::Editor::FActionVertexFilters`  
`struct FActionVertexFilters`  
_L71-88_
- L73 _public member_ `FName InputTypeName = { };`
- L74 _public member_ `EMetasoundFrontendVertexAccessType InputAccessType = EMetasoundFrontendVertexAccessType::Unset;`
- L76 _public function_ `bool HasInputFilters() const`
- L81 _public member_ `FName OutputTypeName = { };`
- L82 _public member_ `EMetasoundFrontendVertexAccessType OutputAccessType = EMetasoundFrontendVertexAccessType::Unset;`
- L84 _public function_ `bool HasOutputFilters() const`

#### struct `FMetasoundGraphSchemaAction`  
`struct FMetasoundGraphSchemaAction : public FEdGraphSchemaAction`  
_L104-145_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L108 _public function_ `static FName StaticGetTypeId()`
- L109 _public function_ `virtual FName GetTypeId() const override`
- L111 _public function_ `FMetasoundGraphSchemaAction() : FEdGraphSchemaAction()`
- L116 _public function_ `FMetasoundGraphSchemaAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup, FText InKeywords = FText::GetEmpty()) : FEdGraphSchemaAction( MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), static_cast<int32>(InGroup), MoveTemp(InKeywords))`
- L126 _public prototype_ `virtual ~FMetasoundGraphSchemaAction() = default;`
- L128 _public function_ `virtual const FSlateBrush* GetIconBrush() const`
- L133 _public function_ `virtual const FLinearColor& GetIconColor() const`
- L140 _public function_ `virtual FString GetUniqueStableFavoriteKey() const` — Used to store & match Recent and Favorite MetaSounds graph actions in the MetaSounds editor

#### struct `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`  
`struct FMetasoundGraphSchemaAction_NodeWithMultipleOutputs : public FMetasoundGraphSchemaAction`  
_L149-168_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction`
- desc: This is used to combine functionality for nodes that can have multiple outputs and should never be directly instantiated.
- L153 _public function_ `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs() : FMetasoundGraphSchemaAction()`
- L157 _public function_ `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs(FText InNodeCategory, FText InMenuDesc, FText InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup, FText InKeywords = FText::GetEmpty()) : FMetasoundGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGroup, InKeywords)`
- L161 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NodeWithMultipleOutputs() = default;`
- L165 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L166 _public function_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true)`

#### struct `FMetasoundGraphSchemaAction_NewInput`  
`struct FMetasoundGraphSchemaAction_NewInput : public FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`  
_L172-202_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`
- desc: Action to add an input node of an existing graph input to the graph
- L177 _public member_ `FGuid NodeID;` — `UPROPERTY()`
- L179 _public function_ `FMetasoundGraphSchemaAction_NewInput() : FMetasoundGraphSchemaAction_NodeWithMultipleOutputs()`
- L183 _public prototype_ `FMetasoundGraphSchemaAction_NewInput(FText InNodeCategory, FText InDisplayName, FGuid InInputNodeID, FText InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup);`
- L185 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewInput() = default;`
- L188 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L190 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L192 _public function_ `virtual FString GetUniqueStableFavoriteKey() const override`
- L200 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_NewGraphMember`  
`struct FMetasoundGraphSchemaAction_NewGraphMember : public FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`  
_L206-225_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`
- desc: Action to add a new graph member and member node to the graph, with the given default literal
- L210 _public function_ `FMetasoundGraphSchemaAction_NewGraphMember() : FMetasoundGraphSchemaAction_NodeWithMultipleOutputs()`
- L214 _public function_ `FMetasoundGraphSchemaAction_NewGraphMember(FName InDataType, FMetasoundFrontendLiteral InLiteral, FText InNodeCategory, FText InMenuDesc, FText InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup) : FMetasoundGraphSchemaAction_NodeWithMultipleOutputs(InNodeCategory, InMenuDesc, InToolTip, InGroup) , DataType(InDataType) , DefaultLiteral(InLiteral)`
- L220 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewGraphMember() = default;`
- L223 _protected member_ `FName DataType;`
- L224 _protected member_ `FMetasoundFrontendLiteral DefaultLiteral;`

#### struct `FMetasoundGraphSchemaAction_NewGraphInput`  
`struct FMetasoundGraphSchemaAction_NewGraphInput : public FMetasoundGraphSchemaAction_NewGraphMember`  
_L229-250_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NewGraphMember`
- desc: Action to add a new graph input and input node to the graph, with the given default literal
- L233 _public function_ `FMetasoundGraphSchemaAction_NewGraphInput() : FMetasoundGraphSchemaAction_NewGraphMember()`
- L237 _public prototype_ `FMetasoundGraphSchemaAction_NewGraphInput(FName DataType, FMetasoundFrontendLiteral InLiteral);`
- L239 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewGraphInput() = default;`
- L242 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L243 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L248 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_NewGraphOutput`  
`struct FMetasoundGraphSchemaAction_NewGraphOutput : public FMetasoundGraphSchemaAction_NewGraphMember`  
_L254-275_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NewGraphMember`
- desc: Action to add a new graph output and output node to the graph, with the given default literal
- L258 _public function_ `FMetasoundGraphSchemaAction_NewGraphOutput() : FMetasoundGraphSchemaAction_NewGraphMember()`
- L262 _public prototype_ `FMetasoundGraphSchemaAction_NewGraphOutput(FName DataType, FMetasoundFrontendLiteral InLiteral);`
- L264 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewGraphOutput() = default;`
- L267 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L268 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L273 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_NewGraphVariable`  
`struct FMetasoundGraphSchemaAction_NewGraphVariable : public FMetasoundGraphSchemaAction_NewGraphMember`  
_L279-300_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NewGraphMember`
- desc: Action to add a new graph variable and getter node to the graph, with the given default literal
- L283 _public function_ `FMetasoundGraphSchemaAction_NewGraphVariable() : FMetasoundGraphSchemaAction_NewGraphMember()`
- L287 _public prototype_ `FMetasoundGraphSchemaAction_NewGraphVariable(FName DataType, FMetasoundFrontendLiteral InLiteral);`
- L289 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewGraphVariable() = default;`
- L292 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L293 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L298 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_PromoteToInput`  
`struct FMetasoundGraphSchemaAction_PromoteToInput : public FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`  
_L304-316_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`
- desc: Promotes an input to a graph input, using its respective literal value as the default value
- L308 _public prototype_ `FMetasoundGraphSchemaAction_PromoteToInput();`
- L310 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_PromoteToInput() = default;`
- L314 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_NewOutput`  
`struct FMetasoundGraphSchemaAction_NewOutput : public FMetasoundGraphSchemaAction`  
_L320-350_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction`
- desc: Adds an output to the graph
- L325 _public member_ `FGuid NodeID;` — `UPROPERTY()`
- L327 _public function_ `FMetasoundGraphSchemaAction_NewOutput() : FMetasoundGraphSchemaAction()`
- L331 _public prototype_ `FMetasoundGraphSchemaAction_NewOutput(FText InNodeCategory, FText InDisplayName, FGuid InOutputNodeID, FText InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup);`
- L333 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewOutput() = default;`
- L336 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L338 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L340 _public function_ `virtual FString GetUniqueStableFavoriteKey() const override`
- L348 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_PromoteToOutput`  
`struct FMetasoundGraphSchemaAction_PromoteToOutput : public FMetasoundGraphSchemaAction`  
_L354-366_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction`
- desc: Promotes a node output to a graph output
- L358 _public prototype_ `FMetasoundGraphSchemaAction_PromoteToOutput();`
- L360 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_PromoteToOutput() = default;`
- L364 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_NewVariableNode`  
`struct FMetasoundGraphSchemaAction_NewVariableNode : public FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`  
_L370-412_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`
- desc: Adds a variable node to the graph
- L375 _public member_ `FGuid VariableID;` — `UPROPERTY()`
- L377 _public function_ `FMetasoundGraphSchemaAction_NewVariableNode() : FMetasoundGraphSchemaAction_NodeWithMultipleOutputs()`
- L381 _public prototype_ `FMetasoundGraphSchemaAction_NewVariableNode(FText InNodeCategory, FText InDisplayName, FGuid InVariableID, FText InToolTip);`
- L383 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewVariableNode() = default;`
- L387 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L391 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L393 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L395 _public function_ `virtual FString GetUniqueStableFavoriteKey() const override`
- L403 _protected function_ `virtual Metasound::Frontend::FNodeHandle CreateFrontendVariableNode(const Metasound::Frontend::FGraphHandle& InFrontendGraph, const FGuid& InVariableID) const` — `UE_DEPRECATED(5.6, "Deprecated in favor of direct creation via Document Builder API")`
- L408 _protected function_ `virtual const FMetasoundFrontendNode* CreateFrontendVariableNode(FMetaSoundFrontendDocumentBuilder& DocBuilder) const`

#### struct `FMetasoundGraphSchemaAction_NewVariableAccessorNode`  
`struct FMetasoundGraphSchemaAction_NewVariableAccessorNode : public FMetasoundGraphSchemaAction_NewVariableNode`  
_L416-431_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NewVariableNode`
- desc: Adds a variable node to the graph
- L420 _public function_ `FMetasoundGraphSchemaAction_NewVariableAccessorNode() : FMetasoundGraphSchemaAction_NewVariableNode()`
- L424 _public prototype_ `FMetasoundGraphSchemaAction_NewVariableAccessorNode(FText InNodeCategory, FText InDisplayName, FGuid InVariableID, FText InToolTip);`
- L426 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewVariableAccessorNode() = default;`
- L429 _protected prototype_ `virtual const FMetasoundFrontendNode* CreateFrontendVariableNode(FMetaSoundFrontendDocumentBuilder& DocBuilder) const override;`

#### struct `FMetasoundGraphSchemaAction_NewVariableDeferredAccessorNode`  
`struct FMetasoundGraphSchemaAction_NewVariableDeferredAccessorNode : public FMetasoundGraphSchemaAction_NewVariableNode`  
_L435-449_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NewVariableNode`
- desc: Adds a variable node to the graph
- L439 _public function_ `FMetasoundGraphSchemaAction_NewVariableDeferredAccessorNode() : FMetasoundGraphSchemaAction_NewVariableNode()`
- L443 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewVariableDeferredAccessorNode() = default;`
- L445 _public prototype_ `FMetasoundGraphSchemaAction_NewVariableDeferredAccessorNode(FText InNodeCategory, FText InDisplayName, FGuid InVariableID, FText InToolTip);`
- L448 _protected prototype_ `virtual const FMetasoundFrontendNode* CreateFrontendVariableNode(FMetaSoundFrontendDocumentBuilder& DocBuilder) const override;`

#### struct `FMetasoundGraphSchemaAction_NewVariableMutatorNode`  
`struct FMetasoundGraphSchemaAction_NewVariableMutatorNode : public FMetasoundGraphSchemaAction_NewVariableNode`  
_L453-467_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NewVariableNode`
- desc: Adds a variable node to the graph
- L457 _public function_ `FMetasoundGraphSchemaAction_NewVariableMutatorNode() : FMetasoundGraphSchemaAction_NewVariableNode()`
- L461 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewVariableMutatorNode() = default;`
- L463 _public prototype_ `FMetasoundGraphSchemaAction_NewVariableMutatorNode(FText InNodeCategory, FText InDisplayName, FGuid InVariableID, FText InToolTip);`
- L466 _protected prototype_ `virtual const FMetasoundFrontendNode* CreateFrontendVariableNode(FMetaSoundFrontendDocumentBuilder& DocBuilder) const override;`

#### struct `FMetasoundGraphSchemaAction_PromoteToVariable_AccessorNode`  
`struct FMetasoundGraphSchemaAction_PromoteToVariable_AccessorNode : public FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`  
_L471-483_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`
- desc: Promotes an input to a graph variable & respective getter node, using its respective literal value as the default value
- L475 _public prototype_ `FMetasoundGraphSchemaAction_PromoteToVariable_AccessorNode();`
- L477 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_PromoteToVariable_AccessorNode() = default;`
- L481 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_PromoteToVariable_MutatorNode`  
`struct FMetasoundGraphSchemaAction_PromoteToVariable_MutatorNode : public FMetasoundGraphSchemaAction`  
_L487-499_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction`
- desc: Promotes an output to a graph variable & respective setter node, using its respective literal value as the default value
- L491 _public prototype_ `FMetasoundGraphSchemaAction_PromoteToVariable_MutatorNode();`
- L493 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_PromoteToVariable_MutatorNode() = default;`
- L497 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_PromoteToVariable_DeferredAccessorNode`  
`struct FMetasoundGraphSchemaAction_PromoteToVariable_DeferredAccessorNode : public FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`  
_L503-515_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`
- desc: Promotes an input to a graph variable & respective deferred getter node, using its respective literal value as the default value
- L507 _public prototype_ `FMetasoundGraphSchemaAction_PromoteToVariable_DeferredAccessorNode();`
- L509 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_PromoteToVariable_DeferredAccessorNode() = default;`
- L513 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_NewNode`  
`struct FMetasoundGraphSchemaAction_NewNode : public FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`  
_L520-551_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NodeWithMultipleOutputs`
- desc: Action to add a node to the graph
- L524 _public member_ `TSharedPtr<Metasound::Editor::ISchemaQueryResult> QueryResult;`
- L526 _public function_ `FMetasoundGraphSchemaAction_NewNode() : FMetasoundGraphSchemaAction_NodeWithMultipleOutputs()`
- L530 _public function_ `FMetasoundGraphSchemaAction_NewNode(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup, FText InKeywords = FText::GetEmpty(), TOptional<Metasound::Editor::FDroppedObjectsInfo> InDroppedObjectsInfo = {}) : FMetasoundGraphSchemaAction_NodeWithMultipleOutputs(InNodeCategory, InMenuDesc, InToolTip, InGroup, InKeywords) , DroppedObjectsInfo(InDroppedObjectsInfo)`
- L535 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewNode() = default;`
- L538 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L540 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L542 _public prototype_ `virtual FString GetUniqueStableFavoriteKey() const override;`
- L547 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L550 _private member_ `TOptional<Metasound::Editor::FDroppedObjectsInfo> DroppedObjectsInfo;`

#### struct `FMetasoundGraphSchemaAction_NewFromSelected`  
`struct FMetasoundGraphSchemaAction_NewFromSelected : public FMetasoundGraphSchemaAction_NewNode`  
_L555-573_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction_NewNode`
- desc: Action to add nodes to the graph based on selected objects
- L559 _public function_ `FMetasoundGraphSchemaAction_NewFromSelected() : FMetasoundGraphSchemaAction_NewNode()`
- L563 _public function_ `FMetasoundGraphSchemaAction_NewFromSelected(FText InNodeCategory, FText InMenuDesc, FText InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup) : FMetasoundGraphSchemaAction_NewNode(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGroup)`
- L567 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewFromSelected() = default;`
- L571 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_NewAudioAnalyzer`  
`struct FMetasoundGraphSchemaAction_NewAudioAnalyzer : public FMetasoundGraphSchemaAction`  
_L577-591_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction`
- desc: Action to create new Audio Analyzer node
- L581 _public prototype_ `FMetasoundGraphSchemaAction_NewAudioAnalyzer();`
- L584 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L589 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_NewReroute`  
`struct FMetasoundGraphSchemaAction_NewReroute : public FMetasoundGraphSchemaAction`  
_L595-618_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction`
- desc: Action to create new reroute node
- L599 _public prototype_ `FMetasoundGraphSchemaAction_NewReroute() = default;`
- L600 _public prototype_ `FMetasoundGraphSchemaAction_NewReroute(const FLinearColor* InIconColor, bool bInShouldTransact = true);`
- L602 _public prototype_ `virtual ~FMetasoundGraphSchemaAction_NewReroute() = default;`
- L605 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L607 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L612 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L616 _private member_ `FLinearColor IconColor;`
- L617 _private member_ `bool bShouldTransact = true;`

#### struct `FMetasoundGraphSchemaAction_NewComment`  
`struct FMetasoundGraphSchemaAction_NewComment : public FMetasoundGraphSchemaAction`  
_L622-644_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction`
- desc: Action to create new comment
- L626 _public function_ `FMetasoundGraphSchemaAction_NewComment() : FMetasoundGraphSchemaAction()`
- L630 _public function_ `FMetasoundGraphSchemaAction_NewComment(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup) : FMetasoundGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGroup)`
- L635 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L637 _public prototype_ `virtual const FLinearColor& GetIconColor() const override;`
- L642 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FMetasoundGraphSchemaAction_Paste`  
`struct FMetasoundGraphSchemaAction_Paste : public FMetasoundGraphSchemaAction`  
_L648-663_
- reflection: `USTRUCT()`
- inherits: `FMetasoundGraphSchemaAction`
- desc: Action to paste clipboard contents into the graph
- L652 _public function_ `FMetasoundGraphSchemaAction_Paste() : FMetasoundGraphSchemaAction()`
- L656 _public function_ `FMetasoundGraphSchemaAction_Paste(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, Metasound::Editor::EPrimaryContextGroup InGroup) : FMetasoundGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGroup)`
- L661 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### class `UMetasoundEditorGraphSchema`  
`class UMetasoundEditorGraphSchema : public UEdGraphSchema`  
_L666-730_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L672 _public prototype_ `bool ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;` — Check whether connecting these pins would cause a loop
- L675 _public prototype_ `void GetPaletteActions(FGraphActionMenuBuilder& ActionMenuBuilder) const;` — Helper method to add items valid to the palette list
- L678 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L679 _public prototype_ `virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L680 _public prototype_ `virtual FText GetPinDisplayName(const UEdGraphPin* Pin) const override;`
- L681 _public prototype_ `virtual float GetActionFilteredWeight(const FEdGraphSchemaAction& InCurrentAction, const TArray<FString>& InFilterTerms, const TArray<FString>& InSanitizedFilterTerms, const TArray<UEdGraphPin*>& DraggedFromPins) const override;`
- L682 _public prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L683 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L684 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L685 _public prototype_ `virtual void TrySetDefaultObject(UEdGraphPin& Pin, UObject* NewDefaultObject, bool bInMarkAsModified) const override;`
- L686 _public prototype_ `virtual void TrySetDefaultValue(UEdGraphPin& Pin, const FString& InNewDefaultValue, bool bInMarkAsModified) const override;`
- L687 _public prototype_ `virtual bool SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* InNodeToDelete) const override;`
- L688 _public prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L689 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L690 _public prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L691 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L692 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L693 _public prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L694 _public prototype_ `virtual void GetAssetsPinHoverMessage(const TArray<FAssetData>& Assets, const UEdGraphPin* HoverPin, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L695 _public prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L696 _public prototype_ `virtual void DroppedAssetsOnPin(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphPin* Pin) const override;`
- L697 _public prototype_ `virtual int32 GetNodeSelectionCount(const UEdGraph* Graph) const override;`
- L698 _public prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;`
- L699 _public prototype_ `virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2f& GraphPosition) const override;`
- L700 _public prototype_ `virtual void SetNodePosition(UEdGraphNode* Node, const FVector2f& Position) const;`
- L703 _public prototype_ `void BreakNodeLinks(UEdGraphNode& TargetNode, bool bShouldActuallyTransact) const;`
- L706 _private prototype_ `void QueryNodeClasses(TFunctionRef<void(TUniquePtr<Metasound::Editor::ISchemaQueryResult>&&)> OnClassFound) const;`
- L709 _private prototype_ `void GetConversionActions(FGraphActionMenuBuilder& ActionMenuBuilder, Metasound::Editor::FActionVertexFilters InFilters = Metasound::Editor::FActionVertexFilters(), bool bShowSelectedActions = true) const;` — Adds actions for creating actions associated with graph DataTypes
- L710 _private prototype_ `void GetFunctionActions(FGraphActionMenuBuilder& ActionMenuBuilder, Metasound::Editor::FActionVertexFilters InFilters = Metasound::Editor::FActionVertexFilters(), bool bShowSelectedActions = true, Metasound::Frontend::FConstGraphHandle InGraphHandle = Metasound::Frontend::IGraphController::GetInvalidHandle(), const UEdGraph* CurrentGraph = nullptr) const;`
- L711 _private prototype_ `void GetVariableActions(FGraphActionMenuBuilder& ActionMenuBuilder, Metasound::Editor::FActionVertexFilters InFilters = Metasound::Editor::FActionVertexFilters(), bool bShowSelectedActions = true, Metasound::Frontend::FConstGraphHandle InGraphHandle = Metasound::Frontend::IGraphController::GetInvalidHandle()) const;`
- L713 _private prototype_ `void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin, bool bShouldTransact) const;`
- L715 _private prototype_ `void GetDataTypeInputNodeActions(FGraphContextMenuBuilder& InMenuBuilder, Metasound::Frontend::FConstGraphHandle InGraphHandle, Metasound::Editor::FInterfaceNodeFilterFunction InFilter = Metasound::Editor::FInterfaceNodeFilterFunction(), bool bShowSelectedActions = true) const;`
- L716 _private prototype_ `void GetDataTypeOutputNodeActions(FGraphContextMenuBuilder& InMenuBuilder, Metasound::Frontend::FConstGraphHandle InGraphHandle, Metasound::Editor::FInterfaceNodeFilterFunction InFilter = Metasound::Editor::FInterfaceNodeFilterFunction(), bool bShowSelectedActions = true) const;`
- L719 _private prototype_ `void GetCommentAction(FGraphActionMenuBuilder& ActionMenuBuilder, const UEdGraph* CurrentGraph = nullptr) const;` — Adds action for creating a comment
- L722 _private prototype_ `void DroppedMetaSoundAssetsOnGraph(const TArray<FMetasoundAssetBase*>& MetaSoundAssets, const FVector2f& GraphPosition, UMetasoundEditorGraph* MetaSoundGraph) const;` — Process dropped assets
- L723 _private prototype_ `void DroppedNonMetaSoundAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UMetasoundEditorGraph* MetaSoundGraph) const;`
- L726 _private prototype_ `bool ValidateDroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString* OutTooltipText = nullptr) const;` — Validate dropped assets, returning true if valid
- L727 _private prototype_ `bool ValidateDroppedAssetsOnPin(const TArray<FAssetData>& Assets, const UEdGraphPin* Pin, FString* OutTooltipText = nullptr) const;`
- L729 _private prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L29 _namespace_ `namespace Metasound`
- L29 _namespace_ `namespace Editor` (scope `Metasound`)
- L47 _prototype_ `const FText& GetContextGroupDisplayName(EPrimaryContextGroup InContextGroup);` (scope `Metasound::Editor`)
- L69 _typedef_ `using FInterfaceNodeFilterFunction = TFunction<bool(Frontend::FConstNodeHandle)>;` (scope `Metasound::Editor`)
- L90 _namespace_ `namespace SchemaUtils` (scope `Metasound::Editor`)
- L92 _prototype_ `UEdGraphNode* PromoteToInput(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const UE::Slate::FDeprecateVector2DParameter& InLocation, bool bSelectNewNode, TOptional<FMetasoundFrontendLiteral> Literal = {});` (scope `Metasound::Editor::SchemaUtils`)
- L93 _prototype_ `UEdGraphNode* PromoteToOutput(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const UE::Slate::FDeprecateVector2DParameter& InLocation, bool bSelectNewNode);` (scope `Metasound::Editor::SchemaUtils`)
- L94 _prototype_ `UEdGraphNode* PromoteToVariable(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const UE::Slate::FDeprecateVector2DParameter& InLocation, bool bSelectNewNode);` (scope `Metasound::Editor::SchemaUtils`)
- L95 _prototype_ `UEdGraphNode* PromoteToDeferredVariable(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const UE::Slate::FDeprecateVector2DParameter& InLocation, bool bSelectNewNode);` (scope `Metasound::Editor::SchemaUtils`)
- L96 _prototype_ `UEdGraphNode* PromoteToMutatorVariable(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const UE::Slate::FDeprecateVector2DParameter& InLocation, bool bSelectNewNode);` (scope `Metasound::Editor::SchemaUtils`)
- L98 _variable_ `const FName MetasoundGraphSchemaActionType("FMe` (scope `Metasound::Editor::SchemaUtils`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorGraphValidation.h` (Public)


#### struct `Metasound::Editor::FGraphNodeValidationResult`  
`struct FGraphNodeValidationResult`  
_L18-44_
- L20 _public prototype_ `FGraphNodeValidationResult(UMetasoundEditorGraphNode& InNode);`
- L26 _public prototype_ `bool GetHasDirtiedNode() const;` — Whether or not validation operations on result have dirtied the associated Node (Validation doesn't mark node as dirtied to avoid resave being required at asset level)
- L28 _public prototype_ `UMetasoundEditorGraphNode& GetNodeChecked() const;`
- L32 _public prototype_ `bool GetIsInvalid() const;` — Whether associated node is in invalid state, i.e. may fail to build or may result in undefined behavior.
- L34 _public prototype_ `void SetMessage(EMessageSeverity::Type InSeverity, const FString& InMessage);`
- L35 _public prototype_ `void SetPinOrphaned(UEdGraphPin& Pin, bool bIsOrphaned);`
- L36 _public prototype_ `void SetUpgradeMessage(const FText& InMessage);`
- L40 _private member_ `UMetasoundEditorGraphNode* Node = nullptr;` — Node associated with validation result
- L43 _private member_ `bool bHasDirtiedNode = false;` — Whether validation made changes to the node and is now in a dirty state

#### struct `Metasound::Editor::FGraphValidationResults`  
`struct FGraphValidationResults`  
_L46-55_
- L48 _public member_ `TArray<FGraphNodeValidationResult> NodeResults;`
- L51 _public prototype_ `const TArray<FGraphNodeValidationResult>& GetResults() const;` — Results corresponding with node validation
- L54 _public prototype_ `EMessageSeverity::Type GetHighestMessageSeverity() const;` — Returns highest message severity of validated nodes

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L14 _namespace_ `namespace Metasound`
- L16 _namespace_ `namespace Editor` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorModule.h` (Public)


#### struct `Metasound::Editor::FCreateGraphNodeVisualizationWidgetParams`  
`struct FCreateGraphNodeVisualizationWidgetParams`  
_L61-64_
- L63 _public member_ `UMetasoundEditorGraphNode* MetaSoundNode = nullptr;`

#### class `Metasound::Editor::IMetasoundEditorModule`  
`class IMetasoundEditorModule : public IModuleInterface`  
_L69-139_
- inherits: `IModuleInterface`
- L73 _public member_ `static constexpr FLazyName ModuleName = "Me` — Module name constant for use with FModuleManager.
- L76 _public prototype_ `virtual bool IsExplicitProxyClass(const UClass& InClass) const = 0;` — `UE_DEPRECATED(5.3, "IsExplicitProxyClass is deprecated, use Metasound::Frontend::FDataTypeRegistryInfo::bIsExplicit")`
- L79 _public prototype_ `virtual void RegisterExplicitProxyClass(const UClass& InClass) = 0;` — `UE_DEPRECATED(5.3, "RegisterExplicitProxyClass is deprecated, use Metasound::TIsExplicit<>")`
- L82 _public prototype_ `virtual bool IsMetaSoundAssetClass(const FTopLevelAssetPath& InClassName) const = 0;` — `UE_DEPRECATED(5.3, "IsMetaSoundAssetClass is deprecated, use IMetasoundUObjectRegistry::IsRegisteredClass")`
- L85 _public function_ `virtual void PrimeAssetRegistryAsync()` — `UE_DEPRECATED(5.5, "Prime no longer supported (nor recommended as AssetTag updates now enable querying MetaSound assets for interface information without loading full asset.")`
- L88 _public prototype_ `virtual EAssetPrimeStatus GetAssetRegistryPrimeStatus() const;` — `UE_DEPRECATED(5.5, "Prime no longer supported (nor recommended as AssetTag updates now enable querying MetaSound assets for interface information without loading full asset.")`
- L91 _public prototype_ `virtual EAssetScanStatus GetAssetRegistryScanStatus() const;` — `UE_DEPRECATED(5.5, "Use FMetaSoundAssetManager::IsInitialAssetScanComplete instead")`
- L93 _public prototype_ `virtual TUniquePtr<FMetasoundDefaultLiteralCustomizationBase> CreateMemberDefaultLiteralCustomization(UClass& InClass, IDetailCategoryBuilder& DefaultCategoryBuilder) const = 0;`
- L98 _public prototype_ `virtual const TSubclassOf<UMetasoundEditorGraphMemberDefaultLiteral> FindDefaultLiteralClass(EMetasoundFrontendLiteralType InLiteralType) const = 0;`
- L101 _public prototype_ `virtual const FEdGraphPinType* FindPinType(FName InDataTypeName) const = 0;` — `UE_DEPRECATED(5.8, "Use IMetaSoundGraphPanelPinFactory::FindPinType instead.")`
- L103 _public prototype_ `virtual const FSlateBrush* GetIconBrush(FName InDataType, const bool bIsConstructorType) const = 0;`
- L106 _public prototype_ `virtual bool GetCustomPinIcons(UEdGraphPin* InPin, const FSlateBrush*& PinConnectedIcon, const FSlateBrush*& PinDisconnectedIcon) const = 0;` — `UE_DEPRECATED(5.8, "Use IMetaSoundGraphPanelPinFactory::GetCustomPinIcons instead.")`
- L109 _public prototype_ `virtual bool GetCustomPinIcons(FName InDataType, const FSlateBrush*& PinConnectedIcon, const FSlateBrush*& PinDisconnectedIcon) const = 0;` — `UE_DEPRECATED(5.8, "Use IMetaSoundGraphPanelPinFactory::GetCustomPinIcons instead.")`
- L112 _public prototype_ `virtual TSharedRef<IMetaSoundGraphPanelPinFactory> GetGraphPanelPinFactory() const = 0;` — Returns the MetaSound GraphPanelPinFactory for registering custom pin types.
- L115 _public prototype_ `virtual void RegisterPinType(FName InDataTypeName, FName InPinCategory = { }, FName InPinSubCategory = { }, const FSlateBrush* InPinConnectedIcon = nullptr, const FSlateBrush* InPinDisconnectedIcon = nullptr) = 0;` — `UE_DEPRECATED(5.8, "Use IMetaSoundGraphPanelPinFactory::RegisterPin instead.")`
- L119 _public prototype_ `virtual void RegisterCustomPinType(FName InDataTypeName, const FGraphPinParams& Params) = 0;` — `UE_DEPRECATED(5.8, "Use IMetaSoundGraphPanelPinFactory::RegisterPin instead.")`
- L132 _public prototype_ `virtual void RegisterGraphNodeVisualization(FName InNodeClassName, FOnCreateGraphNodeVisualizationWidget OnCreateGraphNodeVisualizationWidget) = 0;` — For the given node class, register a delegate that can be used for creating in-graph node visualizations.
- L135 _public prototype_ `virtual bool IsRestrictedMode() const = 0;` — Queries if the MetaSound Editor is in "restricted mode" (i.e. can only make new presets and not make new assets or edit asset graphs)
- L138 _public prototype_ `virtual void SetRestrictedMode(bool bInRestricted) = 0;` — Sets if the MetaSound editor is in "restricted mode" (i.e. can only make new presets and not make new assets or edit asset graphs)

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L35 _namespace_ `namespace Metasound`
- L35 _namespace_ `namespace Engine` (scope `Metasound`)
- L41 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetasoundEditor, Log, All);`
- L41 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetasoundEditor, Log, All);`
- L44 _namespace_ `namespace Metasound`
- L44 _namespace_ `namespace Editor` (scope `Metasound`)
- L46 _namespace_ `namespace Style` (scope `Metasound::Editor`)
- L48 _prototype_ `FSlateIcon CreateSlateIcon(FName InName);` (scope `Metasound::Editor::Style`)
- L49 _prototype_ `const FSlateBrush& GetSlateBrushSafe(FName InName);` (scope `Metasound::Editor::Style`)
- L51 _prototype_ `const FSlateColor& GetPageExecutingColor();` (scope `Metasound::Editor::Style`)
- L56 _typedef_ `using EAssetScanStatus = Metasound::Engine::EAssetScanStatus;` (scope `Metasound::Editor`)
- L57 _typedef_ `using EAssetPrimeStatus = Metasound::Engine::ENodeClassRegistryPrimeStatus;` (scope `Metasound::Editor`)
- L58 _typedef_ `using FCreateNodeConfigurationDetails = TFunction<TSharedRef<FMetaSoundNodeConfigurationCustomization>( TSharedPtr<IPropertyHandle> InStructProperty, TWeakObjectPtr<UMetasoundEditorGraphNode> InNode)>;` (scope `Metasound::Editor`)
- L66 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnCreateGraphNodeVisualizationWidget, const FCreateGraphNodeVisualizationWidgetParams&);`
- L66 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnCreateGraphNodeVisualizationWidget, const FCreateGraphNodeVisualizationWidgetParams&);` (scope `Metasound::Editor`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundEditorSubsystem.h` (Public)


#### class `UMetaSoundEditorSubsystem`  
`class UMetaSoundEditorSubsystem : public UEditorSubsystem`  
_L27-162_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "MetaSound Editor Subsystem"))`
- inherits: `UEditorSubsystem`
- desc: The subsystem in charge of editor MetaSound functionality
- L45 _public prototype_ `bool BindMemberMetadata( FMetaSoundFrontendDocumentBuilder& Builder, UMetasoundEditorGraphMember& InMember, TSubclassOf<UMetasoundEditorGraphMemberDefaultLiteral> LiteralClass, UMetasoundEditorGraphMemberDefaultLiteral* TemplateObject = nullptr);` — Binds literal editor Metadata to the given member.  If the literal already exists, adds literal reference to given member (asserts that existing literal is of similar subclass provided).  If it does not exist, or an optional template object is provided, metadata is generated then bound. Returns true if new literal metadata was generated, false if not. Asserts if bind failed.
- L58 _public prototype_ `UPARAM(DisplayName = "MetaSound Asset") TScriptInterface<IMetaSoundDocumentInterface> BuildToAsset( UPARAM(DisplayName = "Builder") UMetaSoundBuilderBase* InBuilder, const FString& Author, const FString& AssetName, const FString& PackagePath, EMetaSoundBuilderResult& OutResult, UPARAM(DisplayName = "Template SoundWave") const USoundWave* TemplateSou` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder|Editor", meta = (WorldContext = "Parent", ExpandEnumAsExecs = "OutResult"))` — Build the given builder to a MetaSound asset @param Author - Sets the author on the given builder's document. @param AssetName - Name of the asset to build. @param PackagePath - Path of package to build asset to. @param TemplateSoundWave - SoundWave settings such as attenuation, modulation, and sound class will be copied from the optional TemplateSoundWave. For preset builders, TemplateSoundWave will override the template values from the referenced asset.
- L67 _public prototype_ `UMetasoundEditorGraphMemberDefaultLiteral* CreateMemberMetadata(FMetaSoundFrontendDocumentBuilder& Builder, FName InMemberName, TSubclassOf<UMetasoundEditorGraphMemberDefaultLiteral> LiteralClass) const;` — `UE_DEPRECATED(5.8, "Functionality is now private")`
- L72 _public prototype_ `UPARAM(DisplayName = "Builder") UMetaSoundBuilderBase* FindOrBeginBuilding(TScriptInterface<IMetaSoundDocumentInterface> MetaSound, EMetaSoundBuilderResult& OutResult)` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder|Editor", meta = (DisplayName = "Find Or Begin Building MetaSound Asset", ExpandEnumAsExecs = "OutResult"))` — Returns a builder for the given MetaSound asset. Returns null if provided a transient MetaSound. For finding builders for transient MetaSounds, use the UMetaSoundBuilderSubsystem's API (FindPatchBuilder, FindSourceBuilder, FindBuilderByName etc.)
- L76 _public prototype_ `UPARAM(DisplayName = "Input Metadata") UMetaSoundFrontendMemberMetadata* FindOrCreateGraphInputMetadata(UPARAM(DisplayName = "Builder") UMetaSoundBuilderBase* InBuilder, FName InputName, EMetaSoundBuild` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Find graph input metadata (which includes editor only range information for floats) for a given input. If the metadata does not exist, create it.
- L80 _public prototype_ `TSubclassOf<UMetasoundEditorGraphMemberDefaultLiteral> GetLiteralClassForType(FName TypeName) const;` — Returns the corresponding literal class for a given type
- L84 _public prototype_ `FName GetBuildPage(UMetaSoundBuilderBase* Builder) const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder|Editor")` — Get the build page
- L89 _public prototype_ `UPARAM(DisplayName = "Builder") UMetaSoundBuilderBase* InBuilder, UPARAM(DisplayName = "Node Handle") const FMetaSoundNodeHandle& InNode, UPARAM(DisplayName = "Location") const FVector2D& InLocation, EMetaSoundBuilderResult& OutResult);`
- L96 _public prototype_ `void InitAsset(UObject& InNewMetaSound, FInitAssetArgs InitAssetArgs = { });` — Initialize the UObject asset with optional initialization arguments to be applied. Clears the existing MetaSound document (for the case of duplicated assets).
- L99 _public prototype_ `void InitAsset(UObject& InNewMetaSound, UObject* InReferencedMetaSound = nullptr, const bool bClearDocument = false);` — `UE_DEPRECATED(5.8, "Use overload that is passed optional initialization arguments. Call SetSoundWaveSettingsFromTemplate directly if desired.")`
- L103 _public prototype_ `bool IsPageAuditionPlatformCookTarget(FName InPageName) const;` — Returns whether or not a page with the given name both exists and is set as a valid, cooked target for the currently set audition platform in editor.
- L104 _public prototype_ `bool IsPageAuditionPlatformCookTarget(const FGuid& InPageID) const;`
- L108 _public prototype_ `UPARAM(DisplayName = "Builder Listener") UMetaSoundEditorBuilderListener* AddBuilderDelegateListener(UMetaSoundBuilderBase* InBuilder, EMetaSoundBuilderRes` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder|Editor", meta = (ExpandEnumAsExecs = "OutResult"))` — Add a builder listener for a builder which is used to add and remove custom editor builder delegates.
- L114 _public prototype_ `void RegisterGraphWithFrontend(UObject& InMetaSound, bool bInForceViewSynchronization = false) const;` — Wraps RegisterGraphWithFrontend logic in Frontend with any additional logic required to refresh editor & respective editor object state. @param InMetaSound - MetaSound to register @param bInForceSynchronize - Forces the synchronize flag for all open graphs being registered by this call (all referenced graphs and referencing graphs open in editors)
- L117 _public prototype_ `void RegisterToolbarExtender(TSharedRef<FExtender> InExtender);` — Register toolbar extender that will be displayed in the MetaSound Asset Editor.
- L124 _public prototype_ `void SetFocusedPage(UMetaSoundBuilderBase* Builder, FName PageName, bool bOpenEditor, EMetaSoundBuilderResult& OutResult) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "Audio|MetaSound|Builder|Editor", meta = (ExpandEnumAsExecs = "OutResult"))` — If the given page name is implemented on the provided builder, sets the focused (and build) page of the provided builder to the associated page and sets the audition page to the provided name. If the given builder has an asset editor open, optionally opens or brings that editor's associated PageID into user focus.
- L130 _public prototype_ `void SetBuildPage(UMetaSoundBuilderBase* Builder, FName PageName, EMetaSoundBuilderResult& OutResult) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "Audio|MetaSound|Builder|Editor", meta = (ExpandEnumAsExecs = "OutResult"))` — If the given page name is implemented on the provided builder, sets the build page. This page will be the page that graph operations (ex. node add) will be applied to by default if a page name is not specified.
- L137 _public prototype_ `bool SetFocusedPage(UMetaSoundBuilderBase& Builder, const FGuid& InPageID, bool bOpenEditor, bool bPostTransaction = true) const;` — If the given PageID is implemented on the provided builder, sets the focused page of the provided builder to the associated page and sets the audition target page to the provided ID. If the given builder has an asset editor open, optionally opens or brings that editor's associated PageID into user focus. Returns whether or not the audition page was set to the provided focus page.
- L140 _public prototype_ `bool UnregisterToolbarExtender(TSharedRef<FExtender> InExtender);` — Unregisters toolbar extender that is displayed in the MetaSound Asset Editor.
- L143 _public prototype_ `const FString GetDefaultAuthor();` — Get the default author for a MetaSound asset
- L146 _public prototype_ `const TArray<TSharedRef<FExtender>>& GetToolbarExtenders() const;` — Returns all currently toolbar extenders registered to be displayed within the MetaSound Asset Editor.
- L149 _public prototype_ `void SetSoundWaveSettingsFromTemplate(USoundWave& NewMetasound, const USoundWave& TemplateSoundWave) const;` — Copy over sound wave settings such as attenuation, modulation, and sound class from the template sound wave to the MetaSound
- L151 _public prototype_ `static UMetaSoundEditorSubsystem& GetChecked();`
- L152 _public prototype_ `static const UMetaSoundEditorSubsystem& GetConstChecked();`
- L155 _private prototype_ `UMetasoundEditorGraphMemberDefaultLiteral* CreateMemberMetadata(FMetaSoundFrontendDocumentBuilder& Builder, TSubclassOf<UMetasoundEditorGraphMemberDefaultLiteral> LiteralClass) const;`
- L157 _private prototype_ `bool SetFocusedPageInternal(FName PageName, const FGuid& InPageID, UMetaSoundBuilderBase& Builder, bool bOpenEditor, bool bPostTransaction, bool bSetAuditionPage = true) const;`
- L161 _private member_ `TArray<TSharedRef<FExtender>> EditorToolbarExtenders;` — Editor Toolbar Extenders

#### struct `UMetaSoundEditorSubsystem::FInitAssetArgs`  
`struct FInitAssetArgs`  
_L32-39_
- L35 _public member_ `TInstancedStruct<FMetaSoundFrontendDocumentTemplate> Template;` — (Optional) Template to apply to newly initialized asset
- L38 _public member_ `TArray<UObject*> SelectedObjects;` — Currently selected objects in the focused ContentBrowser.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METASOUNDEDITOR_API`

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundFactory.h` (Public)


#### class `UMetaSoundBaseFactory`  
`class UMetaSoundBaseFactory : public UFactory`  
_L19-33_
- reflection: `UCLASS(abstract)`
- inherits: `UFactory`
- L24 _private member_ `TObjectPtr<UObject> ReferencedMetaSoundObject;` — `UPROPERTY(Transient, meta = (Deprecated = 5.8, DeprecationMessage = "Use document template instead"))`
- L27 _private member_ `TInstancedStruct<FMetaSoundFrontendDocumentTemplate> Template;` — `UPROPERTY(EditAnywhere, Transient, meta = (Category = Factory))`
- L32 _private member_ `TArray<TObjectPtr<UObject>> SelectedObjects;` — `UPROPERTY(EditAnywhere, Transient, meta = (Category = Factory))` — If Document configuration is set, selection is provided to the configuration as an initial argument to be set on the configuration if applicable.

#### class `UMetaSoundFactory`  
`class UMetaSoundFactory : public UMetaSoundBaseFactory`  
_L36-43_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UMetaSoundBaseFactory`
- L41 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InFeedbackContext) override;`

#### class `UMetaSoundSourceFactory`  
`class UMetaSoundSourceFactory : public UMetaSoundBaseFactory`  
_L46-53_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UMetaSoundBaseFactory`
- L51 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InFeedbackContext) override;`

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundNodeConfigurationCustomization.h` (Public)


#### class `Metasound::Editor::FMetaSoundNodeConfigurationCustomization`  
`class FMetaSoundNodeConfigurationCustomization : public FInstancedStructDataDetails`  
_L17-32_
- inherits: `FInstancedStructDataDetails`
- L20 _public function_ `FMetaSoundNodeConfigurationCustomization(TSharedPtr<IPropertyHandle> InStructProperty, TWeakObjectPtr<UMetasoundEditorGraphNode> InNode) : FInstancedStructDataDetails(InStructProperty) , GraphNode(InNode)`
- L26 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow) override;`
- L29 _protected prototype_ `void OnChildPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L31 _protected member_ `TWeakObjectPtr<UMetasoundEditorGraphNode> GraphNode;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API METASOUNDEDITOR_API`
- L15 _namespace_ `namespace Metasound`
- L15 _namespace_ `namespace Editor` (scope `Metasound`)
- L34 _typedef_ `using FMetaSoundNodeConfigurationDataDetails UE_DEPRECATED(5.8, "FMetaSoundNodeConfigurationDataDetails has bee` (scope `Metasound::Editor`)

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundPresetWidgetInterface.h` (Public)


#### class `UMetaSoundPresetWidgetInterface`  
`class UMetaSoundPresetWidgetInterface : public UAudioPanelWidgetInterface`  
_L19-22_
- reflection: `UINTERFACE(Blueprintable, MinimalAPI)`
- inherits: `UAudioPanelWidgetInterface`
- desc: IMetaSoundPresetWidgetInterface has been soft deprecated. Use IMetaSoundTemplateWidgetInterface instead.

#### class `IMetaSoundPresetWidgetInterface`  
`class IMetaSoundPresetWidgetInterface : public IAudioPanelWidgetInterface`  
_L24-46_
- inherits: `IAudioPanelWidgetInterface`
- L33 _public prototype_ `void GetSupportedMetaSounds(bool& bSupportAllPresets, TArray<TScriptInterface<IMetaSoundDocumentInterface>>& ExcludedMetaSounds, TArray<TScriptInterface<IMetaSoundDocumentInterface>>& IncludedMetaSounds) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaSound Preset Widget")` — The MetaSounds whose presets are supported by this widget. If Support All Presets is true, this widget is supported by all presets except those in the Excluded array. MetaSounds in the include/exclude arrays can be MetaSound presets or non presets. If a MetaSound is not a preset, then presets of that MetaSound will be supported/excluded by this widget.
- L37 _public prototype_ `void OnConstructed(UMetaSoundBuilderBase* Builder);` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaSound Preset Widget", meta = (DisplayName = "On MetaSoundPreset Widget Constructed"))` — Called when the preset widget is constructed, giving the builder of the associated MetaSound preset
- L41 _public prototype_ `void OnAuditionStateChanged(UAudioComponent* AudioComponent, bool bIsAuditioning);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MetaSound Preset Widget", meta = (DisplayName = "On MetaSound Audition State Changed"))` — Called when the MetaSound starts and stops auditioning. Provides a reference to the audio component when auditioning starts, and returns nullptr when auditioning stops.
- L45 _public prototype_ `void OnInitializingTab(FMetaSoundTemplateWidgetTabInfo& TabInfo);` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaSound Preset Widget", meta = (DisplayName = "On Initializing Tab"))` — (Optional) Called when initializing a tab owning the given widget to allow implementation to provide basic tab display options and information.

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/MetasoundTemplateWidgetInterface.h` (Public)


#### class `UMetaSoundTemplateWidgetInterface`  
`class UMetaSoundTemplateWidgetInterface : public UInterface`  
_L24-27_
- reflection: `UINTERFACE(Blueprintable, MinimalAPI, DisplayName = "MetaSound Template Widget Interface")`
- inherits: `UInterface`

#### struct `FMetaSoundTemplateWidgetTabInfo`  
`struct FMetaSoundTemplateWidgetTabInfo`  
_L30-48_
- reflection: `USTRUCT(BlueprintType, MinimalAPI, DisplayName = "MetaSound Template Widget Tab Info")`
- L35 _public member_ `FName TabName;` — `UPROPERTY(BlueprintReadWrite, Category = TabInfo)`
- L38 _public member_ `FText TabDisplayName;` — `UPROPERTY(BlueprintReadWrite, Category = TabInfo)`
- L41 _public member_ `FName StyleName = "Me` — `UPROPERTY(BlueprintReadWrite, Category = TabInfo)`
- L44 _public member_ `FName TabIcon = "Me` — `UPROPERTY(BlueprintReadWrite, Category = TabInfo)`
- L47 _public member_ `FText ToolTip;` — `UPROPERTY(BlueprintReadWrite, Category = TabInfo)`

#### class `IMetaSoundTemplateWidgetInterface`  
`class IMetaSoundTemplateWidgetInterface`  
_L50-75_
- L58 _public prototype_ `void IsSupportedTemplate(UPARAM(DisplayName = "Template Name") FName ConfigName, const UMetaSoundBuilderBase* Builder, UPARAM(DisplayName = "Is Supported"` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MetaSound|Template", meta = (DisplayName = "Is Supported Template"))` — Returns whether or not the widget supports the given template. Called when initializing the MetaSound Editor to determine if an implemented template supports the given widget.
- L62 _public prototype_ `void OnAuditionStateChanged(UAudioComponent* AudioComponent, bool bIsAuditioning);` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaSound|Template", meta = (DisplayName = "On MetaSound Audition State Changed"))` — Called when the MetaSound starts and stops auditioning. Provides a reference to the audio component when auditioning starts, and returns nullptr when auditioning stops.
- L66 _public prototype_ `void OnBuilderSet(UMetaSoundBuilderBase* Builder);` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaSound|Template", meta = (DisplayName = "On MetaSound Builder Set"))` — Called when the builder is initialized (prior to PreConstruct).
- L70 _public prototype_ `void OnInitializingTab(FMetaSoundTemplateWidgetTabInfo& TabInfo);` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaSound|Template", meta = (DisplayName = "On Initializing Tab"))` — (Optional) Called when initializing a tab owning the given widget to allow implementation to provide basic tab display options and information.
- L74 _public prototype_ `void OnInitializingViewModel(TSubclassOf<UMetaSoundTemplateViewModelBase>& Class);` — `UFUNCTION(BlueprintImplementableEvent, Category = "MetaSound|Template", meta = (DisplayName = "On Initializing ViewModel"))` — (Optional) If ViewModel class provided, automatically initializes and sets ViewModel of the given class for the given widget.

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/TemplateViewModels/MetasoundTemplateViewModelBase.h` (Public)


#### class `UMetaSoundTemplateViewModelBase`  
`class UMetaSoundTemplateViewModelBase : public UMVVMViewModelBase`  
_L23-79_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract, DisplayName = "MetaSound Template ViewModel Base")`
- inherits: `UMVVMViewModelBase`
- L29 _public prototype_ `static void ConstructWidgetViewModel( UUserWidget* UserWidget, UMetaSoundBuilderBase& InBuilder, TConstStructView<FMetaSoundFrontendDocumentTemplate> Config, TSubclassOf<UMetaSoundTemplateViewModelBase> VMClass);` — Constructs a view model
- L35 _public prototype_ `virtual bool IsSupportedTemplate(const UScriptStruct& InStruct) const;`
- L39 _protected function_ `template <typename TemplateType> const TemplateType* GetConstTemplate() const`
- L51 _protected prototype_ `virtual void Reload();` — Enables responding to the builder reloading or the model view requiring a full resynchronization of configuration properties to view (i.e. when user transactions are applied that require a full resync of the view such as undo, redo, etc.)
- L54 _protected member_ `TObjectPtr<UMetaSoundBuilderBase> Builder;` — `UPROPERTY(Transient)`
- L57 _private prototype_ `void Initialize(UMetaSoundBuilderBase* InBuilder);`
- L78 _private member_ `TSharedPtr<FBuilderListener> BuilderListener;`

#### class `UMetaSoundTemplateViewModelBase::FBuilderListener`  
`class FBuilderListener : public Metasound::Frontend::IDocumentBuilderTransactionListener`  
_L59-77_
- inherits: `Metasound::Frontend::IDocumentBuilderTransactionListener`
- L61 _private member_ `TWeakObjectPtr<UMetaSoundTemplateViewModelBase> Parent;`
- L64 _public prototype_ `FBuilderListener() = default;`
- L65 _public function_ `FBuilderListener(UMetaSoundTemplateViewModelBase* InParent) : Parent(InParent)`
- L70 _public prototype_ `virtual ~FBuilderListener() = default;`
- L73 _private prototype_ `virtual void OnBuilderReloaded(Metasound::Frontend::FDocumentModifyDelegates& OutDelegates) override;`
- L74 _private prototype_ `void OnTemplateChanged(const Metasound::Frontend::FDocumentTemplateChangedArgs& Args);`
- L76 _private member_ `FDelegateHandle TemplateChangeDelegateHandle;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API METASOUNDEDITOR_API`

### `Plugins/Runtime/Metasound/Source/MetasoundEditor/Public/TemplateViewModels/RandomizerConfigurationViewModel.h` (Public)


#### class `UMetaSoundRandomizerViewModel`  
`class UMetaSoundRandomizerViewModel : public UMetaSoundTemplateViewModelBase`  
_L19-70_
- reflection: `UCLASS(MinimalAPI, DisplayName = "MetaSound Randomizer ViewModel")`
- inherits: `UMetaSoundTemplateViewModelBase`
- L24 _public prototype_ `bool GetIsOneShot() const;`
- L25 _public prototype_ `FVector2f GetPitch() const;`
- L27 _public prototype_ `const TArray<TObjectPtr<USoundWave>>& GetSounds() const;`
- L30 _public prototype_ `float GetPitchMin() const;` — `UFUNCTION(BlueprintPure, FieldNotify, Category = "MetaSound|Randomizer")`
- L33 _public prototype_ `float GetPitchMax() const;` — `UFUNCTION(BlueprintPure, FieldNotify, Category = "MetaSound|Randomizer")`
- L36 _public prototype_ `void SetNumSounds(int32 NumSounds);` — `UFUNCTION(BlueprintCallable, Category = "MetaSound|Randomizer")`
- L39 _public prototype_ `void SetPitchMin(float PitchMin);` — `UFUNCTION(BlueprintCallable, Category = "MetaSound|Randomizer")`
- L42 _public prototype_ `void SetPitchMax(float PitchMax);` — `UFUNCTION(BlueprintCallable, Category = "MetaSound|Randomizer")`
- L44 _public prototype_ `void SetIsOneShot(bool bInIsOneShot);`
- L45 _public prototype_ `void SetPitch(const FVector2f& InPitch);`
- L47 _public prototype_ `void SetSounds(TArray<TObjectPtr<USoundWave>> InSounds);`
- L49 _public prototype_ `virtual bool IsSupportedTemplate(const UScriptStruct& InStruct) const override;`
- L50 _public prototype_ `virtual void Reload() override;`
- L53 _private prototype_ `void OnPropertyChanged(const FPropertyChangedEvent& InEvent);`
- L55 _private member_ `FDelegateHandle PropertyChangedHandle;`
- L59 _private member_ `bool bIsOneShot = false;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "GetIsOneShot", Setter = "SetIsOneShot", Category = "MetaSound|Randomizer", meta = (AllowPrivateAccess))` — If randomizer is one shot (looping if false).
- L65 _private member_ `TArray<TObjectPtr<USoundWave>> Sounds;` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "GetSounds", Setter = "SetSounds", Category = "MetaSound|Randomizer", meta = ( AllowPrivateAccess, DisallowedClasses = "/Script/MetasoundEngine.MetaSoundSource, /Script/Engine.SoundSourceBus" ))`
- L69 _private member_ `FVector2f Pitch { 0.f, 0.f };` — `UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "GetPitch", Setter = "SetPitch", Category = "MetaSound|Randomizer", meta = (AllowPrivateAccess))` — Sound's pitch range in semitones.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDEDITOR_API`
