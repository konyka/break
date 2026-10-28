# Plugins / CaptureManagerMediaRW

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW`
- headers: 18; symbols: 362
- symbol kinds: class=43, enum=5, enumerator=32, externvar=2, function=2, macro=3, member=92, namespace=4, prototype=172, struct=7
- PrivateDependencyModuleNames: CaptureDataUtils, DataIngestCore, Engine, ImageCore, ImageWriteQueue, Json, JsonUtilities, OodleDataCompression, RenderCore
- PublicDependencyModuleNames: Core, Media

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Readers/ImageSequenceReader.h` (Private)


#### class `FImageSequenceReaderHelper`  
`class FImageSequenceReaderHelper`  
_L10-15_
- L14 _public prototype_ `static void RegisterReaders(class FMediaRWManager& InManager);`

#### class `FImageSequenceReaderFactory`  
`class FImageSequenceReaderFactory final : public IVideoReaderFactory`  
_L17-22_
- inherits: `IVideoReaderFactory`
- L21 _public prototype_ `virtual TUniquePtr<IVideoReader> CreateVideoReader() override;`

#### class `FImageSequenceReader`  
`class FImageSequenceReader final : public IVideoReader`  
_L24-46_
- inherits: `IVideoReader`
- L28 _public prototype_ `FImageSequenceReader();`
- L31 _public prototype_ `virtual TOptional<FText> Open(const FString& InDirectoryPath) override;`
- L32 _public prototype_ `virtual TOptional<FText> Close() override;`
- L34 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaTextureSample>, FText> Next() override;`
- L37 _public prototype_ `virtual FTimespan GetDuration() const override;` — Duration and Frame Rate will be set to number of frames and 1 frame per second
- L38 _public prototype_ `virtual FIntPoint GetDimensions() const override;`
- L39 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L43 _private member_ `TArray<FString> ImagePaths;`
- L44 _private member_ `FIntPoint Dimensions;`
- L45 _private member_ `std::atomic_int CurrentFrameNumber = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Readers/MHADepthVideoReader.h` (Private)


#### class `FMHADepthVideoReaderHelpers`  
`class FMHADepthVideoReaderHelpers`  
_L10-15_
- L14 _public prototype_ `static void RegisterReaders(class FMediaRWManager& InManager);`

#### class `FMHADepthVideoReaderFactory`  
`class FMHADepthVideoReaderFactory final : public IVideoReaderFactory`  
_L17-22_
- inherits: `IVideoReaderFactory`
- L21 _public prototype_ `virtual TUniquePtr<IVideoReader> CreateVideoReader() override;`

#### class `FMHADepthVideoReader`  
`class FMHADepthVideoReader final : public IVideoReader`  
_L24-46_
- inherits: `IVideoReader`
- L28 _public prototype_ `FMHADepthVideoReader();`
- L31 _public prototype_ `virtual TOptional<FText> Open(const FString& InFileName) override;`
- L32 _public prototype_ `virtual TOptional<FText> Close() override;`
- L34 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaTextureSample>, FText> Next() override;`
- L36 _public prototype_ `virtual FTimespan GetDuration() const override;`
- L37 _public prototype_ `virtual FIntPoint GetDimensions() const override;`
- L38 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L42 _private member_ `TUniquePtr<IFileHandle> ReadHandle;`
- L43 _private member_ `FIntPoint Dimensions;`
- L44 _private member_ `FFrameRate FrameRate = FFrameRate(30'000, 1'000);`
- L45 _private member_ `EMediaOrientation Orientation;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Readers/MHAICalibrationReader.h` (Private)


#### class `FMHAICalibrationReaderHelpers`  
`class FMHAICalibrationReaderHelpers`  
_L10-15_
- L14 _public prototype_ `static void RegisterReaders(class FMediaRWManager& InManager);`

#### class `FMHAICalibrationReaderFactory`  
`class FMHAICalibrationReaderFactory : public ICalibrationReaderFactory`  
_L17-22_
- inherits: `ICalibrationReaderFactory`
- L21 _public prototype_ `virtual TUniquePtr<ICalibrationReader> CreateCalibrationReader() override;`

#### class `FMHAICalibrationReader`  
`class FMHAICalibrationReader : public ICalibrationReader`  
_L24-47_
- inherits: `ICalibrationReader`
- L28 _public prototype_ `virtual TOptional<FText> Open(const FString& InFileName) override;`
- L29 _public prototype_ `virtual TOptional<FText> Close() override;`
- L31 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaCalibrationSample>, FText> Next() override;`
- L42 _private prototype_ `EMediaOrientation ParseOrientation(int32 InOrientation);`
- L43 _private prototype_ `void SwitchSampleType();`
- L45 _private member_ `TSharedPtr<FJsonObject> JsonObject;`
- L46 _private member_ `ESampleType CurrentSampleType = ESampleType::Depth;`

#### enum `FMHAICalibrationReader::ESampleType`  
`enum ESampleType`  
_L35-40_
- L37 _public enumerator_ `Depth = 0`
- L38 _public enumerator_ `Video`
- L39 _public enumerator_ `EndOfStream`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Readers/OpenCVCalibrationReader.h` (Private)


#### class `FOpenCvCalibrationReaderHelpers`  
`class FOpenCvCalibrationReaderHelpers`  
_L10-15_
- L14 _public prototype_ `static void RegisterReaders(class FMediaRWManager& InManager);`

#### class `FOpenCvCalibrationReaderFactory`  
`class FOpenCvCalibrationReaderFactory : public ICalibrationReaderFactory`  
_L17-22_
- inherits: `ICalibrationReaderFactory`
- L21 _public prototype_ `virtual TUniquePtr<ICalibrationReader> CreateCalibrationReader() override;`

#### class `FOpenCvCalibrationReader`  
`class FOpenCvCalibrationReader : public ICalibrationReader`  
_L24-37_
- inherits: `ICalibrationReader`
- L28 _public prototype_ `virtual TOptional<FText> Open(const FString& InFileName) override;`
- L29 _public prototype_ `virtual TOptional<FText> Close() override;`
- L31 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaCalibrationSample>, FText> Next() override;`
- L35 _private member_ `TArray<TSharedPtr<FJsonValue>> JsonArray;`
- L36 _private member_ `std::atomic_int ArrayIndex = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Readers/WindowsMediaReader.h` (Private)


#### class `FWindowsReadersFactory`  
`class FWindowsReadersFactory final : public IAudioReaderFactory, public IVideoReaderFactory`  
_L29-37_
- inherits: `IAudioReaderFactory,IVideoReaderFactory`
- L35 _public prototype_ `virtual TUniquePtr<IAudioReader> CreateAudioReader() override;`
- L36 _public prototype_ `virtual TUniquePtr<IVideoReader> CreateVideoReader() override;`

#### class `FWindowsAudioReader`  
`class FWindowsAudioReader final : public IAudioReader`  
_L39-64_
- inherits: `IAudioReader`
- L43 _public prototype_ `FWindowsAudioReader();`
- L46 _public prototype_ `virtual TOptional<FText> Open(const FString& InFileName) override;`
- L47 _public prototype_ `virtual TOptional<FText> Close() override;`
- L49 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaAudioSample>, FText> Next() override;`
- L51 _public prototype_ `virtual FTimespan GetDuration() const override;`
- L52 _public prototype_ `virtual EMediaAudioSampleFormat GetSampleFormat() const override;`
- L53 _public prototype_ `virtual UE::CaptureManager::ESampleRate GetSampleRate() const override;`
- L54 _public prototype_ `virtual uint32 GetNumChannels() const override;`
- L58 _private member_ `TComPtr<IMFSourceReader> AudioReader;`
- L60 _private member_ `FTimespan Duration;`
- L61 _private member_ `EMediaAudioSampleFormat Format;`
- L62 _private member_ `UE::CaptureManager::ESampleRate SampleRate;`
- L63 _private member_ `uint32 Channels;`

#### class `FWindowsVideoReader`  
`class FWindowsVideoReader final : public IVideoReader`  
_L66-91_
- inherits: `IVideoReader`
- L70 _public prototype_ `FWindowsVideoReader();`
- L73 _public prototype_ `virtual TOptional<FText> Open(const FString& InFileName) override;`
- L74 _public prototype_ `virtual TOptional<FText> Close() override;`
- L76 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaTextureSample>, FText> Next() override;`
- L78 _public prototype_ `virtual FTimespan GetDuration() const override;`
- L79 _public prototype_ `virtual FIntPoint GetDimensions() const override;`
- L80 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L84 _private member_ `TComPtr<IMFSourceReader> VideoReader;`
- L86 _private member_ `FTimespan Duration;`
- L87 _private member_ `FIntPoint Dimensions;`
- L88 _private member_ `FFrameRate FrameRate;`
- L89 _private member_ `UE::CaptureManager::EMediaTexturePixelFormat PixelFormat;`
- L90 _private member_ `GUID InputVideoSubType;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Utils/WindowsJpegDecoder.h` (Private)


#### class `FWindowsJpegDecoder`  
`class FWindowsJpegDecoder`  
_L27-43_
- L31 _public prototype_ `static TValueOrError<FWindowsJpegDecoder, FText> CreateJpegDecoder();`
- L33 _public prototype_ `TOptional<FText> Decode(uint8* InData, uint32 InSize, TArray<uint8>& OutImage, UE::CaptureManager::EMediaTexturePixelFormat& OutPixelFormat);`
- L37 _private prototype_ `FWindowsJpegDecoder();`
- L38 _private prototype_ `TOptional<FText> Initialize();`
- L40 _private prototype_ `static UE::CaptureManager::EMediaTexturePixelFormat ConvertPixelFormat(WICPixelFormatGUID InPixelFormat);`
- L42 _private member_ `TComPtr<IWICImagingFactory> WindowsImagingFactory;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Utils/WindowsRWHelpers.h` (Private)


#### class `FWindowsRWHelpers`  
`class FWindowsRWHelpers`  
_L10-28_
- L14 _public prototype_ `static bool Init();`
- L15 _public prototype_ `static void Deinit();`
- L17 _public prototype_ `static void RegisterReaders(class FMediaRWManager& InManager);`
- L18 _public prototype_ `static void RegisterWriters(class FMediaRWManager& InManager);`
- L20 _public prototype_ `static FText CreateErrorMessage(HRESULT InResult, FText InMessage);`
- L24 _private prototype_ `static FString FormatWindowsMessage(HRESULT InResult);`
- L26 _private member_ `static bool bInitialized;`
- L27 _private member_ `static bool bOwnsComInit;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Writers/AudioWaveMediaWriter.h` (Private)


#### class `FAudioWaveWriterHelpers`  
`class FAudioWaveWriterHelpers`  
_L9-14_
- L13 _public prototype_ `static void RegisterWriters(class FMediaRWManager& InManager);`

#### class `FAudioWaveWriterFactory`  
`class FAudioWaveWriterFactory final : public IAudioWriterFactory`  
_L16-21_
- inherits: `IAudioWriterFactory`
- L20 _public prototype_ `virtual TUniquePtr<IAudioWriter> CreateAudioWriter();`

#### class `FAudioWaveWriter`  
`class FAudioWaveWriter final : public IAudioWriter`  
_L23-39_
- inherits: `IAudioWriter`
- L27 _public prototype_ `FAudioWaveWriter();`
- L30 _public prototype_ `virtual TOptional<FText> Open(const FString& InDirectory, const FString& InFileName, const FString& InFormat) override;`
- L31 _public prototype_ `virtual TOptional<FText> Close() override;`
- L33 _public prototype_ `virtual TOptional<FText> Append(UE::CaptureManager::FMediaAudioSample* InSample) override;`
- L37 _private member_ `TUniquePtr<IFileHandle> FileHandle;`
- L38 _private member_ `uint64 TotalDataBytesWritten = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Writers/DepthImageWriter.h` (Private)


#### class `FDepthExrImageWriterHelpers`  
`class FDepthExrImageWriterHelpers`  
_L11-16_
- L15 _public prototype_ `static void RegisterWriters(class FMediaRWManager& InManager);`

#### class `FDepthExrImageWriterFactory`  
`class FDepthExrImageWriterFactory final : public IImageWriterFactory`  
_L18-23_
- inherits: `IImageWriterFactory`
- L22 _public prototype_ `virtual TUniquePtr<IImageWriter> CreateImageWriter() override;`

#### class `FDepthExrImageWriter`  
`class FDepthExrImageWriter final : public IImageWriter`  
_L25-51_
- inherits: `IImageWriter`
- L29 _public prototype_ `FDepthExrImageWriter();`
- L33 _public prototype_ `virtual TOptional<FText> Open(const FString& InDirectory, const FString& InFileName, const FString& InFormat) override;`
- L34 _public prototype_ `virtual TOptional<FText> Close() override;`
- L36 _public prototype_ `virtual TOptional<FText> Append(UE::CaptureManager::FMediaTextureSample* InSample) override;`
- L40 _private prototype_ `TArray<float> Transform(TArray<uint8> InDepthArray, FIntPoint InDimensions, EMediaOrientation InOrientation) const;`
- L42 _private member_ `static constexpr float TrueDepthResolutionPerCentimeter = 80.f;`
- L44 _private member_ `IImageWrapperModule& ImageWrapperModule;`
- L46 _private member_ `FString Directory;`
- L47 _private member_ `FString FileName;`
- L48 _private member_ `FString Format;`
- L50 _private member_ `uint32 FrameNumber = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Writers/UnrealCalibrationWriter.h` (Private)


#### class `FUnrealCalibrationWriterHelpers`  
`class FUnrealCalibrationWriterHelpers`  
_L11-16_
- L15 _public prototype_ `static void RegisterWriters(class FMediaRWManager& InManager);`

#### class `FUnrealCalibrationWriterFactory`  
`class FUnrealCalibrationWriterFactory final : public ICalibrationWriterFactory`  
_L18-23_
- inherits: `ICalibrationWriterFactory`
- L22 _public prototype_ `virtual TUniquePtr<ICalibrationWriter> CreateCalibrationWriter() override;`

#### class `FUnrealCalibrationWriter`  
`class FUnrealCalibrationWriter final : public ICalibrationWriter`  
_L26-40_
- inherits: `ICalibrationWriter`
- L30 _public prototype_ `virtual TOptional<FText> Open(const FString& InDirectory, const FString& InFileName, const FString& InFormat) override;`
- L31 _public prototype_ `virtual TOptional<FText> Close() override;`
- L33 _public prototype_ `virtual TOptional<FText> Append(UE::CaptureManager::FMediaCalibrationSample* InSample) override;`
- L37 _private member_ `FString DestinationFile;`
- L38 _private member_ `TSharedPtr<TJsonWriter<TCHAR>> JsonWriter;`
- L39 _private member_ `FString JsonString;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Private/Writers/WindowsImageWriter.h` (Private)


#### class `FWindowsImageWriterFactory`  
`class FWindowsImageWriterFactory final : public IImageWriterFactory`  
_L28-33_
- inherits: `IImageWriterFactory`
- L32 _public prototype_ `virtual TUniquePtr<IImageWriter> CreateImageWriter() override;`

#### class `FWindowsImageWriter`  
`class FWindowsImageWriter final : public IImageWriter`  
_L35-59_
- inherits: `IImageWriter`
- L39 _public prototype_ `FWindowsImageWriter();`
- L42 _public prototype_ `virtual TOptional<FText> Open(const FString& InDirectory, const FString& InFileName, const FString& InFormat) override;`
- L43 _public prototype_ `virtual TOptional<FText> Close() override;`
- L45 _public prototype_ `virtual TOptional<FText> Append(UE::CaptureManager::FMediaTextureSample* InSample) override;`
- L49 _private prototype_ `GUID GetEncoderGuidBasedOnFormat(const FString& InFormat);`
- L50 _private prototype_ `FString CreateFrameFileName();`
- L52 _private member_ `TComPtr<IWICImagingFactory> WindowsImagingFactory;`
- L54 _private member_ `FString Directory;`
- L55 _private member_ `FString FileName;`
- L56 _private member_ `FString Format;`
- L58 _private member_ `uint32 FrameNumber = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Public/CaptureManagerMediaRWModule.h` (Public)


#### class `FCaptureManagerMediaRWModule`  
`class FCaptureManagerMediaRWModule : public IModuleInterface`  
_L11-23_
- inherits: `IModuleInterface`
- L15 _public prototype_ `void StartupModule();`
- L16 _public prototype_ `void ShutdownModule();`
- L18 _public prototype_ `FMediaRWManager& Get();`
- L22 _private member_ `TUniquePtr<FMediaRWManager> MediaRWManager;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREMANAGERMEDIARW_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Public/IMediaRWFactory.h` (Public)


#### class `IAudioReaderFactory`  
`class IAudioReaderFactory`  
_L8-15_
- L12 _public prototype_ `virtual ~IAudioReaderFactory() = default;`
- L14 _public prototype_ `virtual TUniquePtr<IAudioReader> CreateAudioReader() = 0;`

#### class `IVideoReaderFactory`  
`class IVideoReaderFactory`  
_L17-24_
- L21 _public prototype_ `virtual ~IVideoReaderFactory() = default;`
- L23 _public prototype_ `virtual TUniquePtr<IVideoReader> CreateVideoReader() = 0;`

#### class `ICalibrationReaderFactory`  
`class ICalibrationReaderFactory`  
_L26-33_
- L30 _public prototype_ `virtual ~ICalibrationReaderFactory() = default;`
- L32 _public prototype_ `virtual TUniquePtr<ICalibrationReader> CreateCalibrationReader() = 0;`

#### class `IAudioWriterFactory`  
`class IAudioWriterFactory`  
_L35-42_
- L39 _public prototype_ `virtual ~IAudioWriterFactory() = default;`
- L41 _public prototype_ `virtual TUniquePtr<IAudioWriter> CreateAudioWriter() = 0;`

#### class `IImageWriterFactory`  
`class IImageWriterFactory`  
_L44-51_
- L48 _public prototype_ `virtual ~IImageWriterFactory() = default;`
- L50 _public prototype_ `virtual TUniquePtr<IImageWriter> CreateImageWriter() = 0;`

#### class `ICalibrationWriterFactory`  
`class ICalibrationWriterFactory`  
_L53-60_
- L57 _public prototype_ `virtual ~ICalibrationWriterFactory() = default;`
- L59 _public prototype_ `virtual TUniquePtr<ICalibrationWriter> CreateCalibrationWriter() = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Public/IMediaReader.h` (Public)


#### class `IAudioReader`  
`class IAudioReader`  
_L7-22_
- L11 _public prototype_ `virtual ~IAudioReader() = default;`
- L13 _public prototype_ `virtual TOptional<FText> Open(const FString& InFileName) = 0;`
- L14 _public prototype_ `virtual TOptional<FText> Close() = 0;`
- L16 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaAudioSample>, FText> Next() = 0;`
- L18 _public prototype_ `virtual FTimespan GetDuration() const = 0;`
- L19 _public prototype_ `virtual EMediaAudioSampleFormat GetSampleFormat() const = 0;`
- L20 _public prototype_ `virtual UE::CaptureManager::ESampleRate GetSampleRate() const = 0;`
- L21 _public prototype_ `virtual uint32 GetNumChannels() const = 0;`

#### class `IVideoReader`  
`class IVideoReader`  
_L24-38_
- L28 _public prototype_ `virtual ~IVideoReader() = default;`
- L30 _public prototype_ `virtual TOptional<FText> Open(const FString& InFileName) = 0;`
- L31 _public prototype_ `virtual TOptional<FText> Close() = 0;`
- L33 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaTextureSample>, FText> Next() = 0;`
- L35 _public prototype_ `virtual FTimespan GetDuration() const = 0;`
- L36 _public prototype_ `virtual FIntPoint GetDimensions() const = 0;`
- L37 _public prototype_ `virtual FFrameRate GetFrameRate() const = 0;`

#### class `ICalibrationReader`  
`class ICalibrationReader`  
_L40-50_
- L44 _public prototype_ `virtual ~ICalibrationReader() = default;`
- L46 _public prototype_ `virtual TOptional<FText> Open(const FString& InFileName) = 0;`
- L47 _public prototype_ `virtual TOptional<FText> Close() = 0;`
- L49 _public prototype_ `virtual TValueOrError<TUniquePtr<UE::CaptureManager::FMediaCalibrationSample>, FText> Next() = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Public/IMediaWriter.h` (Public)


#### class `IAudioWriter`  
`class IAudioWriter`  
_L7-31_
- L11 _public prototype_ `virtual ~IAudioWriter() = default;`
- L14 _public prototype_ `virtual TOptional<FText> Open(const FString& InDirectory, const FString& InFileName, const FString& InFormat) = 0;` — FileName is the name of file without the extensions while the Format represents an extension without the dot
- L15 _public prototype_ `virtual TOptional<FText> Close() = 0;`
- L17 _public prototype_ `virtual TOptional<FText> Append(UE::CaptureManager::FMediaAudioSample* Sample) = 0;`
- L19 _public function_ `void Configure(UE::CaptureManager::ESampleRate InSampleRate, int32 InNumChannels, EMediaAudioSampleFormat InBitsPerSample)`
- L28 _protected member_ `UE::CaptureManager::ESampleRate SampleRate = UE::CaptureManager::ESampleRate::SR_44100Hz;`
- L29 _protected member_ `int32 NumChannels = 1;`
- L30 _protected member_ `EMediaAudioSampleFormat BitsPerSample = EMediaAudioSampleFormat::Int16;`

#### class `IImageWriter`  
`class IImageWriter`  
_L33-44_
- L37 _public prototype_ `virtual ~IImageWriter() = default;`
- L40 _public prototype_ `virtual TOptional<FText> Open(const FString& InDirectory, const FString& InFileName, const FString& InFormat) = 0;` — FileName is the name of file without the extensions while the Format represents an extension without the dot
- L41 _public prototype_ `virtual TOptional<FText> Close() = 0;`
- L43 _public prototype_ `virtual TOptional<FText> Append(UE::CaptureManager::FMediaTextureSample* InSample) = 0;`

#### class `ICalibrationWriter`  
`class ICalibrationWriter`  
_L46-57_
- L50 _public prototype_ `virtual ~ICalibrationWriter() = default;`
- L53 _public prototype_ `virtual TOptional<FText> Open(const FString& InDirectory, const FString& InFileName, const FString& InFormat) = 0;` — FileName is the name of file without the extensions while the Format represents an extension without the dot
- L54 _public prototype_ `virtual TOptional<FText> Close() = 0;`
- L56 _public prototype_ `virtual TOptional<FText> Append(UE::CaptureManager::FMediaCalibrationSample* InSample) = 0;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Public/MediaRWManager.h` (Public)


#### class `FMediaRWManager`  
`class FMediaRWManager`  
_L11-63_
- L15 _public prototype_ `FMediaRWManager();`
- L17 _public prototype_ `FMediaRWManager(const FMediaRWManager& InCopy) = delete;`
- L18 _public prototype_ `FMediaRWManager& operator=(const FMediaRWManager& InCopy) = delete;`
- L20 _public prototype_ `void RegisterAudioReader(const TArray<FString>& InFormats, TUniquePtr<IAudioReaderFactory> InReader);`
- L21 _public prototype_ `void RegisterVideoReader(const TArray<FString>& InFormats, TUniquePtr<IVideoReaderFactory> InReader);`
- L22 _public prototype_ `void RegisterCalibrationReader(const TArray<FString>& InFormats, TUniquePtr<ICalibrationReaderFactory> InReader);`
- L24 _public prototype_ `void RegisterAudioWriter(const TArray<FString>& InFormats, TUniquePtr<IAudioWriterFactory> InWriter);`
- L25 _public prototype_ `void RegisterImageWriter(const TArray<FString>& InFormats, TUniquePtr<IImageWriterFactory> InWriter);`
- L26 _public prototype_ `void RegisterCalibrationWriter(const TArray<FString>& InFormats, TUniquePtr<ICalibrationWriterFactory> InWriter);`
- L28 _public prototype_ `TUniquePtr<IAudioReader> CreateAudioReaderByFormat(const FString& InFormat, int32 InIndex = 0);`
- L29 _public prototype_ `TUniquePtr<IVideoReader> CreateVideoReaderByFormat(const FString& InFormat, int32 InIndex = 0);`
- L30 _public prototype_ `TUniquePtr<ICalibrationReader> CreateCalibrationReaderByFormat(const FString& InFormat, int32 InIndex = 0);`
- L32 _public prototype_ `TValueOrError<TUniquePtr<IAudioReader>, FText> CreateAudioReader(const FString& InPath, int32 InIndex = 0);`
- L33 _public prototype_ `TValueOrError<TUniquePtr<IVideoReader>, FText> CreateVideoReader(const FString& InPath, int32 InIndex = 0);`
- L34 _public prototype_ `TValueOrError<TUniquePtr<ICalibrationReader>, FText> CreateCalibrationReader(const FString& InPath, int32 InIndex = 0);`
- L36 _public prototype_ `TUniquePtr<IAudioWriter> CreateAudioWriterByFormat(const FString& InFormat, int32 InIndex = 0);`
- L37 _public prototype_ `TUniquePtr<IImageWriter> CreateImageWriterByFormat(const FString& InFormat, int32 InIndex = 0);`
- L38 _public prototype_ `TUniquePtr<ICalibrationWriter> CreateCalibrationWriterByFormat(const FString& InFormat, int32 InIndex = 0);`
- L40 _public prototype_ `TValueOrError<TUniquePtr<IAudioWriter>, FText> CreateAudioWriter(const FString& InDirectory, const FString& InFileName, const FString& InFormat, int32 InIndex = 0);`
- L41 _public prototype_ `TValueOrError<TUniquePtr<IImageWriter>, FText> CreateImageWriter(const FString& InDirectory, const FString& InFileName, const FString& InFormat, int32 InIndex = 0);`
- L42 _public prototype_ `TValueOrError<TUniquePtr<ICalibrationWriter>, FText> CreateCalibrationWriter(const FString& InDirectory, const FString& InFileName, const FString& InFormat, int32 InIndex = 0);`
- L46 _private member_ `TMap<FString, IAudioReaderFactory*> AudioReadersPerFormat;`
- L47 _private member_ `TArray<TUniquePtr<IAudioReaderFactory>> AudioReaders;`
- L49 _private member_ `TMap<FString, IVideoReaderFactory*> VideoReadersPerFormat;`
- L50 _private member_ `TArray<TUniquePtr<IVideoReaderFactory>> VideoReaders;`
- L52 _private member_ `TMap<FString, ICalibrationReaderFactory*> CalibrationReadersPerFormat;`
- L53 _private member_ `TArray<TUniquePtr<ICalibrationReaderFactory>> CalibrationReaders;`
- L55 _private member_ `TMap<FString, IAudioWriterFactory*> AudioWritersPerFormat;`
- L56 _private member_ `TArray<TUniquePtr<IAudioWriterFactory>> AudioWriters;`
- L58 _private member_ `TMap<FString, IImageWriterFactory*> ImageWritersPerFormat;`
- L59 _private member_ `TArray<TUniquePtr<IImageWriterFactory>> ImageWriters;`
- L61 _private member_ `TMap<FString, ICalibrationWriterFactory*> CalibrationWritersPerFormat;`
- L62 _private member_ `TArray<TUniquePtr<ICalibrationWriterFactory>> CalibrationWriters;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREMANAGERMEDIARW_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Public/MediaSample.h` (Public)


#### enum `UE::CaptureManager::ESampleRate`  
`enum class ESampleRate`  
_L13-22_
- L15 _public enumerator_ `SR_8000Hz = 0`
- L16 _public enumerator_ `SR_16000Hz`
- L17 _public enumerator_ `SR_44100Hz`
- L18 _public enumerator_ `SR_48000Hz`
- L19 _public enumerator_ `SR_88200Hz`
- L20 _public enumerator_ `SR_96000Hz`
- L21 _public enumerator_ `SR_192000Hz`

#### struct `UE::CaptureManager::FMediaAudioSample`  
`struct FMediaAudioSample`  
_L24-33_
- L26 _public member_ `TArray<uint8> Buffer;`
- L27 _public member_ `uint32 Channels;`
- L28 _public member_ `FTimespan Duration;`
- L29 _public member_ `EMediaAudioSampleFormat SampleFormat;`
- L30 _public member_ `uint32 Frames;`
- L31 _public member_ `ESampleRate SampleRate;`
- L32 _public member_ `FTimespan Time;`

#### enum `UE::CaptureManager::EMediaTexturePixelFormat`  
`enum class EMediaTexturePixelFormat`  
_L40-56_
- L42 _public enumerator_ `Undefined = -1`
- L43 _public enumerator_ `U8_RGB = 0`
- L44 _public enumerator_ `U8_BGR`
- L45 _public enumerator_ `U8_RGBA`
- L46 _public enumerator_ `U8_BGRA`
- L47 _public enumerator_ `U8_I444`
- L48 _public enumerator_ `U8_I420`
- L49 _public enumerator_ `U8_YUY2`
- L50 _public enumerator_ `U8_NV12`
- L51 _public enumerator_ `U8_Mono`
- L52 _public enumerator_ `U16_Mono`
- L53 _public enumerator_ `F_Mono`
- L55 _public enumerator_ `Default = U8_RGB`

#### struct `UE::CaptureManager::FMediaTextureSample`  
`struct FMediaTextureSample`  
_L58-69_
- L60 _public member_ `TArray<uint8> Buffer;`
- L61 _public member_ `int32 Stride = -1;`
- L62 _public member_ `FIntPoint Dimensions;`
- L63 _public member_ `FTimespan Duration;`
- L64 _public member_ `EMediaTexturePixelFormat CurrentFormat;`
- L65 _public member_ `EMediaTexturePixelFormat DesiredFormat;`
- L66 _public member_ `FTimespan Time;`
- L67 _public member_ `EMediaOrientation Orientation;`
- L68 _public member_ `EMediaOrientation Rotation;`

#### struct `UE::CaptureManager::FOpenCVDistortionModel`  
`struct FOpenCVDistortionModel`  
_L73-90_
- L88 _public member_ `FRadial Radial;`
- L89 _public member_ `FTangential Tangential;`

#### struct `UE::CaptureManager::FOpenCVDistortionModel::FRadial`  
`struct FRadial`  
_L75-80_
- L77 _public member_ `double K1 = 0.0;`
- L78 _public member_ `double K2 = 0.0;`
- L79 _public member_ `double K3 = 0.0;`

#### struct `UE::CaptureManager::FOpenCVDistortionModel::FTangential`  
`struct FTangential`  
_L82-86_
- L84 _public member_ `double P1 = 0.0;`
- L85 _public member_ `double P2 = 0.0;`

#### struct `UE::CaptureManager::FIphoneDistortionModel`  
`struct FIphoneDistortionModel`  
_L92-96_
- L94 _public member_ `TArray<double> LensDistortionTable;`
- L95 _public member_ `TArray<double> InverseLensDistortionTable;`

#### class `UE::CaptureManager::FCoordinateSystem`  
`class FCoordinateSystem`  
_L98-124_
- L112 _public prototype_ `FCoordinateSystem();`
- L113 _public prototype_ `FCoordinateSystem(FMatrix InMatDescription);`
- L114 _public prototype_ `FCoordinateSystem(FDirection InXDirection, FDirection InYDirection, FDirection InZDirection);`
- L116 _public prototype_ `const FMatrix& GetMatDescription() const;`
- L120 _private prototype_ `static int32 GetIndex(FDirection InDirection);`
- L121 _private prototype_ `static int32 GetSign(FDirection InDirection);`
- L123 _private member_ `FMatrix MatDescription;`

#### enum `UE::CaptureManager::FCoordinateSystem::FDirection`  
`enum FDirection`  
_L102-110_
- L104 _public enumerator_ `Front = 0`
- L105 _public enumerator_ `Back`
- L106 _public enumerator_ `Right`
- L107 _public enumerator_ `Left`
- L108 _public enumerator_ `Up`
- L109 _public enumerator_ `Down`

#### struct `UE::CaptureManager::FMediaCalibrationSample`  
`struct FMediaCalibrationSample`  
_L134-157_
- L144 _public member_ `FString CameraId;`
- L145 _public member_ `ECameraType CameraType = ECameraType::Unknown;`
- L147 _public member_ `FVector2D FocalLength;`
- L148 _public member_ `FVector2D PrincipalPoint;`
- L149 _public member_ `FTransform Transform;`
- L151 _public member_ `FIntPoint Dimensions;`
- L152 _public member_ `EMediaOrientation Orientation;`
- L154 _public member_ `TVariant<FEmptyVariantState, FIphoneDistortionModel, FOpenCVDistortionModel> DistortionModel;`
- L156 _public member_ `FCoordinateSystem InputCoordinateSystem;`

#### enum `UE::CaptureManager::FMediaCalibrationSample::ECameraType`  
`enum ECameraType`  
_L136-142_
- L138 _public enumerator_ `Video = 0`
- L139 _public enumerator_ `Depth`
- L141 _public enumerator_ `Unknown`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREMANAGERMEDIARW_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)
- L35 _prototype_ `int32 ConvertBitsPerSample(EMediaAudioSampleFormat InSampleFormat);` (scope `UE::CaptureManager`)
- L36 _prototype_ `int32 ConvertSampleRate(ESampleRate InSampleRate);` (scope `UE::CaptureManager`)
- L38 _prototype_ `ESampleRate ConvertSampleRate(int32 InSampleRate);` (scope `UE::CaptureManager`)
- L71 _prototype_ `uint32 GetNumberOfChannels(EMediaTexturePixelFormat InPixelFormat);` (scope `UE::CaptureManager`)
- L126 _function_ `inline bool operator==(const FCoordinateSystem& InLeft, const FCoordinateSystem& InRight)` (scope `UE::CaptureManager`)
- L131 _externvar_ `extern const FCoordinateSystem UnrealCS;` (scope `UE::CaptureManager`)
- L132 _externvar_ `extern const FCoordinateSystem OpenCvCS;` (scope `UE::CaptureManager`)
- L159 _prototype_ `FVector ConvertToCoordinateSystem(const FVector& InVector, const FCoordinateSystem& InInputCoordinateSystem, const FCoordinateSystem& InOutputCoordinateSystem);` (scope `UE::CaptureManager`)
- L163 _prototype_ `FTransform ConvertToCoordinateSystem(const FTransform& InTransform, const FCoordinateSystem& InInputCoordinateSystem, const FCoordinateSystem& InOutputCoordinateSystem);` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureManagerMediaRW/Public/Utils/MediaPixelFormatConversions.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace CaptureManager` (scope `UE`)
- L8 _prototype_ `TArray<uint8> ConvertYUVToMono(const UE::CaptureManager::FMediaTextureSample* InSample, bool InScaleRange);` (scope `UE::CaptureManager`) — Any YUV to Mono
- L9 _prototype_ `TArray<uint8> ConvertYUY2ToMono(const UE::CaptureManager::FMediaTextureSample* InSample, bool InScaleRange);` (scope `UE::CaptureManager`)
- L10 _prototype_ `TArray<uint8> ConvertI420ToBGRA(const UE::CaptureManager::FMediaTextureSample* InSample);` (scope `UE::CaptureManager`)
- L11 _prototype_ `TArray<uint8> ConvertNV12ToBGRA(const UE::CaptureManager::FMediaTextureSample* InSample);` (scope `UE::CaptureManager`)
- L12 _prototype_ `TArray<uint8> ConvertYUY2ToBGRA(const UE::CaptureManager::FMediaTextureSample* InSample);` (scope `UE::CaptureManager`)
- L14 _prototype_ `TArray<FColor> UEConvertYUVToMono(const UE::CaptureManager::FMediaTextureSample* InSample, bool InScaleRange);` (scope `UE::CaptureManager`) — Any YUV to Mono
- L15 _prototype_ `TArray<FColor> UEConvertYUY2ToMono(const UE::CaptureManager::FMediaTextureSample* InSample, bool InScaleRange);` (scope `UE::CaptureManager`)
- L16 _prototype_ `TArray<FColor> UEConvertI420ToBGRA(const UE::CaptureManager::FMediaTextureSample* InSample);` (scope `UE::CaptureManager`)
- L17 _prototype_ `TArray<FColor> UEConvertNV12ToBGRA(const UE::CaptureManager::FMediaTextureSample* InSample);` (scope `UE::CaptureManager`)
- L18 _prototype_ `TArray<FColor> UEConvertYUY2ToBGRA(const UE::CaptureManager::FMediaTextureSample* InSample);` (scope `UE::CaptureManager`)
