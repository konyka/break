# Developer / TextureCompressor

- module root: `Source/Developer/TextureCompressor`
- headers: 1; symbols: 125
- symbol kinds: class=1, function=10, macro=1, member=96, namespace=2, prototype=12, struct=3
- PrivateDependencyModuleNames: Core, ImageCore, OpenColorIOWrapper, TextureBuildUtilities, TextureFormat
- PrivateIncludePathModuleNames: Engine

### `Source/Developer/TextureCompressor/Public/TextureCompressorModule.h` (Public)


#### struct `FCompressedImage2D`  
`struct FCompressedImage2D`  
_L21-50_
- desc: Compressed image data.
- L23 _public member_ `TArray64<uint8> RawData;`
- L26 _public member_ `int32 SizeX;` — in the past Sizes here were aligned up to a compressed block size multiple that is no longer done, the real size is stored
- L27 _public member_ `int32 SizeY;`
- L30 _public member_ `int32 SizeZ;` — `UE_DEPRECATED(5.5, "Use NumSlicesWithDepth or GetRHIStyleSizeZ instead")`
- L34 _public member_ `int32 NumSlicesWithDepth;` — See FEncodedTextureDescription::GetNumSlices_WithDepth. Cubemaps = 6, Arrays = Count, Cubemaparrays = Count*6, Volume = Depth
- L44 _public function_ `int32 GetRHIStyleSizeZ(bool bTextureArray, bool bVolume) const` — This is the SizeZ that gets passed to the RHI texture mip map stuff. See FStreamableTextureResource::SizeZ. It's weird because it's actually NOT used for cubemaps or cubemap arrays, however it does get saved in derived data in Texture2DMipMap, so we need to continue to pass through the previous values for cubemaps which are: *non array* cubemap = 1 *array* cubemaps = array_count * 6 volume = depth arrays = array_count
- L49 _public member_ `EPixelFormat PixelFormat;`

#### struct `FColorAdjustmentParameters`  
`struct FColorAdjustmentParameters`  
_L55-93_
- desc: Color adjustment parameters.
- L58 _public member_ `float AdjustBrightness;` — Brightness adjustment (scales HSV value)
- L61 _public member_ `float AdjustBrightnessCurve;` — Curve adjustment (raises HSV value to the specified power)
- L64 _public member_ `float AdjustSaturation;` — Saturation adjustment (scales HSV saturation)
- L67 _public member_ `float AdjustVibrance;` — "Vibrance" adjustment (HSV saturation algorithm adjustment)
- L70 _public member_ `float AdjustRGBCurve;` — RGB curve adjustment (raises linear-space RGB color to the specified power)
- L73 _public member_ `float AdjustHue;` — Hue adjustment (offsets HSV hue by value in degrees)
- L76 _public member_ `float AdjustMinAlpha;` — Remaps the alpha to the specified min/max range  (Non-destructive; Requires texture source art to be available.)
- L79 _public member_ `float AdjustMaxAlpha;` — Remaps the alpha to the specified min/max range  (Non-destructive; Requires texture source art to be available.)
- L82 _public function_ `FColorAdjustmentParameters() : AdjustBrightness( 1.0f ), AdjustBrightnessCurve( 1.0f ), AdjustSaturation( 1.0f ), AdjustVibrance( 0.0f ), AdjustRGBCurve( 1.0f ), AdjustHue( 0.0f ), AdjustMinAlpha( 0.0f ), AdjustMaxAlpha( 1.0f )` — Constructor

#### struct `FTextureBuildSettings`  
`struct FTextureBuildSettings`  
_L98-459_
- desc: Texture build settings.
- L105 _public member_ `FCbObjectView FormatConfigOverride;` — Format specific config object view or null if no format specific config is applied as part of this build. This is only for DDC2 builds, and gets created when the build settings gets serialized for sending - it is not valid beforehand. Meaning, it should only ever be read from build workers. It is used in place of INIs or command line args to configure individual texture formats since those are not available to the texture build workers.
- L107 _public member_ `FColorAdjustmentParameters ColorAdjustment;` — Color adjustment parameters.
- L109 _public member_ `bool bDoScaleMipsForAlphaCoverage;` — Enable preserving alpha coverage.
- L111 _public member_ `FVector4f AlphaCoverageThresholds;` — Channel values to compare to when preserving alpha coverage.
- L113 _public member_ `bool bUseNewMipFilter;` — Use newer & faster mip generation filter
- L115 _public member_ `bool bNormalizeNormals;` — Normalize normals after mip gen, before compression
- L117 _public member_ `float MipSharpening;` — The desired amount of mip sharpening.
- L119 _public member_ `uint32 DiffuseConvolveMipLevel;` — For angular filtered cubemaps, the mip level which contains convolution with the diffuse cosine lobe.
- L121 _public member_ `uint32 SharpenMipKernelSize;` — The size of the kernel with which mips should be sharpened. 2 for 2x2, 4 for 4x4, 6 for 6x6, 8 for 8x8
- L123 _public member_ `uint32 MaxTextureResolution;` — For maximum resolution.
- L125 _public member_ `FName TextureFormatName;` — Format of the compressed texture, used to choose a compression DLL.
- L127 _public member_ `bool bHDRSource;` — Whether the texture being built contains HDR source data
- L129 _public member_ `uint8 MipGenSettings;` — Mipmap generation settings.
- L131 _public member_ `uint32 bCubemap : 1;` — Whether the texture being built is a cubemap.
- L133 _public member_ `uint32 bTextureArray : 1;` — Whether the texture being built is a texture array.
- L135 _public member_ `uint32 bVolume : 1;` — Whether the texture being built is a volume.
- L137 _public member_ `uint32 bLongLatSource : 1;` — Whether the texture being built from long/lat source to cubemap.
- L139 _public member_ `uint32 bSRGB : 1;` — Whether the texture contains color data in the sRGB colorspace.
- L141 _public member_ `uint8 SourceEncodingOverride;` — Advanced source encoding of the image. UE::Color::EEncoding / ETextureSourceEncoding (same thing)
- L143 _public member_ `bool bHasColorSpaceDefinition;` — Whether the texture has a defined source color space.
- L145 _public member_ `FVector2f RedChromaticityCoordinate;` — Red chromaticity coordinate of the source color space.
- L147 _public member_ `FVector2f GreenChromaticityCoordinate;` — Green chromaticity coordinate of the source color space.
- L149 _public member_ `FVector2f BlueChromaticityCoordinate;` — Blue chromaticity coordinate of the source color space.
- L151 _public member_ `FVector2f WhiteChromaticityCoordinate;` — White chromaticity coordinate of the source color space.
- L153 _public member_ `uint8 ChromaticAdaptationMethod;` — Chromatic adaption method applied if the source white point differs from the working color space white point.
- L155 _public member_ `uint32 bUseLegacyGamma : 1;` — Whether the texture should use the legacy gamma space for converting to sRGB
- L157 _public member_ `uint32 bPreserveBorder : 1;` — Whether the border of the image should be maintained during mipmap generation.
- L159 _public member_ `uint32 bForceNoAlphaChannel : 1;` — Whether we should discard the alpha channel even if it contains non-zero values in the pixel data.
- L161 _public member_ `uint32 bForceAlphaChannel : 1;` — Whether we should not discard the alpha channel when it contains 1 for the entire texture.
- L163 _public member_ `uint32 bComputeBokehAlpha : 1;` — Whether bokeh alpha values should be computed for the texture.
- L165 _public member_ `uint32 bReplicateRed : 1;` — Whether the contents of the red channel should be replicated to all channels.
- L167 _public member_ `uint32 bReplicateAlpha : 1;` — Whether the contents of the alpha channel should be replicated to all channels.
- L169 _public member_ `uint32 bDownsampleWithAverage : 1;` — Whether each mip should use the downsampled-with-average result instead of the sharpened result.
- L171 _public member_ `uint32 bSharpenWithoutColorShift : 1;` — Whether sharpening should prevent color shifts.
- L173 _public member_ `uint32 bBorderColorBlack : 1;` — Whether the border color should be black.
- L175 _public member_ `uint32 bFlipGreenChannel : 1;` — Whether the green channel should be flipped. Typically only done on normal maps.
- L177 _public member_ `uint32 bApplyYCoCgBlockScale : 1;` — Calculate and apply a scale for YCoCg textures. This calculates a scale for each 4x4 block, applies it to the red and green channels and stores the scale in the blue channel.
- L179 _public member_ `uint32 bApplyKernelToTopMip : 1;` — 1:apply mip sharpening/blurring kernel to top mip as well (at half the kernel size), 0:don't
- L181 _public member_ `uint32 bRenormalizeTopMip : 1;` — 1: renormalizes the top mip (only useful for normal maps, prevents artists errors and adds quality) 0:don't
- L183 _public member_ `uint32 bCPUAccessible : 1;` — If set, the texture will generate a tiny placeholder hw texture and save off a copy of the top mip for CPU access.
- L185 _public member_ `uint8 CompositeTextureMode;` — e.g. CTM_RoughnessFromNormalAlpha
- L187 _public member_ `float CompositePower;` — default 1, high values result in a stronger effect
- L192 _public member_ `uint32 LODBias;` — The source texture's final LOD bias (i.e. includes LODGroup based biases). Generally this does not affect the built texture as the mips are stripped during cooking, however for tiling some platforms require knowing the actual texture size that will be created. In this case they need to know the LOD bias to compensate.
- L194 _public member_ `uint32 LODBiasWithCinematicMips;` — The source texture's final LOD bias (i.e. includes LODGroup based biases). This allows cinematic mips as well.
- L199 _public member_ `uint32 bStreamable_Unused : 1;` — Can the texture be streamed. This is deprecated because it was used in a single place in a single platform for something that handled an edge case that never happened. That code is removes so this is never touched other than saving it, and it'll be removed soon.
- L201 _public member_ `uint32 bVirtualStreamable : 1;` — Is the texture streamed using the VT system
- L203 _public member_ `uint32 bChromaKeyTexture : 1;` — Whether to chroma key the image, replacing any pixels that match ChromaKeyColor with transparent black
- L205 _public member_ `uint8 PowerOfTwoMode;` — How to stretch or pad the texture to a power of 2 size (if necessary); ETexturePowerOfTwoSetting::Type, opaque to avoid dependencies on Engine headers.
- L207 _public member_ `FColor PaddingColor;` — The color used to pad the texture out if it is resized due to PowerOfTwoMode
- L209 _public member_ `bool bPadWithBorderColor;` — If set to true, texture padding will be performed using colors of the border pixels in order to improve quality of the generated mipmaps.
- L211 _public member_ `int32 ResizeDuringBuildX;` — Width of the resized texture when using "Resize To Specific Resolution" padding and resizing option. If set to zero, original width will be used.
- L213 _public member_ `int32 ResizeDuringBuildY;` — Width of the resized texture when using "Resize To Specific Resolution" padding and resizing option. If set to zero, original height will be used.
- L215 _public member_ `FColor ChromaKeyColor;` — The color that will be replaced with transparent black if chroma keying is enabled
- L217 _public member_ `float ChromaKeyThreshold;` — The threshold that components have to match for the texel to be considered equal to the ChromaKeyColor when chroma keying (<=, set to 0 to require a perfect exact match)
- L221 _public member_ `int32 CompressionQuality;` — The quality of the compression algorithm (min 0 - lowest quality, highest cook speed, 4 - highest quality, lowest cook speed) only used by ASTC formats right now.
- L224 _public member_ `int32 LossyCompressionAmount;` — ETextureLossyCompressionAmount - oodle resolves this to RDO lambda during fast/final resolution.
- L227 _public member_ `FName OodleTextureSdkVersion;` — which version of Oodle Texture to encode with
- L231 _public member_ `FName AstcEncVersion;` — If NAME_None, this encodes with the first non-versioned astcenc (4.2.0). This must not include "." since it's mixed in to the ddc key
- L234 _public member_ `bool bOodlePreserveExtremes;` — If set to true, then Oodle encoder preserves 0 and 255 (0.0 and 1.0) values exactly in alpha channel for BC3/BC7 and in all channels for BC4/BC5.
- L239 _public member_ `uint8 OodleRDO;` — Encoding settings resolved from fast/final. Enums aren't accessible from this module: ETextureEncodeEffort, ETextureUniversalTiling.
- L240 _public member_ `uint8 OodleEncodeEffort;`
- L241 _public member_ `uint8 OodleUniversalTiling;`
- L242 _public member_ `bool bOodleUsesRDO;`
- L245 _public member_ `float Downscale;` — Values > 1.0 will scale down source texture. Ignored for textures with mips
- L247 _public member_ `uint8 DownscaleOptions;` — ETextureDownscaleOptions
- L249 _public member_ `int32 VirtualAddressingModeX;` — TextureAddress, opaque to avoid dependencies on engine headers. How to address the texture (clamp, wrap, ...) for virtual textures this is baked into the build data, for regular textures this is ignored.
- L250 _public member_ `int32 VirtualAddressingModeY;`
- L252 _public member_ `int32 VirtualTextureTileSize;` — Size in pixels of virtual texture tile, not including border
- L254 _public member_ `int32 VirtualTextureBorderSize;` — Size in pixels of border on virtual texture tile
- L260 _public member_ `uint8 RepresentsEncodeSpeedNoSend;` — Which encode speed this build settings represents. This is not sent to the build worker, it is used to return what was done to the UI. ETextureEncodeSpeed, either Final or Fast.
- L263 _public member_ `uint8 TextureAddressModeX = 0;` — "TextureAddress" enum values : (TA_Wrap default)
- L264 _public member_ `uint8 TextureAddressModeY = 0;`
- L265 _public member_ `uint8 TextureAddressModeZ = 0;`
- L268 _public member_ `const ITextureTiler* Tiler = nullptr;` — If the target format is a tiled format and can leverage reusing the linear encoding, this is not nullptr.
- L271 _public member_ `const ITextureTiler* TilerEvenIfNotSharedLinear = nullptr;` — If the target format has a tiler we store it here independent of shared linear
- L275 _public member_ `bool bAffectedBySharedLinearEncoding = false;` — If shared linear is enabled _at all_ and this texture in involved with that _at all_ then we set this so we can segregate the derived data keys.
- L279 _public member_ `FName BaseTextureFormatName;` — If we have a child format, this is the base format (i.e. will have the platform prefix removed). Otherwise equal to TextureFormatName.
- L282 _public member_ `const ITextureFormat* BaseTextureFormat = nullptr;` — Cached pointer to BaseTextureFormatName. Resolved in FinalizeBuildSettingsForLayer and ResolveBuildSettings
- L285 _public member_ `bool bKnowAlphaTransparency = false;` — Whether bHasTransparentAlpha is valid.
- L289 _public member_ `bool bHasTransparentAlpha = false;` — Only valid if bKnowAlphaTransparency is true. This is whether the resulting texture is expected to require an alpha channel based on scanning the source mips and analyzing the build settings.
- L293 _public member_ `bool bDecodeForPCUsage = false;` — If true, after encoding and potentially tiling, convert the texture back to something a PC can render so we can view the final encoding.
- L295 _public member_ `static constexpr uint32 MaxTextureResolutionDefault = TNumericLimits<uint32>::Max();`
- L298 _public function_ `FTextureBuildSettings() : bDoScaleMipsForAlphaCoverage(false) , AlphaCoverageThresholds(0, 0, 0, 0) , bUseNewMipFilter(false) , bNormalizeNormals(false) , MipSharpening(0.0f) , DiffuseConvolveMipLevel(0) , SharpenMipKernelSize(2) , MaxTextureResolution(MaxTextureResolutionDefault) , bHDRSource(false) , MipGenSettings(1 ) , bCubemap(false) , bTextureArray(false) , bVolume(false) , bLongLatSource(false) , bSRGB(false) , SourceEncodingOverride(0 ) , bHasColorSpaceDefinition(false) , RedChromaticityCoordinate(0, 0) , GreenChromaticityCoordinate(0, 0) , BlueChromaticityCoordinate(0, 0) , WhiteChromaticityCoordinate(0, 0) , ChromaticAdaptationMethod(1 ) , bUseLegacyGamma(false) , bPreserveBorder(false) , bForceNoAlphaChannel(false) , bForceAlphaChannel(false) , bComputeBokehAlpha(false) , bReplicateRed(false) , bReplicateAlpha(false) , bDownsampleWithAverage(false) , bSharpenWithoutColorShift(false) , bBorderColorBlack(false) , bFlipGreenChannel(false) , bApplyYCoCgBlockScale(false) , bApplyKernelToTopMip(false) , bRenormalizeTopMip(false) , bCPUAccessible(false) , CompositeTextureMode(0 ) , CompositePower(1.0f)` — Default settings.
- L370 _public function_ `FORCEINLINE EGammaSpace GetSourceGammaSpace() const`
- L375 _public function_ `FORCEINLINE EGammaSpace GetDestGammaSpace() const`
- L381 _public function_ `FORCEINLINE EGammaSpace GetGammaSpace() const` — `UE_DEPRECATED(5.1, "Use GetDestGammaSpace or GetSourceGammaSpace (probably Dest)")`
- L388 _public function_ `bool GetTextureExpectsAlphaInPixelFormat(bool bTopMipAlphaDetected) const` — If there is a choice to be had between two formats: one with alpha and one without, this returns which one the texture expects.
- L403 _public function_ `void GetOutputAlphaFromKnownAlphaOrFallback(bool* bOutOutputHasAlpha, bool bUnknownSourceAlphaFallback = true) const` — bUnknownSourceAlphaFallback is whether we should treat the source as having alpha, in cases where the source alpha is unknown
- L417 _public function_ `bool GetOutputAlphaFromKnownAlphaOrFail(bool* bOutOutputHasAlpha) const` — returns false if we can't determine instead of passing through a fallback
- L443 _public prototype_ `void GetEncodedTextureDescription(FEncodedTextureDescription* OutTextureDescription, const ITextureFormat* InTextureFormat, int32 InEncodedMip0SizeX, int32 InEncodedMip0SizeY, int32 InEncodedMip0NumSlices, int32 InMipCount, bool bInImageHasAlphaChannel) const;` — Convert the build settings to an actual texture description containing enough information to describe the texture to hardware APIs.
- L444 _public prototype_ `void GetEncodedTextureDescriptionWithPixelFormat(FEncodedTextureDescription* OutTextureDescription, EPixelFormat InEncodedPixelFormat, int32 InEncodedMip0SizeX, int32 InEncodedMip0SizeY, int32 InEncodedMip0NumSlices, int32 InMipCount) const;`
- L447 _public prototype_ `bool GetEncodedTextureDescriptionFromSourceMips(FEncodedTextureDescription* OutTextureDescription, const ITextureFormat* InTextureFormat, int32 InSourceMip0SizeX, int32 InSourceMip0SizeY, int32 InSourceMip0NumSlices, int32 InSourceMipCount, bool bInImageHasAlphaChannel) const;` — As per GetEncodedTextureDescription but the mip sizes are pre encoding. Return false for same reasons as GetOutputMipInfo
- L453 _public prototype_ `bool GetOutputMipInfo( int32 InMip0SizeX, int32 InMip0SizeY, int32 InMip0NumSlices, int32 InExistingMipCount, int32& OutMip0SizeX, int32& OutMip0SizeY, int32& OutMip0NumSlices, int32& OutMipCount) const;` — Return the expected size and mip count for a texture processed with these build settings. returns false on virtual textures - physical textures only! returns false if there's an invalid build settings - should never happen - build settings should never get generated such that this fails!
- L458 _public prototype_ `static uint32 GetOpenColorIOVersion();` — Obtain the OpenColorIO library version, primarily used for DDC invalidation.

#### class `ITextureCompressorModule`  
`class ITextureCompressorModule : public IModuleInterface`  
_L464-565_
- inherits: `IModuleInterface`
- desc: Texture compression module interface.
- L480 _public prototype_ `virtual bool BuildTexture( TArray<struct FImage>& SourceMips, TArray<struct FImage>& AssociatedNormalSourceMips, const FTextureBuildSettings& BuildSettings, FStringView DebugTexturePathName, TArray<FCompressedImage2D>& OutTextureMips, uint32& OutNumMipsInTail, uint32& OutExtData, UE::TextureBuildUtilities::FTextureBuildMetadata* OutMetadata ) = 0;` — Builds a texture from source images. @param SourceMips - The input mips. @param BuildSettings - Build settings. @param DebugTexturePathName - The path name of the texture being built, for logging/filtering/dumping. @param OutCompressedMips - The compressed mips built by the compressor. @param OutNumMipsInTail - The number of mips that are joined into a single mip tail mip @param OutExtData - Extra data that the runtime may need @returns true on success SourceMips can be freed by this call
- L499 _public prototype_ `static void GenerateMipChain( const FTextureBuildSettings& Settings, const FImage& BaseImage, TArray<FImage> &OutMipChain, uint32 MipChainDepth );` — Generate a full mip chain. The input mip chain must have one or more mips. @param Settings - Preprocess settings. @param BaseImage - An image that will serve as the source for the generation of the mip chain. @param OutMipChain - An array that will contain the resultant mip images. Generated mip levels are appended to the array. @param MipChainDepth - number of mip images to produce. Mips chain is finished when either a 1x1 mip is produced or 'MipChainDepth' images have been produced.
- L516 _public prototype_ `static bool DetermineAlphaChannelTransparency(const FTextureBuildSettings& InBuildSettings, const FLinearColor& InChannelMin, const FLinearColor& InChannelMax, bool& bOutAlphaIsTransparent);` — Given the channel min/max for the top mip of a texture's source, determine whether there will be any transparency after image processing occurs, and thus the texture will need to be BC3 for the purposes of AutoDXT format selection. @param bOutAlphaIsTransparent		*This is undetermined if the return is false!*. If true, we expect the image after processing to require an alpha channel. @return							Whether the alpha channel can be determined. There are plenty of edge cases where it's not feasible to determine the result prior to full processing, however these are rare in practice.
- L524 _public prototype_ `static void AdjustImageColors(FImage& Image, const FTextureBuildSettings& InBuildSettings);` — Adjusts the colors of the image using the specified settings @param	Image			Image to adjust @param	InBuildSettings	Image build settings
- L532 _public prototype_ `static void GenerateBaseCubeMipFromLongitudeLatitude2D(FImage* OutMip, const FImage& SrcImage, const uint32 MaxCubemapTextureResolution, uint8 SourceEncodingOverride = 0);` — `UE_DEPRECATED(5.3, "GenerateBaseCubeMipFromLongitudeLatitude2D with FTextureBuildSettings should be used.")` — Generates the base cubemap mip from a longitude-latitude 2D image. @param OutMip - The output mip. @param SrcImage - The source longlat image.
- L540 _public prototype_ `static void GenerateBaseCubeMipFromLongitudeLatitude2D(FImage* OutMip, const FImage& SrcImage, const FTextureBuildSettings& InBuildSettings);` — Generates the base cubemap mip from a longitude-latitude 2D image. @param OutMip - The output mip. @param SrcImage - The source longlat image. @param InBuildSettings - Image build settings
- L548 _public prototype_ `static void GenerateAngularFilteredMips(TArray<FImage>& InOutMipChain, int32 NumMips, uint32 DiffuseConvolveMipLevel);` — Generates angularly filtered mips. @param InOutMipChain - The mip chain to angularly filter. @param NumMips - The number of mips the chain should have. @param DiffuseConvolveMipLevel - The mip level that contains the diffuse convolution.
- L555 _public function_ `static FORCEINLINE int32 GetMipCountForBuildSettings( int32 InMip0SizeX, int32 InMip0SizeY, int32 InMip0NumSlices, int32 InExistingMipCount, const FTextureBuildSettings& InBuildSettings, int32& OutMip0SizeX, int32& OutMip0SizeY, int32& OutMip0NumSlices)` — `UE_DEPRECATED(5.5, "Just call GetOutputMipInfo directly off of build settings")` — Returns the number of mips that the given texture will generate with the given build settings, as well as the size of the top mip. Used for physical textures - not virtual textures.

#### Free symbols / members of external scopes

- L9 _macro_ `#define TEXTURE_COMPRESSOR_MODULENAME "TextureCompressor"`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TextureBuildUtilities` (scope `UE`)
