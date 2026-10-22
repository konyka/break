# Plugins / MeshModelingToolsEditorOnlyExp

- module root: `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp`
- headers: 18; symbols: 1139
- symbol kinds: class=71, delegate=1, enum=19, enumerator=59, function=80, macro=16, member=477, namespace=7, prototype=391, struct=16, typedef=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, BSPUtils, CoreUObject, Engine, InputCore, Json, Persona, RenderCore, SceneOutliner, Slate, UnrealEd
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryCore, GeometryFramework, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshModelingTools, MeshModelingToolsEditorOnly, MeshModelingToolsExp, ModelingComponents, ModelingComponentsEditorOnly, ModelingOperators, ModelingOperatorsEditorOnly, SkeletalMeshDescription, StaticMeshDescription

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Private/MeshVertexAttributePaintBrushOps.h` (Private)


#### class `FMeshVertexAttributePaintToolBrushOpBase`  
`class FMeshVertexAttributePaintToolBrushOpBase : public FMeshSculptBrushOp`  
_L12-41_
- inherits: `FMeshSculptBrushOp`
- L17 _public typedef_ `using FalloffFunction = TFunction<float(const FVector&)>;` — falloff as a function of position
- L20 _public function_ `virtual void ApplyStamp( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewColorsOut) override` — not supported for this kind of brush op
- L30 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TFunctionRef<double(int32)> GetVertexWeightFunc, TArray<double>& InOutROIBuffer) = 0;`
- L38 _public member_ `bool bApplyRadiusLimit = true;` — If bApplyRadiusLimit is enabled, only vertices within the stamp radius are considered
- L40 _public prototype_ `virtual bool IgnoreZeroMovements() const override;`

#### class `UMeshVertexAttributePaintToolEraseBrushOpProps`  
`class UMeshVertexAttributePaintToolEraseBrushOpProps : public UMeshSculptBrushOpProps`  
_L50-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L57 _public member_ `double AttributeValue = 0;` — `UPROPERTY(EditAnywhere, Category = EraseBrush, meta = (DisplayName = "Erase Attribute", UIMin = 0))` — Attribute to set as Erased value
- L59 _public function_ `virtual double GetAttribute()`
- L61 _public function_ `virtual float GetFalloff() override`

#### class `FMeshVertexAttributePaintToolEraseBrushOp`  
`class FMeshVertexAttributePaintToolEraseBrushOp : public FMeshVertexAttributePaintToolBrushOpBase`  
_L66-77_
- inherits: `FMeshVertexAttributePaintToolBrushOpBase`
- L70 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TFunctionRef<double(int32)> GetVertexWeightFunc, TArray<double>& InOutROIBuffer) override;`

#### class `UMeshVertexAttributePaintToolSmoothBrushOpProps`  
`class UMeshVertexAttributePaintToolSmoothBrushOpProps : public UMeshSculptBrushOpProps`  
_L87-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L94 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10."))`
- L98 _public member_ `float Falloff = 0.0f;` — `UPROPERTY()`
- L100 _public function_ `virtual float GetStrength() override`
- L101 _public function_ `virtual void SetStrength(float NewStrength) override`
- L103 _public function_ `virtual float GetFalloff() override`

#### class `FMeshVertexAttributePaintToolSmoothBrushOp`  
`class FMeshVertexAttributePaintToolSmoothBrushOp : public FMeshVertexAttributePaintToolBrushOpBase`  
_L107-142_
- inherits: `FMeshVertexAttributePaintToolBrushOpBase`
- L112 _public member_ `TFunction<const TArray<double>&()> GetSmoothEdgeWeights;` — Edge weights to use during smoothing, optional
- L114 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TFunctionRef<double(int32)> GetVertexWeightFunc, TArray<double>& InOutROIBuffer) override;`
- L121 _public prototype_ `static void ApplyStampByVerticesStatic( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TFunctionRef<double(int32)> GetVertexWeightFunc, const TArray<double>& SmoothEdgeWeights, TArray<double>& InOutROIBuffer, bool bApplyRadiusLimit, TSharedPtr<FMeshSculptFallofFunc> FalloffFunc = {});`
- L131 _public prototype_ `static void ApplyToVerticesStatic( const FDynamicMesh3* Mesh, const TArray<int32>& Vertices, TFunctionRef<double(int32)> GetVertexWeightFunc, const TArray<double>& SmoothEdgeWeights, TArray<double>& InOutROIBuffer, const double SmoothingFactor, bool bApplyRadiusLimit, const FVector Center, const float Radius, FalloffFunction FalloffFunc = {});`

#### class `UMeshVertexAttributePaintToolPaintBrushOpProps`  
`class UMeshVertexAttributePaintToolPaintBrushOpProps : public UMeshSculptBrushOpProps`  
_L148-171_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- desc: this brush leverage EMeshVertexAttributePaintToolEditOperation to decide how to paint the vertex attribute
- L155 _public member_ `double AttributeValue = 1;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Value", UIMin = 0))` — The Attribute that will be assigned to triangles within the brush region
- L158 _public member_ `float Strength = 1.0;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10."))`
- L161 _public member_ `float Falloff = 0;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (UIMin = "0.0", UIMax = "1.", ClampMin = "0.0", ClampMax = "1."))`
- L163 _public function_ `virtual double GetAttribute()`
- L164 _public function_ `virtual float GetStrength() override`
- L165 _public function_ `virtual void SetStrength(float NewStrength) override`
- L167 _public function_ `virtual void SetFalloff(float NewFalloff)`
- L168 _public function_ `virtual float GetFalloff() override`
- L170 _public member_ `EMeshVertexAttributePaintToolEditOperation EditOperation = EMeshVertexAttributePaintToolEditOperation::Add;`

#### class `FMeshVertexAttributePaintToolPaintBrushOp`  
`class FMeshVertexAttributePaintToolPaintBrushOp : public FMeshVertexAttributePaintToolBrushOpBase`  
_L173-206_
- inherits: `FMeshVertexAttributePaintToolBrushOpBase`
- L177 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TFunctionRef<double(int32)> GetVertexWeightFunc, TArray<double>& InOutROIBuffer) override;`
- L184 _public prototype_ `static void ApplyStampByVerticesStatic( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TFunctionRef<double(int32)> GetVertexWeightFunc, TArray<double>& InOutROIBuffer, EMeshVertexAttributePaintToolEditOperation EditOperation, const double ToolValue, bool bApplyRadiusLimit, TSharedPtr<FMeshSculptFallofFunc> FalloffFunc = {});`
- L195 _public prototype_ `static void ApplyToVerticesStatic( const FDynamicMesh3* Mesh, const TArray<int32>& Vertices, TFunctionRef<double(int32)> GetVertexWeightFunc, TArray<double>& InOutROIBuffer, EMeshVertexAttributePaintToolEditOperation EditOperation, const double ToolValue, bool bApplyRadiusLimit, const FVector Center, const float Radius, FalloffFunction FalloffFunc = {});`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/AddPivotActorTool.h` (Public)


#### class `UPivotActorTransformProperties`  
`class UPivotActorTransformProperties : public UInteractiveToolPropertySet`  
_L22-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L29 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = PivotLocation)`
- L32 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = PivotLocation)`

#### class `UAddPivotActorToolBuilder`  
`class UAddPivotActorToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L37-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L41 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L42 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L44 _public prototype_ `void InitializeNewTool(UMultiSelectionMeshEditingTool* NewTool, const FToolBuilderState& SceneState) const override;`
- L47 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UAddPivotActorTool`  
`class UAddPivotActorTool : public UMultiSelectionMeshEditingTool`  
_L56-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool`
- desc: Given selected actors, creates an empty actor as the parent of those actors, at a location specified using the gizmo. This is useful for creating a permanent alternate pivot to use in animation.
- L61 _public function_ `virtual void SetPivotRepositionMode(AActor* PivotActor)`
- L63 _public prototype_ `virtual void Setup() override;`
- L64 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L66 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L68 _public function_ `virtual bool HasAccept() const override`
- L69 _public function_ `virtual bool HasCancel() const override`
- L71 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L78 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L81 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`
- L84 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L87 _protected member_ `TObjectPtr<UPivotActorTransformProperties> TransformProperties;` — `UPROPERTY()`
- L89 _protected member_ `TWeakObjectPtr<AActor> ExistingPivotActor = nullptr;`
- L91 _protected member_ `TValueWatcher<FVector> GizmoPositionWatcher;`
- L92 _protected member_ `TValueWatcher<FQuat> GizmoRotationWatcher;`
- L94 _protected prototype_ `void UpdateGizmoFromProperties();`
- L95 _protected prototype_ `void GizmoTransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L97 _protected member_ `FTransform ExistingPivotOriginalTransform;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/BakeRenderCaptureTool.h` (Public)


#### class `UBakeRenderCaptureResults`  
`class UBakeRenderCaptureResults : public UInteractiveToolPropertySet`  
_L39-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L45 _public member_ `TObjectPtr<UTexture2D> BaseColorMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty))`
- L49 _public member_ `TObjectPtr<UTexture2D> NormalMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty))` — World space normal map
- L53 _public member_ `TObjectPtr<UTexture2D> PackedMRSMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty, DisplayName = "Packed MRS Map"))` — Packed Metallic/Roughness/Specular Map
- L56 _public member_ `TObjectPtr<UTexture2D> MetallicMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty))`
- L59 _public member_ `TObjectPtr<UTexture2D> RoughnessMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty))`
- L62 _public member_ `TObjectPtr<UTexture2D> SpecularMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty))`
- L65 _public member_ `TObjectPtr<UTexture2D> EmissiveMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty))`
- L68 _public member_ `TObjectPtr<UTexture2D> OpacityMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty))`
- L71 _public member_ `TObjectPtr<UTexture2D> SubsurfaceColorMap = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (TransientToolProperty))`
- L75 _public member_ `TObjectPtr<UTexture2D> DeviceDepthMap = nullptr;` — `UPROPERTY()` — Device depth is currently unused
- L78 _public prototype_ `const TObjectPtr<UTexture2D>& operator[](UE::Geometry::ERenderCaptureType CaptureType) const;` — Return the texture corresponding to the given CaptureType
- L80 _public prototype_ `bool IsEmpty() const;`

#### class `UBakeRenderCaptureToolBuilder`  
`class UBakeRenderCaptureToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L91-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L96 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L97 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L100 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `URenderCaptureProperties`  
`class URenderCaptureProperties : public UInteractiveToolPropertySet`  
_L111-175_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L117 _public member_ `EBakeTextureResolution Resolution = EBakeTextureResolution::Resolution512;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault, ClampMin = "1", UIMin= "1"), DisplayName="Render Capture Resolution")`
- L121 _public member_ `bool bBaseColorMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault))` — Whether to generate a texture for the Base Color property
- L125 _public member_ `bool bNormalMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault))` — Whether to generate a texture for the World Normal property
- L129 _public member_ `bool bPackedMRSMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault), DisplayName="Packed MRS Map")` — Whether to generate a packed texture with Metallic, Roughness and Specular properties
- L133 _public member_ `bool bMetallicMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault, EditCondition="bPackedMRSMap == false"))` — Whether to generate a texture for the Metallic property
- L137 _public member_ `bool bRoughnessMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault, EditCondition="bPackedMRSMap == false"))` — Whether to generate a texture for the Roughness property
- L141 _public member_ `bool bSpecularMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault, EditCondition="bPackedMRSMap == false"))` — Whether to generate a texture for the Specular property
- L145 _public member_ `bool bEmissiveMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault))` — Whether to generate a texture for the Emissive property
- L149 _public member_ `bool bOpacityMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault))` — Whether to generate a texture for the Opacity property
- L153 _public member_ `bool bSubsurfaceColorMap = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, meta = (NoResetToDefault))` — Whether to generate a texture for the SubsurfaceColor property
- L157 _public member_ `bool bAntiAliasing = false;` — `UPROPERTY(Category = RenderCaptureOptions, EditAnywhere, AdvancedDisplay)` — Whether to use anti-aliasing in the render captures, this may introduce artefacts if pixels at different scene depths get blended
- L162 _public member_ `bool bDeviceDepthMap = false;` — `UPROPERTY()` — Whether to generate a texture for the DeviceDepth.  This option is hidden from the user since its set only if the Bake operation requires a depth map to remove occlusion artefacts, which is determined by ValidSampleDepthThreshold
- L168 _public member_ `float CaptureFieldOfView = 30.0f;` — `UPROPERTY(meta = (ClampMin = "5.0", ClampMax = "160.0"))`
- L171 _public member_ `float NearPlaneDist = 1.0f;` — `UPROPERTY(meta = (ClampMin = "0.001", ClampMax = "1000.0"))`
- L173 _public prototype_ `bool operator==(const URenderCaptureProperties& Other) const;`
- L174 _public prototype_ `bool operator!=(const URenderCaptureProperties& Other) const;`

#### class `UBakeRenderCaptureToolProperties`  
`class UBakeRenderCaptureToolProperties : public UInteractiveToolPropertySet`  
_L178-224_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L186 _public member_ `FString MapPreview = TEXT("");` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta = (DisplayName="Preview Output Type", EditCondition = "bEnableMapPreview", HideEditConditionToggle, TransientToolProperty, GetOptions = GetMapPreviewNamesFunc, NoResetToDefault))` — The map type to preview
- L190 _public member_ `EBakeTextureSamplesPerPixel SamplesPerPixel = EBakeTextureSamplesPerPixel::Sample1;` — `UPROPERTY(EditAnywhere, Category = BakeOutput)` — Number of samples per pixel
- L194 _public member_ `EBakeTextureResolution TextureSize = EBakeTextureResolution::Resolution512;` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta = (ClampMin="1", UIMin="1"), DisplayName="Output Resolution")` — Size of generated textures
- L209 _public member_ `float ValidSampleDepthThreshold = 0.f;` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta = (ClampMin="0", UIMin="0"), DisplayName="Cleanup Threshold")` — This threshold is used to detect occlusion artefacts (e.g., silhouettes/blotches in the base color) so that texels exhibiting them can be cleaned up i.e., rejected and filled in using the values of nearby valid texels instead. If the threshold is zero, the cleanup step is skipped. If the threshold is too large, texels with artefacts won't be detected and the cleanup step is effectively skipped. If the threshold is too small, texels without artefacts get detected and results will be bad because there won't be enough nearby valid texels from which to infill values. A good starting point is to choose a threshold around the size of the distance (in world space) between the target and source meshes; if the target was generated by VoxWrap then the voxel size estimates this distance.
- L214 _public member_ `bool bEnableMapPreview = false;` — `UPROPERTY(Transient, meta = (TransientToolProperty))`
- L217 _public function_ `const TArray<FString>& GetMapPreviewNamesFunc()` — `UFUNCTION()`
- L223 _public member_ `TArray<FString> MapPreviewNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UBakeRenderCaptureInputToolProperties`  
`class UBakeRenderCaptureInputToolProperties : public UInteractiveToolPropertySet`  
_L228-255_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L235 _public member_ `TObjectPtr<UStaticMesh> TargetStaticMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Target Mesh", meta = (TransientToolProperty, NoResetToDefault))` — Target mesh to sample to
- L239 _public member_ `FString TargetUVLayer;` — `UPROPERTY(EditAnywhere, Category = BakeInput, meta = (DisplayName = "Target Mesh UV Channel", GetOptions = GetTargetUVLayerNamesFunc, NoResetToDefault))` — UV channel to use for the target mesh
- L242 _public function_ `int32 GetTargetUVLayerIndex() const` — `UFUNCTION()`
- L248 _public function_ `const TArray<FString>& GetTargetUVLayerNamesFunc() const` — `UFUNCTION()`
- L254 _public member_ `TArray<FString> TargetUVLayerNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UBakeRenderCaptureVisualizationProperties`  
`class UBakeRenderCaptureVisualizationProperties : public UInteractiveToolPropertySet`  
_L258-280_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L267 _public member_ `bool bPreviewAsMaterial = false;` — `UPROPERTY(EditAnywhere, Category = Preview)` — If true  preview results by connecting them to corresponding material inputs If false connect the selected preview output as the Base Color input and use empty maps for other material inputs
- L271 _public member_ `float Brightness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Preview, meta = (UIMin = "0.0", UIMax = "1.0"))` — Adjust the brightness of the Base Color material input; does not affect results stored in textures
- L275 _public member_ `float SSBrightness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Preview, meta = (UIMin = "0.0", UIMax = "1.0", DisplayName = "SS Brightness"))` — Adjust the brightness of the Subsurface Color material input; does not affect results stored in textures
- L279 _public member_ `float EmissiveScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Preview, meta = (UIMin = "0.0", UIMax = "1.0"))` — Adjust the brightness of the Emissive Color material input; does not affect results stored in textures

#### class `UBakeRenderCaptureTool`  
`class UBakeRenderCaptureTool : public UMultiSelectionMeshEditingTool, public UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshMapBaker>, public IInteractiveToolExclusiveToolAPI`  
_L290-448_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshMapBaker>,IInteractiveToolExclusiveToolAPI`
- L298 _public prototype_ `UBakeRenderCaptureTool() = default;`
- L301 _public prototype_ `virtual void Setup() override;`
- L302 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L303 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L304 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L305 _public function_ `virtual bool HasCancel() const override`
- L306 _public function_ `virtual bool HasAccept() const override`
- L307 _public prototype_ `virtual bool CanAccept() const override;`
- L311 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<UE::Geometry::FMeshMapBaker>> MakeNewOperator() override;`
- L317 _protected member_ `TArray<TObjectPtr<AActor>> Actors;` — `UPROPERTY()`
- L320 _protected member_ `TObjectPtr<UBakeRenderCaptureToolProperties> Settings;` — `UPROPERTY()`
- L321 _protected member_ `int32 MapPreviewWatcherIndex = -1;`
- L324 _protected member_ `TObjectPtr<URenderCaptureProperties> RenderCaptureProperties;` — `UPROPERTY()`
- L327 _protected member_ `TObjectPtr<UBakeRenderCaptureInputToolProperties> InputMeshSettings;` — `UPROPERTY()`
- L330 _protected member_ `TObjectPtr<UBakeRenderCaptureVisualizationProperties> VisualizationProps;` — `UPROPERTY()`
- L335 _protected member_ `TObjectPtr<UBakeRenderCaptureResults> ResultSettings;` — `UPROPERTY()` — The computed textures are displayed in the details panel and used in the preview material, they are written out to assest on shutdown.
- L339 _protected prototype_ `void UpdateResult();`
- L340 _protected prototype_ `void UpdateVisualization();`
- L341 _protected prototype_ `void InvalidateResults(UE::Geometry::FRenderCaptureTypeFlags ToInvalidate);`
- L342 _protected prototype_ `void OnMapsUpdated(const TUniquePtr<UE::Geometry::FMeshMapBaker>& NewResult);`
- L350 _protected prototype_ `bool ValidTargetMeshTangents();` — Compute validity of the Target Mesh tangents. Only checks validity once and then caches the result for successive calls. @return true if the TargetMesh tangents are valid
- L351 _protected member_ `bool bCheckTargetMeshTangents = true;`
- L352 _protected member_ `bool bValidTargetMeshTangents = false;`
- L358 _protected prototype_ `void CreateAssets(UWorld* SourceWorld);` — Create texture and material assets from our result map of Texture2D @param SourceWorld the source world to define where the assets will be stored.
- L360 _protected member_ `TUniquePtr<TGenericDataBackgroundCompute<UE::Geometry::FMeshMapBaker>> BakeOp = nullptr;`
- L361 _protected member_ `EBakeOpState BakeOpState = EBakeOpState::Evaluate;`
- L363 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> TargetMesh;`
- L364 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> TargetMeshSpatial;`
- L365 _protected member_ `TSharedPtr<TArray<int32>, ESPMode::ThreadSafe> TargetMeshUVCharts;`
- L366 _protected member_ `TSharedPtr<UE::Geometry::FMeshTangentsd, ESPMode::ThreadSafe> TargetMeshTangents;`
- L370 _protected member_ `TObjectPtr<UTexture2D> EmptyNormalMap;` — `UPROPERTY()` — Empty maps are shown when nothing is computed
- L372 _protected member_ `TObjectPtr<UTexture2D> EmptyColorMapBlack;` — `UPROPERTY()`
- L374 _protected member_ `TObjectPtr<UTexture2D> EmptyColorMapWhite;` — `UPROPERTY()`
- L376 _protected member_ `TObjectPtr<UTexture2D> EmptyEmissiveMap;` — `UPROPERTY()`
- L378 _protected member_ `TObjectPtr<UTexture2D> EmptyOpacityMap;` — `UPROPERTY()`
- L380 _protected member_ `TObjectPtr<UTexture2D> EmptySubsurfaceColorMap;` — `UPROPERTY()`
- L382 _protected member_ `TObjectPtr<UTexture2D> EmptyPackedMRSMap;` — `UPROPERTY()`
- L384 _protected member_ `TObjectPtr<UTexture2D> EmptyRoughnessMap;` — `UPROPERTY()`
- L386 _protected member_ `TObjectPtr<UTexture2D> EmptyMetallicMap;` — `UPROPERTY()`
- L388 _protected member_ `TObjectPtr<UTexture2D> EmptySpecularMap;` — `UPROPERTY()`
- L390 _protected member_ `float SecondsBeforeWorkingMaterial = 0.75;`
- L393 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> WorkingPreviewMaterial;` — `UPROPERTY()`
- L395 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> ErrorPreviewMaterial;` — `UPROPERTY()`
- L397 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewMaterialRC;` — `UPROPERTY()`
- L399 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewMaterialPackedRC;` — `UPROPERTY()`
- L401 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewMaterialRC_Subsurface;` — `UPROPERTY()`
- L403 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewMaterialPackedRC_Subsurface;` — `UPROPERTY()`
- L405 _protected prototype_ `void InitializePreviewMaterials();`
- L408 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L411 _protected member_ `TSharedPtr<UE::Geometry::FSceneCapturePhotoSet, ESPMode::ThreadSafe> SceneCapture;` — Note: We need to compute this on the game thread because the implementation has checks for this
- L414 _protected member_ `float ComputedValidDepthThreshold;` — These are used to determine if we need to re-bake results
- L415 _protected member_ `EBakeTextureSamplesPerPixel ComputedSamplesPerPixel = EBakeTextureSamplesPerPixel::Sample1;`
- L416 _protected member_ `EBakeTextureResolution ComputedTextureSize = EBakeTextureResolution::Resolution512;`
- L417 _protected member_ `FString ComputedTargetUVLayer;`
- L419 _protected member_ `TMap<int, FText> TargetUVLayerToError;`
- L442 _protected member_ `FBakeAnalytics BakeAnalytics;`
- L444 _protected function_ `FString GetAnalyticsEventName() const`
- L445 _protected prototype_ `void GatherAnalytics(FBakeAnalytics::FMeshSettings& Data);`
- L446 _protected prototype_ `void GatherAnalytics(const UE::Geometry::FMeshMapBaker& Result);`
- L447 _protected prototype_ `void RecordAnalytics() const;`

#### struct `UBakeRenderCaptureTool::FBakeAnalytics`  
`struct FBakeAnalytics`  
_L425-440_
- L427 _public member_ `double TotalBakeDuration = 0.0;`
- L428 _public member_ `double WriteToImageDuration = 0.0;`
- L429 _public member_ `double WriteToGutterDuration = 0.0;`
- L430 _public member_ `int64 NumSamplePixels = 0;`
- L431 _public member_ `int64 NumGutterPixels = 0;`
- L439 _public member_ `FMeshSettings MeshSettings;`

#### struct `UBakeRenderCaptureTool::FBakeAnalytics::FMeshSettings`  
`struct FMeshSettings`  
_L433-438_
- L435 _public member_ `int32 NumTargetMeshTris = 0;`
- L436 _public member_ `int32 NumDetailMesh = 0;`
- L437 _public member_ `int64 NumDetailMeshTris = 0;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`
- L23 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/BspConversionTool.h` (Public)


#### class `UBspConversionToolBuilder`  
`class UBspConversionToolBuilder : public UInteractiveToolBuilder`  
_L25-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for UBspConversionTool.
- L29 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L30 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### enum `EBspConversionMode`  
`enum class EBspConversionMode : uint8`  
_L35-42_
- reflection: `UENUM()`
- L38 _public enumerator_ `ConvertFirst = 0 UMETA(DisplayName = "Convert, then Combine")` — First converts the brushes to static meshes, then performs mesh boolean operations.
- L41 _public enumerator_ `CombineFirst = 1 UMETA(DisplayName = "Combine, then Convert")` — First combines brushes using brush CSG operations, then converts result to static mesh (legacy path).

#### class `UBspConversionToolProperties`  
`class UBspConversionToolProperties : public UInteractiveToolPropertySet`  
_L48-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L55 _public member_ `EBspConversionMode ConversionMode = EBspConversionMode::ConvertFirst;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L59 _public member_ `bool bIncludeVolumes = false;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Options)` — Whether to consider BSP volumes to be valid conversion targets.
- L63 _public member_ `bool bRemoveConvertedVolumes = false;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Options, meta = (EditCondition = "bIncludeVolumes"))` — Whether to remove any selected BSP volumes after using them to create a static mesh.
- L68 _public member_ `bool bExplicitSubtractiveBrushSelection = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Options)` — Whether subtractive brushes have to be explicitly selected to be part of the conversion. If false, all subtractive brushes in the level will be used.
- L73 _public member_ `bool bRemoveConvertedSubtractiveBrushes = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Options)` — Whether subtractive brushes used in a conversion should be removed. Only acts on explicitly selected subtractive brushes.
- L78 _public member_ `bool bCacheBrushes = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Options, AdvancedDisplay, meta = (EditCondition = "ConversionMode == EBspConversionMode::ConvertFirst"))` — Caches individual brush conversions in "convert then combine" mode during a single invocation of the tool. Only useful if changing selections or properties after starting the tool. Cleared on tool shutdown.
- L83 _public member_ `bool bShowPreview = true;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = PreviewOptions, AdvancedDisplay)` — Determines whether a dynamic preview is shown. Note that this introduces non-background computations at each event that changes the result, rather than only performing a computation on Accept.

#### enum `EBspConversionToolAction`  
`enum class EBspConversionToolAction`  
_L87-94_
- reflection: `UENUM()`
- L89 _public enumerator_ `NoAction`
- L91 _public enumerator_ `SelectAllValidBrushes`
- L92 _public enumerator_ `DeselectVolumes`
- L93 _public enumerator_ `DeselectNonValid`

#### class `UBspConversionToolActionPropertySet`  
`class UBspConversionToolActionPropertySet : public UInteractiveToolPropertySet`  
_L97-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L102 _public member_ `TWeakObjectPtr<UBspConversionTool> ParentTool;`
- L104 _public function_ `void Initialize(UBspConversionTool* ParentToolIn)`
- L105 _public prototype_ `void PostAction(EBspConversionToolAction Action);`
- L109 _public function_ `void SelectAllValidBrushes()` — `UFUNCTION(CallInEditor, Category = SelectionOperations, Meta = (DisplayName = "Select All Valid Brushes", DisplayPriority = 1))` — Select all brushes that satisfy the current settings.
- L113 _public function_ `void DeselectVolumes()` — `UFUNCTION(CallInEditor, Category = SelectionOperations, Meta = (DisplayName = "Deselect Volumes", DisplayPriority = 2))` — Deselect any currently selected volume brushes.
- L117 _public function_ `void DeselectNonValid()` — `UFUNCTION(CallInEditor, Category = SelectionOperations, Meta = (DisplayName = "Deselect Non-Valid", DisplayPriority = 3))` — Deselect any currently selected brushes that are not valid targets given current settings.

#### class `UBspConversionTool`  
`class UBspConversionTool : public UInteractiveTool`  
_L130-189_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool`
- desc: Converts BSP brushes to static meshes. Known limitations: - Preview does not respond to property changes in the brush detail panel while the tool is running. User would need to create some event that does change the preview (such as tool property change, or selection change). - BSP brushes with non-manifold geometry (specifically, the stair brushes) cannot be used with the "Convert, then combine" path because boolean operations do not allow them. The user gets properly notified of this if it comes up.
- L135 _public prototype_ `UBspConversionTool();`
- L137 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L139 _public prototype_ `virtual void Setup() override;`
- L140 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L142 _public function_ `virtual void SetWorld(UWorld* World)`
- L144 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L145 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L147 _public function_ `virtual bool HasCancel() const override`
- L148 _public function_ `virtual bool HasAccept() const override`
- L149 _public prototype_ `virtual bool CanAccept() const override;`
- L151 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L153 _public prototype_ `virtual void RequestAction(EBspConversionToolAction ActionType);`
- L156 _public member_ `TObjectPtr<UBspConversionToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L159 _public member_ `TObjectPtr<UBspConversionToolActionPropertySet> ToolActions = nullptr;` — `UPROPERTY()`
- L162 _protected member_ `bool bCanAccept = false;`
- L164 _protected member_ `UWorld* TargetWorld;`
- L165 _protected member_ `EBspConversionToolAction PendingAction;`
- L168 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L170 _protected member_ `TArray<ABrush*> BrushesToConvert;`
- L171 _protected member_ `TArray<ABrush*> BrushesToDelete;`
- L172 _protected member_ `ABrush* BrushForPivot = nullptr;`
- L175 _protected member_ `TMap<ABrush*, TPair<TSharedPtr<const UE::Geometry::FDynamicMesh3>, TSharedPtr<const TArray<UMaterialInterface*>>>> CachedBrushes;`
- L177 _protected prototype_ `bool IsValidConversionTarget(const ABrush* Brush) const;`
- L178 _protected prototype_ `bool AtLeastOneValidConversionTarget() const;`
- L179 _protected prototype_ `bool CompareAndUpdateConversionTargets();`
- L181 _protected prototype_ `void OnEditorSelectionChanged(UObject* NewSelection);`
- L182 _protected prototype_ `void OnEditorLevelActorListChanged();`
- L183 _protected prototype_ `void OnEditorActorMoved(AActor* InActor);`
- L185 _protected prototype_ `void ApplyAction(EBspConversionToolAction ActionType);`
- L186 _protected prototype_ `bool ComputeAndUpdatePreviewMesh(FText* ErrorMessage = nullptr);`
- L187 _protected prototype_ `bool ConvertThenCombine(FText* ErrorMessage = nullptr);`
- L188 _protected prototype_ `bool CombineThenConvert(FText* ErrorMessage = nullptr);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/DrawSplineTool.h` (Public)


#### enum `EDrawSplineDrawMode`  
`enum class EDrawSplineDrawMode : uint8`  
_L28-37_
- reflection: `UENUM()`
- L32 _public enumerator_ `TangentDrag` — Click to place a point and then drag to set its tangent. Clicking without dragging will create sharp corners.
- L34 _public enumerator_ `ClickAutoTangent` — Click and drag new points, with the tangent set automatically
- L36 _public enumerator_ `FreeDraw` — Drag to place multiple points, with spacing controlled by Min Point Spacing

#### enum `ESplineOffsetMethod`  
`enum class ESplineOffsetMethod : uint8`  
_L40-46_
- reflection: `UENUM()`
- L43 _public enumerator_ `HitNormal` — Spline points will be offset along the normal direction of the clicked surface
- L45 _public enumerator_ `Custom` — Spline points will be offset along a manually-chosen direction

#### enum `EDrawSplineOutputMode`  
`enum class EDrawSplineOutputMode : uint8`  
_L49-64_
- reflection: `UENUM()`
- L52 _public enumerator_ `EmptyActor` — Create a new empty actor with the spline inside it
- L55 _public enumerator_ `ExistingActor` — Attach the spline to an existing actor, or replace a spline inside that actor if Existing Spline Index To Replace is valid.
- L59 _public enumerator_ `CreateBlueprint` — Create the blueprint specified by Blueprint To Create, and either attach the spline to that, or replace an existing spline if Existing Spline Index To Replace is valid.

#### enum `EDrawSplineUpVectorMode`  
`enum class EDrawSplineUpVectorMode : uint8`  
_L67-74_
- reflection: `UENUM()`
- L71 _public enumerator_ `AlignToPrevious` — Pick the first up vector based on the hit normal, and then align subsequent up vectors with the previous ones.
- L73 _public enumerator_ `UseHitNormal` — Base the up vector off the hit normal.

#### class `UDrawSplineToolProperties`  
`class UDrawSplineToolProperties : public UInteractiveToolPropertySet`  
_L77-201_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L89 _public member_ `bool bLoop = false;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (TransientToolProperty))` — Determines whether the created spline is a loop. This can be toggled using "Closed Loop" in the detail panel after spline creation.
- L95 _public member_ `EDrawSplineOutputMode OutputMode = EDrawSplineOutputMode::EmptyActor;` — `UPROPERTY(EditAnywhere, Category = Spline)` — Determines how the resulting spline is emitted on tool accept.
- L102 _public member_ `TWeakObjectPtr<AActor> TargetActor = nullptr;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (TransientToolProperty, EditCondition = "OutputMode == EDrawSplineOutputMode::ExistingActor", EditConditionHides))` — Actor to attach to when Output Mode is "Existing Actor"
- L109 _public member_ `TWeakObjectPtr<UBlueprint> BlueprintToCreate;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = ( EditCondition = "OutputMode == EDrawSplineOutputMode::CreateBlueprint", EditConditionHides))` — Blueprint to create when Output Mode is "Create Blueprint"
- L118 _public member_ `int32 ExistingSplineIndexToReplace = 0;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (ClampMin = -1, UIMax = 10, EditConditionHides, EditCondition = "OutputMode == EDrawSplineOutputMode::ExistingActor || OutputMode == EDrawSplineOutputMode::CreateBlueprint"))` — When attaching to an existing actor or creating a blueprint, controls whether the drawn spline replaces one of the target's existing components or gets added as a new one (if the index is out of bounds).
- L124 _public member_ `EDrawSplineDrawMode DrawMode = EDrawSplineDrawMode::TangentDrag;` — `UPROPERTY(EditAnywhere, Category = Spline)` — How the spline is drawn in the tool.
- L129 _public member_ `double MinPointSpacing = 200;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (ClampMin = 0, UIMax = 1000, EditCondition = "DrawMode == EDrawSplineDrawMode::FreeDraw", EditConditionHides))` — Point spacing when Draw Mode is "Free Draw"
- L133 _public member_ `double ClickOffset = 0;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (UIMin = 0, UIMax = 100))` — How far to offset spline points from the clicked surface, along the surface normal
- L137 _public member_ `ESplineOffsetMethod OffsetMethod = ESplineOffsetMethod::HitNormal;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (EditCondition = "ClickOffset > 0", EditConditionHides))` — How to choose the direction to offset points from the clicked surface
- L141 _public member_ `FVector OffsetDirection = FVector::UpVector;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (EditCondition = "ClickOffset > 0 && OffsetMethod == ESplineOffsetMethod::Custom", EditConditionHides))` — Manually-specified click offset direction. Note: Will be normalized. If it is a zero vector, a default Up vector will be used instead.
- L148 _public member_ `double FrameVisualizationWidth = 0;` — `UPROPERTY(EditAnywhere, Category = Spline, AdvancedDisplay, meta = (ClampMin = 0, UIMax = 100))` — When nonzero, allows a visualization of the rotation of the spline. Can be controlled in the detail panel after creation via "Scale Visualization Width" property.
- L155 _public member_ `EDrawSplineUpVectorMode UpVectorMode = EDrawSplineUpVectorMode::UseHitNormal;` — `UPROPERTY(EditAnywhere, Category = Spline, AdvancedDisplay)` — How the spline rotation is set. It is suggested to use a nonzero FrameVisualizationWidth to see the effects.
- L164 _public member_ `bool bPreviewUsingActorCopy = true;` — `UPROPERTY(EditAnywhere, Category = Spline, AdvancedDisplay, meta=( EditCondition = "OutputMode != EDrawSplineOutputMode::EmptyActor"))` — When modifying existing actors, whether the result should be previewed using a copy of that actor (rather than just drawing the spline by itself). Could be toggled off if something about duplicating the given actor is problematic.
- L168 _public member_ `bool bHitWorld = true;` — `UPROPERTY(EditAnywhere, Category = RaycastTargets, meta = (DisplayName = "World Objects"))` — Whether to place spline points on the surface of objects in the world
- L172 _public member_ `bool bHitCustomPlane = false;` — `UPROPERTY(EditAnywhere, Category = RaycastTargets, meta = (DisplayName = "Custom Plane"))` — Whether to place spline points on a custom, user-adjustable plane
- L176 _public member_ `bool bHitGroundPlanes = true;` — `UPROPERTY(EditAnywhere, Category = RaycastTargets, meta = (DisplayName = "Ground Planes"))` — Whether to place spline points on a plane through the origin aligned with the Z axis in perspective views, or facing the camera in othographic views
- L180 _public member_ `bool bFitToSurface = false;` — `UPROPERTY(EditAnywhere, Category = RaycastTargets, meta = (EditCondition = bMeshSelected, HideEditConditionToggle))` — Whether to fit the spline to the selected surface. The spline will be subdivided and projected to reduce the distance between the spline and the surface
- L184 _public member_ `int32 MaxNewPoints = 100;` — `UPROPERTY(EditAnywhere, Category = RaycastTargets, meta = (EditCondition = "bFitToSurface && bMeshSelected", ClampMin = 0, UIMax = 100))` — The maximum number of times the spline will be subdivided in order to fit the surface
- L188 _public member_ `double DistanceThreshold = 1.0;` — `UPROPERTY(EditAnywhere, Category = RaycastTargets, meta = (EditCondition = "bFitToSurface && bMeshSelected", ClampMin = 0, UIMax = 100))` — The threshold for spline subdivision. New points are iteratively added where the distance from the spline to the surface is greater than this value
- L196 _public member_ `bool bRerunConstructionScriptOnDrag = true;` — `UPROPERTY(EditAnywhere, Category = Spline, AdvancedDisplay, meta = ( EditCondition = "OutputMode != EDrawSplineOutputMode::EmptyActor"))` — If modifying a blueprint actor, whether to run the construction script while dragging or only at the end of a drag. Can be toggled off for expensive construction scripts.
- L200 _public member_ `bool bMeshSelected = false;` — `UPROPERTY()` — Hidden property set by the tool

#### class `UDrawSplineTool`  
`class UDrawSplineTool : public USingleSelectionMeshEditingTool , public IClickBehaviorTarget , public IClickDragBehaviorTarget`  
_L204-315_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,IClickBehaviorTarget,IClickDragBehaviorTarget`
- L212 _public prototype_ `virtual void SetSelectedActor(AActor* Actor);`
- L214 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L215 _public function_ `virtual UWorld* GetTargetWorld()`
- L218 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L219 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L220 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L221 _public function_ `virtual bool HasCancel() const override`
- L222 _public function_ `virtual bool HasAccept() const override`
- L223 _public prototype_ `virtual bool CanAccept() const override;`
- L224 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L225 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L228 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos);` — IClickBehaviorTarget
- L229 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos);`
- L232 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos);` — IClickDragBehaviorTarget
- L233 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos);`
- L234 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos);`
- L235 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos);`
- L236 _public prototype_ `virtual void OnTerminateDragSequence();`
- L240 _private member_ `TObjectPtr<UDrawSplineToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L243 _private member_ `TObjectPtr<USingleClickOrDragInputBehavior> ClickOrDragBehavior = nullptr;` — `UPROPERTY()`
- L246 _private member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L248 _private member_ `TWeakObjectPtr<UWorld> TargetWorld = nullptr;`
- L251 _private member_ `TWeakObjectPtr<AActor> StartupSelectedActor = nullptr;` — This is only used to initialize TargetActor in the settings object
- L256 _private member_ `TObjectPtr<AActor> PreviewActor = nullptr;` — `UPROPERTY()` — The preview actor is either a APreviewGeometryActor with a spline, or a duplicate of some target blueprint actor so that we can see the effects of the drawn spline immediately.
- L259 _private member_ `int32 SplineRecaptureIndex = 0;` — Used for recapturing the spline when rerunning construction scripts
- L263 _private member_ `TWeakObjectPtr<USplineComponent> WorkingSpline = nullptr;` — This is the spline we add points to. It points to a component nested somewhere under PreviewRootActor.
- L265 _private member_ `bool bDrawTangentForLastPoint = false;`
- L266 _private member_ `bool bFreeDrawPlacedPreviewPoint = false;`
- L267 _private member_ `int32 FreeDrawStrokeStartIndex = 0;`
- L269 _private prototype_ `void RefitToSurface();`
- L271 _private prototype_ `bool Raycast(const FRay& WorldRay, FVector3d& HitLocationOut, FVector3d& HitNormalOut, double& HitTOut);`
- L272 _private prototype_ `void AddSplinePoint(const FVector3d& HitLocation, const FVector3d& UpVector);`
- L273 _private prototype_ `FVector3d GetUpVectorToUse(const FVector3d& HitLocation, const FVector3d& HitNormal, int32 NumSplinePointsBeforehand);`
- L275 _private prototype_ `void TransitionOutputMode();`
- L276 _private prototype_ `void GenerateAsset();`
- L281 _private member_ `TObjectPtr<AActor> PreviousTargetActor = nullptr;` — `UPROPERTY()` — Used to restore visibility of previous actor when switching to a different one, and to avoid switching target actors if the new value is invalid (e.g., user clicked the preview actor with the actor picker)
- L283 _private member_ `int32 TargetActorWatcherID = -1;`
- L284 _private member_ `bool PreviousTargetActorVisibility = true;`
- L286 _private member_ `TWeakObjectPtr<USplineComponent> HiddenSpline = nullptr;` — Used to restore visibility of previous spline when switching to a different one
- L287 _private member_ `bool bPreviousSplineVisibility = true;`
- L289 _private member_ `bool bNeedToRerunConstructionScript = false;`
- L291 _private member_ `FViewCameraState CameraState;`
- L293 _private member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> ProjectionTarget;`
- L294 _private member_ `TUniquePtr<UE::Geometry::FDynamicMesh3> ProjectionTargetMesh;`
- L295 _private member_ `FTransform MeshTargetTransform;`
- L296 _private member_ `TWeakObjectPtr<USplineComponent> ProjectionSpline = nullptr;`
- L300 _private member_ `UE::TransactionUtil::FLongTransactionTracker LongTransactions;`

#### class `UDrawSplineTool::FSplineChange`  
`class FSplineChange : public FToolCommandChange`  
_L304-314_
- inherits: `FToolCommandChange`
- desc: Helper class for making undo/redo transactions, to avoid friending all the variations.
- L308 _public prototype_ `virtual void Apply(UObject* Object) override;` — These pass the working spline to the overloads below
- L309 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L312 _protected prototype_ `virtual void Apply(USplineComponent& Spline) = 0;`
- L313 _protected prototype_ `virtual void Revert(USplineComponent& Spline) = 0;`

#### class `UDrawSplineToolBuilder`  
`class UDrawSplineToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L320-330_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L325 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L327 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L329 _public prototype_ `virtual void InitializeNewTool(USingleSelectionMeshEditingTool* Tool, const FToolBuilderState& SceneState) const override;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/EditMeshMaterialsTool.h` (Public)


#### class `UEditMeshMaterialsToolBuilder`  
`class UEditMeshMaterialsToolBuilder : public UMeshSelectionToolBuilder`  
_L15-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSelectionToolBuilder`
- L20 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L21 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UEditMeshMaterialsToolProperties`  
`class UEditMeshMaterialsToolProperties : public UInteractiveToolPropertySet`  
_L30-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L36 _public member_ `FString ActiveMaterial;` — `UPROPERTY(EditAnywhere, Category = Materials, meta = (TransientToolProperty, DisplayName = "Active Material", GetOptions = GetMaterialNamesFunc, NoResetToDefault))`
- L39 _public function_ `const TArray<FString>& GetMaterialNamesFunc()` — `UFUNCTION()`
- L42 _public member_ `TArray<FString> MaterialNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L44 _public prototype_ `void UpdateFromMaterialsList();`
- L45 _public prototype_ `int32 GetSelectedMaterialIndex() const;`
- L48 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(EditAnywhere, Category=Materials)`

#### enum `EEditMeshMaterialsToolActions`  
`enum class EEditMeshMaterialsToolActions`  
_L56-60_
- reflection: `UENUM()`
- L58 _public enumerator_ `NoAction`
- L59 _public enumerator_ `AssignMaterial`

#### class `UEditMeshMaterialsEditActions`  
`class UEditMeshMaterialsEditActions : public UMeshSelectionToolActionPropertySet`  
_L65-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSelectionToolActionPropertySet`
- L71 _public function_ `void AssignActiveMaterial()` — `UFUNCTION(CallInEditor, Category = MaterialEdits, meta = (DisplayName = "Assign Active Material", DisplayPriority = 1))`
- L76 _public prototype_ `void PostMaterialAction(EEditMeshMaterialsToolActions Action);`

#### class `UEditMeshMaterialsTool`  
`class UEditMeshMaterialsTool : public UMeshSelectionTool`  
_L88-146_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSelectionTool`
- L93 _public prototype_ `virtual void Setup() override;`
- L94 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L95 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L97 _public prototype_ `virtual bool CanAccept() const override;`
- L99 _public prototype_ `void RequestMaterialAction(EEditMeshMaterialsToolActions ActionType);`
- L103 _protected member_ `TObjectPtr<UEditMeshMaterialsToolProperties> MaterialProps;` — `UPROPERTY()`
- L105 _protected prototype_ `virtual UMeshSelectionToolActionPropertySet* CreateEditActions() override;`
- L106 _protected prototype_ `virtual void AddSubclassPropertySets() override;`
- L108 _protected member_ `bool bHavePendingSubAction = false;`
- L109 _protected member_ `EEditMeshMaterialsToolActions PendingSubAction = EEditMeshMaterialsToolActions::NoAction;`
- L111 _protected prototype_ `void ApplyMaterialAction(EEditMeshMaterialsToolActions ActionType);`
- L112 _protected prototype_ `void AssignMaterialToSelectedTriangles();`
- L114 _protected member_ `TArray<UMaterialInterface*> CurrentMaterials;`
- L115 _protected prototype_ `void OnMaterialSetChanged();`
- L122 _protected prototype_ `FMaterialSetKey GetMaterialKey();`
- L124 _protected member_ `FMaterialSetKey InitialMaterialKey;`
- L125 _protected member_ `bool bHaveModifiedMaterials = false;`
- L126 _protected member_ `bool bShowingMaterialSetError = false;`
- L127 _protected member_ `bool bShowingNotEnoughMaterialsError = false;`
- L129 _protected prototype_ `virtual void ApplyShutdownAction(EToolShutdownType ShutdownType) override;`
- L131 _protected prototype_ `void ExternalUpdateMaterialSet(const TArray<UMaterialInterface*>& NewMaterialSet);`
- L137 _private prototype_ `int32 FindMaxActiveMaterialID() const;` — @return the max material ID used in the PreviewMesh
- L140 _private prototype_ `bool FixInvalidMaterialIDs();` — Clamp material IDs to be less than the number of materials
- L143 _private prototype_ `void UpdateMaterialSetErrors();` — Update error messages regarding whether we have enough materials on the current mesh
- L145 _private member_ `int32 MaterialSetWatchIndex = -1;`

#### struct `UEditMeshMaterialsTool::FMaterialSetKey`  
`struct FMaterialSetKey`  
_L117-121_
- L119 _public member_ `TArray<void*> Values;`
- L120 _public prototype_ `bool operator!=(const FMaterialSetKey& Key2) const;`

#### class `FEditMeshMaterials_MaterialSetChange`  
`class FEditMeshMaterials_MaterialSetChange : public FToolCommandChange`  
_L153-167_
- inherits: `FToolCommandChange`
- L156 _public member_ `TArray<UMaterialInterface*> MaterialsBefore;`
- L157 _public member_ `TArray<UMaterialInterface*> MaterialsAfter;`
- L160 _public prototype_ `virtual void Apply(UObject* Object) override;` — Makes the change to the object
- L163 _public prototype_ `virtual void Revert(UObject* Object) override;` — Reverts change to the object
- L166 _public prototype_ `virtual FString ToString() const override;` — Describes this change (for debugging)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/HarvestInstancesTool.h` (Public)


#### class `UHarvestInstancesToolBuilder`  
`class UHarvestInstancesToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L26-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L31 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L33 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L35 _public prototype_ `virtual void InitializeNewTool(UMultiSelectionMeshEditingTool* NewTool, const FToolBuilderState& SceneState) const override;`
- L38 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UHarvestInstancesToolSettings`  
`class UHarvestInstancesToolSettings : public UInteractiveToolPropertySet`  
_L46-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for the Pattern Tool
- L53 _public member_ `bool bDrawBounds = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Display the bounding box of each mesh that will be moved to instances. Bounding box colors indicate instance groupings.

#### enum `EHarvestInstancesToolOutputType`  
`enum class EHarvestInstancesToolOutputType`  
_L59-63_
- reflection: `UENUM()`
- L61 _public enumerator_ `HISMC UMETA(DisplayName="Hierarchical (HISM)")`
- L62 _public enumerator_ `ISMC UMETA(DisplayName="Non-Hierarchical (ISM)")`

#### class `UHarvestInstancesTool_OutputSettings`  
`class UHarvestInstancesTool_OutputSettings : public UInteractiveToolPropertySet`  
_L71-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Output Settings for the Pattern Tool
- L77 _public member_ `EHarvestInstancesToolOutputType ComponentType = EHarvestInstancesToolOutputType::HISMC;` — `UPROPERTY(EditAnywhere, Category = Output)` — Which type of Instanced Static Mesh Component to Create
- L81 _public member_ `bool bSingleActor = false;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (EditCondition="bHaveSingleInstanceSet == false", HideEditConditionToggle))` — Group all output Instanced Components under a single Actor. By default, multiple Actors will be created.
- L85 _public member_ `FString ActorName = TEXT("Ins` — `UPROPERTY(EditAnywhere, Category = Output, meta=(TransientToolProperty, DisplayName="New Actor Name", EditCondition = "bHaveSingleInstanceSet || bSingleActor == true"))` — Base Name to use for the emitted single Actor
- L88 _public member_ `bool bIncludeSingleInstances = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Output, meta = (EditCondition = "bSingleActor == true && bHaveLonerInstances == true", HideEditConditionToggle))`
- L92 _public member_ `bool bDeleteInputs = true;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (EditCondition = "bCanDeleteInputs == true", HideEditConditionToggle))` — Delete Actors that have had their Components harvested
- L95 _public member_ `bool bHaveSingleInstanceSet = false;` — `UPROPERTY(meta=(TransientToolProperty))`
- L98 _public member_ `bool bHaveLonerInstances = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L101 _public member_ `bool bCanDeleteInputs = true;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UHarvestInstancesTool`  
`class UHarvestInstancesTool : public UMultiSelectionMeshEditingTool`  
_L110-175_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool`
- desc: UHarvestInstancesTool
- L115 _public prototype_ `UHarvestInstancesTool();`
- L117 _public prototype_ `virtual void Setup() override;`
- L118 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L120 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L122 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L124 _public function_ `virtual bool HasCancel() const override`
- L125 _public function_ `virtual bool HasAccept() const override`
- L126 _public function_ `virtual bool CanAccept() const override`
- L130 _public member_ `TObjectPtr<UHarvestInstancesToolSettings> Settings;` — `UPROPERTY()`
- L133 _public member_ `TObjectPtr<UHarvestInstancesTool_OutputSettings> OutputSettings;` — `UPROPERTY()`
- L137 _protected prototype_ `void OnParametersUpdated();`
- L147 _protected member_ `TArray<FSourceMesh> SourceMeshes;`
- L160 _protected member_ `TArray<FInstanceSet> InstanceSets;`
- L162 _protected member_ `TArray<AActor*> SourceActors;`
- L163 _protected member_ `TArray<UPrimitiveComponent*> SourceComponents;`
- L165 _protected member_ `bool bHaveNonUniformScaleElements = false;`
- L169 _protected prototype_ `void InitializeInstanceSets();`
- L170 _protected prototype_ `void UpdateInstanceSets();`
- L172 _protected prototype_ `void EmitResults();`
- L174 _protected prototype_ `void UpdateWarningMessages();`

#### struct `UHarvestInstancesTool::FSourceMesh`  
`struct FSourceMesh`  
_L140-146_
- L142 _public member_ `TArray<UStaticMeshComponent*> SourceComponents;`
- L143 _public member_ `UStaticMesh* Mesh;`
- L144 _public member_ `TArray<UMaterialInterface*> InstanceMaterials;`
- L145 _public member_ `TArray<FTransform> InstanceTransformsWorld;`

#### struct `UHarvestInstancesTool::FInstanceSet`  
`struct FInstanceSet`  
_L149-159_
- L151 _public member_ `TArray<UStaticMeshComponent*> SourceComponents;`
- L152 _public member_ `TArray<AActor*> SourceActors;`
- L154 _public member_ `UStaticMesh* StaticMesh = nullptr;`
- L155 _public member_ `FBox Bounds;`
- L156 _public member_ `TArray<UMaterialInterface*> InstanceMaterials;`
- L158 _public member_ `TArray<FTransform> WorldInstanceTransforms;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/ISMEditorTool.h` (Public)


#### class `UISMEditorToolBuilder`  
`class UISMEditorToolBuilder : public UInteractiveToolBuilder`  
_L34-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L39 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L40 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### enum `EISMEditorTransformMode`  
`enum class EISMEditorTransformMode : uint8`  
_L47-59_
- reflection: `UENUM()`
- desc: Mesh Transform modes
- L50 _public enumerator_ `SharedGizmo = 0 UMETA(DisplayName = "Shared Gizmo")` — Single Gizmo for all Instances
- L53 _public enumerator_ `SharedGizmoLocal = 1 UMETA(DisplayName = "Shared Gizmo (Local)")` — Single Gizmo for all Instances, Rotations applied per-Instance
- L56 _public enumerator_ `PerObjectGizmo = 2 UMETA(DisplayName = "Multi-Gizmo")` — Separate Gizmo for each Instance
- L58 _public enumerator_ `LastValue UMETA(Hidden)`

#### class `UISMEditorToolProperties`  
`class UISMEditorToolProperties : public UInteractiveToolPropertySet`  
_L66-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the Transform Meshes operation
- L73 _public member_ `EISMEditorTransformMode TransformMode = EISMEditorTransformMode::SharedGizmo;` — `UPROPERTY(EditAnywhere, Category = Options)` — Transformation Mode controls the overall behavior of the Gizmos in the Tool
- L77 _public member_ `bool bSetPivotMode = false;` — `UPROPERTY(EditAnywhere, Category = Pivot, meta = (TransientToolProperty, EditCondition = "TransformMode != EISMEditorTransformMode::PerObjectGizmo"))` — When true, the Gizmo can be moved independently without affecting objects. This allows the Gizmo to be repositioned before transforming.
- L81 _public member_ `bool bShowSelectable = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Show a highlight around all selectable instances
- L85 _public member_ `bool bShowSelected = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Show a highlight around the selected instances
- L89 _public member_ `bool bHideWhenDragging = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)` — Hide the Selectable and Selected highlights when dragging with the Gizmos
- L93 _public member_ `TArray<FString> SelectedInstances;` — `UPROPERTY(VisibleAnywhere, Category = Selection)` — List of selected Component/Instance values

#### struct `FISMEditorTarget`  
`struct FISMEditorTarget`  
_L98-107_
- reflection: `USTRUCT()`
- L103 _public member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L106 _public member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`

#### enum `EISMEditorToolActions`  
`enum class EISMEditorToolActions`  
_L112-124_
- reflection: `UENUM()`
- L114 _public enumerator_ `NoAction`
- L115 _public enumerator_ `ClearSelection`
- L116 _public enumerator_ `ContractLast`
- L117 _public enumerator_ `ExpandLast`
- L118 _public enumerator_ `ExpandAll`
- L119 _public enumerator_ `Delete`
- L120 _public enumerator_ `Duplicate`
- L121 _public enumerator_ `DuplicateToNew`
- L122 _public enumerator_ `ExtractToNew`
- L123 _public enumerator_ `Replace`

#### class `UISMEditorToolActionPropertySetBase`  
`class UISMEditorToolActionPropertySetBase : public UInteractiveToolPropertySet`  
_L128-137_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L132 _public member_ `TWeakObjectPtr<UISMEditorTool> ParentTool;`
- L134 _public function_ `void Initialize(UISMEditorTool* ParentToolIn)`
- L136 _public prototype_ `void PostAction(EISMEditorToolActions Action);`

#### class `UISMEditorToolActionPropertySet`  
`class UISMEditorToolActionPropertySet : public UISMEditorToolActionPropertySetBase`  
_L142-175_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UISMEditorToolActionPropertySetBase`
- L148 _public function_ `void ClearSelection()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 0))` — Clear the active instance selection
- L154 _public function_ `void ContractLast()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 1))` — Take the last selected element and contract the selection to exclude any instances of that static mesh and materials.
- L160 _public function_ `void ExpandLast()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 2))` — Take the last selected element and expand the selection to include any other instances of the same static mesh and materials.
- L166 _public function_ `void ExpandAll()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 3))` — Expand the selection to include any other instances of the same static mesh(es) and materials as selected.
- L170 _public function_ `void Delete()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 4))` — Delete the selected instances
- L174 _public function_ `void Duplicate()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 5))` — Duplicate the selected instances

#### class `UISMEditorToolReplacePropertySet`  
`class UISMEditorToolReplacePropertySet : public UISMEditorToolActionPropertySetBase`  
_L180-190_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UISMEditorToolActionPropertySetBase`
- L185 _public member_ `TObjectPtr<UStaticMesh> ReplaceWith = nullptr;` — `UPROPERTY(EditAnywhere, Category = Replace)`
- L189 _public function_ `void Replace()` — `UFUNCTION(CallInEditor, Category = Replace, meta = (DisplayPriority = 0))` — Clear the active instance selection

#### class `UISMEditorToolExtractPropertySet`  
`class UISMEditorToolExtractPropertySet : public UISMEditorToolActionPropertySetBase`  
_L193-212_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UISMEditorToolActionPropertySetBase`
- L199 _public member_ `FString ActorName;` — `UPROPERTY(EditAnywhere, Category = Extract)` — Name to use when duplicating or extracting to a new actor.
- L203 _public member_ `bool bCreateHISMs = false;` — `UPROPERTY(EditAnywhere, Category = Extract)` — When true, the components created when extracting to a new actor are HISM's instead of ISM's.
- L207 _public function_ `void DuplicateToNew()` — `UFUNCTION(CallInEditor, Category = Extract)` — Duplicate the selected instances into a new actor.
- L211 _public function_ `void ExtractToNew()` — `UFUNCTION(CallInEditor, Category = Extract)` — Duplicate the selected instances into a new actor and delete them from the current actor(s).

#### class `UISMEditorTool`  
`class UISMEditorTool : public UInteractiveTool, public IInteractiveToolCameraFocusAPI, public IClickBehaviorTarget`  
_L220-354_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolCameraFocusAPI,IClickBehaviorTarget`
- L225 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L227 _public prototype_ `virtual void SetTargets(TArray<UInstancedStaticMeshComponent*> Components);`
- L229 _public prototype_ `virtual void Setup() override;`
- L230 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L232 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L233 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L234 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L236 _public function_ `virtual bool HasCancel() const override`
- L237 _public function_ `virtual bool HasAccept() const override`
- L238 _public function_ `virtual bool CanAccept() const override`
- L241 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L242 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L244 _public prototype_ `virtual void RequestAction(EISMEditorToolActions ActionType);`
- L246 _public prototype_ `virtual void NotifySceneModified();`
- L254 _public member_ `TObjectPtr<USingleClickOrDragInputBehavior> ClickOrDragBehavior;` — `UPROPERTY()`
- L257 _public member_ `TObjectPtr<URectangleMarqueeMechanic> RectangleMarqueeMechanic;` — `UPROPERTY()`
- L260 _protected prototype_ `void OnMarqueeRectangleFinished(const FCameraRectangle& Rectangle, bool bCancelled);`
- L264 _protected member_ `TObjectPtr<UISMEditorToolProperties> TransformProps;` — `UPROPERTY()`
- L267 _protected member_ `TObjectPtr<UISMEditorToolActionPropertySet> ToolActions;` — `UPROPERTY()`
- L270 _protected member_ `TObjectPtr<UISMEditorToolReplacePropertySet> ReplaceAction;` — `UPROPERTY()`
- L273 _protected member_ `TArray<TObjectPtr<UInstancedStaticMeshComponent>> TargetComponents;` — `UPROPERTY()`
- L276 _protected member_ `TArray<FISMEditorTarget> ActiveGizmos;` — `UPROPERTY()`
- L279 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry;` — `UPROPERTY()`
- L283 _private member_ `TObjectPtr<UISMEditorToolExtractPropertySet> ExtractActions;` — `UPROPERTY()`
- L286 _private member_ `TObjectPtr<ULocalDoubleClickInputBehavior> DoubleClickBehavior;` — `UPROPERTY()`
- L289 _protected member_ `TSharedPtr<UE::Geometry::FMeshSceneAdapter> MeshScene;`
- L290 _protected member_ `TArray<UE::Geometry::FAxisAlignedBox3d> AllMeshBoundingBoxes;`
- L291 _protected member_ `bool bMeshSceneDirty = false;`
- L292 _protected prototype_ `void RebuildMeshScene();`
- L301 _protected member_ `TArray<FSelectedInstance> CurrentSelection;`
- L302 _protected prototype_ `void OnSelectionUpdated();`
- L303 _protected prototype_ `void UpdateSelectionInternal(const TArray<FSelectedInstance>& NewSelection, bool bEmitChange);`
- L304 _protected prototype_ `void UpdateSelectionFromUndoRedo(const TArray<FSelectedInstance>& NewSelection);`
- L306 _protected member_ `bool bInActiveDrag = false;`
- L307 _protected member_ `bool bShiftModifier = false;`
- L308 _protected member_ `bool bCtrlModifier = false;`
- L309 _protected prototype_ `void OnUpdateModifierState(int ModifierID, bool bIsOn);`
- L311 _protected member_ `EISMEditorTransformMode CurTransformMode;`
- L312 _protected prototype_ `void UpdateTransformMode(EISMEditorTransformMode NewMode);`
- L313 _protected prototype_ `void UpdateSetPivotModes(bool bEnableSetPivot);`
- L314 _protected prototype_ `void OnTransformCompleted();`
- L316 _protected prototype_ `void SetActiveGizmos_Single(bool bLocalRotations);`
- L317 _protected prototype_ `void SetActiveGizmos_PerObject();`
- L318 _protected prototype_ `void ResetActiveGizmos();`
- L320 _protected member_ `EISMEditorToolActions PendingAction = EISMEditorToolActions::NoAction;`
- L321 _protected prototype_ `virtual void OnClearSelection();`
- L322 _protected prototype_ `virtual void OnDeleteSelection();`
- L323 _protected prototype_ `virtual void OnDuplicateSelection();`
- L324 _protected prototype_ `virtual void OnReplaceSelection();`
- L326 _private prototype_ `void OnContractLastSelection();`
- L327 _private prototype_ `void OnExpandLastSelection();`
- L328 _private prototype_ `void OnExpandAllSelection();`
- L329 _private prototype_ `void OnDuplicateToNew();`
- L330 _private prototype_ `void OnExtractToNew();`
- L332 _private prototype_ `void ExpandSelectionBy(const FSelectedInstance& SelectedInstance, TArray<FSelectedInstance>& SelectionToModify);`
- L333 _private prototype_ `void ContractSelectionBy(const FSelectedInstance& SelectedInstance, TArray<FSelectedInstance>& SelectionToModify);`
- L334 _private prototype_ `void ToggleSelectionBy(const FSelectedInstance& SelectedInstance, TArray<FSelectedInstance>& SelectionToModify);`
- L335 _private prototype_ `void UpdateSelectionInternal(const TArray<FSelectedInstance>& NewSelection, bool bEmitChange, const FText& TransactionLabel);`
- L337 _private prototype_ `void DuplicateToNew(bool bDeleteFromCurrent);`
- L339 _private prototype_ `void OnDoubleClicked(const FInputDeviceRay& ClickPos);`
- L342 _private function_ `bool ShouldAddToSelection()` — Helpers that use the modifiers to determine what to do with selection
- L343 _private function_ `bool ShouldToggleSelection()`
- L344 _private function_ `bool ShouldSubtractSelection()`
- L345 _private function_ `bool ModifyingSelection()`
- L347 _protected prototype_ `void UpdatePreviewGeometry();`
- L350 _protected prototype_ `virtual void InternalNotifySceneModified(const TArray<UInstancedStaticMeshComponent*>& ComponentList, bool bAddToScene);`

#### struct `UISMEditorTool::FSelectedInstance`  
`struct FSelectedInstance`  
_L294-300_
- L296 _public member_ `UInstancedStaticMeshComponent* Component;`
- L297 _public member_ `int32 Index;`
- L298 _public member_ `UE::Geometry::FAxisAlignedBox3d WorldBounds;`
- L299 _public function_ `bool operator==(const FSelectedInstance& Other) const`

#### class `FISMEditorSelectionChange`  
`class FISMEditorSelectionChange : public FToolCommandChange`  
_L358-366_
- inherits: `FToolCommandChange`
- L361 _public member_ `TArray<UISMEditorTool::FSelectedInstance> OldSelection;`
- L362 _public member_ `TArray<UISMEditorTool::FSelectedInstance> NewSelection;`
- L363 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L364 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L365 _public prototype_ `virtual FString ToString() const override;`

#### class `FISMEditorSceneChange`  
`class FISMEditorSceneChange : public FToolCommandChange`  
_L370-378_
- inherits: `FToolCommandChange`
- L373 _public member_ `TArray<UInstancedStaticMeshComponent*> Components;`
- L374 _public member_ `bool bAdded;`
- L375 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L376 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L377 _public prototype_ `virtual FString ToString() const override;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`
- L28 _prototype_ `PREDECLARE_GEOMETRY(class FMeshSceneAdapter);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/MergeMeshesTool.h` (Public)


#### class `UMergeMeshesToolProperties`  
`class UMergeMeshesToolProperties : public UInteractiveToolPropertySet`  
_L20-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the Merge Meshes operation
- L27 _public member_ `int32 VoxelCount = 128;` — `UPROPERTY(EditAnywhere, Category = VoxelSettings, meta = (UIMin = "8", UIMax = "1024", ClampMin = "8", ClampMax = "1024"))` — The size of the geometry bounding box major axis measured in voxels.
- L31 _public member_ `float MeshAdaptivity = 0.001f;` — `UPROPERTY(EditAnywhere, Category = VoxelSettings, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Remeshing adaptivity, prior to optional simplification
- L35 _public member_ `float OffsetDistance = 0;` — `UPROPERTY()` — Offset when remeshing, note large offsets with high voxels counts will be slow.  Hidden because this duplicates functionality of the voxel offset tool
- L39 _public member_ `bool bAutoSimplify = false;` — `UPROPERTY(EditAnywhere, Category = VoxelSettings)` — Automatically simplify the result of voxel-based merge.

#### class `UMergeMeshesTool`  
`class UMergeMeshesTool : public UBaseVoxelTool`  
_L43-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseVoxelTool`
- L49 _public function_ `UMergeMeshesTool()`
- L53 _protected prototype_ `virtual void SetupProperties() override;`
- L54 _protected prototype_ `virtual void SaveProperties() override;`
- L56 _protected prototype_ `virtual FString GetCreatedAssetName() const override;`
- L57 _protected prototype_ `virtual FText GetActionName() const override;`
- L59 _protected prototype_ `virtual void ConvertInputsAndSetPreviewMaterials(bool bSetPreviewMesh) override;`
- L62 _protected prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L65 _protected member_ `TObjectPtr<UMergeMeshesToolProperties> MergeProps;` — `UPROPERTY()`

#### class `UMergeMeshesToolBuilder`  
`class UMergeMeshesToolBuilder : public UBaseCreateFromSelectedToolBuilder`  
_L73-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedToolBuilder`
- L79 _public function_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override`
- L84 _public function_ `virtual int32 MinComponentsSupported() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/MeshAttributePaintToolV2.h` (Public)


#### class `UMeshAttributePaintToolV2Builder`  
`class UMeshAttributePaintToolV2Builder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L24-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: Tool Builder
- L28 _private prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L29 _private prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UMeshAttributePaintToolV2Properties`  
`class UMeshAttributePaintToolV2Properties : public UInteractiveToolPropertySet`  
_L36-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L42 _public member_ `FString Attribute;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Selected Attribute", GetOptions = GetAttributeNames, NoResetToDefault))`
- L45 _public function_ `const TArray<FString>& GetAttributeNames()` — `UFUNCTION()`
- L47 _public member_ `TArray<FString> Attributes;`
- L54 _public prototype_ `void Initialize(const TArray<FName>& AttributeNames, bool bInitialize = false);` — Initialize the internal array of attribute names @param bInitialize if set, selected Attribute will be reset to the first attribute or empty if there are none.
- L59 _public prototype_ `int32 GetSelectedAttributeIndex();` — @return selected attribute index, or -1 if invalid selection

#### class `UMeshAttributePaintToolV2`  
`class UMeshAttributePaintToolV2 : public UMeshVertexAttributePaintToolBase`  
_L66-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexAttributePaintToolBase`
- desc: Editor tool to paint a vertex attribute as vertex colors
- L70 _public prototype_ `virtual bool SetupToolMesh(FDynamicMesh3& InOutToolMesh, int32& OutInitialAttributeIndex) override;`
- L71 _public prototype_ `virtual void CommitToolMesh(FDynamicMesh3& InToolMesh) override;`
- L74 _public prototype_ `virtual void Setup() override;`
- L75 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L78 _public member_ `TObjectPtr<UMeshAttributePaintToolV2Properties> AttribProps;` — `UPROPERTY()`
- L80 _public member_ `TValueWatcher<int32> SelectedAttributeWatcher;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/MeshModelingToolsEditorOnlyExp.h` (Public)


#### class `FMeshModelingToolsEditorOnlyExpModule`  
`class FMeshModelingToolsEditorOnlyExpModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/MeshTangentsTool.h` (Public)


#### class `UMeshTangentsToolBuilder`  
`class UMeshTangentsToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L33-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L38 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L39 _public prototype_ `virtual void InitializeNewTool(USingleSelectionMeshEditingTool* Tool, const FToolBuilderState& SceneState) const;`
- L40 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L43 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UMeshTangentsToolProperties`  
`class UMeshTangentsToolProperties : public UInteractiveToolPropertySet`  
_L49-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L56 _public member_ `EMeshTangentsType CalculationMethod = EMeshTangentsType::FastMikkTSpace;` — `UPROPERTY(EditAnywhere, Category = TangentsCalculation)` — Method used for calculating the tangents
- L60 _public member_ `bool bShowTangents = true;` — `UPROPERTY(EditAnywhere, Category = Display)` — Display the mesh tangents
- L64 _public member_ `bool bShowNormals = false;` — `UPROPERTY(EditAnywhere, Category = Display)` — Display the mesh normals
- L68 _public member_ `float LineLength = 2.0f;` — `UPROPERTY(EditAnywhere, Category = Display, meta = (UIMin = "0.01", UIMax = "25.0", ClampMin = "0.01", ClampMax = "10000000.0"))` — Length of lines used for displaying tangents and/or normals
- L72 _public member_ `float LineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Display, meta = (UIMin = "0", UIMax = "25.0", ClampMin = "0", ClampMax = "1000.0"))` — Thickness of lines used for displaying tangents and/or normals
- L76 _public member_ `bool bShowDegenerates = false;` — `UPROPERTY(EditAnywhere, Category = Display, AdvancedDisplay)` — Display tangents and/or normals for degenerate triangles
- L82 _public member_ `bool bCompareWithMikkt = false;` — `UPROPERTY(EditAnywhere, Category = Display, AdvancedDisplay, meta = (DisplayName = "Compare with MikkT", EditCondition = "CalculationMethod == EMeshTangentsType::FastMikkTSpace"))` — Display difference between FastMikkTSpace tangents and MikkTSpace tangents. This is only available if the FastMikkTSpace Calculation Method is selected.
- L88 _public member_ `float CompareWithMikktThreshold = 5.0f;` — `UPROPERTY(EditAnywhere, Category = Display, AdvancedDisplay, meta = (DisplayName = "Compare Threshold", UIMin = "0.5", UIMax = "90.0", EditCondition = "CalculationMethod == EMeshTangentsType::FastMikkTSpace && bCompareWithMikkt"))` — Minimum angle difference in degrees for a FastMikkTSpace tangent to be considered different to a MikkTSpace tangent. This is only available if a Compare with MikkT is enabled and the FastMikkTSpace Calculation Method is selected.

#### class `UMeshTangentsTool`  
`class UMeshTangentsTool : public USingleSelectionMeshEditingTool, public UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshTangentsd>, public IInteractiveToolManageGeometrySelectionAPI`  
_L100-196_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshTangentsd>,IInteractiveToolManageGeometrySelectionAPI`
- desc: Simple Mesh Simplifying Tool
- L104 _public prototype_ `UMeshTangentsTool();`
- L106 _public prototype_ `virtual void Setup() override;`
- L107 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L109 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L110 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L112 _public function_ `virtual bool HasCancel() const override`
- L113 _public function_ `virtual bool HasAccept() const override`
- L114 _public prototype_ `virtual bool CanAccept() const override;`
- L117 _public prototype_ `void SetGeometrySelection(UE::Geometry::FGeometrySelection&& SelectionIn);` — input selection support
- L120 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L126 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<UE::Geometry::FMeshTangentsd>> MakeNewOperator() override;` — IGenericDataOperatorFactory API
- L130 _protected member_ `TObjectPtr<UMeshTangentsToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L133 _protected member_ `TObjectPtr<UMeshUVChannelProperties> UVChannelProperties = nullptr;` — `UPROPERTY()`
- L136 _protected member_ `TObjectPtr<UMaterialInterface> DefaultMaterial = nullptr;` — `UPROPERTY()`
- L139 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh = nullptr;` — `UPROPERTY()`
- L142 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry = nullptr;` — `UPROPERTY()`
- L144 _protected member_ `TUniquePtr<TGenericDataBackgroundCompute<UE::Geometry::FMeshTangentsd>> Compute = nullptr;`
- L146 _protected member_ `TSharedPtr<FMeshDescription, ESPMode::ThreadSafe> InputMeshDescription;`
- L147 _protected member_ `TSharedPtr<UE::Geometry::FMeshTangentsf, ESPMode::ThreadSafe> InitialTangents;`
- L148 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L150 _protected member_ `bool bThicknessDirty = false;`
- L151 _protected member_ `bool bLengthDirty = false;`
- L152 _protected member_ `bool bVisibilityChanged = false;`
- L154 _protected prototype_ `void OnTangentsUpdated(const TUniquePtr<UE::Geometry::FMeshTangentsd>& NewResult);`
- L155 _protected prototype_ `void CopyToOverlays(const UE::Geometry::FMeshTangentsd& Tangents, FDynamicMesh3& Mesh);`
- L156 _protected prototype_ `void UpdateVisualization(bool bThicknessChanged, bool bLengthChanged);`
- L157 _protected prototype_ `TSet<int32> ComputeDegenerateTris() const;`
- L158 _protected prototype_ `void ComputeMikkTDeviations(const TSet<int32>& DegenerateTris);`
- L169 _protected member_ `TArray<FMikktDeviation> Deviations;`
- L176 _protected member_ `TObjectPtr<UGeometrySelectionVisualizationProperties> GeometrySelectionVizProperties = nullptr;` — `UPROPERTY()`
- L179 _protected member_ `TObjectPtr<UPreviewGeometry> GeometrySelectionViz = nullptr;` — `UPROPERTY()`
- L183 _protected member_ `UE::Geometry::FGeometrySelection InputGeometrySelection;` — The geometry selection that the user started the tool with. If the selection is empty we operate on the whole mesh, otherwise only edit the overlay elements implied by the selection.
- L187 _protected member_ `UE::Geometry::FGeometrySelection TriangleVertexGeometrySelection;` — If the user starts the tool with an edge selection we convert it to a vertex selection with triangle topology and store it here, we do this since we expect users to want vertex and edge selections to behave similarly.
- L191 _protected member_ `TSet<int> EditTriangles;` — These are indices into InputMesh. If both are non-empty we edit the corresponding elements in the overlay, otherwise operate on the whole overlay
- L192 _protected member_ `TSet<int> EditVertices;`
- L195 _private member_ `bool bHasDisplayedNoAttributeError = false;`

#### struct `UMeshTangentsTool::FMikktDeviation`  
`struct FMikktDeviation`  
_L160-168_
- L162 _public member_ `float MaxAngleDeg;`
- L163 _public member_ `int32 TriangleID;`
- L164 _public member_ `int32 TriVertIndex;`
- L165 _public member_ `FVector3f VertexPos;`
- L166 _public member_ `FVector3f MikktTangent, MikktBitangent;`
- L166 _public member_ `FVector3f MikktTangent, MikktBitangent;`
- L167 _public member_ `FVector3f OtherTangent, OtherBitangent;`
- L167 _public member_ `FVector3f OtherTangent, OtherBitangent;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/MeshToVolumeTool.h` (Public)


#### class `UMeshToVolumeToolBuilder`  
`class UMeshToVolumeToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L27-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L31 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState & SceneState) const override;`
- L32 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState & SceneState) const override;`

#### enum `EMeshToVolumeMode`  
`enum class EMeshToVolumeMode`  
_L39-45_
- reflection: `UENUM()`
- L42 _public enumerator_ `TriangulatePolygons` — Create a separate Volume Face for each Triangle
- L44 _public enumerator_ `MinimalPolygons` — Create Volume Faces based on Planar Polygons

#### class `UMeshToVolumeToolProperties`  
`class UMeshToVolumeToolProperties : public UInteractiveToolPropertySet`  
_L50-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L57 _public member_ `EMeshToVolumeMode ConversionMode = EMeshToVolumeMode::MinimalPolygons;` — `UPROPERTY(EditAnywhere, Category = ConversionOptions)` — Method for converting the input mesh to a set of Planar Polygonal Faces in the output Volume.
- L64 _public member_ `bool bPreserveGroupBoundaries = false;` — `UPROPERTY(EditAnywhere, Category = ConversionOptions, meta = (EditCondition = "ConversionMode != EMeshToVolumeMode::TriangulatePolygons"))` — When true, adjacent coplanar groups will not be merged together into single faces. Not relevant if conversion mode is set to emit all triangles separately.
- L70 _public member_ `bool bAutoSimplify = true;` — `UPROPERTY(EditAnywhere, Category = ConversionOptions, AdvancedDisplay)` — Determines whether mesh gets auto simplified when its triangle count is too high.
- L76 _public member_ `int32 SimplifyMaxTriangles = 250;` — `UPROPERTY(EditAnywhere, Category = ConversionOptions, AdvancedDisplay, meta = (EditCondition = "bAutoSimplify"))` — Target triangle count for auto simplification when Auto Simplify is true.
- L80 _public member_ `TSubclassOf<class AVolume> NewVolumeType = ABlockingVolume::StaticClass();` — `UPROPERTY(EditAnywhere, Category = NewVolume, meta = (EditCondition = "TargetVolume == nullptr"))` — Type of new Volume to create on Accept
- L84 _public member_ `TSoftObjectPtr<AVolume> TargetVolume;` — `UPROPERTY(EditAnywhere, Category = UpdateExisting)` — If set, the target Volume will be updated, rather than creating a new Volume.

#### class `UMeshToVolumeTool`  
`class UMeshToVolumeTool : public USingleSelectionMeshEditingTool, public UE::Geometry::IGenericDataOperatorFactory<FDynamicMeshFaceArray>`  
_L98-138_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,UE::Geometry::IGenericDataOperatorFactory<FDynamicMeshFaceArray>`
- desc: Converts a mesh to a volume. Note: If ConversionUtils/DynamicMeshToVolume is rewritten to be safe for runtime, this tool can be moved out of the editor-only section and put with VolumeToMeshTool.
- L103 _public prototype_ `UMeshToVolumeTool();`
- L105 _public prototype_ `virtual void Setup() override;`
- L106 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L108 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L109 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L111 _public function_ `virtual bool HasCancel() const override`
- L112 _public function_ `virtual bool HasAccept() const override`
- L113 _public prototype_ `virtual bool CanAccept() const override;`
- L116 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<FDynamicMeshFaceArray>> MakeNewOperator() override;` — IGenericDataOperatorFactory API
- L120 _protected member_ `TObjectPtr<UMeshToVolumeToolProperties> Settings;` — `UPROPERTY()`
- L123 _protected member_ `TObjectPtr<UOnAcceptHandleSourcesPropertiesSingle> HandleSourcesProperties;` — `UPROPERTY()`
- L126 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L129 _protected member_ `TObjectPtr<ULineSetComponent> VolumeEdgesSet;` — `UPROPERTY()`
- L132 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L134 _protected member_ `TUniquePtr<TGenericDataBackgroundCompute<FDynamicMeshFaceArray>> Compute = nullptr;`
- L136 _protected prototype_ `void UpdateLineSet(FDynamicMeshFaceArray& Faces);`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`
- L89 _typedef_ `using FDynamicMeshFaceArray = TArray<UE::Conversion::FDynamicMeshFace>;`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/MeshVertexAttributePaintToolBase.h` (Public)


#### enum `UE::MeshVertexAttributePaintToolBase::Private::EStampAccumulatorMode`  
`enum class EStampAccumulatorMode : uint8`  
_L53-57_
- desc: Selects how a transaction's stamps commit: GatedByMaxFalloff — each vertex gets at most one stamp's effect (max-falloff wins). Reads from the pre-transaction snapshot. Accumulate        — stamps compound
- L55 _public enumerator_ `GatedByMaxFalloff`
- L56 _public enumerator_ `Accumulate`

#### enum `EMeshVertexAttributePaintToolEditMode`  
`enum class EMeshVertexAttributePaintToolEditMode : uint8`  
_L66-70_
- reflection: `UENUM()`
- L68 _public enumerator_ `Brush`
- L69 _public enumerator_ `Mesh`

#### enum `EMeshVertexAttributePaintToolEditOperation`  
`enum class EMeshVertexAttributePaintToolEditOperation : uint8`  
_L73-80_
- reflection: `UENUM()`
- L75 _public enumerator_ `Add`
- L76 _public enumerator_ `Replace`
- L77 _public enumerator_ `Multiply`
- L78 _public enumerator_ `Invert`
- L79 _public enumerator_ `Relax`

#### enum `EMeshVertexAttributePaintToolVisibilityType`  
`enum class EMeshVertexAttributePaintToolVisibilityType : uint8`  
_L83-87_
- reflection: `UENUM()`
- L85 _public enumerator_ `None`
- L86 _public enumerator_ `Unoccluded`

#### enum `EMeshVertexAttributePaintToolValueQueryType`  
`enum class EMeshVertexAttributePaintToolValueQueryType : uint8`  
_L91-101_
- reflection: `UENUM()`
- desc: Value Query mode
- L94 _public enumerator_ `Interpolated UMETA(DisplayName = "Interpolated")` — Value is interpolated from triangle vertices
- L97 _public enumerator_ `NearestVertexFast UMETA(DisplayName = "Nearest Vertex (Fast)")` — Return the value at the closest vertex of the triangle under the mouse cursor
- L100 _public enumerator_ `NearestVertexAccurate UMETA(DisplayName = "Nearest Vertex (Accurate)")` — Return the value of the nearest vertex inside the brush radius, even if the vertex is not on the triangle under the mouse cursor

#### enum `EMeshVertexAttributePaintToolColorMode`  
`enum class EMeshVertexAttributePaintToolColorMode : uint8`  
_L104-109_
- reflection: `UENUM()`
- L106 _public enumerator_ `Greyscale`
- L107 _public enumerator_ `Ramp`
- L108 _public enumerator_ `FullMaterial`

#### enum `EMeshVertexAttributePaintToolMirrorDirection`  
`enum class EMeshVertexAttributePaintToolMirrorDirection : uint8`  
_L113-117_
- reflection: `UENUM()`
- desc: mirror direction mode
- L115 _public enumerator_ `PositiveToNegative`
- L116 _public enumerator_ `NegativeToPositive`

#### struct `FMeshVertexAttributePaintToolBrushProperties`  
`struct FMeshVertexAttributePaintToolBrushProperties`  
_L129-167_
- reflection: `USTRUCT()`
- L134 _public member_ `EMeshVertexAttributePaintToolEditOperation BrushMode = EMeshVertexAttributePaintToolEditOperation::Replace;` — `UPROPERTY()`
- L138 _public member_ `float AttributeValue = 1.0;` — `UPROPERTY()` — Value to paint on the mesh (dependent on the BrushMode)
- L142 _public member_ `EMeshVertexPaintBrushAreaType BrushAreaMode = EMeshVertexPaintBrushAreaType::Connected;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (DisplayName = "Brush Area Mode"))` — Area Mode specifies the shape of the brush and which triangles will be included relative to the cursor
- L146 _public member_ `float AngleThreshold = 180.0f;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "180.0", ClampMax = "180.0"))` — The Region affected by the current operation will be bounded by edge angles larger than this threshold
- L150 _public member_ `bool bUVSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters)` — The Region affected by the current operation will be bounded by UV borders/seams
- L154 _public member_ `bool bNormalSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters)` — The Region affected by the current operation will be bounded by Hard Normal edges/seams
- L158 _public member_ `EMeshVertexAttributePaintToolVisibilityType VisibilityFilter = EMeshVertexAttributePaintToolVisibilityType::None;` — `UPROPERTY(EditAnywhere, Category = Filters)` — Control which triangles can be affected by the current operation based on visibility. Applied after all other filters.
- L162 _public member_ `double ValueAtBrush = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Query, meta = (NoResetToDefault))` — The weight value at the brush indicator
- L166 _public member_ `EMeshVertexAttributePaintToolValueQueryType ValueQueryType = EMeshVertexAttributePaintToolValueQueryType::NearestVertexFast;` — `UPROPERTY(EditAnywhere, Category = Filters)` — method used for querying the value at brush

#### struct `FMeshVertexAttributePaintToolBrushConfig`  
`struct FMeshVertexAttributePaintToolBrushConfig`  
_L170-185_
- reflection: `USTRUCT()`
- L177 _public member_ `float BrushSize = 0.25f;` — `UPROPERTY(Config)` — Adaptive size of brush - Relative to the model size
- L181 _public member_ `float Value = 1.0;` — `UPROPERTY(Config)` — Value to paint on the mesh (dependent on the BrushMode)
- L184 _public member_ `float Falloff = 0.0;` — `UPROPERTY(Config)`

#### struct `FMeshVertexAttributePaintToolRelaxBrushAdvancedConfig`  
`struct FMeshVertexAttributePaintToolRelaxBrushAdvancedConfig`  
_L190-196_
- reflection: `USTRUCT()`
- L195 _public member_ `bool bAccumulate = true;` — `UPROPERTY(Config)`

#### struct `FMeshVertexAttributePaintToolGradientProperties`  
`struct FMeshVertexAttributePaintToolGradientProperties`  
_L201-213_
- reflection: `USTRUCT()`
- L208 _public member_ `double GradientHighValue = 1.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))` — The Gradient upper limit value
- L212 _public member_ `double GradientLowValue = 0.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))` — The Gradient lower limit value

#### struct `FMeshVertexAttributePaintToolSelectionProperties`  
`struct FMeshVertexAttributePaintToolSelectionProperties`  
_L218-225_
- reflection: `USTRUCT()`
- L224 _public member_ `EComponentSelectionMode ComponentSelectionMode = EComponentSelectionMode::Vertices;` — `UPROPERTY()` — Mesh selection mode (vertex, edge face)

#### struct `FMeshVertexAttributePaintToolDisplayProperties`  
`struct FMeshVertexAttributePaintToolDisplayProperties`  
_L230-320_
- reflection: `USTRUCT()`
- L236 _public member_ `EMeshVertexAttributePaintToolColorMode ColorMode = EMeshVertexAttributePaintToolColorMode::Greyscale;` — `UPROPERTY()` — Vertex color display mode (Greyscale, Ramp, ... )
- L240 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY()` — Color ramp to use when the color mode is set to "Ramp"
- L243 _public member_ `TArray<FLinearColorRamp> ColorRampPresets;` — `UPROPERTY()`
- L246 _public member_ `FLinearColorRamp GreyScaleColorRamp;` — Used by UI customization
- L247 _public member_ `FLinearColorRamp WhiteColorRamp;`
- L250 _public member_ `bool bShowValues = false;` — `UPROPERTY()`
- L253 _public member_ `bool bShowValuesOnlySelected = false;` — `UPROPERTY()`
- L256 _public member_ `float MinValue = 0;` — `UPROPERTY()`
- L259 _public member_ `float MaxValue = 100;` — `UPROPERTY()`
- L263 _public member_ `bool bShowBorders = true;` — `UPROPERTY()` — Should mesh boundary edges be shown
- L267 _public member_ `bool bShowUVSeams = true;` — `UPROPERTY()` — Should mesh uv seam edges be shown
- L271 _public member_ `bool bShowNormalSeams = false;` — `UPROPERTY()` — Should mesh normal seam edges be shown
- L275 _public member_ `bool bShowTangentSeams = true;` — `UPROPERTY()` — Should mesh tangent seam edges be shown
- L279 _public member_ `bool bShowColorSeams = true;` — `UPROPERTY()` — Should mesh color seam edges be shown
- L283 _public member_ `float ThicknessScale = 0.5f;` — `UPROPERTY()` — Multiplier on edge thicknesses
- L287 _public member_ `FColor WireframeColor = FColor(128, 128, 128);` — `UPROPERTY()` — Color of mesh wireframe
- L291 _public member_ `FColor BoundaryEdgeColor = FColor(164, 73, 164);` — `UPROPERTY()` — Color of mesh boundary edges
- L295 _public member_ `FColor UVSeamColor = FColor(240, 160, 15);` — `UPROPERTY()` — Color of mesh UV seam edges
- L299 _public member_ `FColor NormalSeamColor = FColor(128, 128, 240);` — `UPROPERTY()` — Color of mesh normal seam edges
- L303 _public member_ `FColor TangentSeamColor = FColor(64, 240, 240);` — `UPROPERTY()` — Color of mesh tangent seam edges
- L307 _public member_ `FColor ColorSeamColor = FColor(46, 204, 113);` — `UPROPERTY()` — Color of mesh color seam edges
- L311 _public member_ `bool bShowGroupBoundaries = true;` — `UPROPERTY()` — Show polygroup boundary edges
- L315 _public member_ `FColor GroupBoundaryColor = FColor(220, 100, 220);` — `UPROPERTY()` — Color of polygroup boundary edges
- L319 _public member_ `float DepthBias = 0.2f;` — `UPROPERTY()` — Depth bias used to slightly shift depth of lines

#### struct `FMeshVertexAttributePaintToolMirrorProperties`  
`struct FMeshVertexAttributePaintToolMirrorProperties`  
_L325-350_
- reflection: `USTRUCT()`
- L331 _public member_ `bool bEnableBrushMirroring = false;` — `UPROPERTY()` — whether the mirror is enabled in brush mode
- L335 _public member_ `bool bMirrorPlaneWidgetVisible = true;` — `UPROPERTY()` — whether the mirror plane is visible or not
- L339 _public member_ `bool bObjectSpace = true;` — `UPROPERTY()` — if true, the mirror planes will be centered on the bounds of the object
- L343 _public member_ `bool bHideOnBrushStroke = false;` — `UPROPERTY()` — if true, the mirror planes will be hidden when actively painting
- L346 _public member_ `TEnumAsByte<EAxis::Type> MirrorAxis = EAxis::X;` — `UPROPERTY()`
- L349 _public member_ `EMeshVertexAttributePaintToolMirrorDirection MirrorDirection = EMeshVertexAttributePaintToolMirrorDirection::PositiveToNegative;` — `UPROPERTY()`

#### class `UMeshVertexAttributePaintToolProperties`  
`class UMeshVertexAttributePaintToolProperties : public UInteractiveToolPropertySet`  
_L355-433_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings)`
- inherits: `UInteractiveToolPropertySet`
- L359 _private prototype_ `UMeshVertexAttributePaintToolProperties();`
- L365 _public member_ `EMeshVertexAttributePaintToolEditMode EditingMode = EMeshVertexAttributePaintToolEditMode::Brush;` — `UPROPERTY()` — Edit mode (brush,mesh...)
- L368 _public member_ `FMeshVertexAttributePaintToolBrushProperties BrushProperties;` — `UPROPERTY(config)`
- L371 _public member_ `FMeshVertexAttributePaintToolGradientProperties GradientProperties;` — `UPROPERTY()`
- L374 _public member_ `FMeshVertexAttributePaintToolSelectionProperties SelectionProperties;` — `UPROPERTY()`
- L377 _public member_ `FMeshVertexAttributePaintToolDisplayProperties DisplayProperties;` — `UPROPERTY(config)`
- L380 _public member_ `FMeshVertexAttributePaintToolMirrorProperties MirrorProperties;` — `UPROPERTY(config)`
- L382 _public prototype_ `const FMeshVertexAttributePaintToolBrushConfig& GetBrushConfig(EMeshVertexAttributePaintToolEditOperation BrushMode) const;`
- L383 _public prototype_ `void SetBrushConfig(EMeshVertexAttributePaintToolEditOperation BrushMode, const FMeshVertexAttributePaintToolBrushConfig& BrushConfig);`
- L391 _public member_ `bool bSyncBrushRadiusAcrossModes = true;` — `UPROPERTY(config)` — When true (default), the brush radius is shared across all brush modes — every per-mode SetBrushRadius / SaveBrushConfig propagates the new size to every BrushConfig* via SetSharedBrushSize. When false, each mode remembers its own radius and a mode switch (via LoadBrushConfig) pulls that mode's saved size. The UI toggle next to the radius slider drives this and snap-canonicalises all configs to the current size on re-enable.
- L393 _public function_ `void SetSharedBrushSize(float NewBrushSize)`
- L402 _public member_ `FMeshVertexAttributePaintToolBrushConfig BrushConfigAdd;` — `UPROPERTY(config)`
- L405 _public member_ `FMeshVertexAttributePaintToolBrushConfig BrushConfigReplace;` — `UPROPERTY(config)`
- L408 _public member_ `FMeshVertexAttributePaintToolBrushConfig BrushConfigMultiply;` — `UPROPERTY(config)`
- L411 _public member_ `FMeshVertexAttributePaintToolBrushConfig BrushConfigRelax;` — `UPROPERTY(config)`
- L414 _public member_ `FMeshVertexAttributePaintToolRelaxBrushAdvancedConfig RelaxBrushAdvancedConfig;` — `UPROPERTY(config)`
- L417 _public member_ `float SelectionAddStrength = 1.0f;` — `UPROPERTY(config)`
- L420 _public member_ `float SelectionReplaceValue = 1.0f;` — `UPROPERTY(config)`
- L423 _public member_ `float SelectionRelaxStrength = 0.5f;` — `UPROPERTY(config)`
- L426 _public member_ `float SelectionPruneThreshold = 0.01f;` — `UPROPERTY(config)`
- L428 _public prototype_ `void ResetColorRamp();`
- L431 _private prototype_ `void CreateDefaultColorRamp();`

#### class `FMeshVertexAttributePaintToolData`  
`class FMeshVertexAttributePaintToolData`  
_L437-482_
- L440 _public prototype_ `void Setup(UDynamicMesh* InToolDynamicMesh, int32 InInitialAttributeIndex);`
- L441 _public prototype_ `bool SetAttributeToEdit(int32 InNewAttributeIndex);`
- L444 _public prototype_ `void BeginChange();`
- L445 _public prototype_ `TUniquePtr<UE::MeshVertexAttributePaintToolBase::Private::FMeshChange> EndChange();`
- L446 _public prototype_ `void CancelChange();`
- L448 _public prototype_ `bool IsValid() const;`
- L450 _public prototype_ `float GetValue(int32 VertexIdx) const;`
- L451 _public prototype_ `float GetAverageValue(const TArray<int32>& Vertices) const;`
- L453 _public prototype_ `void SetValue(int32 VertexIdx, float Value);`
- L458 _public prototype_ `void SnapshotAllValues(TArray<float>& OutSnapshot) const;` — Bulk-read every vertex's current value into OutSnapshot, sized to MaxVertexID. Holes (invalid vertex IDs) are written as 0. Performed in a single ProcessMesh call so the cost is one mesh lock plus one linear pass over the weight layer.
- L464 _public prototype_ `void SyncPreChangeWeightsToCurrentWeights();` — Sync PreChangeWeights to the current mesh attribute values (the "current weights"). Called at every transaction boundary (EndChange/CancelChange/AfterModify) and at attribute swap so the next transaction's stamps read against a baseline matching the current mesh state.
- L469 _public prototype_ `float GetPreChangeValue(int32 VertexIdx) const;` — Stable baseline for gated-mode stamp reads. Frozen across an entire transaction so multi-call sequences (e.g. slider drag) read the same pre-transaction value for a given vertex. Returns 0 if invalid or vertex index is out of range.
- L471 _public function_ `int32 GetNumVerts() const`
- L475 _private member_ `TUniquePtr<UE::Geometry::FDynamicMeshChangeTracker> ActiveWeightEditChangeTracker;`
- L477 _private member_ `TWeakObjectPtr<UDynamicMesh> ToolDynamicMesh;`
- L479 _private member_ `int32 AttributeIndex = INDEX_NONE;`
- L481 _private member_ `TArray<float> PreChangeWeights;`

#### class `UMeshVertexAttributePaintToolBase`  
`class UMeshVertexAttributePaintToolBase : public UMeshSculptToolBase`  
_L490-788_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptToolBase`
- desc: Editor tool to paint a vertex attribute as vertex colors
- L494 _public prototype_ `UMeshVertexAttributePaintToolBase();`
- L495 _public prototype_ `virtual ~UMeshVertexAttributePaintToolBase();`
- L498 _protected prototype_ `virtual bool SetupToolMesh(FDynamicMesh3& InOutToolMesh, int32& OutInitialAttributeIndex);`
- L499 _protected prototype_ `virtual void CommitToolMesh(FDynamicMesh3& InToolMesh);`
- L500 _protected prototype_ `virtual void UpdatePreview(const TSet<int32>* TrianglesToUpdate = nullptr, const TArray<int32>* VerticesToUpdate = nullptr);`
- L502 _protected prototype_ `bool SetAttributeToPaint(int32 InNewAttributeIndex);`
- L503 _protected prototype_ `void RebuildOctree();`
- L506 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L508 _public prototype_ `virtual void Setup() override;`
- L509 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L510 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L511 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L512 _public prototype_ `virtual void UpdateMaterialMode(EMeshEditingMaterialModes MaterialMode) override;`
- L513 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L515 _public function_ `virtual bool HasCancel() const override`
- L516 _public function_ `virtual bool HasAccept() const override`
- L517 _public prototype_ `virtual bool CanAccept() const override;`
- L519 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& Ray) override;`
- L520 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L522 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L524 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;`
- L526 _public prototype_ `void SetEditingMode(EMeshVertexAttributePaintToolEditMode Editmode);`
- L527 _public prototype_ `EMeshVertexAttributePaintToolEditMode GetEditingMode() const;`
- L529 _public prototype_ `void SetBrushMode(EMeshVertexAttributePaintToolEditOperation BrushMode);`
- L530 _public prototype_ `bool IsInBrushMode() const;`
- L532 _public prototype_ `void SetBrushAreaMode(EMeshVertexPaintBrushAreaType BrushAreaMode);`
- L533 _public prototype_ `bool IsVolumetricBrush() const;`
- L535 _public prototype_ `virtual void SetupBrushEditBehaviorSetup(ULocalTwoAxisPropertyEditInputBehavior& OutBehavior) override;`
- L540 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L545 _public member_ `TObjectPtr<UMeshVertexAttributePaintToolProperties> ToolProperties;` — `UPROPERTY()` — properties of the tool
- L548 _public member_ `TObjectPtr<UMeshVertexAttributePaintToolPaintBrushOpProps> PaintBrushOpProperties;` — `UPROPERTY()`
- L551 _public member_ `TObjectPtr<UMeshVertexAttributePaintToolSmoothBrushOpProps> SmoothBrushOpProperties;` — `UPROPERTY()`
- L553 _public prototype_ `bool HaveVisibilityFilter() const;`
- L554 _public prototype_ `void ApplyVisibilityFilter(const TArray<int32>& Vertices, TArray<int32>& VisibleVertices);`
- L555 _public prototype_ `void ApplyVisibilityFilter(TSet<int32>& Triangles, TArray<int32>& ROIBuffer, TArray<int32>& OutputBuffer);`
- L558 _public prototype_ `float GetBrushAdaptiveSize() const;`
- L559 _public prototype_ `float GetBrushMinRadius() const;`
- L560 _public prototype_ `float GetBrushMaxRadius() const;`
- L561 _public prototype_ `void SetBrushRadius(float NewRadius);`
- L562 _public prototype_ `void SetBrushAdaptiveSize(float AdaptiveSize);`
- L564 _public prototype_ `float GetBrushFalloff() const;`
- L565 _public prototype_ `void SetBrushFalloff(float NewFalloff);`
- L567 _public prototype_ `void SetColorMode(EMeshVertexAttributePaintToolColorMode NewColorMode);`
- L569 _public prototype_ `bool HasSelection() const;`
- L570 _public prototype_ `void GrowSelection() const;`
- L571 _public prototype_ `void ShrinkSelection() const;`
- L572 _public prototype_ `void InvertSelection() const;`
- L573 _public prototype_ `void FloodSelection() const;`
- L574 _public prototype_ `void SelectBorder() const;`
- L575 _public prototype_ `void SetComponentSelectionMode(EComponentSelectionMode NewMode);`
- L577 _public prototype_ `void CopyAverageFromSelectionToClipboard();`
- L578 _public prototype_ `void PasteValueToSelectionFromClipboard();`
- L579 _public prototype_ `void PruneSelection(float Threshold);`
- L582 _public prototype_ `void ApplyValueToSelection(EMeshVertexAttributePaintToolEditOperation Operation, float InValue, bool bWithTransaction = true);` — selection operations
- L583 _public prototype_ `void MirrorValues();`
- L585 _public prototype_ `const TArray<int32>& GetSelectedVertices() const;`
- L587 _public prototype_ `virtual void SetFocusInViewport() const;`
- L590 _public member_ `static FInputChord GreyscaleDisplayInputChord;`
- L591 _public member_ `static FInputChord ColorMapDisplayInputChord;`
- L592 _public member_ `static FInputChord MaterialColorDisplayInputChord;`
- L594 _public member_ `static FInputChord VerticesSelectionModeInputChord;`
- L595 _public member_ `static FInputChord EdgesSelectionModeInputChord;`
- L596 _public member_ `static FInputChord FacesSelectionModeInputChord;`
- L598 _public member_ `static FInputChord GrowSelectionInputChord;`
- L599 _public member_ `static FInputChord ShrinkSelectionInputChord;`
- L600 _public member_ `static FInputChord FloodSelectionInputChord;`
- L602 _public member_ `static FInputChord InvertMirrorDirectionInputChord;`
- L603 _public member_ `static FInputChord MirrorValuesInputChord;`
- L605 _public member_ `static FInputChord CopyAverageValueInputChord;`
- L606 _public member_ `static FInputChord PasteAverageValueInputChord;`
- L608 _public member_ `static FInputChord ToggleValuePickerInputChord;`
- L612 _protected member_ `TObjectPtr<UDynamicMesh> ToolDynamicMesh;` — `UPROPERTY()`
- L615 _protected prototype_ `virtual UBaseDynamicMeshComponent* GetSculptMeshComponent() override;` — UMeshSculptToolBase API
- L616 _protected function_ `virtual FDynamicMesh3* GetBaseMesh() override`
- L617 _protected function_ `virtual const FDynamicMesh3* GetBaseMesh() const override`
- L619 _protected prototype_ `virtual int32 FindHitSculptMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L620 _protected prototype_ `virtual int32 FindHitTargetMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L621 _protected prototype_ `virtual void UpdateHitSculptMeshTriangle(int32 TriangleID, const FRay3d& LocalRay) override;`
- L623 _protected prototype_ `virtual void OnBeginStroke(const FRay& WorldRay) override;`
- L624 _protected prototype_ `virtual void OnEndStroke() override;`
- L625 _protected prototype_ `virtual void OnCancelStroke() override;`
- L627 _protected prototype_ `void OnColorRampChanged(TArray<FRichCurve*> Curves);`
- L629 _protected prototype_ `void SaveBrushConfig(EMeshVertexAttributePaintToolEditOperation BrushMode);`
- L630 _protected prototype_ `void LoadBrushConfig(EMeshVertexAttributePaintToolEditOperation BrushMode);`
- L632 _protected function_ `virtual bool SharesBrushPropertiesChanges() const override`
- L633 _protected prototype_ `virtual void InitializeIndicator() override;`
- L636 _protected prototype_ `void EnableValuePicker(bool bEnable);`
- L637 _protected prototype_ `bool IsValuePickerEnabled() const;`
- L639 _protected prototype_ `void EnableBrushMirroring(bool bEnable);`
- L640 _protected prototype_ `bool IsBrushMirroringEnabled() const;`
- L642 _protected prototype_ `void SetMirrorPlaneWidgetVisible(bool bVisible);`
- L643 _protected prototype_ `bool IsMirrorPlaneWidgetVisible();`
- L645 _protected prototype_ `bool IsBrushMirroringInObjectSpace() const;`
- L647 _protected prototype_ `void SetMirrorAxis(EAxis::Type InAxis);`
- L648 _protected prototype_ `EAxis::Type GetMirrorAxis() const;`
- L650 _protected prototype_ `void InitializeMirrorIndicator();`
- L651 _protected prototype_ `void UpdateMirrorIndicator();`
- L652 _protected prototype_ `void UpdateMirrorPlaneMesh();`
- L653 _protected prototype_ `UE::Geometry::FFrame3d ComputeMirroredFrame(const UE::Geometry::FFrame3d& InLocalSpaceFrame) const;`
- L654 _protected prototype_ `void OnMirrorCommand();`
- L656 _protected prototype_ `void SetMeshSelectionTool(EMeshSelectorTool SelectorTool);`
- L657 _protected prototype_ `EMeshSelectorTool GetMeshSelectionTool() const;`
- L664 _protected member_ `FToolDataVisualizer GradientSelectionRenderer;` — Gradient Support
- L666 _protected member_ `UE::Geometry::FGroupTopologySelection LowValueGradientVertexSelection;`
- L667 _protected member_ `UE::Geometry::FGroupTopologySelection HighValueGradientVertexSelection;`
- L669 _protected prototype_ `void OnSelectionModified();`
- L678 _protected member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay = nullptr;` — `UPROPERTY()`
- L681 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh = nullptr;` — `UPROPERTY()`
- L682 _protected member_ `UE::Geometry::FAxisAlignedBox3d MeshLocalBounds;`
- L685 _protected member_ `TObjectPtr<UToolMeshSelector> MeshSelector = nullptr;` — `UPROPERTY()`
- L688 _protected member_ `TObjectPtr<UBrushStampIndicator> MirrorBrushIndicator = nullptr;` — `UPROPERTY()`
- L691 _protected member_ `TObjectPtr<UPreviewMesh> MirrorBrushIndicatorMesh = nullptr;` — `UPROPERTY()`
- L694 _protected member_ `TObjectPtr<UPreviewMesh> MirrorPlaneMesh = nullptr;` — `UPROPERTY()`
- L696 _protected member_ `FSculptBrushStamp MirrorCurrentStamp;`
- L697 _protected member_ `int32 MirrorBrushTriangleID = INDEX_NONE;`
- L699 _protected prototype_ `float GetCurrentWeightValueUnderBrush() const;`
- L700 _protected member_ `FVector3d CurrentBaryCentricCoords;`
- L701 _protected prototype_ `int32 GetBrushNearestVertex() const;`
- L702 _protected prototype_ `int32 GetBrushNearestVertexAccurate() const;`
- L703 _protected prototype_ `float GetAverageWeightValueFromSelection() const;`
- L706 _protected member_ `bool bFirstStampPending = false;` — Always applies a stamp on mouse press
- L707 _protected member_ `TArray<int> NormalsBuffer;`
- L709 _protected member_ `TArray<int> TempROIBuffer;`
- L710 _protected member_ `TArray<int> VertexROI;`
- L711 _protected member_ `TArray<bool> VisibilityFilterBuffer;`
- L712 _protected member_ `TSet<int> VertexSetBuffer;`
- L713 _protected member_ `TSet<int> TriangleROI;`
- L714 _protected prototype_ `void UpdateROI(const FSculptBrushStamp& CurrentStamp, int32 BrushTriangleID);`
- L716 _protected prototype_ `bool UpdateStampPosition(const FRay& WorldRay);`
- L717 _protected prototype_ `bool ApplyStamp(const FSculptBrushStamp& InStamp);`
- L720 _protected member_ `TSharedRef<UE::MeshVertexAttributePaintToolBase::Private::FStrokeAccumulator> StrokeAccumulator;` — Per-Transaction/Stroke bookkeeping (pimpl).
- L723 _protected member_ `TArray<double> CotangentEdgeWeights;` — Per-edge cotangent weights for the relax operation.
- L725 _protected prototype_ `float ComputeStampFalloffAtVertex(const FSculptBrushStamp& Stamp, const FVector3d& VertexPos);`
- L727 _protected member_ `UE::Geometry::FDynamicMeshOctree3 Octree;`
- L728 _protected prototype_ `void FullUpdateOctree();`
- L730 _protected prototype_ `void UpdateBrushType(EMeshVertexAttributePaintToolEditOperation EditOperation);`
- L731 _protected prototype_ `bool UpdateBrushPosition(const FRay& WorldRay);`
- L733 _protected member_ `bool bPendingPickWeight = false;`
- L734 _protected member_ `bool bBrushIsHoverMesh = false;`
- L735 _protected member_ `bool bIsMirrorHiddenBecauseOfBrushStroke = false;`
- L737 _protected member_ `TArray<int32> ROITriangleBuffer;`
- L738 _protected member_ `TArray<double> ROIWeightValueBuffer;`
- L739 _protected prototype_ `bool SyncMeshWithWeightBuffer();`
- L740 _protected prototype_ `bool SyncWeightBufferWithMesh();`
- L743 _protected prototype_ `void BeginChange();`
- L744 _protected prototype_ `void EndChange();`
- L745 _protected prototype_ `void CancelChange();`
- L747 _protected member_ `TArray<int32> UVSeamEdges;`
- L748 _protected member_ `TArray<int32> NormalSeamEdges;`
- L749 _protected prototype_ `void PrecomputeSeamEdges();`
- L751 _protected member_ `FMeshVertexAttributePaintToolData VertexData;`
- L754 _protected function_ `virtual bool ShowWorkPlane() const override`
- L758 _protected member_ `bool bAnyChangeMade = false;`
- L762 _protected prototype_ `void UpdateVertexColorOverlay(const TSet<int32>* TrianglesToUpdate = nullptr);`
- L764 _protected member_ `static constexpr int32 PaintBrushId = 0;`
- L765 _protected member_ `static constexpr int32 SmoothBrushId = 1;`
- L787 _private member_ `FMirrorData MirrorData;`

#### struct `UMeshVertexAttributePaintToolBase::FMirrorData`  
`struct FMirrorData`  
_L769-786_
- desc: this structure holds information for mirroring
- L773 _public prototype_ `void EnsureMirrorDataIsUpdated(const FDynamicMesh3& Mesh, EAxis::Type InMirrorAxis, EMeshVertexAttributePaintToolMirrorDirection InMirrorDirection, bool bInObjectSpace);` — lazily updates the mirror data tables for the current skeleton/mesh/mirror plane
- L775 _public prototype_ `void FindMirroredIndices(const FDynamicMesh3& Mesh, const TArray<int32>& SelectedVertices, TArray<int32>& OutVerticesToUpdate);`
- L779 _private prototype_ `bool IsPointOnTargetMirrorSide(const FVector& InPoint) const;` — return true if the point lies on the TARGET side of the mirror plane
- L781 _private member_ `EAxis::Type Axis = EAxis::X;`
- L782 _private member_ `EMeshVertexAttributePaintToolMirrorDirection Direction = EMeshVertexAttributePaintToolMirrorDirection::PositiveToNegative;`
- L783 _private member_ `bool bObjectSpace = true;`
- L785 _private member_ `TMap<int32, int32> VertexMap;` — <Target, Source>

#### Free symbols / members of external scopes

- L33 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`
- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace MeshVertexAttributePaintToolBase` (scope `UE`)
- L44 _namespace_ `namespace Private` (scope `UE::MeshVertexAttributePaintToolBase`)
- L60 _namespace_ `namespace UE`
- L60 _namespace_ `namespace MeshVertexAttributePaintToolBase` (scope `UE`)
- L119 _delegate_ `DECLARE_STATS_GROUP(TEXT("MeshVertexAttributePaintTool"), STATGROUP_VertexAttributeP`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/ShapeSprayTool.h` (Public)


#### class `UShapeSprayToolBuilder`  
`class UShapeSprayToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L17-23_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: UMeshSurfacePointMeshEditingToolBuilder override for UShapeSprayTool
- L22 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### class `UShapeSprayToolProperties`  
`class UShapeSprayToolProperties : public UInteractiveToolPropertySet`  
_L30-53_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings UObject for UShapeSprayTool.
- L34 _public prototype_ `UShapeSprayToolProperties();`
- L37 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L40 _public member_ `bool bRandomColor;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L43 _public member_ `float DropSpeed;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Speed", UIMin = "0.01", UIMax = "1.0"))`
- L46 _public member_ `float ObjectSize;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Shape Size", UIMin = "1.0", UIMax = "30.0"))`
- L49 _public member_ `int NumSplats;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Repeat Per Stamp"))`
- L52 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(EditAnywhere, Category = Options)`

#### class `UShapeSprayTool`  
`class UShapeSprayTool : public UDynamicMeshBrushTool`  
_L64-109_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDynamicMeshBrushTool`
- desc: UShapeSprayTool is a brush-based tool that generates random points on the target surface within the brush radius, and then creates small meshes at those points. The accumulated meshes are appended and can be emitted as a new StaticMeshComponent on Accept.
- L69 _public prototype_ `UShapeSprayTool();`
- L71 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L75 _public prototype_ `virtual void Setup() override;`
- L76 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L78 _public function_ `virtual bool HasCancel() const override`
- L79 _public function_ `virtual bool HasAccept() const override`
- L80 _public prototype_ `virtual bool CanAccept() const override;`
- L82 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L85 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;` — UMeshSurfacePointTool API
- L86 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L87 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L91 _protected member_ `TObjectPtr<UShapeSprayToolProperties> Settings;` — `UPROPERTY()`
- L95 _protected member_ `TObjectPtr<UDynamicMeshComponent> AccumMeshComponent;` — `UPROPERTY()` — small meshes are accumulated here
- L99 _protected member_ `UWorld* TargetWorld;`
- L101 _protected member_ `UE::Geometry::FDynamicMesh3 ShapeMesh;`
- L102 _protected prototype_ `void UpdateShapeMesh();`
- L103 _protected prototype_ `void SplatShape(const UE::Geometry::FFrame3d& LocalFrame, double Scale, UE::Geometry::FDynamicMesh3* TargetMesh);`
- L104 _protected member_ `TArray<int> VertexMap;`
- L106 _protected member_ `FRandomStream Random;`
- L108 _protected prototype_ `virtual void EmitResult();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/SkeletalMesh/SkeletalMeshVertexAttributePaintTool.h` (Public)


#### class `USkeletalMeshVertexAttributePaintToolBuilder`  
`class USkeletalMeshVertexAttributePaintToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L24-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: Tool builder for USkeletalMeshVertexAttributePaintTool.
- L29 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L30 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L31 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `USkeletalMeshVertexAttributePaintToolProperties`  
`class USkeletalMeshVertexAttributePaintToolProperties : public UInteractiveToolPropertySet`  
_L41-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Property set for USkeletalMeshVertexAttributePaintTool. Identical shape to UMeshAttributePaintToolV2Properties — the user picks a weight layer from a dropdown and brushes into it.
- L47 _public member_ `FString Attribute;` — `UPROPERTY(EditAnywhere, Category = "Attribute", meta = (DisplayName = "Selected Attribute", GetOptions = GetAttributeNames, NoResetToDefault))`
- L50 _public function_ `const TArray<FString>& GetAttributeNames()` — `UFUNCTION()`
- L52 _public member_ `TArray<FString> Attributes;`
- L55 _public prototype_ `void Initialize(const TArray<FName>& AttributeNames, bool bInitialize = false);`
- L57 _public prototype_ `int32 GetSelectedAttributeIndex();`

#### class `USkeletalMeshVertexAttributePaintTool`  
`class USkeletalMeshVertexAttributePaintTool : public UMeshVertexAttributePaintToolBase, public ISkeletalMeshGeometryIsolationAwareTool, public IHotkeyHintProvider`  
_L70-130_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexAttributePaintToolBase,ISkeletalMeshGeometryIsolationAwareTool,IHotkeyHintProvider`
- desc: Skeletal-mesh-aware vertex attribute paint tool. UX is identical to UMeshAttributePaintToolV2: pick a weight layer, brush, accept. Internally the tool reads pose and isolated-triangle state from USkeletalMeshEditorContextObjectBase, paints in posed/submesh space, and commits results back to the unposed full-mesh weight layer. Brush mirroring suppresses posing so the mirror plane operates on the unposed mesh.
- L78 _protected prototype_ `virtual bool SetupToolMesh(UE::Geometry::FDynamicMesh3& InOutToolMesh, int32& OutInitialAttributeIndex) override;`
- L79 _protected prototype_ `virtual void CommitToolMesh(UE::Geometry::FDynamicMesh3& InToolMesh) override;`
- L80 _protected prototype_ `virtual void UpdatePreview(const TSet<int32>* TrianglesToUpdate = nullptr, const TArray<int32>* VerticesToUpdate = nullptr) override;`
- L83 _public prototype_ `virtual void Setup() override;`
- L84 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L85 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L88 _public prototype_ `virtual bool IsInputIsolationValidOnOutput() const override;` — ISkeletalMeshGeometryIsolationAwareTool
- L91 _public prototype_ `virtual void GetHotkeyHints(TArray<FHotkeyHint>& OutHints) const override;` — IHotkeyHintProvider
- L94 _protected prototype_ `const TArray<FTransform>& GetComponentSpaceBoneTransforms();`
- L95 _protected prototype_ `TMap<FName, float> GetMorphTargetWeights();`
- L96 _protected prototype_ `void ToggleBoneManipulation(bool bEnable);`
- L98 _protected prototype_ `void HandlePoseChangeDetectorEvent(SkeletalMeshToolsHelper::FPoseChangeDetector::FPayload Payload);`
- L100 _protected prototype_ `void PosePreviewMesh( const TArray<FTransform>& ComponentSpaceTransforms, const TMap<FName, float>& MorphTargetWeights, const TSet<int32>* TrianglesToUpdate = nullptr, const TArray<int32>* VerticesToUpdate = nullptr);`
- L108 _protected member_ `TObjectPtr<USkeletalMeshVertexAttributePaintToolProperties> AttribProps;` — `UPROPERTY()`
- L111 _protected member_ `TWeakObjectPtr<USkeletalMeshEditorContextObjectBase> EditorContext = nullptr;` — `UPROPERTY()`
- L113 _protected member_ `SkeletalMeshToolsHelper::FPoseChangeDetector PoseChangeDetector;`
- L118 _protected member_ `TOptional<UE::Geometry::FDynamicMesh3> FullUnposedMesh;` — Held only when isolation is active. ToolDynamicMesh becomes the submesh in that case, so we keep a separate full unposed copy for both pose-preview source and commit target. Without isolation this stays unset and ToolDynamicMesh serves both roles directly.
- L120 _protected member_ `TOptional<UE::Geometry::FDynamicSubmesh3> IsolationSubmesh;`
- L122 _protected member_ `TArray<FTransform> ComponentSpaceTransformsRefPose;`
- L123 _protected member_ `TArray<FTransform> DefaultComponentSpaceBoneTransforms;`
- L125 _protected member_ `TValueWatcher<int32> SelectedAttributeWatcher;`
- L127 _protected member_ `bool bFastDeformPreviewMesh = false;`
- L128 _protected member_ `bool bRebuildOctree = false;`
- L129 _protected member_ `bool bMeshSelectorNeedsUpdate = false;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/SubdividePolyTool.h` (Public)


#### class `USubdividePolyToolBuilder`  
`class USubdividePolyToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L25-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- desc: Tool builder
- L29 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### class `USubdividePolyToolProperties`  
`class USubdividePolyToolProperties : public UInteractiveToolPropertySet`  
_L37-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L45 _public member_ `int SubdivisionLevel = 3;` — `UPROPERTY(EditAnywhere, Category=Settings, meta = (UIMin = "1", ClampMin = "1", Delta = 1, LinearDeltaSensitivity = 50))` — Number of iterations/levels of subdivision to perform
- L48 _public member_ `ESubdivisionScheme SubdivisionScheme = ESubdivisionScheme::CatmullClark;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L52 _public member_ `ESubdivisionBoundaryScheme BoundaryScheme = ESubdivisionBoundaryScheme::SmoothCorners;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = "SubdivisionScheme != ESubdivisionScheme::Bilinear || bOverriddenSubdivisionScheme"))` — How to treat mesh boundaries
- L55 _public member_ `ESubdivisionOutputNormals NormalComputationMethod = ESubdivisionOutputNormals::Generated;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L58 _public member_ `ESubdivisionOutputUVs UVComputationMethod = ESubdivisionOutputUVs::Interpolated;` — `UPROPERTY(EditAnywhere, Category=Settings, meta = (DisplayName = "UV Computation Method"))`
- L62 _public member_ `bool bNewPolyGroups = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DisplayName = "New PolyGroups"))` — Assign a new PolyGroup ID to each newly created face
- L66 _public member_ `bool bRenderGroups = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Display each PolyGroup with an auto-generated color
- L70 _public member_ `bool bRenderCage = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Display the mesh corresponding to Subdivision Level 0
- L74 _public member_ `bool bAddExtraCorners = true;` — `UPROPERTY(EditAnywhere, Category = TopologyOptions, meta = (DisplayName = "Add Extra Corners on Boundary", EditCondition = "SubdivisionScheme != ESubdivisionScheme::Loop"))` — When using the group topology for subdivision, whether to add extra corners at sharp group edge bends on mesh boundaries. Note: We cannot add extra corners on non-boundary group edges, as this would create non-manifold geometry on subdivision.
- L78 _public member_ `double ExtraCornerAngleThresholdDegrees = 135;` — `UPROPERTY(EditAnywhere, Category = TopologyOptions, meta = (ClampMin = "0", ClampMax = "180", EditCondition = "SubdivisionScheme != ESubdivisionScheme::Loop && bAddExtraCorners"))` — How acute an angle between two edges needs to be to add an extra corner there when Add Extra Corners is true.
- L82 _public member_ `bool bOverriddenSubdivisionScheme = false;` — `UPROPERTY(VisibleAnywhere, Category = Settings, AdvancedDisplay, meta = (TransientToolProperty))` — Shows whether the current subdivision scheme is overridden to be "Loop" because the group topology is unsuitable.

#### class `USubdividePolyTool`  
`class USubdividePolyTool : public USingleSelectionMeshEditingTool`  
_L90-137_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- desc: Tool actual
- L96 _public prototype_ `virtual void Setup() override;`
- L97 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L99 _public function_ `virtual bool HasCancel() const override`
- L100 _public function_ `virtual bool HasAccept() const override`
- L101 _public prototype_ `virtual bool CanAccept() const override;`
- L103 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L110 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh = nullptr;` — `UPROPERTY()`
- L113 _protected member_ `TObjectPtr<USubdividePolyToolProperties> Properties = nullptr;` — `UPROPERTY()`
- L116 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Input mesh
- L118 _protected member_ `TSharedPtr<UE::Geometry::FGroupTopology> Topology;`
- L121 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry = nullptr;` — `UPROPERTY()`
- L123 _protected member_ `bool bPreviewGeometryNeedsUpdate;`
- L124 _protected prototype_ `void CreateOrUpdatePreviewGeometry();`
- L128 _protected prototype_ `bool CheckGroupTopology(FText& Message);` — Determine if the mesh group topology can be used for Catmull-Clark or Bilinear subdivision. If not, we can only Loop subdivision on the original triangle mesh.
- L130 _protected prototype_ `void CapSubdivisionLevel(ESubdivisionScheme Scheme, int DesiredLevel);`
- L132 _protected member_ `double ExtraCornerDotProductThreshold = 2;`
- L133 _protected prototype_ `ESubdivisionScheme GetSubdivisionSchemeToUse();`
- L134 _protected member_ `FText OverriddenSchemeMessage;`
- L135 _protected member_ `FText CappedSubdivisionMessage;`
- L136 _protected prototype_ `void UpdateDisplayedMessage();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/VoxelCSGMeshesTool.h` (Public)


#### enum `EVoxelCSGOperation`  
`enum class EVoxelCSGOperation : uint8`  
_L18-32_
- reflection: `UENUM()`
- L21 _public enumerator_ `DifferenceAB = 0 UMETA(DisplayName = "A - B")` — Subtracts the first object from the second
- L24 _public enumerator_ `DifferenceBA = 1 UMETA(DisplayName = "B - A")` — Subtracts the second object from the first
- L27 _public enumerator_ `Intersect = 2 UMETA(DisplayName = "Intersect")` — intersection of two objects
- L30 _public enumerator_ `Union = 3 UMETA(DisplayName = "Union")` — union of two objects

#### class `UVoxelCSGMeshesToolProperties`  
`class UVoxelCSGMeshesToolProperties : public UInteractiveToolPropertySet`  
_L39-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the Voxel CSG operation
- L45 _public member_ `EVoxelCSGOperation Operation = EVoxelCSGOperation::DifferenceAB;` — `UPROPERTY(EditAnywhere, Category = BooleanOptions)` — The type of operation
- L49 _public member_ `int32 VoxelCount = 128;` — `UPROPERTY(EditAnywhere, Category = VoxelSettings, meta = (UIMin = "8", UIMax = "1024", ClampMin = "8", ClampMax = "1024"))` — The size of the geometry bounding box major axis measured in voxels.
- L53 _public member_ `float MeshAdaptivity = 0.01f;` — `UPROPERTY(EditAnywhere, Category = VoxelSettings, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Remeshing adaptivity, prior to optional simplification
- L57 _public member_ `float OffsetDistance = 0.0f;` — `UPROPERTY()` — Offset when remeshing, note large offsets with high voxels counts will be slow.  Hidden because this duplicates functionality of the voxel offset tool
- L61 _public member_ `bool bAutoSimplify = false;` — `UPROPERTY(EditAnywhere, Category = VoxelSettings)` — Automatically simplify the result of voxel-based merge.

#### class `UVoxelCSGMeshesTool`  
`class UVoxelCSGMeshesTool : public UBaseVoxelTool`  
_L65-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseVoxelTool`
- L71 _public function_ `UVoxelCSGMeshesTool()`
- L75 _protected prototype_ `virtual void SetupProperties() override;`
- L76 _protected prototype_ `virtual void SaveProperties() override;`
- L78 _protected prototype_ `virtual FString GetCreatedAssetName() const override;`
- L79 _protected prototype_ `virtual FText GetActionName() const override;`
- L81 _protected prototype_ `virtual void ConvertInputsAndSetPreviewMaterials(bool bSetPreviewMesh) override;`
- L84 _protected prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L87 _protected member_ `TObjectPtr<UVoxelCSGMeshesToolProperties> CSGProps;` — `UPROPERTY()`
- L89 _protected function_ `virtual bool KeepCollisionFrom(int32 TargetIdx) const override`

#### class `UVoxelCSGMeshesToolBuilder`  
`class UVoxelCSGMeshesToolBuilder : public UBaseCreateFromSelectedToolBuilder`  
_L108-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedToolBuilder`
- L114 _public function_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override`
- L119 _public function_ `virtual TOptional<int32> MaxComponentsSupported() const override`
- L120 _public function_ `virtual int32 MinComponentsSupported() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLYEXP_API`
