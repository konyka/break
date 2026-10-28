# Plugins / ChaosModularVehicleEngine

- module root: `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine`
- headers: 32; symbols: 784
- symbol kinds: class=34, delegate=13, enum=8, enumerator=30, function=104, macro=20, member=293, namespace=4, prototype=242, struct=32, typedef=4
- PublicDependencyModuleNames: AnimGraphRuntime, Chaos, ChaosModularVehicle, ChaosSolverEngine, ChaosVehiclesCore, Core, CoreUObject, Engine, EnhancedInput, GeometryCollectionEngine, NetCore, RHI, RenderCore, Renderer

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Private/ChaosModularVehicle/ChaosModularVehicleEnginePluginPrivate.h` (Private)


#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosModularVehicle"), STATGROUP_ChaosModularVehicle,`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/AnimNode_ModularVehicleController.h` (Public)


#### struct `FAnimNode_ModularVehicleController`  
`struct FAnimNode_ModularVehicleController : public FAnimNode_SkeletalControlBase`  
_L19-48_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Simple controller that replaces or adds to the translation/rotation of a single bone.
- L23 _public prototype_ `FAnimNode_ModularVehicleController();`
- L26 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L30 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L31 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L32 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L37 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L46 _private member_ `TArray<FModuleLookupData> Modules;`
- L47 _private member_ `const FModularVehicleAnimationInstanceProxy* AnimInstanceProxy;`

#### struct `FAnimNode_ModularVehicleController::FModuleLookupData`  
`struct FModuleLookupData`  
_L40-44_
- L42 _public member_ `int32 ModuleIndex;`
- L43 _public member_ `FBoneReference BoneReference;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ChaosModularVehicleEnginePlugin.h` (Public)


#### class `IChaosModularVehicleEnginePlugin`  
`class IChaosModularVehicleEnginePlugin : public IModuleInterface`  
_L13-47_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IChaosModularVehicleEnginePlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L41 _private prototype_ `void PhysSceneInit(FPhysScene* PhysScene);`
- L42 _private prototype_ `void PhysSceneTerm(FPhysScene* PhysScene);`
- L44 _private member_ `FDelegateHandle OnPhysSceneInitHandle;`
- L45 _private member_ `FDelegateHandle OnPhysSceneTermHandle;`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ChaosSimModuleManager.h` (Public)


#### class `FSimModuleOutputRecord`  
`class FSimModuleOutputRecord`  
_L23-51_
- desc: Helper class to store physics async output results Todo: generalize this as a Chaos helper template class
- L28 _public prototype_ `void ConsumeOutput(Chaos::TSimCallbackOutputHandle<FChaosSimModuleManagerAsyncOutput>&& Output);` — Consumes an async output. Assumes the output is dated later than previously consumed outputs. Uses move semantics, and will replace the oldest stored output.
- L31 _public prototype_ `const FChaosSimModuleManagerAsyncOutput* GetPreviousOutput() const;` — Returns the oldest stored output
- L32 _public prototype_ `FChaosSimModuleManagerAsyncOutput* GetPreviousOutput();`
- L35 _public prototype_ `const FChaosSimModuleManagerAsyncOutput* GetNextOutput() const;` — Returns the most recent stored output
- L36 _public prototype_ `FChaosSimModuleManagerAsyncOutput* GetNextOutput();`
- L39 _public prototype_ `double GetLatestOutputStartTime() const;` — Returns the start time (InternalTime) of the most recent output
- L42 _public prototype_ `double GetInterpolationFactor(double AtInternalTime) const;` — Returns the interpolation factor
- L45 _public prototype_ `void Clear();` — Clears (and deletes) stored outputs
- L48 _private member_ `Chaos::TSimCallbackOutputHandle<FChaosSimModuleManagerAsyncOutput> CachedOutput_0;`
- L49 _private member_ `Chaos::TSimCallbackOutputHandle<FChaosSimModuleManagerAsyncOutput> CachedOutput_1;`
- L50 _private member_ `bool bPreviousOutputIs0 = true;`

#### class `FChaosSimModuleManager`  
`class FChaosSimModuleManager`  
_L53-136_
- L60 _public prototype_ `FChaosSimModuleManager(FPhysScene* PhysScene);`
- L61 _public prototype_ `~FChaosSimModuleManager();`
- L63 _public prototype_ `static void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues);`
- L64 _public prototype_ `static void OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources);`
- L65 _public prototype_ `static void OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`
- L68 _public function_ `FPhysScene_Chaos& GetScene() const` — Get Physics Scene
- L73 _public prototype_ `void AddVehicle(TWeakObjectPtr<UModularVehicleBaseComponent> Vehicle);` — Register a Physics vehicle for processing
- L78 _public prototype_ `void RemoveVehicle(TWeakObjectPtr<UModularVehicleBaseComponent> Vehicle);` — Unregister a Physics vehicle from processing
- L83 _public prototype_ `void ScenePreTick(FPhysScene* PhysScene, float DeltaTime);` — Update vehicle tuning and other state such as input
- L86 _public prototype_ `void DetachFromPhysScene(FPhysScene* PhysScene);` — Detach this vehicle manager from a FPhysScene (remove delegates, remove from map etc)
- L89 _public prototype_ `void Update(FPhysScene* PhysScene, float DeltaTime);` — Update simulation of registered vehicles
- L92 _public prototype_ `void PostUpdate(FChaosScene* PhysScene);` — Post update step
- L94 _public prototype_ `void OnNetDriverCreated(UWorld* InWorld, UNetDriver* InNetDriver);`
- L95 _public prototype_ `void RegisterNetTokenDataStores(UNetDriver* InNetDriver);`
- L98 _public prototype_ `void InjectInputs_External(int32 PhysicsStep, int32 NumSteps);` — Called on GT but before Physics thread runs - PT tick rate
- L100 _public prototype_ `void ParallelUpdateVehicles();`
- L103 _public prototype_ `static FChaosSimModuleManager* GetManagerFromScene(FPhysScene* PhysScene);` — Find a vehicle manager from an FPhysScene
- L106 _protected prototype_ `void RegisterCallbacks(UWorld* InWorld);`
- L107 _protected prototype_ `void UnregisterCallbacks();`
- L111 _private member_ `static TMap<FPhysScene*, FChaosSimModuleManager*> SceneToModuleManagerMap;` — Map of physics scenes to corresponding vehicle manager
- L114 _private member_ `FPhysScene_Chaos& Scene;` — The physics scene we belong to
- L116 _private member_ `static bool GInitialized;`
- L119 _private member_ `TArray<TWeakObjectPtr<UModularVehicleBaseComponent>> CUVehicles;` — Test out new vehicle bass class
- L122 _private member_ `FDelegateHandle OnNetDriverCreatedHandle;` — callback delegates
- L123 _private member_ `FDelegateHandle OnPhysScenePreTickHandle;`
- L124 _private member_ `FDelegateHandle OnPhysScenePostTickHandle;`
- L126 _private member_ `static FDelegateHandle OnPostWorldInitializationHandle;`
- L127 _private member_ `static FDelegateHandle OnWorldCleanupHandle;`
- L130 _private member_ `FChaosSimModuleManagerAsyncCallback* AsyncCallback;` — Async callback from the physics engine - we can run our simulation here
- L131 _private member_ `int32 Timestamp;`
- L132 _private member_ `int32 SubStepCount;`
- L135 _private member_ `FSimModuleOutputRecord OutputRecord;` — Record used to store the two most recent outputs which time surrounds the time we interpolate at

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ChaosSimModuleManagerAsyncCallback.h` (Public)


#### struct `FSimModuleDebugParams`  
`struct FSimModuleDebugParams`  
_L29-33_
- L31 _public member_ `bool EnableMultithreading = false;`
- L32 _public member_ `bool EnableNetworkStateData = true;`

#### enum `EChaosAsyncVehicleDataType`  
`enum EChaosAsyncVehicleDataType : int8`  
_L35-39_
- L37 _public enumerator_ `AsyncInvalid`
- L38 _public enumerator_ `AsyncDefault`

#### struct `FModuleTransform`  
`struct FModuleTransform`  
_L42-46_
- L44 _public member_ `int TransforIndex;`
- L45 _public member_ `FTransform Transform;`

#### struct `FModularVehicleInputs`  
`struct FModularVehicleInputs`  
_L50-71_
- reflection: `USTRUCT()`
- desc: Vehicle inputs from the player controller
- L54 _public function_ `FModularVehicleInputs() : Reverse(false) , KeepAwake(false)`
- L62 _public member_ `bool Reverse;` — `UPROPERTY()` — Reversing state
- L66 _public member_ `bool KeepAwake;` — `UPROPERTY()` — Keep vehicle awake
- L69 _public member_ `FModuleInputContainer Container;` — `UPROPERTY()`

#### struct `FNetworkModularVehicleInputs`  
`struct FNetworkModularVehicleInputs : public FNetworkPhysicsData`  
_L75-100_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsData`
- desc: Vehicle input data that will be used in the input history to be applied while simulating
- L81 _public member_ `FModularVehicleInputs VehicleInputs;` — `UPROPERTY()` — List of incoming control inputs coming from the local client
- L84 _public prototype_ `virtual void ApplyData(UActorComponent* NetworkComponent) const override;` — Apply the data onto the network physics component
- L87 _public prototype_ `virtual void BuildData(const UActorComponent* NetworkComponent) override;` — Build the data from the network physics component
- L90 _public prototype_ `bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);` — Serialize data function that will be used to transfer the struct across the network
- L93 _public prototype_ `virtual void InterpolateData(const FNetworkPhysicsData& MinData, const FNetworkPhysicsData& MaxData) override;` — Interpolate the data in between two inputs
- L96 _public prototype_ `virtual void MergeData(const FNetworkPhysicsData& FromData) override;` — Merge data when multiple inputs happen an same simulation tick
- L99 _public prototype_ `virtual void DecayData(float DecayAmount) override;` — Decay data during resimulation by DecayAmount which increases over resimulation frames from 0.0 -> 1.0 when the input is being reused

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNetworkModularVehicleInputs> : public TStructOpsTypeTraitsBase2<FNetworkModularVehicleInputs>`  
_L103-109_
- inherits: `TStructOpsTypeTraitsBase2<FNetworkModularVehicleInputs>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L106-108_

#### struct `FNetworkModularVehicleStateNetTokenData`  
`struct FNetworkModularVehicleStateNetTokenData`  
_L112-126_
- reflection: `USTRUCT()`
- L116 _public member_ `TArray<uint32> Hashes;` — `UPROPERTY()`
- L118 _public member_ `TArray<int32> Indexes;` — `UPROPERTY()`
- L120 _public member_ `TArray<bool> ModuleShouldSerialize;` — `UPROPERTY()`
- L124 _public prototype_ `uint64 GetUniqueKey() const;`
- L125 _public prototype_ `void Init(const Chaos::FModuleNetDataArray& ModuleData);`

#### struct `FNetworkModularVehicleStates`  
`struct FNetworkModularVehicleStates : public FNetworkPhysicsData`  
_L132-150_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsData`
- desc: Vehicle state data that will be used in the state history to rewind the simulation
- L136 _public member_ `inline static FName StashServerFrameKey = FName("Ser`
- L137 _public member_ `Chaos::FModuleNetDataArray ModuleData;`
- L139 _public prototype_ `virtual void ApplyData(UActorComponent* NetworkComponent) const override;` — Apply the data onto the network physics component
- L142 _public prototype_ `virtual void BuildData(const UActorComponent* NetworkComponent) override;` — Build the data from the network physics component
- L145 _public prototype_ `bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);` — Serialize data function that will be used to transfer the struct across the network
- L146 _public prototype_ `bool DeltaNetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);`
- L149 _public prototype_ `virtual void InterpolateData(const FNetworkPhysicsData& MinData, const FNetworkPhysicsData& MaxData) override;` — Interpolate the data in between two states

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNetworkModularVehicleStates> : public TStructOpsTypeTraitsBase2<FNetworkModularVehicleStates>`  
_L153-159_
- inherits: `TStructOpsTypeTraitsBase2<FNetworkModularVehicleStates>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L156-158_

#### struct `FPhysicsVehicleOutput`  
`struct FPhysicsVehicleOutput`  
_L164-209_
- desc: Per Vehicle Output State from Physics Thread to Game Thread
- L166 _public function_ `FPhysicsVehicleOutput()`
- L170 _public function_ `~FPhysicsVehicleOutput()`
- L175 _public function_ `void Clean()`
- L187 _public function_ `const Chaos::FSimOutputData* GetOutputData(int InModuleGuid)`
- L207 _public member_ `TArray<Chaos::FSimOutputData*> SimTreeOutputData;`
- L208 _public member_ `TArray<Chaos::FCreatedModule> NewlyCreatedModuleGuids;`

#### struct `FPhysicsModularVehicleTraits`  
`struct FPhysicsModularVehicleTraits`  
_L211-215_
- L213 _public typedef_ `using InputsType = FNetworkModularVehicleInputs;`
- L214 _public typedef_ `using StatesType = FNetworkModularVehicleStates;`

#### struct `FGameStateInputs`  
`struct FGameStateInputs`  
_L218-221_
- desc: #TBD
- L220 _public member_ `FModuleInputContainer StateInputContainer;`

#### enum `ETraceType`  
`enum class ETraceType : uint8`  
_L224-231_
- reflection: `UENUM()`
- L227 _public enumerator_ `Raycast UMETA(DisplayName = "Raycast")` — Use ray to determine suspension length to ground
- L230 _public enumerator_ `Spherecast UMETA(DisplayName = "Spherecast")` — Use sphere to determine suspension length to ground

#### struct `FPhysicsModularVehicleInputs`  
`struct FPhysicsModularVehicleInputs`  
_L236-253_
- desc: Per Vehicle input State from Game Thread to Physics Thread
- L238 _public function_ `FPhysicsModularVehicleInputs() : CollisionChannel(ECollisionChannel::ECC_WorldDynamic) , TraceParams() , TraceCollisionResponse() , TraceType(ETraceType::Raycast) , CurrentTimeDilation(1.0f)`
- L246 _public member_ `mutable FNetworkModularVehicleInputs NetworkInputs;`
- L247 _public member_ `mutable ECollisionChannel CollisionChannel;`
- L248 _public member_ `mutable FCollisionQueryParams TraceParams;`
- L249 _public member_ `mutable FCollisionResponseContainer TraceCollisionResponse;`
- L250 _public member_ `mutable ETraceType TraceType;`
- L251 _public member_ `mutable FGameStateInputs StateInputs;`
- L252 _public member_ `mutable float CurrentTimeDilation;`

#### struct `FModularVehicleAsyncInput`  
`struct FModularVehicleAsyncInput`  
_L258-291_
- desc: Per Vehicle Input State from Game Thread to Physics Thread
- L260 _public function_ `FModularVehicleAsyncInput(EChaosAsyncVehicleDataType InType = EChaosAsyncVehicleDataType::AsyncInvalid) : Type(InType) , Vehicle(nullptr)`
- L267 _public prototype_ `virtual ~FModularVehicleAsyncInput() = default;`
- L272 _public prototype_ `virtual TUniquePtr<struct FModularVehicleAsyncOutput> Simulate(UWorld* World, const float DeltaSeconds, const float TotalSeconds, bool& bWakeOut) const;` — Vehicle simulation running on the Physics Thread
- L274 _public prototype_ `virtual void OnContactModification(Chaos::FCollisionContactModifier& Modifier) const;`
- L275 _public prototype_ `virtual void ApplyDeferredForces() const;`
- L276 _public prototype_ `virtual void ProcessInputs();`
- L278 _public function_ `void SetVehicle(UModularVehicleBaseComponent* VehicleIn)`
- L279 _public function_ `UModularVehicleBaseComponent* GetVehicle() const`
- L281 _public member_ `const EChaosAsyncVehicleDataType Type;`
- L282 _public member_ `IPhysicsProxyBase* Proxy;`
- L283 _public member_ `bool bIsLocallyControlled = false;`
- L285 _public member_ `FPhysicsModularVehicleInputs PhysicsInputs;`
- L289 _private member_ `UModularVehicleBaseComponent* Vehicle;`

#### struct `FChaosSimModuleManagerAsyncInput`  
`struct FChaosSimModuleManagerAsyncInput : public Chaos::FSimCallbackInput`  
_L293-305_
- inherits: `Chaos::FSimCallbackInput`
- L295 _public member_ `TArray<TUniquePtr<FModularVehicleAsyncInput>> VehicleInputs;`
- L297 _public member_ `TWeakObjectPtr<UWorld> World;`
- L298 _public member_ `int32 Timestamp = INDEX_NONE;`
- L300 _public function_ `void Reset()`

#### struct `FModularVehicleAsyncOutput`  
`struct FModularVehicleAsyncOutput`  
_L310-327_
- desc: Async Output Data
- L312 _public member_ `const EChaosAsyncVehicleDataType Type;`
- L313 _public member_ `bool bValid;` — indicates no work was done
- L314 _public member_ `FPhysicsVehicleOutput VehicleSimOutput;`
- L315 _public member_ `UModularVehicleBaseComponent* Vehicle;`
- L317 _public function_ `FModularVehicleAsyncOutput(EChaosAsyncVehicleDataType InType = EChaosAsyncVehicleDataType::AsyncInvalid) : Type(InType) , bValid(false) , Vehicle(nullptr)`
- L323 _public function_ `virtual ~FModularVehicleAsyncOutput()`

#### struct `FChaosSimModuleManagerAsyncOutput`  
`struct FChaosSimModuleManagerAsyncOutput : public Chaos::FSimCallbackOutput`  
_L333-342_
- inherits: `Chaos::FSimCallbackOutput`
- desc: Async Output for all of the vehicles handled by this Vehicle Manager
- L335 _public member_ `TArray<TUniquePtr<FModularVehicleAsyncOutput>> VehicleOutputs;`
- L336 _public member_ `int32 Timestamp = INDEX_NONE;`
- L338 _public function_ `void Reset()`

#### class `FChaosSimModuleManagerAsyncCallback`  
`class FChaosSimModuleManagerAsyncCallback : public Chaos::TSimCallbackObject<FChaosSimModuleManagerAsyncInput, FChaosSimModuleManagerAsyncOutput , Chaos::ESimCallbackOptions::Presimulate | Chaos::ESimCallbackOptions::Rewind | Chaos::ESimCallbackOptions::ContactModification>`  
_L347-356_
- inherits: `Chaos::TSimCallbackObject<FChaosSimModuleManagerAsyncInput,FChaosSimModuleManagerAsyncOutput,Chaos::ESimCallbackOptions::Presimulate|Chaos::ESimCallbackOptions::Rewind|Chaos::ESimCallbackOptions::ContactModification>`
- desc: Async callback from the Physics Engine where we can perform our vehicle simulation
- L351 _public prototype_ `virtual FName GetFNameForStatId() const override;`
- L353 _private prototype_ `virtual void ProcessInputs_Internal(int32 PhysicsStep) override;`
- L354 _private prototype_ `virtual void OnPreSimulate_Internal() override;`
- L355 _private prototype_ `virtual void OnContactModification_Internal(Chaos::FCollisionContactModifier& Modifications) override;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`
- L26 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosSimModuleManager"), STATGROUP_ChaosSimModuleManager,`
- L107 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon71d3d0540103`)
- L157 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon71d3d0540203`)

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ClusterUnionVehicleComponent.h` (Public)


#### class `UClusterUnionVehicleComponent`  
`class UClusterUnionVehicleComponent : public UClusterUnionComponent`  
_L12-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClusterUnionComponent`
- L17 _public prototype_ `UClusterUnionVehicleComponent(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual bool HasAnySockets() const override;`
- L21 _public prototype_ `virtual bool DoesSocketExist(FName InSocketName) const override;`
- L22 _public prototype_ `virtual FTransform GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace = RTS_World) const override;`
- L23 _public prototype_ `virtual void QuerySupportedSockets(TArray<FComponentSocketDescription>& OutSockets) const override;`
- L27 _public member_ `TArray<FModularVehicleSocket> Sockets;` — `UPROPERTY(EditAnywhere, meta = (BlueprintSpawnableComponent), Category = "ModularVehicle")`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/InputModifier_ModularVehicleSmooth.h` (Public)


#### class `UInputModifier_ModularVehicleSmooth`  
`class UInputModifier_ModularVehicleSmooth : public UInputModifier`  
_L19-35_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "Modular Vehicle Smooth Modifier"))`
- inherits: `UInputModifier`
- desc: UInputModifier_ModularVehicleSmooth Add this as a Modifier on any float‐based Action (e.g. “Steer”) to get a smoother, “lagged” feel. To match the behaviour of the OG chaos vehicle plugin
- L29 _public member_ `float RiseRate = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smoothing")` — How quickly to “catch up” to the raw input. Higher numbers = snappier response; lower = more lag/smoothing.
- L32 _protected prototype_ `virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;`
- L34 _protected member_ `float PreviousValue = 0.0f;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/InputProducer.h` (Public)


#### class `UVehicleDefaultInputProducer`  
`class UVehicleDefaultInputProducer : public UVehicleInputProducerBase`  
_L12-28_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UVehicleInputProducerBase`
- desc: The default input producer that takes real input from the player and provides it to the simulation
- L19 _public prototype_ `virtual void InitializeContainer(TArray<FModuleInputSetup>& SetupData, FInputNameMap& NameMapOut, EModuleInputQuantizationType InInputQuantizationType) override;` — initialize the input buffer container
- L22 _public prototype_ `virtual void BufferInput(const FInputNameMap& InNameMap, const FName InName, const FModuleInputValue& InValue, EModuleInputBufferActionType BufferAction) override;` — capture input at game thread frequency
- L25 _public prototype_ `virtual void ProduceInput(int32 PhysicsStep, int32 NumSteps, const FInputNameMap& InNameMap, FModuleInputContainer& InOutContainer) override;` — produce input for PT simulation at PT frequency
- L27 _public member_ `FModuleInputContainer MergedInput;`

#### class `UVehiclePlaybackInputProducer`  
`class UVehiclePlaybackInputProducer : public UVehicleInputProducerBase`  
_L33-57_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UVehicleInputProducerBase`
- desc: Example input generator, generates random input inot a per frame buffer then replays from the buffer, looping back to the start when the bugger is exhausted
- L40 _public prototype_ `virtual void InitializeContainer(TArray<FModuleInputSetup>& SetupData, FInputNameMap& NameMapOut, EModuleInputQuantizationType InInputQuantizationType) override;` — initialize the input buffer containers
- L43 _public prototype_ `virtual void BufferInput(const FInputNameMap& InNameMap, const FName InName, const FModuleInputValue& InValue, EModuleInputBufferActionType BufferAction) override;` — capture input at game thread frequency
- L46 _public prototype_ `virtual void ProduceInput(int32 PhysicsStep, int32 NumSteps, const FInputNameMap& InNameMap, FModuleInputContainer& InOutContainer) override;` — produce input for PT simulation at PT frequency
- L49 _public function_ `virtual TArray<FModuleInputContainer>* GetTestInputBuffer()` — Special case override for providing test input straight onto the physics thread
- L52 _public function_ `virtual bool IsLoopingTestInputBuffer()` — Special case override for providing test input straight onto the physics thread
- L54 _public member_ `TArray<FModuleInputContainer> PlaybackBuffer;`
- L55 _public member_ `int32 BufferLength = 150;`
- L56 _public member_ `int32 StartStep = 0;`

#### class `UVehicleRandomInputProducer`  
`class UVehicleRandomInputProducer : public UVehicleInputProducerBase`  
_L62-79_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UVehicleInputProducerBase`
- desc: Example input generator, generates random input on the fly for the PT
- L69 _public prototype_ `virtual void InitializeContainer(TArray<FModuleInputSetup>& SetupData, FInputNameMap& NameMapOut, EModuleInputQuantizationType InInputQuantizationType) override;` — initialize the input buffer containers
- L72 _public prototype_ `virtual void BufferInput(const FInputNameMap& InNameMap, const FName InName, const FModuleInputValue& InValue, EModuleInputBufferActionType BufferAction) override;` — capture input at game thread frequency
- L75 _public prototype_ `virtual void ProduceInput(int32 PhysicsStep, int32 NumSteps, const FInputNameMap& InNameMap, FModuleInputContainer& InOutContainer) override;` — produce input for PT simulation at PT frequency
- L77 _public member_ `FModuleInputContainer PlaybackContainer;`
- L78 _public member_ `int32 ChangeInputFrequency = 10;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleAnimationInstance.h` (Public)


#### struct `FModuleAnimationData`  
`struct FModuleAnimationData`  
_L15-21_
- L17 _public member_ `FName BoneName;`
- L18 _public member_ `FRotator RotOffset;`
- L19 _public member_ `FVector LocOffset;`
- L20 _public member_ `uint16 Flags;`

#### struct `FModularVehicleAnimationInstanceProxy`  
`struct FModularVehicleAnimationInstanceProxy : public FAnimInstanceProxy`  
_L25-54_
- reflection: `USTRUCT()`
- inherits: `FAnimInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L29 _public function_ `FModularVehicleAnimationInstanceProxy() : FAnimInstanceProxy()`
- L34 _public function_ `FModularVehicleAnimationInstanceProxy(UAnimInstance* Instance) : FAnimInstanceProxy(Instance)`
- L41 _public prototype_ `void SetModularVehicleComponent(const UModularVehicleBaseComponent* InWheeledVehicleComponent);`
- L44 _public prototype_ `virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;` — FAnimInstanceProxy interface begin
- L47 _public function_ `const TArray<FModuleAnimationData>& GetModuleAnimData() const`
- L53 _private member_ `TArray<FModuleAnimationData> ModuleInstances;`

#### class `UModularVehicleAnimationInstance`  
`class UModularVehicleAnimationInstance : public UAnimInstance`  
_L57-91_
- reflection: `UCLASS(MinimalAPI, transient)`
- inherits: `UAnimInstance`
- L63 _private prototype_ `class AModularVehicleClusterPawn* GetVehicle();` — `UFUNCTION(BlueprintCallable, Category = "Animation")` — Makes a montage jump to the end of a named section.
- L66 _public member_ `TArray<TArray<FModuleAnimationData>> ModuleData;`
- L69 _public function_ `void SetModularVehicleComponent(const UModularVehicleBaseComponent* InWheeledVehicleComponent)`
- L75 _public function_ `const UModularVehicleBaseComponent* GetModularVehicleComponent() const`
- L82 _private prototype_ `virtual void NativeInitializeAnimation() override;` — UAnimInstance interface begin
- L83 _private prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`
- L84 _private prototype_ `virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;`
- L87 _private member_ `FModularVehicleAnimationInstanceProxy AnimInstanceProxy;`
- L90 _private member_ `TObjectPtr<const UModularVehicleBaseComponent> ModularVehicleComponent;` — `UPROPERTY(transient)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleAsset.h` (Public)


#### class `FModularVehicleAssetEdit`  
`class FModularVehicleAssetEdit`  
_L23-36_
- desc: FModularVehicleAssetEdit Structured RestCollection access where the scope of the object controls serialization back into the dynamic collection
- L29 _public prototype_ `FModularVehicleAssetEdit(UModularVehicleAsset* InAsset);` — @param UModularVehicleAsset	The FAsset to edit
- L30 _public prototype_ `~FModularVehicleAssetEdit();`
- L32 _public prototype_ `UModularVehicleAsset* GetAsset();`
- L35 _private member_ `UModularVehicleAsset* Asset;`

#### class `UModularVehicleAsset`  
`class UModularVehicleAsset : public UObject`  
_L45-65_
- reflection: `UCLASS(MinimalAPI, customconstructor)`
- inherits: `UObject`
- desc: UModularVehicleAsset (UObject) UObject wrapper for the FModularVehicleAsset
- L52 _public prototype_ `UModularVehicleAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L53 _public function_ `FModularVehicleAssetEdit EditRestCollection()`
- L55 _public prototype_ `void Serialize(FArchive& Ar);`
- L60 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, AdvancedDisplay, Category = GeometryCollection)` — Information for thumbnail rendering
- L64 _private member_ `TSharedPtr<FModularSimCollection, ESPMode::ThreadSafe> ModularSimCollection;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleBaseComponent.h` (Public)


#### struct `FVehicleComponentData`  
`struct FVehicleComponentData`  
_L32-42_
- reflection: `USTRUCT()`
- L36 _public member_ `int Guid = -1;`
- L40 _public member_ `TObjectPtr<USceneComponent> VisualComponentToAnimate = nullptr;` — `UPROPERTY()` — Cached reference to the visual component to animate (if different from sim component)

#### struct `FModularReplicatedState`  
`struct FModularReplicatedState : public FModularVehicleInputs`  
_L46-54_
- reflection: `USTRUCT()`
- inherits: `FModularVehicleInputs`
- desc: Additional replicated state
- L50 _public function_ `FModularReplicatedState() : FModularVehicleInputs()`

#### struct `FConstructionData`  
`struct FConstructionData`  
_L58-67_
- reflection: `USTRUCT()`
- L63 _public member_ `TObjectPtr<USceneComponent> Component = nullptr;` — `UPROPERTY()`
- L66 _public member_ `int32 ConstructionIndex = INDEX_NONE;` — `UPROPERTY()`

#### struct `FModuleAnimationSetup`  
`struct FModuleAnimationSetup`  
_L71-111_
- reflection: `USTRUCT()`
- L75 _public function_ `FModuleAnimationSetup(FName BoneNameIn, int TransformIndexIn, int GuidIn = INDEX_NONE) : BoneName(BoneNameIn) , RotOffset(FRotator::ZeroRotator) , LocOffset(FVector::ZeroVector) , CombinedRotation(FQuat::Identity) , AnimFlags(0) , TransformIndex(TransformIndexIn) , ModuleGUID(GuidIn) , InitialRotOffset(FQuat::Identity) , InitialLocOffset(FVector::ZeroVector)`
- L88 _public function_ `FModuleAnimationSetup() : BoneName(NAME_None) , RotOffset(FRotator::ZeroRotator) , LocOffset(FVector::ZeroVector) , CombinedRotation(FQuat::Identity) , AnimFlags(0) , TransformIndex(INDEX_NONE) , ModuleGUID(INDEX_NONE) , InitialRotOffset(FQuat::Identity) , InitialLocOffset(FVector::ZeroVector)`
- L101 _public member_ `FName BoneName;` — required for skeletal mesh
- L102 _public member_ `FRotator RotOffset;`
- L103 _public member_ `FVector LocOffset;`
- L104 _public member_ `FQuat CombinedRotation;`
- L105 _public member_ `uint16 AnimFlags;`
- L106 _public member_ `int TransformIndex;` — required for non skeletal mesh case
- L107 _public member_ `int ModuleGUID;`
- L108 _public member_ `FQuat InitialRotOffset;`
- L109 _public member_ `FVector InitialLocOffset;`

#### class `UModularVehicleBaseComponent`  
`class UModularVehicleBaseComponent : public UPawnMovementComponent`  
_L115-488_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (Physics), meta = (BlueprintSpawnableComponent), hidecategories = (PlanarMovement, "Components|Movement|Planar", Activation, "Components|Activation"))`
- inherits: `UPawnMovementComponent`
- L119 _private prototype_ `~UModularVehicleBaseComponent();`
- L133 _public typedef_ `using FInputNameMap = TMap<FName, int>;`
- L135 _public prototype_ `APlayerController* GetPlayerController() const;`
- L136 _public prototype_ `bool IsLocallyControlled() const;`
- L137 _public function_ `void SetTreeProcessingOrder(ESimTreeProcessingOrder TreeProcessingOrderIn)`
- L138 _public function_ `ESimTreeProcessingOrder GetTreeProcessingOrder()`
- L140 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L142 _public function_ `virtual bool ShouldCreatePhysicsState() const override`
- L143 _public prototype_ `virtual void OnCreatePhysicsState() override;`
- L144 _public prototype_ `virtual void OnDestroyPhysicsState() override;`
- L145 _public prototype_ `virtual void SetClusterComponent(UClusterUnionComponent* InPhysicalComponent);`
- L147 _public prototype_ `virtual void BeginPlay() override;`
- L148 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L150 _public prototype_ `void ProduceInput(int32 PhysicsStep, int32 NumSteps, FModularVehicleAsyncInput* AsyncInput);`
- L153 _public prototype_ `virtual void CreateAssociatedSimComponents(USceneComponent* ParentComponent, USceneComponent* AttachedComponent, int ParentIndex, int TransformIndex, Chaos::FSimTreeUpdates& TreeUpdatesOut);` — Create sim components hierarchy from parent component - used by original cluster code union path
- L156 _public prototype_ `virtual void CreateIndependentSimComponents(USceneComponent* RootComponent, USceneComponent* AttachedComponent, int ParentIndex, int TransformIndex, Chaos::FSimTreeUpdates& TreeUpdatesOut);` — Create sim components in hierarchy from parent component - used by code path that does not rely on cluster union
- L158 _public prototype_ `void PreTickGT(float DeltaTime);`
- L159 _public prototype_ `void UpdateState(float DeltaTime);`
- L160 _public prototype_ `void SetCurrentAsyncData(FChaosSimModuleManagerAsyncOutput* CurOutput, FChaosSimModuleManagerAsyncOutput* NextOutput, float Alpha, int32 VehicleManagerTimestamp);`
- L162 _public prototype_ `void ParallelUpdate(const Chaos::FCreatedModules& ModuleEvents);`
- L163 _public prototype_ `void Update(float DeltaTime);`
- L164 _public prototype_ `void PostUpdate();`
- L165 _public prototype_ `void FinalizeSimCallbackData(FChaosSimModuleManagerAsyncInput& Input);`
- L168 _public prototype_ `void ProcessControls(float DeltaTime);` — handle stand-alone and networked mode control inputs
- L170 _public prototype_ `void ShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`
- L172 _public function_ `TUniquePtr<FPhysicsVehicleOutput>& PhysicsVehicleOutput()`
- L177 _public prototype_ `const FTransform& GetComponentTransform() const;`
- L180 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnModuleAddedNative, const FName&, int, int);` — native (fast, low overhead) versions
- L181 _public member_ `FOnModuleAddedNative OnModuleAddedNativeEvent;`
- L183 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnModuleRemovedNative, const FName&, int, int);`
- L184 _public member_ `FOnModuleRemovedNative OnModuleRemovedNativeEvent;`
- L187 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnModuleAdded, const FName&, SimType, int, Guid, int, TreeIndex);` — standard events
- L189 _public member_ `FOnModuleAdded OnModuleAddedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Events")`
- L191 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnModuleRemoved, const FName&, SimType, int, Guid, int, TreeIndex);`
- L193 _public member_ `FOnModuleRemoved OnModuleRemovedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Events")`
- L197 _public member_ `float LinearDamping;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")` — Use to naturally decelerate linear velocity of objects
- L201 _public member_ `float AngularDamping;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")` — Use to naturally decelerate angular velocity of objects
- L204 _public member_ `struct FCollisionResponseContainer SuspensionTraceCollisionResponses;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")`
- L208 _public member_ `TEnumAsByte<ECollisionChannel> SuspensionCollisionChannel;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")` — Collision channel to use for the suspension trace.
- L211 _public member_ `bool bSuspensionTraceComplex;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")`
- L215 _public member_ `ETraceType TraceType;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")` — Wheel suspension trace type, defaults to ray trace
- L218 _public member_ `bool bKeepVehicleAwake;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")`
- L222 _public prototype_ `void AddComponentToSimulation(UPrimitiveComponent* Component, const TArray<FClusterUnionBoneData>& BonesData, const TArray<FClusterUnionBoneData>& RemovedBoneIDs, bool bIsNew);` — `UFUNCTION()` — Adds any associated simulation components to the ModularVehicleSimulation
- L226 _public prototype_ `void RemoveComponentFromSimulation(UPrimitiveComponent* Component, const TArray<FClusterUnionBoneData>& RemovedBonesData);` — `UFUNCTION()` — Removes any associated simulation components from the ModularVehicleSimulation
- L229 _public prototype_ `void SetLocallyControlled(bool bLocallyControlledIn);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L232 _public member_ `TSubclassOf<UVehicleInputProducerBase> InputProducerClass;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")`
- L235 _public member_ `EModuleInputQuantizationType InputQuantizationType = EModuleInputQuantizationType::Default_16Bits;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")`
- L238 _public prototype_ `virtual void OnModuleInitialized(const FName& SimType, int Guid, int TreeIndex);` — `UFUNCTION()`
- L241 _public prototype_ `virtual void OnModuleRemoved(const FName& SimType, int Guid, int TreeIndex);` — `UFUNCTION()`
- L247 _public prototype_ `void SetInput(const FName& Name, const bool Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);` — CONTROLS void SetInput(const FName& Name, const FModuleInputValue& Value); Control inputs are automatically quantized for networking
- L248 _public prototype_ `void SetInput(const FName& Name, const int32 Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);`
- L249 _public prototype_ `void SetInput(const FName& Name, const double Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);`
- L250 _public prototype_ `void SetInput(const FName& Name, const FVector2D& Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);`
- L251 _public prototype_ `void SetInput(const FName& Name, const FVector& Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);`
- L254 _public prototype_ `void SetState(const FName& Name, const bool Value);` — The state inputs are not automatically quantized
- L255 _public prototype_ `void SetState(const FName& Name, const int32 Value);`
- L256 _public prototype_ `void SetState(const FName& Name, const double Value);`
- L257 _public prototype_ `void SetState(const FName& Name, const FVector2D& Value);`
- L258 _public prototype_ `void SetState(const FName& Name, const FVector& Value);`
- L260 _public prototype_ `void SetupInputConfiguration();`
- L264 _public prototype_ `void SetInputProducerClass(TSubclassOf<UVehicleInputProducerBase> InInputProducerClass, bool bForceNewInstance = false);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")` — Sets the input producer class and creates an input producer if one doesn't exist, or if forced to create an instance with the new class.
- L266 _public function_ `TObjectPtr<UVehicleInputProducerBase> GetInputProducer()`
- L269 _public prototype_ `void SetInputBool(const FName Name, const bool Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L272 _public prototype_ `void SetInputInteger(const FName Name, const int32 Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L275 _public prototype_ `void SetInputAxis1D(const FName Name, const double Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L278 _public prototype_ `void SetInputAxis2D(const FName Name, const FVector2D Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L281 _public prototype_ `void SetInputAxis3D(const FName Name, const FVector Value, EModuleInputBufferActionType BufferAction = EModuleInputBufferActionType::Override);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L285 _public prototype_ `void SetGearInput(int32 Gear);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")` — Set the gear directly
- L288 _public prototype_ `int32 GetCurrentGear();` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L291 _public prototype_ `bool IsReversing();` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L294 _public prototype_ `void AddActorsToIgnore(TArray<AActor*>& ActorsIn);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L297 _public prototype_ `void RemoveActorsToIgnore(TArray<AActor*>& ActorsIn);` — `UFUNCTION(BlueprintCallable, Category = "Game|Components|ModularVehicle")`
- L301 _public member_ `bool bRequiresControllerForInputs;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")` — Bypass the need for a controller in order for the controls to be processed.
- L305 _public member_ `bool bAutoAddComponentsFromWorld;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")` — Grab nearby components and add them to the cluster union representing the vehicle
- L309 _public member_ `FVector AutoAddOverlappingBoxSize;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle", meta = (EditCondition = "bAutoAddComponentsToCluster"))` — The size of the overlap box testing for nearby components in the world
- L312 _public member_ `int32 DelayClusteringCount;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle", meta = (EditCondition = "bAutoAddComponentsToCluster"))`
- L316 _public member_ `TMap<TObjectPtr<USceneComponent>, FVehicleComponentData> ComponentToPhysicsObjects;` — `UPROPERTY()` — Map simulation component to our vehicle setup data
- L319 _public member_ `TMap<int, TWeakObjectPtr<USceneComponent>> PhysicsGuidToComponent;` — Map physics sim GUID to actor component
- L321 _public member_ `UClusterUnionComponent* ClusterUnionComponent;`
- L324 _public function_ `void SetWheelTraceAllChannels(ECollisionResponse NewResponse)` — Set all channels to the specified response - for wheel raycasts
- L330 _public function_ `void SetWheelTraceResponseToChannel(ECollisionChannel Channel, ECollisionResponse NewResponse)` — Set the response of this body to the supplied settings - for wheel raycasts
- L335 _public function_ `TArray<FModuleAnimationSetup>& AccessModuleAnimationSetups()`
- L336 _public function_ `const TArray<FModuleAnimationSetup>& GetModuleAnimationSetups() const`
- L338 _public prototype_ `const Chaos::FSimOutputData* GetOutputData(int ModuleGuid);`
- L340 _public function_ `void SetPhysicsProxy(IPhysicsProxyBase* PhysicsProxy)`
- L341 _public function_ `void SetPhysicsProxyIfNotAlreadySpecified(IPhysicsProxyBase* PhysicsProxy)`
- L351 _protected prototype_ `void CreateVehicleSim();`
- L352 _protected prototype_ `void DestroyVehicleSim();`
- L353 _protected prototype_ `void UpdatePhysicalProperties();`
- L354 _protected prototype_ `void AddOverlappingComponentsToCluster();`
- L355 _protected prototype_ `void AddComponentToCluster(USceneComponent* Component);`
- L356 _protected prototype_ `bool AddComponentsFromOwnedActor();`
- L357 _protected prototype_ `void SetupSkeletalAnimationStructure();`
- L358 _protected prototype_ `void UpdateNonSkeletalAnimations();`
- L359 _protected prototype_ `void AssimilateComponentInputs(TArray<FModuleInputSetup>& OutCombinedInputs);`
- L360 _protected prototype_ `void CacheRootPhysicsObject(IPhysicsProxyBase* Proxy);`
- L362 _protected prototype_ `void AddSimulationComponentsFromOwnedActor();` — This version does not require cluster unions or geometry collections as parent components
- L364 _protected prototype_ `virtual void AddComponentToSimulationImpl(UPrimitiveComponent* Component, const TArray<FClusterUnionBoneData>& BonesData, const TArray<FClusterUnionBoneData>& RemovedBoneIDs, bool bIsNew);`
- L365 _protected prototype_ `virtual void RemoveComponentFromSimulationImpl(UPrimitiveComponent* Component, const TArray<FClusterUnionBoneData>& RemovedBonesData);`
- L367 _protected prototype_ `void ActionTreeUpdates(Chaos::FSimTreeUpdates* NextTreeUpdates);`
- L369 _protected prototype_ `void SetCurrentAsyncDataInternal(FChaosSimModuleManagerAsyncOutput* CurOutput, FChaosSimModuleManagerAsyncOutput* NextOutput, float Alpha, int32 VehicleManagerTimestamp);`
- L370 _protected prototype_ `int32 FindParentsLastSimComponent(const USceneComponent* AttachedComponent);`
- L372 _protected prototype_ `IPhysicsProxyBase* GetPhysicsProxy() const;`
- L373 _protected prototype_ `int GenerateNewGuid();`
- L375 _protected prototype_ `int32 FindComponentAddOrder(USceneComponent* InComponent);`
- L376 _protected prototype_ `void CreateOrUpdateComponentAddOrder(USceneComponent* InComponent, int32 InComponentAddOrder);`
- L377 _protected prototype_ `bool FindAndRemoveNextPendingUpdate(int32 NextIndex, Chaos::FSimTreeUpdates* OutData);`
- L379 _protected prototype_ `void BroadcastModuleAddedEvent(const FName& SimType, int Guid, int TreeIndex);`
- L380 _protected prototype_ `void BroadcastModuleRemovedEvent(const FName& SimType, int Guid, int TreeIndex);`
- L382 _protected prototype_ `Chaos::FSimOutputData* FindModuleOutputFromGuid(const FPhysicsVehicleOutput& OutputContainer, int Guid) const;`
- L386 _protected member_ `FModularReplicatedState ReplicatedState;` — `UPROPERTY(Transient, Replicated)` — replicated state of vehicle
- L390 _protected member_ `int32 GearInput;` — `UPROPERTY(Transient)` — latest gear selected
- L394 _protected member_ `int32 CurrentGear;` — `UPROPERTY(Transient)` — The currently selected gear
- L398 _protected member_ `float EngineRPM;` — `UPROPERTY(Transient)` — The engine RPM
- L402 _protected member_ `float EngineTorque;` — `UPROPERTY(Transient)` — The engine Torque
- L405 _protected member_ `TObjectPtr<UNetworkPhysicsComponent> NetworkPhysicsComponent = nullptr;` — `UPROPERTY()`
- L410 _public member_ `TArray<FModuleInputSetup> InputConfig;` — `UPROPERTY(EditAnywhere, Category = VehicleInput, meta=(TitleProperty="{Name} | {Type}"))`
- L413 _public member_ `TArray<FModuleInputSetup> StateInputConfiguration;` — `UPROPERTY(EditAnywhere, Category = VehicleState, meta=(TitleProperty="{Name} | {Type}"))`
- L416 _public member_ `TEnumAsByte<ESimTreeProcessingOrder> TreeProcessingOrder = ESimTreeProcessingOrder::LeafFirst;` — `UPROPERTY(EditAnywhere, Category = "Game|Components|ModularVehicle")`
- L419 _public member_ `TArray<FConstructionData> ConstructionDatas;` — `UPROPERTY(Transient, Replicated)`
- L423 _public prototype_ `void ServerUpdateState(const FModuleInputContainer& InputsIn, bool KeepAwake);` — `UFUNCTION(reliable, server, WithValidation)` — Pass current state to server
- L425 _public prototype_ `void AddInput(FModuleInputSetup InputSetup);`
- L427 _public prototype_ `void LogInputSetup();`
- L429 _public prototype_ `int AddSimModule(Chaos::ISimulationModuleBase* NewModule, const FTransform& ComponentTransform, int ParentIndex, int TransformIndex);`
- L430 _public prototype_ `void RemoveSimModule(int ModuleGuid);`
- L431 _public prototype_ `void FinalizeModuleUpdates();`
- L433 _public member_ `Chaos::FSimTreeUpdates StoredTreeUpdates;`
- L435 _public member_ `TArray<AActor*> ActorsToIgnore;`
- L436 _public member_ `EChaosAsyncVehicleDataType CurAsyncType;`
- L437 _public member_ `FModularVehicleAsyncInput* CurAsyncInput;`
- L438 _public member_ `struct FModularVehicleAsyncOutput* CurAsyncOutput;`
- L439 _public member_ `struct FModularVehicleAsyncOutput* NextAsyncOutput;`
- L440 _public member_ `float OutputInterpAlpha;`
- L454 _public member_ `TUniquePtr<FPhysicsVehicleOutput> PVehicleOutput;`
- L455 _public member_ `TUniquePtr<FModularVehicleSimulation> VehicleSimulationPT;` — TUniquePtr<FPhysicsVehicleOutput> PVehicleOutput;	  physics simulation data output from the async physics thread
- L459 _private member_ `int NextTransformIndex = 0;` — is there a better way, getting from size of map/array?
- L460 _private member_ `UPrimitiveComponent* MyComponent = nullptr;`
- L462 _private member_ `bool bUsingNetworkPhysicsPrediction = false;`
- L463 _private member_ `float PrevSteeringInput = 0.0f;`
- L465 _private member_ `int32 LastComponentAddIndex = INDEX_NONE;`
- L466 _private member_ `TMap<TObjectKey<USceneComponent>, Chaos::FSimTreeUpdates> PendingTreeUpdates;`
- L468 _private member_ `int32 NextConstructionIndex = 0;`
- L470 _private member_ `int32 ClusteringCount = 0;`
- L472 _private member_ `bool bIsLocallyControlled;`
- L474 _private member_ `TArray<FModuleAnimationSetup> ModuleAnimationSetups;`
- L476 _private member_ `FInputNameMap InputNameMap;` — map input name to input container array index
- L479 _private member_ `TObjectPtr<UVehicleInputProducerBase> InputProducer = nullptr;` — `UPROPERTY(Transient)`
- L481 _private member_ `FModuleInputContainer InputsContainer;`
- L483 _private member_ `FInputNameMap StateNameMap;`
- L484 _private member_ `FModuleInputContainer StateInputContainer;`
- L486 _private member_ `Chaos::FPhysicsObjectHandle RootPhysicsObject = nullptr;`
- L487 _private member_ `mutable IPhysicsProxyBase* CachedPhysicsProxy = nullptr;`

#### struct `UModularVehicleBaseComponent::FAsyncOutputWrapper`  
`struct FAsyncOutputWrapper`  
_L442-452_
- L444 _public member_ `int32 Idx;`
- L445 _public member_ `int32 Timestamp;`
- L447 _public function_ `FAsyncOutputWrapper() : Idx(INDEX_NONE) , Timestamp(INDEX_NONE)`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogModularBase, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogModularBase, Log, All);`
- L25 _namespace_ `namespace Chaos`
- L180 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnModuleAddedNative, const FName&, int, int);` — native (fast, low overhead) versions
- L183 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnModuleRemovedNative, const FName&, int, int);`
- L187 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnModuleAdded, const FName&, SimType, int, Guid, int, TreeIndex);` — standard events
- L191 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnModuleRemoved, const FName&, SimType, int, Guid, int, TreeIndex);`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleBuilder.h` (Public)


#### class `FModularVehicleBuilder`  
`class FModularVehicleBuilder`  
_L9-15_
- L13 _public prototype_ `static void GenerateSimTree(UModularVehicleBaseComponent* ModularVehicle);`
- L14 _public prototype_ `static void FixupTreeLinks(TUniquePtr<Chaos::FSimModuleTree>& SimModuleTree);`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleClusterActor.h` (Public)


#### class `AModularVehicleClusterActor`  
`class AModularVehicleClusterActor: public AActor`  
_L16-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L22 _public function_ `UClusterUnionVehicleComponent* GetClusterUnionComponent() const` — `UFUNCTION()`
- L25 _public function_ `UModularVehicleBaseComponent* GetVehicleSimulationComponent() const` — `UFUNCTION()`
- L29 _public member_ `TObjectPtr<UClusterUnionVehicleComponent> ClusterUnionVehicleComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Vehicle, meta = (ExposeFunctionCategories = "Components|ModularVehicle", AllowPrivateAccess = "true"))` — VehicleSpecificClusterComponent
- L33 _public member_ `TObjectPtr<UModularVehicleBaseComponent> VehicleSimComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Vehicle, meta = (ExposeFunctionCategories = "Components|ModularVehicle", AllowPrivateAccess = "true"))` — ModularVehicleComponent

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleClusterPawn.h` (Public)


#### class `AModularVehicleClusterPawn`  
`class AModularVehicleClusterPawn: public APawn`  
_L14-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `APawn`
- L20 _public function_ `UClusterUnionVehicleComponent* GetClusterUnionComponent() const` — `UFUNCTION()`
- L23 _public function_ `UModularVehicleBaseComponent* GetVehicleSimulationComponent() const` — `UFUNCTION()`
- L27 _public member_ `TObjectPtr<UClusterUnionVehicleComponent> ClusterUnionVehicleComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Vehicle, meta = (ExposeFunctionCategories = "Components|ModularVehicle", AllowPrivateAccess = "true"))` — VehicleSpecificClusterComponent
- L31 _public member_ `TObjectPtr<UModularVehicleBaseComponent> VehicleSimComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Vehicle, meta = (ExposeFunctionCategories = "Components|ModularVehicle", AllowPrivateAccess = "true"))` — ModularVehicleComponent

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleDebug.h` (Public)


#### Free symbols / members of external scopes

- L9 _function_ `static bool WriteCustomReport(FString FileName, TArray<FString>& FileLines)`
- L44 _function_ `static bool WriteNetReport(bool IsServer, const FString& FileLine)`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleDefaultAsyncInput.h` (Public)


#### struct `FModularVehicleDefaultAsyncInput`  
`struct FModularVehicleDefaultAsyncInput : public FModularVehicleAsyncInput`  
_L9-25_
- inherits: `FModularVehicleAsyncInput`
- L11 _public member_ `mutable FCollisionQueryParams TraceParams;`
- L12 _public member_ `mutable FCollisionResponseContainer TraceCollisionResponse;`
- L14 _public prototype_ `FModularVehicleDefaultAsyncInput();`
- L16 _public prototype_ `virtual TUniquePtr<FModularVehicleAsyncOutput> Simulate(UWorld* World, const float DeltaSeconds, const float TotalSeconds, bool& bWakeOut) const override;`
- L17 _public prototype_ `virtual void ApplyDeferredForces() const override;`
- L19 _public function_ `void SetVehicle(UModularVehicleComponent* VehicleIn)`
- L20 _public function_ `UModularVehicleComponent* GetVehicle()`
- L24 _private member_ `UModularVehicleComponent* GCVehicle;`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleSimulationCU.h` (Public)


#### struct `FModularVehicleDebugParams`  
`struct FModularVehicleDebugParams`  
_L23-34_
- L25 _public member_ `bool ShowDebug = false;`
- L26 _public member_ `bool SuspensionRaycastsEnabled = true;`
- L27 _public member_ `bool ShowSuspensionRaycasts = false;`
- L28 _public member_ `bool ShowWheelData = false;`
- L29 _public member_ `bool ShowRaycastMaterial = false;`
- L30 _public member_ `bool ShowWheelCollisionNormal = false;`
- L32 _public member_ `bool DisableAnim = false;`
- L33 _public member_ `float FrictionOverride = 1.0f;`

#### class `FModularVehicleSimulation`  
`class FModularVehicleSimulation`  
_L45-142_
- L48 _public typedef_ `using FInputNameMap = FInputInterface::FInputNameMap;`
- L50 _public function_ `FModularVehicleSimulation(bool InUsingNetworkPhysicsPrediction, int8 InNetMode) : bUsingNetworkPhysicsPrediction(InUsingNetworkPhysicsPrediction) , NetMode(InNetMode)`
- L56 _public function_ `virtual ~FModularVehicleSimulation()`
- L61 _public prototype_ `void Initialize(TUniquePtr<Chaos::FSimModuleTree>& InSimModuleTree);`
- L62 _public prototype_ `void Terminate();`
- L64 _public function_ `void SetInputQuantizationType(EModuleInputQuantizationType InInputQuantizationType)`
- L70 _public function_ `void SetInputMappings(const FInputNameMap& InNameMap)`
- L76 _public function_ `void SetStateMappings(const FInputNameMap& InNameMap)`
- L82 _public function_ `void SetTestInputBuffer(TArray<FModuleInputContainer>& InTestInputBuffer, bool bInIsLoopBuffer, int32 InTestInputBufferStartFrame)`
- L90 _public prototype_ `void AppendTreeUpdates(Chaos::FSimTreeUpdates* InNextTreeUpdatesInternal);`
- L91 _public prototype_ `void ActionTreeUpdates();`
- L92 _public prototype_ `void GenerateReplicationStructure(FNetworkModularVehicleStates& State);`
- L94 _public prototype_ `void CacheRootParticle(IPhysicsProxyBase* Proxy);`
- L97 _public prototype_ `virtual void Simulate(UWorld* InWorld, float DeltaSeconds, const FModularVehicleAsyncInput& InputData, FModularVehicleAsyncOutput& OutputData, IPhysicsProxyBase* Proxy);` — Update called from Physics Thread
- L98 _public prototype_ `virtual void SimulateModuleTree(UWorld* InWorld, float DeltaSeconds, const FModularVehicleAsyncInput& InputData, FModularVehicleAsyncOutput& OutputData, IPhysicsProxyBase* Proxy);`
- L100 _public prototype_ `virtual void OnContactModification(Chaos::FCollisionContactModifier& Modifier, IPhysicsProxyBase* Proxy);`
- L102 _public prototype_ `void ApplyDeferredForces(IPhysicsProxyBase* Proxy);`
- L104 _public prototype_ `void PerformAdditionalSimWork(float DeltaSeconds, UWorld* InWorld, const FModularVehicleAsyncInput& InputData, IPhysicsProxyBase* Proxy, Chaos::FAllInputs& AllInputs);`
- L106 _public prototype_ `void FillOutputState(FModularVehicleAsyncOutput& Output);`
- L108 _public function_ `const TUniquePtr<Chaos::FSimModuleTree>& GetSimComponentTree() const`
- L113 _public function_ `TUniquePtr<Chaos::FSimModuleTree>& AccessSimComponentTree()`
- L117 _public member_ `TUniquePtr<Chaos::FSimModuleTree> SimModuleTree;`
- L118 _public member_ `Chaos::FAllInputs SimInputData;` — TUniquePtr<Chaos::FSimModuleTree> SimModuleTree;	  Simulation modules stored in tree structure
- L119 _public member_ `bool bUsingNetworkPhysicsPrediction;`
- L122 _public member_ `FModularVehicleInputs VehicleInputs;` — Current control inputs that is being used on the PT
- L123 _public member_ `EModuleInputQuantizationType InputQuantizationType = EModuleInputQuantizationType::Default_16Bits;`
- L124 _public member_ `FInputNameMap InputNameMap;`
- L125 _public member_ `FInputNameMap StateNameMap;`
- L126 _public member_ `FTransactionallySafeRWLock InputConfigurationLock;`
- L127 _public member_ `FTransactionallySafeRWLock TreeConfigurationLock;`
- L129 _public member_ `int8 NetMode;`
- L131 _public member_ `int32 TestInputBufferStartFrame = -1;`
- L132 _public member_ `bool bIsLoopingTestInputBuffer = false;`
- L133 _public function_ `bool ImplementsTestBuffer()`
- L134 _public function_ `bool ImplementsLoopingTestBuffer()`
- L135 _public member_ `TArray<FModuleInputContainer> TestInputBuffer;`
- L136 _public member_ `TArray<Chaos::FSimTreeUpdates> NextTreeUpdatesInternal;`
- L137 _public member_ `TArray<Chaos::FCreatedModule> NewlyCreatedModuleGuids;`
- L139 _public member_ `Chaos::FPBDRigidParticleHandle* RootParticle = nullptr;` — cached root particle
- L141 _public member_ `FModularVehicleSimulationCallback VehicleSimulationCallback;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogModularVehicleSim, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogModularVehicleSim, Log, All);`
- L36 _namespace_ `namespace Chaos`
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_EightParams(FModularVehicleSimulationCallback, FModularVehicleSimulation*, UWorld*, float, const FModularVehicleAsyncInput&, Chaos::FAllInputs&, IPhysicsProxyBase*, Chaos::FPBDRigidParticleHandle*, Chaos::FSimModuleTree*);`
- L43 _prototype_ `DECLARE_MULTICAST_DELEGATE_EightParams(FModularVehicleSimulationCallback, FModularVehicleSimulation*, UWorld*, float, const FModularVehicleAsyncInput&, Chaos::FAllInputs&, IPhysicsProxyBase*, Chaos::FPBDRigidParticleHandle*, Chaos::FSimModuleTree*);`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleSkeletalPawn.h` (Public)


#### class `AModularVehicleSkeletalPawn`  
`class AModularVehicleSkeletalPawn: public APawn`  
_L14-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `APawn`
- L20 _public function_ `USkeletalMeshComponent* GetSkeletalMeshComponent() const` — `UFUNCTION()`
- L23 _public function_ `UModularVehicleBaseComponent* GetVehicleSimulationComponent() const` — `UFUNCTION()`
- L27 _public member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Vehicle, meta = (ExposeFunctionCategories = "Components|ModularVehicle", AllowPrivateAccess = "true"))` — SkeletalMeshComponent root component
- L31 _public member_ `TObjectPtr<UModularVehicleBaseComponent> VehicleSimComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Vehicle, meta = (ExposeFunctionCategories = "Components|ModularVehicle", AllowPrivateAccess = "true"))` — ModularVehicleComponent

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModularVehicleSocket.h` (Public)


#### struct `FModularVehicleSocket`  
`struct FModularVehicleSocket`  
_L17-43_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public prototype_ `FModularVehicleSocket();`
- L27 _public member_ `FName SocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Socket Parameters")` — Defines a named attachment location on the Modular vehicle.
- L30 _public member_ `FVector RelativeLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Socket Parameters")`
- L33 _public member_ `FRotator RelativeRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Socket Parameters")`
- L35 _public prototype_ `FVector GetLocation(const class UClusterUnionVehicleComponent* Component) const;`
- L38 _public prototype_ `FTransform GetLocalTransform() const;` — returns FTransform of Socket local transform
- L41 _public prototype_ `FTransform GetTransform(const class UClusterUnionVehicleComponent* Component) const;` — Utility that returns the current transform for this socket.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/ModuleInputTokenStore.h` (Public)


#### struct `FModuleInputNetTokenData`  
`struct FModuleInputNetTokenData`  
_L12-39_
- reflection: `USTRUCT()`
- L16 _public member_ `TArray<uint8> Types;` — `UPROPERTY()`
- L18 _public member_ `TArray<bool> DecayValues;` — `UPROPERTY()`
- L22 _public function_ `uint64 GetUniqueKey() const`
- L29 _public function_ `void Init(const TArray<FModuleInputValue>& ModuleInputs)`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/SimModuleActor.h` (Public)


#### class `ASimModuleActor`  
`class ASimModuleActor : public AActor`  
_L14-31_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), hidecategories = (PlanarMovement, "Components|Movement|Planar", Activation, "Components|Activation"))`
- inherits: `AActor`
- L21 _public function_ `void TickSimulation(float DeltaTime)` — Game state callback
- L22 _public function_ `virtual void Tick(float DeltaSeconds) override`
- L25 _public member_ `TObjectPtr<UStaticMeshComponent> MeshComp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModularVehicle)`
- L29 _public member_ `TObjectPtr<UVehicleSimBaseComponent> SimComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModularVehicle)` — Simulation Component

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/SuspensionSimModule.h` (Public)


#### struct `FSuspensionSimModuleData`  
`struct FSuspensionSimModuleData : public Chaos::FModuleNetData , public Chaos::TSimulationModuleTypeable<FSuspensionSimModule,FSuspensionSimModuleData>`  
_L19-47_
- inherits: `Chaos::FModuleNetData,Chaos::TSimulationModuleTypeable<FSuspensionSimModule,FSuspensionSimModuleData>`
- L24 _public function_ `FSuspensionSimModuleData(int NodeArrayIndex, const FString& InDebugString) : Chaos::FModuleNetData(NodeArrayIndex, InDebugString)`
- L29 _public prototype_ `virtual void FillSimState(Chaos::ISimulationModuleBase* SimModule) override;`
- L31 _public prototype_ `virtual void FillNetState(const Chaos::ISimulationModuleBase* SimModule) override;`
- L33 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L39 _public prototype_ `virtual void Lerp(const float LerpFactor, const FModuleNetData& Min, const FModuleNetData& Max) override;`
- L42 _public prototype_ `virtual FString ToString() const override;`
- L45 _public member_ `float SpringDisplacement = 0.0f;`
- L46 _public member_ `float LastDisplacement = 0.0f;`

#### struct `FSuspensionOutputData`  
`struct FSuspensionOutputData : public Chaos::FSimOutputData , public Chaos::TSimulationModuleTypeable<FSuspensionSimModule,FSuspensionOutputData>`  
_L49-76_
- inherits: `Chaos::FSimOutputData,Chaos::TSimulationModuleTypeable<FSuspensionSimModule,FSuspensionOutputData>`
- L53 _public function_ `virtual FSimOutputData* MakeNewData() override`
- L54 _public function_ `static FSimOutputData* MakeNew()`
- L56 _public prototype_ `virtual void FillOutputState(const Chaos::ISimulationModuleBase* SimModule) override;`
- L57 _public prototype_ `virtual void Lerp(const FSimOutputData& InCurrent, const Chaos::FSimOutputData& InNext, float Alpha) override;`
- L59 _public prototype_ `virtual void GetFinalAnimDataGameThread(const FTransform& NewTransform, Chaos::FSimModuleAnimationData& AnimDataOut) override;`
- L62 _public prototype_ `virtual FString ToString() override;`
- L65 _public member_ `float SpringDisplacement = 0.0f;`
- L66 _public member_ `FVector SpringDisplacementVector = FVector::ZeroVector;`
- L67 _public member_ `float SpringSpeed = 0.0f;`
- L68 _public member_ `FVector ImpactNormal = FVector(0.0f,0.0f,1.0f);`
- L70 _public member_ `FVector ImpactPosition = FVector::ZeroVector;`
- L71 _public member_ `FVector ModuleLocalPosition = FVector::ZeroVector;`
- L72 _public member_ `FVector LocalSuspensionAxis = FVector::ZeroVector;`
- L73 _public member_ `float MaxRaise = 0.0f;`
- L74 _public member_ `float MaxDrop = 0.0f;`
- L75 _public member_ `bool bWheelHit = false;`

#### struct `FSuspensionSettings`  
`struct FSuspensionSettings`  
_L78-105_
- L80 _public function_ `FSuspensionSettings() : SuspensionAxis(FVector(0.f, 0.f, -1.f)) , RestOffset(FVector::ZeroVector) , MaxRaise(5.f) , MaxDrop(5.f) , MaxLength(0.f) , SpringRate(1.f) , SpringPreload(0.5f) , SpringDamping(0.9f) , SuspensionForceEffect(100.0f)`
- L94 _public member_ `FVector SuspensionAxis;` — local axis, direction of suspension force raycast traces
- L95 _public member_ `FVector RestOffset;`
- L96 _public member_ `float MaxRaise;` — distance [cm]
- L97 _public member_ `float MaxDrop;` — distance [cm]
- L98 _public member_ `float MaxLength;` — distance [cm]
- L100 _public member_ `float SpringRate;` — spring constant
- L101 _public member_ `float SpringPreload;` — Amount of Spring force (independent spring movement)
- L102 _public member_ `float SpringDamping;` — limit compression/rebound speed
- L104 _public member_ `float SuspensionForceEffect;` — force that presses the wheels into the ground - producing grip

#### class `FSuspensionFactory`  
`class FSuspensionFactory : public Chaos::IFactoryModule`  
_L108-120_
- inherits: `Chaos::IFactoryModule`
- L111 _public function_ `virtual TSharedPtr<Chaos::FModuleNetData> GenerateNetData(const int32 SimArrayIndex) const override`

#### class `FSuspensionSimModule`  
`class FSuspensionSimModule : public Chaos::FSuspensionBaseInterface , public Chaos::TSimModuleSettings<FSuspensionSettings> , public Chaos::TSimulationModuleTypeable<FSuspensionSimModule>`  
_L122-179_
- inherits: `Chaos::FSuspensionBaseInterface,Chaos::TSimModuleSettings<FSuspensionSettings>,Chaos::TSimulationModuleTypeable<FSuspensionSimModule>`
- L131 _public prototype_ `DEFINE_CHAOSSIMTYPENAME(FSuspensionSimModule);`
- L132 _public prototype_ `FSuspensionSimModule(const FSuspensionSettings& Settings);`
- L134 _public function_ `virtual TSharedPtr<Chaos::FModuleNetData> GenerateNetData(const int32 SimArrayIndex) const override`
- L146 _public function_ `virtual Chaos::FSimOutputData* GenerateOutputData() const override`
- L151 _public function_ `virtual const FString GetDebugName() const`
- L153 _public function_ `virtual float GetMaxSpringLength() const override`
- L154 _public prototype_ `virtual float GetSpringLength() const override;`
- L155 _public prototype_ `virtual void SetSpringLength(float InLength, float WheelRadius) override;`
- L156 _public prototype_ `virtual void GetWorldTraceEndpoints(float DeltaSeconds, const FTransform& BodyTransform, const FVector& Velocity, float WheelRadius, Chaos::FSpringTrace& OutTrace) const override;`
- L157 _public prototype_ `virtual void OnConstruction_External(const Chaos::FPhysicsObjectHandle& PhysicsObject) override;`
- L158 _public prototype_ `virtual void OnTermination_External() override;`
- L160 _public prototype_ `virtual void Simulate(float DeltaTime, const Chaos::FAllInputs& Inputs, Chaos::FSimModuleTree& VehicleModuleSystem) override;`
- L162 _public prototype_ `virtual void Animate() override;`
- L164 _public function_ `const FVector& GetRestLocation() const`
- L166 _public prototype_ `void UpdateConstraint();`
- L169 _protected prototype_ `void CreateConstraint(const Chaos::FPhysicsObjectHandle& PhysicsObject);`
- L170 _protected prototype_ `void DestroyConstraint();`
- L174 _private member_ `float SpringDisplacement = 0.0f;`
- L175 _private member_ `float LastDisplacement = 0.0f;`
- L176 _private member_ `float SpringSpeed = 0.0f;`
- L177 _private member_ `float CurrentTimeDilation = 1.0f;`
- L178 _private member_ `FPhysicsConstraintHandle ConstraintHandle;`

#### class `FSuspensionSimFactory`  
`class FSuspensionSimFactory : public Chaos::FSimFactoryModule<FSuspensionSimModuleData> , public Chaos::TSimulationModuleTypeable<FSuspensionSimModule, FSuspensionSimFactory> , public Chaos::TSimFactoryAutoRegister<FSuspensionSimFactory>`  
_L182-190_
- inherits: `Chaos::FSimFactoryModule<FSuspensionSimModuleData>,Chaos::TSimulationModuleTypeable<FSuspensionSimModule,FSuspensionSimFactory>,Chaos::TSimFactoryAutoRegister<FSuspensionSimFactory>`
- L189 _public function_ `FSuspensionSimFactory() : FSimFactoryModule(TEXT("Susp`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`
- L12 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimAerofoilComponent.h` (Public)


#### enum `EModuleAerofoilType`  
`enum class EModuleAerofoilType : uint8`  
_L15-21_
- reflection: `UENUM()`
- L17 _public enumerator_ `Fixed = 0`
- L18 _public enumerator_ `Wing` — affected by Roll input
- L19 _public enumerator_ `Rudder` — affected by steering/yaw input
- L20 _public enumerator_ `Elevator` — affected by Pitch input

#### class `UVehicleSimAerofoilComponent`  
`class UVehicleSimAerofoilComponent : public UVehicleSimBaseComponent`  
_L24-69_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), meta = (BlueprintSpawnableComponent), hidecategories = (Object, Tick, Replication, Cooking, Activation, LOD))`
- inherits: `UVehicleSimBaseComponent`
- L29 _public prototype_ `UVehicleSimAerofoilComponent();`
- L30 _public prototype_ `virtual ~UVehicleSimAerofoilComponent() = default;`
- L33 _public member_ `FVector Offset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L36 _public member_ `FVector ForceAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L39 _public member_ `FVector ControlRotationAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L42 _public member_ `float Area;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L45 _public member_ `float Camber;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L48 _public member_ `float MaxControlAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L51 _public member_ `float StallAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L54 _public member_ `EModuleAerofoilType Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L57 _public member_ `float LiftMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L60 _public member_ `float DragMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L63 _public member_ `float AnimationMagnitudeMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L65 _public function_ `virtual ESimModuleType GetModuleType() const override`
- L67 _public prototype_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimBaseComponent.h` (Public)


#### enum `ESimModuleType`  
`enum class ESimModuleType : uint8`  
_L22-40_
- reflection: `UENUM()`
- L24 _public enumerator_ `Undefined = 0`
- L25 _public enumerator_ `Chassis` — no simulation effect
- L26 _public enumerator_ `Thruster` — applies force
- L27 _public enumerator_ `Aerofoil` — applied drag and lift forces
- L28 _public enumerator_ `Wheel` — a wheel will simply roll if it has no power source
- L29 _public enumerator_ `Suspension` — associated with a wheel
- L30 _public enumerator_ `Axle` — connects more than one wheel
- L31 _public enumerator_ `Transmission` — gears - torque multiplier
- L32 _public enumerator_ `Engine` — (torque curve required) power source generates torque for wheel, axle, transmission, clutch
- L33 _public enumerator_ `Motor` — (electric?, no torque curve required?) power source generates torque for wheel, axle, transmission, clutch
- L34 _public enumerator_ `Clutch` — limits the amount of torque transferred between source and destination allowing for different rotation speeds of connected axles
- L35 _public enumerator_ `Wing` — lift and controls aircraft roll
- L36 _public enumerator_ `Rudder` — controls aircraft yaw
- L37 _public enumerator_ `Elevator` — controls aircraft pitch
- L38 _public enumerator_ `Propeller` — generates thrust when connected to a motor/engine
- L39 _public enumerator_ `Balloon` — TODO: rename anti gravity??

#### class `UVehicleSimBaseComponentInterface`  
`class UVehicleSimBaseComponentInterface : public UInterface`  
_L44-47_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface used for shared functionality between types of base components.

#### class `IVehicleSimBaseComponentInterface`  
`class IVehicleSimBaseComponentInterface`  
_L49-69_
- L55 _public function_ `virtual ESimModuleType GetModuleType() const`
- L57 _public function_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const` — Caller takes ownership of pointer to new Sim Module.
- L58 _public function_ `virtual FName GetBoneName() const`
- L59 _public function_ `virtual const FVector& GetAnimationOffset() const`
- L60 _public function_ `virtual void SetAnimationEnabled(bool AnimationEnabledIn)`
- L61 _public function_ `virtual bool GetAnimationEnabled() const`
- L62 _public function_ `virtual TArray<FModuleInputSetup> GetInputConfig() const`
- L63 _public function_ `virtual int32 GetAnimationSetupIndex() const`
- L64 _public function_ `virtual void SetTreeIndex(const int32 NewValue)`
- L65 _public function_ `virtual int32 GetTreeIndex() const`
- L66 _public function_ `virtual void OnAdded()`
- L67 _public function_ `virtual void OnRemoved()`
- L68 _public function_ `virtual void OnOutputReady(const Chaos::FSimOutputData* OutputData)`

#### class `UVehicleSimBaseComponent`  
`class UVehicleSimBaseComponent : public UPrimitiveComponent , public IVehicleSimBaseComponentInterface`  
_L73-108_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UPrimitiveComponent,IVehicleSimBaseComponentInterface`
- desc: This if for sim components that need scene component properties along with rendering and collision.
- L82 _protected member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModularVehicle)`
- L85 _protected member_ `FVector AnimationOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModularVehicle)`
- L88 _protected member_ `bool bAnimationEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModularVehicle)`
- L91 _protected member_ `TArray<FModuleInputSetup> InputConfig;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)`
- L93 _protected member_ `int32 AnimationSetupIndex = INDEX_NONE;`
- L94 _protected member_ `int32 TreeIndex = INDEX_NONE;` — helper - since Component->GetAttachChildren doesn't contain any data
- L99 _public function_ `virtual FName GetBoneName() const override` — IVehicleSimBaseComponentInterface overrides
- L100 _public function_ `virtual const FVector& GetAnimationOffset() const override`
- L101 _public function_ `virtual void SetAnimationEnabled(bool AnimationEnabledIn) override`
- L102 _public function_ `virtual bool GetAnimationEnabled() const override`
- L103 _public function_ `virtual TArray<FModuleInputSetup> GetInputConfig() const override`
- L104 _public function_ `virtual int32 GetAnimationSetupIndex() const override`
- L105 _public prototype_ `virtual void SetTreeIndex(const int32 NewValue) override;`
- L106 _public function_ `virtual int32 GetTreeIndex() const override`

#### class `UVehicleSimBaseSceneComponent`  
`class UVehicleSimBaseSceneComponent : public USceneComponent , public IVehicleSimBaseComponentInterface`  
_L112-128_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `USceneComponent,IVehicleSimBaseComponentInterface`
- desc: This if for sim components that need transform and attachment, no rendering, no collision.
- L121 _protected member_ `TArray<FModuleInputSetup> InputConfig;` — `UPROPERTY(EditAnywhere, Category = VehicleInput)`
- L126 _public function_ `virtual TArray<FModuleInputSetup> GetInputConfig() const override` — IVehicleSimBaseComponentInterface overrides

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`
- L15 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimChassisComponent.h` (Public)


#### class `UVehicleSimChassisComponent`  
`class UVehicleSimChassisComponent : public UVehicleSimBaseComponent`  
_L14-43_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), meta = (BlueprintSpawnableComponent), hidecategories = (Object, Tick, Replication, Cooking, Activation, LOD))`
- inherits: `UVehicleSimBaseComponent`
- L19 _public prototype_ `UVehicleSimChassisComponent();`
- L20 _public prototype_ `virtual ~UVehicleSimChassisComponent() = default;`
- L23 _public member_ `float AreaMetresSquared;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L26 _public member_ `float DragCoefficient;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L29 _public member_ `float DensityOfMedium;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L32 _public member_ `float XAxisMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L35 _public member_ `float YAxisMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L38 _public member_ `float AngularDamping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L40 _public function_ `virtual ESimModuleType GetModuleType() const override`
- L42 _public prototype_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimClutchComponent.h` (Public)


#### class `UVehicleSimClutchComponent`  
`class UVehicleSimClutchComponent : public UVehicleSimBaseComponent`  
_L14-29_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), meta = (BlueprintSpawnableComponent), hidecategories = (Object, Tick, Replication, Cooking, Activation, LOD))`
- inherits: `UVehicleSimBaseComponent`
- L19 _public prototype_ `UVehicleSimClutchComponent();`
- L20 _public prototype_ `virtual ~UVehicleSimClutchComponent() = default;`
- L23 _public member_ `float ClutchStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L25 _public function_ `virtual ESimModuleType GetModuleType() const override`
- L27 _public prototype_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimComponentsInclude.h` (Public)
_(no declarations extracted)_

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimEngineComponent.h` (Public)


#### class `UVehicleSimEngineComponent`  
`class UVehicleSimEngineComponent : public UVehicleSimBaseComponent`  
_L15-46_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), meta = (BlueprintSpawnableComponent), hidecategories = (Object, Tick, Replication, Cooking, Activation, LOD))`
- inherits: `UVehicleSimBaseComponent`
- L20 _public prototype_ `UVehicleSimEngineComponent();`
- L21 _public prototype_ `virtual ~UVehicleSimEngineComponent() = default;`
- L24 _public member_ `FRuntimeFloatCurve TorqueCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L27 _public member_ `float MaxTorque;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — [N.m] The peak torque Y value in the normalized torque graph
- L30 _public member_ `int MaxRPM;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — [RPM] The absolute maximum RPM the engine can theoretically reach (last X value in the normalized torque graph)
- L33 _public member_ `int EngineIdleRPM;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — [RPM] The RPM at which the throttle sits when the car is not moving
- L36 _public member_ `float EngineBrakeEffect;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — [0..1] How much the engine slows the vehicle when the throttle is released
- L39 _public member_ `float EngineInertia;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — [Kg.m-2] How hard it is to turn the engine
- L41 _public function_ `virtual ESimModuleType GetModuleType() const override`
- L42 _public prototype_ `virtual void OnOutputReady(const Chaos::FSimOutputData* OutputData) override;`
- L44 _public prototype_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimSuspensionComponent.h` (Public)


#### class `UVehicleSimSuspensionComponent`  
`class UVehicleSimSuspensionComponent : public UVehicleSimBaseComponent`  
_L14-49_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), meta = (BlueprintSpawnableComponent), hidecategories = (Object, Replication, Cooking, Activation, LOD, Physics, Collision, AssetUserData, Event))`
- inherits: `UVehicleSimBaseComponent`
- L20 _public prototype_ `UVehicleSimSuspensionComponent();`
- L21 _public prototype_ `virtual ~UVehicleSimSuspensionComponent() = default;`
- L24 _public member_ `FVector SuspensionAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L27 _public member_ `float SuspensionMaxRaise;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L30 _public member_ `float SuspensionMaxDrop;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L33 _public member_ `float SpringRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L36 _public member_ `float SpringPreload;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L39 _public member_ `float SpringDamping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L42 _public member_ `float SuspensionForceEffect;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L47 _public function_ `virtual ESimModuleType GetModuleType() const override`
- L48 _public prototype_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimThrusterComponent.h` (Public)


#### class `UVehicleSimThrusterComponent`  
`class UVehicleSimThrusterComponent : public UVehicleSimBaseComponent`  
_L14-50_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), meta = (BlueprintSpawnableComponent), hidecategories = (Object, Tick, Replication, Cooking, Activation, LOD))`
- inherits: `UVehicleSimBaseComponent`
- L20 _public prototype_ `UVehicleSimThrusterComponent();`
- L21 _public prototype_ `virtual ~UVehicleSimThrusterComponent() = default;`
- L24 _public member_ `float MaxThrustForce;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L27 _public member_ `FVector ForceAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L30 _public member_ `FVector ForceOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L33 _public member_ `bool bSteeringEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L36 _public member_ `FVector SteeringAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L39 _public member_ `float MaxSteeringAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L42 _public member_ `float SteeringForceEffect;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L45 _public member_ `float BoostMultiplierEffect;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L47 _public function_ `virtual ESimModuleType GetModuleType() const override`
- L49 _public prototype_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimTransmissionComponent.h` (Public)


#### enum `EModuleTransType`  
`enum class EModuleTransType : uint8`  
_L14-18_
- reflection: `UENUM()`
- L16 _public enumerator_ `Manual = 0`
- L17 _public enumerator_ `Automatic`

#### class `UVehicleSimTransmissionComponent`  
`class UVehicleSimTransmissionComponent : public UVehicleSimBaseComponent`  
_L22-75_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), meta = (BlueprintSpawnableComponent), hidecategories = (Object, Tick, Replication, Cooking, Activation, LOD))`
- inherits: `UVehicleSimBaseComponent`
- L27 _public prototype_ `UVehicleSimTransmissionComponent();`
- L28 _public prototype_ `virtual ~UVehicleSimTransmissionComponent() = default;`
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGearChangeNative, int, int);` — native (fast, low overhead) versions
- L32 _public member_ `FOnGearChangeNative OnGearChangeNativeEvent;`
- L35 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGearChange, int, Guid, int, CurrentGear);` — standard events
- L37 _public member_ `FOnGearChange OnGearChangeEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Events")`
- L41 _public member_ `TArray<float> ForwardRatios;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L44 _public member_ `TArray<float> ReverseRatios;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L47 _public member_ `float FinalDriveRatio;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L50 _public member_ `int ChangeUpRPM;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L53 _public member_ `int ChangeDownRPM;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L56 _public member_ `float GearChangeTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L59 _public member_ `float GearHysteresisTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L62 _public member_ `float TransmissionEfficiency;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L65 _public member_ `EModuleTransType TransmissionType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L68 _public member_ `bool AutoReverse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L70 _public function_ `virtual ESimModuleType GetModuleType() const override`
- L71 _public prototype_ `virtual void OnOutputReady(const Chaos::FSimOutputData* OutputData) override;`
- L73 _public prototype_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGearChangeNative, int, int);` — native (fast, low overhead) versions
- L35 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGearChange, int, Guid, int, CurrentGear);` — standard events

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle/VehicleSimWheelComponent.h` (Public)


#### enum `EWheelAxisType`  
`enum class EWheelAxisType : uint8`  
_L13-17_
- reflection: `UENUM()`
- L15 _public enumerator_ `X = 0` — X forwards
- L16 _public enumerator_ `Y` — Y forwards

#### class `UVehicleSimWheelComponent`  
`class UVehicleSimWheelComponent : public UVehicleSimBaseComponent`  
_L21-104_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (ModularVehicle), meta = (BlueprintSpawnableComponent), hidecategories = (Object, Replication, Cooking, Activation, LOD, Physics, Collision, AssetUserData, Event))`
- inherits: `UVehicleSimBaseComponent`
- L27 _public prototype_ `UVehicleSimWheelComponent();`
- L28 _public prototype_ `virtual ~UVehicleSimWheelComponent() = default;`
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWheelTouchChangeNative, int, bool);` — native (fast, low overhead) versions
- L32 _public member_ `FOnWheelTouchChangeNative OnWheelTouchChangeNativeEvent;`
- L35 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWheelTouchChange, int, Guid, bool, IsInContact);` — standard events
- L37 _public member_ `FOnWheelTouchChange OnWheelTouchChangeEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Events")`
- L44 _public member_ `float WheelRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — [cm]
- L47 _public member_ `float WheelWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — [cm]
- L50 _public member_ `float WheelInertia;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L54 _public member_ `float FrictionMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — grip and turning related
- L57 _public member_ `float CorneringStiffness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L60 _public member_ `float SlipAngleLimit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L67 _public member_ `float MaxBrakeTorque;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — - Braking ------------------------------------------------------
- L71 _public member_ `bool bHandbrakeEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — Handbrake
- L74 _public member_ `float HandbrakeTorque;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, meta = (EditCondition = "bHandbrakeEnabled"))`
- L78 _public member_ `bool bSteeringEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)` — - Steering -----------------------------------------------------
- L81 _public member_ `float MaxSteeringAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes, meta = (EditCondition = "bSteeringEnabled"))`
- L86 _public member_ `bool bABSEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L89 _public member_ `bool bTractionControlEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L92 _public member_ `EWheelAxisType AxisType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L95 _public member_ `FVector ForceOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L98 _public member_ `bool ReverseDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attributes)`
- L100 _public function_ `virtual ESimModuleType GetModuleType() const override`
- L101 _public prototype_ `virtual void OnOutputReady(const Chaos::FSimOutputData* OutputData) override;`
- L103 _public prototype_ `virtual Chaos::ISimulationModuleBase* CreateNewCoreModule() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMODULARVEHICLEENGINE_API`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWheelTouchChangeNative, int, bool);` — native (fast, low overhead) versions
- L35 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWheelTouchChange, int, Guid, bool, IsInContact);` — standard events
