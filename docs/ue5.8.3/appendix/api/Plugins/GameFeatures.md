# Plugins / GameFeatures

- module root: `Plugins/Runtime/GameFeatures/Source/GameFeatures`
- headers: 27; symbols: 1101
- symbol kinds: class=28, delegate=10, enum=14, enumerator=51, externvar=7, function=112, macro=24, member=228, namespace=27, prototype=535, struct=41, typedef=24
- PrivateDependencyModuleNames: AssetRegistry, GameplayTags, InstallBundleManager, IoStoreOnDemandCore, IrisCore, Json, JsonUtilities, PakFile, PlacementMode, PluginUtils, Projects, RenderCore, TraceLog, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DataRegistry, DeveloperSettings, Engine, ModularGameplay
- PublicIncludePathModuleNames: IoStoreOnDemandCore

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Private/GameFeatureDataAssetDependencyGatherer.h` (Private)


#### class `FGameFeatureDataAssetDependencyGatherer`  
`class FGameFeatureDataAssetDependencyGatherer : public IAssetDependencyGatherer`  
_L9-17_
- inherits: `IAssetDependencyGatherer`
- L13 _public prototype_ `FGameFeatureDataAssetDependencyGatherer() = default;`
- L14 _public prototype_ `virtual ~FGameFeatureDataAssetDependencyGatherer() = default;`
- L16 _public prototype_ `virtual void GatherDependencies(FGatherDependenciesContext& Context) const override;`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Private/GameFeaturePluginStateMachine.h` (Private)


#### class `UE::GameFeatures::FStateMachineExecutor`  
`class FStateMachineExecutor`  
_L179-239_
- L182 _private typedef_ `using FStateMachineId = int64;` — State machines are addressed by FGameFeaturePluginStateMachineProperties::Id
- L185 _private member_ `TArray<FStateMachineId> OrderedUpdateQueue;` — Lists of state machines requiring updates stored by the order in which a deferred update request was made
- L186 _private member_ `UGameFeaturesSubsystem* OwningSubsystem = nullptr;`
- L192 _private member_ `bool bPauseImmediateExecution = false;` — If this is true, state machine update requests through TryUpdateStateMachineImmediate will be queued as if QueueUpdateStateMachine had been called instead
- L198 _private prototype_ `bool UpdateStateMachinesGrouped(double StartTime, float DeltaTime, EGameFeaturePluginState State, TConstArrayView<UGameFeaturePluginStateMachine*> StateMachines);` — Update a set of state machines which are expected to be in the same state. Returns true in realtime mode if time limit was exhausted.
- L202 _private prototype_ `template<EGameFeaturePluginState State> bool UpdateStateMachinesGrouped(double StartTime, float DeltaTime, TConstArrayView<UGameFeaturePluginStateMachine*> StateMachines);` — Templated to allow custom implementation per state
- L205 _private prototype_ `bool UpdateStateMachinesRealtime(double StartTime, float DeltaTime, TConstArrayView<UGameFeaturePluginStateMachine*> StateMachines);` — Helper to update a list of state machines, requeing if we run out of time
- L208 _public prototype_ `FStateMachineExecutor(UGameFeaturesSubsystem* InOwningSubsystem);`
- L209 _public prototype_ `~FStateMachineExecutor();`
- L213 _public prototype_ `bool UpdateStateMachines(float DeltaTime, int32 MaxIterations = 10000);` — Update all state machines which are not at their target state and are not waiting on async work to complete
- L219 _public prototype_ `bool PauseExecution();` — Pause immediate execution of state machine updates and return whether it was already paused. The return value should be passed back to TryResumeExecution from a scoped object.
- L225 _public prototype_ `void TryResumeExecution(bool bInStayPaused);` — Try and resume immediately executing state machines. If the argument is false, execution is resumed and any queued updates are performed.
- L231 _public prototype_ `void QueueUpdateStateMachine(FGameFeaturePluginStateMachineProperties& InProperties);` — Store the given state machine as needing to be updated to transition to the next state TODO: Do we need a delay timer, or can that be replaced with proper events?
- L237 _public prototype_ `void TryUpdateStateMachineImmediate(FGameFeaturePluginStateMachineProperties& InProperties);` — If immediate execution is allowed, update the given state machine. Otherwise queue it for deferred execution.
- L238 _public prototype_ `void TryUpdateStateMachineImmediate(int64 Id);`

#### struct `UE::GameFeatures::FScopedPauseStateMachineExecution`  
`struct FScopedPauseStateMachineExecution`  
_L241-250_
- L243 _public prototype_ `FScopedPauseStateMachineExecution(FStateMachineExecutor* InExecutor);`
- L244 _public prototype_ `~FScopedPauseStateMachineExecution();`
- L248 _private member_ `FStateMachineExecutor* Executor = nullptr;`
- L249 _private member_ `bool bOldPaused = false;`

#### struct `FGameFeaturePluginStateRange`  
`struct FGameFeaturePluginStateRange`  
_L255-300_
- desc: Represents an inclusive range of states which it is acceptable for a GFP to be in
- L257 _public member_ `EGameFeaturePluginState MinState = EGameFeaturePluginState::Uninitialized;`
- L258 _public member_ `EGameFeaturePluginState MaxState = EGameFeaturePluginState::Uninitialized;`
- L260 _public prototype_ `FGameFeaturePluginStateRange() = default;`
- L262 _public function_ `FGameFeaturePluginStateRange(EGameFeaturePluginState InMinState, EGameFeaturePluginState InMaxState) : MinState(InMinState), MaxState(InMaxState)`
- L266 _public function_ `explicit FGameFeaturePluginStateRange(EGameFeaturePluginState InState) : MinState(InState), MaxState(InState)`
- L270 _public function_ `bool IsValid() const`
- L273 _public function_ `bool Contains(EGameFeaturePluginState InState) const` — Returns whether a given single state is inside this range
- L279 _public function_ `bool Overlaps(const FGameFeaturePluginStateRange& Other) const` — Returns whether there are any states in common between this range and another range
- L285 _public function_ `TOptional<FGameFeaturePluginStateRange> Intersect(const FGameFeaturePluginStateRange& Other) const` — If there are any states in common between this range and another range, return a new range representing those states.
- L297 _public function_ `bool operator==(const FGameFeaturePluginStateRange& Other) const`
- L298 _public function_ `bool operator<(const FGameFeaturePluginStateRange& Other) const`
- L299 _public function_ `bool operator>(const FGameFeaturePluginStateRange& Other) const`

#### struct `FInstallBundlePluginProtocolMetaData`  
`struct FInstallBundlePluginProtocolMetaData`  
_L325-336_
- L327 _public prototype_ `FInstallBundlePluginProtocolMetaData() = default;`
- L328 _public function_ `FInstallBundlePluginProtocolMetaData(TArray<FName> InInstallBundles) : InstallBundles(MoveTemp(InInstallBundles))`
- L330 _public member_ `TArray<FName> InstallBundles;`
- L331 _public member_ `TArray<FName> InstallBundlesWithAssetDependencies;`
- L334 _public prototype_ `FString ToString() const;` — Functions to convert to/from the URL FString representation of this metadata
- L335 _public prototype_ `static TValueOrError<FInstallBundlePluginProtocolMetaData, FString> FromString(FStringView URLOptionsString);`

#### struct `FGameFeatureProtocolMetadata`  
`struct FGameFeatureProtocolMetadata : public TUnion<FInstallBundlePluginProtocolMetaData, FNull>`  
_L338-343_
- inherits: `TUnion<FInstallBundlePluginProtocolMetaData,FNull>`
- L340 _public function_ `FGameFeatureProtocolMetadata()`
- L341 _public function_ `FGameFeatureProtocolMetadata(const FInstallBundlePluginProtocolMetaData& InData) : TUnion(InData)`
- L342 _public function_ `FGameFeatureProtocolMetadata(FNull InOptions)`

#### struct `FGameFeaturePluginStateMachineProperties`  
`struct FGameFeaturePluginStateMachineProperties`  
_L359-473_
- reflection: `USTRUCT()`
- desc: The common properties that can be accessed by the states of the state machine
- L367 _public member_ `int64 Id = 0;` — Integer identifier for this plugin when the UGameFeaturePluginStateMachine was created. Is not stable across termination and recreation of the state machine for this plugin.
- L370 _public member_ `EGameFeaturePluginState CurrentState = EGameFeaturePluginState::Uninitialized;` — Current state of the state machine. Should not be modified by states themselves, only by UpdateStateMachine or FStateMachineExecutor
- L375 _public member_ `EGameFeaturePluginState MaximumState = EGameFeaturePluginState::Active;` — Maximum allowed state for this plugin to reach. e.g. some plugins may only be allowed to reach Registered in the editor for their assets to be worked on, but they cannot be activated in PIE.
- L378 _public member_ `bool bQueuedForUpdate = false;` — Whether this GFP is in the queue in FStateMachineExecutor
- L381 _public member_ `float StateProgress = 0.0f;` — The progress of the current state. Relevant only for transition states.
- L388 _public member_ `FGameFeaturePluginIdentifier PluginIdentifier;` — The Identifier used to find this Plugin. Parsed from the supplied PluginURL at creation. Every protocol will have its own style of identifier URL that will get parsed to generate this. For example, if the file is simply on disk, you can use file:../../../YourGameModule/Plugins/MyPlugin/MyPlugin.uplugin
- L391 _public member_ `FString PluginInstalledFilename;` — Filename on disk of the .uplugin file.
- L394 _public member_ `FString PluginName;` — Name of the plugin.
- L397 _public member_ `FGameFeatureProtocolMetadata ProtocolMetadata;` — Metadata parsed from the URL for a specific protocol.
- L400 _public member_ `FGameFeatureProtocolOptions ProtocolOptions;` — Additional options for a specific protocol.
- L403 _public member_ `FGameFeaturePluginStateRange Destination;` — The desired state during a transition.
- L406 _public member_ `bool bIsLoadingLocalizationData : 1 = false;` — Whether this plugin has an async localization load in-flight
- L409 _public member_ `bool bAddedPluginToManager : 1 = false;` — Tracks whether or not this state machine added the plugin to the plugin manager.
- L412 _public member_ `bool bWasLoadedAsBuiltInGameFeaturePlugin : 1 = false;` — Was this plugin loaded using LoadBuiltInGameFeaturePlugin
- L415 _public member_ `bool bTryCancel : 1 = false;` — Whether this state machine should attempt to cancel the current transition
- L418 _public member_ `bool bWasBatchProcessed : 1 = false;` — Tracks if the current state was batch processed
- L421 _public member_ `FDelegateHandle BatchProcessingHandle;` — Batch Processing handle if requested for batch processed
- L423 _public member_ `TArray<FName> AddedPrimaryAssetTypes;`
- L427 _public member_ `TObjectPtr<UGameFeatureData> GameFeatureData = nullptr;` — `UPROPERTY(Transient)` — The data asset describing this game feature
- L430 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTransitionCanceled, UGameFeaturePluginStateMachine* );` — Callbacks for when the current state transition is cancelled
- L431 _public member_ `FOnTransitionCanceled OnTransitionCanceled;`
- L433 _public prototype_ `FGameFeaturePluginStateMachineProperties() = default;`
- L434 _public prototype_ `FGameFeaturePluginStateMachineProperties( int64 InId, FGameFeaturePluginIdentifier InPluginIdentifier, EGameFeaturePluginState InitialState, UE::GameFeatures::FStateMachineExecutor* Executor, const FGameFeaturePluginRequestUpdateStateMachine& RequestUpdateStateMachineDelegate);`
- L441 _public prototype_ `EGameFeaturePluginProtocol GetPluginProtocol() const;`
- L443 _public prototype_ `TValueOrError<void, FString> ParseURL();`
- L446 _public prototype_ `UE::GameFeatures::FResult ValidateProtocolOptionsUpdate(const FGameFeatureProtocolOptions& NewProtocolOptions) const;` — Checks to see if any invalid data was changed during a URL update. True if data updated was all values expected to be changed.
- L449 _public prototype_ `FGameFeatureProtocolOptions RecycleProtocolOptions() const;` — Returns protocol options suitable for reuse by another state machine
- L452 _public prototype_ `bool AllowAsyncLoading() const;` — Whether this machine is allowed to be asynchronous
- L454 _public prototype_ `bool CanBatchProcess() const;`
- L455 _public prototype_ `bool IsWaitingForBatchProcessing() const;`
- L456 _public prototype_ `bool WasBatchProcessed() const;`
- L458 _public prototype_ `void UpdateStateMachineImmediate();`
- L463 _public prototype_ `bool UpdateStateMachineDeferred(float Delay);` — Queues an update for this state machine in the executor if it is being used and returns true. Returns false if the executor is not being used
- L469 _private member_ `FGameFeaturePluginRequestUpdateStateMachine OnRequestUpdateStateMachine;` — Delegate to request the state machine be updated.
- L472 _private member_ `UE::GameFeatures::FStateMachineExecutor* Executor = nullptr;` — Object responsible for scheduling state machine updates when UE::GameFeatures::bUseNewExecutor is true

#### struct `FGameFeaturePluginStateStatus`  
`struct FGameFeaturePluginStateStatus`  
_L476-494_
- desc: Input and output information for a state's UpdateState
- L480 _private member_ `UE::GameFeatures::FResult TransitionResult = MakeValue();` — Holds the current error for any state transition.
- L483 _private member_ `EGameFeaturePluginState TransitionToState = EGameFeaturePluginState::Uninitialized;` — The state to transition to after UpdateState is complete.
- L486 _private member_ `bool bSuppressErrorLog = false;` — Whether to suppress error logging if TransitionResult is an error.
- L492 _public prototype_ `void SetTransition(EGameFeaturePluginState InTransitionToState);`
- L493 _public prototype_ `void SetTransitionError(EGameFeaturePluginState TransitionToErrorState, UE::GameFeatures::FResult TransitionResult, bool bInSuppressErrorLog = false);`

#### enum `EGameFeaturePluginStateType`  
`enum class EGameFeaturePluginStateType : uint8`  
_L496-501_
- L498 _public enumerator_ `Transition`
- L499 _public enumerator_ `Destination`
- L500 _public enumerator_ `Error`

#### struct `FGameFeaturePluginState`  
`struct FGameFeaturePluginState`  
_L507-572_
- desc: Base class for all game feature plugin states
- L509 _public function_ `FGameFeaturePluginState(EGameFeaturePluginState InState, FGameFeaturePluginStateMachineProperties& InStateProperties) : StateProperties(InStateProperties) , State(InState)`
- L514 _public prototype_ `virtual ~FGameFeaturePluginState();`
- L517 _public function_ `virtual void BeginState()` — Called when this state becomes the active state
- L520 _public function_ `virtual void UpdateState(FGameFeaturePluginStateStatus& StateStatus)` — Process the state's logic to decide if there should be a state transition.
- L523 _public function_ `virtual void TryCancelState()` — Attempt to cancel any pending state transition.
- L527 _public prototype_ `virtual UE::GameFeatures::FResult TryUpdateProtocolOptions(const FGameFeatureProtocolOptions& NewOptions);` — Called if we have updated the protocol options for this FGameFeaturePluginState. Returns false if no update occured or the update failed. True on successful update.
- L530 _public function_ `virtual void EndState()` — Called when this state is no longer the active state
- L533 _public function_ `virtual EGameFeaturePluginStateType GetStateType() const` — Returns the type of state this is
- L535 _public prototype_ `FDestinationGameFeaturePluginState* AsDestinationState();`
- L536 _public prototype_ `FErrorGameFeaturePluginState* AsErrorState();`
- L539 _public member_ `FGameFeaturePluginStateMachineProperties& StateProperties;` — The common properties that can be accessed by the states of the state machine
- L540 _public member_ `EGameFeaturePluginState State;`
- L542 _public prototype_ `void UpdateStateMachineDeferred(float Delay = 0.0f) const;`
- L543 _public prototype_ `void UpdateStateMachineImmediate() const;`
- L545 _public prototype_ `void UpdateProgress(float Progress) const;`
- L547 _public prototype_ `virtual bool CanBatchProcess() const;`
- L548 _public prototype_ `bool IsWaitingForBatchProcessing() const;`
- L549 _public prototype_ `bool WasBatchProcessed() const;`
- L554 _protected prototype_ `UE::GameFeatures::FResult GetErrorResult(const FString& ErrorCode, const FText OptionalErrorText = FText()) const;` — Builds an end FResult with some minimal error information with overrides for common types we need to generate errors from
- L555 _protected prototype_ `UE::GameFeatures::FResult GetErrorResult(const FString& ErrorNamespaceAddition, const FString& ErrorCode, const FText OptionalErrorText = FText()) const;`
- L556 _protected prototype_ `UE::GameFeatures::FResult GetErrorResult(const FString& ErrorNamespaceAddition, const EInstallBundleResult ErrorResult) const;`
- L557 _protected prototype_ `UE::GameFeatures::FResult GetErrorResult(const FString& ErrorNamespaceAddition, const EInstallBundleReleaseResult ErrorResult) const;`
- L561 _protected prototype_ `bool ShouldVisitUninstallStateBeforeTerminal() const;` — Returns true if this state should transition to the Uninstalled state. returns False if it should just go directly to the Terminal state instead.
- L563 _protected prototype_ `bool AllowIniLoading() const;`
- L565 _protected prototype_ `bool AllowAsyncLoading() const;`
- L566 _protected prototype_ `virtual bool UseAsyncLoading() const;`
- L569 _private prototype_ `void CleanupDeferredUpdateCallbacks() const;`
- L571 _private member_ `mutable FTSTicker::FDelegateHandle TickHandle;`

#### struct `FDestinationGameFeaturePluginState`  
`struct FDestinationGameFeaturePluginState : public FGameFeaturePluginState`  
_L575-592_
- inherits: `FGameFeaturePluginState`
- desc: Base class for destination game feature plugin states
- L580 _public prototype_ `virtual void EndState() override final;` — Called when this state is no longer the active state
- L582 _public prototype_ `virtual void TryCancelState() override final;` — Attempt to cancel any pending state transition.
- L585 _public function_ `virtual EGameFeaturePluginStateType GetStateType() const override` — Returns the type of state this is
- L588 _public prototype_ `virtual void UpdateState(FGameFeaturePluginStateStatus& StateStatus) override final;` — Process the state's logic to decide if there should be a state transition.
- L590 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestinationStateReached, UGameFeaturePluginStateMachine* , const UE::GameFeatures::FResult& );`
- L591 _public member_ `FOnDestinationStateReached OnDestinationStateReached;`

#### struct `FErrorGameFeaturePluginState`  
`struct FErrorGameFeaturePluginState : public FDestinationGameFeaturePluginState`  
_L595-601_
- inherits: `FDestinationGameFeaturePluginState`
- desc: Base class for error game feature plugin states
- L600 _public function_ `virtual EGameFeaturePluginStateType GetStateType() const override` — Returns the type of state this is

#### struct `FGameFeaturePluginStateInfo`  
`struct FGameFeaturePluginStateInfo`  
_L604-618_
- desc: Information about a given plugin state, used to expose information to external code
- L607 _public member_ `EGameFeaturePluginState State = EGameFeaturePluginState::Uninitialized;` — The state this info represents
- L610 _public member_ `float Progress = 0.0f;` — The progress of this state. Relevant only for transition states.
- L612 _public prototype_ `FGameFeaturePluginStateInfo() = default;`
- L613 _public function_ `explicit FGameFeaturePluginStateInfo(EGameFeaturePluginState InState, float InProgress = 0.0f) : State(InState) , Progress(InProgress)`

#### class `UGameFeaturePluginStateMachine`  
`class UGameFeaturePluginStateMachine : public UObject`  
_L622-650_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A state machine to manage transitioning a game feature plugin from just a URL into a fully loaded and active plugin, including registering its contents with other game systems
- L627 _public prototype_ `UGameFeaturePluginStateMachine(const FObjectInitializer& ObjectInitializer);`
- L629 _public prototype_ `FDestinationGameFeaturePluginState* AsDestinationState(FGameFeaturePluginState* InState);`
- L634 _public member_ `FGameFeaturePluginStateMachineProperties StateProperties;` — `UPROPERTY(transient)` — The common properties that can be accessed by the states of the state machine
- L637 _public member_ `TUniquePtr<FGameFeaturePluginState> AllStates[EGameFeaturePluginState::MAX];` — All state machine state objects
- L640 _public member_ `UE::GameFeatures::FStateMachineExecutor* Executor = nullptr;` — Object responsible for scheduling state machine updates when UE::GameFeatures::bUseNewExecutor is true
- L643 _public member_ `bool bInUpdateStateMachine;` — True when we are currently executing UpdateStateMachine, to avoid reentry
- L646 _public member_ `bool bIsInUnrecoverableError = false;` — True when the state machine can not transition out of the current error state or if requested to would likely fail
- L649 _public member_ `bool bRegisteredAsTransitioningGFPSM;` — True when we are registered as a state machine with in flight transitions

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace GameFeatures` (scope `UE`)
- L20 _externvar_ `extern TAutoConsoleVariable<bool> CVarAllowMissingOnDemandDependencies;` (scope `UE::GameFeatures`)
- L21 _externvar_ `extern bool bUseNewExecutor;` (scope `UE::GameFeatures`)
- L22 _externvar_ `extern bool bLoadBuiltin_DeferExecution;` (scope `UE::GameFeatures`)
- L177 _namespace_ `namespace UE`
- L177 _namespace_ `namespace GameFeatures` (scope `UE`)
- L302 _function_ `inline bool operator<(EGameFeaturePluginState State, const FGameFeaturePluginStateRange& StateRange)`
- L307 _function_ `inline bool operator<(const FGameFeaturePluginStateRange& StateRange, EGameFeaturePluginState State)`
- L312 _function_ `inline bool operator>(EGameFeaturePluginState State, const FGameFeaturePluginStateRange& StateRange)`
- L317 _function_ `inline bool operator>(const FGameFeaturePluginStateRange& StateRange, EGameFeaturePluginState State)`
- L322 _prototype_ `void SerializeForLog(FCbWriter& Writer, FGameFeaturePluginStateRange InRange);`
- L346 _delegate_ `DECLARE_DELEGATE_TwoParams(FGameFeatureStateTransitionComplete, UGameFeaturePluginStateMachine* , const UE::GameFeatures::FResult& );` — Notification that a state transition is complete
- L346 _prototype_ `DECLARE_DELEGATE_TwoParams(FGameFeatureStateTransitionComplete, UGameFeaturePluginStateMachine* , const UE::GameFeatures::FResult& );` — Notification that a state transition is complete
- L349 _delegate_ `DECLARE_DELEGATE_OneParam(FGameFeatureStateTransitionCanceled, UGameFeaturePluginStateMachine* );` — Notification that a state transition is canceled
- L349 _prototype_ `DECLARE_DELEGATE_OneParam(FGameFeatureStateTransitionCanceled, UGameFeaturePluginStateMachine* );` — Notification that a state transition is canceled
- L352 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGameFeaturePluginRequestStateMachineDependencies, const FString& , TArray<UGameFeaturePluginStateMachine*>& );` — A request for other state machine dependencies
- L352 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGameFeaturePluginRequestStateMachineDependencies, const FString& , TArray<UGameFeaturePluginStateMachine*>& );` — A request for other state machine dependencies
- L355 _delegate_ `DECLARE_DELEGATE_OneParam(FGameFeatureStateProgressUpdate, float Progress);` — A request to update progress for the current state
- L355 _prototype_ `DECLARE_DELEGATE_OneParam(FGameFeatureStateProgressUpdate, float Progress);` — A request to update progress for the current state
- L430 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTransitionCanceled, UGameFeaturePluginStateMachine* );` — Callbacks for when the current state transition is cancelled
- L590 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestinationStateReached, UGameFeaturePluginStateMachine* , const UE::GameFeatures::FResult& );`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Private/GameFeatureStateHandleInternal.h` (Private)


#### class `FGameFeatureStateHandleInternal`  
`class FGameFeatureStateHandleInternal`  
_L13-50_
- desc: TODO move this actually in the private area. For now its in a public header, but in the Engine it will be hidden
- L16 _public prototype_ `FGameFeatureStateHandleInternal(const FString& Owner, EGameFeatureStateHandleOptions Options);`
- L17 _public prototype_ `FGameFeatureStateHandleInternal(FGameFeatureStateHandleInternal&&) = default;`
- L18 _public prototype_ `FGameFeatureStateHandleInternal& operator=(FGameFeatureStateHandleInternal&& OtherStateHandle) = default;`
- L20 _public prototype_ `~FGameFeatureStateHandleInternal();`
- L23 _public prototype_ `FGameFeatureStateHandleInternal(const FGameFeatureStateHandleInternal& OtherStateHandle) = delete;` — no copying allowed
- L24 _public prototype_ `FGameFeatureStateHandleInternal& operator=(const FGameFeatureStateHandleInternal& OtherStateHandle) = delete;`
- L26 _public prototype_ `void TakeOwnership(FGameFeatureStateHandleInternal& StateHandle);`
- L28 _public prototype_ `void AddOrUpdateOwnershipIfHighestDestState(const FString& PluginName, EGameFeaturePluginState DestPluginState);`
- L29 _public prototype_ `bool FindPluginRequiredState(const FString& PluginName, EGameFeaturePluginState& OutPluginState) const;`
- L31 _public prototype_ `const TArray<FString> GetPlugins() const;`
- L32 _public prototype_ `int GetPluginCount() const;`
- L34 _public prototype_ `void Empty();`
- L35 _public prototype_ `bool IsEmpty() const;`
- L37 _public prototype_ `void Remove(const FString& PluginName);`
- L39 _public prototype_ `FString ToString() const;`
- L40 _public prototype_ `FString GetOwner() const;`
- L41 _public prototype_ `EGameFeatureStateHandleOptions GetOptions() const;`
- L45 _private member_ `TMap<FString, EGameFeaturePluginState> StateHandleData;` — Mapping of PluginName -> ref counted MinRequireState
- L48 _private member_ `FString Owner;` — Copy of the public options and string owners so we can get this info with out needing a copy of the public state handle
- L49 _private member_ `EGameFeatureStateHandleOptions Options;`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Private/GameFeatureStateHandleReferenceControllerInternal.h` (Private)


#### struct `FGameFeatureStateRefCount`  
`struct FGameFeatureStateRefCount`  
_L17-35_
- desc: Each Ref will be in a map (GFPUrl) -> RefCount Each Ref will store the StateHandle that owns a Ref to this GFPUrl and desired min PluginState, and will store the HighestPluginState to make it easier to grab the highest PluginState this GFP should be at
- L20 _public prototype_ `void AddRef(const FGuid& StateHandleId, EGameFeaturePluginState DestPluginState);`
- L22 _public prototype_ `[[nodiscard]] bool RemoveRefAndRequiresDowngrading(const FGuid& StateHandleId);`
- L24 _public prototype_ `bool GetHighestRefCountDestPluginState(EGameFeaturePluginState& OutDestPluginState) const;`
- L25 _public prototype_ `bool IsEmpty() const;`
- L27 _public prototype_ `const TMap<FGuid, EGameFeaturePluginState>& GetOwnerToDestMap() const;`
- L33 _private member_ `TMap<FGuid, EGameFeaturePluginState> OwnerToDestState;` — Keep track of the StateHandleID + its highest Destination State Adding a new Owner + Dest -> update highest DestState tracked Removing an Owner -> search owners for next highest Destination State
- L34 _private member_ `EGameFeaturePluginState HighestDestPluginState = EGameFeaturePluginState::Uninitialized;`

#### struct `FGameFeatureStateHandleReferenceControllerInternal`  
`struct FGameFeatureStateHandleReferenceControllerInternal`  
_L41-51_
- desc: The private data of the Reference Controller Map of GFPURL -> RefCount Map of Public StateHandle (GUID) -> Private Internal StateHandle
- L43 _public prototype_ `void ListGameFeatureStateHandles(const TArray<FString>& Args, UWorld* World, FOutputDevice& Ar);`
- L46 _public member_ `TMap<FString, FGameFeatureStateRefCount> GFPReferenceCount;` — Mapping of GFP Name to RefCount
- L49 _public member_ `FCriticalSection StateHandlesLock;` — Mapping of public StateHandles (GUIDs) to internal storage of our GFPs + PluginState
- L50 _public member_ `TMap<FGuid, FGameFeatureStateHandleInternal> StateHandles;`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction.h` (Public)


#### class `UGameFeatureAction`  
`class UGameFeatureAction : public UObject`  
_L16-56_
- reflection: `UCLASS(MinimalAPI, DefaultToInstanced, EditInlineNew, Abstract)`
- inherits: `UObject`
- desc: Represents an action to be taken when a game feature is activated
- L21 _public prototype_ `virtual UGameFeatureData* GetGameFeatureData() const;`
- L24 _public function_ `virtual void OnGameFeatureRegistering()` — Called when the object owning the action is registered for possible activation, this is called even if a feature never activates
- L27 _public function_ `virtual void OnGameFeatureUnregistering()` — Called to unregister an action, it will not be activated again without being registered again
- L30 _public function_ `virtual void OnGameFeatureLoading()` — Called to indicate that a feature is being loaded for activation in the near future
- L33 _public function_ `virtual void OnGameFeatureUnloading()` — Called to indicate that a feature is being unloaded
- L36 _public prototype_ `virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context);` — Called when the feature is actually applied
- L39 _public function_ `virtual void OnGameFeatureActivating()` — Older-style activation function with no context, called by base class if context version is not overridden
- L42 _public function_ `virtual void OnGameFeatureActivated()` — Called when the feature is fully active
- L45 _public function_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)` — Called when game feature is deactivated, it may be activated again in the near future
- L48 _public prototype_ `bool IsGameFeaturePluginRegistered(bool bCheckForRegistering = false) const;` — Returns whether the action game feature plugin is registered or not.
- L51 _public prototype_ `bool IsGameFeaturePluginActive(bool bCheckForActivating = false) const;` — Returns whether the action game feature plugin is active or not.
- L54 _public function_ `virtual void AddAdditionalAssetBundleData(FAssetBundleData& AssetBundleData)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAMEFEATURES_API`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AddActorFactory.h` (Public)


#### class `UGameFeatureAction_AddActorFactory`  
`class UGameFeatureAction_AddActorFactory final : public UGameFeatureAction`  
_L19-51_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Add Actor Factory"), Config=Engine)`
- inherits: `UGameFeatureAction`
- desc: GameFeatureAction to add an actor factory when this plugin registers. Useful for factories that might load BP classes within a plugin which might not have been discovered yet.
- L25 _public prototype_ `virtual void OnGameFeatureRegistering() override;`
- L26 _public prototype_ `virtual void OnGameFeatureUnregistering() override;`
- L32 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;` — UObject overrides
- L33 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L44 _protected member_ `TSoftClassPtr<UObject> ActorFactory;` — `UPROPERTY(EditAnywhere, Category = "Actor Factory")` — The actor factory class to add once this plugin registers Actor factories should be setup with bShouldAutoRegister so that they do not register during engine boot.
- L46 _protected member_ `TWeakObjectPtr<UObject> AddedFactory;`
- L49 _protected prototype_ `void AddActorFactory();`
- L50 _protected prototype_ `void RemoveActorFactory();`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AddCheats.h` (Public)


#### class `UGameFeatureAction_AddCheats`  
`class UGameFeatureAction_AddCheats final : public UGameFeatureAction`  
_L20-55_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Add Cheats"))`
- inherits: `UGameFeatureAction`
- desc: Adds cheat manager extensions to the cheat manager for each player
- L26 _public prototype_ `virtual void OnGameFeatureActivating() override;`
- L27 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L32 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L37 _private prototype_ `void OnCheatManagerCreated(UCheatManager* CheatManager);`
- L38 _private prototype_ `void SpawnCheatManagerExtension(UCheatManager* CheatManager, const TSubclassOf<UCheatManagerExtension>& CheatManagerClass);`
- L43 _public member_ `TArray<TSoftClassPtr<UCheatManagerExtension>> CheatManagers;` — `UPROPERTY(EditAnywhere, Category="Cheats")` — Cheat managers to setup for the game feature plugin
- L46 _public member_ `bool bLoadCheatManagersAsync;` — `UPROPERTY(EditAnywhere, Category="Cheats")`
- L49 _private member_ `FDelegateHandle CheatManagerRegistrationHandle;`
- L52 _private member_ `TArray<TWeakObjectPtr<UCheatManagerExtension>> SpawnedCheatManagers;` — `UPROPERTY(Transient)`
- L54 _private member_ `bool bIsActive = false;`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AddChunkOverride.h` (Public)


#### class `UGameFeatureAction_AddChunkOverride`  
`class UGameFeatureAction_AddChunkOverride final : public UGameFeatureAction`  
_L19-100_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Add Chunk Override"), Config=Engine)`
- inherits: `UGameFeatureAction`
- desc: Used to cook assets from a GFP into a specified chunkId. This can be useful when individually cooking GFPs for iteration or splitting up a packaged game into smaller downloadable chunks.
- L25 _public prototype_ `virtual void OnGameFeatureRegistering() override;`
- L26 _public prototype_ `virtual void OnGameFeatureUnregistering() override;`
- L29 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldAddChunkOverride, const UGameFeatureData*);`
- L35 _public member_ `static FShouldAddChunkOverride ShouldAddChunkOverride;` — Optionally bound delegate to determine when to add the chunk override. When bound this will be checked before attempting to add the chunk override. Bound delegates should return true if the GameFeatureData should have a chunk id overriden; otherwise, false.
- L45 _public prototype_ `static TOptional<int32> GetChunkForPackage(const FString& PackageName);` — Given the package name will check if this is a package from a GFP that we want to assign a specific chunk to. returns the override chunk for this package if one is set. Should be used in combination with overriding UAssetManager::GetPackageChunkIds so that you are able to reassign a startup package. This can be necessary to reassign startup packages such as the GameFeatureData asset.
- L47 _public prototype_ `static TArray<FString> GetPluginNameFromChunkID(int32 ChunkID);`
- L50 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;` — UObject overrides
- L51 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L54 _public function_ `bool ShouldOverrideChunk() const`
- L56 _public function_ `int32 GetChunkID() const`
- L58 _public prototype_ `static int32 GetLowestAllowedChunkId();`
- L67 _private member_ `bool bShouldOverrideChunk = false;` — `UPROPERTY(EditAnywhere, Category = "Asset Management")` — Should this GFP have their packages cooked into the specified ChunkId
- L73 _private member_ `int32 ChunkId = -1;` — `UPROPERTY(EditAnywhere, Category = "Asset Management", meta=(EditCondition="bShouldOverrideChunk"))` — What ChunkId to place the packages inside for this particular GFP.
- L80 _private member_ `int32 ParentChunk = 10;` — `UPROPERTY(EditAnywhere, Category = "Asset Management", meta=(EditCondition="bShouldOverrideChunk"))` — What Chunk we are parented to. This is used by the ChunkDependencyInfo for when mutiple chunk overrides might conflict requiring assets to be pulled into a lower chunk
- L87 _private member_ `int32 LowestAllowedChunkIndexForAutoGeneration = INDEX_NONE;` — `UPROPERTY(config)` — Config defined value for what is the smallest chunk index the autogeneration code can generate. If autogeneration produces a chunk index lower than this value users will need to manually define the chunk index this GFP will cook into.
- L90 _private prototype_ `void AddChunkIdOverride();`
- L91 _private prototype_ `void RemoveChunkIdOverride();`
- L98 _private prototype_ `int32 GenerateUniqueChunkId() const;` — Attempts to generate a unique int32 id for the given plugin based on the name of the plugin. returns -1 if a unique name couldn't be generated with consideration to other plugins that have an override id.

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FShouldAddChunkOverride, const UGameFeatureData*);`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AddComponents.h` (Public)


#### struct `FGameFeatureComponentEntry`  
`struct FGameFeatureComponentEntry`  
_L27-52_
- reflection: `USTRUCT()`
- desc: Description of a component to add to a type of actor when this game feature is enabled (the actor class must be game feature aware, it does not happen magically) @TODO: Write more documentation here about how to make an actor game feature / modular gameplay aware
- L31 _public prototype_ `FGameFeatureComponentEntry();`
- L35 _public member_ `TSoftClassPtr<AActor> ActorClass;` — `UPROPERTY(EditAnywhere, Category="Components", meta=(AllowAbstract="True"))` — The base actor class to add a component to
- L39 _public member_ `TSoftClassPtr<UActorComponent> ComponentClass;` — `UPROPERTY(EditAnywhere, Category="Components")` — The component class to add to the specified type of actor
- L43 _public member_ `uint8 bClientComponent:1;` — `UPROPERTY(EditAnywhere, Category="Components")` — Should this component be added for clients
- L47 _public member_ `uint8 bServerComponent:1;` — `UPROPERTY(EditAnywhere, Category="Components")` — Should this component be added on servers
- L51 _public member_ `uint8 AdditionFlags;` — `UPROPERTY(EditAnywhere, Category = "Components", meta = (Bitmask, BitmaskEnum = "/Script/ModularGameplay.EGameFrameworkAddComponentFlags"))` — Observe these rules when adding the component, if any

#### class `UGameFeatureAction_AddComponents`  
`class UGameFeatureAction_AddComponents final : public UGameFeatureAction`  
_L63-125_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Add Components"))`
- inherits: `UGameFeatureAction`
- desc: Adds actor<->component spawn requests to the component manager @see UGameFrameworkComponentManager
- L69 _public prototype_ `virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;`
- L70 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L72 _public prototype_ `virtual void AddAdditionalAssetBundleData(FAssetBundleData& AssetBundleData) override;`
- L78 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L84 _public member_ `TArray<FGameFeatureComponentEntry> ComponentList;` — `UPROPERTY(EditAnywhere, Category="Components", meta=(TitleProperty="{ActorClass} -> {ComponentClass}"))` — List of components to add to gameplay actors when this game feature is enabled
- L109 _private prototype_ `void AddToWorld(const FWorldContext& WorldContext, FContextHandles& Handles);`
- L111 _private prototype_ `void HandleGameInstanceStart(UGameInstance* GameInstance, FGameFeatureStateChangeContext ChangeContext);`
- L113 _private prototype_ `void HandleGameInstanceStart_NewWorldTracking(UGameInstance* GameInstance);`
- L114 _private prototype_ `void HandleGameInstanceWorldChanged(UGameInstance* GameInstance, UWorld* OldWorld, UWorld* NewWorld);`
- L115 _private prototype_ `void AddGameInstanceForActivation(TNotNull<UGameInstance*> GameInstance, FActivationContextData& ActivationContextData);`
- L116 _private prototype_ `void UpdateComponentsOnManager(TNotNull<UWorld*> World, TNotNull<UGameFrameworkComponentManager*> Manager, FGameInstanceData& ComponentData);`
- L117 _private prototype_ `TSharedPtr<FComponentRequestHandle> AddComponentRequest(TNotNull<UWorld*> World, TNotNull<UGameFrameworkComponentManager*> Manager, const FGameFeatureComponentEntry& Entry);`
- L119 _private member_ `TMap<FGameFeatureStateChangeContext, FContextHandles> ContextHandles;`
- L121 _private member_ `FDelegateHandle GameInstanceStartHandle;`
- L122 _private member_ `FDelegateHandle GameInstanceWorldChangedHandle;`
- L123 _private member_ `TMap<FGameFeatureStateChangeContext, FActivationContextData> ActivationContextDataMap;`

#### struct `UGameFeatureAction_AddComponents::FContextHandles`  
`struct FContextHandles`  
_L87-91_
- L89 _public member_ `FDelegateHandle GameInstanceStartHandle;`
- L90 _public member_ `TArray<TSharedPtr<FComponentRequestHandle>> ComponentRequestHandles;`

#### struct `UGameFeatureAction_AddComponents::FGameInstanceData`  
`struct FGameInstanceData`  
_L93-101_
- L96 _public member_ `ENetMode WorldNetMode = ENetMode::NM_MAX;` — NetMode of the current world, used to determine if client/server components should be requested
- L100 _public member_ `TArray<TSharedPtr<FComponentRequestHandle>> ComponentRequestHandles;` — May contain null entries, this array is parallel to ComponentList so that client/server components can be added or removed in-place when the world changes

#### struct `UGameFeatureAction_AddComponents::FActivationContextData`  
`struct FActivationContextData`  
_L103-107_
- L106 _public member_ `TMap<FObjectKey, FGameInstanceData> GameInstanceDataMap;` — Map of GameInstance names to component data for it's world

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEFEATURES_API`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AddWPContent.h` (Public)


#### class `UGameFeatureAction_AddWPContent`  
`class UGameFeatureAction_AddWPContent : public UGameFeatureAction`  
_L20-39_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Add World Partition Content (Content Bundle)"))`
- inherits: `UGameFeatureAction`
- L26 _public prototype_ `virtual void OnGameFeatureRegistering() override;`
- L27 _public prototype_ `virtual void OnGameFeatureUnregistering() override;`
- L28 _public prototype_ `virtual void OnGameFeatureActivating() override;`
- L29 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L32 _public function_ `const UContentBundleDescriptor* GetContentBundleDescriptor() const`
- L36 _private member_ `TObjectPtr<UContentBundleDescriptor> ContentBundleDescriptor;` — `UPROPERTY(VisibleAnywhere, Category = ContentBundle)`
- L38 _private member_ `TSharedPtr<FContentBundleClient> ContentBundleClient;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEFEATURES_API`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AddWorldPartitionContent.h` (Public)


#### class `UGameFeatureAction_AddWorldPartitionContent`  
`class UGameFeatureAction_AddWorldPartitionContent : public UGameFeatureAction`  
_L16-67_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Add World Partition Content"))`
- inherits: `UGameFeatureAction`
- L22 _public prototype_ `virtual void OnGameFeatureRegistering() override;`
- L23 _public prototype_ `virtual void OnGameFeatureUnregistering() override;`
- L24 _public prototype_ `virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;`
- L25 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L30 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L31 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public prototype_ `virtual void PreEditUndo() override;`
- L33 _public prototype_ `virtual void PostEditUndo() override;`
- L36 _public function_ `const TObjectPtr<const UExternalDataLayerAsset>& GetExternalDataLayerAsset() const`
- L42 _protected member_ `TObjectPtr<const UExternalDataLayerAsset> ExternalDataLayerAsset;` — `UPROPERTY(EditAnywhere, Category = DataLayer)` — External Data Layer used by this action.
- L46 _protected member_ `FName RequiredCVar;` — `UPROPERTY(EditAnywhere, Category = DataLayer)` — Optional console variable name which (when specified) must return true for the external data layer to be added. If not specified, this condition is skipped.
- L50 _private prototype_ `bool ShouldActivateExternalDataLayer() const;` — Returns whether the external data layer should be activated based on RequiredCVarName. Returns true when no CVar is configured.
- L53 _private prototype_ `void OnExternalDataLayerAssetChanged(const UExternalDataLayerAsset* OldAsset, const UExternalDataLayerAsset* NewAsset);`
- L57 _private member_ `TWeakObjectPtr<const UExternalDataLayerAsset> PreEditChangeExternalDataLayerAsset;` — Used to detect changes on the Data Layer Asset in the action.
- L58 _private member_ `TWeakObjectPtr<const UExternalDataLayerAsset> PreEditUndoExternalDataLayerAsset;`
- L63 _private member_ `FGuid ConvertedContentBundleGuid;` — `UPROPERTY()` — Only used when converting from UGameFeatureAction_AddWPContent

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEFEATURES_API`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AudioActionBase.h` (Public)


#### class `UGameFeatureAction_AudioActionBase`  
`class UGameFeatureAction_AudioActionBase : public UGameFeatureAction`  
_L17-37_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UGameFeatureAction`
- desc: Base class for GameFeatureActions that affect the audio engine
- L23 _public prototype_ `virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;`
- L24 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L29 _protected member_ `FDelegateHandle DeviceCreatedHandle;` — Handle to delegate callbacks
- L30 _protected member_ `FDelegateHandle DeviceDestroyedHandle;`
- L32 _protected prototype_ `void OnDeviceCreated(Audio::FDeviceId InDeviceId);`
- L33 _protected prototype_ `void OnDeviceDestroyed(Audio::FDeviceId InDeviceId);`
- L35 _protected function_ `virtual void AddToDevice(const FAudioDeviceHandle& AudioDeviceHandle)`
- L36 _protected function_ `virtual void RemoveFromDevice(const FAudioDeviceHandle& AudioDeviceHandle)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEFEATURES_API`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_DataRegistry.h` (Public)


#### class `UGameFeatureAction_DataRegistry`  
`class UGameFeatureAction_DataRegistry : public UGameFeatureAction`  
_L12-47_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Add Data Registry"))`
- inherits: `UGameFeatureAction`
- desc: Specifies a list of Data Registries to load and initialize with this feature
- L17 _public prototype_ `virtual void OnGameFeatureRegistering() override;`
- L18 _public prototype_ `virtual void OnGameFeatureUnregistering() override;`
- L19 _public prototype_ `virtual void OnGameFeatureActivating() override;`
- L20 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L23 _public prototype_ `virtual bool ShouldPreloadAtRegistration();` — If true, we should load the registry at registration time instead of activation time
- L26 _public prototype_ `virtual void AddAdditionalAssetBundleData(FAssetBundleData& AssetBundleData) override;`
- L31 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L38 _private member_ `TArray<TSoftObjectPtr<UDataRegistry> > RegistriesToAdd;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — List of registry assets to load and initialize
- L42 _private member_ `bool bPreloadInEditor;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — If true, this will preload the registries when the feature is registered in the editor to support the editor pickers
- L46 _private member_ `bool bPreloadInCommandlets;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — If true, this will preload the registries when the feature is registered whilst a commandlet is running

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_DataRegistrySource.h` (Public)


#### struct `FDataRegistrySourceToAdd`  
`struct FDataRegistrySourceToAdd`  
_L13-46_
- reflection: `USTRUCT()`
- desc: Defines which source assets to add and conditions for adding
- L17 _public function_ `FDataRegistrySourceToAdd() : AssetPriority(0) , bClientSource(false) , bServerSource(false)`
- L25 _public member_ `FName RegistryToAddTo;` — `UPROPERTY(EditAnywhere, Category="Registry Data")` — Name of the registry to add to
- L29 _public member_ `int32 AssetPriority;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — Priority to use when adding to the registry.  Higher priorities are searched first
- L33 _public member_ `uint8 bClientSource : 1;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — Should this component be added for clients
- L37 _public member_ `uint8 bServerSource : 1;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — Should this component be added on servers
- L41 _public member_ `TSoftObjectPtr<UDataTable> DataTableToAdd;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — Link to the data table to add to the registry
- L45 _public member_ `TSoftObjectPtr<UCurveTable> CurveTableToAdd;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — Link to the curve table to add to the registry

#### class `UGameFeatureAction_DataRegistrySource`  
`class UGameFeatureAction_DataRegistrySource : public UGameFeatureAction`  
_L50-92_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Add Data Registry Source"))`
- inherits: `UGameFeatureAction`
- desc: Specifies a list of source assets to add to Data Registries when this feature is activated
- L55 _public prototype_ `virtual void OnGameFeatureRegistering() override;`
- L56 _public prototype_ `virtual void OnGameFeatureUnregistering() override;`
- L57 _public prototype_ `virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;`
- L58 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;`
- L61 _public prototype_ `virtual bool ShouldPreloadAtRegistration();` — If true, we should load the sources at registration time instead of activation time
- L64 _public prototype_ `virtual void AddAdditionalAssetBundleData(FAssetBundleData& AssetBundleData) override;`
- L69 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L75 _public prototype_ `void AddSource(const FDataRegistrySourceToAdd& NewSource);` — Used by an editor tool to programmatically register a new source
- L79 _protected prototype_ `void RegisterRuntimeSources();`
- L81 _protected prototype_ `void UnregisterSources();`
- L87 _private member_ `TArray<FDataRegistrySourceToAdd> SourcesToAdd;` — `UPROPERTY(EditAnywhere, Category = "Registry Data", meta=(TitleProperty="RegistryToAddTo"))` — List of sources to add when this feature is activated
- L91 _private member_ `bool bPreloadInEditor;` — `UPROPERTY(EditAnywhere, Category = "Registry Data")` — If true, this will preload the sources when the feature is registered in the editor to support the editor pickers

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureData.h` (Public)


#### class `FGameFeatureDataExternalAssetsPathCache`  
`class FGameFeatureDataExternalAssetsPathCache : public IExternalAssetPathsProvider`  
_L22-38_
- inherits: `IExternalAssetPathsProvider`
- L24 _private member_ `TMultiMap<FName, FName> PerLevelAssetDirectories;`
- L25 _private member_ `TMap<FName, FString> GameFeatureDataAssetsToMountPoint;`
- L26 _private member_ `TSet<FName> AllLevels;`
- L27 _private member_ `bool bCacheIsUpToDate = false;`
- L28 _private member_ `FDelegateHandle OnPathAddedDelegateHandle;`
- L32 _public prototype_ `FGameFeatureDataExternalAssetsPathCache();`
- L33 _public prototype_ `virtual ~FGameFeatureDataExternalAssetsPathCache();`
- L35 _public prototype_ `void OnPathsAdded(TConstArrayView<FStringView>);`
- L36 _public prototype_ `void UpdateCache(const FUpdateCacheContext& Context) override;`
- L37 _public prototype_ `TArray<FName> GetPathsForPackage(FName LevelPath) override;`

#### class `UGameFeatureData`  
`class UGameFeatureData : public UPrimaryDataAsset`  
_L43-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPrimaryDataAsset`
- desc: Data related to a game feature, a collection of code and content that adds a separable discrete feature to the game
- L49 _public function_ `virtual const TArray<FPrimaryAssetTypeInfo>& GetPrimaryAssetTypesToScan() const` — Method to get where the primary assets should scanned from in the plugin hierarchy
- L52 _public function_ `virtual TArray<FPrimaryAssetTypeInfo>& GetPrimaryAssetTypesToScan()`
- L53 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L54 _public prototype_ `static void GetDependencyDirectoriesFromAssetData(const FAssetData& AssetData, TArray<FString>& OutDependencyDirectories);`
- L58 _public prototype_ `static void InitializeBasePluginIniFile(const FString& PluginInstalledFilename);` — Method to process the base ini file for the plugin during loading
- L61 _public prototype_ `static void InitializeHierarchicalPluginIniFiles(const FString& PluginInstalledFilename);` — Method to process ini files for the plugin during activation
- L62 _public prototype_ `static void InitializeHierarchicalPluginIniFiles(const TArrayView<FString>& PluginInstalledFilenames);`
- L65 _public prototype_ `static void GetPluginName(const UGameFeatureData* GFD, FString& PluginName);` — `UFUNCTION(BlueprintCallable, Category = "GameFeature")`
- L67 _public prototype_ `void GetPluginName(FString& PluginName) const;`
- L70 _public prototype_ `bool IsGameFeaturePluginRegistered(bool bCheckForRegistering = false) const;` — Returns whether the game feature plugin is registered or not.
- L73 _public prototype_ `bool IsGameFeaturePluginActive(bool bCheckForActivating = false) const;` — Returns whether the game feature plugin is active or not.
- L80 _public prototype_ `static FString GetInstallBundleName(FStringView PluginName, bool bEvenIfDoesntExist = false);` — Returns the install bundle name if one exists for this plugin. @param - PluginName - the name of the GameFeaturePlugin we want to get a bundle for. Should be the same name as the .uplugin file @param - bEvenIfDoesntExist - when true will return the name of bundle we are looking for without checking if it exists or not.
- L87 _public prototype_ `static FString GetOptionalInstallBundleName(FStringView PluginName, bool bEvenIfDoesntExist = false);` — Returns the optional install bundle name if one exists for this plugin. @param - PluginName - the name of the GameFeaturePlugin we want to get a bundle for. Should be the same name as the .uplugin file @param - bEvenIfDoesntExist - when true will return the name of bundle we are looking for without checking if it exists or not.
- L92 _public prototype_ `virtual void UpdateAssetBundleData() override;`
- L98 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L102 _public function_ `const TArray<UGameFeatureAction*>& GetActions() const`
- L105 _public function_ `TArray<TObjectPtr<UGameFeatureAction>>& GetMutableActionsInEditor()`
- L110 _private prototype_ `static void ReloadConfigs(FConfigFile& PluginConfig);` — Internal helper function to reload config data on objects as a result of a plugin INI being loaded
- L115 _protected prototype_ `virtual TArray<UClass*> GetDisallowedActions() const;` — `UFUNCTION()`
- L120 _protected member_ `TArray<TObjectPtr<UGameFeatureAction>> Actions;` — `UPROPERTY(EditDefaultsOnly, Instanced, Category="Game Feature | Actions", meta = (GetDisallowedClasses = "GetDisallowedActions"))` — List of actions to perform as this game feature is loaded/activated/deactivated/unloaded
- L124 _protected member_ `TArray<FPrimaryAssetTypeInfo> PrimaryAssetTypesToScan;` — `UPROPERTY(EditAnywhere, Category="Game Feature | Asset Manager", meta=(TitleProperty="PrimaryAssetType"))` — List of asset types to scan at startup

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEFEATURES_API`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureOptionalContentInstaller.h` (Public)


#### class `UGameFeatureOptionalContentInstaller`  
`class UGameFeatureOptionalContentInstaller : public UObject, public IGameFeatureStateChangeObserver`  
_L24-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGameFeatureStateChangeObserver`
- desc: Utilty class to install GFP optional paks (usually containing optional mips) in sync with GFP content installs. NOTE: This only currently supports LRU cached install bundles. It would need UI callbacks and additional support for free space checks and progress tracking to fully support non-LRU GFPs.
- L29 _public member_ `static TMulticastDelegate<void(const FString& PluginName, const UE::GameFeatures::FResult&)> OnOptionalContentInstalled;`
- L30 _public member_ `static TMulticastDelegate<void()> OnOptionalContentInstallStarted;`
- L31 _public member_ `static TMulticastDelegate<void(const bool bInstallSuccessful)> OnOptionalContentInstallFinished;`
- L34 _public prototype_ `virtual void BeginDestroy() override;`
- L36 _public prototype_ `void Init( TUniqueFunction<TArray<FName>(FString)> GetOptionalBundlePredicate, TUniqueFunction<TArray<FName>(FString)> GetOptionalKeepBundlePredicate = [](auto) { return TArray<FName>{}; });`
- L38 _public function_ `TUniqueFunction<TArray<FName>(FString)> GetOptionalBundlePredicate, TUniqueFunction<TArray<FName>(FString)> GetOptionalKeepBundlePredicate = [](auto)`
- L40 _public prototype_ `void Enable(bool bEnable);`
- L42 _public prototype_ `void UninstallContent();`
- L44 _public prototype_ `void EnableCellularDownloading(bool bEnable);`
- L46 _public prototype_ `bool HasOngoingInstalls() const;`
- L52 _public prototype_ `float GetAllInstallsProgress();` — Returns the total progress (between 0 and 1) of all the optional bundles currently being installed. Returns 0 while the progress tracker is starting which happens the first time it is called while bundles are being installed.
- L55 _private prototype_ `bool UpdateContent(const FString& PluginName, bool bIsPredownload);`
- L57 _private prototype_ `void OnContentInstalled(FInstallBundleRequestResultInfo InResult, FString PluginName);`
- L59 _private prototype_ `void ReleaseContent(const FString& PluginName, EInstallBundleReleaseRequestFlags Flags = EInstallBundleReleaseRequestFlags::None);`
- L61 _private prototype_ `void OnEnabled();`
- L62 _private prototype_ `void OnDisabled();`
- L64 _private prototype_ `bool IsEnabled() const;`
- L66 _private prototype_ `void OnCVarsChanged();`
- L68 _private prototype_ `void StartTotalProgressTracker();`
- L71 _private prototype_ `virtual void OnGameFeaturePredownloading(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier) override;` — IGameFeatureStateChangeObserver Interface
- L72 _private prototype_ `virtual void OnGameFeatureDownloading(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier) override;`
- L73 _private prototype_ `virtual void OnGameFeatureRegistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL) override;`
- L74 _private prototype_ `virtual void OnGameFeatureReleasing(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier) override;`
- L85 _private member_ `TUniqueFunction<TArray<FName>(FString)> GetOptionalBundlePredicate;`
- L86 _private member_ `TUniqueFunction<TArray<FName>(FString)> GetOptionalKeepBundlePredicate;`
- L87 _private member_ `TSharedPtr<IInstallBundleManager> BundleManager;`
- L88 _private member_ `TSet<FString> RelevantGFPs;`
- L89 _private member_ `TMap<FString, FGFPInstall> ActiveGFPInstalls;`
- L91 _private member_ `TMap<FName, TSet<FName>> BundleToPlugins;` — Map of bundle to the plugins that requested them. Used for knowing when we can release an optional bundle.
- L92 _private member_ `TOptional<FInstallBundleCombinedProgressTracker> TotalProgressTracker;`
- L93 _private member_ `static const FName GFOContentRequestName;`
- L96 _private member_ `FConsoleVariableSinkHandle CVarSinkHandle;` — Delegate handle for a console variable sink
- L98 _private member_ `bool bEnabled = false;`
- L99 _private member_ `bool bEnabledCVar = false;`
- L100 _private member_ `bool bAllowCellDownload = false;`

#### struct `UGameFeatureOptionalContentInstaller::FGFPInstall`  
`struct FGFPInstall`  
_L77-82_
- L79 _public member_ `FDelegateHandle CallbackHandle;`
- L80 _public member_ `TArray<FName> BundlesEnqueued;`
- L81 _public member_ `bool bIsPredownload = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GameFeatures` (scope `UE`)

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeaturePluginOperationResult.h` (Public)


#### struct `UE::GameFeatures::FResult`  
`struct FResult`  
_L20-62_
- desc: Struct wrapper on a combined TValueOrError ErrorCode and FText OptionalErrorText that can provide an FString error code and if set more detailed FText OptionalErrorText information for the results of a GameFeaturesPlugin operation.
- L23 _public member_ `FErrorCodeType ErrorCode;` — Error Code representing the error that occurred
- L26 _public member_ `FText OptionalErrorText;` — Optional Localized error description to bubble up to the user if one was generated
- L29 _public function_ `bool HasValue() const` — Quick functions that just pass through to the ErrorCode
- L30 _public function_ `bool HasError() const`
- L31 _public function_ `FString GetError() const`
- L32 _public function_ `FString StealError()`
- L34 _public prototype_ `FResult(FErrorCodeType ErrorCodeIn, FText ErrorTextIn);`
- L38 _public prototype_ `explicit FResult(FErrorCodeType ErrorCodeIn);` — Explicit constructor for times we want to create an FResult directly from an FErrorCodeType and not through MakeValue or MakeError. Explicit to avoid any confusion with the following templated constructors.
- L43 _public function_ `template <typename... ArgTypes> FResult(TValueOrError_ValueProxy<ArgTypes...>&& ValueProxyIn) : ErrorCode(MoveTemp(ValueProxyIn)) , OptionalErrorText()` — Template Conversion Constructor to allow us to initialize from TValueOrError MakeValue This is needed because of how TValueOrError implements MakeValue through the same templated approach with TValueOrError_ValueProxy.
- L52 _public function_ `template <typename... ArgTypes> FResult(TValueOrError_ErrorProxy<ArgTypes...>&& ErrorProxyIn) : ErrorCode(MoveTemp(ErrorProxyIn)) , OptionalErrorText()` — Template Conversion Constructor to allow us to initialize from TValueOrError MakeError This is needed because of how TValueOrError implements MakeError through the same templated approach with TValueOrError_ErrorProxy.
- L61 _private prototype_ `FResult() = delete;` — No default constructor as we want to force you to always specify at the minimum if the FResult is an error or not through a supplied FErrorCodeType

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEFEATURES_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GameFeatures` (scope `UE`)
- L16 _typedef_ `using FErrorCodeType = TValueOrError<void, FString>;` (scope `UE::GameFeatures`) — Type used to determine if our FResult is actually an error or success (and hold the error code)
- L64 _prototype_ `FString ToString(const FResult& Result);` (scope `UE::GameFeatures`)
- L66 _namespace_ `namespace CommonErrorCodes` (scope `UE::GameFeatures`)
- L68 _prototype_ `const FText& GetErrorTextForBundleResult(EInstallBundleResult ErrorResult);` (scope `UE::GameFeatures::CommonErrorCodes`)
- L69 _prototype_ `const FText& GetErrorTextForReleaseResult(EInstallBundleReleaseResult ErrorResult);` (scope `UE::GameFeatures::CommonErrorCodes`)
- L71 _prototype_ `const FText& GetGenericFatalError();` (scope `UE::GameFeatures::CommonErrorCodes`)
- L72 _prototype_ `const FText& GetGenericConnectionError();` (scope `UE::GameFeatures::CommonErrorCodes`)
- L73 _prototype_ `const FText& GetGenericMountError();` (scope `UE::GameFeatures::CommonErrorCodes`)
- L74 _prototype_ `const FText& GetGenericReleaseResult();` (scope `UE::GameFeatures::CommonErrorCodes`)

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureStateChangeObserver.h` (Public)


#### class `UGameFeatureStateChangeObserver`  
`class UGameFeatureStateChangeObserver : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IGameFeatureStateChangeObserver`  
`class IGameFeatureStateChangeObserver`  
_L31-90_
- desc: This class is meant to be overridden in your game to handle game-specific reactions to game feature plugins being mounted or unmounted Generally you should prefer to use UGameFeatureAction instances on your game feature data asset instead of this, especially if any data is involved If you do use these, create them in your UGameFeaturesProjectPolicies subclass and register them via AddObserver / RemoveObserver on UGameFeaturesSubsystem
- L38 _public function_ `virtual void OnGameFeatureCheckingStatus(const FString& PluginURL)` — Invoked when going from the UnknownStatus state to the CheckingStatus state
- L41 _public function_ `virtual void OnGameFeatureTerminating(const FString& PluginURL)` — Invoked prior to terminating a game feature plugin
- L44 _public function_ `virtual void OnGameFeaturePredownloading(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier)` — Invoked when content begins installing via predownload
- L47 _public function_ `virtual void OnGameFeaturePostPredownloading(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier)` — Invoked when pre-downloading content has finished.
- L50 _public function_ `virtual void OnGameFeatureDownloading(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier)` — Invoked when content begins installing
- L53 _public function_ `virtual void OnGameFeatureReleasing(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier)` — Invoked when content is released (the point it at which it is safe to remove it)
- L56 _public function_ `virtual void OnGameFeaturePreMounting(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier, FGameFeaturePreMountingContext& Context)` — Invoked prior to mounting a plugin (but after its install bundles become available, if any)
- L59 _public function_ `virtual void OnGameFeaturePostMounting(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier, FGameFeaturePostMountingContext& Context)` — Invoked at the end of the plugin mounting phase (whether it was successfully mounted or not)
- L62 _public function_ `virtual void OnGameFeatureRegistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL)` — Invoked after a game feature plugin has been registered
- L65 _public function_ `virtual void OnGameFeatureUnregistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL)` — Invoked prior to unregistering a game feature plugin
- L68 _public function_ `virtual void OnGameFeatureLoading(const UGameFeatureData* GameFeatureData, const FString& PluginURL)` — Invoked in the early stages of the game feature plugin loading phase
- L71 _public function_ `virtual void OnGameFeatureUnloading(const UGameFeatureData* GameFeatureData, const FString& PluginURL)` — Invoked after a game feature plugin is unloaded
- L74 _public function_ `virtual void OnGameFeatureActivating(const UGameFeatureData* GameFeatureData, const FString& PluginURL)` — Invoked prior to activating a game feature plugin
- L77 _public function_ `virtual void OnGameFeatureActivated(const UGameFeatureData* GameFeatureData, const FString& PluginURL)` — Invoked after a game feature plugin is activated
- L80 _public function_ `virtual void OnGameFeatureDeactivating(const UGameFeatureData* GameFeatureData, FGameFeatureDeactivatingContext& Context, const FString& PluginURL)` — Invoked prior to deactivating a game feature plugin
- L85 _public function_ `virtual void OnGameFeaturePauseChange(const FString& PluginURL, const FString& PluginName, FGameFeaturePauseStateChangeContext& Context)` — Called whenever a GameFeature State either pauses or resumes work without transitioning out of that state. EX: Downloading paused due to a users cellular data settings or the user taking a pause action. We may not yet transition to a download error, but want a way to observe this behavior.
- L87 _public function_ `virtual void OnGameFeatureBatchOperationStarted()`
- L89 _public function_ `virtual void OnGameFeatureBatchOperationComplete()`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureStateHandle.h` (Public)


#### enum `EGameFeatureStateHandleOptions`  
`enum class EGameFeatureStateHandleOptions : uint8`  
_L13-18_
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `TrackDependencies = 1 << 0`
- L17 _public enumerator_ `KeepRegistered = 1 << 1`

#### class `FGameFeatureStateHandle`  
`class FGameFeatureStateHandle`  
_L26-62_
- desc: Public class keep track of ownership and reference counts on which plugins + depends through a public GUID Used internally to reference a structure containing this data You must call the InitAndRegister function this to Properly create a version of this so it is registered internally, otherwise it is invalid to use this
- L29 _public prototype_ `FGameFeatureStateHandle() = default;`
- L30 _public prototype_ `explicit FGameFeatureStateHandle(const FString& Owner, EGameFeatureStateHandleOptions Options = EGameFeatureStateHandleOptions::TrackDependencies);`
- L33 _public function_ `void ReleaseAndUnregister(TFunction<void(bool)> ResetCompleteCallback = [](bool){});` — Releases all the ref counts, and if any GFPs need to be downgraded moves them. When done we call the Callback if setup. The Dtor call this
- L33 _public prototype_ `void ReleaseAndUnregister(TFunction<void(bool)> ResetCompleteCallback = [](bool){});` — Releases all the ref counts, and if any GFPs need to be downgraded moves them. When done we call the Callback if setup. The Dtor call this
- L34 _public prototype_ `~FGameFeatureStateHandle();`
- L37 _public prototype_ `FGameFeatureStateHandle(const FGameFeatureStateHandle&) = delete;` — Move only, so delete copy ctor/assign
- L38 _public prototype_ `FGameFeatureStateHandle& operator=(const FGameFeatureStateHandle&) = delete;`
- L40 _public prototype_ `FGameFeatureStateHandle(FGameFeatureStateHandle&&);`
- L41 _public prototype_ `FGameFeatureStateHandle& operator=(FGameFeatureStateHandle&&);`
- L44 _public prototype_ `bool InitAndRegister(const FString& Owner, EGameFeatureStateHandleOptions Options = EGameFeatureStateHandleOptions::TrackDependencies);` — Init the StateHandle with a unique id, owner, options and registers it with the StateHandleRefController, if this StateHandle already has a valid GUID, we return false
- L46 _public prototype_ `FString ToString() const;`
- L47 _public prototype_ `FGuid GetUniqueId() const;`
- L50 _public prototype_ `void TakeOwnership(FGameFeatureStateHandle&& StateHandle);` — Takes over the ref counts of the StateHandle and its dtor is called
- L52 _public prototype_ `bool IsValid() const;`
- L53 _public prototype_ `bool operator==(const FGameFeatureStateHandle& Other) const;`
- L57 _public prototype_ `int32 CompareAndLogGameFeatureDifferences(const FGameFeatureStateHandle& FinalizedStateHandle);` — Compare and log differences between two state handle owned GFPs. Note: only compares plugin sets across handles (not target states)
- L61 _private member_ `FGuid UniqueId;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEFEATURES_API`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureStateHandleReferenceController.h` (Public)


#### class `FGameFeatureStateHandleReferenceController`  
`class FGameFeatureStateHandleReferenceController`  
_L22-72_
- L25 _public prototype_ `static FGameFeatureStateHandleReferenceController& Get();`
- L26 _public prototype_ `static bool IsLifetimeControlEnabled();`
- L28 _public prototype_ `void RegisterNewStateHandle(const FGameFeatureStateHandle& StateHandle, const FString& Owner, EGameFeatureStateHandleOptions Options);`
- L29 _public prototype_ `void UnregisterStateHandle(const FGameFeatureStateHandle& StateHandle);`
- L31 _public prototype_ `void LoadAndActivateGameFeaturePlugin(const FGameFeatureStateHandle& StateHandle, const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, const UGameFeatureStateHandleLoadComplete& CompleteDelegate);`
- L32 _public prototype_ `void LoadAndActivateGameFeaturePlugin(const FGameFeatureStateHandle& StateHandle, const TArray<FString>& PluginURLs, const FGameFeatureProtocolOptions& ProtocolOptions, const UMultipleGameFeatureStateHandleLoadComplete& CompleteDelegate);`
- L34 _public prototype_ `void LoadGameFeaturePlugin(const FGameFeatureStateHandle& StateHandle, const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, const UGameFeatureStateHandleLoadComplete& CompleteDelegate);`
- L35 _public prototype_ `void LoadGameFeaturePlugin(const FGameFeatureStateHandle& StateHandle, const TArray<FString>& PluginURLs, const FGameFeatureProtocolOptions& ProtocolOptions, const UMultipleGameFeatureStateHandleLoadComplete& CompleteDelegate);`
- L37 _public prototype_ `void RegisterGameFeaturePlugin(const FGameFeatureStateHandle& StateHandle, const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, const UGameFeatureStateHandleLoadComplete& CompleteDelegate);`
- L38 _public prototype_ `void RegisterGameFeaturePlugin(const FGameFeatureStateHandle& StateHandle, const TArray<FString>& PluginURLs, const FGameFeatureProtocolOptions& ProtocolOptions, const UMultipleGameFeatureStateHandleLoadComplete& CompleteDelegate);`
- L40 _public prototype_ `void LoadBuiltInGameFeaturePlugins_Amortized(const FGameFeatureStateHandle& StateHandle, const TArray<TSharedRef<IPlugin>>& Plugins, const UGameFeaturesSubsystem::FBuiltInPluginAdditionalFilters_Copyable& AdditionalFilter, int32 AmortizeRateMS, const UMultipleGameFeatureStateHandleLoadComplete& CompleteDelegate);`
- L43 _public function_ `void ResetGameFeatureStateHandle(const FGameFeatureStateHandle& StateHandle, TFunction<void(bool)> OnComplete = [](bool) {});` — Removes all the GFPs references held by this list of handles, and will empty out the StateHandle list
- L43 _public prototype_ `void ResetGameFeatureStateHandle(const FGameFeatureStateHandle& StateHandle, TFunction<void(bool)> OnComplete = [](bool) {});` — Removes all the GFPs references held by this list of handles, and will empty out the StateHandle list
- L46 _public prototype_ `void AddOrUpdateReference(const FGameFeatureStateHandle& StateHandle, const FString& GameFeaturePluginURL, EGameFeaturePluginState PluginState, bool bCollectDepends = true);` — Adds or Updates the GFP URL to the PluginState
- L49 _public prototype_ `bool GetMinimumRequiredStateForGameFeaturePlugin(const FString& GameFeaturePluginURL, EGameFeaturePluginState& OutPluginState);` — From the RefCounts gets the lowest GFP state required by a GFP we are tracking into OutPluginState
- L52 _public prototype_ `void MergeGameFeatureStateHandle(const FGameFeatureStateHandle& From, const FGameFeatureStateHandle& To);` — The From StateHandles internals are appended to the To StateHandle, and the list of GFPs in From are Emptied
- L56 _public prototype_ `int32 CompareAndLogGameFeatureDifferences(const FGameFeatureStateHandle& A, const FGameFeatureStateHandle& B);` — Compare and log differences between two state handle owned GFPs. Note: only compares plugin sets across handles (not target states)
- L60 _private prototype_ `FGameFeatureStateHandleReferenceController();`
- L61 _private prototype_ `FGameFeatureStateHandleReferenceController(FGameFeatureStateHandleReferenceController const&) = delete;`
- L62 _private prototype_ `FGameFeatureStateHandleReferenceController& operator=(FGameFeatureStateHandleReferenceController const&) = delete;`
- L65 _private prototype_ `void AddOrUpdateReference(const FGuid& StateHandleId, const FString& GameFeaturePluginURL, EGameFeaturePluginState PluginState, bool bCollectDepends = true);` — Internal function so we can handle callbacks safely if the StateHandle passed in goes out of scope, we can detect missing guids over corrupted memory
- L67 _private prototype_ `void RemoveReferences(const FGameFeatureStateHandle& StateHandle, const TArray<FString>& PluginsToRemoveRefences, TFunction<void(bool)> OnComplete);`
- L69 _private prototype_ `bool GetDowngradedTargetState(const FString& PluginURL, EGameFeaturePluginState& OutTransitionState) const;`
- L71 _private member_ `TUniquePtr<FGameFeatureStateHandleReferenceControllerInternal> Internal;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace GameFeatures` (scope `UE`)
- L15 _macro_ `#define UE_API GAMEFEATURES_API`
- L18 _typedef_ `using UMultipleGameFeatureStateHandleLoadComplete = TDelegate<void(const TMap<FString, UE::GameFeatures::FResult>& )>;` — TODO these currently are no longer needed but keeping for now incase we find the return handle + refresh idea doesnt work out
- L19 _typedef_ `using UGameFeatureStateHandleLoadComplete = TDelegate<void(const UE::GameFeatures::FResult& )>;`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureTypes.h` (Public)


#### enum `GameFeaturePluginStatePrivate::EGameFeaturePluginState`  
`enum EGameFeaturePluginState : uint8`  
_L61-65_
- L63 _public enumerator_ `GAME_FEATURE_PLUGIN_STATE_LIST(GAME_FEATURE_PLUGIN_STATE_ENUM) MAX`

#### enum `EGameFeaturePluginProtocol`  
`#define GAME_FEATURE_PLUGIN_PROTOCOL_ENUM(inEnum, inString) inEnum, enum class EGameFeaturePluginProtocol : uint8`  
_L85-89_
- L87 _public enumerator_ `GAME_FEATURE_PLUGIN_PROTOCOL_LIST(GAME_FEATURE_PLUGIN_PROTOCOL_ENUM) Count`

#### enum `EGameFeatureURLOptions`  
`enum class EGameFeatureURLOptions : uint8`  
_L100-105_
- L102 _public enumerator_ `None`
- L103 _public enumerator_ `GAME_FEATURE_PLUGIN_URL_OPTIONS_LIST(GAME_FEATURE_PLUGIN_URL_OPTIONS_ENUM) All = None GAME_FEATURE_PLUGIN_URL_OPTIONS_LIST(GAME_FEATURE_PLUGIN_URL_OPTIONS_ALL)`

#### Free symbols / members of external scopes

- L17 _macro_ `#define GAME_FEATURE_PLUGIN_STATE_LIST(XSTATE) \` — GFP States Desitination states must be fully ordered, Transistion and Error states should be in between the Destination states they transition to/from. See the state chart in GameFeaturePluginStateMachine.h for reference.
- L56 _macro_ `#define GAME_FEATURE_PLUGIN_STATE_ENUM(inEnum, inText) inEnum,`
- L59 _namespace_ `namespace GameFeaturePluginStatePrivate`
- L67 _typedef_ `using EGameFeaturePluginState = GameFeaturePluginStatePrivate::EGameFeaturePluginState;`
- L69 _prototype_ `ENUM_RANGE_BY_COUNT(EGameFeaturePluginState, EGameFeaturePluginState::MAX);`
- L71 _prototype_ `void SerializeForLog(FCbWriter& Writer, EGameFeaturePluginState State);`
- L73 _namespace_ `namespace UE`
- L73 _namespace_ `namespace GameFeatures` (scope `UE`)
- L75 _prototype_ `FString ToString(EGameFeaturePluginState InType);` (scope `UE::GameFeatures`)
- L79 _macro_ `#define GAME_FEATURE_PLUGIN_PROTOCOL_LIST(XPROTO) \` — GFP Protocols
- L84 _macro_ `#define GAME_FEATURE_PLUGIN_PROTOCOL_ENUM(inEnum, inString) inEnum,`
- L92 _prototype_ `ENUM_RANGE_BY_COUNT(EGameFeaturePluginProtocol, EGameFeaturePluginProtocol::Count);`
- L95 _macro_ `#define GAME_FEATURE_PLUGIN_URL_OPTIONS_LIST(XOPTION) \` — GFP URL Options
- L98 _macro_ `#define GAME_FEATURE_PLUGIN_URL_OPTIONS_ENUM(inEnum, inVal) inEnum = inVal,`
- L99 _macro_ `#define GAME_FEATURE_PLUGIN_URL_OPTIONS_ALL(inEnum, inVal) | inEnum`
- L109 _prototype_ `ENUM_CLASS_FLAGS(EGameFeatureURLOptions);`
- L111 _prototype_ `const TCHAR* LexToString(EGameFeatureURLOptions);`
- L112 _prototype_ `void LexFromString(EGameFeatureURLOptions& ValueOut, const FStringView& StringIn);`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureTypesFwd.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace GameFeaturePluginStatePrivate`
- L14 _typedef_ `using EGameFeaturePluginState = GameFeaturePluginStatePrivate::EGameFeaturePluginState;`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace GameFeatures` (scope `UE`)
- L18 _prototype_ `FString ToString(EGameFeaturePluginState InType);` (scope `UE::GameFeatures`)

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureVersePathMapperCommandlet.h` (Public)


#### struct `FGameFeaturePluginInfo`  
`struct FGameFeaturePluginInfo`  
_L16-37_
- reflection: `USTRUCT()`
- L21 _public member_ `FString GfpUri;` — `UPROPERTY()`
- L24 _public member_ `TArray<FName> Dependencies;` — `UPROPERTY()`
- L27 _public member_ `TArray<FName> ImplicitDependencies;` — `UPROPERTY()`
- L30 _public prototype_ `bool Serialize(FArchive& Ar);` — Serialize natively

#### struct `GameFeatureVersePathMapper::FCaseSensitiveKeyMapFuncs`  
`template <typename ValueType> struct FCaseSensitiveKeyMapFuncs : BaseKeyFuncs<ValueType, FString, false>`  
_L43-57_
- inherits: `BaseKeyFuncs<ValueType,FString,false>`
- desc: Case sensitive hashing function for TMap
- L45 _public function_ `static inline const FString& GetSetKey(const TPair<FString, ValueType>& Element)`
- L49 _public function_ `static inline bool Matches(const FString& A, const FString& B)`
- L53 _public function_ `static inline uint32 GetKeyHash(const FString& Key)`

#### struct `GameFeatureVersePathMapper::FGameFeatureVersePathLookup`  
`struct FGameFeatureVersePathLookup`  
_L59-63_
- L61 _public member_ `TMap<FString, FName, FDefaultSetAllocator, GameFeatureVersePathMapper::FCaseSensitiveKeyMapFuncs<FName>> VersePathToGfpMap;`
- L62 _public member_ `TMap<FName, FGameFeaturePluginInfo> GfpInfoMap;`

#### struct `GameFeatureVersePathMapper::FDLCInfo`  
`struct FDLCInfo`  
_L65-70_
- L67 _public member_ `FString DLCName;`
- L68 _public member_ `FString InstallBundleName;`
- L69 _public member_ `TArray<FString> Plugins;`

#### class `GameFeatureVersePathMapper::FDepthFirstGameFeatureSorter`  
`class FDepthFirstGameFeatureSorter`  
_L80-134_
- desc: Finds plugin dependencies and returns them in dependency order (reverse topological sort order)
- L90 _private member_ `const TMap<FName, FGameFeaturePluginInfo>& GfpInfoMap;`
- L91 _private member_ `TMap<FName, EVisitState> VisitedPlugins;`
- L93 _private member_ `bool bIncludeVirtualNodes = false;`
- L95 _private prototype_ `bool Visit(FName Plugin, TFunctionRef<void(FName, const FString&)> AddOutput);`
- L102 _public function_ `FDepthFirstGameFeatureSorter(const TMap<FName, FGameFeaturePluginInfo>& InGfpInfoMap, bool bInIncludeVirtualNodes = false) : GfpInfoMap(InGfpInfoMap) , bIncludeVirtualNodes(bInIncludeVirtualNodes)` — Constructor @Param InGfpInfoMap Map containing plugin dependencies (FDepthFirstGameFeatureSorter points to this map, it is not copied)
- L115 _public prototype_ `bool Sort(TFunctionRef<FName()> GetNextRootPlugin, TFunctionRef<void(FName, const FString&)> AddOutput);` — Find and sort all dependencies @Param GetNextRootPlugin function that iterates plugins in the root set, returning None after the final plugin in the set. @Param AddOutput callback to receive roots and dependencies, called in dependency order @Return false if there is an error or a cyclic dependency is discovered
- L123 _public prototype_ `bool Sort(TConstArrayView<FName> RootPlugins, TFunctionRef<void(FName, const FString&)> AddOutput);` — Find and sort all dependencies @Param RootPlugins set of root plugins @Param AddOutput callback to receive roots and dependencies, called in dependency order @Return false if there is an error or a cyclic dependency is discovered
- L124 _public function_ `bool Sort(FName RootPlugin, TFunctionRef<void(FName, const FString&)> AddOutput)`
- L132 _public prototype_ `bool Sort(TConstArrayView<FName> RootPlugins, TArray<FName>& OutPlugins);` — Find and sort all dependencies @Param RootPlugins set of root plugins @Param OutPlugins roots and dependencies in dependency order @Return false if there is an error or a cyclic dependency is discovered
- L133 _public function_ `bool Sort(FName RootPlugin, TArray<FName>& OutPlugins)`

#### enum `GameFeatureVersePathMapper::FDepthFirstGameFeatureSorter::EVisitState`  
`enum class EVisitState : uint8`  
_L83-88_
- L85 _public enumerator_ `None`
- L86 _public enumerator_ `Visiting`
- L87 _public enumerator_ `Visited`

#### enum `GameFeatureVersePathMapper::EBuildLookupOptions`  
`enum class EBuildLookupOptions : uint32`  
_L136-141_
- L138 _public enumerator_ `None = 0`
- L139 _public enumerator_ `OnlyBaseBuildPlugins = 1 << 0` — Only include GFPs that are intrinsic to the current target
- L140 _public enumerator_ `WithDynamicCookPlugins = 1 << 1` — Include GFPs with CookBehavior.Type=ContentWorker

#### class `UGameFeatureVersePathMapperCommandlet`  
`class UGameFeatureVersePathMapperCommandlet : public UCommandlet`  
_L172-180_
- reflection: `UCLASS(config = Editor)`
- inherits: `UCommandlet`
- L177 _public prototype_ `virtual int32 Main(const FString& CmdLineParams) override;`
- L179 _public prototype_ `static FString GetGameFeatureRootVersePath();`

#### Free symbols / members of external scopes

- L32 _function_ `friend FArchive& operator<<(FArchive& Ar, FGameFeaturePluginInfo& GameFeaturePluginInfo)`
- L39 _namespace_ `namespace GameFeatureVersePathMapper`
- L72 _prototype_ `TArray<FDLCInfo> FindGFPToDLC(const ITargetPlatform* TargetPlatform);` (scope `GameFeatureVersePathMapper`)
- L74 _prototype_ `FString GetVerseAppDomain();` (scope `GameFeatureVersePathMapper`)
- L75 _prototype_ `FString GetAltVerseAppDomain();` (scope `GameFeatureVersePathMapper`)
- L142 _prototype_ `ENUM_CLASS_FLAGS(EBuildLookupOptions) TOptional<FGameFeatureVersePathLookup> BuildLookup( const ITargetPlatform* TargetPlatform = nullptr, const FAssetRegistryState* DevAR = nullptr, EBuildLookupOptions Options = EBuildLookupOptions::None, const TSet<FName>* ReferencedPackageNames = nullptr);` (scope `GameFeatureVersePathMapper`)
- L162 _prototype_ `FString GetVerseLookupBinaryPath(FStringView PlatformName = FStringView());` (scope `GameFeatureVersePathMapper`) — Returns the path where GameFeatureVersePaths.bin is written (commandlet) or read (runtime). Pass the target platform name at cook time to get Saved/Cooked/<Platform>/<Project>/GameFeatureVersePaths.bin. Pass empty (default) at runtime to get FPaths::ProjectDir()/GameFeatureVersePaths.bin (same level as AssetRegistry.bin).
- L168 _prototype_ `bool SerializeLookupBinary(FArchive& Ar, FGameFeatureVersePathLookup& Lookup);` (scope `GameFeatureVersePathMapper`) — Binary serialize or deserialize a FGameFeatureVersePathLookup. Direction is determined by Ar.IsLoading(). Returns false on magic/version mismatch or archive error.

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeaturesProjectPolicies.h` (Public)


#### struct `FPluginDependencyDetails`  
`struct FPluginDependencyDetails`  
_L20-23_
- L22 _public member_ `bool bFailIfNotFound = false;`

#### enum `EStreamingAssetInstallMode`  
`enum class EStreamingAssetInstallMode : uint8`  
_L25-29_
- L27 _public enumerator_ `GfpRequiredOnly` — only stream in data required for the GFP to load
- L28 _public enumerator_ `Full` — stream in all data

#### enum `EGameFeaturesProjectPoliciesThreadSafetyVersion`  
`enum class EGameFeaturesProjectPoliciesThreadSafetyVersion`  
_L33-42_
- desc: Specification of thread safety contract for a class derived from UGameFeaturesProjectPolicies. @see UGameFeaturesProjectPolicies::GetThreadSafetyVersion
- L36 _public enumerator_ `None = 0` — No methods are threadsafe, default for derived classes
- L41 _public enumerator_ `Initial` — Initial version when this enum was added. The follow methods must be callable from any thread: ShouldReadPluginDetails GetGameFeaturePluginURL IsPluginAllowed

#### class `UGameFeaturesProjectPolicies`  
`class UGameFeaturesProjectPolicies : public UObject`  
_L47-185_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: This class allows project-specific rules to be implemented for game feature plugins. Create a subclass and choose it in Project Settings .. Game Features
- L53 _public function_ `virtual void InitGameFeatureManager()` — Called when the game feature manager is initialized
- L56 _public function_ `virtual void ShutdownGameFeatureManager()` — Called when the game feature manager is shut down
- L73 _public prototype_ `virtual EGameFeaturesProjectPoliciesThreadSafetyVersion GetThreadSafetyVersion() const;` — Returns which methods of this class may be called from any thread. The methods which must be callable from any thread for each version are marked as such in this file. Derived classes should return the maximum value of the enum when they were written. The base implementation returns the maximum current version if this is not a derived class. Specifically, implementations should expect that these methods may be called concurrently with calls the game makes into UGameFeaturesSubsystem, and during the subsystem's own ticks. The subsystem makes no particular guarantees about avoid reentrancy if these methods call into UGameFeaturesSubsystem. e.g. if the implementation of IsPluginAllowed calls into the subsystem, the subsystem may call back into another method such as GetGameFeaturePluginURL. The possibility of priority inversion / deadlocks should be considered. Note that no implementation needs to support methods being called concurrently with InitGameFeatureManager or ShutdownGameFeatureManager unless otherwise specified.
- L76 _public prototype_ `virtual bool WillPluginBeCooked(const FString& PluginFilename, const FGameFeaturePluginDetails& PluginDetails) const;` — Called to determined the expected state of a plugin under the WhenLoading conditions.
- L79 _public function_ `virtual TArray<FPrimaryAssetId> GetPreloadAssetListForGameFeature(const UGameFeatureData* GameFeatureToLoad, bool bIncludeLoadedAssets = false) const` — Called when a game feature plugin enters the Loading state to determine additional assets to load
- L84 _public function_ `virtual const TArray<FName> GetPreloadBundleStateForGameFeature() const` — Returns the bundle state to use for assets returned by GetPreloadAssetListForGameFeature() See the Asset Manager documentation for more information about asset bundles Eventually, we should deprecate GetPreloadBundleStateForGameFeature in favor of GetPreloadBundleStateForPlugin since having the plugin name is useful
- L85 _public function_ `virtual const TArray<FName> GetPreloadBundleStateForPlugin(const FString& PluginName) const`
- L89 _public function_ `virtual void GetGameFeatureLoadingMode(bool& bLoadClientData, bool& bLoadServerData) const` — Called to determine if this should be treated as a client, server, or both for data preloading Actions can use this to decide what to load at runtime
- L93 _public prototype_ `virtual bool IsLoadingStartupPlugins() const;` — Called to determine if we are still during engine startup, which can modify loading behavior. This defaults to true for the first few frames of a normal game or editor, but can be overridden.
- L100 _public prototype_ `virtual bool GetGameFeaturePluginURL(const TSharedRef<IPlugin>& Plugin, FString& OutPluginURL) const;` — Called to determine the plugin URL for a given known Plugin. Can be used if the policy wants to deliver non file based URLs. THREAD SAFETY: Should be threadsafe for EGameFeaturesProjectPoliciesThreadSafetyVersion::Initial
- L103 _public function_ `virtual bool IsPluginAllowed(const FString& PluginURL) const` — `UE_DEPRECATED(5.6, "Replaced with IsPluginAllowed(PluginURL, OutReason).")`
- L111 _public function_ `virtual bool IsPluginAllowed(const FString& PluginURL, FString* OutReason) const` — Called to determine if a plugin is allowed to be loaded or not (e.g., when doing a fast cook a game might want to disable some or all game feature plugins) THREAD SAFETY: Should be threadsafe for EGameFeaturesProjectPoliciesThreadSafetyVersion::Initial
- L130 _public function_ `virtual bool IsPluginAllowed(const FString& PluginURL, const FGameFeaturePluginDetails* InDetails, FString* OutReason) const` — Called to determine if a plugin is allowed to be loaded or not. (e.g., when doing a fast cook a game might want to disable some or all game feature plugins) New version that provides plugin details when they are already available to avoid re-entrant calls. Prior version is not yet deprecated. THREAD SAFETY: Should be threadsafe for EGameFeaturesProjectPoliciesThreadSafetyVersion::Initial
- L142 _public function_ `virtual bool ShouldReadPluginDetails(const FString& PluginDescriptorFilename) const` — Return true if a uplugin's details should be read and false if it should be skipped. Skipped plugins will not be processed as GFPs and skipped as though they didn't exist. Useful to limit the number of uplugin files opened for perf reasons. THREAD SAFETY: Should be threadsafe for EGameFeaturesProjectPoliciesThreadSafetyVersion::Initial
- L145 _public function_ `virtual bool ShouldAllowMissingGameFeatureData(const FString& PluginName) const` — Return true if a plugin should be allowed to register if it doesn't have a GameFeatureData. Useful in cases where you want to allow the content of certain plugins to not exist.
- L150 _public prototype_ `virtual TValueOrError<FString, FString> ResolvePluginDependency(const FString& PluginURL, const FString& DependencyName, FPluginDependencyDetails& OutDetails) const;` — Called to resolve plugin dependencies, will successfully return an empty string if a dependency is not a GFP. This may be called with file protocol for built-in plugins in some cases, even if a different protocol is used at runtime. returns The dependency URL or an error if the dependency could not be resolved
- L151 _public prototype_ `virtual TValueOrError<FString, FString> ResolvePluginDependency(const FString& PluginURL, const FString& DependencyName) const;`
- L155 _public function_ `virtual TValueOrError<TArray<FName>, FString> GetStreamingAssetInstallBundles(FStringView PluginURL) const` — `UE_DEPRECATED(5.6, "Use GetStreamingAssetInstallModes instead of creating new bundles for streaming assets.")` — Called to resolve install bundles for streaming asset dependencies
- L159 _public prototype_ `virtual TValueOrError<TArray<EStreamingAssetInstallMode>, FString> GetStreamingAssetInstallModes(FStringView PluginURL, TConstArrayView<FName> InstallBundleNames) const;` — Called to resolve install modes for streaming asset dependencies Return a streaming asset install mode for each install bundle
- L163 _public prototype_ `virtual void ExplicitLoadGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginLoadComplete& CompleteDelegate, const bool bActivateGameFeatures);` — Called by code that explicitly wants to load a specific plugin (e.g., when using a fast cook a game might want to allow explicitly loaded game feature plugins)
- L166 _public prototype_ `virtual bool AllowAsyncLoad(FStringView PluginURL) const;` — Called to determine if async loading is allowed
- L173 _public prototype_ `virtual FString GetInstallBundleName(FStringView PluginName, bool bEvenIfDoesntExist = false);` — Returns the install bundle name if one exists for this plugin. @param - PluginName - the name of the GameFeaturePlugin we want to get a bundle for. Should be the same name as the .uplugin file @param - bEvenIfDoesntExist - when true will return the name of bundle we are looking for without checking if it exists or not.
- L180 _public prototype_ `virtual FString GetOptionalInstallBundleName(FStringView PluginName, bool bEvenIfDoesntExist = false);` — Returns the optional install bundle name if one exists for this plugin. @param - PluginName - the name of the GameFeaturePlugin we want to get a bundle for. Should be the same name as the .uplugin file @param - bEvenIfDoesntExist - when true will return the name of bundle we are looking for without checking if it exists or not.
- L184 _protected member_ `UE::FTransactionallySafeRecursiveMutex Mutex;` — This mutex can be used by derived classes for broad mutual exclusion

#### class `UDefaultGameFeaturesProjectPolicies`  
`class UDefaultGameFeaturesProjectPolicies : public UGameFeaturesProjectPolicies`  
_L192-202_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameFeaturesProjectPolicies`
- desc: This is a default implementation that immediately processes all game feature plugins the based on their BuiltInAutoRegister, BuiltInAutoLoad, and BuiltInAutoActivate settings. It will be used if no project-specific policy is set in Project Settings .. Game Features
- L198 _public prototype_ `virtual void InitGameFeatureManager() override;`
- L199 _public prototype_ `virtual void GetGameFeatureLoadingMode(bool& bLoadClientData, bool& bLoadServerData) const override;`
- L200 _public prototype_ `virtual const TArray<FName> GetPreloadBundleStateForPlugin(const FString& PluginName) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEFEATURES_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace GameFeatures` (scope `UE`)
- L17 _prototype_ `extern const TAutoConsoleVariable<bool>& GetCVarForceAsyncLoad();` (scope `UE::GameFeatures`)

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeaturesSubsystem.h` (Public)


#### struct `FGameFeatureStateChangeContext`  
`struct FGameFeatureStateChangeContext`  
_L77-110_
- desc: Struct that determines if game feature action state changes should be applied for cases where there are multiple worlds or contexts. The default value means to apply to all possible objects. This can be safely copied and used for later querying.
- L82 _public prototype_ `void SetRequiredWorldContextHandle(FName Handle);` — Sets a specific world context handle to limit changes to
- L85 _public prototype_ `bool ShouldApplyToWorldContext(const FWorldContext& WorldContext) const;` — Sees if the specific world context matches the application rules
- L88 _public prototype_ `bool ShouldApplyUsingOtherContext(const FGameFeatureStateChangeContext& OtherContext) const;` — True if events bound using this context should apply when using other context
- L91 _public function_ `inline bool operator==(const FGameFeatureStateChangeContext& OtherContext) const` — Check if this has the exact same state change application rules
- L109 _private member_ `FName WorldContextHandle;` — Specific world context to limit changes to, if none then it will apply to all

#### struct `FGameFeatureActivatingContext`  
`struct FGameFeatureActivatingContext : public FGameFeatureStateChangeContext`  
_L113-121_
- inherits: `FGameFeatureStateChangeContext`
- desc: Context that provides extra information for activating a game feature

#### struct `FGameFeatureDeactivatingContext`  
`struct FGameFeatureDeactivatingContext : public FGameFeatureStateChangeContext`  
_L124-143_
- inherits: `FGameFeatureStateChangeContext`
- desc: Context that provides extra information for deactivating a game feature, will use the same change context rules as the activating context
- L128 _public prototype_ `FSimpleDelegate PauseDeactivationUntilComplete(FString InPauserTag);` — Call this if your observer has an asynchronous action to complete as part of shutdown, and invoke the returned delegate when you are done (on the game thread!)
- L130 _public function_ `FGameFeatureDeactivatingContext(FStringView InPluginName, TFunction<void(FStringView InPauserTag)>&& InCompletionCallback) : PluginName(InPluginName) , CompletionCallback(MoveTemp(InCompletionCallback))`
- L136 _public function_ `int32 GetNumPausers() const`
- L138 _private member_ `FStringView PluginName;`
- L139 _private member_ `TFunction<void(FStringView InPauserTag)> CompletionCallback;`
- L140 _private member_ `int32 NumPausers = 0;`

#### struct `FGameFeaturePauseStateChangeContext`  
`struct FGameFeaturePauseStateChangeContext : public FGameFeatureStateChangeContext`  
_L146-169_
- inherits: `FGameFeatureStateChangeContext`
- desc: Context that provides extra information for a game feature changing its pause state
- L149 _public function_ `FGameFeaturePauseStateChangeContext(FString PauseStateNameIn, FString PauseReasonIn, bool bIsPausedIn) : PauseStateName(MoveTemp(PauseStateNameIn)) , PauseReason(MoveTemp(PauseReasonIn)) , bIsPaused(bIsPausedIn)`
- L157 _public function_ `bool IsPaused() const` — Returns true if the State has paused or false if it is resuming
- L160 _public function_ `const FString& GetPauseReason() const` — Returns an FString description of why the state has paused work.
- L163 _public function_ `const FString& GetPausingStateName() const` — Returns an FString description of what state has issued the pause change
- L166 _private member_ `FString PauseStateName;`
- L167 _private member_ `FString PauseReason;`
- L168 _private member_ `bool bIsPaused = false;`

#### struct `FGameFeaturePreMountingContext`  
`struct FGameFeaturePreMountingContext : public FGameFeatureStateChangeContext`  
_L173-181_
- inherits: `FGameFeatureStateChangeContext`
- desc: Context that provides extra information prior to mounting a plugin
- L176 _public member_ `bool bOpenPluginShaderLibrary = true;`

#### struct `FGameFeaturePostMountingContext`  
`struct FGameFeaturePostMountingContext : public FGameFeatureStateChangeContext`  
_L184-204_
- inherits: `FGameFeatureStateChangeContext`
- desc: Context that allows pausing prior to transitioning out of the mounting state
- L189 _public prototype_ `FSimpleDelegate PauseUntilComplete(FString InPauserTag);` — Call this if your observer has an asynchronous action to complete prior to transitioning out of the mounting state and invoke the returned delegate when you are done (on the game thread!)
- L191 _public function_ `FGameFeaturePostMountingContext(FStringView InPluginName, TFunction<void(FStringView InPauserTag)>&& InCompletionCallback) : PluginName(InPluginName) , CompletionCallback(MoveTemp(InCompletionCallback))`
- L196 _public function_ `int32 GetNumPausers() const`
- L199 _private member_ `FStringView PluginName;`
- L200 _private member_ `TFunction<void(FStringView InPauserTag)> CompletionCallback;`
- L201 _private member_ `int32 NumPausers = 0;`

#### enum `EBuiltInAutoState`  
`enum class EBuiltInAutoState : uint8`  
_L231-238_
- L233 _public enumerator_ `Invalid`
- L234 _public enumerator_ `Installed`
- L235 _public enumerator_ `Registered`
- L236 _public enumerator_ `Loaded`
- L237 _public enumerator_ `Active`

#### enum `EGameFeatureTargetState`  
`enum class EGameFeatureTargetState : uint8`  
_L242-249_
- reflection: `UENUM(BlueprintType)`
- L244 _public enumerator_ `Installed`
- L245 _public enumerator_ `Registered`
- L246 _public enumerator_ `Loaded`
- L247 _public enumerator_ `Active`
- L248 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FGameFeaturePluginReferenceDetails`  
`struct FGameFeaturePluginReferenceDetails`  
_L273-279_
- L276 _public member_ `FPluginString PluginName;`
- L278 _public member_ `bool bShouldActivate = false;`

#### struct `FGameFeaturePluginDetails`  
`struct FGameFeaturePluginDetails`  
_L281-289_
- L283 _public member_ `TArray<FGameFeaturePluginReferenceDetails> PluginDependencies;`
- L285 _public member_ `TMap<FPluginString, TSharedPtr<class FJsonValue>> AdditionalMetadata;`
- L287 _public member_ `bool bHotfixable = false;`
- L288 _public member_ `EBuiltInAutoState BuiltInAutoState = EBuiltInAutoState::Invalid;`

#### struct `FBuiltInGameFeaturePluginBehaviorOptions`  
`struct FBuiltInGameFeaturePluginBehaviorOptions`  
_L291-312_
- L293 _public member_ `EBuiltInAutoState AutoStateOverride = EBuiltInAutoState::Invalid;`
- L296 _public member_ `EGameFeatureTargetState MaximumState = EGameFeatureTargetState::Active;` — Maximum state this plugin is allowed to reach
- L299 _public member_ `bool bForceSyncLoading = false;` — Force this GFP to load synchronously even if async loading is allowed
- L302 _public member_ `bool bBatchProcess = false;` — Batch process GFPs if/when possible (could be used when processing multiple plugins)
- L305 _public member_ `bool bDoNotDownload = false;` — Disallows downloading, useful for conditionally loading content only if it's already been installed
- L308 _public member_ `bool bLogWarningOnForcedDependencyCreation = false;` — Log Warning if loading this GFP forces dependencies to be created, useful for catching GFP load filtering bugs
- L311 _public member_ `bool bLogErrorOnForcedDependencyCreation = false;` — Log Error if loading this GFP forces dependencies to be created, useful for catching GFP load filtering bugs

#### struct `FGameFeaturePluginAsyncHandle`  
`struct FGameFeaturePluginAsyncHandle : public TSharedFromThis<FGameFeaturePluginAsyncHandle>`  
_L314-321_
- inherits: `TSharedFromThis<FGameFeaturePluginAsyncHandle>`
- L316 _public prototype_ `virtual ~FGameFeaturePluginAsyncHandle() = default;`
- L317 _public prototype_ `virtual bool IsComplete() const = 0;`
- L318 _public prototype_ `virtual const UE::GameFeatures::FResult& GetResult() const = 0;`
- L319 _public prototype_ `virtual float GetProgress() const = 0;`
- L320 _public prototype_ `virtual void Cancel() = 0;`

#### struct `FGameFeaturePluginPredownloadHandle`  
`struct FGameFeaturePluginPredownloadHandle : public FGameFeaturePluginAsyncHandle`  
_L324-326_
- inherits: `FGameFeaturePluginAsyncHandle`
- desc: Handle to track a GFP predownload

#### struct `FGameFeaturePluginIdentifier`  
`struct FGameFeaturePluginIdentifier`  
_L331-391_
- reflection: `USTRUCT()`
- desc: Struct used to transform a GameFeaturePlugin URL into something that can uniquely identify the GameFeaturePlugin without including any transient data being passed in through the URL
- L335 _public prototype_ `FGameFeaturePluginIdentifier() = default;`
- L336 _public prototype_ `explicit FGameFeaturePluginIdentifier(FString PluginURL);`
- L338 _public function_ `FGameFeaturePluginIdentifier(const FGameFeaturePluginIdentifier& Other) : FGameFeaturePluginIdentifier(Other.PluginURL)`
- L342 _public prototype_ `FGameFeaturePluginIdentifier(FGameFeaturePluginIdentifier&& Other);`
- L344 _public function_ `FGameFeaturePluginIdentifier& operator=(const FGameFeaturePluginIdentifier& Other)`
- L350 _public prototype_ `FGameFeaturePluginIdentifier& operator=(FGameFeaturePluginIdentifier&& Other);`
- L354 _public prototype_ `bool operator==(const FGameFeaturePluginIdentifier& Other) const;` — Used to determine if 2 FGameFeaturePluginIdentifiers are referencing the same GameFeaturePlugin. Only matching on Identifying information instead of all the optional bundle information
- L357 _public prototype_ `void FromPluginURL(FString PluginURL);` — Function that fills out IdentifyingURLSubset from the given PluginURL
- L361 _public prototype_ `bool ExactMatchesURL(const FString& PluginURL) const;` — Returns true if this FGameFeaturePluginIdentifier exactly matches the given PluginURL. To match exactly all information in the PluginURL has to match and not just the IdentifyingURLSubset
- L363 _public function_ `EGameFeaturePluginProtocol GetPluginProtocol() const`
- L366 _public function_ `FStringView GetIdentifyingString() const` — Returns the Identifying information used for this Plugin. It is a subset of the URL used to create it.
- L369 _public prototype_ `FStringView GetPluginName() const;` — Returns the name of the plugin
- L372 _public function_ `const FString& GetFullPluginURL() const` — Get the Full PluginURL used to originally construct this identifier
- L381 _private member_ `FString PluginURL;` — Full PluginURL used to originally construct this identifier
- L384 _private member_ `FStringView IdentifyingURLSubset;` — The part of the URL that can be used to uniquely identify this plugin without any transient data
- L387 _private member_ `EGameFeaturePluginProtocol PluginProtocol;` — The protocol used in the URL for this GameFeaturePlugin URL

#### struct `FInstallBundlePluginProtocolOptions`  
`struct FInstallBundlePluginProtocolOptions`  
_L394-425_
- reflection: `USTRUCT()`
- L398 _public prototype_ `FInstallBundlePluginProtocolOptions();`
- L401 _public prototype_ `FInstallBundlePluginProtocolOptions(const FInstallBundlePluginProtocolOptions&) = default;`
- L402 _public prototype_ `FInstallBundlePluginProtocolOptions& operator=(const FInstallBundlePluginProtocolOptions&) = default;`
- L406 _public member_ `EInstallBundleRequestFlags InstallBundleFlags;` — EInstallBundleRequestFlags utilized during the download/install by InstallBundleManager
- L410 _public member_ `EInstallBundleReleaseRequestFlags ReleaseInstallBundleFlags;` — `UE_DEPRECATED(5.6, "Release flags are now applied internally and no longer need to be explicitly set.")` — EInstallBundleReleaseRequestFlags utilized during our release and uninstall states
- L413 _public member_ `bool bUninstallBeforeTerminate : 1;` — If we want to attempt to uninstall InstallBundle data installed by this plugin before terminating
- L416 _public member_ `bool bUserPauseDownload : 1;` — If we want to set the Downloading state to pause because of user interaction
- L419 _public member_ `bool bAllowIniLoading : 1;` — Allow the GFP to load INI files, should only be allowed for trusted content
- L422 _public member_ `bool bDoNotDownload : 1;` — Disallows downloading, useful for conditionally loading content only if it's already been installed
- L424 _public prototype_ `bool operator==(const FInstallBundlePluginProtocolOptions& Other) const;`

#### struct `FGameFeatureProtocolOptions`  
`struct FGameFeatureProtocolOptions : public TUnion<FInstallBundlePluginProtocolOptions, FNull>`  
_L427-453_
- inherits: `TUnion<FInstallBundlePluginProtocolOptions,FNull>`
- L429 _public prototype_ `FGameFeatureProtocolOptions();`
- L430 _public prototype_ `explicit FGameFeatureProtocolOptions(const FInstallBundlePluginProtocolOptions& InOptions);`
- L431 _public prototype_ `explicit FGameFeatureProtocolOptions(FNull InOptions);`
- L433 _public function_ `bool operator==(const FGameFeatureProtocolOptions& Other) const`
- L443 _public member_ `bool bForceSyncLoading : 1;` — Force this GFP to load synchronously even if async loading is allowed
- L446 _public member_ `bool bBatchProcess : 1;` — Batch process GFPs if/when possible (could be used when processing multiple plugins)
- L449 _public member_ `bool bLogWarningOnForcedDependencyCreation : 1;` — Log Warning if loading this GFP forces dependencies to be created, useful for catching GFP load filtering bugs
- L452 _public member_ `bool bLogErrorOnForcedDependencyCreation : 1;` — Log Error if loading this GFP forces dependencies to be created, useful for catching GFP load filtering bugs

#### struct `FGameFeatureInfo`  
`struct FGameFeatureInfo`  
_L456-462_
- desc: some important information about a gamefeature
- L458 _public member_ `FString Name;`
- L459 _public member_ `FString URL;`
- L460 _public member_ `bool bLoadedAsBuiltIn;`
- L461 _public member_ `EGameFeaturePluginState CurrentState;`

#### class `UGameFeaturesSubsystem`  
`class UGameFeaturesSubsystem : public UEngineSubsystem`  
_L466-1271_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- desc: The manager subsystem for game features
- L471 _public prototype_ `UGameFeaturesSubsystem(const FObjectInitializer& ObjectInitializer);`
- L474 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L475 _public prototype_ `virtual void Deinitialize() override;`
- L478 _public function_ `static UGameFeaturesSubsystem& Get()`
- L480 _public member_ `static FSimpleMulticastDelegate OnGameFeaturePolicyPreInit;`
- L481 _public member_ `static FSimpleMulticastDelegate OnGameFeaturePolicyPostInit;`
- L485 _public prototype_ `static TSharedPtr<FStreamableHandle> LoadGameFeatureData(const FString& GameFeatureToLoad, bool bStartStalled = false);` — Loads the specified game feature data and its bundles
- L486 _public prototype_ `static void UnloadGameFeatureData(const UGameFeatureData* GameFeatureToUnload);`
- L489 _public prototype_ `void AddObserver(UObject* Observer);` — `UE_DEPRECATED(5.7, "Use AddObserver with EObserverPluginStateUpdateMode parameter")`
- L498 _public prototype_ `void AddObserver(UObject* Observer, const EObserverPluginStateUpdateMode UpdateMode);` — Add Observer to be notified when plugin states change. Observer must implement IGameFeatureStateChangeObserver and be non-null
- L499 _public prototype_ `void RemoveObserver(UObject* Observer);`
- L501 _public prototype_ `void ForEachGameFeature(TFunctionRef<void(FGameFeatureInfo&&)> Visitor) const;`
- L508 _public function_ `template<class GameFeatureDataType, typename Func> void ForEachActiveGameFeature(Func InFunc) const` — Calls the compile-time lambda on each active game feature data of the specified type @param GameFeatureDataType       The kind of data required
- L527 _public function_ `template<class GameFeatureDataType, typename Func> void ForEachRegisteredGameFeature(Func InFunc) const` — Calls the compile-time lambda on each registered game feature data of the specified type @param GameFeatureDataType       The kind of data required
- L546 _public prototype_ `static FString GetPluginURL_FileProtocol(const FString& PluginDescriptorPath);` — Construct a 'file:' Plugin URL using from the PluginDescriptorPath THREAD SAFETY: Any thread
- L547 _public prototype_ `static FString GetPluginURL_FileProtocol(const FString& PluginDescriptorPath, TArrayView<const TPair<FString, FString>> AdditionalOptions);`
- L550 _public prototype_ `static FString GetPluginFilename_FileProtocol(const FString& PluginUrlFileProtocol);` — Get the file path portion of a file protocol URL
- L553 _public prototype_ `static FString GetPluginURL_InstallBundleProtocol(const FString& PluginName, TArrayView<const FString> BundleNames);` — Construct a 'installbundle:' Plugin URL using from the PluginName and required install bundles
- L554 _public prototype_ `static FString GetPluginURL_InstallBundleProtocol(const FString& PluginName, const FString& BundleName);`
- L555 _public prototype_ `static FString GetPluginURL_InstallBundleProtocol(const FString& PluginName, TArrayView<const FName> BundleNames);`
- L556 _public prototype_ `static FString GetPluginURL_InstallBundleProtocol(const FString& PluginName, FName BundleName);`
- L557 _public prototype_ `static FString GetPluginURL_InstallBundleProtocol(const FString& PluginName, TArrayView<const FName> BundleNames, TArrayView<const TPair<FString, FString>> AdditionalOptions);`
- L560 _public prototype_ `static EGameFeaturePluginProtocol GetPluginURLProtocol(FStringView PluginURL);` — Returns the plugin protocol for the specified URL
- L563 _public prototype_ `static bool IsPluginURLProtocol(FStringView PluginURL, EGameFeaturePluginProtocol PluginProtocol);` — Tests whether the plugin URL is the specified protocol
- L569 _public prototype_ `static bool ParsePluginURL(FStringView PluginURL, EGameFeaturePluginProtocol* OutProtocol = nullptr, FStringView* OutPath = nullptr, FStringView* OutOptions = nullptr);` — Parse the plugin URL into subparts THREAD SAFETY: Any thread
- L572 _public prototype_ `static bool ParsePluginURLOptions(FStringView URLOptionsString, TFunctionRef<void(EGameFeatureURLOptions Option, FStringView OptionString, FStringView OptionValue)> Output);` — Parse options from a plugin URL or the options subpart of the plugin URL
- L574 _public prototype_ `static bool ParsePluginURLOptions(FStringView URLOptionsString, EGameFeatureURLOptions OptionsFlags, TFunctionRef<void(EGameFeatureURLOptions Option, FStringView OptionString, FStringView OptionValue)> Output);`
- L576 _public prototype_ `static bool ParsePluginURLOptions(FStringView URLOptionsString, TConstArrayView<FStringView> AdditionalOptions, TFunctionRef<void(EGameFeatureURLOptions Option, FStringView OptionString, FStringView OptionValue)> Output);`
- L578 _public prototype_ `static bool ParsePluginURLOptions(FStringView URLOptionsString, EGameFeatureURLOptions OptionsFlags, TConstArrayView<FStringView> AdditionalOptions, TFunctionRef<void(EGameFeatureURLOptions Option, FStringView OptionString, FStringView OptionValue)> Output);`
- L584 _public prototype_ `void GetGameFeatureDataForActivePlugins(TArray<const UGameFeatureData*>& OutActivePluginFeatureDatas);` — Returns all the active plugins GameFeatureDatas
- L587 _public prototype_ `const UGameFeatureData* GetGameFeatureDataForActivePluginByURL(const FString& PluginURL);` — Returns the game feature data for an active plugin specified by PluginURL
- L590 _public prototype_ `const UGameFeatureData* GetGameFeatureDataForRegisteredPluginByURL(const FString& PluginURL, bool bCheckForRegistering = false);` — Returns the game feature data for a registered plugin specified by PluginURL
- L593 _public prototype_ `bool IsGameFeaturePluginInErrorState(const FString& PluginURL) const;` — Determines if a plugin is in an error state
- L596 _public prototype_ `bool IsGameFeaturePluginInstalled(const FString& PluginURL) const;` — Determines if a plugin is in the Installed state (or beyond)
- L599 _public prototype_ `bool IsGameFeaturePluginMounted(const FString& PluginURL) const;` — Determines if a plugin is beyond the Mounting state
- L602 _public prototype_ `bool IsGameFeaturePluginRegistered(const FString& PluginURL, bool bCheckForRegistering = false) const;` — Determines if a plugin is in the Registered state (or beyond)
- L605 _public prototype_ `bool IsGameFeaturePluginLoaded(const FString& PluginURL) const;` — Determines if a plugin is in the Loaded state (or beyond)
- L608 _public prototype_ `bool WasGameFeaturePluginLoadedAsBuiltIn(const FString& PluginURL) const;` — Was this game feature plugin loaded using the LoadBuiltInGameFeaturePlugin path
- L611 _public prototype_ `void LoadGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginLoadComplete& CompleteDelegate);` — Loads a single game feature plugin.
- L612 _public prototype_ `void LoadGameFeaturePlugin(const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, const FGameFeaturePluginLoadComplete& CompleteDelegate);`
- L613 _public prototype_ `void LoadGameFeaturePlugin(TConstArrayView<FString> PluginURLs, const FGameFeatureProtocolOptions& ProtocolOptions, const FMultipleGameFeaturePluginsLoaded& CompleteDelegate);`
- L616 _public prototype_ `void RegisterGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginLoadComplete& CompleteDelegate);` — Registers a single game feature plugin.
- L617 _public prototype_ `void RegisterGameFeaturePlugin(const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, const FGameFeaturePluginLoadComplete& CompleteDelegate);`
- L618 _public prototype_ `void RegisterGameFeaturePlugin(TConstArrayView<FString> PluginURLs, const FGameFeatureProtocolOptions& ProtocolOptions, const FMultipleGameFeaturePluginsLoaded& CompleteDelegate);`
- L621 _public prototype_ `void LoadAndActivateGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginLoadComplete& CompleteDelegate);` — Loads a single game feature plugin and activates it.
- L622 _public prototype_ `void LoadAndActivateGameFeaturePlugin(const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, const FGameFeaturePluginLoadComplete& CompleteDelegate);`
- L623 _public prototype_ `void LoadAndActivateGameFeaturePlugin(TConstArrayView<FString> PluginURLs, const FGameFeatureProtocolOptions& ProtocolOptions, const FMultipleGameFeaturePluginsLoaded& CompleteDelegate);`
- L626 _public prototype_ `void ChangeGameFeatureTargetState(const FString& PluginURL, EGameFeatureTargetState TargetState, const FGameFeaturePluginChangeStateComplete& CompleteDelegate);` — Changes the target state of a game feature plugin
- L627 _public prototype_ `void ChangeGameFeatureTargetState(const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, EGameFeatureTargetState TargetState, const FGameFeaturePluginChangeStateComplete& CompleteDelegate);`
- L628 _public prototype_ `void ChangeGameFeatureTargetState(TConstArrayView<FString> PluginURLs, const FGameFeatureProtocolOptions& ProtocolOptions, EGameFeatureTargetState TargetState, const FMultipleGameFeaturePluginsLoaded& CompleteDelegate);`
- L631 _public prototype_ `UE::GameFeatures::FResult UpdateGameFeatureProtocolOptions(const FString& PluginURL, const FGameFeatureProtocolOptions& NewOptions, bool* bOutDidUpdate = nullptr);` — Changes the protocol options of a game feature plugin. Useful to change any options data such as settings flags
- L634 _public prototype_ `bool GetGameFeaturePluginInstallPercent(const FString& PluginURL, float& Install_Percent) const;` — Gets the Install_Percent for single game feature plugin if it is active.
- L635 _public prototype_ `bool GetGameFeaturePluginInstallPercent(TConstArrayView<FString> PluginURLs, float& Install_Percent) const;`
- L638 _public prototype_ `bool IsGameFeaturePluginActive(const FString& PluginURL, bool bCheckForActivating = false) const;` — Determines if a plugin is in the Active state.
- L641 _public prototype_ `bool IsGameFeaturePluginActiveByName(FStringView PluginName, bool bCheckForActivating = false) const;` — Determines if a plugin is in the Active state.
- L644 _public prototype_ `bool DoesGameFeaturePluginNeedUpdate(const FString& PluginURL) const;` — Determines if a plugin is up to date or needs an update. Returns true if an update is available.
- L647 _public prototype_ `void DeactivateGameFeaturePlugin(const FString& PluginURL);` — Deactivates the specified plugin. Transition to [Terminal, Loaded]
- L648 _public prototype_ `void DeactivateGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginDeactivateComplete& CompleteDelegate);`
- L649 _public prototype_ `void DeactivateGameFeaturePlugin(TConstArrayView<FString> PluginURLs, const FMultipleGameFeaturePluginsDeactivate& CompleteDelegate);`
- L652 _public prototype_ `void UnloadGameFeaturePlugin(const FString& PluginURL, bool bKeepRegistered = false);` — Unloads the specified game feature plugin. Transition to bKeepRegistered = false -> [Terminal, Installed], bKeepRegistered = true -> [Terminal, Registered]
- L653 _public prototype_ `void UnloadGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginUnloadComplete& CompleteDelegate, bool bKeepRegistered = false);`
- L654 _public prototype_ `void UnloadGameFeaturePlugin(TConstArrayView<FString> PluginURLs, const FMultipleGameFeaturePluginsUnload& CompleteDelegate, bool bKeepRegistered = false);`
- L657 _public prototype_ `void ReleaseGameFeaturePlugin(const FString& PluginURL);` — Releases any game data stored for this GameFeaturePlugin. Does not uninstall data and it will remain on disk. [Terminal, StatusKnown]
- L658 _public prototype_ `void ReleaseGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginReleaseComplete& CompleteDelegate);`
- L659 _public prototype_ `void ReleaseGameFeaturePlugin(TConstArrayView<FString> PluginURLs, const FMultipleGameFeaturePluginsReleased& CompleteDelegate);`
- L665 _public prototype_ `void UninstallGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginUninstallComplete& CompleteDelegate = FGameFeaturePluginUninstallComplete());` — Uninstalls any game data stored for this GameFeaturePlugin and terminates the GameFeaturePlugin. If the given PluginURL is not found this will create a GameFeaturePlugin first and attempt to run it through the uninstall flow. This allows for the uninstalling of data that was installed on previous runs of the application where we haven't yet requested the GameFeaturePlugin that we would like to uninstall data for on this run.
- L666 _public prototype_ `void UninstallGameFeaturePlugin(const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, const FGameFeaturePluginUninstallComplete& CompleteDelegate = FGameFeaturePluginUninstallComplete());`
- L669 _public prototype_ `void TerminateGameFeaturePlugin(const FString& PluginURL);` — Terminate the GameFeaturePlugin and remove all associated plugin tracking data. Transition to [Terminal, Terminal]
- L670 _public prototype_ `void TerminateGameFeaturePlugin(const FString& PluginURL, const FGameFeaturePluginTerminateComplete& CompleteDelegate);`
- L671 _public prototype_ `void TerminateGameFeaturePlugin(TConstArrayView<FString> PluginURLs, const FMultipleGameFeaturePluginsTerminated& CompleteDelegate);`
- L674 _public prototype_ `void CancelGameFeatureStateChange(const FString& PluginURL);` — Attempt to cancel any state change. Calls back when cancelation is complete. Any other pending callbacks will be called with a canceled error.
- L675 _public prototype_ `void CancelGameFeatureStateChange(const FString& PluginURL, const FGameFeaturePluginChangeStateComplete& CompleteDelegate);`
- L676 _public prototype_ `void CancelGameFeatureStateChange(TConstArrayView<FString> PluginURLs, const FMultipleGameFeaturePluginChangeStateComplete& CompleteDelegate);`
- L683 _public prototype_ `bool GetPluginURLByName(FStringView PluginName, FString& OutPluginURL) const;` — If the specified plugin is known by the game feature system, returns the URL used to identify it @return true if the plugin exists, false if it was not found THREAD SAFETY: Any thread as long as GameSpecificPolicies meets version EGameFeaturesProjectPoliciesThreadSafetyVersion::Initial
- L684 _public prototype_ `bool GetPluginURLByName(FUtf8StringView PluginName, FString& OutPluginURL) const;`
- L687 _public prototype_ `FString GetPluginFilenameFromPluginURL(const FString& PluginURL) const;` — Get the plugin path from the plugin URL
- L690 _public prototype_ `FString GetPluginNameFromPluginURL(const FString& PluginURL) const;` — Get the plugin name from the plugin URL
- L693 _public prototype_ `static void FixPluginPackagePath(FString& PathToFix, const FString& PluginRootPath, bool bMakeRelativeToPluginRoot);` — Fixes a package path/directory to either be relative to plugin root or not. Paths relative to different roots will not be modified
- L697 _public function_ `template <typename T = UGameFeaturesProjectPolicies> T& GetPolicy() const` — Returns the game-specific policy for managing game feature plugins
- L703 _public typedef_ `typedef TFunctionRef<bool(const FString& PluginFilename, const FGameFeaturePluginDetails& Details, FBuiltInGameFeaturePluginBehaviorOptions& OutOptions)> FBuiltInPluginAdditionalFilters;`
- L704 _public typedef_ `typedef TFunction<bool(const FString& PluginFilename, const FGameFeaturePluginDetails& Details, FBuiltInGameFeaturePluginBehaviorOptions& OutOptions)> FBuiltInPluginAdditionalFilters_Copyable;`
- L707 _public prototype_ `void LoadBuiltInGameFeaturePlugin(const TSharedRef<IPlugin>& Plugin, FBuiltInPluginAdditionalFilters AdditionalFilter, const FGameFeaturePluginLoadComplete& CompleteDelegate = FGameFeaturePluginLoadComplete());` — Loads a built-in game feature plugin if it passes the specified filter
- L710 _public prototype_ `void LoadBuiltInGameFeaturePlugins(FBuiltInPluginAdditionalFilters AdditionalFilter, const FBuiltInGameFeaturePluginsLoaded& CompleteDelegate = FBuiltInGameFeaturePluginsLoaded());` — Loads all built-in game feature plugins that pass the specified filters
- L713 _public prototype_ `void LoadBuiltInGameFeaturePlugins_Amortized(const FBuiltInPluginAdditionalFilters_Copyable& AdditionalFilter_Copyable, int32 AmortizeRate, const FBuiltInGameFeaturePluginsLoaded& CompleteDelegate = FBuiltInGameFeaturePluginsLoaded());` — Loads all built-in game feature plugins that pass the specified filters, split over multiple frames processing only AmortizeRate plugins per frame if greater than 0. Note that AdditionalFilter must be a TFunction and not a TFunctionRef since it will be used in future ticks
- L714 _public prototype_ `void LoadBuiltInGameFeaturePlugins_Amortized(const TArray<TSharedRef<IPlugin>>& Plugins, const FBuiltInPluginAdditionalFilters_Copyable& AdditionalFilter, int32 AmortizeRate, const FBuiltInGameFeaturePluginsLoaded& CompleteDelegate = FBuiltInGameFeaturePluginsLoaded());`
- L716 _private prototype_ `TArray<TSharedRef<IPlugin>> GetInternalEnabledPlugins() const;`
- L717 _private prototype_ `void LoadBuiltInGameFeaturePluginsInternal(TArray<TSharedRef<IPlugin>> Plugins, FBuiltInPluginAdditionalFilters AdditionalFilter, const FBuiltInPluginAdditionalFilters_Copyable& AdditionalFilter_Copyable, int32 AmortizeRate, const FBuiltInGameFeaturePluginsLoaded& CompleteDelegate = FBuiltInGameFeaturePluginsLoaded());`
- L722 _public prototype_ `void GetLoadedGameFeaturePluginFilenamesForCooking(TArray<FString>& OutLoadedPluginFilenames) const;` — @TODO: GameFeaturePluginEnginePush: Might not be general enough for engine level, TBD
- L725 _public prototype_ `void FilterInactivePluginAssets(TArray<FAssetIdentifier>& AssetsToFilter) const;` — Removes assets that are in plugins we know to be inactive.  Order is not maintained.
- L728 _public prototype_ `void FilterInactivePluginAssets(TArray<FAssetData>& AssetsToFilter) const;` — Removes assets that are in plugins we know to be inactive.  Order is not maintained.
- L731 _public prototype_ `EGameFeaturePluginState GetPluginState(const FString& PluginURL) const;` — Returns the current state of the state machine for the specified plugin URL
- L734 _public prototype_ `EGameFeaturePluginState GetPluginState(FGameFeaturePluginIdentifier PluginIdentifier) const;` — Returns the current state of the state machine for the specified plugin PluginIdentifier
- L737 _public prototype_ `bool GetBuiltInGameFeaturePluginDetails(const TSharedRef<IPlugin>& Plugin, struct FGameFeaturePluginDetails& OutPluginDetails) const;` — Gets relevant properties out of a uplugin file. Should only be used for built-in GFPs
- L740 _public prototype_ `TSharedPtr<const FGameFeaturePluginDetails> GetBuiltInGameFeaturePluginDetails(const TSharedRef<IPlugin>& Plugin) const;` — Returns a shared pointer to immutable cached data about the given plugin. Should only be used for built-in GFPs
- L747 _public prototype_ `void LoadAllBuiltInGameFeaturePluginDetails(bool bForce = false);` — Load and cache all details for all builtin game feature plugins @param bForce If true, will try to load all details even if it has been done already. Use if the GameSpecificPolicies has changed which plugins are allowed.
- L754 _public prototype_ `bool GetBuiltInGameFeaturePluginURL(const TSharedRef<IPlugin>& Plugin, FString& OutPluginURL) const;` — Gets the URL for the given plugin, applying game-specific policies where appropriate. Should only be used for built-in GFPs THREAD SAFETY: Any thread as long as GameSpecificPolicies meets version EGameFeaturesProjectPoliciesThreadSafetyVersion::Initial
- L757 _public prototype_ `bool GetGameFeaturePluginDetails(const FString& PluginURL, struct FGameFeaturePluginDetails& OutPluginDetails) const;` — Gets relevant properties out of a uplugin file if it's installed
- L759 _public prototype_ `TSharedPtr<const FGameFeaturePluginDetails> GetGameFeaturePluginDetails(const FString& PluginURL) const;` — Returns a shared pointer to immutable cached data about the given plugin if it's installed.
- L764 _public prototype_ `bool GetGameFeatureControlsUPlugin(const FString& PluginURL, bool& OutGameFeatureControlsUPlugin) const;` — Sets OutGameFeatureControlsUPlugin to true if the uplugin was added by a GFP as opposed to existing independent of the GFP subsystem.
- L769 _public prototype_ `bool IsPluginAllowed(const FString& PluginURL, FString* OutReason = nullptr) const;` — THREAD SAFETY: Game thread only
- L774 _public prototype_ `bool IsPluginAllowed(const FString& PluginURL, const FGameFeaturePluginDetails* InDetails, FString* OutReason) const;` — THREAD SAFETY: Any thread
- L782 _public prototype_ `TSharedRef<FGameFeaturePluginPredownloadHandle> PredownloadGameFeaturePlugins(TConstArrayView<FString> PluginURLs, TUniqueFunction<void(const UE::GameFeatures::FResult&)> OnComplete = nullptr, TUniqueFunction<void(float)> OnProgress = nullptr, bool bWaitForBundlesToRelease = false);` — Pre-install any required game feature data, which can be useful for larger payloads. This does not instantiate any GFP although it is safe to do so before this finishes. This doesn't not resolve any dependencies, PluginURLs should contain all dependencies. If bWaitForBundlesToRelease is true, OnComplete will not be called until the bundles have been released
- L787 _public prototype_ `static EBuiltInAutoState DetermineBuiltInInitialFeatureState(TSharedPtr<FJsonObject> Descriptor, const FString& ErrorContext);` — Determine the initial feature state for a built-in plugin
- L788 _public prototype_ `static EBuiltInAutoState DetermineBuiltInInitialFeatureState(UE::Json::FConstObject Descriptor, const FString& ErrorContext);`
- L793 _public prototype_ `static EGameFeaturePluginState ConvertInitialFeatureStateToTargetState(EBuiltInAutoState InitialState);` — THREAD SAFETY: Any thread.
- L796 _public prototype_ `static void GetPluginsToCook(TSet<FString>& OutPlugins);` — Used during a DLC cook to determine which plugins should be cooked
- L798 _public prototype_ `static const TSet<FString>& GetDlcPlugins();`
- L805 _public prototype_ `static bool IsGameFeaturePlugin(const TSharedPtr<IPlugin>& InPlugin);` — Returns true if plugin is a GameFeaturePlugin @param InPlugin The plugin to check @return True if plugin considered a GameFeaturePlugin
- L807 _public prototype_ `bool GetPluginDebugStateEnabled(const FString& PluginUrl) const;`
- L808 _public prototype_ `void SetPluginDebugStateEnabled(const FString& PluginUrl, bool bEnabled);`
- L815 _public prototype_ `FString GetInstallBundleName(FStringView PluginName, bool bEvenIfDoesntExist = false);` — Returns the install bundle name if one exists for this plugin. Can be overridden by the policy provider. @param - PluginName - the name of the GameFeaturePlugin we want to get a bundle for. Should be the same name as the .uplugin file @param - bEvenIfDoesntExist - when true will return the name of bundle we are looking for without checking if it exists or not.
- L822 _public prototype_ `FString GetOptionalInstallBundleName(FStringView PluginName, bool bEvenIfDoesntExist = false);` — Returns the optional install bundle name if one exists for this plugin. Can be overridden by the policy provider @param - PluginName - the name of the GameFeaturePlugin we want to get a bundle for. Should be the same name as the .uplugin file @param - bEvenIfDoesntExist - when true will return the name of bundle we are looking for without checking if it exists or not.
- L831 _public prototype_ `bool GetBundlesForPlugin(FStringView PluginName, TArray<FName>& OutBundles);` — Returns the required bundles for this plugin based upon the current state machine. Unlike GetInstallBundleName this will return all the bundles and dependencies for the given plugin. @param - PluginName - the name of the GameFeaturePlugin we want to get the bundles for. @param - OutBundles - Output reference array for the found bundles for the plugin. @return true if an existing state machine with install bundle protocol is found.
- L832 _public prototype_ `bool GetBundlesForPluginURL(FStringView PluginURL, TArray<FName>& OutBundles);`
- L835 _private prototype_ `TSet<FString> GetActivePluginNames() const;`
- L837 _private prototype_ `void OnGameFeatureTerminating(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L840 _private prototype_ `void OnGameFeatureCheckingStatus(const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L843 _private prototype_ `void OnGameFeatureStatusKnown(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifierL);`
- L846 _private prototype_ `void OnGameFeaturePredownloading(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L847 _private prototype_ `void OnGameFeaturePostPredownloading(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L849 _private prototype_ `void OnGameFeatureDownloading(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L852 _private prototype_ `void OnGameFeatureReleasing(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L855 _private prototype_ `void OnGameFeaturePreMounting(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier, FGameFeaturePreMountingContext& Context);`
- L856 _private prototype_ `void OnGameFeaturePostMounting(const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier, FGameFeaturePostMountingContext& Context);`
- L859 _private prototype_ `void OnGameFeatureRegistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L862 _private prototype_ `void OnGameFeatureUnregistering(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L865 _private prototype_ `void OnGameFeatureActivating(const UGameFeatureData* GameFeatureData, const FString& PluginName, FGameFeatureActivatingContext& Context, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L868 _private prototype_ `void OnGameFeatureActivated(const UGameFeatureData* GameFeatureData, const FString& PluginName, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L871 _private prototype_ `void OnGameFeatureDeactivating(const UGameFeatureData* GameFeatureData, const FString& PluginName, FGameFeatureDeactivatingContext& Context, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L874 _private prototype_ `void OnGameFeatureLoading(const UGameFeatureData* GameFeatureData, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L877 _private prototype_ `void OnGameFeatureUnloading(const UGameFeatureData* GameFeatureData, const FGameFeaturePluginIdentifier& PluginIdentifier);`
- L880 _private prototype_ `void OnGameFeaturePauseChange(const FGameFeaturePluginIdentifier& PluginIdentifier, const FString& PluginName, FGameFeaturePauseStateChangeContext& Context);`
- L883 _private prototype_ `void OnAssetManagerCreated();`
- L886 _private prototype_ `static void AddGameFeatureToAssetManager(const UGameFeatureData* GameFeatureToAdd, const FString& PluginName, TArray<FName>& OutNewPrimaryAssetTypes);` — Scans for assets specified in the game feature data
- L888 _private prototype_ `static void RemoveGameFeatureFromAssetManager(const UGameFeatureData* GameFeatureToRemove, const FString& PluginName, const TArray<FName>& AddedPrimaryAssetTypes);`
- L891 _private prototype_ `void GetExplanationForUnavailablePackage(const FString& SkippedPackage, IPlugin* PluginIfFound, FStringBuilderBase& InOutExplanation);` — Provide additional causal information when a package is unavailable for load
- L898 _private prototype_ `bool ShouldUpdatePluginProtocolOptions(const UGameFeaturePluginStateMachine* StateMachine, const FGameFeatureProtocolOptions& NewOptions);` — THREA SAFETY: Any thread
- L903 _private prototype_ `UE::GameFeatures::FResult UpdateGameFeatureProtocolOptions(UGameFeaturePluginStateMachine* StateMachine, const FGameFeatureProtocolOptions& NewOptions, bool* bOutDidUpdate = nullptr);` — THREAD SAFETY: Any thread as long as no other thread is operating on that state machine. e.g. from a parallel for on the game thread, as state machine updates only happen on the game thread.
- L905 _private prototype_ `const UGameFeatureData* GetDataForStateMachine(UGameFeaturePluginStateMachine* GFSM) const;`
- L906 _private prototype_ `const UGameFeatureData* GetRegisteredDataForStateMachine(UGameFeaturePluginStateMachine* GFSM) const;`
- L909 _private prototype_ `TSharedPtr<const struct FGameFeaturePluginDetails> GetGameFeaturePluginDetailsInternal(const FString& PluginDescriptorFilename) const;` — Gets relevant properties out of a uplugin file
- L912 _private prototype_ `UE::Tasks::TTask<TSharedPtr<const struct FGameFeaturePluginDetails>> LoadGameFeaturePluginDetailsAsync(const FString& PluginDescriptorFilename) const;` — Load details for the given plugin if they are not cached and return them asynchronously.
- L915 _private prototype_ `TSharedPtr<const FGameFeaturePluginDetails> ParseGameFeaturePluginDetails(const FString& ErrorContext, TArrayView<TCHAR> JsonTxt) const;` — Parse FGameFeaturePluginDetails from a string. Note that parsing may modify the string in-place
- L917 _private prototype_ `TSharedPtr<const FGameFeaturePluginDetails> ParseGameFeaturePluginDetails(const FString& ErrorContext, TSharedRef<FJsonObject> JsonObject) const;` — Parse FGameFeaturePluginDetails from a JSON object
- L919 _private prototype_ `TSharedPtr<const FGameFeaturePluginDetails> ParseGameFeaturePluginDetails(const FString& ErrorContext, UE::Json::FConstObject JsonObject) const;` — Parse FGameFeaturePluginDetails from a RapidJSON object
- L922 _private prototype_ `void PruneCachedGameFeaturePluginDetails(const FString& PluginURL, const FString& PluginDescriptorFilename) const;` — Prunes any cached GFP details
- L930 _private prototype_ `UGameFeaturePluginStateMachine* FindGameFeaturePluginStateMachine(const FString& PluginURL) const;` — Gets the state machine associated with the specified URL THREAD SAFETY: Any thread.
- L936 _private prototype_ `UGameFeaturePluginStateMachine* FindGameFeaturePluginStateMachine(const FGameFeaturePluginIdentifier& PluginIdentifier) const;` — Gets the state machine associated with the specified PluginIdentifier THREAD SAFETY: Any thread.
- L942 _private prototype_ `UGameFeaturePluginStateMachine* FindOrCreateGameFeaturePluginStateMachine(const FString& PluginURL, const FGameFeatureProtocolOptions& ProtocolOptions, bool* bOutFoundExisting = nullptr);` — Gets the state machine associated with the specified URL, creates it if it doesnt exist THREAD SAFETY: Any thread.
- L945 _private prototype_ `void LoadBuiltInGameFeaturePluginComplete(const UE::GameFeatures::FResult& Result, UGameFeaturePluginStateMachine* Machine, FGameFeaturePluginStateRange RequestedDestination);` — Notification that a game feature has finished loading, and whether it was successful
- L952 _private prototype_ `void ChangeGameFeatureDestination(UGameFeaturePluginStateMachine* Machine, const FGameFeaturePluginStateRange& StateRange, FGameFeaturePluginChangeStateComplete CompleteDelegate);` — Sets a new destination state. Will attempt to cancel the current transition if the new destination is incompatible with the current destination Note: In the case that the existing machine is terminal, a new one will need to be created. In that case ProtocolOptions will be used for the new machine. THREAD SAFETY: Game thread.
- L953 _private prototype_ `void ChangeGameFeatureDestination(UGameFeaturePluginStateMachine* Machine, const FGameFeatureProtocolOptions& ProtocolOptions, const FGameFeaturePluginStateRange& StateRange, FGameFeaturePluginChangeStateComplete CompleteDelegate);`
- L956 _private prototype_ `void ChangeGameFeatureTargetStateComplete(UGameFeaturePluginStateMachine* Machine, const UE::GameFeatures::FResult& Result, FGameFeaturePluginChangeStateComplete CompleteDelegate);` — Generic notification that calls the Complete delegate without broadcasting anything else.
- L958 _private prototype_ `void BeginTermination(UGameFeaturePluginStateMachine* Machine);`
- L959 _private prototype_ `void FinishTermination(UGameFeaturePluginStateMachine* Machine);`
- L963 _private prototype_ `bool FindOrCreatePluginDependencyStateMachines(const FString& PluginURL, const FGameFeaturePluginStateMachineProperties& InStateProperties, TArray<UGameFeaturePluginStateMachine*>& OutDependencyMachines);` — Handler for when a state machine requests its dependencies. Returns false if the dependencies could not be read
- L967 _private prototype_ `bool FindPluginDependencyStateMachinesToActivate(const FString& PluginURL, const FString& PluginFilename, TArray<UGameFeaturePluginStateMachine*>& OutDependencyMachines) const;`
- L970 _private prototype_ `bool FindPluginDependencyStateMachinesToDeactivate(const FString& PluginURL, const FString& PluginFilename, TArray<UGameFeaturePluginStateMachine*>& OutDependencyMachines) const;`
- L974 _private prototype_ `template <typename CallableT> bool EnumeratePluginDependenciesWithShouldActivate(const FString& PluginURL, const FString& PluginFilename, CallableT Callable) const;`
- L977 _private prototype_ `void ListGameFeaturePlugins(const TArray<FString>& Args, UWorld* InWorld, FOutputDevice& Ar);` — Handle 'ListGameFeaturePlugins' console command
- L979 _private prototype_ `void SetExplanationForNotMountingPlugin(const FString& PluginURL, const FString& Explanation);`
- L1002 _private prototype_ `void CallbackObservers(EObserverCallback CallbackType, const FGameFeaturePluginIdentifier& PluginIdentifier, const FString* PluginName = nullptr, const UGameFeatureData* GameFeatureData = nullptr, FGameFeatureStateChangeContext* StateChangeContext = nullptr);`
- L1013 _private prototype_ `void BatchCallbackObservers(EBatchObserverCallback BatchCallbackType);`
- L1017 _private prototype_ `void RegisterRunningStateMachine(UGameFeaturePluginStateMachine* GFPSM);` — Registers a state machine that is in transition and running
- L1020 _private prototype_ `void UnregisterRunningStateMachine(UGameFeaturePluginStateMachine* GFPSM);` — Unregisters a state machine that was in transition is no longer running
- L1023 _private prototype_ `FDelegateHandle AddBatchingRequest(EGameFeaturePluginState State, FGameFeaturePluginRequestUpdateStateMachine UpdateDelegate);` — Adds a batching request for a given state so we can start listening for when state machines have arrived at a fence
- L1026 _private prototype_ `void CancelBatchingRequest(EGameFeaturePluginState State, FDelegateHandle DelegateHandle);` — Cancels an existing batching request
- L1028 _private prototype_ `void EnableTick();`
- L1029 _private prototype_ `void DisableTick();`
- L1030 _private prototype_ `bool Tick(float DeltaTime);`
- L1032 _private prototype_ `bool TickBatchProcessing();`
- L1036 _private prototype_ `void TryUpdateStateMachineImmediate(int64 Id);`
- L1041 _private member_ `TMap<int64, TObjectPtr<UGameFeaturePluginStateMachine>> GameFeaturePluginStateMachines;` — `UPROPERTY(Transient)` — The list of all game feature plugin state machine objects addressed by FGameFeaturePluginStateMachineProperties::Id
- L1045 _private member_ `TMap<FString, TObjectPtr<UGameFeaturePluginStateMachine>> GameFeaturesByIdentifier;` — `UPROPERTY(Transient)` — Lookup of game feature plugins by FGameFeaturePluginIdentifier::GetIdentifyingString
- L1048 _private member_ `TPimplPtr<UE::GameFeatures::FStateMachineExecutor> StateMachineExecutor;` — Private type controlling execution of state machine transitions when UE::GameFeatures::bUseNewExecutor
- L1052 _private member_ `FTSTicker::FDelegateHandle TickHandle;` — The tick handle if currently registered for a tick
- L1055 _private member_ `TArray<UGameFeaturePluginStateMachine*> RunningStateMachines;` — State machine currently in transition, used to limit search space when checking a batch processing fence or similar
- L1062 _private member_ `TMap<EGameFeaturePluginState, FGameFeatureBatchProcessingFence> BatchProcessingFences;`
- L1066 _private member_ `TArray<TObjectPtr<UGameFeaturePluginStateMachine>> TerminalGameFeaturePluginStateMachines;` — `UPROPERTY(Transient)` — Game feature plugin state machine objects that are being terminated. Used to prevent GC until termination is complete.
- L1069 _private member_ `TMap<FPluginString, FPluginString> GameFeaturePluginNameToPathMap;`
- L1070 _private member_ `mutable FTransactionallySafeRWLock GameFeaturePluginNameToPathMapLock;`
- L1073 _private member_ `mutable TMap<FString, TSharedRef<const FGameFeaturePluginDetails>> CachedPluginDetailsByFilename;`
- L1074 _private member_ `mutable FTransactionallySafeRWLock CachedGameFeaturePluginDetailsLock;`
- L1077 _private member_ `TArray<TObjectPtr<UObject>> Observers;` — `UPROPERTY()`
- L1080 _private member_ `TObjectPtr<UGameFeaturesProjectPolicies> GameSpecificPolicies;` — `UPROPERTY(Transient)`
- L1082 _private member_ `TUniquePtr<class UE::GameFeatures::FPackageLoadTracker> PackageLoadTracker;`
- L1086 _private member_ `TMap<FString, FString> UnmountedPluginNameToExplanation;` — When we decide not to mount a plugin, we can store an explanation here so that if we later attempt to load an asset from it we can tell the user why it's not available
- L1088 _private member_ `TUniquePtr<class FGameFeatureDataExternalAssetsPathCache> GameFeatureDataExternalAssetsPathCache;`
- L1092 _private member_ `TSet<FString> DebugStateChangedForPlugins;`
- L1094 _private member_ `FDelegateHandle GetExplanationForUnavailablePackageDelegateHandle;`
- L1096 _private member_ `bool bInitializedPolicyManager = false;`
- L1097 _private member_ `bool bLoadedBuiltInDetails = false;`
- L1099 _private member_ `static TSet<FString> DlcPlugins;`
- L1105 _private member_ `int64 NextInstanceId = 0;` — Next identifier to be used for a GFP state machine. Identifiers are not reused, and when a GFP is terminated and later recreated, a new identifier is assigned.
- L1116 _private prototype_ `void InitStateMachine(UGameFeaturePluginStateMachine* This, int64 Id, FGameFeaturePluginIdentifier InPluginIdentifier, const FGameFeatureProtocolOptions& InProtocolOptions);` — Initializes the state machine and assigns the URL for the plugin it manages. This sets the machine to the 'UnknownStatus' state.
- L1122 _private prototype_ `bool SetDestination( UGameFeaturePluginStateMachine* This, FGameFeaturePluginStateRange InDestination, TDelegate<void(UGameFeaturePluginStateMachine*, const UE::GameFeatures::FResult&)> OnFeatureStateTransitionComplete, FDelegateHandle* OutCallbackHandle = nullptr);` — Asynchronously transitions the state machine to the destination state range and reports when it is done. DestinationState must be of type EGameFeaturePluginStateType::Destination. If returns true and OnFeatureStateTransitionComplete is not called immediately, OutCallbackHandle will be set Returns false and does not callback if a transition is already in progress and the destination range is not compatible with the current range.
- L1129 _private prototype_ `bool TryCancel(UGameFeaturePluginStateMachine* This, TDelegate<void(UGameFeaturePluginStateMachine*)> OnFeatureStateTransitionCanceled, FDelegateHandle* OutCallbackHandle = nullptr) const;` — Cancel the current transition if possible
- L1133 _private prototype_ `UE::GameFeatures::FResult TryUpdatePluginProtocolOptions(UGameFeaturePluginStateMachine* This, const FGameFeatureProtocolOptions& InOptions, bool& bOutDidUpdate) const;` — Update the current PluginURL data for this plugin if possible. Returns false if this update fails or if the supplied InPluginURL matches the existing URL data for this plugin.
- L1136 _private prototype_ `void RemovePendingTransitionCallback(UGameFeaturePluginStateMachine* This, FDelegateHandle InHandle) const;` — Remove any pending callback from SetDestination
- L1139 _private prototype_ `void RemovePendingTransitionCallback(UGameFeaturePluginStateMachine* This, FDelegateUserObject DelegateObject) const;` — Remove any pending callback from SetDestination
- L1142 _private prototype_ `void RemovePendingCancelCallback(UGameFeaturePluginStateMachine* This, FDelegateHandle InHandle) const;` — Remove any pending callback from TryCancel
- L1145 _private prototype_ `void RemovePendingCancelCallback(UGameFeaturePluginStateMachine* This, FDelegateUserObject DelegateObject) const;` — Remove any pending callback from TryCancel
- L1148 _private prototype_ `const FGameFeaturePluginIdentifier& GetPluginIdentifier(const UGameFeaturePluginStateMachine* This) const;` — Returns the PluginIdentifier used to identify this plugin uniquely to the GameFeaturePlugin Subsystem
- L1151 _private prototype_ `const FString& GetGameFeatureName(const UGameFeaturePluginStateMachine* This) const;` — Returns the name of the game feature. Before StatusKnown, this returns the URL.
- L1154 _private prototype_ `const FString& GetPluginURL(const UGameFeaturePluginStateMachine* This) const;` — Returns the URL
- L1157 _private prototype_ `const FGameFeatureProtocolMetadata& GetProtocolMetadata(const UGameFeaturePluginStateMachine* This) const;` — Returns protocol medata
- L1160 _private prototype_ `const FGameFeatureProtocolOptions& GetProtocolOptions(const UGameFeaturePluginStateMachine* This) const;` — Returns any protocol options
- L1163 _private prototype_ `FGameFeatureProtocolOptions RecycleProtocolOptions(const UGameFeaturePluginStateMachine* This) const;` — Returns protocol options suitable for reuse by another state machine
- L1166 _private prototype_ `const FString& GetPluginName(const UGameFeaturePluginStateMachine* This) const;` — Returns the plugin name if known (plugin must have been registered to know the name).
- L1169 _private prototype_ `bool GetPluginFilename(const UGameFeaturePluginStateMachine* This, FString& OutPluginFilename) const;` — Returns the uplugin filename of the game feature. Before StatusKnown, this returns false.
- L1172 _private prototype_ `EGameFeaturePluginState GetCurrentState(const UGameFeaturePluginStateMachine* This) const;` — Returns the enum state for this machine
- L1175 _private prototype_ `FGameFeaturePluginStateRange GetDestination(const UGameFeaturePluginStateMachine* This) const;` — Returns the state range this machine is trying to move to
- L1178 _private prototype_ `FGameFeaturePluginStateInfo GetCurrentStateInfo(const UGameFeaturePluginStateMachine* This) const;` — Returns information about the current state
- L1181 _private prototype_ `bool IsRunning(const UGameFeaturePluginStateMachine* This) const;` — Returns true if attempting to reach a new destination state
- L1184 _private prototype_ `bool IsStatusKnown(const UGameFeaturePluginStateMachine* This) const;` — Returns true if the state is at least StatusKnown so we can query info about the game feature plugin
- L1187 _private prototype_ `bool IsAvailable(const UGameFeaturePluginStateMachine* This) const;` — Returns true if the plugin is available to download/load. Only call if IsStatusKnown is true
- L1190 _private prototype_ `bool IsInErrorState(const UGameFeaturePluginStateMachine* This) const;` — Returns true if the plugin is in an error state
- L1193 _private prototype_ `bool AllowAsyncLoading(const UGameFeaturePluginStateMachine* This) const;` — Whether this machine is allowed to be asynchronous
- L1196 _private prototype_ `bool HasAssetStreamingDependencies(const UGameFeaturePluginStateMachine* This) const;` — Returns true if the plugin will stream dependencies after installing. Only call if IsStatusKnown is true
- L1198 _private prototype_ `void SetWasLoadedAsBuiltIn(UGameFeaturePluginStateMachine* This);`
- L1200 _private prototype_ `bool WasLoadedAsBuiltIn(const UGameFeaturePluginStateMachine* This) const;`
- L1203 _private prototype_ `UGameFeatureData* GetGameFeatureDataForActivePlugin(UGameFeaturePluginStateMachine* This) const;` — If the plugin is activated already, we will retrieve its game feature data
- L1204 _private prototype_ `const UGameFeatureData* GetGameFeatureDataForActivePlugin(const UGameFeaturePluginStateMachine* This) const;`
- L1207 _private prototype_ `UGameFeatureData* GetGameFeatureDataForRegisteredPlugin(UGameFeaturePluginStateMachine* This, bool bCheckForRegistering = false) const;` — If the plugin is registered already, we will retrieve its game feature data
- L1208 _private prototype_ `const UGameFeatureData* GetGameFeatureDataForRegisteredPlugin(const UGameFeaturePluginStateMachine* This, bool bCheckForRegistering = false) const;`
- L1210 _private prototype_ `const FGameFeaturePluginStateMachineProperties& GetProperties(const UGameFeaturePluginStateMachine* This) const;`
- L1213 _private prototype_ `bool IsErrorStateUnrecoverable(const UGameFeaturePluginStateMachine* This) const;` — Returns true if the state machine is in an unrecoverable error state.
- L1216 _private prototype_ `void SetUnrecoverableError(UGameFeaturePluginStateMachine* This) const;` — Sets that the state machine is in an unrecoverable error. Used when the GFD is missing as that can't be recovered from.
- L1219 _private prototype_ `void ExcludeFromBatchProcessing(UGameFeaturePluginStateMachine* This);` — Request to exclude this plugin from batch processing, for e.g. if the plugin is a dependency and has batch processing enabled
- L1222 _private prototype_ `static void BatchProcess(EGameFeaturePluginState State, TConstArrayView<UGameFeaturePluginStateMachine*> GFPSMs);` — Helper static function to trigger state specific batch processing functions
- L1226 _private prototype_ `bool IsValidTransitionState(const UGameFeaturePluginStateMachine* This, EGameFeaturePluginState InState) const;` — Returns true if the specified state is not a transition state
- L1229 _private prototype_ `bool IsValidDestinationState(const UGameFeaturePluginStateMachine* This, EGameFeaturePluginState InDestinationState) const;` — Returns true if the specified state is a destination state
- L1232 _private prototype_ `bool IsValidErrorState(const UGameFeaturePluginStateMachine* This, EGameFeaturePluginState InDestinationState) const;` — Returns true if the specified state is a error state
- L1235 _private prototype_ `void UpdateStateMachine(UGameFeaturePluginStateMachine* This, TOptional<int32> MaxTransitions = {});` — Processes the current state and looks for state transitions
- L1238 _private prototype_ `void RegisterAsTransitioningStateMachine(UGameFeaturePluginStateMachine* This);` — Helper to register the state machine with the manager as a state machine in transiton
- L1241 _private prototype_ `void UnregisterAsTransitioningStateMachine(UGameFeaturePluginStateMachine* This);` — Helper to unregister the state machine with the manager as a state machine in transiton
- L1244 _private prototype_ `void CheckAddBatchingRequestForCurrentState(UGameFeaturePluginStateMachine* This);` — Adds a batching request for current state if state can be batched
- L1247 _private prototype_ `void CheckAndCancelBatchingRequestForCurrentState(UGameFeaturePluginStateMachine* This);` — Cancels batching re1quest for current state if one exists
- L1269 _private prototype_ `bool CancellAmortizedLoads(const FString& PluginURL);`
- L1270 _private member_ `TMap<FGuid, TWeakPtr<FAmmortizedLoadContext>> ActiveAmmoritzedLoads;`

#### enum `UGameFeaturesSubsystem::EObserverPluginStateUpdateMode`  
`enum class EObserverPluginStateUpdateMode`  
_L491-495_
- L493 _public enumerator_ `FutureOnly` — Only call the observer with future plugin state changes
- L494 _public enumerator_ `CurrentAndFuture` — Also update the observer with the current plugin state at add time - note, if project has a lot of plugins this can be expensive

#### enum `UGameFeaturesSubsystem::EObserverCallback`  
`enum class EObserverCallback`  
_L981-1000_
- L983 _public enumerator_ `CheckingStatus`
- L984 _public enumerator_ `Terminating`
- L985 _public enumerator_ `Predownloading`
- L986 _public enumerator_ `PostPredownloading`
- L987 _public enumerator_ `Downloading`
- L988 _public enumerator_ `Releasing`
- L989 _public enumerator_ `PreMounting`
- L990 _public enumerator_ `PostMounting`
- L991 _public enumerator_ `Registering`
- L992 _public enumerator_ `Unregistering`
- L993 _public enumerator_ `Loading`
- L994 _public enumerator_ `Unloading`
- L995 _public enumerator_ `Activating`
- L996 _public enumerator_ `Activated`
- L997 _public enumerator_ `Deactivating`
- L998 _public enumerator_ `PauseChanged`
- L999 _public enumerator_ `Count`

#### enum `UGameFeaturesSubsystem::EBatchObserverCallback`  
`enum class EBatchObserverCallback : uint8`  
_L1007-1011_
- L1009 _public enumerator_ `BatchOperationStarted`
- L1010 _public enumerator_ `BatchOperationComplete`

#### struct `UGameFeaturesSubsystem::FGameFeatureBatchProcessingFence`  
`struct FGameFeatureBatchProcessingFence`  
_L1058-1061_
- desc: Active fences
- L1060 _public member_ `FNotifyGameFeaturePluginRequestUpdateStateMachine NotifyUpdateStateMachines;`

#### struct `UGameFeaturesSubsystem::FAmmortizedLoadContext`  
`struct FAmmortizedLoadContext`  
_L1249-1267_
- L1251 _public member_ `FScopeLogTime ScopeLogTime{ TEXT("BuiltInGameFeaturePlugins loaded."), nullptr, FConditional`
- L1253 _public member_ `TArray<TSharedRef<IPlugin>> AmortizedPluginsRemaining;`
- L1254 _public member_ `TMap<FString, UE::GameFeatures::FResult> Results;`
- L1255 _public member_ `FBuiltInGameFeaturePluginsLoaded CompleteDelegate;`
- L1257 _public member_ `int32 NumPluginsLoaded = 0;`
- L1258 _public member_ `int32 PluginAmortizeRate = 0;`
- L1259 _public member_ `bool bPushedTagsBroadcast = false;`
- L1260 _public member_ `bool bPushedAssetBulkScanning = false;`
- L1261 _public member_ `bool bCancelled = false;`
- L1262 _public member_ `FGuid GUID;`
- L1264 _public prototype_ `FAmmortizedLoadContext();`
- L1266 _public prototype_ `~FAmmortizedLoadContext();`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API GAMEFEATURES_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace GameFeatures` (scope `UE`)
- L26 _prototype_ `bool TickUnloadPluginAssets(float DeltaTime);` (scope `UE::GameFeatures`)
- L47 _namespace_ `namespace GameFeaturesSubsystem`
- L53 _namespace_ `namespace UE`
- L53 _namespace_ `namespace GameFeatures` (scope `UE`)
- L55 _namespace_ `namespace PluginURLStructureInfo` (scope `UE::GameFeatures`)
- L58 _externvar_ `extern const TCHAR* OptionAssignOperator;` (scope `UE::GameFeatures::PluginURLStructureInfo`) — Character used to denote what value is being assigned to the option before it
- L61 _externvar_ `extern const TCHAR* OptionSeperator;` (scope `UE::GameFeatures::PluginURLStructureInfo`) — Character used to separate options on the URL. Used between each assigned value and the next Option name.
- L64 _externvar_ `extern const TCHAR* OptionListSeperator;` (scope `UE::GameFeatures::PluginURLStructureInfo`) — Character used to separate lists of values for a single option. Used between each entry in the list.
- L67 _namespace_ `namespace CommonErrorCodes` (scope `UE::GameFeatures`)
- L69 _externvar_ `extern const TCHAR* DependencyFailedRegister;` (scope `UE::GameFeatures::CommonErrorCodes`)
- L102 _function_ `inline friend uint32 GetTypeHash(const FGameFeatureStateChangeContext& OtherContext)` — Allow this to be used as a map key
- L206 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameFeatures, Log, All);`
- L208 _delegate_ `DECLARE_DELEGATE_OneParam(FGameFeaturePluginChangeStateComplete, const UE::GameFeatures::FResult& );` — Notification that a game feature plugin install/register/load/unload has finished
- L208 _prototype_ `DECLARE_DELEGATE_OneParam(FGameFeaturePluginChangeStateComplete, const UE::GameFeatures::FResult& );` — Notification that a game feature plugin install/register/load/unload has finished
- L211 _delegate_ `DECLARE_DELEGATE(FGameFeaturePluginRequestUpdateStateMachine);` — A request to update the state machine and process states
- L211 _prototype_ `DECLARE_DELEGATE(FGameFeaturePluginRequestUpdateStateMachine);` — A request to update the state machine and process states
- L212 _delegate_ `DECLARE_MULTICAST_DELEGATE(FNotifyGameFeaturePluginRequestUpdateStateMachine) using FGameFeaturePluginLoadComplete = FGameFeaturePluginChangeStateComplete;`
- L214 _typedef_ `using FGameFeaturePluginLoadComplete = FGameFeaturePluginChangeStateComplete;`
- L215 _typedef_ `using FGameFeaturePluginDeactivateComplete = FGameFeaturePluginChangeStateComplete;`
- L216 _typedef_ `using FGameFeaturePluginUnloadComplete = FGameFeaturePluginChangeStateComplete;`
- L217 _typedef_ `using FGameFeaturePluginReleaseComplete = FGameFeaturePluginChangeStateComplete;`
- L218 _typedef_ `using FGameFeaturePluginUninstallComplete = FGameFeaturePluginChangeStateComplete;`
- L219 _typedef_ `using FGameFeaturePluginTerminateComplete = FGameFeaturePluginChangeStateComplete;`
- L220 _typedef_ `using FGameFeaturePluginUpdateProtocolComplete = FGameFeaturePluginChangeStateComplete;`
- L222 _typedef_ `using FMultipleGameFeaturePluginChangeStateComplete = TDelegate<void(const TMap<FString, UE::GameFeatures::FResult>& Results)>;`
- L224 _typedef_ `using FBuiltInGameFeaturePluginsLoaded = FMultipleGameFeaturePluginChangeStateComplete;`
- L225 _typedef_ `using FMultipleGameFeaturePluginsLoaded = FMultipleGameFeaturePluginChangeStateComplete;`
- L226 _typedef_ `using FMultipleGameFeaturePluginsDeactivate = FMultipleGameFeaturePluginChangeStateComplete;`
- L227 _typedef_ `using FMultipleGameFeaturePluginsUnload = FMultipleGameFeaturePluginChangeStateComplete;`
- L228 _typedef_ `using FMultipleGameFeaturePluginsReleased = FMultipleGameFeaturePluginChangeStateComplete;`
- L229 _typedef_ `using FMultipleGameFeaturePluginsTerminated = FMultipleGameFeaturePluginChangeStateComplete;`
- L239 _prototype_ `const FString LexToString(const EBuiltInAutoState BuiltInAutoState);`
- L250 _prototype_ `const FString LexToString(const EGameFeatureTargetState GameFeatureTargetState);`
- L251 _prototype_ `void LexFromString(EGameFeatureTargetState& Value, const TCHAR* StringIn);`
- L260 _typedef_ `typedef FString FPluginString;`
- L261 _macro_ `# define UE_GAME_FEATURE_PLUGIN_DETAILS_USE_UTF8_STRING 0`
- L265 _typedef_ `typedef FUtf8String FPluginString;`
- L266 _macro_ `# define PLUGIN_TEXT(x) UTF8TEXT(x)`
- L267 _macro_ `# define TO_PLUGIN_STRING(x) FUtf8String(x)`
- L269 _macro_ `# define PLUGIN_TEXT(x) TEXT(x)`
- L270 _macro_ `# define TO_PLUGIN_STRING(x) x`
- L374 _function_ `friend inline uint32 GetTypeHash(const FGameFeaturePluginIdentifier& PluginIdentifier)`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeaturesSubsystemSettings.h` (Public)


#### class `UGameFeaturesSubsystemSettings`  
`class UGameFeaturesSubsystemSettings : public UDeveloperSettings`  
_L12-48_
- reflection: `UCLASS(MinimalAPI, config=Game, defaultconfig, meta = (DisplayName = "Game Features"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the Game Features framework
- L17 _public prototype_ `UGameFeaturesSubsystemSettings();`
- L20 _public member_ `static const FName LoadStateClient;` — State/Bundle to always load on clients
- L23 _public member_ `static const FName LoadStateServer;` — State/Bundle to always load on dedicated server
- L27 _public member_ `FSoftClassPath GameFeaturesManagerClassName;` — `UPROPERTY(config, EditAnywhere, Category=DefaultClasses, meta=(MetaClass="/Script/GameFeatures.GameFeaturesProjectPolicies", DisplayName="Game Feature Project Policy Class", ConfigRestartRequired=true))` — Name of a singleton class to spawn as the game feature project policy. If empty, it will spawn the default one (UDefaultGameFeaturesProjectPolicies)
- L31 _public member_ `TArray<FString> EnabledPlugins;` — `UPROPERTY(config, EditAnywhere, Category = GameFeatures)` — List of plugins that are forcibly enabled (e.g., via a hotfix)
- L35 _public member_ `TArray<FString> DisabledPlugins;` — `UPROPERTY(config, EditAnywhere, Category=GameFeatures)` — List of plugins that are forcibly disabled (e.g., via a hotfix)
- L39 _public member_ `TArray<FString> AdditionalPluginMetadataKeys;` — `UPROPERTY(config, EditAnywhere, Category=GameFeatures)` — List of metadata (additional keys) to try parsing from the .uplugin to provide to FGameFeaturePluginDetails
- L45 _public prototype_ `bool IsValidGameFeaturePlugin(const FString& PluginDescriptorFilename) const;` — Returns true if the specified (normalized or full) path is a game feature plugin Safe to call from any thread.
- L46 _public prototype_ `bool IsValidGameFeaturePlugin(FStringView PluginDescriptorFilename) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEFEATURES_API`

### `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/IrisFilterGameFeatureAction.h` (Public)


#### class `UIrisFilterGameFeatureAction`  
`class UIrisFilterGameFeatureAction : public UGameFeatureAction`  
_L17-36_
- reflection: `UCLASS(MinimalAPI, CollapseCategories, meta = (DisplayName = "Create Iris Network Filter"))`
- inherits: `UGameFeatureAction`
- L22 _public prototype_ `virtual void OnGameFeatureActivating(FGameFeatureActivatingContext&) override;`
- L23 _public prototype_ `virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext&) override;`
- L26 _private prototype_ `bool ShouldApplyToWorld(const FGameFeatureStateChangeContext& StateChangeContext, const FWorldContext& WorldContext) const;`
- L27 _private prototype_ `void AddFilterToWorld(UWorld* World);`
- L28 _private prototype_ `void RemoveFilterFromWorld(UWorld* World);`
- L32 _private member_ `FNetObjectFilterDefinition FilterDefinition;` — `UPROPERTY(EditAnywhere, Category=Filter)` — Filters to create on activation & destroy on deactivation.
- L35 _private member_ `TSet<TWeakObjectPtr<UWorld>> AddedToWorlds;` — Worlds the filter was added to, and should be removed from.
