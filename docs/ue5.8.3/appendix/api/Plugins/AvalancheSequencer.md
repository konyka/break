# Plugins / AvalancheSequencer

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer`
- headers: 57; symbols: 848
- symbol kinds: class=51, delegate=6, enum=3, enumerator=14, function=92, macro=1, member=211, namespace=11, prototype=444, struct=12, typedef=3
- PrivateDependencyModuleNames: ApplicationCore, Avalanche, AvalancheCore, AvalancheEditorCore, AvalancheOutliner, AvalancheTransition, AvalancheTransitionEditor, BlueprintGraph, ClassViewer, CustomDetailsView, DeveloperSettings, EditorSubsystem, Engine, GeometryCache, GeometryCacheSequencer, GeometryCacheTracks, InputCore, Json, JsonUtilities, KismetCompiler, LevelSequence, MediaCompositing, MediaCompositingEditor, MovieSceneTools, MovieSceneTracks, Projects, SceneOutliner, SequencerCore, Settings, Slate, StateTreeEditorModule, StateTreeModule, TimeManagement, ToolMenus, ToolWidgets, UMG
- PublicDependencyModuleNames: AvalancheSequence, AvalancheTag, Core, CoreUObject, MovieScene, Sequencer, SlateCore, UnrealEd

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/AvaSequenceEditor.h` (Private)


#### struct `FAvaSequenceEditor`  
`struct FAvaSequenceEditor : FMovieSceneSequenceEditor`  
_L7-16_
- inherits: `FMovieSceneSequenceEditor`
- L11 _private prototype_ `virtual bool CanCreateEvents(UMovieSceneSequence* InSequence) const override;`
- L12 _private prototype_ `virtual bool CanCreateDirectorBlueprint(UMovieSceneSequence* InSequence) const override;`
- L13 _private prototype_ `virtual UBlueprint* GetBlueprintForSequence(UMovieSceneSequence* InSequence) const override;`
- L14 _private prototype_ `virtual UBlueprint* CreateBlueprintForSequence(UMovieSceneSequence* InSequence) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/AvaSequenceItemShared.h` (Private)


#### class `TAvaSequenceItemDelegate`  
`template<typename InMulticastDelegateType> class TAvaSequenceItemDelegate`  
_L17-44_
- desc: Delegate Wrapper so that things other than IAvaSequenceItem can only Add or Remove Listeners but not call Broadcast
- L22 _public function_ `FDelegateHandle AddListener(const typename InMulticastDelegateType::FDelegate& InDelegate)`
- L27 _public function_ `bool RemoveListener(const FDelegateHandle& InDelegateHandle)`
- L32 _public function_ `int32 RemoveListener(FDelegateUserObjectConst InUserObject)`
- L38 _private function_ `void Broadcast()`
- L43 _private member_ `InMulticastDelegateType MulticastDelegate;`

#### Free symbols / members of external scopes

- L11 _typedef_ `using FAvaSequenceItemPtr = TSharedPtr<IAvaSequenceItem>;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/AvaSequencer.h` (Private)


#### class `FAvaSequencer`  
`class FAvaSequencer : public IAvaSequencer, public FEditorUndoClient, public TSharedFromThis<FAvaSequencer>`  
_L51-312_
- inherits: `IAvaSequencer,FEditorUndoClient,TSharedFromThis<FAvaSequencer>`
- L54 _public member_ `static const FName SidebarDrawerId;`
- L56 _public prototype_ `explicit FAvaSequencer(IAvaSequencerProvider& InProvider, FAvaSequencerArgs&& InArgs);`
- L60 _public prototype_ `void BindCommands();`
- L62 _public function_ `TSharedPtr<FUICommandList> GetCommandList() const`
- L64 _public prototype_ `TSharedPtr<IAvaSequenceColumn> FindSequenceColumn(FName InColumnName) const;`
- L67 _public prototype_ `void EnsureSequencer();` — Makes sure the Sequencer is instantiated
- L69 _public prototype_ `TSharedRef<ISequencer> CreateSequencer();`
- L71 _public function_ `IAvaSequencerProvider& GetProvider()`
- L73 _public prototype_ `void GetSelectedObjects(const TArray<FGuid>& InObjectGuids , TArray<UObject*>& OutSelectedActors , TArray<UObject*>& OutSelectedComponents , TArray<UObject*>& OutSelectedObjects) const;`
- L78 _public prototype_ `bool IsBindingSelected(const FMovieSceneBinding& InBinding) const;`
- L81 _public prototype_ `void OnSequencerSelectionChanged(TArray<FGuid> InObjectGuids);` — Syncs from Sequencer Selection to Editor Selection
- L84 _public prototype_ `TSharedRef<FExtender> GetAddTrackSequencerExtender(const TSharedRef<FUICommandList> InCommandList , const TArray<UObject*> InContextSensitiveObjects);` — Gets the extender to use for sequencers context sensitive menus and toolbars
- L88 _public prototype_ `void ExtendSequencerAddTrackMenu(FMenuBuilder& OutAddTrackMenuBuilder , const TArray<UObject*> InContextObjects);` — Extends the sequencer add track menu
- L91 _public prototype_ `void NotifyViewedSequenceChanged(UAvaSequence* InOldSequence);`
- L93 _public prototype_ `UAvaSequence* CreateSequence() const;`
- L95 _public prototype_ `UObject* GetPlaybackContext() const;`
- L97 _public prototype_ `TSharedRef<SWidget> GetSequenceTreeWidget();`
- L99 _public prototype_ `TSharedRef<SWidget> CreatePlayerToolBar(const TSharedRef<FUICommandList>& InCommandList);`
- L101 _public prototype_ `void OnSequenceSearchChanged(const FText& InSearchText, FText& OutErrorMessage);`
- L103 _public prototype_ `void OnActivateSequence(FMovieSceneSequenceIDRef InSequenceID);`
- L106 _public prototype_ `void NotifyOnSequencePlayed();` — Called when an Sequence has Started Playing in either Sequencer or the Sequence Panel
- L109 _public prototype_ `void NotifyOnSequenceStopped();` — Called when an Sequence has Stopped Playing in either Sequencer or the Sequence Panel
- L112 _public prototype_ `void OnActorLabelChanged(AActor* InActor);` — Called when an actor's label has changed
- L114 _public prototype_ `void OnMovieSceneBindingsPasted(const TArray<FMovieSceneBinding>& InBindings);`
- L116 _public function_ `const TArray<FAvaSequenceItemPtr>& GetRootSequenceItems() const`
- L118 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnViewedSequenceChanged, UAvaSequence*);`
- L119 _public function_ `FOnViewedSequenceChanged& GetOnViewedSequenceChanged()`
- L121 _public function_ `FOnSequenceAdded& OnSequenceAdded() override`
- L122 _public function_ `FOnSequenceRemoved& OnSequenceRemoved() override`
- L124 _public prototype_ `void AddTransformKey(EMovieSceneTransformChannel InTransformChannel);`
- L126 _public prototype_ `void ApplyDefaultPresetToSelection(FName InPresetName);`
- L127 _public prototype_ `void ApplyCustomPresetToSelection(FName InPresetName);`
- L128 _public prototype_ `void ApplyPresetToSelection(const FAvaSequencePreset& InPreset);`
- L137 _public prototype_ `static UObject* FindObjectToPossess(UObject* InParentObject, const FMovieScenePossessable& InPossessable);` — Attempts to find the best matching subobject of the given Parent Object based on the information provided by the given possessable @param InParentObject the outer from which to find the object @param InPossessable the possessable to retrieve things like name (label) and object class @return the matching subobject if found, or nullptr if not found
- L140 _public prototype_ `void ApplyCurrentState();` — Resets the pre-animated state of the sequencer, keeping the current state of the world even when sequencer is saved/closed
- L142 _public prototype_ `void FixBindingPaths();`
- L144 _public prototype_ `void FixInvalidBindings();`
- L147 _public prototype_ `static FString GetObjectName(UObject* InObject);` — Gets the Object Name to use for a Possessable Name
- L153 _public prototype_ `static UObject* FindResolutionContext(UAvaSequence& InSequence , UMovieScene& InMovieScene , const FGuid& InParentPossessableGuid , UObject* InPlaybackContext , TFunctionRef<TArray<UObject*, TInlineAllocator<1>>(const FGuid& InGuid, UObject* InContextChecked)> InFindObjectsFunc);` — Recursively finds the most appropriate Resolution Context for a given Parent Guid of a Possessable Uses InFindObjectsFunc to resolve the object.
- L159 _public prototype_ `static UObject* FindResolutionContext(UAvaSequence& InSequence , UMovieScene& InMovieScene , const FGuid& InParentGuid , UObject* InPlaybackContext);`
- L164 _public prototype_ `bool FixPossessable(UAvaSequence& InSequence , const FMovieScenePossessable& InPossessable , UObject* InPlaybackContext , TSet<const FMovieScenePossessable*>& InOutProcessedPossessables);`
- L169 _public prototype_ `void FixBindingHierarchy();`
- L171 _public prototype_ `TArrayView<TWeakObjectPtr<>> ResolveBoundObjects(const FGuid& InBindingId, UMovieSceneSequence* Sequence) const;`
- L173 _public prototype_ `TSharedRef<ISequencer> GetOrCreateSequencer() const;`
- L176 _public function_ `virtual const IAvaSequencerProvider& GetProvider() const override`
- L177 _public prototype_ `virtual TSharedPtr<ISequencer> GetSequencerPtr() const override;`
- L178 _public prototype_ `virtual USequencerSettings* GetSequencerSettings() const override;`
- L179 _public prototype_ `virtual void SetBaseCommandList(const TSharedPtr<FUICommandList>& InBaseCommandList) override;`
- L180 _public prototype_ `virtual UAvaSequence* GetViewedSequence() const override;`
- L181 _public prototype_ `virtual UAvaSequence* GetDefaultSequence() const override;`
- L182 _public prototype_ `virtual void SetViewedSequence(UAvaSequence* InSequenceToView) override;`
- L183 _public prototype_ `virtual TArray<UAvaSequence*> GetSequencesForObject(UObject* InObject) const override;`
- L184 _public prototype_ `virtual TSharedRef<SWidget> CreateSequenceWidget() override;`
- L185 _public prototype_ `virtual void OnActorsCopied(FString& InOutCopiedData, TConstArrayView<AActor*> InCopiedActors) override;`
- L186 _public prototype_ `virtual void OnActorsPasted(FStringView InPastedData, const TMap<FName, AActor*>& InPastedActors) override;`
- L187 _public prototype_ `virtual void OnEditorSelectionChanged(const FAvaEditorSelection& InEditorSelection) override;`
- L188 _public prototype_ `virtual void NotifyOnSequenceTreeChanged() override;`
- L189 _public prototype_ `virtual const TArray<TWeakObjectPtr<UAvaSequence>>& GetRootSequences() const override;`
- L190 _public prototype_ `virtual bool CanAddSequence() const override;`
- L191 _public prototype_ `virtual UAvaSequence* AddSequence(UAvaSequence* const InParentSequence = nullptr) override;`
- L192 _public prototype_ `virtual void DeleteSequences(const TSet<UAvaSequence*>& InSequences) override;`
- L193 _public prototype_ `virtual uint32 AddSequenceFromPresets(TConstArrayView<const FAvaSequencePreset*> InPresets) override;`
- L197 _public prototype_ `void AddSequencesFromPresetGroup(FName InPresetGroup);` — Creates new sequences based on a given preset group
- L199 _public prototype_ `bool AddSequence_CanExecute() const;`
- L200 _public prototype_ `void AddSequence_Execute();`
- L202 _public prototype_ `bool DuplicateSequences_CanExecute() const;`
- L203 _public prototype_ `void DuplicateSequences_Execute();`
- L205 _public prototype_ `bool ExportSequences_CanExecute() const;`
- L206 _public prototype_ `void ExportSequences_Execute();`
- L208 _public prototype_ `bool SpawnPlayers_CanExecute() const;`
- L209 _public prototype_ `void SpawnPlayers_Execute();`
- L211 _public prototype_ `bool DeleteSequences_CanExecute() const;`
- L212 _public prototype_ `void DeleteSequences_Execute();`
- L214 _public prototype_ `bool RelabelSequence_CanExecute() const;`
- L215 _public prototype_ `void RelabelSequence_Execute();`
- L217 _public prototype_ `bool PlaySequences_CanExecute() const;`
- L218 _public prototype_ `void PlaySequences_Execute();`
- L220 _public prototype_ `bool ContinueSequences_CanExecute() const;`
- L221 _public prototype_ `void ContinueSequences_Execute();`
- L223 _public prototype_ `bool StopSequences_CanExecute() const;`
- L224 _public prototype_ `void StopSequences_Execute();`
- L227 _public prototype_ `void OnSequenceEditUndo(UAvaSequence* InSequence);` — Called when PostUndo has been called for the given sequence
- L230 _public prototype_ `virtual void PostUndo(bool bInSuccess) override;`
- L231 _public prototype_ `virtual void PostRedo(bool bInSuccess) override;`
- L235 _private prototype_ `TArray<UAvaSequence*> GetSelectedSequences() const;`
- L237 _private prototype_ `TSharedPtr<UE::Sequencer::SOutlinerView> GetOutlinerView() const;`
- L239 _private prototype_ `void InitSequencerCommandList();`
- L241 _private prototype_ `void ExecuteSequencerDuplication(FExecuteAction InExecuteAction);`
- L243 _private prototype_ `void OnUpdateCameraCut(UObject* InCameraObject, bool bInJumpCut);`
- L245 _private prototype_ `void ExtendSidebarMarkedFramesMenu(FMenuBuilder& OutMenuBuilder);`
- L247 _private prototype_ `void OnSequencerClosed(const TSharedRef<ISequencer> InSequencer);`
- L249 _private member_ `FOnViewedSequenceChanged OnViewedSequenceChanged;`
- L251 _private member_ `FOnSequenceAdded OnSequenceAddedDelegate;`
- L252 _private member_ `FOnSequenceRemoved OnSequenceRemovedDelegate;`
- L254 _private member_ `IAvaSequencerProvider& Provider;`
- L257 _private member_ `TWeakPtr<ISequencer> SequencerWeak;` — The active sequencer to use. This is set to Weak as FSequencer::Tick does not allow to have more than 1 ref (outside of menus)
- L260 _private member_ `TSharedPtr<ISequencer> InstancedSequencer;` — the instanced sequencer if no external sequencer specified. Will be null if using an External Sequencer
- L262 _private member_ `TWeakPtr<UE::Sequencer::SOutlinerView> OutlinerViewWeak;`
- L264 _private member_ `TSharedPtr<IAvaSequencerController> SequencerController;`
- L266 _private member_ `TSharedRef<FUICommandList> CommandList;`
- L268 _private member_ `TWeakObjectPtr<UAvaSequence> ViewedSequenceWeak;`
- L270 _private member_ `FDelegateHandle SequencerAddTrackExtenderHandle;`
- L273 _private member_ `TMap<FName, TSharedPtr<IAvaSequenceColumn>> SequenceColumns;` — BEGIN REMOVE AFTER NAVIGATION TOOL INTEGRATION
- L275 _private member_ `TArray<FAvaSequenceItemPtr> RootSequenceItems;`
- L277 _private member_ `TSharedPtr<SHeaderRow> SequenceTreeHeaderRow;`
- L279 _private member_ `TSharedPtr<SAvaSequenceTree> SequenceTree;`
- L281 _private member_ `TSharedPtr<STreeView<FAvaSequenceItemPtr>> SequenceTreeView;`
- L284 _private member_ `TSharedRef<FAvaSequencerCleanView> CleanView;`
- L287 _private member_ `FDelegateHandle OnSequenceEditUndoHandle;` — Handle to the Sequence Edit Undo delegate
- L289 _private member_ `FDelegateHandle OnSequenceStartedHandle;`
- L291 _private member_ `FDelegateHandle OnSequenceFinishedHandle;`
- L294 _private member_ `FDelegateHandle OnActorLabelChangedHandle;` — Handle to when the actor label has changed
- L296 _private member_ `TArray<TSharedRef<FAvaSequencerAction>> SequencerActions;`
- L299 _private member_ `bool bUpdatingSelection = false;` — prevents reentry when synchronizing Sequencer <-> Provider Selection
- L301 _private member_ `bool bSelectedFromSequencer = false;`
- L304 _private member_ `const bool bUseCustomCleanPlaybackMode;` — Whether custom clean playback mode will ever be used (set via FAvaSequencerArgs::bUseCustomCleanPlaybackMode)
- L307 _private member_ `const bool bCanProcessSequencerSelections;` — Whether FAvaSequencer is allowed to select to/from the ISequencer instance
- L309 _private member_ `TSharedPtr<FExtender> SidebarExtender;`
- L311 _private member_ `FDelegateHandle SidebarSelectionExtenderHandle;`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace UE`
- L40 _namespace_ `namespace Sequencer` (scope `UE`)
- L45 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnViewedSequenceChanged, UAvaSequence*);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/AvaSequencerMenuContext.h` (Private)


#### class `UAvaSequencerMenuContext`  
`class UAvaSequencerMenuContext : public UObject`  
_L12-29_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public function_ `TSharedPtr<FAvaSequencer> GetAvaSequencer() const`
- L22 _public function_ `void SetAvaSequencer(const TWeakPtr<FAvaSequencer>& InAvaSequencerWeak)`
- L28 _private member_ `TWeakPtr<FAvaSequencer> AvaSequencerWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/AvaSequencerModule.h` (Private)


#### class `FAvaSequencerModule`  
`class FAvaSequencerModule : public IModuleInterface`  
_L17-134_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public function_ `static FAvaSequencerModule& Get()`
- L31 _private prototype_ `void RegisterSequenceEditor(ISequencerModule& InSequencerModule);`
- L32 _private prototype_ `void UnregisterSequenceEditor(ISequencerModule& InSequencerModule);`
- L35 _private function_ `template<typename InTrackEditorType> void RegisterTrackEditor(ISequencerModule& InSequencerModule)`
- L46 _private function_ `template<typename InTrackEditorType> void RegisterPropertyTrackEditor(ISequencerModule& InSequencerModule)`
- L51 _private prototype_ `void RegisterTrackEditors(ISequencerModule& InSequencerModule);`
- L52 _private prototype_ `void UnregisterTrackEditors(ISequencerModule& InSequencerModule);`
- L55 _private function_ `template<typename InObjectBindingType> void RegisterObjectBinding(ISequencerModule& InSequencerModule)`
- L65 _private prototype_ `void RegisterObjectBindings(ISequencerModule& InSequencerModule);`
- L66 _private prototype_ `void UnregisterObjectBindings(ISequencerModule& InSequencerModule);`
- L69 _private function_ `template<typename InClassType, typename InCustomizationType> void RegisterCustomization(ISequencerModule& InSequencerModule)`
- L80 _private prototype_ `void RegisterCustomizations(ISequencerModule& InSequencerModule);`
- L81 _private prototype_ `void UnregisterCustomizations(ISequencerModule& InSequencerModule);`
- L83 _private prototype_ `void RegisterOutlinerItems();`
- L84 _private prototype_ `void UnregisterOutlinerItems();`
- L87 _private function_ `template<typename InType> FName GetTypeName() const`
- L104 _private function_ `template<typename InPropertyType, typename InPropertyTypeCustomizationType> void RegisterCustomPropertyTypeLayout(FPropertyEditorModule& InPropertyModule)`
- L116 _private prototype_ `void RegisterCustomLayouts();`
- L117 _private prototype_ `void UnregisterCustomLayouts();`
- L119 _private prototype_ `void RegisterDirectorCompiler();`
- L121 _private member_ `TSharedPtr<FAvaActorSubobjectSchema> ActorSubobjectSchema;`
- L123 _private member_ `FDelegateHandle SequenceEditorHandle;`
- L125 _private member_ `TArray<FName> PropertyTypeLayouts;`
- L127 _private member_ `TArray<FDelegateHandle> TrackEditorHandles;`
- L129 _private member_ `TArray<FDelegateHandle> ObjectBindingHandles;`
- L131 _private member_ `FDelegateHandle OutlinerProxiesExtensionDelegateHandle;`
- L133 _private member_ `TArray<const UClass*> CustomizedClasses;`

#### Free symbols / members of external scopes

- L39 _function_ `` (scope `FAvaSequencerModule::RegisterTrackEditor`)
- L59 _function_ `` (scope `FAvaSequencerModule::RegisterObjectBinding`)
- L75 _function_ `` (scope `FAvaSequencerModule::RegisterCustomization`)
- L111 _function_ `` (scope `FAvaSequencerModule::RegisterCustomPropertyTypeLayout`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Clipboard/AvaSequenceExporter.h` (Private)


#### class `FAvaSequenceExporter`  
`class FAvaSequenceExporter`  
_L15-24_
- desc: Handles exporting the given Copied Actors' Sequence Data to String Text
- L18 _public prototype_ `explicit FAvaSequenceExporter(const TSharedRef<FAvaSequencer>& InAvaSequencer);`
- L20 _public prototype_ `void ExportText(FString& InOutCopiedData, TConstArrayView<AActor*> InCopiedActors);`
- L23 _private member_ `TWeakPtr<FAvaSequencer> AvaSequencerWeak;`

#### class `UAvaSequenceExporter`  
`class UAvaSequenceExporter : public UExporter`  
_L27-38_
- reflection: `UCLASS()`
- inherits: `UExporter`
- L32 _public prototype_ `UAvaSequenceExporter();`
- L35 _public prototype_ `virtual bool ExportText(const FExportObjectInnerContext* InContext, UObject* InObject, const TCHAR* InType , FOutputDevice& Ar, FFeedbackContext* InWarn, uint32 InPortFlags) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Clipboard/AvaSequenceImporter.h` (Private)


#### class `FAvaSequenceImporter`  
`class FAvaSequenceImporter`  
_L22-64_
- desc: Handles parsing String Data to import Bindings into an existing or new UAvaSequence instance
- L25 _public prototype_ `explicit FAvaSequenceImporter(const TSharedRef<FAvaSequencer>& InAvaSequencer);`
- L27 _public prototype_ `void ImportText(FStringView InPastedData, const TMap<FName, AActor*>& InPastedActors);`
- L41 _private prototype_ `bool ParseCommand(const TCHAR** InStream, const TCHAR* InToken);`
- L43 _private prototype_ `void ResetCopiedTracksFlags(UMovieSceneTrack* InTrack);`
- L45 _private prototype_ `UAvaSequence* GetOrCreateSequence(FAvaSequencer& InAvaSequencer, FName InSequenceLabel);`
- L47 _private prototype_ `TArray<UAvaSequenceCopyableBinding*> ImportBindings(ISequencer& InSequencerRef, const FString& InBindingsString);`
- L49 _private prototype_ `void ProcessImportedBindings(const TArray<UAvaSequenceCopyableBinding*>& InImportedBindings , const TMap<FName, AActor*>& InPastedActors);`
- L52 _private prototype_ `FMovieSceneBinding BindPossessable(const FImportContext& InContext);`
- L54 _private prototype_ `FMovieSceneBinding BindSpawnable(const FImportContext& InContext);`
- L56 _private prototype_ `void AddObjectsToBinding(const TSharedRef<ISequencer>& InSequencer , const TArray<UObject*>& InObjectsToAdd , const FMovieSceneBindingProxy& InObjectBinding , UObject* InResolutionContext);`
- L61 _private member_ `TWeakPtr<FAvaSequencer> AvaSequencerWeak;`
- L63 _private member_ `TSet<FObjectKey> UsedSequences;`

#### struct `FAvaSequenceImporter::FImportContext`  
`struct FImportContext`  
_L30-39_
- L32 _public member_ `TSharedRef<ISequencer> Sequencer;`
- L33 _public member_ `UAvaSequence& Sequence;`
- L34 _public member_ `UMovieScene& MovieScene;`
- L35 _public member_ `FMovieSceneSequenceIDRef SequenceIDRef;`
- L36 _public member_ `const TMap<FName, AActor*>& PastedActors;`
- L38 _public member_ `UAvaSequenceCopyableBinding* CopyableBinding;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Commands/AvaSequencerAction.h` (Private)


#### class `FAvaSequencerAction`  
`class FAvaSequencerAction : public TSharedFromThis<FAvaSequencerAction>`  
_L15-36_
- inherits: `TSharedFromThis<FAvaSequencerAction>`
- L18 _public function_ `explicit FAvaSequencerAction(FAvaSequencer& InOwner) : Owner(InOwner)`
- L23 _public prototype_ `virtual ~FAvaSequencerAction() = default;`
- L25 _public prototype_ `virtual void MapAction(const TSharedRef<FUICommandList>& InCommandList) = 0;`
- L27 _public function_ `virtual void OnSequencerCreated()`
- L29 _public function_ `virtual void OnSequencerClosed()`
- L33 _protected prototype_ `TSharedPtr<UE::Sequencer::FSequencerSelection> GetSequencerSelection() const;` — Utility function to directly retrieve the Sequencer Selection from the Owner Ava Sequencer
- L35 _protected member_ `FAvaSequencer& Owner;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Commands/AvaSequencerCommands.h` (Private)


#### class `FAvaSequencerCommands`  
`class FAvaSequencerCommands : public TCommands<FAvaSequencerCommands>`  
_L8-43_
- inherits: `TCommands<FAvaSequencerCommands>`
- L11 _public function_ `FAvaSequencerCommands() : TCommands<FAvaSequencerCommands>(TEXT("AvaSequencerCommands") , NSLOCTEXT("MotionDesignSequencerCommands", "MotionDesignSequencerCommands", "Motion Design Sequencer Commands") , NAME_None , FAppStyle::GetAppStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> AddNew;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> PlaySelected;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ContinueSelected;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> StopSelected;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ApplyCurrentState;` — Applies the current state of the sequence to the world by resetting the pre-animated state of the sequence
- L32 _public member_ `TSharedPtr<FUICommandInfo> FixBindingPaths;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> FixInvalidBindings;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> FixBindingHierarchy;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ExportSequence;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> SpawnSequencePlayer;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> OpenStaggerTool;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Customization/AvaDisplayRateCustomization.h` (Private)


#### class `FAvaDisplayRateCustomization`  
`class FAvaDisplayRateCustomization : public IPropertyTypeCustomization`  
_L7-13_
- inherits: `IPropertyTypeCustomization`
- L10 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L11 _private function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Customization/AvaMarkSettingCustomization.h` (Private)


#### class `FAvaMarkSettingCustomization`  
`class FAvaMarkSettingCustomization : public IPropertyTypeCustomization`  
_L7-15_
- inherits: `IPropertyTypeCustomization`
- L10 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L11 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L14 _private prototype_ `void CustomizeMark(const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& InChildBuilder);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Customization/AvaSequenceCustomization.h` (Private)


#### class `FAvaSequenceCustomization`  
`class FAvaSequenceCustomization : public ISequencerCustomization`  
_L20-48_
- inherits: `ISequencerCustomization`
- L23 _public prototype_ `FAvaSequenceCustomization();`
- L27 _protected prototype_ `virtual void RegisterSequencerCustomization(FSequencerCustomizationBuilder& InBuilder) override;`
- L28 _protected prototype_ `virtual void UnregisterSequencerCustomization() override;`
- L32 _private prototype_ `void CreateChildrenCustomizations();`
- L34 _private prototype_ `void ExtendSequencerToolbar(FToolBarBuilder& InToolbarBuilder);`
- L36 _private prototype_ `TSharedRef<SWidget> MakePlaybackMenu() const;`
- L38 _private prototype_ `bool OnSequencerReceiveDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, FReply& OutReply) const;`
- L40 _private prototype_ `bool OnSequencerReceiveDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, FReply& OutReply) const;`
- L43 _private member_ `TArray<TUniquePtr<ISequencerCustomization>> ChildrenCustomizations;` — Additional Sequencer Customizations that this class applies
- L45 _private member_ `TWeakPtr<ISequencer> SequencerWeak;`
- L47 _private member_ `TWeakObjectPtr<UAvaSequence> SequenceWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Customization/AvaSequenceNameCustomization.h` (Private)


#### class `FAvaSequenceNameCustomization`  
`class FAvaSequenceNameCustomization : public IPropertyTypeCustomization`  
_L7-14_
- inherits: `IPropertyTypeCustomization`
- L11 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L12 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Customization/AvaSequenceTimeCustomization.h` (Private)


#### class `FAvaSequenceTimeCustomization`  
`class FAvaSequenceTimeCustomization : public IPropertyTypeCustomization`  
_L7-13_
- inherits: `IPropertyTypeCustomization`
- L10 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L11 _private function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Customization/Widgets/SAvaDisplayRate.h` (Private)


#### class `SAvaDisplayRate`  
`class SAvaDisplayRate : public SCompoundWidget`  
_L14-38_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvaDisplayRate)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L22 _public prototype_ `TSharedRef<SWidget> CreateDisplayRateOptions();`
- L24 _public prototype_ `FText GetDisplayRateText() const;`
- L26 _public prototype_ `void SetDisplayRate(FFrameRate InFrameRate);`
- L28 _public prototype_ `bool IsSameDisplayRate(FFrameRate InFrameRate) const;`
- L31 _private prototype_ `FAvaSequencerDisplayRate* GetDisplayRate(const TSharedPtr<IPropertyHandle>& PropertyHandle) const;`
- L33 _private prototype_ `void AddMenuEntry(FMenuBuilder& MenuBuilder, const FCommonFrameRateInfo& Info);`
- L35 _private member_ `TWeakPtr<IPropertyHandle> PropertyHandleWeak;`
- L37 _private member_ `FText DisplayRateText;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Customization/Widgets/SAvaSequencePicker.h` (Private)


#### struct `FAvaSequencePickerOption`  
`struct FAvaSequencePickerOption`  
_L13-17_
- L16 _public member_ `FName SequenceName;` — Sequence name converted to Text

#### class `SAvaSequencePicker`  
`class SAvaSequencePicker : public SCompoundWidget`  
_L19-49_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAvaSequencePicker)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InSequenceNameHandle);`
- L28 _private prototype_ `FText GetSequenceName() const;`
- L30 _private prototype_ `void SetSequenceName(FName InSequenceName);`
- L32 _private prototype_ `void OnSequenceNameCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L34 _private prototype_ `void RefreshOptions();`
- L36 _private prototype_ `void OnOptionSelectionChanged(TSharedPtr<FAvaSequencePickerOption> InSelectedOption, ESelectInfo::Type InSelectInfo);`
- L38 _private prototype_ `TSharedRef<SWidget> GenerateOptionWidget(TSharedPtr<FAvaSequencePickerOption> InOption);`
- L40 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FAvaSequencePickerOption>>> ComboBox;`
- L42 _private member_ `TWeakObjectPtr<ULevel> LevelWeak;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> NameHandle;`
- L46 _private member_ `TArray<TSharedPtr<FAvaSequencePickerOption>> Options;`
- L48 _private member_ `TSharedPtr<FAvaSequencePickerOption> SelectedOption;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/DetailsView/SAvaKeyFrameEdit.h` (Private)


#### class `SAvaKeyFrameEdit`  
`class SAvaKeyFrameEdit : public SCompoundWidget`  
_L16-30_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAvaKeyFrameEdit)`
- L20 _public prototype_ `SLATE_ATTRIBUTE(FKeyEditData, KeyEditData) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAvaSequencer>& InSequencer);`
- L26 _protected member_ `TWeakPtr<FAvaSequencer> AvaSequencerWeak;`
- L27 _protected member_ `TWeakPtr<UE::Sequencer::FSequencerSelection> SequencerSelectionWeak;`
- L29 _protected member_ `TAttribute<FKeyEditData> KeyEditData;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/DetailsView/SAvaMarkDetails.h` (Private)


#### class `SAvaMarkDetails`  
`class SAvaMarkDetails : public SCompoundWidget, public FNotifyHook`  
_L17-33_
- inherits: `SCompoundWidget,FNotifyHook`
- L20 _public function_ `SLATE_BEGIN_ARGS(SAvaMarkDetails)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UAvaSequence* InSequence, const FMovieSceneMarkedFrame& InMarkedFrame);`
- L27 _protected prototype_ `virtual void NotifyPreChange(FProperty* InPropertyAboutToChange) override;`
- L28 _protected prototype_ `virtual void NotifyPreChange(FEditPropertyChain* InPropertyAboutToChange) override;`
- L31 _protected member_ `TObjectPtr<UAvaSequence> SequenceToModify;`
- L32 _protected member_ `TSharedPtr<FStructOnScope> AvaMarkStruct;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/DetailsView/Section/AvaSequencePlaybackDetails.h` (Private)


#### class `FAvaSequencePlaybackDetails`  
`class FAvaSequencePlaybackDetails : public ISidebarDrawerContent`  
_L13-32_
- inherits: `ISidebarDrawerContent`
- L16 _public member_ `static const FName UniqueId;`
- L18 _public prototype_ `FAvaSequencePlaybackDetails(const TSharedRef<FAvaSequencer>& InAvaSequencer);`
- L21 _public prototype_ `virtual FName GetUniqueId() const override;`
- L22 _public prototype_ `virtual FName GetSectionId() const override;`
- L23 _public prototype_ `virtual FText GetSectionDisplayText() const override;`
- L24 _public prototype_ `virtual bool ShouldShowSection() const override;`
- L25 _public function_ `virtual TOptional<float> GetSectionFillHeight() const override`
- L26 _public prototype_ `virtual int32 GetSortOrder() const override;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> CreateContentWidget() override;`
- L31 _protected member_ `TWeakPtr<FAvaSequencer> AvaSequencerWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/DetailsView/Section/AvaSequenceSettingsDetails.h` (Private)


#### class `FAvaSequenceSettingsDetails`  
`class FAvaSequenceSettingsDetails : public ISidebarDrawerContent`  
_L12-35_
- inherits: `ISidebarDrawerContent`
- L15 _public member_ `static const FName UniqueId;`
- L17 _public prototype_ `FAvaSequenceSettingsDetails(const TSharedRef<FAvaSequencer>& InAvaSequencer);`
- L20 _public prototype_ `virtual FName GetUniqueId() const override;`
- L21 _public prototype_ `virtual FName GetSectionId() const override;`
- L22 _public prototype_ `virtual FText GetSectionDisplayText() const override;`
- L23 _public prototype_ `virtual bool ShouldShowSection() const override;`
- L24 _public function_ `virtual TOptional<float> GetSectionFillHeight() const override`
- L25 _public prototype_ `virtual int32 GetSortOrder() const override;`
- L26 _public prototype_ `virtual TSharedRef<SWidget> CreateContentWidget() override;`
- L30 _protected prototype_ `void OnViewedSequenceChanged(UAvaSequence* const InSequence);`
- L32 _protected member_ `TWeakPtr<FAvaSequencer> AvaSequencerWeak;`
- L34 _protected member_ `TSharedPtr<ICustomDetailsView> SettingsDetailsView;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/DetailsView/Section/AvaSequenceTreeDetails.h` (Private)


#### class `FAvaSequenceTreeDetails`  
`class FAvaSequenceTreeDetails : public ISidebarDrawerContent`  
_L13-32_
- inherits: `ISidebarDrawerContent`
- L16 _public member_ `static const FName UniqueId;`
- L18 _public prototype_ `FAvaSequenceTreeDetails(const TSharedRef<FAvaSequencer>& InAvaSequencer);`
- L21 _public prototype_ `virtual FName GetUniqueId() const override;`
- L22 _public prototype_ `virtual FName GetSectionId() const override;`
- L23 _public prototype_ `virtual FText GetSectionDisplayText() const override;`
- L24 _public prototype_ `virtual bool ShouldShowSection() const override;`
- L25 _public function_ `virtual TOptional<float> GetSectionFillHeight() const override`
- L26 _public prototype_ `virtual int32 GetSortOrder() const override;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> CreateContentWidget() override;`
- L31 _protected member_ `TWeakPtr<FAvaSequencer> AvaSequencerWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Director/AvaSequenceDirectorCompiler.h` (Private)


#### class `FAvaSequenceDirectorCompilerContext`  
`class FAvaSequenceDirectorCompilerContext : public FKismetCompilerContext`  
_L14-39_
- inherits: `FKismetCompilerContext`
- L17 _public prototype_ `FAvaSequenceDirectorCompilerContext(UBlueprint* InBlueprint , FCompilerResultsLog& InResultsLog , const FKismetCompilerOptions& InCompilerOptions);`
- L22 _private prototype_ `UAvaSequenceDirectorBlueprint* GetDirectorBlueprint() const;`
- L25 _private prototype_ `virtual void SpawnNewClass(const FString& InNewClassName) override;`
- L26 _private prototype_ `virtual void OnNewClassSet(UBlueprintGeneratedClass* InClassToUse) override;`
- L27 _private prototype_ `virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* InClassToClean, UObject*& InOutOldCDO) override;`
- L28 _private prototype_ `virtual void SaveSubObjectsFromCleanAndSanitizeClass(FSubobjectCollection& OutSubObjectsToSave, UBlueprintGeneratedClass* InClassToClean) override;`
- L29 _private prototype_ `virtual void EnsureProperGeneratedClass(UClass*& InOutTargetClass) override;`
- L30 _private prototype_ `virtual void CreateClassVariablesFromBlueprint() override;`
- L31 _private prototype_ `virtual void FinishCompilingClass(UClass* InClass) override;`
- L32 _private prototype_ `virtual void OnPostCDOCompiled(const UObject::FPostCDOCompiledContext& InContext) override;`
- L33 _private prototype_ `virtual void PostCompile() override;`
- L36 _private member_ `UAvaSequenceDirectorGeneratedClass* NewBlueprintClass = nullptr;`
- L38 _private member_ `TMap<TSoftObjectPtr<UAvaSequence>, FProperty*> SequencePropertyMap;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/ObjectBinding/AvaSequencerObjectBinding.h` (Private)


#### class `FAvaSequencerObjectBinding`  
`class FAvaSequencerObjectBinding : public ISequencerEditorObjectBinding`  
_L12-31_
- inherits: `ISequencerEditorObjectBinding`
- L15 _public prototype_ `FAvaSequencerObjectBinding(TSharedRef<ISequencer> InSequencer);`
- L18 _public prototype_ `virtual FText GetDisplayName() const override;`
- L19 _public prototype_ `virtual void BuildSequencerAddMenu(FMenuBuilder& OutMenuBuilder) override;`
- L20 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L25 _private prototype_ `void AddPossessActorMenuExtensions(FMenuBuilder& OutMenuBuilder);` — Menu extension callback for the add menu
- L28 _private prototype_ `void AddActorsToSequencer(const TArray<AActor*>& InActors);` — Add the specified actors to the sequencer
- L30 _private member_ `TWeakPtr<ISequencer> SequencerWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Outliner/AvaOutlinerSequence.h` (Private)


#### class `FAvaOutlinerSequence`  
`class FAvaOutlinerSequence : public FAvaOutlinerObjectReference`  
_L15-38_
- inherits: `FAvaOutlinerObjectReference`
- desc: Item in Outliner representing an Sequence. Inherits from FAvaOutlinerObjectReference as multiple objects can be in the same sequence
- L18 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerSequence, FAvaOutlinerObjectReference);`
- L20 _public prototype_ `FAvaOutlinerSequence(IAvaOutliner& InOutliner, UAvaSequence* InSequence, const FAvaOutlinerItemPtr& InReferencingItem);`
- L22 _public function_ `UAvaSequence* GetSequence() const`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;`
- L26 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L27 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`
- L32 _protected prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L35 _protected member_ `TWeakObjectPtr<UAvaSequence> Sequence;`
- L37 _protected member_ `FSlateIcon SequenceIcon;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Outliner/AvaOutlinerSequenceProxy.h` (Private)


#### class `FAvaOutlinerSequenceProxy`  
`class FAvaOutlinerSequenceProxy : public FAvaOutlinerItemProxy`  
_L16-56_
- inherits: `FAvaOutlinerItemProxy`
- desc: Gathers the Sequences that contain the given Item (UObject)
- L19 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerSequenceProxy, FAvaOutlinerItemProxy);`
- L21 _public prototype_ `FAvaOutlinerSequenceProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L25 _public prototype_ `void OnActorAddedToSequencer(AActor* InActor, const FGuid InGuid);`
- L27 _public prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType InChangeType);`
- L30 _public prototype_ `virtual void OnItemRegistered() override;`
- L31 _public prototype_ `virtual void OnItemUnregistered() override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`
- L33 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L34 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L38 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) override;`
- L42 _private prototype_ `void BindDelegates();`
- L44 _private prototype_ `void UnbindDelegates();`
- L46 _private member_ `FSlateIcon SequenceIcon;`
- L48 _private member_ `TWeakPtr<IAvaSequencer> AvaSequencerWeak;`
- L51 _private member_ `TWeakPtr<ISequencer> LastBoundSequencerWeak;` — Used to keep track of the latest Sequencer instance that our delegates are bound to
- L53 _private member_ `FDelegateHandle OnMovieSceneDataChangedHandle;`
- L55 _private member_ `FDelegateHandle OnActorAddedToSequencerHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Playback/AvaSequencerCleanView.h` (Private)


#### class `FAvaSequencerCleanView`  
`class FAvaSequencerCleanView`  
_L15-33_
- desc: Class that makes sure all the Entities (e.g. ViewportClient, ModeTools, etc) can be Set to Clean View and Restored Back to their previous state
- L19 _public prototype_ `void Apply(const TArray<TWeakPtr<FEditorViewportClient>>& InViewportClients);` — Adds all the Viewport Clients and their Editor Mode Tools to this Clean View State
- L25 _public prototype_ `void Restore(bool bInDeallocateSpaceUsed = false);` — Restores all the added entities back to their original state @param bInDeallocateSpaceUsed whether to remove the allocations of the maps. Defaults to false since it's expected this to be used repetitively.
- L29 _private member_ `TMap<TWeakPtr<FEditorViewportClient>, bool> ViewportClientStates;` — Map of the Editor VP Client to their Initial Clean View State
- L32 _private member_ `TMap<FEditorModeTools*, bool> ModeToolsStates;` — Map of the Editor Mode Tools to their Initial Clean View State

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Playback/AvaSequencerController.h` (Private)


#### class `FAvaSequencerController`  
`class FAvaSequencerController : public IAvaSequencerController, public FTickableEditorObject`  
_L20-59_
- inherits: `IAvaSequencerController,FTickableEditorObject`
- desc: Track Editor designed to follow the Sequencer under the hood while not exposing its Track. Helps manage things like Stop Points
- L23 _public prototype_ `FAvaSequencerController() = default;`
- L27 _public function_ `TSharedPtr<ISequencer> GetSequencer() const`
- L29 _public prototype_ `UAvaSequence* GetCurrentSequence() const;`
- L31 _public prototype_ `void OnPlay();`
- L32 _public prototype_ `void OnStop();`
- L33 _public prototype_ `void OnScrub();`
- L36 _public prototype_ `virtual void SetSequencer(const TSharedPtr<ISequencer>& InSequencer) override;`
- L40 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L41 _public prototype_ `virtual TStatId GetStatId() const override;`
- L42 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L46 _private prototype_ `float GetEffectiveTimeDilation(UAvaSequence& InSequence) const;`
- L48 _private prototype_ `void UnbindDelegates();`
- L50 _private prototype_ `void UpdatePlaybackObject(UAvaSequence& InSequence);`
- L52 _private member_ `TWeakPtr<ISequencer> SequencerWeak;`
- L54 _private member_ `TSharedPtr<IAvaSequenceController> SequenceController;`
- L56 _private member_ `TWeakInterfacePtr<IAvaSequencePlaybackObject> PlaybackObjectWeak;`
- L58 _private member_ `bool bSequencerStopped = true;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Player/AvaSequenceActorFactory.h` (Private)


#### class `UAvaSequenceActorFactory`  
`class UAvaSequenceActorFactory : public UActorFactory`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L14 _public prototype_ `UAvaSequenceActorFactory();`
- L18 _protected prototype_ `virtual bool CanCreateActorFrom(const FAssetData& InAssetData, FText& OutErrorMessage) override;`
- L19 _protected prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;`
- L20 _protected prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* InActorInstance) override;`
- L21 _protected prototype_ `virtual FString GetDefaultActorLabel(UObject* InAsset) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/Schemas/AvaActorSubobjectSchema.h` (Private)


#### class `FAvaActorSubobjectSchema`  
`class FAvaActorSubobjectSchema : public UE::Sequencer::IObjectSchema`  
_L7-15_
- inherits: `UE::Sequencer::IObjectSchema`
- L11 _public prototype_ `virtual UObject* GetParentObject(UObject* InObject) const override;`
- L12 _public prototype_ `virtual UE::Sequencer::FObjectSchemaRelevancy GetRelevancy(const UObject* InObject) const override;`
- L13 _public prototype_ `virtual TSharedPtr<FExtender> ExtendObjectBindingMenu(TSharedRef<FUICommandList> InCommandList, TWeakPtr<ISequencer> InSequencerWeak, TConstArrayView<UObject*> InContextSensitiveObjects) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/AvaSequenceItem.h` (Private)


#### class `FAvaSequenceItem`  
`class FAvaSequenceItem : public IAvaSequenceItem`  
_L11-41_
- inherits: `IAvaSequenceItem`
- L14 _public prototype_ `FAvaSequenceItem(UAvaSequence* InSequence, const TSharedPtr<FAvaSequencer>& InSequencer);`
- L17 _public prototype_ `virtual UAvaSequence* GetSequence() const override;`
- L18 _public prototype_ `virtual FText GetDisplayNameText() const override;`
- L19 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L20 _public prototype_ `virtual FName GetLabel() const override;`
- L21 _public prototype_ `virtual bool CanRelabel(const FText& InText, FText& OutErrorMessage) const override;`
- L22 _public prototype_ `virtual void Relabel(const FName InLabel) override;`
- L23 _public prototype_ `virtual void RequestRelabel() override;`
- L24 _public function_ `virtual TAvaSequenceItemDelegate<FSimpleMulticastDelegate>& GetOnRelabel() override`
- L25 _public prototype_ `virtual bool GetSequenceStatus(EMovieScenePlayerStatus::Type* OutStatus, FFrameTime* OutCurrentFrame, FFrameTime* OutTotalFrames) const override;`
- L26 _public prototype_ `virtual void RefreshChildren() override;`
- L27 _public prototype_ `virtual const TArray<FAvaSequenceItemPtr>& GetChildren() const override;`
- L28 _public prototype_ `virtual TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L29 _public prototype_ `virtual FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L30 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L34 _protected member_ `TWeakPtr<FAvaSequencer> SequencerWeak;`
- L36 _protected member_ `TWeakObjectPtr<UAvaSequence> SequenceWeak;`
- L38 _protected member_ `TAvaSequenceItemDelegate<FSimpleMulticastDelegate> OnRelabel;`
- L40 _protected member_ `TArray<FAvaSequenceItemPtr> Children;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/Columns/AvaSequenceNameColumn.h` (Private)


#### class `FAvaSequenceNameColumn`  
`class FAvaSequenceNameColumn : public IAvaSequenceColumn`  
_L7-18_
- inherits: `IAvaSequenceColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaSequenceNameColumn, IAvaSequenceColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaSequenceItemPtr& InItem, const TSharedPtr<SAvaSequenceItemRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/Columns/AvaSequenceStatusColumn.h` (Private)


#### class `FAvaSequenceStatusColumn`  
`class FAvaSequenceStatusColumn : public IAvaSequenceColumn`  
_L7-18_
- inherits: `IAvaSequenceColumn`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaSequenceStatusColumn, IAvaSequenceColumn);`
- L13 _public prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L14 _public prototype_ `virtual FText GetColumnToolTipText() const override;`
- L15 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L16 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaSequenceItemPtr& InItem, const TSharedPtr<SAvaSequenceItemRow>& InRow) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/Columns/IAvaSequenceColumn.h` (Private)


#### class `IAvaSequenceColumn`  
`class IAvaSequenceColumn : public IAvaTypeCastable, public TSharedFromThis<IAvaSequenceColumn>`  
_L11-25_
- inherits: `IAvaTypeCastable,TSharedFromThis<IAvaSequenceColumn>`
- L14 _public prototype_ `UE_AVA_INHERITS(IAvaSequenceColumn, IAvaTypeCastable);`
- L16 _public function_ `FName GetColumnId() const`
- L18 _public prototype_ `virtual FText GetColumnDisplayNameText() const = 0;`
- L20 _public prototype_ `virtual FText GetColumnToolTipText() const = 0;`
- L22 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() = 0;`
- L24 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FAvaSequenceItemPtr& InItem, const TSharedPtr<SAvaSequenceItemRow>& InRow) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/Columns/Widgets/SAvaSequenceName.h` (Private)


#### class `SAvaSequenceName`  
`class SAvaSequenceName : public SCompoundWidget`  
_L12-36_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SAvaSequenceName)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAvaSequenceItemPtr& InItem, const TSharedPtr<SAvaSequenceItemRow>& InRow);`
- L22 _public prototype_ `FText GetSequenceNameText() const;`
- L24 _public prototype_ `void BeginRename();`
- L26 _public prototype_ `bool OnVerifyNameTextChanged(const FText& InText, FText& OutErrorMessage);`
- L28 _public prototype_ `void OnNameTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo);`
- L31 _protected prototype_ `virtual FText GetToolTipText() const;`
- L33 _protected member_ `TWeakPtr<IAvaSequenceItem> ItemWeak;`
- L35 _protected member_ `TSharedPtr<SInlineEditableTextBlock> InlineTextBlock;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/Columns/Widgets/SAvaSequenceStatus.h` (Private)


#### class `SAvaSequenceStatus`  
`class SAvaSequenceStatus : public SCompoundWidget`  
_L14-42_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SAvaSequenceStatus)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAvaSequenceItemPtr& InItem, const TSharedPtr<SAvaSequenceItemRow>& InRow);`
- L23 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L26 _public prototype_ `FText GetProgressText() const;`
- L28 _public prototype_ `TOptional<float> GetProgressPercent() const;`
- L31 _private member_ `TWeakPtr<IAvaSequenceItem> ItemWeak;`
- L33 _private member_ `FText StatusText;`
- L35 _private member_ `FFrameTime CurrentFrame;`
- L37 _private member_ `FFrameTime TotalFrames;`
- L39 _private member_ `float Progress = 0.f;`
- L41 _private member_ `bool bSequenceInProgress = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/DragDropOps/AvaSequenceItemDragDropOp.h` (Private)


#### class `FAvaSequenceItemDragDropOp`  
`class FAvaSequenceItemDragDropOp : public FAssetDragDropOp`  
_L13-37_
- inherits: `FAssetDragDropOp`
- L16 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FAvaSequenceItemDragDropOp, FAssetDragDropOp) static TSharedRef<FAvaSequenceItemDragDropOp> New(const FAvaSequenceItemPtr& InSequenceItem, UActorFactory* InActorFactory);`
- L20 _public prototype_ `TOptional<EItemDropZone> OnCanDropItem(FAvaSequenceItemPtr InTargetItem) const;`
- L22 _public prototype_ `FReply OnDropOnItem(FAvaSequenceItemPtr InTargetItem);`
- L25 _protected prototype_ `void Init(const FAvaSequenceItemPtr& InSequenceItem, UActorFactory* InActorFactory);`
- L28 _protected function_ `virtual void InitThumbnail() override`
- L32 _protected prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L36 _protected member_ `FAvaSequenceItemPtr SequenceItem;` — Shared Ptr to keep Reference count while drag dropping

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/IAvaSequenceItem.h` (Private)


#### class `IAvaSequenceItem`  
`class IAvaSequenceItem : public TSharedFromThis<IAvaSequenceItem>`  
_L20-61_
- inherits: `TSharedFromThis<IAvaSequenceItem>`
- L23 _public prototype_ `virtual ~IAvaSequenceItem() = default;`
- L25 _public prototype_ `virtual UAvaSequence* GetSequence() const = 0;`
- L27 _public prototype_ `virtual FText GetDisplayNameText() const = 0;`
- L29 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const = 0;`
- L31 _public prototype_ `virtual FName GetLabel() const = 0;`
- L33 _public prototype_ `virtual bool CanRelabel(const FText& InText, FText& OutErrorMessage) const = 0;`
- L35 _public prototype_ `virtual void Relabel(const FName InLabel) = 0;`
- L37 _public prototype_ `virtual void RequestRelabel() = 0;`
- L39 _public prototype_ `virtual TAvaSequenceItemDelegate<FSimpleMulticastDelegate>& GetOnRelabel() = 0;`
- L41 _public prototype_ `virtual bool GetSequenceStatus(EMovieScenePlayerStatus::Type* OutStatus = nullptr , FFrameTime* OutCurrentFrame = nullptr , FFrameTime* OutTotalFrames = nullptr) const = 0;`
- L45 _public prototype_ `virtual void RefreshChildren() = 0;`
- L47 _public prototype_ `virtual const TArray<FAvaSequenceItemPtr>& GetChildren() const = 0;`
- L49 _public prototype_ `virtual TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) = 0;`
- L51 _public prototype_ `virtual FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) = 0;`
- L53 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) = 0;`
- L57 _protected function_ `template<typename T> void Broadcast(TAvaSequenceItemDelegate<T>& InDelegate)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/Widgets/SAvaSequenceItemRow.h` (Private)


#### class `SAvaSequenceItemRow`  
`class SAvaSequenceItemRow : public SMultiColumnTableRow<FAvaSequenceItemPtr>`  
_L16-48_
- inherits: `SMultiColumnTableRow<FAvaSequenceItemPtr>`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAvaSequenceItemRow)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedPtr<STableViewBase>& InOwnerTableView , const FAvaSequenceItemPtr& InItem , const TSharedPtr<FAvaSequencer>& InSequencer);`
- L27 _public prototype_ `FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent , EItemDropZone InDropZone , FAvaSequenceItemPtr InItem);`
- L31 _public prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& InDragDropEvent , EItemDropZone InDropZone , FAvaSequenceItemPtr InItem) const;`
- L36 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L41 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L42 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L45 _protected member_ `TWeakPtr<FAvaSequencer> SequencerWeak;`
- L47 _protected member_ `TWeakPtr<IAvaSequenceItem> ItemWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/SequenceTree/Widgets/SAvaSequenceTree.h` (Private)


#### class `SAvaSequenceTree`  
`class SAvaSequenceTree : public SCompoundWidget`  
_L19-64_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAvaSequenceTree)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedPtr<FAvaSequencer>& InSequencer , const TSharedPtr<SHeaderRow>& InHeaderRow);`
- L29 _public function_ `TSharedPtr<STreeView<FAvaSequenceItemPtr>> GetSequenceTreeView() const`
- L31 _public prototype_ `TSharedPtr<SWidget> OnContextMenuOpening() const;`
- L33 _public prototype_ `void BindCommands(const TSharedRef<FAvaSequencer>& InSequencer);`
- L35 _public prototype_ `TSharedRef<ITableRow> OnGenerateRow(FAvaSequenceItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L37 _public prototype_ `void OnGetChildren(FAvaSequenceItemPtr InItem, TArray<FAvaSequenceItemPtr>& OutChildren) const;`
- L39 _public prototype_ `void OnPostSetViewedSequence(UAvaSequence* InSequence);`
- L41 _public prototype_ `void OnSelectionChanged(FAvaSequenceItemPtr InSelectedItem, ESelectInfo::Type InSelectionInfo);`
- L43 _public prototype_ `void OnSearchChanged(const FText& InSearchText);`
- L46 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L51 _protected prototype_ `static void CreateAddSequencePresetMenu(UToolMenu* InMenu);` — Adds the preset options in the add sequence menu
- L54 _protected prototype_ `TSharedRef<SWidget> CreateAddSequenceMenu() const;` — Creates the add sequence menu when the 'add' button gets clicked
- L56 _protected member_ `TWeakPtr<FAvaSequencer> SequencerWeak;`
- L58 _protected member_ `TSharedPtr<STreeView<FAvaSequenceItemPtr>> SequenceTreeView;`
- L60 _protected member_ `TSharedPtr<SSearchBox> SearchBox;`
- L62 _protected member_ `TSharedPtr<FUICommandList> CommandList;`
- L63 _protected member_ `bool bSyncingSelection = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/StaggerTool/AvaStaggerBarElement.h` (Private)


#### struct `FAvaStaggerBarElement`  
`struct FAvaStaggerBarElement`  
_L20-57_
- desc: Structure that holds cached data for a stagger element operation
- L22 _public prototype_ `static FAvaStaggerBarElement FromTrack(const UE::Sequencer::TViewModelPtr<UE::Sequencer::ITrackAreaExtension>& InTrackAreaExtension);`
- L24 _public function_ `FAvaStaggerBarElement()`
- L25 _public prototype_ `FAvaStaggerBarElement(const UE::Sequencer::TViewModelPtr<UE::Sequencer::FLayerBarModel>& InLayerBar);`
- L26 _public prototype_ `FAvaStaggerBarElement(const UE::Sequencer::TViewModelPtr<UE::Sequencer::ILayerBarExtension>& InSection);`
- L28 _public function_ `bool operator==(const FAvaStaggerBarElement& InOther)`
- L45 _public prototype_ `bool IsValid() const;`
- L47 _public prototype_ `void Offset(const FFrameNumber InDelta);`
- L50 _public member_ `, UE::Sequencer::TViewModelPtr<UE::Sequencer::ILayerBarExtension>> BarModel;`
- L52 _public member_ `UE::Sequencer::TViewModelPtr<UE::Sequencer::IOutlinerExtension> OutlinerItem;`
- L53 _public member_ `TRange<FFrameNumber> Range;`
- L55 _public member_ `FFrameNumber OriginalFrame;`
- L56 _public member_ `FFrameNumber LastOffset;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/StaggerTool/AvaStaggerTool.h` (Private)


#### class `FAvaStaggerTool`  
`class FAvaStaggerTool : public FAvaSequencerAction`  
_L26-181_
- inherits: `FAvaSequencerAction`
- L29 _public prototype_ `explicit FAvaStaggerTool(FAvaSequencer& InOwner);`
- L32 _public prototype_ `TObjectPtr<UAvaSequencerStaggerSettings> GetSettings() const;`
- L34 _public prototype_ `bool HasValidSelection() const;`
- L36 _public prototype_ `bool IsBarSelection() const;`
- L37 _public prototype_ `bool IsKeySelection() const;`
- L39 _public prototype_ `int32 GetSelectionCount() const;`
- L41 _public prototype_ `void Stagger();`
- L43 _public prototype_ `bool IsAutoApplying() const;`
- L45 _public prototype_ `void OnSequencerSelectionChanged();`
- L47 _public prototype_ `bool CanAlignToPlayhead() const;`
- L48 _public prototype_ `void AlignToPlayhead();`
- L50 _public prototype_ `void CloseToolWindow();`
- L64 _private prototype_ `virtual void MapAction(const TSharedRef<FUICommandList>& InCommandList) override;`
- L65 _private prototype_ `virtual void OnSequencerClosed() override;`
- L68 _private prototype_ `bool CanExecute() const;`
- L69 _private prototype_ `void Execute();`
- L71 _private prototype_ `void BindToSequencerSelectionChange();`
- L72 _private prototype_ `void UnbindToSequencerSelectionChange();`
- L74 _private prototype_ `void OnResetToDefaults();`
- L75 _private prototype_ `void OnSettingChange(const FName InPropertyName);`
- L76 _private prototype_ `void OnApply();`
- L78 _private prototype_ `FFrameNumber ConvertTime(FFrameTime InSourceTime) const;`
- L81 _private function_ `template<typename InElementType> FFrameNumber GetStartPosition(const TArray<InElementType>& InElements) const`
- L116 _private prototype_ `TRange<FFrameNumber> GetOperationRange(const EAvaSequencerStaggerRange InRange) const;`
- L118 _private prototype_ `FFrameNumber GetInterval(const FFrameNumber InRangeSize, const int32 InElementCount, const FFrameNumber InElementSize = 0) const;`
- L120 _private prototype_ `FFrameNumber GetBarElementOperationOffset(const FAvaStaggerBarElement& InElement) const;`
- L122 _private prototype_ `static FFrameNumber CalculateBarElementFrameSpan(const TArray<FAvaStaggerBarElement>& InElements, const int32 InStopIndex = INDEX_NONE);`
- L124 _private prototype_ `void CacheOriginalElements();`
- L126 _private prototype_ `FFrameNumber FindFirstBarStaggerPoint() const;`
- L127 _private prototype_ `FFrameNumber FindFirstKeyStaggerPoint() const;`
- L129 _private prototype_ `TArray<FAvaStaggerBarElement> GatherSelectionBarElements(const TSharedPtr<UE::Sequencer::FSequencerSelection>& InSequencerSelection) const;`
- L130 _private prototype_ `TArray<FAvaStaggerKeyElement> GatherSelectionKeyElements() const;`
- L132 _private prototype_ `FFrameNumber CalculateLocalCurveOffset(const float InCurveTime, const TRange<FFrameNumber>& InRange) const;`
- L134 _private prototype_ `FFrameNumber FindNextStaggerLocation(const FAvaStaggerBarElement& InElement , const int32 InElementIndex , const FFrameNumber InFirstFrame , const FFrameNumber InCurrentFrame) const;`
- L138 _private prototype_ `FFrameNumber FindNextStaggerLocation(const FAvaStaggerKeyElement& InElement , const int32 InElementIndex , const FFrameNumber InFirstFrame , const FFrameNumber InCurrentFrame) const;`
- L143 _private prototype_ `void StaggerBarElements();`
- L144 _private prototype_ `void StaggerKeyElements();`
- L146 _private prototype_ `static void SetKeyElementTime(const FAvaStaggerKeyElement& InElement, const FFrameNumber InKeyTime);`
- L149 _private function_ `template<typename InElementType> static void FindFirstFrameInTimeline(const TArray<InElementType>& InElements, FFrameNumber& OutFrame)`
- L162 _private member_ `TSharedPtr<SWindow> ToolWindow;`
- L164 _private member_ `TSharedPtr<SAvaStaggerTool> ToolWidget;`
- L166 _private member_ `TStrongObjectPtr<UAvaSequencerStaggerSettings> Settings;`
- L169 _private member_ `TArray<FAvaStaggerBarElement> OriginalBarElements;` — Cached values at the start of auto-updating
- L170 _private member_ `TArray<FAvaStaggerKeyElement> OriginalKeyElements;`
- L172 _private member_ `int32 CachedBarCount = 0;`
- L173 _private member_ `int32 CachedKeyCount = 0;`
- L175 _private member_ `TRange<FFrameNumber> CachedRange;`
- L176 _private member_ `FFrameNumber CachedRangeSize = 0;`
- L177 _private member_ `FFrameNumber CachedInterval = 0;`
- L178 _private member_ `FFrameNumber CachedShiftFrames = 0;`
- L180 _private member_ `FRandomStream RandomStream;`

#### struct `FAvaStaggerTool::FAvaStaggerKeyElement`  
`struct FAvaStaggerKeyElement`  
_L53-61_
- L55 _public prototype_ `explicit FAvaStaggerKeyElement(UE::Sequencer::TViewModelPtr<UE::Sequencer::FChannelModel> InKeyChannelModel , FKeyHandle InKeyHandle, FFrameNumber InOriginalFrame = 0);`
- L58 _public member_ `UE::Sequencer::TViewModelPtr<UE::Sequencer::FChannelModel> KeyChannelModel;`
- L59 _public member_ `FKeyHandle KeyHandle;`
- L60 _public member_ `FFrameNumber OriginalFrame;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Sequencer` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/StaggerTool/AvaStaggerToolSettings.h` (Private)


#### enum `EAvaSequencerStaggerStartPosition`  
`enum class EAvaSequencerStaggerStartPosition : uint8`  
_L10-25_
- reflection: `UENUM()`
- L13 _public enumerator_ `FirstSelected = 0` — Sequence placement will begin at the position of the first selected
- L15 _public enumerator_ `FirstInTimeline = 1` — Sequence placement will begin at the earliest sequence of the selection
- L17 _public enumerator_ `Playhead = 2` — Sequence placement will begin at the current position of the playhead
- L20 _public enumerator_ `PlaybackRange = 3` — Sequence placement will begin at the start of the playback range
- L22 _public enumerator_ `SelectionRange = 4` — Sequence placement will begin at the start of the selection range
- L24 _public enumerator_ `Default = FirstSelected UMETA(hidden)`

#### enum `EAvaSequencerStaggerDistribution`  
`enum class EAvaSequencerStaggerDistribution : uint8`  
_L28-38_
- reflection: `UENUM()`
- L31 _public enumerator_ `Increment = 0` — Sequences placed one after the other
- L33 _public enumerator_ `Range = 1` — Sequences spaced out between a range
- L35 _public enumerator_ `Random = 255` — Sequences randomly distributed in range
- L37 _public enumerator_ `Default = Increment UMETA(hidden)`

#### enum `EAvaSequencerStaggerRange`  
`enum class EAvaSequencerStaggerRange : uint8`  
_L41-51_
- reflection: `UENUM()`
- L44 _public enumerator_ `Playback = 0` — Sequences distributed between playback range
- L46 _public enumerator_ `Selection = 1` — Sequences distributed between selection range
- L48 _public enumerator_ `Custom = 2` — Sequences distributed between custom user specified frame range
- L50 _public enumerator_ `Default = Playback UMETA(hidden)`

#### struct `FAvaSequencerStaggerOptions`  
`struct FAvaSequencerStaggerOptions`  
_L54-115_
- reflection: `USTRUCT()`
- L58 _public function_ `bool operator==(const FAvaSequencerStaggerOptions& InOther) const`
- L75 _public function_ `bool operator!=(const FAvaSequencerStaggerOptions& InOther) const`
- L81 _public member_ `EAvaSequencerStaggerDistribution Distribution = EAvaSequencerStaggerDistribution::Default;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (Tooltip = "How the layers or keyframes should be distributed after each step"))`
- L84 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (ClampMin = "0", UIMin = "0", Tooltip = "Seed value for randomization"))`
- L87 _public member_ `EAvaSequencerStaggerRange Range = EAvaSequencerStaggerRange::Default;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (Tooltip = "Time range to perform the operation on"))`
- L90 _public member_ `int32 CustomRange = 30;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (UIMin = "-60", UIMax = "60", Tooltip = "Custom time range to perform the operation with"))`
- L93 _public member_ `EAvaSequencerStaggerStartPosition StartPosition = EAvaSequencerStaggerStartPosition::Default;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (Tooltip = "Position to start the first layer or keyframe"))`
- L96 _public member_ `float OperationPoint = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (Tooltip = "Point on the current layer bar at which the next layer is positioned"))`
- L99 _public member_ `int32 Interval = 0;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (UIMin = "-60", UIMax = "60", Tooltip = "Stepping interval between layers or keyframes"))`
- L102 _public member_ `int32 Shift = 0;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (UIMin = "-60", UIMax = "60", Tooltip = "Offset of operation"))`
- L105 _public member_ `int32 Grouping = 1;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (ClampMin = "1", ClampMax = "255", UIMin = "1", UIMax = "10", Tooltip = "Number of layers or keyframes to group together before moving to the next stagger point"))`
- L108 _public member_ `bool bUseCurve = false;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (Tooltip = "Use a curve to layout layers or keyframes"))`
- L111 _public member_ `FRuntimeFloatCurve Curve;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (Tooltip = "Curve to use for distribution between layers or keyframes"))`
- L114 _public member_ `float CurveOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (ClampMin = "-1", ClampMax = "1", UIMin = "-1", UIMax = "1", Tooltip = "Offset of operation"))`

#### class `UAvaSequencerStaggerSettings`  
`class UAvaSequencerStaggerSettings : public UObject`  
_L118-153_
- reflection: `UCLASS()`
- inherits: `UObject`
- L123 _public function_ `UAvaSequencerStaggerSettings()`
- L130 _public function_ `bool CanResetToolOptions() const`
- L135 _public function_ `void ResetToolOptions()`
- L149 _public member_ `bool bAutoApply = false;` — `UPROPERTY()`
- L152 _public member_ `FAvaSequencerStaggerOptions ToolOptions;` — `UPROPERTY(EditAnywhere, Category = "Stagger Tool Options", meta = (ShowOnlyInnerProperties))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/StaggerTool/Customization/AvaStaggerToolSettingsDetailsCustomization.h` (Private)


#### class `FAvaStaggerToolSettingsDetailsCustomization`  
`class FAvaStaggerToolSettingsDetailsCustomization : public IDetailCustomization`  
_L13-67_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakPtr<FAvaStaggerTool> InWeakTool);`
- L18 _public prototype_ `FAvaStaggerToolSettingsDetailsCustomization(const TWeakPtr<FAvaStaggerTool>& InWeakTool);`
- L19 _public function_ `virtual ~FAvaStaggerToolSettingsDetailsCustomization() override`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _private prototype_ `EAvaSequencerStaggerDistribution GetDistributionPropertyValue() const;`
- L27 _private prototype_ `EAvaSequencerStaggerRange GetRangePropertyValue() const;`
- L28 _private prototype_ `EAvaSequencerStaggerStartPosition GetStartPositionPropertyValue() const;`
- L29 _private prototype_ `float GetOperationPointPropertyValue() const;`
- L30 _private prototype_ `bool GetUseCurvePropertyValue() const;`
- L32 _private prototype_ `EVisibility GetCurvePropertyVisibility() const;`
- L33 _private prototype_ `EVisibility GetCurveOffsetPropertyVisibility() const;`
- L34 _private prototype_ `EVisibility GetRandomSeedPropertyVisibility() const;`
- L35 _private prototype_ `EVisibility GetIntervalPropertyVisibility() const;`
- L36 _private prototype_ `EVisibility GetShiftPropertyVisibility() const;`
- L37 _private prototype_ `EVisibility GetRangePropertyVisibility() const;`
- L38 _private prototype_ `EVisibility GetCustomRangePropertyVisibility() const;`
- L39 _private prototype_ `EVisibility GetStartPositionPropertyVisibility() const;`
- L40 _private prototype_ `EVisibility GetOperationPointPropertyVisibility() const;`
- L42 _private prototype_ `void AddCustomIntSpinBoxRow(IDetailPropertyRow& PropertyRow, const TSharedRef<IPropertyHandle> InProperty);`
- L43 _private prototype_ `void AddCustomFloatSpinBoxRow(IDetailPropertyRow& PropertyRow, const TSharedRef<IPropertyHandle> InProperty);`
- L45 _private prototype_ `void AddDistributionRow(IDetailPropertyRow& PropertyRow, const TSharedRef<IPropertyHandle>& InProperty);`
- L46 _private prototype_ `void AddRandomSeedRow(IDetailPropertyRow& PropertyRow, const TSharedRef<IPropertyHandle>& InProperty);`
- L47 _private prototype_ `void AddRangeRow(IDetailPropertyRow& PropertyRow, const TSharedRef<IPropertyHandle>& InProperty);`
- L48 _private prototype_ `void AddStartPositionRow(IDetailPropertyRow& PropertyRow, const TSharedRef<IPropertyHandle>& InProperty);`
- L49 _private prototype_ `void AddOperationPointRow(IDetailPropertyRow& PropertyRow, const TSharedRef<IPropertyHandle>& InProperty);`
- L51 _private member_ `TWeakPtr<FAvaStaggerTool> WeakTool;`
- L53 _private member_ `TSharedPtr<IPropertyHandle> ToolOptionsProperty;`
- L55 _private member_ `TSharedPtr<IPropertyHandle> UseCurveProperty;`
- L56 _private member_ `TSharedPtr<IPropertyHandle> CurveProperty;`
- L57 _private member_ `TSharedPtr<IPropertyHandle> CurveOffsetProperty;`
- L58 _private member_ `TSharedPtr<IPropertyHandle> DistributionProperty;`
- L59 _private member_ `TSharedPtr<IPropertyHandle> RandomSeedProperty;`
- L60 _private member_ `TSharedPtr<IPropertyHandle> RangeProperty;`
- L61 _private member_ `TSharedPtr<IPropertyHandle> CustomRangeProperty;`
- L62 _private member_ `TSharedPtr<IPropertyHandle> StartPositionProperty;`
- L63 _private member_ `TSharedPtr<IPropertyHandle> OperationPointProperty;`
- L64 _private member_ `TSharedPtr<IPropertyHandle> IntervalProperty;`
- L65 _private member_ `TSharedPtr<IPropertyHandle> ShiftProperty;`
- L66 _private member_ `TSharedPtr<IPropertyHandle> GroupingProperty;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/StaggerTool/Widgets/SAvaStaggerOperationPoint.h` (Private)


#### class `SAvaStaggerOperationPoint`  
`class SAvaStaggerOperationPoint : public SCompoundWidget`  
_L10-25_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SAvaStaggerOperationPoint)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<IPropertyHandle>& InWeakProperty);`
- L19 _protected prototype_ `TSharedRef<SCheckBox> CreateButton(const float InValue, const FName InImageBrushName);`
- L22 _private member_ `TWeakPtr<IPropertyHandle> WeakProperty;`
- L24 _private member_ `TArray<TSharedRef<SCheckBox>> Buttons;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/StaggerTool/Widgets/SAvaStaggerSettingsRadioGroup.h` (Private)


#### class `SAvaStaggerSettingsRadioGroup`  
`template<typename InEnumType> class SAvaStaggerSettingsRadioGroup : public SCompoundWidget`  
_L13-115_
- inherits: `SCompoundWidget`
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FEnumValueChangedDelegate, const InEnumType);`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAvaStaggerSettingsRadioGroup)`
- L19 _public function_ `SLATE_EVENT(FEnumValueChangedDelegate, OnValueChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<IPropertyHandle>& InWeakProperty)`
- L63 _protected function_ `TSharedRef<SCheckBox> CreateButton(const InEnumType InValue, const FText& InText, const FText& InToolTipText)`
- L98 _protected function_ `InEnumType GetEnumValue() const`
- L110 _private member_ `TWeakPtr<IPropertyHandle> WeakProperty;`
- L112 _private member_ `FEnumValueChangedDelegate OnValueChanged;`
- L114 _private member_ `TArray<TSharedRef<SCheckBox>> Buttons;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FEnumValueChangedDelegate, const InEnumType);`
- L72 _function_ `` (scope `SAvaStaggerSettingsRadioGroup::CreateButton`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Private/StaggerTool/Widgets/SAvaStaggerTool.h` (Private)


#### class `SAvaStaggerTool`  
`class SAvaStaggerTool : public SCompoundWidget, public FNotifyHook`  
_L19-56_
- inherits: `SCompoundWidget,FNotifyHook`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAvaStaggerTool)`
- L23 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnResetToDefaults) SLATE_EVENT(FAvaStaggerToolSettingChange, OnSettingChange) SLATE_EVENT(FSimpleDelegate, OnApply) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FAvaStaggerTool>& InWeakTool);`
- L31 _protected prototype_ `TSharedRef<SWidget> ConstructDetails();`
- L32 _protected prototype_ `TSharedRef<SWidget> ConstructApplyRow();`
- L34 _protected prototype_ `FText GetSelectionText() const;`
- L35 _protected prototype_ `FText GetSelectionToolTipText() const;`
- L36 _protected prototype_ `FSlateColor GetSelectionTextColor() const;`
- L38 _protected prototype_ `FReply OnApplyButtonClick();`
- L39 _protected prototype_ `FReply OnResetToDefaultsClick();`
- L40 _protected prototype_ `void OnToggleAutoUpdateClick(const ECheckBoxState InNewState);`
- L42 _protected prototype_ `bool OnCanAlignToPlayhead() const;`
- L43 _protected prototype_ `FReply OnAlignToPlayhead();`
- L46 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* const InPropertyChanged) override;`
- L49 _protected member_ `TWeakPtr<FAvaStaggerTool> WeakTool;`
- L51 _protected member_ `FSimpleDelegate OnResetToDefaults;`
- L52 _protected member_ `FAvaStaggerToolSettingChange OnSettingChange;`
- L53 _protected member_ `FSimpleDelegate OnApply;`
- L55 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FAvaStaggerToolSettingChange, const FName ) class SAvaStaggerTool : public SCompoundWidget, public FNotifyHook { public: SLATE_BEGIN_ARGS(SAvaStaggerTool) {} SLATE_EVENT(FSimpleDelegate, OnResetToDefaults) SLATE_EVENT(FAvaStaggerToolSettingChange, OnSettingChange) SLATE_EVENT(FSimpleDelegate, OnApply) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FAvaStaggerTool>& InWeakTool); protected: TSharedRef<SWidget> ConstructDetails(); TSharedRef<SWidget> ConstructApplyRow(); FText GetSelectionText() const; FText GetSelectionToolTipText() const; FSlateColor GetSelectionTextColor() const; FReply OnApplyButtonClick(); FReply OnResetToDefaultsClick(); void OnToggleAutoUpdateClick(const ECheckBoxState InNewState); bool OnCanAlignToPlayhead() const; FReply OnAlignToPlayhead();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/AvaSequenceDefaultTags.h` (Public)


#### class `FAvaSequenceDefaultTags`  
`class FAvaSequenceDefaultTags`  
_L7-17_
- L9 _private prototype_ `FAvaSequenceDefaultTags();`
- L12 _public prototype_ `static const FAvaSequenceDefaultTags& Get();`
- L14 _public member_ `FAvaTagSoftHandle In;`
- L15 _public member_ `FAvaTagSoftHandle Out;`
- L16 _public member_ `FAvaTagSoftHandle Change;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/AvaSequencerArgs.h` (Public)


#### struct `FAvaSequencerArgs`  
`struct FAvaSequencerArgs`  
_L9-25_
- L12 _public member_ `TSharedPtr<IAvaSequencerController> SequencerController;` — Optional Controller instance to use instead of Ava Sequencer instantiating its own
- L18 _public member_ `bool bUseCustomCleanPlaybackMode = false;` — Whether Custom Clean Playback Mode should be used, rather than relying on FSequencer's clean playback that currently only works with level editor viewport clients
- L24 _public member_ `bool bCanProcessSequencerSelections = true;` — Whether FAvaSequencer is allowed to select to/from the ISequencer instance This could be false in, for example, when the ISequencer instance is instantiated as being a Level Editor Sequencer (as it processes the selections in FSequencer)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/AvaSequencerSubsystem.h` (Public)


#### class `UAvaSequencerSubsystem`  
`class UAvaSequencerSubsystem : public UWorldSubsystem`  
_L15-43_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- desc: Subsystem in charge of instancing and keeping reference of the World's Sequencer
- L27 _public prototype_ `TSharedRef<IAvaSequencer> GetOrCreateSequencer(IAvaSequencerProvider& InProvider, FAvaSequencerArgs&& InArgs);` — Gets or Instantiates the World's Sequencer @param InProvider the sequencer provider @param InArgs extra arguments to dictate how the ava sequencer is instantiated @returns an existing or new valid IAvaSequencer instance @note the subsystem holds a non-owning reference of the sequencer, the provider is what ideally should be holding the owning reference
- L29 _public function_ `TSharedPtr<IAvaSequencer> GetSequencer() const`
- L32 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaSequencerCreated, TSharedRef<IAvaSequencer>);` — A delegate that gets executed then a sequencer is created
- L33 _public function_ `FOnAvaSequencerCreated& OnSequencerCreated()`
- L36 _public prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`
- L40 _private member_ `TWeakPtr<IAvaSequencer> SequencerWeak;`
- L42 _private member_ `FOnAvaSequencerCreated OnSequencerCreatedDelegate;`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvaSequencerCreated, TSharedRef<IAvaSequencer>);` — A delegate that gets executed then a sequencer is created

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/AvaSequencerUtils.h` (Public)


#### struct `FAvaSequencerUtils`  
`struct FAvaSequencerUtils`  
_L19-56_
- L21 _public function_ `static const FName& GetSequencerModuleName()`
- L27 _public function_ `static ISequencerModule& GetSequencerModule()`
- L32 _public function_ `static bool IsSequencerModuleLoaded()`
- L37 _public prototype_ `static TSharedRef<IAvaSequencerController> CreateSequencerController();`
- L40 _public prototype_ `static UWorld* GetSequencerWorld(const TSharedRef<ISequencer>& InSequencer);` — @return Motion Design Sequencer World from an ISequencer
- L43 _public prototype_ `static UAvaSequencerSubsystem* GetSequencerSubsystem(const TSharedRef<ISequencer>& InSequencer);` — @return Motion Design Sequencer Subsystem from an ISequencer
- L46 _public prototype_ `static UAvaSceneSubsystem* GetSceneSubsystem(const TSharedRef<ISequencer>& InSequencer);` — @return Motion Design Scene Subsystem from an ISequencer
- L49 _public prototype_ `static IAvaSceneInterface* GetSceneInterface(const TSharedRef<ISequencer>& InSequencer);` — @return Motion Design Scene Interface from an ISequencer
- L52 _public prototype_ `static IAvaSequenceProvider* GetSequenceProvider(const TSharedRef<ISequencer>& InSequencer);` — @return Motion Design Sequence Provider from an ISequencer
- L55 _public prototype_ `static TSharedPtr<IAvaSequencer> GetAvaSequencer(const TSharedRef<ISequencer>& InSequencer);` — @return Motion Design Sequencer from an ISequencer

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/IAvaSequencer.h` (Public)


#### class `IAvaSequencer`  
`class IAvaSequencer`  
_L26-89_
- L29 _public prototype_ `virtual ~IAvaSequencer() = default;`
- L31 _public prototype_ `virtual const IAvaSequencerProvider& GetProvider() const = 0;`
- L34 _public function_ `virtual TSharedRef<ISequencer> GetSequencer() const` — `UE_DEPRECATED(5.7, "Get sequencer by shared reference is deprecated. Use GetSequencerPtr instead.")`
- L40 _public prototype_ `virtual TSharedPtr<ISequencer> GetSequencerPtr() const = 0;` — Gets the sequencer ptr if available.
- L42 _public prototype_ `virtual USequencerSettings* GetSequencerSettings() const = 0;`
- L45 _public prototype_ `virtual void SetBaseCommandList(const TSharedPtr<FUICommandList>& InBaseCommandList) = 0;` — Sets the Command List that the Sequencer will use to append its CommandList to
- L48 _public prototype_ `virtual UAvaSequence* GetViewedSequence() const = 0;` — Get the currently viewed Sequence in Sequencer
- L51 _public prototype_ `virtual UAvaSequence* GetDefaultSequence() const = 0;` — Get the Provider's Default Sequence (e.g. a fallback sequence to view), setting a new valid one if not set
- L54 _public prototype_ `virtual void SetViewedSequence(UAvaSequence* InSequenceToView) = 0;` — Sets the Sequencer to view the provided Sequence
- L57 _public prototype_ `virtual TArray<UAvaSequence*> GetSequencesForObject(UObject* InObject) const = 0;` — Finds all the sequences the given object is in
- L59 _public prototype_ `virtual TSharedRef<SWidget> CreateSequenceWidget() = 0;`
- L62 _public prototype_ `virtual void OnActorsCopied(FString& InOutCopiedData, TConstArrayView<AActor*> InCopiedActors) = 0;` — Should be called when Actors have been copied and give Ava Sequencer opportunity to add to the Buffer to copy the Sequence data for those Actors
- L65 _public prototype_ `virtual void OnActorsPasted(FStringView InPastedData, const TMap<FName, AActor*>& InPastedActors) = 0;` — Should be called when Actors have been pasted to parse the data that was filled in by IAvaSequencer::OnActorsCopied
- L68 _public prototype_ `virtual void OnEditorSelectionChanged(const FAvaEditorSelection& InEditorSelection) = 0;` — Should be called when the Editor (non-Sequencer) selection has changed and needs to propagate to the Sequencer Selection
- L71 _public prototype_ `virtual void NotifyOnSequenceTreeChanged() = 0;` — Should be called when the UAvaSequence tree has changed, so that FAvaSequencer can trigger a UI refresh
- L74 _public prototype_ `virtual const TArray<TWeakObjectPtr<UAvaSequence>>& GetRootSequences() const = 0;` — Gets the list of embedded level sequences
- L76 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSequenceAdded, UAvaSequence*);`
- L77 _public prototype_ `virtual FOnSequenceAdded& OnSequenceAdded() = 0;`
- L79 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSequenceRemoved, UAvaSequence*);`
- L80 _public prototype_ `virtual FOnSequenceRemoved& OnSequenceRemoved() = 0;`
- L82 _public prototype_ `virtual bool CanAddSequence() const = 0;`
- L83 _public prototype_ `virtual UAvaSequence* AddSequence(UAvaSequence* const InParentSequence = nullptr) = 0;`
- L86 _public prototype_ `virtual uint32 AddSequenceFromPresets(TConstArrayView<const FAvaSequencePreset*> InPresets) = 0;` — Creates new sequences based on the given presets
- L88 _public prototype_ `virtual void DeleteSequences(const TSet<UAvaSequence*>& InSequences) = 0;`

#### Free symbols / members of external scopes

- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSequenceAdded, UAvaSequence*);`
- L79 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSequenceRemoved, UAvaSequence*);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/IAvaSequencerController.h` (Public)


#### class `IAvaSequencerController`  
`class IAvaSequencerController : public TSharedFromThis<IAvaSequencerController>`  
_L9-15_
- inherits: `TSharedFromThis<IAvaSequencerController>`
- L12 _public prototype_ `virtual ~IAvaSequencerController() = default;`
- L14 _public prototype_ `virtual void SetSequencer(const TSharedPtr<ISequencer>& InSequencer) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/IAvaSequencerProvider.h` (Public)


#### class `IAvaSequencerProvider`  
`class IAvaSequencerProvider`  
_L21-58_
- L24 _public prototype_ `virtual ~IAvaSequencerProvider() = default;`
- L26 _public prototype_ `virtual TSharedPtr<IAvaSequencer> GetAvaSequencer() const = 0;`
- L29 _public function_ `virtual TSharedPtr<ISequencer> GetExternalSequencer() const` — Option for FAvaSequencer to use an externally instanced ISequencer instead of instancing its own
- L31 _public function_ `virtual void OnViewedSequenceChanged(UAvaSequence* InOldSequence, UAvaSequence* InNewSequence)`
- L34 _public prototype_ `virtual IAvaSequenceProvider* GetSequenceProvider() const = 0;` — Returns the Sequence Provider (for managing AvaSequences like Adding/Removing Sequences, etc)
- L37 _public prototype_ `virtual FEditorModeTools* GetSequencerModeTools() const = 0;` — Returns the Mode Tools used (e.g. for Selections)
- L39 _public prototype_ `virtual IAvaSequencePlaybackObject* GetPlaybackObject() const = 0;`
- L42 _public prototype_ `virtual TSharedPtr<IToolkitHost> GetSequencerToolkitHost() const = 0;` — Returns the Toolkit Host to use by Sequencer
- L45 _public prototype_ `virtual UObject* GetPlaybackContext() const = 0;` — Gets the Context object to use
- L48 _public prototype_ `virtual bool CanEditOrPlaySequences() const = 0;` — Returns whether Sequences can be played in the Sequencer
- L51 _public function_ `virtual void GetCustomCleanViewViewportClients(TArray<TWeakPtr<FEditorViewportClient>>& OutViewportClients) const` — Gets the Editor Viewport Clients to be affected by the Custom Clean View
- L54 _public function_ `virtual void OnUpdateCameraCut(UObject* InCameraObject, bool bInJumpCut)` — Called when a camera cut occurs.
- L57 _public function_ `virtual void ExportSequences(TConstArrayView<UAvaSequence*> InSequencesToExport)` — Implementation of converting the Sequences to Level Sequence assets

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/Settings/AvaMarkSetting.h` (Public)


#### struct `FAvaMarkSetting`  
`struct FAvaMarkSetting`  
_L10-22_
- reflection: `USTRUCT()`
- L15 _public member_ `FString Label;` — `UPROPERTY(EditAnywhere, Category = "Mark")`
- L18 _public member_ `int32 FrameNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Mark")`
- L21 _public member_ `FAvaMark Mark;` — `UPROPERTY(EditAnywhere, Category = "Mark")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/Settings/AvaSequencePreset.h` (Public)


#### struct `FAvaSequencePreset`  
`struct FAvaSequencePreset`  
_L13-77_
- reflection: `USTRUCT()`
- desc: Simple settings to apply to a sequence
- L17 _public typedef_ `using FKeyType = FName;`
- L19 _public prototype_ `FAvaSequencePreset() = default;`
- L20 _public prototype_ `virtual ~FAvaSequencePreset() = default;`
- L22 _public function_ `explicit FAvaSequencePreset(FName InPresetName) : PresetName(InPresetName)`
- L27 _public prototype_ `bool ShouldModifySequence() const;`
- L29 _public prototype_ `bool ShouldModifyMovieScene() const;`
- L31 _public prototype_ `void ApplyPreset(UAvaSequence* InSequence) const;`
- L33 _public function_ `bool operator==(const FAvaSequencePreset& InOther) const`
- L38 _public function_ `bool operator==(const FAvaSequencePreset::FKeyType& InKey) const`
- L50 _public member_ `FName PresetName;` — `UPROPERTY(EditAnywhere, Category="Sequence")` — Name to identify this preset
- L54 _public member_ `FName SequenceLabel;` — `UPROPERTY(EditAnywhere, Category="Sequence", meta=(EditCondition="bEnableLabel"))` — If not none, the sequence label to set
- L57 _public member_ `FAvaTagSoftHandle SequenceTag;` — `UPROPERTY(EditAnywhere, Category="Sequence", meta=(EditCondition="bEnableTag"))`
- L61 _public member_ `double EndTime = 1.0;` — `UPROPERTY(EditAnywhere, Category="Sequence", meta=(EditCondition="bEnableEndTime"))` — Initial end time to set for a sequence, in seconds
- L64 _public member_ `TArray<FAvaMarkSetting> Marks;` — `UPROPERTY(EditAnywhere, Category="Sequence", meta=(EditCondition="bEnableMarks"))`
- L67 _public member_ `bool bEnableLabel = false;` — `UPROPERTY(meta=(InlineEditConditionToggle))`
- L70 _public member_ `bool bEnableTag = false;` — `UPROPERTY(meta=(InlineEditConditionToggle))`
- L73 _public member_ `bool bEnableEndTime = false;` — `UPROPERTY(meta=(InlineEditConditionToggle))`
- L76 _public member_ `bool bEnableMarks = false;` — `UPROPERTY(meta=(InlineEditConditionToggle))`

#### struct `FAvaSequencePresetGroup`  
`struct FAvaSequencePresetGroup`  
_L81-109_
- reflection: `USTRUCT()`
- desc: Represents one or many presets to apply
- L85 _public typedef_ `using FKeyType = FName;`
- L87 _public function_ `bool operator==(const FAvaSequencePresetGroup& InOther) const`
- L92 _public function_ `bool operator==(const FAvaSequencePreset::FKeyType& InKey) const`
- L104 _public member_ `FName GroupName;` — `UPROPERTY(EditAnywhere, Category="Sequence")` — Identifier of this group
- L108 _public member_ `TArray<FName> PresetNames;` — `UPROPERTY(EditAnywhere, Category="Sequence")` — The presets that this group represents

#### Free symbols / members of external scopes

- L43 _function_ `friend uint32 GetTypeHash(const FAvaSequencePreset& InPreset)`
- L97 _function_ `friend uint32 GetTypeHash(const FAvaSequencePresetGroup& InPresetGroup)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/Settings/AvaSequencerDisplayRate.h` (Public)


#### struct `FAvaSequencerDisplayRate`  
`struct FAvaSequencerDisplayRate`  
_L9-15_
- reflection: `USTRUCT(BlueprintType)`
- L14 _public member_ `FFrameRate FrameRate;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/Settings/AvaSequencerSettings.h` (Public)


#### class `UAvaSequencerSettings`  
`class UAvaSequencerSettings : public UDeveloperSettings`  
_L15-107_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta = (DisplayName = "Sequencer"))`
- inherits: `UDeveloperSettings`
- L20 _public member_ `static constexpr const TCHAR* SettingsCategory = TEXT("Mot`
- L21 _public member_ `static constexpr const TCHAR* SettingsSection = TEXT("Seq`
- L24 _public member_ `static const FLazyName TransitionLogicStarterGroup;` — Group name for the built-in default groups
- L25 _public member_ `static const FLazyName TransitionLogicSubLayerGroup;`
- L28 _public member_ `static const FLazyName DefaultChangeInName;` — Default change sequence names
- L29 _public member_ `static const FLazyName DefaultChangeOutName;`
- L31 _public prototype_ `UAvaSequencerSettings();`
- L33 _public function_ `FFrameRate GetDisplayRate() const`
- L38 _public function_ `double GetStartTime() const`
- L43 _public function_ `double GetEndTime() const`
- L49 _public prototype_ `const FAvaSequencePreset* FindPreset(FName InPresetName) const;` — Attempts to find the preset with the given preset name, first searching in the custom presets, then looking at the default presets
- L52 _public prototype_ `const FAvaSequencePresetGroup* FindPresetGroup(FName InGroupName) const;` — Attempts to find the preset group with the given preset name, first searching in the custom groups, then looking at the default (TL) groups
- L55 _public prototype_ `TArray<const FAvaSequencePreset*> GatherPresetsFromGroup(FName InGroupName) const;` — Finds all the presets within a preset group
- L57 _public prototype_ `TConstArrayView<FAvaSequencePreset> GetDefaultSequencePresets() const;`
- L59 _public prototype_ `TConstArrayView<FAvaSequencePresetGroup> GetTransitionLogicPresetGroups() const;`
- L61 _public function_ `const TSet<FAvaSequencePreset>& GetCustomSequencePresets() const`
- L66 _public function_ `const TSet<FAvaSequencePresetGroup>& GetCustomPresetGroups() const`
- L72 _public function_ `FSidebarState& GetSidebarState()` — `UE_DEPRECATED(5.6, "The Motion Design sidebar drawer was moved to the Sequencer sidebar and now stores its state in USequencerSettings. Use USequencerSettings::GetSidebarState() instead.")`
- L78 _public function_ `void SetSidebarState(const FSidebarState& InSidebarState)` — `UE_DEPRECATED(5.6, "The Motion Design sidebar drawer was moved to the Sequencer sidebar and now stores its state in USequencerSettings. Use USequencerSettings::SetSidebarState() instead.")`
- L86 _private member_ `FAvaSequencerDisplayRate DisplayRate;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback")` — The default display rate to use for new sequences
- L90 _private member_ `double StartTime = 0.0;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback")` — The default start time to use for new sequences
- L94 _private member_ `double EndTime = 2.0;` — `UPROPERTY(Config, EditAnywhere, Category = "Playback")` — The default end time to use for new sequences
- L98 _private member_ `TSet<FAvaSequencePreset> CustomSequencePresets;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequencer")` — Sequence Presets that are uniquely identified by their Preset Name
- L102 _private member_ `TSet<FAvaSequencePresetGroup> CustomPresetGroups;` — `UPROPERTY(Config, EditAnywhere, Category = "Sequencer")` — Sequence Preset groups that will be served as options when creating sequences
- L106 _private member_ `FSidebarState SidebarState_DEPRECATED;` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "The Motion Design sidebar drawer was moved to the Sequencer sidebar and now stores its state in USequencerSettings"))` — The state of a sidebar to be restored when Sequencer is initialized

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AVALANCHESEQUENCER_API`
