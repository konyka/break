# Plugins / MassEQS

- module root: `Plugins/Runtime/MassGameplay/Source/MassEQS`
- headers: 11; symbols: 131
- symbol kinds: class=11, delegate=1, enum=1, enumerator=2, function=19, macro=2, member=28, prototype=56, struct=9, typedef=2
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassSignals

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/Generators/MassEnvQueryGenerator.h` (Public)


#### class `UMassEnvQueryGenerator`  
`class UMassEnvQueryGenerator : public UEnvQueryGenerator, public IMassEQSRequestInterface`  
_L11-32_
- reflection: `UCLASS(EditInlineNew, Abstract, meta = (Category = "Generators"), MinimalAPI)`
- inherits: `UEnvQueryGenerator,IMassEQSRequestInterface`
- desc: Generator that will send its work to MassEQSSubsystem in order to be processed in a Mass Processor
- L19 _public prototype_ `virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const final;` — This will send this Generator Request to MassEQSSubsystem the first time it is called, and Try to complete Generation with the Result from MassEQSSubsystem on subsequent calls.
- L21 _public function_ `virtual inline bool IsCurrentlyRunningAsync() const final`
- L25 _public prototype_ `virtual TUniquePtr<FMassEQSRequestData> GetRequestData(FEnvQueryInstance& QueryInstance) const override PURE_VIRTUAL(UMassEnvQueryGenerator::GetRequestData, return nullptr;);`
- L26 _public prototype_ `virtual UClass* GetRequestClass() const override PURE_VIRTUAL(UMassEnvQueryGenerator::GetRequestData, return nullptr;);`
- L27 _public prototype_ `virtual bool TryAcquireResults(FEnvQueryInstance& QueryInstance) const override PURE_VIRTUAL(UMassEnvQueryGenerator::TryAcquireResults, return false;);`
- L31 _protected member_ `mutable FMassEQSRequestHandler MassEQSRequestHandler;`

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/Generators/MassEnvQueryGenerator_MassEntityHandles.h` (Public)


#### class `UMassEnvQueryGenerator_MassEntityHandles`  
`class UMassEnvQueryGenerator_MassEntityHandles : public UMassEnvQueryGenerator`  
_L18-38_
- reflection: `UCLASS(meta = (DisplayName = "Mass Entity Handles"), MinimalAPI)`
- inherits: `UMassEnvQueryGenerator`
- desc: Generator to be sent to MassEQSSubsystem for processing on Mass. This will Generate UEnvQueryItemType_MassEntityHandles within SearchRadius of any ContextPositions. Set SearchRadius to a value <= 0 in order to get all EntityHandles who have an FTransformFragment.
- L24 _public prototype_ `virtual TUniquePtr<FMassEQSRequestData> GetRequestData(FEnvQueryInstance& QueryInstance) const override;`
- L25 _public function_ `virtual UClass* GetRequestClass() const override`
- L27 _public prototype_ `virtual bool TryAcquireResults(FEnvQueryInstance& QueryInstance) const override;`
- L33 _protected member_ `FAIDataProviderFloatValue SearchRadius;` — `UPROPERTY(EditDefaultsOnly, Category=Generator)` — Any Entity who is within SearchRadius of any SearchCenter will be acquired
- L37 _protected member_ `TSubclassOf<UEnvQueryContext> SearchCenter;` — `UPROPERTY(EditAnywhere, Category=Generator)` — Context of query

#### struct `FMassEQSRequestData_MassEntityHandles`  
`struct FMassEQSRequestData_MassEntityHandles : public FMassEQSRequestData`  
_L41-51_
- inherits: `FMassEQSRequestData`
- desc: Data required to be sent to Mass for processing this Generator Request
- L43 _public function_ `FMassEQSRequestData_MassEntityHandles(const TArray<FVector>& InContextPositions, const float InSearchRadius) : ContextPositions(InContextPositions) , SearchRadius(InSearchRadius)`
- L49 _public member_ `TArray<FVector> ContextPositions;`
- L50 _public member_ `float SearchRadius;`

#### struct `FMassEnvQueryResultData_MassEntityHandles`  
`struct FMassEnvQueryResultData_MassEntityHandles: public FMassEQSRequestData`  
_L53-61_
- inherits: `FMassEQSRequestData`
- L55 _public function_ `FMassEnvQueryResultData_MassEntityHandles(TArray<FMassEnvQueryEntityInfo>&& InGeneratedEntityInfo) : GeneratedEntityInfo(MoveTemp(InGeneratedEntityInfo))`
- L60 _public member_ `TArray<FMassEnvQueryEntityInfo> GeneratedEntityInfo;`

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/Items/EnvQueryItemType_MassEntityHandle.h` (Public)


#### class `UEnvQueryItemType_MassEntityHandle`  
`class UEnvQueryItemType_MassEntityHandle : public UEnvQueryItemType_VectorBase`  
_L14-28_
- reflection: `UCLASS(meta = (DisplayName = "Mass Entity Handles Item Type"), MinimalAPI)`
- inherits: `UEnvQueryItemType_VectorBase`
- desc: EnvQueryType representing a MassEntity. Additionally stores a Cached Transform of the Entity at the time of acquisition, in order to use in the implemented UEnvQueryItemType_VectorBase functions.
- L19 _public typedef_ `typedef FMassEnvQueryEntityInfo FValueType;`
- L21 _public prototype_ `UEnvQueryItemType_MassEntityHandle();`
- L23 _public prototype_ `static const FMassEnvQueryEntityInfo& GetValue(const uint8* RawData);`
- L24 _public prototype_ `static void SetValue(uint8* RawData, const FMassEnvQueryEntityInfo& Value);`
- L26 _public prototype_ `virtual FVector GetItemLocation(const uint8* RawData) const override;`
- L27 _public prototype_ `virtual FRotator GetItemRotation(const uint8* RawData) const override;`

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/MassEQS.h` (Public)


#### class `FMassEQSModule`  
`class FMassEQSModule : public IModuleInterface`  
_L9-11_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassEQS, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassEQS, Log, All);`

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/MassEQSBlueprintLibrary.h` (Public)


#### struct `FMassEnvQueryEntityInfoBlueprintWrapper`  
`struct FMassEnvQueryEntityInfoBlueprintWrapper`  
_L16-37_
- reflection: `USTRUCT(Blueprintable, BlueprintType, meta = (DisplayName = "Mass Entity Info"))`
- desc: Wrapper for Blueprints to be able to parse MassEntityInfo to use functions defined in UMassEQSBlueprintLibrary
- L21 _public prototype_ `FMassEnvQueryEntityInfoBlueprintWrapper() = default;`
- L22 _public function_ `FMassEnvQueryEntityInfoBlueprintWrapper(FMassEnvQueryEntityInfo InEntityInfo) : EntityInfo(InEntityInfo)`
- L27 _public function_ `inline FVector GetCachedEntityPosition() const`
- L28 _public function_ `inline FMassEntityHandle GetEntityHandle() const`
- L29 _public function_ `inline void SetEntityHandle(FMassEntityHandle Handle)`
- L31 _public function_ `const FMassEnvQueryEntityInfo& GetEntityInfo() const`
- L32 _public function_ `inline bool operator==(const FMassEnvQueryEntityInfoBlueprintWrapper& Other) const`
- L35 _private member_ `FMassEnvQueryEntityInfo EntityInfo;`

#### class `UMassEQSBlueprintLibrary`  
`class UMassEQSBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L41-86_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library for interfacing with EntityInfo inside blueprints.
- L53 _public prototype_ `static void SendSignalToEntity(const AActor* Owner, const FMassEnvQueryEntityInfoBlueprintWrapper& EntityInfo, const FName Signal);` — `UFUNCTION(BlueprintCallable, Category = "MassEnvQuery|Commands")` — Sends the input Signal to the Entity defined by EntityInfo.EntityHandle using the UMassSignalSubsystem.
- L60 _public function_ `static inline FString EntityToString(const FMassEnvQueryEntityInfoBlueprintWrapper& EntityInfo)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MassEnvQuery|Utils")`
- L63 _public function_ `static inline FVector GetCachedEntityPosition(const FMassEnvQueryEntityInfoBlueprintWrapper& EntityInfo)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MassEnvQuery|Utils")`
- L66 _public prototype_ `static FVector GetCurrentEntityPosition(const AActor* Owner, const FMassEnvQueryEntityInfoBlueprintWrapper& EntityInfo);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MassEnvQuery|Utils")`
- L70 _public function_ `static inline bool EntityComparison(const FMassEnvQueryEntityInfoBlueprintWrapper& A, const FMassEnvQueryEntityInfoBlueprintWrapper& B)` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MassEnvQuery|Utils")` — Custom comparison function, as the Blueprint Equals did not seem to work.
- L74 _public prototype_ `static bool ContainsEntity(const TArray<FMassEnvQueryEntityInfoBlueprintWrapper>& EntityList, const FMassEnvQueryEntityInfoBlueprintWrapper& EntityInfo);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MassEnvQuery|Utils")` — Custom array-contains function, as the Blueprint version did not seem to work.
- L78 _public prototype_ `static TArray<FMassEnvQueryEntityInfoBlueprintWrapper> GetEnviromentQueryResultAsEntityInfo(const UEnvQueryInstanceBlueprintWrapper* QueryInstance);` — `UFUNCTION(BlueprintCallable, Category = "AI|EQS")` — Outputs an array filled with resulting EntityInfos. Note that it makes sense only if ItemType is a EnvQueryItemType_MassEntityHandle-derived type.
- L82 _private prototype_ `static FMassEnvQueryEntityInfoBlueprintWrapper GetItemAsEntityInfoBPWrapper(const FEnvQueryResult* QueryResult, int32 Index);` — Get result and immediately convert to EntityInfoBlueprintWrapper to skip an extra copy step
- L85 _private prototype_ `static void GetAllAsEntityInfoBPWrappers(const FEnvQueryResult* QueryResult, TArray<FMassEnvQueryEntityInfoBlueprintWrapper>& OutEntityInfo);` — Get result array and convert each EntityInfo to EntityInfoBlueprintWrapper along the way to skip extra copy steps

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/MassEQSSubsystem.h` (Public)


#### class `UMassEQSSubsystem`  
`class UMassEQSSubsystem : public UMassSubsystemBase`  
_L17-85_
- reflection: `UCLASS()`
- inherits: `UMassSubsystemBase`
- desc: Subsystem for sending UMassEQSGenerator and UMassEQSTest requests to Mass Processors, and for returning the results back to EQS.
- L21 _private typedef_ `using FRequestQueue = TQueue<TUniquePtr<FMassEQSRequestData>>;` — Queue holding UniquePtrs to the data required for each Request
- L25 _public prototype_ `FMassEQSRequestHandle PushRequest(const FEnvQueryInstance& QueryInstance, const int32 RequestQueueIndex, TUniquePtr<FMassEQSRequestData>&& Request);` — Push new Request into RequestQueue
- L28 _public prototype_ `TUniquePtr<FMassEQSRequestData> PopRequest(const int32 RequestQueueIndex);` — Dequeue next Request off the RequestQueue, removing it from the queue, and transferring ownership of UniquePtr
- L31 _public prototype_ `void SubmitResults(FMassEQSRequestHandle RequestHandle, TUniquePtr<FMassEQSRequestData>&& Result);` — Send results from a finished/processed request to be stored in this subsystem
- L33 _public prototype_ `TUniquePtr<FMassEQSRequestData> TryAcquireResults(FMassEQSRequestHandle RequestHandle);` — Try to Acquire the results from a request from the QueryInstance, if it is available.
- L36 _public prototype_ `int32 GetRequestQueueIndex(TSubclassOf<UEnvQueryNode> RequestClass);` — Returns the index into RequestQueues for the input class
- L43 _public prototype_ `void CancelRequest(FMassEQSRequestHandle RequestHandle);` — If Request in RequestQueue -> Remove from Queue If Result in Results -> Remove from Results Otherwise, Request is currently being processed -> Log this ID as Cancelled, and ignore result when submitted.
- L46 _public prototype_ `void FinalizeRequest(FMassEQSRequestHandle RequestHandle);` — Finalization step for Handle Management
- L48 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L49 _public prototype_ `virtual void Deinitialize() override;`
- L58 _protected member_ `TMap<TSubclassOf<UEnvQueryNode>, int32> RequestQueueLookup = {};` — Mapping from Class of requester, to index into RequestQueues. Each Class that extends UMassEQSGenerator or UMassEQSTest can be a requester, this will store a Queue for each of these types. @see PostInitialize()
- L64 _protected member_ `TArray<FRequestQueue> RequestQueues = {};` — Array of Queues holding each Request. TQueue does not support copy/assignment, which TMap requires. This is the reason the TQueues are stored in a separate Array.
- L69 _protected prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(RequestAccessDetector);` — The detector only guards the extension of RequestQueues array. Modifying specific elements is not guarded since those are a thread safe queues.
- L72 _protected member_ `TMap<FMassEQSRequestHandle, TUniquePtr<FMassEQSRequestData>> Results;` — Holds results for finished Query
- L73 _protected prototype_ `UE_MT_DECLARE_RW_ACCESS_DETECTOR(ResultAccessDetector);`
- L75 _protected member_ `FIndexedHandleManagerBase<FMassEQSRequestHandle, int32, uint32, true> HandleManager;`
- L81 _protected member_ `TArray<FMassEQSRequestHandle> CancelledRequests;` — Holds all RequestHandles of requests who have been canceled, and not yet submitted. Once this request is submitted, we will ignore the results.
- L84 _protected member_ `bool bIsInitialized = false;` — Used to ignore request cancellation after subsystem is De-Initialized

#### struct `TMassExternalSubsystemTraits`  
`template<> struct TMassExternalSubsystemTraits<UMassEQSSubsystem> final`  
_L88-95_

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L91-94_

#### Free symbols / members of external scopes

- L92 _enumerator_ `GameThreadOnly = false` (scope `TMassExternalSubsystemTraits::__anon0a30d1090103`)
- L93 _enumerator_ `ThreadSafeWrite = true` (scope `TMassExternalSubsystemTraits::__anon0a30d1090103`)

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/MassEQSTypes.h` (Public)


#### struct `FMassEnvQueryEntityInfo`  
`struct FMassEnvQueryEntityInfo`  
_L21-33_
- reflection: `USTRUCT()`
- desc: Contents of EnvQueryItemType_MassEntityHandle @see EnvQueryItemType_MassEntityHandle
- L25 _public prototype_ `FMassEnvQueryEntityInfo() = default;`
- L26 _public prototype_ `FMassEnvQueryEntityInfo(int32 Index, int32 SerialNumber, const FTransform& Transform);`
- L28 _public member_ `FMassEntityHandle EntityHandle;`
- L30 _public member_ `FTransform CachedTransform;` — Cached Transform from time of acquisition allows EnvQueryItemType_MassEntityHandle to implement UEnvQueryItemType_VectorBase
- L32 _public function_ `inline bool operator==(const FMassEnvQueryEntityInfo& Other) const`

#### struct `FMassEQSRequestHandle`  
`struct FMassEQSRequestHandle : public FIndexedHandleBase`  
_L39-50_
- reflection: `USTRUCT()`
- inherits: `FIndexedHandleBase`
- desc: Provides a Unique Handle for incoming MassEQS Requests
- L42 _public prototype_ `FMassEQSRequestHandle() = default;`
- L43 _public function_ `FMassEQSRequestHandle(int32 InIndex, uint32 InSerialNumber) : FIndexedHandleBase(InIndex, InSerialNumber)`
- L47 _public prototype_ `FString ToString() const;`
- L49 _public member_ `static FMassEQSRequestHandle Invalid;`

#### struct `FMassEQSRequestData`  
`struct FMassEQSRequestData`  
_L53-66_
- desc: To be extended to hold any data which needs to be transferred between EQS and Mass for a given Request.
- L55 _public prototype_ `FMassEQSRequestData() = default;`
- L56 _public function_ `FMassEQSRequestData(FMassEQSRequestHandle Handle) : RequestHandle(Handle)`
- L62 _public member_ `FMassEQSRequestHandle RequestHandle = FMassEQSRequestHandle::Invalid;` — Unique ID that MassEQSSubsystem's HandleManager has assigned to this Request
- L65 _public member_ `TArray<FMassEntityHandle> EntityHandles;` — EntityHandles to run this request on. Used for Tests.

#### class `UMassEQSRequestInterface`  
`class UMassEQSRequestInterface : public UInterface`  
_L70-73_
- reflection: `UINTERFACE()`
- inherits: `UInterface`
- desc: Interface for sending and receiving EQS Requests to and from MassEQSSubsystem

#### class `IMassEQSRequestInterface`  
`class IMassEQSRequestInterface`  
_L76-144_
- desc: Interface for sending and receiving EQS Requests to and from MassEQSSubsystem utilizing a MassEQSRequestHandler
- L130 _public prototype_ `virtual TUniquePtr<FMassEQSRequestData> GetRequestData(FEnvQueryInstance& QueryInstance) const = 0;` — Called inside RequestProcessing, in order to create a copy of the relevant data for this Request. @param QueryInstance - The EnvQueryInstance that owns this Generator @return A UniquePtr to the Data-Copy created.
- L137 _public prototype_ `virtual UClass* GetRequestClass() const = 0;` — Get StaticClass of the ImplementingClass. Implementer of this Interface must provide this so we can use the correct StaticClass inside RequestProcessing. Implementation should just be StaticClass() called in derived class.
- L143 _public prototype_ `virtual bool TryAcquireResults(FEnvQueryInstance& QueryInstance) const = 0;` — Called when EnvQueryInstance is checking to try to complete its request. @param QueryInstance - The EnvQueryInstance that owns this Generator

#### struct `IMassEQSRequestInterface::FMassEQSRequestHandler`  
`struct FMassEQSRequestHandler`  
_L86-122_
- desc: Stores relevant information for managing requests sent to MassEQSSubsystem. Provides generic functionality for Sending, Receiving, and Canceling these requests. Any class who implements IMassEQSRequestInterface should have one of these.
- L96 _public prototype_ `void SendOrRecieveRequest(FEnvQueryInstance& QueryInstance, const IMassEQSRequestInterface& MassEQSRequestInterface);` — Called when an EnvQueryInstance is trying to run a Generator or Test who implements this. If this Request has not yet been sent (IE. RequestID == 0u) then we will send this request Otherwise, if this Request was already sent (IE. RequestID > 0u) then we will call TryAcquireResults on the input MassEnvRequestInterface. @param QueryInstance - The EnvQueryInstance sending/receiving this request @param MassEQSRequestInterface - The Interface used to call this, @return A unique ID that the QueryInstance can hold on to in order to later retrieve this request result.
- L99 _public prototype_ `void CancelRequest() const;` — Cancel request if currently ongoing.
- L102 _public prototype_ `void Reset();` — Reset RequestID to 0 and RequestStartTime to -1.f
- L104 _public function_ `inline bool IsPendingResults() const`
- L107 _public member_ `FMassEQSRequestHandle RequestHandle = FMassEQSRequestHandle::Invalid;` — Handle for request in MassEQSSubsystem.
- L109 _public member_ `TObjectPtr<UMassEQSSubsystem> MassEQSSubsystem = nullptr;` — Cached MassEQSSubsystem pointer for interacting with this subsystem
- L111 _public member_ `float RequestStartTime = -1.f;` — The point in time that an ongoing request was sent, -1 if none have been sent.
- L113 _public member_ `float MaxRequestTime = DefaultMaxRequestTime;` — The max amount of time allowed for this request. CancelRequest will be called if this is used after this time has elapsed.
- L115 _public member_ `int32 CachedRequestQueueIndex = -1;`
- L117 _public prototype_ `FMassEQSRequestHandler() = default;`
- L118 _public prototype_ `~FMassEQSRequestHandler();`
- L121 _protected member_ `static constexpr float DefaultMaxRequestTime = 5.f;`

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/MassEQSUtils.h` (Public)


#### struct `FMassEQSUtils`  
`struct FMassEQSUtils`  
_L18-50_
- desc: Holds Utility functions for Mass EQS Needs
- L22 _public prototype_ `static FMassEnvQueryEntityInfo GetItemAsEntityInfo(const FEnvQueryInstance& QueryInstance, int32 Index);` — Returns the Item stored in QueryInstance/QueryResult Items[Index] as EntityInfo
- L23 _public prototype_ `static FMassEnvQueryEntityInfo GetItemAsEntityInfo(const FEnvQueryResult& QueryResult, int32 Index);`
- L26 _public prototype_ `static void GetAllAsEntityInfo(const FEnvQueryInstance& QueryInstance, TArray<FMassEnvQueryEntityInfo>& OutEntityInfo);` — Returns all Items stored in QueryInstance/QueryResult as EntityInfo
- L27 _public prototype_ `static void GetAllAsEntityInfo(const FEnvQueryResult& QueryResult, TArray<FMassEnvQueryEntityInfo>& OutEntityInfo);`
- L30 _public prototype_ `static void GetEntityHandles(const TArray<FMassEnvQueryEntityInfo>& EntityInfo, TArray<FMassEntityHandle>& OutHandles);` — Extracts all EntityHandles out of an array of EntityInfo
- L31 _public prototype_ `static void GetAllAsEntityHandles(const FEnvQueryInstance& QueryInstance, TArray<FMassEntityHandle>& OutHandles);`
- L38 _public function_ `template<typename RequestDataType> static inline RequestDataType* TryAndEnsureCast(TUniquePtr<FMassEQSRequestData>& InPtr)` — Used in MassEnvQueryProcessors, to cast generic FMassEQSRequestData to its corresponding child class. If InPtr is not null, then this Cast should never fail.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSEQS_API`

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/Processors/MassEnvQueryGeneratorProcessor_MassEntityHandles.h` (Public)


#### class `UMassEnvQueryGeneratorProcessor_MassEntityHandles`  
`class UMassEnvQueryGeneratorProcessor_MassEntityHandles : public UMassEnvQueryProcessorBase`  
_L11-22_
- reflection: `UCLASS(meta = (DisplayName = "Mass Entity Handles Generator Processor"))`
- inherits: `UMassEnvQueryProcessorBase`
- desc: Processor for completing MassEQSSubsystem Requests sent from UMassEnvQueryGenerator_MassEntityHandles
- L15 _public prototype_ `UMassEnvQueryGeneratorProcessor_MassEntityHandles();`
- L18 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L19 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L21 _protected member_ `FMassEntityQuery EntityQuery;`

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/Processors/MassEnvQueryProcessorBase.h` (Public)


#### class `UMassEnvQueryProcessorBase`  
`class UMassEnvQueryProcessorBase : public UMassProcessor`  
_L14-23_
- reflection: `UCLASS(MinimalAPI, Abstract, meta = (DisplayName = "Mass EQS Processor Base"))`
- inherits: `UMassProcessor`
- desc: Processor for completing MassEQSSubsystem Requests sent from UMassEnvQueryTest_MassEntityTags
- L19 _protected prototype_ `virtual void InitializeInternal(UObject& Owner, const TSharedRef<FMassEntityManager>& EntityManager);`
- L21 _protected member_ `TSubclassOf<UEnvQueryNode> CorrespondingRequestClass;`
- L22 _protected member_ `int32 CachedRequestQueryIndex = -1;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MASSEQS_API`

### `Plugins/Runtime/MassGameplay/Source/MassEQS/Public/Processors/MassEnvQueryTestProcessor_MassEntityTags.h` (Public)


#### class `UMassEnvQueryTestProcessor_MassEntityTags`  
`class UMassEnvQueryTestProcessor_MassEntityTags : public UMassEnvQueryProcessorBase`  
_L11-23_
- reflection: `UCLASS(meta = (DisplayName = "Mass Entity Tags Test Processor"))`
- inherits: `UMassEnvQueryProcessorBase`
- desc: Processor for completing MassEQSSubsystem Requests sent from UMassEnvQueryTest_MassEntityTags
- L15 _public prototype_ `UMassEnvQueryTestProcessor_MassEntityTags();`
- L18 _protected prototype_ `virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;`
- L19 _protected prototype_ `virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;`
- L20 _protected function_ `virtual bool ShouldAllowQueryBasedPruning(const bool bRuntimeMode = true) const override`
- L22 _protected member_ `FMassEntityQuery EntityQuery;`
