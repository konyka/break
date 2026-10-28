# Plugins / ChaosClothAssetTools

- module root: `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools`
- headers: 13; symbols: 116
- symbol kinds: class=13, enum=1, enumerator=3, function=18, macro=3, member=11, namespace=32, prototype=34, struct=1
- PrivateDependencyModuleNames: Chaos, ChaosCloth, ChaosClothAsset, ChaosClothAssetEngine, ChaosClothEditor, ClothPainter, ClothingSystemEditorInterface, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, Core, CoreUObject, DataflowEditor, DataflowEngine, Engine, GeometryCore, MeshConversion, MeshDescription, Projects, RHI, RenderCore, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: MeshConversion

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Internal/ChaosClothAsset/ClothAssetThumbnailRenderer.h` (Internal)


#### class `AChaosClothPreviewActor_Internal`  
`class AChaosClothPreviewActor_Internal : public AActor`  
_L17-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: Minimal actor with a cloth component used to render cloth assets previews
- L21 _public prototype_ `AChaosClothPreviewActor_Internal();`
- L23 _public function_ `UChaosClothComponent* GetClothComponent() const`
- L30 _protected member_ `TObjectPtr<UChaosClothComponent> ClothComponent;` — `UPROPERTY()`

#### class `UE::Chaos::ClothAsset::FThumbnailScene_Internal`  
`class FThumbnailScene_Internal : public FThumbnailPreviewScene`  
_L38-49_
- inherits: `FThumbnailPreviewScene`
- desc: Preview scene for a Cloth asset thumbnail
- L41 _public prototype_ `FThumbnailScene_Internal();`
- L43 _public prototype_ `void SetClothAsset(UChaosClothAssetBase* InClothAsset);`
- L45 _public prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;`
- L48 _private member_ `AChaosClothPreviewActor_Internal* PreviewActor = nullptr;`

#### class `UChaosClothAssetThumbnailRenderer_Internal`  
`class UChaosClothAssetThumbnailRenderer_Internal : public UDefaultSizedThumbnailRenderer`  
_L57-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- desc: Renders a preview scene to be used as a thumbnail for a supported cloth asset
- L61 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* Viewport, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L62 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L63 _private prototype_ `virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override;`
- L65 _private prototype_ `virtual void BeginDestroy() override;`
- L68 _protected member_ `TObjectInstanceThumbnailScene<UE::Chaos::ClothAsset::FThumbnailScene_Internal, 128> ClothThumbnailSceneCache;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace Chaos` (scope `UE`)
- L33 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Private/ChaosClothAsset/ClothAssetSKMClothingAssetFactory.h` (Private)


#### class `UChaosClothAssetSKMClothingAssetFactory`  
`class UChaosClothAssetSKMClothingAssetFactory : public UClothingAssetFactoryBase`  
_L9-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClothingAssetFactoryBase`
- L13 _public prototype_ `UChaosClothAssetSKMClothingAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L16 _public prototype_ `virtual const UClass* GetSupportedSourceAssetType() const override;`
- L18 _public prototype_ `virtual TArray<UClothingAssetBase*> CreateFromSourceAsset(USkeletalMesh* TargetMesh, const UObject* SourceAsset) const override;`
- L20 _public function_ `virtual UClothingAssetBase* CreateFromSkeletalMesh(USkeletalMesh* TargetMesh, FSkeletalMeshClothBuildParams& Params) override`
- L25 _public function_ `virtual UClothingAssetBase* CreateFromExistingCloth(USkeletalMesh* , USkeletalMesh* , UClothingAssetBase* ) override`
- L30 _public function_ `virtual UClothingAssetBase* ImportLodToClothing(USkeletalMesh* TargetMesh, FSkeletalMeshClothBuildParams& Params) override`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Private/ChaosClothAsset/ClothAssetSKMSimulationEditorExtender.h` (Private)


#### class `UE::Chaos::ClothAsset::FSKMSimulationEditorExtender`  
`class FSKMSimulationEditorExtender final : public ::Chaos::FSimulationEditorExtender`  
_L15-31_
- inherits: `::Chaos::FSimulationEditorExtender`
- desc: Chaos extension to the asset editor.
- L18 _public prototype_ `FSKMSimulationEditorExtender();`
- L23 _private prototype_ `virtual UClass* GetSupportedSimulationFactoryClass() override;`
- L27 _private prototype_ `virtual FName GetSectionName() const override;`
- L28 _private prototype_ `virtual FText GetSectionHeadingText() const override;`
- L29 _private prototype_ `virtual const ::Chaos::FClothVisualizationNoGC* GetClothVisualization(const IClothingSimulationInterface* Simulation) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Chaos`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Chaos` (scope `UE`)
- L12 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Private/ChaosClothAsset/ClothComponentEditorStyle.h` (Private)


#### class `UE::Chaos::ClothAsset::FClothComponentEditorStyle`  
`class FClothComponentEditorStyle final : public FSlateStyleSet`  
_L13-36_
- inherits: `FSlateStyleSet`
- desc: Editor style setting up the cloth asset icons in editor. TODO: Merge all styles to a single singleton.
- L16 _public prototype_ `FClothComponentEditorStyle();`
- L20 _public function_ `static FClothComponentEditorStyle& Get()`
- L29 _public function_ `static void Destroy()`
- L35 _private member_ `static TOptional<FClothComponentEditorStyle> Singleton;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Private/ChaosClothAsset/ClothingAssetToClothAssetExporter.h` (Private)


#### class `UClothingAssetToChaosClothAssetExporter`  
`class UClothingAssetToChaosClothAssetExporter : public UClothingAssetExporter`  
_L13-26_
- reflection: `UCLASS()`
- inherits: `UClothingAssetExporter`
- desc: Implement a clothing asset exporter as a way to migrate clothing assets to the new Chaos Cloth asset format.
- L18 _public prototype_ `virtual UClass* GetExportedType() const override;` — Return the class of the exported asset type.
- L25 _public prototype_ `virtual void Export(const UClothingAssetBase* ClothingAsset, UObject* ExportedAsset) override;` — Export the specified asset. \param ClothingAsset the source clothing asset to be exported. \param ExportedAsset the destination asset object in the exported type provided by the caller, ready to be filled by the Export function.

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Private/ChaosClothAsset/SkeletalMeshConverter.h` (Private)


#### class `UClothAssetEditorSkeletalMeshConverter`  
`class UClothAssetEditorSkeletalMeshConverter : public UClothAssetSkeletalMeshConverter`  
_L9-16_
- reflection: `UCLASS()`
- inherits: `UClothAssetSkeletalMeshConverter`
- L15 _public prototype_ `virtual bool ExportToSkeletalMesh(const class UChaosClothAssetBase& ClothAssetBase, class USkeletalMesh& SkeletalMesh) const override;` — Build a skeletal mesh from the specified Cloth Asset.

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Public/ChaosClothAsset/ClothAssetEditorStyle.h` (Public)


#### class `UE::Chaos::ClothAsset::FClothAssetEditorStyle`  
`class FClothAssetEditorStyle final : public FSlateStyleSet`  
_L14-37_
- inherits: `FSlateStyleSet`
- desc: Editor style setting up the cloth asset icons in editor.
- L17 _public prototype_ `FClothAssetEditorStyle();`
- L21 _public function_ `static FClothAssetEditorStyle& Get()`
- L30 _public function_ `static void Destroy()`
- L36 _private member_ `static TOptional<FClothAssetEditorStyle> Singleton;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSETTOOLS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Public/ChaosClothAsset/ClothAssetFactory.h` (Public)


#### class `UChaosClothAssetFactory`  
`class UChaosClothAssetFactory : public UFactory`  
_L17-44_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UFactory`
- desc: Having a cloth factory allows the cloth asset to be created from the Editor's menus.
- L21 _public prototype_ `UChaosClothAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L24 _public function_ `virtual bool CanCreateNew() const override` — UFactory Interface
- L25 _public function_ `virtual bool FactoryCanImport(const FString& Filename) override`
- L26 _public function_ `virtual bool ShouldShowInNewMenu() const override`
- L27 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L28 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L41 _public prototype_ `static UObject* CreateClothAssetFromTemplate( UClass* Class, UObject* Parent, FName Name, EObjectFlags Flags, const FString* TemplatePath, bool bEmbedDataflow);` — Non-modal helper that creates a new cloth asset from a Dataflow template asset path, bypassing the template-picker dialog. Use from scripted / agent-driven flows. @param Class           Asset class to create (typically UChaosClothAsset::StaticClass()). @param Parent          Outer package for the new asset. @param Name            Asset name. @param Flags           Object flags. @param TemplatePath    Object path of the Dataflow template to clone (may be nullptr for "no Dataflow"). @param bEmbedDataflow  Whether to embed the Dataflow graph in the asset or keep it external.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSCLOTHASSETTOOLS_API`

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Public/ChaosClothAsset/ClothPatternToDynamicMesh.h` (Public)


#### class `UE::Chaos::ClothAsset::FClothPatternToDynamicMesh`  
`class FClothPatternToDynamicMesh`  
_L27-50_
- desc: Convert a single pattern from a ClothAsset to a FDynamicMesh3. When PatternIndex = INDEX_NONE, convert the entire cloth asset to an FDynamicMesh3. When VertexDataType = EClothPatternVertexType::Sim3D, this generates a welded mesh (with native welded indexing) when PatternIndex = INDEX_NONE, and an unwelded (with native 2D unwelded indexing) when PatternIndex is a valid SimPattern Index. Use MaterialOffset to specify an offset into the material group ID, and run a Fix up on any triangles without valid material IDs. When MaterialOffset is INDEX_NONE, no offset is applied and no fix up is run. Use bConvertWeightMaps to turn the cloth collection weight maps into a Dynamic Mesh attribute.
- L31 _public prototype_ `void Convert( const TSharedRef<const FManagedArrayCollection> ClothCollection, int32 PatternIndex, EClothPatternVertexType VertexDataType, UE::Geometry::FDynamicMesh3& MeshOut, bool bDisableAttributes = false, int32 MaterialOffset = INDEX_NONE, bool bFlip2DSimFaces = false, bool bConvertWeightMaps = true);`
- L41 _public prototype_ `void Convert( const UChaosClothAsset* ClothAssetMeshIn, int32 LODIndex, int32 PatternIndex, EClothPatternVertexType VertexDataType, UE::Geometry::FDynamicMesh3& MeshOut, int32 MaterialOffset = INDEX_NONE, bool bFlip2DSimFaces = false, bool bConvertWeightMaps = true);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSCLOTHASSETTOOLS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Chaos` (scope `UE`)
- L15 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Public/ChaosClothAsset/ClothPatternToDynamicMeshMappingSupport.h` (Public)


#### class `UE::Chaos::ClothAsset::FClothPatternToDynamicMeshMappingSupport`  
`class FClothPatternToDynamicMeshMappingSupport : public UE::Geometry::FNonManifoldMappingSupport`  
_L17-140_
- inherits: `UE::Geometry::FNonManifoldMappingSupport`
- desc: This uses the NonManifoldMapping attribute for vertices, and a new attribute for triangles.
- L20 _public prototype_ `FClothPatternToDynamicMeshMappingSupport(const UE::Geometry::FDynamicMesh3& Mesh);`
- L25 _public prototype_ `void Reset(const UE::Geometry::FDynamicMesh3& Mesh);` — Update the support for a new DynamicMesh.
- L30 _public function_ `bool IsMappedVertexInSource() const` — Return true if attribute data indicates that the source data that was converted to this DynamicMesh contained mapped vertices.
- L38 _public prototype_ `bool IsMappedTriangleInSource() const;` — Return true if attribute data indicates that the source data that was converted to this DynamicMesh contained mapped triangles.
- L46 _public function_ `bool IsMappedVertexID(const int32 vid) const` — Return true if the provided DynamicMesh vertex id resulted from a remapped vertex in the source data. @param vid - the id of a vertex in the DynamicMesh. Note: the code assumes but does not check that vid is a valid vertex id
- L57 _public function_ `bool IsMappedTriangleID(const int32 Tid) const` — Return true if the provided DynamicMesh triangle id resulted from a remapped triangle in the source data. @param Tid - the id of a triangle in the DynamicMesh. Note: the code assumes but does not check that Tid is a valid triangle id
- L69 _public function_ `int32 GetOriginalVertexID(const int32 vid) const` — Return the vertex ID in the original cloth data used to generate this DynamicMesh associated with the provided vertex id. In the case that the source data was actually manifold the returned vertex id will be identical to the DynamicMesh vertex id. @param vid - the id of a vertex in the DynamicMesh. Note: the code assumes but does not check that vid is a valid vertex vid.
- L81 _public prototype_ `int32 GetOriginalTriangleID(const int32 Tid) const;` — Return the triangle ID in the original cloth data used to generate this DynamicMesh associated with the provided triangle id. In the case that the source data was actually manifold the returned triangle id will be identical to the DynamicMesh triangle id. @param Tid - the id of a triangle in the DynamicMesh. Note: the code assumes but does not check that Tid is a valid triangle id
- L93 _public function_ `static bool AttachVertexMappingData(const TArray<int32>& VertexToOriginalVertexIDMap, UE::Geometry::FDynamicMesh3& InOutMesh)` — Attaches or replaces vertex mapping data to the provided mesh. @param VertexToOriginalVertexIDMap - an array that maps each DynamicMesh vertex id to the associated original vertex id. @return false on failure (no attribute will be attached to the DynamicMesh in this case) Note: Failure occurs if the DynamicMesh does not have attributes enabled or if the provided array is not long enough to provide a mapping value for each DynamicMesh vertex id.
- L105 _public prototype_ `static bool AttachTriangleMappingData(const TArray<int32>& TriangleToOriginalVertexIDMap, UE::Geometry::FDynamicMesh3& InOutMesh);` — Attaches or replaces  triangle mapping data to the provided mesh. @param TriangleToOriginalVertexIDMap - an array that maps each DynamicMesh triangle id to the associated original triangle id. @return false on failure (no attribute will be attached to the DynamicMesh in this case) Note: Failure occurs if the DynamicMesh does not have attributes enabled or if the provided array is not long enough to provide a mapping value for each DynamicMesh triangle id.
- L113 _public function_ `static void RemoveVertexMappingData(UE::Geometry::FDynamicMesh3& InOutMesh)` — Removes triangle mapping data. Note: this will invalidate any NonManifoldMappingSupport/ClothPatternToDynamicMeshMappingSupport object associated with this DynamicMesh, and subsequent use of such object will produce unexpected results.
- L118 _public prototype_ `static void RemoveTriangleMappingData(UE::Geometry::FDynamicMesh3& InOutMesh);`
- L126 _public function_ `static void RemoveAllMappingData(UE::Geometry::FDynamicMesh3& InOutMesh)` — Removes all mapping data. Note, this will invalidate any  NonManifoldMappingSupport/ClothPatternToDynamicMeshMappingSupport object associated with this DynamicMesh, and subsequent use of such object will produce unexpected results.
- L135 _public member_ `static const FName ClothMeshTIDsAttrName;` — Name used to identify triangle attribute data generated during conversion to a DynamicMesh in the case that the source was non-manifold.
- L139 _protected member_ `const FDynamicMeshSourceTriangleIdAttribute* SrcTIDsAttribute = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Chaos` (scope `UE`)
- L11 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Public/ChaosClothAsset/ClothPatternVertexType.h` (Public)


#### enum `UE::Chaos::ClothAsset::EClothPatternVertexType`  
`enum class EClothPatternVertexType : uint8`  
_L9-14_
- L11 _public enumerator_ `Sim2D = 0`
- L12 _public enumerator_ `Sim3D = 1`
- L13 _public enumerator_ `Render = 2`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Public/ChaosClothAsset/ColorScheme.h` (Public)


#### struct `UE::Chaos::ClothAsset::FColorScheme`  
`struct FColorScheme`  
_L9-14_
- L11 _public member_ `static inline const FLinearColor Asset = FColor(242, 77, 26);` — Orange
- L12 _public member_ `static inline const FLinearColor NodeHeader = FColor(180, 120, 110);`
- L13 _public member_ `static inline const FLinearColor NodeBody = FColor(18, 12, 11, 127);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAsset/Source/ChaosClothAssetTools/Public/ChaosClothAsset/LegacyClothingConverterProvider.h` (Public)


#### class `UE::Chaos::ClothAsset::ILegacyClothingConverterProvider`  
`class ILegacyClothingConverterProvider : public IModularFeature`  
_L25-31_
- inherits: `IModularFeature`
- desc: Modular-feature interface that lets ChaosClothAssetTools delegate legacy UClothingAssetCommon -> UChaosClothAsset conversion to FLegacyClothingConverter::ConvertInto, which lives in the higher-level ChaosClothAssetEditor module. The dependency direction prevents a direct call (ChaosClothAssetEditor -> ChaosClothAssetTools), so the higher module registers an implementation on startup and the lower module looks it up via IModularFeatures when the right-click "Export to Chaos Cloth Asset" exporter runs. Returns true on success (TargetAsset has been populated by the new converter). Returns false when the converter rejected the inputs; with no registered implementation, the caller should fall back to the legacy in-tree exporter logic.
- L28 _public member_ `inline static const FName FeatureName = TEXT("ILe`
- L30 _public prototype_ `virtual bool ConvertInto(const UClothingAssetCommon* Source, UChaosClothAsset* Target) const = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Chaos` (scope `UE`)
- L11 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
