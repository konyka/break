# Runtime / ImageCore

- module root: `Source/Runtime/ImageCore`
- headers: 6; symbols: 321
- symbol kinds: class=1, enum=8, enumerator=53, function=93, macro=5, member=40, namespace=9, prototype=100, struct=10, typedef=2
- PrivateDependencyModuleNames: CoreUObject, stb_image_resize2
- PrivateIncludePathModuleNames: Engine
- PublicDependencyModuleNames: Core

### `Source/Runtime/ImageCore/Public/DDSFile.h` (Public)


#### enum `UE::DDS::EDXGIFormat`  
`enum class EDXGIFormat`  
_L145-154_
- desc: Complete list of formats
- L150 _public enumerator_ `UE_DXGI_FORMAT_LIST #undef RGBFMT #undef BCNFMT #undef ODDFMT`

#### enum `UE::DDS::EDDSFormatVersion`  
`enum class EDDSFormatVersion`  
_L157-162_
- desc: What version of DDS file to write
- L159 _public enumerator_ `Auto` — Write as D3D9-version DDS if possible without losing metadata like sRGB status, D3D10 otherwise
- L160 _public enumerator_ `D3D9` — Try really hard to write a D3D9-format .DDS file (the more widely supported version) even when doing so loses some information
- L161 _public enumerator_ `D3D10` — Always write a D3D10-format .DDS file

#### enum `UE::DDS::EDDSReadMipMode`  
`enum class EDDSReadMipMode`  
_L165-170_
- desc: Mip data read modes
- L167 _public enumerator_ `Full`
- L168 _public enumerator_ `HeaderOnly`
- L169 _public enumerator_ `HeaderWithMipInfo`

#### enum `UE::DDS::EDDSError`  
`enum class EDDSError`  
_L173-186_
- desc: Error codes
- L175 _public enumerator_ `OK` — No error
- L176 _public enumerator_ `Ok = OK`
- L177 _public enumerator_ `OutOfMemory` — Out of memory/allocation failure while reading
- L178 _public enumerator_ `NotADds` — No valid DDS header found
- L179 _public enumerator_ `NotADDS = NotADds`
- L180 _public enumerator_ `BadResourceDimension` — Resource not 1D, 2D or 3D
- L181 _public enumerator_ `BadPixelFormat` — Malformed or unsupported pixel format
- L182 _public enumerator_ `BadImageDimension` — Image dimensions (width, height, depth, array size) outside supported range
- L183 _public enumerator_ `BadMipmapCount` — Invalid mipmap count for given image dimensions
- L184 _public enumerator_ `BadCubemap` — Cubemap has non-square faces, non-1 depth, or unsupported array count
- L185 _public enumerator_ `IoError` — General I/O error

#### enum `UE::DDS::EChannelOrder`  
`enum class EChannelOrder`  
_L189-193_
- desc: Channel ordering for 8-bit formats
- L191 _public enumerator_ `RGBA`
- L192 _public enumerator_ `BGRA`

#### struct `UE::DDS::FDDSMip`  
`struct FDDSMip`  
_L196-205_
- desc: One of these for each mip of a DDS
- L198 _public member_ `uint32 Width, Height, Depth;`
- L198 _public member_ `uint32 Width, Height, Depth;`
- L198 _public member_ `uint32 Width, Height, Depth;`
- L201 _public member_ `int64 RowStride;` — Note: pixels in DDS data must be densely packed, they exist for ease of addressing but you can't represent strided data in this form.
- L202 _public member_ `int64 SliceStride;` — Bytes in one 2d slice of the mip, equal to DataStride for 2D textures.
- L203 _public member_ `int64 DataSize;`
- L204 _public member_ `uint8* Data;` — just raw bytes; interpretation as per DXGIFormat in parent FDDSFile

#### struct `UE::DDS::FDDSFile`  
`struct FDDSFile`  
_L227-333_
- desc: Metadata structure for a DDS file, with access pointers for the raw texture data (i.e. unconverted from the DXGI format). Can be used for loading or saving a dds file. For saving, general structure is: { dds = FDDSFile::CreateEmpty[2D](...) copy data for each mip/array: for (mips) memcpy(dds->mips[idx].data, mip_data, mip_size); Ar = IFileManager::Get().CreateFileWriter(filename); dds->Serialize(Ar); delete dds; Ar->Close() delete Ar; }
- L229 _public member_ `int32 Dimension=0;` — 1, 2 or 3.
- L230 _public member_ `uint32 Width=0;`
- L231 _public member_ `uint32 Height=0;`
- L232 _public member_ `uint32 Depth=0;`
- L233 _public member_ `uint32 MipCount=0;`
- L237 _public member_ `uint32 ArraySize=0;` — Array size here uses the conventions as in the D3D runtime, which means an array of N cubemaps has an array size of 6N (one element per face).
- L238 _public member_ `EDXGIFormat DXGIFormat=EDXGIFormat::UNKNOWN;`
- L239 _public member_ `uint32 CreateFlags=0;`
- L244 _public member_ `TArray<FDDSMip> Mips;` — Mips are ordered starting from mip 0 (full-size texture) decreasing in size; for arrays, we store the full mip chain for one array element before advancing to the next array element, and have (ArraySize * MipCount) mips total.
- L250 _public member_ `TArray64<uint8> MipRawData;` — When we allocate the mips ourselves, we keep all storage together in a single allocation, namely this one, and the mips point into it. With CREATE_FLAG_NO_MIP_STORAGE_ALLOC, we don't own the underlying memory and this array is unused.
- L263 _public prototype_ `EDDSError WriteDDS(TArray64<uint8>& OutDDS, EDDSFormatVersion InFormatVersion=EDDSFormatVersion::D3D10);` — Write DDS-format data to memory. This produces a memory image of a DDS file. Automatic format selection rules used are: - D3D9 DDS does not support 1D or array textures directly, so these always write as D3D10 - The pixel format must be a "common" D3D9 format (more obscure formats can be used for D3D9 writing when InFormatVersion is D3D9, but "Auto" sticks with a restricted subset) - For 8-bit pixel formats, the format must be non-sRGB. The latter is somewhat arbitrary. D3D9 DDS files don't store whether pixels for a texture are meant to be interpreted as sRGB or not. This reader treats the resulting formats as non-sRGB UNORM, so the writer does the same for symmetry.
- L268 _public member_ `static constexpr uint32 MAX_MIPS_SUPPORTED = 20;` — 20 mips means 512k x 512k pixels max, should be sufficient for now. It's 512k not 1M because the final 1x1 pixel mip counts; i.e. a mip chain from 1048576x1048576 down to 1x1 has 21 mips!
- L283 _public prototype_ `static FDDSFile* CreateEmpty(int32 InDimension, uint32 InWidth, uint32 InHeight, uint32 InDepth, uint32 InMipCount, uint32 InArraySize, EDXGIFormat InFormat, uint32 InCreateFlags, EDDSError *OutError=nullptr);` — Create an empty DDS structure (for writing DDS files typically) InDimension is [1,3] (1D,2D,3D) InWidth/InHeight are for the top mip. Cubemaps must be square. InDepth is only used for 3D textures, must be 1 otherwise. InMipCount <= MAX_MIPS_SUPPORTED. InArraySize number of textures provided - must be multiple of 6 for cubemaps (CREATE_FLAG_CUBEMAP) Note for texture arrays the mip data pointers are expecting the entire mip chain for one texture before moving to the next On error, returns nullptr. If a non-null OutError is supplied, error information is written there.
- L286 _public prototype_ `static FDDSFile* CreateEmpty2D(uint32 InWidth, uint32 InHeight, uint32 InMipCount, EDXGIFormat InFormat, uint32 InCreateFlags, EDDSError* OutError=nullptr);` — Convenience version of the above to create a basic 2D texture with mip chain
- L289 _public prototype_ `EDDSError Validate() const;` — Sanity-check that all members make sense and return an error code.
- L292 _public prototype_ `bool IsValidTexture2D() const;` — Check if this DDS is usable in Unreal Texture types:
- L293 _public prototype_ `bool IsValidTextureCube() const;` — or cube array
- L294 _public prototype_ `bool IsValidTextureArray() const;`
- L295 _public prototype_ `bool IsValidTextureVolume() const;`
- L298 _public prototype_ `static FDDSFile* CreateFromDDSInMemory(const uint8* InDDS, int64 InDDSSize, EDDSError* OutError, bool bHeaderOnly);` — `UE_DEPRECATED(5.6, "This function is now deprecated, please use CreateFromDDSInMemory with EDDSReadMipMode instead.")`
- L304 _public prototype_ `static FDDSFile* CreateFromDDSInMemory(const uint8* InDDS, int64 InDDSSize, EDDSError* OutError=nullptr, EDDSReadMipMode InMipReadMode = EDDSReadMipMode::Full);` — Used for loading from a DDS file image in memory. On error, returns nullptr. If a non-null OutError is supplied, error information is written there.
- L307 _public prototype_ `static bool IsADDS(const uint8* InDDS, int64 InDDSSize);` — is this buffer a DDS ?
- L314 _public prototype_ `void ConvertChannelOrder(EChannelOrder InTargetOrder);` — For 8-bit UNorm formats, both RGBA and BGRA channel order variants exist and are popular. This function does the trivial conversion between the two, updating both the DXGI Format and the pixel data to do so. When the channel order is already correct or the pixel format is not one of the few formats that exist in both RGBA and BGRA variants, this function does nothing.
- L317 _public prototype_ `void ConvertRGBXtoRGBA();` — convert X alpha to A  and fill 255
- L322 _public prototype_ `bool GetMipImage(const FImageView & ToImage, int MipIndex) const;` — Blit pixels from DDS mip to Image return false if no pixel format conversion is supported ToImage is not allocated, must be pre-allocated and sized correctly
- L326 _public prototype_ `void FillMip(const FImageView & FromImage, int MipIndex);` — Fill DDS mip from Image Image must be of format DXGIFormatFromRawFormat
- L329 _public member_ `static constexpr uint32 CREATE_FLAG_NONE = 0;` — Bit flags
- L330 _public member_ `static constexpr uint32 CREATE_FLAG_CUBEMAP = 1;`
- L331 _public member_ `static constexpr uint32 CREATE_FLAG_NO_MIP_STORAGE_ALLOC = 2;` — Mip storage wasn't allocated by us and isn't owned by us, just pointing elsewhere.
- L332 _public member_ `static constexpr uint32 CREATE_FLAG_WAS_D3D9 = 4;` — Loaded from D3D9-format .DDS file, so whether 8-bit/channel formats are sRGB or not is largely guesswork

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_DXGI_FORMAT_LIST \` — This is supposed to be, as close as possible, the complete list of DXGI formats per those docs - the ODDFMTs we don't support for doing anything other than name, but we keep them here so we can stay in sync with the docs more easily. we support nope out on some of the more exotic formats entirely where they're unlikely to be useful for any assets fields: name, ID, bytes per unit (unit=1 texel for RGB, 1 block for BCN)
- L142 _namespace_ `namespace UE`
- L142 _namespace_ `namespace DDS` (scope `UE`)
- L147 _macro_ `#define RGBFMT(name,id,bypu) name = id,`
- L148 _macro_ `#define BCNFMT(name,id,bypu) name = id,`
- L149 _macro_ `#define ODDFMT(name,id) name = id,`
- L336 _prototype_ `const TCHAR *DXGIFormatGetName(EDXGIFormat InFormat);` (scope `UE::DDS`) — Returns the name of a DXGI format
- L339 _prototype_ `bool DXGIFormatIsSRGB(EDXGIFormat InFormat);` (scope `UE::DDS`) — Returns whether a given pixel format is sRGB
- L340 _prototype_ `bool DXGIFormatHasLinearAndSRGBForm(EDXGIFormat InFormat);` (scope `UE::DDS`)
- L343 _prototype_ `EDXGIFormat DXGIFormatRemoveSRGB(EDXGIFormat InFormat);` (scope `UE::DDS`) — Return the corresponding non-sRGB version of a pixel format if there is one
- L346 _prototype_ `EDXGIFormat DXGIFormatAddSRGB(EDXGIFormat InFormat);` (scope `UE::DDS`) — Return the corresponding sRGB version of a pixel format if there is one
- L348 _prototype_ `EDXGIFormat DXGIFormatFromRawFormat(ERawImageFormat::Type RawFormat,EGammaSpace GammaSpace);` (scope `UE::DDS`)
- L350 _prototype_ `ERawImageFormat::Type DXGIFormatGetClosestRawFormat(EDXGIFormat fmt, bool * pIsExactMatch = nullptr);` (scope `UE::DDS`)
- L353 _prototype_ `int64 GetDDSHeaderMaximalSize();` (scope `UE::DDS`) — note these sizes include the 4-byte magic word, unlike the older DDSLoader functions
- L354 _prototype_ `int64 GetDDSHeaderMinimalSize();` (scope `UE::DDS`)

### `Source/Runtime/ImageCore/Public/ImageCore.h` (Public)


#### enum `ERawImageFormat::Type`  
`enum Type : uint8`  
_L56-69_
- desc: Enumerates supported raw image formats. should map one-to-one with ETextureSourceFormat
- L58 _public enumerator_ `G8`
- L59 _public enumerator_ `BGRA8` — FColor
- L60 _public enumerator_ `BGRE8`
- L61 _public enumerator_ `RGBA16`
- L62 _public enumerator_ `RGBA16F` — FFloat16Color
- L63 _public enumerator_ `RGBA32F` — FLinearColor
- L64 _public enumerator_ `G16` — note G8/G16 = gray = replicate to 3 channels, R16F = just in red channel
- L65 _public enumerator_ `R16F`
- L66 _public enumerator_ `R32F`
- L67 _public enumerator_ `MAX` — used for validation checks < MAX = valid type.
- L68 _public enumerator_ `Invalid = 0xFF`

#### struct `FImageInfo`  
`struct FImageInfo`  
_L138-252_
- desc: FImageInfo describes a 2d pixel surface it can be used by FImage or FImageView
- L141 _public member_ `int32 SizeX = 0;` — Width of the image.
- L144 _public member_ `int32 SizeY = 0;` — Height of the image.
- L147 _public member_ `int32 NumSlices = 0;` — Number of image slices.
- L150 _public member_ `ERawImageFormat::Type Format = ERawImageFormat::BGRA8;` — Format in which the image is stored.
- L153 _public member_ `EGammaSpace GammaSpace = EGammaSpace::sRGB;` — The gamma space the image is stored in.
- L155 _public function_ `FImageInfo()`
- L157 _public function_ `FImageInfo(int32 InSizeX, int32 InSizeY, int32 InNumSlices, ERawImageFormat::Type InFormat, EGammaSpace InGammaSpace) : SizeX(InSizeX) , SizeY(InSizeY) , NumSlices(InNumSlices) , Format(InFormat) , GammaSpace(InGammaSpace)`
- L166 _public function_ `inline bool operator == (const FImageInfo & rhs) const`
- L176 _public function_ `inline bool IsImageInfoValid() const`
- L185 _public function_ `inline bool IsGammaCorrected() const`
- L195 _public function_ `inline int64 GetBytesPerPixel() const` — Gets the number of bytes per pixel. @return Bytes per pixel.
- L200 _public function_ `inline int64 GetNumPixels() const`
- L205 _public function_ `inline int64 GetImageSizeBytes() const`
- L210 _public function_ `inline int64 GetSliceNumPixels() const`
- L215 _public function_ `inline int64 GetSliceSizeBytes() const`
- L220 _public function_ `inline int64 GetWidth() const`
- L221 _public function_ `inline int64 GetHeight() const`
- L223 _public function_ `inline int64 GetStrideBytes() const`
- L225 _public function_ `inline EGammaSpace GetGammaSpace() const`
- L234 _public function_ `inline int64 GetPixelOffsetBytes(int32 X,int32 Y,int32 Slice = 0) const` — get offset of a pixel from the base pointer, in bytes
- L249 _public prototype_ `void ImageInfoToCompactBinary(class FCbObject& OutObject) const;`
- L251 _public prototype_ `bool ImageInfoFromCompactBinary(const FCbObject& InObject);` — Overwrites the current info with the object's info/

#### struct `FImageView`  
`struct FImageView : public FImageInfo`  
_L263-410_
- inherits: `FImageInfo`
- desc: Image functions should take an FImageView as input and output to FImage FImageView can point at an FImage or any pixel surface FImage hold allocations.  FImageView is non-owning.  Make sure the memory pointed at is not freed.
- L265 _public member_ `void * RawData = nullptr;`
- L267 _public function_ `FImageView()`
- L269 _public function_ `FImageView(const FImageInfo & InInfo,void * InRawData) : FImageInfo(InInfo), RawData(InRawData)`
- L274 _public function_ `FImageView(const FColor * InColors,int32 InSizeX,int32 InSizeY,EGammaSpace InGammaSpace = EGammaSpace::sRGB)` — Make an FImageView pointing at an array of FColor pixels as BGRA8 (does not copy the input, points at it)
- L285 _public function_ `FImageView(const FLinearColor * InColors,int32 InSizeX,int32 InSizeY)` — Make an FImageView pointing at an array of FLinearColor pixels as RGBA32F (does not copy the input, points at it)
- L296 _public function_ `FImageView(const FFloat16Color * InColors,int32 InSizeX,int32 InSizeY)` — Make an FImageView pointing at an array of FLinearColor pixels as RGBA16F (does not copy the input, points at it)
- L306 _public function_ `FImageView(void * InData,int32 InSizeX, int32 InSizeY, int32 InNumSlices, ERawImageFormat::Type InFormat, EGammaSpace InGammaSpace) : FImageInfo(InSizeX,InSizeY,InNumSlices,InFormat,InGammaSpace), RawData(InData)`
- L312 _public function_ `FImageView(void * InData,int32 InSizeX, int32 InSizeY, ERawImageFormat::Type InFormat) : FImageInfo(InSizeX,InSizeY,1,InFormat, ERawImageFormat::GetDefaultGammaSpace(InFormat) ), RawData(InData)`
- L319 _public prototype_ `FImageView GetSlice(int32 SliceIndex) const;` — get an FImageView to one 2d slice
- L328 _public prototype_ `void CopyTo(FImage& DestImage, ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace) const;` — Copies the image to a destination image with the specified format. @param DestImage - The destination image. @param DestFormat - The destination image format. @param DestSRGB - Whether the destination image is in SRGB format.
- L331 _public function_ `void CopyTo(FImage& DestImage) const` — CopyTo same format
- L337 _public function_ `inline void * GetPixelPointer(int32 X,int32 Y,int32 Slice=0) const` — get a pointer to a pixel
- L345 _public function_ `const FLinearColor GetOnePixelLinear(int32 X,int32 Y,int32 Slice=0) const` — Get one pixel from the image and return in Linear color
- L356 _public function_ `TArrayView64<uint8> AsG8() const`
- L362 _public function_ `TArrayView64<uint16> AsG16() const`
- L368 _public function_ `TArrayView64<FColor> AsBGRA8() const`
- L374 _public function_ `TArrayView64<FColor> AsBGRE8() const`
- L380 _public function_ `TArrayView64<uint16> AsRGBA16() const`
- L386 _public function_ `TArrayView64<FFloat16Color> AsRGBA16F() const`
- L392 _public function_ `TArrayView64<FLinearColor> AsRGBA32F() const`
- L399 _public function_ `TArrayView64<FFloat16> AsR16F() const`
- L405 _public function_ `TArrayView64<float> AsR32F() const`

#### struct `FImage`  
`struct FImage : public FImageInfo`  
_L415-741_
- inherits: `FImageInfo`
- desc: Structure for raw image data.
- L418 _public member_ `TArray64<uint8> RawData;` — Raw image data.
- L425 _public function_ `FImage()` — Default constructor.
- L429 _public prototype_ `FImage(const FImage & CopyFrom) = default;`
- L430 _public prototype_ `FImage& operator=(const FImage & CopyFrom) = default;`
- L433 _public function_ `inline FImage(FImage && MoveFrom) : FImageInfo(MoveFrom), RawData(MoveTemp(MoveFrom.RawData))` — move constructor
- L439 _public function_ `FImage& operator=(FImage && MoveFrom)` — move assignment
- L458 _public prototype_ `FImage(int32 InSizeX, int32 InSizeY, int32 InNumSlices, ERawImageFormat::Type InFormat, EGammaSpace InGammaSpace);` — Creates and initializes a new image with the specified number of slices. @param InSizeX - The image width. @param InSizeY - The image height. @param InNumSlices - The number of slices. @param InFormat - The image format. @param InGammaSpace - (optional) Image Gamma Space.  GetDefaultGammaSpace() if not provided.
- L461 _public function_ `inline FImage(int32 InSizeX, int32 InSizeY, int32 InNumSlices, ERawImageFormat::Type InFormat) : FImage(InSizeX,InSizeY,InNumSlices,InFormat,ERawImageFormat::GetDefaultGammaSpace(InFormat))` — note: changed default GammaSpace from Linear to GetDefaultGammaSpace
- L474 _public function_ `inline FImage(int32 InSizeX, int32 InSizeY, ERawImageFormat::Type InFormat, EGammaSpace InGammaSpace) : FImage(InSizeX,InSizeY,1,InFormat,InGammaSpace)` — Creates and initializes a new image with a single slice. @param InSizeX - The image width. @param InSizeY - The image height. @param InFormat - The image format. @param InGammaSpace - (optional) Image Gamma Space.  GetDefaultGammaSpace() if not provided.
- L480 _public function_ `inline FImage(int32 InSizeX, int32 InSizeY, ERawImageFormat::Type InFormat) : FImage(InSizeX,InSizeY,1,InFormat,ERawImageFormat::GetDefaultGammaSpace(InFormat))` — note: changed default GammaSpace from Linear to GetDefaultGammaSpace
- L491 _public prototype_ `void FreeData(bool bAsyncDetached);` — Free FImage.RawData if bAsyncDetached free is done on a Task, not immediately, but the RawData member is empty upon return note that FreeData does not change the FImageInfo fields, only frees RawData, follow up with Reset() if desired
- L494 _public function_ `inline void Swap(FImage & Other)` — Swap the contents of this FImage with another
- L502 _public function_ `inline void Reset()` — Reset this FImage to empty default constructed state
- L511 _public function_ `inline operator FImageView () const` — implicit conversion to FImageView allows FImage to be passed to functions that take FImageView functions that read images should use "const FImageView &" as their argument type
- L519 _public prototype_ `FImageView GetSlice(int32 SliceIndex) const;` — get an FImageView to one 2d slice
- L528 _public prototype_ `void CopyTo(FImage& DestImage, ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace) const;` — Copies the image to a destination image with the specified format. @param DestImage - The destination image.  Will be allocated.  Any existing contents are replaced. @param DestFormat - The destination image format. @param DestSRGB - Whether the destination image is in SRGB format.
- L531 _public function_ `void CopyTo(FImage& DestImage) const` — CopyTo same format
- L538 _public prototype_ `void ChangeFormat(ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace);` — in-place format change : does nothing if already in the desired format
- L552 _public prototype_ `void ResizeTo(FImage& DestImage, int32 DestSizeX, int32 DestSizeY, ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace) const;` — Copies and resizes the image to a destination image with the specified size and format. Resize is done using bilinear filtering; gamma correct (light linear) by converting through RGBA32F. legacy API, prefer ResizeImage @param DestImage - The destination image. @param DestSizeX - Width of the resized image @param DestSizeY - Height of the resized image @param DestFormat - The destination image format. @param DestSRGB - Whether the destination image is in SRGB format.
- L563 _public prototype_ `void Linearize(uint8 SourceEncoding, FImage& DestImage) const;` — Linearize to a RGBA32F destination image by applying the decoding function that corresponds to the specified source encoding. If None, this call will be equivalent to CopyTo(DestImage, ERawImageFormat::RGBA32F, EGammaSpace::Linear). @param SourceEncoding - Opaque source encoding (matching UE::Color::EEncoding). @param DestImage - The destination image. SourceEncoding = None (0) to Linearize using the GammaSpace in this FImage
- L565 _public function_ `inline void Linearize(FImage& DestImage) const`
- L571 _public prototype_ `void TransformToWorkingColorSpace(const FVector2d& SourceRedChromaticity, const FVector2d& SourceGreenChromaticity, const FVector2d& SourceBlueChromaticity, const FVector2d& SourceWhiteChromaticity, UE::Color::EChromaticAdaptationMethod Method, double EqualityTolerance = 1.e-7);` — `UE_DEPRECATED(5.3, "TransformToWorkingColorSpace is deprecated, please use the function in FImageCore.")`
- L583 _public prototype_ `void Init(int32 InSizeX, int32 InSizeY, int32 InNumSlices, ERawImageFormat::Type InFormat, EGammaSpace InGammaSpace);` — Initializes this image with the specified number of slices. Allocates RawData. @param InSizeX - The image width. @param InSizeY - The image height. @param InNumSlices - The number of slices. @param InFormat - The image format. @param bInSRGB - Whether the color values are in SRGB format.
- L585 _public function_ `inline void Init(int32 InSizeX, int32 InSizeY, int32 InNumSlices, ERawImageFormat::Type InFormat)`
- L599 _public prototype_ `void Init(int32 InSizeX, int32 InSizeY, ERawImageFormat::Type InFormat, EGammaSpace InGammaSpace);` — Initializes this image with a single slice. Allocates RawData. @param InSizeX - The image width. @param InSizeY - The image height. @param InFormat - The image format. @param bInSRGB - Whether the color values are in SRGB format.
- L601 _public function_ `inline void Init(int32 InSizeX, int32 InSizeY, ERawImageFormat::Type InFormat)`
- L612 _public prototype_ `void Init(const FImageInfo & Info);` — Initializes this image with specified Info. Allocates RawData. @param Info - The image description.  Can also pass an FImage or FImageView to this function.
- L615 _public function_ `inline void * GetPixelPointer(int32 X,int32 Y,int32 Slice=0) const` — get a pointer to a pixel
- L622 _public function_ `const FLinearColor GetOnePixelLinear(int32 X,int32 Y,int32 Slice=0) const` — Get one pixel from the image and return in Linear color
- L632 _public function_ `TArrayView64<uint8> AsG8()`
- L638 _public function_ `TArrayView64<uint16> AsG16()`
- L644 _public function_ `TArrayView64<FColor> AsBGRA8()`
- L650 _public function_ `TArrayView64<FColor> AsBGRE8()`
- L656 _public function_ `TArrayView64<uint16> AsRGBA16()`
- L662 _public function_ `TArrayView64<FFloat16Color> AsRGBA16F()`
- L668 _public function_ `TArrayView64<FLinearColor> AsRGBA32F()`
- L674 _public function_ `TArrayView64<FFloat16> AsR16F()`
- L680 _public function_ `TArrayView64<float> AsR32F()`
- L688 _public function_ `TArrayView64<const uint8> AsG8() const`
- L694 _public function_ `TArrayView64<const uint16> AsG16() const`
- L700 _public function_ `TArrayView64<const FColor> AsBGRA8() const`
- L706 _public function_ `TArrayView64<const FColor> AsBGRE8() const`
- L712 _public function_ `TArrayView64<const uint16> AsRGBA16() const`
- L718 _public function_ `TArrayView64<const FFloat16Color> AsRGBA16F() const`
- L724 _public function_ `TArrayView64<const FLinearColor> AsRGBA32F() const`
- L730 _public function_ `TArrayView64<const FFloat16> AsR16F() const`
- L736 _public function_ `TArrayView64<const float> AsR32F() const`

#### struct `FSharedImage`  
`struct FSharedImage : public FImage, public FRefCountedObject`  
_L745-749_
- inherits: `FImage,FRefCountedObject`
- L747 _public prototype_ `FSharedImage() = default;`
- L748 _public prototype_ `virtual ~FSharedImage() = default;`

#### struct `FMipMapImage`  
`struct FMipMapImage`  
_L754-879_
- desc: Structure for raw image data used for Image formats that support Mip Maps.
- L772 _public member_ `TArray64<uint8> RawData;` — Raw image data.
- L775 _public member_ `TArray<FMipInfo> SubImages;` — Holds information about the sub images some image formats support.
- L778 _public member_ `ERawImageFormat::Type Format = ERawImageFormat::BGRA8;` — Format in which the images is stored.
- L781 _public member_ `EGammaSpace GammaSpace = EGammaSpace::sRGB;` — The gamma space the image is stored in.
- L790 _public prototype_ `void Init(ERawImageFormat::Type InFormat, EGammaSpace InGammaSpace);` — Initializes the Mip Map Image with parameters with uninitialized SubImages. @param InFormat Raw Image Format @param InGammaSpace Gamma Space
- L798 _public prototype_ `void Init(int32 MipZeroWidth, int32 MipZeroHeight, int32 NumMips, ERawImageFormat::Type InFormat, EGammaSpace InGammaSpace);` — Initializes the Mip Map Image with reserving space for mip maps. @param InFormat Raw Image Format @param InGammaSpace Gamma Space
- L807 _public prototype_ `void CopyTo(FMipMapImage& DestImage, ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace);` — Copies the image to a destination image with the specified format. @param DestImage - The destination image.  Will be allocated.  Any existing contents are replaced. @param DestFormat - The destination image format. @param DestSRGB - Whether the destination image is in SRGB format.
- L809 _public function_ `void CopyTo(FMipMapImage& DestImage)`
- L818 _public prototype_ `void ChangeFormat(ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace);` — In - place format change does nothing if already in the desired format
- L821 _public function_ `inline bool IsValid() const`
- L836 _public function_ `inline bool GetMipDimensions(int32 MipLevel, int32& OutWidth, int32& OutHeight) const`
- L850 _public function_ `inline int32 GetMipCount() const`
- L855 _public function_ `FImageView GetMipImage(int32 MipLevel)`
- L861 _public function_ `void AddMipImage(TArray64<uint8>&& Buffer, int32 Width, int32 Height)`
- L874 _public function_ `inline int64 GetNumPixels()`

#### struct `FMipMapImage::FMipInfo`  
`struct FMipInfo`  
_L756-769_
- L759 _public member_ `int32 Width = 0;` — Size of the mip image in Pixels
- L762 _public member_ `int32 Height = 0;` — Size of the mip image in Pixels
- L765 _public member_ `int64 Offset = 0;` — Offset into RawData
- L768 _public member_ `int64 Size = 0;` — Size of the mip image in Bytes

#### enum `FImageCore::EResizeImageFilter`  
`enum class EResizeImageFilter : uint32`  
_L1020-1053_
- desc: filter choice for ResizeImage
- L1022 _public enumerator_ `Default = 0` — uses a good default filter; = AdaptiveSharp
- L1023 _public enumerator_ `PointSample`
- L1024 _public enumerator_ `Box`
- L1025 _public enumerator_ `Triangle`
- L1026 _public enumerator_ `Bilinear = Triangle` — synonym
- L1027 _public enumerator_ `CubicGaussian` — smooth Mitchell B=1,C=0, B-spline, Gaussian-like
- L1028 _public enumerator_ `CubicSharp` — sharp interpolating cubic, Catmull-Rom (has negative lobes) (Mitchell B=0)
- L1029 _public enumerator_ `CubicMitchell` — compromise between sharp and smooth cubic, Mitchell-Netrevalli filter with B=1/3, C=1/3 (has negative lobes)
- L1030 _public enumerator_ `AdaptiveSharp` — sharper adaptive filter; uses CubicSharp for upsample and CubicMitchell for downsample, nop for same size
- L1031 _public enumerator_ `AdaptiveSmooth` — smoother adaptive filter; uses CubicMitchell for upsample and CubicGaussian for downsample, nop for same size
- L1033 _public enumerator_ `MitchellOneQuarter` — B=1/4 ("Robidoux")
- L1034 _public enumerator_ `MitchellOneSixth` — B=1/6
- L1035 _public enumerator_ `MitchellNegOneSixth` — B=-1/6 , over-sharpening
- L1036 _public enumerator_ `MitchellNegOneThird` — B=-1/3 , over-sharpening
- L1037 _public enumerator_ `Lanczos4` — sharp
- L1038 _public enumerator_ `Lanczos5` — very sharp, often ringy
- L1049 _public enumerator_ `WithoutFlagsMask = 63`
- L1050 _public enumerator_ `Flag_WrapX = 64` — default edge mode is clamp; set these to wrap instead
- L1051 _public enumerator_ `Flag_WrapY = 128`
- L1052 _public enumerator_ `Flag_AlphaWeighted = 256` — weight RGB by A in the filter; that is, convert non-premultiplied RGBA input to premultiplied for filtering, then convert back

#### Free symbols / members of external scopes

- L50 _namespace_ `namespace ERawImageFormat`
- L74 _prototype_ `int64 GetBytesPerPixel(Type Format);` (scope `ERawImageFormat`)
- L76 _prototype_ `const TCHAR * GetName(Type Format);` (scope `ERawImageFormat`)
- L77 _prototype_ `const FUtf8StringView GetNameView(Type Format);` (scope `ERawImageFormat`)
- L78 _prototype_ `bool GetFormatFromString(FUtf8StringView InString, Type& OutFormat);` (scope `ERawImageFormat`)
- L81 _prototype_ `bool IsU8Channels(Type Format);` (scope `ERawImageFormat`) — IsU8Channels is not true for BGRE8, it means channels of uint8 in [0,255]
- L82 _prototype_ `int NumChannels(Type Format);` (scope `ERawImageFormat`)
- L83 _prototype_ `bool IsHDR(Type Format);` (scope `ERawImageFormat`)
- L84 _prototype_ `bool HasAlphaChannel(Type Format);` (scope `ERawImageFormat`)
- L87 _prototype_ `const FLinearColor GetOnePixelLinear(const void * PixelData,Type Format,EGammaSpace Gamma);` (scope `ERawImageFormat`) — Get one pixel of Format type from PixelData and return in Linear color
- L90 _function_ `inline const FLinearColor GetOnePixelLinear(const void * PixelData,Type Format,bool bSRGB)` (scope `ERawImageFormat`) — Get one pixel of Format type from PixelData and return in Linear color
- L97 _function_ `inline bool GetFormatNeedsGammaSpace(Type Format)` (scope `ERawImageFormat`) — G8 and BGRA8 are affected by Gamma, 16/32 is NOT (they are always Linear) this happens to be the same as IsU8Channels() at the moment, but don't assume that
- L113 _function_ `inline EGammaSpace GetDefaultGammaSpace(Type Format)` (scope `ERawImageFormat`) — when converting from pixel bags that don't store gamma to FImage you can use this to guess the gamma they probably wanted do not use when a real gamma flag is available!
- L126 _namespace_ `namespace UE`
- L127 _namespace_ `namespace Color` (scope `UE`)
- L743 _typedef_ `typedef TRefCountPtr<struct FSharedImage> FSharedImageRef;`
- L744 _typedef_ `typedef TRefCountPtr<const struct FSharedImage> FSharedImageConstRef;`
- L885 _prototype_ `int32 ImageParallelForComputeNumJobsForPixels(int64 & OutNumPixelsPerJob,int64 NumPixels);`
- L887 _prototype_ `int32 ImageParallelForComputeNumJobsForRows(int32 & OutNumItemsPerJob,int64 SizeX,int64 SizeY);`
- L889 _namespace_ `namespace FImageCore`
- L902 _prototype_ `void CopyImage(const FImageView & SrcImage,const FImageView & DestImage);` (scope `FImageCore`) — Copy FImageView data, converting pixels if necessary. Sizes must match. Dest must already be allocated. For a function that allocates Dest, use CopyTo(). Because FImage implicitly convers to FImageView, these functions can be used on FImage types as well. @param SrcImage - The source image to copy from. @param DestImage - The destination image to copy to. (the FImageView is const but what it points at is not)
- L912 _prototype_ `void CopyImageRGBABGRA(const FImageView & SrcImage,const FImageView & DestImage);` (scope `FImageCore`) — Copy Image, swapping RB, SrcImage must be BGRA8 or RGBA16. Sizes must match. Dest must already be allocated. Src == Dest is okay for in-place transpose. @param SrcImage - The source image to copy from. @param DestImage - The destination image to copy to. (the FImageView is const but what it points at is not)
- L921 _prototype_ `void CopyImageTo2U16(const FImageView & SrcImage,const FImageView & DestImage);` (scope `FImageCore`) — Copy Image to 2xU16 ; Dest Image should be allocated as BGRA8 but is actually 2xU16 Sizes must match. Dest must already be allocated. @param SrcImage - The source image to copy from. @param DestImage - The destination image to copy to. (the FImageView is const but what it points at is not)
- L928 _prototype_ `void TransposeImageRGBABGRA(const FImageView & Image);` (scope `FImageCore`) — Swap RB channels on Image.  Image must be BGRA8 or RGBA16. @param  Image is modified (the FImageView is const but what it points at is not)
- L938 _prototype_ `void SanitizeFloat16AndSetAlphaOpaqueForBC6H(const FImageView & InOutImage);` (scope `FImageCore`) — Clamp Float16 colors which aren't encodable in the BC6H format RGB is clamped to non-negative and finite A is set to 1.0 @param  InOutImage is modified.  Must be RGBA16F. (the FImageView is const but what it points at is not)
- L947 _prototype_ `bool DetectAlphaChannel(const FImageView & InImage);` (scope `FImageCore`) — Detects whether or not the image contains an alpha channel where at least one texel is != 255. @param InImage - The image to look for alpha in. @return True if the image both supports and uses the alpha channel. False otherwise.
- L954 _prototype_ `void SetAlphaOpaque(const FImageView & InImage);` (scope `FImageCore`) — Change alpha channel to opaque, if present @param InImage - The image to look for alpha in.
- L968 _prototype_ `void ResizeTo(const FImageView & SourceImage,FImage& DestImage, int32 DestSizeX, int32 DestSizeY, ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace);` (scope `FImageCore`) — Copies and resizes the image to a destination image with the specified size and format. Resize is done using bilinear filtering; gamma correct (light linear) by converting through RGBA32F. legacy API, prefer ResizeImage @param DestImage - The destination image. @param DestSizeX - Width of the resized image @param DestSizeY - Height of the resized image @param DestFormat - The destination image format. @param DestSRGB - Whether the destination image is in SRGB format.
- L978 _prototype_ `void ComputeChannelLinearMinMax(const FImageView & InImage, FLinearColor & OutMin, FLinearColor & OutMax);` (scope `FImageCore`) — Compute the min/max of each channel to get value ranges Colors are converted to float Linear Gamma @param InImage - The image to scan @param OutMin - filled with the minimum of the color channels @param OutMax - filled with the maximum of the color channels
- L994 _prototype_ `bool ScaleChannelsSoMinMaxIsInZeroToOne(const FImageView & ImageToModify);` (scope `FImageCore`) — If the image has any values outside the [0,1] range, rescale that edge of the domain so that it is in [0,1] does not affect images that were previously in [0,1] also does not change the side of the domain that is not out of bounds eg. values in [0.25,200.0] will be rescaled to [0.25,1.0] returns bool if any change was made If the input format is U8 or U16, no change will ever be made and this will return false. This can be useful if you want to save an HDR/float image to a U8 image format for visualization. This is equivalent to what's called the "UNorm" transformation by the RenderTarget ReadPixels functions.
- L1001 _prototype_ `FLinearColor ComputeImageLinearAverage(const FImageView & Image);` (scope `FImageCore`) — ComputeImageLinearAverage compute the average linear color of the image image can be any pixel format parallel processing is used, but the result is not machine-dependent
- L1014 _prototype_ `void TransformToWorkingColorSpace(const FImageView& InLinearImage, const FVector2d& SourceRedChromaticity, const FVector2d& SourceGreenChromaticity, const FVector2d& SourceBlueChromaticity, const FVector2d& SourceWhiteChromaticity, UE::Color::EChromaticAdaptationMethod Method, double EqualityTolerance = 1.e-7);` (scope `FImageCore`) — Apply a color space transformation from the source chromaticities to the engine's working color space. @param InLinearImage - The image to convert, which must be linear. @param SourceRedChromaticity - The red chromaticity coordinate of the source color space. @param SourceGreenChromaticity - The green chromaticity coordinate of the source color space. @param SourceBlueChromaticity - The blue chromaticity coordinate of the source color space. @param SourceWhiteChromaticity - The white chromaticity coordinate of the source color space. @param Method - The chromatic adapation method. @param EqualityTolerance - The tolerance for the source and working color space chromaticities to be considered equal, bypassing the transform.
- L1054 _prototype_ `ENUM_CLASS_FLAGS(EResizeImageFilter);` (scope `FImageCore`)
- L1067 _prototype_ `void ResizeImage(const FImageView & SourceImage,const FImageView & DestImage, EResizeImageFilter Filter = EResizeImageFilter::Default);` (scope `FImageCore`) — ResizeImage : DestImage should be already allocated; DestImage will be filled in specified format filter is always computed in floating point, gamma correct linear light, but no intermediate conversion is done note: some filters (the three "Cubic" options) will change the image even if Source.Size == Dest.Size this function can be used to apply filters on same-size image with the Cubic set the "Adaptive" (and Default) filters automatically change depending on if the resize is an upsample or downsample, and are nops for same size @param SourceImage - Source Image to resize from @param DestImage - Dest Image to resize to; specifies output size and format.  Note the FImageView itself is const but the Dest pixels are written.  Dest should be already allocated.  Source == Dest in-place resizing not allowed. @param Filter - EResizeImageFilter filter choice, or Default if none
- L1082 _prototype_ `void ResizeImageAllocDest(const FImageView & SourceImage,FImage & DestImage,int32 DestSizeX, int32 DestSizeY, ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace, EResizeImageFilter Filter = EResizeImageFilter::Default);` (scope `FImageCore`) — ResizeImage variant.  See main ResizeImage function for notes. Allocate DestImage (if needed) to specified size and Resize from SourceImage into it do not use this with Source == Dest (call ResizeImageInPlace) @param SourceImage - Source Image to resize from @param DestImage - Dest to allocated and write to.  Will not be allocated if it is already the right size.  DestImage size/format is replaced. @param DestSizeX - Specifies output of resize.  DestImage will be changed to this. @param DestSizeY - Specifies output of resize.  DestImage will be changed to this. @param DestFormat - Specifies output of resize.  DestImage will be changed to this. @param DestGammaSpace - Specifies output of resize.  DestImage will be changed to this. @param Filter - EResizeImageFilter filter choice, or Default if none
- L1097 _prototype_ `void ResizeImageAllocDest(const FImageView & SourceImage,FImage & DestImage,int32 DestSizeX, int32 DestSizeY, EResizeImageFilter Filter = EResizeImageFilter::Default);` (scope `FImageCore`) — ResizeImage variant.  See main ResizeImage function for notes. Allocate DestImage (if needed) to specified size and Resize from SourceImage into it do not use this with Source == Dest (call ResizeImageInPlace) DestImage will have same format as Source @param SourceImage - Source Image to resize from @param DestImage - Dest to allocated and write to.  Will not be allocated if it is already the right size.  DestImage size/format is replaced. @param DestSizeX - Specifies output of resize.  DestImage will be changed to this. @param DestSizeY - Specifies output of resize.  DestImage will be changed to this. @param Filter - EResizeImageFilter filter choice, or Default if none
- L1113 _prototype_ `void ResizeImageInPlace(FImage & Image,int32 DestSizeX, int32 DestSizeY, ERawImageFormat::Type DestFormat, EGammaSpace DestGammaSpace, EResizeImageFilter Filter = EResizeImageFilter::Default);` (scope `FImageCore`) — ResizeImage variant.  See main ResizeImage function for notes. Resize from Image and write the result into Image. Image may be reallocated to fit the destination size/format requested. Other ResizeImage functions do not work in-place. @param Image - Source Image to resize from, will be changed to hold the destination image and reallocated if needed. @param DestSizeX - Specifies output of resize.  DestImage will be changed to this. @param DestSizeY - Specifies output of resize.  DestImage will be changed to this. @param DestFormat - Specifies output of resize.  DestImage will be changed to this. @param DestGammaSpace - Specifies output of resize.  DestImage will be changed to this. @param Filter - EResizeImageFilter filter choice, or Default if none
- L1129 _prototype_ `void ResizeImageInPlace(FImage & Image,int32 DestSizeX, int32 DestSizeY, EResizeImageFilter Filter = EResizeImageFilter::Default);` (scope `FImageCore`) — ResizeImage variant.  See main ResizeImage function for notes. Resize from Image and write the result into Image. Image may be reallocated to fit the destination size/format requested. Other ResizeImage functions do not work in-place. Format of image will not be changed. @param Image - Source Image to resize from, will be changed to hold the destination image and reallocated if needed. @param DestSizeX - Specifies output of resize.  DestImage will be changed to this. @param DestSizeY - Specifies output of resize.  DestImage will be changed to this. @param Filter - EResizeImageFilter filter choice, or Default if none

### `Source/Runtime/ImageCore/Public/ImageCoreBP.h` (Public)


#### struct `FSharedImageConstRefBlueprint`  
`struct FSharedImageConstRefBlueprint`  
_L14-25_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "FSharedImageConst"))`
- desc: Exposes a FSharedImage to blueprint in an unalterable way.
- L17 _public member_ `FSharedImageConstRef Reference;`
- L19 _public prototype_ `FSharedImageConstRefBlueprint() = default;`
- L20 _public prototype_ `~FSharedImageConstRefBlueprint() = default;`
- L21 _public prototype_ `FSharedImageConstRefBlueprint(const FSharedImageConstRefBlueprint&) = default;`
- L22 _public prototype_ `FSharedImageConstRefBlueprint(FSharedImageConstRefBlueprint&&) = default;`
- L23 _public prototype_ `FSharedImageConstRefBlueprint& operator=(const FSharedImageConstRefBlueprint&) = default;`
- L24 _public prototype_ `FSharedImageConstRefBlueprint& operator=(FSharedImageConstRefBlueprint&&) = default;`

#### class `USharedImageConstRefBlueprintFns`  
`class USharedImageConstRefBlueprintFns : public UObject`  
_L28-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L34 _public prototype_ `static bool IsValid(const FSharedImageConstRefBlueprint& Image);` — `UFUNCTION(BlueprintCallable, Category = "SharedImage")`
- L38 _public prototype_ `static FVector2f GetSize(const FSharedImageConstRefBlueprint& Image);` — `UFUNCTION(BlueprintCallable, Category = "SharedImage")` — Returns (-1, -1) if Image is invalid
- L42 _public prototype_ `static int32 GetWidth(const FSharedImageConstRefBlueprint& Image);` — `UFUNCTION(BlueprintCallable, Category = "SharedImage")` — Returns -1 if Image is invalid
- L46 _public prototype_ `static int32 GetHeight(const FSharedImageConstRefBlueprint& Image);` — `UFUNCTION(BlueprintCallable, Category = "SharedImage")` — Returns -1 if Image is invalid
- L57 _public prototype_ `static FLinearColor GetPixelLinearColor(const FSharedImageConstRefBlueprint& Image, int32 X, int32 Y, bool& bValid, FLinearColor FailureColor=FLinearColor::Black);` — `UFUNCTION(BlueprintCallable, Category = "SharedImage")` — Returns the color value for the given pixel. If the input position is invalid, the format is invalid, or the reference isn't set, bValid will be false and the function will return FailureColor. The color is converted using the image's gamma space in to linear space. Do not use this for full image processing as it will be extremely slow, contact support if you need such functionality.
- L76 _public prototype_ `static FVector4f GetPixelValue(const FSharedImageConstRefBlueprint& Image, int32 X, int32 Y, bool& bValid);` — `UFUNCTION(BlueprintCallable, Category = "SharedImage")` — Returns the value in the texture for the given pixel as a float vector. If the input position is invalid, the format is invalid, or the reference isn't set, bValid will be false and the function will return FVector4(0,0,0,0). Pixel values are directly returned with no gamma transformation to allow for lookup tables. Also note that 8 bit formats that you might normally expect to be normalized to 0..1 will return their values directly as 0..256. This supports all image formats. G8 is replicated to X/Y/Z/1. R16/R32 is returned as R/0/0/1. Do not use this for full image processing as it will be extremely slow, contact support if you need such functionality.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IMAGECORE_API`

### `Source/Runtime/ImageCore/Public/ImageCoreDelta.h` (Public)


#### struct `FImageViewStrided`  
`struct FImageViewStrided : public FImageInfo`  
_L18-94_
- inherits: `FImageInfo`
- desc: FImageViewStrided cannot derive from FImageView you can implicitly convert FImage -> FImageView -> FImageViewStrided but you cannot convert FImageViewStrided -> the others, because they can't have stride
- L20 _public member_ `void * RawData = nullptr;`
- L21 _public member_ `int64 StrideBytes = 0;`
- L23 _public function_ `FImageViewStrided()`
- L25 _public function_ `FImageViewStrided(const FImageInfo & InInfo,void * InRawData,int64 InStride = 0) : FImageInfo(InInfo), RawData(InRawData), StrideBytes(InStride)`
- L33 _public function_ `FImageViewStrided(const FImageView & InView)`
- L41 _public function_ `inline int64 GetStrideBytes() const` — replaces the call in FImageInfo but is NOT virtual ; beware
- L44 _public function_ `inline bool IsStrideWidth() const` — if IsStrideWidth, then you can convert back to FImageView
- L48 _public function_ `inline int64 GetPixelOffsetBytes(int32 X,int32 Y,int32 Slice = 0) const` — get offset of a pixel from the base pointer, in bytes replaces the call in FImageInfo but is NOT virtual ; beware
- L63 _public function_ `inline uint8 * GetRowPointer(int32 Y,int32 Slice = 0) const`
- L75 _public function_ `inline void * GetPixelPointer(int32 X,int32 Y,int32 Slice=0) const` — get a pointer to a pixel
- L82 _public function_ `inline const FImageViewStrided GetPortion(int64 PortionStartX,int64 PortionSizeX, int64 PortionStartY,int64 PortionSizeY) const`

#### Free symbols / members of external scopes

- L97 _namespace_ `namespace FImageCoreDelta`
- L102 _prototype_ `void AddSplitStridedViewsForDelta( TArray64<FImageViewStrided> & OutViews, const FImageView & InView );` (scope `FImageCoreDelta`) — Split InView into tiles and add to OutViews.  Will add 1 more entries to OutViews.
- L111 _prototype_ `void DoTransform(const FImageViewStrided & InImage,uint8 * OutData,bool bForward);` (scope `FImageCoreDelta`) — Do Delta Transform bForward=false is the inverse transform OutData must be the same size and layout as InImage ; eg. same pixel sizes and strides.  It is not rearranged in any way. No headers are added.

### `Source/Runtime/ImageCore/Public/ImageCoreUtils.h` (Public)


#### Free symbols / members of external scopes

- L21 _namespace_ `namespace FImageCoreUtils`
- L28 _prototype_ `bool IsImageImportPossible(int64 Width,int64 Height);` (scope `FImageCoreUtils`) — IsImageImportPossible returns false if the image dimensions are not supported to import if this function returns true, image import might still fail due to further constraints (this constraint is weaker than the one actually required) (see IsImportResolutionValid, which is also still weaker than the final constraint) IsImageImportPossible does not check current Engine config or platform limits, only hard-coded absolute limits
- L32 _prototype_ `int32 GetMipCountFromDimensions(int32 InSizeX, int32 InSizeY, int32 InVolumeZ, bool bInIsVolume);` (scope `FImageCoreUtils`) — Returns the number of mips that constitute a full mip chain for the given top level mip size. InVolumeZ is ignored unless bInIsVolume is true
- L35 _prototype_ `ERawImageFormat::Type ConvertToRawImageFormat(ETextureSourceFormat Format);` (scope `FImageCoreUtils`) — ETextureSourceFormat and ERawImageFormat::Type are one-to-one :
- L36 _prototype_ `ETextureSourceFormat ConvertToTextureSourceFormat(ERawImageFormat::Type Format);` (scope `FImageCoreUtils`)
- L44 _prototype_ `EPixelFormat GetPixelFormatForRawImageFormat(ERawImageFormat::Type InFormat, ERawImageFormat::Type * pOutEquivalentFormat=nullptr);` (scope `FImageCoreUtils`) — EPixelFormat is the graphics texture pixel format it is a much larger superset of ERawImageFormat GetPixelFormatForRawImageFormat does not map to the very closest EPixelFormat instead map to a close one that is actually usable as Texture if *pOutEquivalentFormat != InFormat , then conversion is needed and conversion can be done using CopyImage to OutEquivalentFormat
- L48 _prototype_ `FName ConvertToUncompressedTextureFormatName(ERawImageFormat::Type Format);` (scope `FImageCoreUtils`)
- L56 _prototype_ `ETextureSourceFormat GetCommonSourceFormat(ETextureSourceFormat Format1, ETextureSourceFormat Format2);` (scope `FImageCoreUtils`) — Returns ETextureSourceFormat which can be used to efficiently store data encoded in both input formats. Can be used in cases when multiple sources need to be mixed together (i.e. in a texture array or UDIM) @param Format1 - First source format. @param Format2 - Second source format.
- L62 _prototype_ `ERawImageFormat::Type GetRawImageFormatForPixelFormat(EPixelFormat PF);` (scope `FImageCoreUtils`) — return an ERawImageFormat for a PixelFormat these are not equal and you cannot blit between them it's just the closest reasonable thing that can hold that PixelFormat often there is no good match

### `Source/Runtime/ImageCore/Public/ImageParallelFor.h` (Public)


#### enum `FImageCore::ProcessLinearPixelsAction`  
`enum class ProcessLinearPixelsAction`  
_L76-80_
- L78 _public enumerator_ `ReadOnly`
- L79 _public enumerator_ `Modified`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace FImageCore`
- L36 _function_ `inline int64 ImageParallelForComputeNumRows(const FImageView & Image)` (scope `FImageCore`) — ImageParallelFor treats the image as being 2d (no slices) but with *NumSlices rows
- L42 _function_ `inline FImageView ImageParallelForGetOneRowView(const FImageView & Image,int64 Y)` (scope `FImageCore`) — Y indexes across slices and SizeY here :
- L54 _prototype_ `int32 ImageParallelForComputeNumJobs(const FImageView & Image,int64 * pRowsPerJob);` (scope `FImageCore`)
- L55 _prototype_ `int64 ImageParallelForMakePart(FImageView * Part,const FImageView & Whole,int64 JobIndex,int64 RowsPerJob);` (scope `FImageCore`)
- L63 _function_ `template <typename Lambda> inline void ImageParallelFor(const TCHAR* DebugName, const FImageView & Image, const Lambda& Func)` (scope `FImageCore`) — Lambda is a functor that works on an FImageView() it will be called with portions of the image each portion will be a 2d FImageView (NumSlices == 1) use like : FImageCore::ImageParallelFor( TEXT("Texture.AdjustImageColorsFunc.PF"),Image, [&](FImageView & ImagePart) {
- L69 _function_ `` (scope `FImageCore::ImageParallelFor`)
- L92 _function_ `template <typename Lambda> inline void ProcessLinearPixels(const FImageView & Image, const Lambda& Func, int64 StartY)` (scope `FImageCore`) — ProcessLinearPixels act on image pixels as TArrayView64<FLinearColor> Colors pass a lambda that is : ProcessLinearPixelsAction ProcessPixels(TArrayView64<FLinearColor> Colors) return ProcessLinearPixelsAction::Modified if you modify colors return ProcessLinearPixelsAction::ReadOnly if you only read and don't change colors your lambda will be called on one row at a time
- L133 _function_ `template <typename Lambda> inline void ImageParallelProcessLinearPixels(const TCHAR* DebugName, const FImageView & Image, const Lambda& Func)` (scope `FImageCore`) — parallel process image as TArrayView64<FLinearColor> your lambda is called on one row at a time so that the grouping is machine invariant
- L135 _function_ `ImageParallelFor(DebugName,Image,[Func](const FImageView &Part,int64 StartY) {` (scope `FImageCore::ImageParallelProcessLinearPixels`)
