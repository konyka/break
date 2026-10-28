# Runtime / MRMesh

- module root: `Source/Runtime/MRMesh`
- headers: 6; symbols: 162
- symbol kinds: class=7, delegate=4, enum=1, enumerator=3, function=15, macro=7, member=47, prototype=74, struct=3, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, RHI, RenderCore, UnrealEd
- PrivateIncludePathModuleNames: DerivedDataCache

### `Source/Runtime/MRMesh/Public/BaseMeshReconstructorModule.h` (Public)


#### class `FBaseMeshReconstructorModule`  
`class FBaseMeshReconstructorModule : public IModuleInterface, public IModularFeature`  
_L12-63_
- inherits: `IModuleInterface,IModularFeature`
- L25 _public function_ `static FName GetModularFeatureName()` — Part of the pattern for supporting modular features. @return the name of the feature.
- L36 _public function_ `static inline FBaseMeshReconstructorModule& Get()` — Singleton-like access to a MeshReconstructorModule. @return Returns reference to the highest priority MeshReconstructorModule module
- L50 _public function_ `static inline bool IsAvailable()` — Check to see that there is a MeshReconstructor module available. @return True if there exists a MeshReconstructor module registered.
- L58 _public function_ `virtual void StartupModule() override` — Register module as a MeshReconstructor on startup.

### `Source/Runtime/MRMesh/Public/MRMeshBufferDefines.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define WANTS_MRMESH_UVS 1`
- L11 _macro_ `#define WANTS_MRMESH_UVS 0`
- L17 _macro_ `#define WANTS_MRMESH_TANGENTS 1`
- L19 _macro_ `#define WANTS_MRMESH_TANGENTS 0`
- L25 _macro_ `#define WANTS_MRMESH_COLORS 1`
- L27 _macro_ `#define WANTS_MRMESH_COLORS 0`
- L32 _macro_ `#define MRMESH_INDEX_TYPE uint32`

### `Source/Runtime/MRMesh/Public/MRMeshComponent.h` (Public)


#### class `IMRMesh`  
`class IMRMesh`  
_L28-58_
- L37 _public typedef_ `typedef uint64 FBrickId;`
- L51 _public prototype_ `virtual void SetConnected(bool value) = 0;`
- L52 _public prototype_ `virtual bool IsConnected() const = 0;`
- L54 _public prototype_ `virtual void SendRelativeTransform(const FTransform& Transform) = 0;`
- L55 _public prototype_ `virtual void SendBrickData(FSendBrickDataArgs Args) = 0;`
- L56 _public prototype_ `virtual void Clear() = 0;`
- L57 _public prototype_ `virtual void ClearAllBrickData() = 0;`

#### struct `IMRMesh::FBrickDataReceipt`  
`struct FBrickDataReceipt`  
_L31-35_
- L34 _public prototype_ `virtual ~FBrickDataReceipt() = default;` — Optionally subclass and use receipt.  For example: to release the buffers FSendBrickDataArgs has references to.

#### struct `IMRMesh::FSendBrickDataArgs`  
`struct FSendBrickDataArgs`  
_L38-49_
- L41 _public member_ `TSharedPtr<FBrickDataReceipt, ESPMode::ThreadSafe> BrickDataReceipt;` — Note: many members are references!  Be aware of the lifetime of the underlying data.  FBrickDataReceipt is intended to help manage that.
- L42 _public member_ `const FBrickId BrickId = 0;`
- L43 _public member_ `const TArray<FVector3f>& PositionData;`
- L44 _public member_ `const TArray<FVector2D>& UVData;`
- L45 _public member_ `const TArray<FPackedNormal>& TangentXZData;`
- L46 _public member_ `const TArray<FColor>& ColorData;`
- L47 _public member_ `const TArray<MRMESH_INDEX_TYPE>& Indices;`
- L48 _public member_ `const FBox Bounds = FBox(EForceInit::ForceInit);`

#### class `UMRMeshBodyHolder`  
`class UMRMeshBodyHolder : public UObject, public IInterface_CollisionDataProvider`  
_L63-98_
- reflection: `UCLASS(transient)`
- inherits: `UObject,IInterface_CollisionDataProvider`
- desc: Because physics cooking uses GetOuter() to get the IInterface_CollisionDataProvider and provides no way to determine which physics body it is currently working on we are wrapping each body in this Holder so that it can be the Outer and provide the correct data.
- L68 _public prototype_ `void Initialize(IMRMesh::FBrickId InBrickId);`
- L69 _public prototype_ `void Update(const IMRMesh::FSendBrickDataArgs& Args);`
- L70 _public prototype_ `void AbortCook();`
- L71 _public prototype_ `void ReleaseArgData();`
- L72 _public prototype_ `void Cleanup();`
- L75 _public prototype_ `virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;`
- L76 _public prototype_ `virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const override;`
- L77 _public prototype_ `virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;`
- L78 _public function_ `virtual bool WantsNegXTriMesh() override`
- L82 _public prototype_ `void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);` — Once async physics cook is done, create needed state
- L85 _public member_ `TObjectPtr<class UBodySetup> BodySetup;` — `UPROPERTY(transient)`
- L88 _public member_ `FBodyInstance BodyInstance;` — `UPROPERTY(transient)`
- L91 _public member_ `TSharedPtr<IMRMesh::FBrickDataReceipt, ESPMode::ThreadSafe> BrickDataReceipt;` — Hold references to the bulk data which is owned externally, like FSendBrickDataArgs.  The receipt keeps the references valid.
- L92 _public member_ `IMRMesh::FBrickId BrickId = 0;`
- L93 _public member_ `const TArray<FVector3f>* PositionData = nullptr;`
- L94 _public member_ `const TArray<MRMESH_INDEX_TYPE>* Indices = nullptr;`
- L95 _public member_ `FBox Bounds = FBox(EForceInit::ForceInit);`
- L97 _public member_ `bool bCookInProgress = false;`

#### class `UMRMeshComponent`  
`class UMRMeshComponent : public UPrimitiveComponent, public IMRMesh`  
_L105-263_
- reflection: `UCLASS(hideCategories=(Physics), meta = (BlueprintSpawnableComponent), ClassGroup = Rendering, MinimalAPI)`
- inherits: `UPrimitiveComponent,IMRMesh`
- L112 _public prototype_ `virtual void BeginPlay() override;`
- L113 _public prototype_ `void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L116 _public function_ `bool IsConnected() const override` — `UFUNCTION(BlueprintPure, Category = "Mesh Reconstruction")`
- L118 _public function_ `void SetConnected(bool value) override`
- L119 _public function_ `virtual void SendRelativeTransform(const FTransform& Transform) override`
- L125 _public prototype_ `void ForceNavMeshUpdate();` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")` — Force navmesh generation to run using the current collision data.  This will run even if the collision data has not been udpated! Unless you are changing navmesh settings or similar RequestNavMeshUpdate is reccomended.
- L131 _public prototype_ `void RequestNavMeshUpdate();` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")` — Generate nav mesh if collision data has changed since the last nav mesh generation.
- L134 _public prototype_ `void Clear() override;` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L137 _public prototype_ `virtual void SetMaterial(int32 ElementIndex, class UMaterialInterface* InMaterial) override;` — UPrimitiveComponent.. public BP function needs to stay public to avoid nativization errors. (RR)
- L138 _public prototype_ `virtual class UMaterialInterface* GetMaterial(int32 ElementIndex) const override;`
- L142 _public prototype_ `virtual void SetWireframeMaterial(class UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")` — Set the wireframe material.
- L145 _public prototype_ `void UpdateMesh(const FVector& InLocation, const FQuat& InRotation, const FVector& Scale, TArray<FVector>& Vertices, TArray<MRMESH_INDEX_TYPE>& Indices, TArray<FVector2D> UVData = {}, TArray<FPackedNormal> TangentXZData = {}, TArray<FColor> ColorData = {});` — Updates from iOS
- L146 _public prototype_ `void UpdateMesh(const FVector& InLocation, const FQuat& InRotation, const FVector& Scale, TArray<FVector3f>& Vertices, TArray<MRMESH_INDEX_TYPE>& Indices, TArray<FVector2D> UVData = {}, TArray<FPackedNormal> TangentXZData = {}, TArray<FColor> ColorData = {});`
- L149 _public prototype_ `void SetEnableMeshOcclusion(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L152 _public function_ `bool GetEnableMeshOcclusion() const` — `UFUNCTION(BlueprintPure, Category = "Mesh Reconstruction")`
- L155 _public prototype_ `void SetUseWireframe(bool bUseWireframe);` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L158 _public function_ `bool GetUseWireframe() const` — `UFUNCTION(BlueprintPure, Category = "Mesh Reconstruction")`
- L161 _public prototype_ `void SetWireframeColor(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L164 _public function_ `const FLinearColor& GetWireframeColor() const` — `UFUNCTION(BlueprintPure, Category = "Mesh Reconstruction")`
- L166 _public prototype_ `UMaterialInterface* GetMaterialToUse() const;`
- L168 _public function_ `FOnMRMeshBrickDataUpdatedDelegate& OnBrickDataUpdated()`
- L171 _protected prototype_ `virtual void OnActorEnableCollisionChanged() override;`
- L172 _protected prototype_ `virtual void UpdatePhysicsToRBChannels() override;`
- L174 _public prototype_ `virtual void SetCollisionObjectType(ECollisionChannel Channel) override;`
- L175 _public prototype_ `virtual void SetCollisionResponseToChannel(ECollisionChannel Channel, ECollisionResponse NewResponse) override;`
- L176 _public prototype_ `virtual void SetCollisionResponseToAllChannels(ECollisionResponse NewResponse) override;`
- L177 _public prototype_ `virtual void SetCollisionResponseToChannels(const FCollisionResponseContainer& NewResponses) override;`
- L178 _public prototype_ `virtual void SetCollisionEnabled(ECollisionEnabled::Type NewType) override;`
- L179 _public prototype_ `virtual void SetCollisionProfileName(FName InCollisionProfileName, bool bUpdateOverlaps=true) override;`
- L181 _public prototype_ `virtual void SetWalkableSlopeOverride(const FWalkableSlopeOverride& NewOverride) override;`
- L183 _public function_ `void SetNeverCreateCollisionMesh(bool bNeverCreate)`
- L184 _public function_ `void SetEnableNavMesh(bool bEnable)`
- L185 _public prototype_ `void SuggestNavMeshUpdate();`
- L188 _public prototype_ `DECLARE_EVENT(UMRMeshComponent, FOnClear);` — Trackers feeding mesh data to this component may want to know when we clear our mesh data
- L189 _public function_ `FOnClear& OnClear()`
- L193 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L194 _private prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L195 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L196 _private prototype_ `virtual bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const override;`
- L200 _private prototype_ `virtual bool ShouldCreatePhysicsState() const override;`
- L201 _private prototype_ `virtual void SendRenderDynamicData_Concurrent() override;`
- L205 _private prototype_ `virtual void SendBrickData(FSendBrickDataArgs Args) override;`
- L206 _private prototype_ `virtual void ClearAllBrickData() override;`
- L210 _private prototype_ `void SendBrickData_Internal(IMRMesh::FSendBrickDataArgs Args);`
- L212 _private prototype_ `void RemoveBodyInstance(int32 BodyIndex);`
- L213 _private prototype_ `void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) override;`
- L215 _private prototype_ `void ClearAllBrickData_Internal();`
- L218 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L221 _private member_ `TObjectPtr<UMaterialInterface> WireframeMaterial;` — `UPROPERTY(EditAnywhere, Category = Appearance)`
- L225 _private member_ `bool bCreateMeshProxySections = true;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — If true, MRMesh will create a renderable mesh proxy.  If false it will not, but could still provide collision.
- L229 _private member_ `bool bUpdateNavMeshOnMeshUpdate = true;` — `UPROPERTY(EditAnywhere, Category = MRMesh)` — If true, MRMesh will automatically update its navmesh whenever any Mesh section is updated. This may be expensive. If this is disabled use ForceNavMeshUpdate to trigger a navmesh update when necessary.  Moving the component will also trigger a navmesh update.
- L231 _private member_ `bool bNavMeshUpdateSuggested = false;`
- L235 _private member_ `bool bNeverCreateCollisionMesh = false;` — `UPROPERTY(EditAnywhere, Category = MRMesh)` — If true, MRMesh will not create a collidable ridgid body for each mesh section and can therefore never have collision.  Avoids the cost of generating collision.
- L241 _private member_ `bool bUseAsyncCooking = true;` — Controls whether the physics cooking should be done off the game thread. This should be used when collision geometry doesn't have to be immediately up to date (For example streaming in far away objects). Fixing this to true for now.
- L243 _private member_ `bool bConnected = false;`
- L246 _private member_ `bool bEnableOcclusion;` — Whether this mesh should write z-depth to occlude meshes or not
- L248 _private member_ `bool bUseWireframe;` — Whether this mesh should draw using the wireframe material when no material is set or not
- L250 _private member_ `FOnClear OnClearEvent;`
- L252 _private member_ `FLinearColor WireframeColor = FLinearColor::White;`
- L254 _private member_ `FOnMRMeshBrickDataUpdatedDelegate OnBrickDataUpdatedDelegate;`
- L259 _private member_ `TArray<TObjectPtr<UMRMeshBodyHolder>> BodyHolders;` — `UPROPERTY(Transient)` — Collision/Physics data
- L262 _private member_ `TArray<IMRMesh::FBrickId> BodyIds;` — This array is parallel to BodyHolders

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_STATS_GROUP(TEXT("MRMesh"), STATGROUP_MRMESH, STATCAT_Adva`
- L26 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogMrMesh, Warning, All);`
- L102 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMRMeshBrickDataUpdatedDelegate, const UMRMeshComponent*, const IMRMesh::FSendBrickDataArgs&);`
- L102 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMRMeshBrickDataUpdatedDelegate, const UMRMeshComponent*, const IMRMesh::FSendBrickDataArgs&);`
- L188 _delegate_ `DECLARE_EVENT(UMRMeshComponent, FOnClear);` — Trackers feeding mesh data to this component may want to know when we clear our mesh data

### `Source/Runtime/MRMesh/Public/MRMeshModule.h` (Public)


#### class `IMRMeshModule`  
`class IMRMeshModule : public IModuleInterface`  
_L8-10_
- inherits: `IModuleInterface`

### `Source/Runtime/MRMesh/Public/MeshReconstructorBase.h` (Public)


#### struct `FMRMeshConfiguration`  
`struct FMRMeshConfiguration`  
_L17-22_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `bool bSendVertexColors = false;`

#### class `UMeshReconstructorBase`  
`class UMeshReconstructorBase : public UObject`  
_L25-51_
- reflection: `UCLASS(meta=(Experimental), MinimalAPI)`
- inherits: `UObject`
- L31 _public prototype_ `virtual void StartReconstruction();` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L34 _public prototype_ `virtual void StopReconstruction();` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L37 _public prototype_ `virtual void PauseReconstruction();` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L40 _public prototype_ `virtual bool IsReconstructionStarted() const;` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L43 _public prototype_ `virtual bool IsReconstructionPaused() const;` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")`
- L46 _public prototype_ `virtual void ConnectMRMesh(UMRMeshComponent* Mesh);` — `UFUNCTION()`
- L49 _public prototype_ `virtual void DisconnectMRMesh();` — `UFUNCTION()`

### `Source/Runtime/MRMesh/Public/MockDataMeshTrackerComponent.h` (Public)


#### enum `EMeshTrackerVertexColorMode`  
`enum class EMeshTrackerVertexColorMode : uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- desc: Vertex color mode.
- L17 _public enumerator_ `None UMETA(DisplayName = "No Vertex Color")` — Vertex Color is not set.
- L19 _public enumerator_ `Confidence UMETA(DisplayName = "Vertex Confidence")` — Vertex confidence is interpolated between two specified colors.
- L21 _public enumerator_ `Block UMETA(DisplayName = "Blocks Colored")` — Each block is given a color from a list.

#### class `UMockDataMeshTrackerComponent`  
`class UMockDataMeshTrackerComponent : public USceneComponent`  
_L32-149_
- reflection: `UCLASS(ClassGroup = Rendering, BlueprintType, Blueprintable, EditInlineNew, meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `USceneComponent`
- desc: The MeshTrackerComponent class manages requests for environmental mesh data, processes the results and provides them to the calling system. The calling system is able request environmental mesh data within a specified area. Various other search criteria can be set via this class's public properties.  Mesh data requests are processed on a separate thread.  Once a mesh data request has been processed the calling system will be notified via an FOnMeshTrackerUpdated broadcast.
- L39 _public prototype_ `~UMockDataMeshTrackerComponent();` — Destroys the FMeshTrackerImpl instance.
- L46 _public prototype_ `void ConnectMRMesh(class UMRMeshComponent* InMRMeshPtr);` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")` — Sets the procedural mesh component that will store and display the environmental mesh results. @param InMRMeshPtr The procedural mesh component to store the query result in.
- L53 _public prototype_ `void DisconnectMRMesh(class UMRMeshComponent* InMRMeshPtr);` — `UFUNCTION(BlueprintCallable, Category = "Mesh Reconstruction")` — Unlinks the current procedural mesh component from the mesh tracking system. @param InMRMeshPtr The procedural mesh component to unlink from the mesh tracking system.
- L63 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMockDataMeshTrackerUpdated, int32, Index, const TArray<FVector>&, Vertices, const TArray<int32>&, Triangles, const TArray<FVector>&, Normals, const TArray<float>&, Confidence);` — Delegate used by OnMeshUpdated(). @param Index The index of the mesh section in the ProceduralMeshComponent that was updated. @param Vertices List of all vertices in the updated mesh section. @param Triangles List of all triangles in the updated mesh section. @param Normals List of the normals of all triangles in the updated mesh section. @param Confidence List of the confidence values per vertex in the updated mesh section. This can be used to determine if the user needs to scan more.
- L67 _public member_ `FOnMockDataMeshTrackerUpdated OnMeshTrackerUpdated;` — `UPROPERTY(BlueprintAssignable)` — Activated whenever new information about this mesh tracker is detected.
- L71 _public member_ `bool ScanWorld = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshing")` — Set to true to start scanning the world for meshes.
- L75 _public member_ `bool RequestNormals = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshing")` — If true, the system will generate normals for the triangle vertices.
- L82 _public member_ `bool RequestVertexConfidence = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshing")` — If true, the system will generate the mesh confidence values for the triangle vertices. These confidence values can be used to determine if the user needs to scan more.
- L88 _public member_ `EMeshTrackerVertexColorMode VertexColorMode = EMeshTrackerVertexColorMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshing")` — Vertex Colors can be unused, or filled with several types of information.
- L92 _public member_ `TArray<FColor> BlockVertexColors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshing")` — Colors through which we cycle when setting vertex color by block.
- L96 _public member_ `FLinearColor VertexColorFromConfidenceZero;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshing")` — Color mapped to confidence value of zero.
- L100 _public member_ `FLinearColor VertexColorFromConfidenceOne;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshing")` — Color mapped to confidence value of one.
- L106 _public member_ `float UpdateInterval = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshing|MockData")` — Update Interval in Seconds.
- L112 _public member_ `TObjectPtr<class UMRMeshComponent> MRMesh;` — `UPROPERTY(transient)` — MRMeshComponent can render and provide collision based on the Mesh data.
- L121 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;` — Polls for and handles the results of the environmental mesh queries.
- L124 _public prototype_ `virtual void BeginDestroy() override;` — Unlinks the current procedural mesh component from the mesh tracking system.
- L127 _public prototype_ `virtual void FinishDestroy() override;` — Destroys the interface object to the mesh tracking api
- L130 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;`
- L134 _private member_ `class FMockDataMeshTrackerImpl *Impl;`
- L136 _private member_ `float LastUpdateTime = 0.0f;`
- L137 _private member_ `float CurrentTime = 0.0f;`
- L138 _private member_ `int32 UpdateCount = 0;`
- L139 _private member_ `int32 NumBlocks = 4;`
- L141 _private prototype_ `void UpdateBlock(int32 BlockIndex);`
- L142 _private prototype_ `void RemoveBlock(int32 BlockIndex);`
- L147 _private prototype_ `void PrePIEEnded(bool bWasSimulatingInEditor);`

#### Free symbols / members of external scopes

- L9 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogMockMeshDataTracker, Log, All);`
- L63 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnMockDataMeshTrackerUpdated, int32, Index, const TArray<FVector>&, Vertices, const TArray<int32>&, Triangles, const TArray<FVector>&, Normals, const TArray<float>&, Confidence);` — Delegate used by OnMeshUpdated(). @param Index The index of the mesh section in the ProceduralMeshComponent that was updated. @param Vertices List of all vertices in the updated mesh section. @param Triangles List of all triangles in the updated mesh section. @param Normals List of the normals of all triangles in the updated mesh section. @param Confidence List of the confidence values per vertex in the updated mesh section. This can be used to determine if the user needs to scan more.
