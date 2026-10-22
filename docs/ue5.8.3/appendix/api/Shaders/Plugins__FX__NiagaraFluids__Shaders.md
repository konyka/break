# Shaders / Plugins/FX/NiagaraFluids/Shaders

- files: 2; lines: 96
- record kinds: define=2, function=3, groupshared=1

### `Plugins/FX/NiagaraFluids/Shaders/NiagaraFFT.ush` (Other)

- lines: 34; parse: all-branches

#### groupshared (1)

- L8 _groupshared_ `groupshared float2 FFTGroupShared[2*THREADGROUP_SIZE];` — Shared memory for FFT

#### Functions (3)

- L12-15 _function_ `float2 ComplexCon(float2 Z)` — common FFT functions complex conjugate
- L17-21 _function_ `float2 ComplexMultEqs(float2 ZA, float2 ZB)`
- L31-34 _function_ `float EigenValue(int kx_, int ky_, int Mx, int My, float Pi, float dx)`

### `Plugins/FX/NiagaraFluids/Shaders/NiagaraFluids.ush` (Other)

- lines: 62; parse: all-branches

#### Macros (#define, 2)

- L13 `#define MARCH_SINGLE_RAY(RayStart, RayDir, UnitStepSize, LocalStepSize, NumSteps, Volume, RetV) RetV = float4(0,0,0,0); float Transmittance = 1; int Steps = ceil(NumSteps); if(Steps >= 1.0 ) Steps += 1.0; [loop] for (int i = 0; i < Steps && Transmittance > 1e-5; i++) { float Extinction; float Sc ...` (21 lines)
- L35 `#define MARCH_SINGLE_RAY_EMISSION(RayStart, RayDir, UnitStepSize, LocalStepSize, NumSteps, Volume, RetV) RetV = float4(0,0,0,0); float Transmittance = 1; int Steps = ceil(NumSteps); if(Steps >= 1.0 ) Steps += 1.0; [loop] for (int i = 0; i < Steps && Transmittance > 1e-5; i++) { float Extinction; float Sc ...` (27 lines)
- L7 #pragma `once`
