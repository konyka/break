# Plugins / AssetManagerEditor

- module root: `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor`
- headers: 23; symbols: 1206
- symbol kinds: class=35, delegate=11, enum=8, enumerator=34, function=156, macro=4, member=355, namespace=4, prototype=575, struct=13, typedef=11
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, CollectionManager, ContentBrowser, ContentBrowserAssetDataSource, ContentBrowserData, CookMetadata, EditorFramework, EditorWidgets, GraphEditor, InputCore, Json, KismetCompiler, LevelEditor, Projects, PropertyEditor, SandboxFile, Slate, SlateCore, SourceControl, SourceControlWindows, StatusBar, ToolMenus, ToolWidgets, TraceInsightsCore, TreeMap, UncontrolledChangelists, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: StatsViewer
- PublicDependencyModuleNames: Core, CoreUObject, Engine, TargetPlatform

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/AssetManagerEditorCommands.h` (Private)


#### class `FAssetManagerEditorCommands`  
`class FAssetManagerEditorCommands : public TCommands<FAssetManagerEditorCommands>`  
_L8-149_
- inherits: `TCommands<FAssetManagerEditorCommands>`
- desc: Actions that can be invoked in the reference viewer
- L11 _public prototype_ `FAssetManagerEditorCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L18 _public member_ `TSharedPtr<FUICommandInfo> CopyAssetReferences;` — Copy asset references to the clipboard
- L21 _public member_ `TSharedPtr<FUICommandInfo> CopyAssetPaths;` — Copy asset file paths to the clipboard
- L24 _public member_ `TSharedPtr<FUICommandInfo> ViewReferences;` — Shows the reference viewer for the selected assets
- L27 _public member_ `TSharedPtr<FUICommandInfo> ViewSizeMap;` — Shows a size map for the selected assets
- L30 _public member_ `TSharedPtr<FUICommandInfo> ViewShaderCookStatistics;` — Shows shader cook statistics
- L33 _public member_ `TSharedPtr<FUICommandInfo> ViewAssetAudit;` — Adds assets to asset audit window
- L36 _public member_ `TSharedPtr<FUICommandInfo> OpenSelectedInAssetEditor;` — Opens the selected asset in the asset editor
- L39 _public member_ `TSharedPtr<FUICommandInfo> ReCenterGraph;` — Re-constructs the graph with the selected asset as the center
- L42 _public member_ `TSharedPtr<FUICommandInfo> IncreaseReferencerSearchDepth;` — Increase Referencer Search Depth
- L45 _public member_ `TSharedPtr<FUICommandInfo> DecreaseReferencerSearchDepth;` — Decrease Referencer Search Depth
- L48 _public member_ `TSharedPtr<FUICommandInfo> SetReferencerSearchDepth;` — Set the Referencer Serach Depth
- L51 _public member_ `TSharedPtr<FUICommandInfo> IncreaseDependencySearchDepth;` — Increase Dependency Search Depth
- L54 _public member_ `TSharedPtr<FUICommandInfo> DecreaseDependencySearchDepth;` — Decrease Dependency Search Depth
- L57 _public member_ `TSharedPtr<FUICommandInfo> SetDependencySearchDepth;` — Set the Dependency Serach Depth
- L60 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBreadth;` — Increase Search Breadth
- L63 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBreadth;` — Decrease Search Breadth
- L66 _public member_ `TSharedPtr<FUICommandInfo> SetBreadth;` — Set the Breadth LImit
- L69 _public member_ `TSharedPtr<FUICommandInfo> ShowSoftReferences;` — Toggles visiblity of Soft References
- L72 _public member_ `TSharedPtr<FUICommandInfo> ShowHardReferences;` — Toggles visiblity of Hard References
- L75 _public member_ `TSharedPtr<FUICommandInfo> EditorOnlyReferenceFilterTypeGame;` — Sets which level of filter type between Game and EditorOnly is visible
- L76 _public member_ `TSharedPtr<FUICommandInfo> EditorOnlyReferenceFilterTypePropagation;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> EditorOnlyReferenceFilterTypeEditorOnly;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> ShowManagementReferences;` — Toggles visiblity of Management References (i.e. PrimaryAssetIDs)
- L83 _public member_ `TSharedPtr<FUICommandInfo> ShowNameReferences;` — Toggles visiblity of Name References (i.e. Gameplay Tags and Data Table Row Handles)
- L86 _public member_ `TSharedPtr<FUICommandInfo> ShowCodePackages;` — Toggles visiblity of Native Packages
- L89 _public member_ `TSharedPtr<FUICommandInfo> ShowDuplicates;` — Toggles visiblity of Duplicate References
- L92 _public member_ `TSharedPtr<FUICommandInfo> CompactMode;` — Toggles Compact Mode
- L95 _public member_ `TSharedPtr<FUICommandInfo> ShowExternalReferencers;` — Toggles Show External Referencers
- L98 _public member_ `TSharedPtr<FUICommandInfo> ShowCommentPath;` — Toggles Path Comment
- L101 _public member_ `TSharedPtr<FUICommandInfo> Filters;` — Toggles FilterBar Filters On/Off
- L104 _public member_ `TSharedPtr<FUICommandInfo> AutoFilters;` — Toggles if Asset Type Filters are Auto Populated & Updated
- L107 _public member_ `TSharedPtr<FUICommandInfo> CopyPaths;` — Copies the selected Asset Paths to the Clipboard
- L110 _public member_ `TSharedPtr<FUICommandInfo> FilterSearch;` — Toggles whether search results are filtered or just selected
- L113 _public member_ `TSharedPtr<FUICommandInfo> FindPath;` — Toggles the Find Path Mode
- L116 _public member_ `TSharedPtr<FUICommandInfo> CopyReferencedObjects;` — Copies the list of objects that the selected asset references
- L119 _public member_ `TSharedPtr<FUICommandInfo> CopyReferencingObjects;` — Copies the list of objects that reference the selected asset
- L122 _public member_ `TSharedPtr<FUICommandInfo> ShowReferencedObjects;` — Shows a list of objects that the selected asset references
- L125 _public member_ `TSharedPtr<FUICommandInfo> ShowReferencingObjects;` — Shows a list of objects that reference the selected asset
- L128 _public member_ `TSharedPtr<FUICommandInfo> ShowReferenceTree;` — Shows a reference tree for the selected asset
- L131 _public member_ `TSharedPtr<FUICommandInfo> AuditReferencedObjects;` — Adds all referenced objects to asset audit window
- L134 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFit;` — Zoom in to fit the selected objects in the window
- L137 _public member_ `TSharedPtr<FUICommandInfo> ResolveReferencingProperties;` — Display the list of properties which are referencing the selected node from its referencing node(s)
- L140 _public member_ `TSharedPtr<FUICommandInfo> Find;` — Start finding objects
- L143 _public member_ `TSharedPtr<FUICommandInfo> MakeLocalCollectionWithReferencers;` — Creates a new collection with the list of assets that this asset references, user selects which ECollectionShareType to use.
- L144 _public member_ `TSharedPtr<FUICommandInfo> MakePrivateCollectionWithReferencers;`
- L145 _public member_ `TSharedPtr<FUICommandInfo> MakeSharedCollectionWithReferencers;`
- L146 _public member_ `TSharedPtr<FUICommandInfo> MakeLocalCollectionWithDependencies;`
- L147 _public member_ `TSharedPtr<FUICommandInfo> MakePrivateCollectionWithDependencies;`
- L148 _public member_ `TSharedPtr<FUICommandInfo> MakeSharedCollectionWithDependencies;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/AssetSourceControlContextMenu.h` (Private)


#### class `FAssetSourceControlContextMenu`  
`class FAssetSourceControlContextMenu`  
_L12-22_
- desc: Display source control options in the given menu section based on what's selected in the menu context
- L15 _public prototype_ `~FAssetSourceControlContextMenu();`
- L18 _public prototype_ `void MakeContextMenu(FToolMenuSection& InSection);` — Makes the context menu widget
- L21 _private member_ `TSharedPtr<FAssetSourceControlContextMenuState> InnerState;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/PrimaryAssetIdCustomization.h` (Private)


#### class `FPrimaryAssetIdCustomization`  
`class FPrimaryAssetIdCustomization : public IPropertyTypeCustomization`  
_L16-65_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for a primary asset id, shows an asset picker with filters
- L19 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L26 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L29 _private prototype_ `void OnIdSelected(FPrimaryAssetId AssetId);`
- L30 _private prototype_ `void OnBrowseTo();`
- L31 _private prototype_ `void OnClear();`
- L32 _private prototype_ `void OnUseSelected();`
- L33 _private prototype_ `FText GetAssetNameText() const;`
- L34 _private prototype_ `FText GetDisplayText() const;`
- L35 _private prototype_ `FText GetFormattedAssetDisplayText() const;`
- L36 _private prototype_ `FPrimaryAssetId GetCurrentPrimaryAssetId() const;`
- L37 _private prototype_ `void UpdateThumbnail();`
- L38 _private prototype_ `void OnOpenAssetEditor();`
- L41 _private prototype_ `const FSlateBrush* GetThumbnailBorder() const;` — Gets the border brush to show around the thumbnail, changes when the user hovers on it.
- L46 _private prototype_ `FReply OnAssetThumbnailDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);` — Handle double clicking the asset thumbnail. this 'Edits' the displayed asset
- L49 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct property being customized
- L52 _private member_ `TArray<FPrimaryAssetType> AllowedTypes;` — Specified type
- L55 _private member_ `TArray<const UClass*> AllowedClasses;` — Classes which can be selected with this PrimaryAssetId
- L58 _private member_ `TArray<const UClass*> DisallowedClasses;` — Classes which cannot be selected with this PrimaryAssetId
- L61 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;` — Thumbnail resource
- L64 _private member_ `TSharedPtr<SBorder> ThumbnailBorder;` — The border surrounding the thumbnail image.

#### class `SPrimaryAssetIdGraphPin`  
`class SPrimaryAssetIdGraphPin : public SGraphPin`  
_L68-90_
- inherits: `SGraphPin`
- desc: Graph pin version of UI
- L71 _public function_ `SLATE_BEGIN_ARGS(SPrimaryAssetIdGraphPin)`
- L72 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L77 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L82 _private prototype_ `void OnIdSelected(FPrimaryAssetId AssetId);`
- L83 _private prototype_ `FText GetDisplayText() const;`
- L84 _private prototype_ `FSlateColor OnGetWidgetForeground() const;`
- L85 _private prototype_ `FSlateColor OnGetWidgetBackground() const;`
- L86 _private prototype_ `FReply OnBrowseTo();`
- L87 _private prototype_ `FReply OnUseSelected();`
- L89 _private member_ `FPrimaryAssetId CurrentId;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/PrimaryAssetTypeCustomization.h` (Private)


#### class `FPrimaryAssetTypeCustomization`  
`class FPrimaryAssetTypeCustomization : public IPropertyTypeCustomization`  
_L12-32_
- inherits: `IPropertyTypeCustomization`
- desc: Primary asset type, reads the list from AssetManager
- L15 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L27 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct property being customized
- L30 _private prototype_ `void GenerateComboBoxStrings(TArray< TSharedPtr<FString> >& OutComboBoxStrings, TArray<TSharedPtr<class SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems);` — Creates the string list

#### class `SPrimaryAssetTypeGraphPin`  
`class SPrimaryAssetTypeGraphPin : public SGraphPin`  
_L35-53_
- inherits: `SGraphPin`
- desc: Graph pin version of UI
- L38 _public function_ `SLATE_BEGIN_ARGS(SPrimaryAssetTypeGraphPin)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L44 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L49 _private prototype_ `void OnTypeSelected(FPrimaryAssetType AssetType);`
- L50 _private prototype_ `FText GetDisplayText() const;`
- L52 _private member_ `FPrimaryAssetType CurrentType;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/ReferenceViewer/HistoryManager.h` (Private)


#### struct `FReferenceViewerHistoryData`  
`struct FReferenceViewerHistoryData`  
_L12-16_
- desc: The history data object, storing all important history data
- L15 _public member_ `TArray<FAssetIdentifier> Identifiers;` — The list of package names to serve as the root

#### class `FReferenceViewerHistoryManager`  
`class FReferenceViewerHistoryManager`  
_L25-86_
- desc: The class responsible for managing all content browser history
- L29 _public prototype_ `FReferenceViewerHistoryManager();` — Constructor
- L32 _public prototype_ `void SetOnApplyHistoryData(const FOnApplyHistoryData& InOnApplyHistoryData);` — Set the delegate for applying history data
- L35 _public prototype_ `void SetOnUpdateHistoryData(const FOnUpdateHistoryData& InOnUpdateHistoryData);` — Set the delegate for updating history data
- L38 _public prototype_ `bool GoBack();` — Goes back one history snapshot and returns the history data at that snapshot
- L41 _public prototype_ `bool GoForward();` — Goes forward one history snapshot and returns the history data at that snapshot
- L44 _public prototype_ `void AddHistoryData();` — Stores new history data.  Called when creating a history snapshot
- L47 _public prototype_ `void UpdateHistoryData();` — Triggers an update for the current history data. This is typically done right before changing the history.
- L50 _public prototype_ `bool CanGoForward() const;` — Determines if a user can go forward in history
- L53 _public prototype_ `bool CanGoBack() const;` — Determines if a user can go back in history
- L56 _public prototype_ `const FReferenceViewerHistoryData* GetBackHistoryData() const;` — Gets the description of the previous history entry
- L59 _public prototype_ `const FReferenceViewerHistoryData* GetForwardHistoryData() const;` — Gets the description of the next history entry
- L63 _private prototype_ `void ApplyCurrentHistoryData();` — Notifies the owner to update to the state described by the current history data
- L66 _private prototype_ `void UpdateCurrentHistoryData();` — Notifies the owner to update the current history data
- L69 _private prototype_ `void ExecuteJumpToHistory(int32 HistoryIndex);` — Handler for when a history item is chosen in the GetAvailableHistroyMenuItems list
- L73 _private member_ `FOnApplyHistoryData OnApplyHistoryData;` — The delegate for when history data should be applied
- L76 _private member_ `FOnUpdateHistoryData OnUpdateHistoryData;` — The delegate for when history data should be updated
- L79 _private member_ `TArray<FReferenceViewerHistoryData> HistoryData;` — A list of history snapshots
- L82 _private member_ `int32 CurrentHistoryIndex;` — The current history index the user is at (changes when the user goes back,forward, or history snapshots are taken)
- L85 _private member_ `int32 MaxHistoryEntries;` — Max number of history items that can be stored.  Once the max is reached, the oldest history item is removed

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnApplyHistoryData, const FReferenceViewerHistoryData& );` — The delegate for when history data should be applied
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnApplyHistoryData, const FReferenceViewerHistoryData& );` — The delegate for when history data should be applied
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpdateHistoryData, FReferenceViewerHistoryData& );` — The delegate for when history data should be updated
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FOnUpdateHistoryData, FReferenceViewerHistoryData& );` — The delegate for when history data should be updated

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/ReferenceViewer/ReferenceViewerFilters.h` (Private)


#### class `FReferenceViewerFilter`  
`class FReferenceViewerFilter : public FFilterBase<FReferenceNodeInfo&>`  
_L11-43_
- inherits: `FFilterBase<FReferenceNodeInfo&>`
- L14 _public function_ `FReferenceViewerFilter(TSharedPtr<FFilterCategory> InCategory) : FFilterBase<FReferenceNodeInfo&>(MoveTemp(InCategory))`
- L20 _public prototype_ `virtual FLinearColor GetColor() const override;` — Returns the color this filter button will be when displayed as a button
- L23 _public prototype_ `virtual FName GetIconName() const override;` — Returns the name of the icon to use in menu entries
- L26 _public function_ `virtual bool IsInverseFilter() const override` — Returns true if the filter should be in the list when disabled and not in the list when enabled
- L32 _public function_ `virtual void ActiveStateChanged(bool bActive) override` — Notification that the filter became active or inactive
- L35 _public function_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override` — Called when the right-click context menu is being built for this filter
- L38 _public function_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override` — Called when the state of a particular Content Browser is being saved to INI
- L41 _public function_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override` — Called when the state of a particular Content Browser is being loaded from INI

#### class `FReferenceViewerFilter_ShowCheckedOut`  
`class FReferenceViewerFilter_ShowCheckedOut final : public FReferenceViewerFilter , public TSharedFromThis<FReferenceViewerFilter_ShowCheckedOut>`  
_L48-75_
- inherits: `FReferenceViewerFilter,TSharedFromThis<FReferenceViewerFilter_ShowCheckedOut>`
- desc: A Filter to show nodes checked out by revision control
- L53 _public prototype_ `FReferenceViewerFilter_ShowCheckedOut(const TSharedPtr<FFilterCategory>& InCategory);`
- L56 _public prototype_ `virtual FString GetName() const override;` — Returns the system name for this filter
- L59 _public prototype_ `virtual FText GetDisplayName() const override;` — Returns the human-readable name for this filter
- L62 _public prototype_ `virtual FText GetToolTipText() const override;` — Returns the tooltip for this filter, shown in the filters menu
- L65 _public prototype_ `virtual void ActiveStateChanged(bool bInActive) override;` — Notification that the filter became active or inactive
- L67 _public prototype_ `virtual bool PassesFilter(FReferenceNodeInfo& InItem) const override;`
- L71 _private prototype_ `void RequestStatus();` — Request the source control status for this filter
- L74 _private prototype_ `void SourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);` — Callback when source control operation has completed

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/ReferenceViewer/ReferenceViewerStyle.h` (Private)


#### class `FReferenceViewerStyle`  
`class FReferenceViewerStyle : public FSlateStyleSet`  
_L16-29_
- inherits: `FSlateStyleSet`
- desc: The Reference Viewer is being used as a sandbox for testing out ui changes to graphs. This style is setup to facilitate testing new styles for graphs and should be deleted once the main graph style is updated, which currently resides in StarshipStyle (the Editor Style). This style inherits from the EditorStyle (StarshipStyle) and therefore is just overwriting styles on the editor style.  No style names should have to be replaced when removing this style. However, someone will have to update the references from FReferenceViewerStyle::Get() to be FAppStyle::Get().
- L20 _public member_ `static FName StyleName;`
- L23 _public prototype_ `static FReferenceViewerStyle& Get();` — Access the singleton instance for this style set
- L27 _private prototype_ `FReferenceViewerStyle();`
- L28 _private prototype_ `~FReferenceViewerStyle();`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/ReferenceViewer/SReferenceNode.h` (Private)


#### class `SReferenceNode`  
`class SReferenceNode : public SGraphNode`  
_L13-37_
- inherits: `SGraphNode`
- L16 _public function_ `SLATE_BEGIN_ARGS( SReferenceNode )`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, UEdGraphNode_Reference* InNode );`
- L24 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode implementation
- L25 _public function_ `virtual bool IsNodeEditable() const override`
- L31 _private prototype_ `EVisibility GetCollapsedVisibility() const;` — Returns visibility setting for elements which should be hidden if node is collapsed
- L33 _private member_ `TSharedPtr<class FAssetThumbnail> AssetThumbnail;`
- L36 _private member_ `bool bIsCollapsed = false;` — Whether the current node is collapsed (representing more than one node) or not

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/ReferenceViewer/SReferenceViewer.h` (Private)


#### class `SReferenceViewer`  
`class SReferenceViewer : public SCompoundWidget`  
_L31-322_
- inherits: `SCompoundWidget`
- L34 _public function_ `SLATE_BEGIN_ARGS( SReferenceViewer )`
- L35 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ParentTab) SLATE_END_ARGS() ~SReferenceViewer();`
- L41 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L49 _public prototype_ `void SetGraphRootIdentifiers(const TArray<FAssetIdentifier>& NewGraphRootIdentifiers, const FReferenceViewerParams& ReferenceViewerParams = FReferenceViewerParams());` — Sets a new root package name @param NewGraphRootIdentifiers	The root elements of the new graph to be generated @param ReferenceViewerParams		Different visualization settings, such as whether it should display the referencers or the dependencies of the NewGraphRootIdentifiers
- L52 _public function_ `TSharedPtr<SGraphEditor> GetGraphEditor() const` — Gets graph editor
- L55 _public prototype_ `void SetCurrentRegistrySource(const FAssetManagerEditorRegistrySource* RegistrySource);` — Called when the current registry source changes
- L58 _public function_ `virtual bool SupportsKeyboardFocus() const override` — SWidget interface
- L59 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L60 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L62 _public prototype_ `bool CanMakeCollectionWithReferencersOrDependencies(TSharedPtr<ICollectionContainer> CollectionContainer, ECollectionShareType::Type ShareType) const;`
- L63 _public prototype_ `void MakeCollectionWithReferencersOrDependencies(TSharedPtr<ICollectionContainer> CollectionContainer, ECollectionShareType::Type ShareType, bool bReferencers);`
- L65 _public function_ `FOnReferenceViewerSelectionChanged& OnReferenceViewerSelectionChanged()`
- L67 _public prototype_ `void GetSelectedNodeAssetData(TArray<FAssetData>& OutAssetData) const;`
- L71 _private prototype_ `void RebuildGraph();` — Call after a structural change is made that causes the graph to be recreated
- L74 _private prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — Called to create context menu when right-clicking on graph
- L77 _private prototype_ `void OnNodeDoubleClicked(class UEdGraphNode* Node);` — Called when a node is double clicked
- L80 _private prototype_ `bool IsBackEnabled() const;` — True if the user may use the history back button
- L83 _private prototype_ `bool IsForwardEnabled() const;` — True if the user may use the history forward button
- L86 _private prototype_ `void BackClicked();` — Handler for clicking the history back button
- L89 _private prototype_ `void ForwardClicked();` — Handler for clicking the history forward button
- L92 _private prototype_ `void RefreshClicked();` — Refresh the current view
- L95 _private prototype_ `void GraphNavigateHistoryBack();` — Handler for when the graph panel tells us to go back in history (like using the mouse thumb button)
- L98 _private prototype_ `void GraphNavigateHistoryForward();` — Handler for when the graph panel tells us to go forward in history (like using the mouse thumb button)
- L101 _private prototype_ `FText GetHistoryBackTooltip() const;` — Gets the tool tip text for the history back button
- L104 _private prototype_ `FText GetHistoryForwardTooltip() const;` — Gets the tool tip text for the history forward button
- L107 _private prototype_ `FText GetAddressBarText() const;` — Gets the text to be displayed in the address bar
- L110 _private prototype_ `FText GetIdentifierSummaryText(const TArray<FAssetIdentifier>& Identifiers) const;` — Gets the summary text to be displayed for multiple FAssetIdentifiers
- L113 _private prototype_ `FText GetIdentifierText(const FAssetIdentifier& Identifier) const;` — Gets the text to be displayed for a FAssetIdentifier
- L116 _private prototype_ `FText GetStatusText() const;` — Gets the text to be displayed for warning/status updates
- L119 _private prototype_ `FText GetCenteredStatusText() const;` — Gets the text to be displayed at the center of the graph
- L122 _private prototype_ `EVisibility GetCenteredStatusVisibility() const;` — Gets the visibility for the text which can be displayed at the center of the graph
- L125 _private prototype_ `void OnAddressBarTextChanged(const FText& NewText);` — Called when the path is being edited
- L128 _private prototype_ `void OnAddressBarTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);` — Sets the new path for the viewer
- L130 _private prototype_ `void OnApplyHistoryData(const FReferenceViewerHistoryData& History);`
- L132 _private prototype_ `void OnUpdateHistoryData(FReferenceViewerHistoryData& HistoryData) const;`
- L134 _private prototype_ `void OnUpdateFilterBar();`
- L136 _private prototype_ `void OnSearchDepthEnabledChanged( ECheckBoxState NewState );`
- L137 _private prototype_ `ECheckBoxState IsSearchDepthEnabledChecked() const;`
- L139 _private prototype_ `int32 GetSearchReferencerDepthCount() const;`
- L140 _private prototype_ `int32 GetSearchDependencyDepthCount() const;`
- L142 _private prototype_ `void OnSearchReferencerDepthCommitted(int32 NewValue);`
- L143 _private prototype_ `void OnSearchDependencyDepthCommitted(int32 NewValue);`
- L145 _private prototype_ `void OnEnableCollectionFilterChanged(ECheckBoxState NewState);`
- L146 _private prototype_ `ECheckBoxState IsEnableCollectionFilterChecked() const;`
- L147 _private prototype_ `void CollectionFilterAddMenuEntry(FMenuBuilder& MenuBuilder, const TSharedPtr<ICollectionContainer>& CollectionContainer, const FName& CollectionName);`
- L148 _private prototype_ `TSharedRef<SWidget> BuildCollectionFilterMenu();`
- L149 _private prototype_ `FText GetCollectionComboButtonText() const;`
- L151 _private prototype_ `void OnEnablePluginFilterChanged(ECheckBoxState NewState);`
- L152 _private prototype_ `ECheckBoxState IsEnablePluginFilterChecked() const;`
- L153 _private prototype_ `void PluginFilterAddMenuEntry(FMenuBuilder& MenuBuilder, const FName& PluginName, const FText& Label, const FText& ToolTip);`
- L154 _private prototype_ `TSharedRef<SWidget> BuildPluginFilterMenu();`
- L155 _private prototype_ `FText GetPluginComboButtonText() const;`
- L157 _private prototype_ `void OnShowSoftReferencesChanged();`
- L158 _private prototype_ `bool IsShowSoftReferencesChecked() const;`
- L159 _private prototype_ `void OnShowHardReferencesChanged();`
- L160 _private prototype_ `bool IsShowHardReferencesChecked() const;`
- L161 _private prototype_ `void OnEditorOnlyReferenceFilterTypeChanged(EEditorOnlyReferenceFilterType Value);`
- L162 _private prototype_ `EEditorOnlyReferenceFilterType GetEditorOnlyReferenceFilterType() const;`
- L164 _private prototype_ `void OnShowFilteredPackagesOnlyChanged();`
- L165 _private prototype_ `bool IsShowFilteredPackagesOnlyChecked() const;`
- L166 _private prototype_ `void UpdateIsPassingSearchFilterCallback();`
- L168 _private prototype_ `void OnCompactModeChanged();`
- L169 _private prototype_ `bool IsCompactModeChecked() const;`
- L171 _private prototype_ `void OnShowExternalReferencersChanged();`
- L172 _private prototype_ `bool IsShowExternalReferencersChecked() const;`
- L174 _private prototype_ `void OnShowDuplicatesChanged();`
- L175 _private prototype_ `bool IsShowDuplicatesChecked() const;`
- L177 _private prototype_ `bool GetManagementReferencesVisibility() const;`
- L178 _private prototype_ `void OnShowManagementReferencesChanged();`
- L179 _private prototype_ `bool IsShowManagementReferencesChecked() const;`
- L180 _private prototype_ `void OnShowSearchableNamesChanged();`
- L181 _private prototype_ `bool IsShowSearchableNamesChecked() const;`
- L182 _private prototype_ `void OnShowCodePackagesChanged();`
- L183 _private prototype_ `bool IsShowCodePackagesChecked() const;`
- L185 _private prototype_ `int32 GetSearchBreadthCount() const;`
- L186 _private prototype_ `void SetSearchBreadthCount(int32 InBreadthValue);`
- L187 _private prototype_ `void OnSearchBreadthChanged(int32 InBreadthValue);`
- L188 _private prototype_ `void OnSearchBreadthCommited(int32 InBreadthValue, ETextCommit::Type InCommitType);`
- L190 _private prototype_ `TSharedRef<SWidget> GetShowMenuContent();`
- L192 _private prototype_ `void RegisterActions();`
- L193 _private prototype_ `void ShowSelectionInContentBrowser();`
- L194 _private prototype_ `void OpenSelectedInAssetEditor();`
- L195 _private prototype_ `void ReCenterGraph();`
- L196 _private prototype_ `void CopyReferencedObjects();`
- L197 _private prototype_ `void CopyReferencingObjects();`
- L198 _private prototype_ `void ShowReferencedObjects();`
- L199 _private prototype_ `void ShowReferencingObjects();`
- L200 _private prototype_ `bool CanMakeCollectionWithReferencersOrDependencies(ECollectionShareType::Type ShareType) const;`
- L201 _private prototype_ `void MakeCollectionWithReferencersOrDependencies(ECollectionShareType::Type ShareType, bool bReferencers);`
- L202 _private prototype_ `void ShowReferenceTree();`
- L203 _private prototype_ `void ViewSizeMap();`
- L204 _private prototype_ `void ViewAssetAudit();`
- L205 _private prototype_ `void ZoomToFit();`
- L206 _private prototype_ `bool CanZoomToFit() const;`
- L207 _private prototype_ `void OnFind();`
- L208 _private prototype_ `void ResolveReferencingProperties() const;`
- L209 _private prototype_ `bool CanResolveReferencingProperties() const;`
- L212 _private prototype_ `TSharedRef<SWidget> GenerateFindPathAssetPickerMenu();` — Find Path
- L213 _private prototype_ `void OnFindPathAssetSelected( const FAssetData& AssetData );`
- L214 _private prototype_ `void OnFindPathAssetEnterPressed( const TArray<FAssetData>& AssetData );`
- L215 _private member_ `TSharedPtr<SComboButton> FindPathAssetPicker;`
- L216 _private member_ `FAssetIdentifier FindPathAssetId;`
- L219 _private prototype_ `void HandleOnSearchTextChanged(const FText& SearchText);` — Handlers for searching
- L220 _private prototype_ `void HandleOnSearchTextCommitted(const FText& SearchText, ETextCommit::Type CommitType);`
- L222 _private prototype_ `void ReCenterGraphOnNodes(const TSet<UObject*>& Nodes);`
- L230 _private prototype_ `FString GetObjectsList(EObjectsListType ObjectsListType) const;`
- L232 _private prototype_ `UObject* GetObjectFromSingleSelectedNode() const;`
- L233 _private prototype_ `void GetPackageNamesFromSelectedNodes(TSet<FName>& OutNames) const;`
- L234 _private prototype_ `bool HasExactlyOneNodeSelected() const;`
- L235 _private prototype_ `bool HasExactlyOnePackageNodeSelected() const;`
- L236 _private prototype_ `bool HasAtLeastOnePackageNodeSelected() const;`
- L237 _private prototype_ `bool HasAtLeastOneRealNodeSelected() const;`
- L239 _private prototype_ `void OnAssetRegistryChanged(const FAssetData& AssetData);`
- L240 _private prototype_ `void OnInitialAssetRegistrySearchComplete();`
- L241 _private prototype_ `void OnPluginEdited(IPlugin& InPlugin);`
- L243 _private prototype_ `EActiveTimerReturnType TriggerZoomToFit(double InCurrentTime, float InDeltaTime);`
- L246 _private prototype_ `TSharedRef<SWidget> MakeToolBar();`
- L250 _private member_ `FReferenceViewerHistoryManager HistoryManager;` — The manager that keeps track of history data for this browser
- L252 _private member_ `TSharedPtr<SGraphEditor> GraphEditorPtr;`
- L254 _private member_ `TSharedPtr<FUICommandList> ReferenceViewerActions;`
- L255 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L256 _private member_ `TSharedPtr<SWidget> ReferencerCountBox;`
- L257 _private member_ `TSharedPtr<SWidget> DependencyCountBox;`
- L258 _private member_ `TSharedPtr<SWidget> BreadthLimitBox;`
- L260 _private member_ `TSharedPtr< SReferenceViewerFilterBar > FilterWidget;`
- L262 _private member_ `UEdGraph_ReferenceViewer* GraphObj;`
- L264 _private member_ `UReferenceViewerSettings* Settings;`
- L267 _private member_ `FText TemporaryPathBeingEdited;` — The temporary copy of the path text when it is actively being edited.
- L270 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> CollectionsCombo;` — Combo box for collections filter options
- L273 _private member_ `TArray<TSharedPtr<FName>> CollectionsComboList;` — List of collection filter options
- L280 _private member_ `int32 FixAndHideSearchDepthLimit;` — Whether to visually show to the user the option of "Search Depth Limit" or hide it and fix it to a default value: - If 0 or negative, it will show to the user the option of "Search Depth Limit". - If >0, it will hide that option and fix the Depth value to this value.
- L286 _private member_ `int32 FixAndHideSearchBreadthLimit;` — Whether to visually show to the user the option of "Search Breadth Limit" or hide it and fix it to a default value: - If 0 or negative, it will show to the user the option of "Search Breadth Limit". - If >0, it will hide that option and fix the Breadth value to this value.
- L288 _private member_ `bool bShowCollectionFilter;` — Whether to visually show to the user the option of "Collection Filter"
- L290 _private member_ `bool bShowPluginFilter;` — Whether to visually show to the user the option of "Plugin Filter"
- L292 _private member_ `bool bShowShowReferencesOptions;` — Whether to visually show to the user the options of "Show Soft/Hard/Management References"
- L294 _private member_ `bool bShowShowSearchableNames;` — Whether to visually show to the user the option of "Show Searchable Names"
- L296 _private member_ `bool bShowShowCodePackages;` — Whether to visually show to the user the option of "Show C++ Packages"
- L298 _private member_ `bool bShowShowFilteredPackagesOnly;` — Whether to visually show to the user the option of "Show Filtered Packages Only"
- L300 _private member_ `bool bDirtyResults;` — True if our view is out of date due to asset registry changes
- L302 _private member_ `bool bShowCompactMode;` — Whether to visually show to the user the option of "Compact Mode"
- L305 _private member_ `bool bShowingContentVersePath;` — Whether to show Verse paths
- L308 _private member_ `bool bRebuildingFilters;` — A recursion check so as to avoid the rebuild of the graph if we are currently rebuilding the filters
- L311 _private member_ `bool bNeedsGraphRebuild;` — Used to delay graph rebuilding during spinbox slider interaction
- L312 _private member_ `bool bNeedsGraphRefilter;`
- L313 _private member_ `bool bNeedsReferencedPropertiesUpdate;`
- L314 _private member_ `double SliderDelayLastMovedTime = 0.0;`
- L315 _private member_ `double GraphRebuildSliderDelay = 0.25;`
- L318 _private member_ `FDelegateHandle AssetRefreshHandle;` — Handle to know if dirty
- L321 _private member_ `FOnReferenceViewerSelectionChanged OnReferenceViewerSelectionChangedDelegate;` — Called when expanding a node, or manually updating the asset path

#### enum `SReferenceViewer::EObjectsListType`  
`enum class EObjectsListType`  
_L224-228_
- L226 _public enumerator_ `Referenced`
- L227 _public enumerator_ `Referencing`

#### enum `EDependencyPinCategory`  
`enum class EDependencyPinCategory`  
_L324-334_
- L326 _public enumerator_ `LinkEndPassive = 0`
- L327 _public enumerator_ `LinkEndActive = 1`
- L328 _public enumerator_ `LinkEndMask = LinkEndActive`
- L330 _public enumerator_ `LinkTypeNone = 0`
- L331 _public enumerator_ `LinkTypeUsedInGame = 2`
- L332 _public enumerator_ `LinkTypeHard = 4`
- L333 _public enumerator_ `LinkTypeMask = LinkTypeHard | LinkTypeUsedInGame`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace ESelectInfo`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReferenceViewerSelectionChanged, const TArray<FAssetIdentifier>&, const TArray<FAssetIdentifier>&) class SReferenceViewer : public SCompoundWidget { public: SLATE_BEGIN_ARGS( SReferenceViewer ){} SLATE_ARGUMENT(TSharedPtr<SDockTab>, ParentTab) SLATE_END_ARGS() ~SReferenceViewer(); void Construct( const FArguments& InArgs ); void SetGraphRootIdentifiers(const TArray<FAssetIdentifier>& NewGraphRootIdentifiers, const FReferenceViewerParams& ReferenceViewerParams = FReferenceViewerParams()); TSharedPtr<SGraphEditor> GetGraphEditor() const { return GraphEditorPtr; } void SetCurrentRegistrySource(const FAssetManagerEditorRegistrySource* RegistrySource); virtual bool SupportsKeyboardFocus() const override { return true; } virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override; virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override; bool CanMakeCollectionWithReferencersOrDependencies(TSharedPtr<ICollectionContainer> CollectionContainer, ECollectionShareType::Type ShareType) const; void MakeCollectionWithReferencersOrDependencies(TSharedPtr<ICollectionContainer> CollectionContainer, ECollectionShareType::Type ShareType, bool bReferencers); FOnReferenceViewerSelectionChanged& OnReferenceViewerSelectionChanged() { return OnReferenceViewerSelectionChangedDelegate; }`
- L335 _prototype_ `ENUM_CLASS_FLAGS(EDependencyPinCategory);`
- L337 _prototype_ `extern EDependencyPinCategory ParseDependencyPinCategory(FName PinCategory);`
- L338 _prototype_ `extern FLinearColor GetColor(EDependencyPinCategory Category);`
- L339 _prototype_ `extern FName GetName(EDependencyPinCategory Category);`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/ReferenceViewer/SReferenceViewerFilterBar.h` (Private)


#### class `SReferenceViewerFilterBar`  
`class SReferenceViewerFilterBar : public SFilterBar< FReferenceNodeInfo& >`  
_L9-23_
- inherits: `SFilterBar<FReferenceNodeInfo&>`
- L15 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget with InArgs
- L18 _public prototype_ `void SaveSettings() override;` — Saves any settings to config that should be persistent between editor sessions
- L21 _public prototype_ `void LoadSettings() override;` — Loads any settings to config that should be persistent between editor sessions

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/ReferenceViewer/SReferencedPropertiesNode.h` (Private)


#### class `SReferencedPropertiesNode`  
`class SReferencedPropertiesNode : public SGraphNode`  
_L16-49_
- inherits: `SGraphNode`
- desc: Widget displaying the list of properties referencing a specified Asset in the reference Viewer. It visually represents an UEdGraphNode_ReferencedProperties node
- L19 _public function_ `SLATE_BEGIN_ARGS(SReferencedPropertiesNode)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphNode_ReferencedProperties* InReferencedPropertiesNode);`
- L27 _public prototype_ `~SReferencedPropertiesNode();`
- L30 _public prototype_ `virtual void UpdateGraphNode() override;`
- L31 _public function_ `virtual bool IsNodeEditable() const override`
- L35 _public function_ `virtual bool CanBeSelected(const FVector2f& InMousePositionInNode) const override`
- L39 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L43 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FReferencingPropertyDescriptionPtr ReferencingPropertyDescription, const TSharedRef<STableViewBase>& TableViewBase) const;`
- L44 _private prototype_ `FReply CloseNode() const;`
- L45 _private prototype_ `FText GetTooltipText() const;`
- L47 _private member_ `TArray<FReferencingPropertyDescriptionPtr> ReferencingPropertiesSource;`
- L48 _private member_ `TSharedPtr<SListView<FReferencingPropertyDescriptionPtr>> PropertiesTreeView;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/SAssetAuditBrowser.h` (Private)


#### class `SAssetAuditBrowser`  
`class SAssetAuditBrowser : public SCompoundWidget`  
_L18-177_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SAssetAuditBrowser)`
- L26 _public prototype_ `void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `virtual ~SAssetAuditBrowser();`
- L31 _public prototype_ `void AddAssetsToList(const TArray<FAssetData>& AssetsToView, bool bReplaceExisting);` — Adds assets to current management view
- L32 _public prototype_ `void AddAssetsToList(const TArray<FSoftObjectPath>& AssetsToView, bool bReplaceExisting);`
- L33 _public prototype_ `void AddAssetsToList(const TArray<FAssetIdentifier>& AssetsToView, bool bReplaceExisting);`
- L34 _public prototype_ `void AddAssetsToList(const TArray<FName>& PackageNamesToView, bool bReplaceExisting);`
- L37 _public prototype_ `void SetCurrentRegistrySource(const FAssetManagerEditorRegistrySource* RegistrySource);` — Called when the current registry source changes
- L40 _public prototype_ `void OnClose();` — Called when tab is closed
- L43 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L44 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L45 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L48 _protected prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets);` — Delegate that handles creation of context menu
- L51 _protected prototype_ `void FindInContentBrowser() const;` — Delegates for context menu
- L52 _protected prototype_ `bool IsAnythingSelected() const;`
- L53 _protected prototype_ `bool IsAnythingSelectedAndLoaded() const;`
- L54 _protected prototype_ `void OnRequestOpenAsset(const FAssetData& AssetData) const;`
- L56 _protected prototype_ `void EditSelectedAssets() const;`
- L57 _protected prototype_ `void SaveSelectedAssets() const;`
- L58 _protected prototype_ `void FindReferencesForSelectedAssets() const;`
- L59 _protected prototype_ `void ShowSizeMapForSelectedAssets() const;`
- L60 _protected prototype_ `void LoadSelectedAssets() const;`
- L62 _protected prototype_ `bool CanShowColumnForAssetRegistryTag(FName AssetType, FName TagName) const;`
- L63 _protected prototype_ `FString GetStringValueForCustomColumn(FAssetData& AssetData, FName ColumnName) const;`
- L64 _protected prototype_ `FText GetDisplayTextForCustomColumn(FAssetData& AssetData, FName ColumnName) const;`
- L65 _protected prototype_ `void OnGetCustomSourceAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssets) const;`
- L68 _protected prototype_ `void GetSelectedPackages(const TArray<FAssetData>& Assets, TArray<UPackage*>& OutPackages) const;` — Populate supplied OutPackages with the packages for the supplied Assets array
- L69 _protected prototype_ `void GetSelectedAssetIdentifiers(const TArray<FAssetData>& Assets, TArray<FAssetIdentifier>& OutAssetIdentifiers) const;`
- L72 _protected prototype_ `FReply OnGoForwardInHistory();` — Single step forward in history
- L75 _protected prototype_ `FReply OnGoBackInHistory();` — Single step back in history
- L78 _protected prototype_ `void GoToHistoryIndex(int32 InHistoryIdx);` — Jumps immediately to an index in the history if valid
- L81 _protected prototype_ `bool CanStepBackwardInHistory() const;` — Returns TRUE if stepping backward in history is allowed
- L84 _protected prototype_ `bool CanStepForwardInHistory() const;` — Returns TRUE if stepping forward in history is allowed
- L91 _protected prototype_ `FReply OnMouseDownHistory( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, TWeakPtr< SMenuAnchor > InMenuAnchor );` — Mouse down callback to display a history menu @param InMenuAnchor		This is the anchor the menu will use for positioning
- L100 _protected prototype_ `TSharedRef<SWidget> CreateHistoryMenu(bool bInBackHistory) const;` — Callback to create the history menu. @param bInBackHistory		TRUE if the back history is requested, FALSE if the forward history is @return						The menu widget displaying all available history
- L103 _protected prototype_ `EVisibility GetHistoryVisibility() const;` — Returns visible when not in a Blueprint mode
- L106 _protected prototype_ `bool HandleFilterAsset(const FAssetData& InAssetData) const;` — Perform additional filtering
- L108 _protected prototype_ `void OnAssetSelected(const FAssetData& InAssetData);`
- L111 _protected prototype_ `FReply ClearAssets();` — Button callbacks
- L112 _protected prototype_ `FReply AddChunks();`
- L113 _protected prototype_ `FReply RefreshAssets();`
- L116 _protected prototype_ `void AddAssetsOfType(FPrimaryAssetType AssetType);` — Adds all assets of type
- L119 _protected prototype_ `void AddManagedAssets(FPrimaryAssetId AssetId);` — Adds all managed assets by an id
- L122 _protected prototype_ `void AddManagedAssetsOfType(FPrimaryAssetType AssetType);` — Adds all managed assets by by type. Useful to see how much size a primary asset type is using.
- L125 _protected prototype_ `void AddAssetsOfClass(UClass* AssetClass);` — Adds all assets of a class
- L128 _protected prototype_ `TSharedRef<SWidget> CreateClassPicker();` — Generates a class picker combo button content
- L131 _protected prototype_ `TSharedRef<SWidget> GenerateSourceComboItem(TSharedPtr<FString> InItem);` — Platform combo box
- L132 _protected prototype_ `void HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);`
- L133 _protected prototype_ `FText GetSourceComboText() const;`
- L136 _protected prototype_ `void RefreshAssetView();` — Refresh the asset view with a new filter
- L139 _protected member_ `TSharedPtr<FUICommandList> Commands;` — Commands handled by this widget
- L142 _protected member_ `TSet<FName> AssetRegistryTagsToIgnore;` — Set of tags to prevent creating details view columns for (infrequently used)
- L145 _protected member_ `TArray<TSet<FName>> AssetHistory;` — List of asset sets to display in browser, current index sets what to display
- L148 _protected member_ `int32 CurrentAssetHistoryIndex;` — Current position in the asset history
- L151 _protected member_ `TArray<TSharedPtr<FString>> SourceComboList;` — List of valid registry sources
- L157 _protected member_ `TSharedPtr<STextBlock> RegistrySourceTimeText;` — Text block where we put the timestamp for the asset registry so the user knows if they are looking at super out of date data.
- L160 _protected member_ `const FAssetManagerEditorRegistrySource* CurrentRegistrySource;` — Current TargetPlatform and registry state, may be null!
- L163 _protected member_ `FSyncToAssetsDelegate SyncToAssetsDelegate;` — Delegates to interact with asset view
- L164 _protected member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;`
- L165 _protected member_ `FSetARFilterDelegate SetFilterDelegate;`
- L168 _protected member_ `static const int32 MaxAssetsHistory;` — Max asset sets to save in history
- L171 _protected member_ `static const FString SettingsIniSection;` — The section of EditorPerProjectUserSettings in which to save settings
- L174 _protected member_ `class IAssetRegistry* AssetRegistry;` — Cached interfaces
- L175 _protected member_ `class UAssetManager* AssetManager;`
- L176 _protected member_ `class IAssetManagerEditorModule* EditorModule;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/SSizeMap.h` (Private)


#### enum `ESizeMapDependencyType`  
`enum class ESizeMapDependencyType`  
_L21-29_
- reflection: `UENUM()`
- L24 _public enumerator_ `All` — Queries all hard dependencies
- L26 _public enumerator_ `Game` — Queries hard dependencies that are part of a cooked build. See UE::AssetRegistry::EDependencyQuery::Game.
- L28 _public enumerator_ `EditorOnly` — Queries hard dependencies that only exist in the editor. See UE::AssetRegistry::EDependencyQuery::EditorOnly

#### class `USizeMapSettings`  
`class USizeMapSettings : public UObject`  
_L32-42_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L38 _public member_ `FName SizeType = IAssetManagerEditorModule::DiskSizeName;` — `UPROPERTY(config)`
- L41 _public member_ `ESizeMapDependencyType DependencyType = ESizeMapDependencyType::All;` — `UPROPERTY(config)`

#### class `SSizeMap`  
`class SSizeMap : public SCompoundWidget`  
_L47-211_
- inherits: `SCompoundWidget`
- desc: Tree map for displaying the size of assets
- L52 _public function_ `SLATE_BEGIN_ARGS(SSizeMap)`
- L57 _public prototype_ `SSizeMap();` — Default constructor for SSizeMap
- L60 _public prototype_ `~SSizeMap();` — Destructor for SSizeMap
- L67 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the widget @param	InArgs				A declaration from which to construct the widget
- L70 _public prototype_ `void SetRootAssetIdentifiers(const TArray<FAssetIdentifier>& NewRootAssetIdentifiers);` — Sets the assets to view at the root of the size map.  This will rebuild the map.
- L73 _public prototype_ `void SetCurrentRegistrySource(const FAssetManagerEditorRegistrySource* RegistrySource);` — Called when the current registry source changes
- L93 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — Overrides
- L94 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L95 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L98 _protected prototype_ `void OnInitialAssetRegistrySearchComplete();` — Called after the initial asset registry scan finishes
- L101 _protected prototype_ `void GatherDependenciesRecursively(TSharedPtr<class FAssetThumbnailPool>& AssetThumbnailPool, TMap<FAssetIdentifier, TSharedPtr<class FTreeMapNodeData>>& VisitedAssetIdentifiers, const TSet<FAssetIdentifier>& AssetIdentifiers, const FPrimaryAssetId& FilterPrimaryAsset, const TSharedPtr<FTreeMapNodeData>& ParentTreeMapNode, TSharedPtr<FTreeMapNodeData>& SharedRootNode, int32& NumAssetsWhichFailedToLoad);` — Recursively discovers and loads dependent assets, building up a tree map node hierarchy
- L104 _protected prototype_ `void GatherExternalPackages(const FAssetData CurrentAssetData, FName AssetPackageName, TSharedRef<FTreeMapNodeData> ChildTreeMapNode, TMap<FAssetIdentifier, TSharedPtr<FTreeMapNodeData>>& VisitedAssetIdentifiers);` — Gather all external/generated packages tied to the provided asset
- L107 _protected prototype_ `void FinalizeNodesRecursively(TSharedPtr<FTreeMapNodeData>& Node, const TSharedPtr<FTreeMapNodeData>& SharedRootNode, int32& TotalAssetCount, SIZE_T& TotalSize, bool& bAnyUnknownSizes);` — After the node tree is built up, this function is called to generate nice labels for the nodes and to do a final clean-up pass on the tree
- L110 _protected prototype_ `void RefreshMap();` — Refreshes the display
- L113 _protected prototype_ `TSharedPtr<FTreeMapNodeData> GetCurrentTreeNode(bool bConsumeSelection = false) const;` — Returns the size map data associated with current tree map node. If Consume is true it unsets the current selected node
- L114 _protected prototype_ `const FNodeSizeMapData* GetCurrentSizeMapData(bool bConsumeSelection = false) const;`
- L117 _protected prototype_ `void GetReferencedPackages(TSet<FName>& OutPackageNames, TSharedPtr<FTreeMapNodeData> RootNode, bool bRecurse = true) const;` — Returns package names that are referenced by this node, not including root node
- L120 _protected prototype_ `void OnTreeMapNodeRightClicked(class FTreeMapNodeData& TreeMapNodeData, const FPointerEvent& MouseEvent);` — Called when the user right-clicks on an asset in the tree
- L121 _protected prototype_ `void GetMakeCollectionWithDependenciesCollectionContainersSubMenu(class FMenuBuilder& MenuBuilder, TArray<TSharedPtr<ICollectionContainer>> CollectionContainers);`
- L122 _protected prototype_ `void GetMakeCollectionWithDependenciesShareTypeSubMenu(class FMenuBuilder& MenuBuilder);`
- L123 _protected prototype_ `void GetMakeCollectionWithDependenciesShareTypeSubMenu(class FMenuBuilder& MenuBuilder, TSharedPtr<ICollectionContainer> CollectionContainer);`
- L126 _protected prototype_ `void FindInContentBrowser() const;` — Delegates for context menu
- L127 _protected prototype_ `bool IsAnythingSelected() const;`
- L128 _protected prototype_ `void EditSelectedAssets() const;`
- L129 _protected prototype_ `void FindReferencesForSelectedAssets() const;`
- L130 _protected prototype_ `void ShowAssetAuditForSelectedAssets() const;`
- L131 _protected prototype_ `void ShowAssetAuditForReferencedAssets() const;`
- L132 _protected prototype_ `void CopyPackageName() const;`
- L133 _protected prototype_ `bool CanMakeCollectionWithDependencies(ECollectionShareType::Type ShareType) const;`
- L134 _protected prototype_ `void MakeCollectionWithDependencies(ECollectionShareType::Type ShareType);`
- L135 _protected prototype_ `bool CanMakeCollectionWithDependencies(TSharedPtr<ICollectionContainer> CollectionContainer, ECollectionShareType::Type ShareType) const;`
- L136 _protected prototype_ `void MakeCollectionWithDependencies(TSharedPtr<ICollectionContainer> CollectionContainer, ECollectionShareType::Type ShareType);`
- L139 _protected prototype_ `FReply OnZoomOut();` — Back button
- L140 _protected prototype_ `bool CanZoomOut() const;`
- L143 _protected prototype_ `TSharedRef<SWidget> GenerateSizeTypeComboItem(TSharedPtr<FName> InItem) const;` — Size Type Combo Box
- L144 _protected prototype_ `void HandleSizeTypeComboChanged(TSharedPtr<FName> Item, ESelectInfo::Type SelectInfo);`
- L145 _protected prototype_ `FText GetSizeTypeComboText() const;`
- L146 _protected prototype_ `FText GetSizeTypeText(FName SizeType) const;`
- L147 _protected prototype_ `FText GetOverviewText() const;`
- L148 _protected prototype_ `bool IsSizeTypeEnabled() const;`
- L150 _protected member_ `TArray<TSharedPtr<FName>> SizeTypeComboList;`
- L151 _protected member_ `FText OverviewText;`
- L152 _protected member_ `bool bMemorySizeCached;`
- L153 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> SizeTypeComboBoxWidget;`
- L156 _protected prototype_ `TSharedRef<SWidget> GenerateDependencyTypeComboItem(TSharedPtr<ESizeMapDependencyType> InItem) const;` — Dependency Type Combo Box
- L157 _protected prototype_ `void HandleDependencyTypeComboChanged(TSharedPtr<ESizeMapDependencyType> Item, ESelectInfo::Type SelectInfo);`
- L158 _protected prototype_ `FText GetDependencyTypeComboText() const;`
- L159 _protected prototype_ `FText GetDependencyTypeText(ESizeMapDependencyType DependencyType) const;`
- L161 _protected member_ `TArray<TSharedPtr<ESizeMapDependencyType>> DependencyTypeComboList;`
- L162 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<ESizeMapDependencyType>>> DependencyTypeComboBoxWidget;`
- L165 _protected prototype_ `TSharedRef<SWidget> GenerateSourceComboItem(TSharedPtr<FString> InItem) const;` — Platform / Registry Source Combo Box
- L166 _protected prototype_ `void HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);`
- L167 _protected prototype_ `FText GetSourceComboText() const;`
- L169 _protected member_ `TArray<TSharedPtr<FString>> SourceComboList;`
- L170 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> SourceComboBoxWidget;`
- L173 _protected prototype_ `TSharedRef<SWidget> GeneratePluginComboItem(TSharedPtr<FString> InItem) const;` — Plugin Filter Combo Box — sets plugin assets as root identifiers
- L174 _protected prototype_ `void HandlePluginComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);`
- L175 _protected prototype_ `FText GetPluginComboText() const;`
- L178 _protected prototype_ `void SetRootAssetIdentifiersFromPlugin(const FString& PluginName);` — Clears root identifiers and replaces them with all assets from PluginName
- L180 _protected member_ `TArray<TSharedPtr<FString>> PluginComboList;`
- L181 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> PluginComboBoxWidget;`
- L182 _protected member_ `FString CurrentPluginSelection;` — Empty string = no plugin filter (None)
- L185 _protected member_ `TSharedPtr<class STreeMap> TreeMapWidget;` — Our tree map widget
- L188 _protected member_ `TSet<FAssetIdentifier> RootAssetIdentifiers;` — The assets we were asked to look at
- L191 _protected member_ `TSharedPtr<class FTreeMapNodeData> RootTreeMapNode;` — Our tree map source data
- L194 _protected member_ `TSharedPtr<class FAssetThumbnailPool> AssetThumbnailPool;` — Thumbnail pool
- L197 _protected typedef_ `typedef TMap<TSharedRef<FTreeMapNodeData>, FNodeSizeMapData> FNodeSizeMapDataMap;` — Maps a tree node to our size map-specific user data for that node
- L198 _protected member_ `FNodeSizeMapDataMap NodeSizeMapDataMap;`
- L199 _protected member_ `mutable TWeakPtr<FTreeMapNodeData> CurrentSelectedNode;`
- L202 _protected member_ `const FAssetManagerEditorRegistrySource* CurrentRegistrySource;` — The registry source to display information for
- L205 _protected member_ `TSharedPtr<FUICommandList> Commands;` — Commands handled by this widget
- L208 _protected member_ `class IAssetRegistry* AssetRegistry;` — Cached interfaces
- L209 _protected member_ `class UAssetManager* AssetManager;`
- L210 _protected member_ `class IAssetManagerEditorModule* EditorModule;`

#### struct `SSizeMap::FNodeSizeMapData`  
`struct FNodeSizeMapData`  
_L77-90_
- desc: This struct will contain size map-specific payload data that we'll associate with tree map nodes using a hash table
- L80 _public member_ `SIZE_T AssetSize = 0;` — How big the asset is
- L83 _public member_ `bool bHasKnownSize = false;` — Whether it has a known size or not
- L86 _public member_ `int32 ExternalPackageCount = 0;` — Number of external/generated packages discovered for this asset
- L89 _public member_ `FAssetData AssetData;` — Data from the asset registry about this asset

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ESelectInfo`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/TreeView/AssetDependencyGrouping.h` (Private)


#### class `FAssetDependencyGrouping`  
`class FAssetDependencyGrouping : public UE::Insights::FTreeNodeGrouping`  
_L9-18_
- inherits: `UE::Insights::FTreeNodeGrouping`
- L14 _public prototype_ `FAssetDependencyGrouping();`
- L15 _public prototype_ `virtual ~FAssetDependencyGrouping();`
- L17 _public prototype_ `virtual void GroupNodes(const TArray<UE::Insights::FTableTreeNodePtr>& Nodes, UE::Insights::FTableTreeNode& ParentGroup, TWeakPtr<UE::Insights::FTable> InParentTable, UE::Insights::IAsyncOperationProgress& InAsyncOperationProgress) const override;`

#### class `FPluginDependencyGrouping`  
`class FPluginDependencyGrouping : public UE::Insights::FTreeNodeGrouping`  
_L20-29_
- inherits: `UE::Insights::FTreeNodeGrouping`
- L25 _public prototype_ `FPluginDependencyGrouping();`
- L26 _public prototype_ `virtual ~FPluginDependencyGrouping();`
- L28 _public prototype_ `virtual void GroupNodes(const TArray<UE::Insights::FTableTreeNodePtr>& Nodes, UE::Insights::FTableTreeNode& ParentGroup, TWeakPtr<UE::Insights::FTable> InParentTable, UE::Insights::IAsyncOperationProgress& InAsyncOperationProgress) const override;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/TreeView/AssetTable.h` (Private)


#### class `FAssetTableStringStore`  
`class FAssetTableStringStore`  
_L24-110_
- desc: Simple string store.
- L27 _private member_ `static constexpr int32 ChunkBufferLen = 1024 * 1024;` — 2 MiB/buffer
- L28 _private member_ `static constexpr ESearchCase::Type SearchCase = ESearchCase::CaseSensitive;`
- L37 _public prototype_ `FAssetTableStringStore();`
- L38 _public prototype_ `~FAssetTableStringStore();`
- L41 _public prototype_ `void Reset();` — Resets this string store. Frees all memory.
- L46 _public prototype_ `const FStringView Store(const TCHAR* InStr);` — Store a string. Gets the stored string for specified input string. @param InStr - the input string @returns the stored string view.
- L52 _public prototype_ `const FStringView Store(const FStringView InStr);` — Store a string. Gets the stored string for specified input string. The returned string is guaranteed to be null terminated. @param InStr - the input string @returns the stored string view.
- L56 _public function_ `int32 GetMaxStringLength() const` — Gets the maximum length of a single string that can be stored. @returns the maximum string length
- L63 _public function_ `int32 GetNumInputStrings() const` — Gets number of input strings, including duplicates. @returns number of input strings.
- L70 _public function_ `SIZE_T GetTotalInputStringSize() const` — Gets size of input strings, including duplicates, in [bytes]. @returns size of input strings, in [bytes].
- L77 _public function_ `int32 GetNumStrings() const` — Gets number of stored (unique) strings. @returns number of stored strings.
- L84 _public function_ `SIZE_T GetTotalStringSize() const` — Gets size of stored (unique) strings, in [bytes]. @returns size of stored strings, in [bytes].
- L91 _public function_ `SIZE_T GetAllocatedSize() const` — Gets (estimated) total allocated memory for this string store, in [bytes]. @returns memory size, in [bytes].
- L98 _public prototype_ `void EnumerateStrings(TFunction<void(const FStringView Str)> Callback) const;`
- L101 _private prototype_ `void AddChunk();`
- L104 _private member_ `TArray<FChunk> Chunks;`
- L105 _private member_ `TMultiMap<uint32, FStringView> Cache;` — Hash --> FStringView
- L106 _private member_ `SIZE_T TotalInputStringSize;`
- L107 _private member_ `SIZE_T TotalStoredStringSize;`
- L108 _private member_ `int32 NumInputStrings;`
- L109 _private member_ `int32 NumStoredStrings;`

#### struct `FAssetTableStringStore::FChunk`  
`struct FChunk`  
_L30-34_
- L32 _public member_ `TCHAR* Buffer = nullptr;`
- L33 _public member_ `uint32 Used = 0;`

#### struct `FAssetTableColumns`  
`struct FAssetTableColumns`  
_L113-131_
- desc: Column identifiers
- L115 _public member_ `static const FName CountColumnId;`
- L116 _public member_ `static const FName TypeColumnId;`
- L117 _public member_ `static const FName NameColumnId;`
- L118 _public member_ `static const FName PathColumnId;`
- L119 _public member_ `static const FName PrimaryTypeColumnId;`
- L120 _public member_ `static const FName PrimaryNameColumnId;`
- L121 _public member_ `static const FName StagedCompressedSizeRequiredInstallColumnId;`
- L122 _public member_ `static const FName TotalSizeUniqueDependenciesColumnId;`
- L123 _public member_ `static const FName TotalSizeSharedDependenciesColumnId;`
- L124 _public member_ `static const FName TotalSizeExternalDependenciesColumnId;`
- L125 _public member_ `static const FName TotalUsageCountColumnId;`
- L126 _public member_ `static const FName ChunksColumnId;`
- L127 _public member_ `static const FName NativeClassColumnId;`
- L128 _public member_ `static const FName PluginNameColumnId;`
- L129 _public member_ `static const FName PluginInclusiveSizeColumnId;`
- L130 _public member_ `static const FName PluginTypeColumnId;`

#### struct `FAssetTableDependencySizes`  
`struct FAssetTableDependencySizes`  
_L133-137_
- L135 _public member_ `int64 UniqueDependenciesSize = 0;`
- L136 _public member_ `int64 SharedDependenciesSize = 0;`

#### class `FAssetTablePluginInfo`  
`class FAssetTablePluginInfo`  
_L139-211_
- L145 _public function_ `const TCHAR* GetName() const`
- L147 _public function_ `int32 GetNumDependencies() const`
- L148 _public function_ `const TArray<int32>& GetDependencies() const`
- L149 _public function_ `int32 GetNumReferencers() const`
- L150 _public function_ `const TArray<int32>& GetReferencers() const`
- L151 _public function_ `int64 GetSize() const`
- L152 _public function_ `bool IsRootPlugin() const`
- L153 _public function_ `const TCHAR* GetPluginType() const`
- L155 _public prototype_ `int64 GetOrComputeTotalSizeInclusiveOfDependencies(const FAssetTable& OwningTable) const;`
- L158 _public prototype_ `int64 GetOrComputeTotalSizeUniqueDependencies(const FAssetTable& OwningTable) const;` — This is the total size of all dependencies which are not used by any plugin that is not this plugin or one of its other dependencies
- L160 _public prototype_ `int64 GetOrComputeTotalSizeSharedDependencies(const FAssetTable& OwningTable) const;` — This is the total size of all dependencies which are used by some plugin not referenced (directly or indirectly) by this plugin
- L162 _public prototype_ `static void ComputeTotalSelfAndInclusiveSizes(const FAssetTable& OwningTable, const TSet<int32>& RootPlugins, int64& OutTotalSelfSize, int64& OutTotalInclusiveSize);`
- L164 _public function_ `TSet<int32> GetPluginAssets() const`
- L166 _public function_ `void AddPluginAsset(const int32 RowIndex)`
- L168 _public function_ `template<typename T> const T* TryGetDataByKey(int32 Key) const`
- L188 _private prototype_ `void ComputeDependencySizes(const FAssetTable& OwningTable) const;`
- L190 _private member_ `TArray<int32> PluginDependencies;`
- L191 _private member_ `TArray<int32> PluginReferencers;`
- L192 _private member_ `TSet<int32> PluginAssets;`
- L194 _private typedef_ `typedef TVariant<bool, const TCHAR*> CustomFieldVariantType;`
- L202 _private member_ `TArray<FCustomColumnData> CustomColumnData;`
- L204 _private member_ `const TCHAR* PluginName = nullptr;`
- L205 _private member_ `const TCHAR* PluginTypeString = nullptr;`
- L206 _private member_ `int64 Size = 0;`
- L207 _private member_ `mutable int64 InclusiveSize = -1;`
- L208 _private member_ `mutable int64 UniqueDependenciesSize = -1;`
- L209 _private member_ `mutable int64 SharedDependenciesSize = -1;`
- L210 _private member_ `bool bIsRootPlugin = false;`

#### struct `FAssetTablePluginInfo::FCustomColumnData`  
`struct FCustomColumnData`  
_L196-200_
- L198 _public member_ `CustomFieldVariantType Value;`
- L199 _public member_ `int32 Key;`

#### class `FAssetTableRow`  
`class FAssetTableRow`  
_L213-277_
- L219 _public function_ `FAssetTableRow()`
- L222 _public prototype_ `~FAssetTableRow() = default;`
- L224 _public function_ `FName GetNodeName() const`
- L226 _public function_ `const TCHAR* GetType() const`
- L227 _public function_ `const TCHAR* GetName() const`
- L228 _public function_ `const TCHAR* GetPath() const`
- L229 _public function_ `const TCHAR* GetPrimaryType() const`
- L230 _public function_ `const TCHAR* GetPrimaryName() const`
- L231 _public function_ `int64 GetStagedCompressedSizeRequiredInstall() const`
- L232 _public prototype_ `int64 GetOrComputeTotalSizeUniqueDependencies(const FAssetTable& OwningTable, int32 ThisIndex) const;`
- L233 _public prototype_ `int64 GetOrComputeTotalSizeSharedDependencies(const FAssetTable& OwningTable, int32 ThisIndex) const;`
- L234 _public prototype_ `int64 GetOrComputeTotalSizeExternalDependencies(const FAssetTable& OwningTable, int32 ThisIndex) const;`
- L235 _public function_ `int64 GetTotalUsageCount() const`
- L236 _public function_ `const TCHAR* GetChunks() const`
- L237 _public function_ `const TCHAR* GetNativeClass() const`
- L238 _public function_ `const TCHAR* GetPluginName() const`
- L239 _public function_ `int32 GetNumDependencies() const`
- L240 _public function_ `const TArray<int32>& GetDependencies() const`
- L241 _public function_ `int32 GetNumReferencers() const`
- L242 _public function_ `const TArray<int32>& GetReferencers() const`
- L243 _public function_ `FLinearColor GetColor() const`
- L244 _public function_ `const FSoftObjectPath& GetSoftObjectPath() const`
- L246 _public prototype_ `static FAssetTableDependencySizes ComputeDependencySizes(const FAssetTable& OwningTable, const TSet<int32>& RootIndices, TSet<int32>* OutUniqueDependencies = nullptr, TSet<int32>* OutSharedDependencies = nullptr);`
- L248 _public prototype_ `static int64 ComputeTotalSizeExternalDependencies(const FAssetTable& OwningTable, const TSet<int32>& StartingNodes, TSet<int32>* OutExternalDependencies = nullptr, TMap<int32, TArray<int32>>* OutRouteMap = nullptr);`
- L252 _public prototype_ `static TSet<int32> GatherAllReachableNodes(const TArray<int32>& StartingNodes, const FAssetTable& OwningTable, const TSet<int32>& AdditionalNodesToStopAt, const TSet<const TCHAR*, TStringPointerSetKeyFuncs_DEPRECATED<const TCHAR*>>& RestrictToPlugins, TMap<int32, TArray<int32>>* OutRouteMap = nullptr);` — Finds all nodes reachable from StartingNodes INCLUDING those in StartingNodes An optional OutRouteMap may be provided. For each discovered reachable node, the routemap will get a value entry containing an array of nodes that constitute one possible path from a StartingNode to the destination
- L255 _private prototype_ `static void RefineDependencies(const TSet<int32>& PreviouslyVisitedIndices, const FAssetTable& OwningTable, const TSet<int32> RootIndices, const TSet<const TCHAR*, TStringPointerSetKeyFuncs_DEPRECATED<const TCHAR*>>& RestrictToGFPs, TSet<int32>& OutUniqueIndices, TSet<int32>& OutSharedIndices);`
- L256 _private function_ `static inline bool ShouldSkipDueToPlugin(const TSet<const TCHAR*, TStringPointerSetKeyFuncs_DEPRECATED<const TCHAR*>>& RestrictToPlugins, const TCHAR* PluginName)`
- L260 _private member_ `FSoftObjectPath SoftObjectPath;` — Used to allow you to go to that asset in the content browser or to open its editor after lookingup the FAssetData in the original registry state
- L261 _private member_ `const TCHAR* Type = nullptr;`
- L262 _private member_ `const TCHAR* Name = nullptr;`
- L263 _private member_ `const TCHAR* Path = nullptr;`
- L264 _private member_ `const TCHAR* PrimaryType = nullptr;`
- L265 _private member_ `const TCHAR* PrimaryName = nullptr;`
- L266 _private member_ `int64 StagedCompressedSizeRequiredInstall = 0;`
- L267 _private member_ `mutable int64 TotalSizeUniqueDependencies = -1;` — Lazily calculated
- L268 _private member_ `mutable int64 TotalSizeSharedDependencies = -1;` — Lazily calculated
- L269 _private member_ `mutable int64 TotalSizeExternalDependencies = -1;` — Lazily calculated
- L270 _private member_ `int64 TotalUsageCount = 0;`
- L271 _private member_ `const TCHAR* Chunks = nullptr;`
- L272 _private member_ `const TCHAR* NativeClass = nullptr;`
- L273 _private member_ `const TCHAR* PluginName = nullptr;`
- L274 _private member_ `TArray<int32> Dependencies;`
- L275 _private member_ `TArray<int32> Referencers;`
- L276 _private member_ `FLinearColor Color;`

#### class `FAssetTable`  
`class FAssetTable : public UE::Insights::FTable`  
_L279-368_
- inherits: `UE::Insights::FTable`
- L282 _public prototype_ `FAssetTable();`
- L283 _public prototype_ `virtual ~FAssetTable();`
- L285 _public prototype_ `virtual void Reset();`
- L287 _public function_ `TArray<FAssetTableRow>& GetAssets()`
- L288 _public function_ `const TArray<FAssetTableRow>& GetAssets() const`
- L290 _public function_ `bool IsValidRowIndex(int32 InIndex) const`
- L291 _public function_ `FAssetTableRow* GetAsset(int32 InIndex)`
- L292 _public function_ `const FAssetTableRow* GetAsset(int32 InIndex) const`
- L293 _public function_ `FAssetTableRow& GetAssetChecked(int32 InIndex)`
- L294 _public function_ `const FAssetTableRow& GetAssetChecked(int32 InIndex) const`
- L296 _public function_ `int32 GetTotalAssetCount() const`
- L297 _public function_ `int32 GetVisibleAssetCount() const`
- L298 _public function_ `int32 GetHiddenAssetCount() const`
- L300 _public function_ `void SetVisibleAssetCount(int32 InVisibleAssetCount)`
- L302 _public function_ `void AddAsset(const FAssetTableRow& AssetRow)`
- L304 _public prototype_ `FAssetTablePluginInfo& GetOrCreatePluginInfo(const TCHAR* StoredPluginName);`
- L306 _public function_ `const FAssetTablePluginInfo& GetPluginInfoByIndex(int32 PluginIndex) const`
- L307 _public function_ `FAssetTablePluginInfo& GetPluginInfoByIndex(int32 PluginIndex)`
- L308 _public function_ `const FAssetTablePluginInfo& GetPluginInfoByIndexChecked(int32 PluginIndex) const`
- L309 _public prototype_ `int32 GetIndexForPlugin(const TCHAR* StoredPluginName) const;`
- L310 _public function_ `int32 GetNumPlugins() const`
- L312 _public function_ `FName GetNameForPlugin(int32 InPluginIndex) const`
- L321 _public function_ `bool IsValidPluginIndex(int32 Index) const`
- L323 _public prototype_ `void EnumeratePluginDependencies(const FAssetTablePluginInfo& InPlugin, TFunction<void(int32 PluginIndex)> Callback) const;`
- L324 _public prototype_ `void EnumerateAssetsForPlugin(const FAssetTablePluginInfo& InPlugin, TFunction<void(int32 AssetIndex)> Callback) const;`
- L326 _public function_ `const FStringView StoreString(const FStringView InStr)`
- L327 _public function_ `const TCHAR* StoreStr(const FString& InStr)`
- L328 _public function_ `const FAssetTableStringStore& GetStringStore() const`
- L329 _public function_ `FAssetTableStringStore& GetStringStore()`
- L331 _public function_ `void ClearAllData()`
- L341 _public prototype_ `void PopulateAssetsInPlugins();`
- L356 _public function_ `void AddCustomColumn(const FCustomColumnDefinition& ColumnDefinition)`
- L359 _private prototype_ `void AddDefaultColumns();`
- L362 _private member_ `TArray<FAssetTableRow> Assets;`
- L363 _private member_ `TArray<FAssetTablePluginInfo> Plugins;`
- L364 _private member_ `TMap<const TCHAR*, int32, FDefaultSetAllocator, TStringPointerMapKeyFuncs_DEPRECATED<const TCHAR*, int32>> PluginNameToIndexMap;`
- L365 _private member_ `TArray<FCustomColumnDefinition> CustomColumns;`
- L366 _private member_ `int32 VisibleAssetCount = 0;`
- L367 _private member_ `FAssetTableStringStore StringStore;`

#### enum `FAssetTable::ECustomColumnDefinitionType`  
`enum class ECustomColumnDefinitionType`  
_L343-347_
- L345 _public enumerator_ `Boolean`
- L346 _public enumerator_ `String`

#### struct `FAssetTable::FCustomColumnDefinition`  
`struct FCustomColumnDefinition`  
_L349-354_
- L351 _public member_ `FName ColumnId;`
- L352 _public member_ `ECustomColumnDefinitionType Type;`
- L353 _public member_ `int32 Key;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Insights` (scope `UE`)

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/TreeView/AssetTreeNode.h` (Private)


#### class `FAssetTreeNode`  
`class FAssetTreeNode : public UE::Insights::FTableTreeNode`  
_L14-74_
- inherits: `UE::Insights::FTableTreeNode`
- L20 _public function_ `explicit FAssetTreeNode(const FName InName, TWeakPtr<FAssetTable> InParentTable, int32 InRowIndex) : FTableTreeNode(InName, InParentTable, InRowIndex) , AssetTablePtr(InParentTable.Pin().Get())` — Initialization constructor for the asset node.
- L27 _public function_ `explicit FAssetTreeNode(const FName InGroupName, TWeakPtr<FAssetTable> InParentTable) : FTableTreeNode(InGroupName, InParentTable) , AssetTablePtr(InParentTable.Pin().Get())` — Initialization constructor for the group node.
- L34 _public function_ `explicit FAssetTreeNode(const FName InName, TWeakPtr<FAssetTable> InParentTable, int32 InRowIndex, bool bIsGroup) : FTableTreeNode(InName, InParentTable, InRowIndex, bIsGroup) , AssetTablePtr(InParentTable.Pin().Get())` — Initialization constructor for the asset and/or group node.
- L40 _public prototype_ `virtual ~FAssetTreeNode() = default;`
- L42 _public function_ `TWeakPtr<FAssetTable> GetAssetTableWeak() const`
- L44 _public function_ `bool IsValidAsset() const`
- L45 _public function_ `FAssetTable& GetAssetTableChecked() const`
- L46 _public function_ `const FAssetTableRow& GetAssetChecked() const`
- L48 _public prototype_ `virtual const FSlateBrush* GetIcon() const final;`
- L49 _public prototype_ `virtual FLinearColor GetIconColor() const final;`
- L50 _public prototype_ `virtual FLinearColor GetColor() const final;`
- L52 _public function_ `bool IsPluginRelatedNode() const`
- L53 _public function_ `bool IsAssetRelatedNode() const`
- L67 _protected prototype_ `virtual EStyle GetStyle() const;`
- L68 _protected prototype_ `const FSlateBrush* GetIcon(EStyle Style) const;`
- L69 _protected prototype_ `FLinearColor GetIconColor(EStyle Style) const;`
- L70 _protected prototype_ `FLinearColor GetColor(EStyle Style) const;`
- L73 _private member_ `FAssetTable* AssetTablePtr;`

#### enum `FAssetTreeNode::EStyle`  
`enum class EStyle`  
_L58-65_
- desc: Set of UI style options for node types
- L60 _public enumerator_ `EDefault`
- L61 _public enumerator_ `EGroup`
- L62 _public enumerator_ `EAsset`
- L63 _public enumerator_ `EDependencies`
- L64 _public enumerator_ `EPlugin`

#### class `FAssetDependenciesGroupTreeNode`  
`class FAssetDependenciesGroupTreeNode : public FAssetTreeNode`  
_L90-118_
- inherits: `FAssetTreeNode`
- L96 _public function_ `explicit FAssetDependenciesGroupTreeNode(const FName InGroupName, TWeakPtr<FAssetTable> InParentTable, int32 InParentRowIndex) : FAssetTreeNode(InGroupName, InParentTable, InParentRowIndex, true) , bAreChildrenCreated(false) , AuthorGrouping(nullptr)` — Initialization constructor for the group node.
- L105 _public prototype_ `virtual ~FAssetDependenciesGroupTreeNode() = default;`
- L107 _public prototype_ `virtual EStyle GetStyle() const override;`
- L109 _public prototype_ `virtual const FText GetExtraDisplayName() const;`
- L110 _public prototype_ `virtual bool OnLazyCreateChildren(TSharedPtr<class UE::Insights::STableTreeView> InTableTreeView) override;`
- L112 _public function_ `virtual const UE::Insights::FTreeNodeGrouping* GetAuthorGrouping() const override`
- L113 _public function_ `void SetAuthorGrouping(const UE::Insights::FTreeNodeGrouping* InAuthorGrouping)`
- L116 _private member_ `bool bAreChildrenCreated;`
- L117 _private member_ `const UE::Insights::FTreeNodeGrouping* AuthorGrouping;`

#### class `FPluginSimpleGroupNode`  
`class FPluginSimpleGroupNode : public FAssetTreeNode`  
_L125-152_
- inherits: `FAssetTreeNode`
- L131 _public function_ `explicit FPluginSimpleGroupNode(const FName InGroupName, TWeakPtr<FAssetTable> InParentTable, int32 InPluginIndex) : FAssetTreeNode(InGroupName, InParentTable) , PluginIndex(InPluginIndex) , AuthorGrouping(nullptr)` — Initialization constructor.
- L138 _public prototype_ `virtual ~FPluginSimpleGroupNode() = default;`
- L140 _public prototype_ `virtual EStyle GetStyle() const override;`
- L142 _public prototype_ `void AddAssetChildrenNodes();`
- L144 _public function_ `int32 GetPluginIndex() const`
- L146 _public function_ `virtual const UE::Insights::FTreeNodeGrouping* GetAuthorGrouping() const override`
- L147 _public function_ `void SetAuthorGrouping(const UE::Insights::FTreeNodeGrouping* InAuthorGrouping)`
- L150 _protected member_ `int32 PluginIndex;`
- L151 _protected member_ `const UE::Insights::FTreeNodeGrouping* AuthorGrouping;`

#### class `FPluginAndDependenciesGroupNode`  
`class FPluginAndDependenciesGroupNode : public FPluginSimpleGroupNode`  
_L156-172_
- inherits: `FPluginSimpleGroupNode`
- L162 _public function_ `explicit FPluginAndDependenciesGroupNode(const FName InGroupName, TWeakPtr<FAssetTable> InParentTable, int32 InPluginIndex) : FPluginSimpleGroupNode(InGroupName, InParentTable, InPluginIndex)` — Initialization constructor.
- L167 _public prototype_ `virtual ~FPluginAndDependenciesGroupNode() = default;`
- L169 _public prototype_ `virtual EStyle GetStyle() const override;`
- L171 _public prototype_ `TSharedPtr<FPluginSimpleGroupNode> CreateChildren();`

#### class `FPluginDependenciesGroupNode`  
`class FPluginDependenciesGroupNode : public FPluginSimpleGroupNode`  
_L176-197_
- inherits: `FPluginSimpleGroupNode`
- L182 _public function_ `explicit FPluginDependenciesGroupNode(const FName InGroupName, TWeakPtr<FAssetTable> InParentTable, int32 InPluginIndex) : FPluginSimpleGroupNode(InGroupName, InParentTable, InPluginIndex) , bAreChildrenCreated(false)` — Initialization constructor.
- L188 _public prototype_ `virtual ~FPluginDependenciesGroupNode() = default;`
- L190 _public prototype_ `virtual EStyle GetStyle() const override;`
- L192 _public prototype_ `virtual const FText GetExtraDisplayName() const;`
- L193 _public prototype_ `virtual bool OnLazyCreateChildren(TSharedPtr<class UE::Insights::STableTreeView> InTableTreeView) override;`
- L196 _private member_ `bool bAreChildrenCreated;`

#### Free symbols / members of external scopes

- L77 _typedef_ `typedef TSharedPtr<class FAssetTreeNode> FAssetTreeNodePtr;` — Type definition for shared pointers to instances of FAssetTreeNode.
- L80 _typedef_ `typedef TSharedRef<class FAssetTreeNode> FAssetTreeNodeRef;` — Type definition for shared references to instances of FAssetTreeNode.
- L83 _typedef_ `typedef TSharedRef<const class FAssetTreeNode> FAssetTreeNodeRefConst;` — Type definition for shared references to const instances of FAssetTreeNode.
- L86 _typedef_ `typedef TWeakPtr<class FAssetTreeNode> FAssetTreeNodeWeak;` — Type definition for weak references to instances of FAssetTreeNode.
- L121 _typedef_ `typedef TSharedPtr<class FAssetDependenciesGroupTreeNode> FAssetDependenciesGroupTreeNodePtr;` — Type definition for shared pointers to instances of FAssetDependenciesGroupTreeNode.

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/TreeView/SAssetTableTreeView.h` (Private)


#### class `SAssetTableTreeView`  
`class SAssetTableTreeView : public UE::Insights::STableTreeView`  
_L16-183_
- inherits: `UE::Insights::STableTreeView`
- L23 _public prototype_ `SAssetTableTreeView();` — Default constructor.
- L26 _public prototype_ `virtual ~SAssetTableTreeView();` — Virtual destructor.
- L28 _public function_ `SLATE_BEGIN_ARGS(SAssetTableTreeView) : _OnSelectionChanged()`
- L32 _public prototype_ `SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FAssetTable> InTablePtr);`
- L42 _public prototype_ `virtual void ConstructHeaderArea(TSharedRef<SVerticalBox> InWidgetContent);`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> ConstructFooter() override;`
- L45 _public function_ `TSharedPtr<FAssetTable> GetAssetTable()`
- L46 _public function_ `const TSharedPtr<FAssetTable> GetAssetTable() const`
- L48 _public prototype_ `virtual void Reset();`
- L57 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Ticks this widget.  Override in derived classes, but always call the parent implementation. @param  AllottedGeometry The space allotted for this widget @param  InCurrentTime  Current absolute real time @param  InDeltaTime  Real time passed since last tick
- L63 _public prototype_ `virtual void RebuildTree(bool bResync);` — Rebuilds the tree (if necessary). @param bResync - If true, it forces a resync even if the list did not changed since last sync.
- L69 _public prototype_ `void SetFilterToName(const FString& Name);` — Sets the search filter to the given name (does not check if exists but UI is clear when no data matches filter) @param Name - Could be an asset name or a plugin name (any name in the tree really)
- L74 _public prototype_ `virtual bool IsRunning() const override;`
- L75 _public prototype_ `virtual double GetAllOperationsDuration() override;`
- L76 _public prototype_ `virtual FText GetCurrentOperationName() const override;`
- L81 _private prototype_ `void ExecuteFindInContentBrowserAction();`
- L82 _private prototype_ `bool CanExecuteFindInContentBrowserAction();`
- L96 _private prototype_ `virtual void InternalCreateGroupings() override;`
- L98 _private prototype_ `virtual void ExtendMenu(FMenuBuilder& MenuBuilder) override;`
- L100 _private prototype_ `void RequestOpenRegistry();`
- L101 _private prototype_ `void OpenRegistry();`
- L103 _private prototype_ `ECheckFilesExistAndHashMatchesResult CheckFilesExistAndHashMatches(const FString& MetadataFilename, const FString& RegistryFilename, UE::Cook::FCookMetadataState& MetadataTemporaryStorage);`
- L105 _private prototype_ `FText GetOpenRegistryToolTipText() const;`
- L106 _private prototype_ `bool CanChangeRegistry() const;`
- L107 _private prototype_ `FReply OnClickedOpenRegistry();`
- L109 _private prototype_ `FText GetFooterLeftText() const;`
- L110 _private prototype_ `FText GetFooterCenterText1() const;`
- L111 _private prototype_ `FText GetFooterCenterText2() const;`
- L112 _private prototype_ `FText GetFooterRightText1() const;`
- L114 _private prototype_ `virtual void TreeView_OnSelectionChanged(UE::Insights::FTableTreeNodePtr SelectedItem, ESelectInfo::Type SelectInfo) override;`
- L116 _private prototype_ `virtual TSharedRef<SWidget> ConstructSearchBox() override;`
- L118 _private prototype_ `void InitAvailableViewPresets();`
- L120 _private prototype_ `void ExportDependencyData() const;`
- L122 _private prototype_ `TArray<FAssetData> GetAssetDataForSelection() const;`
- L124 _private prototype_ `void CalculateBaseAndMarginalCostForSelection(TSet<int32>& SelectionSetIndices, int64* OutTotalSizeMultiplyUsed, int64* OutTotalSizeSingleUse) const;`
- L127 _private prototype_ `void QuickPopulateAssetTableRow(class FAssetTableRow& OutRow, const FAssetData& AssetData, class FAssetTable& AssetTable) const;` — Populates an asset table row (view model for the asset tree view) with asset data (only identification data; type+path+name).
- L130 _private prototype_ `void PopulateAssetTableRow(class FAssetTableRow& OutRow, const FAssetData& AssetData, class FAssetTable& AssetTable) const;` — Populates an asset table row (view model for the asset tree view) with asset data.
- L132 _private function_ `bool IsRegistrySourceValid() const`
- L134 _private prototype_ `void RequestRefreshAssets();`
- L135 _private prototype_ `void RefreshAssets();`
- L137 _private prototype_ `void ClearTableAndTree();`
- L139 _private typedef_ `typedef TSet<const TCHAR*, TStringPointerSetKeyFuncs_DEPRECATED<const TCHAR*>> DeprecatedTCharSetType;`
- L140 _private prototype_ `void DumpDifferencesBetweenDiscoveredDataAndLoadedMetadata(TMap<const TCHAR*, DeprecatedTCharSetType, FDefaultSetAllocator, TStringPointerMapKeyFuncs_DEPRECATED<const TCHAR*, DeprecatedTCharSetType>>& DiscoveredPluginDependencyEdges) const;`
- L142 _private prototype_ `void RequestRebuildTree(bool bNeedsColumnRebuild = false);`
- L144 _private prototype_ `void UpdateRegistryInfoTextPostLoad(ECheckFilesExistAndHashMatchesResult StatusResult);`
- L147 _private member_ `bool bNeedsToOpenRegistry = false;`
- L148 _private member_ `bool bNeedsToRefreshAssets = false;`
- L149 _private member_ `bool bNeedsToRebuild = false;`
- L150 _private member_ `bool bNeedsToRebuildColumns = false;`
- L152 _private member_ `FText FooterLeftTextStoredPreOpen;`
- L153 _private member_ `FText RegistryLoadedText;`
- L154 _private member_ `FText FooterLeftText;`
- L155 _private member_ `FText FooterCenterText1;`
- L156 _private member_ `FText FooterCenterText2;`
- L157 _private member_ `FText FooterRightText1;`
- L160 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate to invoke when selection changes.
- L161 _private member_ `TSet<int32> SelectedAssetIndices;`
- L162 _private member_ `TSet<int32> SelectedPluginIndices;`
- L165 _private member_ `TArray<TSharedPtr<FString>> SourceComboList;` — List of valid registry sources
- L168 _private member_ `TSharedPtr<SWidget> SearchBoxWidget;` — Used so we can set the search filter from code and have it reflected in the UI
- L174 _private member_ `TSharedPtr<STextBlock> RegistryInfoText;` — Text block where we put the timestamp for the asset registry so the user knows if they are looking at super out of date data.
- L176 _private member_ `FAssetManagerEditorRegistrySource RegistrySource;`
- L178 _private member_ `UE::Cook::FCookMetadataState CookMetadata;`
- L181 _private member_ `class UAssetManager* AssetManager;` — Cached interfaces
- L182 _private member_ `class IAssetManagerEditorModule* EditorModule;`

#### enum `SAssetTableTreeView::ECheckFilesExistAndHashMatchesResult`  
`enum class ECheckFilesExistAndHashMatchesResult : uint8`  
_L84-94_
- L86 _public enumerator_ `Okay`
- L87 _public enumerator_ `RegistryDoesNotExist`
- L88 _public enumerator_ `CookMetadataDoesNotExist`
- L89 _public enumerator_ `FailedToHashRegistry`
- L90 _public enumerator_ `FailedToLoadCookMetadata`
- L91 _public enumerator_ `FailedToLoadRegistry`
- L92 _public enumerator_ `HashesDoNotMatch`
- L93 _public enumerator_ `Unknown`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, const TArray<TSharedPtr<UE::Insights::FTableTreeNode>>) public: SAssetTableTreeView();`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Public/AssetManagerEditorModule.h` (Public)


#### struct `FAssetManagerDependencyQuery`  
`struct FAssetManagerDependencyQuery`  
_L23-45_
- desc: AssetRegistry Dependency Category + QueryFlags, to pass around the two enums in a single variable.
- L25 _public member_ `UE::AssetRegistry::EDependencyCategory Categories = UE::AssetRegistry::EDependencyCategory::All;`
- L26 _public member_ `UE::AssetRegistry::EDependencyQuery Flags = UE::AssetRegistry::EDependencyQuery::NoRequirements;`
- L28 _public function_ `bool IsNone() const`
- L33 _public prototype_ `FAssetManagerDependencyQuery() = default;`
- L35 _public function_ `static FAssetManagerDependencyQuery All()`
- L39 _public function_ `static FAssetManagerDependencyQuery None()`

#### struct `FAssetManagerEditorRegistrySource`  
`struct FAssetManagerEditorRegistrySource`  
_L58-358_
- desc: Struct containing the information about currently investigated asset context
- L61 _public member_ `FString SourceName;` — Display name of the source, equal to target Platform, Editor, or Custom
- L64 _public member_ `FString SourceFilename;` — Filename registry was loaded from
- L70 _public member_ `FString SourceTimestamp;` — Timestamp for the registry we loaded from, if from a file. Modified time if the OS supports it, otherwise creation time. If we can't get anything or not from a file, empty string. In local timezone.
- L73 _public member_ `ITargetPlatform* TargetPlatform;` — Target platform for this state, may be null
- L77 _private member_ `const FAssetRegistryState* RegistryStatePrivate;` — Raw asset registry state, only valid if bIsEditor is false
- L78 _private member_ `FPathTree CachedRegistryStatePathTree;`
- L80 _private member_ `const IAssetRegistry* AssetRegistryPrivate;` — Pointer to the real AssetRegistry, only valid if bIsEditor is true
- L84 _public member_ `uint8 bIsEditor : 1;` — If true, this is the editor
- L87 _public member_ `uint8 bManagementDataInitialized : 1;` — If true, management data has been initialized
- L90 _public member_ `TMap<int32, FAssetManagerChunkInfo> ChunkAssignments;` — Map of chunk information, from chunk id to primary assets/specific assets that are explicitly assigned to that chunk
- L93 _public member_ `static const FString EditorSourceName;` — If SourceName matches this, this is the editor
- L96 _public member_ `static const FString CustomSourceName;` — If SourceName matches this, this is the custom source loaded from an arbitrary path
- L98 _public function_ `FAssetManagerEditorRegistrySource() : TargetPlatform(nullptr) , RegistryStatePrivate(nullptr) , AssetRegistryPrivate(nullptr) , bIsEditor(false) , bManagementDataInitialized(false)`
- L107 _public function_ `~FAssetManagerEditorRegistrySource()`
- L113 _public prototype_ `FAssetManagerEditorRegistrySource(const FAssetManagerEditorRegistrySource& Other) = delete;` — We delete the copy constructor because it's not clear whether we should copy RegistryStatePrivate
- L114 _public prototype_ `FAssetManagerEditorRegistrySource& operator=(const FAssetManagerEditorRegistrySource& Other) = delete;`
- L116 _public function_ `FAssetManagerEditorRegistrySource& operator=(FAssetManagerEditorRegistrySource&& Other)`
- L143 _public function_ `FAssetManagerEditorRegistrySource(FAssetManagerEditorRegistrySource&& Other) :FAssetManagerEditorRegistrySource()`
- L150 _public function_ `const FAssetRegistryState* GetOwnedRegistryState() const` — Returns the RegistryState owned by this. Will be null if this does not have a Registry or is using the global editor Registry
- L164 _public function_ `void SetRegistryState(const FAssetRegistryState* InRegistryState)` — Set the RegistryState viewed by this FAssetManagerEditorRegistrySource to a dynamically allocated FAssetRegistryState FAssetManagerEditorRegistrySource takes ownership of the given AssetRegistry and deletes it is when cleared. Do not call with  AssetRegistry->GetAssetRegistryState; use SetUseEditorAssetRegistry(AssetRegistry) instead.
- L184 _public function_ `void SetUseEditorAssetRegistry(const IAssetRegistry* AssetRegistry)` — Set the RegistryState viewed by this FAssetManagerEditorRegistrySource to the FAssetRegistryState owned by the given global AssetRegistry.
- L195 _public function_ `bool HasRegistry() const`
- L200 _public function_ `void ClearRegistry()`
- L213 _public prototype_ `void LoadRegistryTimestamp();` — grabs the SourceTimestamp from the asset registry file changed times.
- L216 _public function_ `FAssetData GetAssetByPackageName(FName PackageName) const` — Functions to forward on to the RegistryState, either the owned one or the editor's global State.
- L232 _public function_ `FAssetData GetAssetByObjectPath(const FSoftObjectPath& ObjectPath) const`
- L250 _public function_ `template <typename ValueType> bool GetAssetTagByObjectPath(const FSoftObjectPath& InObjectPath, FName InTagName, ValueType& OutTagValue) const`
- L268 _public function_ `bool GetDependencies(const FAssetIdentifier& AssetIdentifier, TArray<FAssetIdentifier>& OutDependencies, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const`
- L286 _public function_ `bool GetReferencers(const FAssetIdentifier& AssetIdentifier, TArray<FAssetIdentifier>& OutReferencers, UE::AssetRegistry::EDependencyCategory Category = UE::AssetRegistry::EDependencyCategory::All, const UE::AssetRegistry::FDependencyQuery& Flags = UE::AssetRegistry::FDependencyQuery()) const`
- L304 _public function_ `TOptional<FAssetPackageData> GetAssetPackageDataCopy(FName PackageName) const`
- L321 _public function_ `bool GetAssets(const FARFilter& Filter, TArray<FAssetData>& OutAssets) const`

#### class `IAssetManagerEditorModule`  
`class IAssetManagerEditorModule : public IModuleInterface`  
_L363-542_
- inherits: `IModuleInterface`
- desc: The Asset Manager Editor module handles creating UI for asset management and exposes several commands
- L384 _public function_ `static inline IAssetManagerEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L394 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L406 _public prototype_ `static TSharedRef<SWidget> MakePrimaryAssetTypeSelector(FOnGetPrimaryAssetDisplayText OnGetDisplayText, FOnSetPrimaryAssetType OnSetType, bool bAllowClear = true, bool bAllowAll = false);` — Creates a simple version of a Primary Asset Type selector, not bound to a PropertyHandle @param OnGetDisplayText Delegate that returns the text to display in body of combo box @param OnSetType Delegate called when type is changed @param bAllowClear If true, add None option to top @param bAlowAll If true, add All Types option to bottom, returns AllPrimaryAssetTypes if selected
- L414 _public prototype_ `static TSharedRef<SWidget> MakePrimaryAssetIdSelector(FOnGetPrimaryAssetDisplayText OnGetDisplayText, FOnSetPrimaryAssetId OnSetId, bool bAllowClear = true, TArray<FPrimaryAssetType> AllowedTypes = TArray<FPrimaryAssetType>(), TArray<const UClass*> AllowedClasses = TArray<const UClass*>(), TArray<const UClass*> DisallowedClasses = TArray<const UClass*>() );` — Creates a simple version of a Primary Asset Id selector, not bound to a PropertyHandle @param OnGetDisplayText Delegate that returns the text to display in body of combo box @param OnSetId Delegate called when id is changed @param bAllowClear If true, add None option to top
- L422 _public prototype_ `static TSharedRef<SWidget> MakePrimaryAssetIdSelector(FPrimaryAssetIdSelectorArgs PrimaryAssetIdSelectorArgs);` — Creates a simple version of a Primary Asset Id selector, not bound to a PropertyHandle @param PrimaryAssetIdSelectorArgs struct of arguments to build the PrimaryAssetIdSelector
- L425 _public prototype_ `static void GeneratePrimaryAssetTypeComboBoxStrings(TArray< TSharedPtr<FString> >& OutComboBoxStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems, bool bAllowClear, bool bAllowAll);` — Called to get list of valid primary asset types
- L428 _public prototype_ `static bool OnShouldFilterPrimaryAsset(const FAssetData& InAssetData, TArray<FPrimaryAssetType> AllowedTypes);` — Called for asset picker to see rather to show asset
- L431 _public prototype_ `static FAssetData CreateFakeAssetDataFromChunkId(int32 ChunkID);` — Creates fake AssetData to represent chunks
- L434 _public prototype_ `static int32 ExtractChunkIdFromFakeAssetData(const FAssetData& InAssetData);` — Returns >= 0 if this is a fake chunk AssetData, otherwise INDEX_NONE
- L437 _public prototype_ `static FAssetData CreateFakeAssetDataFromPrimaryAssetId(const FPrimaryAssetId& PrimaryAssetId);` — Creates fake AssetData to represent a primary asset
- L440 _public prototype_ `static FPrimaryAssetId ExtractPrimaryAssetIdFromFakeAssetData(const FAssetData& InAssetData);` — Returns valid PrimaryAssetId if this is a fake AssetData for a primary asset
- L443 _public prototype_ `static void ExtractAssetIdentifiersFromAssetDataList(const TArray<FAssetData>& AssetDataList, TArray<FAssetIdentifier>& OutAssetIdentifiers);` — Parses a list of AssetData and extracts AssetIdentifiers, handles the fake asset data
- L446 _public member_ `static const FName PrimaryAssetFakeAssetDataPackagePath;` — Fake package path used by placeholder asset data, has primary asset ID added to it to set package name
- L449 _public member_ `static const FName ChunkFakeAssetDataPackageName;` — Specific package path inside PrimaryAssetFakeAssetDataPackagePath representing chunks
- L452 _public member_ `static const FPrimaryAssetType AllPrimaryAssetTypes;` — Fake type returned from type combo box to mean all types
- L455 _public member_ `static const FName ResourceSizeName;` — Custom column names
- L456 _public member_ `static const FName DiskSizeName;`
- L457 _public member_ `static const FName ManagedResourceSizeName;`
- L458 _public member_ `static const FName ManagedDiskSizeName;`
- L459 _public member_ `static const FName TotalUsageName;`
- L460 _public member_ `static const FName CookRuleName;`
- L461 _public member_ `static const FName ChunksName;`
- L462 _public member_ `static const FName PluginName;`
- L465 _public prototype_ `virtual bool GetStringValueForCustomColumn(const FAssetData& AssetData, FName ColumnName, FString& OutValue, const FAssetManagerEditorRegistrySource* OverrideRegistrySource = nullptr) = 0;` — Gets the value of a "virtual" column for an asset data, this will query the AssetManager for you and takes current platform into account. Returns true and sets out parameter if found
- L468 _public prototype_ `virtual bool GetDisplayTextForCustomColumn(const FAssetData& AssetData, FName ColumnName, FText& OutValue, const FAssetManagerEditorRegistrySource* OverrideRegistrySource = nullptr) = 0;` — Gets a display text value for a virtual column. Returns true and sets out parameter if found
- L471 _public prototype_ `virtual bool GetIntegerValueForCustomColumn(const FAssetData& AssetData, FName ColumnName, int64& OutValue, const FAssetManagerEditorRegistrySource* OverrideRegistrySource = nullptr) = 0;` — Gets the value of a "virtual" column for an asset data, this will query the AssetManager for you and takes current platform into account. Returns true and sets out parameter if found
- L474 _public prototype_ `virtual bool GetManagedPackageListForAssetData(const FAssetData& AssetData, TSet<FName>& ManagedPackageSet) = 0;` — Returns the set of asset packages managed the given asset data, returns true if any found. This handles the fake chunk/primary asset types above
- L477 _public prototype_ `virtual void GetAvailableRegistrySources(TArray<const FAssetManagerEditorRegistrySource*>& AvailableSources) = 0;` — Gets the list of registry sources that are available
- L480 _public prototype_ `virtual const FAssetManagerEditorRegistrySource* GetCurrentRegistrySource(bool bNeedManagementData = false) = 0;` — Returns the currently selected registry source. If bNeedManagementData is set it it will cache the chunk/management information
- L483 _public prototype_ `virtual void SetCurrentRegistrySource(const FString& SourceName) = 0;` — Sets the current registry source, this loads the asset registry state if needed and may spawn a file load dialog for custom
- L486 _public prototype_ `virtual bool PopulateRegistrySource(FAssetManagerEditorRegistrySource* InOutRegistrySource, const FString* OptInFilePath = nullptr) = 0;` — Sets up a registry source. If InOutRegistrySource->SourceName is CustomSourceName, a dialog will be presented to select the asset registry to load. If OptInFilePath is provided, it will be used instead of opening a dialog.
- L489 _public prototype_ `virtual void RefreshRegistryData() = 0;` — Refreshes the management dictionary and all sources
- L492 _public prototype_ `virtual bool IsPackageInCurrentRegistrySource(FName PackageName) = 0;` — Returns true if this package exists in the current registry source, optionally setting a redirected package name
- L495 _public prototype_ `virtual bool FilterAssetIdentifiersForCurrentRegistrySource(TArray<FAssetIdentifier>& AssetIdentifiers, const FAssetManagerDependencyQuery& DependencyQuery = FAssetManagerDependencyQuery::None(), bool bForwardDependency = true) = 0;` — Filters list of identifiers and removes ones that do not exist in this registry source. Handles replacing redirectors as well
- L499 _public prototype_ `virtual bool WriteCollection(FName CollectionName, ECollectionShareType::Type ShareType, const TArray<FName>& PackageNames, bool bShowFeedback = true) = 0;` — `UE_DEPRECATED(5.6, "Use the ICollectionContainer overload instead.")` — Creates a collection in the project collection container from a list of packages, will overwrite/modify an existing collection of the same name. Will display feedback to the user if bShowFeedback is true
- L502 _public prototype_ `virtual bool WriteCollection(ICollectionContainer& CollectionContainer, FName CollectionName, ECollectionShareType::Type ShareType, const TArray<FName>& PackageNames, bool bShowFeedback = true) = 0;` — Creates a collection from a list of packages, will overwrite/modify an existing collection of the same name. Will display feedback to the user if bShowFeedback is true
- L505 _public prototype_ `virtual void OpenAssetAuditUI(TArray<FAssetData> SelectedAssets) = 0;` — Opens asset management UI, with selected assets. Pass as value so it can be used in delegates
- L506 _public prototype_ `virtual void OpenAssetAuditUI(TArray<FAssetIdentifier> SelectedIdentifiers) = 0;`
- L507 _public prototype_ `virtual void OpenAssetAuditUI(TArray<FName> SelectedPackages) = 0;`
- L510 _public prototype_ `virtual void OpenReferenceViewerUI(const TArray<FAssetIdentifier> SelectedIdentifiers, const FReferenceViewerParams ReferenceViewerParams = FReferenceViewerParams()) = 0;` — Spawns reference viewer, showing selected packages or identifiers
- L511 _public prototype_ `virtual void OpenReferenceViewerUI(const TArray<FName> SelectedPackages, const FReferenceViewerParams ReferenceViewerParams = FReferenceViewerParams()) = 0;`
- L514 _public prototype_ `virtual bool GetReferenceViewerUISelectedNodesAssetData(TArray<FAssetData>& OutAssetDatas) = 0;` — Returns true if Reference Viewer UI is available and has selected nodes. If true, will also append the asset data for the selected nodes into the passed array
- L517 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanOpenReferenceViewerUI, const TArray<FAssetIdentifier>&, FText*);` — Returns false if should not open reference viewer for items
- L518 _public prototype_ `virtual FCanOpenReferenceViewerUI& OnCanOpenReferenceViewerUI() = 0;`
- L521 _public prototype_ `virtual void OpenSizeMapUI(TArray<FAssetIdentifier> SelectedIdentifiers) = 0;` — Spawns size map with selected packages
- L522 _public prototype_ `virtual void OpenSizeMapUI(TArray<FName> SelectedPackages) = 0;`
- L525 _public prototype_ `virtual void OpenShaderCookStatistics(TArray<FName> SelectedIdentifiers) = 0;` — Open the Shader cook stats
- L528 _public prototype_ `virtual void OpenAssetSizeTreeViewUI(const FString& SearchTerm) = 0;` — Open the Asset Disk Size Tree View
- L531 _public prototype_ `virtual void AppendRegisteredCommandsToCommandList(TSharedRef<FUICommandList> ListToAppendTo) = 0;` — Called by SReferenceViewer to update given list of commands with any of the registered delegates
- L534 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRegisterAdditionalReferenceViewerCommands, TSharedRef<FUICommandList>, TArray<TSharedPtr<FUICommandInfo>>&);` — Passes commandlist and command info array to be updated by any of the registered delegates. Broadcast from AppendRegisteredCommandsToCommandList
- L535 _public prototype_ `virtual FRegisterAdditionalReferenceViewerCommands &OnRegisterAdditionalReferenceViewerCommands() = 0;`
- L538 _public prototype_ `virtual const TArray<TSharedPtr<FUICommandInfo>>& GetRegisteredAdditionalReferenceViewerCommands() = 0;` — Returns our list of command info populated by OnRegisterAdditionalReferenceViewerCommands. Needed to be tracked separately from command list to populate commands in menu ui
- L541 _public prototype_ `virtual TSharedRef<SWidget> CreateAssetSourceControlContextMenu(const TArray<FAssetData>& SelectedAssets) = 0;` — Return a UToolsMenu generated widget containing the asset source control context menu.

#### struct `IAssetManagerEditorModule::FPrimaryAssetIdSelectorArgs`  
`struct FPrimaryAssetIdSelectorArgs`  
_L366-375_
- L368 _public member_ `FOnGetPrimaryAssetDisplayText OnGetDisplayText;`
- L369 _public member_ `FOnGetPrimaryAssetDisplayText OnGetTooltipText;`
- L370 _public member_ `FOnSetPrimaryAssetId OnSetId;`
- L371 _public member_ `bool bAllowClear = true;`
- L372 _public member_ `TArray<FPrimaryAssetType> AllowedTypes;`
- L373 _public member_ `TArray<const UClass*> AllowedClasses;`
- L374 _public member_ `TArray<const UClass*> DisallowedClasses;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API ASSETMANAGEREDITOR_API`
- L47 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetManagerEditor, Log, All);`
- L47 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAssetManagerEditor, Log, All);`
- L49 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FOnGetPrimaryAssetDisplayText);`
- L49 _prototype_ `DECLARE_DELEGATE_RetVal(FText, FOnGetPrimaryAssetDisplayText);`
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetPrimaryAssetType, FPrimaryAssetType);`
- L50 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetPrimaryAssetType, FPrimaryAssetType);`
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetPrimaryAssetId, FPrimaryAssetId);`
- L51 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetPrimaryAssetId, FPrimaryAssetId);`
- L174 _function_ `` (scope `FAssetManagerEditorRegistrySource::SetRegistryState`)
- L175 _function_ `CachedRegistryStatePathTree.CachePath(Path, [](FName AddedPath) {});` (scope `FAssetManagerEditorRegistrySource::SetRegistryState::__anone23befab0102`)
- L517 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanOpenReferenceViewerUI, const TArray<FAssetIdentifier>&, FText*);` — Returns false if should not open reference viewer for items
- L534 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FRegisterAdditionalReferenceViewerCommands, TSharedRef<FUICommandList>, TArray<TSharedPtr<FUICommandInfo>>&);` — Passes commandlist and command info array to be updated by any of the registered delegates. Broadcast from AppendRegisteredCommandsToCommandList

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Public/ReferenceViewer/EdGraphNode_Reference.h` (Public)


#### class `UEdGraphNode_Reference`  
`class UEdGraphNode_Reference : public UEdGraphNode`  
_L17-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L22 _private prototype_ `FAssetIdentifier GetIdentifier() const;` — Returns first asset identifier
- L25 _private prototype_ `void GetAllIdentifiers(TArray<FAssetIdentifier>& OutIdentifiers) const;` — Returns all identifiers on this node including virtual things
- L28 _private prototype_ `void GetAllPackageNames(TArray<FName>& OutPackageNames) const;` — Returns only the packages in this node, skips searchable names
- L31 _private prototype_ `UEdGraph_ReferenceViewer* GetReferenceViewerGraph() const;` — Returns our owning graph
- L34 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode implementation
- L35 _private prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L36 _private prototype_ `virtual FText GetTooltipText() const override;`
- L37 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L38 _private prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L39 _private prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L40 _private function_ `virtual bool ShowPaletteIconOnNode() const override`
- L43 _private function_ `void SetAllowThumbnail(bool bInAllow)`
- L44 _private prototype_ `bool AllowsThumbnail() const;`
- L45 _private prototype_ `bool UsesThumbnail() const;`
- L46 _private prototype_ `bool IsPackage() const;`
- L47 _private prototype_ `bool IsCollapsed() const;`
- L48 _private function_ `bool IsADuplicate() const`
- L53 _private prototype_ `void SetIsFiltered(bool bInFiltered);` — Nodes that are filtered out still may still show because they are between nodes that pass the filter and the root.  This "filtered" bool allows us to render these in-between nodes differently
- L54 _private prototype_ `bool GetIsFiltered() const;`
- L56 _private function_ `bool IsOverflow() const`
- L58 _private prototype_ `const FAssetData& GetAssetData() const;`
- L60 _private prototype_ `UEdGraphPin* GetDependencyPin();`
- L61 _private prototype_ `UEdGraphPin* GetReferencerPin();`
- L63 _private prototype_ `UE_INTERNAL void UpdatePath();`
- L66 _private prototype_ `void CacheAssetData(const FAssetData& AssetData);`
- L67 _private prototype_ `void SetupReferenceNode(const FIntPoint& NodeLoc, const TArray<FAssetIdentifier>& NewIdentifiers, const FAssetData& InAssetData, bool bInAllowThumbnail, bool bInIsADuplicate);`
- L68 _private prototype_ `void SetReferenceNodeCollapsed(const FIntPoint& NodeLoc, int32 InNumReferencesExceedingMax, const TArray<FAssetIdentifier>& Identifiers);`
- L69 _private prototype_ `void AddReferencer(class UEdGraphNode_Reference* ReferencerNode);`
- L71 _private member_ `TArray<FAssetIdentifier> Identifiers;`
- L72 _private member_ `FText NodeTitle;`
- L74 _private member_ `bool bAllowThumbnail;`
- L75 _private member_ `bool bUsesThumbnail;`
- L76 _private member_ `bool bIsPackage;`
- L77 _private member_ `bool bIsPrimaryAsset;`
- L78 _private member_ `bool bIsCollapsed;`
- L79 _private member_ `bool bIsADuplicate;`
- L80 _private member_ `bool bIsFiltered;`
- L81 _private member_ `bool bIsOverflow;`
- L83 _private member_ `FAssetData CachedAssetData;`
- L84 _private member_ `FLinearColor AssetTypeColor;`
- L85 _private member_ `FSlateIcon AssetBrush;`
- L87 _private member_ `UEdGraphPin* DependencyPin;`
- L88 _private member_ `UEdGraphPin* ReferencerPin;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ASSETMANAGEREDITOR_API`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Public/ReferenceViewer/EdGraphNode_ReferencedProperties.h` (Public)


#### struct `FReferencingPropertyDescription`  
`struct FReferencingPropertyDescription`  
_L15-87_
- desc: Describes a graph node property referencing an asset from another node
- L28 _public prototype_ `static TSharedRef<FReferencingPropertyDescription> MakeSharedPropertyDescription( const FReferencingPropertyDescription& InPropertyDescription );`
- L32 _public function_ `FReferencingPropertyDescription(const FString& InName, const FString& InReferencerName, const FString& InReferencedNodeName, const EAssetReferenceType& InType, const UClass* InClass, bool bInIsIndirect = false) : Name(InName), ReferencerName(InReferencerName), ReferencedNodeName(InReferencedNodeName), Type(InType), PropertyClass(InClass), bIsIndirectReference(bInIsIndirect)`
- L42 _public function_ `bool operator==(const FReferencingPropertyDescription& InOther) const`
- L50 _public function_ `const FString& GetName() const` — Returns the name of the property
- L53 _public function_ `const FString& GetReferencerName() const` — Returns the name of the property referencer
- L56 _public function_ `const FString& GetReferencedNodeName() const` — Returns the name of the referenced node
- L59 _public function_ `EAssetReferenceType GetType() const` — Returns the property type
- L62 _public prototype_ `FString GetTypeAsString() const;` — Returns the property type as a string (useful e.g. for tooltips)
- L64 _public function_ `const UClass* GetPropertyClass() const`
- L74 _public function_ `bool IsIndirect() const`
- L78 _private prototype_ `FReferencingPropertyDescription() = default;`
- L80 _private member_ `FString Name;`
- L81 _private member_ `FString ReferencerName;`
- L82 _private member_ `FString ReferencedNodeName;`
- L83 _private member_ `EAssetReferenceType Type = EAssetReferenceType::None;`
- L85 _private member_ `TWeakObjectPtr<const UClass> PropertyClass = nullptr;`
- L86 _private member_ `bool bIsIndirectReference = false;`

#### enum `FReferencingPropertyDescription::EAssetReferenceType`  
`enum class EAssetReferenceType : uint8`  
_L17-26_
- L20 _public enumerator_ `Component` — Reference comes from a BP Component Type
- L22 _public enumerator_ `Property` — Reference comes from a BP Variable Type
- L24 _public enumerator_ `Value` — Reference comes from a BP Variable property Value
- L25 _public enumerator_ `None`

#### class `UEdGraphNode_ReferencedProperties`  
`class UEdGraphNode_ReferencedProperties : public UEdGraphNode`  
_L94-135_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- desc: A node to display a list of Node properties which are referencing another Node/Asset
- L99 _public function_ `const TArray<FReferencingPropertyDescriptionPtr>& GetReferencedPropertiesDescription() const`
- L104 _public function_ `const TObjectPtr<UEdGraphNode_Reference>& GetReferencingNode() const`
- L106 _public function_ `const TObjectPtr<UEdGraphNode_Reference>& GetReferencedNode() const`
- L108 _public prototype_ `UObject* GetReferencingObject() const;`
- L110 _public prototype_ `UObject* GetReferencedObject() const;`
- L113 _public prototype_ `void SetupReferencedPropertiesNode(const TArray<FReferencingPropertyDescription>& InPropertiesDescription , const TObjectPtr<UEdGraphNode_Reference>& InReferencingNode, const TObjectPtr<UEdGraphNode_Reference>& InReferencedNode);` — Initialize this Node
- L120 _public prototype_ `void RefreshLocation(const FVector2f& InNodeSize = FVector2f::Zero());` — Refresh the node location, so it stays mid-way between Referencing and Referenced nodes @param InNodeSize: size of the widget representing this node. Useful when centering
- L122 _public function_ `DECLARE_MULTICAST_DELEGATE(FOnPropertiesDescriptionUpdated) FOnPropertiesDescriptionUpdated& OnPropertiesDescriptionUpdated()`
- L126 _private member_ `TArray<FReferencingPropertyDescriptionPtr> ReferencedPropertyDescription;`
- L129 _private member_ `TObjectPtr<UEdGraphNode_Reference> ReferencingNode;` — `UPROPERTY()`
- L132 _private member_ `TObjectPtr<UEdGraphNode_Reference> ReferencedNode;` — `UPROPERTY()`
- L134 _private member_ `FOnPropertiesDescriptionUpdated OnPropertiesDescriptionUpdatedDelegate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ASSETMANAGEREDITOR_API`
- L88 _typedef_ `using FReferencingPropertyDescriptionPtr = TSharedPtr<FReferencingPropertyDescription>;`
- L122 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPropertiesDescriptionUpdated) FOnPropertiesDescriptionUpdated& OnPropertiesDescriptionUpdated() { return OnPropertiesDescriptionUpdatedDelegate; } private: TArray<FReferencingPropertyDescriptionPtr> ReferencedPropertyDescription;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Public/ReferenceViewer/EdGraph_ReferenceViewer.h` (Public)


#### struct `FReferenceNodeInfo`  
`struct FReferenceNodeInfo`  
_L27-68_
- desc: Holds asset information for building reference graph
- L29 _public member_ `FAssetIdentifier AssetId;`
- L31 _public member_ `FAssetData AssetData;`
- L34 _public member_ `TArray<TPair<FAssetIdentifier, EDependencyPinCategory>> Children;` — immediate children (references or dependencies)
- L37 _public member_ `TArray<FAssetIdentifier> Parents;` — this node's parent references (how it got included)
- L40 _public member_ `bool bReferencers;` — Which direction.  Referencers are left (other assets that depend on me), Dependencies are right (other assets I depend on)
- L42 _public member_ `bool bIsRedirector;`
- L44 _public member_ `int32 OverflowCount;`
- L47 _public member_ `bool bExpandAllChildren;` — Denote when all children have been manually expanded and the breadth limit should be ignored
- L49 _public prototype_ `FReferenceNodeInfo(const FAssetIdentifier& InAssetId, bool InbReferencers);`
- L51 _public prototype_ `bool IsFirstParent(const FAssetIdentifier& InParentId) const;`
- L53 _public prototype_ `bool IsRedirector() const;`
- L55 _public prototype_ `bool IsADuplicate() const;`
- L60 _public prototype_ `int32 ProvisionSize(const FAssetIdentifier& InParentId) const;` — The Provision Size, or vertical spacing required for layout, for a given parent. At the time of writing, the intent is only the first node manifestation of an asset will have its children shown
- L63 _public member_ `int32 ChildProvisionSize;` — how many nodes worth of children require vertical spacing
- L66 _public member_ `bool PassedFilters;` — Whether or not this nodeinfo passed the current filters

#### class `UEdGraph_ReferenceViewer`  
`class UEdGraph_ReferenceViewer : public UEdGraph`  
_L73-264_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L79 _public prototype_ `virtual void BeginDestroy() override;` — UObject implementation
- L83 _public prototype_ `void SetGraphRoot(const TArray<FAssetIdentifier>& GraphRootIdentifiers, const FIntPoint& GraphRootOrigin = FIntPoint(ForceInitToZero));` — Set reference viewer to focus on these assets
- L86 _public prototype_ `const TArray<FAssetIdentifier>& GetCurrentGraphRootIdentifiers() const;` — Returns list of currently focused assets
- L89 _public prototype_ `bool GetSelectedAssetsForMenuExtender(const class UEdGraphNode* Node, TArray<FAssetIdentifier>& SelectedAssets) const;` — If you're extending the reference viewer via GetAllGraphEditorContextMenuExtender you can use this to get the list of selected assets to use in your menu extender
- L92 _public prototype_ `const TSharedPtr<class FAssetThumbnailPool>& GetAssetThumbnailPool() const;` — Accessor for the thumbnail pool in this graph
- L95 _public prototype_ `class UEdGraphNode_Reference* RebuildGraph();` — Force the graph to rebuild
- L99 _public prototype_ `class UEdGraphNode_Reference* RefilterGraph();` — Refilters the nodes, more efficient that a full rebuild.  This function is preferred when the assets, reference types or depth hasn't changed, meaning the NodeInfos didn't change, just the presentation or filtering
- L101 _public function_ `UE_INTERNAL bool IsShowingContentVersePath() const`
- L102 _public prototype_ `UE_INTERNAL void SetShowingContentVersePath(bool bInShowingContentVersePath);`
- L103 _public prototype_ `UE_INTERNAL void UpdatePaths();`
- L105 _public typedef_ `using FIsAssetIdentifierPassingSearchFilterCallback = TFunction<bool(const FAssetIdentifier&)>;`
- L107 _public prototype_ `void SetIsAssetIdentifierPassingSearchFilterCallback(const TOptional<FIsAssetIdentifierPassingSearchFilterCallback>& InIsAssetIdentifierPassingSearchFilterCallback);` — `UE_DEPRECATED(5.7, "Call SetDoesAssetPassSearchFilterCallback instead.")`
- L109 _public typedef_ `using FDoesAssetPassSearchFilterCallback = TFunction<bool(const FAssetIdentifier&, const FAssetData&)>;`
- L110 _public function_ `void SetDoesAssetPassSearchFilterCallback(const FDoesAssetPassSearchFilterCallback& InDoesAssetPassSearchFilterCallback)`
- L113 _public prototype_ `FName GetCurrentCollectionFilter() const;` — `UE_DEPRECATED(5.6, "Use the ICollectionContainer overload instead.")`
- L114 _public prototype_ `void GetCurrentCollectionFilter(ICollectionContainer*& OutCollectionContainer, FName& OutCollectionName) const;`
- L117 _public prototype_ `void SetCurrentCollectionFilter(FName NewFilter);` — `UE_DEPRECATED(5.6, "Use the ICollectionContainer overload instead.")`
- L118 _public prototype_ `void SetCurrentCollectionFilter(const TSharedPtr<ICollectionContainer>& CollectionContainer, FName CollectionName);`
- L120 _public prototype_ `TArray<FName> GetCurrentPluginFilter() const;`
- L121 _public prototype_ `void SetCurrentPluginFilter(TArray<FName> NewFilter);`
- L122 _public prototype_ `TArray<FName> GetEncounteredPluginsAmongNodes() const;`
- L125 _public function_ `FSimpleMulticastDelegate& OnAssetsChanged()` — Delegate type to notify when the assets or NodeInfos have changed as opposed to when the filters changed
- L128 _public prototype_ `void SetCurrentFilterCollection(TSharedPtr< TFilterCollection<FReferenceNodeInfo&> > NewFilterCollection);` — Not to be confused with the above Content Browser Collection name, this is a TFiltercollection, a list of active filters
- L131 _public function_ `const TSet<FTopLevelAssetPath>& GetAssetTypes() const` — Returns a set of unique asset types as UClass*
- L134 _public function_ `bool BreadthLimitExceeded() const` — Returns true if the current graph has overflow nodes
- L137 _public prototype_ `void RefreshReferencedPropertiesNodes();` — Refreshes the information of existing Referenced Properties Nodes
- L140 _public prototype_ `void CloseReferencedPropertiesNode(UEdGraphNode_ReferencedProperties* InNode);` — Closes (removes) the specified Referenced Properties Node
- L150 _private prototype_ `TArray<FReferencingPropertyDescription> RetrieveReferencingProperties(UObject* InReferencer, UObject* InReferencedAsset);` — Retrieves the list of properties/values of a specified Referencer Object which reference the specified Referenced Asset @param InReferencer: the Object referencing the Asset @param InReferencedAsset: the asset referenced by the specified Object @return the list of properties of the input Referencer, referencing the specified Asset.
- L152 _private prototype_ `TWeakPtr<SReferenceViewer> GetReferenceViewer() const;`
- L153 _private prototype_ `void SetReferenceViewer(TSharedPtr<SReferenceViewer> InViewer);`
- L154 _private prototype_ `UEdGraphNode_Reference* ConstructNodes(const TArray<FAssetIdentifier>& GraphRootIdentifiers, const FIntPoint& GraphRootOrigin);`
- L157 _private prototype_ `bool ExceedsMaxSearchDepth(int32 Depth, int32 MaxDepth) const;`
- L158 _private prototype_ `bool ExceedsMaxSearchBreadth(int32 Breadth) const;`
- L159 _private prototype_ `FAssetManagerDependencyQuery GetReferenceSearchFlags(bool bHardOnly) const;`
- L161 _private prototype_ `UEdGraphNode_Reference* CreateReferenceNode();`
- L163 _private prototype_ `UEdGraphNode_ReferencedProperties* CreateReferencedPropertiesNode(const TArray<FReferencingPropertyDescription>& InPropertiesDescriptionArray , const TObjectPtr<UEdGraphNode_Reference>& InReferencingNode, const TObjectPtr<UEdGraphNode_Reference>& InReferencedNode);`
- L167 _private prototype_ `void RecursivelyPopulateNodeInfos(bool bReferencers, const TArray<FAssetIdentifier>& Identifiers, TMap<FAssetIdentifier, FReferenceNodeInfo>& NodeInfos, int32 CurrentDepth, int32 MaxDepth);` — Generates a NodeInfo structure then used to generate and layout the graph nodes
- L170 _private prototype_ `void RecursivelyFilterNodeInfos(const FAssetIdentifier& InAssetId, TMap<FAssetIdentifier, FReferenceNodeInfo>& NodeInfos, int32 CurrentDepth, int32 MaxDepth);` — Marks up the NodeInfos with updated filter information and provision sizes
- L173 _private prototype_ `void GatherAssetData(TMap<FAssetIdentifier, FReferenceNodeInfo>& InNodeInfos);` — Searches for the AssetData for the list of packages derived from the AssetReferences
- L176 _private prototype_ `UEdGraphNode_Reference* RecursivelyCreateNodes( bool bInReferencers, const FAssetIdentifier& InAssetId, const FIntPoint& InNodeLoc, const FAssetIdentifier& InParentId, UEdGraphNode_Reference* InParentNode, TMap<FAssetIdentifier, FReferenceNodeInfo>& InNodeInfos, int32 InCurrentDepth, int32 InMaxDepth, bool bIsRoot = false );` — Uses the NodeInfos map to generate and layout the graph nodes
- L188 _private prototype_ `void ExpandNode(bool bReferencers, const FAssetIdentifier& InAssetIdentifier);`
- L191 _private prototype_ `void RemoveAllNodes();` — Removes all nodes from the graph
- L194 _private prototype_ `bool ShouldFilterByCollection() const;` — Returns true if filtering is enabled and we have a valid collection
- L197 _private prototype_ `bool ShouldFilterByPlugin() const;` — Returns true if filtering is enabled and we have a valid plugin name filter set
- L199 _private prototype_ `void GetUnfilteredGraphPluginNamesRecursive(bool bReferencers, const FAssetIdentifier& InAssetIdentifier, int32 InCurrentDepth, int32 InMaxDepth, const FAssetManagerDependencyQuery& Query, TSet<FAssetIdentifier>& OutAssetIdentifiers);`
- L200 _private prototype_ `void GetUnfilteredGraphPluginNames(TArray<FAssetIdentifier> RootIdentifiers, TArray<FName>& OutPluginNames);`
- L202 _private prototype_ `void GetSortedLinks(const TArray<FAssetIdentifier>& Identifiers, bool bReferencers, const FAssetManagerDependencyQuery& Query, TMap<FAssetIdentifier, EDependencyPinCategory>& OutLinks) const;`
- L203 _private prototype_ `bool IsPackageIdentifierPassingFilter(const FAssetIdentifier& InAssetIdentifier) const;`
- L204 _private prototype_ `bool IsPackageIdentifierPassingPluginFilter(const FAssetIdentifier& InAssetIdentifier) const;`
- L205 _private prototype_ `bool DoesAssetPassSearchTextFilter(const FAssetIdentifier& InAssetIdentifier, const FAssetData& InAssetData) const;`
- L207 _private prototype_ `UEdGraphNode_Reference* FindPath(const FAssetIdentifier& RootId, const FAssetIdentifier& TargetId);`
- L208 _private prototype_ `bool FindPath_Recursive(bool bInReferencers, const FAssetIdentifier& InAssetId, const FAssetIdentifier& Target, TMap<FAssetIdentifier, FReferenceNodeInfo>& InNodeInfos, TSet<FAssetIdentifier>& Visited);`
- L210 _private prototype_ `void RefreshReferencedPropertiesNode(const UEdGraphNode_ReferencedProperties* InNode);`
- L213 _private member_ `TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;` — Pool for maintaining and rendering thumbnails
- L216 _private member_ `TWeakPtr<SReferenceViewer> ReferenceViewer;` — Editor for this pool
- L218 _private member_ `TArray<FAssetIdentifier> CurrentGraphRootIdentifiers;`
- L219 _private member_ `FIntPoint CurrentGraphRootOrigin;`
- L222 _private member_ `bool bBreadthLimitReached;` — Stores if the breadth limit was reached on the last refilter
- L225 _private member_ `bool bShowingContentVersePath;` — Whether to show Verse paths
- L228 _private member_ `TSharedPtr<ICollectionContainer> CurrentCollectionFilterContainer;` — Current collection filter. NAME_None for no filter
- L229 _private member_ `FName CurrentCollectionFilterName;`
- L232 _private member_ `TArray<FName> CurrentPluginFilter;` — Current plugin filter. Empty for no filter.
- L235 _private member_ `TArray<FName> EncounteredPluginsAmongNodes;` — Plugin names found among unfiltered nodes. Chose among these when filtering for plugins.
- L238 _private member_ `TSet<FTopLevelAssetPath> CurrentClasses;` — A set of the unique class types referenced
- L241 _private member_ `TMap<FAssetIdentifier, FReferenceNodeInfo> ReferencerNodeInfos;` — Cached Reference Information used to quickly refilter
- L242 _private member_ `TMap<FAssetIdentifier, FReferenceNodeInfo> DependencyNodeInfos;`
- L244 _private member_ `FDoesAssetPassSearchFilterCallback DoesAssetPassSearchFilterCallback;`
- L247 _private member_ `TSet<FName> CurrentCollectionPackages;` — List of packages the current collection filter allows
- L250 _private member_ `TSharedPtr< TFilterCollection<FReferenceNodeInfo & > > FilterCollection;` — Current filter collection
- L252 _private member_ `UReferenceViewerSettings* Settings;`
- L255 _private member_ `FSimpleMulticastDelegate OnAssetsChangedDelegate;` — A delegate to notify when the underlying assets changed (usually through a root or depth change)
- L257 _private member_ `FAssetIdentifier TargetIdentifier;`
- L260 _private member_ `TMap<uint32, TWeakObjectPtr<UEdGraphNode_ReferencedProperties>> ReferencedPropertiesNodes;` — Keeping track of existing Referencing Properties Nodes

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ASSETMANAGEREDITOR_API`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Public/ReferenceViewer/ReferenceViewerSchema.h` (Public)


#### class `UReferenceViewerSchema`  
`class UReferenceViewerSchema : public UEdGraphSchema`  
_L16-45_
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
- L37 _private prototype_ `void GetMakeCollectionWithSubMenu(UToolMenu* Menu, TWeakPtr<class SReferenceViewer> ReferenceViewer, TArray<TSharedPtr<ICollectionContainer>> CollectionContainers) const;` — Constructs the sub-menu for Make Collection With
- L40 _private prototype_ `void GetMakeCollectionWithCollectionContainersSubMenu(UToolMenu* Menu, TWeakPtr<class SReferenceViewer> ReferenceViewer, TArray<TSharedPtr<ICollectionContainer>> CollectionContainers, bool bReferencers) const;` — Constructs the sub-menu for Make Collection With collection containers
- L43 _private prototype_ `void GetMakeCollectionWithReferencersOrDependenciesSubMenu(UToolMenu* Menu, bool bReferencers) const;` — Constructs the sub-menu for Make Collection With Referencers/Dependencies
- L44 _private prototype_ `void GetMakeCollectionWithReferencersOrDependenciesSubMenu(UToolMenu* Menu, TWeakPtr<class SReferenceViewer> ReferenceViewer, TSharedPtr<ICollectionContainer> CollectionContainer, bool bReferencers) const;`

### `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Public/ReferenceViewer/ReferenceViewerSettings.h` (Public)


#### struct `FilterState`  
`struct FilterState`  
_L14-33_
- reflection: `USTRUCT()`
- desc: Project based Reference Viewer Saved Settings
- L18 _public function_ `FilterState() : FilterPath() , bIsEnabled(false)`
- L23 _public function_ `FilterState(FTopLevelAssetPath InFilterPath, bool InState) : FilterPath(InFilterPath) , bIsEnabled(InState)`
- L29 _public member_ `FTopLevelAssetPath FilterPath;` — `UPROPERTY()`
- L32 _public member_ `bool bIsEnabled;` — `UPROPERTY()`

#### enum `EEditorOnlyReferenceFilterType`  
`enum class EEditorOnlyReferenceFilterType`  
_L37-42_
- reflection: `UENUM()`
- desc: @see tooltips in FAssetManagerEditorCommands::RegisterCommands.
- L39 _public enumerator_ `Game`
- L40 _public enumerator_ `Propagation`
- L41 _public enumerator_ `EditorOnly`

#### class `UReferenceViewerSettings`  
`class UReferenceViewerSettings : public UObject`  
_L45-238_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L50 _public prototype_ `bool IsSearchDepthLimited() const;`
- L51 _public prototype_ `void SetSearchDepthLimitEnabled(bool bNewEnabled);`
- L53 _public prototype_ `bool IsShowReferencers() const;`
- L54 _public prototype_ `void SetShowReferencers(const bool bShouldShowReferencers);`
- L56 _public prototype_ `int32 GetSearchReferencerDepthLimit() const;`
- L57 _public prototype_ `void SetSearchReferencerDepthLimit(int32 NewDepthLimit, bool bSaveConfig = true);`
- L59 _public prototype_ `bool IsShowDependencies() const;`
- L60 _public prototype_ `void SetShowDependencies(const bool bShouldShowDependencies);`
- L62 _public prototype_ `int32 GetSearchDependencyDepthLimit() const;`
- L63 _public prototype_ `void SetSearchDependencyDepthLimit(int32 NewDepthLimit, bool bSaveConfig = true);`
- L66 _public function_ `bool IsSearchBreadthLimited() const` — `UE_DEPRECATED(5.5, "Search breadth is always limited. Will always return true.")`
- L69 _public function_ `void SetSearchBreadthLimitEnabled(bool bNewEnabled)` — `UE_DEPRECATED(5.5, "Search breadth is always limited.")`
- L71 _public prototype_ `int32 GetSearchBreadthLimit() const;`
- L72 _public prototype_ `void SetSearchBreadthLimit(int32 NewBreadthLimit);`
- L74 _public prototype_ `bool GetEnableCollectionFilter() const;`
- L75 _public prototype_ `void SetEnableCollectionFilter(bool bEnabled);`
- L77 _public prototype_ `bool GetEnablePluginFilter() const;`
- L78 _public prototype_ `void SetEnablePluginFilter(bool bEnabled);`
- L80 _public prototype_ `bool IsShowSoftReferences() const;`
- L81 _public prototype_ `void SetShowSoftReferencesEnabled(bool bNewEnabled);`
- L83 _public prototype_ `bool IsShowHardReferences() const;`
- L84 _public prototype_ `void SetShowHardReferencesEnabled(bool bNewEnabled);`
- L87 _public function_ `bool IsShowEditorOnlyReferences() const` — `UE_DEPRECATED(5.5, "Use GetEditorOnlyReferenceFilterType.")`
- L89 _public function_ `void SetShowEditorOnlyReferencesEnabled(bool bNewEnabled)` — `UE_DEPRECATED(5.5, "Use SetEditorOnlyReferenceFilterType.")`
- L91 _public prototype_ `EEditorOnlyReferenceFilterType GetEditorOnlyReferenceFilterType() const;`
- L92 _public prototype_ `void SetEditorOnlyReferenceFilterType(EEditorOnlyReferenceFilterType Value);`
- L94 _public prototype_ `bool IsShowManagementReferences() const;`
- L95 _public prototype_ `void SetShowManagementReferencesEnabled(bool bNewEnabled);`
- L97 _public prototype_ `bool IsShowSearchableNames() const;`
- L98 _public prototype_ `void SetShowSearchableNames(bool bNewEnabled);`
- L100 _public prototype_ `bool IsShowCodePackages() const;`
- L101 _public prototype_ `void SetShowCodePackages(bool bNewEnabled);`
- L103 _public prototype_ `bool IsShowDuplicates() const;`
- L104 _public prototype_ `void SetShowDuplicatesEnabled(bool bNewEnabled);`
- L106 _public prototype_ `bool IsShowFilteredPackagesOnly() const;`
- L107 _public prototype_ `void SetShowFilteredPackagesOnlyEnabled(bool bNewEnabled);`
- L109 _public prototype_ `bool IsCompactMode() const;`
- L110 _public prototype_ `void SetCompactModeEnabled(bool bNewEnabled);`
- L112 _public prototype_ `bool IsShowExternalReferencers() const;`
- L113 _public prototype_ `void SetShowExternalReferencersEnabled(bool bNewEnabled);`
- L115 _public prototype_ `bool IsShowPath() const;`
- L116 _public prototype_ `void SetShowPathEnabled(bool bNewEnabled);`
- L118 _public prototype_ `bool GetFiltersEnabled() const;`
- L119 _public prototype_ `void SetFiltersEnabled(bool bNewEnabled);`
- L121 _public prototype_ `bool AutoUpdateFilters() const;`
- L122 _public prototype_ `void SetAutoUpdateFilters(bool bNewEnabled);`
- L124 _public prototype_ `const TArray<FilterState>& GetUserFilters() const;`
- L125 _public prototype_ `void SetUserFilters(TArray<FilterState>& InFilters);`
- L127 _public prototype_ `const TMap<FString, bool>& GetCustomFilters() const;`
- L128 _public prototype_ `void SetCustomFilters(const TMap<FString, bool>& InCustomFilters);`
- L130 _public prototype_ `bool GetFindPathEnabled() const;`
- L131 _public prototype_ `void SetFindPathEnabled(bool bNewEnabled);`
- L136 _private member_ `bool bLimitSearchDepth;` — `UPROPERTY(config)` — Whether to limit the search depth for Referencers & Dependencies
- L140 _private member_ `bool bIsShowReferencers;` — `UPROPERTY(config)` — Whether to display the Referencers
- L144 _private member_ `int32 MaxSearchReferencerDepth;` — `UPROPERTY(config)` — How deep to search references
- L148 _private member_ `bool bIsShowDependencies;` — `UPROPERTY(config)` — Whether to display the Dependencies
- L152 _private member_ `int32 MaxSearchDependencyDepth;` — `UPROPERTY(config)` — How deep to search dependanies
- L157 _private member_ `bool bLimitSearchBreadth_DEPRECATED;` — `UE_DEPRECATED(5.5, "bLimitSearchBreadth has been deprecated.")` — `UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Search breadth is always limited."))` — Whether or not to limit how many siblings can appear
- L161 _private member_ `int32 MaxSearchBreadth;` — `UPROPERTY(config)` — The max number of siblings that can appear from a node
- L165 _private member_ `bool bEnableCollectionFilter;` — `UPROPERTY(config)` — Whether or not to filter from a collection
- L169 _private member_ `bool bEnablePluginFilter;` — `UPROPERTY(config)` — Whether or not to filter for assets by plugins.
- L173 _private member_ `bool bIsShowSoftReferences;` — `UPROPERTY(config)` — Show/Hide Soft References
- L177 _private member_ `bool bIsShowHardReferences;` — `UPROPERTY(config)` — Show/Hide Hard References
- L181 _private member_ `bool bIsShowEditorOnlyReferences;` — `UE_DEPRECATED(5.5, "Use EditorOnlyReferenceFilterType.")` — `UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Use EditorOnlyReferenceFilterType."))`
- L184 _private member_ `EEditorOnlyReferenceFilterType EditorOnlyReferenceFilterType;` — `UPROPERTY(config)`
- L188 _private member_ `bool bIsShowManagementReferences;` — `UPROPERTY(config)` — Show/Hide Management Assets (i.e. PrimaryAssetIds)
- L192 _private member_ `bool bIsShowSearchableNames;` — `UPROPERTY(config)` — Show/Hide Searchable Names (i.e. Gameplay Tags)
- L196 _private member_ `bool bIsShowCodePackages;` — `UPROPERTY(config)` — Show/Hide Native Packages
- L200 _private member_ `bool bIsShowDuplicates;` — `UPROPERTY(config)` — Whether to show duplicate asset references
- L204 _private member_ `bool bIsShowFilteredPackagesOnly;` — `UPROPERTY(config)` — Whether to filter the search results or just select them
- L208 _private member_ `bool bIsCompactMode;` — `UPROPERTY(config)` — Whether to show the nodes in a compact (no thumbnail) view
- L212 _private member_ `bool bIsShowExternalReferencers;` — `UPROPERTY(config)` — Whether to show external referencers or collapsed owner asset
- L216 _private member_ `bool bIsShowPath;` — `UPROPERTY(config)` — Whether to show the package's path as a comment
- L220 _private member_ `bool bFiltersEnabled;` — `UPROPERTY(config)` — This turns on/off any filtering done though the SFilterBar
- L224 _private member_ `bool bAutoUpdateFilters;` — `UPROPERTY(config)` — When true, the filters bar auto updates based on the node types, otherwise user filters will be used
- L228 _private member_ `TArray<FilterState> UserFilters;` — `UPROPERTY(config)` — The list of filters the user has built up
- L232 _private member_ `TMap<FString, bool> CustomFilters;` — `UPROPERTY(config)` — The list of reference viewer specific filters the user has built up
- L236 _private member_ `bool bFindPathEnabled;` — `UPROPERTY(config)` — Enable the Find Path tool
