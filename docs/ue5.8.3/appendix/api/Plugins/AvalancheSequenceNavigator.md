# Plugins / AvalancheSequenceNavigator

- module root: `Plugins/Experimental/AvalancheSequenceNavigator/Source/AvalancheSequenceNavigator`
- headers: 7; symbols: 146
- symbol kinds: class=7, function=8, macro=2, member=27, namespace=14, prototype=88
- PrivateDependencyModuleNames: Avalanche, AvalancheEditorCore, AvalancheSequence, AvalancheSequencer, CoreUObject, Engine, MovieScene, SequenceNavigator, Sequencer, SequencerCore, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/AvalancheSequenceNavigator/Source/AvalancheSequenceNavigator/Private/AvaNavigationToolProvider.h` (Private)


#### class `UE::AvaSequencer::FAvaNavigationToolProvider`  
`class FAvaNavigationToolProvider : public SequenceNavigator::FNavigationToolProvider`  
_L34-133_
- inherits: `SequenceNavigator::FNavigationToolProvider`
- L37 _public member_ `static const FName Identifier;`
- L39 _public member_ `static const FText MotionDesignColumnViewName;`
- L41 _public prototype_ `FAvaNavigationToolProvider(const TSharedRef<IAvaSequencer>& InAvaSequencer);`
- L42 _public prototype_ `virtual ~FAvaNavigationToolProvider() override = default;`
- L46 _public prototype_ `virtual FName GetIdentifier() const override;`
- L48 _public prototype_ `virtual TSet<TSubclassOf<UMovieSceneSequence>> GetSupportedSequenceClasses() const override;`
- L50 _public prototype_ `virtual FText GetDefaultColumnView() const override;`
- L52 _public prototype_ `virtual FNavigationToolSaveState* GetSaveState(const SequenceNavigator::INavigationTool& InTool) const override;`
- L53 _public prototype_ `virtual void SetSaveState(const SequenceNavigator::INavigationTool& InTool, const FNavigationToolSaveState& InSaveState) const override;`
- L55 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L57 _public prototype_ `virtual void OnActivate() override;`
- L58 _public prototype_ `virtual void OnDeactivate() override;`
- L60 _public prototype_ `virtual void OnExtendColumns(SequenceNavigator::FNavigationToolColumnExtender& OutExtender) override;`
- L61 _public prototype_ `virtual void OnExtendColumnViews(TSet<FNavigationToolColumnView>& OutColumnViews) override;`
- L62 _public prototype_ `virtual void OnExtendItemChildren(SequenceNavigator::INavigationTool& InTool , const SequenceNavigator::FNavigationToolViewModelPtr& InParentItem , TArray<SequenceNavigator::FNavigationToolViewModelWeakPtr>& OutWeakChildren , const bool bInRecursive) override;`
- L66 _public prototype_ `virtual void OnExtendBuiltInFilters(TArray<FNavigationToolBuiltInFilterParams>& OutFilterParams) override;`
- L71 _private member_ `static const FName ToolbarSectionName;`
- L72 _private member_ `static const FName ContextMenuSectionName;`
- L74 _private prototype_ `TSharedPtr<SequenceNavigator::INavigationTool> GetNavigationTool() const;`
- L75 _private prototype_ `IAvaSceneInterface* GetSceneInterface(const SequenceNavigator::INavigationTool& InTool) const;`
- L76 _private prototype_ `IAvaSequenceProvider* GetSequenceProvider(const SequenceNavigator::INavigationTool& InTool) const;`
- L77 _private prototype_ `const IAvaSequencerProvider* GetSequencerProvider() const;`
- L78 _private prototype_ `IAvaSequencePlaybackObject* GetSequencerPlaybackObject() const;`
- L80 _private prototype_ `bool CanEditOrPlaySelection(const int32 InMinNumSelected = 1, const int32 InMaxNumSelected = INDEX_NONE) const;`
- L82 _private prototype_ `void ExtendToolToolBar();`
- L83 _private prototype_ `void ExtendToolItemContextMenu();`
- L85 _private prototype_ `void RemoveToolToolBarExtension();`
- L86 _private prototype_ `void RemoveToolItemContextMenuExtension();`
- L88 _private prototype_ `void ExtendToolItemDragDropOp(SequenceNavigator::FNavigationToolItemDragDropOp& InDragDropOp);`
- L90 _private prototype_ `void OnSequenceAdded(UAvaSequence* const InAvaSequence);`
- L92 _private prototype_ `void GeneratePresetMenu(UToolMenu* const InToolMenu);`
- L94 _private prototype_ `TArray<Sequencer::TViewModelPtr<SequenceNavigator::FNavigationToolAvaSequence>> GetSelectedSequenceItems() const;`
- L95 _private prototype_ `TArray<UAvaSequence*> GetSelectedSequences() const;`
- L97 _private prototype_ `bool CanRelabelSelection() const;`
- L98 _private prototype_ `void RelabelSelection();`
- L100 _private prototype_ `bool CanAddSequenceToSelection() const;`
- L101 _private prototype_ `void AddSequenceToSelection();`
- L103 _private prototype_ `bool CanDuplicateSelection() const;`
- L104 _private prototype_ `void DuplicateSelection();`
- L106 _private prototype_ `bool CanDeleteSelection() const;`
- L107 _private prototype_ `void DeleteSelection();`
- L109 _private prototype_ `bool CanPlaySelection() const;`
- L110 _private prototype_ `void PlaySelection();`
- L112 _private prototype_ `bool CanContinueSelection() const;`
- L113 _private prototype_ `void ContinueSelection();`
- L115 _private prototype_ `bool CanStopSelection() const;`
- L116 _private prototype_ `void StopSelection();`
- L118 _private prototype_ `bool CanExportSelection() const;`
- L119 _private prototype_ `void ExportSelection();`
- L121 _private prototype_ `bool CanSpawnPlayersForSelection() const;`
- L122 _private prototype_ `void SpawnPlayersForSelection();`
- L124 _private prototype_ `void ApplyDefaultPresetToSelection(const FName InPresetName);`
- L125 _private prototype_ `void ApplyCustomPresetToSelection(const FName InPresetName);`
- L126 _private prototype_ `void ApplyPresetToSelection(const FAvaSequencePreset& InPreset);`
- L128 _private member_ `TWeakPtr<IAvaSequencer> WeakAvaSequencer;`
- L130 _private member_ `TSharedRef<FUICommandList> ToolCommands;`
- L132 _private member_ `FDelegateHandle DragDropInitializedDelegate;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace AvaSequencer` (scope `UE`)

### `Plugins/Experimental/AvalancheSequenceNavigator/Source/AvalancheSequenceNavigator/Private/AvaSequenceNavigatorCommands.h` (Private)


#### class `FAvaSequenceNavigatorCommands`  
`class FAvaSequenceNavigatorCommands : public TCommands<FAvaSequenceNavigatorCommands>`  
_L8-32_
- inherits: `TCommands<FAvaSequenceNavigatorCommands>`
- L11 _public function_ `FAvaSequenceNavigatorCommands() : TCommands<FAvaSequenceNavigatorCommands>(TEXT("AvaSequenceNavigatorCommands") , NSLOCTEXT("MotionDesignSequenceNavigatorCommands", "MotionDesignSequenceNavigatorCommands", "Motion Design Sequence Navigator Commands") , NAME_None , FAppStyle::GetAppStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> AddNew;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> PlaySelected;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ContinueSelected;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> StopSelected;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ExportSequence;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> SpawnSequencePlayer;`

### `Plugins/Experimental/AvalancheSequenceNavigator/Source/AvalancheSequenceNavigator/Private/AvalancheSequenceNavigatorModule.h` (Private)


#### class `FAvalancheSequenceNavigatorModule`  
`class FAvalancheSequenceNavigatorModule : public IModuleInterface`  
_L17-38_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _private prototype_ `void OnSequencerCreated(const TSharedRef<ISequencer> InSequencer);`
- L27 _private prototype_ `void OnSequencerClosed(const TSharedRef<ISequencer> InSequencer);`
- L29 _private prototype_ `void OnAvaSequencerCreated(const TSharedRef<IAvaSequencer> InAvaSequencer);`
- L31 _private member_ `FDelegateHandle SequencerCreatedHandle;`
- L32 _private member_ `FDelegateHandle SequencerClosedHandle;`
- L34 _private member_ `FDelegateHandle AvaSequencerCreatedHandle;`
- L37 _private member_ `TSharedPtr<UE::AvaSequencer::FAvaNavigationToolProvider> NavigationToolProvider;` — The provider that supplies data and extends the Sequence Navigator

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace AvaSequencer` (scope `UE`)

### `Plugins/Experimental/AvalancheSequenceNavigator/Source/AvalancheSequenceNavigator/Private/Columns/AvaNavigationToolStatusColumn.h` (Private)


#### class `UE::SequenceNavigator::FAvaNavigationToolStatusColumn`  
`class FAvaNavigationToolStatusColumn : public FNavigationToolColumn`  
_L13-34_
- inherits: `FNavigationToolColumn`
- L20 _public function_ `static FName StaticColumnId()`
- L24 _protected function_ `virtual FName GetColumnId() const override`
- L25 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L26 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L27 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L28 _protected function_ `virtual float GetFillWidth() const override`
- L29 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InToolView, const float InFillSize) override;`
- L30 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHESEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/AvalancheSequenceNavigator/Source/AvalancheSequenceNavigator/Private/Columns/SAvaNavigationToolStatus.h` (Private)


#### class `UE::SequenceNavigator::SAvaNavigationToolStatus`  
`class SAvaNavigationToolStatus : public SCompoundWidget`  
_L18-49_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SAvaNavigationToolStatus)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget , const TSharedRef<ISequencer>& InSequencer);`
- L32 _private prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L35 _private prototype_ `FText GetProgressText() const;`
- L37 _private prototype_ `TOptional<float> GetProgressPercent() const;`
- L39 _private member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L40 _private member_ `TWeakPtr<INavigationToolView> WeakView;`
- L41 _private member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L42 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L44 _private member_ `FText StatusText;`
- L45 _private member_ `FFrameTime CurrentFrame;`
- L46 _private member_ `FFrameTime TotalFrames;`
- L47 _private member_ `float Progress = 0.f;`
- L48 _private member_ `bool bSequenceInProgress = false;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/AvalancheSequenceNavigator/Source/AvalancheSequenceNavigator/Private/DragDrop/NavigationToolAvaSequenceDropHandler.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolAvaSequenceDropHandler`  
`class FNavigationToolAvaSequenceDropHandler : public FNavigationToolItemDropHandler`  
_L17-41_
- inherits: `FNavigationToolItemDropHandler`
- L24 _public prototype_ `FNavigationToolAvaSequenceDropHandler(const TWeakPtr<IAvaSequencer>& InWeakAvaSequencer);`
- L28 _protected prototype_ `virtual bool IsDraggedItemSupported(const FNavigationToolViewModelPtr& InDraggedItem) const override;`
- L29 _protected prototype_ `virtual TOptional<EItemDropZone> CanDrop(const EItemDropZone InDropZone , const FNavigationToolViewModelPtr& InTargetItem) const override;`
- L31 _protected prototype_ `virtual bool Drop(const EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem) override;`
- L34 _protected prototype_ `void MoveItems(const EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem);`
- L36 _protected prototype_ `void DuplicateItems(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems , const FNavigationToolViewModelWeakPtr& InWeakRelativeItem , const TOptional<EItemDropZone>& InRelativeDropZone);`
- L40 _protected member_ `TWeakPtr<IAvaSequencer> WeakAvaSequencer;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHESEQUENCENAVIGATOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/AvalancheSequenceNavigator/Source/AvalancheSequenceNavigator/Private/Items/NavigationToolAvaSequence.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolAvaSequence`  
`class FNavigationToolAvaSequence : public FNavigationToolSequence`  
_L15-62_
- inherits: `FNavigationToolSequence`
- desc: Item in Navigation Tool representing a Motion Design Sequence.
- L19 _public prototype_ `UE_SEQUENCER_DECLARE_CASTABLE(FNavigationToolAvaSequence , FNavigationToolSequence) FNavigationToolAvaSequence(INavigationTool& InTool , const FNavigationToolViewModelPtr& InParentItem , UAvaSequence* const InAvaSequence);`
- L28 _public prototype_ `virtual bool AddChild(const FNavigationToolAddItemParams& InAddItemParams) override;`
- L29 _public prototype_ `virtual bool RemoveChild(const FNavigationToolRemoveItemParams& InRemoveItemParams) override;`
- L30 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`
- L31 _public prototype_ `virtual void GetItemProxies(TArray<TSharedPtr<FNavigationToolItemProxy>>& OutItemProxies) override;`
- L33 _public function_ `virtual bool ShouldSort() const override`
- L34 _public function_ `virtual bool CanBeTopLevel() const override`
- L36 _public prototype_ `virtual bool CanRename() const override;`
- L37 _public prototype_ `virtual void Rename(const FText& InNewName) override;`
- L39 _public prototype_ `virtual bool CanDelete() const override;`
- L40 _public prototype_ `virtual bool Delete() override;`
- L42 _public prototype_ `virtual FText GetDisplayName() const override;`
- L43 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L44 _public prototype_ `virtual FSlateColor GetIconColor() const override;`
- L46 _public prototype_ `virtual void OnSelect() override;`
- L47 _public prototype_ `virtual void OnDoubleClick() override;`
- L52 _public prototype_ `virtual TOptional<FColor> GetColor() const override;`
- L53 _public prototype_ `virtual void SetColor(const TOptional<FColor>& InColor) override;`
- L56 _public prototype_ `UAvaSequence* GetAvaSequence() const;`
- L60 _protected prototype_ `virtual FNavigationToolItemId CalculateItemId() const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)
