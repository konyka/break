# Shaders / Plugins/Interchange/Assets/Shaders

- files: 1; lines: 115
- record kinds: function=9

### `Plugins/Interchange/Assets/Shaders/ThinFilmFunctions.usf` (Other)

- lines: 115; parse: all-branches
- L3 #pragma `once`

#### Functions (9)

- L5-15 _function_ `float3 ThinFilmEvalSensitivityA(float opd, float shift)`
- L17-45 _function_ `void ThinFilmFresnelDielectricA( in float ct1, in float n1, in float n2, out float2 R, out float2 phi)`
- L47-72 _function_ `void ThinFilmFresnelConductorA( in float ct1, in float n1, in float n2, in float k, out float2 R, out float2 phi)`
- L76-90 _function_ `void ComputeComplexIORFromF0AndEdgeTintA( in float3 Reflectivity, in float3 EdgeTint, inout float3 n, inout float3 k)` — [Gulbrandsen, "Artist Friendly Metallic Fresnel"] Compute complex index of refraction N = n + ik from F0 and edge tint.
- L92 _function_ `float ThinFilmDepolA(float2 polV)`
- L93 _function_ `float3 ThinFilmDepolColorA(float3 colS, float3 colP)`
- L95-99 _function_ `float3 SchlickB(float3 F0, float3 F90, float VoH)`
- L101-108 _function_ `float3 SchlickA( float3 SpecularColor, float VoH )`
- L110-115 _function_ `float DielectricToF0A(float Ior)`
