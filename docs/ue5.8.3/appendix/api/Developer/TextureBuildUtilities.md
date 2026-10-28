# Developer / TextureBuildUtilities

- module root: `Source/Developer/TextureBuildUtilities`
- headers: 1; symbols: 39
- symbol kinds: enum=1, enumerator=1, function=1, macro=1, member=7, namespace=5, prototype=21, struct=2
- PrivateDependencyModuleNames: Core, ImageCore, TextureFormat
- PrivateIncludePathModuleNames: Engine, TextureCompressor

### `Source/Developer/TextureBuildUtilities/Public/TextureBuildUtilities.h` (Public)


#### enum `UE::TextureBuildUtilities::(anonymous)`  
``  
_L29-32_

#### struct `UE::TextureBuildUtilities::FTextureBuildMetadata`  
`struct FTextureBuildMetadata`  
_L54-63_
- desc: Carries information out of the build that we don't want to cook or save off in the runtime
- L58 _public member_ `uint64 PreEncodeMipsHash = 0;` — Digests of the data at various processing stages so we can track down determinism issues that arise. Currently just the hash from before we pass to the encoders.
- L60 _public prototype_ `FCbObject ToCompactBinaryWithDefaults() const;`
- L61 _public prototype_ `FTextureBuildMetadata(FCbObject InCbObject);`
- L62 _public prototype_ `FTextureBuildMetadata() = default;`

#### struct `UE::TextureBuildUtilities::FVirtualTextureSourceBlockInfo`  
`struct FVirtualTextureSourceBlockInfo`  
_L107-122_
- desc: Mirrors Texture.h FTextureSourceBlock for use without Texture.h This provides the layout representation of a block of source pixels for a virtual texture. The format is separate as VTs can have multiple layers, each with the same source pixel layout but with a different format (and thus byte size).
- L111 _public member_ `int32 BlockX=0;` — @@ I don't actually know what coordinate space blocks are in and none of the code I'm looking at seems very clear on it. afaict it's just the index of the source image and where it exists. I don't know what happens if you have a hole in your source blocks.
- L112 _public member_ `int32 BlockY=0;`
- L115 _public member_ `int32 SizeX=0;` — Pixel dims.
- L116 _public member_ `int32 SizeY=0;`
- L119 _public member_ `int32 NumSlices=0;` — afaict this is ignored: see "BlockData.NumSlices = 1; // TODO?" in VirtualTextureDataBuilder
- L121 _public member_ `int32 NumMips=0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEXTUREBUILDUTILITIES_API`
- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace TextureBuildUtilities` (scope `UE`)
- L31 _enumerator_ `PLACEHOLDER_TEXTURE_SIZE = 4` (scope `UE::TextureBuildUtilities::__anonaa76d9980103`) — The width and height of the placeholder gpu texture we create when the texture is cpu accessible.
- L35 _namespace_ `namespace EncodedTextureExtendedData` (scope `UE::TextureBuildUtilities`)
- L37 _prototype_ `FCbObject ToCompactBinary(const FEncodedTextureExtendedData& InExtendedData);` (scope `UE::TextureBuildUtilities::EncodedTextureExtendedData`)
- L38 _prototype_ `bool FromCompactBinary(FEncodedTextureExtendedData& OutExtendedData, FCbObject InCbObject);` (scope `UE::TextureBuildUtilities::EncodedTextureExtendedData`)
- L41 _namespace_ `namespace EncodedTextureDescription` (scope `UE::TextureBuildUtilities`)
- L43 _prototype_ `FCbObject ToCompactBinary(const FEncodedTextureDescription& InDescription);` (scope `UE::TextureBuildUtilities::EncodedTextureDescription`)
- L44 _prototype_ `bool FromCompactBinary(FEncodedTextureDescription& OutDescription, FCbObject InCbObject);` (scope `UE::TextureBuildUtilities::EncodedTextureDescription`)
- L47 _namespace_ `namespace TextureEngineParameters` (scope `UE::TextureBuildUtilities`)
- L49 _prototype_ `FCbObject ToCompactBinaryWithDefaults(const FTextureEngineParameters& InEngineParameters);` (scope `UE::TextureBuildUtilities::TextureEngineParameters`)
- L50 _prototype_ `bool FromCompactBinary(FTextureEngineParameters& OutEngineParameters, FCbObject InCbObject);` (scope `UE::TextureBuildUtilities::TextureEngineParameters`)
- L65 _prototype_ `bool TextureFormatIsHdr(FName const& InName);` (scope `UE::TextureBuildUtilities`)
- L69 _prototype_ `bool TextureNeedsDecodeForPC(EPixelFormat InPixelFormat, int32 InCreateMip0SizeX, int32 InCreateMip0SizeY);` (scope `UE::TextureBuildUtilities`) — Pass in the dimensions of the texture that will be created on the PC (i.e. take in to consideration whether LODBias mips will be stripped or not)
- L74 _prototype_ `const FName TextureFormatRemovePrefixFromName(FName const& InName, FName& OutPrefix);` (scope `UE::TextureBuildUtilities`) — Removes platform and other custom prefixes from the name. Returns plain format name and the non-platform prefix (with trailing underscore). i.e. PLAT_BLAH_AutoDXT returns AutoDXT and writes BLAH_ to OutPrefix.
- L77 _prototype_ `const FName TextureFormatRemovePlatformPrefixFromName(FName const& InName);` (scope `UE::TextureBuildUtilities`) — removes platform prefix but leaves other custom prefixes :
- L79 _function_ `FORCEINLINE const FName TextureFormatRemovePrefixFromName(FName const& InName)` (scope `UE::TextureBuildUtilities`)
- L87 _prototype_ `ERawImageFormat::Type GetVirtualTextureBuildIntermediateFormat(const FTextureBuildSettings& BuildSettings);` (scope `UE::TextureBuildUtilities`) — Get the format to use for output of the VT Intermediate stage, cutting into tiles and processing the next step will then encode from this format to the desired output format
- L89 _prototype_ `void GetPlaceholderTextureImageInfo(FImageInfo* OutImageInfo);` (scope `UE::TextureBuildUtilities`)
- L90 _prototype_ `void GetPlaceholderTextureImage(FImage* OutImage);` (scope `UE::TextureBuildUtilities`)
- L94 _prototype_ `bool GetPowerOfTwoTargetTextureSize(int32 InMip0SizeX, int32 InMip0SizeY, int32 InMip0NumSlices, bool bInIsVolume, ETexturePowerOfTwoSetting::Type InPow2Setting, int32 InResizeDuringBuildX, int32 InResizeDuringBuildY, int32& OutTargetSizeX, int32& OutTargetSizeY, int32& OutTargetSizeZ);` (scope `UE::TextureBuildUtilities`) — Returns true if the target texture size is different and padding/stretching is required. if InPow2Setting == None, the Out sizes match the In sizes, and false is returned
- L98 _prototype_ `EPixelFormat GetOutputPixelFormatWithFallback(const FTextureBuildSettings& InBuildSettings, bool bInKnownAlphaFallback);` (scope `UE::TextureBuildUtilities`) — Return the final output pixel format. When we don't know the source's alpha channel information this might not be knowable. In those cases treat such sources as having an alpha channel if bKnownAlphaFallback is true.
- L101 _prototype_ `int64 GetPhysicalTextureBuildMemoryEstimate(const FTextureBuildSettings* InBuildSettings, const FImageInfo& InSourceImageInfo, int32 InMipCount);` (scope `UE::TextureBuildUtilities`) — Return the estimate for how much memory a physical texture will take to build, for managing memory resources during build dispatch.
- L125 _prototype_ `int64 GetVirtualTextureRequiredMemoryEstimate(const FTextureBuildSettings* InBuildSettingsPerLayer, TConstArrayView<ERawImageFormat::Type> InLayerFormats, TConstArrayView<UE::TextureBuildUtilities::FVirtualTextureSourceBlockInfo> InSourceBlocks);` (scope `UE::TextureBuildUtilities`) — Return the estimate for how much memory a virtual texture will take to build, for managing memory resources during build dispatch.
- L130 _prototype_ `uint32 ComputeLongLatCubemapExtents(int32 SrcImageSizeX, uint32 MaxCubemapTextureResolution);` (scope `UE::TextureBuildUtilities`) — ComputeLongLatCubemapExtents is done after pad-to-pow2
