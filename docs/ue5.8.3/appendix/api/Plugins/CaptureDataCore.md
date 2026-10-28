# Plugins / CaptureDataCore

- module root: `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore`
- headers: 9; symbols: 203
- symbol kinds: class=9, delegate=2, enum=7, enumerator=32, function=3, macro=6, member=66, namespace=4, prototype=64, struct=8, typedef=2
- PrivateDependencyModuleNames: CameraCalibrationCore, CaptureDataUtils, Core, CoreUObject, Engine, ImgMedia, MeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: Media

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Private/CaptureDataCoreModule.h` (Private)


#### class `FCaptureDataCoreModule`  
`class FCaptureDataCoreModule : public IModuleInterface`  
_L7-18_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void CheckAssetMigration();`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Public/CameraCalibration.h` (Public)


#### struct `FExtendedLensFile`  
`struct FExtendedLensFile`  
_L16-30_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = Calibration)`
- L26 _public member_ `bool IsDepthCamera{};` — `UPROPERTY(EditAnywhere, Category = Calibration)`
- L29 _public member_ `TObjectPtr<class ULensFile> LensFile{};` — `UPROPERTY(EditAnywhere, Category = Calibration)`

#### struct `FStereoPair`  
`struct FStereoPair`  
_L33-44_
- reflection: `USTRUCT(BlueprintType)`
- L40 _public member_ `uint32 CameraIndex1 {};` — `UPROPERTY(EditAnywhere, Category = Calibration)`
- L43 _public member_ `uint32 CameraIndex2 {};` — `UPROPERTY(EditAnywhere, Category = Calibration)`

#### struct `FCameraCalibration`  
`struct FCameraCalibration`  
_L46-77_
- L58 _public member_ `FString CameraId;`
- L59 _public member_ `EType CameraType;`
- L61 _public member_ `FVector2D ImageSize = FVector2D::Zero();`
- L62 _public member_ `FVector2D FocalLength = FVector2D::Zero();`
- L63 _public member_ `FVector2D PrincipalPoint = FVector2D::Zero();`
- L64 _public member_ `FVector2D FocalLengthNormalized = FVector2D::Zero();`
- L65 _public member_ `FVector2D PrincipalPointNormalized = FVector2D::Zero();`
- L67 _public member_ `double K1 = 0;`
- L68 _public member_ `double K2 = 0;`
- L69 _public member_ `double P1 = 0;`
- L70 _public member_ `double P2 = 0;`
- L71 _public member_ `double K3 = 0;`
- L72 _public member_ `double K4 = 0;`
- L73 _public member_ `double K5 = 0;`
- L74 _public member_ `double K6 = 0;`
- L75 _public member_ `FMatrix Transform;`
- L76 _public member_ `EMediaOrientation Orientation = EMediaOrientation::Original;`

#### enum `FCameraCalibration::EType`  
`enum EType`  
_L50-56_
- L52 _public enumerator_ `Video = 0`
- L53 _public enumerator_ `Depth`
- L55 _public enumerator_ `Unknown`

#### class `UCameraCalibration`  
`class UCameraCalibration : public UObject`  
_L86-124_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Camera Calibration Asset Contains the parameters for calibrating the camera used in footage for MetaHuman Identity and Performance assets.
- L92 _public prototype_ `virtual void PostInitProperties() override;`
- L93 _public prototype_ `virtual void PostLoad() override;`
- L94 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;`
- L98 _public member_ `TArray<FExtendedLensFile> CameraCalibrations;` — `UPROPERTY(EditAnywhere, Category = Calibration)`
- L101 _public member_ `TArray<FStereoPair> StereoPairs;` — `UPROPERTY(EditAnywhere, Category = Calibration)`
- L106 _public member_ `TObjectPtr<UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = "Import Settings")` — Importing data and options used for importing mhaical files
- L109 _public prototype_ `bool ConvertToTrackerNodeCameraModels(TArray<FCameraCalibration>& OutCalibrations, TArray<TPair<FString, FString>>& OutStereoReconstructionPairs) const;`
- L112 _public prototype_ `bool ConvertFromTrackerNodeCameraModels(const TArray<FCameraCalibration>& InCalibrations, bool bInUsingUnrealCoordinateSystem = false);`
- L113 _public prototype_ `bool ConvertFromTrackerNodeCameraModels(const TArray<FCameraCalibration>& InCalibrations, const TMap<FString, FString>& InLensAssetNamesMap, bool bInUsingUnrealCoordinateSystem = false);`
- L115 _public prototype_ `int32 GetCalibrationIndexByName(const FString& InName) const;`
- L119 _private prototype_ `void CreateLensFileForCalibration(const FCameraCalibration& InCalibration, const FString& InAssetName, bool bInUsingUnrealCoordinateSystem);`
- L120 _private prototype_ `void AddStereoPair();`
- L121 _private prototype_ `FString BuildAvailableCalibrationsString() const;`
- L123 _private member_ `EMediaOrientation CameraOrientation;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CAPTUREDATACORE_API`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Public/CaptureData.h` (Public)


#### enum `ECaptureDataInitializedCheck`  
`enum class ECaptureDataInitializedCheck : uint8`  
_L23-32_
- L25 _public enumerator_ `ImageSequences = 1 << 0`
- L26 _public enumerator_ `DepthSequences = 1 << 1`
- L27 _public enumerator_ `Calibrations = 1 << 2`
- L28 _public enumerator_ `Metadata = 1 << 3`
- L30 _public enumerator_ `Full = ImageSequences | DepthSequences | Calibrations | Metadata`
- L31 _public enumerator_ `ImageSequencesOnly = ImageSequences`

#### class `UCaptureData`  
`class UCaptureData : public UObject`  
_L40-75_
- reflection: `UCLASS(Abstract, MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L53 _public prototype_ `virtual bool IsInitialized(ECaptureDataInitializedCheck InInitializedCheck) const PURE_VIRTUAL(UCaptureData::IsInitialized, return false;);` — Returns true is the capture data is fully initialized with all required information present
- L55 _public function_ `FOnCaptureDataInternalsChanged& OnCaptureDataInternalsChanged()`
- L63 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L64 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L71 _protected prototype_ `void NotifyInternalsChanged();` — Notify that something internal to the capture data changed
- L74 _private member_ `FOnCaptureDataInternalsChanged OnCaptureDataInternalsChangedDelegate;`

#### enum `UCaptureData::EInitializedCheck`  
`enum UE_DEPRECATED(5.8, "EInitializedCheck has been moved to global scope. Please use the ECaptureDataInitializedCheck::.") EInitializedCheck`  
_L46-50_
- L48 _public enumerator_ `Full = 0`
- L49 _public enumerator_ `ImageSequencesOnly`

#### class `UMeshCaptureData`  
`class UMeshCaptureData : public UCaptureData`  
_L90-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCaptureData`
- desc: Capture Data (Mesh) Asset An asset that contains the Mesh data representing a facial expression (Pose), that can be used in MetaHuman Identity to generate a Skeletal Mesh or a full MetaHuman resembling a real person or a sculpted character. If pose data represents a real person, the resulting Skeletal Mesh can be used to generate animation from footage of that person in MetaHuman Performance asset
- L96 _public prototype_ `virtual bool IsInitialized(ECaptureDataInitializedCheck InInitializedCheck) const override;` — UCaptureData interface
- L100 _public prototype_ `void GetDataForConforming(const FTransform& InTransform, TArray<float>& OutVertices, TArray<int32>& OutTriangles) const;` — Gets the data in the format expected by the face fitting API
- L104 _public member_ `TObjectPtr<class UObject> TargetMesh;` — `UPROPERTY(EditAnywhere, Category = "Capture", Meta = (AllowedClasses = "/Script/Engine.StaticMesh, /Script/Engine.SkeletalMesh"))` — The target mesh for conforming. This can be either a Static or SkeletalMesh

#### enum `EFootageDeviceClass`  
`enum class EFootageDeviceClass : uint8`  
_L111-120_
- reflection: `UENUM()`
- L113 _public enumerator_ `Unspecified`
- L114 _public enumerator_ `iPhone11OrEarlier UMETA(DisplayName = "iPhone 11 or earlier")`
- L115 _public enumerator_ `iPhone12 UMETA(DisplayName = "iPhone 12")`
- L116 _public enumerator_ `iPhone13 UMETA(DisplayName = "iPhone 13")`
- L117 _public enumerator_ `iPhone14OrLater UMETA(DisplayName = "iPhone 14 or later")`
- L118 _public enumerator_ `OtheriOSDevice UMETA(DisplayName = "Other iOS device")`
- L119 _public enumerator_ `StereoHMC UMETA(DisplayName = "Stereo HMC")`

#### struct `FFootageCaptureMetadata`  
`struct FFootageCaptureMetadata`  
_L123-160_
- reflection: `USTRUCT(BlueprintType)`
- L128 _public member_ `int32 Width_DEPRECATED = 0;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Redundant property"))`
- L131 _public member_ `int32 Height_DEPRECATED = 0;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Redundant property"))`
- L134 _public member_ `double FrameRate = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata")`
- L137 _public member_ `EFootageDeviceClass DeviceClass = EFootageDeviceClass::Unspecified;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metadata")`
- L140 _public member_ `EFootageDeviceClass DeviceModel_DEPRECATED = EFootageDeviceClass::Unspecified;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property has been renamed to Device Class"))`
- L143 _public member_ `FString DeviceModelName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Device Model", Category = "Metadata")`
- L146 _public prototype_ `void SetDeviceClass(const FString& InDeviceModel);` — Sets the DeviceClass property parsing the model string accordingly
- L158 _private prototype_ `TOptional<FIosDeviceVersion> ParseIosDeviceVersion(const FString& Prefix, const FString& ModelName);`
- L159 _private prototype_ `EFootageDeviceClass IPhoneDeviceClass(TOptional<FIosDeviceVersion> IosDeviceVersion);`

#### struct `FFootageCaptureMetadata::FIosDeviceVersion`  
`struct FIosDeviceVersion`  
_L149-157_
- L151 _public member_ `uint16 Major;`
- L152 _public member_ `uint16 Minor;`
- L154 _public function_ `FIosDeviceVersion(uint16 Major, uint16 Minor) : Major(Major), Minor(Minor)`

#### struct `FFootageCaptureView`  
`struct FFootageCaptureView`  
_L163-190_
- reflection: `USTRUCT(BlueprintType)`
- L168 _public member_ `TObjectPtr<class UImgMediaSource> ImageSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")`
- L171 _public member_ `bool bImageTimecodePresent = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")`
- L174 _public member_ `FTimecode ImageTimecode = FTimecode(0, 0, 0, 0, false);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")`
- L177 _public member_ `FFrameRate ImageTimecodeRate = FFrameRate(30, 1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")`
- L180 _public member_ `TObjectPtr<class UImgMediaSource> DepthSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")`
- L183 _public member_ `bool bDepthTimecodePresent = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")`
- L186 _public member_ `FTimecode DepthTimecode = FTimecode(0, 0, 0, 0, false);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")`
- L189 _public member_ `FFrameRate DepthTimecodeRate = FFrameRate(30, 1);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")`

#### enum `ETimecodeAlignment`  
`enum class ETimecodeAlignment : int32`  
_L193-198_
- reflection: `UENUM()`
- L195 _public enumerator_ `None UMETA(DisplayName = "None")`
- L196 _public enumerator_ `Absolute UMETA(DisplayName = "Absolute")`
- L197 _public enumerator_ `Relative UMETA(DisplayName = "Relative")`

#### class `UFootageCaptureData`  
`class UFootageCaptureData : public UCaptureData`  
_L214-318_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCaptureData`
- desc: Capture Data (Footage) Asset An asset that contains the footage data showing facial expressions (Poses) that can be used by MetaHuman Identity Asset toolkit to generate a Skeletal Mesh or a MetaHuman resembling a real person or a sculpted character. The resulting Skeletal Mesh resembling the actor from the footage can be used for generating animation from footage of that person in MetaHuman Performance asset
- L220 _public typedef_ `using FVerifyResult = TValueOrError<void, FString>;`
- L223 _public prototype_ `virtual bool IsInitialized(ECaptureDataInitializedCheck InInitializedCheck) const override;`
- L227 _public prototype_ `virtual void PostLoad() override;`
- L233 _public member_ `TArray<FFootageCaptureView> Views_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Views are deprecated. Please use Image and Depth sequences instead."))`
- L236 _public member_ `TArray<TObjectPtr<class UImgMediaSource>> ImageSequences;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")`
- L239 _public member_ `TArray<TObjectPtr<class UImgMediaSource>> DepthSequences;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")`
- L242 _public member_ `TArray<TObjectPtr<class USoundWave>> AudioTracks;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")`
- L245 _public member_ `TArray<TObjectPtr<class USoundWave>> Audios_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Audios is deprecated. Please use AudioTracks instead."))`
- L248 _public member_ `TObjectPtr<class USoundWave> Audio_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Audio is deprecated. Please use AudioTracks instead."))`
- L251 _public member_ `bool bAudioTimecodePresent_DEPRECATED = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "AudioTimecodePresent is deprecated."))`
- L254 _public member_ `FTimecode AudioTimecode_DEPRECATED = FTimecode(0, 0, 0, 0, false);` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "AudioTimecode is deprecated."))`
- L257 _public member_ `FFrameRate AudioTimecodeRate_DEPRECATED = FFrameRate(30, 1);` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "AudioTimecodeRate is deprecated."))`
- L260 _public member_ `TArray<TObjectPtr<class UCameraCalibration>> CameraCalibrations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")`
- L263 _public member_ `FFootageCaptureMetadata Metadata;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")`
- L266 _public member_ `TArray<FFrameRange> CaptureExcludedFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture", DisplayName = "Excluded Frames")`
- L269 _public member_ `TObjectPtr<class UCameraCalibration> CameraCalibration_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "CameraCalibration is deprecated. Please use CameraCalibrations instead."))`
- L274 _public prototype_ `FIntPoint GetFootageColorResolution() const;` — Gets the resolution of the color channel
- L276 _public prototype_ `void GetFrameRanges(const FFrameRate& InTargetRate, ETimecodeAlignment InTimecodeAlignment, bool bInIncludeAudio, TMap<TWeakObjectPtr<UObject>, TRange<FFrameNumber>>& OutMediaFrameRanges, TRange<FFrameNumber>& OutProcessingFrameRange, TRange<FFrameNumber>& OutMaximumFrameRange) const;`
- L278 _public prototype_ `static TRange<FFrameNumber> GetAudioFrameRange(const FFrameRate& InTargetRate, ETimecodeAlignment InTimecodeAlignment, USoundWave* InMedia, const FTimecode& InMediaTimecode, const FFrameRate& InMediaTimecodeRate);`
- L283 _public prototype_ `FTimecode GetEffectiveImageTimecode(int32 InView) const;` — Functions for getting the effective timecode info on a track - note some tracks may not have a timecode set in which case their effective timecode is defined by others tracks that do have a timecode set.
- L284 _public prototype_ `FFrameRate GetEffectiveImageTimecodeRate(int32 InView) const;`
- L286 _public prototype_ `FTimecode GetEffectiveDepthTimecode(int32 InView) const;`
- L287 _public prototype_ `FFrameRate GetEffectiveDepthTimecodeRate(int32 InView) const;`
- L289 _public prototype_ `FTimecode GetEffectiveAudioTimecode() const;`
- L290 _public prototype_ `FFrameRate GetEffectiveAudioTimecodeRate() const;`
- L292 _public prototype_ `FVerifyResult VerifyData(ECaptureDataInitializedCheck InInitializedCheck) const;`
- L303 _public prototype_ `[[nodiscard]] TArray<FPathAssociation> CheckImageSequencePaths() const;` — Check the existence of the parent directory for all image sequences and return a list of those which fail the test.
- L306 _public prototype_ `static void PopulateCameraNames(UFootageCaptureData* InFootageCaptureData, FString& InOutCamera, TArray<TSharedPtr<FString>>& OutCameraNames);` — List of all RGB cameras (views) in the footage capture data. Ensures InOutCamera is a valid camera name.
- L308 _public prototype_ `int32 GetViewIndexByCameraName(const FString& InName) const;`
- L312 _private prototype_ `FVerifyResult ViewsContainsValidData(ECaptureDataInitializedCheck InInitializedCheck) const;` — Checks if camera calibration and views are valid.
- L313 _private prototype_ `FVerifyResult MetadataContainsValidData() const;`
- L314 _private prototype_ `FVerifyResult CalibrationContainsValidData() const;`
- L316 _private prototype_ `void GetDefaultTimecodeInfo(FTimecode& OutTimecode, FFrameRate& OutFrameRate) const;`
- L317 _private prototype_ `FString BuildAvailableCalibrationsString() const;`

#### struct `UFootageCaptureData::FPathAssociation`  
`struct FPathAssociation`  
_L294-300_
- L296 _public prototype_ `FPathAssociation(const FString& InPathOnDisk, const FString& InAssetPath);`
- L298 _public member_ `FString PathOnDisk;`
- L299 _public member_ `FString AssetPath;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CAPTUREDATACORE_API`
- L34 _prototype_ `ENUM_CLASS_FLAGS(ECaptureDataInitializedCheck);`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCaptureDataInternalsChanged) UCLASS(Abstract, MinimalAPI, BlueprintType) class UCaptureData : public UObject { GENERATED_BODY() public: enum UE_DEPRECATED(5.8, "EInitializedCheck has been moved to global scope. Please use the ECaptureDataInitializedCheck::.") EInitializedCheck { Full = 0, ImageSequencesOnly, }; virtual bool IsInitialized(ECaptureDataInitializedCheck InInitializedCheck) const PURE_VIRTUAL(UCaptureData::IsInitialized, return false;); FOnCaptureDataInternalsChanged& OnCaptureDataInternalsChanged() { return OnCaptureDataInternalsChangedDelegate; } #if WITH_EDITOR` — Delegate called when something changes in the capture data that others should know about

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Public/CaptureDataEditorBridge.h` (Public)


#### class `UE::CaptureManager::ICaptureDataEditorBridge`  
`class ICaptureDataEditorBridge : public IModuleInterface`  
_L13-17_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void DeferMarkDirty(TWeakObjectPtr<UObject> InObject) = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Public/CaptureDataLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCaptureDataCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCaptureDataCore, Log, All);`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Public/FrameRange.h` (Public)


#### struct `FFrameRange`  
`struct FFrameRange`  
_L12-31_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public prototype_ `bool operator==(const FFrameRange& InOther) const;`
- L22 _public member_ `FString Name = TEXT("Unn` — `UPROPERTY(EditAnywhere, Category = "Frame Range")`
- L25 _public member_ `int32 StartFrame = -1;` — `UPROPERTY(EditAnywhere, Category = "Frame Range")`
- L28 _public member_ `int32 EndFrame = -1;` — `UPROPERTY(EditAnywhere, Category = "Frame Range")`
- L30 _public prototype_ `static bool ContainsFrame(int32 InFrame, const TArray<FFrameRange>& InFrameRangeArray);`

#### enum `EFrameRangeType`  
`enum class EFrameRangeType : uint8`  
_L34-41_
- reflection: `UENUM()`
- L36 _public enumerator_ `UserExcluded UMETA(DisplayName = "User Excluded Frame")`
- L37 _public enumerator_ `ProcessingExcluded UMETA(DisplayName = "Processing Excluded Frame")`
- L38 _public enumerator_ `CaptureExcluded UMETA(DisplayName = "Capture Excluded Frame")`
- L39 _public enumerator_ `RateMatchingExcluded UMETA(DisplayName = "Rate Matching Excluded Frame")`
- L40 _public enumerator_ `None`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREDATACORE_API`
- L43 _typedef_ `typedef TMap<EFrameRangeType, TArray<FFrameRange>> FFrameRangeMap;`
- L46 _prototype_ `TArray<FFrameRange> PackIntoFrameRanges(TArray<FFrameNumber> InFrameNumbers);` — Packs a list of frame numbers into a sorted array of frame ranges. Essentially collapsing consecutive frame numbers into blocks

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Public/ImageSequencePathChecker.h` (Public)


#### class `UE::CaptureData::FImageSequencePathChecker`  
`class FImageSequencePathChecker`  
_L14-27_
- L17 _public prototype_ `explicit FImageSequencePathChecker(FText InAssetDisplayName);`
- L19 _public prototype_ `void Check(const UFootageCaptureData& InCaptureData);`
- L20 _public prototype_ `void DisplayDialog() const;`
- L21 _public prototype_ `bool HasError() const;`
- L24 _private member_ `int32 NumCaptureDataFootageAssets;`
- L25 _private member_ `int32 NumInvalidImageSequences;`
- L26 _private member_ `FText AssetDisplayName;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREDATACORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace CaptureData` (scope `UE`)

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Public/ImageSequenceUtils.h` (Public)


#### class `FImageSequenceUtils`  
`class FImageSequenceUtils`  
_L10-27_
- desc: Utility functions for getting information about image sequences.
- L14 _public prototype_ `static bool GetImageSequencePathAndFilesFromAsset(const class UImgMediaSource* InImgSequence, FString& OutFullSequencePath, TArray<FString>& OutImageFiles);` — Get image sequence path and list of files from image media source asset.
- L17 _public prototype_ `static bool GetImageSequenceFilesFromPath(const FString& InFullSequencePath, TArray<FString>& OutImageFiles, bool bInSort = true);` — Get list of image file paths from the image sequence path.
- L20 _public prototype_ `static bool GetImageSequenceInfoFromAsset(const class UImgMediaSource* InImgSequence, FIntVector2& OutDimensions, int32& OutNumImages);` — Get image sequence info (e.g. dimensions, number of images) from image media source asset.
- L23 _public prototype_ `static bool GetImageSequenceInfoFromPath(const FString& InFullSequencePath, FIntVector2& OutDimensions, int32& OutNumImages);` — Get image sequence info (e.g. dimensions, number of images) from image sequence path.
- L26 _public prototype_ `static bool IsImageSequenceValid(const class UImgMediaSource* InImgSequence);` — Returns if the image sequence is valid

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CAPTUREDATACORE_API`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataCore/Public/OpenCVHelperLocal.h` (Public)


#### class `FOpenCVHelperLocal`  
`class FOpenCVHelperLocal`  
_L9-53_
- desc: NB this is a cut-down version of the FOpenCVHelper class from OpenCV runtime plugin
- L20 _public member_ `inline static const TArray<FVector> UnitVectors = { { 1, 0, 0 },` — These axes must match the order in which they are declared in EAxis
- L30 _public function_ `static const FVector& UnitVectorFromAxisEnum(const EAxis Axis)`
- L36 _public prototype_ `static void ConvertCoordinateSystem(FTransform& Transform, const EAxis DstXInSrcAxis, const EAxis DstYInSrcAxis, const EAxis DstZInSrcAxis);` — Converts in-place the coordinate system of the given FTransform by specifying the source axes in terms of the destination axes
- L39 _public prototype_ `static void ConvertUnrealToOpenCV(FTransform& Transform);` — Converts in-place an FTransform in Unreal coordinates to OpenCV coordinates
- L42 _public prototype_ `static void ConvertOpenCVToUnreal(FTransform& Transform);` — Converts in-place an FTransform in OpenCV coordinates to Unreal coordinates
- L45 _public prototype_ `static FVector ConvertUnrealToOpenCV(const FVector& Transform);` — Converts an FVector in Unreal coordinates to OpenCV coordinates
- L48 _public prototype_ `static FVector ConvertOpenCVToUnreal(const FVector& Transform);` — Converts an FTransform in OpenCV coordinates to Unreal coordinates
- L51 _public prototype_ `static void ConvertOpenCVToUnreal(const FMatrix& InRotationOpenCV, const FVector& InTranslationOpenCV, FRotator& OutRotatorUE, FVector& OutTranslationUE);` — Converts a FMatrix and FVector in OpenCV coordinates to FRotator and FVector in Unreal coordinates

#### enum `FOpenCVHelperLocal::EAxis`  
`enum class EAxis`  
_L13-17_
- desc: Enumeration to specify any cartesian axis in positive or negative directions
- L15 _public enumerator_ `X`
- L15 _public enumerator_ `X`
- L15 _public enumerator_ `X`
- L16 _public enumerator_ `Xn`
- L16 _public enumerator_ `Xn`
- L16 _public enumerator_ `Xn`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API CAPTUREDATACORE_API`
