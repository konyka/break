# Plugins / NNEHlslShaders

- module root: `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders`
- headers: 32; symbols: 529
- symbol kinds: class=56, enum=21, enumerator=149, function=2, member=53, namespace=112, prototype=110, struct=1, typedef=25
- PrivateDependencyModuleNames: Core, Engine, NNE, Projects, RHI, RenderCore

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersBase.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FHlslShaderBase`  
`class FHlslShaderBase : public FGlobalShader`  
_L9-17_
- inherits: `FGlobalShader`
- L13 _public prototype_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`
- L15 _public function_ `FHlslShaderBase()`
- L16 _public function_ `FHlslShaderBase(const ShaderMetaType::CompiledShaderInitializerType& initType) : FGlobalShader(initType)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L7 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersBatchNormalizationCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FBatchNormalizationConstants`  
`class FBatchNormalizationConstants`  
_L12-17_
- L16 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::TBatchNormalizationCS`  
`class TBatchNormalizationCS : public FHlslShaderBase`  
_L19-41_
- inherits: `FHlslShaderBase`
- L21 _private prototype_ `DECLARE_GLOBAL_SHADER(TBatchNormalizationCS);`
- L27 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, X) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Scales) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Bias) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Mean) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Var) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, DimC) SHADER_PARAMETER(uint32, SpatialVolume) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(float, Epsilon) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L10 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersCastCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FCastConstants`  
`class FCastConstants`  
_L12-16_
- L15 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::TCastCS`  
`class TCastCS : public FHlslShaderBase`  
_L18-40_
- inherits: `FHlslShaderBase`
- L20 _private prototype_ `DECLARE_GLOBAL_SHADER(TCastCS);`
- L25 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FInputType,FOutputType>;`
- L31 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<uint>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<uint>, Output) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`
- L39 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L10 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersConvCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EConvAlgorithm`  
`enum class EConvAlgorithm : uint8`  
_L11-15_
- L13 _public enumerator_ `SharedMemory = 0`
- L14 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::EConvGroupSize`  
`enum class EConvGroupSize : uint8`  
_L17-23_
- L19 _public enumerator_ `Size128 = 0`
- L20 _public enumerator_ `Size256`
- L21 _public enumerator_ `Size512`
- L22 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::EConvAutoPad`  
`enum class EConvAutoPad : uint8`  
_L25-32_
- L27 _public enumerator_ `NOTSET = 0` — Use pad values passed in the array
- L28 _public enumerator_ `SAME_UPPER` — Auto-pad to match input and output shape with potetnial extra padding at the end
- L29 _public enumerator_ `SAME_LOWER` — Auto-pad to match input and output shape with potetnial extra padding at the beginning
- L30 _public enumerator_ `VALID` — Set all paddings to zero
- L31 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FConvConstants`  
`class FConvConstants`  
_L34-40_
- L37 _public member_ `static const int32 MAX_NUM_DIMENSIONS{4};`
- L38 _public member_ `static const int32 MIN_NUM_READS_PER_THREAD_POW2{1};`
- L39 _public member_ `static const int32 MAX_NUM_READS_PER_THREAD_POW2{4};`

#### class `UE::NNEHlslShaders::Internal::FConvCS`  
`class FConvCS : public FHlslShaderBase`  
_L42-116_
- inherits: `FHlslShaderBase`
- L44 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvCS);`
- L53 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FConvAlgorithm, FConvAreWeightsTransposed, FConvGroupSize, FConvNumDimensions, FConvNumReadsPerThread, FConvHasB>;`
- L57 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, X) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, W) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Y) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, B) SHADER_PARAMETER_ARRAY(FIntVector4, Dilation_Stride_XBlockStartOffset_DilationXBlockStride, [FConvConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FIntVector4, GroupStride_GroupShape_GroupThreadStride_StrideXBlockStride, [FConvConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FIntVector4, YDimension_YMemoryStride_XDimension_XMemoryStride, [FConvConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FIntVector4, XBlockStartStride_XBlockStride_WDimension_WDimensionDilationXBlockStride, [FConvConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FVector4f, OneDiv_GroupStride_GroupThreadStride_XBlockStride, [FConvConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(int32, NumWChannels) SHADER_PARAMETER(int32, NumWFeatures) SHADER_PARAMETER(int32, YBatchStride) SHADER_PARAMETER(int32, YOutputKernelStride) SHADER_PARAMETER(int32, XBatchStride) SHADER_PARAMETER(int32, XChannelStride) SHADER_PARAMETER(int32, XBlockSize) SHADER_PARAMETER(int32, NumChannelBatches) SHADER_PARAMETER(int32, NumChannelsPerBatch) SHADER_PARAMETER(int32, WOutputKernelStride) SHADER_PARAMETER(int32, WChannelBatchSize) SHADER_PARAMETER(int32, WChannelSize) SHADER_PARAMETER(float, GroupsDivM) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& InPar ...`
- L82 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L85 _public prototype_ `static TArray<int32> GetOutputShape(TArrayView<const uint32> XShape, TArrayView<const uint32> WShape, EConvAutoPad AutoPad, TArrayView<const int32> Dilations, TArrayView<const int32> Strides, TArrayView<const int32> Pads);`
- L87 _public prototype_ `static void FillInParameters(EConvGroupSize GroupSize, TArrayView<const uint32> XShape, TArrayView<const uint32> WShape, bool HasB, EConvAutoPad AutoPad, int Group, TArrayView<const int32> Dilations, TArrayView<const int32> Strides, TArrayView<const int32> Pads, FConvCS::FParameters& Parameters);`
- L90 _public prototype_ `static int32 GetNumReadsPerThread(EConvGroupSize GroupSize, TArrayView<const uint32> WShape, TArrayView<const int32> Dilations, TArrayView<const int32> Strides);`
- L99 _public prototype_ `static TArray<int32> GetGroupShape(EConvGroupSize GroupSize, int32 NumDimensions);` — @brief Computes the group shape such that all dimension have roughly equal sizes. @param GroupSize The enum indicating the number of threads contained by a single group. @param NumDimensions The number of dimensions. @return TArray<int32> An array of size \p NumDimensions containing the number of threads in each dimension to form a volume of a total number of threads indicated by \p GroupSize
- L108 _public prototype_ `static FIntVector GetGroupCount(TArrayView<const int32> YShape, TArrayView<const int32> GroupShape);` — @brief Get the group count vector used to launch the gpu shader thread groups @param YShape The shape of the output as computed by GetOutputShape() @param YShape The shape of a single thread group as computed by GetGroupShape() @return FIntVector The number of thread groups to instantiate. z corresponds to the batch and y to the output kernel.
- L110 _public prototype_ `static EConvGroupSize GetBiggestCompatibleGroupSize(TArrayView<const uint32> WShape, TArrayView<const int32> Dilations, TArrayView<const int32> Strides);`
- L111 _public prototype_ `static EConvGroupSize GetMinimalGroupSize(TArrayView<const int32> WShape);`
- L113 _public prototype_ `static TArray<int32> GetPadding(TArrayView<const uint32> XShape, TArrayView<const uint32> WShape, EConvAutoPad AutoPad, TArrayView<const int32> Dilations, TArrayView<const int32> Strides, TArrayView<const int32> Pads);`
- L115 _public prototype_ `static void LexFromString(EConvAutoPad& OutValue, const TCHAR* StringVal);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersConvMatmulCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FConvMatmulCS`  
`class FConvMatmulCS : public FHlslShaderBase`  
_L11-41_
- inherits: `FHlslShaderBase`
- L13 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvMatmulCS);`
- L18 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FConvMatmulAreWeightsTransposed, FConvMatmulHasBias>;`
- L22 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Weight) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Bias) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER(int32, Ci) SHADER_PARAMETER(int32, Hi) SHADER_PARAMETER(int32, Wi) SHADER_PARAMETER(int32, Cw) SHADER_PARAMETER(int32, Hw) SHADER_PARAMETER(int32, Ww) SHADER_PARAMETER(int32, Ho) SHADER_PARAMETER(int32, Wo) SHADER_PARAMETER(int32, StrideH) SHADER_PARAMETER(int32, StrideW) SHADER_PARAMETER(int32, PadLeft) SHADER_PARAMETER(int32, PadTop) END_SHADER_PARAMETER_STRUCT() static FIntVector GetGroupCount(TConstArrayView<uint32> OutputShape);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersConvTransposeCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EConvTransposeAlgorithm`  
`enum class EConvTransposeAlgorithm : uint8`  
_L11-15_
- L13 _public enumerator_ `SharedMemory = 0`
- L14 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::EConvTransposeGroupSize`  
`enum class EConvTransposeGroupSize : uint8`  
_L17-23_
- L19 _public enumerator_ `Size128 = 0`
- L20 _public enumerator_ `Size256`
- L21 _public enumerator_ `Size512`
- L22 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::EConvTransposeAutoPad`  
`enum class EConvTransposeAutoPad : uint8`  
_L25-32_
- L27 _public enumerator_ `NOTSET = 0` — Use pad values passed in the array
- L28 _public enumerator_ `SAME_UPPER` — Auto-pad to match input and output shape with potetnial extra padding at the end
- L29 _public enumerator_ `SAME_LOWER` — Auto-pad to match input and output shape with potetnial extra padding at the beginning
- L30 _public enumerator_ `VALID` — Set all paddings to zero
- L31 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FConvTransposeConstants`  
`class FConvTransposeConstants`  
_L34-41_
- L38 _public member_ `static const int32 MAX_NUM_DIMENSIONS{4};`
- L39 _public member_ `static const int32 MIN_NUM_READS_PER_THREAD_POW2{1};`
- L40 _public member_ `static const int32 MAX_NUM_READS_PER_THREAD_POW2{3};`

#### class `UE::NNEHlslShaders::Internal::FConvTransposeCS`  
`class FConvTransposeCS : public FHlslShaderBase`  
_L43-108_
- inherits: `FHlslShaderBase`
- L45 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvTransposeCS);`
- L46 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FConvTransposeCS, FHlslShaderBase);`
- L53 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FConvTransposeAlgorithm, FConvTransposeGroupSize, FConvTransposeNumStackDimensions, FConvTransposeNumReadsPerThread, FConvTransposeHasB>;`
- L58 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, X) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, W) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Y) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, B) SHADER_PARAMETER_ARRAY(FIntVector4, Dilation_Stride_XBlockStartOffset_DilationXBlockStride, [FConvTransposeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FIntVector4, GroupStride_GroupShape_GroupThreadStride_StrideXBlockStride, [FConvTransposeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FIntVector4, YDimension_YMemoryStride_XDimension_XMemoryStride, [FConvTransposeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FIntVector4, XBlockStartStride_XBlockStride_WDimension_WDimensionDilationXBlockStride, [FConvTransposeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FVector4f, OneDiv_GroupStride_GroupThreadStride_OneDivStride, [FConvTransposeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(int32, NumWChannels) SHADER_PARAMETER(int32, NumOutChannelsDivGroup) SHADER_PARAMETER(int32, YBatchStride) SHADER_PARAMETER(int32, YOutputKernelStride) SHADER_PARAMETER(int32, XBatchStride) SHADER_PARAMETER(int32, XChannelStride) SHADER_PARAMETER(int32, XBlockSize) SHADER_PARAMETER(int32, NumChannelBatches) SHADER_PARAMETER(int32, NumChannelsPerBatch) SHADER_PARAMETER(int32, WOutputKernelStride) SHADER_PARAMETER(int32, WChannelBatchSize) SHADER_PARAMETER(int32, WChannelSize) SHADER_PARAMETER(float, GroupsDivM) SHADER_PARAMETER(float, OneDivGroup) END_SHADER_PARAMETER_S ...`
- L85 _public prototype_ `static TArray<int32> GetOutputShape(TArrayView<const uint32> XShape, TArrayView<const uint32> WShape, EConvTransposeAutoPad AutoPad, TArrayView<const int32> Dilations, TArrayView<const int32> Strides, TArrayView<const int32> Pads, TArrayView<const int32> OutputPadding, int32 Group);`
- L87 _public prototype_ `static void FillInParameters(EConvTransposeGroupSize GroupSize, TArrayView<const uint32> XShape, TArrayView<const uint32> WShape, bool HasB, EConvTransposeAutoPad AutoPad, int32 Group, TArrayView<const int32> Dilations, TArrayView<const int32> Strides, TArrayView<const int32> Pads, TArrayView<const int32> OutputPadding, FConvTransposeCS::FParameters& Parameters);`
- L89 _public prototype_ `static int32 GetNumReadsPerThread(EConvTransposeGroupSize GroupSize, TArrayView<const uint32> WShape, TArrayView<const int32> Dilations, TArrayView<const int32> Strides);`
- L91 _public prototype_ `static TArray<int32> GetGroupShape(EConvTransposeGroupSize GroupSize, int32 NumDimensions);`
- L93 _public prototype_ `static FIntVector GetGroupCount(TArrayView<const int32> YShape, TArrayView<const int32> GroupShape);`
- L95 _public prototype_ `static EConvTransposeGroupSize GetMinimalGroupSize(TArrayView<const uint32> WShape);`
- L97 _public prototype_ `static void LexFromString(EConvTransposeAutoPad& OutValue, const TCHAR* StringVal);`
- L101 _private prototype_ `static TArray<int32> GetXBlockShape(TArrayView<const int32> GroupShape, TArrayView<const uint32> WShape, TArrayView<const int32> Dilations, TArrayView<const int32> Strides);`
- L103 _private prototype_ `static TArray<int32> GetPadding(TArrayView<const uint32> WShape, EConvTransposeAutoPad AutoPad, TArrayView<const int32> Dilations, TArrayView<const int32> Strides, TArrayView<const int32> Pads, TArrayView<const int32> OutputPadding);`
- L105 _private prototype_ `static int32 GetNumThreadsPerGroup(EConvTransposeGroupSize GroupSize);`
- L107 _private prototype_ `static TArray<int32> GetGridShape(TArrayView<const int32> YShape, TArrayView<const int32> GroupShape);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersConvWinogradInputCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FConvWinogradInputConstants`  
`class FConvWinogradInputConstants`  
_L10-15_
- L14 _public member_ `static const int32 THREADGROUP_SIZE_X{ 32 };`

#### class `UE::NNEHlslShaders::Internal::FConvWinogradInputCS`  
`class FConvWinogradInputCS : public FHlslShaderBase`  
_L17-39_
- inherits: `FHlslShaderBase`
- L19 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvWinogradInputCS);`
- L24 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER(int32, C) SHADER_PARAMETER(int32, H) SHADER_PARAMETER(int32, W) SHADER_PARAMETER(int32, WBlockCount) SHADER_PARAMETER(int32, CInputStride) SHADER_PARAMETER(int32, HInputStride) SHADER_PARAMETER(int32, NiOutputStride) SHADER_PARAMETER(int32, MatrixOutputStride) SHADER_PARAMETER(int32, COutputStride) SHADER_PARAMETER(int32, HOutputStride) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L8 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersConvWinogradMMMCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FConvWinogradMMMCS`  
`class FConvWinogradMMMCS : public FHlslShaderBase`  
_L12-42_
- inherits: `FHlslShaderBase`
- L14 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvWinogradMMMCS);`
- L19 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FDataType, FBlockSizeN>;`
- L23 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Weight) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER(int32, M) SHADER_PARAMETER(int32, N) SHADER_PARAMETER(int32, K) SHADER_PARAMETER(int32, MatrixInputStride) SHADER_PARAMETER(int32, KInputStride) SHADER_PARAMETER(int32, MatrixWeightStride) SHADER_PARAMETER(int32, KWeightStride) SHADER_PARAMETER(int32, MatrixOutputStride) SHADER_PARAMETER(int32, NOutputStride) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`
- L39 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L41 _public prototype_ `static int GetOptimalBlockSizeN(int M, int K, int N);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L10 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersConvWinogradOutputCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FConvWinogradOutputConstants`  
`class FConvWinogradOutputConstants`  
_L12-17_
- L16 _public member_ `static const int32 THREADGROUP_SIZE_X{ 32 };`

#### class `UE::NNEHlslShaders::Internal::FConvWinogradOutputCS`  
`class FConvWinogradOutputCS : public FHlslShaderBase`  
_L19-48_
- inherits: `FHlslShaderBase`
- L21 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvWinogradOutputCS);`
- L26 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FHasBias, FDataType>;`
- L30 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Bias) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER(int32, C) SHADER_PARAMETER(int32, H) SHADER_PARAMETER(int32, W) SHADER_PARAMETER(int32, WBlockCount) SHADER_PARAMETER(int32, NiInputStride) SHADER_PARAMETER(int32, MatrixInputStride) SHADER_PARAMETER(int32, CInputStride) SHADER_PARAMETER(int32, HInputStride) SHADER_PARAMETER(int32, COutputStride) SHADER_PARAMETER(int32, HOutputStride) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`
- L47 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L10 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersConvWinogradWeightsCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FConvWinogradWeightsConstants`  
`class FConvWinogradWeightsConstants`  
_L10-15_
- L14 _public member_ `static const int32 THREADGROUP_SIZE_X{ 32 };`

#### class `UE::NNEHlslShaders::Internal::FConvWinogradWeightsCS`  
`class FConvWinogradWeightsCS : public FHlslShaderBase`  
_L17-34_
- inherits: `FHlslShaderBase`
- L19 _private prototype_ `DECLARE_GLOBAL_SHADER(FConvWinogradWeightsCS);`
- L24 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER(int32, Ci) SHADER_PARAMETER(int32, Cw) SHADER_PARAMETER(int32, CwInputStride) SHADER_PARAMETER(int32, MatrixOutputStride) SHADER_PARAMETER(int32, CiOutputStride) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L8 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersCumSumCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FCumSumConstants`  
`class FCumSumConstants`  
_L17-24_
- L20 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L21 _public member_ `static const int32 THREADGROUP_SIZE{ 256 };`
- L22 _public member_ `static const int32 VALUES_PER_THREAD{ 12 };`
- L23 _public member_ `static const int32 INIT_THREADGROUP_SIZE{ 768 };`

#### struct `UE::NNEHlslShaders::Internal::FPartitionDescriptor`  
`struct FPartitionDescriptor`  
_L26-32_
- L28 _public member_ `int32 StatusFlag;`
- L29 _public member_ `float Aggregate;`
- L30 _public member_ `float InclusivePrefix;`
- L31 _public member_ `int32 PadToQWord;`

#### class `UE::NNEHlslShaders::Internal::TInitCumSumCS`  
`class TInitCumSumCS : public FHlslShaderBase`  
_L34-53_
- inherits: `FHlslShaderBase`
- L36 _private prototype_ `DECLARE_GLOBAL_SHADER(TInitCumSumCS);`
- L39 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<>;`
- L44 _public prototype_ `SHADER_PARAMETER(uint32, NumThreadGroupsPerScan) SHADER_PARAMETER(uint32, NumThreadGroupsY) SHADER_PARAMETER(uint32, NumThreadGroupsZ) SHADER_PARAMETER(uint32, NumInitThreadGroups) SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<uint32>, GlobalPartitionIndex) SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FPartitionDescriptor>, PartitionDescriptor) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### class `UE::NNEHlslShaders::Internal::TCumSumCS`  
`class TCumSumCS : public FHlslShaderBase`  
_L55-79_
- inherits: `FHlslShaderBase`
- L57 _private prototype_ `DECLARE_GLOBAL_SHADER(TCumSumCS);`
- L60 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<>;`
- L65 _public prototype_ `SHADER_PARAMETER(uint32, NumThreadGroupsPerScan) SHADER_PARAMETER(uint32, NumThreadGroupsY) SHADER_PARAMETER(uint32, NumThreadGroupsZ) SHADER_PARAMETER(uint32, NumScanValues) SHADER_PARAMETER(uint32, Axis) SHADER_PARAMETER(uint32, AxisStride) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, TensorInfo, [FCumSumConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<uint32>, GlobalPartitionIndex) SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<FPartitionDescriptor>, PartitionDescriptor) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace NNE` (scope `UE`)
- L12 _namespace_ `namespace Internal` (scope `UE::NNE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L14 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersElementWiseBinaryCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FElementWiseBinaryConstants`  
`class FElementWiseBinaryConstants`  
_L12-18_
- L16 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L17 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::TElementWiseBinaryCS`  
`class TElementWiseBinaryCS : public FHlslShaderBase`  
_L20-45_
- inherits: `FHlslShaderBase`
- L22 _private prototype_ `DECLARE_GLOBAL_SHADER(TElementWiseBinaryCS);`
- L27 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FOperatorType, FBinaryNumDimensions>;`
- L32 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, LHSInput) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, RHSInput) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, TensorInfo, [FElementWiseBinaryConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L44 _private prototype_ `static const FString GetOpFunc(EElementWiseBinaryOperatorType OpType);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L10 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersElementWiseUnaryCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FElementWiseUnaryConstants`  
`class FElementWiseUnaryConstants`  
_L12-17_
- L16 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::TElementWiseUnaryCS`  
`class TElementWiseUnaryCS : public FHlslShaderBase`  
_L19-50_
- inherits: `FHlslShaderBase`
- L21 _private prototype_ `DECLARE_GLOBAL_SHADER(TElementWiseUnaryCS);`
- L27 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FOperatorType,FAlphaOnGPU,FBetaOnGPU>;`
- L32 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(float, Alpha) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, AlphaTensor) SHADER_PARAMETER(float, Beta) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, BetaTensor) SHADER_PARAMETER(float, Gamma) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`
- L45 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L49 _private prototype_ `static const FString GetOpFunc(EElementWiseUnaryOperatorType OpType);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L10 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersElementWiseVariadicCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FElementWiseVariadicConstants`  
`class FElementWiseVariadicConstants`  
_L12-19_
- L16 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L17 _public member_ `static const uint32 NUM_GROUP_THREADS{ 256 };`
- L18 _public member_ `static const uint32 MAX_NUM_INPUT{ 4 };`

#### class `UE::NNEHlslShaders::Internal::TElementWiseVariadicCS`  
`class TElementWiseVariadicCS : public FHlslShaderBase`  
_L21-53_
- inherits: `FHlslShaderBase`
- L23 _private prototype_ `DECLARE_GLOBAL_SHADER(TElementWiseVariadicCS);`
- L31 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FOperatorType, FApplyScale, FOutputAsInput, FNumInput, FVariadicNumDimensions>;`
- L36 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input0) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input1) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input2) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input3) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, InputTensorInfo, [FElementWiseVariadicConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FUintVector4, OutputTensorInfo, [FElementWiseVariadicConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(float, Scale) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L52 _private prototype_ `static const FString GetOpFunc(EElementWiseVariadicOperatorType OpType);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L10 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersGatherCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FGatherConstants`  
`class FGatherConstants`  
_L13-19_
- L17 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L18 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::TGatherCS`  
`class TGatherCS : public FHlslShaderBase`  
_L22-50_
- inherits: `FHlslShaderBase`
- desc: template <typename DataElementType, typename IndicesElementType>
- L24 _private prototype_ `DECLARE_GLOBAL_SHADER(TGatherCS);`
- L29 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FGatherNumOutputDimensions,FGather64BitIndices>;`
- L34 _public prototype_ `SHADER_PARAMETER(int32, Axis) SHADER_PARAMETER(int32, OutputSize) SHADER_PARAMETER(int32, NumDataDimensions) SHADER_PARAMETER(int32, NumIndicesDimensions) SHADER_PARAMETER_ARRAY(FIntVector4, DataStride_IndicesStride_OutputStride_DataSizes, [FGatherConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FVector4f, OneDivDataStride_OneDivIndicesStride_OneDivOutputStride, [FGatherConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Data) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<int32>, Indices) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L47 _public prototype_ `static void FillInParameters(int32 Axis, const NNE::FTensorShape& Data, const NNE::FTensorShape& Indices, FParameters& Parameters);`
- L49 _public prototype_ `static FIntVector GetGroupCount(const FParameters& Parameters);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNE` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersGatherElementsCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FGatherElementsConstants`  
`class FGatherElementsConstants`  
_L11-17_
- L15 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L16 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::FGatherElementsCS`  
`class FGatherElementsCS : public FHlslShaderBase`  
_L19-42_
- inherits: `FHlslShaderBase`
- L21 _private prototype_ `DECLARE_GLOBAL_SHADER(FGatherElementsCS);`
- L26 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FGatherElementsDimensions, FGatherElements64BitIndices>;`
- L30 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<int32>, Indices) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FVector4f, OneDivOutputStrides, [FGatherElementsConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FInt32Vector4, Input_OutputStrides, [FGatherElementsConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, Axis) SHADER_PARAMETER(uint32, AxisSize) SHADER_PARAMETER(uint32, OutputSize) SHADER_PARAMETER(uint32, ThreadCountX) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersGemmCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EGemmCScalar`  
`enum class EGemmCScalar : uint8`  
_L13-19_
- L15 _public enumerator_ `No = 0`
- L16 _public enumerator_ `Yes`
- L17 _public enumerator_ `NoBias`
- L18 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::EGemmAlgorithm`  
`enum class EGemmAlgorithm : uint8`  
_L21-39_
- L23 _public enumerator_ `Simple8x8 = 0`
- L24 _public enumerator_ `Simple16x16`
- L25 _public enumerator_ `Simple32x32`
- L26 _public enumerator_ `Simple256x1`
- L27 _public enumerator_ `SharedMemory8x8`
- L28 _public enumerator_ `SharedMemory16x16`
- L29 _public enumerator_ `SharedMemory32x32`
- L30 _public enumerator_ `MultiWrite1x16`
- L31 _public enumerator_ `MultiWrite2x16`
- L32 _public enumerator_ `MultiWrite1x32`
- L33 _public enumerator_ `MultiWrite2x32`
- L34 _public enumerator_ `MultiWrite4x32`
- L35 _public enumerator_ `MultiWrite2x64`
- L36 _public enumerator_ `MultiWrite4x64`
- L37 _public enumerator_ `MultiWrite8x64`
- L38 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FGemmConstants`  
`class FGemmConstants`  
_L41-46_
- L45 _public member_ `static const int32 MAX_NUM_STACK_DIMENSIONS{8};`

#### class `UE::NNEHlslShaders::Internal::TGemmCS`  
`class TGemmCS : public FHlslShaderBase`  
_L48-89_
- inherits: `FHlslShaderBase`
- L50 _private prototype_ `DECLARE_GLOBAL_SHADER(TGemmCS);`
- L56 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FGemmCScalar, FGemmAlgorithm, FGemmNumStackDimensions>;`
- L61 _public prototype_ `SHADER_PARAMETER(float, Alpha) SHADER_PARAMETER(float, Beta) SHADER_PARAMETER(int32, TransA) SHADER_PARAMETER(int32, TransB) SHADER_PARAMETER(uint32, M) SHADER_PARAMETER(uint32, N) SHADER_PARAMETER(uint32, K) SHADER_PARAMETER(uint32, MxK) SHADER_PARAMETER(uint32, KxN) SHADER_PARAMETER(uint32, MxN) SHADER_PARAMETER(uint32, CWidth) SHADER_PARAMETER(uint32, CHeight) SHADER_PARAMETER(float, CScalar) SHADER_PARAMETER_ARRAY(FUint32Vector4, StackShapeA_StackShapeB_StackStrideA_StackStrideB, [FGemmConstants::MAX_NUM_STACK_DIMENSIONS]) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, A) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, B) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, C) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Y) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L83 _public prototype_ `static void FillInParameters(float Alpha, float Beta, int32 TransA, int32 TransB, const NNE::FTensorShape& InputA, const NNE::FTensorShape& InputB, const NNE::FTensorShape* InputC, float CScalar, FParameters& Parameters);`
- L85 _public prototype_ `static void FillInParametersMatMul(const NNE::FTensorShape& InputA, const NNE::FTensorShape& InputB, FParameters& Parameters);`
- L87 _public prototype_ `static FIntVector GetGroupCount(const FParameters& Parameters, EGemmAlgorithm Algorithm, int32 NumStackDimensions);`
- L88 _public prototype_ `static EGemmAlgorithm GetAlgorithm(const FParameters& Parameters);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNE` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersInstanceNormalizationCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FInstanceNormalizationConstants`  
`class FInstanceNormalizationConstants`  
_L13-17_
- L16 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::TInstanceNormalizationCS`  
`class TInstanceNormalizationCS : public FHlslShaderBase`  
_L19-40_
- inherits: `FHlslShaderBase`
- L21 _private prototype_ `DECLARE_GLOBAL_SHADER(TInstanceNormalizationCS);`
- L27 _public prototype_ `SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(uint32, InstanceSize) SHADER_PARAMETER(uint32, ChannelSize) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputScale) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputBias) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputMean) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputInvStdDev) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNE` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersLayerNormalizationCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FLayerNormalizationConstants`  
`class FLayerNormalizationConstants`  
_L13-18_
- L16 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L17 _public member_ `static const int32 NUM_GROUP_THREADS{ 768 };`

#### class `UE::NNEHlslShaders::Internal::TLayerNormalizationCS`  
`class TLayerNormalizationCS : public FHlslShaderBase`  
_L20-50_
- inherits: `FHlslShaderBase`
- L22 _private prototype_ `DECLARE_GLOBAL_SHADER(TLayerNormalizationCS);`
- L27 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FLayerNormalizationNumDimensions, FLayerNormalizationHasB>;`
- L32 _public prototype_ `SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, Axis) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(float, Epsilon) SHADER_PARAMETER(uint32, LayerSize) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_ARRAY(FUintVector4, InputTensorInfo, [FLayerNormalizationConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputScale) SHADER_PARAMETER_ARRAY(FUintVector4, ScaleTensorInfo, [FLayerNormalizationConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputBias) SHADER_PARAMETER_ARRAY(FUintVector4, BiasTensorInfo, [FLayerNormalizationConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputMean) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputInvStdDev) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) END_SHADER_PARAMETER_STRUCT() static void FillInParameters(TConstArrayView<uint32> Shape, int32 Axis, float Epsilon, FParameters* Parameters);`
- L49 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNE` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersLog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeRDGHlsl, Log, All);`

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersOperator.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EElementWiseUnaryOperatorType`  
`enum class EElementWiseUnaryOperatorType : uint8`  
_L11-52_
- desc: One input element-wise operators
- L13 _public enumerator_ `Abs`
- L14 _public enumerator_ `Acos`
- L15 _public enumerator_ `Acosh`
- L16 _public enumerator_ `Asin`
- L17 _public enumerator_ `Asinh`
- L18 _public enumerator_ `Atan`
- L19 _public enumerator_ `Atanh`
- L21 _public enumerator_ `Ceil` — BitShift, //Note: need integer tensors
- L22 _public enumerator_ `Clip`
- L23 _public enumerator_ `Cos`
- L24 _public enumerator_ `Cosh`
- L25 _public enumerator_ `Elu`
- L26 _public enumerator_ `Erf`
- L27 _public enumerator_ `Exp`
- L28 _public enumerator_ `Floor`
- L29 _public enumerator_ `IsInf`
- L30 _public enumerator_ `IsNan`
- L31 _public enumerator_ `HardSigmoid`
- L32 _public enumerator_ `HardSwish`
- L33 _public enumerator_ `LeakyRelu`
- L34 _public enumerator_ `Log`
- L35 _public enumerator_ `Neg`
- L37 _public enumerator_ `Reciprocal` — Not,      //Note: need bool tensors
- L38 _public enumerator_ `Relu`
- L39 _public enumerator_ `Round`
- L40 _public enumerator_ `Selu`
- L41 _public enumerator_ `Sigmoid`
- L42 _public enumerator_ `Sign`
- L43 _public enumerator_ `Sin`
- L44 _public enumerator_ `Sinh`
- L45 _public enumerator_ `Softplus`
- L46 _public enumerator_ `Softsign`
- L47 _public enumerator_ `Sqrt`
- L48 _public enumerator_ `Tan`
- L49 _public enumerator_ `Tanh`
- L51 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::EElementWiseBinaryOperatorType`  
`enum class EElementWiseBinaryOperatorType : uint8`  
_L56-75_
- desc: Two inputs element-wise operators with multi-directional broadcast see https://github.com/onnx/onnx/blob/main/docs/Broadcasting.md
- L58 _public enumerator_ `Add`
- L60 _public enumerator_ `Div` — And,           //Note: need boolean tensors
- L66 _public enumerator_ `Mod` — Equal,         //Note: need boolean tensors Greater,       //Note: need boolean tensors GreaterOrEqual,//Note: need boolean tensors Less,          //Note: need boolean tensors LessOrEqual,   //Note: need boolean tensors
- L67 _public enumerator_ `Mul`
- L69 _public enumerator_ `Prelu` — Or,            //Note: need boolean tensors
- L70 _public enumerator_ `Pow`
- L71 _public enumerator_ `Sub`
- L74 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::EElementWiseVariadicOperatorType`  
`enum class EElementWiseVariadicOperatorType : uint8`  
_L79-87_
- desc: Variable number of inputs element-wise operators with multi-directional broadcast see https://github.com/onnx/onnx/blob/main/docs/Broadcasting.md
- L81 _public enumerator_ `Max`
- L82 _public enumerator_ `Min`
- L83 _public enumerator_ `Mean`
- L84 _public enumerator_ `Sum`
- L86 _public enumerator_ `MAX`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L7 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersPadCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EPadMode`  
`enum class EPadMode : uint8`  
_L11-17_
- L13 _public enumerator_ `CONSTANT = 0`
- L14 _public enumerator_ `REFLECT`
- L15 _public enumerator_ `EDGE`
- L16 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FPadConstants`  
`class FPadConstants`  
_L19-25_
- L23 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L24 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::FPadCS`  
`class FPadCS : public FHlslShaderBase`  
_L27-49_
- inherits: `FHlslShaderBase`
- L29 _private prototype_ `DECLARE_GLOBAL_SHADER(FPadCS);`
- L34 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FPadMode, FPadNumDimensions>;`
- L39 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, TensorInfo, [FPadConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(float, Value) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L48 _public prototype_ `static void LexFromString(EPadMode& OutValue, const TCHAR* StringVal);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersPoolCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EPoolOperatorType`  
`enum class EPoolOperatorType : uint8`  
_L11-16_
- L13 _public enumerator_ `MAX_POOL`
- L14 _public enumerator_ `AVERAGE_POOL`
- L15 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FPoolConstants`  
`class FPoolConstants`  
_L18-25_
- L22 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L23 _public member_ `static const int32 MAX_NUM_SPATIAL_DIMENSIONS{ 6 };`
- L24 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::FPoolCS`  
`class FPoolCS : public FHlslShaderBase`  
_L27-49_
- inherits: `FHlslShaderBase`
- L29 _private prototype_ `DECLARE_GLOBAL_SHADER(FPoolCS);`
- L34 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FPoolNumSpatialDimensions, FPoolType>;`
- L39 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, TensorInfo, [FPoolConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FUintVector4, SpatialInfo, [FPoolConstants::MAX_NUM_SPATIAL_DIMENSIONS]) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(uint32, KernelVolume) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersReduceCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EReduceOperatorType`  
`enum class EReduceOperatorType : uint8`  
_L16-29_
- L18 _public enumerator_ `Average = 0`
- L19 _public enumerator_ `L1`
- L20 _public enumerator_ `L2`
- L21 _public enumerator_ `LogSumExp`
- L22 _public enumerator_ `Max`
- L23 _public enumerator_ `Min`
- L24 _public enumerator_ `Prod`
- L25 _public enumerator_ `Sum`
- L26 _public enumerator_ `SumExp` — Should not be used for multiple axis reduction
- L27 _public enumerator_ `AverageInvStdDev` — Should not be used for multiple axis reduction
- L28 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FReduceConstants`  
`class FReduceConstants`  
_L31-35_
- L34 _public member_ `static const int32 THREADGROUP_SIZE{ 768 };`

#### class `UE::NNEHlslShaders::Internal::TReduceCS`  
`class TReduceCS : public FHlslShaderBase`  
_L37-61_
- inherits: `FHlslShaderBase`
- L39 _private prototype_ `DECLARE_GLOBAL_SHADER(TReduceCS);`
- L43 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FReduceType>;`
- L48 _public prototype_ `SHADER_PARAMETER(int32, NumElemBeforeAxis) SHADER_PARAMETER(int32, AxisSize) SHADER_PARAMETER(int32, NumElemAfterAxis) SHADER_PARAMETER(FUintVector4, DispatchIdxAndStride) SHADER_PARAMETER(float, Epsilon) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output2) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L59 _public prototype_ `static void FillInParameters(TConstArrayView<uint32> Shape, int32 Axis, FParameters* Parameters);`
- L60 _public prototype_ `static void EnqueueRDG(FRDGBuilder& GraphBuilder, FParameters* Parameters, FRDGBufferRef Input, FRDGBufferRef Output, EReduceOperatorType OperatorType, FRDGBufferRef Output2 = {});`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace NNE` (scope `UE`)
- L12 _namespace_ `namespace Internal` (scope `UE::NNE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L14 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersResizeCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::ECoordTransMode`  
`enum class ECoordTransMode : uint8`  
_L12-22_
- L14 _public enumerator_ `HalfPixel = 0`
- L15 _public enumerator_ `HalfPixelSymmetric`
- L16 _public enumerator_ `PytorchHalfPixel`
- L17 _public enumerator_ `AlignCorners`
- L18 _public enumerator_ `Asymmetric`
- L19 _public enumerator_ `TfHalfPixelForNn`
- L20 _public enumerator_ `TfCropAndResize`
- L21 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::EMode`  
`enum class EMode : uint8`  
_L24-30_
- L26 _public enumerator_ `Nearest = 0`
- L27 _public enumerator_ `Linear`
- L28 _public enumerator_ `Cubic`
- L29 _public enumerator_ `MAX`

#### enum `UE::NNEHlslShaders::Internal::ENearestMode`  
`enum class ENearestMode : uint8`  
_L32-39_
- L34 _public enumerator_ `RoundPreferFloor = 0`
- L35 _public enumerator_ `RoundPreferCeil`
- L36 _public enumerator_ `Floor`
- L37 _public enumerator_ `Ceil`
- L38 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FResizeConstants`  
`class FResizeConstants`  
_L41-47_
- L45 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L46 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::FResizeCS`  
`class FResizeCS : public FHlslShaderBase`  
_L49-76_
- inherits: `FHlslShaderBase`
- L51 _private prototype_ `DECLARE_GLOBAL_SHADER(FResizeCS);`
- L58 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FResizeNumDimensions, FMode, FNearestMode, FCoordTransMode>;`
- L62 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_ARRAY(FUintVector4, InputTensorInfo, [FResizeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, OutputTensorInfo, [FResizeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FVector4f, ScalesData, [FResizeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& InParameters);`
- L72 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L73 _public prototype_ `static ECoordTransMode CoordTransModeFromString(const TCHAR* StringVal);`
- L74 _public prototype_ `static EMode ModeFromString(const TCHAR* StringVal);`
- L75 _public prototype_ `static ENearestMode NearestModeFromString(const TCHAR* StringVal);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersScatterNDCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EScatterNDReductionType`  
`enum class EScatterNDReductionType : uint8`  
_L12-20_
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `Add`
- L16 _public enumerator_ `Mul`
- L17 _public enumerator_ `Max`
- L18 _public enumerator_ `Min`
- L19 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FScatterNDConstants`  
`class FScatterNDConstants`  
_L22-28_
- L26 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L27 _public member_ `static const int32 NUM_GROUP_THREADS{ 768 };`

#### class `UE::NNEHlslShaders::Internal::FScatterNDCS`  
`class FScatterNDCS : public FHlslShaderBase`  
_L30-56_
- inherits: `FHlslShaderBase`
- L32 _private prototype_ `DECLARE_GLOBAL_SHADER(FScatterNDCS);`
- L37 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FScatterNDNumDimensions, FReduceType>;`
- L42 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<int>, InputIndices) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputUpdates) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, DataTensorInfo, [FScatterNDConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FUintVector4, OutputTensorInfo, [FScatterNDConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(uint32, PartialIndexRank) SHADER_PARAMETER(uint32, SliceSize) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`
- L55 _public prototype_ `static EScatterNDReductionType ReductionFromString(const TCHAR* StringVal);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersSliceCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FSliceConstants`  
`class FSliceConstants`  
_L11-17_
- L15 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L16 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::FSliceCS`  
`class FSliceCS : public FHlslShaderBase`  
_L19-38_
- inherits: `FHlslShaderBase`
- L21 _private prototype_ `DECLARE_GLOBAL_SHADER(FSliceCS);`
- L25 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FSliceNumDimensions>;`
- L30 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, TensorInfo, [FSliceConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersSoftmaxCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::ESoftmaxOperatorType`  
`enum class ESoftmaxOperatorType : uint8`  
_L13-18_
- L15 _public enumerator_ `SOFTMAX`
- L16 _public enumerator_ `LOG_SOFTMAX`
- L17 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FSoftmaxConstants`  
`class FSoftmaxConstants`  
_L20-24_
- L23 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::TSoftmaxCS`  
`class TSoftmaxCS : public FHlslShaderBase`  
_L26-48_
- inherits: `FHlslShaderBase`
- L28 _private prototype_ `DECLARE_GLOBAL_SHADER(TSoftmaxCS);`
- L33 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FSoftmaxType,FSingleDimension>;`
- L38 _public prototype_ `SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(uint32, AxisSize) SHADER_PARAMETER(uint32, AfterAxisSize) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, InputSumExp) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNE` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L11 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersSplitCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FSplitConstants`  
`class FSplitConstants`  
_L12-19_
- L16 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L17 _public member_ `static const int32 MAX_NUM_SPLITS{ 8 };`
- L18 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::FSplitCS`  
`class FSplitCS : public FHlslShaderBase`  
_L21-44_
- inherits: `FHlslShaderBase`
- L23 _private prototype_ `DECLARE_GLOBAL_SHADER(FSplitCS);`
- L29 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FSplitRank, FSplitAxis, FSplitNumSplits>;`
- L34 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV_ARRAY(RWBuffer<float>, Output, [FSplitConstants::MAX_NUM_SPLITS]) SHADER_PARAMETER_ARRAY(FUintVector4, InputTensorInfo, [FSplitConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER_ARRAY(FUintVector4, OutputTensorInfo, [FSplitConstants::MAX_NUM_SPLITS * FSplitConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, ThreadCountX) SHADER_PARAMETER(uint32, Num) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& InParameters);`
- L43 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersTransposeCS.h` (Internal)


#### class `UE::NNEHlslShaders::Internal::FTransposeConstants`  
`class FTransposeConstants`  
_L11-17_
- L15 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L16 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::FTransposeCS`  
`class FTransposeCS : public FHlslShaderBase`  
_L19-38_
- inherits: `FHlslShaderBase`
- L21 _private prototype_ `DECLARE_GLOBAL_SHADER(FTransposeCS);`
- L25 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FTransposeNumDimensions>;`
- L30 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, TensorInfo, [FTransposeConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) END_SHADER_PARAMETER_STRUCT() static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersTypeHelper.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::ENNEShaderDataType`  
`enum class ENNEShaderDataType : uint8`  
_L10-23_
- L12 _public enumerator_ `BOOL`
- L13 _public enumerator_ `FLOAT16`
- L14 _public enumerator_ `FLOAT32`
- L15 _public enumerator_ `INT8`
- L16 _public enumerator_ `INT16`
- L17 _public enumerator_ `INT32`
- L18 _public enumerator_ `UINT8`
- L19 _public enumerator_ `UINT16`
- L20 _public enumerator_ `UINT32`
- L22 _public enumerator_ `MAX`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L8 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)
- L25 _prototype_ `const TCHAR *ShaderDataTypeToName(ENNEShaderDataType ShaderType);` (scope `UE::NNEHlslShaders::Internal`)
- L26 _prototype_ `ENNEShaderDataType TensorToShaderDataType(ENNETensorDataType TensorType);` (scope `UE::NNEHlslShaders::Internal`)
- L27 _prototype_ `EPixelFormat TensorDataTypeToPixelFormat(ENNETensorDataType TensorType);` (scope `UE::NNEHlslShaders::Internal`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Internal/NNEHlslShadersUpsampleCS.h` (Internal)


#### enum `UE::NNEHlslShaders::Internal::EUpsampleMode`  
`enum class EUpsampleMode : uint8`  
_L11-17_
- L13 _public enumerator_ `Nearest = 0`
- L14 _public enumerator_ `Bilinear`
- L15 _public enumerator_ `Trilinear`
- L16 _public enumerator_ `MAX`

#### class `UE::NNEHlslShaders::Internal::FUpsampleConstants`  
`class FUpsampleConstants`  
_L19-25_
- L23 _public member_ `static const int32 MAX_NUM_DIMENSIONS{ 8 };`
- L24 _public member_ `static const int32 NUM_GROUP_THREADS{ 256 };`

#### class `UE::NNEHlslShaders::Internal::FUpsampleCS`  
`class FUpsampleCS : public FHlslShaderBase`  
_L27-49_
- inherits: `FHlslShaderBase`
- L29 _private prototype_ `DECLARE_GLOBAL_SHADER(FUpsampleCS);`
- L34 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FUpsampleNumDimensions, FUpsampleMode>;`
- L39 _public prototype_ `SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float>, Input) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float>, Output) SHADER_PARAMETER_ARRAY(FUintVector4, TensorInfo, [FUpsampleConstants::MAX_NUM_DIMENSIONS]) SHADER_PARAMETER(uint32, Num) SHADER_PARAMETER(uint32, ThreadCountX) END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);`
- L48 _public prototype_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& InParameters, FShaderCompilerEnvironment& OutEnvironment);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNEHlslShaders` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNEHlslShaders`)
