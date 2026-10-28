# Plugins / AnimationModifierLibrary

- module root: `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary`
- headers: 12; symbols: 172
- symbol kinds: class=10, enum=6, enumerator=27, function=1, macro=1, member=74, prototype=46, struct=7
- PrivateDependencyModuleNames: AnimationBlueprintLibrary, AnimationModifiers, Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: 

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Private/PoseExtractorUtilityLibrary.h` (Private)


#### struct `FPoseExtractorUtilityLibrary`  
`struct FPoseExtractorUtilityLibrary`  
_L14-30_
- L16 _public prototype_ `FPoseExtractorUtilityLibrary(UAnimSequence* Animation);`
- L17 _public prototype_ `bool AddBone(const FBoneReference& Bone);`
- L18 _public prototype_ `bool AddBone(const FName& BoneName, int32 BoneIndex);`
- L19 _public prototype_ `bool CacheGlobalBoneTransforms();`
- L20 _public prototype_ `const FTransform& GetGlobalBoneTransform(int32 AnimKey, uint16 BoneIndex) const;`
- L21 _public prototype_ `const FTransform& GetGlobalBoneTransform(int32 AnimKey, const FName& BoneName) const;`
- L24 _private member_ `const USkeleton* Skeleton = nullptr;`
- L25 _private member_ `const IAnimationDataModel* Model = nullptr;`
- L26 _private member_ `TArray<uint16> BoneIndicesWithParents;`
- L27 _private member_ `TMap<uint16, uint16> ReducedIndexMap;`
- L28 _private member_ `TMap<FName, uint16> NameToBoneIndex;`
- L29 _private member_ `TArray<TArray<FTransform>> GlobalBoneTransforms;`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/AnimationModifierLibrary.h` (Public)


#### class `FAnimationModifierLibraryModule`  
`class FAnimationModifierLibraryModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/CopyBonesModifier.h` (Public)


#### struct `FBoneReferencePair`  
`struct FBoneReferencePair`  
_L11-22_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Bone to get transform from
- L21 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category = "Default")` — Bone to update with the transform copied from SourceBone

#### class `UCopyBonesModifier`  
`class UCopyBonesModifier : public UAnimationModifier`  
_L26-45_
- reflection: `UCLASS()`
- inherits: `UAnimationModifier`
- desc: Animation Modifier to copy the transform of 'SourceBone(s)' to 'TargetBone(s)'
- L34 _public member_ `TArray<FBoneReferencePair> BonePairs;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — Source and Target bone pairs
- L38 _public member_ `EAnimPoseSpaces BonePoseSpace = EAnimPoseSpaces::World;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — Space to convert SourceBone transforms into before copying them to TargetBone
- L40 _public prototype_ `UCopyBonesModifier();`
- L42 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`
- L43 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* Animation) override;`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/CurveFromSyncMarkersModifier.h` (Public)


#### struct `FSyncMarkerCurveEntry`  
`struct FSyncMarkerCurveEntry`  
_L10-19_
- reflection: `USTRUCT(Experimental, BlueprintType)`
- desc: A sync marker name and the float value to assign to the curve at that marker's time
- L15 _public member_ `FName SyncMarkerName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`
- L18 _public member_ `float Value = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`

#### class `UCurveFromSyncMarkersModifier`  
`class UCurveFromSyncMarkersModifier : public UAnimationModifier`  
_L25-44_
- reflection: `UCLASS(Experimental)`
- inherits: `UAnimationModifier`
- desc: Generates a float curve from the authored sync markers on an animation sequence. Each sync marker listed in SyncMarkerValues contributes a curve key at the marker's time with the corresponding float value.
- L32 _public member_ `TArray<FSyncMarkerCurveEntry> SyncMarkerValues;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — List of sync marker names and the float value each should contribute to the generated curve
- L36 _public member_ `FName CurveName = "Cu` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Name of the float curve to add to the animation
- L40 _public member_ `bool bRemoveCurveOnRevert = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — If true, the generated curve is removed when the modifier is reverted
- L42 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`
- L43 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* Animation) override;`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/EncodeRootBoneModifier.h` (Public)


#### enum `EEncodeRootBoneAxis`  
`enum class EEncodeRootBoneAxis : uint8`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `X`
- L13 _public enumerator_ `Y`
- L14 _public enumerator_ `Z`

#### struct `FEncodeRootBoneWeightedBone`  
`struct FEncodeRootBoneWeightedBone`  
_L18-27_
- reflection: `USTRUCT()`
- L23 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L26 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`

#### struct `FEncodeRootBoneWeightedBoneAxis`  
`struct FEncodeRootBoneWeightedBoneAxis : public FEncodeRootBoneWeightedBone`  
_L30-36_
- reflection: `USTRUCT()`
- inherits: `FEncodeRootBoneWeightedBone`
- L35 _public member_ `EEncodeRootBoneAxis BoneAxis = EEncodeRootBoneAxis::Y;` — `UPROPERTY(EditAnywhere, Category = "Settings")`

#### class `UEncodeRootBoneModifier`  
`class UEncodeRootBoneModifier : public UAnimationModifier`  
_L39-51_
- reflection: `UCLASS()`
- inherits: `UAnimationModifier`
- L45 _public member_ `TArray<FEncodeRootBoneWeightedBone> WeightedBoneToComputeRootPosition;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L48 _public member_ `TArray<FEncodeRootBoneWeightedBoneAxis> WeightedBoneToComputeRootOrientation;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L50 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/FootstepAnimEventsModifier.h` (Public)


#### enum `EDetectionTechnique`  
`enum class EDetectionTechnique : uint8`  
_L13-37_
- reflection: `UENUM()`
- desc: Detection method used for placing a notify / marker in the track
- L20 _public enumerator_ `PassThroughReferenceBone` — Create anim event when foot bone passes through a given reference bone. Note that the translation vector of the reference bone will be used as the normal vector for the detection plane used to determine if the foot bone has crossed the reference bone.
- L28 _public enumerator_ `FootBoneReachesGround` — Create anim event when foot bone reaches the ground level within a given threshold. Note that this will only be true if the foot bone position goes from NOT being within the threshold to being WITHIN the ground threshold.
- L36 _public enumerator_ `FootBoneSpeed` — Create anim event when foot bone translation speed is below a given threshold and nearly zero. Note that the foot bone translation speed is normalize therefore when a footstep occurs the speed will be very close to zero.

#### struct `FFootDefinition`  
`struct FFootDefinition`  
_L40-79_
- reflection: `USTRUCT(BlueprintType)`
- L45 _public member_ `FName FootBoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L48 _public member_ `FName ReferenceBoneName = FName(TEXT("root` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")`
- L51 _public member_ `bool bShouldGenerateSyncMarkers = false;` — `UPROPERTY(EditAnywhere, Category = "Sync Markers")`
- L54 _public member_ `FName SyncMarkerTrackName = TEXT("Foo` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta=(EditCondition="bShouldGenerateSyncMarkers"))`
- L57 _public member_ `FName SyncMarkerName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta=(EditCondition="bShouldGenerateSyncMarkers"))`
- L60 _public member_ `EDetectionTechnique SyncMarkerDetectionTechnique = EDetectionTechnique::PassThroughReferenceBone;` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta=(EditCondition="bShouldGenerateSyncMarkers"))`
- L63 _public member_ `bool bShouldSkipSyncMarkerIfFootBoneSpeedStartsBelowThreshold = true;` — `UPROPERTY(EditAnywhere, Category = "Sync Markers", meta=(EditCondition = "SyncMarkerDetectionTechnique == EDetectionTechnique::FootBoneSpeed", EditConditionHides))`
- L66 _public member_ `bool bShouldGenerateNotifies = false;` — `UPROPERTY(EditAnywhere, Category = "Notifies")`
- L69 _public member_ `FName FootstepNotifyTrackName = TEXT("Foo` — `UPROPERTY(EditAnywhere, Category = "Notifies", meta=(EditCondition="bShouldGenerateNotifies"))`
- L72 _public member_ `TSubclassOf<UAnimNotify> FootstepNotify;` — `UPROPERTY(EditAnywhere, Category = "Notifies", meta=(EditCondition="bShouldGenerateNotifies"))`
- L75 _public member_ `EDetectionTechnique FootstepNotifyDetectionTechnique = EDetectionTechnique::FootBoneSpeed;` — `UPROPERTY(EditAnywhere, Category = "Notifies", meta=(EditCondition="bShouldGenerateNotifies"))`
- L78 _public member_ `bool bShouldSkipNotifyIfFootBoneSpeedStartsBelowThreshold = true;` — `UPROPERTY(EditAnywhere, Category = "Notifies", meta=(EditCondition = "FootstepNotifyDetectionTechnique == EDetectionTechnique::FootBoneSpeed", EditConditionHides))`

#### class `UFootstepAnimEventsModifier`  
`class UFootstepAnimEventsModifier : public UAnimationModifier`  
_L83-167_
- reflection: `UCLASS(meta=(IsBlueprintBase=true))`
- inherits: `UAnimationModifier`
- desc: Generates animation notifies and/or sync markers for any specified bone(s)
- L89 _public prototype_ `UFootstepAnimEventsModifier();`
- L93 _public member_ `int SampleRate;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (Units="Hz", UIMin=1))` — Rate used to sample the animation
- L97 _public member_ `float GroundThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — Threshold for determining if a foot bone position can be considered to be on the ground level
- L106 _public member_ `float SpeedThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (ClampMin=0.0f, ClampMax=1.0f))` — Threshold to start finding the smallest foot bone translation speed. Note that the foot bone translation speed is normalize therefore when a footstep occurs the speed will be very close to zero, thus for most cases this value won't need to be changed.
- L110 _public member_ `TArray<FFootDefinition> FootDefinitions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (TitleProperty = "FootBoneName"))` — Foot bone(s) to be processed
- L117 _public member_ `bool bShouldRemovePreExistingNotifiesOrSyncMarkers;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="Remove Pre Existing Notifies or Sync Markers")` — If true, applying the anim modifier becomes a destructive action, meaning that any existing matched tracks will have their data overwritten by the modifier. Otherwise, no previous notifies or sync markers will removed when applying the anim modifier.
- L120 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* InAnimation) override;` — Begin UAnimationModifier interface
- L121 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* InAnimation) override;`
- L147 _private member_ `TSet<FName> GeneratedNotifyTracks;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Settings"))` — Keep track of to be generated tracks during modifier application
- L151 _private member_ `TSet<FName> ProcessedNotifyTracks;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Settings"))` — Keep track of tracks modified during modifier application
- L154 _private prototype_ `void ValidateNotifyTracks(UAnimSequence* InAnimation);` — Prepare all requested notify tracks before starting to generate notifies or sync markers
- L157 _private prototype_ `void GatherNotifyTracksInfo(const UAnimSequence* InAnimation);` — Determine which notify tracks will be generated when this modifier is applied
- L160 _private prototype_ `void PrepareNotifyTrack(UAnimSequence* InAnimation, FName InRequestedNotifyTrackName);` — Create new notify track if requested track does not exist, otherwise, if the requested track exist, clean-up data if needed.
- L163 _private prototype_ `bool CanWePlaceEventAtSample(const FFootSampleState & InTestLegSampleState, EDetectionTechnique DetectionTechnique) const;` — Test if we can place anim event at given sample
- L166 _private prototype_ `float ComputeBoneSpeed(const FAnimPose& InPose, const FAnimPose &InFuturePose, float InDelta, FName InFootBoneName) const;` — Get a bone translation speed

#### struct `UFootstepAnimEventsModifier::FFootSampleState`  
`struct FFootSampleState`  
_L127-143_
- desc: Store state of a foot during a sample step
- L129 _public member_ `double GroundLevel = UE_DOUBLE_BIG_NUMBER;`
- L130 _public member_ `double RefBoneTranslationDotRefBoneToFootBoneVec = 0.0;`
- L131 _public member_ `double PrevRefBoneTranslationDotRefBoneToFootBoneVec = 0.0;`
- L132 _public member_ `bool bIsFootBoneInGround = false;`
- L133 _public member_ `bool bWasFootBoneInGround = false;`
- L134 _public member_ `float FootBoneSpeed = 0.0f;`
- L135 _public member_ `float PrevFootBoneSpeed = 0.0f;`
- L136 _public member_ `float MaxFootSpeed = -MAX_FLT;`
- L137 _public member_ `float MinFootSpeed = MAX_FLT;`
- L138 _public member_ `float MinFootSpeedBelowThreshold = MAX_FLT;`
- L139 _public member_ `float TimeAtMinFootSpeedBelowThreshold = MAX_FLT;`
- L140 _public member_ `bool bIsLast = false;`
- L141 _public member_ `bool bSkipNextSyncMarker = false;`
- L142 _public member_ `bool bSkipNextNotify = false;`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/MirrorModifier.h` (Public)


#### class `UMirrorModifier`  
`class UMirrorModifier : public UAnimationModifier`  
_L14-37_
- reflection: `UCLASS()`
- inherits: `UAnimationModifier`
- desc: Animation Modifier to mirror an animation using a mirror data table
- L22 _public member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — MirrorDataTable that will be used for mirroring the aniamtion
- L26 _public member_ `bool bUpdateSyncMarkers = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If sync markers should be mirrored in the animation
- L30 _public member_ `bool bUpdateNotifies = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If notifies should be mirrored in the animation
- L32 _public prototype_ `UMirrorModifier();`
- L33 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`
- L34 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* Animation) override;`
- L36 _protected prototype_ `void InitializeBoneContainer(const UAnimSequenceBase* AnimationSequenceBase, FBoneContainer& OutContainer) const;`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/MotionExtractorModifier.h` (Public)


#### class `UMotionExtractorModifier`  
`class UMotionExtractorModifier : public UAnimationModifier`  
_L15-95_
- reflection: `UCLASS()`
- inherits: `UAnimationModifier`
- desc: Extracts motion from a bone in the animation and bakes it into a curve
- L23 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Bone we are going to generate the curve from
- L27 _public member_ `FName RelativeToBoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(EditCondition="Space == EMotionExtractor_Space::RelativeToBone"))` — Bone which we'll use as the reference frame to generate this curve from. Space must be RelativeToBone to use this.
- L31 _public member_ `EMotionExtractor_MotionType MotionType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Type of motion to extract
- L35 _public member_ `EMotionExtractor_Axis Axis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Axis to get the value from
- L41 _public member_ `bool bRemoveCurveOnRevert;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Whether we want to remove the curve when we revert or re-apply modifier Disabling this allows you to modify settings and create a new curve each time you re-apply the modifier Enabling this is the preferred setting when using a modifier that's applied in bulk and you may want to remove/rename curves
- L45 _public member_ `bool bRelativeToFirstFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Whether to extract the bone transforms relative to the first frame in the animation
- L49 _public member_ `EMotionExtractor_Space Space;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Reference frame/space to use when extracting the bone pose.
- L53 _public member_ `bool bComponentSpace_DEPRECATED;` — `UPROPERTY()` — Whether to extract the bone pose in component space or local space.
- L57 _public member_ `bool bAbsoluteValue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Whether to convert the final value to absolute (positive)
- L61 _public member_ `EMotionExtractor_MathOperation MathOperation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Optional math operation to apply on the extracted value before add it to the generated curve
- L65 _public member_ `float Modifier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (EditCondition = "MathOperation != EMotionExtractor_MathOperation::None"))` — Right operand for the math operation selected
- L69 _public member_ `bool bNormalize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Whether we want a normalized value (0 - 1)
- L73 _public member_ `int32 SampleRate;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "1"))` — Rate used to sample the animation
- L77 _public member_ `bool bUseCustomCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Whether we want to specify a custom name for the curve. If false, the name of the curve will be auto generated based on the data we are going to extract
- L81 _public member_ `FName CustomCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (EditCondition = "bUseCustomCurveName"))` — Custom name for the curve we are going to generate.
- L83 _public prototype_ `UMotionExtractorModifier();`
- L85 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`
- L86 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* Animation) override;`
- L89 _public prototype_ `FName GetCurveName() const;` — Returns the name for the curve. If CurveName is None it generates a name based on the data we are going to extract
- L92 _public prototype_ `float GetDesiredValue(const FTransform& BoneTransform, const FTransform& LastBoneTransform, float DeltaTime) const;` — Returns the desired value from the extracted poses
- L94 _public prototype_ `virtual void PostLoad() override;`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/MotionExtractorTypes.h` (Public)


#### enum `EMotionExtractor_MotionType`  
`enum class EMotionExtractor_MotionType : uint8`  
_L11-19_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Type of motion to extract
- L13 _public enumerator_ `None = 0 UMETA(Hidden)`
- L14 _public enumerator_ `Translation = 1 << 0`
- L15 _public enumerator_ `Rotation = 1 << 1`
- L16 _public enumerator_ `Scale = 1 << 2`
- L17 _public enumerator_ `TranslationSpeed = 1 << 3`
- L18 _public enumerator_ `RotationSpeed = 1 << 4`

#### enum `EMotionExtractor_Axis`  
`enum class EMotionExtractor_Axis : uint8`  
_L31-40_
- reflection: `UENUM(BlueprintType)`
- desc: Axis to get the final value from
- L33 _public enumerator_ `X`
- L34 _public enumerator_ `Y`
- L35 _public enumerator_ `Z`
- L36 _public enumerator_ `XY`
- L37 _public enumerator_ `XZ`
- L38 _public enumerator_ `YZ`
- L39 _public enumerator_ `XYZ`

#### enum `EMotionExtractor_Space`  
`enum class EMotionExtractor_Space : uint8`  
_L44-49_
- reflection: `UENUM(BlueprintType)`
- desc: Reference frame/space to use when calculating motion
- L46 _public enumerator_ `ComponentSpace`
- L47 _public enumerator_ `LocalSpace`
- L48 _public enumerator_ `RelativeToBone`

#### enum `EMotionExtractor_MathOperation`  
`enum class EMotionExtractor_MathOperation : uint8`  
_L53-60_
- reflection: `UENUM(BlueprintType)`
- desc: Math operations that can be applied to the extracted value before add it to the curve
- L55 _public enumerator_ `None`
- L56 _public enumerator_ `Addition`
- L57 _public enumerator_ `Subtraction`
- L58 _public enumerator_ `Division`
- L59 _public enumerator_ `Multiplication`

#### Free symbols / members of external scopes

- L20 _prototype_ `ENUM_CLASS_FLAGS(EMotionExtractor_MotionType);`
- L21 _function_ `constexpr bool EnumHasAnyFlags(int32 Flags, EMotionExtractor_MotionType Contains)`
- L22 _prototype_ `ENUM_RANGE_BY_VALUES(EMotionExtractor_MotionType, EMotionExtractor_MotionType::Translation, EMotionExtractor_MotionType::Rotation, EMotionExtractor_MotionType::Scale, EMotionExtractor_MotionType::TranslationSpeed, EMotionExtractor_MotionType::RotationSpeed);`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/MotionExtractorUtilities.h` (Public)


#### class `UMotionExtractorUtilityLibrary`  
`class UMotionExtractorUtilityLibrary : public UBlueprintFunctionLibrary`  
_L18-82_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="MotionExtractorUtilityLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L32 _public prototype_ `static FName GenerateCurveName( FName BoneName, EMotionExtractor_MotionType MotionType, EMotionExtractor_Axis Axis);` — `UFUNCTION(BlueprintCallable, Category = "Motion Extractor Utility")` — Generates a curve name based on input settings. @param BoneName			   The name of the bone @param MotionType            What type of motion this curve represents (translation, rotation, speed, etc.) @param Axis				   Which axis/axes the motion for this curve was extracted from
- L47 _public prototype_ `static float GetDesiredValue( const FTransform& BoneTransform, const FTransform& LastBoneTransform, float DeltaTime, EMotionExtractor_MotionType MotionType, EMotionExtractor_Axis Axis);` — `UFUNCTION(BlueprintCallable, Category = "Motion Extractor Utility")` — Returns the desired value from the extracted poses based on input settings. @param BoneTransform         Current frame's bone transform @param LastBoneTransform     Last frame's bone transform. Unused when not calculating speeds. @param DeltaTime			   Time step used between current and last bone transforms. Unused when not calculating speeds. @param MotionType            What type of motion to extract (translation, rotation, speed, etc.) @param Axis				   Which axis/axes to extract motion from
- L62 _public prototype_ `static TArray<FVector2D> GetStoppedRangesFromRootMotion(const UAnimSequence* AnimSequence, float StopSpeedThreshold = 10.0f, float SampleRate = 120.0f);` — `UFUNCTION(BlueprintCallable, Category = "Motion Extractor Utility")` — Returns the ranges (X/Start to Y/End) in the specified animation sequence where the animation is considered stopped. @param AnimSequence			Anim sequence to check @param StopSpeedThreshold		Root motion speed under which the animation is considered stopped. @param SampleRate				Sample rate of the animation. It's recommended to use high values if the animation has very sudden direction changes.
- L72 _public prototype_ `static TArray<FVector2D> GetMovingRangesFromRootMotion(const UAnimSequence* AnimSequence, float StopSpeedThreshold = 10.0f, float SampleRate = 120.0f);` — `UFUNCTION(BlueprintCallable, Category = "Motion Extractor Utility")` — Returns the ranges (X/Start to Y/End) in the specified animation sequence where the animation is considered moving. @param AnimSequence			Anim sequence to check @param StopSpeedThreshold		Root motion speed over which the animation is considered moving. @param SampleRate				Sample rate of the animation. It's recommended to use high values if the animation has very sudden direction changes.
- L78 _public prototype_ `static FTransform ExtractBoneTransform(UAnimSequence* Animation, const FBoneContainer& BoneContainer, FCompactPoseBoneIndex CompactPoseBoneIndex, float Time, bool bComponentSpace);` — Helper function to extract the pose for a given bone at a given time IMPORTANT: This function expects you to add a MemMark (FMemMark Mark(FMemStack::Get());) at the correct scope if you are using it from outside world's tick
- L81 _public prototype_ `static double CalculateMagnitude(const FVector& Vector, EMotionExtractor_Axis Axis);` — Helper function to calculate the magnitude of a vector only considering a specific axis or axes

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONMODIFIERLIBRARY_API`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/ReOrientRootBoneModifier.h` (Public)


#### class `UReOrientRootBoneModifier`  
`class UReOrientRootBoneModifier : public UAnimationModifier`  
_L10-29_
- reflection: `UCLASS()`
- inherits: `UAnimationModifier`
- desc: Reorient root bone in the animation while maintaining mesh position and rotation
- L18 _public member_ `FRotator Rotator;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — Rotation to apply to the root
- L20 _public prototype_ `UReOrientRootBoneModifier();`
- L22 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`
- L23 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* Animation) override;`
- L27 _private prototype_ `void ReOrientRootBone_Internal(UAnimSequence* Animation, const FQuat& Quat);`

### `Plugins/Animation/AnimationModifierLibrary/Source/AnimationModifierLibrary/Public/ZeroOutRootBoneModifier.h` (Public)


#### class `UZeroOutRootBoneModifier`  
`class UZeroOutRootBoneModifier : public UAnimationModifier`  
_L12-29_
- reflection: `UCLASS()`
- inherits: `UAnimationModifier`
- desc: Adjust root motion to be relative to the first frame. Optionally cut the start and end sections of the animation that don't have motion on the root. This was written to be used when capturing Character Movement motion via Take Recorder. Take Recorder outputs an animation captured from a character moving in game in world space, and this modifier zeroes out the root. The animation can then be exported to fbx to be animated against.
- L18 _public prototype_ `UZeroOutRootBoneModifier();`
- L20 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`
- L24 _public member_ `bool bClipStartFramesWithNoMotion = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — Clip frames at the start of the animation that have no root motion.
- L28 _public member_ `bool bClipEndFramesWithNoMotion = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")` — Clip frames at the end of the animation that have no root motion.
