# Developer / MacTargetPlatformControls

- module root: `Source/Developer/Mac/MacTargetPlatformControls`
- headers: 2; symbols: 41
- symbol kinds: class=2, function=31, macro=1, member=4, prototype=1, typedef=2
- PrivateDependencyModuleNames: CookedEditor, Core, CoreUObject, DesktopPlatform, Engine, MacTargetPlatformSettings, TargetPlatform
- PrivateIncludePathModuleNames: Settings, TextureCompressor
- PublicIncludePathModuleNames: Engine

### `Source/Developer/Mac/MacTargetPlatformControls/Public/GenericMacTargetPlatformControls.h` (Public)


#### class `TGenericMacTargetPlatformControls`  
`template<bool HAS_EDITOR_DATA, bool IS_DEDICATED_SERVER, bool IS_CLIENT_ONLY> class TGenericMacTargetPlatformControls : public TTargetPlatformControlsBase<FMacPlatformProperties<HAS_EDITOR_DATA, IS_DEDICATED_SERVER, IS_CLIENT_ONLY> >`  
_L24-146_
- inherits: `TTargetPlatformControlsBase<FMacPlatformProperties<HAS_EDITOR_DATA,IS_DEDICATED_SERVER,IS_CLIENT_ONLY>>`
- desc: Template for Mac target platforms controls
- L29 _public typedef_ `typedef FMacPlatformProperties<HAS_EDITOR_DATA, IS_DEDICATED_SERVER, IS_CLIENT_ONLY> TProperties;`
- L30 _public typedef_ `typedef TTargetPlatformControlsBase<TProperties> TSuper;`
- L35 _public function_ `TGenericMacTargetPlatformControls(ITargetPlatformSettings* TargetPlatformSettings) : TSuper(TargetPlatformSettings)` — Default constructor.
- L48 _public function_ `virtual void EnableDeviceCheck(bool OnOff) override`
- L50 _public function_ `virtual void GetAllDevices( TArray<ITargetDevicePtr>& OutDevices ) const override`
- L59 _public function_ `virtual bool GenerateStreamingInstallManifest(const TMultiMap<FString, int32>& PakchunkMap, const TSet<int32>& PakchunkIndicesInUse) const override`
- L64 _public function_ `virtual ITargetDevicePtr GetDefaultDevice( ) const override`
- L74 _public function_ `virtual ITargetDevicePtr GetDevice( const FTargetDeviceId& DeviceId )`
- L85 _public function_ `virtual void GetPlatformSpecificProjectAnalytics( TArray<FAnalyticsEventAttribute>& AnalyticsParamArray ) const override`
- L94 _public function_ `virtual void GetTextureFormats( const UTexture* Texture, TArray< TArray<FName> >& OutFormats) const override`
- L103 _public function_ `virtual bool SupportsLQCompressionTextureFormat() const override`
- L105 _public function_ `virtual bool CanSupportRemoteShaderCompile() const override`
- L110 _public function_ `virtual void GetShaderCompilerDependencies(TArray<FString>& OutDependencies) const override`
- L119 _public function_ `virtual bool SupportsVariants() const override`
- L125 _public function_ `virtual float GetVariantPriority() const override`
- L135 _private member_ `ITargetDevicePtr LocalDevice;` — Holds the local device.
- L139 _private member_ `const UTextureLODSettings* TextureLODSettings;` — Holds the texture LOD settings.
- L142 _private member_ `FStaticMeshLODSettings StaticMeshLODSettings;` — Holds the static mesh LOD settings.

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "TGenericMacTargetPlatformControls"`

### `Source/Developer/Mac/MacTargetPlatformControls/Public/LocalMacTargetDevice.h` (Public)


#### class `FLocalMacTargetDevice`  
`class FLocalMacTargetDevice : public ITargetDevice`  
_L18-137_
- inherits: `ITargetDevice`
- desc: Template for local Mac target devices.
- L28 _public function_ `FLocalMacTargetDevice(const ITargetPlatformControls& InTargetPlatformControls) : TargetPlatformControls(InTargetPlatformControls)` — Creates and initializes a new device for the specified target platform. @param InTargetPlatform - The target platform.
- L35 _public function_ `virtual bool Connect( ) override`
- L40 _public function_ `virtual void Disconnect( )`
- L43 _public function_ `virtual ETargetDeviceTypes GetDeviceType( ) const override`
- L48 _public function_ `virtual FTargetDeviceId GetId( ) const override`
- L53 _public function_ `virtual FString GetName( ) const override`
- L58 _public function_ `virtual FString GetOperatingSystemName( ) override`
- L63 _public function_ `virtual int32 GetProcessSnapshot( TArray<FTargetDeviceProcessInfo>& OutProcessInfos ) override`
- L69 _public function_ `virtual const class ITargetPlatformSettings& GetPlatformSettings() const override`
- L73 _public function_ `virtual const class ITargetPlatformControls& GetPlatformControls() const override`
- L78 _public function_ `virtual bool IsConnected( )`
- L83 _public function_ `virtual bool IsDefault( ) const override`
- L88 _public function_ `virtual bool PowerOff( bool Force ) override`
- L93 _public function_ `virtual bool PowerOn( ) override`
- L98 _public prototype_ `virtual bool Reboot( bool bReconnect = false ) override;`
- L100 _public function_ `virtual bool SupportsFeature( ETargetDeviceFeatures Feature ) const override`
- L118 _public function_ `virtual void SetUserCredentials( const FString& UserName, const FString& UserPassword ) override`
- L122 _public function_ `virtual bool GetUserCredentials( FString& OutUserName, FString& OutUserPassword ) override`
- L127 _public function_ `virtual bool TerminateProcess( const int64 ProcessId ) override`
- L136 _private member_ `const ITargetPlatformControls& TargetPlatformControls;` — Holds a reference to the device's target platform.
