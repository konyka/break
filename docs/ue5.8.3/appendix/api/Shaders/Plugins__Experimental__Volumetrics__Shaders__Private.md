# Shaders / Plugins/Experimental/Volumetrics/Shaders/Private

- files: 2; lines: 469
- record kinds: define=2, member=46, method=9, parameter=10, struct=3, unparsed=2

### `Plugins/Experimental/Volumetrics/Shaders/Private/TestCustomNode.ush` (Private)

- lines: 13; parse: all-branches; parse notes: 1
- L2 #pragma `once`

#### Structs / classes (1)

- L4-10 _struct_ **`StructExample`** `struct StructExample`
  - L6 _method_ `float AddValues(float inA, float inB)`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `StructExample MyStruct;`

#### Unparsed (raw text) (1)

- L13 _unparsed_ `return MyStruct.AddValues(A, B);`

<details><summary>parse notes</summary>

- L13: statement at declaration scope 'return MyStruct.AddValues(A, B)'

</details>

### `Plugins/Experimental/Volumetrics/Shaders/Private/VolumetricCloudFunctions.ush` (Private)

- lines: 456; parse: all-branches; parse notes: 1

#### Macros (#define, 2)

- L4 `#define UseDetailTexture 0`
- L5 `#define NumShadowSteps 16`
- L2 #pragma `once`

#### Structs / classes (2)

- L16-369 _struct_ **`CloudScene`** `struct CloudScene`
  - L19 _member_ `FMaterialPixelParameters Parameters;` — Params from Custom Node Input
  - L20 _member_ `float GroundRadius;`
  - L21 _member_ `float Steps;`
  - L22 _member_ `float DensityStep;`
  - L23 _member_ `float ShadowStep;`
  - L24 _member_ `Texture2D CloudMaskTexture;`
  - L25 _member_ `SamplerState CloudMaskTextureSampler;`
  - L26 _member_ `float CloudMaskScale;`
  - L27 _member_ `float CloudMaskBias;`
  - L28 _member_ `float2 OffsetXY;`
  - L29 _member_ `float CloudLayerAltitude;`
  - L30 _member_ `float CloudLayerThickness;`
  - L31 _member_ `float CloudUpperFalloff;`
  - L32 _member_ `float CloudLowerFalloff;`
  - L33 _member_ `Texture3D CloudVolumeTexture;`
  - L34 _member_ `SamplerState CloudVolumeTextureSampler;`
  - L35 _member_ `float DetailScale_a;`
  - L36 _member_ `float DetailAmount_a;`
  - L37 _member_ `float DetailMip_a;`
  - L38 _member_ `float DetailAltitudeShift_a;`
  - L39 _member_ `float DetailScale_b;`
  - L40 _member_ `float DetailAmount_b;`
  - L41 _member_ `float DetailMip_b;`
  - L42 _member_ `float3 SunColor;`
  - L43 _member_ `float3 SkyColor;`
  - L44 _member_ `float3 GroundColor;`
  - L45 _member_ `float InternalScatterBoost;`
  - L46 _member_ `float InternalScatterPower;`
  - L47 _member_ `float4 ScatterDensityOctaves;`
  - L48 _member_ `float4 ScatterIntensityOctaves;`
  - L49 _member_ `float3 Panner;`
  - L50 _member_ `float CloudDensity;`
  - L51 _member_ `float ShadowDensity;`
  - L52 _member_ `float AmbientDensity;`
  - L53 _member_ `float PowderDensity;`
  - L56 _member_ `float3 RO;` — View Setup
  - L57 _member_ `float3 RD;`
  - L58 _member_ `float3 LV;`
  - L59 _member_ `float SceneDepth;`
  - L60 _member_ `float TanHalfFOV;`
  - L61 _member_ `float VolumeResolution;`
  - L62 _member_ `float2 ViewSize;`
  - L65 _member_ `float3 LightEnergy;` — locals
  - L66 _member_ `float Transmittance;`
  - L67 _member_ `float accumdist;`
  - L69 _method_ `float3 SphereIntersection(float inRadius)`
  - L83 _method_ `float GetMipLevel(float RayDistance, float RepeatSize)`
  - L90 _method_ `float GetNormalizedRingDistance(float3 Pos, float ringnoise)`
  - L101 _method_ `float GetLayerFalloff(float3 Pos, float layernoise)`
  - L108 _method_ `float SampleCloudLayer(float3 inPos, float inDetailAmount)`
  - L135 _method_ `float4 RayMarch(float3 Pos, float3 Dir, int Steps, float MaxDist)`
  - L266 _method_ `float4 Render()`
- L371-451 _struct_ **`CloudSceneMaker`** `struct CloudSceneMaker`
  - L374 _member_ `CloudScene NewClouds;`
  - L376 _method_ `CloudScene MakeCloudLayer( FMaterialPixelParameters InParameters, float inPlanetRadius, float inSteps, float inStepSize, Texture2D inCloudMask, SamplerState inMaskSampler, float4 inCloudBaseParams, float4 inFalloffParams, Texture3D inVolTex, SamplerState inVolSampler, float4 inDetailParamsA, float4 inDetailParamsB, float3 inSunColor, float3 inSkyColor, float3 inGroundColor, float4 inScatteringParams, float3 inPanner, float4 inDensityParams, float3 inRO, float3 inRD, float3 inLV, float inSceneDepth, float inTanHalfFOV, float2 inViewSize)`

#### Global parameters (uniforms) (9)

- L7 _parameter_ `const float TanHalfFOV = 1;`
- L8 _parameter_ `const float3 SO = float3(0, 0, PlanetRadius);`
- L9 _parameter_ `const float3 RayOrigin = ResolvedView.WorldCameraOrigin + SO;`
- L10 _parameter_ `const float3 RayDirection = -Parameters.CameraVector;`
- L11 _parameter_ `const float3 LightVector = MaterialExpressionSkyAtmosphereLightDirection(Parameters, 0);`
- L13 _parameter_ `float SD = CalcSceneDepth(ScreenAlignedPosition(GetScreenPosition(Parameters))) / abs(dot(RayDirection, ResolvedView.ViewForward));`
- L14 _parameter_ `float2 ViewRes = View.ViewSizeAndInvSize.xy;`
- L453 _parameter_ `CloudSceneMaker CloudMaker;`
- L454 _parameter_ `CloudScene Clouds = CloudMaker.MakeCloudLayer(Parameters, PlanetRadius, MaxSteps, StepSize, CloudMask, CloudMaskSampler, CloudMaskParams, FalloffParams, VolumeTex, VolumeTexSampler, Detail1Params, Detail2Params, SunColor, SkyColor, GroundColor, ScatteringParams, Pan, DensityParams, RayOrigin, RayDirection, LightVector, SD, TanHalfFOV, ViewRes);`

#### Unparsed (raw text) (1)

- L456 _unparsed_ `return Clouds.Render();`

<details><summary>parse notes</summary>

- L456: statement at declaration scope 'return Clouds.Render()'

</details>
