# Runtime / GDKRuntime

- module root: `Source/Runtime/Microsoft/GDKRuntime`
- headers: 6; symbols: 188
- symbol kinds: class=9, delegate=1, function=30, macro=14, member=18, namespace=1, prototype=104, struct=2, typedef=9
- PrivateDependencyModuleNames: Core, GRDK

### `Source/Runtime/Microsoft/GDKRuntime/Private/GDKUserManager.h` (Private)


#### class `FGDKUserManager`  
`class FGDKUserManager`  
_L22-81_
- desc: The GDK user manager is responsible for assigning a suitable FPlatformUserId for GDK users. FPlatformUserIds are currently recycled when a user signs out & is replaced by another and represent the seat that the user is assigned to
- L25 _public prototype_ `FGDKUserManager();`
- L26 _public prototype_ `virtual ~FGDKUserManager();`
- L28 _public prototype_ `FGDKUserHandle GetUserHandleByPlatformId(FPlatformUserId PlatformUserId) const;`
- L29 _public prototype_ `FGDKUserHandle GetUserHandleByXUserId(uint64 XUserId) const;`
- L30 _public prototype_ `FPlatformUserId GetPlatformIdByUserHandle(const FGDKUserHandle& UserHandle);`
- L31 _public prototype_ `TOptional<uint64> GetXUserIdByPlatformId(FPlatformUserId PlatformUserId) const;`
- L32 _public prototype_ `TArray<FGDKUserHandle> GetAllUserHandles() const;`
- L33 _public prototype_ `bool WasUserRecentlySignedOut(XUserLocalId UserLocalId) const;`
- L34 _public prototype_ `int32 FindEmptySeat() const;`
- L35 _public prototype_ `bool HasDefaultUser() const;`
- L36 _public prototype_ `void AddDefaultUser();`
- L37 _public prototype_ `void PickUserAsync(XUserAddOptions Options, FGDKPickUserCompleteDelegate OnPickUserCompleteDelegate);`
- L39 _public prototype_ `void DebugDump() const;`
- L43 _protected prototype_ `FPlatformUserId GetPlatformIdForSeat(int32 SeatIndex) const;` — internal helper functions
- L44 _protected prototype_ `int32 FindSeatForUser(const FGDKUserHandle& UserHandle);`
- L45 _protected prototype_ `int32 GetCurrentSeatForUser(const FGDKUserHandle& UserHandle) const;`
- L49 _private prototype_ `void OnUserChange(XUserLocalId UserLocalId, XUserChangeEvent Event);` — callbacks
- L50 _private prototype_ `void OnApplicationWillEnterBackground();`
- L51 _private prototype_ `void OnApplicationHasEnteredForeground();`
- L54 _private function_ `FORCEINLINE static bool IsValid(const XUserLocalId& UserLocalId)` — helper functions
- L56 _private prototype_ `void HandleXUserAddComplete(XUserAddOptions Options, HRESULT hResult, FGDKUserHandle User, FGDKPickUserCompleteDelegate OnPickUserCompleteDelegate);`
- L57 _private prototype_ `void ResolveUserIssueWithUiAsync(FGDKUserHandle User, FGDKPickUserCompleteDelegate OnResolveUserIssueWithUiComplete);`
- L58 _private prototype_ `void HandleResolveUserIssueWithUiComplete(HRESULT hResult, FGDKUserHandle User, FGDKPickUserCompleteDelegate OnPickUserCompleteDelegate);`
- L59 _private prototype_ `void PickUserAsyncComplete(HRESULT hResult, FGDKUserHandle User, FGDKPickUserCompleteDelegate OnPickUserCompleteDelegate);`
- L67 _private prototype_ `void AutoDebugDump( const TCHAR* BannerMessage, EDebugDumpType::Type Type );`
- L68 _private prototype_ `void DebugDump( const TCHAR* BannerMessage, EDebugDumpType::Type Type = 0 ) const;`
- L70 _private prototype_ `void BroadcastUserAddedOnGameThread( int32 SeatIndex );`
- L71 _private prototype_ `void RemoveUserOnGameThread( int32 SeatIndex );`
- L77 _private member_ `TArray<FSeat> Seats;`
- L78 _private member_ `TSet<uint64> SignedOutXUserLocalIds;`
- L79 _private member_ `FCriticalSection StateLock;`
- L80 _private member_ `XTaskQueueRegistrationToken UserChangeCallbackToken;`

#### struct `FGDKUserManager::EDebugDumpType`  
`struct EDebugDumpType`  
_L61-66_
- L63 _public typedef_ `typedef uint8 Type;`
- L64 _public member_ `static const uint8 BeforeStateChange = 1;`
- L65 _public member_ `static const uint8 AfterStateChange = 2;`

#### struct `FGDKUserManager::FSeat`  
`struct FSeat`  
_L73-76_
- L75 _public member_ `FGDKUserHandle PairedUserHandle;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API GDKRUNTIME_API`

### `Source/Runtime/Microsoft/GDKRuntime/Public/GDKHandle.h` (Public)


#### class `TGDKHandle`  
`template <typename HandleType> class TGDKHandle`  
_L33-149_
- L36 _public typedef_ `using ThisType = TGDKHandle<HandleType>;`
- L38 _public function_ `TGDKHandle() : Handle`
- L42 _public function_ `~TGDKHandle()`
- L47 _public function_ `explicit TGDKHandle(HandleType source) : Handle`
- L52 _public function_ `TGDKHandle(const ThisType& source) : Handle`
- L61 _public function_ `ThisType &operator=(const ThisType& source)`
- L72 _public function_ `TGDKHandle(ThisType&& moveFrom) : Handle`
- L78 _public function_ `ThisType& operator=(ThisType&& moveFrom)`
- L88 _public function_ `bool operator==(const ThisType& Rhs) const`
- L93 _public function_ `operator HandleType() const`
- L98 _public function_ `operator const HandleType*() const`
- L103 _public function_ `operator bool() const`
- L108 _public function_ `bool IsValid() const`
- L113 _public function_ `void Reset(HandleType handle)`
- L120 _public function_ `void Clear()`
- L129 _public function_ `HandleType* GetInitReference()`
- L135 _public function_ `HandleType* ReleaseAndGetInitReference()`
- L148 _private member_ `HandleType Handle;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace GDKHandleTraits`
- L16 _function_ `template<typename T> static int32 CompareHandle(T Lhs, T Rhs)` (scope `GDKHandleTraits`)
- L22 _function_ `template<typename T> static void DuplicateHandle(T Source, T* Target)` (scope `GDKHandleTraits`)
- L27 _function_ `template<typename T> static void ReleaseHandle(T Handle)` (scope `GDKHandleTraits`)
- L142 _function_ `friend SIZE_T GetTypeHash(const ThisType& A)` — Needed for TMap::GetTypeHash()
- L151 _macro_ `#define SETHANDLETYPETRAITS(handleType, duplicateMethod, releaseMethod) \`
- L159 _macro_ `#define SETHANDLETYPETRAITSEX(handleType, duplicateMethod, releaseMethod, compareMethod) \`
- L169 _prototype_ `SETHANDLETYPETRAITS(XTaskQueueHandle, XTaskQueueDuplicateHandle, XTaskQueueCloseHandle);`
- L170 _prototype_ `SETHANDLETYPETRAITSEX(XUserHandle, XUserDuplicateHandle, XUserCloseHandle, XUserCompare);`
- L172 _typedef_ `typedef TGDKHandle<XTaskQueueHandle> FGDKTaskQueueHandle;`
- L173 _typedef_ `typedef TGDKHandle<XUserHandle> FGDKUserHandle;`

### `Source/Runtime/Microsoft/GDKRuntime/Public/GDKHandleTracker.h` (Public)


#### class `FGDKHandleTracker`  
`class FGDKHandleTracker`  
_L24-32_
- L27 _public function_ `inline FGDKHandleTracker()`
- L28 _public function_ `inline ~FGDKHandleTracker()`
- L30 _public prototype_ `static void Start();`
- L31 _public prototype_ `static void Stop();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GDKRUNTIME_API`
- L19 _macro_ `#define WITH_GDK_HANDLE_TRACKER (!UE_BUILD_SHIPPING && !ENABLE_PGO_PROFILE && WITH_GRDK)`
- L36 _macro_ `#define GDK_SCOPE_TRACK_HANDLES() FGDKHandleTracker ANONYMOUS_VARIABLE( GDKHandleTrack )` — track GDK handles that were created while the given scope was active. (note: this tracks all GDK handles in all threads.) this is expected to be used for very localized debugging
- L41 _macro_ `#define GDK_SCOPE_TRACK_HANDLES()` — no-op

### `Source/Runtime/Microsoft/GDKRuntime/Public/GDKRuntimeModule.h` (Public)


#### class `IGDKRuntimeModule`  
`class IGDKRuntimeModule : public IModuleInterface`  
_L54-282_
- inherits: `IModuleInterface`
- L61 _public function_ `static inline IGDKRuntimeModule& Get()` — Singleton-like access to the GDK runtime module instance @return Returns IGDKRuntimeModule singleton instance, loading the module on demand if needed
- L70 _public function_ `static inline IGDKRuntimeModule* TryGet()` — Singleton-like access to the GDK runtime module instance @return Returns IGDKRuntimeModule singleton instance if the module is already loaded
- L78 _public prototype_ `virtual bool IsAvailable() const = 0;` — Returns whether the GDK runtime was initialized successfully.
- L84 _public prototype_ `virtual uint32 GetTitleId() const = 0;` — Returns the Title Id for the game. See the GDK documentation for details.
- L89 _public prototype_ `virtual FString GetXboxSandboxId() const = 0;` — Returns the current XBL sandbox for the platform. See the GDK documentation for details.
- L95 _public prototype_ `virtual FString GetPrimaryServiceConfigId( bool bAllowPlaceholder = true ) const = 0;` — Returns the SCID for the title. See the GDK documentation for details. If bAllowPlaceholder is true and no SCID has been defined, a placeholder one will be returned rather than an empty string.
- L102 _public prototype_ `virtual FString GetGamertag(const FGDKUserHandle& UserHandle) const = 0;` — Returns the gamertag for the given user handle @param UserHandle the user to query @return the gamertag for the user, or an empty string if the user is not valid
- L110 _public prototype_ `virtual FString GetGamertag(const FGDKUserHandle& UserHandle, XUserGamertagComponent GamertagComponent) const = 0;` — Returns the gamertag for the given user handle using the given gamertag convension @param UserHandle        the user to query @param GamertagComponent the convention to use - Classic/Modern etc. @return the gamertag for the user, or an empty string if the user is not valid
- L115 _public prototype_ `virtual XUserGamertagComponent GetDefaultGamertagComponent() const = 0;` — Returns the preferred default gametag component
- L121 _public prototype_ `virtual const TCHAR* GetConfigSectionName() const = 0;` — Returns the config section that the GDK configuration is stored in @return [Config Section] name
- L126 _public prototype_ `virtual bool IsUsingSimplifiedUserModel() const = 0;` — Returns whether the project was configured to use the simplified user model
- L131 _public prototype_ `virtual bool IsNetworkInitialized() const = 0;` — Returns whether networking has been initialized yet (see XNetworkingConnectivityHint in the GDK documentation for details.)
- L140 _public prototype_ `virtual HRESULT AsyncGDKTask( TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<void(XAsyncBlock*)> ResultFunction = nullptr, XTaskQueueHandle TaskQueue = nullptr ) const = 0;` — Simple wrapper for async GDK task execution. @param InitFunction   code that will be executed on the game thread to start the operation (e.g. XUserAddAsync). Expected to return the result from the GDK async function. @param ResultFunction optional code that will be executed when the async operation has finished (e.g. XUserAddResult). Execution thread depends on TaskQueue. @param TaskQueue      optional task queue. Default is GetGenericTaskQueue which executes on a background thread and ResultFunction happens on the game thread. @return the result from InitFunction, so S_OK means the async task has started successfully and ResultFunction will be called
- L149 _public prototype_ `virtual HRESULT AsyncGDKTask( class FGDKAsyncTaskMonitor& OutMonitor, TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<void(XAsyncBlock*)> ResultFunction = nullptr, XTaskQueueHandle TaskQueue = nullptr ) const = 0;` — Simple wrapper for cancellable async GDK task execution. @param OutMonitor     variable that will receive the task monitor, allowing cancellation of the task (ResultFunction will still be called, with E_ABORT) @param InitFunction   code that will be executed on the game thread to start the operation (e.g. XUserAddAsync). Expected to return the result from the GDK async function. @param ResultFunction optional code that will be executed when the async operation has finished (e.g. XUserAddResult). Execution thread depends on TaskQueue. @param TaskQueue      optional task queue. Default is GetGenericTaskQueue which executes on a background thread and ResultFunction happens on the game thread. @return the result from InitFunction, so S_OK means the async task has started successfully and ResultFunction will be called
- L155 _public prototype_ `virtual XTaskQueueHandle GetGenericTaskQueue() const = 0;` — Get a reusable task queue. Tasks execute on a background thread and completion callbacks happen on the game thread
- L160 _public prototype_ `virtual XTaskQueueHandle GetBackgroundTaskQueue() const = 0;` — Get a reusable task queue. Tasks execute on a background thread and completion callbacks also happen on a background thread
- L168 _public prototype_ `virtual FGDKUserHandle GetUserHandleByPlatformId(FPlatformUserId PlatformUserId) const = 0;` — Returns the user handle for the given platform user id @param PlatformUserId the user to query @return user handle for the given platform user
- L175 _public prototype_ `virtual FGDKUserHandle GetUserHandleByXUserId(uint64 XUserId) const = 0;` — Returns the user handle for the given XUID @param XUserId XUID to query @return user handle for the given Xbox User Id
- L182 _public prototype_ `virtual FPlatformUserId GetPlatformIdByUserHandle(const FGDKUserHandle& UserHandle) = 0;` — Returns the platform user id for the given user handle @param UserHandle the user to query @return platform user id for the given user
- L189 _public prototype_ `virtual TOptional<uint64> GetXUserIdByPlatformId(FPlatformUserId PlatformUserId) const = 0;` — Returns the XUID for the given platform user @param PlatformUserId the user to query @return Xbox User Id for the given platform user
- L194 _public prototype_ `virtual TArray<FGDKUserHandle> GetAllUserHandles() const = 0;` — Returns all current user handles
- L202 _public prototype_ `virtual bool WasUserRecentlySignedOut(XUserLocalId UserLocalId) const = 0;` — Returns whether the given local user was previously signed in but is not presently signed in @param UserLocalId the user to query @return true if the user had previously signed in but has now signed out. Will return false when the user has completed signing back in @note this function uses XUserLocalId because the user handle would be invalid once the user is signed out
- L209 _public prototype_ `virtual void PickUserAsync(XUserAddOptions Options, FGDKPickUserCompleteDelegate Delegate) const = 0;` — The async call to pick a user through the system UI @param Options The options when show the user pick UI @param Delegate The delegate to receive the HRESULT of the call
- L214 _public prototype_ `virtual FPlatformUserId GetUnpairedPlatformId() const = 0;` — Returns the platform user id that will be used to represent any gamepads that are not paired to a user
- L219 _public prototype_ `virtual void SetRuntimeErrorProcessDelegate(HRESULT hResult, FGDKRuntimeErrorProcessDelegate Delegate) = 0;` — Set runtime error process delegate for specific gdk runtime error
- L224 _public prototype_ `virtual void ClearRuntimeErrorProcessDelegate(HRESULT hResult) = 0;` — Clear runtime error process delegate for specific gdk runtime error
- L229 _public prototype_ `virtual FDelegateHandle RegisterGameInviteReceivedDelegate( FGDKOnGameInviteReceivedDelegate Delegate ) = 0;` — Register a callback for when the game receives an online game invitation. callback parameter is the matchmaking Uri
- L234 _public prototype_ `virtual void UnregisterGameInviteReceivedDelegate( const FDelegateHandle& DelegateHandle ) = 0;` — Unregister a previously-registered game invite callback
- L246 _public prototype_ `virtual EAppReturnType::Type MessageBoxExt(EAppMsgType::Type MsgType, const TCHAR* Text, const TCHAR* Caption) const = 0;` — Show a message box if possible, otherwise print a message and return the default @param MsgType What sort of options are provided @param Text Specific message @param Caption String indicating the title of the message box @return Very strange convention...not really EAppReturnType, see implementation
- L251 _public prototype_ `virtual ENetworkConnectionType GetNetworkConnectionType() const = 0;` — Returns the current network connection type
- L256 _public prototype_ `virtual bool HasActiveWiFiConnection() const = 0;` — Returns whether WiFi connection is currently active
- L261 _public prototype_ `virtual void DisableScreenTimeout() = 0;` — Prevents the screen from dimming, locking or powering down
- L266 _public prototype_ `virtual void EnableScreenTimeout() = 0;` — Allows the screen to dimming, lock or powering down again
- L272 _public prototype_ `virtual void Internal_HandlePlatformTextFieldVisible( bool bIsVisible ) = 0;`
- L273 _public prototype_ `virtual bool Internal_IsPlatformTextFieldVisible() const = 0;`
- L277 _public prototype_ `virtual void Internal_InitForPIE() = 0;`
- L278 _public prototype_ `virtual void Internal_TeardownForPIE() = 0;`
- L279 _public prototype_ `virtual TMulticastDelegate<void()>& GetOnInitForPIE() = 0;`
- L280 _public prototype_ `virtual TMulticastDelegate<void()>& GetOnTeardownForPIE() = 0;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define WITH_GRDK 1`
- L28 _macro_ `#define WITH_GRDK_DEV_RUNTIME_INIT PLATFORM_WINDOWS && !UE_BUILD_SHIPPING && (_GRDK_EDITION >= 240600)`
- L34 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGDK, Log, All);`
- L36 _typedef_ `using FGDKRuntimeErrorProcessDelegate = TTSDelegate<bool(const char* )>;`
- L37 _typedef_ `using FGDKPickUserCompleteDelegate = TTSDelegate<void(HRESULT, FGDKUserHandle)>;`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam( FGDKOnGameInviteReceived, const FString& );`
- L39 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam( FGDKOnGameInviteReceived, const FString& );`
- L40 _typedef_ `typedef FGDKOnGameInviteReceived::FDelegate FGDKOnGameInviteReceivedDelegate;`
- L47 _prototype_ `bool SetupGDKEnvironment( const TCHAR* ConfigIniSection = nullptr );` — Setup GDK runtime if there is any code rely on it before loading IGDKRuntimeModule
- L52 _prototype_ `void TeardownGDKEnvironment();` — Shutdown GDK runtime, symmetrical call to SetupGDKEnvironment
- L286 _prototype_ `const TCHAR* LexToString(XNetworkingConnectivityLevelHint Value);`
- L287 _prototype_ `FString LexToString(const FGDKUserHandle& UserHandle);`
- L288 _prototype_ `FString LexToString(const XUserLocalId& UserId);`

### `Source/Runtime/Microsoft/GDKRuntime/Public/GDKTaskQueueHelpers.h` (Public)


#### class `FGDKAsyncBlock`  
`class FGDKAsyncBlock`  
_L27-46_
- L30 _public prototype_ `FGDKAsyncBlock(void* UserData, FGDKAsyncBlockDelegate Delegate, XTaskQueueHandle TaskQueue = nullptr);`
- L32 _public prototype_ `~FGDKAsyncBlock();`
- L34 _public prototype_ `HRESULT GetStatus();`
- L36 _public prototype_ `XAsyncBlock* GetInnerBlockForGDKAPI();`
- L37 _public prototype_ `void* GetUserData();`
- L38 _public function_ `operator XAsyncBlock*()`
- L41 _protected member_ `XAsyncBlock AsyncBlock;`
- L42 _protected member_ `void* UserData;`
- L43 _protected member_ `FGDKAsyncBlockDelegate Delegate;`
- L45 _protected prototype_ `void DelegateWrapper();`

#### class `FGDKAsyncTaskQueue`  
`class FGDKAsyncTaskQueue`  
_L55-79_
- desc: Wrapper for XTaskQueueHandle that manages clean shutdown automatically This can be used when a separate, custom task queue is required. In most cases FGDKAsyncTaskQueue::GetGenericQueue() should be sufficient
- L58 _public prototype_ `FGDKAsyncTaskQueue( XTaskQueueDispatchMode WorkDispatchMode = XTaskQueueDispatchMode::ThreadPool, XTaskQueueDispatchMode CompletionDispatchMode = XTaskQueueDispatchMode::ThreadPool );`
- L59 _public prototype_ `~FGDKAsyncTaskQueue();`
- L61 _public function_ `FORCEINLINE XTaskQueueHandle GetQueue() const`
- L62 _public prototype_ `HRESULT BlockUntilComplete( XAsyncBlock& AsyncBlock ) const;`
- L63 _public prototype_ `void CancelPendingTasksAndDestroyQueue();`
- L67 _public prototype_ `static XTaskQueueHandle GetGenericQueue();` — access to common task queues
- L68 _public prototype_ `static XTaskQueueHandle GetGenericSerialQueue();` — completion callbacks happen on the game thread and are guaranteed to execute before the next work task starts in a bg thread, ensuring Work -> Callback order
- L69 _public prototype_ `static XTaskQueueHandle GetBackgroundTaskQueue();` — completion callbacks happen on a background thread
- L72 _public prototype_ `static void PlatformInit();` — internal use - startup & shutdown the queue system
- L73 _public prototype_ `static void PlatformTeardown();`
- L76 _protected member_ `XTaskQueueDispatchMode WorkDispatchMode;`
- L77 _protected member_ `XTaskQueueDispatchMode CompletionDispatchMode;`
- L78 _protected member_ `XTaskQueueHandle Queue;`

#### class `FGDKLocalTaskBlock`  
`class FGDKLocalTaskBlock`  
_L95-109_
- desc: Helper class for executing simple GDK async tasks locally. This is expected to be created on the stack. (Use LocalGDKTask() for an easier to use equivalent.) FGDKLocalTaskBlock Block; if (SUCCEEDED( XUserAddAsync( XUserAddOptions::None, Block ) ) ) { AsyncBlock.BlockUntilComplete(); FGDKUserHandle User; XUserAddResult(Block, User.GetInitReference()); }
- L98 _public prototype_ `FGDKLocalTaskBlock();`
- L99 _public prototype_ `~FGDKLocalTaskBlock();`
- L101 _public function_ `operator XAsyncBlock*()`
- L103 _public prototype_ `HRESULT BlockUntilComplete();`
- L104 _public prototype_ `HRESULT GetStatus();`
- L107 _protected member_ `XAsyncBlock AsyncBlock;`
- L108 _protected member_ `FGDKAsyncTaskQueue Queue;`

#### class `FGDKAsyncTaskMonitor`  
`class FGDKAsyncTaskMonitor`  
_L213-228_
- desc: Helper allowing cancellation from AsyncGDKTask() and LaunchGDKTask()
- L220 _public prototype_ `bool TryCancel(bool bWait = true);` — Attempt to cancel the task. Note that the ResultFunction callback will be called and the GDK API function will likely return E_ABORT - When bWait is false, returns true if cancel request was made. - When bWait is true it returns true if the task was successfully cancelled. This will happen before the ResultFunction is called - Returns false in all other failure cases, including if the task has already completed.
- L223 _public prototype_ `bool IsValid() const;` — Determines if the task that we're monitoring is still valid. This will be true until the ResultFunction callback has completed
- L227 _protected member_ `TWeakPtr<FGDKAsyncBlock> WeakBlock;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GDKRUNTIME_API`
- L25 _typedef_ `typedef TFunction<void(class FGDKAsyncBlock*)> FGDKAsyncBlockDelegate;` — Wrapper for XAsyncBlock that allows capture variables in the lambda If lifetime management is not required, using AsyncGDKTask() is recommended instead
- L128 _prototype_ `HRESULT AsyncGDKTask( TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<void(XAsyncBlock*)> ResultFunction = nullptr, XTaskQueueHandle TaskQueue = nullptr );` — Simple wrapper for async GDK task execution. Returns the result from InitFunction, so S_OK means the async task has started successfully AsyncGDKTask( []( XAsyncBlock* Block ) { return XUserAddAsync( XUserAddOptions::None, Block ); }, []( XAsyncBlock* Block ) { FGDKUserHandle User; XUserAddResult(Block, User.GetInitReference()); } );
- L151 _prototype_ `HRESULT AsyncGDKTask( class FGDKAsyncTaskMonitor& OutAsyncTaskMonitor, TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<void(XAsyncBlock*)> ResultFunction = nullptr, XTaskQueueHandle TaskQueue = nullptr );` — Simple wrapper for async GDK task execution that can be monitored via a helper class. Returns the result from InitFunction, so S_OK means the async task has started successfully FGDKAsyncTaskMonitor MyTask; AsyncGDKTask( MyTask, []( XAsyncBlock* Block ) { return XUserAddAsync( XUserAddOptions::None, Block ); }, []( XAsyncBlock* Block ) { FGDKUserHandle User; XUserAddResult(Block, User.GetInitReference()); } ); MyTask.TryCancel(true);
- L171 _prototype_ `HRESULT LocalGDKTask( TFunction<HRESULT(XAsyncBlock*)> InitFunction, TFunction<HRESULT(XAsyncBlock*)> ResultFunction = nullptr );` — Simple wrapper for local GDK task execution. Blocks until the task is completed. Returns the result from InitFunction or ResultFunction LocalGDKTask( []( XAsyncBlock* Block ) { return XUserAddAsync( XUserAddOptions::None, Block ); }, []( XAsyncBlock* Block ) { FGDKUserHandle User; return XUserAddResult(Block, User.GetInitReference()); } );
- L189 _typedef_ `typedef UE::Tasks::TTask<HRESULT> FGDKTask;` — Simple UE::Task wrapper for GDK task execution. Task result contains the result from InitFunction or ResultFunction FGDKTask Task = LaunchGDKTask( UE_SOURCE_LOCATION, []( XAsyncBlock* Block ) { return XUserAddAsync( XUserAddOptions::None, Block ); }, []( XAsyncBlock* Block ) { FGDKUserHandle User; return XUserAddResult(Block, User.GetInitReference()); } );
- L193 _prototype_ `FGDKTask LaunchGDKTask( const TCHAR* DebugName, TUniqueFunction<HRESULT(XAsyncBlock*)> InitFunction, TUniqueFunction<HRESULT(XAsyncBlock*)> ResultFunction, UE::Tasks::ETaskPriority Priority = UE::Tasks::ETaskPriority::Normal );` — launches a gdk task for asynchronous execution returns a trivially relocatable instance that can be used to wait for task completion or to obtain task execution result
- L199 _prototype_ `FGDKTask LaunchGDKTask( const TCHAR* DebugName, class FGDKAsyncTaskMonitor& OutAsyncTaskMonitor, TUniqueFunction<HRESULT(XAsyncBlock*)> InitFunction, TUniqueFunction<HRESULT(XAsyncBlock*)> ResultFunction, UE::Tasks::ETaskPriority Priority = UE::Tasks::ETaskPriority::Normal );`

### `Source/Runtime/Microsoft/GDKRuntime/Public/GDKThreadCheck.h` (Public)


#### class `FGDKScopedNotTimeSensitive`  
`class FGDKScopedNotTimeSensitive`  
_L20-33_
- L24 _public prototype_ `FGDKScopedNotTimeSensitive();`
- L25 _public prototype_ `~FGDKScopedNotTimeSensitive();`
- L32 _private member_ `bool bWasTimeSensitive;`
- L60 _function_ `inline FGDKScopedNotTimeSensitive::FGDKScopedNotTimeSensitive()`
- L66 _function_ `inline FGDKScopedNotTimeSensitive::~FGDKScopedNotTimeSensitive()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define WITH_GDK_THREAD_CHECK (!UE_BUILD_SHIPPING && !UE_BUILD_TEST && !ENABLE_PGO_PROFILE && WITH_GRDK)`
- L14 _macro_ `#define WITH_GDK_THREAD_CHECK_ALWAYS 0`
- L36 _macro_ `#define GDK_SCOPE_NOT_TIME_SENSITIVE() FGDKScopedNotTimeSensitive ANONYMOUS_VARIABLE( GDKNotTimeSenstitive )` — temporarily disables the time sensitive thread check in the current scope
- L40 _prototype_ `extern bool IsGDKTimeSensitiveThreadCheckEnabled();` — runtime check if time sensitive thread checking should be enabled
- L45 _macro_ `#define GDK_SCOPE_NOT_TIME_SENSITIVE()` — no-op
