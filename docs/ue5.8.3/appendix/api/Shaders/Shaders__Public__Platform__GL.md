# Shaders / Shaders/Public/Platform/GL

- files: 2; lines: 59
- record kinds: define=10, parameter=5

### `Shaders/Public/Platform/GL/GLCommon.ush` (Public)

- lines: 13; parse: all-branches
- L7 #pragma `once`; L10 #pragma `message("UESHADERMETADATA_VERSION CE7F533A-EFA7-4EA0-B2CF-15B195E67095")`

### `Shaders/Public/Platform/GL/GLSubpassSupport.ush` (Public)

- lines: 46; parse: all-branches

#### Macros (#define, 10)

- L15 `#define GLSubpassDepthFetch() GENERATED_SubpassDepthFetchAttachment.SubpassLoad( )` _[#if PIXELSHADER && COMPILER_DXC]_
- L19 `#define GLSubpassFetch0() GENERATED_SubpassFetchAttachment0.SubpassLoad()` _[#if PIXELSHADER && COMPILER_DXC]_
- L23 `#define GLSubpassFetch1() GENERATED_SubpassFetchAttachment1.SubpassLoad()` _[#if PIXELSHADER && COMPILER_DXC]_
- L27 `#define GLSubpassFetch2() GENERATED_SubpassFetchAttachment2.SubpassLoad()` _[#if PIXELSHADER && COMPILER_DXC]_
- L31 `#define GLSubpassFetch3() GENERATED_SubpassFetchAttachment3.SubpassLoad()` _[#if PIXELSHADER && COMPILER_DXC]_
- L35 `#define GLSubpassDepthFetch() 1.0` _[#if PIXELSHADER && !(COMPILER_DXC)]_
- L37 `#define GLSubpassFetch0() float4(1.0)` _[#if PIXELSHADER && !(COMPILER_DXC)]_
- L39 `#define GLSubpassFetch1() float4(1.0)` _[#if PIXELSHADER && !(COMPILER_DXC)]_
- L41 `#define GLSubpassFetch2() float4(1.0)` _[#if PIXELSHADER && !(COMPILER_DXC)]_
- L43 `#define GLSubpassFetch3() float4(1.0)` _[#if PIXELSHADER && !(COMPILER_DXC)]_
- L6 #pragma `once`

#### Global parameters (uniforms) (5)

- L13-14 _parameter_ `[[vk::input_attachment_index(0)]] SubpassInput<float> GENERATED_SubpassDepthFetchAttachment;` _[#if PIXELSHADER && COMPILER_DXC]_
- L17-18 _parameter_ `[[vk::input_attachment_index(1)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment0;` _[#if PIXELSHADER && COMPILER_DXC]_
- L21-22 _parameter_ `[[vk::input_attachment_index(2)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment1;` _[#if PIXELSHADER && COMPILER_DXC]_
- L25-26 _parameter_ `[[vk::input_attachment_index(3)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment2;` _[#if PIXELSHADER && COMPILER_DXC]_
- L29-30 _parameter_ `[[vk::input_attachment_index(4)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment3;` _[#if PIXELSHADER && COMPILER_DXC]_
