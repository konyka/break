# Developer / TargetPlatform

- module root: `Source/Developer/TargetPlatform`
- headers: 23; symbols: 776
- symbol kinds: class=29, delegate=5, enum=9, enumerator=70, function=320, macro=2, member=46, namespace=8, prototype=266, struct=5, typedef=6, variable=10
- DynamicallyLoadedModuleNames: AudioFormatADPCM, AudioFormatBink, AudioFormatOgg, AudioFormatOpus, AudioFormatRad, ImageWrapper, ShaderFormatD3D, ShaderFormatOpenGL, ShaderFormatVectorVM, ShaderPreprocessor, TextureFormatOodle, TextureFormatUncompressed, TurnkeySupport
- PrivateDependencyModuleNames: Core, Engine, Json, Projects, RenderCore, Slate, SlateCore
- PrivateIncludePathModuleNames: Engine, PhysicsCore, TurnkeySupport
- PublicDependencyModuleNames: Analytics, AudioPlatformConfiguration, DesktopPlatform, DeveloperSettings, RHI, TextureFormat
- PublicIncludePathModuleNames: TextureFormat

### `Source/Developer/TargetPlatform/Private/DeviceBrowserDefaultPlatformWidgetCreator.h` (Private)


#### class `FDeviceBrowserDefaultPlatformWidgetCreator`  
`class FDeviceBrowserDefaultPlatformWidgetCreator : public IDeviceManagerCustomPlatformWidgetCreator`  
_L8-17_
- inherits: `IDeviceManagerCustomPlatformWidgetCreator`
- L11 _public prototype_ `virtual TSharedPtr<SWidget> CreateAddDeviceWidget(const FString& InPlatformName) override;`
- L12 _public prototype_ `virtual bool IsAddDeviceInputValid(const FString& InPlatformName, const TSharedPtr<SWidget>& UserData) override;`
- L14 _public prototype_ `virtual TSharedPtr<SWidget> CreateDeviceInfoWidget(const FString& InPlatformName, const ITargetDevicePtr& InDevice) override;`
- L16 _public prototype_ `virtual void AddDevice(const FString& InPlatformName, const TSharedPtr<SWidget>& UserData) override;`

### `Source/Developer/TargetPlatform/Private/SDeviceBrowserDefaultPlatformAddWidget.h` (Private)


#### class `SDeviceBrowserDefaultPlatformAddWidget`  
`class SDeviceBrowserDefaultPlatformAddWidget : public SCompoundWidget`  
_L18-52_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SDeviceBrowserDefaultPlatformAddWidget)`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, const FString& InPlatformName);` — Construct the widget. @param InArgs The construction arguments. @param InDeviceManager The target device manager to use.
- L36 _public prototype_ `bool IsInputValid(const FString& InPlatformName);` — Checks if input user provided in all fields is valid
- L39 _public member_ `TSharedPtr<SEditableTextBox> DeviceIdTextBox;` — The device identifier text box.
- L42 _public member_ `TSharedPtr<SEditableTextBox> DeviceNameTextBox;` — The device name text box.
- L45 _public member_ `TSharedPtr<SEditableTextBox> UserNameTextBox;` — The user name text box.
- L48 _public member_ `TSharedPtr<SEditableTextBox> UserPasswordTextBox;` — The user password text box.
- L51 _public member_ `TSharedPtr<SOverlay> UserDataOverlay;` — The turnable overlay with user data.

### `Source/Developer/TargetPlatform/Public/Common/TargetPlatformBase.h` (Public)


#### class `FTargetPlatformBase`  
`class UE_DEPRECATED(5.5, "FTargetPlatformBase is deprecated, please use FTargetPlatformControlsBase(SDK required to build) or FTargetPlatformSettingsBase(no SDK required).") FTargetPlatformBase : public ITargetPlatform`  
_L39-312_
- inherits: `ITargetPlatform`
- desc: Base class for target platforms.
- L46 _public function_ `virtual bool AddDevice( const FString& DeviceName, bool bDefault ) override`
- L51 _public function_ `virtual bool AddDevice(const FString& DeviceId, const FString& DeviceUserFriendlyName, const FString& Username, const FString& Password, bool bDefault) override`
- L56 _public function_ `virtual FText DisplayName() const override`
- L61 _public function_ `virtual const PlatformInfo::FTargetPlatformInfo& GetTargetPlatformInfo() const override`
- L66 _public function_ `virtual const FDataDrivenPlatformInfo& GetPlatformInfo() const override`
- L71 _public function_ `virtual FConfigCacheIni* GetConfigSystem() const override`
- L76 _public prototype_ `virtual bool IsEnabledForPlugin(const IPlugin& Plugin) const override;`
- L78 _public prototype_ `virtual bool UsesForwardShading() const override;`
- L80 _public prototype_ `virtual bool UsesDBuffer() const override;`
- L83 _public prototype_ `virtual bool UsesBasePassVelocity() const override;` — `UE_DEPRECATED(5.1, "Use IsUsingBasePassVelocity(EShaderPlatform Platform) in renderutils that will uses FShaderPlatformCachedIniValue to retrieve the cvar value per platform.")`
- L85 _public prototype_ `virtual bool VelocityEncodeDepth() const override;`
- L87 _public prototype_ `virtual bool UsesSelectiveBasePassOutputs() const override;`
- L89 _public prototype_ `virtual bool ShouldStripNaniteFallbackMeshes() const override;`
- L91 _public prototype_ `virtual bool UsesDistanceFields() const override;`
- L93 _public prototype_ `virtual bool UsesRayTracing() const override;`
- L95 _public prototype_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const override;`
- L97 _public prototype_ `virtual uint32 GetSupportedHardwareMask() const override;`
- L99 _public prototype_ `virtual EOfflineBVHMode GetStaticMeshOfflineBVHMode() const override;`
- L101 _public prototype_ `virtual bool GetStaticMeshOfflineBVHCompression() const override;`
- L103 _public prototype_ `virtual EOfflineBVHMode GetSkeletalMeshOfflineBVHMode() const override;`
- L105 _public prototype_ `virtual bool ForcesSimpleSkyDiffuse() const override;`
- L107 _public prototype_ `virtual float GetDownSampleMeshDistanceFieldDivider() const override;`
- L109 _public prototype_ `virtual int32 GetHeightFogModeForOpaque() const override;`
- L111 _public prototype_ `virtual bool UsesMobileDBuffer() const override;`
- L113 _public prototype_ `virtual bool UsesASTCHDR() const override;`
- L115 _public prototype_ `virtual FName GetFallbackASTCHDR() const override;`
- L117 _public prototype_ `virtual void GetRayTracingShaderFormats(TArray<FName>& OutFormats) const override;`
- L119 _public prototype_ `virtual void GetPlatformSpecificProjectAnalytics( TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray ) const override;`
- L122 _public function_ `virtual void GetReflectionCaptureFormats( TArray<FName>& OutFormats ) const override`
- L127 _public function_ `virtual FName FinalizeVirtualTextureLayerFormat(FName Format) const override`
- L132 _public function_ `virtual bool SupportsLQCompressionTextureFormat() const override`
- L136 _public function_ `virtual bool PackageBuild( const FString& InPackgeDirectory ) override`
- L141 _public function_ `virtual bool CanSupportRemoteShaderCompile() const override`
- L146 _public function_ `virtual void GetShaderCompilerDependencies(TArray<FString>& OutDependencies) const override`
- L151 _public function_ `static void AddDependencySCArrayHelper(TArray<FString>& OutDependencies, const FString& DependencyRelativePath)` — Helper method to fill a dependencies array for the shader compiler with absolute paths, passing a relative path to the Engine as the parameter.
- L159 _public function_ `virtual bool IsSdkInstalled(bool bProjectHasCode, FString& OutDocumentationPath) const override`
- L164 _public function_ `virtual int32 CheckRequirements(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FString& OutTutorialPath, FString& OutDocumentationPath, FText& CustomizedLogMessage) const override`
- L174 _public prototype_ `virtual bool RequiresTempTarget(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FText& OutReason) const override;`
- L176 _public function_ `virtual bool SupportsValueForType(FName SupportedType, FName RequiredSupportedValue) const override`
- L189 _public function_ `virtual bool SupportsVariants() const override`
- L194 _public function_ `virtual float GetVariantPriority() const override`
- L199 _public function_ `virtual bool SendLowerCaseFilePaths() const override`
- L204 _public function_ `virtual bool AllowsEditorObjects() const override`
- L209 _public function_ `virtual bool AllowsDevelopmentObjects() const override`
- L214 _public function_ `virtual void GetBuildProjectSettingKeys(FString& OutSection, TArray<FString>& InBoolKeys, TArray<FString>& InIntKeys, TArray<FString>& InStringKeys) const override`
- L219 _public function_ `virtual int32 GetPlatformOrdinal() const override`
- L224 _public prototype_ `virtual TSharedPtr<IDeviceManagerCustomPlatformWidgetCreator> GetCustomWidgetCreator() const override;`
- L226 _public function_ `virtual bool ShouldExpandTo32Bit(const uint16* Indices, const int32 NumIndices) const override`
- L232 _public function_ `virtual bool AllowAudioVisualData() const override`
- L237 _public function_ `virtual bool AllowObject(const class UObject* Object) const override`
- L242 _public function_ `virtual FName GetMeshBuilderModuleName() const override`
- L249 _public function_ `virtual void GetShaderFormatModuleHints(TArray<FName>& OutModuleNames) const override`
- L253 _public function_ `virtual void GetTextureFormatModuleHints(TArray<FName>& OutModuleNames) const override`
- L258 _public prototype_ `virtual void GetTextureSizeLimits(uint64 & OutMaximumSurfaceBytes, uint64 & OutMaximumPackageBytes) const override;` — beware this is duplicated between TargetPlatformBase and TargetPlatformControlsBase
- L260 _public prototype_ `virtual FName GetWaveFormat(const class USoundWave* Wave) const override;`
- L262 _public prototype_ `virtual void GetAllWaveFormats(TArray<FName>& OutFormats) const override;`
- L264 _public prototype_ `virtual void GetWaveFormatModuleHints(TArray<FName>& OutModuleNames) const override;`
- L268 _public function_ `virtual bool CopyFileToTarget(const FString& TargetAddress, const FString& HostFilename, const FString& TargetFilename, const TMap<FString,FString>& CustomPlatformData) override`
- L273 _public function_ `virtual void InitializeForCook() override`
- L278 _public function_ `virtual void GetExtraPackagesToCook(TArray<FName>& PackageNames) const override`
- L283 _public function_ `virtual bool InitializeHostPlatform()`
- L292 _protected prototype_ `FTargetPlatformBase(const PlatformInfo::FTargetPlatformInfo *const InPlatformInfo);`
- L295 _protected member_ `const PlatformInfo::FTargetPlatformInfo *PlatformInfo;` — Information about this platform
- L296 _protected member_ `int32 PlatformOrdinal;`
- L298 _protected prototype_ `const Audio::FAudioFormatSettings& GetAudioFormatSettings() const;`
- L301 _protected prototype_ `static void AppendAnalyticsEventConfigBool( TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr );` — Analytics helper functions
- L302 _protected prototype_ `static void AppendAnalyticsEventConfigInt( TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr );`
- L303 _protected prototype_ `static void AppendAnalyticsEventConfigFloat( TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr );`
- L304 _protected prototype_ `static void AppendAnalyticsEventConfigString( TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr );`
- L305 _protected prototype_ `static void AppendAnalyticsEventConfigArray( TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr );`
- L308 _private member_ `TPimplPtr<Audio::FAudioFormatSettings> AudioFormatSettings;`
- L310 _private prototype_ `bool HasDefaultBuildSettings() const;`
- L311 _private prototype_ `static bool DoProjectSettingsMatchDefault(const FString& InPlatformName, const FString& InSection, const TArray<FString>* InBoolKeys, const TArray<FString>* InIntKeys, const TArray<FString>* InStringKeys);`

#### class `TTargetPlatformBase`  
`template<typename TPlatformProperties> class UE_DEPRECATED(5.5, "TTargetPlatformBase is deprecated, please use TTargetPlatformControlsBase(SDK required to build) or TTargetPlatformSettingsBase(no SDK required).") TTargetPlatformBase : public FTargetPlatformBase`  
_L321-551_
- inherits: `FTargetPlatformBase`
- desc: Template for target platforms. @param TPlatformProperties Type of platform properties.
- L330 _public function_ `static bool IsUsable()` — Returns true if the target platform will be able to be  initialized with an FPlatformInfo. Because FPlatformInfo now comes from a .ini file, it's possible that the .dll exists, but the .ini does not (should be uncommon, but is necessary to be handled)
- L340 _public function_ `TTargetPlatformBase(PlatformInfo::FTargetPlatformInfo* PremadePlatformInfo) : FTargetPlatformBase(PremadePlatformInfo)` — Constructor that already has a TPI (notably coming from TNonDesktopTargetPlatform)
- L350 _public function_ `TTargetPlatformBase() : TTargetPlatformBase( new PlatformInfo::FTargetPlatformInfo( TPlatformProperties::IniPlatformName(), TPlatformProperties::HasEditorOnlyData() ? EBuildTargetType::Editor : TPlatformProperties::IsServerOnly() ? EBuildTargetType::Server : TPlatformProperties::IsClientOnly() ? EBuildTargetType::Client : EBuildTargetType::Game, TEXT("")) )` — Constructor that makes a TPI based solely on TPlatformProperties
- L366 _public function_ `virtual bool HasEditorOnlyData() const override`
- L371 _public function_ `virtual bool IsLittleEndian() const override`
- L376 _public function_ `virtual bool IsServerOnly() const override`
- L381 _public function_ `virtual bool IsClientOnly() const override`
- L386 _public function_ `virtual FString PlatformName() const override`
- L394 _public function_ `virtual FString IniPlatformName() const override`
- L399 _public function_ `virtual FString CookingDeviceProfileName() const override`
- L405 _public function_ `virtual bool RequiresCookedData() const override`
- L410 _public function_ `virtual bool RequiresOriginalReleaseVersionForPatch() const override`
- L415 _public function_ `virtual bool HasNonTrivialPatchGeneration() const override`
- L420 _public function_ `virtual bool HasSecurePackageFormat() const override`
- L425 _public function_ `virtual EPlatformAuthentication RequiresUserCredentials() const override`
- L437 _public function_ `virtual bool SupportsBuildTarget( EBuildTargetType TargetType ) const override`
- L442 _public function_ `virtual EBuildTargetType GetRuntimePlatformType() const override`
- L452 _public function_ `virtual bool SupportsAutoSDK() const override`
- L457 _public function_ `virtual bool SupportsFeature( ETargetPlatformFeatures Feature ) const override`
- L525 _public function_ `virtual FName GetZlibReplacementFormat() const override`
- L530 _public function_ `virtual int64 GetMemoryMappingAlignment() const override`
- L535 _public function_ `virtual bool UsesRayTracing() const override`
- L546 _public function_ `virtual FName GetPhysicsFormat( class UBodySetup* Body ) const override`

#### class `TNonDesktopTargetPlatformBase`  
`template<typename TPlatformProperties> class UE_DEPRECATED(5.5, "TNonDesktopTargetPlatformBase is deprecated, please use TNonDesktopTargetPlatformControlsBase.") TNonDesktopTargetPlatformBase : public TTargetPlatformBase<TPlatformProperties>`  
_L555-617_
- inherits: `TTargetPlatformBase<TPlatformProperties>`
- L565 _public function_ `TNonDesktopTargetPlatformBase(bool bInIsClientOnly, const TCHAR* CookFlavor=nullptr, const TCHAR* OverrideIniPlatformName=nullptr) : TTargetPlatformBase<TPlatformProperties>(new PlatformInfo::FTargetPlatformInfo( OverrideIniPlatformName ? FString(OverrideIniPlatformName) : FString(TPlatformProperties::IniPlatformName()), bInIsClientOnly ? EBuildTargetType::Client : EBuildTargetType::Game, CookFlavor)) , bIsClientOnly(bInIsClientOnly)` — A simplified version for TPs that never will have Editor or ServerOnly versions, potentially multiple CookFlavors, as well as IN VERY RARE CASES, a different runtime IniPlatformName than what is passed in here (an example being TVOS and IOS, where passing in TVOS properties is very complicated) Note that if we delayed the Info creation, we could just use this->IniPlatformName() and override that in, say TVOS, but we can't call a virtual here, so we pass it up into the ctor
- L575 _public function_ `virtual FString PlatformName() const override`
- L581 _public function_ `virtual FString IniPlatformName() const override`
- L587 _public function_ `virtual FString CookingDeviceProfileName() const override`
- L593 _public function_ `virtual bool HasEditorOnlyData() const override`
- L598 _public function_ `virtual bool IsServerOnly() const override`
- L603 _public function_ `virtual bool IsClientOnly() const override`
- L608 _public function_ `virtual bool IsRunningPlatform() const override`
- L616 _protected member_ `bool bIsClientOnly;` — true if this target platform is client-only, ie strips out server stuff

#### class `FTargetPlatformMerged`  
`class FTargetPlatformMerged final : public ITargetPlatform`  
_L621-1020_
- inherits: `ITargetPlatform`
- desc: Redirect everything to TPS or TPC
- L625 _public function_ `FTargetPlatformMerged(ITargetPlatformSettings* InTargetPlatformSettings, ITargetPlatformControls* InTargetPlatformControls) : TargetPlatformSettings(InTargetPlatformSettings) , TargetPlatformControls(InTargetPlatformControls)`
- L631 _public function_ `virtual bool AddDevice(const FString& DeviceName, bool bDefault) override`
- L635 _public function_ `virtual bool AddDevice(const FString& DeviceId, const FString& DeviceUserFriendlyName, const FString& Username, const FString& Password, bool bDefault) override`
- L639 _public function_ `virtual FString PlatformName() const override`
- L643 _public function_ `virtual FText DisplayName() const override`
- L647 _public function_ `virtual int32 CheckRequirements(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FString& OutTutorialPath, FString& OutDocumentationPath, FText& CustomizedLogMessage) const override`
- L651 _public function_ `virtual bool RequiresTempTarget(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FText& OutReason) const override`
- L655 _public function_ `virtual const PlatformInfo::FTargetPlatformInfo& GetTargetPlatformInfo() const override`
- L659 _public function_ `virtual const FDataDrivenPlatformInfo& GetPlatformInfo() const override`
- L663 _public function_ `virtual FConfigCacheIni* GetConfigSystem() const override`
- L667 _public function_ `virtual FString IniPlatformName() const override`
- L671 _public function_ `virtual FString CookingDeviceProfileName() const override`
- L675 _public function_ `virtual void EnableDeviceCheck(bool OnOff) override`
- L679 _public function_ `virtual void GetAllDevices(TArray<ITargetDevicePtr>& OutDevices) const override`
- L683 _public function_ `virtual void RefreshAllDevices() override`
- L687 _public function_ `virtual FName GetZlibReplacementFormat() const override`
- L691 _public function_ `virtual int64 GetMemoryMappingAlignment() const override`
- L695 _public function_ `virtual bool GenerateStreamingInstallManifest(const TMultiMap<FString, int32>& PakchunkMap, const TSet<int32>& PakchunkIndicesInUse) const override`
- L699 _public function_ `virtual ITargetDevicePtr GetDefaultDevice() const override`
- L703 _public function_ `virtual ITargetDevicePtr GetDevice(const FTargetDeviceId& DeviceId) override`
- L707 _public function_ `virtual bool HasEditorOnlyData() const override`
- L711 _public function_ `virtual bool AllowsEditorObjects() const override`
- L715 _public function_ `virtual bool AllowsDevelopmentObjects() const override`
- L719 _public function_ `virtual bool IsClientOnly() const override`
- L723 _public function_ `virtual bool IsLittleEndian() const override`
- L727 _public function_ `virtual bool IsRunningPlatform() const override`
- L731 _public function_ `virtual bool IsServerOnly() const override`
- L735 _public function_ `virtual bool IsEnabledForPlugin(const IPlugin& Plugin) const override`
- L739 _public function_ `virtual bool CanSupportRemoteShaderCompile() const override`
- L743 _public function_ `virtual void GetShaderCompilerDependencies(TArray<FString>& OutDependencies) const override`
- L747 _public function_ `virtual bool IsSdkInstalled(bool bProjectHasCode, FString& OutDocumentationPath) const override`
- L751 _public function_ `virtual bool RequiresCookedData() const override`
- L755 _public function_ `virtual bool RequiresOriginalReleaseVersionForPatch() const override`
- L759 _public function_ `virtual bool HasNonTrivialPatchGeneration() const override`
- L763 _public function_ `virtual bool HasSecurePackageFormat() const override`
- L767 _public function_ `virtual EPlatformAuthentication RequiresUserCredentials() const override`
- L771 _public function_ `virtual bool SupportsAutoSDK() const override`
- L775 _public function_ `virtual bool SupportsBuildTarget(EBuildTargetType TargetType) const override`
- L779 _public function_ `virtual EBuildTargetType GetRuntimePlatformType() const override`
- L783 _public function_ `virtual bool SupportsFeature(ETargetPlatformFeatures Feature) const override`
- L787 _public function_ `virtual bool SupportsValueForType(FName SupportedType, FName RequiredSupportedValue) const override`
- L791 _public function_ `virtual bool UsesForwardShading() const override`
- L795 _public function_ `virtual bool UsesDBuffer() const override`
- L799 _public function_ `virtual bool UsesBasePassVelocity() const override`
- L803 _public function_ `virtual bool UsesSelectiveBasePassOutputs() const override`
- L807 _public function_ `virtual bool ShouldStripNaniteFallbackMeshes() const override`
- L811 _public function_ `virtual bool UsesDistanceFields() const override`
- L815 _public function_ `virtual bool UsesRayTracing() const override`
- L819 _public function_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const override`
- L823 _public function_ `virtual uint32 GetSupportedHardwareMask() const override`
- L827 _public function_ `virtual EOfflineBVHMode GetStaticMeshOfflineBVHMode() const override`
- L831 _public function_ `virtual bool GetStaticMeshOfflineBVHCompression() const override`
- L835 _public function_ `virtual EOfflineBVHMode GetSkeletalMeshOfflineBVHMode() const override`
- L839 _public function_ `virtual bool ForcesSimpleSkyDiffuse() const override`
- L843 _public function_ `virtual bool VelocityEncodeDepth() const override`
- L847 _public function_ `virtual float GetDownSampleMeshDistanceFieldDivider() const override`
- L851 _public function_ `virtual int32 GetHeightFogModeForOpaque() const override`
- L855 _public function_ `virtual bool UsesMobileDBuffer() const override`
- L859 _public function_ `virtual bool UsesASTCHDR() const override`
- L863 _public function_ `virtual FName GetFallbackASTCHDR() const override`
- L867 _public function_ `virtual void GetAllPossibleShaderFormats(TArray<FName>& OutFormats) const override`
- L871 _public function_ `virtual void GetAllTargetedShaderFormats(TArray<FName>& OutFormats) const override`
- L875 _public function_ `virtual void GetRayTracingShaderFormats(TArray<FName>& OutFormats) const override`
- L879 _public function_ `virtual void GetPossibleArchitectures(TArray<FString>& OutArchitectures) const override`
- L883 _public function_ `virtual FString GetHostArchitecture() const override`
- L887 _public function_ `virtual void GetPlatformSpecificProjectAnalytics(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray) const override`
- L892 _public function_ `virtual FName GetPhysicsFormat(class UBodySetup* Body) const override`
- L896 _public function_ `virtual void GetReflectionCaptureFormats(TArray<FName>& OutFormats) const override`
- L900 _public function_ `virtual void GetShaderFormatModuleHints(TArray<FName>& OutModuleNames) const override`
- L904 _public function_ `virtual void GetTextureFormats(const class UTexture* Texture, TArray< TArray<FName> >& OutFormats) const override`
- L909 _public function_ `virtual void GetTextureSizeLimits(uint64 & OutMaximumSurfaceBytes, uint64 & OutMaximumPackageBytes) const override`
- L914 _public function_ `virtual void GetTextureFormatModuleHints(TArray<FName>& OutModuleNames) const override`
- L918 _public function_ `virtual FName FinalizeVirtualTextureLayerFormat(FName Format) const override`
- L922 _public function_ `virtual bool SupportsLQCompressionTextureFormat() const override`
- L926 _public function_ `virtual FName GetWaveFormat(const class USoundWave* Wave) const override`
- L930 _public function_ `virtual void GetAllWaveFormats(TArray<FName>& OutFormats) const override`
- L934 _public function_ `virtual void GetWaveFormatModuleHints(TArray<FName>& OutModuleNames) const override`
- L938 _public function_ `virtual bool AllowAudioVisualData() const override`
- L942 _public function_ `virtual bool AllowObject(const class UObject* Object) const override`
- L946 _public function_ `virtual const class UTextureLODSettings& GetTextureLODSettings() const override`
- L950 _public function_ `virtual void RegisterTextureLODSettings(const class UTextureLODSettings* InTextureLODSettings) override`
- L954 _public function_ `virtual const class FStaticMeshLODSettings& GetStaticMeshLODSettings() const override`
- L958 _public function_ `virtual FName GetMeshBuilderModuleName() const override`
- L963 _public function_ `virtual bool PackageBuild(const FString& InPackgeDirectory) override`
- L967 _public function_ `virtual bool SupportsVariants() const override`
- L971 _public function_ `virtual float GetVariantPriority() const override`
- L975 _public function_ `virtual bool SendLowerCaseFilePaths() const override`
- L979 _public function_ `virtual void GetBuildProjectSettingKeys(FString& OutSection, TArray<FString>& InBoolKeys, TArray<FString>& InIntKeys, TArray<FString>& InStringKeys) const override`
- L983 _public function_ `virtual int32 GetPlatformOrdinal() const override`
- L987 _public function_ `virtual TSharedPtr<IDeviceManagerCustomPlatformWidgetCreator> GetCustomWidgetCreator() const override`
- L991 _public function_ `virtual bool ShouldExpandTo32Bit(const uint16* Indices, const int32 NumIndices) const override`
- L995 _public function_ `virtual bool CopyFileToTarget(const FString& DeviceId, const FString& HostFilename, const FString& TargetFilename, const TMap<FString, FString>& CustomPlatformData) override`
- L999 _public function_ `virtual void InitializeForCook() override`
- L1003 _public function_ `virtual void GetExtraPackagesToCook(TArray<FName>& PackageNames) const override`
- L1007 _public function_ `virtual bool InitializeHostPlatform() override`
- L1015 _public prototype_ `virtual ~FTargetPlatformMerged() = default;` — Virtual destructor.
- L1018 _private member_ `ITargetPlatformSettings* TargetPlatformSettings;`
- L1019 _private member_ `ITargetPlatformControls* TargetPlatformControls;`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace Audio`

### `Source/Developer/TargetPlatform/Public/Common/TargetPlatformControlsBase.h` (Public)


#### class `FTargetPlatformControlsBase`  
`class FTargetPlatformControlsBase : public ITargetPlatformControls`  
_L21-225_
- inherits: `ITargetPlatformControls`
- L25 _public function_ `virtual bool AddDevice(const FString& DeviceName, bool bDefault) override`
- L30 _public function_ `virtual bool AddDevice(const FString& DeviceId, const FString& DeviceUserFriendlyName, const FString& Username, const FString& Password, bool bDefault) override`
- L35 _public function_ `virtual FText DisplayName() const override`
- L40 _public function_ `virtual const PlatformInfo::FTargetPlatformInfo& GetTargetPlatformInfo() const override`
- L45 _public function_ `virtual const FDataDrivenPlatformInfo& GetPlatformInfo() const override`
- L50 _public prototype_ `virtual bool IsEnabledForPlugin(const IPlugin& Plugin) const override;`
- L51 _public prototype_ `virtual void GetPlatformSpecificProjectAnalytics(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray) const override;`
- L54 _public function_ `virtual FName FinalizeVirtualTextureLayerFormat(FName Format) const override`
- L58 _public function_ `virtual bool SupportsLQCompressionTextureFormat() const override`
- L61 _public function_ `virtual bool PackageBuild(const FString& InPackgeDirectory) override`
- L66 _public function_ `virtual bool CanSupportRemoteShaderCompile() const override`
- L71 _public function_ `virtual void GetShaderCompilerDependencies(TArray<FString>& OutDependencies) const override`
- L76 _public function_ `static void AddDependencySCArrayHelper(TArray<FString>& OutDependencies, const FString& DependencyRelativePath)` — Helper method to fill a dependencies array for the shader compiler with absolute paths, passing a relative path to the Engine as the parameter.
- L84 _public function_ `virtual bool IsSdkInstalled(bool bProjectHasCode, FString& OutDocumentationPath) const override`
- L89 _public function_ `virtual int32 CheckRequirements(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FString& OutTutorialPath, FString& OutDocumentationPath, FText& CustomizedLogMessage) const override`
- L99 _public prototype_ `virtual bool RequiresTempTarget(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FText& OutReason) const override;`
- L101 _public function_ `virtual bool SupportsVariants() const override`
- L106 _public function_ `virtual float GetVariantPriority() const override`
- L111 _public function_ `virtual bool SendLowerCaseFilePaths() const override`
- L116 _public function_ `virtual bool AllowsEditorObjects() const override`
- L121 _public function_ `virtual bool AllowsDevelopmentObjects() const override`
- L126 _public function_ `virtual void GetBuildProjectSettingKeys(FString& OutSection, TArray<FString>& InBoolKeys, TArray<FString>& InIntKeys, TArray<FString>& InStringKeys) const override`
- L131 _public function_ `virtual int32 GetPlatformOrdinal() const override`
- L136 _public prototype_ `virtual TSharedPtr<IDeviceManagerCustomPlatformWidgetCreator> GetCustomWidgetCreator() const override;`
- L138 _public function_ `virtual bool ShouldExpandTo32Bit(const uint16* Indices, const int32 NumIndices) const override`
- L144 _public function_ `virtual bool AllowAudioVisualData() const override`
- L149 _public function_ `virtual bool AllowObject(const class UObject* Object) const override`
- L154 _public function_ `virtual FName GetMeshBuilderModuleName() const override`
- L162 _public function_ `virtual void GetTextureFormatModuleHints(TArray<FName>& OutModuleNames) const override` — beware this is duplicated between TargetPlatformBase and TargetPlatformControlsBase
- L166 _public prototype_ `virtual FName GetWaveFormat(const class USoundWave* Wave) const override;`
- L168 _public prototype_ `virtual void GetAllWaveFormats(TArray<FName>& OutFormats) const override;`
- L170 _public prototype_ `virtual void GetWaveFormatModuleHints(TArray<FName>& OutModuleNames) const override;`
- L172 _public prototype_ `static void GetTextureSizeLimitsDefault(FConfigCacheIni* ConfigSystem,uint64 & OutMaximumSurfaceBytes, uint64 & OutMaximumPackageBytes);`
- L175 _public function_ `virtual void GetTextureSizeLimits(uint64 & OutMaximumSurfaceBytes, uint64 & OutMaximumPackageBytes) const override` — beware this is duplicated between TargetPlatformBase and TargetPlatformControlsBase
- L182 _public function_ `virtual bool CopyFileToTarget(const FString& TargetAddress, const FString& HostFilename, const FString& TargetFilename, const TMap<FString, FString>& CustomPlatformData) override`
- L187 _public function_ `virtual void InitializeForCook() override`
- L192 _public function_ `virtual void GetExtraPackagesToCook(TArray<FName>& PackageNames) const override`
- L197 _public function_ `virtual bool InitializeHostPlatform()`
- L204 _protected prototype_ `FTargetPlatformControlsBase(const PlatformInfo::FTargetPlatformInfo* const InPlatformInfo, ITargetPlatformSettings* TargetPlatformSettings);`
- L207 _protected member_ `const PlatformInfo::FTargetPlatformInfo* PlatformInfo;` — Information about this platform
- L208 _protected member_ `int32 PlatformOrdinal;`
- L210 _protected prototype_ `const Audio::FAudioFormatSettings& GetAudioFormatSettings() const;`
- L213 _protected prototype_ `static void AppendAnalyticsEventConfigBool(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr);` — Analytics helper functions
- L214 _protected prototype_ `static void AppendAnalyticsEventConfigInt(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr);`
- L215 _protected prototype_ `static void AppendAnalyticsEventConfigFloat(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr);`
- L216 _protected prototype_ `static void AppendAnalyticsEventConfigString(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr);`
- L217 _protected prototype_ `static void AppendAnalyticsEventConfigArray(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray, const TCHAR* ConfigSection, const TCHAR* ConfigKey, const FString& IniFileName, const TCHAR* AnalyticsKeyNameOverride = nullptr);`
- L220 _private member_ `TPimplPtr<Audio::FAudioFormatSettings> AudioFormatSettings;`
- L222 _private prototype_ `bool HasDefaultBuildSettings() const;`
- L223 _private prototype_ `static bool DoProjectSettingsMatchDefault(const FString& InPlatformName, const FString& InSection, const TArray<FString>* InBoolKeys, const TArray<FString>* InIntKeys, const TArray<FString>* InStringKeys);`
- L224 _private prototype_ `static bool IsPluginEnabledForTarget(const IPlugin& Plugin, const struct FProjectDescriptor* Project, const FString& Platform, EBuildConfiguration Configuration, EBuildTargetType TargetType);`

#### class `TTargetPlatformControlsBase`  
`template<typename TPlatformProperties> class TTargetPlatformControlsBase : public FTargetPlatformControlsBase`  
_L228-369_
- inherits: `FTargetPlatformControlsBase`
- L236 _public function_ `static bool IsUsable()` — Returns true if the target platform will be able to be  initialized with an FPlatformInfo. Because FPlatformInfo now comes from a .ini file, it's possible that the .dll exists, but the .ini does not (should be uncommon, but is necessary to be handled)
- L244 _public function_ `TTargetPlatformControlsBase(const PlatformInfo::FTargetPlatformInfo* const InPlatformInfo, ITargetPlatformSettings* TargetPlatformSettings) : FTargetPlatformControlsBase(InPlatformInfo, TargetPlatformSettings)` — Constructor that already has a TPI (notably coming from TNonDesktopTargetPlatform)
- L254 _public function_ `TTargetPlatformControlsBase(ITargetPlatformSettings* TargetPlatformSettings) : TTargetPlatformControlsBase(new PlatformInfo::FTargetPlatformInfo( TPlatformProperties::IniPlatformName(), TPlatformProperties::HasEditorOnlyData() ? EBuildTargetType::Editor : TPlatformProperties::IsServerOnly() ? EBuildTargetType::Server : TPlatformProperties::IsClientOnly() ? EBuildTargetType::Client : EBuildTargetType::Game, TEXT("")), TargetPlatformSettings )` — Constructor that makes a TPCI based solely on TPlatformProperties
- L267 _public function_ `virtual bool HasEditorOnlyData() const override`
- L272 _public function_ `virtual bool IsLittleEndian() const override`
- L277 _public function_ `virtual bool IsServerOnly() const override`
- L282 _public function_ `virtual bool IsClientOnly() const override`
- L287 _public function_ `virtual FString PlatformName() const override`
- L295 _public function_ `virtual FString CookingDeviceProfileName() const override`
- L301 _public function_ `virtual bool RequiresCookedData() const override`
- L306 _public function_ `virtual bool RequiresOriginalReleaseVersionForPatch() const override`
- L311 _public function_ `virtual bool HasNonTrivialPatchGeneration() const override`
- L316 _public function_ `virtual bool HasSecurePackageFormat() const override`
- L321 _public function_ `virtual EPlatformAuthentication RequiresUserCredentials() const override`
- L333 _public function_ `virtual bool SupportsBuildTarget(EBuildTargetType TargetType) const override`
- L338 _public function_ `virtual EBuildTargetType GetRuntimePlatformType() const override`
- L348 _public function_ `virtual bool SupportsAutoSDK() const override`
- L353 _public function_ `virtual FName GetZlibReplacementFormat() const override`
- L358 _public function_ `virtual int64 GetMemoryMappingAlignment() const override`
- L364 _public function_ `virtual FName GetPhysicsFormat(class UBodySetup* Body) const override`

#### class `TNonDesktopTargetPlatformControlsBase`  
`template<typename TPlatformProperties> class TNonDesktopTargetPlatformControlsBase : public TTargetPlatformControlsBase<TPlatformProperties>`  
_L372-415_
- inherits: `TTargetPlatformControlsBase<TPlatformProperties>`
- L376 _public function_ `TNonDesktopTargetPlatformControlsBase(bool bInIsClientOnly, ITargetPlatformSettings* InTargetPlatformSettings, const TCHAR* CookFlavor = nullptr, const TCHAR* OverrideIniPlatformName = nullptr) : TTargetPlatformControlsBase<TPlatformProperties>(new PlatformInfo::FTargetPlatformInfo( OverrideIniPlatformName ? FString(OverrideIniPlatformName) : FString(TPlatformProperties::IniPlatformName()), bInIsClientOnly ? EBuildTargetType::Client : EBuildTargetType::Game, CookFlavor), InTargetPlatformSettings) , bIsClientOnly(bInIsClientOnly)`
- L385 _public function_ `virtual FString PlatformName() const override`
- L391 _public function_ `virtual FString CookingDeviceProfileName() const override`
- L397 _public function_ `virtual bool HasEditorOnlyData() const override`
- L402 _public function_ `virtual bool IsServerOnly() const override`
- L407 _public function_ `virtual bool IsClientOnly() const override`
- L414 _protected member_ `bool bIsClientOnly;` — true if this target platform is client-only, ie strips out server stuff

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Audio`

### `Source/Developer/TargetPlatform/Public/Common/TargetPlatformSettingsBase.h` (Public)


#### class `FTargetPlatformSettingsBase`  
`class FTargetPlatformSettingsBase : public ITargetPlatformSettings`  
_L13-81_
- inherits: `ITargetPlatformSettings`
- L17 _public function_ `virtual FConfigCacheIni* GetConfigSystem() const override`
- L22 _public prototype_ `virtual bool UsesForwardShading() const override;`
- L23 _public prototype_ `virtual bool UsesDBuffer() const override;`
- L25 _public prototype_ `virtual bool UsesBasePassVelocity() const override;` — `UE_DEPRECATED(5.1, "Use IsUsingBasePassVelocity(EShaderPlatform Platform) in renderutils that will uses FShaderPlatformCachedIniValue to retrieve the cvar value per platform.")`
- L26 _public prototype_ `virtual bool VelocityEncodeDepth() const override;`
- L27 _public prototype_ `virtual bool UsesSelectiveBasePassOutputs() const override;`
- L28 _public prototype_ `virtual bool ShouldStripNaniteFallbackMeshes() const override;`
- L29 _public prototype_ `virtual bool UsesDistanceFields() const override;`
- L30 _public prototype_ `virtual bool UsesRayTracing() const override;`
- L31 _public prototype_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const override;`
- L32 _public prototype_ `virtual uint32 GetSupportedHardwareMask() const override;`
- L33 _public prototype_ `virtual EOfflineBVHMode GetStaticMeshOfflineBVHMode() const override;`
- L34 _public prototype_ `virtual bool GetStaticMeshOfflineBVHCompression() const override;`
- L35 _public prototype_ `virtual EOfflineBVHMode GetSkeletalMeshOfflineBVHMode() const override;`
- L36 _public prototype_ `virtual bool ForcesSimpleSkyDiffuse() const override;`
- L37 _public prototype_ `virtual float GetDownSampleMeshDistanceFieldDivider() const override;`
- L38 _public prototype_ `virtual int32 GetHeightFogModeForOpaque() const override;`
- L39 _public prototype_ `virtual bool UsesMobileDBuffer() const override;`
- L40 _public prototype_ `virtual bool UsesASTCHDR() const override;`
- L41 _public prototype_ `virtual FName GetFallbackASTCHDR() const override;`
- L42 _public prototype_ `virtual void GetRayTracingShaderFormats(TArray<FName>& OutFormats) const override;`
- L43 _public prototype_ `virtual void GetPossibleArchitectures(TArray<FString>& OutArchitectures) const override;`
- L44 _public prototype_ `virtual FString GetHostArchitecture() const override;`
- L47 _public function_ `virtual void GetShaderFormatModuleHints(TArray<FName>& OutModuleNames) const override`
- L51 _public function_ `virtual void GetReflectionCaptureFormats(TArray<FName>& OutFormats) const override`
- L57 _public function_ `virtual bool SupportsValueForType(FName SupportedType, FName RequiredSupportedValue) const override`
- L70 _public function_ `virtual bool IsRunningPlatform() const override`
- L78 _protected prototype_ `ERayTracingRuntimeMode ParseRuntimeRayTracingMode(const TCHAR* SectionName) const;`
- L80 _protected function_ `FTargetPlatformSettingsBase()`

#### class `TTargetPlatformSettingsBase`  
`template<typename TPlatformProperties> class TTargetPlatformSettingsBase : public FTargetPlatformSettingsBase`  
_L84-181_
- inherits: `FTargetPlatformSettingsBase`
- L88 _public function_ `TTargetPlatformSettingsBase(const TCHAR* CookFlavor = nullptr, const TCHAR* OverrideIniPlatformName = nullptr) : FTargetPlatformSettingsBase()`
- L94 _public function_ `virtual FString IniPlatformName() const override`
- L99 _public function_ `virtual bool UsesRayTracing() const override`
- L108 _public function_ `virtual bool SupportsFeature(ETargetPlatformFeatures Feature) const override`
- L180 _private member_ `FString IniPlatformNameValue;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Developer/TargetPlatform/Public/Interfaces/IAudioFormat.h` (Public)


#### struct `FSoundQualityInfo`  
`struct FSoundQualityInfo`  
_L15-37_
- desc: A non-UObject based structure used to pass data about a sound node wave around the engine and tools.
- L18 _public member_ `int32 Quality = 0;` — Holds the quality value ranging from 1 [poor] to 100 [very good].
- L21 _public member_ `uint32 NumChannels = 0;` — Holds the number of distinct audio channels.
- L24 _public member_ `uint32 SampleRate = 0;` — Holds the number of PCM samples per second.
- L27 _public member_ `uint32 SampleDataSize = 0;` — Holds the size of sample data in bytes.
- L30 _public member_ `float Duration = 0.f;` — Holds the length of the sound in seconds.
- L33 _public member_ `bool bStreaming = false;` — Holds whether the sound will be streamed.
- L36 _public member_ `FString DebugName;` — Holds a string for debugging purposes.

#### class `IAudioFormat`  
`class IAudioFormat : public IModularFeature`  
_L43-229_
- inherits: `IModularFeature`
- desc: Interface for audio formats.
- L51 _public function_ `FORCEINLINE static FName GetModularFeatureName()` — Returns the name of the modular feature. @return FName of the feature. To be used to query IModularFeatures
- L65 _public function_ `virtual bool AllowParallelBuild() const` — Checks whether parallel audio cooking is allowed. Note: This method is not currently used yet. @return true if this audio format can cook in parallel, false otherwise.
- L79 _public prototype_ `virtual bool Cook( FName Format, const TArray<uint8>& SrcBuffer, FSoundQualityInfo& QualityInfo, TArray<uint8>& OutBuffer ) const = 0;` — Cooks the source data for the platform and stores the cooked data internally. @param Format The desired format. @param SrcBuffer The source buffer. Buffers are 16 bit PCM, either mono or stereo (check QualityInfo.NumChannels) @param QualityInfo All the information the compressor needs to compress the audio. QualityInfo.Duration is unset. @param OutBuffer Will hold the resulting compressed audio. @return true on success, false otherwise.
- L90 _public prototype_ `virtual bool CookSurround( FName Format, const TArray<TArray<uint8> >& SrcBuffers, FSoundQualityInfo& QualityInfo, TArray<uint8>& OutBuffer ) const = 0;` — Cooks up to 8 mono files into a multi-stream file (e.g. 5.1). The front left channel is required, the rest are optional. @param Format The desired format. @param SrcBuffers The source buffers. Buffers are mono 16 bit PCM. @param QualityInfo All the information the compressor needs to compress the audio. QualityInfo.Duration is unset. @param OutBuffer Will contain the resulting compressed audio. @return true if succeeded, false otherwise
- L97 _public prototype_ `virtual void GetSupportedFormats( TArray<FName>& OutFormats ) const = 0;` — Gets the list of supported formats. @param OutFormats Will contain the list of formats.
- L105 _public prototype_ `virtual uint16 GetVersion( FName Format ) const = 0;` — Gets the current version of the specified audio format. @param Format The format to get the version for. @return Version number.
- L118 _public prototype_ `virtual int32 Recompress( FName Format, const TArray<uint8>& SrcBuffer, FSoundQualityInfo& QualityInfo, TArray<uint8>& OutBuffer ) const = 0;` — Re-compresses raw PCM to the the platform dependent format, and then back to PCM. Used for quality previewing. This function is, as far as I can tell, unused. @param Format The desired format. @param SrcBuffer Uncompressed PCM data. @param QualityInfo All the information the compressor needs to compress the audio. @param OutBuffer Uncompressed PCM data after being compressed. @return The size of the compressed audio, or 0 on failure.
- L128 _public function_ `virtual int32 GetMinimumSizeForInitialChunk(FName Format, const TArray<uint8>& SrcBuffer) const` — Given the encoded buffer, returns the minimum number of bytes required to perform ICompressedAudioInfo::ReadCompressedInfo() or IStreamedCompressedInfo::ParseHeader() for this file. This is called prior to SplitDataForStreaming(), and is used for determining FirstChunkMaxSize. @param Format the codec that SrcBuffer was compressed as. @param SrcBuffer the compressed data that will later be split into individual chunks.
- L139 _public function_ `virtual bool SplitDataForStreaming(const TArray<uint8>& SrcBuffer, TArray<TArray<uint8>>& OutBuffers, const int32 FirstChunkMaxSize, const int32 MaxChunkSize) const` — Splits compressed data into chunks suitable for streaming audio. @param SrcBuffer Pre-compressed data as an array of bytes. @param OutBuffers Array of buffers that contain the chunks the original data was split into. @param FirstChunkMaxSize The maximum size for the chunk that will be loaded inline with it's owning USoundWave asset. @param MaxChunkSize The maximum chunk size for each chunk. The chunks will be zero-padded to match this chunk size in the bulk data serialization. @return Whether bulk data could be split for streaming.
- L141 _public function_ `virtual bool RequiresStreamingSeekTable() const`
- L156 _public function_ `virtual bool ExtractSeekTableForStreaming(TArray<uint8>& InOutBuffer, FSeekTable& OutSeektable) const` — Extracts the embedded seek-table, removing it, and outputting it separately. NOTE: TArray is modified in place. The seek-table is parsed and removed from it. @param InOutBuffer Pre-compressed data containing seek-table and compressed data as array of bytes. @param OutSeekTable Seektable in its generic form. @return Success or failure
- L161 _public function_ `virtual bool IsPlatformSupported(const FName InPlatformName) const` — Returns true if the target platform name is supported
- L166 _public function_ `virtual bool IsHardwareFormat() const` — Returns true if this format/codec requires hardware.
- L173 _public function_ `bool IsSampleRateSupported(const int32 InSampleRate) const` — Returns true if the sample rate is supported by this codec. @param InSampleRate The Rate to test @return true or false if supported
- L191 _public function_ `bool IsChannelCountSupported(const int32 InChannelCount) const` — Returns true if the sample rate is supported by this codec. @param InChannelCount The channel count to test for @return true or false if supported
- L209 _public function_ `virtual TConstArrayView<int32> GetSupportedSampleRates() const` — Returns the list of supported sample rates NOTE: An empty list implies all rates are supported. @return List of supported sample rate for this format/codec
- L216 _public function_ `virtual TConstArrayView<int32> GetSupportedChannelCounts() const` — Returns the list of supported channel counts NOTE: An empty list implies all counts are supported. @return List of supported channel counts
- L219 _public function_ `IAudioFormat()` — Self Registering Constructor
- L225 _public function_ `virtual ~IAudioFormat()` — Self Registering Virtual destructor.

#### struct `IAudioFormat::FSeekTable`  
`struct FSeekTable`  
_L143-147_
- L145 _public member_ `TArray<uint32> Times;` — Times in AudioFrames.
- L146 _public member_ `TArray<uint32> Offsets;` — Offset in the compressed data.

### `Source/Developer/TargetPlatform/Public/Interfaces/IAudioFormatModule.h` (Public)


#### class `IAudioFormatModule`  
`class IAudioFormatModule : public IModuleInterface`  
_L13-29_
- inherits: `IModuleInterface`
- desc: Interface for audio format modules.
- L23 _public prototype_ `virtual IAudioFormat* GetAudioFormat() = 0;` — Gets the audio format. @return The audio format interface.
- L28 _public prototype_ `~IAudioFormatModule() = default;` — Virtual destructor.

### `Source/Developer/TargetPlatform/Public/Interfaces/IDeviceManagerCustomPlatformWidgetCreator.h` (Public)


#### class `IDeviceManagerCustomPlatformWidgetCreator`  
`class IDeviceManagerCustomPlatformWidgetCreator`  
_L10-19_
- L13 _public prototype_ `virtual TSharedPtr<SWidget> CreateAddDeviceWidget(const FString& InPlatformName) = 0;`
- L14 _public prototype_ `virtual bool IsAddDeviceInputValid(const FString& InPlatformName, const TSharedPtr<SWidget>& UserData) = 0;`
- L16 _public prototype_ `virtual TSharedPtr<SWidget> CreateDeviceInfoWidget(const FString& InPlatformName, const ITargetDevicePtr& InDevice) = 0;`
- L18 _public prototype_ `virtual void AddDevice(const FString& InPlatformName, const TSharedPtr<SWidget>& UserData) = 0;`

### `Source/Developer/TargetPlatform/Public/Interfaces/IProjectBuildMutatorFeature.h` (Public)


#### class `IProjectBuildMutatorFeature`  
`class IProjectBuildMutatorFeature : public IModularFeature`  
_L10-14_
- inherits: `IModularFeature`
- L13 _public prototype_ `virtual bool RequiresProjectBuild(const FName& InPlatformInfoName, FText& OutReason) const = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define PROJECT_BUILD_MUTATOR_FEATURE "ProjectBuildMutatorFeature"`

### `Source/Developer/TargetPlatform/Public/Interfaces/IShaderFormat.h` (Public)


#### class `IShaderFormat`  
`class IShaderFormat`  
_L22-214_
- desc: IShaderFormat, shader pre-compilation abstraction
- L32 _public prototype_ `virtual uint32 GetVersion(FName Format) const = 0;` — Gets the current version of the specified shader format. @param Format The format to get the version for. @return Version number.
- L39 _public prototype_ `virtual void GetSupportedFormats(TArray<FName>& OutFormats) const = 0;` — Gets the list of supported formats. @param OutFormats Will hold the list of formats.
- L47 _public function_ `virtual bool CanStripShaderCode(bool const bNativeFormat) const` — Can this shader format strip shader code for packaging in a shader library? @param bNative Whether the final shader library uses a native format which may determine if the shader is stripped. @returns True if and only if the format can strip extraneous data from shaders to be included in a shared library, otherwise false.
- L57 _public function_ `virtual bool StripShaderCode(TArray<uint8>& Code, FString const& DebugOutputDir, bool const bNative) const` — Strips the shader bytecode provided of any unnecessary optional data elements when archiving shaders into the shared library. @param Code The byte code to strip (must be uncompressed). @param DebugOutputDir The output directory to write the debug symbol file for this shader. @param bNative Whether the final shader library uses a native format which may determine how the shader is stripped. @return True if the format has successfully stripped the extraneous data from shaders, otherwise false
- L64 _public function_ `virtual bool SupportsShaderArchives() const` — Whether this shader format supports a format-specific archive for precompiled shader code. @returns true if shader archives are supported, false otherwise.
- L77 _public function_ `virtual bool CreateShaderArchive(FString const& LibraryName, FName ShaderFormatAndShaderPlatformName, const FString& WorkingDirectory, const FString& OutputDir, const FString& DebugOutputDir, const FSerializedShaderArchive& SerializedShaders, const TArray<FSharedBuffer>& ShaderCode, TArray<FString>* OutputFiles) const` — Create a format specific archive for precompiled shader code. @param LibraryName The name of this shader library. @param Format The format of shaders to cache. @param WorkingDirectory The working directory. @param The output directory for the archive. @param The directory for the debug data previously generated. @param Optional pointer to a TArray that on success will be filled with a list of the written file paths. @returns true if the archive was created
- L93 _public function_ `virtual bool CanCompileBinaryShaders() const` — Can the shader format compile shaders to the native binary format for the platform. @returns True if the native compiler is available and configured, otherwise false.
- L100 _public prototype_ `virtual const TCHAR* GetPlatformIncludeDirectory() const = 0;` — Returns name of directory with platform specific shaders. @returns Name of directory with platform specific shaders.
- L107 _public function_ `virtual void ModifyShaderCompilerInput(FShaderCompilerInput& Input) const` — Called before a shader is compiled to allow the platform shader format to modify the shader compiler input, e.g. by adding console variable values relevant to shader compilation on that platform.
- L113 _public function_ `virtual void NotifyShaderCompiled(const FCompressedBuffer& SymbolData, FName Format, const FString& DebugInfo = FString()) const` — Called when a shader resource is cooked, so the shader format can perform platform-specific operations on the debug data. Does nothing on platforms that make no use of the symbol data.
- L116 _public function_ `virtual void NotifyShaderCompilersShutdown(FName Format) const` — Called at the end of a cook to free resources and finalize artifacts created during the cook.
- L122 _public function_ `virtual void AppendToKeyString(FString& KeyString) const` — Appends shader key text to the provided key string for use in DDC unique key construction. @param KeyString String that will get shader key text appended to.
- L127 _public function_ `virtual bool PreprocessShader(const FShaderCompilerInput& Input, const FShaderCompilerEnvironment& Environment, FShaderPreprocessOutput& PreprocessOutput) const` — Execute all shader preprocessing steps, storing the output in the PreprocessOutput struct
- L132 _public function_ `virtual void CompilePreprocessedShader( const FShaderCompilerInput& Input, const FShaderPreprocessOutput& PreprocessOutput, FShaderCompilerOutput& Output) const` — Compile the specified preprocessed shader.
- L144 _public function_ `virtual void CompilePreprocessedShader( const FShaderCompilerInput& Input, const FShaderPreprocessOutput& PrimaryPreprocessOutput, const FShaderPreprocessOutput& SecondaryPreprocessOutput, FShaderCompilerOutput& PrimaryOutput, FShaderCompilerOutput& SecondaryOutput) const` — Compile the specified preprocessed shaders; only called if the call to RequiresSecondaryCompile given the first preprocess output returns true. The shader system will pack these outputs together in the following format: [int32 key][uint32 primary length][uint32 secondary length][full primary shader code][full secondary shader code] where "key" is the return value of the GetPackedShaderKey function (this should also be implemented by any backends which require secondary compilation and is used by the RHI to differentiate packed shader code from single shaders)
- L161 _public function_ `virtual bool RequiresSecondaryCompile( const FShaderCompilerInput& Input, const FShaderCompilerEnvironment& Environment, const FShaderPreprocessOutput& PreprocessOutput) const` — Predicate which should return true if a second preprocess & compilation is required given the initial preprocess output. This is generally be determined by analyzing the directives on the given preprocess output (which are set by the presence of UESHADERMETADATA directives in the original source), though other conditions are possible and up to the implementation. In the event this returns true, PreprocessShader will be called an additional time, with the bIsSecondary field on the FShaderPreprocessOutput set to true, and the overload of CompilePreprocessedShader taking two FShaderPreprocessOutput and two FShaderCompilerOutput objects will be called instead of the single object variants. Note that this is done instead of calling the single object variant twice so shader formats can statically distinguish primary compilation in a dual-compile case from the single-compile case.
- L170 _public function_ `virtual FStringView GetSecondaryCompileName() const` — For shader formats which support secondary compilation, this can optionally return a name that is appended to diagnostic messages to distinguish errors in the secondary compile from the primary.
- L177 _public function_ `virtual int32 GetPackedShaderKey() const` — Virtual function that can be implemented by backends which require secondary compilation to specify a unique "key" identifier for the packing scheme (for validation in the runtime at load). see RequiresSecondaryCompile and the overloads of CompilePreprocessedShader for additional details.
- L188 _public function_ `virtual void OutputDebugData( const FShaderCompilerInput& Input, const FShaderPreprocessOutput& PreprocessOutput, const FShaderCompilerOutput& Output, FShaderDebugDataContext& Ctx) const` — Implement to output debug info for a single compile job. This will be called for all jobs (including those found in the job cache) but only if debug info is enabled for the job. Note that any debug info output in CompilePreprocessedShader will only be done for the job that actually executes the compile step, as such any debug outputs that are desirable for all jobs should be written by this function. A BaseShaderFormat implementation is provided in ShaderCompilerCommon which dumps preprocessed and stripped USFs along with the hash of the shader code in an OutputHash.txt file; if no additional custom debug output is required the shader format can inherit from FBaseShaderFormat instead of IShaderFormat.
- L200 _public function_ `virtual void OutputDebugData( const FShaderCompilerInput& Input, const FShaderPreprocessOutput& PreprocessOutput, const FShaderPreprocessOutput& SecondaryPreprocessOutput, const FShaderCompilerOutput& Output, const FShaderCompilerOutput& SecondaryOutput, FShaderDebugDataContext& Ctx) const` — Implement to output debug info for the case where a secondary preprocessed shader was created. As with the dual-output version of CompilePreprocessedShader this is provided so shader formats can statically distinguish the single and dual output cases. Note that BaseShaderFormat does not provide an implementation of this so it needs to be explicitly implemented by backends which require secondary compilation, even if inheriting from FBaseShaderFormat.
- L209 _public function_ `virtual void OutputDebugDataMinimal(const FShaderCompilerInput& Input, FShaderDebugDataContext& Ctx) const` — Implement to output a minimal set of debug info based solely on the compile input. This is invoked when preprocessing fails.
- L213 _public prototype_ `virtual ~IShaderFormat() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L8 _macro_ `#define SHADERFORMAT_MODULE_WILDCARD TEXT("*ShaderFormat*")` — Wildcard string used to search for shader format modules.

### `Source/Developer/TargetPlatform/Public/Interfaces/IShaderFormatModule.h` (Public)


#### class `IShaderFormatModule`  
`class IShaderFormatModule : public IModuleInterface`  
_L13-29_
- inherits: `IModuleInterface`
- desc: Interface for shader format modules.
- L23 _public prototype_ `virtual IShaderFormat* GetShaderFormat() = 0;` — Gets the shader format. @return The shader format interface.
- L28 _public prototype_ `~IShaderFormatModule() = default;` — Virtual destructor.

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetDevice.h` (Public)


#### enum `ETargetDeviceFeatures`  
`enum class ETargetDeviceFeatures`  
_L16-32_
- desc: Enumerates features that may be supported by target devices.
- L19 _public enumerator_ `MultiLaunch` — Multiple instances of a game can run at the same time.
- L22 _public enumerator_ `PowerOff` — The device can be powered off remotely.
- L25 _public enumerator_ `PowerOn` — The device can be powered on remotely.
- L28 _public enumerator_ `ProcessSnapshot` — Snapshot of processes running on the device.
- L31 _public enumerator_ `Reboot` — The device can be rebooted remotely.

#### enum `ETargetDeviceTypes`  
`enum class ETargetDeviceTypes`  
_L38-60_
- desc: Enumerates target device types.
- L41 _public enumerator_ `Indeterminate` — Indeterminate device type.
- L44 _public enumerator_ `Browser` — The device is a web browser (i.e. Flash).
- L47 _public enumerator_ `Console` — The device is a game console.
- L50 _public enumerator_ `Desktop` — The device is a desktop computer.
- L53 _public enumerator_ `Phone` — The device is a smart phone.
- L56 _public enumerator_ `Tablet` — The device is a tablet computer.
- L59 _public enumerator_ `HMD` — The device is a standalone HMD

#### enum `ETargetDeviceConnectionTypes`  
`enum class ETargetDeviceConnectionTypes`  
_L65-84_
- desc: Enumerates how the target device is connected
- L68 _public enumerator_ `Unknown` — It's unknown how the device is connected.
- L71 _public enumerator_ `USB` — The device is connected through USB.
- L74 _public enumerator_ `Wifi` — The device is connected via Wifi.
- L77 _public enumerator_ `Ethernet` — The device is connected via Ethernet.
- L80 _public enumerator_ `Simulator` — The device is running as a simulator on the current Editor.
- L83 _public enumerator_ `Proprietary` — The device is connected via a proprietary connection.

#### enum `ETargetDeviceThreadStates`  
`enum class ETargetDeviceThreadStates`  
_L160-179_
- desc: Enumerates states of threads running on a target device.
- L163 _public enumerator_ `Unknown` — Unknown thread state.
- L166 _public enumerator_ `CanRun` — The thread can run, but is not running right now.
- L169 _public enumerator_ `Inactive` — The thread is inactive, i.e. has just been created or exited.
- L172 _public enumerator_ `Inhibited` — The thread cannot run right now.
- L175 _public enumerator_ `RunQueue` — The thread is in the run queue.
- L178 _public enumerator_ `Running` — The thread is running.

#### enum `ETargetDeviceThreadWaitStates`  
`enum class ETargetDeviceThreadWaitStates`  
_L185-204_
- desc: Enumerates wait states of threads running on a target device.
- L188 _public enumerator_ `Unknown` — Unknown wait state.
- L191 _public enumerator_ `Locked` — The thread is blocked by a lock.
- L194 _public enumerator_ `Sleeping` — The thread is sleeping.
- L197 _public enumerator_ `Suspended` — The thread is suspended.
- L200 _public enumerator_ `Swapped` — The thread is swapped.
- L203 _public enumerator_ `Waiting` — The thread is waiting on an interrupt.

#### struct `FTargetDeviceThreadInfo`  
`struct FTargetDeviceThreadInfo`  
_L210-229_
- desc: Structure for thread information.
- L213 _public member_ `uint64 ExitCode;` — Holds the exit code.
- L216 _public member_ `uint32 Id;` — Holds the thread identifier.
- L219 _public member_ `FString Name;` — Holds the name of the thread.
- L222 _public member_ `uint64 StackSize;` — Holds the thread's stack size.
- L225 _public member_ `ETargetDeviceThreadStates State;` — Holds the thread's current state.
- L228 _public member_ `ETargetDeviceThreadWaitStates WaitState;` — Holds the thread's current wait state.

#### struct `FTargetDeviceProcessInfo`  
`struct FTargetDeviceProcessInfo`  
_L235-251_
- desc: Structure for information for processes that are running on a target device.
- L238 _public member_ `int64 Id;` — Holds the process identifier.
- L241 _public member_ `FString Name;` — Holds the process name.
- L244 _public member_ `uint64 ParentId;` — Holds the identifier of the parent process.
- L247 _public member_ `TArray<FTargetDeviceThreadInfo> Threads;` — Holds the collection of threads that belong to this process.
- L250 _public member_ `FString UserName;` — The name of the user that owns this process.

#### class `ITargetDevice`  
`class ITargetDevice`  
_L269-569_
- desc: Interface for target devices.
- L278 _public prototype_ `virtual bool Connect() = 0;` — Connect to the physical device. @return true if the device is connected, false otherwise.
- L283 _public prototype_ `virtual void Disconnect() = 0;` — Disconnect from the physical device.
- L290 _public prototype_ `virtual ETargetDeviceTypes GetDeviceType() const = 0;` — Gets the device type. @return Device type.
- L297 _public function_ `virtual FString GetModelId() const` — Gets the device model identifier. @return ModelId.
- L304 _public function_ `virtual FString GetOSVersion() const` — Gets the device OS Version. @return OSVersion.
- L311 _public function_ `virtual FStringView GetArchitecture() const` — Gets the device architecture. @return Device Architecture.
- L321 _public function_ `virtual ETargetDeviceConnectionTypes GetDeviceConnectionType() const` — Gets the device connection type. @return Device connection type.
- L329 _public prototype_ `virtual FTargetDeviceId GetId() const = 0;` — Gets the unique device identifier. @return Device identifier. @see GetName
- L342 _public prototype_ `virtual FString GetName() const = 0;` — Gets the name of the device. In contrast to GetId(), this method is intended to return a human readable name for use in the user interface. Depending on the target platform, this name may be some user defined string, a host name, an IP address, or some other string identifying the device that does not need to be unique. @return Device name. @see GetId
- L349 _public prototype_ `virtual FString GetOperatingSystemName() = 0;` — Gets the name of the operating system running on this device. @return Operating system name.
- L357 _public prototype_ `virtual int32 GetProcessSnapshot( TArray<FTargetDeviceProcessInfo>& OutProcessInfos ) = 0;` — Creates a snapshot of processes currently running on the device. @param OutProcessInfos Will contain the information for running processes. @return The number of returned processes.
- L366 _public function_ `virtual bool GetProcessSnapshotAsync(TFunction<void(const TArray<FTargetDeviceProcessInfo>&)> CompleteHandler)` — Creates a snapshot of processes currently running on the device. @param OutProcessInfos Will contain the information for running processes. @param CompleteHandler will be invoked when process snapshot information is available @return True if retrieving a process snapshot is supported
- L379 _protected function_ `virtual const class ITargetPlatform& GetTargetPlatform() const` — Temporary until we get rid of this.
- L388 _public prototype_ `virtual const class ITargetPlatformSettings& GetPlatformSettings() const;`
- L389 _public prototype_ `virtual const class ITargetPlatformControls& GetPlatformControls() const;`
- L396 _public prototype_ `virtual bool IsConnected() = 0;` — Checks whether this device is connected. @return true if the device is connected, false otherwise.
- L405 _public prototype_ `virtual bool IsDefault() const = 0;` — Checks whether this is the default device. Note that not all platforms may have a notion of default devices. @return true if this is the default device, false otherwise.
- L414 _public function_ `virtual bool IsAuthorized() const` — Checks whether this device is authorized to be used with this computer. This is true for most platforms by default, but may be false for mobile platforms @return true if this this device is authorized for launch
- L422 _public prototype_ `virtual bool PowerOff( bool Force ) = 0;` — Powers off the device. @param Force Whether to force powering off. @return true if the device will be powered off, false otherwise.
- L429 _public prototype_ `virtual bool PowerOn() = 0;` — Powers on the device. @return true if the device will be powered on, false otherwise.
- L437 _public prototype_ `virtual bool Reboot( bool bReconnect = false ) = 0;` — Reboot the device. @param bReconnect If true, wait and reconnect when done. @return true if the reboot was successful from the perspective of the PC .
- L445 _public prototype_ `virtual bool SupportsFeature( ETargetDeviceFeatures Feature ) const = 0;` — Checks whether the target device supports the specified feature. @param Feature The feature to check. @return true if the feature is supported, false otherwise.
- L453 _public prototype_ `virtual bool TerminateProcess( const int64 ProcessId ) = 0;` — Terminates a process that was launched on the device using the Launch() or Run() methods. @param ProcessId The identifier of the process to terminate. @return true if the process was terminated, false otherwise.
- L461 _public prototype_ `virtual void SetUserCredentials( const FString& UserName, const FString& UserPassword ) = 0;` — Set credentials for the user account to use on the device @param UserName The user account on the device we will run under @param UserPassword The password for the user account on the device we will run under.
- L470 _public prototype_ `virtual bool GetUserCredentials( FString& OutUserName, FString& OutUserPassword ) = 0;` — Get credentials for the user account to use on the device @param OutUserName The user account on the device we will run under @param OutUserPassword The password for the user account on the device we will run under @return true on success, false if not supported.
- L477 _public function_ `virtual void ExecuteConsoleCommand(const FString& ExecCommand) const` — Execute console command on the device @param ExecCommand Command to execute
- L488 _public function_ `virtual ITargetDeviceOutputPtr CreateDeviceOutputRouter(FOutputDevice* Output) const` — Create device output router This will route device logs into specified OutputDevice until connection to device is alive @param Output OutputDevice to where output should be routed (has to be thread safe) @return Valid router object for devices that support output routing
- L494 _public function_ `virtual bool TerminateLaunchedProcess(const FString & ProcessIdentifier)` — Cancel the application running on the device @param ProcessIdentifier The bundle id
- L501 _public function_ `virtual void ReloadGlobalShadersMap(const FString& GlobalShaderMapDirectory) const` — Execute console command on the device to reload the global shader map @param GlobalShaderMapDirectory path to directory that contains global shader map
- L522 _public function_ `virtual ITargetDeviceSocketPtr OpenConnection(uint32 ProtocolIndex)` — Opens a direct connection with the device allowing data exchange with a process running on the target. ProtocolIndex is a number that identifies the connection and has to be know both to the target process and the PC. There can be only one connection using a given protocol index at a time. You may check EHostProtocol enumeration for known protocols used by the engine. This function just opens a communication channel but doesn't check if there is a peer on the other end of the connection. To know this, you should either check IsProtocolAvailable or ITargetDeviceSocket::Connected. @param ProtocolIndex Unique index of the communication channel (from 0 to a platform-dependent maximum). @return Socket object on success, nullptr otherwise. @see CloseSocket, EHostProtocol, IsProtocolAvailable, ITargetDeviceSocket::Connected
- L530 _public function_ `virtual void CloseConnection(ITargetDeviceSocketPtr Socket)` — Closes a previously opened connection with a process on the target. @param Socket Socket object returned by OpenSocket. @see OpenSocket
- L540 _public function_ `virtual bool IsProtocolAvailable(uint32 ProtocolIndex) const` — Checks if connections using the given ProtocolIndex are available for this device at the moment. If this function returns true, it means that OpenConnection should succeed and communication with a game running on the target should be possible. @param ProtocolIndex Unique index of the communication channel (from 0 to a platform-dependent maximum). @return True if the protocol is available and we can connect to the device, false otherwise.
- L549 _public function_ `virtual bool IsPlatformAggregated() const` — Get the "All devices" flag for the platform @return true if the platform has an "All devices" proxy.
- L556 _public function_ `virtual FString GetAllDevicesName() const` — Get the "All devices" name @return "All devices" name.
- L563 _public function_ `virtual FName GetAllDevicesDefaultVariant() const` — Get the "All devices" default variant @return "All devices" default variant.
- L568 _public prototype_ `virtual ~ITargetDevice() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L86 _namespace_ `namespace TargetDeviceTypes`
- L94 _function_ `inline FString ToString(ETargetDeviceTypes DeviceType)` (scope `TargetDeviceTypes`) — Returns the string representation of the specified ETargetDeviceTypes value. @param DeviceType The value to get the string for. @return A string value.
- L123 _namespace_ `namespace TargetDeviceConnectionTypes`
- L131 _function_ `inline FString ToString(ETargetDeviceConnectionTypes DeviceConnectionType)` (scope `TargetDeviceConnectionTypes`) — Returns the string representation of the specified ETargetDeviceConnectionTypes value. @param DeviceConnectionType The value to get the string for. @return A string value.
- L255 _typedef_ `typedef TSharedPtr<class ITargetDevice, ESPMode::ThreadSafe> ITargetDevicePtr;` — Type definition for shared pointers to instances of ITargetDevice.
- L258 _typedef_ `typedef TSharedRef<class ITargetDevice, ESPMode::ThreadSafe> ITargetDeviceRef;` — Type definition for shared references to instances of ITargetDevice.
- L261 _typedef_ `typedef TWeakPtr<class ITargetDevice, ESPMode::ThreadSafe> ITargetDeviceWeakPtr;` — Type definition for weak pointers to instances of ITargetDevice.
- L264 _typedef_ `typedef TSharedPtr<class ITargetDeviceOutput, ESPMode::ThreadSafe> ITargetDeviceOutputPtr;` — Type definition for shared pointers to instances of ITargetDeviceOutput.

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetDeviceOutput.h` (Public)


#### class `ITargetDeviceOutput`  
`class ITargetDeviceOutput`  
_L10-15_
- desc: Interface for target device output log reader.
- L14 _public prototype_ `virtual ~ITargetDeviceOutput() = default;` — Virtual destructor.

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetDeviceSocket.h` (Public)


#### class `ITargetDeviceSocket`  
`class ITargetDeviceSocket`  
_L13-61_
- desc: Interface for target device sockets. This interface provides an abstraction for communicating with processes running on the target.
- L32 _public prototype_ `virtual bool Send(const void* Data, uint64 BytesToSend) = 0;` — Send data to a connected process on the target device. This is a blocking operation and it will return only after the whole buffer has been sent or an error occurs (e.g. the target disconnects). False return value typically indicates that the remote peer has closed the connection on their side. If it happens, this socket should be closed as well. @param Data        Buffer containing data to be sent (. @param BytesToSend The number of bytes from Data that are to be sent. @return true if communication was successful, false otherwise. @see IHostDevice::OpenConnection, IHostDevice::CloseConnection
- L49 _public prototype_ `virtual bool Receive(void* Data, uint64 BytesToReceive) = 0;` — Receive data from a connected process on the target device. This is a blocking operation and it will return only after the expected amount of data has been received or an error occurs (e.g. the target disconnects). False return value typically indicates that the remote peer has closed the connection on their side. If it happens, this socket should be closed as well. @param Data           Target buffer for the data to receive (it has to be large enough to store BytesToReceive). @param BytesToReceive The number of bytes to receive and store in Data. @return true if communication was successful, false otherwise. @see IHostDevice::OpenConnection, IHostDevice::CloseConnection
- L54 _public prototype_ `virtual bool Connected() const = 0;` — Returns true if this socket is actually connected to another peer and is ready to send/receive data.
- L59 _public prototype_ `virtual ~ITargetDeviceSocket() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L64 _typedef_ `typedef TSharedRef<ITargetDeviceSocket, ESPMode::ThreadSafe> ITargetDeviceSocketRef;` — Type definition for shared references to instances of IPlatformHostSocket.
- L67 _typedef_ `typedef TSharedPtr<ITargetDeviceSocket, ESPMode::ThreadSafe> ITargetDeviceSocketPtr;` — Type definition for shared pointers to instances of IPlatformHostSocket.

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetPlatform.h` (Public)


#### class `ITargetPlatform`  
`class ITargetPlatform : public ITargetPlatformSettings, public ITargetPlatformControls`  
_L37-69_
- inherits: `ITargetPlatformSettings,ITargetPlatformControls`
- desc: Interface for target platforms. This interface is only left for compatibility with platforms that have not been updated to TargetPlatformSettings and TargetPlatformControls Please only add new functions to ITargetPlatformSettings(if the sdk is not required) or ITargetPlatformControls(if the sdk is required)
- L40 _public function_ `const ITargetPlatformControls* GetTargetPlatformControls() const`
- L43 _public function_ `ITargetPlatform() :ITargetPlatformControls(this)`
- L47 _public prototype_ `static const ITargetPlatform* GetPlatformFromOrdinal(int32 Ordinal);` — Given a platform ordinal number, returns the corresponding ITargetPlatform instance
- L51 _public prototype_ `DECLARE_EVENT_OneParam(ITargetPlatform, FOnTargetDeviceDiscovered, ITargetDeviceRef );` — Gets an event delegate that is executed when a new target device has been discovered.
- L53 _public prototype_ `static FOnTargetDeviceDiscovered& OnDeviceDiscovered();` — `UE_DEPRECATED(5.4, "ITargetPlatform::OnDeviceDiscovered is deprecated, use ITargetPlatformControls::OnDeviceDiscovered instead")`
- L58 _public prototype_ `DECLARE_EVENT_OneParam(ITargetPlatform, FOnTargetDeviceLost, ITargetDeviceRef );` — Gets an event delegate that is executed when a target device has been lost, i.e. disconnected or timed out.
- L60 _public prototype_ `static FOnTargetDeviceLost& OnDeviceLost();` — `UE_DEPRECATED(5.4, "ITargetPlatform::OnDeviceLost is deprecated, use ITargetPlatformControls::OnDeviceLost instead")`
- L65 _public prototype_ `virtual ~ITargetPlatform() = default;` — Virtual destructor.
- L68 _protected prototype_ `static int32 AssignPlatformOrdinal(const ITargetPlatform& Platform);`

#### struct `FTargetPlatform`  
`struct FTargetPlatform`  
_L81-104_
- L83 _public function_ `inline FTargetPlatform(const ITargetPlatform& Platform)`
- L88 _public function_ `inline uint32 GetOrdinal() const`
- L90 _public function_ `bool operator<(const FTargetPlatform& Other) const`
- L95 _public function_ `bool operator==(const FTargetPlatform& Other) const`
- L103 _private member_ `uint32 Ordinal = 0;`

#### class `FTargetPlatformSet`  
`class FTargetPlatformSet`  
_L109-205_
- desc: Target platform set implementation using bitmask for compactness
- L112 _public function_ `inline void Add(const FTargetPlatform& Platform)`
- L119 _public function_ `inline void Remove(const FTargetPlatform& Platform)`
- L127 _public function_ `inline void Remove(const FTargetPlatformSet& Platforms)` — Remove all members from the Platforms set from this set
- L133 _public function_ `inline bool Contains(const FTargetPlatform& Platform) const` — Check if this set contains any of the members of the Other set
- L141 _public function_ `bool ContainsAny(const FTargetPlatformSet& Other) const` — Check if this set contains any of the members of the Other set
- L146 _public function_ `bool IsEmpty() const`
- L151 _public function_ `void Merge(const FTargetPlatformSet& Other)`
- L156 _public function_ `void Clear()`
- L161 _public function_ `bool operator==(const FTargetPlatformSet& Other) const`
- L166 _public function_ `uint32 GetHash() const`
- L178 _public function_ `template<typename Func> void ForEach(Func&& Callback) const` — Iterate over all set members @param Callback - callback accepting a const ITargetPlatform* argument
- L204 _private member_ `uint64 Mask = 0;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace PlatformInfo`
- L51 _delegate_ `DECLARE_EVENT_OneParam(ITargetPlatform, FOnTargetDeviceDiscovered, ITargetDeviceRef );` — Gets an event delegate that is executed when a new target device has been discovered.
- L58 _delegate_ `DECLARE_EVENT_OneParam(ITargetPlatform, FOnTargetDeviceLost, ITargetDeviceRef );` — Gets an event delegate that is executed when a target device has been lost, i.e. disconnected or timed out.
- L100 _function_ `friend inline uint32 GetTypeHash(const FTargetPlatform& Key)`

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetPlatformControls.h` (Public)


#### enum `EPlatformAuthentication`  
`enum class EPlatformAuthentication`  
_L17-22_
- L19 _public enumerator_ `Never`
- L20 _public enumerator_ `Possible`
- L21 _public enumerator_ `Always`

#### class `ITargetPlatformControls`  
`class ITargetPlatformControls`  
_L61-523_
- L64 _public function_ `ITargetPlatformControls(ITargetPlatformSettings* InTargetPlatformSettings) :TargetPlatformSettings(InTargetPlatformSettings)`
- L72 _public prototype_ `virtual bool AddDevice(const FString& DeviceName, bool bDefault) = 0;` — Add a target device by name. @param DeviceName The name of the device to add. @param bDefault Whether the added device should be the default. @return true if the device was added, false otherwise.
- L84 _public prototype_ `virtual bool AddDevice(const FString& DeviceId, const FString& DeviceUserFriendlyName, const FString& Username, const FString& Password, bool bDefault) = 0;` — Add a target device. @param DeviceId The id of the device to add. @param DeviceUserFriendlyName The user friendly name of the device to add. @param Username The username for the device to add. @param Password The password for the device to add. @param bDefault Whether the added device should be the default. @return true if the device was added, false otherwise.
- L92 _public prototype_ `virtual FString PlatformName() const = 0;` — Returns the name of this platform @return Platform name. @see DisplayName
- L99 _public prototype_ `virtual FText DisplayName() const = 0;` — Gets the platform's display name. @see PlatformName
- L112 _public prototype_ `virtual int32 CheckRequirements(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FString& OutTutorialPath, FString& OutDocumentationPath, FText& CustomizedLogMessage) const = 0;` — Checks whether the platform's build requirements are met so that we can do things like package for the platform. @param bProjectHasCode true if the project has code, and therefore any compilation based SDK requirements should be checked. @param Configuration The configuration being built @param bRequiresAssetNativization Whether asset nativization is required @param OutTutorialPath Let's the platform tell the editor a path to show some information about how to fix any problem. @param OutDocumentationPath Let's the platform tell the editor a documentation path. @param CustomizedLogMessage Let's the platform return a customized log message instead of the default for the returned status. @return A mask of ETargetPlatformReadyStatus flags to indicate missing requirements, or 0 if all requirements are met.
- L123 _public prototype_ `virtual bool RequiresTempTarget(bool bProjectHasCode, EBuildConfiguration Configuration, bool bRequiresAssetNativization, FText& OutReason) const = 0;` — Checks whether the current project needs a temporary .target.cs file to be packaged as a code project. @param bProjectHasCode Whether the project has code @param Configuration The configuration being built @param bRequiresAssetNativization Whether asset nativization is enabled @param OutReason On success, includes a description of the reason why a target is required @return True if a temporary target is required
- L128 _public prototype_ `virtual const PlatformInfo::FTargetPlatformInfo& GetTargetPlatformInfo() const = 0;` — Returns the information about this target platform
- L133 _public prototype_ `virtual const FDataDrivenPlatformInfo& GetPlatformInfo() const = 0;` — Returns the information about the platform as a whole
- L138 _public prototype_ `virtual FString CookingDeviceProfileName() const = 0;` — Gets the name of the device profile to use when cooking this TargetPlatform
- L143 _public prototype_ `virtual void EnableDeviceCheck(bool OnOff) = 0;` — Enables/Disable the device check
- L150 _public prototype_ `virtual void GetAllDevices(TArray<ITargetDevicePtr>& OutDevices) const = 0;` — Returns all discoverable physical devices. @param OutDevices Will contain a list of discovered devices.
- L157 _public prototype_ `virtual FName GetZlibReplacementFormat() const = 0;` — Gets a new compression format to use in place of Zlib. This should be rarely implemented @return Compression format to use instead of Zlib
- L164 _public prototype_ `virtual int64 GetMemoryMappingAlignment() const = 0;` — Gets the alignment of memory mapping for this platform, typically the page size. @return alignment of memory mapping.
- L173 _public prototype_ `virtual bool GenerateStreamingInstallManifest(const TMultiMap<FString, int32>& PakchunkMap, const TSet<int32>& PakchunkIndicesInUse) const = 0;` — Generates a platform specific asset manifest given an array of FAssetData. @param PakchunkMap A map of asset path to Pakchunk file indices for all of the assets. @param PakchunkIndicesInUse A set of all Pakchunk file indices used by this set of assets. @return true if the manifest was successfully generated, or if the platform doesn't need a manifest .
- L182 _public prototype_ `virtual ITargetDevicePtr GetDefaultDevice() const = 0;` — Gets the default device. Note that not all platforms may have a notion of default devices. @return Default device.
- L190 _public prototype_ `virtual ITargetDevicePtr GetDevice(const FTargetDeviceId& DeviceId) = 0;` — Gets an interface to the specified device. @param DeviceId The identifier of the device to get. @return The target device (can be nullptr).
- L197 _public prototype_ `virtual bool HasEditorOnlyData() const = 0;` — Checks whether this platform has only editor data (typically desktop platforms). @return true if this platform has editor only data, false otherwise.
- L206 _public prototype_ `virtual bool AllowsEditorObjects() const = 0;` — Checks whether this platform will allow editor objects to be cooked, as opposed to editoronly properties. This will allow a target platform to cook editoronly objects, but as if they were being cooked for a client. This is useful for a cooked editor scenario, where every pacakge is cooked, editor and game alike. @return true if this platform allows editor objects to be cooked, false otherwise.
- L214 _public prototype_ `virtual bool AllowsDevelopmentObjects() const = 0;` — Checks whether this platform will allow development objects to be cooked. This is separate from AllowsEditorObjects because cooked editors can be shipped with editor objects but still need to remove development assets. @return true if this platform allows development objects to be cooked, false otherwise.
- L221 _public prototype_ `virtual bool IsClientOnly() const = 0;` — Checks whether this platform is only a client (and must connect to a server to run). @return true if this platform must connect to a server.
- L228 _public prototype_ `virtual bool IsLittleEndian() const = 0;` — Checks whether this platform is little endian. @return true if this platform is little-endian, false otherwise.
- L235 _public prototype_ `virtual bool IsServerOnly() const = 0;` — Checks whether this platform is only a server. @return true if this platform has no graphics or audio, etc, false otherwise.
- L240 _public prototype_ `virtual bool IsEnabledForPlugin(const IPlugin& Plugin) const = 0;` — Checks whether this platform is enabled for the given plugin in the currently active project.
- L247 _public prototype_ `virtual bool CanSupportRemoteShaderCompile() const = 0;` — Checks whether this platform supports shader compilation over XGE interface. @return true if this platform can distribute shader compilation threads with XGE.
- L254 _public prototype_ `virtual void GetShaderCompilerDependencies(TArray<FString>& OutDependencies) const = 0;` — Provide platform specific file dependency patterns for SN-DBS shader compilation. @param OutDependencies Platform specific dependency file patterns are uniquely appended to this array.
- L264 _public prototype_ `virtual bool IsSdkInstalled(bool bProjectHasCode, FString& OutDocumentationPath) const = 0;` — Checks whether the platform's SDK requirements are met so that we can do things like package for the platform @param bProjectHasCode true if the project has code, and therefore any compilation based SDK requirements should be checked @param OutDocumentationPath Let's the platform tell the editor a path to show some documentation about how to set up the SDK @return true if the platform is ready for use
- L271 _public prototype_ `virtual bool RequiresCookedData() const = 0;` — Checks whether this platform requires cooked data (typically console platforms). @return true if this platform requires cooked data, false otherwise.
- L279 _public prototype_ `virtual bool RequiresOriginalReleaseVersionForPatch() const = 0;` — Checks whether this platform requires the originally released version (in addition to the previously released version) to create a patch @return true if this platform requires the originally released version, false otherwise.
- L287 _public prototype_ `virtual bool HasNonTrivialPatchGeneration() const = 0;` — Checks whether the platform has non-trivial patching requirements, where regular workflows may result in invalid patches. It is recommended to check the platform's documentation. @return true if this platform has non-trivial patching requirements, false otherwise.
- L294 _public prototype_ `virtual bool HasSecurePackageFormat() const = 0;` — Checks whether this platform has a secure shippable package format, and therefore doesn't need any encryption or signing support @return true if this platform has a secure shippable package format, false otherwise.
- L301 _public prototype_ `virtual EPlatformAuthentication RequiresUserCredentials() const = 0;` — Checks whether this platform requires user credentials (typically server platforms). @return enum if this platform requires user credentials.
- L306 _public prototype_ `virtual bool SupportsAutoSDK() const = 0;` — Returns true if the platform supports the AutoSDK system
- L314 _public prototype_ `virtual bool SupportsBuildTarget(EBuildTargetType TargetType) const = 0;` — Checks whether this platform supports the specified build target, i.e. Game or Editor. @param TargetType The target type to check. @return true if the build target is supported, false otherwise.
- L322 _public prototype_ `virtual EBuildTargetType GetRuntimePlatformType() const = 0;` — Return the TargetType this platform uses at runtime. Some TargetPlatforms like CookedEditors need to cook with one type, like Client, but then will run as an Editor. Decisions made based solely on the cook type may cause data mismatches if the runtime type is different. This is also useful for knowing what plugins will be enabled at runtime.
- L327 _public prototype_ `virtual void GetPlatformSpecificProjectAnalytics(TArray<struct FAnalyticsEventAttribute>& AnalyticsParamArray) const = 0;` — Gather per-project cook/package analytics
- L333 _public function_ `virtual void RefreshAllDevices()` — Manually refresh the devices
- L341 _public prototype_ `virtual FName GetPhysicsFormat(class UBodySetup* Body) const = 0;` — Gets the format to use for a particular body setup. @return Physics format.
- L350 _public prototype_ `virtual void GetTextureFormats(const class UTexture* Texture, TArray< TArray<FName> >& OutFormats) const = 0;` — Gets the texture format to use for each layer in the given texture, for each of the platform's formats. _Most_ platforms only supply one format for a given texture, so OutFormats.Num() is usually 1. The exception is Android_Multi, where you can get several formats due to targeting different devices. OutFormats.Num() == NumberOfPlatformFormats OutFormats[0...N].Num() == Texture->Source.GetNumLayers().
- L357 _public prototype_ `virtual void GetTextureSizeLimits(uint64 & OutMaximumSurfaceBytes, uint64 & OutMaximumPackageBytes) const = 0;` — Get the limitations on texture size (bytes) on this platform this limitation is in addition to any dimension limits (specified in device profiles) all built textures must be <= this size
- L365 _public function_ `virtual void GetAllTextureFormats(TArray<FName>& OutFormats) const` — `UE_DEPRECATED(5.9, "GetAllTextureFormats is deprecated.")` — Gets the texture formats this platform can use @param OutFormats will contain all the texture formats which are possible for this platform
- L370 _public prototype_ `virtual void GetTextureFormatModuleHints(TArray<FName>& OutModuleNames) const = 0;` — GetTextureFormatModuleHints is not used and should be deleted
- L376 _public prototype_ `virtual FName FinalizeVirtualTextureLayerFormat(FName Format) const = 0;` — Platforms that support multiple texture compression variants might want to use a single specific variant for virtual textures to reduce fragmentation
- L379 _public prototype_ `virtual bool SupportsLQCompressionTextureFormat() const = 0;` — whether R5G6B5 and B5G5R5A1 is supported
- L387 _public prototype_ `virtual FName GetWaveFormat(const class USoundWave* Wave) const = 0;` — Gets the format to use for a particular piece of audio. @param Wave The sound node wave to get the format for. @return Name of the wave format.
- L394 _public prototype_ `virtual void GetAllWaveFormats(TArray<FName>& OutFormats) const = 0;` — Gets all the formats which can be returned from GetWaveFormat @param output array of all the formats
- L401 _public prototype_ `virtual void GetWaveFormatModuleHints(TArray<FName>& OutModuleNames) const = 0;` — Gets a list of modules that may contain the GetAllWaveFormats. This is optional - if any required audio format isn't found in this list, then it will use the old path of loading all audio format modules to gather all available audio formats
- L409 _public prototype_ `virtual bool AllowAudioVisualData() const = 0;` — Checks whether if this platform wants AV data (defaults to !IsServerOnly(), which is the standard reason why we don't want AV data) Used so that custom target platforms can remove AV data, but is not a server-only platform @return true if this platform allows AV data to be cooked, false otherwise.
- L412 _public prototype_ `virtual bool AllowObject(const class UObject* Object) const = 0;` — Checks if this Target will want to load this object (generally used to mark an object to not be cooked for this target)
- L420 _public prototype_ `virtual FName GetMeshBuilderModuleName() const = 0;` — Gets the name of the mesh builder module that is responsible for building static and skeletal mesh derived data for this platform. @return The name of a mesh builder module.
- L429 _public prototype_ `virtual bool PackageBuild(const FString& InPackgeDirectory) = 0;` — Package a build for the given platform @param InPackgeDirectory The directory that contains what needs to be packaged. @return bool true on success, false otherwise.
- L434 _public prototype_ `virtual bool SupportsVariants() const = 0;` — Returns true if the platform is part of a family of variants
- L441 _public prototype_ `virtual float GetVariantPriority() const = 0;` — Gets the variant priority of this platform @return float priority for this platform variant.
- L446 _public prototype_ `virtual bool SendLowerCaseFilePaths() const = 0;` — Whether or not to send all lower-case filepaths when connecting over a fileserver connection.
- L451 _public prototype_ `virtual void GetBuildProjectSettingKeys(FString& OutSection, TArray<FString>& InBoolKeys, TArray<FString>& InIntKeys, TArray<FString>& InStringKeys) const = 0;` — Project settings to check to determine if a build should occur
- L462 _public prototype_ `virtual int32 GetPlatformOrdinal() const = 0;` — Get unique integer identifier for this platform. The implementation will assign an ordinal to each target platform at startup, assigning a value of 0, 1, 2, etc in order to make the ordinals usable as array / bit mask indices. @return int32 A unique integer which may be used to identify target platform during the current session only (note: not stable across runs).
- L467 _public prototype_ `static const ITargetPlatformControls* GetPlatformFromOrdinal(int32 Ordinal);` — Given a platform ordinal number, returns the corresponding ITargetPlatform instance
- L472 _public prototype_ `virtual TSharedPtr<IDeviceManagerCustomPlatformWidgetCreator> GetCustomWidgetCreator() const = 0;` — Returns custom DeviceManager widget creator for this platform
- L477 _public prototype_ `virtual bool ShouldExpandTo32Bit(const uint16* Indices, const int32 NumIndices) const = 0;` — Returns wheter or not this 16bit index buffer should be promoted to 32bit
- L482 _public prototype_ `virtual bool CopyFileToTarget(const FString& DeviceId, const FString& HostFilename, const FString& TargetFilename, const TMap<FString, FString>& CustomPlatformData) = 0;` — Copy a file to the target
- L488 _public prototype_ `virtual void InitializeForCook() = 0;` — Hook called when a TargetPlatform is selected for cooking. Load any required assets or data. May be called multiple times per process; it is called each time a cook starts for the platform.
- L493 _public prototype_ `virtual void GetExtraPackagesToCook(TArray<FName>& PackageNames) const = 0;` — Gets a list of package names to cook when cooking this platform
- L498 _public prototype_ `virtual bool InitializeHostPlatform() = 0;` — Initializes the host platform to support target devices (may be called multiple times after an SDK is installed while running)
- L500 _public function_ `ITargetPlatformSettings* GetTargetPlatformSettings() const`
- L506 _public prototype_ `virtual ~ITargetPlatformControls() = default;` — Virtual destructor.
- L511 _public prototype_ `DECLARE_EVENT_OneParam(ITargetPlatformControls, FOnTargetDeviceDiscovered, ITargetDeviceRef );` — Gets an event delegate that is executed when a new target device has been discovered.
- L512 _public prototype_ `static FOnTargetDeviceDiscovered& OnDeviceDiscovered();`
- L517 _public prototype_ `DECLARE_EVENT_OneParam(ITargetPlatformControls, FOnTargetDeviceLost, ITargetDeviceRef );` — Gets an event delegate that is executed when a target device has been lost, i.e. disconnected or timed out.
- L518 _public prototype_ `static FOnTargetDeviceLost& OnDeviceLost();`
- L521 _protected member_ `ITargetPlatformSettings* TargetPlatformSettings;`
- L522 _protected prototype_ `static int32 AssignPlatformOrdinal(const ITargetPlatformControls& Platform);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PlatformInfo`
- L27 _namespace_ `namespace ETargetPlatformReadyStatus`
- L30 _variable_ `inline const int32 Ready = 0;` (scope `ETargetPlatformReadyStatus`) — Ready
- L33 _variable_ `inline const int32 SDKNotFound = 1;` (scope `ETargetPlatformReadyStatus`) — SDK Not Found
- L36 _variable_ `inline const int32 CodeUnsupported = 2;` (scope `ETargetPlatformReadyStatus`) — Code Build Not Supported
- L39 _variable_ `inline const int32 PluginsUnsupported = 4;` (scope `ETargetPlatformReadyStatus`) — Plugins Not Supported
- L42 _variable_ `inline const int32 SigningKeyNotFound = 8;` (scope `ETargetPlatformReadyStatus`) — Signing Key Not Found
- L45 _variable_ `inline const int32 ProvisionNotFound = 16;` (scope `ETargetPlatformReadyStatus`) — Provision Not Found
- L48 _variable_ `inline const int32 ManifestNotFound = 32;` (scope `ETargetPlatformReadyStatus`) — Manifest Not Found
- L51 _variable_ `inline const int32 RemoveServerNameEmpty = 64;` (scope `ETargetPlatformReadyStatus`) — Remote Server Name Empty
- L54 _variable_ `inline const int32 LicenseNotAccepted = 128;` (scope `ETargetPlatformReadyStatus`) — License Not Accepted
- L57 _variable_ `inline const int32 CodeBuildRequired = 256;` (scope `ETargetPlatformReadyStatus`) — Code Build Required
- L511 _delegate_ `DECLARE_EVENT_OneParam(ITargetPlatformControls, FOnTargetDeviceDiscovered, ITargetDeviceRef );` — Gets an event delegate that is executed when a new target device has been discovered.
- L517 _delegate_ `DECLARE_EVENT_OneParam(ITargetPlatformControls, FOnTargetDeviceLost, ITargetDeviceRef );` — Gets an event delegate that is executed when a target device has been lost, i.e. disconnected or timed out.

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetPlatformControlsModule.h` (Public)


#### class `ITargetPlatformControlsModule`  
`class ITargetPlatformControlsModule : public IModuleInterface`  
_L12-53_
- inherits: `IModuleInterface`
- desc: Interface for target platform modules.
- L18 _public function_ `virtual ~ITargetPlatformControlsModule()` — Virtual destructor.
- L33 _public function_ `TArray<ITargetPlatformControls*> GetTargetPlatformControls(FName& PlatformSettingsModuleName)` — Gets the module's target platforms. This should be overridden by each platform, but currently, we are re-using the single internal GetTargetPlatform method the old TPModules will implement @return The target platform.
- L48 _protected prototype_ `virtual void GetTargetPlatformControls(TArray<ITargetPlatformControls*>& TargetPlatforms, FName& PlatformSettingsModuleName) = 0;` — This is where each platform module will fill out an array
- L52 _private member_ `TArray<ITargetPlatformControls*> AllTargetPlatforms;` — Holds the target platforms.

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetPlatformManagerModule.h` (Public)


#### class `ITargetPlatformManagerModule`  
`class ITargetPlatformManagerModule : public IModuleInterface`  
_L20-231_
- inherits: `IModuleInterface`
- desc: Module for the target platform manager
- L25 _public function_ `static FORCEINLINE ITargetPlatformManagerModule* Get()`
- L41 _public prototype_ `virtual const class IAudioFormat* FindAudioFormat( FName Name ) = 0;` — Finds an audio format with the specified name. @param Name Name of the format to find. @return The audio format, or nullptr if not found.
- L49 _public prototype_ `virtual const class IPhysXCooking* FindPhysXCooking( FName Name ) = 0;` — Finds a PhysX format with the specified name. @param Name Name of the format to find. @return The PhysX format, or nullptr if not found.
- L57 _public prototype_ `virtual const class IShaderFormat* FindShaderFormat( FName Name ) = 0;` — Finds a shader format with the specified name. @param Name Name of the format to find. @return The shader format, or nullptr if not found.
- L65 _public prototype_ `virtual const class ITextureFormat* FindTextureFormat( FName Name ) = 0;` — Finds a texture format with the specified name. @param Name Name of the format to find. @return The texture format, or nullptr if not found.
- L73 _public prototype_ `virtual ITargetDevicePtr FindTargetDevice( const FTargetDeviceId& DeviceId ) = 0;` — Finds a target device by identifier. @param DeviceId The device identifier. @return The target device, or nullptr if not found.
- L81 _public prototype_ `virtual ITargetPlatform* FindTargetPlatform( FStringView Name ) = 0;` — Finds a target platform by name. @param Name The target platform's short or long name. @return The target platform, or nullptr if not found.
- L89 _public prototype_ `virtual ITargetPlatform* FindTargetPlatform(FName Name) = 0;` — Finds a target platform by name. @param Name The target platform's short or long name. @return The target platform, or nullptr if not found.
- L97 _public prototype_ `virtual ITargetPlatform* FindTargetPlatform(const TCHAR* Name) = 0;` — Finds a target platform by name. @param Name The target platform's short or long name. @return The target platform, or nullptr if not found.
- L106 _public prototype_ `virtual ITargetPlatform* FindTargetPlatformWithSupport(FName SupportType, FName RequiredSupportedValue) = 0;` — Finds a target platform by looking for one that supports a given value for a generic type of support @param Name SupportClass The type of support needed (like "ShaderFormat") @param RequiredSupportValue The value of the supported type that is needed @return The target platform, or nullptr if not found.
- L114 _public prototype_ `virtual const TArray<ITargetPlatform*>& GetCookingTargetPlatforms() = 0;` — `UE_DEPRECATED(5.1, "Use GetActiveTargetPlatforms instead of GetCookingTargetPlatforms")` — Return the list of platforms which we need to support when cooking (only set when actually cooking) @return Collection of platforms.
- L121 _public prototype_ `virtual const TArray<ITargetPlatform*>& GetActiveTargetPlatforms() = 0;` — Return the list of the ITargetPlatforms that we want to build data for. @return Collection of platforms.
- L128 _public prototype_ `virtual const TArray<const class IAudioFormat*>& GetAudioFormats() = 0;` — Returns the list of all IAudioFormats that were located in DLLs. @return Collection of audio formats.
- L135 _public prototype_ `virtual const TArray<const class IPhysXCooking*>& GetPhysXCooking() = 0;` — Returns the list of all IPhysXCooking that were located in DLLs. @return Collection of PhysX formats.
- L144 _public prototype_ `virtual ITargetPlatform* GetRunningTargetPlatform() = 0;` — Returns the target platform that is currently running. Note: This method only returns a Target Platform when WITH_EDITOR. @return Running target platform.
- L151 _public prototype_ `virtual const TArray<const class IShaderFormat*>& GetShaderFormats() = 0;` — Returns the list of all ITextureFormats that were located in DLLs. @return Collection of shader formats.
- L158 _public prototype_ `virtual const TArray<ITargetPlatform*>& GetTargetPlatforms() = 0;` — Returns the list of all ITargetPlatforms that were located in DLLs. @return Collection of platforms.
- L159 _public prototype_ `virtual const TArray<ITargetPlatformControls*>& GetTargetPlatformControls() = 0;`
- L160 _public prototype_ `virtual const TArray<ITargetPlatformSettings*>& GetTargetPlatformSettings() = 0;`
- L168 _public function_ `TArray<const class ITextureFormat*> GetTextureFormats()` — `UE_DEPRECATED(5.6, "Not thread safe, use FindTextureFormat")` — Returns the list of all ITextureFormats that were located in DLLs. @return Collection of texture formats.
- L176 _public prototype_ `virtual bool HasInitErrors(FString* OutErrorMessages) const = 0;` — Determine if there were errors during the initialization of the platform manager. @param OutErrorMessages Optional pointer to an FString that will have the error messages appended to it. @return True if there were errors during the initialization of the platform manager, False otherwise.
- L184 _public prototype_ `virtual void Invalidate() = 0;` — Invalidates the target platform module. Invalidate should be called if any TargetPlatform modules get loaded/unloaded/reloaded during runtime to give the implementation the chance to rebuild all its internal states and caches.
- L191 _public prototype_ `virtual bool RestrictFormatsToRuntimeOnly() = 0;` — Checks whether we should only build formats that are actually required for use by the runtime. @return true if formats are restricted, false otherwise.
- L199 _public prototype_ `virtual uint32 ShaderFormatVersion(FName Name) = 0;` — Gets the shader format version for the specified shader. @param Name Name of the shader format to get the version for. @return Version number.
- L205 _public function_ `virtual bool UpdatePlatformEnvironment(const FString& PlatformName, TArray<FString> &Keys, TArray<FString> &Values) final` — `UE_DEPRECATED(5.8, "Deprecated, please use SetupEnvironmentVariables instead")` — Allows changes to environment for a given platform
- L210 _public prototype_ `virtual void SetupEnvironmentVariables(TArray<FString>& EnvVarNames, const TArray<FString>& EnvVarValues) = 0;` — Allows changes to the environment
- L213 _public prototype_ `virtual FOnTargetPlatformsInvalidated& GetOnTargetPlatformsInvalidatedDelegate() = 0;` — A callback that holders of ITargetPlatform* must subscribe to to be notified of when the ITargetPlatform* has been invalidated and should be requeried from e.g. FindTargetPlatform
- L217 _public prototype_ `virtual bool UpdateAfterSDKInstall(FName TargetPlatformName) = 0;` — After installing an SDK with Turnkey, this will refresh the TargetPlatform, find devices, etc
- L221 _public prototype_ `~ITargetPlatformManagerModule() = default;` — Virtual destructor.
- L230 _private prototype_ `virtual void Initialize() = 0;` — Performs all module setup (SDK validation, platform discovery, format loading), called after the module is loaded and before any other methods are used. Separating this from construction allows the async UBT process (kicked off via FDelayedAutoRegisterHelper) more time to finish before we block waiting for it.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTargetPlatformsInvalidated);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTargetPlatformsInvalidated);`

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetPlatformModule.h` (Public)


#### class `ITargetPlatformModule`  
`class ITargetPlatformModule : public IModuleInterface`  
_L17-65_
- inherits: `IModuleInterface`
- desc: Interface for target platform modules.
- L24 _public function_ `virtual ~ITargetPlatformModule()` — Virtual destructor.
- L39 _public function_ `TArray<ITargetPlatform*> GetTargetPlatforms()` — Gets the module's target platforms. This should be overridden by each platform, but currently, we are re-using the single internal GetTargetPlatform method the old TPModules will implement @return The target platform.
- L49 _public member_ `TArray<ITargetPlatformSettings*> PlatformSettings;`
- L50 _public member_ `TArray<ITargetPlatformControls*> PlatformControls;`
- L57 _protected prototype_ `virtual void GetTargetPlatforms(TArray<ITargetPlatform*>& TargetPlatforms) = 0;` — This is where each platform module will fill out an array
- L58 _protected function_ `virtual void GetTargetPlatforms(TArray<ITargetPlatform*>& TargetPlatforms, TArray<ITargetPlatformSettings*> TargetPlatformSettings, TArray<ITargetPlatformControls*> TargetPlatformControls)`
- L64 _private member_ `TArray<ITargetPlatform*> AllTargetPlatforms;` — Holds the target platforms.

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetPlatformSettings.h` (Public)


#### enum `EOfflineBVHMode`  
`enum class EOfflineBVHMode`  
_L6-11_
- L8 _public enumerator_ `Disabled`
- L9 _public enumerator_ `MaximizePerformance`
- L10 _public enumerator_ `MinimizeMemory`

#### enum `ERayTracingRuntimeMode`  
`enum class ERayTracingRuntimeMode : uint8`  
_L13-18_
- L15 _public enumerator_ `Disabled`
- L16 _public enumerator_ `Inline`
- L17 _public enumerator_ `Full`

#### enum `ETargetPlatformFeatures`  
`enum class ETargetPlatformFeatures`  
_L23-117_
- desc: Enumerates features that may be supported by target platforms.
- L26 _public enumerator_ `AudioStreaming` — Audio Streaming
- L29 _public enumerator_ `DistanceFieldShadows` — Distance field shadows.
- L32 _public enumerator_ `DistanceFieldAO` — Distance field AO.
- L35 _public enumerator_ `GrayscaleSRGB` — Gray scale SRGB texture formats support.
- L38 _public enumerator_ `HighQualityLightmaps` — High quality light maps.
- L41 _public enumerator_ `LowQualityLightmaps` — Low quality light maps.
- L44 _public enumerator_ `MultipleGameInstances` — Run multiple game instances on a single device.
- L47 _public enumerator_ `Packaging` — Builds can be packaged for this platform.
- L50 _public enumerator_ `SdkConnectDisconnect` — Connect and disconnect devices through the SDK.
- L53 _public enumerator_ `TextureStreaming` — Texture streaming.
- L56 _public enumerator_ `MeshLODStreaming` — Mesh LOD streaming.
- L59 _public enumerator_ `LandscapeMeshLODStreaming UE_DEPRECATED(5.1, "LandscapeMeshLODStreaming is now deprecated and will be removed.")` — Landscape visual mesh LOD streaming.
- L62 _public enumerator_ `UserCredentials` — User credentials are required to use the device.
- L65 _public enumerator_ `MobileRendering` — The platform uses the mobile forward pipeline
- L68 _public enumerator_ `DeferredRendering` — The platform uses the deferred pipeline, typically PC/Console platforms
- L71 _public enumerator_ `ShouldSplitPaksIntoSmallerSizes` — Should split paks into smaller sized paks
- L74 _public enumerator_ `HalfFloatVertexFormat` — The platform supports half float vertex format
- L77 _public enumerator_ `DeviceOutputLog` — The platform supports the experimental Device Output Log window
- L80 _public enumerator_ `MemoryMappedFiles` — The platform supports memory mapped files
- L83 _public enumerator_ `MemoryMappedAudio` — The platform supports memory mapped audio
- L86 _public enumerator_ `MemoryMappedAnimation` — The platform supports memory mapped animation
- L89 _public enumerator_ `SparseTextures` — The platform supports sparse textures
- L92 _public enumerator_ `VirtualTextureStreaming UE_DEPRECATED(5.6, "VirtualTextureStreaming is now deprecated and will be removed.")` — Can we use the virtual texture streaming system on this platform.
- L95 _public enumerator_ `LumenGI` — Lumen Global Illumination.
- L98 _public enumerator_ `HardwareLZDecompression` — The platform supports hardware LZ decompression
- L101 _public enumerator_ `CookFileRegionMetadata` — The platform makes use of extra cook-time file region metadata in its packaging process.
- L104 _public enumerator_ `DirectDataExchange` — The platform supports communication (reading and writing data) between a target a connected PC.
- L107 _public enumerator_ `NormalmapLAEncodingMode` — The platform supports Luminance + Alpha encoding mode for normalmaps
- L110 _public enumerator_ `ShowAggregateDevice` — Should the Aggregate Device be shown for this platform (ex: All_Android_on_...)
- L113 _public enumerator_ `SupportsMultipleConnectionTypes` — Does the platform allow various connection types to be used (ie: wifi and usb)
- L116 _public enumerator_ `CanCookPackages` — The platform can cook packages (e.g. CookedCooker)

#### class `ITargetPlatformSettings`  
`class ITargetPlatformSettings`  
_L119-339_
- L125 _public prototype_ `virtual FConfigCacheIni* GetConfigSystem() const = 0;` — Returns the config system object usable by this TargetPlatform. It should not be modified in anyway
- L132 _public prototype_ `virtual FString IniPlatformName() const = 0;` — Gets the platform's INI name (so an offline tool can load the INI for the given target platform). @see PlatformName
- L141 _public prototype_ `virtual bool SupportsValueForType(FName SupportedType, FName RequiredSupportedValue) const = 0;` — Checks whether the target platform supports the specified value for the specified type of support @param SupportedType The type of support being queried @param RequiredSupportedValue The value of support needed @return true if the feature is supported, false otherwise.
- L146 _public prototype_ `virtual bool UsesForwardShading() const = 0;` — Gets whether the platform should use forward shading or not.
- L151 _public prototype_ `virtual bool UsesDBuffer() const = 0;` — Gets whether the platform should use DBuffer for decals.
- L156 _public prototype_ `virtual bool UsesBasePassVelocity() const = 0;` — Gets whether the platform should output velocity in the base pass.
- L161 _public prototype_ `virtual bool UsesSelectiveBasePassOutputs() const = 0;` — Gets whether the platform will use selective outputs in the base pass shaders.
- L166 _public prototype_ `virtual bool ShouldStripNaniteFallbackMeshes() const = 0;` — Gets whether Nanite fallback meshes should be stripped from cooked builds for the platform.
- L171 _public prototype_ `virtual bool UsesDistanceFields() const = 0;` — Gets whether the platform will use distance fields.
- L176 _public prototype_ `virtual bool UsesRayTracing() const = 0;` — Gets whether the platform will use ray tracing.
- L181 _public prototype_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const = 0;` — Gets ray tracing runtime mode (disabled/inline/hit-lighting).
- L189 _public prototype_ `virtual uint32 GetSupportedHardwareMask() const = 0;` — Gets a platform-dependent bitfield describing which hardware generations are supported. Applies to platforms with multiple iterations of the device, which may vary in performance. Each bit represents a supported device version. Return 0 if information is not provided by the platform.
- L194 _public prototype_ `virtual EOfflineBVHMode GetStaticMeshOfflineBVHMode() const = 0;` — Gets static mesh offline BVH mode
- L199 _public prototype_ `virtual bool GetStaticMeshOfflineBVHCompression() const = 0;` — Gets whether the platform will use compression for static mesh offline BVH.
- L204 _public prototype_ `virtual EOfflineBVHMode GetSkeletalMeshOfflineBVHMode() const = 0;` — Gets skeletal mesh offline BVH mode
- L209 _public prototype_ `virtual bool ForcesSimpleSkyDiffuse() const = 0;` — Gets whether the platform will use SH2 instead of SH3 for sky irradiance.
- L214 _public prototype_ `virtual bool VelocityEncodeDepth() const = 0;` — Gets whether the platform will encode depth velocity.
- L221 _public prototype_ `virtual float GetDownSampleMeshDistanceFieldDivider() const = 0;` — Gets down sample mesh distance field divider. @return 1 if platform does not need to downsample mesh distance fields
- L227 _public prototype_ `virtual int32 GetHeightFogModeForOpaque() const = 0;` — Gets an integer representing the height fog mode for opaque materials on a platform. @return 0 if no override (i.e. use r.VertexFoggingForOpaque from project settings); 1 if pixel fog; 2 if vertex fog.
- L232 _public prototype_ `virtual bool UsesMobileDBuffer() const = 0;` — Gets whether the platform should use DBuffer for decals when using the mobile renderer.
- L237 _public prototype_ `virtual bool UsesASTCHDR() const = 0;` — Gets whether the platform uses ASTC HDR
- L242 _public prototype_ `virtual FName GetFallbackASTCHDR() const = 0;` — Gets the fallback format when ASTC HDR is not supported
- L249 _public prototype_ `virtual void GetAllPossibleShaderFormats(TArray<FName>& OutFormats) const = 0;` — Gets the shader formats this platform can use. @param OutFormats Will contain the shader formats.
- L256 _public prototype_ `virtual void GetAllTargetedShaderFormats(TArray<FName>& OutFormats) const = 0;` — Gets the shader formats that have been selected for this target platform @param OutFormats Will contain the shader formats.
- L263 _public prototype_ `virtual void GetRayTracingShaderFormats(TArray<FName>& OutFormats) const = 0;` — Gets the shader formats that support ray tracing for this target platform. @param OutFormats Will contain the shader formats.
- L271 _public prototype_ `virtual bool SupportsFeature(ETargetPlatformFeatures Feature) const = 0;` — Checks whether the target platform supports the specified feature. @param Feature The feature to check. @return true if the feature is supported, false otherwise.
- L278 _public prototype_ `virtual void GetPossibleArchitectures(TArray<FString>& OutArchitectures) const = 0;` — Get the possible architectures for the target platform @param OutArchitectures will contain supported architectures.
- L285 _public prototype_ `virtual FString GetHostArchitecture() const = 0;` — Get the host architectures for the target platform, if any @return host architecture, or an empty string if it is not relevant
- L293 _public prototype_ `virtual void GetShaderFormatModuleHints(TArray<FName>& OutModuleNames) const = 0;` — Gets a list of modules that may contain the GetAllTargetedShaderFormats. This is optional - if any required shader format isn't found in this list, then it will use the old path of loading all shader format modules to gather all available shader formats
- L300 _public prototype_ `virtual void GetReflectionCaptureFormats(TArray<FName>& OutFormats) const = 0;` — Gets the reflection capture formats this platform needs. @param OutFormats Will contain the collection of formats.
- L312 _public prototype_ `virtual const class UTextureLODSettings& GetTextureLODSettings() const = 0;` — Gets the texture LOD settings used by this platform. @return A texture LOD settings structure. This should generally be equal to : const UTextureLODSettings* LODSettings = UDeviceProfileManager::Get().FindProfile(TargetPlatform->CookingDeviceProfileName())->GetTextureLODSettings(); It is cached by RegisterTextureLODSettings()
- L317 _public prototype_ `virtual void RegisterTextureLODSettings(const class UTextureLODSettings* InTextureLODSettings) = 0;` — Register Basic LOD Settings for this platform
- L324 _public prototype_ `virtual const class FStaticMeshLODSettings& GetStaticMeshLODSettings() const = 0;` — Gets the static mesh LOD settings used by this platform. @return A static mesh LOD settings structure.
- L335 _public prototype_ `virtual bool IsRunningPlatform() const = 0;` — Checks whether this platform is the platform that's currently running. For example, when running on Windows, the Windows ITargetPlatform will return true and all other platforms will return false. @return true if this platform is running, false otherwise.
- L338 _public prototype_ `virtual ~ITargetPlatformSettings() = default;` — Virtual destructor.

### `Source/Developer/TargetPlatform/Public/Interfaces/ITargetPlatformSettingsModule.h` (Public)


#### class `ITargetPlatformSettingsModule`  
`class ITargetPlatformSettingsModule : public IModuleInterface`  
_L12-54_
- inherits: `IModuleInterface`
- desc: Interface for target platform modules.
- L19 _public function_ `virtual ~ITargetPlatformSettingsModule()` — Virtual destructor.
- L34 _public function_ `TArray<ITargetPlatformSettings*> GetTargetPlatformSettings()` — Gets the module's target platforms. This should be overridden by each platform, but currently, we are re-using the single internal GetTargetPlatform method the old TPModules will implement @return The target platform.
- L49 _protected prototype_ `virtual void GetTargetPlatformSettings(TArray<ITargetPlatformSettings*>& TargetPlatforms) = 0;` — This is where each platform module will fill out an array
- L53 _private member_ `TArray<ITargetPlatformSettings*> AllTargetPlatforms;` — Holds the target platforms.

### `Source/Developer/TargetPlatform/Public/Interfaces/TargetDeviceId.h` (Public)


#### class `FTargetDeviceId`  
`class FTargetDeviceId`  
_L10-140_
- desc: Implements a target devices identifier.
- L15 _public function_ `FTargetDeviceId()` — Default constructor.
- L23 _public function_ `FTargetDeviceId( const FString& InPlatformName, const FString& InDeviceName ) : PlatformName(InPlatformName) , DeviceName(InDeviceName)` — Creates and initializes a new target device identifier. @param InPlatformName The name of the device's target platform. @param InDeviceName The unique device name, i.e. IP address or computer name.
- L36 _public function_ `bool operator==( const FTargetDeviceId& Other ) const` — Compares this device identifier with the given device identifier for equality. @param Other The device identifier to compare with. @return true if the identifiers are equal, false otherwise.
- L47 _public function_ `bool operator!=( const FTargetDeviceId& Other ) const` — Compares this device identifier with the given device identifier for inequality. @param Other The device identifier to compare with. @return true if the identifiers are not equal, false otherwise.
- L71 _public function_ `const FString& GetDeviceName() const` — Gets the device identifier. @return Device identifier.
- L81 _public function_ `const FString& GetPlatformName() const` — Gets the platform name. @return Platform name.
- L91 _public function_ `bool IsValid() const` — Checks whether this target device identifier is valid. @return true if the identifier is valid, false otherwise.
- L101 _public function_ `FString ToString() const` — Gets the string representation for this device identifier. @return String representation.
- L128 _public function_ `static bool Parse( const FString& IdString, FTargetDeviceId& OutId )` — Converts a string to a target device identifier. @param IdString The string to convert. @param OutId Will contain the parsed device identifier. @return true if the string was converted successfully, false otherwise.
- L136 _private member_ `FString PlatformName;` — Holds the name of the device's target platform.
- L139 _private member_ `FString DeviceName;` — Holds the name of the target device.

#### Free symbols / members of external scopes

- L59 _function_ `friend FArchive& operator<<( FArchive& Ar, FTargetDeviceId& Uri )` — Serializes the given device identifier from or into the specified archive. @param Ar The archive to serialize from or into. @param Uri The device identifier to serialize. @return The archive.
- L114 _function_ `friend uint32 GetTypeHash( const FTargetDeviceId& Uri )` — Gets the hash for specified target device identifier. @param Uri The device identifier to get the hash for. @return Hash value.

### `Source/Developer/TargetPlatform/Public/TargetPlatform.h` (Public)
_(no declarations extracted)_
