# Plugins / DataIngestCore

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/DataIngestCore`
- headers: 3; symbols: 42
- symbol kinds: class=1, macro=2, member=22, namespace=5, prototype=6, struct=4, typedef=2
- PrivateDependencyModuleNames: CaptureDataCore, CoreUObject, InputCore, Json, PropertyEditor
- PublicDependencyModuleNames: CaptureUtils, Core, Engine, Media

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/DataIngestCore/Public/IngestCaptureData.h` (Public)


#### struct `FIngestCaptureData`  
`struct FIngestCaptureData`  
_L11-61_
- desc: Capture archive data object for import into UE.
- L14 _public member_ `static const FString Extension;` — Expected extension for capture archive files.
- L49 _public member_ `uint32 Version = 1;` — Archive format version.
- L50 _public member_ `FString DeviceModel;`
- L51 _public member_ `FString Slate;`
- L52 _public member_ `uint32 TakeNumber;`
- L54 _public member_ `TArray<FVideo> Video;`
- L55 _public member_ `TArray<FVideo> Depth;`
- L56 _public member_ `TArray<FAudio> Audio;`
- L57 _public member_ `TArray<FCalibration> Calibration;`
- L60 _public prototype_ `void MakePathsAbsolute(const FString& InBasePath);` — Converts all relative paths to absolute using InBasePath.

#### struct `FIngestCaptureData::FVideo`  
`struct FVideo`  
_L17-29_
- desc: Video/image sequence information.
- L19 _public member_ `FString Name;`
- L20 _public member_ `FString Path;`
- L22 _public member_ `TOptional<float> FrameRate;`
- L23 _public member_ `TOptional<uint32> FrameWidth;`
- L24 _public member_ `TOptional<uint32> FrameHeight;`
- L26 _public member_ `TArray<uint32> DroppedFrames;`
- L28 _public member_ `TOptional<FString> TimecodeStart;`

#### struct `FIngestCaptureData::FAudio`  
`struct FAudio`  
_L32-39_
- desc: Audio info.
- L34 _public member_ `FString Name;`
- L35 _public member_ `FString Path;`
- L37 _public member_ `TOptional<FString> TimecodeStart;`
- L38 _public member_ `TOptional<float> TimecodeRate;`

#### struct `FIngestCaptureData::FCalibration`  
`struct FCalibration`  
_L42-46_
- desc: Calibration info.
- L44 _public member_ `FString Name;`
- L45 _public member_ `FString Path;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAINGESTCORE_API`
- L63 _namespace_ `namespace UE`
- L63 _namespace_ `namespace CaptureManager` (scope `UE`)
- L63 _namespace_ `namespace IngestCaptureData` (scope `UE::CaptureManager`)
- L67 _typedef_ `using FParseResult = TValueOrError<FIngestCaptureData, FText>;` (scope `UE::CaptureManager::IngestCaptureData`) — Parse input file into capture archive data object.
- L68 _prototype_ `FParseResult ParseFile(const FString& InFilePath);` (scope `UE::CaptureManager::IngestCaptureData`)
- L71 _prototype_ `TOptional<FText> Serialize(const FString& InFilePath, const FString& InFileName, const FIngestCaptureData& InIngestCaptureData);` (scope `UE::CaptureManager::IngestCaptureData`) — Serialise capture archive data object to file.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/DataIngestCore/Public/Utils/ParseTakeUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)
- L14 _prototype_ `FTimecode ParseTimecode(const FString& InTimecodeString);` (scope `UE::CaptureManager`) — Parse timecode from string.
- L17 _prototype_ `FFrameRate ParseFrameRate(double InFrameRate);` (scope `UE::CaptureManager`) — Parse frame rate from double.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerCore/Source/DataIngestCore/Public/Utils/UnrealCalibrationParser.h` (Public)


#### class `FUnrealCalibrationParser`  
`class FUnrealCalibrationParser`  
_L9-16_
- L12 _public typedef_ `using FParseResult = TValueOrError<TArray<FCameraCalibration>, FText>;`
- L15 _public prototype_ `static FParseResult Parse(const FString& InFile);` — Parse input file into unreal calibration format.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATAINGESTCORE_API`
