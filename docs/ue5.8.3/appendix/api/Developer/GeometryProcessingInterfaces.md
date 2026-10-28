# Developer / GeometryProcessingInterfaces

- module root: `Source/Developer/GeometryProcessingInterfaces`
- headers: 6; symbols: 186
- symbol kinds: class=6, delegate=1, enum=13, enumerator=36, function=11, member=102, prototype=12, struct=5
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, GeometryCore

### `Source/Developer/GeometryProcessingInterfaces/Private/GeometryProcessingInterfacesModule.h` (Private)


#### class `FGeometryProcessingInterfacesModule`  
`class FGeometryProcessingInterfacesModule : public IGeometryProcessingInterfacesModule`  
_L17-39_
- inherits: `IGeometryProcessingInterfacesModule`
- desc: Implementation of IGeometryProcessingInterfacesModule (which extends the standard IModuleInterface) to provide access to various "Operation" interfaces
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `virtual IGeometryProcessing_ApproximateActors* GetApproximateActorsImplementation() override;` — @return implementation of IGeometryProcessing_ApproximateActors, if available, or nullptr (result is cached internally)
- L33 _public prototype_ `virtual IGeometryProcessing_MeshAutoUV* GetMeshAutoUVImplementation() override;` — @return implementation of IGeometryProcessing_MeshAutoUV, if available, or nullptr (result is cached internally)
- L36 _private member_ `IGeometryProcessing_ApproximateActors* ApproximateActors = nullptr;`
- L37 _private member_ `IGeometryProcessing_CombineMeshInstances* CombineMeshInstances = nullptr;`
- L38 _private member_ `IGeometryProcessing_MeshAutoUV* MeshAutoUV = nullptr;`

### `Source/Developer/GeometryProcessingInterfaces/Public/GeometryProcessingInterfaces/ApproximateActors.h` (Public)


#### class `IGeometryProcessing_ApproximateActors`  
`class IGeometryProcessing_ApproximateActors : public IModularFeature`  
_L31-336_
- inherits: `IModularFeature`
- desc: IGeometryProcessing_ApproximateActors is a generic high-level interface to a function/system that outputs a set of new Mesh assets that approximate a set of input Actors. This can be used to provide LOD-generation implementations for systems like ProxyLOD and HLOD. This is an IModularFeature, and so clients can query/enumerate the available ApproximateActors implementations based on the ::GetModularFeatureName(). However, the preferred way is to use code like the following: IGeometryProcessingInterfacesModule& GeomProcInterfaces = FModuleManager::Get().LoadModuleChecked<IGeometryProcessingInterfacesModule>("GeometryProcessingInterfaces"); IGeometryProcessing_ApproximateActors* ApproxActorsAPI = GeomProcInterfaces.GetApproximateActorsImplementation(); This will automatically determine which available implementation to use (based on any applicable config settings/etc), and cache the result of that decision.
- L34 _public prototype_ `virtual ~IGeometryProcessing_ApproximateActors() = default;`
- L310 _public function_ `virtual FOptions ConstructOptions(const FMeshApproximationSettings& MeshApproximationSettings)` — Construct an FOptions from the provided FMeshApproximationSettings.
- L319 _public function_ `virtual void ApproximateActors(const FInput& Input, const FOptions& Options, FResults& ResultsOut)` — Top-level driver function that clients call to generate the approximation for a set of input Actors or Components.
- L326 _public function_ `static const FName GetModularFeatureName()` — Modular feature name to register for retrieval during runtime
- L333 _public prototype_ `DECLARE_DELEGATE_OneParam(FApproximateActorsCompleteDelegate, FResults&);` — delegates to pass back info?
- L334 _public member_ `FApproximateActorsCompleteDelegate CompleteDelegate;`

#### enum `IGeometryProcessing_ApproximateActors::EMeshDataSourceLODPolicy`  
`enum class EMeshDataSourceLODPolicy`  
_L36-40_
- L38 _public enumerator_ `LOD0SourceMeshes`
- L39 _public enumerator_ `LOD0RenderMeshes`

#### enum `IGeometryProcessing_ApproximateActors::EApproximationPolicy`  
`enum class EApproximationPolicy`  
_L42-46_
- L44 _public enumerator_ `MeshAndGeneratedMaterial`
- L45 _public enumerator_ `CollisionMesh`

#### enum `IGeometryProcessing_ApproximateActors::EGroundPlanePolicy`  
`enum class EGroundPlanePolicy`  
_L48-52_
- L50 _public enumerator_ `NoGroundPlane = 0`
- L51 _public enumerator_ `FixedZHeightGroundPlane = 1`

#### enum `IGeometryProcessing_ApproximateActors::EGroundPlaneClippingPolicy`  
`enum class EGroundPlaneClippingPolicy`  
_L54-60_
- L56 _public enumerator_ `NoClipping = 0`
- L57 _public enumerator_ `DiscardFullyHiddenFaces = 1`
- L58 _public enumerator_ `CutFaces = 2`
- L59 _public enumerator_ `CutFacesAndFill = 3`

#### enum `IGeometryProcessing_ApproximateActors::EBaseCappingPolicy`  
`enum class EBaseCappingPolicy`  
_L62-67_
- L64 _public enumerator_ `NoBaseCapping = 0`
- L65 _public enumerator_ `ConvexPolygon = 1`
- L66 _public enumerator_ `ConvexSolid = 2`

#### enum `IGeometryProcessing_ApproximateActors::EOcclusionPolicy`  
`enum class EOcclusionPolicy : uint8`  
_L69-73_
- L71 _public enumerator_ `None = 0`
- L72 _public enumerator_ `VisibilityBased = 1`

#### enum `IGeometryProcessing_ApproximateActors::ESimplificationPolicy`  
`enum class ESimplificationPolicy`  
_L75-80_
- L77 _public enumerator_ `FixedTriangleCount = 0`
- L78 _public enumerator_ `TrianglesPerUnitSqMeter = 1`
- L79 _public enumerator_ `GeometricTolerance = 2`

#### enum `IGeometryProcessing_ApproximateActors::EUVGenerationPolicy`  
`enum class EUVGenerationPolicy : uint8`  
_L82-87_
- L84 _public enumerator_ `PreferUVAtlas = 0`
- L85 _public enumerator_ `PreferXAtlas = 1`
- L86 _public enumerator_ `PreferPatchBuilder = 2`

#### enum `IGeometryProcessing_ApproximateActors::ETextureSizePolicy`  
`enum class ETextureSizePolicy : uint8`  
_L89-94_
- L91 _public enumerator_ `TextureSize = 0`
- L92 _public enumerator_ `TexelDensity = 1`
- L93 _public enumerator_ `CustomTextureSize = 2`

#### enum `IGeometryProcessing_ApproximateActors::ENaniteFallbackTarget`  
`enum class ENaniteFallbackTarget : uint8`  
_L96-101_
- L98 _public enumerator_ `Auto`
- L99 _public enumerator_ `PercentTriangles`
- L100 _public enumerator_ `RelativeError`

#### struct `IGeometryProcessing_ApproximateActors::FInput`  
`struct FInput`  
_L106-110_
- desc: Input to approximate, as actors and/or components
- L108 _public member_ `TArray<AActor*> Actors;`
- L109 _public member_ `TArray<UActorComponent*> Components;`

#### struct `IGeometryProcessing_ApproximateActors::FOptions`  
`struct FOptions`  
_L116-281_
- desc: Input options to Actor Approximation process
- L119 _public member_ `FString BasePackagePath;` — Base path for generated assets. Names will be generated by appending strings to this path.
- L122 _public member_ `EApproximationPolicy BasePolicy = EApproximationPolicy::MeshAndGeneratedMaterial;` — high-level control of the overall approximation process
- L129 _public member_ `EMeshDataSourceLODPolicy MeshDataLODPolicy = EMeshDataSourceLODPolicy::LOD0SourceMeshes;` — control which LOD, and which type of LOD mesh, should be used as the source for the approximation process
- L134 _public member_ `bool bAutoThickenThinParts = false;` — Mesh Preprocessing settings
- L135 _public member_ `double AutoThickenThicknessMeters = 0.1;`
- L137 _public member_ `bool bIgnoreTinyParts = false;`
- L138 _public member_ `double TinyPartMaxDimensionMeters = 0.1;`
- L140 _public member_ `EBaseCappingPolicy BaseCappingPolicy = EBaseCappingPolicy::NoBaseCapping;`
- L141 _public member_ `double BaseThicknessOverrideMeters = 0.0;` — use this thickness for Solid. If zero, use AutoThickenThickness if bAutoThickenThinParts=true, otherwise use WorldSpaceApproximationAccuracyMeters
- L142 _public member_ `double BaseHeightOverrideMeters = 0.0;` — consider this height from MinZ as "base" region. If zero, use 2.0*WorldSpaceApproximationAccuracyMeters
- L149 _public member_ `double WorldSpaceApproximationAccuracyMeters = 1.0;` — Meshing settings (ie for voxelization)
- L150 _public member_ `int32 ClampVoxelDimension = 1024;`
- L152 _public member_ `double WindingThreshold = 0.5;`
- L154 _public member_ `bool bApplyMorphology = false;`
- L155 _public member_ `double MorphologyDistanceMeters = 0.1;`
- L157 _public member_ `EOcclusionPolicy OcclusionPolicy = EOcclusionPolicy::VisibilityBased;`
- L158 _public member_ `bool bAddDownwardFacesOccluder = true;`
- L160 _public member_ `ESimplificationPolicy MeshSimplificationPolicy = ESimplificationPolicy::FixedTriangleCount;`
- L161 _public member_ `int32 FixedTriangleCount = 5000;`
- L162 _public member_ `double SimplificationTargetMetric = 0.1;` — interpretation varies depending on MeshSimplificationPolicy
- L163 _public member_ `bool bEnableFastSimplifyPrePass = false;` — enable pre-simplify "fast-collapse" pass, using a relatively aggressive tolerance based on WorldSpaceApproximationAccuracyMeters
- L165 _public member_ `EGroundPlanePolicy GroundPlanePolicy = EGroundPlanePolicy::NoGroundPlane;`
- L166 _public member_ `double GroundPlaneZHeight = 0.0;`
- L168 _public member_ `EGroundPlaneClippingPolicy GroundPlaneClippingPolicy = EGroundPlaneClippingPolicy::NoClipping;`
- L170 _public member_ `bool bCalculateHardNormals = true;`
- L171 _public member_ `double HardNormalsAngleDeg = 60.0;`
- L173 _public member_ `EUVGenerationPolicy UVPolicy = EUVGenerationPolicy::PreferXAtlas;`
- L174 _public member_ `double UVAtlasStretchTarget = 0.1;`
- L175 _public member_ `int32 PatchBuilderInitialPatchCount = 250;`
- L176 _public member_ `double PatchBuilderCurvatureAlignment = 1.0;`
- L177 _public member_ `double PatchBuilderMergingThreshold = 1.5;`
- L178 _public member_ `double PatchBuilderMaxNormalDeviationDeg = 45.0;`
- L183 _public member_ `int32 RenderCaptureImageSize = 1024;` — Material approximation settings
- L186 _public member_ `double FieldOfViewDegrees = 45.0;` — render capture parameters
- L187 _public member_ `double NearPlaneDist = 1.0;`
- L189 _public member_ `bool bMaximizeBakeParallelism = true;` — if true, photocapture is computed at the same time as mesh generation. Faster but requires more memory.
- L196 _public member_ `UMaterialInterface* BakeMaterial = nullptr;` — A new MIC derived from this material will be created and assigned to the generated mesh
- L197 _public member_ `FName BaseColorTexParamName = FName("Bas`
- L198 _public member_ `FName BaseColorSwitchName = FName("Ena`
- L199 _public member_ `bool bBakeBaseColor = true;`
- L200 _public member_ `int32 CustomTextureSizeBaseColor = 1024;`
- L201 _public member_ `FName RoughnessTexParamName = FName("Rou`
- L202 _public member_ `FName RoughnessSwitchName = FName("Ena`
- L203 _public member_ `bool bBakeRoughness = true;`
- L204 _public member_ `int32 CustomTextureSizeRoughness = 1024;`
- L205 _public member_ `FName MetallicTexParamName = FName("Met`
- L206 _public member_ `FName MetallicSwitchName = FName("Ena`
- L207 _public member_ `bool bBakeMetallic = true;`
- L208 _public member_ `int32 CustomTextureSizeMetallic = 1024;`
- L209 _public member_ `FName SpecularTexParamName = FName("Spe`
- L210 _public member_ `FName SpecularSwitchName = FName("Ena`
- L211 _public member_ `bool bBakeSpecular = true;`
- L212 _public member_ `int32 CustomTextureSizeSpecular = 1024;`
- L213 _public member_ `FName EmissiveTexParamName = FName("Emi`
- L214 _public member_ `FName EmissiveSwitchName = FName("Ena`
- L215 _public member_ `bool bBakeEmissive = true;`
- L216 _public member_ `int32 CustomTextureSizeEmissive = 1024;`
- L217 _public member_ `FName NormalTexParamName = FName("Nor`
- L218 _public member_ `FName NormalSwitchName = FName("Ena`
- L219 _public member_ `bool bBakeNormalMap = true;`
- L220 _public member_ `int32 CustomTextureSizeNormalMap = 1024;`
- L222 _public member_ `bool bUsePackedMRS = true;`
- L223 _public member_ `FName PackedMRSTexParamName = FName("Pac`
- L224 _public member_ `FName PackedMRSSwitchName = FName("Ena`
- L227 _public member_ `ETextureSizePolicy TextureSizePolicy = ETextureSizePolicy::TextureSize;` — output texture options
- L228 _public member_ `int32 TextureImageSize = 1024;`
- L229 _public member_ `float MeshTexelDensity = 0;`
- L232 _public member_ `int32 AntiAliasMultiSampling = 0;` — supersampling parameter
- L240 _public member_ `bool bGenerateNaniteEnabledMesh = false;` — Whether to generate a nanite-enabled mesh
- L243 _public member_ `ENaniteFallbackTarget NaniteFallbackTarget = ENaniteFallbackTarget::Auto;` — Which heuristic to use when generating the fallback mesh.
- L246 _public member_ `float NaniteFallbackPercentTriangles = 1.0f;` — Percentage of triangles to keep from source mesh for fallback. 1.0 = no reduction, 0.0 = no triangles.
- L249 _public member_ `float NaniteFallbackRelativeError = 1.0f;` — Reduce until at least this amount of error is reached relative to size of the mesh
- L252 _public member_ `bool bSupportRayTracing = true;` — Whether ray tracing will be supported on this mesh. Disable this to save memory if the generated mesh will only be rendered in the distance
- L255 _public member_ `bool bAllowDistanceField = true;` — Whether to allow distance field to be computed for this mesh. Disable this to save memory if the generated mesh will only be rendered in the distance
- L258 _public member_ `bool bGenerateLightmapUVs = false;` — Whether to generate lightmap uvs for the merged mesh
- L261 _public member_ `bool bCreatePhysicsBody = true;` — Whether the UBodySetup on the Asset will be created
- L264 _public member_ `bool bBuildReversedIndexBuffer = true;` — Required to optimize mesh in mirrored transform. Double index buffer size.
- L271 _public member_ `bool bVerbose = false;` — print useful information to the Output Log
- L274 _public member_ `bool bWriteDebugMesh = false;` — create a flattened (ie non-instanced) mesh and save it with _DEBUG suffix. Warning often absolutely enormous!

#### enum `IGeometryProcessing_ApproximateActors::EResultCode`  
`enum class EResultCode`  
_L283-289_
- L285 _public enumerator_ `Success`
- L286 _public enumerator_ `MeshGenerationFailed`
- L287 _public enumerator_ `MaterialGenerationFailed`
- L288 _public enumerator_ `UnknownError`

#### struct `IGeometryProcessing_ApproximateActors::FResults`  
`struct FResults`  
_L294-305_
- desc: Outputs of an Actor Approximation process
- L296 _public member_ `EResultCode ResultCode = EResultCode::UnknownError;`
- L298 _public member_ `TArray<UStaticMesh*> NewMeshAssets;`
- L300 _public member_ `TArray<UMaterialInterface*> NewMaterials;`
- L302 _public member_ `TArray<UTexture2D*> NewTextures;`

#### Free symbols / members of external scopes

- L333 _delegate_ `DECLARE_DELEGATE_OneParam(FApproximateActorsCompleteDelegate, FResults&);` — delegates to pass back info?

### `Source/Developer/GeometryProcessingInterfaces/Public/GeometryProcessingInterfaces/IStaticMeshAssetEditorModularFeature.h` (Public)


#### class `IStaticMeshAssetEditorModularFeature`  
`class IStaticMeshAssetEditorModularFeature : public IModularFeature`  
_L12-33_
- inherits: `IModularFeature`
- desc: This interface acts as a connector to the (optional) Static Mesh Asset Editor plugin. If the plugin is available, then it can be retrieved via IModularFeatures::Get().GetModularFeatureImplementation or related methods.
- L15 _public function_ `virtual ~IStaticMeshAssetEditorModularFeature()`
- L17 _public function_ `virtual void LaunchStaticMeshAssetEditor(const TArray<TObjectPtr<UObject>>& Objects)`
- L22 _public function_ `virtual bool CanLaunchStaticMeshAssetEditor(const TArray<TObjectPtr<UObject>>& Objects)`
- L29 _public function_ `static const FName GetModularFeatureName()` — Modular feature name to register for retrieval during runtime

### `Source/Developer/GeometryProcessingInterfaces/Public/GeometryProcessingInterfaces/IUVEditorModularFeature.h` (Public)


#### class `IUVEditorModularFeature`  
`class IUVEditorModularFeature : public IModularFeature`  
_L12-33_
- inherits: `IModularFeature`
- desc: This interface acts as a connector to the (optional) UV Editor plugin. If the plugin is available, then it can be retrieved via IModularFeatures::Get().GetModularFeatureImplementation or related methods.
- L15 _public prototype_ `virtual ~IUVEditorModularFeature() = default;`
- L17 _public function_ `virtual void LaunchUVEditor(const TArray<TObjectPtr<UObject>>& Objects)`
- L22 _public function_ `virtual bool CanLaunchUVEditor(const TArray<TObjectPtr<UObject>>& Objects)`
- L29 _public function_ `static const FName GetModularFeatureName()` — Modular feature name to register for retrieval during runtime

### `Source/Developer/GeometryProcessingInterfaces/Public/GeometryProcessingInterfaces/MeshAutoUV.h` (Public)


#### class `IGeometryProcessing_MeshAutoUV`  
`class IGeometryProcessing_MeshAutoUV : public IModularFeature`  
_L17-72_
- inherits: `IModularFeature`
- desc: The CombineMeshInstances modular feature is used to provide a mechanism for merging a set of instances of meshes (ie mesh + transform + materials + ...) into a smaller set of meshes. Generally this involves creating simpler versions of the instances and appending them into one or a small number of combined meshes.
- L20 _public prototype_ `virtual ~IGeometryProcessing_MeshAutoUV() = default;`
- L63 _public prototype_ `virtual FOptions ConstructDefaultOptions() PURE_VIRTUAL(IGeometryProcessing_MeshAutoUV::ConstructDefaultOptions, return FOptions(); );`
- L65 _public prototype_ `virtual void GenerateUVs(FMeshDescription& InOutMesh, const FOptions& Options, FResults& ResultsOut) PURE_VIRTUAL(IGeometryProcessing_MeshAutoUV::GenerateUVs,);`
- L68 _public function_ `static const FName GetModularFeatureName()` — Modular feature name to register for retrieval during runtime

#### enum `IGeometryProcessing_MeshAutoUV::EAutoUVMethod`  
`enum class EAutoUVMethod : uint8`  
_L22-27_
- L24 _public enumerator_ `PatchBuilder = 0`
- L25 _public enumerator_ `UVAtlas = 1`
- L26 _public enumerator_ `XAtlas = 2`

#### struct `IGeometryProcessing_MeshAutoUV::FOptions`  
`struct FOptions`  
_L29-50_
- L31 _public member_ `EAutoUVMethod Method = EAutoUVMethod::PatchBuilder;`
- L34 _public member_ `double UVAtlasStretch = 0.11f;` — UVAtlas parameters
- L35 _public member_ `int UVAtlasNumCharts = 0;`
- L38 _public member_ `int XAtlasMaxIterations = 1;` — XAtlas parameters
- L41 _public member_ `int NumInitialPatches = 100;` — PatchBuilder parameters
- L42 _public member_ `double CurvatureAlignment = 1.0;`
- L43 _public member_ `double MergingThreshold = 1.5;`
- L44 _public member_ `double MaxAngleDeviationDeg = 45.0;`
- L45 _public member_ `int SmoothingSteps = 5;`
- L46 _public member_ `double SmoothingAlpha = 0.25;`
- L48 _public member_ `bool bAutoPack = true;`
- L49 _public member_ `int PackingTargetWidth = 512;`

#### enum `IGeometryProcessing_MeshAutoUV::EResultCode`  
`enum class EResultCode`  
_L52-56_
- L54 _public enumerator_ `Success`
- L55 _public enumerator_ `UnknownError`

#### struct `IGeometryProcessing_MeshAutoUV::FResults`  
`struct FResults`  
_L58-61_
- L60 _public member_ `EResultCode ResultCode = EResultCode::UnknownError;`

### `Source/Developer/GeometryProcessingInterfaces/Public/IGeometryProcessingInterfacesModule.h` (Public)


#### class `IGeometryProcessingInterfacesModule`  
`class IGeometryProcessingInterfacesModule : public IModuleInterface`  
_L25-38_
- inherits: `IModuleInterface`
- desc: Abstract interface to a Module that provides functions to access different "Operation" interfaces, which are high-level APIs to run complex geometry operations on engine inputs without the caller needing to know about the potential dependencies (ie, the implementations can be provided by plugins, and this non-plugin module can find them for the Engine/Editor core, avoiding the no-core-dependencies-on-plugins limitation) This interface is implemented by FGeometryProcessingInterfacesModule. Client code that wants access to the operations should get this interface like so: IGeometryProcessingInterfacesModule& GeomProcInterfaces = FModuleManager::Get().LoadModuleChecked<IGeometryProcessingInterfacesModule>("GeometryProcessingInterfaces");
- L31 _public prototype_ `virtual IGeometryProcessing_ApproximateActors* GetApproximateActorsImplementation() = 0;` — @return implementation of IGeometryProcessing_ApproximateActors, if available
- L36 _public prototype_ `virtual IGeometryProcessing_MeshAutoUV* GetMeshAutoUVImplementation() = 0;` — @return implementation of IGeometryProcessing_MeshAutoUV, if available, or nullptr (result is cached internally)
