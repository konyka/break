# Plugins / MetaHumanCaptureData

- module root: `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCaptureData`
- headers: 7; symbols: 57
- symbol kinds: class=5, macro=5, member=10, namespace=10, prototype=26, struct=1
- PrivateDependencyModuleNames: CaptureDataCore, DirectoryWatcher, ImgMedia, MetaHumanImageViewer
- PublicDependencyModuleNames: Core

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCaptureData/Public/FrameNumberTransformer.h` (Public)


#### class `UE::MetaHuman::FFrameNumberTransformer`  
`class FFrameNumberTransformer`  
_L12-36_
- L16 _public prototype_ `FFrameNumberTransformer();` — Pass-through transform (no change)
- L19 _public prototype_ `explicit FFrameNumberTransformer(int32 InFrameNumberOffset);` — Apply a simple offset
- L22 _public prototype_ `FFrameNumberTransformer(FFrameRate InSourceFrameRate, FFrameRate InTargetFrameRate);` — Adjust for differences in frame rate
- L25 _public prototype_ `FFrameNumberTransformer(FFrameRate InSourceFrameRate, FFrameRate InTargetFrameRate, int32 InFrameNumberOffset);` — Adjust for differences in frame rate and apply an offset
- L28 _public prototype_ `int32 Transform(int32 InFrameNumber) const;` — Transforms the input frame number
- L31 _private member_ `FFrameRate SourceFrameRate;`
- L32 _private member_ `FFrameRate TargetFrameRate;`
- L33 _private member_ `int32 SkipFactor = 0;`
- L34 _private member_ `int32 DuplicationFactor = 0;`
- L35 _private member_ `int32 FrameNumberOffset = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTUREDATA_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCaptureData/Public/FramePathResolver.h` (Public)


#### class `UE::MetaHuman::FFramePathResolver`  
`class FFramePathResolver : public IFramePathResolver`  
_L13-25_
- inherits: `IFramePathResolver`
- L16 _public prototype_ `FFramePathResolver(FString InFilePathTemplate);`
- L17 _public prototype_ `FFramePathResolver(FString InFilePathTemplate, FFrameNumberTransformer InFrameNumberTransformer);`
- L20 _public prototype_ `virtual FString ResolvePath(int32 InFrameNumber) const override;`
- L23 _private member_ `FString FilePathTemplate;`
- L24 _private member_ `FFrameNumberTransformer FrameNumberTransformer;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANCAPTUREDATA_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCaptureData/Public/FramePathResolverSingleFile.h` (Public)


#### class `UE::MetaHuman::FFramePathResolverSingleFile`  
`class FFramePathResolverSingleFile : public IFramePathResolver`  
_L13-23_
- inherits: `IFramePathResolver`
- desc: Always resolves to the same file path
- L16 _public prototype_ `explicit FFramePathResolverSingleFile(FString InFilePath);`
- L19 _public prototype_ `virtual FString ResolvePath(int32 InFrameNumber) const override;`
- L22 _private member_ `FString FilePath;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTUREDATA_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCaptureData/Public/IFramePathResolver.h` (Public)


#### struct `UE::MetaHuman::IFramePathResolver`  
`struct IFramePathResolver`  
_L10-14_
- L12 _public prototype_ `virtual ~IFramePathResolver() = default;`
- L13 _public prototype_ `virtual FString ResolvePath(int32 InFrameNumber) const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCaptureData/Public/MetaHumanCaptureDataLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCaptureData, Log, All);`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCaptureData/Public/SequencedImageTrackInfo.h` (Public)


#### class `UE::MetaHuman::FSequencedImageTrackInfo`  
`class FSequencedImageTrackInfo`  
_L15-27_
- desc: Brings together some sequencer and image sequence information for a specific track (A Sequenced "Image Track")
- L18 _public prototype_ `FSequencedImageTrackInfo(FFrameRate InSourceFrameRate, TRange<FFrameNumber> InSequenceFrameRange);`
- L19 _public prototype_ `~FSequencedImageTrackInfo();`
- L21 _public prototype_ `FFrameRate GetSourceFrameRate() const;`
- L22 _public prototype_ `TRange<FFrameNumber> GetSequenceFrameRange() const;`
- L25 _private member_ `FFrameRate SourceFrameRate;`
- L26 _private member_ `TRange<FFrameNumber> SequenceFrameRange;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTUREDATA_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L29 _prototype_ `bool FrameRatesAreCompatible(FFrameRate InFirstFrameRate, FFrameRate InSecondFrameRate);` (scope `UE::MetaHuman`)
- L30 _prototype_ `bool TracksHaveCompatibleFrameRates(const TArray<FSequencedImageTrackInfo>& InSequencedImageTrackInfos);` (scope `UE::MetaHuman`)
- L31 _prototype_ `bool TracksHaveDifferentFrameRates(const TArray<FSequencedImageTrackInfo>& InSequencedImageTrackInfos);` (scope `UE::MetaHuman`)
- L32 _prototype_ `int32 FindFirstCommonFrameNumber(TArray<UE::MetaHuman::FSequencedImageTrackInfo> InSequencedImageTrackInfos);` (scope `UE::MetaHuman`)
- L34 _prototype_ `TArray<FFrameNumber> CalculateRateMatchingDropFrames( FFrameRate InTargetFrameRate, TArray<UE::MetaHuman::FSequencedImageTrackInfo> InSequencedImageTrackInfos );` (scope `UE::MetaHuman`)
- L39 _prototype_ `TArray<FFrameNumber> CalculateRateMatchingDropFrames( FFrameRate InTargetFrameRate, TArray<UE::MetaHuman::FSequencedImageTrackInfo> InSequencedImageTrackInfos, const TRange<FFrameNumber>& InRangeLimit );` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCaptureData/Public/TrackingPathUtils.h` (Public)


#### class `FTrackingPathUtils`  
`class FTrackingPathUtils`  
_L9-16_
- L12 _public prototype_ `static bool GetTrackingFilePathAndInfo(const class UImgMediaSource* InImgSequence, FString& OutTrackingFilePath, int32& OutFrameOffset, int32& OutNumFrames);`
- L13 _public prototype_ `static bool GetTrackingFilePathAndInfo(const FString& InFullSequencePath, FString& OutTrackingFilePath, int32& OutFrameOffset, int32& OutNumFrames);`
- L15 _public prototype_ `static FString ExpandFilePathFormat(const FString& InFilePathFormat, int32 InFrameNumber);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCAPTUREDATA_API`
