# Plugins / ConcertSyncTest

- module root: `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest`
- headers: 26; symbols: 593
- symbol kinds: class=24, delegate=1, enum=10, enumerator=48, function=212, member=132, namespace=87, prototype=66, struct=9, typedef=4
- PrivateDependencyModuleNames: Concert, ConcertClientSharedSlate, ConcertSharedSlate, ConcertSyncClient, ConcertSyncCore, ConcertSyncServer, ConcertTransport, Engine
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/ConcertDataStoreTests.h` (Private)


#### struct `FConcertDataStore_CustomTypeTest`  
`struct FConcertDataStore_CustomTypeTest`  
_L9-34_
- reflection: `USTRUCT()`
- desc: A custom type for ConcertDatastore testing purpose.
- L14 _public member_ `int8 Int8Value = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`
- L17 _public member_ `int64 Int64Value = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`
- L20 _public member_ `float FloatValue = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`
- L23 _public member_ `TArray<int> IntArray;` — `UPROPERTY(VisibleAnywhere, Category = "Concert Message")`
- L25 _public function_ `bool operator==(const FConcertDataStore_CustomTypeTest& other) const`
- L30 _public function_ `bool operator!=(const FConcertDataStore_CustomTypeTest& other) const`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/HistoryEdition/HistoryTestUtil.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L11 _function_ `inline TArray<ConcertSyncCore::FActivityNodeID> ValidateEachActivityHasNode( FAutomationTestBase& Test, const TArray<int64>& ActivityMappings, const ConcertSyncCore::FActivityDependencyGraph& Graph, uint32 ActivityCount, TFunctionRef<FString(uint32 ActivityType)> LexToString)` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/HistoryEdition/RenameEditAndDeleteMapsFlow.h` (Private)


#### enum `UE::ConcertSyncTests::RenameEditAndDeleteMapsFlowTest::ETestActivity`  
`enum ETestActivity`  
_L11-26_
- L13 _public enumerator_ `_1_NewPackageFoo`
- L14 _public enumerator_ `_2_SavePackageFoo`
- L15 _public enumerator_ `_3_AddActor`
- L16 _public enumerator_ `_4_RenameActor`
- L17 _public enumerator_ `_5_EditActor`
- L18 _public enumerator_ `_6_SavePackageBar`
- L19 _public enumerator_ `_7_RenameFooToBar`
- L20 _public enumerator_ `_8_EditActor`
- L21 _public enumerator_ `_9_DeleteBar`
- L22 _public enumerator_ `_10_NewPackageFoo`
- L23 _public enumerator_ `_11_SavePackageFoo`
- L25 _public enumerator_ `ActivityCount`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L9 _namespace_ `namespace RenameEditAndDeleteMapsFlowTest` (scope `UE::ConcertSyncTests`)
- L27 _prototype_ `TSet<ETestActivity> AllActivities();` (scope `UE::ConcertSyncTests::RenameEditAndDeleteMapsFlowTest`)
- L28 _prototype_ `FString LexToString(ETestActivity Activity);` (scope `UE::ConcertSyncTests::RenameEditAndDeleteMapsFlowTest`)
- L32 _typedef_ `template<typename T> using TTestActivityArray = TArray<T, TInlineAllocator<ActivityCount>>;` (scope `UE::ConcertSyncTests::RenameEditAndDeleteMapsFlowTest`) — An array where every entry of ETestActivity is a valid index.
- L47 _prototype_ `TTestActivityArray<FActivityID> CreateActivityHistory(FConcertSyncSessionDatabase& SessionDatabase, const FGuid& EndpointID);` (scope `UE::ConcertSyncTests::RenameEditAndDeleteMapsFlowTest`) — Creates a session history which resembles the following sequence of user actions: 1 Create map Foo 2 Add actor A 3 Edit actor A 4 Edit actor A 5 Rename map to Bar 6 Edit actor A 7 Delete map Bar 8 Create map Bar @return An array where every ETestActivity entry is the index to the activity ID added to SessionDatabase

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/ReplicationTestInterface.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L19 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L25 _namespace_ `namespace TestInterface` (scope `UE::ConcertSyncClient`)
- L27 _prototype_ `extern TSharedRef<IConcertClientReplicationManager> CreateClientReplicationManager( TSharedRef<IConcertClientSession> InLiveSession, IConcertClientReplicationBridge& InBridge UE_LIFETIMEBOUND, EConcertSyncSessionFlags SessionFlags = EConcertSyncSessionFlags::Default_MultiUserSession );` (scope `UE::ConcertSyncClient::TestInterface`)
- L33 _prototype_ `extern TSharedRef<IConcertClientReplicationBridge> CreateClientReplicationBridge();` (scope `UE::ConcertSyncClient::TestInterface`)
- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L36 _namespace_ `namespace TestInterface` (scope `UE::ConcertSyncServer`)
- L38 _prototype_ `extern TSharedRef<Replication::IConcertServerReplicationManager> CreateServerReplicationManager( TSharedRef<IConcertServerSession> InLiveSession, Replication::IReplicationWorkspace& InWorkspace UE_LIFETIMEBOUND, EConcertSyncSessionFlags InSessionFlags = EConcertSyncSessionFlags::Default_MultiUserSession );` (scope `UE::ConcertSyncServer::TestInterface`)
- L44 _prototype_ `extern TSharedRef<Replication::IReplicationWorkspace> CreateReplicationWorkspace( FConcertSyncSessionDatabase& Database, TFunction<TOptional<FConcertSessionClientInfo>(const FGuid& EndpointId)> FindSessionClient, TFunction<bool(const FGuid& ClientId)> ShouldIgnoreClientActivityOnRestore );` (scope `UE::ConcertSyncServer::TestInterface`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/TestReflectionObject.h` (Private)


#### struct `FNativeStruct`  
`struct FNativeStruct`  
_L10-22_
- reflection: `USTRUCT()`
- L15 _public member_ `float Float{};` — `UPROPERTY()`
- L17 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNativeStruct> : public TStructOpsTypeTraitsBase2<FNativeStruct>`  
_L27-33_
- inherits: `TStructOpsTypeTraitsBase2<FNativeStruct>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L30-32_

#### struct `FTestReplicationStruct`  
`struct FTestReplicationStruct`  
_L36-67_
- reflection: `USTRUCT()`
- L41 _public member_ `float Value{};` — `UPROPERTY()` — The name of this property is purposefully equal to FConcertPropertyChain::InternalContainerPropertyValueName.
- L43 _public member_ `FVector Vector = FVector::ZeroVector;` — `UPROPERTY()`
- L45 _public member_ `FNativeStruct NativeStruct;` — `UPROPERTY()`
- L48 _public member_ `TArray<float> FloatArray;` — `UPROPERTY()`
- L50 _public member_ `TArray<FString> StringArray;` — `UPROPERTY()`
- L52 _public member_ `TArray<FNativeStruct> NativeStructArray;` — `UPROPERTY()`
- L55 _public member_ `TSet<float> FloatSet;` — `UPROPERTY()`
- L57 _public member_ `TSet<FString> StringSet;` — `UPROPERTY()`
- L59 _public member_ `TSet<FNativeStruct> NativeStructSet;` — `UPROPERTY()`
- L62 _public member_ `TMap<FString, float> StringToFloat;` — `UPROPERTY()`
- L64 _public member_ `TMap<FString, FVector> StringToVector;` — `UPROPERTY()`
- L66 _public member_ `TMap<FString, FNativeStruct> StringToNativeStruct;` — `UPROPERTY()`

#### struct `FTestNestedReplicationStruct`  
`struct FTestNestedReplicationStruct`  
_L70-79_
- reflection: `USTRUCT()`
- L75 _public member_ `FTestReplicationStruct Nested;` — `UPROPERTY()`
- L78 _public member_ `TArray<FTestReplicationStruct> NestedArray;` — `UPROPERTY()`

#### class `UTestReflectionObject`  
`class UTestReflectionObject : public UObject`  
_L84-111_
- reflection: `UCLASS()`
- inherits: `UObject`
- L90 _public member_ `float Float{};` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L93 _public member_ `FVector Vector = FVector::ZeroVector;` — `UPROPERTY()`
- L96 _public member_ `FTestNestedReplicationStruct TestStruct;` — `UPROPERTY()`
- L101 _public member_ `FTestReflectionDelegate DelegateTest;` — `UPROPERTY(BlueprintAssignable, Category = "Dummy")`
- L104 _public member_ `TObjectPtr<UObject> InstancedSubobject;` — `UPROPERTY(Instanced)`
- L106 _public member_ `TArray<TObjectPtr<UObject>> InstancedSubobjectArray;` — `UPROPERTY(Instanced)`
- L108 _public member_ `TSet<TObjectPtr<UObject>> InstancedSubobjectSet;` — `UPROPERTY(Instanced)`
- L110 _public member_ `TMap<FName, TObjectPtr<UObject>> InstancedSubobjectMap;` — `UPROPERTY(Instanced)`

#### Free symbols / members of external scopes

- L24 _function_ `inline uint32 GetTypeHash(const FNativeStruct& Struct)`
- L31 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon480fedb20103`)
- L81 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestReflectionDelegate);`
- L81 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestReflectionDelegate);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/ChangeStreamsTestBase.h` (Private)


#### enum `UE::ConcertSyncTests::Replication::EChangeStreamValidation`  
`enum class EChangeStreamValidation : uint8`  
_L16-30_
- L19 _public enumerator_ `None = 0` — Do special flags
- L22 _public enumerator_ `TestWasHandled = 1 << 0` — Test that the ErrorCode is EReplicationResponseErrorCode::Handled.
- L24 _public enumerator_ `TestWasTimeout = 1 << 1` — Test that the ErrorCode is EReplicationResponseErrorCode::Timeout.
- L27 _public enumerator_ `TestResponseSuccess = 1 << 2` — Test that the stream change request succeeded
- L29 _public enumerator_ `TestResponseFailed = 1 << 3` — Test that the stream change request  failed

#### class `UE::ConcertSyncTests::Replication::FChangeStreamsTestBase`  
`class FChangeStreamsTestBase : public FSendReceiveGenericTestBase`  
_L39-79_
- inherits: `FSendReceiveGenericTestBase`
- desc: Base test for testing ChangeStream requests. While there is no sending nor receiving of replicated data, subclasses will still refer to the clients as "Sender" and "Receiver".
- L43 _public prototype_ `FChangeStreamsTestBase(const FString& InName, const bool bInComplexTask);`
- L47 _protected member_ `ConcertSyncClient::Replication::FJoinReplicatedSessionArgs SenderArgs;`
- L48 _protected member_ `ConcertSyncClient::Replication::FJoinReplicatedSessionArgs ReceiverArgs;`
- L51 _protected function_ `virtual ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateSenderArgs() override`
- L52 _protected function_ `virtual ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateReceiverArgs() override`
- L55 _protected prototype_ `static void AddFloatProperties(const UTestReflectionObject& TestObject, FConcertReplicationStream& Stream);`
- L57 _protected prototype_ `static TTuple<FGuid, FConcertReplicationStream> CreateFloatPropertyStream( const UTestReflectionObject& TestObject, FConcertObjectReplicationSettings DefaultFrequencySettings = { EConcertObjectReplicationMode::Realtime } );`
- L61 _protected prototype_ `static TTuple<FGuid, FConcertReplicationStream> CreateVectorPropertyStream( const UTestReflectionObject& TestObject, FConcertObjectReplicationSettings DefaultFrequencySettings = { EConcertObjectReplicationMode::Realtime } );`
- L66 _protected prototype_ `static FConcertPropertySelection& GetPropertySelection(FConcertReplicationStream& Stream, const UTestReflectionObject& TestObject);`
- L68 _protected prototype_ `static void AddFloatProperty(FConcertPropertySelection& PropertySelection);`
- L69 _protected prototype_ `static void AddVectorProperty(FConcertPropertySelection& PropertySelection);`
- L72 _protected prototype_ `TFuture<FConcertReplication_ChangeStream_Response> ChangeStreamForSenderClientAndValidate( const FString& InTestName, const FConcertReplication_ChangeStream_Request& Request, const TArray<FConcertBaseStreamInfo>& ExpectedStreams, EChangeStreamValidation ValidationFlags = EChangeStreamValidation::TestWasHandled | EChangeStreamValidation::TestResponseSuccess );` — Sends a ChangeStream request and validates that ExpectedStreams is equal to the registered streams.
- L78 _protected prototype_ `void ValidateSenderClientStreams(const FString& InTestName, const TArray<FConcertBaseStreamInfo>& ExpectedStreams);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(EChangeStreamValidation);` (scope `UE::ConcertSyncTests::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/ClientEventRecorder.h` (Private)


#### enum `UE::ConcertSyncTests::Replication::EEventType`  
`enum class EEventType`  
_L11-21_
- L13 _public enumerator_ `PreStreamChange`
- L14 _public enumerator_ `PostStreamChange`
- L15 _public enumerator_ `PreAuthorityChange`
- L16 _public enumerator_ `PostAuthorityChange`
- L17 _public enumerator_ `PreSyncControlChange`
- L18 _public enumerator_ `PostSyncControlChange`
- L19 _public enumerator_ `PreRemoteEditApplied`
- L20 _public enumerator_ `PostRemoteEditApplied`

#### class `UE::ConcertSyncTests::Replication::FClientEventRecorder`  
`class FClientEventRecorder : public FNoncopyable`  
_L24-61_
- inherits: `FNoncopyable`
- desc: Records the order in which events are broadcast on an IConcertClientReplicationManager.
- L26 _private member_ `IConcertClientReplicationManager& ReplicationManager;`
- L27 _private member_ `TArray<EEventType> EventOrder;`
- L30 _public function_ `FClientEventRecorder(IConcertClientReplicationManager& ReplicationManager UE_LIFETIMEBOUND) : ReplicationManager(ReplicationManager)`
- L42 _public function_ `~FClientEventRecorder()`
- L54 _public function_ `const TArray<EEventType>& GetEventOrder() const`
- L55 _public function_ `void Clear()`
- L59 _private function_ `void HandleEvent(const EEventType EventType)`
- L60 _private function_ `void HandleEvent(const ConcertSyncClient::Replication::FRemoteEditEvent&, const EEventType EventType)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/ConcertClientReplicationBridgeMock.h` (Private)


#### class `UE::ConcertSyncTests::Replication::FConcertClientReplicationBridgeMock`  
`class FConcertClientReplicationBridgeMock : public IConcertClientReplicationBridge`  
_L11-72_
- inherits: `IConcertClientReplicationBridge`
- L15 _public member_ `TArray<FSoftObjectPath> TrackedObjects;`
- L16 _public member_ `TArray<UObject*> AvailableObjects;`
- L18 _public member_ `FConcertClientReplicationBridgeObjectEvent OnObjectDiscoveredDelegate;`
- L19 _public member_ `FConcertClientReplicationBridgeObjectPathEvent OnObjectRemovedDelegate;`
- L21 _public function_ `void InjectAvailableObject(UObject& Object)`
- L26 _public function_ `void HideObject(UObject& Object)`
- L32 _public function_ `virtual void PushTrackedObjects(TArrayView<const FSoftObjectPath> InTrackedObjects) override`
- L49 _public function_ `virtual void PopTrackedObjects(TArrayView<const FSoftObjectPath> InTrackedObjects) override`
- L57 _public function_ `virtual bool IsObjectAvailable(const FSoftObjectPath& Path) override`
- L58 _public function_ `virtual UObject* FindObjectIfAvailable(const FSoftObjectPath& Path) override`
- L70 _public function_ `virtual FConcertClientReplicationBridgeObjectEvent& OnObjectDiscovered() override`
- L71 _public function_ `virtual FConcertClientReplicationBridgeObjectPathEvent& OnObjectHidden() override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L9 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)
- L39 _function_ `` (scope `UE::ConcertSyncTests::Replication::FConcertClientReplicationBridgeMock::PushTrackedObjects`)
- L57 _function_ `virtual bool IsObjectAvailable(const FSoftObjectPath& Path) override` (scope `UE::ConcertSyncTests::Replication::FConcertClientReplicationBridgeMock::IsObjectAvailable`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/Mocks/ReplicationWorkspaceCallInterceptorMock.h` (Private)


#### class `UE::ConcertSyncTests::Replication::FReplicationWorkspaceCallInterceptorMock`  
`class FReplicationWorkspaceCallInterceptorMock : public ConcertSyncServer::Replication::IReplicationWorkspace`  
_L15-106_
- inherits: `ConcertSyncServer::Replication::IReplicationWorkspace`
- L20 _public member_ `TOptional<TTuple<FGuid, FConcertSyncReplicationPayload_LeaveReplication>> LastCall_ProduceClientLeaveReplicationActivity;` — Arguments of last ProduceClientLeaveReplicationActivity call.
- L22 _public member_ `TOptional<TTuple<FGuid, FConcertSyncReplicationPayload_Mute>> LastCall_ProduceClientMuteReplicationActivity;` — Arguments of last ProduceClientMuteReplicationActivity call.
- L24 _public member_ `mutable TOptional<TTuple<FConcertSessionClientInfo>> LastCall_GetLastReplicationActivityByClient;` — Arguments of last GetLastLeaveReplicationActivityByClient call.
- L26 _public member_ `mutable TOptional<TTuple<int64>> LastCall_GetLeaveReplicationActivityById;` — Arguments of last GetLastLeaveReplicationActivityByClient call.
- L29 _public member_ `TOptional<int64> ReturnResult_ProduceClientLeaveReplicationActivity = 0;` — The result to return in ProduceClientLeaveReplicationActivity.
- L31 _public member_ `TOptional<int64> ReturnResult_ProduceClientMuteReplicationActivity = 0;` — The result to return in ProduceClientLeaveReplicationActivity.
- L33 _public member_ `TMap<EConcertSyncReplicationActivityType, FConcertSyncReplicationActivity> ReturnResult_GetLastReplicationActivityByClient;` — The result to return in GetLastReplicationActivityByClient.
- L35 _public member_ `TOptional<FConcertSyncReplicationEvent> ReturnResult_GetReplicationEventById;` — The result to return in GetReplicationEventById.
- L37 _public member_ `TOptional<TArray<FConcertSyncReplicationActivity>> ReturnResult_EnumerateActivities;` — The values to enumerate in EnumerateMuteActivities.
- L40 _public function_ `virtual TOptional<int64> ProduceReplicationActivity(const FGuid& EndpointId, const FConcertSyncReplicationEvent& EventData) override`
- L69 _public function_ `virtual bool GetLastReplicationActivityByClient(const FConcertSessionClientInfo& InClientInfo, EConcertSyncReplicationActivityType ActivityType, FConcertSyncReplicationActivity& OutActivity) const override`
- L80 _public function_ `virtual bool GetReplicationEventById(const int64 ActivityId, FConcertSyncReplicationEvent& OutEvent) const override`
- L90 _public function_ `virtual void EnumerateReplicationActivities(TFunctionRef<EBreakBehavior(const FConcertSyncReplicationActivity& Activity)> Callback) const override`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/Mocks/ReplicationWorkspaceEmptyMock.h` (Private)


#### class `UE::ConcertSyncTests::Replication::FReplicationWorkspaceEmptyMock`  
`class FReplicationWorkspaceEmptyMock : public ConcertSyncServer::Replication::IReplicationWorkspace`  
_L10-20_
- inherits: `ConcertSyncServer::Replication::IReplicationWorkspace`
- L15 _public function_ `virtual TOptional<int64> ProduceReplicationActivity(const FGuid& EndpointId, const FConcertSyncReplicationEvent& EventData) override`
- L16 _public function_ `virtual bool GetLastReplicationActivityByClient(const FConcertSessionClientInfo& InClientInfo, EConcertSyncReplicationActivityType ActivityType, FConcertSyncReplicationActivity& OutActivity) const override`
- L17 _public function_ `virtual bool GetReplicationEventById(const int64 ActivityId, FConcertSyncReplicationEvent& OutEvent) const override`
- L18 _public function_ `virtual void EnumerateReplicationActivities(TFunctionRef<EBreakBehavior(const FConcertSyncReplicationActivity& Activity)> Callback) const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/ReplicatedTestWorld.h` (Private)


#### struct `UE::ConcertSyncTests::Replication::FReplicatedTestWorld`  
`struct FReplicatedTestWorld`  
_L16-61_
- desc: Util that has a world and replication map of the objects in it.
- L18 _public member_ `FPreviewScene PreviewScene;`
- L19 _public member_ `FConcertObjectReplicationMap ReplicationMap;`
- L21 _public function_ `FReplicatedTestWorld() : PreviewScene(FPreviewScene::ConstructionValues() .SetTransactional(false) .SetCreateDefaultLighting(false) .ShouldSimulatePhysics(false) .SetCreatePhysicsScene(false) )`
- L31 _public function_ `template<typename TActor> TActor* SpawnActor(FName Name, FString Label)`
- L41 _public function_ `void AddReplicatedProperty(const UObject* Object, FName RootPropertyName)`
- L45 _public function_ `void AddReplicatedProperties(const UObject* Object, const TArray<TOptional<FConcertPropertyChain>>& Properties)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)
- L47 _function_ `const bool bHasInvalid = Algo::AnyOf(Properties, [](const TOptional<FConcertPropertyChain>& Property){ return !Property.IsSet(); });` (scope `UE::ConcertSyncTests::Replication::FReplicatedTestWorld::AddReplicatedProperties`)
- L58 _function_ `Algo::Transform(Properties, ObjectInfo.PropertySelection.ReplicatedProperties, [](const TOptional<FConcertPropertyChain>& Property){ return *Property; } );` (scope `UE::ConcertSyncTests::Replication::FReplicatedTestWorld::AddReplicatedProperties`)
- L63 _function_ `static void TestReplicatesOnlyProperty(const FConcertObjectReplicationMap& Map, const UObject* Object, FName PropertyName, FAutomationTestBase& Test)` (scope `UE::ConcertSyncTests::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/SendReceiveGenericStreamTestBase.h` (Private)


#### class `UE::ConcertSyncTests::Replication::FSendReceiveGenericTestBase`  
`class FSendReceiveGenericTestBase : public FSendReceiveTestBase`  
_L23-40_
- inherits: `FSendReceiveTestBase`
- desc: Simple test exposing SenderArgs and ReceiverArgs and implements CreateSenderArgs and CreateReceiverArgs to return them, respectively.
- L27 _public function_ `FSendReceiveGenericTestBase(const FString& InName, const bool bInComplexTask) : FSendReceiveTestBase(InName, bInComplexTask)`
- L33 _protected member_ `ConcertSyncClient::Replication::FJoinReplicatedSessionArgs SenderArgs;`
- L34 _protected member_ `ConcertSyncClient::Replication::FJoinReplicatedSessionArgs ReceiverArgs;`
- L37 _protected function_ `virtual ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateSenderArgs() override`
- L38 _protected function_ `virtual ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateReceiverArgs() override`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/SendReceiveObjectTestBase.h` (Private)


#### enum `UE::ConcertSyncTests::Replication::EPropertyTestFlags`  
`enum class EPropertyTestFlags`  
_L21-32_
- desc: Defines the properties to be tested in FSendReceiveObjectTestBase: some tests may want more control of which properties are sent.
- L23 _public enumerator_ `None`
- L25 _public enumerator_ `Float = 1 << 0`
- L26 _public enumerator_ `Vector = 1 << 1`
- L29 _public enumerator_ `SendCDOValues = 1 << 2` — The CDO values should be sent.
- L31 _public enumerator_ `All = Float | Vector`

#### class `UE::ConcertSyncTests::Replication::FSendReceiveObjectTestBase`  
`class FSendReceiveObjectTestBase : public FSendReceiveTestBase`  
_L39-91_
- inherits: `FSendReceiveTestBase`
- desc: Creates a server and connects a sender and receiver client. The clients will be "sending" an UTestReflectionObject among each other.
- L43 _public function_ `FSendReceiveObjectTestBase(const FString& InName, const bool bInComplexTask) : FSendReceiveTestBase(InName, bInComplexTask)`
- L53 _public member_ `UTestReflectionObject* TestObject = nullptr;` — The object the test will be run on. Note: this pointer is knowingly left dangling after the test completes... there really is not need to override CleanUpTest because we assign TestObject first thing in SetUpClientAndServer.
- L54 _public member_ `const FGuid SenderStreamId = FGuid::NewGuid();`
- L57 _public prototype_ `virtual ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateSenderArgs() override;`
- L58 _public prototype_ `virtual ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateReceiverArgs() override;`
- L59 _public prototype_ `virtual void SetUpClientAndServer(ESendReceiveTestFlags Flags = ESendReceiveTestFlags::None) override;`
- L66 _public prototype_ `void SimulateSendObjectToReceiver( TFunctionRef<FReceiveReplicationEventSignature> OnServerReceive = [](auto&, auto&){}, TFunctionRef<FReceiveReplicationEventSignature> OnReceiverClientReceive = [](auto&, auto&){}, EPropertyTestFlags PropertyFlags = EPropertyTestFlags::All );` — Sets test values on TestObject and sends it to the receiver. If the data arrived, bHasServerReceivedData and bHasClientReceivedData are true.
- L67 _public function_ `TFunctionRef<FReceiveReplicationEventSignature> OnServerReceive = [](auto&, auto&)`
- L73 _public prototype_ `void SetTestValues(UTestReflectionObject& Object, EPropertyTestFlags PropertyFlags = EPropertyTestFlags::All);` — Sets the specified properties to its test values
- L75 _public prototype_ `void SetDifferentValues(UTestReflectionObject& Object, EPropertyTestFlags PropertyFlags = EPropertyTestFlags::All);` — Sets the specified properties to values different from the test values
- L78 _public prototype_ `void TestEqualTestValues(UTestReflectionObject& Object, EPropertyTestFlags PropertyFlags = EPropertyTestFlags::All);` — Tests that the specified properties are equal to their test values
- L80 _public prototype_ `void TestEqualDifferentValues(UTestReflectionObject& Object, EPropertyTestFlags PropertyFlags = EPropertyTestFlags::All);` — Tests that the specified properties are equal to the values different from the test values (i.e. the values SetDifferentValues sets).
- L84 _protected member_ `const float SentFloat = 42.f;`
- L85 _protected member_ `const FVector SentVector = { 21.f, 84.f, -1.f };`
- L87 _protected member_ `const float DifferentFloat = -420.f;`
- L88 _protected member_ `const FVector DifferentVector = { -210.f, -840.f, 10.f };`
- L90 _protected function_ `virtual TSet<FGuid> GetSenderStreamIds() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)
- L33 _prototype_ `ENUM_CLASS_FLAGS(EPropertyTestFlags);` (scope `UE::ConcertSyncTests::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/SendReceiveTestBase.h` (Private)


#### enum `UE::ConcertSyncTests::Replication::ESendReceiveTestFlags`  
`enum class ESendReceiveTestFlags : uint8`  
_L27-35_
- L29 _public enumerator_ `None = 0`
- L34 _public enumerator_ `UseRealReplicationBridge = 1 << 1` — Instead of mocking the bridge use the real implementation. The object will only be discovered if it exists when the stream is registered. See IConcertClientReplicationBridge::PushTrackedObjects.

#### class `UE::ConcertSyncTests::Replication::FSendReceiveTestBase`  
`class FSendReceiveTestBase : public FConcertClientServerCommunicationTest`  
_L39-96_
- inherits: `FConcertClientServerCommunicationTest`
- desc: Creates a server, connects a sender and receiver client, and completes a handshake for them.
- L43 _public prototype_ `FSendReceiveTestBase(const FString& InName, const bool bInComplexTask);`
- L52 _public prototype_ `static ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateHandshakeArgsFrom( const UObject& Object, const FGuid& SenderStreamId = FGuid::NewGuid(), EConcertObjectReplicationMode ReplicationMode = EConcertObjectReplicationMode::Realtime, uint8 ReplicationRate = 30 );` — Creates joining arguments containing a stream that will replicate a single object. @param Object The object to replicate @param SenderStreamId The ID of the new stream @param ReplicationMode The replication mode for the object. Set to Realtime by default so tests need not handle latency (due to FConcertReplicatedObjectInfo::ReplicationRate). @param ReplicationRate The replication rate for the object. Only used if ReplicationMode == EConcertObjectReplicationMode::SpecifiedRate
- L59 _public typedef_ `using FReceiveReplicationEventSignature = void(const FConcertSessionContext& Context, const FConcertReplication_BatchReplicationEvent& Event);`
- L61 _public member_ `float FakeDeltaTime = 1.f / 60.f;`
- L63 _public member_ `TSharedPtr<FConcertServerSessionMock> ServerSession;`
- L64 _public member_ `FReplicationWorkspaceEmptyMock WorkspaceMock;`
- L65 _public member_ `TSharedPtr<ConcertSyncServer::Replication::IConcertServerReplicationManager> ServerReplicationManager;`
- L67 _public member_ `FClientInfo* Client_Receiver = nullptr;`
- L69 _public member_ `TSharedPtr<FConcertClientReplicationBridgeMock> BridgeMock_Receiver;` — This is null if ESendReceiveTestFlags::UseRealReplicationBridge was specified.
- L71 _public member_ `TSharedPtr<IConcertClientReplicationBridge> BridgeUsed_Receiver;` — This is always valid. It is the bridge being used by the receiver.
- L72 _public member_ `TSharedPtr<IConcertClientReplicationManager> ClientReplicationManager_Receiver;`
- L74 _public member_ `FClientInfo* Client_Sender = nullptr;`
- L76 _public member_ `TSharedPtr<FConcertClientReplicationBridgeMock> BridgeMock_Sender;` — This is null if ESendReceiveTestFlags::UseRealReplicationBridge was specified.
- L78 _public member_ `TSharedPtr<IConcertClientReplicationBridge> BridgeUsed_Sender;` — This is always valid. It is the bridge being used by the receiver.
- L79 _public member_ `TSharedPtr<IConcertClientReplicationManager> ClientReplicationManager_Sender;`
- L81 _public prototype_ `virtual ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateSenderArgs() = 0;`
- L82 _public prototype_ `virtual ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateReceiverArgs() = 0;`
- L84 _public prototype_ `virtual void SetUpClientAndServer(ESendReceiveTestFlags Flags = ESendReceiveTestFlags::None);`
- L85 _public prototype_ `virtual void SimulateSenderToReceiver( TFunctionRef<FReceiveReplicationEventSignature> OnServerReceive = [](auto&, auto&){}, TFunctionRef<FReceiveReplicationEventSignature> OnReceiverClientReceive = [](auto&, auto&){} );`
- L86 _public function_ `TFunctionRef<FReceiveReplicationEventSignature> OnServerReceive = [](auto&, auto&)`
- L90 _public prototype_ `void TickClient(FClientInfo* Client);`
- L91 _public prototype_ `void TickServer();`
- L94 _public prototype_ `virtual void CleanUpTest(FAutomationTestBase* AutomationTestBase) override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L14 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L18 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L23 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)
- L36 _prototype_ `ENUM_CLASS_FLAGS(ESendReceiveTestFlags);` (scope `UE::ConcertSyncTests::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/SendReceiveWorldTestBase.h` (Private)


#### class `UE::ConcertSyncTests::Replication::FSendReceiveWorldTestBase`  
`class FSendReceiveWorldTestBase : public FSendReceiveGenericTestBase`  
_L17-64_
- inherits: `FSendReceiveGenericTestBase`
- desc: For tests that want to test replication in a UWorld.
- L19 _private typedef_ `using Super = FSendReceiveGenericTestBase;`
- L22 _public function_ `FSendReceiveWorldTestBase(const FString& InName, const bool bInComplexTask) : Super(InName, bInComplexTask)`
- L27 _public prototype_ `virtual void SetupWorld();` — Called by test when it is ready to initialize the world.
- L30 _public prototype_ `UWorld* GetWorld() const;` — @return The test's world.
- L50 _public prototype_ `void SimulateSenderToReceiverForWorld( TFunctionRef<void(UWorld& World)> SetTestValues, TFunctionRef<void(UWorld& World)> SetGarbageValues, TOptional<TFunctionRef<void(UWorld& World)>> TestValues = {} );` — Simulates sending values from one world to the other. This actually operates on the same UWorld instance so that FSoftObjectPaths continue working. This is how to use this function: 1. Set up all your replicated objects 2. SetTestValues sets values on whatever world objects you want 3. This function reads said data and replicates it to the server 4. The server forwards it to the receiving client 5. SetGarbageValues sets values that are different from the test values 6. This function applies the replicated data thus overriding the garbage values (that is assuming replication worked as expected!) 7. This function executes TestValues if set so you can test whether the data was indeed replicated correctly. @param SetTestValues Modifies values on replicated properties before it it sent from the sender client @param SetGarbageValues Modifies values on replicated properties before the replicated data is applied on the receiving client @param TestValues Optionally tests that the replicated data was applied correctly.
- L59 _private member_ `TUniquePtr<FPreviewScene> WorldManager;` — Set when the test is started. Reset by CleanUpTest.
- L62 _private prototype_ `virtual void CleanUpTest(FAutomationTestBase* AutomationTestBase) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/Spec/ClientEventCounter.h` (Private)


#### struct `UE::ConcertSyncTests::Replication::FClientEventCounter`  
`struct FClientEventCounter`  
_L10-41_
- desc: Helps track the number of authority and stream change events in IConcertClientReplicationManager.
- L12 _public member_ `int32 CallCount_PreAuthorityChanged = 0;`
- L13 _public member_ `int32 CallCount_PostAuthorityChanged = 0;`
- L14 _public member_ `int32 CallCount_PreStreamsChanged = 0;`
- L15 _public member_ `int32 CallCount_PostStreamsChanged = 0;`
- L17 _public function_ `void ResetEventCount()`
- L25 _public function_ `void TestCount(FAutomationTestBase& Test, int32 ExpectedStreamCount, int32 ExpectedAuthorityCount) const`
- L33 _public function_ `void Subscribe(const FReplicationClient& Client)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L7 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)
- L35 _function_ `Client.GetClientReplicationManager().OnPreAuthorityChanged().AddLambda([this]{ ++CallCount_PreAuthorityChanged; });` (scope `UE::ConcertSyncTests::Replication::FClientEventCounter::Subscribe`)
- L36 _function_ `Client.GetClientReplicationManager().OnPostAuthorityChanged().AddLambda([this]{ ++CallCount_PostAuthorityChanged; });` (scope `UE::ConcertSyncTests::Replication::FClientEventCounter::Subscribe`)
- L37 _function_ `Client.GetClientReplicationManager().OnPreStreamsChanged().AddLambda([this]{ ++CallCount_PreStreamsChanged; });` (scope `UE::ConcertSyncTests::Replication::FClientEventCounter::Subscribe`)
- L38 _function_ `Client.GetClientReplicationManager().OnPostStreamsChanged().AddLambda([this]{ ++CallCount_PostStreamsChanged; });` (scope `UE::ConcertSyncTests::Replication::FClientEventCounter::Subscribe`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/Spec/ObjectTestReplicator.h` (Private)


#### enum `UE::ConcertSyncTests::Replication::EPropertyReplicationFlags`  
`enum class EPropertyReplicationFlags : uint8`  
_L21-32_
- desc: Defines the properties to be tested in FSendReceiveObjectTestBase: some tests may want more control of which properties are sent.
- L23 _public enumerator_ `None`
- L25 _public enumerator_ `Float = 1 << 0`
- L26 _public enumerator_ `Vector = 1 << 1`
- L29 _public enumerator_ `SendCDOValues = 1 << 2` — The CDO values should be sent.
- L31 _public enumerator_ `All = Float | Vector`

#### enum `UE::ConcertSyncTests::Replication::EPropertyTypeFlags`  
`enum class EPropertyTypeFlags : uint8`  
_L36-43_
- desc: Defines the properties you want to add to the stream
- L38 _public enumerator_ `None`
- L39 _public enumerator_ `Float = 1 << 0`
- L40 _public enumerator_ `Vector = 1 << 1`
- L41 _public enumerator_ `Others = 1 << 2`
- L42 _public enumerator_ `All = Float | Vector | Others`

#### struct `UE::ConcertSyncTests::Replication::FObjectReplicationContext`  
`struct FObjectReplicationContext`  
_L46-53_
- L48 _public member_ `FReplicationClient& Sender;`
- L49 _public member_ `FReplicationServer& Server;`
- L50 _public member_ `FReplicationClient& Receiver;`
- L52 _public member_ `const TCHAR* ContextName = nullptr;` — Helps debug failing tests.

#### class `UE::ConcertSyncTests::Replication::FObjectTestReplicator`  
`class FObjectTestReplicator : public FNoncopyable`  
_L60-141_
- inherits: `FNoncopyable`
- desc: This utility is used in the context of 1 FReplicationServer and 2 FReplicationClients and helps testing transmission of properties from UTestReflectionObject. It assumes you set up
- L64 _public typedef_ `using FReceiveReplicationEventSignature = void(const FConcertSessionContext& Context, const FConcertReplication_BatchReplicationEvent& Event);`
- L67 _public member_ `float SentFloat = 42.f;` — Test values
- L68 _public member_ `FVector SentVector = { 21.f, 84.f, -1.f };`
- L69 _public member_ `float DifferentFloat = -420.f;`
- L70 _public member_ `FVector DifferentVector = { -210.f, -840.f, 10.f };`
- L73 _public member_ `UTestReflectionObject* TestObject = NewObject<UTestReflectionObject>(GetTransientPackage());` — The object that will be transmitted.
- L75 _public prototype_ `FObjectTestReplicator() = default;`
- L76 _public function_ `explicit FObjectTestReplicator(UTestReflectionObject* TestObject) : TestObject(TestObject)`
- L77 _public function_ `explicit FObjectTestReplicator(const FName BaseName) : TestObject(NewObject<UTestReflectionObject>(GetTransientPackage(), MakeUniqueObjectName(GetTransientPackage(), UTestReflectionObject::StaticClass(), BaseName)))`
- L78 _public function_ `explicit FObjectTestReplicator(UPackage* Package) : TestObject(NewObject<UTestReflectionObject>(Package))`
- L81 _public prototype_ `TSharedRef<FObjectTestReplicator> CreateSubobjectReplicator(const FName BaseName = NAME_None) const;` — Create a subobject of TestObject, assigns it to TestObject->InstancedSubobject, and returns a replicator for replicating it.
- L84 _public prototype_ `ConcertSyncClient::Replication::FJoinReplicatedSessionArgs CreateSenderArgs( FGuid SenderStreamId = FGuid::NewGuid(), EConcertObjectReplicationMode ReplicationMode = EConcertObjectReplicationMode::Realtime, uint8 ReplicationRate = 30 ) const;` — Util for creating join args for replicating TestObject.
- L91 _public prototype_ `FConcertReplicationStream CreateStream( FGuid SenderStreamId = FGuid::NewGuid(), EConcertObjectReplicationMode ReplicationMode = EConcertObjectReplicationMode::Realtime, uint8 ReplicationRate = 30 ) const;` — Util for creating a stream that replicates TestObject.
- L97 _public prototype_ `FConcertReplicationStream CreateStreamWithProperties( FGuid SenderStreamId = FGuid::NewGuid(), EPropertyTypeFlags PropertyTypeFlags = EPropertyTypeFlags::All, EConcertObjectReplicationMode ReplicationMode = EConcertObjectReplicationMode::Realtime, uint8 ReplicationRate = 30 ) const;` — Util for creating a stream that replicates TestObject and specifies the properties.
- L105 _public prototype_ `void AddToStream( FConcertReplicationStream& Stream, EConcertObjectReplicationMode ReplicationMode = EConcertObjectReplicationMode::Realtime, uint8 ReplicationRate = 30 ) const;` — Util adding replication settings for TestObject to a stream
- L111 _public prototype_ `void AddToStreamWithProperties( FConcertReplicationStream& Stream, EPropertyTypeFlags PropertyTypeFlags = EPropertyTypeFlags::All, EConcertObjectReplicationMode ReplicationMode = EConcertObjectReplicationMode::Realtime, uint8 ReplicationRate = 30 ) const;` — Util adding replication settings for TestObject to a stream and specifies the properties.
- L119 _public prototype_ `void SimulateSendObjectToReceiver( FAutomationTestBase& Test, FObjectReplicationContext Context, TConstArrayView<FGuid> SenderStreams, TFunctionRef<FReceiveReplicationEventSignature> OnServerReceive = [](auto&, auto&){}, TFunctionRef<FReceiveReplicationEventSignature> OnReceiverClientReceive = [](auto&, auto&){}, EPropertyReplicationFlags PropertyFlags = EPropertyReplicationFlags::All ) const;` — This overload allows you to send properties but from multiple streams.
- L123 _public function_ `FAutomationTestBase& Test, FObjectReplicationContext Context, TConstArrayView<FGuid> SenderStreams, TFunctionRef<FReceiveReplicationEventSignature> OnServerReceive = [](auto&, auto&)`
- L124 _public function_ `FObjectReplicationContext Context, TConstArrayView<FGuid> SenderStreams, TFunctionRef<FReceiveReplicationEventSignature> OnServerReceive = [](auto&, auto&)`
- L129 _public prototype_ `void SetTestValues(EPropertyReplicationFlags PropertyFlags = EPropertyReplicationFlags::All) const;` — Sets the specified properties to its test values
- L131 _public prototype_ `void SetDifferentValues(EPropertyReplicationFlags PropertyFlags = EPropertyReplicationFlags::All) const;` — Sets the specified properties to values different from the test values
- L135 _public prototype_ `void TestValuesWereReplicated(FAutomationTestBase& Test, EPropertyReplicationFlags PropertyFlags = EPropertyReplicationFlags::All, const TCHAR* Context = nullptr) const;` — Tests that the specified properties are equal to their test values
- L137 _public prototype_ `void TestValuesWereNotReplicated(FAutomationTestBase& Test, EPropertyReplicationFlags PropertyFlags = EPropertyReplicationFlags::All, const TCHAR* Context = nullptr) const;` — Tests that the specified properties are equal to the values different from the test values (i.e. the values SetDifferentValues sets).
- L139 _public function_ `void TestValuesWereReplicated(FAutomationTestBase& Test, const TCHAR* Context, EPropertyReplicationFlags PropertyFlags = EPropertyReplicationFlags::All) const`
- L140 _public function_ `void TestValuesWereNotReplicated(FAutomationTestBase& Test, const TCHAR* Context, EPropertyReplicationFlags PropertyFlags = EPropertyReplicationFlags::All) const`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)
- L33 _prototype_ `ENUM_CLASS_FLAGS(EPropertyReplicationFlags);` (scope `UE::ConcertSyncTests::Replication`)
- L44 _prototype_ `ENUM_CLASS_FLAGS(EPropertyTypeFlags);` (scope `UE::ConcertSyncTests::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/Spec/ReplicationClient.h` (Private)


#### enum `UE::ConcertSyncTests::Replication::EReplicationClientFlags`  
`enum class EReplicationClientFlags : uint8`  
_L19-30_
- L21 _public enumerator_ `None = 0`
- L26 _public enumerator_ `UseRealReplicationBridge = 1 << 0` — Instead of mocking the bridge use the real implementation. The object will only be discovered if it exists when the stream is registered. See IConcertClientReplicationBridge::PushTrackedObjects.
- L29 _public enumerator_ `SkipJoinTest = 1 << 1` — Don't test whether joining was successful

#### class `UE::ConcertSyncTests::Replication::FReplicationClient`  
`class FReplicationClient : public FNoncopyable`  
_L34-86_
- inherits: `FNoncopyable`
- desc: Implements reusable behaviour for replication tests, such as the handshake.
- L38 _public function_ `FReplicationClient(const FGuid& ClientEndPointId, EConcertSyncSessionFlags SessionFlags, FConcertServerSessionMock& Server, FAutomationTestBase& TestContext, FConcertClientInfo ClientInfo = {}) : ClientEndPointId(ClientEndPointId) , SessionFlags(SessionFlags) , TestContext(TestContext) , ClientSessionMock(MakeShared<FConcertClientSessionMock>(ClientEndPointId, Server, MoveTemp(ClientInfo)))`
- L46 _public prototype_ `void TickClient(float FakeDeltaTime = 1.f / 60.f);` — Lets the client process any messages that have come in.
- L49 _public prototype_ `TFuture<ConcertSyncClient::Replication::FJoinReplicatedSessionResult> JoinReplication( ConcertSyncClient::Replication::FJoinReplicatedSessionArgs Args = {}, EReplicationClientFlags TestFlags = EReplicationClientFlags::None );` — Joins the client into replication allowing them to participate in replication
- L54 _public prototype_ `TFuture<ConcertSyncClient::Replication::FJoinReplicatedSessionResult> JoinReplicationAsListener( TArray<UObject*> ObjectsToReceive );` — This overload joins replication and injects the objects into the FConcertClientReplicationBridgeMock so they can be received.
- L59 _public prototype_ `void LeaveReplication() const;` — Leaves the session's replication.
- L61 _public function_ `const FGuid& GetEndpointId() const`
- L62 _public function_ `const FConcertClientInfo& GetClientInfo() const`
- L64 _public function_ `TSharedRef<FConcertClientSessionBaseMock> GetClientSessionMock() const`
- L65 _public function_ `FConcertClientReplicationBridgeMock& GetBridgeMock() const`
- L66 _public function_ `IConcertClientReplicationManager& GetClientReplicationManager() const`
- L71 _private member_ `const FGuid ClientEndPointId;` — The client's endpoint.
- L73 _private member_ `const EConcertSyncSessionFlags SessionFlags;` — Relevant for certain requests. Passed to ClientReplicationManager upon creation.
- L76 _private member_ `FAutomationTestBase& TestContext;` — Used to test "obvious" cases that should never fail in any test.
- L78 _private member_ `const TSharedRef<FConcertClientSessionBaseMock> ClientSessionMock;` — The underlying client session
- L81 _private member_ `TSharedPtr<FConcertClientReplicationBridgeMock> BridgeMock;` — Manually detects when objects are "available". This is null if ESendReceiveTestFlags::UseRealReplicationBridge was specified.
- L83 _private member_ `TSharedPtr<IConcertClientReplicationBridge> BridgeUsed;` — Detects when objects are available. This is always valid. It is the bridge being used by the receiver.
- L85 _private member_ `TSharedPtr<IConcertClientReplicationManager> ClientReplicationManager;` — Manages replication client side

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L15 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(EReplicationClientFlags);` (scope `UE::ConcertSyncTests::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Replication/Util/Spec/ReplicationServer.h` (Private)


#### class `UE::ConcertSyncTests::Replication::FReplicationServer`  
`class FReplicationServer : public FNoncopyable`  
_L22-57_
- inherits: `FNoncopyable`
- desc: Reusable logic to simulate a test server in spec tests with.
- L26 _public prototype_ `FReplicationServer( FAutomationTestBase& TestContext, EConcertSyncSessionFlags InSessionFlags = EConcertSyncSessionFlags::Default_MultiUserSession, TSharedRef<ConcertSyncServer::Replication::IReplicationWorkspace> InWorkspace = MakeShared<FReplicationWorkspaceEmptyMock>() );`
- L33 _public prototype_ `FReplicationClient& ConnectClient(FConcertClientInfo ClientInfo = {});` — Connects a client to the server.
- L36 _public prototype_ `void TickServer(float FakeDeltaTime = 1.f / 60.f);` — Lets the server process any messages that have come in.
- L38 _public function_ `const TSharedRef<FConcertServerSessionMock>& GetServerSessionMock() const`
- L43 _private member_ `const EConcertSyncSessionFlags SessionFlags;` — Relevant to some requests. Passed to ServerReplicationManager and clients upon creation.
- L46 _private member_ `FAutomationTestBase& TestContext;` — Used to test "obvious" cases that should never fail in any test.
- L49 _private member_ `TSharedRef<FConcertServerSessionMock> ServerSessionMock;` — The underlying server session
- L51 _private member_ `TSharedRef<ConcertSyncServer::Replication::IReplicationWorkspace> ReplicationWorkspace;` — Mock for the server workspace the replication system interacts with.
- L53 _private member_ `TSharedRef<ConcertSyncServer::Replication::IConcertServerReplicationManager> ServerReplicationManager;` — Manages replication server side
- L56 _private member_ `TArray<TUniquePtr<FReplicationClient>> Clients;` — Clients connected thus far.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncServer` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::ConcertSyncServer`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L17 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Util/ActivityBuilder.h` (Private)


#### class `UE::ConcertSyncTests::FActivityBuilder`  
`class FActivityBuilder`  
_L12-110_
- desc: Helps fill the database
- L14 _private member_ `TArray<FActivityID> Activities;`
- L15 _private member_ `FScopedSessionDatabaseWithEndpoint& SessionDatabase;`
- L18 _public function_ `FActivityBuilder(FScopedSessionDatabaseWithEndpoint& SessionDatabase, uint32 ActivityCount) : SessionDatabase(SessionDatabase)`
- L24 _public function_ `TArray<FActivityID> GetActivities() const`
- L26 _public function_ `bool NewMap(FName MapName, uint32 ActivityIndex, EConcertSyncActivityFlags Flags = EConcertSyncActivityFlags::None)`
- L40 _public function_ `bool SaveMap(FName MapName, uint32 ActivityIndex, EConcertSyncActivityFlags Flags = EConcertSyncActivityFlags::None)`
- L54 _public function_ `bool DeleteMap(FName MapName, uint32 ActivityIndex, EConcertSyncActivityFlags Flags = EConcertSyncActivityFlags::None)`
- L68 _public function_ `bool RenameMap(FName OldMapName, FName NewMapName, uint32 SaveActivityIndex, uint32 RenameActivityIndex, EConcertSyncActivityFlags Flags = EConcertSyncActivityFlags::None)`
- L90 _public function_ `bool CreateActor(FName MapName, uint32 ActivityIndex, FName ActorName = EName::Actor, EConcertSyncActivityFlags Flags = EConcertSyncActivityFlags::None)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncTests` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Util/ClientServerCommunicationTest.h` (Private)


#### class `UE::ConcertSyncTests::FConcertServerSessionBaseMock`  
`class FConcertServerSessionBaseMock : public IConcertServerSession`  
_L22-69_
- inherits: `IConcertServerSession`
- desc: Implements a not-working IConcertServerSession. It must be further overridden to implement just what is required by the tests
- L25 _public function_ `FConcertServerSessionBaseMock() : Id(FGuid::NewGuid()) , Name("FConcertServerSessionBaseMock")`
- L31 _public function_ `virtual const FGuid& GetId() const override` — IConcertSession Begin.
- L32 _public function_ `virtual const FString& GetName() const override`
- L33 _public function_ `virtual void SetName(const FString&) override`
- L34 _public function_ `virtual FMessageAddress GetClientAddress(const FGuid& ClientEndpointId) const override`
- L35 _public function_ `virtual const FConcertSessionInfo& GetSessionInfo() const override`
- L36 _public function_ `virtual FString GetSessionWorkingDirectory() const override`
- L37 _public function_ `virtual TArray<FGuid> GetSessionClientEndpointIds() const override`
- L38 _public function_ `virtual TArray<FConcertSessionClientInfo> GetSessionClients() const override`
- L39 _public function_ `virtual bool FindSessionClient(const FGuid&, FConcertSessionClientInfo&) const override`
- L40 _public function_ `virtual void Startup() override`
- L41 _public function_ `virtual void Shutdown() override`
- L42 _public function_ `virtual FConcertScratchpadRef GetScratchpad() const override`
- L43 _public function_ `virtual FConcertScratchpadPtr GetClientScratchpad(const FGuid&) const override`
- L44 _public function_ `virtual FDelegateHandle InternalRegisterCustomEventHandler(const FName&, const TSharedRef<IConcertSessionCustomEventHandler>&) override`
- L45 _public function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const FDelegateHandle EventHandle) override`
- L46 _public function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const void* EventHandler) override`
- L47 _public function_ `virtual void InternalClearCustomEventHandler(const FName& EventMessageType) override`
- L48 _public function_ `virtual void InternalSendCustomEvent(const UScriptStruct*, const void*, const TArray<FGuid>&, EConcertMessageFlags, TOptional<FConcertSequencedCustomEvent> InSequenceId={}) override`
- L49 _public function_ `virtual void InternalRegisterCustomRequestHandler(const FName&, const TSharedRef<IConcertSessionCustomRequestHandler>&) override`
- L50 _public function_ `virtual void InternalUnregisterCustomRequestHandler(const FName&) override`
- L51 _public function_ `virtual void InternalSendCustomRequest(const UScriptStruct*, const void*, const FGuid&, const TSharedRef<IConcertSessionCustomResponseHandler>&) override`
- L55 _public function_ `virtual FOnConcertServerSessionTick& OnTick() override` — IConcertServerSession Begin
- L56 _public function_ `virtual FOnConcertServerSessionClientChanged& OnSessionClientChanged() override`
- L57 _public function_ `virtual FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint& OnConcertMessageAcknowledgementReceived() override`
- L61 _protected member_ `FGuid Id;`
- L64 _protected member_ `FString Name;` — Those below are unused mocked data member, but required to get the code compiling.
- L65 _protected member_ `FConcertSessionInfo SessionInfo;`
- L66 _protected member_ `FOnConcertServerSessionTick Tick;`
- L67 _protected member_ `FOnConcertServerSessionClientChanged ConnectionChanged;`
- L68 _protected member_ `FOnConcertMessageAcknowledgementReceivedFromLocalEndpoint AckReceived;`

#### class `UE::ConcertSyncTests::FConcertClientSessionBaseMock`  
`class FConcertClientSessionBaseMock : public IConcertClientSession`  
_L72-146_
- inherits: `IConcertClientSession`
- desc: Implements a not-working IConcertClientSession. It must be further overridden to implement just what is required by the tests
- L75 _public function_ `FConcertClientSessionBaseMock(FConcertClientInfo ClientInfo) : Id(FGuid::NewGuid()) , Name("FConcertClientSessionBaseMock") , ClientInfo(MoveTemp(ClientInfo))`
- L82 _public function_ `virtual const FGuid& GetId() const override` — IConcertSession Begin.
- L83 _public function_ `virtual const FString& GetName() const override`
- L84 _public function_ `virtual const FConcertSessionInfo& GetSessionInfo() const override`
- L85 _public function_ `virtual FString GetSessionWorkingDirectory() const override`
- L86 _public function_ `virtual TArray<FGuid> GetSessionClientEndpointIds() const override`
- L87 _public function_ `virtual TArray<FConcertSessionClientInfo> GetSessionClients() const override`
- L88 _public function_ `virtual bool FindSessionClient(const FGuid&, FConcertSessionClientInfo&) const override`
- L89 _public function_ `virtual void Startup() override`
- L90 _public function_ `virtual void Shutdown() override`
- L91 _public function_ `virtual FConcertScratchpadRef GetScratchpad() const override`
- L92 _public function_ `virtual FConcertScratchpadPtr GetClientScratchpad(const FGuid&) const override`
- L93 _public function_ `virtual FDelegateHandle InternalRegisterCustomEventHandler(const FName&, const TSharedRef<IConcertSessionCustomEventHandler>&) override`
- L94 _public function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const FDelegateHandle EventHandle) override`
- L95 _public function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const void* EventHandler) override`
- L96 _public function_ `virtual void InternalClearCustomEventHandler(const FName& EventMessageType) override`
- L97 _public function_ `virtual void InternalSendCustomEvent(const UScriptStruct*, const void*, const TArray<FGuid>&, EConcertMessageFlags, TOptional<FConcertSequencedCustomEvent> InSequenceId={}) override`
- L98 _public function_ `virtual void InternalRegisterCustomRequestHandler(const FName&, const TSharedRef<IConcertSessionCustomRequestHandler>&) override`
- L99 _public function_ `virtual void InternalUnregisterCustomRequestHandler(const FName&) override`
- L100 _public function_ `virtual void InternalSendCustomRequest(const UScriptStruct*, const void*, const FGuid&, const TSharedRef<IConcertSessionCustomResponseHandler>&) override`
- L103 _public function_ `virtual FConcertSequencedCustomEventManager& GetSequencedEventManager() override`
- L108 _public function_ `virtual EConcertConnectionStatus GetConnectionStatus() const override` — IConcertClientSession Begin
- L109 _public function_ `virtual FGuid GetSessionClientEndpointId() const override`
- L110 _public function_ `virtual FGuid GetSessionServerEndpointId() const override`
- L111 _public function_ `virtual const FConcertClientInfo& GetLocalClientInfo() const override`
- L112 _public function_ `virtual void UpdateLocalClientInfo(const FConcertClientInfoUpdate&) override`
- L113 _public function_ `virtual void Connect() override`
- L114 _public function_ `virtual void Disconnect() override`
- L116 _public function_ `virtual EConcertSendReceiveState GetSendReceiveState() const override`
- L121 _public function_ `virtual void SetSendReceiveState(EConcertSendReceiveState InSendReceiveState) override`
- L126 _public function_ `virtual FOnConcertClientSessionTick& OnTick() override`
- L127 _public function_ `virtual FOnConcertClientSessionConnectionChanged& OnConnectionChanged() override`
- L128 _public function_ `virtual FOnConcertClientSessionClientChanged& OnSessionClientChanged() override`
- L129 _public function_ `virtual FOnConcertSessionRenamed& OnSessionRenamed() override`
- L132 _public prototype_ `virtual void HandleCustomEvent(const UScriptStruct* EventType, const void* EventData) = 0;`
- L135 _protected member_ `FGuid Id;`
- L138 _protected member_ `FString Name;` — Those below are unused mocked data member, but required to get the code compiling.
- L139 _protected member_ `FConcertSessionInfo SessionInfo;`
- L140 _protected member_ `FOnConcertClientSessionTick Tick;`
- L141 _protected member_ `FOnConcertClientSessionConnectionChanged ConnectionChanged;`
- L142 _protected member_ `FOnConcertClientSessionClientChanged ClientChanged;`
- L143 _protected member_ `FOnConcertSessionRenamed SessionRenamed;`
- L144 _protected member_ `FConcertSequencedCustomEventManager CustomEventSequenceManager;`
- L145 _protected member_ `FConcertClientInfo ClientInfo;`

#### enum `UE::ConcertSyncTests::EServerSessionTestingFlags`  
`enum class EServerSessionTestingFlags`  
_L148-153_
- L150 _public enumerator_ `None = 0`
- L152 _public enumerator_ `AllowRequestTimeouts = 1 << 0` — In FConcertServerSessionMock::DispatchEvent if no request handler is registered, it is allowed to timeout the request. Otherwise a check() is triggered.

#### class `UE::ConcertSyncTests::FConcertServerSessionMock`  
`class FConcertServerSessionMock : public FConcertServerSessionBaseMock`  
_L157-350_
- inherits: `FConcertServerSessionBaseMock`
- desc: Specializes the base concert server session to act as a fake server session.
- L161 _public function_ `FConcertServerSessionMock()`
- L166 _public function_ `void SetTestFlags(EServerSessionTestingFlags InFlags)`
- L171 _public function_ `virtual void InternalSendCustomEvent(const UScriptStruct* EventType, const void* EventData, const TArray<FGuid>& TargetEndpointIds, EConcertMessageFlags, TOptional<FConcertSequencedCustomEvent> InSequenceId={}) override`
- L188 _public function_ `virtual FDelegateHandle InternalRegisterCustomEventHandler(const FName& EventMessageType, const TSharedRef<IConcertSessionCustomEventHandler>& Handler) override`
- L194 _public function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const FDelegateHandle EventHandle) override`
- L210 _public function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const void* EventHandler) override`
- L226 _public function_ `virtual void InternalRegisterCustomRequestHandler(const FName& RequestMessageType, const TSharedRef<IConcertSessionCustomRequestHandler>& Handler) override`
- L231 _public function_ `virtual void InternalUnregisterCustomRequestHandler(const FName& RequestMessageType) override`
- L236 _public function_ `virtual TArray<FGuid> GetSessionClientEndpointIds() const override`
- L242 _public function_ `void ConnectClient(const FGuid& ClientEndpointId, FConcertClientSessionBaseMock& ClientSession)` — Called by the tests to connect a client to the server.
- L252 _public function_ `void DispatchEvent(const FGuid& RequesterEndpointId, const UScriptStruct* EventType, const void* EventData, const TArray<FGuid>& DestinationEndpointIds, EConcertMessageFlags Flags, TOptional<FConcertSequencedCustomEvent> InSequenceId)`
- L272 _public function_ `void DispatchRequest(const FGuid& RequesterEndpointId, const UScriptStruct* RequestType, const void* RequestData, const TSharedRef<IConcertSessionCustomResponseHandler>& ResponseHandler)` — Called by the FConcertClientSessionMock to dispatch a request
- L299 _public function_ `virtual bool FindSessionClient(const FGuid& EndpointId, FConcertSessionClientInfo& OutSessionClientInfo) const override`
- L315 _public function_ `virtual FOnConcertServerSessionClientChanged& OnSessionClientChanged() override`
- L320 _public function_ `virtual FOnConcertServerSessionTick& OnTick() override`
- L325 _private member_ `FOnConcertServerSessionTick OnTickDelegate;` — Tick delegate for tests that need it
- L328 _private member_ `TMap<FName, TArray<TSharedPtr<IConcertSessionCustomEventHandler>>> CustomEventHandlers;` — Map of session custom event handlers
- L330 _private member_ `TMap<FName, TSharedPtr<IConcertSessionCustomRequestHandler>> CustomRequestHandlers;` — Map of session custom request handlers
- L333 _private member_ `TArray<FGuid> ClientEndpoints;` — Connected client endpoints.
- L336 _private member_ `TArray<FConcertClientSessionBaseMock*> ClientSessions;` — Connected clients sessions.
- L338 _private member_ `EServerSessionTestingFlags TestFlags = EServerSessionTestingFlags::None;`
- L340 _private function_ `void HandleClientLeaveEvent(const FConcertSessionContext& Context, const FConcertSession_LeaveSessionEvent& Event)`

#### class `UE::ConcertSyncTests::FConcertClientSessionMock`  
`class FConcertClientSessionMock : public FConcertClientSessionBaseMock`  
_L353-456_
- inherits: `FConcertClientSessionBaseMock`
- desc: Specializes the base concert client session to act as a fake client session.
- L357 _public function_ `FConcertClientSessionMock(const FGuid& ClientEndpointId, FConcertServerSessionMock& Server, FConcertClientInfo ClientInfo) : FConcertClientSessionBaseMock(MoveTemp(ClientInfo)) , ServerMock(Server) , EndpointId(ClientEndpointId)`
- L364 _public function_ `virtual FDelegateHandle InternalRegisterCustomEventHandler(const FName& EventMessageType, const TSharedRef<IConcertSessionCustomEventHandler>& Handler) override`
- L370 _public function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const FDelegateHandle EventHandle) override`
- L386 _public function_ `virtual void InternalUnregisterCustomEventHandler(const FName& EventMessageType, const void* EventHandler) override`
- L398 _public function_ `virtual void InternalClearCustomEventHandler(const FName& EventMessageType) override`
- L403 _public function_ `virtual void InternalSendCustomEvent(const UScriptStruct* EventType, const void* EventData, const TArray<FGuid>& DestinationEndpointIds, EConcertMessageFlags Flags, TOptional<FConcertSequencedCustomEvent> InSequenceId) override`
- L408 _public function_ `virtual void InternalSendCustomRequest(const UScriptStruct* RequestType, const void* RequestData, const FGuid& DestinationEndpointId, const TSharedRef<IConcertSessionCustomResponseHandler>& Handler) override`
- L414 _public function_ `virtual void HandleCustomEvent(const UScriptStruct* EventType, const void* EventData) override`
- L427 _public function_ `virtual FGuid GetSessionClientEndpointId() const override`
- L432 _public function_ `virtual FGuid GetSessionServerEndpointId() const override`
- L437 _public function_ `virtual void Disconnect() override`
- L448 _public function_ `virtual FOnConcertClientSessionTick& OnTick() override`
- L451 _private member_ `FOnConcertClientSessionTick OnTickDelegate;`
- L452 _private member_ `FConcertServerSessionMock& ServerMock;`
- L453 _private member_ `FGuid EndpointId;`
- L454 _private member_ `bool bIsConnected = true;`
- L455 _private member_ `TMap<FName, TArray<TSharedPtr<IConcertSessionCustomEventHandler>>> CustomEventHandlers;`

#### class `UE::ConcertSyncTests::FConcertClientServerCommunicationTest`  
`class FConcertClientServerCommunicationTest : public FAutomationTestBase`  
_L459-514_
- inherits: `FAutomationTestBase`
- desc: Base class to perform Concert data store client/server tests.
- L471 _public function_ `FConcertClientServerCommunicationTest(const FString& InName, const bool bInComplexTask) : FAutomationTestBase(InName, bInComplexTask)`
- L478 _public function_ `virtual ~FConcertClientServerCommunicationTest() override`
- L484 _public function_ `FClientInfo& ConnectClient(FConcertClientInfo ClientInfo = {})`
- L492 _public function_ `void InitServer()`
- L500 _public function_ `const TSharedPtr<FConcertServerSessionMock>& GetServerSessionMock() const`
- L502 _public function_ `virtual void CleanUpTest(FAutomationTestBase* AutomationTestBase)`
- L512 _private member_ `TSharedPtr<FConcertServerSessionMock> ServerSessionMock;`
- L513 _private member_ `TArray<TUniquePtr<FClientInfo>> Clients;`

#### struct `UE::ConcertSyncTests::FConcertClientServerCommunicationTest::FClientInfo`  
`struct FClientInfo`  
_L462-469_
- L464 _public function_ `FClientInfo(const FGuid& ClientEndPointId, FConcertServerSessionMock& Server, FConcertClientInfo ClientInfo) : ClientSessionMock(MakeShared<FConcertClientSessionMock>(ClientEndPointId, Server, MoveTemp(ClientInfo)))`
- L468 _public member_ `const TSharedRef<FConcertClientSessionBaseMock> ClientSessionMock;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L16 _function_ `inline FString GetTestSessionRootPath()` (scope `UE::ConcertSyncTests`)
- L154 _prototype_ `ENUM_CLASS_FLAGS(EServerSessionTestingFlags);` (scope `UE::ConcertSyncTests`)
- L345 _function_ `const int32 Index = ClientSessions.IndexOfByPredicate([&ClientEndpointId](FConcertClientSessionBaseMock* SessionMock){ return SessionMock->GetSessionClientEndpointId() == ClientEndpointId; });` (scope `UE::ConcertSyncTests::FConcertServerSessionMock::HandleClientLeaveEvent`)
- L392 _function_ `` (scope `UE::ConcertSyncTests::FConcertClientSessionMock::InternalUnregisterCustomEventHandler`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Util/Mock/ConcertClientDataStoreBaseMock.h` (Private)


#### class `UE::ConcertSyncTests::Replication::FConcertClientDataStoreBaseMock`  
`class FConcertClientDataStoreBaseMock : public IConcertClientDataStore`  
_L11-22_
- inherits: `IConcertClientDataStore`
- desc: Implements every function with NotMocked.
- L16 _protected function_ `virtual TFuture<FConcertDataStoreResult> InternalFetchOrAdd(const FName& Key, const UScriptStruct* Type, const FName& TypeName, const void* Payload) override`
- L17 _protected function_ `virtual TFuture<FConcertDataStoreResult> InternalFetchAs(const FName& Key, const UScriptStruct* Type, const FName& TypeName) const override`
- L18 _protected function_ `virtual TFuture<FConcertDataStoreResult> InternalCompareExchange(const FName& Key, const UScriptStruct* Type, const FName& TypeName, const void* Expected, const void* Desired) override`
- L19 _protected function_ `virtual void InternalRegisterChangeNotificationHandler(const FName& Key, const FName& TypeName, const FChangeNotificationHandler& Handler, EConcertDataStoreChangeNotificationOptions Options) override`
- L20 _protected function_ `virtual void InternalUnregisterChangeNotificationHandler(const FName& Key) override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Util/Mock/ConcertClientWorkspaceBaseMock.h` (Private)


#### class `UE::ConcertSyncTests::Replication::FConcertClientWorkspaceBaseMock`  
`class FConcertClientWorkspaceBaseMock : public IConcertClientWorkspace`  
_L13-65_
- inherits: `IConcertClientWorkspace`
- desc: Implements every function with NotMocked.
- L18 _public function_ `virtual IConcertClientSession& GetSession() const override`
- L19 _public function_ `virtual FGuid GetWorkspaceLockId() const override`
- L20 _public function_ `virtual FGuid GetResourceLockId(const FName InResourceName) const override`
- L21 _public function_ `virtual bool AreResourcesLockedBy(TArrayView<const FName> ResourceNames, const FGuid& ClientId) override`
- L22 _public function_ `virtual TFuture<FConcertResourceLockResponse> LockResources(TArray<FName> InResourceName) override`
- L23 _public function_ `virtual TFuture<FConcertResourceLockResponse> UnlockResources(TArray<FName> InResourceName) override`
- L24 _public function_ `virtual bool HasSessionChanges() const override`
- L25 _public function_ `virtual TArray<FName> GatherSessionChanges(bool IgnorePersisted) override`
- L26 _public function_ `virtual TOptional<FString> GetValidPackageSessionPath(FName PackageName) const override`
- L27 _public function_ `virtual FPersistResult PersistSessionChanges(FPersistParameters InParam) override`
- L28 _public function_ `virtual void GetActivities(const int64 FirstActivityIdToFetch, const int64 MaxNumActivities, TMap<FGuid, FConcertClientInfo>& OutEndpointClientInfoMap, TArray<FConcertSessionActivity>& OutActivities) const override`
- L29 _public function_ `virtual int64 GetLastActivityId() const override`
- L30 _public function_ `virtual FOnActivityAddedOrUpdated& OnActivityAddedOrUpdated() override`
- L31 _public function_ `virtual bool HasLiveTransactionSupport(UPackage* InPackage) const override`
- L32 _public function_ `virtual bool ShouldIgnorePackageDirtyEvent(UPackage* InPackage) const override`
- L33 _public function_ `virtual bool FindTransactionEvent(const int64 TransactionEventId, FConcertSyncTransactionEvent& OutTransactionEvent, const bool bMetaDataOnly) const override`
- L34 _public function_ `virtual TFuture<TOptional<FConcertSyncTransactionEvent>> FindOrRequestTransactionEvent(const int64 TransactionEventId, const bool bMetaDataOnly) override`
- L35 _public function_ `virtual bool FindPackageEvent(const int64 PackageEventId, FConcertSyncPackageEventMetaData& OutPackageEvent) const override`
- L36 _public function_ `virtual bool FindReplicationEvent(const int64 ReplicationEventId, FConcertSyncReplicationEvent& OutReplicationEvent) const override`
- L37 _public function_ `virtual FOnWorkspaceSynchronized& OnWorkspaceSynchronized() override`
- L38 _public function_ `virtual FOnFinalizeWorkspaceSyncCompleted& OnFinalizeWorkspaceSyncCompleted() override`
- L39 _public function_ `virtual void AddWorkspaceFinalizeDelegate(FName InDelegateName, FCanFinalizeWorkspaceDelegate InDelegate) override`
- L40 _public function_ `virtual void RemoveWorkspaceFinalizeDelegate(FName InDelegateName) override`
- L41 _public function_ `virtual void AddWorkspaceCanProcessPackagesDelegate(FName InDelegateName, FCanProcessPendingPackages Delegate) override`
- L42 _public function_ `virtual void RemoveWorkspaceCanProcessPackagesDelegate(FName InDelegateName) override`
- L43 _public function_ `virtual bool IsReloadingPackage(FName PackageName) const override`
- L44 _public function_ `virtual IConcertClientDataStore& GetDataStore() override`
- L45 _public function_ `virtual bool IsAssetModifiedByOtherClients(const FName& AssetName, int32* OutOtherClientsWithModifNum, TArray<FConcertClientInfo>* OutOtherClientsWithModifInfo, int32 OtherClientsWithModifMaxFetchNum) const override`
- L46 _public function_ `virtual void SetIgnoreOnRestoreFlagForEmittedActivities(bool bIgnore) override`
- L49 _public prototype_ `virtual ~FConcertClientWorkspaceBaseMock() = default;`
- L60 _private member_ `TSharedRef<FSessionMock> SessionMock = MakeShared<FSessionMock>();`
- L61 _private member_ `FOnActivityAddedOrUpdated OnActivityAddedOrUpdatedDelegate;`
- L62 _private member_ `FOnWorkspaceSynchronized OnWorkspaceSynchronizedDelegate;`
- L63 _private member_ `FOnFinalizeWorkspaceSyncCompleted OnFinalizeWorkspaceSyncCompletedDelegate;`
- L64 _private member_ `FConcertClientDataStoreBaseMock DataStore;`

#### class `UE::ConcertSyncTests::Replication::FConcertClientWorkspaceBaseMock::FSessionMock`  
`class FSessionMock : public FConcertClientSessionBaseMock`  
_L54-59_
- inherits: `FConcertClientSessionBaseMock`
- desc: Required to get stuff to compile
- L57 _public function_ `explicit FSessionMock() : FConcertClientSessionBaseMock(FConcertClientInfo{})`
- L58 _public function_ `virtual void HandleCustomEvent(const UScriptStruct* EventType, const void* EventData) override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::ConcertSyncTests`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Util/Mock/MockUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
- L10 _function_ `template<typename T> T NotMocked(T Ret)` (scope `UE::ConcertSyncTests`) — Utility functions used to detect when a non-mocked function is called, so that we can mock it properly when required.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Util/ScopedSessionDatabase.h` (Private)


#### class `UE::ConcertSyncTests::FScopedSessionDatabase`  
`class FScopedSessionDatabase : public FConcertSyncSessionDatabase`  
_L14-34_
- inherits: `FConcertSyncSessionDatabase`
- L16 _private member_ `FAutomationTestBase& Test;`
- L17 _private member_ `const FString TestSessionPath_Server = FPaths::ProjectIntermediateDir() / TEXT("Con`
- L20 _public function_ `FScopedSessionDatabase(FAutomationTestBase& Test) : Test(Test)`
- L26 _public function_ `~FScopedSessionDatabase()`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncTests` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncTest/Source/ConcertSyncTest/Private/Util/ScopedSessionDatabaseWithEndpoint.h` (Private)


#### class `UE::ConcertSyncTests::FScopedSessionDatabaseWithEndpoint`  
`class FScopedSessionDatabaseWithEndpoint : public FScopedSessionDatabase`  
_L9-27_
- inherits: `FScopedSessionDatabase`
- L11 _private member_ `const FGuid EndpointID;`
- L14 _public function_ `FScopedSessionDatabaseWithEndpoint(FAutomationTestBase& Test) : FScopedSessionDatabase(Test) , EndpointID(FGuid::NewGuid())`
- L26 _public function_ `const FGuid& GetEndpoint() const`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertSyncTests` (scope `UE`)
