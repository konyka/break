# Plugins / AnimToTexture

- module root: `Plugins/Experimental/AnimToTexture/Source/AnimToTexture`
- headers: 3; symbols: 126
- symbol kinds: class=3, delegate=1, enum=3, enumerator=7, function=10, macro=3, member=48, namespace=1, prototype=24, struct=4, variable=22
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, MeshDescription, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/AnimToTexture/Source/AnimToTexture/Public/AnimToTextureDataAsset.h` (Public)


#### enum `EAnimToTextureMode`  
`enum class EAnimToTextureMode : uint8`  
_L45-51_
- reflection: `UENUM(Blueprintable)`
- L48 _public enumerator_ `Vertex` — Position and Normal Per-Vertex
- L50 _public enumerator_ `Bone` — Linear Blending Skinnin

#### enum `EAnimToTexturePrecision`  
`enum class EAnimToTexturePrecision : uint8`  
_L54-60_
- reflection: `UENUM(Blueprintable)`
- L57 _public enumerator_ `EightBits` — 8 bits
- L59 _public enumerator_ `SixteenBits` — 16 bits

#### enum `EAnimToTextureNumBoneInfluences`  
`enum class EAnimToTextureNumBoneInfluences : uint8`  
_L63-71_
- reflection: `UENUM(Blueprintable)`
- L66 _public enumerator_ `One` — Single bone influence
- L68 _public enumerator_ `Two` — Blend between two influences
- L70 _public enumerator_ `Four` — Blend between four influences

#### struct `FAnimToTextureAnimSequenceInfo`  
`struct FAnimToTextureAnimSequenceInfo`  
_L74-96_
- reflection: `USTRUCT(Blueprintable)`
- L79 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = Default, BlueprintReadWrite)`
- L82 _public member_ `TObjectPtr<UAnimSequence> AnimSequence = nullptr;` — `UPROPERTY(EditAnywhere, Category = Default, BlueprintReadWrite, meta = (EditCondition = "bEnabled", EditConditionHides))`
- L86 _public member_ `bool bUseCustomRange = false;` — `UPROPERTY(EditAnywhere, Category = Default, BlueprintReadWrite, meta = (EditCondition = "bEnabled", EditConditionHides))` — Use Custom FrameRange
- L90 _public member_ `int32 StartFrame = 0;` — `UPROPERTY(EditAnywhere, Category = Default, BlueprintReadWrite, meta = (EditCondition = "bEnabled && bUseCustomRange", EditConditionHides))` — Animation Start Frame
- L94 _public member_ `int32 EndFrame = 0;` — `UPROPERTY(EditAnywhere, Category = Default, BlueprintReadWrite, meta = (EditCondition = "bEnabled && bUseCustomRange", EditConditionHides))` — Animation End Frame (Inclusive)

#### struct `FAnimToTextureAnimInfo`  
`struct FAnimToTextureAnimInfo`  
_L99-109_
- reflection: `USTRUCT(Blueprintable)`
- L104 _public member_ `int32 StartFrame = 0;` — `UPROPERTY(VisibleAnywhere, Category = Default, BlueprintReadOnly)`
- L107 _public member_ `int32 EndFrame = 0;` — `UPROPERTY(VisibleAnywhere, Category = Default, BlueprintReadOnly)`

#### class `UAnimToTextureDataAsset`  
`class UAnimToTextureDataAsset : public UPrimaryDataAsset`  
_L112-384_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UPrimaryDataAsset`
- L121 _public member_ `TSoftObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMesh", meta = (AssetBundles = "Client"))` — SkeletalMesh to bake animations from.
- L127 _public member_ `int32 SkeletalLODIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkeletalMesh", Meta = (DisplayName = "LODIndex"))` — SkeletalMesh LOD to bake.
- L133 _public member_ `TSoftObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh", meta = (AssetBundles = "Client"))` — StaticMesh to bake to.
- L139 _public member_ `int32 StaticLODIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh", Meta = (DisplayName = "LODIndex"))` — StaticMesh LOD to bake to.
- L146 _public member_ `int32 UVChannel = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")` — StaticMesh UVChannel Index for storing vertex information. Make sure this index does not conflict with the Lightmap UV Index.
- L155 _public member_ `int32 NumDriverTriangles = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh|Mapping")` — Number of Driver Triangles Each StaticMesh Vertex will be influenced by N SkeletalMesh (Driver) Triangles. Increasing the Number of Driver Triangles will increase the Mapping computation. Using a single Driver Triangle will do a Rigid Binding to Closest Triangle.
- L163 _public member_ `float Sigma = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh|Mapping")` — Inverse Distance Weighting This exponent value will be used for computing weights for the DriverTriangles. Larger number will create a more contrasted weighting, but it might
- L173 _public member_ `int32 MaxHeight = 4096;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")` — Max resolution of the texture. A smaller size will be used if the data fits.
- L180 _public member_ `int32 MaxWidth = 4096;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")` — Max resolution of the texture. A smaller size will be used if the data fits.
- L186 _public member_ `bool bEnforcePowerOfTwo = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")` — Enforce Power Of Two on texture resolutions.
- L192 _public member_ `EAnimToTexturePrecision Precision = EAnimToTexturePrecision::EightBits;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")` — Texture Precision
- L201 _public member_ `EAnimToTextureMode Mode = EAnimToTextureMode::Bone;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")` — Storage Mode. Vertex: will store per-vertex position and normal. Bone: Will store per-bone position and rotation and per-vertex bone weight. This is the preferred method if meshes share skeleton.
- L208 _public member_ `TSoftObjectPtr<UTexture2D> VertexPositionTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture", meta = (EditCondition = "Mode == EAnimToTextureMode::Vertex", EditConditionHides))` — Texture for storing vertex positions This is only used on Vertex Mode
- L215 _public member_ `TSoftObjectPtr<UTexture2D> VertexNormalTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture", meta = (EditCondition = "Mode == EAnimToTextureMode::Vertex", EditConditionHides))` — Texture for storing vertex normals This is only used on Vertex Mode
- L222 _public member_ `TSoftObjectPtr<UTexture2D> BonePositionTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture", meta = (EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))` — Texture for storing bone positions This is only used on Bone Mode
- L229 _public member_ `TSoftObjectPtr<UTexture2D> BoneRotationTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture", meta = (EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))` — Texture for storing bone rotations This is only used on Bone Mode
- L236 _public member_ `TSoftObjectPtr<UTexture2D> BoneWeightTexture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture", meta = (EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))` — Texture for storing vertex/bone weighting This is only used on Bone Mode
- L246 _public member_ `FTransform RootTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")` — Adds transformation to baked textures. This can be used for adding an offset to the animation.
- L253 _public member_ `FName AttachToSocket;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (EditCondition = "Mode == EAnimToTextureMode::Bone"))` — Bone used for Rigid Binding. The bone needs to be part of the RawBones. Sockets and VirtualBones are not supported.
- L256 _public member_ `float SampleRate = 30.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")`
- L259 _public member_ `TArray<FAnimToTextureAnimSequenceInfo> AnimSequences;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")`
- L269 _public member_ `bool bAutoPlay = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")` — AutoPlay will use Engine Time for driving the animation. This will be used by UpdateMaterialInstanceFromDataAsset and AssetActions for setting MaterialInstance static switches
- L277 _public member_ `int32 AnimationIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material", meta = (EditCondition = "bAutoPlay"))` — AnimationIndex Index of the animation to play. This will internally set Start and End Frame when using AutoPlay. This will be used by UpdateMaterialInstanceFromDataAsset and AssetActions for setting MaterialInstance static switches
- L285 _public member_ `int32 Frame = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material", meta = (EditCondition = "!bAutoPlay"))` — Frame to play When not using AutoPlay, user is responsible of setting the frame. This will be used by UpdateMaterialInstanceFromDataAsset and AssetActions for setting MaterialInstance static switches
- L292 _public member_ `EAnimToTextureNumBoneInfluences NumBoneInfluences = EAnimToTextureNumBoneInfluences::Four;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material", meta = (EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))` — Number of Bone Influences for deformation. More influences will produce smoother results at the cost of performance. This will be used by UpdateMaterialInstanceFromDataAsset and AssetActions for setting MaterialInstance static switches
- L299 _public member_ `int32 NumFrames = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")` — Total Number of Frames in all animations
- L303 _public member_ `int32 NumBones = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info", Meta = (EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))` — Total Number of Bones
- L306 _public member_ `int32 VertexRowsPerFrame = 1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info", Meta = (EditCondition = "Mode == EAnimToTextureMode::Vertex", EditConditionHides))`
- L309 _public member_ `FVector3f VertexMinBBox;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info", Meta = (DisplayName = "MinBBox", EditCondition = "Mode == EAnimToTextureMode::Vertex", EditConditionHides))`
- L312 _public member_ `FVector3f VertexSizeBBox;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info", Meta = (DisplayName = "SizeBBox", EditCondition = "Mode == EAnimToTextureMode::Vertex", EditConditionHides))`
- L315 _public member_ `int32 BoneWeightRowsPerFrame = 1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info", Meta = (EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))`
- L318 _public member_ `int32 BoneRowsPerFrame = 1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info", Meta = (EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))`
- L321 _public member_ `FVector3f BoneMinBBox;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info", Meta = (DisplayName = "MinBBox", EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))`
- L324 _public member_ `FVector3f BoneSizeBBox;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info", Meta = (DisplayName = "SizeBBox", EditCondition = "Mode == EAnimToTextureMode::Bone", EditConditionHides))`
- L327 _public member_ `TArray<FAnimToTextureAnimInfo> Animations;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")`
- L334 _public prototype_ `int32 GetIndexFromAnimSequence(const UAnimSequence* Sequence);` — `UFUNCTION(BlueprintCallable, Category = Default)` — Finds AnimSequence Index in the Animations Array. Only Enabled elements are returned. Returns -1 if not found.
- L337 _public prototype_ `void ResetInfo();` — `UFUNCTION()`
- L341 _public function_ `template<typename AssetType> static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer)` — If we weren't in a plugin, we could unify this in a base class
- L362 _public prototype_ `AnimToTextureDataAsset_ASSET_ACCESSOR(UStaticMesh, StaticMesh);`
- L363 _public prototype_ `AnimToTextureDataAsset_ASSET_ACCESSOR(USkeletalMesh, SkeletalMesh);`
- L364 _public prototype_ `AnimToTextureDataAsset_ASSET_ACCESSOR(UTexture2D, VertexPositionTexture);`
- L365 _public prototype_ `AnimToTextureDataAsset_ASSET_ACCESSOR(UTexture2D, VertexNormalTexture);`
- L366 _public prototype_ `AnimToTextureDataAsset_ASSET_ACCESSOR(UTexture2D, BonePositionTexture);`
- L367 _public prototype_ `AnimToTextureDataAsset_ASSET_ACCESSOR(UTexture2D, BoneRotationTexture);`
- L368 _public prototype_ `AnimToTextureDataAsset_ASSET_ACCESSOR(UTexture2D, BoneWeightTexture);`
- L371 _public function_ `UStaticMesh* BP_GetStaticMesh()` — `UFUNCTION(BlueprintPure, Category = Default, meta = (DisplayName = "Get Static Mesh"))`
- L374 _public function_ `USkeletalMesh* BP_GetSkeletalMesh()` — `UFUNCTION(BlueprintPure, Category = Default, meta = (DisplayName = "Get Skeletal Mesh"))`
- L377 _public function_ `UTexture2D* BP_GetBonePositionTexture()` — `UFUNCTION(BlueprintPure, Category = Default, meta = (DisplayName = "Get Bone Position Texture"))`
- L380 _public function_ `UTexture2D* BP_GetBoneRotationTexture()` — `UFUNCTION(BlueprintPure, Category = Default, meta = (DisplayName = "Get Bone Rotation Texture"))`
- L383 _public function_ `UTexture2D* BP_GetBoneWeightTexture()` — `UFUNCTION(BlueprintPure, Category = Default, meta = (DisplayName = "Get Bone Weight Texture"))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMTOTEXTURE_API`
- L18 _namespace_ `namespace AnimToTextureParamNames`
- L20 _variable_ `static const FName Frame = TEXT("Fra` (scope `AnimToTextureParamNames`)
- L21 _variable_ `static const FName AutoPlay = TEXT("Aut` (scope `AnimToTextureParamNames`)
- L22 _variable_ `static const FName StartFrame = TEXT("Sta` (scope `AnimToTextureParamNames`)
- L23 _variable_ `static const FName EndFrame = TEXT("End` (scope `AnimToTextureParamNames`)
- L24 _variable_ `static const FName SampleRate = TEXT("Sam` (scope `AnimToTextureParamNames`)
- L25 _variable_ `static const FName NumFrames = TEXT("Num` (scope `AnimToTextureParamNames`)
- L26 _variable_ `static const FName MinBBox = TEXT("Min` (scope `AnimToTextureParamNames`)
- L27 _variable_ `static const FName SizeBBox = TEXT("Siz` (scope `AnimToTextureParamNames`)
- L28 _variable_ `static const FName NumBones = TEXT("Num` (scope `AnimToTextureParamNames`)
- L29 _variable_ `static const FName RowsPerFrame = TEXT("Row` (scope `AnimToTextureParamNames`)
- L30 _variable_ `static const FName BoneWeightRowsPerFrame = TEXT("Bon` (scope `AnimToTextureParamNames`)
- L31 _variable_ `static const FName VertexPositionTexture = TEXT("Pos` (scope `AnimToTextureParamNames`)
- L32 _variable_ `static const FName VertexNormalTexture = TEXT("Nor` (scope `AnimToTextureParamNames`)
- L33 _variable_ `static const FName BonePositionTexture = TEXT("Bon` (scope `AnimToTextureParamNames`)
- L34 _variable_ `static const FName BoneRotationTexture = TEXT("Bon` (scope `AnimToTextureParamNames`)
- L35 _variable_ `static const FName BoneWeightsTexture = TEXT("Bon` (scope `AnimToTextureParamNames`)
- L36 _variable_ `static const FName UseUV0 = TEXT("Use` (scope `AnimToTextureParamNames`)
- L37 _variable_ `static const FName UseUV1 = TEXT("Use` (scope `AnimToTextureParamNames`)
- L38 _variable_ `static const FName UseUV2 = TEXT("Use` (scope `AnimToTextureParamNames`)
- L39 _variable_ `static const FName UseUV3 = TEXT("Use` (scope `AnimToTextureParamNames`)
- L40 _variable_ `static const FName UseTwoInfluences = TEXT("Use` (scope `AnimToTextureParamNames`)
- L41 _variable_ `static const FName UseFourInfluences = TEXT("Use` (scope `AnimToTextureParamNames`)
- L359 _macro_ `#define AnimToTextureDataAsset_ASSET_ACCESSOR(ClassName, PropertyName) \`

### `Plugins/Experimental/AnimToTexture/Source/AnimToTexture/Public/AnimToTextureInstancePlaybackHelpers.h` (Public)


#### struct `FAnimToTextureFrameData`  
`struct FAnimToTextureFrameData`  
_L15-30_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `float Frame = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimToTexture|Playback")` — Frame to be played
- L29 _public member_ `float PrevFrame = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimToTexture|Playback")` — Previous Frame (this is needeed for motion blur)

#### struct `FAnimToTextureAutoPlayData`  
`struct FAnimToTextureAutoPlayData`  
_L33-60_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public member_ `float TimeOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimToTexture|Playback")` — Adds offset to time
- L47 _public member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimToTexture|Playback")` — Rate for increasing and decreasing speed.
- L53 _public member_ `float StartFrame = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimToTexture|Playback")` — Starting frame for animation.
- L59 _public member_ `float EndFrame = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimToTexture|Playback")` — Last frame of animation

#### class `UAnimToTextureInstancePlaybackLibrary`  
`class UAnimToTextureInstancePlaybackLibrary : public UBlueprintFunctionLibrary`  
_L64-141_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L75 _public prototype_ `static bool SetupInstancedMeshComponent(UInstancedStaticMeshComponent* InstancedMeshComponent, int32 NumInstances, bool bAutoPlay);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture|Playback")` — Adds Instances and allocates the necessary CustomData. @param bAutoPlay: if true, it will allocate the required CustomData for working with AutoPlayData. If false, FrameData will be allocated instead./
- L82 _public prototype_ `static bool BatchUpdateInstancesAutoPlayData(UInstancedStaticMeshComponent* InstancedMeshComponent, const TArray<FAnimToTextureAutoPlayData>& AutoPlayData, const TArray<FTransform>& Transforms, bool bMarkRenderStateDirty=true);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture|Playback")` — Updates all instances with the given Transforms and AutoPlayData @param bMarkRenderStateDirty: if true, the change should be visible immediatelly. If you are updating many instances you should only set this to true for the last instance
- L90 _public prototype_ `static bool BatchUpdateInstancesFrameData(UInstancedStaticMeshComponent* InstancedMeshComponent, const TArray<FAnimToTextureFrameData>& FrameData, const TArray<FTransform>& Transforms, bool bMarkRenderStateDirty=true);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture|Playback")` — Updates all instances with the given Transforms and FrameData @param bMarkRenderStateDirty: if true, the change should be visible immediatelly. If you are updating many instances you should only set this to true for the last instance
- L98 _public prototype_ `static bool UpdateInstanceAutoPlayData(UInstancedStaticMeshComponent* InstancedMeshComponent, int32 InstanceIndex, const FAnimToTextureAutoPlayData& AutoPlayData, bool bMarkRenderStateDirty=true);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture|Playback")` — Updates a single instance with given AutoPlayData @param bMarkRenderStateDirty: if true, the change should be visible immediatelly. If you are updating many instances you should only set this to true for the last instance
- L106 _public prototype_ `static bool UpdateInstanceFrameData(UInstancedStaticMeshComponent* InstancedMeshComponent, int32 InstanceIndex, const FAnimToTextureFrameData& FrameData, bool bMarkRenderStateDirty=true);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture|Playback")` — * Updates a single instance with given FrameData @param bMarkRenderStateDirty: if true, the change should be visible immediatelly. If you are updating many instances you should only set this to true for the last instance
- L114 _public prototype_ `static bool GetAutoPlayDataFromDataAsset(const UAnimToTextureDataAsset* DataAsset, int32 AnimationIndex, FAnimToTextureAutoPlayData& AutoPlayData, float TimeOffset = 0.f, float PlayRate = 1.f);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture|Playback")` — Returns an AutoPlayData with the Start and End Frame for the given AnimationIndex. If AnimationIndex is out of range, false will be returned.
- L118 _public prototype_ `static float GetFrame(float Time, float StartFrame, float EndFrame, float TimeOffset = 0.f, float PlayRate = 1.f, float SampleRate = 30.f);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture|Playback")`
- L122 _public prototype_ `static bool GetFrameDataFromDataAsset(const UAnimToTextureDataAsset* DataAsset, int32 AnimationIndex, float Time, FAnimToTextureFrameData& FrameData, float TimeOffset = 0.f, float PlayRate = 1.f);` — `UFUNCTION(BlueprintCallable, Category = "AnimToTexture|Playback")`
- L128 _private prototype_ `template <class DataType> static bool BatchUpdateInstancesData(UInstancedStaticMeshComponent* InstancedMeshComponent, const TArray<DataType>& Data, const TArray<FTransform>& Transforms, bool bMarkRenderStateDirty = true);`
- L132 _private prototype_ `template <class DataType> static bool UpdateInstanceCustomData(UInstancedStaticMeshComponent* InstancedMeshComponent, int32 InstanceIndex, const DataType& Data, bool bMarkRenderStateDirty = true);`
- L136 _private prototype_ `template <class DataType> static void GetData(const DataType& Data, TArray<float>& CustomData);`
- L139 _private prototype_ `template <class DataType> static void GetCustomData(const TArray<DataType>& Data, TArray<float>& CustomData);`
- L145 _function_ `template <class DataType> bool UAnimToTextureInstancePlaybackLibrary::BatchUpdateInstancesData(UInstancedStaticMeshComponent* InstancedMeshComponent, const TArray<DataType>& Data, const TArray<FTransform>& Transforms, bool bMarkRenderStateDirty)`
- L179 _function_ `template <class DataType> void UAnimToTextureInstancePlaybackLibrary::GetData(const DataType& Data, TArray<float>& CustomData)`
- L188 _function_ `template <class DataType> void UAnimToTextureInstancePlaybackLibrary::GetCustomData(const TArray<DataType>& Data, TArray<float>& CustomData)`
- L197 _function_ `template <class DataType> bool UAnimToTextureInstancePlaybackLibrary::UpdateInstanceCustomData(UInstancedStaticMeshComponent* InstancedMeshComponent, int32 InstanceIndex, const DataType& Data, bool bMarkRenderStateDirty)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMTOTEXTURE_API`

### `Plugins/Experimental/AnimToTexture/Source/AnimToTexture/Public/AnimToTextureModule.h` (Public)


#### class `FAnimToTextureModule`  
`class FAnimToTextureModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimToTexture, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimToTexture, Log, All);`
