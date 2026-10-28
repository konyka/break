# Plugins / ExrReaderGpu

- module root: `Plugins/Media/ImgMedia/Source/ExrReaderGpu`
- headers: 3; symbols: 38
- symbol kinds: class=4, delegate=1, enum=1, enumerator=3, function=2, member=10, prototype=15, struct=1, typedef=1
- PrivateDependencyModuleNames: OpenExrWrapper
- PublicDependencyModuleNames: Core, CoreUObject, Projects, RenderCore

### `Plugins/Media/ImgMedia/Source/ExrReaderGpu/Public/ExrReaderGpu.h` (Public)


#### class `FExrReader`  
`class FExrReader`  
_L16-133_
- desc: This class is a collection of distant and compressed takes on OpenExr's ScanLineInputFile and ReadPixel functionality.
- L41 _private member_ `static const int32 STRING_SIZE = 256;`
- L42 _private member_ `static const int32 MAX_LENGTH = STRING_SIZE - 1;`
- L46 _public member_ `static const int32 PLANAR_RGB_SCANLINE_PADDING = 8;` — At the beginning of each row of B G R channel planes there is 2x4 byte data that has information
- L48 _public member_ `static const int32 TILE_PADDING = 20;` — At the beginning of each tile there is 20 byte data that has information
- L51 _public function_ `FExrReader() : FileHandle(nullptr) , FileLength(0) , LineOrTileOffsetsPerLevel()`
- L58 _private prototype_ `static bool ReadMagicNumberAndVersionField(FILE* FileHandle);`
- L65 _private prototype_ `static bool ReadHeaderData(FILE* FileHandle);` — This is just so we can get line offsets. Based on OpenExr implementation with some caveats. The header in general is discarded, but without reading it - it is impossible to get to the actual pixel data reliably. Returns false if it has failed reading the file in any way.
- L68 _private prototype_ `static bool ReadLineOrTileOffsets(FILE* FileHandle, ELineOrder LineOrder, TArray<int64>& LineOrTileOffsets);` — Reads Scan line offsets so that we can jump to a position in file.
- L73 _public prototype_ `static bool GenerateTextureData(uint16* Buffer, int32 BufferSize, FString FilePath, int32 NumberOfScanlines, int32 NumChannels);` — Discards the header and fills the buffer with plain pixel data.
- L79 _public prototype_ `static void CalculateTileOffsets ( TArray<int32>& OutNumTilesPerLevel , TArray<TArray<FTileDesc>>& OutPartialTileInfo , const FIntPoint& FullTextureResolution , const FIntPoint& TileDimWithBorders , int32 NumMipLevels , int64 PixelSize);` — To be able to read tiles, especially in cases where tiles vary in sizes, we need to calculate offsets manually for custom exr files, since we don't write out offsets.
- L92 _public prototype_ `bool OpenExrAndPrepareForPixelReading(FString FilePath, const TArray<int32>& NumOffsetsPerLevel);` — This function is used to open file and keep a handle to it so the file can be read in chunks. Reading in chunks allows the process of reading to be canceled midway through reading. This function reads and discards the header and keeps the pointers to the scanlines or tiles.
- L98 _public prototype_ `bool ReadExrImageChunk(void* Buffer, int64 ChunkSize);` — Read a chunk of an Exr file previously open via OpenExrAndPrepareForPixelReading. The read starts from the last point of file reading.
- L103 _public prototype_ `bool SeekTileWithinFile(const int32 StartTileIndex, const int32 Level, int64& OutBufferOffset);` — Moves to the specified tile position in the file in preparation for reading.
- L108 _public prototype_ `bool GetByteOffsetForTile(const int32 TileIndex, const int32 Level, int64& OutBufferOffset);` — Gets byte location of the requested tile for the requested mip level.
- L114 _public prototype_ `bool CloseExrFile();` — After we have finished reading the file that was open via OpenExrAndPrepareForPixelReading We need to close it to avoid memory leaks
- L122 _private member_ `FILE* FileHandle;` — One approach to reading is to first open a file, read in chunks and then close the file. It is all done in 3 sepate functions and requires to keep track of Filehandle
- L127 _private member_ `int64 FileLength;` — The length of the file in question. Used to get the last tile.
- L132 _private member_ `TArray<TArray<int64>> LineOrTileOffsetsPerLevel;` — These are byte offsets pointing to scanlines or tiles from the begining of the file.

#### struct `FExrReader::FTileDesc`  
`struct FTileDesc`  
_L20-27_
- L22 _public member_ `FIntPoint TileResolution;`
- L23 _public member_ `uint32 BufferOffset;`
- L26 _public member_ `int32 AlignPadding;` — Optimization: align to 128 bit.

#### enum `FExrReader::ELineOrder`  
`enum ELineOrder`  
_L34-39_
- desc: This is based on Open Exr implementation. We need to handle all of these in the future. At the moment only INCREASING_Y is supported.
- L36 _public enumerator_ `INCREASING_Y`
- L37 _public enumerator_ `DECREASING_Y`
- L38 _public enumerator_ `RANDOM_Y` — Tiled files.

### `Plugins/Media/ImgMedia/Source/ExrReaderGpu/Public/ExrReaderGpuModule.h` (Public)


#### class `FExrReaderGpuModule`  
`class FExrReaderGpuModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation start
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogExrReaderGpu, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogExrReaderGpu, Log, All);`

### `Plugins/Media/ImgMedia/Source/ExrReaderGpu/Public/ExrSwizzlingShader.h` (Public)


#### class `FExrSwizzleVS`  
`class FExrSwizzleVS : public FGlobalShader`  
_L13-22_
- inherits: `FGlobalShader`
- desc: The vertex shader used by DrawScreenPass to draw a rectangle.
- L18 _public prototype_ `FExrSwizzleVS() = default;`
- L19 _public function_ `FExrSwizzleVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)`

#### class `FExrSwizzlePS`  
`class FExrSwizzlePS : public FGlobalShader`  
_L25-47_
- inherits: `FGlobalShader`
- desc: Pixel shader swizzle RGB planar buffer data into proper RGBA texture.
- L28 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FExrSwizzlePS, FGlobalShader);`
- L34 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FRgbaSwizzle, FRenderTiles, FPartialTiles>;`
