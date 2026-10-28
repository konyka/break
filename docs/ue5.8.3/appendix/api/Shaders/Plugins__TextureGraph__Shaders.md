# Shaders / Plugins/TextureGraph/Shaders

- files: 16; lines: 1600
- record kinds: cpp_binding=5, define=28, entry=6, function=78, include=20, member=6, parameter=18, resource=15, struct=1, unparsed=1

### `Plugins/TextureGraph/Shaders/BlobViewWidget.ush` (Other)

- lines: 19; parse: all-branches; parse notes: 1

#### Global parameters (uniforms) (6)

- L7 _parameter_ `float4 sample = blobTex.SampleLevel(blobTexSampler, texcoord.xy, 0);` — Fetch the blob texture no matter what
- L8 _parameter_ `float opacity = sample.w;`
- L11 _parameter_ `float checker = floor(texcoord.x * 10.0) + floor(texcoord.y * 10.0);` — make a checker grid over the viewport
- L12 _parameter_ `checker = frac(checker * 0.5) * 2.0;`
- L13 _parameter_ `float3 finalColor = checker;` — black and white checker by default
- L16 _parameter_ `finalColor = lerp(finalColor, sample.xyz, blobTexIsValid);` — Draw texture sample RGB if valid

#### Unparsed (raw text) (1)

- L18 _unparsed_ `return finalColor;`

<details><summary>parse notes</summary>

- L18: statement at declaration scope 'return finalColor'

</details>

### `Plugins/TextureGraph/Shaders/NormalsCommon.ush` (Other)

- lines: 60; parse: all-branches

#### Macros (#define, 1)

- L8 `#define NORMALS_COMMON_USH ` _[#if !defined(NORMALS_COMMON_USH)]_

#### Functions (7)

- L13-16 _function_ `float3 PartialDerivatesBlend(float3 n1, float3 n2)` _[#if !defined(NORMALS_COMMON_USH)]_
- L18-23 _function_ `float3 PartialDerivatesTransition(float3 a, float3 b, float t)` _[#if !defined(NORMALS_COMMON_USH)]_
- L25-29 _function_ `float3 ReconstructNormalZ(float2 rg)` _[#if !defined(NORMALS_COMMON_USH)]_
- L31-34 _function_ `float3 ReconstructNormalZ(float3 rgb)` _[#if !defined(NORMALS_COMMON_USH)]_
- L37-43 _function_ `float3 ConformNormals(float3 inputNormals)` _[#if !defined(NORMALS_COMMON_USH)]_
- L45-48 _function_ `float3 Conform(float3 A, float Renormalize)` _[#if !defined(NORMALS_COMMON_USH)]_
- L51-58 _function_ `float3 FillBlackPixels01Range(float3 nm)` — if nothing is in red or green channel, return flat normal. Works on [0,1] space normals _[#if !defined(NORMALS_COMMON_USH)]_

### `Plugins/TextureGraph/Shaders/Paint.ush` (Other)

- lines: 94; parse: all-branches

#### Macros (#define, 1)

- L8 `#define PAINT_USH ` _[#if !defined(PAINT_USH)]_

#### Functions (10)

- L13-17 _function_ `float ddLength(float a)` _[#if !defined(PAINT_USH)]_
- L20-26 _function_ `float Paint_EdgeUnder(float Coord, float Edge)` — Evaluate (Coord <= Edge) _[#if !defined(PAINT_USH)]_
- L28-31 _function_ `float Paint_EdgeAbove(float Coord, float Edge)` — Evaluate (Coord >= Edge) _[#if !defined(PAINT_USH)]_
- L34-41 _function_ `float Paint_Interval(float Coord, float LeftEdge, float RightEdge)` — Evaluate (Coord >= LeftEdge) * (Coord <= RightEdge) _[#if !defined(PAINT_USH)]_
- L44-49 _function_ `float Paint_Box(float2 Coord, float Left, float Bottom, float Right, float Top)` — Evaluate Coord in the Box [(Left, Bottom), (Right, Top)] _[#if !defined(PAINT_USH)]_
- L50 _function_ `float Paint_Box(float2 Coord, float2 LeftBottom, float2 RightTop)` _[#if !defined(PAINT_USH)]_
- L51 _function_ `float Paint_Box(float2 Coord, float4 LeftBottomRightTop)` _[#if !defined(PAINT_USH)]_
- L55-58 _function_ `float Paint_BoxEdge(float2 Coord, float2 LeftBottom, float2 RightTop, float2 OutEdge, float2 InEdge)` — Evaluate Coord in the Box [(Left, Bottom), (Right, Top)] _[#if !defined(PAINT_USH)]_
- L60-75 _function_ `float Paint_Stripe(float value, float period, float stripe)` _[#if !defined(PAINT_USH)]_
- L77-92 _function_ `float Paint_Grid(float2 Coord, float period, float stripe)` _[#if !defined(PAINT_USH)]_

### `Plugins/TextureGraph/Shaders/Placement_Projection.ush` (Other)

- lines: 139; parse: all-branches
- includes: L6 `SamplerStates.ush`, L7 `TiledFetch_Combined.ush`

#### Macros (#define, 1)

- L10 `#define PLACEMENT_PROJECTION_USH ` _[#if !defined(PLACEMENT_PROJECTION_USH)]_

#### Global resources (textures / buffers / samplers) (2)

- L18 _resource_ `Texture2D MeshmapPos;` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L19 _resource_ `Texture2D MeshmapNor;` _[#if !defined(PLACEMENT_PROJECTION_USH)]_

#### Global parameters (uniforms) (3)

- L14 _parameter_ `float3 MeshBoxMin;` — Convert the mesh map position to world coordinate _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L15 _parameter_ `float3 MeshBoxSize;` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L16 _parameter_ `float3 MeshViewScale;` _[#if !defined(PLACEMENT_PROJECTION_USH)]_

#### Functions (10)

- L21-36 _function_ `float2x3 Fetch_MeshSurface(float2 layer_uv)` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L38-47 _function_ `float3 Transform_Pos_RotateAroundZX(float2 Zcs, float2 Xcs, float3 pos)` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L48-57 _function_ `float3 Transform_Dir_RotateAroundZX(float2 Zcs, float2 Xcs, float3 dir)` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L59-74 _function_ `float3x2 EvalTriplanar_uvs(float3 mesh_pos, float3 mesh_nor, float2 uv_scaling)` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L76-85 _function_ `float3x4 Fetch_Source_Triplanar (Texture2DArray source, float3 mesh_pos, float3 mesh_nor, float2 uv_scaling)` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L87-94 _function_ `float3x4 Fetch_Source_Triplanar(Texture2DArray source, float3x2 triplanar_uvs)` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L97-100 _function_ `float3 HeightMask(float3 triplanarHeightSamples, float midpoint, float strength)` — Convert height to mask value _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L103-114 _function_ `float3 HeightMaskFromDisplacement(Texture2DArray displacement, float3x2 triplanar_uvs, float midpoint, float strength)` — Fetch height from displacement map at triplanar coordinate _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L116-119 _function_ `float EaseIn(float t)` _[#if !defined(PLACEMENT_PROJECTION_USH)]_
- L121-136 _function_ `float3 ProjectionNormals(float3 normals, float sharpenEdges, float3 heightMask)` _[#if !defined(PLACEMENT_PROJECTION_USH)]_

### `Plugins/TextureGraph/Shaders/SampleCompute.usf` (Other)

- lines: 26; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`

#### Macros (#define, 3)

- L5 `#define THREADGROUPSIZE_X 1` _[#if !defined(THREADGROUPSIZE_X)]_
- L6 `#define THREADGROUPSIZE_Y 1` _[#if !defined(THREADGROUPSIZE_X)]_
- L7 `#define THREADGROUPSIZE_Z 1` _[#if !defined(THREADGROUPSIZE_X)]_

#### Entry points (1)

- L13-25 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)] void CmpSH_Test(uint3 ThreadId : SV_DispatchThreadID)` — stage: **compute**

#### Global resources (textures / buffers / samplers) (2)

- L10 _resource_ `RWTexture2D<uint4> Result;`
- L11 _resource_ `Texture2D<uint4> Albedo;`

### `Plugins/TextureGraph/Shaders/SamplerStates.ush` (Other)

- lines: 17; parse: all-branches

#### Macros (#define, 1)

- L8 `#define SAMPLER_STATES_USH ` _[#if !defined(SAMPLER_STATES_USH)]_

#### Global resources (textures / buffers / samplers) (6)

- L10 _resource_ `SamplerState SamplerStates_Clamp;` _[#if !defined(SAMPLER_STATES_USH)]_
- L11 _resource_ `SamplerState SamplerStates_Wrap;` _[#if !defined(SAMPLER_STATES_USH)]_
- L12 _resource_ `SamplerState SamplerStates_NoBorder;` _[#if !defined(SAMPLER_STATES_USH)]_
- L13 _resource_ `SamplerState SamplerStates_Linear_Clamp;` _[#if !defined(SAMPLER_STATES_USH)]_
- L14 _resource_ `SamplerState SamplerStates_Linear_Wrap;` _[#if !defined(SAMPLER_STATES_USH)]_
- L15 _resource_ `SamplerState SamplerStates_Linear_Border;` _[#if !defined(SAMPLER_STATES_USH)]_

### `Plugins/TextureGraph/Shaders/ShaderUtil.ush` (Other)

- lines: 93; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Functions (12)

- L6-12 _function_ `float SimpleCurve(float input, float curve)`
- L14-17 _function_ `float Remap( float value, float from1, float to1, float from2, float to2)`
- L18-21 _function_ `float2 Remap(float2 value, float2 iMin, float2 iMax, float2 oMin, float2 oMax)`
- L22-26 _function_ `float Posterize(float value, float steps)`
- L27-33 _function_ `float SFNoise(float2 uv, float seed)`
- L35-46 _function_ `float3x3 GetTransform_TS_to_WS(float3x3 _ObjectToWorld, float3 worldNormal, float4 worldTangent)`
- L48-54 _function_ `float4 AdjustBrightnessAndContrast(float4 Color, float Brightness, float Contrast)`
- L56-60 _function_ `float4 AdjustBrightnessAndContrast_NoAlpha(float4 Color, float Brightness, float Contrast)`
- L62-68 _function_ `float LumaFromRGB(float3 Color)`
- L71-75 _function_ `float Grayscale(float3 Color)`
- L77-85 _function_ `float3 RGBToHSV(float3 c)`
- L87-92 _function_ `float3 HSVToRGB( float3 c )`

### `Plugins/TextureGraph/Shaders/ShapeMask.ush` (Other)

- lines: 160; parse: all-branches
- includes: L7 `SignedDistanceFunction.ush`, L8 `ShaderUtil.ush`

#### Macros (#define, 1)

- L11 `#define SHAPE_MASK_USH ` _[#if !defined(SHAPE_MASK_USH)]_

#### Functions (11)

- L15-18 _function_ `float RemapDistanceBevelled(float InDistance, float InBevelWidth)` — Eval the beveled value to the input distance from the edge Clamp the result to the range [0,1] _[#if !defined(SHAPE_MASK_USH)]_
- L22-27 _function_ `float EvalBevelCurve(float input, float curve)` — Eval the bevel curve to the (eventually bevelled) input distance from the edge Return the corresponding _[#if !defined(SHAPE_MASK_USH)]_
- L29-33 _function_ `float EvalMaskFromSDF(float SDF, float BevelWidth, float BevelCurve)` _[#if !defined(SHAPE_MASK_USH)]_
- L57-67 _function_ `float4 ShapeMask_Circle(float2 Pos, float Radius, float Rounding = 0, float2 Bevel = 0)` — A circle centered on the origin of radius R Rounding is not used, it will be returned to the radius value _[#if !defined(SHAPE_MASK_USH)]_
- L71-81 _function_ `float4 ShapeMask_Ellipse(float2 Pos, float2 Size, float Rounding = 0, float2 Bevel = 0)` — An Ellipse centered on the origin of radius Rx = Size.x, Ry = Size.y Rounding is not used, it will be returned to the radius value _[#if !defined(SHAPE_MASK_USH)]_
- L84-94 _function_ `float4 ShapeMask_Rect(float2 Pos, float2 Size, float Rounding = 0, float2 Bevel = 0)` — A rectangle centered on the origin of width 2*Size.x and height 2*Size.y _[#if !defined(SHAPE_MASK_USH)]_
- L96-106 _function_ `float4 ShapeMask_Segment(float2 Pos, float SizeX, float Rounding = 0, float2 Bevel = 0)` _[#if !defined(SHAPE_MASK_USH)]_
- L108-119 _function_ `float4 ShapeMask_Triangle(float2 Pos, float Radius, float Rounding = 0, float2 Bevel = 0)` _[#if !defined(SHAPE_MASK_USH)]_
- L121-132 _function_ `float4 ShapeMask_Pentagon(float2 Pos, float Radius, float Rounding = 0, float2 Bevel = 0)` _[#if !defined(SHAPE_MASK_USH)]_
- L134-145 _function_ `float4 ShapeMask_Hexagon(float2 Pos, float Radius, float Rounding = 0, float2 Bevel = 0)` _[#if !defined(SHAPE_MASK_USH)]_
- L147-158 _function_ `float4 ShapeMask_Polygon(float2 Pos, float Radius, const int NumSides, float Rounding = 0, float2 Bevel = 0)` _[#if !defined(SHAPE_MASK_USH)]_

### `Plugins/TextureGraph/Shaders/SignedDistanceFunction.ush` (Other)

- lines: 262; parse: all-branches

#### Macros (#define, 1)

- L17 `#define SDF_USH ` _[#if !defined(SDF_USH)]_

#### Functions (11)

- L29-32 _function_ `float SDF_Circle(float2 P, float Radius)` — SDF to the circle centered on origin of radius R _[#if !defined(SDF_USH)]_
- L37-65 _function_ `float SDF_Ellipse(float2 P, float RadiusX, float RadiusY)` — SDF to the ellipse centered on origin of radius R Technique taken from IQ's shadertoy "Ellipse - distance 2D II No Trig" Using a Newton solver over 8 passes _[#if !defined(SDF_USH)]_
- L68-73 _function_ `float SDF_Rect(float2 P, float HalfSizeX, float HalfSizeY)` — SDF to the rectangle centered on origin of size [2 * HalfSizeX, 2 * HalfSizeY] _[#if !defined(SDF_USH)]_
- L77-81 _function_ `float SDF_Segment(float2 P, float HalfSize)` — SDF to the segment along X axis centered on origin of size (2 * HalfSize), the SDF is always >= 0 _[#if !defined(SDF_USH)]_
- L84-89 _function_ `float SDF_Segment(float2 P, float2 A, float2 B)` — SDF to the segment AB, the SDF is always >= 0 _[#if !defined(SDF_USH)]_
- L104-114 _function_ `float2 SDF_OrientedSegment_SquareRegion(float2 P, float2 A, float2 B)` — SDF to the oriented segment AB the function returns the pair (SqDistance, Region) - SqDistance is the square of SDF_Segment() - Region express the region of space relative to the segment AB: From the segment tangent vector T, we define the normal vector N (-Ty, Tx). The strip of space [A,B] contained between the 2 lines (A + tN) and (B + tN) which are perpendicular to the segment AB passing by A and B. +1 is the region of space in the strip [A,B] on the Right of the segment -1 is the region of space in the strip [A,B] on the Left of the segment 0  is the points of the segment 0  is the half sp _[#if !defined(SDF_USH)]_
- L117-139 _function_ `float SDF_Triangle(float2 P, float2 V0, float2 V1, float2 V2)` — SDF to the general triangle ABC _[#if !defined(SDF_USH)]_
- L144-162 _function_ `float SDF_EquilateralTriangle(float2 P, float Radius)` — SDF to the equilateral triangle centered on origin O, of radius R Pointing upward -Y axis Base is symetric along horizontal X axis _[#if !defined(SDF_USH)]_
- L170-191 _function_ `float SDF_Pentagon(float2 P, float Radius)` — SDF to the pentagon centered on origin C, of radius R First side is horizontal Pointing upward -Y axis Pentagon has 5 vertices Vn The center C to 2 consecutive vertices define a sector S There are 5 sectors: (C-V0 C-V1) ... (C-V4 C-V0) _[#if !defined(SDF_USH)]_
- L199-217 _function_ `float SDF_Hexagon(float2 P, float Radius)` _[#if !defined(SDF_USH)]_
- L227-260 _function_ `float SDF_Polygon(float2 P, float Radius, const int NumSides)` — SDF to the Regular Polygon with N sides Polygon is centered on origin C, of radius R First side is horizontal Polygon has N vertices Vn The center C to 2 consecutive vertices define a sector S There are N sectors: (C-V0 C-V1) ... (C-Vn-1 C-V0) _[#if !defined(SDF_USH)]_

### `Plugins/TextureGraph/Shaders/Simple.usf` (Other)

- lines: 20; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L4 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (2)

- L7-11 _entry_ `void VSH_Simple(float4 ipos : ATTRIBUTE0, float2 iuv : ATTRIBUTE1, out float2 ouv : TEXCOORD0, out float4 opos : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `VSH_Simple` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/FxMaterial.cpp:10) — Simple vertex shader: Pass through pos and uv attributes
- L16-19 _entry_ `float4 FSH_Simple(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Simple` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/FxMaterial.cpp:11) — Simple fragment shader: Fetch texture at uv and blit out

#### Global resources (textures / buffers / samplers) (1)

- L13 _resource_ `Texture2D SourceTexture;`

### `Plugins/TextureGraph/Shaders/SimpleVT.usf` (Other)

- lines: 30; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L4 `/Plugin/TextureGraph/SamplerStates.ush`, L9 `/Engine/Private/VirtualTextureCommon.ush`

#### Macros (#define, 2)

- L5 `#define NUM_VIRTUALTEXTURE_SAMPLES 0`
- L7 `#define VT_DISABLE_VIEW_UNIFORM_BUFFER 1`

#### Entry points (1)

- L21-29 _entry_ `float4 FSH_SimpleVT(in float2 uv : TEXCOORD0,in float4 InPosition : SV_POSITION) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_SimpleVT` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/FxMaterial.cpp:12) — Simple fragment shader: Fetch virtual texture at uv and blit out

#### Global resources (textures / buffers / samplers) (4)

- L11 _resource_ `Texture2D<uint4> InPageTableTexture0;`
- L12 _resource_ `Texture2D<uint4> InPageTableTexture1;`
- L13 _resource_ `Texture2D InPhysicalTexture;`
- L18 _resource_ `SamplerState InTextureSampler;`

#### Global parameters (uniforms) (2)

- L15 _parameter_ `uint4 VTPackedPageTableUniform[2];`
- L16 _parameter_ `uint4 VTPackedUniform;`

### `Plugins/TextureGraph/Shaders/TextureGraphMaterialShader.usf` (Other)

- lines: 149; parse: all-branches
- includes: L8 `/Engine/Public/Platform.ush`, L9 `/Engine/Private/Common.ush`, L10 `/Engine/Generated/Material.ush`, L11 `/Engine/Private/BasePassCommonFunctions.ush`, L17 `/Engine/Private/Substrate/SubstrateExport.ush` [SHADER_MATERIAL_USES_SUBSTRATE], L22 `TileInfo.ush`

#### Macros (#define, 6)

- L3 `#define SCENE_TEXTURES_DISABLED 1`
- L4 `#define SUBSTRATE_INLINE_SHADING 1`
- L5 `#define SUBSTRATE_USE_FULLYSIMPLIFIED_MATERIAL 1`
- L13 `#define SHADER_MATERIAL_USES_SUBSTRATE (SUBSTRATE_ENABLED && MATERIAL_IS_SUBSTRATE)`
- L15 `#define MATERIAL_SUBSTRATE_OPAQUE_PRECOMPUTED_LIGHTING 0` _[#if SHADER_MATERIAL_USES_SUBSTRATE]_
- L16 `#define SUBSTRATE_MATERIAL_EXPORT_REQUESTED 1` _[#if SHADER_MATERIAL_USES_SUBSTRATE]_
- L2 #undef `SCENE_TEXTURES_DISABLED`

#### Entry points (2)

- L24-33 _entry_ `void TextureGraphMaterialShaderVS( in float4 InPosition : ATTRIBUTE0, in float2 InTexCoord : ATTRIBUTE1, out float2 OutUV : TEXCOORD0, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FTextureGraphMaterialShaderVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/FxMaterial_DrawMaterial.cpp:10)
- L35-148 _entry_ `void TextureGraphMaterialShaderPS( in float2 InUV : TEXCOORD0, in float4 SvPosition : SV_Position, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FTextureGraphMaterialShaderPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/TextureGraph/Source/TextureGraphEngine/FxMat/FxMaterial_DrawMaterial.cpp:11)

#### Global parameters (uniforms) (1)

- L20 _parameter_ `float4 PSControl;`

### `Plugins/TextureGraph/Shaders/TileInfo.ush` (Other)

- lines: 143; parse: all-branches

#### Macros (#define, 1)

- L8 `#define TILE_INFO_USH ` _[#if !defined(TILE_INFO_USH)]_

#### Structs / classes (1)

- L65-73 _struct_ **`TileInfo`** `struct TileInfo` _[#if !defined(TILE_INFO_USH)]_
  - L67 _member_ `float TileX;` _[#if !defined(TILE_INFO_USH)]_
  - L68 _member_ `float TotalCountX;` _[#if !defined(TILE_INFO_USH)]_
  - L69 _member_ `float TileWidth;` _[#if !defined(TILE_INFO_USH)]_
  - L70 _member_ `float TileY;` _[#if !defined(TILE_INFO_USH)]_
  - L71 _member_ `float TotalCountY;` _[#if !defined(TILE_INFO_USH)]_
  - L72 _member_ `float TileHeight;` _[#if !defined(TILE_INFO_USH)]_

#### Global parameters (uniforms) (6)

- L74 _parameter_ `float TileInfo_TileX;` _[#if !defined(TILE_INFO_USH)]_
- L75 _parameter_ `float TileInfo_TileCountX;` _[#if !defined(TILE_INFO_USH)]_
- L76 _parameter_ `float TileInfo_TileWidth;` _[#if !defined(TILE_INFO_USH)]_
- L77 _parameter_ `float TileInfo_TileY;` _[#if !defined(TILE_INFO_USH)]_
- L78 _parameter_ `float TileInfo_TileCountY;` _[#if !defined(TILE_INFO_USH)]_
- L79 _parameter_ `float TileInfo_TileHeight;` _[#if !defined(TILE_INFO_USH)]_

#### Functions (7)

- L83-86 _function_ `float2 TileInfo_tileGridDim()` — Access the full tile grid dimension (numCols, numRows) (xy) _[#if !defined(TILE_INFO_USH)]_
- L88-91 _function_ `float2 TileInfo_layerResolution()` — Access the total resolution of the layer as a single image _[#if !defined(TILE_INFO_USH)]_
- L94-97 _function_ `float2 TileInfo_tilePos()` — Access the current job invocation tile position (xy) within the full tile grid _[#if !defined(TILE_INFO_USH)]_
- L100-105 _function_ `float2 TileInfo_fromCurrentTileToLayer(float2 tileCoord)` — Convert from the CURRENT tile coordinate to the full layer space uv coordinate _[#if !defined(TILE_INFO_USH)]_
- L108-112 _function_ `int2 TileInfo_fromLayerToTile(int2 texelCoord)` — TODO find a better name _[#if !defined(TILE_INFO_USH)]_
- L116-125 _function_ `float4 TileInfo_fromLayerToTile(float2 layerCoord)` — Convert from the layer space coordinate uv to the tile space uv return the normalized uv coord in the tile (in xy) and the tile coordinate in the grid (zw) _[#if !defined(TILE_INFO_USH)]_
- L128-138 _function_ `int TileInfo_tileIndexFromLayerTexel(int2 texel)` — Given texel in layer, find the LINEAR index of the tile (used in a TextureArray) that contains the blob for that texel _[#if !defined(TILE_INFO_USH)]_

### `Plugins/TextureGraph/Shaders/TiledFetch.ush` (Other)

- lines: 264; parse: all-branches
- includes: L9 `SamplerStates.ush` [!defined(TILED_FETCH_USH)]

#### Macros (#define, 8)

- L7 `#define TILED_FETCH_USH ` _[#if !defined(TILED_FETCH_USH)]_
- L39 `#define FetchLinear(tex, _uv) tex.Sample(SamplerStates_Linear_Clamp, _uv)` (2 lines) _[#if !defined(TILED_FETCH_USH)]_
- L42 `#define Fetch(tex, _uv) tex.Sample(SamplerStates_Clamp, _uv)` (2 lines) _[#if !defined(TILED_FETCH_USH)]_
- L45 `#define Tile(T, I) T##_##I` _[#if !defined(TILED_FETCH_USH)]_
- L47 `#define Declare_TiledArray(T) Texture2D Tile(T, 0); Texture2D Tile(T, 1); Texture2D Tile(T, 2); Texture2D Tile(T, 3); Texture2D Tile(T, 4); Texture2D Tile(T, 5); Texture2D Tile(T, 6); Texture2D Tile(T, 7); Texture2D Tile(T, 8);` (10 lines) _[#if !defined(TILED_FETCH_USH)]_
- L59 `#define Declare_FetchTile(T) float4 FetchTile_##T(float2 tile, float2 uv) { int tileIdx = (tile.x + 1) * 3 + (tile.y + 1); if (tileIdx == 1) return Fetch(Tile(T, 1), uv); if (tileIdx == 7) return Fetch(Tile(T, 7), uv); ; if (tile ...` (17 lines) _[#if !defined(TILED_FETCH_USH)]_
- L160 `#define Declare_FetchTiled(T) float4 FetchTiled_##T(float2 uv) { float2 tileSize; Tile(T,4).GetDimensions(tileSize.x, tileSize.y); float2 invTileSize = 1.0 / tileSize; float2 tileQuad = 0; float tileQuadCase = EvalTileQuadAt(uv, i ...` (56 lines) _[#if !defined(TILED_FETCH_USH)]_
- L258 `#define Declare_Tiles_And_FetchTiled(T) Declare_TiledArray(T) Declare_FetchTile(T) Declare_FetchTiled(T)` (4 lines) _[#if !defined(TILED_FETCH_USH)]_

#### Functions (1)

- L229-256 _function_ `float EvalTileQuadAt(float2 texcoord, float2 invTileSize, in out float2 tileQuad)` — EvalTileQuadAt() Evaluate the tile quad fetching situation at the specified 'texcoord' uv in the range [0,1] in a tile containg 'size' texels, the function uses the inverse of size 'invTileSize' the function compute the tileQuad which indicate the neighbor tiles touched by the fetching quad along X and Y. The function returns a CODE indicating the case: 0 <=> tileQuad == (   0,    0) : the quad is fully in the main tile, no need for other tiles 1 <=> tileQuad == (+/-1,    0) : the quad is crossing a West or East border into another tile (but no North/South) 2 <=> tileQuad == (   0, +/-1) : the _[#if !defined(TILED_FETCH_USH)]_

### `Plugins/TextureGraph/Shaders/TiledFetch_Combined.ush` (Other)

- lines: 100; parse: all-branches
- includes: L10 `SamplerStates.ush` [!defined(TILED_FETCH_COMBINED_USH)], L11 `TileInfo.ush` [!defined(TILED_FETCH_COMBINED_USH)]

#### Macros (#define, 1)

- L8 `#define TILED_FETCH_COMBINED_USH ` _[#if !defined(TILED_FETCH_COMBINED_USH)]_

#### Functions (7)

- L13-26 _function_ `void ToPivotInBlob(inout float2 pivot)` _[#if !defined(TILED_FETCH_COMBINED_USH)]_
- L28-31 _function_ `float2 WrapUV(float2 uv, float2 repeatAfter)` _[#if !defined(TILED_FETCH_COMBINED_USH)]_
- L33-36 _function_ `float2 ClampUV(float2 uv, float2 min, float2 max)` _[#if !defined(TILED_FETCH_COMBINED_USH)]_
- L38-41 _function_ `bool inRange(int low, int high, int x)` _[#if !defined(TILED_FETCH_COMBINED_USH)]_
- L44-76 _function_ `float4 SampleBlob(in Texture2DArray CombinedBlobSRV, in float2 layer_uv)` _[#if !defined(TILED_FETCH_COMBINED_USH)]_
- L79-82 _function_ `float2 wrap_uv(float2 uv)` — Wrap the uv in the [0, 1] range _[#if !defined(TILED_FETCH_COMBINED_USH)]_
- L84-97 _function_ `float4 SampleLayerRaster(in Texture2DArray CombinedBlobSRV, in float2 layer_uv)` _[#if !defined(TILED_FETCH_COMBINED_USH)]_

### `Plugins/TextureGraph/Shaders/Transform.ush` (Other)

- lines: 24; parse: all-branches

#### Macros (#define, 1)

- L8 `#define TRANSFORM_USH ` _[#if !defined(TRANSFORM_USH)]_

#### Functions (2)

- L10-13 _function_ `float2 Transform_Rotate(float2 InCoord, float2 Rotation)` _[#if !defined(TRANSFORM_USH)]_
- L15-22 _function_ `float2 Transform_PivotRotate(float2 InCoord, float2 Pivot, float2 Rotation)` _[#if !defined(TRANSFORM_USH)]_
