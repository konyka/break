# Plugins / TakeRecorderSources

- module root: `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources`
- headers: 15; symbols: 366
- symbol kinds: class=15, delegate=4, enum=1, enumerator=3, function=29, macro=9, member=84, namespace=10, prototype=206, struct=4, typedef=1
- PrivateDependencyModuleNames: AudioCaptureEditor, CinematicCamera, Core, CoreUObject, EditorFramework, Engine, InputCore, LevelEditor, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneTracks, SceneOutliner, SequenceRecorder, Sequencer, SerializedRecorderInterface, Slate, SlateCore, TakeMovieScene, TakeRecorder, TakesCore, UnrealEd
- PublicDependencyModuleNames: Core, TakeTrackRecorders

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Private/ActorTakeRecorderDropHandler.h` (Private)


#### struct `UE::TakeRecorderSources::FActorTakeRecorderDropHandler`  
`struct FActorTakeRecorderDropHandler : ITakeRecorderDropHandler`  
_L13-19_
- inherits: `ITakeRecorderDropHandler`
- L15 _public prototype_ `virtual void HandleOperation(TSharedPtr<FDragDropOperation> InOperation, UTakeRecorderSources* Sources) override;`
- L16 _public prototype_ `virtual bool CanHandleOperation(TSharedPtr<FDragDropOperation> InOperation, UTakeRecorderSources* Sources) override;`
- L18 _public prototype_ `TArray<AActor*> GetValidDropActors(TSharedPtr<FDragDropOperation> InOperation, UTakeRecorderSources* Sources);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace TakeRecorderSources` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Private/TakeRecorderSourcesCommands.h` (Private)


#### class `FTakeRecorderSourcesCommands`  
`class FTakeRecorderSourcesCommands : public TCommands<FTakeRecorderSourcesCommands>`  
_L8-17_
- inherits: `TCommands<FTakeRecorderSourcesCommands>`
- L11 _public prototype_ `FTakeRecorderSourcesCommands();`
- L13 _public member_ `TSharedPtr<FUICommandInfo> RecordSelectedActors;`
- L16 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Private/TakeRecorderSourcesModule.h` (Private)


#### class `UE::TakeRecorderSources::FTakeRecorderSourcesModule`  
`class FTakeRecorderSourcesModule : public ITakeRecorderSourcesModule, private FSelfRegisteringExec`  
_L28-92_
- inherits: `ITakeRecorderSourcesModule,FSelfRegisteringExec`
- L32 _public function_ `static FTakeRecorderSourcesModule& Get()`
- L38 _public prototype_ `virtual void StartupModule() override;`
- L39 _public prototype_ `virtual void ShutdownModule() override;`
- L40 _public prototype_ `virtual void RegisterCanRecordDelegate(FName HandleId, FCanRecordDelegate InDelegate) override;`
- L41 _public prototype_ `virtual void UnregisterCanRecordDelegate(FName HandleId) override;`
- L44 _public prototype_ `bool CanRecord(const FCanRecordArgs& InArgs);`
- L49 _private member_ `FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors LevelEditorMenuExtenderDelegate;`
- L52 _private member_ `FActorTakeRecorderDropHandler ActorDropHandler;`
- L53 _private member_ `FDelegateHandle SourcesMenuExtension;`
- L56 _private member_ `FDelegateHandle LevelEditorExtenderDelegateHandle;`
- L59 _private member_ `FDelegateHandle OnSequencerCreatedHandle;`
- L61 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L63 _private member_ `TMap<FName, FCanRecordDelegate> CanRecordDelegates;`
- L65 _private prototype_ `void RegisterMenuExtensions();`
- L66 _private prototype_ `void UnregisterMenuExtensions();`
- L67 _private prototype_ `void BindCommands();`
- L69 _private prototype_ `TSharedRef<FExtender> ExtendLevelViewportContextMenu(const TSharedRef<FUICommandList> InCommandList, const TArray<AActor*> SelectedActors);`
- L72 _private prototype_ `static void ExtendSourcesMenu(TSharedRef<FExtender> Extender, UTakeRecorderSources* Sources);`
- L73 _private prototype_ `static void PopulateSourcesMenu(FMenuBuilder& MenuBuilder, UTakeRecorderSources* Sources);`
- L74 _private prototype_ `static void PopulateActorSubMenu(FMenuBuilder& MenuBuilder, UTakeRecorderSources* Sources);`
- L78 _private prototype_ `virtual bool Exec_Editor(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L80 _private prototype_ `bool HandleRecordTakeCommand(UWorld* InWorld, const TCHAR* InStr, FOutputDevice& Ar);`
- L81 _private prototype_ `bool HandleStopRecordTakeCommand(UWorld* InWorld, const TCHAR* InStr, FOutputDevice& Ar);`
- L82 _private prototype_ `bool HandleCancelRecordTakeCommand(UWorld* InWorld, const TCHAR* InStr, FOutputDevice& Ar);`
- L84 _private prototype_ `void RecordActors(const TArray<AActor*>& ActorsToRecord, TOptional<ULevelSequence*> LevelSequence, TOptional<ULevelSequence*> RootLevelSequence);`
- L85 _private prototype_ `void RecordSelectedActors();`
- L88 _private prototype_ `void OnSequencerCreated(TSharedRef<ISequencer> Sequencer);`
- L91 _private prototype_ `UTakeRecorderSource* OnNewActorReferenceBindingAdded(AActor* InActor, ULevelSequence* InLevelSequence);`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace TakeRecorderSources` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Private/TakeRecorderSourcesUtils.h` (Private)


#### Free symbols / members of external scopes

- L21 _namespace_ `namespace TakeRecorderSourcesUtils`
- L26 _function_ `static UWorld* GetSourceWorld(ULevelSequence* InSequence)` (scope `TakeRecorderSourcesUtils`) — Get the first PIE world, or first world from the actor sources, or the first world
- L73 _function_ `static bool IsActorBeingRecorded(const UTakeRecorderSource* InSource, AActor* Actor)` (scope `TakeRecorderSourcesUtils`) — Is the specified actor part of the current recording? This allows us to do some discovery for attachments and hierarchies. @param  Actor	Actor to check @return True if the specified actor is being recorded by another source.
- L92 _function_ `static bool IsActorRecordable(const AActor* Actor)` (scope `TakeRecorderSourcesUtils`)
- L105 _function_ `static FGuid GetRecordedActorGuid(const UTakeRecorderSource* InSource, class AActor* Actor)` (scope `TakeRecorderSourcesUtils`) — Get the object binding for a given actor that is being recorded. An actor can either be a Possessable or a Spawnable but we only have pointers to the original object being recorded. To solve this, we iterate through each actor being recorded and ask it what Guid it ended up with which ends up abstracting away if it's a Spawnable or a Possessable. @param Actor Actor to look for. @return A valid guid if the actor is being recorded otherwise an invalid guid.
- L129 _function_ `static FTransform GetRecordedActorAnimationInitialRootTransform(const UTakeRecorderSource* InSource, class AActor* Actor)` (scope `TakeRecorderSourcesUtils`) — Returns original transform that may get set when recording a skeletal mesh animation. Needed to correctly transform attached children. @param Actor Actor to look for. @return The FTransform applied to the actor when recording animation, that the attached actor may need to apply to themselves to orient correctly.
- L160 _function_ `static ULevelSequence* GetLevelSequence(const UTakeRecorderSource* InSource, const AActor* Actor, ULevelSequence* RootLevelSequence)` (scope `TakeRecorderSourcesUtils`) — Get the sequence of the level sequence the other actor is coming from. Used for setting cross sequence bindings. @param Actor Actor to look for. @return The Sequence
- L190 _function_ `static FMovieSceneSequenceID GetLevelSequenceID(const UTakeRecorderSource* InSource, class AActor* Actor, ULevelSequence* RootLevelSequence)` (scope `TakeRecorderSourcesUtils`) — Get the sequence id of the level sequence the other actor is coming from. Used for setting cross sequence bindings. @param Actor Actor to look for. @return The Sequence ID
- L213 _function_ `static UTakeRecorderActorSource* StartRecordingActorDuringSession(AActor* InActor, ULevelSequence* InLevelSequence)` (scope `TakeRecorderSourcesUtils`) — Create a new actor source for an actor which can be done during an active recording session.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/ITakeRecorderSourcesModule.h` (Public)


#### struct `UE::TakeRecorderSources::FCanRecordArgs`  
`struct FCanRecordArgs`  
_L11-16_
- L13 _public member_ `TNotNull<UObject*> ObjectToRecord;`
- L15 _public function_ `explicit FCanRecordArgs(TNotNull<UObject*> InObjectToRecord) : ObjectToRecord(InObjectToRecord)`

#### class `UE::TakeRecorderSources::ITakeRecorderSourcesModule`  
`class ITakeRecorderSourcesModule : public IModuleInterface`  
_L19-40_
- inherits: `IModuleInterface`
- L23 _public function_ `static ITakeRecorderSourcesModule& Get()`
- L28 _public function_ `static bool IsAvailable()`
- L38 _public prototype_ `virtual void RegisterCanRecordDelegate(FName HandleId, FCanRecordDelegate InDelegate) = 0;` — When building UTakeRecorderActorSource::RecordedProperties, decides whether an object should be included in the list of recorded objects. This is a conjunction, i.e. all registered delegates must return true for the object to be recorded; in other words, only one delegate need return false for the object to not be recorded.
- L39 _public prototype_ `virtual void UnregisterCanRecordDelegate(FName HandleId) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TakeRecorderSources` (scope `UE`)
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanRecordDelegate, const FCanRecordArgs&);`
- L17 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanRecordDelegate, const FCanRecordArgs&);` (scope `UE::TakeRecorderSources`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderActorSource.h` (Public)


#### enum `ETakeRecorderActorRecordType`  
`enum class ETakeRecorderActorRecordType : uint8`  
_L32-37_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `Possessable`
- L35 _public enumerator_ `Spawnable`
- L36 _public enumerator_ `ProjectDefault`

#### class `UTakeRecorderActorSource`  
`class UTakeRecorderActorSource : public UTakeRecorderSource, public IMovieSceneTrackRecorderHost`  
_L45-468_
- reflection: `UCLASS(MinimalAPI, Category="Actors")`
- inherits: `UTakeRecorderSource,IMovieSceneTrackRecorderHost`
- desc: This Take Recorder Source can record an actor from the World's properties. Records the properties of the actor and the components on the actor and safely handles new components being spawned at runtime and the actor being destroyed.
- L52 _public member_ `TSoftObjectPtr<AActor> Target;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Source Actor", Category="Actor Source")` — Reference to the actor in the world that should have it's properties recorded.
- L59 _public member_ `ETakeRecorderActorRecordType RecordType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Source")` — Should this actor be recorded as a Possessable in Sequencer? If so the resulting Object Binding will not create a Spawnable copy of this object and instead will possess this object in the level.
- L65 _public member_ `ETakeRecorderSpawnableOverwriteBehavior SpawnableOverwriteBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Source")` — Should recording this actor as a spawnable overwrite existing spawnables or not.
- L70 _public member_ `bool bRecordParentHierarchy;` — `UE_DEPRECATED(5.8, "bRecordParentHierarchy has been deprecated. Please use AttachRecordBehaviour instead.")` — `UPROPERTY(BlueprintReadWrite, BlueprintGetter = GetRecordParentHierarchy, BlueprintSetter = SetRecordParentHierarchy, Category = "Actor Source", meta = (DeprecatedProperty = "Note", DeprecationMessage = "Please use AttachRecordBehaviour instead."))`
- L79 _public member_ `ETakeRecorderAttachRecordBehaviour AttachRecordBehaviour;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetAttachRecordBehaviour, BlueprintSetter = SetAttachRecordBehaviour, Category = "Actor Source")` — Control how attachments and hierarchies are recorded. If recording to possessable and the parent is not recorded or controlled by a sequence, the recorded transforms will be in local space since the child will still be attached to the parent in the level after recording.  If recording to spawnable and the parent is not recorded or controlled by a sequence, the recorded transforms will be in global space since the child will not be attached to the parent in the level.
- L83 _public member_ `bool bReduceKeys;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Source")` — Whether to perform key-reduction algorithms as part of the recording
- L90 _public member_ `TObjectPtr<UActorRecorderPropertyMap> RecordedProperties;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, meta=(ShowInnerProperties), Category = "Actor Source")` — Lists the properties and components on the current actor and whether or not each property will be recorded into a track in the resulting Level Sequence.
- L94 _public member_ `TArray<FString> IncludeAnimationNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Source")` — Include only the animation bones/curves that match this list
- L98 _public member_ `TArray<FString> ExcludeAnimationNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Source")` — Exclude all animation bones/curves that match this list
- L102 _public member_ `TObjectPtr<ULevelSequence> TargetLevelSequence;` — `UPROPERTY()` — The level sequence that this source is being recorded into. Set during PreRecording, null after PostRecording.
- L106 _public member_ `TObjectPtr<ULevelSequence> RootLevelSequence;` — `UPROPERTY()` — The root or uppermost level sequence that this source is being recorded into. Set during PreRecording, null after PostRecording.
- L115 _public member_ `TArray<TObjectPtr<UObject>> FactorySettings;` — `UPROPERTY()` — Dynamically created list of settings objects for the different factories that are recording something on this actor. If a Factory has no properties it can record the settings objects will not get created. Only one instance of this object exists for a factory and the factory recorder will be passed the shared instance.
- L122 _public member_ `TArray<TObjectPtr<class UMovieSceneTrackRecorder>> TrackRecorders;` — `UPROPERTY()` — An array of section recorders created during the recording process that are capturing data about the actor/components. Will be an empty list when a recording is not in progress.
- L126 _public member_ `TObjectPtr<UTakeRecorderActorSource> ParentSource;` — `UPROPERTY()` — The parent actor source that generated this actor source (ie. through parenting or as an attached component). Null after PostRecording
- L130 _public member_ `bool bShowProgressDialog;` — `UPROPERTY()` — Show Dialog during the (possibly) slow parts of the take recording
- L142 _public prototype_ `static UTakeRecorderSource* AddSourceForActor(AActor* InActor, UTakeRecorderSources* InSources);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder")` — Add a take recorder source for the given actor. @param InActor The actor to add a source for @param InSources The sources to add the actor to @return The added source or the source already present with the same actor
- L151 _public prototype_ `static void RemoveActorFromSources(AActor* InActor, UTakeRecorderSources* InSources);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder")` — Remove the given actor from TakeRecorderSources. @param InActor The actor to remove from the sources @param InSources The sources from where to remove the actor
- L156 _public prototype_ `static bool AllowsSpawnableObjects();` — External Sequencers can set whether spawnables are allowed for this Take Recorder
- L157 _public prototype_ `static void SetAllowsSpawnableObjects(bool bInAllowsSpawnableObjects);`
- L160 _public prototype_ `UTakeRecorderActorSource(const FObjectInitializer& ObjInit);`
- L163 _public prototype_ `virtual void Initialize() override;` — UTakeRecorderSource Interface
- L164 _public prototype_ `virtual bool IsValid() const override;`
- L165 _public prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;`
- L166 _public prototype_ `virtual void OnAllSourcesPreRecordingFinished() override;`
- L167 _public prototype_ `virtual void StartRecording(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame, class ULevelSequence* InSequence) override;`
- L168 _public prototype_ `virtual void TickRecording(const FQualifiedFrameTime& CurrentSequenceTime) override;`
- L169 _public prototype_ `virtual void StopRecording(class ULevelSequence* InSequence) override;`
- L170 _public prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, class ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L171 _public prototype_ `virtual void FinalizeRecording() override;`
- L172 _public function_ `virtual TArray<UObject*> GetAdditionalSettingsObjects() const`
- L173 _public prototype_ `virtual FString GetSubsceneTrackName(ULevelSequence* InSequence) const override;`
- L174 _public prototype_ `virtual FString GetSubsceneAssetName(ULevelSequence* InSequence) const override;`
- L175 _public prototype_ `virtual void AddContentsToFolder(class UMovieSceneFolder* InFolder) override;`
- L176 _public prototype_ `virtual bool ShouldCreateFolderForContents() const override;`
- L177 _public function_ `virtual FMovieSceneSequenceID GetSequenceID() const override`
- L178 _public prototype_ `virtual const IMovieSceneTrackRecorderHost* AsTrackRecorderHost() const override;`
- L179 _public prototype_ `virtual bool IsActorSourceForActor(const AActor* Actor) const override;`
- L180 _public prototype_ `virtual bool OverwriteExistingTrackData() const override;`
- L181 _public prototype_ `virtual void PreRemove() override;`
- L186 _public prototype_ `void SetSourceActor(TSoftObjectPtr<AActor> InTarget);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder Actor Source")` — Set the Target actor that we are going to record. Will reset the Recorded Property Map to defaults.
- L190 _public function_ `TSoftObjectPtr<AActor> GetSourceActor() const` — `UFUNCTION(BlueprintPure, Category = "Take Recorder Actor Source")` — Get the target source actor.
- L194 _public function_ `ETakeRecorderAttachRecordBehaviour GetAttachRecordBehaviour() const` — `UFUNCTION(BlueprintGetter)` — Get the resolved attach record behaviour. This will resolve from Project Settings if needed.
- L198 _public prototype_ `void SetAttachRecordBehaviour(ETakeRecorderAttachRecordBehaviour InAttachRecordBehaviour);` — `UFUNCTION(BlueprintSetter)` — Set the current attach record behaviour.
- L202 _public function_ `bool GetRecordParentHierarchy() const` — `UFUNCTION(BlueprintGetter, meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use AttachRecordBehaviour instead."))` — Get if we are recording the parent hierarchy. True if the resolved attach behaviour is equal to ETakeRecorderAttachRecordBehaviour::Hierarchy.
- L206 _public prototype_ `void SetRecordParentHierarchy(bool bValue);` — `UFUNCTION(BlueprintSetter, meta = (DeprecatedFunction = "Note", DeprecationMessage = "Use AttachRecordBehaviour instead."))` — Set if the parent hierarchy should be recorded or not. Sets AttachRecordBehaviour.
- L209 _public function_ `FGuid GetObjectBindingGuid() const` — Get the Guid of the Object Binding that this Actor Source created in the resulting Level Sequence.
- L215 _public prototype_ `bool GetRecordToPossessable() const;` — Get the record type. If set to project default, gets the type from the project settings
- L218 _public prototype_ `void SetIsTemporarySource(bool bValue);` — If this source should be cleaned up later.
- L227 _protected prototype_ `void RebuildRecordedPropertyMap();` — Request that we re-build the map of which properties to record. This should only be called when the target Actor is changed as it will wipe out the users preference for which properties are going to get recorded and default them back to the Project Preferences for that particular Actor/Component.
- L228 _protected prototype_ `void RebuildRecordedPropertyMapRecursive(const FFieldVariant& InObject, UActorRecorderPropertyMap* PropertyMap, const FString& OuterStructPath = FString());`
- L237 _protected prototype_ `UActorRecorderPropertyMap* GetParentPropertyMapForComponent(UActorComponent* InComponent);` — Looks at the given component and determines what the parent of this component is. For the root component and Actor Components the parent will be the root Property Map. For all other components, will attempt to find the Property Map which has a child Property Map that references the given component. Used to find which property map a new property map should be added to while respecting the component hierarchy.
- L240 _protected prototype_ `UActorRecorderPropertyMap* GetPropertyMapForComponentRecursive(UActorComponent* InComponent, UActorRecorderPropertyMap* CurrentPropertyMap);` — Looks through the given Property Map recursively to find a property map which references the given component.
- L247 _protected prototype_ `void CreateSectionRecordersRecursive(UObject* ObjectToRecord, UActorRecorderPropertyMap* PropertyMap, TArray<UObject*>& TraversedObjects);` — This is called when recording starts to generate the Section Recorders for the actor and all components that it currently has, as well as again during runtime for any newly added components. This instantiates the TrackRecorders needed, but CreateTrack will not be called until DoCreatePendingTrackRecorders() is called.
- L250 _protected prototype_ `void UpdateCachedNumberOfRecordedProperties();` — Update our cached properties for what will be recorded. Done here so the UI doesn't have to iterate through map every frame.
- L253 _protected prototype_ `FGuid ResolveActorFromSequence(AActor* InActor, ULevelSequence* CurrentSequence) const;` — Returns the Guid of the Possessable in the specified sequence that represents the given actor, or an invalid Guid if the actor has no object binding in the sequence.
- L256 _protected prototype_ `void CleanExistingDataFromSequence(const FGuid& ForGuid, ULevelSequence& InSequence);` — Remove the Possessable data for the given Guid from the sequence. Calls CleanExistingDataFromSequenceImpl afterwards for any other cleanup you may wish to do.
- L259 _protected prototype_ `void PostProcessTrackRecorders(ULevelSequence* InSequence);` — Called as part of PostRecording before Track Recorders are finalized. Calls PostProcessTrackRecordersImpl afterwards for any other post processing you wish to do before Track recorders are finalized.
- L267 _protected prototype_ `bool EnsureObjectTemplateHasComponent(UActorComponent* InComponent, UActorComponent*& OutComponent);` — Ensure that the Object Template this recording is recording into has the specified component. Used to initialize dynamically added components that don't exist in the CDO. @param InComponent - The component on the object that we want to check to see if it's a new component. @param OutComponent - The newly duplicated component for the CDO (if any) @return True if the given component was duplicated and OutComponent is valid.
- L274 _protected prototype_ `void GetAllComponents(TSet<TWeakObjectPtr<UActorComponent>>& OutArray, bool bUpdateReferencedActorList = false);` — Gets all components (both Scene and Actor) on the recorded Actor. @param OutArray - Set of components to add found components to. @param bUpdateReferencedActorList - If true will add any external Actors referenced to the NewReferencedActors list, and possibly print warnings.
- L283 _protected prototype_ `void GetSceneComponents(USceneComponent* OnSceneComponent, TSet< TWeakObjectPtr<UActorComponent>>& OutArray, bool bUpdateReferencedActorList = false);` — Gets all Scene components that are a child of the specified component. Use the Root Component if you want all child components on an actor. @param OnSceneComponent - The component who's children we look at. @param OutArray - Set of components to add found components to. @param bUpdateReferencedActorList - If true will add any external Actors referenced to the NewReferencedActors list, and possibly print warnings.
- L288 _protected prototype_ `void GetChildSceneComponents(USceneComponent* OnSceneComponent, TSet< TWeakObjectPtr<UActorComponent>>& OutArray, bool bUpdateReferencedActorList = false);` — Returns the direct children of the specified scene component. Filters for ownership before returning.
- L293 _protected prototype_ `void GetActorComponents(AActor* OnActor, TSet< TWeakObjectPtr<UActorComponent>>& OutArray) const;` — Gets all Actor components on the recorded actor, not including Scene components.
- L300 _protected prototype_ `void CreateNewActorSourceForReferencedActors();` — Iterates through the NewReferencedActors set and creates a new UTakeRecorderActorSource for each one. Only creates a new source if that actor is not already being recorded by another Actor Source, will not create an Actor source for the actor we currently target.
- L303 _protected prototype_ `void EnsureParentHierarchyIsReferenced();` — `UE_DEPRECATED(5.8, "Use the EnsureParentHierarchyIsReferenced that takes a ULevelSequence as an argument instead.")`
- L310 _protected prototype_ `void EnsureParentHierarchyIsReferenced(ULevelSequence* InLevelSequence);` — Walks the hierarchy of the Target actor and the given sequence to ensure all parents have been added to the NewReferencedActors set. This allows us to ensure that we can record transforms in local space as all parents will be recorded and we can rebuild the hierarchy through Attach Tracks in Sequencer.
- L314 _protected prototype_ `bool IsOtherActorBeingRecorded(AActor* OtherActor) const override;` — Returns true if the other actor is also being recorded by the owning UTakeRecorderSources. Useful for checking if we're recording something we own is attached to.
- L316 _protected prototype_ `FGuid GetRecordedActorGuid(class AActor* OtherActor) const override;` — Returns a valid guid if the other actor is also being recorded by the owning UTakeRecorderSources. Useful for knowing the guid of that Actor without knowing if it's a Possessable or a Spawnable.
- L318 _protected prototype_ `virtual ULevelSequence* GetLevelSequence(const AActor* OtherActor) override;` — Returns active level sequence for the given Actor
- L320 _protected prototype_ `virtual FMovieSceneSequenceID GetLevelSequenceID(class AActor* OtherActor) override;` — Returns id of the active level sequence for the given Actor
- L322 _protected prototype_ `FTrackRecorderSettings GetTrackRecorderSettings() const override;` — Returns generic track recorder settings
- L324 _protected prototype_ `FTransform GetRecordedActorAnimationInitialRootTransform(class AActor* OtherActor) const override;` — Returns offset that may get set when recording a skeletal mesh animation. Needed to correctly transform attached children
- L326 _protected function_ `ULevelSequence* GetRootLevelSequence() const override` — Returns the root level sequence being recorded into
- L330 _protected prototype_ `void InitializeFactorySettingsObject(TSubclassOf<UMovieSceneTrackRecorderSettings> InClass);` — Initializes an instance of the specified class if we don't already have it in our Settings array.
- L332 _protected prototype_ `UMovieSceneTrackRecorderSettings* GetSettingsObjectForFactory(TSubclassOf<UMovieSceneTrackRecorderSettings> InClass) const;` — Gets the already initialized instance of the specified class from the Settings array.
- L335 _protected prototype_ `virtual void PostProcessCreatedObjectTemplateImpl(AActor* ObjectTemplate);` — This is called after a Spawnable object template is created. Use this to modify any settings on the template object that need to be changed (ie: disabling auto-possession of pawns).
- L336 _protected function_ `virtual void CleanExistingDataFromSequenceImpl(const FGuid& ForGuid, ULevelSequence& InSequence)`
- L337 _protected function_ `virtual void PostProcessTrackRecordersImpl()`
- L342 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L343 _public prototype_ `virtual void PostEditUndo() override;`
- L346 _public prototype_ `virtual void PostLoad() override;`
- L347 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L348 _public prototype_ `virtual void PostInitProperties() override;`
- L349 _public prototype_ `virtual void BeginDestroy() override;`
- L354 _private prototype_ `void CleanupAttachedDelegates();` — Cleanup any attached delegates this source is connected to.
- L358 _private member_ `TWeakObjectPtr<AActor> WeakAttachParent;` — Weak pointer to the current attach parent.
- L361 _private prototype_ `void HandleActorAttached(AActor* InChild, const AActor* InParent);` — Functions for handling when actors are attached or detatched in the level.
- L362 _private prototype_ `void HandleActorDetached(AActor* InChild, const AActor* InParent);`
- L365 _private prototype_ `ETakeRecorderAttachRecordBehaviour ResolveAttachRecordBehaviour() const;`
- L366 _private prototype_ `ETakeRecorderSpawnableOverwriteBehavior ResolveSpawnableOverwriteBehaviour() const;`
- L367 _private prototype_ `ETakeRecorderActorRecordType ResolveRecordType() const;`
- L369 _private prototype_ `bool CheckIfBindingCanBeReused(const UE::TakesCore::FActorSequenceInformation& SequenceInfo) const;`
- L371 _private prototype_ `virtual const FSlateBrush* GetDisplayIconImpl() const override;`
- L372 _private prototype_ `virtual FText GetCategoryTextImpl() const;`
- L373 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L374 _private prototype_ `virtual FText GetDescriptionTextImpl() const override;`
- L375 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L377 _private prototype_ `void ProcessRecordedTimes(ULevelSequence* InSequence);`
- L380 _private prototype_ `UMovieSceneAnimationTrackRecorderEditorSettings* GetBestTrackRecorderEditorSettings() const;` — Return either instance or global animation track recorder editor settings.
- L383 _private prototype_ `void DoCreatePendingTrackRecorders();` — Create all pending TrackRecorders.
- L386 _private prototype_ `void TryRecoverTarget(const ULevelSequence* InSequenceToSkip = nullptr, const ULevelSequence* InRootSequenceToSkip = nullptr);` — Attempt to recover the target actor with most current actor. Generally used to repair sequencer spawnable targets.
- L389 _private prototype_ `bool TickRecovery(float DeltaTime);` — Ticker callback: calls TryRecoverTarget while Target is invalid and CachedActorLabel is set.
- L392 _private member_ `FTSTicker::FDelegateHandle RecoveryTickerHandle;` — Ticker handle for the editor-only per-tick recovery check. Active while this source is alive.
- L396 _private member_ `FGuid CachedObjectBindingGuid;` — Object Binding guid that is created in the Level Sequence when recording starts.
- L399 _private member_ `TSet<AActor*> NewReferencedActors;` — Array of actors that have some sort of referenced link to our actor (such as an object attached to our hierarchy) that need Actor Source recorders initialized for them. List is emptied after sources are created.
- L401 _private member_ `TArray<UTakeRecorderSource*> AddedActorSources;` — Array of Actor Sources that we ended up creating that we need to clean up when we stop recording.
- L407 _private member_ `TWeakObjectPtr<AActor> CachedObjectTemplate;` — A pointer to the Object Template instance that was created inside the Target Level Sequence at the start of recording. Can be null (if recording to a possessable) or when we are not recording.
- L413 _private member_ `TSet<TWeakObjectPtr<UActorComponent>> CachedComponentList;` — A set of components that we're currently recording. We compare the components from one frame to the next to see if any components have been added or removed so we can appropriately update their Spawn tracked. Empty unless a recording is in progress (but may still be empty if no components)
- L418 _private member_ `FMovieSceneSequenceID TargetSequenceID;` — ID of the TargetLevelSequence.
- L423 _private member_ `FActorSerializer ActorSerializer;` — Serializer
- L435 _private member_ `TArray<FCreateTrackArgs> PendingTrackRecorders;` — TrackRecorders we need to create after PreRecord has completed for all sources.
- L438 _private member_ `bool bIsTemporarySource = false;` — If this actor source should be considered temporary, and removed later.
- L446 _private member_ `bool bTargetIsSequencerActor = false;` — `UPROPERTY()` — True when this source's target is a Sequencer-managed actor (spawnable or possessable with the SequencerActor tag). Set in SetSourceActor and PreRecording. Serialized so recording copies and sources loaded from a take retain the flag.
- L452 _private member_ `bool bRemovedSpawnTrack = false;` — True when we removed the spawn track from a Take Recorder-created spawnable to prevent a duplicate actor during recording. The track is re-added in FinalizeRecording.
- L461 _private member_ `FString CachedActorLabel;` — `UPROPERTY()` — Cached actor label from when Target was last set. Used to recover the target when the soft pointer becomes invalid. Primarily for when the actor was a Sequencer spawnable instance that was replaced by a new instance after the recording sequence was opened. Actor label matching is a known fragile approach; this is planned to be replaced with a more robust solution in a future pass.
- L467 _private member_ `TWeakObjectPtr<UTakeRecorderActorSource> WeakOriginalSource;` — Weak pointer to the original (pre-recording) source object. Recording operates on a DuplicateObject copy of each source; this lets FinalizeRecording update the original's Target after recording ends.

#### struct `UTakeRecorderActorSource::FCreateTrackArgs`  
`struct FCreateTrackArgs`  
_L426-432_
- desc: Args for calling CreateTrack on TrackRecorders.
- L428 _public member_ `TWeakObjectPtr<UMovieSceneTrackRecorder> TrackRecorder;`
- L429 _public member_ `TWeakObjectPtr<UObject> ObjectToRecord;`
- L430 _public member_ `TWeakObjectPtr<UMovieSceneTrackRecorderSettings> FactorySettings;`
- L431 _public member_ `FGuid ObjectGuid;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API TAKERECORDERSOURCES_API`
- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(ActorSerialization, Verbose, All);`
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(ActorSerialization, Verbose, All);`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace TakesCore` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderCameraCutSource.h` (Public)


#### class `UTakeRecorderCameraCutSource`  
`class UTakeRecorderCameraCutSource : public UTakeRecorderSource`  
_L20-64_
- reflection: `UCLASS(MinimalAPI, Category="Other")`
- inherits: `UTakeRecorderSource`
- desc: A recording source that detects camera switching and creates a camera cut track
- L25 _public prototype_ `UTakeRecorderCameraCutSource(const FObjectInitializer& ObjInit);`
- L30 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;` — UTakeRecorderSource
- L31 _private prototype_ `virtual void TickRecording(const FQualifiedFrameTime& CurrentTime) override;`
- L32 _private prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, class ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L33 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L34 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L36 _private function_ `virtual bool SupportsSubscenes() const override` — This source does not support subscenes
- L41 _private member_ `TObjectPtr<UWorld> World;` — `UPROPERTY()`
- L45 _private member_ `TObjectPtr<ULevelSequence> RootLevelSequence;` — `UPROPERTY()` — The root or uppermost level sequence that this source is being recorded into. Set during PreRecording, null after PostRecording.
- L60 _private member_ `TArray<FCameraCutData> CameraCutData;`
- L63 _private member_ `TArray<TWeakObjectPtr<UTakeRecorderActorSource> > NewActorSources;` — Spawned actor sources to be removed at the end of recording

#### struct `UTakeRecorderCameraCutSource::FCameraCutData`  
`struct FCameraCutData`  
_L48-58_
- L50 _public function_ `FCameraCutData(FGuid InGuid, FMovieSceneSequenceID InSequenceID, FQualifiedFrameTime InTime) : Guid(InGuid) , SequenceID(InSequenceID) , Time(InTime)`
- L55 _public member_ `FGuid Guid;`
- L56 _public member_ `FMovieSceneSequenceID SequenceID;`
- L57 _public member_ `FQualifiedFrameTime Time;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TAKERECORDERSOURCES_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderLevelSequenceSource.h` (Public)


#### class `UTakeRecorderLevelSequenceSource`  
`class UTakeRecorderLevelSequenceSource : public UTakeRecorderSource`  
_L17-42_
- reflection: `UCLASS(MinimalAPI,Category="Other")`
- inherits: `UTakeRecorderSource`
- desc: Plays level sequence actors when recording starts
- L22 _public prototype_ `UTakeRecorderLevelSequenceSource(const FObjectInitializer& ObjInit);`
- L25 _public member_ `TArray<TObjectPtr<ULevelSequence>> LevelSequencesToTrigger;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source")`
- L30 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;` — UTakeRecorderSource
- L31 _private prototype_ `virtual void StartRecording(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame, class ULevelSequence* InSequence) override;`
- L32 _private prototype_ `virtual void StopRecording(class ULevelSequence* InSequence) override;`
- L33 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L34 _private prototype_ `virtual FText GetDescriptionTextImpl() const override;`
- L35 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L38 _private function_ `virtual bool SupportsSubscenes() const override` — This source does not support subscenes since it's a playback source instead of a recording
- L41 _private member_ `TArray<TWeakObjectPtr<ALevelSequenceActor>> ActorsToTrigger;` — Transient level sequence actors to trigger, to be stopped and reset at the end of recording

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TAKERECORDERSOURCES_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderLevelVisibilitySource.h` (Public)


#### class `UTakeRecorderLevelVisibilitySourceSettings`  
`class UTakeRecorderLevelVisibilitySourceSettings : public UTakeRecorderSource`  
_L14-33_
- reflection: `UCLASS(MinimalAPI, Abstract, config = EditorSettings, DisplayName = "Level Visibility Recorder Defaults")`
- inherits: `UTakeRecorderSource`
- desc: A recording source that records level visibilitiy
- L19 _public prototype_ `UTakeRecorderLevelVisibilitySourceSettings(const FObjectInitializer& ObjInit);`
- L22 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L26 _public prototype_ `virtual FString GetSubsceneTrackName(ULevelSequence* InSequence) const override;` — UTakeRecorderSource Interface
- L27 _public prototype_ `virtual FString GetSubsceneAssetName(ULevelSequence* InSequence) const override;`
- L32 _public member_ `FText LevelVisibilityTrackName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source")` — Name of the recorded level visibility track name

#### class `UTakeRecorderLevelVisibilitySource`  
`class UTakeRecorderLevelVisibilitySource : public UTakeRecorderLevelVisibilitySourceSettings`  
_L37-56_
- reflection: `UCLASS(MinimalAPI, Category="Other", config = EditorSettings)`
- inherits: `UTakeRecorderLevelVisibilitySourceSettings`
- desc: A recording source that records level visibility state
- L42 _public prototype_ `UTakeRecorderLevelVisibilitySource(const FObjectInitializer& ObjInit);`
- L47 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;` — UTakeRecorderSource
- L48 _private prototype_ `virtual void TickRecording(const FQualifiedFrameTime& CurrentTime) override;`
- L49 _private prototype_ `virtual void AddContentsToFolder(class UMovieSceneFolder* InFolder) override;`
- L50 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L51 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L52 _private prototype_ `virtual bool CanAddSource(UTakeRecorderSources* InSources) const override;`
- L55 _private member_ `TWeakObjectPtr<class UMovieSceneLevelVisibilityTrack> CachedLevelVisibilityTrack;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TAKERECORDERSOURCES_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderMicrophoneAudioManager.h` (Public)


#### class `UTakeRecorderMicrophoneAudioManager`  
`class UTakeRecorderMicrophoneAudioManager : public UTakeRecorderAudioInputSettings`  
_L28-114_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, PerObjectConfig, DisplayName = "Audio Input Device")`
- inherits: `UTakeRecorderAudioInputSettings`
- desc: This class exposes the audio input device list via the project settings details. It does this in conjunction with FAudioInputDevicePropertyCustomization. It also manages the IAudioCaptureEditor object which handles the low level audio device recording.
- L33 _public prototype_ `UTakeRecorderMicrophoneAudioManager(const FObjectInitializer& ObjInit);`
- L37 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _public prototype_ `virtual void EnumerateAudioDevices(bool InForceRefresh = false) override;` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder|Microphone Audio")` — Enumerates the audio devices present on the current machine
- L47 _public prototype_ `virtual int32 GetDeviceChannelCount() override;` — `UFUNCTION(BlueprintPure, Category = "Take Recorder|Microphone Audio")` — Returns input channel count for currently selected audio device
- L52 _public member_ `FAudioInputDeviceProperty AudioInputDevice;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetAudioInputDevice, BlueprintSetter = SetAudioInputDevice, Category = "Take Recorder|Microphone Audio", meta = (ShowOnlyInnerProperties))` — The audio device to use for this microphone source
- L56 _public prototype_ `FAudioInputDeviceProperty GetAudioInputDevice() const;` — `UFUNCTION(BlueprintPure, Category = "Take Recorder|Microphone Audio")` — Returns the currently configured audio input device settings (device id, buffer size, default-device flag, cached device list).
- L64 _public prototype_ `void SetAudioInputDevice(const FAudioInputDeviceProperty& InAudioInputDevice);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder|Microphone Audio")` — Sets the audio input device settings and notifies dependents — broadcasts OnNotifySourcesOfDeviceChange (so every microphone source re-evaluates its channel) and OnAudioInputDeviceChanged (so UI customizations refresh). Saves config when invoked on the CDO (the canonical instance returned by GetMutableDefault<>).
- L70 _public prototype_ `void StartRecording(int32 InChannelCount);` — Calls StartRecording on the AudioRecorder object. This is called multiple times (once for each microphone source, however, only the first call triggers the call to AudioRecorder.
- L75 _public prototype_ `void StopRecording();` — Calls StopRecording on the AudioRecorder object. This is called multiple times (once for each microphone source, however, only the first call triggers the call to AudioRecorder.
- L80 _public prototype_ `void FinalizeRecording();` — Calls FinalizeRecording on the AudioRecorder object. This is called multiple times (once for each microphone source, however, only the first call triggers the call to AudioRecorder.
- L84 _public prototype_ `TObjectPtr<class USoundWave> GetRecordedSoundWave(const FTakeRecorderAudioSourceSettings& InSourceSettings);` — Fetches the USoundWave for this source after a Take has been recorded
- L88 _public function_ `FOnNotifySourcesOfDeviceChange& GetOnNotifySourcesOfDeviceChange()` — Accessor for the OnNotifySourcesOfDeviceChange delegate list
- L92 _public member_ `FOnAudioInputDevicePropertyChanged OnAudioInputDevicePropertyChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Take Recorder|Microphone Audio")` — Fires after AudioInputDevice is modified — via editor edit or SetAudioInputDevice.
- L97 _private member_ `FOnNotifySourcesOfDeviceChange OnNotifySourcesOfDeviceChange;` — Multicast delegate which notifies clients when the currently selected audio device changes.
- L101 _private prototype_ `TUniquePtr<IAudioCaptureEditor> CreateAudioRecorderObject();` — Calls factory to create the AudioRecorder object
- L105 _private prototype_ `void BuildDeviceInfoArray();` — Builds the list of audio devices which will be used in the device menu
- L108 _private prototype_ `bool IsAudioDeviceAvailable(const FString& InDeviceId);` — Returns whether audio device with given Id was found during enumeration
- L112 _private member_ `TUniquePtr<IAudioCaptureEditor> AudioRecorder;` — The audio recorder object which manages low level recording of audio data

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TAKERECORDERSOURCES_API`
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifySourcesOfDeviceChange, int);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifySourcesOfDeviceChange, int);`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioInputDevicePropertyChanged, const FAudioInputDeviceProperty&, InAudioInputDevice);`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioInputDevicePropertyChanged, const FAudioInputDeviceProperty&, InAudioInputDevice);`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderMicrophoneAudioSource.h` (Public)


#### class `UTakeRecorderMicrophoneAudioSourceSettings`  
`class UTakeRecorderMicrophoneAudioSourceSettings : public UTakeRecorderSource`  
_L24-75_
- reflection: `UCLASS(MinimalAPI, Abstract, config=EditorSettings, DisplayName="Microphone Audio Recorder")`
- inherits: `UTakeRecorderSource`
- desc: A recording source that records microphone audio
- L29 _public prototype_ `UTakeRecorderMicrophoneAudioSourceSettings(const FObjectInitializer& ObjInit);`
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _public prototype_ `virtual FString GetSubsceneTrackName(ULevelSequence* InSequence) const override;` — UTakeRecorderSource Interface
- L37 _public prototype_ `virtual FString GetSubsceneAssetName(ULevelSequence* InSequence) const override;`
- L42 _public member_ `FText AudioSourceName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source")` — Name of the audio source
- L46 _public member_ `FText AudioTrackName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source", meta = (NamingTokens))` — Name of the recorded audio track
- L60 _public member_ `FString AudioAssetName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source", meta = (NamingTokens))` — The name of the audio asset. Supports any of the following format specifiers that will be substituted when a take is recorded : {day} - The day of the timestamp for the start of the recording. {month} - The month of the timestamp for the start of the recording. {year} - The year of the timestamp for the start of the recording. {hour} - The hour of the timestamp for the start of the recording. {minute} - The minute of the timestamp for the start of the recording. {second} - The second of the timestamp for the start of the recording. {take} - The take number. {slate} - The slate string.
- L74 _public member_ `FString AudioSubDirectory;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source", meta = (NamingTokens))` — The name of the subdirectory audio will be placed in. Leave this empty to place into the same directory as the sequence base path Supports any of the following format specifiers that will be substituted when a take is recorded : {day} - The day of the timestamp for the start of the recording. {month} - The month of the timestamp for the start of the recording. {year} - The year of the timestamp for the start of the recording. {hour} - The hour of the timestamp for the start of the recording. {minute} - The minute of the timestamp for the start of the recording. {second} - The second of the timestamp for the start of the recording. {take} - The take number. {slate} - The slate string.

#### class `UTakeRecorderMicrophoneAudioSource`  
`class UTakeRecorderMicrophoneAudioSource : public UTakeRecorderMicrophoneAudioSourceSettings`  
_L79-182_
- reflection: `UCLASS(MinimalAPI, Category="Audio", config=EditorSettings)`
- inherits: `UTakeRecorderMicrophoneAudioSourceSettings`
- desc: A recording source that records microphone audio
- L84 _public prototype_ `UTakeRecorderMicrophoneAudioSource(const FObjectInitializer& ObjInit);`
- L88 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L94 _public member_ `float AudioGain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "20.0", ClampMax = "40.0"))` — Gain in decibels to apply to recorded audio
- L99 _public member_ `bool bSplitAudioChannelsIntoSeparateTracks_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "SplitAudioChannelsIntoSeparateTracks is deprecated."))`
- L104 _public member_ `bool bReplaceRecordedAudio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source")` — Replace existing recorded audio with any newly recorded audio
- L108 _public member_ `FAudioInputDeviceChannelProperty AudioChannel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source", meta = (ShowOnlyInnerProperties))` — The audio device to use for this microphone source
- L111 _public prototype_ `virtual void Initialize() override;` — UTakeRecorderSource
- L112 _public prototype_ `virtual FString GetSubsceneTrackName(ULevelSequence* InSequence) const override;`
- L113 _public prototype_ `virtual FString GetSubsceneAssetName(ULevelSequence* InSequence) const override;`
- L114 _public prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;`
- L115 _public prototype_ `virtual void StartRecording(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame, class ULevelSequence* InSequence) override;`
- L116 _public prototype_ `virtual void TickRecording(const FQualifiedFrameTime& CurrentTime) override;`
- L117 _public prototype_ `virtual void StopRecording(class ULevelSequence* InSequence) override;`
- L118 _public prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(ULevelSequence* InSequence, class ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L119 _public prototype_ `virtual void FinalizeRecording() override;`
- L120 _public prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L121 _public prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L123 _public prototype_ `virtual void AddContentsToFolder(class UMovieSceneFolder* InFolder) override;`
- L124 _public prototype_ `virtual bool CanAddSource(UTakeRecorderSources* InSources) const override;`
- L128 _public prototype_ `FString GetAudioTrackName(ULevelSequence* InSequence) const;` — Returns track display name, replacing any tokens if needed
- L130 _public prototype_ `FString GetAudioAssetName(ULevelSequence* InSequence) const;` — Returns the fully expanded asset name
- L133 _public prototype_ `void SetAudioDeviceChannelCount(int32 InChannelCount);` — Sets the channel count supported by the currently selected audio device.
- L135 _public prototype_ `void OnNotifySourcesOfDeviceChange(int32 InChannelCount);` — Delegate which receives notifications when the audio input device changes.
- L140 _private prototype_ `static UTakeRecorderMicrophoneAudioManager* GetAudioInputManager();` — Helper function for getting a pointer to the AudioInputManger object.
- L143 _private prototype_ `void ProcessRecordedTimes(ULevelSequence* InSequence);` — Parses recorded timecode values
- L146 _private prototype_ `TUniquePtr<TArray<bool>> GetChannelsInUse(const int32 InDeviceChannelCount);` — Returns an array of booleans indicating which channel indexes are currently in use
- L148 _private prototype_ `void GetRecordedSoundWave(ULevelSequence* InSequence);` — Fetches the USoundWave for this source after a Take has been recorded
- L150 _private prototype_ `void SetCurrentInputChannel(int32 InChannelNumber);` — Called when the user selects a new channel in the combobox for this source
- L153 _private prototype_ `bool IsTrackAssociatedWithAnySource(UMovieSceneAudioTrack* InAudioTrack);` — Returns whether given track is being used by any other source
- L156 _private prototype_ `FString GetUniqueAudioAssetName(ULevelSequence* InSequence) const;` — Build asset name, appending channel name if needed for uniqueness
- L159 _private prototype_ `static FString CreateUniqueAudioAssetName(ULevelSequence* InSequence, UTakeRecorderSources* InSources, const FString& InAssetName, const int32 InChannelNumber);` — Static, parameterized helper function for buidling unique asset names
- L162 _private prototype_ `bool TryEvaluateTokenString(const FString& InString, const ULevelSequence* InSequence, FString& OutString) const;` — Evaluate our tokens and automatically create an appropriate context.
- L165 _private prototype_ `void DoAudioSetup();`
- L168 _private member_ `TWeakObjectPtr<class UMovieSceneAudioTrack> CachedAudioTrack;` — Holds the Sequencer audio track for this source
- L171 _private member_ `TWeakObjectPtr<USoundWave> RecordedSoundWave;` — Holds the USoundWave asset for a given take
- L173 _private member_ `FTimecode StartTimecode;` — Caches the starting timecode for this take so it can be referenced when creating USoundWave assets
- L176 _private member_ `FDirectoryPath AudioDirectory;` — The user specified directory to store recorded audio assets in
- L178 _private member_ `FString AssetFileName;` — The name of the UsoundWave asset
- L181 _private member_ `bool bHaveDoneAudioSetup = false;` — Have we initialized our source.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TAKERECORDERSOURCES_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderNearbySpawnedActorSource.h` (Public)


#### class `UTakeRecorderNearbySpawnedActorSource`  
`class UTakeRecorderNearbySpawnedActorSource : public UTakeRecorderSource`  
_L18-61_
- reflection: `UCLASS(MinimalAPI, Category="Actors")`
- inherits: `UTakeRecorderSource`
- desc: A recording source that detects actors spawned close to the current camera, and captures them as spawnables
- L23 _public prototype_ `UTakeRecorderNearbySpawnedActorSource(const FObjectInitializer& ObjInit);`
- L27 _public member_ `float Proximity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Spawn Proximity", Category="Source", meta=(units=cm))` — The proximity to the current camera that an actor must be spawned in order to be recorded as a spawnable. If 0, proximity is disregarded.
- L31 _public member_ `bool bFilterSpawnedActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Source")` — Should we only record actors that pass the filter list?
- L35 _public member_ `TArray<TSubclassOf<AActor> > FilterTypes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Source", meta=(EditCondition="bFilterSpawnedActors"))` — A type filter to apply to spawned objects
- L40 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;` — UTakeRecorderSource
- L41 _private prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, class ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L42 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L43 _private prototype_ `virtual FText GetDescriptionTextImpl() const override;`
- L44 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L46 _private function_ `virtual bool SupportsSubscenes() const override` — This source does not support subscenes (ie. "NearbySpawnedActors subscene"), but each of the spawned actors would be placed in subscenes if the option is enabled
- L49 _private prototype_ `void HandleActorSpawned(AActor* Actor, class ULevelSequence* InSequence);` — Handle actors being spawned
- L52 _private prototype_ `bool IsActorValid(AActor* Actor);` — Is this actor valid for recording? Is it close enough? Is it a filtered type?
- L57 _private member_ `TMap<TWeakObjectPtr<UWorld>, FDelegateHandle> ActorSpawningDelegateHandles;` — Delegate handles for FOnActorSpawned events
- L60 _private member_ `TArray<TWeakObjectPtr<UTakeRecorderActorSource> > SpawnedActorSources;` — Spawned actor sources to be removed at the end of recording

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API TAKERECORDERSOURCES_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderPlayerSource.h` (Public)


#### class `UTakeRecorderPlayerSource`  
`class UTakeRecorderPlayerSource : public UTakeRecorderSource`  
_L16-36_
- reflection: `UCLASS(MinimalAPI, Category="Actors")`
- inherits: `UTakeRecorderSource`
- desc: A recording source that records the current player
- L21 _public prototype_ `UTakeRecorderPlayerSource(const FObjectInitializer& ObjInit);`
- L26 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;` — UTakeRecorderSource
- L27 _private prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, class ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L28 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L29 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L30 _private prototype_ `virtual bool CanAddSource(UTakeRecorderSources* InSources) const override;`
- L33 _private function_ `virtual bool SupportsSubscenes() const override` — This source does not support subscenes (ie. "Player subscene"), but the player would be placed in subscenes if the option is enabled
- L35 _private member_ `TWeakObjectPtr<UTakeRecorderActorSource> PlayerActorSource;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TAKERECORDERSOURCES_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderSourceHelpers.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace TakeRecorderSourceHelpers`
- L24 _prototype_ `void AddActorSources( UTakeRecorderSources* TakeRecorderSources, TArrayView<AActor* const> ActorsToRecord, bool bReduceKeys = true, bool bShowProgress = true);` (scope `TakeRecorderSourceHelpers`) — Adds a number of actors to the set of sources to record from. @param TakeRecorderSources The list of sources used for the current take. @param ActorsToRecord The list of Actors that should be added to Sources. Note that this can include ALevelSequenceActors. @param bReduceKeys Enable/disable key reduction on all the sources registered @param bShowProgress Enable/disable the dialog box showing progress for the potentially slow parts of finalizing the take
- L35 _prototype_ `void RemoveActorSources(UTakeRecorderSources* TakeRecorderSources, TArrayView<AActor* const> ActorsToRemove);` (scope `TakeRecorderSourceHelpers`) — Remove specific actors as a source. @param TakeRecorderSources The list of sources used for the current take. @param ActorsToRemove The list of Actors to be removed from Sources.
- L40 _prototype_ `void RemoveAllActorSources(UTakeRecorderSources* Sources);` (scope `TakeRecorderSourceHelpers`) — Removes all sources from a list of sources to record from.
- L47 _prototype_ `AActor* GetSourceActor(UTakeRecorderSource* Source);` (scope `TakeRecorderSourceHelpers`) — Retrieve the source actor if applicable. @param Source The source to check. @return The source actor, if one is set.
- L49 _typedef_ `using FArrayOfRecordedTimePairs = const TArray<TPair<FQualifiedFrameTime, FQualifiedFrameTime>>;` (scope `TakeRecorderSourceHelpers`)
- L55 _prototype_ `void ProcessRecordedTimes(ULevelSequence* InSequence, UMovieSceneTakeTrack* TakeTrack, const TOptional<TRange<FFrameNumber>>& FrameRange, const FArrayOfRecordedTimePairs& RecordedTimes);` (scope `TakeRecorderSourceHelpers`) — `UE_DEPRECATED(5.7, "Use UE::TakeCores::ProcessRecordedTimes instead.")` — Creates a takes track to store timecode data on a take recorder source.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderWorldSource.h` (Public)


#### class `UTakeRecorderWorldSourceSettings`  
`class UTakeRecorderWorldSourceSettings : public UTakeRecorderSource`  
_L19-45_
- reflection: `UCLASS(Abstract, MinimalAPI, config = EditorSettings, DisplayName = "World Recorder")`
- inherits: `UTakeRecorderSource`
- desc: A recording source that records world state
- L24 _public prototype_ `UTakeRecorderWorldSourceSettings(const FObjectInitializer& ObjInit);`
- L27 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public member_ `bool bRecordWorldSettings;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source")` — Record world settings
- L36 _public member_ `bool bAutotrackActors;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source")` — Add a binding and track for all actors that aren't explicitly being recorded
- L40 _public member_ `bool bAllowEditorOnlyActors;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source")` — When autotracking actors to add, allow recording of editor only actor objects.
- L44 _public member_ `bool bOnlyRecordMoveableActors;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Source")` — When autotracking actors to add, only record actors that have a root component and are moveable.

#### class `UTakeRecorderWorldSource`  
`class UTakeRecorderWorldSource : public UTakeRecorderWorldSourceSettings`  
_L50-84_
- reflection: `UCLASS(MinimalAPI, Category="Actors")`
- inherits: `UTakeRecorderWorldSourceSettings`
- desc: A recording source that records world state
- L55 _public prototype_ `UTakeRecorderWorldSource(const FObjectInitializer& ObjInit);`
- L60 _private prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer) override;` — UTakeRecorderSource
- L61 _private prototype_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, class ULevelSequence* InRootSequence, const bool bCancelled) override;`
- L62 _private function_ `virtual bool SupportsTakeNumber() const override`
- L63 _private prototype_ `virtual FText GetDisplayTextImpl() const override;`
- L64 _private prototype_ `virtual FText GetAddSourceDisplayTextImpl() const override;`
- L65 _private prototype_ `virtual bool CanAddSource(UTakeRecorderSources* InSources) const override;`
- L68 _private function_ `virtual bool SupportsSubscenes() const override` — This source does not support subscenes (ie. "World Settings subscene"), but the world settings actor would be placed in subscenes if the option is enabled
- L75 _private prototype_ `void AutotrackActors(class ULevelSequence* InSequence, UWorld* InWorld);` — Autotrack actors in the world that aren't already being recorded
- L80 _private prototype_ `bool CanRecordActor(AActor* Actor) const;` — If Autotracked actors is enabled this helper will determine if the actor can be recorded.
- L82 _private member_ `TWeakObjectPtr<UTakeRecorderActorSource> WorldSource;`
- L83 _private member_ `TSet<TWeakObjectPtr<UTakeRecorderActorSource>> AutotrackedSources;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TAKERECORDERSOURCES_API`
