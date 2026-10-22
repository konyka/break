# Developer / IOSTargetPlatformControls

- module root: `Source/Developer/IOS/IOSTargetPlatformControls`
- headers: 5; symbols: 168
- symbol kinds: class=6, delegate=1, enum=1, enumerator=5, function=29, member=57, prototype=62, struct=2, typedef=5
- PrivateDependencyModuleNames: AudioPlatformConfiguration, Core, CoreUObject, DesktopPlatform, Engine, IOSTargetPlatformSettings, Json, LaunchDaemonMessages, Networking, Projects, Sockets, TargetPlatform
- PrivateIncludePathModuleNames: MessagingCommon, TargetDeviceServices

### `Source/Developer/IOS/IOSTargetPlatformControls/Private/IOSTargetDevice.h` (Private)


#### class `FTcpDSCommander`  
`class FTcpDSCommander : FRunnable`  
_L28-90_
- inherits: `FRunnable`
- desc: Handles the communication to the Deployment Server over TCP (will start the DeploymentServer if no instance is found running)
- L36 _public prototype_ `FTcpDSCommander(const uint8* Data, int32 Count, TQueue<FString>& InOutputQueue);` — Creates and initializes a new instance.
- L39 _public prototype_ `virtual ~FTcpDSCommander();` — Virtual destructor.
- L42 _public prototype_ `static bool IsDSRunning();` — Check if DeploymentServer mutex is active
- L48 _public prototype_ `virtual void Exit() override;`
- L49 _public prototype_ `virtual bool Init() override;`
- L50 _public prototype_ `virtual uint32 Run() override;`
- L51 _public prototype_ `virtual void Stop() override;`
- L53 _public function_ `inline bool IsValid()`
- L57 _public function_ `inline bool IsStopped()`
- L61 _public function_ `inline bool WasSuccess()`
- L65 _public function_ `inline bool IsSystemError()`
- L72 _private prototype_ `inline bool StartDSProcess();`
- L75 _private member_ `bool bStopping;` — For the thread
- L76 _private member_ `bool bStopped;`
- L77 _private member_ `bool bIsSuccess;`
- L78 _private member_ `bool bIsSystemError;` — Deployment server was not able to start, or connection to it could not be made
- L81 _private member_ `class FSocket* DSSocket;`
- L84 _private member_ `FRunnableThread* Thread;` — Holds the thread object.
- L86 _private member_ `TQueue<FString>& OutputQueue;`
- L87 _private member_ `uint8* DSCommand;`
- L88 _private member_ `int32 DSCommandLen;`
- L89 _private member_ `double LastActivity;`

#### class `FIOSTargetDevice`  
`class FIOSTargetDevice : public ITargetDevice`  
_L95-317_
- inherits: `ITargetDevice`
- desc: Implements an iOS target device.
- L105 _public prototype_ `FIOSTargetDevice(const ITargetPlatformControls& InTargetPlatformControls);` — Create and initialize a new instance. @param InTargetPlatformControls The target platform that owns the device.
- L111 _public prototype_ `virtual bool Connect() override;`
- L112 _public prototype_ `virtual void Disconnect() override;`
- L113 _public prototype_ `virtual int32 GetProcessSnapshot(TArray<FTargetDeviceProcessInfo>& OutProcessInfos) override;`
- L114 _public prototype_ `virtual ETargetDeviceTypes GetDeviceType() const override;`
- L115 _public prototype_ `virtual ETargetDeviceConnectionTypes GetDeviceConnectionType() const override;`
- L116 _public prototype_ `virtual FTargetDeviceId GetId() const override;`
- L117 _public prototype_ `virtual FString GetName() const override;`
- L118 _public prototype_ `virtual FString GetOperatingSystemName() override;`
- L119 _public prototype_ `virtual FString GetModelId() const override;`
- L120 _public prototype_ `virtual FString GetOSVersion() const override;`
- L121 _public prototype_ `virtual const class ITargetPlatformSettings& GetPlatformSettings() const override;`
- L122 _public prototype_ `virtual const class ITargetPlatformControls& GetPlatformControls() const override;`
- L123 _public prototype_ `virtual bool IsConnected() override;`
- L124 _public prototype_ `virtual bool IsDefault() const override;`
- L125 _public prototype_ `virtual bool PowerOff(bool Force) override;`
- L126 _public prototype_ `virtual bool PowerOn() override;`
- L127 _public function_ `virtual bool IsAuthorized() const override`
- L128 _public prototype_ `virtual bool Reboot(bool bReconnect = false) override;`
- L129 _public prototype_ `virtual bool SupportsFeature(ETargetDeviceFeatures Feature) const;`
- L130 _public prototype_ `virtual bool TerminateProcess(const int64 ProcessId) override;`
- L131 _public prototype_ `virtual void SetUserCredentials(const FString& UserName, const FString& UserPassword) override;`
- L132 _public prototype_ `virtual bool GetUserCredentials(FString& OutUserName, FString& OutUserPassword) override;`
- L133 _public prototype_ `virtual void ExecuteConsoleCommand(const FString& ExecCommand) const override;`
- L134 _public prototype_ `virtual ITargetDeviceOutputPtr CreateDeviceOutputRouter(FOutputDevice* Output) const override;`
- L139 _public member_ `FDateTime LastPinged;` — Timeout check for removing stale devices
- L147 _private member_ `const ITargetPlatformControls& TargetPlatformControls;` — Holds a reference to the device's target platform controls.
- L150 _private member_ `FMessageAddress DeviceEndpoint;` — Contains the address of the remote device
- L153 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — MessageEndpoint for communicating with remote device
- L156 _private member_ `FString AppId;` — Contains the current AppID/GameName for Deployment/launching.
- L159 _private member_ `EBuildConfiguration BuildConfiguration;` — Contains the build configuration of the app to deploy
- L162 _private member_ `bool bIsSimulated;` — Lets us know whether the thing is a sim device or a physical device.
- L167 _private member_ `bool bCanReboot;` — Remote rebootable
- L170 _private member_ `bool bCanPowerOn;` — Remote bootable
- L173 _private member_ `bool bCanPowerOff;` — Remote shutdown-able
- L176 _private member_ `FTargetDeviceId DeviceId;` — Id of device
- L179 _private member_ `FString DeviceName;` — Name of device
- L182 _private member_ `bool bIsDeviceAuthorized;` — Holds a flag indicating whether the device is USB / OTA comms authorized
- L185 _private member_ `ETargetDeviceTypes DeviceType;` — Type of device
- L188 _private member_ `FString DeviceModelId;` — The specific model identifier of the device
- L191 _private member_ `FString DeviceOSVersion;` — The iOS/tvOS/iPadOS OS version
- L194 _private member_ `ETargetDeviceConnectionTypes DeviceConnectionType;` — Type of device connection (USB or Wifi)
- L198 _public function_ `void SetFeature(ETargetDeviceFeatures InFeature, bool bFlag)`
- L215 _public function_ `void SetDeviceId(const FTargetDeviceId InDeviceId)` — Sets device id
- L221 _public function_ `void SetDeviceName(const FString InDeviceName)` — Sets the name of the device
- L227 _public function_ `void SetModelId(const FString InModelId)` — Sets the modelId of the device
- L233 _public function_ `void SetOSVersion(const FString InOSVersion)` — Sets the OS version of the device
- L243 _public function_ `void SetAuthorized(bool bInIsAuthorized)` — Sets the device's authorization state. @param bInIsAuthorized - Whether the device is authorized for USB communications.
- L249 _public function_ `void SetDeviceType(const FString InDeviceTypeString)` — Sets the type of the device
- L278 _public function_ `void SetDeviceConnectionType(const FString InDeviceConnectionTypeString)` — Sets the connection type (usb/wifi) of the device
- L298 _public function_ `void SetDeviceEndpoint(const FMessageAddress& DeviceAddress)`
- L303 _public function_ `void SetAppId(const FString& GameName)`
- L308 _public function_ `void SetAppConfiguration(EBuildConfiguration Configuration)`
- L313 _public function_ `void SetIsSimulated(bool IsSimulated)`

#### Free symbols / members of external scopes

- L17 _typedef_ `typedef TSharedPtr<class FIOSTargetDevice, ESPMode::ThreadSafe> FIOSTargetDevicePtr;` — Type definition for shared pointers to instances of FIOSTargetDevice.
- L20 _typedef_ `typedef TSharedRef<class FIOSTargetDevice, ESPMode::ThreadSafe> FIOSTargetDeviceRef;` — Type definition for shared references to instances of FIOSTargetDevice.
- L23 _typedef_ `typedef TSharedPtr<class FIOSTargetDeviceOutput, ESPMode::ThreadSafe> FIOSTargetDeviceOutputPtr;` — Type definition for shared references to instances of FIOSTargetDeviceOutput.

### `Source/Developer/IOS/IOSTargetPlatformControls/Private/IOSTargetDeviceOutput.h` (Private)


#### class `FIOSDeviceOutputReaderRunnable`  
`class FIOSDeviceOutputReaderRunnable : public FRunnable`  
_L32-54_
- inherits: `FRunnable`
- L35 _public prototype_ `FIOSDeviceOutputReaderRunnable(const FString& InDeviceUDID, FOutputDevice* Output);`
- L38 _public prototype_ `virtual bool Init(void) override;` — FRunnable interface.
- L39 _public prototype_ `virtual void Exit(void) override;`
- L40 _public prototype_ `virtual void Stop(void) override;`
- L41 _public prototype_ `virtual uint32 Run(void) override;`
- L44 _private prototype_ `bool StartSyslogProcess(void);`
- L47 _private member_ `FThreadSafeCounter StopTaskCounter;` — > 0 if we've been asked to abort work in progress at the next opportunity
- L49 _private member_ `FString DeviceUDID;`
- L50 _private member_ `FOutputDevice* Output;`
- L51 _private member_ `void* SyslogReadPipe;`
- L52 _private member_ `void* SyslogWritePipe;`
- L53 _private member_ `FProcHandle SyslogProcHandle;`

#### class `FIOSTargetDeviceOutput`  
`class FIOSTargetDeviceOutput : public ITargetDeviceOutput`  
_L59-67_
- inherits: `ITargetDeviceOutput`
- desc: Implements a IOS target device output.
- L62 _public prototype_ `bool Init(const FIOSTargetDevice& TargetDevice, FOutputDevice* Output);`
- L65 _private member_ `TUniquePtr<FRunnableThread> DeviceOutputThread;`
- L66 _private member_ `FString DeviceName;`

#### Free symbols / members of external scopes

- L15 _function_ `static FString GetLibImobileDeviceExe(const FString& ExeName)`

### `Source/Developer/IOS/IOSTargetPlatformControls/Private/IOSTargetDeviceOutput.inl` (Private)


#### Free symbols / members of external scopes

- L14 _function_ `inline FIOSDeviceOutputReaderRunnable::FIOSDeviceOutputReaderRunnable(const FString& InDeviceUDID, FOutputDevice* InOutput) : StopTaskCounter(0) , DeviceUDID(InDeviceUDID) , Output(InOutput) , SyslogReadPipe(nullptr) , SyslogWritePipe(nullptr)` (scope `FIOSDeviceOutputReaderRunnable`)
- L23 _function_ `inline bool FIOSDeviceOutputReaderRunnable::StartSyslogProcess(void)` (scope `FIOSDeviceOutputReaderRunnable`)
- L31 _function_ `inline bool FIOSDeviceOutputReaderRunnable::Init(void)` (scope `FIOSDeviceOutputReaderRunnable`)
- L37 _function_ `inline void FIOSDeviceOutputReaderRunnable::Exit(void)` (scope `FIOSDeviceOutputReaderRunnable`)
- L46 _function_ `inline void FIOSDeviceOutputReaderRunnable::Stop(void)` (scope `FIOSDeviceOutputReaderRunnable`)
- L51 _function_ `inline uint32 FIOSDeviceOutputReaderRunnable::Run(void)` (scope `FIOSDeviceOutputReaderRunnable`)
- L106 _function_ `inline bool FIOSTargetDeviceOutput::Init(const FIOSTargetDevice& TargetDevice, FOutputDevice* Output)` (scope `FIOSTargetDeviceOutput`)

### `Source/Developer/IOS/IOSTargetPlatformControls/Private/IOSTargetPlatformControls.h` (Private)


#### class `FIOSTargetPlatformControls`  
`class FIOSTargetPlatformControls : public TNonDesktopTargetPlatformControlsBase<FIOSPlatformProperties>`  
_L27-110_
- inherits: `TNonDesktopTargetPlatformControlsBase<FIOSPlatformProperties>`
- desc: FIOSTargetPlatformControls, abstraction for cooking iOS platforms
- L34 _public prototype_ `FIOSTargetPlatformControls(bool bInISTVOS, bool bInIsVisionOS, bool bInIsClientOnly, ITargetPlatformSettings* TargetPlatformSettings);` — Default constructor.
- L39 _public prototype_ `~FIOSTargetPlatformControls();` — Destructor.
- L43 _public prototype_ `virtual void EnableDeviceCheck(bool OnOff) override;`
- L45 _public prototype_ `virtual void GetAllDevices( TArray<ITargetDevicePtr>& OutDevices ) const override;`
- L47 _public function_ `virtual bool GenerateStreamingInstallManifest(const TMultiMap<FString, int32>& PakchunkMap, const TSet<int32>& PakchunkIndicesInUse) const override`
- L52 _public prototype_ `virtual ITargetDevicePtr GetDefaultDevice( ) const override;`
- L54 _public prototype_ `virtual ITargetDevicePtr GetDevice( const FTargetDeviceId& DeviceId ) override;`
- L56 _public prototype_ `virtual bool IsSdkInstalled(bool bProjectHasCode, FString& OutTutorialPath) const override;`
- L57 _public prototype_ `virtual int32 CheckRequirements(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FString& OutTutorialPath, FString& OutDocumentationPath, FText& CustomizedLogMessage) const override;`
- L59 _public prototype_ `virtual void GetPlatformSpecificProjectAnalytics( TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray ) const override;`
- L63 _public prototype_ `virtual void GetTextureFormats( const UTexture* Texture, TArray< TArray<FName> >& OutFormats) const override;`
- L65 _public prototype_ `virtual FName FinalizeVirtualTextureLayerFormat(FName Format) const override;`
- L69 _public function_ `virtual void GetBuildProjectSettingKeys(FString& OutSection, TArray<FString>& InBoolKeys, TArray<FString>& InIntKeys, TArray<FString>& InStringKeys) const override`
- L90 _private prototype_ `void HandlePongMessage( const FIOSLaunchDaemonPong& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context );` — Handles received pong messages from the LauncherDaemon.
- L92 _private prototype_ `void HandleDeviceConnected( const FIOSLaunchDaemonPong& Message );`
- L93 _private prototype_ `void HandleDeviceDisconnected( const FIOSLaunchDaemonPong& Message );`
- L98 _private member_ `bool bIsTVOS;` — true if this is targeting TVOS vs IOS
- L99 _private member_ `bool bIsVisionOS;`
- L102 _private member_ `TMap<FTargetDeviceId, FIOSTargetDevicePtr> Devices;` — Contains all discovered IOSTargetDevices over the network.
- L105 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;` — Holds the message endpoint used for communicating with the LaunchDaemon.
- L108 _private member_ `FIOSDeviceHelper DeviceHelper;` — holds usb device helper

### `Source/Developer/IOS/IOSTargetPlatformControls/Public/IOSDeviceHelper.h` (Public)


#### enum `EDeviceConnectionInterface`  
`enum EDeviceConnectionInterface`  
_L7-14_
- L9 _public enumerator_ `NoValue = 0`
- L10 _public enumerator_ `USB = 1`
- L11 _public enumerator_ `Network = 2`
- L12 _public enumerator_ `Simulator = 3`
- L13 _public enumerator_ `Max = 4`

#### struct `FDeviceNotificationCallbackInformation`  
`struct FDeviceNotificationCallbackInformation`  
_L16-26_
- L18 _public member_ `FString DeviceID;`
- L19 _public member_ `FString DeviceName;`
- L20 _public member_ `FString DeviceUDID;`
- L21 _public member_ `FString ProductType;`
- L22 _public member_ `FString DeviceOSVersion;`
- L23 _public member_ `EDeviceConnectionInterface DeviceInterface;`
- L24 _public member_ `uint32 msgType;`
- L25 _public member_ `bool IsAuthorized;`

#### struct `FLibIMobileDevice`  
`struct FLibIMobileDevice`  
_L28-38_
- L30 _public member_ `FString DeviceID;`
- L31 _public member_ `FString DeviceName;`
- L32 _public member_ `FString DeviceUDID;`
- L33 _public member_ `FString DeviceType;`
- L34 _public member_ `FString DeviceOSVersion;`
- L35 _public member_ `EDeviceConnectionInterface DeviceInterface;`
- L36 _public member_ `bool IsAuthorized;`
- L37 _public member_ `bool IsDealtWith;`

#### class `FIOSDeviceHelper`  
`class FIOSDeviceHelper`  
_L60-104_
- desc: Implemented the iOS device helper class
- L63 _public prototype_ `static void Initialize(bool bIsTVOS);`
- L64 _public prototype_ `static TArray<FLibIMobileDevice> GetLibIMobileDevices();`
- L70 _public function_ `static FOnDeviceConnectEvent& OnDeviceConnected()` — Returns a delegate that is executed when a device is connected @return the delegate
- L81 _public function_ `static FOnDeviceConnectEvent& OnDeviceDisconnected()` — Returns a delegate the is executed when a device is disconnected @return the delegate
- L90 _public prototype_ `static bool InstallIPAOnDevice(const class FTargetDeviceId& DeviceId, const FString& IPAPath);` — Installs an ipa on to the device
- L95 _public prototype_ `static void EnableDeviceCheck(bool OnOff);` — Suspends/Enables the device connect/disconnect thread
- L97 _public member_ `static const FString LocalMacDummyUUID;`
- L100 _private prototype_ `static void DeviceCallback(void*);`
- L101 _private prototype_ `static void DoDeviceConnect(void*);`
- L102 _private prototype_ `static void DoDeviceDisconnect(void*);`
- L103 _private prototype_ `static bool MessageTickDelegate(float);`

#### Free symbols / members of external scopes

- L43 _typedef_ `typedef TSharedPtr<class FIOSDeviceHelper, ESPMode::ThreadSafe> FIOSDeviceHelperPtr;` — Type definition for shared pointers to instances of FIOSDeviceHelper
- L48 _typedef_ `typedef TSharedRef<class FIOSDeviceHelper, ESPMode::ThreadSafe> FIOSDeviceHelperRef;` — Type definition for shared references to instances of FIOSDeviceHelper
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeviceConnectEvent, const struct FIOSLaunchDaemonPong&);` — Delegate type for devices being connected or disconnected from the machine The first parameter is newly added or removed device
- L55 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeviceConnectEvent, const struct FIOSLaunchDaemonPong&);` — Delegate type for devices being connected or disconnected from the machine The first parameter is newly added or removed device
