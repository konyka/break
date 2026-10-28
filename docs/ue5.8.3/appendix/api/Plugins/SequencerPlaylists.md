# Plugins / SequencerPlaylists

- module root: `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists`
- headers: 12; symbols: 288
- symbol kinds: class=16, delegate=4, enum=3, enumerator=6, function=34, member=82, prototype=136, struct=6, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ConcertClient, ConcertSyncClient, ConcertSyncCore, CoreUObject, EditorFramework, EditorStyle, EditorSubsystem, Engine, InputCore, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneTools, Projects, PropertyEditor, Slate, SlateCore, TakeRecorder, TakesCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Private/AssetTypeActions_SequencerPlaylist.h` (Private)


#### class `FAssetTypeActions_SequencerPlaylist`  
`class FAssetTypeActions_SequencerPlaylist : public FAssetTypeActions_Base`  
_L7-16_
- inherits: `FAssetTypeActions_Base`
- L11 _public function_ `virtual FText GetName() const override`
- L12 _public function_ `virtual uint32 GetCategories() override`
- L13 _public function_ `virtual FColor GetTypeColor() const override`
- L14 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L15 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> InEditWithinLevelEditor ) override;`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Private/SequencerPlaylistItem_Sequence.h` (Private)


#### class `USequencerPlaylistItem_Sequence`  
`class USequencerPlaylistItem_Sequence : public USequencerPlaylistItem`  
_L19-42_
- reflection: `UCLASS(BlueprintType)`
- inherits: `USequencerPlaylistItem`
- L24 _public prototype_ `static FName GetSequencePropertyName();`
- L27 _public prototype_ `virtual FText GetDisplayName() override;`
- L31 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);`
- L35 _public prototype_ `void SetSequence(ULevelSequence* NewSequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L37 _public function_ `ULevelSequence* GetSequence() const`
- L41 _protected member_ `TObjectPtr<ULevelSequence> Sequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter=SetSequence, Category="Sequencer Playlists", meta=(NoResetToDefault))`

#### class `FSequencerPlaylistItemPlayer_Sequence`  
`class FSequencerPlaylistItemPlayer_Sequence : public ISequencerPlaylistItemPlayer`  
_L45-115_
- inherits: `ISequencerPlaylistItemPlayer`
- L57 _public prototype_ `FSequencerPlaylistItemPlayer_Sequence(TSharedRef<ISequencer> Sequencer);`
- L61 _public prototype_ `virtual bool Play(USequencerPlaylistItem* Item, ESequencerPlaylistPlaybackDirection Direction = ESequencerPlaylistPlaybackDirection::Forward) override;`
- L63 _public prototype_ `virtual bool TogglePause(USequencerPlaylistItem* Item) override;`
- L64 _public prototype_ `virtual bool Stop(USequencerPlaylistItem* Item) override;`
- L65 _public prototype_ `virtual bool AddHold(USequencerPlaylistItem* Item) override;`
- L66 _public prototype_ `virtual bool Reset(USequencerPlaylistItem* Item) override;`
- L68 _public prototype_ `virtual FSequencerPlaylistPlaybackState GetPlaybackState(USequencerPlaylistItem* Item) const override;`
- L87 _private prototype_ `bool InternalPlay(USequencerPlaylistItem* Item, const FPlayParams& PlayParams);`
- L88 _private prototype_ `bool InternalPause(USequencerPlaylistItem* Item);`
- L89 _private prototype_ `bool InternalStop(USequencerPlaylistItem* Item);`
- L96 _private prototype_ `bool InternalAddHold(USequencerPlaylistItem* Item, const FHoldParams& HoldParams);`
- L97 _private prototype_ `bool InternalReset(USequencerPlaylistItem* Item);`
- L99 _private prototype_ `bool IsSequencerRecordingOrPlaying() const;`
- L100 _private prototype_ `void TruncatePlayingUntil(FItemState& InItemState);`
- L101 _private prototype_ `void ClearItemStates();`
- L103 _private prototype_ `UMovieSceneSubTrack* GetOrCreateWorkingTrack(USequencerPlaylistItem* Item);`
- L109 _private prototype_ `bool EndSection(UMovieSceneSection* Section);` — Marks the end of a section based on the item player's Sequencer. @return true if the current sequence was modified, otherwise false.
- L112 _private member_ `TMap<USequencerPlaylistItem*, FItemState> ItemStates;`
- L114 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`

#### struct `FSequencerPlaylistItemPlayer_Sequence::FItemState`  
`struct FItemState`  
_L47-54_
- L49 _public member_ `TWeakObjectPtr<UMovieSceneSubTrack> WeakTrack;`
- L50 _public member_ `TWeakObjectPtr<UMovieSceneSubSection> WeakHoldSection;`
- L51 _public member_ `TArray<TWeakObjectPtr<UMovieSceneSubSection>> WeakPlaySections;`
- L52 _public member_ `int32 PlayingUntil_RootTicks = TNumericLimits<int32>::Min();`
- L53 _public member_ `ESequencerPlaylistPlaybackDirection LastPlayDirection = ESequencerPlaylistPlaybackDirection::Forward;`

#### struct `FSequencerPlaylistItemPlayer_Sequence::FPlayParams`  
`struct FPlayParams`  
_L72-86_
- L77 _public member_ `bool bEnqueueExtraPlays = true;` — If true, playing again before previous plays have completed will queue the additional play at the end. Otherwise, additional plays will occur concurrently on other rows.
- L79 _public member_ `ESequencerPlaylistPlaybackDirection Direction = ESequencerPlaylistPlaybackDirection::Forward;`
- L82 _public member_ `TOptional<FFrameTime> StartFrameOffset_SceneTicks;` — If not provided, defaults to the Item StartFrameOffset property.
- L85 _public member_ `TOptional<FFrameTime> EndFrameOffset_SceneTicks;` — If not provided, defaults to the Item EndFrameOffset property.

#### struct `FSequencerPlaylistItemPlayer_Sequence::FHoldParams`  
`struct FHoldParams`  
_L91-95_
- L94 _public member_ `TOptional<FFrameTime> StartFrameOffset_SceneTicks;` — If not provided, defaults to the Item StartFrameOffset property.

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Private/SequencerPlaylistsCommands.h` (Private)


#### class `FSequencerPlaylistsCommands`  
`class FSequencerPlaylistsCommands : public TCommands<FSequencerPlaylistsCommands>`  
_L8-22_
- inherits: `TCommands<FSequencerPlaylistsCommands>`
- L12 _public function_ `FSequencerPlaylistsCommands() : TCommands<FSequencerPlaylistsCommands>(TEXT("SequencerPlaylists"), NSLOCTEXT("Contexts", "SequencerPlaylists", "Sequencer Playlists Plugin"), NAME_None, FSequencerPlaylistsStyle::GetStyleSetName())`
- L18 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L21 _public member_ `TSharedPtr<FUICommandInfo> OpenPluginWindow;`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Private/SequencerPlaylistsLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSequencerPlaylists, Log, All)`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Private/SequencerPlaylistsModule.h` (Private)


#### class `FSequencerPlaylistsModule`  
`class FSequencerPlaylistsModule : public ISequencerPlaylistsModule`  
_L15-50_
- inherits: `ISequencerPlaylistsModule`
- L18 _public member_ `static const FName MainTabType;`
- L19 _public member_ `static const FName AssetEditorTabType;`
- L22 _public prototype_ `void StartupModule() override;`
- L23 _public prototype_ `void ShutdownModule() override;`
- L27 _public prototype_ `bool RegisterItemPlayer(TSubclassOf<USequencerPlaylistItem> ItemClass, FSequencerPlaylistItemPlayerFactory PlayerFactory) override;`
- L30 _public prototype_ `TSharedPtr<ISequencerPlaylistItemPlayer> CreateItemPlayerForClass(TSubclassOf<USequencerPlaylistItem> ItemClass, TSharedRef<ISequencer> Sequencer);`
- L32 _public function_ `TSharedPtr<FUICommandList> GetCommandList()`
- L34 _public prototype_ `TSharedRef<SDockTab> SpawnEditorForPlaylist(USequencerPlaylist* Playlist);`
- L38 _private prototype_ `void PluginButtonClicked();` — This function will be bound to Command (by default it will bring up plugin window)
- L40 _private prototype_ `void RegisterMenus();`
- L42 _private prototype_ `TSharedRef<SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);`
- L45 _private member_ `TMap<TSubclassOf<USequencerPlaylistItem>, FSequencerPlaylistItemPlayerFactory> ItemPlayerFactories;`
- L47 _private member_ `TSharedPtr<FUICommandList> PluginCommands;`
- L49 _private member_ `TSharedPtr<FAssetTypeActions_SequencerPlaylist> AssetTypeActions;`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Private/SequencerPlaylistsStyle.h` (Private)


#### class `FSequencerPlaylistsStyle`  
`class FSequencerPlaylistsStyle`  
_L10-37_
- L13 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L20 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set
- L22 _public prototype_ `static FName GetStyleSetName();`
- L31 _private prototype_ `static FLinearColor MakeColorVariation(FLinearColor InColor, EColorVariation Variation);`
- L33 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L36 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`

#### enum `FSequencerPlaylistsStyle::EColorVariation`  
`enum class EColorVariation`  
_L25-29_
- L27 _public enumerator_ `Desaturated`
- L28 _public enumerator_ `Dimmed`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Private/SequencerPlaylistsSubsystem.h` (Private)


#### struct `FSequencerPlaylistEditorHandle`  
`struct FSequencerPlaylistEditorHandle`  
_L22-44_
- reflection: `USTRUCT()`
- L26 _public function_ `FSequencerPlaylistEditorHandle()`
- L28 _public function_ `explicit FSequencerPlaylistEditorHandle(SSequencerPlaylistPanel* InEditor) : Editor(InEditor)`
- L33 _public function_ `bool operator==(const FSequencerPlaylistEditorHandle& Other) const`
- L43 _public member_ `SSequencerPlaylistPanel* Editor = nullptr;`

#### class `USequencerPlaylistsSubsystem`  
`class USequencerPlaylistsSubsystem : public UEditorSubsystem`  
_L48-102_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L54 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L55 _public prototype_ `virtual void Deinitialize() override;`
- L59 _public prototype_ `USequencerPlaylistPlayer* CreatePlayerForEditor(TSharedRef<SSequencerPlaylistPanel> Editor);` — For every tab, we manage the lifetime of the associated Player and its transient Playlist.
- L60 _public prototype_ `void NotifyEditorClosed(SSequencerPlaylistPanel* Editor);`
- L62 _public prototype_ `void UpdatePreloadSet();`
- L64 _public prototype_ `bool IsPreloadingActive() const;`
- L69 _public prototype_ `TPair<EConcertSequencerPreloadStatus, FText> GetPreloadStatusForSequence(const FTopLevelAssetPath& SequencePath);` — If any client has failed or is pending, the enum will indicate failure or pending respectively (otherwise, success). The accompanying text contains a (potentially multi-line) summary of which multi-user clients are in which states.
- L71 _public function_ `TWeakPtr<IConcertClientSession> GetWeakSession() const`
- L76 _protected prototype_ `USequencerPlaylist* CreateTransientPlaylistForEditor(TSharedRef<SSequencerPlaylistPanel> Editor);`
- L78 _protected prototype_ `void OnConcertSessionStartup(TSharedRef<IConcertClientSession> InSession);`
- L79 _protected prototype_ `void OnConcertSessionShutdown(TSharedRef<IConcertClientSession> InSession);`
- L81 _protected prototype_ `void HandleSessionClientChanged(IConcertClientSession& InSession, EConcertClientStatus InClientStatus, const FConcertSessionClientInfo& InClientInfo);`
- L82 _protected prototype_ `void HandleSequencerPreloadStatusEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerPreloadClientStatusMap& InEvent);`
- L86 _protected member_ `TMap<FSequencerPlaylistEditorHandle, TObjectPtr<UPackage>> EditorPackages;` — `UPROPERTY(Transient)`
- L89 _protected member_ `TMap<FSequencerPlaylistEditorHandle, TObjectPtr<USequencerPlaylistPlayer>> EditorPlayers;` — `UPROPERTY(Transient)`
- L92 _protected member_ `TMap<FSequencerPlaylistEditorHandle, TObjectPtr<USequencerPlaylist>> EditorPlaylists;` — `UPROPERTY(Transient)`
- L95 _protected member_ `TSet<TObjectPtr<ULevelSequence>> PreloadSequences;` — `UPROPERTY(Transient)`
- L97 _protected typedef_ `using FClientSequenceKey = TPair<FGuid, FTopLevelAssetPath>;`
- L98 _protected member_ `TMap<FClientSequenceKey, EConcertSequencerPreloadStatus> PreloadStates;`
- L101 _protected member_ `TWeakPtr<IConcertClientSession> WeakSession;` — Weak pointer to the client session with which to send events. May be null or stale.

#### Free symbols / members of external scopes

- L38 _function_ `friend uint32 GetTypeHash(const FSequencerPlaylistEditorHandle& Handle)`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Private/SequencerPlaylistsWidgets.h` (Private)


#### struct `FSequencerPlaylistRowData`  
`struct FSequencerPlaylistRowData`  
_L29-39_
- L31 _public member_ `int32 PlaylistIndex;`
- L32 _public member_ `TWeakObjectPtr<USequencerPlaylistItem> WeakItem;`
- L34 _public function_ `FSequencerPlaylistRowData(int32 InPlaylistIndex, USequencerPlaylistItem* InItem) : PlaylistIndex(InPlaylistIndex) , WeakItem(InItem)`

#### class `SSequencerPlaylistPanel`  
`class SSequencerPlaylistPanel : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L42-131_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L46 _private function_ `SLATE_BEGIN_ARGS(SSequencerPlaylistPanel)`
- L50 _public member_ `static const float DefaultWidth;`
- L51 _public member_ `static const FName ColumnName_HoverTransport;`
- L52 _public member_ `static const FName ColumnName_Items;`
- L53 _public member_ `static const FName ColumnName_Offset;`
- L54 _public member_ `static const FName ColumnName_Pause;`
- L55 _public member_ `static const FName ColumnName_Loop;`
- L56 _public member_ `static const FName ColumnName_Preload;`
- L57 _public member_ `static const FName ColumnName_HoverDetails;`
- L59 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<SDockTab> InContainingTab);`
- L60 _public prototype_ `virtual ~SSequencerPlaylistPanel();`
- L62 _public function_ `bool InPlayMode() const`
- L64 _public prototype_ `FString GetDisplayTitle();`
- L65 _public prototype_ `void SetPlayer(USequencerPlaylistPlayer* Player);`
- L66 _public prototype_ `void LoadPlaylist(USequencerPlaylist* Playlist);`
- L69 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L70 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L71 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L75 _private prototype_ `TSharedRef<SWidget> Construct_LeftToolbar();`
- L76 _private prototype_ `TSharedRef<SWidget> Construct_RightToolbar();`
- L77 _private prototype_ `TSharedRef<SWidget> Construct_Transport();`
- L78 _private prototype_ `TSharedRef<SWidget> Construct_AddSearchRow();`
- L79 _private prototype_ `TSharedRef<SWidget> Construct_ItemListView();`
- L81 _private prototype_ `USequencerPlaylist* GetCheckedPlaylist();`
- L82 _private prototype_ `USequencerPlaylist* GetPlaylist();`
- L83 _private prototype_ `void RegenerateRows();`
- L85 _private prototype_ `TSharedRef<SWidget> BuildOpenPlaylistMenu();`
- L86 _private prototype_ `void OnSavePlaylist();`
- L87 _private prototype_ `void OnSavePlaylistAs();`
- L88 _private prototype_ `void SavePlaylistAs(const FString& PackageName);`
- L89 _private prototype_ `void OnLoadPlaylist(const FAssetData& InPreset);`
- L90 _private prototype_ `void OnNewPlaylist();`
- L92 _private prototype_ `void GetSearchStrings(const FSequencerPlaylistRowData& Item, TArray<FString>& OutSearchStrings);`
- L93 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);`
- L95 _private prototype_ `FReply HandleClicked_PlayAll();`
- L96 _private prototype_ `FReply HandleClicked_PlayAllReverse();`
- L97 _private prototype_ `FReply HandleClicked_PauseAll();`
- L98 _private prototype_ `FReply HandleClicked_StopAll();`
- L99 _private prototype_ `FReply HandleClicked_ResetAll();`
- L100 _private prototype_ `FReply HandleClicked_AddSequence();`
- L102 _private prototype_ `FReply HandleClicked_Item_Play(SSequencerPlaylistItemWidget& ItemWidget);`
- L103 _private prototype_ `FReply HandleClicked_Item_PlayReverse(SSequencerPlaylistItemWidget& ItemWidget);`
- L104 _private prototype_ `FReply HandleClicked_Item_Pause(SSequencerPlaylistItemWidget& ItemWidget);`
- L105 _private prototype_ `FReply HandleClicked_Item_Stop(SSequencerPlaylistItemWidget& ItemWidget);`
- L106 _private prototype_ `FReply HandleClicked_Item_Reset(SSequencerPlaylistItemWidget& ItemWidget);`
- L107 _private prototype_ `FReply HandleClicked_Item_Remove(SSequencerPlaylistItemWidget& ItemWidget);`
- L109 _private prototype_ `bool HandleItemDetailsIsPropertyVisible(const FPropertyAndParent& PropertyAndParent);`
- L112 _private prototype_ `TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FSequencerPlaylistRowData> RowData);` — Drag and drop handling
- L113 _private prototype_ `FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FSequencerPlaylistRowData> RowData);`
- L116 _private prototype_ `void OnConcertSessionStartup(TSharedRef<IConcertClientSession> InSession);` — Multi-user event handling
- L117 _private prototype_ `void OnConcertSessionShutdown(TSharedRef<IConcertClientSession> InSession);`
- L120 _private member_ `TWeakObjectPtr<USequencerPlaylistPlayer> WeakPlayer;`
- L121 _private member_ `TWeakObjectPtr<USequencerPlaylist> WeakLoadedPlaylist;`
- L123 _private member_ `bool bPlayMode = false;`
- L125 _private member_ `TWeakPtr<SDockTab> WeakContainingTab;`
- L126 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L127 _private member_ `TSharedPtr<TTextFilter<const FSequencerPlaylistRowData&>> SearchTextFilter;`
- L128 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L129 _private member_ `TArray<TSharedPtr<FSequencerPlaylistRowData>> ItemRows;`
- L130 _private member_ `TSharedPtr<SListView<TSharedPtr<FSequencerPlaylistRowData>>> ItemListView;`

#### class `FSequencerPlaylistItemDragDropOp`  
`class FSequencerPlaylistItemDragDropOp : public FDragDropOperation`  
_L134-153_
- inherits: `FDragDropOperation`
- L137 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FSequencerPlaylistItemDragDropOp, FDragDropOperation) TArray<TSharedPtr<FSequencerPlaylistRowData>> SelectedItems;`
- L141 _public prototype_ `static TSharedRef<FSequencerPlaylistItemDragDropOp> New(const TArray<TSharedPtr<FSequencerPlaylistRowData>>& InSelectedItems);`
- L144 _public prototype_ `virtual ~FSequencerPlaylistItemDragDropOp();`
- L146 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L152 _private member_ `TSharedPtr<SWidget> Decorator;`

#### class `SSequencerPlaylistItemWidget`  
`class SSequencerPlaylistItemWidget : public SMultiColumnTableRow<TSharedPtr<FSequencerPlaylistRowData>>`  
_L159-242_
- inherits: `SMultiColumnTableRow<TSharedPtr<FSequencerPlaylistRowData>>`
- L161 _private member_ `static const FText PlayReverseItemTooltipText;`
- L162 _private member_ `static const FText PlayItemTooltipText;`
- L163 _private member_ `static const FText PauseItemTooltipText;`
- L164 _private member_ `static const FText StopItemTooltipText;`
- L165 _private member_ `static const FText ResetItemTooltipText;`
- L167 _private function_ `SLATE_BEGIN_ARGS(SSequencerPlaylistItemWidget)`
- L192 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FSequencerPlaylistRowData> InRowData, const TSharedRef<STableViewBase>& OwnerTableView);`
- L194 _public function_ `const TSharedPtr<FSequencerPlaylistRowData>& GetRowData()`
- L195 _public function_ `TSharedPtr<const FSequencerPlaylistRowData> GetRowData() const`
- L197 _public function_ `USequencerPlaylistItem* GetItem()`
- L198 _public function_ `const USequencerPlaylistItem* GetItem() const`
- L201 _public prototype_ `void ConstructChildren(ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override;`
- L205 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L209 _public prototype_ `FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L213 _private prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L215 _private function_ `bool InPlayMode() const`
- L216 _private prototype_ `void SetLoopMode(ELoopMode InLoopMode);`
- L218 _private prototype_ `EVisibility GetRowDimmingVisibility() const;`
- L219 _private prototype_ `EVisibility GetPlayModeTransportVisibility() const;`
- L220 _private prototype_ `TOptional<int32> GetItemLengthDisplayFrames() const;`
- L222 _private prototype_ `TSharedRef<SWidget> EnsureSelectedAndBuildContextMenu();`
- L223 _private prototype_ `TSharedRef<SWidget> BuildContextMenu(const TArray<UObject*>& SelectedItems);`
- L226 _private member_ `TSharedPtr<FSequencerPlaylistRowData> RowData;`
- L227 _private member_ `TSharedPtr<SMenuAnchor> DetailsAnchor;`
- L229 _private member_ `ELoopMode LoopMode;`
- L231 _private member_ `TAttribute<bool> PlayMode;`
- L232 _private member_ `TAttribute<bool> IsPlaying;`
- L233 _private member_ `TAttribute<bool> IsPaused;`
- L235 _private member_ `FOnClickedSequencerPlaylistItem PlayClickedDelegate;`
- L236 _private member_ `FOnClickedSequencerPlaylistItem PlayReverseClickedDelegate;`
- L237 _private member_ `FOnClickedSequencerPlaylistItem PauseClickedDelegate;`
- L238 _private member_ `FOnClickedSequencerPlaylistItem StopClickedDelegate;`
- L239 _private member_ `FOnClickedSequencerPlaylistItem ResetClickedDelegate;`
- L240 _private member_ `FOnClickedSequencerPlaylistItem RemoveClickedDelegate;`
- L241 _private member_ `FIsPropertyVisible IsPropertyVisibleDelegate;`

#### enum `SSequencerPlaylistItemWidget::ELoopMode`  
`enum class ELoopMode`  
_L184-189_
- L186 _public enumerator_ `None`
- L187 _public enumerator_ `Finite`

#### Free symbols / members of external scopes

- L156 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnClickedSequencerPlaylistItem, SSequencerPlaylistItemWidget& );`
- L156 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnClickedSequencerPlaylistItem, SSequencerPlaylistItemWidget& );`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Public/ISequencerPlaylistsModule.h` (Public)


#### enum `ESequencerPlaylistPlaybackDirection`  
`enum class ESequencerPlaylistPlaybackDirection : uint8`  
_L18-22_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Forward`
- L21 _public enumerator_ `Reverse`

#### struct `FSequencerPlaylistPlaybackState`  
`struct FSequencerPlaylistPlaybackState`  
_L26-45_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `uint8 bIsPlaying : 1;` — `UPROPERTY(BlueprintReadWrite, Category="Sequencer Playlists")`
- L34 _public member_ `uint8 bIsPaused : 1;` — `UPROPERTY(BlueprintReadWrite, Category="Sequencer Playlists")`
- L37 _public member_ `ESequencerPlaylistPlaybackDirection PlaybackDirection;` — `UPROPERTY(BlueprintReadWrite, Category="Sequencer Playlists")`
- L39 _public function_ `FSequencerPlaylistPlaybackState() : bIsPlaying(false) , bIsPaused(false) , PlaybackDirection(ESequencerPlaylistPlaybackDirection::Forward)`

#### class `ISequencerPlaylistItemPlayer`  
`class ISequencerPlaylistItemPlayer`  
_L49-95_
- desc: Interface for derived classes that play one or more subclasses of USequencerPlaylistItem.
- L52 _public function_ `virtual ~ISequencerPlaylistItemPlayer()`
- L58 _public prototype_ `virtual bool Play(USequencerPlaylistItem* Item, ESequencerPlaylistPlaybackDirection Direction = ESequencerPlaylistPlaybackDirection::Forward) = 0;` — Initiate playback of the specified item. @return True if the current sequence was modified, otherwise false.
- L66 _public prototype_ `virtual bool TogglePause(USequencerPlaylistItem* Item) = 0;` — Suspend playback of the specified item (if it is playing) and begin a hold. If it is already paused, resume playback. @return True if the current sequence was modified, otherwise false.
- L72 _public prototype_ `virtual bool Stop(USequencerPlaylistItem* Item) = 0;` — Halt any current playback of the specified item. @return True if the current sequence was modified, otherwise false.
- L78 _public prototype_ `virtual bool AddHold(USequencerPlaylistItem* Item) = 0;` — Adds a first frame hold section for the specified item. @return True if the current sequence was modified, otherwise false.
- L85 _public prototype_ `virtual bool Reset(USequencerPlaylistItem* Item) = 0;` — Reset the specified item. This is essentially a Stop(), followed by an AddHold() if applicable. @return True if the current sequence was modified, otherwise false.
- L87 _public prototype_ `virtual FSequencerPlaylistPlaybackState GetPlaybackState(USequencerPlaylistItem* Item) const = 0;`
- L91 _public function_ `virtual bool IsPlaying(USequencerPlaylistItem* Item) const` — `UE_DEPRECATED(5.2, "Use GetPlaybackState(Item).bIsPlaying instead.")` — Returns whether we're currently playing the specified item.

#### class `ISequencerPlaylistsModule`  
`class ISequencerPlaylistsModule : public IModuleInterface`  
_L101-120_
- inherits: `IModuleInterface`
- L110 _public function_ `static ISequencerPlaylistsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L116 _public prototype_ `virtual bool RegisterItemPlayer(TSubclassOf<USequencerPlaylistItem> ItemClass, FSequencerPlaylistItemPlayerFactory PlayerFactory) = 0;`
- L119 _public function_ `virtual USequencerPlaylistPlayer* GetDefaultPlayer()` — `UE_DEPRECATED(5.1, "There is no longer a \"default\" player. Open a specific Playlist asset to create a player associated with it.")`

#### Free symbols / members of external scopes

- L98 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<ISequencerPlaylistItemPlayer>, FSequencerPlaylistItemPlayerFactory, TSharedRef<ISequencer>);`
- L98 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<ISequencerPlaylistItemPlayer>, FSequencerPlaylistItemPlayerFactory, TSharedRef<ISequencer>);`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Public/SequencerPlaylist.h` (Public)


#### class `USequencerPlaylist`  
`class USequencerPlaylist : public UObject`  
_L13-23_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L19 _public member_ `FText Description;` — `UPROPERTY(VisibleAnywhere, AssetRegistrySearchable, BlueprintReadWrite, Category="SequencerPlaylists")`
- L22 _public member_ `TArray<TObjectPtr<USequencerPlaylistItem>> Items;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SequencerPlaylists")`

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Public/SequencerPlaylistItem.h` (Public)


#### class `USequencerPlaylistItem`  
`class USequencerPlaylistItem : public UObject`  
_L10-45_
- reflection: `UCLASS(BlueprintType, Abstract, Within=SequencerPlaylist)`
- inherits: `UObject`
- L24 _public member_ `int32 EndFrameOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sequencer Playlists")` — Number of frames by which to clip the out point of sections played from this item.
- L32 _public member_ `bool bHoldAtFirstFrame;` — `UPROPERTY()` — If true, the sequence will be inserted immediately on recording start and any time Reset() is called, paused at the first frame indefinitely until subsequently played or stopped. This is controlled by toggling pause prior to recording/playback.
- L36 _public member_ `int32 NumLoops;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sequencer Playlists")` — 0 is single playthrough, >= 1 is (n+1) playthroughs.
- L40 _public member_ `float PlaybackSpeed = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sequencer Playlists")` — Speed multiplier at which to play sections created by this item. A value of 1 will result in playback at the original speed.
- L44 _public member_ `bool bMute;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sequencer Playlists")` — Disable playback of this item and prevent it from entering a hold state.

### `Plugins/VirtualProduction/SequencerPlaylists/Source/SequencerPlaylists/Public/SequencerPlaylistPlayer.h` (Public)


#### class `USequencerPlaylistPlayer`  
`class USequencerPlaylistPlayer : public UObject`  
_L28-119_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Controls playback of playlist items
- L33 _public prototype_ `USequencerPlaylistPlayer(const FObjectInitializer& ObjectInitializer);`
- L36 _public prototype_ `void BeginDestroy() override;`
- L40 _public prototype_ `void SetPlaylist(USequencerPlaylist* InPlaylist);` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L43 _public function_ `USequencerPlaylist* GetPlaylist()` — `UFUNCTION(BlueprintPure, Category="Sequencer Playlists")`
- L47 _public function_ `static USequencerPlaylistPlayer* GetDefaultPlayer()` — `UE_DEPRECATED(5.1, "There is no longer a \"default\" player. Open a specific Playlist asset to create a player associated with it.")` — `UFUNCTION(BlueprintPure, meta=(DeprecatedFunction, DeprecationMessage= "There is no longer a \"default\" player. Open a specific Playlist asset to create a player associated with it.", DisplayName="Get Default Sequencer Playlist Player"), Category="SequencerPlaylists")`
- L50 _public member_ `FOnPlayerSequencerPlaylistSet OnPlaylistSet;` — `UPROPERTY(BlueprintAssignable, Category="Sequencer Playlists")`
- L54 _public prototype_ `bool PlayItem(USequencerPlaylistItem* Item, ESequencerPlaylistPlaybackDirection Direction = ESequencerPlaylistPlaybackDirection::Forward);` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L58 _public prototype_ `bool PauseItem(USequencerPlaylistItem* Item);` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L61 _public prototype_ `bool StopItem(USequencerPlaylistItem* Item);` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L64 _public prototype_ `bool ResetItem(USequencerPlaylistItem* Item);` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L68 _public prototype_ `bool IsPlaying(USequencerPlaylistItem* Item);` — `UE_DEPRECATED(5.2, "Call GetPlaybackState and use the bIsPlaying flag in FSequencerPlaylistPlaybackState instead.")` — `UFUNCTION(BlueprintPure, Category="Sequencer Playlists")`
- L71 _public prototype_ `FSequencerPlaylistPlaybackState GetPlaybackState(USequencerPlaylistItem* Item);` — `UFUNCTION(BlueprintPure, Category="Sequencer Playlists")`
- L74 _public prototype_ `bool PlayAll(ESequencerPlaylistPlaybackDirection Direction = ESequencerPlaylistPlaybackDirection::Forward);` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L77 _public prototype_ `bool PauseAll();` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L80 _public prototype_ `bool StopAll();` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L83 _public prototype_ `bool ResetAll();` — `UFUNCTION(BlueprintCallable, Category="Sequencer Playlists")`
- L86 _private prototype_ `TSharedPtr<ISequencer> GetOrCreateSequencer();`
- L91 _private prototype_ `void EnterUnboundedPlayIfNotRecording();` — Enters unbounded play (like Take Recorder) if the user is not recording.
- L96 _private prototype_ `void Tick(float DeltaTime);` — Ticked by a tickable game object to perform any necessary time-sliced logic
- L98 _private prototype_ `void OnTakeRecorderInitialized(UTakeRecorder* InRecorder);`
- L99 _private prototype_ `void OnTakeRecorderStarted(UTakeRecorder* InRecorder);`
- L100 _private prototype_ `void OnTakeRecorderStopped(UTakeRecorder* InRecorder);`
- L102 _private prototype_ `TSharedPtr<ISequencerPlaylistItemPlayer> GetCheckedItemPlayer(USequencerPlaylistItem* Item);`
- L107 _private member_ `TMap<TSubclassOf<USequencerPlaylistItem>, TSharedRef<ISequencerPlaylistItemPlayer>> ItemPlayersByType;`
- L110 _private member_ `TObjectPtr<USequencerPlaylist> Playlist;` — `UPROPERTY(Transient)`
- L113 _private member_ `TWeakObjectPtr<UTakeRecorder> WeakRecorder;` — The last initialized recorder, and the one we've bound delegates on.
- L115 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L118 _private member_ `TUniquePtr<FTickablePlaylist> PlaylistTicker;` — A tickable object that will do the playing in the event we are not using a take recorder.

#### class `FTickablePlaylist`  
`class FTickablePlaylist : public FTickableGameObject`  
_L122-159_
- inherits: `FTickableGameObject`
- L125 _public function_ `FTickablePlaylist(USequencerPlaylistPlayer *InPlayer) : WeakPlaylistPlayer(InPlayer)`
- L129 _public function_ `virtual TStatId GetStatId() const override`
- L135 _public function_ `virtual ETickableTickType GetTickableTickType() const override` — Make sure it always ticks, otherwise we can miss recording, particularly when time code is always increasing throughout the system.
- L137 _public function_ `virtual bool IsTickableInEditor() const override`
- L142 _public function_ `virtual UWorld* GetTickableGameObjectWorld() const override`
- L148 _public function_ `virtual void Tick(float DeltaTime) override`
- L157 _private member_ `TWeakObjectPtr<USequencerPlaylistPlayer> WeakPlaylistPlayer;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSequencerPlaylistSet, USequencerPlaylistPlayer*, Player, USequencerPlaylist*, Playlist);`
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSequencerPlaylistSet, USequencerPlaylistPlayer*, Player, USequencerPlaylist*, Playlist);`
