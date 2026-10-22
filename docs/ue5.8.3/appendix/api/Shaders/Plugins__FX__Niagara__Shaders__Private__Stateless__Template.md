# Shaders / Plugins/FX/Niagara/Shaders/Private/Stateless/Template

- files: 2; lines: 161
- record kinds: define=10, entry=1, function=1, include=1, macro_call=9, member=10, parameter=5, resource=1, struct=1

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Template/GenerateCS_PostModules.ush` (Private)

- lines: 113; parse: all-branches
- includes: L3 `/Engine/Private/ComputeShaderUtils.ush`

#### Macros (#define, 4)

- L86 `#define PARTICLE_MODULE(NAME) GRandomSeedInternal = FNiagaraStatelessDefinitions::MakeRandomSeed(Common_RandomSeed, Particle.UniqueID, ModuleSeedOffset++, 0); ##NAME##_Simulate(Particle);` (3 lines)
- L105 `#define PARTICLE_ATTRIBUTE_OUTPUT(TYPE, NAME) if ( IsValidComponent(Permutation_##NAME##Component) ) { OutputComponentData(OutputIndex, Permutation_##NAME##Component, Particle.##NAME); }`
- L106 `#define PARTICLE_ATTRIBUTE_OUTPUT_IMPLICIT(TYPE, NAME) if ( IsValidComponent(Permutation_##NAME##Component) ) { OutputComponentData(OutputIndex, Permutation_##NAME##Component, Particle.##NAME); }`
- L107 `#define PARTICLE_ATTRIBUTE_TRANSIENT(TYPE, NAME) `
- L92 #undef `PARTICLE_MODULE`; L109 #undef `PARTICLE_ATTRIBUTE`; L110 #undef `PARTICLE_ATTRIBUTE_OUTPUT_IMPLICIT`; L111 #undef `PARTICLE_ATTRIBUTE_TRANSIENT`

#### Entry points (1)

- L24-112 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void StatelessMain(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute**

#### Global resources (textures / buffers / samplers) (1)

- L11 _resource_ `RWBuffer<uint> Common_GPUCountBuffer;`

#### Global parameters (uniforms) (5)

- L5 _parameter_ `uint Common_RandomSeed;`
- L6 _parameter_ `float Common_SimulationTime;`
- L7 _parameter_ `float Common_SimulationDeltaTime;`
- L8 _parameter_ `float Common_SimulationInvDeltaTime;`
- L10 _parameter_ `uint Common_GPUCountBufferOffset;`

#### Top-level macro invocations (8)

- L13 _macro_call_ `DECLARE_SCALAR_ARRAY(uint, SpawnInfo_NumActive, NIAGARA_MAX_GPU_SPAWN_INFOS)`
- L14 _macro_call_ `DECLARE_SCALAR_ARRAY(uint, SpawnInfo_ParticleOffset, NIAGARA_MAX_GPU_SPAWN_INFOS)`
- L15 _macro_call_ `DECLARE_SCALAR_ARRAY(uint, SpawnInfo_UniqueOffset, NIAGARA_MAX_GPU_SPAWN_INFOS)`
- L16 _macro_call_ `DECLARE_SCALAR_ARRAY(float, SpawnInfo_Time, NIAGARA_MAX_GPU_SPAWN_INFOS)`
- L17 _macro_call_ `DECLARE_SCALAR_ARRAY(float, SpawnInfo_Rate, NIAGARA_MAX_GPU_SPAWN_INFOS)`
- L18 _macro_call_ `DECLARE_SCALAR_ARRAY(float, SpawnInfo_Probability, NIAGARA_MAX_GPU_SPAWN_INFOS)`
- L19 _macro_call_ `DECLARE_SCALAR_ARRAY(float, SpawnInfo_LifetimeScale, NIAGARA_MAX_GPU_SPAWN_INFOS)`
- L20 _macro_call_ `DECLARE_SCALAR_ARRAY(float, SpawnInfo_LifetimeBias, NIAGARA_MAX_GPU_SPAWN_INFOS)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Template/GenerateCS_PreModules.ush` (Private)

- lines: 48; parse: all-branches

#### Macros (#define, 6)

- L21 `#define PARTICLE_ATTRIBUTE_OUTPUT(TYPE, NAME) TYPE NAME##;`
- L22 `#define PARTICLE_ATTRIBUTE_OUTPUT_IMPLICIT(TYPE, NAME) `
- L23 `#define PARTICLE_ATTRIBUTE_TRANSIENT(TYPE, NAME) TYPE NAME##;`
- L33 `#define PARTICLE_ATTRIBUTE_OUTPUT(TYPE, NAME) int Permutation_##NAME##Component;`
- L34 `#define PARTICLE_ATTRIBUTE_OUTPUT_IMPLICIT(TYPE, NAME) int Permutation_##NAME##Component;`
- L35 `#define PARTICLE_ATTRIBUTE_TRANSIENT(TYPE, NAME) `
- L25 #undef `PARTICLE_ATTRIBUTE`; L26 #undef `PARTICLE_ATTRIBUTE_OUTPUT_IMPLICIT`; L27 #undef `PARTICLE_ATTRIBUTE_TRANSIENT`; L37 #undef `PARTICLE_ATTRIBUTE`; L38 #undef `PARTICLE_ATTRIBUTE_OUTPUT_IMPLICIT`; L39 #undef `PARTICLE_ATTRIBUTE_TRANSIENT`

#### Structs / classes (1)

- L5-29 _struct_ **`FStatelessParticle`** `struct FStatelessParticle`
  - L7 _member_ `bool bAlive;` — If the particle should remain alive or not (only evaluated as specific points)
  - L8 _member_ `uint UniqueID;` — Unique particle index, sequential based on previous spawn info accumulation
  - L9 _member_ `float MaterialRandom;` — Random float passed to materials
  - L10 _member_ `float Lifetime;` — Overall lifetime for the particle
  - L11 _member_ `float Age;` — Current age for the particle
  - L12 _member_ `float NormalizedAge;` — Current normalized age for the particle
  - L13 _member_ `float PreviousAge;` — Previous age for the particle
  - L14 _member_ `float PreviousNormalizedAge;` — Previous normalized age for the particle
  - L16 _member_ `float DeltaTime;` — Simulation DT
  - L17 _member_ `float InvDeltaTime;` — Simulation Inverse DT

#### Functions (1)

- L36-45 _function_ `PARTICLE_ATTRIBUTES void Null_Simulate(inout FStatelessParticle Particle)`

#### Top-level macro invocations (1)

- L24-29 _macro_call_ `PARTICLE_ATTRIBUTES` (scope `FStatelessParticle`)
