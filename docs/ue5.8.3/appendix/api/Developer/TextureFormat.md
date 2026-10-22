# Developer / TextureFormat

- module root: `Source/Developer/TextureFormat`
- headers: 5; symbols: 131
- symbol kinds: class=5, function=76, member=25, prototype=18, struct=5, typedef=2
- PrivateDependencyModuleNames: Core
- PrivateIncludePathModuleNames: TextureCompressor

### `Source/Developer/TextureFormat/Public/ChildTextureFormat.h` (Public)


#### class `FChildTextureFormat`  
`class FChildTextureFormat : public ITextureFormat`  
_L28-329_
- inherits: `ITextureFormat`
- desc: Version of ITextureFormat that handles a child texture format that is used as a "post-process" after compressing textures, useful for several platforms that need to modify already compressed texture data for optimal data. There are 3 ways a texture can get processed: -- ITextureFormat::SupportsTiling returns true. This should only be for the old Oodle RAD Game Tools supplied texture encoder and is being deprecated in favor of the new built-in Oodle texture encoder (TextureFormatOodle). In this case, the child format passes the images to the encoder to split apart prior to passing to the platform tools. -- FChildTextureFormat::GetTiler returns nullptr. This is being phased out because the linear version of the input texture gets encoded for each platform with a post process, wasting cook time. In this case the child format encodes the "base" texture and then tiles it using the platform tools. -- FChildTextureFormat::GetTiler returns a valid pointer. This is the most recent design. In this case, the child format is used as a holder of metadata and doesn't actually do any work (CompressImage class of functions not called).
- L32 _public function_ `FChildTextureFormat(const TCHAR* PlatformFormatPrefix) : FormatPrefix(PlatformFormatPrefix)`
- L38 _public function_ `virtual const FChildTextureFormat* GetChildFormat() const override final`
- L49 _public function_ `virtual const ITextureTiler* GetTiler() const` — Return the texture tiler for this platform. If present, then the texture build process will try to use the cached linear encoding for the texture as input rather than rebuilding the linear texture prior to tiling. Confusingly, this can not happen if the base texture format returns true for SupportsTiling, as that refers to the texture encoder, not the format.
- L54 _public function_ `FName GetBaseFormatName(FName ChildFormatName) const`
- L62 _public function_ `const ITextureFormat* GetBaseFormatObject(FName FormatName) const` — Given a platform specific format name, get the texture format object that will do the encoding.
- L77 _protected function_ `void AddBaseTextureFormatModules(const TCHAR* ModuleNameWildcard)`
- L96 _protected function_ `void FinishAddBaseTextureFormatModules()`
- L112 _protected function_ `FCbObjectView GetBaseFormatConfigOverride(const FCbObjectView& ObjView) const`
- L117 _public function_ `FTextureBuildSettings GetBaseTextureBuildSettings(const FTextureBuildSettings& BuildSettings) const`
- L129 _protected prototype_ `virtual uint8 GetChildFormatVersion(FName Format, const FTextureBuildSettings* BuildSettings) const = 0;` — The final version is a combination of parent and child formats, 8 bits for each
- L135 _protected prototype_ `virtual FString GetChildDerivedDataKeyString(const FTextureBuildSettings& InBuildSettings, int32 InMipCount, const FIntVector3& InMip0Dimensions) const = 0;` — Make the child type think about if they need a key string or not, by making it pure virtual. InMipCount and InMip0Dimensions are only valid for non-virtual textures (VTs should never call this function as they never tile)
- L143 _protected function_ `virtual FCbObject ExportGlobalChildFormatConfig(const FTextureBuildSettings& BuildSettings) const` — Obtains the global format config object for this texture format. @param BuildSettings Build settings. @returns The global format config object or an empty object if no format settings are defined for this texture format.
- L154 _protected function_ `virtual FCbObjectView GetChildFormatConfigOverride(const FCbObjectView& ObjView) const` — Obtains the format config appropriate for the build . @param ObjView A view of the entire format config container or null if none exists. @returns The format settings object view or a null view if the active global format config should be used.
- L163 _public function_ `virtual void GetSupportedFormats(TArray<FName>& OutFormats) const override`
- L168 _public function_ `virtual bool SupportsEncodeSpeed(FName Format, const ITargetPlatformSettings* TargetPlatform) const override`
- L173 _public function_ `virtual bool CanAcceptNonF32Source(FName Format) const override`
- L178 _public function_ `virtual FName GetEncoderName(FName Format) const override`
- L183 _public function_ `virtual uint16 GetVersion(FName Format, const FTextureBuildSettings* BuildSettings) const final`
- L194 _public function_ `virtual FString GetDerivedDataKeyString(const FTextureBuildSettings& InBuildSettings, int32 InMipCount, const FIntVector3& InMip0Dimensions) const final`
- L204 _public function_ `virtual EPixelFormat GetEncodedPixelFormat(const FTextureBuildSettings& InBuildSettings, bool bImageHasAlphaChannel) const`
- L210 _public function_ `bool CompressBaseImage( const FImage& InImage, const FTextureBuildSettings& BuildSettings, const FIntVector3& InMip0Dimensions, int32 InMip0NumSlicesNoDepth, int32 InMipIndex, int32 InMipCount, FStringView DebugTexturePathName, bool bImageHasAlphaChannel, FCompressedImage2D& OutCompressedImage ) const`
- L233 _public function_ `bool CompressBaseImageTiled( const FImage* Images, uint32 NumImages, const FTextureBuildSettings& BuildSettings, FStringView DebugTexturePathName, bool bImageHasAlphaChannel, TSharedPtr<FTilerSettings>& TilerSettings, FCompressedImage2D& OutCompressedImage ) const`
- L254 _public function_ `bool PrepareTiling( const FImage* Images, const uint32 NumImages, const FTextureBuildSettings& BuildSettings, bool bImageHasAlphaChannel, TSharedPtr<FTilerSettings>& OutTilerSettings, TArray<FCompressedImage2D>& OutCompressedImages ) const override`
- L268 _public function_ `bool SetTiling( const FTextureBuildSettings& BuildSettings, TSharedPtr<FTilerSettings>& TilerSettings, const TArray64<uint8>& ReorderedBlocks, uint32 NumBlocks ) const override`
- L280 _public function_ `void ReleaseTiling(const FTextureBuildSettings& BuildSettings, TSharedPtr<FTilerSettings>& TilerSettings) const override`
- L289 _public function_ `virtual FCbObject ExportGlobalFormatConfig(const FTextureBuildSettings& BuildSettings) const override`
- L322 _protected member_ `const FString FormatPrefix;` — Prefix put before all formats from parent formats
- L325 _protected member_ `TArray<FName> BaseFormats;` — List of base formats that. Combined with FormatPrefix, this contains all formats this can handle
- L328 _protected member_ `TArray<FName> SupportedFormatsCached;` — List of combined BaseFormats with FormatPrefix.

### `Source/Developer/TextureFormat/Public/Interfaces/ITextureFormat.h` (Public)


#### struct `FTextureFormatCompressorCaps`  
`struct FTextureFormatCompressorCaps`  
_L17-29_
- desc: Structure for texture format compressor capabilities. This struct is deprecated - FEncodedTextureExtendedData is used instead.
- L19 _public function_ `FTextureFormatCompressorCaps() : MaxTextureDimension_DEPRECATED(TNumericLimits<uint32>::Max()) , NumMipsInTail_DEPRECATED(0) , ExtData_DEPRECATED(0)`
- L26 _public member_ `uint32 MaxTextureDimension_DEPRECATED;` — MaxTextureDimension is never set, remove it
- L27 _public member_ `uint32 NumMipsInTail_DEPRECATED;`
- L28 _public member_ `uint32 ExtData_DEPRECATED;`

#### struct `FTextureEngineParameters`  
`struct FTextureEngineParameters`  
_L42-47_
- desc: Holds various engine configuration parameters that can affect the output of a build but should generally be constant across all texture builds. These are sourced from CVars and enums/defines that aren't necessarily visible in all modules. This structure serializes to compact binary only writing if the values are not default, so changing the default initialization without changing the texture build version/guid can result in build mismatch. Created via GenerateTextureEngineParameters() in TextureDerivedDataTask.cpp.
- L44 _public member_ `bool bEngineSupportsVolumeTextureStreaming = true;` — GEngineSupportsVolumeTextureStreaming
- L45 _public member_ `bool bEngineSupportsTexture2DArrayStreaming = true;` — GEngineSupportsTexture2DArrayStreaming
- L46 _public member_ `int32 NumInlineDerivedMips = 7;` — NUM_INLINE_DERIVED_MIPS

#### struct `FEncodedTextureExtendedData`  
`struct FEncodedTextureExtendedData`  
_L73-100_
- desc: Extra data for an encoded texture. This is filled out by platform "child" formats that can potentially tile or otherwise reorganize the mip data for use on the target platform. For platforms that use bog standard "linear" texture data, this is mostly zeroes, but must still be "Valid" data returned by the GetExtendedDataForTexture - notably the MipSizesInBytes.
- L76 _public member_ `static constexpr int32 MAX_TEXTURE_MIP_COUNT=15;` — Copied from RHIDefinitions.h - we expose here to avoid the include.
- L80 _public member_ `int32 NumMipsInTail = 0;` — Some platforms group the smallest mips in to a single bulk chunk of data. This is nonzero in such cases and the MipSizesInBytes array is truncated.
- L83 _public member_ `uint32 ExtData = 0;` — ExtData is metadata the tiler passes through to the runtime.
- L86 _public member_ `bool bIsTiled = false;` — If true, the mip data can't be assumed to be linear.
- L89 _public member_ `bool bSensitiveToLODBias = false;` — If true, this texture might change layouts if top mips are striped (i.e. LODBias is not zero).
- L92 _public member_ `int8 LODBiasIfSensitive = 0;` — If bSensitiveToLODBias is set, this is the LODBias for this layout.
- L99 _public member_ `TArray<uint64, TInlineAllocator<MAX_TEXTURE_MIP_COUNT>> MipSizesInBytes;` — All generators of this structure are required to fill this structure out even if they are default linear sizes. For non linear textures these are not trivially calculatable. Also note that if the texture is sensitive to LODBias with respect to tiling, the indeces in this array that are for mips that would be stripped are present but should be ignored as they don't represent anything we can accurately calculate.

#### struct `FEncodedTextureDescription`  
`struct FEncodedTextureDescription`  
_L202-438_
- desc: Everything necessary to know the memory layout for an encoded untiled unpacked texture (i.e. enough information to describe the texture entirely to a PC hardware API). Once a texture gets tiled or gets a packed mip tail, FEncodedTextureEncodedData is additionally required to know the memory layout.
- L204 _public member_ `int32 TopMipSizeX;`
- L205 _public member_ `int32 TopMipSizeY;`
- L206 _public member_ `int32 TopMipVolumeSizeZ;` — This is 1 if bVolumeTexture == false
- L207 _public member_ `int32 ArraySlices;` — This is 1 if bTextureArray == false (including cubemaps)
- L208 _public member_ `EPixelFormat PixelFormat;`
- L209 _public member_ `uint8 NumMips;`
- L210 _public member_ `bool bCubeMap;`
- L211 _public member_ `bool bTextureArray;`
- L212 _public member_ `bool bVolumeTexture;`
- L214 _public typedef_ `typedef TArray<FSharedBuffer, TInlineAllocator<FEncodedTextureExtendedData::MAX_TEXTURE_MIP_COUNT>> FSharedBufferMipChain;`
- L215 _public typedef_ `typedef TArray<FUniqueBuffer, TInlineAllocator<FEncodedTextureExtendedData::MAX_TEXTURE_MIP_COUNT>> FUniqueBufferMipChain;`
- L217 _public function_ `bool operator==(const FEncodedTextureDescription& OtherTextureDescription) const`
- L234 _public function_ `int32 GetRHIStyleSizeZ(int32 InMipIndex) const` — This returns the SizeZ value that is expected by RHI streamable texture structures. It is only used by non-cube texture arrays and volumes, however the cubemap array and cubemap values need to be consistent as they are persisted and would cause a DDC determinism issue. (note that cubemap arrays are handled in the bTextureArray path).
- L241 _public function_ `int32 GetNumSlices_WithDepth(int32 InMipIndex) const` — Returns the slice count for usage cases/platform that expect slice count to include volume texture depth. InMipIndex only affects volume textures.
- L261 _public function_ `int32 GetNumSlices_NoDepth() const` — Returns the slice count for usage cases/platforms that expect slice count to only include cubemap/array slices.
- L278 _public function_ `int32 GetMipWidth(int32 InMipIndex) const`
- L282 _public function_ `int32 GetMipHeight(int32 InMipIndex) const`
- L287 _public function_ `int32 GetMipDepth(int32 InMipIndex) const` — Always 1 unless volume texture.
- L291 _public function_ `static int32 GetMipWidth(int32 InTextureWidth, int32 InMipIndex)`
- L295 _public function_ `static int32 GetMipHeight(int32 InTextureHeight, int32 InMipIndex)`
- L299 _public function_ `static int32 GetMipDepth(int32 InTextureDepth, int32 InMipIndex, bool bInVolumeTexture)`
- L306 _public function_ `FIntVector3 GetMipDimensions(int32 InMipIndex) const` — Returns the size of the mip at the given index. Z is 1 unless it's a volume texture.
- L316 _public function_ `uint64 GetMipSizeInBytes(int32 InMipIndex) const` — Returns the byte size of the unpacked/tiled mip. For mip chains that are packed or tiled, use FEncodedTextureExtendedData::MipSizesInBytes.
- L324 _public function_ `uint64 GetMipSliceSizeInBytes(int32 InMipIndex) const` — As GetMipSizeInBytes, except for a single slice of the mip.
- L331 _public function_ `uint64 GetMipSliceRowPitchBytes(int32 InMipIndex) const` — Returns the bytes necessary to get to the next row of the current mip
- L339 _public function_ `int32 GetNumStreamingMips(const FEncodedTextureExtendedData* InExtendedData, const FTextureEngineParameters& InEngineParameters) const` — This is the number of streaming mips without any restrictions associated with block size alignment. It's used primarily for where mips go in the DDC.
- L346 _public function_ `int32 GetNumNonStreamingMips(const FEncodedTextureExtendedData* InExtendedData, const FTextureEngineParameters& InEngineParameters)` — This is the number of nonstreaming mips that works for cooking and thus is aware of block alignment concerns for runtime use. Only call this if streaming is possible.
- L353 _public function_ `void GetLinearMipSizesInBytes(TArray<uint64, TInlineAllocator<FEncodedTextureExtendedData::MAX_TEXTURE_MIP_COUNT>>& OutMipSizesInBytes) const` — Fills out the given array with linear mip sizes for the number of mips this texture has. These sizes are only valid if the texture is linear and has no packed mip tail (i.e. no associated FEncodedTextureExtendedData).
- L372 _public function_ `void GetEncodedMipIterators(const FEncodedTextureExtendedData* InExtendedData, int32& OutMipTailIndex, int32& OutMipsInTail) const` — Convenience function for iterating over the encoded mips when you need to know how many mips are represented. Use as: for (int32 EncodedMipIndex = 0; EncodedMipIndex < OutMipTailIndex + 1; EncodedMipIndex++) { int32 MipsRepresentedThisIndex = EncodedMipIndex == OutMipTailIndex ? OutMipsInTail : 1; } This handles mip chains whether or not they have packed mip tails. Note GetNumEncodedMips() == OutMipTailIndex + 1
- L386 _public function_ `int32 GetNumEncodedMips(const FEncodedTextureExtendedData* InExtendedData) const` — Returns the number of mips that actually carry bulk data for this texture. Nominally the number of total mips, however some platforms have packed mip tails, which means they still have the total number of mips, but the last several are all bundled together for memory savings.
- L397 _public function_ `FEncodedTextureDescription GetDescriptionForMipLevel(const FEncodedTextureExtendedData* InExtendedData, int32 InMipIndex) const` — Returns the description _for the single mip level_ (i.e. no further mips)
- L418 _public function_ `FEncodedTextureDescription RemoveTopMips(const FEncodedTextureExtendedData* InExtendedData, int32 InRemoveCount) const`

#### class `ITextureTiler`  
`class ITextureTiler`  
_L444-478_
- desc: Interface for platform formats that consume a linear, unpacked texture that an be built on a host platform (e.g. windows) and then tile/pack it as necessary.
- L458 _public prototype_ `virtual FEncodedTextureExtendedData GetExtendedDataForTexture(const FEncodedTextureDescription& InTextureDescription, int8 InLODBias) const = 0;` — Generate and return any out-of-band data that needs to be saved for a given encoded texture description and LODBias.
- L460 _public prototype_ `virtual const FUtf8StringView GetBuildFunctionName() const = 0;`
- L461 _public prototype_ `virtual const FUtf8StringView GetDetileBuildFunctionName() const = 0;`
- L468 _public prototype_ `virtual FSharedBuffer ProcessMipLevel(const FEncodedTextureDescription& InTextureDescription, const FEncodedTextureExtendedData& InExtendedData, TArrayView<FMemoryView> InLinearSurfaces, int32 InMipIndex) const = 0;` — InLinearSurfaces must have the necessary input mips for the mip level - i.e. for a packed mip tail, InMipIndex is the index of the top mip of the tail, and InLinearSurfaces must have all the source mips for the entire tail.
- L474 _public function_ `virtual bool DetileMipChain(FEncodedTextureDescription::FUniqueBufferMipChain& OutLinearMips, FEncodedTextureDescription::FSharedBufferMipChain InTiledMips, const FEncodedTextureDescription& InTextureDescription, const FEncodedTextureExtendedData& InExtendedData, const FString& InTexturePathName) const` — Given a tiled mip chain, detile in to OutLinearMips. For mip tails, OutLinearMips.Num may end up larger than InTiledMips.Num. Mips have all slices concatenated together.

#### class `ITextureFormat`  
`class ITextureFormat`  
_L487-841_
- desc: Interface for texture compression modules. Note that if you add any virtual functions to this, they almost certainly need to be plumbed through ChildTextureFormat! This is why the Format is passed around - ChildTextureFormat needs it to resolve to the base format.
- L496 _public function_ `virtual bool AllowParallelBuild() const` — Checks whether this texture format can compress in parallel. @return true if parallel compression is supported, false otherwise.
- L506 _public prototype_ `virtual FName GetEncoderName(FName Format) const = 0;` — Return the name of the encoder used for the given format. Used for debugging and UI.
- L512 _public function_ `virtual bool SupportsEncodeSpeed(FName Format, const ITargetPlatformSettings* TargetPlatform) const` — Exposes whether the format supports the fast/final encode speed switching in project settings. Needs the Format so that we can thunk through the child texture formats correctly.
- L520 _public function_ `virtual bool CanAcceptNonF32Source(FName Format) const` — @returns true in case Compress can handle other than RGBA32F image formats
- L526 _public function_ `virtual const FUtf8StringView GetDecodeBuildFunctionName() const` — If the format can decode to RGBA8/RGBA16F, this is the IBuild function name for it.
- L537 _public prototype_ `virtual uint16 GetVersion( FName Format, const FTextureBuildSettings* BuildSettings = nullptr ) const = 0;` — Gets the current version of the specified texture format. @param Format The format to get the version for. @return Version number.
- L551 _public function_ `virtual FString GetDerivedDataKeyString(const FTextureBuildSettings& InBuildSettings, int32 InMipCount, const FIntVector3& InMip0Dimensions) const` — Gets an optional derived data key string, so that the compressor can rely upon the number of mips, size of texture, etc, when compressing the image @param InBuildSettings Reference to the build settings we are compressing with. @param InMipCount Mip count of the physical texture that will be built - 0 for virtual textures. @param InMip0Dimensions Mip width/height/slices of the physical texture that will be built - 0s for virtual textures. @return A string that will be used with the DDC, the string should be in the format "<DATA>_"
- L561 _public prototype_ `virtual void GetSupportedFormats( TArray<FName>& OutFormats ) const = 0;` — Gets the list of supported formats. @param OutFormats Will hold the list of formats.
- L569 _public function_ `virtual FTextureFormatCompressorCaps GetFormatCapabilities() const` — `UE_DEPRECATED(5.1, "Hasn't been used in a while.")` — Gets the capabilities of the texture compressor. @param OutCaps Filled with capability properties of texture format compressor.
- L577 _public function_ `virtual FTextureFormatCompressorCaps GetFormatCapabilitiesEx(const FTextureBuildSettings& BuildSettings, uint32 NumMips, const struct FImage& ExampleImage, bool bImageHasAlphaChannel) const` — `UE_DEPRECATED(5.1, "Use GetExtendedDataForTexture instead to get the same information without the actual image bits.")` — Gets the capabilities of the texture compressor. @param OutCaps Filled with capability properties of texture format compressor.
- L586 _public function_ `virtual EPixelFormat GetPixelFormatForImage(const FTextureBuildSettings& BuildSettings, const struct FImage& Image, bool bImageHasAlphaChannel) const` — `UE_DEPRECATED(5.1, "Use GetEncodedPixelFormat(BuildSettings, bImageHasAlphaChannel) instead")` — Calculate the final/runtime pixel format for this image on this platform
- L598 _public function_ `virtual EPixelFormat GetEncodedPixelFormat(const FTextureBuildSettings& InBuildSettings, bool bInImageHasAlphaChannel) const` — Returns what the compressed pixel format will be for a given format and the given settings. bInImageHasAlphaChannel is whether or not to treat the source image format as having an alpha channel, independent of whether or not it actually has one.
- L608 _public function_ `[[nodiscard]] virtual FEncodedTextureExtendedData GetExtendedDataForTexture(const FEncodedTextureDescription& InTextureDescription, int8 InLODBias) const` — Generate and return any out-of-band data that needs to be saved for a given encoded texture description. This is for textures that have been transformed in some way for a platform. LODBias is needed because in some cases the tiling changes based on the top mip actually given to the hardware.
- L616 _public function_ `virtual bool CanDecodeFormat(EPixelFormat InPixelFormat) const` — Return true if this format can decode the given pixel format to one of the ERawImageFormats.
- L621 _public function_ `virtual bool DecodeImage(int32 InSizeX, int32 InSizeY, int32 InNumSlices, EPixelFormat InPixelFormat, bool bInSRGB, const FName& InTextureFormatName, FSharedBuffer InEncodedData, FImage& OutImage, FStringView InTextureName) const` — Decodes an image encoded as a EPixelFormat into something encoded as a ERawImageFormat. This will only be called if CanDecodeFormat returns true.
- L640 _public prototype_ `virtual bool CompressImage( const FImage& Image, const FTextureBuildSettings& BuildSettings, const FIntVector3& InMip0Dimensions, int32 InMip0NumSlicesNoDepth, int32 InMipIndex, int32 InMipCount, FStringView DebugTexturePathName, bool bImageHasAlphaChannel, struct FCompressedImage2D& OutCompressedImage ) const = 0;` — Compresses a single image. @param Image The input image.  Image.RawData may be freed or modified by CompressImage; do not use after calling this. @param BuildSettings Build settings. @param InMip0Dimensions X/Y = Width/Height; Z = 1 unless volume texture, then its depth @param InMip0NumSlicesNoDepth see FEncodedTextureDescription::NumSlices_NoDepth() @param InMipIndex Mip index of current image in the overall texture. @param InMipCount Total mips this texture will be created with. @param DebugTexturePathName The path name of the texture we are building, for debug logging/filtering/dumping. @param bImageHasAlphaChannel true if the image has a non-white alpha channel. @param OutCompressedMip The compressed image. @returns true on success, false otherwise.
- L668 _public function_ `virtual bool CompressImageEx( const FImage* Images, const uint32 NumImages, const FTextureBuildSettings& BuildSettings, const FIntVector3& InMip0Dimensions, int32 InMip0NumSlicesNoDepth, int32 InMipIndex, int32 InMipCount, FStringView DebugTexturePathName, bool bImageHasAlphaChannel, uint32 ExtData, FCompressedImage2D& OutCompressedImage) const` — Compress an image (or images for a miptail) into a single mip blob. @param Images The input image(s).  Image.RawData may be freed or modified by CompressImage; do not use after calling this. @param NumImages The number of images (for a miptail, this number should match what was returned in GetExtendedDataForTexture, mostly used for verification) @param BuildSettings Build settings. @param InMip0Dimensions X/Y = Width/Height; Z = 1 unless volume texture, then its depth @param InMip0NumSlicesNoDepth see FEncodedTextureDescription::NumSlices_NoDepth() @param InMipIndex Mip index of current image in the overall texture. @param InMipCount Total mips this texture will be created with. @param DebugTexturePathName The path name of the texture we are building, for debug logging/filtering/dumping. @param bImageHasAlphaChannel true if the image has a non-white alpha channel. @param ExtData Extra data that the format may want to have passed back in to each compress call (makes the format class be stateless) @param OutCompressedMip The compressed image. @returns true on success, false otherwise.
- L711 _public function_ `virtual bool CompressImageTiled( const FImage* Images, uint32 NumImages, const FTextureBuildSettings& BuildSettings, FStringView DebugTexturePathName, bool bImageHasAlphaChannel, TSharedPtr<FTilerSettings>& TilerSettings, struct FCompressedImage2D& OutCompressedImage) const` — `UE_DEPRECATED(5.6, "Tiling compressors will no longer be supported; compress the mip entirely via CompressImage(Ex) and UE will tile the image afterwards")` — Compress an image (or images for a miptail) into a single mip blob with device-specific tiling. @param Image The input image.  May be freed! @param BuildSettings Build settings. @param bImageHasAlphaChannel true if the image has a non-white alpha channel. @param DebugTexturePathName The path name of the texture we are building, for debug logging/filtering/dumping. @param OutCompressedMip The compressed image. @param Tiler The tiler settings. @returns true on success, false otherwise.
- L732 _public function_ `virtual bool SupportsTiling() const` — `UE_DEPRECATED(5.6, "Tiling compressors will no longer be supported; compress the mip entirely via CompressImage(Ex) and UE will tile the image afterwards")` — Whether device-specific tiling is supported by the compressor. @param BuildSettings Build settings. @returns true if tiling is supported, false if it must be done by the caller
- L748 _public function_ `virtual bool PrepareTiling( const FImage* Images, const uint32 NumImages, const FTextureBuildSettings& BuildSettings, bool bImageHasAlphaChannel, TSharedPtr<FTilerSettings>& OutTilerSettings, TArray<FCompressedImage2D>& OutCompressedImage ) const` — `UE_DEPRECATED(5.6, "Tiling compressors will no longer be supported; compress the mip entirely via CompressImage(Ex) and UE will tile the image afterwards")` — Prepares to compresses a single image with tiling. The result OutTilerSettings is used by SetTiling and CompressImageTiled. @param Image The input image. @param BuildSettings Build settings. @param bImageHasAlphaChannel true if the image has a non-white alpha channel. @param OutTilerSettings The tiler settings that will be used by CompressImageTiled and SetTiling. @param OutCompressedImage The image to tile. @returns true on success, false otherwise.
- L771 _public function_ `virtual bool SetTiling( const FTextureBuildSettings& BuildSettings, TSharedPtr<FTilerSettings>& TilerSettings, const TArray64<uint8>& ReorderedBlocks, uint32 NumBlocks ) const` — `UE_DEPRECATED(5.6, "Tiling compressors will no longer be supported; compress the mip entirely via CompressImage(Ex) and UE will tile the image afterwards")` — Sets the tiling settings after device-specific tiling has been performed. @param BuildSettings Build settings. @param TilerSettings The tiler settings produced by PrepareTiling. @param ReorderedBlocks The blocks that have been tiled. @param NumBlocks The number of blocks. @returns true on success, false otherwise.
- L789 _public function_ `virtual void ReleaseTiling(const FTextureBuildSettings& BuildSettings, TSharedPtr<FTilerSettings>& TilerSettings) const` — `UE_DEPRECATED(5.6, "Tiling compressors will no longer be supported; compress the mip entirely via CompressImage(Ex) and UE will tile the image afterwards")` — Cleans up the FTilerSettings object once it is finished. @param BuildSettings Build settings. @param TilerSettings The tiler settings object to release.
- L803 _public function_ `virtual FCbObject ExportGlobalFormatConfig(const FTextureBuildSettings& BuildSettings) const` — Obtains the current global format config object for this texture format. This is only ever called during task creation - never in a build worker (FormatConfigOverride is empty) @param BuildSettings Build settings. @returns The current format config object or an empty object if no format config is defined for this texture format.
- L811 _public function_ `virtual FString GetAlternateTextureFormatPrefix() const` — If this is an Alternate Texture Format, return the prefix to apply
- L816 _public function_ `virtual const FChildTextureFormat* GetChildFormat() const`
- L825 _public function_ `virtual FName GetLatestSdkVersion() const` — Identify the latest sdk version for this texture encoder (note the SdkVersion is different than the TextureFormat Version)
- L831 _public function_ `virtual bool UsesTaskGraph() const` — `UE_DEPRECATED(5.0, "Legacy API - do not use")`
- L840 _public prototype_ `virtual ~ITextureFormat() = default;` — Virtual destructor.

#### struct `ITextureFormat::FTilerSettings`  
`struct FTilerSettings`  
_L695-697_

#### Free symbols / members of external scopes

- L49 _function_ `static bool GetStreamingDisabledForNonVirtualTextureProperties(bool bInCubeMap, bool bInVolumeTexture, bool bInTextureArray, const FTextureEngineParameters& InEngineParameters)`
- L122 _function_ `static int32 GetNumStreamingMipsDirect(int32 InNumMips, bool bInCubeMap, bool bInVolumeTexture, bool bInTextureArray, const FEncodedTextureExtendedData* InExtendedData, const FTextureEngineParameters& InEngineParameters)` — Calculate the number of streaming mips for the given set of texture properties. This must work off of properties that can (eventually) be calculated without running a full texture build. Texture mips are split in to two large groups: streaming and non-streaming (aka "inline"). Note that "inline" is sometimes used as a verb to mean "load off of disk and place in our bulk data". "Inline" textures are loaded with the texture asset, and streaming textures are loaded on demand. Generally, 7 of the smallest mips are inlined, however some platforms pack a lot of mips in to a single allocation ("packed mip tail" = NumMipsInTail). Those mips must all be inlined. This function is used primarily for determining where to put mips in the DDC. Runtime inlining is subject to further constraints and must use the GetNumNonStreamingMipsDirect() function. InNumMips			    The total mips that the texture contains. InExtendedData	    If the texture is being built for a platform that provides extended data, pass it here. For platforms that don't need it (i.e. PC), this should be nullptr. InEngineParameters    Holds a vairety of engine configuration constants, create with GenerateEngineParameters()
- L157 _function_ `static int32 GetNumNonStreamingMipsDirect(int32 InNumMips, int32 InTopMipSizeX, int32 InTopMipSizeY, EPixelFormat InPixelFormat, int32 InNumMipsInTail, int32 InNumInlineDerivedMips)` — Return how many mips need to be inlined for the given texture properties. This pays attention to runtime size restrictions and should be used for serializing cooked data. InNumMips, InTopMipSizeX, InTopMipSizeY must all be sizes _before_ any LOD stripping during cook, with the expectation that the returned value is verified against the remaining mip count after LOD stripping. This function is not valid if streaming is disabled for the texture.

### `Source/Developer/TextureFormat/Public/Interfaces/ITextureFormatManagerModule.h` (Public)


#### class `ITextureFormatManagerModule`  
`class ITextureFormatManagerModule : public IModuleInterface`  
_L11-54_
- inherits: `IModuleInterface`
- desc: Module for the texture format manager
- L22 _public prototype_ `virtual const class ITextureFormat* FindTextureFormat( FName Name ) = 0;` — Finds a texture format with the specified name. Safe to call from any thread. @param Name Name of the format to find. @return The texture format, or nullptr if not found.
- L33 _public prototype_ `virtual const class ITextureFormat* FindTextureFormatAndModule( FName Name, FName& OutModuleName, class ITextureFormatModule*& OutModule ) = 0;` — Finds a texture format with the specified name and provides information about the module it came from. Safe to call from any thread. @param Name Name of the format to find. @param OutModuleName Name of the module that the found format came from, or unmodified if not found. @param OutModule Interface of the module that the found format came from, or unmodified if not found. @return The texture format, or nullptr if not found.
- L40 _public prototype_ `virtual TArray<const class ITextureFormat*> GetAllTextureFormats() = 0;` — Returns the list of all ITextureFormats that were located in DLLs. @return Collection of texture formats.
- L48 _public function_ `void Invalidate()` — `UE_DEPRECATED(5.6, "No longer necessary to call")` — Invalidates the texture format manager module. This is no longer necessary as all work is done in response to broadcast plugin/module discovery messages.
- L53 _public prototype_ `~ITextureFormatManagerModule() = default;` — Virtual destructor.

### `Source/Developer/TextureFormat/Public/Interfaces/ITextureFormatModule.h` (Public)


#### class `ITextureFormatModule`  
`class ITextureFormatModule : public IModuleInterface`  
_L13-35_
- inherits: `IModuleInterface`
- desc: Interface for texture format modules.
- L23 _public prototype_ `virtual ITextureFormat* GetTextureFormat() = 0;` — Gets the texture format. @return The texture format interface.
- L29 _public prototype_ `virtual bool CanCallGetTextureFormats() = 0;` — Will this TextureFormat call back to Managermodule GetTextureFormats ?
- L34 _public prototype_ `~ITextureFormatModule() = default;` — Virtual destructor.

### `Source/Developer/TextureFormat/Public/TextureFormatManager.h` (Public)


#### Free symbols / members of external scopes

- L10 _function_ `inline ITextureFormatManagerModule* GetTextureFormatManager()` — Return the Texture Format Manager interface, if it is available, otherwise return nullptr.
- L23 _function_ `inline ITextureFormatManagerModule& GetTextureFormatManagerRef()` — Return the Texture Format Manager interface, fatal error if it is not available.
