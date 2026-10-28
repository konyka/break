# Plugins / BlendStack

- module root: `Plugins/Animation/BlendStack/Source/Runtime`
- headers: 7; symbols: 221
- symbol kinds: class=4, delegate=1, enum=1, enumerator=3, externvar=1, function=15, macro=4, member=71, namespace=6, prototype=105, struct=8, typedef=2
- PublicDependencyModuleNames: AnimGraphRuntime, AnimationCore, Core, CoreUObject, Engine

### `Plugins/Animation/BlendStack/Source/Runtime/Private/BlendStackAnimEventsFilterScope.h` (Private)


#### class `UE::Anim::FBlendStackAnimEventsFilterContext`  
`class FBlendStackAnimEventsFilterContext : public IAnimEventsFilterContext`  
_L12-25_
- inherits: `IAnimEventsFilterContext`
- L15 _public function_ `FBlendStackAnimEventsFilterContext()`
- L16 _public prototype_ `FBlendStackAnimEventsFilterContext(const TSharedRef<TArray<FName>> & InFiredNotifies, const TSharedRef<TMap<FName,float>>& InNotifyBanList);`
- L18 _public prototype_ `virtual bool ShouldFilterNotify(const FAnimNotifyEventReference& InNotifyEventRef) const override;`
- L22 _private member_ `TSharedRef<TArray<FName>> FiredNotifies;` — @todo: add inline allocator with some preallocated memory
- L24 _private member_ `TSharedRef<TMap<FName,float>> NotifyBanList;` — @todo: add inline allocator with some preallocated memory

#### class `UE::Anim::FBlendStackAnimEventsFilterScope`  
`class FBlendStackAnimEventsFilterScope : public IGraphMessage`  
_L27-42_
- inherits: `IGraphMessage`
- L29 _private prototype_ `DECLARE_ANIMGRAPH_MESSAGE(FBlendStackAnimEventsFilterScope);`
- L32 _public prototype_ `FBlendStackAnimEventsFilterScope(const TSharedRef<TArray<FName>> & InFiredNotifies, const TSharedRef<TMap<FName,float>> & InNotifyBanList);`
- L33 _public prototype_ `FBlendStackAnimEventsFilterScope(const TSharedPtr<TArray<FName>> & InFiredNotifies, const TSharedPtr<TMap<FName,float>> & InNotifyBanList);`
- L35 _public prototype_ `virtual TUniquePtr<const IAnimNotifyEventContextDataInterface> MakeUniqueEventContextData() const override;`
- L39 _private member_ `TSharedRef<TArray<FName>> FiredNotifies;` — @todo: add inline allocator with some preallocated memory
- L41 _private member_ `TSharedRef<TMap<FName,float>> NotifyBanList;` — @todo: add inline allocator with some preallocated memory

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Anim` (scope `UE`)

### `Plugins/Animation/BlendStack/Source/Runtime/Private/BlendedCurveUtils.h` (Private)


#### struct `UE::BlendStack::FBlendedCurveUtils`  
`struct FBlendedCurveUtils : FBlendedCurve`  
_L15-171_
- inherits: `FBlendedCurve`
- desc: Experimental, this feature might be removed without warning, not for production use Utils struct used to perform Curve blending with additiona fixes that have behavioral changes before integrating changes back to their original locations (look for code comments)
- L19 _public function_ `template<typename PredicateType> static void UnionEx(FBlendedCurve& BlendedCurve0, const FBlendedCurve& BlendedCurve1, PredicateType InPredicate)` — function adapted from UE::Anim::FNamedValueArrayUtils::Union, with additional bugfixes (read comments) that changes behaviors
- L167 _public prototype_ `static void LerpToEx(FBlendedCurve& InOutCurve, const FBlendedCurve& OtherCurve, float Alpha);` — function adapted from TBaseBlendedCurve::LerpTo, that uses UnionEx instead of UE::Anim::FNamedValueArrayUtils::Union
- L170 _public prototype_ `static void LerpToPerBoneEx(FBlendedCurve& InOutCurve, const FBlendedCurve& OtherCurve, const FBoneContainer& BoneContainer, TConstArrayView<float> OtherCurveBoneWeights);` — LerpToEx with per linked bone weighting blend

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace BlendStack` (scope `UE`)
- L11 _externvar_ `extern bool GVarUseBlendCurveFixes;` (scope `UE::BlendStack`) — Experimental, this feature might be removed without warning, not for production use

### `Plugins/Animation/BlendStack/Source/Runtime/Public/BlendStack/AnimNode_BlendStack.h` (Public)


#### enum `EBlendStack_BlendspaceUpdateMode`  
`enum class EBlendStack_BlendspaceUpdateMode : uint8`  
_L15-23_
- reflection: `UENUM()`
- L18 _public enumerator_ `InitialOnly` — Only update the blendspace xy inputs once on blend in.
- L20 _public enumerator_ `UpdateActiveOnly` — Update the active/most recent blendspace xy inputs every frame.
- L22 _public enumerator_ `UpdateAll` — Update all blendspaces xy inputs every frame.

#### struct `FBlendStackAnimPlayer`  
`struct FBlendStackAnimPlayer`  
_L26-134_
- reflection: `USTRUCT()`
- L31 _public prototype_ `void Initialize(const FAnimationInitializeContext& Context, UAnimationAsset* AnimationAsset, float AccumulatedTime, bool bLoop, bool bMirrored, UMirrorDataTable* MirrorDataTable, float BlendTime, const UBlendProfile* InBlendProfile, EAlphaBlendOption InBlendOption, const FVector& BlendParameters, float PlayRate, float ActivationDelay, int32 InPoseLinkIdx, FName GroupName, EAnimGroupRole::Type GroupRole, EAnimSyncMethod Method, bool bOverridePositionWhenJoiningSyncGroupAsLeader);`
- L35 _public prototype_ `void UpdatePlayRate(float PlayRate);`
- L36 _public prototype_ `void Evaluate_AnyThread(FPoseContext& Output);`
- L37 _public prototype_ `void Update_AnyThread(const FAnimationUpdateContext& Context);`
- L38 _public prototype_ `float GetAccumulatedTime() const;`
- L39 _public prototype_ `float GetCurrentAssetTime() const;`
- L40 _public prototype_ `float GetCurrentAssetLength() const;`
- L41 _public prototype_ `float GetPlayRate() const;`
- L43 _public prototype_ `float GetBlendInPercentage() const;`
- L45 _public prototype_ `int32 GetBlendInWeightsNum() const;`
- L47 _public prototype_ `void GetBlendInWeights(TArrayView<float> Weights) const;` — Important: this method fills weight array indexed with the full skeleton indices, not the compact pose!
- L48 _public prototype_ `float GetBlendInWeight() const;`
- L50 _public function_ `EAlphaBlendOption GetBlendOption() const`
- L51 _public prototype_ `UMirrorDataTable* GetMirrorDataTable() const;`
- L52 _public prototype_ `EAnimSyncMethod GetGroupMethod() const;`
- L53 _public prototype_ `FName GetGroupName() const;`
- L54 _public prototype_ `EAnimGroupRole::Type GetGroupRole() const;`
- L55 _public prototype_ `bool GetOverridePositionWhenJoiningSyncGroupAsLeader() const;`
- L56 _public prototype_ `const UBlendProfile* GetBlendProfile() const;`
- L58 _public prototype_ `void StorePoseContext(const FPoseContext& PoseContext);`
- L59 _public prototype_ `bool HasValidPoseContext() const;`
- L60 _public prototype_ `void MovePoseContextTo(FBlendStackAnimPlayer& Other);`
- L62 _public function_ `float GetTotalBlendInTime() const`
- L63 _public function_ `float GetCurrentBlendInTime() const`
- L64 _public function_ `float GetTimeToActivation() const`
- L66 _public prototype_ `void UpdateWithDeltaTime(float DeltaTime, int32 PlayerDepth, float PlayerDepthBlendInTimeMultiplier);`
- L67 _public function_ `bool GetMirror() const`
- L68 _public prototype_ `FVector GetBlendParameters() const;`
- L69 _public prototype_ `void SetBlendParameters(const FVector& BlendParameters);`
- L70 _public prototype_ `FString GetAnimationName() const;`
- L71 _public prototype_ `UAnimationAsset* GetAnimationAsset() const;`
- L73 _public function_ `FAnimNode_Mirror_Standalone& GetMirrorNode()`
- L74 _public function_ `int32 GetPoseLinkIndex() const`
- L76 _public prototype_ `void RestorePoseContext(FPoseContext& PoseContext) const;`
- L77 _public prototype_ `void UpdateSourceLinkNode();`
- L78 _public prototype_ `bool IsLooping() const;`
- L79 _public function_ `bool IsPostponed() const`
- L83 _public function_ `bool IsActive() const` — A sample being "Active" is relative to the active branch of the animation update context i.e. Active branches are NOT blending out.
- L85 _public prototype_ `FAnimNode_AssetPlayerBase* GetAssetPlayerNode();`
- L87 _public prototype_ `float GetSecondsFromEnd() const;`
- L90 _public prototype_ `FColor GetDebugColor() const;`
- L94 _public member_ `TBaseBlendedCurve<FDefaultAllocator, UE::Anim::FCurveElement> OverrideCurve;` — Curves to add to the pose after the player evaluates
- L99 _private member_ `FAnimNode_SequencePlayer_Standalone SequencePlayerNode;` — `UPROPERTY(Transient)` — Embedded standalone player to play sequence
- L103 _private member_ `FAnimNode_BlendSpacePlayer_Standalone BlendSpacePlayerNode;` — `UPROPERTY(Transient)` — Embedded standalone player to play blend spaces
- L107 _private member_ `FAnimNode_Mirror_Standalone MirrorNode;` — `UPROPERTY(Transient)` — Embedded mirror node to handle mirroring
- L113 _private member_ `TArray<FTransform> StoredBones;` — if SequencePlayerNode.GetSequence() and BlendSpacePlayerNode.GetBlendSpace() are nullptr, instead of using SequencePlayerNode or BlendSpacePlayerNode (wrapped in MirrorNode), the output FPoseContext will be from StoredBones, StoredCurve, StoredAttributes NoTe: we don't need a full FCompactHeapPose, since we use StoredBoneContainer to cache the bone container
- L114 _private member_ `FBlendedHeapCurve StoredCurve;`
- L115 _private member_ `UE::Anim::FMeshAttributeContainer StoredAttributes;`
- L117 _private member_ `FBoneContainer StoredBoneContainer;` — We need to store the bone container, in case we have a LOD swap during a blend that uses the stored pose.
- L119 _private member_ `EAlphaBlendOption BlendOption = EAlphaBlendOption::Linear;`
- L120 _private member_ `int32 PoseLinkIndex = INDEX_NONE;`
- L121 _private member_ `TCustomBoneIndexArray<float, FSkeletonPoseBoneIndex> TotalBlendInTimePerBone;`
- L124 _private member_ `TObjectPtr<const UBlendProfile> BlendProfile = nullptr;` — `UPROPERTY(Transient)`
- L126 _private member_ `float TotalBlendInTime = 0.f;`
- L127 _private member_ `float CurrentBlendInTime = 0.f;`
- L128 _private member_ `float TimeToActivation = 0.f;`
- L129 _private member_ `bool bIsActive = false;`
- L132 _private member_ `FColor DebugColor = FColor::Black;`

#### struct `UE::BlendStack::FBlendStack_SampleGraphExecutionHelper`  
`struct FBlendStack_SampleGraphExecutionHelper`  
_L138-146_
- L140 _public member_ `FBlendStackAnimPlayer* Player = nullptr;`
- L141 _public member_ `FGraphTraversalCounter CacheBoneCounter;`
- L143 _public prototype_ `void SetInputPosePlayer(FBlendStackAnimPlayer& InPlayer);`
- L144 _public prototype_ `void EvaluatePlayer(FPoseContext& Output, FBlendStackAnimPlayer& SamplePlayer, FPoseLink& SamplePoseLink);`
- L145 _public prototype_ `void ConditionalCacheBones(const FAnimationBaseContext& Output, FPoseLink& SamplePoseLink);`

#### struct `FAnimNode_BlendStack_Standalone`  
`struct FAnimNode_BlendStack_Standalone : public FAnimNode_AssetPlayerBase`  
_L150-269_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_AssetPlayerBase`
- L154 _public member_ `TArray<UE::BlendStack::FBlendStack_SampleGraphExecutionHelper> SampleGraphExecutionHelpers;`
- L157 _public member_ `TArray<FPoseLink> PerSampleGraphPoseLinks;` — `UPROPERTY()`
- L159 _public member_ `int32 CurrentSamplePoseLink = -1;`
- L162 _public member_ `TArray<FBlendStackAnimPlayer> AnimPlayers;` — `UPROPERTY(Transient)`
- L166 _public member_ `bool bShouldFilterNotifies = false;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Flag that determines if any notifies from originating from an anim player samples should be filtered or not.
- L170 _public member_ `TObjectPtr<UObject> StitchDatabase;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stitch|Experimental", meta = (PinHiddenByDefault))` — database used to search for an animation stitch to use as blend
- L174 _public member_ `float StitchBlendTime = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stitch|Experimental", meta = (PinHiddenByDefault))` — blend time in seconds used to blend into and out from a stitch animation
- L179 _public member_ `float StitchBlendMaxCost = 100.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stitch|Experimental", meta = (PinHiddenByDefault))` — if the cost from searching StitchDatabase is above StitchBlendMaxCost, blend stack will perform a regular blend, and not using the returned stitch animation as blend
- L182 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;` — FAnimNode_Base interface
- L183 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L184 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L185 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L188 _public prototype_ `void BlendTo(const FAnimationUpdateContext& Context, UAnimationAsset* AnimationAsset, float AccumulatedTime = 0.f, bool bLoop = false, bool bMirrored = false, UMirrorDataTable* MirrorDataTable = nullptr, float BlendTime = 0.2f, const UBlendProfile* BlendProfile = nullptr, EAlphaBlendOption BlendOption = EAlphaBlendOption::Linear, bool bUseInertialBlend = false, FName InertialBlendNodeTag = NAME_None, const FVector& BlendParameters = FVector::Zero(), float PlayRate = 1.f, float ActivationDelay = 0.f, FName GroupName = NAME_None, EAnimGroupRole::Type GroupRole = EAnimGroupRole::CanBeLeader, EAnimSyncMethod Method = EAnimSyncMethod::DoNotSync, bool bOverridePositionWhenJoiningSyncGroupAsLeader = false, FName PrevGroupName = NAME_None, EAnimGroupRole::Type PrevGroupRole = EAnimGroupRole::CanBeLeader, EAnimSyncMethod PrevMethod = EAnimSyncMethod::DoNotSync);`
- L194 _public prototype_ `void UpdatePlayRate(float PlayRate);`
- L195 _public prototype_ `virtual void Reset();`
- L198 _public prototype_ `virtual UAnimationAsset* GetAnimAsset() const;` — FAnimNode_AssetPlayerBase interface
- L199 _public prototype_ `virtual float GetAccumulatedTime() const override;`
- L200 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L201 _public prototype_ `virtual float GetCurrentAssetTime() const override;`
- L202 _public prototype_ `virtual float GetCurrentAssetLength() const override;`
- L205 _public prototype_ `bool GetMirror() const;`
- L206 _public prototype_ `FVector GetBlendParameters() const;`
- L208 _public prototype_ `int32 GetNextPoseLinkIndex();`
- L210 _public function_ `int32 GetMaxActiveBlends() const`
- L211 _public function_ `void SetMaxActiveBlends(int32 InMaxActiveBlends)`
- L214 _public prototype_ `bool AnyNewBlendToThisFrame() const;` — Experimental, this feature might be removed without warning, not for production use
- L217 _protected prototype_ `void InternalBlendTo(const FAnimationUpdateContext& Context, UAnimationAsset* AnimationAsset, float AccumulatedTime, bool bLoop, bool bMirrored, UMirrorDataTable* MirrorDataTable, float BlendTime, const UBlendProfile* BlendProfile, EAlphaBlendOption BlendOption, bool bUseInertialBlend, FName InertialBlendNodeTag, const FVector& BlendParameters, float PlayRate, float ActivationDelay, FName GroupName, EAnimGroupRole::Type GroupRole, EAnimSyncMethod GroupMethod, bool bOverridePositionWhenJoiningSyncGroupAsLeader, FName PrevGroupName, EAnimGroupRole::Type PrevGroupRole, EAnimSyncMethod PrevGroupMethod);`
- L225 _protected prototype_ `void UpdateBlendspaceParameters(const EBlendStack_BlendspaceUpdateMode UpdateMode, const FVector& BlendParameters);` — Call this to update current blendspace player xy blend parameters. By default, we only update them on initial BlendTo.
- L227 _protected prototype_ `static void BlendWithPose(FAnimationPoseData& InOutPoseData, const FAnimationPoseData& OtherPoseData, const float InOutPoseWeight);`
- L228 _protected prototype_ `static void BlendWithPosePerBone(FAnimationPoseData& InOutPoseData, const FAnimationPoseData& OtherPoseData, TConstArrayView<float> OtherPoseWeights);`
- L232 _protected member_ `int32 MaxActiveBlends = 4;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0"))` — Number of max active blending animation in the blend stack. If MaxActiveBlends is zero then blend stack is disabled
- L238 _protected member_ `bool bStoreBlendedPose = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — if the number of requested blends is higher than MaxActiveBlends, blend stack will blend and accumulate into a stored pose all the overflowing animations. if bStoreBlendedPose is false, the memory to store the pose will be saved, but once reached the MaxActiveBlends, blendstack will start discarding animations, potentially resulting in animation pops
- L240 _protected member_ `TSharedPtr<TArray<FName>> NotifiesFiredLastTick;`
- L241 _protected member_ `TSharedPtr<TMap<FName,float>> NotifyRecencyMap;`
- L245 _protected member_ `float NotifyRecencyTimeOut = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0", PinHiddenByDefault))` — Window of time after firing a notify that any instance of the same notify will be filtered out.
- L250 _protected member_ `float MaxBlendInTimeToOverrideAnimation = 0.f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — if the most relevant (recently added) animation is within MaxBlendInTimeToOverrideAnimation, the new requested blend will take its spot otherwise a new blended will be added to the stack
- L254 _protected member_ `float PlayerDepthBlendInTimeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — AnimPlayers blend in timer will be incremented PlayerDepthBlendInTimeMultiplier times faster on a deeper blend
- L257 _private prototype_ `bool StitchTo(const FAnimationUpdateContext& Context, UAnimationAsset* AnimationAsset, float AccumulatedTime, bool bLoop, bool bMirrored, UMirrorDataTable* MirrorDataTable, float BlendTime, const UBlendProfile* BlendProfile, EAlphaBlendOption BlendOption, bool bUseInertialBlend, FName InertialBlendNodeTag, const FVector& BlendParameters, float PlayRate, float ActivationDelay);`
- L261 _private prototype_ `void PopLastAnimPlayer();`
- L262 _private prototype_ `void InitializeSample(const FAnimationInitializeContext& Context, FBlendStackAnimPlayer& SamplePlayer);`
- L263 _private prototype_ `bool EvaluateSample(FPoseContext& Output, const int32 PlayerIndex);`
- L264 _private prototype_ `void UpdateSample(const FAnimationUpdateContext& Context, const int32 PlayerIndex);`
- L265 _private prototype_ `void CacheBonesForSample(const FAnimationCacheBonesContext& Context, const int32 PlayerIndex);`
- L266 _private prototype_ `bool IsSampleGraphAvailableForPlayer(const int32 PlayerIndex);`
- L268 _private member_ `uint64 LastBlendToFrameCounter = 0;`

#### struct `FAnimNode_BlendStack`  
`struct FAnimNode_BlendStack : public FAnimNode_BlendStack_Standalone`  
_L272-412_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendStack_Standalone`
- L278 _public member_ `TObjectPtr<UAnimationAsset> AnimationAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — requested animation to play
- L282 _public member_ `float AnimationTime = -1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — requested animation time
- L287 _public member_ `float ActivationDelayTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — delay in seconds before activating AnimationAsset playing from AnimationTime assets queued with an ActivationDelayTime will be discarded when a new blend gets requested
- L291 _public member_ `bool bLoop = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — requested AnimationAsset looping
- L295 _public member_ `bool bMirrored = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — requested AnimationAsset mirroring
- L299 _public member_ `float WantedPlayRate = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — requested animation play rate
- L303 _public member_ `float BlendTime = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault, ClampMin = "0"))` — tunable animation transition blend time
- L308 _public member_ `float MaxAnimationDeltaTime = -1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — if MaxAnimationDeltaTime is positive and the currently playing animation accumulated time differs more than MaxAnimationDeltaTime from AnimationTime (animation desynchronized from the requested time) this blend stack will force a blend into the same animation
- L311 _public member_ `TObjectPtr<UBlendProfile> BlendProfile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault, UseAsBlendProfile = true))`
- L314 _public member_ `EAlphaBlendOption BlendOption = UE::Anim::DefaultBlendOption;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))`
- L318 _public member_ `EBlendStack_BlendspaceUpdateMode BlendspaceUpdateMode = EBlendStack_BlendspaceUpdateMode::InitialOnly;` — `UPROPERTY(EditAnywhere, Category = Blendspace)` — How we should update individual blend space parameters. See dropdown options tooltips.
- L322 _public member_ `FVector BlendParameters = FVector::Zero();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blendspace, meta = (PinHiddenByDefault))` — requested blend space blend parameters (if AnimationAsset is a blend space)
- L326 _public member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — if set and bMirrored MirrorDataTable will be used for mirroring the aniamtion
- L331 _public member_ `float BlendParametersDeltaThreshold = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Blendspace)` — Use this to define a threshold to trigger a new blend when blendspace xy input pins change. By default, any delta will trigger a blend.
- L336 _public member_ `bool bForceBlendTo = false;` — `UPROPERTY(Experimental, EditAnywhere, BlueprintReadWrite, Category = "Experimental", meta = (PinHiddenByDefault))` — in case there're no blend to the current frame, this blend stack will force a blend to into the currently playing animation. useful to blend into the same animation in case this blendstack synch properties are set to be a follower
- L340 _public member_ `bool bUseInertialBlend = false;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Enable to use inertial blending
- L344 _public member_ `FName InertialBlendNodeTag = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Tag to force a specific inertialization / dead blending node to process inertial blend requests coming from this blend stack
- L348 _public member_ `bool bResetOnBecomingRelevant = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Reset the blend stack if it has become relevant to the graph after not being updated on previous frames.
- L355 _public member_ `FName GroupName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The group name that we synchronize with (NAME_None if it is not part of any group). Note that this is the name of the group used to sync the output of this node - it will not force syncing of animations contained by it.
- L359 _public member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The role this node (and main AnimPlayer - most recent animation set via BlendTo) can assume within the group (ignored if GroupName is not set)
- L363 _public member_ `EAnimSyncMethod Method = EAnimSyncMethod::DoNotSync;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — How this node main AnimPlayer will synchronize with other animations
- L367 _public member_ `FName PrevGroupName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The role set to the most relevant non main AnimPlayer (previous main AnimPlayer)
- L371 _public member_ `TEnumAsByte<EAnimGroupRole::Type> PrevGroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The group set to the most relevant non main AnimPlayer (previous main AnimPlayer)
- L375 _public member_ `EAnimSyncMethod PrevMethod = EAnimSyncMethod::DoNotSync;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The method set to the most relevant non main AnimPlayer (previous main AnimPlayer)
- L379 _public member_ `bool bIgnoreForRelevancyTest = false;` — `UPROPERTY(EditAnywhere, Category = Relevancy, meta = (FoldProperty, PinHiddenByDefault))` — If true, "Relevant anim" nodes that look for the highest weighted animation in a state will ignore this node
- L383 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;` — FAnimNode_Base interface
- L384 _public prototype_ `virtual FName GetGroupName() const override;`
- L385 _public prototype_ `virtual EAnimGroupRole::Type GetGroupRole() const override;`
- L386 _public prototype_ `virtual EAnimSyncMethod GetGroupMethod() const override;`
- L388 _public prototype_ `FName GetPrevGroupName() const;`
- L389 _public prototype_ `EAnimGroupRole::Type GetPrevGroupRole() const;`
- L390 _public prototype_ `EAnimSyncMethod GetPrevGroupMethod() const;`
- L392 _public prototype_ `virtual bool GetIgnoreForRelevancyTest() const override;`
- L393 _public prototype_ `virtual bool IsLooping() const override;`
- L394 _public prototype_ `virtual bool SetGroupName(FName InGroupName) override;`
- L395 _public prototype_ `virtual bool SetGroupRole(EAnimGroupRole::Type InRole) override;`
- L396 _public prototype_ `virtual bool SetGroupMethod(EAnimSyncMethod InMethod) override;`
- L397 _public prototype_ `virtual bool SetIgnoreForRelevancyTest(bool bInIgnoreForRelevancyTest) override;`
- L401 _public prototype_ `void ForceBlendNextUpdate();` — Force a blend on the next update, even if the anim sequence has not changed.
- L402 _public prototype_ `virtual void Reset() override;`
- L405 _protected prototype_ `bool NeedsReset(const FAnimationUpdateContext& Context) const;`
- L406 _protected prototype_ `bool ConditionalBlendTo(const FAnimationUpdateContext& Context);`
- L409 _protected member_ `FGraphTraversalCounter UpdateCounter;` — Update Counter for detecting being relevant
- L411 _protected member_ `bool bForceBlendNextUpdate = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API BLENDSTACK_API`
- L136 _namespace_ `namespace UE`
- L136 _namespace_ `namespace BlendStack` (scope `UE`)

### `Plugins/Animation/BlendStack/Source/Runtime/Public/BlendStack/AnimNode_BlendStackInput.h` (Public)


#### struct `FAnimNode_BlendStackInput`  
`struct FAnimNode_BlendStackInput : public FAnimNode_Base`  
_L14-39_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Input pose that links the blend stack's sample graph with the sample/pose chosen by the blend stack. @Todo: It might be better to reuse FAnimNode_LinkedInputPose, since we will most likely need variable input pins in the future too.
- L20 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L21 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L24 _public member_ `int32 SampleIndex = INDEX_NONE;` — `UPROPERTY()`
- L27 _public member_ `int32 BlendStackAllocationIndex = INDEX_NONE;` — `UPROPERTY()`
- L31 _public member_ `bool bOverridePlayRate = false;` — `UPROPERTY(EditAnywhere, Category=Settings, meta = (NeverAsPin))` — If true, the PlayRate input from thos node will override the SequencePlayer or BlendSpacePlayer playrate each frame
- L35 _public member_ `float PlayRate = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — The play rate multiplier. Can be negative, which will cause the animation to play in reverse.
- L38 _public member_ `struct FBlendStackAnimPlayer** Player;` — The player is guaranteed to be valid for the whole duration of update/eval.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BLENDSTACK_API`

### `Plugins/Animation/BlendStack/Source/Runtime/Public/BlendStack/BlendStackAnimNodeLibrary.h` (Public)


#### struct `FBlendStackAnimNodeReference`  
`struct FBlendStackAnimNodeReference : public FAnimNodeReference`  
_L17-22_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L21 _public typedef_ `typedef FAnimNode_BlendStack FInternalNodeType;`

#### class `UBlendStackAnimNodeLibrary`  
`class UBlendStackAnimNodeLibrary : public UBlueprintFunctionLibrary`  
_L26-106_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations that can be run on a Blend Stack node via Anim Node Functions such as "On Become Relevant" and "On Update".
- L33 _public prototype_ `static FBlendStackAnimNodeReference ConvertToBlendStackNode(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a blend stack node context from an anim node context
- L37 _public prototype_ `static UAnimationAsset* GetCurrentBlendStackAnimAsset(const FAnimNodeReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))` — Get the current AnimationAsset that is playing from a Blend Stack Input node
- L41 _public prototype_ `static float GetCurrentBlendStackAnimAssetTime(const FAnimNodeReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))` — Get the current elapsed time of the animation that is playing from a Blend Stack Input node
- L45 _public prototype_ `static bool GetCurrentBlendStackAnimIsActive(const FAnimNodeReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))` — Get if current anim is active
- L49 _public prototype_ `static bool GetCurrentBlendStackAnimAssetMirrored(const FAnimNodeReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))` — Get if we are currently mirrored from a Blend Stack Input node
- L53 _public prototype_ `static UMirrorDataTable* GetCurrentBlendStackAnimAssetMirrorTable(const FAnimNodeReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))` — Get current AssetMirrorTable from a Blend Stack Input node
- L57 _public function_ `static void ConvertToBlendStackNodePure(const FAnimNodeReference& Node, FBlendStackAnimNodeReference& BlendStackNode, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe, DisplayName = "Convert to Blend Stack Node"))` — Get a blend stack node context from an anim node context (pure)
- L65 _public prototype_ `static void ForceBlendNextUpdate(const FBlendStackAnimNodeReference& BlendStackNode);` — `UFUNCTION(BlueprintCallable, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe, DisplayName = "Force Blend On Next Update"))`
- L68 _public prototype_ `static void BlendTo(const FAnimUpdateContext& Context, const FBlendStackAnimNodeReference& BlendStackNode, UAnimationAsset* AnimationAsset = nullptr, float AnimationTime = 0.f, bool bLoop = false, bool bMirrored = false, float BlendTime = 0.2f, FVector BlendParameters = FVector::ZeroVector, float WantedPlayRate = 1.f, float ActivationDelay = 0.f);` — `UFUNCTION(BlueprintCallable, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe, DisplayName = "Blend To"))`
- L81 _public prototype_ `static void BlendToWithSettings(const FAnimUpdateContext& Context, const FBlendStackAnimNodeReference& BlendStackNode, UAnimationAsset* AnimationAsset = nullptr, float AnimationTime = 0.f, bool bLoop = false, bool bMirrored = false, float BlendTime = 0.2f, UBlendProfile* BlendProfile = nullptr, EAlphaBlendOption BlendOption = EAlphaBlendOption::HermiteCubic, bool bInertialBlend = false, FVector BlendParameters = FVector::ZeroVector, float WantedPlayRate = 1.f, float ActivationDelay = 0.f);` — `UFUNCTION(BlueprintCallable, Category = "Animation|BlendStack|Experimental", meta = (BlueprintThreadSafe, DisplayName = "Blend To"))` — Note: Experimental and subject to change!
- L96 _public prototype_ `static UAnimationAsset* GetCurrentAsset(const FBlendStackAnimNodeReference& BlendStackNode);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))`
- L99 _public prototype_ `static float GetCurrentAssetTime(const FBlendStackAnimNodeReference& BlendStackNode);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))`
- L102 _public prototype_ `static float GetCurrentAssetTimeRemaining(const FBlendStackAnimNodeReference& BlendStackNode);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))`
- L105 _public prototype_ `static bool IsCurrentAssetLooping(const FBlendStackAnimNodeReference& BlendStackNode);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API BLENDSTACK_API`

### `Plugins/Animation/BlendStack/Source/Runtime/Public/BlendStack/BlendStackDefines.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlendStack, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlendStack, Log, All);`

### `Plugins/Animation/BlendStack/Source/Runtime/Public/BlendStack/BlendStackInputAnimNodeLibrary.h` (Public)


#### struct `FBlendStackInputAnimNodeReference`  
`struct FBlendStackInputAnimNodeReference : public FAnimNodeReference`  
_L15-20_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L19 _public typedef_ `typedef FAnimNode_BlendStackInput FInternalNodeType;`

#### class `UBlendStackInputAnimNodeLibrary`  
`class UBlendStackInputAnimNodeLibrary : public UBlueprintFunctionLibrary`  
_L24-44_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations that can be run on a Blend Stack node via Anim Node Functions such as "On Become Relevant" and "On Update".
- L31 _public prototype_ `static FBlendStackInputAnimNodeReference ConvertToBlendStackInputNode(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a blend stack input node context from an anim node context
- L35 _public function_ `static void ConvertToBlendStackInputNodePure(const FAnimNodeReference& Node, FBlendStackInputAnimNodeReference& BlendStackInputNode, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe, DisplayName = "Convert to Blend Stack Input Node"))` — Get a blend stack input node context from an anim node context (pure)
- L43 _public prototype_ `static void GetProperties(const FBlendStackInputAnimNodeReference& BlendStackInputNode, UAnimationAsset*& AnimationAsset, float& AccumulatedTime);` — `UFUNCTION(BlueprintCallable, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BLENDSTACK_API`
