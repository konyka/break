# Developer / MacTargetPlatformSettings

- module root: `Source/Developer/Mac/MacTargetPlatformSettings`
- headers: 4; symbols: 80
- symbol kinds: class=4, enum=2, enumerator=9, function=14, macro=1, member=45, prototype=3, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, Engine, TargetPlatform
- PrivateIncludePathModuleNames: Settings, TextureCompressor
- PublicDependencyModuleNames: CookedEditor, RHI

### `Source/Developer/Mac/MacTargetPlatformSettings/Classes/MacTargetSettings.h` (Public)


#### enum `EMacMetalShaderStandard`  
`enum class EMacMetalShaderStandard : uint8`  
_L14-27_
- reflection: `UENUM()`
- L17 _public enumerator_ `MacMetalSLStandard_Minimum = 0 UMETA(DisplayName="Minimum, Currently v2.2 (10.15+)")` — Metal Shader 2.2 is the minimum
- L19 _public enumerator_ `MacMetalSLStandard_2_2 = 5 UMETA(DisplayName="Metal v2.2 (10.15+)")` — Metal Shaders Compatible With macOS 10.15 or later (std=osx-metal2.2)
- L21 _public enumerator_ `MacMetalSLStandard_2_3 = 6 UMETA(DisplayName="Metal v2.3 (11.0+)")` — Metal Shaders Compatible With macOS 11.0 or later (std=osx-metal2.3)
- L23 _public enumerator_ `MacMetalSLStandard_2_4 = 7 UMETA(DisplayName="Metal v2.4 (12.0+)")` — Metal Shaders Compatible With macOS 12.0 or later (std=osx-metal2.4)
- L25 _public enumerator_ `MacMetalSLStandard_3_0 = 8 UMETA(DisplayName="Metal v3.0 (13.0+)")` — Metal Shaders Compatible With macOS 13.0 or later (std=metal3.0)

#### enum `EMacTargetArchitecture`  
`enum class EMacTargetArchitecture : uint8`  
_L30-43_
- reflection: `UENUM()`
- L33 _public enumerator_ `MacTargetArchitectureIntel = 0 UMETA(DisplayName="Intel x64")` — Create packages that can run natively on Intel Macs and under translation on Apple Silicon Macs
- L36 _public enumerator_ `MacTargetArchitectureUniversal = 1 UMETA(DisplayName="Universal (Intel & Apple Silicon)")` — Create Universal packages that run natively on all Macs
- L39 _public enumerator_ `MacTargetArchitectureAppleSilicon = 2 UMETA(DisplayName="Apple Silicon")` — Create packages that can run natively on Apple Silicon Macs, and will not run on Intel Macs
- L42 _public enumerator_ `MacTargetArchitectureHost = 3 UMETA(DisplayName="Host (Matches current machine)")` — Create  packages that match the architecture of the Mac the package is made on

#### class `UMacTargetSettings`  
`class UMacTargetSettings : public UObject`  
_L50-180_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the Mac target platform.
- L62 _public member_ `TArray<FString> TargetedRHIs;` — `UPROPERTY(EditAnywhere, config, Category=Rendering)` — The collection of RHI's we want to support on this platform. This is not always the full list of RHI we can support.
- L70 _public member_ `EMacTargetArchitecture EditorTargetArchitecture;` — `UPROPERTY(EditAnywhere, config, Category=Packaging, meta = (DisplayName = "Supported Architecture(s) for Editor builds"))` — The set of architecture(s) this project supports for Editor builds This defines which CPU architectures to target: x86_64 (Intel), arm64 (Apple Silicon) or Universal (Intel & Apple Silicon). It is recommended to use Universal unless you have editor plugins or other libraries that do not support Apple Silicon
- L78 _public member_ `EMacTargetArchitecture TargetArchitecture;` — `UPROPERTY(EditAnywhere, config, Category=Packaging, meta = (DisplayName = "Supported Architecture(s) for non-Editor builds"))` — The target Mac platform CPU architecture. This defines which CPU architectures to target: x86_64 (Intel), arm64 (Apple Silicon) or Universal (Intel & Apple Silicon). It is recommended to use Universal unless you have runtime plugins or other libraries that do not support Apple Silicon
- L86 _public member_ `EMacTargetArchitecture EditorDefaultArchitecture;` — `UPROPERTY(EditAnywhere, config, Category=Packaging, meta = (DisplayName = "Architecture(s) when building Editor"))` — The architecture to compile the Editor target This defines which CPU architectures to target: x86_64 (Intel), arm64 (Apple Silicon) or Universal (Intel & Apple Silicon), or Host to match the machine doing the building Can override with -Architecture= on the UBT commandline, or -EditorArchitecture=  on the BuildCookRun commandline
- L94 _public member_ `EMacTargetArchitecture DefaultArchitecture;` — `UPROPERTY(EditAnywhere, config, Category=Packaging, meta = (DisplayName = "Architecture(s) when building non-Editor"))` — The architectures to compile non-Editor (games, programs, etc) targets for builds outside of Xcode This defines which CPU architectures to target: x86_64 (Intel), arm64 (Apple Silicon) or Universal (Intel & Apple Silicon), or Host to match the machine doing the building Can override with -Architecture= on the UBT commandline, or -GameArchitecture= or -ProgramArchitecture= on the BuildCookRun commandline
- L100 _public member_ `bool bBuildAllSupportedOnBuildMachine;` — `UPROPERTY(EditAnywhere, config, Category=Packaging, meta = (DisplayName = "Build all supported Architectures on Build Machines"))` — If true, builds running on BuildMachines (when the 'IsBuildMachine' environment variable is set to 1) will compile all Supported architectures
- L106 _public member_ `int32 MetalLanguageVersion;` — `UPROPERTY(EditAnywhere, config, Category=Rendering, meta = (DisplayName = "Metal Shader Standard To Target", ConfigRestartRequired = true))` — The Metal shader language version which will be used when compiling the shaders.
- L115 _public member_ `bool UseFastIntrinsics;` — `UPROPERTY(EditAnywhere, config, Category=Rendering, meta = (DisplayName = "Use Fast-Math intrinsics", ConfigRestartRequired = true))` — Whether to use the Metal shading language's "fast" intrinsics. Fast intrinsics assume that no NaN or INF value will be provided as input, so are more efficient. However, they will produce undefined results if NaN/INF is present in the argument/s. By default fast-instrinics are disabled so Metal correctly handles NaN/INF arguments.
- L124 _public member_ `bool EnableMathOptimisations;` — `UPROPERTY(EditAnywhere, config, Category=Rendering, meta = (DisplayName = "Enable Fast-Math optimisations", ConfigRestartRequired = true))` — Whether to use of Metal shader-compiler's -ffast-math optimisations. Fast-Math performs algebraic-equivalent & reassociative optimisations not permitted by the floating point arithmetic standard (IEEE-754). These can improve shader performance at some cost to precision and can lead to NaN/INF propagation as they rely on shader inputs or variables not containing NaN/INF values. By default fast-math is enabled for performance.
- L128 _public member_ `int32 AudioSampleRate;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", Meta = (DisplayName = "Audio Mixer Sample Rate"))` — Sample rate to run the audio mixer with.
- L132 _public member_ `int32 AudioCallbackBufferFrameSize;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "512", ClampMax = "4096", DisplayName = "Callback Buffer Size"))` — The amount of audio to compute each callback block. Lower values decrease latency but may increase CPU cost.
- L136 _public member_ `int32 AudioNumBuffersToEnqueue;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "1", UIMin = "1", DisplayName = "Number of Buffers To Enqueue"))` — The number of buffers to keep enqueued. More buffers increases latency, but can compensate for variable compute availability in audio callbacks on some platforms.
- L140 _public member_ `int32 AudioMaxChannels;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "0", UIMin = "0", DisplayName = "Max Channels"))` — The max number of channels (voices) to limit for this platform. The max channels used will be the minimum of this value and the global audio quality settings. A value of 0 will not apply a platform channel count max.
- L144 _public member_ `int32 AudioNumSourceWorkers;` — `UPROPERTY(config, EditAnywhere, Category = "Audio", meta = (ClampMin = "0", UIMin = "0", DisplayName = "Number of Source Workers"))` — The number of workers to use to compute source audio. Will only use up to the max number of sources. Will evenly divide sources to each source worker.
- L148 _public member_ `FString SpatializationPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled spatialization plugins to use.
- L152 _public member_ `FString SourceDataOverridePlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled source data override plugins to use.
- L156 _public member_ `FString ReverbPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled reverb plugins to use.
- L160 _public member_ `FString OcclusionPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled occlusion plugins to use.
- L164 _public member_ `int32 SoundCueCookQualityIndex = INDEX_NONE;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Audio|CookOverrides", meta = (DisplayName = "Sound Cue Cook Quality"))` — Quality Level to COOK SoundCues at (if set, all other levels will be stripped by the cooker).
- L166 _public function_ `void virtual OverrideConfigSection(FString& InOutSectionName) override`
- L172 _public function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override`

### `Source/Developer/Mac/MacTargetPlatformSettings/Classes/XcodeProjectSettings.h` (Public)


#### class `UXcodeProjectSettings`  
`class UXcodeProjectSettings : public UObject`  
_L17-187_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for Xcode projects
- L30 _public member_ `bool bUseModernXcode = true;` — `UE_DEPRECATED(5.8, "Modern Xcode is now the only option. This property is no longer used.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Modern Xcode is now the only option. This property is no longer used."))` — Enable modernized Xcode, when building from Xcode, use native Xcode for bundle generation and archiving instead of UBT Restart required to apply this setting
- L33 _public function_ `static bool ShouldDisableIOSSettings()` — `UFUNCTION()`
- L47 _public member_ `FString CodeSigningTeam;` — `UPROPERTY(EditAnywhere, config, Category=Xcode, DisplayName = "Apple Dev Account Team ID")` — Team ID used for native Xcode code signing. This must be the 10 letters/numbers ID found in Membership Details tab found in https://developer.apple.com/account
- L53 _public member_ `FString BundleIdentifier;` — `UPROPERTY(EditAnywhere, config, Category=Xcode, DisplayName = "Bundle ID")` — Bundle ID used for nativr Xcode code signing
- L59 _public member_ `FString CodeSigningPrefix;` — `UPROPERTY(EditAnywhere, config, Category=Xcode, DisplayName = "Bundle ID Prefix")` — Bundle ID prefix used for native Xcode code signing. This is only needed if you use the default, pieced-together Bundle ID above. If you specify a full Bundle ID, you can ignore this field.
- L67 _public member_ `FString ApplicationDisplayName;` — `UPROPERTY(EditAnywhere, config, Category=Xcode, DisplayName = "Mac: Published App Name")` — The name of the Mac .app when making an archived build (for uploading to App Store, etc). The Finder shows Mac apps by their .app name, and we don't name the .app  with "pretty" names during development. When packaging for distribution (or using Archive menu in Xcode) this will become the name of the .app, and will be what end users will have on their Mac. If this is not set, the .app will have the name of the .uproject file
- L73 _public member_ `FString AppCategory;` — `UPROPERTY(EditAnywhere, config, Category=Xcode, DisplayName = "App Category")` — The App Category that will be used for Apple App Store submissions
- L79 _public member_ `FFilePath TemplateMacPlist;` — `UPROPERTY(EditAnywhere, config, Category="Plist Files", DisplayName = "Mac: Info.plist Template")` — The template info.plist used for Mac game targets
- L85 _public member_ `FFilePath TemplateIOSPlist;` — `UPROPERTY(EditAnywhere, config, Category="Plist Files", DisplayName = "IOS / TVOS: Info.plist Template")` — The template info.plist used for iOS game targets
- L91 _public member_ `FFilePath PremadeMacEntitlements;` — `UPROPERTY(EditAnywhere, config, Category="Entitlements", DisplayName = "Mac: Entitlements")` — The premade entitlement file used for development Mac builds
- L97 _public member_ `FFilePath ShippingSpecificMacEntitlements;` — `UPROPERTY(EditAnywhere, config, Category="Entitlements", DisplayName = "Mac: Entitlements (Shipping config override)")` — The premade entitlement file used for shipping Mac builds
- L103 _public member_ `FFilePath PremadeIOSEntitlements;` — `UPROPERTY(EditAnywhere, config, Category="Entitlements", DisplayName = "IOS: Entitlements")` — The premade entitlement file used for development IOS builds
- L109 _public member_ `FFilePath ShippingSpecificIOSEntitlements;` — `UPROPERTY(EditAnywhere, config, Category="Entitlements", DisplayName = "IOS: Entitlements (Shipping config override)")` — The premade entitlement file used for shipping IOS builds
- L115 _public member_ `bool bUseAutomaticCodeSigning;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing")` — Enable native Xcode code signing
- L121 _public member_ `bool bMacSignToRunLocally;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", DisplayName="Mac: Sign To Run Locally")` — If true, Mac will sign to run locally. Running on another Mac may bring up a dialog preventing running the app. If this and Use Automatic Code Signing are both false, you will need a certificate installed
- L127 _public member_ `FString MacSigningIdentity;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", meta = (EditCondition="!bUseAutomaticCodeSigning && !bMacSignToRunLocally"), DisplayName = "Mac: Signing Identity")` — The name (prefix or full) of the certificate to use for Mac code signing.
- L133 _public member_ `FString IOSSigningIdentity;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", meta = (EditCondition="!bUseAutomaticCodeSigning", DisplayName = "IOS / TVOS: Signing Identity"))` — The name (prefix or full) of the certificate to use for IOS and TVOS code signing
- L139 _public member_ `FFilePath IOSProvisioningProfile;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", meta = (EditCondition="!bUseAutomaticCodeSigning", DisplayName = "IOS: Provisioning Profile"))` — The path to a .mobileprovision file to use for signing for IOS. Alternatively, if it's a single name or UUID (no .mobileprovision extension), it will use this as the name/UUID of an already installed provision to sign with
- L145 _public member_ `FFilePath TVOSProvisioningProfile;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", meta = (EditCondition="!bUseAutomaticCodeSigning", DisplayName = "TVOS: Provisioning Profile"))` — The path to a .mobileprovision file to use for signing for TVOS. Alternatively, if it's a single name or UUID (no .mobileprovision extension), it will use this as the name/UUID of an already installed provision to sign with
- L151 _public member_ `bool bUseAppStoreConnect;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", meta = (EditCondition="bUseAutomaticCodeSigning"))` — If true, use AppStore Connect authentication for commandline builds. This allows for automatic codesigning functionality without needing to be signed in to Xcode. See the App Store Connect API section of the Keys tab in your Users and Access page in Apple dev center.
- L157 _public member_ `FString AppStoreConnectIssuerID;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", meta = (EditCondition="bUseAutomaticCodeSigning && bUseAppStoreConnect", DisplayName = "App Store Connect: Issuer ID"))` — The Issuer ID for your App Store Connect API
- L163 _public member_ `FString AppStoreConnectKeyID;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", meta = (EditCondition="bUseAutomaticCodeSigning && bUseAppStoreConnect", DisplayName = "App Store Connect: Key ID"))` — The Key ID for your App Store Connect generated API key, a 32 hex-character string, including dashes
- L169 _public member_ `FFilePath AppStoreConnectKeyPath;` — `UPROPERTY(EditAnywhere, config, Category="Code Signing", meta = (EditCondition="bUseAutomaticCodeSigning && bUseAppStoreConnect", DisplayName = "App Store Connect: Key File"))` — The path to the downloaded .p8 file shared with your team
- L175 _public member_ `FFilePath AdditionalPrivacyInfoMac;` — `UPROPERTY(EditAnywhere, config, Category="Privacy Manifests", meta = (DisplayName = "Mac: Additional Privacy Info"))` — The path to the optional PrivacyInfo.xcprivacy file for your project
- L181 _public member_ `FFilePath AdditionalPrivacyInfoIOS;` — `UPROPERTY(EditAnywhere, config, Category="Privacy Manifests", meta = (DisplayName = "IOS/TVOS/VisionOS: Additional Privacy Info"))` — The path to the optional PrivacyInfo.xcprivacy file for your project
- L183 _public function_ `void virtual OverrideConfigSection(FString& InOutSectionName) override`

### `Source/Developer/Mac/MacTargetPlatformSettings/Public/GenericMacTargetPlatformSettings.h` (Public)


#### class `TGenericMacTargetPlatformSettings`  
`template<bool HAS_EDITOR_DATA, bool IS_DEDICATED_SERVER, bool IS_CLIENT_ONLY> class TGenericMacTargetPlatformSettings : public TTargetPlatformSettingsBase<FMacPlatformProperties<HAS_EDITOR_DATA, IS_DEDICATED_SERVER, IS_CLIENT_ONLY> >`  
_L25-185_
- inherits: `TTargetPlatformSettingsBase<FMacPlatformProperties<HAS_EDITOR_DATA,IS_DEDICATED_SERVER,IS_CLIENT_ONLY>>`
- desc: Template for Mac target platforms settings
- L30 _public typedef_ `typedef FMacPlatformProperties<HAS_EDITOR_DATA, IS_DEDICATED_SERVER, IS_CLIENT_ONLY> TProperties;`
- L31 _public typedef_ `typedef TTargetPlatformSettingsBase<TProperties> TSuper;`
- L36 _public function_ `TGenericMacTargetPlatformSettings( )` — Default constructor.
- L48 _public function_ `virtual bool SupportsFeature( ETargetPlatformFeatures Feature ) const override`
- L91 _public function_ `virtual void GetAllPossibleShaderFormats( TArray<FName>& OutFormats ) const override`
- L105 _public function_ `virtual void GetAllTargetedShaderFormats(TArray<FName>& OutFormats) const override`
- L131 _public function_ `virtual const class FStaticMeshLODSettings& GetStaticMeshLODSettings( ) const override`
- L136 _public function_ `virtual const UTextureLODSettings& GetTextureLODSettings() const override`
- L141 _public function_ `virtual void RegisterTextureLODSettings(const UTextureLODSettings* InTextureLODSettings) override`
- L148 _public function_ `virtual bool UsesRayTracing() const override`
- L156 _public function_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const override`
- L169 _public function_ `virtual bool IsRunningPlatform() const override`
- L178 _private member_ `const UTextureLODSettings* TextureLODSettings;` — Holds the texture LOD settings.
- L181 _private member_ `FStaticMeshLODSettings StaticMeshLODSettings;` — Holds the static mesh LOD settings.

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "TGenericMacTargetPlatformSettings"`

### `Source/Developer/Mac/MacTargetPlatformSettings/Public/IMacTargetPlatformSettingsModule.h` (Public)


#### class `IMacTargetPlatformSettingsModule`  
`class IMacTargetPlatformSettingsModule : public ITargetPlatformSettingsModule`  
_L12-18_
- inherits: `ITargetPlatformSettingsModule`
- L15 _public prototype_ `virtual void GetPlatformSettingsMaps(TMap<FString, ITargetPlatformSettings*>& OutMap) = 0;`
- L16 _public prototype_ `virtual ITargetPlatformSettings* GetCookedEditorPlatformSettings() = 0;`
- L17 _public prototype_ `virtual ITargetPlatformSettings* GetCookedCookerPlatformSettings() = 0;`
