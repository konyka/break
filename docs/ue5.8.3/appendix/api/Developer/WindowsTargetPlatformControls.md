# Developer / WindowsTargetPlatformControls

- module root: `Source/Developer/Windows/WindowsTargetPlatfomControls`
- headers: 3; symbols: 71
- symbol kinds: class=3, function=56, macro=1, member=8, prototype=1, typedef=2
- PrivateDependencyModuleNames: AudioPlatformConfiguration, CookedEditor, Core, CoreUObject, DesktopPlatform, Engine, RHI, TargetPlatform, WindowsTargetPlatformSettings
- PrivateIncludePathModuleNames: Settings, TextureCompressor, WindowsTargetPlatformSettings
- PublicIncludePathModuleNames: AudioPlatformConfiguration, Engine

### `Source/Developer/Windows/WindowsTargetPlatfomControls/Public/GenericWindowsTargetPlatformControls.h` (Public)


#### class `TGenericWindowsTargetPlatformControls`  
`class TGenericWindowsTargetPlatformControls : public TTargetPlatformControlsBase<TProperties>`  
_L33-202_
- inherits: `TTargetPlatformControlsBase<TProperties>`
- L36 _public typedef_ `typedef TTargetPlatformControlsBase<TProperties> TSuper;`
- L37 _public typedef_ `typedef TTargetPlatformSettingsBase<TProperties> TSuperSettings;`
- L42 _public function_ `TGenericWindowsTargetPlatformControls(ITargetPlatformSettings* TargetPlatformSettings) : TSuper(TargetPlatformSettings)` — O * Default constructor.
- L64 _public function_ `virtual void EnableDeviceCheck(bool OnOff) override`
- L66 _public function_ `virtual void GetAllDevices( TArray<ITargetDevicePtr>& OutDevices ) const override`
- L91 _public function_ `virtual bool GenerateStreamingInstallManifest(const TMultiMap<FString, int32>& PakchunkMap, const TSet<int32>& PakchunkIndicesInUse) const override`
- L96 _public function_ `virtual ITargetDevicePtr GetDefaultDevice( ) const override`
- L106 _public function_ `virtual ITargetDevicePtr GetDevice( const FTargetDeviceId& DeviceId )`
- L132 _public function_ `virtual void GetShaderCompilerDependencies(TArray<FString>& OutDependencies) const override`
- L147 _public function_ `virtual void GetBuildProjectSettingKeys(FString& OutSection, TArray<FString>& InBoolKeys, TArray<FString>& InIntKeys, TArray<FString>& InStringKeys) const override`
- L154 _public function_ `virtual void GetPlatformSpecificProjectAnalytics( TArray<FAnalyticsEventAttribute>& AnalyticsParamArray ) const override`
- L172 _public function_ `virtual void GetTextureFormats( const UTexture* InTexture, TArray< TArray<FName> >& OutFormats) const override`
- L182 _public function_ `virtual bool SupportsVariants() const override`
- L187 _public function_ `virtual float GetVariantPriority() const override`
- L196 _private member_ `ITargetDevicePtr LocalDevice;` — Holds the local device.
- L198 _private member_ `TArray<ITargetDevicePtr> SteamDevices;`
- L199 _private member_ `TArray<ITargetDevicePtr> RemoteDevices;`
- L201 _private member_ `TSuperSettings* GenericWindowsTargetPlatformSettings;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "TGenericWindowsTargetPlatformControls"`

### `Source/Developer/Windows/WindowsTargetPlatfomControls/Public/LocalPcTargetDevice.h` (Public)


#### class `FLocalPcTargetDevice`  
`class FLocalPcTargetDevice : public ITargetDevice`  
_L19-327_
- inherits: `ITargetDevice`
- desc: Template for local PC target devices.
- L29 _public function_ `FLocalPcTargetDevice( const ITargetPlatformControls& InTargetPlatform ) : TargetPlatformControls(InTargetPlatform)` — Creates and initializes a new device for the specified target platform. @param InTargetPlatform - The target platform.
- L37 _public function_ `virtual bool Connect( ) override`
- L42 _public function_ `virtual void Disconnect( )`
- L45 _public function_ `virtual ETargetDeviceTypes GetDeviceType( ) const override`
- L55 _public function_ `virtual FTargetDeviceId GetId( ) const override`
- L60 _public function_ `virtual FString GetName( ) const override`
- L65 _public function_ `virtual FString GetOperatingSystemName( ) override`
- L70 _public function_ `virtual int32 GetProcessSnapshot( TArray<FTargetDeviceProcessInfo>& OutProcessInfos ) override`
- L193 _public function_ `virtual const class ITargetPlatformSettings& GetPlatformSettings() const override`
- L197 _public function_ `virtual const class ITargetPlatformControls& GetPlatformControls() const override`
- L202 _public function_ `virtual bool IsConnected( )`
- L207 _public function_ `virtual bool IsDefault( ) const override`
- L212 _public function_ `virtual bool PowerOff( bool Force ) override`
- L223 _public function_ `virtual bool PowerOn( ) override`
- L228 _public function_ `virtual bool Reboot( bool bReconnect = false ) override`
- L239 _public function_ `virtual bool SupportsFeature( ETargetDeviceFeatures Feature ) const override`
- L263 _public function_ `virtual void SetUserCredentials( const FString& UserName, const FString& UserPassword ) override`
- L267 _public function_ `virtual bool GetUserCredentials( FString& OutUserName, FString& OutUserPassword ) override`
- L272 _public function_ `virtual bool TerminateProcess( const int64 ProcessId ) override`
- L295 _protected function_ `bool AdjustShutdownPrivileges( )` — Adjusts shutdown privileges for the local host PC. @return true on success, false otherwise.
- L323 _protected member_ `TMap<FGuid, void*> Processes;` — Holds the collection of processes that were started using the Run() method.
- L326 _protected member_ `const ITargetPlatformControls& TargetPlatformControls;` — Holds a reference to the device's target platform.

### `Source/Developer/Windows/WindowsTargetPlatfomControls/Public/RemoteWindowsDevice.h` (Public)


#### class `FRemoteWindowsDevice`  
`class FRemoteWindowsDevice : public ITargetDevice`  
_L32-191_
- inherits: `ITargetDevice`
- L35 _public function_ `FRemoteWindowsDevice(const ITargetPlatformControls& InTargetPlatformControls, const FString& InDeviceName) : TargetPlatformControls(InTargetPlatformControls) , DeviceName(InDeviceName)`
- L41 _public function_ `virtual bool Connect() override`
- L46 _public function_ `virtual void Disconnect() override`
- L50 _public function_ `virtual ETargetDeviceTypes GetDeviceType() const override`
- L55 _public function_ `virtual FTargetDeviceId GetId() const override`
- L60 _public function_ `virtual FString GetName() const override`
- L65 _public function_ `virtual FString GetOperatingSystemName() override`
- L71 _public function_ `virtual int32 GetProcessSnapshot(TArray<FTargetDeviceProcessInfo>& OutProcessInfos) override`
- L76 _public function_ `virtual const class ITargetPlatformSettings& GetPlatformSettings() const override`
- L81 _public function_ `virtual const class ITargetPlatformControls& GetPlatformControls() const override`
- L86 _public function_ `virtual bool IsConnected() override`
- L91 _public function_ `virtual bool IsDefault() const override`
- L96 _public function_ `virtual bool PowerOff(bool Force) override`
- L101 _public function_ `virtual bool PowerOn() override`
- L106 _public function_ `virtual bool Reboot(bool bReconnect = false) override`
- L111 _public function_ `virtual bool SupportsFeature(ETargetDeviceFeatures Feature) const override`
- L116 _public function_ `virtual bool TerminateProcess(const int64 ProcessId) override`
- L121 _public function_ `virtual bool TerminateLaunchedProcess(const FString& ProcessIdentifier)`
- L127 _public function_ `virtual void SetUserCredentials(const FString& UserName, const FString& UserPassword) override`
- L129 _public function_ `virtual bool GetUserCredentials(FString& OutUserName, FString& OutUserPassword) override`
- L134 _public function_ `static TArray<FString> GetAllRemoteDeviceNames()`
- L147 _public function_ `static TArray<ITargetDevicePtr> DiscoverDevices(const ITargetPlatformControls& TargetPlatformControls)`
- L159 _private function_ `bool RunWdRemote( const FString& Parameters ) const`
- L164 _private function_ `static bool RunWdRemote( const FString& Parameters, const FString& DeviceName )`
- L189 _private member_ `const ITargetPlatformControls& TargetPlatformControls;`
- L190 _private member_ `FString DeviceName;`

#### Free symbols / members of external scopes

- L14 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogRemoteWindowsTargetDevice, Log, All);`
