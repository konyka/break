# Plugins / RelativeBodyAnimInfo

- module root: `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimInfo`
- headers: 2; symbols: 33
- symbol kinds: class=5, function=4, macro=1, member=18, prototype=5
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine
- PublicDependencyModuleNames: 

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimInfo/Public/RelativeBodyAnimInfoModule.h` (Public)


#### class `FRelativeBodyAnimInfoModule`  
`class FRelativeBodyAnimInfoModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimInfo/Public/RelativeBodyAnimNotifies.h` (Public)


#### class `URelativeBodyAnimNotifyBase`  
`class URelativeBodyAnimNotifyBase : public UAnimNotify`  
_L15-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimNotify`
- desc: Base class to limit options for notify class types in RelativeBodyAnimModifier

#### class `URelativeBodyBakeAnimNotify`  
`class URelativeBodyBakeAnimNotify : public URelativeBodyAnimNotifyBase`  
_L25-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URelativeBodyAnimNotifyBase`
- desc: Baked relative body anim-notify storing all body relationships in single notify at anim start
- L44 _public prototype_ `void OnRelativeBodyDenseNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, int NumSamplesIn, const TMap<FName,FTransform> &OffsetTransformsForBonesIn, const TArray<FName> &BodyPairsIn, const TArray<float> &BodyPairsSampleTimeIn, const TArray<FVector3f> &BodyPairsLocalReferenceIn, const TArray<bool> &BodyPairsIsParentDominatesIn) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Animation")` — OnRelativeBodyDenseNotify interface for contact pair info @param MeshComp The source SkeletalMeshComponent @param Animation The current animation @param NumSamplesIn The number of samples in baked data @param BodyPairsIn Array of body pairs @param BodyPairsSampleTimeIn Array of sample times @param BodyPairsLocalReferenceIn Array of per-body (pair), per-sample, local reference positions of closest body verts @param BodyPairsIsParentDominatesIn Array indicating if parent body should be allowed to move (one entery per-body-pair)
- L46 _public function_ `virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override`
- L53 _public member_ `int NumSamples = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L56 _public member_ `TMap<FName,FTransform> OffsetTransformsForBones;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L59 _public member_ `TArray<FName> BodyPairs;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L62 _public member_ `TArray<float> BodyPairsSampleTime;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L65 _public member_ `TArray<FVector3f> BodyPairsLocalReference;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L68 _public member_ `TArray<bool> bBodyPairsIsParentDominates;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`

#### class `URelativeBodyPerFrameAnimNotify`  
`class URelativeBodyPerFrameAnimNotify : public URelativeBodyAnimNotifyBase`  
_L75-138_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "RelativeBodyPerFrameAnimNotify"))`
- inherits: `URelativeBodyAnimNotifyBase`
- desc: Per frame body relationships notify (generates a very large amount of data)
- L81 _public function_ `void SetInfo(USkeletalMesh* SkeletalMeshAsset_, FName body1_, FName body2_, FVector3f &loc1_, FVector3f &loc2_, bool IsParentDominates_)` — TODO: Should the mesh be switched to physics asset and pass override if available?
- L101 _public prototype_ `void OnRelativeBodyAnimNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, USkeletalMesh* SkeletalMesh, FName Body1, FName Body2, const FVector3f &Loc1, const FVector3f &Loc2, bool IsParentDominates) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Animation")` — OnRelativeBodyAnimNotify interface for contact pair info @param SkeletalMesh The source SkeletalMesh contains the PhysicsAsset information @param Body1 The domain body of this contact pair @param Body2 The contact body of this contact pair @param Loc1 The local reference position of contact point in the domain body @param Loc2 The local reference position of contact point in the contact body
- L114 _public function_ `virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override`
- L122 _protected member_ `TObjectPtr<USkeletalMesh> SkeletalMeshAsset;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L125 _protected member_ `FName body1;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L128 _protected member_ `FName body2;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L131 _protected member_ `FVector3f loc1;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L134 _protected member_ `FVector3f loc2;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L137 _protected member_ `bool bIsParentDominates;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`

#### class `URelativePropsBakeAnimNotify`  
`class URelativePropsBakeAnimNotify : public URelativeBodyAnimNotifyBase`  
_L145-189_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URelativeBodyAnimNotifyBase`
- desc: Baked relative props anim-notify storing all props relationships in single notify at anim start
- L164 _public prototype_ `void OnRelativePropsDenseNotify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, int NumSamplesIn, const TMap<FName,FTransform> &OffsetTransformsForBonesIn, const TArray<FName>& PropsPairsIn, const TArray<float>& PropsPairsSampleTimeIn, const TArray<FVector3f>& PropsPairsLocalReferenceIn) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Animation")` — OnRelativeBodyDenseNotify interface for contact pair info @param MeshComp The source SkeletalMeshComponent @param Animation The current animation @param NumSamplesIn The number of samples in baked data @param BodyPairsIn Array of body pairs @param BodyPairsSampleTimeIn Array of sample times @param BodyPairsLocalReferenceIn Array of per-body (pair), per-sample, local reference positions of closest body verts @param BodyPairsIsParentDominatesIn Array indicating if parent body should be allowed to move (one entery per-body-pair)
- L166 _public function_ `virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override`
- L173 _public member_ `int NumSamples = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L176 _public member_ `TMap<FName,FTransform> OffsetTransformsForBones;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L179 _public member_ `TArray<FName> PropsPairs;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L182 _public member_ `TArray<float> PropsPairsSampleTime;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L185 _public member_ `TArray<FVector3f> PropsPairsLocalReference;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`
- L188 _public member_ `TArray<bool> bPropsPairsIsParentDominates;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Detail"))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RELATIVEBODYANIMINFO_API`
