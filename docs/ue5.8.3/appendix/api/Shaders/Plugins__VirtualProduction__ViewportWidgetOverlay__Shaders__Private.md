# Shaders / Plugins/VirtualProduction/ViewportWidgetOverlay/Shaders/Private

- files: 1; lines: 31
- record kinds: cpp_binding=1, entry=1, include=1, resource=4

### `Plugins/VirtualProduction/ViewportWidgetOverlay/Shaders/Private/ViewportWidgetOverlay.usf` (Private)

- lines: 31; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L19-28 _entry_ `void OverlayWidgetPS( noperspective float4 UVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDrawTextureInShaderPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/ViewportWidgetOverlay/Source/ViewportWidgetOverlay/Private/Misc/PostProcessSceneViewExtension.cpp:68)

#### Global resources (textures / buffers / samplers) (4)

- L13 _resource_ `Texture2D WidgetTexture;` — The render target containing the result of FWidgetRenderer::DrawWindow
- L14 _resource_ `SamplerState WidgetSampler;`
- L16 _resource_ `Texture2D SceneTexture;` — This is the scene color texture, retrieved by the SVE
- L17 _resource_ `SamplerState SceneSampler;`
