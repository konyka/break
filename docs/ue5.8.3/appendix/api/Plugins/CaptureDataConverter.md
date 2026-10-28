# Plugins / CaptureDataConverter

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter`
- headers: 18; symbols: 207
- symbol kinds: class=16, delegate=1, enum=2, enumerator=18, function=2, macro=4, member=64, namespace=11, prototype=67, struct=9, typedef=3, variable=10
- PrivateDependencyModuleNames: CaptureDataUtils, CoreUObject, DataIngestCore, Engine, ImageWrapper, Json, Media, NamingTokens
- PublicDependencyModuleNames: CaptureManagerMediaRW, CaptureManagerPipeline, CaptureManagerTakeMetadata, CaptureUtils, Core

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Internal/CaptureManagerConversionTypes.h` (Internal)


#### enum `ECaptureManagerPixelFormat`  
`enum class ECaptureManagerPixelFormat : uint8`  
_L13-31_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `U8_RGB = 0 UMETA(DisplayName = "RGB 8-bit")` — Packed RGB
- L17 _public enumerator_ `U8_BGR UMETA(DisplayName = "BGR 8-bit")`
- L18 _public enumerator_ `U8_RGBA UMETA(DisplayName = "RGBA 8-bit")`
- L19 _public enumerator_ `U8_BGRA UMETA(DisplayName = "BGRA 8-bit")`
- L21 _public enumerator_ `U8_I444 UMETA(DisplayName = "I444 8-bit")` — Planar YUV — only supported when a third-party encoder (e.g. FFmpeg) is configured.
- L22 _public enumerator_ `U8_I420 UMETA(DisplayName = "I420 8-bit")`
- L23 _public enumerator_ `U8_NV12 UMETA(DisplayName = "NV12 8-bit")`
- L25 _public enumerator_ `U8_Mono UMETA(DisplayName = "Mono 8-bit")` — Grayscale
- L26 _public enumerator_ `U16_Mono UMETA(DisplayName = "Mono 16-bit")`
- L27 _public enumerator_ `F_Mono UMETA(DisplayName = "Mono Float")`
- L29 _public enumerator_ `Default = U8_RGB UMETA(DisplayName = "Default (U8_RGB)")`
- L30 _public enumerator_ `Undefined = 255 UMETA(Hidden)`

#### enum `ECaptureManagerRotation`  
`enum class ECaptureManagerRotation : uint8`  
_L34-43_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `None = 0 UMETA(DisplayName = "None")`
- L37 _public enumerator_ `CW_90 UMETA(DisplayName = "Clockwise 90°")`
- L38 _public enumerator_ `CW_180 UMETA(DisplayName = "Clockwise 180°")`
- L39 _public enumerator_ `CW_270 UMETA(DisplayName = "Clockwise 270°")`
- L40 _public enumerator_ `Auto = 255 UMETA(DisplayName = "Auto")`
- L42 _public enumerator_ `Default = Auto UMETA(DisplayName = "Default (Auto)")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CAPTUREDATACONVERTER_API`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace CaptureManager` (scope `UE`)
- L49 _prototype_ `EMediaTexturePixelFormat ToMediaPixelFormat(ECaptureManagerPixelFormat InPixelFormat);` (scope `UE::CaptureManager`) — Maps ECaptureManagerPixelFormat to the Core media pipeline type.
- L52 _prototype_ `EMediaOrientation ToMediaOrientation(ECaptureManagerRotation InRotation);` (scope `UE::CaptureManager`) — Maps ECaptureManagerRotation to the Core media pipeline type.
- L55 _prototype_ `EMediaOrientation ToUprightRotation(FTakeMetadata::FVideo::EOrientation InOrientation);` (scope `UE::CaptureManager`) — Converts a sensor capture orientation to the image rotation needed to display it upright.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/CaptureManagerEncoderCommands.h` (Private)


#### class `UE::CaptureManager::FAudioEncoderCommand`  
`class FAudioEncoderCommand`  
_L30-40_
- L33 _public prototype_ `FAudioEncoderCommand(FString InEncoderPath, FString InEncoderArgs);`
- L35 _public prototype_ `FProcessRunnerResult Execute(const FString& InInputPath, const FString& InOutputPath, const FStopToken* InStopToken = nullptr) const;`
- L38 _private member_ `const FString EncoderPath;`
- L39 _private member_ `const FString EncoderArgs;`

#### class `UE::CaptureManager::FVideoEncoderCommand`  
`class FVideoEncoderCommand`  
_L42-52_
- L45 _public prototype_ `FVideoEncoderCommand(FString InEncoderPath, FString InEncoderArgs);`
- L47 _public prototype_ `FProcessRunnerResult Execute(const FString& InInputPath, const FString& InOutputPath, const FString& InVideoParams, const FStopToken* InStopToken = nullptr) const;`
- L50 _private member_ `const FString EncoderPath;`
- L51 _private member_ `const FString EncoderArgs;`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/CaptureConvertAudioData.h` (Private)


#### class `FCaptureConvertAudioData`  
`class FCaptureConvertAudioData final : public FConvertAudioNode`  
_L11-30_
- inherits: `FConvertAudioNode`
- L16 _public prototype_ `FCaptureConvertAudioData(const FTakeMetadata::FAudio& InAudio, const FString& InOutputDirectory, const FCaptureConvertDataNodeParams& InParams, const FCaptureConvertAudioOutputParams& InAudioParams);`
- L23 _private prototype_ `virtual FResult Run() override;`
- L25 _private prototype_ `FResult CopyAudioFile();`
- L26 _private prototype_ `FResult ConvertAudioFile();`
- L28 _private member_ `FCaptureConvertDataNodeParams Params;`
- L29 _private member_ `FCaptureConvertAudioOutputParams AudioParams;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/CaptureConvertCalibrationData.h` (Private)


#### class `FCaptureConvertCalibrationData`  
`class FCaptureConvertCalibrationData final : public FConvertCalibrationNode`  
_L11-30_
- inherits: `FConvertCalibrationNode`
- L16 _public prototype_ `FCaptureConvertCalibrationData(const FTakeMetadata::FCalibration& InCalibration, const FString& InOutputDirectory, const FCaptureConvertDataNodeParams& InParams, const FCaptureConvertCalibrationOutputParams& InCalibrationParams);`
- L23 _private prototype_ `virtual FResult Run() override;`
- L25 _private prototype_ `FResult CopyCalibrationFile();`
- L26 _private prototype_ `FResult ConvertCalibrationFile();`
- L28 _private member_ `FCaptureConvertDataNodeParams Params;`
- L29 _private member_ `FCaptureConvertCalibrationOutputParams CalibrationParams;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/CaptureConvertDepthData.h` (Private)


#### class `FCaptureConvertDepthData`  
`class FCaptureConvertDepthData final : public FConvertDepthNode`  
_L11-53_
- inherits: `FConvertDepthNode`
- L16 _public prototype_ `FCaptureConvertDepthData(const FTakeMetadata::FVideo& InDepth, const FString& InOutputDirectory, const FCaptureConvertDataNodeParams& InParams, const FCaptureConvertDepthOutputParams& InDepthParams);`
- L25 _private prototype_ `virtual FResult Run() override;`
- L27 _private prototype_ `FResult ConvertData();`
- L28 _private prototype_ `FResult CopyData();`
- L30 _private member_ `FCaptureConvertDataNodeParams Params;`
- L31 _private member_ `FCaptureConvertDepthOutputParams DepthParams;`
- L49 _private typedef_ `using FWriteResult = TValueOrError<void, FText>;`
- L50 _private prototype_ `FWriteResult OnWrite(FWritingContext InContext);`
- L52 _private member_ `int32 CurrentFrame = 0;`

#### struct `FCaptureConvertDepthData::FWritingContext`  
`struct FWritingContext`  
_L33-47_
- L35 _public function_ `FWritingContext() : ReadSample(nullptr) , Writer(nullptr) , Task(nullptr) , TotalDuration(0)`
- L43 _public member_ `TUniquePtr<UE::CaptureManager::FMediaTextureSample> ReadSample;`
- L44 _public member_ `class IImageWriter* Writer;`
- L45 _public member_ `UE::CaptureManager::FTaskProgress::FTask* Task;`
- L46 _public member_ `TOptional<int32> TotalDuration;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/CaptureConvertVideoData.h` (Private)


#### class `FCaptureConvertVideoData`  
`class FCaptureConvertVideoData final : public FConvertVideoNode`  
_L14-58_
- inherits: `FConvertVideoNode`
- L19 _public prototype_ `FCaptureConvertVideoData(const FTakeMetadata::FVideo& InVideo, const FString& InOutputDirectory, const FCaptureConvertDataNodeParams& InParams, const FCaptureConvertVideoOutputParams& InVideoParams);`
- L28 _private prototype_ `virtual FResult Run() override;`
- L30 _private prototype_ `FResult ConvertData();`
- L31 _private prototype_ `bool ShouldCopy() const;`
- L32 _private prototype_ `FResult CopyData();`
- L34 _private prototype_ `EMediaOrientation ConvertOrientation(FTakeMetadata::FVideo::EOrientation InOrientation) const;`
- L36 _private member_ `FCaptureConvertDataNodeParams Params;`
- L37 _private member_ `FCaptureConvertVideoOutputParams VideoParams;`
- L56 _private typedef_ `using FWriteResult = TValueOrError<void, FText>;`
- L57 _private prototype_ `FWriteResult OnWrite(FWritingContext InContext);`

#### struct `FCaptureConvertVideoData::FWritingContext`  
`struct FWritingContext`  
_L39-54_
- L41 _public function_ `FWritingContext() : ReadSample(nullptr) , Writer(nullptr) , Task(nullptr) , TotalDuration(0.0f)`
- L49 _public member_ `TUniquePtr<UE::CaptureManager::FMediaTextureSample> ReadSample;`
- L50 _public member_ `class IImageWriter* Writer;`
- L51 _public member_ `UE::CaptureManager::FTaskProgress::FTask* Task;`
- L53 _public member_ `double TotalDuration;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/CaptureCopyProgressReporter.h` (Private)


#### class `FCopyProgressReporter`  
`class FCopyProgressReporter final : public FCopyProgress`  
_L10-23_
- inherits: `FCopyProgress`
- L14 _public prototype_ `FCopyProgressReporter(UE::CaptureManager::FTaskProgress::FTask& InTask, UE::CaptureManager::FStopToken InStopToken);`
- L17 _public prototype_ `virtual bool Poll(float InProgress) override;`
- L21 _private member_ `UE::CaptureManager::FTaskProgress::FTask& Task;`
- L22 _private member_ `UE::CaptureManager::FStopToken StopToken;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/CaptureValidationNode.h` (Private)


#### class `FCaptureValidationNode`  
`class FCaptureValidationNode final : public FCaptureManagerPipelineNode`  
_L13-34_
- inherits: `FCaptureManagerPipelineNode`
- L18 _public prototype_ `FCaptureValidationNode(const FCaptureDataConverterParams& InParams, const FTakeMetadata& InTakeMetadata);`
- L23 _private member_ `static const FString TakeJsonFileName;`
- L25 _private prototype_ `virtual FResult Prepare() override;`
- L26 _private prototype_ `virtual FResult Run() override;`
- L27 _private prototype_ `virtual FResult Validate() override;`
- L29 _private prototype_ `static FResult CheckImages(const FString& InImagesPath, TOptional<EImageFormat> InFormat);`
- L30 _private prototype_ `static FResult CheckAudio(const FString& InExpectedFileName, const FString& InAudio);`
- L32 _private member_ `FCaptureDataConverterParams Params;`
- L33 _private member_ `FTakeMetadata TakeMetadata;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/ThirdPartyEncoder/CaptureConvertAudioDataThirdParty.h` (Private)


#### class `FCaptureConvertAudioDataThirdParty`  
`class FCaptureConvertAudioDataThirdParty final : public FConvertAudioNode`  
_L11-33_
- inherits: `FConvertAudioNode`
- L16 _public prototype_ `FCaptureConvertAudioDataThirdParty(UE::CaptureManager::FAudioEncoderCommand InThirdPartyCommand, const FTakeMetadata::FAudio& InAudio, const FString& InOutputDirectory, const FCaptureConvertDataNodeParams& InParams, const FCaptureConvertAudioOutputParams& InAudioParams );`
- L25 _private prototype_ `virtual FResult Run() override;`
- L27 _private prototype_ `FResult CopyAudioFile();`
- L28 _private prototype_ `FResult ConvertAudioFile();`
- L30 _private member_ `UE::CaptureManager::FAudioEncoderCommand ThirdPartyCommand;`
- L31 _private member_ `FCaptureConvertDataNodeParams Params;`
- L32 _private member_ `FCaptureConvertAudioOutputParams AudioParams;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/ThirdPartyEncoder/CaptureConvertVideoDataThirdParty.h` (Private)


#### class `FCaptureConvertVideoDataThirdParty`  
`class FCaptureConvertVideoDataThirdParty final : public FConvertVideoNode`  
_L10-32_
- inherits: `FConvertVideoNode`
- L15 _public prototype_ `FCaptureConvertVideoDataThirdParty(UE::CaptureManager::FVideoEncoderCommand InThirdPartyCommand, const FTakeMetadata::FVideo& InVideo, const FString& InOutputDirectory, const FCaptureConvertDataNodeParams& InParams, const FCaptureConvertVideoOutputParams& InVideoParams);`
- L23 _private prototype_ `virtual FResult Run() override;`
- L25 _private prototype_ `FResult ConvertData();`
- L26 _private prototype_ `bool ShouldCopy() const;`
- L27 _private prototype_ `FResult CopyData();`
- L29 _private member_ `UE::CaptureManager::FVideoEncoderCommand ThirdPartyCommand;`
- L30 _private member_ `FCaptureConvertDataNodeParams Params;`
- L31 _private member_ `FCaptureConvertVideoOutputParams VideoParams;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Private/Nodes/ThirdPartyEncoder/CaptureThirdPartyNodeUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L10 _prototype_ `FString WrapInQuotes(const FString& InString);` (scope `UE::CaptureManager`)
- L11 _prototype_ `TArray<uint8> ReadPipe(void* InReadPipe);` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Public/CaptureDataConverter.h` (Public)


#### struct `FCaptureDataConverterParams`  
`struct FCaptureDataConverterParams`  
_L18-38_
- L20 _public member_ `FTakeMetadata TakeMetadata;`
- L22 _public member_ `FString TakeName;`
- L23 _public member_ `FString TakeOriginDirectory;`
- L24 _public member_ `FString TakeOutputDirectory;`
- L26 _public member_ `TOptional<FCaptureConvertVideoOutputParams> VideoOutputParams;`
- L27 _public member_ `TOptional<FCaptureConvertAudioOutputParams> AudioOutputParams;`
- L28 _public member_ `TOptional<FCaptureConvertDepthOutputParams> DepthOutputParams;`
- L29 _public member_ `TOptional<FCaptureConvertCalibrationOutputParams> CalibrationOutputParams;`
- L31 _public member_ `TOptional<FCaptureManagerEncoderConfig> AudioEncoderConfig;`
- L32 _public member_ `TOptional<FCaptureManagerEncoderConfig> VideoEncoderConfig;`
- L37 _public member_ `UE_INTERNAL TOptional<UE::CaptureManager::FStopToken> ExternalStopToken;` — When set, conversion nodes check this token for cancellation instead of the converter's internal stop requester. Cancel() on the converter only signals the internal requester, so cooperative node cancellation must be driven by the token's owner.

#### class `FCaptureDataConverter`  
`class FCaptureDataConverter`  
_L43-65_
- L47 _public prototype_ `DECLARE_DELEGATE_OneParam(FProgressReporter, double InProgress);`
- L49 _public prototype_ `FCaptureDataConverter();`
- L50 _public prototype_ `~FCaptureDataConverter();`
- L52 _public prototype_ `void AddCustomNode(TSharedPtr<FCaptureConvertCustomData> InCustomNode);`
- L53 _public prototype_ `void AddSyncNode(TSharedPtr<FCaptureConvertCustomData> InCustomNode);`
- L55 _public prototype_ `[[nodiscard]] FCaptureDataConverterResult<void> Run(FCaptureDataConverterParams InParams, FProgressReporter InProgressReporter);`
- L56 _public prototype_ `void Cancel();`
- L60 _private member_ `TArray<TSharedPtr<FCaptureConvertCustomData>> CustomNodes;`
- L61 _private member_ `TArray<TSharedPtr<FCaptureConvertCustomData>> SyncNodes;`
- L63 _private member_ `TSharedPtr<FCaptureManagerPipeline> Pipeline;`
- L64 _private member_ `UE::CaptureManager::FStopRequester StopRequester;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CAPTUREDATACONVERTER_API`
- L41 _typedef_ `template<typename T> using FCaptureDataConverterResult = TValueOrError<T, FCaptureDataConverterError>;`
- L47 _delegate_ `DECLARE_DELEGATE_OneParam(FProgressReporter, double InProgress);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Public/CaptureDataConverterError.h` (Public)


#### class `FCaptureDataConverterError`  
`class FCaptureDataConverterError`  
_L9-21_
- L13 _public prototype_ `explicit FCaptureDataConverterError(TArray<FText> InErrors);`
- L14 _public prototype_ `~FCaptureDataConverterError();`
- L16 _public prototype_ `TArray<FText> GetErrors() const;`
- L20 _private member_ `TArray<FText> Errors;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CAPTUREDATACONVERTER_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Public/CaptureDataConverterNodeParams.h` (Public)


#### struct `FCaptureConvertDataNodeParams`  
`struct FCaptureConvertDataNodeParams`  
_L10-15_
- L12 _public member_ `FString TakeOriginDirectory;`
- L13 _public member_ `TSharedPtr<UE::CaptureManager::FTaskProgress> TaskProgress;`
- L14 _public member_ `UE::CaptureManager::FStopToken StopToken;`

#### struct `FCaptureConvertVideoOutputParams`  
`struct FCaptureConvertVideoOutputParams`  
_L17-23_
- L19 _public member_ `FString ImageFileName = TEXT("fra`
- L20 _public member_ `FString Format;`
- L21 _public member_ `UE::CaptureManager::EMediaTexturePixelFormat OutputPixelFormat = UE::CaptureManager::EMediaTexturePixelFormat::Undefined;`
- L22 _public member_ `EMediaOrientation Rotation = EMediaOrientation::Original;`

#### struct `FCaptureConvertAudioOutputParams`  
`struct FCaptureConvertAudioOutputParams`  
_L25-29_
- L27 _public member_ `FString AudioFileName = TEXT("aud`
- L28 _public member_ `FString Format = TEXT("wav`

#### struct `FCaptureConvertDepthOutputParams`  
`struct FCaptureConvertDepthOutputParams`  
_L31-36_
- L33 _public member_ `FString ImageFileName = TEXT("dep`
- L34 _public member_ `bool bShouldCompressFiles = true;`
- L35 _public member_ `EMediaOrientation Rotation = EMediaOrientation::Original;`

#### struct `FCaptureConvertCalibrationOutputParams`  
`struct FCaptureConvertCalibrationOutputParams`  
_L38-41_
- L40 _public member_ `FString FileName = TEXT("cal`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Public/CaptureManagerEncoderConfig.h` (Public)


#### struct `FCaptureManagerEncoderConfig`  
`struct FCaptureManagerEncoderConfig`  
_L50-54_
- desc: Encoder path and Pass-1-resolved encoder args supplied by the caller. CaptureDataConverter constructs the private command objects from this internally.
- L52 _public member_ `FString EncoderPath;`
- L53 _public member_ `FString EncoderArgs;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CaptureManager` (scope `UE`)
- L14 _namespace_ `namespace VideoEncoderTokens` (scope `UE::CaptureManager`)
- L16 _variable_ `static constexpr FStringView Namespace = TEXTVIEW("cmv` (scope `UE::CaptureManager::VideoEncoderTokens`)
- L17 _variable_ `static constexpr FStringView InputKey = TEXTVIEW("inp` (scope `UE::CaptureManager::VideoEncoderTokens`)
- L18 _variable_ `static constexpr FStringView OutputKey = TEXTVIEW("out` (scope `UE::CaptureManager::VideoEncoderTokens`)
- L19 _variable_ `static constexpr FStringView ParamsKey = TEXTVIEW("par` (scope `UE::CaptureManager::VideoEncoderTokens`)
- L22 _namespace_ `namespace AudioEncoderTokens` (scope `UE::CaptureManager`)
- L24 _variable_ `static constexpr FStringView Namespace = TEXTVIEW("cma` (scope `UE::CaptureManager::AudioEncoderTokens`)
- L25 _variable_ `static constexpr FStringView InputKey = TEXTVIEW("inp` (scope `UE::CaptureManager::AudioEncoderTokens`)
- L26 _variable_ `static constexpr FStringView OutputKey = TEXTVIEW("out` (scope `UE::CaptureManager::AudioEncoderTokens`)
- L29 _namespace_ `namespace EncoderDefaults` (scope `UE::CaptureManager`)
- L31 _variable_ `static constexpr FStringView AudioCommandArgs = TEXTVIEW("-i` (scope `UE::CaptureManager::EncoderDefaults`)
- L37 _variable_ `static constexpr FStringView VideoCommandArgs = TEXTVIEW("-no` (scope `UE::CaptureManager::EncoderDefaults`) — -fps_mode passthrough emits exactly one output image per decoded frame in decode order. Without it, ffmpeg's default CFR resampling duplicates a video frame at each timing-drift crossing (the camera runs slightly below 30 fps, e.g. 29.9939), which desyncs the RGB image sequence from the sequentially-read depth (RGB gains frames, drift accumulates with take length). Passthrough keeps the video 1:1 with depth, matching the WMF ingest route.
- L43 _variable_ `static constexpr FStringView LegacyVideoCommandArgs_NoFpsMode = TEXTVIEW("-no` (scope `UE::CaptureManager::EncoderDefaults`) — Previously-shipped default video command (pre -fps_mode passthrough). Earlier builds persisted the default straight into the per-user config (defaultconfig), freezing it. The settings migration rewrites any stored value still matching this to the current VideoCommandArgs default so the RGB/depth sync fix reaches existing users.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Public/CaptureManagerEncoderNamingTokens.h` (Public)


#### class `UCaptureManagerVideoEncoderTokens`  
`class UCaptureManagerVideoEncoderTokens final : public UNamingTokens`  
_L10-23_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable)`
- inherits: `UNamingTokens`
- L15 _public prototype_ `UCaptureManagerVideoEncoderTokens();`
- L19 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& OutTokens) override;`
- L20 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L21 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`

#### class `UCaptureManagerAudioEncoderTokens`  
`class UCaptureManagerAudioEncoderTokens final : public UNamingTokens`  
_L27-40_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable)`
- inherits: `UNamingTokens`
- L32 _public prototype_ `UCaptureManagerAudioEncoderTokens();`
- L36 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& OutTokens) override;`
- L37 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L38 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Public/Nodes/CaptureConvertCustomData.h` (Public)


#### class `FCaptureConvertCustomData`  
`class FCaptureConvertCustomData : public FCaptureManagerPipelineNode, public FCaptureConvertParams`  
_L8-15_
- inherits: `FCaptureManagerPipelineNode,FCaptureConvertParams`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureDataConverter/Public/Nodes/CaptureConvertParams.h` (Public)


#### class `FCaptureConvertParams`  
`class FCaptureConvertParams`  
_L11-24_
- L15 _public prototype_ `FCaptureConvertParams();`
- L16 _public prototype_ `virtual ~FCaptureConvertParams();`
- L18 _public prototype_ `void SetParams(const FCaptureConvertDataNodeParams& InParams);`
- L22 _protected member_ `FCaptureConvertDataNodeParams Params;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREDATACONVERTER_API`
