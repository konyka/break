# Shaders / Shaders/Private/PathTracing/Material

- files: 16; lines: 3496
- record kinds: define=20, function=82, include=50, member=110, method=10, struct=12

### `Shaders/Private/PathTracing/Material/FirstBounceRayGuidingCommon.ush` (Private)

- lines: 14; parse: all-branches

#### Macros (#define, 6)

- L5 `#define USE_FIRST_BOUNCE_RAY_GUIDING 0` _[#if !defined(USE_FIRST_BOUNCE_RAY_GUIDING)]_
- L8 `#define TEXEL_CLUSTER_SIZE 8`
- L9 `#define NUM_CLUSTERS_PER_DIM (64 / TEXEL_CLUSTER_SIZE)`
- L10 `#define NUM_CLUSTERS_PER_TILE (64 * 64 / (TEXEL_CLUSTER_SIZE * TEXEL_CLUSTER_SIZE))`
- L12 `#define DIRECTIONAL_BINS_ONE_DIM 16`
- L13 `#define CDF_TILE_SIZE (NUM_CLUSTERS_PER_DIM * DIRECTIONAL_BINS_ONE_DIM)`
- L2 #pragma `once`

### `Shaders/Private/PathTracing/Material/PathTracingEnergyConservation.ush` (Private)

- lines: 5; parse: all-branches
- includes: L5 `../../ShadingEnergyConservation.ush`
- L3 #pragma `once`

### `Shaders/Private/PathTracing/Material/PathTracingEye.ush` (Private)

- lines: 170; parse: all-branches
- includes: L9 `PathTracingMaterialCommon.ush`, L10 `PathTracingFresnel.ush`, L11 `PathTracingEnergyConservation.ush`
- L7 #pragma `once`

#### Structs / classes (1)

- L13-22 _struct_ **`FEyeData`** `struct FEyeData`
  - L15 _member_ `float3x3 Basis;`
  - L16 _member_ `float2 Alpha;`
  - L17 _member_ `float3 V;`
  - L19 _member_ `FBxDFEnergyTermsRGB Spec;`
  - L20 _member_ `float3 DiffWeight;`
  - L21 _member_ `float LobeProb;`

#### Functions (3)

- L24-41 _function_ `FEyeData PrepareEyeData(FPathTracingPayload Payload, float3 V_World)`
- L43-89 _function_ `FMaterialEval Eye_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`
- L91-169 _function_ `FMaterialSample Eye_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample )`

### `Shaders/Private/PathTracing/Material/PathTracingFresnel.ush` (Private)

- lines: 179; parse: all-branches

#### Macros (#define, 1)

- L122 `#define CLEAR_COAT_F0 0.04`
- L6 #pragma `once`

#### Structs / classes (1)

- L131-135 _struct_ **`FThinSlabWeights`** `struct FThinSlabWeights`
  - L133 _member_ `float3 Reflected;`
  - L134 _member_ `float3 Transmitted;`

#### Functions (7)

- L12-30 _function_ `float FresnelReflectance(float CosI, float Eta)`
- L33-50 _function_ `float FresnelReflectance(float CosI, float Eta, float F0)` — TIR handled by Eta parameter, reflectivity by F0
- L53-86 _function_ `bool SampleRefraction(float3 RayDirection, float3 Normal, float Eta, float RandSample, out float3 OutDirection, out float OutFresnel)` — returns true if we sampled a refraction, or false if we reflected (or TIR occured)
- L89-119 _function_ `bool SampleRefraction(float3 RayDirection, float3 Normal, float Eta, float F0, float RandSample, out float3 OutDirection, out float OutFresnel)` — Sample refraction where bending is driven by Eta and reflectivity by F0
- L124-128 _function_ `float ClearCoatFresnel(float VoH)`
- L139-172 _function_ `FThinSlabWeights ComputeThinSlabWeights(float3 SlabColor, float CosV, float Eta, float F0)` — return the amount of reflected and transmitted energy for an infinite slab viewed from a particular direction taking into account the (repeated) Fresnel terms and the transmittance through the slab
- L174-178 _function_ `float ComputeThinTransmittedRoughness(float Roughness, float Ior)`

### `Shaders/Private/PathTracing/Material/PathTracingGlossy.ush` (Private)

- lines: 127; parse: all-branches
- includes: L9 `../../BRDF.ush`, L10 `../../MonteCarlo.ush`

#### Macros (#define, 2)

- L13 `#define GGX_MIN_ROUGHNESS 0.01`
- L14 `#define GGX_MIN_ANISOTROPY 0.001`
- L7 #pragma `once`

#### Functions (6)

- L16-20 _function_ `float2 GetGGXAlpha(float Roughness)`
- L22-35 _function_ `float2 GetGGXAlpha(float Roughness, float Anisotropy)`
- L37-61 _function_ `float3x3 GetGGXBasis(float Roughness, float Anisotropy, float3 WorldNormal, float3 WorldTangent, out float2 Alpha)`
- L63-69 _function_ `float3x3 GetGGXBasis(float Roughness, float3 WorldNormal, out float2 Alpha)`
- L72-100 _function_ `float2 GGXEvalReflection(float3 L, float3 V, float3 H, float2 Alpha, bool bLimitVDNFToReflection = true)` — Compute GGX lobe Weight and Pdf (without Fresnel term) given a set of vectors in local space (Z up)
- L103-126 _function_ `float2 GGXEvalRefraction(float3 L, float3 V, float3 H, float2 Alpha, float Eta)` — Compute GGX lobe Weight and Pdf (without Fresnel term) given a set of vectors in local space (Z up)

### `Shaders/Private/PathTracing/Material/PathTracingHair.ush` (Private)

- lines: 409; parse: all-branches
- includes: L5 `PathTracingMaterialCommon.ush`

#### Macros (#define, 1)

- L7 `#define PATH_TRACER_HAIR_SHADING_MODEL 1`
- L3 #pragma `once`

#### Structs / classes (1)

- L188-206 _struct_ **`FHairData`** `struct FHairData` — precomputed terms for evaluating/sampling the hair bxdf TODO: can we somehow do this stuff only once instead of repeating it in eval and sample? _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L191 _member_ `float4 SinThetaO;` — trig that only depends on viewing direction and offset h _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L192 _member_ `float GammaO;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L193 _member_ `float GammaT;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L195 _member_ `float v0;` — roughness parameter for Mp _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L196 _member_ `float v1;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L197 _member_ `float v2;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L198 _member_ `float v3;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L199 _member_ `float s;` — azimuthal roughness parameter for Np _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L200 _member_ `float A0;` — attenuation term per lobe (first one is always white) _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L201 _member_ `float3 A1;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L202 _member_ `float3 A2;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L203 _member_ `float3 A3;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L204 _member_ `float4 LobePdf;` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
  - L205 _member_ `float3 LobeCdf;` — Normalized sum to help select a lobe _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_

#### Functions (16)

- L14-17 _function_ `float3 GetHairTangent(in const FPathTracingPayload Payload)` — wrapper function to get hair strand direction, it is encoded in 'WorldSmoothNormal' in offline path tracer
- L19-28 _function_ `float3x3 GetHairBasis(float3 T_World, float3 V_World)`
- L33-52 _function_ `float ZinkeHairDiffuse(float3 L)` _[#if PATH_TRACER_HAIR_SHADING_MODEL == 0]_
- L54-76 _function_ `FMaterialSample Hair_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample)` _[#if PATH_TRACER_HAIR_SHADING_MODEL == 0]_
- L78-91 _function_ `FMaterialEval Hair_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )` _[#if PATH_TRACER_HAIR_SHADING_MODEL == 0]_
- L103-124 _function_ `float LogI0(float x)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L126-133 _function_ `float FastASin(float x)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L135-146 _function_ `float Mp(float SinThetaI, float SinThetaO, float v)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L148-155 _function_ `float TrimmedLogistic(float x, float InvS)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L157-163 _function_ `float SampleTrimmedLogistic(float x, float s)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L165-168 _function_ `float Phi(int p, float GammaO, float GammaT)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L170-178 _function_ `float Np(float phi, int p, float InvS, float GammaO, float GammaT)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L181-184 _function_ `float TrigInverse(float x)` — returns sine from cosine (or vice-versa) _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L208-293 _function_ `FHairData PrepareHairData(float3 V, float3 Color, float LongitudinalRoughness, float AzimuthalRoughness, float h, float Specular)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L295-369 _function_ `FMaterialSample Hair_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample)` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_
- L371-406 _function_ `FMaterialEval Hair_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )` _[#if !(PATH_TRACER_HAIR_SHADING_MODEL == 0) && PATH_TRACER_HAIR_SHADING_MODEL == 1]_

### `Shaders/Private/PathTracing/Material/PathTracingLambert.ush` (Private)

- lines: 91; parse: all-branches
- L6 #pragma `once`

#### Functions (4)

- L8-25 _function_ `FMaterialSample Lambert_SampleMaterial( FPathTracingPayload Payload, float3 RandSample)`
- L27-44 _function_ `FMaterialEval Lambert_EvalMaterial( float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`
- L48-66 _function_ `FMaterialSample Simplified_SampleMaterial( FPathTracingPayload Payload, float3 RandSample)` _[#if SIMPLIFIED_MATERIAL_SHADER]_
- L68-88 _function_ `FMaterialEval Simplified_EvalMaterial( float3 L_World, FPathTracingPayload Payload )` _[#if SIMPLIFIED_MATERIAL_SHADER]_

### `Shaders/Private/PathTracing/Material/PathTracingMaterialCommon.ush` (Private)

- lines: 214; parse: all-branches
- includes: L9 `/Engine/Private/MonteCarlo.ush`, L10 `/Engine/Private/BRDF.ush`

#### Macros (#define, 6)

- L82 `#define PATHTRACER_SCATTER_CAMERA 0`
- L83 `#define PATHTRACER_SCATTER_DIFFUSE 1`
- L84 `#define PATHTRACER_SCATTER_SPECULAR 2`
- L85 `#define PATHTRACER_SCATTER_REFRACT 3`
- L86 `#define PATHTRACER_SCATTER_VOLUME 4`
- L147 `#define PATH_TRACER_SHADOW_TERMINATOR 1`
- L7 #pragma `once`

#### Structs / classes (2)

- L88-101 _struct_ **`FMaterialSample`** `struct FMaterialSample`
  - L90 _member_ `float3 Direction;`
  - L91 _member_ `float3 Weight;`
  - L92 _member_ `float Pdf;`
  - L93 _member_ `float PositionBiasSign;`
  - L94 _member_ `float Roughness;`
  - L95 _member_ `int ScatterType;`
  - L97 _method_ `void AddLobeWithMIS(float3 LobeWeight, float LobePdf, float LobeProb)`
- L121-130 _struct_ **`FMaterialEval`** `struct FMaterialEval`
  - L123 _member_ `float3 Weight;`
  - L124 _member_ `float Pdf;`
  - L126 _method_ `void AddLobeWithMIS(float3 LobeWeight, float LobePdf, float LobeProb)`

#### Functions (13)

- L12-22 _function_ `float LobeColorToWeight(float3 C)`
- L26-32 _function_ `float LobeSelectionProb(float3 A, float3 B)` — Given two lobes that will roughly contribute colors A and B to the total (estimated for example using directional albedo) return the probability of choosing lobe A
- L37-49 _function_ `float2 LobeSelectionCdf(float3 A, float3 B, float3 C)` — Given three lobes that will roughly contribute colors A, B and C to the total (estimated for example using directional albedo) return a CDF for choosing lobe A, B or C The individual probabilities of each lobe can be estimated using LobeSelectionPdf.
- L52-66 _function_ `float3 LobeSelectionCdf(float3 A, float3 B, float3 C, float3 D)` — Same as above for choosing among 4 colored lobes
- L69-72 _function_ `float3 LobeSelectionPdf(float2 LobeCdf)` — Given the CDF for a choice between three lobes (as returned by LobeSelectionCdf above), compute the Pdf for each individual lobe
- L75-78 _function_ `float4 LobeSelectionPdf(float3 LobeCdf)` — Given the CDF for a choice between four lobes (as returned by LobeSelectionCdf above), compute the Pdf for each individual lobe
- L103-107 _function_ `FMaterialSample NullMaterialSample()`
- L109-119 _function_ `FMaterialSample CreateMaterialSample(float3 Direction, float3 Weight, float Pdf, float PositionBiasSign, float Roughness, int ScatterType)`
- L132-135 _function_ `FMaterialEval NullMaterialEval()`
- L137-143 _function_ `FMaterialEval CreateMaterialEval(float3 Weight, float Pdf)`
- L149-190 _function_ `float ShadowTerminatorTerm(float3 L, float3 N, float3 Ns)`
- L192-200 _function_ `float3 GetPathTracingDiffuseModel(float3 DiffuseColor, float Roughness, float NoV, float NoL, float VoH, float NoH)`
- L203-214 _function_ `void AdjustPathTracingTwoSidedColorBalance(inout float3 FrontColor, inout float3 BackColor)` — Given two diffuse colors as found on either SHADINGMODELID_TWOSIDED_FOLIAGE or SHADINGMODELID_SUBSURFACE, balance them out to ensure they don't reflect more than 100% energy

### `Shaders/Private/PathTracing/Material/PathTracingMaterialSampling.ush` (Private)

- lines: 416; parse: all-branches
- includes: L9 `PathTracingMaterialCommon.ush`, L10 `PathTracingFresnel.ush`, L11 `PathTracingLambert.ush`, L13 `PathTracingGlossy.ush` [!SIMPLIFIED_MATERIAL_SHADER], L14 `PathTracingSubstrate.ush` [!SIMPLIFIED_MATERIAL_SHADER], L15 `PathTracingSubstrateFoliage.ush` [!SIMPLIFIED_MATERIAL_SHADER], L16 `PathTracingSubstrateSolidGlass.ush` [!SIMPLIFIED_MATERIAL_SHADER], L17 `PathTracingSubstrateThinGlass.ush` [!SIMPLIFIED_MATERIAL_SHADER], L18 `PathTracingEye.ush` [!SIMPLIFIED_MATERIAL_SHADER], L19 `PathTracingHair.ush` [!SIMPLIFIED_MATERIAL_SHADER], L20 `PathTracingMedium.ush` [!SIMPLIFIED_MATERIAL_SHADER]

#### Macros (#define, 1)

- L83 `#define ROUGHNESS_WEIGHT(r) DenoiserRoughnessWeight(r, PathRoughness)` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
- L7 #pragma `once`; L169 #undef `ROUGHNESS_WEIGHT`

#### Structs / classes (1)

- L292-299 _struct_ **`FSSSRandomWalkInfo`** `struct FSSSRandomWalkInfo` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
  - L294 _member_ `float3 Color;` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
  - L295 _member_ `float3 Radius;` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
  - L296 _member_ `float3 Weight;` — multiplier for the path throughput to take into account energy conservation from specular above the SSS _[#if !SIMPLIFIED_MATERIAL_SHADER]_
  - L297 _member_ `float Prob;` — probability of choosing to perform the random walk _[#if !SIMPLIFIED_MATERIAL_SHADER]_
  - L298 _member_ `float G;` _[#if !SIMPLIFIED_MATERIAL_SHADER]_

#### Functions (10)

- L23-79 _function_ `float3 EstimateMaterialAlbedo(FPathTracingPayload Payload)`
- L85-168 _function_ `void AccumulateAlbedoNormal(inout FPathTracingPayload Payload, float3 PathThroughput, float PathRoughness, inout float3 Albedo, inout float3 Normal)` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
- L171-176 _function_ `void AccumulateAlbedo(float3 SigmaS, float3 PathThroughput, float PathRoughness, inout float3 Albedo)` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
- L181-229 _function_ `float GetAverageRoughness(FPathTracingPayload Payload)` — returns an average roughness for the whole material (for the path roughness of shadow rays from this material)
- L231-239 _function_ `void AdjustDiffuseSSSContribution(inout float3 DiffColor, inout float3 SSSColor, inout float3 Radius)`
- L242-290 _function_ `void AdjustPayloadAfterUnpack(inout FPathTracingPayload HitPayload, bool bApplyOverrides)` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
- L302-330 _function_ `FSSSRandomWalkInfo GetMaterialSSSInfo(FPathTracingPayload Payload, float3 V_World)` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
- L332-339 _function_ `void RemoveMaterialSSS(inout FPathTracingPayload Payload)` _[#if !SIMPLIFIED_MATERIAL_SHADER]_
- L344-378 _function_ `FMaterialSample SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample )`
- L380-415 _function_ `FMaterialEval EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`

### `Shaders/Private/PathTracing/Material/PathTracingMedium.ush` (Private)

- lines: 161; parse: all-branches
- includes: L12 `../../ParticipatingMediaCommon.ush`

#### Macros (#define, 1)

- L14 `#define USE_UNIFORM_PHASE_FUNCTION 0`
- L10 #pragma `once`

#### Functions (4)

- L16-77 _function_ `FMaterialSample Medium_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample)`
- L79-112 _function_ `FMaterialEval Medium_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`
- L116-139 _function_ `FMaterialSample Volumetric_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample)`
- L141-160 _function_ `FMaterialEval Volumetric_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`

### `Shaders/Private/PathTracing/Material/PathTracingRadianceProbe.ush` (Private)

- lines: 249; parse: all-branches
- includes: L11 `FirstBounceRayGuidingCommon.ush` [1 && defined(LIGHTMAP_PATH_TRACING_MAIN_RG)]
- L6 #pragma `once`

#### Functions (5)

- L14-49 _function_ `float2 InverseConcentricMapping(float2 p)` _[#if 1]_
- L51-140 _function_ `FMaterialSample RadianceProbe_SampleMaterial( FPathTracingPayload Payload, float3 RandSample )` _[#if 1]_
- L142-223 _function_ `FMaterialEval RadianceProbe_EvalMaterial( float3 L_World, FPathTracingPayload Payload )` _[#if 1]_
- L227-236 _function_ `FMaterialSample RadianceProbe_SampleMaterial( FPathTracingPayload Payload, float3 RandSample)` _[#if !(1)]_
- L238-247 _function_ `FMaterialEval RadianceProbe_EvalMaterial( float3 L_World, FPathTracingPayload Payload )` _[#if !(1)]_

### `Shaders/Private/PathTracing/Material/PathTracingSubstrate.ush` (Private)

- lines: 525; parse: all-branches
- includes: L5 `PathTracingEnergyConservation.ush`, L6 `PathTracingSubstrateCommon.ush`, L7 `PathTracingMaterialCommon.ush`, L8 `PathTracingGlossy.ush`, L9 `PathTracingFresnel.ush`, L10 `../../BRDF.ush`
- L3 #pragma `once`

#### Structs / classes (2)

- L12-68 _struct_ **`FSubstrateSingleSlabData`** `struct FSubstrateSingleSlabData`
  - L14 _member_ `float3x3 Basis;`
  - L15 _member_ `float3 V;`
  - L17 _member_ `float DiffuseWeight;`
  - L18 _member_ `float3 F0;`
  - L19 _member_ `float3 F90;`
  - L20 _member_ `float2 Alpha0;`
  - L21 _member_ `float2 Alpha1;`
  - L22 _member_ `float3 Spec0W;`
  - L23 _member_ `float3 Spec1W;`
  - L24 _member_ `FSubstrateSheenData Fuzz;`
  - L26 _member_ `float3 LobeCdf;`
  - L27 _member_ `float4 LobePdf;`
  - L29 _method_ `void PrepareBSDF(float3 V_World, FPathTracingPayload Payload, bool bUseSSSColor = false)`
- L247-317 _struct_ **`FSubstrateClearCoatData`** `struct FSubstrateClearCoatData`
  - L249 _member_ `float3x3 BaseBasis;`
  - L250 _member_ `float3x3 CoatBasis;`
  - L252 _member_ `float3 BaseV;`
  - L253 _member_ `float3 CoatV;`
  - L255 _member_ `float DiffuseWeight;`
  - L256 _member_ `float3 F0;`
  - L257 _member_ `float3 F90;`
  - L258 _member_ `float2 BaseAlpha;`
  - L259 _member_ `float2 CoatAlpha;`
  - L261 _member_ `float CoatAttenuation;`
  - L262 _member_ `FBxDFEnergyTermsRGB BaseSpec;`
  - L263 _member_ `FBxDFEnergyTermsA CoatSpec;`
  - L264 _member_ `FSubstrateSheenData Fuzz;`
  - L266 _member_ `float3 LobeCdf;`
  - L267 _member_ `float4 LobePdf;`
  - L269 _method_ `void PrepareBSDF(float3 V_World, FPathTracingPayload Payload, bool bUseSSSColor = false)`

#### Functions (4)

- L70-187 _function_ `FMaterialSample Substrate_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample )`
- L189-245 _function_ `FMaterialEval Substrate_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`
- L321-447 _function_ `FMaterialSample SubstrateClearCoat_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample )`
- L450-524 _function_ `FMaterialEval SubstrateClearCoat_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`

### `Shaders/Private/PathTracing/Material/PathTracingSubstrateCommon.ush` (Private)

- lines: 140; parse: all-branches
- includes: L5 `../PathTracingCommon.ush`, L6 `../../BRDF.ush`, L11 `/Engine/Private/Substrate/Glint/GlintThirdParty.ush` [SUBSTRATE_PATH_TRACING_GLINTS]

#### Macros (#define, 2)

- L8 `#define SUBSTRATE_FRESNEL_F82 0`
- L50 `#define USE_SHEEN_LTC_SAMPLER 1`
- L3 #pragma `once`

#### Structs / classes (1)

- L53-131 _struct_ **`FSubstrateSheenData`** `struct FSubstrateSheenData`
  - L55 _member_ `float2 Tangent;` — Captures rotation within the local tangent frame
  - L56 _member_ `float aInv;` — LTC Coefficients
  - L57 _member_ `float bInv;`
  - L58 _member_ `float Scale;` — overall scale factor for the sheen lobe
  - L59 _member_ `float Attenuation;` — amount by which other lobes have to be scaled
  - L61 _method_ `void Prepare(float3 V, float FuzzRoughness, float FuzzAmount)`
  - L83 _method_ `float4 Eval(float3 L, float3 V, float3 H, float3 FuzzColor)`
  - L117 _method_ `float3 Sample(float2 Rand)`

#### Functions (4)

- L14-20 _function_ `float3 SubstrateLobeWeight(FPathTracingPayload Payload, float SatNoL)`
- L22-33 _function_ `float3 SubstrateSpecularTint(FPathTracingPayload Payload, float NoV, float NoL, float VoH, float NoH)`
- L35-48 _function_ `void SubstrateGlint(FPathTracingPayload Payload, float3 InTangentV, float3 InTangentL, float2 InAlphaXY, in float InPdf, inout float OutWeight)`
- L133-139 _function_ `FBxDFEnergyTermsA ComputeSheenEnergyTerms(float NoV, float SheenRoughness)`

### `Shaders/Private/PathTracing/Material/PathTracingSubstrateFoliage.ush` (Private)

- lines: 257; parse: all-branches
- includes: L5 `PathTracingEnergyConservation.ush`, L6 `PathTracingSubstrateCommon.ush`, L7 `PathTracingMaterialCommon.ush`, L8 `PathTracingGlossy.ush`, L9 `PathTracingFresnel.ush`, L10 `../../BRDF.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L12-71 _struct_ **`FSubstrateFoliageSlabData`** `struct FSubstrateFoliageSlabData`
  - L14 _member_ `float3x3 Basis;`
  - L15 _member_ `float3 V;`
  - L17 _member_ `float DiffuseWeight;`
  - L18 _member_ `float TransmissionProb;` — for sampling the transmission lobe
  - L19 _member_ `float3 F0;`
  - L20 _member_ `float3 F90;`
  - L21 _member_ `float2 Alpha0;`
  - L22 _member_ `float2 Alpha1;`
  - L23 _member_ `float3 Spec0W;`
  - L24 _member_ `float3 Spec1W;`
  - L25 _member_ `FSubstrateSheenData Fuzz;`
  - L27 _member_ `float3 LobeCdf;`
  - L28 _member_ `float4 LobePdf;`
  - L30 _method_ `void PrepareBSDF(float3 V_World, FPathTracingPayload Payload)`

#### Functions (2)

- L74-189 _function_ `FMaterialSample SubstrateFoliage_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample )`
- L191-257 _function_ `FMaterialEval SubstrateFoliage_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`

### `Shaders/Private/PathTracing/Material/PathTracingSubstrateSolidGlass.ush` (Private)

- lines: 246; parse: all-branches
- includes: L5 `PathTracingEnergyConservation.ush`, L6 `PathTracingSubstrateCommon.ush`, L7 `PathTracingMaterialCommon.ush`, L8 `PathTracingGlossy.ush`, L9 `PathTracingFresnel.ush`, L10 `../../BRDF.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L13-63 _struct_ **`FSubstrateSolidGlassSlabData`** `struct FSubstrateSolidGlassSlabData`
  - L15 _member_ `float3x3 Basis;`
  - L16 _member_ `float3 V;`
  - L18 _member_ `float F0;`
  - L19 _member_ `float Eta;`
  - L20 _member_ `float2 Alpha0;`
  - L21 _member_ `float2 Alpha1;`
  - L23 _member_ `float EGlass0;`
  - L24 _member_ `float EGlass1;`
  - L26 _member_ `FSubstrateSheenData Fuzz;`
  - L28 _member_ `float2 LobeCdf;`
  - L29 _member_ `float3 LobePdf;`
  - L31 _method_ `void PrepareBSDF(float3 V_World, FPathTracingPayload Payload)`

#### Functions (2)

- L66-172 _function_ `FMaterialSample SubstrateSolidGlass_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample )`
- L175-245 _function_ `FMaterialEval SubstrateSolidGlass_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`

### `Shaders/Private/PathTracing/Material/PathTracingSubstrateThinGlass.ush` (Private)

- lines: 293; parse: all-branches
- includes: L5 `PathTracingEnergyConservation.ush`, L6 `PathTracingSubstrateCommon.ush`, L7 `PathTracingMaterialCommon.ush`, L8 `PathTracingGlossy.ush`, L9 `PathTracingFresnel.ush`, L10 `../../BRDF.ush`, L11 `../../ParticipatingMediaCommon.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L14-90 _struct_ **`FSubstrateThinGlassSlabData`** `struct FSubstrateThinGlassSlabData`
  - L16 _member_ `float3x3 Basis;`
  - L17 _member_ `float3 V;`
  - L19 _member_ `float2 RoughnessT;`
  - L21 _member_ `float DiffuseWeight;`
  - L22 _member_ `float F0, F90;`
  - L22 _member_ `float F0, F90;`
  - L23 _member_ `float Eta;`
  - L24 _member_ `float3 TransmissionColor;`
  - L25 _member_ `float2 AlphaR0, AlphaT0;`
  - L25 _member_ `float2 AlphaR0, AlphaT0;`
  - L26 _member_ `float2 AlphaR1, AlphaT1;`
  - L26 _member_ `float2 AlphaR1, AlphaT1;`
  - L28 _member_ `float SpecR0W, SpecR1W;`
  - L28 _member_ `float SpecR0W, SpecR1W;`
  - L29 _member_ `float SpecT0W, SpecT1W;`
  - L29 _member_ `float SpecT0W, SpecT1W;`
  - L31 _member_ `FSubstrateSheenData Fuzz;`
  - L33 _member_ `float3 LobeCdf;`
  - L34 _member_ `float4 LobePdf;`
  - L36 _method_ `void PrepareBSDF(float3 V_World, FPathTracingPayload Payload)`

#### Functions (2)

- L92-224 _function_ `FMaterialSample SubstrateThinGlass_SampleMaterial( float3 V_World, FPathTracingPayload Payload, float3 RandSample )`
- L227-292 _function_ `FMaterialEval SubstrateThinGlass_EvalMaterial( float3 V_World, float3 L_World, FPathTracingPayload Payload, float2 DiffuseSpecularScale )`
