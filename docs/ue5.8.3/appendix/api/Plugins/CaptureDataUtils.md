# Plugins / CaptureDataUtils

- module root: `Plugins/VirtualProduction/CaptureData/Source/CaptureDataUtils`
- headers: 6; symbols: 37
- symbol kinds: class=3, macro=3, member=4, namespace=4, prototype=23
- PrivateDependencyModuleNames: EditorScriptingUtilities, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, ImgMedia

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataUtils/Internal/SmpteTimecodeUtils.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureData` (scope `UE`)
- L10 _prototype_ `UE_INTERNAL FFrameRate EstimateSmpteTimecodeRate(const FFrameRate InMediaFrameRate);` (scope `UE::CaptureData`)

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataUtils/Private/CaptureTimecodeInfo.h` (Private)


#### class `UCaptureTimecodeInfo`  
`class UCaptureTimecodeInfo : public UObject`  
_L12-22_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- L18 _public member_ `FTimecode Timecode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Info")`
- L21 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Info")`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataUtils/Public/ImageSequenceTimecodeUtils.h` (Public)


#### class `UImageSequenceTimecodeUtils`  
`class UImageSequenceTimecodeUtils : public UObject`  
_L13-44_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UObject`
- L20 _public member_ `static const FName TimecodeTagName;`
- L21 _public member_ `static const FName TimecodeRateTagName;`
- L24 _public prototype_ `static void SetTimecodeInfo(const FTimecode& InTimecode, const FFrameRate& InFrameRate, UImgMediaSource* InImageSequence);` — `UFUNCTION(BlueprintCallable, Category = "ImageSequence")`
- L27 _public prototype_ `static void SetTimecodeInfoString(const FString& InTimecode, const FString& InFrameRate, UImgMediaSource* InImageSequence);` — `UFUNCTION(BlueprintCallable, Category = "ImageSequence")`
- L30 _public prototype_ `static FTimecode GetTimecode(UImgMediaSource* InImageSequence);` — `UFUNCTION(BlueprintCallable, Category = "ImageSequence")`
- L33 _public prototype_ `static FFrameRate GetFrameRate(UImgMediaSource* InImageSequence);` — `UFUNCTION(BlueprintCallable, Category = "ImageSequence")`
- L36 _public prototype_ `static FString GetTimecodeString(UImgMediaSource* InImageSequence);` — `UFUNCTION(BlueprintCallable, Category = "ImageSequence")`
- L39 _public prototype_ `static FString GetFrameRateString(UImgMediaSource* InImageSequence);` — `UFUNCTION(BlueprintCallable, Category = "ImageSequence")`
- L41 _public prototype_ `static bool IsValidTimecodeInfo(const FTimecode& InTimecode, const FFrameRate& InTimecodeRate);`
- L42 _public prototype_ `static bool IsValidTimecode(const FTimecode& InTimecode);`
- L43 _public prototype_ `static bool IsValidFrameRate(const FFrameRate& InTimecodeRate);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CAPTUREDATAUTILS_API`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataUtils/Public/ParseTakeUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _prototype_ `FTimecode ParseTimecode(const FString& InTimecodeString);`
- L11 _prototype_ `FFrameRate ConvertFrameRate(double InFrameRate);`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataUtils/Public/SoundWaveTimecodeUtils.h` (Public)


#### class `USoundWaveTimecodeUtils`  
`class USoundWaveTimecodeUtils : public UObject`  
_L15-35_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UObject`
- L22 _public prototype_ `static void SetTimecodeInfo(const FTimecode& InTimecode, const FFrameRate& InFrameRate, USoundWave* OutSoundWave);` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L25 _public prototype_ `static FTimecode GetTimecode(const USoundWave* InSoundWave);` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L28 _public prototype_ `static FFrameRate GetFrameRate(const USoundWave* InSoundWave);` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L31 _public prototype_ `static bool HasTimecode(const USoundWave* InSoundWave);` — `UFUNCTION(BlueprintCallable, Category = "Audio")`
- L34 _public prototype_ `static bool HasTimecodeRate(const USoundWave* InSoundWave);` — `UFUNCTION(BlueprintCallable, Category = "Audio")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CAPTUREDATAUTILS_API`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataUtils/Public/TakeDirectoryUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREDATAUTILS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureData` (scope `UE`)
- L13 _prototype_ `FRegexPattern GetRegexPattern();` (scope `UE::CaptureData`)
- L14 _prototype_ `bool ExtractInfoFromFileName(const FRegexPattern& InPattern, const FString& InFileName, FString& OutPrefix, FString& OutDigits, FString& OutExtension);` (scope `UE::CaptureData`)
- L16 _prototype_ `FString GetFileFormat(const FRegexPattern& InPattern, const FString& InFileName);` (scope `UE::CaptureData`)
- L17 _prototype_ `FString GetFileNameFormat(const FString& InDirectory);` (scope `UE::CaptureData`)
- L19 _prototype_ `TArray<FString> GetImageSequenceFilesFromPath(const FString& InFullSequencePath, bool bInShouldSort = true);` (scope `UE::CaptureData`)
- L20 _prototype_ `bool GetImageDimensionsFromPath(const FString& InImagePath, FIntPoint& OutDimensions);` (scope `UE::CaptureData`)
