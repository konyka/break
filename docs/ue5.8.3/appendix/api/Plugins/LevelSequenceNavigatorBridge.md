# Plugins / LevelSequenceNavigatorBridge

- module root: `Plugins/Experimental/LevelSequenceNavigatorBridge/Source/LevelSequenceNavigatorBridge`
- headers: 2; symbols: 29
- symbol kinds: class=2, member=6, namespace=2, prototype=19
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, LevelSequence, MovieScene, SequenceNavigator, Sequencer, SequencerCore, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/LevelSequenceNavigatorBridge/Source/LevelSequenceNavigatorBridge/Private/LevelSequenceNavigationToolProvider.h` (Private)


#### class `FLevelSequenceNavigationToolProvider`  
`class FLevelSequenceNavigationToolProvider : public UE::SequenceNavigator::FNavigationToolProvider`  
_L24-65_
- inherits: `UE::SequenceNavigator::FNavigationToolProvider`
- L27 _public member_ `static const FName Identifier;`
- L29 _public member_ `static const FText AnimationColumnViewName;`
- L31 _public prototype_ `FLevelSequenceNavigationToolProvider();`
- L32 _public prototype_ `virtual ~FLevelSequenceNavigationToolProvider() override = default;`
- L36 _public prototype_ `virtual FName GetIdentifier() const override;`
- L38 _public prototype_ `virtual TSet<TSubclassOf<UMovieSceneSequence>> GetSupportedSequenceClasses() const override;`
- L40 _public prototype_ `virtual FText GetDefaultColumnView() const override;`
- L42 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L44 _public prototype_ `virtual void OnActivate() override;`
- L45 _public prototype_ `virtual void OnDeactivate() override;`
- L47 _public prototype_ `virtual void OnExtendColumns(UE::SequenceNavigator::FNavigationToolColumnExtender& OutExtender) override;`
- L48 _public prototype_ `virtual void OnExtendColumnViews(TSet<FNavigationToolColumnView>& OutColumnViews) override;`
- L49 _public prototype_ `virtual void OnExtendItemChildren(UE::SequenceNavigator::INavigationTool& InTool , const UE::SequenceNavigator::FNavigationToolViewModelPtr& InParentItem , TArray<UE::SequenceNavigator::FNavigationToolViewModelWeakPtr>& OutWeakChildren , const bool bInRecursive) override;`
- L53 _public prototype_ `virtual void OnExtendBuiltInFilters(TArray<FNavigationToolBuiltInFilterParams>& OutFilterParams) override;`
- L55 _public prototype_ `virtual FNavigationToolSaveState* GetSaveState(const UE::SequenceNavigator::INavigationTool& InTool) const override;`
- L56 _public prototype_ `virtual void SetSaveState(const UE::SequenceNavigator::INavigationTool& InTool , const FNavigationToolSaveState& InSaveState) const override;`
- L62 _private prototype_ `FMovieSceneEditorData* GetRootMovieSceneEditorData(const UE::SequenceNavigator::INavigationTool& InTool) const;`
- L64 _private member_ `TSharedRef<FUICommandList> ToolCommands;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/LevelSequenceNavigatorBridge/Source/LevelSequenceNavigatorBridge/Private/LevelSequenceNavigatorBridgeModule.h` (Private)


#### class `FLevelSequenceNavigatorBridgeModule`  
`class FLevelSequenceNavigatorBridgeModule : public IModuleInterface`  
_L12-29_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private prototype_ `void OnSequencerCreated(const TSharedRef<ISequencer> InSequencer);`
- L22 _private prototype_ `void OnSequencerClosed(const TSharedRef<ISequencer> InSequencer);`
- L24 _private member_ `FDelegateHandle SequencerCreatedHandle;`
- L25 _private member_ `FDelegateHandle SequencerClosedHandle;`
- L28 _private member_ `TSharedPtr<FLevelSequenceNavigationToolProvider> NavigationToolProvider;` — The provider that supplies data and extends the Sequence Navigator
