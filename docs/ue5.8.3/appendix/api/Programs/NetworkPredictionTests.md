# Programs / NetworkPredictionTests

- module root: `Source/Programs/NetworkPredictionTests`
- headers: 5; symbols: 82
- symbol kinds: class=1, delegate=1, enum=1, enumerator=4, function=5, member=23, namespace=9, prototype=31, struct=6, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, NetworkPrediction

### `Source/Programs/NetworkPredictionTests/Private/NetPredictionMockPackageMap.h` (Private)


#### class `UNetPredictionMockPackageMap`  
`class UNetPredictionMockPackageMap : public UPackageMap`  
_L10-25_
- reflection: `UCLASS(transient)`
- inherits: `UPackageMap`
- desc: Placeholder package map that ensures if any of its functionality is actually used.
- L15 _public prototype_ `virtual bool WriteObject(FArchive & Ar, UObject* InOuter, FNetworkGUID NetGUID, FString ObjName) override;`
- L16 _public prototype_ `virtual bool SerializeObject(FArchive& Ar, UClass* InClass, UObject*& Obj, FNetworkGUID *OutNetGUID = NULL) override;`
- L17 _public prototype_ `virtual bool SerializeName(FArchive& Ar, FName& InName) override;`
- L18 _public prototype_ `virtual UObject* ResolvePathAndAssignNetGUID(const FNetworkGUID& NetGUID, const FString& PathName) override;`
- L19 _public prototype_ `virtual bool SerializeNewActor(FArchive & Ar, class UActorChannel * Channel, class AActor *& Actor) override;`
- L20 _public prototype_ `virtual UObject* GetObjectFromNetGUID(const FNetworkGUID& NetGUID, const bool bIgnoreMustBeMapped) override;`
- L21 _public prototype_ `virtual FNetworkGUID GetNetGUIDFromObject(const UObject* InObject) const override;`
- L22 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L24 _public prototype_ `static UNetPredictionMockPackageMap* Get();`

### `Source/Programs/NetworkPredictionTests/Private/NetPredictionTestChannel.h` (Private)


#### struct `UE::Net::Private::FNetPredictionTestChannel`  
`struct FNetPredictionTestChannel`  
_L11-19_
- L13 _public prototype_ `void Send(const FNetBitWriter& Writer);`
- L14 _public prototype_ `bool HasPendingData();`
- L15 _public prototype_ `FNetBitReader Receive();`
- L18 _private member_ `TResizableCircularQueue<FNetBitWriter> DataBuffer;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Net` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Net`)

### `Source/Programs/NetworkPredictionTests/Private/NetPredictionTestDriver.h` (Private)


#### struct `UE::Net::Private::FNetPredictionTestInputCmd`  
`struct FNetPredictionTestInputCmd`  
_L20-33_
- L22 _public member_ `bool bIncrement = false;`
- L24 _public function_ `void ToString(FAnsiStringBuilderBase& Builder) const`
- L29 _public function_ `void NetSerialize(const FNetSerializeParams& P)`

#### struct `UE::Net::Private::FNetPredictionTestSyncState`  
`struct FNetPredictionTestSyncState`  
_L35-56_
- L38 _public member_ `float AutoCounter = 0.0f;` — Value is incremented by one every frame, not dependent on input
- L41 _public member_ `float InputCounter = 0.0f;` — Value is incremented by one if the input bIncrement value is true, no change if it's false.
- L43 _public function_ `void ToString(FAnsiStringBuilderBase& Builder) const`
- L48 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L54 _public prototype_ `void Interpolate(const FNetPredictionTestSyncState* From, const FNetPredictionTestSyncState* To, float Percent);`
- L55 _public prototype_ `bool ShouldReconcile(const FNetPredictionTestSyncState& AuthorityState) const;`

#### struct `UE::Net::Private::FNetPredictionTestDriver`  
`struct FNetPredictionTestDriver`  
_L61-106_
- desc: Mimics the key parts of UNetworkPredictionComponent without being an actual UActorComponent.
- L63 _public member_ `FNetworkPredictionProxy Proxy;`
- L64 _public member_ `FReplicationProxy ReplicationProxy_ServerRPC;`
- L65 _public member_ `FReplicationProxy ReplicationProxy_Autonomous;`
- L66 _public member_ `FReplicationProxy ReplicationProxy_Simulated;`
- L68 _public member_ `FString DebugName;`
- L70 _public member_ `bool bHidden = false;`
- L71 _public member_ `bool bInputPressed = false;`
- L82 _public member_ `static const uint8 ChangeFlagsBitsNeeded;`
- L84 _public prototype_ `FNetPredictionTestDriver(UNetworkPredictionWorldManager* WorldManager, ENetMode Mode, TSharedPtr<FNetPredictionTestChannel> InClientToServer, TSharedPtr<FNetPredictionTestChannel> InServerToClient);`
- L88 _public prototype_ `void ProduceInput(const int32 DeltaTimeMS, FNetPredictionTestInputCmd* Cmd);`
- L89 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<FNetPredictionTestStateTypes>& SimInput, const TNetSimOutput<FNetPredictionTestStateTypes>& SimOutput);`
- L90 _public prototype_ `void InitializeSimulationState(FNetPredictionTestSyncState* OutSync, void* OutAux);`
- L91 _public prototype_ `void FinalizeFrame(const FNetPredictionTestSyncState* SyncState, const void* AuxState);`
- L92 _public prototype_ `void SetHiddenForInterpolation(bool bInHidden);`
- L93 _public prototype_ `void CallServerRPC();`
- L94 _public prototype_ `void ReceiveServerRPCs();`
- L96 _public prototype_ `void NetSerialize(FArchive& Ar, EChangeFlags Flags);`
- L99 _private function_ `FReplicationProxySet GetReplicationProxies()`
- L104 _private member_ `TSharedPtr<FNetPredictionTestChannel> ClientToServer;`
- L105 _private member_ `TSharedPtr<FNetPredictionTestChannel> ServerToClient;`

#### enum `UE::Net::Private::FNetPredictionTestDriver::EChangeFlags`  
`enum class EChangeFlags : uint8`  
_L73-81_
- L75 _public enumerator_ `None = 0`
- L76 _public enumerator_ `PredictionProxyChanged = 1 << 0`
- L77 _public enumerator_ `ReplicationProxyChanged = 1 << 1`
- L80 _public enumerator_ `MaxFlagPlusOne` — Add new entries above

#### struct `UE::Net::Private::FNetPredictionTestObject`  
`struct FNetPredictionTestObject`  
_L111-133_
- desc: Conveniently associates the server & client object drivers and their channels for ease of writing unit tests.
- L113 _public member_ `TSharedPtr<FNetPredictionTestChannel> ClientToServer;`
- L114 _public member_ `TSharedPtr<FNetPredictionTestChannel> ServerToClient;`
- L116 _public member_ `FNetPredictionTestDriver ServerObject;`
- L117 _public member_ `FNetPredictionTestDriver ClientObject;`
- L119 _public prototype_ `FNetPredictionTestObject( UNetworkPredictionWorldManager* ServerWorldManager, UNetworkPredictionWorldManager* ClientWorldManager, ENetRole ClientRole);`
- L124 _public prototype_ `void ServerSend();`
- L125 _public prototype_ `void ClientReceive();`
- L130 _private member_ `FNetworkPredictionProxy ProxyShadowState;` — Stores previously sent state, compared with current state to prevent "sending" when it hasn't changed. For emulating FRepLayout behavior.
- L131 _private member_ `FReplicationProxy AutonomousProxyShadowState;`
- L132 _private member_ `FReplicationProxy SimulatedProxyShadowState;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Net` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Net`)
- L58 _typedef_ `using FNetPredictionTestStateTypes = TNetworkPredictionStateTypes<FNetPredictionTestInputCmd, FNetPredictionTestSyncState, void>;` (scope `UE::Net::Private`)
- L108 _prototype_ `ENUM_CLASS_FLAGS(FNetPredictionTestDriver::EChangeFlags);` (scope `UE::Net::Private`)

### `Source/Programs/NetworkPredictionTests/Private/NetPredictionTestWorld.h` (Private)


#### struct `UE::Net::Private::FNetPredictionTestWorld`  
`struct FNetPredictionTestWorld`  
_L13-25_
- L16 _public prototype_ `FNetPredictionTestWorld(UNetworkPredictionSettingsObject* Settings, ENetMode InNetMode);`
- L18 _public prototype_ `void PreTick(int32 FixedFrameRate);`
- L19 _public prototype_ `void Tick(int32 FixedFrameRate);`
- L21 _public member_ `UNetworkPredictionWorldManager* WorldManager = nullptr;`
- L24 _private member_ `ENetMode NetMode;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Net` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Net`)

### `Source/Programs/NetworkPredictionTests/Private/NetworkPredictionTests.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkPredictionTests, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkPredictionTests, Log, All);`
