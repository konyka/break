# Plugins / PluginReferenceViewer

- module root: `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer`
- headers: 11; symbols: 258
- symbol kinds: class=10, delegate=2, enum=1, enumerator=7, function=17, macro=2, member=76, namespace=1, prototype=134, struct=8
- PrivateDependencyModuleNames: ApplicationCore, AssetManagerEditor, AssetRegistry, ContentBrowserData, EditorFramework, EditorWidgets, GameplayTags, GraphEditor, PluginBrowser, PluginUtils, Projects, ToolMenus, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Slate, SlateCore

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/EdGraphNode_PluginReference.h` (Private)


#### class `UEdGraphNode_PluginReference`  
`class UEdGraphNode_PluginReference : public UEdGraphNode`  
_L17-61_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- L21 _private prototype_ `FPluginIdentifier GetIdentifier() const;`
- L23 _private prototype_ `void SetupPluginReferenceNode(const FIntPoint& InNodeLoc, const FPluginIdentifier InPluginIdentifier, const TSharedPtr<const IPlugin>& InPlugin, bool bInAllowThumbnail, bool bInIsADuplicate);`
- L25 _private prototype_ `bool AllowsThumbnail() const;`
- L26 _private function_ `bool IsADuplicate() const`
- L28 _private prototype_ `TSharedPtr<const IPlugin> GetPlugin() const;`
- L31 _private prototype_ `UEdGraph_PluginReferenceViewer* GetPluginReferenceViewerGraph() const;` — Returns our owning graph
- L32 _private prototype_ `void AddReferencer(UEdGraphNode_PluginReference* ReferencerNode);`
- L35 _private prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode implementation
- L36 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L37 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L38 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L39 _private prototype_ `virtual FText GetTooltipText() const override;`
- L40 _private function_ `virtual bool ShowPaletteIconOnNode() const override`
- L43 _private prototype_ `UEdGraphPin* GetDependencyPin();`
- L44 _private prototype_ `UEdGraphPin* GetReferencerPin();`
- L47 _private member_ `FPluginIdentifier PluginIdentifier;`
- L48 _private member_ `FText NodeTitle;`
- L50 _private member_ `bool bAllowThumbnail;`
- L51 _private member_ `bool bIsEnginePlugin;`
- L52 _private member_ `bool bIsADuplicate;`
- L54 _private member_ `TSharedPtr<const IPlugin> CachedPlugin;`
- L55 _private member_ `FSlateIcon AssetBrush;`
- L57 _private member_ `UEdGraphPin* DependencyPin;`
- L58 _private member_ `UEdGraphPin* ReferencerPin;`

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/EdGraph_PluginReferenceViewer.h` (Private)


#### struct `FPluginIdentifier`  
`struct FPluginIdentifier`  
_L16-54_
- L18 _public member_ `FName Name;`
- L20 _public function_ `FPluginIdentifier() : Name(NAME_None)`
- L25 _public function_ `FPluginIdentifier(FName InName) : Name(InName)`
- L40 _public function_ `bool IsValid() const`
- L45 _public function_ `FString ToString() const`
- L50 _public function_ `static FPluginIdentifier FromString(const FString& String)`

#### struct `FAssetStats`  
`struct FAssetStats`  
_L57-64_
- L59 _public function_ `FAssetStats() : References(0)`
- L63 _public member_ `uint32 References;`

#### struct `FPluginStats`  
`struct FPluginStats`  
_L66-73_
- L68 _public member_ `uint64 Size;`
- L69 _public member_ `uint64 SizeWithDependencies;`
- L71 _public member_ `uint32 Dependencies;`
- L72 _public member_ `uint32 Referencers;`

#### struct `FPluginDependsNode`  
`struct FPluginDependsNode`  
_L76-88_
- L78 _public function_ `explicit FPluginDependsNode(const FPluginIdentifier& InIdentifier, bool InMissing) : Identifier(InIdentifier) , bMissing(InMissing)`
- L84 _public member_ `FPluginIdentifier Identifier;`
- L85 _public member_ `TArray<FPluginDependsNode*> Dependencies;` — Raw pointer to another node in CachedDependsNodes, same lifetime
- L86 _public member_ `TArray<FPluginDependsNode*> Referencers;` — Raw pointer to another node in CachedDependsNodes, same lifetime
- L87 _public member_ `bool bMissing = false;`

#### struct `FPluginReferenceNodeInfo`  
`struct FPluginReferenceNodeInfo`  
_L90-109_
- L92 _public member_ `FPluginIdentifier Identifier;`
- L94 _public member_ `TArray<TPair<FPluginIdentifier, EPluginReferencePinCategory>> Children;`
- L96 _public member_ `TArray<FPluginIdentifier> Parents;`
- L98 _public member_ `bool bReferencers;`
- L100 _public prototype_ `FPluginReferenceNodeInfo(const FPluginIdentifier& InIdentifier, bool bInReferencers);`
- L102 _public prototype_ `bool IsFirstParent(const FPluginIdentifier& InParentId) const;`
- L105 _public prototype_ `int32 ProvisionSize(const FPluginIdentifier& InParentId) const;` — The Provision Size, or vertical spacing required for layout, for a given parent.
- L108 _public member_ `int32 ChildProvisionSize;` — how many nodes worth of children require vertical spacing

#### class `UEdGraph_PluginReferenceViewer`  
`class UEdGraph_PluginReferenceViewer : public UEdGraph`  
_L112-204_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- L117 _public prototype_ `void CachePluginDependencies(const TArray<TSharedRef<IPlugin>>& Plugins);`
- L120 _public prototype_ `void SetGraphRoot(const TArray<FPluginIdentifier>& GraphRootIdentifiers, const FIntPoint& GraphRootOrigin = FIntPoint(ForceInitToZero));` — Set reference viewer to focus on these assets
- L122 _public prototype_ `const TArray<FPluginIdentifier>& GetCurrentGraphRootIdentifiers() const;`
- L130 _public prototype_ `void FindAssetReferencesAcrossPlugins(const FPluginIdentifier& From, const FPluginIdentifier& To, TArray<FAssetIdentifier>& OutAssetIdentifiers);` — Finds all plugin assets that have dependencies on another plugins assets @param From the plugin whose assets we want to find references from @param To the plugin whose assets we want to find dependencies to
- L133 _public prototype_ `void GetPluginAssets(const FPluginIdentifier& Plugin, TArray<FAssetIdentifier>& OutAssetIdentifiers);` — Finds all plugin assets
- L135 _public prototype_ `const FPluginStats& GetPluginStats(const FPluginIdentifier& Plugin);`
- L137 _public prototype_ `void LoadAdvancedPluginInfo();`
- L139 _public prototype_ `UEdGraphNode_PluginReference* ConstructNodes(const TArray<FPluginIdentifier>& GraphRootIdentifiers, const FIntPoint& GraphRootOrigin);`
- L141 _public prototype_ `UEdGraphNode_PluginReference* RecursivelyCreateNodes(bool bInReferencers, const FPluginIdentifier& InPluginId, const FIntPoint& InNodeLoc, const FPluginIdentifier& InParentId, UEdGraphNode_PluginReference* InParentNode, TMap<FPluginIdentifier, FPluginReferenceNodeInfo>& InNodeInfos, int32 InCurrentDepth, int32 InMaxDepth, bool bIsRoot = false);`
- L143 _public prototype_ `void RecursivelyPopulateNodeInfos(bool bInReferencers, const TArray<FPluginIdentifier>& Identifiers, TMap<FPluginIdentifier, FPluginReferenceNodeInfo>& InNodeInfos, int32 InCurrentDepth, int32 InMaxDepth);`
- L145 _public prototype_ `void RecursivelyFilterNodeInfos(const FPluginIdentifier& InPluginId, TMap<FPluginIdentifier, FPluginReferenceNodeInfo>& InNodeInfos, int32 InCurrentDepth, int32 InMaxDepth);`
- L147 _public prototype_ `void GetSortedLinks(const TArray<FPluginIdentifier>& Identifiers, bool bReferencers, TMap<FPluginIdentifier, EPluginReferencePinCategory>& OutLinks) const;`
- L150 _public prototype_ `UEdGraphNode_PluginReference* RebuildGraph();` — Force the graph to rebuild
- L152 _public prototype_ `UEdGraphNode_PluginReference* CreatePluginReferenceNode();`
- L153 _public prototype_ `void RemoveAllNodes();`
- L156 _public prototype_ `bool IsDependencyNode(const FPluginIdentifier& PluginIdentifier) const;` — Returns true if the plugin is a dependency of the graph root plugin.
- L159 _public prototype_ `bool IsReferencerNode(const FPluginIdentifier& PluginIdentifier) const;` — Returns true if the plugin is a referencer of the graph root plugin.
- L176 _private prototype_ `void SetPluginReferenceViewer(TSharedPtr<SPluginReferenceViewer> InViewer);`
- L178 _private prototype_ `void GetPluginDependencies(const FPluginIdentifier& PluginIdentifier, TArray<FPluginDependency>& OutDependencies) const;`
- L179 _private prototype_ `void GetPluginReferencers(const FPluginIdentifier& PluginIdentifier, TArray<FPluginDependency>& OutReferencers) const;`
- L181 _private prototype_ `UEdGraphNode_PluginReference* RefilterGraph();`
- L185 _private member_ `TWeakPtr<SPluginReferenceViewer> PluginReferenceViewer;` — Editor for this pool
- L187 _private member_ `TArray<FPluginIdentifier> CurrentGraphRootIdentifiers;`
- L188 _private member_ `FIntPoint CurrentGraphRootOrigin;`
- L191 _private member_ `TMap<FPluginIdentifier, TUniquePtr<FPluginDependsNode>> CachedDependsNodes;` — Mapping of plugins which were seen when traversing the dependency graph of active plugins, whether or not they exist in the plugin manager
- L193 _private member_ `TMap<FPluginIdentifier, const TSharedPtr<IPlugin>> PluginMap;` — Mapping of plugins which actually exist - may have fewer keys than CachedDependsNodes
- L194 _private member_ `TMap<FPluginIdentifier, FPluginStats> StatsMap;`
- L197 _private member_ `TMap<FPluginIdentifier, FPluginReferenceNodeInfo> ReferencerNodeInfos;` — Current set of referencers of the graph root plugin(s) to be displayed, expanded to configured depth
- L199 _private member_ `TMap<FPluginIdentifier, FPluginReferenceNodeInfo> DependencyNodeInfos;` — Current set of dependencies of the graph root plugin(s) to be displayed, expanded to configured depth
- L203 _private member_ `bool bAdvancedInfoLoaded = false;`

#### struct `UEdGraph_PluginReferenceViewer::FPluginDependency`  
`struct FPluginDependency`  
_L162-174_
- L164 _public member_ `FPluginIdentifier Identifier;`
- L165 _public member_ `bool bIsEnabled;`
- L166 _public member_ `bool bIsOptional;`
- L168 _public function_ `FPluginDependency(FPluginIdentifier InIdentifier, bool bInIsEnabled, bool bInIsOptional) : Identifier(InIdentifier) , bIsEnabled(bInIsEnabled) , bIsOptional(bInIsOptional)`

#### Free symbols / members of external scopes

- L30 _function_ `friend inline bool operator==(const FPluginIdentifier& A, const FPluginIdentifier& B)`
- L35 _function_ `friend inline uint32 GetTypeHash(const FPluginIdentifier& Key)`

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/HistoryManager.h` (Private)


#### struct `FPluginReferenceViewerHistoryData`  
`struct FPluginReferenceViewerHistoryData`  
_L12-19_
- desc: The history data object, storing all important history data
- L15 _public member_ `FText HistoryDesc;` — History Description
- L18 _public member_ `TArray<FPluginIdentifier> Identifiers;` — The list of package names to serve as the root

#### class `FPluginReferenceViewerHistoryManager`  
`class FPluginReferenceViewerHistoryManager`  
_L28-89_
- desc: The class responsible for managing all content browser history
- L32 _public prototype_ `FPluginReferenceViewerHistoryManager();` — Constructor
- L35 _public prototype_ `void SetOnApplyHistoryData(const FOnApplyHistoryData& InOnApplyHistoryData);` — Set the delegate for applying history data
- L38 _public prototype_ `void SetOnUpdateHistoryData(const FOnUpdateHistoryData& InOnUpdateHistoryData);` — Set the delegate for updating history data
- L41 _public prototype_ `bool GoBack();` — Goes back one history snapshot and returns the history data at that snapshot
- L44 _public prototype_ `bool GoForward();` — Goes forward one history snapshot and returns the history data at that snapshot
- L47 _public prototype_ `void AddHistoryData();` — Stores new history data.  Called when creating a history snapshot
- L50 _public prototype_ `void UpdateHistoryData();` — Triggers an update for the current history data. This is typically done right before changing the history.
- L53 _public prototype_ `bool CanGoForward() const;` — Determines if a user can go forward in history
- L56 _public prototype_ `bool CanGoBack() const;` — Determines if a user can go back in history
- L59 _public prototype_ `FText GetBackDesc() const;` — Gets the description of the previous history entry
- L62 _public prototype_ `FText GetForwardDesc() const;` — Gets the description of the next history entry
- L66 _private prototype_ `void ApplyCurrentHistoryData();` — Notifies the owner to update to the state described by the current history data
- L69 _private prototype_ `void UpdateCurrentHistoryData();` — Notifies the owner to update the current history data
- L72 _private prototype_ `void ExecuteJumpToHistory(int32 HistoryIndex);` — Handler for when a history item is chosen in the GetAvailableHistroyMenuItems list
- L76 _private member_ `FOnApplyHistoryData OnApplyHistoryData;` — The delegate for when history data should be applied
- L79 _private member_ `FOnUpdateHistoryData OnUpdateHistoryData;` — The delegate for when history data should be updated
- L82 _private member_ `TArray<FPluginReferenceViewerHistoryData> HistoryData;` — A list of history snapshots
- L85 _private member_ `int32 CurrentHistoryIndex;` — The current history index the user is at (changes when the user goes back,forward, or history snapshots are taken)
- L88 _private member_ `int32 MaxHistoryEntries;` — Max number of history items that can be stored.  Once the max is reached, the oldest history item is removed

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnApplyHistoryData, const FPluginReferenceViewerHistoryData& );` — The delegate for when history data should be applied
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FOnApplyHistoryData, const FPluginReferenceViewerHistoryData& );` — The delegate for when history data should be applied
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpdateHistoryData, FPluginReferenceViewerHistoryData& );` — The delegate for when history data should be updated
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FOnUpdateHistoryData, FPluginReferenceViewerHistoryData& );` — The delegate for when history data should be updated

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/PluginReferencePinCategory.h` (Private)


#### enum `EPluginReferencePinCategory`  
`enum class EPluginReferencePinCategory`  
_L7-17_
- L9 _public enumerator_ `LinkEndPassive = 0`
- L10 _public enumerator_ `LinkEndActive = 1`
- L11 _public enumerator_ `LinkEndMask = LinkEndActive`
- L13 _public enumerator_ `LinkTypeNone = 0`
- L14 _public enumerator_ `LinkTypeOptional = 2`
- L15 _public enumerator_ `LinkTypeEnabled = 4`
- L16 _public enumerator_ `LinkTypeMask = LinkTypeEnabled | LinkTypeOptional`

#### Free symbols / members of external scopes

- L18 _prototype_ `ENUM_CLASS_FLAGS(EPluginReferencePinCategory);`
- L20 _namespace_ `namespace PluginReferencePinUtil`
- L22 _prototype_ `EPluginReferencePinCategory ParseDependencyPinCategory(FName PinCategory);` (scope `PluginReferencePinUtil`)
- L23 _prototype_ `FName GetName(EPluginReferencePinCategory Category);` (scope `PluginReferencePinUtil`)
- L24 _prototype_ `FLinearColor GetColor(EPluginReferencePinCategory Category);` (scope `PluginReferencePinUtil`)

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/PluginReferenceViewerCommands.h` (Private)


#### class `FPluginReferenceViewerCommands`  
`class FPluginReferenceViewerCommands : public TCommands<FPluginReferenceViewerCommands>`  
_L8-27_
- inherits: `TCommands<FPluginReferenceViewerCommands>`
- desc: Actions that can be invoked in the reference viewer
- L11 _public prototype_ `FPluginReferenceViewerCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L17 _public member_ `TSharedPtr<FUICommandInfo> CompactMode;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> ShowDuplicates;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> ShowEnginePlugins;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ShowOptionalPlugins;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> OpenPluginProperties;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> OpenAssetDiskSizeViewer;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ShowInContentBrowser;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFit;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ReCenterGraph;`

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/PluginReferenceViewerSchema.h` (Private)


#### class `UPluginReferenceViewerSchema`  
`class UPluginReferenceViewerSchema : public UEdGraphSchema`  
_L16-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L22 _public prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UEdGraphSchema interface
- L23 _public function_ `virtual FName GetParentContextMenuName() const override`
- L24 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L25 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L26 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L27 _public prototype_ `virtual FPinConnectionResponse MovePinLinks(UEdGraphPin& MoveFromPin, UEdGraphPin& MoveToPin, bool bIsIntermediateMove = false, bool bNotifyLinkedNodes = false) const override;`
- L28 _public prototype_ `virtual FPinConnectionResponse CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy = false) const override;`
- L29 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L30 _public prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L31 _public prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L35 _private prototype_ `static TSharedPtr<IPlugin> GetDroppedPlugin(const TArray<FAssetData>& Assets);`

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/PluginReferenceViewerStyle.h` (Private)


#### class `FPluginReferenceViewerStyle`  
`class FPluginReferenceViewerStyle : public FSlateStyleSet`  
_L7-20_
- inherits: `FSlateStyleSet`
- L11 _public member_ `static FName StyleName;`
- L14 _public prototype_ `static FPluginReferenceViewerStyle& Get();` — Access the singleton instance for this style set
- L18 _private prototype_ `FPluginReferenceViewerStyle();`
- L19 _private prototype_ `~FPluginReferenceViewerStyle();`

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/SPluginReferenceNode.h` (Private)


#### class `SPluginReferenceNode`  
`class SPluginReferenceNode : public SGraphNode`  
_L14-34_
- inherits: `SGraphNode`
- L17 _public function_ `SLATE_BEGIN_ARGS(SPluginReferenceNode)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphNode_PluginReference* InNode);`
- L25 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode implementation
- L26 _public function_ `virtual bool IsNodeEditable() const override`
- L30 _private member_ `TSharedPtr<class FAssetThumbnail> AssetThumbnail;`
- L33 _private member_ `TSharedPtr<FSlateDynamicImageBrush> PluginIconDynamicImageBrush;` — Brush resource for the image that is dynamically loaded

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Private/SPluginReferenceViewer.h` (Private)


#### class `SPluginReferenceViewer`  
`class SPluginReferenceViewer : public SCompoundWidget`  
_L22-146_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SPluginReferenceViewer)`
- L28 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ParentTab) SLATE_END_ARGS() ~SPluginReferenceViewer();`
- L35 _public prototype_ `void Construct(const FArguments& InArgs);`
- L37 _public prototype_ `void SetGraphRootIdentifiers(const TArray<FPluginIdentifier>& GraphRootIdentifiers);`
- L39 _public prototype_ `int32 GetSearchReferencerDepthCount() const;`
- L40 _public prototype_ `int32 GetSearchDependencyDepthCount() const;`
- L41 _public prototype_ `bool IsCompactModeChecked() const;`
- L42 _public prototype_ `bool IsShowDuplicatesChecked() const;`
- L43 _public prototype_ `bool IsShowEnginePluginsChecked() const;`
- L44 _public prototype_ `bool IsShowOptionalPluginsChecked() const;`
- L47 _private prototype_ `void OnOpenPluginProperties();`
- L48 _private prototype_ `void OnOpenAssetDiskSizeViewer();`
- L49 _private prototype_ `void OnShowPluginInContentBrowser();`
- L50 _private prototype_ `bool HasAtLeastOneRealNodeSelected();`
- L52 _private prototype_ `void OpenPluginProperties(const FString& PluginName);`
- L54 _private prototype_ `TSharedRef<SWidget> MakeToolBar();`
- L55 _private prototype_ `TSharedRef<SWidget> GetShowMenuContent();`
- L57 _private prototype_ `void RebuildGraph();`
- L58 _private prototype_ `void ZoomToFit();`
- L59 _private prototype_ `void ReCenterGraph();`
- L60 _private prototype_ `void ReCenterGraphOnNodes(const TSet<UObject*>& Nodes);`
- L61 _private prototype_ `void RegisterActions();`
- L64 _private prototype_ `void OnNodeDoubleClicked(UEdGraphNode* Node);` — Called when a node is double clicked
- L67 _private prototype_ `bool IsBackEnabled() const;` — True if the user may use the history back button
- L70 _private prototype_ `bool IsForwardEnabled() const;` — True if the user may use the history forward button
- L73 _private prototype_ `void BackClicked();` — Handler for clicking the history back button
- L76 _private prototype_ `void ForwardClicked();` — Handler for clicking the history forward button
- L79 _private prototype_ `void RefreshClicked();` — Refresh the current view
- L82 _private prototype_ `void GraphNavigateHistoryBack();` — Handler for when the graph panel tells us to go back in history (like using the mouse thumb button)
- L85 _private prototype_ `void GraphNavigateHistoryForward();` — Handler for when the graph panel tells us to go forward in history (like using the mouse thumb button)
- L88 _private prototype_ `FText GetHistoryBackTooltip() const;` — Gets the tool tip text for the history back button
- L91 _private prototype_ `FText GetHistoryForwardTooltip() const;` — Gets the tool tip text for the history forward button
- L94 _private prototype_ `FText GetPluginStatsText() const;` — Gets text for advanced info plugin stats. Formatted output of plugin content size, reference counts, etc.
- L96 _private prototype_ `FText GetAddressBarText() const;`
- L97 _private prototype_ `void OnAddressBarTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L98 _private prototype_ `void OnAddressBarTextChanged(const FText& NewText);`
- L100 _private prototype_ `void OnCompactModeChanged();`
- L101 _private prototype_ `void OnShowDuplicatesChanged();`
- L102 _private prototype_ `void OnShowEnginePluginsChanged();`
- L103 _private prototype_ `void OnShowOptionalPluginsChanged();`
- L104 _private prototype_ `void OnApplyHistoryData(const FPluginReferenceViewerHistoryData& History);`
- L105 _private prototype_ `void OnUpdateHistoryData(FPluginReferenceViewerHistoryData& HistoryData) const;`
- L117 _private prototype_ `void OnTabSpawned(const FName& TabIdentifier, const TSharedRef<SDockTab>& SpawnedTab);`
- L118 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ReferenceGraph(const FSpawnTabArgs& Args);`
- L119 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PluginStats(const FSpawnTabArgs& Args) const;`
- L123 _private member_ `FPluginReferenceViewerHistoryManager HistoryManager;` — The manager that keeps track of history data for this browser
- L125 _private member_ `TSharedPtr<SGraphEditor> GraphEditorPtr;`
- L126 _private member_ `TSharedPtr<FUICommandList> PluginReferenceViewerActions;`
- L127 _private member_ `TSharedPtr<SWidget> ReferencerCountBox;`
- L128 _private member_ `TSharedPtr<SWidget> DependencyCountBox;`
- L130 _private member_ `UEdGraph_PluginReferenceViewer* GraphObj;`
- L131 _private member_ `FPluginReferenceViewerSettings Settings;`
- L134 _private member_ `FText TemporaryPathBeingEdited;` — The temporary copy of the path text when it is actively being edited.
- L136 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L137 _private member_ `TMap<FName, TWeakPtr<SDockTab>> SpawnedTabs;`
- L139 _private member_ `TSharedPtr<FUICommandInfo> ShowEnginePlugins;`
- L142 _private member_ `bool bNeedsGraphRebuild;` — Used to delay graph rebuilding during spinbox slider interaction
- L145 _private member_ `bool bShowAdvancedInfo;` — Enables loading of plugin stats, such as reference counts, plugin content size, and dependant content size.

#### struct `SPluginReferenceViewer::FPluginReferenceViewerSettings`  
`struct FPluginReferenceViewerSettings`  
_L107-115_
- L109 _public member_ `int32 MaxSearchReferencersDepth = 1;`
- L110 _public member_ `int32 MaxSearchDependencyDepth = 1;`
- L111 _public member_ `bool bIsCompactMode = false;`
- L112 _public member_ `bool bShowDuplicates = true;`
- L113 _public member_ `bool bShowEnginePlugins = true;`
- L114 _public member_ `bool bShowOptionalPlugins = true;`

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Public/PluginReferenceViewerModule.h` (Public)


#### class `FPluginReferenceViewerModule`  
`class FPluginReferenceViewerModule : public IModuleInterface`  
_L14-37_
- inherits: `IModuleInterface`
- L17 _public function_ `static inline FPluginReferenceViewerModule& Get()`
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `void OpenPluginReferenceViewerUI(const TSharedRef<class IPlugin>& Plugin);`
- L30 _private prototype_ `void OnLaunchReferenceViewerFromPluginBrowser(TSharedPtr<IPlugin> Plugin);`
- L32 _private member_ `static const FName PluginReferenceViewerTabName;`
- L34 _private prototype_ `TSharedRef<SDockTab> SpawnPluginReferenceViewerTab(const FSpawnTabArgs& Args);`
- L36 _private member_ `TSharedPtr<FPluginReferenceViewerGraphPanelNodeFactory> PluginReferenceViewerGraphPanelNodeFactory;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PLUGINREFERENCEVIEWER_API`

### `Plugins/Experimental/PluginReferenceViewer/Source/PluginReferenceViewer/Public/PluginReferenceViewerUtils.h` (Public)


#### class `FPluginReferenceViewerUtils`  
`class FPluginReferenceViewerUtils`  
_L12-48_
- L16 _public prototype_ `static TMap<FAssetIdentifier, TArray<FAssetIdentifier>> GetAssetDependencyMap(const TSharedRef<IPlugin>& InPlugin);` — Helper that returns array of Asset dependencies for a given plugin
- L19 _public prototype_ `static TArray<FAssetIdentifier> GetAssetDependencies(const TSharedRef<IPlugin>& InPlugin);` — Helper that returns array of Asset dependencies for a given plugin
- L22 _public prototype_ `static TMap<FString, TArray<FAssetIdentifier>> SplitByPlugins(const TSharedRef<IPlugin>& InOwningPlugin, const TArray<FAssetIdentifier>& InPluginDependencies);` — Helper that will split plugin dependencies by their owning plugin
- L25 _public prototype_ `static void SplitByReferenceType(const TArray<FAssetIdentifier>& InAssetIdentifiers, TArray<FAssetIdentifier>& OutAssetReferences, TArray<FAssetIdentifier>& OutScriptReferences, TArray<FAssetIdentifier>& OutNameReferences);` — Helper that will split an array of assets by their reference types
- L28 _public prototype_ `static void ExportPlugins(const TArray<FString>& InPlugins, const FString& InFilename);` — Exports the number of references from each plugin to their plugin dependencies. References include; assets, scripts and named references
- L31 _public prototype_ `static void ExportAssetReference(const FString& InPlugin, const FString& InReference, const FString& InFilename);` — Exports to a .csv file the list of asset references that exist between the plugin and one of it's plugin dependencies by asset
- L34 _public prototype_ `static void ExportReference(const FString& InPlugin, const FString& InReference, const FString& InFilename);` — Exports to a .csv file the list of asset references that exist between the plugin and one of it's plugin dependencies
- L37 _public prototype_ `static TArray<TSharedRef<IPlugin>> FindGameplayTagSourcePlugins(FName TagName);` — Returns the list of plugins where the supplied gameplay tag is declated
- L43 _public prototype_ `static bool TracePluginChain(const FString& StartingPlugin, const FString& EndingPlugin, FString& OutPathToEndPlugin);` — Traces the path from one plugin to the ending plugin if one exists. Returns true if a path exists.
- L46 _private prototype_ `FPluginReferenceViewerUtils() = delete;`
- L47 _private prototype_ `FPluginReferenceViewerUtils(const FPluginReferenceViewerUtils&) = delete;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PLUGINREFERENCEVIEWER_API`
