# Plugins / MetaHumanCoreTech

- module root: `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech`
- headers: 18; symbols: 210
- symbol kinds: class=8, delegate=1, enum=6, enumerator=24, function=17, macro=21, member=65, namespace=3, prototype=51, struct=13, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Projects, Slate, SlateCore
- PublicDependencyModuleNames: SpeechAnimationSolver

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Private/MetaHumanCoreCustomVersion.h` (Private)


#### struct `FMetaHumanCoreCustomVersion`  
`struct FMetaHumanCoreCustomVersion`  
_L10-36_
- desc: Custom serialization version for MetaHumanCore asset types TODO leaving this with the same name for now but needs revisiting now we have moved the class
- L32 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L35 _private function_ `FMetaHumanCoreCustomVersion()`

#### enum `FMetaHumanCoreCustomVersion::Type`  
`enum Type`  
_L12-29_
- L15 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L18 _public enumerator_ `AddAudioProcessingTypeToFrameData = 1` — Added audio processing type to frame data
- L21 _public enumerator_ `AddBodyAnimationToFrameData = 2` — Added body animation to frame data
- L24 _public enumerator_ `AddRawBodyAnimationSMPLXToFrameData = 3` — Added raw SMPLX body animation to frame data
- L27 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L28 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Private/SEnumGroupsWidget.h` (Private)


#### class `SEnumGroupsWidget`  
`template<typename TEnum> class SEnumGroupsWidget : public SCompoundWidget`  
_L16-114_
- inherits: `SCompoundWidget`
- desc: Widget used to select an enum value based on groupings.
- L26 _public typedef_ `using EnumGroupList = TArray<EnumGroup>;`
- L28 _public function_ `SLATE_BEGIN_ARGS(SEnumGroupsWidget<TEnum>) : _InitiallySelectedItem(static_cast<TEnum>(0)) , _EnumGroups(EnumGroupList())`
- L33 _public function_ `SLATE_ARGUMENT(TEnum, InitiallySelectedItem) SLATE_ARGUMENT(EnumGroupList, EnumGroups) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L68 _private function_ `TSharedRef<SWidget> GenerateMenu()`
- L104 _private function_ `void OnEnumSelected(TEnum SelectedEnum)`
- L111 _private member_ `TEnum SelectedItem;`
- L112 _private member_ `EnumGroupList EnumGroups;`
- L113 _private member_ `FOnSelectionChanged OnSelectionChanged;`

#### struct `SEnumGroupsWidget::EnumGroup`  
`struct EnumGroup`  
_L21-25_
- L23 _public member_ `FText GroupName;`
- L24 _public member_ `TArray<TEnum> EnumValues;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TEnum) struct EnumGroup { FText GroupName; TArray<TEnum> EnumValues; };`
- L57 _function_ `.Text_Lambda([this]() { return StaticEnum<TEnum>()->GetDisplayNameTextByValue(static_cast<int64>(SelectedItem)); }) .ToolTipText_Lambda([this]() { return StaticEnum<TEnum>()->GetDisplayNameTextByValue(static_cast<int64>(SelectedItem)); }) ] ];` (scope `SEnumGroupsWidget::SLATE_ARGUMENT`)
- L60 _function_ `.ToolTipText_Lambda([this]() { return StaticEnum<TEnum>()->GetDisplayNameTextByValue(static_cast<int64>(SelectedItem)); }) ] ];` (scope `SEnumGroupsWidget::SLATE_ARGUMENT`)
- L88 _function_ `` (scope `SEnumGroupsWidget::GenerateMenu`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/AudioDrivenAnimationMood.h` (Public)


#### class `SAudioDrivenAnimationMood`  
`class SAudioDrivenAnimationMood : public SCompoundWidget`  
_L18-26_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAudioDrivenAnimationMood)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, bool bInOffline, TSharedRef<IPropertyHandle> InMoodPropertyHandle);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANCORETECH_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/CoreUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace epic`
- L9 _namespace_ `namespace core` (scope `epic`)
- L12 _prototype_ `void BurnPointsIntoImage(const TArray<FVector2D>& InPoints, int32 InWidth, int32 InHeight, TArray<uint8>& InImgData, uint8 InRed, uint8 InGreen, uint8 InBlue, int32 InSize, bool bInUseAntiAliasing = true);` (scope `epic::core`)
- L14 _prototype_ `void BurnPointsIntoImage(const TArray<FVector2D>& InPoints, int32 InWidth, int32 InHeight, FColor* OutImgData, uint8 InRed, uint8 InGreen, uint8 InBlue, int32 InSize, bool bInUseAntiAliasing = true);` (scope `epic::core`)
- L16 _prototype_ `void BurnLineIntoImage(const FVector2D& InStartPoint, const FVector2D& InEndPoint, int32 InWidth, int32 InHeight, TArray<uint8>& OutImgData, uint8 InRed, uint8 InGreen, uint8 InBlue, int32 InLineWidth, bool bInUseAntiAliasing = true);` (scope `epic::core`)
- L18 _prototype_ `void BurnLineIntoImage(const FVector2D& InStartPoint, const FVector2D& InEndPoint, int32 InWidth, int32 InHeight, FColor* OutImgData, uint8 InRed, uint8 InGreen, uint8 InBlue, int32 InLineWidth, bool bInUseAntiAliasing = true);` (scope `epic::core`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/DepthMapDiagnosticsResult.h` (Public)


#### struct `FDepthMapDiagnosticsResult`  
`struct FDepthMapDiagnosticsResult`  
_L10-23_
- reflection: `USTRUCT()`
- L15 _public member_ `int32 NumFacePixels = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Diagnostics")`
- L18 _public member_ `int32 NumFaceValidDepthMapPixels = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Diagnostics")`
- L21 _public member_ `float FaceWidthInPixels = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Diagnostics")`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/FrameAnimationData.h` (Public)


#### enum `EFrameAnimationQuality`  
`enum class EFrameAnimationQuality : uint8`  
_L13-21_
- reflection: `UENUM()`
- L15 _public enumerator_ `Undefined`
- L16 _public enumerator_ `Preview`
- L17 _public enumerator_ `Final`
- L18 _public enumerator_ `PostFiltered`
- L19 _public enumerator_ `Custom1`
- L20 _public enumerator_ `Custom2`

#### enum `EAudioProcessingMode`  
`enum class EAudioProcessingMode : uint8`  
_L24-30_
- reflection: `UENUM()`
- L26 _public enumerator_ `Undefined`
- L27 _public enumerator_ `FullFace`
- L28 _public enumerator_ `TongueTracking`
- L29 _public enumerator_ `MouthOnly`

#### enum `EFrameAnimationDataType`  
`enum class EFrameAnimationDataType : uint8`  
_L33-39_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L35 _public enumerator_ `Face = 1 << 0`
- L36 _public enumerator_ `Body = 1 << 1`
- L38 _public enumerator_ `Any = Face | Body`

#### struct `FFrameAnimationData`  
`struct FFrameAnimationData`  
_L44-96_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `FTransform Pose = FTransform(FQuat(ForceInitToZero), FVector(ForceInitToZero), FVector(ForceInitToZero));` — `UPROPERTY()`
- L52 _public member_ `TArray<float> RawPoseData;` — `UPROPERTY(Transient)`
- L55 _public member_ `TMap<FString, float> AnimationData;` — `UPROPERTY(BlueprintReadOnly, Category = "AnimationData")`
- L58 _public member_ `TMap<FString, float> RawAnimationData;` — `UPROPERTY(Transient)`
- L61 _public member_ `TMap<FString, FTransform> BodyAnimationData;` — `UPROPERTY(BlueprintReadOnly, Category = "AnimationData")`
- L64 _public member_ `TArray<float> RawBodyAnimationSMPLXShape;` — `UPROPERTY(BlueprintReadOnly, Category = "AnimationData")`
- L67 _public member_ `TArray<float> RawBodyAnimationSMPLXPose;` — `UPROPERTY(BlueprintReadOnly, Category = "AnimationData")`
- L70 _public member_ `FVector RawBodyAnimationSMPLXTranslation = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "AnimationData")`
- L73 _public member_ `TMap<FString, FTransform> RawBodyAnimationSMPLXData;` — `UPROPERTY(BlueprintReadOnly, Category = "AnimationData")`
- L76 _public member_ `FMetaHumanMeshData MeshData;` — `UPROPERTY(Transient)`
- L79 _public member_ `EFrameAnimationQuality AnimationQuality = EFrameAnimationQuality::Undefined;` — `UPROPERTY()`
- L82 _public member_ `EAudioProcessingMode AudioProcessingMode = EAudioProcessingMode::Undefined;` — `UPROPERTY()`
- L85 _public prototype_ `bool ContainsData() const;` — `UE_DEPRECATED(5.8, "ContainsData() is deprecated. Use new ContainsData function which takes the data type as a parameter")`
- L87 _public prototype_ `bool ContainsData(EFrameAnimationDataType InDataType) const;`
- L95 _public prototype_ `void Serialize(FArchive& Ar);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCORETECH_API`
- L89 _function_ `friend FArchive& operator<<(FArchive& Ar, FFrameAnimationData& P)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/FrameTrackingConfidenceData.h` (Public)


#### struct `FFrameTrackingConfidenceData`  
`struct FFrameTrackingConfidenceData`  
_L11-17_
- reflection: `USTRUCT()`
- L16 _public member_ `double Value = -1;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/FrameTrackingContourData.h` (Public)


#### struct `FMarkerCurveState`  
`struct FMarkerCurveState`  
_L11-23_
- reflection: `USTRUCT()`
- L16 _public member_ `bool bVisible = false;` — `UPROPERTY()`
- L19 _public member_ `bool bActive = false;` — `UPROPERTY()`
- L22 _public member_ `bool bSelected = false;` — `UPROPERTY(Transient)`

#### struct `FTrackingContour`  
`struct FTrackingContour`  
_L26-60_
- reflection: `USTRUCT()`
- L31 _public member_ `TArray<FVector2D> DensePoints;` — `UPROPERTY(EditAnywhere, Category = "InternalPoints")`
- L34 _public member_ `TArray<float> DensePointsConfidence;` — `UPROPERTY()`
- L37 _public member_ `FString StartPointName;` — `UPROPERTY()`
- L40 _public member_ `FString EndPointName;` — `UPROPERTY()`
- L43 _public member_ `FMarkerCurveState State;` — `UPROPERTY(EditAnywhere, Category = "Markers")`
- L51 _public function_ `void Serialize(FArchive& Ar)`

#### struct `FFrameTrackingContourData`  
`struct FFrameTrackingContourData`  
_L63-108_
- reflection: `USTRUCT()`
- L68 _public member_ `FString Camera;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Tracking", DisplayName = "Camera Name")`
- L71 _public member_ `TMap<FString, FTrackingContour> TrackingContours;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Tracking", DisplayName = "Markers")`
- L73 _public function_ `inline bool ContainsData() const`
- L89 _public function_ `inline bool ContainsActiveData() const`
- L103 _public function_ `void Serialize(FArchive& Ar)`

#### struct `FTrackingContour3D`  
`struct FTrackingContour3D`  
_L111-117_
- reflection: `USTRUCT()`
- L116 _public member_ `TArray<FVector3d> DensePoints;` — `UPROPERTY(VisibleAnywhere, Category = "Tracking")`

#### Free symbols / members of external scopes

- L45 _function_ `friend FArchive& operator<<(FArchive& Ar, FTrackingContour& P)`
- L92 _function_ `` (scope `FFrameTrackingContourData::ContainsActiveData`)
- L97 _function_ `friend FArchive& operator<<(FArchive& Ar, FFrameTrackingContourData& P)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/GuiToRawControlsUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GuiToRawControlsUtils`
- L9 _prototype_ `TMap<FString, float> ConvertGuiToRawControls(const TMap<FString, float>& InGuiControls);` (scope `GuiToRawControlsUtils`)

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/MetaHumanCommonDataUtils.h` (Public)


#### enum `EMetaHumanImportDNAType`  
`enum class EMetaHumanImportDNAType : uint8`  
_L12-17_
- L14 _public enumerator_ `Face`
- L15 _public enumerator_ `Body`
- L16 _public enumerator_ `Combined`

#### struct `FMetaHumanCommonDataUtils`  
`struct FMetaHumanCommonDataUtils`  
_L19-68_
- L22 _public prototype_ `static const FString GetFaceDNAFilesystemPath();` — Returns a constructed path to face DNA file
- L25 _public prototype_ `static const FString GetBodyDNAFilesystemPath();` — Returns a constructed path to body DNA file
- L28 _public prototype_ `static const FString GetCombinedDNAFilesystemPath();` — Returns a constructed path to combined DNA file
- L31 _public prototype_ `static void SetPostProcessAnimBP(TNotNull<class USkeletalMesh*> InSkelMesh, FStringView InPackageName);` — Sets the specified post-processing anim BP on a skeletal mesh taking into account UE/UEFN routes
- L34 _public prototype_ `static TSoftObjectPtr<UObject> GetDefaultControlRigFromRegistry(const FStringView InAssetPath);` — Returns a soft object ptr to a UObject of UControlRigBlueprint retrieved from asset registry of a specified control rig
- L37 _public prototype_ `static TSoftObjectPtr<UObject> GetDefaultFaceControlRig(const FStringView InAssetPath);` — `UE_DEPRECATED(5.8, "Please use GetDefaultControlRigFromRegistry function instead")`
- L40 _public prototype_ `static FString GetArchetypeDNAPath(EMetaHumanImportDNAType InImportDNAType);` — Returns a file system path to a dna file for specified import type
- L45 _public prototype_ `static FStringView GetAnimatorPluginFaceSkeletonPath();` — Returns the path to common face skeleton, stored in Animator plugin in long object path format
- L48 _public prototype_ `static FStringView GetAnimatorPluginFaceControlRigPath();` — Returns the path to common face control board control rig, stored in Animator plugin in long object path format
- L51 _public prototype_ `static FStringView GetAnimatorPluginFacePostProcessABPPath();` — Returns the path to common face post-processing anim blueprint, stored in Animator plugin in long object path format
- L54 _public prototype_ `static FStringView GetCharacterPluginFaceSkeletonPath();` — Returns the path to common face skeleton, stored in Character plugin in long object path format
- L57 _public prototype_ `static FStringView GetCharacterPluginBodySkeletonPath();` — Returns the path to body skeleton, stored in Character plugin in long object path format
- L60 _public prototype_ `static FStringView GetCharacterPluginFaceControlRigPath();` — Returns the path to common face control board control rig, stored in Character plugin in long object path format
- L63 _public prototype_ `static FStringView GetCharacterPluginFacePostProcessABPPath();` — Returns the path to common face post-processing anim blueprint, stored in Character plugin in long object path format
- L66 _public prototype_ `static FStringView GetCharacterPluginBodyPostProcessABPPath();` — Returns the path to body post-processing anim blueprint, stored in Character plugin in long object path format

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCORETECH_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/MetaHumanHeadTransform.h` (Public)


#### class `FMetaHumanHeadTransform`  
`class FMetaHumanHeadTransform`  
_L16-25_
- L20 _public prototype_ `static FTransform MeshToBone(const FTransform& InTransform);`
- L21 _public prototype_ `static FTransform BoneToMesh(const FTransform& InTransform);`
- L23 _public prototype_ `static FTransform HeadToRoot(const FTransform& InTransform);`
- L24 _public prototype_ `static FTransform RootToHead(const FTransform& InTransform);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCORETECH_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/MetaHumanMeshData.h` (Public)


#### struct `FMetaHumanMeshData`  
`struct FMetaHumanMeshData`  
_L11-26_
- reflection: `USTRUCT()`
- L16 _public member_ `TArray<float> FaceMeshVertData;` — `UPROPERTY()`
- L19 _public member_ `TArray<float> TeethMeshVertData;` — `UPROPERTY()`
- L22 _public member_ `TArray<float> LeftEyeMeshVertData;` — `UPROPERTY()`
- L25 _public member_ `TArray<float> RightEyeMeshVertData;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/MetaHumanOneEuroFilter.h` (Public)


#### class `FMetaHumanOneEuroFilter`  
`class FMetaHumanOneEuroFilter`  
_L17-75_
- L49 _public prototype_ `FMetaHumanOneEuroFilter();` — Default constructor
- L51 _public prototype_ `FMetaHumanOneEuroFilter(const double InMinCutoff, const double InCutoffSlope, const double InDeltaCutoff);`
- L54 _public prototype_ `double Filter(const double InRaw, const double InDeltaTime);` — Smooth parameter
- L57 _public prototype_ `void SetMinCutoff(const double InMinCutoff);` — Set the minimum cutoff
- L60 _public prototype_ `void SetCutoffSlope(const double InCutoffSlope);` — Set the cutoff slope
- L63 _public prototype_ `void SetDeltaCutoff(const double InDeltaCutoff);` — Set the delta slope
- L67 _private prototype_ `const double CalculateCutoff(const double InValue);`
- L68 _private prototype_ `const double CalculateAlpha(const double InCutoff, const double InDeltaTime) const;`
- L70 _private member_ `double MinCutoff;`
- L71 _private member_ `double CutoffSlope;`
- L72 _private member_ `double DeltaCutoff;`
- L73 _private member_ `FMetaHumanLowpassFilter RawFilter;`
- L74 _private member_ `FMetaHumanLowpassFilter DeltaFilter;`

#### class `FMetaHumanOneEuroFilter::FMetaHumanLowpassFilter`  
`class FMetaHumanLowpassFilter`  
_L21-44_
- L26 _public prototype_ `FMetaHumanLowpassFilter();` — Default constructor
- L29 _public prototype_ `double Filter(const double InValue, const double InAlpha);` — Calculate
- L32 _public prototype_ `bool IsFirstTime() const;` — If the filter was not executed yet
- L35 _public prototype_ `double GetPrevious() const;` — Get the previous filtered value
- L40 _private member_ `double Previous;` — The previous filtered value
- L43 _private member_ `bool bFirstTime;` — If this is the first time doing a filter

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCORETECH_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/MetaHumanRealtimeCalibration.h` (Public)


#### class `FMetaHumanRealtimeCalibration`  
`class FMetaHumanRealtimeCalibration`  
_L9-31_
- L13 _public prototype_ `FMetaHumanRealtimeCalibration(const TArray<FName>& InProperties, const TArray<float>& InNeutralFrame, const float InAlpha);`
- L15 _public prototype_ `static TArray<FName> GetDefaultProperties();`
- L17 _public prototype_ `void SetProperties(const TArray<FName>& InProperties);`
- L18 _public prototype_ `void SetAlpha(float Alpha);`
- L19 _public prototype_ `void SetNeutralFrame(const TArray<float>& InNeutralFrame);`
- L21 _public prototype_ `bool ProcessFrame(const TArray<FName>& InPropertyNames, TArray<float>& InOutFrame) const;`
- L25 _private member_ `static TArray<FName> DefaultProperties;`
- L27 _private member_ `TArray<FName> Properties;`
- L28 _private member_ `TArray<float> NeutralFrame;`
- L29 _private member_ `float Alpha = 1.0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCORETECH_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/MetaHumanRealtimeSmoothing.h` (Public)


#### enum `EMetaHumanRealtimeSmoothingParamMethod`  
`enum class EMetaHumanRealtimeSmoothingParamMethod : uint8`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `RollingAverage = 0`
- L21 _public enumerator_ `OneEuro`

#### struct `FMetaHumanRealtimeSmoothingParam`  
`struct FMetaHumanRealtimeSmoothingParam`  
_L25-42_
- reflection: `USTRUCT()`
- L32 _public member_ `EMetaHumanRealtimeSmoothingParamMethod Method = EMetaHumanRealtimeSmoothingParamMethod::RollingAverage;` — `UPROPERTY(EditAnywhere, Category = "Data")`
- L35 _public member_ `uint8 RollingAverageFrame = 1;` — `UPROPERTY(EditAnywhere, Category = "Data", DisplayName = "Number of frames", meta = (EditCondition = "Method == EMetaHumanRealtimeSmoothingParamMethod::RollingAverage", EditConditionHides))`
- L38 _public member_ `float OneEuroSlope = 5000;` — `UPROPERTY(EditAnywhere, Category = "Data", DisplayName = "Slope", meta = (EditCondition = "Method == EMetaHumanRealtimeSmoothingParamMethod::OneEuro", EditConditionHides))`
- L41 _public member_ `float OneEuroMinCutoff = 5;` — `UPROPERTY(EditAnywhere, Category = "Data", DisplayName = "Min cutoff", meta = (EditCondition = "Method == EMetaHumanRealtimeSmoothingParamMethod::OneEuro", EditConditionHides))`

#### class `UMetaHumanRealtimeSmoothingParams`  
`class UMetaHumanRealtimeSmoothingParams : public UDataAsset`  
_L45-55_
- reflection: `UCLASS(MinimalAPI, DisplayName = "MetaHuman Realtime Smoothing")`
- inherits: `UDataAsset`
- L51 _public prototype_ `virtual void PostInitProperties() override;`
- L54 _public member_ `TMap<FName, FMetaHumanRealtimeSmoothingParam> Parameters;` — `UPROPERTY(EditAnywhere, Category = "Smoothing")`

#### class `FMetaHumanRealtimeSmoothing`  
`class FMetaHumanRealtimeSmoothing`  
_L57-84_
- L62 _public prototype_ `FMetaHumanRealtimeSmoothing(const TMap<FName, FMetaHumanRealtimeSmoothingParam>& InSmoothingParams);`
- L64 _public prototype_ `static TMap<FName, FMetaHumanRealtimeSmoothingParam> GetDefaultSmoothingParams();`
- L66 _public prototype_ `bool ProcessFrame(const TArray<FName>& InPropertyNames, TArray<float>& InOutFrame, double InDeltaTime);`
- L70 _private member_ `TMap<FName, FMetaHumanRealtimeSmoothingParam> SmoothingParams;`
- L72 _private member_ `static constexpr uint8 DefaultRollingAverageFrameCount = 1;`
- L73 _private member_ `static TMap<FName, uint8> DefaultRollingAverage;`
- L74 _private member_ `static TMap<FName, TPair<float, float>> DefaultOneEuro;`
- L76 _private member_ `uint8 RollingAverageMaxBufferSize = 1;`
- L77 _private member_ `TArray<TArray<float>> RollingAverageBuffer;`
- L79 _private member_ `TMap<FName, FMetaHumanOneEuroFilter> OneEuroFilters;`
- L80 _private member_ `FMetaHumanOneEuroFilter OneEuroYAxis[3];`
- L81 _private member_ `FMetaHumanOneEuroFilter OneEuroXAxis[3];`
- L83 _private prototype_ `bool IsOrientation(const FName& InProperty) const;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANCORETECH_API`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/MetaHumanTrace.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define MHA_ENABLE_TRACE 0 // Change to one to enable Insights tracing`
- L8 _macro_ `#define MHA_CPUPROFILER_EVENT_SCOPE(Name) TRACE_CPUPROFILER_EVENT_SCOPE(Name)`
- L9 _macro_ `#define MHA_CPUPROFILER_EVENT_SCOPE_STR(Name) TRACE_CPUPROFILER_EVENT_SCOPE_STR(Name)`
- L10 _macro_ `#define MHA_CPUPROFILER_EVENT_SCOPE_TEXT(Name) TRACE_CPUPROFILER_EVENT_SCOPE_TEXT(Name)`
- L12 _macro_ `#define MHA_CPUPROFILER_EVENT_SCOPE(Name)`
- L13 _macro_ `#define MHA_CPUPROFILER_EVENT_SCOPE_STR(Name)`
- L14 _macro_ `#define MHA_CPUPROFILER_EVENT_SCOPE_TEXT(Name)`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/SupressWarnings.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define MH_DISABLE_EIGEN_WARNINGS THIRD_PARTY_INCLUDES_START // use UE warning suppression if we can`
- L9 _macro_ `#define MH_ENABLE_WARNINGS THIRD_PARTY_INCLUDES_END`
- L11 _macro_ `#define MH_DISABLE_EIGEN_WARNINGS \`
- L15 _macro_ `#define MH_ENABLE_WARNINGS \`
- L25 _macro_ `#define MH_ENABLE_WARNINGS __pragma(warning(pop))`
- L27 _macro_ `#define MH_DISABLE_EIGEN_WARNINGS`
- L28 _macro_ `#define MH_ENABLE_WARNINGS`

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanCoreTech/Public/TrackerOpticalFlowConfiguration.h` (Public)


#### struct `FTrackerOpticalFlowConfiguration`  
`struct FTrackerOpticalFlowConfiguration`  
_L10-22_
- reflection: `USTRUCT()`
- L15 _public member_ `bool bUseOpticalFlow{};` — `UPROPERTY()`
- L18 _public member_ `bool bUseConfidence{};` — `UPROPERTY()`
- L21 _public member_ `bool bUseForwardFlow{};` — `UPROPERTY()`
