# Plugins / NearestNeighborModelEditor

- module root: `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor`
- headers: 12; symbols: 234
- symbol kinds: class=18, enum=1, enumerator=1, function=4, macro=7, member=40, namespace=28, prototype=132, struct=1, typedef=2
- PrivateDependencyModuleNames: ComputeFramework, CoreUObject, DesktopPlatform, EditorFramework, EditorStyle, EditorWidgets, Engine, GeometryCache, InputCore, MLDeformerFramework, MLDeformerFrameworkEditor, NearestNeighborModel, Projects, PropertyEditor, RHI, RenderCore, SkeletalMeshDescription, Slate, SlateCore, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Private/NearestNeighborEditorHelpers.h` (Private)


#### class `UNearestNeighborAnimStream`  
`class UNearestNeighborAnimStream : public UObject`  
_L13-34_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L18 _public prototype_ `void Init(USkeleton* InSkeleton);` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L21 _public prototype_ `bool IsValid() const;` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L24 _public prototype_ `bool AppendFrames(const UAnimSequence* Anim, TArray<int32> Frames);` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L27 _public prototype_ `bool ToAnim(UAnimSequence* OutAnim) const;` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L30 _private member_ `TObjectPtr<USkeleton> Skeleton;`
- L31 _private member_ `TArray<TArray<FVector3f>> PosKeys;`
- L32 _private member_ `TArray<TArray<FQuat4f>> RotKeys;`
- L33 _private member_ `TArray<TArray<FVector3f>> ScaleKeys;`

#### class `UNearestNeighborGeometryCacheStream`  
`class UNearestNeighborGeometryCacheStream : public UObject`  
_L38-59_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L43 _public prototype_ `void Init(const UGeometryCache* InTemplateCache);` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L46 _public prototype_ `bool IsValid() const;` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L49 _public prototype_ `bool AppendFrames(const UGeometryCache* Cache, TArray<int32> Frames);` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L52 _public prototype_ `bool ToGeometryCache(UGeometryCache* OutCache);` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L55 _private member_ `const UGeometryCache* TemplateCache = nullptr;`
- L56 _private member_ `int32 TemplateNumTracks = 0;`
- L57 _private member_ `TArray<int32> TemplateTrackNumVertices;`
- L58 _private member_ `TArray<TArray<TArray<FVector3f>>> TrackToFrameToPositions;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NEARESTNEIGHBORMODELEDITOR_API`

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Private/NearestNeighborMenuTool.h` (Private)


#### class `UE::NearestNeighborModel::FNearestNeighborMenuTool`  
`class FNearestNeighborMenuTool : public TSharedFromThis<FNearestNeighborMenuTool>`  
_L16-30_
- inherits: `TSharedFromThis<FNearestNeighborMenuTool>`
- L19 _public prototype_ `FNearestNeighborMenuTool() = default;`
- L20 _public prototype_ `virtual ~FNearestNeighborMenuTool() = default;`
- L22 _public prototype_ `void Register();`
- L24 _public prototype_ `virtual FName GetToolName() = 0;`
- L25 _public prototype_ `virtual FText GetToolTip() = 0;`
- L26 _public prototype_ `virtual UObject* CreateData();`
- L27 _public prototype_ `virtual void InitData(UObject& Data, UE::MLDeformer::FMLDeformerEditorToolkit& Toolkit);`
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateAdditionalWidgets(UObject& Data, TWeakPtr<UE::MLDeformer::FMLDeformerEditorModel> EditorModel);` — Capture Widget.Data or Widget.EditorModel is not safe because they can be changed after CreateAdditionalWidgets is called. Capture Widget instead.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MLDeformer` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Private/NearestNeighborModelSectionCustomization.h` (Private)


#### class `UE::NearestNeighborModel::SNearestNeighborModelSectionWidget`  
`class SNearestNeighborModelSectionWidget : public SCompoundWidget`  
_L12-24_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SNearestNeighborModelSectionWidget)`
- L16 _public prototype_ `SLATE_ARGUMENT(UNearestNeighborModelSection*, Section) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L22 _private member_ `TObjectPtr<UNearestNeighborModelSection> Section;`
- L23 _private member_ `TSharedPtr<IDetailsView> DetailsView;`

#### class `UE::NearestNeighborModel::FNearestNeighborModelSectionCustomization`  
`class FNearestNeighborModelSectionCustomization : public IDetailCustomization`  
_L26-35_
- inherits: `IDetailCustomization`
- L29 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L34 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Private/Tools/NearestNeighborKMeansTool.h` (Private)


#### struct `FNearestNeighborKMeansInputData`  
`struct FNearestNeighborKMeansInputData`  
_L24-36_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `TObjectPtr<UAnimSequence> Poses;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")`
- L32 _public member_ `TObjectPtr<UGeometryCache> Cache;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", DisplayName = "(Optional) Cache")`
- L35 _public member_ `TArray<int> MustIncludeFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")`

#### class `UNearestNeighborKMeansData`  
`class UNearestNeighborKMeansData : public UObject`  
_L40-69_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L45 _public member_ `TObjectPtr<const UMLDeformerAsset> NearestNeighborModelAsset;` — `UPROPERTY(VisibleAnywhere, Category = "Input")`
- L49 _public member_ `int32 SectionIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")` — Section used to generate clustered poses.
- L53 _public member_ `int32 NumClusters = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (ClampMin = 1))` — Number of clusters to be generated.
- L57 _public member_ `bool bExtractGeometryCache = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")` — Whether to extract geometry cache at the same time.
- L60 _public member_ `TArray<FNearestNeighborKMeansInputData> Inputs;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")`
- L64 _public member_ `TObjectPtr<UAnimSequence> ExtractedPoses;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Output")` — Extracted poses.
- L68 _public member_ `TObjectPtr<UGeometryCache> ExtractedCache;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Output", meta = (EditCondition = "bExtractGeometryCache"))` — Extracted geometry cache.

#### class `UE::NearestNeighborModel::FNearestNeighborKMeansTool`  
`class FNearestNeighborKMeansTool : public FNearestNeighborMenuTool`  
_L73-82_
- inherits: `FNearestNeighborMenuTool`
- L76 _public prototype_ `virtual ~FNearestNeighborKMeansTool() = default;`
- L77 _public prototype_ `virtual FName GetToolName() override;`
- L78 _public prototype_ `virtual FText GetToolTip() override;`
- L79 _public prototype_ `virtual UObject* CreateData() override;`
- L80 _public prototype_ `virtual void InitData(UObject& Data, UE::MLDeformer::FMLDeformerEditorToolkit& Toolkit) override;`
- L81 _public prototype_ `virtual TSharedRef<SWidget> CreateAdditionalWidgets(UObject& Data, TWeakPtr<UE::MLDeformer::FMLDeformerEditorModel> InEditorModel) override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MLDeformer` (scope `UE`)
- L71 _namespace_ `namespace UE`
- L71 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Private/Tools/NearestNeighborStatsTool.h` (Private)


#### class `UNearestNeighborStatsData`  
`class UNearestNeighborStatsData : public UObject`  
_L19-31_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L24 _public member_ `TObjectPtr<const UMLDeformerAsset> NearestNeighborModelAsset;` — `UPROPERTY(VisibleAnywhere, Category = "Input")`
- L27 _public member_ `TObjectPtr<UAnimSequence> TestAnim;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")`
- L30 _public member_ `int32 SectionIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")`

#### class `UE::NearestNeighborModel::FNearestNeighborStatsTool`  
`class FNearestNeighborStatsTool : public FNearestNeighborMenuTool`  
_L35-44_
- inherits: `FNearestNeighborMenuTool`
- L38 _public prototype_ `virtual ~FNearestNeighborStatsTool() = default;`
- L39 _public prototype_ `virtual FName GetToolName() override;`
- L40 _public prototype_ `virtual FText GetToolTip() override;`
- L41 _public prototype_ `virtual UObject* CreateData() override;`
- L42 _public prototype_ `virtual void InitData(UObject& Data, UE::MLDeformer::FMLDeformerEditorToolkit& Toolkit) override;`
- L43 _public prototype_ `virtual TSharedRef<SWidget> CreateAdditionalWidgets(UObject& Data, TWeakPtr<UE::MLDeformer::FMLDeformerEditorModel> InEditorModel) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MLDeformer` (scope `UE`)
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Public/NearestNeighborEditorModel.h` (Public)


#### class `UE::NearestNeighborModel::FNearestNeighborEditorModel`  
`class FNearestNeighborEditorModel : public UE::MLDeformer::FMLDeformerMorphModelEditorModel`  
_L26-94_
- inherits: `UE::MLDeformer::FMLDeformerMorphModelEditorModel`
- L30 _public typedef_ `using FSection = UNearestNeighborModelSection;`
- L31 _public typedef_ `using FMLDeformerSampler = UE::MLDeformer::FMLDeformerSampler;`
- L34 _public prototype_ `static FMLDeformerEditorModel* MakeInstance();` — We need to implement this static MakeInstance method.
- L37 _public function_ `virtual FString GetReferencerName() const override` — FGCObject overrides.
- L41 _public prototype_ `virtual void Init(const InitSettings& Settings) override;` — FMLDeformerEditorModel overrides.
- L42 _public prototype_ `virtual TSharedPtr<FMLDeformerSampler> CreateSamplerObject() const override;`
- L43 _public prototype_ `virtual void CreateActors(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene) override;`
- L44 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L45 _public prototype_ `virtual void InitInputInfo(UMLDeformerInputInfo* InputInfo) override;`
- L46 _public prototype_ `virtual ETrainingResult Train() override;`
- L47 _public prototype_ `virtual bool LoadTrainedNetwork() const override;`
- L48 _public prototype_ `virtual FMLDeformerTrainingInputAnim* GetTrainingInputAnim(int32 Index) const override;`
- L49 _public prototype_ `virtual void UpdateTimelineTrainingAnimList() override;`
- L50 _public prototype_ `virtual void OnPropertyChanged(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L51 _public prototype_ `virtual void OnPostTraining(ETrainingResult TrainingResult, bool bUsePartiallyTrainedWhenAborted) override;`
- L52 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L53 _public prototype_ `virtual void UpdateTrainingDeviceList() override;`
- L54 _public prototype_ `virtual void CopyBaseSettingsFromModel(const FMLDeformerEditorModel* SourceEditorModel) override;`
- L58 _public function_ `virtual bool IsMorphWeightClampingSupported() const override` — UMLDeformerMorphModelEditorModel overrides.
- L61 _public prototype_ `void OnUpdateClicked();`
- L62 _public prototype_ `void ClearReferences();`
- L64 _public prototype_ `FVertexMapSelector* GetVertexMapSelector() const;`
- L65 _public prototype_ `FVertVizSelector* GetVertVizSelector() const;`
- L68 _protected prototype_ `virtual void CreateSamplers() override;`
- L69 _protected prototype_ `virtual bool IsAnimIndexValid(int32 Index) const override;`
- L72 _private member_ `static constexpr int32 DefaultState = INDEX_NONE;`
- L75 _private prototype_ `UNearestNeighborModel* GetCastModel() const;` — Some helpers that cast to this model's variants of some classes.
- L76 _private prototype_ `UNearestNeighborModelVizSettings* GetCastVizSettings() const;`
- L77 _private prototype_ `UMLDeformerComponent* GetTestMLDeformerComponent() const;`
- L78 _private prototype_ `USkeletalMeshComponent* GetTestSkeletalMeshComponent() const;`
- L79 _private prototype_ `UNearestNeighborModelInstance* GetTestNearestNeighborModelInstance() const;`
- L80 _private prototype_ `void CreateDefaultSection();`
- L82 _private prototype_ `EOpFlag Update();`
- L83 _private prototype_ `EOpFlag CheckNetwork();`
- L84 _private prototype_ `EOpFlag UpdateNearestNeighborData();`
- L85 _private prototype_ `EOpFlag UpdateMorphDeltas();`
- L86 _private prototype_ `void UpdateNearestNeighborIds();`
- L88 _private prototype_ `FNearestNeighborEditorModelActor* CreateNearestNeighborActor(UWorld* World) const;`
- L89 _private prototype_ `void UpdateNearestNeighborActor(FNearestNeighborEditorModelActor& Actor) const;`
- L91 _private member_ `FNearestNeighborEditorModelActor* NearestNeighborActor = nullptr;` — This should be only set in CreateActors() and is automatically deleted by the base class.
- L92 _private member_ `TUniquePtr<FVertexMapSelector> VertexMapSelector;`
- L93 _private member_ `TUniquePtr<FVertVizSelector> VertVizSelector;`

#### class `UE::NearestNeighborModel::FVertexMapSelector`  
`class FVertexMapSelector`  
_L96-111_
- L99 _public prototype_ `void Update(const USkeletalMesh* SkelMesh);`
- L100 _public prototype_ `TArray<TSharedPtr<FString>>* GetOptions();`
- L101 _public prototype_ `void OnSelectionChanged(UNearestNeighborModelSection& Section, TSharedPtr<FString> InSelectedItem, ESelectInfo::Type SelectInfo) const;`
- L102 _public prototype_ `TSharedPtr<FString> GetSelectedItem(const UNearestNeighborModelSection& Section) const;`
- L103 _public prototype_ `FString GetVertexMapString(const UNearestNeighborModelSection& Section) const;`
- L104 _public prototype_ `bool IsValid() const;`
- L107 _private prototype_ `void Reset();`
- L108 _private member_ `TArray<TSharedPtr<FString>> Options;`
- L109 _private member_ `TMap<TSharedPtr<FString>, FString> VertexMapStrings;`
- L110 _private member_ `static TSharedPtr<FString> CustomString;`

#### class `UE::NearestNeighborModel::FVertVizSelector`  
`class FVertVizSelector`  
_L113-127_
- L116 _public prototype_ `FVertVizSelector(UNearestNeighborModelVizSettings* InSettings);`
- L117 _public prototype_ `void Update(int32 NumSections);`
- L118 _public prototype_ `TArray<TSharedPtr<FString>>* GetOptions();`
- L119 _public prototype_ `void OnSelectionChanged(TSharedPtr<FString> InSelectedItem, ESelectInfo::Type SelectInfo) const;`
- L120 _public prototype_ `TSharedPtr<FString> GetSelectedItem() const;`
- L121 _public prototype_ `int32 GetSectionIndex(TSharedPtr<FString> Item) const;`
- L122 _public prototype_ `void SelectSection(int32 SectionIndex);`
- L125 _private member_ `TObjectPtr<UNearestNeighborModelVizSettings> Settings;`
- L126 _private member_ `TArray<TSharedPtr<FString>> Options;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NEARESTNEIGHBORMODELEDITOR_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Public/NearestNeighborEditorModelActor.h` (Public)


#### enum `UE::NearestNeighborModel::(anonymous)`  
``  
_L13-15_

#### class `UE::NearestNeighborModel::FNearestNeighborEditorModelActor`  
`class FNearestNeighborEditorModelActor : public UE::MLDeformer::FMLDeformerGeomCacheActor`  
_L17-31_
- inherits: `UE::MLDeformer::FMLDeformerGeomCacheActor`
- L21 _public prototype_ `FNearestNeighborEditorModelActor(const FConstructSettings& Settings);`
- L22 _public prototype_ `virtual ~FNearestNeighborEditorModelActor();`
- L24 _public prototype_ `void SetGeometryCache(UGeometryCache* InGeometryCache) const;`
- L25 _public prototype_ `void SetTrackedComponent(const UMLDeformerComponent* InComponent, int32 InSectionIndex);`
- L26 _public prototype_ `void Tick() const;`
- L29 _private member_ `int32 SectionIndex = INDEX_NONE;`
- L30 _private member_ `TWeakObjectPtr<const UMLDeformerComponent> TrackedComponent;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NearestNeighborModel` (scope `UE`)
- L14 _enumerator_ `ActorID_NearestNeighborActors = 6` (scope `UE::NearestNeighborModel::__anon731dfb8e0103`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Public/NearestNeighborGeomCacheSampler.h` (Public)


#### class `UE::NearestNeighborModel::FNearestNeighborGeomCacheSampler`  
`class FNearestNeighborGeomCacheSampler : public UE::MLDeformer::FMLDeformerGeomCacheSampler`  
_L18-51_
- inherits: `UE::MLDeformer::FMLDeformerGeomCacheSampler`
- L23 _public prototype_ `virtual void Sample(int32 InAnimFrameIndex) override;` — FMLDeformerGeomCacheSampler overrides
- L31 _public prototype_ `void Customize(UAnimSequence* Anim, UGeometryCache* Cache = nullptr);` — This will set the SkeletalMeshComponent with custom Anim and GeometryCacheComponent with custom Cache. Using this fuction will stop using Anim and Cache from the EditorModel. Using this function will break Sample(). Call CustomSample() instead. Do NOT use this function on EditorModel Samplers.
- L37 _public prototype_ `bool CustomSample(int32 Frame);` — Sample function used with Customize @return true if sampling is successful
- L44 _public prototype_ `TArray<uint32> GetMeshIndexBuffer() const;` — Get the Mesh Index Buffer of the skeletal mesh object used by the model. @return A flattened array of the index buffer.
- L47 _private prototype_ `void SampleDualQuaternionDeltas(int32 InAnimFrameIndex);`
- L48 _private prototype_ `EOpFlag GenerateMeshMappings();`
- L49 _private prototype_ `EOpFlag CheckMeshMappingsEmpty() const;`
- L50 _private prototype_ `FVector3f CalcDualQuaternionDelta(int32 VertexIndex, const FVector3f& WorldDelta, const FSkeletalMeshLODRenderData& SkelMeshLODData, const FSkinWeightVertexBuffer& SkinWeightBuffer) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NEARESTNEIGHBORMODELEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Public/NearestNeighborModelDetails.h` (Public)


#### class `UE::NearestNeighborModel::FNearestNeighborModelDetails`  
`class FNearestNeighborModelDetails : public ::UE::MLDeformer::FMLDeformerMorphModelDetails`  
_L18-50_
- inherits: `::UE::MLDeformer::FMLDeformerMorphModelDetails`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails overrides.
- L27 _public prototype_ `virtual void CreateCategories() override;`
- L31 _public prototype_ `virtual bool UpdateMemberPointers(const TArray<TWeakObjectPtr<UObject>>& Objects) override;` — FMLDeformerModelDetails overrides.
- L35 _private prototype_ `UNearestNeighborModel* GetCastModel() const;`
- L36 _private prototype_ `FNearestNeighborEditorModel* GetCastEditorModel() const;`
- L38 _private prototype_ `void CustomizeTrainingSettingsCategory() const;`
- L39 _private prototype_ `void CustomizeNearestNeighborSettingsCategory() const;`
- L40 _private prototype_ `void CustomizeSectionsCategory(IDetailLayoutBuilder& DetailBuilder);`
- L41 _private prototype_ `void CustomizeMorphTargetCategory(IDetailLayoutBuilder& DetailBuilder) const;`
- L42 _private prototype_ `void CustomizeStatusCategory() const;`
- L43 _private prototype_ `void CustomizeFileCacheCategory(IDetailLayoutBuilder& DetailBuilder) const;`
- L45 _private prototype_ `void GenerateSectionElementWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder);`
- L47 _private member_ `IDetailCategoryBuilder* NearestNeighborCategoryBuilder = nullptr;`
- L48 _private member_ `IDetailCategoryBuilder* StatusCategoryBuilder = nullptr;`
- L49 _private member_ `IDetailCategoryBuilder* SectionsCategoryBuilder = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NEARESTNEIGHBORMODELEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Public/NearestNeighborModelStyle.h` (Public)


#### class `UE::NearestNeighborModel::FNearestNeighborModelEditorStyle`  
`class FNearestNeighborModelEditorStyle : public FSlateStyleSet`  
_L11-19_
- inherits: `FSlateStyleSet`
- L15 _public prototype_ `FNearestNeighborModelEditorStyle();`
- L16 _public prototype_ `virtual ~FNearestNeighborModelEditorStyle();`
- L18 _public prototype_ `static FNearestNeighborModelEditorStyle& Get();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API NEARESTNEIGHBORMODELEDITOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Public/NearestNeighborModelVizSettingsDetails.h` (Public)


#### class `UE::NearestNeighborModel::FNearestNeighborModelVizSettingsDetails`  
`class FNearestNeighborModelVizSettingsDetails : public UE::MLDeformer::FMLDeformerMorphModelVizSettingsDetails`  
_L12-24_
- inherits: `UE::MLDeformer::FMLDeformerMorphModelVizSettingsDetails`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L18 _public prototype_ `virtual void AddAdditionalSettings() override;`
- L21 _private prototype_ `void AddTrainingMeshAdditionalSettings();`
- L22 _private prototype_ `void AddLiveAdditionalSettings();`
- L23 _private prototype_ `FNearestNeighborEditorModel* GetCastEditorModel() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API NEARESTNEIGHBORMODELEDITOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NearestNeighborModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Source/NearestNeighborModelEditor/Public/NearestNeighborTrainingModel.h` (Public)


#### class `UNearestNeighborTrainingModel`  
`class UNearestNeighborTrainingModel : public UMLDeformerGeomCacheTrainingModel`  
_L25-92_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMLDeformerGeomCacheTrainingModel`
- L31 _public prototype_ `virtual ~UNearestNeighborTrainingModel();`
- L32 _public prototype_ `virtual void Init(UE::MLDeformer::FMLDeformerEditorModel* InEditorModel) override;`
- L35 _public prototype_ `int32 Train() const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Python")`
- L38 _public prototype_ `int32 UpdateNearestNeighborData();` — `UFUNCTION(BlueprintImplementableEvent, Category = "Python")`
- L41 _public prototype_ `int32 KmeansClusterPoses(const UNearestNeighborKMeansData* KMeansData);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Python")`
- L44 _public prototype_ `bool GetNeighborStats(const UNearestNeighborStatsData* StatsData);` — `UFUNCTION(BlueprintImplementableEvent, Category = "Python")`
- L48 _protected member_ `TArray<float> CustomSamplerBoneRotations;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Python")`
- L51 _protected member_ `TArray<float> CustomSamplerDeltas;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Python")`
- L55 _private prototype_ `int32 GetNumFramesAnimSequence(const UAnimSequence* Anim) const;` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L58 _private prototype_ `int32 GetNumFramesGeometryCache(const UGeometryCache* GeometryCache) const;` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L61 _private prototype_ `const USkeleton* GetModelSkeleton(const UMLDeformerModel* Model) const;` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L64 _private prototype_ `UNearestNeighborModel* GetNearestNeighborModel() const;` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L67 _private prototype_ `bool SetCustomSamplerData(UAnimSequence* Anim, UGeometryCache* Cache = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L70 _private prototype_ `bool CustomSample(int32 Frame);` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L73 _private prototype_ `bool SetCustomSamplerDataFromSection(int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L76 _private prototype_ `TArray<float> GetUnskinnedVertexPositions();` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L79 _private prototype_ `TArray<int32> GetMeshIndexBuffer();` — `UFUNCTION(BlueprintPure, Category = "Python")`
- L82 _private prototype_ `UNearestNeighborModelInstance* CreateModelInstance();` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L85 _private prototype_ `void DestroyModelInstance(UNearestNeighborModelInstance* ModelInstance);` — `UFUNCTION(BlueprintCallable, Category = "Python")`
- L87 _private prototype_ `void SetNewCustomSampler();`
- L88 _private prototype_ `UNearestNeighborModel* GetCastModel() const;`
- L89 _private prototype_ `UE::NearestNeighborModel::FNearestNeighborEditorModel* GetCastEditorModel() const;`
- L91 _private member_ `TUniquePtr<UE::NearestNeighborModel::FNearestNeighborGeomCacheSampler> CustomSampler;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NEARESTNEIGHBORMODELEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace NearestNeighborModel` (scope `UE`)
