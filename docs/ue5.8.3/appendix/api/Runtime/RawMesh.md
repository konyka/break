# Runtime / RawMesh

- module root: `Source/Runtime/RawMesh`
- headers: 1; symbols: 34
- symbol kinds: class=1, enum=1, enumerator=1, function=3, member=14, prototype=13, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/RawMesh/Public/RawMesh.h` (Public)


#### enum `(anonymous)`  
``  
_L21-23_

#### struct `FRawMesh`  
`struct FRawMesh`  
_L38-99_
- desc: Raw mesh data used to construct optimized runtime rendering streams. A note on terminology. Information is stored at various frequencies as defined here: Face - A single polygon in the mesh. Currently all code assumes this is a triangle but conceptually any polygon would do. Corner - Each face has N corners. As all faces are currently triangles, N=3. Wedge - Properties stored for each corner of each face. Index with FaceIndex * NumCorners + CornerIndex. Vertex - Properties shared by overlapping wedges of adjacent polygons. Typically these properties relate to position. Index with VertexIndices[WedgeIndex]. Additionally, to ease in backwards compatibility all properties should use only primitive types!
- L41 _public member_ `TArray<int32> FaceMaterialIndices;` — Material index. Array[FaceId] = int32
- L43 _public member_ `TArray<uint32> FaceSmoothingMasks;` — Smoothing mask. Array[FaceId] = uint32
- L46 _public member_ `TArray<FVector3f> VertexPositions;` — Position in local space. Array[VertexId] = float3(x,y,z)
- L49 _public member_ `TArray<uint32> WedgeIndices;` — Index of the vertex at this wedge. Array[WedgeId] = VertexId
- L51 _public member_ `TArray<FVector3f> WedgeTangentX;` — Tangent, U direction. Array[WedgeId] = float3(x,y,z)
- L53 _public member_ `TArray<FVector3f> WedgeTangentY;` — Tangent, V direction. Array[WedgeId] = float3(x,y,z)
- L55 _public member_ `TArray<FVector3f> WedgeTangentZ;` — Normal. Array[WedgeId] = float3(x,y,z)
- L57 _public member_ `TArray<FVector2f> WedgeTexCoords[MAX_MESH_TEXTURE_COORDS];` — Texture coordinates. Array[UVId][WedgeId]=float2(u,v)
- L59 _public member_ `TArray<FColor> WedgeColors;` — Color. Array[WedgeId]=float3(r,g,b,a)
- L66 _public member_ `TArray<int32> MaterialIndexToImportIndex;` — Map from material index -> original material index at import time. It's valid for this to be empty in which case material index == original material index.
- L69 _public prototype_ `void Empty();` — Empties all data streams.
- L77 _public prototype_ `bool IsValid() const;` — Returns true if the mesh contains valid information. - Validates that stream sizes match. - Validates that there is at least one texture coordinate. - Validates that indices are valid positions in the vertex stream.
- L85 _public prototype_ `bool IsValidOrFixable() const;` — Returns true if the mesh contains valid information or slightly invalid information that we can fix. - Validates that stream sizes match. - Validates that there is at least one texture coordinate. - Validates that indices are valid positions in the vertex stream.
- L88 _public function_ `inline FVector3f GetWedgePosition(int32 WedgeIndex) const` — Helper for getting the position of a wedge.
- L97 _public prototype_ `void CompactMaterialIndices();` — Compacts materials by removing any that have no associated triangles. Also updates the material index map.

#### class `FRawMeshBulkData`  
`class FRawMeshBulkData`  
_L111-151_
- desc: Bulk data storage for raw meshes.
- L115 _private member_ `TDontCopy<FRWLock> BulkDataLock;` — Protects simultaneous access to BulkData
- L118 _private member_ `FByteBulkData BulkData;` — Internally store bulk data as bytes.
- L120 _private member_ `FGuid Guid;` — GUID associated with the data stored herein.
- L122 _private member_ `bool bGuidIsHash;` — If true, the GUID is actually a hash of the contents.
- L126 _public prototype_ `FRawMeshBulkData();` — Default constructor.
- L129 _public prototype_ `void Serialize(class FArchive& Ar, class UObject* Owner);` — Serialization.
- L132 _public prototype_ `void SaveRawMesh(struct FRawMesh& InMesh);` — Store a new raw mesh in the bulk data.
- L135 _public prototype_ `void LoadRawMesh(struct FRawMesh& OutMesh);` — Load the raw mesh from bulk data.
- L138 _public prototype_ `FString GetIdString() const;` — Retrieve a string uniquely identifying the contents of this bulk data.
- L141 _public prototype_ `void UseHashAsGuid(class UObject* Owner);` — Uses a hash as the GUID, useful to prevent creating new GUIDs on load for legacy assets.
- L142 _public function_ `bool UsesHashAsGuid() const`
- L144 _public prototype_ `const FByteBulkData& GetBulkData() const;`
- L147 _public function_ `inline bool IsEmpty() const` — Returns true if no bulk data is available for this mesh.
- L150 _public prototype_ `void Empty();` — Returns true if no bulk data is available for this mesh.

#### Free symbols / members of external scopes

- L22 _enumerator_ `MAX_MESH_TEXTURE_COORDS = 8` (scope `__anonf4676dca0103`)
- L105 _prototype_ `FArchive& operator<<(FArchive& Ar, FRawMesh& RawMesh);` — Add the raw mesh data to an archive
