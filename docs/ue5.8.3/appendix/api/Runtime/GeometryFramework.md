# Runtime / GeometryFramework

- module root: `Source/Runtime/GeometryFramework`
- headers: 14; symbols: 637
- symbol kinds: class=25, delegate=6, enum=10, enumerator=43, function=125, macro=1, member=165, namespace=4, prototype=247, struct=5, typedef=6
- PrivateDependencyModuleNames: EditorWidgets, Slate
- PrivateIncludePathModuleNames: LevelEditor
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GeometryCore, InteractiveToolsFramework, MeshConversion, MeshDescription, PhysicsCore, RHI, RenderCore, SkeletalMeshDescription, StaticMeshDescription
- PublicIncludePathModuleNames: Shaders

### `Source/Runtime/GeometryFramework/Private/Components/DynamicMeshSceneProxy.h` (Private)


#### class `FDynamicMeshSceneProxy`  
`class FDynamicMeshSceneProxy final : public FBaseDynamicMeshSceneProxy`  
_L22-710_
- inherits: `FBaseDynamicMeshSceneProxy`
- desc: Scene Proxy for UDynamicMeshComponent. Based on FProceduralMeshSceneProxy but simplified in various ways. Supports wireframe-on-shaded rendering.
- L24 _private typedef_ `using FIndex2i = UE::Geometry::FIndex2i;`
- L25 _private typedef_ `using FIndex3i = UE::Geometry::FIndex3i;`
- L27 _private member_ `FMaterialRelevance MaterialRelevance;`
- L30 _private member_ `TArray<FMeshRenderBufferSet*> RenderBufferSets;` — note: FBaseDynamicMeshSceneProxy owns and will destroy these
- L33 _private member_ `bool bIsSingleBuffer = false;` — if true, we store entire mesh in single RenderBuffers and we can do some optimizations
- L37 _public member_ `UDynamicMeshComponent* ParentComponent;` — Component that created this proxy (is there a way to look this up?)
- L40 _public function_ `FDynamicMeshSceneProxy(UDynamicMeshComponent* Component) : FBaseDynamicMeshSceneProxy(Component) , MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetShaderPlatform()))`
- L48 _public function_ `virtual void GetActiveRenderBufferSets(TArray<FMeshRenderBufferSet*>& Buffers) const override`
- L55 _public function_ `void Initialize()`
- L96 _public function_ `TUniqueFunction<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> MakeTangentsFunc(bool bSkipAutoCompute = false)`
- L135 _public function_ `void InitializeFromDecomposition(TUniquePtr<FMeshRenderDecomposition>& Decomposition)` — Initialize multiple buffers for the mesh based on the given Decomposition
- L198 _public function_ `void InitializeSingleBufferSet(FMeshRenderBufferSet* RenderBuffers)` — Initialize a single set of mesh buffers for the entire mesh
- L238 _public function_ `void InitializeByMaterial(TArray<FMeshRenderBufferSet*>& BufferSets)` — Initialize the mesh buffers, one per material
- L331 _public function_ `bool RenderMeshLayoutMatchesRenderBuffers() const`
- L403 _public function_ `void FastUpdateVertices(bool bPositions, bool bNormals, bool bColors, bool bUVs)` — Update the vertex position/normal/color buffers
- L502 _public function_ `void FastUpdateVertices(const TArray<int32>& WhichBuffers, bool bPositions, bool bNormals, bool bColors, bool bUVs)` — Update the vertex position/normal/color buffers
- L585 _public function_ `void FastUpdateAllIndexBuffers()` — Update index buffers inside each RenderBuffer set
- L617 _public function_ `void FastUpdateIndexBuffers(const TArray<int32>& WhichBuffers)` — Update index buffers inside each RenderBuffer set
- L653 _public function_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override`
- L681 _public function_ `virtual void UpdatedReferencedMaterials() override`
- L690 _public function_ `virtual void GetLightRelevance(const FLightSceneProxy* LightSceneProxy, bool& bDynamic, bool& bRelevant, bool& bLightMapped, bool& bShadowMapped) const override`
- L695 _public function_ `virtual bool CanBeOccluded() const override`
- L700 _public function_ `virtual uint32 GetMemoryFootprint(void) const override`
- L702 _public function_ `uint32 GetAllocatedSize(void) const`
- L704 _public function_ `SIZE_T GetTypeHash() const override`

#### Free symbols / members of external scopes

- L107 _function_ `` (scope `FDynamicMeshSceneProxy::MakeTangentsFunc`)
- L168 _function_ `` (scope `FDynamicMeshSceneProxy::InitializeFromDecomposition`)
- L181 _function_ `` (scope `FDynamicMeshSceneProxy::InitializeFromDecomposition::__anonb57e29c90402`)
- L228 _function_ `` (scope `FDynamicMeshSceneProxy::InitializeSingleBufferSet`)
- L271 _function_ `` (scope `FDynamicMeshSceneProxy::InitializeByMaterial`)
- L336 _function_ `` (scope `FDynamicMeshSceneProxy::RenderMeshLayoutMatchesRenderBuffers`)
- L457 _function_ `` (scope `FDynamicMeshSceneProxy::FastUpdateVertices`)
- L489 _function_ `` (scope `FDynamicMeshSceneProxy::FastUpdateVertices::__anonb57e29c90b02`)
- L572 _function_ `` (scope `FDynamicMeshSceneProxy::FastUpdateVertices::__anonb57e29c90d02`)
- L593 _function_ `` (scope `FDynamicMeshSceneProxy::FastUpdateAllIndexBuffers`)
- L605 _function_ `` (scope `FDynamicMeshSceneProxy::FastUpdateAllIndexBuffers::__anonb57e29c90f02`)
- L625 _function_ `` (scope `FDynamicMeshSceneProxy::FastUpdateIndexBuffers`)
- L641 _function_ `` (scope `FDynamicMeshSceneProxy::FastUpdateIndexBuffers::__anonb57e29c91102`)

### `Source/Runtime/GeometryFramework/Public/Changes/MeshChange.h` (Public)


#### class `FMeshChange`  
`class FMeshChange : public FMeshRegionChangeBase`  
_L31-63_
- inherits: `FMeshRegionChangeBase`
- desc: FMeshChange represents an undoable change to a FDynamicMesh3. Currently only valid to call Apply/Revert when the Object is a one of several components backed by FDynamicMesh: UDynamicMeshComponent, UOctreeDynamicMeshComponent, UPreviewMesh
- L34 _public prototype_ `FMeshChange();`
- L35 _public prototype_ `FMeshChange(TUniquePtr<UE::Geometry::FDynamicMeshChange> DynamicMeshChangeIn);`
- L36 _public prototype_ `~FMeshChange();`
- L38 _public member_ `TUniquePtr<UE::Geometry::FDynamicMeshChange> DynamicMeshChange;`
- L41 _public member_ `TFunction<void(FMeshChange*, UObject*, bool)> OnChangeAppliedFunc;` — This function is called on Apply and Revert (last argument is true on Apply)
- L44 _public prototype_ `virtual void Apply(UObject* Object) override;` — Makes the change to the object
- L47 _public prototype_ `virtual void Revert(UObject* Object) override;` — Reverts change to the object
- L50 _public prototype_ `virtual void ProcessChangeVertices(const UE::Geometry::FDynamicMesh3* ChangedMesh, TFunctionRef<void(TConstArrayView<int32>)> ProcessFn, bool bRevert) const override;` — FRegionMeshChangeBase API -- builds an array of all vertices changed and passes to the ProcessFn lambda
- L53 _public prototype_ `virtual FString ToString() const override;` — Describes this change (for debugging)
- L62 _public prototype_ `virtual void ApplyChangeToMesh(UE::Geometry::FDynamicMesh3* Mesh, bool bRevert) const;` — Apply embedded DynamicMeshChange to given Mesh. This function is for change-targets to call, when passed a FMeshChange to apply to a Mesh they own. This allows FMeshChange subclasses to customize the change behavior if necessary. The default behavior just forwards the call to DynamicMeshChange->Apply(Mesh, bRevert).

#### class `UMeshCommandChangeTarget`  
`class UMeshCommandChangeTarget : public UInterface`  
_L70-73_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMeshCommandChangeTarget`  
`class IMeshCommandChangeTarget`  
_L77-82_
- desc: IMeshCommandChangeTarget is an interface which is used to apply a mesh change
- L81 _public prototype_ `virtual void ApplyChange(const FMeshChange* Change, bool bRevert) = 0;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Geometry` (scope `UE`)

### `Source/Runtime/GeometryFramework/Public/Changes/MeshRegionChange.h` (Public)


#### class `FMeshRegionChangeBase`  
`class FMeshRegionChangeBase : public FToolCommandChange`  
_L10-17_
- inherits: `FToolCommandChange`
- desc: Base class for mesh changes that apply to a selection of the mesh
- L16 _public prototype_ `virtual void ProcessChangeVertices(const UE::Geometry::FDynamicMesh3* ChangedMesh, TFunctionRef<void(TConstArrayView<int32>)> ProcessFn, bool bRevert) const = 0;` — @param ChangedMesh The mesh after the change has been applied (or undone, if bRevert is true) @param ProcessFn The callback that will be called with the vertices affected by this mesh change @param bRevert Whether the changes is an undo

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Geometry` (scope `UE`)

### `Source/Runtime/GeometryFramework/Public/Changes/MeshReplacementChange.h` (Public)


#### class `FMeshReplacementChange`  
`class FMeshReplacementChange : public FMeshRegionChangeBase`  
_L26-53_
- inherits: `FMeshRegionChangeBase`
- desc: FMeshReplacementChange represents an undoable *complete* change to a FDynamicMesh3. Currently only valid to call Apply/Revert when the Object is a UDynamicMeshComponent
- L28 _private member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> Before, After;`
- L28 _private member_ `TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> Before, After;`
- L31 _public prototype_ `FMeshReplacementChange();`
- L32 _public prototype_ `FMeshReplacementChange(TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> Before, TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe> After);`
- L34 _public function_ `const TSharedPtr<const FDynamicMesh3, ESPMode::ThreadSafe>& GetMesh(bool bRevert) const`
- L40 _public member_ `TFunction<void(FMeshReplacementChange*, UObject*, bool)> OnChangeAppliedFunc;` — This function is called on Apply and Revert (last argument is true on Apply)
- L43 _public prototype_ `virtual void Apply(UObject* Object) override;` — Makes the change to the object
- L46 _public prototype_ `virtual void Revert(UObject* Object) override;` — Reverts change to the object
- L49 _public prototype_ `virtual void ProcessChangeVertices(const UE::Geometry::FDynamicMesh3* ChangedMesh, TFunctionRef<void(TConstArrayView<int32>)> ProcessFn, bool bRevert) const override;` — FRegionMeshChangeBase API -- passes all mesh vertex IDs as an array to the ProcessFn lambda
- L52 _public prototype_ `virtual FString ToString() const override;` — Describes this change (for debugging)

#### class `UMeshReplacementCommandChangeTarget`  
`class UMeshReplacementCommandChangeTarget : public UInterface`  
_L60-63_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMeshReplacementCommandChangeTarget`  
`class IMeshReplacementCommandChangeTarget`  
_L67-72_
- desc: IMeshReplacementCommandChangeTarget is an interface which is used to apply a mesh replacement change
- L71 _public prototype_ `virtual void ApplyChange(const FMeshReplacementChange* Change, bool bRevert) = 0;`

#### Free symbols / members of external scopes

- L18 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Source/Runtime/GeometryFramework/Public/Changes/MeshVertexChange.h` (Public)


#### class `FMeshVertexChange`  
`class FMeshVertexChange : public FMeshRegionChangeBase`  
_L21-53_
- inherits: `FMeshRegionChangeBase`
- desc: FMeshVertexChange represents an reversible change to a set of vertex positions, normals, colors and UVs Currently only a UDynamicMeshComponent target is supported. @todo support optionally storing old/new normals and tangents @todo support applying to a StaticMeshComponent/MeshDescription ?
- L24 _public member_ `bool bHaveVertexPositions = true;`
- L25 _public member_ `bool bHaveVertexColors = false;`
- L26 _public member_ `TArray<int32> Vertices;`
- L27 _public member_ `TArray<FVector3d> OldPositions;`
- L28 _public member_ `TArray<FVector3d> NewPositions;`
- L29 _public member_ `TArray<FVector3f> OldColors;`
- L30 _public member_ `TArray<FVector3f> NewColors;`
- L32 _public member_ `bool bHaveOverlayNormals = false;`
- L33 _public member_ `TArray<int32> Normals;`
- L34 _public member_ `TArray<FVector3f> OldNormals;`
- L35 _public member_ `TArray<FVector3f> NewNormals;`
- L37 _public member_ `bool bHaveOverlayUVs = false;`
- L38 _public member_ `TArray<int32> UVs;`
- L39 _public member_ `TArray<FVector2f> OldUVs;`
- L40 _public member_ `TArray<FVector2f> NewUVs;`
- L43 _public prototype_ `virtual void Apply(UObject* Object) override;` — Makes the change to the object
- L46 _public prototype_ `virtual void Revert(UObject* Object) override;` — Reverts change to the object
- L49 _public prototype_ `virtual void ProcessChangeVertices(const UE::Geometry::FDynamicMesh3* ChangedMesh, TFunctionRef<void(TConstArrayView<int32>)> ProcessFn, bool bRevert) const override;` — FRegionMeshChangeBase API -- passes the Vertices array to the ProcessFn lambda
- L52 _public prototype_ `virtual FString ToString() const override;` — Describes this change (for debugging)

#### enum `EMeshVertexChangeComponents`  
`enum class EMeshVertexChangeComponents : uint8`  
_L56-63_
- L58 _public enumerator_ `None = 0`
- L59 _public enumerator_ `VertexPositions = 1`
- L60 _public enumerator_ `VertexColors = 2`
- L61 _public enumerator_ `OverylayUVs = 4`
- L62 _public enumerator_ `OverlayNormals = 16`

#### class `FMeshVertexChangeBuilder`  
`class FMeshVertexChangeBuilder`  
_L70-117_
- desc: FMeshVertexChangeBuilder can be used to construct a FMeshVertexChange.
- L73 _public member_ `TUniquePtr<FMeshVertexChange> Change;`
- L74 _public member_ `TMap<int32, int32> SavedVertices;`
- L75 _public member_ `bool bSavePositions = true;`
- L76 _public member_ `bool bSaveColors = false;`
- L78 _public member_ `bool bSaveOverlayNormals = false;`
- L79 _public member_ `TMap<int32, int32> SavedNormalElements;`
- L81 _public member_ `bool bSaveOverlayUVs = false;`
- L82 _public member_ `TMap<int32, int32> SavedUVElements;`
- L85 _public member_ `TUniqueFunction<void(int32, int32)> OnNewVertexSaved = nullptr;` — If set, this function is called whenever a newly-seen VertexID is saved, parameters are (VertexID, Index) into saved-vertices array
- L87 _public prototype_ `FMeshVertexChangeBuilder();`
- L88 _public prototype_ `explicit FMeshVertexChangeBuilder(EMeshVertexChangeComponents Components);`
- L90 _public prototype_ `void SaveVertexInitial(const FDynamicMesh3* Mesh, int32 VertexID);`
- L91 _public prototype_ `void SaveVertexFinal(const FDynamicMesh3* Mesh, int32 VertexID);`
- L94 _public prototype_ `template<typename Enumerable> void SaveVertices(const FDynamicMesh3* Mesh, Enumerable Enum, bool bInitial);`
- L96 _public prototype_ `void SaveOverlayNormals(const FDynamicMesh3* Mesh, const TArray<int32>& ElementIDs, bool bInitial);`
- L97 _public prototype_ `void SaveOverlayNormals(const FDynamicMesh3* Mesh, const TSet<int32>& ElementIDs, bool bInitial);`
- L99 _public prototype_ `void SaveOverlayUVs(const FDynamicMesh3* Mesh, const TArray<int32>& ElementIDs, bool bInitial);`
- L100 _public prototype_ `void SaveOverlayUVs(const FDynamicMesh3* Mesh, const TSet<int32>& ElementIDs, bool bInitial);`
- L104 _public prototype_ `void UpdateVertex(int32 VertexID, const FVector3d& OldPosition, const FVector3d& NewPosition);` — currently only used in vertex sculpt tool. cannot be used if bSaveColors = true
- L107 _public prototype_ `void UpdateVertexColor(int32 VertexID, const FVector3f& OldColor, const FVector3f& NewColor);` — currently only used in element paint tool. Can only be used if bSaveColors=true and bSavePositions=false
- L110 _protected prototype_ `void UpdateVertexFinal(int32 VertexID, const FVector3d& NewPosition);`
- L112 _protected prototype_ `void UpdateOverlayNormal(int32 ElementID, const FVector3f& OldNormal, const FVector3f& NewNormal);`
- L113 _protected prototype_ `void UpdateOverlayNormalFinal(int32 ElementID, const FVector3f& NewNormal);`
- L115 _protected prototype_ `void UpdateOverlayUV(int32 ElementID, const FVector2f& OldUV, const FVector2f& NewUV);`
- L116 _protected prototype_ `void UpdateOverlayUVFinal(int32 ElementID, const FVector2f& NewUV);`
- L141 _function_ `template<typename Enumerable> void FMeshVertexChangeBuilder::SaveVertices(const FDynamicMesh3* Mesh, Enumerable Enum, bool bInitial)`

#### class `UMeshVertexCommandChangeTarget`  
`class UMeshVertexCommandChangeTarget : public UInterface`  
_L122-125_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMeshVertexCommandChangeTarget`  
`class IMeshVertexCommandChangeTarget`  
_L129-134_
- desc: IMeshVertexCommandChangeTarget is an interface which is used to apply a FMeshVertexChange
- L133 _public prototype_ `virtual void ApplyChange(const FMeshVertexChange* Change, bool bRevert) = 0;`

#### Free symbols / members of external scopes

- L12 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`
- L64 _prototype_ `ENUM_CLASS_FLAGS(EMeshVertexChangeComponents);`

### `Source/Runtime/GeometryFramework/Public/Components/BaseDynamicMeshComponent.h` (Public)


#### enum `EMeshRenderAttributeFlags`  
`enum class EMeshRenderAttributeFlags : uint8`  
_L28-38_
- desc: EMeshRenderAttributeFlags is used to identify different mesh rendering attributes, for things like fast-update functions
- L30 _public enumerator_ `None = 0`
- L31 _public enumerator_ `Positions = 1`
- L32 _public enumerator_ `VertexColors = 1<<1`
- L33 _public enumerator_ `VertexNormals = 1<<2`
- L34 _public enumerator_ `VertexUVs = 1<<3`
- L35 _public enumerator_ `SecondaryIndexBuffers = 1<<4`
- L37 _public enumerator_ `AllVertexAttribs = Positions | VertexColors | VertexNormals | VertexUVs`

#### enum `EDynamicMeshComponentTangentsMode`  
`enum class EDynamicMeshComponentTangentsMode : uint8`  
_L47-57_
- reflection: `UENUM(BlueprintType)`
- desc: Tangent calculation modes
- L50 _public enumerator_ `NoTangents` — Tangents are not used/available, proceed accordingly (eg generate arbitrary orthogonal basis)
- L52 _public enumerator_ `AutoCalculated` — Tangents will be automatically calculated on demand. Note that mesh changes due to tangents calculation will *not* be broadcast via MeshChange events!
- L54 _public enumerator_ `ExternallyProvided UMETA(DisplayName = "From Dynamic Mesh")` — Tangents are externally provided via the FDynamicMesh3 AttributeSet
- L56 _public enumerator_ `Default = 255` — Tangents mode will be set to the most commonly-useful default -- currently "From Dynamic Mesh"

#### enum `EDynamicMeshComponentColorOverrideMode`  
`enum class EDynamicMeshComponentColorOverrideMode : uint8`  
_L64-74_
- reflection: `UENUM(BlueprintType)`
- desc: Color Override Modes
- L67 _public enumerator_ `None` — No Color Override enabled
- L69 _public enumerator_ `VertexColors` — Vertex Colors are displayed
- L71 _public enumerator_ `Polygroups` — Polygroup Colors are displayed
- L73 _public enumerator_ `Constant` — Constant Color is displayed

#### enum `EDynamicMeshDrawPath`  
`enum class EDynamicMeshDrawPath : uint8`  
_L81-87_
- reflection: `UENUM(BlueprintType)`
- desc: Draw Path to use
- L84 _public enumerator_ `DynamicDraw = 0` — Use the dynamic draw path, intended for meshes that update on most frames
- L86 _public enumerator_ `StaticDraw = 1` — Use the static draw path, for meshes that do not change on most frames

#### enum `EDynamicMeshComponentDistanceFieldMode`  
`enum class UE_DEPRECATED(5.0, "Dynamic Mesh distance field support has been deprecated") EDynamicMeshComponentDistanceFieldMode : uint8`  
_L94-100_
- reflection: `UENUM(BlueprintType)`
- desc: Mesh Signed Distance Field (SDF) mode
- L97 _public enumerator_ `NoDistanceField = 0` — Do not compute a distance field
- L99 _public enumerator_ `AsyncCPUDistanceField = 1 UMETA(DisplayName = "Async CPU Distance Field")` — Compute a distance field in a background thread

#### enum `EDynamicMeshVertexColorTransformMode`  
`enum class EDynamicMeshVertexColorTransformMode : uint8`  
_L109-117_
- reflection: `UENUM(BlueprintType)`
- desc: Color Transform to apply to Vertex Colors when converting from internal DynamicMesh Color attributes (eg Color Overlay stored in FVector4f) to RHI Render Buffers (FColor). Note that UStaticMesh assumes the Source Mesh colors are Linear and always converts to SRGB.
- L112 _public enumerator_ `NoTransform = 0` — Do not apply any color-space transform to Vertex Colors
- L114 _public enumerator_ `LinearToSRGB` — Assume Vertex Colors are in Linear space and transform to SRGB
- L116 _public enumerator_ `SRGBToLinear UMETA(DisplayName = "SRGB To Linear")` — Assume Vertex Colors are in SRGB space and convert to Linear

#### class `UBaseDynamicMeshComponent`  
`class UBaseDynamicMeshComponent : public UMeshComponent, public IToolFrameworkComponent, public IMeshVertexCommandChangeTarget, public IMeshCommandChangeTarget, public IMeshReplacementCommandChangeTarget`  
_L124-737_
- reflection: `UCLASS(Abstract, hidecategories = (LOD), ClassGroup = Rendering, MinimalAPI)`
- inherits: `UMeshComponent,IToolFrameworkComponent,IMeshVertexCommandChangeTarget,IMeshCommandChangeTarget,IMeshReplacementCommandChangeTarget`
- desc: UBaseDynamicMeshComponent is a base interface for a UMeshComponent based on a UDynamicMesh.
- L141 _public function_ `virtual void SetMesh(UE::Geometry::FDynamicMesh3&& MoveMesh)` — initialize the internal mesh from a DynamicMesh
- L150 _public function_ `virtual FDynamicMesh3* GetMesh()` — @return pointer to internal mesh @warning avoid usage of this function, access via GetDynamicMesh() instead
- L159 _public function_ `virtual const FDynamicMesh3* GetMesh() const` — @return pointer to internal mesh
- L168 _public function_ `virtual void ProcessMesh(TFunctionRef<void(const UE::Geometry::FDynamicMesh3&)> ProcessFunc) const` — Allow external code to read the internal mesh.
- L177 _public function_ `virtual UDynamicMesh* GetDynamicMesh()` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return the child UDynamicMesh
- L187 _public function_ `virtual void NotifyMeshUpdated()` — Call this if you update the mesh via GetMesh() @todo should provide a function that calls a lambda to modify the mesh, and only return const mesh pointer
- L195 _public function_ `virtual void ApplyChange(const FMeshVertexChange* Change, bool bRevert) override` — Apply a vertex deformation change to the internal mesh  (implements IMeshVertexCommandChangeTarget)
- L203 _public function_ `virtual void ApplyChange(const FMeshChange* Change, bool bRevert) override` — Apply a general mesh change to the internal mesh  (implements IMeshCommandChangeTarget)
- L211 _public function_ `virtual void ApplyChange(const FMeshReplacementChange* Change, bool bRevert) override` — Apply a full mesh replacement change to the internal mesh  (implements IMeshReplacementCommandChangeTarget)
- L219 _public function_ `virtual void ApplyTransform(const FTransform3d& Transform, bool bInvert)` — Apply a transform to the mesh
- L230 _protected function_ `virtual FBaseDynamicMeshSceneProxy* GetBaseSceneProxy()` — Subclass must implement this to return scene proxy if available, or nullptr
- L239 _protected function_ `virtual void NotifyMaterialSetUpdated()` — Subclass must implement this to notify allocated proxies of updated materials
- L255 _public member_ `bool bExplicitShowWireframe = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Rendering", meta = (DisplayName = "Wireframe Overlay"))` — If true, render the Wireframe on top of the Shaded Mesh
- L261 _public function_ `virtual void SetEnableWireframeRenderPass(bool bEnable)` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Configure whether wireframe rendering is enabled or not
- L267 _public function_ `virtual bool GetEnableWireframeRenderPass() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return true if wireframe rendering pass is enabled
- L273 _public member_ `FLinearColor WireframeColor = FLinearColor(0, 0.5f, 1.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Rendering", meta = (DisplayName = "Wireframe Color"))` — Constant Color used when Override Color Mode is set to Constant
- L284 _public member_ `EDynamicMeshComponentColorOverrideMode ColorMode = EDynamicMeshComponentColorOverrideMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Rendering", meta = (DisplayName = "Color Override"))`
- L290 _public prototype_ `virtual void SetColorOverrideMode(EDynamicMeshComponentColorOverrideMode NewMode);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering")` — Configure the active Color Override
- L296 _public function_ `virtual EDynamicMeshComponentColorOverrideMode GetColorOverrideMode() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering")` — @return active Color Override mode
- L302 _public member_ `FColor ConstantColor = FColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Rendering", meta = (DisplayName = "Constant Color", EditCondition = "ColorMode==EDynamicMeshComponentColorOverrideMode::Constant"))` — Constant Color used when Override Color Mode is set to Constant
- L308 _public prototype_ `virtual void SetConstantOverrideColor(FColor NewColor);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering")` — Configure the Color used with Constant Color Override Mode
- L314 _public function_ `virtual FColor GetConstantOverrideColor() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering")` — @return active Color used for Constant Color Override Mode
- L324 _public member_ `EDynamicMeshVertexColorTransformMode ColorSpaceMode = EDynamicMeshVertexColorTransformMode::NoTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Rendering", meta = (DisplayName = "Vertex Color Space"))` — Color Space Transform that will be applied to the colors stored in the DynamicMesh Attribute Color Overlay when constructing render buffers. Default is "No Transform", ie color R/G/B/A will be independently converted from 32-bit float to 8-bit by direct mapping. LinearToSRGB mode will apply SRGB conversion, ie assumes colors in the Mesh are in Linear space. This will produce the same behavior as UStaticMesh. SRGBToLinear mode will invert SRGB conversion, ie assumes colors in the Mesh are in SRGB space.
- L330 _public prototype_ `virtual void SetVertexColorSpaceTransformMode(EDynamicMeshVertexColorTransformMode NewMode);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering")` — Configure the active Color Space Transform Mode
- L336 _public function_ `virtual EDynamicMeshVertexColorTransformMode GetVertexColorSpaceTransformMode() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering")` — @return active Color Override mode
- L342 _public prototype_ `virtual void SetTwoSided(bool bEnable);`
- L343 _public function_ `virtual bool GetTwoSided() const`
- L347 _protected member_ `bool bTwoSided = false;` — `UPROPERTY(EditAnywhere, Category = "Dynamic Mesh Component|Rendering")`
- L357 _public member_ `bool bEnableFlatShading = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Rendering", meta = (DisplayName = "Flat Shading"))` — Enable use of per-triangle facet normals in place of mesh normals
- L363 _public prototype_ `virtual void SetEnableFlatShading(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering")` — Configure the Color used with Constant Color Override Mode
- L369 _public function_ `virtual bool GetFlatShadingEnabled() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering")` — @return Whether mesh will be rendered with per-triangle normals
- L381 _public prototype_ `virtual void SetShadowsEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")`
- L384 _public function_ `virtual bool GetShadowsEnabled() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")`
- L387 _public prototype_ `virtual void SetViewModeOverridesEnabled(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")`
- L390 _public function_ `virtual bool GetViewModeOverridesEnabled() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")`
- L399 _public member_ `bool bEnableViewModeOverrides = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Rendering", meta = (DisplayName = "View Mode Overrides"))` — This flag controls whether Editor View Mode Overrides are enabled for this mesh. For example, this controls hidden-line removal on the wireframe in Wireframe View Mode, and whether the normal map will be disabled in Lighting-Only View Mode, as well as various other things. Use SetViewModeOverridesEnabled() to control this setting in Blueprints/C++.
- L411 _public prototype_ `virtual void SetOverrideRenderMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Set an active override render material. This should replace all materials during rendering.
- L417 _public prototype_ `virtual void ClearOverrideRenderMaterial();` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Clear any active override render material
- L423 _public function_ `virtual bool HasOverrideRenderMaterial(int k) const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return true if an override render material is currently enabled for the given MaterialIndex
- L432 _public function_ `virtual UMaterialInterface* GetOverrideRenderMaterial(int MaterialIndex) const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return active override render material for the given MaterialIndex
- L439 _protected member_ `TObjectPtr<UMaterialInterface> OverrideRenderMaterial = nullptr;` — `UPROPERTY()`
- L455 _public prototype_ `virtual void SetSecondaryRenderMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Set an active secondary render material.
- L461 _public prototype_ `virtual void ClearSecondaryRenderMaterial();` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Clear any active secondary render material
- L466 _public function_ `virtual bool HasSecondaryRenderMaterial() const` — @return true if a secondary render material is set
- L475 _public function_ `virtual UMaterialInterface* GetSecondaryRenderMaterial() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return active secondary render material
- L484 _public prototype_ `virtual void SetSecondaryBuffersVisibility(bool bSetVisible);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Show/Hide the secondary triangle buffers. Does not invalidate SceneProxy.
- L490 _public prototype_ `virtual bool GetSecondaryBuffersVisibility() const;` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return true if secondary buffers are currently set to be visible
- L494 _protected member_ `TObjectPtr<UMaterialInterface> SecondaryRenderMaterial = nullptr;` — `UPROPERTY()`
- L496 _protected member_ `bool bDrawSecondaryBuffers = true;`
- L507 _public prototype_ `virtual void SetOverrideWireframeRenderMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Set an active wireframe override render Material
- L513 _public prototype_ `virtual void ClearOverrideWireframeRenderMaterial();` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Clear any active wireframe override render material
- L518 _public function_ `virtual bool HasOverrideWireframeRenderMaterial() const` — @return true if a active wireframe override render material is set
- L527 _public function_ `virtual UMaterialInterface* GetOverrideWireframeRenderMaterial() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return active wireframe override render material
- L534 _protected member_ `TObjectPtr<UMaterialInterface> WireframeMaterialOverride = nullptr;` — `UPROPERTY()`
- L545 _public prototype_ `virtual void SetOverrideSecondaryWireframeRenderMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Set an active secondary wireframe override render material
- L551 _public prototype_ `virtual void ClearOverrideSecondaryWireframeRenderMaterial();` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Clear any active secondary wireframe override render material
- L556 _public function_ `virtual bool HasOverrideSecondaryWireframeRenderMaterial() const` — @return true if a active secondary wireframe override render material is set
- L565 _public function_ `virtual UMaterialInterface* GetOverrideSecondaryWireframeRenderMaterial() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return active secondary wireframe override render material
- L572 _protected member_ `TObjectPtr<UMaterialInterface> SecondaryWireframeMaterialOverride = nullptr;` — `UPROPERTY()`
- L587 _public member_ `bool bEnableRaytracing = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Rendering")` — Enable/disable Raytracing support on this Mesh, if Raytracing is currently enabled in the Project Settings. Use SetEnableRaytracing() to configure this flag in Blueprints/C++.
- L594 _public prototype_ `virtual void SetEnableRaytracing(bool bSetEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Enable/Disable raytracing support. This is an expensive call as it flushes the rendering queue and forces an immediate rebuild of the SceneProxy.
- L600 _public prototype_ `virtual bool GetEnableRaytracing() const;` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return true if raytracing support is currently enabled
- L603 _protected prototype_ `virtual void OnRenderingStateChanged(bool bForceImmedateRebuild);`
- L615 _protected member_ `EDynamicMeshDrawPath DrawPath = EDynamicMeshDrawPath::DynamicDraw;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetMeshDrawPath, BlueprintGetter=GetMeshDrawPath, Category = "Dynamic Mesh Component|Rendering")` — Controls whether to use the dynamic or static draw path
- L619 _protected function_ `virtual bool AllowFastUpdate()` — Whether the fast update paths will be used for the mesh. If false, fast update methods can still be called, but will fall back to recreating the render proxy
- L631 _public prototype_ `virtual void SetMeshDrawPath(EDynamicMeshDrawPath NewDrawPath);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Set the mesh rendering to use the static or dynamic draw path
- L637 _public prototype_ `virtual EDynamicMeshDrawPath GetMeshDrawPath() const;` — `UFUNCTION(BlueprintPure, Category = "Dynamic Mesh Component")` — @return Whether the mesh renders using the static or dynamic draw path
- L644 _protected member_ `EDynamicMeshComponentDistanceFieldMode DistanceFieldMode_DEPRECATED = EDynamicMeshComponentDistanceFieldMode::NoDistanceField;` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Dynamic Mesh distance field support has been deprecated"))` — Controls how distance field is computed
- L652 _public function_ `virtual void SetDistanceFieldMode(EDynamicMeshComponentDistanceFieldMode NewDistFieldMode)` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")` — `UFUNCTION(Category = "Dynamic Mesh Component", meta = (DeprecatedFunction, DeprecationMessage = "Dynamic Mesh distance field support has been deprecated"))` — Configure Distance Field computation mode
- L659 _public function_ `virtual EDynamicMeshComponentDistanceFieldMode GetDistanceFieldMode() const` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")` — `UFUNCTION(Category = "Dynamic Mesh Component", meta = (DeprecatedFunction, DeprecationMessage = "Dynamic Mesh distance field support has been deprecated"))` — @return Method used to compute the distance field
- L665 _protected function_ `virtual void OnNewDistanceFieldMode()` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")` — this will be called if a change to distance field mode is detected
- L675 _public prototype_ `virtual int32 GetNumMaterials() const override;` — UMeshComponent Interface.
- L676 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;`
- L678 _public prototype_ `virtual FMaterialRelevance GetMaterialRelevance(ERHIFeatureLevel::Type InFeatureLevel) const override;` — `UE_DEPRECATED(5.7, "Please use GetMaterialRelevance with EShaderPlatform argument and not ERHIFeatureLevel::Type")`
- L679 _public prototype_ `virtual FMaterialRelevance GetMaterialRelevance(EShaderPlatform InShaderPlatform) const override;`
- L680 _public prototype_ `virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;`
- L681 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L683 _public prototype_ `virtual void SetNumMaterials(int32 NumMaterials);`
- L688 _public prototype_ `virtual TArray<FName> GetMaterialSlotNames() const override;` — @return an array of slot names generated from the current materials
- L690 _public prototype_ `virtual bool IsMaterialSlotNameValid(FName MaterialSlotName) const override;` — @return true if the dynamic mesh has a material with this slot name
- L692 _public prototype_ `virtual UMaterialInterface* GetMaterialByName(FName MaterialSlotName) const override;` — @return a material on this component with this slot name, or null not found
- L696 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L700 _public member_ `TArray<TObjectPtr<UMaterialInterface>> BaseMaterials;` — `UPROPERTY()`
- L717 _public prototype_ `static void SetDefaultWireframeMaterial(UMaterialInterface* Material);` — Set the wireframe material used for all BaseDynamicMeshComponent-derived Components
- L722 _public prototype_ `static void SetDefaultVertexColorMaterial(UMaterialInterface* Material);` — Set the vertex color material used for all BaseDynamicMeshComponent-derived Components
- L725 _protected prototype_ `static void InitializeDefaultMaterials();`
- L728 _protected prototype_ `static UMaterialInterface* GetDefaultWireframeMaterial_RenderThread();`
- L729 _protected prototype_ `static UMaterialInterface* GetDefaultVertexColorMaterial_RenderThread();`
- L735 _private member_ `static UMaterialInterface* DefaultWireframeMaterial;` — these Materials are used by the render thread. Once the engine is running they should not be modified without using SetDefaultWireframeMaterial/SetDefaultVertexColorMaterial
- L736 _private member_ `static UMaterialInterface* DefaultVertexColorMaterial;`

#### Free symbols / members of external scopes

- L39 _prototype_ `ENUM_CLASS_FLAGS(EMeshRenderAttributeFlags);`

### `Source/Runtime/GeometryFramework/Public/Components/BaseDynamicMeshSceneProxy.h` (Public)


#### class `FBaseDynamicMeshSceneProxy`  
`class FBaseDynamicMeshSceneProxy : public FPrimitiveSceneProxy`  
_L38-381_
- inherits: `FPrimitiveSceneProxy`
- desc: FBaseDynamicMeshSceneProxy is an abstract base class for a Render Proxy for a UBaseDynamicMeshComponent, where the assumption is that mesh data will be stored in FMeshRenderBufferSet instances
- L40 _private typedef_ `using FIndex2i = UE::Geometry::FIndex2i;`
- L41 _private typedef_ `using FIndex3i = UE::Geometry::FIndex3i;`
- L43 _public member_ `UBaseDynamicMeshComponent* ParentBaseComponent;`
- L49 _public member_ `FMeshRenderBufferSetConversionUtil MeshRenderBufferSetConverter;` — Utility to initialize and update the mesh render buffers from a mesh with overlays and holds all the settings required.
- L55 _protected member_ `TSet<FMeshRenderBufferSet*> AllocatedBufferSets;` — Set of currently-allocated RenderBuffers. We own these pointers and must clean them up. Must guard access with AllocatedSetsLock!!
- L58 _protected member_ `FCriticalSection AllocatedSetsLock;` — use to control access to AllocatedBufferSets
- L61 _protected member_ `bool bTwoSided = false;` — control whether the mesh is rendered two-sided
- L64 _protected member_ `bool bEnableRaytracing = false;` — control raytracing support
- L67 _protected member_ `bool bEnableViewModeOverrides = true;` — Allow view-mode overrides.
- L70 _protected member_ `bool bPreferStaticDrawPath = false;` — whether to try to use the static draw instead of dynamic draw path; note we may still use the dynamic path if collision or vertex color rendering is enabled
- L73 _public prototype_ `FBaseDynamicMeshSceneProxy(UBaseDynamicMeshComponent* Component);`
- L75 _public prototype_ `virtual ~FBaseDynamicMeshSceneProxy();`
- L87 _public prototype_ `virtual void GetActiveRenderBufferSets(TArray<FMeshRenderBufferSet*>& Buffers) const = 0;` — Return set of active renderbuffers. Must be implemented by subclass. This is the set of render buffers that will be drawn by GetDynamicMeshElements
- L100 _public prototype_ `virtual FMeshRenderBufferSet* AllocateNewRenderBufferSet();` — Allocates a set of render buffers. FPrimitiveSceneProxy will keep track of these buffers and destroy them on destruction.
- L105 _public prototype_ `virtual void ReleaseRenderBufferSet(FMeshRenderBufferSet* BufferSet);` — Explicitly release a set of RenderBuffers
- L113 _public function_ `template<typename TriangleEnumerable> void InitializeBuffersFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int NumTriangles, const TriangleEnumerable& Enumerable, const FDynamicMeshUVOverlay* UVOverlay, const FDynamicMeshNormalOverlay* NormalOverlay, const FDynamicMeshColorOverlay* ColorOverlay, TFunctionRef<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc, bool bTrackTriangles = false, bool bParallel = false)` — Initialize rendering buffers from given attribute overlays. Creates three vertices per triangle, IE no shared vertices in buffers.
- L134 _public function_ `template<typename TriangleEnumerable, typename UVOverlayListAllocator> void InitializeBuffersFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int NumTriangles, const TriangleEnumerable& Enumerable, const TArray<const FDynamicMeshUVOverlay*, UVOverlayListAllocator>& UVOverlays, const FDynamicMeshNormalOverlay* NormalOverlay, const FDynamicMeshColorOverlay* ColorOverlay, TFunctionRef<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc, bool bTrackTriangles = false, bool bParallel = false)` — Initialize rendering buffers from given attribute overlays. Creates three vertices per triangle, IE no shared vertices in buffers.
- L156 _public function_ `void UpdateSecondaryTriangleBuffer( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, bool bDuplicate)` — Filter the triangles in a FMeshRenderBufferSet into the SecondaryIndexBuffer. Requires that RenderBuffers->Triangles has been initialized. @param bDuplicate if set, then primary IndexBuffer is unmodified and SecondaryIndexBuffer contains duplicates. Otherwise triangles are sorted via predicate into either primary or secondary.
- L170 _public function_ `void RecomputeRenderBufferTriangleIndexSets( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh)` — RecomputeRenderBufferTriangleIndexSets re-sorts the existing set of triangles in a FMeshRenderBufferSet into primary and secondary index buffers. Note that UploadIndexBufferUpdate() must be called after this function!
- L184 _public function_ `template<typename TriangleEnumerable> void UpdateVertexBuffersFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int NumTriangles, const TriangleEnumerable& Enumerable, const FDynamicMeshNormalOverlay* NormalOverlay, const FDynamicMeshColorOverlay* ColorOverlay, TFunctionRef<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc, bool bUpdatePositions = true, bool bUpdateNormals = false, bool bUpdateColors = false)` — Update vertex positions/normals/colors of an existing set of render buffers. Assumes that buffers were created with unshared vertices, ie three vertices per triangle, eg by InitializeBuffersFromOverlays()
- L203 _public function_ `template<typename TriangleEnumerable, typename UVOverlayListAllocator> void UpdateVertexUVBufferFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int32 NumTriangles, const TriangleEnumerable& Enumerable, const TArray<const FDynamicMeshUVOverlay*, UVOverlayListAllocator>& UVOverlays)` — Update vertex uvs of an existing set of render buffers. Assumes that buffers were created with unshared vertices, ie three vertices per triangle, eg by InitializeBuffersFromOverlays()
- L216 _public prototype_ `virtual int32 GetNumMaterials() const;` — @return number of active materials
- L221 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 k) const;` — Safe GetMaterial function that will never return nullptr
- L226 _public function_ `void SetVerifyUsedMaterials(const bool bState)` — Set whether or not to validate mesh batch materials against the component materials.
- L237 _public prototype_ `virtual void UpdatedReferencedMaterials();` — This needs to be called if the set of active materials changes, otherwise the check in FPrimitiveSceneProxy::VerifyUsedMaterial() will fail if an override material is set, if materials change, etc, etc
- L247 _public prototype_ `static FMaterialRenderProxy* GetEngineVertexColorMaterialProxy(FMeshElementCollector& Collector, const FEngineShowFlags& EngineShowFlags, bool bProxyIsSelected, bool bIsHovered);` — If EngineShowFlags request vertex color rendering, returns the appropriate vertex color override material's render proxy.  Otherwise returns nullptr.
- L252 _public prototype_ `virtual void GetDynamicMeshElements( const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;` — Render set of active RenderBuffers returned by GetActiveRenderBufferSets
- L262 _protected prototype_ `virtual void GetCollisionDynamicMeshElements(TArray<FMeshRenderBufferSet*>& Buffers, const FEngineShowFlags& EngineShowFlags, bool bDrawCollisionView, bool bDrawSimpleCollision, bool bDrawComplexCollision, bool bProxyIsSelected, const TArray<const FSceneView*>& Views, uint32 VisibilityMap, FMeshElementCollector& Collector) const;` — Helper called by GetDynamicMeshElements to process collision debug drawing
- L269 _public prototype_ `virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override;`
- L272 _public prototype_ `virtual bool AllowStaticDrawPath(const FSceneView* View) const;` — Whether to allow use of the static draw path. If false, the dynamic draw path will be used instead.
- L277 _public prototype_ `virtual void DrawBatch(FMeshElementCollector& Collector, const FMeshRenderBufferSet& RenderBuffers, const FDynamicMeshIndexBuffer32& IndexBuffer, FMaterialRenderProxy* UseMaterial, bool bWireframe, ESceneDepthPriorityGroup DepthPriority, int ViewIndex, FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer) const;` — Draw a single-frame FMeshBatch for a FMeshRenderBufferSet
- L288 _public prototype_ `virtual HHitProxy* CreateHitProxies(UPrimitiveComponent* Component, TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L289 _public prototype_ `virtual HHitProxy* CreateHitProxies(IPrimitiveComponent* ComponentInterface, TArray<TRefCountPtr<HHitProxy> >& OutHitProxies) override;`
- L298 _public prototype_ `virtual bool IsRayTracingRelevant() const override;`
- L299 _public prototype_ `virtual bool HasRayTracingRepresentation() const override;`
- L301 _public prototype_ `virtual void GetDynamicRayTracingInstances(FRayTracingInstanceCollector& Collector) override;`
- L307 _public prototype_ `virtual void DrawRayTracingBatch( FRayTracingInstanceCollector& Collector, const FMeshRenderBufferSet& RenderBuffers, const FDynamicMeshIndexBuffer32& IndexBuffer, FRayTracingGeometry& RayTracingGeometry, FMaterialRenderProxy* UseMaterialProxy, ESceneDepthPriorityGroup DepthPriority, FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer) const;` — Draw a single-frame raytracing FMeshBatch for a FMeshRenderBufferSet
- L326 _public prototype_ `virtual const FCardRepresentationData* GetMeshCardRepresentation() const override;`
- L329 _protected member_ `TPimplPtr<FCardRepresentationData> MeshCards;`
- L332 _protected member_ `bool bMeshCardsValid = false;` — `UE_DEPRECATED(5.6, "Use MeshCards.IsValid() instead")`
- L335 _protected prototype_ `void UpdateLumenCardsFromBounds();` — Helper to set lumen cards
- L340 _protected member_ `TSharedPtr<FDistanceFieldVolumeData> DistanceField;` — `UE_DEPRECATED(5.6, "Distance field support is deprecated for dynamic mesh components")`
- L342 _protected member_ `bool bDistanceFieldValid = false;` — `UE_DEPRECATED(5.6, "Distance field support is deprecated for dynamic mesh components")`
- L345 _public prototype_ `static TUniquePtr<FDistanceFieldVolumeData> ComputeDistanceFieldForMesh( const FDynamicMesh3& Mesh, FProgressCancel& Progress, float DistanceFieldResolutionScale = 1.0, bool bGenerateAsIfTwoSided = false );` — `UE_DEPRECATED(5.6, "Distance field support is deprecated for dynamic mesh components")`
- L352 _public prototype_ `void SetNewDistanceField(TSharedPtr<FDistanceFieldVolumeData> NewDistanceField, bool bInInitialize);` — `UE_DEPRECATED(5.6, "Distance field support is deprecated for dynamic mesh components")`
- L356 _public prototype_ `void SetCollisionData();` — Set the collision data to use for debug drawing, or do nothing if debug drawing is not enabled
- L362 _private member_ `bool bOwnerIsNull = true;`
- L364 _private member_ `bool bHasCollisionData = false;` — Whether the collision data has been set up for rendering
- L366 _private member_ `bool bHasComplexMeshData = false;` — Whether a complex collision mesh is available
- L368 _private member_ `ECollisionTraceFlag CollisionTraceFlag;` — Collision trace flags
- L370 _private member_ `FCollisionResponseContainer CollisionResponse;` — Collision Response of this component
- L372 _private member_ `FKAggregateGeom CachedAggGeom;` — Cached AggGeom holding the collision shapes to render
- L375 _private member_ `mutable FCriticalSection CachedCollisionLock;` — Control access to collision data for debug rendering
- L379 _private prototype_ `bool IsCollisionView(const FEngineShowFlags& EngineShowFlags, bool& bDrawSimpleCollision, bool& bDrawComplexCollision) const;`

### `Source/Runtime/GeometryFramework/Public/Components/DynamicMeshComponent.h` (Public)


#### class `IRenderMeshPostProcessor`  
`class IRenderMeshPostProcessor`  
_L35-41_
- desc: Interface for a render mesh processor. Use this to process the Mesh stored in UDynamicMeshComponent before sending it off for rendering. NOTE: This is called whenever the Mesh is updated and before rendering, so performance matters.
- L38 _public prototype_ `virtual ~IRenderMeshPostProcessor() = default;`
- L40 _public prototype_ `virtual void ProcessMesh(const FDynamicMesh3& Mesh, FDynamicMesh3& OutRenderMesh) = 0;`

#### enum `EDynamicMeshComponentRenderUpdateMode`  
`enum class EDynamicMeshComponentRenderUpdateMode`  
_L46-54_
- reflection: `UENUM()`
- desc: Render data update hint
- L49 _public enumerator_ `NoUpdate = 0` — Do not update render data
- L51 _public enumerator_ `FullUpdate = 1` — Invalidate overlay of internal component, rebuilding all render data
- L53 _public enumerator_ `FastUpdate = 2` — Attempt to do partial update of render data if possible

#### struct `TAsyncComponentDataComputeQueue`  
`template<typename DataType> struct TAsyncComponentDataComputeQueue`  
_L58-155_
- L60 _public member_ `std::atomic<int> JobCounter = 0;`
- L61 _public member_ `bool bIsShuttingDown = false;`
- L63 _public function_ `~TAsyncComponentDataComputeQueue()`
- L77 _public member_ `TArray<TUniquePtr<FComputeJob>> PendingJobs;`
- L78 _public member_ `FCriticalSection PendingJobsLock;`
- L83 _public member_ `TFunction<void(TUniquePtr<DataType> NewData)> OnComputeCompleted;` — This function will be called w/ the data computed by a job when it finishes, if it is still valid Note this method will be run from a background thread, and should be thread-safe!
- L85 _public function_ `void LaunchJob(const TCHAR* DebugName, TFunction<TUniquePtr<DataType>(FProgressCancel& Progress)> JobWork)`
- L145 _public function_ `void WaitForAllJobsDuringShutdown()`

#### struct `TAsyncComponentDataComputeQueue::FComputeJob`  
`struct FComputeJob`  
_L68-75_
- L70 _public member_ `UE::Tasks::FTask Task;`
- L71 _public member_ `int JobTimestamp = 0;`
- L72 _public member_ `TUniquePtr<FProgressCancel> Progress;`
- L73 _public member_ `bool bCancelled = false;`
- L74 _public member_ `bool bHasCompleted = false;`

#### class `UDynamicMeshComponent`  
`class UDynamicMeshComponent : public UBaseDynamicMeshComponent, public IInterface_CollisionDataProvider`  
_L171-908_
- reflection: `UCLASS(hidecategories = (LOD), meta = (BlueprintSpawnableComponent), ClassGroup = Rendering, MinimalAPI)`
- inherits: `UBaseDynamicMeshComponent,IInterface_CollisionDataProvider`
- desc: UDynamicMeshComponent is a mesh component similar to UProceduralMeshComponent, except it bases the renderable geometry off an internal UDynamicMesh instance (which encapsulates a FDynamicMesh3). There is extensive support for partial updates to render buffers, customizing colors, internally decomposing the mesh into separate chunks for more efficient render updates, and support for attaching a 'Postprocessor' to generate a render mesh on-the-fly See comment sections below for details.
- L185 _public function_ `virtual FDynamicMesh3* GetMesh() override` — @return pointer to internal mesh @warning avoid usage of this function, access via GetDynamicMesh() instead
- L191 _public function_ `virtual const FDynamicMesh3* GetMesh() const override` — @return pointer to internal mesh @warning avoid usage of this function, access via GetDynamicMesh() instead
- L197 _public function_ `virtual UDynamicMesh* GetDynamicMesh() override` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return the child UDynamicMesh
- L205 _public prototype_ `void SetDynamicMesh(UDynamicMesh* NewMesh);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Replace the current UDynamicMesh with a new one, and transfer ownership of NewMesh to this Component. This can be used to (eg) assign a UDynamicMesh created with NewObject in the Transient Package to this Component. @warning If NewMesh is owned/Outer'd to another DynamicMeshComponent, a GLEO error may occur if that Component is serialized.
- L210 _public prototype_ `virtual void SetMesh(UE::Geometry::FDynamicMesh3&& MoveMesh) override;` — initialize the internal mesh from a DynamicMesh
- L215 _public prototype_ `virtual void ProcessMesh(TFunctionRef<void(const UE::Geometry::FDynamicMesh3&)> ProcessFunc) const;` — Allow external code to read the internal mesh.
- L220 _public prototype_ `virtual void EditMesh(TFunctionRef<void(UE::Geometry::FDynamicMesh3&)> EditFunc, EDynamicMeshComponentRenderUpdateMode UpdateMode = EDynamicMeshComponentRenderUpdateMode::FullUpdate, EDynamicMeshChangeType ChangeType = EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags ChangeFlags = EDynamicMeshAttributeChangeFlags::Unknown);` — Allow external code to to edit the internal mesh.
- L229 _public prototype_ `virtual void ApplyTransform(const FTransform3d& Transform, bool bInvert) override;` — Apply transform to internal mesh. In some cases this can be more efficient than a general edit. @param bInvert if true, inverse tranform is applied instead of forward transform
- L236 _public function_ `bool IsEditable() const` — If set to false, this blocks external code from being able to modify the internal mesh. It prevents modifications through methods on this UDynamicMeshComponent such as EditMesh/SetMesh, However, this cannot prevent code from modifying the underlying UDynamicMesh through direct references (ex. via GetDynamicMesh()->SetMesh).
- L237 _public function_ `void SetIsEditable(bool bInIsEditable)`
- L244 _public function_ `bool AllowsGeometrySelection() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — @return Whether geometry elements (triangles, edges, etc) of the dynamic mesh can be interactively selected.
- L251 _public function_ `void SetAllowsGeometrySelection(bool bInAllowsGeometrySelection)` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Enable/Disable interactive geometry element selection for the mesh. Useful to disable geometry selection on procedural meshes where the selection will be frequently invalidated. @param bInAllowsGeometrySelection Whether geometry elements (triangles, edges, etc) of the dynamic mesh will be interactively selectable.
- L259 _protected member_ `TObjectPtr<UDynamicMesh> MeshObject;` — `UPROPERTY(Instanced)` — Internal FDynamicMesh is stored inside a UDynamicMesh container, which allows it to be used from BP, shared with other UObjects, and so on
- L275 _public prototype_ `virtual void NotifyMeshUpdated() override;` — Call this if you update the mesh via GetMesh(). This will destroy the existing RenderProxy and create a new one. @todo should provide a function that calls a lambda to modify the mesh, and only return const mesh pointer
- L281 _public prototype_ `void FastNotifyColorsUpdated();` — Call this instead of NotifyMeshUpdated() if you have only updated the vertex colors (or triangle color function). This function will update the existing RenderProxy buffers if possible
- L287 _public prototype_ `void FastNotifyPositionsUpdated(bool bNormals = false, bool bColors = false, bool bUVs = false);` — Call this instead of NotifyMeshUpdated() if you have only updated the vertex positions (and possibly some attributes). This function will update the existing RenderProxy buffers if possible
- L293 _public prototype_ `void FastNotifyVertexAttributesUpdated(bool bNormals, bool bColors, bool bUVs);` — Call this instead of NotifyMeshUpdated() if you have only updated the vertex attributes (but not positions). This function will update the existing RenderProxy buffers if possible, rather than create new ones.
- L299 _public prototype_ `void FastNotifyVertexAttributesUpdated(EMeshRenderAttributeFlags UpdatedAttributes);` — Call this instead of NotifyMeshUpdated() if you have only updated the vertex positions/attributes This function will update the existing RenderProxy buffers if possible, rather than create new ones.
- L305 _public prototype_ `void FastNotifyUVsUpdated();` — Call this instead of NotifyMeshUpdated() if you have only updated the vertex uvs. This function will update the existing RenderProxy buffers if possible
- L311 _public prototype_ `void FastNotifySecondaryTrianglesChanged();` — Call this instead of NotifyMeshUpdated() if you have only updated secondary triangle sorting. This function will update the existing buffers if possible, without rebuilding entire RenderProxy.
- L317 _public prototype_ `void FastNotifyTriangleVerticesUpdated(const TArray<int32>& Triangles, EMeshRenderAttributeFlags UpdatedAttributes);` — This function updates vertex positions/attributes of existing SceneProxy render buffers if possible, for the given triangles. If a FMeshRenderDecomposition has not been explicitly set, call is forwarded to FastNotifyVertexAttributesUpdated()
- L323 _public prototype_ `void FastNotifyTriangleVerticesUpdated(const TSet<int32>& Triangles, EMeshRenderAttributeFlags UpdatedAttributes);` — This function updates vertex positions/attributes of existing SceneProxy render buffers if possible, for the given triangles. If a FMeshRenderDecomposition has not been explicitly set, call is forwarded to FastNotifyVertexAttributesUpdated()
- L329 _public prototype_ `void FastNotifyVerticesUpdated(const TArray<int32>& Vertices, EMeshRenderAttributeFlags UpdatedAttributes);` — This function updates vertex positions/attributes of existing SceneProxy render buffers if possible, for the given vertices. If a FMeshRenderDecomposition has not been explicitly set, call is forwarded to FastNotifyVertexAttributesUpdated()
- L333 _private prototype_ `void FastNotifyDecompositionSetsUpdated(TFunctionRef<TArray<int32>(void)> GetUpdatedDecompositionIndices, EMeshRenderAttributeFlags UpdatedAttributes);` — Helper to implement common functionality of above FastNotify-region-Updated methods
- L342 _public prototype_ `TFuture<bool> FastNotifyTriangleVerticesUpdated_TryPrecompute(const TArray<int32>& Triangles, TArray<int32>& UpdateSetsOut, UE::Geometry::FAxisAlignedBox3d& BoundsOut);` — If a Decomposition is set on this Component, and everything is currently valid (proxy/etc), precompute the set of buffers that will be modified, as well as the bounds of the modified region. These are both computed in parallel. Use FastNotifyTriangleVerticesUpdated_ApplyPrecompute() with the returned future to apply this precomputation. @return a future that will (eventually) return true if the precompute is OK, and (immediately) false if it is not
- L351 _public prototype_ `void FastNotifyTriangleVerticesUpdated_ApplyPrecompute(const TArray<int32>& Triangles, EMeshRenderAttributeFlags UpdatedAttributes, TFuture<bool>& Precompute, const TArray<int32>& UpdateSets, const UE::Geometry::FAxisAlignedBox3d& UpdateSetBounds);` — This function updates vertex positions/attributes of existing SceneProxy render buffers if possible, for the given triangles. The assumption is that FastNotifyTriangleVerticesUpdated_TryPrecompute() was used to get the Precompute future, this function will Wait() until it is done and then use the UpdateSets and UpdateSetBounds that were computed (must be the same variables passed to FastNotifyTriangleVerticesUpdated_TryPrecompute). If the Precompute future returns false, then we forward the call to FastNotifyTriangleVerticesUpdated(), which will do more work.
- L369 _public prototype_ `virtual void NotifyMeshModified();` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering", DisplayName = "Notify Mesh Updated")` — Notify the Component that it's DynamicMesh has been modified externally. This will result in all Rendering Data for the Component being rebuilt on the next frame (internally the Scene Proxy is fully destroyed and rebuilt). You must use this function if the mesh triangulation has been modified, or if polygroups or material assignments have been changed, or if Normal/UV/Color topology has changed (ie new split-vertices have been introduced). If only vertex attribute values (position, normals, UVs, colors) have been modified, then Notify Vertex Attributes Updated can be used to do a faster update.
- L380 _public prototype_ `virtual void NotifyMeshVertexAttributesModified( bool bPositions = true, bool bNormals = true, bool bUVs = true, bool bColors = true);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component|Rendering", DisplayName = "Notify Vertex Attributes Updated")` — Notify the Component that vertex attribute values of it's DynamicMesh have been modified externally. This will result in Rendering vertex buffers being updated. This update path is more efficient than doing a full Notify Mesh Updated. @warning it is invalid to call this function if (1) the mesh triangulation has also been changed, (2) triangle MaterialIDs have been changed, or (3) any attribute overlay (normal, color, UV) topology has been modified, ie split-vertices have been added/removed. Behavior of this function is undefined in these cases and may crash. If you are unsure, use Notify Mesh Updated.
- L396 _public prototype_ `virtual void ApplyChange(const FMeshVertexChange* Change, bool bRevert) override;` — Apply a vertex deformation change to the mesh
- L401 _public prototype_ `virtual void ApplyChange(const FMeshChange* Change, bool bRevert) override;` — Apply a general mesh change to the mesh
- L406 _public prototype_ `virtual void ApplyChange(const FMeshReplacementChange* Change, bool bRevert) override;` — Apply a mesh replacement change to mesh
- L411 _public member_ `FSimpleMulticastDelegate OnMeshChanged;` — This delegate fires when the mesh has been changed
- L416 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FMeshVerticesModified, UDynamicMeshComponent*, const FMeshVertexChange*, bool);` — This delegate fires when the mesh vertices have been changed via an FMeshVertexChange
- L417 _public member_ `FMeshVerticesModified OnMeshVerticesChanged;`
- L423 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FMeshRegionModified, UDynamicMeshComponent*, const FMeshRegionChangeBase*, bool);` — This delegate fires when the mesh has been changed via an FMeshRegionChange-derived change -- FMeshChange, FMeshVertexChange, or FMeshReplacementChange Note that in the case of an FMeshVertexChange, the OnMeshVerticesChanged delegate will also fire
- L424 _public member_ `FMeshRegionModified OnMeshRegionChanged;`
- L432 _public prototype_ `void SetInvalidateProxyOnChangeEnabled(bool bEnabled);` — When a FMeshChange or FMeshVertexChange is applied, by default we currently fully invalidate the render proxy. However in certain realtime situations (eg like Sculpting tools) it can be critical to undo/redo performance to do more optimized render data updates (eg using one of the FastXYZ functions above). To allow for that, the full proxy invalidation on change can be (temporarily!) disabled using this function.
- L435 _public function_ `bool GetInvalidateProxyOnChangeEnabled() const` — @return true if InvalidateProxyOnChange is enabled (default)
- L439 _protected member_ `bool bInvalidateProxyOnChange = true;` — If false, we don't completely invalidate the RenderProxy when ApplyChange() is called (assumption is it will be handled elsewhere)
- L442 _protected member_ `FDelegateHandle MeshObjectChangedHandle;` — Handle for OnMeshObjectChanged which is registered with MeshObject::OnMeshChanged delegate
- L445 _protected prototype_ `void OnMeshObjectChanged(UDynamicMesh* ChangedMeshObject, FDynamicMeshChangeInfo ChangeInfo);` — Called whenever internal MeshObject is modified, fires OnMeshChanged and OnMeshVerticesChanged above
- L451 _protected member_ `bool bIsEditable = true;` — If set to false, this blocks external code from being able to modify the internal mesh. It prevents modifications through methods on this UDynamicMeshComponent such as EditMesh/SetMesh, However, this cannot prevent code from modifying the underlying UDynamicMesh through direct references (ex. via GetDynamicMesh()->SetMesh).
- L458 _private member_ `bool bAllowsGeometrySelection = true;` — `UPROPERTY()` — If set to false, the geometry element selection UI will not be used for this mesh component. This is useful for procedural meshes where selection would be frequently invalidated.
- L471 _public prototype_ `virtual void SetTriangleColorFunction(TUniqueFunction<FColor(const FDynamicMesh3*, int)> TriangleColorFuncIn, EDynamicMeshComponentRenderUpdateMode UpdateMode = EDynamicMeshComponentRenderUpdateMode::FastUpdate);` — Set an active triangle color function if one exists, and update the mesh
- L475 _public prototype_ `virtual void ClearTriangleColorFunction(EDynamicMeshComponentRenderUpdateMode UpdateMode = EDynamicMeshComponentRenderUpdateMode::FastUpdate);` — Clear an active triangle color function if one exists, and update the mesh
- L478 _public prototype_ `virtual bool HasTriangleColorFunction();` — @return true if a triangle color function is configured
- L482 _protected member_ `TUniqueFunction<FColor(const FDynamicMesh3*, int)> TriangleColorFunc = nullptr;` — If this function is set, we will use these colors instead of vertex colors
- L485 _protected prototype_ `FColor GetTriangleColor(const FDynamicMesh3* Mesh, int TriangleID);` — This function is passed via lambda to the RenderProxy to be able to access TriangleColorFunc
- L488 _protected prototype_ `FColor GetGroupColor(const FDynamicMesh3* Mesh, int TriangleID) const;` — This function is passed via lambda to the RenderProxy when BaseDynamicMeshComponent::ColorMode == Polygroups
- L499 _public prototype_ `virtual void SetVertexColorRemappingFunction(TUniqueFunction<void(FVector4f&)> ColorMapFuncIn, EDynamicMeshComponentRenderUpdateMode UpdateMode = EDynamicMeshComponentRenderUpdateMode::FastUpdate);` — Set an active VertexColor Remapping function if one exists, and update the mesh
- L503 _public prototype_ `virtual void ClearVertexColorRemappingFunction(EDynamicMeshComponentRenderUpdateMode UpdateMode = EDynamicMeshComponentRenderUpdateMode::FastUpdate);` — Clear an active VertexColor Remapping function if one exists, and update the mesh
- L506 _public prototype_ `virtual bool HasVertexColorRemappingFunction();` — @return true if a VertexColor Remapping function is configured
- L510 _protected member_ `TUniqueFunction<void(FVector4f&)> VertexColorMappingFunc = nullptr;` — If this function is set, DynamicMesh Attribute Color Overlay colors will be passed through this function before sending to render buffers
- L513 _protected prototype_ `void RemapVertexColor(FVector4f& VertexColorInOut);` — This function is passed via lambda to the RenderProxy to be able to access VertexColorMappingFunc
- L530 _public prototype_ `virtual void EnableSecondaryTriangleBuffers(TUniqueFunction<bool(const FDynamicMesh3*, int32)> SecondaryTriFilterFunc);` — If Secondary triangle buffers are enabled, then we will filter triangles that pass the given predicate function into a second index buffer. These triangles will be drawn with the Secondary render material that is set in the BaseDynamicMeshComponent. Calling this function invalidates the SceneProxy.
- L535 _public prototype_ `virtual void DisableSecondaryTriangleBuffers();` — Disable secondary triangle buffers. This invalidates the SceneProxy.
- L538 _protected member_ `TUniqueFunction<bool(const FDynamicMesh3*, int32)> SecondaryTriFilterFunc = nullptr;`
- L555 _public prototype_ `virtual void SetExternalDecomposition(TUniquePtr<FMeshRenderDecomposition> Decomposition);` — Configure a decomposition of the mesh, which will result in separate render buffers for each decomposition triangle group. Invalidates existing SceneProxy.
- L558 _protected member_ `TUniquePtr<FMeshRenderDecomposition> Decomposition;`
- L573 _public prototype_ `virtual void SetRenderMeshPostProcessor(TUniquePtr<IRenderMeshPostProcessor> Processor);` — Add a render mesh processor, to be called before the mesh is sent for rendering.
- L578 _public prototype_ `virtual FDynamicMesh3* GetRenderMesh();` — The SceneProxy should call these functions to get the post-processed RenderMesh. (See IRenderMeshPostProcessor.)
- L583 _public prototype_ `virtual const FDynamicMesh3* GetRenderMesh() const;` — The SceneProxy should call these functions to get the post-processed RenderMesh. (See IRenderMeshPostProcessor.)
- L586 _protected member_ `TUniquePtr<IRenderMeshPostProcessor> RenderMeshPostProcessor;`
- L587 _protected member_ `TUniquePtr<FDynamicMesh3> RenderMesh;`
- L598 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FComponentChildrenChangedDelegate, USceneComponent*, bool);`
- L604 _public member_ `FComponentChildrenChangedDelegate OnChildAttachmentModified;` — The OnChildAttached() and OnChildDetached() implementations (from USceneComponent API) broadcast this delegate. This allows Actors that have UDynamicMeshComponent's to respond to changes in their Component hierarchy.
- L619 _public prototype_ `void ConfigureMaterialSet(const TArray<UMaterialInterface*>& NewMaterialSet, bool bDeleteExtraSlots = true);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Set new list of Materials for the Mesh. Dynamic Mesh Component does not have Slot Names, so the size of the Material Set should be the same as the number of different Material IDs on the mesh MaterialID attribute @param bDeleteExtraSlots if true, extra Material Slots beyond max NewMaterialSet.Num() are removed
- L629 _public prototype_ `bool ValidateMaterialSlots(bool bCreateIfMissing = true, bool bDeleteExtraSlots = true);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Compute the maximum MaterialID on the DynamicMesh, and ensure that Material Slots match. Pass both arguments as false to just do a check. @param bCreateIfMissing if true, add extra (empty) Material Slots to match max MaterialID @param bDeleteExtraSlots if true, extra Material Slots beyond max MaterialID are removed @return true if at the end of this function, Material Slot Count == Max MaterialID
- L645 _private member_ `static constexpr EDynamicMeshComponentTangentsMode UseDefaultTangentsType = EDynamicMeshComponentTangentsMode::ExternallyProvided;` — Default what the 'Default' tangent type should map to
- L649 _public prototype_ `void SetTangentsType(EDynamicMeshComponentTangentsMode NewTangentsType);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")`
- L652 _public function_ `EDynamicMeshComponentTangentsMode GetTangentsType() const` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")`
- L660 _private function_ `EDynamicMeshComponentTangentsMode GetTangentsTypePure() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintInternalUseOnly, Category = "Dynamic Mesh Component")` — pure version of GetTangentsType, so it can be used as a getter below (getters must be BlueprintPure)
- L668 _public prototype_ `virtual void InvalidateAutoCalculatedTangents();` — This function marks the auto tangents as dirty, they will be recomputed before they are used again
- L671 _public prototype_ `const UE::Geometry::FMeshTangentsf* GetAutoCalculatedTangents();` — @return AutoCalculated Tangent Set, which may require that they be recomputed, or nullptr if not enabled/available
- L676 _protected member_ `EDynamicMeshComponentTangentsMode TangentsType = EDynamicMeshComponentTangentsMode::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter=SetTangentsType, BlueprintGetter=GetTangentsTypePure, Category = "Dynamic Mesh Component|Rendering")` — Tangent source defines whether we use the provided tangents on the Dynamic Mesh, autogenerate tangents, or do not use tangents
- L679 _protected member_ `bool bAutoCalculatedTangentsValid = false;` — true if AutoCalculatedTangents has been computed for current mesh
- L682 _protected member_ `UE::Geometry::FMeshTangentsf AutoCalculatedTangents;` — Set of per-triangle-vertex tangents computed for the current mesh. Only valid if bAutoCalculatedTangentsValid == true
- L684 _protected prototype_ `void UpdateAutoCalculatedTangents();`
- L693 _protected member_ `FCriticalSection DistanceFieldLock;` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")`
- L695 _protected member_ `TSharedPtr<FDistanceFieldVolumeData> CurrentDistanceField;` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")`
- L697 _protected function_ `virtual void UpdateDistanceField()` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")`
- L699 _protected member_ `TAsyncComponentDataComputeQueue<FDistanceFieldVolumeData> DistanceFieldComputeQueue;` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")`
- L701 _protected function_ `virtual void OnNewDistanceFieldData_Async(TUniquePtr<FDistanceFieldVolumeData> NewData)` — `UE_DEPRECATED(5.6, "Dynamic Mesh distance field support has been deprecated")`
- L714 _public prototype_ `void EnableComplexAsSimpleCollision();` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — calls SetComplexAsSimpleCollisionEnabled(true, true)
- L722 _public prototype_ `void SetComplexAsSimpleCollisionEnabled(bool bEnabled, bool bImmediateUpdate = true);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — If bEnabled=true, sets bEnableComplexCollision=true and CollisionType=CTF_UseComplexAsSimple If bEnabled=true, sets bEnableComplexCollision=false and CollisionType=CTF_UseDefault @param bImmediateUpdate if true, UpdateCollision(true) is called
- L729 _public prototype_ `void SetDeferredCollisionUpdatesEnabled(bool bEnabled, bool bImmediateUpdate = true);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Set value of bDeferCollisionUpdates, when enabled, collision is not automatically recomputed each time the mesh changes. @param bImmediateUpdate if true, UpdateCollision(true) is called if bEnabled=false, ie to force a collision rebuild
- L732 _public prototype_ `virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;`
- L733 _public prototype_ `virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const override;`
- L734 _public prototype_ `virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;`
- L735 _public prototype_ `virtual bool WantsNegXTriMesh() override;`
- L738 _public function_ `virtual const UBodySetup* GetBodySetup() const` — @return current BodySetup for this Component, or nullptr if it does not exist
- L740 _public prototype_ `virtual UBodySetup* GetBodySetup() override;` — @return BodySetup for this Component. A new BodySetup will be created if one does not exist.
- L747 _public prototype_ `virtual void UpdateCollision(bool bOnlyIfPending = true);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh Component")` — Force an update of the Collision/Physics data for this Component. @param bOnlyIfPending only update if a collision update is pending, ie the underlying DynamicMesh changed and bDeferCollisionUpdates is enabled
- L759 _public prototype_ `virtual void SetSimpleCollisionShapes(const struct FKAggregateGeom& AggGeom, bool bUpdateCollision);` — Update the simple collision shapes associated with this mesh component @param AggGeom				New simple collision shapes to be used @param bUpdateCollision		Whether to automatically call UpdateCollision() -- if false, manually call it to register the change with the physics system
- L761 _public function_ `const FKAggregateGeom& GetSimpleCollisionShapes() const`
- L770 _public prototype_ `virtual void ClearSimpleCollisionShapes(bool bUpdateCollision);` — Clear the simple collision shapes associated with this mesh component @param bUpdateCollision		Whether to automatically call UpdateCollision() -- if false, manually call it to register the change with the physics system
- L777 _public member_ `bool bUseAsyncCooking = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dynamic Mesh Component|Collision")` — Controls whether the physics cooking should be done off the game thread. This should be used when collision geometry doesn't have to be immediately up to date (For example streaming in far away objects)
- L784 _public member_ `bool bEnableComplexCollision = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Collision")` — If true, current mesh will be used as Complex Collision source mesh. This is independent of the CollisionType setting, ie, even if Complex collision is enabled, if this is false, then the Complex Collision mesh will be empty
- L788 _public member_ `bool bDeferCollisionUpdates = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Collision")` — If true, updates to the mesh will not result in immediate collision regeneration. Useful when the mesh will be modified multiple times before collision is needed.
- L792 _public member_ `bool bDisableMeshUVHitResults = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic Mesh Component|Collision")` — If true, UV hit results will not be enabled for this mesh's complex collision even if they are enabled for the project settings generally. This can make the complex build faster and take less memory.
- L800 _public prototype_ `void SetTransientDeferCollisionUpdates(bool bEnabled);` — The bDeferCollisionUpdates property is a serialized Component setting that controls when collision is regenerated. However, in some cases where a UDynamicMesh is being programmatically edited (eg like a live deformation/etc), we want to defer collision updates during the user interaction, but not change the serialized property. In this case a non-serialized version of the flag can be *temporarily* set via this function in C++.
- L804 _protected member_ `TObjectPtr<UBodySetup> MeshBodySetup;` — `UPROPERTY(Instanced)`
- L806 _protected prototype_ `virtual void InvalidatePhysicsData();`
- L807 _protected prototype_ `virtual void RebuildPhysicsData();`
- L809 _protected member_ `bool bTransientDeferCollisionUpdates = false;`
- L810 _protected member_ `bool bCollisionUpdatePending = false;`
- L819 _protected member_ `UE::Geometry::FAxisAlignedBox3d LocalBounds;` — Current local-space bounding box of Mesh
- L822 _protected prototype_ `void UpdateLocalBounds();` — Recompute LocalBounds from the current Mesh
- L830 _protected member_ `struct FKAggregateGeom AggGeom;` — `UPROPERTY(EditAnywhere, Category = BodySetup, meta = (DisplayName = "Primitives", NoResetToDefault))` — Simplified collision representation for the mesh component
- L834 _protected member_ `TArray<TObjectPtr<UBodySetup>> AsyncBodySetupQueue;` — `UPROPERTY(transient)` — Queue for async body setups that are being cooked
- L837 _protected prototype_ `virtual void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);` — Once async physics cook is done, create needed state
- L839 _protected prototype_ `virtual UBodySetup* CreateBodySetupHelper();`
- L842 _protected prototype_ `virtual void SetBodySetup(UBodySetup* NewSetup);` — @return Set new BodySetup for this Component.
- L848 _protected prototype_ `virtual void NotifyMaterialSetUpdated();` — This is called to tell our RenderProxy about modifications to the material set. We need to pass this on for things like material validation in the Editor.
- L856 _protected member_ `bool bProxyValid = false;` — If the render proxy is invalidated (eg by MarkRenderStateDirty()), it will be destroyed at the end of the frame, but the base SceneProxy pointer is not nulled out immediately. As a result if we call various partial-update functions after invalidating the proxy, they may be operating on an invalid proxy. So we have to keep track of proxy-valid state ourselves.
- L865 _protected member_ `bool bProxyVerifyUsedMaterials = true;` — If true, the render proxy will verify that the mesh batch materials match the contents from the component GetUsedMaterials(). Used material verification is prone to races when changing materials on this component in quick succession (for example, SetOverrideRenderMaterial). This parameter is provided to allow clients to opt out of used material verification for these use cases.
- L867 _protected function_ `virtual FBaseDynamicMeshSceneProxy* GetBaseSceneProxy() override`
- L872 _protected prototype_ `FDynamicMeshSceneProxy* GetCurrentSceneProxy();` — @return current render proxy, if valid, otherwise nullptr
- L878 _protected prototype_ `void ResetProxy();` — Fully invalidate all rendering data for this Component. Current Proxy will be discarded, Bounds and possibly Tangents recomputed, etc
- L881 _protected prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L884 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L885 _protected prototype_ `virtual void OnChildAttached(USceneComponent* ChildComponent) override;`
- L886 _protected prototype_ `virtual void OnChildDetached(USceneComponent* ChildComponent) override;`
- L889 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L890 _protected prototype_ `virtual void PostLoad() override;` — called after load
- L891 _protected prototype_ `virtual void PostEditImport() override;` — called after duplicate/copy
- L892 _protected prototype_ `virtual void BeginDestroy() override;`
- L894 _protected prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L899 _public prototype_ `void SetSceneProxyVerifyUsedMaterials(bool bState);` — Set whether or not to validate mesh batch materials against the component materials.
- L904 _private prototype_ `void InternalOnMeshUpdated();` — Internal helper to be called when mesh data is updated
- L906 _private prototype_ `void BroadcastMeshPropertyChangeEvent();`

#### Free symbols / members of external scopes

- L117 _function_ `NewJob->Progress->CancelF = [this, JobPtr]()` (scope `TAsyncComponentDataComputeQueue::LaunchJob`)
- L122 _function_ `NewJob->Task = UE::Tasks::Launch(DebugName, [this, JobWork, JobPtr]() {` (scope `TAsyncComponentDataComputeQueue::LaunchJob`) — launch it
- L416 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FMeshVerticesModified, UDynamicMeshComponent*, const FMeshVertexChange*, bool);` — This delegate fires when the mesh vertices have been changed via an FMeshVertexChange
- L423 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FMeshRegionModified, UDynamicMeshComponent*, const FMeshRegionChangeBase*, bool);` — This delegate fires when the mesh has been changed via an FMeshRegionChange-derived change -- FMeshChange, FMeshVertexChange, or FMeshReplacementChange Note that in the case of an FMeshVertexChange, the OnMeshVerticesChanged delegate will also fire
- L598 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FComponentChildrenChangedDelegate, USceneComponent*, bool);`

### `Source/Runtime/GeometryFramework/Public/Components/MeshRenderBufferSet.h` (Public)


#### class `FMeshRenderBufferSet`  
`class FMeshRenderBufferSet`  
_L38-287_
- desc: FMeshRenderBufferSet stores a set of RenderBuffers for a mesh
- L42 _public member_ `int TriangleCount = 0;` — Number of triangles in this renderbuffer set. Note that triangles may be split between IndexBuffer and SecondaryIndexBuffer.
- L45 _public member_ `FStaticMeshVertexBuffer StaticMeshVertexBuffer;` — The buffer containing vertex data.
- L47 _public member_ `FPositionVertexBuffer PositionVertexBuffer;` — The buffer containing the position vertex data.
- L49 _public member_ `FColorVertexBuffer ColorVertexBuffer;` — The buffer containing the vertex color data.
- L52 _public member_ `FDynamicMeshIndexBuffer32 IndexBuffer;` — triangle indices
- L55 _public member_ `FLocalVertexFactory VertexFactory;` — vertex factory
- L58 _public member_ `UMaterialInterface* Material = nullptr;` — Material to draw this mesh with
- L64 _public member_ `TOptional<TArray<int>> Triangles;` — Optional list of triangles stored in this buffer. Storing this allows us to rebuild the buffers if vertex data changes.
- L69 _public member_ `bool bEnableSecondaryIndexBuffer = false;` — If secondary index buffer is enabled, we populate this index buffer with additional triangles indexing into the same vertex buffers
- L74 _public member_ `FDynamicMeshIndexBuffer32 SecondaryIndexBuffer;` — partition or subset of IndexBuffer that indexes into same vertex buffers
- L79 _public member_ `bool bEnableRaytracing = false;` — configure whether raytracing should be enabled for this RenderBufferSet
- L85 _public member_ `FRayTracingGeometry PrimaryRayTracingGeometry;` — Raytracing buffers
- L86 _public member_ `FRayTracingGeometry SecondaryRayTracingGeometry;`
- L87 _public member_ `bool bIsRayTracingDataValid = false;`
- L94 _public member_ `FCriticalSection BuffersLock;` — In situations where we want to *update* the existing Vertex or Index buffers, we need to synchronize access between the Game and Render threads. We use this lock to do that.
- L97 _public function_ `FMeshRenderBufferSet(ERHIFeatureLevel::Type FeatureLevelType) : VertexFactory(FeatureLevelType, "FMeshRenderBufferSet")`
- L109 _public function_ `virtual ~FMeshRenderBufferSet()`
- L141 _public prototype_ `void Upload();` — Upload initialized mesh buffers. @warning This can only be called on the Rendering Thread.
- L150 _public function_ `void UploadIndexBufferUpdate()` — Fast path to only update the primary and secondary index buffers. This can be used when (eg) the secondary index buffer is being used to highlight/hide a subset of triangles. @warning This can only be called on the Rendering Thread.
- L174 _public prototype_ `void UploadVertexUpdate(bool bPositions, bool bMeshAttribs, bool bColors);` — Fast path to only update vertex buffers. This path rebuilds all the resources and reconfigures the vertex factory, so the counts/etc could be modified. @warning This can only be called on the Rendering Thread.
- L183 _public prototype_ `void TransferVertexUpdateToGPU(FRHICommandListBase& RHICmdList, bool bPositions, bool bNormals, bool bTexCoords, bool bColors);` — Fast path to update various vertex buffers. This path does not support changing the size/counts of any of the sub-buffers, a direct memcopy from the CPU-side buffer to the RHI buffer is used. @warning This can only be called on the Rendering Thread.
- L186 _public function_ `void InvalidateRayTracingData()`
- L196 _public function_ `void ValidateRayTracingData()` — Verify that valid raytracing data is available. This will cause a rebuild of the raytracing data if any of our buffers have been modified. Currently this is called by GetDynamicRayTracingInstances to ensure the RT data is available when needed.
- L212 _protected function_ `void UpdateRaytracingGeometryIfEnabled()` — rebuild raytracing data for current buffers
- L256 _protected function_ `void InitOrUpdateResource(FRHICommandListBase& RHICmdList, FRenderResource* Resource)` — Initializes a render resource, or update it if already initialized. @warning This function can only be called on the Render Thread
- L275 _public function_ `static void DestroyRenderBufferSet(FMeshRenderBufferSet* BufferSet)` — Enqueue a command on the Render Thread to destroy the passed in buffer set. At this point the buffer set should be considered invalid.

#### struct `FMeshRenderBufferSetConversionUtil`  
`struct FMeshRenderBufferSetConversionUtil`  
_L297-471_
- desc: Parameters and accompanying functions used to build and update FMeshRenderBuffers from a dynamic mesh. For usage, see FBaseDynamicMeshSceneProxy or the simple converter below FDynamicMeshComponentToMeshRenderBufferSet Note: This is low-level and methods assume, but do not check, all input data is consistent (e.g. that all overlays, the triangle count and enumerator are all consistent with the provided mesh. )
- L303 _public member_ `FColor ConstantVertexColor = FColor::White;` — Constant color assigned to vertices if no other vertex color is specified
- L308 _public member_ `bool bIgnoreVertexColors = false;` — If true, vertex colors on the FDynamicMesh will be ignored
- L313 _public member_ `bool bUsePerTriangleColor = false;` — If true, a per-triangle color is used to set vertex colors
- L318 _public member_ `TFunction<FColor(const FDynamicMesh3*, int)> PerTriangleColorFunc = nullptr;` — Per-triangle color function. Only called if bUsePerTriangleColor=true
- L323 _public member_ `bool bApplyVertexColorRemapping = false;` — If true, VertexColorRemappingFunc is called on Vertex Colors provided from Mesh to remap them to a different color
- L328 _public member_ `TUniqueFunction<void(FVector4f&)> VertexColorRemappingFunc = nullptr;` — Vertex color remapping function. Only called if bApplyVertexColorRemapping == true, for mesh vertex colors
- L334 _public member_ `EDynamicMeshVertexColorTransformMode ColorSpaceTransformMode = EDynamicMeshVertexColorTransformMode::NoTransform;` — Color Space Transform/Conversion applied to Vertex Colors provided from Mesh Color Overlay Attribute Color Space Conversion is applied after any Vertex Color Remapping.
- L339 _public member_ `bool bUsePerTriangleNormals = false;` — If true, a facet normals are used instead of mesh normals
- L344 _public member_ `bool bUseSecondaryTriBuffers = false;` — If true, populate secondary buffers using SecondaryTriFilterFunc
- L349 _public member_ `TUniqueFunction<bool(const FDynamicMesh3*, int32)> SecondaryTriFilterFunc = nullptr;` — Filter predicate for secondary triangle index buffer. Only called if bUseSecondaryTriBuffers=true
- L357 _public function_ `template<typename TriangleEnumerable> void InitializeBuffersFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int NumTriangles, const TriangleEnumerable& Enumerable, const FDynamicMeshUVOverlay* UVOverlay, const FDynamicMeshNormalOverlay* NormalOverlay, const FDynamicMeshColorOverlay* ColorOverlay, TFunctionRef<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc, bool bTrackTriangles = false, bool bParallel = false)` — Initialize rendering buffers from given attribute overlays. Creates three vertices per triangle, IE no shared vertices in buffers.
- L380 _public prototype_ `template<typename TriangleEnumerable, typename UVOverlayListAllocator> void InitializeBuffersFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int NumTriangles, const TriangleEnumerable& Enumerable, const TArray<const FDynamicMeshUVOverlay*, UVOverlayListAllocator>& UVOverlays, const FDynamicMeshNormalOverlay* NormalOverlay, const FDynamicMeshColorOverlay* ColorOverlay, TFunctionRef<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc, bool bTrackTriangles = false, bool bParallel = false);` — Initialize rendering buffers from given attribute overlays. Creates three vertices per triangle, IE no shared vertices in buffers.
- L398 _public prototype_ `void UpdateSecondaryTriangleBuffer( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, bool bDuplicate);` — Filter the triangles in a FMeshRenderBufferSet into the SecondaryIndexBuffer. Requires that RenderBuffers->Triangles has been initialized. @param bDuplicate if set, then primary IndexBuffer is unmodified and SecondaryIndexBuffer contains duplicates. Otherwise triangles are sorted via predicate into either primary or secondary.
- L408 _public prototype_ `void RecomputeRenderBufferTriangleIndexSets( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh);` — RecomputeRenderBufferTriangleIndexSets re-sorts the existing set of triangles in a FMeshRenderBufferSet into primary and secondary index buffers. Note that UploadIndexBufferUpdate() must be called after this function!
- L417 _public prototype_ `template<typename TriangleEnumerable> void UpdateVertexBuffersFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int NumTriangles, const TriangleEnumerable& Enumerable, const FDynamicMeshNormalOverlay* NormalOverlay, const FDynamicMeshColorOverlay* ColorOverlay, TFunctionRef<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc, bool bUpdatePositions = true, bool bUpdateNormals = false, bool bUpdateColors = false);` — Update vertex positions/normals/colors of an existing set of render buffers. Assumes that buffers were created with unshared vertices, ie three vertices per triangle, eg by InitializeBuffersFromOverlays()
- L433 _public prototype_ `template<typename TriangleEnumerable, typename UVOverlayListAllocator> void UpdateVertexUVBufferFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int32 NumTriangles, const TriangleEnumerable& Enumerable, const TArray<const FDynamicMeshUVOverlay*, UVOverlayListAllocator>& UVOverlays);` — Update vertex uvs of an existing set of render buffers. Assumes that buffers were created with unshared vertices, ie three vertices per triangle, eg by InitializeBuffersFromOverlays()
- L442 _public function_ `FColor GetOverlayColorAsFColor( const FDynamicMeshColorOverlay* ColorOverlay, int32 ElementID)` — Get the overlay color the FColor,  respecting the ColorSpaceTransformMode utilizing the VertexColorRemappingFunc if requested.
- L468 _private typedef_ `using FIndex2i = UE::Geometry::FIndex2i;`
- L469 _private typedef_ `using FIndex3i = UE::Geometry::FIndex3i;`
- L504 _function_ `template<typename TriangleEnumerable, typename UVOverlayListAllocator> void FMeshRenderBufferSetConversionUtil::InitializeBuffersFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int NumTriangles, const TriangleEnumerable& Enumerable, const TArray<const FDynamicMeshUVOverlay*, UVOverlayListAllocator>& UVOverlays, const FDynamicMeshNormalOverlay* NormalOverlay, const FDynamicMeshColorOverlay* ColorOverlay, TFunctionRef<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc, bool bTrackTriangles, bool bParallel)`
- L637 _function_ `template<typename TriangleEnumerable> void FMeshRenderBufferSetConversionUtil::UpdateVertexBuffersFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int NumTriangles, const TriangleEnumerable& Enumerable, const FDynamicMeshNormalOverlay* NormalOverlay, const FDynamicMeshColorOverlay* ColorOverlay, TFunctionRef<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc, bool bUpdatePositions, bool bUpdateNormals, bool bUpdateColors)` — Update vertex positions/normals/colors of an existing set of render buffers. Assumes that buffers were created with unshared vertices, ie three vertices per triangle, eg by InitializeBuffersFromOverlays()
- L717 _function_ `template<typename TriangleEnumerable, typename UVOverlayListAllocator> void FMeshRenderBufferSetConversionUtil::UpdateVertexUVBufferFromOverlays( FMeshRenderBufferSet* RenderBuffers, const FDynamicMesh3* Mesh, int32 NumTriangles, const TriangleEnumerable& Enumerable, const TArray<const FDynamicMeshUVOverlay*, UVOverlayListAllocator>& UVOverlays)`

#### class `FDynamicMeshComponentToMeshRenderBufferSet`  
`class FDynamicMeshComponentToMeshRenderBufferSet`  
_L476-491_
- desc: Simple tool to initialize a single set of mesh buffers for the entire mesh. for examples of more complicated conversions, see DynamicMeshSceneProxy
- L480 _public member_ `FMeshRenderBufferSetConversionUtil MeshRenderBufferSetConverter;`
- L487 _public prototype_ `void Convert(class UDynamicMeshComponent& DynamicMeshComponent, FMeshRenderBufferSet& MeshRenderBufferSet, bool bUseComponentSettings = true);` — note, this conversion may recompute the tangents on the DynamicMeshComponent since a dynamic mesh component with "autocalculated" tangents will compute them on first request @param DynamicMeshComponent - the mesh to be converted @param MeshRenderBufferSet  - the buffer set to be initialized @param bUseComponentSettings - if true, the Component settings will override (and update)  MeshRederBufferSetBuilder.{ColorspaceTransformMode, bUsePerTriangleNormals}.
- L490 _protected prototype_ `TUniqueFunction<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> MakeTangentsFunc(class UDynamicMeshComponent& DynamicMeshCompnent, bool bSkipAutoCompute = false);`

#### Free symbols / members of external scopes

- L559 _function_ `` (scope `FMeshRenderBufferSetConversionUtil::InitializeBuffersFromOverlays`)

### `Source/Runtime/GeometryFramework/Public/Components/MeshRenderDecomposition.h` (Public)


#### class `FMeshRenderDecomposition`  
`class FMeshRenderDecomposition`  
_L19-100_
- desc: FMeshRenderDecomposition represents a decomposition of a mesh into "chunks" of triangles, with associated materials. This is passed to the rendering components to split a mesh into multiple RenderBuffers, for more efficient updating.
- L24 _public prototype_ `FMeshRenderDecomposition(FMeshRenderDecomposition&&) = default;` — Movable
- L25 _public prototype_ `FMeshRenderDecomposition& operator=(FMeshRenderDecomposition&&) = default;`
- L27 _public prototype_ `FMeshRenderDecomposition() = default;` — TArray<TUniquePtr> member cannot be default-constructed (in this case we just make it NonCopyable)
- L28 _public prototype_ `FMeshRenderDecomposition(const FMeshRenderDecomposition&) = delete;`
- L29 _public prototype_ `FMeshRenderDecomposition& operator=(const FMeshRenderDecomposition&) = delete;`
- L36 _public member_ `TArray<TUniquePtr<FGroup>> Groups;`
- L40 _public member_ `TArray<int32> TriangleToGroupMap;` — Mapping from TriangleID to Groups array index. Initialized by BuildAssociations()
- L42 _public function_ `void Initialize(int32 Count)`
- L51 _public function_ `int32 AppendGroup()`
- L59 _public function_ `int32 Num() const`
- L64 _public function_ `bool IsGroup(int32 Index) const`
- L69 _public function_ `FGroup& GetGroup(int32 Index)`
- L74 _public function_ `const FGroup& GetGroup(int32 Index) const`
- L79 _public function_ `int32 GetGroupForTriangle(int32 TriangleID) const`
- L87 _public prototype_ `void BuildAssociations(const FDynamicMesh3* Mesh);` — Construct mappings between mesh and groups (eg TriangleToGroupMap)
- L93 _public prototype_ `static void BuildMaterialDecomposition(const FDynamicMesh3* Mesh, const FComponentMaterialSet* MaterialSet, FMeshRenderDecomposition& Decomp);` — Build decomposition with one group for each MaterialID of mesh
- L99 _public prototype_ `static void BuildChunkedDecomposition(const FDynamicMesh3* Mesh, const FComponentMaterialSet* MaterialSet, FMeshRenderDecomposition& Decomp, int32 MaxChunkSize = 1 << 14 );` — Build per-material decomposition, and then split each of those into chunks of at most MaxChunkSize (actual chunk sizes will be highly variable and some may be very small...)

#### struct `FMeshRenderDecomposition::FGroup`  
`struct FGroup`  
_L31-35_
- L33 _public member_ `TArray<int32> Triangles;`
- L34 _public member_ `UMaterialInterface* Material;`

#### Free symbols / members of external scopes

- L11 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Source/Runtime/GeometryFramework/Public/DynamicMeshActor.h` (Public)


#### class `ADynamicMeshActor`  
`class ADynamicMeshActor : public AActor`  
_L16-66_
- reflection: `UCLASS(ConversionRoot, ComponentWrapperClass, ClassGroup=DynamicMesh, meta = (ChildCanTick), MinimalAPI)`
- inherits: `AActor`
- desc: ADynamicMeshActor is an Actor that has a USimpleDynamicMeshComponent as it's RootObject.
- L22 _protected member_ `TObjectPtr<class UDynamicMeshComponent> DynamicMeshComponent;` — `UPROPERTY(Category = DynamicMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh", AllowPrivateAccess = "true"))`
- L26 _public function_ `UDynamicMeshComponent* GetDynamicMeshComponent() const` — `UFUNCTION(BlueprintCallable, Category = DynamicMeshActor)`
- L40 _public member_ `bool bEnableComputeMeshPool = true;` — `UPROPERTY(Category = "DynamicMeshActor|Advanced", EditAnywhere, BlueprintReadWrite)` — Control whether the DynamicMeshPool will be created when requested via GetComputeMeshPool()
- L44 _protected member_ `TObjectPtr<UDynamicMeshPool> DynamicMeshPool;` — `UPROPERTY(Transient)` — The internal Mesh Pool, for use in DynamicMeshActor BPs. Use GetComputeMeshPool() to access this, as it will only be created on-demand if bEnableComputeMeshPool = true
- L49 _public prototype_ `UDynamicMeshPool* GetComputeMeshPool();` — `UFUNCTION(BlueprintCallable, Category = DynamicMeshActor)` — Access the compute mesh pool
- L53 _public prototype_ `UDynamicMesh* AllocateComputeMesh();` — `UFUNCTION(BlueprintCallable, Category = DynamicMeshActor)` — Request a compute mesh from the Pool, which will return a previously-allocated mesh or add and return a new one. If the Pool is disabled, a new UDynamicMesh will be allocated and returned.
- L57 _public prototype_ `bool ReleaseComputeMesh(UDynamicMesh* Mesh);` — `UFUNCTION(BlueprintCallable, Category = DynamicMeshActor)` — Release a compute mesh back to the Pool
- L61 _public prototype_ `void ReleaseAllComputeMeshes();` — `UFUNCTION(BlueprintCallable, Category = DynamicMeshActor)` — Release all compute meshes that the Pool has allocated
- L65 _public prototype_ `void FreeAllComputeMeshes();` — `UFUNCTION(BlueprintCallable, Category = DynamicMeshActor)` — Release all compute meshes that the Pool has allocated, and then release them from the Pool, so that they will be garbage-collected

### `Source/Runtime/GeometryFramework/Public/DynamicMeshProcessor.h` (Public)


#### class `UDynamicMeshProcessorBlueprint`  
`class UDynamicMeshProcessorBlueprint : public UObject`  
_L16-30_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Blueprints with this parent class can define general processing to apply to a dynamic mesh which can then be used to define procedural operations e.g. in Dataflow or other contexts
- L25 _public prototype_ `void ProcessDynamicMesh(UDynamicMesh* TargetMesh, bool& bFailed);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MeshProcessor")` — Apply some processing to change the input mesh @param TargetMesh Mesh to update (in place) @param bFailed Set to true to report that the processing has failed
- L29 _public member_ `bool bRequiresGameThread = true;` — `UPROPERTY(EditDefaultsOnly, Category = "MeshProcessor")` — Whether the blueprint must be run on the game thread -- i.e. if it may use nodes that aren't thread safe.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GEOMETRYFRAMEWORK_API`

### `Source/Runtime/GeometryFramework/Public/GeometryFrameworkModule.h` (Public)


#### class `FGeometryFrameworkModule`  
`class FGeometryFrameworkModule : public IModuleInterface`  
_L8-19_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `void OnPostEngineInit();` — registered in StartupModule() with FCoreDelegates::OnPostEngineInit and called once

### `Source/Runtime/GeometryFramework/Public/UDynamicMesh.h` (Public)


#### class `UDynamicMeshGenerator`  
`class UDynamicMeshGenerator : public UObject`  
_L22-28_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: UDynamicMeshGenerator is an abstract base class for an implementation that can mutate an input mesh into an output mesh. A subclass of this class can be attached to a UDynamicMesh to allow for arbitrarily-complex procedural generation
- L27 _public function_ `virtual void Generate(FDynamicMesh3& MeshInOut)` — Apply a change to MeshInOut

#### enum `EDynamicMeshChangeType`  
`enum class EDynamicMeshChangeType : uint8`  
_L38-47_
- reflection: `UENUM(BlueprintType)`
- desc: EDynamicMeshChangeType is used by FDynamicMeshChangeInfo to indicate a "type" of mesh change
- L40 _public enumerator_ `GeneralEdit = 0`
- L41 _public enumerator_ `MeshChange = 1`
- L42 _public enumerator_ `MeshReplacementChange = 2`
- L43 _public enumerator_ `MeshVertexChange = 3`
- L45 _public enumerator_ `DeformationEdit = 4`
- L46 _public enumerator_ `AttributeEdit = 5`

#### enum `EDynamicMeshAttributeChangeFlags`  
`enum class EDynamicMeshAttributeChangeFlags : uint8`  
_L50-60_
- reflection: `UENUM(BlueprintType)`
- L52 _public enumerator_ `Unknown = 0`
- L53 _public enumerator_ `MeshTopology = 1 << 0`
- L55 _public enumerator_ `VertexPositions = 1 << 1`
- L56 _public enumerator_ `NormalsTangents = 1 << 2`
- L57 _public enumerator_ `VertexColors = 1 << 3`
- L58 _public enumerator_ `UVs = 1 << 4`
- L59 _public enumerator_ `TriangleGroups = 1 << 5`

#### struct `FDynamicMeshChangeInfo`  
`struct FDynamicMeshChangeInfo`  
_L68-107_
- reflection: `USTRUCT(BlueprintType)`
- desc: FDynamicMeshChangeInfo stores information about a change to a UDynamicMesh. This struct is emitted by the UDynamicMesh OnPreMeshChanged() and OnMeshChanged() delegates.
- L73 _public member_ `EDynamicMeshChangeType Type = EDynamicMeshChangeType::GeneralEdit;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DynamicMeshChangeInfo")`
- L76 _public member_ `EDynamicMeshAttributeChangeFlags Flags = EDynamicMeshAttributeChangeFlags::Unknown;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DynamicMeshChangeInfo")`
- L80 _public member_ `bool bIsRevertChange = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DynamicMeshChangeInfo")` — for changes that are an FChange, indicates whether this is an 'Apply' or 'Revert' of the FChange
- L83 _public function_ `const FMeshRegionChangeBase* GetChange() const` — return the single valid FChange, or null
- L104 _public member_ `const FMeshChange* MeshChange = nullptr;` — internals
- L105 _public member_ `const FMeshReplacementChange* ReplaceChange = nullptr;`
- L106 _public member_ `const FMeshVertexChange* VertexChange = nullptr;`

#### class `UDynamicMesh`  
`class UDynamicMesh : public UObject, public IMeshVertexCommandChangeTarget, public IMeshCommandChangeTarget, public IMeshReplacementCommandChangeTarget`  
_L119-344_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject,IMeshVertexCommandChangeTarget,IMeshCommandChangeTarget,IMeshReplacementCommandChangeTarget`
- desc: UDynamicMesh is a UObject container for a FDynamicMesh3.
- L132 _public prototype_ `UPARAM(DisplayName = "Target") UDynamicMesh* Re` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh", meta = (Keywords = "Clear Empty Delete"))` — Clear the internal mesh to an empty mesh. This *does not* allocate a new mesh, so any existing mesh pointers/refs are still valid
- L139 _public prototype_ `UPARAM(DisplayName = "Target") UDynamicMesh* ResetToC` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh")` — Clear the internal mesh to a 100x100x100 cube with base at the origin. This this instead of Reset() if an initially-empty mesh is undesirable (eg for a Component)
- L148 _public prototype_ `virtual void InitializeMesh();` — Reset the internal mesh data and then optionally run the MeshGenerator
- L154 _public prototype_ `bool IsEmpty() const;` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh")` — @return true if the mesh has no triangles
- L160 _public prototype_ `UPARAM(DisplayName = "Triangle Count") int32 GetTriangle` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh")` — @return number of triangles in the mesh
- L167 _public function_ `const UE::Geometry::FDynamicMesh3& GetMeshRef() const` — @return Const reference to the internal FDynamicMesh3. @warning Calling ProcessMesh() is preferred! This interface may be  removed in the future
- L172 _public function_ `const UE::Geometry::FDynamicMesh3* GetMeshPtr() const` — @return Const pointer to the internal FDynamicMesh3. @warning Calling ProcessMesh() is preferred! This interface may be  removed in the future
- L178 _public function_ `UE::Geometry::FDynamicMesh3& GetMeshRef()` — @return Writable reference to the internal FDynamicMesh3. @warning Calling EditMesh() is preferred! This interface may be  removed in the future
- L183 _public function_ `UE::Geometry::FDynamicMesh3* GetMeshPtr()` — @return Writable pointer to the internal FDynamicMesh3. @warning Calling EditMesh() is preferred! This interface may be  removed in the future
- L187 _public prototype_ `void SetMesh(const UE::Geometry::FDynamicMesh3& MoveMesh);` — Replace the internal mesh with a copy of MoveMesh
- L190 _public prototype_ `void SetMesh(UE::Geometry::FDynamicMesh3&& MoveMesh);` — Replace the internal mesh with the data in MoveMesh
- L195 _public prototype_ `void ProcessMesh(TFunctionRef<void(const UE::Geometry::FDynamicMesh3&)> ProcessFunc) const;` — Apply ProcessFunc to the internal Mesh
- L201 _public prototype_ `void EditMesh(TFunctionRef<void(UE::Geometry::FDynamicMesh3&)> EditFunc, EDynamicMeshChangeType ChangeType = EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags ChangeFlags = EDynamicMeshAttributeChangeFlags::Unknown, bool bDeferChangeEvents = false);` — Apply EditFunc to the internal mesh. This will broadcast PreMeshChangedEvent, then call EditFunc(), then broadcast MeshChangedEvent and MeshModifiedBPEvent
- L209 _public prototype_ `TUniquePtr<UE::Geometry::FDynamicMesh3> ExtractMesh();` — Take ownership of the internal Mesh, and have it replaced with a new mesh
- L218 _public prototype_ `void ApplyChange(const FMeshVertexChange* Change, bool bRevert);` — IMeshVertexCommandChangeTarget implementation, allows a FVertexChange to be applied to the mesh
- L221 _public prototype_ `void ApplyChange(const FMeshChange* Change, bool bRevert);` — IMeshCommandChangeTarget implementation, allows a FMeshChange to be applied to the mesh
- L224 _public prototype_ `void ApplyChange(const FMeshReplacementChange* Change, bool bRevert);` — IMeshReplacementCommandChangeTarget implementation, allows a FMeshReplacementChange to be applied to the mesh
- L232 _protected member_ `FOnDynamicMeshChanged PreMeshChangedEvent;` — Broadcast before the internal mesh is modified by Reset funcs, SetMesh(), EditMesh(), and ApplyChange()'s above
- L234 _protected member_ `FOnDynamicMeshChanged MeshChangedEvent;` — Broadcast after the internal mesh is modified, in the same cases as PreMeshChangedEvent
- L238 _public function_ `FOnDynamicMeshChanged& OnPreMeshChanged()` — Broadcast before the internal mesh is modified by Reset funcs, SetMesh(), EditMesh(), and ApplyChange()'s above
- L240 _public function_ `FOnDynamicMeshChanged& OnMeshChanged()` — Broadcast after the internal mesh is modified, in the same cases as OnPreMeshChanged
- L245 _public member_ `FOnDynamicMeshModifiedBP MeshModifiedBPEvent;` — `UPROPERTY(BlueprintAssignable, meta = (DisplayName = "MeshModified"))` — Blueprintable event called when mesh is modified, in the same cases as OnMeshChanged
- L259 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMeshRealtimeUpdate, UDynamicMesh*);`
- L264 _public function_ `FOnMeshRealtimeUpdate& OnMeshRealtimeUpdate()` — Multicast delegate that is broadcast whenever PostRealtimeUpdate() is called
- L269 _public prototype_ `virtual void PostRealtimeUpdate();` — Broadcasts FOnMeshRealtimeUpdate
- L272 _protected member_ `FOnMeshRealtimeUpdate MeshRealtimeUpdateEvent;`
- L281 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMesh3> Mesh;` — Mesh data, owned by this object. By default will have Attributes enabled and MaterialID enabled.
- L286 _protected prototype_ `void InitializeNewMesh();` — Allocate a new Mesh (ie pointer will change) and then call InitializeMesh()
- L291 _protected prototype_ `void EditMeshInternal(TFunctionRef<void(UE::Geometry::FDynamicMesh3&)> EditFunc, const FDynamicMeshChangeInfo& ChangeInfo, bool bDeferChangeEvents = false);` — Internal function that edits the Mesh, but broadcasts PreMeshChangedEvent and MeshChangedEvent, and then MeshModifiedBPEvent
- L296 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — serialize Mesh to an Archive
- L299 _public prototype_ `virtual void ExportCustomProperties(FOutputDevice& Out, uint32 Indent) override;` — serialize Mesh to/from T3D
- L300 _public prototype_ `virtual void ImportCustomProperties(const TCHAR* SourceText, FFeedbackContext* Warn) override;`
- L319 _protected member_ `TObjectPtr<UDynamicMeshGenerator> MeshGenerator;` — `UPROPERTY(Instanced)` — Active mesh generator. If configured, and bEnableMeshGenerator is true, then MeshGenerator->Generate() will be called when this mesh is Reset(). The Regenerate() function below can be used to force regeneration.
- L327 _public member_ `bool bEnableMeshGenerator = false;` — `UPROPERTY(EditAnywhere, Category = "Dynamic Mesh")` — Controls whether the active Generator (if configured) will be applied when rebuilding the mesh
- L332 _public prototype_ `virtual void SetMeshGenerator(TObjectPtr<UDynamicMeshGenerator> NewGenerator);` — Set the active mesh generator. Clears if nullptr
- L337 _public prototype_ `virtual void ClearMeshGenerator();` — Set the active mesh generator. Clears if nullptr
- L342 _public prototype_ `virtual void Regenerate();` — Reset() the mesh, which will re-run the active MeshGenerator, if bEnableMeshGenerator

#### class `UDynamicMeshPool`  
`class UDynamicMeshPool : public UObject`  
_L387-420_
- reflection: `UCLASS(BlueprintType, Transient, MinimalAPI)`
- inherits: `UObject`
- desc: UDynamicMeshPool manages a Pool of UDynamicMesh objects. This allows the meshes to be re-used instead of being garbage-collected. This is intended to be used by Blueprints that need to do procedural geometry operations that generate temporary meshes, as these will commonly run their construction scripts many times as the user (eg) manipulates parameters, and constantly spawning new UDynamicMesh instances will result in enormous memory usage hanging around until GC runs. Usage is to call RequestMesh() to take ownership of an available UDynamicMesh (which will allocate a new one if the pool is empty) and ReturnMesh() to return it to the pool. ReturnAllMeshes() can be called to return all allocated meshes. In both cases, there is nothing preventing you from still holding on to the mesh. So, be careful. FreeAllMeshes() calls ReturnAllMeshes() and then releases the pool's references to the allocated meshes, so they can be Garbage Collected If you Request() more meshes than you Return(), the Pool will still be holding on to references to those meshes, and they will never be Garbage Collected (ie memory leak). As a failsafe, if the number of allocated meshes exceeds geometry.DynamicMesh.MaxPoolSize, the Pool will release all it's references and run garbage collection on the next call to RequestMesh(). (Do not rely on this as a memory management strategy) An alternate strategy that could be employed here is for the Pool to not hold references to meshes it has provided, only those tha
- L393 _public prototype_ `UDynamicMesh* RequestMesh();` — `UFUNCTION(BlueprintCallable, Category="Dynamic Mesh")` — @return an available UDynamicMesh from the pool (possibly allocating a new mesh)
- L397 _public prototype_ `void ReturnMesh(UDynamicMesh* Mesh);` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh")` — Release a UDynamicMesh returned by RequestMesh() back to the pool
- L401 _public prototype_ `void ReturnAllMeshes();` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh")` — Release all GeneratedMeshes back to the pool
- L405 _public prototype_ `void FreeAllMeshes();` — `UFUNCTION(BlueprintCallable, Category = "Dynamic Mesh")` — Release all GeneratedMeshes back to the pool and allow them to be garbage collected
- L410 _protected member_ `TArray<TObjectPtr<UDynamicMesh>> CachedMeshes;` — `UPROPERTY()` — Meshes in the pool that are available
- L414 _protected member_ `TArray<TObjectPtr<UDynamicMesh>> AllCreatedMeshes;` — `UPROPERTY()` — All meshes the pool has allocated
- L419 _private member_ `mutable FCriticalSection PoolAccessCs;` — Typically the mesh pool is used from the game thread, but in case it is not, we protect pool access w/ this critical section

#### Free symbols / members of external scopes

- L110 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDynamicMeshChanged, UDynamicMesh*, FDynamicMeshChangeInfo);` — These delegates are used by UDynamicMesh
- L110 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDynamicMeshChanged, UDynamicMesh*, FDynamicMeshChangeInfo);` — These delegates are used by UDynamicMesh
- L111 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDynamicMeshModifiedBP, UDynamicMesh*, Mesh);`
- L111 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDynamicMeshModifiedBP, UDynamicMesh*, Mesh);`
- L259 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMeshRealtimeUpdate, UDynamicMesh*);`
