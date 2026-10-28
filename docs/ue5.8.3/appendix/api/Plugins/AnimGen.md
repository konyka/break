# Plugins / AnimGen

- module root: `Plugins/Experimental/Animation/AnimGen/Source/AnimGen`
- headers: 8; symbols: 859
- symbol kinds: class=24, enum=9, enumerator=20, function=3, macro=6, member=327, namespace=13, prototype=438, struct=19
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DrawDebugLibrary, Engine, InputCore, NNE, NNERuntimeBasicCpu, NetCore, PoseSearch, Projects, RigVM, Slate, SlateCore
- PublicDependencyModuleNames: AnimDatabase, Core, Learning, UAF, UAFAnimGraph, UAFPoseSearch

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGen/Public/AnimGen.h` (Public)


#### class `FAnimGenModule`  
`class FAnimGenModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGen/Public/AnimGenAutoEncoder.h` (Public)


#### class `UAnimGenAutoEncoderDebugDraw`  
`class UAnimGenAutoEncoderDebugDraw : public UObject`  
_L35-70_
- reflection: `UCLASS(Abstract, HideDropdown, EditInlineNew, DefaultToInstanced, CollapseCategories, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Debug draw class used by the auto-encoder. Allows for custom debug-draw logic in the viewport
- L45 _public prototype_ `void InitializeDrawDebug(const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const UAnimGenAutoEncoder* InAutoEncoder);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimGen", meta = (ForceAsFunction))` — Make any required frame attributes or other data. This function is called once when the class is initialized
- L51 _public prototype_ `void DrawDebug( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InOriginalPoseState, const FAnimDatabasePoseState& InReconstructedPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor, const FLinearColor& OriginalColor, const FLinearColor& ReconstructedColor);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimGen", meta = (ForceAsFunction))` — Draw Debug function which is called each frame with the current pose state information

#### class `UAnimGenAutoEncoderViewportSettings`  
`class UAnimGenAutoEncoderViewportSettings : public UObject`  
_L74-301_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class containing all the UAnimGenAutoEncoder Editor window viewport settings
- L84 _public member_ `TObjectPtr<USkeletalMesh> PreviewMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — Mesh to use for previewing the character
- L88 _public member_ `bool bMeshOnReconstruction = true;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — If to apply the character mesh to the reconstruction or to the original
- L92 _public member_ `bool bShowDefaultPose = false;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — Shows the character in the "default pose" used by the auto-encoder
- L98 _public member_ `bool bDrawOriginalSkeleton = true;` — `UPROPERTY(EditAnywhere, Category = "Skeleton")` — If to draw the original skeleton of all characters
- L102 _public member_ `FLinearColor DrawOriginalSkeletonColor = FLinearColor(0.0f, 0.0f, 0.025f, 0.5f);` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawOriginalSkeleton", HideEditConditionToggle))` — The color to use for the drawing of the original skeleton
- L106 _public member_ `bool bDrawReconstructedSkeleton = true;` — `UPROPERTY(EditAnywhere, Category = "Skeleton")` — If to draw the reconstructed skeleton of all characters
- L110 _public member_ `FLinearColor DrawReconstructedSkeletonColor = FLinearColor(0.117f, 0.407f, 0.478f, 0.5f);` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawReconstructedSkeleton", HideEditConditionToggle))` — The color to use for the reconstructed skeleton
- L114 _public member_ `bool bDrawRequiredBonesOnly = true;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawOriginalSkeleton || bDrawReconstructedSkeleton", HideEditConditionToggle))` — If to only draw the bones that are being encoded by the auto-encoder
- L118 _public member_ `bool bDrawSimpleSkeleton = true;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawOriginalSkeleton || bDrawReconstructedSkeleton", HideEditConditionToggle))` — Draw a simple skeleton made up of lines connecting bones
- L122 _public member_ `float DrawSkeletonScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawOriginalSkeleton || bDrawReconstructedSkeleton", HideEditConditionToggle))` — The scale of the drawn skeleton bones
- L126 _public member_ `bool bDrawLinearVelocities = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawOriginalSkeleton || bDrawReconstructedSkeleton", HideEditConditionToggle))` — If to draw linear velocities for each of the skeleton's bones
- L130 _public member_ `float DrawLinearVelocitiesScale = 0.05f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "(bDrawOriginalSkeleton || bDrawReconstructedSkeleton) && bDrawLinearVelocities", HideEditConditionToggle))` — The scale of the linear velocities being drawn
- L134 _public member_ `float DrawLinearVelocitiesOpacity = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "(bDrawOriginalSkeleton || bDrawReconstructedSkeleton) && bDrawLinearVelocities", HideEditConditionToggle))` — Opacity of the linear velocities being drawn
- L138 _public member_ `bool bDrawAngularVelocities = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawOriginalSkeleton || bDrawReconstructedSkeleton", HideEditConditionToggle))` — If to draw angular velocities for each of the skeleton's bones
- L142 _public member_ `float DrawAngularVelocitiesScale = 2.5f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "(bDrawOriginalSkeleton || bDrawReconstructedSkeleton) && bDrawAngularVelocities", HideEditConditionToggle))` — The scale of the angular velocities being drawn
- L146 _public member_ `float DrawAngularVelocitiesOpacity = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "(bDrawOriginalSkeleton || bDrawReconstructedSkeleton) && bDrawAngularVelocities", HideEditConditionToggle))` — Opacity of the angular velocities being drawn
- L150 _public member_ `bool bDrawBoneTransforms = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawOriginalSkeleton || bDrawReconstructedSkeleton", HideEditConditionToggle))` — If to draw bone transforms
- L156 _public member_ `bool bDrawRoot = false;` — `UPROPERTY(EditAnywhere, Category = "Root")` — If to draw the root of the skeleton as a transform
- L160 _public member_ `float DrawRootOpacity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Root", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawRoot", HideEditConditionToggle))` — Opacity of the drawn root
- L164 _public member_ `float DrawRootScale = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Root", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRoot", HideEditConditionToggle))` — The scale of the drawn root
- L168 _public member_ `bool bIntegrateRootOnReconstruction = false;` — `UPROPERTY(EditAnywhere, Category = "Root")` — If to integrate the root on the reconstructed pose rather than copy the root from the source
- L174 _public member_ `bool bDrawTrajectories = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory")` — If to draw the trajectories of the selected ranges
- L178 _public member_ `bool bDrawTrajectoryOrientations = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (EditCondition = "bDrawTrajectories", HideEditConditionToggle))` — If to draw the trajectory orientations of the selected ranges
- L184 _public member_ `bool bRangesStartAtOrigin = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — Re-orients all ranges so that they start at the scene origin rather than wherever they started in the source data
- L188 _public member_ `bool bOffsetRanges = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin", HideEditConditionToggle))` — Offset different ranges away from origin so they can be viewed together
- L192 _public member_ `float RangeOffsetSpacing = 100.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bOffsetRanges", HideEditConditionToggle))` — Spacing to use for offsetting ranges
- L196 _public member_ `bool bOffsetRangesInGrid = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bOffsetRanges", HideEditConditionToggle))` — If to offset selected ranges as a grid
- L200 _public member_ `bool bDisableRootTranslation = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin", HideEditConditionToggle))` — Remove root translation when display ranges
- L204 _public member_ `bool bDisableRootRotation = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin && bDisableRootTranslation", HideEditConditionToggle))` — Remove root rotation when display ranges
- L208 _public member_ `bool bDrawRangeIdentifier = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — If to draw the colored range identifier over the character to show which range in the query the animation is from
- L212 _public member_ `int32 RangeIdentifierColorSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — Seed used for the colors of the range identifiers
- L216 _public member_ `float DrawRangeIdentifierThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Thickness of the range identifier
- L220 _public member_ `float DrawRangeIdentifierRadius = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Radius of the range identifier
- L224 _public member_ `float DrawRangeIdentifierOpacity = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Opacity of the range identifier
- L228 _public member_ `float DrawRangeIdentifierHeight = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Height offset used to draw the range identifier
- L232 _public member_ `bool bOverrideRangeIdentifierColor = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — If to override the range identifier color
- L236 _public member_ `FLinearColor RangeIdentifierColorOverride = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bOverrideRangeIdentifierColor", HideEditConditionToggle))` — Color to use to override the range identifier
- L242 _public member_ `bool bDrawOrigin = true;` — `UPROPERTY(EditAnywhere, Category = "Origin")` — If to draw the scene origin as a transform
- L246 _public member_ `float DrawOriginLineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Thickness of the drawn scene origin
- L250 _public member_ `float DrawOriginOpacity = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Opacity of the drawn scene origin
- L254 _public member_ `float DrawOriginScale = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Scale of the drawn scene origin
- L264 _public function_ `void RebuildVisualizationEncoding()` — `UFUNCTION(CallInEditor, Category = "Encoding Visualization", DisplayName="Rebuild Encoding Visualization")` — Rebuilds the encoding visualization
- L270 _public member_ `bool bForceRebuildEncodingVisualization = false;`
- L274 _public member_ `bool bCanDrawEncodingVisualization = false;` — `UPROPERTY(Transient)` — Temp state controlled by the editor mode which says if the encoding visualization can be drawn
- L278 _public member_ `bool bDrawEncodingVisualization = true;` — `UPROPERTY(EditAnywhere, Category = "Encoding Visualization", meta = (EditCondition = "bCanDrawEncodingVisualization", HideEditConditionToggle))` — If to draw the encoding visualization in the scene
- L282 _public member_ `bool bDrawSharedEncodingVisualization = false;` — `UPROPERTY(EditAnywhere, Category = "Encoding Visualization", meta = (EditCondition = "bCanDrawEncodingVisualization && bDrawEncodingVisualization", HideEditConditionToggle))` — If to draw the encoding visualization in a shared axis
- L286 _public member_ `float DrawEncodingVisualizationOpacity = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Encoding Visualization", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bCanDrawEncodingVisualization && bDrawEncodingVisualization", HideEditConditionToggle))` — Visualization encoding opacity
- L290 _public member_ `float DrawEncodingVisualizationThickness = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Encoding Visualization", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bCanDrawEncodingVisualization && bDrawEncodingVisualization", HideEditConditionToggle))` — Visualization encoding line thickness
- L294 _public member_ `float DrawEncodingVisualizationScale = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Encoding Visualization", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bCanDrawEncodingVisualization && bDrawEncodingVisualization", HideEditConditionToggle))` — Visualization encoding overall scale
- L298 _public member_ `float DrawEncodingVisualizationHeight = 300.0f;` — `UPROPERTY(EditAnywhere, Category = "Encoding Visualization", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bCanDrawEncodingVisualization && bDrawEncodingVisualization", HideEditConditionToggle))` — Visualization encoding height offset

#### class `UAnimGenAutoEncoderTrainingSettings`  
`class UAnimGenAutoEncoderTrainingSettings : public UObject, public IBoneReferenceSkeletonProvider`  
_L306-495_
- reflection: `UCLASS()`
- inherits: `UObject,IBoneReferenceSkeletonProvider`
- desc: Class containing all the UAnimGenAutoEncoder Editor window training settings
- L316 _public prototype_ `void ForceRefresh();` — `UFUNCTION(CallInEditor, Category = "Data", DisplayName = "Refresh")` — Forces the Update function to refresh the internal state
- L319 _public prototype_ `void LoadDatabaseAsync();` — Load the current database.
- L322 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& Event) override;` — We use this async load changes to Database
- L330 _public member_ `TSoftObjectPtr<UAnimDatabase> Database = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Input database to train the network with
- L334 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Data")` — Frame ranges in the database to use for training. Leave this as None to train on the full database
- L339 _public member_ `bool bForceRefresh = false;` — Flag to force refresh the query during update
- L342 _public member_ `int32 DatabaseContentHash = 0;` — This hash is used to detect when the database might have changed and re-run the query
- L345 _public member_ `FAnimDatabaseFrameRanges QueryRanges;` — Query Ranges object for the current query
- L348 _public member_ `TArray<TSharedPtr<UE::AnimDatabase::Editor::FQueryEntry>> QueryEntries;` — List of UI entries for the current query
- L351 _public member_ `TArray<int32> SelectedRanges;` — Indices of all the currently selected ranges
- L354 _public member_ `int32 RangeIndentifierColorSeed = 1234;` — Seed used for the colors of the range identifiers
- L364 _public prototype_ `bool Update();` — Checks if QueryRanges needs updating, and if so updates it. returns true if QueryRanges was updated (and therefore the UI may need updating), otherwise false.
- L369 _private prototype_ `void UpdateQueryEntries();` — Internal function for updating the QueryEntries array from an updated QueryRanges
- L379 _public member_ `TArray<FBoneReference> ExcludedBones;` — `UPROPERTY(EditAnywhere, Category = "Data")` — List of bones to exclude from training
- L383 _public member_ `bool bExcludeVirtualBones = true;` — `UPROPERTY(EditAnywhere, Category = "Data", AdvancedDisplay)` — If to exclude virtual bones
- L387 _public member_ `float RootWeightMultiplier = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Data", AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0"))` — Increase this if the root motion is not being accurately reproduced
- L391 _public member_ `float BaseWeightMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Data", AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0"))` — Increase this if the network is not accurately reproducing bones at the end of joint chains
- L395 _public member_ `float AttributeWeightMultiplier = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Data", AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0"))` — Increase this if the attributes are not being accurately reproduced
- L401 _public member_ `TArray<FAnimDatabaseFrameAttributeEntry> FrameAttributes;` — `UPROPERTY(EditAnywhere, Category = "Data")` — List of Frame Attributes to train the network to reproduce
- L407 _public member_ `int32 EncodingSize = 150;` — `UPROPERTY(EditAnywhere, Category = "Network", meta = (ClampMin = "1", UIMin = "1"))` — The encoding size used by the auto-encoder to compress the pose
- L411 _public member_ `int32 HiddenUnitNum = 512;` — `UPROPERTY(EditAnywhere, Category = "Network", meta = (ClampMin = "1", UIMin = "1"))` — The number of hidden units used by the auto-encoder on each layer
- L415 _public member_ `int32 LayerNum = 2;` — `UPROPERTY(EditAnywhere, Category = "Network", meta = (ClampMin = "1", UIMin = "1"))` — The number of layers used by the encoder and decoder networks
- L424 _public member_ `bool bUseCompressedLinearLayers = true;` — `UPROPERTY(EditAnywhere, Category = "Network", AdvancedDisplay)` — If the auto-encoder should use compressed learning layers. This reduces the memory use by half at some very small cost to reproduction accuracy.
- L428 _public member_ `EAnimGenActivationFunction ActivationFunction = EAnimGenActivationFunction::GELU;` — `UPROPERTY(EditAnywhere, Category = "Network", AdvancedDisplay)` — The activation function used by the auto-encoder
- L432 _public member_ `EAnimGenWeightInit WeightInit = EAnimGenWeightInit::Uniform;` — `UPROPERTY(EditAnywhere, Category = "Network", AdvancedDisplay)` — Network weight initialization method
- L441 _public member_ `int32 NumberOfIterations = 250000;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "1", UIMin = "1"))` — The number of iterations to train the auto-encoder for. Typical values are between 100000 and 2000000. Generally this does not need adjusting as 250000 is sufficient
- L445 _public member_ `float LearningRate = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Learning rate. Typical values are between 0.001 and 0.0001. Reduce if training is unsable. Generally this does not need adjusting.
- L453 _public member_ `int32 BatchSize = 512;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "1", UIMin = "1", UIMax = "4096"))` — Batch size to use for training. Smaller values can sometimes produce better results at the cost of slowing down training. Large batch sizes are much more computationally efficient when training on the GPU. Reduce this if you are getting GPU out-of-memory errors during training. Generally this should not need adjusting.
- L460 _public member_ `bool bEnableLogging = false;` — `UPROPERTY(EditAnywhere, Category = "Training")` — If to enable logging to the UE log in the training subprocess. Enable this if training is failing for an unknown reason as it will allow you to check the log for errors.
- L464 _public member_ `bool bEnableTensorboard = false;` — `UPROPERTY(EditAnywhere, Category = "Training")` — If to enable logging to TensorBoard in the intermediate directory. This can slow down training but gives important analytics.
- L470 _public member_ `int32 RandomSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "Training", AdvancedDisplay, meta = (ClampMin = "0", UIMin = "0"))` — The seed used for any random sampling the trainer will perform, e.g. for weight initialization.
- L474 _public member_ `int32 WarmupIterations = 1000;` — `UPROPERTY(EditAnywhere, Category = "Training", AdvancedDisplay, meta = (ClampMin = "1", UIMin = "1"))` — The number of learning rate warm-up iterations to apply. Stabilizes the beginning of training.
- L478 _public member_ `EAnimGenTrainingDevice Device = EAnimGenTrainingDevice::GPU;` — `UPROPERTY(EditAnywhere, Category = "Training", AdvancedDisplay)` — The device to train on.
- L485 _public member_ `TObjectPtr<UAnimDatabaseDebugDraw> DatabaseDebugDrawer;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Debug Draw")` — Custom database debug draw object that can be used to add additional debug draw behavior
- L489 _public member_ `TObjectPtr<UAnimGenAutoEncoderDebugDraw> AutoEncoderDebugDrawer;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Debug Draw")` — Custom debug draw object that can be used to add additional debug draw behavior
- L494 _public prototype_ `USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;`

#### class `UAnimGenAutoEncoder`  
`class UAnimGenAutoEncoder : public UDataAsset`  
_L506-777_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UDataAsset`
- desc: AnimGen AutoEncoder This asset can be used to learn a compact vector encoding of poses (and their velocities) in conjunction with the AnimDatabase. This compact vector encoding is useful for downstream machine learning tasks since it allows them to work in an abstract space rather than dealing directly with the pose representation.
- L512 _private prototype_ `UAnimGenAutoEncoder(const FObjectInitializer& ObjectInitializer);`
- L518 _public prototype_ `bool IsValid() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Check if the AutoEncoder is valid and trained
- L522 _public prototype_ `void Invalidate();` — `UFUNCTION(BlueprintCallable, Category = "AnimGen")` — Invalidate the AutoEncoder and reset back to a default state
- L526 _public prototype_ `int32 GetEncodingSize() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the encoding size used by the AutoEncoder
- L530 _public prototype_ `int32 GetPoseVectorSize() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the pose vector size used by the AutoEncoder
- L536 _public prototype_ `int32 GetBoneNum() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the number of bones used by the AutoEncoder
- L540 _public prototype_ `FName GetBoneName(const int32 BoneIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the bone name for a given AutoEncoder bone index
- L544 _public prototype_ `const TArray<FName>& GetBoneNames() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the array of bone names for the AutoEncoder
- L548 _public prototype_ `int32 FindBoneIndex(const FName BoneName) const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Finds the AutoEncoder bone index corresponding to a bone name
- L552 _public prototype_ `void FindBoneIndices(TArray<int32>& OutBoneIndices, const TArray<FName>& BoneInBoneNamesNames) const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Finds the AutoEncoder bone indices corresponding to the given bone names
- L553 _public prototype_ `void FindBoneIndicesFromArrayViews(TArrayView<int32> OutBoneIndices, const TArrayView<const FName> InBoneNames) const;`
- L557 _public prototype_ `const TArray<int32>& GetBoneParents() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the array of bone parent indices for the AutoEncoder
- L561 _public prototype_ `int32 GetBoneParent(const int32 BoneIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the parent for a given AutoEncoder bone index
- L567 _public prototype_ `int32 GetAttributeNum() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the number of attributes this AutoEncoder is trained on
- L571 _public prototype_ `FName GetAttributeName(const int32 AttributeIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the name of the attribute with the given index
- L575 _public prototype_ `EAnimDatabaseAttributeType GetAttributeType(const int32 AttributeIdx) const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets the type of the attribute with the given index
- L579 _public prototype_ `int32 FindAttributeIndex(const FName AttributeName) const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Finds the attribute index for a given name
- L583 _public prototype_ `const TArray<FName>& GetAttributeNames() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets an array of all of the trained attribute names
- L587 _public prototype_ `const TArray<EAnimDatabaseAttributeType>& GetAttributeTypes() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets an array of all of the trained attribute types
- L596 _public prototype_ `int32 GetContentHash() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Gets a hash value which can be used to test if the underlying content of the auto-encoder networks has changed. This hash should not be relied on for detecting changes with certainty, and so should only be used for non-critical purposes (e.g. UI updates).
- L601 _public prototype_ `void ToPoseVectors( const TLearningArrayView<2, float> OutPoseVectors, const UE::AnimDatabase::FPoseDataConstView& InPoseData) const;` — Converts the given pose data to pose vectors according to this AutoEncoder
- L606 _public prototype_ `void ToPoseVectors( const TLearningArrayView<2, float> OutPoseVectors, const UE::AnimDatabase::FPoseDataConstView& InPoseData, const UE::Learning::FIndexSet BoneIndices) const;` — Converts the given pose data to pose vectors according to this AutoEncoder
- L612 _public prototype_ `void FromPoseVectors( const UE::AnimDatabase::FPoseDataView& OutPoseData, const TLearningArrayView<2, const float> InPoseVectors, const TLearningArrayView<1, const FVector> InRootLocations, const TLearningArrayView<1, const FQuat4f> InRootRotations) const;` — Get the pose data from the given pose vectors according to this AutoEncoder
- L627 _public prototype_ `void SetDefaultPoseData( const UE::AnimDatabase::FPoseDataView& OutPoseData) const;` — Sets the given pose data to the default pose of this AutoEncoder
- L631 _public prototype_ `void SetDefaultPoseData( const UE::AnimDatabase::FPoseDataView& OutPoseData, const UE::Learning::FIndexSet BoneIndices) const;` — Sets the given pose data to the default pose of this AutoEncoder
- L636 _public prototype_ `void NormalizePoseVectors(TLearningArrayView<2, float> InOutPoseVectors) const;` — Normalizes the given pose vectors according to this AutoEncoder
- L639 _public prototype_ `void DenormalizePoseVectors(TLearningArrayView<2, float> InOutPoseVectors) const;` — Denormalizes the given pose vectors according to this AutoEncoder
- L642 _public prototype_ `void ClampPoseVectors(TLearningArrayView<2, float> InOutPoseVectors) const;` — Clamps the given pose vectors according to this AutoEncoder
- L648 _public member_ `TObjectPtr<ULearningNeuralNetworkData> EncoderNetwork = nullptr;` — `UPROPERTY(Instanced)` — Encoder Network
- L652 _public member_ `TObjectPtr<ULearningNeuralNetworkData> DecoderNetwork = nullptr;` — `UPROPERTY(Instanced)` — Decoder Network
- L658 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY()` — Names of the bones used to train the auto-encoder
- L662 _public member_ `TArray<int32> BoneParents;` — `UPROPERTY()` — Parents of the bones used to train the auto-encoder
- L666 _public member_ `TArray<FVector3f> DefaultBoneLocations;` — `UPROPERTY()` — Default bone locations when this value is constant in the dataset
- L670 _public member_ `TArray<FQuat4f> DefaultBoneRotations;` — `UPROPERTY()` — Default bone rotations when this value is constant in the dataset
- L674 _public member_ `TArray<FVector3f> DefaultBoneScales;` — `UPROPERTY()` — Default bone scales when this value is constant in the dataset
- L678 _public member_ `TArray<int32> AutoEncodedBoneLocationIndices;` — `UPROPERTY()` — Indices of bone locations that are encoded/decoded by this AutoEncoder
- L682 _public member_ `TArray<int32> AutoEncodedBoneRotationIndices;` — `UPROPERTY()` — Indices of bone rotations that are encoded/decoded by this AutoEncoder
- L686 _public member_ `TArray<int32> AutoEncodedBoneScaleIndices;` — `UPROPERTY()` — Indices of bone scales that are encoded/decoded by this AutoEncoder
- L690 _public member_ `TArray<int32> AutoEncodedRequiredBoneIndices;` — `UPROPERTY()` — Indices of all of the bones encoded/decoded by this AutoEncoder
- L696 _public member_ `TArray<float> PoseVectorOffset;` — `UPROPERTY()` — Normalization offset for pose vectors
- L700 _public member_ `TArray<float> PoseVectorScale;` — `UPROPERTY()` — Normalization scale for pose vectors
- L704 _public member_ `TArray<float> PoseVectorMin;` — `UPROPERTY()` — Minimum pose vector for clamping
- L708 _public member_ `TArray<float> PoseVectorMax;` — `UPROPERTY()` — Maximum pose vector for clamping
- L714 _public member_ `TArray<FName> AttributeNames;` — `UPROPERTY()` — Names of the attributes encoded/decoded by this AutoEncoder
- L718 _public member_ `TArray<EAnimDatabaseAttributeType> AttributeTypes;` — `UPROPERTY()` — Types of the attributes encoded/decoded by this AutoEncoder
- L726 _public member_ `TObjectPtr<USkeleton> TrainedSkeleton;` — `UPROPERTY(VisibleAnywhere, Category = "Trained")` — The skeleton used for training
- L730 _public member_ `TArray<FAnimDatabaseFrameAttributeEntry> TrainedFrameAttributes;` — `UPROPERTY(VisibleAnywhere, Category = "Trained")` — The Frame Attributes used for training
- L734 _public member_ `TArray<FName> TrainedBoneLocations;` — `UPROPERTY(VisibleAnywhere, Category = "Trained")` — List of bone names where the translation is output by the auto-encoder
- L738 _public member_ `TArray<FName> TrainedBoneRotations;` — `UPROPERTY(VisibleAnywhere, Category = "Trained")` — List of bone names where the rotation is output by the auto-encoder
- L742 _public member_ `TArray<FName> TrainedBoneScales;` — `UPROPERTY(VisibleAnywhere, Category = "Trained")` — List of bone names where the scale is output by the auto-encoder
- L746 _public member_ `int32 TrainedContentHash = 0;` — `UPROPERTY()` — The content hash of the frame ranges used for training
- L752 _public member_ `int32 EncoderSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (ForceUnits = "Kilobytes"))` — Current size of the trained encoder in kilobytes
- L756 _public member_ `int32 DecoderSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (ForceUnits = "Kilobytes"))` — Current size of the trained decoder in kilobytes
- L760 _public member_ `int32 EncoderInferenceTime = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Statistics", meta = (ForceUnits = "Microseconds"))` — Current approximate inference time for the encoder in microseconds
- L764 _public member_ `int32 DecoderInferenceTime = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Statistics", meta = (ForceUnits = "Microseconds"))` — Current approximate inference time for the decoder in microseconds
- L770 _public member_ `TObjectPtr<UAnimGenAutoEncoderViewportSettings> ViewportSettings;` — `UPROPERTY(Instanced)` — Editor-only object containing the viewport settings for the editor window
- L774 _public member_ `TObjectPtr<UAnimGenAutoEncoderTrainingSettings> TrainingSettings;` — `UPROPERTY(Instanced)` — Editor-only object containing the training settings for the editor window

#### class `UAnimGenAutoEncoderDebugDraw_ContactTimings`  
`class UAnimGenAutoEncoderDebugDraw_ContactTimings : public UAnimGenAutoEncoderDebugDraw`  
_L782-835_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Contact Timings Debug Draw"))`
- inherits: `UAnimGenAutoEncoderDebugDraw`
- desc: Debug Draw class for drawing contact timings
- L792 _public member_ `FName LeftToeBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the left toe bone
- L796 _public member_ `FName RightToeBoneName = TEXT("bal` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the right toe bone
- L800 _public member_ `FName LeftContactCurveAttribute = TEXT("con` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the left contact curve attribute
- L804 _public member_ `FName RightContactCurveAttribute = TEXT("con` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the right contact curve attribute
- L808 _public member_ `float ContactCircleRadius = 15.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ForceUnits = "cm"))` — Radius for the circle to display to show contacts
- L816 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InOriginalPoseState, const FAnimDatabasePoseState& InReconstructedPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor, const FLinearColor& OriginalColor, const FLinearColor& ReconstructedColor) override;`

#### class `UAnimGenAutoEncoderDebugDraw_Attributes`  
`class UAnimGenAutoEncoderDebugDraw_Attributes : public UAnimGenAutoEncoderDebugDraw`  
_L839-880_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Attributes"))`
- inherits: `UAnimGenAutoEncoderDebugDraw`
- desc: Debug Draw class for drawing attributes and their reproductions
- L849 _public member_ `float VerticalSpacing = 16.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Spacing for text lines vertically
- L853 _public member_ `float PropertyHorizontalOffset = 250.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Pixel offset to display the properties
- L861 _public prototype_ `virtual void DrawDebug_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimDatabasePoseState& InOriginalPoseState, const FAnimDatabasePoseState& InReconstructedPoseState, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges, const FTransform& RangeViewportTransform, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor, const FLinearColor& OriginalColor, const FLinearColor& ReconstructedColor) override;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API ANIMGEN_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace AnimDatabase` (scope `UE`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGen/Public/AnimGenBehavior.h` (Public)


#### class `UAnimGenBehavior`  
`class UAnimGenBehavior : public UObject`  
_L25-59_
- reflection: `UCLASS(Abstract, HideDropdown, EditInlineNew, DefaultToInstanced, CollapseCategories, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: A Behavior represents a specific control structure that can be used to control a character (for example - a trajectory to follow, a target point to move towards). To define a behavior it is required to inherit from this class and to provide the "SpecifyControl", and "MakeControlSets" functions. The "DrawDebugControl" function may also be provided to do debug drawing in the training viewport.
- L35 _public prototype_ `FAnimGenControlSchemaElement SpecifyControl(UPARAM(ref) FAnimGenControlSchema& InControlSchema) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "AnimGen", meta = (ForceAsFunction))` — Specify the control structure used by this behavior.
- L39 _public prototype_ `void MakeControlSets(TArray<FAnimGenControlSet>& OutControlSets, UPARAM(ref) FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "AnimGen", meta = (ForceAsFunction))` — Make the control sets used for training from the given database and frame ranges in the database
- L43 _public prototype_ `void DrawDebugControl( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AnimGen", meta = (ForceAsFunction))` — Draw debug the current frame in the training data

#### class `UAnimGenBehavior_Uncontrolled`  
`class UAnimGenBehavior_Uncontrolled : public UAnimGenBehavior`  
_L63-76_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Uncontrolled Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior for uncontrolled generation. Produces a random-walk of the dataset.
- L71 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L73 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`

#### class `UAnimGenBehavior_Idle`  
`class UAnimGenBehavior_Idle : public UAnimGenBehavior_Uncontrolled`  
_L80-83_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Idle Behavior"))`
- inherits: `UAnimGenBehavior_Uncontrolled`
- desc: Behavior for idling.

#### class `UAnimGenBehavior_TrajectoryFollow`  
`class UAnimGenBehavior_TrajectoryFollow : public UAnimGenBehavior`  
_L87-137_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Trajectory Follow Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior for following a trajectory which can either be generated from Mover/CharacterMovementComponent or a path to follow
- L97 _public member_ `float TrajectoryFutureTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Future lookahead time for the trajectory
- L101 _public member_ `float TrajectoryPastTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Past time for the trajectory
- L105 _public member_ `int32 TrajectorySampleNum = 4;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Number of samples to use for the trajectory
- L109 _public member_ `FVector TrajectoryForwardVector = FVector::RightVector;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Local root forward vector for the trajectory
- L117 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L119 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`
- L121 _public prototype_ `virtual void DrawDebugControl_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const override;`

#### class `UAnimGenBehavior_VelocityFollow`  
`class UAnimGenBehavior_VelocityFollow : public UAnimGenBehavior`  
_L141-169_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Velocity Follow Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior for following a velocity and angular velocity. More useful for offline generation.
- L149 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L151 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`
- L153 _public prototype_ `virtual void DrawDebugControl_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const override;`

#### class `UAnimGenBehavior_MoveToTarget`  
`class UAnimGenBehavior_MoveToTarget : public UAnimGenBehavior`  
_L173-201_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Move to Target Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior for moving toward a target with an optional facing direction
- L181 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L183 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`
- L185 _public prototype_ `virtual void DrawDebugControl_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const override;`

#### class `UAnimGenBehavior_TrajectoryInteraction`  
`class UAnimGenBehavior_TrajectoryInteraction : public UAnimGenBehavior`  
_L208-278_
- reflection: `UCLASS(BlueprintType, Blueprintable, DontCollapseCategories, meta = (DisplayName = "Trajectory Interaction Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior for following a trajectory while also interacting with an object or prop. This is useful for networked prop interactions where the trajectory may be coming from a montage .
- L218 _public member_ `float TrajectoryFutureTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory")` — Future lookahead time for the trajectory
- L222 _public member_ `float TrajectoryPastTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory")` — Past time for the trajectory
- L226 _public member_ `int32 TrajectorySampleNum = 4;` — `UPROPERTY(EditAnywhere, Category = "Trajectory")` — Number of samples to use for the trajectory
- L230 _public member_ `FVector TrajectoryForwardVector = FVector::RightVector;` — `UPROPERTY(EditAnywhere, Category = "Trajectory")` — Local root forward vector for the trajectory
- L234 _public member_ `FName InteractionBoneName = TEXT("att` — `UPROPERTY(EditAnywhere, Category = "Interaction")` — Name of bone used for interaction
- L238 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> InteractionRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Interaction")` — Ranges where interaction is valid
- L242 _public member_ `FVector InteractionForwardVector = FVector::ForwardVector;` — `UPROPERTY(EditAnywhere, Category = "Interaction")` — Forward Vector for the interaction facing direction
- L246 _public member_ `bool bUseMirroredInteractionForwardVector = false;` — `UPROPERTY(EditAnywhere, Category = "Interaction")` — If to use a separate forward vector for mirrored data
- L250 _public member_ `FVector InteractionMirroredForwardVector = FVector(-1, 0, 0);` — `UPROPERTY(EditAnywhere, Category = "Interaction", meta = (EditCondition = "bUseMirroredInteractionForwardVector", HideEditConditionToggle))` — Separate Forward Vector for the interaction facing direction when mirrored
- L258 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L260 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`
- L262 _public prototype_ `virtual void DrawDebugControl_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const override;`

#### class `UAnimGenBehavior_Tagged`  
`class UAnimGenBehavior_Tagged : public UAnimGenBehavior`  
_L282-328_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Tagged Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior that allows a user to supply tags to control the style of a sub-behavior.
- L292 _public member_ `TObjectPtr<UAnimGenBehavior> Behavior;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Sub-behavior
- L296 _public member_ `TArray<FAnimDatabaseFrameRangesEntry> TagRanges;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — List of tags with associated frame ranges
- L300 _public member_ `FVector TagDebugDrawOffset = FVector(0.0, 0.0, 220.0f);` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Offset to debug draw the current tags
- L308 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L310 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`
- L312 _public prototype_ `virtual void DrawDebugControl_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const override;`

#### class `UAnimGenBehavior_Optional`  
`class UAnimGenBehavior_Optional : public UAnimGenBehavior`  
_L332-374_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Optional Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior that allows a user to optionally provide controls to another Behavior.
- L342 _public member_ `TObjectPtr<UAnimGenBehavior> Behavior;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Sub-behavior
- L346 _public member_ `int32 EncodingSize = 128;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = "1", ClampMin = "1"))` — Size to encode the sub-behaviors controls to
- L354 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L356 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`
- L358 _public prototype_ `virtual void DrawDebugControl_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const override;`

#### class `UAnimGenBehavior_Encoded`  
`class UAnimGenBehavior_Encoded : public UAnimGenBehavior`  
_L378-428_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Encoded Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior that encodes the controls of some sub-behavior.
- L388 _public member_ `TObjectPtr<UAnimGenBehavior> Behavior;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Settings")` — Sub-behavior
- L392 _public member_ `int32 EncodingSize = 128;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = "1", ClampMin = "1"))` — Size to encode the sub-behaviors controls to
- L396 _public member_ `int32 HiddenLayerNum = 1;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (UIMin = "1", ClampMin = "1"))` — Number of layers to use to encode the sub-behavior controls
- L400 _public member_ `EAnimGenActivationFunction ActivationFunction = EAnimGenActivationFunction::ELU;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Activation function to use to encode the sub-behavior controls
- L408 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L410 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`
- L412 _public prototype_ `virtual void DrawDebugControl_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const override;`

#### struct `FAnimGenBehaviorEntry`  
`struct FAnimGenBehaviorEntry`  
_L432-449_
- reflection: `USTRUCT(BlueprintType)`
- desc: Entry specifying a behavior
- L440 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Behavior name
- L444 _public member_ `TObjectPtr<UAnimGenBehavior> Behavior;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Entry")` — Behavior object
- L448 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Entry")` — Frame ranges to use for behavior

#### class `UAnimGenBehavior_Multi`  
`class UAnimGenBehavior_Multi : public UAnimGenBehavior`  
_L453-491_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "Multi Behavior"))`
- inherits: `UAnimGenBehavior`
- desc: Behavior made up of multiple other behaviors - user can also provide some tags to control the style.
- L463 _public member_ `TArray<FAnimGenBehaviorEntry> Behaviors;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Different potential sub-behaviors
- L471 _public prototype_ `virtual FAnimGenControlSchemaElement SpecifyControl_Implementation(FAnimGenControlSchema& InControlSchema) const override;`
- L473 _public prototype_ `virtual void MakeControlSets_Implementation(TArray<FAnimGenControlSet>& OutControlSets, FAnimGenControlObject& InControlObject, const UAnimDatabase* InDatabase, const FAnimDatabaseFrameRanges& InFrameRanges) const override;`
- L475 _public prototype_ `virtual void DrawDebugControl_Implementation( const FDebugDrawer& Drawer, const FDebugDrawer& CanvasDrawer, const FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement InControlObjectElement, const FAnimDatabasePoseState& InPoseState, const UAnimDatabase* InDatabase, const UAnimGenAutoEncoder* InAutoEncoder, const int32 CharacterIdx, const int32 SequenceIdx, const float SequenceTime, const int32 RangeStart, const int32 RangeLength, const FLinearColor& IdentifierColor) const override;`

#### class `UAnimGenBehaviorLibrary`  
`class UAnimGenBehaviorLibrary : public UBlueprintFunctionLibrary`  
_L495-740_
- reflection: `UCLASS(BlueprintType, meta = (BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint library of helper functions for making and testing behaviors including functions for preparing, processing, and making controls
- L503 _public prototype_ `static FAnimGenControlObjectElement MakeUncontrolledBehaviorControl(UPARAM(ref) FAnimGenControlObject& InControlObject);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Make a control object element for the Uncontrolled Behavior
- L507 _public prototype_ `static FAnimGenControlObjectElement MakeIdleBehaviorControl(UPARAM(ref) FAnimGenControlObject& InControlObject);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Make a control object element for the Idle Behavior
- L511 _public prototype_ `static FAnimGenControlObjectElement MakeTrajectoryFollowBehaviorControl( UPARAM(ref) FAnimGenControlObject& InControlObject, const FTransformTrajectory& TransformTrajectory, const FTransform& RootBoneTransform, const int32 InTrajectorySampleNum = 4, const float InTrajectoryFutureTime = 1.0f, const float InTrajectoryPastTime = 0.0f, const FVector InTrajectoryForwardVector = FVector::RightVector);` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AutoCreateRefTerm = "TransformTrajectory, RootBoneTransform"))` — Make a control object element for the Trajectory Following Behavior
- L522 _public prototype_ `static FAnimGenControlObjectElement MakeMoveToTargetBehaviorControl( UPARAM(ref) FAnimGenControlObject& InControlObject, const FVector TargetLocation, const FVector TargetDirection, const bool bUseTargetDirection, const FTransform& RootBoneTransform);` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AutoCreateRefTerm = "RootBoneTransform"))` — Make a control object element for the Move To Target Behavior
- L531 _public prototype_ `static FAnimGenControlObjectElement MakeTrajectoryInteractionBehaviorControl( UPARAM(ref) FAnimGenControlObject& InControlObject, const FTransformTrajectory& TransformTrajectory, const FTransform& RootBoneTransform, const FVector InteractionLocation = FVector::ZeroVector, const FVector InteractionDirection = FVector::ForwardVector, const bool bInteractionActive = false, const int32 InTrajectorySampleNum = 4, const float InTrajectoryFutureTime = 1.0f, const float InTrajectoryPastTime = 0.0f, const FVector InTrajectoryForwardVector = FVector::RightVector);` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AutoCreateRefTerm = "TransformTrajectory, RootBoneTransform"))` — Make a control object element for the Trajectory Interaction Behavior
- L545 _public prototype_ `static FAnimGenControlObjectElement MakeTaggedBehaviorControl( UPARAM(ref) FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement& BehaviorControlElement, const TArray<FName>& DesiredTags);` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AutoCreateRefTerm = "DesiredTags"))` — Make a control object element for the Tagged Behavior
- L550 _public prototype_ `static FAnimGenControlObjectElement MakeTaggedBehaviorControlFromArrayView( FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement& BehaviorControlElement, const TArrayView<const FName> DesiredTags);`
- L557 _public prototype_ `static FAnimGenControlObjectElement MakeMultiBehaviorControl( UPARAM(ref) FAnimGenControlObject& InControlObject, const FName Behavior, const FAnimGenControlObjectElement& BehaviorControlElement);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Make a control object element for the Multi Behavior
- L564 _public prototype_ `static FAnimGenControlObjectElement MakeValidOptionalBehaviorControl( UPARAM(ref) FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement& BehaviorControlElement);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Make a valid control object element for the Optional Behavior
- L570 _public prototype_ `static FAnimGenControlObjectElement MakeNullOptionalBehaviorControl( UPARAM(ref) FAnimGenControlObject& InControlObject);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Make a null control object element for the Optional Behavior
- L574 _public prototype_ `static FAnimGenControlObjectElement MakeValidOptionalBehaviorControlOnCondition( UPARAM(ref) FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement& BehaviorControlElement, const bool bCondition);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")`
- L581 _public prototype_ `static FAnimGenControlObjectElement MakeEncodedBehaviorControl( UPARAM(ref) FAnimGenControlObject& InControlObject, const FAnimGenControlObjectElement& BehaviorControlElement);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Make a control object element for the Encoded Behavior
- L589 _public prototype_ `static FVector ProjectOntoFloor(const FVector Location, const float FloorHeight = 0.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Projects a location onto the floor plane given by the provided height
- L593 _public prototype_ `static FVector ClampToMaxDistanceFromVector( const FVector InVector, const FVector FromVector, const float MaxDistance = 100.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Clamps one vector to some maximum distance from another vector
- L600 _public prototype_ `static void ApplyStickDeadzoneAndSensitivity( FVector& OutAxis, FVector& OutDirection, float& OutLength, bool& bOutNotInDeadzone, const FVector Axis, const float Deadzone = 0.2f, const float Sensitivity = 2.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Apply proper dead-zone and sensitivity treatment to stick input
- L611 _public prototype_ `static float ApplyTriggerSensitivity(const float Trigger, const float Sensitivity = 2.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Apply sensitivity to a trigger value
- L615 _public prototype_ `static bool IsStickNotInDeadzone(const FVector Axis, const float Deadzone = 0.2f);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Check if the stick is not in the deadzone
- L619 _public prototype_ `static bool IsStickInDeadzone(const FVector Axis, const float Deadzone = 0.2f);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Check if the stick is in the deadzone
- L623 _public prototype_ `static FRotator DesiredDirectionToRotation(const FVector Direction);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Convert a desired direction to a desired rotation
- L627 _public prototype_ `static FQuat DesiredDirectionToRotationQuat(const FVector Direction);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Convert a desired direction to a desired rotation quaternion
- L631 _public prototype_ `static void UpdateDesiredVelocityFromAxis( UPARAM(ref) FVector& DesiredVelocity, const FVector Axis, const float VelocitySpeed = 150.0f, const float Deadzone = 0.2f, const float Sensitivity = 2.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Update the desired velocity from a stick axis
- L640 _public prototype_ `static void UpdateDesiredRotationFromAxis( UPARAM(ref) FRotator& DesiredRotation, const FVector Axis, const float Deadzone = 0.2f, const float Sensitivity = 2.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Update the desired rotation from a stick axis
- L648 _public prototype_ `static void UpdateDesiredVelocityAndRotationFromAxes( UPARAM(ref) FVector& DesiredVelocity, UPARAM(ref) FRotator& DesiredRotation, const FVector VelocityAxis, const FVector FacingAxis, const float VelocitySpeed = 150.0f, const float Deadzone = 0.2f, const float Sensitivity = 2.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Update the desired velocity and rotation from two stick axes
- L659 _public prototype_ `static void UpdateDesiredVelocityAndRotationFromAxisAndCameraTrigger( UPARAM(ref) FVector& DesiredVelocity, UPARAM(ref) FRotator& DesiredRotation, const FRotator CameraYawRotation, const FVector VelocityAxis, const float FacingTrigger, const float MinimumSpeed = 75.0f, const float MaximumSpeed = 150.0f, const float Deadzone = 0.2f, const float Sensitivity = 2.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Update the desired velocity and rotation from a stick axes and camera trigger
- L672 _public prototype_ `static int32 FindNearestIndexInFloatArray(const TArray<float>& Values, const float Value);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Find the index of the most similar value in an array of floats
- L676 _public prototype_ `static FName CycleNameInArray(const TArray<FName>& Names, const FName CurrentName, const int32 Steps = 1);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Cycle through an array of names and return the current name
- L677 _public prototype_ `static FName CycleNameInArrayView(const TArrayView<const FName> Names, const FName CurrentName, const int32 Steps = 1);`
- L681 _public prototype_ `static bool LocationDifferenceBelowThreshold( const FVector CurrentLocation, const FVector TargetLocation, const float LocationThreshold = 25.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Check if two locations are within some distance threshold
- L688 _public prototype_ `static bool LocationAndDirectionDifferenceBelowThreshold( const FVector CurrentLocation, const FVector CurrentDirection, const FVector TargetLocation, const FVector TargetDirection, const float LocationThreshold = 25.0f, const float DirectionThresoldAngle = 10.0f);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Check if locations and directions are within some distance and angle threshold (in degrees)
- L700 _public prototype_ `static FVector ApplySimpleAvoidanceToVelocity( const FVector Velocity, const TArray<AActor*>& Actors, const AActor* SelfActor, const float MinAvoidanceRadius = 25.0f, const float MaxAvoidanceRadius = 150.0f, const float AvoidanceVelocity = 200.0f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Applies a simple avoidance heuristic to a movement velocity
- L708 _public prototype_ `static FVector ApplySimpleAvoidanceToVelocityArrayView( const FVector Velocity, const TArrayView<AActor* const> Actors, const AActor* SelfActor, const float MinAvoidanceRadius = 25.0f, const float MaxAvoidanceRadius = 150.0f, const float AvoidanceVelocity = 200.0f);`
- L718 _public prototype_ `static bool CanLookAtActor( const FVector LookAtDirection, const AActor* Actor, const AActor* SelfActor, const float DistanceThreshold = 200.0f, const float DotAngleThreshold = 0.75f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Checks if an actor can look at another actor according to some distance and angle thresholds
- L727 _public prototype_ `static AActor* FindLookAtActor( const FVector LookAtDirection, const TArray<AActor*>& Actors, const AActor* SelfActor, const float DistanceThreshold = 200.0f, const float DotAngleThreshold = 0.75f);` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen")` — Finds an actor to look-at according to some distance and angle thresholds
- L734 _public prototype_ `static AActor* FindLookAtActorArrayView( const FVector LookAtDirection, const TArray<AActor*>& Actors, const AActor* SelfActor, const float DistanceThreshold = 200.0f, const float DotAngleThreshold = 0.75f);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMGEN_API`

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGen/Public/AnimGenControl.h` (Public)


#### struct `FAnimGenControlSchemaElement`  
`struct FAnimGenControlSchemaElement`  
_L27-35_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint accessible version of a control schema element. Represents a single control type in the schema.
- L32 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom Serialization
- L34 _public member_ `UE::Learning::Observation::FSchemaElement SchemaElement;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimGenControlSchemaElement> : public TStructOpsTypeTraitsBase2<FAnimGenControlSchemaElement>`  
_L42-49_
- inherits: `TStructOpsTypeTraitsBase2<FAnimGenControlSchemaElement>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L45-48_

#### struct `FAnimGenControlObjectElement`  
`struct FAnimGenControlObjectElement`  
_L53-61_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint accessible version of a control object element. Represents a single instance of a control object type.
- L58 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom Serialization
- L60 _public member_ `UE::Learning::Observation::FObjectElement ObjectElement;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimGenControlObjectElement> : public TStructOpsTypeTraitsBase2<FAnimGenControlObjectElement>`  
_L68-75_
- inherits: `TStructOpsTypeTraitsBase2<FAnimGenControlObjectElement>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L71-74_

#### struct `UE::AnimGen::FControlSchema`  
`struct FControlSchema`  
_L80-84_
- desc: Wrapped FSchema object to include a lock to allow for BlueprintThreadSafe access
- L82 _public member_ `FSpinLock Lock;`
- L83 _public member_ `Learning::Observation::FSchema Schema;`

#### struct `UE::AnimGen::FControlObject`  
`struct FControlObject`  
_L87-91_
- desc: Wrapped FObject object to include a lock to allow for BlueprintThreadSafe access
- L89 _public member_ `FSpinLock Lock;`
- L90 _public member_ `Learning::Observation::FObject Object;`

#### class `UE::AnimGen::FSpinLockScope`  
`class FSpinLockScope`  
_L93-111_
- L96 _public function_ `UE_NODISCARD_CTOR explicit FSpinLockScope(FSpinLock& InLock) : Lock(InLock)`
- L102 _public function_ `~FSpinLockScope()`
- L108 _private member_ `FSpinLock& Lock;`

#### struct `FAnimGenControlSchema`  
`struct FAnimGenControlSchema`  
_L116-133_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint accessible version of a control schema
- L121 _public prototype_ `bool IsValid() const;` — Check if the schema is valid
- L124 _public prototype_ `bool IsElementValid(const FAnimGenControlSchemaElement& Element) const;` — Check if the given element is valid for this schema
- L127 _public prototype_ `void Invalidate();` — Invalidate the schema
- L130 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom Serialization
- L132 _public member_ `TSharedPtr<UE::AnimGen::FControlSchema, ESPMode::ThreadSafe> ObservationSchema;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimGenControlSchema> : public TStructOpsTypeTraitsBase2<FAnimGenControlSchema>`  
_L138-145_
- inherits: `TStructOpsTypeTraitsBase2<FAnimGenControlSchema>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L141-144_

#### struct `FAnimGenControlObject`  
`struct FAnimGenControlObject`  
_L149-166_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint accessible version of a control object
- L154 _public prototype_ `bool IsValid() const;` — Check if the control object is valid
- L157 _public prototype_ `bool IsElementValid(const FAnimGenControlObjectElement& Element) const;` — Check if the given element is valid for this control object
- L160 _public prototype_ `void Invalidate();` — Invalidate the control object
- L163 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom Serialization
- L165 _public member_ `TSharedPtr<UE::AnimGen::FControlObject, ESPMode::ThreadSafe> ObservationObject;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimGenControlObject> : public TStructOpsTypeTraitsBase2<FAnimGenControlObject>`  
_L171-178_
- inherits: `TStructOpsTypeTraitsBase2<FAnimGenControlObject>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L174-177_

#### enum `EAnimGenEitherControl`  
`enum class EAnimGenEitherControl : uint8`  
_L182-186_
- reflection: `UENUM(BlueprintType)`
- desc: Enum used to determine between two options in an Either control
- L184 _public enumerator_ `A`
- L185 _public enumerator_ `B`

#### enum `EAnimGenOptionalControl`  
`enum class EAnimGenOptionalControl : uint8`  
_L190-194_
- reflection: `UENUM(BlueprintType)`
- desc: Enum used to determine between null and valid in an Optional control
- L192 _public enumerator_ `Null`
- L193 _public enumerator_ `Valid`

#### struct `UE::AnimGen::FControlSetData`  
`struct FControlSetData`  
_L199-203_
- desc: Control set data contains the frame ranges in the database associated with the controls and each control element
- L201 _public member_ `UE::Learning::FFrameRangeSet FrameRangeSet;`
- L202 _public member_ `TArray<FAnimGenControlObjectElement> Controls;`

#### struct `FAnimGenControlSet`  
`struct FAnimGenControlSet`  
_L208-222_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint accessible version of a control set. Represents a set of controls for a set of frames in the database
- L213 _public prototype_ `TArrayView<const FAnimGenControlObjectElement> GetControls() const;` — Get the array of control object elements for this control set
- L216 _public prototype_ `bool IsValid() const;` — Check if this control set is valid
- L219 _public prototype_ `void Invalidate();` — Invalidate this control set
- L221 _public member_ `TSharedPtr<UE::AnimGen::FControlSetData, ESPMode::ThreadSafe> Data;`

#### class `UAnimGenControls`  
`class UAnimGenControls : public UBlueprintFunctionLibrary`  
_L226-1050_
- reflection: `UCLASS(BlueprintType, meta=(BlueprintThreadSafe))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library used for creating control schema elements, control object elements, and control sets
- L233 _public prototype_ `static FAnimGenControlSchema MakeControlSchema();` — `UFUNCTION(BlueprintCallable, Category = "AnimGen")`
- L236 _public prototype_ `static FAnimGenControlObject MakeControlObject();` — `UFUNCTION(BlueprintCallable, Category = "AnimGen")`
- L239 _public prototype_ `static void ResetControlSchema(UPARAM(ref) FAnimGenControlSchema& Schema);` — `UFUNCTION(BlueprintCallable, Category = "AnimGen")`
- L242 _public prototype_ `static void ResetControlObject(UPARAM(ref) FAnimGenControlObject& Object);` — `UFUNCTION(BlueprintCallable, Category = "AnimGen")`
- L245 _public prototype_ `static bool IsControlSchemaValid(const FAnimGenControlSchema& Schema);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")`
- L248 _public prototype_ `static bool IsControlObjectValid(const FAnimGenControlObject& Object);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")`
- L251 _public prototype_ `static bool ValidateControlObjectMatchesSchema( const FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement SchemaElement, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement ObjectElement);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")`
- L260 _public prototype_ `static FAnimGenControlSchemaElement SpecifyNullControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Null` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L263 _public prototype_ `static FAnimGenControlSchemaElement SpecifyContinuousControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 Size, const FName Tag = TEXT("Cont` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L266 _public prototype_ `static FAnimGenControlSchemaElement SpecifyNamedExclusiveDiscreteControl(UPARAM(ref) FAnimGenControlSchema& Schema, const TArray<FName>& ElementNames, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L267 _public prototype_ `static FAnimGenControlSchemaElement SpecifyNamedExclusiveDiscreteControlFromArrayView(UPARAM(ref) FAnimGenControlSchema& Schema, const TArrayView<const FName> ElementNames, const FName Tag = TEXT("Name`
- L270 _public prototype_ `static FAnimGenControlSchemaElement SpecifyNamedInclusiveDiscreteControl(UPARAM(ref) FAnimGenControlSchema& Schema, const TArray<FName>& ElementNames, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L271 _public prototype_ `static FAnimGenControlSchemaElement SpecifyNamedInclusiveDiscreteControlFromArrayView(UPARAM(ref) FAnimGenControlSchema& Schema, const TArrayView<const FName> ElementNames, const FName Tag = TEXT("Name`
- L274 _public prototype_ `static FAnimGenControlSchemaElement SpecifyExclusiveDiscreteControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 Size, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L277 _public prototype_ `static FAnimGenControlSchemaElement SpecifyInclusiveDiscreteControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 Size, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L280 _public prototype_ `static FAnimGenControlSchemaElement SpecifyCountControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Coun` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L283 _public prototype_ `static FAnimGenControlSchemaElement SpecifyStructControl(UPARAM(ref) FAnimGenControlSchema& Schema, const TMap<FName, FAnimGenControlSchemaElement>& Elements, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L286 _public prototype_ `static FAnimGenControlSchemaElement SpecifyStructControlFromArrays(UPARAM(ref) FAnimGenControlSchema& Schema, const TArray<FName>& ElementNames, const TArray<FAnimGenControlSchemaElement>& Elements, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L287 _public prototype_ `static FAnimGenControlSchemaElement SpecifyStructControlFromArrayViews(UPARAM(ref) FAnimGenControlSchema& Schema, const TArrayView<const FName> ElementNames, const TArrayView<const FAnimGenControlSchemaElement> Elements, const FName Tag = TEXT("Stru`
- L290 _public prototype_ `static FAnimGenControlSchemaElement SpecifyExclusiveUnionControl(UPARAM(ref) FAnimGenControlSchema& Schema, const TMap<FName, FAnimGenControlSchemaElement>& Elements, const int32 EncodingSize = 128, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L293 _public prototype_ `static FAnimGenControlSchemaElement SpecifyExclusiveUnionControlFromArrays(UPARAM(ref) FAnimGenControlSchema& Schema, const TArray<FName>& ElementNames, const TArray<FAnimGenControlSchemaElement>& Elements, const int32 EncodingSize = 128, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L295 _public prototype_ `static FAnimGenControlSchemaElement SpecifyExclusiveUnionControlFromArrayViews(UPARAM(ref) FAnimGenControlSchema& Schema, const TArrayView<const FName> ElementNames, const TArrayView<const FAnimGenControlSchemaElement> Elements, const int32 EncodingSize = 128, const FName Tag = TEXT("Excl`
- L298 _public prototype_ `static FAnimGenControlSchemaElement SpecifyInclusiveUnionControl(UPARAM(ref) FAnimGenControlSchema& Schema, const TMap<FName, FAnimGenControlSchemaElement>& Elements, const int32 AttentionEncodingSize = 32, const int32 AttentionHeadNum = 4, const int32 ValueEncodingSize = 32, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L301 _public prototype_ `static FAnimGenControlSchemaElement SpecifyInclusiveUnionControlFromArrays(UPARAM(ref) FAnimGenControlSchema& Schema, const TArray<FName>& ElementNames, const TArray<FAnimGenControlSchemaElement>& Elements, const int32 AttentionEncodingSize = 32, const int32 AttentionHeadNum = 4, const int32 ValueEncodingSize = 32, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L302 _public prototype_ `static FAnimGenControlSchemaElement SpecifyInclusiveUnionControlFromArrayViews(UPARAM(ref) FAnimGenControlSchema& Schema, const TArrayView<const FName> ElementNames, const TArrayView<const FAnimGenControlSchemaElement> Elements, const int32 AttentionEncodingSize = 32, const int32 AttentionHeadNum = 4, const int32 ValueEncodingSize = 32, const FName Tag = TEXT("Incl`
- L305 _public prototype_ `static FAnimGenControlSchemaElement SpecifyStaticArrayControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement Element, const int32 Num, const FName Tag = TEXT("Stat` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L308 _public prototype_ `static FAnimGenControlSchemaElement SpecifySetControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement Element, const int32 MaxNum, const int32 AttentionEncodingSize = 32, const int32 AttentionHeadNum = 4, const int32 ValueEncodingSize = 32, const FName Tag = TEXT("SetC` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L311 _public prototype_ `static FAnimGenControlSchemaElement SpecifyNamedSparseControl(UPARAM(ref) FAnimGenControlSchema& Schema, const TArray<FName>& ElementNames, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L312 _public prototype_ `static FAnimGenControlSchemaElement SpecifyNamedSparseControlFromArrayView(UPARAM(ref) FAnimGenControlSchema& Schema, const TArrayView<const FName> ElementNames, const FName Tag = TEXT("Name`
- L315 _public prototype_ `static FAnimGenControlSchemaElement SpecifySparseControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 Size, const FName Tag = TEXT("Spar` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L318 _public prototype_ `static FAnimGenControlSchemaElement SpecifyPairControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement Key, const FAnimGenControlSchemaElement Value, const FName Tag = TEXT("Pair` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L321 _public prototype_ `static FAnimGenControlSchemaElement SpecifyArrayControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement Element, const int32 MaxNum, const int32 AttentionEncodingSize = 32, const int32 AttentionHeadNum = 4, const int32 ValueEncodingSize = 32, const FName Tag = TEXT("Arra` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L324 _public prototype_ `static FAnimGenControlSchemaElement SpecifyMapControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement KeyElement, const FAnimGenControlSchemaElement ValueElement, const int32 MaxNum, const int32 AttentionEncodingSize = 32, const int32 AttentionHeadNum = 4, const int32 ValueEncodingSize = 32, const FName Tag = TEXT("MapC` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L327 _public prototype_ `static FAnimGenControlSchemaElement SpecifyEnumControl(UPARAM(ref) FAnimGenControlSchema& Schema, const UEnum* Enum, const FName Tag = TEXT("Enum` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L330 _public prototype_ `static FAnimGenControlSchemaElement SpecifyBitmaskControl(UPARAM(ref) FAnimGenControlSchema& Schema, const UEnum* Enum, const FName Tag = TEXT("Bitm` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L333 _public prototype_ `static FAnimGenControlSchemaElement SpecifyOptionalControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement Element, const int32 EncodingSize = 128, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L336 _public prototype_ `static FAnimGenControlSchemaElement SpecifyEitherControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement A, const FAnimGenControlSchemaElement B, const int32 EncodingSize = 128, const FName Tag = TEXT("Eith` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L339 _public prototype_ `static FAnimGenControlSchemaElement SpecifyEncodingControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FAnimGenControlSchemaElement Element, const int32 EncodingSize = 128, const int32 HiddenLayerNum = 1, const EAnimGenActivationFunction ActivationFunction = EAnimGenActivationFunction::ELU, const FName Tag = TEXT("Enco` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L342 _public prototype_ `static FAnimGenControlSchemaElement SpecifyBoolControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L345 _public prototype_ `static FAnimGenControlSchemaElement SpecifyFloatControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Floa` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L348 _public prototype_ `static FAnimGenControlSchemaElement SpecifyLocationControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L351 _public prototype_ `static FAnimGenControlSchemaElement SpecifyRotationControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Rota` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L354 _public prototype_ `static FAnimGenControlSchemaElement SpecifyScaleControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Scal` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L357 _public prototype_ `static FAnimGenControlSchemaElement SpecifyTransformControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Tran` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L360 _public prototype_ `static FAnimGenControlSchemaElement SpecifyAngleControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Angl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L363 _public prototype_ `static FAnimGenControlSchemaElement SpecifyLinearVelocityControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L366 _public prototype_ `static FAnimGenControlSchemaElement SpecifyAngularVelocityControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Angu` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L369 _public prototype_ `static FAnimGenControlSchemaElement SpecifyDirectionControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L372 _public prototype_ `static FAnimGenControlSchemaElement SpecifyTimeControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Time` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L376 _public prototype_ `static FAnimGenControlSchemaElement SpecifyLocationsStaticArrayControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 Num, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L379 _public prototype_ `static FAnimGenControlSchemaElement SpecifyLinearVelocitiesStaticArrayControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 Num, const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L382 _public prototype_ `static FAnimGenControlSchemaElement SpecifyDirectionsStaticArrayControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 Num, const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L386 _public prototype_ `static FAnimGenControlSchemaElement SpecifyPoseControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 BoneNum, const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L389 _public prototype_ `static FAnimGenControlSchemaElement SpecifyTrajectoryControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 TrajectorySampleNum, const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L392 _public prototype_ `static FAnimGenControlSchemaElement SpecifyLocationTrajectoryControl(UPARAM(ref) FAnimGenControlSchema& Schema, const int32 TrajectorySampleNum, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L396 _public prototype_ `static FAnimGenControlSchemaElement SpecifyEventControl(UPARAM(ref) FAnimGenControlSchema& Schema, const FName Tag = TEXT("Even` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L402 _public prototype_ `static FAnimGenControlObjectElement MakeNullControl(UPARAM(ref) FAnimGenControlObject& Object, const FName Tag = TEXT("Null` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L405 _public prototype_ `static FAnimGenControlObjectElement MakeContinuousControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<float>& Values, const FName Tag = TEXT("Cont` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L406 _public prototype_ `static FAnimGenControlObjectElement MakeContinuousControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const float> Values, const FName Tag = TEXT("Cont`
- L409 _public prototype_ `static FAnimGenControlObjectElement MakeNamedExclusiveDiscreteControl(UPARAM(ref) FAnimGenControlObject& Object, const FName ElementName, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L412 _public prototype_ `static FAnimGenControlObjectElement MakeNamedInclusiveDiscreteControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FName>& ElementNames, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L413 _public prototype_ `static FAnimGenControlObjectElement MakeNamedInclusiveDiscreteControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FName> ElementNames, const FName Tag = TEXT("Name`
- L416 _public prototype_ `static FAnimGenControlObjectElement MakeExclusiveDiscreteControl(UPARAM(ref) FAnimGenControlObject& Object, const int32 DiscreteIndex, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L419 _public prototype_ `static FAnimGenControlObjectElement MakeInclusiveDiscreteControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<int32>& DiscreteIndices, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L420 _public prototype_ `static FAnimGenControlObjectElement MakeInclusiveDiscreteControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const int32> DiscreteIndices, const FName Tag = TEXT("Incl`
- L423 _public prototype_ `static FAnimGenControlObjectElement MakeCountControl(UPARAM(ref) FAnimGenControlObject& Object, const int32 Num, const int32 MaxNum, const FName Tag = TEXT("Coun` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L426 _public prototype_ `static FAnimGenControlObjectElement MakeStructControl(UPARAM(ref) FAnimGenControlObject& Object, const TMap<FName, FAnimGenControlObjectElement>& Elements, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L429 _public prototype_ `static FAnimGenControlObjectElement MakeStructControlFromArrays(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FName>& ElementNames, const TArray<FAnimGenControlObjectElement>& Elements, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L430 _public prototype_ `static FAnimGenControlObjectElement MakeStructControlFromArrayViews(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FName> ElementNames, const TArrayView<const FAnimGenControlObjectElement> Elements, const FName Tag = TEXT("Stru`
- L433 _public prototype_ `static FAnimGenControlObjectElement MakeExclusiveUnionControl(UPARAM(ref) FAnimGenControlObject& Object, const FName ElementName, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L436 _public prototype_ `static FAnimGenControlObjectElement MakeInclusiveUnionControl(UPARAM(ref) FAnimGenControlObject& Object, const TMap<FName, FAnimGenControlObjectElement>& Elements, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2, AutoCreateRefTerm = "Elements"))`
- L439 _public prototype_ `static FAnimGenControlObjectElement MakeInclusiveUnionControlFromArrays(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FName>& ElementNames, const TArray<FAnimGenControlObjectElement>& Elements, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "ElementNames,Elements"))`
- L440 _public prototype_ `static FAnimGenControlObjectElement MakeInclusiveUnionControlFromArrayViews(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FName> ElementNames, const TArrayView<const FAnimGenControlObjectElement> Elements, const FName Tag = TEXT("Incl`
- L443 _public prototype_ `static FAnimGenControlObjectElement MakeStaticArrayControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FAnimGenControlObjectElement>& Elements, const FName Tag = TEXT("Stat` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L444 _public prototype_ `static FAnimGenControlObjectElement MakeStaticArrayControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FAnimGenControlObjectElement> Elements, const FName Tag = TEXT("Stat`
- L447 _public prototype_ `static FAnimGenControlObjectElement MakeSetControl(UPARAM(ref) FAnimGenControlObject& Object, const TSet<FAnimGenControlObjectElement>& Elements, const FName Tag = TEXT("SetC` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2, AutoCreateRefTerm = "Elements"))`
- L450 _public prototype_ `static FAnimGenControlObjectElement MakeSetControlFromArray(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FAnimGenControlObjectElement>& Elements, const FName Tag = TEXT("SetC` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2, AutoCreateRefTerm = "Elements"))`
- L451 _public prototype_ `static FAnimGenControlObjectElement MakeSetControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FAnimGenControlObjectElement> Elements, const FName Tag = TEXT("SetC`
- L454 _public prototype_ `static FAnimGenControlObjectElement MakeNamedSparseControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FName>& ElementNames, const TArray<float>& ElementValues, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L455 _public prototype_ `static FAnimGenControlObjectElement MakeNamedSparseControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FName> ElementNames, const TArrayView<const float> ElementValues, const FName Tag = TEXT("Name`
- L458 _public prototype_ `static FAnimGenControlObjectElement MakeSparseControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<int32>& Indices, const TArray<float>& Values, const FName Tag = TEXT("Spar` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L459 _public prototype_ `static FAnimGenControlObjectElement MakeSparseControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const int32> Indices, const TArrayView<const float> Values, const FName Tag = TEXT("Spar`
- L463 _public prototype_ `static FAnimGenControlObjectElement MakePairControl(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlObjectElement Key, const FAnimGenControlObjectElement Value, const FName Tag = TEXT("Pair` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L466 _public prototype_ `static FAnimGenControlObjectElement MakeArrayControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FAnimGenControlObjectElement>& Elements, const int32 MaxNum, const FName Tag = TEXT("Arra` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "Elements"))`
- L467 _public prototype_ `static FAnimGenControlObjectElement MakeArrayControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FAnimGenControlObjectElement> Elements, const int32 MaxNum, const FName Tag = TEXT("Arra`
- L470 _public prototype_ `static FAnimGenControlObjectElement MakeMapControl(UPARAM(ref) FAnimGenControlObject& Object, const TMap<FAnimGenControlObjectElement, FAnimGenControlObjectElement>& Map, const FName Tag = TEXT("MapC` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2, AutoCreateRefTerm = "Map"))`
- L473 _public prototype_ `static FAnimGenControlObjectElement MakeMapControlFromArrays(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FAnimGenControlObjectElement>& Keys, const TArray<FAnimGenControlObjectElement>& Values, const FName Tag = TEXT("MapC` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "Keys,Values"))`
- L474 _public prototype_ `static FAnimGenControlObjectElement MakeMapControlFromArrayViews(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FAnimGenControlObjectElement> Keys, const TArrayView<const FAnimGenControlObjectElement> Values, const FName Tag = TEXT("MapC`
- L477 _public prototype_ `static FAnimGenControlObjectElement MakeEnumControl(UPARAM(ref) FAnimGenControlObject& Object, const UEnum* Enum, const uint8 EnumValue, const FName Tag = TEXT("Enum` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L480 _public prototype_ `static FAnimGenControlObjectElement MakeBitmaskControl(UPARAM(ref) FAnimGenControlObject& Object, const UEnum* Enum, const int32 BitmaskValue, const FName Tag = TEXT("Bitm` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L483 _public prototype_ `static FAnimGenControlObjectElement MakeOptionalControl(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const EAnimGenOptionalControl Option, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L486 _public prototype_ `static FAnimGenControlObjectElement MakeOptionalNullControl(UPARAM(ref) FAnimGenControlObject& Object, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 1))`
- L489 _public prototype_ `static FAnimGenControlObjectElement MakeOptionalValidControl(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L492 _public prototype_ `static FAnimGenControlObjectElement MakeOptionalControlOnCondition(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const bool bCondition, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L493 _public prototype_ `static FAnimGenControlObjectElement MakeOptionalControlOnConditionWithFunction(FAnimGenControlObject& Object, TFunctionRef<FAnimGenControlObjectElement(FAnimGenControlObject&)> ElementFunction, const bool bCondition, const FName Tag = TEXT("Opti`
- L496 _public prototype_ `static FAnimGenControlObjectElement MakeEitherControl(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const EAnimGenEitherControl Either, const FName Tag = TEXT("Eith` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L499 _public prototype_ `static FAnimGenControlObjectElement MakeEitherAControl(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlObjectElement A, const FName Tag = TEXT("Eith` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2, DisplayName = "Make Either A Control"))`
- L502 _public prototype_ `static FAnimGenControlObjectElement MakeEitherBControl(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlObjectElement B, const FName Tag = TEXT("Eith` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2, DisplayName = "Make Either B Control"))`
- L505 _public prototype_ `static FAnimGenControlObjectElement MakeEncodingControl(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Enco` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L508 _public prototype_ `static FAnimGenControlObjectElement MakeBoolControl(UPARAM(ref) FAnimGenControlObject& Object, const bool bValue, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L511 _public prototype_ `static FAnimGenControlObjectElement MakeFloatControl(UPARAM(ref) FAnimGenControlObject& Object, const float Value, const FName Tag = TEXT("Floa` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L514 _public prototype_ `static FAnimGenControlObjectElement MakeLocationControl(UPARAM(ref) FAnimGenControlObject& Object, const FVector Location, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L517 _public prototype_ `static FAnimGenControlObjectElement MakeRotationControl(UPARAM(ref) FAnimGenControlObject& Object, const FRotator Rotation, const FRotator RelativeRotation = FRotator::ZeroRotator, const FName Tag = TEXT("Rota` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L520 _public prototype_ `static FAnimGenControlObjectElement MakeRotationControlFromQuat(UPARAM(ref) FAnimGenControlObject& Object, const FQuat Rotation, const FQuat RelativeRotation, const FName Tag = TEXT("Rota` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L523 _public prototype_ `static FAnimGenControlObjectElement MakeScaleControl(UPARAM(ref) FAnimGenControlObject& Object, const FVector Scale, const FVector RelativeScale = FVector(1, 1, 1), const FName Tag = TEXT("Scal` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L526 _public prototype_ `static FAnimGenControlObjectElement MakeTransformControl(UPARAM(ref) FAnimGenControlObject& Object, const FTransform Transform, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Tran` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L529 _public prototype_ `static FAnimGenControlObjectElement MakeAngleControl(UPARAM(ref) FAnimGenControlObject& Object, const float Angle, const float RelativeAngle = 0.0f, const FName Tag = TEXT("Angl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L532 _public prototype_ `static FAnimGenControlObjectElement MakeAngleControlRadians(UPARAM(ref) FAnimGenControlObject& Object, const float Angle, const float RelativeAngle = 0.0f, const FName Tag = TEXT("Angl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L535 _public prototype_ `static FAnimGenControlObjectElement MakeLinearVelocityControl(UPARAM(ref) FAnimGenControlObject& Object, const FVector LinearVelocity, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L538 _public prototype_ `static FAnimGenControlObjectElement MakeAngularVelocityControl(UPARAM(ref) FAnimGenControlObject& Object, const FVector AngularVelocity, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Angu` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L541 _public prototype_ `static FAnimGenControlObjectElement MakeDirectionControl(UPARAM(ref) FAnimGenControlObject& Object, const FVector Direction, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L544 _public prototype_ `static FAnimGenControlObjectElement MakeTimeControl(UPARAM(ref) FAnimGenControlObject& Object, const float Time, const float RelativeTime = 0.0f, const FName Tag = TEXT("Time` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L548 _public prototype_ `static FAnimGenControlObjectElement MakeLocationsStaticArrayControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FVector>& Locations, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L549 _public prototype_ `static FAnimGenControlObjectElement MakeLocationsStaticArrayControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FVector> Locations, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca`
- L552 _public prototype_ `static FAnimGenControlObjectElement MakeLinearVelocitiesStaticArrayControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FVector>& LinearVelocities, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L553 _public prototype_ `static FAnimGenControlObjectElement MakeLinearVelocitiesStaticArrayControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FVector> LinearVelocities, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Line`
- L556 _public prototype_ `static FAnimGenControlObjectElement MakeDirectionsStaticArrayControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FVector>& Directions, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L557 _public prototype_ `static FAnimGenControlObjectElement MakeDirectionsStaticArrayControlFromArrayView(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FVector> Directions, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Dire`
- L560 _public prototype_ `static FAnimGenControlObjectElement MakePoseControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FVector>& Locations, const TArray<FVector>& LinearVelocities, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L561 _public prototype_ `static FAnimGenControlObjectElement MakePoseControlFromArrayViews(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FVector> Locations, const TArrayView<const FVector> LinearVelocities, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Pose`
- L564 _public prototype_ `static FAnimGenControlObjectElement MakePoseControlFromPoseState(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabasePoseState& PoseState, const TArray<int32>& BoneIndices, const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L565 _public prototype_ `static FAnimGenControlObjectElement MakePoseControlFromPoseStateArrayViews(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabasePoseState& PoseState, const TArrayView<const int32> BoneIndices, const FName Tag = TEXT("Pose`
- L568 _public prototype_ `static FAnimGenControlObjectElement MakeTrajectoryControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FVector>& Locations, const TArray<FVector>& Directions, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4, AutoCreateRefTerm = "RelativeTransform"))`
- L569 _public prototype_ `static FAnimGenControlObjectElement MakeTrajectoryControlFromArrayViews(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FVector> Locations, const TArrayView<const FVector> Directions, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Traj`
- L572 _public prototype_ `static FAnimGenControlObjectElement MakeLocationTrajectoryControl(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FVector>& Locations, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3, AutoCreateRefTerm = "RelativeTransform"))`
- L573 _public prototype_ `static FAnimGenControlObjectElement MakeLocationTrajectoryControlFromArrayViews(UPARAM(ref) FAnimGenControlObject& Object, const TArrayView<const FVector> Locations, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca`
- L576 _public prototype_ `static FAnimGenControlObjectElement MakeTrajectoryControlFromTransformTrajectory(UPARAM(ref) FAnimGenControlObject& Object, const FTransformTrajectory& TransformTrajectory, const FTransform& RelativeTransform = FTransform(), const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FVector ForwardVector = FVector(0,1,0), const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 6, AutoCreateRefTerm = "RelativeTransform"))`
- L579 _public prototype_ `static FAnimGenControlObjectElement MakeLocationTrajectoryControlFromTransformTrajectory(UPARAM(ref) FAnimGenControlObject& Object, const FTransformTrajectory& TransformTrajectory, const FTransform& RelativeTransform = FTransform(), const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 5, AutoCreateRefTerm = "RelativeTransform"))`
- L582 _public prototype_ `static FAnimGenControlObjectElement MakeEventControl(UPARAM(ref) FAnimGenControlObject& Object, const bool bTimeUntilEventKnown, const float TimeUntilEvent, const FName Tag = TEXT("Even` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L585 _public prototype_ `static FAnimGenControlObjectElement MakeEventControlFromPoseState(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabasePoseState& PoseState, const int32 FrameAttributeIndex, const FName Tag = TEXT("Even` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L590 _public prototype_ `static bool GetNullControl(const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Null` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 2, ReturnDisplayName = "Success"))`
- L593 _public prototype_ `static bool GetContinuousControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Cont` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L596 _public prototype_ `static bool GetContinuousControl(TArray<float>& OutValues, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Cont` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L597 _public prototype_ `static bool GetContinuousControlToArrayView(TArrayView<float> OutValues, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Cont`
- L600 _public prototype_ `static bool GetNamedExclusiveDiscreteControl(FName& OutElement, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L603 _public prototype_ `static bool GetNamedInclusiveDiscreteControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L606 _public prototype_ `static bool GetNamedInclusiveDiscreteControl(TArray<FName>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L607 _public prototype_ `static bool GetNamedInclusiveDiscreteControlToArrayView(TArrayView<FName> OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Name`
- L610 _public prototype_ `static bool GetExclusiveDiscreteControl(int32& OutIndex, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L613 _public prototype_ `static bool GetInclusiveDiscreteControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L616 _public prototype_ `static bool GetInclusiveDiscreteControl(TArray<int32>& OutIndices, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L617 _public prototype_ `static bool GetInclusiveDiscreteControlToArrayView(TArrayView<int32> OutIndices, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Incl`
- L620 _public prototype_ `static bool GetCountControl(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const int32 MaxNum, const FName Tag = TEXT("Coun` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L623 _public prototype_ `static bool GetStructControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L626 _public prototype_ `static bool GetStructControl(TMap<FName, FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L629 _public prototype_ `static bool GetStructControlToArrays(TArray<FName>& OutElementNames, TArray<FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L630 _public prototype_ `static bool GetStructControlToArrayViews(TArrayView<FName> OutElementNames, TArrayView<FAnimGenControlObjectElement> OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Stru`
- L633 _public prototype_ `static bool GetStructControlElement(FAnimGenControlObjectElement& OutElement, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName ElementName, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L636 _public prototype_ `static bool GetExclusiveUnionControl(FName& OutElementName, FAnimGenControlObjectElement& OutElement, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L639 _public prototype_ `static bool GetInclusiveUnionControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L642 _public prototype_ `static bool GetInclusiveUnionControl(TMap<FName, FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L645 _public prototype_ `static bool GetInclusiveUnionControlToArrays(TArray<FName>& OutElementNames, TArray<FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L646 _public prototype_ `static bool GetInclusiveUnionControlToArrayViews(TArrayView<FName> OutElementNames, TArrayView<FAnimGenControlObjectElement> OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Incl`
- L649 _public prototype_ `static bool FindInclusiveUnionControlElement(FAnimGenControlObjectElement& OutElement, bool& bFound, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName ElementName, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success"))`
- L652 _public prototype_ `static bool SwitchOnHasInclusiveUnionControlElement(FAnimGenControlObjectElement& OutElement, bool& bFound, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName ElementName, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ExpandBoolAsExecs = "bFound", ReturnDisplayName = "Success"))`
- L655 _public prototype_ `static bool GetStaticArrayControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Stat` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L658 _public prototype_ `static bool GetStaticArrayControl(TArray<FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Stat` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L659 _public prototype_ `static bool GetStaticArrayControlToArrayView(TArrayView<FAnimGenControlObjectElement> OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Stat`
- L662 _public prototype_ `static bool GetSetControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("SetC` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L665 _public prototype_ `static bool GetSetControl(TSet<FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("SetC` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L668 _public prototype_ `static bool GetSetControlToArray(TArray<FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("SetC` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L669 _public prototype_ `static bool GetSetControlToArrayView(TArrayView<FAnimGenControlObjectElement> OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("SetC`
- L672 _public prototype_ `static bool GetNamedSparseControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L675 _public prototype_ `static bool GetNamedSparseControl(TArray<FName>& OutElements, TArray<float>& OutElementValues, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L676 _public prototype_ `static bool GetNamedSparseControlToArrayView(TArrayView<FName> OutElements, TArrayView<float> OutElementValues, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Name`
- L679 _public prototype_ `static bool GetSparseControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Spar` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L682 _public prototype_ `static bool GetSparseControl(TArray<int32>& OutIndices, TArray<float>& OutValues, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Spar` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L683 _public prototype_ `static bool GetSparseControlToArrayView(TArrayView<int32> OutIndices, TArrayView<float> OutValues, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Spar`
- L686 _public prototype_ `static bool GetPairControl(FAnimGenControlObjectElement& OutKey, FAnimGenControlObjectElement& OutValue, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Pair` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L689 _public prototype_ `static bool GetArrayControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Arra` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L692 _public prototype_ `static bool GetArrayControl(TArray<FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const int32 MaxNum, const FName Tag = TEXT("Arra` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L693 _public prototype_ `static bool GetArrayControlToArrayView(TArrayView<FAnimGenControlObjectElement> OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const int32 MaxNum, const FName Tag = TEXT("Arra`
- L696 _public prototype_ `static bool GetMapControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("MapC` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L699 _public prototype_ `static bool GetMapControl(TMap<FAnimGenControlObjectElement, FAnimGenControlObjectElement>& OutElements, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("MapC` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L702 _public prototype_ `static bool GetMapControlToArrays(TArray<FAnimGenControlObjectElement>& OutKeys, TArray<FAnimGenControlObjectElement>& OutValues, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("MapC` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L703 _public prototype_ `static bool GetMapControlToArrayViews(TArrayView<FAnimGenControlObjectElement> OutKeys, TArrayView<FAnimGenControlObjectElement> OutValues, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("MapC`
- L706 _public prototype_ `static bool GetEnumControl(uint8& OutEnumValue, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const UEnum* Enum, const FName Tag = TEXT("Enum` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L709 _public prototype_ `static bool GetBitmaskControl(int32& OutBitmaskValue, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const UEnum* Enum, const FName Tag = TEXT("Bitm` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L712 _public prototype_ `static bool GetOptionalControl(EAnimGenOptionalControl& OutOption, FAnimGenControlObjectElement& OutElement, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ExpandEnumAsExecs = "OutOption", ReturnDisplayName = "Success"))`
- L715 _public prototype_ `static bool GetEitherControl(EAnimGenEitherControl& OutEither, FAnimGenControlObjectElement& OutElement, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Eith` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ExpandEnumAsExecs = "OutEither", ReturnDisplayName = "Success"))`
- L718 _public prototype_ `static bool GetEncodingControl(FAnimGenControlObjectElement& OutElement, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Enco` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L721 _public prototype_ `static bool GetBoolControl(bool& bOutValue, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L724 _public prototype_ `static bool GetFloatControl(float& OutValue, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Floa` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L727 _public prototype_ `static bool GetLocationControl(FVector& OutLocation, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L730 _public prototype_ `static bool GetRotationControl(FRotator& OutRotation, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FRotator RelativeRotation = FRotator::ZeroRotator, const FName Tag = TEXT("Rota` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L733 _public prototype_ `static bool GetRotationControlAsQuat(FQuat& OutRotation, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FQuat RelativeRotation, const FName Tag = TEXT("Rota` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L736 _public prototype_ `static bool GetScaleControl(FVector& OutScale, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FVector RelativeScale = FVector(1, 1, 1), const FName Tag = TEXT("Scal` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L739 _public prototype_ `static bool GetTransformControl(FTransform& OutTransform, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Tran` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L742 _public prototype_ `static bool GetAngleControl(float& OutAngle, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const float RelativeAngle = 0.0f, const FName Tag = TEXT("Angl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L745 _public prototype_ `static bool GetAngleControlRadians(float& OutAngle, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const float RelativeAngle = 0.0f, const FName Tag = TEXT("Angl` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L748 _public prototype_ `static bool GetLinearVelocityControl(FVector& OutLinearVelocity, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L751 _public prototype_ `static bool GetAngularVelocityControl(FVector& OutAngularVelocity, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Angu` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L754 _public prototype_ `static bool GetDirectionControl(FVector& OutDirection, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L757 _public prototype_ `static bool GetTimeControl(float& OutTime, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const float RelativeTime = 0.0f, const FName Tag = TEXT("Time` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L762 _public prototype_ `static bool GetLocationsStaticArrayControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L765 _public prototype_ `static bool GetLocationsStaticArrayControl(TArray<FVector>& OutLocations, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L766 _public prototype_ `static bool GetLocationsStaticArrayControlToArrayView(TArrayView<FVector> OutLocations, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca`
- L769 _public prototype_ `static bool GetLinearVelocitiesStaticArrayControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L772 _public prototype_ `static bool GetLinearVelocitiesStaticArrayControl(TArray<FVector>& OutLinearVelocities, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L773 _public prototype_ `static bool GetLinearVelocitiesStaticArrayControlToArrayView(TArrayView<FVector> OutLinearVelocities, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Line`
- L776 _public prototype_ `static bool GetDirectionsStaticArrayControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L779 _public prototype_ `static bool GetDirectionsStaticArrayControl(TArray<FVector>& OutDirections, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L780 _public prototype_ `static bool GetDirectionsStaticArrayControlToArrayView(TArrayView<FVector> OutDirections, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Dire`
- L784 _public prototype_ `static bool GetPoseControlNum(int32& OutNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L787 _public prototype_ `static bool GetPoseControl(TArray<FVector>& OutLocations, TArray<FVector>& OutLinearVelocities, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L788 _public prototype_ `static bool GetPoseControlToArrayViews(TArrayView<FVector> OutLocations, TArrayView<FVector> OutLinearVelocities, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Pose`
- L792 _public prototype_ `static bool GetTrajectoryControlNum(int32& OutLocationNum, int32& OutDirectionNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L795 _public prototype_ `static bool GetTrajectoryControl(TArray<FVector>& OutLocations, TArray<FVector>& OutDirections, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L796 _public prototype_ `static bool GetTrajectoryControlToArrayViews(TArrayView<FVector> OutLocations, TArrayView<FVector> OutDirections, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Traj`
- L800 _public prototype_ `static bool GetLocationTrajectoryControlNum(int32& OutLocationNum, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 3, ReturnDisplayName = "Success"))`
- L803 _public prototype_ `static bool GetLocationTrajectoryControl(TArray<FVector>& OutLocations, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L804 _public prototype_ `static bool GetLocationTrajectoryControlToArrayViews(TArrayView<FVector> OutLocations, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FName Tag = TEXT("Loca`
- L808 _public prototype_ `static bool GetEventControl(bool& bOutTimeUntilEventKnown, float& OutTimeUntilEvent, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Tag = TEXT("Even` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 4, ReturnDisplayName = "Success"))`
- L813 _public prototype_ `static bool FrameAttributeLocationDistanceFromControl(FAnimDatabaseFrameAttribute& OutFrameAttribute, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FAnimDatabaseFrameAttribute& LocationFrameAttribute, const float Scale = 100.0f, const float Weight = 1.0f, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 6, ReturnDisplayName = "Success"))`
- L816 _public prototype_ `static bool FrameAttributeVelocityDistanceFromControl(FAnimDatabaseFrameAttribute& OutFrameAttribute, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FAnimDatabaseFrameAttribute& VelocityFrameAttribute, const float Scale = 200.0f, const float Weight = 1.0f, const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 6, ReturnDisplayName = "Success"))`
- L819 _public prototype_ `static bool FrameAttributeDirectionDistanceFromControl(FAnimDatabaseFrameAttribute& OutFrameAttribute, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FAnimDatabaseFrameAttribute& DirectionFrameAttribute, const float Weight = 1.0f, const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success"))`
- L822 _public prototype_ `static bool FrameAttributeRotationDistanceFromControl(FAnimDatabaseFrameAttribute& OutFrameAttribute, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FAnimDatabaseFrameAttribute& RotationFrameAttribute, const float Weight = 1.0f, const FName Tag = TEXT("Rota` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success"))`
- L825 _public prototype_ `static bool FrameAttributeEventDistanceFromControl(FAnimDatabaseFrameAttribute& OutFrameAttribute, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FAnimDatabaseFrameAttribute& FrameAttribute, const float Weight = 1.0f, const FName Tag = TEXT("Even` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success"))`
- L828 _public prototype_ `static bool FrameAttributeTrajectoryDistanceFromControl(FAnimDatabaseFrameAttribute& OutFrameAttribute, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const TArray<FAnimDatabaseFrameAttribute>& LocationFrameAttributes, const TArray<FAnimDatabaseFrameAttribute>& DirectionFrameAttributes, const float LocationScale = 100.0f, const float LocationWeight = 1.0f, const float DirectionWeight = 1.0f, const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 8, ReturnDisplayName = "Success"))`
- L831 _public prototype_ `static bool FrameAttributePoseDistanceFromControl(FAnimDatabaseFrameAttribute& OutFrameAttribute, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const TArray<FAnimDatabaseFrameAttribute>& LocationFrameAttributes, const TArray<FAnimDatabaseFrameAttribute>& LinearVelocityFrameAttributes, const float LocationScale = 100.0f, const float LinearVelocityScale = 100.0f, const float LocationWeight = 1.0f, const float LinearVelocityWeight = 1.0f, const float BlendTime = 0.2f, const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 10, ReturnDisplayName = "Success"))`
- L836 _public prototype_ `static FAnimDatabaseFrameRanges ControlSetFrameRanges(const FAnimGenControlSet& ControlSet);` — `UFUNCTION(BlueprintPure, Category = "AnimGen")`
- L839 _public prototype_ `static FAnimGenControlSet MakeEmptyControlSet();` — `UFUNCTION(BlueprintPure, Category = "AnimGen")`
- L842 _public prototype_ `static FAnimGenControlSet MakeNullControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& ControlSetFrameRanges, const FName Tag = TEXT("Null` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L845 _public prototype_ `static FAnimGenControlSet MakeBoolControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& BoolFrameAttribute, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L848 _public prototype_ `static FAnimGenControlSet MakeFloatControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& FloatFrameAttribute, const FName Tag = TEXT("Floa` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L851 _public prototype_ `static FAnimGenControlSet MakeLocationControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& LocationFrameAttribute, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L854 _public prototype_ `static FAnimGenControlSet MakeRotationControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& RotationFrameAttribute, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Rota` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L857 _public prototype_ `static FAnimGenControlSet MakeLinearVelocityControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& LinearVelocityFrameAttribute, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L860 _public prototype_ `static FAnimGenControlSet MakeAngularVelocityControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& AngularVelocityFrameAttribute, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Angu` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L863 _public prototype_ `static FAnimGenControlSet MakeDirectionControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& DirectionFrameAttribute, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L866 _public prototype_ `static FAnimGenControlSet MakeTimeControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& TimeFrameAttribute, const FAnimDatabaseFrameAttribute& RelativeTimeFrameAttribute, const FName Tag = TEXT("Time` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L869 _public prototype_ `static FAnimGenControlSet MakeExclusiveDiscreteControlSetFromConstant(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& ControlSetFrameRanges, const int32 DiscreteIndex, const int32 Size, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L872 _public prototype_ `static FAnimGenControlSet MakeTrajectoryControlSet(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FAnimDatabaseFrameAttribute>& LocationFrameAttributes, const TArray<FAnimDatabaseFrameAttribute>& DirectionFrameAttributes, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L873 _public prototype_ `static FAnimGenControlSet MakeTrajectoryControlSetFromArrayViews(FAnimGenControlObject& Object, const TArrayView<const FAnimDatabaseFrameAttribute> LocationFrameAttributes, const TArrayView<const FAnimDatabaseFrameAttribute> DirectionFrameAttributes, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Traj`
- L876 _public prototype_ `static FAnimGenControlSet MakeLocationTrajectoryControlSet(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FAnimDatabaseFrameAttribute>& LocationFrameAttributes, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L877 _public prototype_ `static FAnimGenControlSet MakeLocationTrajectoryControlSetFromArrayView(FAnimGenControlObject& Object, const TArrayView<const FAnimDatabaseFrameAttribute> LocationFrameAttributes, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Loca`
- L880 _public prototype_ `static FAnimGenControlSet MakePoseControlSet(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FAnimDatabaseFrameAttribute>& LocationFrameAttributes, const TArray<FAnimDatabaseFrameAttribute>& LinearVelocityFrameAttributes, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L881 _public prototype_ `static FAnimGenControlSet MakePoseControlSetFromArrayViews(FAnimGenControlObject& Object, const TArrayView<const FAnimDatabaseFrameAttribute> LocationFrameAttributes, const TArrayView<const FAnimDatabaseFrameAttribute> LinearVelocityFrameAttributes, const FAnimDatabaseFrameAttribute& RelativeTransformFrameAttribute, const FName Tag = TEXT("Pose`
- L884 _public prototype_ `static FAnimGenControlSet MakeStructControlSet(UPARAM(ref) FAnimGenControlObject& Object, const TMap<FName, FAnimGenControlSet>& Elements, const FName Tag = TEXT("Stru` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L885 _public prototype_ `static FAnimGenControlSet MakeStructControlSetFromArrays(FAnimGenControlObject& Object, const TArray<FName>& ElementNames, TArray<FAnimGenControlSet>& Elements, const FName Tag = TEXT("Stru`
- L886 _public prototype_ `static FAnimGenControlSet MakeStructControlSetFromArrayViews(FAnimGenControlObject& Object, const TArrayView<const FName> ElementNames, TArrayView<const FAnimGenControlSet> Elements, const FName Tag = TEXT("Stru`
- L889 _public prototype_ `static FAnimGenControlSet MakeExclusiveUnionControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FName ElementName, const FAnimGenControlSet& Element, const FName Tag = TEXT("Excl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L892 _public prototype_ `static FAnimGenControlSet MakeEmptyInclusiveUnionControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& ControlSetFrameRanges, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L895 _public prototype_ `static FAnimGenControlSet MakeInclusiveUnionControlSet(UPARAM(ref) FAnimGenControlObject& Object, const TMap<FName, FAnimGenControlSet>& Elements, const FName Tag = TEXT("Incl` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L898 _public prototype_ `static FAnimGenControlSet MakeOptionalControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlSet& InControlSet, const FAnimDatabaseFrameAttribute& ValidFrameAttribute, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L901 _public prototype_ `static FAnimGenControlSet MakeOptionalNullControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& ControlSetFrameRanges, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L904 _public prototype_ `static FAnimGenControlSet MakeOptionalValidControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlSet& InControlSet, const FName Tag = TEXT("Opti` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L907 _public prototype_ `static FAnimGenControlSet MakeEnumControlSet(UPARAM(ref) FAnimGenControlObject& Object, const UEnum* Enum, const uint8 EnumValue, const FAnimDatabaseFrameRanges& ControlSetFrameRanges, const FName Tag = TEXT("Enum` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L910 _public prototype_ `static FAnimGenControlSet MakeEventControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameAttribute& EventFrameAttribute, const FName Tag = TEXT("Even` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L913 _public prototype_ `static FAnimGenControlSet MakeSetControlSetFromArray(UPARAM(ref) FAnimGenControlObject& Object, const TArray<FAnimGenControlSet>& Elements, const TArray<FAnimDatabaseFrameAttribute>& ElementMasks, const FName Tag = TEXT("SetC` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L914 _public prototype_ `static FAnimGenControlSet MakeSetControlSetFromArrayView(FAnimGenControlObject& Object, const TArrayView<const FAnimGenControlSet> Elements, const TArrayView<const FAnimDatabaseFrameAttribute> ElementMasks, const FName Tag = TEXT("SetC`
- L917 _public prototype_ `static FAnimGenControlSet MakeEncodingControlSet(UPARAM(ref) FAnimGenControlObject& Object, const FAnimGenControlSet& Element, const FName Tag = TEXT("Enco` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 2))`
- L920 _public prototype_ `static FAnimGenControlSet MakeNamedInclusiveDiscreteControlSetFromFrameRanges(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& FrameRanges, const TMap<FName, FAnimDatabaseFrameRanges>& ElementMap, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L921 _public prototype_ `static FAnimGenControlSet MakeNamedInclusiveDiscreteControlSetFromFrameRangesArrayViews(FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> ElementNames, const TArrayView<const FAnimDatabaseFrameRanges> ElementFrameRanges, const FName Tag = TEXT("Name`
- L924 _public prototype_ `static FAnimGenControlSet MakeNamedInclusiveDiscreteControlSetFromAnimNotifyStates(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TMap<FName, TSubclassOf<UAnimNotifyState>>& AnimNotifyStateMap, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L925 _public prototype_ `static FAnimGenControlSet MakeNamedInclusiveDiscreteControlSetFromAnimNotifyStatesArrayViews(FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> ElementNames, const TArrayView<const TSubclassOf<UAnimNotifyState>> ElementAnimNotifyStates, const FName Tag = TEXT("Name`
- L928 _public prototype_ `static FAnimGenControlSet MakeNamedExclusiveDiscreteControlSetFromFrameRanges(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& FrameRanges, const TMap<FName, FAnimDatabaseFrameRanges>& ElementMap, const FName DefaultElementName, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L929 _public prototype_ `static FAnimGenControlSet MakeNamedExclusiveDiscreteControlSetFromFrameRangesArrayViews(FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> ElementNames, const TArrayView<const FAnimDatabaseFrameRanges> ElementFrameRanges, const FName DefaultElementName, const FName Tag = TEXT("Name`
- L932 _public prototype_ `static FAnimGenControlSet MakeNamedExclusiveDiscreteControlSetFromAnimNotifyStates(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TMap<FName, TSubclassOf<UAnimNotifyState>>& AnimNotifyStateMap, const FName DefaultElementName, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 5))`
- L933 _public prototype_ `static FAnimGenControlSet MakeNamedExclusiveDiscreteControlSetFromAnimNotifyStatesArrayViews(FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> ElementNames, const TArrayView<const TSubclassOf<UAnimNotifyState>> ElementAnimNotifyStates, const FName DefaultElementName, const FName Tag = TEXT("Name`
- L936 _public prototype_ `static FAnimGenControlSet MakeNamedSparseControlSetFromFrameRanges(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& FrameRanges, const TMap<FName, FAnimDatabaseFrameAttribute>& ElementMap, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L937 _public prototype_ `static FAnimGenControlSet MakeNamedSparseControlSetFromFrameRangesArrayViews(FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const FName> ElementNames, const TArrayView<const FAnimDatabaseFrameAttribute> ElementFrameValues, const FName Tag = TEXT("Name`
- L942 _public prototype_ `static FAnimGenControlSet MakeRootLinearVelocityControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L945 _public prototype_ `static FAnimGenControlSet MakeRootAngularVelocityControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName Tag = TEXT("Angu` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L948 _public prototype_ `static FAnimGenControlSet MakeFutureRootLinearVelocityControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float FutureTime = 0.25f, const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L951 _public prototype_ `static FAnimGenControlSet MakeFutureRootDirectionControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const float FutureTime = 0.25f, const FVector ForwardVector = FVector(0.0f, 1.0f, 0.0f), const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 5))`
- L954 _public prototype_ `static FAnimGenControlSet MakeRootLocationAtRangeEndControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L957 _public prototype_ `static FAnimGenControlSet MakeRootDirectionAtRangeEndControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FVector ForwardVector = FVector(0.0, 1.0f, 0.0f), const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L960 _public prototype_ `static FAnimGenControlSet MakeTrajectoryControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FVector ForwardVector = FVector(0.0, 1.0f, 0.0f), const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 7))`
- L963 _public prototype_ `static FAnimGenControlSet MakeLookAtTrajectoryControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 LookAtBoneIndex, const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FVector LocalDirection = FVector(0.0, 1.0f, 0.0f), const float DirectionSmoothingAmount = 15.0f, const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 9))`
- L966 _public prototype_ `static FAnimGenControlSet MakeLocationTrajectoryControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 SampleNum = 4, const float FutureTime = 1.0f, const float PastTime = 0.0f, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 5))`
- L969 _public prototype_ `static FAnimGenControlSet MakeBoolControlSetFromConstant(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& FrameRanges, const bool bValue, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L972 _public prototype_ `static FAnimGenControlSet MakeBoolControlSetFromMirrored(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L975 _public prototype_ `static FAnimGenControlSet MakeBoolControlSetFromNotMirrored(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L978 _public prototype_ `static FAnimGenControlSet MakeBoolControlSetFromActiveRanges(UPARAM(ref) FAnimGenControlObject& Object, const FAnimDatabaseFrameRanges& Active, const FAnimDatabaseFrameRanges& FrameRanges, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 3))`
- L981 _public prototype_ `static FAnimGenControlSet MakeBoolControlSetFromAnimNotifyState(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const TSubclassOf<UAnimNotifyState> AnimNotifyState, const FAnimDatabaseFrameRanges& FrameRanges, const FName Tag = TEXT("Bool` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L984 _public prototype_ `static FAnimGenControlSet MakeBoneGlobalLocationControlSet(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L987 _public prototype_ `static FAnimGenControlSet MakeBoneGlobalLocationControlSetFromName(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L990 _public prototype_ `static FAnimGenControlSet MakeBoneGlobalLocationAtNearestFramesControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const FAnimDatabaseFrames& Frames, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 5))`
- L993 _public prototype_ `static FAnimGenControlSet MakeBoneGlobalLocationAtNearestFramesControlSetFromDatabaseBoneName(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const FAnimDatabaseFrames& Frames, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 5))`
- L996 _public prototype_ `static FAnimGenControlSet MakeBoneGlobalDirectionAtNearestFramesControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const FAnimDatabaseFrames& Frames, const FVector LocalDirection = FVector::ForwardVector, const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 6))`
- L999 _public prototype_ `static FAnimGenControlSet MakeBoneGlobalDirectionAtNearestFramesControlSetFromDatabaseBoneName(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const FAnimDatabaseFrames& Frames, const FVector LocalDirection = FVector::ForwardVector, const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 6))`
- L1002 _public prototype_ `static FAnimGenControlSet MakeBoneGlobalDirectionControlSet(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const int32 BoneIndex, const FVector ForwardVector = FVector(0.0, 1.0f, 0.0f), const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 5))`
- L1005 _public prototype_ `static FAnimGenControlSet MakeBoneGlobalDirectionControlSetFromName(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const FName BoneName, const FVector ForwardVector = FVector(0.0, 1.0f, 0.0f), const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 5))`
- L1008 _public prototype_ `static FAnimGenControlSet MakePoseControlSetFromDatabase(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArray<int32>& BoneIndices, const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L1009 _public prototype_ `static FAnimGenControlSet MakePoseControlSetFromDatabaseArrayView(FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, const TArrayView<const int32> BoneIndices, const FName Tag = TEXT("Pose`
- L1012 _public prototype_ `static FAnimGenControlSet MakeTimeUntilNearestAnimNotifyControlSet(UPARAM(ref) FAnimGenControlObject& Object, const UAnimDatabase* Database, const FAnimDatabaseFrameRanges& FrameRanges, TSubclassOf<UAnimNotify> AnimNotifyClass, const FName Tag = TEXT("Time` — `UFUNCTION(BlueprintPure, Category = "AnimGen", meta = (AdvancedDisplay = 4))`
- L1018 _public prototype_ `static bool DrawDebugLocationControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FLinearColor DrawColor = FLinearColor::Red, const float DrawRadius = 10.0f, const float Thickness = 0.0f, const int32 SegmentNum = 8, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L1021 _public prototype_ `static bool DrawDebugRotationControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FVector DrawLocation = FVector::ZeroVector, const float DrawRadius = 10.0f, const float Thickness = 0.0f, const FName Tag = TEXT("Rota` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L1024 _public prototype_ `static bool DrawDebugLinearVelocityControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FVector DrawLocation = FVector::ZeroVector, const FLinearColor DrawColor = FLinearColor::Red, const float DrawVelocityScale = 1.0f, const float Thickness = 0.0f, const FName Tag = TEXT("Line` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 6, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L1027 _public prototype_ `static bool DrawDebugAngularVelocityControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FVector DrawLocation = FVector::ZeroVector, const FLinearColor DrawColor = FLinearColor::Red, const float DrawVelocityScale = 1.0f, const float Thickness = 0.0f, const FName Tag = TEXT("Angu` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 6, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L1030 _public prototype_ `static bool DrawDebugDirectionControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FVector DrawLocation = FVector::ZeroVector, const FLinearColor DrawColor = FLinearColor::Red, const float DrawArrowLength = 100.0f, const float ArrowHeadScale = 1.0f, const float Thickness = 0.0f, const FName Tag = TEXT("Dire` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 6, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L1033 _public prototype_ `static bool DrawDebugPoseControlFromPoseState(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FAnimDatabasePoseState& PoseState, const TArray<int32>& BoneIndices, const FLinearColor DrawColor = FLinearColor::Red, const float DrawVelocityLineScale = 0.1f, const float Thickness = 0.0f, const FName Tag = TEXT("Pose` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 6, ReturnDisplayName = "Success"))`
- L1034 _public prototype_ `static bool DrawDebugPoseControlFromPoseStateArrayViews(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FAnimDatabasePoseState& PoseState, const TArrayView<const int32> BoneIndices, const FLinearColor DrawColor = FLinearColor::Red, const float DrawVelocityLineScale = 0.1f, const float Thickness = 0.0f, const FName Tag = TEXT("Pose`
- L1037 _public prototype_ `static bool DrawDebugTrajectoryControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FLinearColor DrawColor = FLinearColor::Red, const float DrawArrowLength = 25.0f, const float PointRadius = 5.0f, const float ArrowHeadScale = 1.0f, const float Thickness = 0.0f, const int32 SegmentNum = 8, const FName Tag = TEXT("Traj` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L1040 _public prototype_ `static bool DrawDebugLocationTrajectoryControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FTransform& RelativeTransform = FTransform(), const FLinearColor DrawColor = FLinearColor::Red, const float PointRadius = 5.0f, const float Thickness = 0.0f, const int32 SegmentNum = 8, const FName Tag = TEXT("Loca` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 5, ReturnDisplayName = "Success", AutoCreateRefTerm = "RelativeTransform"))`
- L1043 _public prototype_ `static bool DrawDebugNamedExclusiveDiscreteControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Label, const FVector& Location, const FRotator& Rotation, const float Scale = 10.0f, const FLinearColor DrawColor = FLinearColor::Red, const float Thickness = 0.0f, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 8, ReturnDisplayName = "Success", AutoCreateRefTerm = "Location, Rotation"))`
- L1046 _public prototype_ `static bool DrawDebugNamedInclusiveDiscreteControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Label, const FVector& Location, const FRotator& Rotation, const float Scale = 10.0f, const FLinearColor DrawColor = FLinearColor::Red, const float Thickness = 0.0f, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 8, ReturnDisplayName = "Success", AutoCreateRefTerm = "Location, Rotation"))`
- L1049 _public prototype_ `static bool DrawDebugNamedSparseControl(const FDebugDrawer& Drawer, const FAnimGenControlObject& Object, const FAnimGenControlObjectElement Element, const FName Label, const FVector& Location, const FRotator& Rotation, const float Scale = 10.0f, const FLinearColor DrawColor = FLinearColor::Red, const float Thickness = 0.0f, const FName Tag = TEXT("Name` — `UFUNCTION(BlueprintPure = false, Category = "AnimGen", meta = (AdvancedDisplay = 8, ReturnDisplayName = "Success", AutoCreateRefTerm = "Location, Rotation"))`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API ANIMGEN_API`
- L37 _prototype_ `bool operator==(const FAnimGenControlSchemaElement& Lhs, const FAnimGenControlSchemaElement& Rhs);`
- L39 _prototype_ `uint32 GetTypeHash(const FAnimGenControlSchemaElement& Element);`
- L46 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonaa0a01930103`)
- L47 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonaa0a01930103`)
- L63 _prototype_ `bool operator==(const FAnimGenControlObjectElement& Lhs, const FAnimGenControlObjectElement& Rhs);`
- L65 _prototype_ `uint32 GetTypeHash(const FAnimGenControlObjectElement& Element);`
- L72 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonaa0a01930203`)
- L73 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonaa0a01930203`)
- L77 _namespace_ `namespace UE`
- L77 _namespace_ `namespace AnimGen` (scope `UE`)
- L135 _prototype_ `bool operator==(const FAnimGenControlSchema& Lhs, const FAnimGenControlSchema& Rhs);`
- L142 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonaa0a01930303`)
- L143 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonaa0a01930303`)
- L168 _prototype_ `bool operator==(const FAnimGenControlObject& Lhs, const FAnimGenControlObject& Rhs);`
- L175 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonaa0a01930403`)
- L176 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonaa0a01930403`)
- L196 _namespace_ `namespace UE`
- L196 _namespace_ `namespace AnimGen` (scope `UE`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGen/Public/AnimGenController.h` (Public)


#### class `UAnimGenControllerViewportSettings`  
`class UAnimGenControllerViewportSettings : public UObject`  
_L31-222_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class containing all the UAnimGenController Editor window viewport settings
- L41 _public member_ `TObjectPtr<USkeletalMesh> PreviewMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — Mesh to use for previewing the character
- L47 _public member_ `bool bDrawSkeleton = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton")` — If to draw the skeleton of all characters
- L51 _public member_ `bool bDrawRequiredBonesOnly = true;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — If to only draw the bones that are being encoded by the auto-encoder
- L55 _public member_ `bool bDrawSimpleSkeleton = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — Draw a simple skeleton made up of lines connecting bones
- L59 _public member_ `float DrawSkeletonOpacity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — Opacity of the drawn skeleton
- L63 _public member_ `float DrawSkeletonScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — The scale of the drawn skeleton bones
- L67 _public member_ `bool bDrawLinearVelocities = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — If to draw linear velocities for each of the skeleton's bones
- L71 _public member_ `float DrawLinearVelocitiesScale = 0.05f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawSkeleton && bDrawLinearVelocities", HideEditConditionToggle))` — The scale of the linear velocities being drawn
- L75 _public member_ `float DrawLinearVelocitiesOpacity = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawSkeleton && bDrawLinearVelocities", HideEditConditionToggle))` — Opacity of the linear velocities being drawn
- L79 _public member_ `bool bDrawAngularVelocities = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — If to draw angular velocities for each of the skeleton's bones
- L83 _public member_ `float DrawAngularVelocitiesScale = 2.5f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawSkeleton && bDrawAngularVelocities", HideEditConditionToggle))` — The scale of the angular velocities being drawn
- L87 _public member_ `float DrawAngularVelocitiesOpacity = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawSkeleton && bDrawAngularVelocities", HideEditConditionToggle))` — Opacity of the angular velocities being drawn
- L91 _public member_ `bool bDrawBoneTransforms = false;` — `UPROPERTY(EditAnywhere, Category = "Skeleton", meta = (EditCondition = "bDrawSkeleton", HideEditConditionToggle))` — If to draw bone transforms
- L97 _public member_ `bool bDrawRoot = false;` — `UPROPERTY(EditAnywhere, Category = "Root")` — If to draw the root of the skeleton as a transform
- L101 _public member_ `float DrawRootOpacity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Root", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawRoot", HideEditConditionToggle))` — Opacity of the drawn root
- L105 _public member_ `float DrawRootScale = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Root", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRoot", HideEditConditionToggle))` — The scale of the drawn root
- L111 _public member_ `bool bDrawTrajectories = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory")` — If to draw the trajectories of the selected ranges
- L115 _public member_ `bool bDrawTrajectoryOrientations = false;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (EditCondition = "bDrawTrajectories", HideEditConditionToggle))` — If to draw the trajectory orientations of the selected ranges
- L121 _public member_ `bool bRangesStartAtOrigin = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — Re-orients all ranges so that they start at the scene origin rather than wherever they started in the source data
- L125 _public member_ `bool bOffsetRanges = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin", HideEditConditionToggle))` — Offset different ranges away from origin so they can be viewed together
- L129 _public member_ `float RangeOffsetSpacing = 100.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bOffsetRanges", HideEditConditionToggle))` — Spacing to use for offsetting ranges
- L133 _public member_ `bool bOffsetRangesInGrid = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bOffsetRanges", HideEditConditionToggle))` — If to offset selected ranges as a grid
- L137 _public member_ `bool bDisableRootTranslation = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin", HideEditConditionToggle))` — Remove root translation when display ranges
- L141 _public member_ `bool bDisableRootRotation = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bRangesStartAtOrigin && bDisableRootTranslation", HideEditConditionToggle))` — Remove root rotation when display ranges
- L145 _public member_ `bool bDrawRangeIdentifier = true;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — If to draw the colored range identifier over the character to show which range in the query the animation is from
- L149 _public member_ `int32 RangeIdentifierColorSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — Seed used for the colors of the range identifiers
- L153 _public member_ `float DrawRangeIdentifierThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Thickness of the range identifier
- L157 _public member_ `float DrawRangeIdentifierRadius = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Radius of the range identifier
- L161 _public member_ `float DrawRangeIdentifierOpacity = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Opacity of the range identifier
- L165 _public member_ `float DrawRangeIdentifierHeight = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bDrawRangeIdentifier", HideEditConditionToggle))` — Height offset used to draw the range identifier
- L169 _public member_ `bool bOverrideRangeIdentifierColor = false;` — `UPROPERTY(EditAnywhere, Category = "Ranges")` — If to override the range identifier color
- L173 _public member_ `FLinearColor RangeIdentifierColorOverride = FLinearColor(1.0f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Ranges", meta = (EditCondition = "bOverrideRangeIdentifierColor", HideEditConditionToggle))` — Color to use to override the range identifier
- L179 _public member_ `bool bDrawOrigin = true;` — `UPROPERTY(EditAnywhere, Category = "Origin")` — If to draw the scene origin as a transform
- L183 _public member_ `float DrawOriginLineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Thickness of the drawn scene origin
- L187 _public member_ `float DrawOriginOpacity = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Opacity of the drawn scene origin
- L191 _public member_ `float DrawOriginScale = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Origin", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bDrawOrigin", HideEditConditionToggle))` — Scale of the drawn scene origin
- L197 _public member_ `bool bDrawDebugTesting = true;` — `UPROPERTY(EditAnywhere, Category = "Behavior")` — If to call the draw debug function on the behavior
- L201 _public member_ `bool bDrawDebugTraining = true;` — `UPROPERTY(EditAnywhere, Category = "Behavior")` — If to call the draw debug function on the behavior preview
- L207 _public member_ `bool bDrawEncodedControlVector = false;` — `UPROPERTY(EditAnywhere, Category = "Control Encoding")` — If to draw a representation of the encoded control vector
- L211 _public member_ `int32 DrawEncodedControlVectorDimensions = 8;` — `UPROPERTY(EditAnywhere, Category = "Control Encoding", meta = (ClampMin = "1", UIMin = "1", ClampMax = "16", UIMax = "16", EditCondition = "bDrawEncodedControlVector", HideEditConditionToggle))` — How many dimensions of the encoded control vector to draw
- L215 _public member_ `float DrawEncodedControlVectorScale = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Control Encoding", meta = (ClampMin = "0", UIMin = "10", ClampMax = "100", UIMax = "100", EditCondition = "bDrawEncodedControlVector", HideEditConditionToggle))` — Scale of the drawing for the encoded control vector
- L219 _public member_ `FLinearColor DrawEncodedControlVectorColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.5f);` — `UPROPERTY(EditAnywhere, Category = "Control Encoding", meta = (EditCondition = "bDrawEncodedControlVector", HideEditConditionToggle))` — Color of the drawing for the encoded control vector

#### class `UAnimGenControllerTrainingSettings`  
`class UAnimGenControllerTrainingSettings : public UObject`  
_L226-452_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class containing all the UAnimGenController Editor window training settings
- L236 _public prototype_ `void ForceRefresh();` — `UFUNCTION(CallInEditor, Category = "Data", DisplayName = "Refresh")` — Forces the Update function to refresh the internal state
- L239 _public prototype_ `void LoadDatabaseAsync();` — Load the current database.
- L242 _public prototype_ `void LoadAutoEncoderAsync();` — Load the current auto-encoder.
- L245 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& Event) override;` — We use this async load changes to Database/AutoEncoder
- L253 _public member_ `TSoftObjectPtr<UAnimDatabase> Database = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Input database to train the network with
- L257 _public member_ `TObjectPtr<UAnimDatabaseFrameRangesFunction> FrameRanges = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Data")` — Frame ranges in the database to use for training. Leave this as None to train on the full database
- L261 _public member_ `TSoftObjectPtr<UAnimGenAutoEncoder> AutoEncoder = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Data")` — Input autoencoder to train the network with
- L265 _public member_ `TObjectPtr<UAnimGenBehavior> Behavior = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Data")` — Input Behavior to train the network on
- L270 _public member_ `bool bForceRefresh = false;` — Flag to force refresh the query during update
- L273 _public member_ `int32 DatabaseContentHash = 0;` — This hash is used to detect when the database might have changed and re-generate the control sets
- L276 _public member_ `FAnimDatabaseFrameRanges QueryRanges;` — Query Ranges object for the current query
- L279 _public member_ `FAnimGenControlSchema ControlSchema;` — Current Control Schema
- L282 _public member_ `FAnimGenControlSchemaElement ControlSchemaElement;` — Current Control Schema Element
- L285 _public member_ `FAnimGenControlObject ControlObject;` — Current Control Object
- L288 _public member_ `TArray<FAnimGenControlSet> ControlSets;` — Current Control Sets
- L291 _public member_ `TArray<TSharedPtr<UE::AnimDatabase::Editor::FQueryEntry>> QueryEntries;` — List of UI entries for the current query
- L294 _public member_ `TArray<int32> SelectedRanges;` — Indices of all the currently selected ranges
- L297 _public member_ `int32 RangeIndentifierColorSeed = 1234;` — Seed used for the colors of the range identifiers
- L303 _public member_ `TObjectPtr<UAnimDatabaseDebugDraw> DebugDrawer;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Debug Draw")` — Custom debug draw object that can be used to add additional debug draw behavior
- L313 _public prototype_ `bool Update();` — Checks if ControlSets needs updating, and if so updates it. returns true if ControlSets was updated (and therefore the UI may need updating), otherwise false.
- L318 _private prototype_ `void UpdateQueryEntries();` — Internal function for updating the QueryEntries array from an updated QueryRanges
- L328 _public member_ `int32 DenoiserHiddenUnitNum = 1792;` — `UPROPERTY(EditAnywhere, Category = "Network", meta = (ClampMin = "1", UIMin = "1"))` — The number of hidden units used by the denoiser network on each layer
- L332 _public member_ `int32 DenoiserLayerNum = 10;` — `UPROPERTY(EditAnywhere, Category = "Network", meta = (ClampMin = "2", UIMin = "2"))` — The number of layers used by the denoiser network
- L336 _public member_ `int32 LOD0HiddenUnitNum = 1024;` — `UPROPERTY(EditAnywhere, Category = "Network", DisplayName = "LOD0 Hidden Unit Num", meta = (ClampMin = "1", UIMin = "1"))` — The number of hidden units used by the LOD0 network on each layer
- L340 _public member_ `int32 LOD0LayerNum = 8;` — `UPROPERTY(EditAnywhere, Category = "Network", DisplayName = "LOD0 Layer Num", meta = (ClampMin = "2", UIMin = "2"))` — The number of layers used by the LOD0 network
- L344 _public member_ `int32 LOD1HiddenUnitNum = 512;` — `UPROPERTY(EditAnywhere, Category = "Network", DisplayName = "LOD1 Hidden Unit Num", meta = (ClampMin = "1", UIMin = "1"))` — The number of hidden units used by the LOD1 network on each layer
- L348 _public member_ `int32 LOD1LayerNum = 6;` — `UPROPERTY(EditAnywhere, Category = "Network", DisplayName = "LOD1 Layer Num", meta = (ClampMin = "2", UIMin = "2"))` — The number of layers used by the LOD1 network
- L352 _public member_ `int32 LOD2HiddenUnitNum = 256;` — `UPROPERTY(EditAnywhere, Category = "Network", DisplayName = "LOD2 Hidden Unit Num", meta = (ClampMin = "1", UIMin = "1"))` — The number of hidden units used by the LOD2 network on each layer
- L356 _public member_ `int32 LOD2LayerNum = 4;` — `UPROPERTY(EditAnywhere, Category = "Network", DisplayName = "LOD2 Layer Num", meta = (ClampMin = "2", UIMin = "2"))` — The number of layers used by the LOD2 network
- L365 _public member_ `bool bUseCompressedLinearLayers = true;` — `UPROPERTY(EditAnywhere, Category = "Network", AdvancedDisplay)` — If the controller should use compressed learning layers. This reduces the memory use by half at some very small cost to accuracy.
- L369 _public member_ `EAnimGenActivationFunction ActivationFunction = EAnimGenActivationFunction::GELU;` — `UPROPERTY(EditAnywhere, Category = "Network", AdvancedDisplay)` — The activation function used by the networks
- L373 _public member_ `EAnimGenWeightInit WeightInit = EAnimGenWeightInit::Uniform;` — `UPROPERTY(EditAnywhere, Category = "Network", AdvancedDisplay)` — Network weight initialization method
- L382 _public member_ `int32 NumberOfTrainingIterations = 500000;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "1", UIMin = "1"))` — The number of iterations to train the reference flow-matching network. Typical values are between 100000 and 2000000. Larger values will improve motion fideltity and reduce noise, but can result in over-fitting where the character stuggles to transition between motions.
- L389 _public member_ `int32 NumberOfDistillationIterations = 200000;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "1", UIMin = "1"))` — The number of iterations to train the distilled LOD networks. Typical values are between 100000 and 1000000. Larger values will improve motion quality but can increase training time drastically.
- L393 _public member_ `float LearningRate = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Learning rate. Typical values are between 0.001 and 0.0001. Reduce if training is unsable. Generally this does not need adjusting.
- L401 _public member_ `int32 BatchSize = 512;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "1", UIMin = "1", UIMax = "16384"))` — Batch size to use for training. Smaller values can sometimes produce better results at the cost of slowing down training. Large batch sizes are much more computationally efficient when training on the GPU. Reduce this if you are getting GPU out-of-memory errors during training. Generally this should not need adjusting.
- L408 _public member_ `float PoseNoiseScale = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — The scale of noise to apply to the pose encoding during training. Larger values may allow the character to transition better between motions at the expense of making the result more noisy with less motion fidelity.
- L416 _public member_ `float RandomPoseSampleRate = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Training", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Rate at which to sample random previous poses during training. Setting this to a value larger than zero can greatly help the character transition between motions when the control input changes. However this can also cause the character to randomly transition at undesiable times too so you may want to set this to zero this if you prefer more strict pose continuity such for an idle controller.
- L423 _public member_ `bool bEnableLogging = false;` — `UPROPERTY(EditAnywhere, Category = "Training")` — If to enable logging to the UE log in the training subprocess. Enable this if training is failing for an unknown reason as it will allow you to check the log for errors.
- L427 _public member_ `bool bEnableTensorboard = false;` — `UPROPERTY(EditAnywhere, Category = "Training")` — If to enable logging to TensorBoard in the intermediate directory. This can slow down training but gives important analytics.
- L433 _public member_ `int32 RandomSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "Training", AdvancedDisplay, meta = (ClampMin = "0", UIMin = "0"))` — The seed used for any random sampling the trainer will perform, e.g. for weight initialization.
- L437 _public member_ `float ControlNoiseScale = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Training", AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Scale of noise to apply to the control inputs. Larger values may improve generalization a little.
- L441 _public member_ `int32 WarmupIterations = 1000;` — `UPROPERTY(EditAnywhere, Category = "Training", AdvancedDisplay, meta = (ClampMin = "1", UIMin = "1"))` — The number of learning rate warm-up iterations to apply. Stabilizes the beginning of training.
- L445 _public member_ `int32 DenoiserSteps = 4;` — `UPROPERTY(EditAnywhere, Category = "Training", AdvancedDisplay, meta = (ClampMin = "1", UIMin = "1"))` — Number of denoising steps to use during training of distilled LODs. Larger values may improve quality marginally but makes training slower.
- L449 _public member_ `EAnimGenTrainingDevice Device = EAnimGenTrainingDevice::GPU;` — `UPROPERTY(EditAnywhere, Category = "Training", AdvancedDisplay)` — The device to train on. Training on CPU, while possible, will typically be extremely slow.

#### class `UAnimGenController`  
`class UAnimGenController : public UDataAsset`  
_L461-615_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UDataAsset`
- desc: The Controller class represents a trained character controller that uses flow-matching and a neural-network to auto-regressively produce the character's pose frame by frame. A controller is always implicitly linked to a behavior which it was trained on - and input to the controller will be provided via the behavior.
- L467 _private prototype_ `UAnimGenController(const FObjectInitializer& ObjectInitializer);`
- L473 _public prototype_ `bool IsValid() const;` — `UFUNCTION(BlueprintPure, Category = "AnimGen")` — Check if the controller is valid and trained
- L477 _public prototype_ `void Invalidate();` — `UFUNCTION(BlueprintCallable, Category = "AnimGen")` — Reset the controller back to an untrained state
- L482 _public prototype_ `void NormalizeEncodedPoseVectors( const TLearningArrayView<2, float> OutNormalizedEncodedPoseVectors, const TLearningArrayView<2, const float> InUnnormalizedEncodedPoseVectors) const;` — Normalize encoded pose vectors to make them appropriate for the controller
- L487 _public prototype_ `void NormalizeEncodedPoseVectorsInplace(const TLearningArrayView<2, float> InOutEncodedPoseVectors) const;` — Normalize encoded pose vectors in-place to make them appropriate for the controller
- L490 _public prototype_ `void DenormalizeEncodedPoseVectors( const TLearningArrayView<2, float> OutUnnormalizedEncodedPoseVectors, const TLearningArrayView<2, const float> InNormalizedEncodedPoseVectors) const;` — De-normalize encoded pose vectors produced by the controller
- L495 _public prototype_ `void ClampNormalizedPoseVectorsInplace(const TLearningArrayView<2, float> InOutNormalizedEncodedPoseVectors) const;` — Clamp encoded pose vectors produced by the controller to within a valid range
- L498 _public prototype_ `void ScaleSamplingNoiseInplace(const TLearningArrayView<2, float> InOutSamplingNoise) const;` — Scale initial sampling noise in place to match normalized encoded pose vectors standard deviation
- L504 _public member_ `TObjectPtr<UAnimGenAutoEncoder> AutoEncoder = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Controller")` — Auto-Encoder which this controller uses
- L508 _public member_ `FAnimGenControlSchema ControlSchema;` — `UPROPERTY()` — Control Schema for the given Behavior
- L512 _public member_ `FAnimGenControlSchemaElement ControlSchemaElement;` — `UPROPERTY()` — Control Schema Element for the given Behavior
- L516 _public member_ `TObjectPtr<ULearningNeuralNetworkData> ControlEncoderNetwork = nullptr;` — `UPROPERTY(Instanced)` — Control Encoder Network
- L520 _public member_ `TObjectPtr<ULearningNeuralNetworkData> LOD0Network = nullptr;` — `UPROPERTY(Instanced)` — LOD0 Network
- L524 _public member_ `TObjectPtr<ULearningNeuralNetworkData> LOD1Network = nullptr;` — `UPROPERTY(Instanced)` — LOD1 Network
- L528 _public member_ `TObjectPtr<ULearningNeuralNetworkData> LOD2Network = nullptr;` — `UPROPERTY(Instanced)` — LOD2 Network
- L532 _public member_ `FFrameRate FrameRate = FFrameRate(60, 1);` — `UPROPERTY(VisibleAnywhere, Category = "Controller")` — The Frame Rate this controller was trained to run at
- L536 _public member_ `int32 ControlVectorSize = 0;` — `UPROPERTY()` — Size of the control vector used by this controller
- L540 _public member_ `int32 EncodedControlVectorSize = 0;` — `UPROPERTY()` — Size of the encoded control vector used by this controller
- L544 _public member_ `int32 ControlDistributionVectorSize = 0;` — `UPROPERTY()` — Size of the control distribution vector used to clamp controls for this controller
- L548 _public member_ `TArray<float> EncodedPoseMeans;` — `UPROPERTY()` — Mean of the encoded pose vectors used for training
- L552 _public member_ `TArray<float> EncodedPoseStds;` — `UPROPERTY()` — Std of the encoded pose vectors used for training
- L556 _public member_ `TArray<float> EncodedPoseMaxs;` — `UPROPERTY()` — Max of the encoded pose vectors used for training
- L560 _public member_ `TArray<float> EncodedPoseMins;` — `UPROPERTY()` — Min of the encoded pose vectors used for training
- L564 _public member_ `TArray<float> NormalizedPoseStds;` — `UPROPERTY()` — Std used for normalizing the encoded pose vectors
- L568 _public member_ `float EncodedPoseNormalizationScale = 1.0f;` — `UPROPERTY()` — Scale used for normalizing encoded pose vectors
- L572 _public member_ `TArray<float> ControlVectorDistributionMins;` — `UPROPERTY()` — Min of the control vectors used by this controller
- L576 _public member_ `TArray<float> ControlVectorDistributionMaxs;` — `UPROPERTY()` — Max of the control vectors used by this controller
- L584 _public member_ `int32 TrainedFrameRangesContentHash = 0;` — `UPROPERTY()` — The content hash of the frame ranges used for training
- L588 _public member_ `int32 TrainedAutoEncoderContentHash = 0;` — `UPROPERTY()` — The content hash of the auto-encoder used for training
- L592 _public member_ `int32 TrainedSchemaCompatibilityHash = 0;` — `UPROPERTY()` — The compatibility hash of the schema used for training
- L598 _public member_ `int32 ControlEncoderSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (ForceUnits = "Kilobytes"))` — Current size of the trained control encoder in kilobytes
- L602 _public member_ `int32 DenoiserSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Statistics", meta = (ForceUnits = "Kilobytes"))` — Current size of all the trained denoiser networks in kilobytes
- L608 _public member_ `TObjectPtr<UAnimGenControllerTrainingSettings> TrainingSettings;` — `UPROPERTY(Instanced)` — Editor-only object containing the training settings for the editor window
- L612 _public member_ `TObjectPtr<UAnimGenControllerViewportSettings> ViewportSettings;` — `UPROPERTY(Instanced)` — Editor-only object containing the viewport settings for the editor window

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API ANIMGEN_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace AnimDatabase` (scope `UE`)
- L24 _namespace_ `namespace Editor` (scope `UE::AnimDatabase`)

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGen/Public/AnimGenLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMGEN_API`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimGen, Log, All);`

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGen/Public/AnimGenTraining.h` (Public)


#### enum `EAnimGenTrainingDevice`  
`enum class EAnimGenTrainingDevice : uint8`  
_L9-13_
- reflection: `UENUM(BlueprintType, Category = "AnimGen")`
- desc: Enumeration of the training devices.
- L11 _public enumerator_ `CPU`
- L12 _public enumerator_ `GPU`

#### enum `EAnimGenActivationFunction`  
`enum class EAnimGenActivationFunction : uint8`  
_L17-30_
- reflection: `UENUM(BlueprintType, Category = "AnimGen")`
- desc: Enumeration of activation functions.
- L20 _public enumerator_ `ELU UMETA(DisplayName = "ELU")` — ELU Activation - Generally performs better than ReLU and is not prone to gradient collapse but slower to evaluate.
- L23 _public enumerator_ `ReLU UMETA(DisplayName = "ReLU")` — ReLU Activation - Fast to train and evaluate but occasionally causes gradient collapse and untrainable networks.
- L26 _public enumerator_ `TanH UMETA(DisplayName = "TanH")` — TanH Activation - Smooth activation function that is slower to train and evaluate but sometimes more stable for certain tasks.
- L29 _public enumerator_ `GELU UMETA(DisplayName = "GELU")` — GELU Activation - Similar to ELU but sometimes can perform better for deeper networks.

#### enum `EAnimGenWeightInit`  
`enum class EAnimGenWeightInit : uint8`  
_L34-38_
- reflection: `UENUM(BlueprintType, Category = "AnimGen")`
- desc: Enumeration of different weight initialization.
- L36 _public enumerator_ `Gaussian = 0`
- L37 _public enumerator_ `Uniform = 1`

### `Plugins/Experimental/Animation/AnimGen/Source/AnimGen/Public/AnimNode_AnimGenController.h` (Public)


#### struct `FAnimGenControllerCurveOutput`  
`struct FAnimGenControllerCurveOutput`  
_L26-43_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specifies a curve output from the controller
- L34 _public member_ `FName AutoEncoderAttributeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Auto-Encoder Attribute name
- L38 _public member_ `bool bOutputAutoEncoderAttributeActive = false;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Output if the provided attribute is active or not
- L42 _public member_ `FName OutputCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Output Curve name

#### struct `FAnimGenControllerAttributeOutput`  
`struct FAnimGenControllerAttributeOutput`  
_L47-68_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specifies an attribute output from the controller
- L55 _public member_ `FName AutoEncoderAttributeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Auto-Encoder Attribute name
- L59 _public member_ `bool bOutputAutoEncoderAttributeActive = false;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Output if the provided attribute is active or not
- L63 _public member_ `FName OutputAttributeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Output Attribute name
- L67 _public member_ `FName OutputBoneName = TEXT("roo` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Output Attribute bone

#### struct `FAnimGenControllerBoneOutput`  
`struct FAnimGenControllerBoneOutput`  
_L72-85_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specifies a bone transform output from the controller
- L80 _public member_ `FName AutoEncoderAttributeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Auto-Encoder Attribute name
- L84 _public member_ `FName OutputBoneName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Output Bone name

#### struct `FAnimGenControllerAnimNotifyOutput`  
`struct FAnimGenControllerAnimNotifyOutput`  
_L89-106_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specifies an Anim Notify output from the controller
- L97 _public member_ `FName AutoEncoderAttributeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Auto-Encoder Attribute name
- L101 _public member_ `TObjectPtr<UAnimNotify> AnimNotify;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Entry")` — Output Anim Notify
- L105 _public member_ `float Apprehension = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Entry", meta=(ClampMin="-0.9", UIMin="-0.9", ClampMax="0.9", UIMax="0.9", ForceUnits="s"))` — Amount of time before the event to output the notify

#### struct `FAnimGenControllerAnimNotifyStateOutput`  
`struct FAnimGenControllerAnimNotifyStateOutput`  
_L110-127_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specifies an Anim Notify State output from the controller
- L118 _public member_ `FName AutoEncoderAttributeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Auto-Encoder Attribute name
- L122 _public member_ `bool bOutputAutoEncoderAttributeActive = false;` — `UPROPERTY(EditAnywhere, Category = "Entry")` — Output if the provided attribute is active or not
- L126 _public member_ `TObjectPtr<UAnimNotifyState> AnimNotifyState;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Entry")` — Output Anim Notify State

#### struct `FAnimNode_AnimGenController`  
`struct FAnimNode_AnimGenController : public FAnimNode_Base`  
_L133-287_
- reflection: `USTRUCT(BlueprintInternalUseOnly, Experimental)`
- inherits: `FAnimNode_Base`
- desc: AnimNode that can be used to generate animation using an AnimGenController.
- L139 _public member_ `TObjectPtr<UAnimGenController> Controller;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinShownByDefault))` — Controller asset used by the node
- L143 _public member_ `FAnimGenControlObject ControlObject;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinShownByDefault))` — Control Object taken as input
- L147 _public member_ `FAnimGenControlObjectElement ControlObjectElement;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinShownByDefault))` — Control Object Element from Control Object to use as input
- L151 _public member_ `int32 LODLevel = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinShownByDefault, ClampMin = "0", UIMin = "0", ClampMax = "2", UIMax = "2"))` — Which LOD level to use
- L157 _public member_ `int32 Seed = 1234;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinHiddenByDefault, ClampMin = "0", UIMin = "0"))` — Random Seed to initialize sampling with
- L161 _public member_ `bool bResetOnBecomingRelevant = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If to reset the node when it becomes relevant
- L165 _public member_ `float EvaluationPeriodInFrames = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinHiddenByDefault, ClampMin = "0.0", UIMin = "0.0", ClampMax = "8.0", UIMax = "8.0"))` — The period at which to evaluate the controller in frames. Increasing this can improve performance at the cost of some responsiveness.
- L169 _public member_ `bool bForceEvaluation = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinHiddenByDefault))` — If to force an evaluation of the controller this frame
- L175 _public member_ `float MinPoseSmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Smoothing", meta = (PinHiddenByDefault, ClampMin = "0.0", UIMin = "0.0"))` — Minimum Smoothing time to use - mixes the predicted pose with an integration of the predicted velocity.
- L179 _public member_ `float MaxPoseSmoothingTime = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Smoothing", meta = (PinHiddenByDefault, ClampMin = "0.0", UIMin = "0.0"))` — Maximum Smoothing time to use - mixes the predicted pose with an integration of the predicted velocity.
- L183 _public member_ `float AttributeSmoothingTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Smoothing", meta = (PinHiddenByDefault, ClampMin = "0.0", UIMin = "0.0"))` — Smoothing to apply to predicted attributes
- L189 _public member_ `TArray<FAnimGenControllerCurveOutput> CurveOutputs;` — `UPROPERTY(EditAnywhere, Category = "Additional Outputs")` — Array of additional curve outputs
- L193 _public member_ `TArray<FAnimGenControllerAttributeOutput> AttributeOutputs;` — `UPROPERTY(EditAnywhere, Category = "Additional Outputs")` — Array of additional attribute outputs
- L197 _public member_ `TArray<FAnimGenControllerBoneOutput> BoneOutputs;` — `UPROPERTY(EditAnywhere, Category = "Additional Outputs")` — Array of additional bone outputs
- L201 _public member_ `TArray<FAnimGenControllerAnimNotifyOutput> AnimNotifyOutputs;` — `UPROPERTY(EditAnywhere, Category = "Additional Outputs")` — Array of additional Anim Notify outputs
- L205 _public member_ `TArray<FAnimGenControllerAnimNotifyStateOutput> AnimNotifyStateOutputs;` — `UPROPERTY(EditAnywhere, Category = "Additional Outputs")` — Array of additional Anim Notify State outputs
- L211 _public member_ `bool bApplyRootVelocityDeadzone = true;` — `UPROPERTY(EditAnywhere, Category = "Root Velocity Deadzone")` — If to clamp to zero root velocities that are below a given threshold
- L215 _public member_ `float RootLinearVelocityDeadzone = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Root Velocity Deadzone", meta = (EditCondition = "bApplyRootVelocityDeadzone", HideEditConditionToggle, ClampMin = "0.0", UIMin = "0.0", ForceUnits="cm/s"))` — Minimum linear velocity under which it will be clamped to zero when clamping is enabled
- L219 _public member_ `float RootAngularVelocityDeadzone = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Root Velocity Deadzone", meta = (EditCondition = "bApplyRootVelocityDeadzone", HideEditConditionToggle, ClampMin = "0.0", UIMin = "0.0", ForceUnits = "deg/s"))` — Minimum angular velocity under which it will be clamped to zero when clamping is enabled
- L224 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L225 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L226 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L232 _private member_ `FGraphTraversalCounter UpdateCounter;` — Update Counter for detecting being relevant
- L235 _private member_ `uint32 RandomState = 1234;` — Random state used for sampling initial noise
- L239 _private member_ `TObjectPtr<UAnimGenController> ActiveController = nullptr;` — `UPROPERTY(Transient)` — Current active controller object
- L243 _private member_ `TArray<FAnimNotifyEvent> AnimNotifyEvents;` — `UPROPERTY(Transient)` — Internal buffer of AnimNotifyEvents
- L247 _private member_ `TArray<FAnimNotifyEventReference> AnimNotifyEventReferences;` — `UPROPERTY(Transient)` — Internal buffer of AnimNotifyEventReferences
- L251 _private member_ `bool bControlsValid = false;`
- L252 _private member_ `int32 ControlSchemaHash = 0;`
- L253 _private member_ `int32 ControlVectorSize = 0;`
- L254 _private member_ `int32 EncodedControlVectorSize = 0;`
- L255 _private member_ `int32 ControlDistributionVectorSize = 0;`
- L256 _private member_ `TLearningArray<2, float> ControlVector;`
- L257 _private member_ `TLearningArray<2, float> EncodedControlVector;`
- L261 _private member_ `float PoseDeltaTime = 0.0f;`
- L262 _private member_ `float BlockTime = 0.0f;`
- L263 _private member_ `bool bPoseStateRequiresReset = true;`
- L264 _private member_ `int32 EncodedPoseVectorSize = 0;`
- L265 _private member_ `int32 PoseVectorSize = 0;`
- L266 _private member_ `TLearningArray<2, float> EncodedPoseVector;`
- L267 _private member_ `TLearningArray<2, float> EncodedPoseVectorBlock;`
- L268 _private member_ `TLearningArray<2, float> UnnormalizedEncodedPoseVector;`
- L269 _private member_ `TLearningArray<2, float> PoseVector;`
- L270 _private member_ `UE::AnimDatabase::FPoseData CurrPoseData;`
- L271 _private member_ `UE::AnimDatabase::FPoseData PrevPoseData;`
- L272 _private member_ `UE::AnimDatabase::FPoseData OutputPoseData;`
- L273 _private member_ `TArray<TTuple<FName, float>> OutputCurves;`
- L277 _private member_ `TLearningArray<2, float> DenoiserInputVector;`
- L278 _private member_ `TSharedPtr<UE::Learning::FNeuralNetworkInference> ControlEncoderInference;`
- L279 _private member_ `TSharedPtr<UE::Learning::FNeuralNetworkInference> LOD0Inference;`
- L280 _private member_ `TSharedPtr<UE::Learning::FNeuralNetworkInference> LOD1Inference;`
- L281 _private member_ `TSharedPtr<UE::Learning::FNeuralNetworkInference> LOD2Inference;`
- L282 _private member_ `TSharedPtr<UE::Learning::FNeuralNetworkInference> EncoderInference;`
- L283 _private member_ `TSharedPtr<UE::Learning::FNeuralNetworkInference> DecoderInference;`
- L286 _private member_ `const UE::Anim::IAnimRootMotionProvider* RootMotionProvider = nullptr;` — Root Motion Provider

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API ANIMGEN_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Anim` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Learning` (scope `UE`)
