# Plugins / SVGImporter

- module root: `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter`
- headers: 22; symbols: 806
- symbol kinds: class=17, delegate=8, enum=10, enumerator=48, function=122, member=244, namespace=5, prototype=259, struct=32, variable=61
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, GeometryAlgorithms, GeometryCore, GeometryFramework, GeometryScriptingCore, Projects, RHI, Slate, SlateCore
- PublicDependencyModuleNames: Core, GeometryFramework, GeometryScriptingEditor, LevelEditor, UnrealEd

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Private/ProceduralMeshes/SVGFillComponent.h` (Private)


#### struct `FSVGFillShape`  
`struct FSVGFillShape`  
_L10-25_
- reflection: `USTRUCT()`
- L15 _public member_ `TArray<FVector2D> ShapeVertices;` — `UPROPERTY()`
- L18 _public member_ `bool bShouldBeDrawn = true;` — `UPROPERTY()`
- L20 _public function_ `FSVGFillShape()`
- L21 _public function_ `FSVGFillShape(const TArray<FVector2D>& InVertices, bool bInShouldBeDrawn) : ShapeVertices(InVertices) , bShouldBeDrawn(bInShouldBeDrawn)`

#### struct `FSVGFillMeshData`  
`struct FSVGFillMeshData`  
_L28-36_
- reflection: `USTRUCT()`
- L33 _public member_ `TArray<FSVGFillShape> ShapesToDraw;` — `UPROPERTY()`
- L35 _public prototype_ `void Init(const TArray<FSVGPathPolygon>& InShapes);`

#### struct `FSVGFillParameters`  
`struct FSVGFillParameters`  
_L38-62_
- L40 _public member_ `TArray<FSVGPathPolygon> Shapes;`
- L42 _public member_ `FColor Color;`
- L44 _public member_ `float Extrude = 0.0f;`
- L46 _public member_ `bool bSimplify = false;`
- L48 _public member_ `float BevelDistance = 0.0f;`
- L50 _public member_ `bool bSmoothShapes = false;`
- L52 _public member_ `float SmoothingOffset = 150.0f;`
- L54 _public member_ `bool bUnlit = false;`
- L56 _public member_ `bool bCastShadow = false;`
- L58 _public function_ `FSVGFillParameters(const TArray<FSVGPathPolygon>& InShapes) :Shapes(InShapes)`

#### class `USVGFillComponent`  
`class USVGFillComponent : public USVGDynamicMeshComponent`  
_L65-119_
- reflection: `UCLASS(ClassGroup=(SVGImporter), Meta = (BlueprintSpawnableComponent))`
- inherits: `USVGDynamicMeshComponent`
- L70 _public prototype_ `void GenerateFillMesh(const FSVGFillParameters& InFillParameters);`
- L71 _public prototype_ `void SetSmoothFillShapes(bool bInSmoothFillShapes, float InSmoothingOffset);`
- L76 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L77 _protected prototype_ `virtual void PostEditImport() override;`
- L79 _protected prototype_ `virtual void PostLoad() override;`
- L83 _protected prototype_ `virtual void RegisterDelegates() override;`
- L84 _protected prototype_ `virtual void RegenerateMesh() override;`
- L85 _protected function_ `virtual FName GetShapeType() const override`
- L88 _protected prototype_ `void RefreshNormals();`
- L89 _protected prototype_ `void InitBasePolygons();`
- L90 _protected prototype_ `void GenerateFillMeshInternal();`
- L92 _protected prototype_ `void LoadCachedMeshToDynamicMesh(const TOptional<UE::Geometry::FDynamicMesh3>& InSourceMesh);`
- L93 _protected prototype_ `void ApplyExtrude(float InExtrudeValue);`
- L94 _protected prototype_ `void ApplySimplifyAndBevel();`
- L97 _protected prototype_ `void ApplyFinalMeshChanges();` — Applies all changes after extrusion. Includes beveling.
- L100 _protected prototype_ `void ApplyFillExtrude();` — Applies all changes from extrusion on.
- L103 _protected prototype_ `void ApplyFillBevel();` — Applies changes from extrude on.
- L105 _protected member_ `TOptional<UE::Geometry::FDynamicMesh3> CachedExtrudedMesh;`
- L106 _protected member_ `TOptional<UE::Geometry::FDynamicMesh3> CachedBasePolygon;`
- L109 _protected member_ `bool bSimplify;` — `UPROPERTY()`
- L112 _protected member_ `bool bBypassClipper;` — `UPROPERTY()`
- L115 _protected member_ `float SmoothingOffset;` — `UPROPERTY()`
- L118 _protected member_ `FSVGFillMeshData FillMeshData;` — `UPROPERTY()`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Private/ProceduralMeshes/SVGStrokeComponent.h` (Private)


#### struct `FSVGStrokeParameters`  
`struct FSVGStrokeParameters`  
_L8-32_
- L10 _public member_ `const TArray<FVector>& StrokePoints;`
- L12 _public member_ `float Thickness = 0;`
- L14 _public member_ `FColor InColor;`
- L16 _public member_ `bool bIsClosed = false;`
- L18 _public member_ `bool bIsClockwise = false;`
- L20 _public member_ `EPolygonOffsetJoinType JoinStyle{};`
- L22 _public member_ `float Extrude = 0;`
- L24 _public member_ `bool bUnlit = false;`
- L26 _public member_ `bool bCastShadow = false;`
- L28 _public function_ `FSVGStrokeParameters(const TArray<FVector>& InPoints) : StrokePoints(InPoints)`

#### class `USVGStrokeComponent`  
`class USVGStrokeComponent : public USVGDynamicMeshComponent`  
_L35-78_
- reflection: `UCLASS(ClassGroup=(SVGImporter), Meta = (BlueprintSpawnableComponent))`
- inherits: `USVGDynamicMeshComponent`
- L40 _public prototype_ `void GenerateStrokeMesh(const FSVGStrokeParameters& InStrokeParameters);`
- L42 _public prototype_ `void SetJointStyle(EPolygonOffsetJoinType InJoinStyle);`
- L43 _public prototype_ `void SetStrokeWidth(float InStrokesWidth);`
- L48 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L53 _protected prototype_ `virtual void RegisterDelegates() override;`
- L54 _protected prototype_ `virtual void RegenerateMesh() override;`
- L55 _protected function_ `virtual FName GetShapeType() const override`
- L58 _protected prototype_ `void GenerateStrokeMeshInternal();`
- L59 _protected prototype_ `void GenerateMainStrokeGeometry(float InThickness, float InExtrude);`
- L60 _protected prototype_ `void ApplyStrokeExtrude();`
- L62 _protected prototype_ `void CleanupStrokeMesh();`
- L65 _protected member_ `TArray<FVector> StrokePoints;` — `UPROPERTY()`
- L68 _protected member_ `float StrokeThickness;` — `UPROPERTY()`
- L71 _protected member_ `bool bStrokeIsClosed;` — `UPROPERTY()`
- L74 _protected member_ `bool bStrokeIsClockwise;` — `UPROPERTY()`
- L77 _protected member_ `EPolygonOffsetJoinType JoinStyle;` — `UPROPERTY()`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Private/SVGImporterSettings.h` (Private)


#### class `USVGImporterSettings`  
`class USVGImporterSettings : public UDeveloperSettings`  
_L10-25_
- reflection: `UCLASS(config=Engine, meta=(DisplayName="SVG Importer"))`
- inherits: `UDeveloperSettings`
- L15 _public prototype_ `USVGImporterSettings();`
- L17 _public function_ `ESVGSplineConversionQuality GetSplineConversionQuality() const`
- L24 _private member_ `ESVGSplineConversionQuality SplineConversionQuality = ESVGSplineConversionQuality::VeryHigh;` — `UPROPERTY(Config, EditAnywhere, Category="SVG")` — The quality used to convert SVG Spline Data into poly lines

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Private/SVGJoinedShapesActor.h` (Private)


#### class `ASVGJoinedShapesActor`  
`class ASVGJoinedShapesActor : public ASVGDynamicMeshesContainerActor`  
_L14-30_
- reflection: `UCLASS(ClassGroup=(SVG), meta=(DisplayName="SVG Joint Shapes Actor", ComponentWrapperClass))`
- inherits: `ASVGDynamicMeshesContainerActor`
- L19 _public prototype_ `ASVGJoinedShapesActor();`
- L21 _public function_ `UJoinedSVGDynamicMeshComponent* GetDynamicMeshComponent()`
- L24 _public prototype_ `virtual TArray<UDynamicMeshComponent*> GetSVGDynamicMeshes() override;`
- L29 _protected member_ `TObjectPtr<UJoinedSVGDynamicMeshComponent> JointDynamicMeshComponent;` — `UPROPERTY(Category="SVG", VisibleAnywhere, BlueprintReadOnly)`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Private/SVGShapeActor.h` (Private)


#### class `ASVGShapeActor`  
`class ASVGShapeActor : public ASVGDynamicMeshesContainerActor`  
_L18-36_
- reflection: `UCLASS(ClassGroup = (SVG), meta = (DisplayName = "SVG Shape Actor", ComponentWrapperClass))`
- inherits: `ASVGDynamicMeshesContainerActor`
- desc: Upon splitting SVG Actors, multiple shape actors will be created. Each will have their own SVG Shape.
- L23 _public prototype_ `ASVGShapeActor();`
- L25 _public prototype_ `void SetShape(const USVGDynamicMeshComponent* InShape);`
- L27 _public function_ `USVGDynamicMeshComponent* GetShape()`
- L30 _public prototype_ `virtual TArray<UDynamicMeshComponent*> GetSVGDynamicMeshes() override;`
- L35 _protected member_ `TObjectPtr<USVGDynamicMeshComponent> SVGShape;` — `UPROPERTY(Category = "SVG", VisibleAnywhere, BlueprintReadOnly)`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/ProceduralMeshes/JoinedSVGDynamicMeshComponent.h` (Public)


#### struct `FSVGShapeParameters`  
`struct FSVGShapeParameters`  
_L12-36_
- reflection: `USTRUCT()`
- L17 _public member_ `FString ShapeName;` — `UPROPERTY(VisibleAnywhere, Category="SVG")`
- L20 _public member_ `FLinearColor Color = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category="SVG", meta=(SVGShapeParamColor))`
- L23 _public member_ `int32 MaterialID = 0;` — `UPROPERTY()`
- L25 _public function_ `bool operator==(const FSVGShapeParameters& InShapeParameters) const`

#### struct `FJoinedSVGMeshParameters`  
`struct FJoinedSVGMeshParameters`  
_L39-48_
- reflection: `USTRUCT()`
- L44 _public member_ `bool bIsUnlit = true;` — `UPROPERTY()`
- L47 _public member_ `TSet<FSVGShapeParameters> ShapesParameters;` — `UPROPERTY(EditAnywhere, Category="SVG")`

#### enum `EJoinedSVGMeshColoring`  
`enum class EJoinedSVGMeshColoring : uint8`  
_L51-55_
- reflection: `UENUM()`
- L53 _public enumerator_ `SeparateColors`
- L54 _public enumerator_ `SingleColor`

#### class `UJoinedSVGDynamicMeshComponent`  
`class UJoinedSVGDynamicMeshComponent : public USVGBaseDynamicMeshComponent`  
_L58-124_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))`
- inherits: `USVGBaseDynamicMeshComponent`
- L65 _public prototype_ `UJoinedSVGDynamicMeshComponent();`
- L67 _public prototype_ `void Initialize(const FJoinedSVGMeshParameters& InJoinedMeshParameters);`
- L69 _public prototype_ `void StoreCurrentMesh();`
- L72 _public prototype_ `virtual void PostLoad() override;`
- L75 _public prototype_ `virtual void PostEditImport() override;`
- L76 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L80 _public prototype_ `void SetSVGIsUnlit(bool bInSVGIsUnlit);`
- L82 _public function_ `bool IsSVGUnlit() const`
- L84 _public prototype_ `void SetMainColor(const FLinearColor& InColor);`
- L86 _public function_ `const FLinearColor& GetMainColor() const`
- L89 _protected prototype_ `void LoadStoredMesh();`
- L91 _protected prototype_ `void LoadMaterialSetParameters();`
- L93 _protected prototype_ `void StoreMaterialSetParameters();`
- L95 _protected prototype_ `void RefreshSVGIsUnlit();`
- L97 _protected prototype_ `void LoadResources();`
- L99 _protected prototype_ `void UpdateMaterials(bool bInRefreshInstances = false);`
- L102 _protected member_ `TObjectPtr<UDynamicMesh> SVGStoredMesh;` — `UPROPERTY()`
- L105 _protected member_ `EJoinedSVGMeshColoring Coloring;` — `UPROPERTY(EditAnywhere, Category="SVG")`
- L108 _protected member_ `FLinearColor MainColor;` — `UPROPERTY(EditAnywhere, Category="SVG", Setter="SetMainColor", Getter="GetMainColor", meta=(EditCondition="Coloring == EJoinedSVGMeshColoring::SingleColor", EditConditionHides))`
- L111 _protected member_ `TSet<FSVGShapeParameters> ShapeParametersList;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category="SVG", meta=(ShowOnlyInnerProperties, EditCondition="Coloring == EJoinedSVGMeshColoring::SeparateColors", EditConditionHides, AllowPrivateAccess="true"))`
- L114 _protected member_ `TArray<TObjectPtr<UMaterialInstanceDynamic>> ShapesMaterials;` — `UPROPERTY(Transient)`
- L117 _protected member_ `TObjectPtr<UMaterial> MeshMaterial_Lit;` — `UPROPERTY(Transient)`
- L120 _protected member_ `TObjectPtr<UMaterial> MeshMaterial_Unlit;` — `UPROPERTY(Transient)`
- L123 _protected member_ `bool bSVGIsUnlit;` — `UPROPERTY(EditAnywhere, Category="SVG", Setter="SetSVGIsUnlit", Getter="IsSVGUnlit")`

#### Free symbols / members of external scopes

- L32 _function_ `friend uint32 GetTypeHash(const FSVGShapeParameters& InShapeParameters)`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/ProceduralMeshes/SVGBaseDynamicMeshComponent.h` (Public)


#### class `USVGBaseDynamicMeshComponent`  
`class USVGBaseDynamicMeshComponent : public UDynamicMeshComponent`  
_L9-26_
- reflection: `UCLASS()`
- inherits: `UDynamicMeshComponent`
- L15 _public prototype_ `USVGBaseDynamicMeshComponent();` — Sets default values for this component's properties
- L18 _public prototype_ `virtual void OnRegister() override;`
- L22 _protected prototype_ `void MarkSVGMeshUpdated();`
- L25 _private member_ `bool bMeshHasBeenUpdated;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/ProceduralMeshes/SVGDynamicMeshComponent.h` (Public)


#### enum `ESVGExtrudeType`  
`enum class ESVGExtrudeType : uint8`  
_L10-15_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `None`
- L13 _public enumerator_ `FrontFaceOnly`
- L14 _public enumerator_ `FrontBackMirror UMETA(DisplayName="Front-Back Mirrored")`

#### enum `ESVGEditMode`  
`enum class ESVGEditMode : uint8`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `Interactive`
- L21 _public enumerator_ `ValueSet`

#### enum `ESVGMaterialType`  
`enum class ESVGMaterialType : uint8`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `Default`
- L28 _public enumerator_ `Custom`

#### enum `EPolygonOffsetJoinType`  
`enum class EPolygonOffsetJoinType : uint8`  
_L34-39_
- reflection: `UENUM()`
- L36 _public enumerator_ `Square`
- L37 _public enumerator_ `Round` — Square,   Uniform squaring on all convex edge joins.
- L38 _public enumerator_ `Miter` — Round,    Arcs on all convex edge joins.

#### class `USVGDynamicMeshComponent`  
`class USVGDynamicMeshComponent : public USVGBaseDynamicMeshComponent`  
_L46-203_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(SVG))`
- inherits: `USVGBaseDynamicMeshComponent`
- L51 _public prototype_ `USVGDynamicMeshComponent();`
- L54 _public prototype_ `void FlattenShape();` — Calling this function will flatten the SVG Shape, converting it to a 2D polygon
- L58 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L59 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L60 _public prototype_ `virtual void PostEditImport() override;`
- L62 _public prototype_ `virtual void PostLoad() override;`
- L63 _public prototype_ `virtual void PostInitProperties() override;`
- L64 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L68 _public prototype_ `void ScaleShape(float InScale);` — Calling this function will scale the SVG Shape
- L71 _public prototype_ `void InitializeFromSVGDynamicMesh(const USVGDynamicMeshComponent* InOtherSVGDynamicMeshComponent);` — Initialize the current SVG Dynamic Mesh Component using the data from another component of the same type
- L73 _public prototype_ `void LoadResources();`
- L76 _public prototype_ `void SetMinExtrudeValue(float InBaseExtrude);` — Sets the minimum value for extrusion. The Extrude variable will be applyed to this value, will also refresh
- L77 _public prototype_ `void SetBevel(float InBevel);`
- L79 _public prototype_ `void SetExtrudeType(const ESVGExtrudeType InExtrudeType);`
- L81 _public prototype_ `void SetMeshEditMode(const ESVGEditMode InEditMode);`
- L82 _public prototype_ `void RefreshBevel();`
- L84 _public prototype_ `void StoreCurrentMesh() const;`
- L85 _public prototype_ `void LoadStoredMesh();`
- L87 _public prototype_ `void SetIsUnlit(bool bInIsUnlit);`
- L89 _public function_ `float GetExtrudeDepth() const`
- L91 _public function_ `virtual FName GetShapeType() const`
- L93 _public function_ `UMaterialInstanceDynamic* GetMeshMaterialInstance()`
- L96 _public member_ `FColor Color;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG")`
- L99 _public member_ `ESVGExtrudeType ExtrudeType = ESVGExtrudeType::None;` — `UPROPERTY(VisibleAnywhere, Category="SVG", meta=(EditCondition="ExtrudeType != ESVGExtrudeType::None", EditConditionHides))`
- L102 _public member_ `float Extrude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG", Meta = (ClampMin = -20.0f, UIMin = -20.0f, UIMax = 20.0f, Delta = 0.01f), meta=(EditCondition="ExtrudeType != ESVGExtrudeType::None", EditConditionHides))`
- L105 _public member_ `float Bevel;` — `UPROPERTY()`
- L108 _public member_ `bool bIsBevelBeingEdited;`
- L113 _protected member_ `TObjectPtr<UMaterial> MeshMaterial;` — `UPROPERTY()`
- L116 _protected member_ `TObjectPtr<UMaterial> MeshMaterial_Unlit;` — `UPROPERTY()`
- L119 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> MeshMaterialInstance;` — `UPROPERTY()`
- L122 _protected member_ `TObjectPtr<UMaterialInterface> AssignedMaterial;` — `UPROPERTY()`
- L125 _protected member_ `FColor SVGColor;` — `UPROPERTY()`
- L128 _protected member_ `float DefaultExtrude;` — `UPROPERTY()`
- L131 _protected member_ `float MinExtrudeValue;` — `UPROPERTY()`
- L134 _protected member_ `FVector ExtrudeDirection;` — `UPROPERTY()`
- L137 _protected member_ `bool bSVGIsUnlit = false;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L140 _protected member_ `float Scale;` — `UPROPERTY()`
- L144 _protected prototype_ `virtual void ResetToSVGValues();` — `UFUNCTION(CallInEditor, Category="SVG")`
- L147 _protected prototype_ `virtual UStaticMesh* BakeStaticMesh();` — `UFUNCTION(CallInEditor, Category="SVG")`
- L150 _protected prototype_ `void RefreshCustomMaterial();`
- L152 _protected prototype_ `void RefreshColor();`
- L154 _protected prototype_ `void ApplyExtrudePreview();`
- L156 _protected prototype_ `void ApplyScale();`
- L159 _protected prototype_ `virtual void SetExtrudeInternal(float InExtrude);` — Extrudes the dynamic mesh, also taking into account the base extrude value
- L162 _protected prototype_ `void SetColor(FColor InColor);` — `UFUNCTION(BlueprintCallable, Category="SVG")`
- L164 _protected prototype_ `void CreateSVGMaterialInstance();`
- L166 _protected member_ `float LastValueSetMinExtrude;`
- L168 _protected member_ `float LastValueSetExtrude;`
- L171 _protected member_ `FVector InternalCenter;` — `UPROPERTY()`
- L173 _protected member_ `ESVGEditMode CurrentEditMode;`
- L175 _protected function_ `virtual void RegisterDelegates()`
- L176 _protected function_ `virtual void RegenerateMesh()`
- L179 _protected prototype_ `void RefreshExtrude();` — Re-applies current extrusion value
- L180 _protected prototype_ `void SetCustomMaterial();`
- L183 _protected prototype_ `void RefreshMaterial();` — refreshes material settings (color, lit/unlit, custom material)
- L185 _protected prototype_ `void ApplySimpleUVPlanarProjection();`
- L186 _protected prototype_ `void Simplify();`
- L187 _protected prototype_ `void CenterMesh();`
- L189 _protected member_ `FSVGMeshActionDelegate OnApplyMeshExtrudeDelegate;`
- L190 _protected member_ `FSVGMeshActionDelegate OnApplyMeshBevelDelegate;`
- L191 _protected member_ `FSVGMeshActionDelegate OnApplyMeshBevelPreviewDelegate;`
- L194 _protected member_ `ESVGMaterialType MaterialType = ESVGMaterialType::Default;` — `UPROPERTY()`
- L202 _protected member_ `TObjectPtr<UDynamicMesh> SVGStoredMesh;` — `UPROPERTY()` — We serialize a copy of the mesh so that it is valid among sessions. This is needed when the geometry of a specialized SVG Shape (derived from USVGDynamicMeshComponent) is stored as a plain _new_ USVGDynamicMeshComponent, so its geometry cannot be re-generated using specialized functions from derived classes (e.g. after splitting SVG Actors)

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_DELEGATE(FSVGMeshActionDelegate) class UStaticMesh;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGActor.h` (Public)


#### enum `ESVGRenderMode`  
`enum class ESVGRenderMode : uint8`  
_L28-32_
- reflection: `UENUM()`
- L30 _public enumerator_ `DynamicMesh3D = 0 UMETA(DisplayName = "3D")`
- L31 _public enumerator_ `Texture2D = 1 UMETA(DisplayName = "2D")`

#### struct `FSVGActorInitGuard`  
`struct FSVGActorInitGuard`  
_L34-41_
- L36 _public prototype_ `FSVGActorInitGuard();`
- L37 _public prototype_ `~FSVGActorInitGuard();`
- L40 _private member_ `bool bPreviousValue;`

#### class `ASVGActor`  
`class ASVGActor : public ASVGDynamicMeshesContainerActor`  
_L44-363_
- reflection: `UCLASS()`
- inherits: `ASVGDynamicMeshesContainerActor`
- L49 _public prototype_ `ASVGActor();`
- L51 _public prototype_ `void Initialize();`
- L54 _public prototype_ `virtual void PostLoad() override;`
- L55 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L56 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L57 _public prototype_ `virtual void BeginDestroy() override;`
- L58 _public prototype_ `virtual void Destroyed() override;`
- L59 _public prototype_ `virtual void Serialize(FArchive& InArchive) override;`
- L61 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L62 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L67 _public prototype_ `virtual TArray<UDynamicMeshComponent*> GetSVGDynamicMeshes() override;`
- L71 _public function_ `USVGActorEditorComponent* GetSVGEditorComponent()`
- L74 _public prototype_ `TArray<TObjectPtr<USVGFillComponent>> GetFillComponents() const;`
- L75 _public prototype_ `TArray<TObjectPtr<USVGStrokeComponent>> GetStrokeComponents() const;`
- L77 _public function_ `TObjectPtr<USceneComponent> GetFillShapesRootComponent() const`
- L78 _public function_ `TObjectPtr<USceneComponent> GetStrokeShapesRootComponent() const`
- L80 _public function_ `const FString& GetSVGName() const`
- L82 _public function_ `float GetScale() const`
- L83 _public prototype_ `void SetScale(float InScale);`
- L85 _public function_ `float GetShapesOffset() const`
- L86 _public prototype_ `void SetShapesOffset(float InShapesOffset);`
- L88 _public function_ `float GetFillsExtrude() const`
- L89 _public prototype_ `void SetFillsExtrude(float InFillsExtrude);`
- L91 _public function_ `float GetStrokesExtrude() const`
- L92 _public prototype_ `void SetStrokesExtrude(float InStrokesExtrude);`
- L94 _public function_ `float GetBevelDistance() const`
- L95 _public prototype_ `void SetBevelDistance(float InBevelDistance);`
- L97 _public function_ `float GetStrokesWidth() const`
- L98 _public prototype_ `void SetStrokesWidth(float InStrokesWidth);`
- L100 _public function_ `bool GetVisible() const`
- L101 _public prototype_ `void SetVisible(bool bInVisible);`
- L104 _protected prototype_ `void RefreshFillShapesExtrude(const EPropertyChangeType::Type ChangeType = EPropertyChangeType::ValueSet);`
- L105 _protected prototype_ `void RefreshStrokeShapesExtrude(const EPropertyChangeType::Type ChangeType = EPropertyChangeType::ValueSet);`
- L106 _protected prototype_ `void RefreshFillShapesBevel(EPropertyChangeType::Type ChangeType = EPropertyChangeType::ValueSet);`
- L107 _protected prototype_ `void RefreshAllShapes();`
- L108 _protected prototype_ `void RefreshAllShapesMaterials();`
- L109 _protected prototype_ `void RefreshAllShapesCastShadow();`
- L110 _protected prototype_ `void RefreshSVGPlaneCastShadow() const;`
- L113 _protected prototype_ `void DisplayMissingSVGDataError(const FString& InErrorMsg);`
- L117 _protected prototype_ `void BakeToBlueprint() const;` — `UFUNCTION(CallInEditor, Category="SVG", meta=(ToolTip="Creates a Blueprint with all the SVG components as Static Meshes" , EditCondition="RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides))`
- L121 _protected prototype_ `void ResetGeometry();` — `UFUNCTION(CallInEditor, Category="SVG", meta=(ToolTip="Regenerates geometry from the referenced SVG Data Asset" , EditCondition="RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides))`
- L125 _protected prototype_ `void Split();` — `UFUNCTION(CallInEditor, Category="SVG", meta=(ToolTip="Splits this SVGActor into multiple Actors, each with a single SVG Shape component." , EditCondition="RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides))`
- L128 _protected prototype_ `void Generate();`
- L129 _protected prototype_ `void TryLoadDefaultSVGData();`
- L130 _protected prototype_ `void LoadResources();`
- L131 _protected prototype_ `void DestroySVGDynMeshComponents();`
- L132 _protected prototype_ `void RefreshPlaneMaterialInstance();`
- L133 _protected prototype_ `void DestroySVGPlane();`
- L134 _protected prototype_ `void CreateSVGPlane();`
- L135 _protected prototype_ `void ResetShapesExtrudes();`
- L136 _protected prototype_ `void CleanupEverything() const;`
- L137 _protected prototype_ `bool CanUpdateShapes() const;`
- L138 _protected prototype_ `bool CanGenerateShapes() const;`
- L139 _protected prototype_ `void RemoveAllDelegates() const;`
- L141 _protected prototype_ `void OnShapesGenerationEnd();`
- L142 _protected prototype_ `void OnShapesExtrudeEnd();`
- L144 _protected prototype_ `void CreateMeshesFromShape(const FSVGShape& InShape);`
- L146 _protected prototype_ `void AddStrokeComponent(const TArray<FVector>& InPoints, float InThickness, const FColor& InColor, bool bIsClosed, bool bIsClockwise , float InExtrudeOffset = 0.0f, const FString& InName = TEXT(""));`
- L149 _protected prototype_ `void AddFillComponent(const TArray<FSVGPathPolygon>& InShapesToDraw, const FColor& InColor, float InExtrudeOffset = 0.0f, const FString& InName = TEXT(""));`
- L151 _protected prototype_ `void UpdateFillShapesSmoothing();`
- L152 _protected prototype_ `void UpdateFillShapesSmoothingEnable();`
- L153 _protected prototype_ `void UpdateStrokesVisibility();`
- L154 _protected prototype_ `void UpdateStrokesWidth();`
- L156 _protected prototype_ `void ResetShapes();`
- L157 _protected prototype_ `void ClearShapes();`
- L158 _protected prototype_ `void ClearInstancedSVGShapes();`
- L160 _protected prototype_ `void UpdateStrokeShapesExtrude(float InExtrude, ESVGEditMode InEditMode = ESVGEditMode::ValueSet);`
- L161 _protected prototype_ `void UpdateFillShapesExtrude(float InExtrude, ESVGEditMode InEditMode = ESVGEditMode::ValueSet);`
- L162 _protected prototype_ `void UpdateFillShapesBevel(float InBevel, ESVGEditMode InEditMode);`
- L164 _protected prototype_ `void ScheduleShapesGeneration();`
- L165 _protected prototype_ `void ScheduleFillExtrudeUpdate();`
- L166 _protected prototype_ `void ScheduleStrokesExtrudeUpdate();`
- L167 _protected prototype_ `void ScheduleFillsSmoothUpdate(bool bInHasSmoothingFlagChanged = false);`
- L168 _protected prototype_ `void ScheduleStrokesWidthUpdate();`
- L169 _protected prototype_ `void ScheduleBevelsUpdate();`
- L171 _protected prototype_ `void TriggerActorDetailsRefresh();`
- L172 _protected prototype_ `void GenerateShapesOnEndFrame();`
- L173 _protected prototype_ `void UpdateBevelsOnEndFrame();`
- L174 _protected prototype_ `void UpdateFillsExtrudeOnEndFrame();`
- L175 _protected prototype_ `void UpdateStrokesExtrudeOnEndFrame();`
- L177 _protected prototype_ `void UpdateFillsSmoothingOnEndFrame();`
- L178 _protected prototype_ `void UpdateStrokesWidthOnEndFrame();`
- L180 _protected prototype_ `void GenerateNextMesh();`
- L181 _protected prototype_ `void CenterMeshes();`
- L182 _protected prototype_ `void ComputeOffsetScale();`
- L183 _protected prototype_ `void ApplyOffset();`
- L184 _protected prototype_ `void ApplyScaleAndCenter();`
- L186 _protected prototype_ `void OnVisibilityChanged();`
- L187 _protected prototype_ `void ShowShapes() const;`
- L188 _protected prototype_ `void HideShapes() const;`
- L191 _protected prototype_ `void ShowGenerationStartNotification();`
- L192 _protected prototype_ `void HideGenerationStartNotification();`
- L193 _protected prototype_ `void ShowGenerationFinishedNotification();`
- L196 _protected prototype_ `DECLARE_MULTICAST_DELEGATE(FSVGActorActionEndDelegate);`
- L197 _protected member_ `FSVGActorActionEndDelegate OnShapesGenerationEnd_Delegate;`
- L198 _protected member_ `FSVGActorActionEndDelegate OnFillsExtrudeEnd_Delegate;`
- L199 _protected member_ `FSVGActorActionEndDelegate OnStrokesExtrudeEnd_Delegate;`
- L202 _protected member_ `FSVGActorActionEndDelegate OnFillsUpdateEnd_Delegate;` — todo: we might be able to merge these 2 delegates with the more specific extrude ones above
- L203 _protected member_ `FSVGActorActionEndDelegate OnStrokesUpdateEnd_Delegate;`
- L207 _public member_ `TObjectPtr<USVGData> SVGData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG")`
- L210 _public member_ `ESVGRenderMode RenderMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG")`
- L215 _public member_ `float Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG" , Setter="SetScale", Getter= "GetScale" , meta=(ToolTip="Scale each SVG shape", Delta=0.01f, AllowPrivateAccess="true"))`
- L219 _public member_ `ESVGExtrudeType ExtrudeType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG" , meta=(EditCondition="RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides))`
- L224 _public member_ `float FillsExtrude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG", meta=(ClampMin=0.1f, UIMin=0.1f, UIMax=20.0f, Delta=0.01f) , Setter="SetFillsExtrude", Getter= "GetFillsExtrude" , meta=(EditCondition="ExtrudeType != ESVGExtrudeType::None && bSVGHasFills==true && RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides, AllowPrivateAccess="true"))`
- L229 _public member_ `float StrokesExtrude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG", meta=(ClampMin=0.01f, UIMin=0.01f, UIMax=20.0f, Delta=0.01f) , Setter="SetStrokesExtrude", Getter= "GetStrokesExtrude" , meta=(EditCondition="ExtrudeType != ESVGExtrudeType::None && bSVGHasStrokes==true && RenderMode == ESVGRenderMode::DynamicMesh3D && bIgnoreStrokes == false", EditConditionHides, AllowPrivateAccess="true"))`
- L234 _public member_ `float ShapesOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG" , Setter="SetShapesOffset", Getter= "GetShapesOffset" , meta=(ToolTip="Applies an offset to all SVG shapes along the X axis. Offset increases with each shapes, based on their order within the SVG source.", Delta=0.01f, AllowPrivateAccess="true"))`
- L239 _public member_ `float BevelDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG", meta=(ClampMin=0.0f, UIMin=0.0f, UIMax=0.5f, Delta=0.005f) , Setter="SetBevelDistance", Getter= "GetBevelDistance" , meta=(EditCondition="ExtrudeType != ESVGExtrudeType::None && bSVGHasFills==true && RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides))`
- L243 _public member_ `float ShapesOffsetScale;` — `UPROPERTY()` — This value is computed right after generating the SVG shapes, and used to scale the shapes offset based on the actor bounds extent
- L247 _public member_ `bool bSmoothFillShapes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG", meta=(ToolTip="Applies an offset to all SVG fill shapes edges, resulting in smoother geometry." , EditCondition="RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides))`
- L251 _public member_ `float SmoothingOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG" , meta=(EditCondition="bSmoothFillShapes==true && RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides), Category="SVG")`
- L255 _public member_ `bool bIgnoreStrokes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG", meta=(ToolTip="SVG strokes geometry will not be generated, even when available in SVG Data asset." , EditCondition="RenderMode == ESVGRenderMode::DynamicMesh3D", EditConditionHides))`
- L260 _public member_ `float StrokesWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG", meta=(ClampMin=0.01f, UIMin=0.01f, UIMax=20.0f) , Setter="SetStrokesWidth", Getter= "GetStrokesWidth" , meta=(EditCondition="bSVGHasStrokes == true && RenderMode == ESVGRenderMode::DynamicMesh3D && bIgnoreStrokes == false", EditConditionHides))`
- L264 _public member_ `EPolygonOffsetJoinType StrokeJoinStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SVG" , meta=(EditCondition="bSVGHasStrokes==true && RenderMode == ESVGRenderMode::DynamicMesh3D && bIgnoreStrokes == false", EditConditionHides))`
- L267 _public member_ `bool bSVGIsUnlit;` — `UPROPERTY(EditAnywhere, Category="Rendering", meta=(ToolTip="SVG Actor is unaffected by lighting. This option does not affect SVG shapes with a custom material."))`
- L270 _public member_ `bool bSVGCastsShadow;` — `UPROPERTY(EditAnywhere, Category="Rendering")`
- L274 _protected member_ `bool bVisible = true;` — `UPROPERTY(EditAnywhere, Setter="SetVisible", Getter="GetVisible", Category="Rendering")`
- L277 _protected member_ `bool bSVGHasStrokes;` — `UPROPERTY(EditDefaultsOnly, Category="SVG")`
- L280 _protected member_ `bool bSVGHasFills;` — `UPROPERTY(EditDefaultsOnly, Category="SVG")`
- L283 _protected member_ `TObjectPtr<USceneComponent> FillShapesRoot;` — `UPROPERTY()`
- L286 _protected member_ `TObjectPtr<USceneComponent> StrokeShapesRoot;` — `UPROPERTY()`
- L290 _protected member_ `TObjectPtr<USVGActorEditorComponent> SVGEditorComponent;` — `UPROPERTY()`
- L294 _protected member_ `TArray<TObjectPtr<USVGDynamicMeshComponent>> ShapeComponents;` — `UPROPERTY()`
- L297 _protected member_ `TObjectPtr<UStaticMeshComponent> SVGPlane;` — `UPROPERTY()`
- L300 _protected member_ `TObjectPtr<UStaticMesh> PlaneStaticMesh;` — `UPROPERTY()`
- L303 _protected member_ `TObjectPtr<UMaterial> PlaneMaterial;` — `UPROPERTY()`
- L306 _protected member_ `TObjectPtr<UMaterial> PlaneMaterial_Unlit;` — `UPROPERTY()`
- L309 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PlaneMaterialInstance;` — `UPROPERTY()`
- L312 _protected member_ `bool bMeshesShouldBeGenerated;` — `UPROPERTY()`
- L315 _protected member_ `FString SVGName;` — `UPROPERTY()`
- L317 _protected member_ `bool bIsGeneratingMeshes;`
- L318 _protected member_ `bool bIsUpdatingFills;`
- L319 _protected member_ `bool bStrokesExtrudeFinished;`
- L320 _protected member_ `bool bFillsExtrudeFinished;`
- L323 _protected member_ `float CurrExtrudeForDepth = 0.0f;` — Used to perform rudimentary depth ordering
- L325 _protected member_ `int32 GeneratedShapesCount = 0;`
- L326 _protected member_ `int32 UpdatedFillsCount = 0;`
- L327 _protected member_ `int32 UpdatedStrokesCount = 0;`
- L328 _protected member_ `int32 UpdatedBevelsCount = 0;`
- L330 _protected member_ `int32 UnnamedStrokesNum = 0;`
- L331 _protected member_ `int32 UnnamedFillsNum = 0;`
- L333 _protected member_ `FDelegateHandle GenMeshDelegateHandle;`
- L334 _protected member_ `FDelegateHandle FillsUpdateDelegateHandle;`
- L335 _protected member_ `FDelegateHandle StrokesUpdateDelegateHandle;`
- L336 _protected member_ `FDelegateHandle BevelUpdateDelegateHandle;`
- L339 _protected member_ `FVector OffsetToCenterSVGMeshes;` — `UPROPERTY()`
- L342 _protected member_ `TSharedPtr<FScopedTransaction> GenMeshTransaction;`
- L343 _protected member_ `TSharedPtr<FScopedTransaction> BevelsUpdateTransaction;`
- L344 _protected member_ `TSharedPtr<FScopedTransaction> FillsSmoothingTransaction;`
- L345 _protected member_ `TSharedPtr<FScopedTransaction> StrokesWidthTransaction;`
- L347 _protected member_ `TSharedPtr<SNotificationItem> DynMeshGenNotification;`
- L355 _private prototype_ `void SetFillsExtrudeInteractive(float InFillsExtrude);`
- L356 _private prototype_ `void SetStrokesExtrudeInteractive(float InStrokesExtrude);`
- L357 _private member_ `bool bFillsExtrudeInteractiveUpdate;`
- L358 _private member_ `bool bStrokesExtrudeInteractiveUpdate;`
- L361 _private member_ `bool bClearInstanceComponents;`
- L362 _private member_ `bool bInitialized;`

#### Free symbols / members of external scopes

- L196 _delegate_ `DECLARE_MULTICAST_DELEGATE(FSVGActorActionEndDelegate);`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGActorEditorComponent.h` (Public)


#### class `USVGActorEditorComponent`  
`class USVGActorEditorComponent : public USceneComponent`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneComponent`
- L16 _public prototype_ `ASVGActor* GetSVGActor() const;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGBakedActor.h` (Public)


#### struct `FSVGBakeElement`  
`struct FSVGBakeElement`  
_L9-21_
- reflection: `USTRUCT()`
- L14 _public member_ `TObjectPtr<UStaticMesh> Mesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "SVG Bake Element")`
- L17 _public member_ `FTransform Transform;` — `UPROPERTY(VisibleAnywhere, Category = "SVG Bake Element")`
- L20 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "SVG Bake Element")`

#### class `ASVGBakedActor`  
`class ASVGBakedActor : public AActor`  
_L24-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L29 _public prototype_ `ASVGBakedActor();`
- L32 _public member_ `TArray<FSVGBakeElement> SVGBakeElements;` — `UPROPERTY(EditAnywhere, Category = "Baked SVG")`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGData.h` (Public)


#### struct `FSVGDataInitializer`  
`struct FSVGDataInitializer`  
_L14-40_
- desc: Helper struct to provide SVGData objects with the necessary information for initialization.
- L16 _public function_ `FSVGDataInitializer()`
- L20 _public function_ `FSVGDataInitializer(const FString& InSVGTextBuffer, const FString& InSourceFilename = TEXT("")) : SVGTextBuffer(InSVGTextBuffer) , SourceFilename(InSourceFilename)`
- L27 _public function_ `bool IsInitialized() const` — Is this element initialized?
- L33 _public member_ `FString SVGTextBuffer = TEXT("");` — The SVG Text Buffer
- L36 _public member_ `FString SourceFilename = TEXT("");` — The SVG Filename. Can be empty if Text Buffer is not coming from a file
- L39 _public member_ `TArray<TSharedRef<FSVGBaseElement>> Elements;` — The SVG Elements already parsed from the SVG Text Buffer

#### enum `ESVGSplineConversionQuality`  
`enum class ESVGSplineConversionQuality : uint8`  
_L46-55_
- reflection: `UENUM(BlueprintType)`
- desc: Can be used to set the desired fidelity when converting SVG Splines into Polylines
- L48 _public enumerator_ `None UMETA(Hidden)`
- L49 _public enumerator_ `VeryLow`
- L50 _public enumerator_ `Low`
- L51 _public enumerator_ `Normal`
- L52 _public enumerator_ `Increased`
- L53 _public enumerator_ `High`
- L54 _public enumerator_ `VeryHigh`

#### class `USVGData`  
`class USVGData : public UObject`  
_L58-114_
- reflection: `UCLASS()`
- inherits: `UObject`
- L64 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSVGDataReimport);`
- L65 _public function_ `FOnSVGDataReimport& OnSVGDataReimport()`
- L68 _public prototype_ `void Initialize(const FSVGDataInitializer& InInitializer);` — Initialize this SVGData with the information provided by the initializer
- L70 _public prototype_ `void Reset();`
- L73 _public prototype_ `void GenerateSVGTexture();` — Generate a texture from the SVG information
- L74 _public prototype_ `void Reimport();`
- L77 _public function_ `const FString& GetSourceFilePath() const` — Get the SVG source file path, if available
- L79 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L82 _public prototype_ `void CreateShapes(const TArray<TSharedRef<FSVGBaseElement>>& InSVGElements);` — Create the shapes composing this SVG Data, starting from the information provided by SVG parsing
- L86 _public member_ `TObjectPtr<UTexture2D> SVGTexture;` — `UPROPERTY(VisibleAnywhere, Category = "SVG Data")`
- L89 _public member_ `FString SVGFileContent;` — `UPROPERTY(VisibleAnywhere, Category = "SVG Data")`
- L92 _public member_ `TArray<FSVGShape> Shapes;` — `UPROPERTY()`
- L96 _public member_ `FString SourceFilePath = TEXT("");` — `UPROPERTY(VisibleAnywhere, Category = "Source Asset")`
- L100 _public member_ `bool bEnableOverrideQuality = false;` — `UPROPERTY(EditAnywhere, Category="SVG Data", meta=(InlineEditConditionToggle))` — Enable quality overriding option
- L107 _public member_ `ESVGSplineConversionQuality OverrideQuality = ESVGSplineConversionQuality::VeryHigh;` — `UPROPERTY(EditAnywhere, Category="SVG Data", meta = (EditCondition = "bEnableOverrideQuality"))` — The quality used to convert SVG Spline Data into poly lines Changing this value will trigger a re-import (existing geometry will need to be re-generated).
- L110 _private prototype_ `float GetConversionQualityFactor() const;`
- L112 _private member_ `FOnSVGDataReimport OnSVGDataReimportDelegate;`

#### Free symbols / members of external scopes

- L64 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSVGDataReimport);`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGDefines.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SVGImporter` (scope `UE`)
- L8 _namespace_ `namespace Public` (scope `UE::SVGImporter`)
- L8 _namespace_ `namespace SVGConstants` (scope `UE::SVGImporter::Public`)
- L11 _variable_ `static TMap<const FName, const TCHAR*> Colors = { {TEXT("black"), TEXT("#000000")}, {TEXT("silver"), TEXT("#C0C0C0")}, {TEXT("gray"), TEXT("#808080")}, {TEXT("grey"), TEXT("#808080")}, {TEXT("white"), TEXT("#FFFFFF")}, {TEXT("maroon"), TEXT("#800000")}, {TEXT("red"), TEXT("#FF0000")}, {TEXT("orange"), TEXT("#FFA500")}, {TEXT("purple"), TEXT("#800080")}, {TEXT("fuchsia"), TEXT("#FF00FF")}, {TEXT("green"), TEXT("#008000")}, {TEXT("lime"), TEXT("#00FF00")}, {TEXT("olive"), TEXT("#808000")}, {TEXT("yellow"), TEXT("#FFFF00")}, {TEXT("navy"), TEXT("#000080")}, {TEXT("blue"), TEXT("#0000FF")}, {TEXT("teal"), TEXT("#008080")}, {TEXT("aqua"), TEXT("#00FFFF")} };` (scope `UE::SVGImporter::Public::SVGConstants`) — @todo: actual colors supported list is very long, see https://www.december.com/html/spec/colorsvghex.html
- L33 _variable_ `static const TCHAR* Auto = TEXT("aut` (scope `UE::SVGImporter::Public::SVGConstants`)
- L34 _variable_ `static const TCHAR* Transform = TEXT("tra` (scope `UE::SVGImporter::Public::SVGConstants`)
- L35 _variable_ `static const TCHAR* Translate = TEXT("tra` (scope `UE::SVGImporter::Public::SVGConstants`)
- L36 _variable_ `static const TCHAR* Rotate = TEXT("rot` (scope `UE::SVGImporter::Public::SVGConstants`)
- L37 _variable_ `static const TCHAR* SkewX = TEXT("ske` (scope `UE::SVGImporter::Public::SVGConstants`)
- L38 _variable_ `static const TCHAR* SkewY = TEXT("ske` (scope `UE::SVGImporter::Public::SVGConstants`)
- L39 _variable_ `static const TCHAR* Scale = TEXT("sca` (scope `UE::SVGImporter::Public::SVGConstants`)
- L40 _variable_ `static const TCHAR* Matrix = TEXT("mat` (scope `UE::SVGImporter::Public::SVGConstants`)
- L41 _variable_ `static const TCHAR* Id = TEXT("id"` (scope `UE::SVGImporter::Public::SVGConstants`)
- L42 _variable_ `static const TCHAR* Stroke = TEXT("str` (scope `UE::SVGImporter::Public::SVGConstants`)
- L43 _variable_ `static const TCHAR* StrokeWidth = TEXT("str` (scope `UE::SVGImporter::Public::SVGConstants`)
- L44 _variable_ `static const TCHAR* Fill = TEXT("fil` (scope `UE::SVGImporter::Public::SVGConstants`)
- L45 _variable_ `static const TCHAR* Class = TEXT("cla` (scope `UE::SVGImporter::Public::SVGConstants`)
- L46 _variable_ `static const TCHAR* Style = TEXT("sty` (scope `UE::SVGImporter::Public::SVGConstants`)
- L47 _variable_ `static const TCHAR* G = TEXT("g")` (scope `UE::SVGImporter::Public::SVGConstants`) — Group element
- L48 _variable_ `static const TCHAR* SVG = TEXT("svg` (scope `UE::SVGImporter::Public::SVGConstants`)
- L49 _variable_ `static const TCHAR* LinearGradient = TEXT("lin` (scope `UE::SVGImporter::Public::SVGConstants`)
- L50 _variable_ `static const TCHAR* RadialGradient = TEXT("rad` (scope `UE::SVGImporter::Public::SVGConstants`)
- L51 _variable_ `static const TCHAR* GradientStop = TEXT("sto` (scope `UE::SVGImporter::Public::SVGConstants`)
- L52 _variable_ `static const TCHAR* Offset = TEXT("off` (scope `UE::SVGImporter::Public::SVGConstants`)
- L53 _variable_ `static const TCHAR* StopColor = TEXT("sto` (scope `UE::SVGImporter::Public::SVGConstants`)
- L54 _variable_ `static const TCHAR* StopOpacity = TEXT("sto` (scope `UE::SVGImporter::Public::SVGConstants`)
- L55 _variable_ `static const TCHAR* GradientUnits = TEXT("gra` (scope `UE::SVGImporter::Public::SVGConstants`)
- L56 _variable_ `static const TCHAR* ClipPath = TEXT("cli` (scope `UE::SVGImporter::Public::SVGConstants`) — A clip path restricts the drawing region
- L57 _variable_ `static const TCHAR* UserSpaceOnUse = TEXT("use` (scope `UE::SVGImporter::Public::SVGConstants`) — Coordinate used by a Clip Path are defined with the Clip Path itself
- L58 _variable_ `static const TCHAR* ObjectBoundingBox = TEXT("obj` (scope `UE::SVGImporter::Public::SVGConstants`) — Coordinate used by a Clip Path are relative to the element
- L59 _variable_ `static const TCHAR* Rect = TEXT("rec` (scope `UE::SVGImporter::Public::SVGConstants`)
- L60 _variable_ `static const TCHAR* Circle = TEXT("cir` (scope `UE::SVGImporter::Public::SVGConstants`)
- L61 _variable_ `static const TCHAR* Ellipse = TEXT("ell` (scope `UE::SVGImporter::Public::SVGConstants`)
- L62 _variable_ `static const TCHAR* Line = TEXT("lin` (scope `UE::SVGImporter::Public::SVGConstants`)
- L63 _variable_ `static const TCHAR* Polygon = TEXT("pol` (scope `UE::SVGImporter::Public::SVGConstants`)
- L64 _variable_ `static const TCHAR* PolyLine = TEXT("pol` (scope `UE::SVGImporter::Public::SVGConstants`)
- L65 _variable_ `static const TCHAR* Path = TEXT("pat` (scope `UE::SVGImporter::Public::SVGConstants`)
- L66 _variable_ `static const TCHAR* PathLength = TEXT("pat` (scope `UE::SVGImporter::Public::SVGConstants`)
- L67 _variable_ `static const TCHAR* D = TEXT("d")` (scope `UE::SVGImporter::Public::SVGConstants`) — Path to be Drawn
- L68 _variable_ `static const TCHAR* Points = TEXT("poi` (scope `UE::SVGImporter::Public::SVGConstants`)
- L69 _variable_ `static const TCHAR* X = TEXT("x")` (scope `UE::SVGImporter::Public::SVGConstants`)
- L70 _variable_ `static const TCHAR* X1 = TEXT("x1"` (scope `UE::SVGImporter::Public::SVGConstants`) — X value for elements requiring more than one Point to be drawn
- L71 _variable_ `static const TCHAR* X2 = TEXT("x2"` (scope `UE::SVGImporter::Public::SVGConstants`) — X value for elements requiring more than one Point to be drawn
- L72 _variable_ `static const TCHAR* Y = TEXT("y")` (scope `UE::SVGImporter::Public::SVGConstants`)
- L73 _variable_ `static const TCHAR* Y1 = TEXT("y1"` (scope `UE::SVGImporter::Public::SVGConstants`) — Y value for elements requiring more than one Point to be drawn
- L74 _variable_ `static const TCHAR* Y2 = TEXT("y2"` (scope `UE::SVGImporter::Public::SVGConstants`) — Y value for elements requiring more than one Point to be drawn
- L75 _variable_ `static const TCHAR* CX = TEXT("cx"` (scope `UE::SVGImporter::Public::SVGConstants`) — Center Point X
- L76 _variable_ `static const TCHAR* CY = TEXT("cy"` (scope `UE::SVGImporter::Public::SVGConstants`) — Center Point Y
- L77 _variable_ `static const TCHAR* R = TEXT("r")` (scope `UE::SVGImporter::Public::SVGConstants`) — Radius of a circle
- L78 _variable_ `static const TCHAR* RX = TEXT("rx"` (scope `UE::SVGImporter::Public::SVGConstants`) — Radius X (e.g. Ellipse)
- L79 _variable_ `static const TCHAR* RY = TEXT("ry"` (scope `UE::SVGImporter::Public::SVGConstants`) — Radius Y (e.g. Ellipse)
- L80 _variable_ `static const TCHAR* Width = TEXT("wid` (scope `UE::SVGImporter::Public::SVGConstants`)
- L81 _variable_ `static const TCHAR* Height = TEXT("hei` (scope `UE::SVGImporter::Public::SVGConstants`)
- L82 _variable_ `static const TCHAR* HexPrefix = TEXT("#")` (scope `UE::SVGImporter::Public::SVGConstants`)
- L83 _variable_ `static const TCHAR* Percentage = TEXT("%")` (scope `UE::SVGImporter::Public::SVGConstants`)
- L84 _variable_ `static const TCHAR* RGB = TEXT("rgb` (scope `UE::SVGImporter::Public::SVGConstants`)
- L85 _variable_ `static const TCHAR* RGBA = TEXT("rgb` (scope `UE::SVGImporter::Public::SVGConstants`)
- L86 _variable_ `static const TCHAR* A = TEXT("a")` (scope `UE::SVGImporter::Public::SVGConstants`) — Alpha
- L87 _variable_ `static const TCHAR* Transparent = TEXT("tra` (scope `UE::SVGImporter::Public::SVGConstants`)
- L88 _variable_ `static const TCHAR* Display = TEXT("dis` (scope `UE::SVGImporter::Public::SVGConstants`)
- L89 _variable_ `static const TCHAR* None = TEXT("non` (scope `UE::SVGImporter::Public::SVGConstants`)
- L90 _variable_ `static const TCHAR* Inherit = TEXT("inh` (scope `UE::SVGImporter::Public::SVGConstants`)
- L91 _variable_ `static const TCHAR* URL_Start = TEXT("url` (scope `UE::SVGImporter::Public::SVGConstants`)
- L92 _variable_ `static const TCHAR* URL_End = TEXT(")")` (scope `UE::SVGImporter::Public::SVGConstants`)

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGDynamicMeshesContainerActor.h` (Public)


#### class `ASVGDynamicMeshesContainerActor`  
`class ASVGDynamicMeshesContainerActor : public AActor`  
_L11-17_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `AActor`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGElements.h` (Public)


#### enum `ESVGElementType`  
`enum class ESVGElementType : uint8`  
_L15-31_
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `Other`
- L19 _public enumerator_ `SVG`
- L20 _public enumerator_ `Style`
- L21 _public enumerator_ `Group`
- L22 _public enumerator_ `ClipPath`
- L23 _public enumerator_ `Path`
- L24 _public enumerator_ `Rectangle`
- L25 _public enumerator_ `Circle`
- L26 _public enumerator_ `Ellipse`
- L27 _public enumerator_ `Line`
- L28 _public enumerator_ `PolyLine`
- L29 _public enumerator_ `Polygon`
- L30 _public enumerator_ `Gradient`

#### struct `FSVGMatrix`  
`struct FSVGMatrix`  
_L33-75_
- L35 _public prototype_ `FSVGMatrix() = default;`
- L37 _public prototype_ `explicit FSVGMatrix(const FString& InMatrixString);`
- L39 _public prototype_ `void Decompose();`
- L41 _public prototype_ `void ApplyTransformToSplinePoint(FSplinePoint& OutSplinePoint);`
- L43 _public prototype_ `void ApplyTransformToPoint2D(FVector2D& OutPoint);`
- L45 _public function_ `const FTransform& GetTransform() const`
- L47 _public prototype_ `FShear2D GetShear() const;`
- L49 _public member_ `float A = 0.0f;`
- L50 _public member_ `float B = 0.0f;`
- L51 _public member_ `float C = 0.0f;`
- L52 _public member_ `float D = 0.0f;`
- L53 _public member_ `float Tx = 0.0f;`
- L54 _public member_ `float Ty = 0.0f;`
- L56 _public member_ `bool bIsMatrix = false;`
- L58 _public member_ `FVector2D Translation = FVector2D::ZeroVector;`
- L60 _public member_ `FVector2D Scale = FVector2D::UnitVector;`
- L62 _public member_ `float RotAngle = 0.0;`
- L64 _public member_ `FVector2D RotPivot = FVector2D::UnitVector;`
- L66 _public member_ `FVector2D Skew = FVector2D::ZeroVector;`
- L68 _public member_ `FTransform FinalTransform = FTransform::Identity;`
- L70 _public member_ `TArray<FString> TransformationsList;`
- L72 _public member_ `FVector Scale3D = FVector::OneVector;`
- L74 _public member_ `bool bIsInitialized = false;`

#### struct `FSVGBaseElement`  
`struct FSVGBaseElement : TSharedFromThis<FSVGBaseElement>`  
_L77-99_
- inherits: `TSharedFromThis<FSVGBaseElement>`
- L79 _public function_ `void SetName(const FString& InName)`
- L84 _public function_ `bool TypeIsSet() const`
- L89 _public function_ `bool IsGraphicElement() const`
- L94 _public member_ `ESVGElementType Type = ESVGElementType::None;`
- L96 _public member_ `bool bIsGraphicElement = false;`
- L98 _public member_ `FString Name;`

#### struct `FSVGMainElement`  
`struct FSVGMainElement : FSVGBaseElement`  
_L101-107_
- inherits: `FSVGBaseElement`
- L103 _public function_ `FSVGMainElement()`

#### struct `FSVGStyleElement`  
`struct FSVGStyleElement : FSVGBaseElement`  
_L109-143_
- inherits: `FSVGBaseElement`
- L111 _public function_ `FSVGStyleElement(const TArray<FSVGStyle>& InStyles) : Styles(InStyles)`
- L117 _public member_ `TArray<FSVGStyle> Styles;`
- L119 _public function_ `bool GetStyleByClassName(const FString& InClassName, FSVGStyle& OutStyle)`
- L133 _public function_ `bool GetDefaultStyle(FSVGStyle& OutStyle)`

#### struct `FSVGClipPath`  
`struct FSVGClipPath : FSVGBaseElement`  
_L145-151_
- inherits: `FSVGBaseElement`
- L147 _public function_ `FSVGClipPath()`

#### struct `FSVGGradientElement`  
`struct FSVGGradientElement : FSVGBaseElement`  
_L153-172_
- inherits: `FSVGBaseElement`
- L155 _public function_ `FSVGGradientElement(const FSVGGradient& InGradient) : Gradient(InGradient)`
- L161 _public function_ `bool HasID() const`
- L166 _public function_ `const FString& GetID() const`
- L171 _public member_ `FSVGGradient Gradient;`

#### struct `FSVGGraphicsElement`  
`struct FSVGGraphicsElement : FSVGBaseElement`  
_L178-334_
- inherits: `FSVGBaseElement`
- desc: Base for all elements which can be drawn. They can have fill and/or stroke information, a style, and a transform.
- L180 _public prototype_ `FSVGGraphicsElement();`
- L183 _public prototype_ `void TryRegisterWithParent(const TSharedPtr<FSVGBaseElement>& InParent);` — If the specified parent is a Group element, add this Graphic Element to its children
- L186 _public function_ `void SetClassName(const FString& InClassName)` — Set the class name (e.g. rect, circle, path)
- L192 _public function_ `void SetStyleClassName(const FString& InStyleClassName)` — Set the style class name (the one specified by CSS styling info)
- L198 _public function_ `void SetStyle(const FSVGStyle& InStyle)` — Set style information
- L204 _public function_ `void SetStrokeColor(const FColor& InColor)` — Set stroke color (used if this graphic element has strokes)
- L210 _public function_ `void SetStrokeColor(const FString& InColorSVGString)` — Set stroke color (used if this graphic element has strokes)
- L216 _public function_ `void SetStrokeWidth(float InWidth)` — Set stroke width (used if this graphic element has strokes)
- L222 _public function_ `void SetFillColor(const FColor& InColor)` — Set fill color (used if this graphic element has strokes)
- L228 _public function_ `void SetFillColor(const FString& InColorSVGString)` — Set fill color (used if this graphic element has strokes)
- L233 _public function_ `void SetFillGradient(const FSVGGradient& InFillGradient)`
- L238 _public function_ `void SetFillGradientID(const FString& InFillGradientID)`
- L243 _public function_ `void SetStrokeGradient(const FSVGGradient& InStrokeGradient)`
- L248 _public function_ `void SetStrokeGradientID(const FString& InStrokeGradientID)`
- L254 _public prototype_ `void SetTransform(const FString& InMatrixSVGString);` — Initialize the transform matrix for this Graphic Element
- L257 _public prototype_ `void SetIsClosed(bool bInIsClosed);` — Mark the path for this element as closed or not
- L260 _public prototype_ `void Hide();` — Set visibility for this element and its hierarchy
- L263 _public function_ `bool IsVisible() const` — Whether this element and its hierarchy should be rendered or not
- L266 _public function_ `bool IsClosed() const` — Is this graphic element path closed?
- L269 _public function_ `bool HasStroke() const` — Should the path of this graphic element be rendered as a stroke?
- L272 _public function_ `bool HasFill() const` — Should the path of this graphic element be rendered as a fill?
- L274 _public function_ `bool HasFillGradientID() const`
- L276 _public function_ `bool HasStrokeGradientID() const`
- L278 _public function_ `const FString& GetFillGradientID() const`
- L280 _public function_ `const FString& GetStrokeGradientID() const`
- L282 _public function_ `const FSVGGradient& GetFillGradient() const`
- L284 _public function_ `const FSVGGradient& GetStrokeGradient() const`
- L287 _public function_ `const FString& GetClassName() const` — Get the class name for this Graphic Element (e.g. rect, circle, path)
- L290 _public function_ `const FString& GetStyleClassName() const` — Get the style class name for this Graphic Element (the one specified by CSS styling info)
- L293 _public function_ `const FColor& GetFillColor() const` — Get the fill color of this element
- L296 _public function_ `const FColor& GetStrokeColor() const` — Get the stroke color of this element
- L299 _public function_ `const FSVGStyle& GetStyle() const` — Get the style of this element
- L302 _public function_ `FSVGMatrix& GetTransform()` — Get the transform to be applied to this element
- L305 _public function_ `const TSharedPtr<FSVGGroupElement>& GetParentGroup() const` — Returns the parent group element, if any. Nullptr if none.
- L308 _protected member_ `TSharedPtr<FSVGGroupElement> ParentGroup = nullptr;`
- L311 _protected member_ `FString ClassName;` — The class name of this graphic element (e.g. rect, circle, path)
- L314 _protected member_ `FString StyleClassName;` — The Style Class name of this element (for CSS styling)
- L317 _protected member_ `FSVGStyle Style;` — The style of this element
- L320 _protected member_ `FSVGGradient FillGradient;` — Fill gradient, if available
- L323 _protected member_ `FSVGGradient StrokeGradient;` — Stroke gradient, if available
- L326 _protected member_ `FSVGMatrix Transform;` — The transform of this element
- L329 _protected member_ `bool bIsClosed = false;` — Is this element path closed?
- L331 _protected member_ `FString FillGradientID;`
- L333 _protected member_ `FString StrokeGradientID;`

#### struct `FSVGGroupElement`  
`struct FSVGGroupElement : FSVGGraphicsElement`  
_L341-359_
- inherits: `FSVGGraphicsElement`
- desc: Container struct representing SVG "group". It holds a list of graphics elements. It is defined as a graphic element itself, since it can contain info about elements styling.
- L343 _public member_ `TArray<TSharedRef<FSVGGraphicsElement>> Children;`
- L345 _public function_ `FSVGGroupElement()`
- L350 _public function_ `void Setup(const TArray<TSharedRef<FSVGGraphicsElement>>& InChildren)`
- L355 _public function_ `void AddChild(const TSharedRef<FSVGGraphicsElement>& InChild)`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGEngineSubsystem.h` (Public)


#### class `USVGEngineSubsystem`  
`class USVGEngineSubsystem : public UEngineSubsystem`  
_L16-33_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- L21 _public prototype_ `static USVGEngineSubsystem* Get();`
- L23 _public function_ `FSVGActorComponentsReady& GetSVGActorComponentsReadyDelegate()`
- L25 _public function_ `static FOnSVGActorSplit& OnSVGActorSplit()`
- L26 _public function_ `static FOnSVGShapesUpdated& OnSVGShapesUpdated()`
- L29 _protected member_ `static FOnSVGActorSplit OnSVGActorSplitDelegate;`
- L30 _protected member_ `static FOnSVGShapesUpdated OnSVGShapesUpdatedDelegate;`
- L32 _protected member_ `FSVGActorComponentsReady SVGActorComponentsReady;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FSVGActorComponentsReady, ASVGActor*) DECLARE_DELEGATE_OneParam(FOnSVGActorSplit, ASVGShapesParentActor*) DECLARE_DELEGATE_OneParam(FOnSVGShapesUpdated, AActor*) UCLASS() class USVGEngineSubsystem : public UEngineSubsystem { GENERATED_BODY() public: static USVGEngineSubsystem* Get(); FSVGActorComponentsReady& GetSVGActorComponentsReadyDelegate() { return SVGActorComponentsReady; } static FOnSVGActorSplit& OnSVGActorSplit() { return OnSVGActorSplitDelegate; } static FOnSVGShapesUpdated& OnSVGShapesUpdated() { return OnSVGShapesUpdatedDelegate; } protected: static FOnSVGActorSplit OnSVGActorSplitDelegate; static FOnSVGShapesUpdated OnSVGShapesUpdatedDelegate; FSVGActorComponentsReady SVGActorComponentsReady; };`
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSVGActorSplit, ASVGShapesParentActor*) DECLARE_DELEGATE_OneParam(FOnSVGShapesUpdated, AActor*) UCLASS() class USVGEngineSubsystem : public UEngineSubsystem { GENERATED_BODY() public: static USVGEngineSubsystem* Get(); FSVGActorComponentsReady& GetSVGActorComponentsReadyDelegate() { return SVGActorComponentsReady; } static FOnSVGActorSplit& OnSVGActorSplit() { return OnSVGActorSplitDelegate; } static FOnSVGShapesUpdated& OnSVGShapesUpdated() { return OnSVGShapesUpdatedDelegate; } protected: static FOnSVGActorSplit OnSVGActorSplitDelegate; static FOnSVGShapesUpdated OnSVGShapesUpdatedDelegate; FSVGActorComponentsReady SVGActorComponentsReady; };`
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSVGShapesUpdated, AActor*) UCLASS() class USVGEngineSubsystem : public UEngineSubsystem { GENERATED_BODY() public: static USVGEngineSubsystem* Get(); FSVGActorComponentsReady& GetSVGActorComponentsReadyDelegate() { return SVGActorComponentsReady; } static FOnSVGActorSplit& OnSVGActorSplit() { return OnSVGActorSplitDelegate; } static FOnSVGShapesUpdated& OnSVGShapesUpdated() { return OnSVGShapesUpdatedDelegate; } protected: static FOnSVGActorSplit OnSVGActorSplitDelegate; static FOnSVGShapesUpdated OnSVGShapesUpdatedDelegate; FSVGActorComponentsReady SVGActorComponentsReady; };`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGGraphicalElements.h` (Public)


#### struct `FSVGLine`  
`struct FSVGLine : FSVGPath`  
_L12-20_
- inherits: `FSVGPath`
- L14 _public prototype_ `FSVGLine(float InPathLength, float InX1, float InY1, float InX2, float InY2);`
- L16 _public member_ `float X1 = 0.0f;`
- L17 _public member_ `float Y1 = 0.0f;`
- L18 _public member_ `float X2 = 0.0f;`
- L19 _public member_ `float Y2 = 0.0f;`

#### struct `FSVGPolyLine`  
`struct FSVGPolyLine : FSVGPath`  
_L22-27_
- inherits: `FSVGPath`
- L24 _public prototype_ `FSVGPolyLine(float InPathLength, const TArray<FVector2D>& InPoints);`
- L26 _public member_ `TArray<FVector2D> Points;`

#### struct `FSVGPolygon`  
`struct FSVGPolygon : FSVGPolyLine`  
_L29-32_
- inherits: `FSVGPolyLine`
- L31 _public prototype_ `FSVGPolygon(float InPathLength, const TArray<FVector2D>& InPoints);`

#### struct `FSVGRectangle`  
`struct FSVGRectangle : FSVGPath`  
_L34-44_
- inherits: `FSVGPath`
- L36 _public prototype_ `FSVGRectangle(float InX, float InY, float InWidth, float InHeight, float InRx, float InRy);`
- L38 _public member_ `float X;`
- L39 _public member_ `float Y;`
- L40 _public member_ `float Width;`
- L41 _public member_ `float Height;`
- L42 _public member_ `float Rx;`
- L43 _public member_ `float Ry;`

#### struct `FSVGCircle`  
`struct FSVGCircle : FSVGPath`  
_L46-53_
- inherits: `FSVGPath`
- L48 _public prototype_ `FSVGCircle(float InCx, float InCy, float InR);`
- L50 _public member_ `float Cx;`
- L51 _public member_ `float Cy;`
- L52 _public member_ `float R;`

#### struct `FSVGEllipse`  
`struct FSVGEllipse : FSVGPath`  
_L55-63_
- inherits: `FSVGPath`
- L57 _public prototype_ `FSVGEllipse(float InCx, float InCy, float InRx, float InRy);`
- L59 _public member_ `float Cx;`
- L60 _public member_ `float Cy;`
- L61 _public member_ `float Rx;`
- L62 _public member_ `float Ry;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGImporter.h` (Public)


#### class `FSVGImporterModule`  
`class FSVGImporterModule : public IModuleInterface`  
_L17-33_
- inherits: `IModuleInterface`
- L23 _public function_ `static FSVGImporterModule& Get()`
- L28 _public prototype_ `USVGData* CreateDefaultSVGData() const;`
- L31 _protected prototype_ `DECLARE_DELEGATE_RetVal(USVGData*, FOnDefaultSVGDataRequested) FOnDefaultSVGDataRequested OnDefaultSVGDataRequested;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSVGImporter, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSVGImporter, Log, All);`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal(USVGData*, FOnDefaultSVGDataRequested) FOnDefaultSVGDataRequested OnDefaultSVGDataRequested;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGImporterUtils.h` (Public)


#### class `FSVGImporterUtils`  
`class FSVGImporterUtils`  
_L33-160_
- L36 _public member_ `inline static double SVGScaleFactor = 0.1;`
- L47 _public prototype_ `static bool ConvertSVGSplineToPolyLine(const USplineComponent* InSplineComponent, ESplineCoordinateSpace::Type InCoordinateSpace , float InMaxSquareDistanceFromSpline, TArray<FVector>& OutPoints);` — Given a threshold, returns a list of vertices along the specified spline that, treated as a list of segments (polyline), matches the spline shape. This function is a reviewed implementation of USplineComponent::ConvertSplineToPolyLine. @param InSplineComponent The spline to be fitted @param InCoordinateSpace The coordinate space to be used @param InMaxSquareDistanceFromSpline Fitting threshold @param OutPoints The polyline, as a list of Vectors @return
- L63 _public prototype_ `static bool ShouldPolygonBeDrawn(const FSVGPathPolygon& ShapeToCheck, const TArray<FSVGPathPolygon>& Polygons, bool& bOutIsClockwise);` — Evaluates if the specified ShapeToCheck is to be drawn or not (e.g. actual shape or hole to be cut) The value nonzero determines the "insideness" of a point in the shape by drawing a ray from that point to infinity in any direction, and then examining the places where a segment of the shape crosses the ray. Starting with a count of zero, add one each time a path segment crosses the ray from left to right and subtract one each time a path segment crosses the ray from right to left. After counting the crossings, if the result is zero then the point is outside the path. Otherwise, it is inside. See: https://developer.mozilla.org/en-US/docs/Web/Attribute/fill-rule For now, this function is only considering the non-zero fill rule. todo: might need support for even odd fill rule.
- L66 _public prototype_ `static void RotateAroundCustomPivot(FVector& OutPointToRotate, const FVector& InPivotPosition, float InAngle);` — Rotates an input point around a custom pivot
- L69 _public prototype_ `static FColor GetColorFromSVGString(FString InColorString);` — Extracts a color from SVG color string
- L72 _public prototype_ `static TArray<FSVGStyle> StylesFromCSS(FString InString);` — Extracts SVG Style from a CSS style string
- L75 _public prototype_ `static bool SetSVGMatrixFromTransformString(const FString& InTransformString, FSVGMatrix& OutSVGMatrix);` — Sets an SVG Matrix based on the specified SVG Transform string
- L83 _public prototype_ `static FLinearColor GetAverageColor(const TArray<FLinearColor>& InColors);` — Computes a simple average of the provided Linear Colors @param InColors the colors to average @return the average color
- L93 _private prototype_ `static bool FindIntersectingSegments(const UE::Geometry::TSegment2<double>& InRay, const UE::Geometry::TPolygon2<double>& InOtherPoly , TArray<UE::Geometry::TSegment2<double>>& OutArray);` — Finds the polygon segments intersecting the specified ray @param InRay The ray @param InOtherPoly The polygon to check against @param OutArray The list of intersecting segments @return true if at least one segment is found
- L99 _public prototype_ `static UTexture2D* CreateSVGTexture(const FString& InSVGString, UObject* InOuter);` — Creates a Texture 2D from the specified SVG Text Buffer. Uses the nanosvg parser and rasterizer
- L109 _public prototype_ `static void BakeSVGActorToBlueprint(const ASVGActor* InSVGActorToBake, const FString& InAssetPath);` — Create Blueprint from SVG Actor. Will also create the required Static Meshes, Materials and Material Instances assets. The Dynamic meshes of the SVG Actor will be converted to Static Meshes, and their materials to Materials. Material Instances will be used when possible, to reduce the number of created Materials. @param InSVGActorToBake the Actor to be used as a template for the Blueprint @param InAssetPath The path where the Blueprint and required assets will be created
- L117 _public prototype_ `static UStaticMesh* BakeSVGDynamicMeshToStaticMesh(USVGDynamicMeshComponent* InSVGDynamicMeshToBake, const FString& InAssetPath, TMap<FString, UMaterialInstance*>& OutGeneratedMaterialInstances);` — Creates a Static Mesh Asset starting from the specified SVG Dynamic Mesh Component @param InSVGDynamicMeshToBake the source SVG Dynamic Mesh @param InAssetPath The path where the Asset will be created @param OutGeneratedMaterialInstances if possible, the function will generate material instances instead of multiple materials
- L125 _public prototype_ `static ASVGShapesParentActor* SplitSVGActor(ASVGActor* InSVGActor);` — Splits the specified SVG Actor into multiple actors. Each actor will have a single SVG Shape component @param InSVGActor the source SVG Actor to split @return the newly created Shapes Parent Actor
- L133 _public prototype_ `static ASVGJoinedShapesActor* ConsolidateSVGActor(ASVGActor* InSVGActor);` — Merges all SVG Shapes of this Actor into a single Actor with a single Shape. @param InSVGActor the source SVG Actor to consolidate @return the newly created Joined Shapes Actor
- L141 _public prototype_ `static ASVGJoinedShapesActor* JoinSVGDynamicMeshOwners(const TArray<ASVGDynamicMeshesContainerActor*>& InDynamicSVGShapesOwners);` — Joins the SVG Shapes of 2 or more Actors of type ASVGDynamicMeshesOwnerActor onto a single ASVGJoinedShapesActor @param InDynamicSVGShapesOwners the list of Actors owning the SVG Shapes which are going to be joined @return the newly created Joined Shapes Actor
- L145 _private prototype_ `static bool GetAvailableFolderPath(const FString& InAssetPath, FString& OutAssetPath);` — Based on the specified Asset Path, will return an available Folder Path where we can create assets for SVG Baking purposes
- L148 _private prototype_ `static ASVGJoinedShapesActor* CreateSVGJoinedActor(UObject* InOuter, const TArray<UDynamicMeshComponent*>& InShapesToJoin, const FTransform& InTransform, const FName& InBaseName);` — Creates a new SVG Joined Actor from the provided Dynamic Meshes Shapes.
- L158 _private prototype_ `static ASVGShapeActor* CreateSVGShapeActorFromShape(const ASVGActor* InSourceSVGActor, const USVGDynamicMeshComponent* InSVGShapeComponent, AActor* InShapesParentActor);` — Creates an SVG Shape Actor for the specified component @param InSourceSVGActor the source SVG Actor @param InSVGShapeComponent the Shape Component to be moved to the newly created actor @param InShapesParentActor the created actor will be attached to this parent actor @return the newly created actor

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace ESplineCoordinateSpace`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGPath.h` (Public)


#### enum `ESVGPathInstructionType`  
`enum class ESVGPathInstructionType : uint8`  
_L12-25_
- desc: The available commands describing a path
- L14 _public enumerator_ `None`
- L15 _public enumerator_ `MoveTo`
- L16 _public enumerator_ `ClosePath`
- L17 _public enumerator_ `LineTo`
- L18 _public enumerator_ `HorizontalLineTo`
- L19 _public enumerator_ `VerticalLineTo`
- L20 _public enumerator_ `CurveTo`
- L21 _public enumerator_ `SmoothCurveTo`
- L22 _public enumerator_ `QuadraticCurveTo`
- L23 _public enumerator_ `SmoothQuadraticCurveTo`
- L24 _public enumerator_ `EllipticalArc`

#### struct `FSVGPathCommand`  
`struct FSVGPathCommand`  
_L30-50_
- desc: Defines a single SVG Path Command
- L32 _public prototype_ `FSVGPathCommand() = default;`
- L34 _public function_ `FSVGPathCommand(ESVGPathInstructionType InInstructionType) : InstructionType(InInstructionType)`
- L40 _public member_ `ESVGPathInstructionType InstructionType = ESVGPathInstructionType::None;` — The instruction type of this command (e.g. Move To, Line To, Cubic Bezier To, etc)
- L43 _public member_ `FVector2D PointTo = FVector2D::UnitVector;` — Command destination point
- L46 _public member_ `FVector2D ArriveControlPoint = FVector2D::ZeroVector;` — Arrive control point
- L49 _public member_ `FVector2D LeaveControlPoint = FVector2D::UnitVector;` — Leave Control point

#### struct `FSVGPathElement`  
`struct FSVGPathElement`  
_L55-88_
- desc: The Element of an SVG Path
- L62 _public prototype_ `FSplinePoint AsSplinePoint(float InputKey) const;` — Returns this Path Element as a Spline Point @param InputKey the Key/Index the returned spline will be associated with
- L65 _public function_ `bool IsSubpathInitialPoint() const` — Is this element a subpath initial point?
- L67 _public prototype_ `FSVGPathElement() = default;`
- L69 _public function_ `FSVGPathElement(const FVector2D& Point, const FVector2D& InArriveControlPoint = FVector2D::ZeroVector , const FVector2D& InLeaveControlPoint = FVector2D::ZeroVector) : Point(Point) , ArriveControlPoint(InArriveControlPoint) , LeaveControlPoint(InLeaveControlPoint)`
- L78 _public member_ `FVector2D Point = FVector2D::ZeroVector;` — Point location
- L81 _public member_ `FVector2D ArriveControlPoint = FVector2D::ZeroVector;` — Arrive control point
- L84 _public member_ `FVector2D LeaveControlPoint = FVector2D::ZeroVector;` — Leave control point
- L87 _public member_ `bool bIsSubpathInitialPoint = false;` — Is this Element the first point of a sub path?

#### struct `FSVGSubPath`  
`struct FSVGSubPath`  
_L93-112_
- desc: SVG Subpath
- L96 _public function_ `void SetIsClosed(bool bInIsClosed)` — Set the path closed flag
- L102 _public function_ `void AddPathElement(const FSVGPathElement& InElement)` — Add an element to this path
- L108 _public member_ `TArray<FSVGPathElement> Elements;` — Elements of this Sub Path
- L111 _public member_ `bool bIsClosed = false;` — True if path is closed

#### struct `FSVGPath`  
`struct FSVGPath : public FSVGGraphicsElement`  
_L117-201_
- inherits: `FSVGGraphicsElement`
- desc: SVG Path. It can describe a path with multiple subpaths and a length
- L120 _public prototype_ `FSVGPath();`
- L122 _public prototype_ `FSVGPath(float InPathLength);`
- L124 _public prototype_ `FSVGPath(const TArray<TArray<FSVGPathCommand>>& InPaths, float InPathLength);`
- L127 _public prototype_ `bool UpdatePreviousElementLeaveTangent(const FVector2D& InLeaveTangent);` — Set the leave tangent of the previous point
- L130 _public prototype_ `void AddSubPath(const TArray<FSVGPathCommand>& Commands);` — Add a subpath to this path
- L141 _public prototype_ `void AddPoint(float InX, float InY, float InCx, float InCy, float OutCx, float OutCy);` — Add a point to this path @param InX Point X @param InY Point Y @param InCx In Control Point X @param InCy In Control Point Y @param OutCx Out Control Point X @param OutCy Out Control Point Y
- L147 _public prototype_ `void AddPoint(const FVector2D& Point);` — Add a point to this path @param Point the location of the point
- L155 _public prototype_ `void AddPoint(const FVector2D& Point, const FVector2D& ArriveControlPoint, const FVector2D& LeaveControlPoint);` — Add a point to this path @param Point the location of the point @param ArriveControlPoint the location of the Arrive Control Point @param LeaveControlPoint the location of the Leave Control Point
- L158 _public prototype_ `void MoveTo(const FVector2D& InCursorPos);` — Move To operation (see svg specifications)
- L161 _public prototype_ `void MoveTo(float InX, float InY);` — Move To operation (see svg specifications)
- L164 _public prototype_ `void PathMoveTo(const FVector2D& InPointTo);` — Path Move To operation (see svg specifications)
- L167 _public prototype_ `void PathMoveTo(float InX, float InY);` — Path Move To operation (see svg specifications)
- L170 _public prototype_ `void LineTo(const FVector2D& PointTo);` — Line To operation (see svg specifications)
- L173 _public prototype_ `void LineTo(float InX, float InY);` — Line To operation (see svg specifications)
- L176 _public prototype_ `void PathLineTo(float InX, float InY);` — Path Line To operation (see svg specifications)
- L179 _public prototype_ `void PathLineTo(const FVector2D& InPointTo);` — Path Line To operation (see svg specifications)
- L182 _public prototype_ `void CubicBezierTo(float InX, float InY, float InCx, float InCy, float OutCx, float OutCy);` — Cubic Bezier To operation (see svg specifications)
- L185 _public prototype_ `void PathCubicBezierTo(float InX, float InY, float InCx, float InCy, float OutCx, float OutCy);` — Path Cubic Bezier To operation (see svg specifications)
- L188 _public prototype_ `void PathCubicBezierTo(const FVector2D& InPointTo, const FVector2D& InArriveControlPoint, const FVector2D& InLeaveControlPoint);` — Path Cubic Bezier To operation (see svg specifications)
- L191 _public member_ `float PathLength = 0.0f;` — Length of this path
- L194 _public member_ `TArray<FSVGSubPath> SubPaths;` — The SubPaths composing this Path
- L197 _public member_ `FSVGPathElement PathCursor;` — Current position of the Path Cursor
- L200 _public member_ `FSVGPathElement InitialPoint;` — Starting Path point

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGShapesParentActor.h` (Public)


#### class `ASVGShapesParentActor`  
`class ASVGShapesParentActor : public ASVGDynamicMeshesContainerActor`  
_L15-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ASVGDynamicMeshesContainerActor`
- desc: This actor is used as a parent to organize SVG Shape Actors
- L21 _public prototype_ `void GetShapes(TMap<TObjectPtr<AActor>, TObjectPtr<USVGDynamicMeshComponent>>& OutMap) const;` — Returns a map associating each dynamic mesh component shape to the actor they are attached to
- L23 _public prototype_ `void DestroyAttachedActorMeshes();`
- L26 _public prototype_ `virtual TArray<UDynamicMeshComponent*> GetSVGDynamicMeshes() override;`

### `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Public/SVGTypes.h` (Public)


#### struct `FSVGStyle`  
`struct FSVGStyle`  
_L18-77_
- reflection: `USTRUCT()`
- L22 _public prototype_ `void FillFromAttributesMap(const TMap<FString, FString>& StyleAttributes);`
- L24 _public prototype_ `void SetName(const FString& InName);`
- L26 _public prototype_ `void SetStrokeColor(const FColor& InColor);`
- L28 _public prototype_ `void SetStrokeColor(const FString& InColorSVGString);`
- L30 _public prototype_ `void SetStrokeWidth(float InWidth);`
- L32 _public prototype_ `void SetFillColor(const FColor& InColor);`
- L34 _public prototype_ `void SetFillColor(const FString& InColorSVGString);`
- L36 _public prototype_ `void SetDisplay(const FString& InDisplay);`
- L38 _public prototype_ `void Hide();`
- L40 _public function_ `bool HasStroke() const`
- L42 _public function_ `bool HasFill() const`
- L44 _public function_ `const FColor& GetFillColor() const`
- L46 _public function_ `const FColor& GetStrokeColor() const`
- L48 _public prototype_ `bool IsVisible() const;`
- L50 _public prototype_ `bool DisplayIsSet() const;`
- L52 _public function_ `const FString& GetName() const`
- L54 _public function_ `float GetStrokeWidth() const`
- L58 _private member_ `FString Name;` — `UPROPERTY()`
- L61 _private member_ `bool bHasFill = false;` — `UPROPERTY()`
- L64 _private member_ `FColor FillColor = FColor::Black;` — `UPROPERTY()`
- L67 _private member_ `bool bHasStroke = false;` — `UPROPERTY()`
- L70 _private member_ `FColor StrokeColor = FColor::Black;` — `UPROPERTY()`
- L73 _private member_ `float StrokeWidth = 1.0f;` — `UPROPERTY()`
- L76 _private member_ `FString Display;` — `UPROPERTY()`

#### enum `ESVGGradientPointUnit`  
`enum class ESVGGradientPointUnit : uint8`  
_L79-83_
- L81 _public enumerator_ `UserSpaceOnUse`
- L82 _public enumerator_ `ObjectBoundingBox`

#### struct `FSVGGradientStop`  
`struct FSVGGradientStop`  
_L86-98_
- reflection: `USTRUCT()`
- L91 _public member_ `float Offset = 0.0f;` — `UPROPERTY()`
- L94 _public member_ `float StopOpacity = 0.0f;` — `UPROPERTY()`
- L97 _public member_ `FColor StopColor = FColor::Black;` — `UPROPERTY()`

#### struct `FSVGGradient`  
`struct FSVGGradient`  
_L101-142_
- reflection: `USTRUCT()`
- L105 _public function_ `FSVGGradient()`
- L108 _public function_ `FSVGGradient(const FString& Id, ESVGGradientPointUnit InGradientUnits, const FVector2D& StartingPoint , const FVector2D& EndingPoint, const TArray<FSVGGradientStop>& StopNodes = {}) : Id(Id) , GradientUnits(InGradientUnits) , StartingPoint(StartingPoint) , EndingPoint(EndingPoint) , StopNodes(StopNodes)`
- L118 _public function_ `bool IsValid() const`
- L121 _public member_ `FString Id;` — `UPROPERTY()`
- L124 _public member_ `ESVGGradientPointUnit GradientUnits = ESVGGradientPointUnit::ObjectBoundingBox;` — Tells whether this gradient is using coordinates or percentage values for start and end point of the gradient
- L127 _public member_ `FVector2D StartingPoint = FVector2D::ZeroVector;` — This can be either coordinates of percentage values, see GradientUnits value for that
- L130 _public member_ `FVector2D EndingPoint = FVector2D::UnitVector * 100.0f;` — This can be either coordinates of percentage values, see GradientUnits value for that
- L133 _public member_ `TArray<FSVGGradientStop> StopNodes;` — `UPROPERTY()`
- L141 _public prototype_ `FColor GetAverageColor() const;`

#### struct `FSVGPathPolygon`  
`struct FSVGPathPolygon`  
_L145-190_
- reflection: `USTRUCT(Blueprintable)`
- L149 _public function_ `FSVGPathPolygon()`
- L154 _public function_ `FSVGPathPolygon(const TArray<FVector>& InVertices)`
- L160 _public function_ `const TArray<FVector>& GetVertices() const`
- L162 _public function_ `const TArray<FVector2D>& Get2DVertices() const`
- L164 _public function_ `int GetNumVertices() const`
- L166 _public function_ `bool GetShouldBeDrawn() const`
- L168 _public function_ `const UE::Geometry::TPolygon2<double>& GetPolygon() const`
- L170 _public function_ `bool ShouldBeDrawn() const`
- L172 _public prototype_ `void SetVertices(const TArray<FVector>& InVertices);`
- L174 _public function_ `void SetShouldBeDrawn(bool bInShouldBeDrawn)`
- L180 _private member_ `UE::Geometry::TPolygon2<double> Polygon;`
- L183 _private member_ `TArray<FVector2D> Vertices2D;` — `UPROPERTY()`
- L186 _private member_ `TArray<FVector> Vertices;` — `UPROPERTY()`
- L189 _private member_ `bool bShouldBeDrawn;` — `UPROPERTY()`

#### struct `FSVGShape`  
`struct FSVGShape`  
_L193-304_
- reflection: `USTRUCT()`
- L197 _public function_ `FSVGShape()`
- L202 _public function_ `FSVGShape(const FSVGStyle& InStyle, bool bInIsClosed , const FSVGGradient& InFillGradient = FSVGGradient() , const FSVGGradient& InStrokeGradient = FSVGGradient())`
- L213 _public function_ `bool IsVisible() const`
- L215 _public function_ `void SetDefaultValues()`
- L221 _public function_ `void SetId(const FString& InId)`
- L226 _public function_ `void SetIsClosed(bool bInIsClosed)`
- L231 _public function_ `FColor GetStrokeColor() const`
- L243 _public function_ `FColor GetFillColor() const`
- L255 _public function_ `bool HasStroke() const`
- L257 _public function_ `bool HasFill() const`
- L259 _public function_ `bool IsClosed() const`
- L261 _public function_ `int32 PolygonsNum() const`
- L263 _public function_ `bool IsClockwise() const`
- L265 _public function_ `const FString& GetId() const`
- L267 _public function_ `const TArray<FSVGPathPolygon>& GetPolygons() const`
- L269 _public function_ `const FSVGStyle& GetStyle() const`
- L271 _public function_ `void SetStyle(const FSVGStyle& InStyle)`
- L276 _public prototype_ `void AddPolygon(const TArray<FVector>& InPoints);`
- L278 _public prototype_ `void ApplyFillRule();`
- L282 _private member_ `FString Id;` — `UPROPERTY()`
- L285 _private member_ `TArray<FSVGPathPolygon> Polygons;` — `UPROPERTY()`
- L288 _private member_ `TArray<TObjectPtr<USplineComponent>> PolygonSplines;` — `UPROPERTY()`
- L291 _private member_ `FSVGStyle Style;` — `UPROPERTY()`
- L294 _private member_ `FSVGGradient FillGradient;` — `UPROPERTY()`
- L297 _private member_ `FSVGGradient StrokeGradient;` — `UPROPERTY()`
- L299 _private member_ `bool bIsClosed;`
- L301 _private member_ `bool bIsClockwise;`
- L303 _private member_ `bool bShapesHaveBeenGenerated;`
