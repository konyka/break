# Shaders / Shaders/Private/Substrate/Glint

- files: 1; lines: 954
- record kinds: define=9, function=15, member=5, struct=1

### `Shaders/Private/Substrate/Glint/GlintThirdParty.ush` (Private)

- lines: 954; parse: all-branches

#### Macros (#define, 9)

- L19 `#define InvSqrt2 0.707106f`
- L20 `#define MaxAnisotropy 4.0f`
- L22 `#define GlintSafeThreshold 0.000001f`
- L48 `#define FORCE_DISABLE_GLINTS_AA 0` _[#if !defined(FORCE_DISABLE_GLINTS_AA)]_
- L54 `#define USE_GLINT_AA (!RAYCALLABLESHADER && !RAYHITGROUPSHADER && !RAYGENSHADER && !RAYMISSSHADER && !FORCE_DISABLE_GLINTS_AA)`
- L57 `#define GGAAKernelSize 0.5`
- L58 `#define GGAAFilter 1`
- L59 `#define UseHemisDerivatives true`
- L778 `#define MAX_CELL_COUNT 64`
- L3 #pragma `once`

#### Structs / classes (1)

- L25-32 _struct_ **`FGlintLutParams`** `struct FGlintLutParams` — FGlintLutParams contains variables linked to the GlintShadingLUT
  - L27 _member_ `float Alpha;`
  - L28 _member_ `int N;`
  - L29 _member_ `int NLevels;`
  - L30 _member_ `float LevelBias;`
  - L31 _member_ `float LevelMin;`

#### Functions (15)

- L34-45 _function_ `FGlintLutParams GetGlintParams()`
- L61-65 _function_ `float3 SlopeToNormal(float2 Slope)`
- L70-81 _function_ `float non_axis_aligned_anisotropic_beckmann(float x, float y, float sigma_x, float sigma_y, float rho)`
- L86-116 _function_ `float erfinv(float x)`
- L123-129 _function_ `float hashIQ(uint n)`
- L134-137 _function_ `int pyramidSize(FGlintLutParams GlintLutParams, int level)`
- L142-146 _function_ `float sampleNormalDistribution(float U, float mu, float sigma)`
- L148-168 _function_ `float2 sampleBivariateNormalDistribution(float2 u, float sigmaX, float sigmaY, float rho)`
- L175-338 _function_ `float P22_M( FGlintLutParams GlintLutParams, float2 slope_h, int l, int s0, int t0, float2 slope_dx, float2 slope_dy, float3 sigma_x_y_rho, float l_dist, float MicrofacetRelativeArea)`
- L348-420 _function_ `float P22__glint_discrete_LOD( FGlintLutParams GlintLutParams, int l, float2 slope_h, float2 st, float2 dst0, float2 dst1, float2 slope_dx, float2 slope_dy, float3 sigma_x_y_rho, float l_dist, float MicrofacetRelativeArea)` — Most of this function is similar to pbrt-v3 EWA function, which itself is similar to Heckbert 1889 algorithm, http://www.cs.cmu.edu/~ph/texfund/texfund.pdf, Section 3.5.9. Go through cells within the pixel footprint for a givin LOD
- L425-579 _function_ `float f_P(float3 wo, float3 wi, float3 sigmas_rho, float GlintDensity, float2 TexCoord, float2 TexCoordDDX, float2 TexCoordDDY, bool bIncludeGeometryTerm=false)`
- L586-651 _function_ `float Sample_P_1D(FGlintLutParams GlintLutParams, float u, int ij, int l)` — Returns the ith 1D distribution at level l. It uses two random numbers: one for sampling the positive 1D distribution, the other to inverse the sign of the sampled value.
- L658-725 _function_ `float2 Sample_P22_M(FGlintLutParams GlintLutParams, float2 u01, int l, int s0, int t0, float3 sigma_x_y_rho, float l_dist)`
- L731-846 _function_ `float2 Sample_P22_LOD( FGlintLutParams GlintLutParams, float u0, float u1, float u2, int l, float2 st, float2 dst0, float2 dst1, float3 sigma_x_y_rho, float l_dist)` — Most of this function is similar to pbrt-v3 EWA function, which itself is similar to Heckbert 1889 algorithm, http://www.cs.cmu.edu/~ph/texfund/texfund.pdf, Section 3.5.9. Go through cells within the pixel footprint for a givin LOD
- L848-953 _function_ `float3 Sample_P(float3 u, float3 wo, float3 sigmas_rho, float LogMicrofacetDensity, float2 TexCoord, float2 TexCoordDDX, float2 TexCoordDDY)`
