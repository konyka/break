# Plugins / MeshFileUtils

- module root: `Plugins/Runtime/GeometryProcessing/Source/MeshFileUtils`
- headers: 2; symbols: 20
- symbol kinds: class=1, enum=1, enumerator=2, member=7, namespace=2, prototype=5, struct=2
- PublicDependencyModuleNames: Core, GeometryCore

### `Plugins/Runtime/GeometryProcessing/Source/MeshFileUtils/Public/MeshFileUtilsModule.h` (Public)


#### class `FMeshFileUtilsModule`  
`class FMeshFileUtilsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/GeometryProcessing/Source/MeshFileUtils/Public/OBJMeshUtil.h` (Public)


#### enum `UE::MeshFileUtils::ELoadOBJStatus`  
`enum class ELoadOBJStatus`  
_L11-15_
- L13 _public enumerator_ `InvalidPath`
- L14 _public enumerator_ `Success`

#### struct `UE::MeshFileUtils::FLoadOBJSettings`  
`struct FLoadOBJSettings`  
_L17-33_
- L23 _public member_ `bool bAddSeparatedTriForNonManifold = true;` — Dynamic mesh doesn't support non-manifold edges (edges with more than two triangles), but OBJ does If this setting is true, non-manifold triangles will be added as fully separated triangles; otherwise, such triangles will be skipped entirely
- L26 _public member_ `bool bReverseOrientation = true;` — If true, reverses the orientation of the faces
- L29 _public member_ `bool bLoadNormals = false;` — If true and obj contains normal information will compute normal overlay
- L32 _public member_ `bool bLoadUVs = false;` — If true and obj contains UVs information will compute UV overlay.

#### struct `UE::MeshFileUtils::FWriteOBJSettings`  
`struct FWriteOBJSettings`  
_L35-45_
- L38 _public member_ `bool bReverseOrientation = true;` — If true reverses the orientation of the faces
- L41 _public member_ `bool bWritePerVertexValues = true;` — If true will attempt to write the per-vertex normals and UVs to the OBJ instead of the per-element values
- L44 _public member_ `bool bWritePerVertexColors = false;` — Whether to write per-vertex colors (when available)

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshFileUtils` (scope `UE`)
- L48 _prototype_ `ELoadOBJStatus LoadOBJ(const char* Path, UE::Geometry::FDynamicMesh3& Mesh, const FLoadOBJSettings& Settings = FLoadOBJSettings());` (scope `UE::MeshFileUtils`) — Attempt to load an OBJ file into a Dynamic Mesh
- L50 _prototype_ `UE::Geometry::FDynamicMesh3 LoadOBJChecked(const char* Path, const FLoadOBJSettings& Settings = FLoadOBJSettings());` (scope `UE::MeshFileUtils`) — Load an OBJ file into a Dynamic Mesh, or fail a check() if it cannot be loaded
- L52 _prototype_ `bool WriteOBJ(const char* Path, const UE::Geometry::FDynamicMesh3& InMesh, const FWriteOBJSettings& Settings = FWriteOBJSettings());` (scope `UE::MeshFileUtils`) — Write an OBJ file to the target path; returns true on success
