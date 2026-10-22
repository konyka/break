# Plugins / NNEDenoiserShaders

- module root: `Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders`
- headers: 5; symbols: 73
- symbol kinds: class=12, delegate=1, enum=3, enumerator=13, macro=4, member=9, namespace=12, prototype=15, typedef=4
- PrivateDependencyModuleNames: Projects, RHI, Renderer
- PublicDependencyModuleNames: Core, RenderCore

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Internal/NNEDenoiserShadersAutoExposureCS.h` (Internal)


#### class `UE::NNEDenoiserShaders::Internal::FAutoExposureDownsampleConstants`  
`class FAutoExposureDownsampleConstants`  
_L14-19_
- L17 _public member_ `static constexpr int32 MAX_BIN_SIZE{16};`
- L18 _public member_ `static constexpr int32 THREAD_GROUP_SIZE{MAX_BIN_SIZE};`

#### class `UE::NNEDenoiserShaders::Internal::FAutoExposureDownsampleCS`  
`class FAutoExposureDownsampleCS : public FGlobalShader`  
_L21-39_
- inherits: `FGlobalShader`
- L29 _public prototype_ `SHADER_PARAMETER(int32, InputTextureWidth) SHADER_PARAMETER(int32, InputTextureHeight) SHADER_PARAMETER_RDG_TEXTURE(Texture2D, InputTexture) SHADER_PARAMETER(int32, NumBinsW) SHADER_PARAMETER(int32, NumBinsH) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer, OutputBins) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L38 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

#### class `UE::NNEDenoiserShaders::Internal::FAutoExposureReduceConstants`  
`class FAutoExposureReduceConstants`  
_L41-47_
- L44 _public member_ `static constexpr int32 THREAD_GROUP_SIZE{32};`
- L45 _public member_ `static constexpr float EPS{1e-8f};`
- L46 _public member_ `static constexpr float KEY{0.18f};`

#### class `UE::NNEDenoiserShaders::Internal::FAutoExposureReduceCS`  
`class FAutoExposureReduceCS : public FGlobalShader`  
_L49-66_
- inherits: `FGlobalShader`
- L57 _public prototype_ `SHADER_PARAMETER(int32, InputSize) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer, InputBins) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer, OutputSums) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer, OutputCounts) SHADER_PARAMETER(int32, NumThreads) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L65 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

#### class `UE::NNEDenoiserShaders::Internal::FAutoExposureReduceFinalCS`  
`class FAutoExposureReduceFinalCS : public FGlobalShader`  
_L68-84_
- inherits: `FGlobalShader`
- L76 _public prototype_ `SHADER_PARAMETER(int32, InputSize) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer, InputSums) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer, InputCounts) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer, OutputBuffer) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L83 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NNEDENOISERSHADERS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEDenoiserShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEDenoiserShaders`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Internal/NNEDenoiserShadersDefaultIOProcessCS.h` (Internal)


#### enum `UE::NNEDenoiserShaders::Internal::EDefaultIOProcessInputKind`  
`enum class EDefaultIOProcessInputKind : uint8`  
_L14-22_
- L16 _public enumerator_ `Color = 0`
- L17 _public enumerator_ `Albedo`
- L18 _public enumerator_ `Normal`
- L19 _public enumerator_ `Flow`
- L20 _public enumerator_ `Output`
- L21 _public enumerator_ `MAX`

#### class `UE::NNEDenoiserShaders::Internal::FDefaultIOProcessConstants`  
`class FDefaultIOProcessConstants`  
_L24-28_
- L27 _public member_ `static constexpr int32 THREAD_GROUP_SIZE{16};`

#### class `UE::NNEDenoiserShaders::Internal::FDefaultIOProcessCS`  
`class FDefaultIOProcessCS : public FGlobalShader`  
_L30-49_
- inherits: `FGlobalShader`
- L36 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDefaultIOProcessInputKind>;`
- L41 _public prototype_ `SHADER_PARAMETER(int32, Width) SHADER_PARAMETER(int32, Height) SHADER_PARAMETER_RDG_TEXTURE(Texture2D, InputTexture) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, OutputTexture) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L48 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NNEDENOISERSHADERS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEDenoiserShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEDenoiserShaders`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Internal/NNEDenoiserShadersMappedCopyCS.h` (Internal)


#### enum `UE::NNEDenoiserShaders::Internal::EDataType`  
`enum class EDataType : uint8`  
_L15-23_
- desc: Maps to ENNETensorDataType
- L17 _public enumerator_ `None = 0`
- L20 _public enumerator_ `Half = 3` — Char, Boolean,
- L21 _public enumerator_ `Float`
- L22 _public enumerator_ `MAX`

#### class `UE::NNEDenoiserShaders::Internal::FMappedCopyConstants`  
`class FMappedCopyConstants`  
_L25-30_
- L28 _public member_ `static constexpr int32 THREAD_GROUP_SIZE{16};`
- L29 _public member_ `static constexpr int32 MAX_NUM_MAPPED_CHANNELS{4};`

#### class `UE::NNEDenoiserShaders::Internal::FTextureBufferMappedCopyCS`  
`class FTextureBufferMappedCopyCS : public FGlobalShader`  
_L34-56_
- inherits: `FGlobalShader`
- L42 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FInputDataType, FOutputDataType, FNumMappedChannels>;`
- L47 _public prototype_ `SHADER_PARAMETER(int32, Width) SHADER_PARAMETER(int32, Height) SHADER_PARAMETER_RDG_TEXTURE(Texture2D, InputTexture) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer, OutputBuffer) SHADER_PARAMETER_ARRAY(FIntVector4, OutputChannel_InputChannel_Unused_Unused, [FMappedCopyConstants::MAX_NUM_MAPPED_CHANNELS]) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L55 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

#### class `UE::NNEDenoiserShaders::Internal::FBufferTextureMappedCopyCS`  
`class FBufferTextureMappedCopyCS : public FGlobalShader`  
_L58-80_
- inherits: `FGlobalShader`
- L66 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FInputDataType, FOutputDataType, FNumMappedChannels>;`
- L71 _public prototype_ `SHADER_PARAMETER(int32, Width) SHADER_PARAMETER(int32, Height) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer, InputBuffer) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, OutputTexture) SHADER_PARAMETER_ARRAY(FIntVector4, OutputChannel_InputChannel_Unused_Unused, [FMappedCopyConstants::MAX_NUM_MAPPED_CHANNELS]) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L79 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NNEDENOISERSHADERS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEDenoiserShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEDenoiserShaders`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Internal/NNEDenoiserShadersTransferFunctionOidnCS.h` (Internal)


#### enum `UE::NNEDenoiserShaders::Internal::ETransferFunctionOidnMode`  
`enum class ETransferFunctionOidnMode : uint8`  
_L14-19_
- L16 _public enumerator_ `Forwward = 0`
- L17 _public enumerator_ `Inverse`
- L18 _public enumerator_ `MAX`

#### class `UE::NNEDenoiserShaders::Internal::FTransferFunctionOidnConstants`  
`class FTransferFunctionOidnConstants`  
_L21-25_
- L24 _public member_ `static constexpr int32 THREAD_GROUP_SIZE{16};`

#### class `UE::NNEDenoiserShaders::Internal::FTransferFunctionOidnCS`  
`class FTransferFunctionOidnCS : public FGlobalShader`  
_L27-49_
- inherits: `FGlobalShader`
- L33 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FTransferFunctionOidnMode>;`
- L38 _public prototype_ `SHADER_PARAMETER(int32, Width) SHADER_PARAMETER(int32, Height) SHADER_PARAMETER_RDG_TEXTURE(Texture2D, InputTexture) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer, InputScaleBuffer) SHADER_PARAMETER(float, NormScale) SHADER_PARAMETER(float, InvNormScale) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, OutputTexture) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L48 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NNEDENOISERSHADERS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEDenoiserShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEDenoiserShaders`)

### `Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Private/NNEDenoiserShadersLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNEDenoiserShaders, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNEDenoiserShaders, Log, All);`
