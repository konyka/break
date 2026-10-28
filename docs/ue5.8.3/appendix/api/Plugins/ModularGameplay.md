# Plugins / ModularGameplay

- module root: `Plugins/Runtime/ModularGameplay/Source/ModularGameplay`
- headers: 10; symbols: 240
- symbol kinds: class=11, delegate=4, enum=2, enumerator=6, function=70, macro=7, member=47, prototype=82, struct=9, typedef=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core, Engine, GameplayTags

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Private/ModularGameplayLogs.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogModularGameplay, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogModularGameplay, Log, All);`

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/Components/ControllerComponent.h` (Public)


#### class `UControllerComponent`  
`class UControllerComponent : public UGameFrameworkComponent`  
_L15-112_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameFrameworkComponent`
- desc: ControllerComponent is an actor component made for AController and receives controller events.
- L21 _public prototype_ `UControllerComponent(const FObjectInitializer& ObjectInitializer);`
- L25 _public function_ `template <class T> T* GetController() const` — Gets the controller that owns the component, this will always be valid during gameplay but can return null in the editor
- L32 _public function_ `template <class T> T* GetControllerChecked() const`
- L45 _public function_ `template <class T> T* GetPawn() const` — Returns the pawn that is currently possessed by the owning controller, will often return null
- L53 _public function_ `template <class T> T* GetViewTarget() const` — Returns the actor that is serving as the current view target for the owning controller
- L61 _public function_ `template <class T> T* GetPawnOrViewTarget() const` — If this controller is possessing a pawn return the pawn, if not return the view target
- L75 _public function_ `template <class T> T* GetPlayerState() const` — Returns the player state attached to this controller if there is one
- L82 _public prototype_ `bool IsLocalController() const;` — Returns true if the owning controller is considered to be local
- L85 _public prototype_ `void GetPlayerViewPoint(FVector& Location, FRotator& Rotation) const;` — Returns the point of view for either a player or controlled pawn
- L93 _public function_ `template <class T> T* GetPlayer() const`
- L108 _public function_ `virtual void ReceivedPlayer()` — Called after the PlayerController's viewport/net connection is associated with this player controller.
- L111 _public function_ `virtual void PlayerTick(float DeltaTime)` — PlayerTick is only called if the PlayerController has a PlayerInput object. Therefore, it will only be called for locally controlled PlayerControllers.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODULARGAMEPLAY_API`

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/Components/GameFrameworkComponent.h` (Public)


#### class `UGameFrameworkComponent`  
`class UGameFrameworkComponent : public UActorComponent`  
_L14-47_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, HideCategories=(Trigger, PhysicsVolume))`
- inherits: `UActorComponent`
- desc: GameFrameworkComponent is a base class for actor components made for the basic game framework classes.
- L20 _public prototype_ `UGameFrameworkComponent(const FObjectInitializer& ObjectInitializer);`
- L24 _public function_ `template <class T> T* GetGameInstance() const` — Gets the game instance this component is a part of, this will return null if not called during normal gameplay
- L32 _public function_ `template <class T> T* GetGameInstanceChecked() const`
- L43 _public prototype_ `bool HasAuthority() const;` — Returns true if the owner's role is ROLE_Authority
- L46 _public prototype_ `class FTimerManager& GetWorldTimerManager() const;` — Returns the world's timer manager

#### class `TComponentIterator`  
`template <typename T> class TComponentIterator`  
_L53-125_
- desc: Iterator for registered components on an actor
- L56 _public function_ `explicit TComponentIterator(AActor* OwnerActor) : CompIndex(-1)`
- L67 _public function_ `inline void operator++()`
- L72 _public function_ `inline explicit operator bool() const`
- L77 _public function_ `inline bool operator!() const`
- L82 _public function_ `inline T* operator*() const`
- L87 _public function_ `inline T* operator->() const`
- L94 _protected function_ `inline T* GetComponent() const` — Gets the current component
- L100 _protected function_ `inline bool Advance()` — Moves the iterator to the next valid component
- L118 _private member_ `TInlineComponentArray<T*> AllComponents;` — Results from GetComponents
- L121 _private member_ `int32 CompIndex;` — Index of the current element in the componnet array
- L123 _private function_ `inline bool operator==(const TComponentIterator& Other) const`
- L124 _private function_ `inline bool operator!=(const TComponentIterator& Other) const`

#### class `TConstComponentIterator`  
`template <typename T> class TConstComponentIterator`  
_L131-203_
- desc: Const iterator for registered components on an actor
- L134 _public function_ `explicit TConstComponentIterator(const AActor* OwnerActor) : CompIndex(-1)`
- L145 _public function_ `inline void operator++()`
- L150 _public function_ `inline explicit operator bool() const`
- L155 _public function_ `inline bool operator!() const`
- L160 _public function_ `inline const T* operator*() const`
- L165 _public function_ `inline const T* operator->() const`
- L172 _protected function_ `inline const T* GetComponent() const` — Gets the current component
- L178 _protected function_ `inline bool Advance()` — Moves the iterator to the next valid component
- L196 _private member_ `TInlineComponentArray<const T*> AllComponents;` — Results from GetComponents
- L199 _private member_ `int32 CompIndex;` — Index of the current element in the componnet array
- L201 _private function_ `inline bool operator==(const TConstComponentIterator& Other) const`
- L202 _private function_ `inline bool operator!=(const TConstComponentIterator& Other) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODULARGAMEPLAY_API`

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/Components/GameFrameworkComponentDelegates.h` (Public)


#### struct `FActorInitStateChangedParams`  
`struct FActorInitStateChangedParams`  
_L10-41_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters struct for Init State change functions
- L14 _public function_ `FActorInitStateChangedParams() : OwningActor(nullptr) , Implementer(nullptr)`
- L19 _public function_ `FActorInitStateChangedParams(AActor* InOwningActor, FName InFeatureName, UObject* InImplementer, FGameplayTag InFeatureState) : OwningActor(InOwningActor) , FeatureName(InFeatureName) , Implementer(InImplementer) , FeatureState(InFeatureState)`
- L28 _public member_ `TObjectPtr<AActor> OwningActor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)` — The actor owning the feature that changed
- L32 _public member_ `FName FeatureName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)` — Name of the feature that changed
- L36 _public member_ `TObjectPtr<UObject> Implementer;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)` — The object (often a component) that implements the feature
- L40 _public member_ `FGameplayTag FeatureState;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)` — The new state of the feature

#### Free symbols / members of external scopes

- L44 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FActorInitStateChangedBPDelegate, const FActorInitStateChangedParams&, Params);` — Blueprint delegate called when an actor feature changes init state
- L44 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FActorInitStateChangedBPDelegate, const FActorInitStateChangedParams&, Params);` — Blueprint delegate called when an actor feature changes init state

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/Components/GameFrameworkComponentManager.h` (Public)


#### enum `EGameFrameworkAddComponentFlags`  
`enum class EGameFrameworkAddComponentFlags : uint8`  
_L23-30_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Bitflag enum to control how this AddComponents action should actually run
- L26 _public enumerator_ `None = 0 UMETA(Hidden)` — If 0, no specific rule is applied and the component will be always created on the receiver"),
- L27 _public enumerator_ `AddUnique = 0b00000001 UMETA(DisplayName = "Add Unique", ToolTip="If AddUnique is set, it will be added only if there is no existing component on ActorInstance of ComponentClass.")`
- L28 _public enumerator_ `AddIfNotChild = 0b00000010 UMETA(DisplayName = "Add Unique If Not Child", ToolTip = "If AddIfNotChild is set, it will be added only if ComponentClass is not a child of an existing component on ActorInstance.")`
- L29 _public enumerator_ `UseAutoGeneratedName = 0b00000100 UMETA(DisplayName = "Use Auto Generated Name", ToolTip = "If UseAutoGeneratedName is set, it will generate a new name and not re-use the class name directly (which can lead to component recycling).")`

#### enum `EGameFrameworkAddComponentResult`  
`enum class EGameFrameworkAddComponentResult : uint8`  
_L33-37_
- L35 _public enumerator_ `Success`
- L36 _public enumerator_ `Failed`

#### struct `FComponentRequestHandle`  
`struct FComponentRequestHandle`  
_L42-73_
- desc: A handle for a request to put components or call a delegate for an extensible actor class. When this handle is destroyed, it will remove the associated request from the system.
- L44 _public function_ `FComponentRequestHandle(const TWeakObjectPtr<UGameFrameworkComponentManager>& InOwningManager, const TSoftClassPtr<AActor>& InReceiverClass, const TSubclassOf<UActorComponent>& InComponentClass) : OwningManager(InOwningManager) , ReceiverClass(InReceiverClass) , ComponentClass(InComponentClass)`
- L50 _public function_ `FComponentRequestHandle(const TWeakObjectPtr<UGameFrameworkComponentManager>& InOwningManager, const TSoftClassPtr<AActor>& InReceiverClass, FDelegateHandle InExtensionHandle) : OwningManager(InOwningManager) , ReceiverClass(InReceiverClass) , ExtensionHandle(InExtensionHandle)`
- L56 _public prototype_ `~FComponentRequestHandle();`
- L59 _public prototype_ `bool IsValid() const;` — Returns true if the manager that this request is for still exists
- L63 _private member_ `TWeakObjectPtr<UGameFrameworkComponentManager> OwningManager;` — The manager that this request was for
- L66 _private member_ `TSoftClassPtr<AActor> ReceiverClass;` — The class of actor to put components
- L69 _private member_ `TSubclassOf<UActorComponent> ComponentClass;` — The class of component to put on actors
- L72 _private member_ `FDelegateHandle ExtensionHandle;` — A handle to an extension delegate to run

#### class `UGameFrameworkComponentManager`  
`class UGameFrameworkComponentManager : public UGameInstanceSubsystem`  
_L90-556_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameInstanceSubsystem`
- desc: GameFrameworkComponentManager A manager to handle putting components on actors as they come and go. Put in a request to instantiate components of a given class on actors of a given class and they will automatically be made for them as the actors are spawned. Submit delegate handlers to listen for actors of a given class. Those handlers will automatically run when actors of a given class or registered as receivers or game events are sent. Actors must opt-in to this behavior by calling AddReceiver/RemoveReceiver for themselves when they are ready to receive the components and when they want to remove them. Any actors that are in memory when a request is made will automatically get the components, and any in memory when a request is removed will lose the components immediately. Requests are reference counted, so if multiple requests are made for the same actor class and component class, only one component will be added and that component wont be removed until all requests are removed.
- L96 _public prototype_ `DECLARE_DELEGATE_TwoParams(FExtensionHandlerDelegate, AActor*, FName);` — Delegate types for extension handlers
- L98 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L99 _public prototype_ `virtual void Deinitialize() override;`
- L102 _public prototype_ `static UGameFrameworkComponentManager* GetForActor(const AActor* Actor, bool bOnlyGameWorlds = true);` — Utility to get this manager from an actor, will return null if actor is null or not in a world
- L106 _public prototype_ `void AddReceiver(AActor* Receiver, bool bAddOnlyInGameWorlds = true);` — `UFUNCTION(BlueprintCallable, Category="Gameplay", meta=(DefaultToSelf="Receiver", AdvancedDisplay=1))` — Adds an actor as a receiver for components. If it passes the actorclass filter on requests it will get the components.
- L110 _public prototype_ `void RemoveReceiver(AActor* Receiver);` — `UFUNCTION(BlueprintCallable, Category="Gameplay", meta=(DefaultToSelf="Receiver"))` — Removes an actor as a receiver for components.
- L113 _public prototype_ `static void AddGameFrameworkComponentReceiver(AActor* Receiver, bool bAddOnlyInGameWorlds = true);` — Adds an actor as a receiver for components (automatically finding the manager for the actor's  game instance). If it passes the actorclass filter on requests it will get the components.
- L116 _public prototype_ `static void RemoveGameFrameworkComponentReceiver(AActor* Receiver);` — Removes an actor as a receiver for components (automatically finding the manager for the actor's game instance).
- L127 _public prototype_ `TSharedPtr<FComponentRequestHandle> AddComponentRequest(const TSoftClassPtr<AActor>& ReceiverClass, TSubclassOf<UActorComponent> ComponentClass, const EGameFrameworkAddComponentFlags AdditionFlags = EGameFrameworkAddComponentFlags::None);` — Adds a request to instantiate components on actors of the given classes. @param ReceiverClass		The class on which we should add the component onto @param ComponentClass		The component class to add on the new instance @param AdditionFlags (optional)	Set of flags to considered at component creation @return Returns a handle that will keep the request "alive" until all handles for the request are destructed, at which point the request is removed.
- L135 _public member_ `static FName NAME_ReceiverAdded;` — AddReceiver was called for a registered class and components were added, called early in initialization
- L138 _public member_ `static FName NAME_ReceiverRemoved;` — RemoveReceiver was called for a registered class and components were removed, normally called from EndPlay
- L141 _public member_ `static FName NAME_ExtensionAdded;` — A new extension handler was added
- L144 _public member_ `static FName NAME_ExtensionRemoved;` — An extension handler was removed by a freed request handle
- L150 _public member_ `static FName NAME_GameActorReady;` — Game-specific event indicating an actor is mostly initialized and ready for extension. All extensible games are expected to send this event at the appropriate actor-specific point, as plugins may be listening for it.
- L154 _public prototype_ `TSharedPtr<FComponentRequestHandle> AddExtensionHandler(const TSoftClassPtr<AActor>& ReceiverClass, FExtensionHandlerDelegate ExtensionHandler);` — Adds an extension handler to run on actors of the given class. Returns a handle that will keep the handler "alive" until it is destructed, at which point the delegate is removed
- L158 _public prototype_ `void SendExtensionEvent(AActor* Receiver, FName EventName, bool bOnlyInGameWorlds = true);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay", meta = (DefaultToSelf = "Receiver", AdvancedDisplay = 1))` — Sends an arbitrary extension event that can be listened for by other systems
- L161 _public prototype_ `static void SendGameFrameworkComponentExtensionEvent(AActor* Receiver, const FName& EventName, bool bOnlyInGameWorlds = true);` — Sends an arbitrary extension event that can be listened for by other systems
- L163 _public prototype_ `static void AddReferencedObjects(UObject* InThis, class FReferenceCollector& Collector);`
- L166 _public prototype_ `static void DumpGameFrameworkComponentManagers();`
- L171 _private prototype_ `void PostGC();`
- L174 _private prototype_ `void AddReceiverInternal(AActor* Receiver);`
- L175 _private prototype_ `void RemoveReceiverInternal(AActor* Receiver);`
- L176 _private prototype_ `void SendExtensionEventInternal(AActor* Receiver, const FName& EventName);`
- L179 _private prototype_ `void RemoveComponentRequest(const TSoftClassPtr<AActor>& ReceiverClass, TSubclassOf<UActorComponent> ComponentClass);` — Called by FComponentRequestHandle's destructor to remove a request for components to be created.
- L182 _private prototype_ `void RemoveExtensionHandler(const TSoftClassPtr<AActor>& ReceiverClass, FDelegateHandle DelegateHandle);` — Called by FComponentRequestHandle's destructor to remove a handler from the system.
- L185 _private prototype_ `EGameFrameworkAddComponentResult CreateComponentOnInstance(AActor* ActorInstance, TSubclassOf<UActorComponent> ComponentClass, const EGameFrameworkAddComponentFlags AdditionFlags = EGameFrameworkAddComponentFlags::None);` — Creates an instance of a component on an actor
- L188 _private prototype_ `void DestroyInstancedComponent(UActorComponent* Component);` — Removes an instance of a component on an actor
- L203 _private function_ `friend inline uint32 GetTypeHash(const FComponentRequestInfo& Request)`
- L265 _private function_ `friend inline uint32 GetTypeHash(const FComponentRequestReceiverClassPath& Request)`
- L287 _private function_ `friend inline uint32 GetTypeHash(const FComponentRequest& Request)`
- L320 _private typedef_ `using FExtensionHandlerEvent = TMap<FDelegateHandle, TSharedRef<FExtensionHandlerRegisteredDelegate>>;` — Using a fake multicast delegate so order can be kept consistent
- L323 _private member_ `TMap<FComponentRequest, int32> RequestTrackingMap;` — All active component requests. Used to avoid adding the same component twice if requested from multiple sources
- L326 _private member_ `TMap<UClass*, TSet<FObjectKey>> ComponentClassToComponentInstanceMap;` — A map of component classes to instances of that component class made by this component manager
- L329 _private member_ `TMap<FComponentRequestReceiverClassPath, TSet<FComponentRequestInfo>> ReceiverClassToComponentClassMap;` — A map of actor classes to component classes & addition flags that should be made for that class.
- L332 _private member_ `TMap<FComponentRequestReceiverClassPath, FExtensionHandlerEvent> ReceiverClassToEventMap;` — A map of actor classes to delegate handlers that should be executed for actors of that class.
- L336 _private member_ `TSet<FObjectKey> AllReceivers;` — Editor-only set to validate that component requests are only being added for actors that call AddReceiver and RemoveReceiver
- L349 _public prototype_ `void RegisterInitState(FGameplayTag NewState, bool bAddBefore, FGameplayTag ExistingState);` — Adds a new global actor feature state, either before or after an existing one. This will generally be called from game global or game feature initialization
- L352 _public prototype_ `bool IsInitStateAfterOrEqual(FGameplayTag FeatureState, FGameplayTag RelativeState) const;` — Returns true if FeatureState comes after the second state (or is equal)
- L355 _public prototype_ `FGameplayTag GetInitStateForFeature(AActor* Actor, FName FeatureName) const;` — Returns the earliest state found for the given feature
- L358 _public prototype_ `bool HasFeatureReachedInitState(AActor* Actor, FName FeatureName, FGameplayTag FeatureState) const;` — Returns true if feature has reached query state or later
- L361 _public prototype_ `UObject* GetImplementerForFeature(AActor* Actor, FName FeatureName, FGameplayTag RequiredState = FGameplayTag()) const;` — Returns the object implementing specified feature, filtered by required state if not none
- L364 _public prototype_ `void GetAllFeatureImplementers(TArray<UObject*>& OutImplementers, AActor* Actor, FGameplayTag RequiredState, FName ExcludingFeature = NAME_None) const;` — Gets all implementing objects for an actor that are at RequiredState or later, other than excluding feature if specified
- L367 _public prototype_ `bool HaveAllFeaturesReachedInitState(AActor* Actor, FGameplayTag RequiredState, FName ExcludingFeature = NAME_None) const;` — Checks to see if all features of object, other than the excluding feature if specified, have reached a specified state or later
- L370 _public prototype_ `bool ChangeFeatureInitState(AActor* Actor, FName FeatureName, UObject* Implementer, FGameplayTag FeatureState);` — Changes the current actor feature state, this will call registered callbacks and return true if anything changed
- L373 _public prototype_ `bool RegisterFeatureImplementer(AActor* Actor, FName FeatureName, UObject* Implementer);` — Registers an implementer for a given feature, this will create a feature if required and set the implementer object but will not change the current state
- L376 _public prototype_ `void RemoveActorFeatureData(AActor* Actor);` — Removes an actor and all of it's state information
- L379 _public prototype_ `void RemoveFeatureImplementer(AActor* Actor, UObject* Implementer);` — Removes an implementing object and any feature states it implements
- L391 _public prototype_ `FDelegateHandle RegisterAndCallForActorInitState(AActor* Actor, FName FeatureName, FGameplayTag RequiredState, FActorInitStateChangedDelegate Delegate, bool bCallImmediately = true);` — Registers native delegate for feature state change notifications on a specific actor and may call it immediately @param Actor				The actor to listen for state changes to, if you don't have a specific actor call the Class version instead @param FeatureName		If not empty, only listen to state changes for the specified feature @param RequiredState		If specified, only activate if the init state of the feature is equal to or later than this @param Delegate			Native delegate to call @param bCallImmediately	If true and the actor feature is already in the specified state, call delegate immediately after registering @return DelegateHandle used for later removal
- L394 _public prototype_ `bool UnregisterActorInitStateDelegate(AActor* Actor, FDelegateHandle& Handle);` — Removes a registered delegate bound to a specific actor
- L407 _public prototype_ `bool RegisterAndCallForActorInitState(AActor* Actor, FName FeatureName, FGameplayTag RequiredState, FActorInitStateChangedBPDelegate Delegate, bool bCallImmediately = true);` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Registers blueprint delegate for feature state change notifications on a specific actor and may call it immediately @param Actor				The actor to listen for state changes to, if you don't have a specific actor call the Class version instead @param FeatureName		If not empty, only listen to state changes for the specified feature @param RequiredState		If specified, only activate if the init state of the feature is equal to or later than this @param Delegate			Native delegate to call @param bCallImmediately	If true and the actor feature is already in the specified state, call delegate immediately after registering @return true if delegate was registered
- L411 _public prototype_ `bool UnregisterActorInitStateDelegate(AActor* Actor, FActorInitStateChangedBPDelegate DelegateToRemove);` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Removes a registered delegate bound to a specific actor
- L424 _public prototype_ `FDelegateHandle RegisterAndCallForClassInitState(const TSoftClassPtr<AActor>& ActorClass, FName FeatureName, FGameplayTag RequiredState, FActorInitStateChangedDelegate Delegate, bool bCallImmediately = true);` — Registers native delegate for feature state change notifications on a class of actors and may call it immediately @param ActorClass		Name of an actor class to listen for changes to @param FeatureName		If not empty, only listen to state changes for the specified feature @param RequiredState		If specified, only activate if the init state of the feature is equal to or later than this @param Delegate			Native delegate to call @param bCallImmediately	If true and the actor feature is already in the specified state, call delegate immediately after registering @return DelegateHandle used for later removal
- L427 _public prototype_ `bool UnregisterClassInitStateDelegate(const TSoftClassPtr<AActor>& ActorClass, FDelegateHandle& Handle);` — Removes a registered delegate bound to a class
- L440 _public prototype_ `bool RegisterAndCallForClassInitState(TSoftClassPtr<AActor> ActorClass, FName FeatureName, FGameplayTag RequiredState, FActorInitStateChangedBPDelegate Delegate, bool bCallImmediately = true);` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Registers blueprint delegate for feature state change notifications on a class of actors and may call it immediately @param ActorClass		Name of an actor class to listen for changes to @param FeatureName		If not empty, only listen to state changes for the specified feature @param RequiredState		If specified, only activate if the init state of the feature is equal to or later than this @param Delegate			Native delegate to call @param bCallImmediately	If true and the actor feature is already in the specified state, call delegate immediately after registering @return true if delegate was registered
- L444 _public prototype_ `bool UnregisterClassInitStateDelegate(TSoftClassPtr<AActor> ActorClass, FActorInitStateChangedBPDelegate DelegateToRemove);` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Removes a registered delegate bound to a class
- L449 _private member_ `TArray<FGameplayTag> InitStateOrder;` — List of all registered feature states in order
- L502 _private typedef_ `using FActorFeatureDelegateList = TArray<TSharedRef<FActorFeatureRegisteredDelegate>>;` — Always stored as shared refs to avoid being destroyed during execution
- L521 _private member_ `TMap<FObjectKey, FActorFeatureData> ActorFeatureMap;` — Actors that were registered as tracking feature state
- L524 _private member_ `TMap<FComponentRequestReceiverClassPath, FActorFeatureDelegateList> ClassFeatureChangeDelegates;` — Global delegates for any class name
- L527 _private member_ `TArray<TPair<AActor*, FActorFeatureState> > StateChangeQueue;` — A queue of state changes to call delegates for, we don't want recursive callbacks
- L530 _private member_ `int32 CurrentStateChange;` — Position in state change queue, INDEX_NONE means not actively handling
- L533 _private prototype_ `const FActorFeatureState* FindFeatureStateStruct(const FActorFeatureData* ActorStruct, FName FeatureName, FGameplayTag RequiredState = FGameplayTag()) const;` — Find an appropriate state struct if it exists
- L536 _private prototype_ `void ProcessFeatureStateChange(AActor* Actor, const FActorFeatureState* StateChange);` — Add to queue for delegate processing
- L539 _private prototype_ `void CallFeatureStateDelegates(AActor* Actor, FActorFeatureState StateChange);` — Call all delegates for a specific actor feature change
- L542 _private prototype_ `void CallDelegateForMatchingFeatures(AActor* Actor, FActorFeatureRegisteredDelegate& RegisteredDelegate);` — Call the specified delegate for all matching features on the actor, this should be passed a copy of the original delegate
- L545 _private prototype_ `void CallDelegateForMatchingActors(UClass* ActorClass, FActorFeatureRegisteredDelegate& RegisteredDelegate);` — Call the specified delegate for all matching actors and features, this should be passed a copy of the original delegate
- L548 _private prototype_ `FActorFeatureData& FindOrAddActorData(AActor* Actor);` — Gets or creates the actor struct
- L551 _private prototype_ `bool RemoveActorFeatureDelegateFromList(FActorFeatureDelegateList& DelegateList, FDelegateHandle& SearchHandle) const;` — Try to removes delegate from list, returns true if it removed anything and clear handle if required
- L552 _private prototype_ `bool RemoveActorFeatureDelegateFromList(FActorFeatureDelegateList& DelegateList, FActorInitStateChangedBPDelegate SearchDelegate) const;`
- L555 _private prototype_ `void PruneUnboundDelegates(TConstArrayView<UPackage*> Packages);` — Unregister all class feature change delegates in the relevant packages

#### struct `UGameFrameworkComponentManager::FComponentRequestInfo`  
`struct FComponentRequestInfo`  
_L191-213_
- desc: A pair holding a receiver class and AdditionFlags
- L193 _public function_ `FComponentRequestInfo(UClass* InClass, const EGameFrameworkAddComponentFlags InAdditionFlags = EGameFrameworkAddComponentFlags::None) : Class(InClass) , AdditionFlags(InAdditionFlags)`
- L198 _public function_ `bool operator==(const FComponentRequestInfo& Other) const`
- L209 _public member_ `TObjectPtr<UClass> Class;` — The receiver class
- L212 _public member_ `EGameFrameworkAddComponentFlags AdditionFlags = EGameFrameworkAddComponentFlags::None;` — Observe these rules when adding the component, if any

#### struct `UGameFrameworkComponentManager::FComponentRequestReceiverClassPath`  
`struct FComponentRequestReceiverClassPath`  
_L216-274_
- desc: A list of FNames to represent an object path. Used for fast hashing and comparison of paths
- L219 _public member_ `TArray<FName, TInlineAllocator<2>> Path;` — Usually only 2 elements long. Ex [UPackage FName, UClass FName]
- L221 _public function_ `FComponentRequestReceiverClassPath()`
- L223 _public function_ `FComponentRequestReceiverClassPath(UClass* InClass)`
- L232 _public function_ `FComponentRequestReceiverClassPath(const TSoftClassPtr<AActor>& InSoftClassPtr)`
- L244 _public function_ `FString ToDebugString() const`
- L260 _public function_ `bool operator==(const FComponentRequestReceiverClassPath& Other) const`

#### struct `UGameFrameworkComponentManager::FComponentRequest`  
`struct FComponentRequest`  
_L277-291_
- desc: A pair of classes that describe a request. Together these form a key that is used to batch together requests that are identical and reference count them
- L279 _public member_ `FComponentRequestReceiverClassPath ReceiverClassPath;`
- L280 _public member_ `UClass* ComponentClass;`
- L282 _public function_ `bool operator==(const FComponentRequest& Other) const`

#### struct `UGameFrameworkComponentManager::FExtensionHandlerRegisteredDelegate`  
`struct FExtensionHandlerRegisteredDelegate`  
_L294-317_
- desc: Stores a delegate as shared ref to avoid deallocation during execution
- L297 _public member_ `FExtensionHandlerDelegate Delegate;` — Delegate to call
- L300 _public member_ `bool bRemoved;` — Has this been removed, if so do not call
- L303 _public function_ `FExtensionHandlerRegisteredDelegate(FExtensionHandlerDelegate&& InDelegate) : Delegate(InDelegate) , bRemoved(false)` — Construct from an existing delegate, there is no default constructor
- L310 _public function_ `void Execute(AActor* OwningActor, FName EventName)` — Call Delegate if it is valid

#### struct `UGameFrameworkComponentManager::FActorFeatureState`  
`struct FActorFeatureState`  
_L452-464_
- desc: State for a specific object implementing an actor feature, should this be in a map instead of an array?
- L454 _public function_ `FActorFeatureState(FName InFeatureName) : FeatureName(InFeatureName)`
- L457 _public member_ `FName FeatureName;` — The feature this is tracking
- L460 _public member_ `FGameplayTag CurrentState;` — The state when it was last registered
- L463 _public member_ `TWeakObjectPtr<UObject> Implementer;` — The object implementing this feature, this can be null

#### struct `UGameFrameworkComponentManager::FActorFeatureRegisteredDelegate`  
`struct FActorFeatureRegisteredDelegate`  
_L467-499_
- desc: Holds the list of feature delegates
- L470 _public prototype_ `FActorFeatureRegisteredDelegate(FActorInitStateChangedDelegate&& InDelegate, FName InFeatureName = NAME_None, FGameplayTag InInitState = FGameplayTag());` — Construct from a native or BP Delegate
- L471 _public prototype_ `FActorFeatureRegisteredDelegate(FActorInitStateChangedBPDelegate&& InDelegate, FName InFeatureName = NAME_None, FGameplayTag InInitState = FGameplayTag());`
- L474 _public prototype_ `void Execute(AActor* OwningActor, FName FeatureName, UObject* Implementer, FGameplayTag FeatureState);` — Call the appropriate native/bp delegate, this could invalidate this struct
- L477 _public function_ `bool IsBound() const` — Check whether this delegate has a valid registration
- L483 _public member_ `FActorInitStateChangedDelegate Delegate;` — Delegate that is called on notification
- L486 _public member_ `FActorInitStateChangedBPDelegate BPDelegate;` — BP delegate that is called on notification
- L489 _public member_ `FDelegateHandle DelegateHandle;` — A handle assigned to this delegate so it acts like a multicast delegate for removal
- L492 _public member_ `FName RequiredFeatureName;` — If this is not null, will only activate for specific feature names
- L495 _public member_ `FGameplayTag RequiredInitState;` — If this is not null, will only activate for states >= to this
- L498 _public member_ `bool bRemoved;` — Indicates this delegate has been removed and will soon be destroyed, do not execute

#### struct `UGameFrameworkComponentManager::FActorFeatureData`  
`struct FActorFeatureData`  
_L505-518_
- desc: Information for each registered actor
- L508 _public member_ `TWeakObjectPtr<UClass> ActorClass;` — Actor class for cross referencing with the class callbacks
- L511 _public member_ `TArray<FActorFeatureState> RegisteredStates;` — All active features
- L514 _public member_ `FActorFeatureDelegateList RegisteredDelegates;` — All delegates bound to this actor
- L517 _public prototype_ `~FActorFeatureData();` — Properly clear delegate list

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODULARGAMEPLAY_API`
- L31 _prototype_ `ENUM_CLASS_FLAGS(EGameFrameworkAddComponentFlags);`
- L77 _delegate_ `DECLARE_DELEGATE_OneParam(FActorInitStateChangedDelegate, const FActorInitStateChangedParams&);` — Native delegate called when an actor feature changes init state
- L77 _prototype_ `DECLARE_DELEGATE_OneParam(FActorInitStateChangedDelegate, const FActorInitStateChangedParams&);` — Native delegate called when an actor feature changes init state
- L96 _delegate_ `DECLARE_DELEGATE_TwoParams(FExtensionHandlerDelegate, AActor*, FName);` — Delegate types for extension handlers

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/Components/GameFrameworkInitStateInterface.h` (Public)


#### class `UGameFrameworkInitStateInterface`  
`class UGameFrameworkInitStateInterface : public UInterface`  
_L18-21_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintable)`
- inherits: `UInterface`
- desc: Interface that can be implemented by actors/components to make interacting with the init state system easier

#### class `IGameFrameworkInitStateInterface`  
`class IGameFrameworkInitStateInterface`  
_L23-90_
- L29 _public prototype_ `virtual AActor* GetOwningActor() const;` — Returns the Actor this object is bound to, might be this object
- L32 _public prototype_ `UGameFrameworkComponentManager* GetComponentManager() const;` — Gets the component manager corresponding to this object based on owning actor
- L36 _public function_ `virtual FName GetFeatureName() const` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Returns the feature this object implements, this interface is only meant for simple objects with a single feature like Actor
- L40 _public prototype_ `virtual FGameplayTag GetInitState() const;` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Returns the current feature state of this object, the default behavior is to query the manager
- L44 _public prototype_ `virtual bool HasReachedInitState(FGameplayTag DesiredState) const;` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Checks the component manager to see if we have already reached the desired state or a later one
- L47 _public function_ `virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const` — Should be overridden to perform class-specific checks to see if the desired state can be reached
- L50 _public function_ `virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)` — Should be overridden to perform class-specific state changes, this is called right before notifying the component manager
- L53 _public prototype_ `virtual bool TryToChangeInitState(FGameplayTag DesiredState);` — Checks to see if a change is possible, then calls execute and notify
- L56 _public prototype_ `virtual FGameplayTag ContinueInitStateChain(const TArray<FGameplayTag>& InitStateChain);` — Tries to follow a chain of connected init states, will progress states in order and returns the final state reached
- L59 _public function_ `virtual void CheckDefaultInitialization()` — Override to try and progress the default initialization path, likely using ContinueInitStateChain
- L62 _public prototype_ `virtual void CheckDefaultInitializationForImplementers();` — This will call CheckDefaultInitialization on all other feature implementers using this interface, useful to update the state of any dependencies
- L65 _public function_ `virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params)` — Signature for handling a game feature state, this is not registered by default
- L68 _public prototype_ `virtual void BindOnActorInitStateChanged(FName FeatureName, FGameplayTag RequiredState, bool bCallIfReached);` — Call to bind the OnActorInitStateChanged function to the appropriate delegate on the component manager
- L71 _public prototype_ `virtual void RegisterInitStateFeature();` — Call to register with the component manager during spawn if this is a game world
- L74 _public prototype_ `virtual void UnregisterInitStateFeature();` — Unregisters state and delegate binding with component manager
- L78 _public prototype_ `virtual bool RegisterAndCallForInitStateChange(FGameplayTag RequiredState, FActorInitStateChangedBPDelegate Delegate, bool bCallImmediately = true);` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Binds a BP delegate to get called on a state change for this feature
- L82 _public prototype_ `virtual bool UnregisterInitStateDelegate(FActorInitStateChangedBPDelegate Delegate);` — `UFUNCTION(BlueprintCallable, Category = "InitState")` — Unbinds a BP delegate from changes to this feature
- L85 _public prototype_ `virtual FString GetDebugState() const;` — Returns Current state and any additional debug information for the active state
- L89 _protected member_ `FDelegateHandle ActorInitStateChangedHandle;` — Default handle created from calling BindOnActorInitStateChanged

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODULARGAMEPLAY_API`

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/Components/GameStateComponent.h` (Public)


#### class `UGameStateComponent`  
`class UGameStateComponent : public UGameFrameworkComponent`  
_L16-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameFrameworkComponent`
- desc: GameStateComponent is an actor component made for AGameStateBase and receives GameState events.
- L22 _public prototype_ `UGameStateComponent(const FObjectInitializer& ObjectInitializer);`
- L26 _public function_ `template <class T> T* GetGameState() const` — Gets the game state that owns the component, this will always be valid during gameplay but can return null in the editor
- L33 _public function_ `template <class T> T* GetGameStateChecked() const`
- L45 _public function_ `template <class T> T* GetGameMode() const` — Gets the game mode that owns this component, this will always return null on the client
- L60 _public function_ `virtual void HandleMatchHasStarted()` — Called when gameplay has fully started
- L63 _public function_ `virtual void HandleMatchHasEnded()` — Called when gameplay has fully ended

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODULARGAMEPLAY_API`

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/Components/PawnComponent.h` (Public)


#### class `UPawnComponent`  
`class UPawnComponent : public UGameFrameworkComponent`  
_L17-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameFrameworkComponent`
- desc: PawnComponent is an actor component made for APawn and receives pawn events.
- L23 _public prototype_ `UPawnComponent(const FObjectInitializer& ObjectInitializer);`
- L27 _public function_ `template <class T> T* GetPawn() const` — Gets the pawn that owns the component, this will always be valid during gameplay but can return null in the editor
- L34 _public function_ `template <class T> T* GetPawnChecked() const`
- L46 _public function_ `template <class T> T* GetPlayerState() const` — Gets the player state that owns the component, this can return null on clients for player pawns that are still being replicated
- L54 _public function_ `template <class T> T* GetController() const` — Gets the controller that owns the component, this will usually be null on clients

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODULARGAMEPLAY_API`

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/Components/PlayerStateComponent.h` (Public)


#### class `UPlayerStateComponent`  
`class UPlayerStateComponent : public UGameFrameworkComponent`  
_L17-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameFrameworkComponent`
- desc: PlayerStateComponent is an actor component made for APlayerState and receives PlayerState events.
- L23 _public prototype_ `UPlayerStateComponent(const FObjectInitializer& ObjectInitializer);`
- L27 _public function_ `template <class T> T* GetPlayerState() const` — Gets the player state that owns the component, this will always be valid during gameplay but can return null in the editor
- L34 _public function_ `template <class T> T* GetPlayerStateChecked() const`
- L46 _public function_ `template <class T> T* GetPawn() const` — Gets the pawn that owns the component, this will return null if the pawn does not exist or is still replicating
- L59 _public function_ `virtual void Reset()` — Reset properties to default state
- L62 _public function_ `virtual void CopyProperties(UPlayerStateComponent* TargetPlayerStateComponent)` — Copy properties which need to be saved in inactive PlayerState

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODULARGAMEPLAY_API`

### `Plugins/Runtime/ModularGameplay/Source/ModularGameplay/Public/ModularGameplayModule.h` (Public)


#### class `IModularGameplayModule`  
`class IModularGameplayModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L10 _public function_ `static inline IModularGameplayModule& Get()`
