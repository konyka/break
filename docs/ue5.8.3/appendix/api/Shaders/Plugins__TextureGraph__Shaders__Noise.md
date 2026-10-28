# Shaders / Plugins/TextureGraph/Shaders/Noise

- files: 4; lines: 659
- record kinds: define=5, function=19, include=3, member=6, static_const=4, static_var=1, struct=1

### `Plugins/TextureGraph/Shaders/Noise/Noise_Common.ush` (Other)

- lines: 29; parse: all-branches

#### Structs / classes (1)

- L21-29 _struct_ **`FBMDesc`** `struct FBMDesc` — Standard struct of properties to configure a FBM (fractal brownian motion) Noise sum regardless of the noise function used
  - L23 _member_ `float Seed;`
  - L24 _member_ `float Amplitude;`
  - L25 _member_ `float Frequency;`
  - L26 _member_ `int Octaves;`
  - L27 _member_ `float Lacunarity;`
  - L28 _member_ `float Persistance;`

#### static const (2)

- L5 _static_const_ `static const float TWO_PI = 2.0 * 3.14159265358979323846f;`
- L6 _static_const_ `static const float TWO_PI_INV = 1.0f / TWO_PI;`

#### Functions (1)

- L9-17 _function_ `float4 Make4DNoiseCoord(float2 uv)` — Make a 4D coordinate from a 2d uv coordinate

### `Plugins/TextureGraph/Shaders/Noise/Noise_Perlin.ush` (Other)

- lines: 144; parse: all-branches
- includes: L3 `/Plugin/TextureGraph/Noise/Noise_Common.ush`

#### Macros (#define, 3)

- L5 `#define FADE(t) ( t * t * t * ( t * ( t * 6 - 15 ) + 10 ) )`
- L7 `#define FASTFLOOR(x) ( ((x)>0) ? ((int)x) : ((int)x-1 ) )`
- L8 `#define LERP(t, a, b) ((a) + (t)*((b)-(a)))`

#### static const (1)

- L10-18 _static_const_ `static const uint PermutationTable[64] = { 1535746199, 226692954, 895508425, 3775392194, 510076044, 1661505093, 169209893, 2483469847, 1273657591, 1053104640, 3420191838, 537600885, 1478603065, 1463326189, 2289898670, 2940512427, 2252842314, 2786799755, 3885929037, 2061856595, 3867530044, 693922268, 687156791, 915367668, 2705267009, 1230034945, 3146009809, 2836552144, 2189935816, 1453309044, 3329057956, 1073986221, 4209170740, 3389356924, 2121700134, 3562361599, 3812347599, 289017903, 706526646, 3584735199, 43579511, 1185126956, 2607127005, 162278311, 4247197313, 1852596755, 3907023183, 175221`

#### Functions (4)

- L20-26 _function_ `uint permF(uint x)`
- L28-34 _function_ `float grad4(int hash, float x, float y, float z, float t)`
- L36-119 _function_ `float Perlin4D(float4 coord)`
- L122-144 _function_ `float FBM_Perlin4D(float2 uv, FBMDesc fbm)`

### `Plugins/TextureGraph/Shaders/Noise/Noise_Simplex.ush` (Other)

- lines: 309; parse: all-branches
- includes: L22 `/Plugin/TextureGraph/Noise/Noise_Common.ush`

#### static const (1)

- L43-51 _static_const_ `const static uint PermutationTable[64] = { 1535746199, 226692954, 895508425, 3775392194, 510076044, 1661505093, 169209893, 2483469847, 1273657591, 1053104640, 3420191838, 537600885, 1478603065, 1463326189, 2289898670, 2940512427, 2252842314, 2786799755, 3885929037, 2061856595, 3867530044, 693922268, 687156791, 915367668, 2705267009, 1230034945, 3146009809, 2836552144, 2189935816, 1453309044, 3329057956, 1073986221, 4209170740, 3389356924, 2121700134, 3562361599, 3812347599, 289017903, 706526646, 3584735199, 43579511, 1185126956, 2607127005, 162278311, 4247197313, 1852596755, 3907023183, 175221`

#### static variables (1)

- L72-106 _static_var_ `static float4 grad4F2[32] = { float4(0, 1, 1, 1), float4(0, 1, 1, -1), float4(0, 1, -1, 1), float4(0, 1, -1, -1), float4(0, -1, 1, 1), float4(0, -1, 1, -1), float4(0, -1, -1, 1), float4(0, -1, -1, -1), float4(1, 0, 1, 1), float4(1, 0, 1, -1), float4(1, 0, -1, 1), float4(1, 0, -1, -1), float4(-1, 0, 1, 1), float4(-1, 0, 1, -1), float4(-1, 0, -1, 1), float4(-1, 0, -1, -1), float4(1, 1, 0, 1), float4(1, 1, 0, -1), float4(1, -1, 0, 1), float4(1, -1, 0, -1), float4(-1, 1, 0, 1), float4(-1, 1, 0, -1), float4(-1, -1, 0, 1), float4(-1, -1, 0, -1), float4(1, 1, 1, 0), float4(1, 1, -1, 0), float4(1, -1,`

#### Functions (6)

- L53-59 _function_ `uint permF(uint x)`
- L62-65 _function_ `float dot(int g[4], float x, float y, float z, float w)`
- L67-70 _function_ `float dotF(float4 g, float x, float y, float z, float w)`
- L108-111 _function_ `float4 grad4F(int index)`
- L117-282 _function_ `float Simplex4D(float4 coord)`
- L285-307 _function_ `float FBM_Simplex4D(float2 uv, FBMDesc fbm)`

### `Plugins/TextureGraph/Shaders/Noise/Noise_Voronoise.ush` (Other)

- lines: 177; parse: all-branches
- includes: L2 `/Plugin/TextureGraph/Noise/Noise_Common.ush`

#### Macros (#define, 2)

- L5 `#define K 0.142857142857`
- L7 `#define Ko 0.428571428571`

#### Functions (8)

- L10 _function_ `float4 mod(float4 x, float y)`
- L11 _function_ `float3 mod(float3 x, float y)`
- L14-17 _function_ `float3 Permutation(float3 x)` — Permutation polynomial: (34x^2 + x) mod 289
- L20-74 _function_ `float2 Voronoise4D(float4 P, float jitter)`
- L76-82 _function_ `float FrequencyRemap(float freq)`
- L84-114 _function_ `float FBM_Voronoise4D_F0_Squared(float2 uv, FBMDesc fbm)`
- L116-145 _function_ `float FBM_Voronoise4D_F1_Squared(float2 uv, FBMDesc fbm)`
- L147-177 _function_ `float FBM_Voronoise4D_F1_F0_Squared(float2 uv, FBMDesc fbm)`
