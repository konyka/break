# Plugins / PlanarCut

- module root: `Plugins/Experimental/PlanarCutPlugin/Source/PlanarCut`
- headers: 4; symbols: 228
- symbol kinds: class=1, delegate=1, enum=4, enumerator=20, function=39, macro=1, member=60, namespace=15, prototype=76, struct=11
- PrivateDependencyModuleNames: Eigen, MeshConversion, MeshUtilitiesCommon, StaticMeshDescription
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, DynamicMesh, GeometryAlgorithms, GeometryCore, MeshDescription, Voronoi

### `Plugins/Experimental/PlanarCutPlugin/Source/PlanarCut/Private/GeometryMeshConversion.h` (Private)


#### struct `UE::PlanarCut::FCellMeshes`  
`struct FCellMeshes`  
_L58-148_
- desc: Dynamic mesh representation of cutting cells, to be used to fracture a mesh
- L73 _public member_ `TIndirectArray<FCellInfo> CellMeshes;`
- L74 _public member_ `int32 OutsideCellIndex = -1;`
- L75 _public member_ `int32 NumUVLayers = 1;`
- L78 _public member_ `FNoiseOffsets NoiseOffsets;` — Noise Offsets, to randomize where perlin noise is sampled
- L80 _public function_ `void SetNumCells(int32 NumMeshes)`
- L89 _public function_ `FCellMeshes(int32 NumUVLayers, FRandomStream& RandomStream)`
- L94 _public prototype_ `FCellMeshes(int32 NumUVLayers, FRandomStream& RandomStream, const FPlanarCells& Cells, UE::Geometry::FAxisAlignedBox3d DomainBounds, double Grout, double ExtendDomain, bool bIncludeOutsideCell);`
- L97 _public prototype_ `FCellMeshes(int32 NumUVLayers, const UE::Geometry::FDynamicMesh3& SingleCutter, const FInternalSurfaceMaterials& Materials, TOptional<FTransform> Transform);` — Note: RandomStream not required for this constructor because noise is not supported in this case
- L101 _public prototype_ `void MakeOnlyPlanarGroutCell(const FPlanarCells& Cells, UE::Geometry::FAxisAlignedBox3d DomainBounds, double Grout);` — Special function to just make the "grout" part of the planar mesh cells Used to make the multi-plane cuts with grout easier to implement
- L103 _public prototype_ `void RemeshForNoise(UE::Geometry::FDynamicMesh3& Mesh, UE::Geometry::EEdgeRefineFlags EdgeFlags, double TargetEdgeLen);`
- L105 _public prototype_ `FVector3d NoiseDisplacement(const FVector3d& Pos, const FNoiseSettings& Settings);`
- L107 _public prototype_ `void ApplyNoise(UE::Geometry::FDynamicMesh3& Mesh, FVector3d Normal, const FNoiseSettings& Settings, bool bProjectBoundariesToNormal = false);`
- L113 _public function_ `int PlaneToMaterial(int Plane)` — Convert plane index to material ID @return material ID encoding the source plane into a triangle mesh
- L122 _public function_ `int MaterialToPlane(int MaterialID)` — Convert material ID to plane index @return index of source plane for triangle, or -1 if no such plane
- L127 _public function_ `void InitEmpty(FRandomStream& RandomStream)`
- L133 _public prototype_ `void Init(int32 NumUVLayersIn, FRandomStream& RandomStream, const FPlanarCells& Cells, UE::Geometry::FAxisAlignedBox3d DomainBounds, double Grout, double ExtendDomain, bool bIncludeOutsideCell);`
- L135 _public prototype_ `void ApplyGeneralGrout(double Grout);`
- L137 _public prototype_ `void AppendMesh(UE::Geometry::FDynamicMesh3& Base, UE::Geometry::FDynamicMesh3& ToAppend, bool bFlipped);`
- L141 _private prototype_ `void CreateMeshesForBoundedPlanesWithoutNoise(int NumCells, const FPlanarCells& Cells, const UE::Geometry::FAxisAlignedBox3d& DomainBounds, bool bNoise, double GlobalUVScale);`
- L144 _private prototype_ `double GetSafeNoiseSpacing(float SurfaceArea, float TargetSpacing);` — Approximately calculate a "safe" spacing that would not require the remesher to create more than a million new vertices
- L146 _private prototype_ `void CreateMeshesForBoundedPlanesWithNoise(int NumCells, const FPlanarCells& Cells, const UE::Geometry::FAxisAlignedBox3d& DomainBounds, bool bNoise, double GlobalUVScale);`
- L147 _private prototype_ `void CreateMeshesForSinglePlane(const FPlanarCells& Cells, const UE::Geometry::FAxisAlignedBox3d& DomainBounds, bool bNoise, double GlobalUVScale, double Grout, bool bOnlyGrout);`

#### struct `UE::PlanarCut::FCellMeshes::FCellInfo`  
`struct FCellInfo`  
_L60-71_
- L62 _public member_ `UE::Geometry::FDynamicMesh3 AugMesh;`
- L64 _public function_ `FCellInfo(int32 NumUVLayers = 1)`

#### struct `UE::PlanarCut::FDynamicMeshCollection`  
`struct FDynamicMeshCollection`  
_L153-331_
- desc: Holds Geometry from an FGeometryCollection in an FDynamicMesh3 representation, and convert both directions Also supports cutting geometry with FCellMeshes
- L210 _public member_ `TIndirectArray<FMeshData> Meshes;`
- L211 _public member_ `UE::Geometry::FAxisAlignedBox3d Bounds;`
- L216 _public member_ `bool bSkipInvisible = false;` — If true, triangles where the Visible property is false will not be added to the MeshData
- L218 _public member_ `bool bComponentSpaceTransforms = false;` — If false, Transforms passed to Init are interpreted as relative to the parent bone transform. If true, Transforms are all in the same 'global' / component-relative space
- L219 _public member_ `bool bGenerateMeshToCollectionFaceMapping = false;`
- L221 _public function_ `FDynamicMeshCollection()`
- L223 _public function_ `FDynamicMeshCollection(const FGeometryCollection* Collection, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices = false)`
- L228 _public function_ `FDynamicMeshCollection(const FGeometryCollection* Collection, const TManagedArray<FTransform>& Transforms, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices = false)`
- L233 _public function_ `FDynamicMeshCollection(const FGeometryCollection* Collection, const TManagedArray<FTransform3f>& Transforms, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices = false)`
- L238 _public function_ `void Init(const FGeometryCollection* Collection, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices = false)`
- L243 _public function_ `void Init(const FGeometryCollection* Collection, const TManagedArray<FTransform>& Transforms, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices = false)`
- L247 _public function_ `void Init(const FGeometryCollection* Collection, const TManagedArray<FTransform3f>& Transforms, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices = false)`
- L252 _public prototype_ `void Init(const FGeometryCollection* Collection, TArrayView<const FTransform> Transforms, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices = false);`
- L253 _public prototype_ `void Init(const FGeometryCollection* Collection, TArrayView<const FTransform3f> Transforms, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices = false);`
- L255 _public prototype_ `int32 CutWithMultiplePlanes( const TArrayView<const FPlane>& Planes, double Grout, double CollisionSampleSpacing, const FIslandSplitSettings& IslandSplitSettings, int32 RandomSeed, FGeometryCollection* Collection, FInternalSurfaceMaterials& InternalSurfaceMaterials, bool bSetDefaultInternalMaterialsFromCollection, FProgressCancel* Progress = nullptr );`
- L278 _public prototype_ `int32 CutWithCellMeshes(const FInternalSurfaceMaterials& InternalSurfaceMaterials, const TArray<TPair<int32, int32>>& CellConnectivity, FCellMeshes& CellMeshes, const FIslandSplitSettings& IslandSplitSettings, FGeometryCollection* Collection, bool bSetDefaultInternalMaterialsFromCollection, double CollisionSampleSpacing);` — Cut collection meshes with cell meshes, and append results to a geometry collection @param InternalSurfaceMaterials Internal material info (used for material ID) @param CellConnectivity The connectivity between cells: PlaneTag -> The two cells separated by triangles with this tag @param CellsMeshes Meshed versions of the cells, with noise and material properties baked in @param Collection Results will be stored in this @param bSetDefaultInternalMaterialsFromCollection If true, set internal materials to the most common external material + 1, following a convenient artist convention @param CollisionSampleSpacing If > 0, new geometry will have collision samples added (vertices not on any triangles) to fill any gaps greater than the this size @return Index of the first created geometry
- L288 _public prototype_ `int32 SplitAllIslands(FGeometryCollection* Collection, double CollisionSampleSpacing, const FIslandSplitSettings& IslandSplitSettings = FIslandSplitSettings());` — Split islands for all collection meshes, and append results to a geometry collection @param Collection Results will be stored in this @param CollisionSampleSpacing If > 0, new geometry will have collision samples added (vertices not on any triangles) to fill any gaps greater than the this size @return Index of the first created geometry, or -1 if nothing was split
- L290 _public function_ `static void SetVisibility(FGeometryCollection& Collection, int32 GeometryIdx, bool bVisible)`
- L300 _public prototype_ `bool SplitIslands(UE::Geometry::FDynamicMesh3& Source, TArray<TUniquePtr<UE::Geometry::FDynamicMesh3>>& SeparatedMeshes, const FIslandSplitSettings& IslandSplitSettings = FIslandSplitSettings());` — Split mesh into connected components, including implicit connections by co-located vertices
- L302 _public function_ `FString GetBoneName(FGeometryCollection& Output, int TransformParent, int SubPartIndex)`
- L307 _public prototype_ `void AddCollisionSamples(double CollisionSampleSpacing);`
- L311 _public prototype_ `bool UpdateAllCollections(FGeometryCollection& Collection);` — Update all geometry in a GeometryCollection w/ the meshes in the MeshCollection Resizes the GeometryCollection as needed
- L313 _public prototype_ `static int32 AppendToCollection(const FTransform& FromCollection, UE::Geometry::FDynamicMesh3& Mesh, double CollisionSampleSpacing, int32 TransformParent, FString BoneName, FGeometryCollection& Output, int32 InternalMaterialID);`
- L318 _private prototype_ `template<typename TransformType> void InitTemplate(const FGeometryCollection* Collection, TArrayView<const TransformType> Transforms, const TArrayView<const int32>& TransformIndices, FTransform TransformCollection, bool bSaveIsolatedVertices);`
- L321 _private prototype_ `void SetGeometryVisibility(FGeometryCollection* Collection, const TArray<int32>& GeometryIndices, bool bVisible);`
- L324 _private prototype_ `static bool UpdateCollection(const FTransform& FromCollection, UE::Geometry::FDynamicMesh3& Mesh, int32 GeometryIdx, FGeometryCollection& Output, int32 InternalMaterialID);` — Update an existing geometry in a collection w/ a new mesh (w/ the same number of faces and vertices!)
- L326 _private prototype_ `void FillVertexHash(const UE::Geometry::FDynamicMesh3& Mesh, UE::Geometry::TPointHashGrid3d<int>& VertHash);`
- L328 _private prototype_ `bool IsNeighboring( UE::Geometry::FDynamicMesh3& MeshA, const UE::Geometry::TPointHashGrid3d<int>& VertHashA, const UE::Geometry::FAxisAlignedBox3d& BoundsA, UE::Geometry::FDynamicMesh3& MeshB, const UE::Geometry::TPointHashGrid3d<int>& VertHashB, const UE::Geometry::FAxisAlignedBox3d& BoundsB);`

#### struct `UE::PlanarCut::FDynamicMeshCollection::FMeshData`  
`struct FMeshData`  
_L155-209_
- L157 _public member_ `UE::Geometry::FDynamicMesh3 AugMesh;`
- L161 _public member_ `int32 TransformIndex;` — FDynamicMeshAABBTree3 Spatial; // TODO: maybe refactor mesh booleans to allow version where caller provides spatial data; it's computed every boolean now FTransform3d Transform; // TODO: maybe pretransform the data to a space that is good for cutting; refactor mesh boolean so there is an option to have it not transform input
- L162 _public member_ `FTransform FromCollection;` — transform that was used to go from the geometry collection to the local space used for processing
- L164 _public function_ `FMeshData(int32 NumUVLayers)`
- L169 _public function_ `FMeshData(const UE::Geometry::FDynamicMesh3& Mesh, int32 TransformIndex, FTransform FromCollection) : AugMesh(Mesh), TransformIndex(TransformIndex), FromCollection(FromCollection)`
- L172 _public function_ `void SetMesh(const UE::Geometry::FDynamicMesh3& NewAugMesh)`
- L179 _public function_ `const UE::Geometry::FAxisAlignedBox3d& GetCachedBounds()` — Note this relies on the caller to also call ClearCachedBounds() as needed; it will not automatically invalidate any computed bounds
- L189 _public function_ `void ClearCachedBounds()`
- L194 _public function_ `void AddMeshToCollectionFaceMapping(int32 MeshFaceIndex, int32 CollectionFaceIndex)`
- L199 _public function_ `int32 GetCollectionFaceFromMeshFace(int32 MeshFaceIndex) const`
- L205 _private member_ `bool bHasBounds = false;`
- L206 _private member_ `UE::Geometry::FAxisAlignedBox3d Bounds;`
- L208 _private member_ `TMap<int32, int32> MeshToCollectionFaceMapping;` — optional face mapping from the mesh to the collection ( see bGenerateMeshToCollectionFaceMapping option )

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace PlanarCut` (scope `UE`)
- L25 _prototype_ `void SetGeometryCollectionAttributes(UE::Geometry::FDynamicMesh3& Mesh, int32 NumUVLayers);` (scope `UE::PlanarCut`) — Add attributes necessary for a dynamic mesh to represent geometry from an FGeometryCollection
- L31 _prototype_ `void ClearCustomGeometryCollectionAttributes(UE::Geometry::FDynamicMesh3& Mesh);` (scope `UE::PlanarCut`) — Clear custom FGeometryCollection-specific attributes from a FDynamicMesh3 Note: Does not remove the general attribute layer and MaterialID attributes, as these are not specific to geometry collections
- L34 _namespace_ `namespace AugmentedDynamicMesh` (scope `UE::PlanarCut`)
- L36 _prototype_ `void SetVisibility(UE::Geometry::FDynamicMesh3& Mesh, int TID, bool bIsVisible);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L37 _prototype_ `bool GetVisibility(const UE::Geometry::FDynamicMesh3& Mesh, int TID);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L38 _prototype_ `void SetInternal(UE::Geometry::FDynamicMesh3& Mesh, int TID, bool bIsInternal);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L39 _prototype_ `bool GetInternal(const UE::Geometry::FDynamicMesh3& Mesh, int TID);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L40 _prototype_ `void SetUV(UE::Geometry::FDynamicMesh3& Mesh, int VID, FVector2f UV, int UVLayer);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L41 _prototype_ `void GetUV(const UE::Geometry::FDynamicMesh3& Mesh, int VID, FVector2f& UV, int UVLayer);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L42 _prototype_ `void SetTangent(UE::Geometry::FDynamicMesh3& Mesh, int VID, FVector3f Normal, FVector3f TangentU, FVector3f TangentV);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L43 _prototype_ `void GetTangent(const UE::Geometry::FDynamicMesh3& Mesh, int VID, FVector3f& U, FVector3f& V);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L45 _prototype_ `void InitializeOverlayToPerVertexUVs(UE::Geometry::FDynamicMesh3& Mesh, int32 NumUVLayers, int32 FirstUVLayer = 0);` (scope `UE::PlanarCut::AugmentedDynamicMesh`) — Initialize UV overlays based on the custom AugmentedDynamicMesh per-vertex UV attributes.  Optionally use FirstUVLayer to skip layers
- L46 _prototype_ `void InitializeOverlayToPerVertexTangents(UE::Geometry::FDynamicMesh3& Mesh);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L47 _prototype_ `void InitializeOverlayToPerVertexColors(UE::Geometry::FDynamicMesh3& Mesh);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L48 _prototype_ `void ComputeTangents(UE::Geometry::FDynamicMesh3& Mesh, bool bOnlyInternalSurfaces, bool bRecomputeNormals = true, bool bMakeSharpEdges = false, float SharpAngleDegrees = 60);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L50 _prototype_ `void AddCollisionSamplesPerComponent(UE::Geometry::FDynamicMesh3& Mesh, double Spacing);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)
- L51 _prototype_ `void SplitOverlayAttributesToPerVertex(UE::Geometry::FDynamicMesh3& Mesh, bool bSplitUVs = true, bool bSplitTangents = true);` (scope `UE::PlanarCut::AugmentedDynamicMesh`)

### `Plugins/Experimental/PlanarCutPlugin/Source/PlanarCut/Public/FractureAutoUV.h` (Public)


#### enum `UE::PlanarCut::EUseMaterials`  
`enum class EUseMaterials`  
_L18-23_
- desc: Note: prefer ETargetFaces below
- L20 _public enumerator_ `AllMaterials` — Include all materials
- L21 _public enumerator_ `OddMaterials` — Include materials w/ odd IDs (+ any manually selected materials)
- L22 _public enumerator_ `NoDefaultMaterials` — No default materials; Only use manually selected materials

#### enum `UE::PlanarCut::ETargetFaces`  
`enum class ETargetFaces`  
_L25-32_
- L27 _public enumerator_ `AllFaces`
- L28 _public enumerator_ `InternalFaces`
- L29 _public enumerator_ `ExternalFaces`
- L31 _public enumerator_ `CustomFaces` — If custom faces is chosen, then no faces are selected by default, and some other criteria (such as Material ID) must be used to select the target faces

#### struct `UE::PlanarCut::FMergeIslandSettings`  
`struct FMergeIslandSettings`  
_L84-101_
- L91 _public member_ `double AreaDistortionThreshold = 1.5;` — Threshold for allowed area distortion from merging islands (when we use ExpMap to compute new UVs for the merged island)
- L93 _public member_ `double MaxNormalDeviationDeg = 45.0;` — Threshold for allowed normal deviation between merge-able islands
- L99 _public member_ `int32 NormalSmoothingRounds = 0;`
- L100 _public member_ `double NormalSmoothingAlpha = 0.25;`

#### enum `UE::PlanarCut::EBakeAttributes`  
`enum class EBakeAttributes : int32`  
_L189-201_
- desc: Different attributes we can bake
- L191 _public enumerator_ `None`
- L192 _public enumerator_ `DistanceToExternal`
- L193 _public enumerator_ `AmbientOcclusion`
- L194 _public enumerator_ `Curvature`
- L195 _public enumerator_ `NormalX`
- L196 _public enumerator_ `NormalY`
- L197 _public enumerator_ `NormalZ`
- L198 _public enumerator_ `PositionX`
- L199 _public enumerator_ `PositionY`
- L200 _public enumerator_ `PositionZ`

#### struct `UE::PlanarCut::FTextureAttributeSettings`  
`struct FTextureAttributeSettings`  
_L203-220_
- L205 _public member_ `double ToExternal_MaxDistance = 100.0;`
- L206 _public member_ `int AO_Rays = 32;`
- L207 _public member_ `double AO_BiasAngleDeg = 15.0;`
- L208 _public member_ `bool bAO_Blur = true;`
- L209 _public member_ `double AO_BlurRadius = 2.5;`
- L210 _public member_ `double AO_MaxDistance = 0.0;` — 0.0 is interpreted as TNumericLimits<double>::Max()
- L211 _public member_ `int Curvature_VoxelRes = 128;`
- L212 _public member_ `double Curvature_Winding = .5;`
- L213 _public member_ `int Curvature_SmoothingSteps = 10;`
- L214 _public member_ `double Curvature_SmoothingPerStep = .8;`
- L215 _public member_ `bool bCurvature_Blur = true;`
- L216 _public member_ `double Curvature_BlurRadius = 2.5;`
- L217 _public member_ `double Curvature_ThicknessFactor = 3.0;` — distance to search for mesh correspondence, as a factor of voxel size
- L218 _public member_ `double Curvature_MaxValue = .1;` — curvatures above this value will be clamped
- L219 _public member_ `int ClearGutterChannel = -1;` — don't copy gutter values for this channel, if specified -- useful for visualizing the UV island borders

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PlanarCut` (scope `UE`)
- L44 _prototype_ `bool BoxProjectUVs( int32 TargetUVLayer, FGeometryCollection& Collection, const FVector3d& BoxDimensions, ETargetFaces TargetFaces = ETargetFaces::InternalFaces, TArrayView<int32> TargetMaterials = TArrayView<int32>(), FVector2f OffsetUVs = FVector2f(.5f,.5f), bool bOverrideBoxDimensionsWithBounds = false, bool bCenterBoxAtPivot = false, bool bUniformProjectionScale = false );` (scope `UE::PlanarCut`) — Box project UVs @param TargetUVLayer		Which UV layer to update @param Collection		The collection to be box projected @param BoxDimensions		Scale of projection box @param TargetFaces		Which faces to automatically consider for box projection @param TargetMaterials	If non-empty, additionally consider faces with listed material IDs for box projection
- L66 _function_ `inline bool BoxProjectUVs( int32 TargetUVLayer, FGeometryCollection& Collection, const FVector3d& BoxDimensions, EUseMaterials MaterialsPattern = EUseMaterials::OddMaterials, TArrayView<int32> WhichMaterials = TArrayView<int32>(), FVector2f OffsetUVs = FVector2f(.5f,.5f), bool bOverrideBoxDimensionsWithBounds = false, bool bCenterBoxAtPivot = false, bool bUniformProjectionScale = false )` (scope `UE::PlanarCut`) — `UE_DEPRECATED(5.3, "Use the BoxProjectUVs variant that takes ETargetFaces instead")` — Box project UVs @param TargetUVLayer		Which UV layer to update @param Collection		The collection to be box projected @param BoxDimensions		Scale of projection box @param MaterialsPattern	Which pattern of material IDs to automatically consider for box projection @param WhichMaterials	If non-empty, consider listed material IDs for UV box projection
- L107 _prototype_ `bool MergeUVIslands( int32 TargetUVLayer, FGeometryCollection& Collection, FMergeIslandSettings MergeIslandSettings, TArrayView<bool> FaceSelection, FProgressCancel* Progress = nullptr );` (scope `UE::PlanarCut`) — Merge existing UV islands on the chosen faces and UV Layer, based on a normal angle threshold and a distortion threshold. The Exponential Map algorithm will be used to compute new UVs for the merged islands.
- L127 _prototype_ `bool UVLayout( int32 TargetUVLayer, FGeometryCollection& Collection, int32 UVRes = 1024, float GutterSize = 1, ETargetFaces MaterialsPattern = ETargetFaces::InternalFaces, TArrayView<int32> WhichMaterials = TArrayView<int32>(), bool bRecreateUVsForDegenerateIslands = true, FProgressCancel* Progress = nullptr );` (scope `UE::PlanarCut`) — Make a UV atlas of non-overlapping UV charts for a geometry collection, using the existing UV islands @param TargetUVLayer		Which UV layer to update with new UV coordinates @param Collection		The collection to be atlas'd @param UVRes				Target resolution for the atlas @param GutterSize		Space to leave between UV islands, in pixels at the target resolution @param TargetFaces		Which faces to automatically consider for UV island layout @param TargetMaterials	If non-empty, additionally consider faces with listed material IDs for UV island layout @param bRecreateUVsForDegenerateIslands If true, detect and fix islands that don't have proper UVs (i.e. UVs all zero or otherwise collapsed to a point)
- L148 _prototype_ `bool UVLayout( int32 TargetUVLayer, FGeometryCollection& Collection, int32 UVRes, float GutterSize, TArrayView<bool> FaceSelection, bool bRecreateUVsForDegenerateIslands = true, FProgressCancel* Progress = nullptr );` (scope `UE::PlanarCut`) — Make a UV atlas of non-overlapping UV charts for a geometry collection ( face selection version ) @param TargetUVLayer		Which UV layer to update with new UV coordinates @param Collection		The collection to be atlas'd @param UVRes				Target resolution for the atlas @param GutterSize		Space to leave between UV islands, in pixels at the target resolution @param FacesSelection	Which faces to automatically consider for UV island layout @param bRecreateUVsForDegenerateIslands If true, detect and fix islands that don't have proper UVs (i.e. UVs all zero or otherwise collapsed to a point)
- L170 _function_ `inline bool UVLayout( int32 TargetUVLayer, FGeometryCollection& Collection, int32 UVRes = 1024, float GutterSize = 1, EUseMaterials MaterialsPattern = EUseMaterials::OddMaterials, TArrayView<int32> WhichMaterials = TArrayView<int32>(), bool bRecreateUVsForDegenerateIslands = true, FProgressCancel* Progress = nullptr )` (scope `UE::PlanarCut`) — `UE_DEPRECATED(5.3, "Use the UVLayout variant that takes ETargetFaces instead")` — Make a UV atlas of non-overlapping UV charts for a geometry collection @param TargetUVLayer		Which UV layer to update with new UV coordinates @param Collection		The collection to be atlas'd @param UVRes				Target resolution for the atlas @param GutterSize		Space to leave between UV islands, in pixels at the target resolution @param MaterialsPattern	Which pattern of material IDs to automatically consider for UV island layout @param WhichMaterials	If non-empty, consider listed material IDs for UV island layout @param bRecreateUVsForDegenerateIslands If true, detect and fix islands that don't have proper UVs (i.e. UVs all zero or otherwise collapsed to a point)
- L235 _prototype_ `bool TextureSpecifiedFaces( int32 TargetUVLayer, FGeometryCollection& Collection, int32 GutterSize, UE::Geometry::FIndex4i BakeAttributes, const FTextureAttributeSettings& AttributeSettings, UE::Geometry::TImageBuilder<FVector4f>& TextureOut, ETargetFaces MaterialsPattern = ETargetFaces::InternalFaces, TArrayView<int32> WhichMaterials = TArrayView<int32>(), FProgressCancel* Progress = nullptr );` (scope `UE::PlanarCut`) — Generate a texture for specified groups of faces based on chosen BakeAttributes and AttributeSettings @param TargetUVLayer		Which UV layer to take UV coordinates from when creating the new texture @param Collection		The collection to be create a new texture for @param GutterSize		Number of texels to fill outside of UV island borders (values are copied from nearest inside pt) @param BakeAttributes	Which attributes to bake into which color channel @param AttributeSettings	Settings for the BakeAttributes @param TextureOut		Texture to write to @param MaterialsPattern	Which pattern of material IDs to apply texture to @param WhichMaterials	If non-empty, apply texture to the listed material IDs
- L271 _prototype_ `bool TextureInternalSurfaces( int32 TargetUVLayer, FGeometryCollection& Collection, int32 GutterSize, UE::Geometry::FIndex4i BakeAttributes, const FTextureAttributeSettings& AttributeSettings, UE::Geometry::TImageBuilder<FVector4f>& TextureOut, EUseMaterials MaterialsPattern = EUseMaterials::OddMaterials, TArrayView<int32> WhichMaterials = TArrayView<int32>(), FProgressCancel* Progress = nullptr );` (scope `UE::PlanarCut`) — `UE_DEPRECATED(5.3, "Use TextureSpecifiedFaces instead")`

### `Plugins/Experimental/PlanarCutPlugin/Source/PlanarCut/Public/PlanarCut.h` (Public)


#### struct `FNoiseOffsets`  
`struct FNoiseOffsets`  
_L17-37_
- desc: Offsets to randomize where Perlin noise is sampled for each dimension of a noise vector
- L19 _public function_ `FNoiseOffsets(FRandomStream& RandomStream) : X(RandomStream.VRand() * RandomOffsetScale), Y(RandomStream.VRand() * RandomOffsetScale), Z(RandomStream.VRand() * RandomOffsetScale)`
- L24 _public function_ `FNoiseOffsets()`
- L26 _public function_ `void SetOffsets(FRandomStream& RandomStream)`
- L33 _public member_ `FVector X, Y, Z;`
- L33 _public member_ `FVector X, Y, Z;`
- L33 _public member_ `FVector X, Y, Z;`
- L36 _private member_ `static constexpr double RandomOffsetScale = 100.0;` — Offset scale chosen to keep reasonably small offsets while still de-correlating the noise in each dimension.

#### struct `FNoiseSettings`  
`struct FNoiseSettings`  
_L39-79_
- L42 _public member_ `TFunction<FVector3d(const FVector& Pos)> NoiseOverride = nullptr;` — if NoiseOverride is set, will be used instead of default Octave Noise.
- L44 _public member_ `float PointSpacing = 1;` — desired spacing between noise samples, used for both Octave Noise and Noise Override cases
- L47 _public member_ `float Amplitude = 2;` — Octave Noise settings, not used if NoiseOverride is specified
- L48 _public member_ `float Frequency = 0.1f;`
- L49 _public member_ `int32 Octaves = 4;`
- L50 _public member_ `float Lacunarity = 2;`
- L51 _public member_ `float Persistence = 0.5f;`
- L53 _public function_ `FVector NoiseVector(const FVector& Pos, const FNoiseOffsets& Offsets) const`
- L68 _public function_ `float OctaveNoise(const FVector& V) const`

#### struct `FIslandSplitSettings`  
`struct FIslandSplitSettings`  
_L82-98_
- desc: Settings controlling how disconnected islands are detected and split after a cut
- L85 _public function_ `FIslandSplitSettings(bool bInSplitIslands = true, double InCloseVertexDistance = 1e-3, double InVertexToSurfaceBridgeDistance = 0) : bSplitIslands(bInSplitIslands), CloseVertexDistance(InCloseVertexDistance), VertexToSurfaceBridgeDistance(InVertexToSurfaceBridgeDistance)`
- L90 _public member_ `bool bSplitIslands = true;` — Whether to detect and split disconnected islands
- L93 _public member_ `double CloseVertexDistance = 1e-3;` — Distance threshold for connecting spatially-close vertices before computing islands
- L96 _public member_ `double VertexToSurfaceBridgeDistance = 0;` — If > 0, bridge separate islands whose surfaces are within this vertex-to-triangle distance

#### struct `FInternalSurfaceMaterials`  
`struct FInternalSurfaceMaterials`  
_L101-119_
- desc: auxiliary structure for FPlanarCells to carry material info
- L103 _public member_ `int32 GlobalMaterialID = 0;`
- L104 _public member_ `bool bGlobalVisibility = true;`
- L105 _public member_ `float GlobalUVScale = 1;`
- L107 _public member_ `TOptional<FNoiseSettings> NoiseSettings;` — if unset, noise will not be added
- L115 _public prototype_ `void SetUVScaleFromCollection(const GeometryCollection::Facades::FCollectionMeshFacade& CollectionMesh, int32 GeometryIdx = -1);` — @param Collection	Reference collection to use for setting UV scale @param GeometryIdx	Reference geometry inside collection; if -1, use all geometries in collection
- L118 _public prototype_ `int32 GetDefaultMaterialIDForGeometry(const FGeometryCollection& Collection, int32 GeometryIdx = -1) const;`

#### struct `FPlanarCells`  
`struct FPlanarCells`  
_L122-220_
- desc: Stores planar facets that divide space into cells
- L124 _public function_ `FPlanarCells()`
- L127 _public prototype_ `FPlanarCells(const FPlane& Plane);`
- L128 _public prototype_ `FPlanarCells(const TArrayView<const FVector> Sites, FVoronoiDiagram &Voronoi);`
- L129 _public prototype_ `FPlanarCells(const TArrayView<const FBox> Boxes, bool bResolveAdjacencies = false);`
- L130 _public prototype_ `FPlanarCells(const FBox &Region, const FIntVector& CubesPerAxis);`
- L131 _public prototype_ `FPlanarCells(const FBox &Region, const TArrayView<const FColor> Image, int32 Width, int32 Height);`
- L133 _public member_ `int32 NumCells;`
- L134 _public member_ `bool AssumeConvexCells = false;` — enables optimizations in this common case (can create incorrect geometry if set to true when cells are not actually convex)
- L135 _public member_ `TArray<FPlane> Planes;`
- L137 _public member_ `TArray<TPair<int32, int32>> PlaneCells;` — the two cells neighboring each plane, w/ the cell on the negative side of the plane first, positive side second
- L138 _public member_ `TArray<TArray<int32>> PlaneBoundaries;`
- L139 _public member_ `TArray<FVector> PlaneBoundaryVertices;`
- L141 _public member_ `FInternalSurfaceMaterials InternalSurfaceMaterials;`
- L144 _public prototype_ `void DiscardCells(TFunctionRef<bool(int32)> KeepFunc, bool bKeepNeighbors);` — Discards cells from the diagram, used to support visualization of a subset of cells
- L149 _public function_ `bool IsInfinitePlane() const` — @return true if this is a single, unbounded cutting plane
- L158 _public function_ `bool HasValidPlaneBoundaryOrientations() const` — Debugging function to check that the plane boundary vertices are wound to match the orientation of the plane normal vectors @return	false if any plane boundary vertices are found in the 'wrong' orientation relative to the plane normal
- L201 _public function_ `inline void AddPlane(const FPlane &P, int32 CellIdxBehind, int32 CellIdxInFront)`
- L208 _public function_ `inline int32 AddPlane(const FPlane &P, int32 CellIdxBehind, int32 CellIdxInFront, const TArray<int32>& PlaneBoundary)`
- L216 _public function_ `void SetNoise(FNoiseSettings Noise = FNoiseSettings())`

#### enum `UE::PlanarCut::ENeighborSelectionMethod`  
`enum ENeighborSelectionMethod`  
_L416-421_
- L418 _public enumerator_ `LargestNeighbor`
- L419 _public enumerator_ `NearestCenter`
- L420 _public enumerator_ `LargestContactArea`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PLANARCUT_API`
- L11 _namespace_ `namespace GeometryCollection`
- L11 _namespace_ `namespace Facades` (scope `GeometryCollection`)
- L239 _prototype_ `int32 CutWithPlanarCells( FPlanarCells &Cells, FGeometryCollection& Collection, int32 TransformIdx, double Grout, double CollisionSampleSpacing, int32 RandomSeed, const TOptional<FTransform>& TransformCollection = TOptional<FTransform>(), bool bIncludeOutsideCellInOutput = true, bool bSetDefaultInternalMaterialsFromCollection = true, FProgressCancel* Progress = nullptr, FVector CellsOrigin = FVector::ZeroVector, FIslandSplitSettings IslandSplitSettings = FIslandSplitSettings() );` — Cut a Geometry inside a GeometryCollection with PlanarCells, and add each cut cell back to the GeometryCollection as a new child of the input Geometry.  For geometries that would not be cut, nothing is added. @param Cells				Defines the cutting planes and division of space @param Collection		The collection to be cut @param TransformIdx		Which transform inside the collection to cut @param Grout				Separation to leave between cutting cells @param CollisionSampleSpacing	Target spacing between collision sample vertices @param RandomSeed				Seed to be used for random noise displacement @param TransformCollection		Optional transform of the whole geometry collection; if unset, defaults to Identity @param bIncludeOutsideCellInOutput	If true, geometry that was not inside any of the cells (e.g. was outside of the bounds of all cutting geometry) will still be included in the output; if false, it will be discarded. @param Progress						Optionally tracks progress and supports early-cancel @param CellsOrigin					Optionally provide a local origin of the cutting Cells @param IslandSplitSettings			Controls detection and splitting of disconnected components after the cut @return	index of first new geometry in the Output GeometryCollection, or -1 if no geometry was added
- L267 _prototype_ `void CreateCuttingSurfacePreview( const FPlanarCells& Cells, const FBox& Bounds, double Grout, int32 RandomSeed, UE::Geometry::FDynamicMesh3& OutCuttingMeshes, TFunctionRef<bool(int)> FilterCellsFunc, const TOptional<FTransform>& TransformCollection = TOptional<FTransform>(), FProgressCancel* Progress = nullptr, FVector CellsOrigin = FVector::ZeroVector );` — Generate cutting mesh surfaces as a single mesh Useful for creating a preview of the cut surface. @param Cells				Defines the cutting planes and division of space @param Grout				Separation to leave between cutting cells @param RandomSeed				Seed to be used for random noise displacement @param OutCuttingMeshes			Dynamic mesh representing the preview surface @param FilterCellsFunc			Filter which cells should be included in the preview @param TransformCollection		Optional transform that would be applied to the to-cut surface; if unset, defaults to Identity @param Progress						Optionally tracks progress and supports early-cancel @param CellsOrigin					Optionally provide a local origin of the cutting Cells
- L295 _prototype_ `int32 CutMultipleWithPlanarCells( FPlanarCells &Cells, FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, double Grout, double CollisionSampleSpacing, int32 RandomSeed, const TOptional<FTransform>& TransformCollection = TOptional<FTransform>(), bool bIncludeOutsideCellInOutput = true, bool bSetDefaultInternalMaterialsFromCollection = true, FProgressCancel* Progress = nullptr, FVector CellsOrigin = FVector::ZeroVector, FIslandSplitSettings IslandSplitSettings = FIslandSplitSettings() );` — Cut multiple Geometry groups inside a GeometryCollection with PlanarCells, and add each cut cell back to the GeometryCollection as a new child of their source Geometry.  For geometries that would not be cut, nothing is added. @param Cells				Defines the cutting planes and division of space @param Collection		The collection to be cut @param TransformIndices	Which transform groups inside the collection to cut @param Grout				Separation to leave between cutting cells @param CollisionSampleSpacing	Target spacing between collision sample vertices @param RandomSeed				Seed to be used for random noise displacement @param TransformCollection		Optional transform of the whole geometry collection; if unset, defaults to Identity @param bIncludeOutsideCellInOutput	If true, geometry that was not inside any of the cells (e.g. was outside of the bounds of all cutting geometry) will still be included in the output; if false, it will be discarded. @param Progress						Optionally tracks progress and supports early-cancel @param CellsOrigin					Optionally provide a local origin of the cutting Cells @param IslandSplitSettings			Controls detection and splitting of disconnected components after the cut @return	index of first new geometry in the Output GeometryCollection, or -1 if no geometry was added
- L319 _prototype_ `int32 SplitIslands( FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, double CollisionSampleSpacing, FProgressCancel* Progress = nullptr, FIslandSplitSettings IslandSplitSettings = FIslandSplitSettings() );` — Split the geometry at the given transforms into their connected components @param Collection		The collection to be cut @param TransformIndices	Which transform groups inside the collection to cut @param CollisionSampleSpacing	Target spacing between collision sample vertices @param Progress						Optionally tracks progress and supports early-cancel @return	index of first new geometry in the Output GeometryCollection, or -1 if no geometry was added
- L342 _prototype_ `int32 CutMultipleWithMultiplePlanes( const TArrayView<const FPlane>& Planes, FInternalSurfaceMaterials& InternalSurfaceMaterials, FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, double Grout, double CollisionSampleSpacing, int32 RandomSeed, const TOptional<FTransform>& TransformCollection = TOptional<FTransform>(), bool bSetDefaultInternalMaterialsFromCollection = true, FProgressCancel* Progress = nullptr, FIslandSplitSettings IslandSplitSettings = FIslandSplitSettings() );` — Cut multiple Geometry groups inside a GeometryCollection with Planes, and add each cut cell back to the GeometryCollection as a new child of their source Geometry.  For geometries that would not be cut, nothing is added. @param Planes				Defines the cutting planes and division of space @param InternalSurfaceMaterials	Defines material properties for any added internal surfaces @param Collection			The collection to be cut @param TransformIndices	Which transform groups inside the collection to cut @param Grout				Separation to leave between cutting cells @param CollisionSampleSpacing	Target spacing between collision sample vertices @param RandomSeed				Seed to be used for random noise displacement @param TransformCollection		Optional transform of the whole geometry collection; if unset, defaults to Identity @param Progress					Optionally tracks progress and supports early-cancel @param IslandSplitSettings			Controls detection and splitting of disconnected components after the cut @return	index of first new geometry in the Output GeometryCollection, or -1 if no geometry was added
- L366 _prototype_ `void FindBoneVolumes( FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, TArray<double>& OutVolumes, double ScalePerDimension = .01, bool bIncludeClusters = false );` — Populate an array of transform indices w/ those that are smaller than a threshold volume @param Collection			The collection to be processed @param TransformIndices		The transform indices to process, or empty if all should be processed @param OutVolumes			Output array, to be filled w/ volumes of geometry; 1:1 w/ TransformIndices array @param ScalePerDimension		Scale to apply per dimension (e.g. 1/100 converts volume from centimeters^3 to meters^3) @param bIncludeClusters		Whether to set the volumes for clusters as a sum of the child volumes. Otherwise, cluster volumes are set to zero.
- L384 _prototype_ `void FindSmallBones( const FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, const TArrayView<const double>& Volumes, double MinVolume, TArray<int32>& OutSmallBones, bool bIncludeClusters = false );` — Populate an array of transform indices w/ those that are smaller than a threshold volume @param Collection			The collection to be processed @param TransformIndices		The transform indices to process, or empty if all should be processed @param Volumes				Volumes of geometry; 1:1 w/ TransformIndices array @param MinVolume				Geometry smaller than this quantity will be chosen @param OutSmallBones			Output array, to be filled with transform indices for small pieces of geometry @param bIncludeClusters		Whether to include clusters in the search
- L403 _prototype_ `void FilterBonesByVolume( const FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, const TArrayView<const double>& Volumes, TFunctionRef<bool(double Volume, int32 BoneIdx)> Filter, TArray<int32>& OutSmallBones, bool bIncludeClusters = false );` — Populate an array of transform indices w/ those that match a custom volume-based filter @param Collection			The collection to be processed @param TransformIndices		The transform indices to process, or empty if all should be processed @param Volumes				Volumes of geometry; 1:1 w/ TransformIndices array @param Filter				Geometry for which the volume filter returns true will be chosen @param OutSmallBones			Output array, to be filled with transform indices for small pieces of geometry @param bIncludeClusters		Whether to allow clusters in the filter
- L412 _namespace_ `namespace UE`
- L414 _namespace_ `namespace PlanarCut` (scope `UE`)
- L439 _prototype_ `int32 MergeBones( FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, const TArrayView<const double>& Volumes, double MinVolume, const TArrayView<const int32>& SmallTransformIndices, bool bUnionJoinedPieces, UE::PlanarCut::ENeighborSelectionMethod NeighborSelectionMethod, bool bUseCollectionProximity = true, bool bOnlySameParent = false );` — Merge chosen geometry into neighboring geometry. @param Collection				The collection to be processed @param TransformIndices			The transform indices to process, or empty if all should be processed @param Volumes					Volumes of geometry; 1:1 w/ TransformIndices array @param MinVolume					If merged small geometry is larger than this, it will not require further merging @param SmallTransformIndices		Transform indices of pieces that we want to merge @param bUnionJoinedPieces		Try to 'union' the merged pieces, removing internal triangles and connecting the shared cut boundary @param NeighborSelectionMethod	How to choose which neighbor to merge to @param bUseCollectionProximity	If true, will use the proximity data on the collection to decide which pieces are allowed to merge. Otherwise, a reasonable default proximity will be computed and used. @param bOnlySameParent			Whether to only merge nodes that have the same parent in the hierarchy
- L463 _prototype_ `void MergeClusters( FGeometryCollection& Collection, const TArrayView<const double>& Volumes, double MinVolume, const TArrayView<const int32>& SmallTransformIndices, UE::PlanarCut::ENeighborSelectionMethod NeighborSelectionMethod, bool bOnlyMergeInProximity, bool bOnlySameParent, bool bUseCollectionProximity = true );` — Merge chosen bones into neighboring clusters. @param Collection				The collection to be processed @param Volumes					Volumes of geometry; 1:1 w/ TransformIndices array @param MinVolume					If merged small geometry is larger than this, it will not require further merging @param SmallTransformIndices		Transform indices of pieces that we want to merge @param NeighborSelectionMethod	How to choose which neighbor to merge to @param bOnlyMergeInProximity		Whether to only follow proximity graph, or to fall back to nearest center when for when no proximity links are found @param bOnlySameParent			Whether to only merge nodes that have the same parent in the hierarchy @param bUseCollectionProximity	If true, will use the proximity data on the collection to decide which pieces are allowed to merge. Otherwise, a reasonable default proximity will be computed and used.
- L481 _prototype_ `void MergeAllSelectedBones( FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, bool bUnionJoinedPieces );` — Merge all chosen nodes into a single node.  Unlike MergeBones(), does not account for proximity and will always only merge the selected bones. @param Collection				The collection to be processed @param TransformIndices			The transform indices to process, or empty if all should be processed @param bUnionJoinedPieces		Try to 'union' the merged pieces, removing internal triangles and connecting the shared cut boundary
- L498 _prototype_ `void RecomputeNormalsAndTangents(bool bOnlyTangents, bool bMakeSharpEdges, float SharpAngleDegrees, FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices = TArrayView<const int32>(), bool bOnlyInternalSurfaces = true);` — Recompute normals and tangents of selected geometry, optionally restricted to faces with odd or given material IDs (i.e. to target internal faces) @param bOnlyTangents		If true, leave normals unchanged and only recompute tangent&bitangent vectors @param bMakeSharpEdges	If true, recompute the normal topology to split normals at 'sharp' edges @param SharpAngleDegrees	If bMakeSharpEdges, edges w/ adjacent triangle normals deviating by more than this threshold will be sharp edges (w/ split normals) @param Collection		The Geometry Collection to be updated @param TransformIndices	Which transform groups on the Geometry Collection to be updated.  If empty, all groups are updated. @param bOnlyOddMaterials	If true, restrict recomputation to odd-numbered material IDs @param WhichMaterials	If non-empty, restrict recomputation to only the listed material IDs
- L508 _prototype_ `int32 AddCollisionSampleVertices(double TargetSpacing, FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices = TArrayView<const int32>());` — Scatter additional vertices (w/ no associated triangle) as needed to satisfy minimum point spacing @param TargetSpacing		The desired spacing between collision sample vertices @param Collection		The Geometry Collection to be updated @param TransformIndices	Which transform groups on the Geometry Collection to be updated.  If empty, all groups are updated. @return Index of first transform group w/ updated geometry.  (To update geometry we delete and re-add, because geometry collection isn't designed for in-place updates)
- L524 _prototype_ `int32 CutWithMesh( const UE::Geometry::FDynamicMesh3& CuttingMesh, FTransform CuttingMeshTransform, FInternalSurfaceMaterials& InternalSurfaceMaterials, FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, double CollisionSampleSpacing, const TOptional<FTransform>& TransformCollection = TOptional<FTransform>(), bool bSetDefaultInternalMaterialsFromCollection = true, FProgressCancel* Progress = nullptr, FIslandSplitSettings IslandSplitSettings = FIslandSplitSettings() );` — Cut multiple Geometry groups inside a GeometryCollection with a mesh, and add each cut cell back to the GeometryCollection as a new child of their source Geometry.  For geometries that would not be cut, nothing is added. @param CuttingMesh				Mesh to be used to cut the geometry collection @param CuttingMeshTransform		Position of cutting mesh @param InternalSurfaceMaterials	Defines material properties for any added internal surfaces @param Collection				The collection to be cut @param TransformIndices			Which transform groups inside the collection to cut @param CollisionSampleSpacing	Target spacing between collision sample vertices @param TransformCollection		Optional transform of the collection; if unset, defaults to Identity @param Progress					Optionally tracks progress and supports early-cancel @param IslandSplitSettings			Controls detection and splitting of disconnected components after the cut @return index of first new geometry in the Output GeometryCollection, or -1 if no geometry was added
- L538 _prototype_ `UE::Geometry::FDynamicMesh3 ConvertMeshDescriptionToCuttingDynamicMesh(const FMeshDescription* CuttingMesh, int32 NumUVLayers, FProgressCancel* Progress = nullptr);` — Convert a mesh description to a dynamic mesh *specifically* augmented / designed for cutting geometry collections, to be passed to CutWithMesh
- L540 _function_ `inline int32 CutWithMesh( const FMeshDescription* CuttingMesh, FTransform CuttingMeshTransform, FInternalSurfaceMaterials& InternalSurfaceMaterials, FGeometryCollection& Collection, const TArrayView<const int32>& TransformIndices, double CollisionSampleSpacing, const TOptional<FTransform>& TransformCollection = TOptional<FTransform>(), bool bSetDefaultInternalMaterialsFromCollection = true, FProgressCancel* Progress = nullptr, FIslandSplitSettings IslandSplitSettings = FIslandSplitSettings() )`
- L579 _prototype_ `void ConvertToMeshDescription( FMeshDescription& OutputMesh, FTransform& TransformOut, bool bCenterPivot, FGeometryCollection& Collection, const TManagedArray<FTransform>& BoneTransforms, const TArrayView<const int32>& TransformIndices, TFunction<int32(int32, bool)> RemapMaterialIDs = nullptr );` — Convert chosen Geometry groups inside a GeometryCollection to a single Mesh Description. @param OutputMesh				Mesh to be filled with the geometry collection geometry @param TransformOut				Transform taking output mesh geometry to local space of geometry collection @param bCenterPivot				Whether to center the geometry at the origin @param Collection				The collection to be converted @param TransformIndices			Which transform groups inside the collection to convert @param RemapMaterialIDs			Optional function to remap (MaterialID, bIsInternal) -> NewMaterialID
- L599 _prototype_ `void ConvertToMeshDescription( FMeshDescription& OutputMesh, FTransform& TransformOut, bool bCenterPivot, FGeometryCollection& Collection, const TManagedArray<FTransform3f>& BoneTransforms, const TArrayView<const int32>& TransformIndices, TFunction<int32(int32, bool)> RemapMaterialIDs = nullptr );` — Convert chosen Geometry groups inside a GeometryCollection to a single Mesh Description. @param OutputMesh				Mesh to be filled with the geometry collection geometry @param TransformOut				Transform taking output mesh geometry to local space of geometry collection @param bCenterPivot				Whether to center the geometry at the origin @param Collection				The collection to be converted @param TransformIndices			Which transform groups inside the collection to convert @param RemapMaterialIDs			Optional function to remap (MaterialID, bIsInternal) -> NewMaterialID
- L624 _prototype_ `void ConvertGeometryCollectionToDynamicMesh( UE::Geometry::FDynamicMesh3& OutputMesh, FTransform& TransformOut, bool bCenterPivot, const FGeometryCollection& Collection, bool bWeldEdges, TArrayView<const FTransform3f> BoneTransforms, bool bUseRelativeTransforms, TArrayView<const int32> TransformIndices, TFunction<int32(int32, bool)> RemapMaterialIDs = nullptr, bool bAllowInvisible = false, bool bSetPolygroupPerBone = true );` — Convert chosen Geometry groups inside a GeometryCollection to a single Dynamic Mesh. @param OutputMesh				Mesh to be filled with the geometry collection geometry @param TransformOut				Transform taking output mesh geometry to local space of geometry collection. This will be Identity unless bCenterPivot is true. @param bCenterPivot				Whether to center the geometry at the origin @param Collection				The collection to be converted @param bWeldEdges				Whether to weld edges on conversion @param BoneTransforms			Transforms for each bone in the geometry collection @param bUseRelativeTransforms	Whether the BoneTransforms are relative to each bone's parent, or in a shared space (e.g., Collection.Transform is relative, UGeometryCollectionComponent's component space transforms are not) @param TransformIndices			Which transform groups inside the collection to convert @param RemapMaterialIDs			Optional function to remap (MaterialID, bIsInternal) -> NewMaterialID @param bAllowInvisible			Allow mesh to include triangles that are not marked 'visible' (typically, pre-fracture geometry stored for potential history/LOD usage) @param bSetPolygroupPerBone		Enable PolyGroups on the OutputMesh and set one group per geometry

### `Plugins/Experimental/PlanarCutPlugin/Source/PlanarCut/Public/PlanarCutPlugin.h` (Public)


#### class `IPlanarCutPlugin`  
`class IPlanarCutPlugin : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IPlanarCutPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlanarCut, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPlanarCut, Log, All);`
