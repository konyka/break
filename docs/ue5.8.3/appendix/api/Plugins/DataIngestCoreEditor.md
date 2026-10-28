# Plugins / DataIngestCoreEditor

- module root: `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/DataIngestCoreEditor`
- headers: 3; symbols: 111
- symbol kinds: class=3, enum=1, enumerator=4, function=3, macro=3, member=44, namespace=4, prototype=36, struct=9, typedef=4
- PrivateDependencyModuleNames: AssetDefinition, CameraCalibrationCore, CaptureDataCore, CaptureDataEditor, CaptureManagerEditorSettings, CoreUObject, DataIngestCore, ImgMedia, InputCore, Json, JsonUtilities, Media, MeshDescription, NamingTokens, PropertyEditor, Slate, SlateCore, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: CaptureDataCore, CaptureUtils, Core, Engine

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/DataIngestCoreEditor/Internal/CaptureManagerIngestPreparation.h` (Internal)


#### struct `UE::CaptureManager::FCaptureDataTakeInfo`  
`struct FCaptureDataTakeInfo`  
_L19-24_
- L21 _public member_ `FString Name;`
- L22 _public member_ `double FrameRate = 0.0;`
- L23 _public member_ `FString DeviceModel;`

#### class `UE::CaptureManager::FAssetNamingStrategy`  
`class FAssetNamingStrategy`  
_L26-55_
- L29 _public prototype_ `FAssetNamingStrategy(const FIngestCaptureData& InIngestCaptureData);`
- L30 _public prototype_ `FAssetNamingStrategy(const FIngestCaptureData& InIngestCaptureData, FString InImportID, FString InDeviceName);`
- L32 _public prototype_ `FString GetImportFolder() const;`
- L33 _public prototype_ `FString GetCaptureDataAssetName() const;`
- L34 _public prototype_ `FString GetImageSequenceAssetName(const FIngestCaptureData::FVideo& InVideo, const FFrameRate& InFrameRate) const;`
- L35 _public prototype_ `FString GetDepthSequenceAssetName(const FIngestCaptureData::FVideo& InVideo, const FFrameRate& InFrameRate) const;`
- L36 _public prototype_ `FString GetAudioAssetName(const FIngestCaptureData::FAudio& InAudio) const;`
- L37 _public prototype_ `FString GetCalibrationAssetName(const FIngestCaptureData::FCalibration& InCalibration) const;`
- L38 _public prototype_ `FString GetLensFileAssetName(const FIngestCaptureData::FCalibration& InCalibration, const FCameraCalibration& InCameraCalibration) const;`
- L41 _private typedef_ `using FSanitizeFunc = void(*)(FString&, FString::ElementType);`
- L43 _private prototype_ `FString ResolveTemplate( const FString& InTemplate, const FNamingTokenFilterArgs& InTokenArgs, TConstArrayView<const FStringFormatNamedArguments*> InFormatArgSets, FSanitizeFunc InSanitize) const;`
- L49 _private prototype_ `static FStringFormatNamedArguments BuildVideoNamedArgs( const UCaptureManagerEditorSettings* InSettings, const FIngestCaptureData::FVideo& InVideo, const FFrameRate& InFrameRate);`
- L54 _private member_ `FStringFormatNamedArguments ImportNamedArgs;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAINGESTCOREEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace CaptureManager` (scope `UE`)
- L57 _prototype_ `FCreateAssetsData BuildAssetData(const FIngestCaptureData& InIngestCaptureData, const FAssetNamingStrategy& InNamingStrategy);` (scope `UE::CaptureManager`)
- L60 _prototype_ `FCaptureDataTakeInfo BuildTakeInfo(const FCreateAssetsData& InAssetsData, const FIngestCaptureData& InIngestCaptureData);` (scope `UE::CaptureManager`) — Populates a FCaptureDataTakeInfo from the asset name, device model, and first video entry of the ingest data.
- L63 _prototype_ `UFootageCaptureData* CreateFootageCaptureDataAsset_GameThread(const FString& InAssetPath, const FCaptureDataAssetInfo& InResult, const FCaptureDataTakeInfo& InTakeInfo, bool bShouldSave = true);` (scope `UE::CaptureManager`) — Creates a UFootageCaptureData asset from prepared asset info and take metadata. Returns nullptr if the asset already exists.

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/DataIngestCoreEditor/Public/DataIngestCoreError.h` (Public)


#### enum `EAssetCreationError`  
`enum class EAssetCreationError`  
_L12-18_
- desc: Asset creation error types.
- L14 _public enumerator_ `InternalError = 1`
- L15 _public enumerator_ `InvalidArgument`
- L16 _public enumerator_ `NotFound`
- L17 _public enumerator_ `Warning`

#### class `FAssetCreationError`  
`class FAssetCreationError`  
_L21-40_
- desc: Information related to an error during ingest asset creation.
- L25 _public prototype_ `FAssetCreationError(FText InMessage, EAssetCreationError InError = EAssetCreationError::InternalError);`
- L28 _public prototype_ `const FText& GetMessage() const;` — Get the error message.
- L31 _public prototype_ `EAssetCreationError GetError() const;` — Get the error type.
- L36 _private member_ `FText Message;` — Error message.
- L39 _private member_ `EAssetCreationError Error;` — Error type.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAINGESTCOREEDITOR_API`

### `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/DataIngestCoreEditor/Public/IngestAssetCreator.h` (Public)


#### struct `UE::CaptureManager::FCreateAssetsData`  
`struct FCreateAssetsData`  
_L23-78_
- desc: Data used to create assets.
- L66 _public member_ `FString CaptureDataAssetName;`
- L69 _public member_ `int32 TakeId = 0;` — Unique identifier for this take.
- L70 _public member_ `FString PackagePath;`
- L71 _public member_ `TArray<FImageSequenceData> ImageSequences;`
- L72 _public member_ `TArray<FImageSequenceData> DepthSequences;`
- L73 _public member_ `TArray<FAudioData> AudioClips;`
- L74 _public member_ `TArray<FCalibrationData> Calibrations;`
- L77 _public member_ `TArray<FFrameRange> CaptureExcludedFrames;` — Frame range(s) to exclude from processing.

#### struct `UE::CaptureManager::FCreateAssetsData::FImageSequenceData`  
`struct FImageSequenceData`  
_L26-39_
- desc: Image sequence information.
- L28 _public member_ `FString AssetName;`
- L30 _public member_ `FString Name;`
- L31 _public member_ `FString SequenceDirectory;`
- L32 _public member_ `FFrameRate FrameRate = FFrameRate(30, 1);`
- L35 _public member_ `bool bTimecodePresent = false;` — Whether timecode is available.
- L37 _public member_ `FTimecode Timecode = FTimecode(0, 0, 0, 0, false);`
- L38 _public member_ `FFrameRate TimecodeRate = FFrameRate(30, 1);`

#### struct `UE::CaptureManager::FCreateAssetsData::FAudioData`  
`struct FAudioData`  
_L42-54_
- desc: Audio information.
- L44 _public member_ `FString AssetName;`
- L46 _public member_ `FString Name;`
- L47 _public member_ `FString WAVFile;`
- L50 _public member_ `bool bTimecodePresent = false;` — Whether timecode is available.
- L52 _public member_ `FTimecode Timecode = FTimecode(0, 0, 0, 0, false);`
- L53 _public member_ `FFrameRate TimecodeRate = FFrameRate(30, 1);`

#### struct `UE::CaptureManager::FCreateAssetsData::FCalibrationData`  
`struct FCalibrationData`  
_L57-64_
- desc: Calibration information.
- L59 _public member_ `FString AssetName;`
- L61 _public member_ `FString Name = TEXT("Cal`
- L62 _public member_ `TArray<FCameraCalibration> CameraCalibrations;`
- L63 _public member_ `TMap<FString, FString> LensFileAssetNames;`

#### struct `UE::CaptureManager::FCaptureDataAssetInfo`  
`struct FCaptureDataAssetInfo`  
_L81-115_
- desc: Capture data asset information.
- L106 _public member_ `int32 TakeId;` — Unique identifier for this take.
- L108 _public member_ `TArray<FImageSequence> ImageSequences;`
- L109 _public member_ `TArray<FImageSequence> DepthSequences;`
- L110 _public member_ `TArray<FCalibration> Calibrations;`
- L111 _public member_ `TArray<FAudio> Audios;`
- L114 _public member_ `TArray<FFrameRange> CaptureExcludedFrames;` — Frame range(s) to exclude from processing.

#### struct `UE::CaptureManager::FCaptureDataAssetInfo::FImageSequence`  
`struct FImageSequence`  
_L84-89_
- desc: Image sequence information.
- L86 _public member_ `TObjectPtr<UImgMediaSource> Asset;`
- L87 _public member_ `FTimecode Timecode;`
- L88 _public member_ `FFrameRate TimecodeRate;`

#### struct `UE::CaptureManager::FCaptureDataAssetInfo::FCalibration`  
`struct FCalibration`  
_L92-95_
- desc: Calibration information.
- L94 _public member_ `TObjectPtr<UCameraCalibration> Asset;`

#### struct `UE::CaptureManager::FCaptureDataAssetInfo::FAudio`  
`struct FAudio`  
_L98-103_
- desc: Audio information.
- L100 _public member_ `TObjectPtr<USoundWave> Asset;`
- L101 _public member_ `FTimecode Timecode;`
- L102 _public member_ `FFrameRate TimecodeRate;`

#### class `UE::CaptureManager::FIngestAssetCreator`  
`class FIngestAssetCreator`  
_L118-205_
- desc: Facilitates creation, retrieval and removal of capture data assets.
- L121 _public typedef_ `using FAssetCreationResult = TValueOrError<void, FAssetCreationError>;`
- L122 _public typedef_ `using FPerTakeResult = TPair<int32, FAssetCreationResult>;`
- L123 _public typedef_ `using FPerTakeCallback = TManagedDelegate<FPerTakeResult>;`
- L126 _public prototype_ `static TArray<FCaptureDataAssetInfo> CreateAssets_GameThread(const TArray<FCreateAssetsData>& InOutCreateAssetDataList, FPerTakeCallback InPerTakeCallback);` — Creates assets from asset data.
- L130 _public prototype_ `static UObject* GetAssetIfExists(const FString& InTargetPackagePath, const FString& InAssetName);` — Gets an asset if it exists.
- L133 _public function_ `template<class TReturnType> static TReturnType* GetAssetIfExists(const FString& InTargetPackagePath, const FString& InAssetName)`
- L140 _public function_ `template<class TReturnType> static TReturnType* GetOrCreateAsset(const FString& InTargetPackagePath, const FString& InAssetName)` — Gets an existing asset or create a new asset at the specified package path.
- L147 _public function_ `template<class TReturnType> static TReturnType* CreateAsset(const FString& InTargetPackagePath, const FString& InAssetName)` — Creates a new asset at the specified package path.
- L153 _private prototype_ `static void CreateTakeAssets_GameThread(const TArray<FCreateAssetsData>& InOutCreateAssetsData, const FPerTakeCallback& InPerTakeCallback, TArray<FCaptureDataAssetInfo>& OutTakes);`
- L157 _private prototype_ `static void VerifyIngestedData_GameThread(const TArray<FCreateAssetsData>& InCreateAssetsData, const TArray<FCaptureDataAssetInfo>& InCreatedTakes, const FPerTakeCallback& InPerTakeCallback);`
- L161 _private prototype_ `static TValueOrError<void, FText> CreateTakeAssetViews_GameThread(const FCreateAssetsData& InCreateAssetDate, FCaptureDataAssetInfo& OutTake);`
- L165 _private prototype_ `static FAssetCreationResult AssignAudioAsset(const FCreateAssetsData::FAudioData& AudioClip, const TObjectPtr<UAssetImportTask>& InAssetImportTask, FCaptureDataAssetInfo& OutTake);` — Adds audio asset to capture data asset info.
- L171 _private prototype_ `static bool RemoveAssetsByPath(const FString& InPackagePath);` — Deletes all assets at the specified package path. Returns true if all assets were deleted (or none existed), false if any deletion failed.
- L174 _private prototype_ `static FString CreateTimecodeString(FTimecode InTimecode, FFrameRate InFrameRate);` — Converts timecode to string.
- L177 _private prototype_ `static FString CreateAssetPathString(const UAssetImportTask* InAssetImportTask);` — Creates asset path from import task.
- L180 _private prototype_ `static void StampWithTakeMetadataTimecode(const FCreateAssetsData::FAudioData& InAudioClip, const UAssetImportTask* InAssetImportTask, USoundWave* OutSoundWave);` — Adds timecode to soundwave asset.
- L183 _private prototype_ `static bool IsValidAudioTimecodeRate(FFrameRate InTimecodeRate, uint32 InNumSamplesPerSecond);` — Checks whether timecode rate is valid.
- L186 _private prototype_ `static void PrepareSoundWave(const FCreateAssetsData::FAudioData& InAudioClip, const UAssetImportTask* InAssetImportTask, USoundWave* OutSoundWave);` — Creates sound wave asset.
- L189 _private prototype_ `static FAssetCreationResult CheckCreatedTakeAssets_GameThread(const FCreateAssetsData& InCreateAssetsData);`
- L190 _private prototype_ `static FAssetCreationResult CheckCreatedTakeStruct_GameThread(const FCaptureDataAssetInfo& InCreatedTakeStruct);`
- L193 _private prototype_ `static void RemoveTakes(TArray<int32> InTakesToRemove, TArray<FCaptureDataAssetInfo>& OutTakeList);` — Deletes specified takes from take list.
- L197 _private prototype_ `static FAssetCreationResult CheckTakeAssets(const FCaptureDataAssetInfo& InTake);` — Checks validity of assets in the take.
- L199 _private prototype_ `static UObject* GetOrCreateAsset(const FString& InTargetPackagePath, const FString& InAssetName, UClass* InClass);`
- L200 _private prototype_ `static UObject* CreateAsset(const FString& InTargetPackagePath, const FString& InAssetName, UClass* InClass);`
- L202 _private prototype_ `static TValueOrError<TObjectPtr<class UImgMediaSource>, FText> CreateImageSequenceAsset(const FString& InPackagePath, const FCreateAssetsData::FImageSequenceData& InImageSequenceData);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API DATAINGESTCOREEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace CaptureManager` (scope `UE`)
