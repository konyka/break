# Shaders / Plugins/Experimental/WaterAdvanced/Shaders

- files: 1; lines: 174
- record kinds: function=8, static_const=1

### `Plugins/Experimental/WaterAdvanced/Shaders/WaterAdvanced.ush` (Other)

- lines: 174; parse: all-branches
- L7 #pragma `once`

#### static const (1)

- L9 _static_const_ `static const float TWOPI = 2. * PI;`

#### Functions (8)

- L11-42 _function_ `void BracketAngle(float2 Velocity, float BracketAngleDelta, out float2 VelocityDir0, out float2 VelocityDir1, out float BlendAlpha)`
- L45-61 _function_ `void BracketValue(float Value, float BracketMagnitudeDelta, out float Value0, out float Value1, out float BlendAlpha)` — More general form of bracketing - takes just a float and a bracket size.
- L63-75 _function_ `float2 CalculateUV(float2 vAxis, float2 position, float Time, float Speed)`
- L77-87 _function_ `float ComputeMipLevel(float2 uv, int2 sz)`
- L89-113 _function_ `void Compute3Phases(const float PulseLength, const float Time, out float lerp0, out float lerp1, out float lerp2, out float t0, out float t1, out float t2, out float3 CycleCount)`
- L115-126 _function_ `void Compute2Phases(const float PulseLength, const float Time, out float lerpV, out float t0, out float t1, out float2 CycleCount)`
- L128-148 _function_ `float4 AdvectionInterpolation2(float2 UV, float2 Velocity, float t0, float t1, float lerpV, float AdvectedTextureScale, float2 TexMipLevel, Texture2D<float4> Tex, SamplerState TexSampler, float2 CycleCount)`
- L150-174 _function_ `float4 AdvectionInterpolation3(float2 UV, float2 Velocity, float t0, float t1, float t2, float lerp0, float lerp1, float lerp2, float AdvectedTextureScale, float3 TexMipLevel, Texture2D<float4> Tex, SamplerState TexSampler, float3 CycleCount)`
