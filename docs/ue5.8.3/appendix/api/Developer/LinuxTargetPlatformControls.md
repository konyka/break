# Developer / LinuxTargetPlatformControls

- module root: `Source/Developer/Linux/LinuxTargetPlatformControls`
- headers: 2; symbols: 75
- symbol kinds: class=6, function=54, macro=1, member=11, typedef=3
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, Engine, LinuxTargetPlatformSettings, Projects, TargetPlatform
- PrivateIncludePathModuleNames: Settings, TextureCompressor
- PublicIncludePathModuleNames: Engine

### `Source/Developer/Linux/LinuxTargetPlatformControls/Public/LinuxTargetDevice.h` (Public)


#### class `FLinuxTargetDevice`  
`class FLinuxTargetDevice : public ITargetDevice`  
_L36-223_
- inherits: `ITargetDevice`
- desc: Implements a Linux target device.
- L46 _public function_ `FLinuxTargetDevice(const ITargetPlatformControls& InTargetPlatformControls, const FString& InDeviceName, TFunction<void()> InSavePlatformDevices) : TargetPlatformControls(InTargetPlatformControls) , DeviceName(InDeviceName) , SavePlatformDevices(InSavePlatformDevices)` — Creates and initializes a new device for the specified target platform. @param InTargetPlatformControls - The target platform controls.
- L54 _public function_ `FLinuxTargetDevice(const ITargetPlatformControls& InTargetPlatformControls) : FLinuxTargetDevice(InTargetPlatformControls, TEXT("UnknownName"), nullptr)` — Minimal constructor for use with SteamDeck devices
- L60 _public function_ `virtual bool Connect( ) override`
- L65 _public function_ `virtual void Disconnect( ) override`
- L68 _public function_ `virtual ETargetDeviceTypes GetDeviceType( ) const override`
- L73 _public function_ `virtual FTargetDeviceId GetId() const override`
- L78 _public function_ `virtual FString GetName( ) const override`
- L83 _public function_ `virtual FString GetOperatingSystemName( ) override`
- L88 _public function_ `virtual int32 GetProcessSnapshot( TArray<FTargetDeviceProcessInfo>& OutProcessInfos ) override`
- L94 _public function_ `virtual const class ITargetPlatformSettings& GetPlatformSettings() const override`
- L98 _public function_ `virtual const class ITargetPlatformControls& GetPlatformControls() const override`
- L103 _public function_ `virtual bool IsConnected( ) override`
- L108 _public function_ `virtual bool IsDefault( ) const override`
- L113 _public function_ `virtual bool PowerOff( bool Force ) override`
- L118 _public function_ `virtual bool PowerOn( ) override`
- L123 _public function_ `virtual bool Reboot( bool bReconnect = false ) override`
- L129 _public function_ `virtual bool SupportsFeature( ETargetDeviceFeatures Feature ) const override`
- L156 _public function_ `virtual void SetUserCredentials( const FString& InUserName, const FString& InUserPassword ) override`
- L167 _public function_ `virtual bool GetUserCredentials( FString& OutUserName, FString& OutUserPassword ) override`
- L174 _public function_ `virtual bool TerminateProcess( const int64 ProcessId ) override`
- L210 _protected member_ `const ITargetPlatformControls& TargetPlatformControls;` — Holds a reference to the device's target platform.
- L213 _protected member_ `FString DeviceName;` — Device display name
- L216 _protected member_ `FString UserName;` — User name on the remote machine
- L219 _protected member_ `FString UserPassword;` — User password on the remote machine
- L222 _protected member_ `TFunction<void()> SavePlatformDevices;` — Target platform function to save device state

#### Free symbols / members of external scopes

- L25 _typedef_ `typedef TSharedPtr<class FLinuxTargetDevice, ESPMode::ThreadSafe> FLinuxTargetDevicePtr;` — Type definition for shared pointers to instances of FLinuxTargetDevice.
- L30 _typedef_ `typedef TSharedRef<class FLinuxTargetDevice, ESPMode::ThreadSafe> FLinuxTargetDeviceRef;` — Type definition for shared references to instances of FLinuxTargetDevice.

### `Source/Developer/Linux/LinuxTargetPlatformControls/Public/LinuxTargetPlatformControls.h` (Public)


#### class `TLinuxTargetPlatformControls`  
`template<typename TProperties> class TLinuxTargetPlatformControls : public TTargetPlatformControlsBase<TProperties>`  
_L28-402_
- inherits: `TTargetPlatformControlsBase<TProperties>`
- desc: Template for Linux target platforms controls
- L33 _public typedef_ `typedef TTargetPlatformControlsBase<TProperties> TSuper;`
- L38 _public function_ `TLinuxTargetPlatformControls(const PlatformInfo::FTargetPlatformInfo* const InPlatformInfo, ITargetPlatformSettings* TargetPlatformSettings) : TSuper(InPlatformInfo ? InPlatformInfo : new PlatformInfo::FTargetPlatformInfo( TProperties::IniPlatformName(), TProperties::HasEditorOnlyData() ? EBuildTargetType::Editor : TProperties::IsServerOnly() ? EBuildTargetType::Server : TProperties::IsClientOnly() ? EBuildTargetType::Client : EBuildTargetType::Game, TEXT("")), TargetPlatformSettings) #if WITH_ENGINE , bChangingDeviceConfig(false) #endif` — Default constructor.
- L72 _public function_ `TLinuxTargetPlatformControls(ITargetPlatformSettings* TargetPlatformSettings) : TLinuxTargetPlatformControls(nullptr, TargetPlatformSettings)` — Forward this one on to the version that can create a new PlatformInfo for us.  This allows us to specify a PlatformInfo with a CookFlavor in derived templates, but not have to specify the nullptr manually to keep the code compact
- L81 _public function_ `virtual FString PlatformName() const override`
- L87 _public function_ `virtual void EnableDeviceCheck(bool OnOff) override`
- L89 _public function_ `virtual FString CookingDeviceProfileName() const override`
- L95 _public function_ `virtual bool AddDevice(const FString& DeviceName, bool bDefault) override`
- L100 _public function_ `virtual bool AddDevice(const FString& DeviceName, const FString& DeviceUserFriendlyName, const FString& Username, const FString& Password, bool bDefault) override`
- L128 _public function_ `virtual void GetAllDevices(TArray<ITargetDevicePtr>& OutDevices) const override`
- L151 _public function_ `virtual bool GenerateStreamingInstallManifest(const TMultiMap<FString, int32>& PakchunkMap, const TSet<int32>& PakchunkIndicesInUse) const override`
- L156 _public function_ `virtual ITargetDevicePtr GetDefaultDevice() const override`
- L166 _public function_ `virtual ITargetDevicePtr GetDevice(const FTargetDeviceId& DeviceId) override`
- L192 _public function_ `virtual bool IsSdkInstalled(bool bProjectHasCode, FString& OutDocumentationPath) const override`
- L227 _public function_ `virtual int32 CheckRequirements(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FString& OutTutorialPath, FString& OutDocumentationPath, FText& CustomizedLogMessage) const override`
- L249 _public function_ `virtual void GetPlatformSpecificProjectAnalytics(TArray<FAnalyticsEventAttribute>& AnalyticsParamArray) const override`
- L258 _public function_ `virtual void GetTextureFormats(const UTexture* InTexture, TArray< TArray<FName> >& OutFormats) const override`
- L286 _public function_ `virtual bool SupportsVariants() const override`
- L291 _public function_ `virtual float GetVariantPriority() const override`
- L302 _protected member_ `bool bChangingDeviceConfig;` — Whether we're in process of changing device config - if yes, we will prevent recurrent calls.
- L304 _protected function_ `void InitDevicesFromConfig()`
- L352 _protected function_ `void SaveDevicesToConfig()`
- L398 _protected member_ `FLinuxTargetDevicePtr LocalDevice;` — Holds the local device.
- L400 _protected member_ `TMap<FString, FLinuxTargetDevicePtr> Devices;` — Holds a map of valid devices.
- L401 _protected member_ `TArray<ITargetDevicePtr> SteamDevices;`

#### class `TLinuxDXTTargetPlatformControls`  
`template<typename TProperties> class TLinuxDXTTargetPlatformControls : public TLinuxTargetPlatformControls<TProperties>`  
_L405-427_
- inherits: `TLinuxTargetPlatformControls<TProperties>`
- L409 _public function_ `TLinuxDXTTargetPlatformControls(ITargetPlatformSettings* TargetPlatformSettings) : TLinuxTargetPlatformControls<TProperties>(new PlatformInfo::FTargetPlatformInfo( TProperties::IniPlatformName(), TProperties::HasEditorOnlyData() ? EBuildTargetType::Editor : TProperties::IsServerOnly() ? EBuildTargetType::Server : TProperties::IsClientOnly() ? EBuildTargetType::Client : EBuildTargetType::Game, TEXT("DXT")), TargetPlatformSettings)`
- L421 _public function_ `virtual float GetVariantPriority() const override`

#### class `TLinuxASTCTargetPlatformControls`  
`template<typename TProperties> class TLinuxASTCTargetPlatformControls : public TLinuxTargetPlatformControls<TProperties>`  
_L430-491_
- inherits: `TLinuxTargetPlatformControls<TProperties>`
- L434 _public function_ `TLinuxASTCTargetPlatformControls(ITargetPlatformSettings* TargetPlatformSettings) : TLinuxTargetPlatformControls<TProperties>(new PlatformInfo::FTargetPlatformInfo( TProperties::IniPlatformName(), TProperties::HasEditorOnlyData() ? EBuildTargetType::Editor : TProperties::IsServerOnly() ? EBuildTargetType::Server : TProperties::IsClientOnly() ? EBuildTargetType::Client : EBuildTargetType::Game, TEXT("ASTC")), TargetPlatformSettings)`
- L446 _public function_ `virtual float GetVariantPriority() const override`
- L454 _public function_ `virtual void GetTextureFormats(const UTexture* InTexture, TArray< TArray<FName> >& OutFormats) const override`

#### class `TLinuxETC2TargetPlatformControls`  
`template<typename TProperties> class TLinuxETC2TargetPlatformControls : public TLinuxTargetPlatformControls<TProperties>`  
_L494-542_
- inherits: `TLinuxTargetPlatformControls<TProperties>`
- L498 _public function_ `TLinuxETC2TargetPlatformControls(ITargetPlatformSettings* TargetPlatformSettings) : TLinuxTargetPlatformControls<TProperties>(new PlatformInfo::FTargetPlatformInfo( TProperties::IniPlatformName(), TProperties::HasEditorOnlyData() ? EBuildTargetType::Editor : TProperties::IsServerOnly() ? EBuildTargetType::Server : TProperties::IsClientOnly() ? EBuildTargetType::Client : EBuildTargetType::Game, TEXT("ETC2")), TargetPlatformSettings)`
- L510 _public function_ `virtual float GetVariantPriority() const override`
- L518 _public function_ `virtual void GetTextureFormats(const UTexture* InTexture, TArray< TArray<FName> >& OutFormats) const override`

#### class `TLinuxMultiTargetPlatformControls`  
`template<typename TProperties> class TLinuxMultiTargetPlatformControls : public TLinuxTargetPlatformControls<TProperties>`  
_L545-653_
- inherits: `TLinuxTargetPlatformControls<TProperties>`
- L548 _private member_ `TArray<ITargetPlatformControls*> FormatTargetPlatforms;`
- L549 _private member_ `FString FormatTargetString;`
- L552 _public function_ `TLinuxMultiTargetPlatformControls(ITargetPlatformSettings* InTargetPlatformSettings) : TLinuxTargetPlatformControls<TProperties>(new PlatformInfo::FTargetPlatformInfo( TProperties::IniPlatformName(), TProperties::HasEditorOnlyData() ? EBuildTargetType::Editor : TProperties::IsServerOnly() ? EBuildTargetType::Server : TProperties::IsClientOnly() ? EBuildTargetType::Client : EBuildTargetType::Game, TEXT("Multi")), InTargetPlatformSettings)`
- L566 _public function_ `void LoadFormats(TArray<ITargetPlatformControls*> SingleFormatTPs)` — Set up which formats to include based on bMultiTargetFormat_* config keys. Pass all single-format target platform controls; this will filter and deduplicate them.
- L624 _public function_ `virtual float GetVariantPriority() const override`
- L631 _public function_ `virtual void GetTextureFormats(const UTexture* InTexture, TArray< TArray<FName> >& OutFormats) const override`
- L646 _public function_ `virtual FText DisplayName() const override`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LOCTEXT_NAMESPACE "TLinuxTargetPlatformControls"`
- L112 _function_ `[&]()` (scope `TLinuxTargetPlatformControls::AddDevice`)
- L571 _function_ `` (scope `TLinuxMultiTargetPlatformControls::LoadFormats`)
