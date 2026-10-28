# Shaders / Plugins/TextureGraph/Shaders/Mesh

- files: 4; lines: 162
- record kinds: cpp_binding=7, define=1, entry=7, function=2, include=6, member=10, parameter=5, resource=1, struct=2

### `Plugins/TextureGraph/Shaders/Mesh/MeshVertexShader.ush` (Other)

- lines: 42; parse: all-branches

#### Macros (#define, 1)

- L7 `#define MESH_VERTEX_SHADER_USH ` _[#if !defined(MESH_VERTEX_SHADER_USH)]_

#### Structs / classes (2)

- L9-16 _struct_ **`CoreMeshInput`** `struct CoreMeshInput` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L11 _member_ `float4 pos : ATTRIBUTE0;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L12 _member_ `float2 uv : ATTRIBUTE1;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L13 _member_ `float3 normal : ATTRIBUTE2;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L14 _member_ `float4 tangent : ATTRIBUTE3;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L15 _member_ `float4 color : ATTRIBUTE4;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
- L18-25 _struct_ **`CoreMeshOutput`** `struct CoreMeshOutput` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L20 _member_ `float4 pos : SV_POSITION;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L21 _member_ `float2 uv : TEXCOORD0;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L22 _member_ `float3 normal : NORMAL0;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L23 _member_ `float4 tangent : TANGENT0;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_
  - L24 _member_ `float4 color : COLOR0;` _[#if !defined(MESH_VERTEX_SHADER_USH)]_

#### Functions (1)

- L27-38 _function_ `CoreMeshOutput VSH_MeshUV(CoreMeshInput v)` _[#if !defined(MESH_VERTEX_SHADER_USH)]_

### `Plugins/TextureGraph/Shaders/Mesh/Mesh_Dilate.usf` (Other)

- lines: 68; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (1)

- L64-67 _entry_ `float4 FSH_Main(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_DilateMeshTexture` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshDilateUVs.cpp:11)

#### Global resources (textures / buffers / samplers) (1)

- L11 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (3)

- L8 _parameter_ `float InvSourceWidth;`
- L9 _parameter_ `float InvSourceHeight;`
- L10 _parameter_ `float Steps;`

#### Functions (1)

- L13-62 _function_ `float4 DilateFunction(Texture2D sourceTex, float2 uv, float maxSteps)`

### `Plugins/TextureGraph/Shaders/Mesh/Mesh_TextureEncoding.usf` (Other)

- lines: 25; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `./MeshVertexShader.ush`

#### Entry points (4)

- L5-8 _entry_ `float4 FSH_WorldPos(CoreMeshOutput input) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_MeshTexture_WorldPos` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshEncodedAsTexture.cpp:15)
- L10-13 _entry_ `float4 FSH_WorldNormals(CoreMeshOutput input) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_MeshTexture_WorldNormals` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshEncodedAsTexture.cpp:16)
- L15-19 _entry_ `float4 FSH_WorldTangents(CoreMeshOutput input) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_MeshTexture_WorldTangents` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshEncodedAsTexture.cpp:17)
- L21-24 _entry_ `float4 FSH_WorldUVMask(CoreMeshOutput input) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_MeshTexture_WorldUVMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshEncodedAsTexture.cpp:18)

### `Plugins/TextureGraph/Shaders/Mesh/Mesh_TextureVSH.usf` (Other)

- lines: 27; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `./MeshVertexShader.ush`

#### Entry points (2)

- L6-10 _entry_ `CoreMeshOutput VSH_MeshTexture(CoreMeshInput input)` — stage: **vertex (from C++ binding)** — C++: `VSH_MeshTexture` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshEncodedAsTexture.cpp:12)
- L17-26 _entry_ `CoreMeshOutput VSH_MeshTexture_WorldPos(CoreMeshInput input)` — stage: **vertex (from C++ binding)** — C++: `VSH_MeshTexture_WorldPos` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mesh/T_MeshEncodedAsTexture.cpp:13)

#### Global parameters (uniforms) (2)

- L14 _parameter_ `float3 BoundsMin;`
- L15 _parameter_ `float3 InvBoundsDiameter;`
