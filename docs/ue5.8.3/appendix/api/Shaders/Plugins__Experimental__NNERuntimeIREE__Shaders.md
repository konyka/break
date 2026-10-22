# Shaders / Plugins/Experimental/NNERuntimeIREE/Shaders

- files: 2; lines: 28
- record kinds: cpp_binding=2, entry=1, include=3, parameter=1, resource=1

### `Plugins/Experimental/NNERuntimeIREE/Shaders/NNERuntimeIREEShader.usf` (Other)

- lines: 6; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L6 `/Plugin/NNERuntimeIREEShader/Generated/NNERuntimeIREEShader.ush`

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `__` → entry not found in file (macro-generated or #include'd); C++ `FNNERuntimeIREEShader` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Private/NNERuntimeIREEShader.cpp:9)

### `Plugins/Experimental/NNERuntimeIREE/Shaders/NNERuntimeIREEShaderFillBuffer.usf` (Other)

- lines: 22; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L14-22 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void Main(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FFillBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREEShader/Private/NNERuntimeIREEShaderFillBufferCS.cpp:23)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `RWByteAddressBuffer TargetBuffer;`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `uint4 Fill;` — Fill parameters x: pattern y: pattern width z: fill offset in bytes w: fill length in bytes
