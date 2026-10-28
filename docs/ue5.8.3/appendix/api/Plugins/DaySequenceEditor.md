# Plugins / DaySequenceEditor

- module root: `Plugins/Experimental/DaySequence/Source/DaySequenceEditor`
- headers: 29; symbols: 344
- symbol kinds: class=29, delegate=9, function=30, macro=2, member=84, prototype=186, struct=4
- DynamicallyLoadedModuleNames: PropertyEditor
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, ClassViewer, CoreUObject, DaySequence, EditorFramework, EditorStyle, EditorSubsystem, EditorWidgets, Engine, InputCore, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneCaptureDialog, MovieSceneTools, MovieSceneTracks, Projects, SceneOutliner, Sequencer, SequencerScripting, Slate, SlateCore, SubobjectEditor, ToolMenus, ToolWidgets, UnrealEd, VREditor, ViewportInteraction, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/AssetDefinition_DaySequence.h` (Private)


#### class `UAssetDefinition_DaySequence`  
`class UAssetDefinition_DaySequence : public UAssetDefinitionDefault`  
_L11-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L26 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/AssetDefinition_DaySequenceCollectionAsset.h` (Private)


#### class `UAssetDefinition_DaySequenceCollectionAsset`  
`class UAssetDefinition_DaySequenceCollectionAsset : public UAssetDefinitionDefault`  
_L15-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L20 _public function_ `virtual FText GetAssetDisplayName() const override`
- L21 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L22 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`

#### class `UDaySequenceCollectionAssetFactory`  
`class UDaySequenceCollectionAssetFactory : public UFactory`  
_L26-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L31 _public prototype_ `UDaySequenceCollectionAssetFactory(const class FObjectInitializer& Obj);`
- L33 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DAYSEQUENCEEDITOR_API`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceActorDetails.h` (Private)


#### class `FDaySequenceActorDetails`  
`class FDaySequenceActorDetails : public IDetailCustomization`  
_L12-25_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L24 _private member_ `TWeakObjectPtr<ADaySequenceActor> DaySequenceActor;` — The selected DaySequence sequence actor

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceActorFactory.h` (Private)


#### class `UDaySequenceActorFactory`  
`class UDaySequenceActorFactory : public UActorFactory`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L19 _private prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;`
- L20 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L21 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceActorPreview.h` (Private)


#### class `FDaySequenceActorPreview`  
`class FDaySequenceActorPreview : public FTickableEditorObject`  
_L17-106_
- inherits: `FTickableEditorObject`
- desc: Mediates the preview of DaySequenceActor sequences.
- L20 _public prototype_ `virtual ~FDaySequenceActorPreview();`
- L23 _public prototype_ `bool IsValid() const;` — @return true if the current state has a valid DaySequence actor.
- L26 _public prototype_ `TWeakObjectPtr<ADaySequenceActor> GetPreviewActor() const;` — @return Weak pointer to the DaySequence actor.
- L29 _public prototype_ `TWeakPtr<ISequencer> GetPreviewSequencer() const;` — @return Weak pointer to the sequencer instance hosting the DaySequence actor preview.
- L32 _public prototype_ `float GetPreviewTime() const;` — @return float, the preview time in hours
- L39 _public prototype_ `void SetPreviewTime(float PreviewTime);` — Sets the preview time on the preview sequencer instance. @param PreviewTime the time to set in hours.
- L42 _public prototype_ `bool IsPreviewEnabled() const;` — @return true if there is an active preview.
- L45 _public prototype_ `float GetDayLength() const;` — @return the length of a game day in hours.
- L53 _public prototype_ `void EnablePreview(bool bEnable);` — Enables/disables the actor preview for the current DaySequence actor. This will only enable actor preview if there are no active Sequence Editor toolkits. @param bEnable if true, initializes a new preview, otherwise shuts down any active preview.
- L56 _public prototype_ `void Register();` — Register actor preview state delegates.
- L59 _public prototype_ `void Deregister();` — Deregister actor preview state delegates.
- L67 _public prototype_ `TSharedRef<SWidget> MakeTransportControls(bool bExtended) const;` — Utility function to generate transport controls for the preview sequencer. @param bExtended if true, add extended Sequencer playback controls @return transport control widget if preview sequencer is valid, SNullWidget otherwise.
- L71 _protected prototype_ `void UpdateActorPreview();` — Synchronize the actor preview state to the editor world.
- L74 _protected prototype_ `void ClosePreviewToolkit();` — Close the active preview toolkit.
- L80 _protected prototype_ `void UpdateLevelEditorViewports();` — Invalidate level editor viewports to ensure a tick is fired to process any invalidated main sequences on the active DaySequenceActor.
- L82 _protected prototype_ `void OnTimeOfDayPreviewChanged(float PreviewHours);`
- L83 _protected prototype_ `void OnBlueprintPreCompile(UBlueprint* Blueprint);`
- L84 _protected prototype_ `void OnPreRootSequenceChanged();`
- L85 _protected prototype_ `void OnPostRootSequenceChanged();`
- L86 _protected prototype_ `void OnDaySequenceToolkitPostMapChanged();`
- L87 _protected prototype_ `void OnMapChanged(uint32 MapChangeFlags);`
- L88 _protected prototype_ `void OnGlobalTimeChanged();`
- L89 _protected prototype_ `void OnBeginPIE(bool bSimulate);`
- L90 _protected prototype_ `void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);`
- L93 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L94 _protected function_ `virtual ETickableTickType GetTickableTickType() const override`
- L95 _protected prototype_ `virtual bool IsTickable() const override;`
- L96 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L100 _private prototype_ `void UpdateDetails();`
- L103 _private member_ `TWeakObjectPtr<ADaySequenceActor> DaySequenceActor = nullptr;`
- L104 _private member_ `TWeakPtr<FDaySequenceEditorToolkit> DaySequencePreviewToolkit;`
- L105 _private member_ `float LastPreviewTime = -1.f;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorActorBinding.h` (Private)


#### class `FDaySequenceEditorActorBinding`  
`class FDaySequenceEditorActorBinding : public ISequencerEditorObjectBinding`  
_L11-32_
- inherits: `ISequencerEditorObjectBinding`
- L15 _public prototype_ `FDaySequenceEditorActorBinding(TSharedRef<ISequencer> InSequencer);`
- L18 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerEditorObjectBinding interface
- L19 _public prototype_ `virtual void BuildSequencerAddMenu(FMenuBuilder& MenuBuilder) override;`
- L20 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L25 _private prototype_ `void AddPossessActorMenuExtensions(FMenuBuilder& MenuBuilder);` — Menu extension callback for the add menu
- L28 _private prototype_ `void AddActorsToSequencer(AActor*const* InActors, int32 NumActors);` — Add the specified actors to the sequencer
- L31 _private member_ `TWeakPtr<ISequencer> Sequencer;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorActorSpawner.h` (Private)


#### class `FDaySequenceEditorActorSpawner`  
`class FDaySequenceEditorActorSpawner : public FDaySequenceActorSpawner`  
_L9-21_
- inherits: `FDaySequenceActorSpawner`
- L12 _public prototype_ `static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();`
- L15 _public function_ `virtual bool IsEditor() const override` — IMovieSceneObjectSpawner interface
- L17 _public prototype_ `virtual TValueOrError<FNewSpawnable, FText> CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory = nullptr) override;`
- L18 _public prototype_ `virtual void SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings) override;`
- L19 _public prototype_ `virtual bool CanSetupDefaultsForSpawnable(UObject* SpawnedObject) const override;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorCommands.h` (Private)


#### class `FDaySequenceEditorCommands`  
`class FDaySequenceEditorCommands : public TCommands<FDaySequenceEditorCommands>`  
_L8-40_
- inherits: `TCommands<FDaySequenceEditorCommands>`
- L12 _public function_ `FDaySequenceEditorCommands() : TCommands<FDaySequenceEditorCommands>(TEXT("DaySequence"), NSLOCTEXT("Contexts", "DaySequence", "DaySequence Plugin"), NAME_None, FDaySequenceEditorStyle::GetStyleSetName())`
- L18 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L21 _public member_ `TSharedPtr<FUICommandInfo> OverrideInitialTimeOfDay;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> OverrideRunDayCycle;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> SelectDaySequenceActor;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> RefreshDaySequenceActor;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> OpenDaySequenceActor;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> OpenRootSequence;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> SnapSectionsToTimelineUsingSourceTimecode;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SyncSectionsUsingSourceTimecode;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> BakeTransform;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> FixActorReferences;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> AddActorsToBinding;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> RemoveActorsFromBinding;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> ReplaceBindingWithActors;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> RemoveAllBindings;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> RemoveInvalidBindings;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorMenuContext.h` (Private)


#### class `UDaySequenceEditorMenuContext`  
`class UDaySequenceEditorMenuContext : public UObject`  
_L11-16_
- reflection: `UCLASS()`
- inherits: `UObject`
- L15 _public member_ `TWeakPtr<FDaySequenceEditorToolkit> Toolkit;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorSettings.h` (Private)


#### struct `FDaySequencePropertyTrackSettings`  
`struct FDaySequencePropertyTrackSettings`  
_L11-22_
- reflection: `USTRUCT()`
- L17 _public member_ `FString ComponentPath;` — `UPROPERTY(config, EditAnywhere, Category=PropertyTrack)` — Optional ActorComponent tag (when keying a component property).
- L21 _public member_ `FString PropertyPath;` — `UPROPERTY(config, EditAnywhere, Category=PropertyTrack)` — Path to the keyed property within the Actor or ActorComponent.

#### struct `FDaySequenceTrackSettings`  
`struct FDaySequenceTrackSettings`  
_L26-49_
- reflection: `USTRUCT()`
- L32 _public member_ `FSoftClassPath MatchingActorClass;` — `UPROPERTY(config, noclear, EditAnywhere, Category=TrackSettings, meta=(MetaClass="/Script/Engine.Actor"))` — The Actor class to create movie scene tracks for.
- L36 _public member_ `TArray<FSoftClassPath> DefaultTracks;` — `UPROPERTY(config, noclear, EditAnywhere, Category=TrackSettings, meta=(MetaClass="/Script/MovieScene.MovieSceneTrack"))` — List of movie scene track classes to be added automatically.
- L40 _public member_ `TArray<FSoftClassPath> ExcludeDefaultTracks;` — `UPROPERTY(config, noclear, EditAnywhere, Category=TrackSettings, meta=(MetaClass="/Script/MovieScene.MovieSceneTrack"))` — List of movie scene track classes not to be added automatically.
- L44 _public member_ `TArray<FDaySequencePropertyTrackSettings> DefaultPropertyTracks;` — `UPROPERTY(config, EditAnywhere, Category=TrackSettings)` — List of property names for which movie scene tracks will be created automatically.
- L48 _public member_ `TArray<FDaySequencePropertyTrackSettings> ExcludeDefaultPropertyTracks;` — `UPROPERTY(config, EditAnywhere, Category=TrackSettings)` — List of property names for which movie scene tracks will not be created automatically.

#### class `UDaySequenceEditorSettings`  
`class UDaySequenceEditorSettings : public UObject`  
_L56-76_
- reflection: `UCLASS(config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: DaySequence Editor settings.
- L63 _public prototype_ `UDaySequenceEditorSettings(const FObjectInitializer& ObjectInitializer);`
- L67 _public member_ `TArray<FDaySequenceTrackSettings> TrackSettings;` — `UPROPERTY(config, EditAnywhere, Category=Tracks)` — Specifies class properties for which movie scene tracks will be created automatically.
- L71 _public member_ `bool bAutoBindToPIE;` — `UPROPERTY(config, EditAnywhere, Category=Playback)` — Specifies whether to automatically bind an active sequencer UI to PIE worlds.
- L75 _public member_ `bool bAutoBindToSimulate;` — `UPROPERTY(config, EditAnywhere, Category=Playback)` — Specifies whether to automatically bind an active sequencer UI to simulate worlds.

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorSpecializedBinding.h` (Private)


#### class `FDaySequenceEditorSpecializedBinding`  
`class FDaySequenceEditorSpecializedBinding : public ISequencerEditorObjectBinding`  
_L11-29_
- inherits: `ISequencerEditorObjectBinding`
- L15 _public prototype_ `FDaySequenceEditorSpecializedBinding(TSharedRef<ISequencer> InSequencer);`
- L18 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerEditorObjectBinding interface
- L19 _public prototype_ `virtual void BuildSequencerAddMenu(FMenuBuilder& MenuBuilder) override;`
- L20 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L25 _private prototype_ `void AddSpecializedBindingMenuExtensions(FMenuBuilder& MenuBuilder);` — Menu extension callback for the specialized binding menu
- L28 _private member_ `TWeakPtr<ISequencer> Sequencer;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorStyle.h` (Private)


#### class `FDaySequenceEditorStyle`  
`class FDaySequenceEditorStyle`  
_L9-28_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static void ReloadTextures();` — Reloads textures used by slate renderer
- L19 _public prototype_ `static TSharedRef<ISlateStyle> Get();` — @return The Slate style set for the Shooter game
- L21 _public prototype_ `static FName GetStyleSetName();`
- L24 _private prototype_ `static TSharedRef<class FSlateStyleSet> Create();`
- L27 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleInstance;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorToolkit.h` (Private)


#### class `FDaySequenceEditorToolkit`  
`class FDaySequenceEditorToolkit : public IDaySequenceEditorToolkit , public FGCObject`  
_L29-202_
- inherits: `IDaySequenceEditorToolkit,FGCObject`
- desc: Implements an Editor toolkit for Day sequences.
- L40 _public prototype_ `FDaySequenceEditorToolkit(const TSharedRef<ISlateStyle>& InStyle);` — Creates and initializes a new instance. @param InStyle The style set to use.
- L43 _public prototype_ `virtual ~FDaySequenceEditorToolkit();` — Virtual destructor
- L48 _public prototype_ `static void IterateOpenToolkits(TFunctionRef<bool(FDaySequenceEditorToolkit&)> Iter);` — Iterate all open Day sequence editor toolkits
- L51 _public prototype_ `static void CloseOpenToolkits(TFunctionRef<bool(FDaySequenceEditorToolkit&)> Iter);` — Iterates over the open toolkits and closes them if Iter returns true.
- L54 _public prototype_ `static bool HasOpenSequenceEditorToolkits();` — @return true if any open toolkits are hosted by the sequence editor.
- L57 _public prototype_ `static bool HasOpenActorPreviewToolkits();` — @return true if any open toolkits are actor preview.
- L60 _public prototype_ `DECLARE_EVENT_OneParam(FDaySequenceEditorToolkit, FDaySequenceEditorToolkitOpened, FDaySequenceEditorToolkit&);` — Called when a toolkit is opened
- L61 _public prototype_ `static FDaySequenceEditorToolkitOpened& OnOpened();`
- L64 _public prototype_ `DECLARE_EVENT_OneParam(FDaySequenceEditorToolkit, FDaySequenceEditorToolkitClosed, FDaySequenceEditorToolkit&);` — Called when a toolkit is closed
- L65 _public prototype_ `static FDaySequenceEditorToolkitClosed& OnClosed();`
- L68 _public prototype_ `DECLARE_EVENT_OneParam(FDaySequenceEditorToolkit, FDaySequenceEditorToolkitDestroyed, FDaySequenceEditorToolkit&);` — Called when a toolkit is destroyed
- L69 _public prototype_ `static FDaySequenceEditorToolkitDestroyed& OnDestroyed();`
- L72 _public prototype_ `DECLARE_EVENT(FDaySequenceEditorToolkit, FDaySequenceEditorToolkitPostMapChanged);` — Called after this class has processed its MapChanged event.
- L73 _public prototype_ `static FDaySequenceEditorToolkitPostMapChanged& OnToolkitPostMapChanged();`
- L84 _public prototype_ `void Initialize(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UDaySequence* InDaySequence);` — Initialize this asset editor. @param Mode Asset editing mode for this editor (standalone or world-centric). @param InitToolkitHost When Mode is WorldCentric, this is the level editor instance to spawn this editor within. @param InDaySequence The animation to edit.
- L89 _public prototype_ `void InitializeActorPreview(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, ADaySequenceActor* InDayActor);` — Initialize a read-only asset editor for previewing a DaySequenceActor.
- L92 _public function_ `bool IsActive() const` — @return true if this toolkit is initialized and open.
- L99 _public function_ `bool IsActorPreview() const` — @return true if this toolkit was initialized for an Actor Preview.
- L109 _public function_ `virtual TSharedPtr<ISequencer> GetSequencer() const override` — Get the sequencer object being edited in this tool kit. @return Sequencer object.
- L117 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L121 _public function_ `virtual FString GetReferencerName() const override`
- L126 _public prototype_ `virtual void OnClose() override;`
- L127 _public prototype_ `virtual bool CanFindInContentBrowser() const override;`
- L128 _public function_ `virtual bool CanSaveAsset() const override`
- L129 _public function_ `virtual bool CanSaveAssetAs() const override`
- L135 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L136 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L137 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L138 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L139 _public prototype_ `virtual FText GetTabSuffix() const override;`
- L142 _public function_ `virtual bool IncludeAssetInRestoreOpenAssetsPrompt() const override`
- L147 _protected prototype_ `void AddDefaultTracksForActor(AActor& Actor, const FGuid Binding);` — Add default movie scene tracks for the given actor.
- L150 _protected prototype_ `void OnSequencerReceivedFocus();` — Called whenever sequencer has received focus
- L153 _protected prototype_ `void OnInitToolMenuContext(FToolMenuContext& MenuContext);` — Called whenever sequencer in initializing tool menu context
- L156 _private prototype_ `void InitializeInternal( const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, const FSequencerInitParams& SequencerInitParams, TSharedRef<FDaySequenceEditorSpawnRegister>& SpawnRegister);`
- L162 _private prototype_ `void ExtendSequencerToolbar(FName InToolMenuName);`
- L165 _private prototype_ `void HandleMapChanged(UWorld* NewWorld, EMapChangeType MapChangeType);` — Callback for map changes.
- L168 _private prototype_ `TSharedRef<FExtender> HandleMenuExtensibilityGetExtender(const TSharedRef<FUICommandList> CommandList, const TArray<UObject*> ContextSensitiveObjects);` — Callback for the menu extensibility manager.
- L171 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args);` — Callback for spawning tabs.
- L174 _private prototype_ `void HandleActorAddedToSequencer(AActor* Actor, const FGuid Binding);` — Callback for actor added to sequencer.
- L177 _private prototype_ `void OnGlobalTimeChanged();` — Callback for keeping Day Sequence Actor preview time correct when editing a day sequence asset.
- L182 _private member_ `TObjectPtr<UDaySequence> DaySequence = nullptr;` — Time of day sequence viewed/edited by this toolkit.
- L185 _private member_ `TSharedPtr<ISequencer> Sequencer;` — The sequencer used by this editor.
- L188 _private member_ `TSharedRef<ISlateStyle> Style;` — Pointer to the style set to use for toolkits.
- L191 _private member_ `TSharedPtr<FDaySequencePlaybackContext> PlaybackContext;` — Instance of a class used for managing the playback context for a Day sequence.
- L194 _private member_ `ADaySequenceActor* PreviewActor = nullptr;` — The actor being previewed if this Toolkit was initialized for an Actor Preview.
- L197 _private member_ `ADaySequenceActor* RootActor = nullptr;` — The actor that owns the sequence if this Toolkit was initialized to the actor's root sequence.
- L201 _private member_ `static const FName SequencerMainTabId;` — The tab ids for all the tabs used

#### Free symbols / members of external scopes

- L60 _delegate_ `DECLARE_EVENT_OneParam(FDaySequenceEditorToolkit, FDaySequenceEditorToolkitOpened, FDaySequenceEditorToolkit&);` — Called when a toolkit is opened
- L64 _delegate_ `DECLARE_EVENT_OneParam(FDaySequenceEditorToolkit, FDaySequenceEditorToolkitClosed, FDaySequenceEditorToolkit&);` — Called when a toolkit is closed
- L68 _delegate_ `DECLARE_EVENT_OneParam(FDaySequenceEditorToolkit, FDaySequenceEditorToolkitDestroyed, FDaySequenceEditorToolkit&);` — Called when a toolkit is destroyed
- L72 _delegate_ `DECLARE_EVENT(FDaySequenceEditorToolkit, FDaySequenceEditorToolkitPostMapChanged);` — Called after this class has processed its MapChanged event.

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceFactoryNew.h` (Private)


#### class `UDaySequenceFactoryNew`  
`class UDaySequenceFactoryNew : public UFactory`  
_L13-26_
- reflection: `UCLASS(BlueprintType, hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UDaySequence objects.
- L17 _public prototype_ `UDaySequenceFactoryNew();`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L21 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L25 _private prototype_ `void AddDefaultBindings(UDaySequence* NewDaySequence);`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequencePlaybackContext.h` (Private)


#### class `FDaySequencePlaybackContext`  
`class FDaySequencePlaybackContext : public TSharedFromThis<FDaySequencePlaybackContext>`  
_L17-84_
- inherits: `TSharedFromThis<FDaySequencePlaybackContext>`
- desc: Class that manages the current playback context that a Time of Day editor should use for playback
- L21 _public prototype_ `FDaySequencePlaybackContext(UDaySequence* InDaySequence);`
- L22 _public prototype_ `~FDaySequencePlaybackContext();`
- L27 _public prototype_ `UDaySequence* GetDaySequence() const;` — Gets the Day sequence for which we are trying to find the context.
- L32 _public prototype_ `TSharedRef<SWidget> BuildWorldPickerCombo();` — Build a world picker widget that allows the user to choose a world, and exit the auto-bind settings
- L37 _public prototype_ `ADaySequenceActor* GetPlaybackContext() const;` — Resolve the current world context pointer. Can never be nullptr.
- L42 _public prototype_ `UObject* GetPlaybackContextAsObject() const;` — Returns GetPlaybackContext as a plain object.
- L47 _public prototype_ `ADaySequenceActor* GetPlaybackClient() const;` — Resolve the current playback client. May be nullptr.
- L52 _public prototype_ `IMovieScenePlaybackClient* GetPlaybackClientAsInterface() const;` — Returns GetPlaybackClient as an interface pointer.
- L58 _public prototype_ `void OverrideWith(ADaySequenceActor* InNewClient);` — Specify a new world to use as the context. Persists until the next PIE or map change event. May be null, in which case the context will be recomputed automatically
- L66 _private prototype_ `static ADaySequenceActor* ComputePlaybackContext(const UDaySequence* InDaySequence);` — Compute the new playback context based on the user's current auto-bind settings. Will use the first encountered PIE or Simulate world if possible, else the Editor world as a fallback
- L71 _private prototype_ `void UpdateCachedContext() const;` — Update the cached context and client pointers if needed.
- L73 _private prototype_ `void OnPieEvent(bool);`
- L74 _private prototype_ `void OnMapChange(uint32);`
- L75 _private prototype_ `void OnWorldListChanged(UWorld*);`
- L80 _private member_ `TWeakObjectPtr<UDaySequence> DaySequence;` — Time of Day sequence that we should find a context for
- L83 _private member_ `mutable TWeakObjectPtr<ADaySequenceActor> WeakCurrentContext;` — Mutable cached context pointer

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceTrackEditor.h` (Private)


#### class `FDaySequenceTrackEditor`  
`class FDaySequenceTrackEditor : public FSubTrackEditor`  
_L7-28_
- inherits: `FSubTrackEditor`
- L10 _public prototype_ `FDaySequenceTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L19 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L23 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;` — ISequencerTrackEditor interface
- L26 _public prototype_ `virtual TSubclassOf<UMovieSceneSubTrack> GetSubTrackClass() const;` — FSubTrackEditor interface
- L27 _public prototype_ `virtual void GetSupportedSequenceClassPaths(TArray<FTopLevelAssetPath>& ClassPaths) const override;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/EditableDaySequenceConditionSet.h` (Private)


#### class `UEditableDaySequenceConditionSet`  
`class UEditableDaySequenceConditionSet : public UObject`  
_L10-28_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- L15 _public prototype_ `UEditableDaySequenceConditionSet();`
- L17 _public prototype_ `void SetConditions(const FDaySequenceConditionSet::FConditionValueMap& InConditions);`
- L18 _public prototype_ `FDaySequenceConditionSet::FConditionValueMap& GetConditions();`
- L20 _public prototype_ `FString GetConditionSetExportText();`
- L24 _private member_ `FDaySequenceConditionSet ConditionSet;` — `UPROPERTY()`
- L26 _private member_ `FProperty* ConditionsProperty;`
- L27 _private member_ `FString ConditionsPropertyAsString;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/EnvironmentLightingActorDetails.h` (Private)


#### class `FEnvironmentLightingActorDetails`  
`class FEnvironmentLightingActorDetails : public IDetailCustomization`  
_L9-18_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/MovieSceneSequenceEditor_DaySequence.h` (Private)


#### struct `FMovieSceneSequenceEditor_DaySequence`  
`struct FMovieSceneSequenceEditor_DaySequence : FMovieSceneSequenceEditor`  
_L15-60_
- inherits: `FMovieSceneSequenceEditor`
- L17 _public function_ `virtual bool CanCreateEvents(UMovieSceneSequence* InSequence) const`
- L22 _public function_ `virtual bool CanCreateDirectorBlueprint(UMovieSceneSequence* Sequence) const override`
- L38 _public function_ `virtual UBlueprint* GetBlueprintForSequence(UMovieSceneSequence* InSequence) const override`
- L44 _public function_ `virtual UBlueprint* CreateBlueprintForSequence(UMovieSceneSequence* InSequence) const override`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/SDaySequenceConditionSetCombo.h` (Private)


#### class `SDaySequenceConditionSetCombo`  
`class SDaySequenceConditionSetCombo : public SCompoundWidget`  
_L22-68_
- inherits: `SCompoundWidget`
- desc: Widget for editing a condition set.
- L28 _public function_ `SLATE_BEGIN_ARGS(SDaySequenceConditionSetCombo) : _StructPropertyHandle(nullptr)`
- L32 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, StructPropertyHandle) SLATE_END_ARGS();` — Used for writing changes to the condition set being edited.
- L35 _public prototype_ `void Construct(const FArguments& InArgs);`
- L39 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(UClass* InCondition, const TSharedRef<STableViewBase>& OwnerTable);` — Returns a table row with an SDaySequenceConditionTagChip.
- L42 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — Instantiates the tag picker and sets it as the widget to focus for the ComboButton.
- L45 _private prototype_ `FReply OnClearTagClicked(UClass* InCondition);` — Bound to/called via SDaySequenceConditionTagChip::OnClearPressed. Removes TagToClear from condition set.
- L48 _private prototype_ `void OnConditionExpectedValueChanged(UClass* InCondition, bool bNewPassValue);` — Bound to/called via SDaySequenceConditionTagChip::OnExpectedValueChanged. Sets the expected value for TagToModify to bNewPassValue.
- L50 _private prototype_ `bool GetConditionExpectedValue(UClass* InCondition);`
- L53 _private prototype_ `void RefreshListView();` — Populates ActiveConditionTags with the conditions currently active on the condition set.
- L56 _private member_ `TArray<UClass*> ActiveConditionTags;` — The set of condition tags to display, based on the condition tags present in the condition set we are editing.
- L57 _private member_ `TSharedPtr<SListView<UClass*>> ActiveConditionTagsListView;`
- L60 _private member_ `TSharedPtr<SComboButton> ComboButton;` — Widgets we retain ownership of and refer to in a named manner.
- L61 _private member_ `TSharedPtr<SDaySequenceConditionSetPicker> TagPicker;`
- L64 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Property handle to an FDaySequenceConditionSet, used for accessing the source condition set.
- L67 _private member_ `TStrongObjectPtr<UEditableDaySequenceConditionSet> HelperConditionSet;` — A helper class which is used for propagating changes to the source condition set.

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/SDaySequenceConditionSetPicker.h` (Private)


#### class `SDaySequenceConditionSetPicker`  
`class SDaySequenceConditionSetPicker : public SCompoundWidget`  
_L25-78_
- inherits: `SCompoundWidget`
- desc: Widget allowing user to edit the condition tags in a given condition set.
- L28 _public function_ `SLATE_BEGIN_ARGS(SDaySequenceConditionSetPicker) : _StructPropertyHandle(nullptr)`
- L32 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, StructPropertyHandle) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Used for writing changes to the condition set being edited.
- L39 _private prototype_ `TSharedRef<SWidget> GetChildWidget();`
- L40 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(UClass* InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _private prototype_ `void OnSearchStringChanged(const FText& NewString);` — Members for tracking and using search text.
- L44 _private member_ `TSharedPtr<SSearchBox> ConditionSearchBox;`
- L45 _private member_ `FString SearchString;`
- L48 _private prototype_ `void RefreshListView();` — Populate VisibleConditionTags with the correct subset of AllConditionTags given our current search text.
- L51 _private member_ `TArray<UClass*> VisibleConditionTags;` — The set of condition tags to display, based on our current search text.
- L52 _private member_ `TSharedPtr<SListView<UClass*>> VisibleConditionTagsListView;`
- L55 _private prototype_ `void PopulateVisibleClasses();` — Queries the asset registry to get all known condition tags.
- L58 _private member_ `TArray<UClass*> AllConditionTags;` — The set of condition tags which can be displayed.
- L61 _private prototype_ `ECheckBoxState IsTagChecked(UClass* InTag);` — Functions for querying the condition set for information about a particular tag.
- L62 _private prototype_ `void PopulateCheckedTags();`
- L63 _private member_ `TMap<UClass*, bool> CheckedTags;`
- L66 _private prototype_ `void OnTagChecked(UClass* NodeChecked);` — Functions for adding/removing tags to/from the condition set.
- L67 _private prototype_ `void OnTagUnchecked(UClass* NodeUnchecked);`
- L68 _private prototype_ `void OnUncheckAllTags();`
- L71 _private prototype_ `void FlushHelperConditionSet() const;` — Brings the source condition set to parity with HelperConditionSet. Generally called immediately after modifying HelperConditionSet.
- L74 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Property handle to an FDaySequenceConditionSet, used for accessing the source condition set.
- L77 _private member_ `TStrongObjectPtr<UEditableDaySequenceConditionSet> HelperConditionSet;` — A helper class which is used for propagating changes to the source condition set.

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/SDaySequenceConditionTagChip.h` (Private)


#### class `SDaySequenceConditionTagChip`  
`class SDaySequenceConditionTagChip : public SCompoundWidget`  
_L13-60_
- inherits: `SCompoundWidget`
- desc: Widget for displaying a single condition tag.
- L19 _public prototype_ `DECLARE_DELEGATE_RetVal(FReply, FOnClearPressed);`
- L20 _public function_ `DECLARE_DELEGATE_TwoParams(FOnExpectedValueChanged, UClass*, bool) SLATE_BEGIN_ARGS(SDaySequenceConditionTagChip)`
- L25 _public prototype_ `SLATE_ARGUMENT(UClass*, TagClass)` — The condition subclass associated with this chip.
- L43 _public prototype_ `SDaySequenceConditionTagChip();`
- L44 _public prototype_ `void Construct(const FArguments& InArgs);`
- L47 _public member_ `inline static constexpr float ChipHeight = 25.f;` — This is public because it is used in SDaySequenceConditionSetCombo and SDaySequenceConditionSetPicker.
- L50 _private member_ `TSlateAttribute<FText> ToolTipTextAttribute;`
- L51 _private member_ `TSlateAttribute<FText> TextAttribute;`
- L52 _private member_ `TSlateAttribute<bool> ExpectedValueAttribute;`
- L54 _private member_ `FOnClearPressed OnClearPressed;`
- L55 _private member_ `FOnExpectedValueChanged OnExpectedValueChanged;`
- L57 _private member_ `TSharedPtr<SButton> ClearButton;`
- L59 _private member_ `UClass* TagClass;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_RetVal(FReply, FOnClearPressed);`
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnExpectedValueChanged, UClass*, bool) SLATE_BEGIN_ARGS(SDaySequenceConditionTagChip) {}`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/SDaySequencePreviewTimeSlider.h` (Private)


#### class `SDaySequencePreviewTimeSlider`  
`class SDaySequencePreviewTimeSlider : public SCompoundWidget`  
_L10-21_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SDaySequencePreviewTimeSlider)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _private member_ `FDaySequenceActorPreview* DaySequenceActorPreview = nullptr;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/SDaySequenceSettings.h` (Private)


#### class `SDaySequenceSettings`  
`class SDaySequenceSettings : public SCompoundWidget`  
_L15-39_
- inherits: `SCompoundWidget`
- L17 _private function_ `SLATE_BEGIN_ARGS(SDaySequenceSettings)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);`
- L25 _private prototype_ `void OnSettingsSectionChanged(ESettingsSection NewSection);`
- L26 _private prototype_ `void OnMapChanged(uint32 Flags);`
- L27 _private prototype_ `UObject* GetObjectContext() const;`
- L28 _private prototype_ `void UpdateDaySequenceActor();`
- L29 _private prototype_ `FReply OnEditDaySequenceClicked();`
- L30 _private prototype_ `void OnSubobjectEditorTreeViewSelectionChanged(const TArray<TSharedPtr<FSubobjectEditorTreeNode> >& SelectedNodes);`
- L32 _private prototype_ `TSharedRef<SWidget> MakeEnvironmentPanel();`
- L33 _private prototype_ `TSharedRef<SWidget> MakeEditDaySequencePanel();`
- L35 _private member_ `TSharedPtr<SWidgetSwitcher> SettingsSwitcher;`
- L36 _private member_ `TSharedPtr<SSubobjectInstanceEditor> SubobjectEditor;`
- L37 _private member_ `TWeakObjectPtr<ADaySequenceActor> EditorDaySequenceActor;`
- L38 _private member_ `TSharedPtr<IDetailsView> ComponentDetailsView;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Public/DaySequenceConditionSetCustomization.h` (Public)


#### class `FDaySequenceConditionSetCustomization`  
`class FDaySequenceConditionSetCustomization : public IPropertyTypeCustomization`  
_L10-18_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Public/DaySequenceEditorSpawnRegister.h` (Public)


#### class `FDaySequenceEditorSpawnRegister`  
`class FDaySequenceEditorSpawnRegister : public FDaySequenceSpawnRegister`  
_L24-108_
- inherits: `FDaySequenceSpawnRegister`
- desc: Spawn register used in the editor to add some usability features like maintaining selection states, and projecting spawned state onto spawnable defaults
- L30 _public prototype_ `FDaySequenceEditorSpawnRegister();` — Constructor
- L36 _public prototype_ `void SetSequencer(const TSharedPtr<ISequencer>& Sequencer);`
- L40 _public prototype_ `virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) override;` — FDaySequenceSpawnRegister interface
- L41 _public prototype_ `virtual void PreDestroyObject(UObject& Object, const FGuid& BindingId, int32 BindingIndex, FMovieSceneSequenceIDRef TemplateID) override;`
- L43 _public prototype_ `virtual TValueOrError<FNewSpawnable, FText> CreateNewSpawnableType(UObject& SourceObject, UMovieScene& OwnerMovieScene, UActorFactory* ActorFactory = nullptr) override;`
- L44 _public prototype_ `virtual void SaveDefaultSpawnableState(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) override;`
- L45 _public prototype_ `virtual void SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings) override;`
- L46 _public prototype_ `virtual void HandleConvertPossessableToSpawnable(UObject* OldObject, TSharedRef<const FSharedPlaybackState> SharedPlaybackState, TOptional<FTransformData>& OutTransformData) override;`
- L47 _public prototype_ `virtual bool CanConvertSpawnableToPossessable(FMovieSceneSpawnable& Spawnable) const override;`
- L52 _private prototype_ `void HandleActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Called when the editor selection has changed.
- L56 _private prototype_ `void SaveDefaultSpawnableState(const FGuid& Guid, int32 BindingIndex, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) override;` — Saves the default state for the specified spawnable, if an instance for it currently exists
- L57 _private prototype_ `void SaveDefaultSpawnableStateImpl(FMovieSceneSpawnable& Spawnable, UMovieSceneSequence* Sequence, UObject* SpawnedObject, TSharedRef<const FSharedPlaybackState> SharedPlaybackState);`
- L61 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);` — Called from the editor when a blueprint object replacement has occurred
- L64 _private prototype_ `void OnObjectModified(UObject* ModifiedObject);` — Called whenever an object is modified in the editor
- L67 _private prototype_ `void OnPreObjectSaved(UObject* Object, FObjectPreSaveContext SaveContext);` — Called before an object is saved in the editor
- L86 _private member_ `FDelegateHandle OnActorSelectionChangedHandle;` — Handles for delegates that we've bound to.
- L89 _private member_ `TSet<FMovieSceneSpawnRegisterKey> SelectedSpawnedObjects;` — Set of spawn register keys for objects that should be selected if they are spawned.
- L92 _private member_ `TMap<FObjectKey, FTrackedObjectState> TrackedObjects;` — Map from a sequenceID to an array of objects that have been tracked
- L95 _private member_ `TSet<FObjectKey> SequencesWithModifiedObjects;` — Set of UMovieSceneSequences that this register has spawned objects for that are modified
- L98 _private member_ `bool bShouldClearSelectionCache;` — True if we should clear the above selection cache when the editor selection has been changed.
- L101 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Weak pointer to the active sequencer.
- L104 _private member_ `FDelegateHandle OnObjectModifiedHandle;` — Handle to a delegate that is bound to FCoreUObjectDelegates::OnObjectModified to harvest changes to spawned objects.
- L107 _private member_ `FDelegateHandle OnObjectSavedHandle;` — Handle to a delegate that is bound to FCoreUObjectDelegates::OnObjectPreSave to harvest changes to spawned objects.

#### struct `FDaySequenceEditorSpawnRegister::FTrackedObjectState`  
`struct FTrackedObjectState`  
_L70-82_
- L72 _public function_ `FTrackedObjectState(FMovieSceneSequenceIDRef InTemplateID, const FGuid& InObjectBindingID) : TemplateID(InTemplateID), ObjectBindingID(InObjectBindingID), bHasBeenModified(false)`
- L75 _public member_ `FMovieSceneSequenceID TemplateID;` — The sequence ID that spawned this object
- L78 _public member_ `FGuid ObjectBindingID;` — The object binding ID of the object in the template
- L81 _public member_ `bool bHasBeenModified;` — true if this object has been modified since it was spawned and is different from the current object template

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DAYSEQUENCEEDITOR_API`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Public/DaySequenceTimeDetailsCustomization.h` (Public)


#### class `FDaySequenceTimeDetailsCustomization`  
`class FDaySequenceTimeDetailsCustomization : public IPropertyTypeCustomization`  
_L17-38_
- inherits: `IPropertyTypeCustomization`
- desc: Customize FDaySequenceTime
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public function_ `FDaySequenceTimeDetailsCustomization()`
- L29 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — IPropertyTypeCustomization interface
- L30 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L33 _private prototype_ `FText OnGetTimeText() const;`
- L34 _private prototype_ `void OnTimeTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L37 _private member_ `TSharedPtr<IPropertyHandle> TimeProperty;` — Store the property handle to the Time field so we can get/set the value on the object via text box callbacks.

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Public/IDaySequenceEditorModule.h` (Public)


#### class `IDaySequenceEditorModule`  
`class IDaySequenceEditorModule : public IModuleInterface`  
_L11-25_
- inherits: `IModuleInterface`
- desc: Interface for the DaySequence Editor module.
- L15 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAllowPlaybackContext, bool&);` — TODO: Should we set this for UMoviePipelineQueueSubsystem like LevelSequence?
- L16 _public prototype_ `virtual FAllowPlaybackContext& OnComputePlaybackContext() = 0;`
- L18 _public prototype_ `virtual FDaySequenceActorPreview& GetDaySequenceActorPreview() = 0;`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FPreSelectDaySequenceActor);`
- L21 _public prototype_ `virtual FPreSelectDaySequenceActor& OnPreSelectDaySequenceActor() = 0;`
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FPostSelectDaySequenceActor);`
- L24 _public prototype_ `virtual FPostSelectDaySequenceActor& OnPostSelectDaySequenceActor() = 0;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAllowPlaybackContext, bool&);` — TODO: Should we set this for UMoviePipelineQueueSubsystem like LevelSequence?
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE(FPreSelectDaySequenceActor);`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE(FPostSelectDaySequenceActor);`

### `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Public/IDaySequenceEditorToolkit.h` (Public)


#### class `IDaySequenceEditorToolkit`  
`class IDaySequenceEditorToolkit : public FAssetEditorToolkit`  
_L12-17_
- inherits: `FAssetEditorToolkit`
- desc: Implements an Editor toolkit for day sequences.
- L16 _public prototype_ `virtual TSharedPtr<ISequencer> GetSequencer() const = 0;` — Access the sequencer that is displayed on this asset editor UI
