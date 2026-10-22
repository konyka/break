# Developer / AndroidTargetPlatformSettings

- module root: `Source/Developer/Android/AndroidTargetPlatformSettings`
- headers: 2; symbols: 74
- symbol kinds: class=7, enum=1, enumerator=4, function=13, member=2, namespace=1, prototype=18, variable=28
- PrivateDependencyModuleNames: Core, CoreUObject, DesktopPlatform, Engine, TargetPlatform

### `Source/Developer/Android/AndroidTargetPlatformSettings/Public/AndroidTargetPlatformSettings.h` (Public)


#### enum `EAndroidTextureFormatCategory`  
`enum class EAndroidTextureFormatCategory`  
_L17-24_
- desc: Listed in order of priority...if device supports multiple formats, first format in list will be chosen
- L19 _public enumerator_ `DXT`
- L20 _public enumerator_ `ETC2`
- L21 _public enumerator_ `ASTC`
- L23 _public enumerator_ `Count`

#### class `FAndroidTargetPlatformSettings`  
`class FAndroidTargetPlatformSettings : public TTargetPlatformSettingsBase<FAndroidPlatformProperties>`  
_L96-156_
- inherits: `TTargetPlatformSettingsBase<FAndroidPlatformProperties>`
- L99 _public prototype_ `FAndroidTargetPlatformSettings(const TCHAR* CookFlavor = nullptr, const TCHAR* OverrideIniPlatformName = nullptr);`
- L104 _public prototype_ `virtual ~FAndroidTargetPlatformSettings()= default;` — Destructor
- L106 _public function_ `virtual bool SupportsTextureFormatCategory(EAndroidTextureFormatCategory Category) const`
- L111 _public prototype_ `virtual bool SupportsFeature(ETargetPlatformFeatures Feature) const override;`
- L112 _public prototype_ `virtual void GetAllPossibleShaderFormats(TArray<FName>& OutFormats) const override;`
- L113 _public prototype_ `virtual void GetAllTargetedShaderFormats(TArray<FName>& OutFormats) const override;`
- L115 _public function_ `virtual bool UsesRayTracing() const override`
- L123 _public function_ `virtual ERayTracingRuntimeMode GetRayTracingMode() const override`
- L129 _public prototype_ `virtual void GetReflectionCaptureFormats(TArray<FName>& OutFormats) const override;`
- L130 _public prototype_ `virtual const UTextureLODSettings& GetTextureLODSettings() const override;`
- L131 _public function_ `virtual void RegisterTextureLODSettings(const UTextureLODSettings* InTextureLODSettings) override`
- L135 _public prototype_ `virtual const class FStaticMeshLODSettings& GetStaticMeshLODSettings() const override;`
- L138 _public prototype_ `bool SupportsES31() const;` — query for rendering mode support
- L139 _public prototype_ `bool SupportsVulkan() const;`
- L140 _public prototype_ `bool SupportsVulkanSM5() const;`
- L142 _public prototype_ `virtual bool UsesDistanceFields() const override;`
- L147 _protected member_ `const UTextureLODSettings* TextureLODSettings;` — Holds a cache of the target LOD settings.
- L150 _protected member_ `FStaticMeshLODSettings StaticMeshLODSettings;` — Holds the static mesh LOD settings.
- L153 _private prototype_ `bool GetIsDistanceField() const;`
- L154 _private prototype_ `int32 GetMobileShadingPath() const;`
- L155 _private prototype_ `bool GetIsMobileForwardEnableClusteredReflections() const;`

#### class `FAndroid_DXTTargetPlatformSettings`  
`class FAndroid_DXTTargetPlatformSettings : public FAndroidTargetPlatformSettings`  
_L158-169_
- inherits: `FAndroidTargetPlatformSettings`
- L161 _public function_ `FAndroid_DXTTargetPlatformSettings() : FAndroidTargetPlatformSettings(TEXT("DXT"))`
- L165 _public function_ `virtual bool SupportsTextureFormatCategory(EAndroidTextureFormatCategory Category) const override`

#### class `FAndroid_ASTCTargetPlatformSettings`  
`class FAndroid_ASTCTargetPlatformSettings : public FAndroidTargetPlatformSettings`  
_L171-182_
- inherits: `FAndroidTargetPlatformSettings`
- L174 _public function_ `FAndroid_ASTCTargetPlatformSettings(const TCHAR* Name=TEXT("ASTC")) : FAndroidTargetPlatformSettings(Name)`
- L178 _public function_ `virtual bool SupportsTextureFormatCategory(EAndroidTextureFormatCategory Category) const override`

#### class `FAndroid_ETC2TargetPlatformSettings`  
`class FAndroid_ETC2TargetPlatformSettings : public FAndroidTargetPlatformSettings`  
_L185-197_
- inherits: `FAndroidTargetPlatformSettings`
- L189 _public function_ `FAndroid_ETC2TargetPlatformSettings() : FAndroidTargetPlatformSettings(TEXT("ETC2"))`
- L193 _public function_ `virtual bool SupportsTextureFormatCategory(EAndroidTextureFormatCategory Category) const override`

#### class `FAndroid_MultiTargetPlatformSettings`  
`class FAndroid_MultiTargetPlatformSettings : public FAndroidTargetPlatformSettings`  
_L199-217_
- inherits: `FAndroidTargetPlatformSettings`
- L203 _public function_ `FAndroid_MultiTargetPlatformSettings() : FAndroidTargetPlatformSettings(TEXT("Multi"))`
- L207 _public function_ `bool SupportsFeature(ETargetPlatformFeatures Feature) const override`

#### class `FAndroid_OpenXRTargetPlatformSettings`  
`class FAndroid_OpenXRTargetPlatformSettings : public FAndroid_ASTCTargetPlatformSettings`  
_L219-226_
- inherits: `FAndroid_ASTCTargetPlatformSettings`
- L223 _public function_ `FAndroid_OpenXRTargetPlatformSettings() : FAndroid_ASTCTargetPlatformSettings(TEXT("OpenXR"))`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace AndroidTexFormat`
- L29 _variable_ `const static FName NameDXT1(TEXT("DXT1` (scope `AndroidTexFormat`) — Compressed Texture Formats
- L30 _variable_ `const static FName NameDXT5(TEXT("DXT5` (scope `AndroidTexFormat`)
- L31 _variable_ `const static FName NameDXT5n(TEXT("DXT5` (scope `AndroidTexFormat`)
- L32 _variable_ `const static FName NameAutoDXT(TEXT("Auto` (scope `AndroidTexFormat`)
- L33 _variable_ `const static FName NameBC4(TEXT("BC4"` (scope `AndroidTexFormat`)
- L34 _variable_ `const static FName NameBC5(TEXT("BC5"` (scope `AndroidTexFormat`)
- L35 _variable_ `const static FName NameBC6H(TEXT("BC6H` (scope `AndroidTexFormat`)
- L36 _variable_ `const static FName NameBC7(TEXT("BC7"` (scope `AndroidTexFormat`)
- L38 _variable_ `const static FName NameETC2_RGB(TEXT("ETC2` (scope `AndroidTexFormat`)
- L39 _variable_ `const static FName NameETC2_RGBA(TEXT("ETC2` (scope `AndroidTexFormat`)
- L40 _variable_ `const static FName NameETC2_R11(TEXT("ETC2` (scope `AndroidTexFormat`)
- L41 _variable_ `const static FName NameETC2_RG11(TEXT("ETC2` (scope `AndroidTexFormat`)
- L42 _variable_ `const static FName NameAutoETC2(TEXT("Auto` (scope `AndroidTexFormat`)
- L44 _variable_ `const static FName NameAutoASTC(TEXT("ASTC` (scope `AndroidTexFormat`)
- L45 _variable_ `const static FName NameASTC_NormalRG(TEXT("ASTC` (scope `AndroidTexFormat`)
- L47 _variable_ `const static FName NameASTC_NormalLA(TEXT("ASTC` (scope `AndroidTexFormat`) — L+A mode suppoprted by ARM ASTC encoder
- L50 _variable_ `const static FName NameBGRA8(TEXT("BGRA` (scope `AndroidTexFormat`) — Uncompressed Texture Formats
- L51 _variable_ `const static FName NameG8(TEXT("G8")` (scope `AndroidTexFormat`)
- L52 _variable_ `const static FName NameRGBA16F(TEXT("RGBA` (scope `AndroidTexFormat`)
- L53 _variable_ `const static FName NameR16F(TEXT("R16F` (scope `AndroidTexFormat`)
- L54 _variable_ `const static FName NameG16(TEXT("G16"` (scope `AndroidTexFormat`)
- L57 _variable_ `const static FName NameA1RGB555(TEXT("A1RG` (scope `AndroidTexFormat`) — A1RGB555 is mapped to RGB555A1, because OpenGL GL_RGB5_A1 only supports alpha on the lowest bit
- L58 _variable_ `const static FName NameRGB555A1(TEXT("RGB5` (scope `AndroidTexFormat`)
- L60 _variable_ `const static FName GenericRemap[][2] = { { NameA1RGB555, NameRGB555A1 }, { NameG16, NameR16F },` (scope `AndroidTexFormat`)
- L66 _variable_ `static const FName NameASTC_RGB_HDR(TEXT("ASTC` (scope `AndroidTexFormat`)
- L67 _variable_ `static const FName NameASTC_RGB_LDR(TEXT("ASTC` (scope `AndroidTexFormat`)
- L69 _variable_ `const static FName ASTCRemap[][2] = {` (scope `AndroidTexFormat`)
- L82 _variable_ `const static FName ETCRemap[][2] = {` (scope `AndroidTexFormat`)

### `Source/Developer/Android/AndroidTargetPlatformSettings/Public/IAndroidTargetPlatformSettingsModule.h` (Public)


#### class `IAndroidTargetPlatformSettingsModule`  
`class IAndroidTargetPlatformSettingsModule : public ITargetPlatformSettingsModule`  
_L13-19_
- inherits: `ITargetPlatformSettingsModule`
- L16 _public prototype_ `virtual void GetSinglePlatformSettings(TMap<EAndroidTextureFormatCategory, ITargetPlatformSettings*>& OutMap) = 0;`
- L17 _public prototype_ `virtual ITargetPlatformSettings* GetMultiPlatformSettings() = 0;`
- L18 _public prototype_ `virtual ITargetPlatformSettings* GetXRPlatformSettings() = 0;`
