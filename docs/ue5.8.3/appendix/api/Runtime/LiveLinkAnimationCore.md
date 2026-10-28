# Runtime / LiveLinkAnimationCore

- module root: `Source/Runtime/LiveLinkAnimationCore`
- headers: 4; symbols: 61
- symbol kinds: class=3, enum=1, enumerator=1, function=10, member=15, prototype=28, struct=3
- PublicDependencyModuleNames: Core, CoreUObject, Engine, LiveLinkInterface

### `Source/Runtime/LiveLinkAnimationCore/Public/AnimNode_LiveLinkPose.h` (Public)


#### struct `FAnimNode_LiveLinkPose`  
`struct FAnimNode_LiveLinkPose : public FAnimNode_Base`  
_L23-86_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L29 _public member_ `FPoseLink InputPose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)`
- L32 _public member_ `FLiveLinkSubjectName LiveLinkSubjectName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SourceData, meta = (PinShownByDefault))`
- L35 _public member_ `bool bDoLiveLinkEvaluation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = SourceData, meta = (PinShownByDefault))`
- L40 _public member_ `FName SubjectName_DEPRECATED;` — `UE_DEPRECATED(4.23, "FName SubjectName is deprecated. Use the SubjectName of type FLiveLinkSubjectName instead.")` — `UPROPERTY()`
- L44 _public member_ `TSubclassOf<ULiveLinkRetargetAsset> RetargetAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, NoClear, Category = Retarget, meta = (NeverAsPin))`
- L47 _public member_ `TObjectPtr<ULiveLinkRetargetAsset> CurrentRetargetAsset;` — `UPROPERTY(transient)`
- L50 _public prototype_ `FAnimNode_LiveLinkPose();`
- L53 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L54 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext & Context) override;`
- L55 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext & Context) override;`
- L56 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L57 _public function_ `virtual bool HasPreUpdate() const`
- L58 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L59 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L62 _public prototype_ `bool Serialize(FArchive& Ar);`
- L65 _protected prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;`
- L68 _protected prototype_ `void BuildPoseFromAnimData(const FLiveLinkSubjectFrameData& LiveLinkData, FPoseContext& Output);` — Build output pose using evaluated LiveLink animation data
- L71 _protected prototype_ `void BuildPoseFromCurveData(const FLiveLinkSubjectFrameData& LiveLinkData, FPoseContext& Output);` — Build output pose using evaluated LiveLink curve (Basic Role) data
- L76 _private member_ `ILiveLinkClient* LiveLinkClient_AnyThread;`
- L79 _private member_ `float CachedDeltaTime;` — Delta time from update so that it can be passed to retargeter
- L82 _private member_ `TSharedPtr<FLiveLinkSubjectFrameData> CachedLiveLinkData;` — Cached LiveLink evaluated data from last frame
- L85 _private member_ `TSubclassOf<ULiveLinkRole> CachedEvaluatedRole;` — Cached LiveLink Role evaluated last frame

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_LiveLinkPose> : public TStructOpsTypeTraitsBase2<FAnimNode_LiveLinkPose>`  
_L91-97_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_LiveLinkPose>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L94-96_

#### Free symbols / members of external scopes

- L95 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anone93b0ba20103`)

### `Source/Runtime/LiveLinkAnimationCore/Public/LiveLinkInstance.h` (Public)


#### struct `FLiveLinkInstanceProxy`  
`struct FLiveLinkInstanceProxy : public FAnimInstanceProxy`  
_L15-38_
- reflection: `USTRUCT()`
- inherits: `FAnimInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L22 _public function_ `FLiveLinkInstanceProxy()`
- L26 _public function_ `FLiveLinkInstanceProxy(UAnimInstance* InAnimInstance) : FAnimInstanceProxy(InAnimInstance)`
- L31 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;`
- L32 _public prototype_ `virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;`
- L33 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L34 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L37 _public member_ `FAnimNode_LiveLinkPose PoseNode;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### class `ULiveLinkInstance`  
`class ULiveLinkInstance : public UAnimInstance`  
_L41-79_
- reflection: `UCLASS(transient, NotBlueprintable, MinimalAPI)`
- inherits: `UAnimInstance`
- L48 _public function_ `void SetSubject(FLiveLinkSubjectName SubjectName)` — `UFUNCTION(BlueprintCallable, Category="Animation|Live Link")`
- L54 _public function_ `void SetRetargetAsset(TSubclassOf<ULiveLinkRetargetAsset> RetargetAsset)` — `UFUNCTION(BlueprintCallable, Category = "Animation|Live Link")`
- L60 _public function_ `void EnableLiveLinkEvaluation(bool bDoEnable)` — `UFUNCTION(BlueprintCallable, Category = "Animation|Live Link")`
- L65 _public function_ `bool GetEnableLiveLinkEvaluation()`
- L71 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`
- L72 _protected prototype_ `virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;`
- L76 _protected member_ `TObjectPtr<ULiveLinkRetargetAsset> CurrentRetargetAsset;` — `UPROPERTY(transient)` — Cache for GC

### `Source/Runtime/LiveLinkAnimationCore/Public/LiveLinkRemapAsset.h` (Public)


#### class `ULiveLinkRemapAsset`  
`class ULiveLinkRemapAsset : public ULiveLinkRetargetAsset`  
_L26-69_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `ULiveLinkRetargetAsset`
- desc: Remap asset for data coming from Live Link. Allows simple application of bone transforms into current pose based on name remapping only
- L30 _private prototype_ `virtual ~ULiveLinkRemapAsset() = default;`
- L33 _private prototype_ `virtual void BeginDestroy() override;`
- L37 _private prototype_ `virtual void BuildPoseFromAnimationData(float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose) override;`
- L38 _private prototype_ `virtual void BuildPoseAndCurveFromBaseData(float DeltaTime, const FLiveLinkBaseStaticData* InBaseStaticData, const FLiveLinkBaseFrameData* InBaseFrameData, FCompactPose& OutPose, FBlendedCurve& OutCurve) override;`
- L43 _private prototype_ `FName GetRemappedBoneName(FName BoneName) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Live Link Remap")` — Blueprint Implementable function for getting a remapped bone name from the original
- L47 _private prototype_ `FName GetRemappedCurveName(FName CurveName) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Live Link Remap")` — Blueprint Implementable function for getting a remapped curve name from the original
- L51 _private prototype_ `void RemapCurveElements(UPARAM(ref)TMap<FName, float>& CurveItems) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Live Link Remap")` — Blueprint Implementable function for remapping, adding or otherwise modifying the curve element data from Live Link. This is run after GetRemappedCurveName
- L55 _private prototype_ `void OnBlueprintClassCompiled(UBlueprint* TargetBlueprint);`
- L59 _private member_ `TMap<FName, FName> BoneNameMap;` — Name mapping between source bone name and transformed bone name (returned from GetRemappedBoneName)
- L63 _private member_ `TMap<FName, FName> CurveNameMap;` — Name mapping between source curve name and transformed curve name (returned from GetRemappedCurveName)
- L67 _private member_ `FDelegateHandle OnBlueprintCompiledDelegate;` — Blueprint.OnCompiled delegate handle

### `Source/Runtime/LiveLinkAnimationCore/Public/LiveLinkRetargetAsset.h` (Public)


#### class `ULiveLinkRetargetAsset`  
`class ULiveLinkRetargetAsset : public UObject`  
_L24-45_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for retargeting live link data.
- L29 _private prototype_ `void ApplyCurveValue(const USkeleton* Skeleton, const FName CurveName, const float CurveValue, FBlendedCurve& OutCurve) const;` — Takes the supplied curve name and value and applies it to the blended curve (as approriate given the supplied skeleton
- L32 _private prototype_ `void BuildCurveData(const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, const FCompactPose& InPose, FBlendedCurve& OutCurve) const;` — Builds curve data into OutCurve from the supplied live link frame
- L35 _private prototype_ `void BuildCurveData(const TMap<FName, float>& CurveMap, const FCompactPose& InPose, FBlendedCurve& OutCurve) const;` — Builds curve data into OutCurve from the supplied map of curve name to float
- L38 _private function_ `virtual void Initialize()` — Called once when the retargeter is created
- L41 _private function_ `virtual void BuildPoseFromAnimationData(float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose)` — Build OutPose from AnimationData if subject was from this type
- L44 _private function_ `virtual void BuildPoseAndCurveFromBaseData(float DeltaTime, const FLiveLinkBaseStaticData* InBaseStaticData, const FLiveLinkBaseFrameData* InBaseFrameData, FCompactPose& OutPose, FBlendedCurve& OutCurve)` — Build OutPose and OutCurve from the basic data. Called for every type of subjects
