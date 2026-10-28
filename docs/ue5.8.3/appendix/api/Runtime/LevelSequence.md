# Runtime / LevelSequence

- module root: `Source/Runtime/LevelSequence`
- headers: 19; symbols: 426
- symbol kinds: class=19, delegate=7, enum=4, enumerator=4, function=31, macro=3, member=116, prototype=226, struct=16
- PrivateDependencyModuleNames: ActorPickerMode, DeveloperSettings, EditorFramework, MediaAssets, PropertyEditor, UniversalObjectLocator, UnrealEd
- PrivateIncludePathModuleNames: SceneOutliner
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MovieScene, MovieSceneTracks, TimeManagement, UMG

### `Source/Runtime/LevelSequence/Private/LegacyLazyObjectPtrFragment.h` (Private)


#### struct `FLegacyLazyObjectPtrFragment`  
`struct FLegacyLazyObjectPtrFragment`  
_L14-39_
- reflection: `USTRUCT()`
- L19 _public member_ `FGuid LazyObjectId;` — `UPROPERTY()`
- L21 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FLegacyLazyObjectPtrFragment> FragmentType;`
- L33 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L34 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L35 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L36 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L38 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLegacyLazyObjectPtrFragment> : public TStructOpsTypeTraitsBase2<FLegacyLazyObjectPtrFragment>`  
_L42-48_
- inherits: `TStructOpsTypeTraitsBase2<FLegacyLazyObjectPtrFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L45-47_

#### Free symbols / members of external scopes

- L23 _function_ `friend uint32 GetTypeHash(const FLegacyLazyObjectPtrFragment& A)`
- L28 _function_ `friend bool operator==(const FLegacyLazyObjectPtrFragment& A, const FLegacyLazyObjectPtrFragment& B)`
- L46 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon2dfce37f0103`)

### `Source/Runtime/LevelSequence/Private/LevelSequenceModule.h` (Private)


#### class `FLevelSequenceModule`  
`class FLevelSequenceModule : public ILevelSequenceModule, public FSelfRegisteringExec`  
_L15-45_
- inherits: `ILevelSequenceModule,FSelfRegisteringExec`
- desc: Implements the LevelSequence module.
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `virtual FDelegateHandle RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner InOnCreateMovieSceneObjectSpawner) override;` — ILevelSequenceModule interface
- L25 _public prototype_ `virtual void GenerateObjectSpawners(TArray<TSharedRef<IMovieSceneObjectSpawner>>& OutSpawners) const override;`
- L26 _public prototype_ `virtual void UnregisterObjectSpawner(FDelegateHandle InHandle) override;`
- L27 _public prototype_ `virtual FOnNewActorTrackAdded& OnNewActorTrackAdded() override;`
- L31 _protected prototype_ `virtual bool Exec_Runtime(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec interface
- L35 _public member_ `TArray< FOnCreateMovieSceneObjectSpawner > OnCreateMovieSceneObjectSpawnerDelegates;` — List of object spawner delegates used to extend the spawn register
- L38 _public member_ `FDelegateHandle OnCreateMovieSceneObjectSpawnerDelegateHandle;` — Internal delegate handle used for spawning actors
- L43 _private member_ `TWeakObjectPtr<ULevelSequence> LevelSequenceCDO;` — Weak ptr to the level sequence CDO so we can gracefully remove the meta-data on shutdown module without crashing when ShutdownModule is called after the CDO has been destroyed.
- L44 _private member_ `FOnNewActorTrackAdded NewActorTrackAdded;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLevelSequence, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLevelSequence, Log, All);`

### `Source/Runtime/LevelSequence/Public/AnimSequenceLevelSequenceLink.h` (Public)


#### class `UAnimSequenceLevelSequenceLink`  
`class UAnimSequenceLevelSequenceLink : public UAssetUserData`  
_L11-26_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UAssetUserData`
- desc: Link To Level Sequence That may be driving the anim sequence
- L16 _public function_ `virtual bool IsEditorOnly() const override`
- L19 _public member_ `FGuid SkelTrackGuid;` — `UPROPERTY(BlueprintReadWrite, Category = Property)`
- L22 _public member_ `FSoftObjectPath PathToLevelSequence;` — `UPROPERTY(BlueprintReadWrite, AssetRegistrySearchable, Category = Property)`
- L24 _public prototype_ `void SetLevelSequence(ULevelSequence* InLevelSequence);`
- L25 _public prototype_ `ULevelSequence* ResolveLevelSequence();`

### `Source/Runtime/LevelSequence/Public/DefaultLevelSequenceInstanceData.h` (Public)


#### class `UDefaultLevelSequenceInstanceData`  
`class UDefaultLevelSequenceInstanceData : public UObject , public IMovieSceneTransformOrigin`  
_L16-48_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject,IMovieSceneTransformOrigin`
- desc: Default instance data class that level sequences understand. Implements IMovieSceneTransformOrigin.
- L24 _public function_ `UDefaultLevelSequenceInstanceData(const FObjectInitializer& Init) : Super(Init)`
- L31 _public function_ `virtual FTransform NativeGetTransformOrigin() const override`
- L35 _public member_ `TObjectPtr<AActor> TransformOriginActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="General")` — When set, this actor's world position will be used as the transform origin for all absolute transform sections
- L39 _public member_ `FTransform TransformOrigin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="General")` — Specifies a transform that offsets all absolute transform sections in this sequence. Scale is ignored. Not applied to Relative or Additive sections.
- L42 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FTransformOriginChanged);`
- L43 _public member_ `FTransformOriginChanged TransformOriginChangedEvent;`
- L46 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LEVELSEQUENCE_API`
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE(FTransformOriginChanged);`

### `Source/Runtime/LevelSequence/Public/ILevelSequenceModule.h` (Public)


#### class `ILevelSequenceModule`  
`class ILevelSequenceModule : public IModuleInterface`  
_L12-28_
- inherits: `IModuleInterface`
- desc: Implements the LevelSequence module.
- L17 _public prototype_ `virtual FDelegateHandle RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner InOnCreateMovieSceneObjectSpawner) = 0;` — Register an object spawner
- L20 _public prototype_ `virtual void GenerateObjectSpawners(TArray<TSharedRef<IMovieSceneObjectSpawner>>& OutSpawners) const = 0;` — Populate the specified array with new object spawner instances for all registered object spawner types
- L23 _public prototype_ `virtual void UnregisterObjectSpawner(FDelegateHandle InHandle) = 0;` — Unregister an object spawner
- L25 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnNewActorTrackAdded, const AActor& , const FGuid& , TSharedPtr<ISequencer> );`
- L27 _public prototype_ `virtual FOnNewActorTrackAdded& OnNewActorTrackAdded() = 0;` — Callback to set up defaults for new actor tracks

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnNewActorTrackAdded, const AActor& , const FGuid& , TSharedPtr<ISequencer> );`

### `Source/Runtime/LevelSequence/Public/LevelSequence.h` (Public)


#### class `ULevelSequence`  
`class ULevelSequence : public UMovieSceneSequence, public IInterface_AssetUserData`  
_L23-316_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMovieSceneSequence,IInterface_AssetUserData`
- desc: Movie scene animation for Actors.
- L32 _public member_ `TObjectPtr<UMovieScene> MovieScene;` — `UPROPERTY()` — Pointer to the movie scene that controls this animation.
- L37 _public prototype_ `virtual void Initialize();` — Initialize this level sequence.
- L42 _public prototype_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;` — UMovieSceneSequence interface
- L43 _public prototype_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;`
- L46 _public prototype_ `virtual FGuid FindBindingFromObject(UObject* InObject, UObject* Context) const override;` — `UE_DEPRECATED(5.5, "Use the version that takes a SharedPlaybackState")`
- L47 _public prototype_ `virtual FGuid FindBindingFromObject(UObject* InObject, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) const override;`
- L49 _public prototype_ `virtual void GatherExpiredObjects(const FMovieSceneObjectCache& InObjectCache, TArray<FGuid>& OutInvalidIDs) const override;`
- L50 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L51 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L52 _public prototype_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;`
- L53 _public prototype_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* InContext) override;`
- L54 _public prototype_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* InContext) override;`
- L55 _public prototype_ `virtual bool AllowsSpawnableObjects() const override;`
- L56 _public prototype_ `virtual bool AllowsCustomBindings() const override;`
- L57 _public prototype_ `virtual bool CanRebindPossessable(const FMovieScenePossessable& InPossessable) const override;`
- L58 _public prototype_ `virtual UObject* MakeSpawnableTemplateFromInstance(UObject& InSourceObject, FName ObjectName) override;`
- L59 _public prototype_ `virtual bool CanAnimateObject(UObject& InObject) const override;`
- L60 _public prototype_ `virtual UObject* CreateDirectorInstance(TSharedRef<const FSharedPlaybackState> SharedPlaybackState, FMovieSceneSequenceID SequenceID) override;`
- L61 _public prototype_ `virtual const FMovieSceneBindingReferences* GetBindingReferences() const override;`
- L62 _public prototype_ `virtual void PostLoad() override;`
- L64 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L67 _public prototype_ `virtual void PostInitProperties() override;`
- L68 _public prototype_ `virtual bool Rename(const TCHAR* NewName = nullptr, UObject* NewOuter = nullptr, ERenameFlags Flags = REN_None) override;`
- L72 _public prototype_ `virtual void AddAssetUserData(UAssetUserData* InUserData) override;`
- L73 _public prototype_ `virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L74 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L75 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L80 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L81 _public prototype_ `virtual bool IsFilterSupportedImpl(const FString& InFilterName) const override;`
- L82 _public prototype_ `virtual void GetAssetRegistryTagMetadata(TMap<FName, FAssetRegistryTagMetadata>& OutMetadata) const override;`
- L83 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L85 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L87 _protected prototype_ `virtual void ThreadedPostLoadAssetRegistryTagsOverride(FPostLoadAssetRegistryTagsContext& Context) const override;`
- L90 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(void, FPostDuplicateEvent, ULevelSequence*);`
- L91 _public member_ `static FPostDuplicateEvent PostDuplicateEvent;`
- L93 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FFixupDynamicBindingsEvent, ULevelSequence*);`
- L94 _public member_ `static FFixupDynamicBindingsEvent FixupDynamicBindingsEvent;`
- L99 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L104 _public prototype_ `void LocateBoundObjects(const FGuid& ObjectId, UObject* Context, const FLevelSequenceBindingReference::FResolveBindingParams& InResolveBindingParams, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const;` — `UE_DEPRECATED(5.4, "Use the base class LocateBoundObjects()")`
- L109 _public prototype_ `virtual void IterateDynamicBindings(TFunction<void(const FGuid&, FMovieSceneDynamicBinding&)> InCallback) override;`
- L115 _public prototype_ `void SetDirectorBlueprint(UBlueprint* NewDirectorBlueprint);` — Assign a new director blueprint to this level sequence. The specified blueprint *must* be contained within this object.?
- L120 _public prototype_ `UBlueprint* GetDirectorBlueprint() const;` — Retrieve the currently assigned director blueprint for this level sequence
- L122 _public prototype_ `FString GetDirectorBlueprintName() const;`
- L126 _protected prototype_ `virtual FGuid CreatePossessable(UObject* ObjectToPossess) override;`
- L127 _protected prototype_ `virtual FGuid CreateSpawnable(UObject* ObjectToSpawn) override;`
- L129 _protected prototype_ `FGuid FindOrAddBinding(UObject* ObjectToPossess);`
- L134 _protected prototype_ `void OnDirectorRecompiled(UBlueprint*);` — Invoked when this level sequence's director blueprint has been recompiled
- L139 _private prototype_ `bool ConvertOldSpawnables();` — Used to convert any old spawnables in this movie scene to use the custom binding system
- L141 _private prototype_ `void ConvertDynamicBindingPossessable(FMovieScenePossessable& Possessable);` — Used to convert possessables using deprecated 'DynamicBinding' to a custom director blueprint binding
- L142 _private prototype_ `void OnEndLoadPackage(const FEndLoadPackageContext& Context);`
- L151 _protected member_ `FUpgradedLevelSequenceBindingReferences BindingReferences;` — `UPROPERTY()` — References to bound objects.
- L157 _protected member_ `FLevelSequenceObjectReferenceMap ObjectReferences_DEPRECATED;` — `UPROPERTY()` — Legacy object references
- L161 _protected member_ `TObjectPtr<UBlueprint> DirectorBlueprint;` — `UPROPERTY()` — A pointer to the director blueprint that generates this sequence's DirectorClass.
- L170 _protected member_ `TObjectPtr<UClass> DirectorClass;` — `UPROPERTY()` — The class that is used to spawn this level sequence's director instance. Director instances are allocated on-demand one per sequence during evaluation and are used by event tracks for triggering events.
- L179 _public function_ `UObject* FindMetaDataByClass(TSubclassOf<UObject> InClass) const` — `UFUNCTION(BlueprintPure, Category = "Level Sequence", meta=(DevelopmentOnly))` — Find meta-data of a particular type for this level sequence instance. @param InClass - Class that you wish to find the metadata object for. @return An instance of this class if it already exists as metadata on this Level Sequence, otherwise null.
- L195 _public function_ `UObject* FindOrAddMetaDataByClass(TSubclassOf<UObject> InClass)` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence", meta=(DevelopmentOnly))` — Find meta-data of a particular type for this level sequence instance, adding it if it doesn't already exist. @param InClass - Class that you wish to find or create the metadata object for. @return An instance of this class as metadata on this Level Sequence.
- L217 _public function_ `UObject* CopyMetaData(UObject* InMetaData)` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence", meta=(DevelopmentOnly))` — Copy the specified meta data into this level sequence, overwriting any existing meta-data of the same type Meta-data may implement the ILevelSequenceMetaData interface in order to hook into default ULevelSequence functionality. @param InMetaData - Existing Metadata Object that you wish to copy into this Level Sequence. @return The newly copied instance of the Metadata that now exists on this sequence.
- L241 _public function_ `void RemoveMetaDataByClass(TSubclassOf<UObject> InClass)` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence", meta=(DevelopmentOnly))` — Remove meta-data of a particular type for this level sequence instance, if it exists @param InClass - The class type that you wish to remove the metadata for
- L256 _public function_ `template<typename MetaDataType> MetaDataType* FindMetaData() const` — Find meta-data of a particular type for this level sequence instance
- L268 _public function_ `template<typename MetaDataType> MetaDataType* FindOrAddMetaData()` — Find meta-data of a particular type for this level sequence instance, adding one if it was not found. Meta-data may implement the ILevelSequenceMetaData interface in order to hook into default ULevelSequence functionality.
- L284 _public function_ `template<typename MetaDataType> MetaDataType* CopyMetaData(MetaDataType* InMetaData)` — Copy the specified meta data into this level sequence, overwriting any existing meta-data of the same type Meta-data may implement the ILevelSequenceMetaData interface in order to hook into default ULevelSequence functionality.
- L298 _public function_ `template<typename MetaDataType> void RemoveMetaData()` — Remove meta-data of a particular type for this level sequence instance, if it exists
- L308 _private member_ `TArray<TObjectPtr<UObject>> MetaDataObjects;` — `UPROPERTY()` — Array of meta-data objects associated with this level sequence. Each pointer may implement the ILevelSequenceMetaData interface in order to hook into default ULevelSequence functionality.
- L315 _protected member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserData;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = Animation)` — Array of user data stored with the asset

#### Free symbols / members of external scopes

- L90 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(void, FPostDuplicateEvent, ULevelSequence*);`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FFixupDynamicBindingsEvent, ULevelSequence*);`
- L182 _function_ `auto const* Found = MetaDataObjects.FindByPredicate([InClass](UObject* In) { return In && In->GetClass() == InClass; });` (scope `ULevelSequence::FindMetaDataByClass`)
- L244 _function_ `MetaDataObjects.RemoveAll([InClass](UObject* In) { return In && In->GetClass() == InClass; });` (scope `ULevelSequence::RemoveMetaDataByClass`)
- L259 _function_ `auto const* Found = MetaDataObjects.FindByPredicate([PredicateClass](UObject* In){ return In && In->GetClass() == PredicateClass; });` (scope `ULevelSequence::FindMetaData`)
- L301 _function_ `MetaDataObjects.RemoveAll([PredicateClass](UObject* In){ return In && In->GetClass() == PredicateClass; });` (scope `ULevelSequence::RemoveMetaData`)

### `Source/Runtime/LevelSequence/Public/LevelSequenceActor.h` (Public)


#### class `ULevelSequenceBurnInInitSettings`  
`class ULevelSequenceBurnInInitSettings : public UObject`  
_L24-27_
- reflection: `UCLASS(Blueprintable, DefaultToInstanced, MinimalAPI)`
- inherits: `UObject`

#### class `ULevelSequenceBurnInOptions`  
`class ULevelSequenceBurnInOptions : public UObject`  
_L30-60_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, PerObjectConfig, DefaultToInstanced, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L35 _public prototype_ `ULevelSequenceBurnInOptions(const FObjectInitializer& Init);`
- L39 _public prototype_ `void SetBurnIn(FSoftClassPath InBurnInClass);` — `UFUNCTION(BlueprintCallable, Category = "General")` — Loads the specified class path and initializes an instance, then stores it in Settings.
- L42 _public prototype_ `void ResetSettings();` — Ensure the settings object is up-to-date
- L47 _public member_ `bool bUseBurnIn;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="General")`
- L50 _public member_ `FSoftClassPath BurnInClass;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="General", meta=(EditCondition=bUseBurnIn, MetaClass="/Script/LevelSequence.LevelSequenceBurnIn"))`
- L53 _public member_ `TObjectPtr<ULevelSequenceBurnInInitSettings> Settings;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category="General", meta=(EditCondition=bUseBurnIn))`
- L58 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `ALevelSequenceActor`  
`class ALevelSequenceActor : public AActor , public IMovieScenePlaybackClient , public IMovieSceneBindingOwnerInterface , public IWorldPartitionObjectResolver`  
_L66-336_
- reflection: `UCLASS(hideCategories=(Rendering, Physics, HLOD, Activation, Input), MinimalAPI)`
- inherits: `AActor,IMovieScenePlaybackClient,IMovieSceneBindingOwnerInterface,IWorldPartitionObjectResolver`
- desc: Actor responsible for controlling a specific level sequence in the world.
- L74 _public prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnLevelSequenceLoaded);`
- L79 _public prototype_ `ALevelSequenceActor(const FObjectInitializer& Init);` — Create and initialize a new instance.
- L84 _public member_ `FMovieSceneSequencePlaybackSettings PlaybackSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Playback", meta=(ShowOnlyInnerProperties, ExposeOnSpawn))`
- L88 _public member_ `TObjectPtr<ULevelSequencePlayer> SequencePlayer;` — `UE_DEPRECATED(5.4, "Direct access to SequencePlayer will be removed. Please use GetSequencePlayer()")` — `UPROPERTY(Instanced, transient, replicated, BlueprintReadOnly, BlueprintGetter = GetSequencePlayer, Category = "Playback", meta = (ExposeFunctionCategories = "Sequencer|Player"))`
- L91 _public member_ `TObjectPtr<ULevelSequence> LevelSequenceAsset;` — `UPROPERTY(EditAnywhere, replicated, BlueprintReadOnly, Category="General", meta=(AllowedClasses="/Script/LevelSequence.LevelSequence", ExposeOnSpawn))`
- L95 _public member_ `FSoftObjectPath LevelSequence_DEPRECATED;` — `UPROPERTY()`
- L99 _public member_ `FLevelSequenceCameraSettings CameraSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cameras", meta=(ShowOnlyInnerProperties, ExposeOnSpawn))`
- L102 _public member_ `TObjectPtr<ULevelSequenceBurnInOptions> BurnInOptions;` — `UPROPERTY(Instanced, BlueprintReadOnly, Category="General")`
- L106 _public member_ `TObjectPtr<UMovieSceneBindingOverrides> BindingOverrides;` — `UPROPERTY(Instanced, BlueprintReadOnly, Category="General")` — Mapping of actors to override the sequence bindings with
- L109 _public member_ `uint8 bAutoPlay_DEPRECATED : 1;` — `UPROPERTY()`
- L113 _public member_ `uint8 bOverrideInstanceData : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="General")` — Enable specification of dynamic instance data to be supplied to the sequence during playback
- L117 _public member_ `uint8 bReplicatePlayback:1;` — `UPROPERTY(EditAnywhere, DisplayName="Replicate Playback", BlueprintReadWrite, BlueprintSetter=SetReplicatePlayback, Category=Replication, meta=(ExposeOnSpawn))` — If true, playback of this level sequence on the server will be synchronized across other clients
- L121 _public member_ `TObjectPtr<UObject> DefaultInstanceData;` — `UPROPERTY(Instanced, BlueprintReadWrite, Category="General")` — Instance data that can be used to dynamically control sequence evaluation at runtime
- L132 _public prototype_ `ULevelSequence* GetSequence() const;` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Player")` — Get the level sequence being played by this actor. @return Level sequence, or nullptr if not assigned or if it cannot be loaded. @see SetSequence
- L141 _public prototype_ `void SetSequence(ULevelSequence* InSequence);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Player")` — Set the level sequence being played by this actor. @param InSequence The sequence object to set. @see GetSequence
- L147 _public prototype_ `void SetReplicatePlayback(bool ReplicatePlayback);` — `UFUNCTION(BlueprintSetter)` — Set whether or not to replicate playback for this actor
- L153 _public prototype_ `ULevelSequencePlayer* GetSequencePlayer() const;` — `UFUNCTION(BlueprintGetter)` — Access this actor's sequence player, or None if it is not yet initialized
- L157 _public prototype_ `void HideBurnin();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Hide burnin
- L161 _public prototype_ `void ShowBurnin();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Show burnin
- L164 _public prototype_ `void RefreshBurnIn();` — Refresh this actor's burn in
- L178 _public prototype_ `void SetBinding(FMovieSceneObjectBindingID Binding, const TArray<AActor*>& Actors, bool bAllowBindingsFromAsset = false);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Overrides the specified binding with the specified actors, optionally still allowing the bindings defined in the Level Sequence asset @param Binding Binding to modify @param Actors Actors to bind @param bAllowBindingsFromAsset If false the new bindings being supplied here will replace the bindings set in the level sequence asset, meaning the original object animated by Sequencer will no longer be animated. Bindings set to spawnables will not spawn if false. If true, new bindings will be in addition to ones set set in Sequencer UI. This function will not modify the original asset.
- L190 _public prototype_ `void SetBindingByTag(FName BindingTag, const TArray<AActor*>& Actors, bool bAllowBindingsFromAsset = false);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Assigns an set of actors to all the bindings tagged with the specified name in this sequence. Object Bindings can be tagged within the sequence UI by RMB -> Tags... on the object binding in the tree. @param BindingTag   The unique tag name to lookup bindings with @param Actors       The actors to assign to all the tagged bindings @param bAllowBindingsFromAsset If false the new bindings being supplied here will replace the bindings set in the level sequence asset, meaning the original object animated by Sequencer will no longer be animated. Bindings set to spawnables will not spawn if false. If true, new bindings will be in addition to ones set set in Sequencer UI. This function will not modify the original asset.
- L202 _public prototype_ `void AddBinding(FMovieSceneObjectBindingID Binding, AActor* Actor, bool bAllowBindingsFromAsset = false);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Adds the specified actor to the overridden bindings for the specified binding ID, optionally still allowing the bindings defined in the Level Sequence asset @param Binding Binding to modify @param Actor Actor to bind @param bAllowBindingsFromAsset If false the new bindings being supplied here will replace the bindings set in the level sequence asset, meaning the original object animated by Sequencer will no longer be animated. Bindings set to spawnables will not spawn if false. If true, new bindings will be in addition to ones set set in Sequencer UI. This function will not modify the original asset.
- L214 _public prototype_ `void AddBindingByTag(FName BindingTag, AActor* Actor, bool bAllowBindingsFromAsset = false);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Binds an actor to all the bindings tagged with the specified name in this sequence. Does not remove any exising bindings that have been set up through this API. Object Bindings can be tagged within the sequence UI by RMB -> Tags... on the object binding in the tree. @param BindingTag   The unique tag name to lookup bindings with @param Actor        The actor to assign to all the tagged bindings @param bAllowBindingsFromAsset If false the new bindings being supplied here will replace the bindings set in the level sequence asset, meaning the original object animated by Sequencer will no longer be animated. Bindings set to spawnables will not spawn if false. If true, new bindings will be in addition to ones set set in Sequencer UI. This function will not modify the original asset.
- L220 _public prototype_ `void RemoveBinding(FMovieSceneObjectBindingID Binding, AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Removes the specified actor from the specified binding's actor array
- L226 _public prototype_ `void RemoveBindingByTag(FName Tag, AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Removes the specified actor from the specified binding's actor array
- L232 _public prototype_ `void ResetBinding(FMovieSceneObjectBindingID Binding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Resets the specified binding back to the defaults defined by the Level Sequence asset
- L238 _public prototype_ `void ResetBindings();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Resets all overridden bindings back to the defaults defined by the Level Sequence asset
- L244 _public prototype_ `FMovieSceneObjectBindingID FindNamedBinding(FName Tag) const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings", DisplayName="Find Binding by Tag")` — Retrieve the first object binding that has been tagged with the specified name
- L253 _public prototype_ `const TArray<FMovieSceneObjectBindingID>& FindNamedBindings(FName Tag) const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings", DisplayName="Find Bindings by Tag")` — Retrieve all the bindings that have been tagged with the specified name @param Tag  The unique tag name to lookup bindings with. Object Bindings can be tagged within the sequence UI by RMB -> Tags... on the object binding in the tree. @return An array containing all the bindings that are tagged with this name, potentially empty.
- L258 _protected prototype_ `virtual bool RetrieveBindingOverrides(const FGuid& InBindingId, FMovieSceneSequenceID InSequenceID, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L259 _protected prototype_ `virtual UObject* GetInstanceData() const override;`
- L260 _protected prototype_ `virtual TOptional<EAspectRatioAxisConstraint> GetAspectRatioAxisConstraint() const override;`
- L261 _protected prototype_ `virtual bool GetIsReplicatedPlayback() const override;`
- L263 _protected prototype_ `virtual bool CanPreview(const UMovieSceneSequence& InSequence) const override;`
- L268 _protected prototype_ `virtual void PostInitProperties() override;`
- L269 _protected prototype_ `virtual void PostLoad() override;`
- L272 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L274 _protected prototype_ `void TransformOriginChanged();`
- L279 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L286 _protected prototype_ `virtual void PreInitializeComponents() override;`
- L287 _protected prototype_ `virtual void PostInitializeComponents() override;`
- L288 _protected prototype_ `virtual void BeginPlay() override;`
- L289 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L290 _protected prototype_ `virtual void RewindForReplay() override;`
- L291 _protected prototype_ `virtual void PostNetReceive() override;`
- L293 _protected function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L299 _public function_ `const FWorldPartitionResolveData& GetWorldPartitionResolveData() const`
- L305 _public function_ `virtual void SetWorldPartitionResolveData(const FWorldPartitionResolveData& InWorldPartitionResolveData)`
- L310 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L314 _public prototype_ `void InitializePlayer();` — Initialize the player object by loading the asset, using async loading when necessary
- L317 _public prototype_ `void InitializePlayerWithSequence(ULevelSequence* LevelSequenceAsset);` — Initialize the player object with the specified asset
- L318 _public prototype_ `void OnSequenceLoaded(const FName& PackageName, UPackage* Package, EAsyncLoadingResult::Type Result);`
- L321 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetObjectPickerProxy(TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L322 _public prototype_ `virtual void UpdateObjectFromProxy(FStructOnScope& Proxy, IPropertyHandle& ObjectPropertyHandle) override;`
- L323 _public prototype_ `virtual UMovieSceneSequence* RetrieveOwnedSequence() const override;`
- L329 _private member_ `TObjectPtr<ULevelSequenceBurnIn> BurnInInstance;` — `UPROPERTY()` — Burn-in widget
- L332 _private member_ `bool bShowBurnin;` — `UPROPERTY()`
- L335 _private member_ `FWorldPartitionResolveData WorldPartitionResolveData;` — `UPROPERTY()`

#### struct `FBoundActorProxy`  
`struct FBoundActorProxy`  
_L339-356_
- reflection: `USTRUCT()`
- L347 _public member_ `TObjectPtr<AActor> BoundActor = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, Category="General")` — Specifies the actor to override the binding with
- L349 _public prototype_ `void Initialize(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L351 _public prototype_ `void OnReflectedPropertyChanged();`
- L353 _public member_ `TSharedPtr<IPropertyHandle> ReflectedProperty;`

#### class `AReplicatedLevelSequenceActor`  
`class AReplicatedLevelSequenceActor : public ALevelSequenceActor`  
_L362-370_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ALevelSequenceActor`
- desc: A level sequence actor that is set to always be relevant for networking purposes
- L369 _public prototype_ `AReplicatedLevelSequenceActor(const FObjectInitializer& Init);` — Create and initialize a new instance.

#### Free symbols / members of external scopes

- L74 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnLevelSequenceLoaded);`

### `Source/Runtime/LevelSequence/Public/LevelSequenceActorSpawner.h` (Public)


#### class `FLevelSequenceActorSpawner`  
`class FLevelSequenceActorSpawner : public IMovieSceneObjectSpawner`  
_L7-17_
- inherits: `IMovieSceneObjectSpawner`
- L11 _public prototype_ `static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();`
- L14 _public prototype_ `virtual UClass* GetSupportedTemplateType() const override;` — IMovieSceneObjectSpawner interface
- L15 _public prototype_ `virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;`
- L16 _public prototype_ `virtual void DestroySpawnedObject(UObject& Object) override;`

### `Source/Runtime/LevelSequence/Public/LevelSequenceAnimSequenceLink.h` (Public)


#### struct `FLevelSequenceAnimSequenceLinkItem`  
`struct FLevelSequenceAnimSequenceLinkItem`  
_L20-120_
- reflection: `USTRUCT(BlueprintType)`
- desc: Link To Anim Sequence that we are linked too.
- L26 _public member_ `FGuid SkelTrackGuid;` — `UPROPERTY(BlueprintReadWrite, Category = Property)`
- L29 _public member_ `FSoftObjectPath PathToAnimSequence;` — `UPROPERTY(BlueprintReadWrite, Category = Property)`
- L33 _public member_ `bool bAutoBake = false;` — `UPROPERTY(BlueprintReadWrite, Category = Property)` — if true it will be autobaked
- L37 _public member_ `bool bExportTransforms = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)` — From Editor Only UAnimSeqExportOption we cache this since we can re-import dynamically
- L39 _public member_ `bool bExportMorphTargets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L41 _public member_ `bool bExportAttributeCurves = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L43 _public member_ `bool bExportMaterialCurves = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L45 _public member_ `bool bSkipCurvesWithZeroValue = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L47 _public member_ `bool bSetRetargetSourceAsset = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L49 _public member_ `EAnimInterpolationType Interpolation = EAnimInterpolationType::Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L51 _public member_ `TEnumAsByte<ERichCurveInterpMode> CurveInterpolation = ERichCurveInterpMode::RCIM_Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L53 _public member_ `bool bRecordInWorldSpace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L55 _public member_ `bool bEvaluateAllSkeletalMeshComponents = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)`
- L59 _public member_ `TArray<FString> IncludeAnimationNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)` — Include only the animation bones/curves that match this list
- L62 _public member_ `TArray<FString> ExcludeAnimationNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)` — Exclude all animation bones/curves that match this list
- L65 _public member_ `bool bRemoveExcludedCurves = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)` — If enabled, curves in ExcludeAnimationNames that already exist in the target sequence will be removed at the start of recording
- L68 _public member_ `FFrameNumber WarmUpFrames = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)` — Number of Display Rate frames to evaluate before doing the export. It will evaluate after any Delay. This will use frames before the start frame. Use it if there is some post anim BP effects you want to run before export start time.
- L71 _public member_ `FFrameNumber DelayBeforeStart = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)` — Number of Display Rate frames to delay at the same frame before doing the export. It will evalaute first, then any warm up, then the export. Use it if there is some post anim BP effects you want to ran repeatedly at the start.
- L74 _public member_ `bool bUseCustomTimeRange = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)` — Whether or not to use custom time range
- L77 _public member_ `FFrameNumber CustomStartFrame = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bUseCustomTimeRange), Category = Property)` — Custom start frame in display rate
- L80 _public member_ `FFrameNumber CustomEndFrame = 120;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bUseCustomTimeRange), Category = Property)` — Custom end frame in display rate
- L83 _public member_ `FFrameRate CustomDisplayRate = FFrameRate(30, 1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bUseCustomTimeRange), Category = Property)` — Custom display rate, should be set from the movie scene/sequencer display rate
- L87 _public member_ `bool bUseCustomFrameRate = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)` — Whether or not to use custom frame rate or Sequencer display rate
- L91 _public member_ `FFrameRate CustomFrameRate = FFrameRate(30, 1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bUseCustomFrameRate), Category = Property)` — Custom frame rate that the anim sequence may have been recorded at
- L93 _public prototype_ `void SetAnimSequence(UAnimSequence* InAnimSequence);`
- L94 _public prototype_ `UAnimSequence* ResolveAnimSequence();`
- L96 _public function_ `bool IsEqual(FGuid InSkelTrackGuid, bool bInUseCustomTimeRange = false, FFrameNumber InCustomStartFrame = 0, FFrameNumber InCustomEndFrame = 120, FFrameRate InCustomDisplayRate = FFrameRate(30,1), bool bInUseCustomFrameRate = false, FFrameRate InCustomFrameRate = FFrameRate(30, 1) )`

#### class `ULevelSequenceAnimSequenceLink`  
`class ULevelSequenceAnimSequenceLink : public UAssetUserData`  
_L124-133_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UAssetUserData`
- desc: Link To Set of Anim Sequences that we may belinked to.
- L129 _public function_ `virtual bool IsEditorOnly() const override`
- L132 _public member_ `TArray< FLevelSequenceAnimSequenceLinkItem> AnimSequenceLinks;` — `UPROPERTY(BlueprintReadWrite, Category = Links)`

### `Source/Runtime/LevelSequence/Public/LevelSequenceBindingReference.h` (Public)


#### struct `FLevelSequenceBindingReference`  
`struct FLevelSequenceBindingReference`  
_L25-89_
- reflection: `USTRUCT()`
- desc: An external reference to an level sequence object, resolvable through an arbitrary context. Bindings consist of an optional package name, and the path to the object within that package. Where package name is empty, the reference is a relative path from a specific outer (the context). Currently, the package name should only ever be empty for component references, which must remain relative bindings to work correctly with spawnables and reinstanced actors.
- L32 _public function_ `FLevelSequenceBindingReference()` — Default construction only used for serialization
- L38 _public prototype_ `FLevelSequenceBindingReference(UObject* InObject, UObject* InContext);` — `UE_DEPRECATED(5.4, "This class is now deprecated. Please convert your code to use the more generic FMovieSceneBindingReferences.")` — Construct a new binding reference from an object, and a given context (expected to be either a UWorld, or an AActor)
- L66 _public prototype_ `UObject* Resolve(UObject* InContext, const FResolveBindingParams& InResolveBindingParams) const;` — `UE_DEPRECATED(5.4, "This class is now deprecated. Please convert your code to use the more generic FMovieSceneBindingReferences.")` — Resolve this reference within the specified context @param	InContext	The context to resolve the binding within. Either a UWorld, ULevel (when playing in an instanced level) or an AActor where this binding relates to an actor component @param	InResolveBindingParams   The struct containing additional resolving params. @return	The object (usually an Actor or an ActorComponent).
- L72 _public prototype_ `bool operator==(const FLevelSequenceBindingReference& Other) const;` — `UE_DEPRECATED(5.4, "This class is now deprecated. Please convert your code to use the more generic FMovieSceneBindingReferences.")` — Check whether this binding reference is equal to the specified object
- L75 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Handles ExternalObjectPath fixup
- L80 _public member_ `FString PackageName_DEPRECATED;` — `UPROPERTY()` — Replaced by ExternalObjectPath
- L84 _public member_ `FSoftObjectPath ExternalObjectPath;` — `UPROPERTY()` — Path to a specific actor/component inside an external package
- L88 _public member_ `FString ObjectPath;` — `UPROPERTY()` — Object path relative to a passed in context object, this is used if ExternalObjectPath is invalid

#### struct `FLevelSequenceBindingReference::FResolveBindingParams`  
`struct FResolveBindingParams`  
_L43-56_
- desc: Structure that stores additional params that are used for resolving bindings.
- L46 _public function_ `FResolveBindingParams() : WorldPartitionResolveData(nullptr), StreamingWorld(nullptr)` — `UE_DEPRECATED(5.4, "This class is now deprecated. Please convert your code to use the more generic FMovieSceneBindingReferences.")`
- L49 _public member_ `FTopLevelAssetPath StreamedLevelAssetPath;` — The path to the streamed level asset that contains the level sequence actor playing back the sequence. 'None' for any non - instance - level setups.
- L52 _public member_ `const FWorldPartitionResolveData* WorldPartitionResolveData;` — World Partition Resolve Data
- L55 _public member_ `UWorld* StreamingWorld;` — World Partition Streaming World

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLevelSequenceBindingReference> : public TStructOpsTypeTraitsBase2<FLevelSequenceBindingReference>`  
_L93-99_
- inherits: `TStructOpsTypeTraitsBase2<FLevelSequenceBindingReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L96-98_

#### struct `FLevelSequenceBindingReferenceArray`  
`struct FLevelSequenceBindingReferenceArray`  
_L105-111_
- reflection: `USTRUCT()`
- desc: An array of binding references
- L110 _public member_ `TArray<FLevelSequenceBindingReference> References;` — `UPROPERTY()`

#### struct `FUpgradedLevelSequenceBindingReferences`  
`struct FUpgradedLevelSequenceBindingReferences : public FMovieSceneBindingReferences`  
_L114-121_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneBindingReferences`
- L118 _public prototype_ `void AddBinding(const FGuid& ObjectId, UObject* InObject, UObject* InContext);`
- L120 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUpgradedLevelSequenceBindingReferences> : public TStructOpsTypeTraitsBase2<FUpgradedLevelSequenceBindingReferences>`  
_L124-130_
- inherits: `TStructOpsTypeTraitsBase2<FUpgradedLevelSequenceBindingReferences>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L127-129_

#### struct `FLevelSequenceBindingReferences`  
`struct FLevelSequenceBindingReferences`  
_L136-151_
- reflection: `USTRUCT()`
- desc: Structure that stores a one to many mapping from object binding ID, to object references that pertain to that ID.
- L142 _public member_ `TMap<FGuid, FLevelSequenceBindingReferenceArray> BindingIdToReferences;` — `UPROPERTY()` — The map from object binding ID to an array of references that pertain to that ID
- L146 _public member_ `TSet<FGuid> AnimSequenceInstances;` — `UPROPERTY()` — A set of object binding IDs that relate to anim sequence instances (must be a child of USkeletalMeshComponent)
- L150 _public member_ `TSet<FGuid> PostProcessInstances;` — `UPROPERTY()` — A set of object binding IDs that relate to post process instances (must be a child of USkeletalMeshComponent)

#### Free symbols / members of external scopes

- L97 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon5f6e16480103`)
- L128 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon5f6e16480203`)

### `Source/Runtime/LevelSequence/Public/LevelSequenceBurnIn.h` (Public)


#### class `ULevelSequenceBurnIn`  
`class ULevelSequenceBurnIn : public UUserWidget`  
_L17-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUserWidget`
- desc: Base class for level sequence burn ins
- L22 _public prototype_ `ULevelSequenceBurnIn(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `void TakeSnapshotsFrom(ALevelSequenceActor& InActor);` — Initialize this burn in
- L29 _public prototype_ `void SetSettings(UObject* InSettings);` — `UFUNCTION(BlueprintImplementableEvent, Category="Burn In")` — Called when this burn in is receiving its settings
- L33 _public prototype_ `TSubclassOf<ULevelSequenceBurnInInitSettings> GetSettingsClass() const;` — `UFUNCTION(BlueprintNativeEvent, Category="Burn In")` — Get the settings class to use for this burn in
- L34 _public function_ `virtual TSubclassOf<ULevelSequenceBurnInInitSettings> GetSettingsClass_Implementation() const`
- L39 _protected prototype_ `void OnSequenceUpdated(const UMovieSceneSequencePlayer& Player, FFrameTime CurrentTime, FFrameTime PreviousTime);` — Called as part of the game tick loop when the sequence has been updated
- L45 _protected member_ `FLevelSequencePlayerSnapshot FrameInformation;` — `UPROPERTY(BlueprintReadOnly, Category="Burn In")` — Snapshot of frame information.
- L49 _protected member_ `TObjectPtr<ALevelSequenceActor> LevelSequenceActor;` — `UPROPERTY(BlueprintReadOnly, Category="Burn In")` — The actor to get our burn in frames from

### `Source/Runtime/LevelSequence/Public/LevelSequenceCameraSettings.h` (Public)


#### struct `FLevelSequenceCameraSettings`  
`struct FLevelSequenceCameraSettings`  
_L11-20_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `bool bOverrideAspectRatioAxisConstraint = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aspect Ratio")`
- L19 _public member_ `TEnumAsByte<EAspectRatioAxisConstraint> AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainXFOV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aspect Ratio", meta = (EditCondition = bOverrideAspectRatioAxisConstraint))`

### `Source/Runtime/LevelSequence/Public/LevelSequenceDirector.h` (Public)


#### class `ULevelSequenceDirector`  
`class ULevelSequenceDirector : public UObject`  
_L21-136_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L28 _public prototype_ `void OnCreated();` — `UFUNCTION(BlueprintImplementableEvent, Category="Sequencer")` — Called when this director is created
- L35 _public prototype_ `UMovieSceneClock* GetRootSequenceCustomClock() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Director")` — @return The custom clock of the outermost (root) sequence
- L42 _public prototype_ `UMovieSceneClock* GetSequenceCustomClock() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Director")` — @return The custom clock of this director's sequence
- L49 _public prototype_ `FQualifiedFrameTime GetRootSequenceTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Director")` — Get the current time for the outermost (root) sequence @return The current playback position of the outermost (root) sequence
- L56 _public prototype_ `FQualifiedFrameTime GetCurrentTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Director")` — Get the current time for this director's sub-sequence (or the root sequence, if this is a root sequence director) @return The current playback position of this director's sequence
- L65 _public prototype_ `TArray<UObject*> GetBoundObjects(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Resolve the bindings inside this sub-sequence that relate to the specified ID @note: ObjectBinding should be constructed from the same sequence as this Sequence Director's owning Sequence (see the GetSequenceBinding node) @param ObjectBinding The ID for the object binding inside this sub-sequence or one of its children to resolve
- L75 _public prototype_ `UObject* GetBoundObject(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Resolve the first valid binding inside this sub-sequence that relates to the specified ID @note: ObjectBinding should be constructed from the same sequence as this Sequence Director's owning Sequence (see the GetSequenceBinding node) @param ObjectBinding The ID for the object binding inside this sub-sequence or one of its children to resolve
- L85 _public prototype_ `TArray<AActor*> GetBoundActors(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Resolve the actor bindings inside this sub-sequence that relate to the specified ID @note: ObjectBinding should be constructed from the same sequence as this Sequence Director's owning Sequence (see the GetSequenceBinding node) @param ObjectBinding The ID for the object binding inside this sub-sequence or one of its children to resolve
- L95 _public prototype_ `AActor* GetBoundActor(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Resolve the first valid Actor binding inside this sub-sequence that relates to the specified ID @note: ObjectBinding should be constructed from the same sequence as this Sequence Director's owning Sequence (see the GetSequenceBinding node) @param ObjectBinding The ID for the object binding inside this sub-sequence or one of its children to resolve
- L101 _public prototype_ `UMovieSceneSequence* GetSequence();` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Get the current sequence that this director is playing back within
- L105 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L109 _private prototype_ `const UE::MovieScene::FSequenceInstance* FindSequenceInstance() const;`
- L115 _public member_ `int32 SubSequenceID;` — `UPROPERTY()` — The Sequence ID for the sequence this director is playing back within - has to be stored as an int32 so that it is reinstanced correctly
- L119 _public member_ `TWeakObjectPtr<UMovieSceneEntitySystemLinker> WeakLinker;` — `UPROPERTY()` — The linker inside which the sequence is evaluating. Only valid in game or in PIE/Simulate.
- L123 _public member_ `uint16 InstanceID = (uint16)-1;` — `UPROPERTY()` — Instance ID of the sequence. Only valid in game or in PIE/Simulate.
- L127 _public member_ `uint16 InstanceSerial = 0;` — `UPROPERTY()` — Instance serial of the sequence. Only valid in game or in PIE/Simulate.
- L131 _public member_ `TObjectPtr<ULevelSequencePlayer> Player;` — `UPROPERTY(BlueprintReadOnly, Category="Cinematics")` — Pointer to the player that's playing back this director's sequence. Only valid in game or in PIE/Simulate.
- L135 _public member_ `int32 MovieScenePlayerIndex;` — `UPROPERTY()` — Native player interface index - stored by index so that it can be reinstanced correctly

#### class `ULegacyLevelSequenceDirectorBlueprint`  
`class ULegacyLevelSequenceDirectorBlueprint : public UBlueprint`  
_L140-149_
- reflection: `UCLASS()`
- inherits: `UBlueprint`
- L144 _private function_ `ULegacyLevelSequenceDirectorBlueprint(const FObjectInitializer& ObjInit) : Super(ObjInit)`

### `Source/Runtime/LevelSequence/Public/LevelSequenceLegacyObjectReference.h` (Public)


#### struct `FLevelSequenceLegacyObjectReference`  
`struct FLevelSequenceLegacyObjectReference`  
_L15-41_
- reflection: `USTRUCT()`
- desc: Legacy method by which objects were referenced within a level sequence. No longer used. See FLevelSequenceBindingReference for up-to-date implementation.
- L24 _public prototype_ `UObject* Resolve(UObject* InContext) const;` — Resolve this reference within the specified context @return The object (usually an Actor or an ActorComponent).
- L37 _public member_ `FUniqueObjectGuid ObjectId;` — Primary method of resolution - object ID, stored as an annotation on the object in the world
- L40 _public member_ `FString ObjectPath;` — Secondary method of resolution - path to the object within the context

#### struct `FLevelSequenceObjectReferenceMap`  
`struct FLevelSequenceObjectReferenceMap`  
_L44-56_
- reflection: `USTRUCT()`
- L53 _public prototype_ `bool Serialize(FArchive& Ar);` — Serialization function
- L55 _public member_ `TMap<FGuid, FLevelSequenceLegacyObjectReference> Map;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLevelSequenceObjectReferenceMap> : public TStructOpsTypeTraitsBase2<FLevelSequenceObjectReferenceMap>`  
_L58-61_
- inherits: `TStructOpsTypeTraitsBase2<FLevelSequenceObjectReferenceMap>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L60-60_

#### Free symbols / members of external scopes

- L29 _function_ `friend FArchive& operator<<(FArchive& Ar, FLevelSequenceLegacyObjectReference& Ref)` — Serialization operator
- L60 _enumerator_ `enum { WithSerializer = true };` (scope `TStructOpsTypeTraits::__anon2ce9adb90103`)

### `Source/Runtime/LevelSequence/Public/LevelSequencePlayer.h` (Public)


#### struct `FLevelSequencePlayerSnapshot`  
`struct FLevelSequencePlayerSnapshot`  
_L33-66_
- reflection: `USTRUCT(BlueprintType)`
- desc: Frame snapshot information for a level sequence
- L38 _public member_ `FString RootName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")`
- L41 _public member_ `FQualifiedFrameTime RootTime;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")`
- L44 _public member_ `FQualifiedFrameTime SourceTime;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")`
- L47 _public member_ `FString CurrentShotName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")`
- L50 _public member_ `FQualifiedFrameTime CurrentShotLocalTime;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")`
- L53 _public member_ `FQualifiedFrameTime CurrentShotSourceTime;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")`
- L56 _public member_ `FString SourceTimecode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")`
- L59 _public member_ `TSoftObjectPtr<UCameraComponent> CameraComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="General")`
- L62 _public member_ `TObjectPtr<ULevelSequence> ActiveShot = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")`
- L65 _public member_ `FMovieSceneSequenceID ShotID;` — `UPROPERTY()`

#### class `ULevelSequencePlayer`  
`class ULevelSequencePlayer : public UMovieSceneSequencePlayer , public UE::MovieScene::FCameraCutPlaybackCapability`  
_L75-187_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMovieSceneSequencePlayer,UE::MovieScene::FCameraCutPlaybackCapability`
- desc: ULevelSequencePlayer is used to actually "play" an level sequence asset at runtime. This class keeps track of playback state and provides functions for manipulating an level sequence while its playing.
- L80 _public prototype_ `ULevelSequencePlayer(const FObjectInitializer&);`
- L91 _public prototype_ `void Initialize(ULevelSequence* InLevelSequence, ULevel* InLevel, const FLevelSequenceCameraSettings& InCameraSettings);` — Initialize the player. @param InLevelSequence The level sequence to play. @param InLevel The level that the animation is played in. @param InCameraSettings The desired camera settings
- L93 _public prototype_ `void SetSourceActorContext(UWorld* InStreamingWorld, FActorContainerID InContainerID, FTopLevelAssetPath InSourceAssetPath);`
- L106 _public prototype_ `static ULevelSequencePlayer* CreateLevelSequencePlayer(UObject* WorldContextObject, ULevelSequence* LevelSequence, FMovieSceneSequencePlaybackSettings Settings, ALevelSequenceActor*& OutActor);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Player", meta=(WorldContext="WorldContextObject", DynamicOutputParam="OutActor"))` — Create a new level sequence player. @param WorldContextObject Context object from which to retrieve a UWorld. @param LevelSequence The level sequence to play. @param Settings The desired playback settings @param OutActor The level sequence actor created to play this sequence.
- L110 _public member_ `FOnLevelSequencePlayerCameraCutEvent OnCameraCut;` — `UPROPERTY(BlueprintAssignable, Category="Sequencer|Player")` — Event triggered when there is a camera cut
- L114 _public function_ `UCameraComponent* GetActiveCameraComponent() const` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Player")` — Get the active camera cut camera
- L119 _public prototype_ `virtual UObject* GetPlaybackContext() const override;` — IMovieScenePlayer interface
- L120 _public prototype_ `virtual TArray<UObject*> GetEventContexts() const override;`
- L122 _public prototype_ `void RewindForReplay();`
- L128 _protected prototype_ `virtual void ResolveBoundObjects(UE::UniversalObjectLocator::FResolveParams& ResolveParams, const FGuid& InBindingId, FMovieSceneSequenceID SequenceID, UMovieSceneSequence& Sequence, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L129 _protected prototype_ `virtual void InitializeRootInstance(TSharedRef<UE::MovieScene::FSharedPlaybackState> NewSharedPlaybackState) override;`
- L132 _protected prototype_ `virtual bool CanPlay() const override;`
- L133 _protected prototype_ `virtual void OnStartedPlaying() override;`
- L134 _protected prototype_ `virtual void OnStopped() override;`
- L135 _protected prototype_ `virtual void UpdateMovieSceneInstance(FMovieSceneEvaluationRange InRange, EMovieScenePlayerStatus::Type PlayerStatus, const FMovieSceneUpdateArgs& Args) override;`
- L138 _protected prototype_ `virtual bool ShouldUpdateCameraCut() override;`
- L139 _protected prototype_ `virtual float GetCameraBlendPlayRate() override;`
- L140 _protected prototype_ `virtual TOptional<EAspectRatioAxisConstraint> GetAspectRatioAxisConstraintOverride() override;`
- L141 _protected prototype_ `virtual void OnCameraCutUpdated(const UE::MovieScene::FOnCameraCutUpdatedParams& Params) override;`
- L146 _public prototype_ `static void GetEventContexts(UWorld& InWorld, TArray<UObject*>& OutContexts);` — Populate the specified array with any given event contexts for the specified world
- L149 _public prototype_ `void TakeFrameSnapshot(FLevelSequencePlayerSnapshot& OutSnapshot) const;` — Take a snapshot of the current state of this player
- L152 _public function_ `void SetSnapshotOffsetFrames(int32 InFrameOffset)` — Set the offset time for the snapshot in play rate frames.
- L156 _private prototype_ `void EnableCinematicMode(bool bEnable);`
- L158 _private prototype_ `void InitializeLevelSequenceRootInstance(TSharedRef<UE::MovieScene::FSharedPlaybackState> NewSharedPlaybackState);`
- L163 _private member_ `TWeakObjectPtr<UWorld> World;` — The world this player will spawn actors in, if needed
- L166 _private member_ `TWeakObjectPtr<ULevel> Level;` — The world this player will spawn actors in, if needed
- L169 _private member_ `FLevelSequenceCameraSettings CameraSettings;` — The camera settings to use when playing the sequence
- L173 _protected member_ `TOptional<int32> SnapshotOffsetTime;`
- L175 _protected member_ `TWeakObjectPtr<UCameraComponent> CachedCameraComponent;`
- L179 _private member_ `TOptional<FLevelSequencePlayerSnapshot> PreviousSnapshot;`
- L182 _private member_ `TWeakObjectPtr<UWorld> WeakStreamingWorld;` — Optional streaming world that should be used primarily for resolving actor references. Used for locating actors within World Partition runtime cells.
- L184 _private member_ `FTopLevelAssetPath SourceAssetPath;` — Source asset path denoting the level asset path that has been streamed in.
- L186 _private member_ `FActorContainerID ContainerID;` — World Partition container ID for the world that should be added to any actor locaters when being resolved within the same world.

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelSequencePlayerCameraCutEvent , UCameraComponent*, CameraComponent);`
- L27 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelSequencePlayerCameraCutEvent , UCameraComponent*, CameraComponent);`

### `Source/Runtime/LevelSequence/Public/LevelSequenceProjectSettings.h` (Public)


#### class `ULevelSequenceProjectSettings`  
`class ULevelSequenceProjectSettings : public UDeveloperSettings`  
_L16-39_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig, meta=(DisplayName="Level Sequence"))`
- inherits: `UDeveloperSettings`
- desc: Settings for level sequences
- L21 _public prototype_ `ULevelSequenceProjectSettings();`
- L24 _public member_ `bool bDefaultLockEngineToDisplayRate;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ConsoleVariable="LevelSequence.DefaultLockEngineToDisplayRate", Tooltip="0: Playback locked to playback frames\n1: Unlocked playback with sub frame interpolation"))`
- L27 _public member_ `FString DefaultDisplayRate;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ConsoleVariable="LevelSequence.DefaultDisplayRate", Tooltip="Specifies default display frame rate for newly created level sequences; also defines frame locked frame rate where sequences are set to be frame locked. Examples: 30 fps, 120/1 (120 fps), 30000/1001 (29.97), 0.01s (10ms)."))`
- L30 _public member_ `FString DefaultTickResolution;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ConsoleVariable="LevelSequence.DefaultTickResolution", Tooltip="Specifies default tick resolution for newly created level sequences. Examples: 30 fps, 120/1 (120 fps), 30000/1001 (29.97), 0.01s (10ms)."))`
- L33 _public member_ `EUpdateClockSource DefaultClockSource;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ConsoleVariable="LevelSequence.DefaultClockSource", Tooltip="Specifies default clock source for newly created level sequences. Examples: 0: Tick, 1: Platform, 2: Audio, 3: RelativeTimecode, 4: Timecode, 5: Custom"))`
- L35 _public prototype_ `virtual void PostInitProperties() override;`
- L37 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LEVELSEQUENCE_API`

### `Source/Runtime/LevelSequence/Public/LevelSequenceShotMetaDataLibrary.h` (Public)


#### class `ULevelSequenceShotMetaDataLibrary`  
`class ULevelSequenceShotMetaDataLibrary : public UBlueprintFunctionLibrary`  
_L19-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Manages ULevelSequence meta data that is common for rating shots in cinematic workflows. Manages access to UMovieSceneShotsMetaData for ULevelSequences.
- L29 _public prototype_ `static bool GetIsNoGood(const ULevelSequence* InLevelSequence, bool& bOutNoGood);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets whether the user has marked this shot as no good. @return Whether the value was set by the user.
- L35 _public prototype_ `static bool GetIsFlagged(const ULevelSequence* InLevelSequence, bool& bOutIsFlagged);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets whether this was flagged by a user. @return Whether the value was set by the user.
- L41 _public prototype_ `static bool GetIsRecorded(const ULevelSequence* InLevelSequence, bool& bOutIsRecorded);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets whether this was recorded. @return Whether the value was set.
- L47 _public prototype_ `static bool GetIsSubSequence(const ULevelSequence* InLevelSequence, bool& bOutIsSubSequence);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets whether this was recorded as a subsequence. @return Whether the value was set.
- L53 _public prototype_ `static bool GetFavoriteRating(const ULevelSequence* InLevelSequence, int32& OutFavoriteRating);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets the favorite rating. The favorite rating is like a star rating, usually 1-3 if it was rated. @return Whether the value was set by the user.
- L57 _public prototype_ `static bool HasIsNoGood(const ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether the user has ever set a value for this property.
- L60 _public prototype_ `static bool HasIsFlagged(const ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether the user has ever set a value for this property.
- L63 _public prototype_ `static bool HasIsRecorded(const ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether IsRecorded has been set.
- L66 _public prototype_ `static bool HasIsSubSequence(const ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether IsSubSequence has been set.
- L69 _public prototype_ `static bool HasFavoriteRating(const ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether the user has ever set a value for this property.
- L73 _public prototype_ `static void SetIsNoGood(ULevelSequence* InLevelSequence, bool bInIsNoGood);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Sets whether the user has marked this shot as no good.
- L76 _public prototype_ `static void SetIsFlagged(ULevelSequence* InLevelSequence, bool bInIsFlagged);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Sets whether this was flagged by a user.
- L79 _public prototype_ `static void SetIsRecorded(ULevelSequence* InLevelSequence, bool bInIsRecorded);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Sets whether this sequence was recorded.
- L82 _public prototype_ `static void SetIsSubSequence(ULevelSequence* InLevelSequence, bool bInIsSubSequence);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Sets whether this is a subsequence.
- L85 _public prototype_ `static void SetFavoriteRating(ULevelSequence* InLevelSequence, int32 InFavoriteRating);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Sets the favorite rating. The favorite rating is like a star rating, usually 1-3 if it was rated.
- L89 _public prototype_ `static void ClearIsNoGood(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Clear the IsNoGood flag.
- L92 _public prototype_ `static void ClearIsFlagged(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Clear IsFlagged flag.
- L95 _public prototype_ `static void ClearIsRecorded(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Clear IsRecorded flag.
- L98 _public prototype_ `static void ClearIsSubSequence(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Clear IsSubSequence flag.
- L101 _public prototype_ `static void ClearFavoriteRating(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "Level Sequence")` — Clears the favorite rating.
- L105 _public prototype_ `static FName GetIsNoGoodAssetTag();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return The asset tag for the IsNoGood value.
- L108 _public prototype_ `static FName GetIsFlaggedAssetTag();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return The asset tag for the IsFlagged value.
- L111 _public prototype_ `static FName GetIsRecordedAssetTag();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return The asset tag for the IsRecorded value.
- L114 _public prototype_ `static FName GetIsSubSequenceAssetTag();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return The asset tag for the IsSubSequence value.
- L117 _public prototype_ `static FName GetFavoriteRatingAssetTag();` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return The asset tag for the FavoriteRating value.
- L124 _public prototype_ `static bool GetIsNoGoodByAssetData(const FAssetData& InAssetData, bool& bOutNoGood);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets whether the user has marked this shot as no good. @return Whether the value was set by the user.
- L130 _public prototype_ `static bool GetIsFlaggedByAssetData(const FAssetData& InAssetData, bool& bOutIsFlagged);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets whether this was flagged by a user. @return Whether the value was set by the user.
- L136 _public prototype_ `static bool GetIsRecordedByAssetData(const FAssetData& InAssetData, bool& bOutIsRecorded);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets whether this was recorded. @return Whether the value was set by the user.
- L142 _public prototype_ `static bool GetIsSubSequenceByAssetData(const FAssetData& InAssetData, bool& bOutIsSubSequence);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets whether this was recorded as a sub sequence. @return Whether the value was set by the user.
- L148 _public prototype_ `static bool GetFavoriteRatingByAssetData(const FAssetData& InAssetData, int32& OutFavoriteRating);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — Gets the favorite rating. The favorite rating is like a star rating, usually 1-3 if it was rated. @return Whether the value was set by the user.
- L152 _public prototype_ `static bool HasIsNoGoodByAssetData(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether the user has ever set a value for this property.
- L155 _public prototype_ `static bool HasIsFlaggedByAssetData(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether the user has ever set a value for this property.
- L158 _public prototype_ `static bool HasIsRecordedByAssetData(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether the user has ever set a value for this property.
- L161 _public prototype_ `static bool HasIsSubSequenceByAssetData(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether the user has ever set a value for this property.
- L164 _public prototype_ `static bool HasFavoriteRatingByAssetData(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "Level Sequence")` — @return Whether the user has ever set a value for this property.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEVELSEQUENCE_API`

### `Source/Runtime/LevelSequence/Public/LevelSequenceSpawnRegister.h` (Public)


#### class `FLevelSequenceSpawnRegister`  
`class FLevelSequenceSpawnRegister : public FMovieSceneSpawnRegister`  
_L20-39_
- inherits: `FMovieSceneSpawnRegister`
- desc: Movie scene spawn register that knows how to handle spawning objects (actors) for a level sequence
- L23 _public prototype_ `FLevelSequenceSpawnRegister();`
- L24 _public prototype_ `FLevelSequenceSpawnRegister(const FLevelSequenceSpawnRegister&);`
- L25 _public prototype_ `~FLevelSequenceSpawnRegister();`
- L29 _protected prototype_ `virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) override;` — ~ FMovieSceneSpawnRegister interface
- L30 _protected prototype_ `virtual void DestroySpawnedObject(UObject& Object, UMovieSceneSpawnableBindingBase* CustomSpawnableBinding) override;`
- L33 _protected prototype_ `virtual bool CanSpawnObject(UClass* InClass) const override;`
- L38 _protected member_ `TArray<TSharedRef<IMovieSceneObjectSpawner>> MovieSceneObjectSpawners;` — Extension object spawners

### `Source/Runtime/LevelSequence/Public/SequenceMediaController.h` (Public)


#### class `ALevelSequenceMediaController`  
`class ALevelSequenceMediaController : public AActor , public IMovieSceneCustomClockSource`  
_L21-94_
- reflection: `UCLASS(hideCategories=(Rendering, Physics, HLOD, Activation, Input, Collision), MinimalAPI)`
- inherits: `AActor,IMovieSceneCustomClockSource`
- desc: Replicated actor class that is responsible for instigating various cinematic assets (Media, Audio, Level Sequences) in a synchronized fasion
- L29 _public prototype_ `ALevelSequenceMediaController(const FObjectInitializer& Init);`
- L32 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category="Synchronization")`
- L38 _public function_ `UMediaComponent* GetMediaComponent() const` — `UFUNCTION(BlueprintPure, Category="Synchronization")` — Access this actor's media component
- L47 _public function_ `ALevelSequenceActor* GetSequence() const` — `UFUNCTION(BlueprintPure, Category="Synchronization")` — Access this actor's Level Sequence Actor
- L56 _public prototype_ `void SynchronizeToServer(float DesyncThresholdSeconds = 2.f);` — `UFUNCTION(BlueprintCallable, Category="Synchronization")` — Forcibly synchronize the sequence to the server's position if it has diverged by more than the specified threshold
- L60 _private prototype_ `void Client_Play();`
- L62 _private prototype_ `void Client_ConditionallyForceTime(float DesyncThresholdSeconds);`
- L66 _private prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;`
- L70 _private prototype_ `virtual void OnTick(float DeltaSeconds, float InPlayRate) override final;`
- L71 _private prototype_ `virtual void OnStartPlaying(const FQualifiedFrameTime& InStartTime) override final;`
- L72 _private prototype_ `virtual void OnStopPlaying(const FQualifiedFrameTime& InStopTime) override final;`
- L73 _private prototype_ `virtual FFrameTime OnRequestCurrentTime(const FQualifiedFrameTime& InCurrentTime, float InPlayRate) override final;`
- L78 _private prototype_ `void OnRep_ServerStartTimeSeconds();` — `UFUNCTION()`
- L82 _private member_ `TObjectPtr<ALevelSequenceActor> Sequence;` — `UPROPERTY(EditAnywhere, BlueprintGetter=GetSequence, Category="Synchronization")` — Pointer to the sequence actor to use for playback
- L86 _private member_ `TObjectPtr<UMediaComponent> MediaComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintGetter=GetMediaComponent, Category="Synchronization")` — Media component that contains the media player to synchronize with
- L90 _private member_ `float ServerStartTimeSeconds;` — `UPROPERTY(BlueprintReadOnly, Category="Synchronization", replicated, ReplicatedUsing=OnRep_ServerStartTimeSeconds, meta=(AllowPrivateAccess="true"))` — Replicated time at which the server started the sequence (taken from AGameStateBase::GetServerWorldTimeSeconds)
- L93 _private member_ `double SequencePositionSeconds;` — Time to use for the sequence playback position
