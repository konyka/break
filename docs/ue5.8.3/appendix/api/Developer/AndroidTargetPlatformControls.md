# Developer / AndroidTargetPlatformControls

- module root: `Source/Developer/Android/AndroidTargetPlatformControls`
- headers: 6; symbols: 156
- symbol kinds: class=10, function=69, member=30, prototype=44, typedef=3
- PrivateDependencyModuleNames: AndroidDeviceDetection, AndroidTargetPlatformSettings, AudioPlatformConfiguration, Core, CoreUObject, DesktopPlatform, Engine, TargetPlatform
- PrivateIncludePathModuleNames: AndroidTargetPlatformSettings, TextureCompressor

### `Source/Developer/Android/AndroidTargetPlatformControls/Private/AndroidTargetDevice.h` (Private)


#### class `FAndroidTargetDevice`  
`class FAndroidTargetDevice : public ITargetDevice`  
_L42-307_
- inherits: `ITargetDevice`
- desc: Implements a Android target device.
- L53 _public function_ `FAndroidTargetDevice(const ITargetPlatformControls& InTargetPlatformControls, const FString& InDeviceId, const FString& InAndroidVariant) : DeviceId` — Creates and initializes a new Android target device. @param InTargetPlatformControls - The target platform controls. @param InSerialNumber - The ADB serial number of the target device. @param InAndroidVariant - The variant of the Android platform, i.e. ETC2, DXT or ASTC.
- L62 _public function_ `const FString& GetDeviceId() const`
- L72 _public function_ `void SetConnected(bool bInConnected)` — Sets the device's connection state. @param bInConnected - Whether the device is connected.
- L82 _public function_ `void SetAuthorized(bool bInIsAuthorized)` — Sets the device's authorization state. @param bInConnected - Whether the device is authorized for USB communications.
- L93 _public function_ `void SetVersions(int32 InSDKVersion, const FString& InReleaseVersion)` — Sets the device's OS/SDK versions. @param InSDKVersion - Android SDK version of the device. @param InReleaseVersion - Android Release (human-readable) version of the device.
- L104 _public function_ `void SetArchitecture(FString InArchitecture)` — Sets the architecture. @param InArchitecture - The architecture to set.
- L114 _public function_ `void SetName(FString InName)` — Sets the name. @param InName - The name to set.
- L124 _public function_ `void SetDeviceName(const FString& InDeviceName)` — Sets the device name. @param InDeviceName - The device name to set.
- L134 _public function_ `void SetModel(const FString& InModel)` — Sets the device name. @param InModel - The device name to set.
- L144 _public function_ `void SetSerialNumber(FString InSerialNumber)` — Sets the serial number @param InSerialNumber - The serial number to set.
- L149 _public function_ `const FString& GetSerialNumber() const`
- L157 _public function_ `virtual bool Connect() override`
- L162 _public function_ `virtual void Disconnect() override`
- L166 _public function_ `virtual ETargetDeviceTypes GetDeviceType() const override`
- L172 _public function_ `virtual FTargetDeviceId GetId() const override`
- L177 _public function_ `virtual FString GetName() const override`
- L183 _public function_ `virtual FString GetModelId() const override`
- L188 _public function_ `virtual FString GetOSVersion() const override`
- L193 _public function_ `virtual FStringView GetArchitecture() const override`
- L198 _public function_ `virtual const class ITargetPlatformSettings& GetPlatformSettings() const override`
- L202 _public function_ `virtual const class ITargetPlatformControls& GetPlatformControls() const override`
- L207 _public prototype_ `virtual FString GetOperatingSystemName() override;`
- L209 _public prototype_ `virtual int32 GetProcessSnapshot( TArray<FTargetDeviceProcessInfo>& OutProcessInfos ) override;`
- L211 _public function_ `virtual bool IsConnected() override`
- L216 _public function_ `virtual bool IsDefault() const override`
- L221 _public function_ `virtual bool IsAuthorized() const override`
- L226 _public prototype_ `virtual bool PowerOn() override;`
- L227 _public prototype_ `virtual bool PowerOff(bool Force) override;`
- L230 _public function_ `virtual bool IsPlatformAggregated() const override` — Return true if the devices can be grouped in an aggregate (All_<platform>_devices_on_<host>) proxy
- L236 _public prototype_ `virtual FString GetAllDevicesName() const override;` — the name of the aggregate (All_<platform>_devices_on_<host>) proxy
- L239 _public function_ `virtual FName GetAllDevicesDefaultVariant() const override` — the default variant (texture compression) of the aggregate (All_<platform>_devices_on_<host>) proxy
- L246 _public prototype_ `virtual bool Reboot(bool bReconnect = false) override;`
- L247 _public prototype_ `virtual bool TerminateLaunchedProcess(const FString& ProcessIdentifier) override;`
- L248 _public prototype_ `virtual bool SupportsFeature(ETargetDeviceFeatures Feature) const override;`
- L249 _public prototype_ `virtual bool TerminateProcess(const int64 ProcessId) override;`
- L250 _public prototype_ `virtual void SetUserCredentials(const FString& UserName, const FString& UserPassword) override;`
- L251 _public prototype_ `virtual bool GetUserCredentials(FString& OutUserName, FString& OutUserPassword) override;`
- L252 _public prototype_ `virtual void ExecuteConsoleCommand(const FString& ExecCommand) const override;`
- L253 _public prototype_ `virtual ITargetDeviceOutputPtr CreateDeviceOutputRouter(FOutputDevice* Output) const override;`
- L257 _public prototype_ `static bool GetAdbFullFilename(FString& OutFilename);` — Full filename for ADB executable.
- L270 _protected prototype_ `bool ExecuteAdbCommand( const FString& Params, FString* OutStdOut, FString* OutStdErr ) const;` — Executes an SDK command with the specified command line on this device only using ADB. @param Params - The command line parameters. @param OutStdOut - Optional pointer to a string that will hold the command's output log. @param OutStdErr - Optional pointer to a string that will hold the error message, if any. @return true on success, false otherwise.
- L274 _protected member_ `FString DeviceId;`
- L277 _protected member_ `FString AndroidVariant;` — The variant of the Android platform, i.e. ETC2, DXT or ASTC.
- L280 _protected member_ `bool bConnected;` — Holds a flag indicating whether the device is currently connected.
- L283 _protected member_ `bool bIsDeviceAuthorized;` — Holds a flag indicating whether the device is USB comms authorized (if not, most other values aren't valid but we still want to show the device as detected but unready)
- L286 _protected member_ `int32 AndroidSDKVersion;` — Holds the Android SDK version
- L289 _protected member_ `FString AndroidVersionString;` — Holds the Android Release version string (e.g., "2.3" or "4.2.2")
- L291 _protected member_ `FString Architecture;`
- L294 _protected member_ `FString Name;` — Holds the name.
- L297 _protected member_ `FString DeviceName;` — Holds the device name.
- L300 _protected member_ `FString Model;` — Holds the device model.
- L303 _protected member_ `FString SerialNumber;` — Holds the serial number (from ADB devices) of this target device.
- L306 _protected member_ `const ITargetPlatformControls& TargetPlatformControls;` — Holds a reference to the device's target platform.

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TSharedPtr<class FAndroidTargetDevice, ESPMode::ThreadSafe> FAndroidTargetDevicePtr;` — Type definition for shared pointers to instances of FAndroidTargetDevice.
- L32 _typedef_ `typedef TSharedRef<class FAndroidTargetDevice, ESPMode::ThreadSafe> FAndroidTargetDeviceRef;` — Type definition for shared references to instances of FAndroidTargetDevice.
- L37 _typedef_ `typedef TSharedPtr<class FAndroidTargetDeviceOutput, ESPMode::ThreadSafe> FAndroidTargetDeviceOutputPtr;` — Type definition for shared references to instances of FAndroidTargetDevice.

### `Source/Developer/Android/AndroidTargetPlatformControls/Private/AndroidTargetDevice.inl` (Private)


#### Free symbols / members of external scopes

- L17 _function_ `inline FString FAndroidTargetDevice::GetOperatingSystemName()` (scope `FAndroidTargetDevice`)
- L29 _function_ `inline int32 FAndroidTargetDevice::GetProcessSnapshot( TArray<FTargetDeviceProcessInfo>& OutProcessInfos )` (scope `FAndroidTargetDevice`)
- L35 _function_ `inline bool FAndroidTargetDevice::Reboot( bool bReconnect )` (scope `FAndroidTargetDevice`)
- L45 _function_ `inline bool FAndroidTargetDevice::PowerOn()` (scope `FAndroidTargetDevice`)
- L57 _function_ `inline bool FAndroidTargetDevice::PowerOff(bool Force)` (scope `FAndroidTargetDevice`)
- L62 _function_ `inline FString FAndroidTargetDevice::GetAllDevicesName() const` (scope `FAndroidTargetDevice`)
- L68 _function_ `inline bool FAndroidTargetDevice::TerminateLaunchedProcess(const FString& ProcessIdentifier)` (scope `FAndroidTargetDevice`) — cancel the running application
- L74 _function_ `inline bool FAndroidTargetDevice::SupportsFeature(ETargetDeviceFeatures Feature) const` (scope `FAndroidTargetDevice`)
- L93 _function_ `inline bool FAndroidTargetDevice::TerminateProcess( const int64 ProcessId )` (scope `FAndroidTargetDevice`)
- L99 _function_ `inline void FAndroidTargetDevice::SetUserCredentials( const FString& UserName, const FString& UserPassword )` (scope `FAndroidTargetDevice`)
- L104 _function_ `inline bool FAndroidTargetDevice::GetUserCredentials( FString& OutUserName, FString& OutUserPassword )` (scope `FAndroidTargetDevice`)
- L109 _function_ `inline void FAndroidTargetDevice::ExecuteConsoleCommand(const FString& ExecCommand) const` (scope `FAndroidTargetDevice`)
- L115 _function_ `inline ITargetDeviceOutputPtr FAndroidTargetDevice::CreateDeviceOutputRouter(FOutputDevice* Output) const` (scope `FAndroidTargetDevice`)
- L129 _function_ `inline bool FAndroidTargetDevice::GetAdbFullFilename(FString& OutFilename)` (scope `FAndroidTargetDevice`)
- L149 _function_ `inline bool FAndroidTargetDevice::ExecuteAdbCommand( const FString& CommandLine, FString* OutStdOut, FString* OutStdErr ) const` (scope `FAndroidTargetDevice`)

### `Source/Developer/Android/AndroidTargetPlatformControls/Private/AndroidTargetDeviceOutput.h` (Private)


#### class `FAndroidDeviceOutputReaderRunnable`  
`class FAndroidDeviceOutputReaderRunnable : public FRunnable`  
_L17-42_
- inherits: `FRunnable`
- L20 _public prototype_ `FAndroidDeviceOutputReaderRunnable(const FString& AdbFilename, const FString& DeviceSerialNumber, FOutputDevice* Output);`
- L23 _public prototype_ `virtual bool Init(void) override;` — FRunnable interface.
- L24 _public prototype_ `virtual void Exit(void) override;`
- L25 _public prototype_ `virtual void Stop(void) override;`
- L26 _public prototype_ `virtual uint32 Run(void) override;`
- L29 _private prototype_ `bool StartLogcatProcess(void);`
- L33 _private member_ `FThreadSafeCounter StopTaskCounter;` — > 0 if we've been asked to abort work in progress at the next opportunity
- L35 _private member_ `FString AdbFilename;`
- L36 _private member_ `FString DeviceSerialNumber;`
- L37 _private member_ `FOutputDevice* Output;`
- L39 _private member_ `void* LogcatReadPipe;`
- L40 _private member_ `void* LogcatWritePipe;`
- L41 _private member_ `FProcHandle LogcatProcHandle;`

#### class `FAndroidTargetDeviceOutput`  
`class FAndroidTargetDeviceOutput : public ITargetDeviceOutput`  
_L47-56_
- inherits: `ITargetDeviceOutput`
- desc: Implements a Android target device.
- L50 _public prototype_ `bool Init(const FAndroidTargetDevice& TargetDevice, FOutputDevice* Output);`
- L53 _private member_ `TUniquePtr<FRunnableThread> DeviceOutputThread;`
- L54 _private member_ `FString DeviceSerialNumber;`
- L55 _private member_ `FString DeviceName;`

### `Source/Developer/Android/AndroidTargetPlatformControls/Private/AndroidTargetDeviceOutput.inl` (Private)


#### Free symbols / members of external scopes

- L12 _function_ `inline FAndroidDeviceOutputReaderRunnable::FAndroidDeviceOutputReaderRunnable(const FString& InAdbFilename, const FString& InDeviceSerialNumber, FOutputDevice* InOutput) : StopTaskCounter(0) , AdbFilename(InAdbFilename) , DeviceSerialNumber(InDeviceSerialNumber) , Output(InOutput) , LogcatReadPipe(nullptr) , LogcatWritePipe(nullptr)` (scope `FAndroidDeviceOutputReaderRunnable`)
- L22 _function_ `inline bool FAndroidDeviceOutputReaderRunnable::StartLogcatProcess(void)` (scope `FAndroidDeviceOutputReaderRunnable`)
- L29 _function_ `inline bool FAndroidDeviceOutputReaderRunnable::Init(void)` (scope `FAndroidDeviceOutputReaderRunnable`)
- L35 _function_ `inline void FAndroidDeviceOutputReaderRunnable::Exit(void)` (scope `FAndroidDeviceOutputReaderRunnable`)
- L44 _function_ `inline void FAndroidDeviceOutputReaderRunnable::Stop(void)` (scope `FAndroidDeviceOutputReaderRunnable`)
- L49 _function_ `inline uint32 FAndroidDeviceOutputReaderRunnable::Run(void)` (scope `FAndroidDeviceOutputReaderRunnable`)
- L104 _function_ `inline bool FAndroidTargetDeviceOutput::Init(const FAndroidTargetDevice& TargetDevice, FOutputDevice* Output)` (scope `FAndroidTargetDeviceOutput`)

### `Source/Developer/Android/AndroidTargetPlatformControls/Private/AndroidTargetPlatformControls.h` (Private)


#### class `FAndroidTargetPlatformControls`  
`class FAndroidTargetPlatformControls : public TNonDesktopTargetPlatformControlsBase<FAndroidPlatformProperties>`  
_L37-157_
- inherits: `TNonDesktopTargetPlatformControlsBase<FAndroidPlatformProperties>`
- desc: FAndroidTargetPlatformControls, abstraction for cooking Android platforms
- L45 _public prototype_ `FAndroidTargetPlatformControls(bool bInIsClient, ITargetPlatformSettings* TargetPlatformSettings, const TCHAR* FlavorName, const TCHAR* OverrideIniPlatformName = nullptr);` — Default constructor.
- L50 _public prototype_ `virtual ~FAndroidTargetPlatformControls();` — Destructor
- L59 _public function_ `FString GetAndroidVariantName() const` — Gets the name of the Android platform variant, i.e. ASTC, ETC2, DXT, etc. @param Variant name.
- L68 _public function_ `virtual void EnableDeviceCheck(bool OnOff) override`
- L70 _public function_ `virtual bool AddDevice(const FString& DeviceName, bool bDefault) override`
- L75 _public prototype_ `virtual void GetAllDevices(TArray<ITargetDevicePtr>& OutDevices) const override;`
- L77 _public function_ `virtual bool GenerateStreamingInstallManifest(const TMultiMap<FString, int32>& PakchunkMap, const TSet<int32>& PakchunkIndicesInUse) const override`
- L82 _public prototype_ `virtual ITargetDevicePtr GetDefaultDevice() const override;`
- L84 _public prototype_ `virtual ITargetDevicePtr GetDevice(const FTargetDeviceId& DeviceId) override;`
- L86 _public prototype_ `virtual bool IsSdkInstalled(bool bProjectHasCode, FString& OutDocumentationPath) const override;`
- L88 _public prototype_ `virtual int32 CheckRequirements(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FString& OutTutorialPath, FString& OutDocumentationPath, FText& CustomizedLogMessage) const override;`
- L90 _public prototype_ `virtual void GetPlatformSpecificProjectAnalytics(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray) const override;`
- L92 _public function_ `virtual bool SupportsCompressedNonPOT() const`
- L99 _public prototype_ `virtual void GetTextureFormats(const UTexture* InTexture, TArray< TArray<FName> >& OutFormats) const override;`
- L100 _public prototype_ `virtual FName FinalizeVirtualTextureLayerFormat(FName Format) const override;`
- L103 _public prototype_ `virtual bool SupportsVariants() const override;`
- L105 _public function_ `virtual void GetBuildProjectSettingKeys(FString& OutSection, TArray<FString>& InBoolKeys, TArray<FString>& InIntKeys, TArray<FString>& InStringKeys) const override`
- L113 _public prototype_ `virtual bool ShouldExpandTo32Bit(const uint16* Indices, const int32 NumIndices) const override;`
- L116 _public prototype_ `virtual void InitializeDeviceDetection();`
- L120 _protected prototype_ `virtual FAndroidTargetDevicePtr CreateTargetDevice(const ITargetPlatformControls& InTargetPlatform, const FString& InDeviceId, const FString& InAndroidVariant) const;`
- L129 _protected function_ `virtual bool SupportedByExtensionsString(const FString& ExtensionsString, const int GLESVersion) const` — Return true if this device has a supported set of extensions for this platform. @param Extensions - The GL extensions string. @param GLESVersion - The GLES version reported by this device.
- L135 _protected prototype_ `bool HandleTicker(float DeltaTime);` — Handles when the ticker fires.
- L137 _protected prototype_ `virtual FAndroidTargetDeviceRef CreateNewDevice(const FAndroidDeviceInfo& DeviceInfo);`
- L140 _protected member_ `TMap<FString, FAndroidTargetDevicePtr> Devices;` — Holds a map of valid devices.
- L143 _protected member_ `FTickerDelegate TickDelegate;` — Holds a delegate to be invoked when the widget ticks.
- L146 _protected member_ `FTSTicker::FDelegateHandle TickDelegateHandle;` — Handle to the registered TickDelegate.
- L149 _protected member_ `IAndroidDeviceDetection* DeviceDetection;` — Pointer to the device detection handler that grabs device ids in another thread
- L153 _protected member_ `ITargetDevicePtr DefaultDevice;`
- L156 _protected member_ `FAndroidTargetPlatformSettings* AndroidTargetPlatformSettings;`

#### class `FAndroid_DXTTargetPlatformControls`  
`class FAndroid_DXTTargetPlatformControls : public FAndroidTargetPlatformControls`  
_L159-181_
- inherits: `FAndroidTargetPlatformControls`
- L162 _public function_ `FAndroid_DXTTargetPlatformControls(bool bIsClient, ITargetPlatformSettings* TargetPlatformSettings) : FAndroidTargetPlatformControls(bIsClient, TargetPlatformSettings, TEXT("DXT"))`
- L166 _public function_ `virtual bool SupportedByExtensionsString(const FString& ExtensionsString, const int GLESVersion) const override`
- L171 _public function_ `virtual float GetVariantPriority() const override`
- L179 _public prototype_ `virtual void GetTextureFormats(const UTexture* Texture, TArray< TArray<FName> >& OutFormats) const override;`

#### class `FAndroid_ASTCTargetPlatformControls`  
`class FAndroid_ASTCTargetPlatformControls : public FAndroidTargetPlatformControls`  
_L183-206_
- inherits: `FAndroidTargetPlatformControls`
- L186 _public function_ `FAndroid_ASTCTargetPlatformControls(bool bIsClient, ITargetPlatformSettings* TargetPlatformSettings, const TCHAR* OverrideIniPlatformName = TEXT("ASTC")) : FAndroidTargetPlatformControls(bIsClient, TargetPlatformSettings, OverrideIniPlatformName)`
- L191 _public function_ `virtual bool SupportedByExtensionsString(const FString& ExtensionsString, const int GLESVersion) const override`
- L196 _public function_ `virtual float GetVariantPriority() const override`
- L204 _public prototype_ `virtual void GetTextureFormats(const UTexture* Texture, TArray< TArray<FName> >& OutFormats) const;`

#### class `FAndroid_DefaultTargetPlatformControls`  
`class FAndroid_DefaultTargetPlatformControls : public FAndroid_ASTCTargetPlatformControls`  
_L209-216_
- inherits: `FAndroid_ASTCTargetPlatformControls`
- desc: Flavorless Android platform defaults to ASTC
- L212 _public function_ `FAndroid_DefaultTargetPlatformControls(bool bIsClient, ITargetPlatformSettings* TargetPlatformSettings) : FAndroid_ASTCTargetPlatformControls(bIsClient, TargetPlatformSettings, nullptr)`

#### class `FAndroid_ETC2TargetPlatformControls`  
`class FAndroid_ETC2TargetPlatformControls : public FAndroidTargetPlatformControls`  
_L218-241_
- inherits: `FAndroidTargetPlatformControls`
- L222 _public function_ `FAndroid_ETC2TargetPlatformControls(bool bIsClient, ITargetPlatformSettings* TargetPlatformSettings) : FAndroidTargetPlatformControls(bIsClient, TargetPlatformSettings, TEXT("ETC2"))`
- L226 _public function_ `virtual bool SupportedByExtensionsString(const FString& ExtensionsString, const int GLESVersion) const override`
- L231 _public function_ `virtual float GetVariantPriority() const override`
- L239 _public prototype_ `virtual void GetTextureFormats(const UTexture* Texture, TArray< TArray<FName> >& OutFormats) const;`

#### class `FAndroid_MultiTargetPlatformControls`  
`class FAndroid_MultiTargetPlatformControls : public FAndroidTargetPlatformControls`  
_L243-312_
- inherits: `FAndroidTargetPlatformControls`
- L245 _private member_ `TArray<FAndroidTargetPlatformControls*> FormatTargetPlatforms;`
- L246 _private member_ `FString FormatTargetString;`
- L249 _public function_ `FAndroid_MultiTargetPlatformControls(bool bIsClient, ITargetPlatformSettings* TargetPlatformSettings) : FAndroidTargetPlatformControls(bIsClient, TargetPlatformSettings, TEXT("Multi"))`
- L254 _public function_ `void LoadFormats(TArray<FAndroidTargetPlatformControls*> SingleFormatTPs)` — set up all of the multiple formats together into this one
- L302 _public function_ `virtual float GetVariantPriority() const override`
- L309 _public prototype_ `virtual void GetTextureFormats(const UTexture* Texture, TArray< TArray<FName> >& OutFormats) const;`
- L311 _public prototype_ `virtual FText DisplayName() const override;`

#### Free symbols / members of external scopes

- L259 _function_ `` (scope `FAndroid_MultiTargetPlatformControls::LoadFormats`)

### `Source/Developer/Android/AndroidTargetPlatformControls/Public/IAndroidTargetPlatformControlsModule.h` (Public)


#### class `IAndroidTargetPlatformControlsModule`  
`class IAndroidTargetPlatformControlsModule : public ITargetPlatformControlsModule`  
_L12-19_
- inherits: `ITargetPlatformControlsModule`
- L18 _public prototype_ `virtual void NotifyMultiSelectedFormatsChanged() = 0;` — Called by AndroidRuntimeSettings to notify us when the user changes the selected texture formats for the Multi format
