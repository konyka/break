# Shaders / Plugins/Media/MediaIOFramework/Shaders

- files: 1; lines: 51
- record kinds: cpp_binding=2, entry=2, include=2, macro_call=2, parameter=1, resource=2

### `Plugins/Media/MediaIOFramework/Shaders/MediaIO.usf` (Other)

- lines: 51; parse: all-branches
- includes: L3 `/Engine/Private/ScreenPass.ush`, L4 `/Engine/Private/Common.ush`

#### Entry points (2)

- L14-40 _entry_ `void MediaDownsample(float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMediaCaptureResamplePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaCaptureRenderPass.cpp:64) — Shader to downsample a texture, Adapted from PostProcessDownsample.usf
- L44-51 _entry_ `void MediaTransform(float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMediaTextureTransformPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/MediaIOFramework/Source/MediaIOCore/Private/MediaCaptureSources.inl:558)

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `Texture2D InputTexture;`
- L11 _resource_ `SamplerState InputSampler;`

#### Global parameters (uniforms) (1)

- L42 _parameter_ `float4 RotationScale;`

#### Top-level macro invocations (2)

- L6 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input)`
- L7 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Output)`
