# Developer / LinuxTargetPlatformSettings

- module root: `Source/Developer/Linux/LinuxTargetPlatformSettings`
- headers: 3; symbols: 80
- symbol kinds: class=7, function=17, macro=2, member=18, namespace=1, prototype=3, typedef=1, variable=31
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, Engine, Projects, TargetPlatform
- PrivateIncludePathModuleNames: LinuxArm64TargetPlatformControls, Settings, TextureCompressor
- PublicIncludePathModuleNames: Engine

### `Source/Developer/Linux/LinuxTargetPlatformSettings/Classes/LinuxTargetSettings.h` (Public)


#### class `ULinuxTargetSettings`  
`class ULinuxTargetSettings : public UObject`  
_L20-105_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the Linux target platform.
- L27 _public prototype_ `virtual void PostInitProperties() override;`
- L31 _public member_ `FString SpatializationPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled spatialization plugins to use.
- L35 _public member_ `FString SourceDataOverridePlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled source data override plugins to use.
- L39 _public member_ `FString ReverbPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled reverb plugins to use.
- L43 _public member_ `FString OcclusionPlugin;` — `UPROPERTY(config, EditAnywhere, Category = "Audio")` — Which of the currently enabled occlusion plugins to use.
- L47 _public member_ `int32 SoundCueCookQualityIndex = INDEX_NONE;` — `UPROPERTY(config, EditAnywhere, Category = "Audio|CookOverrides", meta = (DisplayName = "Sound Cue Cook Quality"))` — Quality Level to COOK SoundCues at (if set, all other levels will be stripped by the cooker).
- L54 _public member_ `TArray<FString> TargetedRHIs;` — `UPROPERTY(EditAnywhere, config, Category=Rendering)` — The collection of RHI's we want to support on this platform. This is not always the full list of RHI we can support.
- L58 _public member_ `bool bGenerateNaniteFallbackMeshes = true;` — `UPROPERTY(config, EditAnywhere, Category = "Renderer", meta = (DisplayName = "Generate Nanite Fallback Meshes", ConfigRestartRequired = true))` — Whether to include Nanite Fallback Meshes in cooked builds for Linux. Can be overriden for specific assets in Static Mesh Editor.
- L62 _public member_ `bool bEnableRayTracing_DEPRECATED;` — `UPROPERTY(config, meta = (DeprecatedProperty))` — Deprecated use RayTracingMode instead.
- L66 _public member_ `ETargetSettingsRayTracingRuntimeMode RayTracingMode;` — `UPROPERTY(config, EditAnywhere, Category = "Renderer", meta = (DisplayName = "Hardware Ray Tracing Mode"))` — Controls the level of ray tracing support for Linux. r.RayTracing cvar also needs to be enabled.
- L75 _public member_ `bool bMultiTargetFormat_DXT;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "LinuxArm64 Multi Texture Formats", meta = (DisplayName = "Include DXT textures"))` — Include DXT textures when packaging with the Linux ARM64 (Multi) cook target.
- L79 _public member_ `bool bMultiTargetFormat_ASTC;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "LinuxArm64 Multi Texture Formats", meta = (DisplayName = "Include ASTC textures"))` — Include ASTC textures when packaging with the Linux ARM64 (Multi) cook target.
- L83 _public member_ `bool bMultiTargetFormat_ETC2;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "LinuxArm64 Multi Texture Formats", meta = (DisplayName = "Include ETC2 textures"))` — Include ETC2 textures when packaging with the Linux ARM64 (Multi) cook target.
- L87 _public member_ `float TextureFormatPriority_ETC2;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "LinuxArm64 Multi Texture Formats", meta = (DisplayName = "ETC2 texture format priority"))` — Priority for the ETC2 texture format when packaging using Linux ARM64 (Multi). The highest priority format supported by the device will be used. Default value is 0.2.
- L91 _public member_ `float TextureFormatPriority_DXT;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "LinuxArm64 Multi Texture Formats", meta = (DisplayName = "DXT texture format priority"))` — Priority for the DXT texture format when packaging using Linux ARM64 (Multi). The highest priority format supported by the device will be used. Default value is 0.6.
- L95 _public member_ `float TextureFormatPriority_ASTC;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "LinuxArm64 Multi Texture Formats", meta = (DisplayName = "ASTC texture format priority"))` — Priority for the ASTC texture format when packaging using Linux ARM64 (Multi). The highest priority format supported by the device will be used. Default value is 0.9.
- L98 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L101 _public function_ `void virtual OverrideConfigSection(FString& InOutSectionName) override`

### `Source/Developer/Linux/LinuxTargetPlatformSettings/Public/ILinuxTargetPlatformSettingsModule.h` (Public)


#### class `ILinuxTargetPlatformSettingsModule`  
`class ILinuxTargetPlatformSettingsModule : public ITargetPlatformSettingsModule`  
_L12-16_
- inherits: `ITargetPlatformSettingsModule`
- L15 _public prototype_ `virtual void GetPlatformSettingsMaps(TMap<FString, ITargetPlatformSettings*>& OutMap) = 0;`

### `Source/Developer/Linux/LinuxTargetPlatformSettings/Public/LinuxTargetPlatformSettings.h` (Public)


#### class `TLinuxTargetPlatformSettings`  
`template<typename TProperties> class TLinuxTargetPlatformSettings : public TTargetPlatformSettingsBase<TProperties>`  
_L98-258_
- inherits: `TTargetPlatformSettingsBase<TProperties>`
- desc: Template for Linux target platforms settings
- L103 _public typedef_ `typedef TTargetPlatformSettingsBase<TProperties> TSuper;`
- L108 _public function_ `TLinuxTargetPlatformSettings(const TCHAR* CookFlavor = nullptr, const TCHAR* OverrideIniPlatformName = nullptr) : TSuper(CookFlavor, OverrideIniPlatformName)` — Default constructor.
- L132 _public function_ `virtual bool SupportsFeature(ETargetPlatformFeatures Feature) const override`
- L147 _public function_ `virtual void GetAllPossibleShaderFormats( TArray<FName>& OutFormats ) const override`
- L161 _public function_ `virtual void GetAllTargetedShaderFormats( TArray<FName>& OutFormats ) const override`
- L186 _public function_ `virtual bool IsRunningPlatform() const override`
- L193 _public function_ `virtual void GetReflectionCaptureFormats(TArray<FName>& OutFormats) const override`
- L203 _public function_ `virtual const class FStaticMeshLODSettings& GetStaticMeshLODSettings( ) const override`
- L208 _public function_ `virtual const UTextureLODSettings& GetTextureLODSettings() const override`
- L213 _public function_ `virtual void RegisterTextureLODSettings(const UTextureLODSettings* InTextureLODSettings) override`
- L220 _public function_ `virtual bool ShouldStripNaniteFallbackMeshes() const override`
- L228 _public function_ `virtual bool UsesRayTracing() const override`
- L233 _public function_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const override`
- L250 _protected member_ `const UTextureLODSettings* TextureLODSettings;` — Holds the texture LOD settings.
- L253 _protected member_ `FStaticMeshLODSettings StaticMeshLODSettings;` — Holds static mesh LOD settings.
- L256 _protected member_ `bool bRequiresEncodedHDRReflectionCaptures;` — True if the project requires encoded HDR reflection captures

#### class `TLinux_DXTTargetPlatformSettings`  
`template<typename TProperties> class TLinux_DXTTargetPlatformSettings : public TLinuxTargetPlatformSettings<TProperties>`  
_L261-267_
- inherits: `TLinuxTargetPlatformSettings<TProperties>`
- L264 _public function_ `TLinux_DXTTargetPlatformSettings() : TLinuxTargetPlatformSettings<TProperties>(TEXT("DXT"))`

#### class `TLinux_ASTCTargetPlatformSettings`  
`template<typename TProperties> class TLinux_ASTCTargetPlatformSettings : public TLinuxTargetPlatformSettings<TProperties>`  
_L270-276_
- inherits: `TLinuxTargetPlatformSettings<TProperties>`
- L273 _public function_ `TLinux_ASTCTargetPlatformSettings() : TLinuxTargetPlatformSettings<TProperties>(TEXT("ASTC"))`

#### class `TLinux_ETC2TargetPlatformSettings`  
`template<typename TProperties> class TLinux_ETC2TargetPlatformSettings : public TLinuxTargetPlatformSettings<TProperties>`  
_L279-286_
- inherits: `TLinuxTargetPlatformSettings<TProperties>`
- L283 _public function_ `TLinux_ETC2TargetPlatformSettings() : TLinuxTargetPlatformSettings<TProperties>(TEXT("ETC2"))`

#### class `TLinux_MultiTargetPlatformSettings`  
`template<typename TProperties> class TLinux_MultiTargetPlatformSettings : public TLinuxTargetPlatformSettings<TProperties>`  
_L289-296_
- inherits: `TLinuxTargetPlatformSettings<TProperties>`
- L293 _public function_ `TLinux_MultiTargetPlatformSettings() : TLinuxTargetPlatformSettings<TProperties>(TEXT("Multi"))`

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "TLinuxTargetPlatformSettings"`
- L17 _macro_ `#define LINUX_SECTION_TEXT TEXT("/Script/LinuxTargetPlatform.LinuxTargetSettings")`
- L21 _namespace_ `namespace LinuxTexFormat`
- L24 _variable_ `const static FName NameDXT1(TEXT("DXT1` (scope `LinuxTexFormat`) — Compressed Texture Formats
- L25 _variable_ `const static FName NameDXT5(TEXT("DXT5` (scope `LinuxTexFormat`)
- L26 _variable_ `const static FName NameDXT5n(TEXT("DXT5` (scope `LinuxTexFormat`)
- L27 _variable_ `const static FName NameAutoDXT(TEXT("Auto` (scope `LinuxTexFormat`)
- L28 _variable_ `const static FName NameBC4(TEXT("BC4"` (scope `LinuxTexFormat`)
- L29 _variable_ `const static FName NameBC5(TEXT("BC5"` (scope `LinuxTexFormat`)
- L30 _variable_ `const static FName NameBC6H(TEXT("BC6H` (scope `LinuxTexFormat`)
- L31 _variable_ `const static FName NameBC7(TEXT("BC7"` (scope `LinuxTexFormat`)
- L33 _variable_ `const static FName NameETC2_RGB(TEXT("ETC2` (scope `LinuxTexFormat`)
- L34 _variable_ `const static FName NameETC2_RGBA(TEXT("ETC2` (scope `LinuxTexFormat`)
- L35 _variable_ `const static FName NameETC2_R11(TEXT("ETC2` (scope `LinuxTexFormat`)
- L36 _variable_ `const static FName NameETC2_RG11(TEXT("ETC2` (scope `LinuxTexFormat`)
- L37 _variable_ `const static FName NameAutoETC2(TEXT("Auto` (scope `LinuxTexFormat`)
- L39 _variable_ `const static FName NameAutoASTC(TEXT("ASTC` (scope `LinuxTexFormat`)
- L40 _variable_ `const static FName NameASTC_NormalRG(TEXT("ASTC` (scope `LinuxTexFormat`)
- L42 _variable_ `const static FName NameASTC_NormalLA(TEXT("ASTC` (scope `LinuxTexFormat`) — L+A mode supported by ARM ASTC encoder. Not included in ASTCRemap as it is already an ASTC format and requires no remapping.
- L45 _variable_ `const static FName NameBGRA8(TEXT("BGRA` (scope `LinuxTexFormat`) — Uncompressed Texture Formats
- L46 _variable_ `const static FName NameG8(TEXT("G8")` (scope `LinuxTexFormat`)
- L47 _variable_ `const static FName NameRGBA16F(TEXT("RGBA` (scope `LinuxTexFormat`)
- L48 _variable_ `const static FName NameR16F(TEXT("R16F` (scope `LinuxTexFormat`)
- L49 _variable_ `const static FName NameG16(TEXT("G16"` (scope `LinuxTexFormat`)
- L52 _variable_ `const static FName NameA1RGB555(TEXT("A1RG` (scope `LinuxTexFormat`) — A1RGB555 is mapped to RGB555A1, because OpenGL GL_RGB5_A1 only supports alpha on the lowest bit
- L53 _variable_ `const static FName NameRGB555A1(TEXT("RGB5` (scope `LinuxTexFormat`)
- L55 _variable_ `const static FName GenericRemap[][2] = { { NameA1RGB555, NameRGB555A1 }, { NameG16, NameR16F },` (scope `LinuxTexFormat`)
- L61 _variable_ `const static FName NameASTC_RGB_HDR(TEXT("ASTC` (scope `LinuxTexFormat`)
- L62 _variable_ `const static FName NameASTC_RGB(TEXT("ASTC` (scope `LinuxTexFormat`)
- L63 _variable_ `const static FName NameASTC_RGBA(TEXT("ASTC` (scope `LinuxTexFormat`)
- L64 _variable_ `const static FName NameASTC_RGBA_HQ(TEXT("ASTC` (scope `LinuxTexFormat`)
- L65 _variable_ `const static FName NameASTC_NormalAG(TEXT("ASTC` (scope `LinuxTexFormat`)
- L67 _variable_ `const static FName ASTCRemap[][2] = {` (scope `LinuxTexFormat`)
- L80 _variable_ `const static FName ETCRemap[][2] = {` (scope `LinuxTexFormat`)
