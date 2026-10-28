# Plugins / OpenExrWrapper

- module root: `Plugins/Media/ImgMedia/Source/OpenExrWrapper`
- headers: 5; symbols: 105
- symbol kinds: class=9, delegate=1, function=5, macro=1, member=16, prototype=72, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, TimeManagement, TmvMedia

### `Plugins/Media/ImgMedia/Source/OpenExrWrapper/Private/OpenExrWrapperLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenEXRWrapper, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenEXRWrapper, Log, All);`

### `Plugins/Media/ImgMedia/Source/OpenExrWrapper/Private/OpenExrWrapperTmvEncoder.h` (Private)


#### class `FOpenExrWrapperTmvEncoder`  
`class FOpenExrWrapperTmvEncoder : public ITmvMediaEncoder`  
_L11-34_
- inherits: `ITmvMediaEncoder`
- desc: Implementation of a TMV encoder for the OpenExr.
- L14 _public prototype_ `FOpenExrWrapperTmvEncoder(const FOpenExrWrapperTmvEncoderOptions& InEncoderOptions);`
- L18 _public prototype_ `virtual ETmvMediaEncoderResult RequestMipInfos( const FTmvMediaFrameTimeInfo& InTimeInfo, const FTmvMediaEncoderMipInfo& InFrameInfo, TArray<FTmvMediaFrameMipInfo>& OutFrameMipInfo, FTmvMediaMessageContext* OutMessageContext) override;`
- L24 _public prototype_ `virtual ETmvMediaEncoderResult Encode( const FTmvMediaFrameTimeInfo& InTimeInfo, ITmvMediaEncoderAccessUnit& InAccessUnit, TArrayView<FTmvMediaEncoderMipRequest> InMipRequests, FTmvMediaMessageContext* OutMessageContext) override;`
- L33 _private member_ `FOpenExrWrapperTmvEncoderOptions EncoderOptions;` — Current encoder options

### `Plugins/Media/ImgMedia/Source/OpenExrWrapper/Private/OpenExrWrapperTmvEncoderFactory.h` (Private)


#### class `FOpenExrWrapperTmvEncoderFactory`  
`class FOpenExrWrapperTmvEncoderFactory : public ITmvMediaEncoderFactory`  
_L8-23_
- inherits: `ITmvMediaEncoderFactory`
- desc: Implementation of OpenExr Tmv Encoder Factory.
- L11 _public prototype_ `virtual ~FOpenExrWrapperTmvEncoderFactory() override = default;`
- L14 _public prototype_ `virtual FName GetName() const override;`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public function_ `virtual bool SupportsMemoryAccessUnit() const override`
- L17 _public prototype_ `virtual void GetEncoderOptions(TInstancedStruct<FTmvMediaEncoderOptions>& OutOptions) const override;`
- L18 _public prototype_ `virtual TSharedPtr<ITmvMediaEncoder, ESPMode::ThreadSafe> CreateEncoder(const FString& InCodecFormat, const TInstancedStruct<FTmvMediaEncoderOptions>& InOptions) override;`
- L22 _public member_ `static const FLazyName EncoderName;` — Encoder Name.

### `Plugins/Media/ImgMedia/Source/OpenExrWrapper/Private/OpenExrWrapperTmvEncoderOptions.h` (Private)


#### struct `FOpenExrWrapperTmvEncoderOptions`  
`struct FOpenExrWrapperTmvEncoderOptions : public FTmvMediaEncoderOptions`  
_L15-63_
- reflection: `USTRUCT(DisplayName = "OpenExr Tmv Encoder Options")`
- inherits: `FTmvMediaEncoderOptions`
- desc: OpenExr Tmv Encoder options.
- L19 _public prototype_ `FOpenExrWrapperTmvEncoderOptions();`
- L20 _public prototype_ `virtual ~FOpenExrWrapperTmvEncoderOptions() override = default;`
- L23 _public function_ `virtual FName GetEncoderName() const override`
- L24 _public function_ `virtual FString GetFileSequenceExtension() const override`
- L28 _public function_ `bool IsTilingEnabled() const` — Returns true if tiling is enabled.
- L35 _public member_ `bool bEnableTiling = true;` — `UPROPERTY(EditAnywhere, Category = Tiles)` — If checked, then enable tiling.
- L39 _public member_ `int32 TileSizeX = 256;` — `UPROPERTY(EditAnywhere, Category = Tiles, meta = (EditCondition = "bEnableTiling", ClampMin = "0.0"))` — Width of a tile in pixels. If 0, then do not make tiles.
- L43 _public member_ `int32 TileSizeY = 256;` — `UPROPERTY(EditAnywhere, Category = Tiles, meta = (EditCondition = "bEnableTiling", ClampMin = "0.0"))` — Height of a tile in pixels. If 0, then do not make tiles.
- L47 _public member_ `int32 NumThreads = 0;` — `UPROPERTY(EditAnywhere, Category = "Advanced", meta = (ClampMin = "0.0"))` — Number of worker thread to encode tiles (0 = automatically use the available number of cores).
- L54 _public member_ `bool bRemoveAlphaChannel = false;` — `UPROPERTY(EditAnywhere, Category = Channels)` — This option removes alpha channel. Since alpha channel adds 25% reading cost, it is suggested to have alpha channel removed if it is not used.
- L58 _public member_ `bool bEnableMipLevelTint = false;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Tint each mip level a different colour to help with debugging.
- L62 _public member_ `TArray<FLinearColor> MipLevelTints;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Color to tint each mip level.

### `Plugins/Media/ImgMedia/Source/OpenExrWrapper/Public/OpenExrWrapper.h` (Public)


#### class `FOpenExr`  
`class FOpenExr`  
_L14-19_
- L18 _public prototype_ `static void SetGlobalThreadCount(uint16 ThreadCount);`

#### class `FRgbaInputFile`  
`class FRgbaInputFile`  
_L22-61_
- L26 _public prototype_ `FRgbaInputFile(const FString& FilePath);`
- L27 _public prototype_ `FRgbaInputFile(const FString& FilePath, uint16 ThreadCount);`
- L28 _public prototype_ `~FRgbaInputFile();`
- L32 _public prototype_ `const TCHAR* GetCompressionName() const;`
- L33 _public prototype_ `FIntPoint GetDataWindow() const;`
- L34 _public prototype_ `FIntRect GetDataWindowRect() const;`
- L35 _public prototype_ `FIntRect GetDisplayWindow() const;`
- L36 _public prototype_ `FFrameRate GetFrameRate(const FFrameRate& DefaultValue) const;`
- L37 _public prototype_ `int32 GetUncompressedSize() const;`
- L38 _public prototype_ `int32 GetNumChannels() const;`
- L41 _public prototype_ `bool GetTileSize(FIntPoint& OutTileSize) const;` — Gets tile dimensions. Returns false if image has no tiles.
- L43 _public prototype_ `bool IsComplete() const;`
- L44 _public prototype_ `bool HasInputFile() const;`
- L45 _public prototype_ `void ReadPixels(int32 StartY, int32 EndY);`
- L46 _public prototype_ `void SetFrameBuffer(void* Buffer, const FIntPoint& Stride);`
- L56 _public prototype_ `bool GetIntAttribute(const FString& Name, int32& Value);` — Get an attribute from the image. @param Name		Name of attribute. @param Value		Will be set to the value of the attribute if the attribute is found. Will NOT be set if the attribute is not found. @return			True if the attribute was found, false otherwise.
- L60 _private member_ `void* InputFile;`

#### class `FExrInputFile`  
`class FExrInputFile`  
_L67-108_
- desc: Reads EXR files with per-channel control using the general Imf::InputFile API. Unlike FRgbaInputFile, this allows selecting specific named channels for each RGBA output slot.
- L71 _public prototype_ `FExrInputFile(const FString& FilePath, uint16 ThreadCount);`
- L72 _public prototype_ `~FExrInputFile();`
- L76 _public prototype_ `bool HasInputFile() const;`
- L77 _public prototype_ `FIntPoint GetDataWindow() const;`
- L95 _public prototype_ `void ReadPixels( void* Buffer, const FIntPoint& BufferDim, const FString& ChannelR, const FString& ChannelG, const FString& ChannelB, const FString& ChannelA, int32 StartY, int32 EndY);` — Read specific channels into an RGBA half-float (uint16) interleaved buffer. Each channel parameter is a full EXR channel name (e.g., "R", "beauty.G", "Zdepth.Z"). Empty string means fill with a default value (0 for RGB slots, 1 for A slot). The same channel name may be used for multiple slots (e.g., all RGB = "Zdepth.Z" for grayscale). @param Buffer		Destination buffer, must hold BufferDim.X * BufferDim.Y * 4 * sizeof(uint16) bytes. @param BufferDim		Width and height of the buffer (used for stride calculation). @param ChannelR		EXR channel name to read into the R slot. @param ChannelG		EXR channel name to read into the G slot. @param ChannelB		EXR channel name to read into the B slot. @param ChannelA		EXR channel name to read into the A slot. @param StartY		First scanline to read (0-based, relative to data window). @param EndY			Last scanline to read (inclusive, 0-based, relative to data window).
- L107 _private member_ `void* InputFile;`

#### class `FOpenExrHeaderReader`  
`class FOpenExrHeaderReader`  
_L111-158_
- L115 _public prototype_ `FOpenExrHeaderReader(const FString& FilePath);`
- L116 _public prototype_ `~FOpenExrHeaderReader();`
- L120 _public prototype_ `const TCHAR* GetCompressionName() const;`
- L121 _public prototype_ `FIntPoint GetDataWindow() const;`
- L122 _public prototype_ `FFrameRate GetFrameRate(const FFrameRate& DefaultValue) const;`
- L123 _public prototype_ `int64 GetUncompressedSize() const;`
- L124 _public prototype_ `int64 GetUncompressedMipSize(int32 InMipLevel) const;`
- L125 _public prototype_ `int32 GetNumChannels() const;`
- L126 _public prototype_ `int32 GetPixelSize() const;`
- L127 _public prototype_ `bool ContainsMips() const;`
- L128 _public prototype_ `int32 GetNumMipLevels() const;`
- L129 _public prototype_ `int32 CalculateNumMipLevels(const FIntPoint& NumTiles) const;`
- L132 _public prototype_ `bool IsOptimizedForGpu() const;` — Determines if Gpu reader can be utilized.
- L135 _public prototype_ `bool GetTileSize(FIntPoint& OutTileSize) const;` — Gets tile dimensions. Returns false if image has no tiles.
- L137 _public prototype_ `bool HasInputFile() const;`
- L147 _public prototype_ `bool GetIntAttribute(const FString& Name, int32& Value);` — Get an attribute from the image. @param Name		Name of attribute. @param Value		Will be set to the value of the attribute if the attribute is found. Will NOT be set if the attribute is not found. @return			True if the attribute was found, false otherwise.
- L154 _public prototype_ `void GetChannelNames(TArray<FString>& OutChannelNames) const;` — Get the names of all channels in the file. @param OutChannelNames Will contain all channel names (e.g., "R", "G", "B", "Zdepth.Z").
- L157 _private member_ `TSharedPtr<void> FileContext;`

#### class `FBaseOutputFile`  
`class FBaseOutputFile`  
_L163-204_
- desc: Base class for our classes that output EXR files.
- L174 _public prototype_ `FBaseOutputFile( const FIntPoint& DisplayWindowMin, const FIntPoint& DisplayWindowMax, const FIntPoint& DataWindowMin, const FIntPoint& DataWindowMax);` — Constructor. @param DisplayWindowMin		Normally (0, 0). @param DisplayWindowMax		Normally (width - 1, height - 1). @param DataWindowMin			Normally (0, 0). @param DataWindowMax			Normally (width - 1, height - 1).
- L183 _public prototype_ `virtual ~FBaseOutputFile();` — Destructor.
- L192 _public prototype_ `void AddIntAttribute(const FString& Name, int32 Value);` — Call this to add an attribute to the EXR file. This MUST be called before CreateOutputFile. @param Name		Name for this attribute. @param Value		Value for this attribute.
- L197 _public function_ `virtual int32 GetNumberOfMipLevels()` — Call this to get the number of mipmap levels.
- L201 _protected member_ `void* Header;` — Stores the EXR header object.
- L203 _protected member_ `void* OutputFile;` — Stores the EXR object.

#### class `FTiledRgbaOutputFile`  
`class FTiledRgbaOutputFile : public FBaseOutputFile`  
_L213-261_
- inherits: `FBaseOutputFile`
- desc: Use this to write out tiled EXR images. Add any attributes after construction. Then you can call CreateOutputFile. After that, you can write out data to the file.
- L224 _public prototype_ `FTiledRgbaOutputFile( const FIntPoint& DisplayWindowMin, const FIntPoint& DisplayWindowMax, const FIntPoint& DataWindowMin, const FIntPoint& DataWindowMax);` — Constructor. @param DisplayWindowMin		Normally (0, 0). @param DisplayWindowMax		Normally (width - 1, height - 1). @param DataWindowMin			Normally (0, 0). @param DataWindowMax			Normally (width - 1, height - 1).
- L239 _public prototype_ `void CreateOutputFile(const FString& FilePath, int32 TileWidth, int32 TileHeight, int32 NumChannels, bool bIsMipsEnabled);` — Call this after adding any attributes BUT before doing anything else. @param FilePath			Filename to save to. @param TileWidth			Width of a tile. @param TileHeight		Height of a tile. @param NumChannels		Number of channels out write out. @param bIsMipsEnabled	True to enable mip mapping.
- L248 _public prototype_ `void SetFrameBuffer(void* Buffer, const FIntPoint& Stride);` — Call this prior to WriteTile to set where the data is coming from. @param Buffer		Source of data. @param Stride		A pixels location is calculated by Buffer + x * StrideX + y * StrideY.
- L257 _public prototype_ `void WriteTile(int32 TileX, int32 TileY, int32 MipLevel);` — Call this to write data to a specific tile. @param TileX			X coordinate of tile. @param TileY			Y coordinate of tile. @param MipLevel		Mipmap level of tile.
- L260 _public prototype_ `virtual int32 GetNumberOfMipLevels() override;`

#### class `FTiledOutputFile`  
`class FTiledOutputFile : public FBaseOutputFile`  
_L271-393_
- inherits: `FBaseOutputFile`
- desc: Use this to write out tiled EXR images using the general interface. Add any attributes and AddChannel after construction. Then you can call CreateOutputFile. Then you can call AddFrameBufferChannel for each channel, and then SetFrameBuffer. After that, you can write out data to the file.
- L283 _public prototype_ `FTiledOutputFile( const FIntPoint& DisplayWindowMin, const FIntPoint& DisplayWindowMax, const FIntPoint& DataWindowMin, const FIntPoint& DataWindowMax, bool bInIsTiled = true);` — Constructor. @param DisplayWindowMin		Normally (0, 0). @param DisplayWindowMax		Normally (width - 1, height - 1). @param DataWindowMin			Normally (0, 0). @param DataWindowMax			Normally (width - 1, height - 1). @param bInIsTiled			True if you want tiles.
- L293 _public prototype_ `virtual ~FTiledOutputFile();` — Destructor.
- L300 _public prototype_ `void AddChannel(const FString& Name);` — Call this before CreateOutputFile for each channel in the image. @param Name		Name of channel (e.g. R, G, B, or A).
- L311 _public prototype_ `void CreateOutputFile(const FString& FilePath, int32 TileWidth, int32 TileHeight, bool bIsMipsEnabled, int32 NumThreads);` — Call this after adding any attributes or channels BUT before doing anything else. @param FilePath			Filename to save to. @param TileWidth			Width of a tile. @param TileHeight		Height of a tile. @param bIsMipsEnabled	True to enable mip mapping. @param NumThreads		Number of threads for EXR to use.
- L317 _public prototype_ `int32 GetMipWidth(int32 MipLevel);` — Get the width of a mip level.
- L322 _public prototype_ `int32 GetMipHeight(int32 MipLevel);` — Get the height of a mip level.
- L327 _public prototype_ `int32 GetNumXTiles(int32 MipLevel);` — Get number of horizontal tiles for a mip level.
- L332 _public prototype_ `int32 GetNumYTiles(int32 MipLevel);` — Get number of vertical tiles for a mip level.
- L341 _public prototype_ `void AddFrameBufferChannel(const FString& Name, void* Base, const FIntPoint& Stride);` — Call this before SetFrameBuffer for each channel in the frame buffer. @param Name			Name of channel (e.g. R, G, B, or A). @param Base			Address of the start of the data. @param Stride		A pixels location is calculated by Base + x * StrideX + y * StrideY.
- L351 _public prototype_ `void UpdateFrameBufferChannel(const FString& Name, void* Base, const FIntPoint& Stride);` — Call this to change a channel in the frame buffer. @param Name			Name of channel (e.g. R, G, B, or A). @param Base			Address of the start of the data. @param Stride		A pixels location is calculated by Base + x * StrideX + y * StrideY.
- L360 _public prototype_ `void SetFrameBuffer();` — Call this prior to WriteTile to set where the data is coming from. @param Buffer		Source of data. @param Stride		A pixels location is calculated by Buffer + x * StrideX + y * StrideY.
- L370 _public prototype_ `void WriteTile(int32 TileX, int32 TileY, int32 MipLevel);` — Call this to write data to a specific tile. If tiles are not enabled then this just writes out the whole image. @param TileX			X coordinate of tile. @param TileY			Y coordinate of tile. @param MipLevel		Mipmap level of tile.
- L382 _public prototype_ `void WriteTiles(int32 TileX1, int32 TileX2, int32 TileY1, int32 TileY2, int32 MipLevel);` — Call this to write data to some tiles. If tiles are not enabled then this just writes out the whole image. @param TileX1		X coordinate of first tile. @param TileX2		X coordinate of last tile. @param TileY1		Y coordinate of first tile. @param TileY2		Y coordinate of last tile. @param MipLevel		Mipmap level of tile.
- L385 _public prototype_ `virtual int32 GetNumberOfMipLevels() override;`
- L390 _private member_ `void* FrameBuffer;` — Stores the EXR frame buffer object.
- L392 _private member_ `bool bIsTiled;` — True if tiles are enabled.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API OPENEXRWRAPPER_API`
