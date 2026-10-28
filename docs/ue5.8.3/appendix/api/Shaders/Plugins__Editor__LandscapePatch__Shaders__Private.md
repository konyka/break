# Shaders / Plugins/Editor/LandscapePatch/Shaders/Private

- files: 2; lines: 413
- record kinds: cpp_binding=9, entry=9, function=5, include=4, parameter=41, resource=14

### `Plugins/Editor/LandscapePatch/Shaders/Private/LandscapeCircleHeightPatchPS.usf` (Private)

- lines: 52; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`, L6 `/Engine/Private/Landscape/LandscapeCommon.ush`
- L3 #pragma `once`

#### Entry points (2)

- L15-33 _entry_ `void ApplyLandscapeCircleHeightPatch(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeCircleHeightPatchPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeCircleHeightPatchPS.cpp:57) _[#if CIRCLE_HEIGHT_PATCH]_
- L39-49 _entry_ `void ApplyLandscapeCircleVisibilityPatch(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeCircleVisibilityPatchPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeCircleHeightPatchPS.cpp:58) _[#if CIRCLE_VISIBILITY_PATCH]_

#### Global parameters (uniforms) (4)

- L8 _parameter_ `float3 InCenter;`
- L9 _parameter_ `float InRadius;`
- L10 _parameter_ `float InFalloff;`
- L11 _parameter_ `float InEditLayerWeightmapAlpha;`

### `Plugins/Editor/LandscapePatch/Shaders/Private/LandscapeTexturePatchPS.usf` (Private)

- lines: 361; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`, L6 `/Engine/Private/Landscape/LandscapeCommon.ush`
- L3 #pragma `once`

#### Entry points (7)

- L168-201 _entry_ `void ApplyLandscapeTextureHeightPatch(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `UE::Landscape::FApplyLandscapeTextureHeightPatchPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeTexturePatchPS.cpp:275) _[#if APPLY_HEIGHT_PATCH]_
- L208-213 _entry_ `void ApplyOffsetToHeightmap(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `UE::Landscape::FOffsetHeightmapPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeTexturePatchPS.cpp:276) _[#if OFFSET_HEIGHT_PATCH]_
- L222-229 _entry_ `void ConvertToNativeLandscapePatch(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `UE::Landscape::FConvertToNativeLandscapePatchPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeTexturePatchPS.cpp:278) _[#if CONVERT_TO_NATIVE_LANDSCAPE_PATCH]_
- L238-246 _entry_ `void ConvertBackFromNativeLandscapePatch(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `UE::Landscape::FConvertBackFromNativeLandscapePatchPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeTexturePatchPS.cpp:279) _[#if CONVERT_BACK_FROM_NATIVE_LANDSCAPE_PATCH]_
- L292-322 _entry_ `void ApplyLandscapeTextureWeightPatch(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `UE::Landscape::FApplyLandscapeTextureWeightPatchPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeTexturePatchPS.cpp:280) _[#if APPLY_WEIGHT_PATCH]_
- L332-347 _entry_ `void ReinitializePatch(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `UE::Landscape::FReinitializeLandscapePatchPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeTexturePatchPS.cpp:281) _[#if REINITIALIZE_PATCH]_
- L356-360 _entry_ `void SimpleTextureCopy(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `UE::Landscape::FSimpleTextureCopyPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Editor/LandscapePatch/Source/LandscapePatch/Private/LandscapeTexturePatchPS.cpp:277) _[#if SIMPLE_TEXTURE_COPY]_

#### Global resources (textures / buffers / samplers) (14)

- L120 _resource_ `Texture2D<float4> InHeightPatch;` _[#if APPLY_HEIGHT_PATCH]_
- L121 _resource_ `SamplerState InHeightPatchSampler;` _[#if APPLY_HEIGHT_PATCH]_
- L143 _resource_ `Texture2D<float4> InHeightPatchAlphaTexture;` _[#if APPLY_HEIGHT_PATCH]_
- L205 _resource_ `Texture2D<float4> InHeightmap;` _[#if OFFSET_HEIGHT_PATCH]_
- L217 _resource_ `Texture2D<float4> InHeightmap;` _[#if CONVERT_TO_NATIVE_LANDSCAPE_PATCH]_
- L233 _resource_ `Texture2D<float4> InHeightmap;` _[#if CONVERT_BACK_FROM_NATIVE_LANDSCAPE_PATCH]_
- L250 _resource_ `Texture2D<float4> InSourceWeightmap;` _[#if APPLY_WEIGHT_PATCH]_
- L251 _resource_ `Texture2D<float4> InWeightPatch;` _[#if APPLY_WEIGHT_PATCH]_
- L252 _resource_ `SamplerState InWeightPatchSampler;` _[#if APPLY_WEIGHT_PATCH]_
- L268 _resource_ `Texture2D<float4> InWeightPatchAlphaTexture;` _[#if APPLY_WEIGHT_PATCH]_
- L328 _resource_ `Texture2D<float4> InSource;` _[#if REINITIALIZE_PATCH]_
- L329 _resource_ `SamplerState InSourceSampler;` _[#if REINITIALIZE_PATCH]_
- L352 _resource_ `Texture2D<float4> InSource;` _[#if SIMPLE_TEXTURE_COPY]_
- L353 _resource_ `SamplerState InSourceSampler;` _[#if SIMPLE_TEXTURE_COPY]_

#### Global parameters (uniforms) (37)

- L123 _parameter_ `float4x4 InHeightmapToPatchUV;` — Heightmap to PatchUV transform. Default patch behavior that samples the texture relative to the patch's bounds _[#if APPLY_HEIGHT_PATCH]_
- L125 _parameter_ `float4x4 InHeightmapToPatchUVTransform;` — InHeightmapToPatchUV matrix with the source texture transform (world space or relative) applied _[#if APPLY_HEIGHT_PATCH]_
- L126 _parameter_ `float2 InPatchWorldDimensions;` _[#if APPLY_HEIGHT_PATCH]_
- L127 _parameter_ `float2 InEdgeUVDeadBorder;` _[#if APPLY_HEIGHT_PATCH]_
- L128 _parameter_ `float InFalloffWorldMargin;` _[#if APPLY_HEIGHT_PATCH]_
- L130 _parameter_ `float InZeroInEncoding;` — Value that corresponds to 0 (i.e. to LANDSCAPE_MID_VALUE) in the patch data _[#if APPLY_HEIGHT_PATCH]_
- L132 _parameter_ `float InHeightScale;` — Scale to apply to patch values relative to the value representing zero _[#if APPLY_HEIGHT_PATCH]_
- L134 _parameter_ `float InHeightOffset;` — An offset to apply to the resulting height, after applying the height scale _[#if APPLY_HEIGHT_PATCH]_
- L136 _parameter_ `uint InBlendMode;` — Enum defining blend modes, with values set in corresponding cpp file. _[#if APPLY_HEIGHT_PATCH]_
- L138 _parameter_ `uint InFlags;` — A combination of flags, whose positions are set in the corresponding cpp file. _[#if APPLY_HEIGHT_PATCH]_
- L140 _parameter_ `uint InTextureChannel;` — Height source texture color channel _[#if APPLY_HEIGHT_PATCH]_
- L142 _parameter_ `uint InAlphaMode;` — Alpha source mode, override texture (White system texture if undefined), alpha texture color channel, and texture transform _[#if APPLY_HEIGHT_PATCH]_
- L144 _parameter_ `uint InAlphaTextureChannel;` _[#if APPLY_HEIGHT_PATCH]_
- L146 _parameter_ `float4x4 InHeightmapAlphaToPatchUVTransform;` — InHeightmapToPatchUV matrix with the alpha source texture transform (world space or relative) applied _[#if APPLY_HEIGHT_PATCH]_
- L148 _parameter_ `float InEditLayerHeightmapAlpha;` — Assigned edit layer's heightmap/weightmap alpha _[#if APPLY_HEIGHT_PATCH]_
- L149 _parameter_ `float InEditLayerWeightmapAlpha;` _[#if APPLY_HEIGHT_PATCH]_
- L206 _parameter_ `float InHeightOffset;` _[#if OFFSET_HEIGHT_PATCH]_
- L218 _parameter_ `float InZeroInEncoding;` _[#if CONVERT_TO_NATIVE_LANDSCAPE_PATCH]_
- L219 _parameter_ `float InHeightScale;` _[#if CONVERT_TO_NATIVE_LANDSCAPE_PATCH]_
- L220 _parameter_ `float InHeightOffset;` _[#if CONVERT_TO_NATIVE_LANDSCAPE_PATCH]_
- L234 _parameter_ `float InZeroInEncoding;` _[#if CONVERT_BACK_FROM_NATIVE_LANDSCAPE_PATCH]_
- L235 _parameter_ `float InHeightScale;` _[#if CONVERT_BACK_FROM_NATIVE_LANDSCAPE_PATCH]_
- L236 _parameter_ `float InHeightOffset;` _[#if CONVERT_BACK_FROM_NATIVE_LANDSCAPE_PATCH]_
- L254 _parameter_ `float4x4 InWeightmapToPatchUV;` — Weightmap to PatchUV transform. Default patch behavior that samples the texture relative to the patch's bounds _[#if APPLY_WEIGHT_PATCH]_
- L256 _parameter_ `float4x4 InWeightmapToPatchUVTransform;` — InWeightmapToPatchUV matrix with the source texture transform (world space or relative) applied _[#if APPLY_WEIGHT_PATCH]_
- L257 _parameter_ `float2 InPatchWorldDimensions;` _[#if APPLY_WEIGHT_PATCH]_
- L258 _parameter_ `float2 InEdgeUVDeadBorder;` _[#if APPLY_WEIGHT_PATCH]_
- L259 _parameter_ `float InFalloffWorldMargin;` _[#if APPLY_WEIGHT_PATCH]_
- L261 _parameter_ `uint InBlendMode;` — Enum defining blend modes, with values set in corresponding cpp file. _[#if APPLY_WEIGHT_PATCH]_
- L263 _parameter_ `uint InFlags;` — A combination of flags, whose positions are set in the corresponding cpp file. _[#if APPLY_WEIGHT_PATCH]_
- L265 _parameter_ `uint InTextureChannel;` — Weight source texture color channel _[#if APPLY_WEIGHT_PATCH]_
- L267 _parameter_ `uint InAlphaMode;` — Alpha source mode, override texture (White system texture if undefined), alpha texture color channel, and texture transform _[#if APPLY_WEIGHT_PATCH]_
- L269 _parameter_ `uint InAlphaTextureChannel;` _[#if APPLY_WEIGHT_PATCH]_
- L271 _parameter_ `float4x4 InWeightmapAlphaToPatchUVTransform;` — InWeightmapToPatchUV matrix with the alpha source texture transform (world space or relative) applied _[#if APPLY_WEIGHT_PATCH]_
- L273 _parameter_ `float InEditLayerWeightmapAlpha;` — Patch edit layer's weightmap alpha _[#if APPLY_WEIGHT_PATCH]_
- L330 _parameter_ `float4x4 InPatchToSource;` _[#if REINITIALIZE_PATCH]_
- L354 _parameter_ `float2 InDestinationResolution;` _[#if SIMPLE_TEXTURE_COPY]_

#### Functions (5)

- L23-80 _function_ `float GetFalloffAlpha(float FalloffWorldMargin, float2 PatchWorldDimensions, float2 PatchUVCoordinates, float2 EdgeUVDeadBorder, bool bRectangularFalloff)` — Given the falloff settings, gives the alpha to use for a pixel at the given patch UV coordinates. _[#if APPLY_HEIGHT_PATCH \|\| APPLY_WEIGHT_PATCH]_
- L82-99 _function_ `float GetChannelFromSample(uint InTextureChannel, float4 InSampledValue)` _[#if APPLY_HEIGHT_PATCH \|\| APPLY_WEIGHT_PATCH]_
- L101-116 _function_ `float GetAlphaFactor(uint InAlphaMode, uint InAlphaTextureChannel, float4 InPatchTextureSampledValue, float4 InAlphaTextureSampledValue)` _[#if APPLY_HEIGHT_PATCH \|\| APPLY_WEIGHT_PATCH]_
- L151-166 _function_ `uint ConvertPatchBlendModeToHeightAlphaFlags()` _[#if APPLY_HEIGHT_PATCH]_
- L275-290 _function_ `uint ConvertPatchBlendModeToWeightAlphaFlags()` _[#if APPLY_WEIGHT_PATCH]_
