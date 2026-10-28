# Plugins / ActorSequence

- module root: `Plugins/MovieScene/ActorSequence/Source/ActorSequence`
- headers: 4; symbols: 68
- symbol kinds: class=3, delegate=1, enum=1, enumerator=3, function=8, macro=3, member=13, prototype=33, struct=3
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MovieScene, MovieSceneTracks, TimeManagement

### `Plugins/MovieScene/ActorSequence/Source/ActorSequence/Public/ActorSequence.h` (Public)


#### class `UActorSequence`  
`class UActorSequence : public UMovieSceneSequence`  
_L16-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental, DefaultToInstanced)`
- inherits: `UMovieSceneSequence`
- desc: Movie scene animation embedded within an actor.
- L22 _public prototype_ `UActorSequence(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;`
- L26 _public prototype_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;`
- L27 _public prototype_ `virtual void LocateBoundObjects(const FGuid& ObjectId, UObject* Context, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L28 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L29 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L30 _public prototype_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;`
- L31 _public function_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* Context) override`
- L32 _public function_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* Context) override`
- L33 _public prototype_ `virtual UObject* CreateDirectorInstance(TSharedRef<const FSharedPlaybackState> SharedPlaybackState, FMovieSceneSequenceID SequenceID) override;`
- L36 _public prototype_ `virtual FText GetDisplayName() const override;`
- L37 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L41 _public prototype_ `UBlueprint* GetParentBlueprint() const;`
- L44 _public prototype_ `bool IsEditable() const;`
- L49 _private prototype_ `virtual void PostInitProperties() override;`
- L55 _private member_ `TObjectPtr<UMovieScene> MovieScene;` — `UPROPERTY(Instanced)` — Pointer to the movie scene that controls this animation.
- L59 _private member_ `FActorSequenceObjectReferenceMap ObjectReferences;` — `UPROPERTY()` — Collection of object references.
- L65 _public function_ `DECLARE_EVENT_OneParam(UActorSequence, FOnInitialize, UActorSequence*) static FOnInitialize& OnInitializeSequence()` — Event that is fired to initialize default state for a sequence
- L69 _private member_ `static FOnInitialize OnInitializeSequenceEvent;`
- L75 _private member_ `bool bHasBeenInitialized;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ACTORSEQUENCE_API`
- L65 _delegate_ `DECLARE_EVENT_OneParam(UActorSequence, FOnInitialize, UActorSequence*) static FOnInitialize& OnInitializeSequence() { return OnInitializeSequenceEvent; } private: static FOnInitialize OnInitializeSequenceEvent;` — Event that is fired to initialize default state for a sequence

### `Plugins/MovieScene/ActorSequence/Source/ActorSequence/Public/ActorSequenceComponent.h` (Public)


#### class `UActorSequenceComponent`  
`class UActorSequenceComponent : public UActorComponent`  
_L20-74_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Experimental, ClassGroup=Sequence, hidecategories=(Collision, Cooking, Activation), meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Movie scene animation embedded within an actor.
- L26 _public prototype_ `UActorSequenceComponent(const FObjectInitializer& Init);`
- L28 _public function_ `UActorSequence* GetSequence() const`
- L33 _public function_ `UActorSequencePlayer* GetSequencePlayer() const`
- L40 _public prototype_ `void PlaySequence();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Calls the Play function on the SequencePlayer if its valid.
- L44 _public prototype_ `void PlaySequenceReverse();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Calls the PlayReverse function on the SequencePlayer if its valid.
- L48 _public prototype_ `void PauseSequence();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Calls the Pause function on the SequencePlayer if its valid.
- L52 _public prototype_ `void StopSequence();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Calls the Stop function on the SequencePlayer if its valid.
- L55 _public prototype_ `virtual void PostInitProperties() override;` — UActorComponent interface
- L56 _public prototype_ `virtual void BeginPlay() override;`
- L57 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L58 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L61 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L66 _protected member_ `FMovieSceneSequencePlaybackSettings PlaybackSettings;` — `UPROPERTY(EditAnywhere, Category="Playback", meta=(ShowOnlyInnerProperties))`
- L70 _protected member_ `TObjectPtr<UActorSequence> Sequence;` — `UPROPERTY(EditAnywhere, Instanced, Category=Animation)` — Embedded actor sequence data
- L73 _protected member_ `TObjectPtr<UActorSequencePlayer> SequencePlayer;` — `UPROPERTY(transient, BlueprintReadOnly, Category=Animation)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ACTORSEQUENCE_API`

### `Plugins/MovieScene/ActorSequence/Source/ActorSequence/Public/ActorSequenceObjectReference.h` (Public)


#### enum `EActorSequenceObjectReferenceType`  
`enum class EActorSequenceObjectReferenceType : uint8`  
_L11-19_
- reflection: `UENUM()`
- L14 _public enumerator_ `ContextActor` — The reference relates to the context actor
- L16 _public enumerator_ `ExternalActor` — The reference relates to an actor outside of the context actor actor
- L18 _public enumerator_ `Component` — The reference relates to a component

#### struct `FActorSequenceObjectReference`  
`struct FActorSequenceObjectReference`  
_L25-91_
- reflection: `USTRUCT()`
- desc: An external reference to an level sequence object, resolvable through an arbitrary context.
- L32 _public function_ `FActorSequenceObjectReference() : Type(EActorSequenceObjectReferenceType::ContextActor)` — Default construction to a null reference
- L41 _public prototype_ `static FActorSequenceObjectReference CreateForComponent(UActorComponent* InComponent);` — Generates a new reference to an object within a given context. @param InComponent The component to create a reference for
- L48 _public prototype_ `static FActorSequenceObjectReference CreateForActor(AActor* InActor, AActor* ResolutionContext);` — Generates a new reference to an object within a given context. @param InActor The actor to create a reference for
- L53 _public prototype_ `static FActorSequenceObjectReference CreateForContextActor();` — Generates a new reference to the root actor.
- L58 _public function_ `bool IsValid() const` — Check whether this object reference is valid or not
- L68 _public prototype_ `UObject* Resolve(AActor* SourceActor) const;` — Resolve this reference from the specified source actor @return The object
- L82 _private member_ `EActorSequenceObjectReferenceType Type;` — `UPROPERTY()` — The type of the binding
- L86 _private member_ `FGuid ActorId;` — `UPROPERTY()` — The ID of the actor - if this is set, we're either the owner actor, or an object outside of the context
- L90 _private member_ `FString PathToComponent;` — `UPROPERTY()` — Path to the component from its owner actor

#### struct `FActorSequenceObjectReferences`  
`struct FActorSequenceObjectReferences`  
_L94-100_
- reflection: `USTRUCT()`
- L99 _public member_ `TArray<FActorSequenceObjectReference> Array;` — `UPROPERTY()`

#### struct `FActorSequenceObjectReferenceMap`  
`struct FActorSequenceObjectReferenceMap`  
_L103-144_
- reflection: `USTRUCT()`
- L111 _public prototype_ `bool HasBinding(const FGuid& ObjectId) const;` — Check whether this map has a binding for the specified object id @return true if this map contains a binding for the id, false otherwise
- L118 _public prototype_ `void RemoveBinding(const FGuid& ObjectId);` — Remove a binding for the specified ID @param ObjectId	The ID to remove
- L126 _public prototype_ `void CreateBinding(const FGuid& ObjectId, const FActorSequenceObjectReference& ObjectReference);` — Create a binding for the specified ID @param ObjectId				The ID to associate the component with @param ObjectReference	The component reference to bind
- L135 _public prototype_ `void ResolveBinding(const FGuid& ObjectId, AActor* ParentActor, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const;` — Resolve a binding for the specified ID using a given context @param ObjectId		The ID to associate the object with @param ParentActor	The parent actor to resolve within @param OutObjects	Container to populate with bound components
- L140 _private member_ `TArray<FGuid> BindingIds;` — `UPROPERTY()`
- L143 _private member_ `TArray<FActorSequenceObjectReferences> References;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L73 _function_ `friend bool operator==(const FActorSequenceObjectReference& A, const FActorSequenceObjectReference& B)` — Equality comparator

### `Plugins/MovieScene/ActorSequence/Source/ActorSequence/Public/ActorSequencePlayer.h` (Public)


#### class `UActorSequencePlayer`  
`class UActorSequencePlayer : public UMovieSceneSequencePlayer`  
_L16-27_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneSequencePlayer`
- desc: UActorSequencePlayer is used to actually "play" an actor sequence asset at runtime.
- L25 _protected prototype_ `virtual UObject* GetPlaybackContext() const override;`
- L26 _protected prototype_ `virtual TArray<UObject*> GetEventContexts() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ACTORSEQUENCE_API`
