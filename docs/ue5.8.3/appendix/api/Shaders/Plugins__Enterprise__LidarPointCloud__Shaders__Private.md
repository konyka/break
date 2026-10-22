# Shaders / Plugins/Enterprise/LidarPointCloud/Shaders/Private

- files: 1; lines: 632
- record kinds: cpp_binding=1, define=1, function=34, include=3, macro_call=3, member=20, parameter=32, prototype=2, resource=1, static_var=1, struct=6

### `Plugins/Enterprise/LidarPointCloud/Shaders/Private/LidarPointCloudVertexFactory.ush` (Private)

- lines: 632; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/VertexFactoryCommon.ush`, L630 `/Engine/Private/VertexFactoryDefaultInterface.ush`

#### Macros (#define, 1)

- L503 `#define VF_IMPLEMENTED_GET_INSTANCE_HIT_PROXY_ID ` _[#if USE_INSTANCING]_

#### Structs / classes (6)

- L72-81 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput`
  - L74 _member_ `float4 Position : ATTRIBUTE0;`
  - L75 _member_ `half4 Color : ATTRIBUTE1;`
  - L76 _member_ `uint MetaData : ATTRIBUTE2;`
  - L77 _member_ `uint VertexId : SV_VertexID;`
- L83-90 _struct_ **`FPositionOnlyVertexFactoryInput`** `struct FPositionOnlyVertexFactoryInput`
  - L85 _member_ `float4 Position : ATTRIBUTE0;`
  - L86 _member_ `uint VertexId : SV_VertexID;`
- L92-100 _struct_ **`FPositionAndNormalOnlyVertexFactoryInput`** `struct FPositionAndNormalOnlyVertexFactoryInput`
  - L94 _member_ `float4 Position : ATTRIBUTE0;`
  - L95 _member_ `float4 Normal : ATTRIBUTE2;`
  - L96 _member_ `uint VertexId : SV_VertexID;`
- L102-110 _struct_ **`FVertexFactoryInterpolantsVSToPS`** `struct FVertexFactoryInterpolantsVSToPS`
  - L104 _member_ `TANGENTTOWORLD_INTERPOLATOR_BLOCK half4 Color : COLOR0;`
  - L107 _member_ `half Alpha : COLOR1;`
  - L108 _member_ `float2 TexCoords : TEXCOORD0;`
- L112-122 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates`
  - L114 _member_ `half3x3 TangentToLocal;`
  - L115 _member_ `half3x3 TangentToWorld;`
  - L116 _member_ `half TangentToWorldSign;`
  - L117 _member_ `half4 Color;`
  - L118 _member_ `half Alpha;`
  - L119 _member_ `float3 Position;`
  - L121 _member_ `FSceneDataIntermediates SceneData;` — Cached primitive and instance data
- L515-518 _struct_ **`FVertexFactoryRayTracingInterpolants`** `struct FVertexFactoryRayTracingInterpolants` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
  - L517 _member_ `FVertexFactoryInterpolantsVSToPS InterpolantsVSToPS;` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_

#### Global resources (textures / buffers / samplers) (1)

- L30 _resource_ `Buffer<float> TreeBuffer;` _[#if !RAYHITGROUPSHADER]_

#### Global parameters (uniforms) (32)

- L14 _parameter_ `uint bEditorView;` — Used to detect if the instance is rendered inside the editor viewport
- L17 _parameter_ `half3 SelectionColor;` — Selection
- L20 _parameter_ `float3 LocationOffset;` — Alignment
- L23 _parameter_ `float VirtualDepth;` — Used for sprite size calculation
- L24 _parameter_ `float SpriteSizeMultiplier;`
- L25 _parameter_ `float RootCellSize;`
- L26 _parameter_ `float3 RootExtent;`
- L27 _parameter_ `uint bUsePerPointScaling;`
- L28 _parameter_ `float ReversedVirtualDepthMultiplier;`
- L34 _parameter_ `float3 ViewRightVector;` — Needed for WPO calculations
- L35 _parameter_ `float3 ViewUpVector;`
- L36 _parameter_ `uint bUseCameraFacing;`
- L37 _parameter_ `uint bUseScreenSizeScaling;`
- L38 _parameter_ `uint bUseStaticBuffers;`
- L41 _parameter_ `float3 BoundsSize;` — Used for coloration override
- L42 _parameter_ `half3 ElevationColorBottom;`
- L43 _parameter_ `half3 ElevationColorTop;`
- L46 _parameter_ `half4 Offset;` — Color Adjustment
- L47 _parameter_ `half4 Contrast;`
- L48 _parameter_ `half4 Saturation;`
- L49 _parameter_ `half4 Gamma;`
- L50 _parameter_ `half3 Tint;`
- L51 _parameter_ `float IntensityInfluence;`
- L54 _parameter_ `uint bUseCircle;` — Flags
- L55 _parameter_ `uint bUseColorOverride;`
- L56 _parameter_ `uint bUseElevationColor;`
- L57 _parameter_ `uint bUseClassification;`
- L58 _parameter_ `uint bUseClassificationAlpha;`
- L60 _parameter_ `float4 ClassificationColors[32];`
- L68 _parameter_ `float4x4 ClippingVolume[16];` — [Tx, Ty, Tz, Invert] [Fx, Fy, Fz, Ex] [Rx, Ry, Rz, Ey] [Ux, Uy, Uz, Ez]
- L69 _parameter_ `uint NumClippingVolumes;`
- L70 _parameter_ `uint bStartClipped;`

#### static variables (1)

- L11 _static_var_ `static float2 PrecomputedUV_Quad[8] = { float2(-0.5, -0.5), float2(0.5, -0.5), float2(0.5, 0.5), float2(-0.5, 0.5), float2(0, 1), float2(1, 1), float2(1, 0), float2(0, 0) };` — First half is normal, second half has inverted V

#### Functions (34)

- L124-154 _function_ `float3 ApplyClipping(float3 Position)`
- L156-209 _function_ `half3x3 CalcTangentToLocal(uint MetaData)`
- L211-219 _function_ `half3x3 CalcTangentToWorldNoScale(in half3x3 TangentToLocal)`
- L221-268 _function_ `float CalcSpriteSize(float3 Position)`
- L270-275 _function_ `float3 ProcessPosition(float3 Position, half3x3 TangentToLocal, int VertexID)`
- L277-283 _function_ `float3 ProcessPosition(float3 Position, int VertexID)`
- L285-289 _function_ `float3 LidarGetInstancePosition(uint VertexId)`
- L291-295 _function_ `float3 LidarGetInstanceNormal(uint VertexId)`
- L297-365 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)`
- L367-377 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)`
- L379-382 _function_ `half3x3 VertexFactoryGetTangentToLocal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L385-390 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return translated world position
- L392-396 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to instance
- L397-404 _function_ `float4 VertexFactoryGetWorldPosition(FPositionOnlyVertexFactoryInput Input)`
- L405-412 _function_ `float4 VertexFactoryGetWorldPosition(FPositionAndNormalOnlyVertexFactoryInput Input)`
- L413-416 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 InWorldPosition)`
- L417-420 _function_ `float3 VertexFactoryGetPositionForVertexLighting(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 TranslatedWorldPosition)`
- L421-424 _function_ `float3 VertexFactoryGetWorldNormal(FPositionAndNormalOnlyVertexFactoryInput Input)`
- L425-428 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L431-434 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return previous translated world position
- L437-441 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to instance
- L447-480 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, half3x3 TangentToLocal, bool bIsPreviousFrame = false)` — Converts from vertex factory specific input to a FMaterialVertexParameters, which is used by vertex shader material inputs.
- L482-500 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)`
- L505 _function_ `float4 VertexFactoryGetInstanceHitProxyId(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if USE_INSTANCING]_
- L508-512 _function_ `float4 VertexFactoryGetTranslatedPrimitiveVolumeBounds(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L520-527 _function_ `float2 VertexFactoryGetRayTracingTextureCoordinate( FVertexFactoryRayTracingInterpolants Interpolants )` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L529-532 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryAssignInterpolants(FVertexFactoryRayTracingInterpolants Input)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L534-539 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryGetRayTracingInterpolants(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L541-560 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryInterpolate(FVertexFactoryRayTracingInterpolants a, float aInterp, FVertexFactoryRayTracingInterpolants b, float bInterp)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L563-566 _function_ `uint VertexFactoryGetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L569-572 _function_ `uint GetNumRayTracingDynamicMeshVerticesIndirect()` _[#if RAYHITGROUPSHADER \|\| COMPUTESHADER]_
- L575-601 _function_ `FVertexFactoryInput LoadVertexFactoryInputFromIndices(uint TriangleIndex, int VertexIndex)`
- L604-613 _function_ `FVertexFactoryInput LoadVertexFactoryInputForHGS(uint TriangleIndex, int VertexIndex)` _[#if RAYHITGROUPSHADER]_
- L618-626 _function_ `FVertexFactoryInput LoadVertexFactoryInputForDynamicUpdate(uint TriangleIndex, int VertexIndex, uint PrimitiveId, uint DrawInstanceId)` _[#if COMPUTESHADER]_

#### Prototypes (2)

- L443 _prototype_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L444 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`

#### Top-level macro invocations (3)

- L79-81 _macro_call_ `VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`)
- L88-90 _macro_call_ `VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FPositionOnlyVertexFactoryInput`)
- L98-100 _macro_call_ `VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FPositionAndNormalOnlyVertexFactoryInput`)

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `EVertexFactoryFlags::UsedWithMaterials
	\| EVertexFactoryFlags::SupportsDynamicLighting
	\| EVertexFactoryFlags::SupportsPositionOnly
	\| EVertexFactoryFlags::SupportsRayTracingDynamicGeometry` → entry not found in file (macro-generated or #include'd); C++ `FLidarPointCloudVertexFactoryBase`  via IMPLEMENT_VERTEX_FACTORY_TYPE (Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Private/Rendering/LidarPointCloudRenderBuffers.cpp:426)
