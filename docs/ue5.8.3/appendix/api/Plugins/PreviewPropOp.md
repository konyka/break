# Plugins / PreviewPropOp

- module root: `Plugins/Experimental/Animation/RelativeIKOp/Source/PreviewPropOp`
- headers: 2; symbols: 63
- symbol kinds: class=2, function=2, macro=2, member=30, prototype=21, struct=6
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine, IKRig, MeshDescription, Renderer, SkeletalMeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: 

### `Plugins/Experimental/Animation/RelativeIKOp/Source/PreviewPropOp/Public/PreviewPropOp.h` (Public)


#### struct `FPropTfmInfo`  
`struct FPropTfmInfo`  
_L25-30_
- L27 _public member_ `bool bValidTargetTfm = false;`
- L28 _public member_ `FTransform SourceTfm;`
- L29 _public member_ `FTransform TargetTfm;`

#### struct `FDebugPropDrawInfo`  
`struct FDebugPropDrawInfo`  
_L33-36_
- desc: Used to hold all debug draw info for convenience
- L35 _public member_ `TArray<FPropTfmInfo> PropTfmInfo;`

#### struct `FPropMeshData`  
`struct FPropMeshData`  
_L38-48_
- L40 _public member_ `int32 PropIdx;`
- L41 _public member_ `TArray<uint32> Indices;`
- L42 _public member_ `TArray<FDynamicMeshVertex> Vertices;`
- L43 _public member_ `TArray<FVector3f> RestVLocation;`
- L45 _public member_ `int32 SourceAttachBoneIndex;`
- L46 _public member_ `int32 TargetAttachBoneIndex;`
- L47 _public member_ `FTransform AttachTransform = FTransform::Identity;`

#### struct `FPreviewPropsData`  
`struct FPreviewPropsData`  
_L51-106_
- reflection: `USTRUCT(BlueprintType)`
- L59 _public member_ `bool ShowProp = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to anim sequence is looping
- L63 _public member_ `TObjectPtr<UStaticMesh> PropStaticMeshAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to preview
- L67 _public member_ `TObjectPtr<USkeletalMesh> PropSkeletalMeshAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to preview
- L71 _public member_ `FBoneReference SourceAttachBone;` — `UPROPERTY(EditAnywhere, Category = "Prop", meta=(ReinitializeOnEdit))` — Source skeletal mesh bone to attach prop to
- L75 _public member_ `FTransform AttachTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Local transform of prop relative to attach bone
- L79 _public member_ `TObjectPtr<UAnimSequence> PropAnimSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to anim sequence
- L83 _public member_ `float PropAnimStartTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to anim sequence start time
- L87 _public member_ `bool PropAnimIsLooping = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop", meta=(ReinitializeOnEdit))` — Prop mesh to anim sequence is looping
- L91 _public function_ `const FMeshDescription* GetMeshDescription(int32 LodIndex) const`

#### struct `FIKRetargetPreviewPropOpSettings`  
`struct FIKRetargetPreviewPropOpSettings : public FIKRetargetOpSettingsBase`  
_L109-136_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Preview Prop Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L113 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L115 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L118 _public prototype_ `virtual USkeleton* GetSkeleton(const FName InPropertyName);`
- L123 _public member_ `TMap<FName,FName> AttachMapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source Target Mapping", meta=(ReinitializeOnEdit))` — Attach bone source -> target name mapping
- L127 _public member_ `TArray<FPreviewPropsData> PreviewProps;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta=(ReinitializeOnEdit))` — Prop info to preview when debug drawing enabled
- L131 _public member_ `TObjectPtr<UMaterialInterface> DebugMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta=(ReinitializeOnEdit))` — Debug Material for displaying props (must work w/ dynamic mesh, e.g. physics materials)
- L135 _public member_ `bool bShowSourceProps = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Prop info to preview when debug drawing enabled

#### struct `FIKRetargetPreviewPropOp`  
`struct FIKRetargetPreviewPropOp : public FIKRetargetOpBase`  
_L139-206_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Prop Debug Preview"))`
- inherits: `FIKRetargetOpBase`
- L143 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L150 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L156 _public prototype_ `virtual void AnimGraphPreUpdateMainThread( USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent) override;`
- L160 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L162 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L164 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L167 _public member_ `FIKRetargetPreviewPropOpSettings Settings;` — `UPROPERTY()`
- L170 _private prototype_ `FName ApplyBoneMap(FName SourceBone);`
- L173 _private prototype_ `void UpdateAnimSeqPlayhead(UAnimInstance* SourceAnimInstance);`
- L174 _private prototype_ `float ComputePropAnimPlayhead(float PropAnimLength, float PropAnimStartTime, bool bLooping) const;`
- L176 _private prototype_ `void GetAnimSeqFramePose(const UAnimSequenceBase* AnimSeq, double Time, TArray<FName>& OutBones, TArray<FTransform>& OutPose) const;`
- L178 _private prototype_ `static bool GetMeshVertTris(FPropMeshData& OutMeshData, const FPreviewPropsData& PreviewProp);`
- L181 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L188 _public function_ `virtual bool HasDebugDrawing() override`
- L189 _public prototype_ `void UpdateSkinnedVertices(USkeletalMesh* SkeletalMeshAsset, FPropMeshData& PropMeshDataIn, const TArray<FMatrix44f>& RefToPoseMatrices);`
- L190 _public prototype_ `void GetRefToAnimPoseMatrices(UAnimSequence* InAnimation, float AnimPlayhead, USkeletalMesh* SkeletalMeshAsset, TArray<FMatrix44f>& OutRefToPose) const;`
- L194 _private member_ `FDebugPropDrawInfo DebugPropInfo;` — Bone transforms for prop preview
- L196 _private member_ `TArray<FPropMeshData> PropMeshData;` — Prop mesh info for all meshes (created in Initialize)
- L198 _private member_ `static FCriticalSection DebugDataMutex;`
- L201 _private member_ `TObjectPtr<const UAnimSequenceBase> CacheSourceCharacterAnim;` — Cache playing anim-seq/montage for grabbing a playhead
- L202 _private member_ `float SourceAnimPlayhead = 0.0f;`
- L204 _private member_ `TStrongObjectPtr<UMaterialInstanceDynamic> PropDefaultMaterial = nullptr;`

#### class `UIKRetargetPreviewPropController`  
`class UIKRetargetPreviewPropController : public UIKRetargetOpControllerBase`  
_L210-225_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing BodyIntersectIK Op
- L219 _public prototype_ `FIKRetargetPreviewPropOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetBodyIntersectIKOp struct with the current settings used by the op.
- L224 _public prototype_ `void SetSettings(FIKRetargetPreviewPropOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRetargetBodyIntersectIKOp struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PREVIEWPROPOP_API`
- L15 _macro_ `#define LOCTEXT_NAMESPACE "PreviewPropOp"`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/PreviewPropOp/Public/PreviewPropOpModule.h` (Public)


#### class `FPreviewPropOpModule`  
`class FPreviewPropOpModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
