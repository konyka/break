# Plugins / CinematicSequenceNavigator

- module root: `Plugins/Experimental/CinematicSequenceNavigator/Source/CinematicSequenceNavigator`
- headers: 3; symbols: 45
- symbol kinds: class=3, function=1, member=9, namespace=6, prototype=26
- PrivateDependencyModuleNames: CineAssemblyTools, CoreUObject, Engine, MovieScene, SequenceNavigator, Sequencer, SequencerCore, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/CinematicSequenceNavigator/Source/CinematicSequenceNavigator/Private/CinematicNavigationToolProvider.h` (Private)


#### class `UE::CineAssemblyTools::FCinematicNavigationToolProvider`  
`class FCinematicNavigationToolProvider : public SequenceNavigator::FNavigationToolProvider`  
_L28-83_
- inherits: `SequenceNavigator::FNavigationToolProvider`
- L31 _public member_ `static const FName Identifier;`
- L33 _public member_ `static const FText CinematicColumnViewName;`
- L35 _public prototype_ `FCinematicNavigationToolProvider(const TSharedRef<ISequencer>& InSequencer);`
- L36 _public prototype_ `virtual ~FCinematicNavigationToolProvider() override = default;`
- L40 _public prototype_ `virtual FName GetIdentifier() const override;`
- L42 _public prototype_ `virtual TSet<TSubclassOf<UMovieSceneSequence>> GetSupportedSequenceClasses() const override;`
- L44 _public prototype_ `virtual FText GetDefaultColumnView() const override;`
- L46 _public prototype_ `virtual FNavigationToolSaveState* GetSaveState(const SequenceNavigator::INavigationTool& InTool) const override;`
- L47 _public prototype_ `virtual void SetSaveState(const SequenceNavigator::INavigationTool& InTool, const FNavigationToolSaveState& InSaveState) const override;`
- L49 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L51 _public prototype_ `virtual void OnActivate() override;`
- L52 _public prototype_ `virtual void OnDeactivate() override;`
- L54 _public prototype_ `virtual void OnExtendColumns(SequenceNavigator::FNavigationToolColumnExtender& OutExtender) override;`
- L55 _public prototype_ `virtual void OnExtendColumnViews(TSet<FNavigationToolColumnView>& OutColumnViews) override;`
- L56 _public prototype_ `virtual void OnExtendItemChildren(SequenceNavigator::INavigationTool& InTool , const SequenceNavigator::FNavigationToolViewModelPtr& InParentItem , TArray<SequenceNavigator::FNavigationToolViewModelWeakPtr>& OutWeakChildren , const bool bInRecursive) override;`
- L60 _public prototype_ `virtual void OnExtendBuiltInFilters(TArray<FNavigationToolBuiltInFilterParams>& OutFilterParams) override;`
- L65 _private member_ `static const FName ToolbarSectionName;`
- L66 _private member_ `static const FName ContextMenuSectionName;`
- L68 _private prototype_ `TSharedPtr<SequenceNavigator::INavigationTool> GetNavigationTool() const;`
- L70 _private prototype_ `void ExtendToolToolBar();`
- L71 _private prototype_ `void ExtendToolItemContextMenu();`
- L73 _private prototype_ `void RemoveToolToolBarExtension();`
- L74 _private prototype_ `void RemoveToolItemContextMenuExtension();`
- L76 _private prototype_ `void ExtendToolItemDragDropOp(SequenceNavigator::FNavigationToolItemDragDropOp& InDragDropOp);`
- L78 _private prototype_ `FMovieSceneEditorData* GetRootMovieSceneEditorData(const UE::SequenceNavigator::INavigationTool& InTool) const;`
- L80 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L82 _private member_ `TSharedRef<FUICommandList> ToolCommands;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace CineAssemblyTools` (scope `UE`)

### `Plugins/Experimental/CinematicSequenceNavigator/Source/CinematicSequenceNavigator/Private/CinematicSequenceNavigatorCommands.h` (Private)


#### class `FCinematicSequenceNavigatorCommands`  
`class FCinematicSequenceNavigatorCommands : public TCommands<FCinematicSequenceNavigatorCommands>`  
_L8-23_
- inherits: `TCommands<FCinematicSequenceNavigatorCommands>`
- L11 _public function_ `FCinematicSequenceNavigatorCommands() : TCommands<FCinematicSequenceNavigatorCommands>(TEXT("CinematicSequenceNavigatorCommands") , NSLOCTEXT("CinematicSequenceNavigatorCommands" , "CinematicSequenceNavigatorCommands", "Cinematic Sequence Navigator Commands") , NAME_None , FAppStyle::GetAppStyleSetName())`
- L20 _public prototype_ `virtual void RegisterCommands() override;`

### `Plugins/Experimental/CinematicSequenceNavigator/Source/CinematicSequenceNavigator/Private/CinematicSequenceNavigatorModule.h` (Private)


#### class `FCinematicSequenceNavigatorModule`  
`class FCinematicSequenceNavigatorModule : public IModuleInterface`  
_L16-33_
- inherits: `IModuleInterface`
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _private prototype_ `void OnSequencerCreated(const TSharedRef<ISequencer> InSequencer);`
- L26 _private prototype_ `void OnSequencerClosed(const TSharedRef<ISequencer> InSequencer);`
- L28 _private member_ `FDelegateHandle SequencerCreatedHandle;`
- L29 _private member_ `FDelegateHandle SequencerClosedHandle;`
- L32 _private member_ `TSharedPtr<UE::CineAssemblyTools::FCinematicNavigationToolProvider> NavigationToolProvider;` — The provider that supplies data and extends the Sequence Navigator

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CineAssemblyTools` (scope `UE`)
