# Plugins / NetworkServiceDiscovery

- module root: `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery`
- headers: 8; symbols: 172
- symbol kinds: class=7, delegate=6, function=13, macro=1, member=55, prototype=88, struct=2
- PrivateDependencyModuleNames: CoreUObject, Engine, Launch
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery/Private/Android/NetworkServiceDiscoveryAndroid.h` (Private)


#### class `FNetworkServiceDiscoveryAndroid`  
`class FNetworkServiceDiscoveryAndroid : public INetworkServiceDiscoveryPlatform`  
_L14-67_
- inherits: `INetworkServiceDiscoveryPlatform`
- desc: Android implementation of network service discovery using NsdManager via JNI.
- L17 _public prototype_ `FNetworkServiceDiscoveryAndroid();`
- L18 _public prototype_ `virtual ~FNetworkServiceDiscoveryAndroid();`
- L21 _public prototype_ `FNetworkServiceDiscoveryAndroid(const FNetworkServiceDiscoveryAndroid&) = delete;` — Non-copyable — JNI global refs are owned exclusively
- L22 _public prototype_ `FNetworkServiceDiscoveryAndroid& operator=(const FNetworkServiceDiscoveryAndroid&) = delete;`
- L25 _public prototype_ `virtual bool RegisterService(const FString& ServiceName, const FString& ServiceType, int32 Port, const TMap<FString, FString>& TxtRecord) override;` — Registration
- L26 _public prototype_ `virtual void UnregisterService(const FString& ServiceName) override;`
- L27 _public prototype_ `virtual bool IsServiceRegistered(const FString& ServiceName) const override;`
- L30 _public prototype_ `virtual bool StartDiscovery(const FString& ServiceType) override;` — Discovery
- L31 _public prototype_ `virtual void StopDiscovery() override;`
- L32 _public prototype_ `virtual bool IsDiscovering() const override;`
- L33 _public prototype_ `virtual void ResolveService(const FNetworkServiceInfo& Service) override;`
- L34 _public prototype_ `virtual TArray<FNetworkServiceInfo> GetDiscoveredServices() const override;`
- L37 _public prototype_ `void HandleServiceFound(const FString& ServiceName, const FString& ServiceType);` — Called from JNI callbacks (on game thread)
- L38 _public prototype_ `void HandleServiceLost(const FString& ServiceName, const FString& ServiceType);`
- L39 _public prototype_ `void HandleServiceResolved(const FNetworkServiceInfo& Service);`
- L40 _public prototype_ `void HandleServiceRegistered(const FString& ServiceName, const FString& ServiceType, int32 Port);`
- L41 _public prototype_ `void HandleError(const FString& ErrorMessage);`
- L44 _public function_ `static FNetworkServiceDiscoveryAndroid* GetInstance()` — Singleton accessor for JNI callbacks
- L47 _private prototype_ `bool InitJNI();`
- L50 _private member_ `jclass HelperClass = nullptr;` — JNI references — all default-initialized to null for safety on partial InitJNI failure
- L51 _private member_ `jobject HelperInstance = nullptr;`
- L52 _private member_ `jmethodID RegisterServiceMethod = nullptr;`
- L53 _private member_ `jmethodID UnregisterServiceMethod = nullptr;`
- L54 _private member_ `jmethodID StartDiscoveryMethod = nullptr;`
- L55 _private member_ `jmethodID StopDiscoveryMethod = nullptr;`
- L56 _private member_ `jmethodID ResolveServiceMethod = nullptr;`
- L57 _private member_ `jmethodID IsServiceRegisteredMethod = nullptr;`
- L58 _private member_ `jmethodID IsDiscoveringMethod = nullptr;`
- L60 _private member_ `bool bJNIInitialized = false;`
- L63 _private member_ `mutable FCriticalSection ServicesLock;` — Currently discovered services
- L64 _private member_ `TArray<FNetworkServiceInfo> DiscoveredServices;`
- L66 _private member_ `static FNetworkServiceDiscoveryAndroid* Instance;`

### `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery/Private/Apple/NetworkServiceDiscoveryApple.h` (Private)


#### class `FNetworkServiceDiscoveryApple`  
`class FNetworkServiceDiscoveryApple : public INetworkServiceDiscoveryPlatform`  
_L14-51_
- inherits: `INetworkServiceDiscoveryPlatform`
- desc: Apple implementation of network service discovery using NSNetServiceBrowser / NSNetService. Works on both iOS and macOS.
- L17 _public prototype_ `FNetworkServiceDiscoveryApple();`
- L18 _public prototype_ `virtual ~FNetworkServiceDiscoveryApple();`
- L21 _public prototype_ `virtual bool RegisterService(const FString& ServiceName, const FString& ServiceType, int32 Port, const TMap<FString, FString>& TxtRecord) override;` — Registration
- L22 _public prototype_ `virtual void UnregisterService(const FString& ServiceName) override;`
- L23 _public prototype_ `virtual bool IsServiceRegistered(const FString& ServiceName) const override;`
- L26 _public prototype_ `virtual bool StartDiscovery(const FString& ServiceType) override;` — Discovery
- L27 _public prototype_ `virtual void StopDiscovery() override;`
- L28 _public prototype_ `virtual bool IsDiscovering() const override;`
- L29 _public prototype_ `virtual void ResolveService(const FNetworkServiceInfo& Service) override;`
- L30 _public prototype_ `virtual TArray<FNetworkServiceInfo> GetDiscoveredServices() const override;`
- L33 _public prototype_ `void HandleServiceFound(const FNetworkServiceInfo& Service);` — Called from Objective-C delegates
- L34 _public prototype_ `void HandleServiceLost(const FNetworkServiceInfo& Service);`
- L35 _public prototype_ `void HandleServiceResolved(const FNetworkServiceInfo& Service);`
- L36 _public prototype_ `void HandleServiceRegistered(const FNetworkServiceInfo& Service);`
- L37 _public prototype_ `void HandleError(const FString& ErrorMessage);`
- L41 _private member_ `FNSDServiceBrowserDelegate* BrowserDelegate;` — Objective-C delegate for NSNetServiceBrowser callbacks
- L44 _private member_ `TMap<FString, FNSDServiceDelegate*> PublishDelegates;` — Published services keyed by service name
- L47 _private member_ `mutable FCriticalSection ServicesLock;` — Currently discovered services
- L48 _private member_ `TArray<FNetworkServiceInfo> DiscoveredServices;`
- L50 _private member_ `bool bIsDiscovering;`

### `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery/Private/INetworkServiceDiscoveryPlatform.h` (Private)


#### class `INetworkServiceDiscoveryPlatform`  
`class INetworkServiceDiscoveryPlatform`  
_L11-34_
- desc: Internal platform abstraction for network service discovery. Each platform provides a concrete implementation of this interface.
- L14 _public prototype_ `virtual ~INetworkServiceDiscoveryPlatform() = default;`
- L17 _public prototype_ `virtual bool RegisterService(const FString& ServiceName, const FString& ServiceType, int32 Port, const TMap<FString, FString>& TxtRecord) = 0;` — --- Registration ---
- L18 _public prototype_ `virtual void UnregisterService(const FString& ServiceName) = 0;`
- L19 _public prototype_ `virtual bool IsServiceRegistered(const FString& ServiceName) const = 0;`
- L22 _public prototype_ `virtual bool StartDiscovery(const FString& ServiceType) = 0;` — --- Discovery ---
- L23 _public prototype_ `virtual void StopDiscovery() = 0;`
- L24 _public prototype_ `virtual bool IsDiscovering() const = 0;`
- L25 _public prototype_ `virtual void ResolveService(const FNetworkServiceInfo& Service) = 0;`
- L26 _public prototype_ `virtual TArray<FNetworkServiceInfo> GetDiscoveredServices() const = 0;`
- L29 _public member_ `FOnServiceFound OnServiceFoundDelegate;` — --- Delegates ---
- L30 _public member_ `FOnServiceLost OnServiceLostDelegate;`
- L31 _public member_ `FOnServiceResolved OnServiceResolvedDelegate;`
- L32 _public member_ `FOnServiceRegistered OnServiceRegisteredDelegate;`
- L33 _public member_ `FOnDiscoveryError OnDiscoveryErrorDelegate;`

### `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery/Private/NetworkServiceDiscoveryModule.h` (Private)


#### class `FNetworkServiceDiscoveryModule`  
`class FNetworkServiceDiscoveryModule : public INetworkServiceDiscoveryModule`  
_L11-45_
- inherits: `INetworkServiceDiscoveryModule`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `virtual bool RegisterService(const FString& ServiceName, const FString& ServiceType, int32 Port, const TMap<FString, FString>& TxtRecord) override;` — INetworkServiceDiscoveryModule - Registration
- L21 _public prototype_ `virtual void UnregisterService(const FString& ServiceName = FString()) override;`
- L22 _public prototype_ `virtual bool IsServiceRegistered(const FString& ServiceName = FString()) const override;`
- L25 _public prototype_ `virtual bool StartDiscovery(const FString& ServiceType) override;` — INetworkServiceDiscoveryModule - Discovery
- L26 _public prototype_ `virtual void StopDiscovery() override;`
- L27 _public prototype_ `virtual bool IsDiscovering() const override;`
- L28 _public prototype_ `virtual void ResolveService(const FNetworkServiceInfo& Service) override;`
- L29 _public prototype_ `virtual TArray<FNetworkServiceInfo> GetDiscoveredServices() const override;`
- L32 _public prototype_ `virtual FOnServiceFound& OnServiceFound() override;` — INetworkServiceDiscoveryModule - Delegates
- L33 _public prototype_ `virtual FOnServiceLost& OnServiceLost() override;`
- L34 _public prototype_ `virtual FOnServiceResolved& OnServiceResolved() override;`
- L35 _public prototype_ `virtual FOnServiceRegistered& OnServiceRegistered() override;`
- L36 _public prototype_ `virtual FOnDiscoveryError& OnDiscoveryError() override;`
- L41 _private member_ `TUniquePtr<INetworkServiceDiscoveryPlatform> PlatformImpl;` — Platform-specific implementation
- L44 _private prototype_ `static TUniquePtr<INetworkServiceDiscoveryPlatform> CreatePlatformImpl();` — Create the appropriate platform implementation

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkServiceDiscovery, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNetworkServiceDiscovery, Log, All);`

### `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery/Private/Null/NetworkServiceDiscoveryNull.h` (Private)


#### class `FNetworkServiceDiscoveryNull`  
`class FNetworkServiceDiscoveryNull : public INetworkServiceDiscoveryPlatform`  
_L12-57_
- inherits: `INetworkServiceDiscoveryPlatform`
- desc: Null (no-op) implementation for unsupported platforms. All operations log a warning and return failure.
- L16 _public function_ `virtual bool RegisterService(const FString& ServiceName, const FString& ServiceType, int32 Port, const TMap<FString, FString>& TxtRecord) override`
- L22 _public function_ `virtual void UnregisterService(const FString& ServiceName) override`
- L24 _public function_ `virtual bool IsServiceRegistered(const FString& ServiceName) const override`
- L26 _public function_ `virtual bool StartDiscovery(const FString& ServiceType) override`
- L32 _public function_ `virtual void StopDiscovery() override`
- L34 _public function_ `virtual bool IsDiscovering() const override`
- L36 _public function_ `virtual void ResolveService(const FNetworkServiceInfo& Service) override`
- L41 _public function_ `virtual TArray<FNetworkServiceInfo> GetDiscoveredServices() const override`
- L48 _private function_ `void LogUnsupported()`

### `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery/Private/Windows/NetworkServiceDiscoveryWindows.h` (Private)


#### class `FNetworkServiceDiscoveryWindows`  
`class FNetworkServiceDiscoveryWindows : public INetworkServiceDiscoveryPlatform`  
_L23-100_
- inherits: `INetworkServiceDiscoveryPlatform`
- desc: Windows implementation of network service discovery using native DNS-SD APIs from windns.h / dnsapi.dll (Windows 10 1803+). dnsapi.dll is loaded dynamically at runtime to avoid hard link-time dependencies and allow graceful fallback on older Windows versions. NOTE: Windows DnsServiceBrowse does not provide service removal notifications. We work around this with periodic re-browsing: each browse cycle collects the current set of services and diffs against the previous set to detect removals.
- L26 _public prototype_ `FNetworkServiceDiscoveryWindows();`
- L27 _public prototype_ `virtual ~FNetworkServiceDiscoveryWindows();`
- L30 _public member_ `TSharedRef<TAtomic<bool>> bIsAlive = MakeShared<TAtomic<bool>>(true);` — Shared flag used by async callbacks to detect if this object is still alive
- L33 _public prototype_ `static bool LoadDnsApi();` — Try to load dnsapi.dll and resolve all required function pointers. Returns true on success.
- L36 _public member_ `static bool bDnsApiLoaded;` — Whether dnsapi.dll was loaded successfully. All operations are no-ops if false.
- L39 _public prototype_ `virtual bool RegisterService(const FString& ServiceName, const FString& ServiceType, int32 Port, const TMap<FString, FString>& TxtRecord) override;` — Registration
- L40 _public prototype_ `virtual void UnregisterService(const FString& ServiceName) override;`
- L41 _public prototype_ `virtual bool IsServiceRegistered(const FString& ServiceName) const override;`
- L44 _public prototype_ `virtual bool StartDiscovery(const FString& ServiceType) override;` — Discovery
- L45 _public prototype_ `virtual void StopDiscovery() override;`
- L46 _public prototype_ `virtual bool IsDiscovering() const override;`
- L47 _public prototype_ `virtual void ResolveService(const FNetworkServiceInfo& Service) override;`
- L48 _public prototype_ `virtual TArray<FNetworkServiceInfo> GetDiscoveredServices() const override;`
- L69 _public member_ `TMap<FString, TArray<FRegistration>> Registrations;` — Active registrations keyed by service name. One service name produces N entries (one per LAN-publishable network interface), each bound to its own adapter, so multi-NIC hosts can be reached from any segment they're attached to.
- L75 _private member_ `uint64 RegistrationGeneration = 0;` — Monotonic counter - incremented per FRegistration created (every per-adapter entry gets its own unique Generation) so callbacks can identify the exact entry they belong to, and stale callbacks for cancelled/replaced registrations are dropped.
- L78 _private member_ `void* BrowseCancelHandle = nullptr;` — Browse state
- L79 _private member_ `TSharedPtr<FBrowseContext> BrowseCallbackContext;` — Ref-counted; shared with async browse callback
- L80 _private member_ `bool bIsDiscovering = false;`
- L81 _private member_ `FString BrowseServiceType;`
- L82 _private member_ `FString BrowseQueryName;` — Kept alive for async DnsServiceBrowse
- L85 _private member_ `FTSTicker::FDelegateHandle ReBrowseTickerHandle;` — Periodic re-browse ticker for detecting service removals
- L86 _private prototype_ `bool OnReBrowseTick(float DeltaTime);`
- L90 _public member_ `mutable FCriticalSection ServicesLock;` — Public for file-static callback access
- L91 _public member_ `TArray<FNetworkServiceInfo> DiscoveredServices;`
- L95 _public member_ `TSet<FString> CurrentBrowseCycleServices;` — Double-buffered service sets for removal detection. BrowseCallback populates CurrentBrowseCycleServices. OnReBrowseTick swaps current→previous, then diffs previous against the new current.
- L96 _public member_ `TSet<FString> PreviousBrowseCycleServices;`
- L97 _public member_ `bool bFirstBrowseCycleComplete = false;`
- L98 _public member_ `mutable FCriticalSection ResolveLock;`
- L99 _public member_ `TArray<void*> PendingResolveCancels;`

#### struct `FNetworkServiceDiscoveryWindows::FRegistration`  
`struct FRegistration`  
_L55-64_
- desc: Per-registration state — public for file-static callback access. Tracks both the original instance (for cancelling pending registrations) and the actual instance from the callback (for deregistering active registrations whose name may have been changed by mDNS conflict resolution).
- L57 _public member_ `void* OriginalInstance = nullptr;` — DNS_SERVICE_INSTANCE* we constructed (for pending cancel)
- L58 _public member_ `void* ActualInstance = nullptr;` — DNS_SERVICE_INSTANCE* from callback (for active deregister)
- L59 _public member_ `void* CancelHandle = nullptr;` — DNS_SERVICE_CANCEL*
- L60 _public member_ `uint64 Generation = 0;` — Unique per-entry id - one service name can have multiple entries (one per
- L63 _public member_ `uint32 InterfaceIndex = 0;` — adapter address), so InterfaceIndex alone does not identify a single registration. Also used to drop stale callbacks (zeroed on cancel).

### `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery/Public/INetworkServiceDiscovery.h` (Public)


#### class `INetworkServiceDiscoveryModule`  
`class INetworkServiceDiscoveryModule : public IModuleInterface`  
_L23-108_
- inherits: `IModuleInterface`
- desc: Module interface for cross-platform mDNS/DNS-SD service discovery. Supports two primary operations: 1. Service Registration (host side) - Advertise a service on the local network 2. Service Discovery (client side) - Browse for and resolve services on the local network Platform implementations: - Apple (iOS/Mac): NSNetServiceBrowser / NSNetService - Android: NsdManager - Windows: Native DNS-SD via windns.h / dnsapi.dll (Windows 10 1803+)
- L27 _public function_ `static INetworkServiceDiscoveryModule* Get()`
- L56 _public prototype_ `virtual void UnregisterService(const FString& ServiceName = FString()) = 0;` — Unregister (stop advertising) a previously registered service. @param ServiceName   Name of the service to unregister. If empty, unregisters all services.
- L59 _public prototype_ `virtual bool IsServiceRegistered(const FString& ServiceName = FString()) const = 0;` — Returns true if the named service (or any service, if empty) is currently registered.
- L71 _public prototype_ `virtual bool StartDiscovery(const FString& ServiceType) = 0;` — Start browsing for services of the given type on the local network. @param ServiceType   DNS-SD service type to browse for, e.g. "_unrealremote._tcp." @return true if browsing was started successfully
- L74 _public prototype_ `virtual void StopDiscovery() = 0;` — Stop browsing for services.
- L77 _public prototype_ `virtual bool IsDiscovering() const = 0;` — Returns true if currently browsing for services.
- L85 _public prototype_ `virtual void ResolveService(const FNetworkServiceInfo& Service) = 0;` — Resolve a discovered service to obtain its IP address and port. Result delivered via OnServiceResolved delegate. @param Service   The service to resolve (as received from OnServiceFound)
- L88 _public prototype_ `virtual TArray<FNetworkServiceInfo> GetDiscoveredServices() const = 0;` — Get a snapshot of all currently discovered services.
- L94 _public prototype_ `virtual FOnServiceFound& OnServiceFound() = 0;`
- L95 _public prototype_ `virtual FOnServiceLost& OnServiceLost() = 0;`
- L96 _public prototype_ `virtual FOnServiceResolved& OnServiceResolved() = 0;`
- L105 _public prototype_ `virtual FOnServiceRegistered& OnServiceRegistered() = 0;` — Fires once for each successful registration. On platforms that publish the service per network interface (e.g. Windows multi-NIC hosts) this may fire multiple times for a single RegisterService call - once per interface, with FNetworkServiceInfo::InterfaceName / InterfaceIndex identifying which interface the broadcast is for so consumers can disambiguate. FNetworkServiceInfo::Address is NOT populated on register broadcasts (an interface may carry multiple addresses; the address is an implementation detail of the publication).
- L107 _public prototype_ `virtual FOnDiscoveryError& OnDiscoveryError() = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NETWORKSERVICEDISCOVERY_API`

### `Plugins/Experimental/NetworkServiceDiscovery/Source/NetworkServiceDiscovery/Public/NetworkServiceDiscoveryTypes.h` (Public)


#### struct `FNetworkServiceInfo`  
`struct FNetworkServiceInfo`  
_L10-54_
- desc: Represents a network service discovered or registered via mDNS/DNS-SD.
- L13 _public member_ `FString ServiceName;` — Human-readable service name, e.g. "MyProject on DESKTOP-ABC"
- L16 _public member_ `FString ServiceType;` — DNS-SD service type, e.g. "_unrealremote._tcp."
- L19 _public member_ `FString HostName;` — Resolved hostname of the service provider
- L22 _public member_ `FString Address;` — Resolved IP address (IPv4 or IPv6 string, e.g. "192.168.1.100" or "2001:db8::1")
- L25 _public member_ `int32 Port = 0;` — Resolved port number
- L28 _public member_ `TMap<FString, FString> TxtRecord;` — TXT record key-value pairs carrying service metadata
- L31 _public member_ `bool bIsResolved = false;` — Whether this service has been resolved (Address and Port are valid)
- L37 _public member_ `FString InterfaceName;` — Human-readable description of the network interface this broadcast is for. Set on OnServiceRegistered broadcasts on platforms that publish per network interface (Windows). Empty on browse-side broadcasts and on platforms whose NSD APIs don't surface per-interface info (Android, Apple).
- L43 _public member_ `uint32 InterfaceIndex = 0;` — Adapter index (Windows IfIndex / Unix ifindex) the registration is bound to. Set on OnServiceRegistered broadcasts on platforms that publish per network interface (Windows). Zero on browse-side broadcasts and on platforms that don't surface a per-interface registration.
- L45 _public function_ `bool operator==(const FNetworkServiceInfo& Other) const`

#### Free symbols / members of external scopes

- L50 _function_ `friend uint32 GetTypeHash(const FNetworkServiceInfo& Info)`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceFound, const FNetworkServiceInfo& );` — Fired when a new service is found during discovery (not yet resolved).
- L57 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceFound, const FNetworkServiceInfo& );` — Fired when a new service is found during discovery (not yet resolved).
- L60 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceLost, const FNetworkServiceInfo& );` — Fired when a previously discovered service is no longer available.
- L60 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceLost, const FNetworkServiceInfo& );` — Fired when a previously discovered service is no longer available.
- L63 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceResolved, const FNetworkServiceInfo& );` — Fired when a discovered service has been resolved to an address and port.
- L63 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceResolved, const FNetworkServiceInfo& );` — Fired when a discovered service has been resolved to an address and port.
- L66 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceRegistered, const FNetworkServiceInfo& );` — Fired when a service has been successfully registered/advertised.
- L66 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnServiceRegistered, const FNetworkServiceInfo& );` — Fired when a service has been successfully registered/advertised.
- L69 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDiscoveryError, const FString& );` — Fired when a discovery or registration error occurs.
- L69 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDiscoveryError, const FString& );` — Fired when a discovery or registration error occurs.
