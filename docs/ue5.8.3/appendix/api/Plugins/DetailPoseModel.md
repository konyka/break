# Plugins / DetailPoseModel

- module root: `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModel`
- headers: 4; symbols: 55
- symbol kinds: class=4, function=24, member=13, namespace=2, prototype=11, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ComputeFramework, CoreUObject, Engine, GeometryCache, MLDeformerFramework, NNE, NNERuntimeBasicCpu, NeuralMorphModel, OptimusCore, Projects, RHI, RenderCore
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModel/Public/DetailPoseModel.h` (Public)


#### struct `FDetailPoseModelDetailPose`  
`struct FDetailPoseModelDetailPose`  
_L12-19_
- reflection: `USTRUCT()`
- L18 _public member_ `TArray<float> PoseValues;` — `UPROPERTY()` — The values that represent the pose. These are the same as the neural network inputs that would represent this pose.

#### class `UDetailPoseModel`  
`class UDetailPoseModel : public UNeuralMorphModel`  
_L30-124_
- reflection: `UCLASS()`
- inherits: `UNeuralMorphModel`
- desc: The detail pose model for the ML Deformer. This model is inherited from the Neural Morph Model, but adds additional morph targets on top of this. The additional morph targets that are generated are morph targets that bring it to the ground truth as seen during training at specific poses. These special poses are called Detail Poses. We basically look at the deltas that we predict using the neural morph model, and put the remaining error between that and the ground truth into the morph target at the given pose. There can be multiple detail poses, and each of them generates a new morph target.
- L36 _public prototype_ `UDetailPoseModel(const FObjectInitializer& ObjectInitializer);`
- L39 _public prototype_ `void Serialize(FArchive& Archive) override final;` — UObject overrides.
- L40 _public prototype_ `void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override final;`
- L44 _public function_ `FString GetDisplayName() const override final` — UMLDeformerModel overrides.
- L45 _public prototype_ `UMLDeformerModelInstance* CreateModelInstance(UMLDeformerComponent* Component) override final;`
- L46 _public prototype_ `UMLDeformerInputInfo* CreateInputInfo() override final;`
- L50 _public function_ `bool SupportsGlobalModeOnly() const override final` — UNeuralMorphModel overrides.
- L53 _public function_ `const TArray<FDetailPoseModelDetailPose>& GetDetailPoses() const`
- L54 _public function_ `TArray<FDetailPoseModelDetailPose>& GetDetailPoses()`
- L55 _public function_ `float GetBlendSpeed() const`
- L56 _public function_ `bool GetUseRBFBlending() const`
- L57 _public function_ `float GetRBFRange() const`
- L59 _public function_ `void SetUseRBFBlending(bool bUse)`
- L60 _public function_ `void SetBlendSpeed(float Speed)`
- L61 _public function_ `void SetRBFRange(float Range)`
- L64 _public prototype_ `UAnimSequence* GetDetailPosesAnimSequence() const;`
- L65 _public prototype_ `UGeometryCache* GetDetailPosesGeomCache() const;`
- L67 _public function_ `static FName GetDetailPosesAnimSequencePropertyName()`
- L68 _public function_ `static FName GetDetailPosesGeomCachePropertyName()`
- L69 _public function_ `static FName GetBlendSpeedPropertyName()`
- L70 _public function_ `static FName GetUseRBFBlendingPropertyName()`
- L71 _public function_ `static FName GetRBFRangePropertyName()`
- L77 _private member_ `TArray<FDetailPoseModelDetailPose> DetailPoses;` — `UPROPERTY()` — The detail poses. This contains the pose values we use at runtime.
- L90 _private member_ `TSoftObjectPtr<UAnimSequence> DetailPosesAnimSequence;` — `UPROPERTY(EditAnywhere, Category = "Detail Poses")` — For certain poses the ML Deformer might not reconstruct important details such as specific cloth folding patterns. To improve the results near these important poses, you can provide a set of these poses. The poses are provided similar to the training input data, with an animation sequence and geometry cache pair where each frame contains a pose you want to preserve details in. The more poses you add, the higher the memory usage. Each pose will generate an additional morph target. If you do not add any detail poses, the model will behave the same as the Neural Morph Model in global mode. Please keep the frame rate and frame count the same for both the anim sequence and geometry cache.
- L102 _private member_ `TSoftObjectPtr<UGeometryCache> DetailPosesGeomCache;` — `UPROPERTY(EditAnywhere, Category = "Detail Poses")` — For certain poses the ML Deformer might not reconstruct important details such as specific cloth folding patterns. To improve the results near these important poses, you can provide a set of these poses. The poses are provided similar to the training input data, with an animation sequence and geometry cache pair where each frame contains a pose you want to preserve details in. The more poses you add, the higher the memory usage. Each pose will generate an additional morph target. If you do not add any detail poses, the model will behave the same as the Neural Morph Model in global mode. Please keep the frame rate and frame count the same for both the anim sequence and geometry cache.
- L112 _private member_ `float BlendSpeed = 0.3f;` — `UPROPERTY(EditAnywhere, Category = "Detail Poses", meta = (ClampMin="0.0", ClampMax="1.0"))` — The speed at which the detail poses are blend in. Higher values make it blend in faster. A value of 0.0 would disable the detail poses from being calculated. A value of 1.0 would disable blending and instantly switch the active detail pose weight.
- L119 _private member_ `bool bUseRBF = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Use RBF Blending", Category = "Detail Poses")` — Use RBF (Radial Basis Functions) to interpolate? This will produce higher quality blends between detail poses, at the cost of runtime CPU performance.
- L123 _private member_ `float RBFRange = 1.0f;` — `UPROPERTY(EditAnywhere, DisplayName = "RBF Range", Category = "Detail Poses", meta = (ClampMin = "0", EditCondition = "bUseRBF"))` — The range to blend detail poses. Larger values will blend more detail poses together but also result in slower GPU performance.

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDetailPoseModel, Log, All);` — Declare our log category.

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModel/Public/DetailPoseModelInputInfo.h` (Public)


#### class `UDetailPoseModelInputInfo`  
`class UDetailPoseModelInputInfo : public UNeuralMorphInputInfo`  
_L18-48_
- reflection: `UCLASS()`
- inherits: `UNeuralMorphInputInfo`
- desc: The input info class for the Detail Pose Model. We store values that were used during training. These are often used during inference.
- L27 _public prototype_ `void Reset() override final;` — FMLDeformerInputInfo overrides.
- L39 _public function_ `int32 GetNumGlobalMorphTargets() const` — Get the number of morph targets that the model should output. This is basically the number of outputs of our neural network. Please keep in mind that the number of morph targets that are actually used is higher than this number. The number returned by this method is really what we entered as number of morph targets in the UI. We do generate an extra morph target that holds the mean values as well, and next to that there is a morph target for each detail pose. So please keep in mind this is just the number of morph targets we entered in the UI before we pressed the Train button, and that it is equal to the number of neural network outputs.
- L42 _private function_ `void SetNumGlobalMorphTargets(int32 Num)`
- L47 _private member_ `int32 NumGlobalMorphTargets = 0;` — `UPROPERTY()` — The number of morph targets the training process generated. This excludes the morph target that contains the means.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DetailPoseModel` (scope `UE`)

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModel/Public/DetailPoseModelInstance.h` (Public)


#### class `UDetailPoseModelInstance`  
`class UDetailPoseModelInstance : public UNeuralMorphModelInstance`  
_L16-43_
- reflection: `UCLASS()`
- inherits: `UNeuralMorphModelInstance`
- desc: The model instance class of the Detail Pose Model. This contains the code that calculates the morph target weights and which calculates which detail pose should be blend in.
- L23 _public prototype_ `void Init(USkeletalMeshComponent* SkelMeshComponent) override final;` — UMLDeformerModelInstance overrides.
- L24 _public prototype_ `void Execute(float ModelWeight) override final;`
- L32 _public function_ `int32 GetBestDetailPoseIndex() const` — Get the best matching detail pose, compared to the character's current pose as defined by the skeletal mesh component we are linked to. The integer that is returned represents the frame number inside the detail pose model's detail pose geometry cache. @return The index of the frame number in the detail pose geometry cache that best matches our current pose.
- L36 _private member_ `TArray<float> DetailPoseDistances;` — The distance value between the current current pose and each detail pose.
- L39 _private member_ `TArray<float> DetailPosePrevWeights;` — The detail pose previous frame weights, one for each detail pose.
- L42 _private member_ `int32 BestDetailPoseIndex = -1;` — The detail pose index that currently is the one with closest distance. This is the frame number inside the detail pose geometry cache.

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModel/Public/DetailPoseModelVizSettings.h` (Public)


#### class `UDetailPoseModelVizSettings`  
`class UDetailPoseModelVizSettings : public UNeuralMorphModelVizSettings`  
_L13-42_
- reflection: `UCLASS()`
- inherits: `UNeuralMorphModelVizSettings`
- desc: The visualization settings specific to the Detail Pose Model.
- L20 _public function_ `float GetDetailPoseWeight() const`
- L21 _public function_ `void SetDetailPoseWeight(float Factor)`
- L23 _public function_ `bool GetDrawDetailPose() const`
- L24 _public function_ `void SetDrawDetailPose(bool bDraw)`
- L26 _public function_ `static FName GetDetailPoseWeightPropertyName()`
- L27 _public function_ `static FName GetDrawDetailPosePropertyName()`
- L36 _private member_ `float DetailPoseWeight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Live Settings|Detail Poses", meta = (ClampMin = "0.0", ClampMax = "1.0"))` — The weight that specifies how much of the detail poses should be added. When this value is set to 0 it means the detail poses are not visually active. When set to 1, they are fully active.
- L40 _private member_ `bool bDrawDetailPose = true;` — `UPROPERTY(EditAnywhere, Category = "Live Settings|Detail Poses")` — Do we want to draw the closest matching detail pose?
