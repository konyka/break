# Runtime / EventLoop

- module root: `Source/Runtime/Online/EventLoop`
- headers: 17; symbols: 337
- symbol kinds: class=13, delegate=1, enum=5, enumerator=13, function=99, macro=7, member=59, namespace=32, prototype=42, struct=24, typedef=42
- PrivateDependencyModuleNames: Core, NetCommon
- PublicDependencyModuleNames: 

### `Source/Runtime/Online/EventLoop/Private/EventLoop/BSDSocket/BSDSocketTypesPrivate.h` (Private)


#### Free symbols / members of external scopes

- L18 _typedef_ `typedef int32 SOCKLEN;`
- L19 _macro_ `#define strerror_r(errno,buf,len) strerror_s(buf,len,errno)`
- L50 _macro_ `#define ioctlsocket ioctl`
- L53 _macro_ `#define SOCKET_ERROR -1`
- L54 _macro_ `#define INVALID_SOCKET -1`
- L56 _typedef_ `typedef socklen_t SOCKLEN;`
- L57 _typedef_ `typedef int32 SOCKET;`
- L58 _typedef_ `typedef sockaddr_in SOCKADDR_IN;`
- L59 _typedef_ `typedef struct timeval TIMEVAL;`
- L61 _function_ `inline int32 closesocket(SOCKET Socket)`
- L69 _function_ `inline FString GetLastErrorString()`

### `Source/Runtime/Online/EventLoop/Private/EventLoop/EventLoopLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace EventLoop` (scope `UE`)
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogEventLoop, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogEventLoop, Log, All);` (scope `UE::EventLoop`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/BSDSocket/BSDSocketTypes.h` (Public)


#### Free symbols / members of external scopes

- L10 _typedef_ `typedef UPTRINT SOCKET;`
- L11 _macro_ `#define INVALID_SOCKET (SOCKET)(~0)`
- L13 _typedef_ `typedef int32 SOCKET;`
- L14 _macro_ `#define INVALID_SOCKET -1`
- L17 _macro_ `#define SOCKET_RESULT_FAILED -1`

### `Source/Runtime/Online/EventLoop/Public/EventLoop/BSDSocket/EventLoopIOAccessBSDSocket.h` (Public)


#### enum `UE::EventLoop::ESocketIoRequestStatus`  
`enum class ESocketIoRequestStatus : uint8`  
_L17-39_
- L24 _public enumerator_ `Ok` — No error occurred, signaled flags are valid. After signaling the handle associated with the request will remain valid until the user deletes the associated request.
- L31 _public enumerator_ `NoResources` — There are no resources available to serve the IO request. This will occur if more requests have been made than the system is capable of handling. After signaling the handle associated with the request is removed.
- L38 _public enumerator_ `Invalid` — The request is invalid. A request may be invalid if another request for the same socket is already in progress. After signaling the handle associated with the request is removed.

#### struct `UE::EventLoop::FIORequestBSDSocket`  
`struct FIORequestBSDSocket`  
_L44-49_
- L46 _public member_ `SOCKET Socket = INVALID_SOCKET;`
- L47 _public member_ `EIOFlags Flags = EIOFlags::None;`
- L48 _public member_ `FSocketIOCallback Callback;`

#### class `UE::EventLoop::FIOAccessBSDSocket`  
`class FIOAccessBSDSocket final : public FNoncopyable`  
_L51-83_
- inherits: `FNoncopyable`
- L59 _public typedef_ `using FStorageType = TManagedStorage<FIORequestBSDSocket, FStorageTraits>;`
- L61 _public function_ `FIOAccessBSDSocket(FStorageType& InIORequestStorage) : IORequestStorage(InIORequestStorage)`
- L66 _public function_ `FIORequestHandle CreateSocketIORequest(FIORequestBSDSocket&& Request)`
- L76 _public function_ `void DestroyIORequest(FIORequestHandle& Handle, FSocketIORequestDestroyedCallback&& OnDestroyComplete = FSocketIORequestDestroyedCallback())`
- L82 _private member_ `FStorageType& IORequestStorage;`

#### struct `UE::EventLoop::FIOAccessBSDSocket::FStorageTraits`  
`struct FStorageTraits : public FManagedStorageDefaultTraits`  
_L54-57_
- inherits: `FManagedStorageDefaultTraits`
- L56 _public typedef_ `using FExternalHandle = FIORequestHandle;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace EventLoop` (scope `UE`)
- L41 _typedef_ `using FSocketIOCallback = TUniqueFunction<void(SOCKET Socket, ESocketIoRequestStatus Status, EIOFlags SignaledFlags)>;` (scope `UE::EventLoop`)
- L42 _typedef_ `using FSocketIORequestDestroyedCallback = FManagedStorageOnRemoveComplete;` (scope `UE::EventLoop`)
- L87 _function_ `inline FString LexToString(UE::EventLoop::ESocketIoRequestStatus Status)`

### `Source/Runtime/Online/EventLoop/Public/EventLoop/BSDSocket/EventLoopIOManagerBSDSocket.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace EventLoop` (scope `UE`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/BSDSocket/EventLoopIOManagerBSDSocketSelect.h` (Public)


#### class `UE::EventLoop::FIOManagerBSDSocketSelect`  
`class FIOManagerBSDSocketSelect final : public IIOManager`  
_L17-41_
- inherits: `IIOManager`
- L20 _public typedef_ `using FIOAccess = FIOAccessBSDSocket;`
- L30 _public prototype_ `FIOManagerBSDSocketSelect(IEventLoop& EventLoop, FParams&& Params);`
- L31 _public prototype_ `virtual ~FIOManagerBSDSocketSelect() = default;`
- L32 _public prototype_ `virtual bool Init() override;`
- L33 _public prototype_ `virtual void Shutdown() override;`
- L34 _public prototype_ `virtual void Notify() override;`
- L35 _public prototype_ `virtual void Poll(FTimespan WaitTime) override;`
- L37 _public prototype_ `FIOAccess& GetIOAccess();`
- L40 _private member_ `TSharedRef<class FIOManagerBSDSocketSelectImpl> Impl;`

#### struct `UE::EventLoop::FIOManagerBSDSocketSelect::FParams`  
`struct FParams`  
_L22-24_

#### struct `UE::EventLoop::FIOManagerBSDSocketSelect::FConfig`  
`struct FConfig`  
_L26-28_

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace EventLoop` (scope `UE`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/BSDSocket/EventLoopNotifier.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace EventLoop` (scope `UE`)
- L11 _typedef_ `using FEventLoopNotifier = FEventLoopNotifierEventFd;` (scope `UE::EventLoop`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace EventLoop` (scope `UE`)
- L17 _typedef_ `using FEventLoopNotifier = FEventLoopNotifierSocket;` (scope `UE::EventLoop`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/BSDSocket/EventLoopNotifierEventFd.h` (Public)


#### class `UE::EventLoop::FEventLoopNotifierEventFd`  
`class FEventLoopNotifierEventFd`  
_L13-27_
- L16 _public prototype_ `bool Init();`
- L17 _public prototype_ `void Shutdown();`
- L19 _public prototype_ `void Notify();`
- L20 _public prototype_ `void Clear();`
- L22 _public function_ `int32 GetFileDescriptorRead() const`
- L25 _private member_ `int32 FileDescriptorRead = INVALID_SOCKET;`
- L26 _private member_ `std::atomic<bool> bNotified = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace EventLoop` (scope `UE`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/BSDSocket/EventLoopNotifierSocket.h` (Public)


#### class `UE::EventLoop::FEventLoopNotifierSocket`  
`class FEventLoopNotifierSocket`  
_L12-27_
- L15 _public prototype_ `bool Init();`
- L16 _public prototype_ `void Shutdown();`
- L18 _public prototype_ `void Notify();`
- L19 _public prototype_ `void Clear();`
- L21 _public function_ `int32 GetFileDescriptorRead() const`
- L24 _private member_ `int32 FileDescriptorListener = INVALID_SOCKET;`
- L25 _private member_ `int32 FileDescriptorWrite = INVALID_SOCKET;`
- L26 _private member_ `int32 FileDescriptorRead = INVALID_SOCKET;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace EventLoop` (scope `UE`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/EventLoop.h` (Public)


#### struct `UE::EventLoop::FEventLoopTraitsBase`  
`struct FEventLoopTraitsBase`  
_L21-62_
- L23 _public function_ `static inline uint32 GetCurrentThreadId()`
- L28 _public function_ `static inline FTimespan GetCurrentTime()`
- L33 _public function_ `static inline bool IsEventLoopThread(uint32 EventLoopThreadId)`
- L38 _public function_ `static inline bool IsInitialized(uint32 EventLoopThreadId)`
- L43 _public function_ `static inline void CheckInitialized(uint32 EventLoopThreadId)`
- L48 _public function_ `static inline void CheckNotInitialized(uint32 EventLoopThreadId)`
- L53 _public function_ `static inline void CheckIsEventLoopThread(uint32 EventLoopThreadId)`
- L58 _public function_ `static inline bool IsShutdownRequested(bool bShutdownRequested)`

#### struct `UE::EventLoop::FEventLoopDefaultTraits`  
`struct FEventLoopDefaultTraits : public FEventLoopTraitsBase`  
_L64-67_
- inherits: `FEventLoopTraitsBase`
- L66 _public typedef_ `using FTimerManagerTraits = FTimerManagerDefaultTraits;`

#### class `UE::EventLoop::TEventLoop`  
`template <typename IOManagerType, typename Traits = FEventLoopDefaultTraits> class TEventLoop final : public IEventLoop`  
_L70-334_
- inherits: `IEventLoop`
- L73 _private member_ `IOManagerType IOManager;`
- L74 _private member_ `TTimerManager<typename Traits::FTimerManagerTraits> TimerManager;`
- L75 _private member_ `TMpscQueue<FAsyncTask> AsyncTasks;`
- L76 _private member_ `TArray<FOnShutdownComplete> ShutdownRequests;`
- L77 _private member_ `FTimespan LoopTime;`
- L78 _private member_ `TAtomic<uint32> EventLoopThreadId;`
- L79 _private member_ `TAtomic<bool> bShutdownRequested;`
- L80 _private member_ `TAtomic<bool> bShutdownCompleted;`
- L81 _private member_ `TAtomic<bool> bNotifyOnInit;`
- L82 _private member_ `UE::FMutex InitMutex;`
- L83 _private member_ `UE::FMutex ShutdownMutex;`
- L92 _public function_ `TEventLoop(FParams&& Params = FParams()) : IOManager(*this, MoveTemp(Params.IOManagerParams)) , TimerManager() , AsyncTasks() , LoopTime() , EventLoopThreadId(0) , bShutdownRequested(false) , bShutdownCompleted(false) , bNotifyOnInit(false)`
- L106 _public prototype_ `virtual ~TEventLoop() = default;`
- L108 _public function_ `typename IOManagerType::FIOAccess& GetIOAccess()`
- L113 _public function_ `virtual bool Init() override`
- L139 _public function_ `virtual void RequestShutdown(FOnShutdownComplete&& OnShutdownComplete = FOnShutdownComplete()) override`
- L178 _public function_ `virtual FTimerHandle SetTimer(FTimerCallback&& Callback, FTimespan InRate, bool InbRepeat = false, TOptional<FTimespan> InFirstDelay = TOptional<FTimespan>()) override`
- L185 _public function_ `virtual void ClearTimer(FTimerHandle& InHandle, FOnTimerCleared&& OnTimerCleared = FOnTimerCleared()) override`
- L195 _public function_ `virtual void PostAsyncTask(FAsyncTask&& Task) override`
- L201 _public function_ `virtual void Run() override`
- L218 _public function_ `virtual bool RunOnce(FTimespan WaitTime) override`
- L288 _public function_ `virtual FTimespan GetLoopTime() const override`
- L295 _private function_ `void RunAsyncTasks()`
- L304 _private function_ `void TryNotify()`

#### struct `UE::EventLoop::TEventLoop::FParams`  
`struct FParams`  
_L86-90_
- L89 _public member_ `typename IOManagerType::FParams IOManagerParams;` — Initial IO manager parameters.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace EventLoop` (scope `UE`)
- L273 _function_ `Algo::ForEach(LocalShutdownRequests, [](FOnShutdownComplete& OnShutdownComplete){ if (OnShutdownComplete) { OnShutdownComplete(); } });` (scope `UE::EventLoop::TEventLoop::RunOnce`) — Run post-shutdown tasks.

### `Source/Runtime/Online/EventLoop/Public/EventLoop/EventLoopHandle.h` (Public)


#### struct `UE::EventLoop::TResourceHandle`  
`template <typename Traits> struct TResourceHandle final`  
_L11-91_
- L19 _public function_ `TResourceHandle() : ID(0)` — Creates an initially unset handle
- L25 _public function_ `explicit TResourceHandle(EGenerateNewHandleType) : ID(GenerateNewID())` — Creates a handle pointing to a new instance
- L31 _public function_ `bool IsValid() const` — True if this handle was ever initialized by the timer manager
- L37 _public function_ `void Invalidate()` — Explicitly clear handle
- L42 _public function_ `bool operator==(const TResourceHandle& Other) const`
- L47 _public function_ `bool operator!=(const TResourceHandle& Other) const`
- L57 _public function_ `FString ToString() const`
- L62 _public function_ `static const TCHAR* GetTypeName()`
- L73 _private function_ `static uint64 GenerateNewID()` — Generates a new ID for use the delegate handle. @return A unique ID for the delegate.
- L88 _private member_ `static TAtomic<uint64> NextID;`
- L90 _private member_ `uint64 ID;`

#### enum `UE::EventLoop::TResourceHandle::EGenerateNewHandleType`  
`enum EGenerateNewHandleType`  
_L13-16_
- L15 _public enumerator_ `GenerateNewHandle`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace EventLoop` (scope `UE`)
- L52 _function_ `friend inline uint32 GetTypeHash(const TResourceHandle& InHandle)` (scope `UE::EventLoop`)
- L94 _member_ `template <typename Traits> TAtomic<uint64> TResourceHandle<Traits>::NextID = 1;` (scope `UE::EventLoop::TResourceHandle<Traits>`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/EventLoopIOManagerNull.h` (Public)


#### class `UE::EventLoop::FIOAccessNull`  
`class FIOAccessNull final : public FNoncopyable`  
_L12-16_
- inherits: `FNoncopyable`

#### class `UE::EventLoop::FIOManagerNull`  
`class FIOManagerNull final : public IIOManager`  
_L18-61_
- inherits: `IIOManager`
- L21 _public typedef_ `using FIOAccess = FIOAccessNull;`
- L27 _public function_ `FIOManagerNull(IEventLoop& EventLoop, FParams&& Params)`
- L31 _public prototype_ `virtual ~FIOManagerNull() = default;`
- L33 _public function_ `virtual bool Init() override`
- L38 _public function_ `virtual void Shutdown() override`
- L42 _public function_ `virtual void Notify() override`
- L47 _public function_ `virtual void Poll(FTimespan WaitTime) override`
- L53 _public function_ `FIOAccess& GetIOAccess()`
- L59 _private member_ `FIOAccess IOAccess;`
- L60 _private member_ `UE::FManualResetEvent Event;`

#### struct `UE::EventLoop::FIOManagerNull::FParams`  
`struct FParams`  
_L23-25_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace EventLoop` (scope `UE`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/EventLoopManagedStorage.h` (Public)


#### struct `UE::EventLoop::FManagedStorageDefaultExternalHandleTraits`  
`struct FManagedStorageDefaultExternalHandleTraits`  
_L19-22_
- L21 _public member_ `static constexpr TCHAR Name[] = TEXT("Man`

#### struct `UE::EventLoop::FManagedStorageTraitsBase`  
`struct FManagedStorageTraitsBase`  
_L24-45_
- L26 _public function_ `static inline uint32 GetCurrentThreadId()`
- L31 _public function_ `static inline bool IsManagerThread(uint32 ManagerThreadId)`
- L36 _public function_ `static inline void CheckNotInitialized(uint32 ManagerThreadId)`
- L41 _public function_ `static inline void CheckIsManagerThread(uint32 ManagerThreadId)`

#### struct `UE::EventLoop::FManagedStorageDefaultTraits`  
`struct FManagedStorageDefaultTraits : public FManagedStorageTraitsBase`  
_L53-74_
- inherits: `FManagedStorageTraitsBase`
- desc: Default traits for managed storage. Traits are used to implement functionality which can be mocked to allow testing the class. In most cases the default traits can be used without modification.
- L62 _public typedef_ `using InternalHandleArryAllocatorType = TInlineAllocator<32>;` — The allocator to use for the internal handle array. An internal handle array is passed to Update to get the handles added since the last call. Using inline storage can prevent an unnecessary allocation when retrieving this info.
- L68 _public member_ `static constexpr bool bStorageAccessThreadChecksEnabled = false;` — Whether to check thread safety when accessing internal storage. Defaulted to off for performance, but can be added to implementation traits for debugging.
- L73 _public typedef_ `using FExternalHandle = TResourceHandle<FManagedStorageDefaultExternalHandleTraits>;` — The type of handle which will ne externally usable.

#### class `UE::EventLoop::TManagedStorage`  
`template <typename ElementType, typename Traits = FManagedStorageDefaultTraits> class TManagedStorage final : public FNoncopyable`  
_L81-511_
- inherits: `FNoncopyable`
- desc: Managed storage class which allows resource creation and removal from any thread. The owning thread may access the storage without thread safety concerns.
- L131 _public function_ `friend inline uint32 GetTypeHash(const TManagedStorageInternalHandle& InHandle)`
- L158 _public typedef_ `using FExternalHandle = typename Traits::FExternalHandle;`
- L159 _public typedef_ `using FInternalHandle = TManagedStorageInternalHandle<FExternalHandle>;`
- L160 _public typedef_ `using FInternalHandleArryType = TArray<FInternalHandle, typename Traits::InternalHandleArryAllocatorType>;`
- L181 _private typedef_ `using FStorageType = TSparseArray<FStorageEntry>;`
- L184 _private member_ `FStorageType Storage;` — The internal storage of entries.
- L186 _private member_ `TMap<FExternalHandle, int32> StorageHandleIndex;` — Mapping of external handles to the array index of the element in Storage.
- L188 _private member_ `TMpscQueue<FAddRequest> AddRequests;` — Requests to add entries to storage. Processed in Update().
- L190 _private member_ `TMpscQueue<FRemoveRequest> RemoveRequests;` — Requests to remove entries from storage. Processed in Update().
- L195 _private member_ `TAtomic<uint32> ManagerThreadId;` — The thread id set when calling Init. This thread becomes the 'Manager' thread and is safe to call non-thread safe methods from.
- L198 _public function_ `TManagedStorage() : Storage() , StorageHandleIndex() , AddRequests() , RemoveRequests() , ManagerThreadId(0)`
- L207 _public prototype_ `~TManagedStorage() = default;`
- L212 _public function_ `inline bool IsManagerThread() const` — External access for checking whether the current thread is the manager thread.
- L222 _public function_ `void Init()` — Initialize storage. NOT thread safe.
- L239 _public function_ `uint32 Update(FInternalHandleArryType* OutAddedHandles = nullptr, FInternalHandleArryType* OutRemovedHandles = nullptr)` — Process all pending storage modifications. NOT thread safe. @param OutAddedHandles	Handles which were added since the last call to Update. Element may not be present in the internal storage if element was also removed since the last call to update. @param OutRemovedHandles Handles which were removed since the last update. @return The number of changes which occurred.
- L298 _public function_ `FExternalHandle Add(ElementType&& Data)` — Requests to add a resource. Thread safe. @param Data The data to be added and managed. @return A new handle for the added resource.
- L314 _public function_ `void Remove(const FExternalHandle Handle, FManagedStorageOnRemoveComplete&& OnRemoveComplete = FManagedStorageOnRemoveComplete())` — Requests to remove a resource. Thread safe. @param Handle The handle for the resource to be removed. @param OnComplete A callback to be signaled once the resource has been destroyed.
- L326 _public function_ `void Remove(const FInternalHandle Handle)` — Removes a resource directly using its internal handle. NOT thread safe. @param Handle The handle for the resource to be removed.
- L338 _public function_ `inline int32 Num() const`
- L344 _public function_ `inline bool IsEmpty() const`
- L350 _public function_ `inline ElementType* Find(FExternalHandle Handle)`
- L364 _public function_ `inline const ElementType* Find(FExternalHandle Handle) const`
- L369 _public function_ `inline ElementType* Find(FInternalHandle Handle)`
- L386 _public function_ `inline const ElementType* Find(FInternalHandle Handle) const`
- L449 _public typedef_ `using TRangedForIterator = TBaseRangeForIterator<false>;`
- L450 _public typedef_ `using TRangedForConstIterator = TBaseRangeForIterator<true>;`
- L452 _public function_ `inline TRangedForIterator begin()`
- L458 _public function_ `inline TRangedForConstIterator begin() const`
- L464 _public function_ `inline TRangedForIterator end()`
- L470 _public function_ `inline TRangedForConstIterator end() const`
- L477 _private function_ `inline void CheckThreadForStorageAccess() const`
- L485 _private function_ `FInternalHandle AddImpl(const FExternalHandle Handle, ElementType&& Data)`
- L494 _private function_ `FInternalHandle RemoveImpl(const FExternalHandle Handle, const FManagedStorageOnRemoveComplete& OnComplete)`

#### struct `UE::EventLoop::TManagedStorage::TManagedStorageInternalHandle`  
`template <typename ExternalHandleType> struct TManagedStorageInternalHandle`  
_L88-156_
- desc: Handle which extends the external resource handle to allow O(1) access into the internal storage array.
- L96 _public function_ `TManagedStorageInternalHandle() : ExternalHandle() , InternalIndex(INDEX_NONE)` — Creates an initially unset handle
- L103 _public function_ `explicit TManagedStorageInternalHandle(EGenerateNewHandleType, ExternalHandleType InExternalHandle, int32 InInternalIndex) : ExternalHandle(InExternalHandle) , InternalIndex(InInternalIndex)` — Creates a handle pointing to a new instance
- L110 _public function_ `bool IsValid() const` — True if this handle was ever initialized by the timer manager
- L116 _public function_ `void Invalidate()` — Explicitly clear handle
- L121 _public function_ `bool operator==(const TManagedStorageInternalHandle& Other) const`
- L126 _public function_ `bool operator!=(const TManagedStorageInternalHandle& Other) const`
- L136 _public function_ `FString ToString() const`
- L142 _public function_ `ExternalHandleType GetExternalHandle() const` — Gets the external view of this handle.
- L148 _public function_ `int32 GetInternalIndex() const` — Gets the internal storage index for the handles data.
- L154 _private member_ `ExternalHandleType ExternalHandle;`
- L155 _private member_ `int32 InternalIndex;`

#### enum `UE::EventLoop::TManagedStorage::TManagedStorageInternalHandle::EGenerateNewHandleType`  
`enum EGenerateNewHandleType`  
_L90-93_
- L92 _public enumerator_ `GenerateNewHandle`

#### struct `UE::EventLoop::TManagedStorage::FAddRequest`  
`struct FAddRequest`  
_L163-167_
- L165 _public member_ `FExternalHandle Handle;`
- L166 _public member_ `ElementType Data;`

#### struct `UE::EventLoop::TManagedStorage::FRemoveRequest`  
`struct FRemoveRequest`  
_L169-173_
- L171 _public member_ `FExternalHandle Handle;`
- L172 _public member_ `FManagedStorageOnRemoveComplete OnComplete;`

#### struct `UE::EventLoop::TManagedStorage::FStorageEntry`  
`struct FStorageEntry`  
_L175-179_
- L177 _public member_ `FInternalHandle InternalHandle;`
- L178 _public member_ `ElementType Data;`

#### class `UE::EventLoop::TManagedStorage::TBaseRangeForIterator`  
`template <bool bConst> class TBaseRangeForIterator`  
_L398-447_
- desc: DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support. NOT thread safe.
- L401 _private typedef_ `using TInternalIterator = typename FStorageType::TRangedForIterator;`
- L402 _private typedef_ `using StorageIteratorType = std::conditional_t<bConst, typename FStorageType::TRangedForConstIterator, typename FStorageType::TRangedForIterator>;`
- L403 _private typedef_ `using InternalElementType = std::conditional_t<bConst, const ElementType, ElementType>;`
- L404 _private typedef_ `using ItElementType = TPair<FInternalHandle, InternalElementType&>;`
- L407 _public function_ `explicit TBaseRangeForIterator(StorageIteratorType InStorageIterator) : StorageIterator(InStorageIterator)`
- L416 _public function_ `inline TBaseRangeForIterator& operator++()`
- L426 _public function_ `inline bool operator==(const TBaseRangeForIterator& Rhs) const`
- L427 _public function_ `inline bool operator!=(const TBaseRangeForIterator& Rhs) const`
- L430 _public function_ `inline explicit operator bool() const` — conversion to "bool" returning true if the iterator is valid.
- L436 _public function_ `inline bool operator !() const` — inverse of the "bool" operator
- L441 _public function_ `inline ItElementType& operator*() const`
- L442 _public function_ `inline ItElementType* operator->() const`
- L445 _private member_ `StorageIteratorType StorageIterator;`
- L446 _private member_ `mutable TOptional<ItElementType> ElementAccess;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace EventLoop` (scope `UE`)
- L17 _typedef_ `using FManagedStorageOnRemoveComplete = TUniqueFunction<void()>;` (scope `UE::EventLoop`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/EventLoopModule.h` (Public)


#### class `UE::EventLoop::FEventLoopModule`  
`class FEventLoopModule : public IModuleInterface`  
_L11-37_
- inherits: `IModuleInterface`
- L20 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created Overloaded to allow the default subsystem a chance to load
- L26 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed. Overloaded to shut down all loaded online subsystems
- L33 _public function_ `virtual bool SupportsDynamicReloading() override` — Override this to set whether your module is allowed to be unloaded on the fly @return	Whether the module supports shutdown separate from the rest of the engine.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace EventLoop` (scope `UE`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/EventLoopTimer.h` (Public)


#### struct `UE::EventLoop::FTimerHandleTraits`  
`struct FTimerHandleTraits`  
_L13-16_
- L15 _public member_ `static constexpr TCHAR Name[] = TEXT("Tim`

#### enum `UE::EventLoop::ETimerStatus`  
`enum class ETimerStatus : uint8`  
_L24-47_
- L30 _public enumerator_ `Pending` — Timer has been queued, but has not started running yet. Timer will become active the next time the timer manager is ticked.
- L34 _public enumerator_ `Active` — Timer is active and will be triggered once its expiration elapses in Tick.
- L38 _public enumerator_ `PendingRemoval` — Timer will be removed during the next tick.
- L42 _public enumerator_ `PendingReschedule` — Timer will be rescheduled during the next tick.
- L46 _public enumerator_ `Executing` — The timer has elapsed and its callback is executing.

#### struct `UE::EventLoop::FTimerData`  
`struct FTimerData`  
_L49-83_
- L51 _public function_ `FTimerData(FTimerCallback&& InCallback, TOptional<FTimespan> InFirstDelay, FTimespan InRate, bool bInRepeat) : Callback(MoveTemp(InCallback)) , FirstDelay(InFirstDelay) , Rate(InRate) , bRepeat(bInRepeat)`
- L60 _public member_ `FTimerCallback Callback;` — Holds the callback to call.
- L63 _public member_ `TOptional<FTimespan> FirstDelay;` — Time to delay the first execution of the timer. Relevant to looping timers.
- L66 _public member_ `FTimespan Rate;` — Time between set and fire, or repeat frequency if looping.
- L69 _public member_ `FTimespan Expiration;` — When the timer is active, the expiration is the absolute time relative to the Timer Manager at which the timer should be fired.
- L71 _public member_ `ETimerStatus Status = ETimerStatus::Pending;`
- L74 _public member_ `uint8 bRepeat : 1;` — If true, this timer will repeat indefinitely. Otherwise, it will be destroyed when it expires.
- L76 _public prototype_ `FTimerData() = default;`
- L79 _public prototype_ `FTimerData(FTimerData&&) = default;` — Movable only
- L80 _public prototype_ `FTimerData(const FTimerData&) = delete;`
- L81 _public prototype_ `FTimerData& operator=(FTimerData&&) = default;`
- L82 _public prototype_ `FTimerData& operator=(const FTimerData&) = delete;`

#### struct `UE::EventLoop::FTimerManagerTraitsBase`  
`struct FTimerManagerTraitsBase`  
_L85-91_
- L87 _public function_ `static inline void CheckIsManagerThread(bool bIsManagerThread)`

#### struct `UE::EventLoop::FTimerManagerDefaultTraits`  
`struct FTimerManagerDefaultTraits : public FTimerManagerTraitsBase`  
_L99-118_
- inherits: `FTimerManagerTraitsBase`
- desc: Default traits for timer manager. Traits are used to implement functionality which can be mocked to allow testing the class. In most cases the default traits can be used without modification.
- L104 _public typedef_ `using FTimerHeapAllocatorType = TInlineAllocator<32>;` — The allocator to use for the timer heap.
- L109 _public typedef_ `using FTimerRepeatAllocatorType = TInlineAllocator<32>;` — The allocator to use for timers waiting to be rescheduled.

#### struct `UE::EventLoop::FTimerManagerDefaultTraits::FStorageTraits`  
`struct FStorageTraits : public FManagedStorageDefaultTraits`  
_L114-117_
- inherits: `FManagedStorageDefaultTraits`
- desc: Default traits used for timer storage.
- L116 _public typedef_ `using FExternalHandle = FTimerHandle;`

#### class `UE::EventLoop::TTimerManager`  
`template <typename Traits = FTimerManagerDefaultTraits> class TTimerManager final : public FNoncopyable`  
_L132-308_
- inherits: `FNoncopyable`
- desc: Timer manager for posting timers to an event loop. The event loop timer manager provides the guarantee that its timers will never fire early while only progressing its view of time based on the delta passed to its Tick method. To provide this guarantee, timers may fire later than requested which is by design. Adding and removing timers are thread-safe, however the timer callback and clear callbacks will both be called from within the Tick method, which may be a different thread. It is up to the user to handle thread safety within their callbacks.
- L135 _public typedef_ `using FStorageType = TManagedStorage<FTimerData, typename Traits::FStorageTraits>;`
- L136 _public typedef_ `using FTimerHandle = typename FStorageType::FExternalHandle;`
- L137 _public typedef_ `using FInternalHandle = typename FStorageType::FInternalHandle;`
- L138 _public typedef_ `using FInternalHandleArryType = typename FStorageType::FInternalHandleArryType;`
- L146 _public function_ `void Init()` — Initialize the timer manager and its storage. NOT thread safe.
- L158 _public prototype_ `void Tick(FTimespan DeltaTime);` — Accumulate the timer managers elapsed time and fire timers which have elapsed. NOT thread safe. @param DeltaTime The amount of time which has elapsed since the last call to Tick.
- L168 _public function_ `inline bool GetNextTimeout(FTimespan& OutTimeout) const` — Retrieve the remaining time since the last call to Tick before the next timer will fire. NOT thread safe. @param OutTimeout Time amount of time relative to TimerManagers' internal time until the next valid timer will run. @return true if a valid timer is currently set.
- L188 _public function_ `inline uint32 GetNumTimers() const` — Returns the total number of timers. Includes active timers and timers waiting to be rescheduled. NOT thread safe. @return the total number of timers.
- L205 _public function_ `inline FTimerHandle SetTimer(FTimerCallback&& Callback, FTimespan InRate, bool InbRepeat = false, TOptional<FTimespan> InFirstDelay = TOptional<FTimespan>())` — Set a new timer. The timer callback will be triggered from within the call to Tick, which may occur on a different thread from the one which set the timer. Thread safe. @param Callback Callback to call when timer fires. @param InRate The amount of time between set and firing. @param InbRepeat true to keep firing at Rate intervals, false to fire only once. @param InFirstDelay The time for the first iteration of a looping timer. @return handle to the registered timer.
- L234 _public function_ `inline void ClearTimer(FTimerHandle& InHandle, FOnTimerCleared&& OnTimerCleared = FOnTimerCleared())` — Clears a previously set timer. Thread safe. @param InHandle The handle of the timer to clear. @param OnTimerCleared Callback to be fired when the timer has been removed. The callback will be fired within the Tick method which may be a different thread from which the timer clear was requested.
- L260 _public function_ `inline bool HasPendingRepeatTimer() const` — Returns whether any timers are waiting to be rescheduled. NOT thread safe. @return true if a valid timer is waiting to be rescheduled.
- L299 _private member_ `FStorageType Storage;` — Storage for timer entries.
- L301 _private member_ `TArray<FInternalHandle, typename Traits::FTimerHeapAllocatorType> ActiveTimerHeap;` — Heap of actively running timers.
- L303 _private member_ `TArray<FInternalHandle, typename Traits::FTimerRepeatAllocatorType> PendingRepeatTimers;` — Timers which will be rescheduled on the next call to Tick.
- L305 _private member_ `FTimespan InternalTime;` — An internally consistent clock. Advances during ticking.
- L307 _private member_ `bool bIsTicking = false;` — Track whether the timer manager is in the process of ticking.
- L311 _function_ `template <typename Traits> void TTimerManager<Traits>::Tick(FTimespan DeltaTime)`

#### struct `UE::EventLoop::TTimerManager::FTimerHeapOrder`  
`struct FTimerHeapOrder`  
_L266-296_
- L268 _public function_ `explicit FTimerHeapOrder(const FStorageType& InStorage) : Storage(InStorage) , NumTimers(InStorage.Num())`
- L274 _public function_ `bool operator()(FInternalHandle LhsHandle, FInternalHandle RhsHandle) const`
- L294 _public member_ `const FStorageType& Storage;`
- L295 _public member_ `int32 NumTimers;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace EventLoop` (scope `UE`)
- L18 _typedef_ `using FTimerCallback = TUniqueFunction<void()>;` (scope `UE::EventLoop`)
- L20 _typedef_ `using FOnTimerCleared = FManagedStorageOnRemoveComplete;` (scope `UE::EventLoop`)
- L22 _typedef_ `using FTimerHandle = TResourceHandle<FTimerHandleTraits>;` (scope `UE::EventLoop`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/IEventLoop.h` (Public)


#### class `UE::EventLoop::IEventLoop`  
`class IEventLoop`  
_L16-96_
- L19 _public prototype_ `virtual ~IEventLoop() = default;`
- L26 _public prototype_ `virtual bool Init() = 0;` — Initialize the event loop. NOT thread safe.
- L34 _public prototype_ `virtual void RequestShutdown(FOnShutdownComplete&& OnShutdownComplete = FOnShutdownComplete()) = 0;` — Signals a shutdown request to the event loop. May be signaled from any thread. Once called, RunOnce will return false after completing its current iteration. Thread safe.
- L48 _public prototype_ `virtual FTimerHandle SetTimer(FTimerCallback&& Callback, FTimespan InRate, bool InbRepeat = false, TOptional<FTimespan> InFirstDelay = TOptional<FTimespan>()) = 0;` — Set a new timer. The timer callback will be triggered from within the call to RunOnce, which may occur on a different thread from the one which set the timer. Thread safe. @param Callback Callback to call when timer fires. @param InRate The amount of time between set and firing. @param InbRepeat true to keep firing at Rate intervals, false to fire only once. @param InFirstDelay The time for the first iteration of a looping timer. @return handle to the registered timer.
- L59 _public prototype_ `virtual void ClearTimer(FTimerHandle& InHandle, FOnTimerCleared&& OnTimerCleared = FOnTimerCleared()) = 0;` — Clears a previously set timer. Thread safe. @param InHandle The handle of the timer to clear. @param OnTimerCleared Callback to be fired when the timer has been removed. The callback will be fired from within the event loops RunOnce method.
- L68 _public prototype_ `virtual void PostAsyncTask(FAsyncTask&& Task) = 0;` — Post a task to be run by the event loop. Queues the task to be run and signals the event loop to wake. Thread safe. @param Task The task to be run.
- L76 _public prototype_ `virtual void Run() = 0;` — Run the event loop until shutdown is called. The event loop will wake up when a timer needs to run or an async task has been posted. NOT thread safe.
- L86 _public prototype_ `virtual bool RunOnce(FTimespan WaitTime) = 0;` — Run one iteration of the event loop. NOT thread safe. @param WaitTime Maximum amount of time to wait for events. @return true if RunOnce should be called again.
- L95 _public prototype_ `virtual FTimespan GetLoopTime() const = 0;` — Return the event loops current loop time. NOT thread safe. @return the time the event loop last woke up.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace EventLoop` (scope `UE`)
- L13 _typedef_ `using FAsyncTask = TUniqueFunction<void()>;` (scope `UE::EventLoop`)
- L14 _typedef_ `using FOnShutdownComplete = TUniqueFunction<void()>;` (scope `UE::EventLoop`)

### `Source/Runtime/Online/EventLoop/Public/EventLoop/IEventLoopIOManager.h` (Public)


#### struct `UE::EventLoop::FIORequestHandleTraits`  
`struct FIORequestHandleTraits`  
_L13-16_
- L15 _public member_ `static constexpr auto Name = TEXT("Eve`

#### enum `UE::EventLoop::EIOFlags`  
`enum class EIOFlags : uint32`  
_L19-24_
- L21 _public enumerator_ `None = 0`
- L22 _public enumerator_ `Read = 1 << 0`
- L23 _public enumerator_ `Write = 1 << 1`

#### class `UE::EventLoop::IIOManager`  
`class IIOManager : public FNoncopyable`  
_L27-74_
- inherits: `FNoncopyable`
- L44 _public prototype_ `virtual ~IIOManager() = default;`
- L52 _public prototype_ `virtual bool Init() = 0;` — Initialize the IO manager. Called from within IEventLoop::Init. @return true if successfully initialized.
- L58 _public prototype_ `virtual void Shutdown() = 0;` — Cleanup any resources and prepare for shutdown. Called from IEventLoop::RunOnce when the event loop has received a shutdown request.
- L66 _public prototype_ `virtual void Notify() = 0;` — Notify the IO manager to interrupt a waiting call to Poll. Used to wake the request manager when activity is required. Thread safe.
- L73 _public prototype_ `virtual void Poll(FTimespan WaitTime) = 0;` — Poll the request manager for activity. @param WaitTime The maximum amount of time to wait for request activity.

#### struct `UE::EventLoop::IIOManager::FParams`  
`struct FParams`  
_L36-38_
- desc: Parameters for starting an IO manager. Derived classes are expected to implement the structure with any needed values. Will be passed from the event loop constructor into the IO manager.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace EventLoop` (scope `UE`)
- L17 _typedef_ `using FIORequestHandle = TResourceHandle<FIORequestHandleTraits>;` (scope `UE::EventLoop`)
- L25 _prototype_ `ENUM_CLASS_FLAGS(EIOFlags);` (scope `UE::EventLoop`)
