# Plugins / ChaosUserDataPT

- module root: `Plugins/Experimental/ChaosUserDataPT/Source/ChaosUserDataPT`
- headers: 3; symbols: 53
- symbol kinds: class=2, delegate=8, function=18, member=17, namespace=2, prototype=3, struct=2, typedef=1
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/ChaosUserDataPT/Source/ChaosUserDataPT/Public/ChaosUserDataPT.h` (Public)


#### struct `Chaos::FUserDataPTConfig`  
`struct FUserDataPTConfig`  
_L47-53_
- desc: Configuration for TUserDataManagerPT behavior. Passed at construction time and stored as a const member.
- L52 _public member_ `bool bGetData_GT = false;` — When true, TUserDataManagerPT will cache userdata on GT as well as PT, so that GT users can get the last set value. Useful when they want to make incremental changes, but incurs a higher memory footprint.

#### struct `Chaos::TUserDataManagerPTInput`  
`template <typename TUserData> struct TUserDataManagerPTInput : public FSimCallbackInput`  
_L69-121_
- inherits: `FSimCallbackInput`
- desc: TUserDataManagerPTInput Input is a collection of pointers to new and updated userdata objects to be sent to the physics thread NOTE: On deprecation strategy here. The members of this struct should never have been public, so they have all been deprecated. Private duplicates are now in use, but those will be renamed to the original names once the deprecated versions are removed. Copies are needed so that during the deprecation phase the internal TUserDataManagerPT code doesn't trigger deprecation warnings for valid operations.
- L72 _public member_ `mutable TMap<FUniqueIdx, TUniquePtr<TUserData>> UserDataToAdd;` — `UE_DEPRECATED(5.8, "UserDataToAdd no longer used, will be removed.")`
- L75 _public member_ `TSet<FUniqueIdx> UserDataToRemove;` — `UE_DEPRECATED(5.8, "UserDataToRemove no longer used, will be removed.")`
- L78 _public member_ `bool bClear = false;` — `UE_DEPRECATED(5.8, "bClear no longer used, will be removed.")`
- L81 _public member_ `bool bResizeOnClear = false;` — `UE_DEPRECATED(5.8, "bResizeOnClear no longer used, will be removed.")`
- L84 _public member_ `uint32 Identifier = std::numeric_limits<uint32>::max();` — `UE_DEPRECATED(5.8, "Identifier no longer used, will be removed.")`
- L86 _public function_ `void Reset()`
- L104 _private member_ `mutable TMap<FUniqueIdx, TUniquePtr<TUserData>> UserDataToAddPrivate;` — Map of particle unique indices to user data ptrs NOTE: This is marked mutable because the userdata objects must be moved to the internal array after making it OnPreSimulate_Internal, but input objects are const in that context. This might be frowned on, but since TUserDataManagerPTInput is a class which is only used internally to TUserDataManagerPT, an argument could be made either way.
- L107 _private member_ `TSet<FUniqueIdx> UserDataToRemovePrivate;` — Set of particle unique indices for which to remove user data
- L110 _private member_ `bool bClearPrivate = false;` — Flag for clearing all data
- L113 _private member_ `bool bResize = false;` — Flag for resizing container to fit data
- L117 _private member_ `uint32 IdentifierPrivate = std::numeric_limits<uint32>::max();` — Monotonically increasing identifier for the input object. Each newly constructed input will store and increment this;

#### class `Chaos::TUserDataManagerPT`  
`template <typename TUserData> class TUserDataManagerPT : public TSimCallbackObject< TUserDataManagerPTInput<TUserData>, FSimCallbackNoOutput, ESimCallbackOptions::Presimulate | ESimCallbackOptions::ParticleUnregister>`  
_L132-488_
- inherits: `TSimCallbackObject<TUserDataManagerPTInput<TUserData>,FSimCallbackNoOutput,ESimCallbackOptions::Presimulate|ESimCallbackOptions::ParticleUnregister>`
- desc: TUserDataManagerPT A chaos callback object which stores and allows access to user data associated with particles on the physics thread. Note that FSimCallbackOutput is the output struct - this carries no data because this is a one-way callback. We use it basically just to marshal data in one direction.
- L137 _private typedef_ `using TInput = TUserDataManagerPTInput<TUserData>;`
- L141 _public function_ `explicit TUserDataManagerPT(const FUserDataPTConfig& InConfig = FUserDataPTConfig()) : Config(InConfig)`
- L146 _public prototype_ `virtual ~TUserDataManagerPT() = default;`
- L150 _public function_ `template <typename TParticleHandle> bool SetData_GT(const TParticleHandle& Handle, const TUserData& UserData)` — Add or update user data associated with a particle handle (copy)
- L158 _public function_ `template <typename TParticleHandle> bool SetData_GT(const TParticleHandle& Handle, TUserData&& UserData)` — Add or update user data associated with a particle handle (move)
- L197 _public function_ `template <typename TParticleHandle> const TUserData* GetData_GT(const TParticleHandle& Handle) const` — Get user data from the GT cache. Returns nullptr if Config.bGetData_GT is false or the particle has no data.
- L212 _public function_ `template <typename TParticleHandle> bool RemoveData_GT(const TParticleHandle& Handle)` — Remove user data associated with a particle handle
- L250 _public function_ `template <> bool SetData_GT<Chaos::FPhysicsObjectHandle>(const Chaos::FPhysicsObjectHandle& Object, const TUserData& UserData)`
- L263 _public function_ `template <> bool RemoveData_GT<Chaos::FPhysicsObjectHandle>(const Chaos::FPhysicsObjectHandle& Object)`
- L279 _public function_ `template <typename TParticleHandle> const TUserData* GetData_PT(const TParticleHandle& Handle) const` — TParticleHandle is generalized here because it can be FRigidBodyHandle_Internal or FGeometryParticleHandle which have the same api...
- L288 _public function_ `void VisitData_PT(TFunctionRef<void(Chaos::FUniqueIdx, const TUserData&)> Lambda)` — Execute a lambda on each data entry
- L300 _public function_ `void VisitAllData_PT(const TFunction<void(Chaos::FUniqueIdx, const TUserData&)>& Lambda)` — `UE_DEPRECATED(5.8, "VisitAllData_PT will be removed, use VisitData_PT instead.")`
- L306 _public function_ `bool ClearData_GT(const bool bResize = true)` — Clear all data
- L344 _public function_ `virtual FName GetFNameForStatId() const override`
- L351 _public member_ `const FUserDataPTConfig Config;` — Runtime configuration (immutable after construction)
- L355 _protected function_ `virtual void OnPostInitialize_Internal() override`
- L377 _protected function_ `virtual void OnPreShutdown_External() override`
- L391 _protected function_ `virtual void OnPreSimulate_Internal() override`
- L453 _protected function_ `virtual void OnParticleUnregistered_Internal(TArray<TTuple<FUniqueIdx, FSingleParticlePhysicsProxy*>>& UnregisteredProxies) override`
- L474 _protected member_ `uint32 InputIdentifier_GT = 0;` — Identifier of the next input to be created on the game thread
- L477 _protected member_ `uint32 InputIdentifier_PT = std::numeric_limits<uint32>::max();` — Identifier of the last input to be consumed on the physics thread
- L480 _protected member_ `TSparseArray<TUniquePtr<TUserData>> UserDataMap_PT;` — Map of particle unique ids to user data, for PT access
- L484 _protected member_ `TSparseArray<TUniquePtr<TUserData>> UserDataMap_GT;` — Map of particle unique ids to user data, for optional GT access. Only populated when Config.bGetData_GT is true; otherwise stays empty.
- L487 _protected member_ `FDelegateHandle ParticleUnregisteredGTHandle;` — Delegate handle for GT particle unregistration cleanup

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace Chaos`
- L365 _function_ `` (scope `Chaos::TUserDataManagerPT::OnPostInitialize_Internal`)

### `Plugins/Experimental/ChaosUserDataPT/Source/ChaosUserDataPT/Public/ChaosUserDataPTModule.h` (Public)


#### class `FChaosUserDataPTModule`  
`class FChaosUserDataPTModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/ChaosUserDataPT/Source/ChaosUserDataPT/Public/ChaosUserDataPTStats.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_STATS_GROUP(TEXT("ChaosUserDataPT"), STATGROUP_ChaosUserDataPT, STA`
- L9 _namespace_ `namespace Chaos`
- L11 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ChaosUserDataPT::SetData_GT"), STAT_UserDataPT_SetData_GT, STATGROUP_ChaosUserDa`
- L12 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ChaosUserDataPT::RemoveData_GT"), STAT_UserDataPT_RemoveData_GT, STATGROUP_ChaosUse`
- L13 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ChaosUserDataPT::GetData_PT"), STAT_UserDataPT_GetData_PT, STATGROUP_ChaosUserDa`
- L14 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ChaosUserDataPT::GetData_GT"), STAT_UserDataPT_GetData_GT, STATGROUP_ChaosUserDa`
- L15 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ChaosUserDataPT::OnPreSimulate::UpdateData"), STAT_UserDataPT_UpdateData_PT, STATGR`
- L16 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ChaosUserDataPT::OnPreSimulate::RemoveData"), STAT_UserDataPT_RemoveData_PT, STATGR`
- L17 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ChaosUserDataPT::OnPreSimulate::ClearData"), STAT_UserDataPT_ClearData_PT, STATGRO`
