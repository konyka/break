# Runtime / ImageWrapper

- module root: `Source/Runtime/ImageWrapper`
- headers: 19; symbols: 390
- symbol kinds: class=15, delegate=1, enum=6, enumerator=42, function=27, member=104, namespace=3, prototype=181, struct=6, typedef=5
- PrivateDependencyModuleNames: Core
- PrivateIncludePathModuleNames: Engine
- PublicDependencyModuleNames: ImageCore, LibTiff
- PublicIncludePathModuleNames: ImageCore

### `Source/Runtime/ImageWrapper/Private/Formats/BmpImageWrapper.h` (Private)


#### class `FBmpImageWrapper`  
`class FBmpImageWrapper : public FImageWrapperBase`  
_L12-57_
- inherits: `FImageWrapperBase`
- desc: BMP implementation of the helper class
- L18 _public prototype_ `FBmpImageWrapper(bool bInHasHeader = true, bool bInHalfHeight = false);` — Default Constructor.
- L23 _public prototype_ `bool UncompressBMPData(const ERGBFormat InFormat, const int32 InBitDepth);` — Helper function used to uncompress BMP data from a buffer
- L30 _public prototype_ `bool LoadBMPHeader();` — Load the header information, returns true if successful. @return true if successful
- L37 _public prototype_ `bool LoadBMPInfoHeader(int64 HeaderOffset);` — Load the sub-header information, returns true if successful. @return true if successful
- L43 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L44 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L45 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L47 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L48 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L53 _private member_ `bool bHasHeader;` — Whether this file has a BMP file header
- L56 _private member_ `bool bHalfHeight;` — BMP as a sub-format of ICO stores its height as half their actual size

### `Source/Runtime/ImageWrapper/Private/Formats/DdsImageWrapper.h` (Private)


#### class `FDdsImageWrapper`  
`class FDdsImageWrapper : public FImageWrapperBase`  
_L12-49_
- inherits: `FImageWrapperBase`
- desc: DDS implementation of the helper class
- L14 _private typedef_ `typedef FImageWrapperBase Super;`
- L17 _public function_ `FDdsImageWrapper()`
- L20 _public function_ `~FDdsImageWrapper()`
- L25 _public function_ `void FreeDDS()`
- L38 _public prototype_ `virtual void Reset() override;`
- L40 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L41 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L42 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L44 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L45 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L48 _public member_ `UE::DDS::FDDSFile * DDS = nullptr;`

### `Source/Runtime/ImageWrapper/Private/Formats/ExrImageWrapper.h` (Private)


#### class `FExrImageWrapper`  
`class FExrImageWrapper : public FImageWrapperBase`  
_L30-60_
- inherits: `FImageWrapperBase`
- desc: OpenEXR implementation of the helper class
- L38 _public prototype_ `FExrImageWrapper();` — Default Constructor.
- L44 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L45 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L46 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L48 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L49 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L51 _public typedef_ `typedef TUniquePtr<char[]> FUniqueCString;`
- L52 _public function_ `FUniqueCString MakeUniqueCString(const char *str)`
- L59 _public member_ `TArray< FUniqueCString > FileChannelNames;`

### `Source/Runtime/ImageWrapper/Private/Formats/IcnsImageWrapper.h` (Private)


#### class `FIcnsImageWrapper`  
`class FIcnsImageWrapper : public FImageWrapperBase`  
_L11-30_
- inherits: `FImageWrapperBase`
- desc: ICNS implementation of the helper class.
- L17 _public prototype_ `FIcnsImageWrapper();` — Default Constructor.
- L23 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L24 _public prototype_ `virtual bool SetRaw(const void* InRawData, int64 InRawSize, const int32 InWidth, const int32 InHeight, const ERGBFormat InFormat, const int32 InBitDepth, const int32 InBytesPerRow = 0) override;`
- L25 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L26 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L28 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L29 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`

### `Source/Runtime/ImageWrapper/Private/Formats/IcoImageWrapper.h` (Private)


#### class `FIcoImageWrapper`  
`class FIcoImageWrapper : public FImageWrapperBase`  
_L14-56_
- inherits: `FImageWrapperBase`
- desc: ICO implementation of the helper class.
- L20 _public prototype_ `FIcoImageWrapper();` — Default Constructor.
- L26 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L27 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L28 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L29 _public prototype_ `virtual bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, TArray64<uint8>& OutRawData) override;`
- L31 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L32 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L41 _protected prototype_ `bool LoadICOHeader();` — Load the header information. @return true if successful
- L46 _private member_ `TSharedPtr<FImageWrapperBase> SubImageWrapper;` — Sub-wrapper component, as icons that contain PNG or BMP data
- L49 _private member_ `uint32 ImageOffset;` — Offset into file that we use as image data
- L52 _private member_ `uint32 ImageSize;` — Size of image data in file
- L55 _private member_ `bool bIsPng;` — Whether we should use PNG or BMP data

### `Source/Runtime/ImageWrapper/Private/Formats/JpegImageWrapper.h` (Private)


#### class `FJpegImageWrapper`  
`class FJpegImageWrapper : public FImageWrapperBase`  
_L19-55_
- inherits: `FImageWrapperBase`
- desc: Uncompresses JPEG data to raw 24bit RGB image that can be used by Unreal textures. Source code for JPEG decompression from http://code.google.com/p/jpeg-compressor/
- L26 _public prototype_ `FJpegImageWrapper(int32 InNumComponents = 4);` — NumComponents == 1 for GrayscaleJPEG , but not supported by TJPEG path so currently broken
- L28 _public prototype_ `virtual ~FJpegImageWrapper();`
- L29 _public prototype_ `virtual void Reset() override;`
- L35 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L36 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L37 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L39 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L40 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L44 _private member_ `int32 NumComponents;`
- L47 _private prototype_ `bool SetCompressedTurbo(const void* InCompressedData, int64 InCompressedSize);`
- L48 _private prototype_ `void CompressTurbo(int32 Quality);`
- L49 _private prototype_ `void UncompressTurbo(const ERGBFormat InFormat, int32 InBitDepth);`
- L53 _private member_ `tjhandle Decompressor;`

#### Free symbols / members of external scopes

- L11 _typedef_ `using tjhandle = void*;`

### `Source/Runtime/ImageWrapper/Private/Formats/PngImageWrapper.h` (Private)


#### class `FPngImageWrapper`  
`class FPngImageWrapper : public FImageWrapperBase`  
_L36-127_
- inherits: `FImageWrapperBase`
- desc: PNG implementation of the helper class. The implementation of this class is almost entirely based on the sample from the libPNG documentation. See http://www.libpng.org/pub/png/libpng-1.2.5-manual.html for details. InitCompressed and InitRaw will set initial state and you will then be able to fill in Raw or CompressedData by calling Uncompress or Compress respectively.
- L42 _public prototype_ `FPngImageWrapper();` — Default Constructor.
- L48 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L49 _public prototype_ `virtual void Reset() override;`
- L50 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L51 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L53 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L54 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L61 _public prototype_ `virtual bool SupportsMetadata() const override;` — Does this image type support embedded metadata in its header? PNG is an example of an image type which supports adding user-defined metadata to its header.
- L69 _public prototype_ `virtual void AddMetadata(const FString& InKey, const FString& InValue) override;` — Adds a key and value to this image's metadata.  Will be saved in the image's header and restored when the image is loaded. @param InKey Metadata consists of key value pairs. @param InValue Metadata consists of key value pairs.
- L76 _public prototype_ `virtual void GetMetadata(TStringMap& OutMetadata) const override;` — Copies this image's metadata to the caller's map. @param OutMetadata A copy of this image's metadata.
- L85 _public prototype_ `bool IsPNG() const;` — Query whether this is a valid PNG type. @return true if data a PNG
- L92 _public prototype_ `bool LoadPNGHeader();` — Load the header information, returns true if successful. @return true if successful
- L95 _public prototype_ `void UncompressPNGData(const ERGBFormat InFormat, const int32 InBitDepth);` — Helper function used to uncompress PNG data from a buffer
- L100 _protected prototype_ `static void user_read_compressed(png_structp png_ptr, png_bytep data, png_size_t length);` — Callbacks for the pnglibs
- L101 _protected prototype_ `static void user_write_compressed(png_structp png_ptr, png_bytep data, png_size_t length);`
- L102 _protected prototype_ `static void user_flush_data(png_structp png_ptr);`
- L103 _protected prototype_ `static void user_error_fn(png_structp png_ptr, png_const_charp error_msg);`
- L104 _protected prototype_ `static void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg);`
- L105 _protected prototype_ `static void* user_malloc(png_structp png_ptr, png_size_t size);`
- L106 _protected prototype_ `static void user_free(png_structp png_ptr, png_voidp struct_ptr);`
- L111 _private member_ `int64 ReadOffset;` — The read offset into our array.
- L114 _private member_ `int32 ColorType;` — The color type as defined in the header.
- L117 _private member_ `uint8 Channels;` — The number of channels.
- L122 _private member_ `jmp_buf SetjmpBuffer;` — setjmp buffer for error recovery.
- L126 _private member_ `TMap<FString, FString> TextBlocks;` — Metadata for/from our header.

### `Source/Runtime/ImageWrapper/Private/Formats/TgaImageWrapper.h` (Private)


#### class `FTgaImageWrapper`  
`class FTgaImageWrapper : public FImageWrapperBase`  
_L12-38_
- inherits: `FImageWrapperBase`
- desc: TGA implementation of the helper class
- L19 _public prototype_ `bool LoadTGAHeader();` — Load the header information, returns true if successful.
- L21 _public prototype_ `static bool IsTGAHeader(const void * CompressedData,int64 CompressedDataLength);`
- L27 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L28 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L29 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L31 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L32 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L36 _private member_ `int32 ColorMapType;` — The color type as defined in the header.
- L37 _private member_ `uint8 ImageTypeCode;`

### `Source/Runtime/ImageWrapper/Private/Formats/TiffImageWrapper.h` (Private)


#### class `UE::ImageWrapper::Private::FTiffImageWrapper`  
`class FTiffImageWrapper : public FImageWrapperBase`  
_L14-88_
- inherits: `FImageWrapperBase`
- L17 _public prototype_ `~FTiffImageWrapper();`
- L19 _public prototype_ `FTiffImageWrapper() = default;`
- L20 _public prototype_ `FTiffImageWrapper(FTiffImageWrapper&&) = default;`
- L21 _public prototype_ `FTiffImageWrapper& operator=(FTiffImageWrapper&&) = default;`
- L23 _public prototype_ `FTiffImageWrapper(const FTiffImageWrapper&) = delete;`
- L24 _public prototype_ `FTiffImageWrapper& operator=(const FTiffImageWrapper&) = delete;`
- L27 _public prototype_ `virtual void Compress(int32 Quality) override;` — FImageWrapperBase Interface
- L28 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L29 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth, FDecompressedImageOutput& OutDecompressedImage) override;`
- L30 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L32 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L33 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L36 _private prototype_ `bool Uncompress_Internal(const ERGBFormat InFormat, int32 InBitDepth, TMap<FString, FString>& OutTagMetaData);`
- L38 _private prototype_ `void ReleaseTiffImage();`
- L42 _private prototype_ `template<class DataTypeDest> void UnpackIntoRawBuffer(const uint8 NumOfChannelDst);` — Unpack the compressed data into the raw buffer. It will also add the alpha channel when needed.
- L45 _private prototype_ `template<class DataTypeDest, class DataTypeSrc, class Adapter> void CallUnpackIntoRawBufferImpl(uint8 NumOfChannelDest, const bool bIsTiled);`
- L48 _private prototype_ `template<class DataTypeDest, class DataTypeSrc> void DefaultCallUnpackIntoRawBufferImpl(uint8 NumOfChannelDest, const bool bIsTiled);`
- L51 _private prototype_ `template<class DataTypeDest, class DataTypeSrc, class Adapter> void PaletteCallUnpackIntoRawBufferImpl(uint8 NumOfChannelDest, const bool bIsTiled);`
- L54 _private prototype_ `template<class DataTypeDest, class DataTypeSrc, bool bIsTiled, class ReadWriteAdapter> bool UnpackIntoRawBufferImpl(const uint8 NumOfChannelDest, const bool bAddAlpha);`
- L57 _private member_ `int64 CurrentPosition = 0;` — Postion in the buffer pass as a memory file to LibTiff
- L59 _private member_ `TIFF* Tiff = nullptr;`
- L61 _private member_ `uint16 Photometric = 0;`
- L62 _private member_ `uint16 Compression = 0;`
- L63 _private member_ `uint16 BitsPerSample = 0;`
- L64 _private member_ `uint16 SamplesPerPixel = 0;`
- L65 _private member_ `uint16 SampleFormat = 0;`
- L67 _private member_ `int64 CurrSubImageWidth = 0;`
- L68 _private member_ `int64 CurrSubImageHeight = 0;`
- L69 _private member_ `TArray64<uint8> SubImageBuffer;`
- L73 _private function_ `virtual void Reset() override`

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef struct tiff TIFF;`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ImageWrapper` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::ImageWrapper`)

### `Source/Runtime/ImageWrapper/Private/Formats/UEJpegImageWrapper.h` (Private)


#### class `FUEJpegImageWrapper`  
`class FUEJpegImageWrapper : public FImageWrapperBase`  
_L10-36_
- inherits: `FImageWrapperBase`
- L17 _public prototype_ `FUEJpegImageWrapper(int32 InNumComponents = 4);` — NumComponents == 1 for GrayscaleJPEG
- L19 _public prototype_ `virtual ~FUEJpegImageWrapper();`
- L25 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L26 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) override;`
- L27 _public prototype_ `virtual void Compress(int32 Quality) override;`
- L28 _public prototype_ `virtual TArray64<uint8> GetExportData(int32 Quality) override;`
- L30 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L31 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L35 _private member_ `int32 NumComponents;`

### `Source/Runtime/ImageWrapper/Private/ImageWrapperBase.h` (Private)


#### class `FImageWrapperBase`  
`class FImageWrapperBase : public IImageWrapper`  
_L15-178_
- inherits: `IImageWrapper`
- desc: The abstract helper class for handling the different image formats
- L21 _public prototype_ `FImageWrapperBase();` — Default Constructor.
- L30 _public function_ `const TArray64<uint8>& GetRawData() const` — Gets the image's raw data. @return A read-only byte array containing the data.
- L40 _public function_ `void MoveRawData(TArray64<uint8>& OutRawData)` — Moves the image's raw data into the provided array. @param OutRawData The destination array.
- L54 _public prototype_ `virtual void Compress(int32 Quality) = 0;` — Compresses the data. @param Quality The compression quality. returns void. call SetError() in your implementation if you fail.
- L59 _public prototype_ `virtual void Reset();` — Resets the local variables.
- L66 _public prototype_ `void SetError(const TCHAR* ErrorMessage);` — Sets last error message. @param ErrorMessage The error message to set.
- L71 _public function_ `const FString & GetLastError() const` — Gets last error message.
- L84 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth) = 0;` — Function to uncompress our data @param InFormat How we want to manipulate the RGB data @param InBitDepth The bit depth per-channel of the image. returns void. call SetError() in your implementation if you fail.
- L96 _public prototype_ `virtual void Uncompress(const ERGBFormat InFormat, int32 InBitDepth, FDecompressedImageOutput& OutDecompressedImage);` — Function to uncompress our data and retrive meta info along with it. @param InFormat				How we want to manipulate the RGB data @param InBitDepth			The bit depth per-channel of the image. @param OutDecompressedImage	Holds decompressed image, its mip-maps if available along with meta data that can be retrived during the decompression of the image. returns void. call SetError() in your implementation if you fail.
- L102 _public prototype_ `virtual TArray64<uint8> GetCompressed(int32 Quality = 0) override;`
- L104 _public function_ `virtual int32 GetBitDepth() const override`
- L109 _public function_ `virtual ERGBFormat GetFormat() const override`
- L114 _public function_ `virtual int64 GetHeight() const override`
- L119 _public prototype_ `virtual bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, TArray64<uint8>& OutRawData) override;`
- L122 _public prototype_ `virtual bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, FDecompressedImageOutput& OutDecompressedImage) override;` — Use this version when you expect more information such as mipmaps, etc.
- L124 _public function_ `virtual int64 GetWidth() const override`
- L129 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;`
- L130 _public prototype_ `virtual bool SetRaw(const void* InRawData, int64 InRawSize, const int32 InWidth, const int32 InHeight, const ERGBFormat InFormat, const int32 InBitDepth, const int32 InBytesPerRow = 0) override;`
- L137 _public prototype_ `virtual bool SupportsMetadata() const override;` — Does this image type support embedded metadata in its header? PNG is an example of an image type which supports adding user-defined metadata to its header.
- L145 _public prototype_ `virtual void AddMetadata(const FString& InKey, const FString& InValue) override;` — Adds a key and value to this image's metadata.  Will be saved in the image's header and restored when the image is loaded. @param InKey Metadata consists of key value pairs. @param InValue Metadata consists of key value pairs.
- L152 _public prototype_ `virtual void GetMetadata(TStringMap& OutMetadata) const override;` — Copies this image's metadata to the caller's map. @param OutMetadata A copy of this image's metadata.
- L156 _protected function_ `int64 GetBytesPerPel() const`
- L157 _protected function_ `int64 GetBytesPerRow() const`
- L162 _protected prototype_ `bool GetImageViewOfSetRawForCompress(FImageView & OutImage) const;` — For writers: after SetRaw(), call this to get an ImageView of the raw data that was set can return false if the SetRaw does not map to an image format pixels point at the RawData array
- L165 _protected member_ `TArray64<uint8> RawData;` — Arrays of compressed/raw data
- L166 _protected member_ `TArray64<uint8> CompressedData;`
- L169 _protected member_ `ERGBFormat Format;` — Format of the raw data
- L170 _protected member_ `int BitDepth;`
- L173 _protected member_ `int64 Width;` — Width/Height of the image data
- L174 _protected member_ `int64 Height;`
- L177 _protected member_ `FString LastError;` — Last Error Message.

### `Source/Runtime/ImageWrapper/Private/ImageWrapperPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogImageWrapper, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogImageWrapper, Log, All);`

### `Source/Runtime/ImageWrapper/Public/BmpImageSupport.h` (Public)


#### enum `EBitmapCompression`  
`enum EBitmapCompression`  
_L11-20_
- desc: Bitmap compression types.
- L13 _public enumerator_ `BCBI_RGB = 0`
- L14 _public enumerator_ `BCBI_RLE8 = 1`
- L15 _public enumerator_ `BCBI_RLE4 = 2`
- L16 _public enumerator_ `BCBI_BITFIELDS = 3`
- L17 _public enumerator_ `BCBI_JPEG = 4`
- L18 _public enumerator_ `BCBI_PNG = 5`
- L19 _public enumerator_ `BCBI_ALPHABITFIELDS = 6`

#### enum `EBitmapHeaderVersion`  
`enum class EBitmapHeaderVersion : uint8`  
_L23-31_
- desc: Bitmap info header versions.
- L25 _public enumerator_ `BHV_BITMAPINFOHEADER = 0`
- L26 _public enumerator_ `BHV_BITMAPV2INFOHEADER = 1`
- L27 _public enumerator_ `BHV_BITMAPV3INFOHEADER = 2`
- L28 _public enumerator_ `BHV_BITMAPV4HEADER = 3`
- L29 _public enumerator_ `BHV_BITMAPV5HEADER = 4`
- L30 _public enumerator_ `BHV_INVALID = 0xFF`

#### enum `EBitmapCSType`  
`enum class EBitmapCSType : uint32`  
_L34-41_
- desc: Color space type of the bitmap, property introduced in Bitmap header version 4.
- L36 _public enumerator_ `BCST_BLCS_CALIBRATED_RGB = 0x00000000`
- L37 _public enumerator_ `BCST_LCS_sRGB = 0x73524742`
- L38 _public enumerator_ `BCST_LCS_WINDOWS_COLOR_SPACE = 0x57696E20`
- L39 _public enumerator_ `BCST_PROFILE_LINKED = 0x4C494E4B`
- L40 _public enumerator_ `BCST_PROFILE_EMBEDDED = 0x4D424544`

#### struct `FBitmapFileHeader`  
`struct FBitmapFileHeader`  
_L45-58_
- L47 _public member_ `uint16 bfType;`
- L48 _public member_ `uint32 bfSize;`
- L49 _public member_ `uint16 bfReserved1;`
- L50 _public member_ `uint16 bfReserved2;`
- L51 _public member_ `uint32 bfOffBits;`

#### struct `FBitmapInfoHeader`  
`struct FBitmapInfoHeader`  
_L63-112_
- L65 _public member_ `uint32 biSize;`
- L66 _public member_ `uint32 biWidth;`
- L67 _public member_ `int32 biHeight;`
- L68 _public member_ `uint16 biPlanes;`
- L69 _public member_ `uint16 biBitCount;`
- L70 _public member_ `uint32 biCompression;`
- L71 _public member_ `uint32 biSizeImage;`
- L72 _public member_ `uint32 biXPelsPerMeter;`
- L73 _public member_ `uint32 biYPelsPerMeter;`
- L74 _public member_ `uint32 biClrUsed;`
- L75 _public member_ `uint32 biClrImportant;`
- L87 _public function_ `EBitmapHeaderVersion GetHeaderVersion() const`

#### struct `FBitmapInfoHeaderV4`  
`struct FBitmapInfoHeaderV4`  
_L118-163_
- L120 _public member_ `uint32 biSize;`
- L121 _public member_ `uint32 biWidth;`
- L122 _public member_ `int32 biHeight;`
- L123 _public member_ `uint16 biPlanes;`
- L124 _public member_ `uint16 biBitCount;`
- L125 _public member_ `uint32 biCompression;`
- L126 _public member_ `uint32 biSizeImage;`
- L127 _public member_ `uint32 biXPelsPerMeter;`
- L128 _public member_ `uint32 biYPelsPerMeter;`
- L129 _public member_ `uint32 biClrUsed;`
- L130 _public member_ `uint32 biClrImportant;`
- L131 _public member_ `uint32 biRedMask;`
- L132 _public member_ `uint32 biGreenMask;`
- L133 _public member_ `uint32 biBlueMask;`
- L134 _public member_ `uint32 biAlphaMask;`
- L135 _public member_ `uint32 biCSType;`
- L136 _public member_ `int32 biEndPointRedX;`
- L137 _public member_ `int32 biEndPointRedY;`
- L138 _public member_ `int32 bibiEndPointRedZ;`
- L139 _public member_ `int32 bibiEndPointGreenX;`
- L140 _public member_ `int32 biEndPointGreenY;`
- L141 _public member_ `int32 biEndPointGreenZ;`
- L142 _public member_ `int32 biEndPointBlueX;`
- L143 _public member_ `int32 biEndPointBlueY;`
- L144 _public member_ `int32 biEndPointBlueZ;`
- L145 _public member_ `uint32 biGammaRed;`
- L146 _public member_ `uint32 biGammaGreen;`
- L147 _public member_ `uint32 biGammaBlue;`

#### struct `FBmiColorsMask`  
`struct FBmiColorsMask`  
_L169-173_
- desc: Used by InfoHeaders pre-version 4, a structure that is declared after the FBitmapInfoHeader.
- L172 _public member_ `uint32 RGBAMask[4];` — RGBA, in header pre-version 4, Alpha was only used as padding.

#### Free symbols / members of external scopes

- L53 _function_ `friend FArchive& operator<<( FArchive& Ar, FBitmapFileHeader& H )`
- L76 _function_ `friend FArchive& operator<<( FArchive& Ar, FBitmapInfoHeader& H )`
- L149 _function_ `friend FArchive& operator<<(FArchive& Ar, FBitmapInfoHeaderV4& H)`

### `Source/Runtime/ImageWrapper/Public/Formats/HdrImageWrapper.h` (Public)


#### class `FHdrImageWrapper`  
`class FHdrImageWrapper : public IImageWrapper`  
_L17-105_
- inherits: `IImageWrapper`
- desc: does not use ImageWrapperBase , unlike all other imagewrappers
- L22 _public prototype_ `bool SetCompressedFromView(TArrayView64<const uint8> Data);` — Todo we should have this for all image wrapper.
- L25 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) override;` — IIMageWrapper Interface begin
- L26 _public prototype_ `virtual bool SetRaw(const void* InRawData, int64 InRawSize, const int32 InWidth, const int32 InHeight, const ERGBFormat InFormat, const int32 InBitDepth, const int32 InBytesPerRow) override;`
- L27 _public prototype_ `virtual TArray64<uint8> GetCompressed(int32 Quality = 0) override;`
- L28 _public prototype_ `virtual bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, TArray64<uint8>& OutRawData) override;`
- L29 _public prototype_ `virtual bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, FDecompressedImageOutput& OutDecompressedImage) override;`
- L31 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const override;`
- L32 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const override;`
- L34 _public prototype_ `virtual int64 GetWidth() const override;`
- L35 _public prototype_ `virtual int64 GetHeight() const override;`
- L36 _public prototype_ `virtual int32 GetBitDepth() const override;`
- L37 _public prototype_ `virtual ERGBFormat GetFormat() const override;`
- L42 _public prototype_ `const FText& GetErrorMessage() const;` — GetErrorMessage : nice idea, but not virtual, never called by the standard import path
- L44 _public prototype_ `void FreeCompressedData();`
- L51 _public prototype_ `virtual bool SupportsMetadata() const override;` — Does this image type support embedded metadata in its header? PNG is an example of an image type which supports adding user-defined metadata to its header.
- L59 _public prototype_ `virtual void AddMetadata(const FString& InKey, const FString& InValue) override;` — Adds a key and value to this image's metadata.  Will be saved in the image's header and restored when the image is loaded. @param InKey Metadata consists of key value pairs. @param InValue Metadata consists of key value pairs.
- L66 _public prototype_ `virtual void GetMetadata(TStringMap& OutMetadata) const override;` — Copies this image's metadata to the caller's map. @param OutMetadata A copy of this image's metadata.
- L72 _private prototype_ `void SetAndLogError(const FText& InText);` — Helpers for error exits. Set error messages and return false.
- L73 _private prototype_ `bool FailHeaderParsing();` — also calls FreeCompressData.
- L74 _private prototype_ `bool FailUnexpectedEOB();`
- L75 _private prototype_ `bool FailMalformedScanline();`
- L77 _private prototype_ `bool GetHeaderLine(const uint8*& BufferPos, char Line[256]);`
- L79 _private prototype_ `static bool ParseMatchString(const char*& InOutCursor, const char* InExpected);`
- L80 _private prototype_ `static bool ParsePositiveInt(const char*& InOutCursor, int* OutValue);`
- L81 _private prototype_ `static bool ParseImageSize(const char* InLine, int* OutWidth, int* OutHeight);`
- L83 _private prototype_ `static bool HaveBytes(const uint8* InCursor, const uint8* InEnd, int InAmount);`
- L86 _private prototype_ `bool DecompressScanline(uint8* Out, const uint8*& In, const uint8* InEnd);` — @param Out order in bytes: RGBE
- L88 _private prototype_ `bool OldDecompressScanline(uint8* Out, const uint8*& In, const uint8* InEnd, int32 Length, bool bInitialRunAllowed);`
- L90 _private prototype_ `bool IsCompressedImageValid() const;`
- L92 _private member_ `TArrayView64<const uint8> CompressedData;`
- L93 _private member_ `const uint8* RGBDataStart = nullptr;`
- L95 _private member_ `TArray64<uint8> CompressedDataHolder;`
- L96 _private member_ `TArray64<uint8> RawDataHolder;`
- L99 _private member_ `int64 Width = INDEX_NONE;` — INDEX_NONE if not valid
- L101 _private member_ `int64 Height = INDEX_NONE;` — INDEX_NONE if not valid
- L104 _private member_ `FText ErrorMessage;` — Reported error

### `Source/Runtime/ImageWrapper/Public/IImageWrapper.h` (Public)


#### enum `EImageFormat`  
`enum class EImageFormat : int8`  
_L26-69_
- desc: Enumerates the types of image formats this class can handle.
- L29 _public enumerator_ `Invalid = -1` — Invalid or unrecognized format.
- L32 _public enumerator_ `PNG = 0` — Portable Network Graphics.
- L35 _public enumerator_ `JPEG` — Joint Photographic Experts Group.
- L38 _public enumerator_ `GrayscaleJPEG` — Single channel JPEG.
- L41 _public enumerator_ `BMP` — Windows Bitmap.
- L44 _public enumerator_ `ICO` — Windows Icon resource.
- L47 _public enumerator_ `EXR` — OpenEXR (HDR) image file format.
- L50 _public enumerator_ `ICNS` — Mac icon.
- L53 _public enumerator_ `TGA` — Truevision TGA / TARGA
- L56 _public enumerator_ `HDR` — Hdr file from radiance using RGBE
- L59 _public enumerator_ `TIFF` — Tag Image File Format files
- L62 _public enumerator_ `DDS` — DirectDraw Surface
- L65 _public enumerator_ `UEJPEG` — UE JPEG format.
- L68 _public enumerator_ `GrayscaleUEJPEG` — Single channel UE JPEG.

#### enum `ERGBFormat`  
`enum class ERGBFormat : int8`  
_L75-96_
- desc: Enumerates the types of RGB formats this class can handle.
- L77 _public enumerator_ `Invalid = -1`
- L80 _public enumerator_ `RGBA = 0` — Red, Green, Blue and Alpha ; requires RB swap from FColor
- L83 _public enumerator_ `BGRA = 1` — Blue, Green, Red and Alpha ; is ERawImageFormat::BGRA8 and Fcolor
- L86 _public enumerator_ `Gray = 2` — Gray scale
- L89 _public enumerator_ `RGBAF = 3` — Red, Green, Blue and Alpha using IEEE Floating-Point Arithmetic (see IEEE754). The format is always binary.
- L92 _public enumerator_ `BGRE = 4` — Blue, Green, Red and Exponent (Similar to the RGBE format from radiance but with the blue and red channel inversed)
- L95 _public enumerator_ `GrayF = 5` — Gray scale using IEEE Floating-Point Arithmetic (see IEEE754). The format is always binary.

#### enum `EImageCompressionQuality`  
`enum class EImageCompressionQuality : int8`  
_L112-117_
- desc: Enumerates available image compression qualities. JPEG interprets Quality as 1-100 JPEG default quality is 85 , Uncompressed means 100 for PNG: Negative qualities in [-1,-9] set PNG zlib level PNG interprets "Uncompressed" as zlib level 0 (none) otherwise default zlib level 3 is used. EXR respects the "Uncompressed" flag to turn off compression; otherwise ZIP_COMPRESSION is used.
- L114 _public enumerator_ `Default = 0`
- L115 _public enumerator_ `Uncompressed = 1`
- L116 _public enumerator_ `Max = 100`

#### class `IImageWrapper`  
`class IImageWrapper`  
_L131-463_
- desc: Interface for image wrappers. to Encode: SetRaw() then GetCompressed() to Decode : SetCompressed() then GetRaw() in general, direct use of the IImageWrapper interface is now discouraged use ImageWrapperModule CompressImage/DecompressImage instead.
- L135 _protected member_ `const TCHAR* DebugImageName = nullptr;` — debug image name string for any errors or warnings
- L151 _public prototype_ `virtual bool SetCompressed(const void* InCompressedData, int64 InCompressedSize) = 0;` — Sets the compressed data.  Can then call GetRaw(). @param InCompressedData The memory address of the start of the compressed data. @param InCompressedSize The size of the compressed data parsed. @return true if data was the expected format. after SetCompressed, image info queries like GetWidth and GetBitDepth are allowed call GetRaw to get the decoded bits decompression is not done until GetRaw
- L171 _public prototype_ `virtual bool SetRaw(const void* InRawData, int64 InRawSize, const int32 InWidth, const int32 InHeight, const ERGBFormat InFormat, const int32 InBitDepth, const int32 InBytesPerRow = 0) = 0;` — Sets the raw image data.  Prepares to call GetCompressed() next. @param InRawData The memory address of the start of the raw data. @param InRawSize The size of the compressed data parsed. @param InWidth The width of the image data. @param InHeight the height of the image data. @param InFormat the format the raw data is in, normally RGBA. @param InBitDepth the bit-depth per channel, normally 8. @param InBytesPerRow the number of bytes between rows, 0 = tightly packed rows with no padding. @return true if data was the expected format. you must not SetRaw() with a format unless it passes CanSetRawFormat() deprecated : avoid direct calls to SetRaw(), use ImageWrapperModule CompressImage instead do not use InBytesPerRow, it is ignored SetRaw does not take gamma information assumes U8 = SRGB and all else = Linear
- L174 _public prototype_ `virtual bool CanSetRawFormat(const ERGBFormat InFormat, const int32 InBitDepth) const = 0;` — CanSetRawFormat returns true if SetRaw will accept this format
- L180 _public prototype_ `virtual ERawImageFormat::Type GetSupportedRawFormat(const ERawImageFormat::Type InFormat) const = 0;` — returns InFormat if supported, else maps to something supported the returned format will pass CanSetRawFormat()
- L190 _public prototype_ `virtual TArray64<uint8> GetCompressed(int32 Quality = 0) = 0;` — Gets the compressed data.  (call SetRaw first) (Note: It may consume the data set in the SetCompressed function if it was set before) @return Array of the compressed data.  returns empty array on failure
- L199 _public function_ `virtual TArray64<uint8> GetExportData(int32 Quality = 0)` — Gets the data for export. Usually the same thing as GetCompressed. @return Array of the data to export.  returns empty array on failure
- L213 _public function_ `bool GetRaw(TArray64<uint8>& OutRawData)` — GetRaw after SetCompressed fills the raw data in the native format/depth contained in the file Do not use the GetRaw() variants that take format/depth arguments. @param OutRawData    Filled with raw image data. This GetRaw call replaces the variants with format/depth arguments, but prefer GetRawImage instead.
- L237 _public function_ `bool GetRaw(FDecompressedImageOutput& OutDecompressedImage)` — GetRaw after SetCompressed fills the raw data in the native format/depth contained in the file along with meta info Do not use the GetRaw() variants that take format/depth arguments. @param OutRawData				Filled with raw image data. @param OutDecompressedImage		Filled with mip images and other metadata. This GetRaw call replaces the variants with format/depth arguments, but prefer GetRawImage instead.
- L262 _public prototype_ `bool GetRawImage(FImage & OutImage);` — Decode the image file data from SetCompressed() into an FImage OutImage is allocated and attributes are filled Any previous passed-in contents of OutImage are destroyed OutImage.Format is ignored, a new format is set from the loaded image @param OutImage	 Filled with the image This is the recommended API to get the raw image data from the imagewrapper. Prefer this instead of any of the GetRaw() calls.
- L276 _public prototype_ `bool GetRawImage(FDecompressedImageOutput& OutDecompressedImage);` — Decode the image file data from SetCompressed() into an FImage OutImage is allocated and attributes are filled. Any previous passed-in contents of OutImage are destroyed. OutImage.Format is ignored, a new format is set from the loaded image MetaInfo is filled if applicable @param OutDecompressedImage	Image and meta data along with Mip Map Images This is the recommended API to get the raw image data from the imagewrapper. Prefer this instead of any of the GetRaw() calls.
- L291 _public prototype_ `virtual bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, TArray64<uint8>& OutRawData) = 0;` — Gets the raw data. (Note: It may consume the data set in the SetRaw function if it was set before) @param InFormat How we want to manipulate the RGB data. @param InBitDepth The output bit-depth per channel, normally 8. @param OutRawData Will contain the uncompressed raw data. @return true on success, false otherwise. this is often broken, should only be used with InFormat == GetFormat() DEPRECATED , use GetRaw() with 1 argument or GetRawImage()
- L306 _public prototype_ `virtual bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, FDecompressedImageOutput& OutDecompressedImage) = 0;` — Gets the raw data and meta info (Note: It may consume the data set in the SetRaw function if it was set before) @param InFormat How we want to manipulate the RGB data. @param InBitDepth The output bit-depth per channel, normally 8. @param OutRawData Will contain the uncompressed raw data. @param OutDecompressedImage Will contain the mip images if available and other metadata. @return true on success, false otherwise. this is often broken, should only be used with InFormat == GetFormat() DEPRECATED , use GetRaw() with 2 argument or GetRawImage() meta info overload
- L321 _public function_ `bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, TArray<uint8>& OutRawData)` — Gets the raw data in a TArray. Only use this if you're certain that the image is less than 2 GB in size. Prefer using the overload which takes a TArray64 in general. (Note: It may consume the data set in the SetRaw function if it was set before) @param InFormat How we want to manipulate the RGB data. @param InBitDepth The output bit-depth per channel, normally 8. @param OutRawData Will contain the uncompressed raw data. @return true on success, false otherwise. this is often broken, should only be used with InFormat == GetFormat() DEPRECATED , use GetRaw() with 1 argument or GetRawImage()
- L347 _public function_ `bool GetRaw(const ERGBFormat InFormat, int32 InBitDepth, TArrayView64<uint8> OutRawData)` — Get the raw version of the image and write to the array view (Note: It may consume the data set in the SetRaw function if it was set before) @param InFormat How we want to manipulate the RGB data. @param InBitDepth The output bit-depth per channel, normally 8. @param OutRawData Will contain the uncompressed raw data. @return true on success, false otherwise. this is often broken, should only be used with InFormat == GetFormat() DEPRECATED , use GetRaw() with 1 argument or GetRawImage()
- L368 _public prototype_ `virtual int64 GetWidth() const = 0;` — Gets the width of the image. @return Image width. @see GetHeight
- L376 _public prototype_ `virtual int64 GetHeight() const = 0;` — Gets the height of the image. @return Image height. @see GetWidth
- L386 _public prototype_ `virtual int32 GetBitDepth() const = 0;` — Gets the bit depth of the image. @return The bit depth per-channel of the image. Beware several of the old wrappers (BMP,TGA) incorrectly used to return bits per *color* not per channel they now correctly return per-channel.
- L394 _public prototype_ `virtual ERGBFormat GetFormat() const = 0;` — Gets the format of the image. Theoretically, this is the format it would be best to call GetRaw() with, if you support it. @return The format the image data is in
- L403 _public function_ `bool GetSRGB() const` — Should the pixels be treated as sRGB encoded? (or Linear) note: ImageWrapper Format does not track if pixels are Gamma/SRGB or not assume they are ERawImageFormat::GetDefaultGammaSpace gammaspace eg. U8 is SRGB and everything else is Linear
- L412 _public prototype_ `static void ConvertRawImageFormat(ERawImageFormat::Type RawFormat, ERGBFormat & OutFormat,int & OutBitDepth);` — external users call these from ImageWrapperModule.h , see documentation there
- L413 _public prototype_ `static ERawImageFormat::Type ConvertRGBFormat(ERGBFormat RGBFormat,int BitDepth,bool * bIsExactMatch = nullptr);`
- L415 _public prototype_ `static int64 GetRGBFormatBytesPerPel(ERGBFormat RGBFormat,int BitDepth);`
- L421 _public function_ `ERawImageFormat::Type GetClosestRawImageFormat(bool * bIsExactMatch = nullptr) const` — get the current image format, mapped to an ERawImageFormat if ! *bIsExactMatch , conversion is needed can call after SetCompressed()
- L431 _public function_ `void SetDebugImageName(const TCHAR* InDebugImageName)` — Set the debug image name
- L441 _public prototype_ `virtual bool SupportsMetadata() const = 0;` — Does this image type support embedded metadata in its header? PNG is an example of an image type which supports adding user-defined metadata to its header.
- L449 _public prototype_ `virtual void AddMetadata(const FString& InKey, const FString& InValue) = 0;` — Adds a key and value to this image's metadata.  Will be saved in the image's header and restored when the image is loaded. @param InKey Metadata consists of key value pairs. @param InValue Metadata consists of key value pairs.
- L451 _public typedef_ `using TStringMap = TMap<FString, FString>;`
- L457 _public prototype_ `virtual void GetMetadata(TStringMap& OutMetadata) const = 0;` — Copies this image's metadata to the caller's map. @param OutMetadata A copy of this image's metadata.
- L462 _public prototype_ `virtual ~IImageWrapper() = default;` — Virtual destructor.

### `Source/Runtime/ImageWrapper/Public/IImageWrapperModule.h` (Public)


#### class `IImageWrapperModule`  
`class IImageWrapperModule : public IModuleInterface`  
_L48-139_
- inherits: `IModuleInterface`
- desc: Interface for image wrapper modules. DO NOT WRITE CODE THAT USES IMAPE WRAPPERS DIRECTLY. If you have "Engine" module, then just use FImageUtils::CompressImage/DecompressImage The easiest way to load/save an image is FImageUtils::LoadImage/SaveImageByExtension If you don't have "Engine" module, then use IImageWrapperModule::CompressImage/DecompressImage Do not manually create individual image wrappers. NOTE: Please prefer to work with images through ImageCore FImage/FImageView (not TextureSource/TextureSourceFormat or raw arrays of bytes) again, do not manually use ERGBFormat and arrays of bytes to work with ImageWrappers instead use the FImage-oriented APIs which will handle all format conversions for you. You do NOT need to convert formats before saving an image, the FImage APIs will do it for you. If you got an image from a render target, it may have a zero alpha channel.  You might want to do FImageCore::SetAlphaOpaque before saving. note on SRGB/Gamma handling : it is assumed that non-U8 data is always Linear U8 data is written without changing the bytes the gamma correction of U8 bytes is NOT persisted in the file formats (for read or write) loading will always give you SRGB for U8 (ERawImageFormat::GetDefaultGammaSpace) if U8-float conversions are required, they do respect gamma space eg. if you write U8 Linear data to EXR, it will be converted to Linear float from U8 Linear correctly if you write U8 Linear to BMP , it will write the U8 bytes unchanged, and on load it 
- L67 _public prototype_ `virtual bool CompressImage(TArray64<uint8> & OutData, EImageFormat ToFormat, const FImageView & InImage, int32 Quality = 0) = 0;` — Convert input FImage into a file-format encoded array. in ImageWrapper land, "Compress" means "put in file format" OutData is filled with the file format encoded data lossy conversion of the pixel type may be done if necessary eg. if you pass F32 float pixels to write to BMP, they will be converted to SRGB U8 BGRA8 @param OutData		Filled with image-format data @param ToFormat		Image format to encode to @param InImage		Image to encode @param Quality		50-100 for JPEG, or EImageCompressionQuality
- L77 _public prototype_ `virtual bool DecompressImage(const void* InCompressedData, int64 InCompressedSize, FImage & OutImage) = 0;` — Read an image from file format encoded data. ImageWrapper calls this a "decompress" OutImage is allocated and filled, any existing contents are discarded @param InCompressedData	Image format encoded bytes to read; format is automatically deduced from the content @param InCompressedSize	Size of InCompressedData in bytes @param OutImage			Filled with Image that is read.  Allocated.
- L87 _public prototype_ `virtual bool DecompressImage(const void* InCompressedData, int64 InCompressedSize, FDecompressedImageOutput& OutDecompressedImage) = 0;` — Read an image from file format encoded data. ImageWrapper calls this a "decompress" OutImage is allocated and filled, any existing contents are discarded @param InCompressedData					Image format encoded bytes to read; format is automatically deduced from the content @param InCompressedSize					Size of InCompressedData in bytes @param OutDecompressedImageData			Filled with Image along with other meta data and mip images that is read.  Allocated.
- L99 _public prototype_ `virtual TSharedPtr<IImageWrapper> CreateImageWrapper(const EImageFormat InFormat, const TCHAR* InOptionalDebugImageName = nullptr) = 0;` — Create an IImageWrapper helper of a specific type @param InFormat - The type of image we want to deal with @param InOptionalDebugImageName - An optional string to be displayed with any errors or warnings @return The helper base class to manage the data EImageFormat is a compressor / file format, not a pixel format Deprecated.  Prefer CompressImage/DecompressImage.
- L109 _public prototype_ `virtual EImageFormat DetectImageFormat(const void* InCompressedData, int64 InCompressedSize) = 0;` — Detect image format by looking at the first few bytes of the compressed image data. You can call this method as soon as you have 8-16 bytes of compressed file content available. @param InCompressedData The raw image header. @param InCompressedSize The size of InCompressedData. @return the detected format or EImageFormat::Invalid if the method could not detect the image format.
- L114 _public prototype_ `virtual EImageFormat GetImageFormatFromExtension(const TCHAR * Name) = 0;` — Name can be a full name like "xx.png" or just the extension part, like "png" returns EImageFormat::Invalid if no supported image extension found
- L117 _public prototype_ `virtual const TCHAR * GetExtension(EImageFormat Format) = 0;` — returns extension, not including the "." , 3 or 4 chars
- L120 _public prototype_ `virtual EImageFormat GetDefaultOutputFormat(ERawImageFormat::Type RawFormat) = 0;` — get a good default output image format for a pixel format
- L127 _public prototype_ `virtual ERawImageFormat::Type ConvertRGBFormat(ERGBFormat Format,int BitDepth,bool * bIsExactMatch = nullptr) = 0;` — Convert an ImageWrapper style {ERGBFormat+BitDepth} into an ERawImageFormat for FImage returns ERawImageFormat::Invalid if no mapping is possible bIsExactMatch is filled with whether the formats are an exact match or not if not, conversion is needed
- L133 _public prototype_ `virtual void ConvertRawImageFormat(ERawImageFormat::Type RawFormat, ERGBFormat & OutFormat,int & OutBitDepth) = 0;` — Convert an FImage ERawImageFormat into an ImageWrapper style {ERGBFormat+BitDepth} mapping is always possible and requires no conversion
- L138 _public prototype_ `virtual ~IImageWrapperModule() = default;` — Virtual destructor.

### `Source/Runtime/ImageWrapper/Public/ImageWrapperHelper.h` (Public)


#### class `ImageWrapperHelper`  
`class ImageWrapperHelper`  
_L9-20_
- desc: ImageWrapperHelper is deprecated, use IImageWrapperModule instead
- L14 _public prototype_ `static FStringView GetFormatExtension(EImageFormat InImageFormat, bool bIncludeDot=false);` — deprecated, use IImageWrapperModule::GetExtension() instead
- L17 _public prototype_ `static EImageFormat GetImageFormat(FStringView StringExtention);` — deprecated, use IImageWrapperModule::GetImageFormatFromExtension instead
- L19 _public prototype_ `static const FStringView GetImageFilesFilterString(bool bIncludeAllFiles);`

### `Source/Runtime/ImageWrapper/Public/ImageWrapperOutputTypes.h` (Public)


#### struct `FDecompressedImageOutput`  
`struct FDecompressedImageOutput`  
_L10-18_
- desc: Use this struct to get mip images and other metadata about the image.
- L12 _public member_ `FMipMapImage MipMapImage;`
- L15 _public member_ `FString ApplicationVendor;` — Meta data
- L16 _public member_ `FString ApplicationName;`
- L17 _public member_ `FString ApplicationVersion;`

### `Source/Runtime/ImageWrapper/Public/TgaImageSupport.h` (Public)


#### struct `FTGAFileHeader`  
`struct FTGAFileHeader`  
_L10-33_
- L12 _public member_ `uint8 IdFieldLength;`
- L13 _public member_ `uint8 ColorMapType;`
- L14 _public member_ `uint8 ImageTypeCode;` — 2 for uncompressed RGB format
- L15 _public member_ `uint16 ColorMapOrigin;`
- L16 _public member_ `uint16 ColorMapLength;`
- L17 _public member_ `uint8 ColorMapEntrySize;`
- L18 _public member_ `uint16 XOrigin;`
- L19 _public member_ `uint16 YOrigin;`
- L20 _public member_ `uint16 Width;`
- L21 _public member_ `uint16 Height;`
- L22 _public member_ `uint8 BitsPerPixel;`
- L23 _public member_ `uint8 ImageDescriptor;`

#### Free symbols / members of external scopes

- L25 _function_ `friend FArchive& operator<<( FArchive& Ar, FTGAFileHeader& H )`
- L40 _prototype_ `bool DecompressTGA_helper( const FTGAFileHeader* TGA, const int64 TGABufferLength, uint32* TextureData, const int64 TextureDataSize );` — This helper allows to decompress TGA data in a pre-allocated memory block. The pixel format is necessarily PF_A8R8G8B8.
