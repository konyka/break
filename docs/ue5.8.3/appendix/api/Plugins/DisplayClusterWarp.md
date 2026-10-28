# Plugins / DisplayClusterWarp

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp`
- headers: 31; symbols: 534
- symbol kinds: class=22, delegate=3, enum=11, enumerator=37, function=90, member=166, namespace=11, prototype=167, struct=21, variable=6
- PrivateDependencyModuleNames: DisplayCluster, ProceduralMeshComponent, RHI, RenderCore, Renderer, ScalableMPCDI, UnrealEd
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, DisplayCluster, Engine, Projects

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/DisplayClusterWarpLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterWarp, Log, All);` — Plugin-wide log categories
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterWarp, Log, All);` — Plugin-wide log categories
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterWarpBlend, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterWarpBlend, Log, All);`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterWarpInFrustumFitPolicy, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterWarpInFrustumFitPolicy, Log, All);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/DisplayClusterWarpModule.h` (Private)


#### class `FDisplayClusterWarpModule`  
`class FDisplayClusterWarpModule : public IDisplayClusterWarp`  
_L13-61_
- inherits: `IDisplayClusterWarp`
- desc: Implement DisplayClusterWarp module
- L17 _public prototype_ `FDisplayClusterWarpModule();`
- L18 _public prototype_ `virtual ~FDisplayClusterWarpModule();`
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public function_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_MPCDIFile& InConstructParameters) const override`
- L33 _public function_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_MPCDIFile_Profile2DScreen& InConstructParameters) const override`
- L38 _public function_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_PFMFile& InConstructParameters) const override`
- L43 _public function_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_StaticMesh& InConstructParameters) const override`
- L48 _public function_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_ProceduralMesh& InConstructParameters) const override`
- L53 _public function_ `virtual bool ReadMPCDFileStructure(const FString& InMPCDIFileName, TMap<FString, TMap<FString, FDisplayClusterWarpMPCDIAttributes>>& OutMPCDIFileStructure) const override`
- L60 _private member_ `TMap<FString, TSharedPtr<IDisplayClusterWarpPolicyFactory>> WarpPolicyFactories;` — Available factories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/PDisplayClusterWarpStrings.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DisplayClusterWarpStrings` (scope `UE`)
- L9 _namespace_ `namespace InFrustumFit` (scope `UE::DisplayClusterWarpStrings`)
- L11 _namespace_ `namespace material` (scope `UE::DisplayClusterWarpStrings::InFrustumFit`)
- L13 _variable_ `static constexpr const TCHAR* Name = TEXT("/nD` (scope `UE::DisplayClusterWarpStrings::InFrustumFit::material`)
- L15 _namespace_ `namespace attr` (scope `UE::DisplayClusterWarpStrings::InFrustumFit::material`)
- L17 _variable_ `static constexpr const TCHAR* GlobalScale = TEXT("Glo` (scope `UE::DisplayClusterWarpStrings::InFrustumFit::material::attr`)
- L18 _variable_ `static constexpr const TCHAR* GlobalForward = TEXT("Glo` (scope `UE::DisplayClusterWarpStrings::InFrustumFit::material::attr`)
- L19 _variable_ `static constexpr const TCHAR* GlobalRight = TEXT("Glo` (scope `UE::DisplayClusterWarpStrings::InFrustumFit::material::attr`)
- L20 _variable_ `static constexpr const TCHAR* GlobalUp = TEXT("Glo` (scope `UE::DisplayClusterWarpStrings::InFrustumFit::material::attr`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/Policy/DisplayClusterWarpPolicyBase.h` (Private)


#### class `FDisplayClusterWarpPolicyBase`  
`class FDisplayClusterWarpPolicyBase : public IDisplayClusterWarpPolicy , public TSharedFromThis<FDisplayClusterWarpPolicyBase, ESPMode::ThreadSafe>`  
_L13-39_
- inherits: `IDisplayClusterWarpPolicy,TSharedFromThis<FDisplayClusterWarpPolicyBase,ESPMode::ThreadSafe>`
- desc: Base warp policy
- L18 _public prototype_ `FDisplayClusterWarpPolicyBase(const FString& InType, const FString& InWarpPolicyName);`
- L20 _public function_ `virtual TSharedPtr<IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> ToSharedPtr() override`
- L25 _public function_ `virtual TSharedPtr<const IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L31 _public function_ `virtual const FString& GetId() const override`
- L38 _private member_ `const FString PolicyInstanceId;` — unique name

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/Policy/InFrustumFit/DisplayClusterWarpInFrustumFitPolicy.h` (Private)


#### class `FDisplayClusterWarpInFrustumFitPolicy`  
`class FDisplayClusterWarpInFrustumFitPolicy : public FDisplayClusterWarpPolicyBase`  
_L18-125_
- inherits: `FDisplayClusterWarpPolicyBase`
- desc: InFrustumFit warp policy
- L22 _public prototype_ `FDisplayClusterWarpInFrustumFitPolicy(const FString& InWarpPolicyName);`
- L26 _public prototype_ `virtual const FString& GetType() const override;`
- L27 _public prototype_ `virtual void HandleNewFrame(const TArray<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports) override;`
- L28 _public prototype_ `virtual void Tick(IDisplayClusterViewportManager* InViewportManager, float DeltaSeconds) override;`
- L30 _public prototype_ `virtual void BeginCalcFrustum(IDisplayClusterViewport* InViewport, const uint32 ContextNum) override;`
- L31 _public prototype_ `virtual void EndCalcFrustum(IDisplayClusterViewport* InViewport, const uint32 ContextNum) override;`
- L33 _public prototype_ `virtual bool HasPreviewEditableMesh(IDisplayClusterViewport* InViewport) override;`
- L35 _public prototype_ `virtual void OnUpdateDisplayDeviceMeshAndMaterialInstance(IDisplayClusterViewportPreview& InViewportPreview, const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType, UMeshComponent* InMeshComponent, UMaterialInstanceDynamic* InMeshMaterialInstance) const override;`
- L40 _private prototype_ `FDisplayClusterWarpProjection ApplyInFrustumFit(IDisplayClusterViewport* InViewport, const FTransform& World2OriginTransform, const FDisplayClusterWarpProjection& InWarpProjection) const;` — Apply frustum fit to the specified warp projection
- L43 _private prototype_ `FVector2D FindFrustumFit(const EDisplayClusterWarpCameraProjectionMode InProjectionMode, const FVector2D& InCameraFOV, const FVector2D& InGeometryFOV) const;` — Find final projection scale.
- L46 _private prototype_ `bool GetWarpBlendAPI(IDisplayClusterViewport* InViewport, const uint32 ContextNum, TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe>& OutWarpBlend, TObjectPtr<UDisplayClusterInFrustumFitCameraComponent>& OutConfigurationCameraComponent) const;` — Return true, if this viewport context can be processed.
- L49 _private prototype_ `bool CalcUnitedGeometryWorldAABBox(const TArray<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports, const float WorldScale, FDisplayClusterWarpAABB& OutUnitedGeometryWorldAABBox) const;` — Calculate united AABB for group of viewports:
- L58 _private prototype_ `bool CalcUnitedGeometryFrustum(const TArray<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports, const int32 InContextNum, const float WorldScale, FDisplayClusterWarpProjection& OutUnitedGeometryWarpProjection);` — Calculate united geometry frustum for group of viewports @param InViewports - viewports with warp geometry @param InContextNum - context number (i.e., eye index) @param WorldScale - world scale @param OutUnitedGeometryWarpProjection (out) calculated
- L102 _private prototype_ `bool CalcUnitedGeometrySymmetricFrustum(const TArray<TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>>& InViewports, const int32 InContextNum, FSymmetricFrustumData& InOutSymmetricFrustumData);` — Calculate united symmetric frustum for group of viewports: @param InViewports - viewports with warp geometry @param InContextNum - context number (i.e., eye index) @param InOutSymmetricFrustumData - (in, out) data used by the iteration step logic.
- L107 _private prototype_ `void DrawDebugGroupBoundingBox(ADisplayClusterRootActor* RootActor, const FLinearColor& Color);` — Renders a debug visualization for the group bounding box
- L110 _private prototype_ `void DrawDebugGroupFrustum(ADisplayClusterRootActor* RootActor, UDisplayClusterInFrustumFitCameraComponent* CameraComponent, const FLinearColor& Color);` — Renders a debug visualization for the group frustum
- L115 _private member_ `TOptional<FDisplayClusterWarpProjection> OptUnitedGeometryWarpProjection;` — Warp projection data
- L119 _private member_ `TOptional<FDisplayClusterWarpAABB> OptUnitedGeometryWorldAABB;` — United geometry AABB (The world space is used because each viewport can use its own origin.)
- L124 _private member_ `TOptional<FVector> OptOverrideWorldViewTarget;` — The view target position (world space). This value is used to obtain the direction of view and to build the "projection plane". (The world space is used because each viewport can use its own origin.)

#### struct `FDisplayClusterWarpInFrustumFitPolicy::FSymmetricFrustumData`  
`struct FSymmetricFrustumData`  
_L62-93_
- desc: Auxiliary container for the CalcUnitedGeometrySymmetricFrustum() function.
- L64 _public function_ `FSymmetricFrustumData(const float InWorldScale, const FTransform& InCameraComponent2WorldTransform) : WorldScale(InWorldScale), CameraComponent2WorldTransform(InCameraComponent2WorldTransform)`
- L70 _public member_ `const float WorldScale;` — World scale value
- L73 _public member_ `const FTransform CameraComponent2WorldTransform;` — Transform from the FrustumFit component space to the world space.
- L82 _public member_ `int32 IterationNum = 0;` — Index of the current iteration. Used to stop the search when the maximum number of iterations is reached. Note: The united geometry frustum is built from geometric points projected onto a special plane. This plane is called the 'projection plane' and is created from two quantities: the view direction vector and the eye position. Therefore, when we change the view direction vector, it leads to a change in the "projection plane" and, then, to new frustum values. When we set out to create a symmetrical frustum, we need to solve this math problem. An easy way is to do this in a few iterations and stop when we find a suitable view direction that provides a nearly symmetrical frustum with acceptable precision.
- L85 _public member_ `TOptional<FDisplayClusterWarpProjection> NewUnitedSymmetricWarpProjection;` — United symmetric WarpProjection
- L88 _public member_ `TOptional<FVector> NewWorldViewTarget;` — new location of the viewing target in the world space.
- L91 _public member_ `TOptional<TPair<double, FDisplayClusterWarpProjection>> BestSymmetricWarpProjection;` — Store the best symmetric projection, which is used when the iterative method has not found a projection within the expected precision.
- L92 _public member_ `TOptional<FVector> BestWorldViewTarget;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/Policy/InFrustumFit/DisplayClusterWarpInFrustumFitPolicyFactory.h` (Private)


#### class `FDisplayClusterWarpInFrustumFitPolicyFactory`  
`class FDisplayClusterWarpInFrustumFitPolicyFactory : public IDisplayClusterWarpPolicyFactory`  
_L9-17_
- inherits: `IDisplayClusterWarpPolicyFactory`
- desc: Implements warp policy factory for the 'InFrustumFit' policy
- L16 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> Create(const FString& InWarpPolicyType, const FString& InWarpPolicyName) override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/DisplayClusterWarpBlend.h` (Private)


#### class `FDisplayClusterWarpBlend`  
`class FDisplayClusterWarpBlend : public IDisplayClusterWarpBlend , public TSharedFromThis<FDisplayClusterWarpBlend, ESPMode::ThreadSafe>`  
_L13-116_
- inherits: `IDisplayClusterWarpBlend,TSharedFromThis<FDisplayClusterWarpBlend,ESPMode::ThreadSafe>`
- desc: WarpBlend interface implementation for MPCDI and mesh projection policies
- L18 _public prototype_ `FDisplayClusterWarpBlend();`
- L23 _public function_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> ToSharedPtr() override`
- L28 _public function_ `virtual TSharedPtr<const IDisplayClusterWarpBlend, ESPMode::ThreadSafe> ToSharedPtr() const override`
- L33 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) override;`
- L34 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewport* InViewport) override;`
- L36 _public prototype_ `virtual bool MarkWarpGeometryComponentDirty(const FName& InComponentName) override;`
- L38 _public prototype_ `virtual bool UpdateGeometryContext(const float InWorldScale) override;`
- L39 _public prototype_ `virtual const FDisplayClusterWarpGeometryContext& GetGeometryContext() const override;`
- L41 _public prototype_ `virtual bool CalcFrustumContext(const TSharedPtr<FDisplayClusterWarpEye, ESPMode::ThreadSafe>& InWarpEye) override;`
- L44 _public function_ `virtual class FRHITexture* GetTexture(EDisplayClusterWarpBlendTextureType TextureType) const override` — Get texture by type.
- L50 _public function_ `virtual TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> GetTextureInterface(EDisplayClusterWarpBlendTextureType InTextureType) const override`
- L55 _public function_ `virtual float GetAlphaMapEmbeddedGamma() const override`
- L60 _public function_ `virtual const IDisplayClusterRender_MeshComponentProxy* GetWarpMeshProxy_RenderThread() const override`
- L66 _public function_ `virtual EDisplayClusterWarpProfileType GetWarpProfileType() const override` — Return current warp profile type
- L71 _public function_ `virtual EDisplayClusterWarpGeometryType GetWarpGeometryType() const override`
- L76 _public function_ `virtual EDisplayClusterWarpFrustumGeometryType GetWarpFrustumGeometryType() const override`
- L81 _public function_ `virtual const FDisplayClusterWarpMPCDIAttributes& GetMPCDIAttributes() const override`
- L86 _public prototype_ `virtual bool ExportWarpMapGeometry(FDisplayClusterWarpGeometryOBJ& OutMeshData, uint32 InMaxDimension = 0) const override final;`
- L88 _public prototype_ `virtual bool ShouldSupportICVFX() const override;`
- L90 _public prototype_ `virtual FDisplayClusterWarpData& GetWarpData(const uint32 ContextNum) override;`
- L91 _public prototype_ `virtual const FDisplayClusterWarpData& GetWarpData(const uint32 ContextNum) const override;`
- L93 _public prototype_ `virtual UMeshComponent* GetOrCreatePreviewMeshComponent(IDisplayClusterViewport* InViewport, bool& bExistingComponent) const override;`
- L94 _public prototype_ `virtual UMeshComponent* GetOrCreatePreviewEditableMeshComponent(IDisplayClusterViewport* InViewport) const override;`
- L106 _private prototype_ `UMeshComponent* GetOrCreatePreviewMeshComponentImpl(IDisplayClusterViewport* InViewport, bool bEditableMesh, bool& bExistingComponent) const;` — Get or create a mesh component for previewing @param InViewport - The viewport that do this request @param bCreateCopy - true to always create a copy of the mesh @param bExistingComponent - (out) true if the mesh component is not a copy
- L109 _private prototype_ `void BeginCalcFrustum(const TSharedPtr<FDisplayClusterWarpEye, ESPMode::ThreadSafe>& InWarpEye);` — Begin frustum calc.
- L112 _public member_ `FDisplayClusterWarpBlend_GeometryContext GeometryContext;`
- L115 _private member_ `TArray<FDisplayClusterWarpData> WarpData;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/DisplayClusterWarpBlend_GeometryContext.h` (Private)


#### class `FDisplayClusterWarpBlend_GeometryContext`  
`class FDisplayClusterWarpBlend_GeometryContext`  
_L11-49_
- desc: Math context for Warp
- L14 _public function_ `FDisplayClusterWarpBlend_GeometryContext()`
- L17 _public function_ `~FDisplayClusterWarpBlend_GeometryContext()`
- L23 _public prototype_ `bool UpdateGeometryContext(const double InWorldScale);` — Update internal geometry context (AABB, matrices, etc)
- L26 _public prototype_ `FMatrix GetTextureMatrix() const;` — Get matrix for WarpMap texture.
- L29 _public prototype_ `FMatrix GetRegionMatrix() const;` — Obtaining a matrix for the area on the input texture (mpcdi 2d profile).
- L32 _public function_ `inline EDisplayClusterWarpProfileType GetWarpProfileType() const` — Returns the profile type used.
- L38 _public function_ `inline void SetWarpProfileType(const EDisplayClusterWarpProfileType InWarpProfileType)` — Assignment of the profile type to be used.
- L45 _public member_ `FDisplayClusterWarpBlend_GeometryProxy GeometryProxy;` — Geometry container
- L48 _public member_ `FDisplayClusterWarpGeometryContext Context;` — Geometry context

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/DisplayClusterWarpBlend_GeometryProxy.h` (Private)


#### class `FDisplayClusterWarpBlend_GeometryProxy`  
`class FDisplayClusterWarpBlend_GeometryProxy`  
_L16-125_
- desc: Geometry container for warp
- L19 _public function_ `FDisplayClusterWarpBlend_GeometryProxy()`
- L22 _public function_ `~FDisplayClusterWarpBlend_GeometryProxy()`
- L29 _public function_ `const TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> ImplGetTexture(EDisplayClusterWarpBlendTextureType TextureType) const` — Get texture resource by type.
- L48 _public prototype_ `bool MarkWarpFrustumGeometryComponentDirty(const FName& InComponentName);`
- L50 _public prototype_ `bool UpdateFrustumGeometry();`
- L51 _public prototype_ `bool UpdateFrustumGeometryLOD(const FIntPoint& InSizeLOD);`
- L53 _public prototype_ `const IDisplayClusterRender_MeshComponentProxy* GetWarpMeshProxy_RenderThread() const;`
- L55 _public prototype_ `const FStaticMeshLODResources* GetStaticMeshComponentLODResources() const;`
- L56 _public prototype_ `const FProcMeshSection* GetProceduralMeshComponentSection() const;`
- L59 _private prototype_ `bool ImplUpdateFrustumGeometry_WarpMesh();`
- L60 _private prototype_ `bool ImplUpdateFrustumGeometry_WarpProceduralMesh();`
- L61 _private prototype_ `bool ImplUpdateFrustumGeometry_WarpMap();`
- L62 _private prototype_ `bool ImplUpdateFrustumGeometry_MPCDIAttributes();`
- L65 _public member_ `bool bIsGeometryCacheValid = false;`
- L66 _public member_ `bool bIsGeometryValid = false;`
- L69 _public member_ `EDisplayClusterWarpGeometryType GeometryType = EDisplayClusterWarpGeometryType::Invalid;` — Geometry source for render
- L72 _public member_ `EDisplayClusterWarpFrustumGeometryType FrustumGeometryType = EDisplayClusterWarpFrustumGeometryType::Invalid;` — Geometry source for frustum
- L74 _public prototype_ `void ReleaseResources();`
- L78 _public member_ `FDisplayClusterWarpMPCDIAttributes MPCDIAttributes;` — MPCDI attributes
- L81 _public member_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> WarpMapTexture;` — Render resources:
- L82 _public member_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> AlphaMapTexture;`
- L83 _public member_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> BetaMapTexture;`
- L85 _public member_ `TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> WarpMeshComponent;`
- L86 _public member_ `FDisplayClusterSceneComponentRef PreviewMeshComponentRef;`
- L88 _public member_ `FDisplayClusterMeshUVs WarpMeshUVs;`
- L91 _public member_ `int32 StaticMeshComponentLODIndex = 0;` — for huge warp mesh geometry, change this value, and use LOD geometry in frustum math
- L92 _public member_ `int32 ProceduralMeshComponentSectionIndex = 0;`
- L94 _public member_ `float AlphaMapEmbeddedGamma = 1.f;`
- L97 _private member_ `bool bIsMeshComponentLost = false;`
- L100 _private prototype_ `bool ImplUpdateFrustumGeometryCache_WarpMesh();`
- L101 _private prototype_ `bool ImplUpdateFrustumGeometryCache_WarpProceduralMesh();`
- L102 _private prototype_ `bool ImplUpdateFrustumGeometryCache_WarpMap();`
- L103 _private prototype_ `bool ImplUpdateFrustumGeometryCache_MPCDIAttributes();`
- L105 _private function_ `inline EDisplayClusterWarpProfileType GetWarpProfileType() const`
- L124 _public member_ `FDisplayClusterWarpBlend_GeometryCache GeometryCache;`

#### class `FDisplayClusterWarpBlend_GeometryProxy::FDisplayClusterWarpBlend_GeometryCache`  
`class FDisplayClusterWarpBlend_GeometryCache`  
_L112-122_
- desc: Cached values for geometry (updated only if geometry changed)
- L115 _public member_ `FTransform GeometryToOrigin;`
- L117 _public member_ `FBox AABBox;`
- L118 _public member_ `FVector SurfaceViewNormal;`
- L119 _public member_ `FVector SurfaceViewPlane;`
- L121 _public member_ `TArray<int32> IndexLOD;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Exporter/DisplayClusterWarpBlendExporter_WarpMap.h` (Private)


#### class `FDisplayClusterWarpBlendExporter_WarpMap`  
`class FDisplayClusterWarpBlendExporter_WarpMap`  
_L8-19_
- desc: Auxiliary class for exporting WarpMap geometry.
- L15 _public prototype_ `static bool ExportWarpMap(const class FDisplayClusterWarpBlend_GeometryContext& InContext, struct FDisplayClusterWarpGeometryOBJ& Dst, uint32 InMaxDimension = 0);` — Exprot WarpMap texture geometry into the memory structure. For a 2D profile the geometry does not exist and is created based on the definition of <buffer> and <region>.
- L18 _public prototype_ `static void Get2DProfileGeometry(const struct FDisplayClusterWarpMPCDIAttributes& InMPCDIAttributes, TArray<FVector>& OutGeometryPoints, TArray<FVector>* OutNormal = nullptr, TArray<FVector2D>* OutUV = nullptr);` — [2D] Return fake geometry points for region in mpcdi 2D profile.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Loader/DisplayClusterWarpBlendLoader_MPCDI.h` (Private)


#### class `FDisplayClusterWarpBlendLoader_MPCDI`  
`class FDisplayClusterWarpBlendLoader_MPCDI`  
_L10-31_
- desc: An auxiliary class for creating the WarpBlend interface from initializing structures associated with MPCDI.
- L14 _public prototype_ `static TSharedPtr<FDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_MPCDIFile& InConstructParameters);` — Create WarpBlend interface from the MPCDI file.
- L17 _public prototype_ `static TSharedPtr<FDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_PFMFile& InConstructParameters);` — Create WarpBlend interface from the PFM file.
- L20 _public prototype_ `static TSharedPtr<FDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_MPCDIFile_Profile2DScreen& InConstructParameters);` — Create WarpBlend interface from MPCDI file and DisplayClusterScreen component.
- L30 _public prototype_ `static bool ReadMPCDFileStructure(const FString& InMPCDIFileName, TMap<FString, TMap<FString, FDisplayClusterWarpMPCDIAttributes>>& OutMPCDIFileStructure);` — Read MPCDI file structure @param InMPCDIFileName        - (in)  filename of the MPCDI file @param OutMPCDIFileStructure  - (out) readed mpcdi structure in format: TMap<BufferId, TArray<RegionId, MPCDIAttributes>> @return true if success

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Loader/DisplayClusterWarpBlendLoader_MPCDIFileLoader.h` (Private)


#### class `FDisplayClusterWarpBlendMPCDIFileLoader`  
`class FDisplayClusterWarpBlendMPCDIFileLoader`  
_L17-97_
- desc: Loader and container for mpcdi file.
- L20 _public prototype_ `FDisplayClusterWarpBlendMPCDIFileLoader(const FString& InUniqueName, const FString& InFilePath);`
- L21 _public prototype_ `~FDisplayClusterWarpBlendMPCDIFileLoader();`
- L25 _public function_ `const FString& GetName() const` — Get unique name of this file loader. Generated from file name.
- L38 _public prototype_ `bool FindRegion(const FString& InBufferName, const FString& InRegionId, mpcdi::Buffer*& OutBufferData, mpcdi::Region*& OutRegionData) const;` — Find MPCDI buffer and region by name. @param InBufferName - buffer name from the xml file inside the mpcdi file @param InRegionId - region name under the buffer name from the xml file inside the mpcdi file @param OutBufferData - (out) loaded buffer data @param OutRegionData - (out) loaded region data @return false if no buffer or region exists
- L47 _public prototype_ `bool ReadMPCDFileStructure(TMap<FString, TMap<FString, FDisplayClusterWarpMPCDIAttributes>>& OutMPCDIFileStructure);` — Read MPCDI file structure @param OutMPCDIFileStructure  - (out) readed mpcdi structure in format: TMap<BufferId, TArray<RegionId, MPCDIAttributes>> @return true if success
- L50 _public function_ `bool IsValid() const` — True if this data valid.
- L58 _public prototype_ `void LoadMPCDIAttributes(mpcdi::Buffer* mpcdiBuffer, mpcdi::Region* mpcdiRegion, FDisplayClusterWarpMPCDIAttributes& OutMPCDIAttributes) const;` — Load attributes
- L61 _public prototype_ `EDisplayClusterWarpProfileType GetProfileType() const;` — Get mpcdi profile type.
- L64 _public prototype_ `static FString GetFullPathToFile(const FString& InFilePath);` — Convert full file path from relative path to mpcdi files.
- L67 _public prototype_ `static TSharedPtr<FDisplayClusterWarpBlendMPCDIFileLoader, ESPMode::ThreadSafe> GetOrCreateCachedMPCDILoader(const FString& InFilePath);` — Get or create an MPCDI loader in the cache.
- L72 _public prototype_ `static int32 GetDataCacheTimeOutInFrames();` — Return DataCache timeout in frames.
- L75 _public prototype_ `static bool IsDataCacheEnabled();` — Return true if DataCache is enabled.
- L78 _public function_ `inline const FString& GetDataCacheName() const` — Returns the unique name of this MPCDI file resource for DataCache.
- L84 _public function_ `inline void ReleaseDataCacheItem()` — Method for releasing a cached data item, called before its destructor.
- L89 _protected prototype_ `void Release();`
- L93 _private member_ `const FString UniqueName;` — Unique name generated from the filename.
- L96 _private member_ `mpcdi::Profile* Profile = nullptr;` — loaded mpcdi data.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace mpcdi`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Loader/DisplayClusterWarpBlendLoader_MPCDIRegionLoader.h` (Private)


#### class `FDisplayClusterWarpBlendMPCDIRegionLoader`  
`class FDisplayClusterWarpBlendMPCDIRegionLoader`  
_L18-75_
- desc: MPCDI region loader. Creates the IDisplayClusterWarpBlend interface.
- L21 _public prototype_ `FDisplayClusterWarpBlendMPCDIRegionLoader() = default;`
- L22 _public function_ `~FDisplayClusterWarpBlendMPCDIRegionLoader()`
- L29 _public prototype_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> CreateTextureFromDataMap(const FString& InUniqueTextureName, mpcdi::DataMap* InDataMap);` — Creates a WarpMap texture from the DataMap.
- L32 _public prototype_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> CreateTextureFromGeometry(const FString& InUniqueTextureName, mpcdi::GeometryWarpFile* InGeometryWarp);` — Creates a WarpMap texture from the GeometryWarp.
- L35 _public prototype_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> CreateTextureFromPFMFile(const FString& InPFMFile, float PFMScale, bool bIsUnrealGameSpace);` — Creates a WarpMap texture from the PFM file.
- L40 _public prototype_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> CreateTextureFromFile(const FString& InFileName);` — Creates a texture from the file. Supported image formats: PNG.
- L45 _public prototype_ `bool LoadRegionFromMPCDIFile(const FString& InFilePath, const FString& InBufferName, const FString& InRegionName);` — Load region data from the MPCDI file into the internal data of this class.
- L51 _public prototype_ `TSharedPtr<FDisplayClusterWarpBlend, ESPMode::ThreadSafe> CreateWarpBlendInterface();` — Creates the WarpBlend interface from the internal data of this class. This function should be called at the end when all internal data is initialized.
- L55 _private prototype_ `void ReleaseResources();` — Release internal resources.
- L57 _private function_ `inline EDisplayClusterWarpProfileType GetWarpProfileType() const`
- L64 _public member_ `FDisplayClusterWarpMPCDIAttributes MPCDIAttributes;` — mpcdi attributes from xml
- L67 _public member_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> WarpMap;` — WarpMap texture (required)
- L70 _public member_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> AlphaMap;` — ALphaMap texture
- L71 _public member_ `float AlphaMapGammaEmbedded = 1.f;`
- L74 _public member_ `TSharedPtr<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> BetaMap;` — BetaMap texture

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace mpcdi`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Loader/DisplayClusterWarpBlendLoader_MeshComponent.h` (Private)


#### class `FDisplayClusterWarpBlendLoader_MeshComponent`  
`class FDisplayClusterWarpBlendLoader_MeshComponent`  
_L12-23_
- desc: An auxiliary class for creating the WarpBlend interface from initializing structures associated with UE components.
- L16 _public prototype_ `static TSharedPtr<IDisplayClusterRender_MeshComponent, ESPMode::ThreadSafe> CreateMeshComponent();` — Create mesh component instance.
- L19 _public prototype_ `static TSharedPtr<FDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_StaticMesh& InConstructParameters);` — Create WarpBlend interface from the StaticMesh component.
- L22 _public prototype_ `static TSharedPtr<FDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_ProceduralMesh& InConstructParameters);` — Create WarpBlend interface from the ProceduralMesh component.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Loader/DisplayClusterWarpBlendLoader_WarpMap.h` (Private)


#### class `FDisplayClusterWarpBlendLoader`  
`class FDisplayClusterWarpBlendLoader`  
_L15-77_
- desc: WarpMap data loader.
- L18 _public prototype_ `FDisplayClusterWarpBlendLoader() = default;`
- L19 _public prototype_ `~FDisplayClusterWarpBlendLoader();`
- L23 _public function_ `int32 GetWidth() const` — Get the width of the WarpMap.
- L29 _public function_ `int32 GetHeight() const` — Get the height of the WarpMap.
- L35 _public function_ `const FVector4f* GetWarpData() const` — Get a pointer to WarpMap data.
- L41 _public prototype_ `bool LoadFromGeometryWarpFile(const EDisplayClusterWarpProfileType InProfileType, mpcdi::GeometryWarpFile* SourceWarpMap);` — Load WarpMap from GeometryWarpFile structure.
- L44 _public prototype_ `bool LoadFromPoint(const EDisplayClusterWarpProfileType InProfileType, const TArray<FVector>& InPoints, int32 WarpX, int32 WarpY, float WorldScale, bool bIsUnrealGameSpace);` — Load WarpMap from points.
- L47 _public prototype_ `bool LoadFromPFM(const EDisplayClusterWarpProfileType InProfileType, mpcdi::PFM* SourcePFM, float PFMScale, bool bIsUnrealGameSpace);` — Load WarpMap from PFM structure.
- L51 _protected prototype_ `bool InitializeWarpDataImpl(int32 InWidth, int32 InHeight);` — Initializes WarpData and returns true if successful.
- L54 _protected prototype_ `void LoadGeometryImpl(EDisplayClusterWarpProfileType ProfileType, const TArray<FVector>& InPoints, float WorldScale, bool bIsUnrealGameSpace);` — Load data from points with scaling and space conversion.
- L57 _protected prototype_ `bool Is3DPointValid(int32 X, int32 Y) const;` — Returns true if this point can be used in the warp.
- L63 _protected prototype_ `void ClearNoise(const EDisplayClusterWarpProfileType InProfileType);` — Helper: The calibration data is not perfect and contains noise. This function deletes disconnected point areas. Useful for large warp nets.
- L66 _protected prototype_ `int32 ClearNoiseImpl(const FIntPoint& SearchLen, const FIntPoint& RemoveRule);` — Implementation of the ClearNoice().
- L70 _protected member_ `int32 Width = 0;` — Width of the WarpData
- L73 _protected member_ `int32 Height = 0;` — Height of the WarpData
- L76 _protected member_ `FVector4f* WarpData = nullptr;` — WarpData

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace mpcdi`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Math/DisplayClusterWarpBlendMath_Frustum.h` (Private)


#### class `FDisplayClusterWarpBlendMath_Frustum`  
`class FDisplayClusterWarpBlendMath_Frustum`  
_L13-132_
- desc: The WarpBlend math implementation.
- L16 _public prototype_ `FDisplayClusterWarpBlendMath_Frustum(FDisplayClusterWarpData& InWarpData, FDisplayClusterWarpBlend_GeometryContext& InGeometryContext);`
- L20 _public prototype_ `bool CalcFrustum();` — Entry point.
- L24 _private prototype_ `bool CalcFrustum2D();` — Math for mpcdi 2D profile.
- L27 _private prototype_ `bool CalcFrustum3D();` — Math for mpcdi 3D profile.
- L30 _private prototype_ `bool CalcFrustumA3D();` — Math for mpcdi A3D profile.
- L33 _private prototype_ `bool CalcFrustumSL();` — Math for mpcdi SL profile.
- L37 _protected prototype_ `FMatrix CalcProjectionMatrix(const FDisplayClusterWarpProjection& InWarpProjection);` — Calculate projection matrix from angles
- L40 _protected function_ `inline EDisplayClusterWarpProfileType GetWarpProfileType() const` — Get warp profile type.
- L46 _public function_ `inline void SetParameter(EDisplayClusterWarpBlendProjectionType InParameterValue)`
- L59 _private prototype_ `bool ShouldRotateFrustumToFitContextSize() const;`
- L61 _private function_ `inline bool ImplUpdateProjectionType()`
- L86 _private prototype_ `FMatrix GetUVMatrix(const FMatrix& InProjectionMatrix) const;`
- L88 _private prototype_ `bool ShouldUseCustomViewDirection() const;`
- L90 _private prototype_ `FVector GetViewTarget() const;`
- L93 _private prototype_ `FVector GetViewDirection();` — Get view direction.
- L96 _private prototype_ `void InitializeWarpProjectionData();` — Initialize warp projection data before search.
- L99 _private prototype_ `void ImplCalcViewProjectionMatrices();` — build projection plane matrices.
- L102 _private prototype_ `bool ImplCalcFrustumProjection();` — Frustum build logics:
- L103 _private prototype_ `bool ImplCalcFrustumProjection_AABB(const FMatrix& InGeometryToFrustumMatrix);`
- L104 _private prototype_ `bool ImplCalcFrustumProjection_WarpMap(const FMatrix& InGeometryToFrustumMatrix);`
- L105 _private prototype_ `bool ImplCalcFrustumProjection_WarpMesh(const FMatrix& InGeometryToFrustumMatrix);`
- L106 _private prototype_ `bool ImplCalcFrustumProjection_WarpProceduralMesh(const FMatrix& InGeometryToFrustumMatrix);`
- L107 _private prototype_ `bool ImplCalcFrustumProjection_MPCDIAttributes(const FMatrix& InGeometryToFrustumMatrix);`
- L109 _private prototype_ `bool EndCalcFrustum();`
- L113 _private prototype_ `bool ShouldHandleOverrideCalcFrustum() const;`
- L114 _private prototype_ `bool OverrideCalcFrustum();`
- L119 _private prototype_ `void ImplFitFrustumToContextSize();` — When necessary, rotates by 90 deg. the frustum to better fit the aspect ratio of the viewport.
- L122 _private prototype_ `static bool GetProjectionClip(const FVector4& InPoint, const FMatrix& InGeometryToFrustumA3D, FDisplayClusterWarpProjection& InOutWarpProjection);`
- L125 _private member_ `FDisplayClusterWarpBlend_GeometryContext& GeometryContext;`
- L128 _private member_ `FDisplayClusterWarpData& WarpData;` — context data
- L131 _private member_ `const int32 WarpMapLODRatio = 16;` — legacy WarpMap, now always use x16 downscale ratio

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Math/DisplayClusterWarpBlendMath_WarpMap.h` (Private)


#### class `FDisplayClusterWarpBlendMath_WarpMap`  
`class FDisplayClusterWarpBlendMath_WarpMap`  
_L12-287_
- desc: Implement math for WarpMap texture as a source of geometry
- L15 _public function_ `FDisplayClusterWarpBlendMath_WarpMap(const TSharedRef<IDisplayClusterRender_Texture, ESPMode::ThreadSafe>& InWarpMapTexture) : WarpMapTexture(InWarpMapTexture)`
- L20 _public function_ `inline bool CanBeUsed() const` — Check if WarpMap data can be used.
- L29 _public function_ `FBox GetAABBox() const` — Build a bbox from valid points.
- L50 _public function_ `bool BuildIndexLOD(const FIntPoint& InSizeLOD, TArray<int32>& OutIndexLOD)` — Build an LOD mesh with the size specified in InSizeLOD.
- L95 _private function_ `int32 GetSavedPointIndex()`
- L100 _private function_ `FORCEINLINE int32 GetPointIndex(int32 InX, int32 InY) const`
- L105 _private function_ `FORCEINLINE const FVector4f& GetPoint(int32 InX, int32 InY) const`
- L110 _private function_ `FORCEINLINE const FVector4f& GetPoint(int32 PointIndex) const`
- L115 _private function_ `bool IsValidPoint(int32 InX, int32 InY)`
- L120 _private function_ `bool FindValidPoint(int32 InX, int32 InY)`
- L137 _public function_ `FVector GetSurfaceViewNormal()`
- L186 _public function_ `FVector GetSurfaceViewPlane()`
- L204 _private function_ `const FVector4f& GetValidPoint(int32 InX, int32 InY)`
- L217 _private function_ `bool FindValidPointInRange(int32 Range)`
- L237 _private function_ `bool IsValid(int32 newX, int32 newY)`
- L260 _private function_ `inline const int32 GetWidth() const` — Return WarpMap texture width.
- L266 _private function_ `inline const int32 GetHeight() const` — Return WarpMap texture height.
- L272 _private function_ `inline const FVector4f* GetData() const` — Return WarpMap texture points data.
- L279 _private member_ `const TSharedRef<IDisplayClusterRender_Texture, ESPMode::ThreadSafe> WarpMapTexture;` — WarpMap texture reference
- L282 _private member_ `int32 ValidPointX = 0;` — Internal logic
- L283 _private member_ `int32 ValidPointY = 0;`
- L285 _private member_ `int32 X0 = 0;`
- L286 _private member_ `int32 Y0 = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Math/DisplayClusterWarpBlendMath_WarpMesh.h` (Private)


#### class `FDisplayClusterWarpBlendMath_WarpMesh`  
`class FDisplayClusterWarpBlendMath_WarpMesh`  
_L12-74_
- desc: Implement math for StaticMesh component as a source of geometry
- L15 _public function_ `FDisplayClusterWarpBlendMath_WarpMesh(const FStaticMeshLODResources& InMeshLODResources) : MeshLODResources(InMeshLODResources)`
- L20 _public function_ `FBox CalcAABBox()`
- L32 _public function_ `void CalcSurfaceVectors(FVector& OutSurfaceViewNormal, FVector& OutSurfaceViewPlane)`
- L73 _private member_ `const FStaticMeshLODResources& MeshLODResources;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Private/WarpBlend/Math/DisplayClusterWarpBlendMath_WarpProceduralMesh.h` (Private)


#### class `FDisplayClusterWarpBlendMath_WarpProceduralMesh`  
`class FDisplayClusterWarpBlendMath_WarpProceduralMesh`  
_L12-74_
- desc: Implement math for ProceduralMesh component as a source of geometry
- L15 _public function_ `FDisplayClusterWarpBlendMath_WarpProceduralMesh(const FProcMeshSection& InProcMeshSection) : ProcMeshSection(InProcMeshSection)`
- L20 _public function_ `FBox CalcAABBox()`
- L31 _public function_ `void CalcSurfaceVectors(FVector& OutSurfaceViewNormal, FVector& OutSurfaceViewPlane)`
- L73 _private member_ `const FProcMeshSection& ProcMeshSection;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Blueprints/DisplayClusterWarpBlueprint_Enums.h` (Public)


#### enum `EDisplayClusterWarpCameraProjectionMode`  
`enum class EDisplayClusterWarpCameraProjectionMode : uint8`  
_L16-23_
- reflection: `UENUM()`
- desc: Projection mode for the camera that is used as an image source This projection does not directly use slices from the camera image, but calculates the camera sub-frustum used to render the sub-images of camera for a particular viewport. Since the aspect ratio of the AABB geometry in the viewport cannot be equal to the aspect ratio of the camera, we must use several methods to fit the camera to the geometry.
- L19 _public enumerator_ `Fit UMETA(DisplayName = "Fit")` — Fit the stage geometry entirely within the camera's frustum
- L22 _public enumerator_ `Fill UMETA(DisplayName = "Fill")` — Fill the camera's frustum entire with the stage geometry

#### enum `EDisplayClusterWarpCameraViewTarget`  
`enum class EDisplayClusterWarpCameraViewTarget`  
_L27-34_
- reflection: `UENUM()`
- desc: A set of modes used to determine the view target of the stage's geometry frustum
- L30 _public enumerator_ `GeometricCenter UMETA(DisplayName = "Geometric Center")` — The camera will point in the direction of the geometric center of the stage's geometry
- L33 _public enumerator_ `MatchViewOrigin UMETA(DisplayName = "Match View Point")` — The camera will point in the same direction as the frustum fit view point.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Blueprints/DisplayClusterWarpGeometry.h` (Public)


#### struct `FDisplayClusterWarpGeometryPFM`  
`struct FDisplayClusterWarpGeometryPFM`  
_L12-28_
- reflection: `USTRUCT(BlueprintType, Category = "nDisplay|WarpGeometry")`
- desc: 3D geometry that can be used for warping, in an PFM-like format UE scale used: 1 unit = 1 centimeter
- L19 _public member_ `int32 Width = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay|WarpGeometry")` — Number of vertices horizontally.
- L23 _public member_ `int32 Height = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay|WarpGeometry")` — Number of vertices vertically.
- L27 _public member_ `TArray<FVector> Vertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay|WarpGeometry")` — An array with vertices. The total number of vertices in this array must be equal to Width*Height.

#### struct `FDisplayClusterWarpGeometryOBJ`  
`struct FDisplayClusterWarpGeometryOBJ`  
_L34-57_
- reflection: `USTRUCT(BlueprintType, Category = "nDisplay|WarpGeometry")`
- desc: 3D geometry that can be used for warping, in an OBJ-like format
- L39 _public prototype_ `void PostAddFace(int32 f0, int32 f1, int32 f2);`
- L44 _public member_ `TArray<FVector> Vertices;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay|WarpGeometry")` — Vertices of the mesh.
- L48 _public member_ `TArray<FVector> Normal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay|WarpGeometry")` — Normal of the vertices of the mesh.
- L52 _public member_ `TArray<FVector2D> UV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay|WarpGeometry")` — UV of the vertices of the mesh.
- L56 _public member_ `TArray<int32> Triangles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "nDisplay|WarpGeometry")` — Triangles with mesh vertex indices.

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Components/DisplayClusterInFrustumFitCameraComponent.h` (Public)


#### class `UDisplayClusterInFrustumFitCameraComponent`  
`class UDisplayClusterInFrustumFitCameraComponent : public UDisplayClusterCameraComponent`  
_L20-91_
- reflection: `UCLASS(ClassGroup = (DisplayCluster), meta = (BlueprintSpawnableComponent, DisplayName = "NDisplay Frustum Fit View Point"))`
- inherits: `UDisplayClusterCameraComponent`
- desc: 3D point in space used to project the camera view onto a group of nDisplay viewports. Support projection policies: mpcdi/pfm 2d/a3d, mesh.
- L25 _public prototype_ `UDisplayClusterInFrustumFitCameraComponent(const FObjectInitializer& ObjectInitializer);`
- L28 _public prototype_ `virtual void OnRegister() override;`
- L29 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L34 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _public prototype_ `virtual bool ShouldUseEntireClusterViewports(IDisplayClusterViewportManager* InViewportManager) const override;` — virtual void GetDesiredView(IDisplayClusterViewportConfiguration& InViewportConfiguration, FMinimalViewInfo& InOutViewInfo, float* OutCustomNearClippingPlane = nullptr) override;
- L42 _public prototype_ `virtual IDisplayClusterWarpPolicy* GetWarpPolicy(IDisplayClusterViewportManager* InViewportManager) override;`
- L44 _public prototype_ `virtual TObjectPtr<UMaterial> GetDisplayDeviceMaterial(const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType) const override;`
- L45 _public prototype_ `virtual void OnUpdateDisplayDeviceMeshAndMaterialInstance(IDisplayClusterViewportPreview& InViewportPreview, const EDisplayClusterDisplayDeviceMeshType InMeshType, const EDisplayClusterDisplayDeviceMaterialType InMaterialType, UMeshComponent* InMeshComponent, UMaterialInstanceDynamic* InMeshMaterialInstance) const override;`
- L47 _public prototype_ `virtual bool IsViewPointOverrideCameraPosition() const override;`
- L48 _public prototype_ `virtual void GetEyePosition(const IDisplayClusterViewportConfiguration& InViewportConfiguration, FVector& OutViewLocation, FRotator& OutViewRotation) override;`
- L51 _protected prototype_ `virtual bool IsICVFXCameraBeingUsed() const override;`
- L56 _public prototype_ `const UDisplayClusterInFrustumFitCameraComponent& GetConfigurationInFrustumFitCameraComponent(IDisplayClusterViewportConfiguration& InViewportConfiguration) const;` — Return component that used for configuration.
- L60 _private prototype_ `bool IsEnabled() const;` — true, if camera projection is used.
- L65 _public member_ `bool bEnableCameraProjection = true;` — `UPROPERTY(EditAnywhere, Category = "Frustum Fit", meta = (DisplayName = "Enable Frustum Fit"))` — Camera projection mode is used.
- L69 _public member_ `EDisplayClusterWarpCameraProjectionMode CameraProjectionMode = EDisplayClusterWarpCameraProjectionMode::Fit;` — `UPROPERTY(EditAnywhere, Category = "Frustum Fit", meta = (DisplayName = "Frustum Fit Mode", EditCondition = "bEnableCameraProjection", EditConditionHides))` — Enable special rendering mode for all viewports using this viewpoint.
- L73 _public member_ `EDisplayClusterWarpCameraViewTarget CameraViewTarget = EDisplayClusterWarpCameraViewTarget::GeometricCenter;` — `UPROPERTY(EditAnywhere, Category = "Frustum Fit", meta = (DisplayName = "Frustum Fit Target", EditCondition = "bEnableCameraProjection", EditConditionHides))` — Indicates which camera facing mode is used when frustum fitting the stage geometry
- L77 _public member_ `bool bShowPreviewFrustumFit = false;` — `UPROPERTY(EditAnywhere, Category = "Frustum Fit", meta = (DisplayName = "Show Frustum Fit Preview", EditCondition = "bEnableCameraProjection", EditConditionHides))` — Show additional warped preview meshes before the camera.
- L81 _public member_ `TSoftObjectPtr<ACineCameraActor> ExternalCameraActor;` — `UE_DEPRECATED(5.5, "Use the camera settings from the UDisplayClusterCameraComponent instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the Camera from the UDisplayClusterCameraComponent instead"))`
- L85 _public member_ `bool bUseCameraPostprocess = false;` — `UE_DEPRECATED(5.5, "Use the bEnablePostProcess from the UDisplayClusterCameraComponent instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the bEnablePostProcess from the UDisplayClusterCameraComponent instead"))`
- L90 _private member_ `TSharedPtr<IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> WarpPolicy;` — a unique type of warp policy for this component this policy class knows the properties of the component and implements the corresponding logic

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Containers/DisplayClusterWarpAABB.h` (Public)


#### struct `FDisplayClusterWarpAABB`  
`struct FDisplayClusterWarpAABB : public FBox`  
_L10-97_
- inherits: `FBox`
- desc: Implement AABB math
- L13 _public function_ `FDisplayClusterWarpAABB() : FBox(FVector(FLT_MAX, FLT_MAX, FLT_MAX), FVector(-FLT_MAX, -FLT_MAX, -FLT_MAX))`
- L19 _public function_ `template<typename FArg> inline void UpdateAABB(const FArg X, const FArg Y, const FArg Z)` — Expand the value in AABB with the new values.
- L31 _public function_ `inline void UpdateAABB(const FVector4f& InPts)` — Expand value in AABB with a new point.
- L40 _public function_ `inline void UpdateAABB(const FVector& InPts)`
- L46 _public function_ `inline void UpdateAABB(const TArray<FVector>& InPoints)` — Expand the value in AABB using the input point list.
- L55 _public function_ `inline void UpdateAABB(const FDisplayClusterWarpAABB& InAABB)` — Expand the value in AABB using the input AABB.
- L63 _public function_ `inline FVector GetAABBPts(const uint32 InPtsIndex) const` — The AABB defined by 8 points Get AABB 3d-cube points:

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Containers/DisplayClusterWarpContainers.h` (Public)


#### struct `FDisplayClusterWarpProjection`  
`struct FDisplayClusterWarpProjection`  
_L10-115_
- desc: Frustum projection angles.
- L12 _public function_ `inline void ResetProjectionAngles()`
- L20 _public function_ `inline bool IsValidProjection() const`
- L25 _public function_ `inline void ExpandProjectionAngles(const FDisplayClusterWarpProjection& In)`
- L36 _public function_ `inline void RotateProjectionAngles90Degree()`
- L49 _public function_ `inline double ConvertDegreesToProjection(double InAngle) const`
- L56 _public function_ `inline double ConvertProjectionToDegrees(double InProjectedAngle) const`
- L63 _public function_ `inline void ConvertProjectionAngles(const EDisplayClusterWarpAngleUnit InUnitType)`
- L94 _public member_ `EDisplayClusterWarpAngleUnit DataType = EDisplayClusterWarpAngleUnit::Default;` — Unit type for values
- L97 _public member_ `double Left = DBL_MAX;` — Projection angles
- L98 _public member_ `double Right = -DBL_MAX;`
- L99 _public member_ `double Top = -DBL_MAX;`
- L100 _public member_ `double Bottom = DBL_MAX;`
- L103 _public member_ `double ZNear = 1.f;` — Clipping planes
- L104 _public member_ `double ZFar = 1.f;`
- L107 _public member_ `double WorldScale = 1.f;` — Scale
- L110 _public member_ `FVector EyeLocation = FVector::ZeroVector;` — Warp projection ViewPoint
- L113 _public member_ `FRotator CameraRotation = FRotator::ZeroRotator;` — Camera ViewPoint
- L114 _public member_ `FVector CameraLocation = FVector::ZeroVector;`

#### struct `FDisplayClusterWarpViewPoint`  
`struct FDisplayClusterWarpViewPoint`  
_L120-141_
- desc: WarpBlend ViewPoint data
- L122 _public function_ `inline FVector GetEyeLocation() const`
- L127 _public function_ `inline bool IsEqual(const FDisplayClusterWarpViewPoint& InWarpViewPoint, float Precision) const`
- L134 _public member_ `FVector Location = FVector::ZeroVector;` — ViewPoint location
- L137 _public member_ `FVector EyeOffset = FVector::ZeroVector;` — Eye offset
- L140 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — ViewPoint rotation

#### struct `FDisplayClusterWarpMPCDIAttributes`  
`struct FDisplayClusterWarpMPCDIAttributes`  
_L146-268_
- desc: MPCDI attributes
- L149 _public member_ `EDisplayClusterWarpProfileType ProfileType = EDisplayClusterWarpProfileType::Invalid;` — MPCDI profile type
- L162 _public member_ `} Profile2DSettings;`
- L166 _public member_ `EDisplayClusterWarpMPCDIAttributesFlags Flags = EDisplayClusterWarpMPCDIAttributesFlags::None;` — Special flags
- L177 _public member_ `} Buffer;`
- L192 _public member_ `} Region;`
- L208 _public member_ `} Frustum;`
- L225 _public member_ `} CoordinateFrame;`
- L231 _public function_ `inline bool CalcProfile2DScreen(FVector& OutScreenPosition, FVector2D& OutScreenSize) const` — Calculates the position and screen size for a 2d profile. Returns true if the success.

#### struct `FDisplayClusterWarpMPCDIAttributes::FProfile2DSettings`  
`struct FProfile2DSettings`  
_L154-162_
- desc: Special settings for creating 3D geometry of the mpcdi 2D profile.
- L157 _public member_ `float DesiredFOV = 90.f;` — The focal length will be calculated for that FOV and the geometry will be shifted by that value.
- L160 _public member_ `float BufferPixelsToWorldUnits = 0.1f;` — The amount to scale an MPCDI buffer by when converting from pixels to world coordinates.

#### struct `FDisplayClusterWarpMPCDIAttributes::FBuffer`  
`struct FBuffer`  
_L169-177_
- desc: additional mpcdi attributes: <Buffer>
- L171 _public function_ `FBuffer() : Resolution(1024, 1024)`
- L175 _public member_ `FIntPoint Resolution;`

#### struct `FDisplayClusterWarpMPCDIAttributes::FRegion`  
`struct FRegion`  
_L180-192_
- desc: additional mpcdi attributes: <Region>
- L182 _public function_ `FRegion() : Resolution(1024, 1024) , Pos(0.0, 0.0) , Size(1.0, 1.0)`
- L188 _public member_ `FIntPoint Resolution;`
- L189 _public member_ `FVector2D Pos;`
- L190 _public member_ `FVector2D Size;`

#### struct `FDisplayClusterWarpMPCDIAttributes::FFrustum`  
`struct FFrustum`  
_L195-208_
- desc: additional mpcdi attributes <frustum>
- L197 _public function_ `FFrustum() : Rotator(FRotator::ZeroRotator) , Angles(FVector4::Zero())`
- L203 _public member_ `FRotator Rotator;` — Frustum direction
- L206 _public member_ `FVector4 Angles;` — Frustum angles XYZW = LRTB

#### struct `FDisplayClusterWarpMPCDIAttributes::FCoordinateFrame`  
`struct FCoordinateFrame`  
_L211-225_
- desc: additional mpcdi attributes <coordinateFrame>
- L213 _public function_ `FCoordinateFrame() : Pos(FVector::ZeroVector) , Yaw(FVector::ZeroVector) , Pitch(FVector::ZeroVector) , Roll(FVector::ZeroVector)`
- L220 _public member_ `FVector Pos;`
- L221 _public member_ `FVector Yaw;`
- L222 _public member_ `FVector Pitch;`
- L223 _public member_ `FVector Roll;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Containers/DisplayClusterWarpContext.h` (Public)


#### struct `FDisplayClusterWarpContext`  
`struct FDisplayClusterWarpContext`  
_L12-41_
- desc: Warp context
- L14 _public member_ `bool bIsValid = false;`
- L18 _public member_ `bool bFrustumRotated = false;` — Frustum has been rotated to fit the size of the context. This value contains the result of the ShouldRotateFrustumToFitContextSize() function.
- L21 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — Camera
- L22 _public member_ `FVector Location = FVector::ZeroVector;`
- L25 _public member_ `FMatrix GeometryProjectionMatrix = FMatrix::Identity;` — Frustum projection matrix
- L28 _public member_ `FMatrix ProjectionMatrix = FMatrix::Identity;` — Frustum projection matrix
- L31 _public member_ `FMatrix UVMatrix = FMatrix::Identity;` — From the texture's perspective
- L33 _public member_ `FMatrix TextureMatrix = FMatrix::Identity;`
- L34 _public member_ `FMatrix RegionMatrix = FMatrix::Identity;`
- L37 _public member_ `FMatrix MeshToStageMatrix = FMatrix::Identity;` — From the mesh local space to cave
- L40 _public member_ `FTransform Origin2WorldTransform = FTransform::Identity;` — Origin viewpoint transform to world space.

#### struct `FDisplayClusterWarpData`  
`struct FDisplayClusterWarpData`  
_L44-85_
- desc: Internal warp data for the one context of the viewport.
- L47 _public member_ `TSharedPtr<FDisplayClusterWarpEye, ESPMode::ThreadSafe> WarpEye;` — Input data from projection policy
- L50 _public member_ `FDisplayClusterWarpProjection GeometryWarpProjection;` — Warp projection data for geometry
- L53 _public member_ `FDisplayClusterWarpProjection WarpProjection;` — Warp projection for render
- L56 _public member_ `FDisplayClusterWarpContext WarpContext;` — Results
- L59 _public member_ `FMatrix Local2World = FMatrix::Identity;` — Projection plane matrices
- L62 _public member_ `double WorldScale = 1;` — Current world scale
- L66 _public member_ `bool bRotateFrustumToFitContextSize = false;` — Indicates if the frustum was rotated from base algorithm to better fit context size Used to implement hysteresis and avoid potential jumps back and forth.
- L69 _public member_ `bool bEnabledRotateFrustumToFitContextSize = true;` — Allows to use bRotateFrustumToFitContextSize
- L72 _public member_ `EDisplayClusterWarpBlendFrustumType FrustumType = EDisplayClusterWarpBlendFrustumType::AABB;` — Other warp settings:
- L73 _public member_ `EDisplayClusterWarpBlendStereoMode StereoMode = EDisplayClusterWarpBlendStereoMode::AsymmetricAABB;`
- L76 _public member_ `bool bFindBestProjectionType = false;` — Control projection type
- L77 _public member_ `EDisplayClusterWarpBlendProjectionType ProjectionType = EDisplayClusterWarpBlendProjectionType::DynamicAABBCenter;`
- L80 _public member_ `bool bValid = false;` — After successful warpdata calculation, this value is set to true.
- L84 _public member_ `bool bHasWarpPolicyChanges = false;` — The warp policy Tick() function uses warp data, and it must be sure that this data is updated in the previous frame. This value must be set to true from the EndCalcFrustum() warp policy function when changes are made to this structure.

#### struct `FDisplayClusterWarpGeometryContext`  
`struct FDisplayClusterWarpGeometryContext`  
_L87-105_
- L89 _public member_ `FMatrix GeometryToOrigin = FMatrix::Identity;`
- L92 _public member_ `FDisplayClusterWarpAABB AABBox;` — AABB of the warp geometry (in the space of the Origin component).
- L95 _public member_ `FVector SurfaceViewNormal;` — Static surface average normal for this region
- L98 _public member_ `FVector SurfaceViewPlane;` — Static surface average normal from 4 corner points
- L101 _public member_ `bool bGeometryChanged = false;` — Force update caches
- L104 _public member_ `bool bUseRegionMatrix = false;` — Allows you to use a matrix of regions (MPCDI 2D profile area defines a sub-rectangle of the input image to be cut and used for warp).

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Containers/DisplayClusterWarpEnums.h` (Public)


#### enum `EDisplayClusterWarpAngleUnit`  
`enum class EDisplayClusterWarpAngleUnit : uint8`  
_L9-16_
- desc: Angle values data type.
- L12 _public enumerator_ `Default = 0` — in projected space
- L15 _public enumerator_ `Degrees` — In degress 0..360

#### enum `EDisplayClusterWarpProfileType`  
`enum class EDisplayClusterWarpProfileType : uint8`  
_L21-33_
- desc: MPCDI profile type
- L24 _public enumerator_ `warp_2D = 0` — 2D mode
- L26 _public enumerator_ `warp_3D` — 3D mode (2D + static Frustum)
- L28 _public enumerator_ `warp_A3D` — Advanced 3D mode
- L30 _public enumerator_ `warp_SL` — Shader lamps
- L32 _public enumerator_ `Invalid`

#### enum `EDisplayClusterWarpGeometryType`  
`enum class EDisplayClusterWarpGeometryType : uint8`  
_L38-51_
- desc: Type of geometry source
- L41 _public enumerator_ `WarpMap = 0` — Use texture warpmap as geometry source
- L44 _public enumerator_ `WarpMesh` — Use mesh component as geometry source
- L47 _public enumerator_ `WarpProceduralMesh` — Use procedural mesh component as geometry source
- L50 _public enumerator_ `Invalid` — Undefined source

#### enum `EDisplayClusterWarpFrustumGeometryType`  
`enum class EDisplayClusterWarpFrustumGeometryType : uint8`  
_L56-72_
- desc: Type of frustum geometry source
- L59 _public enumerator_ `MPCDIAttributes = 0` — Use mpcdi attributes  to build virtual frustum geometry (profile 2D)
- L62 _public enumerator_ `WarpMap` — Use texture warpmap as frustum geometry source
- L65 _public enumerator_ `WarpMesh` — Use mesh component as frustum geometry source
- L68 _public enumerator_ `WarpProceduralMesh` — Use procedural mesh component as frustum geometry source
- L71 _public enumerator_ `Invalid` — Undefined source

#### enum `EDisplayClusterWarpBlendTextureType`  
`enum class EDisplayClusterWarpBlendTextureType :uint8`  
_L77-87_
- desc: The type of data stored in the texture (MPCDI or PFM only)
- L80 _public enumerator_ `WarpMap = 0` — Geometry data will be stored as a three-component (RGB) PFM file (Portable Float Map Format)
- L83 _public enumerator_ `AlphaMap` — Blend grayscale texture, color multiplier. Use in basic color correction: color = color * alpha;
- L86 _public enumerator_ `BetaMap` — Bate grayscale texture, for advanced collor correction. Use with AlphaMap: color = (color*alpha*(1 - beta)) + beta;

#### enum `EDisplayClusterWarpBlendFrustumType`  
`enum class EDisplayClusterWarpBlendFrustumType : uint8`  
_L92-102_
- desc: The method used to calc a frustum from geometric points
- L95 _public enumerator_ `AABB = 0` — Build frustum from 8 points of AABB
- L98 _public enumerator_ `FULL` — Build frustum from all geometry points
- L101 _public enumerator_ `LOD` — Performance: Build frustum from part of geometry (LOD)

#### enum `EDisplayClusterWarpBlendProjectionType`  
`enum class EDisplayClusterWarpBlendProjectionType : uint8`  
_L107-116_
- desc: Type of normal used to make the projection surface
- L109 _public enumerator_ `StaticSurfaceNormal = 0`
- L110 _public enumerator_ `StaticSurfacePlane`
- L111 _public enumerator_ `DynamicAABBCenter`
- L113 _public enumerator_ `RuntimeProjectionModes`
- L114 _public enumerator_ `RuntimeStaticSurfaceNormalInverted`
- L115 _public enumerator_ `RuntimeStaticSurfacePlaneInverted`

#### enum `EDisplayClusterWarpBlendStereoMode`  
`enum class EDisplayClusterWarpBlendStereoMode : uint8`  
_L121-125_
- desc: The method used to calculate a stereo projection
- L123 _public enumerator_ `AsymmetricAABB = 0`
- L124 _public enumerator_ `SymmetricAABB`

#### enum `EDisplayClusterWarpMPCDIAttributesFlags`  
`enum class EDisplayClusterWarpMPCDIAttributesFlags : uint8`  
_L130-139_
- desc: MPCDI attributes flags
- L132 _public enumerator_ `None = 0`
- L135 _public enumerator_ `HasFrustum = 1 << 0` — Frustum data defined
- L138 _public enumerator_ `HasCoordinateFrame = 1 << 1` — CoordinateFrame data defined

#### Free symbols / members of external scopes

- L140 _prototype_ `ENUM_CLASS_FLAGS(EDisplayClusterWarpMPCDIAttributesFlags);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Containers/DisplayClusterWarpEye.h` (Public)


#### class `FDisplayClusterWarpEye`  
`class FDisplayClusterWarpEye : public TSharedFromThis<FDisplayClusterWarpEye, ESPMode::ThreadSafe>`  
_L13-57_
- inherits: `TSharedFromThis<FDisplayClusterWarpEye,ESPMode::ThreadSafe>`
- desc: WarpBlend eye data
- L17 _public function_ `FDisplayClusterWarpEye(const TSharedPtr<IDisplayClusterViewport, ESPMode::ThreadSafe>& InViewport, const uint32 InContextNum) : ViewportWeakPtr(InViewport) , ContextNum(InContextNum)`
- L22 _public function_ `inline bool IsEqual(const FDisplayClusterWarpEye& InEye, float Precision) const`
- L32 _public function_ `inline IDisplayClusterViewport* GetViewport() const`
- L38 _public member_ `const TWeakPtr<IDisplayClusterViewport, ESPMode::ThreadSafe> ViewportWeakPtr;`
- L39 _public member_ `const uint32 ContextNum;`
- L41 _public member_ `FDisplayClusterWarpViewPoint ViewPoint;`
- L44 _public member_ `float WorldScale = 1.f;` — Current scene additional settings
- L47 _public member_ `FTransform World2LocalTransform;` — DCRA world2local
- L50 _public member_ `TSharedPtr<IDisplayClusterWarpPolicy, ESPMode::ThreadSafe> WarpPolicy;` — Warp policy
- L53 _public member_ `TOptional<FVector> OverrideViewTarget;` — (optional) this a view target point. By default used AABB center.
- L56 _public member_ `TOptional<FVector> OverrideViewDirection;` — (Optional) is the view direction (when this value is used, it also overrides the OverrideViewTarget parameter).

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/Containers/DisplayClusterWarpInitializer.h` (Public)


#### struct `FDisplayClusterWarpInitializer_MPCDIFile`  
`struct FDisplayClusterWarpInitializer_MPCDIFile`  
_L14-24_
- desc: Initialize WarpBlend from MPCDI file
- L17 _public member_ `FString MPCDIFileName;` — The file with MPCDI calibration data (extension of this file '.mpcdi')
- L20 _public member_ `FString BufferId;` — Name of buffer (mpcdi internal topology)
- L23 _public member_ `FString RegionId;` — Name of region (mpcdi internal topology)

#### struct `FDisplayClusterWarpInitializer_MPCDIFile_Profile2DScreen`  
`struct FDisplayClusterWarpInitializer_MPCDIFile_Profile2DScreen : public FDisplayClusterWarpInitializer_MPCDIFile`  
_L29-40_
- inherits: `FDisplayClusterWarpInitializer_MPCDIFile`
- desc: Initialize WarpBlend from MPCDI file and DisplayClusterScreen component
- L33 _public member_ `USceneComponent* OriginComponent = nullptr;` — Origin component ptr
- L36 _public member_ `UStaticMeshComponent* WarpMeshComponent = nullptr;` — StaticMesh component ptr (warp geometry data source)
- L39 _public member_ `UStaticMeshComponent* PreviewMeshComponent = nullptr;` — Preview StaticMesh component ptr (warp geometry data source)

#### struct `FDisplayClusterWarpInitializer_PFMFile`  
`struct FDisplayClusterWarpInitializer_PFMFile`  
_L45-67_
- desc: Initialize WarpBlend from PFM file
- L48 _public member_ `FString PFMFileName;` — The file with region calibration data (extension of this file '.pfm')
- L51 _public member_ `float PFMScale = 1.f;` — Geometry scale of this file to UE space (1 = 1 centemeter)
- L54 _public member_ `bool bIsUnrealGameSpace = false;` — Wrap axis to mpcdi space for unreal
- L57 _public member_ `FString AlphaMapFileName;` — AlphaMap file (supported format: PNG)
- L60 _public member_ `float AlphaMapEmbeddedAlpha = 0.f;` — Control alpha multiplier for AlphaMap texture
- L63 _public member_ `FString BetaMapFileName;` — BetaMap file (supported format: PNG)
- L66 _public member_ `FDisplayClusterWarpMPCDIAttributes MPCDIAttributes;` — Additional attributes from xml inside MPCDI file

#### struct `FDisplayClusterWarpInitializer_BaseMesh`  
`struct FDisplayClusterWarpInitializer_BaseMesh`  
_L72-80_
- desc: Base struct, not used as initialized
- L75 _public member_ `USceneComponent* OriginComponent = nullptr;` — Origin component ptr
- L78 _public member_ `int32 BaseUVIndex = INDEX_NONE;` — Map source mesh geometry UVs to WarpMesh UVs
- L79 _public member_ `int32 ChromakeyUVIndex = INDEX_NONE;`

#### struct `FDisplayClusterWarpInitializer_StaticMesh`  
`struct FDisplayClusterWarpInitializer_StaticMesh : public FDisplayClusterWarpInitializer_BaseMesh`  
_L85-96_
- inherits: `FDisplayClusterWarpInitializer_BaseMesh`
- desc: Initialize WarpBlend from static mesh component
- L89 _public member_ `UStaticMeshComponent* WarpMeshComponent = nullptr;` — StaticMesh component ptr (warp geometry data source)
- L92 _public member_ `UStaticMeshComponent* PreviewMeshComponent = nullptr;` — Preview StaticMesh component ptr (warp geometry data source)
- L95 _public member_ `int32 StaticMeshComponentLODIndex = 0;` — (optional) get geometry data from specified LOD index

#### struct `FDisplayClusterWarpInitializer_ProceduralMesh`  
`struct FDisplayClusterWarpInitializer_ProceduralMesh : public FDisplayClusterWarpInitializer_BaseMesh`  
_L101-112_
- inherits: `FDisplayClusterWarpInitializer_BaseMesh`
- desc: Initialize WarpBlend from procedural mesh component
- L105 _public member_ `UProceduralMeshComponent* WarpMeshComponent = nullptr;` — ProceduralMesh component ptr (warp geometry data source)
- L108 _public member_ `UProceduralMeshComponent* PreviewMeshComponent = nullptr;` — Preview ProceduralMesh component ptr (warp geometry data source)
- L111 _public member_ `int32 ProceduralMeshComponentSectionIndex = 0;` — (optional) get geometry data from specified SectionIndex

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/DisplayClusterWarpStrings.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace DisplayClusterWarpStrings` (scope `UE`)
- L9 _namespace_ `namespace warp` (scope `UE::DisplayClusterWarpStrings`)
- L11 _variable_ `static constexpr const TCHAR* InFrustumFit = TEXT("InF` (scope `UE::DisplayClusterWarpStrings::warp`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/IDisplayClusterWarp.h` (Public)


#### class `IDisplayClusterWarp`  
`class IDisplayClusterWarp : public IModuleInterface`  
_L11-78_
- inherits: `IModuleInterface`
- L14 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L17 _public prototype_ `virtual ~IDisplayClusterWarp() = default;`
- L26 _public function_ `static inline IDisplayClusterWarp& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L45 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_MPCDIFile& InConstructParameters) const = 0;` — Create new WarpBlend interface from MPCDI File
- L51 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_MPCDIFile_Profile2DScreen& InConstructParameters) const = 0;` — Create WarpBlend interface from MPCDI file and DisplayClusterScreen component
- L56 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_PFMFile& InConstructParameters) const = 0;` — Create new WarpBlend interface from PFM File
- L61 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_StaticMesh& InConstructParameters) const = 0;` — Create new WarpBlend interface from static mesh
- L66 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> Create(const FDisplayClusterWarpInitializer_ProceduralMesh& InConstructParameters) const = 0;` — Create new WarpBlend interface from procedural mesh
- L77 _public prototype_ `virtual bool ReadMPCDFileStructure(const FString& InMPCDIFileName, TMap<FString, TMap<FString, FDisplayClusterWarpMPCDIAttributes>>& OutMPCDIFileStructure) const = 0;` — Read MPCDI file structure (This function uses MPCDICachedLoader's internal implementation, which greatly reduces the load time of huge MPCDI files.) @param InMPCDIFileName        - (in)  filename of the MPCDI file @param OutMPCDIFileStructure  - (out) readed mpcdi structure in format: TMap<BufferId, TMap<RegionId, MPCDIAttributes>> @return true if success

### `Plugins/Runtime/nDisplay/Source/DisplayClusterWarp/Public/IDisplayClusterWarpBlend.h` (Public)


#### class `IDisplayClusterWarpBlend`  
`class IDisplayClusterWarpBlend`  
_L14-134_
- desc: WarpBlend interface for MPCDI and mesh projection policies
- L17 _public prototype_ `virtual ~IDisplayClusterWarpBlend() = default;`
- L21 _public prototype_ `virtual TSharedPtr<IDisplayClusterWarpBlend, ESPMode::ThreadSafe> ToSharedPtr() = 0;` — Get TSharedPtr from self.
- L22 _public prototype_ `virtual TSharedPtr<const IDisplayClusterWarpBlend, ESPMode::ThreadSafe> ToSharedPtr() const = 0;`
- L29 _public prototype_ `virtual bool HandleStartScene(IDisplayClusterViewport* InViewport) = 0;` — Called each time a new game level starts @param InViewport - a owner viewport
- L36 _public prototype_ `virtual void HandleEndScene(IDisplayClusterViewport* InViewport) = 0;` — Called when current level is going to be closed (i.e. before loading a new map) @param InViewport - a owner viewport
- L41 _public prototype_ `virtual bool UpdateGeometryContext(const float InWorldScale) = 0;` — Update internal geometry cached data
- L44 _public prototype_ `virtual const FDisplayClusterWarpGeometryContext& GetGeometryContext() const = 0;` — Get geometry context data.
- L53 _public prototype_ `virtual bool CalcFrustumContext(const TSharedPtr<FDisplayClusterWarpEye, ESPMode::ThreadSafe>& InWarpEye) = 0;` — Calculate warp context data for new eye @param InEye - Current eye and scene @return - true if the context calculated successfully
- L58 _public prototype_ `virtual class FRHITexture* GetTexture(EDisplayClusterWarpBlendTextureType InTextureType) const = 0;` — Access to resources by type
- L63 _public prototype_ `virtual TSharedPtr<class IDisplayClusterRender_Texture, ESPMode::ThreadSafe> GetTextureInterface(EDisplayClusterWarpBlendTextureType InTextureType) const = 0;` — Get texture interface by type
- L68 _public prototype_ `virtual float GetAlphaMapEmbeddedGamma() const = 0;` — Return AlphaMap embedded gamma value
- L73 _public prototype_ `virtual const class IDisplayClusterRender_MeshComponentProxy* GetWarpMeshProxy_RenderThread() const = 0;` — Get mesh proxy
- L78 _public prototype_ `virtual EDisplayClusterWarpProfileType GetWarpProfileType() const = 0;` — MPCDI profile type
- L83 _public prototype_ `virtual const FDisplayClusterWarpMPCDIAttributes& GetMPCDIAttributes() const = 0;` — Get MPCDI attributes (or their default values if they are not defined)
- L88 _public prototype_ `virtual EDisplayClusterWarpGeometryType GetWarpGeometryType() const = 0;` — Warp geometry type
- L93 _public prototype_ `virtual EDisplayClusterWarpFrustumGeometryType GetWarpFrustumGeometryType() const = 0;` — Warp frustum geometry type
- L98 _public prototype_ `virtual bool ExportWarpMapGeometry(struct FDisplayClusterWarpGeometryOBJ& OutMeshData, uint32 InMaxDimension = 0) const = 0;` — Export warp geometry to memory
- L107 _public prototype_ `virtual bool MarkWarpGeometryComponentDirty(const FName& InComponentName) = 0;` — Mark internal component ref as dirty for geometry update @param InComponentName - (optional) the name of the internal geometry ref component. Empty string for any component name @return - true, if there is a marked.
- L110 _public prototype_ `virtual bool ShouldSupportICVFX() const = 0;` — Return true, if this WarpBlend support ICVFX pipeline.
- L113 _public prototype_ `virtual FDisplayClusterWarpData& GetWarpData(const uint32 ContextNum) = 0;` — Get internal warp context data.
- L116 _public prototype_ `virtual const FDisplayClusterWarpData& GetWarpData(const uint32 ContextNum) const = 0;` — Get internal warp context data.
- L125 _public prototype_ `virtual UMeshComponent* GetOrCreatePreviewMeshComponent(IDisplayClusterViewport* InViewport, bool& bExistingComponent) const = 0;` — Get a mesh component with the geometry used for the warp blend. @param InViewport - The viewport with the projection policy to which the instance belongs @param bExistingComponent - true if the component already exists in the DCRA and does not need to be deleted externally. @return - ptr to the mesh component with the geometry, or nullptr in case of failure
- L133 _public prototype_ `virtual UMeshComponent* GetOrCreatePreviewEditableMeshComponent(IDisplayClusterViewport* InViewport) const = 0;` — Build preview editable mesh This MeshComponent is a copy of the preview mesh and can be moved freely with the UI visualization. @param InViewport - Projection specific parameters.
