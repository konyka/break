# Plugins / MaterialAnalyzer

- module root: `Plugins/Editor/MaterialAnalyzer/Source`
- headers: 4; symbols: 207
- symbol kinds: class=7, function=40, member=94, prototype=48, struct=11, typedef=7
- PrivateDependencyModuleNames: AssetManagerEditor
- PublicDependencyModuleNames: Core, CoreUObject, DesktopPlatform, EditorFramework, Engine, InputCore, PropertyEditor, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicIncludePathModuleNames: WorkspaceMenuStructure

### `Plugins/Editor/MaterialAnalyzer/Source/MaterialAnalyzerModule.h` (Other)
_(no declarations extracted)_

### `Plugins/Editor/MaterialAnalyzer/Source/Private/AnalyzedMaterialNode.h` (Private)


#### struct `FBasePropertyOverrideNode`  
`struct FBasePropertyOverrideNode`  
_L7-26_
- L10 _public function_ `FBasePropertyOverrideNode(FName InParameterName, FName InParameterID, float InParameterValue, bool bInOverride, const FText& InHighlightText = FText::GetEmpty()) : ParameterName(InParameterName), ParameterID(InParameterID), ParameterValue(InParameterValue), bOverride(bInOverride), HighlightText(InHighlightText)`
- L19 _public member_ `FName ParameterName;`
- L20 _public member_ `FName ParameterID;`
- L21 _public member_ `float ParameterValue;`
- L22 _public member_ `bool bOverride;`
- L23 _public member_ `FText HighlightText;`
- L25 _public member_ `TArray<TSharedRef<FBasePropertyOverrideNode>>* Children;`

#### struct `FStaticMaterialLayerParameterNode`  
`struct FStaticMaterialLayerParameterNode`  
_L28-43_
- L31 _public function_ `FStaticMaterialLayerParameterNode(FName InParameterName, FString InParameterValue, bool bInOverride, const FText& InHighlightText = FText::GetEmpty()): ParameterName(InParameterName), ParameterValue(InParameterValue), bOverride(bInOverride), HighlightText(InHighlightText)`
- L39 _public member_ `FName ParameterName;`
- L40 _public member_ `FString ParameterValue;`
- L41 _public member_ `bool bOverride;`
- L42 _public member_ `FText HighlightText;`

#### struct `FStaticSwitchParameterNode`  
`struct FStaticSwitchParameterNode`  
_L45-62_
- L48 _public function_ `FStaticSwitchParameterNode(FName InParameterName, bool InParameterValue, bool bInOverride, const FText& InHighlightText = FText::GetEmpty()) : ParameterName(InParameterName), ParameterValue(InParameterValue), bOverride(bInOverride), HighlightText(InHighlightText)`
- L56 _public member_ `FName ParameterName;`
- L57 _public member_ `bool ParameterValue;`
- L58 _public member_ `bool bOverride;`
- L59 _public member_ `FText HighlightText;`
- L61 _public member_ `TArray<TSharedRef<FStaticSwitchParameterNode>>* Children;`

#### struct `FStaticComponentMaskParameterNode`  
`struct FStaticComponentMaskParameterNode`  
_L64-85_
- L67 _public function_ `FStaticComponentMaskParameterNode(FName InParameterName, bool InR, bool InG, bool InB, bool InA, bool bInOverride, const FText& InHighlightText = FText::GetEmpty()) : ParameterName(InParameterName), R(InR), G(InG), B(InB), A(InA), bOverride(bInOverride), HighlightText(InHighlightText)`
- L78 _public member_ `FName ParameterName;`
- L79 _public member_ `bool R;`
- L80 _public member_ `bool G;`
- L81 _public member_ `bool B;`
- L82 _public member_ `bool A;`
- L83 _public member_ `bool bOverride;`
- L84 _public member_ `FText HighlightText;`

#### struct `FAnalyzedMaterialNode`  
`struct FAnalyzedMaterialNode`  
_L99-228_
- L105 _public function_ `FAnalyzedMaterialNodeRef* AddChildNode(FAnalyzedMaterialNodeRef InChildNode)` — Add the given node to our list of children for this material (this node will keep a strong reference to the instance)
- L114 _public function_ `TArray<FAnalyzedMaterialNodeRef>& GetChildNodes()` — @return The node entries for the material's children
- L119 _public function_ `TArray<FAnalyzedMaterialNodeRef>* GetChildNodesPtr()`
- L124 _public function_ `int32 ActualNumberOfChildren() const`
- L129 _public function_ `int32 TotalNumberOfChildren() const`
- L141 _public function_ `FBasePropertyOverrideNodeRef FindBasePropertyOverride(FName ParameterName)`
- L148 _public function_ `FStaticMaterialLayerParameterNodeRef FindMaterialLayerParameter(FName ParameterName)`
- L155 _public function_ `FStaticSwitchParameterNodeRef FindStaticSwitchParameter(FName ParameterName)`
- L162 _public function_ `FStaticComponentMaskParameterNodeRef FindStaticComponentMaskParameter(FName ParameterName)`
- L169 _public function_ `bool HasAnyFilteredParameters(const FString& ParameterFilter) const`
- L216 _public member_ `FString Path;`
- L217 _public member_ `FSoftObjectPath ObjectPath;`
- L218 _public member_ `FAnalyzedMaterialNodePtr Parent;`
- L219 _public member_ `FAssetData AssetData;`
- L221 _public member_ `TArray<FBasePropertyOverrideNodeRef> BasePropertyOverrides;`
- L222 _public member_ `TArray<FStaticMaterialLayerParameterNodeRef> MaterialLayerParameters;`
- L223 _public member_ `TArray<FStaticSwitchParameterNodeRef> StaticSwitchParameters;`
- L224 _public member_ `TArray<FStaticComponentMaskParameterNodeRef> StaticComponentMaskParameters;`
- L227 _protected member_ `TArray<FAnalyzedMaterialNodeRef> ChildNodes;`

#### Free symbols / members of external scopes

- L87 _typedef_ `typedef TSharedRef<FBasePropertyOverrideNode, ESPMode::ThreadSafe> FBasePropertyOverrideNodeRef;`
- L89 _typedef_ `typedef TSharedRef<FStaticMaterialLayerParameterNode, ESPMode::ThreadSafe> FStaticMaterialLayerParameterNodeRef;`
- L91 _typedef_ `typedef TSharedRef<FStaticSwitchParameterNode, ESPMode::ThreadSafe> FStaticSwitchParameterNodeRef;`
- L93 _typedef_ `typedef TSharedRef<FStaticComponentMaskParameterNode, ESPMode::ThreadSafe> FStaticComponentMaskParameterNodeRef;`
- L95 _typedef_ `typedef TSharedRef<struct FAnalyzedMaterialNode, ESPMode::ThreadSafe> FAnalyzedMaterialNodeRef;`
- L97 _typedef_ `typedef TSharedPtr<struct FAnalyzedMaterialNode, ESPMode::ThreadSafe> FAnalyzedMaterialNodePtr;`
- L143 _function_ `FBasePropertyOverrideNodeRef* BasePropertyOverride = BasePropertyOverrides.FindByPredicate([&](const FBasePropertyOverrideNodeRef& Entry) { return Entry->ParameterName == ParameterName; });` (scope `FAnalyzedMaterialNode::FindBasePropertyOverride`)
- L150 _function_ `FStaticMaterialLayerParameterNodeRef* MaterialLayerParameter = MaterialLayerParameters.FindByPredicate([&](const FStaticMaterialLayerParameterNodeRef& Entry) { return Entry->ParameterName == ParameterName; });` (scope `FAnalyzedMaterialNode::FindMaterialLayerParameter`)
- L157 _function_ `FStaticSwitchParameterNodeRef* StaticSwitchParameter = StaticSwitchParameters.FindByPredicate([&](const FStaticSwitchParameterNodeRef& Entry) { return Entry->ParameterName == ParameterName; });` (scope `FAnalyzedMaterialNode::FindStaticSwitchParameter`)
- L164 _function_ `FStaticComponentMaskParameterNodeRef* StaticComponentMaskParameter = StaticComponentMaskParameters.FindByPredicate([&](const FStaticComponentMaskParameterNodeRef& Entry) { return Entry->ParameterName == ParameterName; });` (scope `FAnalyzedMaterialNode::FindStaticComponentMaskParameter`)
- L174 _function_ `` (scope `FAnalyzedMaterialNode::HasAnyFilteredParameters`)

### `Plugins/Editor/MaterialAnalyzer/Source/Private/SAnalyzedMaterialNodeWidgetItem.h` (Private)


#### class `SAnalyzedMaterialNodeWidgetItem`  
`class SAnalyzedMaterialNodeWidgetItem : public SMultiColumnTableRow<FAnalyzedMaterialNodeRef>`  
_L13-69_
- inherits: `SMultiColumnTableRow<FAnalyzedMaterialNodeRef>`
- L17 _public member_ `static FName NAME_MaterialName;`
- L18 _public member_ `static FName NAME_NumberOfChildren;`
- L19 _public member_ `static FName NAME_BasePropertyOverrides;`
- L20 _public member_ `static FName NAME_MaterialLayerParameters;`
- L21 _public member_ `static FName NAME_StaticSwitchParameters;`
- L22 _public member_ `static FName NAME_StaticComponentMaskParameters;`
- L24 _public function_ `SLATE_BEGIN_ARGS(SAnalyzedMaterialNodeWidgetItem) : _MaterialInfoToVisualize()`
- L40 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — Construct child widgets that comprise this widget. @param InArgs Declaration from which to construct this widget.
- L44 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — SMultiColumnTableRow overrides
- L46 _public prototype_ `FReply FindInContentBrowser();`
- L47 _public function_ `FText GetMaterialName() const`
- L52 _public function_ `FText GetNumberOfChildren() const`
- L59 _protected member_ `FAnalyzedMaterialNodePtr MaterialInfo;` — The info about the widget that we are visualizing.
- L61 _protected member_ `FText CachedMaterialName;`
- L62 _protected member_ `int TotalNumberOfChildren;`
- L63 _protected member_ `int NumberOfChildren;`
- L64 _protected member_ `FAssetData AssetData;`
- L65 _protected member_ `TArray<FBasePropertyOverrideNodeRef> BasePropertyOverrideNodes;`
- L66 _protected member_ `TArray<FStaticSwitchParameterNodeRef> StaticSwitchNodes;`
- L67 _protected member_ `TArray<FStaticComponentMaskParameterNodeRef> StaticComponentMaskNodes;`
- L68 _protected member_ `TArray<FStaticMaterialLayerParameterNodeRef> StaticMaterialLayerNodes;`

#### class `SStaticParameterWidget`  
`template<typename NodeType> class SStaticParameterWidget : public SCompoundWidget`  
_L72-113_
- inherits: `SCompoundWidget`
- L75 _private function_ `SLATE_BEGIN_ARGS(SStaticParameterWidget) : _StyleSet(&FCoreStyle::Get()), _StaticInfos()`
- L85 _public function_ `SStaticParameterWidget() : bIsExpanded(false)`
- L91 _public function_ `virtual TSharedRef<SWidget> CreateRowWidget(NodeType RowData)`
- L96 _public prototype_ `virtual FText GetBaseText() const;`
- L98 _public prototype_ `void Construct(const FArguments& InArgs);`
- L100 _public member_ `TSharedPtr<SVerticalBox> DataVerticalBox;`
- L101 _public member_ `TSharedPtr<SButton> ExpanderButton;`
- L103 _public member_ `TArray<NodeType> StaticNodes;`
- L105 _public prototype_ `FReply DoExpand();`
- L106 _public prototype_ `const FSlateBrush* GetExpanderImage() const;`
- L109 _public member_ `const ISlateStyle* StyleSet;` — The slate style to use
- L111 _public member_ `bool bIsExpanded;`

#### class `SBasePropertyOverrideWidget`  
`class SBasePropertyOverrideWidget : public SStaticParameterWidget<FBasePropertyOverrideNodeRef>`  
_L115-121_
- inherits: `SStaticParameterWidget<FBasePropertyOverrideNodeRef>`
- L118 _private prototype_ `virtual TSharedRef<SWidget> CreateRowWidget(FBasePropertyOverrideNodeRef RowData) override;`
- L120 _private prototype_ `virtual FText GetBaseText() const override;`

#### class `SStaticSwitchParameterWidget`  
`class SStaticSwitchParameterWidget : public SStaticParameterWidget<FStaticSwitchParameterNodeRef>`  
_L123-129_
- inherits: `SStaticParameterWidget<FStaticSwitchParameterNodeRef>`
- L126 _private prototype_ `virtual TSharedRef<SWidget> CreateRowWidget(FStaticSwitchParameterNodeRef RowData) override;`
- L128 _private prototype_ `virtual FText GetBaseText() const override;`

#### class `SStaticComponentMaskParameterWidget`  
`class SStaticComponentMaskParameterWidget : public SStaticParameterWidget<FStaticComponentMaskParameterNodeRef>`  
_L131-137_
- inherits: `SStaticParameterWidget<FStaticComponentMaskParameterNodeRef>`
- L134 _private prototype_ `virtual TSharedRef<SWidget> CreateRowWidget(FStaticComponentMaskParameterNodeRef RowData) override;`
- L136 _private prototype_ `virtual FText GetBaseText() const override;`

#### class `SStaticMaterialLayerParameterWidget`  
`class SStaticMaterialLayerParameterWidget : public SStaticParameterWidget<FStaticMaterialLayerParameterNodeRef>`  
_L139-145_
- inherits: `SStaticParameterWidget<FStaticMaterialLayerParameterNodeRef>`
- L143 _public prototype_ `virtual TSharedRef<SWidget> CreateRowWidget(FStaticMaterialLayerParameterNodeRef RowData) override;`
- L144 _public prototype_ `virtual FText GetBaseText() const override;`

### `Plugins/Editor/MaterialAnalyzer/Source/Private/SMaterialAnalyzer.h` (Private)


#### struct `FBuildBasicMaterialTreeAsyncTask`  
`struct FBuildBasicMaterialTreeAsyncTask : FNonAbandonableTask`  
_L20-49_
- inherits: `FNonAbandonableTask`
- L24 _public member_ `TArray<FAnalyzedMaterialNodeRef>& MaterialTreeRoot;` — File data loaded for the async read
- L26 _public member_ `TArray<FAssetData> AssetDataToAnalyze;`
- L28 _public member_ `FString ParameterFilter;`
- L31 _public function_ `FBuildBasicMaterialTreeAsyncTask(TArray<FAnalyzedMaterialNodeRef>& InMaterialTreeRoot, const TArray<FAssetData>& InAssetDataToAnalyze, const FString& InParameterFilter = TEXT("")) : MaterialTreeRoot(InMaterialTreeRoot) , AssetDataToAnalyze(InAssetDataToAnalyze) , ParameterFilter(InParameterFilter)` — Initializes the variables needed to load and verify the data
- L38 _public prototype_ `FAnalyzedMaterialNodePtr FindOrMakeBranchNode(FAnalyzedMaterialNodePtr ParentNode, const FAssetData* ChildData);`
- L43 _public prototype_ `void DoWork();` — Loads and hashes the file data. Empties the data if the hash check fails
- L45 _public function_ `FORCEINLINE TStatId GetStatId() const`

#### struct `FAnalyzeMaterialTreeAsyncTask`  
`struct FAnalyzeMaterialTreeAsyncTask`  
_L51-104_
- L54 _public member_ `FAnalyzedMaterialNodeRef MaterialTreeRoot;`
- L55 _public member_ `const TArray<FAssetData>& AssetDataToAnalyze;`
- L57 _public member_ `TArray<FAnalyzedMaterialNodeRef> MaterialQueue;`
- L59 _public member_ `int32 CurrentMaterialQueueIndex;`
- L61 _public member_ `FAnalyzedMaterialNodeRef CurrentMaterialNode;`
- L62 _public member_ `UMaterialInterface* CurrentMaterialInterface;`
- L64 _public member_ `TArray<FMaterialParameterInfo> BasePropertyOverrideInfo;`
- L66 _public member_ `TArray<FMaterialParameterInfo> StaticSwitchParameterInfo;`
- L67 _public member_ `TArray<FGuid> StaticSwitchGuids;`
- L69 _public member_ `TArray<FMaterialParameterInfo> StaticMaskParameterInfo;`
- L70 _public member_ `TArray<FGuid> StaticMaskGuids;`
- L72 _public member_ `FText ParameterFilter;`
- L75 _public function_ `FAnalyzeMaterialTreeAsyncTask(FAnalyzedMaterialNodeRef InMaterialTreeRoot, const TArray<FAssetData>& InAssetDataToAnalyze, const FText& InParameterFilter = FText::GetEmpty()): MaterialTreeRoot(InMaterialTreeRoot), AssetDataToAnalyze(InAssetDataToAnalyze), CurrentMaterialQueueIndex(0), CurrentMaterialNode(InMaterialTreeRoot), ParameterFilter(InParameterFilter)`
- L87 _public prototype_ `bool LoadNextMaterial();`
- L89 _public prototype_ `void DoWork();`
- L92 _public function_ `bool CanAbandon()` — need to make abandon-able eventually
- L96 _public function_ `void Abandon()`
- L100 _public function_ `FORCEINLINE TStatId GetStatId() const`

#### struct `FPermutationSuggestionData`  
`struct FPermutationSuggestionData`  
_L106-117_
- L108 _public member_ `FText Header;`
- L109 _public member_ `TArray<FString> Materials;`
- L111 _public function_ `FPermutationSuggestionData(const FText& InHeader, TArray<FString> InMaterials) : Header(InHeader) , Materials(InMaterials)`

#### struct `FPermutationSuggestionView`  
`struct FPermutationSuggestionView`  
_L119-123_
- L121 _public member_ `FText Header;`
- L122 _public member_ `TArray<TSharedPtr<FPermutationSuggestionView>> Children;`

#### struct `FAnalyzeForSuggestions`  
`struct FAnalyzeForSuggestions`  
_L125-146_
- L129 _public function_ `TMultiMap<int32, FPermutationSuggestionData> GetSuggestions()`
- L135 _protected function_ `FAnalyzeForSuggestions() :Suggestions(TMultiMap<int32, FPermutationSuggestionData>())`
- L140 _protected prototype_ `virtual ~FAnalyzeForSuggestions() = default;`
- L142 _protected member_ `TMultiMap<int32, FPermutationSuggestionData> Suggestions;`
- L144 _protected prototype_ `virtual void GatherSuggestions() = 0;`

#### struct `FAnalyzeForIdenticalPermutationsAsyncTask`  
`struct FAnalyzeForIdenticalPermutationsAsyncTask : FAnalyzeForSuggestions`  
_L148-186_
- inherits: `FAnalyzeForSuggestions`
- L151 _public prototype_ `virtual ~FAnalyzeForIdenticalPermutationsAsyncTask() = default;`
- L153 _public member_ `FAnalyzedMaterialNodeRef MaterialTreeRoot;`
- L155 _public member_ `TArray<FAnalyzedMaterialNodeRef> MaterialQueue;`
- L157 _public member_ `TMap<uint32, TArray<FSoftObjectPath>> MaterialPermutationHashToMaterialObjectPath;`
- L159 _public member_ `int32 AssetCount;`
- L161 _public function_ `FAnalyzeForIdenticalPermutationsAsyncTask(FAnalyzedMaterialNodeRef InMaterialTreeRoot) : MaterialTreeRoot(InMaterialTreeRoot)`
- L168 _public prototype_ `bool CreateMaterialPermutationHashForNode(const FAnalyzedMaterialNodeRef& MaterialNode, uint32& OutHash);`
- L169 _public prototype_ `void DoWork();`
- L172 _public function_ `bool CanAbandon()` — need to make abandon-able eventually
- L176 _public function_ `void Abandon()`
- L180 _public prototype_ `virtual void GatherSuggestions() override;`
- L182 _public function_ `FORCEINLINE TStatId GetStatId() const`

#### class `SMaterialAnalyzer`  
`class SMaterialAnalyzer : public SCompoundWidget`  
_L188-291_
- inherits: `SCompoundWidget`
- L191 _public function_ `SLATE_BEGIN_ARGS(SMaterialAnalyzer)`
- L195 _public typedef_ `typedef STreeView<FAnalyzedMaterialNodeRef> SAnalyzedMaterialTree;`
- L198 _public prototype_ `SMaterialAnalyzer();`
- L199 _public prototype_ `virtual ~SMaterialAnalyzer();`
- L209 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);` — Constructs the application. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed. @param InStyleSet The style set to use.
- L211 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L213 _public prototype_ `TSharedRef< ITableRow > OnGenerateSuggestionRow(TSharedPtr<FPermutationSuggestionView> Item, const TSharedRef< STableViewBase >& OwnerTable);`
- L214 _public prototype_ `EVisibility ShouldShowAdvancedRecommendations(TSharedPtr<FPermutationSuggestionView> Item) const;`
- L215 _public prototype_ `void OnAssetAdded(const FAssetData& InAssetData);`
- L219 _protected member_ `TArray<FAssetData> AssetDataArray;`
- L220 _protected member_ `TArray<FAssetData> RecentlyAddedAssetData;`
- L221 _protected member_ `TArray<FAssetData> RecentlyRemovedAssetData;`
- L223 _protected member_ `TSharedPtr<SAnalyzedMaterialTree> MaterialTree;`
- L224 _protected member_ `TSharedPtr<STextBlock> StatusBox;`
- L225 _protected member_ `TSharedPtr<SScrollBox> SuggestionsBox;`
- L226 _protected member_ `TSharedPtr<SThrobber> StatusThrobber;`
- L228 _protected member_ `TArray<FAnalyzedMaterialNodeRef> AllMaterialTreeRoots;`
- L229 _protected member_ `TArray<FAnalyzedMaterialNodeRef> MaterialTreeRoot;`
- L232 _protected member_ `TSharedPtr<STreeView<TSharedPtr<FPermutationSuggestionView>>> SuggestionsTree;` — The tree view widget
- L233 _protected member_ `TArray<TSharedPtr<FPermutationSuggestionView>> SuggestionDataArray;`
- L235 _protected member_ `FAsyncTask<FBuildBasicMaterialTreeAsyncTask>* BuildBaseMaterialTreeTask;`
- L236 _protected member_ `FAsyncTask<FAnalyzeMaterialTreeAsyncTask>* AnalyzeTreeTask;`
- L237 _protected member_ `FAsyncTask<FAnalyzeForIdenticalPermutationsAsyncTask>* AnalyzeForIdenticalPermutationsTask;`
- L239 _protected member_ `FAssetData CurrentlySelectedAsset;`
- L241 _protected member_ `bool bWaitingForAssetRegistryLoad;`
- L243 _protected prototype_ `void OnAssetSelected(const FAssetData& AssetData);`
- L244 _protected prototype_ `void OnParameterFilterChanged(const FText& Filter, const ETextCommit::Type InTextAction);`
- L246 _protected prototype_ `FReply OnExportAnalyzedMaterialToCSV();`
- L248 _protected prototype_ `void BuildBasicMaterialTree();`
- L250 _protected prototype_ `int32 GetTotalNumberOfMaterialNodes();`
- L252 _protected prototype_ `void SetupAssetRegistryCallbacks();`
- L254 _protected prototype_ `void OnGetSuggestionChildren(TSharedPtr<FPermutationSuggestionView> InParent, TArray< TSharedPtr<FPermutationSuggestionView> >& OutChildren);`
- L255 _protected prototype_ `FReply CreateLocalSuggestionCollectionClicked(TSharedPtr<FPermutationSuggestionView> InSuggestion);`
- L256 _protected prototype_ `void CreateLocalSuggestionCollection(ICollectionContainer& InCollectionContainer, const FPermutationSuggestionView& InSuggestion);`
- L257 _protected prototype_ `void StartAsyncWork(const FText& WorkText);`
- L259 _protected prototype_ `void AsyncWorkFinished(const FText& CompleteText);`
- L261 _protected prototype_ `FString GetCurrentAssetPath() const;`
- L266 _private prototype_ `TSharedRef<ITableRow> HandleReflectorTreeGenerateRow(FAnalyzedMaterialNodeRef InReflectorNode, const TSharedRef<STableViewBase>& OwnerTable);` — Callback for generating a row in the reflector tree view.
- L269 _private prototype_ `void HandleReflectorTreeGetChildren(FAnalyzedMaterialNodeRef InReflectorNode, TArray<FAnalyzedMaterialNodeRef>& OutChildren);` — Callback for getting the child items of the given reflector tree node.
- L277 _private prototype_ `void HandleReflectorTreeRecursiveExpansion(FAnalyzedMaterialNodeRef InTreeNode, bool bIsItemExpanded);` — Called to recursively expand/collapse the children of the given item @param InTreeNode		The node that was expanded or collapsed @param bIsItemExpanded	True if the item is expanded, false if it is collapsed
- L279 _private prototype_ `void UpdateViewForSelectedAsset();`
- L281 _private function_ `bool IsMaterialSelectionAllowed() const`
- L288 _private member_ `bool bIsAsyncWorkInProgress = false;`
- L289 _private member_ `FText ParameterFilter;`
- L290 _private member_ `bool bHasParameterFilterChanged = false;`
