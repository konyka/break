# Plugins / ProceduralMeshComponent

- module root: `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent`
- headers: 5; symbols: 87
- symbol kinds: class=3, delegate=1, enum=1, enumerator=3, function=13, macro=2, member=22, prototype=39, struct=3
- PrivateIncludePathModuleNames: Shaders
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MeshDescription, PhysicsCore, RHI, RenderCore, StaticMeshDescription

### `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Private/ProceduralMeshComponentPluginPrivate.h` (Private)


#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_STATS_GROUP(TEXT("ProceduralMesh"), STATGROUP_ProceduralMesh, STAT`

### `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/IProceduralMeshComponentPlugin.h` (Public)


#### class `IProceduralMeshComponentPlugin`  
`class IProceduralMeshComponentPlugin : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IProceduralMeshComponentPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/KismetProceduralMeshLibrary.h` (Public)


#### enum `EProcMeshSliceCapOption`  
`enum class EProcMeshSliceCapOption : uint8`  
_L19-27_
- reflection: `UENUM()`
- desc: Options for creating cap geometry when slicing
- L22 _public enumerator_ `NoCap` — Do not create cap geometry
- L24 _public enumerator_ `CreateNewSectionForCap` — Add a new section to ProceduralMesh for cap
- L26 _public enumerator_ `UseLastSectionForCap` — Add cap geometry to existing last section

#### class `UKismetProceduralMeshLibrary`  
`class UKismetProceduralMeshLibrary : public UBlueprintFunctionLibrary`  
_L30-110_
- reflection: `UCLASS(MinimalAPI, meta=(ScriptName="ProceduralMeshLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L37 _public prototype_ `static void GenerateBoxMesh(FVector BoxRadius, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UVs, TArray<FProcMeshTangent>& Tangents);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Generate vertex and index buffer for a simple box, given the supplied dimensions. Normals, UVs and tangents are also generated for each vertex.
- L44 _public prototype_ `static void CalculateTangentsForMesh(const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector2D>& UVs, TArray<FVector>& Normals, TArray<FProcMeshTangent>& Tangents);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta=(AutoCreateRefTerm = "SmoothingGroups,UVs" ))` — Automatically generate normals and tangent vectors for a mesh UVs are required for correct tangent generation.
- L48 _public prototype_ `static void ConvertQuadToTriangles(UPARAM(ref) TArray<int32>& Triangles, int32 Vert0, int32 Vert1, int32 Vert2, int32 Vert3);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Add a quad, specified by four indices, to a triangle index buffer as two triangles.
- L58 _public prototype_ `static void CreateGridMeshTriangles(int32 NumX, int32 NumY, bool bWinding, TArray<int32>& Triangles);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Generate an index buffer for a grid of quads. @param	NumX			Number of vertices in X direction (must be >= 2) @param	NumY			Number of vertices in y direction (must be >= 2) @param	bWinding		Reverses winding of indices generated for each quad @out	Triangles		Output index buffer
- L70 _public prototype_ `static void CreateGridMeshWelded(int32 NumX, int32 NumY, TArray<int32>& Triangles, TArray<FVector>& Vertices, TArray<FVector2D>& UVs, float GridSpacing = 16.0f);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Generate a vertex buffer, index buffer and UVs for a tessellated grid mesh. @param	NumX			Number of vertices in X direction (must be >= 2) @param	NumY			Number of vertices in y direction (must be >= 2) @out	Triangles		Output index buffer @out	Vertices		Output vertex buffer @out	UVs				Out UVs @param	GridSpacing		Size of each quad in world units
- L83 _public prototype_ `static void CreateGridMeshSplit(int32 NumX, int32 NumY, TArray<int32>& Triangles, TArray<FVector>& Vertices, TArray<FVector2D>& UVs, TArray<FVector2D>& UV1s, float GridSpacing = 16.0f);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Generate a vertex buffer, index buffer and UVs for a grid mesh where each quad is split, with standard 0-1 UVs on UV0 and point sampled texel center UVs for UV1. @param	NumX			Number of vertices in X direction (must be >= 2) @param	NumY			Number of vertices in y direction (must be >= 2) @out	Triangles		Output index buffer @out	Vertices		Output vertex buffer @out	UVs				Out UVs @out	UV1s			Out UV1s @param	GridSpacing		Size of each quad in world units
- L87 _public prototype_ `static void GetSectionFromStaticMesh(UStaticMesh* InMesh, int32 LODIndex, int32 SectionIndex, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UVs, TArray<FProcMeshTangent>& Tangents);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Grab geometry data from a StaticMesh asset.
- L91 _public prototype_ `static void CopyProceduralMeshFromStaticMeshComponent(UStaticMeshComponent* StaticMeshComponent, int32 LODIndex, UProceduralMeshComponent* ProcMeshComponent, bool bCreateCollision);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Copy materials from StaticMeshComponent to ProceduralMeshComponent.
- L95 _public prototype_ `static void GetSectionFromProceduralMesh(UProceduralMeshComponent* InProcMesh, int32 SectionIndex, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals, TArray<FVector2D>& UVs, TArray<FProcMeshTangent>& Tangents);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Grab geometry data from a ProceduralMeshComponent.
- L109 _public prototype_ `static void SliceProceduralMesh(UProceduralMeshComponent* InProcMesh, FVector PlanePosition, FVector PlaneNormal, bool bCreateOtherHalf, UProceduralMeshComponent*& OutOtherHalfProcMesh, EProcMeshSliceCapOption CapOption, UMaterialInterface* CapMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Slice the ProceduralMeshComponent (including simple convex collision) using a plane. Optionally create 'cap' geometry. @param	InProcMesh				ProceduralMeshComponent to slice @param	PlanePosition			Point on the plane to use for slicing, in world space @param	PlaneNormal				Normal of plane used for slicing. Geometry on the positive side of the plane will be kept. @param	bCreateOtherHalf		If true, an additional ProceduralMeshComponent (OutOtherHalfProcMesh) will be created using the other half of the sliced geometry @param	OutOtherHalfProcMesh	If bCreateOtherHalf is set, this is the new component created. Its owner will be the same as the supplied InProcMesh. @param	CapOption				If and how to create 'cap' geometry on the slicing plane @param	CapMaterial				If creating a new section for the cap, assign this material to that section

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PROCEDURALMESHCOMPONENT_API`

### `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/ProceduralMeshComponent.h` (Public)


#### struct `FProcMeshTangent`  
`struct FProcMeshTangent`  
_L20-47_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct used to specify a tangent vector for a vertex The Y tangent is computed from the cross product of the vertex normal (Tangent Z) and the TangentX member.
- L27 _public member_ `FVector TangentX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tangent)` — Direction of X tangent for this vertex
- L31 _public member_ `bool bFlipTangentY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tangent)` — Bool that indicates whether we should flip the Y tangent when we compute it using cross product
- L33 _public function_ `FProcMeshTangent() : TangentX(1.f, 0.f, 0.f) , bFlipTangentY(false)`
- L38 _public function_ `FProcMeshTangent(float X, float Y, float Z) : TangentX(X, Y, Z) , bFlipTangentY(false)`
- L43 _public function_ `FProcMeshTangent(FVector InTangentX, bool bInFlipTangentY) : TangentX(InTangentX) , bFlipTangentY(bInFlipTangentY)`

#### struct `FProcMeshVertex`  
`struct FProcMeshVertex`  
_L51-99_
- reflection: `USTRUCT(BlueprintType)`
- desc: One vertex for the procedural mesh, used for storing data internally
- L58 _public member_ `FVector Position;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vertex)` — Vertex position
- L62 _public member_ `FVector Normal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vertex)` — Vertex normal
- L66 _public member_ `FProcMeshTangent Tangent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vertex)` — Vertex tangent
- L70 _public member_ `FColor Color;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vertex)` — Vertex color
- L74 _public member_ `FVector2D UV0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vertex)` — Vertex texture co-ordinate
- L78 _public member_ `FVector2D UV1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vertex)` — Vertex texture co-ordinate
- L82 _public member_ `FVector2D UV2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vertex)` — Vertex texture co-ordinate
- L86 _public member_ `FVector2D UV3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Vertex)` — Vertex texture co-ordinate
- L89 _public function_ `FProcMeshVertex() : Position(0.f, 0.f, 0.f) , Normal(0.f, 0.f, 1.f) , Tangent(FVector(1.f, 0.f, 0.f), false) , Color(255, 255, 255) , UV0(0.f, 0.f) , UV1(0.f, 0.f) , UV2(0.f, 0.f) , UV3(0.f, 0.f)`

#### struct `FProcMeshSection`  
`struct FProcMeshSection`  
_L103-142_
- reflection: `USTRUCT()`
- desc: One section of the procedural mesh. Each material has its own section.
- L110 _public member_ `TArray<FProcMeshVertex> ProcVertexBuffer;` — `UPROPERTY()` — Vertex buffer for this section
- L114 _public member_ `TArray<uint32> ProcIndexBuffer;` — `UPROPERTY()` — Index buffer for this section
- L117 _public member_ `FBox SectionLocalBox;` — `UPROPERTY()` — Local bounding box of section
- L121 _public member_ `bool bEnableCollision;` — `UPROPERTY()` — Should we build collision data for triangles in this section
- L125 _public member_ `bool bSectionVisible;` — `UPROPERTY()` — Should we display this section
- L127 _public function_ `FProcMeshSection() : SectionLocalBox(ForceInit) , bEnableCollision(false) , bSectionVisible(true)`
- L134 _public function_ `void Reset()` — Reset this section, clear all mesh info.

#### class `UProceduralMeshComponent`  
`class UProceduralMeshComponent : public UMeshComponent, public IInterface_CollisionDataProvider`  
_L149-349_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Object, LOD), meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)`
- inherits: `UMeshComponent,IInterface_CollisionDataProvider`
- desc: Component that allows you to specify custom triangle mesh geometry Beware! This feature is experimental and may be substantially changed in future releases.
- L154 _public prototype_ `UProceduralMeshComponent(const FObjectInitializer& ObjectInitializer);`
- L169 _public function_ `void CreateMeshSection(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bCreateCollision)` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta = (DeprecatedFunction, DeprecationMessage = "This function is deprecated for Blueprints because it uses the unsupported 'Color' type. Use new 'Create Mesh Section' function which uses LinearColor instead.", DisplayName = "Create Mesh Section FColor", AutoCreateRefTerm = "Normals,UV0,VertexColors,Tangents"))` — Create/replace a section for this procedural mesh component. This function is deprecated for Blueprints because it uses the unsupported 'Color' type. Use new 'Create Mesh Section' function which uses LinearColor instead. @param	SectionIndex		Index of the section to create or replace. @param	Vertices			Vertex buffer of all vertex positions to use for this mesh section. @param	Triangles			Index buffer indicating which vertices make up each triangle. Length must be a multiple of 3. @param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array. @param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array. @param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array. @param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array. @param	bCreateCollision	Indicates whether collision should be created for this section. This adds significant cost.
- L175 _public prototype_ `void CreateMeshSection(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, const TArray<FVector2D>& UV2, const TArray<FVector2D>& UV3, const TArray<FColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bCreateCollision);`
- L193 _public function_ `void CreateMeshSection_LinearColor(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FLinearColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bCreateCollision, bool bSRGBConversion = false)`
- L209 _public function_ `void UpdateMeshSection(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents)` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh", meta = (DeprecatedFunction, DeprecationMessage = "This function is deprecated for Blueprints because it uses the unsupported 'Color' type. Use new 'Update Mesh Section' function which uses LinearColor instead.", DisplayName = "Update Mesh Section FColor", AutoCreateRefTerm = "Normals,UV0,VertexColors,Tangents"))` — Updates a section of this procedural mesh component. This is faster than CreateMeshSection, but does not let you change topology. Collision info is also updated. This function is deprecated for Blueprints because it uses the unsupported 'Color' type. Use new 'Create Mesh Section' function which uses LinearColor instead. @param	Vertices			Vertex buffer of all vertex positions to use for this mesh section. @param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array. @param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array. @param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array. @param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array.
- L215 _public prototype_ `void UpdateMeshSection(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FVector2D>& UV1, const TArray<FVector2D>& UV2, const TArray<FVector2D>& UV3, const TArray<FColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents);`
- L230 _public function_ `void UpdateMeshSection_LinearColor(int32 SectionIndex, const TArray<FVector>& Vertices, const TArray<FVector>& Normals, const TArray<FVector2D>& UV0, const TArray<FLinearColor>& VertexColors, const TArray<FProcMeshTangent>& Tangents, bool bSRGBConversion = true)`
- L238 _public prototype_ `void ClearMeshSection(int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Clear a section of the procedural mesh. Other sections do not change index.
- L242 _public prototype_ `void ClearAllMeshSections();` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Clear all mesh sections and reset to empty state
- L246 _public prototype_ `void SetMeshSectionVisible(int32 SectionIndex, bool bNewVisibility);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Control visibility of a particular section
- L250 _public prototype_ `bool IsMeshSectionVisible(int32 SectionIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Returns whether a particular section is currently visible
- L254 _public prototype_ `int32 GetNumSections() const;` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Returns number of sections currently created for this component
- L258 _public prototype_ `void AddCollisionConvexMesh(TArray<FVector> ConvexVerts);` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Add simple collision convex to this component
- L262 _public prototype_ `void ClearCollisionConvexMeshes();` — `UFUNCTION(BlueprintCallable, Category = "Components|ProceduralMesh")` — Remove collision meshes from this component
- L265 _public prototype_ `void SetCollisionConvexMeshes(const TArray< TArray<FVector> >& ConvexMeshes);` — Function to replace _all_ simple collision in one go
- L268 _public prototype_ `virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const override;`
- L269 _public prototype_ `virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;`
- L270 _public prototype_ `virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;`
- L271 _public function_ `virtual bool WantsNegXTriMesh() override`
- L279 _public member_ `bool bUseComplexAsSimpleCollision;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Procedural Mesh")` — Controls whether the complex (Per poly) geometry should be treated as 'simple' collision. Should be set to false if this component is going to be given simple collision and simulated.
- L285 _public member_ `bool bUseAsyncCooking;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Procedural Mesh")` — Controls whether the physics cooking should be done off the game thread. This should be used when collision geometry doesn't have to be immediately up to date (For example streaming in far away objects)
- L289 _public member_ `TObjectPtr<class UBodySetup> ProcMeshBodySetup;` — `UPROPERTY(Instanced)` — Collision data
- L295 _public prototype_ `FProcMeshSection* GetProcMeshSection(int32 SectionIndex);` — Get pointer to internal data for one section of this procedural mesh component. Note that pointer will becomes invalid if sections are added or removed.
- L298 _public prototype_ `void SetProcMeshSection(int32 SectionIndex, const FProcMeshSection& Section);` — Replace a section with new section geometry
- L301 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L302 _public prototype_ `virtual class UBodySetup* GetBodySetup() override;`
- L303 _public prototype_ `virtual UMaterialInterface* GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const override;`
- L307 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L311 _public prototype_ `virtual void PostLoad() override;`
- L315 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L321 _private prototype_ `void UpdateLocalBounds();` — Update LocalBounds member from the local box of each section
- L323 _private prototype_ `void CreateProcMeshBodySetup();` — Ensure ProcMeshBodySetup is allocated and configured
- L325 _private prototype_ `void UpdateCollision();` — Mark collision data as dirty, and re-create on instance if necessary
- L327 _private prototype_ `void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);` — Once async physics cook is done, create needed state
- L330 _private prototype_ `UBodySetup* CreateBodySetupHelper();` — Helper to create new body setup objects
- L334 _private member_ `TArray<FProcMeshSection> ProcMeshSections;` — `UPROPERTY()` — Array of sections of mesh
- L338 _private member_ `TArray<FKConvexElem> CollisionConvexElems;` — `UPROPERTY()` — Convex shapes used for simple collision
- L342 _private member_ `FBoxSphereBounds LocalBounds;` — `UPROPERTY()` — Local space bounds of mesh
- L346 _private member_ `TArray<TObjectPtr<UBodySetup>> AsyncBodySetupQueue;` — `UPROPERTY(transient)` — Queue for async body setups that are being cooked

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PROCEDURALMESHCOMPONENT_API`

### `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/ProceduralMeshConversion.h` (Public)


#### Free symbols / members of external scopes

- L13 _prototype_ `BuildMeshDescription( UProceduralMeshComponent* ProcMeshComp );`
- L17 _prototype_ `MeshDescriptionToProcMesh( const FMeshDescription& MeshDescription, UProceduralMeshComponent* ProcMeshComp );`
