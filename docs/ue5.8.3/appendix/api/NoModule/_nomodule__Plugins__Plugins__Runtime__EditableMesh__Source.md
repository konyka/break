# NoModule / _nomodule__Plugins__Plugins__Runtime__EditableMesh__Source

- module root: `.`
- headers: 3; symbols: 343
- symbol kinds: class=2, delegate=1, enum=5, enumerator=23, function=83, member=106, namespace=1, prototype=90, struct=32

### `Plugins/Runtime/EditableMesh/Source/EditableMesh/EditableGeometryCollectionAdapter.h` (Other)


#### struct `FAdaptorTriangleID`  
`struct FAdaptorTriangleID : public FElementID`  
_L17-42_
- reflection: `USTRUCT()`
- inherits: `FElementID`
- L21 _public function_ `FAdaptorTriangleID()`
- L25 _public function_ `explicit FAdaptorTriangleID( const FElementID InitElementID ) : FElementID( InitElementID.GetValue() )`
- L30 _public function_ `explicit FAdaptorTriangleID( const uint32 InitIDValue ) : FElementID( InitIDValue )`
- L41 _public member_ `static const FAdaptorTriangleID Invalid;` — Invalid triangle ID

#### struct `FAdaptorPolygon`  
`struct FAdaptorPolygon`  
_L46-66_
- reflection: `USTRUCT()`
- L52 _public member_ `FPolygonGroupID PolygonGroupID;` — `UPROPERTY()` — Which rendering polygon group the polygon is in
- L57 _public member_ `TArray<FAdaptorTriangleID> TriangulatedPolygonTriangleIndices;` — `UPROPERTY()` — This is a list of indices of triangles in the FRenderingPolygon2Group2::Triangles array. We use this to maintain a record of which triangles in the section belong to this polygon.

#### struct `FAdaptorPolygon2Group`  
`struct FAdaptorPolygon2Group`  
_L70-99_
- reflection: `USTRUCT()`
- L76 _public member_ `uint32 RenderingSectionIndex=0;` — `UPROPERTY()` — The rendering section index for this mesh section
- L80 _public member_ `int32 MaterialIndex=0;` — `UPROPERTY()` — The material slot index assigned to this polygon group's material
- L84 _public member_ `int32 MaxTriangles=0;` — `UPROPERTY()` — Maximum number of triangles which have been reserved in the index buffer
- L88 _public member_ `TMeshElementArray<FMeshTriangle, FAdaptorTriangleID> Triangles;` — Sparse array of triangles, that matches the triangles in the mesh index buffers.  Elements that aren't allocated will be stored as degenerates in the mesh index buffer.

#### class `UEditableGeometryCollectionAdapter`  
`class UEditableGeometryCollectionAdapter : public UEditableMeshAdapter`  
_L103-200_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditableMeshAdapter`
- L110 _public prototype_ `UEditableGeometryCollectionAdapter();` — Default constructor that initializes good defaults for UEditableGeometryCollectionAdapter
- L112 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;`
- L115 _public prototype_ `void InitEditableGeometryCollection( UEditableMesh* EditableMesh, class UPrimitiveComponent& Component, const FEditableMeshSubMeshAddress& InitSubMeshAddress );` — Creates a editable mesh from the specified component and sub-mesh address
- L116 _public prototype_ `void InitFromBlankGeometryCollection( UEditableMesh* EditableMesh, UGeometryCollection& InGeometryCollection);`
- L118 _public prototype_ `virtual void InitializeFromEditableMesh( const UEditableMesh* EditableMesh ) override;`
- L119 _public prototype_ `virtual void OnRebuildRenderMeshStart( const UEditableMesh* EditableMesh, const bool bInvalidateLighting ) override;`
- L120 _public prototype_ `virtual void OnRebuildRenderMesh( const UEditableMesh* EditableMesh ) override;`
- L121 _public prototype_ `virtual void OnRebuildRenderMeshFinish( const UEditableMesh* EditableMesh, const bool bRebuildBoundsAndCollision, const bool bIsPreviewRollback ) override;`
- L122 _public prototype_ `virtual void OnStartModification( const UEditableMesh* EditableMesh, const EMeshModificationType MeshModificationType, const EMeshTopologyChange MeshTopologyChange ) override;`
- L123 _public prototype_ `virtual void OnEndModification( const UEditableMesh* EditableMesh ) override;`
- L124 _public prototype_ `virtual void OnReindexElements( const UEditableMesh* EditableMesh, const FElementIDRemappings& Remappings ) override;`
- L125 _public prototype_ `virtual bool IsCommitted( const UEditableMesh* EditableMesh ) const override;`
- L126 _public prototype_ `virtual bool IsCommittedAsInstance( const UEditableMesh* EditableMesh ) const override;`
- L127 _public prototype_ `virtual void OnCommit( UEditableMesh* EditableMesh ) override;`
- L128 _public prototype_ `virtual UEditableMesh* OnCommitInstance( UEditableMesh* EditableMesh, UPrimitiveComponent* ComponentToInstanceTo ) override;`
- L129 _public prototype_ `virtual void OnRevert( UEditableMesh* EditableMesh ) override;`
- L130 _public prototype_ `virtual UEditableMesh* OnRevertInstance( UEditableMesh* EditableMesh ) override;`
- L131 _public prototype_ `virtual void OnPropagateInstanceChanges( UEditableMesh* EditableMesh ) override;`
- L133 _public prototype_ `virtual void OnDeleteVertexInstances( const UEditableMesh* EditableMesh, const TArray<FVertexInstanceID>& VertexInstanceIDs ) override;`
- L134 _public prototype_ `virtual void OnDeleteOrphanVertices( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs ) override;`
- L135 _public prototype_ `virtual void OnCreateEmptyVertexRange( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs ) override;`
- L136 _public prototype_ `virtual void OnCreateVertices( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs ) override;`
- L137 _public prototype_ `virtual void OnCreateVertexInstances( const UEditableMesh* EditableMesh, const TArray<FVertexInstanceID>& VertexInstanceIDs ) override;`
- L138 _public prototype_ `virtual void OnSetVertexAttribute( const UEditableMesh* EditableMesh, const FVertexID VertexID, const FMeshElementAttributeData& Attribute ) override;`
- L139 _public prototype_ `virtual void OnSetVertexInstanceAttribute( const UEditableMesh* EditableMesh, const FVertexInstanceID VertexInstanceID, const FMeshElementAttributeData& Attribute ) override;`
- L140 _public prototype_ `virtual void OnCreateEdges( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs ) override;`
- L141 _public prototype_ `virtual void OnDeleteEdges( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs ) override;`
- L142 _public prototype_ `virtual void OnSetEdgesVertices( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs ) override;`
- L143 _public prototype_ `virtual void OnSetEdgeAttribute( const UEditableMesh* EditableMesh, const FEdgeID EdgeID, const FMeshElementAttributeData& Attribute ) override;`
- L144 _public prototype_ `virtual void OnCreatePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs ) override;`
- L145 _public prototype_ `virtual void OnDeletePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs ) override;`
- L146 _public prototype_ `virtual void OnChangePolygonVertexInstances( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs ) override;`
- L147 _public function_ `virtual void OnSetPolygonAttribute( const UEditableMesh* EditableMesh, const FPolygonID PolygonID, const FMeshElementAttributeData& Attribute ) override`
- L148 _public prototype_ `virtual void OnCreatePolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupID>& PolygonGroupIDs ) override;`
- L149 _public prototype_ `virtual void OnDeletePolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupID>& PolygonGroupIDs ) override;`
- L150 _public prototype_ `virtual void OnSetPolygonGroupAttribute( const UEditableMesh* EditableMesh, const FPolygonGroupID PolygonGroupID, const FMeshElementAttributeData& Attribute ) override;`
- L151 _public prototype_ `virtual void OnAssignPolygonsToPolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupForPolygon>& PolygonGroupForPolygons ) override;`
- L152 _public prototype_ `virtual void OnRetriangulatePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs ) override;`
- L155 _public prototype_ `virtual void GeometryHitTest(const FHitParamsIn& InParams, FHitParamsOut& OutParams) override;`
- L162 _private prototype_ `void DeletePolygonTriangles( const UEditableMesh* EditableMesh, const FPolygonID PolygonID );` — Deletes all of a polygon's triangles (including rendering triangles from the index buffer.)
- L165 _private prototype_ `void UpdateBounds( const UEditableMesh* EditableMesh, const bool bShouldRecompute );` — Rebuilds bounds
- L168 _private prototype_ `void UpdateCollision();` — Rebuilds collision.  Bounds should always be updated first.
- L171 _private prototype_ `FPolygonGroupID GetSectionForRenderingSectionIndex( const int32 RenderingSectionIndex ) const;` — Gets the editable mesh section index which corresponds to the given rendering section index
- L177 _private member_ `UGeometryCollection* GeometryCollection;` — `UPROPERTY()` — The Geometry Collection asset we're representing
- L180 _private member_ `UGeometryCollection* OriginalGeometryCollection;` — `UPROPERTY()`
- L183 _private member_ `int32 GeometryCollectionLODIndex;` — `UPROPERTY()`
- L186 _private member_ `TMeshElementArray<FAdaptorPolygon, FPolygonID> RenderingPolygons;` — All of the polygons in this mesh
- L189 _private member_ `TMeshElementArray<FAdaptorPolygon2Group, FPolygonGroupID> RenderingPolygonGroups;` — All of the polygon groups in this mesh
- L192 _private member_ `class UGeometryCollectionComponent* GeometryCollectionComponent;` — The Component this adaptir represents
- L196 _private member_ `FBoxSphereBounds CachedBoundingBoxAndSphere;` — Cached bounding box for the mesh.  This bounds can be (temporarily) larger than the actual mesh itself as an optimization.
- L198 _private prototype_ `void LogGeometryCollectionStats(const FString& SourceString);`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryCollectionAdapter, Verbose, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeometryCollectionAdapter, Verbose, All);`
- L35 _function_ `FORCEINLINE friend uint32 GetTypeHash( const FAdaptorTriangleID& Other )`
- L60 _function_ `friend FArchive& operator<<( FArchive& Ar, FAdaptorPolygon& Polygon )` — Serializer
- L91 _function_ `friend FArchive& operator<<( FArchive& Ar, FAdaptorPolygon2Group& Section )` — Serializer

### `Plugins/Runtime/EditableMesh/Source/EditableMesh/EditableStaticMeshAdapter.h` (Other)


#### struct `FRenderingPolygon`  
`struct FRenderingPolygon`  
_L13-33_
- reflection: `USTRUCT()`
- L19 _public member_ `FPolygonGroupID PolygonGroupID;` — `UPROPERTY()` — Which rendering polygon group the polygon is in
- L24 _public member_ `TArray<FTriangleID> TriangulatedPolygonTriangleIndices;` — `UPROPERTY()` — This is a list of indices of triangles in the FRenderingPolygonGroup::Triangles array. We use this to maintain a record of which triangles in the section belong to this polygon.

#### struct `FRenderingPolygonGroup`  
`struct FRenderingPolygonGroup`  
_L37-79_
- reflection: `USTRUCT()`
- L43 _public member_ `uint32 RenderingSectionIndex=0;` — `UPROPERTY()` — The rendering section index for this mesh section
- L47 _public member_ `int32 MaterialIndex=0;` — `UPROPERTY()` — The material slot index assigned to this polygon group's material
- L51 _public member_ `int32 MaxTriangles=0;` — `UPROPERTY()` — Maximum number of triangles which have been reserved in the index buffer
- L55 _public member_ `TMeshElementArray<FMeshTriangle, FTriangleID> Triangles;` — Sparse array of triangles, that matches the triangles in the mesh index buffers.  Elements that aren't allocated will be stored as degenerates in the mesh index buffer.
- L59 _public function_ `inline static FTriangleID RenderingTriangleFirstIndexToTriangleIndex( const FStaticMeshSection& RenderingSection, const uint32 RenderingTriangleFirstIndex )` — Converts from an index in our Triangles array to an index of a rendering triangle's first vertex in the rendering mesh's index buffer
- L65 _public function_ `inline static uint32 TriangleIndexToRenderingTriangleFirstIndex( const FStaticMeshSection& RenderingSection, const FTriangleID TriangleIndex )` — Converts from an index of a rendering triangle's first vertex in the rendering mesh's index buffer to an index in our Triangles array

#### class `UEditableStaticMeshAdapter`  
`class UEditableStaticMeshAdapter : public UEditableMeshAdapter`  
_L85-199_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditableMeshAdapter`
- L92 _public prototype_ `UEditableStaticMeshAdapter();` — Default constructor that initializes good defaults for UEditableStaticMeshAdapter
- L94 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;`
- L97 _public prototype_ `void InitEditableStaticMesh( UEditableMesh* EditableMesh, class UPrimitiveComponent& Component, const FEditableMeshSubMeshAddress& InitSubMeshAddress );` — Creates a editable static mesh from the specified component and sub-mesh address
- L98 _public prototype_ `void InitFromBlankStaticMesh( UEditableMesh* EditableMesh, UStaticMesh& InStaticMesh );`
- L100 _public prototype_ `virtual void InitializeFromEditableMesh( const UEditableMesh* EditableMesh ) override;`
- L101 _public prototype_ `virtual void OnRebuildRenderMeshStart( const UEditableMesh* EditableMesh, const bool bInvalidateLighting ) override;`
- L102 _public prototype_ `virtual void OnRebuildRenderMesh( const UEditableMesh* EditableMesh ) override;`
- L103 _public prototype_ `virtual void OnRebuildRenderMeshFinish( const UEditableMesh* EditableMesh, const bool bRebuildBoundsAndCollision, const bool bIsPreviewRollback ) override;`
- L104 _public prototype_ `virtual void OnStartModification( const UEditableMesh* EditableMesh, const EMeshModificationType MeshModificationType, const EMeshTopologyChange MeshTopologyChange ) override;`
- L105 _public prototype_ `virtual void OnEndModification( const UEditableMesh* EditableMesh ) override;`
- L106 _public prototype_ `virtual void OnReindexElements( const UEditableMesh* EditableMesh, const FElementIDRemappings& Remappings ) override;`
- L107 _public prototype_ `virtual bool IsCommitted( const UEditableMesh* EditableMesh ) const override;`
- L108 _public prototype_ `virtual bool IsCommittedAsInstance( const UEditableMesh* EditableMesh ) const override;`
- L109 _public prototype_ `virtual void OnCommit( UEditableMesh* EditableMesh ) override;`
- L110 _public prototype_ `virtual UEditableMesh* OnCommitInstance( UEditableMesh* EditableMesh, UPrimitiveComponent* ComponentToInstanceTo ) override;`
- L111 _public prototype_ `virtual void OnRevert( UEditableMesh* EditableMesh ) override;`
- L112 _public prototype_ `virtual UEditableMesh* OnRevertInstance( UEditableMesh* EditableMesh ) override;`
- L113 _public prototype_ `virtual void OnPropagateInstanceChanges( UEditableMesh* EditableMesh ) override;`
- L115 _public prototype_ `virtual void OnDeleteVertexInstances( const UEditableMesh* EditableMesh, const TArray<FVertexInstanceID>& VertexInstanceIDs ) override;`
- L116 _public prototype_ `virtual void OnDeleteOrphanVertices( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs ) override;`
- L117 _public prototype_ `virtual void OnCreateEmptyVertexRange( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs ) override;`
- L118 _public prototype_ `virtual void OnCreateVertices( const UEditableMesh* EditableMesh, const TArray<FVertexID>& VertexIDs ) override;`
- L119 _public prototype_ `virtual void OnCreateVertexInstances( const UEditableMesh* EditableMesh, const TArray<FVertexInstanceID>& VertexInstanceIDs ) override;`
- L120 _public prototype_ `virtual void OnSetVertexAttribute( const UEditableMesh* EditableMesh, const FVertexID VertexID, const FMeshElementAttributeData& Attribute ) override;`
- L121 _public prototype_ `virtual void OnSetVertexInstanceAttribute( const UEditableMesh* EditableMesh, const FVertexInstanceID VertexInstanceID, const FMeshElementAttributeData& Attribute ) override;`
- L122 _public prototype_ `virtual void OnCreateEdges( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs ) override;`
- L123 _public prototype_ `virtual void OnDeleteEdges( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs ) override;`
- L124 _public prototype_ `virtual void OnSetEdgesVertices( const UEditableMesh* EditableMesh, const TArray<FEdgeID>& EdgeIDs ) override;`
- L125 _public prototype_ `virtual void OnSetEdgeAttribute( const UEditableMesh* EditableMesh, const FEdgeID EdgeID, const FMeshElementAttributeData& Attribute ) override;`
- L126 _public prototype_ `virtual void OnCreatePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs ) override;`
- L127 _public prototype_ `virtual void OnDeletePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs ) override;`
- L128 _public prototype_ `virtual void OnChangePolygonVertexInstances( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs ) override;`
- L129 _public function_ `virtual void OnSetPolygonAttribute( const UEditableMesh* EditableMesh, const FPolygonID PolygonID, const FMeshElementAttributeData& Attribute ) override`
- L130 _public prototype_ `virtual void OnCreatePolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupID>& PolygonGroupIDs ) override;`
- L131 _public prototype_ `virtual void OnDeletePolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupID>& PolygonGroupIDs ) override;`
- L132 _public prototype_ `virtual void OnSetPolygonGroupAttribute( const UEditableMesh* EditableMesh, const FPolygonGroupID PolygonGroupID, const FMeshElementAttributeData& Attribute ) override;`
- L133 _public prototype_ `virtual void OnAssignPolygonsToPolygonGroups( const UEditableMesh* EditableMesh, const TArray<FPolygonGroupForPolygon>& PolygonGroupForPolygons ) override;`
- L134 _public prototype_ `virtual void OnRetriangulatePolygons( const UEditableMesh* EditableMesh, const TArray<FPolygonID>& PolygonIDs ) override;`
- L137 _public prototype_ `virtual void GeometryHitTest(const FHitParamsIn& InParams, FHitParamsOut& OutParams) override;`
- L140 _public function_ `void SetRecreateSimpleCollision(bool bInRecreateSimplifiedCollision)`
- L141 _public function_ `bool GetRecreateSimpleCollision() const`
- L147 _private prototype_ `void DeletePolygonTriangles( const UEditableMesh* EditableMesh, const FPolygonID PolygonID );` — Deletes all of a polygon's triangles (including rendering triangles from the index buffer.)
- L150 _private prototype_ `const struct FStaticMeshLODResources& GetStaticMeshLOD() const;` — Helper function to get a specific static mesh LOD structure for a mesh
- L151 _private prototype_ `struct FStaticMeshLODResources& GetStaticMeshLOD();`
- L154 _private prototype_ `void EnsureIndexBufferIs32Bit();` — Makes sure our mesh's index buffer is 32-bit, converting if needed
- L157 _private prototype_ `void UpdateBounds( const UEditableMesh* EditableMesh, const bool bShouldRecompute );` — Rebuilds bounds
- L160 _private prototype_ `void UpdateCollision();` — Rebuilds collision.  Bounds should always be updated first.
- L163 _private prototype_ `FPolygonGroupID GetSectionForRenderingSectionIndex( const int32 RenderingSectionIndex ) const;` — Gets the editable mesh section index which corresponds to the given rendering section index
- L169 _private member_ `UStaticMesh* StaticMesh;` — `UPROPERTY()` — The static mesh asset we're representing
- L172 _private member_ `UStaticMesh* OriginalStaticMesh;` — `UPROPERTY()`
- L175 _private member_ `int32 StaticMeshLODIndex;` — `UPROPERTY()`
- L179 _private member_ `static const uint32 IndexBufferInterSectionGap = 32;` — Size of the extra gaps in the index buffer between different sections (so new triangles have some space to be added into, without requiring the index buffer to be manipulated)
- L182 _private member_ `TMeshElementArray<FRenderingPolygon, FPolygonID> RenderingPolygons;` — All of the polygons in this mesh
- L185 _private member_ `TMeshElementArray<FRenderingPolygonGroup, FPolygonGroupID> RenderingPolygonGroups;` — All of the polygon groups in this mesh
- L188 _private member_ `TSharedPtr<class FStaticMeshComponentRecreateRenderStateContext> RecreateRenderStateContext;` — Used to refresh all components in the scene that may be using a mesh we're editing
- L192 _private member_ `FBoxSphereBounds CachedBoundingBoxAndSphere;` — Cached bounding box for the static mesh.  This bounds can be (temporarily) larger than the actual mesh itself as an optimization.
- L195 _private member_ `bool bUpdateCollisionNeeded;` — Flag to indicate if a modification requires regenerating collision
- L198 _private member_ `bool bRecreateSimplifiedCollision;` — Flag to indicate if the simple collision has to be regenerated

#### Free symbols / members of external scopes

- L27 _function_ `friend FArchive& operator<<( FArchive& Ar, FRenderingPolygon& Polygon )` — Serializer
- L71 _function_ `friend FArchive& operator<<( FArchive& Ar, FRenderingPolygonGroup& Section )` — Serializer

### `Plugins/Runtime/EditableMesh/Source/EditableMesh/Public/EditableMeshTypes.h` (Other)


#### enum `EEditableMeshElementType`  
`enum class EEditableMeshElementType`  
_L85-104_
- desc: The different components that make up a typical mesh
- L88 _public enumerator_ `Invalid` — Invalid mesh element (or "none")
- L91 _public enumerator_ `Vertex` — A unique point in 3D space
- L94 _public enumerator_ `Edge` — An edge that connects two vertices
- L97 _public enumerator_ `Polygon` — A polygon with at least three 3D points.  It could be triangle, quad, or more complex shape
- L100 _public enumerator_ `Fracture` — Mesh Fracturing Mode
- L103 _public enumerator_ `Any` — Represents any element type

#### struct `FEditableMeshSubMeshAddress`  
`struct FEditableMeshSubMeshAddress`  
_L110-162_
- desc: Unique identifies a specific sub-mesh within a component
- L113 _public member_ `void* MeshObjectPtr;` — Pointer that uniquely identifies the mesh object being edited (not the instance), for hashing/comparison purposes
- L117 _public member_ `class IEditableMeshFormat* EditableMeshFormat;` — @todo mesheditor: Should SHOULD be OK, but if it somehow was deallocated while we were using it, we'd want to store an FName or ID here instead of a pointer.  Should be fine though.
- L120 _public member_ `int32 MeshIndex;` — The index of the mesh within the component, for components that may define more than one mesh
- L123 _public member_ `int32 LODIndex;` — The mesh level of detail index, or zero if not applicable to the type of mesh.
- L127 _public function_ `FEditableMeshSubMeshAddress() : MeshObjectPtr( nullptr ), EditableMeshFormat( nullptr ), MeshIndex( 0 ), LODIndex( 0 )` — Default constructor that initializes variables to an default sub-mesh address
- L136 _public function_ `inline bool operator==( const FEditableMeshSubMeshAddress& Other ) const` — Equality check
- L153 _public function_ `inline FString ToString() const` — Convert to a string

#### enum `EMeshModificationType`  
`enum class EMeshModificationType : uint8`  
_L166-176_
- reflection: `UENUM()`
- L169 _public enumerator_ `FirstInterim` — The first Interim change since the last Final change.  This must be followed by either an Interim change or a Final change
- L172 _public enumerator_ `Interim` — User is still in the middle of their interaction.  More changes to come, so don't bother finalizing everything yet (smoother performance)
- L175 _public enumerator_ `Final` — User has finished their current interaction with this mesh, and everything needs to be finalized at this time

#### enum `EMeshTopologyChange`  
`enum class EMeshTopologyChange : uint8`  
_L180-187_
- reflection: `UENUM()`
- L183 _public enumerator_ `NoTopologyChange` — We won't be changing the mesh topology, but values could be changed (vertex positions, UVs, colors, etc.)
- L186 _public enumerator_ `TopologyChange` — Topology is changing with this edit, potentially along with other changes

#### struct `FSubdividedQuadVertex`  
`struct FSubdividedQuadVertex`  
_L192-214_
- reflection: `USTRUCT(BlueprintType)`
- L197 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) int32 VertexPos` — The index of the vertex position (into the FSubdivisionLimitData's VertexPositions array) used for this vertex
- L200 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) FVector2D TextureCoordinate0= FVector2D` — Texture coordinates for this vertex.  We only support up to two, for now. (Just to avoid TArrays/allocations)
- L201 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) FVector2D TextureCoordinate1 = FVector2D` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Texture coordinates for this vertex.  We only support up to two, for now. (Just to avoid TArrays/allocations)
- L204 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) FColor VertexColor = F` — Vertex color
- L207 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) FVector VertexNormal =FVector:` — Quad vertex normal
- L210 _public member_ `UPROPERTY(BlueprintReadWrite, Category = "Editable Mesh") FVector VertexTangent=FVector:` — Quad vertex tangent
- L213 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) float VertexBinor` — Quad vertex binormal sign (-1.0 or 1.0)

#### struct `FSubdividedQuad`  
`struct FSubdividedQuad`  
_L218-267_
- reflection: `USTRUCT(BlueprintType)`
- L225 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) FSubdividedQuadVertex` — The vertices for the four corners of this quad
- L226 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) FSubdividedQuadVertex` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertices for the four corners of this quad
- L227 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) FSubdividedQuadVertex` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertices for the four corners of this quad
- L228 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) FSubdividedQuadVertex` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertices for the four corners of this quad
- L230 _public function_ `const FSubdividedQuadVertex& GetQuadVertex( const int32 Index ) const`
- L249 _public function_ `FSubdividedQuadVertex& AccessQuadVertex( const int32 Index )`

#### struct `FSubdividedWireEdge`  
`struct FSubdividedWireEdge`  
_L271-284_
- reflection: `USTRUCT(BlueprintType)`
- L278 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) int32 EdgeVertex0Pos` — The vertex indices for the two corners of this quad
- L279 _public member_ `UPROPERTY( BlueprintReadWrite, Category="Editable Mesh" ) int32 EdgeVertex1Pos` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertex indices for the two corners of this quad
- L283 _public member_ `FEdgeID CounterpartEdgeID;` — True if this edge is a counterpart to an original base cage edge of the mesh.  Otherwise it's a new edge that exists only in the subdivision surfaces

#### struct `FSubdivisionLimitSection`  
`struct FSubdivisionLimitSection`  
_L288-295_
- reflection: `USTRUCT(BlueprintType)`
- L294 _public member_ `TArray<FSubdividedQuad> SubdividedQuads;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — All of the quads in this section, as a result from subdividing the mesh

#### struct `FSubdivisionLimitData`  
`struct FSubdivisionLimitData`  
_L299-315_
- reflection: `USTRUCT(BlueprintType)`
- L305 _public member_ `TArray<FVector> VertexPositions;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Positions of all of the vertices for this subdivision level.  Many vertex positions may be shared between subdivided quads.
- L310 _public member_ `TArray<FSubdivisionLimitSection> Sections;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Data for each of the sections in the mesh.  This array will have the same number of elements as the editable mesh's section list (not necessarily the same indices though, due to sparseness).
- L314 _public member_ `TArray<FSubdividedWireEdge> SubdividedWireEdges;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — All of the wire edges in the entire mesh (for all sections)

#### enum `EMeshElementAttributeType`  
`enum class EMeshElementAttributeType : uint8`  
_L319-329_
- reflection: `UENUM()`
- L321 _public enumerator_ `None`
- L322 _public enumerator_ `FVector4`
- L323 _public enumerator_ `FVector`
- L324 _public enumerator_ `FVector2D`
- L325 _public enumerator_ `Float`
- L326 _public enumerator_ `Int`
- L327 _public enumerator_ `Bool`
- L328 _public enumerator_ `FName`

#### struct `FMeshElementAttributeValue`  
`struct FMeshElementAttributeValue`  
_L333-455_
- reflection: `USTRUCT(BlueprintType)`
- L341 _public function_ `FMeshElementAttributeValue() : Type( EMeshElementAttributeType::None )` — Define constructors
- L342 _public function_ `explicit FMeshElementAttributeValue( const FVector4& Value ) : Type( EMeshElementAttributeType::FVector4 ), Value_FVector4( Value )`
- L343 _public function_ `explicit FMeshElementAttributeValue( const FVector Value ) : Type( EMeshElementAttributeType::FVector ), Value_FVector( Value )`
- L344 _public function_ `explicit FMeshElementAttributeValue( const FVector2D Value ) : Type( EMeshElementAttributeType::FVector2D ), Value_FVector2D( Value )`
- L345 _public function_ `explicit FMeshElementAttributeValue( const float Value ) : Type( EMeshElementAttributeType::Float ), Value_Float( Value )`
- L346 _public function_ `explicit FMeshElementAttributeValue( const int Value ) : Type( EMeshElementAttributeType::Int ), Value_Int( Value )`
- L347 _public function_ `explicit FMeshElementAttributeValue( const bool Value ) : Type( EMeshElementAttributeType::Bool ), Value_Bool( Value )`
- L348 _public function_ `explicit FMeshElementAttributeValue( const FName Value ) : Type( EMeshElementAttributeType::FName ), Value_FName( Value )`
- L351 _public function_ `EMeshElementAttributeType GetType() const` — Returns the type of this attribute value
- L357 _public prototype_ `template <typename T> T GetValue() const;` — Accessors for known types. There will be a runtime error if the attribute value is not of the specified type.
- L366 _public function_ `template <typename FuncType> void Visit( const FuncType& Func ) const` — Calls the specified polymorphic lambda, with this attribute value as its passed-in parameter. For example: AttributeValue.Visit( []( const auto& Value ) { DoSomethingWith( Value ); } );
- L381 _public function_ `FString ToString() const` — Returns the attribute value as a string
- L447 _private member_ `EMeshElementAttributeType Type;`
- L448 _private member_ `FVector4 Value_FVector4;`
- L449 _private member_ `FVector Value_FVector;`
- L450 _private member_ `FVector2D Value_FVector2D;`
- L451 _private member_ `float Value_Float;`
- L452 _private member_ `int Value_Int;`
- L453 _private member_ `bool Value_Bool;`
- L454 _private member_ `FName Value_FName;`
- L458 _function_ `template <> inline FVector4 FMeshElementAttributeValue::GetValue<FVector4>() const` — Implementations of accessors for known types. These must be defined outside the class definition.
- L462 _function_ `template <> inline FVector FMeshElementAttributeValue::GetValue<FVector>() const`
- L463 _function_ `template <> inline FVector2D FMeshElementAttributeValue::GetValue<FVector2D>() const`
- L464 _function_ `template <> inline float FMeshElementAttributeValue::GetValue<float>() const`

#### struct `FMeshElementAttributeData`  
`struct FMeshElementAttributeData`  
_L469-507_
- reflection: `USTRUCT(BlueprintType)`
- L475 _public member_ `FName AttributeName;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Name of the attribute
- L479 _public member_ `int32 AttributeIndex;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Index of the attribute
- L483 _public member_ `FMeshElementAttributeValue AttributeValue;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The value of this attribute
- L486 _public function_ `FMeshElementAttributeData() : AttributeName( NAME_None ), AttributeIndex( 0 ), AttributeValue()` — Default constructor
- L493 _public function_ `FMeshElementAttributeData( const FName InitAttributeName, const int32 InitAttributeIndex, const FMeshElementAttributeValue& InitAttributeValue ) : AttributeName( InitAttributeName ), AttributeIndex( InitAttributeIndex ), AttributeValue( InitAttributeValue )` — Constructor that fills in all fields
- L499 _public function_ `FString ToString() const`

#### struct `FMeshElementAttributeList`  
`struct FMeshElementAttributeList`  
_L511-531_
- reflection: `USTRUCT(BlueprintType)`
- L517 _public member_ `TArray<FMeshElementAttributeData> Attributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — List of attributes to apply to a mesh element
- L520 _public function_ `FMeshElementAttributeList() : Attributes()` — Default constructor
- L525 _public function_ `FString ToString() const`

#### struct `FVertexToCreate`  
`struct FVertexToCreate`  
_L535-560_
- reflection: `USTRUCT(BlueprintType)`
- L541 _public member_ `FMeshElementAttributeList VertexAttributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Attributes of this vertex itself
- L545 _public member_ `FVertexID OriginalVertexID;` — `UPROPERTY()` — The original ID of the vertex.  Should only be used by the undo system.
- L547 _public function_ `FVertexToCreate() : VertexAttributes(), OriginalVertexID( FVertexID::Invalid )`
- L553 _public function_ `FString ToString() const`

#### struct `FVertexInstanceToCreate`  
`struct FVertexInstanceToCreate`  
_L564-595_
- reflection: `USTRUCT(BlueprintType)`
- L570 _public member_ `FVertexID VertexID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Vertex ID which is being instanced
- L574 _public member_ `FMeshElementAttributeList VertexInstanceAttributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Attributes of this vertex instance
- L578 _public member_ `FVertexInstanceID OriginalVertexInstanceID;` — `UPROPERTY()` — The original ID of the vertex instance.  Should only be used by the undo system.
- L580 _public function_ `FVertexInstanceToCreate() : VertexID( FVertexID::Invalid ), VertexInstanceAttributes(), OriginalVertexInstanceID( FVertexInstanceID::Invalid )`
- L587 _public function_ `FString ToString() const`

#### struct `FEdgeToCreate`  
`struct FEdgeToCreate`  
_L599-643_
- reflection: `USTRUCT(BlueprintType)`
- L605 _public member_ `FVertexID VertexID0;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The first vertex this edge connects
- L609 _public member_ `FVertexID VertexID1;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The second vertex this edge connects
- L617 _public member_ `FMeshElementAttributeList EdgeAttributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Attributes of this edge itself
- L621 _public member_ `FEdgeID OriginalEdgeID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The original ID of the edge.  Should only be used by the undo system.
- L624 _public function_ `FEdgeToCreate() : VertexID0( FVertexID::Invalid ), VertexID1( FVertexID::Invalid ),` — Default constructor
- L633 _public function_ `FString ToString() const`

#### struct `FVertexAndAttributes`  
`struct FVertexAndAttributes`  
_L648-680_
- reflection: `USTRUCT(BlueprintType)`
- L654 _public member_ `FVertexInstanceID VertexInstanceID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertex instance ID to insert into the polygon, or FVertexInstanceID::Invalid to create a new vertex instance with the given attributes
- L658 _public member_ `FVertexID VertexID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertex ID to insert into the polygon, if no valid vertex instance ID was supplied.
- L662 _public member_ `FMeshElementAttributeList PolygonVertexAttributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — A list of polygon attributes to set for the vertex on the polygon we're inserting it into, if no valid vertex instance ID was supplied.
- L665 _public function_ `FVertexAndAttributes() : VertexInstanceID( FVertexInstanceID::Invalid ), VertexID( FVertexID::Invalid ), PolygonVertexAttributes()` — Default constructor
- L672 _public function_ `FString ToString() const`

#### enum `EPolygonEdgeHardness`  
`enum class EPolygonEdgeHardness : uint8`  
_L684-697_
- reflection: `UENUM(BlueprintType)`
- L687 _public enumerator_ `NewEdgesSoft` — Create any new edges required by the polygon as soft, leaving existing edges as they are
- L690 _public enumerator_ `NewEdgesHard` — Create any new edges required by the polygon as hard, leaving existing edges as they are
- L693 _public enumerator_ `AllEdgesSoft` — Set all edges as soft, overriding edge hardness on existing edges
- L696 _public enumerator_ `AllEdgesHard` — Set all edges as hard, overriding edge hardness on existing edges

#### struct `FPolygonToCreate`  
`struct FPolygonToCreate`  
_L701-738_
- reflection: `USTRUCT(BlueprintType)`
- L707 _public member_ `FPolygonGroupID PolygonGroupID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The group the polygon will be added to
- L711 _public member_ `TArray<FVertexAndAttributes> PerimeterVertices;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Ordered list of vertices that defines the polygon's perimeter, along with the polygon vertex attributes to set for each vertex
- L715 _public member_ `FPolygonID OriginalPolygonID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The original ID of the polygon.  Should only be used by the undo system.
- L719 _public member_ `EPolygonEdgeHardness PolygonEdgeHardness;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Whether to create a hard-edged polygon
- L722 _public function_ `FPolygonToCreate() : PolygonGroupID( FPolygonGroupID::Invalid ), PerimeterVertices(), OriginalPolygonID( FPolygonID::Invalid ), PolygonEdgeHardness( EPolygonEdgeHardness::NewEdgesSoft )` — Default constructor
- L730 _public function_ `FString ToString() const`

#### struct `FVertexPair`  
`struct FVertexPair`  
_L743-769_
- reflection: `USTRUCT(BlueprintType)`
- L749 _public member_ `FVertexID VertexID0;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The first vertex ID in this pair
- L753 _public member_ `FVertexID VertexID1;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The second vertex ID in this pair
- L756 _public function_ `FVertexPair() : VertexID0( FVertexID::Invalid ), VertexID1( FVertexID::Invalid )` — Default constructor
- L762 _public function_ `FString ToString() const`

#### struct `FPolygonToSplit`  
`struct FPolygonToSplit`  
_L773-800_
- reflection: `USTRUCT(BlueprintType)`
- L779 _public member_ `FPolygonID PolygonID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The polygon that we'll be splitting
- L784 _public member_ `TArray<FVertexPair> VertexPairsToSplitAt;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — A list of pairs of vertices that new edges will be created at.  The pairs must be ordered, and the vertices must already exist and be connected to the polygon
- L787 _public function_ `FPolygonToSplit() : PolygonID( FPolygonID::Invalid ), VertexPairsToSplitAt()` — Default constructor
- L793 _public function_ `FString ToString() const`

#### struct `FAttributesForVertex`  
`struct FAttributesForVertex`  
_L804-830_
- reflection: `USTRUCT(BlueprintType)`
- L810 _public member_ `FVertexID VertexID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertex ID to set attributes on
- L814 _public member_ `FMeshElementAttributeList VertexAttributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — A list of attributes to set for the vertex
- L817 _public function_ `FAttributesForVertex() : VertexID( 0 ), VertexAttributes()` — Default constructor
- L823 _public function_ `FString ToString() const`

#### struct `FAttributesForVertexInstance`  
`struct FAttributesForVertexInstance`  
_L834-860_
- reflection: `USTRUCT(BlueprintType)`
- L840 _public member_ `FVertexInstanceID VertexInstanceID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertex instance ID to set attributes on
- L844 _public member_ `FMeshElementAttributeList VertexInstanceAttributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — A list of attributes to set for the vertex instance
- L847 _public function_ `FAttributesForVertexInstance() : VertexInstanceID( 0 ), VertexInstanceAttributes()` — Default constructor
- L853 _public function_ `FString ToString() const`

#### struct `FAttributesForEdge`  
`struct FAttributesForEdge`  
_L864-890_
- reflection: `USTRUCT(BlueprintType)`
- L870 _public member_ `FEdgeID EdgeID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The edge ID to set attributes on
- L874 _public member_ `FMeshElementAttributeList EdgeAttributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — A list of attributes to set for the edge
- L877 _public function_ `FAttributesForEdge() : EdgeID( 0 ), EdgeAttributes()` — Default constructor
- L883 _public function_ `FString ToString() const`

#### struct `FVertexAttributesForPolygonHole`  
`struct FVertexAttributesForPolygonHole`  
_L894-915_
- reflection: `USTRUCT(BlueprintType)`
- L901 _public member_ `TArray<FMeshElementAttributeList> VertexAttributeList;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — For each hole vertex, a list of attributes for that vertex.  You can leave a given array empty for a specific hole index if you don't want to set attributes for select holes.
- L904 _public function_ `FVertexAttributesForPolygonHole() : VertexAttributeList()` — Default constructor
- L909 _public function_ `FString ToString() const`

#### struct `FVertexAttributesForPolygon`  
`struct FVertexAttributesForPolygon`  
_L919-952_
- reflection: `USTRUCT(BlueprintType)`
- L925 _public member_ `FPolygonID PolygonID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The polygon to set vertex attributes on
- L929 _public member_ `TArray<FMeshElementAttributeList> PerimeterVertexAttributeLists;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — For each polygon vertex, a list of attributes for that vertex.  Can be left empty if you don't want to set any attributes.
- L934 _public member_ `TArray<FVertexAttributesForPolygonHole> VertexAttributeListsForEachHole;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — For each hole vertex, a list of attributes for that vertex.  Can be left empty if you don't want to set any attributes.  Also you can leave a given array empty for a specific hole index if you don't want to set attributes for select holes.
- L937 _public function_ `FVertexAttributesForPolygon() : PolygonID( FPolygonID::Invalid ), PerimeterVertexAttributeLists(), VertexAttributeListsForEachHole()` — Default constructor
- L944 _public function_ `FString ToString() const`

#### struct `FVertexIndexAndInstanceID`  
`struct FVertexIndexAndInstanceID`  
_L956-975_
- reflection: `USTRUCT(BlueprintType)`
- L962 _public member_ `int32 ContourIndex=0;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Contour index of the vertex to change
- L966 _public member_ `FVertexInstanceID VertexInstanceID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — New vertex instance ID to assign
- L968 _public function_ `FString ToString() const`

#### struct `FVertexInstancesForPolygonHole`  
`struct FVertexInstancesForPolygonHole`  
_L979-999_
- reflection: `USTRUCT(BlueprintType)`
- L985 _public member_ `TArray<FVertexIndexAndInstanceID> VertexIndicesAndInstanceIDs;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — A list of vertex instance IDs for a polygon hole.
- L988 _public function_ `FVertexInstancesForPolygonHole() : VertexIndicesAndInstanceIDs()` — Default constructor
- L993 _public function_ `FString ToString() const`

#### struct `FChangeVertexInstancesForPolygon`  
`struct FChangeVertexInstancesForPolygon`  
_L1003-1035_
- reflection: `USTRUCT(BlueprintType)`
- L1009 _public member_ `FPolygonID PolygonID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The polygon to set vertex instances on
- L1013 _public member_ `TArray<FVertexIndexAndInstanceID> PerimeterVertexIndicesAndInstanceIDs;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — A list of vertex numbers and vertex instance IDs to change for the polygon perimeter.
- L1017 _public member_ `TArray<FVertexInstancesForPolygonHole> VertexIndicesAndInstanceIDsForEachHole;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — A list of vertex instance IDs for each hole.
- L1020 _public function_ `FChangeVertexInstancesForPolygon() : PolygonID( FPolygonID::Invalid ), PerimeterVertexIndicesAndInstanceIDs(), VertexIndicesAndInstanceIDsForEachHole()` — Default constructor
- L1027 _public function_ `FString ToString() const`

#### struct `FVertexToMove`  
`struct FVertexToMove`  
_L1077-1103_
- reflection: `USTRUCT(BlueprintType)`
- L1083 _public member_ `FVertexID VertexID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The vertex we'll be moving around
- L1087 _public member_ `FVector NewVertexPosition;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The new position of the vertex
- L1090 _public function_ `FVertexToMove() : VertexID( FVertexID::Invalid ), NewVertexPosition( FVector::ZeroVector )`
- L1096 _public function_ `FString ToString() const`

#### struct `FPolygonGroupToCreate`  
`struct FPolygonGroupToCreate`  
_L1107-1132_
- reflection: `USTRUCT(BlueprintType)`
- L1113 _public member_ `FMeshElementAttributeList PolygonGroupAttributes;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Attributes of this polygon group
- L1117 _public member_ `FPolygonGroupID OriginalPolygonGroupID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — The original ID of the polygon group.  Should only be used by the undo system.
- L1120 _public function_ `FPolygonGroupToCreate() : OriginalPolygonGroupID( FPolygonGroupID::Invalid )` — Default constructor
- L1125 _public function_ `FString ToString() const`

#### struct `FPolygonGroupForPolygon`  
`struct FPolygonGroupForPolygon`  
_L1136-1162_
- reflection: `USTRUCT(BlueprintType)`
- L1142 _public member_ `FPolygonID PolygonID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Polygon to assign to a new group
- L1146 _public member_ `FPolygonGroupID PolygonGroupID;` — `UPROPERTY(BlueprintReadWrite, Category="Editable Mesh")` — Polygon group to assign polygon to
- L1149 _public function_ `FPolygonGroupForPolygon() : PolygonID( FPolygonID::Invalid ) , PolygonGroupID( FPolygonGroupID::Invalid )` — Default constructor
- L1155 _public function_ `FString ToString() const`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace LogHelpers`
- L18 _function_ `template <typename ElementType, typename TEnableIf<!TIsArithmetic<ElementType>::Value, int>::Type = 0> inline FString ElementToString( const ElementType& Element )` (scope `LogHelpers`)
- L24 _function_ `template <typename ElementType, typename TEnableIf<TIsArithmetic<ElementType>::Value, int>::Type = 0> inline FString ElementToString( const ElementType& Element )` (scope `LogHelpers`)
- L30 _function_ `template <typename ArrayType> inline FString ArrayToString( const TArray<ArrayType>& Array )` (scope `LogHelpers`)
- L53 _function_ `template<typename ArrayType> inline FString ArrayToString( const TArray<TArray<ArrayType>>& Array )` (scope `LogHelpers`)
- L75 _function_ `inline FString BoolToString( const bool Bool )` (scope `LogHelpers`)
- L146 _function_ `FORCEINLINE friend uint32 GetTypeHash( const FEditableMeshSubMeshAddress& Other )` — Hashing
- L399 _function_ `friend FArchive& operator<<( FArchive& Ar, FMeshElementAttributeValue& AttributeValue )` — Serializer
- L418 _function_ `friend bool operator==( const FMeshElementAttributeValue& Value1, const FMeshElementAttributeValue& Value2 )` — Test equality of two attribute values
- L440 _function_ `friend bool operator!=( const FMeshElementAttributeValue& Value1, const FMeshElementAttributeValue& Value2 )`
