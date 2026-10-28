# Developer / TargetDeviceServices

- module root: `Source/Developer/TargetDeviceServices`
- headers: 11; symbols: 331
- symbol kinds: class=10, delegate=9, function=46, member=100, prototype=153, struct=10, typedef=3
- PrivateDependencyModuleNames: CoreUObject
- PrivateIncludePathModuleNames: Messaging, MessagingCommon
- PublicDependencyModuleNames: Core, DesktopPlatform, TargetPlatform

### `Source/Developer/TargetDeviceServices/Private/Proxies/TargetDeviceProxy.h` (Private)


#### class `FTargetDeviceProxy`  
`class FTargetDeviceProxy : public ITargetDeviceProxy`  
_L26-310_
- inherits: `ITargetDeviceProxy`
- desc: Implementation of the device proxy.
- L32 _public function_ `FTargetDeviceProxy()` — Default constructor.
- L39 _public prototype_ `FTargetDeviceProxy(const FString& InId);` — Creates and initializes a new instance. @param InId The identifier of the target device to create this proxy for.
- L49 _public prototype_ `FTargetDeviceProxy(const FString& InName, const FTargetDeviceServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, bool InIsAggregated);` — Creates and initializes a new instance. @param InId The identifier of the target device to create this proxy for. @param Message The message to initialize from. @param Context The message context. @param InIsAggregated Indicates if the proxy is of type "All Devices".
- L56 _public function_ `void AddTimeout(const FDateTime& NewTimeout)` — Add a time by which a ping response should arrive
- L67 _public function_ `bool HasTimedOut(const FDateTime& Now) const` — Check if ping response arrived on time
- L78 _public prototype_ `void UpdateFromMessage(const FTargetDeviceServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Updates the proxy's information from the given device service response and clear timeout expectations @param Message The message containing the response. @param Context The message context.
- L84 _public function_ `virtual const bool CanMultiLaunch() const override`
- L89 _public function_ `virtual bool CanPowerOff() const override`
- L94 _public function_ `virtual bool CanPowerOn() const override`
- L99 _public function_ `virtual bool CanReboot() const override`
- L104 _public function_ `virtual bool CanSupportVariants() const override`
- L109 _public prototype_ `virtual int32 GetNumVariants() const override;`
- L110 _public prototype_ `virtual int32 GetVariants(TArray<FName>& OutVariants) const override;`
- L111 _public prototype_ `virtual FName GetTargetDeviceVariant(const FString& InDeviceId) const override;`
- L112 _public prototype_ `const FString GetTargetDeviceId(FName InVariant) const override;`
- L113 _public prototype_ `virtual const TSet<FString>& GetTargetDeviceIds(FName InVariant) const override;`
- L114 _public prototype_ `virtual FString GetTargetPlatformName(FName InVariant) const override;`
- L115 _public prototype_ `virtual FName GetTargetPlatformId(FName InVariant) const override;`
- L116 _public prototype_ `virtual FName GetVanillaPlatformId(FName InVariant) const override;`
- L117 _public prototype_ `virtual FText GetPlatformDisplayName(FName InVariant) const override;`
- L119 _public function_ `virtual const FString& GetHostName() const override`
- L124 _public function_ `virtual const FString& GetHostUser() const override`
- L129 _public function_ `virtual const FString& GetMake() const override`
- L134 _public function_ `virtual const FString& GetModel() const override`
- L139 _public function_ `virtual const FString& GetName() const override`
- L144 _public function_ `virtual const FString& GetDeviceUser() const override`
- L149 _public function_ `virtual const FString& GetDeviceUserPassword() const override`
- L154 _public function_ `virtual const FString& GetType() const override`
- L159 _public function_ `virtual const FString& GetOSVersion() const override`
- L164 _public function_ `virtual FStringView GetArchitecture() const override`
- L169 _public function_ `virtual const FString& GetConnectionType() const override`
- L174 _public prototype_ `virtual bool HasDeviceId(const FString& InDeviceId) const override;`
- L175 _public prototype_ `virtual bool HasVariant(FName InVariant) const override;`
- L176 _public prototype_ `virtual bool HasTargetPlatform(FName InTargetPlatformId) const override;`
- L178 _public function_ `virtual bool IsConnected() const override`
- L183 _public function_ `virtual bool IsAuthorized() const override`
- L188 _public function_ `virtual bool IsShared() const override`
- L193 _public function_ `virtual bool IsSimulated() const override`
- L198 _public prototype_ `virtual bool TerminateLaunchedProcess(FName InVariant, const FString& ProcessIdentifier) override;`
- L200 _public prototype_ `virtual void PowerOff(bool Force) override;`
- L201 _public prototype_ `virtual void PowerOn() override;`
- L202 _public prototype_ `virtual void Reboot() override;`
- L205 _public function_ `virtual bool IsAggregated() const override` — Returns true if this is an aggregate (All_<platform>_devices_on_<host>) proxy, false otherwise
- L213 _protected prototype_ `void InitializeMessaging();` — Initializes the message endpoint.
- L218 _private member_ `bool Connected;` — Holds a flag indicating whether the device is connected.
- L221 _private member_ `bool Authorized;` — Holds a flag indicating whether the device is authorized
- L224 _private member_ `FString HostName;` — Holds the name of the computer that hosts the device.
- L227 _private member_ `FString HostUser;` — Holds the name of the user that owns the device.
- L230 _private member_ `TOptional<FDateTime> PingTimeout;` — The time by which the lack of any ping response is considered a timeout.
- L233 _private member_ `FString Make;` — Holds the device make.
- L236 _private member_ `FMessageAddress MessageAddress;` — Holds the remote device's message bus address.
- L239 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the local message bus endpoint.
- L242 _private member_ `FString Model;` — Holds the remote device's model.
- L245 _private member_ `FString Name;` — Holds the name of the device.
- L248 _private member_ `FString DeviceUser;` — Holds device user.
- L251 _private member_ `FString DeviceUserPassword;` — Holds device user password.
- L254 _private member_ `bool Shared;` — Holds a flag indicating whether the device is being shared with other users.
- L257 _private member_ `bool SupportsMultiLaunch;` — Holds a flag indicating whether the device supports multi-launch.
- L260 _private member_ `bool SupportsPowerOff;` — Holds a flag indicating whether the device can power off.
- L263 _private member_ `bool SupportsPowerOn;` — Holds a flag indicating whether the device can be power on.
- L266 _private member_ `bool SupportsReboot;` — Holds a flag indicating whether the device can reboot.
- L269 _private member_ `bool SupportsVariants;` — Holds a flag indicating whether the device's target platform supports variants.
- L272 _private member_ `FString Type;` — Holds the device type.
- L275 _private member_ `FString Architecture;` — Holds the remote device's architecture.
- L278 _private member_ `FString OSVersion;` — Holds the remote device's OS version.
- L281 _private member_ `FString ConnectionType;` — Holds the type of connection.
- L284 _private member_ `FName DefaultVariant;` — Holds default variant name.
- L288 _private member_ `bool Aggregated;` — Holds a flag indicating whether the proxy is of type "All Devices".
- L309 _private member_ `TMap<FName, FTargetDeviceProxyVariant> TargetDeviceVariants;` — Map of all the Variants for this Device.

#### class `FTargetDeviceProxy::FTargetDeviceProxyVariant`  
`class FTargetDeviceProxyVariant`  
_L291-306_
- desc: Holds data about a device proxy variant.
- L296 _public member_ `TSet<FString> DeviceIDs;` — Holds a list with the string versions of device ids.
- L299 _public member_ `FName VariantName;` — Holds the variant name, this is the the map key as well.
- L302 _public member_ `FString TargetPlatformName;` — Platform information.
- L303 _public member_ `FName TargetPlatformId;`
- L304 _public member_ `FName VanillaPlatformId;`
- L305 _public member_ `FText PlatformDisplayName;`

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef TSharedRef<class FTargetDeviceProxy> FTargetDeviceProxyRef;` — Type definition for shared references to instances of FTargetDeviceProxy.

### `Source/Developer/TargetDeviceServices/Private/Proxies/TargetDeviceProxyManager.h` (Private)


#### class `FTargetDeviceProxyManager`  
`class FTargetDeviceProxyManager : public ITargetDeviceProxyManager`  
_L24-109_
- inherits: `ITargetDeviceProxyManager`
- desc: Implements a class which locates devices based on criteria for use in the Launcher.
- L30 _public prototype_ `FTargetDeviceProxyManager();` — Default constructor.
- L33 _public prototype_ `virtual ~FTargetDeviceProxyManager();` — Virtual destructor.
- L39 _public prototype_ `virtual TSharedRef<ITargetDeviceProxy> FindOrAddProxy(const FString& Name) override;`
- L40 _public prototype_ `virtual TSharedPtr<ITargetDeviceProxy> FindProxy(const FString& Name) override;`
- L41 _public prototype_ `virtual TSharedPtr<ITargetDeviceProxy> FindProxyDeviceForTargetDevice(const FString& DeviceId) override;`
- L42 _public prototype_ `virtual void GetProxies(FName TargetPlatformName, bool IncludeUnshared, TArray<TSharedPtr<ITargetDeviceProxy>>& OutProxies) override;`
- L45 _public prototype_ `virtual void GetAllProxies(FName TargetPlatformName, TArray<TSharedPtr<ITargetDeviceProxy>>& OutProxies) override;` — the proxy list include aggregate (All_<platform>_devices_on_<host>) proxies
- L47 _public prototype_ `DECLARE_DERIVED_EVENT(FTargetDeviceProxyManager, ITargetDeviceProxyManager::FOnTargetDeviceProxyAdded, FOnTargetDeviceProxyAdded);`
- L48 _public function_ `virtual FOnTargetDeviceProxyAdded& OnProxyAdded() override`
- L53 _public prototype_ `DECLARE_DERIVED_EVENT(FTargetDeviceProxyManager, ITargetDeviceProxyManager::FOnTargetDeviceProxyRemoved, FOnTargetDeviceProxyRemoved);`
- L54 _public function_ `virtual FOnTargetDeviceProxyRemoved& OnProxyRemoved() override`
- L62 _protected prototype_ `void RemoveDeadProxies();` — Removes all target device proxies that timed out.
- L65 _protected prototype_ `void SendPing();` — Pings all target devices on the network.
- L70 _private prototype_ `void HandlePongMessage(const FTargetDeviceServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles FTargetDeviceServicePong messages.
- L73 _private prototype_ `void AddProxyFromPongMessage(const FTargetDeviceServicePong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context, bool InIsAggregated);` — Add or update the proxy from the FTargetDeviceServicePong message
- L76 _private prototype_ `bool HandleTicker(float DeltaTime);` — Handles ticks from the ticker.
- L87 _private prototype_ `void GetProxyList(FName TargetPlatformName, bool IncludeUnshared, bool bIncludeAggregate, TArray<TSharedPtr<ITargetDeviceProxy>>& OutProxies);` — Gets a filtered list of proxies created by the device discovery routine @param PlatformName The the name of the target platform to get proxies for (or empty string for all proxies). @param IncludeUnshared Will hold the list of devices found by the locator. @param IncludeAggregate Will include the "All devices" entries. @param OutProxies Will hold the list of devices found by the locator. @see FindOrAddProxy, FindProxy, FindProxyDeviceForTargetDevice
- L91 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint.
- L94 _private member_ `TMap<FString, TSharedPtr<FTargetDeviceProxy>> Proxies;` — Holds the collection of proxies.
- L99 _private member_ `FOnTargetDeviceProxyAdded ProxyAddedDelegate;` — Holds a delegate that is invoked when a target device proxy has been added.
- L102 _private member_ `FOnTargetDeviceProxyRemoved ProxyRemovedDelegate;` — Holds a delegate that is invoked when a target device proxy has been removed.
- L105 _private member_ `FTickerDelegate TickDelegate;` — Holds a delegate to be invoked when the widget ticks.
- L108 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;` — Handle to the registered TickDelegate.

#### Free symbols / members of external scopes

- L47 _delegate_ `DECLARE_DERIVED_EVENT(FTargetDeviceProxyManager, ITargetDeviceProxyManager::FOnTargetDeviceProxyAdded, FOnTargetDeviceProxyAdded);`
- L53 _delegate_ `DECLARE_DERIVED_EVENT(FTargetDeviceProxyManager, ITargetDeviceProxyManager::FOnTargetDeviceProxyRemoved, FOnTargetDeviceProxyRemoved);`

### `Source/Developer/TargetDeviceServices/Private/Services/TargetDeviceService.h` (Private)


#### class `FTargetDeviceService`  
`class FTargetDeviceService : public ITargetDeviceService`  
_L36-142_
- inherits: `ITargetDeviceService`
- desc: Implements remote services for a specific target device.
- L47 _public prototype_ `FTargetDeviceService(const FString& InDeviceName, const TSharedRef<IMessageBus, ESPMode::ThreadSafe>& InMessageBus);` — Creates and initializes a new instance. @param InDeviceName The name of the device to expose. @param InMessageBus The message bus to listen on for clients.
- L50 _public prototype_ `~FTargetDeviceService();` — Destructor.
- L56 _public prototype_ `virtual void AddTargetDevice(TSharedPtr<ITargetDevice, ESPMode::ThreadSafe> InDevice) override;`
- L57 _public prototype_ `virtual bool CanStart(FName InFlavor = NAME_None) const override;`
- L58 _public prototype_ `virtual const FString& GetClaimHost() override;`
- L59 _public prototype_ `virtual const FString& GetClaimUser() override;`
- L60 _public prototype_ `virtual ITargetDevicePtr GetDevice(FName InVariant = NAME_None) const override;`
- L61 _public prototype_ `virtual FString GetDeviceName() const override;`
- L62 _public prototype_ `virtual FName GetDevicePlatformName() const override;`
- L63 _public prototype_ `virtual FString GetDevicePlatformDisplayName() const override;`
- L64 _public prototype_ `virtual bool IsRunning() const override;`
- L65 _public prototype_ `virtual bool IsShared() const override;`
- L66 _public prototype_ `virtual int32 NumTargetDevices() override;`
- L67 _public prototype_ `virtual void RemoveTargetDevice(TSharedPtr<ITargetDevice, ESPMode::ThreadSafe> InDevice) override;`
- L68 _public prototype_ `virtual void SetShared(bool InShared) override;`
- L69 _public prototype_ `virtual bool Start() override;`
- L70 _public prototype_ `virtual void Stop() override;`
- L80 _protected prototype_ `bool StoreDeployedFile(FArchive* FileReader, const FString& TargetFileName) const;` — Stores the specified file to deploy. @param FileReader The archive reader providing access to the file data. @param TargetFileName The desired name of the file on the target device.
- L85 _private prototype_ `void HandleClaimDeniedMessage(const FTargetDeviceClaimDenied& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for FTargetDeviceClaimDenied messages.
- L88 _private prototype_ `void HandleClaimedMessage( const FTargetDeviceClaimed& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Callback for FTargetDeviceClaimDenied messages.
- L91 _private prototype_ `void HandleUnclaimedMessage(const FTargetDeviceUnclaimed& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for FTargetDeviceClaimDropped messages.
- L94 _private prototype_ `void HandleTerminateLaunchedProcessMessage(const FTargetDeviceServiceTerminateLaunchedProcess& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for FTargetDeviceServiceTerminateLaunchedProcess messages.
- L97 _private prototype_ `void HandlePingMessage(const FTargetDeviceServicePing& InMessage, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for FTargetDeviceServicePing messages.
- L100 _private prototype_ `void HandlePowerOffMessage(const FTargetDeviceServicePowerOff& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for FTargetDeviceServicePowerOff messages.
- L103 _private prototype_ `void HandlePowerOnMessage(const FTargetDeviceServicePowerOn& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for FTargetDeviceServicePowerOn messages.
- L106 _private prototype_ `void HandleRebootMessage(const FTargetDeviceServiceReboot& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Callback for FTargetDeviceServiceReboot messages.
- L111 _private member_ `TWeakPtr<ITargetDevice, ESPMode::ThreadSafe> DefaultDevicePtr;` — Default target device used when no flavor is specified.
- L114 _private member_ `FString DeviceName;` — Caches the name of the device name that this services exposes.
- L117 _private member_ `FName DevicePlatformName;` — Caches the platform name of the device name that this services exposes.
- L120 _private member_ `FString DevicePlatformDisplayName;` — Caches the platform name of the device name that this services exposes.
- L123 _private member_ `FString ClaimHost;` — Holds the name of the host that has a claim on the device.
- L126 _private member_ `FMessageAddress ClaimAddress;` — Holds the message address of the target device service that has a claim on the device.
- L129 _private member_ `FString ClaimUser;` — Holds the name of the user that has a claim on the device.
- L132 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint.
- L135 _private member_ `bool Running;` — Holds a flag indicating whether this service is currently running.
- L138 _private member_ `bool Shared;` — Holds a flag indicating whether the device is shared with other users.
- L141 _private member_ `TMap<FName, TWeakPtr<ITargetDevice, ESPMode::ThreadSafe>> TargetDevicePtrs;` — Map of all the Flavors for this Service

### `Source/Developer/TargetDeviceServices/Private/Services/TargetDeviceServiceManager.h` (Private)


#### class `FTargetDeviceServiceManager`  
`class FTargetDeviceServiceManager : public ITargetDeviceServiceManager`  
_L22-145_
- inherits: `ITargetDeviceServiceManager`
- desc: Implements a target device service manager. Services that were running at the
- L28 _public prototype_ `FTargetDeviceServiceManager();` — Default constructor.
- L31 _public prototype_ `~FTargetDeviceServiceManager();` — Destructor.
- L37 _public prototype_ `virtual bool AddStartupService(const FString& DeviceName) override;`
- L38 _public prototype_ `virtual int32 GetServices(TArray<TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe>>& OutServices) override;`
- L39 _public prototype_ `virtual void RemoveStartupService(const FString& DeviceName) override;`
- L41 _public prototype_ `DECLARE_DERIVED_EVENT(FTargetDeviceServiceManager, ITargetDeviceServiceManager::FOnTargetDeviceServiceAdded, FOnTargetDeviceServiceAdded);`
- L42 _public function_ `virtual FOnTargetDeviceServiceAdded& OnServiceAdded() override`
- L47 _public prototype_ `DECLARE_DERIVED_EVENT(FTargetDeviceServiceManager, ITargetDeviceServiceManager::FOnTargetDeviceServiceRemoved, FOnTargetDeviceServiceRemoved);`
- L48 _public function_ `virtual FOnTargetDeviceServiceRemoved& OnServiceRemoved() override`
- L61 _protected prototype_ `TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe> AddService(const FString& DeviceName);` — Adds a device service for the given device. @param DeviceName The name to of the device to add. @return the created or preexisting service, nullptr if creation failed.
- L69 _protected prototype_ `bool AddTargetDevice(ITargetDevicePtr InDevice);` — Adds a target device, a device service will be created if needed. @param InDevice The target device to add @return true if the device was added to the device service, false if the service failed to create.
- L76 _protected prototype_ `void InitializeTargetPlatforms();` — Initializes target platforms callbacks. @see ShutdownTargetPlatforms
- L83 _protected prototype_ `void LoadSettings();` — Loads all settings from disk. @see SaveSettings
- L90 _protected prototype_ `void RemoveService(const FString& DeviceName);` — Removes the device service for the given target device. @param DeviceName The name of the device to remove the service for.
- L97 _protected prototype_ `void RemoveTargetDevice(ITargetDevicePtr InDevice);` — Removes the given target device, if that is the last target device in the device service the entire service is removed. @param InDevice The target device to remove.
- L104 _protected prototype_ `void SaveSettings();` — Saves all settings to disk. @see LoadSettings
- L111 _protected prototype_ `void ShutdownTargetPlatforms();` — Shuts down target platforms callbacks. @see InitializeTargetPlatforms
- L116 _private prototype_ `void HandleMessageBusShutdown();` — Callback for handling message bus shutdowns.
- L119 _private prototype_ `void HandleTargetPlatformDeviceDiscovered(ITargetDeviceRef DiscoveredDevice);` — Callback for discovered target devices.
- L122 _private prototype_ `void HandleTargetPlatformDeviceLost(ITargetDeviceRef LostDevice);` — Callback for lost target devices.
- L127 _private member_ `FCriticalSection CriticalSection;` — Holds a critical section object.
- L130 _private member_ `TMap<FString, TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe>> DeviceServices;` — Holds the list of locally managed device services.
- L133 _private member_ `TWeakPtr<IMessageBus, ESPMode::ThreadSafe> MessageBusPtr;` — Holds a weak pointer to the message bus.
- L136 _private member_ `TMap<FString, bool> StartupServices;` — Holds the collection of identifiers for devices that start automatically (shared/unshared).
- L141 _private member_ `FOnTargetDeviceServiceAdded ServiceAddedDelegate;` — Holds a delegate that is invoked when a target device service was added.
- L144 _private member_ `FOnTargetDeviceServiceRemoved ServiceRemovedDelegate;` — Holds a delegate that is invoked when a target device service was removed.

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_DERIVED_EVENT(FTargetDeviceServiceManager, ITargetDeviceServiceManager::FOnTargetDeviceServiceAdded, FOnTargetDeviceServiceAdded);`
- L47 _delegate_ `DECLARE_DERIVED_EVENT(FTargetDeviceServiceManager, ITargetDeviceServiceManager::FOnTargetDeviceServiceRemoved, FOnTargetDeviceServiceRemoved);`

### `Source/Developer/TargetDeviceServices/Private/TargetDeviceServicesPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(TargetDeviceServicesLog, Log, All);` — Declares the module's log category.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(TargetDeviceServicesLog, Log, All);` — Declares the module's log category.

### `Source/Developer/TargetDeviceServices/Public/ITargetDeviceProxy.h` (Public)


#### class `ITargetDeviceProxy`  
`class ITargetDeviceProxy`  
_L19-305_
- desc: Interface for target device proxies.
- L28 _public prototype_ `virtual const bool CanMultiLaunch() const = 0;` — Checks whether the device can launch multiple games or applications simultaneously. @return true if launching multiple instances is supported, false otherwise.
- L35 _public prototype_ `virtual bool CanPowerOff() const = 0;` — Checks whether this device can be powered off remotely. @return true if the device can be powered off, false otherwise.
- L42 _public prototype_ `virtual bool CanPowerOn() const = 0;` — Checks whether this device can be powered on remotely. @return true if the device can be powered on, false otherwise.
- L49 _public prototype_ `virtual bool CanReboot() const = 0;` — Checks whether this device can be rebooted remotely. @return true if the device can be rebooted, false otherwise.
- L56 _public prototype_ `virtual bool CanSupportVariants() const = 0;` — Checks whether this device's target platform supports variants. @return true if the device's target platform supports variants, false otherwise.
- L63 _public prototype_ `virtual int32 GetNumVariants() const = 0;` — Gets the number of variants this device supports @return The number of variants supported.
- L71 _public prototype_ `virtual int32 GetVariants(TArray<FName>& OutVariants) const = 0;` — Gets the list of variants this device supports @param OutVariants This list will be populated with the unique variant names. @return The number of variants in the list.
- L79 _public prototype_ `virtual bool HasVariant(FName InVariant) const = 0;` — Checks whether this device proxy contains a variant @param InVariant Variant to check for. @return true is this variant is found.
- L87 _public prototype_ `virtual FName GetTargetDeviceVariant(const FString& InDeviceId) const = 0;` — Gets the variant name of the target device. @param InDeviceId target device id to get the variant for. @return The target device variant name.
- L95 _public prototype_ `virtual bool HasDeviceId(const FString& InDeviceId) const = 0;` — Checks whether this device proxy contains a variant for the provided target device. @param InDeviceId DeviceId to check for a variant. @return true if this device has a variant of the provided DeviceId.
- L103 _public prototype_ `virtual const FString GetTargetDeviceId(FName InVariant) const = 0;` — Gets the identifier of the device. @param InVariant name of the variant to return the device identifier for, If InVariant == NAME_None you'll get back the default target device identifier. @return The target device identifier.
- L111 _public prototype_ `virtual const TSet<FString>& GetTargetDeviceIds(FName InVariant) const = 0;` — Gets a list of device identifiers for an aggregate (All_<platform>_devices_on_<host>) proxy @param InVariant name of the variant to return the device identifier for, If InVariant == NAME_None you'll get back the default target device identifiers. @param OutDeviceIds The list of device identifiers.
- L119 _public prototype_ `virtual bool HasTargetPlatform(FName InTargetPlatformId) const = 0;` — Checks whether this device proxy contains a variant for the provided platform. @param InTargetPlatformName Target Platform Name for the target device to check for as a variant of this device. @return true if this device has a variant of the provided Target Platform .
- L127 _public prototype_ `virtual FString GetTargetPlatformName(FName InVariant) const = 0;` — Gets the target platform of the device variant. @param InVariant Variant to get the platform name for. @return Target Platform Name string.
- L135 _public prototype_ `virtual FName GetTargetPlatformId(FName InVariant) const = 0;` — Gets the target platform of the device variant. @param InVariant Variant to get the platform id for. @return Target Platform Id.
- L143 _public prototype_ `virtual FName GetVanillaPlatformId(FName InVariant) const = 0;` — Gets the Vanilla platform of the device variant. @param InVariant Variant to get the platform id for. @return Vanilla Platform Id.
- L151 _public prototype_ `virtual FText GetPlatformDisplayName(FName InVariant) const = 0;` — Gets the Vanilla platform of the device variant. @param InVariant Variant to get the vanilla platform name for. @return Platform Display Name string.
- L158 _public prototype_ `virtual const FString& GetHostName() const = 0;` — Gets the name of the host machine that claimed the device. @return Host name string.
- L165 _public prototype_ `virtual const FString& GetHostUser() const = 0;` — Gets the name of the user that claimed the device. @return User name.
- L172 _public prototype_ `virtual const FString& GetDeviceUser() const = 0;` — Gets the name of the (device's) user that is logged in on a device. @return Device user name.
- L179 _public prototype_ `virtual const FString& GetDeviceUserPassword() const = 0;` — Gets the password of the (device's) user that is logged in on a device. @return Device user password.
- L186 _public prototype_ `virtual const FString& GetMake() const = 0;` — Gets the device make (i.e. Apple or Sony). @return Device make.
- L193 _public prototype_ `virtual const FString& GetModel() const = 0;` — Gets the device model (i.e. PS3 or XBox). @return Device model.
- L200 _public prototype_ `virtual const FString& GetName() const = 0;` — Gets the name of the device (i.e. network name or IP address). @return Device name string.
- L207 _public prototype_ `virtual const FString& GetType() const = 0;` — Gets the device type (i.e. Console, PC or Mobile). @return Device type.
- L214 _public prototype_ `virtual const FString& GetOSVersion() const = 0;` — Gets the OS Version of the device @return Device OS Version.
- L221 _public function_ `virtual FStringView GetArchitecture() const` — Gets the architecture of the device @return Device Architecture.
- L231 _public prototype_ `virtual const FString& GetConnectionType() const = 0;` — Gets the type of connection for this device. @return Device type.
- L238 _public prototype_ `virtual bool IsConnected() const = 0;` — Checks whether the device is currently connected. @return true if the device is connected, false otherwise.
- L245 _public prototype_ `virtual bool IsAuthorized() const = 0;` — Checks whether the device is authorized. @return true if the device is authorized, false otherwise.
- L252 _public prototype_ `virtual bool IsShared() const = 0;` — Checks whether this device is being shared with other users. @return true if the device is being shared, false otherwise.
- L259 _public prototype_ `virtual bool IsSimulated() const = 0;` — Checks whether this device is being simulated on a Simulator @return true if the device is being simulated, false otherwise.
- L267 _public prototype_ `virtual bool TerminateLaunchedProcess(FName InVariant, const FString& ProcessIdentifier) = 0;` — Cancel the application running on the device @param InVariant Variant of the device @param ProcessIdentifier The bundle id @return true if the launch has been successfully terminated, false otherwise.
- L274 _public function_ `virtual bool IsAggregated() const` — Checks if this is an aggregate (All_<platform>_devices_on_<host>) proxy. @return true if the device is aggregated, false otherwise.
- L285 _public prototype_ `virtual void PowerOff(bool Force) = 0;` — Powers off the device. @param Force Whether to force powering off. @see PowerOn, Reboot
- L292 _public prototype_ `virtual void PowerOn() = 0;` — Powers on the device. @see PowerOff, Reboot
- L299 _public prototype_ `virtual void Reboot() = 0;` — Reboots the device. @see PowerOff, PowerOn
- L304 _public prototype_ `virtual ~ITargetDeviceProxy() = default;` — Virtual destructor.

### `Source/Developer/TargetDeviceServices/Public/ITargetDeviceProxyManager.h` (Public)


#### class `ITargetDeviceProxyManager`  
`class ITargetDeviceProxyManager`  
_L18-90_
- desc: Interface for device proxy managers.
- L29 _public prototype_ `virtual TSharedRef<ITargetDeviceProxy> FindOrAddProxy(const FString& Name) = 0;` — Finds or adds a device proxy for the specified device name. @param Name The name of the device to create the proxy for. @return The device proxy. @see FindProxy, FindProxyDeviceForTargetDevice, GetProxies
- L38 _public prototype_ `virtual TSharedPtr<ITargetDeviceProxy> FindProxy(const FString& Name) = 0;` — Finds the device proxy for the specified device name. @param Name The name of the device to create the proxy for. @return The device proxy, or nullptr if it couldn't be found. @see FindOrAddProxy, FindProxyDeviceForTargetDevice, GetProxies
- L47 _public prototype_ `virtual TSharedPtr<ITargetDeviceProxy> FindProxyDeviceForTargetDevice(const FString& DeviceId) = 0;` — Finds the device proxy for the specified target device id. @param DeviceId The identifier of the target device to create the proxy for. @return The device proxy, or nullptr if it couldn't be found. @see FindOrAddProxy, FindProxy, GetProxies
- L57 _public prototype_ `virtual void GetProxies(FName TargetPlatformName, bool IncludeUnshared, TArray<TSharedPtr<ITargetDeviceProxy>>& OutProxies) = 0;` — Gets a list of devices found by the device discovery. @param PlatformName The the name of the target platform to get proxies for (or empty string for all proxies). @param IncludeUnshared Whether to include devices that are not being shared with the local user. @param OutProxies Will hold the list of devices found by the locator. @see FindOrAddProxy, FindProxy, FindProxyDeviceForTargetDevice
- L66 _public prototype_ `virtual void GetAllProxies(FName TargetPlatformName, TArray<TSharedPtr<ITargetDeviceProxy>>& OutProxies) = 0;` — Gets a list of proxies created by the device discovery, including the "All device" proxies @param PlatformName The the name of the target platform to get proxies for (or empty string for all proxies). @param OutProxies Will hold the list of devices found by the locator. @see FindOrAddProxy, FindProxy, FindProxyDeviceForTargetDevice
- L75 _public prototype_ `DECLARE_EVENT_OneParam(ITargetDeviceServiceManager, FOnTargetDeviceProxyAdded, const TSharedRef<ITargetDeviceProxy>& );` — Gets an event delegate that is executed when a target device proxy was added. @return The event delegate.
- L76 _public prototype_ `virtual FOnTargetDeviceProxyAdded& OnProxyAdded() = 0;`
- L83 _public prototype_ `DECLARE_EVENT_OneParam(ITargetDeviceServiceManager, FOnTargetDeviceProxyRemoved, const TSharedRef<ITargetDeviceProxy>& );` — Gets an event delegate that is executed when a target device proxy was removed. @return The event delegate.
- L84 _public prototype_ `virtual FOnTargetDeviceProxyRemoved& OnProxyRemoved() = 0;`
- L89 _public prototype_ `virtual ~ITargetDeviceProxyManager() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L75 _delegate_ `DECLARE_EVENT_OneParam(ITargetDeviceServiceManager, FOnTargetDeviceProxyAdded, const TSharedRef<ITargetDeviceProxy>& );` — Gets an event delegate that is executed when a target device proxy was added. @return The event delegate.
- L83 _delegate_ `DECLARE_EVENT_OneParam(ITargetDeviceServiceManager, FOnTargetDeviceProxyRemoved, const TSharedRef<ITargetDeviceProxy>& );` — Gets an event delegate that is executed when a target device proxy was removed. @return The event delegate.

### `Source/Developer/TargetDeviceServices/Public/ITargetDeviceService.h` (Public)


#### class `ITargetDeviceService`  
`class ITargetDeviceService`  
_L31-156_
- desc: Interface for target device services. Device services make locally connected or discovered network target devices available over the network. Remote clients communicate with device services through a target device proxy. @see ITargetDeviceProxy
- L40 _public prototype_ `virtual void AddTargetDevice(TSharedPtr<ITargetDevice, ESPMode::ThreadSafe> InDevice) = 0;` — Adds a flavor to this device. @return true if the service can start, false otherwise.
- L50 _public prototype_ `virtual bool CanStart(FName InFlavor = NAME_None) const = 0;` — Checks whether this service can start. A service can be started if it has a valid device and the device is connected. This method does not take into account whether the service is already started. @return true if the service can start, false otherwise.
- L57 _public prototype_ `virtual const FString& GetClaimHost() = 0;` — Gets the name of the host that has a claim on the device. @return Host name string.
- L64 _public prototype_ `virtual const FString& GetClaimUser() = 0;` — Gets the name of the user that has a claim on the device. @return User name string.
- L71 _public prototype_ `virtual TSharedPtr<ITargetDevice, ESPMode::ThreadSafe> GetDevice(FName InFlavor = NAME_None) const = 0;` — Gets the target device for the supplied flavor, if no flavor is specified then the default device flavor is returned. @return A pointer to the target device.
- L78 _public prototype_ `virtual FString GetDeviceName() const = 0;` — Gets the name of the device that this service exposes. @return The human readable device name.
- L85 _public prototype_ `virtual FName GetDevicePlatformName() const = 0;` — Gets the name of the platform of device that this service exposes. @return The platform name.
- L92 _public prototype_ `virtual FString GetDevicePlatformDisplayName() const = 0;` — Gets the display name of the platform of device that this service exposes. @return The human readable platform name.
- L99 _public prototype_ `virtual bool IsRunning() const = 0;` — Checks whether the service is currently running. @return true if the service is running, false otherwise.
- L110 _public prototype_ `virtual bool IsShared() const = 0;` — Checks whether the device is being shared with other users. If a device is shared, the device proxies of all users on the network can discover and use the device. @return true if the device is shared, false otherwise. @see SetShared
- L117 _public prototype_ `virtual int32 NumTargetDevices() = 0;` — Gets number of target devices. @return number of target devices in this device service.
- L124 _public prototype_ `virtual void RemoveTargetDevice(TSharedPtr<ITargetDevice, ESPMode::ThreadSafe> InDevice) = 0;` — Removes a flavor from this device. @return true if the service can start, false otherwise.
- L135 _public prototype_ `virtual void SetShared(bool InShared) = 0;` — Sets whether the device should be shared with other users. If a device is shared, the device proxies of all users on the network can discover and use the device. @param InShared Indicates whether device sharing is enabled. @see IsShared
- L143 _public prototype_ `virtual bool Start() = 0;` — Starts the service. @return true if the service has been started, false otherwise. @see IsRunning, Stop
- L150 _public prototype_ `virtual void Stop() = 0;` — Stops the service. @see IsRunning, Stop
- L155 _public prototype_ `virtual ~ITargetDeviceService() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef TSharedPtr<class ITargetDeviceService, ESPMode::ThreadSafe> ITargetDeviceServicePtr;` — Type definition for shared pointers to instances of ITargetDeviceService.
- L19 _typedef_ `typedef TSharedRef<class ITargetDeviceService, ESPMode::ThreadSafe> ITargetDeviceServiceRef;` — Type definition for shared references to instances of ITargetDeviceService.

### `Source/Developer/TargetDeviceServices/Public/ITargetDeviceServiceManager.h` (Public)


#### class `ITargetDeviceServiceManager`  
`class ITargetDeviceServiceManager`  
_L17-72_
- desc: Interface for target device service managers.
- L32 _public prototype_ `virtual bool AddStartupService(const FString& DeviceName) = 0;` — Adds a service to the list of services that are started automatically. A preliminary device name may be assigned to services that expose devices which could not be discovered automatically or are currently unavailable. This name will be replaced with the actual device name once the physical device becomes available. @param DeviceName The device name for the service to add to the startup list @return true if the service added, false otherwise. @see GetServices, RemoveStartupService
- L40 _public prototype_ `virtual int32 GetServices(TArray<TSharedPtr<ITargetDeviceService, ESPMode::ThreadSafe>>& OutServices) = 0;` — Gets the collection of target device services managed by this instance. @param OutServices Will contain the collection of services. @return The number of services returned.
- L48 _public prototype_ `virtual void RemoveStartupService(const FString& DeviceName) = 0;` — Removes a service from the list of services that are started automatically. @param DeviceName The device name for the service to remove from the startup list. @see AddStartupService, GetServices
- L57 _public prototype_ `DECLARE_EVENT_OneParam(ITargetDeviceServiceManager, FOnTargetDeviceServiceAdded, const ITargetDeviceServiceRef& );` — Gets an event delegate that is executed when a target device service was added. @return The event delegate.
- L58 _public prototype_ `virtual FOnTargetDeviceServiceAdded& OnServiceAdded() = 0;`
- L65 _public prototype_ `DECLARE_EVENT_OneParam(ITargetDeviceServiceManager, FOnTargetDeviceServiceRemoved, const ITargetDeviceServiceRef& );` — Gets an event delegate that is executed when a target device service was removed. @return The event delegate.
- L66 _public prototype_ `virtual FOnTargetDeviceServiceRemoved& OnServiceRemoved() = 0;`
- L71 _public prototype_ `virtual ~ITargetDeviceServiceManager() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L57 _delegate_ `DECLARE_EVENT_OneParam(ITargetDeviceServiceManager, FOnTargetDeviceServiceAdded, const ITargetDeviceServiceRef& );` — Gets an event delegate that is executed when a target device service was added. @return The event delegate.
- L65 _delegate_ `DECLARE_EVENT_OneParam(ITargetDeviceServiceManager, FOnTargetDeviceServiceRemoved, const ITargetDeviceServiceRef& );` — Gets an event delegate that is executed when a target device service was removed. @return The event delegate.

### `Source/Developer/TargetDeviceServices/Public/ITargetDeviceServicesModule.h` (Public)


#### class `ITargetDeviceServicesModule`  
`class ITargetDeviceServicesModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: Interface for target device services modules.
- L24 _public prototype_ `virtual TSharedRef<ITargetDeviceProxyManager> GetDeviceProxyManager() = 0;` — Gets the target device proxy manager. @return The device proxy manager. @see GetDeviceServiceManager
- L32 _public prototype_ `virtual TSharedRef<ITargetDeviceServiceManager> GetDeviceServiceManager() = 0;` — Gets the target device service manager. @return The device service manager. @see GetDeviceProxyManager
- L37 _public prototype_ `virtual ~ITargetDeviceServicesModule() = default;` — Virtual destructor.

### `Source/Developer/TargetDeviceServices/Public/TargetDeviceServiceMessages.h` (Public)


#### struct `FTargetDeviceServiceTerminateLaunchedProcess`  
`struct FTargetDeviceServiceTerminateLaunchedProcess`  
_L25-52_
- reflection: `USTRUCT()`
- desc: Implements a message for terminating an application running on the device. @see FTargetDeviceServiceTerminateLaunchedProcess
- L31 _public member_ `FName Variant;` — `UPROPERTY(EditAnywhere, Category = "Message")` — Holds the variant identifier of the target device to use.
- L42 _public member_ `FString AppID;` — `UPROPERTY(EditAnywhere, Category = "Message")` — Holds the identifier of the application to launch. The semantics of this identifier are target platform specific. In some cases it may be a GUID, in other cases it may be the path to the application or some other means of identifying the application. Application identifiers are returned from target device services as result of successful deployment transactions.
- L45 _public function_ `FTargetDeviceServiceTerminateLaunchedProcess()` — Default constructor.
- L48 _public function_ `FTargetDeviceServiceTerminateLaunchedProcess(FName InVariant, const FString& InAppId) : Variant(InVariant) , AppID(InAppId)` — Creates and initializes a new instance.

#### struct `FTargetDeviceClaimDenied`  
`struct FTargetDeviceClaimDenied`  
_L65-91_
- reflection: `USTRUCT()`
- desc: Implements a message that is sent when a device is already claimed by someone else. @see FTargetDeviceClaimDropped @see FTargetDeviceClaimRequest
- L71 _public member_ `FString DeviceName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the identifier of the device that is already claimed.
- L75 _public member_ `FString HostName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the host computer that claimed the device.
- L79 _public member_ `FString HostUser;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that claimed the device.
- L83 _public function_ `FTargetDeviceClaimDenied()` — Default constructor.
- L86 _public function_ `FTargetDeviceClaimDenied(const FString& InDeviceName, const FString& InHostName, const FString& InHostUser) : DeviceName(InDeviceName) , HostName(InHostName) , HostUser(InHostUser)` — Creates and initializes a new instance.

#### struct `FTargetDeviceClaimed`  
`struct FTargetDeviceClaimed`  
_L101-127_
- reflection: `USTRUCT()`
- desc: Implements a message that is sent when a service claimed a device. @see FTargetDeviceClaimDenied @see FTargetDeviceClaimDropped
- L107 _public member_ `FString DeviceName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the identifier of the device that is being claimed.
- L111 _public member_ `FString HostName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the host computer that is claiming the device.
- L115 _public member_ `FString HostUser;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that is claiming the device.
- L119 _public function_ `FTargetDeviceClaimed()` — Default constructor.
- L122 _public function_ `FTargetDeviceClaimed(const FString& InDeviceName, const FString& InHostName, const FString& InHostUser) : DeviceName(InDeviceName) , HostName(InHostName) , HostUser(InHostUser)` — Creates and initializes a new instance.

#### struct `FTargetDeviceUnclaimed`  
`struct FTargetDeviceUnclaimed`  
_L136-162_
- reflection: `USTRUCT()`
- desc: Implements a message that is sent when a device is no longer claimed. @see FTargetDeviceClaimDenied, FTargetDeviceClaimRequest
- L142 _public member_ `FString DeviceName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the identifier of the device that is no longer claimed.
- L146 _public member_ `FString HostName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the host computer that had claimed the device.
- L150 _public member_ `FString HostUser;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that had claimed the device.
- L154 _public function_ `FTargetDeviceUnclaimed()` — Default constructor.
- L157 _public function_ `FTargetDeviceUnclaimed(const FString& InDeviceName, const FString& InHostName, const FString& InHostUser) : DeviceName(InDeviceName) , HostName(InHostName) , HostUser(InHostUser)` — Creates and initializes a new instance.

#### struct `FTargetDeviceServicePing`  
`struct FTargetDeviceServicePing`  
_L172-188_
- reflection: `USTRUCT()`
- desc: Implements a message for discovering target device services on the network.
- L178 _public member_ `FString HostUser;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user who generated the ping.
- L182 _public function_ `FTargetDeviceServicePing()` — Default constructor.
- L185 _public function_ `FTargetDeviceServicePing(const FString& InHostUser) : HostUser(InHostUser)` — Creates and initializes a new instance.

#### struct `FTargetDeviceVariant`  
`struct FTargetDeviceVariant`  
_L195-216_
- reflection: `USTRUCT()`
- desc: Struct for a flavor's information
- L200 _public member_ `FString DeviceID;` — `UPROPERTY(EditAnywhere, Category="Variant")`
- L203 _public member_ `FName VariantName;` — `UPROPERTY(EditAnywhere, Category="Variant")`
- L206 _public member_ `FString TargetPlatformName;` — `UPROPERTY(EditAnywhere, Category="Variant")`
- L209 _public member_ `FName TargetPlatformId;` — `UPROPERTY(EditAnywhere, Category="Variant")`
- L212 _public member_ `FName VanillaPlatformId;` — `UPROPERTY(EditAnywhere, Category="Variant")`
- L215 _public member_ `FString PlatformDisplayName;` — `UPROPERTY(EditAnywhere, Category="Variant")`

#### struct `FTargetDeviceServicePong`  
`struct FTargetDeviceServicePong`  
_L223-322_
- reflection: `USTRUCT()`
- desc: Implements a message that is sent in response to target device service discovery messages.
- L229 _public member_ `bool Connected = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the device is currently connected.
- L233 _public member_ `bool Authorized = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the device is authorized.
- L237 _public member_ `FString HostName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the host computer that the device is attached to.
- L241 _public member_ `FString HostUser;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user under which the host computer is running.
- L245 _public member_ `FString Make;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the make of the device, i.e. Microsoft or Sony.
- L249 _public member_ `FString Model;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the model of the device.
- L253 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the human readable name of the device, i.e "Bob's XBox'.
- L257 _public member_ `FString DeviceUser;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that we log in to remote device as, i.e "root".
- L261 _public member_ `FString DeviceUserPassword;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the password of the user that we log in to remote device as, i.e "12345".
- L265 _public member_ `bool Shared = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether this device is shared with other users on the network.
- L269 _public member_ `bool SupportsMultiLaunch = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the device supports running multiple application instances in parallel.
- L273 _public member_ `bool SupportsPowerOff = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the device can be powered off.
- L277 _public member_ `bool SupportsPowerOn = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the device can be powered on.
- L281 _public member_ `bool SupportsReboot = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the device can be rebooted.
- L285 _public member_ `bool SupportsVariants = false;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the device's target platform supports variants.
- L289 _public member_ `FString Type;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the device type.
- L293 _public member_ `FString OSVersion;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the device OS Version.
- L297 _public member_ `FString Architecture;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the device architecture.
- L301 _public member_ `FString ConnectionType;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the connection type.
- L305 _public member_ `FName DefaultVariant;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the variant name of the default device.
- L309 _public member_ `TArray<FTargetDeviceVariant> Variants;` — `UPROPERTY(EditAnywhere, Category="Message")` — List of the Flavors this service supports
- L313 _public member_ `bool Aggregated = true;` — `UPROPERTY(EditAnywhere, Category = "Message")` — Flag for the "All devices" proxy.
- L317 _public member_ `FString AllDevicesName;` — `UPROPERTY(EditAnywhere, Category = "Message")` — Holds the name of "All devices" proxy.
- L321 _public member_ `FName AllDevicesDefaultVariant;` — `UPROPERTY(EditAnywhere, Category = "Message")` — Holds the default variant name of "All devices" proxy.

#### struct `FTargetDeviceServicePowerOff`  
`struct FTargetDeviceServicePowerOff`  
_L332-357_
- reflection: `USTRUCT()`
- desc: Implements a message for powering on a target device.
- L342 _public member_ `bool Force;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds a flag indicating whether the power-off should be enforced. If powering off is not enforced, if may fail if some running application prevents it.
- L346 _public member_ `FString Operator;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that wishes to power off the device.
- L350 _public function_ `FTargetDeviceServicePowerOff() : Force(false)` — Default constructor.
- L353 _public function_ `FTargetDeviceServicePowerOff(const FString& InOperator, bool InForce) : Force(InForce) , Operator(InOperator)` — Creates and initializes a new instance.

#### struct `FTargetDeviceServicePowerOn`  
`struct FTargetDeviceServicePowerOn`  
_L364-380_
- reflection: `USTRUCT()`
- desc: Implements a message for powering on a target device.
- L370 _public member_ `FString Operator;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that wishes to power on the device.
- L374 _public function_ `FTargetDeviceServicePowerOn()` — Default constructor.
- L377 _public function_ `FTargetDeviceServicePowerOn(const FString& InOperator) : Operator(InOperator)` — Creates and initializes a new instance.

#### struct `FTargetDeviceServiceReboot`  
`struct FTargetDeviceServiceReboot`  
_L387-403_
- reflection: `USTRUCT()`
- desc: Implements a message for rebooting a target device.
- L393 _public member_ `FString Operator;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that wishes to reboot the device.
- L397 _public function_ `FTargetDeviceServiceReboot()` — Default constructor.
- L400 _public function_ `FTargetDeviceServiceReboot(const FString& InOperator) : Operator(InOperator)` — Creates and initializes a new instance.
