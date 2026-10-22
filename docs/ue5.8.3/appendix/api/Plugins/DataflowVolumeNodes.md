# Plugins / DataflowVolumeNodes

- module root: `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeNodes`
- headers: 4; symbols: 251
- symbol kinds: class=2, function=1, member=175, namespace=7, prototype=49, struct=17
- PrivateDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin, DataflowVolumeCore, DynamicMesh, Engine, GeometryCollectionEngine, GeometryCore, GeometryFramework, MeshConversion, MeshDescription, PlanarCut, StaticMeshDescription, Voronoi
- PublicDependencyModuleNames: 

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeNodes/Private/Dataflow/DataflowVolumeNodeAndPinTypeColors.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Dataflow` (scope `UE`)
- L7 _prototype_ `void RegisterVolumeColors();` (scope `UE::Dataflow`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeNodes/Private/Dataflow/DataflowVolumeNodes.h` (Private)


#### struct `FMakeSDFSphereDataflowNode`  
`struct FMakeSDFSphereDataflowNode : public FDataflowNode`  
_L23-60_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Make a sphere SDF
- L31 _public member_ `float VoxelSize = 1.f;` — `UPROPERTY(EditAnywhere, Category = "SDF", meta = (DataflowInput, ClampMin = 0.1f))` — The size of voxels in the output VDB volume
- L35 _public member_ `float Radius = 3.f;` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (DataflowInput, ClampMin = 0.1f))` — Sphere radius
- L39 _public member_ `FVector Center = FVector(0);` — `UPROPERTY(EditAnywhere, Category = "Sphere", meta = (DataflowInput))` — Sphere center
- L44 _public member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L47 _public member_ `bool bDrawVoxels = true;` — `UPROPERTY()`
- L50 _public member_ `bool bDrawVoxelCenters = false;` — `UPROPERTY()`
- L54 _public member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowOutput))` — SDF volume
- L56 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L59 _public prototype_ `FMakeSDFSphereDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMakeSDFCubeDataflowNode`  
`struct FMakeSDFCubeDataflowNode : public FDataflowNode`  
_L66-103_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Make a cube SDF
- L74 _private member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Cube", meta = (DataflowInput))` — Scale
- L78 _private member_ `FVector Center = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Cube", meta = (DataflowInput))` — Center
- L82 _private member_ `float VoxelSize = 1.f;` — `UPROPERTY(EditAnywhere, Category = "SDF", meta = (DataflowInput, ClampMin = 0.1f))` — The size of voxels in the output VDB volume
- L87 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L90 _private member_ `bool bDrawVoxels = true;` — `UPROPERTY()`
- L93 _private member_ `bool bDrawVoxelCenters = false;` — `UPROPERTY()`
- L97 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowOutput))` — SDF volume
- L99 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L102 _public prototype_ `FMakeSDFCubeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FMakeSDFPlatonicSolidDataflowNode`  
`struct FMakeSDFPlatonicSolidDataflowNode : public FDataflowNode`  
_L109-150_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Make a platonic solid SDF
- L117 _private member_ `EDataflowVolumePlatonicSolidType PlatonicSolidType = EDataflowVolumePlatonicSolidType::Tetrahedron;` — `UPROPERTY(EditAnywhere, Category = "Platonic Solid")` — Platonic solid type
- L121 _private member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Platonic Solid", meta = (DataflowInput))` — Scale
- L125 _private member_ `FVector Center = FVector(0.0);` — `UPROPERTY(EditAnywhere, Category = "Platonic Solid", meta = (DataflowInput))` — Center
- L129 _private member_ `float VoxelSize = 1.f;` — `UPROPERTY(EditAnywhere, Category = "SDF", meta = (DataflowInput, ClampMin = 0.1f))` — The size of voxels in the output VDB volume
- L134 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L137 _private member_ `bool bDrawVoxels = true;` — `UPROPERTY()`
- L140 _private member_ `bool bDrawVoxelCenters = false;` — `UPROPERTY()`
- L144 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowOutput))` — SDF volume
- L146 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L149 _public prototype_ `FMakeSDFPlatonicSolidDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVolumeInfoDataflowNode`  
`struct FVolumeInfoDataflowNode : public FDataflowNode`  
_L157-175_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Outputs info of a volume Grid(s), resolution, type, voxel count, voxel size
- L165 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowInput))` — Volume
- L169 _private member_ `FString String;` — `UPROPERTY(meta = (DataflowOutput))` — Formatted string containing the groups and attributes
- L171 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L174 _public prototype_ `FVolumeInfoDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FCollectionToVolumeDataflowNode`  
`struct FCollectionToVolumeDataflowNode : public FDataflowNode`  
_L183-267_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Convert a Collection to a volume
- L191 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Collection to convert to volume
- L198 _private member_ `FDataflowVolumeTypes ReferenceVolume;` — `UPROPERTY(meta = (DataflowInput))` — Optional reference volume, to use this grid's orientation and voxel size to create the new one. If the reference VDB is a Level set then match the narrow band width as well.
- L202 _private member_ `float VoxelSize = 1.f;` — `UPROPERTY(EditAnywhere, Category = "SDF", meta = (DataflowInput, ClampMin = 0.1f))` — The size of voxels in the SDF
- L206 _private member_ `EDataflowVolumeOutputType OutputType = EDataflowVolumeOutputType::SDF;` — `UPROPERTY(EditAnywhere, Category = "SDF")` — Name of the SDF grid in the VDB
- L210 _private member_ `FString GridName = FString(TEXT("Leve` — `UPROPERTY(EditAnywhere, Category = "SDF")` — Name of the SDF grid in the VDB
- L214 _private member_ `bool bUseWorldSpaceUnits = false;` — `UPROPERTY(EditAnywhere, Category = "SDF")` — Use world space units for narrow band
- L218 _private member_ `float ExteriorBand = 1.f;` — `UPROPERTY(EditAnywhere, Category = "SDF", meta = (ClampMin = 0.00001f, ClampMax = 10.f, EditCondition = "bUseWorldSpaceUnits == true", EditConditionHides))`
- L222 _private member_ `float InteriorBand = 1.f;` — `UPROPERTY(EditAnywhere, Category = "SDF", meta = (ClampMin = 0.00001f, ClampMax = 10.f, EditCondition = "bUseWorldSpaceUnits == true && bFillInterior == false", EditConditionHides))`
- L226 _private member_ `int32 ExteriorBandVoxels = 3;` — `UPROPERTY(EditAnywhere, Category = "SDF", meta = (ClampMin = 1, ClampMax = 10, EditCondition = "bUseWorldSpaceUnits == false", EditConditionHides))`
- L230 _private member_ `int32 InteriorBandVoxels = 3;` — `UPROPERTY(EditAnywhere, Category = "SDF", meta = (ClampMin = 1, ClampMax = 10, EditCondition = "bUseWorldSpaceUnits == false && bFillInterior == false", EditConditionHides))`
- L234 _private member_ `bool bFillInterior = false;` — `UPROPERTY(EditAnywhere, Category = "SDF")`
- L238 _private member_ `bool bPreserveHoles = false;` — `UPROPERTY(EditAnywhere, Category = "SDF")`
- L242 _private member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Closest Surface Point", meta = (DataflowInput))` — IsoValue specifying the surface for ClosestSurfacePointVolume
- L247 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L250 _private member_ `bool bDrawVoxels = false;` — `UPROPERTY()`
- L253 _private member_ `bool bDrawVoxelCenters = true;` — `UPROPERTY()`
- L257 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowOutput))` — Float volume
- L261 _private member_ `FDataflowIntVolume FaceIndexVolume;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "FaceIndex Volume"))` — Every voxel stores the closest face index
- L263 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L266 _public prototype_ `FCollectionToVolumeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVolumeToSpheresDataflowNode`  
`struct FVolumeToSpheresDataflowNode : public FDataflowNode`  
_L275-329_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Fill an SDF/Fog volume with spheres, using the original algorithm
- L283 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowInput))` — Float volume
- L286 _private member_ `int32 MinSphereCount = 1;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Minimum Sphere Count"))`
- L289 _private member_ `int32 MaxSphereCount = 50;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Maximum Sphere Count"))`
- L292 _private member_ `bool bOverlapping = false;` — `UPROPERTY(EditAnywhere, Category = "Spheres")`
- L295 _private member_ `float MinRadius = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Minimum Radius", ClampMin = 0.001f))`
- L298 _private member_ `float MaxRadius = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Maximum Radius", ClampMin = 0.001f))`
- L301 _private member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput))`
- L304 _private member_ `int32 InstanceCount = 10000;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, ClampMin = 1))`
- L309 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L312 _private member_ `bool bDrawSpheres = true;` — `UPROPERTY()`
- L315 _private member_ `bool bDrawSphereCenters = false;` — `UPROPERTY()`
- L319 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))`
- L323 _private member_ `TArray<FSphere> Spheres;` — `UPROPERTY(meta = (DataflowOutput))`
- L325 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L328 _public prototype_ `FVolumeToSpheresDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVolumeToSpheresDataflowNode_v2`  
`struct FVolumeToSpheresDataflowNode_v2 : public FDataflowNode`  
_L337-409_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Fill an SDF/Fog volume with spheres, using the improved algorithm
- L345 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowInput))` — Float volume
- L348 _private member_ `int32 MinSphereCount = 1;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Minimum Sphere Count"))`
- L351 _private member_ `int32 MaxSphereCount = 50;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Maximum Sphere Count"))`
- L354 _private member_ `bool bOverlapping = false;` — `UPROPERTY(EditAnywhere, Category = "Spheres")`
- L357 _private member_ `float MinRadius = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Minimum Radius", ClampMin = 0.001f))`
- L360 _private member_ `float MaxRadius = 1000.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Maximum Radius", ClampMin = 0.001f))`
- L363 _private member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput))`
- L366 _private member_ `int32 InstanceCount = 10000;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, ClampMin = 1))`
- L369 _private member_ `EDataflowVolumeScatterType ScatterType = EDataflowVolumeScatterType::Uniform;` — `UPROPERTY(EditAnywhere, Category = "Scatter")`
- L372 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput))`
- L376 _private member_ `float Spread = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 0, ClampMax = 1))`
- L380 _private member_ `float MinNumberOfPointsPerVoxel = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 0, EditCondition = "ScatterType != EDataflowVolumeScatterType::Uniform", EditConditionHides))` — Minimum for the random range
- L384 _private member_ `float MaxNumberOfPointsPerVoxel = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 0, EditCondition = "ScatterType != EDataflowVolumeScatterType::Uniform", EditConditionHides))` — Maximum for the random range
- L389 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L392 _private member_ `bool bDrawSpheres = true;` — `UPROPERTY()`
- L395 _private member_ `bool bDrawSphereCenters = false;` — `UPROPERTY()`
- L399 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))`
- L403 _private member_ `TArray<FSphere> Spheres;` — `UPROPERTY(meta = (DataflowOutput))`
- L405 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L408 _public prototype_ `FVolumeToSpheresDataflowNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertVolumeDataflowNode`  
`struct FConvertVolumeDataflowNode : public FDataflowNode`  
_L415-474_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Convert a volume to Volume/Polygons
- L423 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "FloatVolume", DataflowIntrinsic))` — Float volume
- L426 _private member_ `EDataflowVolumeConvertSDFTo ConvertTo = EDataflowVolumeConvertSDFTo::Collection;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (DisplayName = "Convert To"))`
- L429 _private member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (UiMin = -1, UIMax = 1, EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::Collection", EditConditionHides))`
- L432 _private member_ `float Adaptivity = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (ClampMin = 0, ClampMax = 1, EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::Collection", EditConditionHides))`
- L435 _private member_ `EDataflowVolumeConvertSDFGridClass GridClass = EDataflowVolumeConvertSDFGridClass::NoChange;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (DisplayName = "Class", EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::SDF", EditConditionHides))`
- L438 _private member_ `EDataflowVolumeConvertSDFGridType GridType = EDataflowVolumeConvertSDFGridType::NoChange;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (DisplayName = "Type", EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::SDF && GridClass == EDataflowVolumeConvertSDFGridClass::NoChange", EditConditionHides))`
- L441 _private member_ `float FogIsoValue = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (ClampMin = 0, ClampMax = 1, EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::SDF && GridClass == EDataflowVolumeConvertSDFGridClass::FogToSDF", EditConditionHides))`
- L444 _private member_ `bool bPruneTolerance = true;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::SDF", EditConditionHides))`
- L447 _private member_ `float Tolerance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::SDF && bPruneTolerance == true", EditConditionHides))`
- L450 _private member_ `bool bFloodFillOutput = true;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (DisplayName = "Signed-Flood Fill Output", EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::SDF", EditConditionHides))`
- L453 _private member_ `bool bActivateInteriror = true;` — `UPROPERTY(EditAnywhere, Category = "Convert", meta = (DisplayName = "Activate Interior Voxels", EditCondition = "ConvertTo == EDataflowVolumeConvertSDFTo::SDF", EditConditionHides))`
- L458 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L461 _private member_ `bool bDrawVoxels = true;` — `UPROPERTY()`
- L464 _private member_ `bool bDrawVoxelCenters = false;` — `UPROPERTY()`
- L468 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowOutput))` — Collection output
- L470 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L473 _public prototype_ `FConvertVolumeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FUniformVolumeScatterDataflowNode`  
`struct FUniformVolumeScatterDataflowNode : public FDataflowNode`  
_L480-523_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Uniformly scatter a total amount of points in active regions of a LevelSet or Fog volume
- L488 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Float volume
- L492 _private member_ `int32 MinNumberOfPoints = 100;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 1))` — Minimum for the random range
- L496 _private member_ `int32 MaxNumberOfPoints = 100;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 1))` — Maximum for the random range
- L500 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = "0"))` — Seed for random
- L504 _private member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (DataflowInput))` — IsoValue
- L508 _private member_ `float Spread = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (DataflowInput, ClampMin = 0, ClampMax = 1))`
- L513 _private member_ `FLinearColor Color = FLinearColor(0.7f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L517 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Generated points
- L519 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L522 _public prototype_ `FUniformVolumeScatterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDenseUniformVolumeScatterDataflowNode`  
`struct FDenseUniformVolumeScatterDataflowNode : public FDataflowNode`  
_L533-576_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Uniformly scatter a fixed number of points per active voxel of a LevelSet or Fog volume. If the pointsPerVoxel value provided is a fractional value, each voxel calculates a delta value of how likely it is to contain an extra point.
- L541 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Float volume
- L545 _private member_ `float MinNumberOfPointsPerVoxel = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 0))` — Minimum for the random range
- L549 _private member_ `float MaxNumberOfPointsPerVoxel = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 0))` — Maximum for the random range
- L553 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = "0"))` — Seed for random
- L557 _private member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (DataflowInput))` — IsoValue
- L561 _private member_ `float Spread = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (DataflowInput, ClampMin = 0, ClampMax = 1))`
- L566 _private member_ `FLinearColor Color = FLinearColor(0.7f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L570 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Generated points
- L572 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L575 _public prototype_ `FDenseUniformVolumeScatterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FNonUniformVolumeScatterDataflowNode`  
`struct FNonUniformVolumeScatterDataflowNode : public FDataflowNode`  
_L587-630_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Non uniformly scatter points per active voxel. The pointsPerVoxel value is used to weight each grids cell value to compute a fixed number of points for every active voxel. If the computed result is a fractional value, each voxel calculates a delta value of how likely it is to contain an extra point.
- L595 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Float volume
- L599 _private member_ `float MinNumberOfPointsPerVoxel = .1f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 0))` — Minimum for the random range
- L603 _private member_ `float MaxNumberOfPointsPerVoxel = .3f;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = 0))` — Maximum for the random range
- L607 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Scatter", meta = (DataflowInput, ClampMin = "0"))` — Seed for random
- L611 _private member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (DataflowInput))` — IsoValue
- L615 _private member_ `float Spread = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (DataflowInput, ClampMin = 0, ClampMax = 1))`
- L620 _private member_ `FLinearColor Color = FLinearColor(0.7f, 0.0f, 1.0f, 1.0f);` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L624 _private member_ `TArray<FVector> Points;` — `UPROPERTY(meta = (DataflowOutput))` — Generated points
- L626 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L629 _public prototype_ `FNonUniformVolumeScatterDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVolumeSampleToPointsDataflowNode`  
`struct FVolumeSampleToPointsDataflowNode : public FDataflowNode`  
_L636-675_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Sample a volume at input point's location
- L644 _private member_ `FDataflowVolumeTypes Volume;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Volume to sample
- L648 _private member_ `FDataflowVectorArrayTypes SamplePoints;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Points to sample at
- L651 _private member_ `EDataflowVolumeSampleType SampleType = EDataflowVolumeSampleType::Float;` — `UPROPERTY(EditAnywhere, Category = "Sampling")`
- L656 _private member_ `FLinearColor Color = FLinearColor(0.2f, 1.0f, 1.0f, 1.0f);` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L659 _private member_ `FString Attribute = FString("Att` — `UPROPERTY(EditAnywhere, Category = "Sampling")`
- L663 _private member_ `FDataflowAnyType OutArray;` — `UPROPERTY(meta = (DataflowOutput))` — TArray<float>, TArray<int32>, TArray<FVector3f>
- L666 _private member_ `FManagedArrayCollection PointsCollection;` — `UPROPERTY(meta = (DataflowOutput))`
- L668 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L671 _public prototype_ `FVolumeSampleToPointsDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L673 _public prototype_ `void SetOutTypeFromSampleType();`
- L674 _public prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`

#### struct `FVolumeSliceDataflowNode`  
`struct FVolumeSliceDataflowNode : public FDataflowNode`  
_L681-758_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- desc: Extracts 2d slices from a volume
- L690 _private member_ `FDataflowVolumeTypes Volume;` — FDataflowFloatVolume Volume;
- L694 _private member_ `EDataflowVolumeSliceMethod Method = EDataflowVolumeSliceMethod::Points;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings")`
- L698 _private member_ `EDataflowVolumeSlicePlane Plane = EDataflowVolumeSlicePlane::XYPlane;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings")`
- L702 _private member_ `float BoundingBoxScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings", meta = (ClampMin = "1", ClampMax = "10"))`
- L706 _private member_ `float Offset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings", meta = (ClampMin = "-1", ClampMax = "1"))`
- L709 _private member_ `bool bVisualize = true;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings")`
- L713 _private member_ `EDataflowVolumeSliceRamp ColorRampType = EDataflowVolumeSliceRamp::InfraRed;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Scalar Visualization Settings", meta = (EditCondition = "bVisualize == true", EditConditionHides))`
- L716 _private member_ `FLinearColorRamp LinearColorRamp;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Scalar Visualization Settings", meta = (EditCondition = "bVisualize == true", EditConditionHides, DisplayName = "ColorRamp"))`
- L719 _private member_ `bool bInvertColorRamp = false;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Scalar Visualization Settings")`
- L723 _private member_ `FVector2f Range = FVector2f(0.f, 1.f);` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Scalar Visualization Settings", meta = (ClampMin = "-100", ClampMax = "100", EditCondition = "bVisualize == true", EditConditionHides))`
- L726 _private member_ `float VectorScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Vector Visualization Settings", meta = (ClampMin = "0.01", ClampMax = "100", EditCondition = "bVisualize == true", EditConditionHides))`
- L729 _private member_ `float PointScale = 4.f;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Vector Visualization Settings", meta = (ClampMin = "0.01", ClampMax = "100", EditCondition = "bVisualize == true", EditConditionHides))`
- L732 _private member_ `float LineWidth = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Vector Visualization Settings", meta = (ClampMin = "0.01", ClampMax = "100", EditCondition = "bVisualize == true", EditConditionHides))`
- L735 _private member_ `float MinLength = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Vector Visualization Settings", meta = (ClampMin = "0.0001", ClampMax = "100", EditCondition = "bVisualize == true", EditConditionHides))`
- L738 _private member_ `FLinearColor PointColor = FLinearColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Vector Visualization Settings", meta = (EditCondition = "bVisualize == true", EditConditionHides))`
- L741 _private member_ `FLinearColor VectorColor = FLinearColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = "Visualization Settings - Vector Visualization Settings", meta = (EditCondition = "bVisualize == true", EditConditionHides))`
- L743 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L744 _private prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L747 _private function_ `virtual bool CanDebugDraw() const override`
- L751 _private prototype_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const override;`
- L752 _private prototype_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const override;`
- L755 _private prototype_ `void OnColorCurveChanged(TArray<FRichCurve*> Curves);`
- L757 _public prototype_ `FVolumeSliceDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVolumeAnalysisDataflowNode`  
`struct FVolumeAnalysisDataflowNode : public FDataflowNode`  
_L764-801_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- L772 _private member_ `FDataflowVolumeTypes Volume;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Volume to process (scalar or vector volume)
- L776 _private member_ `EDataflowVolumeAnalysisOperator Operator = EDataflowVolumeAnalysisOperator::Gradient;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L780 _private member_ `FDataflowBoolVolume MaskVolume;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "MaskVolume"))` — Mask volume
- L784 _private member_ `EDataflowVolumeAnalysisOutputName OutputName = EDataflowVolumeAnalysisOutputName::CustomName;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L788 _private member_ `FString CustomName = FString("Cus` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "OutputName == EDataflowVolumeAnalysisOutputName::CustomName", EditConditionHides))`
- L792 _private member_ `FDataflowVolumeTypes OutVolume;` — `UPROPERTY(meta = (DataflowOutput))` — Volume output (scalar or vector volume)
- L794 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L797 _public prototype_ `FVolumeAnalysisDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L799 _public prototype_ `void SetOutTypeFromOperator();`
- L800 _public prototype_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent) override;`

#### struct `FVolumeCombineDataflowNode`  
`struct FVolumeCombineDataflowNode : public FDataflowNode`  
_L809-866_
- reflection: `USTRUCT(meta = (DataflowVolume))`
- inherits: `FDataflowNode`
- L817 _private member_ `FDataflowFloatVolume FloatVolumeA;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Float A volume
- L821 _private member_ `FDataflowFloatVolume FloatVolumeB;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Float B volume
- L824 _private member_ `EDataflowVolumeSDFCombineOperation Operation = EDataflowVolumeSDFCombineOperation::SDFUnion;` — `UPROPERTY(EditAnywhere, Category = "Combine")`
- L827 _private member_ `bool bFlipInputs = false;` — `UPROPERTY(EditAnywhere, Category = "Combine")`
- L830 _private member_ `float MultiplierA = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Combine", meta = (DataflowInput, DisplayName = "A Multiplier", UIMin = -10.f, UIMax = 10.f))`
- L833 _private member_ `float MultiplierB = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Combine", meta = (DataflowInput, DisplayName = "B Multiplier", UIMin = -10.f, UIMax = 10.f))`
- L836 _private member_ `EDataflowVolumeSDFCombineResample Resample = EDataflowVolumeSDFCombineResample::BMatchA;` — `UPROPERTY(EditAnywhere, Category = "Combine")`
- L839 _private member_ `EDataflowVolumeSDFCombineInterpolation Interpolation = EDataflowVolumeSDFCombineInterpolation::Linear;` — `UPROPERTY(EditAnywhere, Category = "Combine")`
- L842 _private member_ `bool bPruneDegenerateTiles = false;` — `UPROPERTY(EditAnywhere, Category = "Combine", meta = (DisplayName = "Prune Degenarate Tiles"))`
- L845 _private member_ `float PruneTol = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Combine", meta = (DisplayName = "Prune Tolerance", UIMin = 0.f, UIMax = 1.f))`
- L850 _private member_ `FDataflowNodeDebugDrawSettings DebugDrawRenderSettings;` — `UPROPERTY()` — These properties are not needed anymore as we use the new rendering system. Since we don't wan't to version up the node we will just hide them.
- L853 _private member_ `bool bDrawVoxels = true;` — `UPROPERTY()`
- L856 _private member_ `bool bDrawVoxelCenters = false;` — `UPROPERTY()`
- L860 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowOutput))` — Output Float volume
- L862 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L865 _public prototype_ `FVolumeCombineDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVolumeTextureTerminalNode`  
`struct FVolumeTextureTerminalNode : public FDataflowTerminalNode`  
_L872-889_
- reflection: `USTRUCT(meta = (DataflowTerminal))`
- inherits: `FDataflowTerminalNode`
- desc: Terminal node to a save volume texture
- L879 _private member_ `FDataflowVolumeTypes Volume;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowIntrinsic, DataflowPassthrough = "Volume"))`
- L882 _private member_ `TObjectPtr<UVolumeTexture> VolumeTextureAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Asset, meta = (DataflowInput))`
- L884 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const override;`
- L885 _private prototype_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const override;`
- L888 _public prototype_ `FVolumeTextureTerminalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FVolumeToSpheresWithRelaxationDataflowNode`  
`struct FVolumeToSpheresWithRelaxationDataflowNode : public FDataflowNode`  
_L897-967_
- reflection: `USTRUCT(meta = (Experimental, DataflowVolume))`
- inherits: `FDataflowNode`
- L905 _private member_ `FDataflowFloatVolume FloatVolume;` — `UPROPERTY(meta = (DataflowInput))` — Float volume
- L909 _private member_ `int32 PointCount = 100;` — `UPROPERTY(EditAnywhere, Category = "PointScatter", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Number of points to scatter inside of the volume
- L913 _private member_ `int32 ScatterRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "PointScatter", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Random seed for scatter
- L917 _private member_ `float Spread = 1.f;` — `UPROPERTY(EditAnywhere, Category = "PointScatter", meta = (DataflowInput, UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))` — Spread for OpenVDB scatter
- L921 _private member_ `float MinRadius = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Minimum Radius", UIMin = 0.001, ClampMin = 0.001f))` — Minimum radius for spheres
- L925 _private member_ `float MaxRadius = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, DisplayName = "Maximum Radius", UIMin = 0.001, ClampMin = 0.001f))` — Maximum radius for spheres
- L929 _private member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput, UIMin = 0, ClampMin = 0))` — Random seed for radius
- L933 _private member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Spheres", meta = (DataflowInput))` — Isovalue used for scattering
- L937 _private member_ `bool bRemoveEmbededSpheres = true;` — `UPROPERTY(EditAnywhere, Category = "Spheres")` — Remove spheres which are completely inside of another sphere
- L941 _private member_ `bool bApplyRelaxation = true;` — `UPROPERTY(EditAnywhere, Category = "Relaxation")` — Apply relaxation to the remaining spheres after removal
- L945 _private member_ `int32 Steps = 10;` — `UPROPERTY(EditAnywhere, Category = "Relaxation", meta = (DataflowInput, DisplayName = "Iteration", UIMin = 1, ClampMin = 1, UIMax = 20, EditCondition = "bApplyRelaxation"))` — Number of iterations for the relaxation
- L949 _private member_ `float StepScalar = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Relaxation", meta = (DataflowInput, UIMin = 0, ClampMin = 0.f, EditCondition = "bApplyRelaxation"))` — Scale the displacement applied to separate spheres
- L953 _private member_ `bool bCorrectAgainstSurface = true;` — `UPROPERTY(EditAnywhere, Category = "Relaxation", meta = (DisplayName = "Correct against Isosurface", EditCondition = "bApplyRelaxation"))` — Move spheres so their distance from the isosurface equals to DistanceThreshold
- L957 _private member_ `float DistanceThreshold = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Relaxation", meta = (DataflowInput, ClampMin = 0.f, EditCondition = "bApplyRelaxation && bCorrectAgainstSurface"))` — Amount allowed of a sphere to be outside of the isosurface
- L961 _private member_ `TArray<FSphere> Spheres;` — `UPROPERTY(meta = (DataflowOutput))` — Output spheres
- L963 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L966 _public prototype_ `FVolumeToSpheresWithRelaxationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L969 _namespace_ `namespace UE`
- L969 _namespace_ `namespace Dataflow` (scope `UE`)
- L971 _prototype_ `void RegisterVolumeNodes();` (scope `UE::Dataflow`)

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeNodes/Private/Dataflow/DataflowVolumeNodesPlugin.h` (Private)


#### class `IDataflowVolumetricPlugin`  
`class IDataflowVolumetricPlugin : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`

### `Plugins/DataflowVolumetricPlugin/Source/DataflowVolumeNodes/Private/Dataflow/DataflowVolumeRenderableType.h` (Private)


#### class `UDataflowVolumeRenderSettings`  
`class UDataflowVolumeRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-28_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "Surface|ConstantColor, Surface|RandomColor, Surface|ColorBySize")`
- inherits: `UDataflowRenderableTypeSettings`
- L16 _public prototype_ `UDataflowVolumeRenderSettings();`
- L19 _public member_ `FDataflowColorCommonRenderSettings ColorSettings;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (ShowOnlyInnerProperties))`
- L23 _public member_ `float IsoValue = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (UIMin = -3, UIMax = 3))` — Voxels to display the volume gets generated at the Isovalue
- L27 _public member_ `float VoxelScale = .75f;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (UIMin = 0.001f, ClampMin = 0.001f, UIMax = 1.f, ClampMax = 1.f))` — Scale applied to display the voxels

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Dataflow` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L32 _prototype_ `void RegisterVolumeRenderableTypes();` (scope `UE::Dataflow::Private`)
