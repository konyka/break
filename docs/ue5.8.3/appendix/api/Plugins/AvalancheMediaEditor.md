# Plugins / AvalancheMediaEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor`
- headers: 149; symbols: 1911
- symbol kinds: class=145, delegate=11, enum=7, enumerator=39, function=133, macro=1, member=370, namespace=8, prototype=1165, struct=16, typedef=16
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetTools, Avalanche, AvalancheEditorCore, AvalancheRemoteControl, AvalancheTag, ContentBrowser, EditorWidgets, GraphEditor, InputCore, Json, JsonSerialization, JsonUtilities, Kismet, MediaIOEditor, Messaging, Projects, PropertyEditor, RHI, RemoteControl, RemoteControlLogic, RemoteControlUI, RenderCore, Serialization, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, XmlSerialization
- PublicDependencyModuleNames: AvalancheCore, AvalancheMedia, Core, CoreUObject, DeveloperSettings, Engine, MediaIOCore

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/AssetDefinition/AssetDefinition_AvaBroadcastDisplayMediaOutput.h` (Private)


#### class `UAssetDefinition_AvaBroadcastDisplayMediaOutput`  
`class UAssetDefinition_AvaBroadcastDisplayMediaOutput : public UAssetDefinition_MediaOutput`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaOutput`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/AvaMediaEditorModule.h` (Private)


#### class `FAvaMediaEditorModule`  
`class FAvaMediaEditorModule : public IAvaMediaEditorModule`  
_L15-87_
- inherits: `IAvaMediaEditorModule`
- L21 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetBroadcastToolBarExtensibilityManager() override;` — IAvaMediaEditorModule
- L27 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetPlaybackToolBarExtensibilityManager() override;`
- L28 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetRundownToolBarExtensibilityManager() override;`
- L29 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetRundownMenuExtensibilityManager() override;`
- L30 _public prototype_ `virtual bool CanFilterSupportComparisonOperation(const FName& InFilterKey, ETextFilterComparisonOperation InOperation, EAvaRundownSearchListType InRundownSearchListType) const override;`
- L31 _public prototype_ `virtual bool FilterExpression(const FName& InFilterKey, const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const override;`
- L32 _public prototype_ `virtual TArray<TSharedPtr<IAvaRundownFilterSuggestionFactory>> GetSimpleSuggestions(EAvaRundownSearchListType InSuggestionType) const override;`
- L33 _public prototype_ `virtual TArray<TSharedPtr<IAvaRundownFilterSuggestionFactory>> GetComplexSuggestions(EAvaRundownSearchListType InSuggestionType) const override;`
- L36 _public prototype_ `void AddEditorToolbarButtons();`
- L37 _public prototype_ `void RemoveEditorToolbarButtons();`
- L38 _public prototype_ `virtual FSlateIcon GetToolbarBroadcastButtonIcon() const override;`
- L40 _public prototype_ `static void OpenBroadcastEditor(const TArray<FString>& InArguments);`
- L43 _protected prototype_ `void InitExtensibilityManagers();`
- L44 _protected prototype_ `void ResetExtensibilityManagers();`
- L47 _protected prototype_ `void RegisterCustomizations() const;` — Register details view customizations.
- L50 _protected prototype_ `void UnregisterCustomizations() const;` — Unregister details view customizations.
- L53 _private prototype_ `void PostEngineInit();`
- L54 _private prototype_ `void HandleMapChanged(UWorld* InWorld, EMapChangeType InMapChangeType);`
- L61 _private prototype_ `void RegisterRundownFilterExpressionFactory(InArgsType&&... InArgs);`
- L68 _private prototype_ `void RegisterRundownFilterSuggestionFactory(InArgsType&&... InArgs);`
- L70 _private prototype_ `void RegisterRundownFilterExpressionFactories();`
- L72 _private prototype_ `void RegisterRundownFilterSuggestionFactories();`
- L75 _private member_ `TSharedPtr<FExtensibilityManager> BroadcastToolBarExtensibility;`
- L76 _private member_ `TSharedPtr<FExtensibilityManager> PlaybackToolBarExtensibility;`
- L77 _private member_ `TSharedPtr<FExtensibilityManager> RundownToolBarExtensibility;`
- L78 _private member_ `TSharedPtr<FExtensibilityManager> RundownMenuExtensibility;`
- L80 _private member_ `TSharedPtr<FGraphPanelPinConnectionFactory> PlaybackConnectionFactory;`
- L83 _private member_ `TMap<FName, TSharedPtr<IAvaRundownFilterExpressionFactory>> FilterExpressionFactories;` — Holds all the RundownFilterExpressionFactory
- L86 _private member_ `TMap<FName, TSharedPtr<IAvaRundownFilterSuggestionFactory>> FilterSuggestionFactories;` — Holds all the RundownFilterSuggestionFactory

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/AvaMediaEditorSettings.h` (Private)


#### class `UAvaMediaEditorSettings`  
`class UAvaMediaEditorSettings : public UDeveloperSettings`  
_L9-51_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Playback & Broadcast"))`
- inherits: `UDeveloperSettings`
- L14 _public prototype_ `UAvaMediaEditorSettings();`
- L16 _public function_ `static const UAvaMediaEditorSettings& Get()`
- L17 _public function_ `static UAvaMediaEditorSettings& GetMutable()`
- L20 _public member_ `bool bBroadcastEnforceMaxChannelCount = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Broadcast", meta = (InlineEditConditionToggle))`
- L23 _public member_ `int32 BroadcastMaxChannelCount = 9;` — `UPROPERTY(Config, EditAnywhere, Category = "Broadcast", meta = (DisplayName = "Max Channel Count", EditCondition = "bBroadcastEnforceMaxChannelCount"))`
- L32 _public member_ `bool bBroadcastShowAllMediaOutputClasses = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Broadcast", meta = (DisplayName = "Show All Media Output Classes"))` — By default, only the media output classes with a device provider are listed as output devices. If this is set to true, then all the media output classes will be listed, thus allowing use of outputs that don't correspond to a physical device, such as NDI, File output, etc. Caution: enabling this mode may expose Media Output classes that are not usable.
- L35 _public member_ `FLinearColor PlaybackDefaultNodeColor;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback", meta = (DisplayName = "Default Node Color"))`
- L38 _public member_ `FLinearColor PlaybackChannelsNodeColor;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback", meta = (DisplayName = "Channels Node Color"))`
- L41 _public member_ `FLinearColor PlaybackPlayerNodeColor;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback", meta = (DisplayName = "Player Node Color"))`
- L44 _public member_ `FLinearColor PlaybackEventNodeColor;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback", meta = (DisplayName = "Event Node Color"))`
- L47 _public member_ `FLinearColor PlaybackActionNodeColor;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback", meta = (DisplayName = "Action Node Color"))`
- L50 _private prototype_ `static UAvaMediaEditorSettings* GetSingletonInstance();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/AvaMediaEditorStyle.h` (Private)


#### class `FAvaMediaEditorStyle`  
`class FAvaMediaEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaMediaEditorStyle& Get()`
- L16 _public prototype_ `FAvaMediaEditorStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/AvaMediaEditorUtils.h` (Private)


#### class `FAvaMediaEditorUtils`  
`class FAvaMediaEditorUtils`  
_L8-13_
- L11 _public prototype_ `static const FSlateBrush* GetChannelStatusBrush(EAvaBroadcastChannelState InChannelState, EAvaBroadcastIssueSeverity InChannelIssueSeverity);`
- L12 _public prototype_ `static FText GetChannelStatusText(EAvaBroadcastChannelState InChannelState, EAvaBroadcastIssueSeverity InChannelIssueSeverity);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/AppModes/AvaBroadcastAppMode.h` (Private)


#### class `FAvaBroadcastAppMode`  
`class FAvaBroadcastAppMode : public FApplicationMode`  
_L10-29_
- inherits: `FApplicationMode`
- L15 _public member_ `static const FName DefaultMode;` — Mode constants
- L18 _public prototype_ `FAvaBroadcastAppMode(const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor, const FName& InModeName);`
- L19 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L23 _protected prototype_ `static FText GetLocalizedMode(const FName InMode);`
- L25 _protected member_ `TWeakPtr<FAvaBroadcastEditor> BroadcastEditorWeak;`
- L28 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs in the mode

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/AppModes/AvaBroadcastDefaultMode.h` (Private)


#### class `FAvaBroadcastDefaultMode`  
`class FAvaBroadcastDefaultMode : public FAvaBroadcastAppMode`  
_L7-11_
- inherits: `FAvaBroadcastAppMode`
- L10 _public prototype_ `FAvaBroadcastDefaultMode(const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/AvaBroadcastEditor.h` (Private)


#### class `FAvaBroadcastEditor`  
`class FAvaBroadcastEditor : public FWorkflowCentricApplication`  
_L23-95_
- inherits: `FWorkflowCentricApplication`
- L28 _public function_ `explicit FAvaBroadcastEditor(FPrivateToken)`
- L32 _public prototype_ `static void OpenBroadcastEditor();`
- L34 _public prototype_ `void SelectOutputTile(const TSharedPtr<FAvaBroadcastOutputTileItem>& InOutputTile);`
- L35 _public prototype_ `TSharedPtr<FAvaBroadcastOutputTileItem> GetSelectedOutputTile() const;`
- L37 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutputItemSelectionChanged, const TSharedPtr<FAvaBroadcastOutputTileItem>&);`
- L38 _public member_ `FOnOutputItemSelectionChanged OnOutputTileSelectionChanged;`
- L41 _protected prototype_ `void InitBroadcastEditor(UAvaBroadcast* InBroadcast);`
- L43 _protected prototype_ `void OnBroadcastChanged(EAvaBroadcastChange ChangedEvent);`
- L44 _protected prototype_ `void OnAvaMediaSettingsChanged(UObject*, FPropertyChangedEvent&);`
- L46 _protected prototype_ `virtual void SaveAsset_Execute() override;`
- L47 _protected function_ `virtual bool CanSaveAssetAs() const override`
- L48 _protected function_ `virtual bool CanFindInContentBrowser() const override`
- L50 _protected prototype_ `virtual void OnClose() override;`
- L53 _protected prototype_ `virtual FName GetToolkitFName() const override;`
- L54 _protected prototype_ `virtual FText GetBaseToolkitName() const override;`
- L55 _protected prototype_ `virtual FText GetToolkitName() const override;`
- L56 _protected prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L57 _protected prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L58 _protected prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L62 _protected prototype_ `virtual const FSlateBrush* GetDefaultTabIcon() const override;`
- L66 _public prototype_ `UAvaBroadcast* GetBroadcastObject() const;`
- L68 _public prototype_ `void ExtendToolBar(TSharedPtr<FExtender> Extender);`
- L69 _public prototype_ `void FillPlayToolBar(FToolBarBuilder& ToolBarBuilder);`
- L71 _public prototype_ `FText GetCurrentProfileName() const;`
- L72 _public prototype_ `void MakeProfilesToolbar(FToolBarBuilder& ToolBarBuilder);`
- L73 _public prototype_ `TSharedRef<SWidget> MakeProfileComboButton();`
- L75 _public prototype_ `void CreateNewProfile();`
- L76 _public prototype_ `FReply OnProfileSelected(FName InProfileName);`
- L78 _public prototype_ `bool CanAddChannel();`
- L79 _public prototype_ `void AddChannel();`
- L82 _protected prototype_ `void RegisterApplicationModes();`
- L83 _protected prototype_ `void CreateDefaultCommands();`
- L85 _protected prototype_ `static FText GetStopPlaybackClientTooltip();`
- L86 _protected prototype_ `static FText GetLaunchLocalServerTooltip();`
- L87 _protected prototype_ `static void StartPlaybackClientAction();`
- L90 _protected member_ `static TSharedPtr<FAvaBroadcastEditor> BroadcastEditor;`
- L92 _protected member_ `TWeakObjectPtr<UAvaBroadcast> BroadcastWeak;`
- L94 _protected member_ `TWeakPtr<FAvaBroadcastOutputTileItem> SelectedOutputTileWeak;`

#### struct `FAvaBroadcastEditor::FPrivateToken`  
`struct FPrivateToken`  
_L25-25_
- L25 _public prototype_ `struct FPrivateToken`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutputItemSelectionChanged, const TSharedPtr<FAvaBroadcastOutputTileItem>&);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/ChannelGrid/AvaBroadcastOutputTileItem.h` (Private)


#### class `FAvaBroadcastOutputTileItem`  
`class FAvaBroadcastOutputTileItem : public TSharedFromThis<FAvaBroadcastOutputTileItem>`  
_L26-70_
- inherits: `TSharedFromThis<FAvaBroadcastOutputTileItem>`
- L29 _public prototype_ `FAvaBroadcastOutputTileItem(FName InChannelName, UMediaOutput* InMediaOutput);`
- L30 _public prototype_ `~FAvaBroadcastOutputTileItem();`
- L32 _public prototype_ `const FAvaBroadcastOutputChannel& GetChannel() const;`
- L33 _public prototype_ `FAvaBroadcastOutputChannel& GetChannel();`
- L35 _public function_ `UMediaOutput* GetMediaOutput() const`
- L37 _public prototype_ `TSharedRef<SWidget> GenerateTile() const;`
- L39 _public prototype_ `FText GetDisplayText() const;`
- L40 _public prototype_ `FText GetMediaOutputStatusText() const;`
- L41 _public prototype_ `FText GetToolTipText() const;`
- L43 _public prototype_ `const FSlateBrush* GetMediaOutputIcon() const;`
- L44 _public prototype_ `const FSlateBrush* GetMediaOutputStatusBrush() const;`
- L46 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L49 _protected prototype_ `void OnMediaOutputPropertyChanged(UObject* InObject, FPropertyChangedEvent& PropertyChangedEvent);`
- L50 _protected prototype_ `void OnChannelChanged(const FAvaBroadcastOutputChannel& InChannel, EAvaBroadcastChannelChange InChange);`
- L51 _protected prototype_ `void OnMediaOutputStateChanged(const FAvaBroadcastOutputChannel& InChannel, const UMediaOutput* InMediaOutput);`
- L52 _protected prototype_ `void OnBroadcastChanged(EAvaBroadcastChange InChange);`
- L54 _protected prototype_ `void UpdateInfo();`
- L56 _protected prototype_ `FText FindLatestDisplayText() const;`
- L59 _protected member_ `FName ChannelName = NAME_None;`
- L61 _protected member_ `TWeakObjectPtr<UMediaOutput> MediaOutput;`
- L63 _protected member_ `FText MediaOutputDisplayText;`
- L64 _protected member_ `FText MediaOutputStatusText;`
- L65 _protected member_ `FText MediaOutputToolTipText;`
- L67 _protected member_ `const FSlateBrush* MediaOutputStatusBrush = nullptr;`
- L69 _protected member_ `FDelegateHandle BroadcastChangedHandle;`

#### Free symbols / members of external scopes

- L24 _typedef_ `using FAvaBroadcastOutputTileItemPtr = TSharedPtr<FAvaBroadcastOutputTileItem>;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/ChannelGrid/DragDropOps/AvaBroadcastOutputTileItemDragDropOp.h` (Private)


#### class `FAvaBroadcastOutputTileItemDragDropOp`  
`class FAvaBroadcastOutputTileItemDragDropOp : public FDecoratedDragDropOp`  
_L11-31_
- inherits: `FDecoratedDragDropOp`
- L14 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAvaOutputTileDragDropOp, FDecoratedDragDropOp) static TSharedRef<FAvaBroadcastOutputTileItemDragDropOp> New(const FAvaBroadcastOutputTileItemPtr& InOutputClassItem, bool bInIsDuplicating);`
- L18 _public prototype_ `bool IsValidToDropInChannel(FName InTargetChannelName) const;`
- L20 _public function_ `FAvaBroadcastOutputTileItemPtr GetOutputTileItem() const`
- L22 _public prototype_ `FReply OnChannelDrop(FName InTargetChannelName);`
- L25 _protected prototype_ `void Init(const FAvaBroadcastOutputTileItemPtr& InOutputTileItem, bool bInIsDuplicating);`
- L28 _protected member_ `FAvaBroadcastOutputTileItemPtr OutputTileItem;` — Keep Reference Count while Drag Dropping
- L30 _protected member_ `bool bIsDuplicating = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/ChannelGrid/Slate/SAvaBroadcastChannel.h` (Private)


#### class `SAvaBroadcastChannel`  
`class SAvaBroadcastChannel : public SCompoundWidget`  
_L38-158_
- inherits: `SCompoundWidget`
- L41 _public function_ `SLATE_BEGIN_ARGS(SAvaBroadcastChannel)`
- L42 _public prototype_ `SLATE_ARGUMENT(FName, ChannelName) SLATE_ATTRIBUTE(bool, CanMaximize) SLATE_EVENT(FAvaBroadcastOnChannelMaximizeClicked, OnMaximizeClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`
- L51 _public prototype_ `void RegisterCommands();`
- L52 _public function_ `FName GetChannelName() const`
- L54 _public prototype_ `void SetPosition(int32 InColumnIndex, int32 InRowIndex);`
- L55 _public function_ `int32 GetRowIndex() const`
- L56 _public function_ `int32 GetColumnIndex() const`
- L58 _public prototype_ `void OnChannelChanged(const FAvaBroadcastOutputChannel& InChannel, EAvaBroadcastChannelChange InChange);`
- L60 _public prototype_ `void OnChannelBroadcastStateChanged(const FAvaBroadcastOutputChannel& InChannel);`
- L61 _public prototype_ `void OnChannelRenderTargetChanged(const FAvaBroadcastOutputChannel& InChannel);`
- L62 _public prototype_ `void OnChannelMediaOutputsChanged(const FAvaBroadcastOutputChannel& InChannel);`
- L64 _public prototype_ `void OnOutputTileSelectionChanged(const TSharedPtr<FAvaBroadcastOutputTileItem>& InMediaOutputItem);`
- L66 _public prototype_ `void DeleteSelectedOutputTiles();`
- L68 _public prototype_ `FText GetChannelStatusText() const;`
- L70 _public prototype_ `TSharedRef<SWidget> GetChannelStatusOptions();`
- L71 _public prototype_ `TSharedRef<SWidget> MakeChannelVerticalBox();`
- L72 _public prototype_ `TSharedRef<SWidget> MakeMediaOutputsTileView();`
- L74 _public prototype_ `TSharedRef<ITableRow> OnGenerateMediaOutputTile(FAvaBroadcastOutputTileItemPtr Item, const TSharedRef<STableViewBase>& InOwnerTable) const;`
- L75 _public prototype_ `void OnMediaOutputTileSelectionChanged(FAvaBroadcastOutputTileItemPtr Item, ESelectInfo::Type SelectInfo);`
- L76 _public prototype_ `TSharedPtr<SWidget> OnMediaOutputTileContextMenuOpening() const;`
- L78 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L79 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L80 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L82 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L84 _public prototype_ `void SetDragging(bool bIsDragging);`
- L86 _public prototype_ `FText GetChannelNameText() const;`
- L87 _public prototype_ `bool OnVerifyChannelNameTextChanged(const FText& InText, FText& OutErrorMessage);`
- L88 _public prototype_ `void OnChannelNameTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L90 _public prototype_ `FReply OnChannelStatusButtonClicked();`
- L91 _public prototype_ `FReply OnChannelPinButtonClicked();`
- L92 _public prototype_ `FReply OnChannelTypeToggleButtonClicked();`
- L93 _public prototype_ `FReply OnChannelMaximizeButtonClicked();`
- L94 _public prototype_ `FReply OnChannelRemoveButtonClicked();`
- L96 _public prototype_ `void OnChannelStatusSelected(EAvaBroadcastChannelState State);`
- L98 _public prototype_ `const FSlateBrush* GetChannelStatusBrush() const;`
- L99 _public prototype_ `const FSlateBrush* GetChannelPreviewBrush() const;`
- L100 _public prototype_ `const FSlateBrush* GetChannelPinBrush() const;`
- L101 _public prototype_ `const FSlateBrush* GetChannelMaximizeRestoreBrush() const;`
- L102 _public prototype_ `const FSlateBrush* GetChannelTypeBrush() const;`
- L104 _public prototype_ `EVisibility GetMediaOutputEmptyTextVisibility() const;`
- L105 _public prototype_ `EVisibility GetChannelPreviewVisibility() const;`
- L106 _public prototype_ `EVisibility GetChannelDragVisibility() const;`
- L108 _public prototype_ `bool ShouldInvertAlpha() const;`
- L110 _public prototype_ `bool IsReadOnly() const;`
- L111 _public prototype_ `bool CanEditChanges() const;`
- L114 _protected prototype_ `FText GetChannelMaximizeRestoreTooltipText() const;`
- L116 _protected prototype_ `void CreateQualitySettingsDetails();`
- L118 _protected prototype_ `void OnChannelQualitySettingsChanged(const FPropertyChangedEvent& InEvent);`
- L120 _protected prototype_ `TSharedRef<SWidget> GetQualitySettingsDetails();`
- L122 _protected member_ `FName ChannelName = NAME_None;`
- L124 _protected member_ `TSharedPtr<SMenuAnchor> ChannelStatusOptions;`
- L126 _protected member_ `TSharedPtr<SListView<FAvaBroadcastOutputTileItemPtr>> OutputTileListView;`
- L128 _protected member_ `TSharedPtr<FStructOnScope> QualitySettingsStruct;`
- L130 _protected member_ `TSharedPtr<IStructureDetailsView> QualitySettingsDetails;`
- L132 _protected member_ `TArray<FAvaBroadcastOutputTileItemPtr> OutputTileItems;`
- L134 _protected member_ `TSharedPtr<FSlateImageBrush> ChannelPreviewBrush;`
- L136 _protected member_ `const FSlateBrush* ChannelStatusBrush = nullptr;`
- L138 _protected member_ `TSharedPtr<SInlineEditableTextBlock> ChannelNameTextBlock;`
- L140 _protected member_ `TWeakPtr<FAvaBroadcastEditor> BroadcastEditorWeak;`
- L142 _protected member_ `TSharedPtr<FUICommandList> MediaOutputCommandList;`
- L144 _protected member_ `EVisibility DragVisibility = EVisibility::Hidden;`
- L146 _protected member_ `EAvaBroadcastChannelState ChannelState = EAvaBroadcastChannelState::Idle;`
- L148 _protected member_ `FText ChannelStateText;`
- L150 _protected member_ `TAttribute<bool> CanMaximize;`
- L151 _protected member_ `FAvaBroadcastOnChannelMaximizeClicked OnMaximizeClicked;`
- L153 _protected member_ `int32 RowIndex = INDEX_NONE;`
- L155 _protected member_ `int32 ColumnIndex= INDEX_NONE;`
- L157 _protected member_ `bool bShouldInvertAlpha = false;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FAvaBroadcastCanMaximizeChannel);`
- L35 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FAvaBroadcastCanMaximizeChannel);`
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FAvaBroadcastOnChannelMaximizeClicked, const TSharedRef<SAvaBroadcastChannel>&);`
- L36 _prototype_ `DECLARE_DELEGATE_OneParam(FAvaBroadcastOnChannelMaximizeClicked, const TSharedRef<SAvaBroadcastChannel>&);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/ChannelGrid/Slate/SAvaBroadcastChannels.h` (Private)


#### class `SAvaBroadcastChannels`  
`class SAvaBroadcastChannels : public SCompoundWidget`  
_L18-65_
- inherits: `SCompoundWidget`
- L36 _public function_ `SLATE_BEGIN_ARGS(SAvaBroadcastChannels)`
- L37 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`
- L44 _public prototype_ `float GetRowFill(int32 RowId) const;`
- L45 _public prototype_ `float GetColumnFill(int32 ColumnId) const;`
- L47 _public prototype_ `bool CanMaximizeChannel() const;`
- L48 _public prototype_ `void ToggleMaximizeChannel(const TSharedRef<SAvaBroadcastChannel>& InWidget);`
- L50 _public prototype_ `void OnBroadcastChanged(EAvaBroadcastChange ChangedEvent);`
- L51 _public prototype_ `void RefreshChannelGrid();`
- L53 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _protected member_ `TWeakObjectPtr<UAvaBroadcast> BroadcastWeak;`
- L58 _protected member_ `TWeakPtr<FAvaBroadcastEditor> BroadcastEditorWeak;`
- L60 _protected member_ `TSharedPtr<SGridPanel> ChannelGrid;`
- L62 _protected member_ `TMap<FName, TSharedPtr<SAvaBroadcastChannel>> Channels;`
- L64 _protected member_ `FAvaChannelMaximizer ChannelMaximizer;`

#### struct `SAvaBroadcastChannels::FAvaChannelMaximizer`  
`struct FAvaChannelMaximizer`  
_L20-33_
- L22 _public prototype_ `FAvaChannelMaximizer();`
- L24 _public prototype_ `void Reset();`
- L25 _public prototype_ `void ToggleMaximize(const TSharedRef<SAvaBroadcastChannel>& InChannelWidget);`
- L27 _public prototype_ `float GetRowFill(int32 InRowIndex) const;`
- L28 _public prototype_ `float GetColumnFill(int32 InColumnIndex) const;`
- L30 _public member_ `TWeakPtr<SAvaBroadcastChannel> ChannelWidgetWeak;`
- L31 _public member_ `FCurveSequence MaximizeSequence;`
- L32 _public member_ `bool bMaximizing = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/ChannelGrid/Slate/SAvaBroadcastProfileEntry.h` (Private)


#### class `SAvaBroadcastProfileEntry`  
`class SAvaBroadcastProfileEntry : public SCompoundWidget`  
_L21-61_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SAvaBroadcastProfileEntry)`
- L25 _public prototype_ `SLATE_EVENT(FOnAvaBroadcastProfileEntrySelected, OnProfileEntrySelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FName InProfileName);`
- L31 _public prototype_ `void UpdateProfileName(FName InProfileName);`
- L32 _public function_ `FText GetProfileNameText() const`
- L34 _public prototype_ `void OnProfileTextCommitted(const FText& InProfileText, ETextCommit::Type InCommitType);`
- L35 _public prototype_ `bool OnVerifyProfileTextChanged(const FText& InProfileText, FText& OutErrorMessage);`
- L37 _public prototype_ `void OnEnterEditingMode();`
- L38 _public prototype_ `void OnExitEditingMode();`
- L40 _public prototype_ `FReply RenameProfile();`
- L41 _public prototype_ `FReply DeleteProfile();`
- L43 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L44 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L46 _public prototype_ `const FSlateBrush* GetBorderImage() const;`
- L49 _protected member_ `FName ProfileName;`
- L51 _protected member_ `FText ProfileNameText;`
- L53 _protected member_ `FOnAvaBroadcastProfileEntrySelected OnProfileEntrySelected;`
- L55 _protected member_ `TSharedPtr<SInlineEditableTextBlock> ProfileTextBlock;`
- L57 _protected member_ `static const FButtonStyle* MenuButtonStyle;`
- L59 _protected member_ `bool bRenameRequested = false;`
- L60 _protected member_ `bool bInEditingMode = false;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnAvaBroadcastProfileEntrySelected, FName ProfileName);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnAvaBroadcastProfileEntrySelected, FName ProfileName);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/DetailsView/SAvaBroadcastDetailsView.h` (Private)


#### class `SAvaBroadcastDetailsView`  
`class SAvaBroadcastDetailsView : public SCompoundWidget`  
_L13-31_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaBroadcastDetailsView)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`
- L22 _public prototype_ `bool IsMediaOutputEditingEnabled() const;`
- L23 _public prototype_ `void OnMediaOutputSelectionChanged(const TSharedPtr<FAvaBroadcastOutputTileItem>& InSelectedItem);`
- L25 _public prototype_ `EVisibility GetEmptySelectionTextVisibility() const;`
- L28 _protected member_ `TWeakPtr<FAvaBroadcastEditor> BroadcastEditorWeak;`
- L30 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/OutputDevices/AvaBroadcastDisplayMediaOutputFactory.h` (Private)


#### class `UAvaBroadcastDisplayMediaOutputFactory`  
`class UAvaBroadcastDisplayMediaOutputFactory : public UFactory`  
_L18-28_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Implements a factory for UAvaBroadcastDisplayMediaOutput objects.
- L23 _public prototype_ `UAvaBroadcastDisplayMediaOutputFactory();`
- L25 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L26 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L27 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/OutputDevices/AvaBroadcastMediaIOOutputConfigurationCustomization.h` (Private)


#### class `FAvaBroadcastMediaIOOutputConfigurationCustomization`  
`class FAvaBroadcastMediaIOOutputConfigurationCustomization : public FMediaIOCustomizationBase`  
_L12-26_
- inherits: `FMediaIOCustomizationBase`
- desc: Implements a details view customization for the FMediaIOOutputConfiguration
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _private prototype_ `virtual TAttribute<FText> GetContentText() override;`
- L19 _private prototype_ `virtual TSharedRef<SWidget> HandleSourceComboButtonMenuContent() override;`
- L21 _private prototype_ `void OnSelectionChanged(FMediaIOOutputConfiguration SelectedItem);`
- L22 _private prototype_ `FReply OnButtonClicked() const;`
- L24 _private member_ `TWeakPtr<SWidget> PermutationSelector;`
- L25 _private member_ `FMediaIOOutputConfiguration SelectedConfiguration;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/OutputDevices/DragDropOps/AvaBroadcastOutputTreeItemDragDropOp.h` (Private)


#### class `FAvaBroadcastOutputTreeItemDragDropOp`  
`class FAvaBroadcastOutputTreeItemDragDropOp : public FDecoratedDragDropOp`  
_L9-27_
- inherits: `FDecoratedDragDropOp`
- L12 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAvaBroadcastOutputTreeItemDragDropOp, FDecoratedDragDropOp) static TSharedRef<FAvaBroadcastOutputTreeItemDragDropOp> New(const TSharedPtr<IAvaBroadcastOutputTreeItem>& InOutputClassItem);`
- L16 _public prototype_ `bool IsValidToDropInChannel(FName InTargetChannelName) const;`
- L18 _public function_ `TSharedPtr<IAvaBroadcastOutputTreeItem> GetOutputTreeItem() const`
- L20 _public prototype_ `FReply OnChannelDrop(FName InTargetChannelName);`
- L23 _protected prototype_ `void Init(const TSharedPtr<IAvaBroadcastOutputTreeItem>& InOutputClassItem);`
- L26 _protected member_ `TSharedPtr<IAvaBroadcastOutputTreeItem> OutputTreeItem;` — Keep Reference Count while Drag Dropping

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/OutputDevices/Slate/SAvaBroadcastOutputDevices.h` (Private)


#### class `SAvaBroadcastOutputDevices`  
`class SAvaBroadcastOutputDevices : public SCompoundWidget`  
_L15-47_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAvaBroadcastOutputDevices)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`
- L24 _public prototype_ `TSharedRef<ITableRow> OnGenerateItemRow(FAvaOutputTreeItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L26 _public prototype_ `void OnGetRowChildren(FAvaOutputTreeItemPtr InItem, TArray<FAvaOutputTreeItemPtr>& OutChildren) const;`
- L27 _public prototype_ `void OnRowExpansionChanged(FAvaOutputTreeItemPtr InItem, const bool bInIsExpanded);`
- L29 _public prototype_ `void RefreshOutputDevices();`
- L32 _protected prototype_ `void OnBroadcastChanged(EAvaBroadcastChange InChange);`
- L33 _protected prototype_ `void OnAvaMediaSettingsChanged(UObject*, FPropertyChangedEvent& InPropertyChangeEvent);`
- L35 _protected prototype_ `uint32 ItemHashRecursive(const FAvaOutputTreeItemPtr& InItem) const;`
- L36 _protected prototype_ `void SetExpansionStatesRecursive(const FAvaOutputTreeItemPtr& InRootItem);`
- L38 _protected member_ `static TMap<uint32, bool> ItemExpansionStates;`
- L40 _protected member_ `FDelegateHandle BroadcastChangedHandle;`
- L42 _protected member_ `TSharedPtr<STreeView<FAvaOutputTreeItemPtr>> OutputTree;`
- L44 _protected member_ `TArray<FAvaOutputTreeItemPtr> TopLevelItems;`
- L46 _protected member_ `TSharedPtr<FAvaBroadcastOutputRootItem> RootItem;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/TabFactories/AvaBroadcastChannelsTabFactory.h` (Private)


#### class `FAvaBroadcastChannelsTabFactory`  
`class FAvaBroadcastChannelsTabFactory : public FAvaBroadcastTabFactory`  
_L7-18_
- inherits: `FAvaBroadcastTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaBroadcastChannelsTabFactory(const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`
- L15 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L16 _public prototype_ `virtual const FSlateBrush* GetTabIcon(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/TabFactories/AvaBroadcastDetailsTabFactory.h` (Private)


#### class `FAvaBroadcastDetailsTabFactory`  
`class FAvaBroadcastDetailsTabFactory : public FAvaBroadcastTabFactory`  
_L7-15_
- inherits: `FAvaBroadcastTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaBroadcastDetailsTabFactory(const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/TabFactories/AvaBroadcastOutputsTabFactory.h` (Private)


#### class `FAvaBroadcastOutputsTabFactory`  
`class FAvaBroadcastOutputsTabFactory : public FAvaBroadcastTabFactory`  
_L7-16_
- inherits: `FAvaBroadcastTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaBroadcastOutputsTabFactory(const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Broadcast/TabFactories/AvaBroadcastTabFactory.h` (Private)


#### class `FAvaBroadcastTabFactory`  
`class FAvaBroadcastTabFactory : public FWorkflowTabFactory`  
_L10-19_
- inherits: `FWorkflowTabFactory`
- desc: Base class for all Tab Factories in Ava Broadcast Editor
- L14 _public prototype_ `FAvaBroadcastTabFactory(const FName& InTabID, const TSharedPtr<FAvaBroadcastEditor>& InBroadcastEditor);`
- L18 _protected member_ `TWeakPtr<FAvaBroadcastEditor> BroadcastEditorWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Customization/AvaPlaybackServerLoggingEntryCustomization.h` (Private)


#### class `FAvaPlaybackServerLoggingEntryCustomization`  
`class FAvaPlaybackServerLoggingEntryCustomization : public IPropertyTypeCustomization`  
_L7-16_
- inherits: `IPropertyTypeCustomization`
- L10 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L13 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InPropertyTypeCustomizationUtils) override;`
- L14 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InPropertyTypeCustomizationUtils) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Customization/AvaSynchronizedEventsFeatureSelectionCustomization.h` (Private)


#### class `FAvaSynchronizedEventsFeatureSelectionCustomization`  
`class FAvaSynchronizedEventsFeatureSelectionCustomization : public IPropertyTypeCustomization`  
_L10-19_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InPropertyTypeCustomizationUtils) override;`
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InPropertyTypeCustomizationUtils) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Customization/SAvaSynchronizedEventsImplementationSelector.h` (Private)


#### class `SAvaSynchronizedEventsImplementationSelector`  
`class SAvaSynchronizedEventsImplementationSelector : public SCompoundWidget`  
_L10-40_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaSynchronizedEventsImplementationSelector)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L19 _public prototype_ `TSharedRef<SWidget> GenerateWidget(FName InItem);`
- L21 _public prototype_ `void HandleSelectionChanged(FName InProposedSelection, ESelectInfo::Type InSelectInfo);`
- L23 _public prototype_ `FText GetDisplayTextFromProperty() const;`
- L25 _public prototype_ `void OnComboBoxOpening();`
- L28 _protected prototype_ `FName GetItemFromProperty() const;`
- L30 _protected prototype_ `FText GetDisplayTextFromItem(FName InItem) const;`
- L31 _protected prototype_ `FText GetDisplayDescriptionFromItem(FName InItem) const;`
- L33 _protected prototype_ `void UpdateItems();`
- L35 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L37 _protected member_ `TSharedPtr<SComboBox<FName>> Combo;`
- L39 _protected member_ `TArray<FName> Items;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/AppModes/AvaPlaybackAppMode.h` (Private)


#### class `FAvaPlaybackAppMode`  
`class FAvaPlaybackAppMode : public FApplicationMode`  
_L10-29_
- inherits: `FApplicationMode`
- L15 _public member_ `static const FName DefaultMode;` — Mode constants
- L18 _public prototype_ `FAvaPlaybackAppMode(const TSharedPtr<FAvaPlaybackGraphEditor>& InPlaybackEditor, const FName& InModeName);`
- L19 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L23 _protected prototype_ `static FText GetLocalizedMode(const FName InMode);`
- L25 _protected member_ `TWeakPtr<FAvaPlaybackGraphEditor> PlaybackEditorWeak;`
- L28 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs in the mode

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/AppModes/AvaPlaybackDefaultMode.h` (Private)


#### class `FAvaPlaybackDefaultMode`  
`class FAvaPlaybackDefaultMode : public FAvaPlaybackAppMode`  
_L7-11_
- inherits: `FAvaPlaybackAppMode`
- L10 _public prototype_ `FAvaPlaybackDefaultMode(const TSharedPtr<FAvaPlaybackGraphEditor>& InPlaybackEditor);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/AssetDefinition_AvaPlaybackGraph.h` (Private)


#### class `UAssetDefinition_AvaPlaybackGraph`  
`class UAssetDefinition_AvaPlaybackGraph : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/AvaPlaybackCommands.h` (Private)


#### class `FAvaPlaybackCommands`  
`class FAvaPlaybackCommands : public TCommands<FAvaPlaybackCommands>`  
_L8-24_
- inherits: `TCommands<FAvaPlaybackCommands>`
- L12 _public function_ `FAvaPlaybackCommands() : TCommands<FAvaPlaybackCommands>(TEXT("AvaPlayback") , NSLOCTEXT("MotionDesignPlaybackCommands", "MotionDesignPlaybackCommands", "Motion Design Playback") , NAME_None , FAppStyle::GetAppStyleSetName())`
- L20 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L22 _public member_ `TSharedPtr<FUICommandInfo> AddInputPin;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> RemoveInputPin;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/AvaPlaybackGraphEditor.h` (Private)


#### class `FAvaPlaybackGraphEditor`  
`class FAvaPlaybackGraphEditor : public FWorkflowCentricApplication , public IAvaPlaybackGraphEditor`  
_L34-139_
- inherits: `FWorkflowCentricApplication,IAvaPlaybackGraphEditor`
- L39 _public prototype_ `void InitPlaybackEditor(const EToolkitMode::Type InMode , const TSharedPtr<IToolkitHost>& InitToolkitHost , UAvaPlaybackGraph* InPlayback);`
- L44 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L45 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L46 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L47 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L50 _public prototype_ `UAvaPlaybackGraph* GetPlaybackObject() const;`
- L52 _public prototype_ `void ExtendToolBar(TSharedPtr<FExtender> Extender);`
- L53 _public prototype_ `void FillPlayToolBar(FToolBarBuilder& ToolBarBuilder);`
- L56 _public prototype_ `static void CacheOverrideNodeClasses();`
- L58 _public prototype_ `TSharedRef<SGraphEditor> CreateGraphEditor();`
- L61 _public prototype_ `virtual UEdGraph* CreatePlaybackGraph(UAvaPlaybackGraph* InPlayback) override;`
- L62 _public prototype_ `virtual void SetupPlaybackNode(UEdGraph* InGraph, UAvaPlaybackNode* InPlaybackNode, bool bSelectNewNode) override;`
- L63 _public prototype_ `virtual void CompilePlaybackNodesFromGraphNodes(UAvaPlaybackGraph* InPlayback) override;`
- L64 _public prototype_ `virtual void CreateInputPin(UEdGraphNode* InGraphNode) override;`
- L65 _public prototype_ `virtual void RefreshNode(UEdGraphNode& InGraphNode) override;`
- L66 _public prototype_ `virtual bool GetBoundsForSelectedNodes(FSlateRect& Rect, float Padding) override;`
- L67 _public prototype_ `virtual TSet<UObject*> GetSelectedNodes() const override;`
- L71 _public prototype_ `void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L80 _public prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);` — Called when a node's title is committed for a rename @param	NewText				New title text @param	CommitInfo			How text was committed @param	NodeBeingChanged	The node being changed
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaybackSelectionChanged, const TArray<UObject*>&);`
- L83 _public member_ `FOnPlaybackSelectionChanged OnPlaybackSelectionChanged;`
- L86 _protected prototype_ `void RegisterApplicationModes();`
- L88 _protected prototype_ `void CreateDefaultCommands();`
- L89 _protected prototype_ `void CreateGraphCommands();`
- L92 _public prototype_ `bool CanAddInputPin() const;`
- L93 _public prototype_ `void AddInputPin();`
- L95 _public prototype_ `bool CanRemoveInputPin() const;`
- L96 _public prototype_ `void RemoveInputPin();`
- L98 _public prototype_ `void CreateComment();`
- L100 _public function_ `bool CanSelectAllNodes() const`
- L101 _public prototype_ `void SelectAllNodes();`
- L103 _public prototype_ `bool CanDeleteSelectedNodes() const;`
- L104 _public prototype_ `void DeleteSelectedNodes();`
- L105 _public prototype_ `void DeleteSelectedDuplicatableNodes();`
- L107 _public prototype_ `bool CanCopySelectedNodes() const;`
- L108 _public prototype_ `void CopySelectedNodes();`
- L110 _public prototype_ `bool CanCutSelectedNodes() const;`
- L111 _public prototype_ `void CutSelectedNodes();`
- L113 _public prototype_ `virtual bool CanPasteNodes() const override;`
- L114 _public prototype_ `void PasteNodes();`
- L115 _public prototype_ `virtual void PasteNodesHere(const FVector2D& Location) override;`
- L117 _public prototype_ `bool CanDuplicateSelectedNodes() const;`
- L118 _public prototype_ `void DuplicateSelectedNodes();`
- L120 _public prototype_ `void OnAlignTop();`
- L121 _public prototype_ `void OnAlignMiddle();`
- L122 _public prototype_ `void OnAlignBottom();`
- L123 _public prototype_ `void OnAlignLeft();`
- L124 _public prototype_ `void OnAlignCenter();`
- L125 _public prototype_ `void OnAlignRight();`
- L127 _public prototype_ `void OnStraightenConnections();`
- L128 _public prototype_ `void OnDistributeNodesH();`
- L129 _public prototype_ `void OnDistributeNodesV();`
- L132 _protected member_ `TWeakObjectPtr<UAvaPlaybackGraph> PlaybackGraphWeak;`
- L134 _protected member_ `TSharedPtr<FUICommandList> GraphEditorCommands;`
- L136 _protected member_ `TSharedPtr<SGraphEditor> GraphEditor;`
- L138 _protected member_ `static TMap<TSubclassOf<UAvaPlaybackNode>, TSubclassOf<UAvaPlaybackEditorGraphNode>> OverrideNodeClasses;`

#### Free symbols / members of external scopes

- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlaybackSelectionChanged, const TArray<UObject*>&);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/AvaPlaybackGraphFactory.h` (Private)


#### class `UAvaPlaybackGraphFactory`  
`class UAvaPlaybackGraphFactory : public UFactory`  
_L9-26_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `UAvaPlaybackGraphFactory();`
- L21 _protected prototype_ `virtual bool CanCreateNew() const override;`
- L22 _protected prototype_ `virtual uint32 GetMenuCategories() const override;`
- L23 _protected prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _protected prototype_ `virtual FString GetDefaultNewAssetName() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/DetailsView/SAvaPlaybackDetailsView.h` (Private)


#### class `SAvaPlaybackDetailsView`  
`class SAvaPlaybackDetailsView : public SCompoundWidget`  
_L13-28_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaPlaybackDetailsView)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaPlaybackGraphEditor>& InPlaybackEditor);`
- L22 _public prototype_ `void OnPlaybackNodeSelectionChanged(const TArray<UObject*>& InSelectedObjects);`
- L25 _protected member_ `TWeakPtr<FAvaPlaybackGraphEditor> PlaybackEditorWeak;`
- L27 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/AvaPlaybackConnectionDrawingPolicy.h` (Private)


#### struct `FAvaPlaybackConnectionDrawingPolicyFactory`  
`struct FAvaPlaybackConnectionDrawingPolicyFactory : public FGraphPanelPinConnectionFactory`  
_L8-25_
- inherits: `FGraphPanelPinConnectionFactory`
- L12 _public function_ `virtual ~FAvaPlaybackConnectionDrawingPolicyFactory() override`
- L17 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionPolicy(const UEdGraphSchema* Schema , int32 InBackLayerID , int32 InFrontLayerID , float ZoomFactor , const FSlateRect& InClippingRect , FSlateWindowElementList& InDrawElements , UEdGraph* InGraphObj) const override;` — FGraphPanelPinConnectionFactory

#### class `FAvaPlaybackConnectionDrawingPolicy`  
`class FAvaPlaybackConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L27-70_
- inherits: `FConnectionDrawingPolicy`
- L45 _protected typedef_ `using FExecPairingMap = TMap<UEdGraphNode*, FTimePair>;` — Map of pairings
- L48 _protected member_ `TMap<UEdGraphNode*, FExecPairingMap> PredecessorNodes;` — Map of nodes that preceded before a given node in the execution sequence (one entry for each pairing)
- L50 _protected member_ `UEdGraph* GraphObject;`
- L52 _protected member_ `FLinearColor ActiveColor;`
- L53 _protected member_ `FLinearColor InactiveColor;`
- L55 _protected member_ `float ActiveWireThickness;`
- L56 _protected member_ `float InactiveWireThickness;`
- L60 _public prototype_ `FAvaPlaybackConnectionDrawingPolicy(int32 InBackLayerID , int32 InFrontLayerID , float ZoomFactor , const FSlateRect& InClippingRect , FSlateWindowElementList& InDrawElements , UEdGraph* InGraphObject);`
- L68 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface

#### struct `FAvaPlaybackConnectionDrawingPolicy::FTimePair`  
`struct FTimePair`  
_L32-42_
- desc: Times for one execution pair within the current graph
- L34 _public member_ `double PredExecTime;`
- L35 _public member_ `double ThisExecTime;`
- L37 _public function_ `FTimePair() : PredExecTime(0.0) , ThisExecTime(0.0)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/AvaPlaybackEditorGraph.h` (Private)


#### class `UAvaPlaybackEditorGraph`  
`class UAvaPlaybackEditorGraph : public UEdGraph`  
_L13-22_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- L18 _public prototype_ `UAvaPlaybackGraph* GetPlaybackGraph() const;`
- L20 _public prototype_ `UAvaPlaybackEditorGraphNode* CreatePlaybackEditorGraphNode(TSubclassOf<UAvaPlaybackEditorGraphNode> NewNodeClass , bool bSelectNewNode = true);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/AvaPlaybackEditorGraphSchema.h` (Private)


#### class `UAvaPlaybackEditorGraphSchema`  
`class UAvaPlaybackEditorGraphSchema : public UEdGraphSchema`  
_L29-72_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L34 _public member_ `static const FLinearColor ActivePinColor;`
- L35 _public member_ `static const FLinearColor InactivePinColor;`
- L38 _public member_ `static const FName PC_ChannelFeed;` — Allowable PinType.PinCategory values
- L39 _public member_ `static const FName PC_Event;`
- L41 _public prototype_ `void CompilePlaybackNodesFromGraphNodes(UEdGraphNode& Node) const;`
- L44 _public prototype_ `bool ConnectionCausesLoop(const UEdGraphPin* InputPin, const UEdGraphPin* OutputPin) const;` — Check whether connecting these pins would cause a loop
- L47 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L48 _public prototype_ `virtual void GetContextMenuActions(UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L49 _public prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L50 _public function_ `virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const override`
- L51 _public function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L52 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;`
- L53 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L54 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L55 _public prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L56 _public prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L57 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L58 _public prototype_ `virtual int32 GetNodeSelectionCount(const UEdGraph* Graph) const override;`
- L59 _public prototype_ `virtual TSharedPtr<FEdGraphSchemaAction> GetCreateCommentAction() const override;`
- L62 _public prototype_ `static void CachePlaybackNodeClasses();`
- L65 _public prototype_ `void GetPlaybackNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder, bool bShowSelectedActions) const;` — Adds actions for creating every type of Playback Node
- L66 _public prototype_ `void GetCommentAction(FGraphActionMenuBuilder& ActionMenuBuilder, const UEdGraph* CurrentGraph = nullptr) const;`
- L69 _protected member_ `static TArray<TSubclassOf<UAvaPlaybackNode>> PlaybackNodeClasses;`
- L71 _protected prototype_ `TSharedPtr<IAvaPlaybackGraphEditor> GetPlaybackGraphEditor(const UEdGraph* Graph) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/AvaPlaybackEditorGraphNode.h` (Private)


#### class `UAvaPlaybackEditorGraphNode`  
`class UAvaPlaybackEditorGraphNode : public UEdGraphNode`  
_L25-115_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- L30 _public prototype_ `UAvaPlaybackGraph* GetPlayback() const;`
- L32 _public prototype_ `void SetPlaybackNode(UAvaPlaybackNode* InPlaybackNode);`
- L34 _public prototype_ `double GetLastTimeTicked();`
- L35 _public prototype_ `double GetChildLastTimeTicked(int32 ChildIndex) const;`
- L37 _public prototype_ `bool CanAddInputPin() const;`
- L38 _public prototype_ `void AddInputPin();`
- L39 _public prototype_ `void CreateInputPin();`
- L41 _public prototype_ `void RemoveInputPin(UEdGraphPin* InGraphPin);`
- L44 _public prototype_ `virtual void PrepareForCopying() override;`
- L45 _public prototype_ `virtual void PostPasteNode() override;`
- L48 _public prototype_ `void PostCopyNode();`
- L51 _public prototype_ `void ResetPlaybackNodeOwner();` — Make sure the PlaybackNode is owned by the Playback Object
- L54 _public prototype_ `virtual TSubclassOf<UAvaPlaybackNode> GetPlaybackNodeClass() const;` — Return which Playback Node this Graph Node should Represent
- L56 _public function_ `UAvaPlaybackNode* GetPlaybackNode() const`
- L63 _protected prototype_ `void CreateInputPins();` — Create all of the input pins required
- L64 _protected prototype_ `void CreateOutputPin();`
- L68 _public prototype_ `bool IsRootNode() const;` — Is this the non-deletable root node
- L70 _public prototype_ `UEdGraphPin* GetOutputPin() const;`
- L71 _public prototype_ `TArray<UEdGraphPin*> GetInputPins() const;`
- L73 _public prototype_ `UEdGraphPin* GetInputPin(int32 InputIndex) const;`
- L74 _public prototype_ `int32 GetInputPinIndex(UEdGraphPin* InInputPin) const;`
- L75 _public prototype_ `int32 GetInputPinCount() const;`
- L84 _public prototype_ `void InsertNewNode(UEdGraphPin* FromPin, UEdGraphPin* NewLinkPin, TSet<UEdGraphNode*>& OutNodeList);` — Handles inserting the node between the FromPin and what the FromPin was original connected to @param FromPin			The pin this node is being spawned from @param NewLinkPin		The new pin the FromPin will connect to @param OutNodeList		Any nodes that are modified will get added to this list for notification purposes
- L87 _public prototype_ `virtual void PostLoad() override;`
- L88 _public prototype_ `virtual void PostEditImport() override;`
- L89 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L93 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L94 _public prototype_ `virtual FText GetTooltipText() const override;`
- L95 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;`
- L96 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L97 _public prototype_ `virtual void ReconstructNode() override;`
- L98 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L99 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L100 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L101 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L104 _public prototype_ `virtual FName GetInputPinName(int32 InputPinIndex) const;`
- L105 _public prototype_ `virtual FName GetInputPinCategory(int32 InputPinIndex) const;`
- L106 _public prototype_ `virtual FName GetInputPinSubCategory(int32 InputPinIndex) const;`
- L107 _public prototype_ `virtual UObject* GetInputPinSubCategoryObject(int32 InputPinIndex) const;`
- L109 _public prototype_ `virtual FName GetOutputPinCategory() const;`
- L114 _protected member_ `TObjectPtr<UAvaPlaybackNode> PlaybackNode;` — `UPROPERTY(VisibleAnywhere, Instanced, Category=Playback)` — The Playback Node this represents

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/AvaPlaybackEditorGraphNode_EventAction.h` (Private)


#### class `UAvaPlaybackEditorGraphNode_EventAction`  
`class UAvaPlaybackEditorGraphNode_EventAction : public UAvaPlaybackEditorGraphNode`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackEditorGraphNode`
- L15 _public prototype_ `virtual TSubclassOf<UAvaPlaybackNode> GetPlaybackNodeClass() const override;`
- L17 _public prototype_ `virtual FName GetInputPinCategory(int32 InputPinIndex) const override;`
- L18 _public prototype_ `virtual FName GetOutputPinCategory() const override;`
- L21 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/AvaPlaybackEditorGraphNode_EventFlow.h` (Private)


#### class `UAvaPlaybackEditorGraphNode_EventFlow`  
`class UAvaPlaybackEditorGraphNode_EventFlow : public UAvaPlaybackEditorGraphNode`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackEditorGraphNode`
- L15 _public prototype_ `virtual TSubclassOf<UAvaPlaybackNode> GetPlaybackNodeClass() const override;`
- L17 _public prototype_ `virtual FName GetInputPinCategory(int32 InputPinIndex) const override;`
- L18 _public prototype_ `virtual FName GetOutputPinCategory() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/AvaPlaybackEditorGraphNode_EventTrigger.h` (Private)


#### class `UAvaPlaybackEditorGraphNode_EventTrigger`  
`class UAvaPlaybackEditorGraphNode_EventTrigger : public UAvaPlaybackEditorGraphNode`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackEditorGraphNode`
- L15 _public prototype_ `virtual TSubclassOf<UAvaPlaybackNode> GetPlaybackNodeClass() const override;`
- L16 _public prototype_ `virtual FName GetOutputPinCategory() const override;`
- L19 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/AvaPlaybackEditorGraphNode_LevelPlayer.h` (Private)


#### class `UAvaPlaybackEditorGraphNode_LevelPlayer`  
`class UAvaPlaybackEditorGraphNode_LevelPlayer : public UAvaPlaybackEditorGraphNode`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackEditorGraphNode`
- L13 _private prototype_ `virtual TSubclassOf<UAvaPlaybackNode> GetPlaybackNodeClass() const override;`
- L14 _private prototype_ `virtual FName GetInputPinCategory(int32 InputPinIndex) const override;`
- L17 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L18 _private prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/AvaPlaybackEditorGraphNode_Root.h` (Private)


#### class `UAvaPlaybackEditorGraphNode_Root`  
`class UAvaPlaybackEditorGraphNode_Root : public UAvaPlaybackEditorGraphNode`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAvaPlaybackEditorGraphNode`
- L13 _private prototype_ `virtual TSubclassOf<UAvaPlaybackNode> GetPlaybackNodeClass() const override;`
- L16 _private prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode interface
- L17 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L18 _private prototype_ `virtual bool CanDuplicateNode() const override;`
- L19 _private prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/Slate/SAvaPlaybackEditorGraphNode.h` (Private)


#### class `SAvaPlaybackEditorGraphNode`  
`class SAvaPlaybackEditorGraphNode : public SGraphNode`  
_L16-36_
- inherits: `SGraphNode`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAvaPlaybackEditorGraphNode)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAvaPlaybackEditorGraphNode* InGraphNode);`
- L24 _public function_ `virtual void PostConstruct()`
- L28 _protected prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;`
- L29 _protected prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`
- L30 _protected prototype_ `virtual FReply OnAddPin() override;`
- L31 _protected prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L35 _protected member_ `TWeakObjectPtr<UAvaPlaybackEditorGraphNode> PlaybackGraphNode;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/Slate/SAvaPlaybackEditorGraphNode_Player.h` (Private)


#### class `SAvaPlaybackEditorGraphNode_Player`  
`class SAvaPlaybackEditorGraphNode_Player : public SAvaPlaybackEditorGraphNode`  
_L15-38_
- inherits: `SAvaPlaybackEditorGraphNode`
- L18 _public prototype_ `SAvaPlaybackEditorGraphNode_Player();`
- L21 _public prototype_ `virtual void PostConstruct() override;`
- L24 _public prototype_ `TSharedRef<SWidget> CreatePreviewWidget();` — Creates a preview viewport if necessary
- L26 _public prototype_ `const FSlateBrush* GetPlayerPreviewBrush() const;`
- L29 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;` — SGraphNode Interface
- L30 _public prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L34 _protected member_ `TWeakObjectPtr<UAvaPlaybackNodePlayer> PlayerNode;`
- L37 _protected member_ `TUniquePtr<FPreviewBrush> PlayerPreviewBrush;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Nodes/Slate/SAvaPlaybackEditorGraphNode_Root.h` (Private)


#### class `SAvaPlaybackEditorGraphNode_Root`  
`class SAvaPlaybackEditorGraphNode_Root : public SAvaPlaybackEditorGraphNode`  
_L12-17_
- inherits: `SAvaPlaybackEditorGraphNode`
- L16 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — Hook that allows derived classes to supply their own SGraphPin derivatives for any pin.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/Pins/Slate/SAvaPlaybackEditorGraphPin_Channel.h` (Private)


#### class `SAvaPlaybackEditorGraphPin_Channel`  
`class SAvaPlaybackEditorGraphPin_Channel : public SGraphPin`  
_L15-42_
- inherits: `SGraphPin`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAvaPlaybackEditorGraphPin_Channel)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L23 _public prototype_ `const FAvaBroadcastOutputChannel* GetChannel() const;`
- L25 _public prototype_ `void UpdateChannelState();`
- L28 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;` — Build the widget we should put into the 'default value' space, shown when nothing connected
- L30 _public prototype_ `FText GetChannelStatusText() const;`
- L32 _public prototype_ `const FSlateBrush* GetChannelStatusBrush() const;`
- L34 _public prototype_ `virtual FSlateColor GetPinColor() const override;`
- L37 _protected member_ `const FSlateBrush* ChannelStateBrush = nullptr;`
- L39 _protected member_ `FText ChannelStateText;`
- L41 _protected member_ `bool bPinEnabled = true;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/SchemaActions/AvaPlaybackAction_NewComment.h` (Private)


#### struct `FAvaPlaybackAction_NewComment`  
`struct FAvaPlaybackAction_NewComment : public FEdGraphSchemaAction`  
_L9-27_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L13 _public prototype_ `FAvaPlaybackAction_NewComment() = default;`
- L15 _public function_ `FAvaPlaybackAction_NewComment(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L22 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2f& Location , bool bSelectNewNode = true) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/SchemaActions/AvaPlaybackAction_NewNode.h` (Private)


#### struct `FAvaPlaybackAction_NewNode`  
`struct FAvaPlaybackAction_NewNode : public FEdGraphSchemaAction`  
_L17-42_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L22 _public prototype_ `FAvaPlaybackAction_NewNode() = default;`
- L24 _public prototype_ `FAvaPlaybackAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping);`
- L27 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2f& Location , bool bSelectNewNode = true) override;`
- L33 _public prototype_ `void SetPlaybackNodeClass(TSubclassOf<UAvaPlaybackNode> InPlaybackNodeClass);`
- L37 _protected prototype_ `void ConnectToSelectedNodes(UAvaPlaybackNode* NewNode, UEdGraph* ParentGraph) const;` — Connects new node to output of selected nodes
- L41 _protected member_ `TSubclassOf<UAvaPlaybackNode> PlaybackNodeClass;` — `UPROPERTY()` — Class of node we want to create

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/Graph/SchemaActions/AvaPlaybackAction_PasteNode.h` (Private)


#### struct `FAvaPlaybackAction_PasteNode`  
`struct FAvaPlaybackAction_PasteNode : public FEdGraphSchemaAction`  
_L9-26_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L13 _public prototype_ `FAvaPlaybackAction_PasteNode() = default;`
- L15 _public function_ `FAvaPlaybackAction_PasteNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L21 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph , UEdGraphPin* FromPin , const FVector2f& Location , bool bSelectNewNode = true) override;` — FEdGraphSchemaAction Interface

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/TabFactories/AvaPlaybackDetailsTabFactory.h` (Private)


#### class `FAvaPlaybackDetailsTabFactory`  
`class FAvaPlaybackDetailsTabFactory : public FAvaPlaybackTabFactory`  
_L7-15_
- inherits: `FAvaPlaybackTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaPlaybackDetailsTabFactory(const TSharedPtr<FAvaPlaybackGraphEditor>& InPlaybackEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/TabFactories/AvaPlaybackEditorGraphTabFactory.h` (Private)


#### class `FAvaPlaybackEditorGraphTabFactory`  
`class FAvaPlaybackEditorGraphTabFactory : public FAvaPlaybackTabFactory`  
_L7-15_
- inherits: `FAvaPlaybackTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaPlaybackEditorGraphTabFactory(const TSharedPtr<FAvaPlaybackGraphEditor>& InPlaybackEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Playback/TabFactories/AvaPlaybackTabFactory.h` (Private)


#### class `FAvaPlaybackTabFactory`  
`class FAvaPlaybackTabFactory : public FWorkflowTabFactory`  
_L10-19_
- inherits: `FWorkflowTabFactory`
- desc: Base class for all Tab Factories in Ava Playback Editor
- L14 _public prototype_ `FAvaPlaybackTabFactory(const FName& InTabID, const TSharedPtr<FAvaPlaybackGraphEditor>& InPlaybackEditor);`
- L18 _protected member_ `TWeakPtr<FAvaPlaybackGraphEditor> PlaybackEditorWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AppModes/AvaRundownAppMode.h` (Private)


#### class `FAvaRundownAppMode`  
`class FAvaRundownAppMode : public FApplicationMode`  
_L10-36_
- inherits: `FApplicationMode`
- L15 _public member_ `static const FName DefaultMode;` — Mode constants
- L18 _public prototype_ `FAvaRundownAppMode(const TSharedPtr<FAvaRundownEditor>& InRundownEditor, const FName& InModeName);`
- L19 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;`
- L21 _public prototype_ `TSharedPtr<FDocumentTabFactory> GetDocumentTabFactory(const FName& InName) const;`
- L23 _public prototype_ `void RegisterDocumentTabFactory(const TSharedPtr<FDocumentTabFactory>& InDocumentTabFactory, const TSharedPtr<FTabManager>& InTabManager = nullptr);`
- L24 _public prototype_ `void UnregisterDocumentTabFactory(const FName& InTabId, const TSharedPtr<FTabManager>& InTabManager);`
- L28 _protected prototype_ `static FText GetLocalizedMode(const FName InMode);`
- L30 _protected member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L33 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — Set of spawnable tabs in the mode
- L35 _protected member_ `TMap<FName, TSharedRef<FDocumentTabFactory>> DocumentTabFactories;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AppModes/AvaRundownDefaultMode.h` (Private)


#### class `FAvaRundownDefaultMode`  
`class FAvaRundownDefaultMode : public FAvaRundownAppMode`  
_L7-11_
- inherits: `FAvaRundownAppMode`
- L10 _public prototype_ `FAvaRundownDefaultMode(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AssetDefinition_AvaRundown.h` (Private)


#### class `UAssetDefinition_AvaRundown`  
`class UAssetDefinition_AvaRundown : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AssetDefinition_AvaRundownMacroCollection.h` (Private)


#### class `UAssetDefinition_AvaRundownMacroCollection`  
`class UAssetDefinition_AvaRundownMacroCollection : public UAssetDefinitionDefault`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AvaRundownCommands.h` (Private)


#### class `FAvaRundownCommands`  
`class FAvaRundownCommands : public TCommands<FAvaRundownCommands>`  
_L11-61_
- inherits: `TCommands<FAvaRundownCommands>`
- L15 _public function_ `FAvaRundownCommands() : TCommands<FAvaRundownCommands>(TEXT("AvaRundown") , LOCTEXT("MotionDesignRundownCommands", "Motion Design Rundown") , NAME_None , FAvaMediaEditorStyle::Get().GetStyleSetName())`
- L24 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L27 _public member_ `TSharedPtr<FUICommandInfo> AddTemplate;` — Page List Commands
- L28 _public member_ `TSharedPtr<FUICommandInfo> CreatePageInstanceFromTemplate;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> CreateComboTemplate;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> RemovePage;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> RenumberPage;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ReimportPage;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> EditPageSource;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ExportPagesToRundown;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ExportPagesToJson;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ExportPagesToXml;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> Play;` — Show Control / Rundown Commands
- L40 _public member_ `TSharedPtr<FUICommandInfo> UpdateValues;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> Stop;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ForceStop;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> Continue;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> PlayNext;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> LoadAllPages;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> LoadNextPages;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> LoadSelectedPages;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> PreviewFrame;` — Preview Control / Rundown Commands
- L51 _public member_ `TSharedPtr<FUICommandInfo> PreviewPlay;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> PreviewStop;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> PreviewForceStop;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> PreviewContinue;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> PreviewPlayNext;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> TakeToProgram;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> ResetValuesToDefaults;` — Remote Control Commands
- L60 _public member_ `TSharedPtr<FUICommandInfo> ResetValuesToTemplate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "AvaRundownCommands"`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AvaRundownEditorMacroCommands.h` (Private)


#### enum `EAvaRundownEditorMacroCommand`  
`enum class EAvaRundownEditorMacroCommand : uint8`  
_L9-30_
- reflection: `UENUM()`
- desc: Available macro commands for Ava rundown editor.
- L11 _public enumerator_ `None`
- L13 _public enumerator_ `LoadPage` — Playback commands
- L14 _public enumerator_ `UnloadPage`
- L15 _public enumerator_ `TakeIn`
- L16 _public enumerator_ `TakeOut`
- L17 _public enumerator_ `ForceTakeOut`
- L18 _public enumerator_ `TakeNext`
- L19 _public enumerator_ `Continue`
- L20 _public enumerator_ `PreviewIn`
- L21 _public enumerator_ `PreviewOut`
- L22 _public enumerator_ `ForcePreviewOut`
- L23 _public enumerator_ `PreviewNext`
- L24 _public enumerator_ `ContinuePreview`
- L25 _public enumerator_ `TakeToProgram`
- L26 _public enumerator_ `StopPageTransition`
- L27 _public enumerator_ `StartChannel`
- L28 _public enumerator_ `StopChannel`
- L29 _public enumerator_ `PreviewFrame`

#### struct `FAvaRundownEditorMacroCommands`  
`struct FAvaRundownEditorMacroCommands`  
_L32-36_
- L34 _public prototype_ `static FName GetCommandName(EAvaRundownEditorMacroCommand InCommand);`
- L35 _public prototype_ `static FName GetShortCommandName(EAvaRundownEditorMacroCommand InCommand);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AvaRundownEditorSettings.h` (Private)


#### class `UAvaRundownEditorSettings`  
`class UAvaRundownEditorSettings : public UDeveloperSettings`  
_L12-75_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Rundown"))`
- inherits: `UDeveloperSettings`
- L17 _public prototype_ `UAvaRundownEditorSettings();`
- L19 _public prototype_ `static const UAvaRundownEditorSettings* Get();`
- L20 _public prototype_ `static UAvaRundownEditorSettings* GetMutable();`
- L23 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L31 _public member_ `bool bShouldStopPagesOnClose = true;` — `UPROPERTY(Config, EditAnywhere, Category="Rundown")` — Configuring the default page action when closing the editor. By default it will stop the pages.
- L35 _public member_ `bool bPreviewCheckerBoard = false;` — `UPROPERTY(Config, EditAnywhere, Category="Preview")` — Shows the checker board in preview
- L39 _public member_ `bool bAutoStartPreviewBroadcastChannel = true;` — `UPROPERTY(Config, EditAnywhere, Category="Preview")` — Automatically start the currently selected preview broadcast channel when a preview playback starts.
- L43 _public member_ `bool bPageDetailsShowProperties = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Page Details", meta = (DisplayName = "Show RC Controlled Properties"))` — Whether to show controller properties in Rundown Page Details
- L47 _public member_ `TSoftObjectPtr<UAvaRundownMacroCollection> MacroCollection;` — `UPROPERTY(Config, EditAnywhere, Category="Macros")` — Current macro collection used by the rundown editor.
- L50 _public member_ `EAvaRundownPageSet PreviewContinueActionPageSet = EAvaRundownPageSet::SelectedOrPlaying;` — `UPROPERTY(Config, EditAnywhere, Category="Page Actions")`
- L53 _public member_ `EAvaRundownPageSet PreviewOutActionPageSet = EAvaRundownPageSet::SelectedOrPlaying;` — `UPROPERTY(Config, EditAnywhere, Category="Page Actions")`
- L56 _public member_ `EAvaRundownPageSet ContinueActionPageSet = EAvaRundownPageSet::SelectedOrPlaying;` — `UPROPERTY(Config, EditAnywhere, Category="Page Actions")`
- L59 _public member_ `EAvaRundownPageSet TakeOutActionPageSet = EAvaRundownPageSet::SelectedOrPlaying;` — `UPROPERTY(Config, EditAnywhere, Category="Page Actions")`
- L62 _public member_ `EAvaRundownPageSet UpdateValuesActionPageSet = EAvaRundownPageSet::SelectedOrPlaying;` — `UPROPERTY(Config, EditAnywhere, Category="Page Actions")`
- L70 _public member_ `bool bAutoStartRundownServer = false;` — `UPROPERTY(Config, EditAnywhere, Category="Server")` — Whether rundown server is started automatically when the editor is launched. For game mode or packaged games, the rundown server can be launched with the command line -MotionDesignRundownServerStart[=ServerName].
- L74 _public member_ `FString RundownServerName;` — `UPROPERTY(Config, EditAnywhere, Category="Server")` — Name given to the rundown server. If empty, the server name will be the host name.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AvaRundownEditorUtils.h` (Private)


#### struct `UE::AvaRundownEditor::Utils::FImportTemplateMap`  
`struct FImportTemplateMap`  
_L47-66_
- desc: Map of "Source TemplateId" to "Destination Template Id". During the import of new pages, we need to keep track of the destination template Id, i.e. Source Page's template id -> actual id in rundown.
- L49 _public member_ `TMap<int32, int32> TemplateIds;`
- L51 _public function_ `void Add(int32 InSourceTemplateId, int32 InDestinationTemplateId)`
- L56 _public function_ `bool HasSourceTemplateId(int32 InSourceTemplateId) const`
- L61 _public function_ `int32 GetTemplateId(int32 InSourceTemplateId) const`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AvaRundownEditor` (scope `UE`)
- L15 _namespace_ `namespace Utils` (scope `UE::AvaRundownEditor`)
- L17 _prototype_ `FString GetImportFilepath(const TCHAR* InFileDescription, const TCHAR* InExtension);` (scope `UE::AvaRundownEditor::Utils`)
- L18 _prototype_ `FString GetExportFilepath(const UObject* InObjectToExport, const TCHAR* InFileDescription, const TCHAR* InExtension);` (scope `UE::AvaRundownEditor::Utils`)
- L19 _prototype_ `FString GetSaveAssetAsPath(const FString& InDefaultPath, const FString& InDefaultAssetName);` (scope `UE::AvaRundownEditor::Utils`)
- L21 _prototype_ `FString SerializePagesToJson(UAvaRundown* InRundown, const TArray<int32>& InPageIds);` (scope `UE::AvaRundownEditor::Utils`)
- L22 _prototype_ `TArray<FAvaRundownPage> DeserializePagesFromJson(const FString& InJsonString);` (scope `UE::AvaRundownEditor::Utils`)
- L30 _prototype_ `TStrongObjectPtr<UAvaRundown> ExportPagesToRundown(const UAvaRundown* InRundown, const TArray<int32>& InPageIds);` (scope `UE::AvaRundownEditor::Utils`) — @brief Creates a transient rundown with only the specified pages. @param InRundown Source Rundown. @param InPageIds Pages to copy to the new rundown. @return Created rundown.
- L32 _prototype_ `bool SaveRundownToXml(const UAvaRundown* InRundown, FArchive& InArchive, EXmlSerializationEncoding InXmlEncoding);` (scope `UE::AvaRundownEditor::Utils`)
- L33 _prototype_ `bool SaveRundownToXml(const UAvaRundown* InRundown, const TCHAR* InFilepath, EXmlSerializationEncoding InXmlEncoding);` (scope `UE::AvaRundownEditor::Utils`)
- L39 _prototype_ `bool CanLoadRundownFromFile(const TCHAR* InFilepath);` (scope `UE::AvaRundownEditor::Utils`) — Check the file extenstion to see if it is a supported format to use with the deserializing functions (LoadRundownFrom...).
- L68 _prototype_ `TArray<int32> ImportTemplatePages(UAvaRundown* InRundown, const TArray<FAvaRundownPage>& InSourceTemplates, FImportTemplateMap& OutImportedTemplateIds);` (scope `UE::AvaRundownEditor::Utils`)
- L85 _prototype_ `TArray<int32> ImportInstancedPages( UAvaRundown* InRundown, const FAvaRundownPageListReference& InPageListReference, const TArray<FAvaRundownPage>& InSourcePages, const TArray<FAvaRundownPage>& InSourceTemplates, FImportTemplateMap& InOutImportedTemplateIds, const FAvaRundownPageInsertPosition& InInsertPosition = FAvaRundownPageInsertPosition());` (scope `UE::AvaRundownEditor::Utils`) — @brief Import the given pages to the rundown. @param InRundown Rundown that receives the new pages. @param InPageListReference Reference to the page list to which the pages will be added. @param InSourcePages Source pages @param InSourceTemplates Source templates, if available, for the source pages. @param InOutImportedTemplateIds Imported template ids to make the correspondence between the source page template id and what was imported. @param InInsertPosition Indicate where in the page list to insert the new pages. @return Array of added page ids. Importing pages is a non-trivial operation. It includes adding missing templates. The biggest issue is maintaining the link between the page's template id and the imported templates. If available, the source templates can be used to reconstruct this relationship by finding an exact match with the templates of the destination rundown.
- L100 _prototype_ `TArray<int32> ImportInstancedPagesFromRundown( UAvaRundown* InRundown, const UAvaRundown* InSourceRundown, const FAvaRundownPageInsertPosition& InInsertPosition = FAvaRundownPageInsertPosition());` (scope `UE::AvaRundownEditor::Utils`) — @brief Import/Merge a rundown into another rundown. @param InRundown Destination rundown. @param InSourceRundown Source rundown to merge in the destination. @param InInsertPosition Indicate where in the page list to insert the new pages. @return Array of added page ids.
- L105 _prototype_ `UAvaRundown* SaveDuplicateRundown(UAvaRundown* InSourceRundown, const FString& InAssetName, const FString& InPackagePath);` (scope `UE::AvaRundownEditor::Utils`)
- L107 _prototype_ `bool MergeDefaultRemoteControlValues(const TArray<TSharedPtr<FAvaRundownManagedInstance>>& InManagedInstances, FAvaPlayableRemoteControlValues& OutMergedValues);` (scope `UE::AvaRundownEditor::Utils`)
- L108 _prototype_ `EAvaPlayableRemoteControlChanges UpdateDefaultRemoteControlValues(UAvaRundown* InRundown, const TArray<int32>& InSelectedPageIds);` (scope `UE::AvaRundownEditor::Utils`)
- L113 _prototype_ `bool ForceUpdatePageSummary(int32 InPageId, UAvaRundown* InRundown);` (scope `UE::AvaRundownEditor::Utils`) — Utility function to force update the page summary from the controller values.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AvaRundownExporter.h` (Private)


#### class `UAvaRundownExporter`  
`class UAvaRundownExporter : public UExporter`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L14 _public prototype_ `UAvaRundownExporter();`
- L17 _public prototype_ `virtual bool ExportText(const FExportObjectInnerContext* InContext, UObject* InObject, const TCHAR* InType, FOutputDevice& InAr, FFeedbackContext* InWarn, uint32 InPortFlags) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AvaRundownFactory.h` (Private)


#### class `UAvaRundownFactory`  
`class UAvaRundownFactory : public UFactory`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `UAvaRundownFactory();`
- L21 _protected prototype_ `virtual uint32 GetMenuCategories() const override;`
- L22 _protected prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _protected prototype_ `virtual FString GetDefaultNewAssetName() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AvaRundownMacroCollectionFactory.h` (Private)


#### class `UAvaRundownMacroCollectionFactory`  
`class UAvaRundownMacroCollectionFactory : public UFactory`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L13 _private prototype_ `UAvaRundownMacroCollectionFactory();`
- L16 _private prototype_ `virtual uint32 GetMenuCategories() const override;`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L18 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/ChannelLayerStatus/SAvaRundownChannelLayerStatusList.h` (Private)


#### struct `FAvaRundownChannelLayerEntry`  
`struct FAvaRundownChannelLayerEntry`  
_L15-23_
- L17 _public member_ `FName ChannelName;`
- L18 _public member_ `FName LayerName;`
- L19 _public member_ `int32 PageId;`
- L20 _public member_ `FText LayerDescription;`
- L21 _public member_ `FLinearColor ComboPageColor;`
- L22 _public member_ `bool bOverridden;`

#### class `SAvaRundownChannelLayerStatusList`  
`class SAvaRundownChannelLayerStatusList : public SCompoundWidget`  
_L28-48_
- inherits: `SCompoundWidget`
- desc: Widget containing the Status of all Channel Layers in Broadcast. It contains a list of SAvaRundownChannelLayerStatus widgets
- L31 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownChannelLayerStatusList)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L38 _protected member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L39 _protected member_ `TSharedPtr<SWrapBox> Container;`
- L40 _protected member_ `FDelegateHandle UpdateHandle;`
- L43 _protected member_ `TMap<FName, TMap<FName, FAvaRundownChannelLayerEntry>> ChannelLayerStatusList;` — Channel,    Layer, Details
- L45 _protected prototype_ `void RefreshList();`
- L47 _protected prototype_ `void OnPlaybackInstanceStatusChanged(const FAvaPlaybackInstance& InPlaybackInstance);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/ChannelStatus/SAvaRundownChannelStatus.h` (Private)


#### class `SAvaRundownChannelStatus`  
`class SAvaRundownChannelStatus : public SCompoundWidget`  
_L18-34_
- inherits: `SCompoundWidget`
- desc: Widget displaying the Status of a Single Channel
- L21 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownChannelStatus)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAvaBroadcastOutputChannel& InChannel);`
- L28 _public prototype_ `void OnChannelChanged(const FAvaBroadcastOutputChannel& InChannel, EAvaBroadcastChannelChange InChange);`
- L31 _protected member_ `FName ChannelName;`
- L33 _protected member_ `TSharedPtr<SImage> ChannelStatusIcon;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/ChannelStatus/SAvaRundownChannelStatusList.h` (Private)


#### class `SAvaRundownChannelStatusList`  
`class SAvaRundownChannelStatusList : public SCompoundWidget`  
_L19-40_
- inherits: `SCompoundWidget`
- desc: Widget containing the Status of all Channels in Broadcast. It contains a list of SAvaRundownChannelStatus widgets
- L22 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownChannelStatusList)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `void RefreshList();`
- L32 _public prototype_ `void OnBroadcastChanged(EAvaBroadcastChange InChange);`
- L35 _protected member_ `TSharedPtr<SWrapBox> WrapBox;`
- L37 _protected member_ `TWeakObjectPtr<UAvaBroadcast> BroadcastWeak;`
- L39 _protected member_ `TMap<FName, TSharedPtr<SAvaRundownChannelStatus>> ChannelStatusSlots;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Customization/AvaRundownMacroCommandCustomization.h` (Private)


#### class `FAvaRundownMacroCommandCustomization`  
`class FAvaRundownMacroCommandCustomization : public IPropertyTypeCustomization`  
_L10-25_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;`
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;`
- L21 _private prototype_ `void RemoveMacroCommandButton_OnClick();`
- L24 _private member_ `TSharedPtr<IPropertyHandle> MacroCommandHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Customization/AvaRundownMacroKeyBindingCustomization.h` (Private)


#### class `FAvaRundownMacroKeyBindingCustomization`  
`class FAvaRundownMacroKeyBindingCustomization : public IPropertyTypeCustomization`  
_L10-22_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InPropertyTypeCustomizationUtils) override;`
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InPropertyTypeCustomizationUtils) override;`
- L21 _private prototype_ `void AddInputChord(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InStructBuilder);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Customization/SAvaRundownMacroCommandSelector.h` (Private)


#### class `SAvaRundownMacroCommandSelector`  
`class SAvaRundownMacroCommandSelector : public SCompoundWidget`  
_L10-49_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownMacroCommandSelector)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L27 _public typedef_ `using FCommandItemPtr = TSharedPtr<FCommandItem>;`
- L29 _public prototype_ `TSharedRef<SWidget> GenerateWidget(FCommandItemPtr InItem);`
- L31 _public prototype_ `void HandleSelectionChanged(SComboBox<FCommandItemPtr>::NullableOptionType InProposedSelection, ESelectInfo::Type InSelectInfo);`
- L33 _public prototype_ `FText GetDisplayTextFromProperty() const;`
- L35 _public prototype_ `void OnComboBoxOpening();`
- L38 _protected prototype_ `FCommandItemPtr GetItemFromProperty() const;`
- L40 _protected prototype_ `FText GetDisplayTextFromItem(const FCommandItemPtr& InItem) const;`
- L42 _protected prototype_ `void UpdateCommandItems();`
- L44 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L46 _protected member_ `TSharedPtr<SComboBox<FCommandItemPtr>> CommandCombo;`
- L48 _protected member_ `static TArray<FCommandItemPtr> CommandItems;`

#### struct `SAvaRundownMacroCommandSelector::FCommandItem`  
`struct FCommandItem`  
_L19-25_
- L21 _public member_ `int32 EnumIndex = 0;`
- L22 _public member_ `FName Name;`
- L24 _public function_ `FCommandItem(int32 InEnumIndex, FName InName) : EnumIndex(InEnumIndex), Name(InName)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/AvaRundownPageDetailView.h` (Private)


#### class `UAvaRundownPageDetailView`  
`class UAvaRundownPageDetailView : public UObject`  
_L13-21_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class used to expose part of the rundown page data to the detail panel.
- L20 _public member_ `TArray<FInstancedStruct> Commands;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Page Data", meta = (ExcludeBaseStruct, BaseStruct = "/Script/AvalancheMedia.AvaRundownPageCommand"))` — Page Commands

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Controllers/AvaRundownPageControllerContextMenu.h` (Private)


#### class `FAvaRundownPageControllerContextMenu`  
`class FAvaRundownPageControllerContextMenu : public TSharedFromThis<FAvaRundownPageControllerContextMenu>`  
_L18-44_
- inherits: `TSharedFromThis<FAvaRundownPageControllerContextMenu>`
- L21 _public prototype_ `FAvaRundownPageControllerContextMenu(const TWeakPtr<FUICommandList>& InCommandList);`
- L23 _public prototype_ `TSharedRef<SWidget> GeneratePageContextMenuWidget(const TWeakPtr<FAvaRundownEditor>& InRundownEditorWeak , const FAvaRundownPage& InRundownPage , const TWeakPtr<SAvaRundownRCControllerPanel>& InControllerListWidgetWeak);`
- L27 _public prototype_ `bool HasValidSelectedItems() const;`
- L30 _private prototype_ `void PopulatePageContextMenu(UToolMenu& InMenu, UAvaRundownPageControllerContext* const InContext);`
- L32 _private prototype_ `void BindCommands(const TWeakPtr<FUICommandList>& InCommandListWeak);`
- L34 _private prototype_ `void ResetValuesToDefaults(const bool bInUseTemplateValues);`
- L35 _private prototype_ `bool CanResetValuesToDefaults(const bool bInUseTemplateValues) const;`
- L37 _private prototype_ `TArray<TWeakPtr<FAvaRundownRCControllerItem>> GetSelectedControllerItems() const;`
- L39 _private prototype_ `UAvaRundown* GetContextRundown() const;`
- L41 _private member_ `TWeakPtr<FUICommandList> CommandListWeak;`
- L43 _private member_ `TWeakObjectPtr<UAvaRundownPageControllerContext> CurrentContext;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Controllers/AvaRundownRCControllerItem.h` (Private)


#### class `FAvaRundownRCControllerItem`  
`class FAvaRundownRCControllerItem : public TSharedFromThis<FAvaRundownRCControllerItem>`  
_L16-47_
- inherits: `TSharedFromThis<FAvaRundownRCControllerItem>`
- L19 _public prototype_ `FAvaRundownRCControllerItem(int32 InInstanceIndex, FName InAssetName, URCController* InController, const TSharedRef<IDetailTreeNode>& InTreeNode, const FAvaPlayableRemoteControlPresetInfo& InPresetInfo);`
- L21 _public prototype_ `TSharedRef<ITableRow> CreateWidget(TSharedRef<SAvaRundownRCControllerPanel> InControllerPanel, const TSharedRef<STableViewBase>& InOwnerTable) const;`
- L23 _public function_ `FText GetDisplayName() const`
- L24 _public function_ `FText GetDescriptionText() const`
- L25 _public function_ `FText GetToolTipText() const`
- L26 _public function_ `const FNodeWidgets& GetNodeWidgets() const`
- L28 _public function_ `int32 GetInstanceIndex() const`
- L29 _public function_ `int32 GetDisplayIndex() const`
- L30 _public function_ `FName GetAssetName() const`
- L32 _public prototype_ `URCController* GetController() const;`
- L35 _public prototype_ `void ExecuteController() const;` — Executes the behaviors of the controller that this item references
- L38 _private member_ `int32 InstanceIndex = 0;`
- L39 _private member_ `int32 DisplayIndex = 0;`
- L40 _private member_ `FName AssetName;`
- L41 _private member_ `FText DisplayNameText;`
- L42 _private member_ `FText DescriptionText;`
- L43 _private member_ `FText ToolTipText;`
- L44 _private member_ `FNodeWidgets NodeWidgets;`
- L46 _private member_ `TWeakObjectPtr<URCController> ControllerWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Controllers/SAvaRundownRCControllerItemRow.h` (Private)


#### class `SAvaRundownRCControllerItemRow`  
`class SAvaRundownRCControllerItemRow : public SMultiColumnTableRow<FAvaRundownRCControllerItemPtr>`  
_L11-28_
- inherits: `SMultiColumnTableRow<FAvaRundownRCControllerItemPtr>`
- L14 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownRCControllerItemRow)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<SAvaRundownRCControllerPanel> InControllerPanel, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedPtr<const FAvaRundownRCControllerItem>& InRowItem);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L23 _protected prototype_ `EVisibility GetExecuteButtonVisibility() const;`
- L24 _protected prototype_ `FReply OnExecuteController();`
- L26 _protected member_ `TWeakPtr<const FAvaRundownRCControllerItem> ItemPtrWeak;`
- L27 _protected member_ `TWeakPtr<SAvaRundownRCControllerPanel> ControllerPanelWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Controllers/SAvaRundownRCControllerPanel.h` (Private)


#### class `SAvaRundownRCControllerPanel`  
`class SAvaRundownRCControllerPanel : public SCompoundWidget`  
_L30-112_
- inherits: `SCompoundWidget`
- L33 _public member_ `static const FLazyName ControllerColumnName;`
- L34 _public member_ `static const FLazyName DescriptionColumnName;`
- L35 _public member_ `static const FLazyName ValueColumnName;`
- L36 _public member_ `static const FLazyName ExecuteColumnName;`
- L38 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownRCControllerPanel)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L43 _public prototype_ `bool HasRemoteControlPreset(const URemoteControlPreset* InPreset) const;`
- L45 _public prototype_ `void Refresh(const TArray<int32>& InSelectedPageIds);`
- L47 _public prototype_ `TSharedRef<ITableRow> OnGenerateControllerRow(FAvaRundownRCControllerItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L49 _public prototype_ `const TArray<FAvaRundownRCControllerItemPtr> GetSelectedControllerItems() const;`
- L51 _public prototype_ `void UpdatePageSummary(bool bInForceUpdate);`
- L55 _private prototype_ `FReply OnExecuteAllControllers();` — Executes all the controllers from the items in this panel, in array order
- L57 _private prototype_ `void UpdatePropertyRowGenerators(int32 InNumGenerators);`
- L59 _private prototype_ `void RefreshForManagedInstance(int32 InInstanceIndex, const FAvaRundownManagedInstance& InManagedInstance, const FAvaRundownPage& InPage);`
- L62 _private prototype_ `void UpdateDefaultValuesAndRefresh(const TArray<int32>& InSelectedPageIds);` — Update the given pages remote control values from the defaults then refresh the widget.
- L64 _private function_ `void OnRemoteControlControllerAdded(URemoteControlPreset* InPreset, const FName NewControllerName, const FGuid& InControllerId)`
- L65 _private function_ `void OnRemoteControlControllerRemoved(URemoteControlPreset* InPreset, const FGuid& InControllerId)`
- L66 _private function_ `void OnRemoteControlControllerRenamed(URemoteControlPreset* InPreset, const FName InOldLabel, const FName InNewLabel)`
- L67 _private prototype_ `void OnRemoteControlControllerModified(URemoteControlPreset* InPreset, const TSet<FGuid>& InModifiedControllerIds);`
- L68 _private prototype_ `void BindRemoteControlDelegates(URemoteControlPreset* InPreset);`
- L70 _private prototype_ `const FAvaPlayableRemoteControlValue* GetSelectedPageControllerValue(const URCVirtualPropertyBase* InController) const;`
- L71 _private prototype_ `bool SetSelectedPageControllerValue(const URCVirtualPropertyBase* InController, const FAvaPlayableRemoteControlValue& InValue) const;`
- L73 _private prototype_ `UAvaRundown* GetRundown() const;`
- L74 _private prototype_ `const FAvaRundownPage& GetActivePage(const UAvaRundown* InRundown) const;`
- L75 _private function_ `const FAvaRundownPage& GetActivePage() const`
- L76 _private prototype_ `FAvaRundownPage& GetActivePageMutable(UAvaRundown* InRundown) const;`
- L77 _private function_ `FAvaRundownPage& GetActivePageMutable() const`
- L79 _private prototype_ `TSharedPtr<SWidget> GetContextMenuContent();`
- L81 _private member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L99 _private member_ `TArray<TUniquePtr<FPropertyRowGeneratorWrapper>> PropertyRowGenerators;`
- L101 _private member_ `FAvaRundownManagedInstanceHandles ManagedHandles;`
- L103 _private member_ `TSharedPtr<SListView<FAvaRundownRCControllerItemPtr>> ControllerContainer;`
- L105 _private member_ `TArray<FAvaRundownRCControllerItemPtr> ControllerItems;`
- L107 _private member_ `int32 ActivePageId = -1;`
- L109 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L111 _private member_ `TSharedPtr<FAvaRundownPageControllerContextMenu> ContextMenu;`

#### class `SAvaRundownRCControllerPanel::FPropertyRowGeneratorWrapper`  
`class FPropertyRowGeneratorWrapper : public FNotifyHook`  
_L83-97_
- inherits: `FNotifyHook`
- L86 _public member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;`
- L87 _public member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeak;`
- L88 _public member_ `SAvaRundownRCControllerPanel* ParentPanel = nullptr;`
- L89 _public member_ `TSet<FProperty*> OngoingPropertyChanges;`
- L91 _public prototype_ `FPropertyRowGeneratorWrapper(SAvaRundownRCControllerPanel* InParentPanel);`
- L92 _public prototype_ `virtual ~FPropertyRowGeneratorWrapper();`
- L95 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`

#### Free symbols / members of external scopes

- L28 _typedef_ `using FAvaRundownRCControllerItemPtr = TSharedPtr<FAvaRundownRCControllerItem>;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Properties/AvaRundownPagePropertyContextMenu.h` (Private)


#### class `FAvaRundownPagePropertyContextMenu`  
`class FAvaRundownPagePropertyContextMenu : public TSharedFromThis<FAvaRundownPagePropertyContextMenu>`  
_L18-44_
- inherits: `TSharedFromThis<FAvaRundownPagePropertyContextMenu>`
- L21 _public prototype_ `FAvaRundownPagePropertyContextMenu(const TWeakPtr<FUICommandList>& InCommandListWeak);`
- L23 _public prototype_ `TSharedRef<SWidget> GeneratePageContextMenuWidget(const TWeakPtr<FAvaRundownEditor>& InRundownEditorWeak , const FAvaRundownPage& InRundownPage , const TWeakPtr<SAvaRundownPageRemoteControlProps>& InPropertyListWidgetWeak);`
- L27 _public prototype_ `bool HasValidSelectedItems() const;`
- L30 _private prototype_ `void PopulatePageContextMenu(UToolMenu& InMenu, UAvaRundownPagePropertyContext* const InContext);`
- L32 _private prototype_ `void BindCommands(const TWeakPtr<FUICommandList>& InCommandListWeak);`
- L34 _private prototype_ `void ResetValuesToDefaults(const bool bInUseTemplateValues);`
- L35 _private prototype_ `bool CanResetValuesToDefaults(const bool bInUseTemplateValues) const;`
- L37 _private prototype_ `TArray<TWeakPtr<FAvaRundownRCFieldItem>> GetSelectedPropertyItems() const;`
- L39 _private prototype_ `UAvaRundown* GetContextRundown() const;`
- L41 _private member_ `TWeakPtr<FUICommandList> CommandListWeak;`
- L43 _private member_ `TWeakObjectPtr<UAvaRundownPagePropertyContext> CurrentContext;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Properties/AvaRundownPageRCObject.h` (Private)


#### class `FAvaRundownPageRCObject`  
`class FAvaRundownPageRCObject`  
_L18-45_
- desc: A class containing the information of a UObject exposed to RC
- L21 _public prototype_ `explicit FAvaRundownPageRCObject(UObject* InObject);`
- L23 _public prototype_ `void Initialize(FNotifyHook* InNotifyHook);`
- L25 _public prototype_ `TSharedPtr<IDetailTreeNode> FindTreeNode(const FString& InPathInfo) const;`
- L27 _public function_ `bool operator==(const FAvaRundownPageRCObject& InOther) const`
- L37 _public prototype_ `void CacheTreeNodes();`
- L40 _private member_ `FObjectKey ObjectKey;`
- L42 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;`
- L44 _private member_ `TMap<FString, TSharedRef<IDetailTreeNode>> TreeNodeMap;`

#### Free symbols / members of external scopes

- L32 _function_ `friend uint32 GetTypeHash(const FAvaRundownPageRCObject& InObject)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Properties/Item/AvaRundownRCDetailTreeNodeItem.h` (Private)


#### class `FAvaRundownRCDetailTreeNodeItem`  
`class FAvaRundownRCDetailTreeNodeItem : public FAvaRundownRCFieldItem`  
_L10-35_
- inherits: `FAvaRundownRCFieldItem`
- L15 _public prototype_ `static TSharedPtr<FAvaRundownRCDetailTreeNodeItem> CreateItem(const TSharedRef<SAvaRundownPageRemoteControlProps>& InPropertyPanel , const TSharedRef<FRemoteControlProperty>& InPropertyEntity , bool bInControlled);`
- L19 _public prototype_ `void Initialize(TSharedRef<IDetailTreeNode> InDetailTreeNode);`
- L22 _public prototype_ `virtual FStringView GetPath() const override;`
- L23 _public prototype_ `virtual void Refresh(const TSharedRef<SAvaRundownPageRemoteControlProps>& InPropertyPanel) override;`
- L27 _private prototype_ `void RefreshChildren();`
- L29 _private member_ `TWeakPtr<FRemoteControlProperty> PropertyEntityWeak;`
- L31 _private member_ `TSharedPtr<IDetailTreeNode> DetailTreeNode;`
- L34 _private member_ `FString FieldPath;` — Cached path of the Field

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Properties/Item/AvaRundownRCFieldItem.h` (Private)


#### class `FAvaRundownRCFieldItem`  
`class FAvaRundownRCFieldItem : public TSharedFromThis<FAvaRundownRCFieldItem>`  
_L15-60_
- inherits: `TSharedFromThis<FAvaRundownRCFieldItem>`
- L18 _public prototype_ `static TSharedPtr<FAvaRundownRCFieldItem> CreateItem(const TSharedRef<SAvaRundownPageRemoteControlProps>& InPropertyPanel , const TSharedRef<FRemoteControlEntity>& InEntity , bool bInControlled);`
- L22 _public prototype_ `FAvaRundownRCFieldItem();`
- L24 _public prototype_ `virtual ~FAvaRundownRCFieldItem() = default;`
- L26 _public function_ `TSharedPtr<FRemoteControlEntity> GetEntity() const`
- L31 _public function_ `bool IsEntityControlled() const`
- L36 _public function_ `virtual void Refresh(const TSharedRef<SAvaRundownPageRemoteControlProps>& InPropertyPanel)`
- L38 _public function_ `TConstArrayView<TSharedPtr<FAvaRundownRCFieldItem>> GetChildren() const`
- L43 _public prototype_ `TSharedRef<ITableRow> CreateWidget(const TSharedRef<SAvaRundownPageRemoteControlProps>& InPropertyPanel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L45 _public function_ `const FNodeWidgets& GetNodeWidgets() const`
- L50 _public prototype_ `virtual FStringView GetPath() const;`
- L53 _protected member_ `TWeakPtr<FRemoteControlEntity> EntityOwnerWeak;`
- L55 _protected member_ `TArray<TSharedPtr<FAvaRundownRCFieldItem>> Children;`
- L57 _protected member_ `FNodeWidgets NodeWidgets;`
- L59 _protected member_ `bool bEntityControlled = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Properties/Item/AvaRundownRCFunctionItem.h` (Private)


#### class `FAvaRundownRCFunctionItem`  
`class FAvaRundownRCFunctionItem : public FAvaRundownRCFieldItem`  
_L10-23_
- inherits: `FAvaRundownRCFieldItem`
- L13 _public prototype_ `static TSharedPtr<FAvaRundownRCFunctionItem> CreateItem(const TSharedRef<SAvaRundownPageRemoteControlProps>& InPropertyPanel , const TSharedRef<FRemoteControlFunction>& InFunctionEntity , bool bInControlled);`
- L18 _private prototype_ `void Initialize();`
- L20 _private prototype_ `FText GetLabel() const;`
- L22 _private prototype_ `FReply OnFunctionButtonClicked() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Properties/SAvaRundownPageRemoteControlProps.h` (Private)


#### class `FAvaRundownPageRCPropsNotifyHook`  
`class FAvaRundownPageRCPropsNotifyHook : public FNotifyHook`  
_L53-58_
- inherits: `FNotifyHook`
- desc: Note: Making a separate object for notify hook to break the SharedPtr circular dependency: PanelWidget ->(strong) ItemWidget -> (strong) Hook -> (weak) PanelWidget The ItemWidget has a weak ptr on the PanelWidget, but the Hook needs to be strong to match ownership with the PropertyRowGenerator that is using the Hook.
- L57 _public prototype_ `virtual ~FAvaRundownPageRCPropsNotifyHook() = default;` — Need to define a virtual destructor because FNotifyHook doesn't.

#### class `SAvaRundownPageRemoteControlProps`  
`class SAvaRundownPageRemoteControlProps : public SCompoundWidget`  
_L63-184_
- inherits: `SCompoundWidget`
- desc: The page props implementation for remote control fields.
- L66 _public member_ `static const FName PropertyColumnName;`
- L67 _public member_ `static const FName ValueColumnName;`
- L69 _public function_ `static FAvaRundownRCPropertyHeaderRowExtensionDelegate& GetHeaderRowExtensionDelegate()`
- L70 _public prototype_ `static TArray<FAvaRundownRCPropertyTableRowExtensionDelegate>& GetTableRowExtensionDelegates(FName InExtensionName);`
- L72 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPageRemoteControlProps)`
- L73 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SAvaRundownPageDetails>& InPageDetailPanel, const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L79 _public prototype_ `void UpdateDefaultValuesAndRefresh(const TArray<int32>& InSelectedPageIds);` — Update the current page's remote control values from the defaults then refresh the widget.
- L82 _public prototype_ `void Refresh(const TArray<int32>& InSelectedPageIds);` — Refreshes the content of this widget.
- L85 _public prototype_ `void SetShowControlledProperties(bool bInShowControlledProperties);` — Sets the visibility on the properties that are set by controllers
- L88 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L91 _public prototype_ `const TArray<TSharedPtr<FAvaRundownRCFieldItem>> GetSelectedPropertyItems() const;`
- L93 _public prototype_ `TSharedPtr<FAvaRundownPageRCPropsNotifyHook> GetNotifyHook() const;`
- L95 _public prototype_ `FAvaRundownPageRCObject& FindOrAddPageRCObject(UObject* InObject);`
- L104 _public prototype_ `static bool SaveRemoteControlEntitiesToPage(const URemoteControlPreset* InPreset, const TSet<FGuid>& InEntityIds, UAvaRundown* InRundown, int32 InPageId);` — Utility to save the given Preset's Entities to the given page's property. @param InPreset Source Preset the entity values are read from. @param InEntityIds Set of entity ids to read from the given preset and save to the given page. @param InRundown Rundown. @param InPageId Page Id to save the value to.
- L107 _private member_ `static FAvaRundownRCPropertyHeaderRowExtensionDelegate HeaderRowExtensionDelegate;`
- L108 _private member_ `static TMap<FName, TArray<FAvaRundownRCPropertyTableRowExtensionDelegate>> TableRowExtensionDelegates;`
- L110 _private function_ `void OnRemoteControlEntitiesExposed(URemoteControlPreset* InPreset, const FGuid& InEntityId)`
- L111 _private function_ `void OnRemoteControlEntitiesUnexposed(URemoteControlPreset* InPreset, const FGuid& InEntityId)`
- L112 _private function_ `void OnRemoteControlEntitiesUpdated(URemoteControlPreset* InPreset, const TSet<FGuid>& InModifiedEntities)`
- L113 _private prototype_ `void OnRemoteControlExposedPropertiesModified(URemoteControlPreset* InPreset, const TSet<FGuid>& InModifiedProperties);`
- L114 _private prototype_ `void OnRemoteControlControllerModified(URemoteControlPreset* InPreset, const TSet<FGuid>& InModifiedControllerIds);`
- L116 _private prototype_ `void OnPostPropertyChanged(FProperty* InPropertyThatChanged);`
- L118 _private prototype_ `void RequestRefresh();`
- L120 _private prototype_ `void BindRemoteControlDelegates(URemoteControlPreset* InPreset);`
- L122 _private prototype_ `bool HasRemoteControlPreset(const URemoteControlPreset* InPreset) const;`
- L125 _private prototype_ `FAvaRundownPage* GetActivePage() const;` — Returns the currently selected page if 1 page is currently selected, returns nullptr otherwise.
- L128 _private function_ `int32 GetActivePageId() const` — Returns the currently selected page id if 1 page is currently selected, returns InvalidPageId otherwise.
- L134 _private prototype_ `const FAvaPlayableRemoteControlValue* GetSelectedPageEntityValue(const TSharedPtr<FRemoteControlEntity>& InRemoteControlEntity) const;` — Get Selected Page's entity value corresponding to the given entity (using entity Id to match). @return pointer to page's entity value, null if not found.
- L140 _private prototype_ `bool SetSelectedPageEntityValue(const TSharedPtr<FRemoteControlEntity>& InRemoteControlEntity, const FAvaPlayableRemoteControlValue& InValue) const;` — Set (or add) Selected Page's entity value corresponding to the given entity (using entity Id to match). @return true if it succeeded, false otherwise.
- L142 _private prototype_ `TSharedRef<ITableRow> OnGenerateControllerRow(TSharedPtr<FAvaRundownRCFieldItem> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L144 _private prototype_ `void OnGetEntityChildren(TSharedPtr<FAvaRundownRCFieldItem> InItem, TArray<TSharedPtr<FAvaRundownRCFieldItem>>& OutChildren);`
- L146 _private prototype_ `void OnExpansionChanged(TSharedPtr<FAvaRundownRCFieldItem> InItem, bool bInIsExpanded);`
- L148 _private prototype_ `void UpdateItemExpansionsRecursive(TConstArrayView<TSharedPtr<FAvaRundownRCFieldItem>> InItems);`
- L150 _private prototype_ `void RefreshTable(const TSet<FGuid>& InEntityIds = TSet<FGuid>());`
- L152 _private prototype_ `TSharedPtr<SWidget> GetContextMenuContent();`
- L154 _private member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L156 _private member_ `TArray<TSharedPtr<FAvaRundownManagedInstance>> ManagedInstances;`
- L159 _private member_ `TSharedPtr<STreeView<TSharedPtr<FAvaRundownRCFieldItem>>> FieldContainer;` — The widget that lists the property rows.
- L162 _private member_ `TArray<TSharedPtr<FAvaRundownRCFieldItem>> FieldItems;` — The data used to back the properties container list view.
- L164 _private member_ `int32 ActivePageId = -1;`
- L166 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L168 _private member_ `TSharedPtr<FAvaRundownPagePropertyContextMenu> ContextMenu;`
- L170 _private member_ `TSharedPtr<FAvaRundownPageRCPropsNotifyHook> NotifyHook;`
- L172 _private member_ `TSet<FAvaRundownPageRCObject> PageRCObjects;`
- L174 _private member_ `TSet<FString> ExpandedPaths;`
- L178 _private member_ `bool bRefreshRequested = false;`
- L181 _private member_ `bool bShowControlledProperties = false;` — Whether the properties that are set by controllers are shown
- L183 _private member_ `TSharedPtr<UE::AvaPlayback::Utils::FAsyncAssetLoader> AsyncAssetLoader;`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace AvaPlayback` (scope `UE`)
- L36 _namespace_ `namespace Utils` (scope `UE::AvaPlayback`)
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAvaRundownRCPropertyHeaderRowExtensionDelegate, TSharedRef<SAvaRundownPageRemoteControlProps> Panel, TSharedRef<SHeaderRow>& HeaderRow) DECLARE_DELEGATE_ThreeParams(FAvaRundownRCPropertyTableRowExtensionDelegate, TSharedRef<SAvaRundownPageRemoteControlProps> Panel, TSharedRef<const FAvaRundownRCFieldItem> ItemPtr, TSharedPtr<SWidget>& CurrentWidget) class FAvaRundownPageRCPropsNotifyHook : public FNotifyHook { public:`
- L43 _delegate_ `DECLARE_DELEGATE_ThreeParams(FAvaRundownRCPropertyTableRowExtensionDelegate, TSharedRef<SAvaRundownPageRemoteControlProps> Panel, TSharedRef<const FAvaRundownRCFieldItem> ItemPtr, TSharedPtr<SWidget>& CurrentWidget) class FAvaRundownPageRCPropsNotifyHook : public FNotifyHook { public:`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/RemoteControl/Properties/SAvaRundownRCPropertyItemRow.h` (Private)


#### class `SAvaRundownRCPropertyItemRow`  
`class SAvaRundownRCPropertyItemRow : public SMultiColumnTableRow<TSharedPtr<FAvaRundownRCFieldItem>>`  
_L15-39_
- inherits: `SMultiColumnTableRow<TSharedPtr<FAvaRundownRCFieldItem>>`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownRCPropertyItemRow)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<SAvaRundownPageRemoteControlProps> InPropertyPanel, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedPtr<const FAvaRundownRCFieldItem>& InRowItem);`
- L24 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L26 _public prototype_ `void UpdateValue();`
- L29 _protected prototype_ `TSharedRef<SWidget> CreateName();`
- L31 _protected prototype_ `TSharedRef<SWidget> CreateValue();`
- L33 _protected prototype_ `FText GetPropertyTooltipText() const;`
- L35 _protected member_ `TWeakPtr<const FAvaRundownRCFieldItem> FieldItemWeak;`
- L36 _protected member_ `TWeakPtr<SAvaRundownPageRemoteControlProps> PropertyPanelWeak;`
- L37 _protected member_ `TSharedPtr<FAvaRundownPageRCPropsNotifyHook> NotifyHook;`
- L38 _protected member_ `TSharedPtr<SBox> ValueContainer;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/DetailsView/SAvaRundownPageDetails.h` (Private)


#### class `SAvaRundownPageDetails`  
`class SAvaRundownPageDetails : public SCompoundWidget`  
_L25-104_
- inherits: `SCompoundWidget`
- L28 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPageDetails)`
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L36 _public prototype_ `void OnPageEvent(const TArray<int32>& InSelectedPageIds, UE::AvaRundown::EPageEvent InPageEvent);`
- L37 _public prototype_ `void OnManagedInstanceCacheEntryInvalidated(const FSoftObjectPath& InAssetPath);`
- L39 _public function_ `void RefreshSelectedPage()`
- L45 _protected prototype_ `void OnFinishedChangingPageDetailProperties(const FPropertyChangedEvent& InChangedProperty);`
- L47 _protected prototype_ `FReply ToggleExposedPropertiesVisibility();`
- L49 _protected prototype_ `const FSlateBrush* GetExposedPropertiesVisibilityBrush() const;`
- L59 _protected prototype_ `FRundownContext GetRundownContext() const;`
- L61 _protected prototype_ `const FAvaRundownPage& GetSelectedPage(const FRundownContext& InRundownContext) const;`
- L62 _protected prototype_ `FAvaRundownPage& GetMutableSelectedPage(const FRundownContext& InRundownContext) const;`
- L64 _protected prototype_ `void QueueRefreshSelectedPage();`
- L65 _protected prototype_ `void QueueUpdateAndRefreshSelectedPage();`
- L66 _protected prototype_ `void RefreshPageDetailView();`
- L68 _protected prototype_ `bool HasSelectedPage() const;`
- L70 _protected prototype_ `FText GetPageId() const;`
- L73 _protected prototype_ `void OnPageIdCommitted(const FText& InNewText, ETextCommit::Type InCommitType);` — Only update page id on commit.
- L75 _protected prototype_ `FText GetPageDescription() const;`
- L78 _protected prototype_ `void OnPageNameChanged(const FText& InNewText);` — Update page name live.
- L80 _protected prototype_ `FReply DuplicateSelectedPage();`
- L82 _protected prototype_ `void OnPagesChanged(const UAvaRundown* InRundown, const FAvaRundownPage& InPage, const EAvaRundownPageChanges InChanges);`
- L83 _protected prototype_ `void OnPageListChanged(const FAvaRundownPageListChangeParams& InParams);`
- L86 _private member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L88 _private member_ `TSharedPtr<SAvaRundownPageRemoteControlProps> RemoteControlProps;`
- L89 _private member_ `TSharedPtr<SAvaRundownRCControllerPanel> RCControllerPanel;`
- L92 _private member_ `TSharedPtr<IDetailsView> PageDetailView;` — Detail view of the page detail model.
- L95 _private member_ `TStrongObjectPtr<UAvaRundownPageDetailView> CurrentPageDetailViewData;` — Page view data of the current page (being edited).
- L98 _private member_ `int32 CurrentPageDetailViewPageId = FAvaRundownPage::InvalidPageId;` — This is separate from ActivePageId because of order of update events. ActivePageId update first.
- L100 _private member_ `bool bRefreshSelectedPageQueued = false;`
- L101 _private member_ `bool bUpdateAndRefreshSelectedPageQueued = false;`
- L103 _private member_ `int32 ActivePageId = FAvaRundownPage::InvalidPageId;`

#### struct `SAvaRundownPageDetails::FRundownContext`  
`struct FRundownContext`  
_L52-58_
- desc: Encapsulate how the rundown is accessed for this widget to reduce duplicated code.
- L54 _public prototype_ `bool IsValid() const;`
- L55 _public prototype_ `UAvaRundown* GetRundown() const;`
- L57 _public member_ `TSharedPtr<FAvaRundownEditor> RundownEditor;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/AvaRundownFactoriesUtils.h` (Private)


#### enum `EAvaRundownSearchListType`  
`enum class EAvaRundownSearchListType : uint8`  
_L9-14_
- desc: Type of the Page list
- L11 _public enumerator_ `None = 0x00` — None
- L12 _public enumerator_ `Template = 0x01` — Template pages type
- L13 _public enumerator_ `Instanced = 0x10` — Instanced pages type

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/AvaRundownFilterChannelExpressionFactory.h` (Private)


#### class `FAvaRundownFilterChannelExpressionFactory`  
`class FAvaRundownFilterChannelExpressionFactory : public IAvaRundownFilterExpressionFactory`  
_L7-15_
- inherits: `IAvaRundownFilterExpressionFactory`
- L11 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L12 _public prototype_ `virtual bool FilterExpression(const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const override;`
- L13 _public prototype_ `virtual bool SupportsComparisonOperation(ETextFilterComparisonOperation InComparisonOperation, EAvaRundownSearchListType InRundownSearchListType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/AvaRundownFilterComboPageExpressionFactory.h` (Private)


#### class `FAvaRundownFilterComboPageExpressionFactory`  
`class FAvaRundownFilterComboPageExpressionFactory : public IAvaRundownFilterExpressionFactory`  
_L7-15_
- inherits: `IAvaRundownFilterExpressionFactory`
- L11 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L12 _public prototype_ `virtual bool FilterExpression(const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const override;`
- L13 _public prototype_ `virtual bool SupportsComparisonOperation(ETextFilterComparisonOperation InComparisonOperation, EAvaRundownSearchListType InPlaylistSearchListType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/AvaRundownFilterIdExpressionFactory.h` (Private)


#### class `FAvaRundownFilterIdExpressionFactory`  
`class FAvaRundownFilterIdExpressionFactory : public IAvaRundownFilterExpressionFactory`  
_L7-15_
- inherits: `IAvaRundownFilterExpressionFactory`
- L11 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L12 _public prototype_ `virtual bool FilterExpression(const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const override;`
- L13 _public prototype_ `virtual bool SupportsComparisonOperation(ETextFilterComparisonOperation InComparisonOperation, EAvaRundownSearchListType InRundownSearchListType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/AvaRundownFilterNameExpressionFactory.h` (Private)


#### class `FAvaRundownFilterNameExpressionFactory`  
`class FAvaRundownFilterNameExpressionFactory : public IAvaRundownFilterExpressionFactory`  
_L7-15_
- inherits: `IAvaRundownFilterExpressionFactory`
- L11 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L12 _public prototype_ `virtual bool FilterExpression(const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const override;`
- L13 _public prototype_ `virtual bool SupportsComparisonOperation(ETextFilterComparisonOperation InComparisonOperation, EAvaRundownSearchListType InRundownSearchListType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/AvaRundownFilterPathExpressionFactory.h` (Private)


#### class `FAvaRundownFilterPathExpressionFactory`  
`class FAvaRundownFilterPathExpressionFactory : public IAvaRundownFilterExpressionFactory`  
_L7-15_
- inherits: `IAvaRundownFilterExpressionFactory`
- L11 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L12 _public prototype_ `virtual bool FilterExpression(const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const override;`
- L13 _public prototype_ `virtual bool SupportsComparisonOperation(ETextFilterComparisonOperation InComparisonOperation, EAvaRundownSearchListType InRundownSearchListType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/AvaRundownFilterStatusExpressionFactory.h` (Private)


#### class `FAvaRundownFilterStatusExpressionFactory`  
`class FAvaRundownFilterStatusExpressionFactory : public IAvaRundownFilterExpressionFactory`  
_L7-15_
- inherits: `IAvaRundownFilterExpressionFactory`
- L11 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L12 _public prototype_ `virtual bool FilterExpression(const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const override;`
- L13 _public prototype_ `virtual bool SupportsComparisonOperation(ETextFilterComparisonOperation InComparisonOperation, EAvaRundownSearchListType InRundownSearchListType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/AvaRundownFilterTransitionLayerExpressionFactory.h` (Private)


#### class `FAvaRundownFilterTransitionLayerExpressionFactory`  
`class FAvaRundownFilterTransitionLayerExpressionFactory : public IAvaRundownFilterExpressionFactory`  
_L7-15_
- inherits: `IAvaRundownFilterExpressionFactory`
- L11 _public prototype_ `virtual FName GetFilterIdentifier() const override;`
- L12 _public prototype_ `virtual bool FilterExpression(const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const override;`
- L13 _public prototype_ `virtual bool SupportsComparisonOperation(ETextFilterComparisonOperation InComparisonOperation, EAvaRundownSearchListType InRundownSearchListType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/IAvaRundownFilterExpressionFactory.h` (Private)


#### struct `FAvaRundownTextFilterArgs`  
`struct FAvaRundownTextFilterArgs`  
_L18-31_
- desc: Holds the arguments required for the expression evaluation.
- L21 _public member_ `const UAvaRundown* ItemRundown;` — Item Rundown
- L24 _public member_ `FTextFilterString ValueToCheck;` — Second Value
- L27 _public member_ `ETextFilterComparisonOperation ComparisonOperation;` — Comparison Operation requested (Equal/Greater/etc...) still needed for certain Filter
- L30 _public member_ `ETextFilterTextComparisonMode ComparisonMode;` — Comparison Mode requested see ETextFilterTextComparisonMode for more information

#### class `IAvaRundownFilterExpressionFactory`  
`class IAvaRundownFilterExpressionFactory : public TSharedFromThis<IAvaRundownFilterExpressionFactory>`  
_L33-72_
- inherits: `TSharedFromThis<IAvaRundownFilterExpressionFactory>`
- L36 _public function_ `virtual ~IAvaRundownFilterExpressionFactory()`
- L39 _public prototype_ `virtual FName GetFilterIdentifier() const = 0;` — Get the filter identifier for this factory
- L52 _public function_ `static TSharedRef<InRundownFilterExpressionFactoryType> MakeInstance(InArgsType&&... InArgs)`
- L63 _public prototype_ `virtual bool FilterExpression(const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const = 0;` — Evaluate the expression with the Value given @param InItem Current Item being checked @param InArgs The argument containing the data to evaluate the expression see FAvaTextFilterArgs for more information @return True if the expression evaluate to True, False otherwise
- L71 _public prototype_ `virtual bool SupportsComparisonOperation(ETextFilterComparisonOperation InComparisonOperation, EAvaRundownSearchListType InRundownSearchListType) const = 0;` — Whether the factory support a given Comparison Operation @param InComparisonOperation Comparison Operation to check @param InRundownSearchListType Type of the Search List either Template or Instanced @return True if Factory support passed Comparison Operation, False otherwise

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Filters/IAvaRundownFilterSuggestionFactory.h` (Private)


#### struct `FAvaRundownFilterSuggestionPayload`  
`struct FAvaRundownFilterSuggestionPayload`  
_L18-34_
- desc: Holds the arguments required for the suggestion factory to get the suggestion.
- L21 _public member_ `TArray<FAssetSearchBoxSuggestion>& PossibleSuggestions;` — Holds all the suggestion that will be shown
- L24 _public member_ `const FString FilterValue;` — The current string value written in the searchbox
- L27 _public member_ `int32 ItemPageId = UE::AvaMedia::Rundown::InvalidPageId;` — Current item to check
- L30 _public member_ `const UAvaRundown* Rundown = nullptr;` — Current item rundown
- L33 _public member_ `TSet<FString>& FilterCache;` — Used to speed up the check on whether a suggestion is already added

#### class `IAvaRundownFilterSuggestionFactory`  
`class IAvaRundownFilterSuggestionFactory : public TSharedFromThis<IAvaRundownFilterSuggestionFactory>`  
_L36-74_
- inherits: `TSharedFromThis<IAvaRundownFilterSuggestionFactory>`
- L39 _public function_ `virtual ~IAvaRundownFilterSuggestionFactory()`
- L52 _public function_ `static TSharedRef<InRundownSuggestionFactoryType> MakeInstance(InArgsType&&... InArgs)`
- L58 _public prototype_ `virtual FName GetSuggestionIdentifier() const = 0;` — Get the suggestion identifier for this factory
- L61 _public prototype_ `virtual bool IsSimpleSuggestion() const = 0;` — True if the suggestion doesn't need to use the item to add its suggestions
- L66 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaRundownFilterSuggestionPayload>& InPayload) = 0;` — Add suggestions entry to be shown @param InPayload Arguments to be passed to the factory to get the suggestion to show
- L73 _public prototype_ `virtual bool SupportSuggestionType(EAvaRundownSearchListType InSuggestionType) const = 0;` — Whether the factory support a given type of suggestion @param InSuggestionType Suggestion type to check @return True if Factory support passed Suggestion Type, False otherwise

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Suggestions/AvaRundownFilterChannelSuggestionFactory.h` (Private)


#### class `FAvaRundownFilterChannelSuggestionFactory`  
`class FAvaRundownFilterChannelSuggestionFactory : public IAvaRundownFilterSuggestionFactory`  
_L7-16_
- inherits: `IAvaRundownFilterSuggestionFactory`
- L11 _public prototype_ `virtual FName GetSuggestionIdentifier() const override;`
- L12 _public function_ `virtual bool IsSimpleSuggestion() const override`
- L13 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaRundownFilterSuggestionPayload>& InPayload) override;`
- L14 _public prototype_ `virtual bool SupportSuggestionType(EAvaRundownSearchListType InSuggestionType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Suggestions/AvaRundownFilterComboPageSuggestionFactory.h` (Private)


#### class `FAvaRundownFilterComboPageSuggestionFactory`  
`class FAvaRundownFilterComboPageSuggestionFactory : public IAvaRundownFilterSuggestionFactory`  
_L7-16_
- inherits: `IAvaRundownFilterSuggestionFactory`
- L11 _public prototype_ `virtual FName GetSuggestionIdentifier() const override;`
- L12 _public function_ `virtual bool IsSimpleSuggestion() const override`
- L13 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaRundownFilterSuggestionPayload>& InPayload) override;`
- L14 _public prototype_ `virtual bool SupportSuggestionType(EAvaRundownSearchListType InSuggestionType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Suggestions/AvaRundownFilterIdSuggestionFactory.h` (Private)


#### class `FAvaRundownFilterIdSuggestionFactory`  
`class FAvaRundownFilterIdSuggestionFactory : public IAvaRundownFilterSuggestionFactory`  
_L7-16_
- inherits: `IAvaRundownFilterSuggestionFactory`
- L11 _public prototype_ `virtual FName GetSuggestionIdentifier() const override;`
- L12 _public function_ `virtual bool IsSimpleSuggestion() const override`
- L13 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaRundownFilterSuggestionPayload>& InPayload) override;`
- L14 _public prototype_ `virtual bool SupportSuggestionType(EAvaRundownSearchListType InSuggestionType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Suggestions/AvaRundownFilterNameSuggestionFactory.h` (Private)


#### class `FAvaRundownFilterNameSuggestionFactory`  
`class FAvaRundownFilterNameSuggestionFactory : public IAvaRundownFilterSuggestionFactory`  
_L7-16_
- inherits: `IAvaRundownFilterSuggestionFactory`
- L11 _public prototype_ `virtual FName GetSuggestionIdentifier() const override;`
- L12 _public function_ `virtual bool IsSimpleSuggestion() const override`
- L13 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaRundownFilterSuggestionPayload>& InPayload) override;`
- L14 _public prototype_ `virtual bool SupportSuggestionType(EAvaRundownSearchListType InSuggestionType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Suggestions/AvaRundownFilterPathSuggestionFactory.h` (Private)


#### class `FAvaRundownFilterPathSuggestionFactory`  
`class FAvaRundownFilterPathSuggestionFactory : public IAvaRundownFilterSuggestionFactory`  
_L7-16_
- inherits: `IAvaRundownFilterSuggestionFactory`
- L11 _public prototype_ `virtual FName GetSuggestionIdentifier() const override;`
- L12 _public function_ `virtual bool IsSimpleSuggestion() const override`
- L13 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaRundownFilterSuggestionPayload>& InPayload) override;`
- L14 _public prototype_ `virtual bool SupportSuggestionType(EAvaRundownSearchListType InSuggestionType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Suggestions/AvaRundownFilterStatusSuggestionFactory.h` (Private)


#### class `FAvaRundownFilterStatusSuggestionFactory`  
`class FAvaRundownFilterStatusSuggestionFactory : public IAvaRundownFilterSuggestionFactory`  
_L7-16_
- inherits: `IAvaRundownFilterSuggestionFactory`
- L11 _public prototype_ `virtual FName GetSuggestionIdentifier() const override;`
- L12 _public function_ `virtual bool IsSimpleSuggestion() const override`
- L13 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaRundownFilterSuggestionPayload>& InPayload) override;`
- L14 _public prototype_ `virtual bool SupportSuggestionType(EAvaRundownSearchListType InSuggestionType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Factories/Suggestions/AvaRundownFilterTransitionLayerSuggestionFactory.h` (Private)


#### class `FAvaRundownFilterTransitionLayerSuggestionFactory`  
`class FAvaRundownFilterTransitionLayerSuggestionFactory : public IAvaRundownFilterSuggestionFactory`  
_L7-16_
- inherits: `IAvaRundownFilterSuggestionFactory`
- L11 _public prototype_ `virtual FName GetSuggestionIdentifier() const override;`
- L12 _public function_ `virtual bool IsSimpleSuggestion() const override`
- L13 _public prototype_ `virtual void AddSuggestion(const TSharedRef<FAvaRundownFilterSuggestionPayload>& InPayload) override;`
- L14 _public prototype_ `virtual bool SupportSuggestionType(EAvaRundownSearchListType InSuggestionType) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Filters/AvaRundownPageFilterExpressionContext.h` (Private)


#### class `FAvaRundownPageFilterExpressionContext`  
`class FAvaRundownPageFilterExpressionContext : public ITextFilterExpressionContext`  
_L16-52_
- inherits: `ITextFilterExpressionContext`
- desc: Expression context to test the given asset data against the current text filter
- L19 _public function_ `FAvaRundownPageFilterExpressionContext() : ItemPageId(UE::AvaMedia::Rundown::InvalidPageId) , ItemRundown(nullptr) , RundownSearchListType(EAvaRundownSearchListType::None)`
- L25 _public prototype_ `void SetItem(const FAvaRundownPage& InItem, const UAvaRundown* InRundown, EAvaRundownSearchListType InRundownSearchListType);`
- L27 _public prototype_ `void ClearItem();`
- L29 _public prototype_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue , const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L32 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey , const FTextFilterString& InValue , const ETextFilterComparisonOperation InComparisonOperation , const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L39 _private member_ `int32 ItemPageId;` — Pointer to the asset we're currently filtering
- L41 _private member_ `const UAvaRundown* ItemRundown;`
- L43 _private member_ `EAvaRundownSearchListType RundownSearchListType;`
- L45 _private member_ `FName ItemName;`
- L47 _private member_ `FName ItemId;`
- L49 _private member_ `FName ItemPath;`
- L51 _private member_ `TArray<FName> ItemStatuses;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Filters/AvaRundownPageTextFilter.h` (Private)


#### class `FAvaRundownPageTextFilter`  
`class FAvaRundownPageTextFilter : public IFilter<const FAvaRundownPage&> , public TSharedFromThis<FAvaRundownPageTextFilter>`  
_L15-40_
- inherits: `IFilter<constFAvaRundownPage&>,TSharedFromThis<FAvaRundownPageTextFilter>`
- L20 _public prototype_ `FAvaRundownPageTextFilter();`
- L23 _public function_ `virtual FChangedEvent& OnChanged() override`
- L24 _public prototype_ `virtual bool PassesFilter(const FAvaRundownPage& InItem) const override;`
- L27 _public prototype_ `FText GetFilterText() const;`
- L29 _public prototype_ `void SetFilterText(const FText& InFilterText);`
- L31 _public prototype_ `void SetItem(const FAvaRundownPage& InItem, const UAvaRundown* InRundown, EAvaRundownSearchListType InRundownSearchListType) const;`
- L35 _private member_ `TSharedRef<FAvaRundownPageFilterExpressionContext> TextFilterExpressionContext;` — Transient context data, used when calling PassesFilter. Kept around to minimize re-allocations between multiple calls to PassesFilter
- L37 _private member_ `FTextFilterExpressionEvaluator TextFilterExpressionEvaluator;`
- L39 _private member_ `FChangedEvent ChangedEvent;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/AvaRundownPageContextMenu.h` (Private)


#### class `FAvaRundownPageContextMenu`  
`class FAvaRundownPageContextMenu : public TSharedFromThis<FAvaRundownPageContextMenu>`  
_L14-21_
- inherits: `TSharedFromThis<FAvaRundownPageContextMenu>`
- L17 _public prototype_ `TSharedRef<SWidget> GeneratePageContextMenuWidget(const TWeakPtr<FAvaRundownEditor>& InRundownEditorWeak, const FAvaRundownPageListReference& InPageListReference, const TSharedPtr<FUICommandList>& InCommandList);`
- L20 _private prototype_ `void PopulatePageContextMenu(UToolMenu& InMenu, UAvaRundownPageContext& InContext);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageAssetNameColumn.h` (Private)


#### class `FAvaRundownPageAssetNameColumn`  
`class FAvaRundownPageAssetNameColumn : public IAvaRundownPageViewColumn`  
_L7-18_
- inherits: `IAvaRundownPageViewColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageAssetNameColumn, IAvaRundownPageViewColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageAssetSelectorColumn.h` (Private)


#### class `FAvaRundownPageAssetSelectorColumn`  
`class FAvaRundownPageAssetSelectorColumn : public IAvaRundownPageViewColumn`  
_L7-21_
- inherits: `IAvaRundownPageViewColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageAssetSelectorColumn, IAvaRundownPageViewColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`
- L19 _public prototype_ `static EVisibility GetAssetSelectorVisibility(const FAvaRundownPageViewWeak InPageViewWeak);`
- L20 _public prototype_ `static EVisibility GetAssetNameVisibility(const FAvaRundownPageViewWeak InPageViewWeak);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageChannelSelectorColumn.h` (Private)


#### class `FAvaRundownPageChannelSelectorColumn`  
`class FAvaRundownPageChannelSelectorColumn : public IAvaRundownPageViewColumn`  
_L7-18_
- inherits: `IAvaRundownPageViewColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageChannelSelectorColumn, IAvaRundownPageViewColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageEnabledColumn.h` (Private)


#### class `FAvaRundownPageEnabledColumn`  
`class FAvaRundownPageEnabledColumn : public IAvaRundownPageViewColumn`  
_L8-19_
- inherits: `IAvaRundownPageViewColumn`
- L11 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageEnabledColumn, IAvaRundownPageViewColumn);`
- L14 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L15 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L16 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L17 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageIdColumn.h` (Private)


#### class `FAvaRundownPageIdColumn`  
`class FAvaRundownPageIdColumn : public IAvaRundownPageViewColumn`  
_L7-18_
- inherits: `IAvaRundownPageViewColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageIdColumn, IAvaRundownPageViewColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageNameColumn.h` (Private)


#### class `FAvaRundownPageNameColumn`  
`class FAvaRundownPageNameColumn : public IAvaRundownPageViewColumn`  
_L7-18_
- inherits: `IAvaRundownPageViewColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageNameColumn, IAvaRundownPageViewColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageStatusColumn.h` (Private)


#### class `FAvaRundownPageStatusColumn`  
`class FAvaRundownPageStatusColumn : public IAvaRundownPageViewColumn`  
_L9-33_
- inherits: `IAvaRundownPageViewColumn`
- L12 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageStatusColumn, IAvaRundownPageViewColumn);`
- L15 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L16 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L17 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L18 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`
- L21 _public prototype_ `static FSlateColor GetIsPreviewingButtonColor(const TWeakPtr<FAvaRundownInstancedPageViewImpl> InPageViewWeak);`
- L23 _public prototype_ `static const FSlateBrush* GetPreviewBorderBackgroundImage(const TWeakPtr<FAvaRundownInstancedPageViewImpl> InPageViewWeak);`
- L25 _public prototype_ `static FSlateColor GetIsPlayingButtonColor(const TWeakPtr<FAvaRundownInstancedPageViewImpl> InPageViewWeak);`
- L27 _public prototype_ `static const FSlateBrush* GetProgramBorderBackgroundImage(const TWeakPtr<FAvaRundownInstancedPageViewImpl> InPageViewWeak);`
- L29 _public prototype_ `static FText GetTakeInTooltip(const TWeakPtr<FAvaRundownInstancedPageViewImpl> InPageViewWeak);`
- L31 _public prototype_ `static FSlateColor GetAssetStatusButtonColor(const TWeakPtr<FAvaRundownInstancedPageViewImpl> InPageViewWeak);`
- L32 _public prototype_ `static FText GetAssetStatusButtonTooltip(const TWeakPtr<FAvaRundownInstancedPageViewImpl> InPageViewWeak);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageTemplateNameColumn.h` (Private)


#### class `FAvaRundownPageTemplateNameColumn`  
`class FAvaRundownPageTemplateNameColumn : public IAvaRundownPageViewColumn`  
_L7-18_
- inherits: `IAvaRundownPageViewColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageTemplateNameColumn, IAvaRundownPageViewColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageTemplateStatusColumn.h` (Private)


#### class `FAvaRundownPageTemplateStatusColumn`  
`class FAvaRundownPageTemplateStatusColumn : public IAvaRundownPageViewColumn`  
_L9-28_
- inherits: `IAvaRundownPageViewColumn`
- L12 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageTemplateStatusColumn, IAvaRundownPageViewColumn);`
- L15 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L16 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L17 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L18 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`
- L21 _public prototype_ `static FSlateColor GetIsPreviewingButtonColor(const TWeakPtr<FAvaRundownTemplatePageViewImpl> InPageViewWeak);`
- L23 _public prototype_ `static FSlateColor GetAssetStatusButtonColor(const TWeakPtr<FAvaRundownTemplatePageViewImpl> InPageViewWeak);`
- L24 _public prototype_ `static FText GetAssetStatusButtonTooltip(const TWeakPtr<FAvaRundownTemplatePageViewImpl> InPageViewWeak);`
- L26 _public prototype_ `static FText GetSyncStatusButtonTooltip(const TWeakPtr<FAvaRundownTemplatePageViewImpl> InPageViewWeak);`
- L27 _public prototype_ `static FSlateColor GetSyncStatusButtonColor(const TWeakPtr<FAvaRundownTemplatePageViewImpl> InPageViewWeak);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageThumbnailColumn.h` (Private)


#### class `FAvaRundownPageThumbnailColumn`  
`class FAvaRundownPageThumbnailColumn : public IAvaRundownPageViewColumn`  
_L7-18_
- inherits: `IAvaRundownPageViewColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageThumbnailColumn, IAvaRundownPageViewColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/AvaRundownPageTransitionLayerColumn.h` (Private)


#### class `FAvaRundownPageTransitionLayerColumn`  
`class FAvaRundownPageTransitionLayerColumn : public IAvaRundownPageViewColumn`  
_L7-18_
- inherits: `IAvaRundownPageViewColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageTransitionLayerColumn, IAvaRundownPageViewColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/IAvaRundownPageViewColumn.h` (Private)


#### class `IAvaRundownPageViewColumn`  
`class IAvaRundownPageViewColumn : public IAvaTypeCastable, public TSharedFromThis<IAvaRundownPageViewColumn>`  
_L15-28_
- inherits: `IAvaTypeCastable,TSharedFromThis<IAvaRundownPageViewColumn>`
- L18 _public prototype_ `UE_AVA_INHERITS(IAvaRundownPageViewColumn, IAvaTypeCastable);`
- L20 _public function_ `FName GetColumnId() const`
- L22 _public prototype_ `virtual FText GetColumnDisplayNameText() const = 0;`
- L23 _public prototype_ `virtual FText GetColumnToolTipText() const = 0;`
- L25 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() = 0;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/Slate/SAvaRundownPageChannelSelector.h` (Private)


#### class `SAvaRundownPageChannelSelector`  
`class SAvaRundownPageChannelSelector : public SCompoundWidget`  
_L18-47_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPageChannelSelector)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAvaRundownPageViewRef& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow);`
- L27 _public prototype_ `TSharedRef<SWidget> GenerateChannelWidget(FName InChannelName);`
- L29 _public prototype_ `void OnChannelSelectionChanged(SComboBox<FName>::NullableOptionType InProposedSelection, ESelectInfo::Type InSelectInfo);`
- L31 _public prototype_ `FText GetCurrentChannelName() const;`
- L33 _public prototype_ `void OnComboBoxOpening();`
- L36 _protected prototype_ `void UpdateChannelNames();`
- L38 _protected member_ `TWeakPtr<IAvaRundownInstancedPageView> PageViewWeak;`
- L40 _protected member_ `TWeakPtr<SAvaRundownPageViewRow> PageViewRowWeak;`
- L42 _protected member_ `TSharedPtr<SComboBox<FName>> ChannelCombo;`
- L44 _protected member_ `TArray<FName> ChannelNames;`
- L46 _protected member_ `bool bInEditingMode = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/Slate/SAvaRundownPageId.h` (Private)


#### class `SAvaRundownPageId`  
`class SAvaRundownPageId : public SCompoundWidget`  
_L14-42_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPageId)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAvaRundownPageViewPtr& InPageView);`
- L24 _public prototype_ `void OnRenumberAction(EAvaRundownPageActionState InRenumberAction);`
- L26 _public prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo);`
- L28 _public prototype_ `bool OnVerifyTextChanged(const FText& InText, FText& OutErrorMessage);`
- L30 _public prototype_ `void OnEnterEditingMode();`
- L32 _public prototype_ `void OnExitEditingMode();`
- L34 _public prototype_ `void RenumberPageId(const FText& InText, const FAvaRundownPageViewPtr& InPageView);`
- L37 _protected member_ `TWeakPtr<IAvaRundownPageView> PageViewWeak;`
- L39 _protected member_ `TSharedPtr<SInlineEditableTextBlock> InlineTextBlock;`
- L41 _protected member_ `bool bInEditingMode = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/Slate/SAvaRundownPageName.h` (Private)


#### class `SAvaRundownPageName`  
`class SAvaRundownPageName : public SCompoundWidget`  
_L16-47_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPageName)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAvaRundownPageViewPtr& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow);`
- L26 _public prototype_ `void OnRenameAction(EAvaRundownPageActionState InRenameAction);`
- L28 _public prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo);`
- L29 _public prototype_ `bool OnVerifyTextChanged(const FText& InText, FText& OutErrorMessage);`
- L31 _public prototype_ `void OnEnterEditingMode();`
- L32 _public prototype_ `void OnExitEditingMode();`
- L34 _public prototype_ `void RenamePage(const FText& InText, const FAvaRundownPageViewPtr& InPageView);`
- L36 _public prototype_ `bool IsReadOnly() const;`
- L39 _protected member_ `TWeakPtr<IAvaRundownPageView> PageViewWeak;`
- L41 _protected member_ `TWeakPtr<SAvaRundownPageViewRow> PageViewRowWeak;`
- L43 _protected member_ `TSharedPtr<SInlineEditableTextBlock> InlineTextBlock;`
- L45 _protected member_ `bool bInEditingMode = false;`
- L46 _protected member_ `bool bIsReadOnly = true;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Columns/Slate/SAvaRundownPageThumbnail.h` (Private)


#### class `SAvaRundownPageThumbnail`  
`class SAvaRundownPageThumbnail : public SCompoundWidget`  
_L15-51_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPageThumbnail) : _ThumbnailWidgetSize(64)`
- L23 _public prototype_ `SLATE_ARGUMENT(int32, ThumbnailWidgetSize) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAvaRundownPageViewPtr& InPageView, const TSharedPtr<SAvaRundownPageViewRow>& InRow);`
- L29 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L33 _private prototype_ `void OnAssetUpdate(const UAvaRundown* InRundown, const FAvaRundownPage& InPage, EAvaRundownPageChanges InPageChangeType);`
- L35 _private prototype_ `void InitThumbnailWidget();`
- L38 _private member_ `TWeakPtr<IAvaRundownPageView> PageViewWeak;`
- L40 _private member_ `TWeakPtr<SAvaRundownPageViewRow> PageViewRowWeak;`
- L42 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;`
- L44 _private member_ `TSharedPtr<SWidget> ThumbnailWidget;`
- L46 _private member_ `TSharedPtr<IToolTip> Tooltip;`
- L48 _private member_ `bool bWasAssetLoaded = false;`
- L50 _private member_ `int32 ThumbnailWidgetSize = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/PageViews/AvaRundownInstancedPageViewImpl.h` (Private)


#### class `FAvaRundownInstancedPageViewImpl`  
`class FAvaRundownInstancedPageViewImpl : public FAvaRundownPageViewImpl, public IAvaRundownInstancedPageView`  
_L8-29_
- inherits: `FAvaRundownPageViewImpl,IAvaRundownInstancedPageView`
- L11 _public prototype_ `UE_AVA_INHERITS(FAvaRundownInstancedPageViewImpl, FAvaRundownPageViewImpl, IAvaRundownInstancedPageView);`
- L13 _public prototype_ `FAvaRundownInstancedPageViewImpl(int32 InPageId, UAvaRundown* InRundown, const TSharedPtr<SAvaRundownPageList>& InPageList);`
- L15 _public prototype_ `virtual bool IsTemplate() const override;`
- L16 _public prototype_ `virtual bool IsComboTemplate() const override;`
- L18 _public prototype_ `virtual FReply OnPlayButtonClicked() override;`
- L19 _public prototype_ `virtual bool CanPlay() const override;`
- L21 _public prototype_ `virtual ECheckBoxState IsEnabled() const override;`
- L22 _public prototype_ `virtual void SetEnabled(ECheckBoxState InState) override;`
- L24 _public prototype_ `virtual FName GetChannelName() const override;`
- L25 _public prototype_ `virtual bool SetChannel(FName InChannel) override;`
- L27 _public prototype_ `virtual const FAvaRundownPage& GetTemplate() const override;`
- L28 _public prototype_ `virtual FText GetTemplateDescription() const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/PageViews/AvaRundownPageViewImpl.h` (Private)


#### class `FAvaRundownPageViewImpl`  
`class FAvaRundownPageViewImpl : public IAvaRundownPageView`  
_L15-84_
- inherits: `IAvaRundownPageView`
- L18 _public prototype_ `UE_AVA_INHERITS(FAvaRundownPageViewImpl, IAvaRundownPageView);`
- L20 _public prototype_ `FAvaRundownPageViewImpl(int32 InPageId, UAvaRundown* InRundown, const TSharedPtr<SAvaRundownPageList>& InPageList);`
- L23 _public function_ `void RefreshPageId(int32 InPageId)` — Fast-path for in-place UI refresh.
- L28 _public prototype_ `virtual UAvaRundown* GetRundown() const override;`
- L30 _public prototype_ `virtual int32 GetPageId() const override;`
- L31 _public prototype_ `virtual FText GetPageIdText() const override;`
- L32 _public prototype_ `virtual FText GetPageNameText() const override;`
- L33 _public prototype_ `virtual FText GetPageTransitionLayerNameText() const override;`
- L34 _public prototype_ `virtual FText GetPageSummary() const override;`
- L35 _public prototype_ `virtual FText GetPageDescription() const override;`
- L37 _public prototype_ `virtual bool HasObjectPath(const UAvaRundown* InRundown) const override;`
- L38 _public prototype_ `virtual FSoftObjectPath GetObjectPath(const UAvaRundown* InRundown) const override;`
- L39 _public prototype_ `virtual FText GetObjectName(const UAvaRundown* InRundown) const override;`
- L40 _public prototype_ `virtual FText GetObjectNames(const UAvaRundown* InRundown) const override;`
- L41 _public prototype_ `virtual void OnObjectChanged(const FAssetData& InAssetData) override;`
- L43 _public prototype_ `virtual bool HasCommands(const UAvaRundown* InRundown) const override;`
- L45 _public prototype_ `virtual bool Rename(const FText& InNewName) override;`
- L46 _public prototype_ `virtual bool RenameFriendlyName(const FText& InNewName) override;`
- L47 _public function_ `virtual FOnPageAction& GetOnRename() override`
- L48 _public function_ `virtual FOnPageAction& GetOnRenumber() override`
- L50 _public prototype_ `virtual FReply OnAssetStatusButtonClicked() override;`
- L51 _public prototype_ `virtual bool CanChangeAssetStatus() const override;`
- L53 _public prototype_ `virtual FReply OnPreviewButtonClicked() override;`
- L54 _public prototype_ `virtual bool CanPreview() const override;`
- L55 _public prototype_ `virtual FText GetPreviewInTooltip() const override;`
- L57 _public prototype_ `virtual bool IsPageSelected() const override;`
- L58 _public prototype_ `virtual bool SetPageSelection(EAvaRundownPageViewSelectionChangeType InSelectionChangeType) override;`
- L68 _protected prototype_ `bool PerformWorkOnPages(const FText& InTransactionSessionName, TFunction<bool(FAvaRundownPage&)>&& InWork);` — Performs the given work on the underlying Page of this Page View and, if this page is selected, to do this work on the rest of the selected pages too @param InTransactionSessionName the session name to use for the transaction @param InWork the function to execute on each page. needs to return true for the work to be considered done @return whether any work was performed and a transaction was completed
- L70 _protected prototype_ `const FAvaRundownPage& GetPage() const;`
- L74 _protected member_ `int32 PageId;` — The Id used to search the Actual Page from the Rundown
- L76 _protected member_ `TWeakObjectPtr<UAvaRundown> RundownWeak;`
- L78 _protected member_ `TWeakPtr<SAvaRundownPageList> PageListWeak;`
- L80 _protected member_ `FOnPageAction OnRename;`
- L82 _protected member_ `FOnPageAction OnRenumber;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/PageViews/AvaRundownTemplatePageViewImpl.h` (Private)


#### class `FAvaRundownTemplatePageViewImpl`  
`class FAvaRundownTemplatePageViewImpl : public FAvaRundownPageViewImpl, public IAvaRundownTemplatePageView`  
_L11-27_
- inherits: `FAvaRundownPageViewImpl,IAvaRundownTemplatePageView`
- L14 _public prototype_ `UE_AVA_INHERITS(FAvaRundownTemplatePageViewImpl, FAvaRundownPageViewImpl, IAvaRundownTemplatePageView);`
- L16 _public prototype_ `FAvaRundownTemplatePageViewImpl(int32 InPageId, UAvaRundown* InRundown, const TSharedPtr<SAvaRundownPageList>& InPageList);`
- L18 _public prototype_ `virtual UAvaRundown* GetRundown() const override;`
- L20 _public prototype_ `virtual bool IsTemplate() const override;`
- L21 _public prototype_ `virtual bool IsComboTemplate() const override;`
- L22 _public prototype_ `virtual FReply OnPlayButtonClicked() override;`
- L23 _public prototype_ `virtual bool CanPlay() const override;`
- L25 _public prototype_ `FReply OnSyncStatusButtonClicked();`
- L26 _public prototype_ `bool CanChangeSyncStatus() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/PageViews/IAvaRundownInstancedPageView.h` (Private)


#### class `IAvaRundownInstancedPageView`  
`class IAvaRundownInstancedPageView`  
_L10-25_
- L13 _public prototype_ `UE_AVA_TYPE(IAvaRundownInstancedPageView);`
- L15 _public prototype_ `virtual ~IAvaRundownInstancedPageView() = default;`
- L17 _public prototype_ `virtual ECheckBoxState IsEnabled() const = 0;`
- L18 _public prototype_ `virtual void SetEnabled(ECheckBoxState InState) = 0;`
- L20 _public prototype_ `virtual FName GetChannelName() const = 0;`
- L21 _public prototype_ `virtual bool SetChannel(FName InChannel) = 0;`
- L23 _public prototype_ `virtual const FAvaRundownPage& GetTemplate() const = 0;`
- L24 _public prototype_ `virtual FText GetTemplateDescription() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/PageViews/IAvaRundownPageView.h` (Private)


#### enum `EAvaRundownPageActionState`  
`enum class EAvaRundownPageActionState : uint8`  
_L15-21_
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `Requested`
- L19 _public enumerator_ `Completed`
- L20 _public enumerator_ `Cancelled`

#### enum `EAvaRundownPageViewSelectionChangeType`  
`enum class EAvaRundownPageViewSelectionChangeType : uint8`  
_L23-28_
- L25 _public enumerator_ `Deselect`
- L26 _public enumerator_ `ReplaceSelection`
- L27 _public enumerator_ `AddToSelection`

#### class `IAvaRundownPageView`  
`class IAvaRundownPageView : public IAvaTypeCastable, public TSharedFromThis<IAvaRundownPageView>`  
_L30-80_
- inherits: `IAvaTypeCastable,TSharedFromThis<IAvaRundownPageView>`
- L33 _public prototype_ `UE_AVA_INHERITS(IAvaRundownPageView, IAvaTypeCastable);`
- L35 _public prototype_ `virtual UAvaRundown* GetRundown() const = 0;`
- L37 _public prototype_ `virtual int32 GetPageId() const = 0;`
- L38 _public prototype_ `virtual FText GetPageIdText() const = 0;`
- L39 _public prototype_ `virtual FText GetPageNameText() const = 0;`
- L40 _public prototype_ `virtual FText GetPageTransitionLayerNameText() const = 0;`
- L42 _public prototype_ `virtual FText GetPageSummary() const = 0;`
- L43 _public prototype_ `virtual FText GetPageDescription() const = 0;`
- L45 _public prototype_ `virtual bool IsTemplate() const = 0;`
- L48 _public prototype_ `virtual bool IsComboTemplate() const = 0;` — Returns true if the page is a template, and that template is a combo.
- L50 _public prototype_ `virtual bool HasObjectPath(const UAvaRundown* InRundown) const = 0;`
- L51 _public prototype_ `virtual FSoftObjectPath GetObjectPath(const UAvaRundown* InRundown) const = 0;`
- L53 _public prototype_ `virtual FText GetObjectName(const UAvaRundown* InRundown) const = 0;` — Returns asset name if single asset template.
- L55 _public prototype_ `virtual FText GetObjectNames(const UAvaRundown* InRundown) const = 0;` — Returns list of all assets: single, combo or commands.
- L56 _public prototype_ `virtual void OnObjectChanged(const FAssetData& InAssetData) = 0;`
- L59 _public prototype_ `virtual bool HasCommands(const UAvaRundown* InRundown) const = 0;` — Returns true if the page has commands, either directly or from it's templates.
- L61 _public prototype_ `virtual bool Rename(const FText& InNewName) = 0;`
- L62 _public prototype_ `virtual bool RenameFriendlyName(const FText& InNewName) = 0;`
- L64 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPageAction, EAvaRundownPageActionState);`
- L65 _public prototype_ `virtual FOnPageAction& GetOnRename() = 0;`
- L66 _public prototype_ `virtual FOnPageAction& GetOnRenumber() = 0;`
- L68 _public prototype_ `virtual FReply OnAssetStatusButtonClicked() = 0;`
- L69 _public prototype_ `virtual bool CanChangeAssetStatus() const = 0;`
- L71 _public prototype_ `virtual FReply OnPreviewButtonClicked() = 0;`
- L72 _public prototype_ `virtual bool CanPreview() const = 0;`
- L73 _public prototype_ `virtual FText GetPreviewInTooltip() const = 0;`
- L75 _public prototype_ `virtual FReply OnPlayButtonClicked() = 0;`
- L76 _public prototype_ `virtual bool CanPlay() const = 0;`
- L78 _public prototype_ `virtual bool IsPageSelected() const = 0;`
- L79 _public prototype_ `virtual bool SetPageSelection(EAvaRundownPageViewSelectionChangeType InSelectionChangeType) = 0;`

#### Free symbols / members of external scopes

- L64 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPageAction, EAvaRundownPageActionState);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/PageViews/IAvaRundownTemplatePageView.h` (Private)


#### class `IAvaRundownTemplatePageView`  
`class IAvaRundownTemplatePageView`  
_L7-13_
- L10 _public prototype_ `UE_AVA_TYPE(IAvaRundownTemplatePageView);`
- L12 _public prototype_ `virtual ~IAvaRundownTemplatePageView() = default;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Slate/SAvaRundownInstancedPageList.h` (Private)


#### class `SAvaRundownInstancedPageList`  
`class SAvaRundownInstancedPageList : public SAvaRundownPageList`  
_L11-122_
- inherits: `SAvaRundownPageList`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownInstancedPageList)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FAvaRundownEditor> InRundownEditor, const FAvaRundownPageListReference& PageListReference);`
- L24 _public prototype_ `virtual void Refresh() override;`
- L25 _public prototype_ `virtual void CreateColumns() override;`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> OnContextMenuOpening() override;`
- L27 _public prototype_ `virtual void BindCommands() override;`
- L28 _public prototype_ `virtual bool HandleDropAssets(const TArray<FSoftObjectPath>& InAvaAssets, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) override;`
- L29 _public prototype_ `virtual bool HandleDropRundowns(const TArray<FSoftObjectPath>& InRundownPaths, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) override;`
- L30 _public prototype_ `virtual bool HandleDropPageIds(const FAvaRundownPageListReference& InPageListReference, const TArray<int32>& InPageIds, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) override;`
- L31 _public prototype_ `virtual bool HandleDropExternalFiles(const TArray<FString>& InFiles, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) override;`
- L34 _public prototype_ `bool HandleDropPageIdsOnMainListFromTemplates(const TArray<int32>& InPageIds, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem);`
- L35 _public prototype_ `bool HandleDropPageIdsOnMainListFromMainList(const TArray<int32>& InPageIds, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem);`
- L36 _public prototype_ `bool HandleDropPageIdsOnSubListFromTemplates(const TArray<int32>& InPageIds, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem);`
- L37 _public prototype_ `bool HandleDropPageIdsOnSubListFromMainList(const TArray<int32>& InPageIds, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem);`
- L38 _public prototype_ `bool HandleDropPageIdsOnSubListFromSubList(const FAvaRundownPageListReference& InFromList, const TArray<int32>& InPageIds, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem);`
- L40 _public prototype_ `void OnTabActivated(TSharedRef<SDockTab> InDockTab, ETabActivationCause InActivationCause);`
- L43 _public prototype_ `void PlaySelectedPage() const;` — Plays the currently selected page.
- L44 _public prototype_ `bool CanPlaySelectedPage() const;`
- L47 _public prototype_ `bool CanLoadAllPages() const;` — Returns true if there's at least 1 page in this page list that can be loaded
- L49 _public prototype_ `void LoadAllPages();` — Requests load all the pages in this page list that can play
- L52 _public prototype_ `bool CanLoadNextPages() const;` — Returns true if there's at least 1 page in from the next pages that can be loaded
- L54 _public prototype_ `void LoadNextPages();` — Requests load the next pages that can play
- L57 _public prototype_ `bool CanLoadSelectedPages() const;` — Returns true if there's at least 1 page from the list of selected pages that can be loaded
- L59 _public prototype_ `void LoadSelectedPages();` — Requests load the selected pages that can play
- L62 _public prototype_ `bool CanLoadPages(TConstArrayView<int32> InPageIds) const;` — Returns true if there's at least 1 page from the given ids that can be loaded
- L64 _public prototype_ `void LoadPages(TConstArrayView<int32> InPageIds);` — Requests load the given page ids that can play
- L66 _public prototype_ `bool CanUpdateValuesOnSelectedPage() const;`
- L67 _public prototype_ `void UpdateValuesOnSelectedPage();`
- L69 _public prototype_ `void ContinueSelectedPage() const;`
- L70 _public prototype_ `bool CanContinueSelectedPage() const;`
- L72 _public prototype_ `void StopSelectedPage(bool bInForce) const;`
- L73 _public prototype_ `bool CanStopSelectedPage(bool bInForce) const;`
- L75 _public prototype_ `TArray<int32> PlayNextPage() const;`
- L76 _public prototype_ `bool CanPlayNextPage() const;`
- L78 _public function_ `TArray<int32> GetPageIdsToTakeNext() const`
- L89 _private prototype_ `void OnPageListChanged(const FAvaRundownPageListChangeParams& InParams);`
- L90 _private prototype_ `void OnActiveListChanged();`
- L92 _private prototype_ `TArray<int32> FilterPlayingPages(FFilterPageFunctionRef InFilterPageFunction) const;`
- L93 _private prototype_ `TArray<int32> FilterSelectedOrPlayingPages(FFilterPageFunctionRef InFilterPageFunction, const bool bInAllowFallback) const;`
- L94 _private prototype_ `TArray<int32> FilterPageSetForProgram(FFilterPageFunctionRef InFilterPageFunction, const EAvaRundownPageSet InPageSet) const;`
- L97 _private prototype_ `TArray<int32> GetAllPageIds() const;` — Retrieves all the page ids available in this page list
- L98 _private prototype_ `TArray<int32> GetPagesToTakeIn() const;`
- L99 _private prototype_ `TArray<int32> GetPagesToTakeOut(bool bInForce) const;`
- L100 _private prototype_ `TArray<int32> GetPagesToContinue() const;`
- L101 _private prototype_ `TArray<int32> GetPagesToUpdate() const;`
- L102 _private prototype_ `int32 GetNextPageIdToLoad() const;`
- L103 _private prototype_ `int32 GetPageIdToTakeNext() const;`
- L106 _protected prototype_ `void RequestCloseTab();`
- L108 _protected prototype_ `FReply MakeActive();`
- L109 _protected prototype_ `bool CanMakeActive() const;`
- L110 _protected prototype_ `FSlateColor GetMakeActiveButtonColor() const;`
- L112 _protected prototype_ `FText GetPageViewName() const;`
- L113 _protected prototype_ `void OnPageViewNameCommitted(const FText& InNewText, ETextCommit::Type InCommitType);`
- L114 _protected prototype_ `FReply OnDeletePageView();`
- L116 _protected function_ `void PlayNextPageNoReturn() const`
- L118 _protected prototype_ `virtual TArray<int32> AddPastedPages(const TArray<FAvaRundownPage>& InPages) override;`
- L120 _protected prototype_ `void ResetPagesToDefaults(bool bInResetToTemplate);`
- L121 _protected prototype_ `bool CanResetPagesToDefaults(bool bInResetToTemplate) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Slate/SAvaRundownPageList.h` (Private)


#### class `SAvaRundownPageList`  
`class SAvaRundownPageList : public SCompoundWidget`  
_L27-244_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPageList)`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FAvaRundownEditor> InRundownEditor, const FAvaRundownPageListReference& InPageListReference);`
- L39 _public function_ `const FAvaRundownPageListReference& GetPageListReference() const`
- L41 _public prototype_ `void OnPageEvent(const TArray<int32>& InSelectedPageIds, UE::AvaRundown::EPageEvent InPageEvent);`
- L43 _public prototype_ `void OnPageItemActionRequested(const TArray<int32>& InPageIds, IAvaRundownPageView::FOnPageAction&(IAvaRundownPageView::*InFunc)());`
- L45 _public prototype_ `void OnPageSelectionRequested(const TArray<int32>& InPageIds);`
- L47 _public prototype_ `TSharedRef<ITableRow> GeneratePageTableRow(FAvaRundownPageViewPtr InPageView, const TSharedRef<STableViewBase>& InOwnerTable);`
- L49 _public prototype_ `void OnPageSelected(FAvaRundownPageViewPtr InPageView, ESelectInfo::Type InSelectInfo);`
- L51 _public function_ `TSharedPtr<SListView<FAvaRundownPageViewPtr>> GetPageListView()`
- L53 _public prototype_ `TSharedPtr<IAvaRundownPageViewColumn> FindColumn(FName InColumnName) const;`
- L55 _public prototype_ `FAvaRundownPageViewPtr GetPageViewPtr(int32 InPageId) const;`
- L57 _public prototype_ `void SelectPage(int32 InPageId, bool bInScrollIntoView = true);`
- L58 _public prototype_ `void SelectPages(const TArray<int32>& InPageIds, bool bInScrollIntoView = true);`
- L59 _public prototype_ `void DeselectPage(int32 InPageId);`
- L60 _public prototype_ `void DeselectPages();`
- L62 _public function_ `const TArray<int32>& GetSelectedPageIds() const`
- L63 _public prototype_ `TArray<int32> GetPlayingPageIds() const;`
- L64 _public function_ `const TArray<FAvaRundownPageViewPtr>& GetPageViews() const`
- L66 _public prototype_ `TSharedPtr<FAvaRundownEditor> GetRundownEditor() const;`
- L68 _public prototype_ `UAvaRundown* GetRundown() const;`
- L69 _public prototype_ `UAvaRundown* GetValidRundown() const;`
- L71 _public prototype_ `virtual void BindCommands();`
- L73 _public prototype_ `virtual void Refresh() = 0;`
- L75 _public prototype_ `virtual void CreateColumns() = 0;`
- L77 _public prototype_ `virtual TSharedPtr<SWidget> OnContextMenuOpening() = 0;`
- L79 _public prototype_ `int32 GetFirstSelectedPageId() const;`
- L81 _public prototype_ `TSharedRef<SWidget> GetPageListContextMenu();`
- L83 _public prototype_ `bool CanCopySelectedPages() const;`
- L84 _public prototype_ `void CopySelectedPages();`
- L86 _public prototype_ `bool CanCutSelectedPages() const;`
- L87 _public prototype_ `void CutSelectedPages();`
- L89 _public prototype_ `bool CanPaste() const;`
- L90 _public prototype_ `void Paste();`
- L92 _public prototype_ `bool CanDuplicateSelectedPages() const;`
- L93 _public prototype_ `void DuplicateSelectedPages();`
- L95 _public prototype_ `bool CanAddPage() const;`
- L96 _public prototype_ `bool CanAddTemplate() const;`
- L97 _public prototype_ `bool CanCreateInstance() const;`
- L99 _public prototype_ `bool CanRemoveSelectedPages() const;`
- L100 _public prototype_ `void RemoveSelectedPages();`
- L102 _public prototype_ `bool CanRenameSelectedPage() const;`
- L103 _public prototype_ `void RenameSelectedPage();`
- L105 _public prototype_ `bool CanRenumberSelectedPages() const;`
- L106 _public prototype_ `void RenumberSelectedPages();`
- L108 _public prototype_ `bool CanReimportSelectedPage() const;`
- L109 _public prototype_ `void ReimportSelectedPage() const;`
- L111 _public prototype_ `bool CanEditSelectedPageSource() const;`
- L112 _public prototype_ `void EditSelectedPageSource();`
- L114 _public prototype_ `bool CanExportSelectedPagesToRundown();`
- L115 _public prototype_ `void ExportSelectedPagesToRundown();`
- L117 _public prototype_ `bool CanExportSelectedPagesToExternalFile(const TCHAR* InType);`
- L118 _public prototype_ `void ExportSelectedPagesToExternalFile(const TCHAR* InType);`
- L120 _public prototype_ `bool CanPreviewPlaySelectedPage() const;`
- L121 _public prototype_ `void PreviewPlaySelectedPage(bool bInToMark) const;`
- L123 _public prototype_ `bool CanPreviewStopSelectedPage(bool bInForce) const;`
- L124 _public prototype_ `void PreviewStopSelectedPage(bool bInForce) const;`
- L126 _public prototype_ `bool CanPreviewContinueSelectedPage() const;`
- L127 _public prototype_ `void PreviewContinueSelectedPage() const;`
- L129 _public prototype_ `bool CanPreviewPlayNextPage() const;`
- L130 _public prototype_ `void PreviewPlayNextPage();`
- L132 _public prototype_ `bool CanTakeToProgram() const;`
- L133 _public prototype_ `void TakeToProgram() const;`
- L136 _public prototype_ `static bool IsAssetDropSupported(const FAssetData& InAsset, const FSoftObjectPath& InDestinationRundownPath);` — For the given asset, check if it supported for drop operation.
- L139 _public prototype_ `static TArray<FSoftObjectPath> FilterAvaAssetPaths(const TArray<FAssetData>& InAssets);` — From the given array of asset data, filter only ava assets.
- L142 _public prototype_ `static TArray<FSoftObjectPath> FilterRundownPaths(const TArray<FAssetData>& InAssets, const FSoftObjectPath& InDestinationRundownPath);` — From the given array of asset data, keep only the rundowns.
- L145 _public prototype_ `static FAvaRundownPageInsertPosition MakeInsertPosition(EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem);` — Helper to convert drop parameters to insert position.
- L147 _public prototype_ `virtual bool CanHandleDragObjects(const FDragDropEvent& InDragDropEvent) const;`
- L148 _public prototype_ `virtual bool HandleDropEvent(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem);`
- L150 _public prototype_ `virtual bool HandleDropAssets(const TArray<FSoftObjectPath>& InAvaAssets, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) = 0;`
- L151 _public prototype_ `virtual bool HandleDropRundowns(const TArray<FSoftObjectPath>& InRundownPaths, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) = 0;`
- L152 _public prototype_ `virtual bool HandleDropPageIds(const FAvaRundownPageListReference& PageListReference, const TArray<int32>& InPageIds, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) = 0;`
- L153 _public prototype_ `virtual bool HandleDropExternalFiles(const TArray<FString>& InFiles, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) = 0;`
- L156 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L157 _public prototype_ `virtual FReply OnDragOver(const FGeometry& InMyGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L158 _public prototype_ `virtual FReply OnDrop(const FGeometry& InMyGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L159 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InMyGeometry, const FKeyEvent& InKeyEvent) override;`
- L163 _protected function_ `static bool IsPageIdValid(int32 InPageId)`
- L168 _protected typedef_ `using FFilterPageFunctionRef = TFunctionRef<TArray<int32>(const UAvaRundown* InRundown, const TArray<int32>& InPageIds)>;`
- L170 _protected prototype_ `TArray<int32> FilterSelectedPages(FFilterPageFunctionRef InFilterPageFunction) const;`
- L171 _protected prototype_ `TArray<int32> FilterPreviewingPages(FFilterPageFunctionRef InFilterPageFunction) const;`
- L172 _protected prototype_ `TArray<int32> FilterSelectedOrPreviewingPages(FFilterPageFunctionRef InFilterPageFunction, const bool bInAllowFallback) const;`
- L173 _protected prototype_ `TArray<int32> FilterPageSetForPreview(FFilterPageFunctionRef InFilterPageFunction, const EAvaRundownPageSet InPageSet) const;`
- L175 _protected prototype_ `TArray<int32> GetPagesToPreviewIn() const;`
- L176 _protected prototype_ `TArray<int32> GetPagesToPreviewOut(bool bInForce) const;`
- L177 _protected prototype_ `TArray<int32> GetPagesToPreviewContinue() const;`
- L178 _protected prototype_ `TArray<int32> GetPagesToTakeToProgram() const;`
- L179 _protected prototype_ `int32 GetPageIdToPreviewNext() const;`
- L181 _protected function_ `bool IsPageVisible(const FAvaRundownPage& InPage) const`
- L186 _protected function_ `bool IsPageVisible(int32 InPageId) const`
- L192 _protected prototype_ `void RefreshPagesVisibility();` — Applies PageTextFilter to current page list and caches the result.
- L195 _private prototype_ `FText OnAssetSearchBoxSuggestionChosen(const FText& InSearchText, const FString& InSuggestion);`
- L197 _private prototype_ `void OnSearchTextChanged(const FText& FilterText);`
- L199 _private prototype_ `void OnSearchTextCommitted(const FText& FilterText, ETextCommit::Type CommitType);`
- L201 _private prototype_ `void OnSearchBoxSuggestionFilter(const FText& InSearchText, TArray<FAssetSearchBoxSuggestion>& OutPossibleSuggestions, FText& OutSuggestionHighlightText);`
- L203 _private prototype_ `void OnPageTextFilterChanged();`
- L205 _private prototype_ `void OnActiveTabChanged(TSharedPtr<SDockTab> InPreviouslyActive, TSharedPtr<SDockTab> InNewlyActivated);`
- L208 _protected member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L210 _protected member_ `TSharedPtr<FAvaRundownPageContextMenu> PageContextMenu;`
- L212 _protected member_ `FAvaRundownPageListReference PageListReference;`
- L214 _protected member_ `TSharedPtr<SHorizontalBox> SearchBar;`
- L216 _protected member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L218 _protected member_ `TMap<FName, TSharedPtr<IAvaRundownPageViewColumn>> Columns;`
- L220 _protected member_ `TSharedPtr<SListView<FAvaRundownPageViewPtr>> PageListView;`
- L222 _protected member_ `TArray<FAvaRundownPageViewPtr> PageViews;`
- L224 _protected member_ `TArray<int32> SelectedPageIds;`
- L226 _protected member_ `TSharedPtr<FUICommandList> CommandList;`
- L228 _protected member_ `TSharedPtr<FAvaRundownPageTextFilter> PageTextFilter;`
- L231 _protected member_ `TSet<int32> VisiblePageIds;` — Cached result of PageTextFilter applied to current page list.
- L237 _protected prototype_ `virtual TArray<int32> AddPastedPages(const TArray<FAvaRundownPage>& InPages) = 0;` — For template and instance lists, it will return the list of page ids created. For a sub list it will return the list of page ids that were added to the page view.
- L240 _private member_ `TSharedPtr<SAssetSearchBox> AssetSearchBoxPtr;`
- L243 _private member_ `FDelegateHandle OnActiveTabChangedDelegateHandle;` — Delegate handle bound to the FGlobalTabmanager::OnActiveTabChanged delegate

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Slate/SAvaRundownPageViewRow.h` (Private)


#### enum `EAvaRundownRowState`  
`enum class EAvaRundownRowState`  
_L23-27_
- L25 _public enumerator_ `Active`
- L26 _public enumerator_ `Disabled`

#### class `FAvaRundownPageViewRowDragDropOp`  
`class FAvaRundownPageViewRowDragDropOp : public FDragDropOperation`  
_L29-46_
- inherits: `FDragDropOperation`
- L32 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAvaRundownPageViewRowDragDropOp, FDragDropOperation) virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L36 _public prototype_ `static TSharedRef<FAvaRundownPageViewRowDragDropOp> New(const TSharedPtr<SAvaRundownPageList>& InPageList);`
- L38 _public function_ `TSharedPtr<SAvaRundownPageList> GetPageList() const`
- L39 _public function_ `const TArray<int32>& GetDraggedIds() const`
- L41 _public member_ `FName Color;`
- L44 _protected member_ `TWeakPtr<SAvaRundownPageList> PageListWeak;`
- L45 _protected member_ `TArray<int32> DraggedIds;`

#### class `SAvaRundownPageViewRow`  
`class SAvaRundownPageViewRow : public SMultiColumnTableRow<FAvaRundownPageViewPtr>`  
_L48-71_
- inherits: `SMultiColumnTableRow<FAvaRundownPageViewPtr>`
- L51 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPageViewRow)`
- L52 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FAvaRundownPageViewPtr InPageView, const TSharedRef<SAvaRundownPageList>& InPageList);`
- L57 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L59 _public prototype_ `virtual const FSlateBrush* GetBorder() const override;`
- L62 _protected prototype_ `FReply OnPageViewDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InPointerEvent);`
- L63 _protected prototype_ `TOptional<EItemDropZone> OnPageViewCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FAvaRundownPageViewPtr InItem);`
- L64 _protected prototype_ `FReply OnPageViewAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FAvaRundownPageViewPtr InItem);`
- L66 _protected member_ `TWeakPtr<IAvaRundownPageView> PageViewWeak;`
- L67 _protected member_ `TWeakPtr<SAvaRundownPageList> PageListWeak;`
- L70 _private prototype_ `const FSlateBrush* GetRowColorBrush(EAvaRundownRowState InRowState) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Slate/SAvaRundownReadPage.h` (Private)


#### class `SAvaRundownReadPage`  
`class SAvaRundownReadPage : public SCompoundWidget`  
_L11-38_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownReadPage)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FAvaRundownEditor> InRundownEditor);`
- L22 _public prototype_ `void OnPageEvent(const TArray<int32>& InSelectedPageIds, UE::AvaRundown::EPageEvent InPageEvent);`
- L24 _public prototype_ `bool IsKeyRelevant(const FKeyEvent& InKeyEvent) const;`
- L26 _public prototype_ `bool ProcessRundownKeyDown(const FKeyEvent& InKeyEvent);`
- L28 _public prototype_ `bool OnVerifyTextChanged(const FText& InText, FText& OutErrorMessage) const;`
- L30 _public prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L32 _public prototype_ `FReply OnReadPageClicked();`
- L35 _private member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L37 _private member_ `TSharedPtr<SAvaRundownReadPageEditableTextBox> ReadPageText;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Slate/SAvaRundownRenumberPages.h` (Private)


#### class `SAvaRundownRenumberPages`  
`class SAvaRundownRenumberPages : public SWindow`  
_L10-41_
- inherits: `SWindow`
- L13 _public function_ `DECLARE_DELEGATE_TwoParams(FOnRundownRenumberPagesResult, const int32 , const int32 ) SLATE_BEGIN_ARGS(SAvaRundownRenumberPages)`
- L17 _public prototype_ `SLATE_EVENT(FOnRundownRenumberPagesResult, OnAccept) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _protected member_ `static constexpr int32 MaxSliderValue = 1000;`
- L25 _protected prototype_ `TSharedRef<SWidget> ConstructBaseNumberWidget();`
- L26 _protected prototype_ `TSharedRef<SWidget> ConstructIncrementWidget();`
- L28 _protected prototype_ `TOptional<int32> GetBaseNumber() const;`
- L29 _protected prototype_ `void HandleBaseNumberChanged(const int32 InNewValue);`
- L31 _protected prototype_ `TOptional<int32> GetIncrement() const;`
- L32 _protected prototype_ `void HandleIncrementChanged(const int32 InNewValue);`
- L34 _protected prototype_ `FReply HandleAcceptClick();`
- L35 _protected prototype_ `FReply HandleCancelClick();`
- L37 _protected member_ `FOnRundownRenumberPagesResult OnAccept;`
- L39 _protected member_ `int32 BaseNumber = 0;`
- L40 _protected member_ `int32 Increment = 1;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRundownRenumberPagesResult, const int32 , const int32 ) SLATE_BEGIN_ARGS(SAvaRundownRenumberPages) {} SLATE_EVENT(FOnRundownRenumberPagesResult, OnAccept) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Slate/SAvaRundownSubListStartPage.h` (Private)


#### class `SAvaRundownSubListStartPage`  
`class SAvaRundownSubListStartPage : public SCompoundWidget`  
_L9-23_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownSubListStartPage)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FAvaRundownEditor> InRundownEditor);`
- L16 _public function_ `virtual ~SAvaRundownSubListStartPage() override`
- L19 _protected member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L21 _protected prototype_ `FReply OnCreateSubListClicked();`
- L22 _protected prototype_ `FReply OnShowAllSubListsClicked();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Pages/Slate/SAvaRundownTemplatePageList.h` (Private)


#### class `SAvaRundownTemplatePageList`  
`class SAvaRundownTemplatePageList : public SAvaRundownPageList`  
_L18-55_
- inherits: `SAvaRundownPageList`
- L23 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownTemplatePageList)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FAvaRundownEditor> InRundownEditor);`
- L31 _public prototype_ `virtual void Refresh() override;`
- L32 _public prototype_ `virtual void CreateColumns() override;`
- L33 _public prototype_ `virtual TSharedPtr<SWidget> OnContextMenuOpening() override;`
- L34 _public prototype_ `virtual void BindCommands() override;`
- L35 _public prototype_ `virtual bool HandleDropAssets(const TArray<FSoftObjectPath>& InAvaAssets, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) override;`
- L36 _public prototype_ `virtual bool HandleDropRundowns(const TArray<FSoftObjectPath>& InRundownPaths, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) override;`
- L37 _public prototype_ `virtual bool HandleDropPageIds(const FAvaRundownPageListReference& InPageListReference, const TArray<int32>& InPageIds, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) override;`
- L38 _public prototype_ `virtual bool HandleDropExternalFiles(const TArray<FString>& InFiles, EItemDropZone InDropZone, const FAvaRundownPageViewPtr& InItem) override;`
- L41 _public prototype_ `void AddTemplate();`
- L43 _public prototype_ `void CreateInstance();`
- L44 _public prototype_ `void CreateComboTemplate();`
- L45 _public prototype_ `bool CanCreateComboTemplate();`
- L48 _protected prototype_ `virtual TArray<int32> AddPastedPages(const TArray<FAvaRundownPage>& InPages) override;`
- L50 _protected prototype_ `void ResetPagesToDefaults();`
- L51 _protected prototype_ `bool CanResetPagesToDefaults() const;`
- L54 _private prototype_ `void OnPageListChanged(const FAvaRundownPageListChangeParams& InParams);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Preview/SAvaRundownPagePreview.h` (Private)


#### class `SAvaRundownPagePreview`  
`class SAvaRundownPagePreview : public SCompoundWidget`  
_L19-52_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPagePreview)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L27 _public prototype_ `SAvaRundownPagePreview();`
- L30 _public prototype_ `TSharedRef<SWidget> CreatePagePreviewToolBar(const TSharedRef<FUICommandList>& InCommandList);`
- L31 _public prototype_ `TSharedRef<SWidget> OnGenerateSettingsMenu();`
- L34 _protected prototype_ `const FSlateBrush* GetPreviewBrush() const;`
- L35 _protected prototype_ `bool IsBlendingEnabled() const;`
- L36 _protected prototype_ `EVisibility GetCheckerboardVisibility() const;`
- L37 _protected prototype_ `void SetPreviewResolution(FIntPoint InResolution) const;`
- L38 _protected prototype_ `bool IsPreviewResolution(FIntPoint InResolution) const;`
- L40 _protected prototype_ `UTextureRenderTarget2D* GetPreviewRenderTarget() const;`
- L42 _protected prototype_ `void AddResolutionMenuEntry(FMenuBuilder& InOutMenuBuilder, const FText& Label, const FIntPoint& InResolution);`
- L44 _protected prototype_ `void HandleCheckerboardActionExecute() const;`
- L45 _protected prototype_ `void HandleSettingsActionExecute() const;`
- L48 _protected member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L51 _protected member_ `TUniquePtr<FPreviewBrush> PreviewBrush;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/Preview/SAvaRundownPreviewChannelSelector.h` (Private)


#### class `SAvaRundownPreviewChannelSelector`  
`class SAvaRundownPreviewChannelSelector : public SCompoundWidget`  
_L8-33_
- inherits: `SCompoundWidget`
- L11 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownPreviewChannelSelector)`
- L12 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L17 _public prototype_ `TSharedRef<SWidget> GenerateChannelWidget(FName InChannelName);`
- L19 _public prototype_ `void OnChannelSelectionChanged(SComboBox<FName>::NullableOptionType InProposedSelection, ESelectInfo::Type InSelectInfo);`
- L21 _public prototype_ `FText GetCurrentChannelName() const;`
- L23 _public prototype_ `static FName GetPreviewChannelNameFromSettings();`
- L25 _public prototype_ `void OnComboBoxOpening();`
- L28 _protected prototype_ `void UpdateChannelNames();`
- L30 _protected member_ `TSharedPtr<SComboBox<FName>> ChannelCombo;`
- L32 _protected member_ `TArray<FName> ChannelNames;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/ShowControl/SAvaRundownShowControl.h` (Private)


#### class `SAvaRundownShowControl`  
`class SAvaRundownShowControl : public SCompoundWidget`  
_L13-32_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAvaRundownShowControl)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L22 _public prototype_ `TSharedRef<SWidget> BuildShowControlToolBar(const TSharedRef<FUICommandList>& InCommandList);`
- L25 _protected member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L27 _protected prototype_ `TSharedRef<SWidget> CreateActiveListWidget();`
- L28 _protected prototype_ `FText GetActiveListName() const;`
- L30 _protected prototype_ `TSharedRef<SWidget> CreateNextPageWidget();`
- L31 _protected prototype_ `FText GetNextPageName() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownChannelLayerStatusListTabFactory.h` (Private)


#### class `FAvaRundownChannelLayerStatusListTabFactory`  
`class FAvaRundownChannelLayerStatusListTabFactory : public FAvaRundownTabFactory`  
_L7-15_
- inherits: `FAvaRundownTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaRundownChannelLayerStatusListTabFactory(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownChannelStatusListTabFactory.h` (Private)


#### class `FAvaRundownChannelStatusListTabFactory`  
`class FAvaRundownChannelStatusListTabFactory : public FAvaRundownTabFactory`  
_L7-15_
- inherits: `FAvaRundownTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaRundownChannelStatusListTabFactory(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownInstancedPageListTabFactory.h` (Private)


#### class `FAvaRundownInstancedPageListTabFactory`  
`class FAvaRundownInstancedPageListTabFactory : public FAvaRundownTabFactory`  
_L7-18_
- inherits: `FAvaRundownTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaRundownInstancedPageListTabFactory(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`
- L17 _protected prototype_ `virtual TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& InSpawnArgs, TWeakPtr<FTabManager> InWeakTabManager) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownPageDetailsTabFactory.h` (Private)


#### class `FAvaRundownPageDetailsTabFactory`  
`class FAvaRundownPageDetailsTabFactory : public FAvaRundownTabFactory`  
_L7-15_
- inherits: `FAvaRundownTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaRundownPageDetailsTabFactory(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownPageViewerTabFactory.h` (Private)


#### class `FAvaRundownPageViewerTabFactory`  
`class FAvaRundownPageViewerTabFactory : public FAvaRundownTabFactory`  
_L7-15_
- inherits: `FAvaRundownTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaRundownPageViewerTabFactory(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownShowControlTabFactory.h` (Private)


#### class `FAvaRundownShowControlTabFactory`  
`class FAvaRundownShowControlTabFactory : public FAvaRundownTabFactory`  
_L7-15_
- inherits: `FAvaRundownTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaRundownShowControlTabFactory(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownSubListDocumentTabFactory.h` (Private)


#### class `FAvaRundownSubListDocumentTabFactory`  
`class FAvaRundownSubListDocumentTabFactory : public FDocumentTabFactory`  
_L13-43_
- inherits: `FDocumentTabFactory`
- desc: Base class for all Tab Factories in Ava SubListDocument Editor
- L16 _public member_ `static const FName FactoryId;`
- L17 _public member_ `static const FString BaseTabName;`
- L19 _public prototype_ `static FName GetTabId(const FAvaRundownPageListReference& InSubListReference);`
- L20 _public prototype_ `static FText GetTabLabel(const FAvaRundownPageListReference& InSubListReference, const UAvaRundown* InRundown);`
- L21 _public prototype_ `static FText GetTabDescription(const FAvaRundownPageListReference& InSubListReference, const UAvaRundown* InRundown);`
- L22 _public prototype_ `static FText GetTabTooltip(const FAvaRundownPageListReference& InSubListReference, const UAvaRundown* InRundown);`
- L24 _public prototype_ `FAvaRundownSubListDocumentTabFactory(const FAvaRundownPageListReference& InSubListReference, const TSharedPtr<FAvaRundownEditor>& InSubListDocumentEditor);`
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`
- L30 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> InTabManager, const FApplicationMode* InCurrentApplicationMode) const override;`
- L32 _protected prototype_ `virtual TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& InSpawnArgs, TWeakPtr<FTabManager> InTabManagerWeak) const override;`
- L36 _protected prototype_ `FText GetTabTitle() const;`
- L38 _protected prototype_ `void OnPageListChanged(const FAvaRundownPageListChangeParams& InParams);`
- L41 _protected member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L42 _protected member_ `FAvaRundownPageListReference SubListReference;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownSubListTabFactory.h` (Private)


#### class `FAvaRundownSubListTabFactory`  
`class FAvaRundownSubListTabFactory : public FAvaRundownTabFactory`  
_L10-18_
- inherits: `FAvaRundownTabFactory`
- desc: Base class for all Tab Factories in Ava SubList Editor
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FAvaRundownSubListTabFactory(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownTabFactory.h` (Private)


#### class `FAvaRundownTabFactory`  
`class FAvaRundownTabFactory : public FWorkflowTabFactory`  
_L10-19_
- inherits: `FWorkflowTabFactory`
- desc: Base class for all Tab Factories in Ava Rundown Editor
- L14 _public prototype_ `FAvaRundownTabFactory(const FName& InTabID, const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L18 _protected member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/TabFactories/AvaRundownTemplatePageListTabFactory.h` (Private)


#### class `FAvaRundownTemplatePageListTabFactory`  
`class FAvaRundownTemplatePageListTabFactory : public FAvaRundownTabFactory`  
_L7-15_
- inherits: `FAvaRundownTabFactory`
- L10 _public member_ `static const FName TabID;`
- L12 _public prototype_ `FAvaRundownTemplatePageListTabFactory(const TSharedPtr<FAvaRundownEditor>& InRundownEditor);`
- L14 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& InInfo) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Public/IAvaMediaEditorModule.h` (Public)


#### class `IAvaMediaEditorModule`  
`class IAvaMediaEditorModule : public IModuleInterface`  
_L22-91_
- inherits: `IModuleInterface`
- L24 _private member_ `static constexpr const TCHAR* ModuleName = TEXT("Ava`
- L27 _public function_ `static bool IsLoaded()`
- L32 _public function_ `static IAvaMediaEditorModule& Get()`
- L38 _public function_ `static FName GetRundownPageMenuName()` — Returns the tool menu name used for Page Context Menu
- L43 _public prototype_ `virtual FSlateIcon GetToolbarBroadcastButtonIcon() const = 0;`
- L46 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetBroadcastToolBarExtensibilityManager() = 0;` — Returns the toolbar extensibility manager for the Broadcast Editor
- L49 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetPlaybackToolBarExtensibilityManager() = 0;` — Returns the toolbar extensibility manager for the Playback Editor
- L52 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetRundownToolBarExtensibilityManager() = 0;` — Returns the toolbar extensibility manager for the Playback Editor
- L58 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetRundownMenuExtensibilityManager() = 0;` — Returns the context menu extensibility manager for the Rundown Editor's Template Pages @remark prefer extending with the UToolMenu named after IAvaMediaEditorModule::GetRundownPageMenuName, and using UAvaRundownPageContext to retrieve context information
- L67 _public prototype_ `virtual bool CanFilterSupportComparisonOperation(const FName& InFilterKey, ETextFilterComparisonOperation InOperation, EAvaRundownSearchListType InRundownSearchListType) const = 0;` — Check if current rundown filter expression factory support the comparison operation @param InFilterKey Filter key to get the rundown filter expression factory needed @param InOperation Operation to check if supported @param InRundownSearchListType Type of the Search List either Template or Instanced @return True if operation is supported, False otherwise
- L76 _public prototype_ `virtual bool FilterExpression(const FName& InFilterKey, const FAvaRundownPage& InItem, const FAvaRundownTextFilterArgs& InArgs) const = 0;` — Evaluate the expression and return the result @param InFilterKey Filter Key to get the Factory @param InItem Item that is currently checked @param InArgs Args to evaluate the expression see FAvaRundownTextFilterArgs for more information @return True if the expression evaluated to True, False otherwise
- L83 _public prototype_ `virtual TArray<TSharedPtr<IAvaRundownFilterSuggestionFactory>> GetSimpleSuggestions(EAvaRundownSearchListType InSuggestionType) const = 0;` — Get all simple suggestions with the given type (Template/Instanced/All) @param InSuggestionType Type of suggestion to get, see EAvaRundownSearchListType for more information @return An Array containing all suggestions of the given type
- L90 _public prototype_ `virtual TArray<TSharedPtr<IAvaRundownFilterSuggestionFactory>> GetComplexSuggestions(EAvaRundownSearchListType InSuggestionType) const = 0;` — Get all complex suggestions with the given type (Template/Instanced/All) @param InSuggestionType Type of suggestion to get, see EAvaRundownSearchListType for more information @return An Array containing all suggestions of the given type

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMediaEditor, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMediaEditor, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Public/Rundown/AvaRundownEditor.h` (Public)


#### class `FAvaRundownEditor`  
`class FAvaRundownEditor : public FWorkflowCentricApplication`  
_L17-219_
- inherits: `FWorkflowCentricApplication`
- L20 _public prototype_ `FAvaRundownEditor();`
- L24 _public prototype_ `void InitRundownEditor(const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UAvaRundown* InRundown);`
- L27 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L28 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L29 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L30 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L34 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L37 _public prototype_ `TSharedRef<SWidget> MakeReadPageWidget();`
- L39 _public prototype_ `void ExtendToolBar(TSharedPtr<FExtender> InExtender);`
- L40 _public prototype_ `void FillPageToolBar(FToolBarBuilder& OutToolBarBuilder);`
- L42 _public function_ `bool IsRundownValid() const`
- L43 _public prototype_ `UAvaRundown* GetRundown() const;`
- L46 _public prototype_ `void BeginModify();` — Begin transaction buffer, but don't mark as dirty yet.
- L49 _public prototype_ `void MarkAsModified();` — Mark the rundown as dirty.
- L51 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPageEvent, const TArray<int32>&, UE::AvaRundown::EPageEvent);`
- L52 _public function_ `FOnPageEvent& GetOnPageEvent()`
- L54 _public prototype_ `bool IsKeyRelevant(const FKeyEvent& InKeyEvent) const;`
- L55 _public prototype_ `bool HandleKeyDownEvent(const FKeyEvent& InKeyEvent);`
- L57 _public prototype_ `TSharedPtr<SAvaRundownPageList> GetTemplateListWidget() const;`
- L58 _public prototype_ `TSharedPtr<SAvaRundownPageList> GetInstanceListWidget() const;`
- L59 _public prototype_ `TSharedPtr<SAvaRundownPageList> GetListWidget(const FAvaRundownPageListReference& InPageListReference) const;`
- L60 _public prototype_ `TSharedPtr<SAvaRundownPageList> GetListWidget(const FName& InTabId) const;`
- L63 _public prototype_ `TSharedPtr<SAvaRundownInstancedPageList> GetActiveListWidget() const;` — Returns the currently active Instanced Page List.
- L66 _public prototype_ `TSharedPtr<SAvaRundownPageList> GetFocusedListWidget() const;` — Returns the currently focused Page List, including templates, instances or views.
- L68 _public prototype_ `int32 GetFirstSelectedPageOnActiveSubListWidget() const;`
- L69 _public prototype_ `TConstArrayView<int32> GetSelectedPagesOnActiveSubListWidget() const;`
- L70 _public prototype_ `TConstArrayView<int32> GetSelectedPagesOnFocusedWidget() const;`
- L72 _public prototype_ `bool CanAddTemplate() const;`
- L73 _public prototype_ `void AddTemplate();`
- L75 _public prototype_ `bool CanPlaySelectedPage() const;`
- L76 _public prototype_ `void PlaySelectedPage();`
- L78 _public prototype_ `bool CanUpdateValuesOnSelectedPage() const;`
- L79 _public prototype_ `void UpdateValuesOnSelectedPage();`
- L81 _public prototype_ `bool CanStopSelectedPage(bool bInForce) const;`
- L82 _public prototype_ `void StopSelectedPage(bool bInForce);`
- L84 _public prototype_ `bool CanContinueSelectedPage() const;`
- L85 _public prototype_ `void ContinueSelectedPage();`
- L87 _public prototype_ `bool CanPlayNextPage() const;`
- L88 _public prototype_ `void PlayNextPage();`
- L91 _public prototype_ `bool CanLoadAllPages() const;` — Returns true if there's at least 1 page in the active page list that can be loaded
- L93 _public prototype_ `void LoadAllPages();` — Requests load all the pages in this page list that can play
- L96 _public prototype_ `bool CanLoadNextPages() const;` — Returns true if there's at least 1 page in from the next pages in active page list that can be loaded
- L98 _public prototype_ `void LoadNextPages();` — Requests load the next pages that can play
- L101 _public prototype_ `bool CanLoadSelectedPages() const;` — Returns true if there's at least 1 page from the list of selected pages in active page list that can be loaded
- L103 _public prototype_ `void LoadSelectedPages();` — Requests load the selected pages that can play
- L105 _public prototype_ `bool CanPreviewPlaySelectedPage() const;`
- L106 _public prototype_ `void PreviewPlaySelectedPage(bool bInToMark);`
- L108 _public prototype_ `bool CanPreviewContinueSelectedPage() const;`
- L109 _public prototype_ `void PreviewContinueSelectedPage();`
- L111 _public prototype_ `bool CanPreviewStopSelectedPage(bool bInForce) const;`
- L112 _public prototype_ `void PreviewStopSelectedPage(bool bInForce);`
- L114 _public prototype_ `bool CanPreviewPlayNextPage() const;`
- L115 _public prototype_ `void PreviewPlayNextPage();`
- L117 _public prototype_ `bool CanTakeToProgram() const;`
- L118 _public prototype_ `void TakeToProgram() const;`
- L120 _public prototype_ `bool CanCreateInstancesFromSelectedTemplates() const;`
- L121 _public prototype_ `void CreateInstancesFromSelectedTemplates();`
- L123 _public prototype_ `bool CanRemoveSelectedPages() const;`
- L124 _public prototype_ `void RemoveSelectedPages();`
- L126 _public prototype_ `void RefreshSubListTabs();`
- L128 _public prototype_ `bool RequestCloseDocumentTab(const FName& InDocumentTabId);`
- L130 _public prototype_ `void UnregisterDocumentTabFactory(const FName& InDocumentTabId);`
- L133 _protected prototype_ `void RegisterApplicationModes();`
- L135 _protected prototype_ `void CreateRundownCommands();`
- L137 _protected prototype_ `FText GetCurrentProfileName() const;`
- L139 _protected prototype_ `TSharedRef<SWidget> MakeProfileComboButton();`
- L141 _protected prototype_ `void StartAutoPlayCommand(const TArray<FString>& InArgs);`
- L142 _protected prototype_ `void StopAutoPlayCommand(const TArray<FString>& InArgs);`
- L143 _protected prototype_ `void CancelAutoPlay();`
- L145 _protected prototype_ `void LoadPageCommand(const TArray<FString>& InArgs);`
- L146 _protected prototype_ `void UnloadPageCommand(const TArray<FString>& InArgs);`
- L147 _protected prototype_ `void PlayPageCommand(const TArray<FString>& InArgs, EAvaRundownPagePlayType InPlayType);`
- L148 _protected prototype_ `void ContinuePageCommand(const TArray<FString>& InArgs, bool bInPreview);`
- L149 _protected prototype_ `void PlayNextPageCommand(const TArray<FString>& InArgs, bool bInPreview);`
- L150 _protected prototype_ `void StopPageCommand(const TArray<FString>& InArgs, bool bInPreview, bool bInForce);`
- L151 _protected prototype_ `void StopLayersCommand(const TArray<FString>& InArgs, bool bInPreview, bool bInForce);`
- L152 _protected prototype_ `void TakeToProgramCommand(const TArray<FString>& InArgs);`
- L153 _protected prototype_ `void StopPageTransitionCommand(const TArray<FString>& InArgs);`
- L154 _protected prototype_ `void StartChannelCommand(const TArray<FString>& InArgs);`
- L155 _protected prototype_ `void StopChannelCommand(const TArray<FString>& InArgs);`
- L157 _protected prototype_ `TArray<int32> ArgumentsToPageIds(const TArray<FString>& InArgs, bool bInPreview, FString& OutErrors) const;`
- L159 _protected typedef_ `using FMacroCommandFunction = TFunction<void(const TArray<FString>& InArgs)>;`
- L160 _protected typedef_ `using FBindableMacroCommands = TMap<FName, FMacroCommandFunction>;`
- L161 _protected prototype_ `const FBindableMacroCommands& GetBindableMacroCommands();`
- L188 _protected member_ `TUniquePtr<FAutoPlayTicker> AutoPlayTicker;`
- L190 _protected prototype_ `TSharedPtr<SDockTab> CreateSubListTab(const FAvaRundownPageListReference& InSubListReference);`
- L192 _protected prototype_ `void RefreshSubListTab(const FAvaRundownPageListReference& InSubListReference, bool bInSetActive = false);`
- L194 _protected prototype_ `void OnPageListChanged(const FAvaRundownPageListChangeParams& InParams);`
- L195 _protected prototype_ `void OnActiveListChanged();`
- L196 _protected prototype_ `void HandleOnPagePlayerAdded(UAvaRundown* InRundown, UAvaRundownPagePlayer* InPagePlayer);`
- L197 _protected prototype_ `void OnCanClosePlaybackContext(const UAvaRundown* InRundown, bool& bOutResult) const;`
- L199 _protected member_ `TWeakObjectPtr<UAvaRundown> AvaRundown;`
- L201 _protected member_ `FOnPageEvent OnPageEvent;`
- L204 _private member_ `TSharedPtr<SAvaRundownReadPage> ReadPageWidget;`
- L206 _private member_ `TSharedPtr<FAvaRundownEditorInputProcessor> InputProcessor;`
- L213 _private member_ `TSharedPtr<FSharedConsoleCommands> SharedConsoleCommands;`
- L215 _private member_ `FBindableMacroCommands BindableMacroCommands;`
- L218 _private member_ `TOptional<bool> bStopPagesOnCloseOverride;` — Optional user specified action for stopping pages.

#### struct `FAvaRundownEditor::FAutoPlayTicker`  
`struct FAutoPlayTicker : public FTickableEditorObject`  
_L170-187_
- inherits: `FTickableEditorObject`
- desc: Tickable object that keeps track of the play time of a page and will automatically play the next page once the specified play time has elapsed. The measure of play time begins when the page has started playing, the loading time is ignored. This is tracked from the page's status.
- L172 _public member_ `static constexpr double DefaultPlayInterval = 10;`
- L174 _public member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L175 _public member_ `double PlayInterval = DefaultPlayInterval;`
- L176 _public member_ `double NextPageStartTime = 0;`
- L177 _public member_ `bool bIsPagePlaying = false;`
- L178 _public member_ `bool bIsCancelled = false;`
- L180 _public prototype_ `FAutoPlayTicker(TWeakPtr<FAvaRundownEditor> InRundownEditorWeak, double InPlayInterval);`
- L183 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L184 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L185 _public prototype_ `virtual TStatId GetStatId() const override;`

#### Free symbols / members of external scopes

- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPageEvent, const TArray<int32>&, UE::AvaRundown::EPageEvent);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Public/Rundown/AvaRundownEditorDefines.h` (Public)


#### enum `EAvaRundownPageSet`  
`enum class EAvaRundownPageSet : uint8`  
_L28-50_
- reflection: `UENUM()`
- desc: Defines the page set that an action applies to.
- L34 _public enumerator_ `SelectedOrPlayingStrict` — The action applies to either the selected pages or playing pages if no pages are selected. If the selection is not empty and has no applicable pages, then the action is disabled.
- L40 _public enumerator_ `SelectedOrPlaying` — The action applies to applicable selected pages or playing pages if no applicable pages are selected. The selection may have pages, but if not applicable to the action, playing pages are used instead.
- L46 _public enumerator_ `Selected` — The action applies to selected pages only. For actions requiring the page to be playing, this effectively becomes "selected and playing".
- L49 _public enumerator_ `Playing` — The action applies to playing pages only regardless of selection.

#### struct `UE::AvaRundown::FEditorMetrics`  
`struct FEditorMetrics`  
_L54-58_
- L56 _public member_ `static constexpr float ColumnLeftOffset = 5.f;`
- L57 _public member_ `static const FNumberFormattingOptions PageIdFormattingOptions;`

#### enum `UE::AvaRundown::EPageEvent`  
`enum class EPageEvent : uint8`  
_L60-76_
- L63 _public enumerator_ `SelectionChanged` — Called after the Selection has Changed
- L66 _public enumerator_ `SelectionRequest` — Called to sync the Selection of current Selected Items in the Caller
- L69 _public enumerator_ `RenameRequest` — Called to Request a Rename of the Selected Items
- L72 _public enumerator_ `RenumberRequest` — Called to Request Renumbering Page Id of Selected Items
- L75 _public enumerator_ `ReimportRequest` — Called to Request Reimporting Assets of Selected Items

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef TWeakPtr<IAvaRundownPageView> FAvaRundownPageViewWeak;`
- L16 _typedef_ `typedef TSharedPtr<IAvaRundownPageView> FAvaRundownPageViewPtr;`
- L17 _typedef_ `typedef TSharedRef<IAvaRundownPageView> FAvaRundownPageViewRef;`
- L18 _typedef_ `typedef TWeakPtr<IAvaRundownTemplatePageView> FAvaRundownTemplatePageViewWeak;`
- L19 _typedef_ `typedef TSharedPtr<IAvaRundownTemplatePageView> FAvaRundownTemplatePageViewPtr;`
- L20 _typedef_ `typedef TSharedRef<IAvaRundownTemplatePageView> FAvaRundownTemplatePageViewRef;`
- L21 _typedef_ `typedef TWeakPtr<IAvaRundownInstancedPageView> FAvaRundownInstancedPageViewWeak;`
- L22 _typedef_ `typedef TSharedPtr<IAvaRundownInstancedPageView> FAvaRundownInstancedPageViewPtr;`
- L23 _typedef_ `typedef TSharedRef<IAvaRundownInstancedPageView> FAvaRundownInstancedPageViewRef;`
- L52 _namespace_ `namespace UE`
- L52 _namespace_ `namespace AvaRundown` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Public/Rundown/Pages/AvaRundownPageContext.h` (Public)


#### class `UAvaRundownPageContext`  
`class UAvaRundownPageContext : public UObject`  
_L14-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _public function_ `TSharedPtr<FAvaRundownEditor> GetRundownEditor() const`
- L26 _public function_ `const FAvaRundownPageListReference& GetPageListReference() const`
- L32 _private member_ `TWeakPtr<FAvaRundownPageContextMenu> ContextMenuWeak;`
- L34 _private member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L36 _private member_ `FAvaRundownPageListReference PageListReference;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Public/Rundown/Pages/AvaRundownPageControllerContext.h` (Public)


#### class `UAvaRundownPageControllerContext`  
`class UAvaRundownPageControllerContext : public UObject`  
_L15-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _public function_ `void InitContext(const TWeakPtr<FAvaRundownEditor>& InRundownEditorWeak , const int32 InRundownPageId , const TWeakPtr<SAvaRundownRCControllerPanel>& InControllerListWidgetWeak)`
- L29 _public function_ `TSharedPtr<FAvaRundownEditor> GetRundownEditor() const`
- L34 _public function_ `int32 GetRundownPageId() const`
- L39 _public function_ `TSharedPtr<SAvaRundownRCControllerPanel> GetControllerListWidget() const`
- L45 _private member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L47 _private member_ `int32 RundownPageId = FAvaRundownPage::InvalidPageId;`
- L49 _private member_ `TWeakPtr<SAvaRundownRCControllerPanel> ControllerListWidgetWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Public/Rundown/Pages/AvaRundownPagePropertyContext.h` (Public)


#### class `UAvaRundownPagePropertyContext`  
`class UAvaRundownPagePropertyContext : public UObject`  
_L15-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _public function_ `void InitContext(const TWeakPtr<FAvaRundownEditor>& InRundownEditorWeak , const int32 InRundownPageId , const TWeakPtr<SAvaRundownPageRemoteControlProps>& InPropertyListWidgetWeak)`
- L29 _public function_ `TSharedPtr<FAvaRundownEditor> GetRundownEditor() const`
- L34 _public function_ `int32 GetRundownPageId() const`
- L39 _public function_ `TSharedPtr<SAvaRundownPageRemoteControlProps> GetPropertyListWidget() const`
- L45 _private member_ `TWeakPtr<FAvaRundownEditor> RundownEditorWeak;`
- L47 _private member_ `int32 RundownPageId = FAvaRundownPage::InvalidPageId;`
- L49 _private member_ `TWeakPtr<SAvaRundownPageRemoteControlProps> PropertyListWidgetWeak;`
