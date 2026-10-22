# Plugins / CaptureMetadataExtraction

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction`
- headers: 13; symbols: 193
- symbol kinds: class=9, enum=7, enumerator=31, function=4, macro=8, member=55, namespace=29, prototype=36, struct=8, typedef=6
- PrivateDependencyModuleNames: CaptureDataCore, CaptureDataUtils, CaptureManagerMediaRW, CaptureUtils, DataIngestCore, ElectraPlayerPlugin, Json, Media, MediaAssets
- PublicDependencyModuleNames: CaptureManagerTakeMetadata, Core, CoreUObject, Engine

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Internal/CaptureManagerCalibrationUtils.h` (Internal)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CAPTUREMETADATAEXTRACTION_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L17 _prototype_ `FString DetectCalibrationFormat(const FString& InFilePath);` (scope `UE::CaptureManager`) — Inspects a JSON calibration file to determine whether it is OpenCV or Unreal format. Returns "opencv", "unreal", or empty string if the format cannot be determined. Detection mirrors the entry checks in the actual parsers: OpenCV (OpenCVCalibrationReader.cpp): root array, elements have "fx" Unreal (UnrealCalibrationParser.cpp): root object with "Calibrations" key

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Internal/CaptureManagerExtractionConfig.h` (Internal)


#### struct `UE::CaptureManager::FExtractionConfig`  
`struct FExtractionConfig`  
_L10-14_
- L12 _public member_ `bool bUseFFprobe = false;`
- L13 _public member_ `FString FFmpegPath;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Internal/CaptureManagerFileExtensions.h` (Internal)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L13 _function_ `inline bool IsVideoExtension(FStringView Ext)` (scope `UE::CaptureManager`) — Returns true if the extension (without leading dot) is a recognized video container format. Case-insensitive.
- L23 _function_ `inline bool IsAudioExtension(FStringView Ext)` (scope `UE::CaptureManager`) — Returns true if the extension (without leading dot) is a recognized audio format. Case-insensitive.
- L33 _function_ `inline bool IsImageExtension(FStringView Ext)` (scope `UE::CaptureManager`) — Returns true if the extension (without leading dot) is a supported image-sequence format. Case-insensitive.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Internal/LiveLinkFaceMetadata.h` (Internal)


#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CAPTUREMETADATAEXTRACTION_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace CaptureManager` (scope `UE`)
- L14 _namespace_ `namespace LiveLinkMetadata` (scope `UE::CaptureManager`)
- L17 _prototype_ `TOptional<FTakeMetadata> ParseOldLiveLinkTakeMetadata(const FString& InJsonFile, TArray<FText>& OutValidationError);` (scope `UE::CaptureManager::LiveLinkMetadata`)
- L18 _prototype_ `TArray<FTakeMetadata::FVideo> ParseOldLiveLinkVideoMetadataFromString(const FString& InJsonString, TArray<FText>& OutValidationError);` (scope `UE::CaptureManager::LiveLinkMetadata`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Internal/LiveLinkFaceMetadataExtractor.h` (Internal)


#### enum `UE::CaptureManager::ELiveLinkFaceExtractionError`  
`enum class ELiveLinkFaceExtractionError : uint8`  
_L13-19_
- L15 _public enumerator_ `DirectoryNotFound`
- L16 _public enumerator_ `MetadataFileNotFound` — directory exists but contains no .cptake or legacy metadata
- L17 _public enumerator_ `MetadataFormatNotRecognized` — metadata file found but could not be parsed
- L18 _public enumerator_ `MultipleMetadataFilesFound` — directory contains more than one .cptake file; legacy JSON is not multiplicity-checked

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREMETADATAEXTRACTION_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)
- L24 _prototype_ `ExtractLiveLinkFaceMetadata(const FString& InTakeDirectoryPath, const FExtractionConfig& InConfig);` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Internal/MonoVideoMetadataExtractor.h` (Internal)


#### enum `UE::CaptureManager::EMonoVideoExtractionError`  
`enum class EMonoVideoExtractionError : uint8`  
_L13-18_
- L15 _public enumerator_ `VideoFileNotFound`
- L16 _public enumerator_ `UnsupportedVideoFormat`
- L17 _public enumerator_ `AudioFileNotFound`

#### struct `UE::CaptureManager::FMonoVideoDescriptor`  
`struct FMonoVideoDescriptor`  
_L20-26_
- L22 _public member_ `FString VideoFilePath;`
- L23 _public member_ `TArray<FString> AudioFilePaths;` — empty = use embedded audio if present
- L24 _public member_ `FString Slate;` — empty = derived from video filename stem
- L25 _public member_ `int32 TakeNumber = 1;` — clamped to 1 if < 1

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREMETADATAEXTRACTION_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)
- L31 _prototype_ `ExtractMonoVideoMetadata(FMonoVideoDescriptor InDescriptor, const FExtractionConfig& InConfig);` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Internal/StereoVideoMetadataExtractor.h` (Internal)


#### enum `UE::CaptureManager::EStereoVideoExtractionError`  
`enum class EStereoVideoExtractionError : uint8`  
_L13-23_
- L15 _public enumerator_ `VideoANotFound`
- L16 _public enumerator_ `VideoBNotFound`
- L17 _public enumerator_ `UnsupportedVideoFormatA` — video A: not a supported video file or image sequence directory
- L18 _public enumerator_ `UnsupportedVideoFormatB` — video B: not a supported video file or image sequence directory
- L19 _public enumerator_ `VideoTypeMismatch` — video A is a file, video B is a folder, or vice versa
- L20 _public enumerator_ `AudioFileNotFound`
- L21 _public enumerator_ `CalibrationFileNotFound`
- L22 _public enumerator_ `CalibrationFormatUnrecognized` — calibration file provided but format could not be detected

#### struct `UE::CaptureManager::FStereoVideoDescriptor`  
`struct FStereoVideoDescriptor`  
_L25-33_
- L27 _public member_ `FString VideoPathA;` — video file (.mp4/.mov) or image sequence folder
- L28 _public member_ `FString VideoPathB;` — same type as video A
- L29 _public member_ `TArray<FString> AudioFilePaths;` — empty = no audio
- L30 _public member_ `FString CalibrationFilePath;` — empty = no calibration; format auto-detected from JSON structure
- L31 _public member_ `FString Slate;` — empty = derived from video A stem/folder name
- L32 _public member_ `int32 TakeNumber = 1;` — clamped to 1 if < 1

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREMETADATAEXTRACTION_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)
- L38 _prototype_ `ExtractStereoVideoMetadata(FStereoVideoDescriptor InDescriptor, const FExtractionConfig& InConfig);` (scope `UE::CaptureManager`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Internal/TakeArchiveMetadataExtractor.h` (Internal)


#### enum `UE::CaptureManager::ETakeArchiveExtractionError`  
`enum class ETakeArchiveExtractionError : uint8`  
_L13-17_
- L15 _public enumerator_ `MetadataFileNotFound`
- L16 _public enumerator_ `MetadataFormatNotRecognized`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREMETADATAEXTRACTION_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)
- L21 _prototype_ `TValueOrError<FTakeMetadata, ETakeArchiveExtractionError> ExtractTakeArchiveMetadata(const FString& InMetadataFilePath, const FExtractionConfig& InConfig);` (scope `UE::CaptureManager`) — Media probing (timecodes, frame rate, orientation) is best-effort. Probe failure is non-fatal - extraction succeeds with missing values.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Private/ResolutionResolver.h` (Private)


#### class `UE::CaptureManager::FResolutionResolver`  
`class FResolutionResolver`  
_L20-45_
- desc: Class used to determine and validate the image resolution for a set of stereo camera data. Each time a camera is added to the resolver, the internal state is updated and will influence the result of the final Resolve() call. A collective value for the image resolution will only be returned if all of the cameras share the same image resolution.
- L36 _public prototype_ `TValueOrError<FIntPoint, EAddError> Add(const FStereoCameraTakeInfo::FCamera& Camera);`
- L37 _public prototype_ `TValueOrError<FIntPoint, EResolveError> Resolve() const;`
- L40 _private prototype_ `TValueOrError<FIntPoint, EAddError> GetCameraResolution(const FStereoCameraTakeInfo::FCamera& Camera) const;`
- L41 _private prototype_ `TValueOrError<FIntPoint, EAddError> GetResolutionFromSingleImage(const FString& InDirectoryPath) const;`
- L43 _private member_ `FIntPoint CommonResolution = FIntPoint::NoneValue;`
- L44 _private member_ `bool bAllEqual = true;`

#### enum `UE::CaptureManager::FResolutionResolver::EAddError`  
`enum class EAddError`  
_L23-29_
- L25 _public enumerator_ `FramesPathDoesNotExist`
- L26 _public enumerator_ `NoImagesFound`
- L27 _public enumerator_ `ImageLoadFailed`
- L28 _public enumerator_ `InvalidImageWrapper`

#### enum `UE::CaptureManager::FResolutionResolver::EResolveError`  
`enum class EResolveError`  
_L31-34_
- L33 _public enumerator_ `Mismatched`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Private/StereoCameraMetadataParseUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CAPTUREMETADATAEXTRACTION_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)
- L9 _namespace_ `namespace StereoCameraMetadata` (scope `UE::CaptureManager`)
- L12 _prototype_ `TOptional<FTakeMetadata> ParseOldStereoCameraMetadata(const FString& InTakeFolder, TArray<FText>& OutValidationError);` (scope `UE::CaptureManager::StereoCameraMetadata`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Private/StereoCameraTakeMetadata.h` (Private)


#### class `FStereoCameraInfo`  
`class FStereoCameraInfo`  
_L15-21_
- L19 _public member_ `FString Name;`
- L20 _public member_ `FCameraCalibration Calibration;`

#### class `FStereoCameraTakeInfo`  
`class FStereoCameraTakeInfo`  
_L23-70_
- L43 _public typedef_ `using FCameraMap = TMap<FString, FCamera>;`
- L52 _public typedef_ `using FAudioArray = TArray<FAudio>;`
- L54 _public member_ `uint32 Version = 0;`
- L55 _public member_ `FString Id;`
- L56 _public member_ `uint32 Take = 0;`
- L57 _public member_ `FString Slate;`
- L58 _public member_ `FString ThumbnailPath;`
- L59 _public member_ `FDateTime Date;`
- L60 _public member_ `FDeviceInfo DeviceInfo;`
- L61 _public member_ `FString CalibrationFilePath;`
- L63 _public member_ `FCameraMap CameraMap;`
- L64 _public member_ `FAudioArray AudioArray;`
- L66 _public member_ `FString TakeJsonFilePath;`
- L68 _public prototype_ `FString GetName() const;`
- L69 _public prototype_ `FString GetFolderName() const;`

#### struct `FStereoCameraTakeInfo::FDeviceInfo`  
`struct FDeviceInfo`  
_L26-31_
- L28 _public member_ `FString Model;`
- L29 _public member_ `FString Type;`
- L30 _public member_ `FString Id;`

#### struct `FStereoCameraTakeInfo::FCamera`  
`struct FCamera`  
_L33-42_
- L35 _public member_ `FString UserId;`
- L36 _public member_ `TPair<uint32, uint32> FrameRange;`
- L37 _public member_ `float FrameRate = 0.0f;`
- L38 _public member_ `FString FramesPath;`
- L39 _public member_ `FString StartTimecode;`
- L40 _public member_ `FIntPoint Resolution = FIntPoint::NoneValue;`
- L41 _public member_ `TArray<FFrameRange> CaptureExcludedFrames;`

#### struct `FStereoCameraTakeInfo::FAudio`  
`struct FAudio`  
_L45-51_
- L47 _public member_ `FString UserId;`
- L48 _public member_ `FString StreamPath;`
- L49 _public member_ `float TimecodeRate = 0.0f;`
- L50 _public member_ `FString StartTimecode;`

#### class `FStereoCameraSystemTakeParser`  
`class FStereoCameraSystemTakeParser`  
_L72-85_
- L76 _public prototype_ `static TOptional<FStereoCameraTakeInfo> ParseTakeMetadataFile(const FString& InFileName);`
- L78 _public prototype_ `static TArray<FText> CheckStereoCameraTakeInfo( const FString& InFilePath, FStereoCameraTakeInfo& InStereoCameraTakeInfo, int32 InExpectedCameraCount, const FString& InDeviceType);`
- L84 _public prototype_ `static TArray<FText> ResolveResolution(FStereoCameraTakeInfo& OutStereoCameraTakeInfo);`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Private/Utils/AppleDeviceList.h` (Private)


#### class `UE::CaptureManager::FAppleDeviceList`  
`class FAppleDeviceList`  
_L11-17_
- L14 _public typedef_ `using FDeviceMap = TMap<FString, FString>;`
- L16 _public member_ `static const FDeviceMap DeviceMap;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/CaptureMetadataExtraction/Private/Utils/CaptureExtractTimecode.h` (Private)


#### struct `UE::CaptureManager::FTimecodeInfo`  
`struct FTimecodeInfo`  
_L24-28_
- L26 _public member_ `FTimecode Timecode;`
- L27 _public member_ `FFrameRate TimecodeRate;`

#### struct `UE::CaptureManager::FVideoInformation`  
`struct FVideoInformation`  
_L30-34_
- L32 _public member_ `FFrameRate FrameRate;`
- L33 _public member_ `FTimecodeInfo TimecodeInfo;`

#### enum `UE::CaptureManager::ECaptureExtractInfoError`  
`enum ECaptureExtractInfoError : int32`  
_L36-47_
- L38 _public enumerator_ `InternalError = -1`
- L39 _public enumerator_ `TimecodeNotFound = 1`
- L40 _public enumerator_ `UnableToParseTimecode = 2`
- L41 _public enumerator_ `UnableToParseTimecodeRate = 3`
- L42 _public enumerator_ `TimecodeRateNotFound = 4`
- L43 _public enumerator_ `UnhandledMedia = 5`
- L44 _public enumerator_ `UnableToOpenMedia = 6`
- L45 _public enumerator_ `FfprobeNotFound = 7`
- L46 _public enumerator_ `FailedToParseJson = 8`

#### class `UDesiredPlayerMediaSource`  
`class UDesiredPlayerMediaSource : public UFileMediaSource`  
_L52-61_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UFileMediaSource`
- L57 _public function_ `virtual FName GetDesiredPlayerName() const override`

#### class `UE::CaptureManager::Private::FFProbeCommand`  
`class FFProbeCommand`  
_L66-75_
- L69 _public prototype_ `FFProbeCommand(FString InFfmpegPath);`
- L71 _public prototype_ `FProcessRunnerResult Execute(const FString& InFilePath, int32 InTimeoutSeconds, const FStopToken* InStopToken = nullptr) const;`
- L74 _private member_ `const FString ProbePath;`

#### class `FCaptureExtractVideoInfo`  
`class FCaptureExtractVideoInfo final`  
_L78-111_
- L82 _public typedef_ `using FResult = TValueOrError<FCaptureExtractVideoInfo, UE::CaptureManager::ECaptureExtractInfoError>;`
- L84 _public prototype_ `static FResult Create(const FString& InFilePath, TOptional<UE::CaptureManager::Private::FFProbeCommand> InProbeCommand );`
- L86 _public prototype_ `FFrameRate GetFrameRate() const;`
- L87 _public prototype_ `FTimecode GetTimecode() const;`
- L88 _public prototype_ `FFrameRate GetTimecodeRate() const;`
- L89 _public prototype_ `bool ContainsAudio() const;`
- L90 _public prototype_ `float GetAudioDurationSeconds() const;`
- L91 _public prototype_ `EMediaOrientation GetVideoOrientation() const;`
- L95 _private prototype_ `FCaptureExtractVideoInfo();`
- L97 _private typedef_ `using FExtractResult = TValueOrError<void, UE::CaptureManager::ECaptureExtractInfoError>;`
- L98 _private prototype_ `FExtractResult ExtractInfo(const FString& InFilePath, TOptional<UE::CaptureManager::Private::FFProbeCommand> InProbeCommand);`
- L99 _private prototype_ `FExtractResult ExtractInfoUsingElectraPlayer(const FString& InFilePath);`
- L100 _private prototype_ `FExtractResult ExtractInfoUsingFFProbe(const FString& InFilePath, const UE::CaptureManager::Private::FFProbeCommand& InProbeCommand);`
- L102 _private prototype_ `TValueOrError<FFrameRate, UE::CaptureManager::ECaptureExtractInfoError> ParseTimecodeRate(FString TimecodeRateString);`
- L104 _private member_ `static constexpr int32 TimeoutPeriod = 3;`
- L106 _private member_ `FFrameRate FrameRate;`
- L107 _private member_ `UE::CaptureManager::FTimecodeInfo TimecodeInfo;`
- L108 _private member_ `bool bContainsAudio = false;`
- L109 _private member_ `float AudioDurationSeconds = 0.0f;`
- L110 _private member_ `EMediaOrientation VideoOrientation = EMediaOrientation::Original;`

#### class `FCaptureExtractAudioTimecode`  
`class FCaptureExtractAudioTimecode final : public TSharedFromThis<FCaptureExtractAudioTimecode>`  
_L113-132_
- inherits: `TSharedFromThis<FCaptureExtractAudioTimecode>`
- L117 _public typedef_ `using FTimecodeInfoResult = TValueOrError<UE::CaptureManager::FTimecodeInfo, UE::CaptureManager::ECaptureExtractInfoError>;`
- L119 _public prototype_ `FCaptureExtractAudioTimecode(const FString& InFilePath);`
- L120 _public prototype_ `~FCaptureExtractAudioTimecode() = default;`
- L122 _public prototype_ `FTimecodeInfoResult Extract();`
- L123 _public prototype_ `FTimecodeInfoResult Extract(FFrameRate InFrameRate);`
- L127 _private member_ `FString FilePath;`
- L129 _private member_ `const int32 TimeoutPeriod = 3;`
- L131 _private prototype_ `FTimecodeInfoResult ExtractTimecodeFromBroadcastWaveFormat(FFrameRate InTimecodeRate);`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CAPTUREMETADATAEXTRACTION_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace CaptureManager` (scope `UE`)
- L64 _namespace_ `namespace UE`
- L64 _namespace_ `namespace CaptureManager` (scope `UE`)
- L64 _namespace_ `namespace Private` (scope `UE::CaptureManager`)
