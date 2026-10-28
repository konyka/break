# Plugins / SpatialReadiness

- module root: `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness`
- headers: 12; symbols: 156
- symbol kinds: class=5, delegate=6, enum=2, enumerator=6, externvar=1, function=8, macro=2, member=27, namespace=1, prototype=86, struct=6, typedef=6
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Private/SpatialReadiness/SpatialReadinessAPIDelegates.h` (Private)


#### struct `FSpatialReadinessAPIDelegates`  
`struct FSpatialReadinessAPIDelegates final`  
_L8-19_
- L11 _public prototype_ `FSpatialReadinessAPIDelegates( FAddUnreadyVolume_Function AddUnreadyVolume, FRemoveUnreadyVolume_Function RemoveUnreadyVolume);` — Constructor which binds TFunctions
- L15 _public prototype_ `~FSpatialReadinessAPIDelegates() = default;`
- L17 _public member_ `FAddUnreadyVolume_Delegate AddUnreadyVolumeDelegate;`
- L18 _public member_ `FRemoveUnreadyVolume_Delegate RemoveUnreadyVolumeDelegate;`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessAPI.h` (Public)


#### class `FSpatialReadinessAPI`  
`class FSpatialReadinessAPI final`  
_L12-37_
- L17 _public prototype_ `FSpatialReadinessAPI( FAddUnreadyVolume_Function AddUnreadyVolume, FRemoveUnreadyVolume_Function RemoveUnreadyVolume);` — This constructor binds TFunctions to the internal add and remove delegates
- L26 _public prototype_ `template <typename ObjectT> FSpatialReadinessAPI(ObjectT* Object, TAddUnreadyVolume_Member<ObjectT> AddUnreadyVolume, TRemoveUnreadyVolume_Member<ObjectT> RemoveUnreadyVolume);` — This constructor binds member functions to the internal add and remove delegates. Please be sure that this API object will not outlive the object to whose members its delegates are bound after this construction!
- L30 _public prototype_ `~FSpatialReadinessAPI();`
- L32 _public prototype_ `FSpatialReadinessVolume CreateVolume(const FBox& Bounds, const FString& Description);`
- L36 _private member_ `TSharedPtr<FSpatialReadinessAPIDelegates> Delegates;`
- L40 _function_ `template <typename ObjectT> FSpatialReadinessAPI::FSpatialReadinessAPI(ObjectT* Object, TAddUnreadyVolume_Member<ObjectT> AddUnreadyVolume, TRemoveUnreadyVolume_Member<ObjectT> RemoveUnreadyVolume) : FSpatialReadinessAPI( [Object, AddUnreadyVolume] (const FBox& Bounds, const FString& Desc) -> int32 { return (Object->*AddUnreadyVolume)(Bounds, Desc); }, [Object, RemoveUnreadyVolume] (int32 Index) -> void { (Object->*RemoveUnreadyVolume)(Index); })`

#### Free symbols / members of external scopes

- L45 _function_ ``

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessDebug.h` (Public)


#### Free symbols / members of external scopes

- L6 _externvar_ `extern TAutoConsoleVariable<bool> CVarSpatialReadinessDebugDraw;`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessDefines.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define WITH_SPATIAL_READINESS_DESCRIPTIONS (!(UE_BUILD_SHIPPING || UE_BUILD_TEST))`
- L11 _macro_ `#define WITH_SPATIAL_READINESS_CVD (!(UE_BUILD_SHIPPING || UE_BUILD_TEST))`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessLog.h` (Public)


#### Free symbols / members of external scopes

- L5 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpatialReadiness, Log, All);`
- L5 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpatialReadiness, Log, All);`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessModule.h` (Public)


#### class `FSpatialReadinessModule`  
`class FSpatialReadinessModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessSignatures.h` (Public)


#### enum `EUnreadyVolumeAction`  
`enum class EUnreadyVolumeAction : uint8`  
_L9-9_
- reflection: `UENUM()`
- desc: Declare external delegate types
- L9 _public enumerator_ `enum class EUnreadyVolumeAction : uint8 { Added, Removed }; DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUnreadyVolumeChanged_Delegate, const FBox&, const FString&, EUnreadyVolumeAction); DECLARE_DELEGATE_RetVal_TwoParams(int32, FAddUnreadyVolume_Delegate, const FBox&, const FString&); DECLARE_DELEGATE_OneParam(FRemoveUnreadyVolume_Delegate, int32);`
- L9 _public enumerator_ `enum class EUnreadyVolumeAction : uint8 { Added, Removed }; DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUnreadyVolumeChanged_Delegate, const FBox&, const FString&, EUnreadyVolumeAction); DECLARE_DELEGATE_RetVal_TwoParams(int32, FAddUnreadyVolume_Delegate, const FBox&, const FString&); DECLARE_DELEGATE_OneParam(FRemoveUnreadyVolume_Delegate, int32);`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUnreadyVolumeChanged_Delegate, const FBox&, const FString&, EUnreadyVolumeAction);`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUnreadyVolumeChanged_Delegate, const FBox&, const FString&, EUnreadyVolumeAction);`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(int32, FAddUnreadyVolume_Delegate, const FBox&, const FString&);` — Declare internal delegate types
- L13 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(int32, FAddUnreadyVolume_Delegate, const FBox&, const FString&);` — Declare internal delegate types
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FRemoveUnreadyVolume_Delegate, int32);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FRemoveUnreadyVolume_Delegate, int32);`
- L17 _typedef_ `using FAddUnreadyVolume_Function = TFunction<int32(const FBox&, const FString&)>;` — Declare TFunction types which can be bound to the delegates
- L18 _typedef_ `using FRemoveUnreadyVolume_Function = TFunction<void(int32)>;`
- L22 _typedef_ `template <typename ObjectT> using TAddUnreadyVolume_Member = int32(ObjectT::*)(const FBox&, const FString&);` — Declare member function types which can be bound to delegates
- L24 _typedef_ `template <typename ObjectT> using TRemoveUnreadyVolume_Member = void(ObjectT::*)(int32);`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessSimCallback.h` (Public)


#### enum `ESpatialReadinessSimCallback_MidPhaseStrategy`  
`enum ESpatialReadinessSimCallback_MidPhaseStrategy`  
_L19-25_
- L21 _public enumerator_ `PrioritizeUnreadyVolumes = 0`
- L22 _public enumerator_ `PrioritizeMidPhases`
- L23 _public enumerator_ `Grid`
- L24 _public enumerator_ `COUNT`

#### struct `FUnreadyVolumeData_GT`  
`struct FUnreadyVolumeData_GT`  
_L28-42_
- L30 _public function_ `FUnreadyVolumeData_GT(Chaos::FSingleParticlePhysicsProxy* InProxy, const FBox& InBounds, const FString& InDescription) : Proxy(InProxy) , Bounds(InBounds) #if WITH_SPATIAL_READINESS_DESCRIPTIONS , Description(InDescription) #endif`
- L37 _public member_ `Chaos::FSingleParticlePhysicsProxy* Proxy;`
- L38 _public member_ `FBox Bounds;`
- L40 _public member_ `FString Description;`

#### struct `FSpatialReadinessSimCallbackInput`  
`struct FSpatialReadinessSimCallbackInput : public Chaos::FSimCallbackInput`  
_L44-54_
- inherits: `Chaos::FSimCallbackInput`
- L46 _public member_ `TSet<Chaos::FSingleParticlePhysicsProxy*> UnreadyVolumesToAdd;`
- L47 _public member_ `TSet<Chaos::FSingleParticlePhysicsProxy*> UnreadyVolumesToRemove;`
- L49 _public function_ `void Reset()`

#### struct `FSpatialReadinessSimCallback`  
`struct FSpatialReadinessSimCallback : public Chaos::TSimCallbackObject< FSpatialReadinessSimCallbackInput, Chaos::FSimCallbackNoOutput, Chaos::ESimCallbackOptions::Presimulate | Chaos::ESimCallbackOptions::ParticleRegister | Chaos::ESimCallbackOptions::MidPhaseModification | Chaos::ESimCallbackOptions::PreIntegrate | Chaos::ESimCallbackOptions::PostIntegrate | Chaos::ESimCallbackOptions::PreSolve | Chaos::ESimCallbackOptions::PostSolve>`  
_L56-191_
- inherits: `Chaos::TSimCallbackObject<FSpatialReadinessSimCallbackInput,Chaos::FSimCallbackNoOutput,Chaos::ESimCallbackOptions::Presimulate|Chaos::ESimCallbackOptions::ParticleRegister|Chaos::ESimCallbackOptions::MidPhaseModification|Chaos::ESimCallbackOptions::PreIntegrate|Chaos::ESimCallbackOptions::PostIntegrate|Chaos::ESimCallbackOptions::PreSolve|Chaos::ESimCallbackOptions::PostSolve>`
- L68 _public typedef_ `using This = FSpatialReadinessSimCallback;`
- L71 _public prototype_ `FSpatialReadinessSimCallback(FPhysScene_Chaos& InPhysicsScene);`
- L74 _public prototype_ `int32 AddUnreadyVolume_GT(const FBox& Bounds, const FString& Description);` — Game thread functions for adding and removing unready volumes
- L75 _public prototype_ `void RemoveUnreadyVolume_GT(int32 UnreadyVolumeIndex);`
- L84 _public prototype_ `bool QueryReadiness_GT(const FBox& Bounds, TArray<int32>& OutVolumeIndices, bool bAllUnreadyVolumes=false) const;` — Game thread function for querying for unready volumes If bAllUnreadyVolumes is true, then a multi-query will be used and OutVolumeIndices will be populated with every index that encroaches. For performance, we only return the index of the first unread volume that we find.
- L87 _public prototype_ `const FUnreadyVolumeData_GT* GetVolumeData_GT(int32 VolumeIndex) const;` — Given a volume index, get it's description
- L90 _public prototype_ `void ForEachVolumeData_GT(const TFunction<void(const FUnreadyVolumeData_GT&)>& Func);` — Iterate over each unready volume and get
- L93 _public prototype_ `int32 GetNumUnreadyVolumes_GT() const;` — Get the number of unready volumes
- L96 _public prototype_ `void ForEachUnreadyRigidParticle_PT(const TFunction<bool(Chaos::FPBDRigidParticleHandle*)>& Lambda) const;` — Perform an operation on each of the currently frozen particles - only valid on the physics thread
- L99 _public prototype_ `void ForEachUnreadyRigidParticle_PT(const TFunction<bool(Chaos::FPBDRigidParticleHandle*, int32)>& Lambda) const;` — A variant which also sees how many frames each particle will remain frozen
- L102 _public prototype_ `int32 GetNumUnreadyRigidParticles_PT() const;` — Get the total number of currently frozen particles - only valid on the physics thread
- L106 _protected prototype_ `virtual void OnPreSimulate_Internal() override;`
- L107 _protected prototype_ `virtual void OnParticlesRegistered_Internal(TArray<Chaos::FSingleParticlePhysicsProxy*>& RegisteredProxies) override;`
- L108 _protected prototype_ `virtual void OnMidPhaseModification_Internal(Chaos::FMidPhaseModifierAccessor& Accessor) override;`
- L109 _protected prototype_ `virtual void OnPreIntegrate_Internal() override;`
- L110 _protected prototype_ `virtual void OnPostIntegrate_Internal() override;`
- L111 _protected prototype_ `virtual void OnPreSolve_Internal() override;`
- L112 _protected prototype_ `virtual void OnPostSolve_Internal() override;`
- L117 _protected prototype_ `void OnMidPhaseModification_PrioritizeUnreadyVolumes(Chaos::FMidPhaseModifierAccessor& Accessor);` — Variants of the midphase modification function, with different performance characteristics
- L118 _protected prototype_ `void OnMidPhaseModification_PrioritizeMidPhases(Chaos::FMidPhaseModifierAccessor& Accessor);`
- L119 _protected prototype_ `void OnMidPhaseModification_Grid(Chaos::FMidPhaseModifierAccessor& Accessor);`
- L122 _protected prototype_ `Chaos::FPBDRigidsEvolution* GetEvolution();` — Helpers
- L123 _protected prototype_ `static int32 GetFreezeFrames();`
- L124 _protected prototype_ `ESpatialReadinessSimCallback_MidPhaseStrategy GetMidPhaseStrategy(const Chaos::FMidPhaseModifierAccessor& Accessor) const;`
- L128 _protected prototype_ `void FreezeParticles_PT();` — Functions for freezing and unfreezing all particles in the UnreadyRigidParticles_PT set.
- L129 _protected prototype_ `void UnFreezeParticles_PT();`
- L133 _protected prototype_ `void DecrementUnreadyRigidParticles_PT();` — Decrement counters for each unready particle, removing them from the unready particles array when their counters reach zero.
- L137 _protected prototype_ `bool QueryReadiness_PT(const Chaos::FAABB3& Bounds, TArray<const Chaos::FSingleParticlePhysicsProxy*>& OutVolumeProxies);` — Physics thread function for querying for unready volumes TODO: Make const
- L140 _protected prototype_ `bool IsUnreadyVolume_PT(const Chaos::FGeometryParticleHandle& ParticleHandle) const;` — True for particles which are in the unready volumes particles list
- L143 _protected member_ `FPhysScene_Chaos& PhysicsScene;` — Keep a ref to the phys scene so we can add and remove particles
- L153 _protected member_ `Chaos::Private::THashMappedArray<int32, FUnreadyVolumeData_GT, FHashMapTraits> UnreadyVolumeData_GT;`
- L156 _protected member_ `TSet<Chaos::FSingleParticlePhysicsProxy*> UnreadyVolumeParticles_PT;` — List of particle handles which represent unready volumes
- L185 _protected member_ `TMap<Chaos::FPBDRigidParticleHandle*, FUnreadyRigidParticleData> UnreadyRigidParticles_PT;`
- L190 _protected member_ `TArray<TPair<Chaos::FGeometryParticleHandle*, Chaos::EObjectStateType>> ParticleDataCache_PT;` — "Unready" particles are forced to be stationary in PreSimulate, and restored to their previous state in PostIntegrate. The values needed for restoration are stored and mapped back to particle id's in this hash-mapped array.

#### struct `FSpatialReadinessSimCallback::FHashMapTraits`  
`struct FHashMapTraits`  
_L148-152_
- desc: List of unready volume physics proxies. We directly use single particle physics proxy rather than something more generic because we know that we are only going to create static single particles for these volumes.
- L150 _public function_ `static uint32 GetIDHash(const int32 Idx)`
- L151 _public prototype_ `static uint32 GetElementID(const FUnreadyVolumeData_GT& Element);`

#### struct `FSpatialReadinessSimCallback::FUnreadyRigidParticleData`  
`struct FUnreadyRigidParticleData`  
_L180-184_
- desc: Lists of particle handles which represent particles that interacted with unready volumes, along with a counter representing how many more ticks the particle should remain frozen. The counter strategy is to accommodate the following oddities about particle creation, deletion, and midphase creation. - A particle can exist for one entire sim tick after it is created without appearing in the mid phase. Therefore particles which are registered on top of unready volumes must be unreadied with a count of 2. - For the same reason as the item above, when an unready volume is deleted on the same frame that another particle is created (perhaps a streaming object with which the unready volume was meant to prevent overlap), there's an additional frame during which the new particle has no collision. We lose nothing by keeping objects frozen for one more frame. The counter is used to accommadate this case. This freeze frame counter is packed into a small struct which also contains the SyncTimeStamp for the particle's proxy, because if we're going to track the particle for more than one frame (and we are), then we also need to track the validity of the SyncTimeStamp before ever accessing methods or properties on the particle handle ptr.
- L182 _public member_ `TWeakPtr<FProxyTimestampBase, ESPMode::ThreadSafe> SyncTimeStamp;`
- L183 _public member_ `int FreezeFrames;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessStats.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_STATS_GROUP(TEXT("SpatialReadiness"), STATGROUP_SpatialReadiness, ST`
- L8 _delegate_ `DECLARE_STATS_GROUP_VERBOSE(TEXT("SpatialReadinessDetailed"), STATGROUP_SpatialReadinessVerbose, STATCAT_Advanced)`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessSubsystem.h` (Public)


#### class `USpatialReadiness`  
`class USpatialReadiness : public UWorldSubsystem`  
_L16-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L19 _private typedef_ `using This = USpatialReadiness;`
- L22 _public prototype_ `USpatialReadiness();`
- L23 _public prototype_ `USpatialReadiness(FVTableHelper& Helper);`
- L26 _public prototype_ `FSpatialReadinessVolume AddReadinessVolume(const FBox& Bounds, const FString& Description);` — Add a volume which can be marked read/unready
- L33 _public prototype_ `bool QueryReadiness(const FBox& Bounds, TArray<FString>& OutDescriptions, bool bAllDescriptions = false) const;` — Check to see if a volume is ready - returns true if ready. If bAllDescriptions = false, OutDescriptions will contain only the description of the first unready volume that we hit. If true, it will contain descriptions from all overlapping volumes.
- L36 _public prototype_ `uint32 GetNumUnreadyVolumes() const;` — Get the number of unready volumes
- L40 _public function_ `template <typename ReceiverT> FDelegateHandle OnUnreadyVolumeChangedDelegate_AddUObject(ReceiverT* Receiver, void (ReceiverT::*Method)(const FBox&, const FString&, EUnreadyVolumeAction))` — Add a function of some type to the external-facing delegate for unready volume updates
- L44 _public prototype_ `void OnUnreadyVolumeChangedDelegate_Remove(const FDelegateHandle& Handle);` — Remove a function from the external-facing delegate for unready volume updates
- L47 _public function_ `FSpatialReadinessSimCallback* GetSimCallback()`
- L48 _public function_ `const FSpatialReadinessSimCallback* GetSimCallback() const`
- L52 _public member_ `FDelegateHandle OnDebugDrawDelegateHandle;`
- L53 _public prototype_ `void OnDebugDraw(UCanvas* Canvas, APlayerController* PlayerController);`
- L56 _public prototype_ `static bool StaticShouldCreateSubsystem(UObject* Outer);`
- L60 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L61 _protected prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L62 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L63 _protected prototype_ `virtual void Deinitialize() override;`
- L69 _private member_ `FSpatialReadinessAPI SpatialReadiness;` — The spatial readiness API object which manages giving out volume "handles"
- L72 _private prototype_ `int32 AddUnreadyVolume(const FBox& Bounds, const FString& Description);` — The functions to bind to the spatial readiness API.
- L73 _private prototype_ `void RemoveUnreadyVolume(int32 UnreadyVolumeIndex);`
- L76 _private prototype_ `bool CreateSimCallback();` — Create and destroy the physics sim callback
- L77 _private prototype_ `bool DestroySimCallback();`
- L80 _private prototype_ `FPhysScene_Chaos* GetScene();` — Getters
- L81 _private prototype_ `Chaos::FPhysicsSolver* GetSolver();`
- L83 _private member_ `FOnUnreadyVolumeChanged_Delegate OnUnreadyVolumeChanged_Delegate;`
- L85 _private member_ `FSpatialReadinessSimCallback* SimCallback = nullptr;`

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessVolume.h` (Public)


#### class `FSpatialReadinessVolume`  
`class FSpatialReadinessVolume final`  
_L11-92_
- L17 _public prototype_ `bool IsValid() const;` — Check to make sure that the readiness system which created this handle did not go out of scope.
- L21 _public prototype_ `bool EnsureIsValid() const;` — Ensure that IsValid() returns true, printing a message and returning false if not.
- L24 _public prototype_ `bool IsReady() const;` — Check to see if this handle points to a volume which is currently "ready".
- L27 _public prototype_ `void MarkReady();` — Mark this volume as "ready"
- L30 _public prototype_ `void MarkUnready();` — Mark this volume as "unready"
- L33 _public prototype_ `void MarkUnready(const FBox& NewBounds);` — Optional overrides to MakeUnready() for adjusting bounds and/or description
- L34 _public prototype_ `void MarkUnready(const FString& NewDescription);`
- L35 _public prototype_ `void MarkUnready(const FBox& NewBounds, const FString& NewDescription);`
- L38 _public prototype_ `void SetDescription(const FString& NewDescription);` — Set properties, updating internals if necessary
- L39 _public prototype_ `void SetBounds(const FBox& NewBounds);`
- L43 _public prototype_ `const FString& GetDescription() const;` — Get the description of this handle - will be empty string if the WITH_SPATIAL_READINESS_DESCRIPTIONS macro is 0
- L47 _public prototype_ `const FString GetDebugString() const;` — Get a debug string for this volume
- L51 _public prototype_ `~FSpatialReadinessVolume();` — When a handle is destroyed, it will make the corresponding volume as ready
- L54 _public prototype_ `FSpatialReadinessVolume(const FSpatialReadinessVolume&) = delete;` — Readiness handles are unique and cannot be copied
- L55 _public prototype_ `FSpatialReadinessVolume& operator=(const FSpatialReadinessVolume&) = delete;`
- L58 _public prototype_ `FSpatialReadinessVolume(FSpatialReadinessVolume&& Other);` — Move constructor & assignment
- L59 _public prototype_ `FSpatialReadinessVolume& operator=(FSpatialReadinessVolume&& Other);`
- L63 _private prototype_ `void MarkUnready_Internal(bool bRecreateState);`
- L68 _private prototype_ `FSpatialReadinessVolume( TWeakPtr<FSpatialReadinessAPIDelegates> InDelegates, const FBox& InBounds, const FString& InDescription);`
- L75 _private member_ `TWeakPtr<FSpatialReadinessAPIDelegates> Delegates;` — Ref to the spatial readiness system. It will be an access error to use this handle if this interface ever goes out of scope
- L80 _private member_ `int32 Index;` — Index used by the interface to select the related volume, if one exists (ie if this handle refers to an "unready" state). If one doesn't exist, then this handle is "ready" and this is INDEX_NONE
- L84 _private member_ `FBox Bounds;` — Bounds of the unready volume. This is used when marking the volume as unready to create the internal "unready volume".
- L90 _private member_ `FString Description;` — Description of the reason why the volume referred to by this handle might be unready. Again, this is used only when creating the internal unready volume.

### `Plugins/Experimental/SpatialReadiness/Source/SpatialReadiness/Public/SpatialReadinessVolumeComponent.h` (Public)


#### class `USpatialReadinessVolumeComponent`  
`class USpatialReadinessVolumeComponent : public UActorComponent`  
_L10-49_
- reflection: `UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UActorComponent`
- L16 _public prototype_ `virtual void BeginPlay() override;`
- L17 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L20 _public prototype_ `bool IsReady() const;` — `UFUNCTION(BlueprintCallable, Category = "SpatialReadiness")`
- L23 _public prototype_ `void MarkReady();` — `UFUNCTION(BlueprintCallable, Category = "SpatialReadiness")`
- L26 _public prototype_ `void MarkUnready();` — `UFUNCTION(BlueprintCallable, Category = "SpatialReadiness")`
- L29 _public prototype_ `void SetReadiness(bool bIsReady);` — `UFUNCTION(BlueprintCallable, Category = "SpatialReadiness")`
- L32 _public prototype_ `void SetDescription(const FString& InDescription);` — `UFUNCTION(BlueprintCallable, Category = "SpatialReadiness")`
- L35 _public prototype_ `void SetBounds(const FBox& InBounds);` — `UFUNCTION(BlueprintCallable, Category = "SpatialReadiness")`
- L38 _public member_ `FString Description = "Sp` — `UPROPERTY(EditDefaultsOnly, Category = "SpatialReadiness", BlueprintSetter=SetDescription)`
- L41 _public member_ `FBox Bounds = FBox(FVector(-50.f, -50.f, -50.f), FVector(50.f, 50.f, 50.f));` — `UPROPERTY(EditDefaultsOnly, Category = "SpatialReadiness", BlueprintSetter=SetBounds)`
- L44 _public member_ `bool bStartReady = false;` — `UPROPERTY(EditDefaultsOnly, Category = "SpatialReadiness")`
- L48 _protected member_ `TOptional<FSpatialReadinessVolume> ReadinessVolume;`
