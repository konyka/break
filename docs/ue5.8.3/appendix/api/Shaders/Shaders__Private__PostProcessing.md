# Shaders / Shaders/Private/PostProcessing

- files: 2; lines: 99
- record kinds: cpp_binding=2, define=1, entry=2, groupshared=1, include=2, parameter=2, resource=4

### `Shaders/Private/PostProcessing/FilmGrainPackConstants.usf` (Private)

- lines: 28; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L15-27 _entry_ `[numthreads(1, 1, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FFilmGrainPackConstantsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessTonemap.cpp:508)

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `Texture2D ReducedFilmGrainTexture;`
- L10 _resource_ `RWStructuredBuffer<float4> FilmGrainConstantsOutput;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `uint2 OriginalFilmGrainTextureSize;`

### `Shaders/Private/PostProcessing/FilmGrainReduce.usf` (Private)

- lines: 71; parse: all-branches
- includes: L3 `../Common.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 8`

#### Entry points (1)

- L26-70 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FFilmGrainReduceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessTonemap.cpp:507)

#### Global resources (textures / buffers / samplers) (2)

- L14 _resource_ `Texture2D FilmGrainTexture;`
- L16 _resource_ `RWTexture2D<float4> Output;`

#### Global parameters (uniforms) (1)

- L13 _parameter_ `uint2 FilmGrainTextureSize;`

#### groupshared (1)

- L21 _groupshared_ `groupshared float4 SharedColor[TILE_SIZE * TILE_SIZE];`
