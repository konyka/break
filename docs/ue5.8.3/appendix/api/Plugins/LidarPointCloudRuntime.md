# Plugins / LidarPointCloudRuntime

- module root: `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime`
- headers: 16; symbols: 1249
- symbol kinds: class=28, delegate=3, enum=7, enumerator=22, externvar=3, function=319, macro=43, member=360, namespace=3, prototype=429, struct=32
- PrivateDependencyModuleNames: AssetRegistry, ContentBrowser, Core, CoreUObject, EditorFramework, Engine, GeometryCore, InputCore, MeshConversion, MeshDescription, Projects, PropertyEditor, RHI, RenderCore, Slate, SlateCore, StaticMeshDescription, UnrealEd

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Private/LidarPointCloudOctreeMacros.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define FOR(ElemName, Node) for(FLidarPointCloudPoint* ElemName = Node->GetPersistentData(), *DataEnd##ElemName = ElemName + Node->GetNumPoints(); ElemName != DataEnd##ElemName; ++ElemName)`
- L6 _macro_ `#define FOR_RO(ElemName, Node) for(FLidarPointCloudPoint* ElemName = Node->GetData(), *DataEnd##ElemName = ElemName + Node->GetNumPoints(); ElemName != DataEnd##ElemName; ++ElemName)`
- L8 _macro_ `#define IS_VIS_CHECK_REQUIRED (bVisibleOnly && CurrentNode->NumVisiblePoints < CurrentNode->GetNumPoints())`
- L10 _macro_ `#define NODE_IN_BOX (Box.Intersect(Child->GetBounds()))`
- L11 _macro_ `#define NODE_IN_CONVEX_VOLUME (ConvexVolume.IntersectBox((FVector)Child->Center, (FVector)SharedData[Child->Depth].Extent))`
- L13 _macro_ `#define ITERATE_NODES_BODY(Action, NodeTest, Const) \`
- L28 _macro_ `#define ITERATE_NODES(Action, NodeTest) ITERATE_NODES_BODY(Action, NodeTest, )`
- L29 _macro_ `#define ITERATE_NODES_CONST(Action, NodeTest) ITERATE_NODES_BODY(Action, NodeTest, const)`
- L31 _macro_ `#define ITERATE_SELECTED_NODES(NodeAction) \`
- L37 _macro_ `#define ITERATE_SELECTED(PointAction, NodeAction) \`
- L44 _macro_ `#define POINT_IN_BOX Box.IsInsideOrOn((FVector)Point->Location)`
- L45 _macro_ `#define POINT_IN_SPHERE (POINT_IN_BOX && FVector3f::DistSquared(Point->Location, (FVector3f)Sphere.Center) <= RadiusSq)`
- L46 _macro_ `#define POINT_IN_CONVEX_VOLUME ConvexVolume.IntersectSphere((FVector)Point->Location, 0)`
- L47 _macro_ `#define POINT_BY_RAY Ray.Intersects(Point, RadiusSq)`
- L49 _macro_ `#define PROCESS_BODY(Action, PointTest, Mode) \`
- L64 _macro_ `#define PROCESS_ALL_BODY(Action, Mode) \`
- L73 _macro_ `#define PROCESS_IN_SPHERE_BODY_EXTERN(Octree, Action, Mode) \`
- L81 _macro_ `#define PROCESS_IN_SPHERE_BODY(Action, Mode) PROCESS_IN_SPHERE_BODY_EXTERN(this, Action, Mode)`
- L83 _macro_ `#define PROCESS_IN_BOX_BODY_EXTERN(Octree, Action, Mode) \`
- L91 _macro_ `#define PROCESS_IN_BOX_BODY(Action, Mode) PROCESS_IN_BOX_BODY_EXTERN(this, Action, Mode)`
- L93 _macro_ `#define PROCESS_IN_CONVEX_VOLUME_BODY(Action, Mode) \`
- L103 _macro_ `#define PROCESS_BY_RAY_BODY(Action, Mode) \`
- L120 _macro_ `#define PROCESS_IN_SPHERE_COMMON(Action) \`
- L127 _macro_ `#define PROCESS_IN_SPHERE(Action) { PROCESS_IN_SPHERE_COMMON(ITERATE_NODES(PROCESS_IN_SPHERE_BODY(Action,), NODE_IN_BOX)) }`
- L128 _macro_ `#define PROCESS_IN_SPHERE_EX(Action, NodeAction) { PROCESS_IN_SPHERE_COMMON(ITERATE_NODES({PROCESS_IN_SPHERE_BODY(Action,)} {NodeAction}, NODE_IN_BOX)) }`
- L129 _macro_ `#define PROCESS_IN_SPHERE_CONST(Action) { PROCESS_IN_SPHERE_COMMON(ITERATE_NODES_CONST(PROCESS_IN_SPHERE_BODY(Action, _RO), NODE_IN_BOX)) }`
- L130 _macro_ `#define PROCESS_IN_SPHERE_EXTERN(Octree, Action) { PROCESS_IN_SPHERE_COMMON(ITERATE_NODES(PROCESS_IN_SPHERE_BODY_EXTERN(Octree, Action,), NODE_IN_BOX)) }`
- L133 _macro_ `#define PROCESS_ALL(Action) { ITERATE_NODES(PROCESS_ALL_BODY(Action,), true) }`
- L134 _macro_ `#define PROCESS_ALL_EX(Action, NodeAction) { ITERATE_NODES({PROCESS_ALL_BODY(Action,)} {NodeAction}, true) }`
- L135 _macro_ `#define PROCESS_ALL_CONST(Action) { ITERATE_NODES_CONST(PROCESS_ALL_BODY(Action, _RO), true) }`
- L137 _macro_ `#define PROCESS_IN_BOX(Action) { ITERATE_NODES(PROCESS_IN_BOX_BODY(Action,), NODE_IN_BOX) }`
- L138 _macro_ `#define PROCESS_IN_BOX_EX(Action, NodeAction) { ITERATE_NODES({PROCESS_IN_BOX_BODY(Action,)} {NodeAction}, NODE_IN_BOX) }`
- L139 _macro_ `#define PROCESS_IN_BOX_CONST(Action) { ITERATE_NODES_CONST(PROCESS_IN_BOX_BODY(Action, _RO), NODE_IN_BOX) }`
- L140 _macro_ `#define PROCESS_IN_BOX_EXTERN(Octree, Action) { ITERATE_NODES(PROCESS_IN_BOX_BODY_EXTERN(Octree, Action,), NODE_IN_BOX) }`
- L142 _macro_ `#define PROCESS_IN_CONVEX_VOLUME(Action) { ITERATE_NODES(PROCESS_IN_CONVEX_VOLUME_BODY(Action,), NODE_IN_CONVEX_VOLUME) }`
- L143 _macro_ `#define PROCESS_IN_CONVEX_VOLUME_CONST(Action) { ITERATE_NODES_CONST(PROCESS_IN_CONVEX_VOLUME_BODY(Action, _RO), NODE_IN_CONVEX_VOLUME) }`
- L145 _macro_ `#define PROCESS_BY_RAY_COMMON(Action)\`
- L150 _macro_ `#define PROCESS_BY_RAY(Action) { PROCESS_BY_RAY_COMMON(ITERATE_NODES(PROCESS_BY_RAY_BODY(Action,), false)) }`
- L151 _macro_ `#define PROCESS_BY_RAY_EX(Action, NodeAction) { PROCESS_BY_RAY_COMMON(ITERATE_NODES({PROCESS_BY_RAY_BODY(Action,)} {NodeAction}, false)) }`
- L152 _macro_ `#define PROCESS_BY_RAY_CONST(Action) { PROCESS_BY_RAY_COMMON(ITERATE_NODES_CONST(PROCESS_BY_RAY_BODY(Action, _RO), false)) }`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Private/Rendering/LidarPointCloudRenderBuffers.h` (Private)


#### class `FLidarPointCloudBuffer`  
`class FLidarPointCloudBuffer`  
_L23-36_
- desc: Base class for the buffers
- L26 _public function_ `FLidarPointCloudBuffer() : FLidarPointCloudBuffer(100000)`
- L27 _public function_ `FLidarPointCloudBuffer(uint32 Capacity) : Capacity(Capacity)`
- L30 _public prototype_ `virtual void Resize(const uint32& RequestedCapacity) = 0;` — Resizes the buffer to the specified capacity, if necessary. Must be called from Rendering thread.
- L32 _public function_ `FORCEINLINE uint32 GetCapacity() const`
- L35 _protected member_ `uint32 Capacity;`

#### class `FLidarPointCloudIndexBuffer`  
`class FLidarPointCloudIndexBuffer : public FLidarPointCloudBuffer, public FIndexBuffer`  
_L41-50_
- inherits: `FLidarPointCloudBuffer,FIndexBuffer`
- desc: This class creates an IndexBuffer shared between all assets and all instances.
- L44 _public function_ `FLidarPointCloudIndexBuffer() : FLidarPointCloudBuffer(100000)`
- L46 _public member_ `uint32 PointOffset;`
- L48 _public prototype_ `virtual void Resize(const uint32& RequestedCapacity) override;`
- L49 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`

#### class `FLidarPointCloudRenderBuffer`  
`class FLidarPointCloudRenderBuffer : public FLidarPointCloudBuffer, public FRenderResource`  
_L55-76_
- inherits: `FLidarPointCloudBuffer,FRenderResource`
- desc: Encapsulates a GPU read buffer with its SRV.
- L58 _public function_ `FLidarPointCloudRenderBuffer() : FLidarPointCloudBuffer()`
- L59 _public function_ `FLidarPointCloudRenderBuffer(uint32 Capacity) : FLidarPointCloudBuffer(Capacity)`
- L61 _public prototype_ `void Initialize(FLidarPointCloudPoint* Data, int32 NumPoints);`
- L63 _public function_ `virtual FRHIUniformBuffer* GetUniformBuffer() const`
- L65 _public member_ `FBufferRHIRef Buffer;`
- L66 _public member_ `FShaderResourceViewRHIRef SRV;`
- L68 _public member_ `int32 PointCount;`
- L70 _public prototype_ `virtual void Resize(const uint32& RequestedCapacity) override;`
- L71 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L72 _public prototype_ `virtual void ReleaseRHI() override;`
- L75 _private member_ `TUniformBufferRef<FLidarPointCloudVertexFactoryUniformShaderParameters> UniformBuffer;`

#### class `FLidarPointCloudRayTracingGeometry`  
`class FLidarPointCloudRayTracingGeometry : public FRayTracingGeometry`  
_L78-93_
- inherits: `FRayTracingGeometry`
- L81 _public function_ `FLidarPointCloudRayTracingGeometry()`
- L82 _public function_ `virtual ~FLidarPointCloudRayTracingGeometry()`
- L84 _public prototype_ `void Initialize(int32 NumPoints);`
- L86 _public function_ `uint32 GetNumVertices() const`
- L87 _public function_ `uint32 GetNumPrimitives() const`
- L88 _public function_ `uint32 GetBufferSize() const`
- L91 _private member_ `uint32 NumVertices;`
- L92 _private member_ `uint32 NumPrimitives;`

#### struct `FLidarPointCloudBatchElementUserData`  
`struct FLidarPointCloudBatchElementUserData`  
_L98-137_
- desc: Holds all data to be passed to the FLidarPointCloudVertexFactoryShaderParameters as UserData
- L100 _public member_ `FRHIShaderResourceView* TreeBuffer;`
- L101 _public member_ `int32 bEditorView;`
- L102 _public member_ `FVector3f SelectionColor;`
- L103 _public member_ `FVector3f LocationOffset;`
- L104 _public member_ `float RootCellSize;`
- L105 _public member_ `FVector3f RootExtent;`
- L106 _public member_ `int32 bUsePerPointScaling;`
- L107 _public member_ `float VirtualDepth;`
- L108 _public member_ `float SpriteSizeMultiplier;`
- L109 _public member_ `float ReversedVirtualDepthMultiplier;`
- L110 _public member_ `FVector3f ViewRightVector;`
- L111 _public member_ `FVector3f ViewUpVector;`
- L112 _public member_ `int32 bUseCameraFacing;`
- L113 _public member_ `int32 bUseScreenSizeScaling;`
- L114 _public member_ `int32 bUseStaticBuffers;`
- L115 _public member_ `FVector3f BoundsSize;`
- L116 _public member_ `FVector3f ElevationColorBottom;`
- L117 _public member_ `FVector3f ElevationColorTop;`
- L118 _public member_ `int32 bUseCircle;`
- L119 _public member_ `int32 bUseColorOverride;`
- L120 _public member_ `int32 bUseElevationColor;`
- L121 _public member_ `FVector4f Offset;`
- L122 _public member_ `FVector4f Contrast;`
- L123 _public member_ `FVector4f Saturation;`
- L124 _public member_ `FVector4f Gamma;`
- L125 _public member_ `FVector3f Tint;`
- L126 _public member_ `float IntensityInfluence;`
- L127 _public member_ `int32 bUseClassification;`
- L128 _public member_ `int32 bUseClassificationAlpha;`
- L129 _public member_ `FVector4f ClassificationColors[32];`
- L130 _public member_ `FMatrix44f ClippingVolume[16];`
- L131 _public member_ `uint32 NumClippingVolumes;`
- L132 _public member_ `uint32 bStartClipped;`
- L134 _public prototype_ `FLidarPointCloudBatchElementUserData();`
- L136 _public prototype_ `void SetClassificationColors(const TMap<int32, FLinearColor>& InClassificationColors);`

#### class `FLidarPointCloudVertexFactoryShaderParameters`  
`class FLidarPointCloudVertexFactoryShaderParameters : public FVertexFactoryShaderParameters`  
_L142-184_
- inherits: `FVertexFactoryShaderParameters`
- desc: Binds shader parameters necessary for rendering
- L147 _public prototype_ `void Bind(const FShaderParameterMap& ParameterMap);`
- L148 _public prototype_ `void GetElementShaderBindings(const class FSceneInterface* Scene, const FSceneView* View, const FMeshMaterialShader* Shader, const EVertexInputStreamType InputStreamType, ERHIFeatureLevel::Type FeatureLevel, const FVertexFactory* VertexFactory, const FMeshBatchElement& BatchElement, class FMeshDrawSingleShaderBindings& ShaderBindings, FVertexInputStreamArray& VertexStreams) const;`

#### class `FLidarPointCloudVertexFactoryBase`  
`class FLidarPointCloudVertexFactoryBase : public FVertexFactory`  
_L186-207_
- inherits: `FVertexFactory`
- L188 _private prototype_ `DECLARE_VERTEX_FACTORY_TYPE(FLidarPointCloudVertexFactoryBase);`
- L191 _public function_ `static bool ShouldCache(const FVertexFactoryShaderPermutationParameters& Parameters)`
- L192 _public prototype_ `static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);`
- L193 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`
- L195 _public function_ `FLidarPointCloudVertexFactoryBase() : FVertexFactory(ERHIFeatureLevel::SM5)`
- L197 _public function_ `virtual FVertexBuffer* GetVertexBuffer()`
- L198 _public function_ `virtual FBufferRHIRef GetVertexBufferRHI()`
- L199 _public prototype_ `virtual FShaderResourceViewRHIRef GetVertexBufferSRV();`
- L200 _public function_ `virtual FRHIUniformBuffer* GetUniformBuffer() const`
- L202 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L203 _public prototype_ `virtual void ReleaseRHI() override;`
- L206 _protected member_ `TUniformBufferRef<FLidarPointCloudVertexFactoryUniformShaderParameters> UniformBuffer;`

#### class `FLidarPointCloudVertexFactory`  
`class FLidarPointCloudVertexFactory : public FLidarPointCloudVertexFactoryBase`  
_L209-232_
- inherits: `FLidarPointCloudVertexFactoryBase`
- L212 _public prototype_ `void Initialize(FLidarPointCloudPoint* Data, int32 NumPoints);`
- L214 _public function_ `virtual FVertexBuffer* GetVertexBuffer() override`
- L215 _public function_ `virtual FShaderResourceViewRHIRef GetVertexBufferSRV() override`
- L228 _private member_ `} VertexBuffer;`
- L230 _private prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L231 _private prototype_ `virtual void ReleaseRHI() override;`

#### class `FLidarPointCloudVertexFactory::FPointCloudVertexBuffer`  
`class FPointCloudVertexBuffer : public FVertexBuffer`  
_L218-228_
- inherits: `FVertexBuffer`
- L220 _private member_ `FLidarPointCloudPoint* Data;`
- L221 _private member_ `int32 NumPoints;`
- L222 _private member_ `FShaderResourceViewRHIRef VertexBufferSRV;`
- L225 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L226 _public function_ `virtual FString GetFriendlyName() const override`

#### class `FLidarPointCloudSharedVertexFactory`  
`class FLidarPointCloudSharedVertexFactory : public FLidarPointCloudVertexFactoryBase`  
_L237-254_
- inherits: `FLidarPointCloudVertexFactoryBase`
- desc: Implementation of the custom Vertex Factory, containing only a ZeroStride position stream.
- L240 _public function_ `virtual FVertexBuffer* GetVertexBuffer() override`
- L250 _private member_ `} VertexBuffer;`
- L252 _private prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L253 _private prototype_ `virtual void ReleaseRHI() override;`

#### class `FLidarPointCloudSharedVertexFactory::FPointCloudVertexBuffer`  
`class FPointCloudVertexBuffer : public FVertexBuffer`  
_L244-250_
- inherits: `FVertexBuffer`
- desc: Very simple implementation of a ZeroStride Vertex Buffer
- L246 _private member_ `FShaderResourceViewRHIRef VertexBufferSRV;`
- L248 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L249 _public function_ `virtual FString GetFriendlyName() const override`

#### Free symbols / members of external scopes

- L257 _externvar_ `extern TGlobalResource<FLidarPointCloudIndexBuffer> GLidarPointCloudIndexBuffer;` — A set of global render resources shared between all Lidar Point Cloud proxies
- L258 _externvar_ `extern TGlobalResource<FLidarPointCloudSharedVertexFactory> GLidarPointCloudSharedVertexFactory;`
- L259 _externvar_ `extern TGlobalResource<FLidarPointCloudRenderBuffer> GDummyLidarPointCloudRenderBuffer;`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/ILidarPointCloudRuntimeModule.h` (Public)


#### class `ILidarPointCloudRuntimeModule`  
`class ILidarPointCloudRuntimeModule : public IModuleInterface`  
_L12-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline ILidarPointCloudRuntimeModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/IO/LidarPointCloudFileIO.h` (Public)


#### struct `FLidarPointCloudImportSettings`  
`struct FLidarPointCloudImportSettings`  
_L14-78_
- desc: Base for all importer settings
- L18 _public member_ `bool bImportAll;` — Holds a flag determining whether the same settings should be applied to the whole import at once
- L22 _protected member_ `FString Filename;` — Used to determine the correct Handler to use during serialization.
- L25 _public function_ `FLidarPointCloudImportSettings(const FString& Filename) : bImportAll(false) , Filename(Filename)`
- L30 _public function_ `virtual ~FLidarPointCloudImportSettings()`
- L36 _public function_ `virtual bool IsFileCompatible(const FString& InFilename) const` — Should return true if the given file is compatible with this instance of settings Useful for detecting different headers
- L42 _public prototype_ `virtual void Serialize(FArchive& Ar);` — Links the FLidarPointCloudImportSettings with FArchive serialization No need to manually serialize Filename - it is handled by ULidarPointCloudFileIO::SerializeImportSettings
- L44 _public function_ `FString GetFilename() const`
- L47 _public function_ `bool IsGeneric() const` — Returns true it this is an instance of FLidarPointCloudImportSettings
- L49 _public function_ `virtual void SetNewFilename(const FString& NewFilename)`
- L55 _public function_ `virtual FString GetUID() const` — Must return a unique id of this Import Settings type.
- L61 _public function_ `virtual TSharedPtr<FLidarPointCloudImportSettings> Clone(const FString& NewFilename = "")` — Returns duplicate of this instance of Import Settings. Optionally, can use a different filename when cloning.
- L63 _public function_ `static TSharedPtr<FLidarPointCloudImportSettings> MakeGeneric(const FString& Filename)`
- L70 _public function_ `virtual TSharedPtr<SWidget> GetWidget()` — Used to create properties window.
- L73 _public function_ `virtual bool HasImportUI() const` — Should return true, if the importer requires import settings UI to be shown.

#### struct `FLidarPointCloudImportResults`  
`struct FLidarPointCloudImportResults`  
_L81-133_
- desc: Stores the results of the import process
- L84 _public member_ `TArray64<FLidarPointCloudPoint> Points;`
- L85 _public member_ `FBox Bounds;`
- L86 _public member_ `FVector OriginalCoordinates;`
- L89 _public member_ `TArray<uint8> ClassificationsImported;` — Contains the list of imported classification IDs
- L93 _private member_ `TFunction<void(float)> ProgressCallback;` — Used for async importing
- L94 _private member_ `FThreadSafeBool* bCancelled;`
- L95 _private member_ `uint64 ProgressFrequency;`
- L96 _private member_ `uint64 ProgressCounter;`
- L97 _private member_ `uint64 TotalProgressCounter;`
- L98 _private member_ `uint64 MaxProgressCounter;`
- L99 _private member_ `TFunction<void(const FBox& Bounds, FVector)> InitCallback;`
- L100 _private member_ `TFunction<void(TArray64<FLidarPointCloudPoint>*)> BufferCallback;`
- L103 _public prototype_ `FLidarPointCloudImportResults(FThreadSafeBool* bInCancelled = nullptr, TFunction<void(float)> InProgressCallback = TFunction<void(float)>());`
- L104 _public prototype_ `FLidarPointCloudImportResults(FThreadSafeBool* bInCancelled, TFunction<void(float)> InProgressCallback, TFunction<void(const FBox& Bounds, FVector)> InInitCallback, TFunction<void(TArray64<FLidarPointCloudPoint>*)> InBufferCallback);`
- L106 _public prototype_ `void InitializeOctree(const FBox& InBounds);`
- L108 _public prototype_ `void ProcessBuffer(TArray64<FLidarPointCloudPoint>* InPoints);`
- L110 _public prototype_ `void SetPointCount(const uint64& InTotalPointCount);`
- L112 _public function_ `inline void AddPoint(const FVector& Location, const float& R, const float& G, const float& B, const float& A = 1.0f)`
- L117 _public prototype_ `void AddPoint(const float& X, const float& Y, const float& Z, const float& R, const float& G, const float& B, const float& A = 1.0f);`
- L119 _public prototype_ `void AddPoint(const float& X, const float& Y, const float& Z, const float& R, const float& G, const float& B, const float& A, const float& NX, const float& NY, const float& NZ);`
- L121 _public prototype_ `void AddPointsBulk(TArray64<FLidarPointCloudPoint>& InPoints);`
- L123 _public prototype_ `void CenterPoints();`
- L125 _public function_ `inline bool IsCancelled() const`
- L130 _public prototype_ `void SetMaxProgressCounter(uint64 MaxCounter);`
- L132 _public prototype_ `void IncrementProgressCounter(uint64 Increment);`

#### class `FLidarPointCloudFileIOHandler`  
`class FLidarPointCloudFileIOHandler`  
_L136-179_
- desc: Base type implemented by all file handlers.
- L140 _protected member_ `double PrecisionCorrectionOffset[3] = { 0, 0, 0 };` — Used for precision loss check and correction.
- L141 _protected member_ `bool bPrecisionCorrected = false;`
- L145 _public prototype_ `void PrepareImport();` — Called before importing to prepare the data.
- L148 _public function_ `virtual bool SupportsImport() const` — Must return true if the handler supports importing.
- L151 _public function_ `virtual bool SupportsExport() const` — Must return true if the handler supports exporting.
- L154 _public function_ `virtual bool HandleImport(const FString& Filename, TSharedPtr<FLidarPointCloudImportSettings> ImportSettings, FLidarPointCloudImportResults& OutImportResults)` — This is what will actually be called to process the import of the file.
- L157 _public function_ `virtual bool HandleExport(const FString& Filename, class ULidarPointCloud* PointCloud)` — These will actually be called to process the export of the asset.
- L160 _public function_ `virtual TSharedPtr<FLidarPointCloudImportSettings> GetImportSettings(const FString& Filename) const` — Returns a shared pointer for the import settings of this importer.
- L166 _public function_ `virtual bool SupportsConcurrentInsertion(const FString& Filename) const` — Returns true if the given file supports importing and building an octree concurrently. False if the data needs caching first.
- L172 _public function_ `virtual bool IsSettingsUIDSupported(const FString& UID)` — Must return true if the provided UID is of supported Import Settings type. Default implementation simply checks the default ImportSettings' UID to compare against.
- L178 _public prototype_ `virtual bool ValidateImportSettings(TSharedPtr<FLidarPointCloudImportSettings>& ImportSettings, const FString& Filename);` — Performs validation checks and corrections on the provided ImportSettings object using the given Filename. Returns true if the resulting object is valid.

#### class `ULidarPointCloudFileIO`  
`class ULidarPointCloudFileIO : public UExporter`  
_L185-234_
- reflection: `UCLASS()`
- inherits: `UExporter`
- desc: Holds information about all registered file handlers
- L191 _private member_ `static TMap<FString, FLidarPointCloudFileIOHandler*> RegisteredHandlers;` — Links extensions to file handlers.
- L198 _public prototype_ `static bool Import(const FString& Filename, TSharedPtr<FLidarPointCloudImportSettings> ImportSettings, FLidarPointCloudImportResults& OutImportResults);` — Automatically detects correct format and performs the import. Returns true if the import was successful.
- L200 _public prototype_ `static bool Export(const FString& Filename, class ULidarPointCloud* AssetToExport);`
- L205 _public prototype_ `static TSharedPtr<FLidarPointCloudImportSettings> GetImportSettings(const FString& Filename);` — Returns the import settings instance depending on the format provided
- L208 _public prototype_ `static TArray<FString> GetSupportedImportExtensions();` — Returns the list of all registered import extensions
- L211 _public prototype_ `static TArray<FString> GetSupportedExportExtensions();` — Returns the list of all registered export extensions
- L214 _public prototype_ `static void RegisterHandler(FLidarPointCloudFileIOHandler* Handler, const TArray<FString>& Extensions);` — Called to register an handler for the supported formats list
- L217 _public function_ `static FLidarPointCloudFileIOHandler* FindHandlerByFilename(const FString& Filename)` — Returns pointer to the handler, which supports the given format or null if none found.
- L218 _public prototype_ `static FLidarPointCloudFileIOHandler* FindHandlerByType(const FString& Type);`
- L221 _public prototype_ `static void SerializeImportSettings(FArchive& Ar, TSharedPtr<FLidarPointCloudImportSettings>& ImportSettings);` — Responsible for serialization using correct serializer for the given format.
- L227 _public prototype_ `static bool FileSupportsConcurrentInsertion(const FString& Filename);` — Returns true if the given file supports importing and building an octree concurrently. False if the data needs caching first.
- L231 _public prototype_ `virtual bool SupportsObject(UObject* Object) const override;`
- L232 _public prototype_ `virtual bool ExportBinary(UObject* Object, const TCHAR* Type, FArchive& Ar, FFeedbackContext* Warn, int32 FileIndex = 0, uint32 PortFlags = 0) override;`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/IO/LidarPointCloudFileIO_ASCII.h` (Public)


#### struct `FLidarPointCloudImportSettings_ASCII_Columns`  
`struct FLidarPointCloudImportSettings_ASCII_Columns`  
_L25-84_
- reflection: `USTRUCT(BlueprintType)`
- desc: Used to help expose the import settings to Blueprints
- L32 _public member_ `int32 LocationX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Location X data
- L36 _public member_ `int32 LocationY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Location Y data
- L40 _public member_ `int32 LocationZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Location Z data
- L44 _public member_ `int32 Red;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Red channel. Set to -1 if not available
- L48 _public member_ `int32 Green;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Green channel. Set to -1 if not available
- L52 _public member_ `int32 Blue;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Blue channel. Set to -1 if not available
- L56 _public member_ `int32 Intensity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Intensity channel. Set to -1 if not available
- L60 _public member_ `int32 NormalX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Normal X data. Set to -1 if not available
- L64 _public member_ `int32 NormalY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Normal Y data. Set to -1 if not available
- L68 _public member_ `int32 NormalZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Import Settings")` — Index of a column containing Normal Z data. Set to -1 if not available
- L71 _public function_ `FLidarPointCloudImportSettings_ASCII_Columns()`

#### struct `FLidarPointCloudImportSettings_ASCII`  
`struct FLidarPointCloudImportSettings_ASCII : public FLidarPointCloudImportSettings`  
_L86-160_
- inherits: `FLidarPointCloudImportSettings`
- L88 _public member_ `int32 LinesToSkip;`
- L89 _public member_ `int64 EstimatedPointCount;`
- L90 _public member_ `FString Delimiter;`
- L91 _public member_ `TArray<FString> Columns;`
- L92 _public member_ `TArray<int32> SelectedColumns;`
- L93 _public member_ `FVector2D RGBRange;`
- L96 _public prototype_ `FLidarPointCloudImportSettings_ASCII(const FString& Filename);`
- L97 _public prototype_ `virtual bool IsFileCompatible(const FString& InFilename) const override;`
- L100 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Links the FLidarPointCloudImportSettings_ASCII with FArchive serialization
- L102 _public function_ `virtual FString GetUID() const override`
- L104 _public function_ `virtual void SetNewFilename(const FString& NewFilename) override`
- L121 _public function_ `virtual TSharedPtr<FLidarPointCloudImportSettings> Clone(const FString& NewFilename = "") override`
- L132 _public function_ `inline bool HasValidData()`
- L136 _private prototype_ `void ReadFileHeader(const FString& InFilename);` — Reads and parses header information about the given file.
- L142 _private prototype_ `FVector2D ReadFileMinMaxColumns(TArray<int32> ColumnsToScan, bool bBestMatch);` — Scans the given file and searches for Min and Max values within the given columns. Optionally, attempts to find the best color range match for the given MinMax pair
- L148 _private member_ `TArray<TSharedPtr<FString>> Options;`
- L149 _private member_ `TSharedPtr<SSpinBox<float>> RGBRangeMin;`
- L150 _private member_ `TSharedPtr<SSpinBox<float>> RGBRangeMax;`
- L153 _public prototype_ `virtual TSharedPtr<SWidget> GetWidget() override;`
- L155 _public function_ `virtual bool HasImportUI() const override`
- L158 _private prototype_ `TSharedRef<SWidget> HandleGenerateWidget(FString Item) const;`

#### class `ULidarPointCloudFileIO_ASCII`  
`class ULidarPointCloudFileIO_ASCII : public UBlueprintFunctionLibrary, public FLidarPointCloudFileIOHandler`  
_L166-186_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary,FLidarPointCloudFileIOHandler`
- desc: Inherits from UBlueprintFunctionLibrary to allow exposure to Blueprint Library in the same class.
- L171 _public function_ `virtual bool SupportsImport() const override`
- L172 _public function_ `virtual bool SupportsExport() const override`
- L175 _public prototype_ `static void CreatePointCloudFromFile(UObject* WorldContextObject, const FString& Filename, bool bUseAsync, FVector2D RGBRange, FLidarPointCloudImportSettings_ASCII_Columns Columns, FLatentActionInfo LatentInfo, ELidarPointCloudAsyncMode& AsyncMode, float& Progress, ULidarPointCloud*& PointCloud);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "AsyncMode", DisplayName = "Create Lidar Point Cloud From File (ASCII)"))`
- L176 _public prototype_ `static ULidarPointCloud* CreatePointCloudFromFile(const FString& Filename, const FLidarPointCloudAsyncParameters& AsyncParameters, const FVector2D& RGBRange, const FLidarPointCloudImportSettings_ASCII_Columns& Columns);`
- L178 _public prototype_ `virtual bool HandleImport(const FString& Filename, TSharedPtr<FLidarPointCloudImportSettings> ImportSettings, FLidarPointCloudImportResults &OutImportResults) override;`
- L179 _public function_ `virtual TSharedPtr<FLidarPointCloudImportSettings> GetImportSettings(const FString& Filename) const override`
- L181 _public prototype_ `virtual bool HandleExport(const FString& Filename, class ULidarPointCloud* PointCloud) override;`
- L183 _public function_ `virtual bool SupportsConcurrentInsertion(const FString& Filename) const override`
- L185 _public function_ `ULidarPointCloudFileIO_ASCII()`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/IO/LidarPointCloudFileIO_E57.h` (Public)


#### struct `FLidarPointCloudImportSettings_E57`  
`struct FLidarPointCloudImportSettings_E57 : public FLidarPointCloudImportSettings`  
_L11-22_
- inherits: `FLidarPointCloudImportSettings`
- L13 _public function_ `FLidarPointCloudImportSettings_E57(const FString& Filename) : FLidarPointCloudImportSettings(Filename)`
- L14 _public function_ `virtual bool IsFileCompatible(const FString& InFilename) const override`
- L15 _public function_ `virtual FString GetUID() const override`
- L16 _public function_ `virtual TSharedPtr<FLidarPointCloudImportSettings> Clone(const FString& NewFilename = "") override`

#### class `ULidarPointCloudFileIO_E57`  
`class ULidarPointCloudFileIO_E57 : public UObject, public FLidarPointCloudFileIOHandler`  
_L26-49_
- reflection: `UCLASS()`
- inherits: `UObject,FLidarPointCloudFileIOHandler`
- L32 _public function_ `virtual bool SupportsImport() const override`
- L33 _public function_ `virtual bool SupportsExport() const override`
- L35 _public prototype_ `virtual bool HandleImport(const FString& Filename, TSharedPtr<FLidarPointCloudImportSettings> ImportSettings, FLidarPointCloudImportResults& OutImportResults) override;`
- L36 _public function_ `virtual bool HandleExport(const FString& Filename, class ULidarPointCloud* PointCloud) override`
- L38 _public function_ `virtual TSharedPtr<FLidarPointCloudImportSettings> GetImportSettings(const FString& Filename) const override`
- L40 _public function_ `virtual bool SupportsConcurrentInsertion(const FString& Filename) const override`
- L43 _public function_ `ULidarPointCloudFileIO_E57()`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/IO/LidarPointCloudFileIO_LAS.h` (Public)


#### struct `FLidarPointCloudImportSettings_LAS`  
`struct FLidarPointCloudImportSettings_LAS : public FLidarPointCloudImportSettings`  
_L12-24_
- inherits: `FLidarPointCloudImportSettings`
- L14 _public function_ `FLidarPointCloudImportSettings_LAS(const FString& Filename) : FLidarPointCloudImportSettings(Filename)`
- L15 _public function_ `virtual bool IsFileCompatible(const FString& InFilename) const override`
- L16 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L17 _public function_ `virtual FString GetUID() const override`
- L18 _public function_ `virtual TSharedPtr<FLidarPointCloudImportSettings> Clone(const FString& NewFilename = "") override`

#### class `ULidarPointCloudFileIO_LAS`  
`class ULidarPointCloudFileIO_LAS : public UObject, public FLidarPointCloudFileIOHandler`  
_L27-58_
- reflection: `UCLASS()`
- inherits: `UObject,FLidarPointCloudFileIOHandler`
- L32 _public function_ `virtual bool SupportsImport() const override`
- L33 _public function_ `virtual bool SupportsExport() const override`
- L35 _public function_ `virtual TSharedPtr<FLidarPointCloudImportSettings> GetImportSettings(const FString& Filename) const override`
- L37 _public prototype_ `virtual bool HandleImport(const FString& Filename, TSharedPtr<FLidarPointCloudImportSettings> ImportSettings, FLidarPointCloudImportResults& OutImportResults) override;`
- L38 _public prototype_ `virtual bool HandleExport(const FString& Filename, ULidarPointCloud* PointCloud) override;`
- L40 _public prototype_ `virtual bool SupportsConcurrentInsertion(const FString& Filename) const override;`
- L42 _public function_ `ULidarPointCloudFileIO_LAS()`
- L51 _private prototype_ `bool HandleImportLAS(const FString& Filename, FLidarPointCloudImportResults& OutImportResults);`
- L52 _private prototype_ `bool HandleExportLAS(const FString& Filename, ULidarPointCloud* PointCloud);`
- L55 _private prototype_ `bool HandleImportLAZ(const FString& Filename, FLidarPointCloudImportResults& OutImportResults);`
- L56 _private prototype_ `bool HandleExportLAZ(const FString& Filename, ULidarPointCloud* PointCloud);`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/LidarPointCloud.h` (Public)


#### struct `FLidarPointCloudAsyncParameters`  
`struct FLidarPointCloudAsyncParameters`  
_L33-56_
- desc: Used for ULidarPointCloud::CreateFromXXXX calls
- L36 _public member_ `bool bUseAsync;` — Should the creation use async operation
- L42 _public member_ `TFunction<void(float)> ProgressCallback;` — Called every time at least 1% progress is generated. The parameter is within 0.0 - 1.0 range.
- L48 _public member_ `TFunction<void(bool)> CompletionCallback;` — Called once, when the operation completes. The parameter specifies whether it has been executed successfully.
- L50 _public function_ `FLidarPointCloudAsyncParameters(bool bUseAsync, TFunction<void(float)> ProgressCallback = nullptr, TFunction<void(bool)> CompletionCallback = nullptr) : bUseAsync(bUseAsync) , ProgressCallback(MoveTemp(ProgressCallback)) , CompletionCallback(MoveTemp(CompletionCallback))`

#### class `ULidarPointCloud`  
`class ULidarPointCloud : public UObject, public IInterface_CollisionDataProvider`  
_L65-713_
- reflection: `UCLASS(BlueprintType, AutoExpandCategories=("Performance", "Rendering|Sprite"), AutoCollapseCategories=("Import Settings"))`
- inherits: `UObject,IInterface_CollisionDataProvider`
- desc: Represents the Point Cloud asset
- L72 _private member_ `FFilePath SourcePath;` — `UPROPERTY(EditAnywhere, Category = "Import Settings", meta = (AllowPrivateAccess = "true"))` — Stores the path to the original source file. Empty if dynamically created.
- L81 _public member_ `float MaxCollisionError;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")` — Determines the maximum error (in cm) of the collision for this point cloud. NOTE: Lower values will require more time to build. Rebuild collision for the changes to take effect.
- L84 _public member_ `float CollisionAccuracy_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use MaxCollisionError instead."))`
- L88 _public member_ `int32 NormalsQuality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals", meta = (ClampMin = "1", ClampMax = "100", DisplayName = "Quality"))` — Higher values will generally result in more accurate calculations, at the expense of time
- L96 _public member_ `float NormalsNoiseTolerance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals", meta = (ClampMin = "0.0", DisplayName = "Noise Tolerance"))` — Higher values are less susceptible to noise, but will most likely lose finer details, especially around hard edges. Lower values retain more detail, at the expense of time. NOTE: setting this too low will cause visual artifacts and geometry holes in noisier datasets.
- L100 _public member_ `FVector OriginalCoordinates;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Coordinates")` — Stores the original offset as a double.
- L111 _private member_ `bool bOptimizedForDynamicData;` — `UPROPERTY(EditAnywhere, Category = "Performance", meta = (AllowPrivateAccess = "true"))` — Disables the LOD pipeline, allowing for much faster data operations (insert/remove/set) at a potential expense of runtime performance. The whole asset will be treated as a single, large asset with no granular density control, nor occlusion culling. Recommended for assets, which have their data updated per-frame (such as live streaming).
- L115 _public member_ `TSharedPtr<struct FLidarPointCloudImportSettings> ImportSettings;` — Holds pointer to the Import Settings used for the import.
- L117 _public member_ `FLidarPointCloudOctree Octree;`
- L118 _public member_ `FLidarPointCloudCollisionRendering* CollisionRendering;`
- L122 _public member_ `FVector LocationOffset;` — `UPROPERTY()` — Contains an offset to be added to all points when rendering
- L125 _public member_ `static const FGuid PointCloudFileGUID;` — Required for file versioning
- L126 _public member_ `static const int32 PointCloudFileVersion;`
- L134 _private member_ `} PointCloudAssetRegistryCache;`
- L138 _private member_ `TArray<uint8> ClassificationsImported;` — `UPROPERTY()` — Contains the list of imported classification IDs
- L141 _private member_ `FThreadSafeBool bAsyncCancelled;` — Used for async processing
- L142 _private member_ `FCriticalSection ProcessingLock;`
- L155 _private member_ `} Notifications;`
- L159 _private member_ `TObjectPtr<UBodySetup> BodySetup;` — `UPROPERTY(transient, duplicatetransient)` — Description of collision
- L161 _private member_ `TObjectPtr<UBodySetup> NewBodySetup;` — `UPROPERTY(transient, duplicatetransient)`
- L164 _private member_ `FThreadSafeBool bCollisionBuildInProgress;` — Used for collision building
- L166 _private member_ `FOnPointCloudChanged OnPointCloudRebuiltEvent;`
- L167 _private member_ `FOnPointCloudChanged OnPointCloudUpdateCollisionEvent;`
- L168 _private member_ `FOnPointCloudChanged OnPointCloudNormalsUpdatedEvent;`
- L169 _private member_ `FOnPointCloudChanged OnPreSaveCleanupEvent;`
- L172 _public prototype_ `ULidarPointCloud();`
- L174 _public function_ `FOnPointCloudChanged& OnPointCloudRebuilt()`
- L175 _public function_ `FOnPointCloudChanged& OnPointCloudCollisionUpdated()`
- L176 _public function_ `FOnPointCloudChanged& OnPointCloudNormalsUpdated()`
- L177 _public function_ `FOnPointCloudChanged& OnPreSaveCleanup()`
- L180 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L181 _public prototype_ `virtual void PostLoad() override;`
- L182 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L184 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L185 _public prototype_ `virtual void BeginDestroy() override;`
- L186 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L188 _public prototype_ `virtual void ClearAllCachedCookedPlatformData() override;`
- L189 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L194 _public function_ `int32 GetNumLODs() const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta=(ScriptName="GetNumLods;GetNumLODs"))`
- L197 _public function_ `int64 GetNumPoints() const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")`
- L200 _public function_ `int64 GetNumVisiblePoints() const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")`
- L203 _public function_ `int32 GetNumNodes() const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")`
- L206 _public function_ `inline float GetEstimatedPointSpacing() const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")`
- L210 _public prototype_ `int32 GetDataSize() const;` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns the amount of memory in MB used to store the point cloud.
- L213 _public function_ `FString GetSourcePath() const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")`
- L216 _public function_ `bool IsOptimizedForDynamicData() const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")`
- L219 _public function_ `FBox GetBounds(bool bUseOriginalCoordinates = false) const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")`
- L223 _public prototype_ `void RefreshBounds();` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Recalculates and updates points bounds.
- L227 _public prototype_ `bool HasCollisionData() const;` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns true, if the Octree has collision built
- L231 _public prototype_ `int32 GetColliderPolys() const;` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns the number of polygons in the collider or 0 if no collider is built
- L234 _public prototype_ `void RefreshRendering();` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")`
- L236 _public function_ `TArray<uint8> GetClassificationsImported()`
- L240 _public function_ `bool HasPointsInSphere(FVector Center, float Radius, bool bVisibleOnly) const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns true if there are any points within the given sphere.
- L244 _public function_ `bool HasPointsInSphere(const FSphere& Sphere, bool bVisibleOnly) const`
- L251 _public function_ `bool HasPointsInBox(FVector Center, FVector Extent, bool bVisibleOnly) const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns true if there are any points within the given box.
- L255 _public function_ `bool HasPointsInBox(const FBox& Box, bool bVisibleOnly) const`
- L262 _public function_ `bool HasPointsByRay(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly) const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns true if there are any points hit by the given ray.
- L266 _public function_ `bool HasPointsByRay(const FLidarPointCloudRay& Ray, float Radius, bool bVisibleOnly) const`
- L272 _public prototype_ `void GetPoints(TArray<FLidarPointCloudPoint*>& Points, int64 StartIndex = 0, int64 Count = -1);` — Populates the given array with points from the tree
- L273 _public prototype_ `void GetPoints(TArray64<FLidarPointCloudPoint*>& Points, int64 StartIndex = 0, int64 Count = -1);`
- L276 _public prototype_ `void GetPointsInSphere(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly);` — Populates the array with the list of points within the given sphere.
- L277 _public prototype_ `void GetPointsInSphere(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly);`
- L280 _public prototype_ `void GetPointsInBox(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly);` — Populates the array with the list of points within the given box.
- L281 _public prototype_ `void GetPointsInBox(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly);`
- L287 _public prototype_ `void GetPointsInConvexVolume(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FConvexVolume& ConvexVolume, const bool& bVisibleOnly);` — Populates the array with the list of points within the given convex volume. The volume is assumed to include the LocationOffset of the asset
- L288 _public prototype_ `void GetPointsInConvexVolume(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FConvexVolume& ConvexVolume, const bool& bVisibleOnly);`
- L295 _public prototype_ `TArray<FLidarPointCloudPoint> GetPointsAsCopies(bool bReturnWorldSpace, int32 StartIndex = 0, int32 Count = -1) const;` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns an array with copies of points from the tree If ReturnWorldSpace is selected, the points' locations will be converted into absolute value, otherwise they will be relative to the center of the cloud.
- L296 _public prototype_ `void GetPointsAsCopies(TArray<FLidarPointCloudPoint>& Points, bool bReturnWorldSpace, int64 StartIndex = 0, int64 Count = -1) const;`
- L297 _public prototype_ `void GetPointsAsCopies(TArray64<FLidarPointCloudPoint>& Points, bool bReturnWorldSpace, int64 StartIndex = 0, int64 Count = -1) const;`
- L304 _public prototype_ `TArray<FLidarPointCloudPoint> GetPointsInSphereAsCopies(FVector Center, float Radius, bool bVisibleOnly, bool bReturnWorldSpace);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns an array with copies of points within the given sphere If ReturnWorldSpace is selected, the points' locations will be converted into absolute value, otherwise they will be relative to the center of the cloud.
- L305 _public prototype_ `void GetPointsInSphereAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly, bool bReturnWorldSpace) const;`
- L306 _public prototype_ `void GetPointsInSphereAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly, bool bReturnWorldSpace) const;`
- L313 _public prototype_ `TArray<FLidarPointCloudPoint> GetPointsInBoxAsCopies(FVector Center, FVector Extent, bool bVisibleOnly, bool bReturnWorldSpace);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns an array with copies of points within the given box If ReturnWorldSpace is selected, the points' locations will be converted into absolute value, otherwise they will be relative to the center of the cloud.
- L314 _public prototype_ `void GetPointsInBoxAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly, bool bReturnWorldSpace) const;`
- L315 _public prototype_ `void GetPointsInBoxAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly, bool bReturnWorldSpace) const;`
- L319 _public prototype_ `bool LineTraceSingle(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly, FLidarPointCloudPoint& PointHit);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (Keywords = "raycast"))` — Performs a raycast test against the point cloud. Returns the pointer if hit or nullptr otherwise.
- L320 _public function_ `FLidarPointCloudPoint* LineTraceSingle(const FLidarPointCloudRay& Ray, const float& Radius, const bool& bVisibleOnly)`
- L329 _public function_ `bool LineTraceMulti(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly, bool bReturnWorldSpace, TArray<FLidarPointCloudPoint>& OutHits)` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (Keywords = "raycast"))` — Performs a raycast test against the point cloud. Populates OutHits array with the results. If ReturnWorldSpace is selected, the points' locations will be converted into absolute value, otherwise they will be relative to the center of the cloud. Returns true it anything has been hit.
- L330 _public function_ `bool LineTraceMulti(const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly, bool bReturnWorldSpace, TArray<FLidarPointCloudPoint>& OutHits)`
- L335 _public function_ `bool LineTraceMulti(const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly, TArray<FLidarPointCloudPoint*>& OutHits)`
- L339 _public function_ `void SetVisibilityOfPointsInSphere(bool bNewVisibility, FVector Center, float Radius)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets visibility of points within the given sphere.
- L340 _public function_ `void SetVisibilityOfPointsInSphere(const bool& bNewVisibility, FSphere Sphere)`
- L348 _public function_ `void SetVisibilityOfPointsInBox(bool bNewVisibility, FVector Center, FVector Extent)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets visibility of points within the given box.
- L349 _public function_ `void SetVisibilityOfPointsInBox(const bool& bNewVisibility, const FBox& Box)`
- L353 _public function_ `void SetVisibilityOfFirstPointByRay(bool bNewVisibility, FVector Origin, FVector Direction, float Radius)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets visibility of the first point hit by the given ray.
- L354 _public function_ `void SetVisibilityOfFirstPointByRay(const bool& bNewVisibility, const FLidarPointCloudRay& Ray, const float& Radius)`
- L358 _public function_ `void SetVisibilityOfPointsByRay(bool bNewVisibility, FVector Origin, FVector Direction, float Radius)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets visibility of points hit by the given ray.
- L359 _public function_ `void SetVisibilityOfPointsByRay(const bool& bNewVisibility, const FLidarPointCloudRay& Ray, const float& Radius)`
- L363 _public function_ `void HideAll()` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Marks all points hidden
- L367 _public function_ `void UnhideAll()` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Marks all points visible
- L370 _public function_ `void ExecuteActionOnAllPoints(TFunction<void(FLidarPointCloudPoint*)> Action, const bool& bVisibleOnly)` — Executes the provided action on each of the points.
- L373 _public function_ `void ExecuteActionOnPointsInSphere(TFunction<void(FLidarPointCloudPoint*)> Action, const FVector& Center, const float& Radius, const bool& bVisibleOnly)` — Executes the provided action on each of the points within the given sphere.
- L374 _public function_ `void ExecuteActionOnPointsInSphere(TFunction<void(FLidarPointCloudPoint*)> Action, FSphere Sphere, const bool& bVisibleOnly)`
- L381 _public function_ `void ExecuteActionOnPointsInBox(TFunction<void(FLidarPointCloudPoint*)> Action, const FVector& Center, const FVector& Extent, const bool& bVisibleOnly)` — Executes the provided action on each of the points within the given box.
- L382 _public function_ `void ExecuteActionOnPointsInBox(TFunction<void(FLidarPointCloudPoint*)> Action, const FBox& Box, const bool& bVisibleOnly)`
- L385 _public function_ `void ExecuteActionOnFirstPointByRay(TFunction<void(FLidarPointCloudPoint*)> Action, const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly)` — Executes the provided action on the first point hit by the given ray.
- L388 _public function_ `void ExecuteActionOnPointsByRay(TFunction<void(FLidarPointCloudPoint*)> Action, const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly)` — Executes the provided action on each of the points hit by the given ray.
- L392 _public function_ `void ApplyColorToAllPoints(const FColor& NewColor, const bool& bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to all points
- L396 _public function_ `void ApplyColorToPointsInSphere(FColor NewColor, FVector Center, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to all points within the sphere
- L397 _public function_ `void ApplyColorToPointsInSphere(const FColor& NewColor, FSphere Sphere, const bool& bVisibleOnly)`
- L405 _public function_ `void ApplyColorToPointsInBox(FColor NewColor, FVector Center, FVector Extent, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to all points within the box
- L406 _public function_ `void ApplyColorToPointsInBox(const FColor& NewColor, const FBox& Box, const bool& bVisibleOnly)`
- L410 _public function_ `void ApplyColorToFirstPointByRay(FColor NewColor, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to the first point hit by the given ray
- L411 _public function_ `void ApplyColorToFirstPointByRay(const FColor& NewColor, const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly)`
- L415 _public function_ `void ApplyColorToPointsByRay(FColor NewColor, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to all points hit by the given ray
- L416 _public function_ `void ApplyColorToPointsByRay(const FColor& NewColor, const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly)`
- L423 _public function_ `void MarkPointVisibilityDirty()` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — This should to be called if any manual modification to individual points' visibility has been made. If not marked dirty, the rendering may work sub-optimally.
- L427 _public prototype_ `void SelectByConvexVolume(FConvexVolume ConvexVolume, bool bAdditive, bool bApplyLocationOffset, bool bVisibleOnly);` — Set of editor helper functions
- L428 _public prototype_ `void SelectBySphere(FSphere Sphere, bool bAdditive, bool bApplyLocationOffset, bool bVisibleOnly);`
- L429 _public prototype_ `void HideSelected();`
- L430 _public prototype_ `void DeleteSelected();`
- L431 _public prototype_ `void InvertSelection();`
- L432 _public prototype_ `int64 NumSelectedPoints() const;`
- L433 _public prototype_ `bool HasSelectedPoints() const;`
- L435 _public prototype_ `template <typename T> void GetSelectedPointsAsCopies_Internal(TArray<FLidarPointCloudPoint, T>& SelectedPoints, FTransform Transform) const;`
- L436 _public prototype_ `void GetSelectedPointsAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FTransform& Transform) const;`
- L437 _public prototype_ `void GetSelectedPointsAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FTransform& Transform) const;`
- L438 _public prototype_ `void CalculateNormalsForSelection();`
- L439 _public prototype_ `void ClearSelection();`
- L440 _public prototype_ `void BuildStaticMeshBuffersForSelection(float CellSize, LidarPointCloudMeshing::FMeshBuffers* OutMeshBuffers, const FTransform& Transform);`
- L444 _public prototype_ `void SetSourcePath(const FString& NewSourcePath);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")`
- L447 _public prototype_ `void SetOptimizedForDynamicData(bool bNewOptimizedForDynamicData);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")`
- L454 _public function_ `void Initialize(const FBox& NewBounds)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Re-initializes the asset with new bounds. Warning: Will erase all currently held data!
- L461 _public prototype_ `void SetOptimalCollisionError();` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")`
- L465 _public function_ `void BuildCollision()` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Builds collision mesh for the cloud, using current collision settings
- L466 _public prototype_ `void BuildCollision(TFunction<void(bool)> CompletionCallback);`
- L469 _public prototype_ `void BuildCollisionWithCallback(UObject* WorldContextObject, FLatentActionInfo LatentInfo, bool& bSuccess);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo"))`
- L473 _public prototype_ `void RemoveCollision();` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes collision mesh from the cloud.
- L476 _public prototype_ `void BuildStaticMeshBuffers(float CellSize, LidarPointCloudMeshing::FMeshBuffers* OutMeshBuffers, const FTransform& Transform);` — Constructs and returns the MeshBuffers struct from the data
- L480 _public function_ `bool IsFullyLoaded() const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns true, if the cloud is fully and persistently loaded.
- L484 _public function_ `void LoadAllNodes()` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Persistently loads all nodes.
- L488 _public prototype_ `void SetLocationOffset(FVector Offset);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies given offset to this point cloud.
- L492 _public function_ `void CenterPoints()` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Centers this cloud
- L496 _public function_ `void RestoreOriginalCoordinates()` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Restores original coordinates
- L500 _public function_ `bool IsCentered() const` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Returns true, if the cloud has been centered.
- L504 _public prototype_ `void Reimport(UObject* WorldContextObject, bool bUseAsync, FLatentActionInfo LatentInfo, ELidarPointCloudAsyncMode& AsyncMode, float& Progress);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "AsyncMode"))` — Re-imports the cloud from it's original source file, overwriting any current point information.
- L505 _public prototype_ `void Reimport(const FLidarPointCloudAsyncParameters& AsyncParameters);`
- L513 _public prototype_ `bool Export(const FString& Filename);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Exports this Point Cloud to the given filename. Consult supported export formats. Returns true if successful
- L520 _public prototype_ `void InsertPoint(const FLidarPointCloudPoint& Point, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Inserts the given point into the Octree structure. If bRefreshPointsBounds is set to false, make sure you call RefreshBounds() manually or cloud centering may not work correctly.
- L527 _public function_ `void InsertPoints(const TArray<FLidarPointCloudPoint>& Points, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Inserts group of points into the Octree structure, multi-threaded. If bRefreshPointsBounds is set to false, make sure you call RefreshBounds() manually or cloud centering may not work correctly.
- L536 _public prototype_ `bool InsertPoints(FLidarPointCloudPoint* InPoints, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation, FThreadSafeBool* bCanceled = nullptr, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());` — Inserts group of points into the Octree structure, multi-threaded. If bRefreshPointsBounds is set to false, make sure you call RefreshBounds() manually or cloud centering may not work correctly. Can be optionally passed a cancellation pointer - if it ever becomes non-null with value of true, process will be canceled. May also provide progress callback, called approximately every 1% of progress. Returns false if canceled.
- L537 _public prototype_ `bool InsertPoints(const FLidarPointCloudPoint* InPoints, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation, FThreadSafeBool* bCanceled = nullptr, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L538 _public prototype_ `bool InsertPoints(FLidarPointCloudPoint** InPoints, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation, FThreadSafeBool* bCanceled = nullptr, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L539 _public prototype_ `bool InsertPoints_NoLock(FLidarPointCloudPoint* InPoints, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation, FThreadSafeBool* bCanceled = nullptr, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L540 _public prototype_ `bool InsertPoints_NoLock(const FLidarPointCloudPoint* InPoints, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation, FThreadSafeBool* bCanceled = nullptr, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L541 _public prototype_ `bool InsertPoints_NoLock(FLidarPointCloudPoint** InPoints, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation, FThreadSafeBool* bCanceled = nullptr, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L545 _public function_ `void RemovePoint(FLidarPointCloudPoint Point)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Attempts to remove the given point.
- L550 _public function_ `void RemovePoint_NoLock(FLidarPointCloudPoint Point)`
- L554 _public function_ `void RemovePoint(const FLidarPointCloudPoint* Point)`
- L559 _public function_ `void RemovePoint_NoLock(const FLidarPointCloudPoint* Point)`
- L565 _public function_ `void RemovePoints(TArray<FLidarPointCloudPoint*>& Points)` — Removes points in bulk
- L570 _public function_ `void RemovePoints(TArray64<FLidarPointCloudPoint*>& Points)`
- L575 _public function_ `void RemovePoints_NoLock(TArray<FLidarPointCloudPoint*>& Points)`
- L576 _public function_ `void RemovePoints_NoLock(TArray64<FLidarPointCloudPoint*>& Points)`
- L580 _public function_ `void RemovePointsInSphere(FVector Center, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes all points within the given sphere
- L581 _public function_ `void RemovePointsInSphere(FSphere Sphere, const bool& bVisibleOnly)`
- L589 _public function_ `void RemovePointsInBox(FVector Center, FVector Extent, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes all points within the given box
- L590 _public function_ `void RemovePointsInBox(const FBox& Box, const bool& bVisibleOnly)`
- L594 _public function_ `void RemoveFirstPointByRay(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes the first point hit by the given ray
- L595 _public function_ `void RemoveFirstPointByRay(const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly)`
- L599 _public function_ `void RemovePointsByRay(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes all points hit by the given ray
- L600 _public function_ `void RemovePointsByRay(const FLidarPointCloudRay& Ray, const float& Radius, const bool& bVisibleOnly)`
- L604 _public function_ `void RemoveHiddenPoints()` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes all hidden points
- L608 _public function_ `bool SetData(const TArray<FLidarPointCloudPoint>& Points)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Reinitializes the cloud with the new set of data.
- L609 _public function_ `bool SetData(TArray<FLidarPointCloudPoint*>& Points)`
- L610 _public function_ `bool SetData(const TArray64<FLidarPointCloudPoint>& Points)`
- L611 _public function_ `bool SetData(TArray64<FLidarPointCloudPoint*>& Points)`
- L612 _public prototype_ `bool SetData(const FLidarPointCloudPoint* Points, const int64& Count, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L613 _public prototype_ `bool SetData(FLidarPointCloudPoint** Points, const int64& Count, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L617 _public function_ `void Merge(TArray<ULidarPointCloud*> PointCloudsToMerge)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Merges this point cloud with the ones provided
- L618 _public prototype_ `void Merge(TArray<ULidarPointCloud*> PointCloudsToMerge, TFunction<void(void)> ProgressCallback);`
- L622 _public function_ `void MergeSingle(ULidarPointCloud* PointCloudToMerge)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Merges this point cloud with the one provided
- L626 _public prototype_ `void CalculateNormals(FLatentActionInfo LatentInfo);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (Latent, LatentInfo = "LatentInfo"))` — Calculates Normals for this point cloud
- L632 _public prototype_ `void CalculateNormals(TArray64<FLidarPointCloudPoint*>* Points, TFunction<void(void)> CompletionCallback);` — Calculates Normals for the provided points If a nullptr is passed as Points, the calculation will be executed on the whole cloud.
- L635 _public prototype_ `virtual bool GetPhysicsTriMeshData(FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;`
- L636 _public prototype_ `virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const override;`
- L637 _public function_ `virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override`
- L638 _public function_ `virtual bool WantsNegXTriMesh() override`
- L641 _public prototype_ `UBodySetup* GetBodySetup();`
- L645 _public prototype_ `void GetPointsInFrustum(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FConvexVolume& Frustum, const bool& bVisibleOnly);` — `UE_DEPRECATED(4.27, "Use GetPointsInConvexVolume instead.")`
- L647 _public prototype_ `void GetPointsInFrustum(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FConvexVolume& Frustum, const bool& bVisibleOnly);` — `UE_DEPRECATED(4.27, "Use GetPointsInConvexVolume instead.")`
- L652 _public prototype_ `static void AlignClouds(TArray<ULidarPointCloud*> PointCloudsToAlign);` — Aligns provided clouds based on the relative offset between their Original Coordinates. Retains overall centering of the group.
- L658 _public function_ `static ULidarPointCloud* CreateFromFile(const FString& Filename, TSharedPtr<struct FLidarPointCloudImportSettings> ImportSettings = nullptr, UObject* InParent = (UObject*)GetTransientPackage(), FName InName = NAME_None, EObjectFlags Flags = RF_NoFlags)` — Returns new Point Cloud object imported using the settings provided. Use nullptr as ImportSettings parameter to use default set of settings instead.
- L662 _public prototype_ `static ULidarPointCloud* CreateFromFile(const FString& Filename, const FLidarPointCloudAsyncParameters& AsyncParameters, TSharedPtr<struct FLidarPointCloudImportSettings> ImportSettings = nullptr, UObject* InParent = (UObject*)GetTransientPackage(), FName InName = NAME_None, EObjectFlags Flags = RF_NoFlags);`
- L669 _public prototype_ `template<typename T> static ULidarPointCloud* CreateFromData(T Points, const int64& Count, const FLidarPointCloudAsyncParameters& AsyncParameters);` — Returns new Point Cloud object created from the data provided. Warning: If using Async, make sure the data does not get invalidated during processing!
- L670 _public prototype_ `static ULidarPointCloud* CreateFromData(const TArray<FLidarPointCloudPoint>& Points, const bool& bUseAsync);`
- L671 _public prototype_ `static ULidarPointCloud* CreateFromData(const TArray64<FLidarPointCloudPoint>& Points, const bool& bUseAsync);`
- L672 _public prototype_ `static ULidarPointCloud* CreateFromData(const TArray<FLidarPointCloudPoint>& Points, const FLidarPointCloudAsyncParameters& AsyncParameters);`
- L673 _public prototype_ `static ULidarPointCloud* CreateFromData(const TArray64<FLidarPointCloudPoint>& Points, const FLidarPointCloudAsyncParameters& AsyncParameters);`
- L674 _public prototype_ `static ULidarPointCloud* CreateFromData(TArray<FLidarPointCloudPoint*>& Points, const bool& bUseAsync);`
- L675 _public prototype_ `static ULidarPointCloud* CreateFromData(TArray64<FLidarPointCloudPoint*>& Points, const bool& bUseAsync);`
- L676 _public prototype_ `static ULidarPointCloud* CreateFromData(TArray<FLidarPointCloudPoint*>& Points, const FLidarPointCloudAsyncParameters& AsyncParameters);`
- L677 _public prototype_ `static ULidarPointCloud* CreateFromData(TArray64<FLidarPointCloudPoint*>& Points, const FLidarPointCloudAsyncParameters& AsyncParameters);`
- L680 _public prototype_ `static FBox CalculateBoundsFromPoints(const FLidarPointCloudPoint* Points, const int64& Count);` — Returns bounds fitting the given list of points
- L681 _public prototype_ `static FBox CalculateBoundsFromPoints(FLidarPointCloudPoint** Points, const int64& Count);`
- L685 _private function_ `void FinishPhysicsAsyncCook(TSharedRef<FLidarPointCloudNotification, ESPMode::ThreadSafe> Notification)` — Once async physics cook is done, create needed state
- L686 _private prototype_ `void FinishPhysicsAsyncCook(bool bSuccess, TSharedRef<FLidarPointCloudNotification, ESPMode::ThreadSafe> Notification);`
- L688 _private prototype_ `void InitializeCollisionRendering();`
- L689 _private prototype_ `void ReleaseCollisionRendering(bool bDestroyAfterRelease);`
- L692 _private prototype_ `template <typename T> void GetPoints_Internal(TArray<FLidarPointCloudPoint*, T>& Points, int64 StartIndex = 0, int64 Count = -1);`
- L694 _private prototype_ `template <typename T> void GetPointsInSphere_Internal(TArray<FLidarPointCloudPoint*, T>& SelectedPoints, FSphere Sphere, const bool& bVisibleOnly);`
- L696 _private prototype_ `template <typename T> void GetPointsInBox_Internal(TArray<FLidarPointCloudPoint*, T>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly);`
- L698 _private prototype_ `template <typename T> void GetPointsInConvexVolume_Internal(TArray<FLidarPointCloudPoint*, T>& SelectedPoints, const FConvexVolume& ConvexVolume, const bool& bVisibleOnly);`
- L700 _private prototype_ `template <typename T> void GetPointsAsCopies_Internal(TArray<FLidarPointCloudPoint, T>& Points, bool bReturnWorldSpace, int64 StartIndex = 0, int64 Count = -1) const;`
- L702 _private prototype_ `template <typename T> void GetPointsInSphereAsCopies_Internal(TArray<FLidarPointCloudPoint, T>& SelectedPoints, FSphere Sphere, const bool& bVisibleOnly, bool bReturnWorldSpace) const;`
- L704 _private prototype_ `template <typename T> void GetPointsInBoxAsCopies_Internal(TArray<FLidarPointCloudPoint, T>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly, bool bReturnWorldSpace) const;`
- L707 _private prototype_ `template<typename T> bool InsertPoints_Internal(T InPoints, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation, FThreadSafeBool* bCanceled = nullptr, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L709 _private prototype_ `template<typename T> bool InsertPoints_NoLock_Internal(T InPoints, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector& Translation, FThreadSafeBool* bCanceled = nullptr, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`
- L712 _private prototype_ `template<typename T> bool SetData_Internal(T Points, const int64& Count, TFunction<void(float)> ProgressCallback = TFunction<void(float)>());`

#### struct `ULidarPointCloud::FLidarPointCloudAssetRegistryCache`  
`struct FLidarPointCloudAssetRegistryCache`  
_L130-134_
- desc: Used for caching the asset registry tag data.
- L132 _public member_ `FString PointCount;`
- L133 _public member_ `FString ApproxSize;`

#### class `ULidarPointCloud::FLidarPointCloudNotificationManager`  
`class FLidarPointCloudNotificationManager`  
_L145-155_
- desc: Notifications we hold on to, that indicate status and progress.
- L147 _private member_ `TArray<TSharedRef<FLidarPointCloudNotification, ESPMode::ThreadSafe>> Notifications;`
- L148 _private member_ `TWeakObjectPtr<ULidarPointCloud> Owner;`
- L151 _public function_ `FLidarPointCloudNotificationManager() : FLidarPointCloudNotificationManager(nullptr)`
- L152 _public function_ `FLidarPointCloudNotificationManager(TWeakObjectPtr<ULidarPointCloud> Owner) : Owner(Owner)`
- L153 _public prototype_ `TSharedRef<FLidarPointCloudNotification, ESPMode::ThreadSafe> Create(const FString& Text, FThreadSafeBool* bCancelPtr = nullptr, const FString& Icon = "Cla`
- L154 _public prototype_ `void CloseAll();`

#### struct `FLidarPointCloudTraceHit`  
`struct FLidarPointCloudTraceHit`  
_L716-737_
- reflection: `USTRUCT(BlueprintType)`
- L722 _public member_ `TObjectPtr<ALidarPointCloudActor> Actor = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")`
- L725 _public member_ `TObjectPtr<ULidarPointCloudComponent> Component = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")`
- L728 _public member_ `TArray<FLidarPointCloudPoint> Points;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")`
- L730 _public function_ `FLidarPointCloudTraceHit()`
- L732 _public function_ `FLidarPointCloudTraceHit(ALidarPointCloudActor* Actor, ULidarPointCloudComponent* Component) : Actor(Actor) , Component(Component)`

#### class `ULidarPointCloudBlueprintLibrary`  
`class ULidarPointCloudBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L743-866_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint library for the Point Cloud assets
- L750 _public function_ `static ULidarPointCloud* CreatePointCloudEmpty()` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (DisplayName = "Create Empty Lidar Point Cloud"))` — Returns new, empty Point Cloud object.
- L757 _public prototype_ `static void CreatePointCloudFromFile(UObject* WorldContextObject, const FString& Filename, bool bUseAsync, FLatentActionInfo LatentInfo, ELidarPointCloudAsyncMode& AsyncMode, float& Progress, ULidarPointCloud*& PointCloud);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "AsyncMode", DisplayName = "Create Lidar Point Cloud From File"))` — Returns new Point Cloud object imported using default settings. If using Async, the process runs in the background without blocking the game thread.
- L758 _public prototype_ `static void CreatePointCloudFromFile(UObject* WorldContextObject, const FString& Filename, bool bUseAsync, FLatentActionInfo LatentInfo, TSharedPtr<struct FLidarPointCloudImportSettings> ImportSettings, ELidarPointCloudAsyncMode& AsyncMode, float& Progress, ULidarPointCloud*& PointCloud);`
- L765 _public prototype_ `static void CreatePointCloudFromData(UObject* WorldContextObject, const TArray<FLidarPointCloudPoint>& Points, bool bUseAsync, FLatentActionInfo LatentInfo, ELidarPointCloudAsyncMode& AsyncMode, float& Progress, ULidarPointCloud*& PointCloud);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "AsyncMode", DisplayName = "Create Lidar Point Cloud From Data"))` — Returns new Point Cloud object created from the data provided. Warning: If using Async, make sure the data does not get invalidated during processing!
- L773 _public function_ `static bool ExportPointCloudToFile(ULidarPointCloud* PointCloud, const FString& Filename)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Exports the Point Cloud to the given filename. Consult supported export formats. Returns true if successful
- L777 _public function_ `static void AlignClouds(TArray<ULidarPointCloud*> PointCloudsToAlign)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Aligns provided clouds based on the relative offset between their Original Coordinates. Retains overall centering of the group.
- L781 _public prototype_ `static bool ArePointsInSphere(UObject* WorldContextObject, FVector Center, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Returns true if there are any points within the given sphere.
- L785 _public prototype_ `static bool ArePointsInBox(UObject* WorldContextObject, FVector Center, FVector Extent, bool bVisibleOnly);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Returns true if there are any points within the given box.
- L789 _public prototype_ `static bool ArePointsByRay(UObject* WorldContextObject, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Returns true if there are any points hit by the given ray.
- L793 _public prototype_ `static void GetPointsInSphereAsCopies(UObject* WorldContextObject, TArray<FLidarPointCloudPoint>& SelectedPoints, FVector Center, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Returns an array with copies of points within the given sphere
- L797 _public prototype_ `static void GetPointsInBoxAsCopies(UObject* WorldContextObject, TArray<FLidarPointCloudPoint>& SelectedPoints, FVector Center, FVector Extent, const bool& bVisibleOnly);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Returns an array with copies of points within the given box
- L801 _public prototype_ `static bool LineTraceSingle(UObject* WorldContextObject, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly, FLidarPointCloudTraceHit& Hit);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject", DisplayName = "LineTraceForLidarPointCloud", Keywords = "raycast"))` — Does a collision trace along the given line and returns the first blocking hit encountered.
- L805 _public prototype_ `static bool LineTraceMulti(UObject* WorldContextObject, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly, TArray<FLidarPointCloudTraceHit>& Hits);` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject", DisplayName = "LineTraceMultiForLidarPointCloud", Keywords = "raycast"))` — Does a collision trace along the given line and returns all hits encountered up to and including the first blocking hit.
- L809 _public prototype_ `static void SetVisibilityOfPointsInSphere(UObject* WorldContextObject, bool bNewVisibility, FVector Center, float Radius);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Sets visibility of points within the given sphere.
- L813 _public prototype_ `static void SetVisibilityOfPointsInBox(UObject* WorldContextObject, bool bNewVisibility, FVector Center, FVector Extent);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Sets visibility of points within the given box.
- L817 _public prototype_ `static void SetVisibilityOfFirstPointByRay(UObject* WorldContextObject, bool bNewVisibility, FVector Origin, FVector Direction, float Radius);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Sets visibility of the first point hit by the given ray.
- L821 _public prototype_ `static void SetVisibilityOfPointsByRay(UObject* WorldContextObject, bool bNewVisibility, FVector Origin, FVector Direction, float Radius);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Sets visibility of points hit by the given ray.
- L825 _public prototype_ `static void ApplyColorToPointsInSphere(UObject* WorldContextObject, FColor NewColor, FVector Center, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Applies the given color to all points within the sphere
- L829 _public prototype_ `static void ApplyColorToPointsInBox(UObject* WorldContextObject, FColor NewColor, FVector Center, FVector Extent, bool bVisibleOnly);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Applies the given color to all points within the box
- L833 _public prototype_ `static void ApplyColorToFirstPointByRay(UObject* WorldContextObject, FColor NewColor, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Applies the given color to the first point hit by the given ray
- L837 _public prototype_ `static void ApplyColorToPointsByRay(UObject* WorldContextObject, FColor NewColor, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Applies the given color to all points hit by the given ray
- L841 _public prototype_ `static void RemovePointsInSphere(UObject* WorldContextObject, FVector Center, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Removes all points within the given sphere
- L845 _public prototype_ `static void RemovePointsInBox(UObject* WorldContextObject, FVector Center, FVector Extent, bool bVisibleOnly);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Removes all points within the given box
- L849 _public prototype_ `static void RemoveFirstPointByRay(UObject* WorldContextObject, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Removes the first point hit by the given ray
- L853 _public prototype_ `static void RemovePointsByRay(UObject* WorldContextObject, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly);` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud", meta = (WorldContext = "WorldContextObject"))` — Removes all points hit by the given ray
- L857 _public function_ `static void NormalFromVector(UPARAM(ref) FLidarPointCloudNormal& Normal, FVector Vector)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets the given normal using provided vector
- L861 _public function_ `static FVector Conv_LidarPointCloudNormalToVector(const FLidarPointCloudNormal& Normal)` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Normal to Vector", CompactNodeTitle = "->", BlueprintAutocast), Category = "Lidar Point Cloud")` — Converts a Lidar Point Cloud Normal to a Vector
- L865 _public function_ `static FLidarPointCloudNormal Conv_VectorToLidarPointCloudNormal(const FVector& Vector)` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Vector to Normal", CompactNodeTitle = "->", BlueprintAutocast), Category = "Lidar Point Cloud")` — Converts a Vector to a Lidar Point Cloud Normal

#### class `ALidarClippingVolume`  
`class ALidarClippingVolume : public AVolume`  
_L869-889_
- reflection: `UCLASS(hidecategories = (Collision, Brush, Attachment, Physics, Volume, BrushBuilder), MinimalAPI)`
- inherits: `AVolume`
- L875 _public member_ `bool bEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clipping Volume")`
- L879 _public member_ `ELidarClippingVolumeMode Mode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clipping Volume")` — Affects how this volume affects points
- L886 _public member_ `int32 Priority;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clipping Volume")` — Determines the processing order of the nodes, in case they overlap. Higher values take priority over lower ones.
- L888 _public prototype_ `ALidarClippingVolume();`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace LidarPointCloudMeshing`
- L59 _delegate_ `DECLARE_EVENT(ULidarPointCloud, FOnPointCloudChanged);` — Used to notify the component it should refresh its state.
- L59 _prototype_ `DECLARE_EVENT(ULidarPointCloud, FOnPointCloudChanged);` — Used to notify the component it should refresh its state.

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/LidarPointCloudActor.h` (Public)


#### class `ALidarPointCloudActor`  
`class ALidarPointCloudActor : public AActor`  
_L12-34_
- reflection: `UCLASS(BlueprintType, hidecategories = ("Materials"))`
- inherits: `AActor`
- L18 _private member_ `TObjectPtr<ULidarPointCloudComponent> PointCloudComponent;` — `UPROPERTY(Category = PointCloudActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Rendering,Components|LidarPointCloud", AllowPrivateAccess = "true"))`
- L22 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L27 _public function_ `ULidarPointCloudComponent* GetPointCloudComponent() const` — Returns PointCloudComponent subobject
- L30 _public prototype_ `ULidarPointCloud* GetPointCloud() const;` — `UFUNCTION(BlueprintPure, Category = "Components|LidarPointCloud")`
- L33 _public prototype_ `void SetPointCloud(ULidarPointCloud *InPointCloud);` — `UFUNCTION(BlueprintCallable, Category = "Components|LidarPointCloud")`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/LidarPointCloudComponent.h` (Public)


#### enum `ELidarPointCloudSpriteOrientation`  
`enum class ELidarPointCloudSpriteOrientation : uint8`  
_L14-20_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `PreferFacingCamera` — The sprites will face camera, even if Normals are available.
- L19 _public enumerator_ `PreferFacingNormal` — The sprites will attempt to face Normals, if available, or fall back to facing camera otherwise.

#### class `ULidarPointCloudComponent`  
`class ULidarPointCloudComponent : public UMeshComponent`  
_L24-620_
- reflection: `UCLASS(ClassGroup=Rendering, ShowCategories = (Rendering), HideCategories = (Object, LOD, Physics, Activation, Materials, Cooking, Input, HLOD, Mobile), meta = (BlueprintSpawnableComponent))`
- inherits: `UMeshComponent`
- desc: Component that allows you to render specified point cloud section
- L30 _private member_ `TObjectPtr<ULidarPointCloud> PointCloud;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lidar Point Cloud", meta = (AllowPrivateAccess = "true"))`
- L37 _private member_ `TObjectPtr<UMaterialInterface> CustomMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material", meta = (AllowPrivateAccess = "true"))` — Allows using custom-built material for the point cloud. Set to None to use the default one instead.
- L45 _public member_ `float PointSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (ClampMin = "0.0"))` — Use to tweak the size of the points. Set to 0 to switch to 1 pixel points.
- L49 _public member_ `ELidarPointCloudScalingMethod ScalingMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Determines how the points will be scaled
- L57 _public member_ `float GapFillingStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", meta = (ClampMin = "0.0"))` — If set to > 0, it attempts to close gaps between points. Setting this too high may cause visual artifacts. This setting may interfere with AO
- L61 _public member_ `ELidarPointCloudColorationMode ColorSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Specifies which source to use for point colors.
- L66 _private member_ `ELidarPointCloudSpriteShape PointShape;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance", BlueprintSetter = SetPointShape, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage="Use GetPointShape() / SetPointShape() instead."))` — Affects the shape of points.
- L71 _public member_ `ELidarPointCloudSpriteOrientation PointOrientation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Affects the orientation of points.
- L78 _public member_ `TMap<int32, FLinearColor> ClassificationColors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Used with the Classification source. Maps the given classification ID to a color.
- L82 _public member_ `FLinearColor ElevationColorBottom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Appearance")` — Specifies the bottom color of the elevation-based gradient.
- L86 _public member_ `FLinearColor ElevationColorTop;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Appearance")` — Specifies the top color of the elevation-based gradient.
- L93 _public member_ `float PointSizeBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Appearance", meta = (ClampMin = "0.0", ClampMax = "0.15"))` — Larger values will help mask LOD transition areas, but too large values will lead to loss of detail. Values in range 0.035 - 0.05 seem to produce best overall results.
- L96 _public member_ `FVector4 Saturation;` — `UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, Category = "Color Adjustment", meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "saturation"))`
- L99 _public member_ `FVector4 Contrast;` — `UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, Category = "Color Adjustment", meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "contrast"))`
- L102 _public member_ `FVector4 Gamma;` — `UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, Category = "Color Adjustment", meta = (UIMin = "0.0", UIMax = "2.0", Delta = "0.01", ColorGradingMode = "gamma"))`
- L106 _public member_ `FVector4 Gain;` — `UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, Category = "Color Adjustment", meta = (UIMin = "0.0", UIMax = "1.0", Delta = "0.01", ColorGradingMode = "gain"))` — Affects the emissive strength of the color. Useful to create Bloom and light bleed effects.
- L110 _public member_ `FVector4 Offset;` — `UPROPERTY(interp, EditAnywhere, BlueprintReadWrite, Category = "Color Adjustment", meta = (UIMin = "-1.0", UIMax = "1.0", Delta = "0.001", ColorGradingMode = "offset", SupportDynamicSliderMaxValue = "true", SupportDynamicSliderMinValue = "true"))` — Applied additively, 0 being neutral.
- L114 _public member_ `FLinearColor ColorTint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Adjustment")` — Specifies the tint to apply to the points.
- L118 _public member_ `float IntensityInfluence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Adjustment", meta = (ClampMin = "0", ClampMax = "1"))` — Specifies the influence of Intensity data, if available, on the overall color.
- L126 _public member_ `bool bUseFrustumCulling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")` — If enabled, points outside of the visible frustum will not be rendered. While most project should leave this enabled, disabling it may help with the data streaming lag when shooting cinematics.
- L133 _public member_ `int32 MinDepth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Rendering", meta = (ClampMin = "0"))` — Minimum Depth from which the nodes should be rendered. 0 to disable.
- L140 _public member_ `int32 MaxDepth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Rendering")` — Maximum Depth to which the nodes should be rendered. -1 to disable.
- L144 _public member_ `bool bDrawNodeBounds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Rendering")` — Enabling this will cause the visible nodes to render their bounds.
- L148 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(Transient)`
- L150 _private member_ `TObjectPtr<UMaterialInterface> BaseMaterial;` — `UPROPERTY(Transient)`
- L152 _private member_ `TObjectPtr<UMaterialInterface> BaseMaterialMasked;` — `UPROPERTY(Transient)`
- L155 _private member_ `TWeakPtr<FViewportClient> OwningViewportClient;` — Pointer to the viewport client of the owning editor, or null, if this is a game object.
- L158 _public prototype_ `ULidarPointCloudComponent();`
- L161 _public function_ `ULidarPointCloud* GetPointCloud() const` — `UFUNCTION(BlueprintPure, Category = "Components|LidarPointCloud")`
- L163 _public function_ `inline TWeakPtr<FViewportClient> GetOwningViewportClient() const`
- L164 _public function_ `inline bool IsOwnedByEditor() const`
- L168 _public function_ `bool HasPointsInSphere(FVector Center, float Radius, bool bVisibleOnly) const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns true if there are any points within the given sphere.
- L172 _public function_ `bool HasPointsInSphere(const FSphere& Sphere, bool bVisibleOnly) const`
- L179 _public function_ `bool HasPointsInBox(FVector Center, FVector Extent, bool bVisibleOnly) const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns true if there are any points within the given box.
- L183 _public function_ `bool HasPointsInBox(const FBox& Box, bool bVisibleOnly) const`
- L190 _public function_ `bool HasPointsByRay(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly) const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")` — Returns true if there are any points hit by the given ray.
- L194 _public function_ `bool HasPointsByRay(const FLidarPointCloudRay& Ray, float Radius, bool bVisibleOnly) const`
- L200 _public function_ `TArray<FLidarPointCloudPoint> GetSelectedPointsAsCopies(bool bReturnWorldSpace) const` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud")`
- L209 _public function_ `void GetSelectedPointsAsCopies(TArray<FLidarPointCloudPoint>& Points, bool bReturnWorldSpace) const`
- L216 _public function_ `void GetSelectedPointsAsCopies(TArray64<FLidarPointCloudPoint>& Points, bool bReturnWorldSpace) const`
- L226 _public function_ `void GetPointsInSphere(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FVector& Center, const float& Radius, const bool& bVisibleOnly)` — Populates the array with the list of points within the given sphere.
- L227 _public function_ `void GetPointsInSphere(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FVector& Center, const float& Radius, const bool& bVisibleOnly)`
- L228 _public function_ `void GetPointsInSphere(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly)`
- L235 _public function_ `void GetPointsInSphere(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly)`
- L244 _public function_ `void GetPointsInBox(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FVector& Center, const FVector& Extent, const bool& bVisibleOnly)` — Populates the array with the list of points within the given box.
- L245 _public function_ `void GetPointsInBox(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FVector& Center, const FVector& Extent, const bool& bVisibleOnly)`
- L246 _public function_ `void GetPointsInBox(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly)`
- L253 _public function_ `void GetPointsInBox(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly)`
- L266 _public function_ `TArray<FLidarPointCloudPoint> GetPointsInSphereAsCopies(FVector Center, float Radius, bool bVisibleOnly, bool bReturnWorldSpace)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Populates the array with copies of points within the given sphere. If ReturnWorldSpace is selected, the points' locations will be converted into absolute value, otherwise they will be relative to the center of the cloud.
- L273 _public function_ `void GetPointsInSphereAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly, const bool& bReturnWorldSpace)`
- L281 _public function_ `void GetPointsInSphereAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly, const bool& bReturnWorldSpace)`
- L295 _public function_ `TArray<FLidarPointCloudPoint> GetPointsInBoxAsCopies(FVector Center, FVector Extent, bool bVisibleOnly, bool bReturnWorldSpace)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Populates the array with copies of points within the given box. If ReturnWorldSpace is selected, the points' locations will be converted into absolute value, otherwise they will be relative to the center of the cloud.
- L301 _public function_ `void GetPointsInBoxAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly, const bool& bReturnWorldSpace)`
- L309 _public function_ `void GetPointsInBoxAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly, const bool& bReturnWorldSpace)`
- L320 _public function_ `bool LineTraceSingle(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly, FLidarPointCloudPoint& PointHit)` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (Keywords = "raycast"))` — Performs a raycast test against the point cloud. Returns the pointer if hit or nullptr otherwise.
- L331 _public function_ `FLidarPointCloudPoint* LineTraceSingle(FLidarPointCloudRay Ray, float Radius, bool bVisibleOnly)`
- L343 _public function_ `bool LineTraceMulti(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly, bool bReturnWorldSpace, TArray<FLidarPointCloudPoint>& OutHits)` — `UFUNCTION(BlueprintPure, Category = "Lidar Point Cloud", meta = (Keywords = "raycast"))` — Performs a raycast test against the point cloud. Populates OutHits array with the results. If ReturnWorldSpace is selected, the points' locations will be converted into absolute value, otherwise they will be relative to the center of the cloud. Returns true it anything has been hit.
- L347 _public function_ `bool LineTraceMulti(FLidarPointCloudRay Ray, float Radius, bool bVisibleOnly, bool bReturnWorldSpace, TArray<FLidarPointCloudPoint>& OutHits)`
- L357 _public function_ `bool LineTraceMulti(FLidarPointCloudRay Ray, float Radius, bool bVisibleOnly, TArray<FLidarPointCloudPoint*>& OutHits)`
- L364 _public function_ `void SetVisibilityOfPointsInSphere(bool bNewVisibility, FVector Center, float Radius)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets visibility of points within the given sphere.
- L365 _public function_ `void SetVisibilityOfPointsInSphere(const bool& bNewVisibility, const FSphere& Sphere)`
- L375 _public function_ `void SetVisibilityOfPointsInBox(bool bNewVisibility, FVector Center, FVector Extent)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets visibility of points within the given box.
- L376 _public function_ `void SetVisibilityOfPointsInBox(const bool& bNewVisibility, const FBox& Box)`
- L386 _public function_ `void SetVisibilityOfFirstPointByRay(bool bNewVisibility, FVector Origin, FVector Direction, float Radius)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets visibility of the first point hit by the given ray.
- L387 _public function_ `void SetVisibilityOfFirstPointByRay(bool bNewVisibility, FLidarPointCloudRay Ray, float Radius)`
- L397 _public function_ `void SetVisibilityOfPointsByRay(bool bNewVisibility, FVector Origin, FVector Direction, float Radius)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Sets visibility of points hit by the given ray.
- L398 _public function_ `void SetVisibilityOfPointsByRay(bool bNewVisibility, FLidarPointCloudRay Ray, float Radius)`
- L407 _public function_ `void ExecuteActionOnPointsInSphere(TFunction<void(FLidarPointCloudPoint*)> Action, const FVector& Center, const float& Radius, const bool& bVisibleOnly)` — Executes the provided action on each of the points within the given sphere.
- L408 _public function_ `void ExecuteActionOnPointsInSphere(TFunction<void(FLidarPointCloudPoint*)> Action, const FSphere& Sphere, const bool& bVisibleOnly)`
- L417 _public function_ `void ExecuteActionOnPointsInBox(TFunction<void(FLidarPointCloudPoint*)> Action, const FVector& Center, const FVector& Extent, const bool& bVisibleOnly)` — Executes the provided action on each of the points within the given box.
- L418 _public function_ `void ExecuteActionOnPointsInBox(TFunction<void(FLidarPointCloudPoint*)> Action, const FBox& Box, const bool& bVisibleOnly)`
- L427 _public function_ `void ExecuteActionOnFirstPointByRay(TFunction<void(FLidarPointCloudPoint*)> Action, FLidarPointCloudRay Ray, float Radius, bool bVisibleOnly)` — Executes the provided action on the first point hit by the given ray.
- L436 _public function_ `void ExecuteActionOnPointsByRay(TFunction<void(FLidarPointCloudPoint*)> Action, FLidarPointCloudRay Ray, float Radius, bool bVisibleOnly)` — Executes the provided action on each of the points hit by the given ray.
- L446 _public function_ `void ApplyColorToPointsInSphere(FColor NewColor, FVector Center, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to all points within the sphere
- L447 _public function_ `void ApplyColorToPointsInSphere(const FColor& NewColor, const FSphere& Sphere, const bool& bVisibleOnly)`
- L457 _public function_ `void ApplyColorToPointsInBox(FColor NewColor, FVector Center, FVector Extent, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to all points within the box
- L458 _public function_ `void ApplyColorToPointsInBox(const FColor& NewColor, const FBox& Box, const bool& bVisibleOnly)`
- L468 _public function_ `void ApplyColorToFirstPointByRay(FColor NewColor, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to the first point hit by the given ray
- L469 _public function_ `void ApplyColorToFirstPointByRay(const FColor& NewColor, FLidarPointCloudRay Ray, float Radius, bool bVisibleOnly)`
- L479 _public function_ `void ApplyColorToPointsByRay(FColor NewColor, FVector Origin, FVector Direction, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Applies the given color to all points hit by the given ray
- L480 _public function_ `void ApplyColorToPointsByRay(const FColor& NewColor, FLidarPointCloudRay Ray, float Radius, bool bVisibleOnly)`
- L490 _public function_ `void RemovePointsInSphere(FVector Center, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes all points within the given sphere
- L491 _public function_ `void RemovePointsInSphere(const FSphere& Sphere, const bool& bVisibleOnly)`
- L501 _public function_ `void RemovePointsInBox(FVector Center, FVector Extent, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes all points within the given box
- L502 _public function_ `void RemovePointsInBox(const FBox& Box, const bool& bVisibleOnly)`
- L512 _public function_ `void RemoveFirstPointByRay(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes the first point hit by the given ray
- L513 _public function_ `void RemoveFirstPointByRay(const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly)`
- L523 _public function_ `void RemovePointsByRay(FVector Origin, FVector Direction, float Radius, bool bVisibleOnly)` — `UFUNCTION(BlueprintCallable, Category = "Lidar Point Cloud")` — Removes all points hit by the given ray
- L524 _public function_ `void RemovePointsByRay(FLidarPointCloudRay Ray, float Radius, const bool& bVisibleOnly)`
- L533 _public prototype_ `void SelectByConvexVolume(FConvexVolume ConvexVolume, bool bAdditive, bool bVisibleOnly);`
- L534 _public prototype_ `void SelectBySphere(FSphere Sphere, bool bAdditive, bool bVisibleOnly);`
- L535 _public prototype_ `void HideSelected();`
- L536 _public prototype_ `void DeleteSelected();`
- L537 _public prototype_ `void InvertSelection();`
- L538 _public prototype_ `int64 NumSelectedPoints();`
- L539 _public prototype_ `void ClearSelection();`
- L544 _public prototype_ `void SetPointCloud(ULidarPointCloud *InPointCloud);` — `UFUNCTION(BlueprintCallable, Category = "Components|LidarPointCloud")`
- L548 _public function_ `inline ELidarPointCloudSpriteShape GetPointShape() const` — `UFUNCTION(BlueprintPure, Category = "Components|LidarPointCloud")` — Returns the current Point Shape
- L552 _public prototype_ `void SetPointShape(ELidarPointCloudSpriteShape NewPointShape);` — `UFUNCTION(BlueprintCallable, Category = "Components|LidarPointCloud")` — Sets new Point Shape
- L556 _public prototype_ `void ApplyRenderingParameters();` — `UFUNCTION(BlueprintCallable, Category = "Components|LidarPointCloud|Rendering")` — Applies specified rendering parameters (Brightness, Saturation, etc) to the selected material
- L560 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L561 _public prototype_ `virtual void PostLoad() override;`
- L565 _public function_ `virtual int32 GetNumMaterials() const override`
- L566 _public function_ `virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override`
- L567 _public prototype_ `virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* InMaterial) override;`
- L571 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L572 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L573 _public function_ `virtual void PostEditImport() override`
- L582 _public prototype_ `virtual UBodySetup* GetBodySetup() override;`
- L585 _public function_ `bool ShouldRenderFacingNormals() const` — Returns true if the component should be rendered facing normals
- L589 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L593 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L596 _private function_ `FTransform GetLocalToWorld()`
- L606 _private prototype_ `void UpdateMaterial();`
- L608 _private prototype_ `void AttachPointCloudListener();`
- L609 _private prototype_ `void RemovePointCloudListener();`
- L610 _private prototype_ `void OnPointCloudRebuilt();`
- L611 _private prototype_ `void OnPointCloudCollisionUpdated();`
- L612 _private prototype_ `void OnPointCloudNormalsUpdated();`
- L614 _private prototype_ `void PostPointCloudSet();`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/LidarPointCloudLODManager.h` (Public)


#### struct `FLidarPointCloudViewData`  
`struct FLidarPointCloudViewData`  
_L19-34_
- desc: Stores View data required to calculate LODs for Lidar Point Clouds
- L21 _public member_ `bool bValid;`
- L22 _public member_ `FVector ViewOrigin;`
- L23 _public member_ `FVector ViewDirection;`
- L24 _public member_ `float ScreenSizeFactor;`
- L25 _public member_ `FConvexVolume ViewFrustum;`
- L26 _public member_ `bool bSkipMinScreenSize;`
- L27 _public member_ `bool bPIE;`
- L28 _public member_ `bool bHasFocus;`
- L30 _public prototype_ `FLidarPointCloudViewData(bool bCompute = false);`
- L32 _public prototype_ `void Compute();`
- L33 _public prototype_ `bool ComputeFromEditorViewportClient(class FViewportClient* ViewportClient);`

#### class `FLidarPointCloudLODManager`  
`class FLidarPointCloudLODManager : public FTickableGameObject`  
_L40-113_
- inherits: `FTickableGameObject`
- desc: This class is responsible for selecting nodes for rendering among all instances of all LidarPointCloud assets.
- L63 _private member_ `TArray<FRegisteredProxy> RegisteredProxies;` — This holds the list of currently registered proxies, which will be used for node selection
- L66 _private member_ `TAtomic<bool> bProcessing;` — Allows skipping processing, if another one is already in progress
- L69 _private member_ `float Time;` — Stores cumulative time, elapsed from the creation of the manager. Used to determine nodes' lifetime.
- L72 _private member_ `FThreadSafeCounter64 NumPointsInFrustum;` — Stores the number of points in visible frustum during last frame
- L75 _private member_ `uint32 LastPointBudget;` — Stores the last calculated point budget
- L78 _public prototype_ `FLidarPointCloudLODManager();`
- L80 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L82 _public prototype_ `virtual TStatId GetStatId() const override;`
- L84 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L86 _public function_ `virtual bool IsTickableInEditor() const override`
- L88 _public prototype_ `static void RegisterProxy(ULidarPointCloudComponent* Component, TWeakPtr<FLidarPointCloudSceneProxyWrapper, ESPMode::ThreadSafe> SceneProxyWrapper);`
- L90 _public prototype_ `static void RefreshLOD();`
- L101 _private prototype_ `int64 ProcessLOD(const TArray<FRegisteredProxy>& RegisteredProxies, const float CurrentTime, const uint32 PointBudget, const TArray<FLidarPointCloudClippingVolumeParams>& ClippingVolumes);` — This function: - Resizes the global IndexBuffer and StructuredBuffer to fit the required GlobalPointBudget - Iterates over all registered proxies and selects the best set of nodes within the point budget - Generates the data for the StructuredBuffer and passes it to the Render Thread for an update Returns the number of points in visible frustum
- L104 _private prototype_ `void ForceProcessLOD();` — Forces a refresh of the LOD processing. Must be called from a GT
- L107 _private prototype_ `void PrepareProxies();` — Called to prepare the proxies for processing
- L110 _private prototype_ `TArray<FLidarPointCloudClippingVolumeParams> GetClippingVolumes() const;` — Compiles a list of all clipping volumes affecting any of the registered proxies
- L112 _private prototype_ `static FLidarPointCloudLODManager& Get();`

#### struct `FLidarPointCloudLODManager::FRegisteredProxy`  
`struct FRegisteredProxy`  
_L42-60_
- L44 _public member_ `TWeakObjectPtr<ULidarPointCloudComponent> Component;`
- L45 _public member_ `TWeakObjectPtr<ULidarPointCloud> PointCloud;`
- L46 _public member_ `FLidarPointCloudOctree* Octree;`
- L47 _public member_ `FLidarPointCloudComponentRenderParams ComponentRenderParams;`
- L48 _public member_ `TWeakPtr<FLidarPointCloudSceneProxyWrapper, ESPMode::ThreadSafe> SceneProxyWrapper;`
- L49 _public member_ `TSharedPtr<FLidarPointCloudTraversalOctree, ESPMode::ThreadSafe> TraversalOctree;`
- L51 _public prototype_ `FRegisteredProxy(TWeakObjectPtr<ULidarPointCloudComponent> Component, TWeakPtr<FLidarPointCloudSceneProxyWrapper, ESPMode::ThreadSafe> SceneProxyWrapper);`
- L54 _public member_ `FTransform LastComponentTransform;` — Used to detect transform changes without the need of callbacks from the SceneProxy
- L56 _public member_ `FLidarPointCloudViewData ViewData;`
- L59 _public member_ `bool bSkip;` — If true, this proxy will be skipped. Used to avoid point duplication in PIE

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/LidarPointCloudOctree.h` (Public)


#### struct `FLidarPointCloudOctreeNode`  
`struct FLidarPointCloudOctreeNode`  
_L49-213_
- desc: Represents a single octant in the tree.
- L53 _private member_ `float BulkDataLifetime;` — Stores the time, at which the BulkData needs to be released
- L56 _private member_ `uint8 Depth;` — Depth of this node
- L59 _private member_ `uint8 LocationInParent;` — Location of this node inside the parent node - see the Child Ordering at the top of the file
- L62 _private member_ `FVector3f Center;` — Center point of this node.
- L66 _private member_ `TArray<FLidarPointCloudOctreeNode*> Children;` — #todo: Change to TIndirectArray<> - investigate increased memory consumption, ~130 bytes / Node
- L69 _private member_ `FLidarPointCloudOctree* Tree;` — Pointer to the Tree holding this node
- L72 _private member_ `bool bVisibilityDirty;` — Marks the node for visibility recalculation next time it's necessary
- L75 _private member_ `bool bInUse;` — Marks the node as being used for rendering
- L78 _private member_ `bool bHasSelection;` — Marks the node as containing active selection
- L81 _private member_ `uint32 NumVisiblePoints;` — Stores the number of visible points
- L83 _private member_ `FCriticalSection MapLock;`
- L89 _private member_ `TArray<FLidarPointCloudPoint> Data;` — Holds point data allocated to this node Can be empty, if the data hasn't been streamed in yet
- L95 _private member_ `uint32 NumPoints;` — Stores the number of points this node contains. Needed, since Data may not have been streamed yet, and would return a count of 0.
- L98 _private member_ `TAtomic<bool> bHasData;` — True, if the node has its data loaded
- L101 _private member_ `int64 BulkDataOffset;` — Offset in the archive file, where the data for this node is located
- L103 _private member_ `uint32 BulkDataSize;`
- L106 _private member_ `TSharedPtr<FLidarPointCloudRenderBuffer> DataCache;` — Holds render data for this node
- L107 _private member_ `TSharedPtr<FLidarPointCloudVertexFactory> VertexFactory;`
- L108 _private member_ `TSharedPtr<FLidarPointCloudRayTracingGeometry> RayTracingGeometry;`
- L110 _private member_ `bool bRenderDataDirty;`
- L113 _private member_ `TAtomic<bool> bHasDataPending;` — Used to keep track, which data is available for rendering
- L116 _private member_ `TAtomic<bool> bCanReleaseData;` — This is used to prevent nodes with changed content from being overwritten by consecutive streaming.
- L119 _public function_ `inline FLidarPointCloudOctreeNode(FLidarPointCloudOctree* Tree, const uint8& Depth) : FLidarPointCloudOctreeNode(Tree, Depth, 0, FVector3f::ZeroVector)`
- L120 _public prototype_ `FLidarPointCloudOctreeNode(FLidarPointCloudOctree* Tree, const uint8& Depth, const uint8& LocationInParent, const FVector3f& Center);`
- L121 _public prototype_ `~FLidarPointCloudOctreeNode();`
- L122 _public prototype_ `FLidarPointCloudOctreeNode(const FLidarPointCloudOctreeNode&) = delete;`
- L123 _public prototype_ `FLidarPointCloudOctreeNode(FLidarPointCloudOctreeNode&&) = delete;`
- L124 _public prototype_ `FLidarPointCloudOctreeNode& operator=(const FLidarPointCloudOctreeNode&) = delete;`
- L125 _public prototype_ `FLidarPointCloudOctreeNode& operator=(FLidarPointCloudOctreeNode&&) = delete;`
- L128 _public prototype_ `FLidarPointCloudPoint* GetData() const;` — Returns a pointer to the point data
- L131 _public prototype_ `FLidarPointCloudPoint* GetPersistentData() const;` — Returns a pointer to the point data and prevents it from being released
- L134 _public function_ `inline TSharedPtr<FLidarPointCloudRenderBuffer> GetDataCache()` — Returns a pointer to the point data
- L137 _public function_ `inline TSharedPtr<FLidarPointCloudVertexFactory> GetVertexFactory()` — Return a pointer to the vertex factory containing pre-cached geometry
- L140 _public function_ `inline TSharedPtr<FLidarPointCloudRayTracingGeometry> GetRayTracingGeometry()` — Return a pointer to the ray tracing geometry
- L146 _public prototype_ `bool BuildDataCache(bool bUseStaticBuffers, bool bUseRayTracing);` — Builds and updates the necessary render data buffers Returns true if successful
- L149 _public function_ `inline uint32 GetNumPoints() const` — Returns the sum of grid and padding points allocated to this node.
- L152 _public function_ `uint32 GetNumVisiblePoints() const` — Returns the sum of visible grid and padding points allocated to this node.
- L155 _public prototype_ `inline FBox GetBounds() const;` — Calculates and returns the bounds of this node
- L158 _public prototype_ `inline FSphere GetSphereBounds() const;` — Calculates and returns the sphere bounds of this node
- L161 _public prototype_ `FLidarPointCloudOctreeNode* GetChildNodeAtLocation(const uint8& Location) const;` — Returns a pointer to the node at the given location, or null if one doesn't exist yet.
- L163 _public prototype_ `uint8 GetChildrenBitmask() const;`
- L165 _public prototype_ `void UpdateNumVisiblePoints();`
- L168 _public prototype_ `void InsertPoints(const FLidarPointCloudPoint* Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, const FVector3f& Translation);` — Attempts to insert given points to this node or passes it to the children, otherwise.
- L169 _public prototype_ `void InsertPoints(FLidarPointCloudPoint** Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, const FVector3f& Translation);`
- L172 _public prototype_ `void Empty(bool bRecursive = true);` — Removes all points.
- L175 _public prototype_ `uint32 GetMaxDepth() const;` — Returns the maximum depth of any children of this node .
- L178 _public prototype_ `int64 GetAllocatedSize(bool bRecursive, bool bIncludeBulkData) const;` — Returns the amount of memory used by this node
- L181 _public function_ `bool HasData() const` — Returns true, if the node has its data loaded
- L184 _public function_ `bool HasRenderData() const` — Returns true, if the node has its data loaded
- L190 _public prototype_ `void ReleaseData(bool bForce = false);` — Releases the BulkData If forced, the node will be released even if persistent
- L193 _public prototype_ `void ReleaseDataCache();` — Releases and removes the render data cache
- L196 _public prototype_ `void AddPointCount(int32 PointCount);` — Convenience function, to add point statistics to the Tree table.
- L199 _public prototype_ `void SortVisiblePoints();` — Sorts the points by visibility (visible first) to optimize data processing and rendering
- L203 _private prototype_ `template <typename T> void InsertPoints_Internal(T Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, const FVector3f& Translation);`
- L204 _private prototype_ `void InsertPoints_Dynamic(const FLidarPointCloudPoint* Points, const int64& Count, const FVector3f& Translation);`
- L205 _private prototype_ `void InsertPoints_Static(const FLidarPointCloudPoint* Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, const FVector3f& Translation);`
- L206 _private prototype_ `void InsertPoints_Dynamic(FLidarPointCloudPoint** Points, const int64& Count, const FVector3f& Translation);`
- L207 _private prototype_ `void InsertPoints_Static(FLidarPointCloudPoint** Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, const FVector3f& Translation);`

#### class `FLidarPointCloudOctree`  
`class FLidarPointCloudOctree`  
_L218-644_
- desc: Used for efficient handling of point cloud data.
- L238 _public member_ `static int32 MaxNodeDepth;` — Maximum allowed depth for any node
- L241 _public member_ `static int32 MaxBucketSize;` — Maximum number of unallocated points to keep inside the node before they need to be converted in to a full child node
- L244 _public member_ `static int32 NodeGridResolution;` — Virtual grid resolution to divide the node into
- L247 _public member_ `mutable FCriticalSection DataLock;` — Used for thread safety between rendering and asset operations.
- L250 _public member_ `FCriticalSection DataReleaseLock;` — Used to prevent auto-release of nodes if they are in use by other threads
- L253 _private member_ `FLidarPointCloudOctreeNode* Root;`
- L256 _private member_ `TArray<FSharedLODData> SharedData;` — Stores shared per-LOD node data.
- L259 _private member_ `TArray<FThreadSafeCounter64> PointCount;` — Stores number of points per each LOD.
- L262 _private member_ `TArray<FThreadSafeCounter> NodeCount;` — Stores number of nodes per each LOD.
- L265 _private member_ `FVector3f Extent;` — Extent of this Cloud.
- L268 _private member_ `mutable int32 PreviousNodeCount;` — Used to cache the Allocated Size.
- L269 _private member_ `mutable int64 PreviousPointCount;`
- L270 _private member_ `mutable int64 PreviousAllocatedStructureSize;`
- L271 _private member_ `mutable int64 PreviousAllocatedSize;`
- L274 _private member_ `TArray<TWeakPtr<FLidarPointCloudTraversalOctree, ESPMode::ThreadSafe>> LinkedTraversalOctrees;` — Used to notify any linked traversal octrees when they need to re-generate the data.
- L277 _private member_ `FTriMeshCollisionData CollisionMesh;` — Stores collision mesh data
- L280 _private member_ `ULidarPointCloud* Owner;` — Pointer to the owner of this Octree
- L282 _private member_ `IAsyncReadFileHandle* ReadHandle;`
- L284 _private member_ `FByteBulkData BulkData;`
- L294 _private member_ `} SavingBulkData;`
- L297 _private member_ `TQueue<FLidarPointCloudOctreeNode*> QueuedNodes;`
- L298 _private member_ `TArray<FLidarPointCloudOctreeNode*> NodesInUse;`
- L300 _private member_ `TAtomic<bool> bStreamingBusy;`
- L303 _private member_ `bool bIsFullyLoaded;` — Set to true when the Octree is persistently force-loaded.
- L306 _public function_ `FLidarPointCloudOctree() : FLidarPointCloudOctree(nullptr)`
- L307 _public prototype_ `FLidarPointCloudOctree(ULidarPointCloud* Owner);`
- L308 _public prototype_ `~FLidarPointCloudOctree();`
- L309 _public prototype_ `FLidarPointCloudOctree(const FLidarPointCloudOctree&) = delete;`
- L310 _public prototype_ `FLidarPointCloudOctree(FLidarPointCloudOctree&&) = delete;`
- L311 _public prototype_ `FLidarPointCloudOctree& operator=(const FLidarPointCloudOctree&) = delete;`
- L312 _public prototype_ `FLidarPointCloudOctree& operator=(FLidarPointCloudOctree&&) = delete;`
- L315 _public function_ `bool HasData() const` — Returns true if the Root node exists and has any data assigned.
- L318 _public prototype_ `int32 GetNumLODs() const;` — Returns the number of different LODs.
- L321 _public function_ `FBox GetBounds() const` — Returns the Cloud bounds.
- L324 _public function_ `inline FVector3f GetExtent() const` — Returns the extent of the Cloud's bounds.
- L327 _public prototype_ `void RefreshBounds();` — Recalculates and updates points bounds.
- L330 _public prototype_ `int64 GetNumPoints() const;` — Returns the total number of points.
- L333 _public prototype_ `int64 GetNumVisiblePoints() const;` — Returns the total number of visible points.
- L336 _public prototype_ `int32 GetNumNodes() const;` — Returns the total number of nodes.
- L339 _public function_ `inline int32 GetNumNodesInUse() const` — Returns the total number of nodes.
- L342 _public function_ `ULidarPointCloud* GetOwner() const` — Returns a pointer to the Point Cloud asset, which owns this Octree.
- L345 _public prototype_ `int64 GetAllocatedSize() const;` — Returns the amount of memory used by this Octree, including the BulkData
- L348 _public prototype_ `int64 GetAllocatedStructureSize() const;` — Returns the amount of memory used by this Octree, excluding the BulkData
- L351 _public function_ `float GetRootCellSize() const` — Returns the grid cell size at root level.
- L354 _public prototype_ `float GetEstimatedPointSpacing() const;` — Returns an estimated spacing between points
- L357 _public function_ `bool HasCollisionData() const` — Returns true, if the Octree has collision built
- L360 _public prototype_ `void BuildCollision(const float& Accuracy, const bool& bVisibleOnly);` — Builds collision using the accuracy provided
- L363 _public prototype_ `void RemoveCollision();` — Removes collision mesh data
- L366 _public function_ `const FTriMeshCollisionData* GetCollisionData() const` — Returns pointer to the collision data
- L369 _public prototype_ `void BuildStaticMeshBuffers(float CellSize, LidarPointCloudMeshing::FMeshBuffers* OutMeshBuffers, const FTransform& Transform);` — Constructs and returns the MeshBuffers struct from the data
- L372 _public prototype_ `void GetPoints(TArray<FLidarPointCloudPoint*>& SelectedPoints, int64 StartIndex = 0, int64 Count = -1);` — Populates the given array with points from the tree
- L373 _public prototype_ `void GetPoints(TArray64<FLidarPointCloudPoint*>& SelectedPoints, int64 StartIndex = 0, int64 Count = -1);`
- L376 _public prototype_ `void GetPointsInSphere(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly);` — Populates the array with the list of points within the given sphere.
- L377 _public prototype_ `void GetPointsInSphere(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly);`
- L380 _public prototype_ `void GetPointsInBox(TArray<const FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly) const;` — Populates the array with the list of pointers to points within the given box.
- L381 _public prototype_ `void GetPointsInBox(TArray64<const FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly) const;`
- L382 _public prototype_ `void GetPointsInBox(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly);`
- L383 _public prototype_ `void GetPointsInBox(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly);`
- L386 _public prototype_ `void GetPointsInConvexVolume(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FConvexVolume& ConvexVolume, const bool& bVisibleOnly);` — Populates the array with the list of points within the given convex volume.
- L387 _public prototype_ `void GetPointsInConvexVolume(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FConvexVolume& ConvexVolume, const bool& bVisibleOnly);`
- L390 _public prototype_ `void GetPointsAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FTransform* LocalToWorld, int64 StartIndex = 0, int64 Count = -1) const;` — Populates the given array with copies of points from the tree
- L391 _public prototype_ `void GetPointsAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FTransform* LocalToWorld, int64 StartIndex = 0, int64 Count = -1) const;`
- L394 _public prototype_ `void GetPointsAsCopiesInBatches(TFunction<void(TSharedPtr<TArray64<FLidarPointCloudPoint>>)> Action, const int64& BatchSize, const bool& bVisibleOnly);` — Executes the provided action on batches of points.
- L397 _public prototype_ `void GetPointsInSphereAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly, const FTransform* LocalToWorld) const;` — Populates the array with the list of points within the given sphere.
- L398 _public prototype_ `void GetPointsInSphereAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly, const FTransform* LocalToWorld) const;`
- L401 _public prototype_ `void GetPointsInBoxAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly, const FTransform* LocalToWorld) const;` — Populates the array with the list of pointers to points within the given box.
- L402 _public prototype_ `void GetPointsInBoxAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly, const FTransform* LocalToWorld) const;`
- L405 _public prototype_ `FLidarPointCloudPoint* RaycastSingle(const FLidarPointCloudRay& Ray, const float& Radius, const bool& bVisibleOnly);` — Performs a raycast test against the point cloud. Returns the pointer if hit or nullptr otherwise.
- L412 _public prototype_ `bool RaycastMulti(const FLidarPointCloudRay& Ray, const float& Radius, const bool& bVisibleOnly, TArray<FLidarPointCloudPoint*>& OutHits);` — Performs a raycast test against the point cloud. Populates OutHits array with the results. Returns true it anything has been hit.
- L413 _public prototype_ `bool RaycastMulti(const FLidarPointCloudRay& Ray, const float& Radius, const bool& bVisibleOnly, const FTransform* LocalToWorld, TArray<FLidarPointCloudPoint>& OutHits);`
- L416 _public prototype_ `bool HasPointsInSphere(const FSphere& Sphere, const bool& bVisibleOnly) const;` — Returns true if there are any points within the given sphere.
- L419 _public prototype_ `bool HasPointsInBox(const FBox& Box, const bool& bVisibleOnly) const;` — Returns true if there are any points within the given box.
- L422 _public prototype_ `bool HasPointsByRay(const FLidarPointCloudRay& Ray, const float& Radius, const bool& bVisibleOnly) const;` — Returns true if there are any points hit by the given ray.
- L425 _public prototype_ `void SetVisibilityOfPointsInSphere(const bool& bNewVisibility, const FSphere& Sphere);` — Sets visibility of points within the given sphere.
- L428 _public prototype_ `void SetVisibilityOfPointsInBox(const bool& bNewVisibility, const FBox& Box);` — Sets visibility of points within the given box.
- L431 _public prototype_ `void SetVisibilityOfFirstPointByRay(const bool& bNewVisibility, const FLidarPointCloudRay& Ray, const float& Radius);` — Sets visibility of the first point hit by the given ray.
- L434 _public prototype_ `void SetVisibilityOfPointsByRay(const bool& bNewVisibility, const FLidarPointCloudRay& Ray, const float& Radius);` — Sets visibility of points hit by the given ray.
- L437 _public prototype_ `void HideAll();` — Marks all points hidden
- L440 _public prototype_ `void UnhideAll();` — Marks all points visible
- L443 _public prototype_ `void ExecuteActionOnAllPoints(TFunction<void(FLidarPointCloudPoint*)> Action, const bool& bVisibleOnly);` — Executes the provided action on each of the points.
- L446 _public prototype_ `void ExecuteActionOnPointsInSphere(TFunction<void(FLidarPointCloudPoint*)> Action, const FSphere& Sphere, const bool& bVisibleOnly);` — Executes the provided action on each of the points within the given sphere.
- L449 _public prototype_ `void ExecuteActionOnPointsInBox(TFunction<void(FLidarPointCloudPoint*)> Action, const FBox& Box, const bool& bVisibleOnly);` — Executes the provided action on each of the points within the given box.
- L452 _public prototype_ `void ExecuteActionOnFirstPointByRay(TFunction<void(FLidarPointCloudPoint*)> Action, const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly);` — Executes the provided action on the first point hit by the given ray.
- L455 _public prototype_ `void ExecuteActionOnPointsByRay(TFunction<void(FLidarPointCloudPoint*)> Action, const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly);` — Executes the provided action on each of the points hit by the given ray.
- L458 _public prototype_ `void ApplyColorToAllPoints(const FColor& NewColor, const bool& bVisibleOnly);` — Applies the given color to all points
- L461 _public prototype_ `void ApplyColorToPointsInSphere(const FColor& NewColor, const FSphere& Sphere, const bool& bVisibleOnly);` — Applies the given color to all points within the sphere
- L464 _public prototype_ `void ApplyColorToPointsInBox(const FColor& NewColor, const FBox& Box, const bool& bVisibleOnly);` — Applies the given color to all points within the box
- L467 _public prototype_ `void ApplyColorToFirstPointByRay(const FColor& NewColor, const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly);` — Applies the given color to the first point hit by the given ray
- L470 _public prototype_ `void ApplyColorToPointsByRay(const FColor& NewColor, const FLidarPointCloudRay& Ray, const float& Radius, bool bVisibleOnly);` — Applies the given color to all points hit by the given ray
- L476 _public prototype_ `void MarkPointVisibilityDirty();` — This should to be called if any manual modification to individual points' visibility has been made. If not marked dirty, the rendering may work suboptimally.
- L479 _public prototype_ `void MarkRenderDataDirty();` — Marks render data of all nodes as dirty.
- L482 _public prototype_ `void MarkRenderDataInSphereDirty(const FSphere& Sphere);` — Marks render data of all nodes within the given sphere as dirty.
- L485 _public prototype_ `void MarkRenderDataInConvexVolumeDirty(const FConvexVolume& ConvexVolume);` — Marks render data of all nodes within the given convex volume as dirty.
- L488 _public prototype_ `void SelectByConvexVolume(const FConvexVolume& ConvexVolume, bool bAdditive, bool bVisibleOnly);`
- L489 _public prototype_ `void SelectBySphere(const FSphere& Sphere, bool bAdditive, bool bVisibleOnly);`
- L490 _public prototype_ `void HideSelected();`
- L491 _public prototype_ `void DeleteSelected();`
- L492 _public prototype_ `void InvertSelection();`
- L493 _public prototype_ `int64 NumSelectedPoints() const;`
- L494 _public prototype_ `bool HasSelectedPoints() const;`
- L495 _public prototype_ `void GetSelectedPoints(TArray64<FLidarPointCloudPoint*>& SelectedPoints) const;`
- L497 _public prototype_ `template <typename T> void GetSelectedPointsAsCopies_Internal(TArray<FLidarPointCloudPoint, T>& SelectedPoints, const FTransform& Transform) const;`
- L498 _public prototype_ `void GetSelectedPointsAsCopies(TArray<FLidarPointCloudPoint>& SelectedPoints, const FTransform& Transform) const;`
- L499 _public prototype_ `void GetSelectedPointsAsCopies(TArray64<FLidarPointCloudPoint>& SelectedPoints, const FTransform& Transform) const;`
- L500 _public prototype_ `void GetSelectedPointsInBox(TArray64<const FLidarPointCloudPoint*>& SelectedPoints, const FBox& Box) const;`
- L501 _public prototype_ `void ClearSelection();`
- L502 _public prototype_ `void BuildStaticMeshBuffersForSelection(float CellSize, LidarPointCloudMeshing::FMeshBuffers* OutMeshBuffers, const FTransform& Transform);`
- L506 _public prototype_ `void Initialize(const FVector3f& InExtent);` — Initializes the Octree properties.
- L509 _public prototype_ `void InsertPoint(const FLidarPointCloudPoint* Point, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector3f& Translation);` — Inserts the given point into the Octree structure, internally thread-safe.
- L512 _public prototype_ `void InsertPoints(FLidarPointCloudPoint* Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector3f& Translation);` — Inserts group of points into the Octree structure, internally thread-safe.
- L513 _public prototype_ `void InsertPoints(const FLidarPointCloudPoint* Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector3f& Translation);`
- L514 _public prototype_ `void InsertPoints(FLidarPointCloudPoint** Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector3f& Translation);`
- L517 _public prototype_ `void RemovePoint(const FLidarPointCloudPoint* Point);` — Attempts to remove the given point.
- L518 _public prototype_ `void RemovePoint(FLidarPointCloudPoint Point);`
- L521 _public prototype_ `void RemovePoints(TArray<FLidarPointCloudPoint*>& Points);` — Removes points in bulk
- L522 _public prototype_ `void RemovePoints(TArray64<FLidarPointCloudPoint*>& Points);`
- L525 _public prototype_ `void RemovePointsInSphere(const FSphere& Sphere, const bool& bVisibleOnly);` — Removes all points within the given sphere
- L528 _public prototype_ `void RemovePointsInBox(const FBox& Box, const bool& bVisibleOnly);` — Removes all points within the given box
- L531 _public prototype_ `void RemoveFirstPointByRay(const FLidarPointCloudRay& Ray, const float& Radius, const bool& bVisibleOnly);` — Removes the first point hit by the given ray
- L534 _public prototype_ `void RemovePointsByRay(const FLidarPointCloudRay& Ray, const float& Radius, const bool& bVisibleOnly);` — Removes all points hit by the given ray
- L537 _public prototype_ `void RemoveHiddenPoints();` — Removes all hidden points
- L540 _public prototype_ `void ResetNormals();` — Resets all normals information
- L546 _public prototype_ `void CalculateNormals(FThreadSafeBool* bCancelled, int32 Quality, float Tolerance, TArray64<FLidarPointCloudPoint*>* InPointSelection);` — Calculates Normals for the provided points If a nullptr is passed, the calculation will be executed on the whole cloud
- L549 _public prototype_ `void Empty(bool bDestroyNodes);` — Removes all points and, optionally, all nodes except for the root node. Retains the bounds.
- L552 _public function_ `void RegisterTraversalOctree(TWeakPtr<FLidarPointCloudTraversalOctree, ESPMode::ThreadSafe> TraversalOctree)` — Adds the given traversal octree to the list of linked octrees.
- L561 _public prototype_ `void UnregisterTraversalOctree(FLidarPointCloudTraversalOctree* TraversalOctree);` — Removes the given traversal octree from the list
- L567 _public prototype_ `void StreamNodes(TArray<FLidarPointCloudOctreeNode*>& Nodes, const float& CurrentTime);` — Streams requested nodes or extends their lifetime, if already loaded Unloads all unused nodes with expired lifetime
- L570 _public function_ `bool IsFullyLoaded() const` — Returns true, if the cloud is fully and persistently loaded.
- L573 _public prototype_ `void LoadAllNodes(bool bLoadPersistently);` — Loads all nodes.
- L579 _public prototype_ `void ReleaseAllNodes(bool bIncludePersistent);` — Releases all nodes. Optionally, releases persistent nodes too.
- L581 _public prototype_ `bool IsOptimizedForDynamicData() const;`
- L583 _public prototype_ `void OptimizeForDynamicData();`
- L585 _public prototype_ `void OptimizeForStaticData();`
- L587 _public prototype_ `IAsyncReadFileHandle* GetReadHandle();`
- L588 _public prototype_ `void CloseReadHandle();`
- L592 _public prototype_ `void GetPointsInFrustum(TArray<FLidarPointCloudPoint*>& SelectedPoints, const FConvexVolume& Frustum, const bool& bVisibleOnly);` — `UE_DEPRECATED(4.27, "Use GetPointsInConvexVolume instead.")`
- L594 _public prototype_ `void GetPointsInFrustum(TArray64<FLidarPointCloudPoint*>& SelectedPoints, const FConvexVolume& Frustum, const bool& bVisibleOnly);` — `UE_DEPRECATED(4.27, "Use GetPointsInConvexVolume instead.")`
- L596 _public prototype_ `void MarkRenderDataInFrustumDirty(const FConvexVolume& Frustum);` — `UE_DEPRECATED(4.27, "Use MarkRenderDataInConvexVolumeDirty instead.")`
- L600 _private prototype_ `void RefreshAllocatedSize();`
- L603 _private prototype_ `template <typename T> void InsertPoints_Internal(T Points, const int64& Count, ELidarPointCloudDuplicateHandling DuplicateHandling, bool bRefreshPointsBounds, const FVector3f& Translation);`
- L606 _private prototype_ `template <typename T> void GetPoints_Internal(TArray<FLidarPointCloudPoint*, T>& Points, int64 StartIndex = 0, int64 Count = -1);`
- L608 _private prototype_ `template <typename T> void GetPointsInSphere_Internal(TArray<FLidarPointCloudPoint*, T>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly);`
- L610 _private prototype_ `template <typename T> void GetPointsInBox_Internal(TArray<FLidarPointCloudPoint*, T>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly);`
- L612 _private prototype_ `template <typename T> void GetPointsInBox_Internal(TArray<const FLidarPointCloudPoint*, T>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly) const;`
- L614 _private prototype_ `template <typename T> void GetPointsInConvexVolume_Internal(TArray<FLidarPointCloudPoint*, T>& SelectedPoints, const FConvexVolume& ConvexVolume, const bool& bVisibleOnly);`
- L616 _private prototype_ `template <typename T> void GetPointsAsCopies_Internal(TArray<FLidarPointCloudPoint, T>& Points, const FTransform* LocalToWorld, int64 StartIndex = 0, int64 Count = -1) const;`
- L618 _private prototype_ `template <typename T> void GetPointsInSphereAsCopies_Internal(TArray<FLidarPointCloudPoint, T>& SelectedPoints, const FSphere& Sphere, const bool& bVisibleOnly, const FTransform* LocalToWorld) const;`
- L620 _private prototype_ `template <typename T> void GetPointsInBoxAsCopies_Internal(TArray<FLidarPointCloudPoint, T>& SelectedPoints, const FBox& Box, const bool& bVisibleOnly, const FTransform* LocalToWorld) const;`
- L623 _private prototype_ `template <typename T> void RemovePoints_Internal(TArray<FLidarPointCloudPoint*, T>& Points);`
- L625 _private prototype_ `void RemovePoint_Internal(FLidarPointCloudOctreeNode* Node, int32 Index);`
- L628 _private prototype_ `void MarkTraversalOctreesForInvalidation();` — Notifies all linked traversal octrees that they should invalidate and regenerate the data.
- L630 _private prototype_ `void Serialize(FArchive& Ar);`
- L631 _private prototype_ `void SerializeBulkData(FArchive& Ar);`
- L633 _private prototype_ `void StreamNodeData(FLidarPointCloudOctreeNode* Node);`

#### struct `FLidarPointCloudOctree::FSharedLODData`  
`struct FSharedLODData`  
_L222-234_
- desc: Stores shared per-LOD node data.
- L224 _public member_ `float Radius;`
- L225 _public member_ `float RadiusSq;`
- L226 _public member_ `float GridSize;`
- L227 _public member_ `FVector3f GridSize3D;`
- L228 _public member_ `float Size;`
- L229 _public member_ `float NormalizationMultiplier;`
- L230 _public member_ `FVector3f Extent;`
- L232 _public function_ `FSharedLODData()`
- L233 _public prototype_ `FSharedLODData(const FVector3f& InExtent);`

#### struct `FLidarPointCloudOctree::FLidarPointCloudBulkData`  
`struct FLidarPointCloudBulkData : public FBulkData`  
_L287-294_
- inherits: `FBulkData`
- L289 _public member_ `FSerializeBulkDataElements SerializeElementsCallback;`
- L291 _public prototype_ `FLidarPointCloudBulkData(FLidarPointCloudOctree* Octree);`
- L293 _public prototype_ `void Serialize(FArchive& Ar, UObject* InOwner);`

#### struct `FLidarPointCloudTraversalOctreeNode`  
`struct FLidarPointCloudTraversalOctreeNode`  
_L649-684_
- desc: Represents a single octant in the traversal tree.
- L652 _public member_ `FLidarPointCloudOctreeNode* DataNode;` — Pointer to the target node.
- L655 _public member_ `FVector3f Center;` — Stores the center of the target node in World space.
- L658 _public member_ `uint8 Depth;` — Depth of this node
- L661 _public member_ `uint8 VirtualDepth;` — Calculated for use with adaptive sprite scaling
- L663 _public member_ `FLidarPointCloudTraversalOctreeNode* Parent;`
- L665 _public member_ `FLidarPointCloudTraversalOctree* Octree;`
- L668 _public member_ `TArray<FLidarPointCloudTraversalOctreeNode> Children;` — Stores the children array
- L671 _public member_ `bool bSelected;` — Holds true if the node has been selected for rendering.
- L673 _public member_ `bool bFullyContained;`
- L675 _public prototype_ `FLidarPointCloudTraversalOctreeNode();`
- L678 _public prototype_ `void Build(FLidarPointCloudTraversalOctree* TraversalOctree, FLidarPointCloudOctreeNode* Node, const FTransform& LocalToWorld, const FVector3f& LocationOffset);` — Builds the traversal version of the given node.
- L681 _public prototype_ `void CalculateVirtualDepth(const TArray<float>& LevelWeights, const float& PointSizeBias);` — Calculates virtual depth of this node, to be used to estimate the best sprite size
- L683 _public function_ `inline bool IsAvailable() const`

#### struct `FLidarPointCloudTraversalOctreeNodeSizeData`  
`struct FLidarPointCloudTraversalOctreeNodeSizeData`  
_L687-694_
- desc: Used for node size sorting and node selection.
- L689 _public member_ `FLidarPointCloudTraversalOctreeNode* Node;`
- L690 _public member_ `float Size;`
- L691 _public member_ `int32 ProxyIndex;`
- L693 _public prototype_ `FLidarPointCloudTraversalOctreeNodeSizeData(FLidarPointCloudTraversalOctreeNode* Node, const float& Size, const int32& ProxyIndex);`

#### struct `FLidarPointCloudNodeSelectionParams`  
`struct FLidarPointCloudNodeSelectionParams`  
_L697-706_
- desc: Convenience struct to group all selection params into one
- L699 _public member_ `float MinScreenSize;`
- L700 _public member_ `float ScreenCenterImportance;`
- L701 _public member_ `int32 MinDepth;`
- L702 _public member_ `int32 MaxDepth;`
- L703 _public member_ `float BoundsScale;`
- L704 _public member_ `bool bUseFrustumCulling;`
- L705 _public member_ `const TArray<struct FLidarPointCloudClippingVolumeParams>* ClippingVolumes;`

#### struct `FLidarPointCloudTraversalOctree`  
`struct FLidarPointCloudTraversalOctree`  
_L711-754_
- desc: Used as a traversal tree for node selection during rendering
- L713 _public member_ `FLidarPointCloudTraversalOctreeNode Root;`
- L716 _public member_ `TArray<float> RadiiSq;` — Stores per-LOD bounds in World space.
- L717 _public member_ `TArray<FVector3f> Extents;`
- L720 _public member_ `uint8 NumLODs;` — Stores the number of LODs.
- L723 _public member_ `TArray<float> LevelWeights;` — Normalized histogram of level weights, one for each LOD. Used for point scaling
- L725 _public member_ `float VirtualDepthMultiplier;`
- L726 _public member_ `float ReversedVirtualDepthMultiplier;`
- L729 _public member_ `FLidarPointCloudOctree* Octree;` — Pointer to the source Octree
- L731 _public member_ `bool bValid;`
- L734 _public prototype_ `FLidarPointCloudTraversalOctree(FLidarPointCloudOctree* Octree, const FTransform& LocalToWorld);` — Build the Traversal tree from the Octree provided
- L736 _public prototype_ `~FLidarPointCloudTraversalOctree();`
- L737 _public prototype_ `FLidarPointCloudTraversalOctree(const FLidarPointCloudTraversalOctree&) = delete;`
- L738 _public prototype_ `FLidarPointCloudTraversalOctree(FLidarPointCloudTraversalOctree&&) = delete;`
- L739 _public prototype_ `FLidarPointCloudTraversalOctree& operator=(const FLidarPointCloudTraversalOctree&) = delete;`
- L740 _public prototype_ `FLidarPointCloudTraversalOctree& operator=(FLidarPointCloudTraversalOctree&&) = delete;`
- L746 _public prototype_ `int32 GetVisibleNodes(TArray<FLidarPointCloudTraversalOctreeNodeSizeData>& NodeSizeData, const struct FLidarPointCloudViewData* ViewData, const int32& ProxyIndex, const FLidarPointCloudNodeSelectionParams& SelectionParams);` — Selects and appends the subset of visible nodes for rendering. Returns number of selected nodes
- L748 _public prototype_ `void CalculateVisibilityStructure(TArray<uint32>& OutData);`
- L750 _public prototype_ `void CalculateLevelWeightsForSelectedNodes(TArray<float>& OutLevelWeights);`
- L752 _public function_ `FVector GetCenter() const`
- L753 _public function_ `FVector GetExtent() const`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace LidarPointCloudMeshing`
- L635 _function_ `friend FArchive& operator<<(FArchive& Ar, FLidarPointCloudOctree& O)`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/LidarPointCloudSettings.h` (Public)


#### enum `ELidarPointCloudDuplicateHandling`  
`enum class ELidarPointCloudDuplicateHandling : uint8`  
_L10-18_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Ignore` — Keeps any duplicates found
- L15 _public enumerator_ `SelectFirst` — Keeps the first point and skips any further duplicates
- L17 _public enumerator_ `SelectBrighter` — Selects the brightest of the duplicates

#### class `ULidarPointCloudSettings`  
`class ULidarPointCloudSettings : public UObject`  
_L21-134_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UObject`
- L28 _public member_ `ELidarPointCloudDuplicateHandling DuplicateHandling;` — `UPROPERTY(config, EditAnywhere, Category=Octree)` — Determines how to handle duplicate points (distance < 0.0001).
- L32 _public member_ `float MaxDistanceForDuplicate;` — `UPROPERTY(config, EditAnywhere, Category=Octree, meta = (ClampMin = "0"))` — Maximum distance between points, within which they are considered to be duplicates
- L39 _public member_ `int32 MaxBucketSize;` — `UPROPERTY(config, EditAnywhere, Category=Octree)` — Maximum number of unallocated points to keep inside the node before they need to be converted in to a full child node. Lower values will provide finer LOD control at the expense of system RAM and CPU time.
- L46 _public member_ `int32 NodeGridResolution;` — `UPROPERTY(config, EditAnywhere, Category=Octree)` — Virtual grid resolution to divide the node into. Lower values will provide finer LOD control at the expense of system RAM and CPU time.
- L50 _public member_ `int32 MultithreadingInsertionBatchSize;` — `UPROPERTY(config, EditAnywhere, Category=Performance)` — Determines the maximum amount of points to process in a single batch when using multi-threading.
- L54 _public member_ `bool bUseAsyncImport;` — `UPROPERTY(config, EditAnywhere, Category=Performance)` — Enabling this will allow editor to import the point clouds in the background, without blocking the main thread.
- L62 _public member_ `bool bPrioritizeActiveViewport;` — `UPROPERTY(config, EditAnywhere, Category=Performance)` — Enabling this will allocate larger portion of the available point budget to the viewport with focus. May improve asset editing experience, if the scenes are busy. Disable, if you are experiencing visual glitches.
- L69 _public member_ `float CachedNodeLifetime;` — `UPROPERTY(config, EditAnywhere, Category=Performance, meta = (ClampMin = "0"))` — Sets how long the nodes wil be kept in RAM after they are no longer visible. Larger values are more likely to avoid re-loads from storage, at the cost of increased RAM usage.
- L76 _public member_ `bool bReleaseAssetAfterSaving;` — `UPROPERTY(config, EditAnywhere, Category= Performance)` — Enabling this will automatically release memory used by the asset once it's saved Helpful when dealing with very large data sets to avoid memory blocking
- L83 _public member_ `bool bReleaseAssetAfterCooking;` — `UPROPERTY(config, EditAnywhere, Category= Performance)` — Enabling this will automatically release memory used by the asset once it's cooked Helpful when dealing with very large data sets to avoid memory blocking
- L87 _public member_ `bool bUseRenderDataSmoothing;` — `UPROPERTY(config, EditAnywhere, Category=Performance)` — If enabled, the render data generation will be spread across multiple frames to avoid freezes
- L91 _public member_ `float RenderDataSmoothingMaxFrametime;` — `UPROPERTY(config, EditAnywhere, Category=Performance, meta = (EditCondition = "bUseAsyncImport"))` — If UseRenderDataSmoothing is enabled, this will determine how much of the frame time can be spent on render data generation.
- L95 _public member_ `bool bUseFastRendering;` — `UPROPERTY(config, EditAnywhere, Category=Performance)` — Enabling this will greatly improve runtime performance at a cost of quadrupling VRAM use
- L102 _public member_ `bool bEnableLidarRayTracing;` — `UPROPERTY(config, EditAnywhere, Category=RayTracing)` — If enabled, Lidar assets will become visible to Ray Tracing. Warning, this will significantly increase VRAM usage!
- L106 _public member_ `int32 MeshingBatchSize;` — `UPROPERTY(config, EditAnywhere, Category=Collision)` — Affects the size of per-thread data for the meshing algorithm.
- L114 _public member_ `bool bAutoCenterOnImport;` — `UPROPERTY(config, EditAnywhere, Category="Automation")` — Automatically centers the cloud on import. Caution: Preserving original coordinates may cause noticeable precision loss, if the values are too large. Should you experience point 'banding' effect, please re-import your cloud with centering enabled.
- L118 _public member_ `bool bAutoCalculateNormalsOnImport;` — `UPROPERTY(config, EditAnywhere, Category="Automation")` — If enabled, the assets will automatically calculate normals upon their successful import.
- L122 _public member_ `bool bAutoBuildCollisionOnImport;` — `UPROPERTY(config, EditAnywhere, Category="Automation")` — If enabled, the assets will automatically build collision upon their successful import.
- L126 _public member_ `float ImportScale;` — `UPROPERTY(config, EditAnywhere, Category= "Import / Export", meta = (ClampMin = "0.0001"))` — Scale to apply during import
- L130 _public member_ `float ExportScale;` — `UPROPERTY(config, EditAnywhere, Category= "Import / Export", meta = (ClampMin = "0.0001"))` — Scale to apply during export. In most cases, this should be equal to an inverted ImportScale
- L133 _public prototype_ `ULidarPointCloudSettings();`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/LidarPointCloudShared.h` (Public)


#### struct `FLidarPointCloudNormal`  
`struct FLidarPointCloudNormal`  
_L19-60_
- reflection: `USTRUCT(BlueprintType)`
- desc: 3D vector represented using only a single byte per component
- L25 _public member_ `uint8 X;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lidar Point Normal")`
- L28 _public member_ `uint8 Y;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lidar Point Normal")`
- L31 _public member_ `uint8 Z;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lidar Point Normal")`
- L34 _public function_ `FLidarPointCloudNormal()`
- L35 _public function_ `FLidarPointCloudNormal(const FVector3f& Normal)`
- L36 _public function_ `FLidarPointCloudNormal(const FPlane& Normal)`
- L37 _public function_ `FLidarPointCloudNormal(const float& X, const float& Y, const float& Z)`
- L39 _public function_ `bool operator==(const FLidarPointCloudNormal& Other) const`
- L41 _public function_ `inline bool IsValid() const`
- L43 _public function_ `inline void SetFromVector(const FVector3f& Normal)`
- L47 _public function_ `inline void SetFromFloats(const float& InX, const float& InY, const float& InZ)`
- L54 _public function_ `inline void Reset()`
- L59 _public function_ `inline FVector3f ToVector() const`

#### struct `FLidarPointCloudPoint_Legacy`  
`struct FLidarPointCloudPoint_Legacy`  
_L63-70_
- desc: Used for backwards compatibility with pre-normal datasets
- L65 _public member_ `FVector3f Location;`
- L66 _public member_ `FColor Color;`
- L67 _public member_ `uint8 bVisible : 1;`
- L68 _public member_ `uint8 ClassificationID : 5;`
- L69 _public member_ `uint8 Dummy : 2;`

#### struct `FLidarPointCloudPoint`  
`struct FLidarPointCloudPoint`  
_L73-196_
- reflection: `USTRUCT(BlueprintType)`
- L79 _public member_ `FVector3f Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lidar Point Cloud Point")`
- L82 _public member_ `FColor Color;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lidar Point Cloud Point")`
- L85 _public member_ `FLidarPointCloudNormal Normal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lidar Point Cloud Point")`
- L88 _public member_ `uint8 bVisible : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lidar Point Cloud Point")`
- L91 _public member_ `uint8 ClassificationID : 5;` — Valid range is 0 - 31.
- L93 _public member_ `uint8 bSelected : 1;`
- L96 _private member_ `uint8 bMarkedForDeletion : 1;`
- L99 _public function_ `FLidarPointCloudPoint() : Location(FVector3f::ZeroVector) , Color(FColor::White) , Normal() , bVisible(true) , ClassificationID(0) , bSelected(false) , bMarkedForDeletion(false)`
- L109 _public function_ `FLidarPointCloudPoint(const float& X, const float& Y, const float& Z) : FLidarPointCloudPoint()`
- L116 _public function_ `FLidarPointCloudPoint(const float& X, const float& Y, const float& Z, const float& I) : FLidarPointCloudPoint(X, Y, Z)`
- L121 _public function_ `FLidarPointCloudPoint(const float& X, const float& Y, const float& Z, const float& R, const float& G, const float& B, const float& A = 1.0f) : FLidarPointCloudPoint(X, Y, Z)`
- L126 _public function_ `FLidarPointCloudPoint(const float& X, const float& Y, const float& Z, const float& R, const float& G, const float& B, const float& A, const float& NX, const float& NY, const float& NZ) : FLidarPointCloudPoint(X, Y, Z)`
- L132 _public function_ `FLidarPointCloudPoint(const FVector3f& Location) : FLidarPointCloudPoint(Location.X, Location.Y, Location.Z)`
- L133 _public function_ `FLidarPointCloudPoint(const FVector3f& Location, const float& R, const float& G, const float& B, const float& A = 1.0f) : FLidarPointCloudPoint(Location)`
- L138 _public function_ `FLidarPointCloudPoint(const FVector3f& Location, const float& R, const float& G, const float& B, const float& A, const uint8& ClassificationID) : FLidarPointCloudPoint(Location, R, G, B, A)`
- L143 _public function_ `FLidarPointCloudPoint(const FVector3f& Location, const uint8& R, const uint8& G, const uint8& B, const uint8& A, const uint8& ClassificationID) : FLidarPointCloudPoint(Location.X, Location.Y, Location.Z)`
- L149 _public function_ `FLidarPointCloudPoint(const FVector3f& Location, const FColor& Color, const bool& bVisible, const uint8& ClassificationID) : FLidarPointCloudPoint(Location)`
- L156 _public function_ `FLidarPointCloudPoint(const FVector3f& Location, const FColor& Color, const bool& bVisible, const uint8& ClassificationID, const FLidarPointCloudNormal& Normal) : FLidarPointCloudPoint(Location)`
- L165 _public function_ `FLidarPointCloudPoint(const FLidarPointCloudPoint& Other) : FLidarPointCloudPoint()` — Questionable behavior here - the copy constructor only copies part of the state but the assignment operator copies it all
- L170 _public prototype_ `FLidarPointCloudPoint& operator=(const FLidarPointCloudPoint&) = default;`
- L171 _public function_ `FLidarPointCloudPoint(const FLidarPointCloudPoint_Legacy& Other) : FLidarPointCloudPoint(Other.Location, Other.Color, Other.bVisible, Other.ClassificationID)`
- L176 _public function_ `inline void CopyFrom(const FLidarPointCloudPoint& Other)`
- L185 _public function_ `inline FLidarPointCloudPoint Transform(const FTransform3f& Transform) const`
- L190 _public function_ `bool operator==(const FLidarPointCloudPoint& P) const`

#### enum `ELidarPointCloudAsyncMode`  
`enum class ELidarPointCloudAsyncMode : uint8`  
_L201-206_
- reflection: `UENUM(BlueprintType)`
- desc: Used in blueprint latent function execution
- L203 _public enumerator_ `Success`
- L204 _public enumerator_ `Failure`
- L205 _public enumerator_ `Progress`

#### enum `ELidarPointCloudScalingMethod`  
`enum class ELidarPointCloudScalingMethod : uint8`  
_L209-236_
- reflection: `UENUM(BlueprintType)`
- L216 _public enumerator_ `PerNode` — Points are scaled based on the estimated density of their containing node. Recommended for assets with high variance of point densities, but may produce less fine detail overall. Default method in 4.25 and 4.26
- L222 _public enumerator_ `PerNodeAdaptive` — Similar to PerNode, but the density is calculated adaptively based on the current view. Produces good amount of fine detail while being generally resistant to density variance.
- L229 _public enumerator_ `PerPoint` — Points are scaled based on their individual calculated depth. Capable of resolving the highest amount of fine detail, but is the most susceptible to density changes across the dataset, and may result in patches of varying point sizes.
- L235 _public enumerator_ `FixedScreenSize` — Sprites will be rendered using screen-space scaling method. In that mode, Point Size property will work as Screen Percentage.

#### class `FLidarPointCloudDataBuffer`  
`class FLidarPointCloudDataBuffer`  
_L239-272_
- desc: Used to help track multiple buffer allocations
- L242 _public function_ `FLidarPointCloudDataBuffer() : bInUse(false), PendingSize(0)`
- L243 _public prototype_ `~FLidarPointCloudDataBuffer() = default;`
- L244 _public function_ `FLidarPointCloudDataBuffer(const FLidarPointCloudDataBuffer& Other)`
- L249 _public prototype_ `FLidarPointCloudDataBuffer(FLidarPointCloudDataBuffer&&) = delete;`
- L250 _public function_ `FLidarPointCloudDataBuffer& operator=(const FLidarPointCloudDataBuffer& Other)`
- L256 _public prototype_ `FLidarPointCloudDataBuffer& operator=(FLidarPointCloudDataBuffer&&) = delete;`
- L258 _public function_ `inline uint8* GetData()`
- L259 _public function_ `inline bool InUse() const`
- L262 _public prototype_ `void MarkAsFree();` — Marks the buffer as no longer in use so it can be reassigned to another read thread.
- L263 _public prototype_ `void Initialize(const int32& Size);`
- L264 _public prototype_ `void Resize(const int32& NewBufferSize, bool bForce = false);`
- L267 _private member_ `TAtomic<bool> bInUse;`
- L268 _private member_ `TArray<uint8> Data;`
- L269 _private member_ `int32 PendingSize;`

#### class `FLidarPointCloudDataBufferManager`  
`class FLidarPointCloudDataBufferManager`  
_L275-296_
- desc: Used to help track multiple buffer allocations
- L279 _public prototype_ `FLidarPointCloudDataBufferManager(const int32& BufferSize, const int32& MaxNumberOfBuffers = 0);` — If MaxNumberOfBuffers is 0, no limit is applied
- L280 _public prototype_ `~FLidarPointCloudDataBufferManager();`
- L281 _public prototype_ `FLidarPointCloudDataBufferManager(const FLidarPointCloudDataBufferManager&) = delete;`
- L282 _public prototype_ `FLidarPointCloudDataBufferManager(FLidarPointCloudDataBufferManager&&) = delete;`
- L283 _public prototype_ `FLidarPointCloudDataBufferManager& operator=(const FLidarPointCloudDataBufferManager&) = delete;`
- L284 _public prototype_ `FLidarPointCloudDataBufferManager& operator=(FLidarPointCloudDataBufferManager&&) = delete;`
- L286 _public prototype_ `FLidarPointCloudDataBuffer* GetFreeBuffer();`
- L288 _public prototype_ `void Resize(const int32& NewBufferSize);`
- L291 _private member_ `int32 BufferSize;`
- L292 _private member_ `int32 MaxNumberOfBuffers;`
- L293 _private member_ `int32 NumBuffersCreated;`
- L294 _private member_ `TList<FLidarPointCloudDataBuffer> Head;`
- L295 _private member_ `TList<FLidarPointCloudDataBuffer>* Tail;`

#### struct `FLidarPointCloudRay`  
`struct FLidarPointCloudRay`  
_L299-396_
- desc: Used for Raycasting
- L302 _public member_ `FVector3f Origin;`
- L305 _private member_ `FVector3f Direction;`
- L306 _private member_ `FVector3f InvDirection;`
- L309 _public function_ `FLidarPointCloudRay() : FLidarPointCloudRay(FVector3f::ZeroVector, FVector3f::ForwardVector)`
- L310 _public function_ `FLidarPointCloudRay(const FVector3f& Origin, const FVector3f& Direction) : Origin(Origin)`
- L314 _public function_ `FLidarPointCloudRay(const FVector& Origin, const FVector& Direction) : FLidarPointCloudRay((FVector3f)Origin, (FVector3f)Direction)`
- L316 _public function_ `static inline FLidarPointCloudRay FromLocations(const FVector3f& Origin, const FVector3f& Destination)`
- L321 _public function_ `FLidarPointCloudRay& TransformBy(const FTransform& Transform)`
- L327 _public function_ `FLidarPointCloudRay TransformBy(const FTransform& Transform) const`
- L331 _public function_ `inline FLidarPointCloudRay ShiftBy(const FVector3f& Offset) const`
- L335 _public function_ `inline FLidarPointCloudRay ShiftBy(const FVector& Offset) const`
- L340 _public function_ `inline FVector3f GetDirection() const`
- L341 _public function_ `inline void SetDirection(const FVector3f& NewDirection)`
- L348 _public function_ `inline bool Intersects(const FBox& Box) const` — An Efficient and Robust Ray-Box Intersection Algorithm. Amy Williams et al. 2004.
- L382 _public function_ `inline bool Intersects(const FLidarPointCloudPoint* Point, const float& RadiusSq) const`

#### enum `ELidarClippingVolumeMode`  
`enum class ELidarClippingVolumeMode : uint8`  
_L399-405_
- reflection: `UENUM(BlueprintType)`
- L402 _public enumerator_ `ClipInside` — This will clip all points inside the volume
- L404 _public enumerator_ `ClipOutside` — This will clip all points outside of the volume

#### struct `FLidarPointCloudClippingVolumeParams`  
`struct FLidarPointCloudClippingVolumeParams`  
_L408-421_
- desc: Used to pass clipping information for async processing, to avoid accessing UObjects in non-GT
- L410 _public member_ `ELidarClippingVolumeMode Mode;`
- L411 _public member_ `int32 Priority;`
- L412 _public member_ `FBox Bounds;`
- L413 _public member_ `FMatrix PackedShaderData;`
- L415 _public function_ `inline bool operator<(const FLidarPointCloudClippingVolumeParams& O) const`
- L420 _public prototype_ `FLidarPointCloudClippingVolumeParams(const class ALidarClippingVolume* ClippingVolume);`

#### enum `ELidarPointCloudColorationMode`  
`enum class ELidarPointCloudColorationMode : uint8`  
_L424-438_
- reflection: `UENUM(BlueprintType)`
- L427 _public enumerator_ `None` — Uses color tint only
- L429 _public enumerator_ `Data` — Uses imported RGB / Intensity data
- L431 _public enumerator_ `DataWithClassificationAlpha` — Uses imported RGB / Intensity data combined with Alpha mask from Classification Colors
- L433 _public enumerator_ `Elevation` — The cloud's color will be overridden with elevation-based color
- L435 _public enumerator_ `Position` — The cloud's color will be overridden with relative position-based color
- L437 _public enumerator_ `Classification` — Uses Classification ID of the point along with the component's Classification Colors property to sample the color

#### enum `ELidarPointCloudSpriteShape`  
`enum class ELidarPointCloudSpriteShape : uint8`  
_L441-445_
- reflection: `UENUM(BlueprintType)`
- L443 _public enumerator_ `Square`
- L444 _public enumerator_ `Circle`

#### struct `FLidarPointCloudComponentRenderParams`  
`struct FLidarPointCloudComponentRenderParams`  
_L448-486_
- desc: Convenience struct to group all component's rendering params into one
- L450 _public member_ `int32 MinDepth;`
- L451 _public member_ `int32 MaxDepth;`
- L453 _public member_ `float BoundsScale;`
- L454 _public member_ `FVector3f BoundsSize;`
- L455 _public member_ `FVector3f LocationOffset;`
- L456 _public member_ `float ComponentScale;`
- L458 _public member_ `float PointSize;`
- L459 _public member_ `float PointSizeBias;`
- L460 _public member_ `float GapFillingStrength;`
- L462 _public member_ `bool bOwnedByEditor;`
- L463 _public member_ `bool bDrawNodeBounds;`
- L464 _public member_ `bool bUseScreenSizeScaling;`
- L465 _public member_ `bool bShouldRenderFacingNormals;`
- L466 _public member_ `bool bUseFrustumCulling;`
- L468 _public member_ `ELidarPointCloudColorationMode ColorSource;`
- L469 _public member_ `ELidarPointCloudSpriteShape PointShape;`
- L470 _public member_ `ELidarPointCloudScalingMethod ScalingMethod;`
- L472 _public member_ `FVector4f Saturation;`
- L473 _public member_ `FVector4f Contrast;`
- L474 _public member_ `FVector4f Gamma;`
- L475 _public member_ `FVector4f Offset;`
- L476 _public member_ `FVector3f ColorTint;`
- L477 _public member_ `float IntensityInfluence;`
- L479 _public member_ `TMap<int32, FLinearColor> ClassificationColors;`
- L480 _public member_ `FLinearColor ElevationColorBottom;`
- L481 _public member_ `FLinearColor ElevationColorTop;`
- L483 _public member_ `class UMaterialInterface* Material = nullptr;`
- L485 _public prototype_ `void UpdateFromComponent(class ULidarPointCloudComponent* Component);`

#### struct `FBenchmarkTimer`  
`struct FBenchmarkTimer`  
_L488-512_
- L490 _public function_ `static void Reset()`
- L494 _public function_ `static double Split(uint8 Decimal = 2)`
- L504 _public function_ `static void Log(FString Text, uint8 Decimal = 2)`
- L511 _private member_ `static double Time;`

#### struct `FScopeBenchmarkTimer`  
`struct FScopeBenchmarkTimer`  
_L514-554_
- L517 _public member_ `bool bActive;`
- L520 _private member_ `double Time;`
- L521 _private member_ `FString Label;`
- L522 _private member_ `float* OutTimer;`
- L525 _public function_ `FScopeBenchmarkTimer(const FString& Label) : bActive(true) , Time(FPlatformTime::Seconds()) , Label(Label) , OutTimer(nullptr)`
- L532 _public function_ `FScopeBenchmarkTimer(float* OutTimer) : bActive(true) , Time(FPlatformTime::Seconds()) , OutTimer(OutTimer)`
- L538 _public function_ `~FScopeBenchmarkTimer()`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLidarPointCloud, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLidarPointCloud, Log, All);`
- L9 _delegate_ `DECLARE_STATS_GROUP(TEXT("Lidar Point Cloud"), STATGROUP_LidarPointCloud, S`
- L11 _macro_ `#define PC_LOG(Format, ...) UE_LOG(LogLidarPointCloud, Log, TEXT(Format), ##__VA_ARGS__)`
- L12 _macro_ `#define PC_WARNING(Format, ...) UE_LOG(LogLidarPointCloud, Warning, TEXT(Format), ##__VA_ARGS__)`
- L13 _macro_ `#define PC_ERROR(Format, ...) UE_LOG(LogLidarPointCloud, Error, TEXT(Format), ##__VA_ARGS__)`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/Meshing/LidarPointCloudMeshing.h` (Public)


#### struct `LidarPointCloudMeshing::FVertexData`  
`struct FVertexData`  
_L15-23_
- L17 _public member_ `FVector3f Position;`
- L18 _public member_ `FVector3f Normal;`
- L19 _public member_ `FColor Color;`
- L21 _public function_ `FVertexData()`
- L22 _public function_ `FVertexData(const FVector3f& Position, const FVector3f& Normal, const FColor& Color) : Position(Position), Normal(Normal), Color(Color)`

#### struct `LidarPointCloudMeshing::FMeshBuffers`  
`struct FMeshBuffers`  
_L25-34_
- L27 _public member_ `TArray<uint32> Indices;`
- L28 _public member_ `TArray<FVertexData> Vertices;`
- L29 _public member_ `FBoxSphereBounds Bounds;`
- L31 _public prototype_ `void Init(uint32 Capacity, bool bExpandIfNotEmpty, uint32& OutIndexOffset, uint32& OutVertexOffset);`
- L32 _public prototype_ `void ExpandBounds(const FBox& NewBounds);`
- L33 _public prototype_ `void NormalizeNormals();`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace LidarPointCloudMeshing`
- L36 _prototype_ `void CalculateNormals(FLidarPointCloudOctree* Octree, FThreadSafeBool* bCancelled, int32 Quality, float Tolerance, TArray64<FLidarPointCloudPoint*>& InPointSelection);` (scope `LidarPointCloudMeshing`)
- L37 _prototype_ `void BuildCollisionMesh(FLidarPointCloudOctree* Octree, const float& CellSize, FTriMeshCollisionData* CollisionMesh);` (scope `LidarPointCloudMeshing`)
- L38 _prototype_ `void BuildStaticMeshBuffers(FLidarPointCloudOctree* Octree, const float& CellSize, bool bUseSelection, FMeshBuffers* OutMeshBuffers, const FTransform& Transform);` (scope `LidarPointCloudMeshing`)

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/Rendering/LidarPointCloudRendering.h` (Public)


#### struct `FLidarPointCloudSceneProxyWrapper`  
`struct FLidarPointCloudSceneProxyWrapper`  
_L11-15_
- desc: This allows the LOD Manager to observe the SceneProxy via weak pointer
- L13 _public member_ `ILidarPointCloudSceneProxy* Proxy;`
- L14 _public function_ `FLidarPointCloudSceneProxyWrapper(ILidarPointCloudSceneProxy* Proxy) : Proxy(Proxy)`

#### struct `FLidarPointCloudProxyUpdateDataNode`  
`struct FLidarPointCloudProxyUpdateDataNode`  
_L17-47_
- L20 _private member_ `struct FLidarPointCloudOctreeNode* DataNode;`
- L23 _public member_ `uint8 VirtualDepth;`
- L24 _public member_ `int64 NumVisiblePoints;`
- L30 _public member_ `TSharedPtr<class FLidarPointCloudRenderBuffer> DataCache;` — Holds render data pointers for this node This allows us to avoid exposing potentially invalid DataNode pointer in Render Thread
- L31 _public member_ `TSharedPtr<class FLidarPointCloudVertexFactory> VertexFactory;`
- L32 _public member_ `TSharedPtr<class FLidarPointCloudRayTracingGeometry> RayTracingGeometry;`
- L34 _public function_ `FLidarPointCloudProxyUpdateDataNode() : FLidarPointCloudProxyUpdateDataNode(0, 0, nullptr)`
- L35 _public function_ `FLidarPointCloudProxyUpdateDataNode(uint8 VirtualDepth, int64 NumVisiblePoints, FLidarPointCloudOctreeNode* DataNode) : DataNode(DataNode) , VirtualDepth(VirtualDepth) , NumVisiblePoints(NumVisiblePoints) , DataCache(nullptr) , VertexFactory(nullptr) , RayTracingGeometry(nullptr)`
- L46 _public prototype_ `bool BuildDataCache(bool bUseStaticBuffers, bool bUseRayTracing);` — Passthrough method

#### struct `FLidarPointCloudProxyUpdateData`  
`struct FLidarPointCloudProxyUpdateData`  
_L50-77_
- desc: Used to pass data to RT to update the proxy's render data
- L52 _public member_ `TWeakPtr<FLidarPointCloudSceneProxyWrapper, ESPMode::ThreadSafe> SceneProxyWrapper;`
- L55 _public member_ `int32 NumElements;` — Number of elements within the structured buffer related to this proxy
- L57 _public member_ `TArray<FLidarPointCloudProxyUpdateDataNode> SelectedNodes;`
- L59 _public member_ `float VDMultiplier;`
- L60 _public member_ `float RootCellSize;`
- L62 _public member_ `bool bUseStaticBuffers;`
- L63 _public member_ `bool bUseRayTracing;`
- L65 _public member_ `TArray<uint32> TreeStructure;`
- L69 _public member_ `TArray<FBox> Bounds;` — Stores bounds of selected nodes, used for debugging
- L72 _public member_ `TArray<FLidarPointCloudClippingVolumeParams> ClippingVolumes;`
- L74 _public member_ `FLidarPointCloudComponentRenderParams RenderParams;`
- L76 _public prototype_ `FLidarPointCloudProxyUpdateData();`

#### class `ILidarPointCloudSceneProxy`  
`class ILidarPointCloudSceneProxy`  
_L80-85_
- desc: Used for communication between LOD Manager and SceneProxy
- L84 _public prototype_ `virtual void UpdateRenderData(const FLidarPointCloudProxyUpdateData& InRenderData) = 0;` — Updates necessary render data for the proxy. Initiated via LOD Manager's Tick
