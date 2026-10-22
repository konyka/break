# Plugins / DetailPoseModelEditor

- module root: `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModelEditor`
- headers: 5; symbols: 50
- symbol kinds: class=5, enum=1, enumerator=1, function=2, member=5, namespace=8, prototype=28
- PrivateDependencyModuleNames: CoreUObject, DetailPoseModel, DeveloperSettings, Engine, GeometryCache, InputCore, MLDeformerFramework, MLDeformerFrameworkEditor, NeuralMorphModel, NeuralMorphModelEditor, Projects, PropertyEditor, Slate, SlateCore, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModelEditor/Public/DetailPoseEditorModel.h` (Public)


#### class `UE::DetailPoseModel::FDetailPoseEditorModel`  
`class FDetailPoseEditorModel : public UE::NeuralMorphModel::FNeuralMorphEditorModel`  
_L22-74_
- inherits: `UE::NeuralMorphModel::FNeuralMorphEditorModel`
- desc: The editor model for the Detail Pose Model.
- L27 _public prototype_ `static FMLDeformerEditorModel* MakeInstance();` — We need to implement this static MakeInstance method.
- L30 _public function_ `FString GetReferencerName() const override final` — FGCObject overrides.
- L34 _public prototype_ `FMLDeformerTrainingInputAnim* GetTrainingInputAnim(int32 Index) const override final;` — FMLDeformerEditorModel overrides.
- L35 _public prototype_ `void UpdateTimelineTrainingAnimList() override final;`
- L36 _public prototype_ `void OnPropertyChanged(FPropertyChangedEvent& PropertyChangedEvent) override final;`
- L37 _public prototype_ `void OnPostTraining(ETrainingResult TrainingResult, bool bUsePartiallyTrainedWhenAborted) override final;`
- L38 _public prototype_ `void InitInputInfo(UMLDeformerInputInfo* InputInfo) override final;`
- L39 _public prototype_ `void CreateActors(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene) override final;`
- L40 _public prototype_ `void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override final;`
- L41 _public prototype_ `void UpdateActorVisibility() override final;`
- L42 _public prototype_ `ETrainingResult Train() override final;`
- L46 _public prototype_ `void InitEngineMorphTargets(const TArray<FVector3f>& Deltas) override final;` — FMLDeformerMorphModelEditorModel overrides.
- L50 _public function_ `UDetailPoseModel* GetDetailPoseModel() const` — Get a pointer to the runtime model.
- L53 _private prototype_ `void CalculateDetailPoseDeltas(TArray<FVector3f>& OutDeltas, TArray<FDetailPoseModelDetailPose>& OutDetailPoses);`
- L54 _private prototype_ `void CalculateDetailPoseDeltas(int32 DetailPoseIndex, FMLDeformerGeomCacheSampler& Sampler, UDetailPoseModelInstance* ModelInstance, TArrayView<FVector3f> OutDeltas, FDetailPoseModelDetailPose& OutDetailPose);`
- L56 _private prototype_ `FDetailPoseModelEditorActor* CreateDetailPoseActor(UWorld* World) const;`
- L57 _private prototype_ `void UpdateDetailPoseActor(FDetailPoseModelEditorActor& Actor) const;`
- L59 _private prototype_ `UMLDeformerComponent* GetTestMLDeformerComponent() const;`
- L63 _private member_ `mutable TUniquePtr<FMLDeformerGeomCacheTrainingInputAnim> DetailPosesAnim;` — The training input anim object that holds the detail pose anim sequence and geom cache sequence.
- L66 _private member_ `TArray<FVector3f> DetailPosesDeltas;` — The detail pose deltas, of size (NumDetailPoses * NumBaseMeshVerts).
- L73 _private member_ `FDetailPoseModelEditorActor* DetailPoseActor = nullptr;` — The editor actor that represents the detail pose actor. It is used to show the currently used detail pose. It's creation and destruction are managed internally. @see CreateActors.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DetailPoseModel` (scope `UE`)

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModelEditor/Public/DetailPoseModelDetails.h` (Public)


#### class `UE::DetailPoseModel::FDetailPoseModelDetails`  
`class FDetailPoseModelDetails : public UE::NeuralMorphModel::FNeuralMorphModelDetails`  
_L22-45_
- inherits: `UE::NeuralMorphModel::FNeuralMorphModelDetails`
- desc: The details customization for the model settings of the Detail Pose Model. We implement a detail customization because we want to show some errors/warnings in case there are any issues with the detail pose animation sequence or geometry cache. Those errors could be like mismatching frame numbers etc.
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override final;` — ILayoutDetails overrides.
- L31 _public prototype_ `virtual void CreateCategories() override final;`
- L40 _private prototype_ `UDetailPoseModel* GetCastModel() const;` — Get a cast version of the UMLDeformerModel that we are showing details for. This casts the model to the UDetailPoseModel class. @result A pointer to the UDetailPoseModel that we are currently customizing, or nullptr when something is wrong.
- L44 _private member_ `IDetailCategoryBuilder* DetailPosesCategoryBuilder = nullptr;` — The category that holds the Detail Pose settings in the model details panel.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DetailPoseModel` (scope `UE`)

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModelEditor/Public/DetailPoseModelEditorActor.h` (Public)


#### enum `UE::DetailPoseModel::(anonymous)`  
``  
_L13-16_

#### class `UE::DetailPoseModel::FDetailPoseModelEditorActor`  
`class FDetailPoseModelEditorActor : public UE::MLDeformer::FMLDeformerGeomCacheActor`  
_L23-57_
- inherits: `UE::MLDeformer::FMLDeformerGeomCacheActor`
- desc: The editor actor for the Detail Pose model. This represents the visual detail pose actor inside the ML Deformer asset editor's viewport. It is used to show the current closest matching detail pose, compared to the current pose of our skeletal mesh component.
- L27 _public prototype_ `FDetailPoseModelEditorActor(const FConstructSettings& Settings);`
- L28 _public prototype_ `virtual ~FDetailPoseModelEditorActor();`
- L35 _public prototype_ `void SetGeometryCache(UGeometryCache* InGeometryCache) const;` — Set the geometry cache asset to use to render in the editor viewport. This should be the detail pose geometry cache. @param InGeometryCache The geometry cache to use to render the detail poses.
- L43 _public prototype_ `void SetTrackedComponent(const UMLDeformerComponent* InComponent);` — Specify which ML Deformer component to extract the current closest detail pose from. The Tick method will use this and update the geometry cache components current time value based on this. @param InComponent The ML Deformer Component to grab the current frame index from inside the detail pose geometry cache. @see Tick.
- L52 _public prototype_ `void Tick() const;` — Tick the editor actor, which will basically tick the geometry cache component and set it to the frame that is the current closest detail pose as reported by the tracked ML Deformer component. The ML Deformer component (or well the UDetailPoseModelInstance inside it) stores the current closest detail pose. We grab the frame number of that pose (the frame number inside the Geometry Cache), and then set the internal geometry cache component's time to this frame number to display this pose.
- L56 _private member_ `TWeakObjectPtr<const UMLDeformerComponent> TrackedComponent;` — The ML Deformer component from which we grab the current frame value.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DetailPoseModel` (scope `UE`)
- L15 _enumerator_ `ActorID_DetailPoseActor = 6` (scope `UE::DetailPoseModel::__anon9c95cec90103`) — The detail pose actor, which shows the current closest matching detail pose.

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModelEditor/Public/DetailPoseModelEditorStyle.h` (Public)


#### class `UE::DetailPoseModel::FDetailPoseModelEditorStyle`  
`class FDetailPoseModelEditorStyle : public FSlateStyleSet`  
_L13-21_
- inherits: `FSlateStyleSet`
- desc: The styles used in the Detail Pose editor model. This contains things like colors for the label of the Detail Pose model rendered in the viewport.
- L17 _public prototype_ `FDetailPoseModelEditorStyle();`
- L18 _public prototype_ `virtual ~FDetailPoseModelEditorStyle();`
- L20 _public prototype_ `static FDetailPoseModelEditorStyle& Get();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DetailPoseModel` (scope `UE`)

### `Plugins/Experimental/Animation/MLDeformer/DetailPoseModel/Source/DetailPoseModelEditor/Public/DetailPoseTrainingModel.h` (Public)


#### class `UDetailPoseTrainingModel`  
`class UDetailPoseTrainingModel : public UNeuralMorphTrainingModel`  
_L15-19_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UNeuralMorphTrainingModel`
- desc: The Training Model for the Detail Pose Model. Even though this is an empty class we still need it, as we inherit from it inside the Python code. This allows us to separate it from the Neural Morph Model that we inherited from. We basically find an object of this class type and call the Train method on that in Python.
