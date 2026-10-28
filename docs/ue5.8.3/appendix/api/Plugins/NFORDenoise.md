# Plugins / NFORDenoise

- module root: `Plugins/Experimental/NFORDenoise/Source/NFORDenoise`
- headers: 4; symbols: 230
- symbol kinds: class=26, delegate=1, enum=12, enumerator=42, function=57, macro=5, member=27, namespace=2, prototype=36, struct=4, typedef=17, union=1
- PrivateDependencyModuleNames: Eigen, Projects, RHI, RenderCore, Renderer
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.h` (Private)


#### enum `NFORDenoise::EVarianceType`  
`enum class EVarianceType : uint32`  
_L24-30_
- L26 _public enumerator_ `Normal` — length of vector
- L27 _public enumerator_ `GreyScale` — grey scale
- L28 _public enumerator_ `Colored` — Not supported at this moment.
- L29 _public enumerator_ `MAX`

#### enum `NFORDenoise::EImageChannelCount`  
`enum class EImageChannelCount : uint32`  
_L32-39_
- L34 _public enumerator_ `One`
- L35 _public enumerator_ `Two`
- L36 _public enumerator_ `Three`
- L37 _public enumerator_ `Four`
- L38 _public enumerator_ `MAX`

#### enum `NFORDenoise::ENonLocalMeanAtlasType`  
`enum class ENonLocalMeanAtlasType : uint32`  
_L41-46_
- L43 _public enumerator_ `OneSymmetricPair`
- L44 _public enumerator_ `TwoSymmetricPair`
- L45 _public enumerator_ `MAX`

#### enum `NFORDenoise::EAlbedoDivideRecoverPhase`  
`enum class EAlbedoDivideRecoverPhase : uint32`  
_L48-54_
- L50 _public enumerator_ `Disabled`
- L51 _public enumerator_ `Each`
- L52 _public enumerator_ `Final`
- L53 _public enumerator_ `MAX`

#### class `NFORDenoise::FTextureMultiplyCS`  
`class FTextureMultiplyCS : public FGlobalShader`  
_L62-88_
- inherits: `FGlobalShader`
- L68 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Source) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWTarget) SHADER_PARAMETER(FIntPoint, SourcePosition) SHADER_PARAMETER(FIntPoint, TargetPosition) SHADER_PARAMETER(FIntPoint, Size) SHADER_PARAMETER(int32, ForceOperation) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L84 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `NFORDenoise::FTextureDivideCS`  
`class FTextureDivideCS : public FGlobalShader`  
_L90-116_
- inherits: `FGlobalShader`
- L96 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Source) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWTarget) SHADER_PARAMETER(FIntPoint, SourcePosition) SHADER_PARAMETER(FIntPoint, TargetPosition) SHADER_PARAMETER(FIntPoint, Size) SHADER_PARAMETER(int32, ForceOperation) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L112 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `NFORDenoise::FTextureAccumulateConstantCS`  
`class FTextureAccumulateConstantCS : public FGlobalShader`  
_L118-146_
- inherits: `FGlobalShader`
- L124 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWTarget) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Mask) SHADER_PARAMETER(FIntPoint, TargetPosition) SHADER_PARAMETER(FIntPoint, Size) SHADER_PARAMETER(FLinearColor, ConstantValue) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L139 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L145 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionAccumulateByMask>;`

#### class `NFORDenoise::FTextureAccumulateCS`  
`class FTextureAccumulateCS : public FGlobalShader`  
_L149-174_
- inherits: `FGlobalShader`
- desc: Accumulate all channels of a texture onto another texture for a given region.
- L155 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Source) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWTarget) SHADER_PARAMETER(FIntPoint, SourcePosition) SHADER_PARAMETER(FIntPoint, TargetPosition) SHADER_PARAMETER(FIntPoint, Size) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L170 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `NFORDenoise::FCopyTexturePS`  
`class FCopyTexturePS : public FGlobalShader`  
_L176-192_
- inherits: `FGlobalShader`
- L182 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Source) SHADER_PARAMETER(FIntPoint, SourceOffset) SHADER_PARAMETER(FIntPoint, TextureSize) RENDER_TARGET_BINDING_SLOTS() END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### enum `NFORDenoise::ETextureCopyType`  
`enum class ETextureCopyType :uint32`  
_L194-199_
- L196 _public enumerator_ `TargetSingleChannel`
- L197 _public enumerator_ `SourceSingleChannel`
- L198 _public enumerator_ `MAX`

#### class `NFORDenoise::FCopyTextureSingleChannelCS`  
`class FCopyTextureSingleChannelCS : public FGlobalShader`  
_L201-229_
- inherits: `FGlobalShader`
- L207 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, CopySource) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWCopyTarget) SHADER_PARAMETER(FIntPoint, SourceOffset) SHADER_PARAMETER(FIntPoint, TargetOffset) SHADER_PARAMETER(FIntPoint, CopySize) SHADER_PARAMETER(FIntPoint, TextureSize) SHADER_PARAMETER(int32, Channel) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L222 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L228 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimTextureCopyType>;`

#### class `NFORDenoise::FClassifyPreAlbedoDivideMaskIdCS`  
`class FClassifyPreAlbedoDivideMaskIdCS : public FGlobalShader`  
_L258-281_
- inherits: `FGlobalShader`
- L260 _private prototype_ `DECLARE_GLOBAL_SHADER(FClassifyPreAlbedoDivideMaskIdCS);`
- L261 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FClassifyPreAlbedoDivideMaskIdCS, FGlobalShader);`
- L264 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Normal) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, NormalVariance) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWMask) SHADER_PARAMETER(FIntPoint, TextureSize) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L277 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `NFORDenoise::FNormalizeRadianceVarianceByAlbedoCS`  
`class FNormalizeRadianceVarianceByAlbedoCS : public FGlobalShader`  
_L284-306_
- inherits: `FGlobalShader`
- desc: Based on Taylor expansion, sigma_{normalized radiance} \approx = sigma_{radiance} / sigma_{albedo}, if normalized radiance = radiance / albedo
- L290 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, Albedo) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, RWRadianceVariance) SHADER_PARAMETER(FIntPoint, Size) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L302 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `NFORDenoise::FAdjustFeatureRangeCS`  
`class FAdjustFeatureRangeCS : public FGlobalShader`  
_L311-339_
- inherits: `FGlobalShader`
- desc: Remap feature range
- L318 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWImage) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWImageVariance) SHADER_PARAMETER(FIntPoint, Size) SHADER_PARAMETER(int32, VarianceChannelOffset) SHADER_PARAMETER(float, MaxValue) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L332 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L338 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionVarianceType>;`

#### enum `NFORDenoise::ENonLocalMeanWeightLayout`  
`enum class ENonLocalMeanWeightLayout : uint32`  
_L368-376_
- L371 _public enumerator_ `None` — Weight buffer is not in use
- L372 _public enumerator_ `NumOfWeightsPerPixelxWxH`
- L373 _public enumerator_ `WxHxNumOfWeightsPerPixel`
- L374 _public enumerator_ `Float4xWxHxNumOfWeightsPerPixelByFloat4`
- L375 _public enumerator_ `MAX`

#### struct `NFORDenoise::FNonLocalMeanWeightDesc`  
`struct FNonLocalMeanWeightDesc`  
_L378-388_
- L381 _public member_ `FIntRect Region;` — The region this weights is gathered for.
- L384 _public member_ `FRDGBufferRef WeightBuffer = nullptr;` — The gathered weights
- L387 _public member_ `ENonLocalMeanWeightLayout WeightLayout = ENonLocalMeanWeightLayout::None;` — The layout of the weight

#### class `NFORDenoise::FNonLocalMeanFilteringCS`  
`class FNonLocalMeanFilteringCS : public FGlobalShader`  
_L395-435_
- inherits: `FGlobalShader`
- desc: Output the non-local mean filtered image (feature) based on variance Input: Image, variance, Guide(optional), NonLocalMean parameters Dim: WxHx?, WxHx? Output: Image holding  prefiltered features Dim: WxHx?
- L402 _public function_ `SHADER_PARAMETER_STRUCT_INCLUDE(FNonLocalMeanParameters, NLMParams) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, Guide) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Variance) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Image) SHADER_PARAMETER(FIntPoint, TextureSize) SHADER_PARAMETER(int32, VarianceChannelOffset) SHADER_PARAMETER(int32, DenoisingChannelCount) SHADER_PARAMETER(FIntRect, FilteringRegion)`
- L424 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L434 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionVarianceType, FDimensionUseGuide, FDimensionImageChannelCount, FDimPreAlbedoDivide, FDimWeightLayout>;`

#### class `NFORDenoise::FNonLocalMeanWeightsCS`  
`class FNonLocalMeanWeightsCS : public FGlobalShader`  
_L443-476_
- inherits: `FGlobalShader`
- desc: Output the non-local mean weights for each pixel, used to solve the weighted least squares problem. Input: Image, variance, NonLocalMean parameters Dim: WxHx3, WxHx? Output: Buffer holding  weights for each pixel Dim: WxHx(2*N+1)^2, where N = NLMParams.PatchDistance
- L450 _public function_ `SHADER_PARAMETER_STRUCT_INCLUDE(FNonLocalMeanFilteringCS::FParameters, CommonParameters) SHADER_PARAMETER(FIntRect, Region) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, TargetImage) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, TargetVariance) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, RWNonLocalMeanWeights) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L463 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L474 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionVarianceType, FDimensionUseGuide, FDimensionImageChannelCount, FDimensionSeparateSourceTarget, FDimPreAlbedoDivide, FDimTargetWeightLayout>;`

#### class `NFORDenoise::FNonLocalMeanGetSqauredDistanceToAtlasCS`  
`class FNonLocalMeanGetSqauredDistanceToAtlasCS : public FGlobalShader`  
_L479-510_
- inherits: `FGlobalShader`
- desc: Optimize the weights query.
- L485 _public function_ `SHADER_PARAMETER_STRUCT_INCLUDE(FNonLocalMeanFilteringCS::FParameters, CommonParameters) SHADER_PARAMETER_STRUCT_INCLUDE(FNonLocalMeanWeightAtlasDispatchParameters, NLMWeightAtlasDispatchParameters) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, TargetImage) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, TargetVariance) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWNLMWeightAtlas) SHADER_PARAMETER(FIntPoint, NLMWeightAtlasSize) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L499 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L509 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionVarianceType, FDimensionImageChannelCount, FDimensionSeparateSourceTarget, FDimPreAlbedoDivide, FDimAtlasType>;`

#### class `NFORDenoise::FNonLocalMeanSeperableFilterPatchSqauredDistanceCS`  
`class FNonLocalMeanSeperableFilterPatchSqauredDistanceCS : public FGlobalShader`  
_L512-549_
- inherits: `FGlobalShader`
- L518 _public function_ `SHADER_PARAMETER_STRUCT_INCLUDE(FNonLocalMeanParameters, NLMParams) SHADER_PARAMETER_STRUCT_INCLUDE(FNonLocalMeanWeightAtlasDispatchParameters, NLMWeightAtlasDispatchParameters) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, NLMWeightAtlasSource) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWNLMWeightAtlasTarget) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer, RWNLMWeights) SHADER_PARAMETER(FIntVector, SeperableRegionSize) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L532 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L548 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionSeperablePassType, FDimPreAlbedoDivide, FDimAtlasType, FDimBufferPassThrough>;`

#### enum `NFORDenoise::FNonLocalMeanSeperableFilterPatchSqauredDistanceCS::ESeperablePassType`  
`enum class ESeperablePassType : int32`  
_L537-542_
- L539 _public enumerator_ `Horizontal`
- L540 _public enumerator_ `Vertical`
- L541 _public enumerator_ `MAX`

#### class `NFORDenoise::FNonLocalMeanReshapeBufferCS`  
`class FNonLocalMeanReshapeBufferCS : public FGlobalShader`  
_L553-581_
- inherits: `FGlobalShader`
- desc: Reshape the layout of the buffer to target From XxYx[W/B] (each element is of size B) to W*X*Y
- L559 _public function_ `SHADER_PARAMETER_STRUCT_INCLUDE(FNonLocalMeanParameters, NLMParams) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float2>, SourceBuffer) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, RWTargetBuffer) SHADER_PARAMETER(FIntVector4, SourceBufferDim) SHADER_PARAMETER(FIntVector, TargetBufferDim) SHADER_PARAMETER(int32, HalfOffsetSearchCount) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L573 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L580 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionSeparateSourceTarget, FDimensionTargetWeightLayout>;`

#### class `NFORDenoise::FCopyTextureToBufferCS`  
`class FCopyTextureToBufferCS : public FGlobalShader`  
_L591-634_
- inherits: `FGlobalShader`
- desc: Collaborative filtering shaders 1. Tiling Copy textures to buffer based on copy channel config Buffer layout |Pixel 1                          | Pixel 2|...|Pixel n| tex1.rgb|tex2.rgb|tex3.rgb
- L598 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Source) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Dest) SHADER_PARAMETER(FIntPoint, TextureSize) SHADER_PARAMETER(int32, CopyChannelCount) SHADER_PARAMETER(int32, CopyChannelOffset) SHADER_PARAMETER(int32, BufferChannelOffset) SHADER_PARAMETER(int32, BufferChannelSize) SHADER_PARAMETER(FIntRect, CopyRegion) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L614 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L619 _public function_ `static EPixelFormat GetDestFloatFormat(uint32 BufferBytesPerElement)`
- L630 _public member_ `static const int kMaxSourceChannelCount = 4;`
- L633 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionSourceChannelCount>;`

#### class `NFORDenoise::FNormalizeTextureCS`  
`class FNormalizeTextureCS : public FGlobalShader`  
_L636-657_
- inherits: `FGlobalShader`
- L642 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWSource) SHADER_PARAMETER(FIntPoint, TextureSize) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L653 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### enum `NFORDenoise::RegressionKernel::EWeightedMultiplicationType`  
`enum class EWeightedMultiplicationType : uint8`  
_L679-684_
- L681 _public enumerator_ `Quadratic` — X^T W X
- L682 _public enumerator_ `Generalized` — X^T W Y
- L683 _public enumerator_ `MAX`

#### class `NFORDenoise::RegressionKernel::FInPlaceBatchedMatrixMultiplicationCS`  
`class FInPlaceBatchedMatrixMultiplicationCS : public FGlobalShader`  
_L701-770_
- inherits: `FGlobalShader`
- desc: Calculate X^T Diag(W) Y, where Y might be equal to X Note that the data is gathered in place to calculate the matrix for each pixel. This avoids data duplication saved to memory at the cost of increasing memory bandwidth utilization it is useful when memory size is small.
- L703 _private prototype_ `DECLARE_GLOBAL_SHADER(FInPlaceBatchedMatrixMultiplicationCS);`
- L704 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FInPlaceBatchedMatrixMultiplicationCS, FGlobalShader);`
- L707 _public prototype_ `static FRDGBufferRef AllocateResultBuffer(FRDGBuilder& GraphBuilder, FIntPoint Size, int F, int A);`
- L710 _public function_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, X) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer , W) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Y) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Result)`
- L738 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L744 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L749 _public function_ `static EPixelFormat GetXYFloatFormat(uint32 BufferBytesPerElement)`
- L760 _public member_ `static const int kMaxSourceChannelCount = 4;`
- L768 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimWeightedMultiplicationType, FDimAddConstantFeatureDim, FDimOptimizeTargetMatrixMultiplication, FDimNumFeature, FDimUseSamplingStep, FDimensionWeightLayout>;`

#### class `NFORDenoise::RegressionKernel::FLinearSolverCS`  
`class FLinearSolverCS : public FGlobalShader`  
_L773-818_
- inherits: `FGlobalShader`
- L775 _private prototype_ `DECLARE_GLOBAL_SHADER(FLinearSolverCS);`
- L776 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FLinearSolverCS, FGlobalShader);`
- L803 _public function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L809 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L817 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimNumFeature, FDimSolverType, FDimOutputIndices>;`

#### enum `NFORDenoise::RegressionKernel::FLinearSolverCS::ESolverType`  
`enum class ESolverType : uint32`  
_L795-801_
- L797 _public enumerator_ `NewtonSchulz`
- L798 _public enumerator_ `Cholesky`
- L799 _public enumerator_ `NewtonCholesky`
- L800 _public enumerator_ `MAX`

#### enum `NFORDenoise::RegressionKernel::EInputMatrixType`  
`enum class EInputMatrixType : uint32`  
_L820-825_
- L822 _public enumerator_ `Success`
- L823 _public enumerator_ `Fail`
- L824 _public enumerator_ `MAX`

#### class `NFORDenoise::RegressionKernel::FLinearSolverBuildIndirectDispatchArgsCS`  
`class FLinearSolverBuildIndirectDispatchArgsCS : public FGlobalShader`  
_L827-851_
- inherits: `FGlobalShader`
- L829 _private prototype_ `DECLARE_GLOBAL_SHADER(FLinearSolverBuildIndirectDispatchArgsCS);`
- L830 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FLinearSolverBuildIndirectDispatchArgsCS, FGlobalShader);`
- L834 _public function_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<uint>, SuccessAndFailIndexBuffer) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<uint>, RWIndirectDispatchArgsBuffer) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L844 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L850 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain <FDimInputMatrixType>;`

#### class `NFORDenoise::RegressionKernel::FLinearSolverIndirectCS`  
`class FLinearSolverIndirectCS : public FGlobalShader`  
_L853-881_
- inherits: `FGlobalShader`
- L855 _private prototype_ `DECLARE_GLOBAL_SHADER(FLinearSolverIndirectCS);`
- L856 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FLinearSolverIndirectCS, FGlobalShader);`
- L860 _public function_ `SHADER_PARAMETER_STRUCT_INCLUDE(FLinearSolverCS::FParameters, CommonParameters) RDG_BUFFER_ACCESS(IndirectDispatchArgsBuffer, ERHIAccess::IndirectArgs) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<uint>, SuccessAndFailIndexBuffer) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L871 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L880 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimNumFeature, FDimSolverType, FDimInputMatrixType, FDimOutputIndices>;`

#### class `NFORDenoise::RegressionKernel::FReconstructSpatialTemporalImage`  
`class FReconstructSpatialTemporalImage : public FGlobalShader`  
_L889-965_
- inherits: `FGlobalShader`
- L891 _private prototype_ `DECLARE_GLOBAL_SHADER(FReconstructSpatialTemporalImage);`
- L892 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FReconstructSpatialTemporalImage, FGlobalShader);`
- L896 _public function_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, X) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer , W) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, B) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, RWReconstruction) SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<uint4>, RWReconstructBuffer) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<UlongType>, RWReconstructBuffer64) SHADER_PARAMETER(FIntPoint, XDim)`
- L927 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L932 _public function_ `static EPixelFormat GetXFloatFormat(uint32 BufferBytesPerElement)`
- L950 _public function_ `static const TCHAR* GetEventName(EReconstructionType ReconstructionType)`
- L964 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimReconstructionType, FDimPreAlbedoDivide, FDimNumFeature, FDimensionWeightLayout>;`

#### enum `NFORDenoise::RegressionKernel::FReconstructSpatialTemporalImage::EReconstructionType`  
`enum class EReconstructionType : uint8`  
_L943-948_
- L945 _public enumerator_ `Scatter`
- L946 _public enumerator_ `Gather`
- L947 _public enumerator_ `MAX`

#### class `NFORDenoise::FAccumulateBufferToTextureCS`  
`class FAccumulateBufferToTextureCS : public FGlobalShader`  
_L968-996_
- inherits: `FGlobalShader`
- L970 _private prototype_ `DECLARE_GLOBAL_SHADER(FAccumulateBufferToTextureCS);`
- L971 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FAccumulateBufferToTextureCS, FGlobalShader);`
- L975 _public function_ `SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<uint4>, StructuredBufferSource) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<UlongType>, ReconstructBuffer64) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, RWTarget) SHADER_PARAMETER(FIntPoint, TextureSize) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L989 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L995 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimPreAlbedoDivide>;`

#### class `NFORDenoise::FMSEEstimationCS`  
`class FMSEEstimationCS : public FGlobalShader`  
_L1002-1031_
- inherits: `FGlobalShader`
- L1009 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, Variance) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, Image) SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>, FilteredImage) SHADER_PARAMETER(FIntPoint, TextureSize) SHADER_PARAMETER(int32, VarianceChannelOffset) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, MSE) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L1024 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L1030 _public typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDimensionVarianceType>;`

#### class `NFORDenoise::FGenerateSelectionMapCS`  
`class FGenerateSelectionMapCS : public FGlobalShader`  
_L1033-1055_
- inherits: `FGlobalShader`
- L1041 _public function_ `SHADER_PARAMETER(FIntPoint, TextureSize) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWSelectionMap) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L1051 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### class `NFORDenoise::FCombineFilteredImageCS`  
`class FCombineFilteredImageCS : public FGlobalShader`  
_L1057-1080_
- inherits: `FGlobalShader`
- L1065 _public function_ `SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, SelectionMap) SHADER_PARAMETER(FIntPoint, TextureSize) SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RWFilteredImage) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment)`
- L1076 _public function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

#### struct `NFORDenoise::FNFORTextureDesc`  
`struct FNFORTextureDesc`  
_L1085-1099_
- L1087 _public member_ `FRDGTextureRef Image;`
- L1090 _public member_ `int32 ChannelOffset;` — the specific channels for this feature
- L1091 _public member_ `int32 ChannelCount;`
- L1094 _public member_ `int32 NumOfChannel;` — The number of channels of the image
- L1096 _public function_ `FNFORTextureDesc(FRDGTextureRef Image, int32 ChannelOffset = 0, int32 ChannelCount = 4, int32 NumOfChannel = 4) : Image(Image), ChannelOffset(ChannelOffset), ChannelCount(ChannelCount), NumOfChannel(NumOfChannel)`

#### struct `NFORDenoise::FFeatureDesc`  
`struct FFeatureDesc`  
_L1101-1119_
- L1109 _public member_ `FNFORTextureDesc Variance;`
- L1112 _public member_ `EVarianceType VarianceType;` — Variance type, greyscale, normal, or colored
- L1115 _public member_ `bool bCleanFeature;` — Indicate no need to denoise if true
- L1117 _public function_ `FFeatureDesc(FNFORTextureDesc Feature, FNFORTextureDesc Variance, EVarianceType VarianceType = EVarianceType::GreyScale, bool bCleanFeature = false) :Feature(Feature), Variance(Variance), VarianceType(VarianceType), bCleanFeature(bCleanFeature)`

#### union `NFORDenoise::FFeatureDesc::(anonymous)`  
``  
_L1104-1107_

#### Free symbols / members of external scopes

- L11 _macro_ `#define NON_LOCAL_MEAN_THREAD_GROUP_SIZE 8`
- L13 _macro_ `#define TEXTURE_OPS_MULTIPLY 0`
- L14 _macro_ `#define TEXTURE_OPS_DIVIDE 1`
- L15 _macro_ `#define TEXTURE_OPS_ADD_CONSTANT 2`
- L16 _macro_ `#define TEXTURE_OPS_ACCUMULATE 3`
- L18 _namespace_ `namespace NFORDenoise`
- L21 _prototype_ `int32 GetFrameCount(const FSceneView& View);` (scope `NFORDenoise`)
- L22 _prototype_ `int32 GetDenoisingFrameIndex(const FSceneView& View, int32 NumberOfFrameInBuffer = -1);` (scope `NFORDenoise`)
- L60 _prototype_ `bool ShouldCompileNFORShadersForProject(EShaderPlatform ShaderPlatform);` (scope `NFORDenoise`)
- L232 _prototype_ `void AddMultiplyTextureRegionPass(FRDGBuilder& GraphBuilder, const FRDGTextureRef& SourceTexture, const FRDGTextureRef& TargetTexture, bool bForceMultiply = true, FIntPoint SourcePosition = FIntPoint::ZeroValue, FIntPoint TargetPosition = FIntPoint::ZeroValue, FIntPoint Size = FIntPoint::ZeroValue);` (scope `NFORDenoise`) — TargetTexture.rgb = TargetTexture.rgb * lerp (1.0f,SourceTexture.rgb, (SourceTexture.rgb != 0 || bForceMultiply));
- L236 _prototype_ `void AddDivideTextureRegionPass(FRDGBuilder& GraphBuilder, const FRDGTextureRef& SourceTexture, const FRDGTextureRef& TargetTexture, bool bForceDivide = true, FIntPoint SourcePosition = FIntPoint::ZeroValue, FIntPoint TargetPosition = FIntPoint::ZeroValue, FIntPoint Size = FIntPoint::ZeroValue);` (scope `NFORDenoise`) — TargetTexture.rgb = TargetTexture.rgb / lerp (1.0f,SourceTexture.rgb, SourceTexture.rgb != 0 || bForceDivide);
- L240 _prototype_ `void AddAccumulateTextureRegionPass(FRDGBuilder& GraphBuilder, const FRDGTextureRef& SourceTexture, const FRDGTextureRef& TargetTexture, FIntPoint SourcePosition = FIntPoint::ZeroValue, FIntPoint TargetPosition = FIntPoint::ZeroValue, FIntPoint Size = FIntPoint::ZeroValue);` (scope `NFORDenoise`) — TargetTexture += SourceTexture;
- L244 _prototype_ `void AddAccumulateConstantRegionPass(FRDGBuilder& GraphBuilder, const FLinearColor& ConstantValue, const FRDGTextureRef& TargetTexture, const FRDGTextureRef& Mask = nullptr, FIntPoint SourcePosition = FIntPoint::ZeroValue, FIntPoint TargetPosition = FIntPoint::ZeroValue, FIntPoint Size = FIntPoint::ZeroValue);` (scope `NFORDenoise`) — TargetTexture.rgb = TargetTexture.rgb + lerp(ConstantValue, ConstantValue[mask], Mask != nullptr);
- L248 _prototype_ `void AddCopyMirroredTexturePass(FRDGBuilder& GraphBuilder, const FRDGTextureRef& SourceTexture, const FRDGTextureRef& TargetTexture, FIntPoint SourcePosition = FIntPoint::ZeroValue, FIntPoint TargetPosition = FIntPoint::ZeroValue, FIntPoint Size = FIntPoint::ZeroValue, bool bAlphaOnly = false);` (scope `NFORDenoise`) — Copy texture with mirrored border of source texture;
- L252 _prototype_ `void AddCopyMirroredTexturePass(FRDGBuilder& GraphBuilder, const FRDGTextureRef& SourceTexture, const FRDGTextureRef& TargetTexture, int32 Channel, ETextureCopyType CopyType, FIntPoint SourcePosition = FIntPoint::ZeroValue, FIntPoint TargetPosition = FIntPoint::ZeroValue, FIntPoint Size = FIntPoint::ZeroValue);` (scope `NFORDenoise`) — Copy a channel from the source image to the target image where ETextureCopyType indicates which image is single channel;
- L341 _prototype_ `FRDGTextureRef GetPreAlbedoDivideMask(FRDGBuilder& GraphBuilder, const FSceneView& View, const FRDGTextureRef& Normal, const FRDGTextureRef& NormalVariance);` (scope `NFORDenoise`)
- L343 _prototype_ `void AddNormalizeRadianceVariancePass(FRDGBuilder& GraphBuilder, const FRDGTextureRef& Albedo, const FRDGTextureRef& RadianceVariance);` (scope `NFORDenoise`)
- L347 _prototype_ `void AddAdjustFeatureRangePass(FRDGBuilder& GraphBuilder, const FFeatureDesc& FeatureDesc, float MaxValue);` (scope `NFORDenoise`) — Adjust feature and variance range based on MaxValue to suppress random specular noise. NewValue = min(Value, MaxValue). Std = lerp(Std,(MaxValue/Value)*Std,Value > MaxValue).
- L353 _prototype_ `SHADER_PARAMETER(int32, PatchSize) SHADER_PARAMETER(int32, PatchDistance) SHADER_PARAMETER(float, Bandwidth) END_SHADER_PARAMETER_STRUCT() BEGIN_SHADER_PARAMETER_STRUCT(FNonLocalMeanWeightAtlasDispatchParameters, ) SHADER_PARAMETER(int32, DispatchId) SHADER_PARAMETER(FIntPoint, DispatchTileSize) SHADER_PARAMETER(int32, DispatchTileCount) SHADER_PARAMETER(FIntRect, SeparableFilteringRegion) SHADER_PARAMETER(FIntVector, DispatchRegionSize) END_SHADER_PARAMETER_STRUCT() FNonLocalMeanParameters GetNonLocalMeanParameters(int32 PatchSize, int32 PatchDistance, float Bandwidth);` (scope `NFORDenoise`)
- L675 _namespace_ `namespace RegressionKernel` (scope `NFORDenoise`)
- L677 _prototype_ `FRDGBufferRef AllocateMatrixfBuffer(FRDGBuilder& GraphBuilder, int32 NumOfMatrices, int32 Dim0, int32 Dim1, const TCHAR* Name);` (scope `NFORDenoise::RegressionKernel`)
- L686 _function_ `static const TCHAR* GetEventName(EWeightedMultiplicationType WeightedMultiplicationType)` (scope `NFORDenoise::RegressionKernel`)
- L1105 _member_ `FNFORTextureDesc Feature;` (scope `NFORDenoise::FFeatureDesc::__anon95f4c9ac010a`)
- L1106 _member_ `FNFORTextureDesc Data;` (scope `NFORDenoise::FFeatureDesc::__anon95f4c9ac010a`)
- L1121 _typedef_ `typedef FFeatureDesc FRadianceDesc;` (scope `NFORDenoise`)
- L1124 _prototype_ `void FilterFeatures( FRDGBuilder& GraphBuilder, const FSceneView& View, const TArray<FFeatureDesc>& FeatureDescs);` (scope `NFORDenoise`) — Denoise features based on non-local mean on its variance texture.
- L1130 _prototype_ `bool FilterMain( FRDGBuilder& GraphBuilder, const FSceneView& View, const TArray<FRadianceDesc>& Radiances, const TArray<FFeatureDesc>& FeatureDescs, const FRDGTextureRef& DenoisedRadiance);` (scope `NFORDenoise`) — Denoise the radiance based on spatial temporal features.

### `Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORRegressionCPUSolver.h` (Private)


#### Free symbols / members of external scopes

- L11 _prototype_ `void SolveWeightedLSRCPU( FRDGBuilder& GraphBuilder, const FSceneView& View, const FRDGBufferRef& Feature, const FRDGTextureRef& Radiance, const FRDGBufferRef& NonLocalMeanWeightsBuffer, const FRDGTextureRef& FilteredRadiance, const FWeightedLSRDesc& WeightedLSRDesc, const FRDGBufferRef Radiances, const FRDGTextureRef& SourceAlbedo);`
- L23 _prototype_ `void SolveLinearEquationCPU( FRDGBuilder& GraphBuilder, const FRDGBufferRef& A, const FRDGBufferRef& B, const int32 NumOfElements, const FIntPoint BDim, const FRDGBufferRef& X);` — Solve AX=B

### `Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORWeightedLSRCommon.h` (Private)


#### enum `EWeightedLSRSolverType`  
`enum class EWeightedLSRSolverType : uint8`  
_L8-12_
- L10 _public enumerator_ `Full` — whole image input
- L11 _public enumerator_ `Tiled` — tiled image input, Overlapping region data are included

#### struct `FWeightedLSRDesc`  
`struct FWeightedLSRDesc`  
_L14-31_
- L16 _public member_ `int32 NumOfFeatureChannels;` — F
- L17 _public member_ `int32 NumOfFeatureChannelsPerFrame;`
- L18 _public member_ `int32 NumOfWeightsPerPixel;` — N
- L19 _public member_ `int32 NumOfWeightsPerPixelPerFrame;`
- L20 _public member_ `int32 NumOfRadianceChannels;`
- L21 _public member_ `int32 NumOfRadianceChannelsPerFrame;`
- L22 _public member_ `int32 Width;` — W
- L23 _public member_ `int32 Height;` — H
- L25 _public member_ `FIntPoint TileStartPosition;` — The start position of the tile
- L26 _public member_ `FIntPoint Offset;` — Used in tiled mode as we need to copy data outside of the region
- L28 _public member_ `int32 NumOfFrames;` — T
- L29 _public member_ `FIntPoint TextureSize;` — (W+2B,H+2B) where B is the border size
- L30 _public member_ `EWeightedLSRSolverType SolverType;`

### `Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Public/NFORDenoise.h` (Public)


#### class `FNFORDenoiseModule`  
`class FNFORDenoiseModule : public IModuleInterface`  
_L12-18_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNFORDenoise, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNFORDenoise, Log, All);`
