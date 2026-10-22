# Plugins / MeshModelingToolsExp

- module root: `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp`
- headers: 47; symbols: 2680
- symbol kinds: class=154, delegate=1, enum=60, enumerator=268, function=226, macro=43, member=1126, namespace=12, prototype=749, struct=32, typedef=8, variable=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, GeometryAlgorithms, InputCore, ModelingComponentsEditorOnly, PhysicsCore, RenderCore, SlateCore
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryCore, GeometryFramework, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshModelingTools, ModelingComponents, ModelingOperators, SkeletalMeshDescription, StaticMeshDescription

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/AddPatchTool.h` (Public)


#### class `UAddPatchToolBuilder`  
`class UAddPatchToolBuilder : public UInteractiveToolBuilder`  
_L22-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L26 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L27 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UAddPatchToolProperties`  
`class UAddPatchToolProperties : public UInteractiveToolPropertySet`  
_L33-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L38 _public prototype_ `UAddPatchToolProperties();`
- L42 _public member_ `float Width;` — `UPROPERTY(EditAnywhere, Category = PatchSettings, meta = (DisplayName = "Width", UIMin = "1.0", UIMax = "1000.0", ClampMin = "0.0001", ClampMax = "1000000.0"))` — Width of Shape
- L46 _public member_ `float Rotation;` — `UPROPERTY(EditAnywhere, Category = PatchSettings, meta = (DisplayName = "Rotation", UIMin = "0.0", UIMax = "360.0"))` — Rotation around up axis
- L50 _public member_ `int Subdivisions;` — `UPROPERTY(EditAnywhere, Category = PatchSettings, meta = (DisplayName = "Subdivisions", UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "4000"))` — Subdivisions
- L54 _public member_ `float Shift;` — `UPROPERTY(EditAnywhere, Category = PatchSettings, meta = (DisplayName = "Shift", UIMin = "-1000", UIMax = "1000"))` — Rotation around up axis

#### class `UAddPatchTool`  
`class UAddPatchTool : public USingleClickTool, public IHoverBehaviorTarget`  
_L67-123_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickTool,IHoverBehaviorTarget`
- L72 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L74 _public prototype_ `virtual void Setup() override;`
- L75 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L77 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L78 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L80 _public function_ `virtual bool HasCancel() const override`
- L81 _public function_ `virtual bool HasAccept() const override`
- L82 _public function_ `virtual bool CanAccept() const override`
- L84 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L86 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L90 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget interface
- L91 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L92 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L93 _public prototype_ `virtual void OnEndHover() override;`
- L98 _protected member_ `TObjectPtr<UAddPatchToolProperties> ShapeSettings;` — `UPROPERTY()`
- L101 _protected member_ `TObjectPtr<UNewMeshMaterialProperties> MaterialProperties;` — `UPROPERTY()`
- L106 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L109 _protected member_ `UWorld* TargetWorld;`
- L111 _protected member_ `FBox WorldBounds;`
- L113 _protected member_ `UE::Geometry::FFrame3f ShapeFrame;`
- L114 _protected member_ `bool bPreviewValid = true;`
- L116 _protected prototype_ `void UpdatePreviewPosition(const FInputDeviceRay& ClickPos);`
- L117 _protected prototype_ `void UpdatePreviewMesh();`
- L119 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMesh3> BaseMesh;`
- L120 _protected prototype_ `void GeneratePreviewBaseMesh();`
- L122 _protected prototype_ `void GeneratePlane(UE::Geometry::FDynamicMesh3* OutMesh);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L16 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/AlignObjectsTool.h` (Public)


#### class `UAlignObjectsToolBuilder`  
`class UAlignObjectsToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L22-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L27 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L28 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L31 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EAlignObjectsAlignTypes`  
`enum class EAlignObjectsAlignTypes`  
_L36-40_
- reflection: `UENUM()`
- L38 _public enumerator_ `Pivots`
- L39 _public enumerator_ `BoundingBoxes`

#### enum `EAlignObjectsAlignToOptions`  
`enum class EAlignObjectsAlignToOptions`  
_L43-48_
- reflection: `UENUM()`
- L45 _public enumerator_ `FirstSelected`
- L46 _public enumerator_ `LastSelected`
- L47 _public enumerator_ `Combined`

#### enum `EAlignObjectsBoxPoint`  
`enum class EAlignObjectsBoxPoint`  
_L51-62_
- reflection: `UENUM()`
- L53 _public enumerator_ `Center`
- L54 _public enumerator_ `Bottom`
- L55 _public enumerator_ `Top`
- L56 _public enumerator_ `Left`
- L57 _public enumerator_ `Right`
- L58 _public enumerator_ `Front`
- L59 _public enumerator_ `Back`
- L60 _public enumerator_ `Min`
- L61 _public enumerator_ `Max`

#### class `UAlignObjectsToolProperties`  
`class UAlignObjectsToolProperties : public UInteractiveToolPropertySet`  
_L70-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the Align Objects Operation
- L76 _public member_ `EAlignObjectsAlignTypes AlignType = EAlignObjectsAlignTypes::BoundingBoxes;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L79 _public member_ `EAlignObjectsAlignToOptions AlignTo = EAlignObjectsAlignToOptions::Combined;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L82 _public member_ `EAlignObjectsBoxPoint BoxPosition = EAlignObjectsBoxPoint::Center;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "AlignType == EAlignObjectsAlignTypes::BoundingBoxes || AlignTo == EAlignObjectsAlignToOptions::Combined"))`
- L85 _public member_ `bool bAlignX = false;` — `UPROPERTY(EditAnywhere, Category = Axes)`
- L88 _public member_ `bool bAlignY = false;` — `UPROPERTY(EditAnywhere, Category = Axes)`
- L91 _public member_ `bool bAlignZ = true;` — `UPROPERTY(EditAnywhere, Category = Axes)`

#### class `UAlignObjectsTool`  
`class UAlignObjectsTool : public UMultiSelectionMeshEditingTool, public IClickDragBehaviorTarget`  
_L104-161_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IClickDragBehaviorTarget`
- desc: UAlignObjectsTool transforms the input Components so that they are aligned in various ways, depending on the current settings. The object positions move after every change in the parameters. Currently those changes are not transacted. On cancel the original positions are restored, and on accept the positions are updated with a transaction.
- L107 _private typedef_ `using FAxisAlignedBox3d = UE::Geometry::FAxisAlignedBox3d;`
- L109 _public prototype_ `UAlignObjectsTool();`
- L111 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L113 _public prototype_ `virtual void Setup() override;`
- L114 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L116 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L117 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L119 _public function_ `virtual bool HasCancel() const override`
- L120 _public function_ `virtual bool HasAccept() const override`
- L121 _public function_ `virtual bool CanAccept() const override`
- L123 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L127 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — ICLickDragBehaviorTarget interface
- L128 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L129 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L130 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L131 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L135 _public member_ `TObjectPtr<UAlignObjectsToolProperties> AlignProps;` — `UPROPERTY()`
- L149 _protected member_ `TArray<FAlignInfo> ComponentInfo;`
- L151 _protected member_ `FAxisAlignedBox3d CombinedBounds;`
- L152 _protected member_ `FAxisAlignedBox3d PivotBounds;`
- L153 _protected member_ `FVector3d AveragePivot;`
- L155 _protected prototype_ `void Precompute();`
- L157 _protected member_ `bool bAlignDirty = false;`
- L158 _protected prototype_ `void UpdateAlignment();`
- L159 _protected prototype_ `void UpdateAlignment_Pivots();`
- L160 _protected prototype_ `void UpdateAlignment_BoundingBoxes();`

#### struct `UAlignObjectsTool::FAlignInfo`  
`struct FAlignInfo`  
_L140-147_
- L142 _public member_ `UPrimitiveComponent* Component;`
- L143 _public member_ `FTransform SavedTransform;`
- L144 _public member_ `FTransform3d WorldTransform;`
- L145 _public member_ `FVector3d WorldPivot;`
- L146 _public member_ `FAxisAlignedBox3d WorldBounds;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/BakeMeshAttributeMapsTool.h` (Public)


#### class `UBakeMeshAttributeMapsToolBuilder`  
`class UBakeMeshAttributeMapsToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L34-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L39 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L40 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L43 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UBakeMeshAttributeMapsToolProperties`  
`class UBakeMeshAttributeMapsToolProperties : public UInteractiveToolPropertySet`  
_L52-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L60 _public member_ `int32 MapTypes = static_cast<int32>(EBakeMapType::None);` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta = (DisplayName = "Output Types", Bitmask, BitmaskEnum = "/Script/MeshModelingToolsExp.EBakeMapType", ValidEnumValues="TangentSpaceNormal, AmbientOcclusion, BentNormal, Curvature, Texture, ObjectSpaceNormal, FaceNormal, Position, MaterialID, PolyGroupID, MultiTexture, VertexColor, UVShell, Height"))` — The bake output types to generate
- L65 _public member_ `FString MapPreview;` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta = (DisplayName = "Preview Output Type", GetOptions = GetMapPreviewNamesFunc, TransientToolProperty, EditCondition = "MapTypes != 0", NoResetToDefault))` — The baked output type used for preview in the viewport
- L69 _public member_ `EBakeTextureResolution Resolution = EBakeTextureResolution::Resolution256;` — `UPROPERTY(EditAnywhere, Category = Textures)` — The pixel resolution of the generated textures
- L73 _public member_ `EBakeTextureBitDepth BitDepth = EBakeTextureBitDepth::ChannelBits8;` — `UPROPERTY(EditAnywhere, Category = Textures)` — The bit depth for each channel of the generated textures
- L77 _public member_ `EBakeTextureSamplesPerPixel SamplesPerPixel = EBakeTextureSamplesPerPixel::Sample1;` — `UPROPERTY(EditAnywhere, Category = Textures)` — Number of samples per pixel
- L81 _public member_ `TObjectPtr<UTexture2D> SampleFilterMask = nullptr;` — `UPROPERTY(EditAnywhere, Category = Textures, AdvancedDisplay)` — Mask texture for filtering out samples/pixels from the output texture
- L84 _public prototype_ `const TArray<FString>& GetMapPreviewNamesFunc();` — `UFUNCTION()`
- L86 _public member_ `TArray<FString> MapPreviewNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L87 _public member_ `TMap<FString, FString> MapPreviewNamesMap;`

#### class `UBakeMeshAttributeMapsTool`  
`class UBakeMeshAttributeMapsTool : public UBakeMeshAttributeMapsToolBase`  
_L95-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBakeMeshAttributeMapsToolBase`
- desc: Detail Map Baking Tool
- L100 _public prototype_ `UBakeMeshAttributeMapsTool() = default;`
- L103 _public prototype_ `virtual void Setup() override;`
- L104 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L106 _public function_ `virtual bool HasCancel() const override`
- L107 _public function_ `virtual bool HasAccept() const override`
- L108 _public prototype_ `virtual bool CanAccept() const override;`
- L112 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<UE::Geometry::FMeshMapBaker>> MakeNewOperator() override;`
- L120 _protected member_ `TObjectPtr<UBakeInputMeshProperties> InputMeshSettings;` — `UPROPERTY()`
- L123 _protected member_ `TObjectPtr<UBakeMeshAttributeMapsToolProperties> Settings;` — `UPROPERTY()`
- L126 _protected member_ `TObjectPtr<UBakeMeshAttributeMapsResultToolProperties> ResultSettings;` — `UPROPERTY()`
- L129 _protected member_ `TObjectPtr<UBakeUVShellMapToolProperties> UVShellSettings;` — `UPROPERTY()`
- L133 _protected prototype_ `virtual void UpdateResult() override;`
- L134 _protected prototype_ `virtual void UpdateVisualization() override;`
- L136 _protected prototype_ `virtual void GatherAnalytics(FBakeAnalytics::FMeshSettings& Data) override;`
- L141 _protected member_ `bool bIsBakeToSelf = false;`
- L143 _protected prototype_ `bool ValidDetailMeshTangents();`
- L144 _protected member_ `bool bCheckDetailMeshTangents = true;`
- L145 _protected member_ `bool bValidDetailMeshTangents = false;`
- L147 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> DetailMesh;`
- L148 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> DetailSpatial;`
- L149 _protected member_ `TSharedPtr<UE::Geometry::TMeshTangents<double>, ESPMode::ThreadSafe> DetailMeshTangents;`
- L150 _protected member_ `int32 DetailMeshTimestamp = 0;`
- L151 _protected prototype_ `void UpdateDetailMesh();`
- L153 _protected prototype_ `void UpdateOnModeChange();`
- L155 _protected prototype_ `void InvalidateResults();`
- L157 _protected prototype_ `EBakeOpState UpdateResult_DetailMeshTangents(EBakeMapType BakeType);`
- L159 _protected member_ `FDetailMeshSettings CachedDetailMeshSettings;`
- L160 _protected member_ `TSharedPtr<UE::Geometry::TImageBuilder<FVector4f>, ESPMode::ThreadSafe> CachedDetailNormalMap;`
- L161 _protected prototype_ `EBakeOpState UpdateResult_DetailNormalMap();`
- L163 _protected member_ `FUVShellMapSettings CachedUVShellMapSettings;`
- L164 _protected prototype_ `EBakeOpState UpdateResult_UVShellMap(const FImageDimensions& Dimensions);`
- L166 _protected function_ `void SetSourceObjectVisible(bool bState)`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L24 _prototype_ `PREDECLARE_GEOMETRY(template<typename RealType> class TMeshTangents);`
- L25 _prototype_ `PREDECLARE_GEOMETRY(class FMeshImageBakingCache);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/BakeMeshAttributeMapsToolBase.h` (Public)


#### class `UBakeMeshAttributeMapsResultToolProperties`  
`class UBakeMeshAttributeMapsResultToolProperties : public UInteractiveToolPropertySet`  
_L24-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L30 _public member_ `TMap<EBakeMapType, TObjectPtr<UTexture2D>> Result;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (DisplayName = "Results", TransientToolProperty))` — Bake

#### class `UBakeMeshAttributeMapsToolBase`  
`class UBakeMeshAttributeMapsToolBase : public UBakeMeshAttributeTool, public UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshMapBaker>`  
_L38-308_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBakeMeshAttributeTool,UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshMapBaker>`
- desc: Base Bake Maps tool
- L43 _public prototype_ `UBakeMeshAttributeMapsToolBase() = default;`
- L46 _public prototype_ `virtual void Setup() override;`
- L47 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L49 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L50 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L54 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<UE::Geometry::FMeshMapBaker>> MakeNewOperator() override;`
- L64 _public prototype_ `static EBakeMapType GetMapTypes(const int32& MapTypes);` — Process a bitfield into an EBakeMapType. This function may inject additional map types based on the enabled bits. For example, enabling AmbientOcclusion if BentNormal is active. @return An enumerated map type from a bitfield
- L71 _protected member_ `TObjectPtr<UBakeVisualizationProperties> VisualizationProps;` — `UPROPERTY()` — Tool property sets
- L77 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()` — Preview mesh and materials
- L80 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewMaterial;` — `UPROPERTY()`
- L83 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> BentNormalPreviewMaterial;` — `UPROPERTY()`
- L90 _protected prototype_ `void PostSetup();` — Post-client setup function. Should be invoked at end of client Setup(). Initialize common base tool properties (ex. visualization properties) and analytics.
- L96 _protected prototype_ `virtual void UpdateResult();` — Process dirty props and update background compute. Invoked during Render.
- L102 _protected prototype_ `virtual void UpdateVisualization();` — Updates the preview material on the preview mesh with the computed results. Invoked by OnMapsUpdated.
- L107 _protected prototype_ `void InvalidateCompute();` — Invalidates the background compute operator.
- L115 _protected prototype_ `void CreateTextureAssets(const TMap<EBakeMapType, TObjectPtr<UTexture2D>>& Textures, UWorld* SourceWorld, UObject* SourceAsset);` — Create texture assets from our result map of Texture2D @param Textures the result map of textures to create @param SourceWorld the source world to define where the texture assets will be stored. @param SourceAsset if not null, result textures will be stored adjacent to this asset.
- L141 _protected member_ `FBakeSettings CachedBakeSettings;`
- L143 _protected prototype_ `EBakeOpState UpdateResult_SampleFilterMask(UTexture2D* SampleFilterMask);`
- L144 _protected member_ `TSharedPtr<UE::Geometry::TImageBuilder<FVector4f>, ESPMode::ThreadSafe> CachedSampleFilterMask;`
- L146 _protected member_ `TSharedPtr<TArray<int32>, ESPMode::ThreadSafe> TargetMeshUVCharts;`
- L156 _protected prototype_ `void OnMapTypesUpdated( EBakeMapType ResultMapTypes, TMap<EBakeMapType, TObjectPtr<UTexture2D>>& Result, FString& MapPreview, TArray<FString>& MapPreviewNamesList, TMap<FString, FString>& MapPreviewNamesMap);` — To be invoked by client when bake map types change. @param ResultMapTypes the requested map types to compute @param Result the output map of bake result textures @param MapPreview the map preview string property @param MapPreviewNamesList the stored list of map preview display names. @param MapPreviewNamesMap the stored map of map preview display names to enum string values.
- L166 _protected member_ `TUniquePtr<TGenericDataBackgroundCompute<UE::Geometry::FMeshMapBaker>> Compute = nullptr;` — Background compute
- L178 _protected member_ `TMap<EBakeMapType, TObjectPtr<UTexture2D>> CachedMaps;` — `UPROPERTY()` — Internal cache of bake texture results. The tool can inject additional bake types that were not requested by the user. This can occur in cases where a particular bake type might need another bake type to preview such as BentNormal requiring AmbientOcclusion to preview. To avoid writing out assets that the user did not request, we introduce CachedMaps as a temporary texture cache for the tool preview. The Result array is then updated from CachedMaps to only hold user requested textures that are written out on Shutdown.
- L187 _protected prototype_ `void OnMapsUpdated(const TUniquePtr<UE::Geometry::FMeshMapBaker>& NewResult);` — Retrieves the result of the FMeshMapBaker and generates UTexture2D into the CachedMaps. It is the responsibility of the client to ensure that CachedMaps is appropriately sized for the range of index values in MapIndex. @param NewResult the resulting FMeshMapBaker from the background Compute
- L196 _protected prototype_ `void UpdatePreview(const FString& PreviewDisplayName, const TMap<FString, FString>& MapPreviewNamesMap);` — Update the preview material parameters for a given Bake type display name. @param PreviewDisplayName Displayed UI preview name to preview @param MapPreviewNamesMap Map containing the list of displayed preview name to enum string value.
- L203 _protected prototype_ `void UpdatePreview(EBakeMapType PreviewMapType);` — Update the preview material parameters for a given a Bake type. @param PreviewMapType EBakeMapType to preview
- L209 _protected prototype_ `void ResetPreview();` — Resets the preview material parameters to their default state.
- L222 _protected prototype_ `void UpdatePreviewNames( const EBakeMapType MapTypes, FString& MapPreview, TArray<FString>& MapPreviewNamesList, TMap<FString, FString>& MapPreviewNamesMap);` — Updates a tool property set's MapPreviewNamesList from the list of active map types. Also updates the MapPreview property if the current preview option is no longer available. @param MapTypes the requested map types to compute @param MapPreview the map preview string property @param MapPreviewNamesList the stored list of map preview display names. @param MapPreviewNamesMap the stored map of map preview display names to enum string values.
- L252 _protected member_ `FBakeAnalytics BakeAnalytics;`
- L258 _protected prototype_ `virtual void GatherAnalytics(FBakeAnalytics::FMeshSettings& Data);` — Computes the NumTargetMeshTris, NumDetailMesh and NumDetailMeshTris analytics. @param Data the mesh analytics data to compute
- L266 _protected prototype_ `static void GatherAnalytics(const UE::Geometry::FMeshMapBaker& Result, const FBakeSettings& Settings, FBakeAnalytics& Data);` — Records bake timing and settings data for analytics. @param Result the result of the bake. @param Settings The bake settings used for the bake. @param Data the output bake analytics struct.
- L275 _protected prototype_ `static void RecordAnalytics(const FBakeAnalytics& Data, const FString& EventName);` — Posts an analytics event using the given analytics struct. @param Data the bake analytics struct to output. @param EventName the name of the analytics event to output.
- L281 _protected function_ `virtual FString GetAnalyticsEventName() const` — @return the analytics event name for this tool.
- L291 _protected prototype_ `static UE::Geometry::FTexture2DBuilder::ETextureType GetTextureType(EBakeMapType MapType, EBakeTextureBitDepth MapFormat);` — @return the Texture2D type for a given map type
- L294 _protected prototype_ `static void GetTextureName(EBakeMapType MapType, const FString& BaseName, FString& TexName);` — @return the texture name given a base name and map type
- L299 _protected member_ `TObjectPtr<UTexture2D> EmptyNormalMap;` — `UPROPERTY()` — empty maps are shown when nothing is computed
- L302 _protected member_ `TObjectPtr<UTexture2D> EmptyColorMapBlack;` — `UPROPERTY()`
- L305 _protected member_ `TObjectPtr<UTexture2D> EmptyColorMapWhite;` — `UPROPERTY()`
- L307 _protected prototype_ `void InitializeEmptyMaps();`

#### struct `UBakeMeshAttributeMapsToolBase::FBakeSettings`  
`struct FBakeSettings`  
_L120-140_
- desc: Bake parameters
- L122 _public member_ `EBakeMapType SourceBakeMapTypes = EBakeMapType::None;`
- L123 _public member_ `EBakeMapType BakeMapTypes = EBakeMapType::None;`
- L124 _public member_ `FImageDimensions Dimensions;`
- L125 _public member_ `EBakeTextureBitDepth BitDepth = EBakeTextureBitDepth::ChannelBits8;`
- L126 _public member_ `int32 TargetUVLayer = 0;`
- L127 _public member_ `int32 DetailTimestamp = 0;`
- L128 _public member_ `float ProjectionDistance = 3.0;`
- L129 _public member_ `int32 SamplesPerPixel = 1;`
- L130 _public member_ `bool bProjectionInWorldSpace = false;`
- L132 _public function_ `bool operator==(const FBakeSettings& Other) const`

#### struct `UBakeMeshAttributeMapsToolBase::FBakeAnalytics`  
`struct FBakeAnalytics`  
_L232-251_
- desc: Analytics
- L234 _public member_ `double TotalBakeDuration = 0.0;`
- L235 _public member_ `double WriteToImageDuration = 0.0;`
- L236 _public member_ `double WriteToGutterDuration = 0.0;`
- L237 _public member_ `int64 NumSamplePixels = 0;`
- L238 _public member_ `int64 NumGutterPixels = 0;`
- L246 _public member_ `FMeshSettings MeshSettings;`
- L248 _public member_ `FBakeSettings BakeSettings;`
- L249 _public member_ `FOcclusionMapSettings OcclusionSettings;`
- L250 _public member_ `FCurvatureMapSettings CurvatureSettings;`

#### struct `UBakeMeshAttributeMapsToolBase::FBakeAnalytics::FMeshSettings`  
`struct FMeshSettings`  
_L240-245_
- L242 _public member_ `int32 NumTargetMeshTris = 0;`
- L243 _public member_ `int32 NumDetailMesh = 0;`
- L244 _public member_ `int64 NumDetailMeshTris = 0;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/BakeMeshAttributeTool.h` (Public)


#### enum `EBakeMapType`  
`enum class EBakeMapType`  
_L26-64_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L28 _public enumerator_ `None = 0`
- L31 _public enumerator_ `TangentSpaceNormal = 1 << 0 UMETA(DisplayName = "Tangent Normal")` — Normals in tangent space
- L33 _public enumerator_ `ObjectSpaceNormal = 1 << 1 UMETA(DisplayName = "Object Normal")` — Interpolated normals in object space
- L35 _public enumerator_ `FaceNormal = 1 << 2` — Geometric face normals in object space
- L37 _public enumerator_ `BentNormal = 1 << 3` — Normals skewed towards the least occluded direction
- L39 _public enumerator_ `Position = 1 << 4` — Positions in object space
- L41 _public enumerator_ `Curvature = 1 << 5` — Local curvature of the mesh surface
- L43 _public enumerator_ `AmbientOcclusion = 1 << 6` — Ambient occlusion sampled across the hemisphere
- L45 _public enumerator_ `Texture = 1 << 7` — Transfer a given texture
- L47 _public enumerator_ `MultiTexture = 1 << 8` — Transfer a texture per material ID
- L49 _public enumerator_ `VertexColor = 1 << 9` — Interpolated vertex colors
- L51 _public enumerator_ `MaterialID = 1 << 10 UMETA(DisplayName = "Material ID")` — Material IDs as unique colors
- L53 _public enumerator_ `PolyGroupID = 1 << 11 UMETA(DisplayName = "PolyGroup ID")` — PolyGroup IDs as unique colors
- L55 _public enumerator_ `One = 1 << 12` — Constant value of One
- L57 _public enumerator_ `Zero = 1 << 13` — Constant value of Zero
- L59 _public enumerator_ `UVShell = 1 << 14 UMETA(DisplayName = "UV Shell")` — UV shell
- L61 _public enumerator_ `Height = 1 << 15` — Height
- L63 _public enumerator_ `All = 0x7FFF UMETA(Hidden)`

#### class `UBakeMeshAttributeTool`  
`class UBakeMeshAttributeTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolExclusiveToolAPI, public IInteractiveToolManageGeometrySelectionAPI`  
_L95-228_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolExclusiveToolAPI,IInteractiveToolManageGeometrySelectionAPI`
- desc: Base Mesh Bake tool
- L100 _public prototype_ `UBakeMeshAttributeTool() = default;`
- L103 _public prototype_ `virtual void Setup() override;`
- L105 _public function_ `virtual bool HasCancel() const override`
- L106 _public function_ `virtual bool HasAccept() const override`
- L107 _public function_ `virtual bool CanAccept() const override`
- L111 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L121 _protected member_ `TObjectPtr<UBakeOcclusionMapToolProperties> OcclusionSettings;` — `UPROPERTY()` — Bake tool property sets
- L124 _protected member_ `TObjectPtr<UBakeCurvatureMapToolProperties> CurvatureSettings;` — `UPROPERTY()`
- L127 _protected member_ `TObjectPtr<UBakeTexture2DProperties> TextureSettings;` — `UPROPERTY()`
- L130 _protected member_ `TObjectPtr<UBakeMultiTexture2DProperties> MultiTextureSettings;` — `UPROPERTY()`
- L133 _protected member_ `TObjectPtr<UBakeHeightMapToolProperties> HeightSettings;` — `UPROPERTY()`
- L140 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> WorkingPreviewMaterial;` — `UPROPERTY()` — Preview materials
- L143 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> ErrorPreviewMaterial;` — `UPROPERTY()`
- L145 _protected member_ `float SecondsBeforeWorkingMaterial = 0.75;`
- L151 _protected member_ `EBakeOpState OpState = EBakeOpState::Evaluate;` — Bake parameters
- L153 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> TargetMesh;`
- L154 _protected member_ `TSharedPtr<UE::Geometry::TMeshTangents<double>, ESPMode::ThreadSafe> TargetMeshTangents;`
- L162 _protected prototype_ `bool ValidTargetMeshTangents();` — Compute validity of the Target Mesh tangents. Only checks validity once and then caches the result for successive calls. @return true if the TargetMesh tangents are valid
- L163 _protected member_ `bool bCheckTargetMeshTangents = true;`
- L164 _protected member_ `bool bValidTargetMeshTangents = false;`
- L169 _protected member_ `const bool bPreferPlatformData = false;` — Bake results update management
- L172 _protected prototype_ `EBakeOpState UpdateResult_TargetMeshTangents(EBakeMapType BakeType);` — Update the OpState based on the validity of the target mesh tangents
- L174 _protected prototype_ `EBakeOpState UpdateResult_Normal(const FImageDimensions& Dimensions);`
- L175 _protected member_ `FNormalMapSettings CachedNormalMapSettings;`
- L177 _protected prototype_ `EBakeOpState UpdateResult_Occlusion(const FImageDimensions& Dimensions);`
- L178 _protected member_ `FOcclusionMapSettings CachedOcclusionMapSettings;`
- L180 _protected prototype_ `EBakeOpState UpdateResult_Curvature(const FImageDimensions& Dimensions);`
- L181 _protected member_ `FCurvatureMapSettings CachedCurvatureMapSettings;`
- L183 _protected prototype_ `EBakeOpState UpdateResult_MeshProperty(const FImageDimensions& Dimensions);`
- L184 _protected member_ `FMeshPropertyMapSettings CachedMeshPropertyMapSettings;`
- L186 _protected prototype_ `EBakeOpState UpdateResult_Height(const FImageDimensions& Dimensions);`
- L187 _protected member_ `FHeightMapSettings CachedHeightMapSettings;`
- L189 _protected prototype_ `EBakeOpState UpdateResult_Texture2DImage(const FImageDimensions& Dimensions, const FDynamicMesh3* DetailMesh);`
- L190 _protected member_ `FTexture2DSettings CachedTexture2DSettings;`
- L191 _protected member_ `TSharedPtr<UE::Geometry::TImageBuilder<FVector4f>, ESPMode::ThreadSafe> CachedTextureImage;`
- L193 _protected prototype_ `EBakeOpState UpdateResult_MultiTexture(const FImageDimensions& Dimensions, const FDynamicMesh3* DetailMesh);`
- L194 _protected member_ `FTexture2DSettings CachedMultiTexture2DSettings;`
- L195 _protected member_ `TArray<TSharedPtr<UE::Geometry::TImageBuilder<FVector4f>, ESPMode::ThreadSafe>> CachedMultiTextures;`
- L208 _protected prototype_ `static int SelectColorTextureToBake(const TArray<UTexture*>& Textures);` — Given an array of textures associated with a material, use heuristics to identify the color/albedo texture. @param Textures array of textures associated with a material. @return integer index into the Textures array representing the color/albedo texture
- L216 _protected prototype_ `template <typename ProcessFn> static void ProcessComponentTextures(const UPrimitiveComponent* Component, ProcessFn&& ProcessFunc);` — Iterate through a primitive component's textures by material ID. @param Component the component to query @param ProcessFunc enumeration function with signature: void(int NumMaterials, int MaterialID, const TArray<UTexture*>& Textures)
- L224 _protected prototype_ `static void UpdateMultiTextureMaterialIDs( UToolTarget* Target, TArray<TObjectPtr<UTexture2D>>& AllSourceTextures, TArray<TObjectPtr<UTexture2D>>& MaterialIDTextures);` — Find all source textures and material IDs for a given target. @param Target the tool target to inspect @param AllSourceTextures the output array of all textures associated with the target. @param MaterialIDTextures the output array of material IDs and best guess textures for those IDs on the target.
- L232 _function_ `template <typename ProcessFn> void UBakeMeshAttributeTool::ProcessComponentTextures(const UPrimitiveComponent* Component, ProcessFn&& ProcessFunc)`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L65 _prototype_ `ENUM_CLASS_FLAGS(EBakeMapType);`
- L72 _variable_ `static constexpr EBakeMapType ENUM_EBAKEMAPTYPE_ALL[] = { EBakeMapType::TangentSpaceNormal, EBakeMapType::ObjectSpaceNormal, EBakeMapType::FaceNormal, EBakeMapType::BentNormal, EBakeMapType::Position, EBakeMapType::Curvature, EBakeMapType::Height, EBakeMapType::AmbientOcclusion, EBakeMapType::Texture, EBakeMapType::MultiTexture, EBakeMapType::VertexColor, EBakeMapType::MaterialID, EBakeMapType::PolyGroupID, EBakeMapType::UVShell };` — Array of all bake map types. This defines the order in which the bake map types are iterated in the bake tools. Consequently this ordering is reflected in the order of the bake Results property.

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/BakeMeshAttributeToolCommon.h` (Public)


#### enum `EBakeNormalSpace`  
`enum class EBakeNormalSpace`  
_L25-31_
- reflection: `UENUM()`
- L28 _public enumerator_ `Tangent` — Tangent space
- L30 _public enumerator_ `Object` — Object space

#### class `UBakeInputMeshProperties`  
`class UBakeInputMeshProperties : public UInteractiveToolPropertySet`  
_L35-133_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L42 _public member_ `TObjectPtr<UStaticMesh> TargetStaticMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Target Mesh", meta = (TransientToolProperty, EditCondition = "TargetStaticMesh != nullptr", EditConditionHides))` — Target mesh to sample to
- L47 _public member_ `TObjectPtr<USkeletalMesh> TargetSkeletalMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Target Mesh", meta = (TransientToolProperty, EditCondition = "TargetSkeletalMesh != nullptr", EditConditionHides))` — Target mesh to sample to
- L52 _public member_ `TObjectPtr<AActor> TargetDynamicMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Target Mesh", meta = (TransientToolProperty, EditCondition = "TargetDynamicMesh != nullptr", EditConditionHides))` — Target mesh to sample to
- L58 _public member_ `FString TargetUVLayer;` — `UPROPERTY(EditAnywhere, Category = BakeInput, meta = (DisplayName = "Target Mesh UV Channel", GetOptions = GetTargetUVLayerNamesFunc, TransientToolProperty, NoResetToDefault, EditCondition = "bHasTargetUVLayer == true", EditConditionHides, HideEditConditionToggle))` — UV channel to use for the target mesh
- L62 _public member_ `bool bHasTargetUVLayer = false;` — `UPROPERTY()` — If true, expose the TargetUVLayer property
- L67 _public member_ `TObjectPtr<UStaticMesh> SourceStaticMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Source Mesh", meta = (TransientToolProperty, EditCondition = "SourceStaticMesh != nullptr", EditConditionHides))` — Source mesh to sample from
- L72 _public member_ `TObjectPtr<USkeletalMesh> SourceSkeletalMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Source Mesh", meta = (TransientToolProperty, EditCondition = "SourceSkeletalMesh != nullptr", EditConditionHides))` — Source mesh to sample from
- L77 _public member_ `TObjectPtr<AActor> SourceDynamicMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Source Mesh", meta = (TransientToolProperty, EditCondition = "SourceDynamicMesh != nullptr", EditConditionHides))` — Source mesh to sample from
- L82 _public member_ `bool bHideSourceMesh = false;` — `UPROPERTY(EditAnywhere, Category = BakeInput, meta = (EditConditionHides, HideEditConditionToggle, EditCondition = "SourceStaticMesh != nullptr || SourceSkeletalMesh != nullptr || SourceDynamicMesh != nullptr"))` — If true, hide the source mesh
- L87 _public member_ `TObjectPtr<UTexture2D> SourceNormalMap = nullptr;` — `UPROPERTY(EditAnywhere, Category = BakeInput, AdvancedDisplay, meta = (TransientToolProperty, EditCondition = "bHasSourceNormalMap == true", EditConditionHides, HideEditConditionToggle))` — Source mesh normal map; if empty, the geometric normals will be used
- L93 _public member_ `FString SourceNormalMapUVLayer;` — `UPROPERTY(EditAnywhere, Category = BakeInput, AdvancedDisplay, meta = (DisplayName = "Source Normal UV Channel", GetOptions = GetSourceUVLayerNamesFunc, TransientToolProperty, NoResetToDefault, EditCondition = "bHasSourceNormalMap == true", EditConditionHides, HideEditConditionToggle))` — UV channel to use for the source mesh normal map; only relevant if a source normal map is set
- L98 _public member_ `EBakeNormalSpace SourceNormalSpace = EBakeNormalSpace::Tangent;` — `UPROPERTY(EditAnywhere, Category = BakeInput, AdvancedDisplay, meta = (TransientToolProperty, EditCondition = "bHasSourceNormalMap == true", EditConditionHides, HideEditConditionToggle))` — Normal space of the source mesh normal map.
- L102 _public member_ `bool bHasSourceNormalMap = false;` — `UPROPERTY()` — If true, expose the SourceNormalMap and SourceNormalMapUVLayer properties
- L108 _public member_ `float ProjectionDistance = 3.0;` — `UPROPERTY(EditAnywhere, Category = BakeInput, meta = (ClampMin = "0.001", EditCondition = "SourceStaticMesh != nullptr || SourceSkeletalMesh != nullptr || SourceDynamicMesh != nullptr", HideEditConditionToggle))` — Maximum allowed distance for the projection from target mesh to source mesh for the sample to be considered valid. This is only relevant if a separate source mesh is provided.
- L114 _public member_ `bool bProjectionInWorldSpace = false;` — `UPROPERTY(EditAnywhere, Category = BakeInput, meta = ( EditCondition = "SourceStaticMesh != nullptr || SourceSkeletalMesh != nullptr || SourceDynamicMesh != nullptr", HideEditConditionToggle))` — If true, uses the world space positions for the projection from target mesh to source mesh, otherwise it uses their object space positions. This is only relevant if a separate source mesh is provided.
- L117 _public function_ `const TArray<FString>& GetTargetUVLayerNamesFunc() const` — `UFUNCTION()`
- L123 _public member_ `TArray<FString> TargetUVLayerNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L126 _public function_ `const TArray<FString>& GetSourceUVLayerNamesFunc() const` — `UFUNCTION()`
- L132 _public member_ `TArray<FString> SourceUVLayerNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UBakeNormalMapToolProperties`  
`class UBakeNormalMapToolProperties : public UInteractiveToolPropertySet`  
_L137-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`

#### class `UBakeOcclusionMapToolProperties`  
`class UBakeOcclusionMapToolProperties : public UInteractiveToolPropertySet`  
_L146-169_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L152 _public member_ `int32 OcclusionRays = 16;` — `UPROPERTY(EditAnywhere, Category = OcclusionOutput, meta = (UIMin = "1", UIMax = "1024", ClampMin = "1", ClampMax = "65536"))` — Number of occlusion rays per sample
- L156 _public member_ `float MaxDistance = 0.0f;` — `UPROPERTY(EditAnywhere, Category = OcclusionOutput, meta = (UIMin = "0.0", UIMax = "1000.0", ClampMin = "0.0", ClampMax = "99999999.0"))` — Maximum distance for occlusion rays to test for intersections; a value of 0 means infinity
- L160 _public member_ `float SpreadAngle = 180.0f;` — `UPROPERTY(EditAnywhere, Category = OcclusionOutput, meta = (UIMin = "0", UIMax = "180.0", ClampMin = "0", ClampMax = "180.0"))` — Maximum spread angle in degrees for occlusion rays; for example, 180 degrees will cover the entire hemisphere whereas 90 degrees will only cover the center of the hemisphere down to 45 degrees from the horizon.
- L164 _public member_ `float BiasAngle = 15.0f;` — `UPROPERTY(EditAnywhere, Category = OcclusionOutput, meta = (UIMin = "0", UIMax = "45.0", ClampMin = "0", ClampMax = "89.9"))` — Angle in degrees from the horizon for occlusion rays for which the contribution is attenuated to reduce faceting artifacts.
- L168 _public member_ `EBakeNormalSpace NormalSpace = EBakeNormalSpace::Tangent;` — `UPROPERTY(EditAnywhere, Category = OcclusionOutput)` — Normal space for Bent Normal bakes.

#### enum `EBakeCurvatureTypeMode`  
`enum class EBakeCurvatureTypeMode`  
_L173-183_
- reflection: `UENUM()`
- L176 _public enumerator_ `MeanAverage UMETA(DisplayName = "Mean")` — Average of the minimum and maximum principal curvatures
- L178 _public enumerator_ `Max` — Maximum principal curvature
- L180 _public enumerator_ `Min` — Minimum principal curvature
- L182 _public enumerator_ `Gaussian` — Product of the minimum and maximum principal curvatures

#### enum `EBakeCurvatureColorMode`  
`enum class EBakeCurvatureColorMode`  
_L187-195_
- reflection: `UENUM()`
- L190 _public enumerator_ `Grayscale` — Map curvature values to grayscale such that black is negative, grey is zero, and white is positive
- L192 _public enumerator_ `RedBlue` — Map curvature values to red and blue such that red is negative, black is zero, and blue is positive
- L194 _public enumerator_ `RedGreenBlue` — Map curvature values to red, green, blue such that red is negative, green is zero, and blue is positive

#### enum `EBakeCurvatureClampMode`  
`enum class EBakeCurvatureClampMode`  
_L199-207_
- reflection: `UENUM()`
- L202 _public enumerator_ `None` — Include both negative and positive curvatures
- L204 _public enumerator_ `OnlyPositive` — Clamp negative curvatures to zero
- L206 _public enumerator_ `OnlyNegative` — Clamp positive curvatures to zero

#### class `UBakeCurvatureMapToolProperties`  
`class UBakeCurvatureMapToolProperties : public UInteractiveToolPropertySet`  
_L211-234_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L217 _public member_ `EBakeCurvatureTypeMode CurvatureType = EBakeCurvatureTypeMode::MeanAverage;` — `UPROPERTY(EditAnywhere, Category = CurvatureOutput)` — Type of curvature
- L221 _public member_ `EBakeCurvatureColorMode ColorMapping = EBakeCurvatureColorMode::Grayscale;` — `UPROPERTY(EditAnywhere, Category = CurvatureOutput)` — How to map calculated curvature values to colors
- L225 _public member_ `float ColorRangeMultiplier = 1.0;` — `UPROPERTY(EditAnywhere, Category = CurvatureOutput, meta = (UIMin = "0.1", UIMax = "2.0", ClampMin = "0.001", ClampMax = "100.0"))` — Multiplier for how the curvature values fill the available range in the selected Color Mapping; a larger value means that higher curvature is required to achieve the maximum color value.
- L229 _public member_ `float MinRangeMultiplier = 0.0;` — `UPROPERTY(EditAnywhere, Category = CurvatureOutput, AdvancedDisplay, meta = (DisplayName = "Color Range Minimum", UIMin = "0.0", UIMax = "1.0"))` — Minimum for the curvature values to not be clamped to zero relative to the curvature for the maximum color value; a larger value means that higher curvature is required to not be considered as no curvature.
- L233 _public member_ `EBakeCurvatureClampMode Clamping = EBakeCurvatureClampMode::None;` — `UPROPERTY(EditAnywhere, Category = CurvatureOutput)` — Clamping applied to curvature values before color mapping

#### class `UBakeUVShellMapToolProperties`  
`class UBakeUVShellMapToolProperties : public UInteractiveToolPropertySet`  
_L238-261_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L244 _public member_ `int UVLayer = 0;` — `UPROPERTY(EditAnywhere, Category = "UV Shell Output")` — The source mesh UV Layer to sample.
- L248 _public member_ `float WireframeThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "UV Shell Output")` — The thickness of the wireframe in pixels.
- L252 _public member_ `FLinearColor WireframeColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "UV Shell Output")` — The color of wireframe pixels.
- L256 _public member_ `FLinearColor ShellColor = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "UV Shell Output")` — The color of the UV shell interior pixels.
- L260 _public member_ `FLinearColor BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, Category = "UV Shell Output")` — The color of pixels external to UV shells.

#### enum `EBakeHeightRangeMode`  
`enum class EBakeHeightRangeMode`  
_L265-271_
- reflection: `UENUM()`
- L268 _public enumerator_ `Absolute` — Height range defined in absolute units in object space
- L270 _public enumerator_ `RelativeBounds` — Height range defined as a ratio of the maximal bounding box axis

#### class `UBakeHeightMapToolProperties`  
`class UBakeHeightMapToolProperties : public UInteractiveToolPropertySet`  
_L275-298_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L281 _public member_ `EBakeHeightRangeMode HeightRangeMode = EBakeHeightRangeMode::Absolute;` — `UPROPERTY(EditAnywhere, Category = HeightOutput)` — The coordinate space to compute height
- L285 _public member_ `float InnerDistance = -1.0f;` — `UPROPERTY(EditAnywhere, Category = HeightOutput, meta=(EditConditionHides,EditCondition="HeightRangeMode == EBakeHeightRangeMode::Absolute", UIMin=-100.0f, UIMax=100.0f))` — The inner height map distance from the low poly mesh, in object space units. This value maps to black.
- L289 _public member_ `float OuterDistance = 1.0f;` — `UPROPERTY(EditAnywhere, Category = HeightOutput, meta=(EditConditionHides,EditCondition="HeightRangeMode == EBakeHeightRangeMode::Absolute", UIMin=-100.0f, UIMax=100.0f))` — The outer height map distance from the low poly mesh, in object space units. This value maps to white.
- L293 _public member_ `float InnerBoundsDistance = -0.1f;` — `UPROPERTY(EditAnywhere, Category = HeightOutput, meta=(EditConditionHides,EditCondition="HeightRangeMode == EBakeHeightRangeMode::RelativeBounds", ClampMin=-1.0f, ClampMax=1.0f))` — The inner height map distance from the low poly mesh, as a ratio of the maximum bounding box axis. This value maps to black.
- L297 _public member_ `float OuterBoundsDistance = 0.1f;` — `UPROPERTY(EditAnywhere, Category = HeightOutput, meta=(EditConditionHides,EditCondition="HeightRangeMode == EBakeHeightRangeMode::RelativeBounds", ClampMin=-1.0f, ClampMax=1.0f))` — The outer height map distance from the low poly mesh, as a ratio of the maximum bounding box axis. This value maps to white.

#### class `UBakeTexture2DProperties`  
`class UBakeTexture2DProperties : public UInteractiveToolPropertySet`  
_L302-323_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L308 _public member_ `TObjectPtr<UTexture2D> SourceTexture;` — `UPROPERTY(EditAnywhere, Category = TextureOutput, meta = (TransientToolProperty))` — Source mesh texture that is to be resampled into a new texture
- L313 _public member_ `FString UVLayer;` — `UPROPERTY(EditAnywhere, Category = TextureOutput, meta = (DisplayName = "Source Texture UV Channel", GetOptions = GetUVLayerNamesFunc, NoResetToDefault))` — UV channel to use for the source mesh texture
- L316 _public function_ `const TArray<FString>& GetUVLayerNamesFunc() const` — `UFUNCTION()`
- L322 _public member_ `TArray<FString> UVLayerNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UBakeMultiTexture2DProperties`  
`class UBakeMultiTexture2DProperties : public UInteractiveToolPropertySet`  
_L327-356_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L335 _public member_ `TArray<TObjectPtr<UTexture2D>> MaterialIDSourceTextures;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = MultiTextureOutput, meta = (DisplayName = "Material IDs", TransientToolProperty, EditFixedOrder))` — For each material ID, the source texture that will be resampled in that material's region
- L340 _public member_ `FString UVLayer;` — `UPROPERTY(EditAnywhere, Category = MultiTextureOutput, meta = (DisplayName = "Source Texture UV Channel", GetOptions = GetUVLayerNamesFunc, NoResetToDefault))` — UV channel to use for the source mesh texture
- L343 _public function_ `const TArray<FString>& GetUVLayerNamesFunc() const` — `UFUNCTION()`
- L349 _public member_ `TArray<FString> UVLayerNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L354 _public member_ `TArray<TObjectPtr<UTexture2D>> AllSourceTextures;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MultiTextureOutput, meta = (DisplayName = "Source Textures", TransientToolProperty))` — The set of all source textures from all input materials

#### class `UBakeVisualizationProperties`  
`class UBakeVisualizationProperties : public UInteractiveToolPropertySet`  
_L360-376_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L366 _public member_ `bool bPreviewAsMaterial = false;` — `UPROPERTY(EditAnywhere, Category = Preview)` — Preview the texture as an input to the respective material parameter (ex. Normal, Ambient Occlusion)
- L370 _public member_ `float Brightness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Preview, meta = (DisplayName = "Brightness", UIMin = "0.0", UIMax = "1.0"))` — Adjust the brightness of the preview material; does not affect results stored in textures
- L375 _public member_ `float AOMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Preview, meta = (DisplayName = "AO Multiplier", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Ambient Occlusion multiplier in the viewport; does not affect results stored in textures

#### struct `FDetailMeshSettings`  
`struct FDetailMeshSettings`  
_L383-392_
- L385 _public member_ `int32 UVLayer = 0;`
- L386 _public member_ `EBakeNormalSpace NormalSpace = EBakeNormalSpace::Tangent;`
- L388 _public function_ `bool operator==(const FDetailMeshSettings& Other) const`

#### struct `FNormalMapSettings`  
`struct FNormalMapSettings`  
_L394-402_
- L396 _public member_ `FImageDimensions Dimensions;`
- L398 _public function_ `bool operator==(const FNormalMapSettings& Other) const`

#### struct `FOcclusionMapSettings`  
`struct FOcclusionMapSettings`  
_L404-422_
- L406 _public member_ `FImageDimensions Dimensions;`
- L407 _public member_ `int32 OcclusionRays;`
- L408 _public member_ `float MaxDistance;`
- L409 _public member_ `float SpreadAngle;`
- L410 _public member_ `float BiasAngle;`
- L411 _public member_ `EBakeNormalSpace NormalSpace = EBakeNormalSpace::Tangent;`
- L413 _public function_ `bool operator==(const FOcclusionMapSettings& Other) const`

#### struct `FCurvatureMapSettings`  
`struct FCurvatureMapSettings`  
_L424-437_
- L426 _public member_ `FImageDimensions Dimensions;`
- L427 _public member_ `int32 CurvatureType = 0;`
- L428 _public member_ `float RangeMultiplier = 1.0f;`
- L429 _public member_ `float MinRangeMultiplier = 0.0f;`
- L430 _public member_ `int32 ColorMode = 0;`
- L431 _public member_ `int32 ClampMode = 0;`
- L433 _public function_ `bool operator==(const FCurvatureMapSettings& Other) const`

#### struct `FMeshPropertyMapSettings`  
`struct FMeshPropertyMapSettings`  
_L439-447_
- L441 _public member_ `FImageDimensions Dimensions;`
- L443 _public function_ `bool operator==(const FMeshPropertyMapSettings& Other) const`

#### struct `FHeightMapSettings`  
`struct FHeightMapSettings`  
_L449-467_
- L451 _public member_ `FImageDimensions Dimensions;`
- L452 _public member_ `int32 HeightRangeMode = 0;`
- L453 _public member_ `float InnerDistance = -1.0f;`
- L454 _public member_ `float OuterDistance = 1.0f;`
- L455 _public member_ `float InnerBoundsDistance = -0.1f;`
- L456 _public member_ `float OuterBoundsDistance = 0.1f;`
- L458 _public function_ `bool operator==(const FHeightMapSettings& Other) const`

#### struct `FUVShellMapSettings`  
`struct FUVShellMapSettings`  
_L469-487_
- L471 _public member_ `FImageDimensions Dimensions;`
- L472 _public member_ `int UVLayer = 0;`
- L473 _public member_ `float WireframeThickness = 1.0f;`
- L474 _public member_ `FLinearColor WireframeColor = FLinearColor::Blue;`
- L475 _public member_ `FLinearColor ShellColor = FLinearColor::Gray;`
- L476 _public member_ `FLinearColor BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);`
- L478 _public function_ `bool operator==(const FUVShellMapSettings& Other) const`

#### struct `FTexture2DSettings`  
`struct FTexture2DSettings`  
_L489-498_
- L491 _public member_ `FImageDimensions Dimensions;`
- L492 _public member_ `int32 UVLayer = 0;`
- L494 _public function_ `bool operator==(const FTexture2DSettings& Other) const`

#### enum `EBakeOpState`  
`enum class EBakeOpState`  
_L504-510_
- desc: Bake compute state
- L506 _public enumerator_ `Clean = 0` — No-op - evaluation already launched/complete.
- L507 _public enumerator_ `Evaluate = 1 << 0` — Inputs are modified and valid, re-evaluate.
- L508 _public enumerator_ `EvaluateDetailMesh = 1 << 1` — Detail mesh input is modified, re-evaluate the detail mesh.
- L509 _public enumerator_ `Invalid = 1 << 2` — Inputs are modified and invalid - retry eval until valid.

#### Free symbols / members of external scopes

- L511 _prototype_ `ENUM_CLASS_FLAGS(EBakeOpState);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/BakeMeshAttributeVertexTool.h` (Public)


#### class `UBakeMeshAttributeVertexToolBuilder`  
`class UBakeMeshAttributeVertexToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L28-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- desc: Tool Builder
- L32 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L33 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### enum `EBakeVertexTopology`  
`enum class EBakeVertexTopology`  
_L38-44_
- reflection: `UENUM()`
- L41 _public enumerator_ `CreateNew` — Generate new vertex color topology, optionally using normal and UV seams to determine splits
- L43 _public enumerator_ `UseExisting` — Use existing vertex color topology on the Target Mesh

#### enum `EBakeVertexOutput`  
`enum class EBakeVertexOutput`  
_L48-54_
- reflection: `UENUM()`
- L51 _public enumerator_ `RGBA` — Bake vertex data to RGBA
- L53 _public enumerator_ `PerChannel` — Bake vertex data to individual color channels

#### enum `EBakeVertexChannel`  
`enum class EBakeVertexChannel`  
_L58-65_
- reflection: `UENUM()`
- L60 _public enumerator_ `R`
- L61 _public enumerator_ `G`
- L62 _public enumerator_ `B`
- L63 _public enumerator_ `A`
- L64 _public enumerator_ `RGBA`

#### class `UBakeMeshAttributeVertexToolProperties`  
`class UBakeMeshAttributeVertexToolProperties : public UInteractiveToolPropertySet`  
_L69-128_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L76 _public member_ `EBakeVertexOutput OutputMode = EBakeVertexOutput::RGBA;` — `UPROPERTY(EditAnywhere, Category = BakeOutput)` — The bake output mode
- L83 _public member_ `int32 OutputType = static_cast<int32>(EBakeMapType::TangentSpaceNormal);` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta=(Bitmask, BitmaskEnum = "/Script/MeshModelingToolsExp.EBakeMapType", DisplayName="Source Type", ValidEnumValues="TangentSpaceNormal, AmbientOcclusion, BentNormal, Curvature, Texture, ObjectSpaceNormal, FaceNormal, Position, MaterialID, PolyGroupID, MultiTexture, VertexColor, Height", EditCondition="OutputMode == EBakeVertexOutput::RGBA", EditConditionHides))` — The source data to bake to vertex colors
- L90 _public member_ `int32 OutputTypeR = static_cast<int32>(EBakeMapType::None);` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta=(Bitmask, BitmaskEnum = "/Script/MeshModelingToolsExp.EBakeMapType", DisplayName="Source Type R", ValidEnumValues="None, AmbientOcclusion, Curvature, Height, One, Zero", EditCondition="OutputMode == EBakeVertexOutput::PerChannel", EditConditionHides))` — The source data to bake to the Red channel
- L97 _public member_ `int32 OutputTypeG = static_cast<int32>(EBakeMapType::None);` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta=(Bitmask, BitmaskEnum = "/Script/MeshModelingToolsExp.EBakeMapType", DisplayName="Source Type G", ValidEnumValues="None, AmbientOcclusion, Curvature, Height, One, Zero", EditCondition="OutputMode == EBakeVertexOutput::PerChannel", EditConditionHides))` — The source data to bake to the Green channel
- L104 _public member_ `int32 OutputTypeB = static_cast<int32>(EBakeMapType::None);` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta=(Bitmask, BitmaskEnum = "/Script/MeshModelingToolsExp.EBakeMapType", DisplayName="Source Type B", ValidEnumValues="None, AmbientOcclusion, Curvature, Height, One, Zero", EditCondition="OutputMode == EBakeVertexOutput::PerChannel", EditConditionHides))` — The source data to bake to the Blue channel
- L111 _public member_ `int32 OutputTypeA = static_cast<int32>(EBakeMapType::None);` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta=(Bitmask, BitmaskEnum = "/Script/MeshModelingToolsExp.EBakeMapType", DisplayName="Source Type A", ValidEnumValues="None, AmbientOcclusion, Curvature, Height, One, Zero", EditCondition="OutputMode == EBakeVertexOutput::PerChannel", EditConditionHides))` — The source data to bake to the Alpha channel
- L115 _public member_ `EBakeVertexChannel PreviewMode = EBakeVertexChannel::RGBA;` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta = (TransientToolProperty))` — The vertex color channel to preview
- L119 _public member_ `EBakeVertexTopology TopologyMode = EBakeVertexTopology::CreateNew;` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta = (TransientToolProperty))` — The vertex color topology to use for the bake
- L123 _public member_ `bool bSplitAtNormalSeams = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = BakeOutput, meta=(EditCondition="TopologyMode == EBakeVertexTopology::CreateNew"))` — If true, compute a separate vertex color for each unique normal on a vertex
- L127 _public member_ `bool bSplitAtUVSeams = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = BakeOutput, meta=(DisplayName = "Split at UV Seams", EditCondition="TopologyMode == EBakeVertexTopology::CreateNew"))` — If true, Compute a separate vertex color for each unique UV on a vertex.

#### class `UBakeMeshAttributeVertexTool`  
`class UBakeMeshAttributeVertexTool : public UBakeMeshAttributeTool, public UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshVertexBaker>`  
_L135-276_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBakeMeshAttributeTool,UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshVertexBaker>`
- desc: Vertex Baking Tool
- L140 _public prototype_ `UBakeMeshAttributeVertexTool() = default;`
- L143 _public prototype_ `virtual void Setup() override;`
- L144 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L146 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L147 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L149 _public function_ `virtual bool HasCancel() const override`
- L150 _public function_ `virtual bool HasAccept() const override`
- L151 _public prototype_ `virtual bool CanAccept() const override;`
- L155 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<UE::Geometry::FMeshVertexBaker>> MakeNewOperator() override;`
- L160 _protected member_ `TObjectPtr<UBakeInputMeshProperties> InputMeshSettings;` — `UPROPERTY()`
- L163 _protected member_ `TObjectPtr<UBakeMeshAttributeVertexToolProperties> Settings;` — `UPROPERTY()`
- L169 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L172 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewMaterial;` — `UPROPERTY()`
- L175 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PreviewAlphaMaterial;` — `UPROPERTY()`
- L177 _protected member_ `TUniquePtr<TGenericDataBackgroundCompute<UE::Geometry::FMeshVertexBaker>> Compute = nullptr;`
- L178 _protected prototype_ `void OnResultUpdated(const TUniquePtr<UE::Geometry::FMeshVertexBaker>& NewResult);`
- L180 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> DetailMesh;`
- L181 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> DetailSpatial;`
- L182 _protected member_ `int32 DetailMeshTimestamp = 0;`
- L183 _protected prototype_ `void UpdateDetailMesh();`
- L185 _protected member_ `int32 NumColorElements = 0;`
- L186 _protected member_ `bool bColorTopologyValid = false;`
- L187 _protected member_ `bool bIsBakeToSelf = false;`
- L188 _protected prototype_ `void UpdateOnModeChange();`
- L189 _protected prototype_ `void UpdateVisualization();`
- L190 _protected prototype_ `void UpdateColorTopology();`
- L191 _protected prototype_ `void UpdateSourceVertexColors();`
- L192 _protected prototype_ `void UpdateResult();`
- L221 _protected member_ `FBakeSettings CachedBakeSettings;`
- L223 _protected function_ `void SetSourceObjectVisible(bool bState)`
- L252 _protected member_ `FBakeAnalytics BakeAnalytics;`
- L258 _protected prototype_ `virtual void GatherAnalytics(FBakeAnalytics::FMeshSettings& Data);` — Computes the NumTargetMeshTris, NumDetailMesh and NumDetailMeshTris analytics. @param Data the mesh analytics data to compute
- L266 _protected prototype_ `static void GatherAnalytics(const UE::Geometry::FMeshVertexBaker& Result, const FBakeSettings& Settings, FBakeAnalytics& Data);` — Records bake timing and settings data for analytics. @param Result the result of the bake. @param Settings The bake settings used for the bake. @param Data the output bake analytics struct.
- L275 _protected prototype_ `static void RecordAnalytics(const FBakeAnalytics& Data, const FString& EventName);` — Outputs an analytics event using the given analytics struct. @param Data the bake analytics struct to output. @param EventName the name of the analytics event to output.

#### struct `UBakeMeshAttributeVertexTool::FBakeSettings`  
`struct FBakeSettings`  
_L194-220_
- L196 _public member_ `EBakeVertexOutput OutputMode = EBakeVertexOutput::RGBA;`
- L197 _public member_ `EBakeMapType OutputType = EBakeMapType::TangentSpaceNormal;`
- L198 _public member_ `EBakeMapType OutputTypePerChannel[4] = { EBakeMapType::None, EBakeMapType::None, EBakeMapType::None, EBakeMapType::None };`
- L199 _public member_ `EBakeVertexChannel PreviewMode = EBakeVertexChannel::RGBA;`
- L200 _public member_ `EBakeVertexTopology TopologyMode = EBakeVertexTopology::CreateNew;`
- L201 _public member_ `float ProjectionDistance = 3.0;`
- L202 _public member_ `bool bProjectionInWorldSpace = false;`
- L203 _public member_ `bool bSplitAtNormalSeams = false;`
- L204 _public member_ `bool bSplitAtUVSeams = false;`
- L206 _public function_ `bool operator==(const FBakeSettings& Other) const`

#### struct `UBakeMeshAttributeVertexTool::FBakeAnalytics`  
`struct FBakeAnalytics`  
_L235-251_
- desc: Analytics
- L237 _public member_ `double TotalBakeDuration = 0.0;`
- L246 _public member_ `FMeshSettings MeshSettings;`
- L248 _public member_ `FBakeSettings BakeSettings;`
- L249 _public member_ `FOcclusionMapSettings OcclusionSettings;`
- L250 _public member_ `FCurvatureMapSettings CurvatureSettings;`

#### struct `UBakeMeshAttributeVertexTool::FBakeAnalytics::FMeshSettings`  
`struct FMeshSettings`  
_L239-245_
- L241 _public member_ `int32 NumTargetMeshVerts = 0;`
- L242 _public member_ `int32 NumTargetMeshTris = 0;`
- L243 _public member_ `int32 NumDetailMesh = 0;`
- L244 _public member_ `int64 NumDetailMeshTris = 0;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/BakeMultiMeshAttributeMapsTool.h` (Public)


#### class `UBakeMultiMeshAttributeMapsToolBuilder`  
`class UBakeMultiMeshAttributeMapsToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L25-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- desc: Tool Builder
- L30 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L31 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L34 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UBakeMultiMeshAttributeMapsToolProperties`  
`class UBakeMultiMeshAttributeMapsToolProperties : public UInteractiveToolPropertySet`  
_L39-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L47 _public member_ `int32 MapTypes = (int32) EBakeMapType::None;` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta=(DisplayName="Output Types", Bitmask, BitmaskEnum= "/Script/MeshModelingToolsExp.EBakeMapType", ValidEnumValues="TangentSpaceNormal, ObjectSpaceNormal, Position, Texture"))` — The map types to generate
- L52 _public member_ `FString MapPreview;` — `UPROPERTY(EditAnywhere, Category = BakeOutput, meta=(DisplayName="Preview Output Type", TransientToolProperty, GetOptions = GetMapPreviewNamesFunc, EditCondition = "MapTypes != 0", NoResetToDefault))` — The map type index to preview
- L56 _public member_ `EBakeTextureResolution Resolution = EBakeTextureResolution::Resolution256;` — `UPROPERTY(EditAnywhere, Category = Textures)` — The pixel resolution of the generated map
- L60 _public member_ `EBakeTextureBitDepth BitDepth = EBakeTextureBitDepth::ChannelBits8;` — `UPROPERTY(EditAnywhere, Category = Textures)` — The channel bit depth of the source data for the generated textures
- L64 _public member_ `EBakeTextureSamplesPerPixel SamplesPerPixel = EBakeTextureSamplesPerPixel::Sample1;` — `UPROPERTY(EditAnywhere, Category = Textures)` — Number of samples per pixel
- L68 _public member_ `TObjectPtr<UTexture2D> SampleFilterMask = nullptr;` — `UPROPERTY(EditAnywhere, Category = Textures, AdvancedDisplay)` — Mask texture for filtering out samples/pixels from the output texture
- L71 _public function_ `const TArray<FString>& GetMapPreviewNamesFunc()` — `UFUNCTION()`
- L76 _public member_ `TArray<FString> MapPreviewNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L77 _public member_ `TMap<FString, FString> MapPreviewNamesMap;`

#### struct `FBakeMultiMeshDetailProperties`  
`struct FBakeMultiMeshDetailProperties`  
_L82-99_
- reflection: `USTRUCT()`
- L88 _public member_ `TObjectPtr<UStaticMesh> SourceMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeSources, meta = (TransientToolProperty))` — Source mesh to sample from
- L93 _public member_ `TObjectPtr<UTexture2D> SourceTexture = nullptr;` — `UPROPERTY(EditAnywhere, Category = BakeSources, meta = (TransientToolProperty, EditCondition="SourceMesh != nullptr"))` — Source mesh color texture that is to be resampled into a new texture
- L98 _public member_ `int32 SourceTextureUVLayer = 0;` — `UPROPERTY(EditAnywhere, Category = BakeSources, meta = (TransientToolProperty, DisplayName = "Source Texture UV Channel", EditCondition="SourceTexture != nullptr", ClampMin=0, ClampMax=7))` — UV channel to use for the source mesh color texture

#### class `UBakeMultiMeshInputToolProperties`  
`class UBakeMultiMeshInputToolProperties : public UInteractiveToolPropertySet`  
_L103-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L111 _public member_ `TObjectPtr<UStaticMesh> TargetStaticMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Target Mesh", meta = (TransientToolProperty, EditCondition = "TargetStaticMesh != nullptr", EditConditionHides))` — Target mesh to sample to
- L116 _public member_ `TObjectPtr<USkeletalMesh> TargetSkeletalMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Target Mesh", meta = (TransientToolProperty, EditCondition = "TargetSkeletalMesh != nullptr", EditConditionHides))` — Target mesh to sample to
- L121 _public member_ `TObjectPtr<AActor> TargetDynamicMesh = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = BakeInput, DisplayName = "Target Mesh", meta = (TransientToolProperty, EditCondition = "TargetDynamicMesh != nullptr", EditConditionHides))` — Target mesh to sample to
- L126 _public member_ `FString TargetUVLayer;` — `UPROPERTY(EditAnywhere, Category = BakeInput, meta = (DisplayName = "Target Mesh UV Channel", GetOptions = GetTargetUVLayerNamesFunc, TransientToolProperty, NoResetToDefault))` — UV channel to use for the target mesh
- L130 _public member_ `TArray<FBakeMultiMeshDetailProperties> SourceMeshes;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = BakeInput, meta = (TransientToolProperty, EditFixedOrder, NoResetToDefault))` — Source meshes and textures to sample from
- L135 _public member_ `float ProjectionDistance = 3.0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = BakeInput, meta = (ClampMin = "0.001"))` — Maximum allowed distance for the projection from target mesh to source mesh for the sample to be considered valid. This is only relevant if a separate source mesh is provided.
- L138 _public function_ `const TArray<FString>& GetTargetUVLayerNamesFunc() const` — `UFUNCTION()`
- L144 _public member_ `TArray<FString> TargetUVLayerNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### struct `FBakeMultiMeshDetailSettings`  
`struct FBakeMultiMeshDetailSettings`  
_L148-163_
- L150 _public typedef_ `using FColorMapData = TTuple<int32, bool>;`
- L151 _public member_ `TArray<FColorMapData> ColorMapData;`
- L153 _public function_ `bool operator==(const FBakeMultiMeshDetailSettings& Other) const`

#### class `UBakeMultiMeshAttributeMapsTool`  
`class UBakeMultiMeshAttributeMapsTool : public UBakeMeshAttributeMapsToolBase`  
_L171-238_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBakeMeshAttributeMapsToolBase`
- desc: N-to-1 Detail Map Baking Tool
- L176 _public prototype_ `UBakeMultiMeshAttributeMapsTool() = default;`
- L179 _public prototype_ `virtual void Setup() override;`
- L180 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L182 _public function_ `virtual bool HasCancel() const override`
- L183 _public function_ `virtual bool HasAccept() const override`
- L184 _public prototype_ `virtual bool CanAccept() const override;`
- L188 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<UE::Geometry::FMeshMapBaker>> MakeNewOperator() override;`
- L196 _protected member_ `TObjectPtr<UBakeMultiMeshAttributeMapsToolProperties> Settings;` — `UPROPERTY()`
- L199 _protected member_ `TObjectPtr<UBakeMultiMeshInputToolProperties> InputMeshSettings;` — `UPROPERTY()`
- L202 _protected member_ `TObjectPtr<UBakeMeshAttributeMapsResultToolProperties> ResultSettings;` — `UPROPERTY()`
- L207 _protected prototype_ `virtual void UpdateResult() override;`
- L208 _protected prototype_ `virtual void UpdateVisualization() override;`
- L210 _protected prototype_ `virtual void GatherAnalytics(FBakeAnalytics::FMeshSettings& Data) override;`
- L217 _protected member_ `TSharedPtr<UE::Geometry::FMeshSceneAdapter, ESPMode::ThreadSafe> DetailMeshScene;`
- L219 _protected prototype_ `void UpdateOnModeChange();`
- L221 _protected prototype_ `void InvalidateResults();`
- L224 _protected member_ `FBakeMultiMeshDetailSettings CachedDetailSettings;` — Cached detail mesh data
- L225 _protected prototype_ `EBakeOpState UpdateResult_DetailMeshes();`
- L227 _protected typedef_ `using FTextureImageData = TTuple<UE::Geometry::TImageBuilder<FVector4f>*, int>;`
- L228 _protected typedef_ `using FTextureImageMap = TMap<void*, UE::Geometry::IMeshBakerDetailSampler::FBakeDetailTexture>;`
- L229 _protected member_ `TArray<TSharedPtr<UE::Geometry::TImageBuilder<FVector4f>>> CachedColorImages;`
- L230 _protected member_ `TArray<int> CachedColorUVLayers;`
- L231 _protected member_ `FTextureImageMap CachedMeshToColorImagesMap;`
- L234 _protected function_ `virtual FString GetAnalyticsEventName() const override` — Analytics

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/BakeToolUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L27 _prototype_ `void UpdateUVLayerNames(FString& UVLayer, TArray<FString>& UVLayerNamesList, const FDynamicMesh3& Mesh);` (scope `UE::Geometry`) — Updates a tool property set's UVLayerNamesList from the list of UV layers on a given mesh. Also updates the UVLayer property if the current UV layer is no longer available. @param UVLayer Selected UV Layer. @param UVLayerNamesList List of available UV layers. @param Mesh the mesh to query
- L29 _prototype_ `UPreviewMesh* CreateBakePreviewMesh(UObject* Tool, UToolTarget* ToolTarget, UWorld* World);` (scope `UE::Geometry`)
- L32 _prototype_ `AActor* GetTargetActorViaIPersistentDynamicMeshSource(UToolTarget* Target);` (scope `UE::Geometry`) — @return AActor that owns a DynamicMeshComponent from a tool target, or nullptr if there is no such Actor

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/BakeTransformTool.h` (Public)


#### class `UBakeTransformToolBuilder`  
`class UBakeTransformToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L26-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L30 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L33 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EBakeScaleMethod`  
`enum class EBakeScaleMethod : uint8`  
_L38-46_
- reflection: `UENUM()`
- L41 _public enumerator_ `BakeFullScale` — bake all scale information, so the component has scale of 1 on all axes
- L43 _public enumerator_ `BakeNonuniformScale` — bake the non-uniform scale, so the component has a uniform scale
- L45 _public enumerator_ `DoNotBakeScale` — do not bake any scaling

#### class `UBakeTransformToolProperties`  
`class UBakeTransformToolProperties : public UInteractiveToolPropertySet`  
_L53-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties
- L58 _public prototype_ `UBakeTransformToolProperties();`
- L62 _public member_ `bool bApplyToAllLODs = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — If checked, the baked transform will be applied to all available LODs. Has no effect on selections without LODs.
- L66 _public member_ `bool bBakeRotation = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Bake rotation
- L70 _public member_ `EBakeScaleMethod BakeScale = EBakeScaleMethod::BakeFullScale;` — `UPROPERTY(EditAnywhere, Category = Options)` — Bake scale
- L74 _public member_ `bool bRecenterPivot = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Recenter pivot after baking transform
- L79 _public member_ `bool bAllowNoScale = true;` — `UPROPERTY(VisibleAnywhere, Category = Options)` — This variable is used to enable/disable the "DoNotBakeScale" option in the BakeScale enum It is marked as visible only so that the FBakeTransformToolDetails can read it; it will be hidden by that DetailCustomization

#### class `UBakeTransformTool`  
`class UBakeTransformTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L88-116_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Simple tool to bake scene transform on meshes into the mesh assets
- L93 _public prototype_ `UBakeTransformTool();`
- L95 _public prototype_ `virtual void Setup() override;`
- L96 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L98 _public function_ `virtual bool HasCancel() const override`
- L99 _public function_ `virtual bool HasAccept() const override`
- L102 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L110 _protected member_ `TObjectPtr<UBakeTransformToolProperties> BasicProperties;` — `UPROPERTY()`
- L113 _protected member_ `TArray<int> MapToFirstOccurrences;`
- L115 _protected prototype_ `void UpdateAssets();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/ConvertMeshesTool.h` (Public)


#### class `UConvertMeshesToolBuilder`  
`class UConvertMeshesToolBuilder : public UInteractiveToolBuilder`  
_L20-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L24 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const;`
- L25 _private prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const;`

#### class `UConvertMeshesToolProperties`  
`class UConvertMeshesToolProperties : public UInteractiveToolPropertySet`  
_L32-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the Transfer operation
- L37 _public member_ `bool bTransferMaterials = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "bShowTransferMaterials == true", EditConditionHides, HideEditConditionToggle))`
- L41 _public member_ `bool bShowTransferMaterials = true;` — `UPROPERTY(meta = (TransientToolProperty))` — control whether the transfer materials option is displayed
- L44 _public member_ `bool bTransferCollision = true;` — `UPROPERTY(EditAnywhere, Category = Options)`

#### class `UConvertMeshesTool`  
`class UConvertMeshesTool : public UInteractiveTool,`  
_L50-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolExclusiveToolAPI`
- L57 _public prototype_ `virtual void Setup() override;`
- L58 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L60 _public function_ `virtual bool HasCancel() const override`
- L61 _public function_ `virtual bool HasAccept() const override`
- L62 _public prototype_ `virtual bool CanAccept() const override;`
- L65 _public member_ `TObjectPtr<UConvertMeshesToolProperties> BasicProperties;` — `UPROPERTY()`
- L68 _public member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()`
- L70 _public function_ `void InitializeInputs(TArray<TWeakObjectPtr<UPrimitiveComponent>>&& InInputs)`
- L75 _public function_ `void SetTargetLOD(EMeshLODIdentifier LOD)`
- L82 _private member_ `TArray<TWeakObjectPtr<UPrimitiveComponent>> Inputs;` — `UPROPERTY()`
- L84 _private member_ `EMeshLODIdentifier TargetLOD = EMeshLODIdentifier::Default;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/CubeGridTool.h` (Public)


#### class `UCubeGridToolBuilder`  
`class UCubeGridToolBuilder : public UInteractiveToolWithToolTargetsBuilder`  
_L47-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- L52 _public member_ `IAssetGenerationAPI* AssetAPI = nullptr;`
- L54 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L55 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L59 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `ECubeGridToolFaceSelectionMode`  
`enum class ECubeGridToolFaceSelectionMode`  
_L64-74_
- reflection: `UENUM()`
- L67 _public enumerator_ `OutsideBasedOnNormal` — Use hit normal to pick the outer face of the containing cell.
- L69 _public enumerator_ `InsideBasedOnNormal` — Use hit normal to pierce backward through the geometry to pick an inside face of the containing cell.
- L71 _public enumerator_ `OutsideBasedOnViewRay` — Use view ray to pick the outer face of the containing cell.
- L73 _public enumerator_ `InsideBasedOnViewRay` — Use view ray to pierce backward through the geometry to pick an inside face of the containing cell.

#### class `UCubeGridToolProperties`  
`class UCubeGridToolProperties : public UInteractiveToolPropertySet`  
_L78-223_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L86 _public member_ `FVector GridFrameOrigin = FVector(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "bAllowedToEditGrid", HideEditConditionToggle))`
- L91 _public member_ `FRotator GridFrameOrientation = FRotator(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "bAllowedToEditGrid", HideEditConditionToggle, UIMin = -180, UIMax = 180, ClampMin = -180000, ClampMax = 18000))`
- L94 _public member_ `bool bShowGrid = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L97 _public member_ `bool bShowGizmo = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (TransientToolProperty))`
- L100 _public member_ `const uint8 DEFAULT_GRID_POWER = 5;` — These are here so that we can reset the appropriate settings to their defaults in code.
- L101 _public member_ `const double DEFAULT_CURRENT_BLOCK_SIZE = 100;`
- L111 _public member_ `uint8 GridPower = DEFAULT_GRID_POWER;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "bAllowedToEditGrid", HideEditConditionToggle, UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "31"))` — Determines cube grid scale. Can also be adjusted with hotkeys. This changes Current Block Size to match the current Base Block Size and Grid Power (differently depending on the Power of Two setting).
- L120 _public member_ `double CurrentBlockSize = DEFAULT_CURRENT_BLOCK_SIZE;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "bAllowedToEditGrid", HideEditConditionToggle, UIMin = "1", UIMax = "1000", ClampMin = "0.001"))` — Sets the size of a block at the current grid power. This changes Base Block Size such that the given value is achieved at the the current value of Grid Power.
- L125 _public member_ `int32 BlocksPerStep = 1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( UIMin = "0", ClampMin = "0", Delta = 1, LinearDeltaSensitivity = 50))` — How many blocks each push/pull invocation will do at a time.
- L134 _public member_ `bool bPowerOfTwoBlockSizes = true;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay)` — When true, block sizes change by powers of two as Grid Power is changed. When false, block sizes change by twos and fives, much like the default editor grid snapping options (for instance, sizes might increase from 10 to 50 to 100 to 500). Note that toggling this option will reset Grid Power and Current Block Size to default values.
- L137 _public member_ `const uint8 MaxGridPower = 31;` — Must match ClampMax in GridPower, used to make hotkeys not exceed it.
- L144 _public member_ `double BlockBaseSize = 3.125;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = ( EditCondition = "bAllowedToEditGrid", HideEditConditionToggle, UIMin = "0.1", UIMax = "10", ClampMin = "0.001", ClampMax = "1000"))` — Smallest block size to use in the grid, i.e. the block size at Grid Power 0. This changes Current Block Size according to current value of Grid Power.
- L151 _public member_ `bool bCrosswiseDiagonal = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "bInCornerMode", HideEditConditionToggle))` — When pushing/pulling in a way where the diagonal matters, setting this to true makes the diagonal generally try to lie flat across the face rather than at an incline.
- L157 _public member_ `bool bKeepSideGroups = true;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay)` — When performing multiple push/pulls with the same selection, attempt to keep the same group IDs on the sides of the new geometry (ie multiple E/Q presses will not result in different group topology around the sides compared to a single Ctrl+drag).
- L161 _public member_ `bool bShowSelectionMeasurements = true;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay)` — When true, displays dimensions of the given selection in the viewport.
- L169 _public member_ `double PlaneTolerance = 0.01;` — `UPROPERTY()`
- L174 _public member_ `bool bHitUnrelatedGeometry = true;` — `UPROPERTY(EditAnywhere, Category = BlockSelection)` — When raycasting to find a selected grid face, this determines whether geometry in the scene that is not part of the edited mesh is hit.
- L179 _public member_ `bool bHitGridGroundPlaneIfCloser = false;` — `UPROPERTY(EditAnywhere, Category = BlockSelection, AdvancedDisplay)` — When the grid ground plane is above some geometry, whether we should hit that plane or pass through to the other geometry.
- L183 _public member_ `ECubeGridToolFaceSelectionMode FaceSelectionMode = ECubeGridToolFaceSelectionMode::OutsideBasedOnNormal;` — `UPROPERTY(EditAnywhere, Category = BlockSelection, AdvancedDisplay)` — How the selected face is determined.
- L186 _public member_ `FString ToggleCornerMode = TEXT("Z t` — `UPROPERTY(VisibleAnywhere, Category = ShortcutInfo)`
- L189 _public member_ `FString PushPull = TEXT("E/Q` — `UPROPERTY(VisibleAnywhere, Category = ShortcutInfo)`
- L192 _public member_ `FString ResizeGrid = #if PLATFORM_MAC TEXT("Opt` — `UPROPERTY(VisibleAnywhere, Category = ShortcutInfo)`
- L200 _public member_ `FString SlideSelection = TEXT("Middle mouse drag to slide selection in plane. " "Shi` — `UPROPERTY(VisibleAnywhere, Category = ShortcutInfo)`
- L204 _public member_ `FString FlipSelection = TEXT("T t` — `UPROPERTY(VisibleAnywhere, Category = ShortcutInfo)`
- L207 _public member_ `FString GridGizmo = TEXT("R t` — `UPROPERTY(VisibleAnywhere, Category = ShortcutInfo)`
- L210 _public member_ `FString QuickShiftGizmo = TEXT("Ctrl + middle click to quick-reposition " "the` — `UPROPERTY(VisibleAnywhere, Category = ShortcutInfo)`
- L214 _public member_ `FString AlignGizmo = TEXT("While dragging gizmo handles, hold Ctrl to align " "to` — `UPROPERTY(VisibleAnywhere, Category = ShortcutInfo)`
- L218 _public member_ `bool bInCornerMode = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L222 _public member_ `bool bAllowedToEditGrid = true;` — `UPROPERTY(meta = (TransientToolProperty))`

#### enum `ECubeGridToolAction`  
`enum class ECubeGridToolAction`  
_L226-240_
- reflection: `UENUM()`
- L228 _public enumerator_ `NoAction`
- L229 _public enumerator_ `Push`
- L230 _public enumerator_ `Pull`
- L231 _public enumerator_ `Flip`
- L232 _public enumerator_ `SlideForward`
- L233 _public enumerator_ `SlideBack`
- L234 _public enumerator_ `DecreaseGridPower`
- L235 _public enumerator_ `IncreaseGridPower`
- L236 _public enumerator_ `CornerMode`
- L238 _public enumerator_ `ResetFromActor` — FitGrid,
- L239 _public enumerator_ `AcceptAndStartNew`

#### class `UCubeGridToolActions`  
`class UCubeGridToolActions : public UInteractiveToolPropertySet`  
_L243-303_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L248 _public member_ `TWeakObjectPtr<UCubeGridTool> ParentTool;`
- L250 _public function_ `void Initialize(UCubeGridTool* ParentToolIn)`
- L252 _public prototype_ `void PostAction(ECubeGridToolAction Action);`
- L256 _public function_ `void Pull()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayPriority = 1))` — Can also be invoked with E.
- L260 _public function_ `void Push()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayPriority = 2))` — Can also be invoked with Q.
- L264 _public function_ `void SlideBack()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayPriority = 3))` — Can also be invoked with Shift + E.
- L268 _public function_ `void SlideForward()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayPriority = 4))` — Can also be invoked with Shift + Q.
- L274 _public function_ `void CornerMode()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayPriority = 5))` — Engages a mode where specific corners can be selected to push/pull only those corners. Press Apply to commit the result afterward. Can also be toggled with Z.
- L278 _public function_ `void Flip()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayPriority = 6))` — Can also be invoked with T.
- L283 _public member_ `TObjectPtr<AActor> GridSourceActor = nullptr;` — `UPROPERTY(EditAnywhere, Category = GridReinitialization, meta = (TransientToolProperty))`
- L292 _public function_ `void ResetGridFromActor ()` — `UFUNCTION(CallInEditor, Category = GridReinitialization)` — Resets the grid position and orientation based on the actor in Grid Source Actor. This allows grid positions/orientations to be saved by pasting them into the transform of some actor that is later used, or by relying on the fact that the tool initializes transforms of newly created meshes based on the grid used.
- L302 _public function_ `void AcceptAndStartNew()` — `UFUNCTION(CallInEditor, Category = AssetActions)` — Accepts the output of the current tool and restarts it in "create new asset" mode. Used to avoid creating one huge mesh when working on different parts of a level. Note that undoing object creation will not remove any created assets on disc (i.e. undoing the creation of a static mesh will remove the actor from the world but not remove the static mesh asset from disc).

#### class `UCubeGridTool`  
`class UCubeGridTool : public UInteractiveTool, public IClickDragBehaviorTarget, public IHoverBehaviorTarget, public UE::Geometry::IDynamicMeshOperatorFactory, public IInteractiveToolNestedAcceptCancelAPI, public IInteractiveToolCameraFocusAPI`  
_L307-631_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IClickDragBehaviorTarget,IHoverBehaviorTarget,UE::Geometry::IDynamicMeshOperatorFactory,IInteractiveToolNestedAcceptCancelAPI,IInteractiveToolCameraFocusAPI`
- desc: Tool that allows for blocky boolean operations on an orientable power-of-two grid.
- L336 _protected typedef_ `using FCubeGrid = UE::Geometry::FCubeGrid;`
- L362 _public function_ `virtual bool HasAccept() const override`
- L363 _public function_ `virtual bool CanAccept() const override`
- L364 _public function_ `virtual bool HasCancel() const override`
- L366 _public prototype_ `virtual void Setup() override;`
- L367 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L369 _public function_ `virtual void SetTarget(TObjectPtr<UToolTarget> TargetIn)`
- L370 _public function_ `virtual void SetWorld(UWorld* World)`
- L372 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L373 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L374 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L376 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L378 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L380 _public prototype_ `virtual void RequestAction(ECubeGridToolAction ActionType);`
- L382 _public prototype_ `virtual void SetSelection(const FSelection& Selection, bool bEmitChange);`
- L383 _public prototype_ `virtual void ClearSelection(bool bEmitChange);`
- L386 _public prototype_ `virtual void UpdateUsingMeshChange(const UE::Geometry::FDynamicMeshChange& MeshChange, bool bRevert);` — Used by undo/redo
- L387 _public prototype_ `virtual bool IsInDefaultMode() const;`
- L388 _public prototype_ `virtual bool IsInCornerMode() const;`
- L389 _public prototype_ `virtual void RevertToDefaultMode();`
- L390 _public prototype_ `virtual void SetChangesMade(bool bChangesMadeIn);`
- L391 _public prototype_ `virtual void SetCurrentMeshTransform(const FTransform& TransformIn);`
- L392 _public prototype_ `virtual void SetCurrentExtrudeAmount(int32 ExtrudeAmount);`
- L393 _public prototype_ `virtual void SetCornerSelection(bool CornerSelectedFlags[4]);`
- L396 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget
- L397 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L398 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L399 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L400 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L403 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget
- L404 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L405 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L406 _public prototype_ `virtual void OnEndHover() override;`
- L407 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L410 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L413 _public function_ `virtual bool SupportsNestedCancelCommand() override` — IInteractiveToolNestedAcceptCancelAPI
- L414 _public prototype_ `virtual bool CanCurrentlyNestedCancel() override;`
- L415 _public prototype_ `virtual bool ExecuteNestedCancelCommand() override;`
- L416 _public function_ `virtual bool SupportsNestedAcceptCommand() override`
- L417 _public prototype_ `virtual bool CanCurrentlyNestedAccept() override;`
- L418 _public prototype_ `virtual bool ExecuteNestedAcceptCommand() override;`
- L421 _public function_ `virtual bool SupportsWorldSpaceFocusBox()` — IInteractiveToolCameraFocusAPI
- L422 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;`
- L424 _public function_ `void SetInitialGridPivot(FVector3d PivotPos)`
- L430 _public prototype_ `bool CanApplyPreview() const;`
- L435 _protected member_ `TObjectPtr<UCombinedTransformGizmo> GridGizmo = nullptr;` — `UPROPERTY()`
- L438 _protected member_ `TObjectPtr<UDragAlignmentMechanic> GridGizmoAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L441 _protected member_ `TObjectPtr<UTransformProxy> GridGizmoTransformProxy = nullptr;` — `UPROPERTY()`
- L444 _protected member_ `TObjectPtr<UPreviewGeometry> LineSets = nullptr;` — `UPROPERTY()`
- L447 _protected member_ `TObjectPtr<UClickDragInputBehavior> ClickDragBehavior = nullptr;` — `UPROPERTY()`
- L450 _protected member_ `TObjectPtr<UMouseHoverBehavior> HoverBehavior = nullptr;` — `UPROPERTY()`
- L453 _protected member_ `TObjectPtr<ULocalSingleClickInputBehavior> CtrlMiddleClickBehavior = nullptr;` — `UPROPERTY()`
- L456 _protected member_ `TObjectPtr<ULocalClickDragInputBehavior> MiddleClickDragBehavior = nullptr;` — `UPROPERTY()`
- L460 _protected member_ `TObjectPtr<UCubeGridToolProperties> Settings = nullptr;` — `UPROPERTY()` — Properties, etc
- L463 _protected member_ `TObjectPtr<UCubeGridToolActions> ToolActions = nullptr;` — `UPROPERTY()`
- L466 _protected member_ `TObjectPtr<UNewMeshMaterialProperties> MaterialProperties = nullptr;` — `UPROPERTY()`
- L469 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties = nullptr;` — `UPROPERTY()`
- L473 _protected member_ `TObjectPtr<UToolTarget> Target = nullptr;` — `UPROPERTY()` — Existing asset to modify, if one was selected
- L475 _protected member_ `TSharedPtr<FCubeGrid, ESPMode::ThreadSafe> CubeGrid;`
- L478 _protected member_ `TObjectPtr<UWorld> TargetWorld = nullptr;` — Where to make the preview, new mesh, etc
- L482 _protected member_ `EMode Mode = EMode::PushPull;` — Important state. Could refactor things into tool activities (like PolyEdit) someday.
- L483 _protected member_ `EMouseState MouseState = EMouseState::NotDragging;`
- L485 _protected prototype_ `bool GetHitGridFace(const FRay& WorldRay, UE::Geometry::FCubeGrid::FCubeFace& FaceOut);`
- L486 _protected prototype_ `bool UpdateHover(const FRay& WorldRay);`
- L487 _protected prototype_ `void UpdateHoverLineSet(bool bHaveHover, const UE::Geometry::FAxisAlignedBox3d& HoveredBox);`
- L488 _protected prototype_ `void UpdateSelectionLineSet();`
- L489 _protected prototype_ `void UpdateGridLineSet();`
- L490 _protected prototype_ `void UpdateCornerModeLineSet();`
- L491 _protected prototype_ `void ClearHover();`
- L493 _protected member_ `bool bHaveSelection = false;`
- L494 _protected member_ `FSelection Selection;`
- L496 _protected member_ `bool bPreviousHaveSelection = false;`
- L497 _protected member_ `FSelection PreviousSelection;`
- L499 _protected member_ `bool bHaveHoveredSelection = false;`
- L500 _protected member_ `UE::Geometry::FAxisAlignedBox3d HoveredSelectionBox;`
- L502 _protected prototype_ `void SlideSelection(int32 ExtrudeAmount, bool bEmitChange);`
- L504 _protected member_ `bool bSlideToggle = false;`
- L505 _protected member_ `bool bSelectionToggle = false;`
- L506 _protected member_ `bool bChangeSideToggle = false;`
- L507 _protected member_ `bool bMouseDragShouldPushPull = false;`
- L508 _protected member_ `FRay3d DragProjectionAxis;`
- L509 _protected member_ `double DragProjectedStartParam;`
- L510 _protected member_ `int32 DragStartExtrudeAmount = 0;`
- L512 _protected prototype_ `void ApplyFlipSelection();`
- L513 _protected prototype_ `void ApplySlide(int32 NumBlocks);`
- L514 _protected prototype_ `void ApplyPushPull(int32 NumBlocks);`
- L517 _protected prototype_ `void SetGridPowerClamped(int32 GridPower);` — Parameter is signed on purpose so we can give negatives for clamping.
- L520 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview;` — `UPROPERTY()`
- L528 _protected prototype_ `void InvalidatePreview(bool bUpdateCornerLineSet = true);` — @param bUpdateCornerLineSet This can be set to false when the invalidation is a result of a grid transform change (which is applied to the line set via the LineSets->SetTransform), or when the corner shape otherwise doesn't change. Usually it can be left to true.
- L530 _protected prototype_ `void ApplyPreview();`
- L532 _protected member_ `int32 CurrentExtrudeAmount = 0;`
- L533 _protected member_ `bool bPreviewMayDiffer = false;`
- L534 _protected member_ `bool bWaitingToApplyPreview = false;`
- L535 _protected member_ `bool bBlockUntilPreviewUpdate = false;`
- L536 _protected member_ `bool bAdjustSelectionOnPreviewUpdate = false;`
- L538 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> CurrentMesh;`
- L539 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> MeshSpatial;`
- L540 _protected member_ `UE::Geometry::FTransformSRT3d CurrentMeshTransform = UE::Geometry::FTransformSRT3d::Identity();`
- L541 _protected member_ `TSharedPtr<TArray<int32>, ESPMode::ThreadSafe> LastOpChangedTids;`
- L543 _protected member_ `TArray<UMaterialInterface*> CurrentMeshMaterials;`
- L544 _protected member_ `int32 OpMeshMaterialID = 0;`
- L545 _protected prototype_ `void UpdateOpMaterials();`
- L550 _protected member_ `double OpMeshHeightUVOffset = 0;` — These are used to keep UV's and side groups consistent across multiple E/Q (push/pull) presses. This data should be reset whenever the selection changes in a way that is not a byproduct of a push/pull.
- L551 _protected member_ `TArray<int32, TFixedAllocator<4>> OpMeshAddSideGroups;`
- L552 _protected member_ `TArray<int32, TFixedAllocator<4>> OpMeshSubtractSideGroups;`
- L553 _protected prototype_ `void ResetMultiStepConsistencyData();`
- L556 _protected member_ `TSharedPtr<const UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> ComputeStartMesh;` — Safe inputs for the background compute to use, untouched by undo/redo/other CurrentMesh updates.
- L557 _protected prototype_ `void UpdateComputeInputs();`
- L559 _protected member_ `static const int32 ShiftModifierID = 1;`
- L560 _protected member_ `static const int32 CtrlModifierID = 2;`
- L562 _protected member_ `ECubeGridToolAction PendingAction = ECubeGridToolAction::NoAction;`
- L563 _protected prototype_ `void ApplyAction(ECubeGridToolAction ActionType);`
- L564 _protected prototype_ `void ClearViewportButtonCustomization();`
- L566 _protected member_ `int32 GridPowerWatcherIdx;`
- L567 _protected member_ `int32 BlockBaseSizeWatcherIdx;`
- L568 _protected member_ `int32 CurrentBlockSizeWatcherIdx;`
- L570 _protected member_ `int32 GridFrameOriginWatcherIdx;`
- L571 _protected member_ `int32 GridFrameOrientationWatcherIdx;`
- L572 _protected prototype_ `void GridGizmoMoved(UTransformProxy* Proxy, FTransform Transform);`
- L573 _protected prototype_ `void UpdateGizmoVisibility(bool bVisible);`
- L574 _protected member_ `bool bInGizmoDrag = false;`
- L584 _protected prototype_ `void UpdateGridGizmo(const FTransform& NewTransform, bool bSilentlyUpdate = false);` — Updates the gizmo controlling the cube grid transform. Only updates the cube grid itself if bSilentlyUpdate is false. @param bSilentlyUpdate If true, gizmo is just repositioned without triggering any callback or emitting an undo transaction. If false, emits transactions and triggers the GridGizmoMoved callback (which will trigger UpdateGridTransform).
- L594 _protected prototype_ `void UpdateGridTransform(const FTransform& NewTransform, bool bUpdateDetailPanel = true, bool bTriggerDetailPanelRebuild = true);` — Updates the cube grid. @param bUpdateDetailPanel Not needed if updating from the detail panel, otherwise should be true. @param bTriggerDetailPanelRebuild Should be false if updating from a drag to avoid the costly rebuild, but otherwise should be true to update the edit conditions and "revert to default" arrows. Not relevant if bUpdateDetailPanel is false.
- L596 _protected member_ `FVector3d MiddleClickDragStart;`
- L597 _protected prototype_ `FInputRayHit RayCastSelectionPlane(const FRay3d& WorldRay, FVector3d& HitPointOut);`
- L599 _protected prototype_ `FInputRayHit CanBeginMiddleClickDrag(const FInputDeviceRay& ClickPos);`
- L600 _protected prototype_ `void OnMiddleClickDrag(const FInputDeviceRay& DragPos);`
- L601 _protected prototype_ `void OnCtrlMiddleClick(const FInputDeviceRay& ClickPos);`
- L602 _protected prototype_ `void PrepForSelectionChange();`
- L603 _protected prototype_ `void EndSelectionChange();`
- L610 _protected member_ `bool CornerSelectedFlags[4] = { false, false, false, false };` — Used in corner push/pull mode. If you create a flat FOrientedBox3d out of the current selection, with the Z axis being along selection normal, the 0-3 indices here correspond to the 0-3 corner indices in the box, which are the bottom corners along Z axis (see TOrientedBox3::GetCorner()) TODO: Might be nice to pack these into one value for ease of copying/resetting/comparing
- L611 _protected member_ `bool PreDragCornerSelectedFlags[4] = { false, false, false, false };`
- L613 _protected member_ `FViewCameraState CameraState;`
- L614 _protected member_ `FToolDataVisualizer SelectedCornerRenderer;`
- L615 _protected member_ `UE::Geometry::FGeometrySet3 CornersGeometrySet;`
- L616 _protected prototype_ `void UpdateCornerGeometrySet();`
- L617 _protected prototype_ `void StartCornerMode();`
- L618 _protected prototype_ `void ApplyCornerMode(bool bDontWaitForTick = false);`
- L619 _protected prototype_ `void CancelCornerMode();`
- L620 _protected prototype_ `void AttemptToSelectCorner(const FRay3d& WorldRay);`
- L623 _protected member_ `bool bChangesMade = false;` — Used to see if we need to update the asset that we've been modifying
- L625 _protected prototype_ `void OutputCurrentResults(bool bSetSelection);`
- L626 _protected prototype_ `void AcceptToolAndStartNew();`
- L629 _private member_ `bool bHasInitialGridPivot = false;`
- L630 _private member_ `FVector3d InitialGridPivot;`

#### enum `UCubeGridTool::EMouseState`  
`enum class EMouseState`  
_L315-321_
- L317 _public enumerator_ `NotDragging`
- L318 _public enumerator_ `DraggingExtrudeDistance`
- L319 _public enumerator_ `DraggingCornerSelection`
- L320 _public enumerator_ `DraggingRegularSelection`

#### enum `UCubeGridTool::EMode`  
`enum class EMode`  
_L323-334_
- L325 _public enumerator_ `PushPull`
- L326 _public enumerator_ `Corner`
- L333 _public enumerator_ `FitGrid` — This is currently not supported, but some of the code was written with space for a "fit grid" mode that would have allowed the dimensions of the grid to be fit using a sequence of (snapped) mouse clicks. It seems useful to leave those code stubs for now in case we add the mode in, so it's easier to track down the affected portions of code.

#### struct `UCubeGridTool::FSelection`  
`struct FSelection`  
_L340-360_
- L343 _public member_ `UE::Geometry::FAxisAlignedBox3d Box;` — Both of these boxes are in the coordinate space of the (unscaled) grid frame.
- L344 _public member_ `UE::Geometry::FAxisAlignedBox3d StartBox;` — Box delineating original selected face
- L347 _public member_ `FCubeGrid::EFaceDirection Direction = FCubeGrid::EFaceDirection::PositiveX;` — Direction must be initialized to a valid enum value (0 is not one).
- L349 _public function_ `bool operator==(const FSelection& Other) const`
- L356 _public function_ `bool operator!=(const FSelection& Other) const`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L26 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L27 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMeshChange);`
- L28 _prototype_ `PREDECLARE_GEOMETRY(class FCubeGrid);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/DrawPolyPathTool.h` (Public)


#### class `UDrawPolyPathToolBuilder`  
`class UDrawPolyPathToolBuilder : public UInteractiveToolBuilder`  
_L27-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: ToolBuilder
- L31 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L33 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### enum `EDrawPolyPathWidthMode`  
`enum class EDrawPolyPathWidthMode`  
_L38-45_
- reflection: `UENUM()`
- L41 _public enumerator_ `Fixed` — Fixed width along the drawn path determined by the Width property
- L44 _public enumerator_ `Interactive` — Extrude drawn path to height set via additional mouse input after finishing the path

#### enum `EDrawPolyPathRadiusMode`  
`enum class EDrawPolyPathRadiusMode`  
_L48-55_
- reflection: `UENUM()`
- L51 _public enumerator_ `Fixed` — Fixed radius determined by the CornerRadius property.
- L54 _public enumerator_ `Interactive` — Set the radius interactively by clicking in the viewport.

#### enum `EDrawPolyPathExtrudeMode`  
`enum class EDrawPolyPathExtrudeMode`  
_L58-74_
- reflection: `UENUM()`
- L61 _public enumerator_ `Flat` — Flat path without extrusion
- L64 _public enumerator_ `Fixed` — Extrude drawn path to a fixed height determined by the Extrude Height property
- L67 _public enumerator_ `Interactive` — Extrude drawn path to height set via additional mouse input after finishing the path
- L70 _public enumerator_ `RampFixed` — Extrude with increasing height along the drawn path. The height at the start and the end of the ramp is determined by the Extrude Height and Ramp Start Ratio properties .
- L73 _public enumerator_ `RampInteractive` — Extrude with increasing height along the drawn path. The height is set via additional mouse input after finishing the path.

#### class `UDrawPolyPathProperties`  
`class UDrawPolyPathProperties : public UInteractiveToolPropertySet`  
_L78-130_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L85 _public member_ `EDrawPolyPathWidthMode WidthMode = EDrawPolyPathWidthMode::Interactive;` — `UPROPERTY(EditAnywhere, Category = Path)` — How the drawn path width gets set
- L90 _public member_ `float Width = 10.0f;` — `UPROPERTY(EditAnywhere, Category = Path, meta = (EditCondition = "WidthMode == EDrawPolyPathWidthMode::Fixed", UIMin = "0.0001", UIMax = "1000", ClampMin = "0.0001", ClampMax = "999999"))` — Width of the drawn path when using Fixed width mode; also shows the width in Interactive width mode
- L94 _public member_ `bool bRoundedCorners = false;` — `UPROPERTY(EditAnywhere, Category = Path)` — Use arc segments instead of straight lines in corners
- L98 _public member_ `EDrawPolyPathRadiusMode RadiusMode = EDrawPolyPathRadiusMode::Interactive;` — `UPROPERTY(EditAnywhere, Category = Path, meta = (EditCondition = "bRoundedCorners"))` — How the rounded corner radius gets set
- L104 _public member_ `float CornerRadius = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Path, meta = ( EditCondition = "RadiusMode == EDrawPolyPathRadiusMode::Fixed && bRoundedCorners", UIMin = "0", UIMax = "2.0", ClampMin = "0", ClampMax = "999999"))` — Radius of the corner arcs, as a fraction of path width. This is only available if Rounded Corners is enabled.
- L109 _public member_ `int RadialSlices = 16;` — `UPROPERTY(EditAnywhere, NonTransactional, Category = Path, meta = (UIMin = "3", UIMax = "100", ClampMin = "3", ClampMax = "10000", EditCondition = "bRoundedCorners"))` — Number of radial subdivisions for rounded corners
- L113 _public member_ `bool bSinglePolyGroup = false;` — `UPROPERTY(EditAnywhere, Category = Path, meta = (DisplayName = "Single PolyGroup"))` — If true, all quads on the path will belong to the same polygon. If false, each quad gets its own polygon.
- L117 _public member_ `EDrawPolyPathExtrudeMode ExtrudeMode = EDrawPolyPathExtrudeMode::Interactive;` — `UPROPERTY(EditAnywhere, Category = Extrude)` — If and how the drawn path gets extruded
- L123 _public member_ `float ExtrudeHeight = 10.0f;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = ( EditCondition = "ExtrudeMode == EDrawPolyPathExtrudeMode::Fixed || ExtrudeMode == EDrawPolyPathExtrudeMode::RampFixed", UIMin = "-1000", UIMax = "1000", ClampMin = "-10000", ClampMax = "10000"))` — Extrusion distance when using the Fixed extrude modes; also shows the distance in Interactive extrude modes
- L129 _public member_ `float RampStartRatio = 0.05f;` — `UPROPERTY(EditAnywhere, Category = Extrude, meta = ( EditCondition = "ExtrudeMode == EDrawPolyPathExtrudeMode::RampFixed || ExtrudeMode == EDrawPolyPathExtrudeMode::RampInteractive", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "100.0"))` — Height of the start of the ramp as a fraction of the Extrude Height property

#### enum `EDrawPolyPathExtrudeDirection`  
`enum class EDrawPolyPathExtrudeDirection`  
_L135-144_
- reflection: `UENUM()`
- L137 _public enumerator_ `SelectionNormal`
- L138 _public enumerator_ `WorldX`
- L139 _public enumerator_ `WorldY`
- L140 _public enumerator_ `WorldZ`
- L141 _public enumerator_ `LocalX`
- L142 _public enumerator_ `LocalY`
- L143 _public enumerator_ `LocalZ`

#### class `UDrawPolyPathExtrudeProperties`  
`class UDrawPolyPathExtrudeProperties : public UInteractiveToolPropertySet`  
_L148-157_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L154 _public member_ `EDrawPolyPathExtrudeDirection Direction = EDrawPolyPathExtrudeDirection::SelectionNormal;` — `UPROPERTY(EditAnywhere, Category = Extrude)`

#### class `UDrawPolyPathTool`  
`class UDrawPolyPathTool : public UInteractiveTool, public IClickBehaviorTarget, public IHoverBehaviorTarget, public IInteractiveToolManageGeometrySelectionAPI`  
_L165-316_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IClickBehaviorTarget,IHoverBehaviorTarget,IInteractiveToolManageGeometrySelectionAPI`
- L170 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L172 _public prototype_ `virtual void Setup() override;`
- L173 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L175 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L176 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L177 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L179 _public function_ `virtual bool HasCancel() const override`
- L180 _public function_ `virtual bool HasAccept() const override`
- L181 _public function_ `virtual bool CanAccept() const override`
- L183 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit);`
- L186 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget API
- L187 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L190 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget API
- L191 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L192 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L193 _public function_ `virtual void OnEndHover() override`
- L196 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IModifierToggleBehaviorTarget
- L198 _public function_ `void SetInitialDrawFrame(UE::Geometry::FFrame3d Frame)`
- L204 _public prototype_ `virtual bool IsInputSelectionValidOnOutput() override;` — IInteractiveToolManageGeometrySelectionAPI - enables restoration of previous selection when applicable
- L207 _protected member_ `UWorld* TargetWorld;`
- L211 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()` — Property set for type of output object (StaticMesh, Volume, etc)
- L214 _protected member_ `TObjectPtr<UDrawPolyPathProperties> TransformProps;` — `UPROPERTY()`
- L217 _protected member_ `TObjectPtr<UDrawPolyPathExtrudeProperties> ExtrudeProperties;` — `UPROPERTY()`
- L220 _protected member_ `TObjectPtr<UNewMeshMaterialProperties> MaterialProperties;` — `UPROPERTY()`
- L230 _protected member_ `EState State = EState::DrawingPath;`
- L233 _protected member_ `FTransform3d WorldTransform;` — camera state at last render
- L234 _protected member_ `FViewCameraState CameraState;`
- L239 _protected member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L241 _protected member_ `UE::Geometry::FFrame3d DrawPlaneWorld;`
- L243 _protected prototype_ `bool CanUpdateDrawPlane() const;`
- L246 _protected member_ `float UVScaleFactor = 1.0f;` — UV Scale factor to apply to texturing on any new geometry (e.g. new faces added by extrude)
- L248 _protected member_ `TArray<UE::Geometry::FFrame3d> CurPathPoints;`
- L249 _protected member_ `TArray<double> OffsetScaleFactors;`
- L250 _protected member_ `TArray<FVector3d> CurPolyLine;`
- L251 _protected member_ `double CurPathLength;`
- L252 _protected member_ `double CurHeight;`
- L253 _protected member_ `bool bHasSavedWidth = false;`
- L254 _protected member_ `float SavedWidth;`
- L255 _protected member_ `bool bHasSavedRadius = false;`
- L256 _protected member_ `float SavedRadius;`
- L257 _protected member_ `bool bHasSavedExtrudeHeight = false;`
- L258 _protected member_ `float SavedExtrudeHeight;`
- L259 _protected member_ `bool bPathIsClosed = false;` — If true, CurPathPoints are assumed to define a closed path
- L261 _protected member_ `static const int ShiftModifierID = 1;`
- L262 _protected member_ `bool bIgnoreSnappingToggle = false;` — toggled by hotkey (shift)
- L264 _protected member_ `TArray<FVector3d> CurPolyLoop;`
- L265 _protected member_ `TArray<FVector3d> SecondPolyLoop;`
- L268 _protected member_ `TObjectPtr<UPolyEditPreviewMesh> EditPreview;` — `UPROPERTY()`
- L271 _protected member_ `TObjectPtr<UPlaneDistanceFromHitMechanic> ExtrudeHeightMechanic = nullptr;` — `UPROPERTY()`
- L273 _protected member_ `TObjectPtr<USpatialCurveDistanceMechanic> CurveDistMechanic = nullptr;` — `UPROPERTY()`
- L275 _protected member_ `TObjectPtr<UCollectSurfacePathMechanic> SurfacePathMechanic = nullptr;` — `UPROPERTY()`
- L277 _protected member_ `bool bSpecifyingRadius = false;`
- L279 _protected prototype_ `void InitializeNewSurfacePath();`
- L280 _protected prototype_ `void UpdateSurfacePathPlane();`
- L281 _protected prototype_ `void OnCompleteSurfacePath();`
- L283 _protected prototype_ `void BeginSettingWidth();`
- L284 _protected prototype_ `void OnCompleteWidth();`
- L286 _protected prototype_ `void BeginSettingRadius();`
- L287 _protected prototype_ `void OnCompleteRadius();`
- L289 _protected prototype_ `void BeginSettingHeight();`
- L290 _protected prototype_ `void BeginInteractiveExtrudeHeight();`
- L291 _protected prototype_ `void BeginConstantExtrudeHeight();`
- L292 _protected prototype_ `void UpdateExtrudePreview();`
- L293 _protected prototype_ `void OnCompleteExtrudeHeight();`
- L295 _protected prototype_ `void UpdatePathPreview();`
- L296 _protected prototype_ `void InitializePreviewMesh();`
- L297 _protected prototype_ `void ClearPreview();`
- L299 _protected prototype_ `[[nodiscard]] FVector3d GeneratePathMesh(UE::Geometry::FDynamicMesh3& Mesh);`
- L300 _protected prototype_ `void GenerateExtrudeMesh(UE::Geometry::FDynamicMesh3& PathMesh);`
- L301 _protected prototype_ `void EmitNewObject();`
- L304 _protected prototype_ `void ShowStartupMessage();` — user feedback messages
- L305 _protected prototype_ `void ShowExtrudeMessage();`
- L306 _protected prototype_ `void ShowOffsetMessage();`
- L309 _protected member_ `int32 CurrentCurveTimestamp = 1;`
- L310 _protected prototype_ `void UndoCurrentOperation(EState DestinationState);`
- L311 _protected function_ `bool CheckInCurve(int32 Timestamp) const`
- L315 _private member_ `bool bRestoreInputSelection = true;` — if the drawn path is incomplete upon 'Accept' of the tool, no mesh should be created and the previous mesh element selection from before entering the tool should be restored

#### enum `UDrawPolyPathTool::EState`  
`enum class EState`  
_L223-229_
- L225 _public enumerator_ `DrawingPath`
- L226 _public enumerator_ `SettingWidth`
- L227 _public enumerator_ `SettingRadius`
- L228 _public enumerator_ `SettingHeight`

#### class `FDrawPolyPathStateChange`  
`class FDrawPolyPathStateChange : public FToolCommandChange`  
_L321-336_
- inherits: `FToolCommandChange`
- L324 _public member_ `bool bHaveDoneUndo = false;`
- L325 _public member_ `int32 CurveTimestamp = 0;`
- L326 _public member_ `UDrawPolyPathTool::EState PreviousState = UDrawPolyPathTool::EState::DrawingPath;`
- L327 _public function_ `FDrawPolyPathStateChange(int32 CurveTimestampIn, UDrawPolyPathTool::EState PreviousStateIn) : CurveTimestamp(CurveTimestampIn) , PreviousState(PreviousStateIn)`
- L332 _public function_ `virtual void Apply(UObject* Object) override`
- L333 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L334 _public prototype_ `virtual bool HasExpired(UObject* Object) const override;`
- L335 _public prototype_ `virtual FString ToString() const override;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/EditNormalsTool.h` (Public)


#### class `UEditNormalsToolBuilder`  
`class UEditNormalsToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L30-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L35 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L36 _public prototype_ `virtual void InitializeNewTool(UMultiSelectionMeshEditingTool* NewTool, const FToolBuilderState& SceneState) const override;`
- L37 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UEditNormalsToolProperties`  
`class UEditNormalsToolProperties : public UInteractiveToolPropertySet`  
_L48-96_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties
- L53 _public prototype_ `UEditNormalsToolProperties();`
- L55 _public function_ `bool WillTopologyChange()`
- L63 _public member_ `bool bRecomputeNormals;` — `UPROPERTY(EditAnywhere, Category = NormalsCalculation, meta = (EditCondition = "SplitNormalMethod == ESplitNormalMethod::UseExistingTopology && !bToolHasSelection", HideEditConditionToggle))` — Recompute all mesh normals
- L67 _public member_ `ENormalCalculationMethod NormalCalculationMethod;` — `UPROPERTY(EditAnywhere, Category = NormalsCalculation)` — Choose the method for computing vertex normals
- L72 _public member_ `bool bFixInconsistentNormals;` — `UPROPERTY(EditAnywhere, Category = NormalsCalculation, meta = (EditCondition = "!bToolHasSelection", HideEditConditionToggle))` — For meshes with inconsistent triangle orientations/normals, flip as needed to make the normals consistent
- L76 _public member_ `bool bInvertNormals;` — `UPROPERTY(EditAnywhere, Category = NormalsCalculation)` — Invert (flip) all mesh normals and associated triangle orientations
- L80 _public member_ `ESplitNormalMethod SplitNormalMethod;` — `UPROPERTY(EditAnywhere, Category = NormalsTopology)` — Control whether and how the topology of the normals is recomputed, e.g. to create sharp edges where face normals change by a large amount or where face group IDs change.  Normals will always be recomputed unless SplitNormal Method is UseExistingTopology.
- L84 _public member_ `float SharpEdgeAngleThreshold;` — `UPROPERTY(EditAnywhere, Category = NormalsTopology, meta = (UIMin = "0.0", UIMax = "180.0", ClampMin = "0.0", ClampMax = "180.0", EditCondition = "SplitNormalMethod == ESplitNormalMethod::FaceNormalThreshold"))` — Threshold on angle of change in face normals across an edge, above which we create a sharp edge if bSplitNormals is true
- L88 _public member_ `bool bAllowSharpVertices;` — `UPROPERTY(EditAnywhere, Category = NormalsTopology, meta = (EditCondition = "SplitNormalMethod == ESplitNormalMethod::FaceNormalThreshold"))` — Assign separate normals at 'sharp' vertices, for example, at the tip of a cone
- L95 _public member_ `bool bToolHasSelection;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UEditNormalsOperatorFactory`  
`class UEditNormalsOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L108-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Factory with enough info to spawn the background-thread Operator to do a chunk of work for the tool stores a pointer to the tool and enough info to know which specific operator it should spawn
- L114 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L117 _public member_ `TObjectPtr<UEditNormalsTool> Tool;` — `UPROPERTY()`
- L119 _public member_ `int ComponentIndex;`

#### class `UEditNormalsTool`  
`class UEditNormalsTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L127-213_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Simple Mesh Normal Updating Tool
- L135 _public prototype_ `UEditNormalsTool();`
- L137 _public prototype_ `virtual void Setup() override;`
- L138 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L140 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L142 _public function_ `virtual bool HasCancel() const override`
- L143 _public prototype_ `virtual bool HasAccept() const override;`
- L144 _public prototype_ `virtual bool CanAccept() const override;`
- L147 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;`
- L150 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L153 _public prototype_ `void SetGeometrySelection(UE::Geometry::FGeometrySelection&& SelectionIn);` — input selection support
- L156 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L164 _protected member_ `TObjectPtr<UEditNormalsToolProperties> BasicProperties = nullptr;` — `UPROPERTY()`
- L167 _protected member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties = nullptr;` — `UPROPERTY()`
- L170 _protected member_ `TArray<TObjectPtr<UMeshOpPreviewWithBackgroundCompute>> Previews;` — `UPROPERTY()`
- L174 _protected member_ `TArray<TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe>> OriginalDynamicMeshes;`
- L176 _protected member_ `FViewCameraState CameraState;`
- L178 _protected prototype_ `void UpdateNumPreviews();`
- L180 _protected prototype_ `void GenerateAsset(const TArray<FDynamicMeshOpResult>& Results);`
- L183 _protected member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> ActiveGroupSet;`
- L184 _protected prototype_ `void OnSelectedGroupLayerChanged();`
- L185 _protected prototype_ `void UpdateActiveGroupLayer();`
- L192 _protected member_ `TObjectPtr<UGeometrySelectionVisualizationProperties> GeometrySelectionVizProperties = nullptr;` — `UPROPERTY()`
- L195 _protected member_ `TObjectPtr<UPreviewGeometry> GeometrySelectionViz = nullptr;` — `UPROPERTY()`
- L199 _protected member_ `UE::Geometry::FGeometrySelection InputGeometrySelection;` — The geometry selection that the user started the tool with. If the selection is empty we operate on the whole mesh, if its not empty we only edit the overlay elements implied by the selection.
- L203 _protected member_ `UE::Geometry::FGeometrySelection TriangleVertexGeometrySelection;` — If the user starts the tool with an edge selection we convert it to a vertex selection with triangle topology and store it here, we do this since we expect users to want vertex and edge selections to behave similarly.
- L207 _protected member_ `TSet<int> EditTriangles;` — These are indices into the tool target mesh. If both are non-empty we edit the corresponding elements in the overlay, otherwise operate on the whole overlay
- L208 _protected member_ `TSet<int> EditVertices;`
- L212 _protected member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> InputGeometrySelectionPolygroupSet;` — Cache the input polygroup set which was used to start the tool. We do this because users can change the polygroup referenced by the operator while using the tool.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/EditPivotTool.h` (Public)


#### class `UEditPivotToolBuilder`  
`class UEditPivotToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L27-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L31 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L32 _public prototype_ `virtual void InitializeNewTool(UMultiSelectionMeshEditingTool* NewTool, const FToolBuilderState& SceneState) const override;`
- L35 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EEditPivotSnapDragRotationMode`  
`enum class EEditPivotSnapDragRotationMode : uint8`  
_L43-52_
- reflection: `UENUM()`
- desc: Snap-Drag Rotation Mode
- L46 _public enumerator_ `Align = 1 UMETA(DisplayName = "Align")` — Snap-Drag aligns the pivot Z Axis and Target Normals to point in the same direction
- L49 _public enumerator_ `AlignFlipped = 2 UMETA(DisplayName = "Align Flipped")` — Snap-Drag aligns the pivot Z Axis to the opposite of the Target Normal direction
- L51 _public enumerator_ `LastValue UMETA(Hidden)`

#### class `UEditPivotToolProperties`  
`class UEditPivotToolProperties : public UInteractiveToolPropertySet`  
_L60-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the Edit Pivot operation
- L67 _public member_ `bool bApplyToAllLODs = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — If checked, the baked transform will be applied to all available LODs. Has no effect on selections without LODs.
- L71 _public member_ `bool bSnapDragPosition = false;` — `UPROPERTY(EditAnywhere, Category = SnapDragging)` — When enabled, click-drag to reposition the Pivot
- L75 _public member_ `bool bSnapDragRotation = false;` — `UPROPERTY(EditAnywhere, Category = SnapDragging)` — When enabled, click-drag to reorient the Pivot
- L79 _public member_ `EEditPivotSnapDragRotationMode RotationMode = EEditPivotSnapDragRotationMode::Align;` — `UPROPERTY(EditAnywhere, Category = SnapDragging, meta = (EditCondition = "bSnapDragRotation"))` — When snap-dragging rotation, how to align source and target normals

#### struct `FEditPivotTarget`  
`struct FEditPivotTarget`  
_L84-93_
- reflection: `USTRUCT()`
- L89 _public member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L92 _public member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`

#### enum `EEditPivotToolActions`  
`enum class EEditPivotToolActions`  
_L99-111_
- reflection: `UENUM()`
- L101 _public enumerator_ `NoAction`
- L103 _public enumerator_ `Center`
- L104 _public enumerator_ `Bottom`
- L105 _public enumerator_ `Top`
- L106 _public enumerator_ `Left`
- L107 _public enumerator_ `Right`
- L108 _public enumerator_ `Front`
- L109 _public enumerator_ `Back`
- L110 _public enumerator_ `WorldOrigin`

#### class `UEditPivotToolActionPropertySet`  
`class UEditPivotToolActionPropertySet : public UInteractiveToolPropertySet`  
_L116-153_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L121 _public member_ `TWeakObjectPtr<UEditPivotTool> ParentTool;`
- L123 _public function_ `void Initialize(UEditPivotTool* ParentToolIn)`
- L124 _public prototype_ `void PostAction(EEditPivotToolActions Action);`
- L128 _public member_ `bool bUseWorldBox = false;` — `UPROPERTY(EditAnywhere, Category = BoxPositions)` — Use the World-Space Bounding Box of the target object, instead of the Object-space Bounding Box
- L131 _public function_ `void Center()` — `UFUNCTION(CallInEditor, Category = BoxPositions, meta = (DisplayPriority = 1))`
- L134 _public function_ `void Bottom()` — `UFUNCTION(CallInEditor, Category = BoxPositions, meta = (DisplayPriority = 2))`
- L137 _public function_ `void Top()` — `UFUNCTION(CallInEditor, Category = BoxPositions, meta = (DisplayPriority = 2))`
- L140 _public function_ `void Left()` — `UFUNCTION(CallInEditor, Category = BoxPositions, meta = (DisplayPriority = 3))`
- L143 _public function_ `void Right()` — `UFUNCTION(CallInEditor, Category = BoxPositions, meta = (DisplayPriority = 3))`
- L146 _public function_ `void Front()` — `UFUNCTION(CallInEditor, Category = BoxPositions, meta = (DisplayPriority = 4))`
- L149 _public function_ `void Back()` — `UFUNCTION(CallInEditor, Category = BoxPositions, meta = (DisplayPriority = 4))`
- L152 _public function_ `void WorldOrigin()` — `UFUNCTION(CallInEditor, Category = BoxPositions, meta = (DisplayPriority = 5))`

#### class `UEditPivotTool`  
`class UEditPivotTool : public UMultiSelectionMeshEditingTool, public IClickDragBehaviorTarget, public IInteractiveToolManageGeometrySelectionAPI`  
_L161-239_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IClickDragBehaviorTarget,IInteractiveToolManageGeometrySelectionAPI`
- L166 _public prototype_ `UEditPivotTool();`
- L168 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L170 _public prototype_ `virtual void Setup() override;`
- L171 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L173 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L174 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L176 _public function_ `virtual bool HasCancel() const override`
- L177 _public function_ `virtual bool HasAccept() const override`
- L179 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L183 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — ICLickDragBehaviorTarget interface
- L184 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L185 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L186 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L187 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L190 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L197 _public member_ `TObjectPtr<UEditPivotToolProperties> TransformProps;` — `UPROPERTY()`
- L200 _public member_ `TObjectPtr<UEditPivotToolActionPropertySet> EditPivotActions;` — `UPROPERTY()`
- L202 _public prototype_ `virtual void RequestAction(EEditPivotToolActions ActionType);`
- L204 _public function_ `void SetInitialPivot(FTransform3d InInitialPivot)`
- L211 _protected member_ `TArray<int> MapToFirstOccurrences;`
- L213 _protected member_ `FTransform3d InitialPivot = FTransform3d::Identity;`
- L214 _protected member_ `bool bHasCustomInitialPivot = false;`
- L216 _protected member_ `FTransform3d Transform;`
- L217 _protected member_ `UE::Geometry::FAxisAlignedBox3d ObjectBounds;`
- L218 _protected member_ `UE::Geometry::FAxisAlignedBox3d WorldBounds;`
- L219 _protected prototype_ `void Precompute();`
- L222 _protected member_ `TArray<FEditPivotTarget> ActiveGizmos;` — `UPROPERTY()`
- L225 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L227 _protected prototype_ `void UpdateSetPivotModes(bool bEnableSetPivot);`
- L228 _protected prototype_ `void SetActiveGizmos_Single(bool bLocalRotations);`
- L229 _protected prototype_ `void ResetActiveGizmos();`
- L231 _protected member_ `FTransform StartDragTransform;`
- L233 _protected member_ `EEditPivotToolActions PendingAction;`
- L234 _protected prototype_ `virtual void ApplyAction(EEditPivotToolActions ActionType);`
- L235 _protected prototype_ `virtual void SetPivotToBoxPoint(EEditPivotToolActions ActionPoint);`
- L236 _protected prototype_ `virtual void SetPivotToWorldOrigin();`
- L238 _protected prototype_ `void UpdateAssets(const UE::Geometry::FFrame3d& NewPivotWorldFrame);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/EditUVIslandsTool.h` (Public)


#### class `UEditUVIslandsToolBuilder`  
`class UEditUVIslandsToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L29-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- desc: ToolBuilder
- L33 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L34 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### class `FUVGroupTopology`  
`class FUVGroupTopology : public FGroupTopology`  
_L40-57_
- inherits: `FGroupTopology`
- L43 _public member_ `TArray<int32> TriIslandGroups;`
- L44 _public member_ `const FDynamicMeshUVOverlay* UVOverlay;`
- L46 _public function_ `FUVGroupTopology()`
- L47 _public prototype_ `FUVGroupTopology(const UE::Geometry::FDynamicMesh3* Mesh, uint32 UVLayerIndex, bool bAutoBuild = false);`
- L49 _public prototype_ `void CalculateIslandGroups();`
- L51 _public function_ `virtual int GetGroupID(int32 TriangleID) const override`
- L56 _public prototype_ `UE::Geometry::FFrame3d GetIslandFrame(int32 GroupID, UE::Geometry::FDynamicMeshAABBTree3& AABBTree);`

#### class `UEditUVIslandsTool`  
`class UEditUVIslandsTool : public UMeshSurfacePointTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L64-176_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointTool,IInteractiveToolManageGeometrySelectionAPI`
- L69 _public prototype_ `UEditUVIslandsTool();`
- L71 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L73 _public prototype_ `virtual void Setup() override;`
- L74 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L76 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L77 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L79 _public function_ `virtual bool HasCancel() const override`
- L80 _public function_ `virtual bool HasAccept() const override`
- L83 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;` — UMeshSurfacePointTool API
- L84 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L85 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L86 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L87 _public prototype_ `virtual void OnCancelDrag() override;`
- L88 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L89 _public prototype_ `virtual void OnEndHover() override;`
- L92 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget API
- L95 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L102 _public member_ `TObjectPtr<UExistingMeshMaterialProperties> MaterialSettings = nullptr;` — `UPROPERTY()`
- L105 _public member_ `TObjectPtr<UMaterialInstanceDynamic> CheckerMaterial = nullptr;` — `UPROPERTY()`
- L110 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L113 _protected member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent = nullptr;` — `UPROPERTY()`
- L116 _protected member_ `TObjectPtr<UPolygonSelectionMechanic> SelectionMechanic;` — `UPROPERTY()`
- L118 _protected member_ `bool bSelectionStateDirty = false;`
- L119 _protected prototype_ `void OnSelectionModifiedEvent();`
- L122 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`
- L125 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L127 _protected prototype_ `void OnGizmoTransformBegin(UTransformProxy* TransformProxy);`
- L128 _protected prototype_ `void OnGizmoTransformUpdate(UTransformProxy* TransformProxy, FTransform Transform);`
- L129 _protected prototype_ `void OnGizmoTransformEnd(UTransformProxy* TransformProxy);`
- L132 _protected prototype_ `void OnDynamicMeshComponentChanged();` — realtime visualization
- L133 _protected member_ `FDelegateHandle OnDynamicMeshComponentChangedHandle;`
- L136 _protected member_ `FTransform3d WorldTransform;` — camera state at last render
- L137 _protected member_ `FViewCameraState CameraState;`
- L140 _protected member_ `bool bInDrag;` — True for the duration of UI click+drag
- L142 _protected member_ `double UVTranslateScale;`
- L143 _protected member_ `UE::Geometry::FFrame3d InitialGizmoFrame;`
- L144 _protected member_ `FVector3d InitialGizmoScale;`
- L145 _protected prototype_ `void ComputeUpdate_Gizmo();`
- L147 _protected member_ `FUVGroupTopology Topology;`
- L148 _protected prototype_ `void PrecomputeTopology();`
- L150 _protected member_ `FDynamicMeshAABBTree3 MeshSpatial;`
- L151 _protected prototype_ `FDynamicMeshAABBTree3& GetSpatial();`
- L152 _protected member_ `bool bSpatialDirty;`
- L167 _protected member_ `TArray<FEditIsland> ActiveIslands;`
- L168 _protected prototype_ `void UpdateUVTransformFromSelection(const FGroupTopologySelection& Selection);`
- L170 _protected member_ `FMeshVertexChangeBuilder* ActiveVertexChange;`
- L171 _protected prototype_ `void BeginChange();`
- L172 _protected prototype_ `void EndChange();`
- L173 _protected prototype_ `void UpdateChangeFromROI(bool bFinal);`
- L175 _protected prototype_ `void OnMaterialSettingsChanged();`

#### struct `UEditUVIslandsTool::FEditIsland`  
`struct FEditIsland`  
_L158-166_
- desc: data for current drag
- L160 _public member_ `UE::Geometry::FFrame3d LocalFrame;`
- L161 _public member_ `TArray<int32> Triangles;`
- L162 _public member_ `TArray<int32> UVs;`
- L163 _public member_ `UE::Geometry::FAxisAlignedBox2d UVBounds;`
- L164 _public member_ `FVector2d UVOrigin;`
- L165 _public member_ `TArray<FVector2f> InitialPositions;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/ExtractSplineTool.h` (Public)


#### enum `EExtractSplineMode`  
`enum class EExtractSplineMode : uint8`  
_L32-42_
- reflection: `UENUM()`
- L35 _public enumerator_ `PlaneCut = 1` — Extract splines as cross sections where a specified plane intersects the target mesh
- L38 _public enumerator_ `OpenBoundary = 2` — Extract open boundary edges on target mesh as splines
- L41 _public enumerator_ `PolygroupLoops = 3` — Extract splines from selected polygroup loop boundaries

#### class `UExtractSplineToolProperties`  
`class UExtractSplineToolProperties : public UInteractiveToolPropertySet`  
_L45-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L52 _public member_ `EExtractSplineMode ExtractionMode = EExtractSplineMode::PlaneCut;` — `UPROPERTY(EditAnywhere, Category = "Extract Splines")`

#### class `UExtractSplineTool`  
`class UExtractSplineTool : public USingleSelectionMeshEditingTool`  
_L60-120_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- desc: A tool to create splines from mesh cross sections or open mesh boundary edges.
- L67 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L68 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L69 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L70 _public function_ `virtual bool HasCancel() const override`
- L71 _public function_ `virtual bool HasAccept() const override`
- L72 _public prototype_ `virtual bool CanAccept() const override;`
- L73 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L74 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L80 _private member_ `TObjectPtr<UExtractSplineToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L83 _private member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L86 _private member_ `TObjectPtr<UPolygonSelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L88 _private member_ `TSharedPtr<UE::Geometry::FGroupTopology> Topology;`
- L89 _private prototype_ `UE::Geometry::FDynamicMeshAABBTree3& GetSpatial();`
- L90 _private member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> MeshSpatial;`
- L93 _private member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview;` — `UPROPERTY()`
- L95 _private member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> OriginalMesh;`
- L98 _private member_ `TObjectPtr<UGenerateCrossSectionOpFactory> Factory;` — `UPROPERTY()`
- L101 _private member_ `UE::Geometry::FFrame3d CutPlaneWorld;` — Cutting plane
- L104 _private member_ `TObjectPtr<UPreviewGeometry> CutlineGeometry;` — `UPROPERTY()`
- L106 _private typedef_ `typedef TArray<FVector3d> FPolygonVertices;`
- L107 _private member_ `TArray<FPolygonVertices> CutLoops;`
- L108 _private member_ `TArray<FPolygonVertices> CutSpans;`
- L110 _private prototype_ `void SetupPreviews();`
- L111 _private prototype_ `void InvalidatePreviews();`
- L112 _private prototype_ `void UpdateVisibility();`
- L113 _private prototype_ `void GetCutPlane(FVector& Origin, FVector& Normal);`
- L114 _private prototype_ `void GenerateAsset();`
- L115 _private prototype_ `void RegeneratePreviewSplines();`
- L116 _private prototype_ `void GatherSplineDataFromMeshBoundaries();`
- L117 _private prototype_ `void GatherSplineDataFromPolygroupSelection();`
- L118 _private prototype_ `void SetInteractionMode();`

#### class `UExtractSplineToolBuilder`  
`class UExtractSplineToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L123-129_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L128 _public prototype_ `virtual UExtractSplineTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L25 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/MeshBoundaryToolBase.h` (Public)


#### class `UMeshBoundaryToolBase`  
`class UMeshBoundaryToolBase : public USingleSelectionMeshEditingTool`  
_L27-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- desc: Base class for tools that do things with a mesh boundary. Provides ability to select mesh boundaries and some other boilerplate code. TODO: We can refactor to make the HoleFiller tool inherit from this.
- L33 _public function_ `virtual bool HasCancel() const override`
- L34 _public function_ `virtual bool HasAccept() const override`
- L37 _public prototype_ `virtual void Setup() override;`
- L38 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L40 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L44 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L47 _protected member_ `UE::Geometry::FDynamicMeshAABBTree3 MeshSpatial;` — Used for hit querying
- L50 _protected member_ `TObjectPtr<UPolygonSelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L75 _protected member_ `TUniquePtr<FBasicTopology> Topology;`
- L78 _protected function_ `virtual void OnSelectionChanged()` — Override in the child to respond to new loop selections.

#### class `UMeshBoundaryToolBase::FBasicTopology`  
`class FBasicTopology : public UE::Geometry::FGroupTopology`  
_L55-74_
- inherits: `UE::Geometry::FGroupTopology`
- desc: A variant of group topology that considers all triangles one group, so that group edges are boundary edges in the mesh.
- L58 _public function_ `FBasicTopology(const FDynamicMesh3* Mesh, bool bAutoBuild) : FGroupTopology(Mesh, false)`
- L70 _public function_ `int GetGroupID(int TriangleID) const override`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L17 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/MeshInspectorTool.h` (Public)


#### class `UMeshInspectorToolBuilder`  
`class UMeshInspectorToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L31-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L36 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L39 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EMeshInspectorToolDrawIndexMode`  
`enum class EMeshInspectorToolDrawIndexMode : uint8`  
_L44-51_
- reflection: `UENUM()`
- L46 _public enumerator_ `None`
- L47 _public enumerator_ `VertexID`
- L48 _public enumerator_ `TriangleID`
- L49 _public enumerator_ `GroupID`
- L50 _public enumerator_ `EdgeID`

#### class `UMeshInspectorProperties`  
`class UMeshInspectorProperties : public UInteractiveToolPropertySet`  
_L55-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L62 _public member_ `bool bWireframe = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of all mesh edges
- L66 _public member_ `bool bBoundaryEdges = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of open boundary edges
- L70 _public member_ `bool bBowtieVertices = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of bowtie vertices
- L74 _public member_ `bool bPolygonBorders = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of polygon borders
- L78 _public member_ `bool bUVSeams = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of UV seam edges
- L82 _public member_ `bool bUVBowties = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of UV bowtie vertices
- L86 _public member_ `bool bMissingUVs = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of triangles with missing UVs
- L90 _public member_ `bool bNormalSeams = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of Normal seam edges
- L94 _public member_ `bool bTangentSeams = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of Tangent seam edges
- L98 _public member_ `bool bNormalVectors = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of normal vectors
- L102 _public member_ `bool bTangentVectors = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of tangent vectors
- L106 _public member_ `bool bDrawHiddenEdgesAndSeams = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Toggle visibility of occluded boundary edges and seams
- L111 _public member_ `float NormalLength = 5.0f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "bNormalVectors", UIMin="0", UIMax="400", ClampMin = "0", ClampMax = "1000000000.0"))` — Length of line segments representing normal vectors
- L116 _public member_ `float TangentLength = 5.0f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "bTangentVectors", UIMin = "0", UIMax = "400", ClampMin = "0", ClampMax = "1000000000.0"))` — Length of line segments representing tangent vectors
- L120 _public member_ `EMeshInspectorToolDrawIndexMode ShowIndices = EMeshInspectorToolDrawIndexMode::None;` — `UPROPERTY(EditAnywhere, Category=Options)` — Draw the mesh indices of the selected type. A maximum of 500 visible indices will be rendered.

#### enum `EMeshInspectorMaterialMode`  
`enum class EMeshInspectorMaterialMode : uint8`  
_L128-148_
- reflection: `UENUM()`
- desc: Material Modes for Mesh Inspector Tool
- L131 _public enumerator_ `Original` — Input material
- L133 _public enumerator_ `FlatShaded` — Flat Shaded Material, ie with per-triangle normals
- L135 _public enumerator_ `Grey` — Grey material
- L137 _public enumerator_ `Transparent` — Transparent material, with opacity/color controls
- L139 _public enumerator_ `TangentNormal` — Tangent/Normal material
- L141 _public enumerator_ `VertexColor` — Vertex Color material
- L143 _public enumerator_ `GroupColor` — Polygroup Color material
- L145 _public enumerator_ `Checkerboard` — Checkerboard material
- L147 _public enumerator_ `Override` — Override material

#### class `UMeshInspectorMaterialProperties`  
`class UMeshInspectorMaterialProperties : public UInteractiveToolPropertySet`  
_L153-219_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: material settings for mesh inspector tool
- L160 _public member_ `EMeshInspectorMaterialMode MaterialMode = EMeshInspectorMaterialMode::Original;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial)` — Material that will be used to render the mesh
- L165 _public member_ `float CheckerDensity = 50.0f;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (UIMin = "10.0", UIMax = "100.0", ClampMin = "0.01", ClampMax = "10000.0", EditConditionHides, EditCondition = "MaterialMode == EMeshInspectorMaterialMode::Checkerboard"))` — Number of checkerboard tiles within the 0 to 1 range; only available when Checkerboard is selected as material mode
- L169 _public member_ `TObjectPtr<UMaterialInterface> OverrideMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshInspectorMaterialMode::Override"))` — Material to use instead of the original material; only available when Override is selected as material mode
- L175 _public member_ `FString UVChannel;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (DisplayName = "Preview UV Channel", GetOptions = GetUVChannelNamesFunc, EditConditionHides, EditCondition = "MaterialMode == EMeshInspectorMaterialMode::Checkerboard", NoResetToDefault))` — Which UV channel to use for visualizing the checkerboard material on the mesh; note that this does not affect the preview layout
- L178 _public member_ `TArray<FString> UVChannelNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L181 _public prototype_ `const TArray<FString>& GetUVChannelNamesFunc() const;` — `UFUNCTION()`
- L186 _public member_ `bool bFlatShading = false;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshInspectorMaterialMode::VertexColor || MaterialMode == EMeshInspectorMaterialMode::GroupColor"))` — Toggle flat shading on/off
- L190 _public member_ `FLinearColor Color = FLinearColor(0.4f, 0.4f, 0.4f);` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshInspectorMaterialMode::Diffuse"))` — Main Color of Material
- L194 _public member_ `double Opacity = 0.65;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshInspectorMaterialMode::Transparent", ClampMin = "0", ClampMax = "1.0"))` — Opacity of transparent material
- L198 _public member_ `FLinearColor TransparentMaterialColor = FLinearColor(0.0606f, 0.309f, 0.842f);` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshInspectorMaterialMode::Transparent", DisplayName = "Color"))`
- L202 _public member_ `bool bTwoSided = true;` — `UPROPERTY(EditAnywhere, Category = PreviewMaterial, meta = (EditConditionHides, EditCondition = "MaterialMode == EMeshInspectorMaterialMode::Transparent"))` — Although a two-sided transparent material causes rendering issues with overlapping faces, it is still frequently useful to see the shape when sculpting around other objects.
- L205 _public member_ `TObjectPtr<UMaterialInstanceDynamic> CheckerMaterial = nullptr;` — `UPROPERTY(meta = (TransientToolProperty))`
- L208 _public member_ `TObjectPtr<UMaterialInstanceDynamic> ActiveCustomMaterial = nullptr;` — `UPROPERTY(meta = (TransientToolProperty))`
- L211 _public prototype_ `virtual void RestoreProperties(UInteractiveTool* RestoreToTool, const FString& CacheIdentifier = TEXT("")) override;` — Needs custom restore in order to call setup
- L213 _public prototype_ `void Setup();`
- L215 _public prototype_ `void UpdateMaterials();`
- L216 _public prototype_ `UMaterialInterface* GetActiveOverrideMaterial() const;`
- L218 _public prototype_ `void UpdateUVChannels(int32 UVChannelIndex, const TArray<FString>& UVChannelNames, bool bUpdateSelection = true);`

#### class `UMeshInspectorTool`  
`class UMeshInspectorTool : public USingleSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L232-311_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Mesh Inspector Tool for visualizing mesh information
- L237 _public prototype_ `UMeshInspectorTool();`
- L239 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L241 _public prototype_ `virtual void Setup() override;`
- L242 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L244 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L245 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L247 _public function_ `virtual bool HasCancel() const override`
- L248 _public prototype_ `virtual bool HasAccept() const override;`
- L249 _public prototype_ `virtual bool CanAccept() const override;`
- L251 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L254 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L261 _public prototype_ `virtual void IncreaseLineWidthAction();`
- L262 _public prototype_ `virtual void DecreaseLineWidthAction();`
- L267 _protected member_ `TObjectPtr<UMeshInspectorProperties> Settings = nullptr;` — `UPROPERTY()`
- L270 _protected member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties = nullptr;` — `UPROPERTY()`
- L273 _protected member_ `TObjectPtr<UMeshInspectorMaterialProperties> MaterialSettings = nullptr;` — `UPROPERTY()`
- L275 _protected member_ `float LineWidthMultiplier = 1.0f;`
- L279 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L282 _protected member_ `TObjectPtr<ULineSetComponent> DrawnLineSet;` — `UPROPERTY()`
- L285 _protected member_ `TObjectPtr<UMaterialInterface> DefaultMaterial = nullptr;` — `UPROPERTY()`
- L287 _protected member_ `TArray<int> BoundaryEdges;`
- L288 _protected member_ `TArray<int> BoundaryBowties;`
- L289 _protected member_ `TArray<int> UVSeamEdges;`
- L290 _protected member_ `TArray<int> UVBowties;`
- L291 _protected member_ `TArray<int> NormalSeamEdges;`
- L292 _protected member_ `TArray<int> TangentSeamEdges;`
- L293 _protected member_ `TArray<int> GroupBoundaryEdges;`
- L294 _protected member_ `TArray<int> MissingUVTriangleEdges;`
- L296 _protected prototype_ `void UpdateVisualization();`
- L297 _protected prototype_ `void Precompute();`
- L299 _protected member_ `FViewCameraState CameraState;`
- L300 _protected member_ `FTransform LocalToWorldTransform;`
- L302 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> MeshAABBTree;`
- L303 _protected prototype_ `UE::Geometry::FDynamicMeshAABBTree3* GetSpatial();`
- L305 _protected member_ `TUniquePtr<UE::Geometry::FPolygroupSet> ActiveGroupSet;`
- L306 _protected prototype_ `void OnSelectedGroupLayerChanged();`
- L307 _protected prototype_ `void UpdateActiveGroupLayer();`
- L309 _protected member_ `bool bDrawGroupsDataValid = false;`
- L310 _protected member_ `UE::Geometry::FGroupVisualizationCache GroupVisualizationCache;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/MeshModelingToolsExp.h` (Public)


#### class `FMeshModelingToolsExpModule`  
`class FMeshModelingToolsExpModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshModelingTools, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshModelingTools, Log, All);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/MeshSelectionTool.h` (Public)


#### class `UMeshSelectionToolBuilder`  
`class UMeshSelectionToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L28-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- L33 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L34 _public prototype_ `virtual void InitializeNewTool(UMeshSurfacePointTool* Tool, const FToolBuilderState& SceneState) const override;`

#### enum `EMeshSelectionToolActions`  
`enum class EMeshSelectionToolActions`  
_L41-67_
- reflection: `UENUM()`
- L43 _public enumerator_ `NoAction`
- L45 _public enumerator_ `SelectAll`
- L46 _public enumerator_ `SelectAllByMaterial`
- L47 _public enumerator_ `ClearSelection`
- L48 _public enumerator_ `InvertSelection`
- L49 _public enumerator_ `GrowSelection`
- L50 _public enumerator_ `ShrinkSelection`
- L51 _public enumerator_ `ExpandToConnected`
- L53 _public enumerator_ `SelectLargestComponentByTriCount`
- L54 _public enumerator_ `SelectLargestComponentByArea`
- L55 _public enumerator_ `OptimizeSelection`
- L57 _public enumerator_ `DeleteSelected`
- L58 _public enumerator_ `DisconnectSelected`
- L59 _public enumerator_ `SeparateSelected`
- L60 _public enumerator_ `DuplicateSelected`
- L61 _public enumerator_ `FlipSelected`
- L62 _public enumerator_ `CreateGroup`
- L63 _public enumerator_ `SmoothBoundary`
- L65 _public enumerator_ `CycleSelectionMode`
- L66 _public enumerator_ `CycleViewMode`

#### class `UMeshSelectionToolActionPropertySet`  
`class UMeshSelectionToolActionPropertySet : public UInteractiveToolPropertySet`  
_L72-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L77 _public member_ `TWeakObjectPtr<UMeshSelectionTool> ParentTool;`
- L79 _public function_ `void Initialize(UMeshSelectionTool* ParentToolIn)`
- L81 _public prototype_ `void PostAction(EMeshSelectionToolActions Action);`

#### class `UMeshSelectionEditActions`  
`class UMeshSelectionEditActions : public UMeshSelectionToolActionPropertySet`  
_L88-163_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSelectionToolActionPropertySet`
- L95 _public function_ `void Clear()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 0))` — Clear the active triangle selection
- L102 _public function_ `void SelectAll()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 1))` — Select all triangles in the mesh
- L110 _public function_ `void Invert()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 2))` — Invert the active triangle selection
- L117 _public function_ `void Grow()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 3))` — Grow the active triangle selection to include any triangles touching a vertex on the selection boundary
- L124 _public function_ `void Shrink()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = ( DisplayPriority = 4))` — Shrink the active triangle selection by removing any triangles touching a vertex on the selection boundary
- L131 _public function_ `void FloodFill()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 5))` — Grow the active selection to include any triangle connected via shared edges (ie flood-fill)
- L138 _public function_ `void LargestTriCountPart()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 6))` — Select the largest connected mesh component by triangle count
- L145 _public function_ `void LargestAreaPart()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 7))` — Select the largest connected mesh component by mesh area
- L152 _public function_ `void OptimizeBorder()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 8))` — Optimize the selection border by removing "fin" triangles and including "ear" triangles
- L159 _public function_ `void ExpandToMaterials()` — `UFUNCTION(CallInEditor, Category = SelectionEdits, meta = (DisplayPriority = 9))` — Expand the selection to include all triangles with Materials matching the Materials on the currently selected triangles

#### class `UMeshSelectionMeshEditActions`  
`class UMeshSelectionMeshEditActions : public UMeshSelectionToolActionPropertySet`  
_L169-223_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSelectionToolActionPropertySet`
- L176 _public function_ `void Delete()` — `UFUNCTION(CallInEditor, Category = MeshEdits, meta = (DisplayName = "Delete", DisplayPriority = 1))` — Delete the selected triangles
- L183 _public function_ `void Disconnect()` — `UFUNCTION(CallInEditor, Category = MeshEdits, meta = (DisplayName = "Disconnect", DisplayPriority = 3))` — Disconnected the selected triangles from their neighbours, to create mesh boundaries along the selection borders
- L190 _public function_ `void FlipNormals()` — `UFUNCTION(CallInEditor, Category = MeshEdits, meta = (DisplayName = "Flip Normals", DisplayPriority = 4))` — Flip the normals of the selected triangles. This will create hard normals at selection borders.
- L197 _public function_ `void CreatePolygroup()` — `UFUNCTION(CallInEditor, Category = MeshEdits, meta = (DisplayName = "Create Polygroup", DisplayPriority = 5))` — Assign a new unique Polygroup index to the selected triangles
- L204 _public function_ `void Separate()` — `UFUNCTION(CallInEditor, Category = MeshEdits, meta = (DisplayName = "Separate", DisplayPriority = 10))` — Delete the selected triangles from the active Mesh Object and create a new Mesh Object containing those triangles
- L211 _public function_ `void Duplicate()` — `UFUNCTION(CallInEditor, Category = MeshEdits, meta = (DisplayName = "Duplicate", DisplayPriority = 11))` — Create a new Mesh Object containing the selected triangles
- L218 _public function_ `void SmoothBorder()` — `UFUNCTION(CallInEditor, Category = MeshEdits, meta = (DisplayPriority = 12))` — Smooth the selection border

#### enum `EMeshSelectionToolPrimaryMode`  
`enum class EMeshSelectionToolPrimaryMode`  
_L231-262_
- reflection: `UENUM()`
- L234 _public enumerator_ `Brush` — Select all triangles inside the brush area
- L237 _public enumerator_ `VolumetricBrush` — Select all triangles inside the brush volume
- L240 _public enumerator_ `AngleFiltered` — Select all triangles inside brush with normal within angular tolerance of hit triangle
- L243 _public enumerator_ `Visible` — Select all triangles inside brush that are visible from current view
- L246 _public enumerator_ `AllConnected` — Select all triangles connected to any triangle inside the brush
- L249 _public enumerator_ `AllInGroup` — Select all triangles in groups connected to any triangle inside the brush
- L252 _public enumerator_ `ByMaterial UMETA(DisplayName = "By Material (Connected)")` — Select the connected group of triangles with same material as hit triangle
- L255 _public enumerator_ `ByMaterialAll UMETA(DisplayName = "By Material (All)")` — Select all triangles with same material as hit triangle
- L258 _public enumerator_ `ByUVIsland` — Select all triangles in same UV island as hit triangle
- L261 _public enumerator_ `AllWithinAngle` — Select all triangles with normal within angular tolerance of hit triangle

#### enum `EMeshFacesColorMode`  
`enum class EMeshFacesColorMode`  
_L267-277_
- reflection: `UENUM()`
- L270 _public enumerator_ `None` — Display original mesh materials
- L272 _public enumerator_ `ByGroup` — Color mesh triangles by PolyGroup Color
- L274 _public enumerator_ `ByMaterialID` — Color mesh triangles by Material ID
- L276 _public enumerator_ `ByUVIsland` — Color mesh triangles by UV Island

#### class `UMeshSelectionToolProperties`  
`class UMeshSelectionToolProperties : public UInteractiveToolPropertySet`  
_L281-305_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L288 _public member_ `EMeshSelectionToolPrimaryMode SelectionMode = EMeshSelectionToolPrimaryMode::Brush;` — `UPROPERTY(EditAnywhere, Category = Selection)` — The Selection Mode defines the behavior of the selection brush
- L292 _public member_ `float AngleTolerance = 1.0;` — `UPROPERTY(EditAnywhere, Category = Selection, meta = (UIMin = "0.0", UIMax = "90.0"))` — Angle in Degrees used for Angle-based Selection Modes
- L296 _public member_ `bool bHitBackFaces = true;` — `UPROPERTY(EditAnywhere, Category = Selection)` — Allow the brush to hit back-facing parts of the surface
- L300 _public member_ `bool bShowPoints = false;` — `UPROPERTY(EditAnywhere, Category = Selection)` — Toggle drawing of highlight points on/off
- L304 _public member_ `EMeshFacesColorMode FaceColorMode = EMeshFacesColorMode::None;` — `UPROPERTY(EditAnywhere, Category = Selection)` — Color each triangle based on the selected mesh attribute

#### class `UMeshSelectionTool`  
`class UMeshSelectionTool : public UDynamicMeshBrushTool, public IInteractiveToolNestedAcceptCancelAPI`  
_L313-475_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDynamicMeshBrushTool,IInteractiveToolNestedAcceptCancelAPI`
- L318 _public prototype_ `UMeshSelectionTool();`
- L320 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L322 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L324 _public prototype_ `virtual void Setup() override;`
- L326 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L327 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L329 _public function_ `virtual bool HasCancel() const override`
- L330 _public function_ `virtual bool HasAccept() const override`
- L332 _public function_ `virtual bool CanAccept() const override` — virtual bool CanAccept() const override { return Super::CanAccept() && bHaveModifiedMesh; }
- L335 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;` — UBaseBrushTool overrides
- L336 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L337 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L338 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L339 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L342 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L345 _public prototype_ `virtual bool SupportsNestedCancelCommand() override;` — IInteractiveToolCancelAPI
- L346 _public prototype_ `virtual bool CanCurrentlyNestedCancel() override;`
- L347 _public prototype_ `virtual bool ExecuteNestedCancelCommand() override;`
- L350 _public prototype_ `virtual void SetGeometrySelection(UE::Geometry::FGeometrySelection&& SelectionIn);` — input selection support
- L355 _public prototype_ `virtual void RequestAction(EMeshSelectionToolActions ActionType);`
- L358 _public member_ `TObjectPtr<UMeshSelectionToolProperties> SelectionProps;` — `UPROPERTY()`
- L361 _public member_ `TObjectPtr<UMeshSelectionEditActions> SelectionActions;` — `UPROPERTY()`
- L364 _public member_ `TObjectPtr<UMeshSelectionToolActionPropertySet> EditActions;` — `UPROPERTY()`
- L367 _public member_ `TObjectPtr<UMeshStatisticsProperties> MeshStatisticsProperties;` — `UPROPERTY()`
- L370 _public member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay;` — `UPROPERTY()`
- L373 _public member_ `TObjectPtr<UMeshUVChannelProperties> UVChannelProperties = nullptr;` — `UPROPERTY()`
- L376 _public member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties = nullptr;` — `UPROPERTY()`
- L379 _protected prototype_ `virtual UMeshSelectionToolActionPropertySet* CreateEditActions();`
- L380 _protected function_ `virtual void AddSubclassPropertySets()`
- L384 _protected prototype_ `virtual void ApplyStamp(const FBrushStampData& Stamp);`
- L386 _protected prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L390 _protected member_ `UE::Geometry::FGeometrySelection InputGeometrySelection;`
- L393 _protected member_ `TObjectPtr<UMeshSelectionSet> Selection;` — `UPROPERTY()`
- L396 _protected member_ `TArray<TObjectPtr<AActor>> SpawnedActors;` — `UPROPERTY()`
- L398 _protected member_ `UWorld* TargetWorld;`
- L401 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMeshOctree3> Octree;` — note: ideally this octree would be part of PreviewMesh!
- L402 _protected member_ `bool bOctreeValid = false;`
- L403 _protected prototype_ `TUniquePtr<UE::Geometry::FDynamicMeshOctree3>& GetOctree();`
- L405 _protected member_ `EMeshSelectionElementType SelectionType = EMeshSelectionElementType::Face;`
- L407 _protected member_ `bool bInRemoveStroke = false;`
- L408 _protected member_ `FBrushStampData StartStamp;`
- L409 _protected member_ `FBrushStampData LastStamp;`
- L410 _protected member_ `bool bStampPending;`
- L412 _protected prototype_ `void UpdateFaceSelection(const FBrushStampData& Stamp, const TArray<int>& BrushROI);`
- L416 _protected member_ `TArray<int> IndexBuf;` — temp
- L417 _protected member_ `TArray<int32> TemporaryBuffer;`
- L418 _protected member_ `TSet<int32> TemporarySet;`
- L419 _protected prototype_ `void CalculateVertexROI(const FBrushStampData& Stamp, TArray<int>& VertexROI);`
- L420 _protected prototype_ `void CalculateTriangleROI(const FBrushStampData& Stamp, TArray<int>& TriangleROI);`
- L421 _protected member_ `TArray<int> PreviewBrushROI;`
- L422 _protected member_ `TBitArray<> SelectedVertices;`
- L423 _protected member_ `TBitArray<> SelectedTriangles;`
- L424 _protected prototype_ `void OnExternalSelectionChange();`
- L426 _protected prototype_ `void OnRegionHighlightUpdated(const TArray<int32>& Triangles);`
- L427 _protected prototype_ `void OnRegionHighlightUpdated(const TSet<int32>& Triangles);`
- L428 _protected prototype_ `void OnRegionHighlightUpdated();`
- L429 _protected prototype_ `void UpdateVisualization(bool bSelectionModified);`
- L430 _protected member_ `bool bFullMeshInvalidationPending = false;`
- L431 _protected member_ `bool bColorsUpdatePending = false;`
- L432 _protected prototype_ `FColor GetCurrentFaceColor(const FDynamicMesh3* Mesh, int TriangleID);`
- L433 _protected prototype_ `void CacheUVIslandIDs();`
- L434 _protected member_ `TArray<int> TriangleToUVIsland;`
- L437 _protected member_ `FMeshSelectionChangeBuilder* ActiveSelectionChange = nullptr;` — selection change
- L438 _protected prototype_ `void BeginChange(bool bAdding);`
- L439 _protected prototype_ `TUniquePtr<FToolCommandChange> EndChange();`
- L440 _protected prototype_ `void CancelChange();`
- L445 _protected member_ `bool bHavePendingAction = false;`
- L446 _protected member_ `EMeshSelectionToolActions PendingAction;`
- L447 _protected prototype_ `virtual void ApplyAction(EMeshSelectionToolActions ActionType);`
- L449 _protected prototype_ `void SelectAll();`
- L450 _protected prototype_ `void ClearSelection();`
- L451 _protected prototype_ `void InvertSelection();`
- L452 _protected prototype_ `void GrowShrinkSelection(bool bGrow);`
- L453 _protected prototype_ `void ExpandToConnected();`
- L454 _protected prototype_ `void SelectAllByMaterial();`
- L456 _protected prototype_ `void SelectLargestComponent(bool bWeightByArea);`
- L457 _protected prototype_ `void OptimizeSelection();`
- L459 _protected prototype_ `void DeleteSelectedTriangles();`
- L460 _protected prototype_ `void DisconnectSelectedTriangles();` — disconnects edges between selected and not-selected triangles; keeps all triangles in the same mesh
- L461 _protected prototype_ `void SeparateSelectedTriangles(bool bDeleteSelected);` — separates out selected triangles to a new mesh, optionally removing them from the current mesh
- L462 _protected prototype_ `void FlipSelectedTriangles();`
- L463 _protected prototype_ `void AssignNewGroupToSelectedTriangles();`
- L465 _protected prototype_ `void SmoothSelectionBoundary();`
- L467 _protected member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> ActiveGroupSet;`
- L468 _protected prototype_ `void OnSelectedGroupLayerChanged();`
- L469 _protected prototype_ `void UpdateActiveGroupLayer();`
- L472 _protected member_ `bool bHaveModifiedMesh = false;` — if true, mesh has been edited
- L474 _protected prototype_ `virtual void ApplyShutdownAction(EToolShutdownType ShutdownType);`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/MirrorTool.h` (Public)


#### class `UMirrorToolBuilder`  
`class UMirrorToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L24-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L28 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### enum `EMirrorSaveMode`  
`enum class EMirrorSaveMode : uint8`  
_L32-39_
- reflection: `UENUM()`
- L35 _public enumerator_ `InputObjects = 0` — Save the results in place of the original input objects.
- L38 _public enumerator_ `NewObjects = 1` — Save the results as new objects.

#### enum `EMirrorOperationMode`  
`enum class EMirrorOperationMode : uint8`  
_L42-49_
- reflection: `UENUM()`
- L45 _public enumerator_ `MirrorAndAppend = 0` — Append a mirrored version of the mesh to itself.
- L48 _public enumerator_ `MirrorExisting = 1` — Mirror the existing mesh.

#### enum `EMeshMirrorWeldNormalMode`  
`enum class EMeshMirrorWeldNormalMode : uint8`  
_L52-59_
- reflection: `UENUM()`
- L55 _public enumerator_ `MirrorNormals = 0` — Normals are split and mirrored across the plane.
- L58 _public enumerator_ `AverageMirrorNormals = 1` — Normals are averaged with their mirrored normal across the plane.

#### class `UMirrorToolProperties`  
`class UMirrorToolProperties : public UInteractiveToolPropertySet`  
_L62-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L70 _public member_ `EMirrorOperationMode OperationMode = EMirrorOperationMode::MirrorAndAppend;` — `UPROPERTY(EditAnywhere, Category = Options)` — Mode of operation.
- L74 _public member_ `bool bCropAlongMirrorPlaneFirst = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Cut off everything on the back side of the mirror plane before mirroring.
- L78 _public member_ `bool bSimplifyAlongCrop = true;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "bCropAlongMirrorPlaneFirst"))` — Whether to locally simplify new edges created when cropping along the mirror plane. Will only simplify when doing so will not change the shape, UVs or PolyGroups.
- L83 _public member_ `bool bWeldVerticesOnMirrorPlane = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "OperationMode == EMirrorOperationMode::MirrorAndAppend", EditConditionHides))` — Weld vertices that lie on the mirror plane. Vertices will not be welded if doing so would give an edge more than two faces, or if they are part of a face in the plane.
- L88 _public member_ `EMeshMirrorWeldNormalMode WeldVerticesNormalMode = EMeshMirrorWeldNormalMode::MirrorNormals;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "OperationMode == EMirrorOperationMode::MirrorAndAppend && bWeldVerticesOnMirrorPlane", EditConditionHides))` — The normal compute method for vertices welded along the mirror plane.
- L94 _public member_ `double PlaneTolerance = KINDA_SMALL_NUMBER;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "OperationMode == EMirrorOperationMode::MirrorAndAppend && bWeldVerticesOnMirrorPlane", EditConditionHides, UIMin = 0, UIMax = 0.01, ClampMin = 0, ClampMax = 10))` — Distance (in unscaled mesh space) to allow a point to be from the plane and still consider it "on the mirror plane".
- L99 _public member_ `bool bAllowBowtieVertexCreation = false;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = ( EditCondition = "bWeldVerticesOnMirrorPlane && OperationMode == EMirrorOperationMode::MirrorAndAppend", EditConditionHides))` — When welding, whether to allow bowtie vertices to be created, or to duplicate the vertex.
- L103 _public member_ `bool bShowPreview = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to show the preview.
- L107 _public member_ `EMirrorSaveMode WriteTo = EMirrorSaveMode::InputObjects;` — `UPROPERTY(EditAnywhere, Category = OutputOptions)` — How to save the result.

#### class `UMirrorOperatorFactory`  
`class UMirrorOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L112-125_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L118 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L121 _public member_ `TObjectPtr<UMirrorTool> MirrorTool;` — `UPROPERTY()`
- L124 _public member_ `int ComponentIndex;` — Index of the component within MirrorTool->ComponentTargets that this factory creates an operator for.

#### enum `EMirrorToolAction`  
`enum class EMirrorToolAction`  
_L128-140_
- reflection: `UENUM()`
- L130 _public enumerator_ `NoAction`
- L132 _public enumerator_ `ShiftToCenter`
- L134 _public enumerator_ `Left`
- L135 _public enumerator_ `Right`
- L136 _public enumerator_ `Up`
- L137 _public enumerator_ `Down`
- L138 _public enumerator_ `Forward`
- L139 _public enumerator_ `Backward`

#### class `UMirrorToolActionPropertySet`  
`class UMirrorToolActionPropertySet : public UInteractiveToolPropertySet`  
_L143-184_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L148 _public member_ `TWeakObjectPtr<UMirrorTool> ParentTool;`
- L150 _public function_ `void Initialize(UMirrorTool* ParentToolIn)`
- L151 _public prototype_ `void PostAction(EMirrorToolAction Action);`
- L155 _public function_ `void ShiftToCenter()` — `UFUNCTION(CallInEditor, Category = RepositionPlane)` — Move the mirror plane to center of bounding box without changing its normal.
- L159 _public member_ `bool bButtonsOnlyChangeOrientation = false;` — `UPROPERTY(EditAnywhere, Category = PresetMirrorDirections)` — If true the "Preset Mirror Directions" buttons only change the plane orientation, not location.
- L163 _public function_ `void Left()` — `UFUNCTION(CallInEditor, Category = PresetMirrorDirections, meta = (DisplayPriority = 1))` — Move the mirror plane and adjust its normal to mirror entire selection leftward.
- L167 _public function_ `void Right()` — `UFUNCTION(CallInEditor, Category = PresetMirrorDirections, meta = (DisplayPriority = 2))` — Move the mirror plane and adjust its normal to mirror entire selection rightward.
- L171 _public function_ `void Up()` — `UFUNCTION(CallInEditor, Category = PresetMirrorDirections, meta = (DisplayPriority = 3))` — Move the mirror plane and adjust its normal to mirror entire selection upward.
- L175 _public function_ `void Down()` — `UFUNCTION(CallInEditor, Category = PresetMirrorDirections, meta = (DisplayPriority = 4))` — Move the mirror plane and adjust its normal to mirror entire selection downward.
- L179 _public function_ `void Forward()` — `UFUNCTION(CallInEditor, Category = PresetMirrorDirections, meta = (DisplayPriority = 5))` — Move the mirror plane and adjust its normal to mirror entire selection forward.
- L183 _public function_ `void Backward()` — `UFUNCTION(CallInEditor, Category = PresetMirrorDirections, meta = (DisplayPriority = 6))` — Move the mirror plane and adjust its normal to mirror entire selection backward.

#### class `UMirrorTool`  
`class UMirrorTool : public UMultiSelectionMeshEditingTool, public IModifierToggleBehaviorTarget`  
_L188-248_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IModifierToggleBehaviorTarget`
- desc: Tool for mirroring one or more meshes across a plane.
- L195 _public prototype_ `UMirrorTool();`
- L197 _public prototype_ `virtual void Setup() override;`
- L198 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L200 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L201 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L203 _public function_ `virtual bool HasCancel() const override`
- L204 _public function_ `virtual bool HasAccept() const override`
- L205 _public prototype_ `virtual bool CanAccept() const override;`
- L207 _public prototype_ `void RequestAction(EMirrorToolAction ActionType);`
- L209 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L212 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IClickSequenceBehaviorTarget implementation
- L216 _protected member_ `TObjectPtr<UMirrorToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L219 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties = nullptr;` — `UPROPERTY()`
- L222 _protected member_ `TObjectPtr<UOnAcceptHandleSourcesProperties> HandleSourcesProperties = nullptr;` — `UPROPERTY()`
- L225 _protected member_ `TObjectPtr<UMirrorToolActionPropertySet> ToolActions = nullptr;` — `UPROPERTY()`
- L228 _protected member_ `TArray<TObjectPtr<UDynamicMeshReplacementChangeTarget>> MeshesToMirror;` — `UPROPERTY()`
- L231 _protected member_ `TArray<TObjectPtr<UMeshOpPreviewWithBackgroundCompute>> Previews;` — `UPROPERTY()`
- L233 _protected member_ `FVector3d MirrorPlaneOrigin = FVector3d::Zero();`
- L234 _protected member_ `FVector3d MirrorPlaneNormal = FVector3d::UnitZ();`
- L237 _protected member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic;` — `UPROPERTY()`
- L239 _protected member_ `EMirrorToolAction PendingAction;`
- L240 _protected member_ `FBox CombinedBounds;`
- L241 _protected prototype_ `void ApplyAction(EMirrorToolAction ActionType);`
- L243 _protected prototype_ `void SetupPreviews();`
- L244 _protected prototype_ `void GenerateAsset(const TArray<FDynamicMeshOpResult>& Results);`
- L247 _private prototype_ `void CheckAndDisplayWarnings();`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/PatternTool.h` (Public)


#### class `UPatternToolBuilder`  
`class UPatternToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L38-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L43 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L45 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L47 _public prototype_ `virtual void InitializeNewTool(UMultiSelectionMeshEditingTool* NewTool, const FToolBuilderState& SceneState) const override;`
- L49 _public member_ `bool bEnableCreateISMCs = true;`
- L52 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EPatternToolShape`  
`enum class EPatternToolShape : uint8`  
_L59-69_
- reflection: `UENUM()`
- L62 _public enumerator_ `Line = 0` — Arrange pattern elements along a Line
- L65 _public enumerator_ `Grid = 1` — Arrange pattern elements in a 2D Grid
- L68 _public enumerator_ `Circle = 2` — Arrange pattern elements in a Circle

#### enum `EPatternToolSingleAxis`  
`enum class EPatternToolSingleAxis : uint8`  
_L73-78_
- reflection: `UENUM()`
- L75 _public enumerator_ `XAxis = 0`
- L76 _public enumerator_ `YAxis = 1`
- L77 _public enumerator_ `ZAxis = 2`

#### enum `EPatternToolSinglePlane`  
`enum class EPatternToolSinglePlane : uint8`  
_L81-86_
- reflection: `UENUM()`
- L83 _public enumerator_ `XYPlane = 0`
- L84 _public enumerator_ `XZPlane = 1`
- L85 _public enumerator_ `YZPlane = 2`

#### enum `EPatternToolAxisSpacingMode`  
`enum class EPatternToolAxisSpacingMode : uint8`  
_L91-101_
- reflection: `UENUM()`
- L94 _public enumerator_ `ByCount = 0` — Place a specific number of Pattern Elements along the pattern geometry
- L97 _public enumerator_ `StepSize = 1` — Place Pattern Elements at regular increments along the Pattern Geometry (on-center)
- L100 _public enumerator_ `Packed = 2` — Pack in as many Pattern Elements as fits in the available space

#### class `UPatternToolSettings`  
`class UPatternToolSettings : public UInteractiveToolPropertySet`  
_L108-147_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for the Pattern Tool
- L114 _public member_ `int32 Seed = FMath::Rand();` — `UPROPERTY(EditAnywhere, Category = General, meta = (NoResetToDefault, Delta = 1, LinearDeltaSensitivity = 50))` — The seed used to introduce random transform variations when enabled
- L118 _public member_ `bool bProjectElementsDown = false;` — `UPROPERTY(EditAnywhere, Category = General)` — Whether or not the pattern items should be projected along the negative Z axis of the plane mechanic
- L122 _public member_ `float ProjectionOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = General, meta = (EditCondition = "bProjectElementsDown == true", EditConditionHides, Delta = 0.1, LinearDeltaSensitivity = 1))` — How much each pattern item should be moved along the negative Z axis of the plane mechanic if Project Elements Down is enabled
- L126 _public member_ `bool bHideSources = true;` — `UPROPERTY(EditAnywhere, Category = General)` — Hide the source meshes when enabled
- L130 _public member_ `bool bUseRelativeTransforms = true;` — `UPROPERTY(EditAnywhere, Category = General)` — If false, all pattern elements will be positioned at the origin of the first pattern element
- L134 _public member_ `bool bRandomlyPickElements = false;` — `UPROPERTY(EditAnywhere, Category = General)` — Whether to randomly pick which source mesh is scattered at each location, or to always use all source meshes
- L138 _public member_ `EPatternToolShape Shape = EPatternToolShape::Line;` — `UPROPERTY(EditAnywhere, Category = Shape)` — Shape of the underlying Pattern
- L142 _public member_ `EPatternToolSingleAxis SingleAxis = EPatternToolSingleAxis::XAxis;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (DisplayName = "Direction", EditCondition = "Shape == EPatternToolShape::Line", EditConditionHides))` — Axis direction used for the Pattern geometry
- L146 _public member_ `EPatternToolSinglePlane SinglePlane = EPatternToolSinglePlane::XYPlane;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (DisplayName = "Plane", EditCondition = "Shape != EPatternToolShape::Line", EditConditionHides))` — Plane used for the Pattern geometry

#### class `UPatternTool_BoundingBoxSettings`  
`class UPatternTool_BoundingBoxSettings : public UInteractiveToolPropertySet`  
_L153-168_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for Bounding Box adjustments in the Pattern Tool
- L159 _public member_ `bool bIgnoreTransforms = false;` — `UPROPERTY(EditAnywhere, Category = BoundingBox)` — If true, pattern element bounding boxes are not changed to account for StartScale or StartRotation
- L163 _public member_ `float Adjustment = 0.0f;` — `UPROPERTY(EditAnywhere, Category = BoundingBox, meta = (Delta = 0.1, LinearDeltaSensitivity = 1))` — Value added to the all pattern elements' bounding boxes for adjusting the behavior of packed spacing mode manually
- L167 _public member_ `bool bVisualize = false;` — `UPROPERTY(EditAnywhere, Category = BoundingBox)` — If true, the bounding boxes of each element are rendered in green and the combined bounding box of all source elements is rendered in red

#### class `UPatternTool_LinearSettings`  
`class UPatternTool_LinearSettings : public UInteractiveToolPropertySet`  
_L174-197_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for Linear Patterns in the Pattern Tool
- L180 _public member_ `EPatternToolAxisSpacingMode SpacingMode = EPatternToolAxisSpacingMode::ByCount;` — `UPROPERTY(EditAnywhere, Category = LinearPattern)` — Spacing Technique used to distribute Pattern Elements
- L184 _public member_ `int32 Count = 10;` — `UPROPERTY(EditAnywhere, Category = LinearPattern, meta = (ClampMin = 1, UIMax = 25, EditCondition = "SpacingMode == EPatternToolAxisSpacingMode::ByCount", EditConditionHides))` — Number of Pattern Elements to place
- L188 _public member_ `double StepSize = 100.0;` — `UPROPERTY(EditAnywhere, Category = LinearPattern, meta = (ClampMin = 0, EditCondition = "SpacingMode == EPatternToolAxisSpacingMode::StepSize", EditConditionHides))` — Fixed Increment used to place Pattern Elements
- L192 _public member_ `double Extent = 1000.0;` — `UPROPERTY(EditAnywhere, Category = LinearPattern, meta = (ClampMin = 0))` — Length of Pattern along the Axis
- L196 _public member_ `bool bCentered = true;` — `UPROPERTY(EditAnywhere, Category = LinearPattern)` — If true, Pattern is centered at the Origin, otherwise Pattern starts at the Origin

#### class `UPatternTool_GridSettings`  
`class UPatternTool_GridSettings : public UInteractiveToolPropertySet`  
_L207-250_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for Grid Patterns in the Pattern Tool TODO: maybe we can just re-use UPatternTool_LinearSettings for this??
- L213 _public member_ `EPatternToolAxisSpacingMode SpacingX = EPatternToolAxisSpacingMode::ByCount;` — `UPROPERTY(EditAnywhere, Category = GridPatternX)` — Spacing Technique used to distribute Pattern Elements along the Main axis
- L217 _public member_ `int32 CountX = 10;` — `UPROPERTY(EditAnywhere, Category = GridPatternX, meta = (ClampMin = 1, UIMax = 25, EditCondition = "SpacingX == EPatternToolAxisSpacingMode::ByCount", EditConditionHides))` — Number of Pattern Elements to place along the Main axis
- L221 _public member_ `double StepSizeX = 100.0;` — `UPROPERTY(EditAnywhere, Category = GridPatternX, meta = (ClampMin = 0, EditCondition = "SpacingX == EPatternToolAxisSpacingMode::StepSize", EditConditionHides))` — Fixed Increment used to place Pattern Elements along the Main axis
- L225 _public member_ `double ExtentX = 1000.0;` — `UPROPERTY(EditAnywhere, Category = GridPatternX, meta = (ClampMin = 0))` — Length/Extent of Pattern falong the Main Axis
- L229 _public member_ `bool bCenteredX = true;` — `UPROPERTY(EditAnywhere, Category = GridPatternX)` — If true, Pattern is centered at the Origin along the Main axis, otherwise Pattern starts at the Origin
- L233 _public member_ `EPatternToolAxisSpacingMode SpacingY = EPatternToolAxisSpacingMode::ByCount;` — `UPROPERTY(EditAnywhere, Category = GridPatternY)` — Spacing Technique used to distribute Pattern Elements along the Secondary axis
- L237 _public member_ `int32 CountY = 10;` — `UPROPERTY(EditAnywhere, Category = GridPatternY, meta = (ClampMin = 1, UIMax = 25, EditCondition = "SpacingY == EPatternToolAxisSpacingMode::ByCount", EditConditionHides))` — Number of  Pattern Elements to place along the Secondary axis
- L241 _public member_ `double StepSizeY = 100.0;` — `UPROPERTY(EditAnywhere, Category = GridPatternY, meta = (ClampMin = 0, EditCondition = "SpacingY == EPatternToolAxisSpacingMode::StepSize", EditConditionHides))` — Fixed Increment used to place Pattern Elements along the Secondary axis
- L245 _public member_ `double ExtentY = 1000.0;` — `UPROPERTY(EditAnywhere, Category = GridPatternY, meta = (ClampMin = 0))` — Length/Extent of Pattern falong the Secondary Axis
- L249 _public member_ `bool bCenteredY = true;` — `UPROPERTY(EditAnywhere, Category = GridPatternY)` — If true, Pattern is centered at the Origin along the Secondary axis, otherwise Pattern starts at the Origin

#### class `UPatternTool_RadialSettings`  
`class UPatternTool_RadialSettings : public UInteractiveToolPropertySet`  
_L260-295_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for Radial Patterns in the Pattern Tool
- L266 _public member_ `EPatternToolAxisSpacingMode SpacingMode = EPatternToolAxisSpacingMode::ByCount;` — `UPROPERTY(EditAnywhere, Category = RadialPattern)` — Spacing Technique used to distribute Pattern Elements around the Circle/Arc
- L270 _public member_ `int32 Count = 10;` — `UPROPERTY(EditAnywhere, Category = RadialPattern, meta = (ClampMin = 1, UIMax = 25, EditCondition = "SpacingMode == EPatternToolAxisSpacingMode::ByCount", EditConditionHides))` — Number of  Pattern Elements to place
- L274 _public member_ `double StepSize = 100.0;` — `UPROPERTY(EditAnywhere, Category = RadialPattern, meta = (Units = "Degrees", ClampMin = 0, EditCondition = "SpacingMode == EPatternToolAxisSpacingMode::StepSize", EditConditionHides))` — Fixed Increment (in Degrees) used to position Pattern Elements around the Circle/Arc
- L278 _public member_ `double Radius = 250;` — `UPROPERTY(EditAnywhere, Category = RadialPattern, meta = (ClampMin = 0))` — Radius of the Circle/Arc
- L282 _public member_ `double StartAngle = 0.0;` — `UPROPERTY(EditAnywhere, Category = RadialPattern, meta = (Units = "Degrees", UIMin = -360, UIMax = 360))` — Start angle of the Circle/Arc
- L286 _public member_ `double EndAngle = 360.0;` — `UPROPERTY(EditAnywhere, Category = RadialPattern, meta = (Units = "Degrees", UIMin = -360, UIMax = 360))` — End angle of the Circle/Arc
- L290 _public member_ `double AngleShift = 0.0;` — `UPROPERTY(EditAnywhere, Category = RadialPattern, meta = (Units = "Degrees", ClampMin = -180, ClampMax = 180))` — Fixed offset added to Start/End Angles
- L294 _public member_ `bool bOriented = true;` — `UPROPERTY(EditAnywhere, Category = RadialPattern)` — If true, Pattern elements are rotated to align with the Circle tangent

#### class `UPatternTool_RotationSettings`  
`class UPatternTool_RotationSettings : public UInteractiveToolPropertySet`  
_L304-327_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for Per Element Rotation in the Pattern Tool
- L310 _public member_ `bool bInterpolate = false;` — `UPROPERTY(EditAnywhere, Category = Rotation, meta = (InlineEditConditionToggle))` — If true, Rotation is linearly interpolated between StartRotation and Rotation values
- L314 _public member_ `bool bJitter = false;` — `UPROPERTY(EditAnywhere, Category = Rotation, meta = (InlineEditConditionToggle))` — If true, Rotation at each Pattern Element is offset by a uniformly chosen random value in the range of [-RotationJitterRange, RotationJitterRange]
- L318 _public member_ `FRotator StartRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = Rotation, meta = (UIMin = -360, UIMax = 360))` — Rotation applied to all Pattern Elements, or to first Pattern Element for Interpolated rotation
- L322 _public member_ `FRotator EndRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = Rotation, meta = (EditCondition = "bInterpolate", UIMin = -360, UIMax = 360))` — Rotation applied to last Pattern Elements for Interpolated rotation
- L326 _public member_ `FRotator Jitter = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = Rotation, meta = (ClampMin = 0, EditCondition = "bJitter", UIMin = -360, UIMax = 360))` — Upper bound of the range which is sampled to randomly rotate each Pattern Element if Jitter is true

#### class `UPatternTool_TranslationSettings`  
`class UPatternTool_TranslationSettings : public UInteractiveToolPropertySet`  
_L334-357_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for Per Element Translation in the Pattern Tool
- L340 _public member_ `bool bInterpolate = false;` — `UPROPERTY(EditAnywhere, Category = Translation, meta = (InlineEditConditionToggle))` — If true, Translation is linearly interpolated between StartTranslation and Translation values
- L344 _public member_ `bool bJitter = false;` — `UPROPERTY(EditAnywhere, Category = Translation, meta = (InlineEditConditionToggle))` — If true, Translation at each Pattern Element is offset by a uniformly chosen random value in the range of [-TranslationJitterRange, TranslationJitterRange]
- L348 _public member_ `FVector StartTranslation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Translation)` — Translation applied to all Pattern Elements, or to first Pattern Element for Interpolated translation
- L352 _public member_ `FVector EndTranslation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Translation, meta = (EditCondition = "bInterpolate"))` — Translation applied to last Pattern Element for Interpolated translation
- L356 _public member_ `FVector Jitter = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Translation, meta = (ClampMin = 0, EditCondition = "bJitter"))` — Upper bound of the range which is sampled to randomly translate each Pattern Element if Jitter is true

#### class `UPatternTool_ScaleSettings`  
`class UPatternTool_ScaleSettings : public UInteractiveToolPropertySet`  
_L363-393_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for Per Element Scale in the Pattern Tool
- L368 _public member_ `static constexpr double MinScale = 0.001;` — Initial value for Jitter and referenced in FPatternGenerator when applying scale jitter. Can't be used for ClampMin.
- L372 _public member_ `bool bProportional = true;` — `UPROPERTY(EditAnywhere, Category = Scale)` — If true, changes to Start Scale, End Scale, and Jitter are proportional along all the axes
- L376 _public member_ `bool bInterpolate = false;` — `UPROPERTY(EditAnywhere, Category = Scale, meta = (InlineEditConditionToggle))` — If true, Scale is linearly interpolated between StartScale and Scale values
- L380 _public member_ `bool bJitter = false;` — `UPROPERTY(EditAnywhere, Category = Scale, meta = (InlineEditConditionToggle))` — If true, Scale at each Pattern Element is offset by a uniformly chosen random value in the range of [-ScaleJitterRange, ScaleJitterRange]
- L384 _public member_ `FVector StartScale = FVector::OneVector;` — `UPROPERTY(EditAnywhere, Category = Scale, meta = (ClampMin = 0.001, Delta = 0.01, LinearDeltaSensitivity = 1))` — Scale applied to all Pattern Elements, or to first Pattern Element for Interpolated scale
- L388 _public member_ `FVector EndScale = FVector::OneVector;` — `UPROPERTY(EditAnywhere, Category = Scale, meta = (ClampMin = 0.001, EditCondition = "bInterpolate", Delta = 0.01, LinearDeltaSensitivity = 1))` — Scale applied to last Pattern Element for Interpolated scale
- L392 _public member_ `FVector Jitter = FVector(MinScale);` — `UPROPERTY(EditAnywhere, Category = Scale, meta = (ClampMin = 0.001, EditCondition = "bJitter", Delta = 0.01, LinearDeltaSensitivity = 1))` — Upper bound of the range which is sampled to randomly scale each Pattern Element if Jitter is true

#### class `UPatternTool_OutputSettings`  
`class UPatternTool_OutputSettings : public UInteractiveToolPropertySet`  
_L402-425_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Output Settings for the Pattern Tool
- L408 _public member_ `bool bSeparateActors = false;` — `UPROPERTY(EditAnywhere, Category = Output)` — Emit a separate Actor for each pattern element
- L412 _public member_ `bool bConvertToDynamic = false;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (EditCondition = "bHaveStaticMeshes == true", HideEditConditionToggle))` — Emit StaticMesh pattern elements as DynamicMeshes
- L416 _public member_ `bool bCreateISMCs = false;` — `UPROPERTY(EditAnywhere, Category = Output, meta = (EditCondition = "bHaveStaticMeshes == true && bSeparateActors == false && bConvertToDynamic == false && bEnableCreateISMCs == true", HideEditConditionToggle))` — Create InstancedStaticMeshComponents instead multiple StaticMeshComponents, for StaticMesh pattern elements
- L420 _public member_ `bool bHaveStaticMeshes = false;` — `UPROPERTY(meta = (TransientToolProperty))` — internal, used to control state of Instance settings
- L424 _public member_ `bool bEnableCreateISMCs = true;` — `UPROPERTY(meta = (TransientToolProperty))` — internal, used to disable the creation of ISMCs

#### class `UPatternTool`  
`class UPatternTool : public UMultiSelectionMeshEditingTool`  
_L436-619_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool`
- desc: UPatternTool takes input meshes and generates 3D Patterns of those meshes, by placing repeated copies along geometric paths like lines, grids, circles, etc. The output can be a single Actor per pattern Element, or combined into single Actors in various ways depending on the input mesh type.
- L441 _public prototype_ `UPatternTool();`
- L443 _public prototype_ `virtual void Setup() override;`
- L444 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L446 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L448 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L450 _public function_ `virtual bool HasCancel() const override`
- L451 _public function_ `virtual bool HasAccept() const override`
- L452 _public function_ `virtual bool CanAccept() const override`
- L454 _public prototype_ `virtual void SetEnableCreateISMCs(bool bEnable);`
- L458 _public member_ `TObjectPtr<UPatternToolSettings> Settings;` — `UPROPERTY()`
- L461 _public member_ `TObjectPtr<UPatternTool_BoundingBoxSettings> BoundingBoxSettings;` — `UPROPERTY()`
- L464 _public member_ `TObjectPtr<UPatternTool_LinearSettings> LinearSettings;` — `UPROPERTY()`
- L467 _public member_ `TObjectPtr<UPatternTool_GridSettings> GridSettings;` — `UPROPERTY()`
- L470 _public member_ `TObjectPtr<UPatternTool_RadialSettings> RadialSettings;` — `UPROPERTY()`
- L473 _public member_ `TObjectPtr<UPatternTool_RotationSettings> RotationSettings;` — `UPROPERTY()`
- L476 _public member_ `TObjectPtr<UPatternTool_TranslationSettings> TranslationSettings;` — `UPROPERTY()`
- L479 _public member_ `TObjectPtr<UPatternTool_ScaleSettings> ScaleSettings;` — `UPROPERTY()`
- L481 _public member_ `FVector CachedStartScale;`
- L482 _public member_ `FVector CachedEndScale;`
- L483 _public member_ `FVector CachedJitterScale;`
- L485 _public member_ `int32 StartScaleWatcherIdx;`
- L486 _public member_ `int32 EndScaleWatcherIdx;`
- L487 _public member_ `int32 JitterScaleWatcherIdx;`
- L490 _public member_ `TObjectPtr<UPatternTool_OutputSettings> OutputSettings;` — `UPROPERTY()`
- L498 _protected member_ `TObjectPtr<UComponentBoundTransformProxy> PatternGizmoProxy = nullptr;` — `UPROPERTY()`
- L501 _protected member_ `TObjectPtr<UInteractiveGizmo> PatternGizmo = nullptr;` — `UPROPERTY()`
- L504 _protected member_ `TObjectPtr<UPrimitiveComponent> PatternGizmoComponent = nullptr;` — `UPROPERTY()`
- L507 _protected member_ `bool bUsingSingleAxis;` — If true, Settings->SingleAxis is being used. If false, Settings->SinglePlane is being used
- L509 _protected member_ `int32 LinearExtentWatcherIdx;`
- L510 _protected member_ `int32 GridExtentXWatcherIdx;`
- L511 _protected member_ `int32 GridExtentYWatcherIdx;`
- L512 _protected member_ `int32 RadiusWatcherIdx;`
- L514 _protected prototype_ `void OnTransformGizmoUpdated(UTransformProxy* Proxy, FTransform Transform);`
- L515 _protected prototype_ `void ResetTransformGizmoPosition();`
- L516 _protected prototype_ `void ReconstructTransformGizmos();`
- L519 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L522 _protected member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L524 _protected member_ `UE::Geometry::FFrame3d CurrentStartFrameWorld;`
- L525 _protected member_ `TArray<UE::Geometry::FTransformSRT3d> CurrentPattern;`
- L527 _protected member_ `bool bPatternNeedsUpdating = false;`
- L528 _protected member_ `FDateTime LastPatternUpdateTime;`
- L529 _protected prototype_ `void MarkPatternDirty();`
- L531 _protected prototype_ `void OnSourceVisibilityToggled(bool bVisible);`
- L532 _protected prototype_ `void OnMainFrameUpdated();`
- L533 _protected prototype_ `void OnShapeUpdated();`
- L534 _protected prototype_ `void OnSingleAxisUpdated();`
- L535 _protected prototype_ `void OnSinglePlaneUpdated();`
- L536 _protected prototype_ `void OnSpacingModeUpdated();`
- L537 _protected prototype_ `void OnParametersUpdated();`
- L538 _protected prototype_ `void UpdatePattern();`
- L539 _protected prototype_ `void ComputeWorldTransform(FTransform& OutWorldTransform, const FTransform& InElementTransform, const FTransform& InPatternTransform) const;`
- L540 _protected prototype_ `void GetPatternTransforms_Linear(TArray<UE::Geometry::FTransformSRT3d>& TransformsOut);`
- L541 _protected prototype_ `void GetPatternTransforms_Grid(TArray<UE::Geometry::FTransformSRT3d>& TransformsOut);`
- L542 _protected prototype_ `void GetPatternTransforms_Radial(TArray<UE::Geometry::FTransformSRT3d>& TransformsOut);`
- L544 _protected prototype_ `void RenderBoundingBoxes(IToolsContextRenderAPI* RenderAPI);`
- L545 _protected member_ `FToolDataVisualizer BoundingBoxVisualizer;`
- L569 _protected member_ `TArray<FPatternElement> Elements;`
- L570 _protected member_ `UE::Geometry::FAxisAlignedBox3d CombinedPatternBounds = UE::Geometry::FAxisAlignedBox3d::Empty();` — The bounding box that contains all of the elements' PatternBounds bounding boxes. Used for packed mode spacing
- L572 _protected prototype_ `void ComputePatternBounds(int32 ElemIdx);`
- L573 _protected prototype_ `void ComputeCombinedPatternBounds();`
- L577 _protected prototype_ `void ComputeBoundingBoxWithTransform(int32 ElemIdx, UE::Geometry::FAxisAlignedBox3d& BoundingBox, const UE::Geometry::FTransformSRT3d& Transform);` — Given an Element index and an FTransformSRT3d, determine the bounding box that contains the transformed underlying mesh BoundingBox is made empty before growing to contain the transformed mesh.
- L579 _protected member_ `bool bHaveNonUniformScaleElements = false;`
- L581 _protected member_ `bool bEnableCreateISMCs = true;`
- L587 _protected member_ `TArray<FComponentSet> PreviewComponents;`
- L592 _protected member_ `TArray<const UPrimitiveComponent*> AllPreviewComponents;` — This duplicates the data stored by PreviewComponents but it is necessary to have a simple TArray<UPrimitiveComponent*> of all preview components when raycasting, otherwise the raycasts will hit the preview components from the previous frame.
- L596 _protected member_ `TSet<TObjectPtr<UPrimitiveComponent>> AllComponents;` — `UPROPERTY()` — to keep components in FComponentSet alive
- L599 _protected member_ `TMap<int32, FComponentSet> StaticMeshPools;`
- L600 _protected prototype_ `UStaticMeshComponent* GetPreviewStaticMesh(const FPatternElement& Element);`
- L601 _protected prototype_ `void ReturnStaticMeshes(FPatternElement& Element, FComponentSet& ComponentSet);`
- L603 _protected member_ `TMap<int32, FComponentSet> DynamicMeshPools;`
- L604 _protected prototype_ `UDynamicMeshComponent* GetPreviewDynamicMesh(const FPatternElement& Element);`
- L605 _protected prototype_ `void ReturnDynamicMeshes(FPatternElement& Element, FComponentSet& ComponentSet);`
- L607 _protected prototype_ `void HideReturnedPreviewMeshes();`
- L611 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeometry = nullptr;` — `UPROPERTY()` — parent actor for all preview components
- L614 _protected prototype_ `void InitializeElements();`
- L615 _protected prototype_ `void ResetPreviews();`
- L616 _protected prototype_ `void DestroyPreviews();`
- L618 _protected prototype_ `void EmitResults();`

#### struct `UPatternTool::FPatternElement`  
`struct FPatternElement`  
_L547-568_
- L549 _public member_ `int32 TargetIndex = 0;`
- L552 _public member_ `bool bValid = true;` — todo: This is no longer necessary now that InitializeNewTool filters out invalid targets.
- L554 _public member_ `UPrimitiveComponent* SourceComponent = nullptr;`
- L555 _public member_ `TArray<UMaterialInterface*> SourceMaterials;`
- L556 _public member_ `UE::Geometry::FTransformSRT3d SourceTransform = UE::Geometry::FTransformSRT3d::Identity();`
- L557 _public member_ `UE::Geometry::FTransformSRT3d BaseRotateScale = UE::Geometry::FTransformSRT3d::Identity();`
- L561 _public member_ `FVector3d RelativePosition = FVector3d::ZeroVector;` — We don't need to store rotation or scale relative to first element because that is handled by BaseRotateScale
- L563 _public member_ `UDynamicMesh* SourceDynamicMesh = nullptr;`
- L564 _public member_ `UStaticMesh* SourceStaticMesh = nullptr;`
- L566 _public member_ `UE::Geometry::FAxisAlignedBox3d LocalBounds = UE::Geometry::FAxisAlignedBox3d::Empty();` — The unchanged bounding box of the source mesh. Only used indirectly through PatternBounds
- L567 _public member_ `UE::Geometry::FAxisAlignedBox3d PatternBounds = UE::Geometry::FAxisAlignedBox3d::Empty();` — The bounding box used for computing CombinedPatternBounds for packed spacing. By default this box adapts to StartScale/StartRotation

#### struct `UPatternTool::FComponentSet`  
`struct FComponentSet`  
_L583-586_
- L585 _public member_ `TArray<UPrimitiveComponent*> Components;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Physics/CollisionGeometryVisualization.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PhysicsTools` (scope `UE`)
- L19 _prototype_ `void InitializeCollisionGeometryVisualization( UPreviewGeometry* PreviewGeom, UCollisionGeometryVisualizationProperties* Settings, const FPhysicsDataCollection& PhysicsData, float DepthBias = 0.f, int32 CircleStepResolution = 16, bool bClearExistingLinesAndTriangles = true);` (scope `UE::PhysicsTools`) — Create triangle sets (solids) and line sets (wireframes) in a UPreviewGeometry for all the elements in a Physics Data Collection. In line sets, Spheres and Capsules are drawn as 3-axis wireframes. Convexes are added as wireframes. By default, clear existing lines and triangles from the preview
- L30 _prototype_ `void UpdateCollisionGeometryVisualization( UPreviewGeometry* PreviewGeom, UCollisionGeometryVisualizationProperties* Settings);` (scope `UE::PhysicsTools`) — Update line sets in a UPreviewGeometry.
- L44 _prototype_ `void PartiallyInitializeCollisionGeometryVisualization( UPreviewGeometry* PartialPreviewGeom, UCollisionGeometryVisualizationProperties* Settings, const FPhysicsDataCollection& PhysicsData, int32 ColorIndex, float DepthBias = 0.f, int32 CircleStepResolution = 16);` (scope `UE::PhysicsTools`) — Like InitializeCollisionGeometryVisualization but only initializes part of the collision geometry visualization. The ColorIndex parameter is used to implement Settings->bRandomColors since pseudorandom colors are determined using unique integers for each line/triangle set, which may be stored in separate UPreviewGeometry objects. Since the initialization is partial this function doesn't set Settings->bVisualizationDirty, the caller should do that.
- L59 _prototype_ `void PartiallyUpdateCollisionGeometryVisualization( UPreviewGeometry* PartialPreviewGeom, UCollisionGeometryVisualizationProperties* Settings, int32 ColorIndex);` (scope `UE::PhysicsTools`) — Like UpdateCollisionGeometryVisualization but only updates part of the collision geometry visualization. The ColorIndex parameter is used implement Settings->bRandomColors since pseudorandom colors are determined using unique integers for each line/triangle set, which may be stored in separate UPreviewGeometry objects. Since the update is partial this function doesn't check or set Settings->bVisualizationDirty, the caller should do that.

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Physics/CollisionPropertySets.h` (Public)


#### enum `ECollisionGeometryMode`  
`enum class ECollisionGeometryMode`  
_L18-28_
- reflection: `UENUM()`
- L21 _public enumerator_ `Default = CTF_UseDefault` — Use project physics settings (DefaultShapeComplexity)
- L23 _public enumerator_ `SimpleAndComplex = CTF_UseSimpleAndComplex` — Create both simple and complex shapes. Simple shapes are used for regular scene queries and collision tests. Complex shape (per poly) is used for complex scene queries.
- L25 _public enumerator_ `UseSimpleAsComplex = CTF_UseSimpleAsComplex` — Create only simple shapes. Use simple shapes for all scene queries and collision tests.
- L27 _public enumerator_ `UseComplexAsSimple = CTF_UseComplexAsSimple` — Create only complex shapes (per poly). Use complex shapes for all scene queries and collision tests. Can be used in simulation for static shapes only (i.e can be collided against but not moved through forces or velocity.)

#### struct `FPhysicsSphereData`  
`struct FPhysicsSphereData`  
_L32-45_
- reflection: `USTRUCT()`
- L37 _public member_ `float Radius = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)`
- L40 _public member_ `FTransform Transform;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)`
- L44 _public member_ `FKShapeElem Element;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)` — Shape Element storing standard collision and physics properties for a shape

#### struct `FPhysicsBoxData`  
`struct FPhysicsBoxData`  
_L48-61_
- reflection: `USTRUCT()`
- L53 _public member_ `FVector Dimensions = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)`
- L56 _public member_ `FTransform Transform;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)`
- L60 _public member_ `FKShapeElem Element;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)` — Shape Element storing standard collision and physics properties for a shape

#### struct `FPhysicsCapsuleData`  
`struct FPhysicsCapsuleData`  
_L64-80_
- reflection: `USTRUCT()`
- L69 _public member_ `float Radius = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)`
- L72 _public member_ `float Length = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)`
- L75 _public member_ `FTransform Transform;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)`
- L79 _public member_ `FKShapeElem Element;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)` — Shape Element storing standard collision and physics properties for a shape

#### struct `FPhysicsConvexData`  
`struct FPhysicsConvexData`  
_L83-96_
- reflection: `USTRUCT()`
- L88 _public member_ `int32 NumVertices = 0;` — `UPROPERTY(VisibleAnywhere, Category = Convex)`
- L91 _public member_ `int32 NumFaces = 0;` — `UPROPERTY(VisibleAnywhere, Category = Convex)`
- L95 _public member_ `FKShapeElem Element;` — `UPROPERTY(VisibleAnywhere, Category = Sphere)` — Shape Element storing standard collision and physics properties for a shape

#### struct `FPhysicsLevelSetData`  
`struct FPhysicsLevelSetData`  
_L99-106_
- reflection: `USTRUCT()`
- L105 _public member_ `FKShapeElem Element;` — `UPROPERTY(VisibleAnywhere, Category = LevelSet)` — Shape Element storing standard collision and physics properties for a shape

#### class `UPhysicsObjectToolPropertySet`  
`class UPhysicsObjectToolPropertySet : public UInteractiveToolPropertySet`  
_L109-138_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L116 _public member_ `FString ObjectName;` — `UPROPERTY(VisibleAnywhere, Category = PhysicsData)` — Source Object Name
- L120 _public member_ `ECollisionGeometryMode CollisionType;` — `UPROPERTY(VisibleAnywhere, Category = PhysicsData)` — Collision Flags controlling how simple and complex collision shapes are used
- L123 _public member_ `TArray<FPhysicsSphereData> Spheres;` — `UPROPERTY(VisibleAnywhere, Category = PhysicsData)`
- L126 _public member_ `TArray<FPhysicsBoxData> Boxes;` — `UPROPERTY(VisibleAnywhere, Category = PhysicsData)`
- L129 _public member_ `TArray<FPhysicsCapsuleData> Capsules;` — `UPROPERTY(VisibleAnywhere, Category = PhysicsData)`
- L132 _public member_ `TArray<FPhysicsConvexData> Convexes;` — `UPROPERTY(VisibleAnywhere, Category = PhysicsData)`
- L135 _public member_ `TArray<FPhysicsLevelSetData> LevelSets;` — `UPROPERTY(VisibleAnywhere, Category = PhysicsData)`
- L137 _public prototype_ `void Reset();`

#### class `UCollisionGeometryVisualizationProperties`  
`class UCollisionGeometryVisualizationProperties : public UInteractiveToolPropertySet`  
_L144-227_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L150 _public prototype_ `void Initialize(UInteractiveTool* Tool);` — Sets materials and registers property watchers to set bVisualizationDirty to true when any property changes
- L157 _public prototype_ `FColor GetLineSetColor(int32 LineSetIndex = 0) const;` — Returns the line set color. If bRandomColors == true  LineSetIndex is used to choose the color If bRandomColors == false LineSetIndex is ignored and this->Color is returned
- L160 _public function_ `FColor GetTriangleSetColor(int32 TriangleSetIndex = 0) const` — @return The color used for solid rendering. Currently uses the same colors as the lines.
- L165 _public function_ `UMaterialInterface* GetLineMaterial() const`
- L173 _public function_ `UMaterialInterface* GetSolidMaterial() const` — @return the material to use for triangle rendering, when bShowSolid is true
- L182 _public member_ `bool bShowCollision = true;` — `UPROPERTY(EditAnywhere, Category = "Collision Visualization", meta = (EditCondition = "bEnableShowCollision", EditConditionHides, HideEditConditionToggle))` — Show/hide collision geometry
- L187 _public member_ `bool bShowSolid = false;` — `UPROPERTY(EditAnywhere, Category = "Collision Visualization", meta = (EditCondition = "bEnableShowSolid", EditConditionHides, HideEditConditionToggle))` — Whether to show solid shapes in addition to wireframes
- L191 _public member_ `float LineThickness = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "Collision Visualization")` — Thickness of lines used to visualize collision shapes
- L195 _public member_ `bool bShowHidden = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Show Hidden Lines", Category = "Collision Visualization")` — Show occluded parts of the collision geometry, rendered with dashed lines
- L199 _public member_ `bool bRandomColors = true;` — `UPROPERTY(EditAnywhere, Category = "Collision Visualization")` — Render each collision geometry with a randomly-chosen color
- L204 _public member_ `FColor Color = FColor::Red;` — `UPROPERTY(EditAnywhere, Category = "Collision Visualization", meta = (EditCondition = "!bRandomColors"))` — The color to use for all collision visualizations, if random colors are not used
- L208 _public member_ `TObjectPtr<UMaterialInterface> LineMaterial = nullptr;` — `UPROPERTY(Transient, meta=(TransientToolProperty))`
- L212 _public member_ `TObjectPtr<UMaterialInterface> LineMaterialShowingHidden = nullptr;` — `UPROPERTY(Transient, meta=(TransientToolProperty))`
- L216 _public member_ `TObjectPtr<UMaterialInterface> TriangleMaterial = nullptr;` — `UPROPERTY(Transient, meta = (TransientToolProperty))`
- L220 _public member_ `bool bEnableShowCollision = true;` — `UPROPERTY(Transient, meta=(TransientToolProperty))`
- L224 _public member_ `bool bEnableShowSolid = true;` — `UPROPERTY(Transient, meta = (TransientToolProperty))`
- L226 _public member_ `bool bVisualizationDirty = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L232 _namespace_ `namespace UE`
- L234 _namespace_ `namespace PhysicsTools` (scope `UE`)
- L236 _prototype_ `void InitializePhysicsToolObjectPropertySet(const FPhysicsDataCollection* PhysicsData, UPhysicsObjectToolPropertySet* PropSet);` (scope `UE::PhysicsTools`)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Physics/ExtractCollisionGeometryTool.h` (Public)


#### class `UExtractCollisionGeometryToolBuilder`  
`class UExtractCollisionGeometryToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L18-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L23 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L26 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EExtractCollisionOutputType`  
`enum class EExtractCollisionOutputType : uint8`  
_L31-37_
- reflection: `UENUM()`
- L34 _public enumerator_ `Simple = 0` — Simple Collision shapes (Box, Sphere, Capsule, Convex)
- L36 _public enumerator_ `Complex = 1` — Complex Collision Mesh

#### class `UExtractCollisionToolProperties`  
`class UExtractCollisionToolProperties : public UInteractiveToolPropertySet`  
_L41-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L47 _public member_ `EExtractCollisionOutputType CollisionType = EExtractCollisionOutputType::Simple;` — `UPROPERTY(EditAnywhere, Category = Options)` — Type of collision geometry to convert to Mesh
- L51 _public member_ `bool bOutputSeparateMeshes = true;` — `UPROPERTY(EditAnywhere, Category = Options, Meta = (EditCondition = "CollisionType == EExtractCollisionOutputType::Simple"))` — Whether or not to generate a seperate Mesh Object for each Simple Collision Shape
- L55 _public member_ `bool bShowPreview = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Show/Hide a preview of the generated mesh (overlaps source mesh)
- L59 _public member_ `bool bShowInputMesh = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "CollisionType != EExtractCollisionOutputType::Complex || !bShowPreview"))` — Show/Hide input mesh
- L63 _public member_ `bool bWeldEdges = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Options, Meta = (EditCondition = "CollisionType == EExtractCollisionOutputType::Complex"))` — Whether or not to weld coincident border edges of the Complex Collision Mesh (if possible)

#### class `UExtractCollisionGeometryTool`  
`class UExtractCollisionGeometryTool : public USingleSelectionMeshEditingTool`  
_L72-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- desc: Mesh Inspector Tool for visualizing mesh information
- L76 _public prototype_ `virtual void Setup() override;`
- L77 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L79 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L81 _public function_ `virtual bool HasCancel() const override`
- L82 _public function_ `virtual bool HasAccept() const override`
- L83 _public prototype_ `virtual bool CanAccept() const override;`
- L89 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()` — Property set for type of output object (StaticMesh, Volume, etc)
- L92 _protected member_ `TObjectPtr<UExtractCollisionToolProperties> Settings;` — `UPROPERTY()`
- L95 _protected member_ `TObjectPtr<UCollisionGeometryVisualizationProperties> VizSettings = nullptr;` — `UPROPERTY()`
- L98 _protected member_ `TObjectPtr<UPhysicsObjectToolPropertySet> ObjectProps;` — `UPROPERTY()`
- L102 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewElements;` — `UPROPERTY()`
- L105 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L108 _protected member_ `TSharedPtr<FPhysicsDataCollection> PhysicsInfo;` — these are TSharedPtr because TPimplPtr cannot currently be added to a TArray?
- L110 _protected member_ `TArray<TSharedPtr<UE::Geometry::FDynamicMesh3>> CurrentMeshParts;`
- L111 _protected member_ `UE::Geometry::FDynamicMesh3 CurrentMesh;`
- L112 _protected member_ `bool bResultValid = false;`
- L113 _protected prototype_ `void RecalculateMesh_Simple();`
- L114 _protected prototype_ `void RecalculateMesh_Complex();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Physics/PhysicsInspectorTool.h` (Public)


#### class `UPhysicsInspectorToolBuilder`  
`class UPhysicsInspectorToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L16-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L21 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L24 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UPhysicsInspectorToolProperties`  
`class UPhysicsInspectorToolProperties : public UInteractiveToolPropertySet`  
_L29-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L36 _public member_ `bool bShowTargetMesh = true;` — `UPROPERTY(EditAnywhere, Category = TargetVisualization)` — Show/Hide target mesh

#### class `UPhysicsInspectorTool`  
`class UPhysicsInspectorTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L44-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Mesh Inspector Tool for visualizing mesh information
- L48 _public prototype_ `virtual void Setup() override;`
- L49 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L51 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L53 _public function_ `virtual bool HasCancel() const override`
- L54 _public function_ `virtual bool HasAccept() const override`
- L55 _public function_ `virtual bool CanAccept() const override`
- L58 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L63 _public prototype_ `void OnCreatePhysics(UActorComponent* Component);`
- L68 _protected member_ `TObjectPtr<UCollisionGeometryVisualizationProperties> VizSettings = nullptr;` — `UPROPERTY()`
- L71 _protected member_ `TObjectPtr<UPhysicsInspectorToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L74 _protected member_ `TArray<TObjectPtr<UPhysicsObjectToolPropertySet>> ObjectData;` — `UPROPERTY()`
- L78 _protected member_ `TArray<TObjectPtr<UPreviewGeometry>> PreviewElements;` — `UPROPERTY()`
- L82 _private prototype_ `void InitializePreviewGeometry(bool bClearExisting);` — Helper to create or re-create preview geometry
- L84 _private member_ `FDelegateHandle OnCreatePhysicsDelegateHandle;` — Delegate to track when physics data may have been updated
- L86 _private member_ `bool bUnderlyingPhysicsObjectsUpdated = false;` — A flag to track when the preview geometry needs to be re-initialized

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Physics/SetCollisionGeometryTool.h` (Public)


#### class `USetCollisionGeometryToolBuilder`  
`class USetCollisionGeometryToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L30-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L35 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L36 _public prototype_ `virtual void InitializeNewTool(UMultiSelectionMeshEditingTool* Tool, const FToolBuilderState& SceneState) const;`
- L37 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L40 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `ESetCollisionGeometryInputMode`  
`enum class ESetCollisionGeometryInputMode`  
_L47-61_
- reflection: `UENUM()`
- L50 _public enumerator_ `CombineAll = 0` — Compute collision geometry using a combined mesh of all input objects
- L54 _public enumerator_ `PerInputObject = 1` — Compute collision geometry for each input object Note: A Geometry Selection always counts as one input object
- L57 _public enumerator_ `PerMeshComponent = 2` — Compute collision geometry for each connected component of each input object
- L60 _public enumerator_ `PerMeshGroup = 3` — Compute collision geometry for each PolyGroup of each input object

#### enum `ECollisionGeometryType`  
`enum class ECollisionGeometryType`  
_L65-95_
- reflection: `UENUM()`
- L70 _public enumerator_ `CopyFromInputs = 0` — Copy the existing collision geometry shapes from the inputs to the target. With a single-selection, always does the same thing as Empty with Append To Existing set to true.
- L72 _public enumerator_ `AlignedBoxes = 1` — Fit axis-aligned bounding boxes to the inputs
- L74 _public enumerator_ `OrientedBoxes = 2` — Fit oriented bounding boxes to the inputs
- L76 _public enumerator_ `MinimalSpheres = 3` — Fit spheres to the inputs
- L78 _public enumerator_ `Capsules = 4` — Fit capsules to the inputs
- L80 _public enumerator_ `ConvexHulls = 5` — Fit convex hulls to the inputs
- L82 _public enumerator_ `ConvexDecompositions = 8` — Fit multiple convex hulls to each input
- L84 _public enumerator_ `SweptHulls = 6` — Fit convex hulls to 2D projections of the inputs, and sweep these 2D hulls along the projection dimension
- L86 _public enumerator_ `LevelSets = 7` — Fit level sets to the inputs
- L89 _public enumerator_ `MinVolume = 10` — Note: ConvexDecomposition = 8 is set above, to be next to Convex Hulls in the UI Fit the boxes, spheres, and capsules to the inputs, and keep the best fitting of these shapes based on volume
- L94 _public enumerator_ `Empty = 11` — Do not produce new collision for inputs. If Append To Existing is false, this gives a way to empty the simple collision on the target. If Append To Existing is true, the existing collision is kept and can be passed through the optional filters in the tool, like removing enclosed shapes.

#### enum `EProjectedHullAxis`  
`enum class EProjectedHullAxis`  
_L100-112_
- reflection: `UENUM()`
- L103 _public enumerator_ `X = 0` — Project along the X axis
- L105 _public enumerator_ `Y = 1` — Project along the Y axis
- L107 _public enumerator_ `Z = 2` — Project along the Z axis
- L109 _public enumerator_ `SmallestBoxDimension = 3` — Project along the bounding box's shortest axis
- L111 _public enumerator_ `SmallestVolume = 4` — Project along each major axis, and take the result with the smallest volume

#### enum `EConvexDecompositionMethod`  
`enum class EConvexDecompositionMethod`  
_L116-122_
- reflection: `UENUM()`
- desc: Method to use to compute convex decomposition
- L119 _public enumerator_ `NavigationDriven` — Use the Navigable Space Protection's Error Tolerance and Min Radius settings to control the decomposition
- L121 _public enumerator_ `VolumetricError` — Minimize volumetric differences to the input

#### class `USetCollisionGeometryToolProperties`  
`class USetCollisionGeometryToolProperties : public UInteractiveToolPropertySet`  
_L126-282_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L133 _public member_ `ECollisionGeometryType GeometryType = ECollisionGeometryType::AlignedBoxes;` — `UPROPERTY(EditAnywhere, Category = Options)` — What kind of shapes to fit to the input. Note: Will be overridden by any enabled 'Auto Detect' settings, if close-fitting 'Auto Detect' shapes are found.
- L137 _public member_ `bool bAppendToExisting = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to keep the existing collision shapes, and append new shapes to that set. Otherwise, existing collision will be cleared.
- L141 _public member_ `bool bUseWorldSpace = false;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "bUsingMultipleInputs", EditConditionHides, HideEditConditionToggle))` — When using multiple inputs to generate our collision, whether to use the world-space position of those input. If false, inputs will be considered as if they were all centered at the same location.
- L146 _public member_ `ESetCollisionGeometryInputMode InputMode = ESetCollisionGeometryInputMode::PerInputObject;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( EditCondition = "GeometryType != ECollisionGeometryType::Empty && GeometryType != ECollisionGeometryType::CopyFromInputs"))` — What parts of the input should be separately fit with collision shapes
- L150 _public member_ `bool bRemoveContained = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to attempt to detect and remove collision shapes that are fully contained inside other collision shapes
- L154 _public member_ `bool bEnableMaxCount = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to discard all but MaxCount collision geometries with the largest volume
- L158 _public member_ `int32 MaxCount = 50;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", ClampMax = "9999999", EditCondition = "bEnableMaxCount"))` — The maximum number of collision shapes to generate. If necessary, the shapes with smallest volume will be discarded to meet this count.
- L162 _public member_ `float MinThickness = 0.01f;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (ClampMin = "0", UIMax = "10", EditCondition = "GeometryType != ECollisionGeometryType::LevelSets && GeometryType != ECollisionGeometryType::ConvexDecompositions"))` — Generated collision shapes will be expanded if they are smaller than this in any dimension. Not supported for Level Sets or Convex Decompositions.
- L166 _public member_ `bool bDetectBoxes = true;` — `UPROPERTY(EditAnywhere, Category = AutoDetectGeometryOverrides)` — Whether to override the requested Geometry Type with a box whenever a box closely fits the input shape
- L170 _public member_ `bool bDetectSpheres = true;` — `UPROPERTY(EditAnywhere, Category = AutoDetectGeometryOverrides)` — Whether to override the requested Geometry Type with a sphere whenever a sphere closely fits the input shape
- L174 _public member_ `bool bDetectCapsules = true;` — `UPROPERTY(EditAnywhere, Category = AutoDetectGeometryOverrides)` — Whether to override the requested Geometry Type with a capsule whenever a capsule closely fits the input shape
- L178 _public member_ `bool bMergeCollisionShapes = false;` — `UPROPERTY(EditAnywhere, Category = MergeCollisionShapes)` — Whether to attempt to merge the generated collision shapes, when there are more than MergeAboveCount
- L182 _public member_ `int32 MergeAboveCount = 1;` — `UPROPERTY(EditAnywhere, Category = MergeCollisionShapes, meta = (EditConditionHides, EditCondition = "bMergeCollisionShapes", ClampMin = "1"))` — Attempt to merge generated collision shapes until there are at most this many
- L186 _public member_ `bool bUseNegativeSpaceInMerge = false;` — `UPROPERTY(EditAnywhere, Category = MergeCollisionShapes, meta = (EditConditionHides, EditCondition = "bMergeCollisionShapes"))` — Whether to protect negative space while merging the generated collision shapes, using the negative space settings
- L191 _public member_ `bool bSimplifyHulls = true;` — `UPROPERTY(EditAnywhere, DisplayName = "Simplify to Face Count", Category = ConvexHulls, meta = (EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::ConvexHulls || GeometryType == ECollisionGeometryType::ConvexDecompositions"))` — Whether to simplify the convex hull down to at most a target face count.
- L196 _public member_ `int32 HullTargetFaceCount = 20;` — `UPROPERTY(EditAnywhere, Category = ConvexHulls, meta = (UIMin = "4", UIMax = "100", ClampMin = "4", ClampMax = "9999999", EditConditionHides, EditCondition = "(GeometryType == ECollisionGeometryType::ConvexHulls || GeometryType == ECollisionGeometryType::ConvexDecompositions) && bSimplifyHulls"))` — Target number of faces in the simplified hull
- L201 _public member_ `double HullSimplifyGeometryTolerance = 1.;` — `UPROPERTY(EditAnywhere, Category = ConvexHulls, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", EditConditionHides, EditCondition = "(GeometryType == ECollisionGeometryType::ConvexHulls || GeometryType == ECollisionGeometryType::ConvexDecompositions) && bSimplifyHulls"))` — Geometric tolerance to apply after simplifying to the target face count
- L206 _public member_ `bool bPreSimplifyToEdgeLength = false;` — `UPROPERTY(EditAnywhere, DisplayName = "Simplify to Edge Length", Category = ConvexHulls, meta = (EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::ConvexDecompositions"))` — Whether to simplify the input to this edge length before computing convex decomposition. Can give a decomposition result faster for large meshes.
- L211 _public member_ `double DecompositionTargetEdgeLength = 1.0;` — `UPROPERTY(EditAnywhere, DisplayName = "Target Edge Length", Category = ConvexHulls, meta = (UIMin = "0", UIMax = "100", ClampMin = "0", EditConditionHides, EditCondition = "bPreSimplifyToEdgeLength && GeometryType == ECollisionGeometryType::ConvexDecompositions"))` — Simplify the input to this edge length before computing convex decomposition. Can give a decomposition result faster for large meshes.
- L216 _public member_ `EConvexDecompositionMethod DecompositionMethod = EConvexDecompositionMethod::NavigationDriven;` — `UPROPERTY(EditAnywhere, Category = ConvexHulls, meta = ( EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::ConvexDecompositions"))` — What algorithm should be used to perform convex decomposition
- L221 _public member_ `bool bLimitHullsPerShape = false;` — `UPROPERTY(EditAnywhere, Category = ConvexHulls, meta = ( EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::ConvexDecompositions && DecompositionMethod == EConvexDecompositionMethod::NavigationDriven"))` — Whether to limit the number of convex hulls use in each decomposition
- L226 _public member_ `int32 MaxHullsPerShape = 10;` — `UPROPERTY(EditAnywhere, Category = ConvexHulls, meta = (UIMin = "1", UIMax = "100", ClampMin = "1", EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::ConvexDecompositions && (bLimitHullsPerShape || DecompositionMethod != EConvexDecompositionMethod::NavigationDriven)"))` — Maximum number of convex hulls to use in each decomposition
- L231 _public member_ `float ConvexDecompositionSearchFactor = .5;` — `UPROPERTY(EditAnywhere, DisplayName = "Max Hulls Search Factor", Category = ConvexHulls, meta = (UIMin = "0", UIMax = "2", ClampMin = "0", EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::ConvexDecompositions && (DecompositionMethod != EConvexDecompositionMethod::NavigationDriven)"))` — How much to search the space of possible decompositions beyond Max Hulls Per Shape; for larger values, will do additional work to try to better approximate mesh features (but resulting hulls may overlap more)
- L236 _public member_ `float AddHullsErrorTolerance = 0;` — `UPROPERTY(EditAnywhere, Category = ConvexHulls, meta = (UIMin = "0", UIMax = "1000", ClampMin = "0", EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::ConvexDecompositions && DecompositionMethod != EConvexDecompositionMethod::NavigationDriven"))` — Error tolerance for adding more convex hulls, in cm.  For volumetric errors, the value will be cubed (so a value of 10 indicates a 10x10x10 volume worth of error is acceptable).
- L241 _public member_ `float MinPartThickness = 0.1f;` — `UPROPERTY(EditAnywhere, Category = ConvexHulls, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::ConvexDecompositions"))` — Minimum part thickness for convex decomposition, in cm; hulls thinner than this will be merged into adjacent hulls, if possible.
- L246 _public member_ `double NegativeSpaceTolerance = 10;` — `UPROPERTY(EditAnywhere, DisplayName = "Tolerance Distance", Category = NavigableSpaceProtection, meta = (UIMin = "1", UIMax = "100", ClampMin = "0.1", EditConditionHides, EditCondition = "(GeometryType == ECollisionGeometryType::ConvexDecompositions && DecompositionMethod == EConvexDecompositionMethod::NavigationDriven) || (bMergeCollisionShapes && bUseNegativeSpaceInMerge)"))` — Navigable space closer to the input than this tolerance distance can be filled in
- L250 _public member_ `double NegativeSpaceMinRadius = 40;` — `UPROPERTY(EditAnywhere, DisplayName = "Min Radius", Category = NavigableSpaceProtection, meta = (UIMin = "1", UIMax = "200", ClampMin = "0.1", EditConditionHides, EditCondition = "(GeometryType == ECollisionGeometryType::ConvexDecompositions && DecompositionMethod == EConvexDecompositionMethod::NavigationDriven) || (bMergeCollisionShapes && bUseNegativeSpaceInMerge)"))` — Minimum radius of navigable space to protect; tunnels with radius smaller than this could be filled in
- L254 _public member_ `bool bIgnoreInternalNegativeSpace = true;` — `UPROPERTY(EditAnywhere, Category = NavigableSpaceProtection, meta = ( EditConditionHides, EditCondition = "(GeometryType == ECollisionGeometryType::ConvexDecompositions && DecompositionMethod == EConvexDecompositionMethod::NavigationDriven) || (bMergeCollisionShapes && bUseNegativeSpaceInMerge)"))` — Whether to ignore navigable space that is not accessible by from outside (e.g., closed-off interiors / air pockets)
- L259 _public member_ `float HullTolerance = 0.1f;` — `UPROPERTY(EditAnywhere, Category = SweptHulls, meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "100000", EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::SweptHulls"))` — If > 0, the polygon used to generate the swept hull will be simplified up to this distance tolerance, in cm
- L264 _public member_ `EProjectedHullAxis SweepAxis = EProjectedHullAxis::SmallestVolume;` — `UPROPERTY(EditAnywhere, Category = SweptHulls, meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "100000", EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::SweptHulls"))` — How to choose which direction to sweep when creating a swept hull
- L269 _public member_ `int32 LevelSetResolution = 10;` — `UPROPERTY(EditAnywhere, Category = LevelSets, meta = (UIMin = "3", UIMax = "100", ClampMin = "3", ClampMax = "1000", EditConditionHides, EditCondition = "GeometryType == ECollisionGeometryType::LevelSets"))` — Level set grid resolution along longest grid axis
- L273 _public member_ `ECollisionGeometryMode SetCollisionType = ECollisionGeometryMode::SimpleAndComplex;` — `UPROPERTY(EditAnywhere, Category = OutputOptions)` — Set how the physics system should interpret collision shapes on the output mesh. Does not affect what collision shapes are generated by this tool.
- L277 _public member_ `bool bShowTargetMesh = true;` — `UPROPERTY(EditAnywhere, Category = TargetVisualization)` — Show/Hide target mesh
- L281 _public member_ `bool bUsingMultipleInputs = false;` — `UPROPERTY()` — Set by the tool to tell the settings object whether the tool is using multiple inputs.

#### class `USetCollisionGeometryTool`  
`class USetCollisionGeometryTool : public UMultiSelectionMeshEditingTool, public UE::Geometry::IGenericDataOperatorFactory<FPhysicsDataCollection>, public IInteractiveToolManageGeometrySelectionAPI`  
_L292-418_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,UE::Geometry::IGenericDataOperatorFactory<FPhysicsDataCollection>,IInteractiveToolManageGeometrySelectionAPI`
- desc: Mesh Inspector Tool for visualizing mesh information
- L296 _public prototype_ `virtual void Setup() override;`
- L297 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L299 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L301 _public function_ `virtual bool HasCancel() const override`
- L302 _public function_ `virtual bool HasAccept() const override`
- L303 _public function_ `virtual bool CanAccept() const override`
- L310 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<FPhysicsDataCollection>> MakeNewOperator() override;`
- L313 _public prototype_ `void SetGeometrySelection(UE::Geometry::FGeometrySelection&& SelectionIn);`
- L316 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L324 _protected member_ `TObjectPtr<USetCollisionGeometryToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L327 _protected member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties = nullptr;` — `UPROPERTY()`
- L330 _protected member_ `TObjectPtr<UCollisionGeometryVisualizationProperties> VizSettings = nullptr;` — `UPROPERTY()`
- L333 _protected member_ `TObjectPtr<UPhysicsObjectToolPropertySet> CollisionProps = nullptr;` — `UPROPERTY()`
- L338 _protected member_ `TUniquePtr<TGenericDataBackgroundCompute<FPhysicsDataCollection>> Compute = nullptr;` — Background compute
- L342 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeom = nullptr;` — `UPROPERTY()`
- L344 _protected member_ `TArray<int32> SourceObjectIndices;`
- L345 _protected member_ `bool bSourcesHidden = false;`
- L347 _protected member_ `TArray<FDynamicMesh3> InitialSourceMeshes;`
- L349 _protected prototype_ `void OnInputModeChanged();`
- L354 _protected prototype_ `void InvalidateCompute();` — Invalidates the background compute operator.
- L376 _protected member_ `bool bInputMeshesValid = false;`
- L377 _protected member_ `TArray<TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe>> InputMeshes;`
- L378 _protected member_ `TArray<TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe>> CombinedInputMeshes;`
- L379 _protected member_ `TArray<TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe>> SeparatedInputMeshes;`
- L380 _protected member_ `TArray<TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe>> PerGroupInputMeshes;`
- L382 _protected member_ `TSharedPtr<UE::Geometry::FMeshSimpleShapeApproximation, ESPMode::ThreadSafe> InputMeshesApproximator;`
- L383 _protected member_ `TSharedPtr<UE::Geometry::FMeshSimpleShapeApproximation, ESPMode::ThreadSafe> CombinedInputMeshesApproximator;`
- L384 _protected member_ `TSharedPtr<UE::Geometry::FMeshSimpleShapeApproximation, ESPMode::ThreadSafe> SeparatedMeshesApproximator;`
- L385 _protected member_ `TSharedPtr<UE::Geometry::FMeshSimpleShapeApproximation, ESPMode::ThreadSafe> PerGroupMeshesApproximator;`
- L387 _protected prototype_ `void PrecomputeInputMeshes();`
- L388 _protected prototype_ `void InitializeDerivedMeshSet( const TArray<TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe>>& FromInputMeshes, TArray<TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe>>& ToMeshes, TFunctionRef<bool(const FDynamicMesh3*, int32, int32)> TrisConnectedPredicate);`
- L393 _protected prototype_ `void OnSelectedGroupLayerChanged();`
- L395 _protected member_ `FTransform OrigTargetTransform;`
- L396 _protected member_ `UE::Geometry::FTransformSequence3d TargetInverseTransform;`
- L397 _protected member_ `FVector TargetScale3D;`
- L399 _protected member_ `TSharedPtr<FPhysicsDataCollection, ESPMode::ThreadSafe> InitialCollision;`
- L400 _protected member_ `TSharedPtr<FPhysicsDataCollection, ESPMode::ThreadSafe> GeneratedCollision;`
- L401 _protected member_ `TSharedPtr<TArray<FPhysicsDataCollection>, ESPMode::ThreadSafe> OtherInputsCollision;`
- L402 _protected member_ `TSharedPtr<TArray<FTransform3d>, ESPMode::ThreadSafe> OtherInputsTransforms;`
- L408 _protected member_ `UE::Geometry::FGeometrySelection InputGeometrySelection;`
- L411 _protected member_ `TObjectPtr<UGeometrySelectionVisualizationProperties> GeometrySelectionVizProperties = nullptr;` — `UPROPERTY()`
- L414 _protected member_ `TObjectPtr<UPreviewGeometry> GeometrySelectionViz = nullptr;` — `UPROPERTY()`
- L417 _private prototype_ `UE::Geometry::FPolygroupSet GetActiveGroupLayer(const FDynamicMesh3* GroupLayersMesh);`

#### enum `USetCollisionGeometryTool::EDetectedCollisionGeometry`  
`enum class EDetectedCollisionGeometry`  
_L356-363_
- L358 _public enumerator_ `None`
- L359 _public enumerator_ `Sphere = 2`
- L360 _public enumerator_ `Box = 4`
- L361 _public enumerator_ `Capsule = 8`
- L362 _public enumerator_ `Convex = 16`

#### struct `USetCollisionGeometryTool::FSourceMesh`  
`struct FSourceMesh`  
_L365-374_
- L367 _public member_ `FDynamicMesh3 Mesh;`
- L369 _public member_ `EDetectedCollisionGeometry DetectedType = EDetectedCollisionGeometry::None;`
- L371 _public member_ `UE::Geometry::FSphere3d DetectedSphere;`
- L372 _public member_ `UE::Geometry::FOrientedBox3d DetectedBox;`
- L373 _public member_ `UE::Geometry::FCapsule3d DetectedCapsule;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L27 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Physics/SimpleCollisionEditorTool.h` (Public)


#### class `USimpleCollisionEditorToolBuilder`  
`class USimpleCollisionEditorToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L18-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L23 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L25 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L28 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `ESimpleCollisionEditorToolAction`  
`enum class ESimpleCollisionEditorToolAction : uint8`  
_L32-41_
- reflection: `UENUM()`
- L34 _public enumerator_ `NoAction`
- L35 _public enumerator_ `AddSphere`
- L36 _public enumerator_ `AddBox`
- L37 _public enumerator_ `AddCapsule`
- L38 _public enumerator_ `Duplicate`
- L39 _public enumerator_ `DeleteSelected`
- L40 _public enumerator_ `DeleteAll`

#### class `USimpleCollisionEditorToolActionProperties`  
`class USimpleCollisionEditorToolActionProperties : public UInteractiveToolPropertySet`  
_L44-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L49 _public member_ `TWeakObjectPtr<USimpleCollisionEditorTool> ParentTool;`
- L50 _public function_ `void Initialize(USimpleCollisionEditorTool* ParentToolIn)`
- L51 _public prototype_ `void PostAction(ESimpleCollisionEditorToolAction Action);`
- L55 _public function_ `void Duplicate()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "Duplicate"))` — Duplicate all selected simple collision shapes
- L62 _public function_ `void Delete()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "Delete Selected"))` — Remove currently selected simple collision shapes from the mesh
- L69 _public function_ `void DeleteAll()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "Delete All"))` — Remove all current simple collision shapes from the mesh
- L76 _public function_ `void AddSphere()` — `UFUNCTION(CallInEditor, Category = "Add Shapes", meta = (DisplayName = "Add Sphere"))` — Add a new simple sphere collision shape
- L83 _public function_ `void AddBox()` — `UFUNCTION(CallInEditor, Category = "Add Shapes", meta = (DisplayName = "Add Box"))` — Add a new simple box collision shape
- L90 _public function_ `void AddCapsule()` — `UFUNCTION(CallInEditor, Category = "Add Shapes", meta = (DisplayName = "Add Capsule"))` — Add a new simple capsule collision shape

#### class `USimpleCollisionEditorTool`  
`class USimpleCollisionEditorTool : public USingleSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L101-138_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Simple Collision Editing tool for updating the simple collision geometry on meshes
- L105 _public prototype_ `virtual void Setup() override;`
- L106 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L108 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L110 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L111 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L113 _public function_ `virtual bool HasCancel() const override`
- L114 _public function_ `virtual bool HasAccept() const override`
- L115 _public function_ `virtual bool CanAccept() const override`
- L118 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L126 _protected member_ `TObjectPtr<USimpleCollisionEditorToolActionProperties> ActionProperties;` — `UPROPERTY()`
- L128 _protected member_ `ESimpleCollisionEditorToolAction PendingAction = ESimpleCollisionEditorToolAction::NoAction;`
- L129 _protected prototype_ `void RequestAction(ESimpleCollisionEditorToolAction Action);`
- L130 _protected prototype_ `void ApplyAction(ESimpleCollisionEditorToolAction Action);`
- L135 _protected member_ `TSharedPtr<FPhysicsDataCollection> PhysicsInfos;`
- L136 _protected member_ `TObjectPtr<UCollisionPrimitivesMechanic> CollisionPrimitivesMechanic;`
- L137 _protected prototype_ `void InitializeObjectProperties(const FPhysicsDataCollection& PhysicsData, UPhysicsObjectToolPropertySet* PropSet);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/PlaneCutTool.h` (Public)


#### class `UPlaneCutToolBuilder`  
`class UPlaneCutToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L25-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L30 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### class `UPlaneCutToolProperties`  
`class UPlaneCutToolProperties : public UInteractiveToolPropertySet`  
_L38-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the plane cut operation
- L43 _public function_ `UPlaneCutToolProperties()`
- L48 _public member_ `bool bKeepBothHalves = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — If true, both halves of the cut are computed
- L52 _public member_ `float SpacingBetweenHalves = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "bKeepBothHalves", UIMin = "0", ClampMin = "0", Delta = 0.5, LinearDeltaSensitivity = 1))` — If keeping both halves, separate the two pieces by this amount
- L56 _public member_ `bool bExportSeparatedPiecesAsNewMeshAssets = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "bKeepBothHalves"))` — If true, meshes cut into multiple pieces will be saved as separate assets on 'accept'.
- L59 _public member_ `bool bShowPreview = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L63 _public member_ `bool bFillCutHole = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — If true, the cut surface is filled with simple planar hole fill surface(s)
- L67 _public member_ `bool bFillSpans = false;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = (EditCondition = "bFillCutHole"))` — If true, will attempt to fill cut holes even if they're ill-formed (e.g. because they connect to pre-existing holes in the geometry)
- L71 _public member_ `bool bSimplifyAlongCut = true;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay)` — If true, will simplify triangulation along plane cut when doing so will not affect the shape, UVs or PolyGroups

#### enum `EPlaneCutToolActions`  
`enum class EPlaneCutToolActions`  
_L77-82_
- reflection: `UENUM()`
- L79 _public enumerator_ `NoAction`
- L80 _public enumerator_ `Cut`
- L81 _public enumerator_ `FlipPlane`

#### class `UPlaneCutOperatorFactory`  
`class UPlaneCutOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L88-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L94 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L97 _public member_ `TObjectPtr<UPlaneCutTool> CutTool;` — `UPROPERTY()`
- L99 _public member_ `int ComponentIndex;`

#### class `UPlaneCutTool`  
`class UPlaneCutTool : public UMultiSelectionMeshEditingTool`  
_L106-190_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool`
- desc: Simple Mesh Plane Cutting Tool
- L114 _public prototype_ `UPlaneCutTool();`
- L116 _public prototype_ `virtual void Setup() override;`
- L117 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L119 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L121 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L122 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L124 _public function_ `virtual bool HasCancel() const override`
- L125 _public function_ `virtual bool HasAccept() const override`
- L126 _public prototype_ `virtual bool CanAccept() const override;`
- L129 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;`
- L132 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L137 _protected member_ `TObjectPtr<UPlaneCutToolProperties> BasicProperties;` — `UPROPERTY()`
- L140 _protected member_ `TArray<TObjectPtr<UMeshOpPreviewWithBackgroundCompute>> Previews;` — `UPROPERTY()`
- L149 _protected function_ `void Cut()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "Cut"))` — Cut with the current plane without exiting the tool (Hotkey: T)
- L156 _protected function_ `void FlipPlane()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "Flip Plane"))` — Flip the cutting plane (Hotkey: R)
- L164 _protected member_ `TArray<TObjectPtr<UDynamicMeshReplacementChangeTarget>> MeshesToCut;` — `UPROPERTY()`
- L167 _protected member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L170 _protected member_ `UE::Geometry::FFrame3d CutPlaneWorld;` — Cutting plane
- L173 _protected member_ `TArray<float> MeshUVScaleFactor;` — UV Scale factor is cached based on the bounding box of the mesh before any cuts are performed, so you don't get inconsistent UVs if you multi-cut the object to smaller sizes
- L175 _protected member_ `FViewCameraState CameraState;`
- L177 _protected member_ `EPlaneCutToolActions PendingAction = EPlaneCutToolActions::NoAction;`
- L180 _protected prototype_ `void DoCut();`
- L181 _protected prototype_ `void DoFlipPlane();`
- L183 _protected prototype_ `void SetupPreviews();`
- L185 _protected prototype_ `void InvalidatePreviews();`
- L187 _protected prototype_ `void GenerateAsset(const TArray<FDynamicMeshOpResult>& Results);`
- L189 _protected prototype_ `void UpdateVisibility();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Polymodeling/ExtrudeMeshSelectionTool.h` (Public)


#### class `UExtrudeMeshSelectionToolBuilder`  
`class UExtrudeMeshSelectionToolBuilder : public USingleTargetWithSelectionToolBuilder`  
_L24-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionToolBuilder`
- desc: ToolBuilder
- L28 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L29 _public function_ `virtual bool RequiresInputSelection() const override`

#### enum `EExtrudeMeshSelectionInteractionMode`  
`enum class EExtrudeMeshSelectionInteractionMode : uint8`  
_L34-40_
- reflection: `UENUM()`
- L37 _public enumerator_ `Interactive = 0` — Define the extrusion distance using a 3D gizmo
- L39 _public enumerator_ `Fixed = 1` — Define the extrusion distance using a slider in the Settings

#### enum `EExtrudeMeshSelectionRegionModifierMode`  
`enum class EExtrudeMeshSelectionRegionModifierMode : uint8`  
_L43-51_
- reflection: `UENUM()`
- L46 _public enumerator_ `OriginalShape = 0` — Transform the original selected area
- L48 _public enumerator_ `FlattenToPlane = 1` — Flatten the extrusion area to the X/Y plane of the extrusion frame
- L50 _public enumerator_ `RaycastToPlane = 2` — Flatten the extrusion area by raycasting against the X/Y plane of the extrusion frame

#### class `UExtrudeMeshSelectionToolProperties`  
`class UExtrudeMeshSelectionToolProperties : public UInteractiveToolPropertySet`  
_L54-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L61 _public member_ `EExtrudeMeshSelectionInteractionMode InputMode = EExtrudeMeshSelectionInteractionMode::Interactive;` — `UPROPERTY(EditAnywhere, Category = "Extrude", meta = (ModelingQuickEdit))` — Control how the Extruded Area should be Transformed
- L65 _public member_ `double ExtrudeDistance = 10.0;` — `UPROPERTY(EditAnywhere, Category = "Extrude", meta = (DisplayName="Fixed Distance", UIMin = -250, UIMax = 250, EditCondition = "InputMode == EExtrudeMeshSelectionInteractionMode::Fixed", ModelingQuickEdit))` — The Extrusion Distance used in Fixed Input Mode
- L69 _public member_ `EExtrudeMeshSelectionRegionModifierMode RegionMode = EExtrudeMeshSelectionRegionModifierMode::OriginalShape;` — `UPROPERTY(EditAnywhere, Category = "Extrude")` — Control how the Extruded Area should be deformed as part of the Extrusion
- L73 _public member_ `int NumSubdivisions = 0;` — `UPROPERTY(EditAnywhere, Category = "Extrude", meta = (DisplayName="Subdivisions", UIMin = 0, UIMax = 10, ClampMin = 0, ClampMax = 1000))` — Specify the number of subdivisions along the sides of the Extrusion
- L77 _public member_ `double CreaseAngle = 60.0;` — `UPROPERTY(EditAnywhere, Category = "Extrude", meta = (UIMin = 0, UIMax = 180, Min = 0, Max = 180))` — Specify the Crease Angle used to split the sides of the Extrusion into separate Groups
- L81 _public member_ `double RaycastMaxDistance = 1000.0;` — `UPROPERTY(EditAnywhere, Category = "Extrude", meta = (DisplayName="Max Distance", UIMin = 0, UIMax = 1000, ClampMin = 0, EditCondition = "RegionMode == EExtrudeMeshSelectionRegionModifierMode::RaycastToPlane"))` — Control the maximum distance each vertex may be moved in Raycast To Plane Mode
- L85 _public member_ `bool bShellsToSolids = true;` — `UPROPERTY(EditAnywhere, Category = "Extrude")` — If the Extruded Area has a fully open border, this option determines if Extrusion will create a Solid mesh or leave the base "open"
- L89 _public member_ `bool bInferGroupsFromNbrs = true;` — `UPROPERTY(EditAnywhere, Category = "Groups", meta = (DisplayName="Propagate Groups"))` — Control whether a single Group should be generated along the sides of the Extrusion, or multiple Groups based on the adjacent Groups around the Extruded Area border
- L93 _public member_ `bool bGroupPerSubdivision = true;` — `UPROPERTY(EditAnywhere, Category = "Groups", meta=(DisplayName="Per Subdivision", EditCondition="NumSubdivisions > 0"))` — Control whether a new Group is generated for each Subdivision
- L97 _public member_ `bool bReplaceSelectionGroups = false;` — `UPROPERTY(EditAnywhere, Category = "Groups", meta=(DisplayName="Replace Cap Groups"))` — Control whether groups in the Extruded Area are mapped to new Groups, or replaced with a single new Group
- L101 _public member_ `double UVScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "UVs", meta = (DisplayName="UV Scale", UIMin = 0.001, UIMax = 10.0, ClampMin = 0.000001))` — The automatically-generated UVs on the sides of the Extrusion are scaled by this value
- L105 _public member_ `bool bUVIslandPerGroup = true;` — `UPROPERTY(EditAnywhere, Category = "UVs", meta = (DisplayName="Island Per Group"))` — Control whether a separate UV island should be generated for each output Group on the sides of the Extrusion, or a single UV island wrapping around the entire "tube"
- L109 _public member_ `bool bInferMaterialID = true;` — `UPROPERTY(EditAnywhere, Category = "Material", meta=(DisplayName="Infer Materials"))` — Control whether SetMaterialID is assigned to all triangles along the sides of the Extrusion, or if MaterialIDs should be inferred from the Extruded Area
- L113 _public member_ `int SetMaterialID = 0;` — `UPROPERTY(EditAnywhere, Category = "Material", meta=(DisplayName="Material ID", EditCondition="bInferMaterialID == false"))` — Constant Material ID used when MaterialIDs are not being inferred, or no adjacent MaterialID exists
- L117 _public member_ `bool bShowInputMaterials = false;` — `UPROPERTY(EditAnywhere, Category = "Visualization", meta=(DisplayName="Show Materials"))` — Control whether the original Mesh Materials should be shown, or a visualization of the extruded Groups

#### class `UExtrudeMeshSelectionTool`  
`class UExtrudeMeshSelectionTool : public USingleTargetWithSelectionTool`  
_L123-195_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionTool`
- L126 _private typedef_ `using FFrame3d = UE::Geometry::FFrame3d;`
- L128 _public prototype_ `UExtrudeMeshSelectionTool();`
- L130 _public prototype_ `virtual void Setup() override;`
- L131 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L133 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L134 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L136 _public function_ `virtual bool HasCancel() const override`
- L137 _public function_ `virtual bool HasAccept() const override`
- L140 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L142 _public prototype_ `FTransform GetTransform() const;`
- L143 _public prototype_ `void SetTransform(const FTransform& NewTransform);`
- L147 _protected member_ `TObjectPtr<UExtrudeMeshSelectionToolProperties> ExtrudeProperties = nullptr;` — `UPROPERTY()`
- L151 _protected member_ `FBox SelectionBoundsWorld;`
- L152 _protected member_ `UE::Geometry::FTransformSRT3d WorldTransform;`
- L154 _protected member_ `UE::Geometry::FFrame3d SelectionFrameLocal;`
- L155 _protected member_ `UE::Geometry::FFrame3d InitialFrameLocal;`
- L156 _protected member_ `UE::Geometry::FFrame3d InitialFrameWorld;`
- L157 _protected member_ `UE::Geometry::FFrame3d ExtrudeFrameWorld;`
- L158 _protected member_ `UE::Geometry::FFrame3d ExtrudeFrameLocal;`
- L159 _protected member_ `FVector3d LocalScale;`
- L161 _protected member_ `UE::Geometry::FDynamicMesh3 CurrentMesh;`
- L162 _protected member_ `TArray<int32> ExtrudeROI;`
- L163 _protected member_ `TSet<int32> ModifiedROI;`
- L164 _protected member_ `int32 MaxMaterialID = 0;` — maximum material ID on mesh (inclusive)
- L166 _protected member_ `TPimplPtr<UE::Geometry::FMeshRegionOperator> RegionOperator;`
- L167 _protected member_ `UE::Geometry::FDynamicMesh3 EditRegionMesh;`
- L168 _protected member_ `TSharedPtr<UE::Geometry::FSharedConstDynamicMesh3> EditRegionSharedMesh;`
- L170 _protected member_ `TSet<int32> RegionExtrudeROI;`
- L171 _protected member_ `TSet<int32> RegionBorderTris;`
- L173 _protected member_ `TPimplPtr<FExtrudeMeshSelectionOpFactory> OperatorFactory;`
- L177 _protected member_ `TObjectPtr<UPreviewMesh> SourcePreview = nullptr;` — `UPROPERTY()`
- L180 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> EditCompute = nullptr;` — `UPROPERTY()`
- L182 _protected prototype_ `void UpdateVisualizationSettings();`
- L184 _protected prototype_ `void Initialize_GizmoMechanic();`
- L187 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`
- L190 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L192 _protected prototype_ `void GizmoTransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L194 _protected prototype_ `void UpdateInteractionMode(EExtrudeMeshSelectionInteractionMode InteractionMode);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Polymodeling/OffsetMeshSelectionTool.h` (Public)


#### class `UOffsetMeshSelectionToolBuilder`  
`class UOffsetMeshSelectionToolBuilder : public USingleTargetWithSelectionToolBuilder`  
_L22-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionToolBuilder`
- desc: ToolBuilder
- L26 _public prototype_ `virtual USingleTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L27 _public function_ `virtual bool RequiresInputSelection() const override`

#### enum `EOffsetMeshSelectionInteractionMode`  
`enum class EOffsetMeshSelectionInteractionMode : uint8`  
_L32-36_
- reflection: `UENUM()`
- L35 _public enumerator_ `Fixed = 0` — Define the offset distance using a slider in the Settings

#### enum `EOffsetMeshSelectionDirectionMode`  
`enum class EOffsetMeshSelectionDirectionMode : uint8`  
_L39-47_
- reflection: `UENUM()`
- L42 _public enumerator_ `VertexNormals = 0`
- L44 _public enumerator_ `FaceNormals = 1`
- L46 _public enumerator_ `ConstantWidth = 2`

#### class `UOffsetMeshSelectionToolProperties`  
`class UOffsetMeshSelectionToolProperties : public UInteractiveToolPropertySet`  
_L51-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L62 _public member_ `double OffsetDistance = 10.0;` — `UPROPERTY(EditAnywhere, Category = "Offset", meta = (DisplayName="Distance", UIMin = -250, UIMax = 250, ModelingQuickEdit))` — The Extrusion Distance used in Fixed Input Mode
- L66 _public member_ `EOffsetMeshSelectionDirectionMode Direction = EOffsetMeshSelectionDirectionMode::ConstantWidth;` — `UPROPERTY(EditAnywhere, Category = "Offset")` — Control how the Offset Area should be displaced
- L70 _public member_ `int NumSubdivisions = 0;` — `UPROPERTY(EditAnywhere, Category = "Offset", meta = (DisplayName="Subdivisions", UIMin = 0, UIMax = 10, ClampMin = 0, ClampMax = 1000))` — Specify the number of subdivisions along the sides of the Extrusion
- L74 _public member_ `double CreaseAngle = 60.0;` — `UPROPERTY(EditAnywhere, Category = "Offset", meta = (UIMin = 0, UIMax = 180, Min = 0, Max = 180))` — Specify the Crease Angle used to split the sides of the Extrusion into separate Groups
- L78 _public member_ `bool bShellsToSolids = true;` — `UPROPERTY(EditAnywhere, Category = "Offset")` — If the Offset Area has a fully open border, this option determines if Extrusion will create a Solid mesh or leave the base "open"
- L82 _public member_ `bool bInferGroupsFromNbrs = true;` — `UPROPERTY(EditAnywhere, Category = "Groups", meta = (DisplayName="Propagate Groups"))` — Control whether a single Group should be generated along the sides of the Extrusion, or multiple Groups based on the adjacent Groups around the Offset Area border
- L86 _public member_ `bool bGroupPerSubdivision = true;` — `UPROPERTY(EditAnywhere, Category = "Groups", meta=(DisplayName="Per Subdivision", EditCondition="NumSubdivisions > 0"))` — Control whether a new Group is generated for each Subdivision
- L90 _public member_ `bool bReplaceSelectionGroups = false;` — `UPROPERTY(EditAnywhere, Category = "Groups", meta=(DisplayName="Replace Cap Groups"))` — Control whether groups in the Offset Area are mapped to new Groups, or replaced with a single new Group
- L94 _public member_ `double UVScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "UVs", meta = (DisplayName="UV Scale", UIMin = 0.001, UIMax = 10.0, ClampMin = 0.000001))` — The automatically-generated UVs on the sides of the Extrusion are scaled by this value
- L98 _public member_ `bool bUVIslandPerGroup = true;` — `UPROPERTY(EditAnywhere, Category = "UVs", meta = (DisplayName="Island Per Group"))` — Control whether a separate UV island should be generated for each output Group on the sides of the Extrusion, or a single UV island wrapping around the entire "tube"
- L102 _public member_ `bool bInferMaterialID = true;` — `UPROPERTY(EditAnywhere, Category = "Material", meta=(DisplayName="Infer Materials"))` — Control whether SetMaterialID is assigned to all triangles along the sides of the Extrusion, or if MaterialIDs should be inferred from the Offset Area
- L106 _public member_ `int SetMaterialID = 0;` — `UPROPERTY(EditAnywhere, Category = "Material", meta=(DisplayName="Material ID", EditCondition="bInferMaterialID == false"))` — Constant Material ID used when MaterialIDs are not being inferred, or no adjacent MaterialID exists
- L110 _public member_ `bool bShowInputMaterials = false;` — `UPROPERTY(EditAnywhere, Category = "Visualization", meta=(DisplayName="Show Materials"))` — Control whether the original Mesh Materials should be shown, or a visualization of the Offset Groups

#### class `UOffsetMeshSelectionTool`  
`class UOffsetMeshSelectionTool : public USingleTargetWithSelectionTool`  
_L116-174_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleTargetWithSelectionTool`
- L119 _private typedef_ `using FFrame3d = UE::Geometry::FFrame3d;`
- L121 _public prototype_ `UOffsetMeshSelectionTool();`
- L123 _public prototype_ `virtual void Setup() override;`
- L124 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L126 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L127 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L129 _public function_ `virtual bool HasCancel() const override`
- L130 _public function_ `virtual bool HasAccept() const override`
- L133 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI implementation
- L138 _protected member_ `TObjectPtr<UOffsetMeshSelectionToolProperties> OffsetProperties = nullptr;` — `UPROPERTY()`
- L142 _protected member_ `FBox SelectionBoundsWorld;`
- L143 _protected member_ `UE::Geometry::FTransformSRT3d WorldTransform;`
- L145 _protected member_ `UE::Geometry::FFrame3d SelectionFrameLocal;`
- L146 _protected member_ `UE::Geometry::FFrame3d InitialFrameLocal;`
- L147 _protected member_ `UE::Geometry::FFrame3d InitialFrameWorld;`
- L148 _protected member_ `UE::Geometry::FFrame3d OffsetFrameWorld;`
- L149 _protected member_ `UE::Geometry::FFrame3d OffsetFrameLocal;`
- L150 _protected member_ `FVector3d LocalScale;`
- L152 _protected member_ `UE::Geometry::FDynamicMesh3 CurrentMesh;`
- L153 _protected member_ `TArray<int32> OffsetROI;`
- L154 _protected member_ `TSet<int32> ModifiedROI;`
- L155 _protected member_ `int32 MaxMaterialID = 0;` — maximum material ID on mesh (inclusive)
- L157 _protected member_ `TPimplPtr<UE::Geometry::FMeshRegionOperator> RegionOperator;`
- L158 _protected member_ `UE::Geometry::FDynamicMesh3 EditRegionMesh;`
- L159 _protected member_ `TSharedPtr<UE::Geometry::FSharedConstDynamicMesh3> EditRegionSharedMesh;`
- L161 _protected member_ `TSet<int32> RegionOffsetROI;`
- L162 _protected member_ `TSet<int32> RegionBorderTris;`
- L164 _protected member_ `TPimplPtr<FOffsetMeshSelectionOpFactory> OperatorFactory;`
- L168 _protected member_ `TObjectPtr<UPreviewMesh> SourcePreview = nullptr;` — `UPROPERTY()`
- L171 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> EditCompute = nullptr;` — `UPROPERTY()`
- L173 _protected prototype_ `void UpdateVisualizationSettings();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Properties/MeshAnalysisProperties.h` (Public)


#### class `UMeshAnalysisProperties`  
`class UMeshAnalysisProperties : public UInteractiveToolPropertySet`  
_L19-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L26 _public member_ `FString SurfaceArea;` — `UPROPERTY(VisibleAnywhere, Category = MeshAnalysis, meta = (NoResetToDefault))` — In meters squared
- L30 _public member_ `FString Volume;` — `UPROPERTY(VisibleAnywhere, Category = MeshAnalysis, meta = (NoResetToDefault))` — In cubic meters
- L32 _public prototype_ `void Update(const FDynamicMesh3& Mesh, const FTransform& Transform);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L14 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);` — predeclarations

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/RevolveBoundaryTool.h` (Public)


#### class `URevolveBoundaryToolBuilder`  
`class URevolveBoundaryToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L25-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L30 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L31 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### class `URevolveBoundaryOperatorFactory`  
`class URevolveBoundaryOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L35-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- L41 _public prototype_ `TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;`
- L44 _public member_ `TObjectPtr<URevolveBoundaryTool> RevolveBoundaryTool;` — `UPROPERTY()`

#### class `URevolveBoundaryToolProperties`  
`class URevolveBoundaryToolProperties : public URevolveProperties`  
_L48-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URevolveProperties`
- L57 _public member_ `ERevolvePropertiesCapFillMode CapFillMode = ERevolvePropertiesCapFillMode::Delaunay;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay, meta = (DisplayAfter = "QuadSplitMode", EditCondition = "HeightOffsetPerDegree != 0 || RevolveDegrees != 360"))` — Determines how end caps are created. This is not relevant if the end caps are not visible or if the path is not closed.
- L61 _public member_ `bool bDisplayInputMesh = false;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay)` — If true, displays the original mesh in addition to the revolved boundary.
- L66 _public member_ `FVector AxisOrigin = FVector(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = RevolutionAxis, meta = (DisplayName = "Origin", Delta = 5, LinearDeltaSensitivity = 1))` — Sets the revolution axis origin.
- L71 _public member_ `FVector2D AxisOrientation;` — `UPROPERTY(EditAnywhere, Category = RevolutionAxis, meta = (DisplayName = "Orientation", UIMin = -180, UIMax = 180, ClampMin = -180000, ClampMax = 180000))` — Sets the revolution axis pitch and yaw.
- L74 _protected function_ `virtual ERevolvePropertiesCapFillMode GetCapFillMode() const override`

#### class `URevolveBoundaryTool`  
`class URevolveBoundaryTool : public UMeshBoundaryToolBase, public IClickBehaviorTarget`  
_L85-137_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshBoundaryToolBase,IClickBehaviorTarget`
- desc: Tool that revolves the boundary of a mesh around an axis to create a new mesh. Mainly useful for revolving planar meshes.
- L91 _public prototype_ `virtual bool CanAccept() const override;`
- L93 _public prototype_ `virtual void Setup() override;`
- L94 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L96 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L97 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L98 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L100 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L104 _protected member_ `bool bMoveAxisOnClick = false;` — Support for Ctrl+(Shift+)Clicking a boundary to align the revolution axis to that segment
- L105 _protected member_ `bool bAlignAxisOnClick = true;`
- L106 _protected member_ `int32 CtrlModifier = 2;`
- L107 _protected member_ `int32 ShiftModifier = 3;`
- L111 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()` — Property set for type of output object (StaticMesh, Volume, etc)
- L114 _protected member_ `TObjectPtr<URevolveBoundaryToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L117 _protected member_ `TObjectPtr<UNewMeshMaterialProperties> MaterialProperties;` — `UPROPERTY()`
- L120 _protected member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L123 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L125 _protected member_ `FVector3d RevolutionAxisOrigin;`
- L126 _protected member_ `FVector3d RevolutionAxisDirection;`
- L128 _protected prototype_ `void GenerateAsset(const FDynamicMeshOpResult& Result);`
- L129 _protected prototype_ `void UpdateRevolutionAxis();`
- L130 _protected prototype_ `void StartPreview();`
- L133 _protected prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget API
- L134 _protected prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/RevolveSplineTool.h` (Public)


#### enum `ERevolveSplineSampleMode`  
`enum class ERevolveSplineSampleMode : uint8`  
_L20-32_
- reflection: `UENUM()`
- L23 _public enumerator_ `ControlPointsOnly` — Place points only at the spline control points
- L27 _public enumerator_ `PolyLineMaxError` — Place points along the spline such that the resulting polyline has no more than some maximum deviation from the curve.
- L31 _public enumerator_ `UniformSpacingAlongCurve` — Place points along spline that are an equal spacing apart, and so that the spacing is as close as possible to some max spacing.

#### class `URevolveSplineToolProperties`  
`class URevolveSplineToolProperties : public URevolveProperties`  
_L37-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URevolveProperties`
- L45 _public member_ `ERevolveSplineSampleMode SampleMode = ERevolveSplineSampleMode::ControlPointsOnly;` — `UPROPERTY(EditAnywhere, Category = Spline)` — Determines how points to revolve are actually picked from the spline.
- L50 _public member_ `double ErrorTolerance = 1.0;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (ClampMin = 0.001, EditConditionHides, EditCondition = "SampleMode == ERevolveSplineSampleMode::PolyLineMaxError"))` — How far to allow the triangulation boundary can deviate from the spline curve before we add more vertices.
- L55 _public member_ `double MaxSampleDistance = 50.0;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (ClampMin = 0.01, EditConditionHides, EditCondition = "SampleMode == ERevolveSplineSampleMode::UniformSpacingAlongCurve"))` — The maximal distance that the spacing should be allowed to be.
- L60 _public member_ `ERevolvePropertiesCapFillMode CapFillMode = ERevolvePropertiesCapFillMode::Delaunay;` — `UPROPERTY(EditAnywhere, Category = Revolve, AdvancedDisplay, meta = (DisplayAfter = "QuadSplitMode", EditCondition = "HeightOffsetPerDegree != 0 || RevolveDegrees != 360"))` — Determines how end caps are created. This is not relevant if the end caps are not visible or if the path is not closed.
- L65 _public member_ `bool bClosePathToAxis = true;` — `UPROPERTY(EditAnywhere, Category = Revolve)` — Connect the ends of an open path to the axis to add caps to the top and bottom of the revolved result. This is not relevant for paths that are already closed.
- L70 _public member_ `FVector AxisOrigin = FVector(0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = RevolutionAxis, meta = (DisplayName = "Origin", Delta = 5, LinearDeltaSensitivity = 1))` — Sets the revolution axis origin.
- L75 _public member_ `FVector2D AxisOrientation;` — `UPROPERTY(EditAnywhere, Category = RevolutionAxis, meta = (DisplayName = "Orientation", UIMin = -180, UIMax = 180, ClampMin = -180000, ClampMax = 180000))` — Sets the revolution axis pitch and yaw.
- L82 _public member_ `bool bResetAxisOnStart = true;` — `UPROPERTY(EditAnywhere, Category = RevolutionAxis, AdvancedDisplay)` — If true, the revolution axis is re-fit to the input spline on each tool start. If false, the previous revolution axis is kept.
- L85 _protected function_ `virtual ERevolvePropertiesCapFillMode GetCapFillMode() const override`

#### enum `ERevolveSplineToolAction`  
`enum class ERevolveSplineToolAction`  
_L91-94_
- L93 _public enumerator_ `ResetAxis`

#### class `URevolveSplineToolActionPropertySet`  
`class URevolveSplineToolActionPropertySet : public UInteractiveToolPropertySet`  
_L97-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L102 _public member_ `TWeakObjectPtr<URevolveSplineTool> ParentTool;`
- L104 _public function_ `void Initialize(URevolveSplineTool* ParentToolIn)`
- L105 _public prototype_ `void PostAction(ERevolveSplineToolAction Action);`
- L109 _public function_ `void ResetAxis()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayPriority = 1))` — Fit the axis to the current curve(by aligning it to the startand end points)

#### class `URevolveSplineTool`  
`class URevolveSplineTool : public UBaseMeshFromSplinesTool`  
_L117-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseMeshFromSplinesTool`
- desc: Revolves a selected spline to create a new mesh.
- L123 _public prototype_ `virtual void RequestAction(ERevolveSplineToolAction ActionType);`
- L126 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L127 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L128 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L129 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L130 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L133 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory
- L135 _public prototype_ `virtual FString GeneratedAssetBaseName() const override;`
- L136 _public prototype_ `virtual FText TransactionName() const override;`
- L140 _protected prototype_ `virtual void OnSplineUpdate() override;` — Update the profile curve and fit plane from spline
- L143 _protected function_ `virtual FTransform3d HandleOperatorTransform(const FDynamicMeshOpResult& OpResult) override` — Keep the result mesh in the same space as set by the operator result
- L151 _private member_ `TObjectPtr<URevolveSplineToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L154 _private member_ `TObjectPtr<URevolveSplineToolActionPropertySet> ToolActions = nullptr;` — `UPROPERTY()`
- L157 _private member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L160 _private member_ `TArray<FVector3d> ProfileCurve;` — The actual points to be resolved, sampled from the spline
- L161 _private member_ `bool bProfileCurveIsClosed;`
- L164 _private member_ `FVector3d RevolutionAxisDirection;` — Axis direction in vector form (since the user modifiable values are a pitch and yaw)
- L166 _private member_ `FVector3d RevolutionAxisOrigin;` — This duplicates Settings->AxisOrigin, but kept for cleanliness since we do need RevolutionAxisDirection
- L167 _private prototype_ `void UpdateRevolutionAxis();`
- L169 _private prototype_ `void ResetAxis();`
- L171 _private member_ `FVector3d SplineFitPlaneOrigin;`
- L172 _private member_ `FVector3d SplineFitPlaneNormal;`

#### class `URevolveSplineToolBuilder`  
`class URevolveSplineToolBuilder : public UBaseMeshFromSplinesToolBuilder`  
_L178-190_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBaseMeshFromSplinesToolBuilder`
- L184 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;` — @return new Tool instance initialized with selected spline source(s)
- L186 _public function_ `virtual UE::Geometry::FIndex2i GetSupportedSplineCountRange() const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/SeamSculptTool.h` (Public)


#### class `USeamSculptToolBuilder`  
`class USeamSculptToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L20-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- L25 _public prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L26 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### class `USeamSculptToolProperties`  
`class USeamSculptToolProperties : public UInteractiveToolPropertySet`  
_L34-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L40 _public member_ `bool bShowWireframe = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L44 _public member_ `bool bHitBackFaces = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L54 _public member_ `double PathSimilarityWeight = 200;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = ( ClampMin = 0, UIMax = 1000))` — Setting this above 0 will include a measure of path similarity to seam transfer, so that among similarly short paths, we pick one that lies closer to the edge. Useful in cases where the path is on the wrong diagonal to the triangulation, because it prefers a closely zigzagging path over a wider "up and over" path that has similar length. If set to 0, only path length is used.

#### class `USeamSculptTool`  
`class USeamSculptTool : public UDynamicMeshBrushTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L64-139_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDynamicMeshBrushTool,IInteractiveToolManageGeometrySelectionAPI`
- L68 _public prototype_ `USeamSculptTool();`
- L70 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L72 _public prototype_ `virtual void Setup() override;`
- L73 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L74 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L76 _public function_ `virtual bool HasCancel() const override`
- L77 _public function_ `virtual bool HasAccept() const override`
- L80 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;` — UBaseBrushTool overrides
- L81 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L82 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L83 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L84 _public function_ `virtual bool SupportsBrushAdjustmentInput() override`
- L87 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L94 _protected prototype_ `virtual void ApplyStamp(const FBrushStampData& Stamp);`
- L96 _protected prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L101 _public member_ `TObjectPtr<USeamSculptToolProperties> Settings;` — `UPROPERTY()`
- L106 _protected member_ `TObjectPtr<UPreviewGeometry> PreviewGeom;` — `UPROPERTY()`
- L108 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L109 _protected member_ `FTransform3d MeshTransform;`
- L110 _protected member_ `double NormalOffset = 0;`
- L112 _protected prototype_ `void InitPreviewGeometry();`
- L113 _protected prototype_ `void UpdatePreviewGeometry();`
- L114 _protected member_ `bool bPreviewGeometryNeedsUpdate = false;`
- L116 _protected member_ `FVector3d CurrentSnapPositionLocal = FVector3d::Zero();`
- L117 _protected member_ `int32 CurrentSnapVertex = -1;`
- L119 _protected member_ `FVector3d DrawPathStartPositionLocal = FVector3d::Zero();`
- L120 _protected member_ `int32 DrawPathStartVertex = -1;`
- L122 _protected member_ `TArray<int32> CurDrawPath;`
- L123 _protected prototype_ `void UpdateCurrentDrawPath();`
- L126 _protected prototype_ `void CreateSeamAlongPath();`
- L133 _protected member_ `EActiveCaptureState CaptureState = EActiveCaptureState::NoState;`
- L135 _protected member_ `UWorld* TargetWorld;`
- L138 _private member_ `double MeshMaxDim = 0;`

#### enum `USeamSculptTool::EActiveCaptureState`  
`enum class EActiveCaptureState`  
_L128-132_
- L130 _public enumerator_ `NoState`
- L131 _public enumerator_ `DrawNewPath`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L14 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/SelfUnionMeshesTool.h` (Public)


#### class `USelfUnionMeshesToolProperties`  
`class USelfUnionMeshesToolProperties : public UInteractiveToolPropertySet`  
_L24-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the self-union operation
- L31 _public member_ `bool bTrimFlaps = false;` — `UPROPERTY(EditAnywhere, Category = Merge)` — If true, remove open, visible geometry
- L35 _public member_ `bool bTryFixHoles = false;` — `UPROPERTY(EditAnywhere, Category = Merge, AdvancedDisplay)` — Try to fill holes created by the merge, e.g. due to numerical errors
- L39 _public member_ `bool bTryCollapseEdges = true;` — `UPROPERTY(EditAnywhere, Category = Merge, AdvancedDisplay)` — Try to collapse extra edges created by the merge
- L43 _public member_ `float WindingThreshold = 0.5;` — `UPROPERTY(EditAnywhere, Category = Merge, AdvancedDisplay, meta = (UIMin = "0", UIMax = "1"))` — Threshold to determine whether a triangle in one mesh is inside or outside of the other
- L47 _public member_ `bool bShowNewBoundaryEdges = true;` — `UPROPERTY(EditAnywhere, Category = Display)` — Show boundary edges created by the merge (often due to numerical error)
- L51 _public member_ `bool bOnlyUseFirstMeshMaterials = false;` — `UPROPERTY(EditAnywhere, Category = Materials)` — If true, only the first mesh will keep its materials assignments; all other triangles will be assigned material 0

#### class `USelfUnionMeshesTool`  
`class USelfUnionMeshesTool : public UBaseCreateFromSelectedTool`  
_L60-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedTool`
- desc: Union of meshes, resolving self intersections
- L66 _public function_ `USelfUnionMeshesTool()`
- L70 _protected prototype_ `void TransformChanged(UTransformProxy* Proxy, FTransform Transform) override;`
- L72 _protected prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L74 _protected prototype_ `virtual void ConvertInputsAndSetPreviewMaterials(bool bSetPreviewMesh = true) override;`
- L76 _protected prototype_ `virtual void SetupProperties() override;`
- L77 _protected prototype_ `virtual void SaveProperties() override;`
- L78 _protected prototype_ `virtual void SetPreviewCallbacks() override;`
- L80 _protected prototype_ `virtual FString GetCreatedAssetName() const override;`
- L81 _protected prototype_ `virtual FText GetActionName() const override;`
- L84 _protected prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L88 _protected prototype_ `void UpdateVisualization();`
- L93 _protected member_ `TObjectPtr<USelfUnionMeshesToolProperties> Properties;` — `UPROPERTY()`
- L96 _protected member_ `TObjectPtr<ULineSetComponent> DrawnLineSet;` — `UPROPERTY()`
- L98 _protected member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> CombinedSourceMeshes;`
- L101 _protected member_ `TArray<int> CreatedBoundaryEdges;` — for visualization of any errors in the currently-previewed merge operation
- L103 _protected member_ `FVector3d CombinedCenter;`

#### class `USelfUnionMeshesToolBuilder`  
`class USelfUnionMeshesToolBuilder : public UBaseCreateFromSelectedToolBuilder`  
_L108-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedToolBuilder`
- L113 _public function_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L17 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);` — predeclarations

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/Spline/BaseMeshFromSplinesTool.h` (Public)


#### class `UBaseMeshFromSplinesTool`  
`class UBaseMeshFromSplinesTool : public UInteractiveTool, public IInteractiveToolEditorGizmoAPI, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L36-159_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolEditorGizmoAPI,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Tool to create a mesh from a set of selected Spline Components
- L43 _public function_ `virtual bool GetAllowStandardEditorGizmos() override` — IInteractiveToolEditorGizmoAPI -- allow editor gizmo so users can live-edit the splines
- L49 _public prototype_ `virtual void Setup() override;` — InteractiveTool API
- L50 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L51 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L52 _public function_ `virtual bool HasCancel() const override`
- L53 _public function_ `virtual bool HasAccept() const override`
- L54 _public prototype_ `virtual bool CanAccept() const override;`
- L56 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L58 _public function_ `virtual void SetSplineActors(TArray<TWeakObjectPtr<AActor>> InSplineActors)`
- L63 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L64 _public prototype_ `virtual UWorld* GetTargetWorld();`
- L67 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator();` — IDynamicMeshOperatorFactory API
- L72 _protected function_ `virtual void OnSplineUpdate()` — Override to respond to spline changes
- L75 _protected prototype_ `virtual void GenerateAsset(const FDynamicMeshOpResult& OpResult);`
- L83 _protected prototype_ `virtual FTransform3d HandleOperatorTransform(const FDynamicMeshOpResult& OpResult);` — Called by GenerateAsset to set the desired asset transform and if needed transform the result to the corresponding local space @return The transform to use for the generated asset
- L85 _protected function_ `virtual FString GeneratedAssetBaseName() const` — Override with an appropriate prefix for generated meshes
- L90 _protected function_ `virtual FText TransactionName() const` — Override with an appropriate tool transaction name
- L100 _protected function_ `template<typename Func> void EnumerateSplines(Func SplineComponentFunc) const`
- L119 _protected function_ `inline int32 NumSplines() const`
- L129 _protected prototype_ `USplineComponent* GetFirstSpline() const;`
- L130 _protected prototype_ `USplineComponent* GetLastSpline() const;`
- L135 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties = nullptr;` — `UPROPERTY()`
- L138 _protected member_ `TObjectPtr<UNewMeshMaterialProperties> MaterialProperties = nullptr;` — `UPROPERTY()`
- L141 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview;` — `UPROPERTY()`
- L144 _protected member_ `TWeakObjectPtr<UWorld> TargetWorld = nullptr;` — `UPROPERTY()`
- L148 _protected member_ `TArray<TWeakObjectPtr<AActor>> ActorsWithSplines;` — `UPROPERTY()` — Note: We track actors instead of the USplineComponents here because the USplineComponents objects are often deleted / swapped for identical but new objects
- L151 _protected prototype_ `void PollSplineUpdates();` — Helper to track the splines we are triangulating, so we can re-triangulate when they are moved or changed
- L153 _protected member_ `TArray<uint32> LastSplineVersions;` — Track the spline 'Version' integer, which is incremented when splines are changed
- L155 _protected member_ `TArray<FTransform> LastSplineTransforms;` — Track the spline component's transform (to world space)
- L158 _protected member_ `bool bLostInputSpline = false;` — If failed to reacquire once, used to avoid trying to reaquire again.

#### class `UBaseMeshFromSplinesToolBuilder`  
`class UBaseMeshFromSplinesToolBuilder : public UInteractiveToolBuilder`  
_L167-183_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UInteractiveToolBuilder`
- desc: Base Tool Builder for tools that operate on a selection of Spline Components
- L173 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — @return true if spline component sources can be found in the active selection
- L176 _public prototype_ `virtual void InitializeNewTool(UBaseMeshFromSplinesTool* Tool, const FToolBuilderState& SceneState) const;` — Called by BuildTool to configure the Tool with the input spline source(s) based on the SceneState
- L179 _public function_ `virtual UE::Geometry::FIndex2i GetSupportedSplineCountRange() const` — @return the min and max (inclusive) number of splines allowed in the selection for the tool to be built. A value of -1 can be used to indicate there is no maximum.

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L112 _function_ `` (scope `UBaseMeshFromSplinesTool::EnumerateSplines`)
- L123 _function_ `` (scope `UBaseMeshFromSplinesTool::NumSplines`)

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/SplitMeshesTool.h` (Public)


#### class `USplitMeshesToolBuilder`  
`class USplitMeshesToolBuilder : public UMultiTargetWithSelectionToolBuilder`  
_L17-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiTargetWithSelectionToolBuilder`
- L21 _public prototype_ `virtual UMultiTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L23 _public function_ `virtual bool RequiresInputSelection() const override`
- L26 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `ESplitMeshesMethod`  
`enum class ESplitMeshesMethod : uint8`  
_L31-41_
- reflection: `UENUM()`
- desc: Methods for splitting meshes
- L34 _public enumerator_ `ByMeshTopology` — Split meshes based on the triangle-connected regions of the mesh
- L36 _public enumerator_ `ByVertexOverlap` — Split meshes based on triangle-connected regions, and consider vertices to be connected if they are within a tolerance distance
- L38 _public enumerator_ `ByMaterialID` — Split meshes based on material ID
- L40 _public enumerator_ `ByPolyGroup` — Split meshes based on PolyGroup ID

#### class `USplitMeshesToolProperties`  
`class USplitMeshesToolProperties : public UInteractiveToolPropertySet`  
_L44-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L51 _public member_ `ESplitMeshesMethod SplitMethod = ESplitMeshesMethod::ByMeshTopology;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "!bIsInSelectionMode", EditConditionHides, HideEditConditionToggle))` — Method to use to split the input(s) into output meshes
- L55 _public member_ `double ConnectVerticesThreshold = 0.01;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (ClampMin = .0001, UIMax = 1.0, EditCondition = "!bIsInSelectionMode && SplitMethod == ESplitMeshesMethod::ByVertexOverlap", EditConditionHides, HideEditConditionToggle))` — Vertices as close as this distance will be treated as overlapping, and kept in the same output mesh
- L59 _public member_ `bool bTransferMaterials = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to transfer materials to the output meshes
- L63 _public member_ `bool bShowPreview = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to color mesh faces based on how they will be split into output meshes
- L66 _public member_ `bool bIsInSelectionMode = false;` — `UPROPERTY()`

#### class `USplitMeshesTool`  
`class USplitMeshesTool : public UMultiTargetWithSelectionTool`  
_L72-120_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiTargetWithSelectionTool`
- L77 _public prototype_ `virtual void Setup() override;`
- L78 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L80 _public function_ `virtual bool HasCancel() const override`
- L81 _public function_ `virtual bool HasAccept() const override`
- L82 _public prototype_ `virtual bool CanAccept() const override;`
- L85 _public member_ `TObjectPtr<USplitMeshesToolProperties> BasicProperties;` — `UPROPERTY()`
- L88 _public member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()`
- L96 _protected member_ `TArray<FSourceMeshInfo> SourceMeshes;`
- L106 _protected member_ `TArray<FComponentsInfo> SplitMeshes;`
- L108 _protected member_ `int32 NoSplitCount = 0;`
- L110 _protected prototype_ `void UpdateSplitMeshes();`
- L115 _private member_ `TArray<TObjectPtr<UPreviewGeometry>> PerTargetPreviews;` — `UPROPERTY()` — Preview how the meshes are to be split
- L117 _private member_ `TObjectPtr<UMaterialInterface> PreviewMaterial = nullptr;` — `UPROPERTY()`
- L119 _private prototype_ `void UpdatePreviewVisibility(bool bShowPreview);`

#### struct `USplitMeshesTool::FSourceMeshInfo`  
`struct FSourceMeshInfo`  
_L91-95_
- L93 _public member_ `UE::Geometry::FDynamicMesh3 Mesh;`
- L94 _public member_ `TArray<UMaterialInterface*> Materials;`

#### struct `USplitMeshesTool::FComponentsInfo`  
`struct FComponentsInfo`  
_L99-105_
- L101 _public member_ `bool bNoComponents;`
- L102 _public member_ `TArray<UE::Geometry::FDynamicMesh3> Meshes;`
- L103 _public member_ `TArray<TArray<UMaterialInterface*>> Materials;`
- L104 _public member_ `TArray<FVector3d> Origins;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/TransferMeshTool.h` (Public)


#### class `UTransferMeshToolBuilder`  
`class UTransferMeshToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L18-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L22 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L23 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L26 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UTransferMeshToolProperties`  
`class UTransferMeshToolProperties : public UInteractiveToolPropertySet`  
_L34-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the Transfer operation
- L39 _public member_ `bool bTransferMaterials = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L42 _public member_ `bool bTransferCollision = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L46 _public member_ `FString SourceLOD;` — `UPROPERTY(EditAnywhere, Category = SourceMesh, meta = (DisplayName = "Source LOD", TransientToolProperty, NoResetToDefault, GetOptions = GetSourceLODNamesFunc, HideEditConditionToggle, EditCondition="bIsStaticMeshSource", EditConditionHides))` — Specify which LOD from the Source (First) mesh to copy from
- L50 _public member_ `FString TargetLOD;` — `UPROPERTY(EditAnywhere, Category = TargetMesh, meta = (DisplayName = "Target LOD", TransientToolProperty, NoResetToDefault, GetOptions = GetTargetLODNamesFunc, HideEditConditionToggle, EditCondition="bIsStaticMeshTarget", EditConditionHides))` — Specify which LOD on the Target (Second) mesh to copy to
- L58 _public member_ `bool bIsStaticMeshSource = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L61 _public function_ `const TArray<FString>& GetSourceLODNamesFunc() const` — `UFUNCTION()`
- L64 _public member_ `TArray<FString> SourceLODNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L66 _public member_ `TArray<EMeshLODIdentifier> SourceLODEnums;`
- L70 _public function_ `const TArray<FString>& GetTargetLODNamesFunc() const` — `UFUNCTION()`
- L73 _public member_ `TArray<FString> TargetLODNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`
- L75 _public member_ `TArray<EMeshLODIdentifier> TargetLODEnums;`
- L78 _public member_ `bool bIsStaticMeshTarget = false;` — `UPROPERTY(meta = (TransientToolProperty))`

#### class `UTransferMeshTool`  
`class UTransferMeshTool : public UMultiSelectionMeshEditingTool,`  
_L84-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolExclusiveToolAPI`
- L91 _public prototype_ `virtual void Setup() override;`
- L92 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L94 _public function_ `virtual bool HasCancel() const override`
- L95 _public function_ `virtual bool HasAccept() const override`
- L96 _public prototype_ `virtual bool CanAccept() const override;`
- L99 _public member_ `TObjectPtr<UTransferMeshToolProperties> BasicProperties;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/TransformMeshesTool.h` (Public)


#### class `UTransformMeshesToolBuilder`  
`class UTransformMeshesToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L26-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L31 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L34 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `ETransformMeshesTransformMode`  
`enum class ETransformMeshesTransformMode : uint8`  
_L41-53_
- reflection: `UENUM()`
- desc: Mesh Transform modes
- L44 _public enumerator_ `SharedGizmo = 0 UMETA(DisplayName = "Shared Gizmo")` — Single Gizmo for all Objects
- L47 _public enumerator_ `SharedGizmoLocal = 1 UMETA(DisplayName = "Shared Gizmo (Local)")` — Single Gizmo for all Objects, Rotations applied per-Object
- L50 _public enumerator_ `PerObjectGizmo = 2 UMETA(DisplayName = "Multi-Gizmo")` — Separate Gizmo for each Object
- L52 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `ETransformMeshesSnapDragSource`  
`enum class ETransformMeshesSnapDragSource : uint8`  
_L59-70_
- reflection: `UENUM()`
- desc: Snap-Drag Source Point
- L62 _public enumerator_ `ClickPoint = 0 UMETA(DisplayName = "Click Point")` — Snap-Drag moves the Clicked Point to the Target Location
- L65 _public enumerator_ `Pivot = 1 UMETA(DisplayName = "Pivot")` — Snap-Drag moves the Gizmo/Pivot to the Target Location
- L68 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `ETransformMeshesSnapDragRotationMode`  
`enum class ETransformMeshesSnapDragRotationMode : uint8`  
_L76-88_
- reflection: `UENUM()`
- desc: Snap-Drag Rotation Mode
- L79 _public enumerator_ `Ignore = 0 UMETA(DisplayName = "Ignore")` — Snap-Drag only translates, ignoring Normals
- L82 _public enumerator_ `Align = 1 UMETA(DisplayName = "Align")` — Snap-Drag aligns the Source and Target Normals to point in the same direction
- L85 _public enumerator_ `AlignFlipped = 2 UMETA(DisplayName = "Align Flipped")` — Snap-Drag aligns the Source Normal to the opposite of the Target Normal direction
- L87 _public enumerator_ `LastValue UMETA(Hidden)`

#### class `UTransformMeshesToolProperties`  
`class UTransformMeshesToolProperties : public UInteractiveToolPropertySet`  
_L96-133_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the Transform Meshes operation
- L103 _public member_ `ETransformMeshesTransformMode TransformMode = ETransformMeshesTransformMode::SharedGizmo;` — `UPROPERTY(EditAnywhere, Category = Options)` — Transformation Mode controls the overall behavior of the Gizmos in the Tool
- L107 _public member_ `bool bApplyToInstances = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (HideEditConditionToggle, EditCondition = "bHaveInstances"))` — When true, transformations are applied to the Instances of any Instanced Components (eg InstancedStaticMeshComponent) instead of to the Components
- L112 _public member_ `bool bSetPivotMode = false;` — `UPROPERTY(EditAnywhere, Category = Pivot, meta = (TransientToolProperty, EditCondition = "TransformMode != ETransformMeshesTransformMode::PerObjectGizmo"))` — When true, the Gizmo can be moved independently without affecting objects. This allows the Gizmo to be repositioned before transforming.
- L117 _public member_ `bool bEnableSnapDragging = false;` — `UPROPERTY(EditAnywhere, Category = SnapDragging, meta = (TransientToolProperty, DisplayName = "Enable"))` — When Snap-Dragging is enabled, you can Click-drag starting on the target objects to reposition them relative to the rest of the scene
- L121 _public member_ `ETransformMeshesSnapDragSource SnapDragSource = ETransformMeshesSnapDragSource::ClickPoint;` — `UPROPERTY(EditAnywhere, Category = SnapDragging, meta = (EditCondition = "bEnableSnapDragging == true"))` — Which point on the object being Snap-Dragged to use as the "Source" point
- L125 _public member_ `ETransformMeshesSnapDragRotationMode RotationMode = ETransformMeshesSnapDragRotationMode::AlignFlipped;` — `UPROPERTY(EditAnywhere, Category = SnapDragging, meta = (EditCondition = "bEnableSnapDragging == true"))` — How the object being Snap-Dragged should be rotated relative to the Source point location and Hit Surface normal
- L132 _public member_ `bool bHaveInstances = false;` — `UPROPERTY(meta = (TransientToolProperty))` — internal, used to control visibility of Instance settings

#### struct `FTransformMeshesTarget`  
`struct FTransformMeshesTarget`  
_L137-146_
- reflection: `USTRUCT()`
- L142 _public member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L145 _public member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`

#### class `UTransformMeshesTool`  
`class UTransformMeshesTool : public UMultiSelectionMeshEditingTool, public IClickDragBehaviorTarget, public IInteractiveToolManageGeometrySelectionAPI`  
_L153-212_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IClickDragBehaviorTarget,IInteractiveToolManageGeometrySelectionAPI`
- L158 _public prototype_ `UTransformMeshesTool();`
- L160 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L162 _public prototype_ `virtual void Setup() override;`
- L163 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L165 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L167 _public function_ `virtual bool HasCancel() const override`
- L168 _public function_ `virtual bool HasAccept() const override`
- L169 _public function_ `virtual bool CanAccept() const override`
- L173 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — ICLickDragBehaviorTarget interface
- L174 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L175 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L176 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L177 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L180 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L187 _protected member_ `TObjectPtr<UTransformMeshesToolProperties> TransformProps;` — `UPROPERTY()`
- L191 _protected member_ `TArray<FTransformMeshesTarget> ActiveGizmos;` — `UPROPERTY()`
- L194 _protected member_ `TObjectPtr<UDragAlignmentMechanic> DragAlignmentMechanic = nullptr;` — `UPROPERTY()`
- L196 _protected member_ `ETransformMeshesTransformMode CurTransformMode;`
- L197 _protected prototype_ `void UpdateTransformMode(ETransformMeshesTransformMode NewMode);`
- L198 _protected prototype_ `void UpdateSetPivotModes(bool bEnableSetPivot);`
- L200 _protected prototype_ `void SetActiveGizmos_Single(bool bLocalRotations);`
- L201 _protected prototype_ `void SetActiveGizmos_PerObject();`
- L202 _protected prototype_ `void ResetActiveGizmos();`
- L205 _protected member_ `UE::Geometry::FFrame3d StartDragFrameWorld;`
- L206 _protected member_ `FTransform StartDragTransform;`
- L207 _protected member_ `int ActiveSnapDragIndex = -1;`
- L209 _protected member_ `bool bCurrentlyDragging = false;` — Can't just use ActiveSnapDragIndex to replace this bool, because the former gets set while checking for capture
- L211 _protected prototype_ `void OnParametersUpdated();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/TriangulateSplinesTool.h` (Public)


#### class `UTriangulateSplinesToolProperties`  
`class UTriangulateSplinesToolProperties : public UInteractiveToolPropertySet`  
_L22-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Parameters for controlling the spline triangulation
- L29 _public member_ `double ErrorTolerance = 1.0;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (ClampMin = 0.001))` — How far to allow the triangulation boundary can deviate from the spline curve before we add more vertices
- L33 _public member_ `EFlattenCurveMethod FlattenMethod = EFlattenCurveMethod::DoNotFlatten;` — `UPROPERTY(EditAnywhere, Category = Spline)` — Whether and how to flatten the curves. If curves are flattened, they can also be offset and combined
- L37 _public member_ `ECombineCurvesMethod CombineMethod = ECombineCurvesMethod::LeaveSeparate;` — `UPROPERTY(EditAnywhere, Category = Spline, meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten", EditConditionHides))` — Whether or how to combine the curves
- L41 _public member_ `double Thickness = 0.0;` — `UPROPERTY(EditAnywhere, Category = Mesh, meta = (ClampMin = 0.0))` — If > 0, Extrude the triangulation by this amount
- L45 _public member_ `bool bFlipResult = false;` — `UPROPERTY(EditAnywhere, Category = Mesh)` — Whether to flip the facing direction of the generated mesh
- L49 _public member_ `EOffsetOpenCurvesMethod OpenCurves = EOffsetOpenCurvesMethod::TreatAsClosed;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten", EditConditionHides))` — How to handle open curves: Either offset them, or treat them as closed curves
- L53 _public member_ `double CurveOffset = 0.0;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten", EditConditionHides))` — How much offset to apply to curves
- L57 _public member_ `EOffsetClosedCurvesMethod OffsetClosedCurves = EOffsetClosedCurvesMethod::OffsetOuterSide;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten && CurveOffset != 0", EditConditionHides))` — Whether and how to apply offset to closed curves
- L61 _public member_ `EOpenCurveEndShapes EndShapes = EOpenCurveEndShapes::Square;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten && OpenCurves != EOffsetOpenCurvesMethod::TreatAsClosed && CurveOffset != 0", EditConditionHides))` — The shape of the ends of offset curves
- L65 _public member_ `EOffsetJoinMethod JoinMethod = EOffsetJoinMethod::Square;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten && CurveOffset != 0", EditConditionHides))` — The shape of joins between segments of an offset curve
- L69 _public member_ `double MiterLimit = 1.0;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (ClampMin = 0.0, EditCondition = "FlattenMethod != EFlattenCurveMethod::DoNotFlatten && CurveOffset != 0 && JoinMethod == EOffsetJoinMethod::Miter", EditConditionHides))` — How far a miter join can extend before it is replaced by a square join

#### class `UTriangulateSplinesTool`  
`class UTriangulateSplinesTool : public UBaseMeshFromSplinesTool`  
_L77-109_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseMeshFromSplinesTool`
- desc: Tool to create a mesh by triangulating the shapes outlined or traced by a set of selected Spline Components, with optional offset and extrusion
- L83 _public prototype_ `virtual void Setup() override;`
- L84 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L87 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L89 _public prototype_ `virtual FString GeneratedAssetBaseName() const override;`
- L90 _public prototype_ `virtual FText TransactionName() const override;`
- L93 _protected prototype_ `virtual void OnSplineUpdate() override;`
- L98 _private member_ `TObjectPtr<UTriangulateSplinesToolProperties> TriangulateProperties;` — `UPROPERTY()`
- L107 _private member_ `TArray<FPathCache> SplinesCache;`

#### struct `UTriangulateSplinesTool::FPathCache`  
`struct FPathCache`  
_L101-106_
- desc: Sampled splines, computed in OnSplineUpdate
- L103 _public member_ `TArray<FVector3d> Vertices;`
- L104 _public member_ `bool bClosed;`
- L105 _public member_ `FTransform ComponentTransform;`

#### class `UTriangulateSplinesToolBuilder`  
`class UTriangulateSplinesToolBuilder : public UBaseMeshFromSplinesToolBuilder`  
_L113-120_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBaseMeshFromSplinesToolBuilder`
- L119 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;` — @return new Tool instance initialized with selected spline source(s)

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/UVTransferTool.h` (Public)


#### class `UUVTransferToolBuilder`  
`class UUVTransferToolBuilder : public UMultiTargetWithSelectionToolBuilder`  
_L27-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiTargetWithSelectionToolBuilder`
- L32 _public prototype_ `virtual UMultiTargetWithSelectionTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L33 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L34 _public function_ `virtual bool RequiresInputSelection() const override`
- L37 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UUVTransferToolProperties`  
`class UUVTransferToolProperties : public UInteractiveToolPropertySet`  
_L41-119_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L50 _public member_ `bool bReverseDirection = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — If false, the first selected mesh's UV's are applied to the second selected mesh. If true, the reverse direction is used.
- L56 _public member_ `bool bTransferSeamsOnly = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — If true, we only transfer the seams without trying to transfer actual UV element values.
- L62 _public member_ `bool bClearExistingSeams = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — If true, clears existing seams on the destination mesh before carrying over new ones.
- L72 _public member_ `double PathSimilarityWeight = 200;` — `UPROPERTY(EditAnywhere, Category = Options, meta = ( ClampMin = 0, UIMax = 1000))` — Setting this above 0 will include a measure of path similarity to seam transfer, so that among similarly short paths, we pick one that lies closer to the edge. Useful in cases where the path is on the wrong diagonal to the triangulation, because it prefers a closely zigzagging path over a wider "up and over" path that has similar length. If set to 0, only path length is used.
- L75 _public member_ `bool bShowWireframes = false;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L78 _public member_ `bool bShowSeams = true;` — `UPROPERTY(EditAnywhere, Category = Visualization)`
- L85 _public member_ `double VertexSearchDistance = 0.0001;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = ( ClampMin = 0.0001, ClampMax = 10000, UIMax = 1.0))` — How far to look for a corresponding vertex on the destination. The destination is expected to be a simplified version of source using existing vertices, so this should not need to be set high.
- L90 _private member_ `FString SourceUVChannel;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DisplayName = "Source UV Channel", GetOptions = GetSourceUVChannelNames, NoResetToDefault))`
- L97 _private member_ `bool bSameDestinationChannel = true;` — `UPROPERTY(EditAnywhere, Category = "Options")` — When true, the source channel is the same index in the source and destination, and options are limited to channels that exist on both meshes.
- L103 _private member_ `FString DestUVChannel;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (DisplayName = "Destination UV Channel", GetOptions = GetDestUVChannelNames, NoResetToDefault, EditCondition = "!bSameDestinationChannel", EditConditionHides))` — UV Channel to use as destination, if Same Destination Channel is false.
- L106 _private function_ `const TArray<FString>& GetSourceUVChannelNames() const` — `UFUNCTION()`
- L109 _private function_ `const TArray<FString>& GetDestUVChannelNames() const` — `UFUNCTION()`
- L111 _private prototype_ `void ReinitializeChannelOptions(int32 NumSourceChannels, int32 NumDestChannels);`
- L112 _private prototype_ `int32 GetSourceUVChannel();`
- L113 _private prototype_ `int32 GetDestUVChannel();`
- L115 _private member_ `TArray<FString> SourceUVChannels;`
- L116 _private member_ `TArray<FString> DestUVChannels;`

#### class `UUVTransferTool`  
`class UUVTransferTool : public UMultiTargetWithSelectionTool , public UE::Geometry::IDynamicMeshOperatorFactory , public IInteractiveToolManageGeometrySelectionAPI`  
_L128-187_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiTargetWithSelectionTool,UE::Geometry::IDynamicMeshOperatorFactory,IInteractiveToolManageGeometrySelectionAPI`
- desc: Tool that transfers UV data from a lower res mesh to a higher one. The lower resolution mesh is typically obtained by simplifying the destination mesh with a "use existing vertices" setting so that an easy correspondence between mesh vertices can be found.
- L137 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;` — UMultiSelectionMeshEditingTool
- L140 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L141 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L142 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L143 _public function_ `virtual bool HasCancel() const override`
- L144 _public function_ `virtual bool HasAccept() const override`
- L145 _public prototype_ `virtual bool CanAccept() const override;`
- L146 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L149 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory
- L152 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L160 _private member_ `TObjectPtr<UUVTransferToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L163 _private member_ `TObjectPtr<UExistingMeshMaterialProperties> DestinationMaterialSettings = nullptr;` — `UPROPERTY()`
- L166 _private member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> DestinationPreview = nullptr;` — `UPROPERTY()`
- L169 _private member_ `TObjectPtr<UPreviewMesh> SourcePreview = nullptr;` — `UPROPERTY()`
- L172 _private member_ `TObjectPtr<UMeshElementsVisualizer> SourceSeamVisualizer = nullptr;` — `UPROPERTY()`
- L175 _private member_ `TObjectPtr<UMeshElementsVisualizer> DestinationSeamVisualizer = nullptr;` — `UPROPERTY()`
- L178 _private member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> Meshes[2];` — Normally, Mesh1 corresponds to source and Mesh2 is destination, but this is reversed if bReverseDirection is true.
- L179 _private member_ `TOptional<TSet<int32>> SelectionTidSets[2];`
- L181 _private prototype_ `void ReinitializePreviews();`
- L182 _private prototype_ `void UpdateVisualizations();`
- L183 _private prototype_ `void ReinitializeUVChannelOptions();`
- L185 _private prototype_ `void InvalidatePreview();`
- L186 _private prototype_ `void GenerateAsset(const FDynamicMeshOpResult& Result);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
- L23 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/VolumeToMeshTool.h` (Public)


#### class `UVolumeToMeshToolBuilder`  
`class UVolumeToMeshToolBuilder : public UInteractiveToolBuilder`  
_L20-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L24 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L25 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UVolumeToMeshToolProperties`  
`class UVolumeToMeshToolProperties : public UInteractiveToolPropertySet`  
_L34-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L41 _public member_ `bool bWeldEdges = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Weld coincident vertices and edges together in the resulting mesh to form a closed mesh surface.
- L45 _public member_ `bool bAutoRepair = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "bWeldEdges"))` — If WeldEdges is enabled, attempt to fill any small holes or cracks in the resulting mesh to form a closed surface.
- L49 _public member_ `bool bOptimizeMesh = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "bWeldEdges"))` — If WeldEdges is enabled, and after mesh generation is complete, flip edges in planar regions to improve triangle quality.
- L53 _public member_ `bool bShowWireframe = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Show the wireframe of the resulting converted mesh geometry.

#### class `UVolumeToMeshTool`  
`class UVolumeToMeshTool : public UInteractiveTool`  
_L62-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool`
- L67 _public prototype_ `UVolumeToMeshTool();`
- L69 _public function_ `virtual void SetWorld(UWorld* World)`
- L70 _public prototype_ `virtual void SetSelection(AVolume* Volume);`
- L72 _public prototype_ `virtual void Setup() override;`
- L73 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L75 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L76 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L78 _public function_ `virtual bool HasCancel() const override`
- L79 _public function_ `virtual bool HasAccept() const override`
- L80 _public prototype_ `virtual bool CanAccept() const override;`
- L85 _protected member_ `TObjectPtr<UVolumeToMeshToolProperties> Settings;` — `UPROPERTY()`
- L88 _protected member_ `TObjectPtr<UCreateMeshObjectTypeProperties> OutputTypeProperties;` — `UPROPERTY()`
- L91 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L94 _protected member_ `TSoftObjectPtr<AVolume> TargetVolume;` — `UPROPERTY()`
- L97 _protected member_ `TObjectPtr<ULineSetComponent> VolumeEdgesSet;` — `UPROPERTY()`
- L100 _protected member_ `UWorld* TargetWorld = nullptr;`
- L102 _protected member_ `UE::Geometry::FDynamicMesh3 CurrentMesh;`
- L104 _protected prototype_ `void RecalculateMesh();`
- L106 _protected prototype_ `void UpdateLineSet();`
- L108 _protected member_ `bool bResultValid = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/VoxelBlendMeshesTool.h` (Public)


#### enum `EVoxelBlendOperation`  
`enum class EVoxelBlendOperation : uint8`  
_L16-23_
- reflection: `UENUM()`
- desc: CSG-style blend operations
- L19 _public enumerator_ `Union = 0` — Smoothed union of all shapes
- L22 _public enumerator_ `Subtract = 1` — Smoothed subtraction of all shapes from the first selected shape

#### class `UVoxelBlendMeshesToolProperties`  
`class UVoxelBlendMeshesToolProperties : public UInteractiveToolPropertySet`  
_L30-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties of the blend operation
- L37 _public member_ `double BlendPower = 2;` — `UPROPERTY(EditAnywhere, Category = Blend, meta = (UIMin = "1", UIMax = "4", ClampMin = "1", ClampMax = "10"))` — Blend power controls the shape of the blend between shapes
- L41 _public member_ `double BlendFalloff = 10;` — `UPROPERTY(EditAnywhere, Category = Blend, meta = (UIMin = ".1", UIMax = "100", ClampMin = ".001", ClampMax = "1000"))` — Blend falloff controls the size of the blend region
- L45 _public member_ `EVoxelBlendOperation Operation = EVoxelBlendOperation::Union;` — `UPROPERTY(EditAnywhere, Category = Blend)` — How to combine the shapes
- L51 _public member_ `bool bVoxWrap = false;` — `UPROPERTY(EditAnywhere, Category = VoxWrapPreprocess)` — Apply a "VoxWrap" operation to input mesh(es) before computing the blend.  Fixes results for inputs with holes and/or self-intersections.
- L55 _public member_ `bool bRemoveInternalsAfterVoxWrap = false;` — `UPROPERTY(EditAnywhere, Category = VoxWrapPreprocess, meta = (EditCondition = "bVoxWrap == true"))` — Remove internal surfaces from the VoxWrap output, before computing the blend.
- L59 _public member_ `double ThickenShells = 0.0;` — `UPROPERTY(EditAnywhere, Category = VoxWrapPreprocess, meta = (EditCondition = "bVoxWrap == true", UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — Thicken open-boundary surfaces (extrude them inwards) before VoxWrapping them. Units are in world space. If 0 then no extrusion is applied.

#### class `UVoxelBlendMeshesTool`  
`class UVoxelBlendMeshesTool : public UBaseVoxelTool`  
_L68-102_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseVoxelTool`
- desc: Tool to smoothly blend meshes together
- L74 _public function_ `UVoxelBlendMeshesTool()`
- L78 _protected prototype_ `virtual void SetupProperties() override;`
- L79 _protected prototype_ `virtual void SaveProperties() override;`
- L81 _protected prototype_ `virtual FString GetCreatedAssetName() const override;`
- L82 _protected prototype_ `virtual FText GetActionName() const override;`
- L84 _protected prototype_ `virtual void ConvertInputsAndSetPreviewMaterials(bool bSetPreviewMesh) override;`
- L89 _protected prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L92 _protected member_ `TObjectPtr<UVoxelBlendMeshesToolProperties> BlendProperties;` — `UPROPERTY()`
- L94 _protected function_ `virtual bool KeepCollisionFrom(int32 TargetIdx) const override`

#### class `UVoxelBlendMeshesToolBuilder`  
`class UVoxelBlendMeshesToolBuilder : public UBaseCreateFromSelectedToolBuilder`  
_L106-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedToolBuilder`
- L111 _public function_ `virtual int32 MinComponentsSupported() const override`
- L113 _public function_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/VoxelMorphologyMeshesTool.h` (Public)


#### class `UVoxelMorphologyMeshesToolProperties`  
`class UVoxelMorphologyMeshesToolProperties : public UInteractiveToolPropertySet`  
_L20-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties of the morphology tool
- L28 _public member_ `EMorphologyOperation Operation = EMorphologyOperation::Dilate;` — `UPROPERTY(EditAnywhere, Category = Offset)` — Which offset (or morphology) operation to apply
- L32 _public member_ `double Distance = 5;` — `UPROPERTY(EditAnywhere, Category = Offset, meta = (UIMin = ".1", UIMax = "100", ClampMin = ".001", ClampMax = "1000"))` — Distance to offset the mesh
- L36 _public member_ `bool bVoxWrap = false;` — `UPROPERTY(EditAnywhere, Category = VoxWrapPreprocess)` — Apply a "VoxWrap" operation to input mesh(es) before computing the morphology.  Fixes results for inputs with holes and/or self-intersections.
- L40 _public member_ `bool bRemoveInternalsAfterVoxWrap = false;` — `UPROPERTY(EditAnywhere, Category = VoxWrapPreprocess, meta = (EditCondition = "bVoxWrap == true"))` — Remove internal surfaces from the VoxWrap output, before computing the morphology.
- L44 _public member_ `double ThickenShells = 0.0;` — `UPROPERTY(EditAnywhere, Category = VoxWrapPreprocess, meta = (EditCondition = "bVoxWrap == true", UIMin = "0", UIMax = "100", ClampMin = "0", ClampMax = "1000"))` — Thicken open-boundary surfaces (extrude them inwards) before VoxWrapping them. Units are in world space. If 0, no extrusion is applied.

#### class `UVoxelMorphologyMeshesTool`  
`class UVoxelMorphologyMeshesTool : public UBaseVoxelTool`  
_L53-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseVoxelTool`
- desc: Morphology tool -- dilate, contract, close, open operations on the input shape
- L59 _public function_ `UVoxelMorphologyMeshesTool()`
- L63 _protected prototype_ `virtual void SetupProperties() override;`
- L64 _protected prototype_ `virtual void SaveProperties() override;`
- L66 _protected prototype_ `virtual FString GetCreatedAssetName() const override;`
- L67 _protected prototype_ `virtual FText GetActionName() const override;`
- L69 _protected prototype_ `virtual void ConvertInputsAndSetPreviewMaterials(bool bSetPreviewMesh) override;`
- L72 _protected prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L75 _protected member_ `TObjectPtr<UVoxelMorphologyMeshesToolProperties> MorphologyProperties;` — `UPROPERTY()`

#### class `UVoxelMorphologyMeshesToolBuilder`  
`class UVoxelMorphologyMeshesToolBuilder : public UBaseCreateFromSelectedToolBuilder`  
_L83-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedToolBuilder`
- L88 _public function_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`

### `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsExp/Public/VoxelSolidifyMeshesTool.h` (Public)


#### class `UVoxelSolidifyMeshesToolProperties`  
`class UVoxelSolidifyMeshesToolProperties : public UInteractiveToolPropertySet`  
_L21-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Properties of the solidify operation
- L28 _public member_ `double WindingThreshold = .5;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0.1", UIMax = ".9", ClampMin = "-10", ClampMax = "10"))` — Winding number threshold to determine what is consider inside the mesh
- L32 _public member_ `double ExtendBounds = 1;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "1000"))` — How far we allow bounds of solid surface to go beyond the bounds of the original input surface before clamping / cutting the surface off
- L36 _public member_ `int SurfaceSearchSteps = 4;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "6", ClampMin = "0", ClampMax = "10"))` — How many binary search steps to take when placing vertices on the surface
- L40 _public member_ `bool bSolidAtBoundaries = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — Whether to fill at the border of the bounding box, if the surface extends beyond the voxel boundaries
- L44 _public member_ `bool bApplyThickenShells = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — If true, uses the ThickenShells setting
- L48 _public member_ `double ThickenShells = 5;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = ".1", UIMax = "100", ClampMin = ".001", ClampMax = "1000", EditCondition = "bApplyThickenShells == true"))` — Thicken open-boundary surfaces (extrude them inwards) to ensure they are captured in the VoxWrap output. Units are in world space.

#### class `UVoxelSolidifyMeshesTool`  
`class UVoxelSolidifyMeshesTool : public UBaseVoxelTool`  
_L57-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseVoxelTool`
- desc: Tool to take one or more meshes, possibly intersecting and possibly with holes, and create a single solid mesh with consistent inside/outside
- L63 _public function_ `UVoxelSolidifyMeshesTool()`
- L65 _public prototype_ `virtual void SetupProperties() override;`
- L66 _public prototype_ `virtual void SaveProperties() override;`
- L68 _public prototype_ `virtual FString GetCreatedAssetName() const override;`
- L69 _public prototype_ `virtual FText GetActionName() const override;`
- L72 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L77 _protected member_ `TObjectPtr<UVoxelSolidifyMeshesToolProperties> SolidifyProperties;` — `UPROPERTY()`

#### class `UVoxelSolidifyMeshesToolBuilder`  
`class UVoxelSolidifyMeshesToolBuilder : public UBaseCreateFromSelectedToolBuilder`  
_L83-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCreateFromSelectedToolBuilder`
- L88 _public function_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLSEXP_API`
