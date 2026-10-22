# Runtime / OpenColorIOWrapper

- module root: `Source/Runtime/OpenColorIOWrapper`
- headers: 2; symbols: 72
- symbol kinds: class=5, delegate=1, enum=1, enumerator=2, function=4, member=8, namespace=1, prototype=48, struct=1, variable=1
- PrivateDependencyModuleNames: ImageCore
- PrivateIncludePathModuleNames: Engine
- PublicDependencyModuleNames: Core

### `Source/Runtime/OpenColorIOWrapper/Public/OpenColorIOWrapper.h` (Public)


#### class `FOpenColorIOWrapperConfig`  
`class FOpenColorIOWrapperConfig`  
_L50-135_
- desc: Wrapper around library-native config object.
- L63 _public prototype_ `FOpenColorIOWrapperConfig();` — Constructor.
- L71 _public prototype_ `explicit FOpenColorIOWrapperConfig(FStringView InFilePath, EAddWorkingColorSpaceOption InOption = WCS_None);` — Constructor. @param InFilePath Config absolute file path. @param InOptions Initialization options.
- L73 _public prototype_ `virtual ~FOpenColorIOWrapperConfig() = default;`
- L76 _public prototype_ `bool IsValid() const;` — Valid when the native config has been successfully created and isn't null.
- L79 _public prototype_ `int32 GetNumColorSpaces() const;` — Get the number of color spaces in the configuration.
- L82 _public prototype_ `FString GetColorSpaceName(int32 Index) const;` — Get a color space name at an index.
- L85 _public prototype_ `int32 GetColorSpaceIndex(const TCHAR* InColorSpaceName);` — Get the index of a color space, -1 if none.
- L88 _public prototype_ `FString GetColorSpaceFamilyName(const TCHAR* InColorSpaceName) const;` — Get the family name for a color space.
- L91 _public prototype_ `FString GetColorSpaceDescription(const TCHAR* InColorSpaceName) const;` — Get a color space description.
- L94 _public prototype_ `int32 GetNumDisplays() const;` — Get the number of displays in the configuration.
- L97 _public prototype_ `FString GetDisplayName(int32 Index) const;` — Get a display name at an index.
- L100 _public prototype_ `int32 GetNumViews(const TCHAR* InDisplayName) const;` — Get the number of views for a display.
- L103 _public prototype_ `FString GetViewName(const TCHAR* InDisplayName, int32 Index) const;` — Get a view name for its display and index.
- L106 _public prototype_ `FString GetDisplayViewTransformName(const TCHAR* InDisplayName, const TCHAR* InViewName) const;` — Get a display-view transform name.
- L109 _public prototype_ `FString GetDisplayViewDescription(const TCHAR* InDisplayName, const TCHAR* InViewName) const;` — Get a display-view transform name.
- L112 _public prototype_ `FString GetDisplayViewTransformDescription(const TCHAR* InDisplayName, const TCHAR* InViewName) const;` — Get a display-view transform description.
- L115 _public prototype_ `TMap<FString, FString> GetCurrentContextStringVars() const;` — Returns the current context key-value strings.
- L118 _public prototype_ `FString GetCacheID() const;` — Get the string hash of the config.
- L121 _public prototype_ `FString GetDebugString() const;` — Returns a config debug string.
- L124 _public prototype_ `TMap<FString, FString> GetBuiltInConfigNames(bool bRecommendedOnly, bool bShortenUIName) const;` — Returns all the available built-in config name/UI name pairs.
- L127 _public prototype_ `static FString ResolveConfigPath(const TCHAR* InOriginalPath) noexcept;` — Make a config path forward-compatible by replacing special built-in config names with the current name.
- L131 _protected member_ `TPimplPtr<struct FOpenColorIOConfigPimpl, EPimplPtrMode::DeepCopy> Pimpl;`

#### enum `FOpenColorIOWrapperConfig::EAddWorkingColorSpaceOption`  
`enum EAddWorkingColorSpaceOption`  
_L55-60_
- desc: Config initialization options.
- L57 _public enumerator_ `WCS_None`
- L59 _public enumerator_ `WCS_AsInterchangeSpace` — Add the working color space as ACES 2065-1 so that we can target it with an extra conversion from our config if it defines aces_interchange.

#### struct `FOpenColorIOWrapperSourceColorSettings`  
`struct FOpenColorIOWrapperSourceColorSettings`  
_L138-151_
- desc: Matches FTextureSourceColorSettings in Engine/Texture.h
- L141 _public member_ `UE::Color::EEncoding EncodingOverride = UE::Color::EEncoding::None;` — Source encoding of the texture, exposing more options than just sRGB.
- L144 _public member_ `UE::Color::EColorSpace ColorSpace = UE::Color::EColorSpace::None;` — Source color space of the texture. Leave to None for custom color space.
- L147 _public member_ `TOptional<TStaticArray<FVector2d, 4>> ColorSpaceOverride = {};` — Optional chromaticity coordinates of a custom source color space.
- L150 _public member_ `UE::Color::EChromaticAdaptationMethod ChromaticAdaptationMethod = UE::Color::EChromaticAdaptationMethod::None;` — Chromatic adaption method applied if the source white point differs from the working color space white point.

#### class `FOpenColorIOWrapperEngineConfig`  
`class FOpenColorIOWrapperEngineConfig : public FOpenColorIOWrapperConfig`  
_L157-166_
- inherits: `FOpenColorIOWrapperConfig`
- desc: Wrapper around library-native config object for module-specific use cases. This uses the built-in studio config as a base.
- L163 _public prototype_ `FOpenColorIOWrapperEngineConfig();` — Constructor.
- L165 _public prototype_ `FOpenColorIOWrapperEngineConfig(FStringView InFilePath, EAddWorkingColorSpaceOption InOption = WCS_None) = delete;`

#### class `FOpenColorIOWrapperProcessor`  
`class FOpenColorIOWrapperProcessor final`  
_L172-270_
- desc: Wrapper around library-native processor object. This class can also be used for CPU transforms. It will allocate CPU processors as needed, and reuse them since they are by default cached by the library.
- L179 _public prototype_ `FOpenColorIOWrapperProcessor();` — Empty constructor.
- L189 _public prototype_ `explicit FOpenColorIOWrapperProcessor( const FOpenColorIOWrapperConfig* InConfig, FStringView InSourceColorSpace, FStringView InDestinationColorSpace, const TMap<FString, FString>& InContextKeyValues = {} );` — Constructor. @param InConfig Owner config. @param InSourceColorSpace Source color space name. @param InDestinationColorSpace Destination color space name. @param InContextKeyValues (Optional) Additional context modifiers.
- L206 _public prototype_ `explicit FOpenColorIOWrapperProcessor( const FOpenColorIOWrapperConfig* InConfig, FStringView InSourceColorSpace, FStringView InDisplay, FStringView InView, bool bInverseDirection = false, const TMap<FString, FString>& InContextKeyValues = {} );` — Constructor. @param InConfig Owner config. @param InSourceColorSpace Source color space name. @param InDisplay Display name in display-view transform. @param InView View name in display-view transform. @param bInverseDirection Flag for inverse transform direction. @param InContextKeyValues (Optional) Additional context modifiers.
- L223 _public prototype_ `explicit FOpenColorIOWrapperProcessor( const FOpenColorIOWrapperConfig* InConfig, FStringView InNamedTransform, bool bInverseDirection = false, const TMap<FString, FString>& InContextKeyValues = {} );` — Constructor. @param InConfig Owner config. @param InNamedTransform Transform name. @param bInverseDirection Flag for inverse transform direction. @param InContextKeyValues (Optional) Additional context modifiers.
- L235 _public prototype_ `static FOpenColorIOWrapperProcessor CreateTransformToWorkingColorSpace( const FOpenColorIOWrapperSourceColorSettings& InSourceColorSettings );` — Create a processor from source color settings to working color space. @param InColorSettings Source encoding and colorspace. @return Processor of the transform
- L240 _public prototype_ `bool IsValid() const;` — Valid when the processor has been successfully created and isn't null.
- L243 _public prototype_ `FString GetCacheID() const;` — Get the string hash of the processor.
- L250 _public prototype_ `static FString GetTransformToWorkingColorSpaceName(const FOpenColorIOWrapperSourceColorSettings& InSourceColorSettings);` — Get the generated transform name from source color settings to working color space. @param InColorSettings Source encoding and colorspace. @return Generated name of the transform
- L253 _public prototype_ `bool TransformColor(FLinearColor& InOutColor) const;` — Apply the CPU color transform in-place to the specified color.
- L256 _public prototype_ `bool TransformImage(const FImageView& InOutImage) const;` — Apply the CPU color transform in-place to the specified image.
- L263 _public prototype_ `bool TransformImage(const FImageView& SrcImage, const FImageView& DestImage) const;` — Apply the CPU color transform from the source image to the destination image. (The destination FImageView is const but what it points at is not.) Note: This function is currently less optimal, as it is not parallelized.
- L267 _private member_ `TPimplPtr<struct FOpenColorIOProcessorPimpl, EPimplPtrMode::DeepCopy> Pimpl;`

#### class `FOpenColorIOWrapperGPUProcessor`  
`class FOpenColorIOWrapperGPUProcessor final`  
_L275-342_
- desc: Wrapper around library-native GPU processor object.
- L285 _public prototype_ `explicit FOpenColorIOWrapperGPUProcessor( FOpenColorIOWrapperProcessor InProcessor, bool bUseLegacy = false );` — Constructor. @param InProcessor Parent processor. @param InOptions Initialization options.
- L291 _public prototype_ `bool IsValid() const;` — Valid when the processor has been successfully created and isn't null.
- L300 _public prototype_ `bool GetShader(FString& OutShaderCacheID, FString& OutShaderCode) const;` — Get the generated shader. @param OutShaderCacheID Generated shader hash string. @param OutShaderCode Generated shader text. @return True when the result is valid.
- L303 _public prototype_ `uint32 GetNum3DTextures() const;` — Get the number of 3D LUT textures.
- L315 _public prototype_ `bool Get3DTexture(uint32 InIndex, FName& OutName, uint32& OutEdgeLength, TextureFilter& OutTextureFilter, const float*& OutData) const;` — Get the index-specific 3D LUT texture used by the shader transform. @param InIndex Index of the texture. @param OutName Shader parameter name of the texture. @param OutEdgeLength Size of the texture. @param OutTextureFilter Texture filter type. @param OutData Raw texel data. @return True when the result is valid.
- L318 _public prototype_ `uint32 GetNumTextures() const;` — Get the number of 2D LUT textures. (1D resources are disabled in our case.)
- L332 _public prototype_ `bool GetTexture(uint32 InIndex, FName& OutName, uint32& OutWidth, uint32& OutHeight, TextureFilter& OutTextureFilter, bool& bOutRedChannelOnly, const float*& OutData) const;` — Get the index-specific 2D LUT texture used by the shader transform. @param InIndex Index of the texture. @param OutName Shader parameter name of the texture. @param OutWidth Width of the texture. @param OutHeight Height of the texture. @param OutTextureFilter Texture filter type. @param bOutRedChannelOnly Flag indicating whether the texture has a single channel or is RGB. @param OutData Raw texel data. @return True when the result is valid.
- L335 _public prototype_ `FString GetCacheID() const;` — Get the string hash of the gpu processor.
- L339 _private member_ `const FOpenColorIOWrapperProcessor ParentProcessor;`
- L341 _private member_ `TPimplPtr<struct FOpenColorIOGPUProcessorPimpl, EPimplPtrMode::DeepCopy> GPUPimpl;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace OpenColorIOWrapper`
- L22 _function_ `constexpr const TCHAR* GetWorkingColorSpaceName()` (scope `OpenColorIOWrapper`) — Color space name of the engine's working color space we insert in OpenColorIO configs.
- L28 _function_ `constexpr const TCHAR* GetShaderFunctionName()` (scope `OpenColorIOWrapper`) — Default generated shader function name.
- L34 _variable_ `static constexpr uint32 Legacy3dEdgeLength = 65;` (scope `OpenColorIOWrapper`) — Default LUT size used in the legacy gpu processor
- L37 _prototype_ `const TCHAR* GetVersion();` (scope `OpenColorIOWrapper`) — Get the OpenColorIO version string.
- L40 _prototype_ `uint32 GetVersionHex();` (scope `OpenColorIOWrapper`) — Get the OpenColorIO version hex value.
- L43 _prototype_ `void ClearAllCaches();` (scope `OpenColorIOWrapper`) — Calls the native function of the same name.

### `Source/Runtime/OpenColorIOWrapper/Public/OpenColorIOWrapperModule.h` (Public)


#### class `IOpenColorIOWrapperModule`  
`class IOpenColorIOWrapperModule : public IModuleInterface`  
_L15-50_
- inherits: `IModuleInterface`
- desc: Interface for the OpenColorIO module.
- L24 _public function_ `static IOpenColorIOWrapperModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L45 _public prototype_ `virtual FOpenColorIOWrapperEngineConfig& GetEngineBuiltInConfig() = 0;` — Returns a minimal dynamically-created native config for engine (working color spaces) conversions.
- L49 _public prototype_ `virtual ~IOpenColorIOWrapperModule() = default;` — Virtual destructor

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenColorIOWrapper, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenColorIOWrapper, Log, All);`
