# Plugins / RelativeBodyAnimUtils

- module root: `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimUtils`
- headers: 6; symbols: 82
- symbol kinds: class=5, member=41, prototype=30, struct=6
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationBlueprintLibrary, AnimationCore, AnimationModifiers, Core, CoreUObject, DynamicMesh, Engine, GeometryCore, IKRig, IKRigEditor, MeshConversion, MeshDescription, RelativeBodyAnimInfo, SkeletalMeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: 

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimUtils/Public/RelativeBodyAnimModifier.h` (Public)


#### struct `FRelativeBodySourceData`  
`struct FRelativeBodySourceData`  
_L18-39_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `TArray<int32> BodyIndicesParentBodyIndices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalIKRetargeter)` — The names of either controls of body modifiers (depending on context)
- L26 _public member_ `TArray<bool> BodyIndicesToIgnore;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalIKRetargeter)`
- L28 _public member_ `TArray<bool> IsDomainBody;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalIKRetargeter)`
- L31 _public member_ `TArray<FTransform> SourceRetargetGlobalPose;` — Source Data
- L32 _public member_ `TArray<TArray<int32>> SourceVertexIndicesInfluencedByBodyIndices;`
- L34 _public member_ `TArray<FVector3f> SourceVLocations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalIKRetargeter)`
- L36 _public member_ `TArray<int32> BodyIndicesToSourceBoneIndices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalIKRetargeter)`
- L38 _public member_ `TArray<int32> SourceBoneIndicesToBodyIndices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalIKRetargeter)`

#### class `URelativeBodyAnimModifier`  
`class URelativeBodyAnimModifier : public UAnimationModifier`  
_L45-97_
- reflection: `UCLASS(BlueprintType, meta = (IsBlueprintBase = true))`
- inherits: `UAnimationModifier`
- desc: Animation modifier for baking relative body relationships into anim notify
- L51 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* InAnimation) override;` — Begin UAnimationModifier interface
- L52 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* InAnimation) override;`
- L58 _public member_ `int SampleRate = 30;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (Units = "Hz", UIMin = 1))` — Rate used to sample the animation
- L62 _public member_ `float ContactThreshold = 150.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Threshold for determining if a bone pair can be considered to be having contact
- L65 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "SkeletalMeshAsset"))`
- L68 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAssetOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "PhysicsAssetOverride"))`
- L72 _public member_ `TArray<FName> DomainBodyNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "DomainBodyNames"))` — Bodies to be checked against contact bodies
- L75 _public member_ `TArray<FName> ContactBodyNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "ContactBodyNames"))`
- L79 _public member_ `TSubclassOf<URelativeBodyAnimNotifyBase> NotifyClass = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "PhysicalIKRetargeterNotifyClass"))` — Relative Body Notify subclass to create
- L82 _protected member_ `FMeshDescription MeshDescription;`
- L83 _protected member_ `FRelativeBodySourceData CachedBodySourceData;`
- L86 _protected member_ `int32 LODIndex = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Settings"))`
- L90 _protected member_ `TSet<FName> GeneratedNotifyTracks;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Settings"))` — Keep track of to be generated tracks during modifier application
- L92 _protected prototype_ `UPhysicsAsset* GetPhysicsAsset() const;`
- L94 _protected prototype_ `void CacheBodyDataForSourceMesh(FRelativeBodySourceData& OutSourceData);`
- L95 _protected prototype_ `void GetRefToAnimPoseMatrices(TArray<FMatrix44f>& OutRefToPose, const FAnimPose& AnimPose) const;`
- L96 _protected prototype_ `void GetSkinnedVertices(TArray<FVector3f>& VLocations, const TArray<FMatrix44f>& CacheToLocals);`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimUtils/Public/RelativeBodyAnimUtilsModule.h` (Public)


#### class `FRelativeBodyAnimUtilsModule`  
`class FRelativeBodyAnimUtilsModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimUtils/Public/RelativeBodyBlueprintFunctions.h` (Public)


#### struct `FRelativeBodyAnimModifierOptions`  
`struct FRelativeBodyAnimModifierOptions`  
_L13-41_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `int SampleRate = 30;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (Units = "Hz", UIMin = 1))` — Rate used to sample the animation
- L23 _public member_ `float ContactThreshold = 150.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Threshold for determining if a bone pair can be considered to be having contact
- L26 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "SkeletalMeshAsset"))`
- L29 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAssetOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "PhysicsAssetOverride"))`
- L33 _public member_ `TArray<FName> DomainBodyNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "DomainBodyNames"))` — Bodies to be checked against contact bodies
- L36 _public member_ `TArray<FName> ContactBodyNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "ContactBodyNames"))`
- L40 _public member_ `TSubclassOf<URelativeBodyAnimNotifyBase> NotifyClass = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (TitleProperty = "PhysicalIKRetargeterNotifyClass"))` — Relative Body Notify subclass to create

#### struct `FPropBodyAnimModifierOptions`  
`struct FPropBodyAnimModifierOptions : public FRelativeBodyAnimModifierOptions`  
_L44-59_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRelativeBodyAnimModifierOptions`
- L50 _public member_ `TArray<FPropsInfo> PropMeshSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Settings for each prop static mesh attachment to bake
- L54 _public member_ `bool bPropsFloorInfoBaking = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Include floor constraint info in prop bake
- L58 _public member_ `TSubclassOf<URelativePropsBakeAnimNotify> PropNotifyClass = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Prop Notify subclass to create

#### class `URelativeBodyAnimBlueprintFunctions`  
`class URelativeBodyAnimBlueprintFunctions : public UBlueprintFunctionLibrary`  
_L66-88_
- reflection: `UCLASS(Transient, meta=(ScriptName="RelativeBodyAnimModifyHelper"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: BPFL helper for setting up anim modifier
- L72 _public prototype_ `static void SetPropAttachBone(UPARAM(ref) FPropsInfo& Info, FName AttachBoneName);` — `UFUNCTION(BlueprintCallable, Category = "Anim Modifier", meta=(DeprecatedFunction, DeprecationMessage="Set prop attach SocketName directly in Props Info"))`
- L75 _public prototype_ `static FName GetPropAttachBone(const FPropsInfo& Info);` — `UFUNCTION(BlueprintCallable, Category = "Anim Modifier", meta=(DeprecatedFunction, DeprecationMessage="Get prop attach SocketName directly from Props Info"))`
- L78 _public prototype_ `static float GetSegmentStartTime(const FAnimNotifyEvent& AnimNotifyEvent);` — `UFUNCTION(BlueprintCallable, Category = "Anim Notify")`
- L81 _public prototype_ `static void SetRelativeAnimModifiers(UPARAM(ref) TArray<UAnimSequenceBase*>& AnimationList, const FPropBodyAnimModifierOptions& Options);` — `UFUNCTION(BlueprintCallable, Category = "Anim Modifier")`
- L84 _public prototype_ `static void BulkUpdateRelativeBodyModifiers(UPARAM(ref) TArray<UAnimSequenceBase*>& AnimationList, const FRelativeBodyAnimModifierOptions& Options);` — `UFUNCTION(BlueprintCallable, Category = "Anim Modifier")`
- L87 _public prototype_ `static void BulkUpdatePropBodyModifiers(UPARAM(ref) TArray<UAnimSequenceBase*>& AnimationList, const FPropBodyAnimModifierOptions& Options);` — `UFUNCTION(BlueprintCallable, Category = "Anim Modifier")`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimUtils/Public/RelativeBodyUtils.h` (Public)


#### struct `FRelativeBodyPhysicsUtils`  
`struct FRelativeBodyPhysicsUtils`  
_L14-19_
- L16 _public prototype_ `static FVector3f CalcReferenceShapeScale3D(FKShapeElem* ShapeElem);`
- L17 _public prototype_ `static FTransform GetBodyTransform(const UPhysicsAsset* PhysAsset, FName BoneName);`
- L18 _public prototype_ `static FKShapeElem* FindBodyShape(const UPhysicsAsset* PhysAsset, FName BoneName);`

#### struct `FRelativeBodyAnimUtils`  
`struct FRelativeBodyAnimUtils`  
_L21-28_
- L23 _public prototype_ `static FName FindParentBodyBoneName(const FName BoneName, const FReferenceSkeleton& RefSkeleton, const UPhysicsAsset* PhysicsAsset);`
- L24 _public prototype_ `static void GetRefGlobalPos(TArray<FTransform>& GlobalRefPose, const FReferenceSkeleton& RefSkeleton);`
- L26 _public prototype_ `static void GetRefPoseToLocalMatrices(TArray<FMatrix44f>& OutRefToLocals, TObjectPtr<USkeletalMesh> SkeletalMeshAsset, int32 LODIndex, const TArray<FTransform>& RetargetGlobalPose);`
- L27 _public prototype_ `static FVector3f CalcVertLocationInUnitBody(const FVector3f& RefPoint, const FName BodyBoneName, const FReferenceSkeleton& SourceRefSkeleton, const TArray<FMatrix44f>& CacheToLocals, const TArray<FTransform>& SourceGlobalPose, UPhysicsAsset* SourcePhysicsAsset);`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimUtils/Public/RelativeIKBulkExportHelper.h` (Public)


#### class `URelativeIKBulkExportHelper`  
`class URelativeIKBulkExportHelper : public UBlueprintFunctionLibrary`  
_L16-27_
- reflection: `UCLASS(Transient, meta=(ScriptName="RelativeBodyBulkExportHelper"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: BPFL helper for running bulk anim retarget for export
- L21 _public prototype_ `static void BulkRetargetSequences( UIKRetargeter* RetargetAsset, UPARAM(ref) const TArray<UAnimSequence*>& RetargetSequenceList, const FString& OutPath, USkeletalMesh* SourceMesh = nullptr, USkeletalMesh* TargetMesh = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Export Tools")`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeBodyAnimUtils/Public/RelativePropsAnimModifier.h` (Public)


#### struct `FPropsInfo`  
`struct FPropsInfo`  
_L21-59_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `TObjectPtr<UStaticMesh> PropStaticMeshAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to preview
- L30 _public member_ `TObjectPtr<USkeletalMesh> PropSkeletalMeshAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to preview
- L34 _public member_ `FName SocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Source skeletal mesh bone to attach prop to
- L38 _public member_ `FTransform AttachTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Local transform of prop relative to attach bone
- L42 _public member_ `TObjectPtr<UAnimSequence> PropAnimSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to anim sequence
- L46 _public member_ `float PropAnimStartTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to anim sequence start time
- L50 _public member_ `bool PropAnimIsLooping = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to anim sequence is looping
- L53 _public prototype_ `const FPositionVertexBuffer& GetPositionVertexBuffer();`
- L54 _public prototype_ `FMeshDescription* GetMeshDescription(int32 LodIndex);`
- L56 _public prototype_ `float ComputePropAnimPlayhead(float CharacterPlayhead) const;`
- L57 _public prototype_ `void GetSkinnedVertices(const TArray<FMatrix44f>& RefToPoseMatrices, TArray<FVector3f>& VLocation);`
- L58 _public prototype_ `void GetRefToAnimPoseMatrices(float AnimPlayhead, TArray<FMatrix44f>& OutRefToPose) const;`

#### class `URelativePropsAnimModifier`  
`class URelativePropsAnimModifier : public URelativeBodyAnimModifier`  
_L65-95_
- reflection: `UCLASS(meta = (IsBlueprintBase = true))`
- inherits: `URelativeBodyAnimModifier`
- desc: Animation modifier for baking relative body relationships into anim notify
- L71 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* InAnimation) override;` — Begin UAnimationModifier interface
- L76 _public member_ `TArray<FPropsInfo> PropsData;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (TitleProperty = "PropsData"))`
- L80 _public member_ `TSubclassOf<URelativePropsBakeAnimNotify> PropsNotifyClass = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (TitleProperty = "PropsNotifyClass"))` — Relative Props Notify subclass to create
- L83 _public member_ `bool bPropsFloorInfoBaking = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (TitleProperty = "PropsFloorInfoBaking"))`
- L86 _private prototype_ `void GetPropsVertices(TArray<TArray<FVector3f>>& PropsVLocations, const FAnimPose& AnimPose);`
- L88 _private prototype_ `static FName GetPropAttachInfo(FTransform& OutAttachTfm, const FPropsInfo& PropInfo, const USkeletalMesh* SkeletalMesh);`
- L91 _private member_ `TArray<FName> PropAttachBones;` — Actual bone names (pulled from socket info or prop info)
- L94 _private member_ `TArray<FTransform> PropAttachTfms;` — Baked down socket/prop attachments
