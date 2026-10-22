# Shaders / Plugins/Runtime/RenderTrace/Shaders/Private

- files: 1; lines: 129
- record kinds: cpp_binding=2, entry=2, function=1, include=3, member=2, parameter=1, struct=1

### `Plugins/Runtime/RenderTrace/Shaders/Private/PhysicalMaterialSampler.usf` (Private)

- lines: 129; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`, L8 `/Engine/Generated/Material.ush`, L9 `/Engine/Generated/VertexFactory.ush`

#### Entry points (2)

- L20-37 _entry_ `void VSMain( FVertexFactoryInput Input, out FPhysicalMaterialSamplerInterpolantsVSToPS Output )` — stage: **vertex (from C++ binding)** — C++: `FPhysicalMaterialSamplerShaderVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/RenderTrace/Source/Private/RenderTrace.cpp:166) — Simple default vertex shader. _[#if VERTEXSHADER]_
- L54-126 _entry_ `void PSMain( FPhysicalMaterialSamplerInterpolantsVSToPS Interpolants OPTIONAL_IsFrontFace, out HALF4_TYPE OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FPhysicalMaterialSamplerShaderPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/RenderTrace/Source/Private/RenderTrace.cpp:225) — Pixel shader outputs index of physical material. _[#if !(VERTEXSHADER) && PIXELSHADER]_

#### Structs / classes (1)

- L11-15 _struct_ **`FPhysicalMaterialSamplerInterpolantsVSToPS`** `struct FPhysicalMaterialSamplerInterpolantsVSToPS`
  - L13 _member_ `FVertexFactoryInterpolantsVSToPS FactoryInterpolants;`
  - L14 _member_ `float4 Position : SV_POSITION;`

#### Global parameters (uniforms) (1)

- L41 _parameter_ `float DrawSerialNumber;` _[#if !(VERTEXSHADER) && PIXELSHADER]_

#### Functions (1)

- L43-51 _function_ `float2 UpdateDominantMaterial(in float Index, in float Contribution, in float2 DominantMaterial)` _[#if !(VERTEXSHADER) && PIXELSHADER]_
