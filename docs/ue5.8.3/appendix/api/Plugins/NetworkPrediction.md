# Plugins / NetworkPrediction

- module root: `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction`
- headers: 41; symbols: 1472
- symbol kinds: class=42, delegate=3, enum=25, enumerator=87, externvar=7, function=400, macro=102, member=373, namespace=19, prototype=165, struct=126, typedef=117, variable=6
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, Engine, NetCore, PhysicsCore, RenderCore, TraceLog

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Private/NetworkPredictionNetSerializers.h` (Private)


#### struct `FNetworkPredictionProxyNetSerializerConfig`  
`struct FNetworkPredictionProxyNetSerializerConfig : public FNetSerializerConfig`  
_L14-17_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`
- desc: Iris net serialization for FNetworkPredictionProxy. This is required due to the struct mixing locally-set and replicated member variables.

#### struct `FServerReplicationRPCParameterNetSerializerConfig`  
`struct FServerReplicationRPCParameterNetSerializerConfig : public FNetSerializerConfig`  
_L29-39_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`
- desc: Iris net serialization for FServerReplicationRPCParameter. This is required due to the struct using a custom NetSerialize function that is routed to other serialization method(s) that may do polymorphic and/or conditional serialization. Implementation is based on FCharacterNetworkSerializationPackedBitsNetSerializer
- L34 _public member_ `static constexpr uint32 DefaultMaxQuantizedSizeBits = FServerReplicationRPCParameter::MaxNumBits;`
- L38 _public member_ `uint32 MaxQuantizedSizeBits = DefaultMaxQuantizedSizeBits;` — `UPROPERTY()` — Value used to sanity check incoming data so that we do not over-allocate dynamic memory

#### struct `FReplicationProxyNetSerializerConfig`  
`struct FReplicationProxyNetSerializerConfig : public FNetSerializerConfig`  
_L53-63_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`
- desc: Iris net serialization for FReplicationProxy. This is required due to the struct using a custom NetSerialize function that is routed to other serialization method(s) that may do polymorphic and/or conditional serialization. Implementation is partly based on the last resort net serializer.
- L58 _public member_ `static constexpr uint32 DefaultMaxQuantizedSizeBits = FReplicationProxy::MaxNumBits;`
- L62 _public member_ `uint32 MaxQuantizedSizeBits = DefaultMaxQuantizedSizeBits;` — `UPROPERTY()` — Value used to sanity check incoming data so that we do not over-allocate dynamic memory

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Net` (scope `UE`)
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace Net` (scope `UE`)
- L65 _namespace_ `namespace UE`
- L65 _namespace_ `namespace Net` (scope `UE`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionBuffer.h` (Public)


#### struct `TNetSimLazyWriterFunc`  
`template<typename ElementType> struct TNetSimLazyWriterFunc`  
_L9-30_
- desc: Helper struct to encapsulate optional, delayed writing of new element to TNetworkSimAuxBuffer buffer
- L12 _public function_ `template<typename TBuffer> TNetSimLazyWriterFunc(TBuffer& Buffer, int32 PendingFrame)`
- L18 _public function_ `TNetSimLazyWriterFunc(void* Data)` — Hack
- L23 _public function_ `ElementType* Get() const`
- L29 _public member_ `TFunction<void*()> GetFunc;`

#### struct `TNetSimLazyWriter`  
`template<typename ElementType> struct TNetSimLazyWriter`  
_L34-46_
- desc: Reference version of LazyWriter. This is what gets passed through chains of ::SimulationTick calls. This is to avoid copying the TFunction in TNetSimLazyWriterFunc around.
- L37 _public function_ `template<typename TLazyWriter> TNetSimLazyWriter(const TLazyWriter& Parent) : GetFunc(Parent.GetFunc)`
- L40 _public function_ `ElementType* Get() const`
- L45 _public member_ `TFunctionRef<void*()> GetFunc;`

#### struct `TNetworkSimAuxBuffer`  
`template<typename ElementType> struct TNetworkSimAuxBuffer`  
_L50-153_
- desc: Sparse buffer: each element has explicit Frame value
- L52 _public function_ `TNetworkSimAuxBuffer(int32 Capacity)`
- L57 _public function_ `ElementType* operator[](int32 Frame)`
- L62 _public function_ `const ElementType* operator[](int32 Frame) const`
- L68 _public function_ `ElementType* WriteAtFrame(int32 Frame)` — Writes a new element at Frame. Copies previous frames contents into new element.
- L93 _public function_ `TNetSimLazyWriterFunc<ElementType> LazyWriter(int32 Frame)`
- L99 _public function_ `void Resize(int32 NewSize)` — Resizes while preserving contents from head position
- L122 _private function_ `void Init(int32 NewSize)`
- L129 _private function_ `const ElementType* GetImpl(int32 Frame) const`
- L146 _private member_ `int32 HeadPosition = 0;` — Latest element to be written
- L149 _private member_ `int32 IndexMask = 0;` — Holds the mask for indexing the buffer's elements
- L152 _private member_ `TArray<TInternal> Elements;` — Holds the buffer's elements

#### struct `TNetworkSimAuxBuffer::TInternal`  
`struct TInternal`  
_L116-120_
- L118 _public member_ `int32 Frame = -1;`
- L119 _public member_ `ElementType Element;`

#### struct `TNetworkPredictionBuffer`  
`template<typename ElementType, bool SingleElement=false> struct TNetworkPredictionBuffer`  
_L157-223_
- desc: Circular buffer for storing continuous frame data
- L159 _public function_ `TNetworkPredictionBuffer(int32 Capacity=2)`
- L165 _public function_ `TNetworkPredictionBuffer(const TNetworkPredictionBuffer<ElementType, SingleElement>&& Other) : IndexMask(Other.IndexMask) , Elements(MoveTemp(Other.Elements))`
- L171 _public function_ `TNetworkPredictionBuffer<ElementType, SingleElement>& operator=(TNetworkPredictionBuffer<ElementType, SingleElement>&& Other)`
- L178 _public function_ `ElementType& operator[](int32 Index)`
- L183 _public function_ `const ElementType& operator[](int32 Index) const`
- L188 _public function_ `int32 Capacity() const`
- L194 _public function_ `void Resize(int32 NewSize, int32 PrevHead)` — Resizes while preserving contents from head position
- L211 _private function_ `void Init(int32 NewSize)`
- L219 _private member_ `int32 IndexMask = 0;` — Holds the mask for indexing the buffer's elements.
- L222 _private member_ `TArray<ElementType> Elements;` — Holds the buffer's elements.
- L235 _private member_ `ElementType Element;`

#### struct `TNetworkPredictionBuffer`  
`template<typename ElementType> struct TNetworkPredictionBuffer<ElementType, true>`  
_L226-236_
- L159 _public function_ `TNetworkPredictionBuffer(int32 Capacity=2)`
- L165 _public function_ `TNetworkPredictionBuffer(const TNetworkPredictionBuffer<ElementType, SingleElement>&& Other) : IndexMask(Other.IndexMask) , Elements(MoveTemp(Other.Elements))`
- L171 _public function_ `TNetworkPredictionBuffer<ElementType, SingleElement>& operator=(TNetworkPredictionBuffer<ElementType, SingleElement>&& Other)`
- L178 _public function_ `ElementType& operator[](int32 Index)`
- L183 _public function_ `const ElementType& operator[](int32 Index) const`
- L188 _public function_ `int32 Capacity() const`
- L194 _public function_ `void Resize(int32 NewSize, int32 PrevHead)` — Resizes while preserving contents from head position
- L211 _private function_ `void Init(int32 NewSize)`
- L219 _private member_ `int32 IndexMask = 0;` — Holds the mask for indexing the buffer's elements.
- L222 _private member_ `TArray<ElementType> Elements;` — Holds the buffer's elements.
- L235 _private member_ `ElementType Element;`

#### Free symbols / members of external scopes

- L14 _function_ `GetFunc = [&Buffer, PendingFrame]()` (scope `TNetSimLazyWriterFunc::TNetSimLazyWriterFunc`)
- L20 _function_ `GetFunc = [Data]()` (scope `TNetSimLazyWriterFunc::TNetSimLazyWriterFunc`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionCVars.h` (Public)


#### struct `FConditionalAutoConsoleRegister`  
`struct FConditionalAutoConsoleRegister`  
_L25-42_
- desc: This is required because these cvars live in header files that will be included across different compilation units Just using standard FAutoConsoleVariableRef will cause multiple registrations of the same variable
- L27 _public function_ `FConditionalAutoConsoleRegister(const TCHAR* VarName, int32 Value, const TCHAR* Help)`
- L35 _public function_ `FConditionalAutoConsoleRegister(const TCHAR* VarName, float Value, const TCHAR* Help)`

#### Free symbols / members of external scopes

- L13 _function_ `inline IConsoleVariable* FindConsoleVarHelper(const TCHAR* VarName)`
- L20 _macro_ `#define NETSIM_CONST_CVARS (UE_BUILD_SHIPPING || UE_BUILD_TEST)`
- L44 _macro_ `#define NP_DEVCVAR_INT(Var,Value,VarName,Help) \`
- L48 _macro_ `#define NETSIM_DEVCVAR_INT(Var,Value,VarName,Help) \`
- L64 _macro_ `#define NETSIM_DEVCVAR_SHIPCONST_INT(Var,Value,VarName,Help) \`
- L68 _macro_ `#define NETSIM_DEVCVAR_SHIPCONST_INT(Var,Value,VarName,Help) NETSIM_DEVCVAR_INT(Var,Value,VarName,Help)`
- L73 _macro_ `#define NP_DEVCVAR_FLOAT(Var,Value,VarName,Help) \`
- L77 _macro_ `#define NETSIM_DEVCVAR_FLOAT(Var,Value,VarName,Help) \`
- L93 _macro_ `#define NETSIM_DEVCVAR_SHIPCONST_FLOAT(Var,Value,VarName,Help) \`
- L97 _macro_ `#define NETSIM_DEVCVAR_SHIPCONST_FLOAT(Var,Value,VarName,Help) NETSIM_DEVCVAR_FLOAT(Var,Value,VarName,Help)`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionCheck.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define NP_ENSURES_ALWAYS 0`
- L11 _macro_ `#define NP_CHECKS_AND_ENSURES 1`
- L13 _macro_ `#define npCheck(Condition) check(Condition)`
- L14 _macro_ `#define npCheckf(Condition, ...) checkf(Condition, ##__VA_ARGS__)`
- L16 _macro_ `#define npEnsure(Condition) ensureAlways(Condition)`
- L17 _macro_ `#define npEnsureMsgf(Condition, ...) ensureAlwaysMsgf(Condition, ##__VA_ARGS__)`
- L19 _macro_ `#define npEnsure(Condition) ensure(Condition)`
- L20 _macro_ `#define npEnsureMsgf(Condition, ...) ensureMsgf(Condition, ##__VA_ARGS__)`
- L23 _macro_ `#define npCheck(...)`
- L24 _macro_ `#define npCheckf(...)`
- L25 _macro_ `#define npEnsure(Condition) (!!(Condition))`
- L26 _macro_ `#define npEnsureMsgf(Condition, ...) (!!(Condition))`
- L29 _macro_ `#define NP_CHECKS_AND_ENSURES_SLOW !(UE_BUILD_SHIPPING || UE_BUILD_TEST)`
- L31 _macro_ `#define npCheckSlow(Condition) check(Condition)`
- L32 _macro_ `#define npCheckfSlow(Condition, ...) checkf(Condition, ##__VA_ARGS__)`
- L34 _macro_ `#define npEnsureSlow(Condition) ensureAlways(Condition)`
- L35 _macro_ `#define npEnsureMsgfSlow(Condition, ...) ensureAlwaysMsgf(Condition, ##__VA_ARGS__)`
- L37 _macro_ `#define npEnsureSlow(Condition) ensure(Condition)`
- L38 _macro_ `#define npEnsureMsgfSlow(Condition, ...) ensureMsgf(Condition, ##__VA_ARGS__)`
- L41 _macro_ `#define npCheckSlow(Condition)`
- L42 _macro_ `#define npCheckfSlow(...)`
- L43 _macro_ `#define npEnsureSlow(Condition) (!!(Condition))`
- L44 _macro_ `#define npEnsureMsgfSlow(Condition, ...) (!!(Condition))`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionComponent.h` (Public)


#### class `UNetworkPredictionComponent`  
`class UNetworkPredictionComponent : public UActorComponent`  
_L27-90_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UActorComponent`
- L33 _public prototype_ `UNetworkPredictionComponent();`
- L35 _public prototype_ `virtual void InitializeComponent() override;`
- L36 _public prototype_ `virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;`
- L37 _public prototype_ `virtual void PreNetReceive() override;`
- L38 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type Reason);`
- L41 _public prototype_ `void CallServerRPC();` — Invoke the ServerRPC, called from UNetworkPredictionWorldManager via the TServerRPCService.
- L46 _protected function_ `virtual void InitializeNetworkPredictionProxy()` — Classes must initialize the NetworkPredictionProxy (register with the NetworkPredictionSystem) here. EndPlay will unregister.
- L49 _protected prototype_ `virtual void InitializeForNetworkRole(ENetRole Role, const bool bHasNetConnection);` — Finalizes initialization when NetworkRole changes. Does not need to be overridden.
- L52 _protected prototype_ `bool CheckOwnerRoleChange();` — Helper: Checks if the owner's role has changed and calls InitializeForNetworkRole if necessary.
- L56 _protected prototype_ `void ServerReceiveClientInput(const FServerReplicationRPCParameter& ProxyParameter);` — `UFUNCTION(Server, unreliable, WithValidation)` — The actual ServerRPC. This needs to be a UFUNCTION but is generic and not dependent on the simulation instance
- L60 _protected member_ `FNetworkPredictionProxy NetworkPredictionProxy;` — `UPROPERTY(Replicated, transient)` — Proxy to interface with the NetworkPrediction system
- L64 _protected member_ `FReplicationProxy ReplicationProxy_ServerRPC;` — `UPROPERTY()` — ReplicationProxies are just pointers to the data/NetSerialize functions within the NetworkSim
- L69 _private member_ `FReplicationProxy ReplicationProxy_Autonomous;` — `UPROPERTY(Replicated, transient)`
- L72 _private member_ `FReplicationProxy ReplicationProxy_Simulated;` — `UPROPERTY(Replicated, transient)`
- L75 _private member_ `FReplicationProxy ReplicationProxy_Replay;` — `UPROPERTY(Replicated, transient)`
- L78 _private member_ `FNetBitWriter ServerRPCParamBitWriter;` — Iris support: used for writing server RPC parameter bits.
- L81 _private member_ `FNetBitReader ServerRPCParamBitReader;` — Iris support: used for reading server RPC parameter bits.
- L86 _protected function_ `FReplicationProxySet GetReplicationProxies()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NETWORKPREDICTION_API`
- L13 _namespace_ `namespace EEndPlayReason`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionConditionalState.h` (Public)


#### struct `TConditionalState`  
`template<typename TestType, typename UnderlyingType=TestType> struct TConditionalState`  
_L7-27_
- L11 _public function_ `operator UnderlyingType*()`
- L13 _public function_ `const UnderlyingType* operator->() const`
- L14 _public function_ `UnderlyingType* operator->()`
- L16 _public function_ `UnderlyingType* Get()`
- L17 _public function_ `const UnderlyingType* Get() const`
- L19 _public function_ `void CopyTo(UnderlyingType* Dest) const`
- L26 _private member_ `UnderlyingType State;`
- L34 _public function_ `operator void*() const`
- L36 _public function_ `const void* operator->() const`
- L37 _public function_ `void* operator->()`
- L39 _public function_ `void* Get()`
- L40 _public function_ `const void* Get() const`
- L42 _public function_ `void CopyTo(void* Dest) const`

#### enum `TConditionalState::(anonymous)`  
`enum`  
_L9-9_

#### struct `TConditionalState`  
`template<typename UnderlyingType> struct TConditionalState<void, UnderlyingType>`  
_L30-43_
- L11 _public function_ `operator UnderlyingType*()`
- L13 _public function_ `const UnderlyingType* operator->() const`
- L14 _public function_ `UnderlyingType* operator->()`
- L16 _public function_ `UnderlyingType* Get()`
- L17 _public function_ `const UnderlyingType* Get() const`
- L19 _public function_ `void CopyTo(UnderlyingType* Dest) const`
- L26 _private member_ `UnderlyingType State;`
- L34 _public function_ `operator void*() const`
- L36 _public function_ `const void* operator->() const`
- L37 _public function_ `void* operator->()`
- L39 _public function_ `void* Get()`
- L40 _public function_ `const void* Get() const`
- L42 _public function_ `void CopyTo(void* Dest) const`

#### enum `TConditionalState::(anonymous)`  
`enum`  
_L32-32_

#### Free symbols / members of external scopes

- L9 _enumerator_ `enum { Valid = true }; operator UnderlyingType*() { return &State; } const UnderlyingType* operator->() const { return &State; } UnderlyingType* operator->() { return &State; } UnderlyingType* Get() { return &State; }` (scope `TConditionalState::__anond9e0f4820103`)
- L32 _enumerator_ `enum { Valid = false }; operator void*() const { return nullptr; } const void* operator->() const { return nullptr; } void* operator->() { return nullptr; } void* Get() { return nullptr; }` (scope `TConditionalState::__anond9e0f4820203`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionConfig.h` (Public)


#### enum `ENetworkPredictionTickingPolicy`  
`enum class ENetworkPredictionTickingPolicy : uint8`  
_L9-17_
- reflection: `UENUM()`
- desc: Must be kept in sync with ENP_TickingPolicy
- L12 _public enumerator_ `Independent = 1 << 0` — Client ticks at local frame rate. Server ticks clients independently at client input cmd rate.
- L14 _public enumerator_ `Fixed = 1 << 1` — Everyone ticks at same fixed rate. Supports group rollback.
- L16 _public enumerator_ `All = Independent | Fixed UMETA(Hidden)`

#### enum `ENetworkPredictionLocalInputPolicy`  
`enum class ENetworkPredictionLocalInputPolicy : uint8`  
_L20-26_
- L23 _public enumerator_ `Passive` — Up to the user to write input via FNetSimProxy::WriteInputCmd.
- L25 _public enumerator_ `PollPerSimFrame` — ProduceInput is called on the driver before every simulation frame. This may be necessary for things like aim assist and fixed step simulations that run multiple sim frames per engine frame

#### enum `ENetworkLOD`  
`enum class ENetworkLOD : uint8`  
_L30-37_
- reflection: `UENUM()`
- desc: Must be kept in sync with ENP_NetworkLOD. Note: SimExtrapolate Not currently implemented so it is hidden
- L32 _public enumerator_ `Interpolated = 1 << 0`
- L33 _public enumerator_ `SimExtrapolate = 1 << 1 UMETA(Hidden)`
- L34 _public enumerator_ `ForwardPredict = 1 << 2`
- L36 _public enumerator_ `All = Interpolated | SimExtrapolate | ForwardPredict UMETA(Hidden)`

#### struct `FNetworkPredictionModelDefCapabilities`  
`struct FNetworkPredictionModelDefCapabilities`  
_L58-70_
- desc: What a ModelDef of capable of
- L69 _public member_ `ENetworkPredictionTickingPolicy SupportedTickingPolicies = ENetworkPredictionTickingPolicy::All;`

#### struct `FNetworkPredictionModelDefCapabilities::FSupportedNetworkLODs`  
`struct FSupportedNetworkLODs`  
_L60-64_
- L62 _public member_ `ENetworkLOD AP;`
- L63 _public member_ `ENetworkLOD SP;`

#### struct `FNetworkPredictionInstanceArchetype`  
`struct FNetworkPredictionInstanceArchetype`  
_L74-81_
- desc: How a registered instance should behave globally. That is, independent of any instance state (local role, connection, significance, local budgets). E.g, everyone agrees on this. This can be changed explicitly by the user or simulation. For example, a sim that transitions between fixed and independent ticking modes.
- L76 _public member_ `ENetworkPredictionTickingPolicy TickingMode;`
- L77 _public function_ `void NetSerialize(FArchive& Ar)`

#### struct `FNetworkPredictionInstanceConfig`  
`struct FNetworkPredictionInstanceConfig`  
_L87-91_
- desc: The config should tell us what services we should be subscribed to. See UNetworkPredictionWorldManager::ConfigureInstance This probably needs to be split into two parts: 1. What settings/config that the server is authority over and must be agreed on (TickingPolicy) 2. What are the local settings that can be lodded around?
- L89 _public member_ `ENetworkPredictionLocalInputPolicy InputPolicy = ENetworkPredictionLocalInputPolicy::Passive;`
- L90 _public member_ `ENetworkLOD NetworkLOD = ENetworkLOD::ForwardPredict;`

#### Free symbols / members of external scopes

- L18 _prototype_ `ENUM_CLASS_FLAGS(ENetworkPredictionTickingPolicy);`
- L38 _prototype_ `ENUM_CLASS_FLAGS(ENetworkLOD);`
- L40 _function_ `static constexpr ENetworkLOD GetHighestNetworkLOD(ENetworkLOD Mask)`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionCueTraits.h` (Public)


#### enum `ESimulationTickContext`  
`enum class ESimulationTickContext : uint8`  
_L26-34_
- desc: When we run a SimulationTick, it will be done under one of these contexts. This isn't NetSimCue specific and probably makes sense to move to the NetSimModel types
- L28 _public enumerator_ `None = 0`
- L29 _public enumerator_ `Authority = 1 << 0` — The authority (usually "server" but could also mean client authoritative client)
- L30 _public enumerator_ `Predict = 1 << 1` — Predicting client: autonomous proxy ("controlling client")
- L31 _public enumerator_ `Resimulate = 1 << 2` — Predicting client during resimulate (simulation rollback into resimulate steps)
- L32 _public enumerator_ `SimExtrapolate = 1 << 3` — Simulation extrapolation: non controlling client (simulated proxy) running the simulation to extrapolate
- L33 _public enumerator_ `ResimExtrapolate = 1 << 4` — Simulation extrapolation during a reconcile (sim rolled back to server state then stepped again to "catch back up")

#### enum `ENetSimCueInvoker`  
`enum class ENetSimCueInvoker : uint8`  
_L38-45_
- desc: High level "who can invoke this". Does not take resimulate into account yet. All combinations of this enum are valid (though Authority | SimExtrapolate is a bit weird maybe)
- L40 _public enumerator_ `Authority = (uint8)ESimulationTickContext::Authority`
- L41 _public enumerator_ `Predict = (uint8)ESimulationTickContext::Predict`
- L42 _public enumerator_ `SimExtrapolate = (uint8)ESimulationTickContext::SimExtrapolate`
- L44 _public enumerator_ `All = Authority | Predict | SimExtrapolate`

#### enum `ENetSimCueReplicationTarget`  
`enum class ENetSimCueReplicationTarget : uint8`  
_L58-66_
- desc: Who a NetSimCue should replicate/be accepted by
- L60 _public enumerator_ `None = 0` — Do not replicate cue to anyone
- L61 _public enumerator_ `AutoProxy = 1 << 0` — Replicate to autonomous proxies (controlling clients)
- L62 _public enumerator_ `SimulatedProxy = 1 << 1` — Replicate to simulated proxies that are running the simulation
- L63 _public enumerator_ `Interpolators = 1 << 2` — Replicate to simulated proxies that are *not* running the simulation themselves (E.,g interpolating)
- L65 _public enumerator_ `All = AutoProxy | SimulatedProxy | Interpolators`

#### struct `NetSimCueTraits::Weak`  
`struct Weak`  
_L89-94_
- desc: Non replicated cue that only plays during "latest" simulate. Will not be played during rewind/resimulate. Lightest weight cue. Best used for cosmetic, non critical events. Footsteps, impact effects, etc.
- L91 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { ENetSimCueInvoker::All };`
- L92 _public member_ `static constexpr bool Resimulate { false };`
- L93 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { ENetSimCueReplicationTarget::None };`

#### struct `NetSimCueTraits::WeakOwningClientOnly`  
`struct WeakOwningClientOnly`  
_L98-103_
- desc: Same as above but will only play on the owning, autonomous proxy client (not on authority, not on simulated clients) Useful if the Cue is needed for only the controlling player, maybe like a HUD/UI notification pop
- L100 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { ENetSimCueInvoker::Predict };`
- L101 _public member_ `static constexpr bool Resimulate { false };`
- L102 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { ENetSimCueReplicationTarget::None };`

#### struct `NetSimCueTraits::WeakClientsOnly`  
`struct WeakClientsOnly`  
_L107-112_
- desc: Same as above but will play on all clients, just not the authority. Useful for something that is purely cosmetic. E.g, does not run on the server but all clients should see it if they are running the sim
- L109 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { ENetSimCueInvoker::Predict | ENetSimCueInvoker::SimExtrapolate };`
- L110 _public member_ `static constexpr bool Resimulate { false };`
- L111 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { ENetSimCueReplicationTarget::None };`

#### struct `NetSimCueTraits::AuthorityOnly`  
`struct AuthorityOnly`  
_L115-120_
- desc: Will only play on the authority path and not replicate to anyone else
- L117 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { ENetSimCueInvoker::Authority };`
- L118 _public member_ `static constexpr bool Resimulate { false };`
- L119 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { ENetSimCueReplicationTarget::None };`

#### struct `NetSimCueTraits::ReplicatedNonPredicted`  
`struct ReplicatedNonPredicted`  
_L124-129_
- desc: Only invoked on authority and will replicate to everyone else. Not predicted so controlling client will see delays! Best for events that are critical that cannot be rolled back/undown and do not need to be predicted.
- L126 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { ENetSimCueInvoker::Authority };`
- L127 _public member_ `static constexpr bool Resimulate { false };`
- L128 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { ENetSimCueReplicationTarget::All };`

#### struct `NetSimCueTraits::ReplicatedXOrPredicted`  
`struct ReplicatedXOrPredicted`  
_L133-138_
- desc: Replicated to interpolating proxies, predicted by autonomous/simulated proxy Best for events you want everyone to see but don't need to get perfect in the predicting cases: doesn't need to rollback and cheap on cpu (no NetIdentical tests on predicted path)
- L135 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { ENetSimCueInvoker::All };`
- L136 _public member_ `static constexpr bool Resimulate { false };`
- L137 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { ENetSimCueReplicationTarget::Interpolators };`

#### struct `NetSimCueTraits::Strong`  
`struct Strong`  
_L142-147_
- desc: Invoked and replicated to all. NetIdentical testing to avoid double playing, rollbackable so that it can (re)play during resimulates Most expensive (bandwidth/CPU) and requires rollback callbacks to be implemented to be correct. But will always be shown "as correct as possible"
- L144 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { ENetSimCueInvoker::All };`
- L145 _public member_ `static constexpr bool Resimulate { true };`
- L146 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { ENetSimCueReplicationTarget::All };`

#### struct `NetSimCueTraits::NonReplicatedResimulated`  
`struct NonReplicatedResimulated`  
_L151-156_
- desc: Non replicated but if a resimulate happens, the cue is undone and replayed. This is not common and doesn't really have a clear use case. But the system can support it.
- L153 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { ENetSimCueInvoker::All };`
- L154 _public member_ `static constexpr bool Resimulate { true };`
- L155 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { ENetSimCueReplicationTarget::None };`

#### struct `TNetSimCueTraitsExplicit`  
`template<ENetSimCueInvoker InInvokeMask, ENetSimCueReplicationTarget InReplicationTarget, bool InResimulate> struct TNetSimCueTraitsExplicit`  
_L161-171_
- desc: Explicit trait settings. This can be used to explicitly set your traits without using a preset.
- L164 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { InInvokeMask };` — Who can Invoke this Cue in their simulation (if this test fails, the Invoke call is suppressed locally)
- L167 _public member_ `static constexpr bool Resimulate { InResimulate };` — Whether the cue will be invoked during resimulates (which will require cue to be rollbackable)
- L170 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { InReplicationTarget };` — Does the cue replicate? (from authority). This will also determine if the cue needs to be saved locally for NetIdentical tests (to avoid double playing)

#### struct `TToVoid`  
`template<typename T> struct TToVoid`  
_L180-183_
- desc: SFINAE helper
- L182 _public typedef_ `using type = void;`

#### struct `THasNetSimCueTraits`  
`template<typename T, typename dummy=void> struct THasNetSimCueTraits`  
_L187-190_
- desc: Helper to see if T has a Traits type or not

#### enum `THasNetSimCueTraits::(anonymous)`  
`enum`  
_L189-189_

#### struct `THasNetSimCueTraits`  
`template<typename T> struct THasNetSimCueTraits<T, typename TToVoid<typename T::Traits>::type>`  
_L193-196_

#### enum `THasNetSimCueTraits::(anonymous)`  
`enum`  
_L195-195_

#### struct `TSelectNetSimCueTraits`  
`template<typename T, bool HasTraits = THasNetSimCueTraits<T>::Value> struct TSelectNetSimCueTraits`  
_L200-203_
- desc: Selects explicit traits set by T
- L202 _public typedef_ `using Traits = typename T::Traits;`
- L209 _public typedef_ `using Traits = NetSimCueTraits::Default;`

#### struct `TSelectNetSimCueTraits`  
`template<typename T> struct TSelectNetSimCueTraits<T, false>`  
_L207-210_
- desc: Fall back to Default traits
- L202 _public typedef_ `using Traits = typename T::Traits;`
- L209 _public typedef_ `using Traits = NetSimCueTraits::Default;`

#### struct `TNetSimCueTraits`  
`template<typename TCue> struct TNetSimCueTraits`  
_L218-226_
- desc: Actual trait struct that we use to look up traits. The ways this can be set: 1. Explicitly specialize TNetSimCueTraits for your type (non intrusive, but does not inherit) 2. Explicitly set Traits inside your struct. E.g: using Traits = TNetSimCueTraits_Strong; (intrustive but more concise, does support inherited types) 3. Automatically falls back to NetSimCueTraits::Default if not explicitly set above
- L220 _public typedef_ `using Traits = typename TSelectNetSimCueTraits<TCue>::Traits;`
- L222 _public member_ `static constexpr ENetSimCueInvoker InvokeMask { Traits::InvokeMask };`
- L223 _public member_ `static constexpr bool Resimulate { Traits::Resimulate };`
- L224 _public member_ `static constexpr ENetSimCueReplicationTarget ReplicationTarget { Traits::ReplicationTarget };`
- L225 _public function_ `static constexpr ESimulationTickContext SimTickMask()`

#### struct `TNetSimCueTypeRequirements`  
`template <typename TCue> struct TNetSimCueTypeRequirements`  
_L230-239_
- desc: Type requirements: helper to determine if NetSerialize/NetIdentical functions need to be defined for user types based on the above traits

#### enum `TNetSimCueTypeRequirements::(anonymous)`  
``  
_L233-238_

#### struct `THasNetIdenticalHelper`  
`template<typename TCue> struct THasNetIdenticalHelper`  
_L250-254_
- desc: Helper to compile time check if NetIdentical exists (since argument is template type, must be wrapped in helper struct)
- L252 _public prototype_ `GENERATE_MEMBER_FUNCTION_CHECK(NetIdentical, bool, const, const TCue&);`

#### enum `THasNetIdenticalHelper::(anonymous)`  
`enum`  
_L253-253_

#### struct `TNetCueNetIdenticalHelper`  
`template<typename TCue, bool Enabled=THasNetIdenticalHelper<TCue>::Value> struct TNetCueNetIdenticalHelper`  
_L258-261_
- desc: Helper to call NetIdentical if type defines it
- L260 _public function_ `static bool CallNetIdenticalOrNot(const TCue& Cue, const TCue& Other)` — This should never be hit by cue types that don't need to NetIdentical

#### struct `TNetCueNetIdenticalHelper`  
`template<typename TCue> struct TNetCueNetIdenticalHelper<TCue, true>`  
_L264-267_
- L260 _public function_ `static bool CallNetIdenticalOrNot(const TCue& Cue, const TCue& Other)` — This should never be hit by cue types that don't need to NetIdentical

#### struct `TNetCueNetSerializeHelper`  
`template<typename TCue, bool Enabled=THasMemberFunction_NetSerialize<TCue>::Value> struct TNetCueNetSerializeHelper`  
_L271-274_
- desc: Helper to call NetSerialize if type defines it
- L273 _public function_ `static void CallNetSerializeOrNot(TCue& Cue, FArchive& Ar)` — This should never be hit by cue types that don't need to NetSerialize

#### struct `TNetCueNetSerializeHelper`  
`template<typename TCue> struct TNetCueNetSerializeHelper<TCue, true>`  
_L277-280_
- L273 _public function_ `static void CallNetSerializeOrNot(TCue& Cue, FArchive& Ar)` — This should never be hit by cue types that don't need to NetSerialize

#### Free symbols / members of external scopes

- L35 _prototype_ `ENUM_CLASS_FLAGS(ESimulationTickContext);`
- L46 _prototype_ `ENUM_CLASS_FLAGS(ENetSimCueInvoker);`
- L49 _function_ `static constexpr ESimulationTickContext GetSimTickMask(const ENetSimCueInvoker Invoker, const bool bAllowResimulate)` — Turns "Who can invoke this" + "Does this play during resimulate" into the final ESimulationTickContext mask we use at runtime. This is done so users can't make invalid configurations (like "Authority | Resimulate")
- L67 _prototype_ `ENUM_CLASS_FLAGS(ENetSimCueReplicationTarget);`
- L82 _namespace_ `namespace NetSimCueTraits`
- L85 _typedef_ `using Default = struct Weak;` (scope `NetSimCueTraits`) — Default Traits: if you do not explicitly set Traits on your class, this is what it defaults to
- L189 _enumerator_ `enum { Value = false };` (scope `THasNetSimCueTraits::__anon3df7f5a10103`)
- L195 _enumerator_ `enum { Value = true };` (scope `THasNetSimCueTraits::__anon3df7f5a10203`)
- L235 _enumerator_ `RequiresNetSerialize = (TNetSimCueTraits<TCue>::ReplicationTarget != ENetSimCueReplicationTarget::None)` (scope `TNetSimCueTypeRequirements::__anon3df7f5a10303`) — NetSerialize is required if we ever need to replicate
- L237 _enumerator_ `RequiresNetIdentical = (TNetSimCueTraits<TCue>::ReplicationTarget != ENetSimCueReplicationTarget::None) || (TNetSimCueTraits<TCue>::Resimulate)` (scope `TNetSimCueTypeRequirements::__anon3df7f5a10303`) — Likewise for NetIdentical, but also if we plan to invoke during Resimulate too (even if non replicated, we use NetIdentical for comparisons. though this is probably a non practical use case).
- L253 _enumerator_ `enum { Value = THasMemberFunction_NetIdentical<TCue>::Value };` (scope `THasNetIdenticalHelper::__anon3df7f5a10403`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionCues.h` (Public)


#### struct `FNetSimCueWrapperBase`  
`struct FNetSimCueWrapperBase`  
_L53-60_
- L55 _public prototype_ `virtual ~FNetSimCueWrapperBase() = default;`
- L56 _public prototype_ `virtual void NetSerialize(FArchive& Ar) = 0;`
- L57 _public prototype_ `virtual bool NetIdentical(const void* OtherCueData) const = 0;`
- L58 _public prototype_ `virtual void* CueData() const = 0;`
- L59 _public prototype_ `virtual ENetSimCueReplicationTarget GetReplicationTarget() const = 0;`

#### struct `TNetSimCueWrapper`  
`template<typename TCue> struct TNetSimCueWrapper : FNetSimCueWrapperBase`  
_L63-92_
- inherits: `FNetSimCueWrapperBase`
- L65 _public prototype_ `TNetSimCueWrapper() = default;`
- L68 _public function_ `template <typename... ArgsType> TNetSimCueWrapper(ArgsType&&... Args) : Instance( MoveTempIfPossible(Forward<ArgsType>(Args))... )`
- L71 _public function_ `void NetSerialize(FArchive& Ar) override final`
- L76 _public function_ `bool NetIdentical(const void* OtherCueData) const override final`
- L81 _public function_ `void* CueData() const override final`
- L86 _public function_ `ENetSimCueReplicationTarget GetReplicationTarget() const override final`
- L91 _public member_ `TCue Instance;`

#### struct `FNetSimCueCallbacks`  
`struct FNetSimCueCallbacks`  
_L98-105_
- L101 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRollback) FOnRollback OnRollback;` — Callback to rollback any side effects of the cue.

#### struct `FNetSimCueSystemParamemters`  
`struct FNetSimCueSystemParamemters`  
_L108-115_
- desc: System parameters for NetSimCue events
- L111 _public member_ `const int32& TimeSinceInvocation;` — How much simulation time has passed since this cue was invoked. This will be 0 in authority/predict contexts, but when invoked via replication this will tell you how long ago it happened, relative to local simulation time.
- L114 _public member_ `FNetSimCueCallbacks* Callbacks;` — Callback structure if applicable. This will be null on non-rewindable cues as well as execution contexts where rollbacks wont happen (e.g, authority).

#### class `FGlobalCueTypeTable`  
`class FGlobalCueTypeTable`  
_L122-267_
- L131 _public function_ `template<typename TCue> FORCENOINLINE static void RegisterCueType(const FString& TypeName)`
- L152 _public function_ `template<typename TCue> static void UnregisterCueType()`
- L179 _public function_ `static bool IsRegisterationTypeInfoDirty()`
- L181 _public function_ `static FDelegateHandle RegisterDispatchTableCallback(const TFunction<void()>& RegisterFunc)`
- L189 _public function_ `static void UnregisterDispatchTableCallback(FDelegateHandle Handle)`
- L202 _public function_ `void FinalizeCueTypes()`
- L230 _public function_ `static FGlobalCueTypeTable& Get()`
- L235 _public function_ `FNetSimCueWrapperBase* Allocate(FNetSimCueTypeId ID)`
- L240 _public function_ `FString GetTypeName(FNetSimCueTypeId ID) const`
- L262 _private prototype_ `static FRegisteredCueTypeInfo& GetRegistedTypeInfo();` — The registered type info lives in its own inlined static function to avoid static variable initialization order conflicts
- L264 _private member_ `TMap<FNetSimCueTypeId, FTypeInfo> TypeInfoMap;`
- L266 _private member_ `static FGlobalCueTypeTable Singleton;`

#### struct `FGlobalCueTypeTable::FTypeInfo`  
`struct FTypeInfo`  
_L247-252_
- L249 _public member_ `FNetSimCueTypeId* IDPtr = nullptr;`
- L250 _public member_ `TFunction<FNetSimCueWrapperBase*()> AllocateFunc;`
- L251 _public member_ `FString TypeName;`

#### struct `FGlobalCueTypeTable::FRegisteredCueTypeInfo`  
`struct FRegisteredCueTypeInfo`  
_L254-259_
- L256 _public member_ `TArray<FTypeInfo> CueTypes;`
- L257 _public member_ `FSimpleMulticastDelegate InitDispatchTablesDelegate;`
- L258 _public member_ `bool bDirty = false;`

#### struct `FSavedCue`  
`struct FSavedCue`  
_L273-359_
- L275 _public function_ `FSavedCue(bool bInNetConfirmed) : bNetConfirmed(bInNetConfirmed)`
- L277 _public prototype_ `FSavedCue(const FSavedCue&) = delete;`
- L278 _public prototype_ `FSavedCue& operator=(const FSavedCue&) = delete;`
- L280 _public prototype_ `FSavedCue(FSavedCue&&) = default;`
- L281 _public prototype_ `FSavedCue& operator=(FSavedCue&&) = default;`
- L283 _public function_ `FSavedCue(const FNetSimCueTypeId& InId, const int32& InFrame, const int32& InTime, const bool& bInAllowRollback, const bool& bInNetConfirmed, const bool& bInResimulates, FNetSimCueWrapperBase* Cue) : ID(InId), Frame(InFrame), Time(InTime), CueInstance(Cue), bAllowRollback(bInAllowRollback), bNetConfirmed(bInNetConfirmed), bResimulates(bInResimulates), ReplicationTarget(Cue->GetReplicationTarget())`
- L289 _public function_ `void NetSerialize(FArchive& Ar, const bool bSerializeFrameNumber)`
- L327 _public function_ `bool NetIdentical(FSavedCue& OtherCue) const` — Test NetUniqueness against another saved cue
- L334 _public function_ `template<typename TCue> bool NetIdentical(TCue& OtherCue) const` — Test NetUniqueness against an actual cue instance
- L340 _public function_ `FString GetDebugName() const`
- L345 _public member_ `FNetSimCueTypeId ID = 0;`
- L346 _public member_ `int32 Frame = INDEX_NONE;`
- L347 _public member_ `int32 Time = 0;`
- L348 _public member_ `TUniquePtr<FNetSimCueWrapperBase> CueInstance;`
- L349 _public member_ `FNetSimCueCallbacks Callbacks;`
- L351 _public member_ `bool bDispatched = false;` — Cue has been dispatched to the local handler. Never dispatch twice.
- L352 _public member_ `bool bAllowRollback = false;` — Cue supports rolling back. ie., we should pass the user valid FNetSimCueCallbacks rollback callback (note this is "this saved cue" specifically, not "this cue type". E.g, on authority, bAllowRollback is always false)
- L353 _public member_ `bool bNetConfirmed = false;` — This cue has been net confirmed, meaning we received it directly via replication or we received a replicated cue that matched this one that was locally predicted.
- L355 _public member_ `bool bResimulates = false;` — Whether this cue supports invocation during resimulation. Needed to set bResimulatePendingRollback
- L356 _public member_ `bool bPendingResimulateRollback = false;` — Rollback is pending due to resimulation (unless CUe is matched with an Invocation during the resimulate)
- L358 _public member_ `ENetSimCueReplicationTarget ReplicationTarget;`

#### class `TCueDispatchTable`  
`template<typename TCueHandler> class TCueDispatchTable`  
_L367-426_
- L370 _public function_ `static TCueDispatchTable<TCueHandler>& Get()`
- L377 _public function_ `template<typename TCue> void RegisterType()` — All types that the receiver can handle must be registered here. This is where we create the TFunction to call ::HandleCue
- L391 _public function_ `void Reset()`
- L396 _public function_ `void Dispatch(FSavedCue& SavedCue, TCueHandler& Handler, const int32& TimeSinceInvocation)`
- L418 _private member_ `static TCueDispatchTable<TCueHandler> Singleton;`
- L425 _private member_ `TMap<FNetSimCueTypeId, FCueTypeInfo> CueTypeInfoMap;`

#### struct `TCueDispatchTable::FCueTypeInfo`  
`struct FCueTypeInfo`  
_L420-423_
- L422 _public member_ `TFunction<void(FNetSimCueWrapperBase* Cue, TCueHandler& Handler, const FNetSimCueSystemParamemters& SystemParameters)> Dispatch;`

#### struct `FCueDispatcherTraitsBase`  
`struct FCueDispatcherTraitsBase`  
_L438-444_
- desc: Traits for TNetSimCueDispatcher
- L442 _public function_ `static constexpr int32 ReplicationWindowMS()` — Window for replicating a NetSimCue. That is, after a cue is invoked, it has ReplicationWindow time before it will be pruned. If a client does not get a net update for the sim in this window, they will miss the event.
- L443 _public function_ `static constexpr int32 ReplicationWindowFrames()` — for frame based cases (FIXME: time makes more sense but we don't have good way to map at this level)

#### struct `TCueDispatcherTraits`  
`template<typename T> struct TCueDispatcherTraits : public FCueDispatcherTraitsBase`  
_L445-445_
- inherits: `FCueDispatcherTraitsBase`

#### struct `FNetSimCueDispatcher`  
`struct FNetSimCueDispatcher`  
_L448-565_
- desc: Non-templated, "networking model independent" base: this is what the pure simulation code gets to invoke cues.
- L450 _public prototype_ `virtual ~FNetSimCueDispatcher() = default;`
- L462 _public function_ `template<typename T, typename... ArgsType> void Invoke(ArgsType&&... Args)`
- L534 _public prototype_ `virtual FString GetDebugName() const = 0;`
- L538 _protected function_ `bool EnsureValidContext()`
- L551 _protected member_ `TArray<FSavedCue> SavedCues;` — Cues that must be saved for some period of time, either for replication or for uniqueness testing
- L552 _protected member_ `TArray<FSavedCue> TransientCues;` — Cues that are dispatched on this frame and then forgotten about
- L553 _protected function_ `TArray<FSavedCue>& GetBuffer(const bool& bTransient)`
- L555 _protected member_ `FContext Context;`
- L556 _protected member_ `int32 RollbackFrame = INDEX_NONE;` — Frame# of last rollback, reset after dispatching
- L561 _public function_ `void PushContext(const FContext& InContext)` — Push/pop simulation context.
- L562 _public function_ `void PopContext()`
- L563 _public function_ `const FContext& GetContext() const`

#### struct `FNetSimCueDispatcher::FContext`  
`struct FContext`  
_L544-549_
- desc: Sim Context: the Sim has to tell the dispatcher what its doing so that it can decide if it should suppress Invocations or not
- L546 _public member_ `int32 Frame = INDEX_NONE;`
- L547 _public member_ `int32 CurrentSimTime = 0;`
- L548 _public member_ `ESimulationTickContext TickContext;`

#### struct `TNetSimCueDispatcher`  
`template<typename ModelDef=void> struct TNetSimCueDispatcher : public FNetSimCueDispatcher`  
_L569-856_
- inherits: `FNetSimCueDispatcher`
- desc: Templated cue dispatcher that can be specialized per networking model definition. This is what the system actually uses internally, but is not exposed to user code.
- L571 _public typedef_ `using DriverType = typename ModelDef::Driver;`
- L575 _public function_ `void NetSendSavedCues(FArchive& Ar, ENetSimCueReplicationTarget ReplicationMask, bool bSerializeFrameNumber)` — Serializes all saved cues bSerializeFrameNumber - whether to serialize Frame# or Time to this target. Frame is more accurate but some cases require time based replication.
- L602 _public function_ `void NetRecvSavedCues(FArchive& Ar, const bool bSerializeFrameNumber, const int32 InLastRecvFrame, const int32 InLastRecvTime)`
- L676 _public function_ `template<typename T> void DispatchCueRecord(T& Handler, const int32 SimFrame, const int32 CurrentSimTime, const int32 FixedTimeStepMS)` — Dispatches and prunes saved/transient cues
- L804 _public function_ `void NotifyRollback(int32 InRollbackFrame)` — Tell dispatcher that we've rolled back to a new simulation time (resimulate steps to follow, most likely)
- L830 _public function_ `void SetReceiveReplicationTarget(ENetSimCueReplicationTarget InReplicationMask)` — Set which cues we should accept locally (if they get sent to us)
- L835 _public member_ `DriverType* Driver = nullptr;`
- L836 _public function_ `FString GetDebugName() const final override`
- L852 _private member_ `ENetSimCueReplicationTarget RecvReplicationMask;`
- L854 _private member_ `int32 LastRecvFrame = INDEX_NONE;`
- L855 _private member_ `int32 LastRecvMS = 0;`

#### struct `TNetSimCueTypeAutoRegisterHelper`  
`template<typename TCue> struct TNetSimCueTypeAutoRegisterHelper`  
_L869-880_
- L871 _public function_ `TNetSimCueTypeAutoRegisterHelper(const FString& Name)`
- L876 _public function_ `~TNetSimCueTypeAutoRegisterHelper()`

#### struct `TNetSimCueHandlerAutoRegisterHelper`  
`template<typename THandler> struct TNetSimCueHandlerAutoRegisterHelper`  
_L889-907_
- L891 _public function_ `TNetSimCueHandlerAutoRegisterHelper()`
- L900 _public function_ `~TNetSimCueHandlerAutoRegisterHelper()`
- L906 _private member_ `FDelegateHandle Handle;`

#### struct `TNetSimCueSetHandlerAutoRegisterHelper`  
`template<typename THandler, typename TCueSet> struct TNetSimCueSetHandlerAutoRegisterHelper`  
_L915-933_
- L917 _public function_ `TNetSimCueSetHandlerAutoRegisterHelper()`
- L926 _public function_ `~TNetSimCueSetHandlerAutoRegisterHelper()`
- L932 _private member_ `FDelegateHandle Handle;`

#### Free symbols / members of external scopes

- L38 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkPredictionCues, Display, All);`
- L41 _macro_ `#define NETSIMCUE_TYPEID_TYPE uint8;`
- L44 _typedef_ `using FNetSimCueTypeId = NETSIMCUE_TYPEID_TYPE;`
- L101 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRollback) FOnRollback OnRollback;` — Callback to rollback any side effects of the cue.
- L142 _function_ `&TCue::ID, []()` (scope `FGlobalCueTypeTable::RegisterCueType`)
- L210 _function_ `RegisteredTypes.CueTypes.Sort([](const FTypeInfo& LHS, const FTypeInfo& RHS) { return LHS.TypeName < RHS.TypeName; });` (scope `FGlobalCueTypeTable::FinalizeCueTypes`)
- L385 _function_ `` (scope `TCueDispatchTable::RegisterType`)
- L429 _member_ `template<typename TCueHandler> TCueDispatchTable<TCueHandler> TCueDispatchTable<TCueHandler>::Singleton;` (scope `TCueDispatchTable<TCueHandler>`)
- L678 _function_ `auto CalcPrune = [](int32 Head, int32 Confirm, int32 Window)` (scope `TNetSimCueDispatcher::DispatchCueRecord`)
- L863 _macro_ `#define NETSIMCUE_BODY() static FNetSimCueTypeId ID` — Body of NetSimCue header. Gives type a static ID to be identified with
- L883 _macro_ `#define NETSIMCUE_REGISTER(X, STR) FNetSimCueTypeId X::ID=0; TNetSimCueTypeAutoRegisterHelper<X> NetSimCueAr_##X(STR);` — Note this also defines the internal static ID for the cue type
- L894 _function_ `` (scope `TNetSimCueHandlerAutoRegisterHelper::TNetSimCueHandlerAutoRegisterHelper`)
- L909 _macro_ `#define NETSIMCUEHANDLER_REGISTER(X) TNetSimCueHandlerAutoRegisterHelper<X> NetSimCueHandlerAr_##X;`
- L920 _function_ `` (scope `TNetSimCueSetHandlerAutoRegisterHelper::TNetSimCueSetHandlerAutoRegisterHelper`)
- L935 _macro_ `#define NETSIMCUESET_REGISTER(THandler, TCueSet) TNetSimCueSetHandlerAutoRegisterHelper<THandler,TCueSet> NetSimCueSetHandlerAr_##THandler_##TCueSet;`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionDebug.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace NetworkPredictionDebug`
- L11 _prototype_ `void DrawDebugOutline(FTransform Transform, FBox BoundingBox, FColor Color, float Lifetime);` (scope `NetworkPredictionDebug`)
- L12 _prototype_ `void DrawDebugText3D(const TCHAR* Str, FTransform Transform, FColor, float Lifetime);` (scope `NetworkPredictionDebug`)
- L13 _prototype_ `UObject* FindReplicatedObjectOnPIEServer(UObject* ClientObject);` (scope `NetworkPredictionDebug`)
- L14 _prototype_ `FNetworkGUID FindObjectNetGUID(UObject* Obj);` (scope `NetworkPredictionDebug`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionDriver.h` (Public)


#### struct `FNetworkPredictionDriverBase`  
`template<typename ModelDef> struct FNetworkPredictionDriverBase`  
_L62-668_
- L64 _public typedef_ `using DriverType = typename ModelDef::Driver;`
- L65 _public typedef_ `using Simulation = typename ModelDef::Simulation;`
- L66 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L67 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L68 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L69 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L71 _public function_ `static constexpr bool HasNpState()`
- L72 _public function_ `static constexpr bool HasDriver()`
- L73 _public function_ `static constexpr bool HasSimulation()`
- L74 _public function_ `static constexpr bool HasInput()`
- L77 _public function_ `static constexpr FNetworkPredictionModelDefCapabilities GetCapabilities()` — Defines what the ModelDef can do. This is a compile time thing only.
- L93 _public function_ `static bool GetDefaultArchetype(FNetworkPredictionInstanceArchetype& Archetype, ENetworkPredictionTickingPolicy PreferredTickingPolicy)` — Defines the default settings for a spawn instance.
- L112 _public function_ `static FNetworkPredictionInstanceConfig GetConfig(const FNetworkPredictionInstanceArchetype& Archetype, const FNetworkPredictionSettings& GlobalSettings, ENetRole Role, bool bHasNetConnection)` — Defines the default config for an instance, given their archetype and Role/NetConnection
- L149 _public function_ `static void GetDebugString(AActor* Actor, FStringBuilderBase& Builder)`
- L154 _public function_ `static void GetDebugString(UActorComponent* ActorComp, FStringBuilderBase& Builder)`
- L159 _public function_ `static void GetDebugString(void* NoDriver, FStringBuilderBase& Builder)`
- L164 _public function_ `static void GetDebugStringFull(AActor* Actor, FStringBuilderBase& Builder)`
- L169 _public function_ `static void GetDebugStringFull(UActorComponent* ActorComp, FStringBuilderBase& Builder)`
- L174 _public function_ `static void GetDebugStringFull(void* NoDriver, FStringBuilderBase& Builder)`
- L179 _public function_ `static void GetTraceString(UActorComponent* ActorComp, FStringBuilderBase& Builder)`
- L184 _public function_ `static void GetTraceString(AActor* Actor, FStringBuilderBase& Builder)`
- L189 _public function_ `static void GetTraceString(void* NoDriver, FStringBuilderBase& Builder)`
- L194 _public function_ `static FTransform GetDebugWorldTransform(AActor* DriverActor)`
- L199 _public function_ `static FTransform GetDebugWorldTransform(UActorComponent* DriverComponent)`
- L204 _public function_ `static FTransform GetDebugWorldTransform(void* NoDriver)`
- L210 _public function_ `static FBox GetDebugBoundingBox(AActor* DriverActor)`
- L215 _public function_ `static FBox GetDebugBoundingBox(UActorComponent* DriverComponent)`
- L220 _public function_ `static FBox GetDebugBoundingBox(void* NoDriver)`
- L226 _public function_ `static void DrawDebugOutline(DriverType* Driver, FColor Color, float Lifetime=0.f)`
- L231 _public function_ `static void DrawDebugText3D(DriverType* Driver, const TCHAR* Str, FColor Color, float Lifetime=0.f, float ZOffset=50.f)`
- L247 _public function_ `static void InitializeSimulationState(DriverType* Driver, FNetworkPredictionStateView* View)`
- L253 _public function_ `static void InitializeSimulationState(DriverType* Driver, SyncType* Sync, AuxType* Aux)`
- L264 _public member_ `static constexpr bool HasInitializeSimulationState = TModels_V<CInitializeSimulationStateFuncable, DriverType, SyncType, AuxType>;`
- L267 _public function_ `template<bool HasFunc=HasInitializeSimulationState> static typename TEnableIf<HasFunc>::Type CallInitializeSimulationStateMemberFunc(DriverType* Driver, SyncType* Sync, AuxType* Aux)`
- L274 _public function_ `template<bool HasFunc=HasInitializeSimulationState> static typename TEnableIf<!HasFunc>::Type CallInitializeSimulationStateMemberFunc(DriverType* Driver, SyncType* Sync, AuxType* Aux)`
- L287 _public function_ `static void ProduceInput(DriverType* Driver, int32 DeltaTimeMS, InputType* InputCmd)`
- L298 _public member_ `static constexpr bool HasProduceInput = TModels_V<CProduceInputMemberFuncable, DriverType, int32, InputType>;`
- L301 _public function_ `template<bool HasFunc=HasProduceInput> static typename TEnableIf<HasFunc>::Type CallProduceInputMemberFunc(DriverType* Driver, int32 DeltaTimeMS, InputType* InputCmd)`
- L308 _public function_ `template<bool HasFunc=HasProduceInput> static typename TEnableIf<!HasFunc>::Type CallProduceInputMemberFunc(DriverType* Driver, int32 DeltaTimeMS, InputType* InputCmd)`
- L318 _public function_ `static void FinalizeFrame(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L329 _public member_ `static constexpr bool HasFinalizeFrame = TModels_V<CFinalizeFrameMemberFuncable, DriverType, SyncType, AuxType>;`
- L332 _public function_ `template<bool HasFunc=HasFinalizeFrame> static typename TEnableIf<HasFunc>::Type CallFinalizeFrameMemberFunc(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L339 _public function_ `template<bool HasFunc=HasFinalizeFrame> static typename TEnableIf<!HasFunc>::Type CallFinalizeFrameMemberFunc(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L350 _public function_ `static void FinalizeSmoothingFrame(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L361 _public member_ `static constexpr bool HasFinalizeSmoothingFrame = TModels_V<CFinalizeSmoothingFrameMemberFuncable, DriverType, SyncType, AuxType>;`
- L364 _public function_ `template<bool HasFunc=HasFinalizeSmoothingFrame> static typename TEnableIf<HasFunc>::Type CallFinalizeSmoothingFrameMemberFunc(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L371 _public function_ `template<bool HasFunc=HasFinalizeSmoothingFrame> static typename TEnableIf<!HasFunc>::Type CallFinalizeSmoothingFrameMemberFunc(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L385 _public function_ `static void RestoreFrame(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L396 _public member_ `static constexpr bool HasRestoreFrame = TModels_V<CRestoreFrameMemberFuncable, DriverType, SyncType, AuxType>;`
- L399 _public function_ `template<bool HasFunc=HasRestoreFrame> static typename TEnableIf<HasFunc>::Type CallRestoreFrameMemberFunc(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L406 _public function_ `template<bool HasFunc=HasRestoreFrame> static typename TEnableIf<!HasFunc>::Type CallRestoreFrameMemberFunc(DriverType* Driver, const SyncType* SyncState, const AuxType* AuxState)`
- L421 _public function_ `static void CallServerRPC(DriverType* Driver)`
- L432 _public member_ `static constexpr bool HasCallServerRPC = TModels_V<CCallServerRPCMemberFuncable, DriverType>;`
- L435 _public function_ `template<bool HasFunc=HasCallServerRPC> static typename TEnableIf<HasFunc>::Type CallServerRPCMemberFunc(DriverType* Driver)`
- L442 _public function_ `template<bool HasFunc=HasCallServerRPC> static typename TEnableIf<!HasFunc>::Type CallServerRPCMemberFunc(DriverType* Driver)`
- L454 _public function_ `template<typename InDriverType=DriverType> static void DispatchCues(TNetSimCueDispatcher<ModelDef>* CueDispatcher, InDriverType* Driver, int32 SimFrame, int32 SimTimeMS, const int32 FixedStepMS)`
- L460 _public function_ `static void DispatchCues(TNetSimCueDispatcher<ModelDef>* CueDispatcher, void* Driver, int32 SimFrame, int32 SimTimeMS, const int32 FixedStepMS)`
- L471 _public function_ `static bool ShouldReconcile(DriverType* Driver, const TSyncAuxPair<StateTypes>& Predicted, const TSyncAuxPair<StateTypes>& Authority)`
- L494 _public member_ `static constexpr bool HasShouldReconcileSyncState = TModels_V<CShouldReconcileSyncStateMemberFuncable, DriverType, SyncType, SyncType>;`
- L495 _public member_ `static constexpr bool HasShouldReconcileAuxState = TModels_V<CShouldReconcileAuxStateMemberFuncable, DriverType, AuxType, AuxType>;`
- L499 _public function_ `template<bool HasFunc = HasShouldReconcileSyncState> static typename TEnableIf<HasFunc, bool>::Type CallShouldReconcileSyncStateMemberFunc(DriverType* Driver, const SyncType* Predicted, const SyncType* Authority)`
- L506 _public function_ `template<bool HasFunc = HasShouldReconcileSyncState> static typename TEnableIf<!HasFunc, bool>::Type CallShouldReconcileSyncStateMemberFunc(DriverType* Driver, const SyncType* Predicted, const SyncType* Authority)`
- L512 _public function_ `static bool CallShouldReconcileSyncStateMemberFunc(DriverType* Driver, const void* Predicted, const void* Authority)`
- L519 _public function_ `template<bool HasFunc = HasShouldReconcileAuxState> static typename TEnableIf<HasFunc, bool>::Type CallShouldReconcileAuxStateMemberFunc(DriverType* Driver, const AuxType* Predicted, const AuxType* Authority)`
- L526 _public function_ `template<bool HasFunc = HasShouldReconcileAuxState> static typename TEnableIf<!HasFunc, bool>::Type CallShouldReconcileAuxStateMemberFunc(DriverType* Driver, const AuxType* Predicted, const AuxType* Authority)`
- L532 _public function_ `static bool CallShouldReconcileAuxStateMemberFunc(DriverType* Driver, const void* Predicted, const void* Authority)`
- L542 _public function_ `static void Interpolate(const TSyncAuxPair<StateTypes>& From, const TSyncAuxPair<StateTypes>& To, const float PCT, SyncType* SyncOut, AuxType* AuxOut)`
- L549 _public function_ `template<typename StateType> static void InterpolateState(const StateType* From, const StateType* To, const float PCT, StateType* Out)`
- L554 _public function_ `static void InterpolateState(const void* From, const void* To, const float PCT, void* Out)`
- L564 _public function_ `static void SetHiddenForInterpolation(DriverType* Driver, bool bHide)`
- L575 _public member_ `static constexpr bool HasSetHiddenForInterpolation = TModels_V<CSetHiddenForInterpolationFuncable, DriverType>;`
- L578 _public function_ `template<bool HasFunc=HasSetHiddenForInterpolation> static typename TEnableIf<HasFunc>::Type CallSetHiddenForInterpolation(DriverType* Driver, bool bHide)`
- L585 _public function_ `template<bool HasFunc=HasSetHiddenForInterpolation> static typename TEnableIf<!HasFunc>::Type CallSetHiddenForInterpolation(DriverType* Driver, bool bHide)`
- L590 _public function_ `static void CallSetHiddenForInterpolationFallback(AActor* Driver, bool bHide)`
- L595 _public function_ `static void CallSetHiddenForInterpolationFallback(UActorComponent* Driver, bool bHide)`
- L615 _public function_ `static void LogUserStates(const TNetworkPredictionState<StateTypes>& UserStates, FOutputDevice& Ar=*GLog)`
- L630 _public function_ `template<typename StateType> static void LogUserState(const StateType* State, FOutputDevice& Ar=*GLog)`
- L641 _public function_ `template<typename StateType> static void TraceUserStateString(const StateType* State, FAnsiStringBuilderBase& Builder)`
- L649 _public function_ `template<typename StateType> static void ToString(const StateType* State, FAnsiStringBuilderBase& Builder)`
- L654 _public function_ `static void ToString(const void* State, FAnsiStringBuilderBase& Builder)`
- L662 _public function_ `template<typename StateType> static void NetSerialize(TConditionalState<StateType>& State, const FNetSerializeParams& P)`
- L667 _public function_ `static void NetSerialize(TConditionalState<void>& State, const FNetSerializeParams& P)`

#### struct `FNetworkPredictionDriverBase::CInitializeSimulationStateFuncable`  
`struct CInitializeSimulationStateFuncable`  
_L258-262_
- L261 _public prototype_ `template <typename InDriverType, typename...> auto Requires(InDriverType* Driver, SyncType* Sync, AuxType* Aux) -> decltype(Driver->InitializeSimulationState(Sync, Aux));`

#### struct `FNetworkPredictionDriverBase::CProduceInputMemberFuncable`  
`struct CProduceInputMemberFuncable`  
_L292-296_
- L295 _public prototype_ `template <typename InDriverType, typename...> auto Requires(InDriverType* Driver, int32 TimeMS, InputType* InputCmd) -> decltype(Driver->ProduceInput(TimeMS, InputCmd));`

#### struct `FNetworkPredictionDriverBase::CFinalizeFrameMemberFuncable`  
`struct CFinalizeFrameMemberFuncable`  
_L323-327_
- L326 _public prototype_ `template <typename InDriverType, typename...> auto Requires(InDriverType* Driver, const SyncType* S, const AuxType* A) -> decltype(Driver->FinalizeFrame(S, A));`

#### struct `FNetworkPredictionDriverBase::CFinalizeSmoothingFrameMemberFuncable`  
`struct CFinalizeSmoothingFrameMemberFuncable`  
_L355-359_
- L358 _public prototype_ `template <typename InDriverType, typename...> auto Requires(InDriverType* Driver, const SyncType* S, const AuxType* A) -> decltype(Driver->FinalizeSmoothingFrame(S, A));`

#### struct `FNetworkPredictionDriverBase::CRestoreFrameMemberFuncable`  
`struct CRestoreFrameMemberFuncable`  
_L390-394_
- L393 _public prototype_ `template <typename InDriverType, typename...> auto Requires(InDriverType* Driver, const SyncType* S, const AuxType* A) -> decltype(Driver->RestoreFrame(S, A));`

#### struct `FNetworkPredictionDriverBase::CCallServerRPCMemberFuncable`  
`struct CCallServerRPCMemberFuncable`  
_L426-430_
- L429 _public prototype_ `template <typename InDriverType> auto Requires(InDriverType* Driver) -> decltype(Driver->CallServerRPC());`

#### struct `FNetworkPredictionDriverBase::CShouldReconcileSyncStateMemberFuncable`  
`struct CShouldReconcileSyncStateMemberFuncable`  
_L477-483_
- L480 _public prototype_ `template <typename InDriverType, typename...> auto Requires(InDriverType* Driver, const SyncType* Predicted, const SyncType* Authority) -> decltype( Driver->ShouldReconcile(Predicted, Authority) );`

#### struct `FNetworkPredictionDriverBase::CShouldReconcileAuxStateMemberFuncable`  
`struct CShouldReconcileAuxStateMemberFuncable`  
_L485-491_
- L488 _public prototype_ `template <typename InDriverType, typename...> auto Requires(InDriverType* Driver, const AuxType* Predicted, const AuxType* Authority) -> decltype( Driver->ShouldReconcile(Predicted, Authority) );`

#### struct `FNetworkPredictionDriverBase::CSetHiddenForInterpolationFuncable`  
`struct CSetHiddenForInterpolationFuncable`  
_L569-573_
- L572 _public prototype_ `template <typename InDriverType> auto Requires(InDriverType* Driver, bool bHidden) -> decltype(Driver->SetHiddenForInterpolation(bHidden));`

#### struct `FNetworkPredictionDriver`  
`template<typename ModelDef> struct FNetworkPredictionDriver : FNetworkPredictionDriverBase<ModelDef>`  
_L673-676_
- inherits: `FNetworkPredictionDriverBase<ModelDef>`
- desc: This is the actual template to specialize when wanting to override functions

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Chaos`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionGenericKinematicActor.h` (Public)


#### struct `FGenericKinematicActorSyncState`  
`struct FGenericKinematicActorSyncState`  
_L7-11_
- L9 _public member_ `FVector_NetQuantize100 Location;`
- L10 _public member_ `FQuat Rotation;`

#### struct `FGenericKinematicActorDef`  
`struct FGenericKinematicActorDef : FNetworkPredictionModelDef`  
_L15-23_
- inherits: `FNetworkPredictionModelDef`
- desc: Generic def for kinematic (non physics) actor that doesn't have a backing simulation. This is quite limited in what it can do, but hopefully useful is that they can still be recorded and restored
- L17 _public prototype_ `NP_MODEL_BODY();`
- L19 _public typedef_ `using StateTypes = TNetworkPredictionStateTypes<void, FGenericKinematicActorSyncState, void>;`
- L20 _public typedef_ `using Driver = AActor;`
- L21 _public function_ `static const TCHAR* GetName()`
- L22 _public function_ `static constexpr int32 GetSortPriority()`

#### struct `FNetworkPredictionDriver`  
`template<> struct FNetworkPredictionDriver<FGenericKinematicActorDef> : FNetworkPredictionDriverBase<FGenericKinematicActorDef>`  
_L26-34_
- inherits: `FNetworkPredictionDriverBase<FGenericKinematicActorDef>`
- L28 _public function_ `static void InitializeSimulationState(AActor* ActorDriver, FGenericKinematicActorSyncState* Sync, void* Aux)`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionID.h` (Public)


#### struct `FNetworkPredictionID`  
`struct FNetworkPredictionID`  
_L8-34_
- desc: Unique server assigned ID for a network sim instance
- L10 _public prototype_ `FNetworkPredictionID() = default;`
- L11 _public function_ `explicit FNetworkPredictionID(int32 InSpawnID) : SpawnID(InSpawnID)`
- L17 _public function_ `explicit FNetworkPredictionID(int32 InSpawnID, int32 InTraceID) : SpawnID(InSpawnID), TraceID(InTraceID)`
- L19 _public function_ `int32 GetTraceID() const`
- L21 _public function_ `bool IsValid() const`
- L23 _public function_ `operator int32() const`
- L24 _public function_ `bool operator< (const FNetworkPredictionID &rhs) const`
- L25 _public function_ `bool operator<= (const FNetworkPredictionID &rhs) const`
- L26 _public function_ `bool operator> (const FNetworkPredictionID &rhs) const`
- L27 _public function_ `bool operator>= (const FNetworkPredictionID &rhs) const`
- L28 _public function_ `bool operator== (const FNetworkPredictionID &rhs) const`
- L29 _public function_ `bool operator!= (const FNetworkPredictionID &rhs) const`
- L32 _private member_ `int32 SpawnID=INDEX_NONE;`
- L33 _private member_ `int32 TraceID=0;`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkPrediction, Log, All);`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionModelDef.h` (Public)


#### enum `ENetworkPredictionSortPriority`  
`enum class ENetworkPredictionSortPriority : uint8`  
_L9-17_
- desc: Arbitrary sort values used by system default definitions
- L11 _public enumerator_ `First = 1`
- L12 _public enumerator_ `PreKinematicMovers = 50`
- L13 _public enumerator_ `KinematicMovers = 75`
- L14 _public enumerator_ `PostKinematicMovers = 100`
- L16 _public enumerator_ `Last = 250`

#### struct `FNetworkPredictionModelDef`  
`struct FNetworkPredictionModelDef`  
_L22-45_
- L29 _public typedef_ `using StateTypes = TNetworkPredictionStateTypes<void,void,void>;` — TNetworkPredictionStateTypes: User State Types (Input, Sync, Aux) Enables: Reconcile, Ticking, Input, Finalize
- L34 _public typedef_ `using Simulation = void;` — Object that runs SimulationTick Requires: valid StateTypes Enables: Ticking
- L40 _public typedef_ `using Driver = void;` — Object class that can take output from prediction system. E.g AActor, AMyPawn. See notes in NetworkPredictionDriver.h Requires: StateTypes Enables: Finalize, Cues
- L42 _public function_ `static const TCHAR* GetName()`
- L44 _public function_ `static constexpr int32 GetSortPriority()`

#### struct `FConditionalSimulationPtr`  
`template<typename ModelDef=FNetworkPredictionModelDef, typename SimulationType=typename ModelDef::Simulation> struct FConditionalSimulationPtr`  
_L50-57_
- L52 _public function_ `FConditionalSimulationPtr(SimulationType* Sim=nullptr) : Simulation(Sim)`
- L53 _public function_ `SimulationType* operator->() const`
- L56 _private member_ `SimulationType* Simulation = nullptr;`
- L62 _public function_ `FConditionalSimulationPtr(void* v=nullptr)`

#### struct `FConditionalSimulationPtr`  
`template<typename ModelDef> struct FConditionalSimulationPtr<ModelDef, void>`  
_L60-63_
- L52 _public function_ `FConditionalSimulationPtr(SimulationType* Sim=nullptr) : Simulation(Sim)`
- L53 _public function_ `SimulationType* operator->() const`
- L56 _private member_ `SimulationType* Simulation = nullptr;`
- L62 _public function_ `FConditionalSimulationPtr(void* v=nullptr)`

#### struct `TNetworkPredictionModelInfo`  
`template<typename ModelDef=FNetworkPredictionModelDef> struct TNetworkPredictionModelInfo`  
_L68-79_
- L70 _public typedef_ `using SimulationType = typename ModelDef::Simulation;`
- L71 _public typedef_ `using DriverType = typename ModelDef::Driver;`
- L73 _public member_ `FConditionalSimulationPtr<ModelDef> Simulation;` — Object that ticks this instance
- L74 _public member_ `DriverType* Driver = nullptr;` — Object that handles input/out
- L75 _public member_ `struct FNetworkPredictionStateView* View = nullptr;` — Game side view of state to update
- L77 _public function_ `TNetworkPredictionModelInfo(SimulationType* InSimulation=nullptr, DriverType* InDriver=nullptr, FNetworkPredictionStateView* InView=nullptr) : Simulation(InSimulation), Driver(InDriver), View(InView)`

#### Free symbols / members of external scopes

- L19 _typedef_ `using FModelDefId = int32;`
- L20 _macro_ `#define NP_MODEL_BODY() static FModelDefId ID`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionModelDefRegistry.h` (Public)


#### class `FNetworkPredictionModelDefRegistry`  
`class FNetworkPredictionModelDefRegistry`  
_L12-59_
- desc: Basic ModelDef type registry. ModelDefs are registered and assigned an ID (their ModelDef::ID) based on ModelDef::SortPriority. This ID is used as indices into the various NP service arrays
- L15 _private prototype_ `FNetworkPredictionModelDefRegistry() = default;` — Declaring this as private to help avoid sidestepping singleton
- L19 _public prototype_ `static FNetworkPredictionModelDefRegistry& Get();`
- L22 _public function_ `template<typename ModelDef> void RegisterType()`
- L41 _public prototype_ `void FinalizeTypes();`
- L56 _private member_ `TArray<FTypeInfo> ModelDefList;`
- L58 _private member_ `bool bFinalized = false;`

#### struct `FNetworkPredictionModelDefRegistry::FTypeInfo`  
`struct FTypeInfo`  
_L44-54_
- L46 _public function_ `bool operator==(const FModelDefId* OtherIDPtr) const`
- L51 _public member_ `FModelDefId* IDPtr = nullptr;`
- L52 _public member_ `int32 SortPriority;`
- L53 _public member_ `const TCHAR* Name;`

#### struct `TNetworkPredictionModelDefRegisterHelper`  
`template<typename ModelDef> struct TNetworkPredictionModelDefRegisterHelper`  
_L62-68_
- L64 _public function_ `TNetworkPredictionModelDefRegisterHelper()`

#### Free symbols / members of external scopes

- L72 _macro_ `#define NP_MODEL_REGISTER(X) \` — Helper to register ModelDef type. Sets static ID to 0 (invalid) and calls global registration function

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionModule.h` (Public)


#### class `INetworkPredictionModule`  
`class INetworkPredictionModule : public IModuleInterface`  
_L7-32_
- inherits: `IModuleInterface`
- L18 _public function_ `static inline INetworkPredictionModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L28 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionProxy.h` (Public)


#### enum `ENetworkPredictionStateRead`  
`enum class ENetworkPredictionStateRead`  
_L27-34_
- reflection: `UENUM()`
- L30 _public enumerator_ `Simulation` — The authoritative, networked state values.
- L33 _public enumerator_ `Presentation` — The local "smoothed" or "corrected" state values. If no explicit presentation value is set, Simulation value is implied. Presentation values never feed back into the simulation.

#### struct `FNetworkPredictionProxy`  
`struct FNetworkPredictionProxy`  
_L37-273_
- reflection: `USTRUCT()`
- L54 _public prototype_ `template<typename ModelDef> void Init(UWorld* World, const FReplicationProxySet& RepProxies, typename ModelDef::Simulation* Simulation=nullptr, typename ModelDef::Driver* Driver=nullptr);` — The init function that you need to call. This is defined in NetworkPredictionProxyInit.h (which should only be included by your .cpp file)
- L57 _public prototype_ `template<typename ModelDef> void Init(const FInitParams<ModelDef>& Params);`
- L60 _public function_ `void InitForNetworkRole(ENetRole Role, bool bHasNetConnection)` — When network role changes, initializes role storage and logic controller
- L71 _public function_ `void SetArchetype(const FNetworkPredictionInstanceArchetype& Archetype, const FNetworkPredictionInstanceConfig& Config)` — Should only be called on the authority. Changes what how this instance is allowed to be configured
- L78 _public function_ `void Configure(const FNetworkPredictionInstanceConfig& Config)` — Call to change local configuration of proxy. Not networked.
- L88 _public function_ `void EndPlay()` — Unregisters from NetworkPrediction System
- L102 _public function_ `template<typename TInputCmd> const TInputCmd* ReadInputCmd() const` — Returns pending InputCmd. (Note there is no Presentation version of InputCmds)
- L109 _public function_ `template<typename TSyncState> const TSyncState* ReadSyncState(ENetworkPredictionStateRead ReadType = ENetworkPredictionStateRead::Presentation) const` — Returns Presentation SyncState by default, if it is set. Otherwise returns pending Simulation value.
- L121 _public function_ `template<typename TSyncState> const TSyncState* ReadPrevPresentationSyncState() const` — Returns Prev Presentation SyncState by default, if it is set. Otherwise returns pending Simulation value.
- L134 _public function_ `template<typename TAuxState> const TAuxState* ReadAuxState(ENetworkPredictionStateRead ReadType = ENetworkPredictionStateRead::Presentation) const` — Returns Presentation AuxState by default, if it is set. Otherwise returns pending Simulation value.
- L146 _public function_ `template<typename TAuxState> const TAuxState* ReadPrevPresentationAuxState() const` — Returns Prev Presentation AuxState by default, if it is set. Otherwise returns pending Simulation value.
- L159 _public prototype_ `template<typename TInputCmd> const TInputCmd* WriteInputCmd(TFunctionRef<void(TInputCmd&)> WriteFunc, const FAnsiStringView& TraceMsg=FAnsiStringView());` — Writes - must include NetworkPredictionProxyWrite.h in places that call this Note that writes are implicitly done on the simulation state. It is not valid to modify the presentation value out of band.
- L162 _public prototype_ `template<typename TSyncState> const TSyncState* WriteSyncState(TFunctionRef<void(TSyncState&)> WriteFunc, const FAnsiStringView& TraceMsg=FAnsiStringView());`
- L165 _public prototype_ `template<typename TSyncState> const TSyncState* WritePresentationSyncState(TFunctionRef<void(TSyncState&)> WriteFunc, const FAnsiStringView& TraceMsg=FAnsiStringView());`
- L168 _public prototype_ `template<typename TSyncState> const TSyncState* WritePrevPresentationSyncState(TFunctionRef<void(TSyncState&)> WriteFunc, const FAnsiStringView& TraceMsg=FAnsiStringView());`
- L171 _public prototype_ `template<typename TAuxState> const TAuxState* WriteAuxState(TFunctionRef<void(TAuxState&)> WriteFunc, const FAnsiStringView& TraceMsg=FAnsiStringView());`
- L174 _public prototype_ `template<typename TAuxState> const TAuxState* WritePresentationAuxState(TFunctionRef<void(TAuxState&)> WriteFunc, const FAnsiStringView& TraceMsg=FAnsiStringView());`
- L177 _public prototype_ `template<typename TAuxState> const TAuxState* WritePrevPresentationAuxState(TFunctionRef<void(TAuxState&)> WriteFunc, const FAnsiStringView& TraceMsg=FAnsiStringView());`
- L182 _public function_ `FNetSimCueDispatcher* GetCueDispatcher() const`
- L187 _public function_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)`
- L202 _public function_ `void ConfigureAfterLoading(uint32 LoadedID)`
- L228 _public function_ `bool Identical(const FNetworkPredictionProxy* Other, uint32 PortFlags) const`
- L235 _public function_ `int32 GetPendingFrame() const`
- L236 _public function_ `int32 GetTotalSimTimeMS() const`
- L237 _public function_ `ENetRole GetCachedNetRole() const`
- L238 _public function_ `bool GetCachedHasNetConnection() const`
- L241 _public function_ `FNetworkPredictionID& GetID()`
- L242 _public function_ `FNetworkPredictionInstanceArchetype& GetCachedArchetype()`
- L258 _private prototype_ `void TraceViaConfigFunc(EConfigAction Action);`
- L260 _private member_ `FNetworkPredictionID ID;`
- L261 _private member_ `FNetworkPredictionStateView View;`
- L263 _private member_ `ENetRole CachedNetRole = ROLE_None;`
- L264 _private member_ `bool bCachedHasNetConnection = false;`
- L265 _private member_ `FNetworkPredictionInstanceConfig CachedConfig;`
- L266 _private member_ `FNetworkPredictionInstanceArchetype CachedArchetype;`
- L267 _private member_ `uint8 ArchetypeDirtyCount = 0;`
- L269 _private member_ `TFunction<void(FNetworkPredictionProxy* const, FNetworkPredictionID NewID, EConfigAction Action)> ConfigFunc;`
- L272 _private member_ `TObjectPtr<UNetworkPredictionWorldManager> WorldManager = nullptr;` — `UPROPERTY()`

#### struct `FNetworkPredictionProxy::FInitParams`  
`template<typename ModelDef> struct FInitParams`  
_L43-50_
- desc: Parameter struct to be used with the Init function overload below, when a UWorld isn't available, such as in unit tests.
- L45 _public member_ `UNetworkPredictionWorldManager* WorldManager;`
- L46 _public member_ `ENetMode Mode;`
- L47 _public member_ `const FReplicationProxySet& RepProxies;`
- L48 _public member_ `typename ModelDef::Simulation* Simulation = nullptr;`
- L49 _public member_ `typename ModelDef::Driver* Driver = nullptr;`

#### enum `FNetworkPredictionProxy::EConfigAction`  
`enum class EConfigAction : uint8`  
_L248-256_
- desc: Allows ConfigFunc to be invoked to "do a thing" instead of set a new config/id. This is useful because ConfigFunc can make the untemplated caller -> ModelDef jump.
- L250 _public enumerator_ `None`
- L251 _public enumerator_ `EndPlay`
- L252 _public enumerator_ `UpdateConfigWithDefault`
- L253 _public enumerator_ `TraceInput`
- L254 _public enumerator_ `TraceSync`
- L255 _public enumerator_ `TraceAux`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNetworkPredictionProxy> : public TStructOpsTypeTraitsBase2<FNetworkPredictionProxy>`  
_L276-283_
- inherits: `TStructOpsTypeTraitsBase2<FNetworkPredictionProxy>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L279-282_

#### Free symbols / members of external scopes

- L280 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon0eed5def0103`)
- L281 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anon0eed5def0103`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionProxyInit.h` (Public)


#### Free symbols / members of external scopes

- L14 _function_ `template<typename ModelDef> void FNetworkPredictionProxy::Init(const FInitParams<ModelDef>& Params)` (scope `FNetworkPredictionProxy`) — The init function binds to the templated methods on UNetworkPredictionMAnager. This will "bring in" all the templated systems on NP, so this file should only be included in your .cpp file that is calling Init.
- L16 _typedef_ `using StateTypes = typename ModelDef::StateTypes;` (scope `FNetworkPredictionProxy::Init`)
- L17 _typedef_ `using InputType = typename StateTypes::InputType;` (scope `FNetworkPredictionProxy::Init`)
- L18 _typedef_ `using SyncType = typename StateTypes::SyncType;` (scope `FNetworkPredictionProxy::Init`)
- L19 _typedef_ `using AuxType = typename StateTypes::AuxType;` (scope `FNetworkPredictionProxy::Init`)
- L42 _function_ `` (scope `FNetworkPredictionProxy::Init`)
- L86 _function_ `template<typename ModelDef> void FNetworkPredictionProxy::Init(UWorld* World, const FReplicationProxySet& RepProxies, typename ModelDef::Simulation* Simulation, typename ModelDef::Driver* Driver)` (scope `FNetworkPredictionProxy`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionProxyWrite.h` (Public)


#### Free symbols / members of external scopes

- L8 _function_ `inline void FNetworkPredictionProxy::TraceViaConfigFunc(EConfigAction Action)` (scope `FNetworkPredictionProxy`)
- L22 _function_ `template<typename TInputCmd> const TInputCmd* FNetworkPredictionProxy::WriteInputCmd(TFunctionRef<void(TInputCmd&)> WriteFunc,const FAnsiStringView& TraceMsg)` (scope `FNetworkPredictionProxy`)
- L36 _function_ `template<typename TSyncState> const TSyncState* FNetworkPredictionProxy::WriteSyncState(TFunctionRef<void(TSyncState&)> WriteFunc, const FAnsiStringView& TraceMsg)` (scope `FNetworkPredictionProxy`)
- L49 _function_ `template<typename TSyncState> const TSyncState* FNetworkPredictionProxy::WritePresentationSyncState(TFunctionRef<void(TSyncState&)> WriteFunc, const FAnsiStringView& TraceMsg)` (scope `FNetworkPredictionProxy`)
- L62 _function_ `template<typename TSyncState> const TSyncState* FNetworkPredictionProxy::WritePrevPresentationSyncState(TFunctionRef<void(TSyncState&)> WriteFunc, const FAnsiStringView& TraceMsg)` (scope `FNetworkPredictionProxy`)
- L75 _function_ `template<typename TAuxState> const TAuxState* FNetworkPredictionProxy::WriteAuxState(TFunctionRef<void(TAuxState&)> WriteFunc, const FAnsiStringView& TraceMsg)` (scope `FNetworkPredictionProxy`)
- L88 _function_ `template<typename TAuxState> const TAuxState* FNetworkPredictionProxy::WritePresentationAuxState(TFunctionRef<void(TAuxState&)> WriteFunc, const FAnsiStringView& TraceMsg)` (scope `FNetworkPredictionProxy`)
- L101 _function_ `template<typename TAuxState> const TAuxState* FNetworkPredictionProxy::WritePrevPresentationAuxState(TFunctionRef<void(TAuxState&)> WriteFunc, const FAnsiStringView& TraceMsg)` (scope `FNetworkPredictionProxy`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionReplicatedManager.h` (Public)


#### struct `FSharedPackageMapItem`  
`struct FSharedPackageMapItem`  
_L16-22_
- reflection: `USTRUCT()`
- L21 _public member_ `TSoftObjectPtr<UObject> SoftPtr;` — `UPROPERTY()`

#### struct `FSharedPackageMap`  
`struct FSharedPackageMap`  
_L25-31_
- reflection: `USTRUCT()`
- L30 _public member_ `TArray<FSharedPackageMapItem> Items;` — `UPROPERTY()`

#### class `ANetworkPredictionReplicatedManager`  
`class ANetworkPredictionReplicatedManager : public AActor`  
_L34-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L40 _public prototype_ `ANetworkPredictionReplicatedManager();`
- L42 _public prototype_ `static FDelegateHandle OnAuthoritySpawn(const TFunction<void(ANetworkPredictionReplicatedManager*)>& Func);`
- L43 _public function_ `static void UnregisterOnAuthoritySpawn(FDelegateHandle Handle)`
- L45 _public prototype_ `virtual void BeginPlay();`
- L47 _public prototype_ `uint8 AddObjectToSharedPackageMap(TSoftObjectPtr<UObject> SoftPtr);`
- L49 _public prototype_ `uint8 GetIDForObject(UObject* Obj) const;`
- L51 _public prototype_ `TSoftObjectPtr<UObject> GetObjectForID(uint8 ID) const;`
- L56 _private member_ `FSharedPackageMap SharedPackageMap;` — `UPROPERTY(Replicated)`
- L58 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAuthoritySpawn, ANetworkPredictionReplicatedManager*) static FOnAuthoritySpawn OnAuthoritySpawnDelegate;`
- L61 _private member_ `static TWeakObjectPtr<ANetworkPredictionReplicatedManager> AuthorityInstance;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NETWORKPREDICTION_API`
- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAuthoritySpawn, ANetworkPredictionReplicatedManager*) static FOnAuthoritySpawn OnAuthoritySpawnDelegate;`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionReplicationProxy.h` (Public)


#### enum `EReplicationProxyTarget`  
`enum class EReplicationProxyTarget: uint8`  
_L18-24_
- desc: Target of replication
- L20 _public enumerator_ `ServerRPC` — Client -> Server
- L21 _public enumerator_ `AutonomousProxy` — Owning/Controlling client
- L22 _public enumerator_ `SimulatedProxy` — Non owning client
- L23 _public enumerator_ `Replay` — Replay net driver

#### struct `FNetSerializeParams`  
`struct FNetSerializeParams`  
_L32-38_
- desc: The parameters for NetSerialize that are passed around the system. Everything should use this, expecting to have to add more.
- L34 _public function_ `FNetSerializeParams(FArchive& InAr, UPackageMap* InMap=nullptr) : Ar(InAr), Map(InMap)`
- L36 _public member_ `FArchive& Ar;`
- L37 _public member_ `UPackageMap* Map;`

#### struct `FReplicationProxy`  
`struct FReplicationProxy`  
_L44-86_
- reflection: `USTRUCT()`
- desc: Redirects NetSerialize to a dynamically set NetSerializeFunc. This is how we hook into the replication systems role-based serialization
- L48 _public prototype_ `void Init(FNetworkPredictionProxy* InNetSimProxy, EReplicationProxyTarget InReplicationTarget);`
- L49 _public prototype_ `bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);`
- L50 _public prototype_ `void OnPreReplication();`
- L51 _public prototype_ `bool Identical(const FReplicationProxy* Other, uint32 PortFlags) const;`
- L53 _public function_ `int32 GetCachedPendingFrame() const`
- L58 _public member_ `TFunction<void(const FNetSerializeParams& P)> NetSerializeFunc;`
- L60 _public member_ `FNetworkPredictionProxy* NetSimProxy = nullptr;`
- L66 _public member_ `static constexpr uint32 NumReservedBits = 4096;` — Number of bits to reserve in serialization container. Make this large enough to try to avoid re-allocation during the worst case calls.
- L67 _public member_ `static constexpr uint32 MaxNumBits = 16384;`
- L70 _public member_ `TWeakObjectPtr<AActor> OwnerActor = nullptr;` — Iris support: holding ptr to associated actor for replication bridge / package map retrieval
- L73 _public member_ `TBitArray<TInlineAllocator<NumReservedBits / NumBitsPerDWORD>> DataBits;` — Iris support: TInlineAllocator used with TBitArray takes the number of 32-bit dwords, but the define is in number of bits, so convert here by dividing by 32.
- L77 _public member_ `UE::Net::FIrisPackageMapExports PackageMapExports;` — Iris support: Since this struct uses custom serialization path we need to explicitly capture exports in order to forward them to iris This is managed by the use of a custom packagemap.
- L80 _public member_ `UE::Net::FNetTokenExportContext::FNetTokenExports NetTokensPendingExport;` — Iris support: Since we capturing data outside of the normal serialization path we also need to store exports to inject when actually sending the data.
- L84 _private member_ `EReplicationProxyTarget ReplicationTarget;`
- L85 _private member_ `int32 CachedPendingFrame = INDEX_NONE;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FReplicationProxy> : public TStructOpsTypeTraitsBase2<FReplicationProxy>`  
_L89-96_
- inherits: `TStructOpsTypeTraitsBase2<FReplicationProxy>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L92-95_

#### struct `FReplicationProxySet`  
`struct FReplicationProxySet`  
_L99-114_
- desc: Collection of each replication proxy
- L101 _public member_ `FReplicationProxy* ServerRPC = nullptr;`
- L102 _public member_ `FReplicationProxy* AutonomousProxy = nullptr;`
- L103 _public member_ `FReplicationProxy* SimulatedProxy = nullptr;`
- L104 _public member_ `FReplicationProxy* Replay = nullptr;`
- L106 _public function_ `void UnbindAll() const`

#### struct `FServerReplicationRPCParameter`  
`struct FServerReplicationRPCParameter`  
_L125-165_
- reflection: `USTRUCT()`
- L130 _public function_ `FServerReplicationRPCParameter() : Proxy(nullptr)` — Receive flow: ctor() -> NetSerialize
- L133 _public function_ `FServerReplicationRPCParameter(FReplicationProxy& InProxy) : Proxy(&InProxy)` — Send flow: ctor(Proxy) -> SerializeToProxy
- L134 _public function_ `void SetReplicationProxy(FReplicationProxy& InProxy)`
- L135 _public prototype_ `bool SerializeToProxy(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L136 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L138 _public function_ `UPackageMap* GetPackageMap() const`
- L145 _public prototype_ `static UIrisObjectReferencePackageMap* GetIrisPackageMapToCaptureReferences(UNetConnection* NetConnection, UE::Net::FIrisPackageMapExports& PackageMapExports);` — Iris support
- L146 _public prototype_ `static UIrisObjectReferencePackageMap* GetIrisPackageMapToReadReferences(const UNetConnection* NetConnection, UE::Net::FIrisPackageMapExports& PackageMapExports);`
- L149 _public member_ `static constexpr uint32 NumReservedBits = 4096;` — Number of bits to reserve in serialization container. Make this large enough to try to avoid re-allocation during worst-case RPC calls.
- L150 _public member_ `static constexpr uint32 MaxNumBits = 16384;`
- L153 _public member_ `TBitArray<TInlineAllocator<NumReservedBits / NumBitsPerDWORD>> DataBits;` — Iris support: TInlineAllocator used with TBitArray takes the number of 32-bit dwords, but the define is in number of bits, so convert here by dividing by 32.
- L157 _public member_ `UE::Net::FIrisPackageMapExports PackageMapExports;` — Iris support: Since this struct uses custom serialization path we need to explicitly capture exports in order to forward them to iris This is managed by the use of a custom packagemap.
- L160 _public member_ `UE::Net::FNetTokenExportContext::FNetTokenExports NetTokensPendingExport;` — Iris support: Since we capturing data outside of the normal serialization path we also need to store exports to inject when actually sending the data.
- L163 _private member_ `FReplicationProxy* Proxy = nullptr;`
- L164 _private member_ `UPackageMap* CachedPackageMap = nullptr;` — Used for non-Iris replication

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FServerReplicationRPCParameter> : public TStructOpsTypeTraitsBase2<FServerReplicationRPCParameter>`  
_L168-174_
- inherits: `TStructOpsTypeTraitsBase2<FServerReplicationRPCParameter>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L171-173_

#### struct `FScopedBandwidthLimitBypass`  
`struct FScopedBandwidthLimitBypass`  
_L180-188_
- desc: Helper struct to bypass the bandwidth limit imposed by the engine's NetDriver (QueuedBits, NetSpeed, etc). This is really a temp measure to make the system easier to drop in/try in a project without messing with your engine settings. (bandwidth optimizations have not been done yet and the system in general hasn't been stressed with packetloss / gaps in command streams) So, you are free to use this in your own code but it may be removed one day. Hopefully in general bandwidth limiting will also become more robust.
- L182 _public prototype_ `FScopedBandwidthLimitBypass(AActor* OwnerActor);`
- L183 _public prototype_ `~FScopedBandwidthLimitBypass();`
- L186 _private member_ `int64 RestoreBits = 0;`
- L187 _private member_ `class UNetConnection* CachedNetConnection = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API NETWORKPREDICTION_API`
- L26 _function_ `inline FString LexToString(EReplicationProxyTarget A)`
- L93 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon49b8b0290103`)
- L94 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anon49b8b0290103`)
- L172 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon49b8b0290203`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionSerialization.h` (Public)


#### struct `FNetworkPredictionSerialization`  
`struct FNetworkPredictionSerialization`  
_L42-102_
- L59 _public function_ `static int32 SerializeFrame(FArchive& Ar, int32 Frame, int32 RelativeFrame)` — Helper to serialize an int32 frame as 8 bits. Returns the unpacked value (this will be same as input in the save path)
- L71 _public function_ `static void WriteCompressedFrame(FArchive& Ar, int32 Frame)` — Disabled right now: this is causing issues with JIP
- L80 _public function_ `static int32 ReadCompressedFrame(FArchive& Ar, int32 RelativeFrame)` — Disabled right now: this is causing issues with JIP
- L91 _public function_ `static void SerializeTimeMS(FArchive& Ar, int32& TimestampMS)` — For serializing timestamps
- L98 _public function_ `static void SerializeDeltaMS(FArchive& Ar, int32& DeltaTimeMS)` — For serializing DeltaMS, expected to be small (< 1000)

#### enum `FNetworkPredictionSerialization::(anonymous)`  
`enum`  
_L48-48_
- desc: How many bits we use to NetSerialize Frame numbers. This is only relevant AP Client <--> Server communication. Frames are stored locally as 32 bit integers, but we use a smaller number of bits to NetSerialize. The system internally guards from Frame numbers diverging. E.g, the client will not generate new frames if the last serialization frame would be pushed out of the buffer. Server does not generate frames without input from client.

#### enum `FNetworkPredictionSerialization::(anonymous)`  
`enum`  
_L51-51_
- desc: Abs max value we encode into the bit writer

#### enum `FNetworkPredictionSerialization::(anonymous)`  
`enum`  
_L56-56_
- desc: This is the threshold at which we would wrap around and incorrectly assign a frame on the receiving side. E.g, If there are FRAME_ERROR_THRESHOLD frames that do not make it across from sender->receiver, the receiver will have incorrect local values. With 8 bits, this works out to be 128 frames or about 2 seconds at 60fps.

#### class `TFixedTickReplicator_Server`  
`template<typename InModelDef> class TFixedTickReplicator_Server`  
_L113-233_
- L117 _public typedef_ `using ModelDef = InModelDef;`
- L118 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L119 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L121 _public function_ `static void SetNumInputsPerSend(int32 NumToSend)`
- L129 _public function_ `static void NetRecv(const FNetSerializeParams& P, TServerRecvData_Fixed<ModelDef>& ServerRecvData, TModelDataStore<ModelDef>* DataStore, FFixedTickState* TickState)`
- L190 _public function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, FFixedTickState* TickState)`
- L225 _public function_ `static void EatCmd(const FNetSerializeParams& P)`
- L232 _private member_ `inline static int32 NumInputsPerSend = 6;`

#### class `TIndependentTickReplicator_Server`  
`template<typename InModelDef> class TIndependentTickReplicator_Server`  
_L236-364_
- L240 _public typedef_ `using ModelDef = InModelDef;`
- L242 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L243 _public typedef_ `using InputType= typename StateTypes::InputType;`
- L245 _public function_ `static void SetNumInputsPerSend(int32 NumToSend)`
- L253 _public function_ `static void NetRecv(const FNetSerializeParams& P, TServerRecvData_Independent<ModelDef>& ServerRecvData, TModelDataStore<ModelDef>* DataStore)`
- L315 _public function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, FVariableTickState* TickState)`
- L354 _private function_ `static void EatCmd(const FNetSerializeParams& P)`
- L363 _private member_ `inline static int32 NumInputsPerSend = 6;`

#### class `TCommonReplicator_AP`  
`template<typename ModelDef> class TCommonReplicator_AP`  
_L378-400_
- L382 _public function_ `static void NetRecv(const FNetSerializeParams& P, TInstanceData<ModelDef>& InstanceData, TClientRecvData<ModelDef>& ClientRecvState)`
- L393 _public function_ `static void NetSend(const FNetSerializeParams& P, TInstanceData<ModelDef>& InstanceData, typename TInstanceFrameState<ModelDef>::FFrame& FrameData)`

#### class `TFixedTickReplicator_AP`  
`template<typename InModelDef> class TFixedTickReplicator_AP`  
_L405-544_
- L409 _public typedef_ `using ModelDef = InModelDef;`
- L414 _public function_ `static void NetRecv(const FNetSerializeParams& P, TClientRecvData<ModelDef>& ClientRecvState, TModelDataStore<ModelDef>* DataStore, FFixedTickState* TickState)`
- L479 _public function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, const FFixedTickState* TickState)`

#### class `TIndependentTickReplicator_AP`  
`template<typename InModelDef> class TIndependentTickReplicator_AP`  
_L547-587_
- L551 _public typedef_ `using ModelDef = InModelDef;`
- L556 _public function_ `static void NetRecv(const FNetSerializeParams& P, TClientRecvData<ModelDef>& ClientRecvState, TModelDataStore<ModelDef>* DataStore, FVariableTickState* TickState)`
- L576 _public function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, TServerRecvData_Independent<ModelDef>& ServerRecvData, const FVariableTickState* VariableTickState)`

#### class `TCommonReplicator_SP`  
`template<typename InModelDef> class TCommonReplicator_SP`  
_L601-637_
- L605 _public typedef_ `using ModelDef = InModelDef;`
- L608 _public function_ `template<typename ClientRecvDataType> static void NetRecv(const FNetSerializeParams& P, ClientRecvDataType& ClientRecvState, TModelDataStore<ModelDef>* DataStore)`
- L622 _public function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, TInstanceData<ModelDef>* InstanceData, int32 PendingFrame)`

#### class `TFixedTickReplicator_SP`  
`template<typename InModelDef> class TFixedTickReplicator_SP`  
_L640-685_
- L644 _public typedef_ `using ModelDef = InModelDef;`
- L649 _public function_ `static void NetRecv(const FNetSerializeParams& P, TClientRecvData<ModelDef>& ClientRecvState, TModelDataStore<ModelDef>* DataStore, FFixedTickState* TickState)`
- L670 _public function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, const FFixedTickState* TickState)`

#### class `TIndependentTickReplicator_SP`  
`template<typename InModelDef> class TIndependentTickReplicator_SP`  
_L688-779_
- L692 _public typedef_ `using ModelDef = InModelDef;`
- L697 _public function_ `static void NetRecv(const FNetSerializeParams& P, TClientRecvData<ModelDef>& ClientRecvState, TModelDataStore<ModelDef>* DataStore, FVariableTickState* TickState)`
- L736 _public function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, const FVariableTickState* TickState)`
- L743 _public function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, const TServerRecvData_Independent<ModelDef>& IndependentTickState, const FVariableTickState* VariableTickState)` — For remotely controlled/ticked actors on the server
- L763 _private function_ `static void NetSend(const FNetSerializeParams& P, FNetworkPredictionID ID, TModelDataStore<ModelDef>* DataStore, int32 IndependentSimTime, int32 ServerTotalSimTime, int32 PendingFrame)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API NETWORKPREDICTION_API`
- L16 _macro_ `#define NETSIM_ENABLE_CHECKSUMS !(UE_BUILD_SHIPPING || UE_BUILD_TEST)`
- L18 _macro_ `#define NETSIM_CHECKSUM(Ser) SerializeChecksum(Ser,0xA186A384, false);`
- L20 _macro_ `#define NETSIM_CHECKSUM`
- L24 _macro_ `#define NETSIM_NETCONSTANT_NUM_BITS_FRAME 8 // Allows you to override this setting via UBT, but access via cleaner FActorMotionNetworkingConstants::NUM_BITS_FRAME`
- L27 _namespace_ `namespace NetworkPredictionCVars`
- L32 _externvar_ `extern TAutoConsoleVariable<bool> EnableTimeDilation;` (scope `NetworkPredictionCVars`) — Options governing fixed-tick time dilation. See CVar definitions for descriptions.
- L33 _externvar_ `extern TAutoConsoleVariable<float> TimeDilationAmount;` (scope `NetworkPredictionCVars`)
- L34 _externvar_ `extern TAutoConsoleVariable<bool> AllowTimeDilationEscalation;` (scope `NetworkPredictionCVars`)
- L35 _externvar_ `extern TAutoConsoleVariable<float> TimeDilationEscalationDecay;` (scope `NetworkPredictionCVars`)
- L36 _externvar_ `extern TAutoConsoleVariable<float> TimeDilationEscalationDecayMax;` (scope `NetworkPredictionCVars`)
- L37 _externvar_ `extern TAutoConsoleVariable<float> TimeDilationMax;` (scope `NetworkPredictionCVars`)
- L38 _externvar_ `extern TAutoConsoleVariable<float> TimeDilationMin;` (scope `NetworkPredictionCVars`)
- L48 _enumerator_ `enum { NUM_BITS_FRAME = NETSIM_NETCONSTANT_NUM_BITS_FRAME }; enum { MAX_FRAME_WRITE = 1 << NUM_BITS_FRAME };` (scope `FNetworkPredictionSerialization::__anon5f621c4b0103`) — How many bits we use to NetSerialize Frame numbers. This is only relevant AP Client <--> Server communication. Frames are stored locally as 32 bit integers, but we use a smaller number of bits to NetSerialize. The system internally guards from Frame numbers diverging. E.g, the client will not generate new frames if the last serialization frame would be pushed out of the buffer. Server does not generate frames without input from client.
- L51 _enumerator_ `enum { MAX_FRAME_WRITE = 1 << NUM_BITS_FRAME }; enum { FRAME_ERROR_THRESHOLD = MAX_FRAME_WRITE / 2};` (scope `FNetworkPredictionSerialization::__anon5f621c4b0203`) — Abs max value we encode into the bit writer
- L56 _enumerator_ `enum { FRAME_ERROR_THRESHOLD = MAX_FRAME_WRITE / 2}; static int32 SerializeFrame(FArchive& Ar, int32 Frame, int32 RelativeFrame) { if (Ar.IsSaving()) { ((FNetBitWriter&)Ar).WriteIntWrapped( Frame, MAX_FRAME_WRITE );` (scope `FNetworkPredictionSerialization::__anon5f621c4b0303`) — This is the threshold at which we would wrap around and incorrectly assign a frame on the receiving side. E.g, If there are FRAME_ERROR_THRESHOLD frames that do not make it across from sender->receiver, the receiver will have incorrect local values. With 8 bits, this works out to be 128 frames or about 2 seconds at 60fps.
- L402 _variable_ `static constexpr float TimeDilationNetSerializationScale = 10000.f;` — Used when net-serializing a float into an int16

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionSettings.h` (Public)


#### struct `FNetworkPredictionSettings`  
`struct FNetworkPredictionSettings`  
_L13-66_
- reflection: `USTRUCT(meta=(ShowOnlyInnerProperties))`
- L19 _public member_ `ENetworkPredictionTickingPolicy PreferredTickingPolicy = ENetworkPredictionTickingPolicy::Fixed;` — `UPROPERTY(config, EditAnywhere, Category = Global)` — Which ticking policy to use in cases where both are supported by the underlying simulation.
- L23 _public member_ `TSubclassOf<ANetworkPredictionReplicatedManager> ReplicatedManagerClassOverride;` — `UPROPERTY(config, EditAnywhere, Category = Global)` — Replicated Manager class
- L29 _public member_ `int32 FixedTickFrameRate = 60;` — `UPROPERTY(config, EditAnywhere, Category = FixedTick)` — Frame rate to use when running Fixed Tick simulations. Note: Engine::FixedFrameRate will take precedence if Engine::bUseFixedFrameRate is enabled.
- L33 _public member_ `ENetworkLOD SimulatedProxyNetworkLOD = ENetworkLOD::ForwardPredict;` — `UPROPERTY(config, EditAnywhere, Category = FixedTick)` — Default NetworkLOD for simulated proxy simulations.
- L37 _public member_ `bool bEnableFixedTickSmoothing = false;` — `UPROPERTY(config, EditAnywhere, Category = FixedTick)` — If enabled, the fixed tick smoothing service will be active, allowing drivers to receive smoothly interpolated updates for any locally-simulated objects (including forward-predicted sim proxies).
- L43 _public member_ `int32 FixedTickInterpolationBufferedMS = 100;` — `UPROPERTY(config, EditAnywhere, Category = Interpolation)` — How much buffered time to keep for fixed ticking interpolated sims (client only).
- L47 _public member_ `int32 IndependentTickInterpolationBufferedMS = 100;` — `UPROPERTY(config, EditAnywhere, Category = Interpolation)` — How much buffered time to keep for fixed independent interpolated sims (client only).
- L51 _public member_ `int32 IndependentTickInterpolationMaxBufferedMS = 250;` — `UPROPERTY(config, EditAnywhere, Category = Interpolation)` — Max buffered time to keep for fixed independent interpolated sims (client only).
- L57 _public member_ `int32 FixedTickInputSendCount = 6;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — Clients should send this number of most recent input commands together per update, for a Fixed Tick simulation
- L61 _public member_ `int32 IndependentTickInputSendCount = 6;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — Clients should send this number of most recent input commands together per update, for an Independent Tick simulation
- L65 _public member_ `int32 MaximumRemoteInputFaultLimit = 6;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — Cap the number of remote input commands required to be buffered before resuming input consumption after a fault

#### struct `FNetworkPredictionDevHUDItem`  
`struct FNetworkPredictionDevHUDItem`  
_L69-90_
- reflection: `USTRUCT(meta=(ShowOnlyInnerProperties))`
- L74 _public member_ `FString DisplayName;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD)`
- L77 _public member_ `FString ExecCommand;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD)`
- L81 _public member_ `bool bAutoBack = true;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD)` — Return to to level HUD menu after selecting this
- L85 _public member_ `bool bRequirePIE = false;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD)` — only works in PIE
- L89 _public member_ `bool bRequireNotPIE = false;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD)` — only works in non PIE

#### struct `FNetworkPredictionDevHUD`  
`struct FNetworkPredictionDevHUD`  
_L93-110_
- reflection: `USTRUCT(meta=(ShowOnlyInnerProperties))`
- L98 _public member_ `FString HUDName;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD)`
- L101 _public member_ `TArray<FNetworkPredictionDevHUDItem> Items;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD, meta=(ShowOnlyInnerProperties))`
- L105 _public member_ `bool bRequirePIE = false;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD)` — only works in PIE
- L109 _public member_ `bool bRequireNotPIE = false;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD)` — only works in non PIE

#### class `UNetworkPredictionSettingsObject`  
`class UNetworkPredictionSettingsObject : public UObject`  
_L114-129_
- reflection: `UCLASS(config=NetworkPrediction, defaultconfig, meta=(DisplayName="Network Prediction"))`
- inherits: `UObject`
- L121 _public member_ `FNetworkPredictionSettings Settings;` — `UPROPERTY(config, EditAnywhere, Category = "Network Prediction", meta=(ShowOnlyInnerProperties))`
- L124 _public member_ `TArray<FNetworkPredictionDevHUD> DevHUDs;` — `UPROPERTY(config, EditAnywhere, Category = DevHUD, meta=(ShowOnlyInnerProperties))`
- L127 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionSimulation.h` (Public)


#### struct `TNetSimOutput`  
`template<typename StateType=TNetworkPredictionStateTypes<>> struct TNetSimOutput`  
_L16-28_
- desc: Output state: the output SyncState (always created) and TNetSimLazyWriter for the AuxState (created on demand since every tick does not generate a new aux frame)
- L18 _public typedef_ `using InputType = typename StateType::InputType;`
- L19 _public typedef_ `using SyncType = typename StateType::SyncType;`
- L20 _public typedef_ `using AuxType = typename StateType::AuxType;`
- L22 _public member_ `SyncType* Sync;`
- L23 _public member_ `const TNetSimLazyWriter<AuxType>& Aux;`
- L24 _public member_ `FNetSimCueDispatcher& CueDispatch;`
- L26 _public function_ `TNetSimOutput(SyncType* InSync, const TNetSimLazyWriter<AuxType>& InAux, FNetSimCueDispatcher& InCueDispatch) : Sync(InSync), Aux(InAux), CueDispatch(InCueDispatch)`

#### Free symbols / members of external scopes

- L12 _typedef_ `template<typename StateTypes=TNetworkPredictionStateTypes<>> using TNetSimInput = TNetworkPredictionState<StateTypes>;` — Input state is just a collection of references to the simulation state types

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionStateTypes.h` (Public)


#### enum `ENetworkPredictionStateType`  
`enum class ENetworkPredictionStateType : uint8`  
_L6-11_
- desc: Enum to identify the state types
- L8 _public enumerator_ `Input`
- L9 _public enumerator_ `Sync`
- L10 _public enumerator_ `Aux`

#### struct `TNetworkPredictionStateTypes`  
`template<typename InInputCmd=void, typename InSyncState=void, typename InAuxState=void> struct TNetworkPredictionStateTypes`  
_L26-31_
- desc: State type defines
- L28 _public typedef_ `using InputType = InInputCmd;`
- L29 _public typedef_ `using SyncType = InSyncState;`
- L30 _public typedef_ `using AuxType = InAuxState;`

#### struct `TNetworkPredictionState`  
`template<typename StateType=TNetworkPredictionStateTypes<>> struct TNetworkPredictionState`  
_L35-52_
- desc: Tuple of state types
- L37 _public typedef_ `using InputType = typename StateType::InputType;`
- L38 _public typedef_ `using SyncType = typename StateType::SyncType;`
- L39 _public typedef_ `using AuxType = typename StateType::AuxType;`
- L41 _public member_ `const InputType* Cmd;`
- L42 _public member_ `const SyncType* Sync;`
- L43 _public member_ `const AuxType* Aux;`
- L45 _public function_ `TNetworkPredictionState(const InputType* InInputCmd, const SyncType* InSync, const AuxType* InAux) : Cmd(InInputCmd), Sync(InSync), Aux(InAux)`
- L50 _public function_ `template<typename T> TNetworkPredictionState(const TNetworkPredictionState<T>& Other) : Cmd(Other.Cmd), Sync(Other.Sync), Aux(Other.Aux)` — Allows implicit downcasting to a parent simulation's types

#### struct `TSyncAuxPair`  
`template<typename StateType=TNetworkPredictionStateTypes<>> struct TSyncAuxPair`  
_L56-71_
- desc: Just the Sync/Aux pair
- L58 _public typedef_ `using SyncType = typename StateType::SyncType;`
- L59 _public typedef_ `using AuxType = typename StateType::AuxType;`
- L61 _public member_ `const SyncType* Sync;`
- L62 _public member_ `const AuxType* Aux;`
- L64 _public function_ `TSyncAuxPair(const SyncType* InSync, const AuxType* InAux) : Sync(InSync), Aux(InAux)`
- L69 _public function_ `template<typename T> TSyncAuxPair(const TSyncAuxPair<T>& Other) : Sync(Other.Sync), Aux(Other.Aux)` — Allows implicit downcasting to a parent simulation's types

#### Free symbols / members of external scopes

- L13 _function_ `inline const TCHAR* LexToString(ENetworkPredictionStateType A)`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionStateView.h` (Public)


#### struct `FNetworkPredictionStateView`  
`struct FNetworkPredictionStateView`  
_L10-75_
- desc: Generic view into a managed instance's state
- L15 _public member_ `int32 PendingFrame = 0;` — Simulation PendingFrame number. This is the "server frame" number that will be used as input for the next tick. This can be used for server authoritative timers/countdowns etc but should not be used to index into local frame buffer storage. Local frame numbers are stored on the NetworkPredictionWorldManager's internal tick states.
- L20 _public member_ `int32 SimTimeMS = 0;` — Latest Simulation time. Like PendingFrame this is the "server time" and is synchronized. This is redundant in fixed tick scenerios but is needed for independent ticking (Consider: maybe this is rarely used enough that a more expensive lookup would be better than cacheing it in the view?)
- L23 _public member_ `bool bTickInProgress = false;` — ::SimulationTick is in progress
- L28 _public member_ `void* PendingInputCmd = nullptr;` — Pending states: these are what will be used as input into the next SimulationTick call, if we are running a local tick. if there is no local tick, for example in interpolation mode, these will set to the latest consume simulation frame. (so, latest simulation frame used in interpolation for example. But not necessarily the latest received frame)
- L29 _public member_ `void* PendingSyncState = nullptr;`
- L30 _public member_ `void* PendingAuxState = nullptr;`
- L34 _public member_ `void* PresentationSyncState = nullptr;` — Presentation states: the latest locally smoothed/interpolated states that will not be fed back into the sim (these will be null in cases where there is no smoothing/interpolation)
- L35 _public member_ `void* PresentationAuxState = nullptr;`
- L39 _public member_ `void* PrevPresentationSyncState = nullptr;` — Previous presentation states: these may be used by a smoothing service to represent state that we're smoothing away from. These will not be fed back into the simulation, and they will be null in cases where there is no smoothing.
- L40 _public member_ `void* PrevPresentationAuxState = nullptr;`
- L44 _public member_ `FNetSimCueDispatcher* CueDispatcher = nullptr;` — CueDispatcher is exposed so that game code can invoke OOB cues Future versions may move this / make Invoking OOB cues go through a different API
- L46 _public function_ `void UpdateView(int32 Frame, int32 InSimTimMS, void* Input, void* Sync, void* Aux)`
- L56 _public function_ `void UpdatePresentationView(void* Sync, void* Aux)`
- L62 _public function_ `void UpdatePrevPresentationView(void* Sync, void* Aux)`
- L68 _public function_ `void ClearPresentationView()`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionTickState.h` (Public)


#### struct `FNetSimTimeStep`  
`struct FNetSimTimeStep`  
_L9-24_
- desc: TimeStep info that is passed into SimulationTick
- L12 _public member_ `int32 StepMS;` — The delta time step for this tick
- L17 _public member_ `int32 TotalSimulationTime;` — How much simulation time has ran up until this point. This is "Server time", e.g, everyone agrees on this time and it can be used for timers/cooldowns etc in the simulation code. It can be stored in sync/aux state and reconciles pred vs authority. This will be 0 the first time ::SimulationTick runs (globally for fix tick, local tick and per-sim for remote independent sims)
- L23 _public member_ `int32 Frame;` — The Simulation Frame number we are computing in this tick, E.g, the output frame. This is the global, everyone agrees-upon frame number. E.g, the "server frame" number. This will be 1 the first time ::SimulationTick runs. (0 is the starting input and is not generated in a Tick) (globally for fix tick, local tick and per-sim for remote independent sims)

#### struct `FServiceTimeStep`  
`struct FServiceTimeStep`  
_L27-35_
- desc: Data that is needed to tick the internal ticking services but is not passed to the user code
- L30 _public member_ `int32 LocalInputFrame;` — The local frame number, this is what should be used when mapping to local frame buffers for storage
- L31 _public member_ `int32 LocalOutputFrame;`
- L34 _public member_ `int32 EndTotalSimulationTime;` — Ending total sim time, needed for Cue dispatching

#### struct `FFixedTickState`  
`struct FFixedTickState`  
_L44-103_
- L47 _public member_ `int32 FixedStepMS = 33;` — FixedStepMS that simulations should use
- L51 _public member_ `float FixedStepRealTimeMS = 1.0f /30.0f;` — Realtime steps. That is, one of these = one FixedStepMS in simulation time. This means sim time ticks slightly slower than real time.
- L54 _public member_ `float FixedStepDilatedRealTimeMS = 1.0f / 30.0f;` — If time dilation is enabled, one of these = one FixedStepMS in simulation time. This will shrink or grow slightly as network latency changes.
- L57 _public member_ `int32 PendingFrame=0;` — Next frame to be ticked (used as input to generated PendingFrame+1)
- L60 _public member_ `int32 ConfirmedFrame=INDEX_NONE;` — Latest confirmed local frame number. Anything at or before this frame is "set in stone"
- L65 _public member_ `int32 Offset=0;` — Maps ForwardPredicted authority frames to local frame. E.g, server says "I processed your frame 1 on my frame 101" client calcs Offset as 100. "LocalFrame" = "ServerFrame" - Offset.
- L68 _public member_ `float UnspentTimeMS = 0.f;` — Accumulates raw delta time into our fixed steps
- L71 _public member_ `bool bHasTimeDilation = false;` — Signals whether any time dilation is active. If so, use @SuggestedTimeDilation
- L74 _public member_ `float SuggestedTimeDilation = 1.f;` — Only valid when bHasTimeDilation is true. Represents a percentage of time speed up/down.  1.0 = no dilation.
- L87 _public member_ `FInterpolationState Interpolation;`
- L89 _public function_ `FNetSimTimeStep GetNextTimeStep() const`
- L94 _public function_ `FServiceTimeStep GetNextServiceTimeStep() const`
- L99 _public function_ `int32 GetTotalSimTimeMS() const`

#### struct `FFixedTickState::FInterpolationState`  
`struct FInterpolationState`  
_L76-85_
- L78 _public member_ `float AccumulatedTimeMS = 0.f;` — accumulated real time
- L79 _public member_ `int32 LatestRecvFrameAP = INDEX_NONE;` — Latest server frame we received, set by the AP
- L80 _public member_ `int32 LatestRecvFrameSP = INDEX_NONE;` — Latest server frame we received, set by the SP
- L81 _public member_ `int32 ToFrame = INDEX_NONE;` — Where we are interpolating to (ToFrame-1 -> ToFrame. Both should be valid at all times for anyone interpolating)
- L82 _public member_ `float PCT = 0.f;`
- L84 _public member_ `int32 InterpolatedTimeMS = 0;`

#### struct `FVariableTickState`  
`struct FVariableTickState`  
_L106-145_
- desc: Variable tick state tracking for independent tick services
- L114 _public member_ `TNetworkPredictionBuffer<FFrame> Frames;`
- L116 _public function_ `FVariableTickState() : Frames(64)`
- L118 _public member_ `int32 PendingFrame = 0;`
- L119 _public member_ `int32 ConfirmedFrame = INDEX_NONE;`
- L121 _public member_ `float UnspentTimeMS = 0.f;`
- L129 _public member_ `FInterpolationState Interpolation;`
- L131 _public function_ `FNetSimTimeStep GetNextTimeStep() const`
- L136 _public function_ `FNetSimTimeStep GetNextTimeStep(const FFrame& PendingFrameData) const`
- L141 _public function_ `FServiceTimeStep GetNextServiceTimeStep(const FFrame& PendingFrameData) const`

#### struct `FVariableTickState::FFrame`  
`struct FFrame`  
_L108-112_
- L110 _public member_ `int32 DeltaMS=0;`
- L111 _public member_ `int32 TotalMS=0;`

#### struct `FVariableTickState::FInterpolationState`  
`struct FInterpolationState`  
_L123-127_
- L125 _public member_ `float fTimeMS = 0.f;`
- L126 _public member_ `int32 LatestRecvTimeMS = 0;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Chaos`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionTrace.h` (Public)


#### class `FNetworkPredictionTrace`  
`class FNetworkPredictionTrace`  
_L129-206_
- L134 _public function_ `template<typename ModelDef> static void TraceSimulationCreated(FNetworkPredictionID ID, typename ModelDef::Driver* Driver)`
- L141 _public prototype_ `static void TraceWorldFrameStart(UGameInstance* GameInstance, float DeltaSeconds);`
- L142 _public prototype_ `static void TraceSimulationConfig(int32 TraceID, ENetRole NetRole, bool bHasNetConnection, const FNetworkPredictionInstanceArchetype& Archetype, const FNetworkPredictionInstanceConfig& Config, int32 ServiceMask);`
- L144 _public prototype_ `static void TracePIEStart();`
- L145 _public prototype_ `static void TraceWorldPreInit();`
- L146 _public prototype_ `static void TraceSystemFault(const TCHAR* Fmt, ...);`
- L148 _public prototype_ `static void TraceSimulationScope(int32 TraceID);`
- L150 _public prototype_ `static void TraceTick(int32 StartMS, int32 DeltaMS, int32 OutputFrame);`
- L151 _public prototype_ `static void TraceSimTick(int32 TraceID);`
- L153 _public prototype_ `static void TraceSimState(int32 TraceID);` — Used to lazy update user state after a simtick
- L155 _public prototype_ `static void TraceNetRecv(int32 Frame, int32 TimeMS);`
- L157 _public prototype_ `static void TraceReconcile(const FAnsiStringView& StrView);`
- L159 _public prototype_ `static void TraceShouldReconcile(int32 TraceID);`
- L160 _public prototype_ `static void TraceRollbackInject(int32 TraceID);`
- L162 _public prototype_ `static void TracePushInputFrame(int32 Frame);`
- L163 _public prototype_ `static void TraceFixedTickOffset(int32 Offset, bool bChanged);`
- L164 _public prototype_ `static void TraceBufferedInput(int32 NumBufferedFrames, bool bFault);`
- L165 _public prototype_ `static void TraceProduceInput(int32 TraceID);`
- L167 _public prototype_ `static void TraceOOBStateMod(int32 SimulationId, int32 Frame, const FAnsiStringView& StrView);`
- L177 _public function_ `template<typename ModelDef, typename StateType> static void TraceUserState(const StateType* State, ETraceUserState StateTypeEnum)`
- L198 _private prototype_ `static void TraceSimulationCreated_Internal(FNetworkPredictionID ID, FStringBuilderBase& Builder);`
- L203 _private prototype_ `static void TraceUserState_Internal(ETraceUserState StateType, FAnsiStringBuilderBase& Builder);`

#### enum `FNetworkPredictionTrace::ETraceUserState`  
`enum class ETraceUserState : uint8`  
_L169-174_
- L171 _public enumerator_ `Input`
- L172 _public enumerator_ `Sync`
- L173 _public enumerator_ `Aux`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NETWORKPREDICTION_API`
- L15 _macro_ `#define UE_NP_TRACE_ENABLED !(UE_BUILD_SHIPPING || UE_BUILD_TEST)`
- L20 _macro_ `#define UE_NP_TRACE_USER_STATES_ENABLED 1`
- L28 _macro_ `#define UE_NP_TRACE_RECONCILE(Condition, Str) if (Condition) { FNetworkPredictionTrace::TraceReconcile(Str); return true; }` — Traces what caused a reconcile (added in user ShouldReconcile function) Note this actually adds the 'return true' logic for reconciliation
- L31 _macro_ `#define UE_NP_TRACE_SIM(TraceID) FNetworkPredictionTrace::TraceSimulationScope(TraceID)` — General trace to push the active simulation's trace ID
- L34 _macro_ `#define UE_NP_TRACE_SIM_CREATED(ID, Driver, ModelDef) FNetworkPredictionTrace::TraceSimulationCreated<ModelDef>(ID, Driver)` — Called when simulation is created. (Note this also sets a Scope for tracing the initial user states next)
- L37 _macro_ `#define UE_NP_TRACE_SIM_CONFIG(TraceID, NetRole, bHasNetConnection, Archetype, Config, ServiceMask) FNetworkPredictionTrace::TraceSimulationConfig(TraceID, NetRole, bHasNetConnection, Archetype, Config, (int32)ServiceMask);` — Trace config of sim changing
- L40 _macro_ `#define UE_NP_TRACE_PIE_START() FNetworkPredictionTrace::TracePIEStart()` — Called when a PIE session is started. This is so we can keep our sets of worlds/simulations separate in between runs.
- L43 _macro_ `#define UE_NP_TRACE_WORLD_PREINIT() FNetworkPredictionTrace::TraceWorldPreInit()` — Called during WorldPreInit. This mainly just ensure we have a valid trace context so that actors loaded with the map can trace their \initialization
- L46 _macro_ `#define UE_NP_TRACE_SYSTEM_FAULT(Format, ...) FNetworkPredictionTrace::TraceSystemFault(TEXT(Format), ##__VA_ARGS__)` — Generic fault/error message that gets bubbled up in the NP Insights UI
- L49 _macro_ `#define UE_NP_TRACE_WORLD_FRAME_START(GameInstance, DeltaSeconds) FNetworkPredictionTrace::TraceWorldFrameStart(GameInstance, DeltaSeconds)` — Trace engine frame starting for GameInstance
- L52 _macro_ `#define UE_NP_TRACE_PUSH_TICK(StartMS, DeltaMS, OutputFrame) FNetworkPredictionTrace::TraceTick(StartMS, DeltaMS, OutputFrame)` — Called to set the general tick state
- L55 _macro_ `#define UE_NP_TRACE_SIM_TICK(TraceID) FNetworkPredictionTrace::TraceSimTick(TraceID)` — Called when an actual instance ticks (after calling UE_NP_TRACE_PUSH_TICK)
- L58 _macro_ `#define UE_NP_TRACE_SIM_STATE(TraceID) FNetworkPredictionTrace::TraceSimState(TraceID)` — General trace to push the active simulation's trace ID and setup for updating the traced state for an already ticked frame (Used to update async data after completion)
- L61 _macro_ `#define UE_NP_TRACE_NET_RECV(Frame, TimeMS) FNetworkPredictionTrace::TraceNetRecv(Frame, TimeMS)` — Called when we receive networked data (regardless of what we end up doing with it)
- L64 _macro_ `#define UE_NP_TRACE_SHOULD_RECONCILE(TraceID) FNetworkPredictionTrace::TraceShouldReconcile(TraceID)` — Called when ShouldReconcile returns true, signaling a rollback/correction is required
- L67 _macro_ `#define UE_NP_TRACE_ROLLBACK_INJECT(TraceID) FNetworkPredictionTrace::TraceRollbackInject(TraceID)` — Called when received data is injected back into the local frame buffer (Note that the sim itself may not have been in error, we may be rolling "everything" back)
- L70 _macro_ `#define UE_NP_TRACE_PUSH_INPUT_FRAME(Frame) FNetworkPredictionTrace::TracePushInputFrame(Frame)` — Called before running input producing services
- L73 _macro_ `#define UE_NP_TRACE_FIXED_TICK_OFFSET(Offset, bChanged) FNetworkPredictionTrace::TraceFixedTickOffset(Offset, bChanged)` — Traces current local frame # -> server frame # offset
- L76 _macro_ `#define UE_NP_TRACE_BUFFERED_INPUT(NumBufferedFrames, bFault) FNetworkPredictionTrace::TraceBufferedInput(NumBufferedFrames, bFault)` — Called to trace buffered input state
- L79 _macro_ `#define UE_NP_TRACE_PRODUCE_INPUT(TraceID) FNetworkPredictionTrace::TraceProduceInput(TraceID)` — Trace call to Driver's ProduceInput function
- L82 _macro_ `#define UE_NP_TRACE_OOB_STATE_MOD(TraceID, Frame, StrView) FNetworkPredictionTrace::TraceOOBStateMod(TraceID, Frame, StrView)` — Called to indicate we are about to write state to the buffers outside of the normal simulation tick/netrecive. TODO: add char* identifier to debug where the mod came from
- L85 _macro_ `#define UE_NP_TRACE_USER_STATE_INPUT(ModelDef, UserState) FNetworkPredictionTrace::TraceUserState<ModelDef>(UserState, FNetworkPredictionTrace::ETraceUserState::Input)` — Called whenever a new user state has been inserted into the buffers. Analysis will determine "how" it got there from previous trace events
- L86 _macro_ `#define UE_NP_TRACE_USER_STATE_SYNC(ModelDef, UserState) FNetworkPredictionTrace::TraceUserState<ModelDef>(UserState, FNetworkPredictionTrace::ETraceUserState::Sync)`
- L87 _macro_ `#define UE_NP_TRACE_USER_STATE_AUX(ModelDef, UserState) FNetworkPredictionTrace::TraceUserState<ModelDef>(UserState, FNetworkPredictionTrace::ETraceUserState::Aux)`
- L94 _macro_ `#define UE_NP_TRACE_RECONCILE(Condition, Str) if (Condition) { return true; }` — Compiled out
- L95 _macro_ `#define UE_NP_TRACE_SIM(...)`
- L96 _macro_ `#define UE_NP_TRACE_SIM_CREATED(...)`
- L97 _macro_ `#define UE_NP_TRACE_SIM_CONFIG(...)`
- L99 _macro_ `#define UE_NP_TRACE_PIE_START(...)`
- L100 _macro_ `#define UE_NP_TRACE_WORLD_PREINIT(...)`
- L101 _macro_ `#define UE_NP_TRACE_SYSTEM_FAULT(Format, ...) UE_LOG(LogNetworkPrediction, Warning, TEXT(Format), ##__VA_ARGS__);`
- L102 _macro_ `#define UE_NP_TRACE_WORLD_FRAME_START(...)`
- L103 _macro_ `#define UE_NP_TRACE_PUSH_TICK(...)`
- L104 _macro_ `#define UE_NP_TRACE_SIM_TICK(...)`
- L105 _macro_ `#define UE_NP_TRACE_SIM_STATE(...)`
- L106 _macro_ `#define UE_NP_TRACE_NET_RECV(...)`
- L107 _macro_ `#define UE_NP_TRACE_SHOULD_RECONCILE(...)`
- L108 _macro_ `#define UE_NP_TRACE_ROLLBACK_INJECT(...)`
- L109 _macro_ `#define UE_NP_TRACE_PUSH_INPUT_FRAME(...)`
- L110 _macro_ `#define UE_NP_TRACE_FIXED_TICK_OFFSET(...)`
- L111 _macro_ `#define UE_NP_TRACE_PRODUCE_INPUT(...)`
- L112 _macro_ `#define UE_NP_TRACE_BUFFERED_INPUT(...)`
- L113 _macro_ `#define UE_NP_TRACE_OOB_STATE_MOD(...)`
- L115 _macro_ `#define UE_NP_TRACE_USER_STATE_INPUT(...)`
- L116 _macro_ `#define UE_NP_TRACE_USER_STATE_SYNC(...)`
- L117 _macro_ `#define UE_NP_TRACE_USER_STATE_AUX(...)`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionUtil.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE_NP`
- L11 _macro_ `#define NP_MAX_ASYNC_MODEL_DEFS 16`
- L14 _variable_ `const int32 MaxAsyncModelDefs = NP_MAX_ASYNC_MODEL_DEFS;` (scope `UE_NP`)
- L17 _macro_ `#define NP_NUM_FRAME_STORAGE 64`
- L20 _variable_ `const int32 NumFramesStorage = NP_NUM_FRAME_STORAGE;` (scope `UE_NP`)
- L23 _macro_ `#define NP_FRAME_STORAGE_GROWTH 8`
- L26 _variable_ `const int32 FrameStorageGrowth = NP_FRAME_STORAGE_GROWTH;` (scope `UE_NP`)
- L29 _macro_ `#define NP_FRAME_INPUTCMD_BUFFER_SIZE 16`
- L32 _variable_ `const int32 InputCmdBufferSize = NP_FRAME_INPUTCMD_BUFFER_SIZE;` (scope `UE_NP`)
- L35 _macro_ `#define NP_INLINE_SIMOBJ_INPUTS 3`
- L38 _variable_ `const int32 InlineSimObjInputs = NP_INLINE_SIMOBJ_INPUTS;` (scope `UE_NP`)
- L44 _function_ `template<typename BitArrayType> void NpResizeAndSetBit(BitArrayType& BitArray, int32 Index, bool Value=true)` — Sets index to value, resizing bit array if necessary and setting new bits to false
- L59 _function_ `template<typename BitArrayType> void NpResizeBitArray(BitArrayType& BitArray, int32 NewNum)` — Resize BitArray to NewNum, setting default value of new bits to false
- L72 _function_ `template<typename BitArrayType> void NpClearBitArray(BitArrayType& BitArray)` — Set bit array contents to false
- L78 _function_ `template<typename ArrayType> void NpResizeForIndex(ArrayType& Array, int32 Index)`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionWorldManager.h` (Public)


#### class `UNetworkPredictionWorldManager`  
`class UNetworkPredictionWorldManager : public UWorldSubsystem`  
_L22-171_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L27 _public member_ `static UNetworkPredictionWorldManager* ActiveInstance;`
- L29 _public prototype_ `UNetworkPredictionWorldManager();`
- L33 _public member_ `TObjectPtr<ANetworkPredictionReplicatedManager> ReplicatedManager = nullptr;` — `UPROPERTY()` — Server created, replicated manager (only used for centralized/system wide data replication)
- L36 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Subsystem Init/Deinit
- L37 _public prototype_ `virtual void Deinitialize() override;`
- L41 _public function_ `FNetworkPredictionID CreateSimulationID(const bool bForClient)` — Returns unique ID for a new simulation instance regardless of type. Clients set bForClient to get a negative, temp ID to use until server version comes in
- L47 _public function_ `template<typename ModelDef> void RemapClientSimulationID(FNetworkPredictionID ClientID, FNetworkPredictionID ServerID)`
- L59 _public function_ `template<typename ModelDef> void RegisterInstance(FNetworkPredictionID ID, const TNetworkPredictionModelInfo<ModelDef>& ModelInfo)`
- L71 _public function_ `template<typename ModelDef> void UnregisterInstance(FNetworkPredictionID ID)`
- L87 _public prototype_ `template<typename ModelDef> void ConfigureInstance(FNetworkPredictionID ID, const FNetworkPredictionInstanceArchetype& Archetype, const FNetworkPredictionInstanceConfig& Config, FReplicationProxySet RepProxies, ENetRole Role, bool bHasNetConnection);`
- L89 _public prototype_ `ENetworkPredictionTickingPolicy PreferredDefaultTickingPolicy() const;`
- L91 _public prototype_ `void SyncNetworkPredictionSettings(const UNetworkPredictionSettingsObject* Settings);`
- L93 _public function_ `const FNetworkPredictionSettings& GetSettings() const`
- L95 _public function_ `const FFixedTickState& GetFixedTickState() const`
- L96 _public function_ `const FVariableTickState& GetVariableTickState() const`
- L100 _private member_ `FNetworkPredictionSettings Settings;`
- L102 _private member_ `FFixedTickState FixedTickState;`
- L103 _private member_ `FVariableTickState VariableTickState;`
- L104 _private member_ `FNetworkPredictionServiceRegistry Services;`
- L106 _private prototype_ `void OnWorldPreTick(UWorld* InWorld, ELevelTick InLevelTick, float InDeltaSeconds);`
- L107 _private prototype_ `void ReconcileSimulationsPostNetworkUpdate();`
- L108 _private prototype_ `void BeginNewSimulationFrame(UWorld* InWorld, ELevelTick InLevelTick, float InDeltaSeconds);`
- L112 _private prototype_ `void OnWorldPreTick_Internal(float InDeltaSeconds, float InFixedFrameRate);`
- L113 _private prototype_ `void ReconcileSimulationsPostNetworkUpdate_Internal();`
- L114 _private prototype_ `void BeginNewSimulationFrame_Internal(float InDeltaSeconds);`
- L116 _private member_ `FDelegateHandle PreTickDispatchHandle;`
- L117 _private member_ `FDelegateHandle PostTickDispatchHandle;`
- L118 _private member_ `FDelegateHandle PreWorldActorTickHandle;`
- L120 _private member_ `int32 InstanceSpawnCounter = 1;`
- L121 _private member_ `int32 TempClientSpawnCount = -2;` — negative IDs for client to use before getting server assigned id
- L122 _private member_ `int32 LastFixedTickOffset = 0;`
- L125 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHandleDeferredServiceConfig, UNetworkPredictionWorldManager*);` — Callbacks to change subscribed services, that couldn't be made inline
- L126 _private member_ `FOnHandleDeferredServiceConfig DeferredServiceConfigDelegate;`
- L127 _private member_ `bool bLockServices = false;` — Services are locked and we can't
- L132 _private prototype_ `template<typename ModelDef> void BindServerNetRecv_Fixed(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore);`
- L135 _private prototype_ `template<typename ModelDef> void BindServerNetRecv_Independent(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore);`
- L140 _private prototype_ `template<typename ReplicatorType, typename ModelDef=typename ReplicatorType::ModelDef> void BindClientNetRecv_Fixed(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole);`
- L143 _private prototype_ `template<typename ReplicatorType, typename ModelDef=typename ReplicatorType::ModelDef> void BindClientNetRecv_Independent(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole);`
- L148 _private prototype_ `template<typename ReplicatorType, typename ModelDef=typename ReplicatorType::ModelDef> void BindNetSend_Fixed(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore);`
- L151 _private prototype_ `template<typename ReplicatorType, typename ModelDef=typename ReplicatorType::ModelDef> void BindNetSend_IndependentLocal(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore);`
- L154 _private prototype_ `template<typename ReplicatorType, typename ModelDef=typename ReplicatorType::ModelDef> void BindNetSend_IndependentRemote(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore);`
- L159 _private prototype_ `template<typename ReplicatorType, typename ModelDef=typename ReplicatorType::ModelDef> void BindReplayNetSendRecv_Fixed(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole);`
- L162 _private prototype_ `template<typename ReplicatorType, typename ModelDef = typename ReplicatorType::ModelDef> void BindReplayNetSendRecv_IndependentLocal(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole);`
- L165 _private prototype_ `template<typename ReplicatorType, typename ModelDef = typename ReplicatorType::ModelDef> void BindReplayNetSendRecv_IndependentRemote(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole);`
- L170 _private prototype_ `template<typename ModelDef> void InitClientRecvData(FNetworkPredictionID ID, TClientRecvData<ModelDef>& ClientRecvData, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole);`
- L177 _function_ `template<typename ModelDef> void UNetworkPredictionWorldManager::ConfigureInstance(FNetworkPredictionID ID, const FNetworkPredictionInstanceArchetype& Archetype, const FNetworkPredictionInstanceConfig& Config, FReplicationProxySet RepProxies, ENetRole Role, bool bHasNetConnection)` — This is the function that takes the config and current network state (role/connection) and subscribes to the appropriate internal NetworkPrediction services.
- L436 _function_ `template<typename ModelDef> void UNetworkPredictionWorldManager::BindServerNetRecv_Fixed(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore)`
- L460 _function_ `template<typename ModelDef> void UNetworkPredictionWorldManager::BindServerNetRecv_Independent(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore)`
- L501 _function_ `template<typename ReplicatorType, typename ModelDef> void UNetworkPredictionWorldManager::BindClientNetRecv_Fixed(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole)`
- L527 _function_ `template<typename ReplicatorType, typename ModelDef> void UNetworkPredictionWorldManager::BindClientNetRecv_Independent(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole)`
- L566 _function_ `template<typename ReplicatorType, typename ModelDef> void UNetworkPredictionWorldManager::BindNetSend_Fixed(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore)`
- L582 _function_ `template<typename ReplicatorType, typename ModelDef> void UNetworkPredictionWorldManager::BindNetSend_IndependentLocal(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore)`
- L598 _function_ `template<typename ReplicatorType, typename ModelDef> void UNetworkPredictionWorldManager::BindNetSend_IndependentRemote(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore)`
- L621 _function_ `template<typename ReplicatorType, typename ModelDef> void UNetworkPredictionWorldManager::BindReplayNetSendRecv_Fixed(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole)`
- L655 _function_ `template<typename ReplicatorType, typename ModelDef> void UNetworkPredictionWorldManager::BindReplayNetSendRecv_IndependentLocal(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole)`
- L689 _function_ `template<typename ReplicatorType, typename ModelDef> void UNetworkPredictionWorldManager::BindReplayNetSendRecv_IndependentRemote(FNetworkPredictionID ID, FReplicationProxy* RepProxy, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole)`
- L728 _function_ `template<typename ModelDef> void UNetworkPredictionWorldManager::InitClientRecvData(FNetworkPredictionID ID, TClientRecvData<ModelDef>& ClientRecvData, TModelDataStore<ModelDef>* DataStore, ENetRole NetRole)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NETWORKPREDICTION_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Net` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Net`)
- L80 _function_ `` (scope `UNetworkPredictionWorldManager::UnregisterInstance`)
- L125 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHandleDeferredServiceConfig, UNetworkPredictionWorldManager*);` — Callbacks to change subscribed services, that couldn't be made inline
- L401 _function_ `` (scope `UNetworkPredictionWorldManager::ConfigureInstance`)
- L450 _function_ `` (scope `UNetworkPredictionWorldManager::BindServerNetRecv_Fixed`)
- L480 _function_ `` (scope `UNetworkPredictionWorldManager::BindServerNetRecv_Independent`)
- L516 _function_ `` (scope `UNetworkPredictionWorldManager::BindClientNetRecv_Fixed`)
- L542 _function_ `` (scope `UNetworkPredictionWorldManager::BindClientNetRecv_Independent`)
- L574 _function_ `` (scope `UNetworkPredictionWorldManager::BindNetSend_Fixed`)
- L590 _function_ `` (scope `UNetworkPredictionWorldManager::BindNetSend_IndependentLocal`)
- L606 _function_ `` (scope `UNetworkPredictionWorldManager::BindNetSend_IndependentRemote`)
- L636 _function_ `` (scope `UNetworkPredictionWorldManager::BindReplayNetSendRecv_Fixed`)
- L670 _function_ `` (scope `UNetworkPredictionWorldManager::BindReplayNetSendRecv_IndependentLocal`)
- L707 _function_ `` (scope `UNetworkPredictionWorldManager::BindReplayNetSendRecv_IndependentRemote`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionInstanceData.h` (Public)


#### enum `ENetworkPredictionService`  
`enum class ENetworkPredictionService : uint32`  
_L12-49_
- desc: Enum that maps to internal NetworkPrediction services, see notes in NetworkPredictionServiceRegistry.h
- L14 _public enumerator_ `None = 0`
- L17 _public enumerator_ `ServerRPC = 1 << 0` — Common services that fix/independent can share
- L18 _public enumerator_ `MAX_COMMON = ServerRPC`
- L21 _public enumerator_ `FixedRollback = 1 << 1` — Services exclusive to fix tick mode
- L22 _public enumerator_ `FixedExtrapolate = 1 << 2` — TODO
- L23 _public enumerator_ `FixedInterpolate = 1 << 3`
- L24 _public enumerator_ `FixedInputLocal = 1 << 4`
- L25 _public enumerator_ `FixedInputRemote = 1 << 5`
- L26 _public enumerator_ `FixedTick = 1 << 6`
- L27 _public enumerator_ `FixedSmoothing = 1 << 7`
- L28 _public enumerator_ `FixedFinalize = 1 << 8`
- L29 _public enumerator_ `MAX_FIXED = FixedFinalize`
- L32 _public enumerator_ `IndependentRollback = 1 << 10` — Services exclusive to independent tick mode
- L33 _public enumerator_ `IndependentExtrapolate = 1 << 11` — TODO
- L34 _public enumerator_ `IndependentInterpolate = 1 << 12`
- L36 _public enumerator_ `IndependentLocalInput = 1 << 13`
- L37 _public enumerator_ `IndependentLocalTick = 1 << 14`
- L38 _public enumerator_ `IndependentRemoteTick = 1 << 15`
- L40 _public enumerator_ `IndependentSmoothingFinalize = 1 << 16` — TODO
- L41 _public enumerator_ `IndependentLocalFinalize = 1 << 17`
- L42 _public enumerator_ `IndependentRemoteFinalize = 1 << 18`
- L43 _public enumerator_ `MAX_INDEPENDENT = IndependentRemoteFinalize`
- L46 _public enumerator_ `ANY_COMMON = (MAX_COMMON<<1)-1` — Helper masks
- L47 _public enumerator_ `ANY_FIXED = ((MAX_FIXED<<1)-1) & ~ANY_COMMON`
- L48 _public enumerator_ `ANY_INDEPENDENT = (((MAX_INDEPENDENT<<1)-1) & ~ANY_FIXED) & ~ANY_COMMON`

#### struct `TInstanceData`  
`template<typename ModelDef=FNetworkPredictionModelDef> struct TInstanceData`  
_L55-64_
- desc: Basic data that all instances have
- L57 _public member_ `TNetworkPredictionModelInfo<ModelDef> Info;`
- L59 _public member_ `ENetRole NetRole = ROLE_None;`
- L60 _public member_ `TUniqueObj<TNetSimCueDispatcher<ModelDef>> CueDispatcher;` — Should maybe be moved out?
- L62 _public member_ `int32 TraceID;`
- L63 _public member_ `ENetworkPredictionService ServiceMask = ENetworkPredictionService::None;`

#### struct `TInstanceFrameState`  
`template<typename ModelDef=FNetworkPredictionModelDef> struct TInstanceFrameState`  
_L68-86_
- desc: Frame data that instances with StateTypes will have.
- L70 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L71 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L72 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L73 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L82 _public member_ `TNetworkPredictionBuffer<FFrame> Buffer;`
- L84 _public function_ `TInstanceFrameState() : Buffer(64)`

#### struct `TInstanceFrameState::FFrame`  
`struct FFrame`  
_L75-80_
- L77 _public member_ `TConditionalState<InputType> InputCmd;`
- L78 _public member_ `TConditionalState<SyncType> SyncState;`
- L79 _public member_ `TConditionalState<AuxType> AuxState;`

#### struct `TClientRecvData`  
`template<typename ModelDef=FNetworkPredictionModelDef> struct TClientRecvData`  
_L90-109_
- desc: Data the client receives from the server
- L92 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L93 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L94 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L95 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L97 _public member_ `int32 ServerFrame;` — Fixed tick || Independent AP only
- L98 _public member_ `int32 SimTimeMS;` — Independent tick only
- L100 _public member_ `TConditionalState<InputType> InputCmd;` — SP Only
- L101 _public member_ `TConditionalState<SyncType> SyncState;`
- L102 _public member_ `TConditionalState<AuxType> AuxState;`
- L105 _public member_ `int32 TraceID = INDEX_NONE;` — Acceleration data.
- L106 _public member_ `int32 InstanceIdx = INDEX_NONE;` — Index into TModelDataStore::Instances
- L107 _public member_ `int32 FramesIdx = INDEX_NONE;` — Index into TModelDataStore::Frames
- L108 _public member_ `ENetRole NetRole = ROLE_None;`

#### struct `TServerRecvData_Fixed`  
`template<typename ModelDef=FNetworkPredictionModelDef> struct TServerRecvData_Fixed`  
_L113-128_
- desc: Data the server receives from a fixed ticking AP client
- L115 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L116 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L118 _public member_ `TNetworkPredictionBuffer<TConditionalState<InputType>> InputBuffer;`
- L121 _public member_ `int32 LastConsumedFrame = INDEX_NONE;` — Note that these are client frame numbers, they do not match the servers local PendingFrame
- L122 _public member_ `int32 LastRecvFrame = INDEX_NONE;`
- L124 _public member_ `int32 TraceID = INDEX_NONE;`
- L126 _public function_ `TServerRecvData_Fixed() : InputBuffer(32)`

#### struct `TServerRecvData_Independent`  
`template<typename ModelDef=FNetworkPredictionModelDef> struct TServerRecvData_Independent`  
_L132-159_
- desc: Data the server receives from an independent ticking AP client
- L134 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L135 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L143 _public function_ `TServerRecvData_Independent() : InputBuffer(16)`
- L146 _public member_ `int32 PendingFrame = 0;`
- L147 _public member_ `int32 TotalSimTimeMS = 0;`
- L148 _public member_ `float UnspentTimeMS = 0.f;`
- L150 _public member_ `int32 LastConsumedFrame = INDEX_NONE;`
- L151 _public member_ `int32 LastRecvFrame = INDEX_NONE;`
- L153 _public member_ `TNetworkPredictionBuffer<FFrame> InputBuffer;`
- L156 _public member_ `int32 TraceID = INDEX_NONE;` — Acceleration data.
- L157 _public member_ `int32 InstanceIdx = INDEX_NONE;` — Index into TModelDataStore::Instances
- L158 _public member_ `int32 FramesIdx = INDEX_NONE;` — Index into TModelDataStore::Frames

#### struct `TServerRecvData_Independent::FFrame`  
`struct FFrame`  
_L137-141_
- L139 _public member_ `TConditionalState<InputType> InputCmd;`
- L140 _public member_ `int32 DeltaTimeMS;`

#### struct `TModelDataStore`  
`template<typename ModelDef=FNetworkPredictionModelDef> struct TModelDataStore`  
_L163-175_
- desc: Stores all public data for a given model def
- L165 _public member_ `TStableInstanceMap<TInstanceData<ModelDef>> Instances;`
- L167 _public member_ `TInstanceMap<TInstanceFrameState<ModelDef>> Frames;`
- L169 _public member_ `TInstanceMap<TClientRecvData<ModelDef>> ClientRecv;`
- L170 _public member_ `TBitArray<> ClientRecvBitMask;`
- L172 _public member_ `TInstanceMap<TServerRecvData_Fixed<ModelDef>> ServerRecv;`
- L174 _public member_ `TInstanceMap<TServerRecvData_Independent<ModelDef>> ServerRecv_IndependentTick;`

#### Free symbols / members of external scopes

- L51 _prototype_ `ENUM_CLASS_FLAGS(ENetworkPredictionService);`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionInstanceMap.h` (Public)


#### struct `TInstanceMap`  
`template<typename T> struct TInstanceMap`  
_L13-71_
- desc: Generic associative container for instance data keyed off of the FNetworkPredictionID SortedMap + SparseArray provides: -O(log n) add/remove. -Stable index that can be cached for O(1) lookup in various service acceleration structures -Data* are not stable out of this data structure
- L15 _public function_ `T& FindOrAdd(const FNetworkPredictionID& ID)`
- L20 _public function_ `T* Find(const FNetworkPredictionID& ID)`
- L31 _public function_ `void Remove(const FNetworkPredictionID& ID)`
- L41 _public function_ `int32 GetIndexChecked(const FNetworkPredictionID& ID)`
- L46 _public function_ `int32 GetIndex(const FNetworkPredictionID& ID)`
- L58 _public function_ `T& GetByIndexChecked(int32 idx)`
- L67 _private member_ `TSortedMap<int32, FIndex> Lookup;` — Sorted map of priority (spawnID -> stable index into SparseArray)
- L68 _private member_ `int32 LastFreeIndex = 0;`
- L70 _private member_ `TSparseArray<T> Data;`

#### struct `TInstanceMap::FIndex`  
`struct FIndex`  
_L66-66_
- desc: just to default to INDEX_NONE for new entries
- L66 _public member_ `struct FIndex { int32 idx=INDEX_NONE; };` — just to default to INDEX_NONE for new entries

#### struct `TStableInstanceMap`  
`template<typename T> struct TStableInstanceMap`  
_L74-132_
- L76 _public function_ `T& FindOrAdd(const FNetworkPredictionID& ID)`
- L81 _public function_ `T* Find(const FNetworkPredictionID& ID)`
- L92 _public function_ `void Remove(const FNetworkPredictionID& ID)`
- L102 _public function_ `int32 GetIndexChecked(const FNetworkPredictionID& ID)`
- L107 _public function_ `int32 GetIndex(const FNetworkPredictionID& ID)`
- L119 _public function_ `T& GetByIndexChecked(int32 idx)`
- L128 _private member_ `TSortedMap<int32, FIndex> Lookup;` — Sorted map of priority (spawnID -> stable index into SparseArray)
- L129 _private member_ `int32 LastFreeIndex = 0;`
- L131 _private member_ `TSparseArray<TUniqueObj<T>> Data;`

#### struct `TStableInstanceMap::FIndex`  
`struct FIndex`  
_L127-127_
- desc: just to default to INDEX_NONE for new entries
- L127 _public member_ `struct FIndex { int32 idx=INDEX_NONE; };` — just to default to INDEX_NONE for new entries

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionServiceRegistry.h` (Public)


#### class `FNetworkPredictionServiceRegistry`  
`class FNetworkPredictionServiceRegistry`  
_L71-267_
- L81 _public function_ `template<typename ModelDef> void RegisterInstance(FNetworkPredictionID ID, TInstanceData<ModelDef>& InstanceData, ENetworkPredictionService ServiceMask)` — Registers instance with given services. Will unregister instance with any previously-subscribed services.
- L111 _public function_ `template<typename ModelDef> void UnregisterInstance(FNetworkPredictionID ID)`
- L126 _public function_ `template<typename ModelDef=FNetworkPredictionModelDef> TModelDataStore<ModelDef>* GetDataStore()`
- L165 _public prototype_ `NP_DECLARE_SERVICE(ServerRPC, IServerRPCService);` — Declares generic storage for the service type: TServiceStorage<InterfaceType>
- L167 _public prototype_ `NP_DECLARE_SERVICE(FixedRollback, IFixedRollbackService);`
- L168 _public prototype_ `NP_DECLARE_SERVICE(FixedInterpolate, IFixedInterpolateService);`
- L169 _public prototype_ `NP_DECLARE_SERVICE(FixedInputLocal, IInputService);`
- L170 _public prototype_ `NP_DECLARE_SERVICE(FixedInputRemote, IInputService);`
- L171 _public prototype_ `NP_DECLARE_SERVICE(FixedTick, ILocalTickService);`
- L172 _public prototype_ `NP_DECLARE_SERVICE(FixedFinalize, IFinalizeService);`
- L173 _public prototype_ `NP_DECLARE_SERVICE(FixedSmoothing, IFixedSmoothingService);`
- L175 _public prototype_ `NP_DECLARE_SERVICE(IndependentRollback, IIndependentRollbackService);`
- L176 _public prototype_ `NP_DECLARE_SERVICE(IndependentInterpolate, IIndependentInterpolateService);`
- L177 _public prototype_ `NP_DECLARE_SERVICE(IndependentLocalInput, IInputService);`
- L178 _public prototype_ `NP_DECLARE_SERVICE(IndependentLocalTick, ILocalTickService);`
- L179 _public prototype_ `NP_DECLARE_SERVICE(IndependentRemoteTick, IRemoteIndependentTickService);`
- L180 _public prototype_ `NP_DECLARE_SERVICE(IndependentLocalFinalize, IFinalizeService);`
- L181 _public prototype_ `NP_DECLARE_SERVICE(IndependentRemoteFinalize, IRemoteFinalizeService);`
- L186 _private function_ `template<typename ModelDef=FNetworkPredictionModelDef, typename FuncRefType> void ForEachService(ENetworkPredictionService Mask, const FuncRefType& Func)`
- L214 _private function_ `template<ENetworkPredictionService ServiceMask, typename ServiceType, typename FuncRefType, typename ServiceStorageType> void ConditionalCallFuncOnService(ServiceStorageType& ServiceStorage, const FuncRefType& Func, ENetworkPredictionService Mask)`
- L238 _private function_ `template<typename ServiceType, typename ArrayType> ServiceType* GetService_Internal(ArrayType& Array)`
- L253 _private function_ `template<typename ModelDef> void UnregisterInstance_Internal(FNetworkPredictionID ID, ENetworkPredictionService ServiceMask)`
- L266 _private member_ `TArray<TUniquePtr<IDataStore>> DataStoreArray;`

#### struct `FNetworkPredictionServiceRegistry::GetDataStore::FThisDataStore`  
`struct FThisDataStore : IDataStore`  
_L130-133_
- inherits: `IDataStore`
- L132 _public member_ `TModelDataStore<ModelDef> Self;`

#### struct `FNetworkPredictionServiceRegistry::TServiceStorage`  
`template<typename InServiceInterface, int32 NumInlineServices=5> struct TServiceStorage`  
_L154-158_
- L156 _public typedef_ `using ServiceInterface = InServiceInterface;`
- L157 _public member_ `TSparseArray<TUniquePtr<ServiceInterface>, TInlineSparseArrayAllocator<NumInlineServices>> Array;`

#### struct `FNetworkPredictionServiceRegistry::IDataStore`  
`struct IDataStore`  
_L261-264_
- L263 _public prototype_ `virtual ~IDataStore() = default;`

#### Free symbols / members of external scopes

- L94 _function_ `` (scope `FNetworkPredictionServiceRegistry::RegisterInstance`)
- L161 _macro_ `#define NP_DECLARE_SERVICE(EnumName, ServiceInterface) TServiceStorage<ServiceInterface> EnumName` — Macros are mainly to enforce consistent naming and cohesion with ENetworkPredictionService
- L162 _macro_ `#define NP_DEFINE_SERVICE_CALL(EnumName, ServiceType) ConditionalCallFuncOnService<ENetworkPredictionService::EnumName, ServiceType<ModelDef>>(EnumName, Func, Mask)`
- L216 _typedef_ `using ModelDef = typename ServiceType::ModelDef;` (scope `FNetworkPredictionServiceRegistry::ConditionalCallFuncOnService`)
- L240 _typedef_ `using ModelDef = typename ServiceType::ModelDef;` (scope `FNetworkPredictionServiceRegistry::GetService_Internal`)
- L256 _function_ `` (scope `FNetworkPredictionServiceRegistry::UnregisterInstance_Internal`)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionService_Finalize.inl` (Public)


#### class `IFinalizeService`  
`class IFinalizeService`  
_L9-15_
- L13 _public prototype_ `virtual ~IFinalizeService() = default;`
- L14 _public prototype_ `virtual void FinalizeFrame(float DeltaTimeSeconds, const int32 SimFrame, const int32 SimTimeMS, const int32 FixedStepMS) = 0;`

#### class `TFinalizeService`  
`template<typename InModelDef> class TFinalizeService : public IFinalizeService`  
_L18-68_
- inherits: `IFinalizeService`
- L22 _public typedef_ `using ModelDef = InModelDef;`
- L23 _public typedef_ `using DriverType = typename ModelDef::Driver;`
- L24 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L25 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L26 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L27 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L29 _public function_ `TFinalizeService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L32 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L38 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L44 _public function_ `void FinalizeFrame(float DeltaTimeSeconds, const int32 ServerSimFrame, const int32 SimTimeMS, const int32 FixedStepMS) final override`
- L66 _private member_ `TBitArray<> FinalizeBitArray;` — index into DataStore->Instances
- L67 _private member_ `TModelDataStore<ModelDef>* DataStore;`

#### class `IRemoteFinalizeService`  
`class IRemoteFinalizeService`  
_L72-78_
- L76 _public prototype_ `virtual ~IRemoteFinalizeService() = default;`
- L77 _public prototype_ `virtual void FinalizeFrame(float DeltaTimeSeconds) = 0;`

#### class `TRemoteFinalizeService`  
`template<typename InModelDef> class TRemoteFinalizeService : public IRemoteFinalizeService`  
_L81-132_
- inherits: `IRemoteFinalizeService`
- L85 _public typedef_ `using ModelDef = InModelDef;`
- L86 _public typedef_ `using DriverType = typename ModelDef::Driver;`
- L87 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L88 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L89 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L90 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L92 _public function_ `TRemoteFinalizeService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L95 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L101 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L107 _public function_ `void FinalizeFrame(float DeltaTimeSeconds) final override`
- L130 _private member_ `TBitArray<> FinalizeBitArray;` — index into DataStore->ServerRecv_IndependentTick
- L131 _private member_ `TModelDataStore<ModelDef>* DataStore;`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionService_Input.inl` (Public)


#### class `IInputService`  
`class IInputService`  
_L10-16_
- L14 _public prototype_ `virtual ~IInputService() = default;`
- L15 _public prototype_ `virtual void ProduceInput(int32 DeltaTimeMS) = 0;`

#### class `TLocalInputService`  
`template<typename InModelDef> class TLocalInputService : public IInputService`  
_L21-77_
- inherits: `IInputService`
- desc: Calls ProduceInput on driver to get local input Requires valid FNetworkPredictionDriver::ProduceInput function
- L25 _public typedef_ `using ModelDef = InModelDef;`
- L26 _public typedef_ `using DriverType = typename ModelDef::Driver;`
- L27 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L28 _public typedef_ `using InputType= typename StateTypes::InputType;`
- L31 _public function_ `TLocalInputService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L34 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L44 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L49 _public function_ `void ProduceInput(int32 DeltaTimeMS) final override`
- L75 _private member_ `TSortedMap<int32, FInstance, TInlineAllocator<1>> InstanceMap;`
- L76 _private member_ `TModelDataStore<ModelDef>* DataStore;`

#### struct `TLocalInputService::FInstance`  
`struct FInstance`  
_L68-73_
- L70 _public member_ `int32 TraceID;`
- L71 _public member_ `FNetworkPredictionStateView* View;`
- L72 _public member_ `DriverType* Driver;`

#### class `TRemoteInputService`  
`template<typename InModelDef> class TRemoteInputService : public IInputService`  
_L81-191_
- inherits: `IInputService`
- desc: Pulls input from ServerRecvData. E.g: server side input buffering
- L85 _public typedef_ `using ModelDef = InModelDef;`
- L86 _public typedef_ `using DriverType = typename ModelDef::Driver;`
- L87 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L88 _public typedef_ `using InputType= typename StateTypes::InputType;`
- L90 _public function_ `TRemoteInputService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L93 _public function_ `static void SetMaxFaultLimit(int32 InMaxFaultLimit)`
- L98 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L107 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L112 _public function_ `void ProduceInput(int32 DeltaTimeMS) final override`
- L187 _private member_ `TSortedMap<int32, FInstance> InstanceMap;`
- L188 _private member_ `TModelDataStore<ModelDef>* DataStore;`
- L190 _private member_ `inline static int32 MaxFaultLimit = 6;`

#### struct `TRemoteInputService::FInstance`  
`struct FInstance`  
_L177-185_
- L179 _public member_ `int32 TraceID;`
- L180 _public member_ `FNetworkPredictionStateView* View;`
- L182 _public member_ `int32 ServerRecvIdx;` — idx into DataStore->ServerRecv::GetByIndexChecked
- L183 _public member_ `int32 FaultLimit = 2;` — InputBuffer must have >= this number of unprocessed commands before resuming consumption
- L184 _public member_ `bool bFault=true;` — Recently starved on input buffer, wait until we reach FaultLimit before consuming input again. (Note you start out in fault to let the buffer fill up)

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionService_Interpolate.inl` (Public)


#### class `IFixedInterpolateService`  
`class IFixedInterpolateService`  
_L52-59_
- L56 _public prototype_ `virtual ~IFixedInterpolateService() = default;`
- L57 _public prototype_ `virtual void Reconcile(const FFixedTickState* TickState) = 0;`
- L58 _public prototype_ `virtual void FinalizeFrame(float DeltaTimeSeconds, const FFixedTickState* TickState) = 0;`

#### class `TFixedInterpolateService`  
`template<typename InModelDef> class TFixedInterpolateService : public IFixedInterpolateService`  
_L62-333_
- inherits: `IFixedInterpolateService`
- L66 _public typedef_ `using ModelDef = InModelDef;`
- L67 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L68 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L69 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L70 _public typedef_ `using SyncAuxType = TSyncAuxPair<StateTypes>;`
- L72 _public function_ `TFixedInterpolateService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L75 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L92 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L111 _public function_ `void Reconcile(const FFixedTickState* TickState) final override`
- L194 _public function_ `void FinalizeFrame(float DeltaTimeSeconds, const FFixedTickState* TickState) final override`
- L294 _private member_ `TSparseArray<FInstance> Instances;` — Indices are shared with DataStore->ClientRecv
- L295 _private member_ `TBitArray<> ClientRecvBitMask;` — Indices into DataStore->ClientRecv that we are managing
- L296 _private member_ `TBitArray<> PendingFixups;` — Indices into DataStore->ClientRecv index that didn't have a valid ToFrame when reconciling
- L298 _private member_ `TModelDataStore<ModelDef>* DataStore;`
- L301 _private function_ `static void CopyFrameData(int32 SourceFrame, int32 DestFrame, TInstanceFrameState<ModelDef>& Frames, FInstance& Instance)`
- L310 _private function_ `static void Interpolate(const int32 FromSourceFrame, const int32 ToSourceFrame, const int32 DestFrame, TInstanceFrameState<ModelDef>& Frames, FInstance& Instance, const int32 FixedStepMS)`

#### struct `TFixedInterpolateService::FInstance`  
`struct FInstance`  
_L278-292_
- L280 _public function_ `FInstance(int32 InTraceID, int32 InInstanceIdx, int32 InFramesIdx) : TraceID(InTraceID), InstanceIdx(InInstanceIdx), FramesIdx(InFramesIdx)`
- L283 _public member_ `int32 TraceID;`
- L284 _public member_ `int32 InstanceIdx;`
- L285 _public member_ `int32 FramesIdx;`
- L286 _public member_ `int32 LastWrittenFrame = INDEX_NONE;`
- L287 _public member_ `bool bTwoValidFrames = false;`
- L290 _public member_ `TConditionalState<SyncType> SyncState;` — Last interpolated values. Stored here so that we can maintain FNetworkPredictionStateView to them
- L291 _public member_ `TConditionalState<AuxType> AuxState;`

#### class `IIndependentInterpolateService`  
`class IIndependentInterpolateService`  
_L349-356_
- L353 _public prototype_ `virtual ~IIndependentInterpolateService() = default;`
- L354 _public prototype_ `virtual void Reconcile(const FVariableTickState* TickState) = 0;`
- L355 _public prototype_ `virtual void FinalizeFrame(float DeltaTimeSeconds, const FVariableTickState* TickState) = 0;`

#### class `TIndependentInterpolateService`  
`template<typename InModelDef> class TIndependentInterpolateService : public IIndependentInterpolateService`  
_L360-602_
- inherits: `IIndependentInterpolateService`
- L364 _public typedef_ `using ModelDef = InModelDef;`
- L365 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L366 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L367 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L368 _public typedef_ `using SyncAuxType = TSyncAuxPair<StateTypes>;`
- L370 _public function_ `TIndependentInterpolateService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L373 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L389 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L401 _public function_ `void Reconcile(const FVariableTickState* TickState) final override`
- L431 _public function_ `void FinalizeFrame(float DeltaTimeSeconds, const FVariableTickState* TickState) final override`
- L598 _private member_ `TBitArray<> ClientRecvBitMask;` — Indices into DataStore->ClientRecv that we are managing
- L599 _private member_ `TSparseArray<FInstance> Instances;` — Indices are shared with DataStore->ClientRecv
- L601 _private member_ `TModelDataStore<ModelDef>* DataStore;`

#### struct `TIndependentInterpolateService::FInstance`  
`struct FInstance`  
_L562-596_
- L564 _public function_ `FInstance(int32 InTraceID, int32 InInstanceIdx) : TraceID(InTraceID), InstanceIdx(InInstanceIdx), ClientRecvFrames(16)`
- L567 _public member_ `int32 TraceID;`
- L568 _public member_ `int32 InstanceIdx;`
- L570 _public member_ `int32 LastWrittenFrame = INDEX_NONE;`
- L571 _public member_ `int32 LastFromFrame = INDEX_NONE;`
- L574 _public member_ `TConditionalState<SyncType> SyncState;` — Last interpolated values. Stored here so that we can maintain FNetworkPredictionStateView to them
- L575 _public member_ `TConditionalState<AuxType> AuxState;`
- L595 _public member_ `TNetworkPredictionBuffer<FFrame> ClientRecvFrames;`

#### struct `TIndependentInterpolateService::FInstance::FFrame`  
`struct FFrame`  
_L588-593_
- L590 _public member_ `TConditionalState<SyncType> SyncState;`
- L591 _public member_ `TConditionalState<AuxType> AuxState;`
- L592 _public member_ `int32 SimTimeMS;`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace NetworkPredictionCVars`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionService_Rollback.inl` (Public)


#### class `IFixedRollbackService`  
`class IFixedRollbackService`  
_L20-29_
- L24 _public prototype_ `virtual ~IFixedRollbackService() = default;`
- L25 _public prototype_ `virtual int32 QueryRollback(const FFixedTickState* TickState) = 0;`
- L27 _public prototype_ `virtual void PreStepRollback(const FNetSimTimeStep& Step, const FServiceTimeStep& ServiceStep, const int32 Offset, const bool bFirstStepInResim) = 0;`
- L28 _public prototype_ `virtual void StepRollback(const FNetSimTimeStep& Step, const FServiceTimeStep& ServiceStep) = 0;`

#### class `TFixedRollbackService`  
`template<typename InModelDef> class TFixedRollbackService : public IFixedRollbackService`  
_L32-237_
- inherits: `IFixedRollbackService`
- L36 _public typedef_ `using ModelDef = InModelDef;`
- L37 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L38 _public typedef_ `using SyncAuxType = TSyncAuxPair<StateTypes>;`
- L40 _public member_ `static constexpr bool bNeedsTickService = FNetworkPredictionDriver<ModelDef>::HasSimulation();`
- L42 _public function_ `TFixedRollbackService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore), InternalTickService(InDataStore)`
- L45 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L56 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L67 _public function_ `int32 QueryRollback(const FFixedTickState* TickState) final override`
- L150 _public function_ `void PreStepRollback(const FNetSimTimeStep& Step, const FServiceTimeStep& ServiceStep, const int32 Offset, const bool bFirstStepInResim)`
- L182 _public function_ `void StepRollback(const FNetSimTimeStep& Step, const FServiceTimeStep& ServiceStep) final override`
- L193 _private function_ `template<bool FlushCorrection> void ApplyCorrection(const int32 LocalInputFrame, const int32 Offset)`
- L231 _private member_ `TBitArray<> InstanceBitArray;` — Indices into DataStore->ClientRecv that we are managing
- L232 _private member_ `TBitArray<> RollbackBitArray;` — Indices into DataStore->ClientRecv that we should rollback
- L234 _private member_ `TModelDataStore<ModelDef>* DataStore;`
- L236 _private member_ `TLocalTickService<ModelDef> InternalTickService;`

#### class `IIndependentRollbackService`  
`class IIndependentRollbackService`  
_L241-247_
- L245 _public prototype_ `virtual ~IIndependentRollbackService() = default;`
- L246 _public prototype_ `virtual void Reconcile(const FVariableTickState* TickState) = 0;`

#### class `TIndependentRollbackService`  
`template<typename InModelDef> class TIndependentRollbackService : public IIndependentRollbackService`  
_L250-343_
- inherits: `IIndependentRollbackService`
- L254 _public typedef_ `using ModelDef = InModelDef;`
- L255 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L256 _public typedef_ `using SyncAuxType = TSyncAuxPair<StateTypes>;`
- L258 _public function_ `TIndependentRollbackService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L261 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L270 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L276 _public function_ `void Reconcile(const FVariableTickState* TickState) final override`
- L341 _private member_ `TBitArray<> InstanceBitArray;` — Indices into DataStore->ClientRecv that we are managing
- L342 _private member_ `TModelDataStore<ModelDef>* DataStore;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace NetworkPredictionCVars`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionService_ServerRPC.inl` (Public)


#### class `IServerRPCService`  
`class IServerRPCService`  
_L14-20_
- L18 _public prototype_ `virtual ~IServerRPCService() = default;`
- L19 _public prototype_ `virtual void CallServerRPC(float DeltaTimeSeconds) = 0;`

#### class `TServerRPCService`  
`template<typename InModelDef> class TServerRPCService : public IServerRPCService`  
_L23-67_
- inherits: `IServerRPCService`
- L27 _public typedef_ `using ModelDef = InModelDef;`
- L28 _public typedef_ `using DriverType = typename ModelDef::Driver;`
- L30 _public function_ `TServerRPCService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L33 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L41 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L46 _public function_ `void CallServerRPC(float DeltaTimeSeconds) final override`
- L65 _private member_ `TSortedMap<int32, FInstance, TInlineAllocator<1>> Instances;`
- L66 _private member_ `TModelDataStore<ModelDef>* DataStore;`

#### struct `TServerRPCService::FInstance`  
`struct FInstance`  
_L59-63_
- desc: The vast majority of the time there will be <= 1 instances that wants to call the ServerRPC. Only split screen type situations will require more.
- L61 _public member_ `int32 TraceID;`
- L62 _public member_ `DriverType* Driver;`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionService_Smooth.inl` (Public)


#### class `IFixedSmoothingService`  
`class IFixedSmoothingService`  
_L26-33_
- L30 _public prototype_ `virtual ~IFixedSmoothingService() = default;`
- L31 _public prototype_ `virtual void UpdateSmoothing(const FServiceTimeStep& ServiceStep,const FFixedTickState* TickState) = 0;`
- L32 _public prototype_ `virtual void FinalizeSmoothingFrame(const FFixedTickState* TickState) = 0;`

#### class `TFixedSmoothingService`  
`template<typename InModelDef> class TFixedSmoothingService : public IFixedSmoothingService`  
_L36-194_
- inherits: `IFixedSmoothingService`
- L40 _public typedef_ `using ModelDef = InModelDef;`
- L41 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L42 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L43 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L44 _public typedef_ `using SyncAuxType = TSyncAuxPair<StateTypes>;`
- L47 _public function_ `TFixedSmoothingService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L50 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L78 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L86 _public function_ `virtual void UpdateSmoothing(const FServiceTimeStep& ServiceStep, const FFixedTickState* TickState) final override`
- L118 _public function_ `virtual void FinalizeSmoothingFrame(const FFixedTickState* TickState) final override`
- L161 _private function_ `void UpdateAllInstancePresentationViews()`
- L191 _private member_ `TSparseArray<FInstance> Instances;` — Indices are shared with DataStore->ClientRecv
- L193 _private member_ `TModelDataStore<ModelDef>* DataStore;`

#### struct `TFixedSmoothingService::FInstance`  
`struct FInstance`  
_L173-189_
- L175 _public function_ `FInstance(int32 InTraceID, int32 InInstanceIdx, int32 InFramesIdx) : TraceID(InTraceID), InstanceIdx(InInstanceIdx), FramesIdx(InFramesIdx)`
- L178 _public member_ `int32 TraceID;`
- L179 _public member_ `int32 InstanceIdx;`
- L180 _public member_ `int32 FramesIdx;`
- L181 _public member_ `uint8 bHasTwoFrames : 1 = false;`
- L184 _public member_ `TConditionalState<SyncType> SyncState;` — Latest states to smooth between. Stored here so that we can maintain FNetworkPredictionStateView to them
- L185 _public member_ `TConditionalState<AuxType> AuxState;`
- L186 _public member_ `TConditionalState<SyncType> LastSyncState;`
- L187 _public member_ `TConditionalState<AuxType> LastAuxState;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace NetworkPredictionCVars`

### `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/Services/NetworkPredictionService_Ticking.inl` (Public)


#### struct `TTickUtil`  
`template<typename ModelDef> struct TTickUtil`  
_L14-55_
- desc: Common util used by the ticking services. Might make sense to move to FNetworkPredictionDriverBase if needed elsewhere
- L16 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L17 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L18 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L19 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L21 _public typedef_ `using FrameDataType = typename TInstanceFrameState<ModelDef>::FFrame;`
- L24 _public function_ `template<typename SimulationType = typename ModelDef::Simulation> static typename TEnableIf<!std::is_same_v<SimulationType, void>>::Type DoTick(TInstanceData<ModelDef>& Instance, FrameDataType& InputFrameData, FrameDataType& OutputFrameData, const FNetSimTimeStep& Step, const int32 CueTimeMS, ESimulationTickContext TickContext)`
- L51 _public function_ `template<typename SimulationType = typename ModelDef::Simulation> static typename TEnableIf<std::is_same_v<SimulationType, void>>::Type DoTick(TInstanceData<ModelDef>& Instance, FrameDataType& InputFrameData, FrameDataType& OutputFrameData, const FNetSimTimeStep& Step, const int32 EndTimeMS, ESimulationTickContext TickContext)`

#### class `ILocalTickService`  
`class ILocalTickService`  
_L58-64_
- desc: The tick service's role is to tick new simulation frames based on local frame state (fixed or independent/variable)
- L62 _public prototype_ `virtual ~ILocalTickService() = default;`
- L63 _public prototype_ `virtual void Tick(const FNetSimTimeStep& Step, const FServiceTimeStep& ServiceStep) = 0;`

#### class `TLocalTickServiceBase`  
`template<typename InModelDef> class TLocalTickServiceBase : public ILocalTickService`  
_L67-187_
- inherits: `ILocalTickService`
- L71 _public typedef_ `using ModelDef = InModelDef;`
- L72 _public typedef_ `using StateTypes = typename ModelDef::StateTypes;`
- L73 _public typedef_ `using InputType = typename StateTypes::InputType;`
- L74 _public typedef_ `using SyncType = typename StateTypes::SyncType;`
- L75 _public typedef_ `using AuxType = typename StateTypes::AuxType;`
- L77 _public function_ `TLocalTickServiceBase(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L80 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L85 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L90 _public function_ `void Tick(const FNetSimTimeStep& Step, const FServiceTimeStep& ServiceStep) override`
- L95 _public function_ `void TickResim(const FNetSimTimeStep& Step, const FServiceTimeStep& ServiceStep)`
- L100 _public function_ `void BeginRollback(const int32 LocalFrame, const int32 StartTimeMS, const int32 ServerFrame)`
- L113 _protected function_ `template<bool bIsResim> void Tick_Internal(const FNetSimTimeStep& Step, const FServiceTimeStep& ServiceStep)`
- L143 _protected function_ `template<bool bIsResim> ESimulationTickContext GetTickContext(ENetRole NetRole)`
- L184 _protected member_ `TSortedMap<int32, FInstance> InstancesToTick;`
- L185 _protected member_ `TModelDataStore<ModelDef>* DataStore;`

#### struct `TLocalTickServiceBase::FInstance`  
`struct FInstance`  
_L177-182_
- L179 _public member_ `int32 TraceID;`
- L180 _public member_ `int32 InstanceIdx;` — idx into TModelDataStore::Instances
- L181 _public member_ `int32 FrameBufferIdx;` — idx into TModelDataStore::Frames

#### class `TLocalTickService`  
`template<typename InModelDef> class TLocalTickService : public TLocalTickServiceBase<InModelDef>`  
_L191-199_
- inherits: `TLocalTickServiceBase<InModelDef>`
- desc: To allow template specialization
- L194 _public function_ `TLocalTickService(TModelDataStore<InModelDef>* InDataStore) : TLocalTickServiceBase<InModelDef>(InDataStore)`

#### class `IRemoteIndependentTickService`  
``  
_L206-212_
- desc: Service for ticking independent simulations that are remotely controlled.
- L210 _public prototype_ `virtual ~IRemoteIndependentTickService() = default;`
- L211 _public prototype_ `virtual void Tick(float DeltaTimeSeconds, const FVariableTickState* VariableTickState) = 0;`

#### class `TRemoteIndependentTickService`  
`template<typename InModelDef> class TRemoteIndependentTickService : public IRemoteIndependentTickService`  
_L216-328_
- inherits: `IRemoteIndependentTickService`
- desc: Ticking remote clients on the server.
- L219 _public typedef_ `using ModelDef = InModelDef;`
- L222 _public member_ `static constexpr int32 MinRemoteClientStepMS = 1;` — These are rough ballparks, maybe should be configurable
- L223 _public member_ `static constexpr int32 MaxRemoteClientStepMS = 100;`
- L225 _public member_ `static constexpr int32 MaxRemoteClientStepsPerFrame = 6;`
- L226 _public member_ `static constexpr int32 MaxRemoteClientTotalMSPerFrame = 200;`
- L228 _public function_ `TRemoteIndependentTickService(TModelDataStore<ModelDef>* InDataStore) : DataStore(InDataStore)`
- L231 _public function_ `void RegisterInstance(FNetworkPredictionID ID)`
- L237 _public function_ `void UnregisterInstance(FNetworkPredictionID ID)`
- L243 _public function_ `void Tick(float DeltaTimeSeconds, const FVariableTickState* VariableTickState) final override`
- L326 _private member_ `TBitArray<> InstanceBitArray;` — Indices into DataStore->ServerRecv_IndependentTick that we are managing
- L327 _private member_ `TModelDataStore<ModelDef>* DataStore;`
