# Plugins / PlatformDLC

- module root: `Plugins/Experimental/PlatformDLC/Source/PlatformDLC`
- headers: 3; symbols: 83
- symbol kinds: class=5, delegate=1, enum=3, enumerator=15, function=19, macro=1, member=5, prototype=34
- PrivateDependencyModuleNames: Core

### `Plugins/Experimental/PlatformDLC/Source/PlatformDLC/Private/PlatformDLCPlatformFile.h` (Private)


#### class `IPlatformDLCPlatformFile`  
`class IPlatformDLCPlatformFile : public IPlatformFile`  
_L8-19_
- inherits: `IPlatformFile`
- L11 _public prototype_ `static TUniquePtr<IPlatformDLCPlatformFile> Construct();`
- L13 _public prototype_ `virtual ~IPlatformDLCPlatformFile() = default;`
- L16 _public prototype_ `virtual void AddMountPoint( FName DLCName, const FString& MountPoint ) = 0;` — IPlatformDLCPlatformFile interface
- L17 _public prototype_ `virtual void RemoveMountPoint( FName DLCName ) = 0;`
- L18 _public prototype_ `virtual bool HasMountPoints() const = 0;`

### `Plugins/Experimental/PlatformDLC/Source/PlatformDLC/Public/PlatformDLC.h` (Public)


#### class `IPlatformDLC`  
`class IPlatformDLC`  
_L14-112_
- desc: main interface for Platform DLC note: API may be subject to change while this plugin is experimental
- L17 _public prototype_ `virtual ~IPlatformDLC() = default;`
- L41 _public prototype_ `virtual bool InitializeAsync() = 0;` — start initializing the platform DLC; subsequent calls after the first are ignored; returns true if initialization was started
- L44 _public prototype_ `virtual void RegisterInitializationCallback(TFunction<void()> Callback) = 0;` — register a callback for when initialization is complete; the callback will still occur if the DLC is already initialized
- L47 _public prototype_ `virtual void Shutdown() = 0;` — shutdown the platform DLC and clean up resources
- L50 _public prototype_ `virtual bool IsInitialized() const = 0;` — determines whether the platform DLC has finished initializing
- L55 _public prototype_ `virtual bool IsAvailable() = 0;` — returns true if DLC is supported in the current build configuration. Some platforms may only support DLC based on how its run (e.g., packaged builds) or it may be preferred in development to disable DLC.
- L59 _public prototype_ `virtual bool HasEntitlement( FName DLCName ) const = 0;` — query if we have entitlement to download & mount the given DLC
- L62 _public prototype_ `virtual EState GetState( FName DLCName ) const = 0;` — returns the current state of the given DLC
- L65 _public prototype_ `virtual FOnDLCNotification& OnNotification() = 0;` — called when there is a notification about DLC, such as mounting completion
- L71 _public prototype_ `virtual bool Mount( FName DLCName ) = 0;` — start asynchronously mounting the given DLC can also be used to attempt entitlement reacquisition after it has been lost returns true if the callback will be triggered, or false if the DLC is not known
- L75 _public prototype_ `virtual bool Unmount( FName DLCName ) = 0;` — start asynchronously unmounting the given DLC. It is essential that the game is no longer using the DLC returns true if the callback will be triggered, or false if the DLC is not known
- L79 _public prototype_ `virtual bool Download( FName DLCName ) = 0;` — start asynchronously downloading the given DLC. Depending on the platform you may reacquire entitlements before you can download. returns true if the callback will be triggered, or false if the DLC is not known
- L83 _public prototype_ `virtual bool Uninstall( FName DLCName ) = 0;` — start uninstalling the given DLC (may not work properly on all platforms. DLC must be unmounted first) returns true if the callback will be triggered, or false if the DLC is not known
- L88 _public prototype_ `virtual bool GetDownloadSize( FName DLCName, uint64& OutCurrentInstallSize, uint64& OutFullInstallSize ) const = 0;` — determine the download size for the given DLC returns true if the download size is available
- L91 _public prototype_ `virtual FString GetRootDirectory( FName DLCName ) const = 0;` — returns the file system mount point for the given DLC
- L94 _public prototype_ `virtual TArray<FName> GetAllDLCNames() const = 0;` — returns the list of all known DLC (regardless of whether downloaded / mounted)
- L97 _public prototype_ `virtual TArray<FName> GetMountedDLCNames() const = 0;` — returns the list of all DLC that is ready for use (entitled, downloaded & mounted)
- L100 _public prototype_ `virtual FString GetStoreId( FName DLCName ) const = 0;` — get the store id for the DLC (should be convertible to FUniqueOfferId)
- L103 _public prototype_ `virtual void SetStoreUser( FPlatformUserId PlatformUserId ) = 0;` — set the user who will be used to purchase any DLC
- L106 _public prototype_ `virtual FPlatformUserId GetStoreUser() const = 0;` — returns the user who will be used to purchase any DLC, if any
- L111 _public member_ `static const TCHAR* ConfigSectionName;` — config section for Platform DLC settings

#### enum `IPlatformDLC::ENotification`  
`enum class ENotification`  
_L19-26_
- L21 _public enumerator_ `Entitlement` — true = entitlement gained, false = lost
- L22 _public enumerator_ `Mounted` — whether the DLC has been successfully mounted and can now be used
- L23 _public enumerator_ `Unmounted` — whether the DLC has been successfully unmounted
- L24 _public enumerator_ `Downloaded` — whether the DLC has been successfully downloaded and can now be mounted (note if AutoMount is configured, this will happen automatically)
- L25 _public enumerator_ `Uninstalled` — whether the DLC has been successfully uninstalled

#### enum `IPlatformDLC::EState`  
`enum class EState : uint8`  
_L29-38_
- L31 _public enumerator_ `NotInstalled`
- L32 _public enumerator_ `Downloading`
- L33 _public enumerator_ `Downloaded`
- L34 _public enumerator_ `Mounting`
- L35 _public enumerator_ `Mounted`
- L36 _public enumerator_ `Unmounting`
- L37 _public enumerator_ `Uninstalling`

#### class `IPlatformDLCFactoryModule`  
`class IPlatformDLCFactoryModule : public IModuleInterface`  
_L116-121_
- inherits: `IModuleInterface`
- desc: interface for a platform DLC factory
- L120 _public prototype_ `virtual TSharedPtr<IPlatformDLC> GetPlatformDLC() = 0;` — get the platform DLC for this factory

#### class `FGenericPlatformDLC`  
`class FGenericPlatformDLC : public IPlatformDLC`  
_L125-237_
- inherits: `IPlatformDLC`
- desc: generic platform DLC implementation - typical base class for platform specializations
- L128 _public prototype_ `virtual bool InitializeAsync() override final;`
- L129 _public prototype_ `virtual void RegisterInitializationCallback(TFunction<void()> Callback) override final;`
- L130 _public prototype_ `virtual void Shutdown() override;`
- L132 _public function_ `virtual bool IsInitialized() const override`
- L137 _public function_ `virtual bool IsAvailable() override`
- L142 _public function_ `virtual bool HasEntitlement( FName DLCName ) const override`
- L147 _public function_ `virtual EState GetState( FName DLCName ) const override`
- L152 _public function_ `virtual FOnDLCNotification& OnNotification() override`
- L157 _public function_ `virtual bool Mount( FName DLCName ) override`
- L162 _public function_ `virtual bool Unmount( FName DLCName ) override`
- L167 _public function_ `virtual bool Download( FName DLCName ) override`
- L172 _public function_ `virtual bool Uninstall( FName DLCName ) override`
- L177 _public function_ `virtual bool GetDownloadSize( FName DLCName, uint64& OutCurrentInstallSize, uint64& OutFullInstallSize ) const override`
- L182 _public function_ `virtual FString GetRootDirectory( FName DLCName ) const override`
- L187 _public function_ `virtual TArray<FName> GetAllDLCNames() const override`
- L192 _public function_ `virtual TArray<FName> GetMountedDLCNames() const override`
- L197 _public function_ `virtual FString GetStoreId( FName DLCName ) const override`
- L202 _public function_ `virtual void SetStoreUser( FPlatformUserId PlatformUserId ) override`
- L206 _public function_ `virtual FPlatformUserId GetStoreUser() const override`
- L213 _protected function_ `virtual void BeginInitializeInternal()` — override to perform platform-specific initialization on any thread and call EndInitializeInternal() when finished
- L215 _protected prototype_ `void EndInitializeInternal();`
- L217 _protected function_ `bool IsInitializing() const`
- L222 _protected prototype_ `void PostNotification( FName DLCName, ENotification Notification, bool bSuccess );`
- L232 _private member_ `mutable FCriticalSection InitLock;`
- L233 _private member_ `TArray<TFunction<void()>> PendingInitCallbacks;`
- L234 _private member_ `std::atomic<EInitState> InitState{ EInitState::NotStarted };`
- L236 _private member_ `FOnDLCNotification NotificationDelegate;`

#### enum `FGenericPlatformDLC::EInitState`  
`enum class EInitState : uint8`  
_L225-230_
- L227 _public enumerator_ `NotStarted`
- L228 _public enumerator_ `InProgress`
- L229 _public enumerator_ `Complete`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PLATFORMDLC_API`
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnDLCNotification, FName, ENotification, bool ) enum class EState : uint8 { NotInstalled, Downloading, Downloaded, Mounting, Mounted, Unmounting, Uninstalling, };`
- L241 _prototype_ `FString LexToString(IPlatformDLC::ENotification Notification);`
- L242 _prototype_ `FString LexToString(IPlatformDLC::EState State);`

### `Plugins/Experimental/PlatformDLC/Source/PlatformDLC/Public/PlatformDLCModule.h` (Public)


#### class `IPlatformDLCModule`  
`class IPlatformDLCModule : public IPlatformFileModule`  
_L14-31_
- inherits: `IPlatformFileModule`
- L21 _public function_ `static inline IPlatformDLCModule& Get()` — Singleton-like access to the platform DLC module instance @return Returns IPlatformDLCModule singleton instance, loading the module on demand if needed
- L30 _public prototype_ `virtual TSharedPtr<IPlatformDLC> GetPlatformDLC() = 0;` — Returns the platform DLC, if any (configured via ini) @return platform DLC pointer, or null if it isn't available
