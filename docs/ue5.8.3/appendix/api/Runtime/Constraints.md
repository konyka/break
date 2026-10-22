# Runtime / Constraints

- module root: `Source/Runtime/Experimental/Animation/Constraints`
- headers: 15; symbols: 580
- symbol kinds: class=15, delegate=4, enum=6, enumerator=17, function=25, macro=3, member=91, namespace=17, prototype=366, struct=26, typedef=10
- PublicDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine, MovieScene, Slate, SlateCore

### `Source/Runtime/Experimental/Animation/Constraints/Private/ConstraintSubsystem.h` (Private)


#### struct `FConstraintsInWorld`  
`struct FConstraintsInWorld`  
_L18-36_
- reflection: `USTRUCT()`
- L24 _public member_ `TWeakObjectPtr<UWorld> World;` — `UPROPERTY(transient)`
- L27 _public member_ `mutable TArray<TWeakObjectPtr<UTickableConstraint>> Constraints;` — `UPROPERTY(transient)`
- L29 _public prototype_ `void RemoveConstraints(UWorld* World);`
- L31 _public prototype_ `FConstraintsEvaluationGraph& GetEvaluationGraph();`
- L32 _public prototype_ `void InvalidateGraph();`
- L35 _private member_ `TSharedPtr<FConstraintsEvaluationGraph> EvaluationGraph = nullptr;`

#### class `UConstraintSubsystem`  
`class UConstraintSubsystem: public UEngineSubsystem`  
_L40-138_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- L46 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FOnConstraintAddedToSystem, UConstraintSubsystem, OnConstraintAddedToSystem_BP, UConstraintSubsystem*, Mananger, UTickableConstraint*, Constraint);` — Dynamic blueprintable delegates for knowing when a constraints are added or deleted
- L47 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_ThreeParams(FOnConstraintRemovedFromSystem, UConstraintSubsystem, OnConstraintRemovedFromSystem_BP, UConstraintSubsystem*, Mananger, UTickableConstraint*, Constraint, bool, bDoNotCompensate);`
- L49 _public prototype_ `UConstraintSubsystem();`
- L51 _public prototype_ `static UConstraintSubsystem* Get();`
- L52 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L53 _public prototype_ `virtual void Deinitialize() override;`
- L56 _public prototype_ `void SetConstraintDependencies( FConstraintTickFunction* InFunctionToTickBefore, FConstraintTickFunction* InFunctionToTickAfter);` — Set tick dependencies between two constraints.
- L60 _public prototype_ `TArray<TWeakObjectPtr<UTickableConstraint>> GetConstraints(const UWorld* InWorld) const;`
- L61 _public prototype_ `const TArray<TWeakObjectPtr<UTickableConstraint>>& GetConstraintsArray(const UWorld* InWorld) const;`
- L63 _public prototype_ `void AddConstraint(UWorld* InWorld, UTickableConstraint* InConstraint);`
- L64 _public prototype_ `void RemoveConstraint(UWorld* InWorld, UTickableConstraint* InConstraint, bool bDoNoCompensate);`
- L65 _public prototype_ `bool HasConstraint(UWorld* InWorld, UTickableConstraint* InConstraint) const;`
- L67 _public prototype_ `FConstraintsEvaluationGraph& GetEvaluationGraph(UWorld* InWorld);`
- L69 _public prototype_ `void InvalidateConstraints();`
- L72 _public prototype_ `virtual void PostEditUndo() override;`
- L77 _public member_ `FOnConstraintAddedToSystem OnConstraintAddedToSystem_BP;` — `UPROPERTY(BlueprintAssignable, Category = Constraints, meta = (DisplayName = "OnConstraintAdded"))` — BP Delegate fired when constraints are added
- L81 _public member_ `FOnConstraintRemovedFromSystem OnConstraintRemovedFromSystem_BP;` — `UPROPERTY(BlueprintAssignable, Category = Constraints, meta = (DisplayName = "OnConstraintRemoved"))` — BP Delegate fired when constraints are removed
- L84 _public prototype_ `UTickableConstraint* GetConfig(const UClass* InConstraintClass);` — Returns a UTickableConstraint instance that can be used as a configuration constraints.
- L88 _public function_ `template<typename ConstraintType> void RegisterConfig()` — Register a new constraint class type and allocate a new configuration constraints for that class.
- L110 _private member_ `TArray<FConstraintsInWorld> ConstraintsInWorld;` — `UPROPERTY(transient)`
- L113 _private member_ `static FDelegateHandle OnWorldInitHandle;` — handles for handling world creation init and teardown
- L114 _private prototype_ `static void OnWorldInit(UWorld* World, const UWorld::InitializationValues IVS);`
- L116 _private member_ `static FDelegateHandle OnWorldCleanupHandle;`
- L117 _private prototype_ `static void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);`
- L120 _private member_ `static FDelegateHandle OnPostGarbageCollectHandle;` — handle for handling GC
- L121 _private prototype_ `static void OnPostGarbageCollect();`
- L123 _private prototype_ `void InitializeInternal();`
- L125 _private member_ `mutable bool bNeedsCleanup = false;`
- L127 _private prototype_ `const FConstraintsInWorld* ConstraintsInWorldFind(const UWorld* InWorld) const;`
- L128 _private prototype_ `FConstraintsInWorld* ConstraintsInWorldFind(const UWorld* InWorld);`
- L129 _private prototype_ `FConstraintsInWorld& ConstraintsInWorldFindOrAdd(UWorld* InWorld);`
- L131 _private prototype_ `int32 GetConstraintsInWorldIndex(const UWorld* InWorld) const;`
- L133 _private prototype_ `void CleanupInvalidConstraints() const;`
- L137 _private member_ `TMap<TObjectPtr<UClass>, TObjectPtr<UTickableConstraint>> ConstraintsConfig;` — `UPROPERTY(transient)` — Per UClass constraint configuration instance.

### `Source/Runtime/Experimental/Animation/Constraints/Public/ConstraintChannel.h` (Public)


#### struct `FMovieSceneConstraintChannel`  
`struct FMovieSceneConstraintChannel : public FMovieSceneBoolChannel`  
_L22-67_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneBoolChannel`
- L26 _public function_ `FMovieSceneConstraintChannel()`
- L33 _public function_ `virtual TMovieSceneChannelData<bool> GetData() override` — Access a mutable interface for this channel's data @return An object that is able to manipulate this channel's data
- L43 _public function_ `virtual TMovieSceneChannelData<const bool> GetData() const override` — Access a constant interface for this channel's data @return An object that is able to interrogate this channel's data
- L55 _public prototype_ `virtual bool Evaluate(FFrameTime InTime, bool& OutValue) const override;` — Evaluate this channel @param InTime     The time to evaluate at @param OutValue   A value to receive the result @return true if the channel was evaluated successfully, false otherwise
- L61 _public prototype_ `bool IsInfinite() const;` — Checks whether this constraint channel is infinite @return true if there are no keys and the default value is set to true.
- L64 _public typedef_ `using ExtraLabelFunction = TFunction< FString() >;`
- L65 _public member_ `ExtraLabelFunction ExtraLabel;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneConstraintChannel> : public TStructOpsTypeTraitsBase2<FMovieSceneConstraintChannel>`  
_L70-73_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneConstraintChannel>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L72-72_

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneConstraintChannel> : TMovieSceneChannelTraitsBase<FMovieSceneConstraintChannel>`  
_L77-87_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneConstraintChannel>`
- L84 _public typedef_ `typedef TMovieSceneExternalValue<bool> ExtendedEditorDataType;` — Byte channels can have external values (ie, they can get their values from external objects for UI purposes)

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L79-79_

#### struct `FConstraintAndActiveChannel`  
`struct FConstraintAndActiveChannel`  
_L102-119_
- reflection: `USTRUCT()`
- L106 _public function_ `FConstraintAndActiveChannel()`
- L107 _public function_ `FConstraintAndActiveChannel(const TObjectPtr<UTickableConstraint>& InConstraint) : ConstraintCopyToSpawn(InConstraint)`
- L110 _public function_ `TObjectPtr<UTickableConstraint> GetConstraint() const`
- L111 _public function_ `void SetConstraint(UTickableConstraint* InConstraint)`
- L114 _public member_ `FMovieSceneConstraintChannel ActiveChannel;` — `UPROPERTY()`
- L118 _private member_ `TObjectPtr<UTickableConstraint> ConstraintCopyToSpawn;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L72 _enumerator_ `enum { WithStructuredSerializeFromMismatchedTag = true };` (scope `TStructOpsTypeTraits::__anoneec93a7e0103`)
- L79 _enumerator_ `enum { SupportsDefaults = false }; #if WITH_EDITOR typedef TMovieSceneExternalValue<bool> ExtendedEditorDataType; #endif` (scope `TMovieSceneChannelTraits::__anoneec93a7e0203`)

### `Source/Runtime/Experimental/Animation/Constraints/Public/ConstraintsActor.h` (Public)


#### class `AConstraintsActor`  
`class AConstraintsActor : public AActor`  
_L16-47_
- reflection: `UCLASS(NotPlaceable, MinimalAPI)`
- inherits: `AActor`
- L22 _public prototype_ `AConstraintsActor(const FObjectInitializer& ObjectInitializer);` — Sets default values for this actor's properties
- L23 _public prototype_ `virtual ~AConstraintsActor();`
- L25 _public prototype_ `virtual void BeginDestroy() override;`
- L26 _public prototype_ `virtual void Destroyed() override;`
- L28 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L31 _public prototype_ `virtual void PostEditUndo() override;`
- L36 _protected prototype_ `virtual void BeginPlay() override;` — Called when the game starts or when spawned
- L40 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Called every frame
- L43 _public member_ `TObjectPtr<UConstraintsManager> ConstraintsManager = nullptr;` — `UPROPERTY()`
- L46 _private prototype_ `void RegisterConstraintsTickFunctions() const;`

### `Source/Runtime/Experimental/Animation/Constraints/Public/ConstraintsEvaluation.h` (Public)


#### struct `FSequentialConstraintsEvaluator`  
`struct FSequentialConstraintsEvaluator`  
_L19-26_
- L21 _public prototype_ `FSequentialConstraintsEvaluator(USceneComponent* InInitialComponent = nullptr);`
- L22 _public prototype_ `void DoEvaluate(UTickableConstraint* InConstraint, const FConstraintTickFunction* InConstraintTickFunction = nullptr);`
- L25 _private member_ `USceneComponent* LastMarkedForEvaluation = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CONSTRAINTS_API`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Anim` (scope `UE`)
- L28 _namespace_ `namespace Constraints` (scope `UE::Anim`)
- L31 _prototype_ `bool UseFastEvaluation();` (scope `UE::Anim::Constraints`) — Whether the fast sequential evaluation is enabled.
- L34 _prototype_ `void EvaluateConstraints(TConstArrayView<TWeakObjectPtr<UTickableConstraint>> InConstraints);` (scope `UE::Anim::Constraints`) — Evaluate all the constraints sequentially. this will use a faster evaluation scheme UseFastEvaluation() is true.

### `Source/Runtime/Experimental/Animation/Constraints/Public/ConstraintsEvaluationGraph.h` (Public)


#### struct `FConstraintNode`  
`struct FConstraintNode`  
_L18-37_
- L21 _public member_ `FGuid ConstraintID;` — Constraint data
- L22 _public member_ `FConstraintTickFunction* ConstraintTick = nullptr;`
- L25 _public member_ `int32 NodeIndex = INDEX_NONE;` — Internal indices for quick navigation through the nodes and constraints data structures
- L26 _public member_ `int32 ConstraintIndex = INDEX_NONE;`
- L29 _public member_ `TSet<uint32> Parents;` — internal hierarchy representing dependencies at the nodes level (indices here represent the nodes' NodeIndex)
- L30 _public member_ `TSet<uint32> Children;`
- L33 _public member_ `bool bMarkedForEvaluation = false;` — Whether this node needs to be evaluated on the next flush.
- L36 _public member_ `bool bEvaluating = false;` — Whether this node is currently being evaluated (used to avoid re-entrant evaluations).

#### struct `FConstraintsEvaluationGraph`  
`struct FConstraintsEvaluationGraph: public TSharedFromThis<FConstraintsEvaluationGraph>`  
_L44-109_
- inherits: `TSharedFromThis<FConstraintsEvaluationGraph>`
- L47 _public function_ `explicit FConstraintsEvaluationGraph(const FConstraintsInWorld* InConstraintsInWorld) : ConstraintsInWorld(*InConstraintsInWorld)`
- L55 _public prototype_ `void MarkForEvaluation(const TWeakObjectPtr<UTickableConstraint>& InConstraint);` — Marks the constraint for evaluation. Note that it will only be evaluated after FlushPendingEvaluations has been called. This makes it possible to tag several constraints and evaluate the graph only once.
- L58 _public prototype_ `void FlushPendingEvaluations();` — Evaluates constraints marked for evaluation + their dependencies.
- L61 _public prototype_ `void InvalidateData();` — Invalidates internal data so that the graph will be rebuilt on request.
- L64 _public prototype_ `void Rebuild();` — Rebuilds the full graph taking constraints tick dependencies into account.
- L67 _public prototype_ `bool IsPendingEvaluation() const;` — Should the graph be evaluated ?
- L70 _public prototype_ `bool GetSortedConstraints(TArray<TWeakObjectPtr<UTickableConstraint>>& OutConstraints);` — Get Sorted Constraints
- L82 _private prototype_ `FConstraintsEvaluationGraph(FConstraintsEvaluationGraph&& InOther) = default;`
- L83 _private prototype_ `FConstraintsEvaluationGraph(const FConstraintsEvaluationGraph& InOther) = delete;`
- L84 _private prototype_ `FConstraintsEvaluationGraph& operator=(const FConstraintsEvaluationGraph& InOther) = delete;`
- L87 _private prototype_ `FConstraintNode& GetNode(const TWeakObjectPtr<UTickableConstraint>& InConstraint);` — Get or create a new node in the graph that wraps that constraint.
- L90 _private prototype_ `FConstraintNode* FindNode(const TWeakObjectPtr<UTickableConstraint>& InConstraint);` — Returns the node wrapping that constraint if any.
- L93 _private prototype_ `void Evaluate(FConstraintNode* InNode);` — Evaluates InNode if its tick function is enabled + evaluates its children recursively.
- L96 _private prototype_ `void Dump() const;` — Dumps the current state of the graph.
- L99 _private member_ `TArray<FConstraintNode> Nodes;` — Array of constraint wrappers.
- L102 _private member_ `const FConstraintsInWorld& ConstraintsInWorld;` — References to the actual stored data.
- L105 _private member_ `EGraphState State = InvalidData;` — Current graph state.
- L108 _private member_ `FSequentialConstraintsEvaluator SequentialEvaluator;` — Constraints sequential evaluator used if the fast evaluation scheme is enabled.

#### enum `FConstraintsEvaluationGraph::EGraphState`  
`enum EGraphState`  
_L74-80_
- L76 _public enumerator_ `InvalidData = 0` — Invalid data
- L77 _public enumerator_ `ReadyForEvaluation` — Internal data has been built and is ready for evaluation
- L78 _public enumerator_ `PendingEvaluation` — Some constraints has been marked for evaluation
- L79 _public enumerator_ `Flushing` — The graph is currently being evaluated

#### Free symbols / members of external scopes

- L111 _namespace_ `namespace UE`
- L111 _namespace_ `namespace Constraints` (scope `UE`)
- L111 _namespace_ `namespace Graph` (scope `UE::Constraints`)
- L114 _typedef_ `using ConstraintPtr = TWeakObjectPtr<UTickableConstraint>;` (scope `UE::Constraints::Graph`)
- L121 _prototype_ `void BuildGraph(UWorld* InWorld, const TArrayView<const ConstraintPtr>& InConstraints, TArray<FConstraintNode>& OutNodes);` (scope `UE::Constraints::Graph`) — Builds a directed graph from a constraints array using the tick prerequisites to define dependencies. @param InWorld - The UWorld in which tick functions are registered. @param InConstraints - An array of constraints. @param OutNodes - A ordered data structure storing constraints' dependencies.
- L127 _prototype_ `void SortConstraints(UWorld* InWorld, TArray<ConstraintPtr>& InOutConstraints);` (scope `UE::Constraints::Graph`) — Sorts the constraint array by building a directed graph from it, using the tick prerequisites to define dependencies. @param InWorld - The UWorld in which tick functions are registered. @param InOutConstraints - An array of constraints that will be re-ordered from the constraints' dependencies.

### `Source/Runtime/Experimental/Animation/Constraints/Public/ConstraintsManager.h` (Public)


#### struct `FConstraintTickFunction`  
`struct FConstraintTickFunction : public FTickFunction`  
_L24-56_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- L28 _public prototype_ `FConstraintTickFunction();`
- L29 _public prototype_ `~FConstraintTickFunction();`
- L31 _public prototype_ `FConstraintTickFunction(const FConstraintTickFunction& In);`
- L33 _public prototype_ `virtual void ExecuteTick( float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;` — Begin FTickFunction Interface
- L39 _public prototype_ `virtual FString DiagnosticMessage() override;`
- L43 _public typedef_ `using ConstraintFunction = TFunction<void()>;` — Callable function that represents the actual constraint.
- L46 _public prototype_ `void RegisterFunction(ConstraintFunction InConstraint);` — Register a callable function.
- L49 _public prototype_ `void EvaluateFunctions() const;` — Register a callable function.
- L52 _public member_ `TWeakObjectPtr<UTickableConstraint> Constraint;` — Weak ptr to the Constraint holding this tick function.
- L55 _public member_ `TArray<ConstraintFunction> ConstraintFunctions;` — The list of the constraint functions that will be called within the tick function.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FConstraintTickFunction> : public TStructOpsTypeTraitsBase2<FConstraintTickFunction>`  
_L59-65_
- inherits: `TStructOpsTypeTraitsBase2<FConstraintTickFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L62-64_

#### class `UTickableConstraint`  
`class UTickableConstraint : public UObject`  
_L73-154_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L78 _public function_ `UTickableConstraint()`
- L79 _public prototype_ `virtual ~UTickableConstraint() = default;`
- L82 _public prototype_ `virtual FConstraintTickFunction::ConstraintFunction GetFunction() const PURE_VIRTUAL(GetFunction, return {};);` — Returns the actual function that the tick function needs to evaluate.
- L85 _public prototype_ `virtual void Evaluate(bool bTickHandlesAlso = false) const;` — Evaluates the constraint in a context where it's mot done thru the ConstraintTick's tick function.
- L88 _public prototype_ `virtual bool IsValid(const bool bDeepCheck = true) const PURE_VIRTUAL(IsValid, return false;);` — Whether or not it's valid for example it may not be fully loaded, missing handles or set to not be valid
- L90 _public prototype_ `virtual void SetActive(const bool bIsActive);` — Sets the Active value and enable/disable the tick function.
- L93 _public prototype_ `virtual bool IsFullyActive() const;` — Get whether or not it's fully active, it's set to active and all pieces are set up,e.g. objects really exist that are being constrainted
- L95 _public prototype_ `virtual bool HasBoundObjects() const PURE_VIRTUAL(HasBoundObjects, return false;);` — If true it contains objects bound to an external system, like sequencer so we don't do certain things, like remove constraints when they don't resolve
- L97 _public prototype_ `virtual void ResolveBoundObjects(FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState, UObject* SubObject = nullptr) PURE_VIRTUAL(ResolveBoundObjects);` — Resolve the bound objects so that any object it references are resovled and correctly set up
- L100 _public prototype_ `virtual uint32 GetTargetHash() const PURE_VIRTUAL(GetTargetHash, return 0;);` — @todo document
- L102 _public prototype_ `virtual bool ReferencesObject(TWeakObjectPtr<UObject> InObject) const PURE_VIRTUAL(ReferencesObject, return false;);` — Whether or not this object references this object. If it HasBoundObjects you should ResolveBoundObjects if you expect this to be up to date
- L104 _public prototype_ `virtual UTickableConstraint* Duplicate(UObject* NewOuter) const;` — Create duplicate with new Outer
- L106 _public prototype_ `virtual void InitConstraint(UWorld * InWorld) PURE_VIRTUAL(UTickableConstraint::InitConstraint);` — Initialize and register the constraint with that world
- L108 _public prototype_ `virtual void TeardownConstraint(UWorld* InWorld) PURE_VIRTUAL(UTickableConstraint::DeInitConstraint);` — Teardown and unregister the constraint with that world
- L110 _public prototype_ `virtual void AddedToWorld(UWorld* InWorld) PURE_VIRTUAL(UTickableConstraint::AddedToWorld);`
- L113 _public prototype_ `FConstraintTickFunction& GetTickFunction(const UWorld* InWorld);` — Get Tick function in that world
- L114 _public prototype_ `const FConstraintTickFunction& GetTickFunction(const UWorld* InWorld) const;`
- L117 _public prototype_ `FConstraintTickFunction* FindTickFunction(const UWorld* InWorld) const;` — Returns the tick function registrered in the world's current level if any (assuming both world and current leve are valid)
- L120 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L121 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L122 _public prototype_ `virtual void PostInitProperties() override;`
- L127 _public prototype_ `virtual FString GetLabel() const;` — Returns the constraint's label used for UI.
- L128 _public prototype_ `virtual FString GetFullLabel() const;`
- L131 _public prototype_ `virtual FString GetTypeLabel() const;` — Returns the constraint's type label used for UI.
- L134 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject editor only interface
- L135 _public prototype_ `virtual void PostEditUndo() override;`
- L141 _public member_ `bool Active = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active State", Category="Constraint")` — @todo documentation.
- L144 _public member_ `bool bValid = false;` — `UPROPERTY()`
- L148 _public member_ `FGuid ConstraintID;` — Unique id to be used to fine constraint in a particular world, may be shared
- L153 _protected member_ `mutable TMap<TWeakObjectPtr<ULevel>, TUniquePtr<FConstraintTickFunction>, TInlineSetAllocator<4>> ConstraintTicks;` — Tick function that will be registered and evaluated.

#### class `UConstraintsManager`  
`class UConstraintsManager : public UObject`  
_L164-226_
- reflection: `UCLASS(BLUEPRINTABLE, MinimalAPI)`
- inherits: `UObject`
- L169 _public typedef_ `using ConstraintPtr = TObjectPtr<UTickableConstraint>;`
- L172 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FOnConstraintAdded, UConstraintsManager, OnConstraintAdded_BP, UConstraintsManager*, Mananger, UTickableConstraint*, Constraint);` — Dynamic blueprintable delegates for knowing when a constraints are added or deleted
- L173 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_ThreeParams(FOnConstraintRemoved, UConstraintsManager, OnConstraintRemoved_BP, UConstraintsManager*, Mananger, UTickableConstraint*, Constraint, bool, bDoNotCompensate);`
- L176 _public prototype_ `UConstraintsManager();`
- L177 _public prototype_ `virtual ~UConstraintsManager();`
- L180 _public prototype_ `virtual void PostLoad() override;` — UObjects
- L182 _public prototype_ `void Init(UWorld* InWorld);`
- L183 _public prototype_ `void Clear(UWorld* World);`
- L185 _public function_ `void RemoveStaticConstraint(UTickableConstraint* InConstraint)`
- L186 _public function_ `bool IsStaticConstraint(UTickableConstraint* InConstraint) const`
- L189 _public prototype_ `static UConstraintsManager* Find(const UWorld* InWorld);` — Find the existing Constraints Manager.
- L193 _private prototype_ `static UConstraintsManager* Get(UWorld* InWorld);` — Get the existing Constraints Manager if existing or create a new one.
- L199 _public member_ `FOnConstraintAdded OnConstraintAdded_BP;` — `UPROPERTY(BlueprintAssignable, Category = Constraints, meta = (DisplayName = "OnConstraintAdded"))` — BP Delegate fired when constraints are added
- L203 _public member_ `FOnConstraintRemoved OnConstraintRemoved_BP;` — `UPROPERTY(BlueprintAssignable, Category = Constraints, meta = (DisplayName = "OnConstraintRemoved"))` — BP Delegate fired when constraints are removed
- L209 _private member_ `FDelegateHandle OnActorDestroyedHandle;` — @todo document
- L210 _private prototype_ `void OnActorDestroyed(AActor* InActor);`
- L212 _private prototype_ `void RegisterDelegates(UWorld* World);`
- L213 _private prototype_ `void UnregisterDelegates(UWorld* World);`
- L217 _private prototype_ `void Dump() const;` — @todo document
- L222 _private member_ `TArray< TObjectPtr<UTickableConstraint> > Constraints;` — `UPROPERTY()` — For 5.4, this now just contains all of the static constraints. Other constraints will exist in the subsystem and owned by the section

#### enum `EConstraintsManagerNotifyType`  
`enum class EConstraintsManagerNotifyType`  
_L233-240_
- L235 _public enumerator_ `ConstraintAdded`
- L236 _public enumerator_ `ConstraintRemoved` — ConstraintAdded,					  A new constraint has been added.
- L237 _public enumerator_ `ConstraintRemovedWithCompensation` — ConstraintRemoved,					  A constraint has been removed.
- L238 _public enumerator_ `ManagerUpdated` — ConstraintRemovedWithCompensation,	  A constraint has been removed and needs compensation.
- L239 _public enumerator_ `GraphUpdated` — ManagerUpdated,						  The manager has been updated/reset.

#### class `FConstraintsManagerController`  
`class FConstraintsManagerController`  
_L244-355_
- L249 _public member_ `static bool bDoNotRemoveConstraint;` — Static to control if we should remove constraints or not, may not want to do some when compensating since we may be deleting spawnables while doing so
- L251 _public prototype_ `static FConstraintsManagerController& Get(UWorld* InWorld);` — Get and Set Controller acive in this world
- L255 _public prototype_ `template< typename TConstraint > TConstraint* AllocateConstraintT(const FName& InBaseName, const bool bUseDefault = false) const;` — Allocates a new constraint with the constraints manager as the owner.
- L258 _public prototype_ `bool AddConstraint(UTickableConstraint* InConstraint) const;` — Add this constraint to the manager
- L261 _public prototype_ `UTickableConstraint* AddConstraintFromCopy(UTickableConstraint* CopyOfConstraint) const;` — Make a copy of this constraint and add it to the manager, returns the copy mode if it was added
- L264 _public prototype_ `int32 GetConstraintIndex(const FGuid& InGuid) const;` — Get the index of the given constraint's ID.
- L267 _public prototype_ `bool RemoveConstraint(const int32 InConstraintIndex, bool bDoNotCompensate = false);` — Remove the constraint at the given index.
- L270 _public prototype_ `bool RemoveConstraint(UTickableConstraint* InConstraint, bool bDoNotCompensate = false);` — Remove constraint by ptr
- L273 _public prototype_ `bool UnregisterConstraint(UTickableConstraint* InConstraint);` — Disable a constraint and remove it from the subsystem.
- L276 _public prototype_ `bool RemoveAllConstraints(bool bDoNotCompensate = false);` — Remove All Constraints
- L279 _public prototype_ `UTickableConstraint* GetConstraint(const FGuid& InGuid) const;` — Returns the constraint based on it's ID within the manager's constraints array.
- L282 _public prototype_ `UTickableConstraint* GetConstraint(const int32 InConstraintIndex) const;` — Returns the constraint based on it's index within the manager's constraints array.
- L285 _public prototype_ `const TArray< TWeakObjectPtr<UTickableConstraint> >& GetConstraintsArray() const;` — Get read-only access to the array of constraints.
- L288 _public prototype_ `TArray< TWeakObjectPtr<UTickableConstraint> > GetAllConstraints(const bool bSorted = false) const;` — Returns systems' constraints array (sorted if needed).
- L291 _public prototype_ `TArray< TWeakObjectPtr<UTickableConstraint> > GetStaticConstraints(const bool bSorted = false) const;` — Returns the static/non-animated constraints
- L295 _public prototype_ `template <typename Predicate> TArray< TWeakObjectPtr<UTickableConstraint> > GetConstraintsByPredicate(Predicate Pred, const bool bSorted = false) const;` — Returns a filtered constraints array checking if the predicate for each element is true.
- L298 _public prototype_ `TArray< TWeakObjectPtr<UTickableConstraint> > GetParentConstraints( const uint32 InTargetHash, const bool bSorted = false) const;` — Get parent constraints of the specified child. If bSorted is true, then the constraints will be sorted by dependency.
- L303 _public prototype_ `void SetConstraintsDependencies( const FName& InNameToTickBefore, const FName& InNameToTickAfter) const;` — Set dependencies between two constraints.
- L307 _public prototype_ `void SetConstraintsDependencies( const FGuid& InGuidToTickBefore, const FGuid& InGuidToTickAfter) const;`
- L312 _public prototype_ `void EvaluateAllConstraints() const;` — Go through each constraint in order and evaluate and tick them
- L316 _public prototype_ `bool DoesExistInAnyWorld(UTickableConstraint* InConstraint);` — `UE_DEPRECATED(5.7, "Function is no longer needed.")` — when PIEing/Simulating it's possible that the constraint isn't in the active manager but still lives
- L319 _public prototype_ `void StaticConstraintCreated(UWorld* InWorld, UTickableConstraint* InConstraint);` — `UE_DEPRECATED(5.7, "Function is no longer needed.")`
- L322 _public prototype_ `void StaticConstraintCreated(UTickableConstraint* InConstraint);` — If a static constraint is created, we call this, which stores it to the manager/actor
- L326 _private prototype_ `int32 GetConstraintIndex(const FName& InConstraintName) const;` — Get the index of the given constraint's name.
- L329 _private prototype_ `UConstraintsManager* GetManager();` — Find the existing Constraints Manager in World or create a new one.
- L332 _private prototype_ `UConstraintsManager* FindManager() const;` — Find the existing Constraints Manager in World.
- L335 _private prototype_ `void DestroyManager() const;` — Destroy the ConstraintsManager from the World.
- L338 _private member_ `UWorld* World = nullptr;` — The World that holds the ConstraintsManagerActor.
- L342 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSceneComponentConstrained, USceneComponent* );` — Delegate that's fired when a scene component is constrained, this is needed to make sure things like gizmo's get updated after the constraint tick happens
- L343 _public prototype_ `static FOnSceneComponentConstrained& OnSceneComponentConstrained();`
- L346 _public prototype_ `static FConstraintsManagerNotifyDelegate& GetNotifyDelegate();` — Delegate to trigger changes in the constraints manager.
- L349 _public prototype_ `static void Notify(EConstraintsManagerNotifyType InNotifyType, UObject* InObject);` — Notify from changes in the constraints manager.
- L352 _public prototype_ `void MarkConstraintForEvaluation(UTickableConstraint* InConstraint) const;` — Evaluation graph API.
- L353 _public prototype_ `void InvalidateEvaluationGraph() const;`
- L354 _public prototype_ `void FlushEvaluationGraph() const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieScene` (scope `UE`)
- L63 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon229a39b30103`)
- L242 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FConstraintsManagerNotifyDelegate, EConstraintsManagerNotifyType , UObject* );`
- L242 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FConstraintsManagerNotifyDelegate, EConstraintsManagerNotifyType , UObject* );`
- L342 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSceneComponentConstrained, USceneComponent* );` — Delegate that's fired when a scene component is constrained, this is needed to make sure things like gizmo's get updated after the constraint tick happens

### `Source/Runtime/Experimental/Animation/Constraints/Public/ConstraintsManager.inl` (Public)


#### Free symbols / members of external scopes

- L10 _function_ `template< typename TConstraint > TConstraint* FConstraintsManagerController::AllocateConstraintT(const FName& InBaseName, const bool bUseDefault) const` (scope `FConstraintsManagerController`)
- L23 _function_ `` (scope `FConstraintsManagerController::AllocateConstraintT`)
- L38 _function_ `template <typename Predicate> TArray< TWeakObjectPtr<UTickableConstraint> > FConstraintsManagerController::GetConstraintsByPredicate( Predicate Pred, const bool bSorted) const` (scope `FConstraintsManagerController`)
- L41 _typedef_ `using ConstraintPtr = TWeakObjectPtr<UTickableConstraint>;` (scope `FConstraintsManagerController::GetConstraintsByPredicate`)
- L58 _function_ `` (scope `FConstraintsManagerController::GetConstraintsByPredicate`)
- L62 _function_ `` (scope `FConstraintsManagerController::GetConstraintsByPredicate::__anon320f854e0202`)

### `Source/Runtime/Experimental/Animation/Constraints/Public/ConstraintsScripting.h` (Public)


#### class `UConstraintsScriptingLibrary`  
`class UConstraintsScriptingLibrary : public UBlueprintFunctionLibrary`  
_L21-105_
- reflection: `UCLASS(meta = (Transient, ScriptName = "ConstraintsScriptingLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: This is a set of helper functions to access various parts of the Sequencer and Control Rig API via Python and Blueprints.
- L34 _public prototype_ `static UConstraintsManager* GetManager(UWorld* InWorld);` — `UE_DEPRECATED(5.3, "Please use UConstraintSubsystem delegates.")` — No longer used, the system will internally set up the outers for the handles and see UConstraintSubsystem for the delegates.
- L44 _public prototype_ `static UTransformableComponentHandle* CreateTransformableComponentHandle(UWorld* InWorld, USceneComponent* InSceneComponent, const FName& InSocketName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Constraints")` — Create the transformable handle that deals with getting and setting transforms on this scene component @param InWorld, the world you are in @param InSceneComponent World to create the constraint @param InSocketName Optional name of the socket to get the transform @return returns the handle for this scene component
- L54 _public prototype_ `static UTransformableHandle* CreateTransformableHandle(UWorld* InWorld, UObject* InObject, const FName& InAttachmentName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Constraints")` — Create the transformable handle that deals with getting and setting transforms on this object @param InWorld, the world you are in @param InObject World to create the constraint @param InAttachmentName Optional name of the attachment to get the transform. Not that this can represent a scene component's socket name or a control rig control for example. @return returns the handle for this scene component
- L63 _public prototype_ `static UTickableTransformConstraint* CreateFromType(UWorld* InWorld, const ETransformConstraintType InType);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Constraints")` — Create Constraint based on the specified type. @param InWorld World to create the constraint @param InType The type of constraint @return return The constraint object
- L75 _public prototype_ `static bool AddConstraint(UWorld* InWorld, UTransformableHandle* InParentHandle, UTransformableHandle* InChildHandle, UTickableTransformConstraint *InConstraint, const bool bMaintainOffset);` — `UE_DEPRECATED(5.4, "UConstraintsScriptingLibrary::AddConstraint is deprecated. use UControlRigSequencerEditorLibrary::AddConstraint instead.")` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Constraints")` — Add Constraint to the system using the incoming parent and child handles with the specified type. @param InWorld World to create the constraint @param InParentHandle The parent handle @param InChildHandle The child handle @param InConsrtaint The constraint @return return If constraint added correctly
- L84 _public prototype_ `static TArray<UTickableConstraint*> GetConstraintsArray(UWorld* InWorld);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Constraints")` — Get a copy of the constraints in the current world @param InWorld World we are in @return Copy of the constraints in the level
- L94 _public prototype_ `static bool RemoveThisConstraint(UWorld* InWorld, UTickableConstraint* InTickableConstraint);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Constraints")` — Remove specified constraint @param InWorld World to remove the constraint @param InTickableConstraint Constraint to remove @return return If constraint removed correctly
- L103 _public prototype_ `static bool RemoveConstraint(UWorld* InWorld, int32 InIndex);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Sequencer Tools | Control Rig | Constraints")` — Remove constraint at specified index @param InWorld World to remove the constraint @param InIndex Index to remove from @return return If constraint removed correctly

### `Source/Runtime/Experimental/Animation/Constraints/Public/Transform/AnimationEvaluation.h` (Public)


#### struct `UE::Anim::FAnimationEvaluationTask`  
`struct FAnimationEvaluationTask`  
_L19-29_
- L21 _public function_ `bool IsValid(const USkeletalMeshComponent* InSkeletalMeshComponent) const`
- L26 _public member_ `FGuid Guid;`
- L27 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;`
- L28 _public member_ `TFunction<void()> PostEvaluationFunction;`

#### struct `UE::Anim::FAnimationEvaluator`  
`struct FAnimationEvaluator`  
_L40-86_
- L42 _public prototype_ `FAnimationEvaluator(USkeletalMeshComponent* InSkeletalMeshComponent);`
- L43 _public prototype_ `~FAnimationEvaluator();`
- L46 _public prototype_ `void Update(const bool bRefreshBoneTransforms);` — Clears the context and refresh the bones transforms if bRefreshBoneTransforms is true.
- L51 _public prototype_ `bool IsValid(const bool bForTransform = false) const;` — Returns true if the skeletal mesh component, its skeletal mesh and the transforms are valid for use. If bForTransform is true, the sizes of the component space transforms from the skeletal mesh component and those of the context are tested.
- L54 _public prototype_ `FTransform GetGlobalTransform(const FName InSocketName) const;` — Returns InSocketName component space transform composed with the skeletal mesh component's global transform.
- L57 _public prototype_ `FTransform GetRelativeTransform(const FName InSocketName) const;` — Returns InSocketName component space transform composed with the skeletal mesh component's relative transform.
- L60 _public prototype_ `bool AddPostEvaluationTask(const FAnimationEvaluationTask& InTask);` — Adds a post-evaluation task to this evaluator if it has not already been added (returns true if added).
- L64 _private prototype_ `FAnimationEvaluator() = default;`
- L67 _private prototype_ `void BindDelegates();` — Bind/Unbind this to the SkeletalMeshComponent's OnBoneTransformsFinalizedMC delegate.
- L68 _private prototype_ `void UnbindDelegates();`
- L71 _private prototype_ `void UpdateContext();` — Prepares the animation context for evaluation.
- L74 _private prototype_ `void EvaluateAnimation();` — Evaluates the animation using the Context.
- L77 _private prototype_ `void RefreshBoneTransforms();` — Evaluates the animation and store the bones transforms.
- L80 _private prototype_ `void BoneTransformsFinalized();` — Updates the bones transforms once the skeletal mesh is finally up to date.
- L82 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;`
- L83 _private member_ `FAnimationEvaluationContext Context;`
- L84 _private member_ `FDelegateHandle OnBoneTransformsFinalizedHandle;`
- L85 _private member_ `TMap<FGuid, FAnimationEvaluationTask> PostEvaluationTasks;`

#### struct `UE::Anim::FAnimationEvaluationCache`  
`struct FAnimationEvaluationCache`  
_L94-134_
- L97 _public prototype_ `static FAnimationEvaluationCache& Get();`
- L98 _public prototype_ `~FAnimationEvaluationCache();`
- L101 _public prototype_ `void MarkForEvaluation(const USkeletalMeshComponent* InSkeletalMeshComponent);` — Marks the evaluator related to InSkeletalMeshComponent for evaluation.
- L107 _public prototype_ `const FAnimationEvaluator& GetEvaluator(USkeletalMeshComponent* InSkeletalMeshComponent);` — Returns and up-to-date evaluator to be queried. Note that calling this function will actually evaluate the animation if the evaluator has been previously dirtied.
- L113 _public prototype_ `const FAnimationEvaluator& GetEvaluator(USkeletalMeshComponent* InSkeletalMeshComponent, const FAnimationEvaluationTask& InTask);` — Returns and up-to-date evaluator to be queried and adds the post-evaluation task if it has not already been added. Note that calling this function will actually evaluate the animation and the post-evaluation tasks if the evaluator has been previously dirtied.
- L119 _public prototype_ `const FAnimationEvaluator& FindEvaluator(const USkeletalMeshComponent* InSkeletalMeshComponent) const;` — Returns the evaluator related to InSkeletalMeshComponent if any or an invalid one otherwise. Note that calling this function won't update the evaluator so make sure to use FAnimationEvaluator::IsValid after calling that function.
- L122 _private prototype_ `FAnimationEvaluationCache() = default;`
- L125 _private prototype_ `void RegisterNotifications();` — Listen to the constraint manager notification to avoid keeping useless or invalid data.
- L128 _private prototype_ `void UnregisterNotifications();` — Stop listening to the constraint manager notification system.
- L131 _private member_ `TMap<USkeletalMeshComponent*, TUniquePtr<FAnimationEvaluator>> PerSkeletalMeshEvaluator;` — List of connected skeletal mesh components and animation evaluators.
- L133 _private member_ `FDelegateHandle ConstraintsNotificationHandle;`

#### struct `UE::Anim::FEvaluationForCachingScope`  
`struct FEvaluationForCachingScope : public FNoncopyable`  
_L141-145_
- inherits: `FNoncopyable`
- L143 _public prototype_ `FEvaluationForCachingScope(const float InDeltaTime = 1.f / 30.f);`
- L144 _public prototype_ `~FEvaluationForCachingScope();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Anim` (scope `UE`)
- L147 _prototype_ `bool IsCaching();` (scope `UE::Anim`)

### `Source/Runtime/Experimental/Animation/Constraints/Public/Transform/DependencyBuilder.h` (Public)


#### struct `FDependencyBuilder`  
`struct FDependencyBuilder`  
_L20-39_
- L24 _public prototype_ `static bool BuildDependencies(UWorld* InWorld, UTickableTransformConstraint* Constraint);` — Ensure default dependencies between constraints.
- L27 _public prototype_ `static bool LogDependencies();` — Returns true if dependencies should be logged.
- L32 _private prototype_ `static void BuildAttachmentsDependencies(UWorld* InWorld, const UTickableTransformConstraint* InConstraint);` — Ensures that attachment dependencies are reflected at the constraints level.
- L35 _private prototype_ `static void BuildSelfDependencies(UWorld* InWorld, UTickableTransformConstraint* InConstraint);` — Ensures that internal dependencies (control rig only at this point) are addressed at the constraints level.
- L38 _private prototype_ `static void BuildExternalDependencies(UWorld* InWorld, UTickableTransformConstraint* InConstraint);` — Ensures that external dependencies are addressed at the constraints level.

#### struct `FConstraintDependencyScope`  
`struct FConstraintDependencyScope`  
_L47-55_
- L49 _public prototype_ `FConstraintDependencyScope(UTickableTransformConstraint* InConstraint, UWorld* InWorld = nullptr);`
- L50 _public prototype_ `~FConstraintDependencyScope();`
- L52 _private member_ `TWeakObjectPtr<UTickableTransformConstraint> WeakConstraint = nullptr;`
- L53 _private member_ `TWeakObjectPtr<UWorld> WeakWorld = nullptr;`
- L54 _private member_ `bool bPreviousValidity = false;`

#### struct `FHandleDependencyChecker`  
`struct FHandleDependencyChecker`  
_L62-68_
- L64 _public prototype_ `FHandleDependencyChecker(UWorld* InWorld = nullptr);`
- L65 _public prototype_ `bool HasDependency(const UTransformableHandle& InHandle, const UTransformableHandle& InParentToCheck) const;`
- L67 _private member_ `TWeakObjectPtr<UWorld> WeakWorld = nullptr;`

#### struct `FConstraintCycleChecker`  
`struct FConstraintCycleChecker`  
_L74-95_
- L78 _public prototype_ `static bool IsCycling(const TWeakObjectPtr<UTransformableHandle>& InHandle);` — Checks if this handle is cycle from a tick dependencies perspective.
- L81 _public prototype_ `static void CheckAndFixCycles(const UTickableTransformConstraint* InConstraint);` — Checks for cycling constraints and manage tick dependencies if needed to avoid cycles from a tick dependency pov.
- L84 _public prototype_ `static bool HasPrerequisiteDependencyWith(const FTickFunction* InSecondary, const FTickFunction* InPrimary, TSet<const FTickFunction*>& InOutVisitedFunctions);` — ensure that InPossiblePrimary is not depending on InPossibleSecondary to avoid creating cycles
- L91 _private prototype_ `static void UpdateCyclingDependency(UWorld* InWorld, UTickableTransformConstraint* InConstraintToUpdate);` — Manage tick dependencies if needed to avoid cycles from a tick dependency pov. Both InConstraintToUpdate and its parent handle are supposed valid at this point
- L93 _private typedef_ `using ConstraintPtr = TWeakObjectPtr<UTickableConstraint>;`
- L94 _private typedef_ `using ConstraintArray = TArray<ConstraintPtr>;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API CONSTRAINTS_API`

### `Source/Runtime/Experimental/Animation/Constraints/Public/Transform/TransformConstraint.h` (Public)


#### class `UTickableTransformConstraint`  
`class UTickableTransformConstraint : public UTickableConstraint`  
_L26-200_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UTickableConstraint`
- L33 _public prototype_ `void Setup();` — Sets up the constraint so that the initial offset is set and dependencies and handles managed.
- L36 _public prototype_ `virtual void PostLoad() override;` — UObjects overrides.
- L37 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L40 _public prototype_ `virtual uint32 GetTargetHash() const override;` — Returns the target hash value (i.e. the child handle's hash).
- L43 _public prototype_ `virtual bool ReferencesObject(TWeakObjectPtr<UObject> InObject) const override;` — Test whether an InObject is referenced by that constraint. (i.e. is it's parent or child).
- L45 _public prototype_ `virtual bool HasBoundObjects() const override;` — If true it contains objects bound to an external system, like sequencer so we don't do certain things, like remove constraints when they don't resolve
- L48 _public prototype_ `virtual void ResolveBoundObjects(FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState, UObject* SubObject = nullptr) override;` — Resolve the bound objects so that any object it references are resovled and correctly set up
- L51 _public prototype_ `virtual bool IsValid(const bool bDeepCheck = true) const override;` — Whether or not it's valid for example it may not be fully loaded
- L54 _public prototype_ `virtual bool IsFullyActive() const override;` — If Active and the handles and targets are valid, and tick function is registered
- L57 _public prototype_ `virtual bool NeedsCompensation() const;` — If that constraint needs to be handled by the compensation system.
- L60 _public prototype_ `virtual UTickableConstraint* Duplicate(UObject* NewOuter) const override;` — Create duplicate with new Outer
- L63 _public prototype_ `virtual void Evaluate(bool bTickHandlesAlso = false) const override;` — Override the evaluate so we can tick our handles
- L66 _public prototype_ `virtual void SetActive(const bool bIsActive) override;` — Sets the Active value and enable/disable the tick function.
- L70 _public member_ `TObjectPtr<UTransformableHandle> ParentTRSHandle;` — `UPROPERTY(BlueprintReadWrite, Category = "Handle")` — The transformable handle representing the parent of that constraint.
- L74 _public member_ `TObjectPtr<UTransformableHandle> ChildTRSHandle;` — `UPROPERTY(BlueprintReadWrite, Category = "Handle")` — The transformable handle representing the child of that constraint.
- L78 _public member_ `bool bMaintainOffset = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offset", meta=(EditCondition="Type!=ETransformConstraintType::LookAt"))` — Should that constraint maintain the default offset.
- L84 _public member_ `float Weight = 1.f;` — `UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Weight", meta = (Input, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0")) @benoit when not EditAnywhere?
- L88 _public member_ `bool bDynamicOffset = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offset", meta=(EditCondition="(Type!=ETransformConstraintType::LookAt) && bMaintainOffset"))` — Should the child be able to change it's offset dynamically.
- L91 _public prototype_ `int64 GetType() const;` — Returns the constraint type (Position, Parent, Aim...).
- L94 _public prototype_ `FTransform GetChildGlobalTransform() const;` — Get the current child's global transform.
- L97 _public prototype_ `FTransform GetChildLocalTransform() const;` — Get the current child's local transform.
- L100 _public prototype_ `FTransform GetParentGlobalTransform() const;` — Get the current parent's global transform.
- L103 _public prototype_ `FTransform GetParentLocalTransform() const;` — Get the current parent's local transform.
- L106 _public prototype_ `EMovieSceneTransformChannel GetChannelsToKey() const;` — Returns the channels to key based on the constraint's type.
- L112 _public prototype_ `virtual void OnHandleModified(UTransformableHandle* InHandle, EHandleEvent InEvent);` — Manages changes on the child/parent transformable handle. This can be used to update internal data (i.e. offset) when transform changes outside of that system and need to trigger changes within the constraint itself.
- L115 _public prototype_ `FTickFunction* GetChildHandleTickFunction() const;` — Returns the handles tick function (ensuring it lives in the same world).
- L116 _public prototype_ `FTickFunction* GetParentHandleTickFunction() const;`
- L121 _public prototype_ `void EnsurePrimaryDependency(const UWorld* InWorld);` — Sets up dependencies with the first primary prerequisite available if the parent does not tick.
- L126 _protected prototype_ `void UnregisterDelegates() const;` — Registers/Unregisters useful delegates for both child and parent handles.
- L127 _protected prototype_ `void RegisterDelegates();`
- L134 _protected prototype_ `virtual void ComputeOffset() PURE_VIRTUAL(ComputeOffset, return;);` — Computes the initial offset that is needed to keep the child's global transform unchanged when creating the constraint. This can be called whenever necessary to update the current offset.
- L140 _protected prototype_ `void SetupDependencies(const UWorld* InWorld);` — Sets up dependencies between the parent, the constraint and the child using their respective tick functions. It creates a dependency graph between them so that they tick in the right order when evaluated.
- L143 _protected prototype_ `void SetChildGlobalTransform(const FTransform& InGlobal) const;` — Set the current child's global transform.
- L146 _protected prototype_ `void SetChildLocalTransform(const FTransform& InLocal) const;` — Set the current child's local transform.
- L150 _protected member_ `ETransformConstraintType Type = ETransformConstraintType::Parent;` — `UPROPERTY()` — Defines the constraint's type (Position, Parent, Aim...).
- L154 _protected function_ `void OnActiveStateChanged() const` — `UE_DEPRECATED(5.8, "Deprecated, no longer used.")` — Handle active state modification if needed.
- L157 _protected prototype_ `FTickFunction* GetHandleTickFunction(const TObjectPtr<UTransformableHandle>& InHandle) const;` — Returns the handle's tick function (ensuring it lives in the same world).
- L160 _protected prototype_ `void PreEvaluate() const;` — Perform necessary pre-evaluation steps before calculating the constraint's result.
- L163 _protected prototype_ `void PostEvaluate() const;` — Perform necessary post-evaluation steps after calculating the constraint's result.
- L167 _public prototype_ `virtual void InitConstraint(UWorld * InWorld) override;` — (Re-)Registers the constraint function and (re-)binds the required delegates
- L168 _public prototype_ `virtual void TeardownConstraint(UWorld * InWorld) override;`
- L169 _public prototype_ `virtual void AddedToWorld(UWorld* InWorld) override;`
- L173 _public member_ `bool bUseCurrentOffset = true;` — `UPROPERTY(EditAnywhere, Transient, Category="Offset", meta = (DisplayPriority=0))` — Used at creation to define whether the current relative offset should be used instead of the provided one.
- L178 _public prototype_ `virtual FString GetLabel() const override;` — Returns the constraint's label used for UI.
- L179 _public prototype_ `virtual FString GetFullLabel() const override;`
- L182 _public prototype_ `virtual FString GetTypeLabel() const override;` — Returns the constraint's type label used for UI.
- L185 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;` — UObject interface
- L186 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L187 _public prototype_ `virtual void PostEditUndo() override;`
- L194 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConstraintChanged, UTickableTransformConstraint*, const FPropertyChangedEvent&);` — Returns a delegate that can be used to monitor for property changes. This can be used to monitor constraints changes only instead of using FCoreUObjectDelegates::OnObjectPropertyChanged that is listening to every objects. Note that bScaling is currently the only property change we monitor but this can be used for other properties.
- L195 _public prototype_ `static FOnConstraintChanged& GetOnConstraintChanged();`
- L198 _protected member_ `static FOnConstraintChanged OnConstraintChanged;`

#### class `UTickableTranslationConstraint`  
`class UTickableTranslationConstraint : public UTickableTransformConstraint`  
_L207-248_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UTickableTransformConstraint`
- L212 _public prototype_ `UTickableTranslationConstraint();`
- L215 _public prototype_ `virtual FConstraintTickFunction::ConstraintFunction GetFunction() const override;` — Returns the position constraint function that the tick function will evaluate.
- L218 _public prototype_ `virtual void OnHandleModified(UTransformableHandle* InHandle, EHandleEvent InEvent) override;` — Updates the dynamic offset based on external child's transform changes.
- L227 _protected member_ `mutable FDynamicCache Cache;`
- L228 _protected prototype_ `uint32 CalculateInputHash() const;`
- L231 _protected prototype_ `virtual void ComputeOffset() override;` — Computes the child's local translation offset in the parent space.
- L236 _public member_ `FVector OffsetTranslation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offset", meta=(EditCondition="bMaintainOffset"))` — Defines the local child's translation offset in the parent space.
- L240 _public member_ `FFilterOptionPerAxis AxisFilter;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Axis Filter")` — Defines which translation axis is constrained.
- L245 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface

#### struct `UTickableTranslationConstraint::FDynamicCache`  
`struct FDynamicCache`  
_L223-226_
- desc: Cache data structure to store last child local/global location.
- L225 _public member_ `uint32 CachedInputHash = 0;`

#### class `UTickableRotationConstraint`  
`class UTickableRotationConstraint : public UTickableTransformConstraint`  
_L255-296_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UTickableTransformConstraint`
- L260 _public prototype_ `UTickableRotationConstraint();`
- L263 _public prototype_ `virtual FConstraintTickFunction::ConstraintFunction GetFunction() const override;` — Returns the rotation constraint function that the tick function will evaluate.
- L266 _public prototype_ `virtual void OnHandleModified(UTransformableHandle* InHandle, EHandleEvent InEvent) override;` — Updates the dynamic offset based on external child's transform changes.
- L275 _protected member_ `mutable FDynamicCache Cache;`
- L276 _protected prototype_ `uint32 CalculateInputHash() const;`
- L279 _protected prototype_ `virtual void ComputeOffset() override;` — Computes the child's local rotation offset in the parent space.
- L284 _public member_ `FQuat OffsetRotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offset", meta=(EditCondition="bMaintainOffset"))` — Defines the local child's rotation offset in the parent space.
- L288 _public member_ `FFilterOptionPerAxis AxisFilter;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Axis Filter")` — Defines which rotation axis is constrained.
- L293 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface

#### struct `UTickableRotationConstraint::FDynamicCache`  
`struct FDynamicCache`  
_L271-274_
- desc: Cache data structure to store last child local/global rotation.
- L273 _public member_ `uint32 CachedInputHash = 0;`

#### class `UTickableScaleConstraint`  
`class UTickableScaleConstraint : public UTickableTransformConstraint`  
_L303-343_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UTickableTransformConstraint`
- L308 _public prototype_ `UTickableScaleConstraint();`
- L311 _public prototype_ `virtual FConstraintTickFunction::ConstraintFunction GetFunction() const override;` — Returns the scale constraint function that the tick function will evaluate.
- L314 _public prototype_ `virtual void OnHandleModified(UTransformableHandle* InHandle, EHandleEvent InEvent) override;` — Updates the dynamic offset based on external child's transform changes.
- L318 _protected prototype_ `virtual void ComputeOffset() override;` — Computes the child's local scale offset in the parent space.
- L325 _protected member_ `mutable FDynamicCache Cache;`
- L326 _protected prototype_ `uint32 CalculateInputHash() const;`
- L331 _public member_ `FVector OffsetScale = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offset", meta=(EditCondition="bMaintainOffset"))` — Defines the local child's scale offset in the parent space.
- L335 _public member_ `FFilterOptionPerAxis AxisFilter;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Axis Filter")` — Defines which scale axis is constrained.
- L340 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface

#### struct `UTickableScaleConstraint::FDynamicCache`  
`struct FDynamicCache`  
_L321-324_
- desc: Cache data structure to store last child local/global transform.
- L323 _public member_ `uint32 CachedInputHash = 0;`

#### class `UTickableParentConstraint`  
`class UTickableParentConstraint : public UTickableTransformConstraint`  
_L350-406_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UTickableTransformConstraint`
- L355 _public prototype_ `UTickableParentConstraint();`
- L358 _public prototype_ `virtual FConstraintTickFunction::ConstraintFunction GetFunction() const override;` — Returns the transform constraint function that the tick function will evaluate.
- L360 _public function_ `bool IsScalingEnabled() const`
- L365 _public function_ `void SetScaling(const bool bInScale)`
- L370 _public function_ `static FName GetScalingPropertyName()`
- L373 _public prototype_ `virtual void OnHandleModified(UTransformableHandle* InHandle, EHandleEvent InEvent) override;` — Updates the dynamic offset based on external child's transform changes.
- L381 _protected member_ `mutable FDynamicCache Cache;`
- L382 _protected prototype_ `uint32 CalculateInputHash() const;`
- L385 _protected prototype_ `virtual void ComputeOffset() override;` — Computes the child's local transform offset in the parent space.
- L390 _public member_ `FTransform OffsetTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offset", meta=(EditCondition="bMaintainOffset"))` — Defines the local child's transform offset in the parent space.
- L394 _public member_ `bool bScaling = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")` — Defines whether we propagate the parent scale.
- L398 _public member_ `FTransformFilter TransformFilter;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Axis Filter")` — Defines which translation/rotation/scale axis are constrained.
- L403 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface

#### struct `UTickableParentConstraint::FDynamicCache`  
`struct FDynamicCache`  
_L377-380_
- desc: Cache data structure to store last child local/global transform.
- L379 _public member_ `uint32 CachedInputHash = 0;`

#### class `UTickableLookAtConstraint`  
`class UTickableLookAtConstraint : public UTickableTransformConstraint`  
_L413-447_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UTickableTransformConstraint`
- L418 _public prototype_ `UTickableLookAtConstraint();`
- L421 _public prototype_ `virtual FConstraintTickFunction::ConstraintFunction GetFunction() const override;` — Returns the look at constraint function that the tick function will evaluate.
- L424 _public prototype_ `virtual bool NeedsCompensation() const override;` — If that constraint needs to be handled by the compensation system.
- L430 _protected prototype_ `virtual void ComputeOffset() override;` — Computes the initial axis that is needed to keep the child's orientation unchanged when creating the constraint.
- L434 _protected member_ `FVector Axis = FVector::XAxisVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Axis")` — Defines the aiming axis.
- L439 _private prototype_ `static FQuat FindQuatBetweenNormals(const FVector& A, const FVector& B);` — Computes the shortest quaternion between A and B.
- L444 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface

#### struct `FTransformConstraintUtils`  
`struct FTransformConstraintUtils`  
_L449-511_
- L452 _public prototype_ `static void GetParentConstraints( UWorld* World, const AActor* InChild, TArray< TWeakObjectPtr<UTickableConstraint> >& OutConstraints);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L458 _public prototype_ `static UTransformableComponentHandle* CreateHandleForSceneComponent( USceneComponent* InSceneComponent, const FName& InSocketName);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L463 _public prototype_ `static UTickableTransformConstraint* CreateFromType( UWorld* InWorld, const ETransformConstraintType InType, const bool bUseDefault = false);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L469 _public prototype_ `static UTickableTransformConstraint* CreateAndAddFromObjects( UWorld* InWorld, UObject* InParent, const FName& InParentSocketName, UObject* InChild, const FName& InChildSocketName, const ETransformConstraintType InType, const bool bMaintainOffset = true, const bool bUseDefault = false);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L478 _public prototype_ `static bool AddConstraint( UWorld* InWorld, UTransformableHandle* InParentHandle, UTransformableHandle* InChildHandle, UTickableTransformConstraint* Constraint, const bool bMaintainOffset = true, const bool bUseDefault = false);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L487 _public prototype_ `static FTransform ComputeRelativeTransform( const FTransform& InChildLocal, const FTransform& InChildWorld, const FTransform& InSpaceWorld, const UTickableTransformConstraint* InConstraint);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L494 _public prototype_ `static TOptional<FTransform> GetRelativeTransform(UWorld* InWorld, const uint32 InHandleHash);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L495 _public prototype_ `static TOptional<FTransform> GetConstraintsRelativeTransform( const TArray< TWeakObjectPtr<UTickableConstraint> >& InConstraints, const FTransform& InChildLocal, const FTransform& InChildWorld);`
- L500 _public prototype_ `static int32 GetLastActiveConstraintIndex(const TArray< TWeakObjectPtr<UTickableConstraint> >& InConstraints);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L503 _public prototype_ `static void GetChildrenConstraints( UWorld* World, const UTickableTransformConstraint* InConstraint, TArray< TWeakObjectPtr<UTickableConstraint> >& OutConstraints, const bool bIncludeTarget = false);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`
- L510 _public prototype_ `static void UpdateTransformBasedOnConstraint(FTransform& CurrentTransform, USceneComponent* SceneComponent);` — `UE_DEPRECATED(5.6, "This function was moved to the UE::TransformConstraintUtil namespace.")`

#### Free symbols / members of external scopes

- L194 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConstraintChanged, UTickableTransformConstraint*, const FPropertyChangedEvent&);` — Returns a delegate that can be used to monitor for property changes. This can be used to monitor constraints changes only instead of using FCoreUObjectDelegates::OnObjectPropertyChanged that is listening to every objects. Note that bScaling is currently the only property change we monitor but this can be used for other properties.

### `Source/Runtime/Experimental/Animation/Constraints/Public/Transform/TransformConstraintUtil.h` (Public)


#### struct `UE::TransformConstraintUtil::FConstraintsInteractionCache`  
`struct FConstraintsInteractionCache`  
_L30-60_
- L33 _public prototype_ `~FConstraintsInteractionCache();`
- L35 _public prototype_ `void Reset();`
- L37 _public prototype_ `const TArray< TWeakObjectPtr<UTickableConstraint> >& Get(const UObject* InObject, const FName& InAttachmentName);`
- L38 _public prototype_ `bool HasAnyActiveConstraint(const UObject* InObject, const FName& InAttachmentName);`
- L39 _public prototype_ `TOptional<FTransform> GetParentTransform(const UObject* InObject, const FName& InAttachmentName);`
- L41 _public prototype_ `const TArray< TWeakObjectPtr<UTickableConstraint> >& Get(const uint32 InHandleHash, UWorld* InWorld);`
- L42 _public prototype_ `bool HasAnyActiveConstraint(const uint32 InHandleHash, UWorld* InWorld);`
- L43 _public prototype_ `TOptional<FTransform> GetParentTransform(const uint32 InHandleHash, UWorld* InWorld);`
- L45 _public prototype_ `const TArray< TWeakObjectPtr<UTickableConstraint> >& Get(UObject* InTarget, UWorld* InWorld = nullptr);`
- L46 _public prototype_ `bool HasAnyActiveConstraint(UObject* InTarget, UWorld* InWorld = nullptr);`
- L48 _public prototype_ `bool HasAnyDependency(UObject* InChild, UObject* InParent, UWorld* InWorld);`
- L50 _public prototype_ `void RegisterNotifications();`
- L51 _public prototype_ `void UnregisterNotifications();`
- L55 _private prototype_ `bool HasAnyDependencyInternal(UObject* InChild, UObject* InParent, UWorld* InWorld, TSet< UObject* >& Visited);`
- L57 _private member_ `TMap<uint32, TArray< TWeakObjectPtr<UTickableConstraint> >> PerHandleConstraints;`
- L58 _private member_ `TMap<TObjectKey<UObject>, TArray< TWeakObjectPtr<UTickableConstraint> >> PerTargetConstraints;`
- L59 _private member_ `FDelegateHandle ConstraintsNotificationHandle;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CONSTRAINTS_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace TransformConstraintUtil` (scope `UE`)
- L65 _namespace_ `namespace UE`
- L65 _namespace_ `namespace TransformConstraintUtil` (scope `UE`)
- L69 _prototype_ `void GetParentConstraints( UWorld* World, const AActor* InChild, TArray< TWeakObjectPtr<UTickableConstraint> >& OutConstraints);` (scope `UE::TransformConstraintUtil`) — Fills a sorted constraint array that InChild actor is the child of.
- L75 _prototype_ `UTransformableComponentHandle* CreateHandleForSceneComponent( USceneComponent* InSceneComponent, const FName& InSocketName);` (scope `UE::TransformConstraintUtil`) — Create a handle for the scene component.
- L80 _prototype_ `UTickableTransformConstraint* CreateFromType( UWorld* InWorld, const ETransformConstraintType InType, const bool bUseDefault = false);` (scope `UE::TransformConstraintUtil`) — Creates a new transform constraint based on the InType.
- L86 _prototype_ `UTickableTransformConstraint* CreateAndAddFromObjects( UWorld* InWorld, UObject* InParent, const FName& InParentSocketName, UObject* InChild, const FName& InChildSocketName, const ETransformConstraintType InType, const bool bMaintainOffset = true, const bool bUseDefault = false, const TFunction<void()>& InValidDependencyFunction = nullptr);` (scope `UE::TransformConstraintUtil`) — Creates respective handles and creates a new InType transform constraint.
- L96 _prototype_ `bool AddConstraint( UWorld* InWorld, UTransformableHandle* InParentHandle, UTransformableHandle* InChildHandle, UTickableTransformConstraint* Constraint, const bool bMaintainOffset = true, const bool bUseDefault = false);` (scope `UE::TransformConstraintUtil`) — Registers a new transform constraint within the constraints manager.
- L105 _prototype_ `FTransform ComputeRelativeTransform( const FTransform& InChildLocal, const FTransform& InChildWorld, const FTransform& InSpaceWorld, const UTickableTransformConstraint* InConstraint);` (scope `UE::TransformConstraintUtil`) — Computes the relative transform between both transform based on the constraint's InType.
- L112 _prototype_ `TOptional<FTransform> GetRelativeTransform(UWorld* InWorld, const uint32 InHandleHash);` (scope `UE::TransformConstraintUtil`) — Computes the current constraint space local transform.
- L113 _prototype_ `TOptional<FTransform> GetConstraintsRelativeTransform( const TArray< TWeakObjectPtr<UTickableConstraint> >& InConstraints, const FTransform& InChildLocal, const FTransform& InChildWorld);` (scope `UE::TransformConstraintUtil`)
- L118 _prototype_ `int32 GetLastActiveConstraintIndex(const TArray< TWeakObjectPtr<UTickableConstraint> >& InConstraints);` (scope `UE::TransformConstraintUtil`) — Get the last active constraint that has dynamic offset.
- L124 _prototype_ `void GetChildrenConstraints( UWorld* World, const UTickableTransformConstraint* InConstraint, TArray< TWeakObjectPtr<UTickableConstraint> >& OutConstraints, const bool bIncludeTarget = false);` (scope `UE::TransformConstraintUtil`) — Fills a constraint array that InConstraint->ChildHandle is the parent of. If bIncludeTarget is true, we also get the other constraints that act on the same target.
- L131 _prototype_ `void UpdateTransformBasedOnConstraint(FTransform& InOutCurrentTransform, const USceneComponent* InSceneComponent);` (scope `UE::TransformConstraintUtil`) — Adjust the transform on a scene component so it's effected by the constraint
- L134 _prototype_ `UTickableTransformConstraint* GetConfig(const UClass* InConstraintClass);` (scope `UE::TransformConstraintUtil`) — Returns the configuration constraint instance for a specific constraint class if it exists

### `Source/Runtime/Experimental/Animation/Constraints/Public/Transform/TransformableHandle.h` (Public)


#### enum `EHandleEvent`  
`enum class EHandleEvent : uint8`  
_L28-37_
- reflection: `UENUM()`
- L30 _public enumerator_ `LocalTransformUpdated`
- L31 _public enumerator_ `GlobalTransformUpdated`
- L32 _public enumerator_ `ComponentUpdated`
- L33 _public enumerator_ `UpperDependencyUpdated`
- L36 _public enumerator_ `Max UMETA(Hidden)` — MAX - invalid

#### class `UTransformableHandle`  
`class UTransformableHandle : public UObject`  
_L44-146_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L50 _public prototype_ `DECLARE_EVENT_TwoParams(UTransformableHandle, FHandleModifiedEvent, UTransformableHandle*, EHandleEvent);`
- L52 _public prototype_ `virtual ~UTransformableHandle();`
- L60 _public prototype_ `virtual bool IsValid(const bool bDeepCheck = true) const PURE_VIRTUAL(IsValid, return false;);` — Sanity check to ensure the handle is safe to use. @param bDeepCheck to check that the transformable object it wraps is valid AND can be transformed. Default is true. Some handles, such as control handles, will only be bound to a skeletal mesh once the level sequence has been opened, but their control rig pointer and control name are valid, so they must be fully loaded so that the constraint can be updated later. bDeepCheck = false will be used for that purpose.
- L63 _public prototype_ `virtual void SetGlobalTransform(const FTransform& InGlobal) const PURE_VIRTUAL(SetGlobalTransform, );` — Sets the global transform of the underlying transformable object.
- L65 _public prototype_ `virtual void SetLocalTransform(const FTransform& InLocal) const PURE_VIRTUAL(SetLocalTransform, );` — Sets the local transform of the underlying transformable object in it's parent space.
- L67 _public prototype_ `virtual FTransform GetGlobalTransform() const PURE_VIRTUAL(GetGlobalTransform, return FTransform::Identity;);` — Gets the global transform of the underlying transformable object.
- L69 _public prototype_ `virtual FTransform GetLocalTransform() const PURE_VIRTUAL(GetLocalTransform, return FTransform::Identity;);` — Gets the local transform of the underlying transformable object in it's parent space.
- L72 _public prototype_ `virtual bool HasBoundObjects() const;` — If true it contains objects bound to an external system, like sequencer so we don't do certain things, like remove constraints when they don't resolve
- L75 _public prototype_ `virtual void ResolveBoundObjects(FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState, UObject* SubObject = nullptr) PURE_VIRTUAL(ResolveBoundObjects);` — Resolve the bound objects so that any object it references are resolved and correctly set up
- L78 _public prototype_ `virtual UTransformableHandle* Duplicate(UObject* NewOuter) const PURE_VIRTUAL(Duplicate, return nullptr;);` — Make a duplicate of myself with this outer
- L82 _public prototype_ `void OnBindingIDsUpdated(const TMap<UE::MovieScene::FFixedObjectBindingID, UE::MovieScene::FFixedObjectBindingID>& OldFixedToNewFixedMap, FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState);` — Fix up Binding in case it has changed
- L85 _public function_ `virtual void TickTarget() const` — Perform any special ticking needed for this handle, by default it does nothing, todo need to see if we need to tick control rig also
- L91 _public prototype_ `virtual void PreEvaluate(const bool bTick = false) const;` — Perform any pre-evaluation of the handle to ensure that the transform data are up to date. @param bTick to force any pre-evaluation ticking. Default is false.
- L94 _public prototype_ `virtual TArrayView<FMovieSceneFloatChannel*> GetFloatChannels(const UMovieSceneSection* InSection) const PURE_VIRTUAL(GetFloatChannels, return TArrayView<FMovieSceneFloatChannel*>(); );` — Get the array of float channels for the specified section
- L96 _public prototype_ `virtual TArrayView<FMovieSceneDoubleChannel*> GetDoubleChannels(const UMovieSceneSection * InSection) const PURE_VIRTUAL(GetDoubleChannels, return TArrayView<FMovieSceneDoubleChannel*>(); );` — Get the array of double channels for the specified section
- L98 _public prototype_ `virtual bool AddTransformKeys(const TArray<FFrameNumber>& InFrames, const TArray<FTransform>& InTransforms, const EMovieSceneTransformChannel& InChannels, const FFrameRate& InTickResolution, UMovieSceneSection* InSection, const bool bLocal = true) const PURE_VIRTUAL(AddTransformKeys, return false;);` — Add Transform Keys at the specified times
- L109 _public prototype_ `virtual UObject* GetPrerequisiteObject() const PURE_VIRTUAL(GetPrerequisiteObject, return nullptr;);` — Returns the target object containing the tick function (returned in GetTickFunction). See FTickFunction::AddPrerequisite for details.
- L114 _public prototype_ `virtual FTickFunction* GetTickFunction() const PURE_VIRTUAL(GetTickFunction, return nullptr;);` — Returns the tick function of the underlying transformable object. This is used to set dependencies with the constraint.
- L117 _public prototype_ `virtual uint32 GetHash() const PURE_VIRTUAL(GetHash, return 0;);` — Generates a hash value of the underlying transformable object.
- L120 _public prototype_ `virtual TWeakObjectPtr<UObject> GetTarget() const PURE_VIRTUAL(GetTarget, return nullptr;);` — Returns the underlying targeted object.
- L123 _public prototype_ `virtual bool HasDirectDependencyWith(const UTransformableHandle& InOther) const PURE_VIRTUAL(HasDirectDependencyWith, return false;);` — Check for direct dependencies with InOther.
- L126 _public function_ `virtual bool HasIndirectDependencyWith(const UTransformableHandle& InOther) const` — Check for indirect dependencies with InOther. (returns false by default, override in child classes if needed)
- L129 _public prototype_ `virtual FTickPrerequisite GetPrimaryPrerequisite(const bool bAllowThis = true) const PURE_VIRTUAL(GetPrimaryPrerequisite, return FTickPrerequisite(););` — Look for a possible tick function that can be used as a prerequisite.
- L131 _public prototype_ `FHandleModifiedEvent& HandleModified();`
- L132 _public prototype_ `void Notify(EHandleEvent InEvent, const bool bPreTickTarget = false) const;`
- L133 _public member_ `mutable bool bNotifying = false;`
- L136 _public prototype_ `virtual FString GetLabel() const PURE_VIRTUAL(GetLabel, return FString(););`
- L137 _public prototype_ `virtual FString GetFullLabel() const PURE_VIRTUAL(GetFullLabel, return FString(););`
- L142 _public member_ `FMovieSceneObjectBindingID ConstraintBindingID;` — `UPROPERTY(BlueprintReadOnly, Category = "Binding")` — possible bindingID
- L145 _private member_ `FHandleModifiedEvent OnHandleModified;`

#### struct `FComponentEvaluationGraphBinding`  
`struct FComponentEvaluationGraphBinding`  
_L152-156_
- L154 _public prototype_ `void OnActorMoving(AActor* InActor);`
- L155 _public member_ `bool bPendingFlush = false;`

#### class `UTransformableComponentHandle`  
`class UTransformableComponentHandle : public UTransformableHandle`  
_L159-255_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UTransformableHandle`
- L165 _public prototype_ `virtual ~UTransformableComponentHandle();`
- L167 _public prototype_ `virtual void PostLoad() override;`
- L170 _public prototype_ `virtual bool IsValid(const bool bDeepCheck = true) const override;` — Sanity check to ensure that Component.
- L173 _public prototype_ `virtual void SetGlobalTransform(const FTransform& InGlobal) const override;` — Sets the global transform of Component.
- L175 _public prototype_ `virtual void SetLocalTransform(const FTransform& InLocal) const override;` — Sets the local transform of Component in it's attachment.
- L177 _public prototype_ `virtual FTransform GetGlobalTransform() const override;` — Gets the global transform of Component.
- L179 _public prototype_ `virtual FTransform GetLocalTransform() const override;` — Gets the local transform of Component in it's attachment.
- L181 _public prototype_ `virtual void TickTarget() const override;` — Tick any skeletal mesh related to the component.
- L188 _public prototype_ `virtual void PreEvaluate(const bool bTickSkeletalMeshes = false) const override;` — Perform any pre-evaluation of the handle to ensure that the transform data is up to date. @param bTickSkeletalMeshes to force any pre-evaluation ticking. The rig will still be pre-evaluated even if bTick is false (it just won't tick the bound skeletal meshes) Default is false.
- L191 _public prototype_ `virtual UObject* GetPrerequisiteObject() const override;` — Returns the target object containing the tick function (e.i. Component).
- L193 _public prototype_ `virtual FTickFunction* GetTickFunction() const override;` — Returns Component's tick function.
- L196 _public prototype_ `virtual uint32 GetHash() const override;` — Generates a hash value of Component.
- L199 _public prototype_ `virtual TWeakObjectPtr<UObject> GetTarget() const override;` — Returns the underlying targeted object.
- L202 _public prototype_ `virtual bool HasDirectDependencyWith(const UTransformableHandle& InOther) const override;` — Check for direct dependencies (ie hierarchy) with InOther.
- L208 _public prototype_ `virtual FTickPrerequisite GetPrimaryPrerequisite(const bool bAllowThis = true) const override;` — Look for a possible tick function that can be used as a prerequisite. If bAllowThis is false then the component's tick function is not allowed as a primary prerequisite.
- L211 _public prototype_ `virtual TArrayView<FMovieSceneFloatChannel*> GetFloatChannels(const UMovieSceneSection* InSection) const override;` — Get the array of float channels for the specified section
- L213 _public prototype_ `virtual TArrayView<FMovieSceneDoubleChannel*> GetDoubleChannels(const UMovieSceneSection* InSection) const override;` — Get the array of double channels for the specified section
- L215 _public prototype_ `virtual bool AddTransformKeys(const TArray<FFrameNumber>& InFrames, const TArray<FTransform>& InTransforms, const EMovieSceneTransformChannel& InChannels, const FFrameRate& InTickResolution, UMovieSceneSection* InSection, const bool bLocal = true) const override;` — Add Transform Keys at the specified times
- L223 _public prototype_ `virtual void ResolveBoundObjects(FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState, UObject* SubObject = nullptr) override;` — Resolve the bound objects so that any object it references are resovled and correctly set up
- L226 _public prototype_ `virtual UTransformableHandle* Duplicate(UObject* NewOuter) const override;` — Make a duplicate of myself with this outer
- L230 _public prototype_ `virtual FString GetLabel() const override;` — Returns labels used for UI.
- L231 _public prototype_ `virtual FString GetFullLabel() const override;`
- L236 _public member_ `TWeakObjectPtr<USceneComponent> Component;` — `UPROPERTY(BlueprintReadOnly, Category = "Object")` — The Component that this handle is pointing at.
- L240 _public member_ `FName SocketName = NAME_None;` — `UPROPERTY(BlueprintReadOnly, Category = "Object")` — Optional socket name on Component.
- L243 _public prototype_ `void UnregisterDelegates() const;` — Registers/Unregisters useful delegates to track changes in the Component's transform.
- L244 _public prototype_ `void RegisterDelegates();`
- L247 _public prototype_ `void OnActorMoving(AActor* InActor);`
- L248 _public prototype_ `void OnPostPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L249 _public prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& InOldToNewInstances);`
- L254 _protected prototype_ `static FComponentEvaluationGraphBinding& GetEvaluationBinding();`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MovieScene` (scope `UE`)
- L50 _delegate_ `DECLARE_EVENT_TwoParams(UTransformableHandle, FHandleModifiedEvent, UTransformableHandle*, EHandleEvent);`

### `Source/Runtime/Experimental/Animation/Constraints/Public/Transform/TransformableHandleUtils.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace TransformableHandleUtils`
- L16 _prototype_ `bool SkipTicking();` (scope `TransformableHandleUtils`) — Returns true if the constraints' evaluation scheme should skip ticking skeletal meshes.
- L19 _prototype_ `void TickDependantComponents(USceneComponent* InComponent);` (scope `TransformableHandleUtils`) — Force ticking all the skeletal meshes related to this component.
- L22 _prototype_ `void TickSkeletalMeshComponent(USkeletalMeshComponent* InSkeletalMeshComponent);` (scope `TransformableHandleUtils`) — Force ticking InSkeletalMeshComponent.
- L28 _prototype_ `void MarkComponentForEvaluation(const USceneComponent* InSceneComponent, const bool bRecursive = false);` (scope `TransformableHandleUtils`) — Mark InSceneComponent for animation evaluation. If bRecursive is true, then all skeletal mesh components up the hierarchy will be marked for evaluation.
- L31 _prototype_ `FTransform GetGlobalTransform(USceneComponent* InSceneComponent, const FName InSocketName);` (scope `TransformableHandleUtils`) — `UE_DEPRECATED(5.8, "Use TransformableHandleUtils::EvaluateGlobalTransform instead")`
- L38 _prototype_ `FTransform EvaluateGlobalTransform(USceneComponent* InSceneComponent, const FName InSocketName);` (scope `TransformableHandleUtils`) — Evaluates the global transform of the scene component (composed with a socket component transform if InSocketName is not none). If any of the component's parent is a skeletal mesh and has a valid evaluator, then it will be used to compose the final transform. Note that this function will update invalid evaluators if needed.
- L45 _prototype_ `FTransform GetGlobalTransform(const USceneComponent* InSceneComponent, const FName InSocketName);` (scope `TransformableHandleUtils`) — Returns the global transform of the scene component (composed with a socket component transform if InSocketName is not none). If the component or one of its parents is a skeletal mesh component and has an invalid evaluator, this function will return the equivalent of USceneComponent::GetSocketTransform. Otherwise, the evaluators will be used to compose the final transform.
- L48 _prototype_ `const UE::Anim::FAnimationEvaluator& EvaluateComponent(USceneComponent* InSceneComponent);` (scope `TransformableHandleUtils`) — Returns an updated version of InSceneComponent's animation evaluator.
- L51 _prototype_ `const UE::Anim::FAnimationEvaluator& EvaluateComponent( USceneComponent* InSceneComponent, const UE::Anim::FAnimationEvaluationTask& InTask);` (scope `TransformableHandleUtils`) — Returns an updated version of InSceneComponent's animation evaluator and adds the input post-evaluation task if not already added.
- L59 _function_ `template<typename T = UObject> T* GetTarget(const TObjectPtr<UTransformableHandle>& InHandle)` (scope `TransformableHandleUtils`) — Returns a cast version of InHandle's target (if it's valid).

### `Source/Runtime/Experimental/Animation/Constraints/Public/Transform/TransformableRegistry.h` (Public)


#### class `FTransformableRegistry`  
`class FTransformableRegistry`  
_L18-63_
- L23 _public typedef_ `using CreateHandleFuncT = TFunction<UTransformableHandle*(UObject*, const FName&)>;` — Defines the function that will allocate a new transformable handle to wrap the object.
- L25 _public typedef_ `using GetHashFuncT = TFunction<uint32(const UObject*, const FName&)>;` — Defines the function that return a hash value from the object and the attachment name.
- L27 _public prototype_ `~FTransformableRegistry();`
- L30 _public prototype_ `static FTransformableRegistry& Get();` — Get registry singleton
- L33 _public prototype_ `void Register(UClass* InClass, CreateHandleFuncT InHandleFunc, GetHashFuncT InHashFunc);` — Registers a InClass as transformable object.
- L36 _public prototype_ `GetHashFuncT GetHashFunction(const UClass* InClass) const;` — Get the associated hash function for that specific class.
- L38 _public prototype_ `CreateHandleFuncT GetCreateFunction(const UClass* InClass) const;` — Get the associated handle creation function for that specific class.
- L44 _protected prototype_ `static void RegisterBaseObjects();` — Registers the basic transformable objects. (called when starting the constraints module).
- L46 _protected prototype_ `static void UnregisterAllObjects();` — Registers the basic transformable objects. (called when shutting down the constraints module).
- L49 _private prototype_ `FTransformableRegistry() = default;`
- L59 _private prototype_ `const FTransformableInfo* FindInfo(const UClass* InClass) const;` — Find the associated info for that specific class.
- L62 _private member_ `TMap<UClass*, FTransformableInfo> Transformables;` — List of all registered transformable objects.

#### struct `FTransformableRegistry::FTransformableInfo`  
`struct FTransformableInfo`  
_L52-56_
- desc: Per class information that need to be register.
- L54 _public member_ `CreateHandleFuncT CreateHandleFunc;`
- L55 _public member_ `GetHashFuncT GetHashFunc;`
