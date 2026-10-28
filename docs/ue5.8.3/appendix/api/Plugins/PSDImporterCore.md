# Plugins / PSDImporterCore

- module root: `Plugins/Experimental/PSDImporter/Source/PSDImporterCore`
- headers: 9; symbols: 191
- symbol kinds: class=5, delegate=1, enum=6, enumerator=51, function=13, member=41, namespace=28, prototype=30, struct=11, typedef=5
- PrivateDependencyModuleNames: Engine, ImageCore, ImageWrapper, PsdSDK
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Private/PSDFileReader.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PSDImporter` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PSDImporter` (scope `UE`)
- L13 _namespace_ `namespace Internal` (scope `UE::PSDImporter`)
- L15 _prototype_ `int64 ReadBounds(FArchive& InAr, FIntRect& InBounds);` (scope `UE::PSDImporter::Internal`)
- L18 _function_ `template <typename DataType = uint16> DataType ReadBigEndian16(const void* InPtr)` (scope `UE::PSDImporter::Internal`)
- L27 _function_ `template <typename DataType = uint32> DataType ReadBigEndian32(const void* InPtr)` (scope `UE::PSDImporter::Internal`)
- L38 _function_ `template <typename DataType> bool Read(FMemoryView& InOutView, DataType& OutValue)` (scope `UE::PSDImporter::Internal`)
- L45 _prototype_ `template <> bool Read(FMemoryView& InOutView, uint16& OutValue);` (scope `UE::PSDImporter::Internal`)
- L47 _prototype_ `bool SkipSection(FMemoryView& InOutView);` (scope `UE::PSDImporter::Internal`)
- L50 _prototype_ `bool DecodeRLERow(const uint8* InRowSource, uint16 InRowSourceBytes, uint8* InOutputScanlineData, uint64 InOutputScanlineDataSize);` (scope `UE::PSDImporter::Internal`) — Decodes the raw data for a row - this is the same independent of the scanline format.
- L52 _prototype_ `bool ReadData(const FMutableMemoryView& InOutput, FMemoryView InInput, const FPSDFileHeader& InHeader);` (scope `UE::PSDImporter::Internal`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Private/PSDImporterCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPSDImporterCore, All, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPSDImporterCore, All, All);`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Private/Readers/DocumentReader.h` (Private)


#### class `UE::PSDImporter::Private::FDocumentReader`  
`class FDocumentReader`  
_L15-19_
- L18 _public prototype_ `bool Read(FReadContext& InContext);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace psd`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PSDImporter` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::PSDImporter`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Private/Readers/LayerReader.h` (Private)


#### enum `UE::PSDImporter::Private::ELayerMaskType`  
`enum class ELayerMaskType : uint8`  
_L19-23_
- L21 _public enumerator_ `LayerMask`
- L22 _public enumerator_ `VectorMask`

#### class `UE::PSDImporter::Private::FLayerReader`  
`class FLayerReader`  
_L27-35_
- L30 _public typedef_ `using FInputType = psd::Layer;`
- L32 _public prototype_ `File::FPSDLayerRecord* Read(FReadContext& InContext, psd::Layer* InLayer, const int32 InLayerIdx, const File::FPSDLayerRecord* InParentLayer);`
- L33 _public prototype_ `TFuture<FImage> ReadLayerData(FReadContext& InContext, psd::Layer* InLayer);`
- L34 _public prototype_ `TFuture<FImage> ReadMaskData(FReadContext& InContext, psd::Layer* InLayer);`

#### class `UE::PSDImporter::Private::FLayersReader`  
`class FLayersReader`  
_L37-73_
- L58 _public typedef_ `using FInputType = psd::LayerMaskSection;`
- L60 _public prototype_ `TFuture<bool> Read(Private::FReadContext& InContext);`
- L63 _private prototype_ `int32 ReadLayers( FReadContext& InContext, FLayerData& InOutLayerData, const TFunctionRef<bool(psd::Layer*, File::FPSDLayerRecord*)>& InLayerVisitorFunc = [](psd::Layer*, File::FPSDLayerRecord*) { return true; } );`
- L66 _private function_ `FReadContext& InContext, FLayerData& InOutLayerData, const TFunctionRef<bool(psd::Layer*, File::FPSDLayerRecord*)>& InLayerVisitorFunc = [](psd::Layer*, File::FPSDLayerRecord*)`
- L69 _private prototype_ `File::FPSDLayerRecord* ReadGroup(FReadContext& InContext, const psd::Layer* InLayer, FLayerData& InOutLayerData);`
- L72 _private member_ `FLayerReader LayerReader;`

#### struct `UE::PSDImporter::Private::FLayersReader::FReadContext`  
`struct FReadContext : Private::FReadContext`  
_L39-48_
- inherits: `Private::FReadContext`
- L41 _public function_ `FReadContext(const Private::FReadContext& InBaseContext, psd::LayerMaskSection* InLayerMasks) : Private::FReadContext(InBaseContext) , LayerMasks(InLayerMasks)`
- L47 _public member_ `psd::LayerMaskSection* LayerMasks;`

#### struct `UE::PSDImporter::Private::FLayersReader::FLayerData`  
`struct FLayerData`  
_L50-55_
- L52 _public member_ `int32 LayerIdx;`
- L53 _public member_ `File::FPSDLayerRecord* ParentLayer = nullptr;`
- L54 _public member_ `TSet<File::FPSDLayerRecord*>& LayerRecords;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace psd`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PSDImporter` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::PSDImporter`)
- L25 _prototype_ `static EPSDBlendMode ConvertBlendMode(uint32 InPsdBlendMode);` (scope `UE::PSDImporter::Private`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Private/Readers/ReaderShared.h` (Private)


#### class `UE::PSDImporter::Private::FPsdAllocator`  
`class FPsdAllocator : public psd::Allocator`  
_L15-28_
- inherits: `psd::Allocator`
- L19 _public function_ `virtual void* DoAllocate(size_t InSize, size_t InAlignment) override`
- L24 _public function_ `virtual void DoFree(void* InPtr) override`

#### struct `UE::PSDImporter::Private::FReadContext`  
`struct FReadContext`  
_L30-61_
- L32 _public function_ `FReadContext( psd::Allocator& InAllocator, psd::NativeFile* InFile, psd::Document* InDocument, const TSharedPtr<IPSDFileReader>& InReader, File::FPSDDocument* InDocument2, const TSharedPtr<FPSDFileImportVisitors>& InVisitors, const FPSDFileImporterOptions& InOptions) : Allocator(InAllocator) , File(InFile) , Document(InDocument) , FileReader(InReader) , Document2(InDocument2) , Visitors(InVisitors) , Options(InOptions)`
- L50 _public member_ `psd::Allocator& Allocator;`
- L51 _public member_ `psd::NativeFile* File = nullptr;`
- L52 _public member_ `psd::Document* Document = nullptr;`
- L54 _public member_ `TSharedPtr<IPSDFileReader> FileReader = nullptr;`
- L56 _public member_ `File::FPSDDocument* Document2 = nullptr;`
- L58 _public member_ `TSharedPtr<FPSDFileImportVisitors> Visitors;`
- L60 _public member_ `FPSDFileImporterOptions Options;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PSDImporter` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::PSDImporter`)
- L64 _prototype_ `bool SaveImage(const FImage& InImage, const FString& InFilePath);` (scope `UE::PSDImporter::Private`) — For debugging purposes.
- L68 _function_ `template <typename DataType> DataType* ExpandChannelToCanvas(psd::Allocator* InAllocator, const psd::Layer* InLayer, const void* InData, uint32 InWidth, uint32 InHeight)` (scope `UE::PSDImporter::Private`) — Pads the channel so that it's placed correctly on the overall document canvas.
- L78 _prototype_ `uint32 FindChannelIdx(const psd::Layer* InLayer, int16 InChannelType);` (scope `UE::PSDImporter::Private`)
- L80 _prototype_ `FString GetLayerName(const psd::Layer* InLayer);` (scope `UE::PSDImporter::Private`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Public/PSDFileData.h` (Public)


#### enum `EPSDBlendMode`  
`enum class EPSDBlendMode : uint8`  
_L15-52_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `PassThrough`
- L18 _public enumerator_ `Normal`
- L19 _public enumerator_ `Dissolve`
- L21 _public enumerator_ `Darken`
- L22 _public enumerator_ `Multiply`
- L23 _public enumerator_ `ColorBurn`
- L24 _public enumerator_ `LinearBurn`
- L25 _public enumerator_ `DarkerColor`
- L27 _public enumerator_ `Lighten`
- L28 _public enumerator_ `Screen`
- L29 _public enumerator_ `ColorDodge`
- L30 _public enumerator_ `LinearDodge`
- L31 _public enumerator_ `LighterColor`
- L33 _public enumerator_ `Overlay`
- L34 _public enumerator_ `SoftLight`
- L35 _public enumerator_ `HardLight`
- L36 _public enumerator_ `VividLight`
- L37 _public enumerator_ `LinearLight`
- L38 _public enumerator_ `PinLight`
- L39 _public enumerator_ `HardMix`
- L41 _public enumerator_ `Difference`
- L42 _public enumerator_ `Exclusion`
- L43 _public enumerator_ `Subtract`
- L44 _public enumerator_ `Divide`
- L46 _public enumerator_ `Hue`
- L47 _public enumerator_ `Saturation`
- L48 _public enumerator_ `Color`
- L49 _public enumerator_ `Luminosity`
- L51 _public enumerator_ `Unknown`

#### enum `UE::PSDImporter::File::EPSDColorMode`  
`enum class EPSDColorMode : int16`  
_L59-69_
- L61 _public enumerator_ `Bitmap = 0`
- L62 _public enumerator_ `Grayscale = 1`
- L63 _public enumerator_ `Indexed = 2`
- L64 _public enumerator_ `RGB = 3`
- L65 _public enumerator_ `CMYK = 4`
- L66 _public enumerator_ `Multichannel = 7`
- L67 _public enumerator_ `Duotone = 8`
- L68 _public enumerator_ `Lab = 9`

#### enum `UE::PSDImporter::File::EPSDCompressionMethod`  
`enum class EPSDCompressionMethod : int16`  
_L71-77_
- L73 _public enumerator_ `Raw = 0`
- L74 _public enumerator_ `RLE = 1`
- L75 _public enumerator_ `ZIPWithoutPrediction = 2`
- L76 _public enumerator_ `ZIPWithPrediction = 3`

#### enum `UE::PSDImporter::File::EPSDLayerType`  
`enum class EPSDLayerType : int16`  
_L79-83_
- L81 _public enumerator_ `Any = 0`
- L82 _public enumerator_ `Group = 1`

#### struct `UE::PSDImporter::File::FPSDHeader`  
`struct FPSDHeader`  
_L86-98_
- desc: @see: https://www.adobe.com/devnet-apps/photoshop/fileformatashtml/PSDFileFormats.htm#50577409_19840
- L88 _public member_ `int32 Signature = 0;` — Must be 8BPS
- L89 _public member_ `int16 Version = 0;` — Version: 1 = PSD, 2 = PSB
- L90 _public member_ `uint8 Pad[6] = {};` — Padding
- L91 _public member_ `int16 NumChannels = 0;` — Number of Channels: (3=RGB) (4=RGBA)
- L92 _public member_ `int32 Height = 0;` — Number of Image Rows: 1-30,000 or 1-300,000 if PSB
- L93 _public member_ `int32 Width = 0;` — Number of Image Columns
- L94 _public member_ `int16 Depth = 0;` — Number of Bits per Channel: 1, 8, 16, 32
- L95 _public member_ `EPSDColorMode Mode = EPSDColorMode::RGB;` — Image Mode: (0=Bitmap)(1=Grayscale)(2=Indexed)(3=RGB)(4=CYMK)(7=Multichannel)
- L97 _public prototype_ `bool IsValid() const;`

#### struct `UE::PSDImporter::File::FPSDImageData`  
`struct FPSDImageData`  
_L100-103_
- L102 _public member_ `EPSDCompressionMethod CompressionMethod;`

#### enum `UE::PSDImporter::File::EPSDLayerFlags`  
`enum class EPSDLayerFlags : uint8`  
_L105-113_
- L107 _public enumerator_ `None = 0`
- L108 _public enumerator_ `TransparencyProtected = 1 << 0`
- L109 _public enumerator_ `Visible = 1 << 1`
- L110 _public enumerator_ `Obsolete = 1 << 2`
- L111 _public enumerator_ `HasDataInBit4 = 1 << 3`
- L112 _public enumerator_ `NonVisiblePixelData = 1 << 4`

#### struct `UE::PSDImporter::File::FPSDLayerAndMaskInformation`  
`struct FPSDLayerAndMaskInformation`  
_L116-122_
- L118 _public member_ `uint16 NumLayers = 0;`
- L119 _public member_ `bool bHasTransparencyMask = false;`
- L121 _public member_ `TSet<FPSDLayerRecord*> Layers;`

#### Free symbols / members of external scopes

- L55 _namespace_ `namespace UE`
- L55 _namespace_ `namespace PSDImporter` (scope `UE`)
- L55 _namespace_ `namespace File` (scope `UE::PSDImporter`)
- L114 _prototype_ `ENUM_CLASS_FLAGS(EPSDLayerFlags);` (scope `UE::PSDImporter::File`)
- L124 _prototype_ `const TCHAR* LexToString(EPSDColorMode InEnum);` (scope `UE::PSDImporter::File`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Public/PSDFileDocument.h` (Public)


#### struct `UE::PSDImporter::File::FPSDDocument`  
`struct FPSDDocument`  
_L11-23_
- L13 _public member_ `FPSDHeader Header;`
- L20 _public member_ `FPSDLayerAndMaskInformation LayerAndMaskInformation;` — 3. LayerAndMaskInformation

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PSDImporter` (scope `UE`)
- L9 _namespace_ `namespace File` (scope `UE::PSDImporter`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Public/PSDFileImport.h` (Public)


#### struct `UE::PSDImporter::FPSDFileImportVisitors`  
`struct FPSDFileImportVisitors`  
_L23-38_
- L25 _public prototype_ `virtual ~FPSDFileImportVisitors() = default;`
- L27 _public function_ `virtual void OnImportComplete()`
- L29 _public typedef_ `using FHeaderInputType = UE::PSDImporter::File::FPSDHeader;`
- L30 _public function_ `virtual void OnImportHeader(const FHeaderInputType& InHeader)`
- L32 _public typedef_ `using FLayersInputType = UE::PSDImporter::File::FPSDLayerAndMaskInformation;`
- L33 _public function_ `virtual void OnImportLayers(const FLayersInputType& Layers)`
- L35 _public typedef_ `using FLayerInputType = UE::PSDImporter::File::FPSDLayerRecord;`
- L36 _public function_ `virtual void OnImportLayer(const FLayerInputType& InLayer, const FLayerInputType* InParentLayer, TFunction<TFuture<FImage>()> InReadLayerData, TFunction<TFuture<FImage>()> InReadMaskData)`

#### struct `UE::PSDImporter::FPSDFileImporterOptions`  
`struct FPSDFileImporterOptions`  
_L40-43_
- L42 _public member_ `bool bResizeLayersToDocument = false;`

#### class `UE::PSDImporter::FPSDFileImporter`  
`class FPSDFileImporter`  
_L45-56_
- L48 _public prototype_ `static TSharedRef<FPSDFileImporter> Make(const FString& InFileName);`
- L50 _public prototype_ `virtual ~FPSDFileImporter() = default;`
- L52 _public prototype_ `virtual bool Import(const TSharedPtr<FPSDFileImportVisitors>& InVisitors, const FPSDFileImporterOptions& InOptions) = 0;`
- L55 _protected prototype_ `FPSDFileImporter() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PSDImporter` (scope `UE`)
- L11 _namespace_ `namespace File` (scope `UE::PSDImporter`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterCore/Public/PSDFileRecord.h` (Public)


#### struct `UE::PSDImporter::File::FPSDChannelInformation`  
`struct FPSDChannelInformation`  
_L11-15_
- L13 _public member_ `int16 Id;` — 0 = Red, 1 = Green, 2 = Blue, -1 = Transparency Mask, -2 = User Mask, -3 = Both Masks
- L14 _public member_ `int64 Length;` — Data length

#### struct `UE::PSDImporter::File::FPSDLayerRecord`  
`struct FPSDLayerRecord`  
_L17-42_
- L19 _public member_ `int32 Index;`
- L20 _public member_ `FIntRect Bounds;`
- L21 _public member_ `uint16 NumChannels;`
- L22 _public member_ `EPSDBlendMode BlendMode;`
- L23 _public member_ `uint8 Opacity = 255;`
- L24 _public member_ `uint8 Clipping = 0;`
- L25 _public member_ `EPSDLayerFlags Flags;`
- L26 _public member_ `bool bIsGroup = false;`
- L27 _public member_ `FIntRect MaskBounds;`
- L28 _public member_ `uint8 MaskDefaultValue;`
- L30 _public member_ `FString LayerName;`
- L32 _public member_ `TSet<FPSDChannelInformation*> Channels;`
- L34 _public prototype_ `~FPSDLayerRecord();`
- L36 _public prototype_ `bool operator==(const FPSDLayerRecord& InOther) const;`
- L37 _public prototype_ `bool operator!=(const FPSDLayerRecord& InOther) const;`
- L38 _public prototype_ `bool operator<(const FPSDLayerRecord& InOther) const;`
- L39 _public prototype_ `bool operator<=(const FPSDLayerRecord& InOther) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PSDImporter` (scope `UE`)
- L9 _namespace_ `namespace File` (scope `UE::PSDImporter`)
