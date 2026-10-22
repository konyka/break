# Shaders / Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders

- files: 30; lines: 3912
- record kinds: cpp_binding=29, define=190, entry=34, function=64, groupshared=19, include=44, macro_call=1, member=6, parameter=189, resource=90, static_const=1, struct=2

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersBatchNormalization.usf` (Private)

- lines: 42; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 1)

- L5 `#define WORK_TYPE float`

#### Entry points (1)

- L27-41 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void BatchNormalization(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TBatchNormalizationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersBatchNormalizationCS.cpp:15)

#### Global resources (textures / buffers / samplers) (6)

- L7 _resource_ `Buffer<WORK_TYPE> X;`
- L8 _resource_ `Buffer<WORK_TYPE> Scales;`
- L9 _resource_ `Buffer<WORK_TYPE> Bias;`
- L10 _resource_ `Buffer<WORK_TYPE> Mean;`
- L11 _resource_ `Buffer<WORK_TYPE> Var;`
- L12 _resource_ `RWBuffer<WORK_TYPE> Output;`

#### Global parameters (uniforms) (5)

- L13 _parameter_ `float Epsilon;`
- L14 _parameter_ `uint SpatialVolume;`
- L15 _parameter_ `uint DimC;`
- L16 _parameter_ `uint ThreadCountX;`
- L17 _parameter_ `uint Num;`

#### Functions (1)

- L19-24 _function_ `WORK_TYPE ApplyBatchNormalization(WORK_TYPE x, WORK_TYPE input_mean, WORK_TYPE input_var, WORK_TYPE scale, WORK_TYPE bias)`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersBroadcastHelper.ush` (Private)

- lines: 9; parse: all-branches
- L3 #pragma `once`

#### Functions (1)

- L5-9 _function_ `void DivMod(uint op1, uint op2, out uint q, out uint r)`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersCast.usf` (Private)

- lines: 19; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L10-18 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Cast(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TCastCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersCastCS.cpp:47)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Buffer<INPUT_TYPE> Input;`
- L6 _resource_ `RWBuffer<OUTPUT_TYPE> Output;`

#### Global parameters (uniforms) (2)

- L7 _parameter_ `uint Num;`
- L8 _parameter_ `uint ThreadCountX;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersConv.usf` (Private)

- lines: 304; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 7)

- L5 `#define WORK_TYPE float`
- L6 `#define BUFFER_TYPE float`
- L7 `#define BUFFER_TO_WORK_TYPE(x) x`
- L8 `#define WORK_TO_BUFFER_TYPE(x) x`
- L12 `#define NUM_GROUP_THREADS 128` _[#if GROUP_SIZE == 0]_
- L14 `#define NUM_GROUP_THREADS 256` _[#if !(GROUP_SIZE == 0) && GROUP_SIZE == 1]_
- L16 `#define NUM_GROUP_THREADS 512` _[#if !(GROUP_SIZE == 0) && !(GROUP_SIZE == 1) && GROUP_SIZE == 2]_

#### Entry points (1)

- L76-302 _entry_ `[numthreads(NUM_GROUP_THREADS, 1, 1)] void Conv(in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupID : SV_GroupID, in const uint3 GroupThreadID : SV_GroupThreadID)` — stage: **compute** — C++: `FConvCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersConvCS.cpp:360) _[#if ALGORITHM < 1]_

#### Global resources (textures / buffers / samplers) (4)

- L19 _resource_ `Buffer<BUFFER_TYPE> X;` — N x C x XD0 x ... x XDi
- L20 _resource_ `Buffer<BUFFER_TYPE> W;` — M x C/GROUPS x WD0 x ... x WDi OR WD0 x WD1 x C X M if WEIGHTS_TRANSPOSED (only supported for 4D)
- L21 _resource_ `RWBuffer<BUFFER_TYPE> Y;` — N x M x YD0 x ... x YDi
- L22 _resource_ `Buffer<BUFFER_TYPE> B;` — B0, ..., BM

#### Global parameters (uniforms) (18)

- L27 _parameter_ `int4 Dilation_Stride_XBlockStartOffset_DilationXBlockStride[MAX_NUM_DIMENSIONS];` — x: Dilation0, ...., Dilationi y: Strides0, ...., Stridesi z: Pad0Begin, ...., PadiBegin
- L32 _parameter_ `int4 GroupStride_GroupShape_GroupThreadStride_StrideXBlockStride[MAX_NUM_DIMENSIONS];` — x: Element j contains PROD(GDj+1,..,GDi) with the last element containing 1, with GDi being the number of thread groups contained by a dimension i y: Number of threads in each dimension of a group z: Element j contains PROD(GTDj+1,..,GTDi) with the last element containing 1, with GTDi being the number of threads contained by a dimension i inside a group
- L38 _parameter_ `int4 YDimension_YMemoryStride_XDimension_XMemoryStride[MAX_NUM_DIMENSIONS];` — x: YD0, ..., YDi y: Element j contains PROD(YDj+1,..,YDi) with the last element containing 1 z: XD0, ..., XDi w: Element j contains PROD(XDj+1,..,XDi) with the last element containing 1
- L43 _parameter_ `int4 XBlockStartStride_XBlockStride_WDimension_WDimensionDilationXBlockStride[MAX_NUM_DIMENSIONS];` — x: Number of elements in each dimension of a X block y: The strides of the X block to be loaded z: WD0, ..., WDi
- L48 _parameter_ `float4 OneDiv_GroupStride_GroupThreadStride_XBlockStride[MAX_NUM_DIMENSIONS];` — x: 1/GroupStride y: 1/GroupThreadStride z: 1/XBlockStride
- L50 _parameter_ `int NumWFeatures;` — Number of features (aka output channels)
- L51 _parameter_ `int NumWChannels;` — Number of input channels
- L53 _parameter_ `int YBatchStride;`
- L54 _parameter_ `int YOutputKernelStride;`
- L56 _parameter_ `int XBatchStride;` — The number of elements in each bacth of X
- L57 _parameter_ `int XChannelStride;` — The number of elements in each channel of X
- L59 _parameter_ `int XBlockSize;` — The total number of elements in each block to be loaded
- L61 _parameter_ `int NumChannelBatches;` — The number of iteration needed to cover all channels that needs to be processed. Equals to ceil(NumWChannels/NumChannelsPerBatch)
- L62 _parameter_ `int NumChannelsPerBatch;` — The number of complete kernel channels that can be loaded in one batch
- L64 _parameter_ `int WOutputKernelStride;` — The total number of W elements per output kernel and thus PROD(C/GROUPS, WD0, .., WDi)
- L65 _parameter_ `int WChannelBatchSize;` — The total number of W elements inside a channel batch and thus the number of channels per batch times PROD(WD0, .., WDi)
- L66 _parameter_ `int WChannelSize;` — Number of elements in a single channel of W and thus PROD(WDi)
- L68 _parameter_ `float GroupsDivM;` — The number of groups divided by the number of output kernels used to compute the start channel offset

#### groupshared (2)

- L70 _groupshared_ `groupshared WORK_TYPE SharedMemoryX[NUM_GROUP_THREADS<<NUM_READS_PER_THREAD_POW2];`
- L71 _groupshared_ `groupshared WORK_TYPE SharedMemoryW[NUM_GROUP_THREADS];`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersConvMatmul.usf` (Private)

- lines: 236; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 11)

- L5 `#define WORK_TYPE float`
- L6 `#define BUFFER_TYPE float`
- L7 `#define BUFFER_TO_WORK_TYPE(x) x`
- L8 `#define WORK_TO_BUFFER_TYPE(x) x`
- L10 `#define LDS_IC 16`
- L11 `#define TG_OC 32`
- L12 `#define TG_OP 32`
- L15 `#define LDS_PADX 1`
- L16 `#define LDS_PADY 2`
- L17 `#define LDS_X_PADDEDSIZE ((4 + LDS_PADX) * 8 + LDS_PADY)`
- L168 `#define INNERLOOPUNROLLCOUNT 4`

#### Entry points (1)

- L59-235 _entry_ `[numthreads(8, 8, 1)] void ConvMatmul( in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupID : SV_GroupID, in const uint3 GroupThreadID : SV_GroupThreadID, in const uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FConvMatmulCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersConvMatmulCS.cpp:25)

#### Global resources (textures / buffers / samplers) (4)

- L21 _resource_ `Buffer<BUFFER_TYPE> Input;` — Ni x Ci x Hi x Wi
- L22 _resource_ `Buffer<BUFFER_TYPE> Weight;` — Cw x Ci x Hw x Ww OR Hw x Ww x Ci x Cw if WEIGHTS_TRANSPOSED
- L23 _resource_ `Buffer<BUFFER_TYPE> Bias;` — Cw
- L24 _resource_ `RWBuffer<BUFFER_TYPE> Output;` — Ni x Cw x Ho x Wo

#### Global parameters (uniforms) (12)

- L26 _parameter_ `int Ci;`
- L27 _parameter_ `int Hi;`
- L28 _parameter_ `int Wi;`
- L29 _parameter_ `int Ho;`
- L30 _parameter_ `int Wo;`
- L31 _parameter_ `int Cw;`
- L32 _parameter_ `int Hw;`
- L33 _parameter_ `int Ww;`
- L34 _parameter_ `int PadLeft;`
- L35 _parameter_ `int PadTop;`
- L36 _parameter_ `int StrideH;`
- L37 _parameter_ `int StrideW;`

#### groupshared (1)

- L19 _groupshared_ `groupshared WORK_TYPE LDSBuffer[32 * LDS_X_PADDEDSIZE];` — max (16*32+32,32*42) = 1344 WORK_TYPE

#### Functions (4)

- L39-42 _function_ `WORK_TYPE ReadLDSWeights(int inputChannel, int outputChannel)`
- L44-47 _function_ `void WriteLDSWeights(int inputChannel, int outputChannel, WORK_TYPE value)`
- L49-52 _function_ `WORK_TYPE ReadLDSInputs(int inputChannel, int outputPixel)`
- L54-57 _function_ `void WriteLDSInputs(int inputChannel, int outputPixel, WORK_TYPE value)`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersConvTranspose.usf` (Private)

- lines: 335; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 19)

- L7 `#define WORK_TYPE float` _[#if DATA_TYPE == 0]_
- L8 `#define BUFFER_TYPE float` _[#if DATA_TYPE == 0]_
- L9 `#define BUFFER_TO_WORK_TYPE(x) x` _[#if DATA_TYPE == 0]_
- L10 `#define WORK_TO_BUFFER_TYPE(x) x` _[#if DATA_TYPE == 0]_
- L14 `#define WORK_TYPE int` _[#if !(DATA_TYPE == 0) && DATA_TYPE == 1]_
- L15 `#define BUFFER_TYPE int` _[#if !(DATA_TYPE == 0) && DATA_TYPE == 1]_
- L16 `#define BUFFER_TO_WORK_TYPE(x) x` _[#if !(DATA_TYPE == 0) && DATA_TYPE == 1]_
- L17 `#define WORK_TO_BUFFER_TYPE(x) x` _[#if !(DATA_TYPE == 0) && DATA_TYPE == 1]_
- L21 `#define WORK_TYPE uint` _[#if !(DATA_TYPE == 0) && !(DATA_TYPE == 1) && DATA_TYPE == 2]_
- L22 `#define BUFFER_TYPE uint` _[#if !(DATA_TYPE == 0) && !(DATA_TYPE == 1) && DATA_TYPE == 2]_
- L23 `#define BUFFER_TO_WORK_TYPE(x) x` _[#if !(DATA_TYPE == 0) && !(DATA_TYPE == 1) && DATA_TYPE == 2]_
- L24 `#define WORK_TO_BUFFER_TYPE(x) x` _[#if !(DATA_TYPE == 0) && !(DATA_TYPE == 1) && DATA_TYPE == 2]_
- L28 `#define WORK_TYPE float` _[#if !(DATA_TYPE == 0) && !(DATA_TYPE == 1) && !(DATA_TYPE == 2) && DATA_TYPE == 3]_
- L29 `#define BUFFER_TYPE min16uint` _[#if !(DATA_TYPE == 0) && !(DATA_TYPE == 1) && !(DATA_TYPE == 2) && DATA_TYPE == 3]_
- L30 `#define BUFFER_TO_WORK_TYPE(x) f16tof32(x)` _[#if !(DATA_TYPE == 0) && !(DATA_TYPE == 1) && !(DATA_TYPE == 2) && DATA_TYPE == 3]_
- L31 `#define WORK_TO_BUFFER_TYPE(x) f32tof16(x)` _[#if !(DATA_TYPE == 0) && !(DATA_TYPE == 1) && !(DATA_TYPE == 2) && DATA_TYPE == 3]_
- L37 `#define NUM_GROUP_THREADS 128` _[#if GROUP_SIZE == 0]_
- L39 `#define NUM_GROUP_THREADS 256` _[#if !(GROUP_SIZE == 0) && GROUP_SIZE == 1]_
- L41 `#define NUM_GROUP_THREADS 512` _[#if !(GROUP_SIZE == 0) && !(GROUP_SIZE == 1) && GROUP_SIZE == 2]_

#### Entry points (1)

- L102-332 _entry_ `[numthreads(NUM_GROUP_THREADS, 1, 1)] void ConvTranspose(in const int3 DispatchThreadID : SV_DispatchThreadID, in const int3 GroupID : SV_GroupID, in const int3 GroupThreadID : SV_GroupThreadID)` — stage: **compute** — C++: `FConvTransposeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersConvTransposeCS.cpp:293) _[#if ALGORITHM < 1]_

#### Global resources (textures / buffers / samplers) (4)

- L44 _resource_ `Buffer<BUFFER_TYPE> X;` — N x C x XD0 x ... x XDi
- L45 _resource_ `Buffer<BUFFER_TYPE> W;` — M x C/GROUPS x WD0 x ... x WDi
- L46 _resource_ `RWBuffer<BUFFER_TYPE> Y;` — N x M x YD0 x ... x YDi
- L47 _resource_ `Buffer<BUFFER_TYPE> B;` — B0, ..., BM

#### Global parameters (uniforms) (19)

- L52 _parameter_ `int4 Dilation_Stride_XBlockStartOffset_DilationXBlockStride[NUM_STACK_DIMENSIONS];` — x: Dilation0, ...., Dilationi y: Strides0, ...., Stridesi z: Pad0Begin, ...., PadiBegin
- L57 _parameter_ `int4 GroupStride_GroupShape_GroupThreadStride_StrideXBlockStride[NUM_STACK_DIMENSIONS];` — x: Element j contains PROD(GDj+1,..,GDi) with the last element containing 1, with GDi being the number of thread groups contained by a dimension i y: Number of threads in each dimension of a group z: Element j contains PROD(GTDj+1,..,GTDi) with the last element containing 1, with GTDi being the number of threads contained by a dimension i inside a group
- L63 _parameter_ `int4 YDimension_YMemoryStride_XDimension_XMemoryStride[NUM_STACK_DIMENSIONS];` — x: YD0, ..., YDi y: Element j contains PROD(YDj+1,..,YDi) with the last element containing 1 z: XD0, ..., XDi w: Element j contains PROD(XDj+1,..,XDi) with the last element containing 1
- L68 _parameter_ `int4 XBlockStartStride_XBlockStride_WDimension_WDimensionDilationXBlockStride[NUM_STACK_DIMENSIONS];` — x: Number of elements in each dimension of a X block y: The strides of the X block to be loaded z: WD0, ..., WDi
- L73 _parameter_ `float4 OneDiv_GroupStride_GroupThreadStride_OneDivStride[NUM_STACK_DIMENSIONS];` — x: 1/GroupStride y: 1/GroupThreadStride z: 1/XBlockStride
- L75 _parameter_ `int NumWChannels;` — WShape[0]
- L76 _parameter_ `int NumOutChannelsDivGroup;` — WShape[1]
- L78 _parameter_ `int YBatchStride;`
- L79 _parameter_ `int YOutputKernelStride;`
- L81 _parameter_ `int XBatchStride;` — The number of elements in each bacth of X
- L82 _parameter_ `int XChannelStride;` — The number of elements in each channel of X
- L84 _parameter_ `int XBlockSize;` — The total number of elements in each block to be loaded
- L86 _parameter_ `int NumChannelBatches;` — The number of iteration needed to cover all channels that needs to be processed. Equals to ceil(NumWChannels/NumChannelsPerBatch)
- L87 _parameter_ `int NumChannelsPerBatch;` — The number of complete kernel channels that can be loaded in one batch
- L89 _parameter_ `int WOutputKernelStride;` — The total number of W elements per output kernel and thus PROD(C/GROUPS, WD0, .., WDi)
- L90 _parameter_ `int WChannelBatchSize;` — The total number of W elements inside a channel batch and thus the number of channels per batch times PROD(WD0, .., WDi)
- L91 _parameter_ `int WChannelSize;` — Number of elements in a single channel of W and thus PROD(WDi)
- L93 _parameter_ `float GroupsDivM;` — The number of groups divided by the number of output kernels used to compute the start channel offset
- L94 _parameter_ `float OneDivGroup;`

#### groupshared (2)

- L96 _groupshared_ `groupshared WORK_TYPE SharedMemoryX[NUM_GROUP_THREADS<<NUM_READS_PER_THREAD_POW2];`
- L97 _groupshared_ `groupshared WORK_TYPE SharedMemoryW[NUM_GROUP_THREADS];`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersConvWinogradInput.usf` (Private)

- lines: 96; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Entry points (1)

- L22-95 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void ConvWinogradInput( in const uint3 GroupID : SV_GroupID, in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupThreadID : SV_GroupThreadID)` — stage: **compute** — C++: `FConvWinogradInputCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersConvWinogradInputCS.cpp:13)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Buffer<float> Input;` — Ni x C x H x W
- L7 _resource_ `RWBuffer<float> Output;` — Ni x 36 x C x Ceil(H/4)*Ceil(W/4)

#### Global parameters (uniforms) (10)

- L9 _parameter_ `int C;`
- L10 _parameter_ `int H;`
- L11 _parameter_ `int W;`
- L12 _parameter_ `int WBlockCount;`
- L14 _parameter_ `int CInputStride;`
- L15 _parameter_ `int HInputStride;`
- L17 _parameter_ `int NiOutputStride;`
- L18 _parameter_ `int MatrixOutputStride;`
- L19 _parameter_ `int COutputStride;`
- L20 _parameter_ `int HOutputStride;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersConvWinogradMMM.usf` (Private)

- lines: 148; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 11)

- L5 `#define K_STEP 16`
- L6 `#define BLOCK_ELEM_COUNT_M 64`
- L7 `#define VECTOR_SIZE 2`
- L9 `#define BLOCK_VECTOR_ELEM_COUNT_M (BLOCK_ELEM_COUNT_M / VECTOR_SIZE)`
- L10 `#define BLOCK_VECTOR_ELEM_COUNT_N (BLOCK_ELEM_COUNT_N / VECTOR_SIZE)`
- L12 `#define BLOCK_COUNT_M (BLOCK_ELEM_COUNT_M / 4)`
- L13 `#define BLOCK_COUNT_N (BLOCK_ELEM_COUNT_N / 4)`
- L14 `#define BLOCK_COUNT (BLOCK_COUNT_M * BLOCK_COUNT_N)`
- L16 `#define THREADGROUP_SIZE_X BLOCK_VECTOR_ELEM_COUNT_M`
- L17 `#define THREADGROUP_SIZE_Y (BLOCK_COUNT / THREADGROUP_SIZE_X)`
- L18 `#define THREADGROUP_SIZE (THREADGROUP_SIZE_X * THREADGROUP_SIZE_Y)`

#### Entry points (1)

- L45-147 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void ConvWinogradMMM( in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupID : SV_GroupID, in const uint3 GroupThreadID : SV_GroupThreadID, in const uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FConvWinogradMMMCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersConvWinogradMMMCS.cpp:89)

#### Global resources (textures / buffers / samplers) (3)

- L25 _resource_ `Buffer<WORK_TYPE_VECTOR> Input;` — Ni x 36 x K x M
- L26 _resource_ `Buffer<WORK_TYPE_VECTOR> Weight;` — 36 x K x N
- L27 _resource_ `RWBuffer<WORK_TYPE_VECTOR> Output;` — Ni x 36 x N x M

#### Global parameters (uniforms) (9)

- L32 _parameter_ `int M;`
- L33 _parameter_ `int N;`
- L34 _parameter_ `int K;`
- L36 _parameter_ `int MatrixInputStride;`
- L37 _parameter_ `int KInputStride;`
- L39 _parameter_ `int MatrixWeightStride;`
- L40 _parameter_ `int KWeightStride;`
- L42 _parameter_ `int MatrixOutputStride;`
- L43 _parameter_ `int NOutputStride;`

#### groupshared (2)

- L29 _groupshared_ `groupshared WORK_TYPE_VECTOR LDS_InputOutput[max(K_STEP, BLOCK_ELEM_COUNT_N)][BLOCK_VECTOR_ELEM_COUNT_M];`
- L30 _groupshared_ `groupshared WORK_TYPE_VECTOR LDS_Weight[K_STEP][BLOCK_VECTOR_ELEM_COUNT_N];`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersConvWinogradOutput.usf` (Private)

- lines: 96; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Entry points (1)

- L23-95 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void ConvWinogradOutput( in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupID : SV_GroupID, in const uint3 GroupThreadID : SV_GroupThreadID)` — stage: **compute** — C++: `FConvWinogradOutputCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersConvWinogradOutputCS.cpp:33)

#### Global resources (textures / buffers / samplers) (3)

- L6 _resource_ `Buffer<WORK_TYPE> Input;` — Ni x 36 x CExtended x Ceil(H/4)*Ceil(W/4)
- L7 _resource_ `Buffer<WORK_TYPE> Bias;` — C
- L8 _resource_ `RWBuffer<WORK_TYPE> Output;` — Ni x C x H x W

#### Global parameters (uniforms) (10)

- L10 _parameter_ `int C;`
- L11 _parameter_ `int H;`
- L12 _parameter_ `int W;`
- L13 _parameter_ `int WBlockCount;`
- L15 _parameter_ `int NiInputStride;`
- L16 _parameter_ `int MatrixInputStride;`
- L17 _parameter_ `int CInputStride;`
- L18 _parameter_ `int HInputStride;`
- L20 _parameter_ `int COutputStride;`
- L21 _parameter_ `int HOutputStride;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersConvWinogradWeights.usf` (Private)

- lines: 79; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 1)

- L5 `#define KERNEL_STRIDE 9`

#### Entry points (1)

- L19-78 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void ConvWinogradWeights( in const uint3 GroupID : SV_GroupID, in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FConvWinogradWeightsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersConvWinogradWeightsCS.cpp:13)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `Buffer<float> Input;` — Cw x Ci x 3 x 3
- L8 _resource_ `RWBuffer<float> Output;` — 36 x Ci x Cw

#### Global parameters (uniforms) (5)

- L10 _parameter_ `int Ci;`
- L11 _parameter_ `int Cw;`
- L13 _parameter_ `int CwInputStride;`
- L15 _parameter_ `int MatrixOutputStride;`
- L16 _parameter_ `int CiOutputStride;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersCumSum.usf` (Private)

- lines: 322; parse: all-branches
- includes: L6 `/Engine/Public/Platform.ush`

#### Macros (#define, 12)

- L9 `#define WORK_TYPE float`
- L10 `#define BUFFER_TYPE float`
- L11 `#define READ(x) x`
- L12 `#define WRITE(x) x`
- L18 `#define STATUS_INVALID 0`
- L19 `#define STATUS_AGGREGATE_AVAILABLE 1`
- L20 `#define STATUS_PREFIX_AVAILABLE 2`
- L83 `#define STRIDE_IDX 0` _[#if !(defined(INIT_SHADER))]_
- L85 `#define MIN_WAVE_LANES 4U` _[#if !(defined(INIT_SHADER))]_
- L86 `#define PARTITION_SIZE (THREADGROUP_SIZE * VALUES_PER_THREAD)` _[#if !(defined(INIT_SHADER))]_
- L87 `#define NUM_WAVEAGGREGATES (THREADGROUP_SIZE / WaveGetLaneCount())` _[#if !(defined(INIT_SHADER))]_
- L88 `#define LAST_WAVEAGGREGATE_ID (NUM_WAVEAGGREGATES - 1)` _[#if !(defined(INIT_SHADER))]_

#### Entry points (2)

- L48-76 _entry_ `[numthreads(INIT_THREADGROUP_SIZE, 1, 1)] void InitCumSum(uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TInitCumSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersCumSumCS.cpp:27) _[#if defined(INIT_SHADER)]_
- L284-320 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void CumSum(in const uint3 GroupID : SV_GroupID, in const uint3 GroupThreadIDVec : SV_GroupThreadID)` — stage: **compute** — C++: `TCumSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersCumSumCS.cpp:28) _[#if !(defined(INIT_SHADER))]_

#### Structs / classes (1)

- L34-40 _struct_ **`FPartitionDescriptor`** `struct FPartitionDescriptor` — Elements to scan are partitioned. Each thread group computes the prefix scan of a partition. Results to be propagated to the next groups are written in the partition descriptor in device memory. It needs to be 'globallycoherent' so that memory fences flush updates across groups. There are as many descriptors as thread groups.
  - L36 _member_ `int StatusFlag;`
  - L37 _member_ `WORK_TYPE Aggregate;`
  - L38 _member_ `WORK_TYPE InclusivePrefix;`
  - L39 _member_ `int PadToQWord;`

#### Global resources (textures / buffers / samplers) (4)

- L27 _resource_ `globallycoherent RWStructuredBuffer<uint> GlobalPartitionIndex;` — For each scan there is a different global partition index. Each group in the same scan lock-step increments the global partition index. The value before the increment is the partition index assigned to the thread group that did the increment.
- L41 _resource_ `globallycoherent RWStructuredBuffer<FPartitionDescriptor> PartitionDescriptor;`
- L80 _resource_ `Buffer<BUFFER_TYPE> Input;` _[#if !(defined(INIT_SHADER))]_
- L81 _resource_ `RWBuffer<BUFFER_TYPE> Output;` _[#if !(defined(INIT_SHADER))]_

#### Global parameters (uniforms) (7)

- L14 _parameter_ `uint NumThreadGroupsPerScan;` — Each group's x-axis refers to a single prefix scan (cumulative sum)
- L15 _parameter_ `uint NumThreadGroupsY;` — Each group's y-index refers to pre-axis dimensions
- L16 _parameter_ `uint NumThreadGroupsZ;` — Each group's z-index refers to post-axis dimensions
- L46 _parameter_ `uint NumInitThreadGroups;` _[#if defined(INIT_SHADER)]_
- L90 _parameter_ `uint NumScanValues;` _[#if !(defined(INIT_SHADER))]_
- L91 _parameter_ `uint Axis;` _[#if !(defined(INIT_SHADER))]_
- L92 _parameter_ `uint AxisStride;` _[#if !(defined(INIT_SHADER))]_

#### groupshared (4)

- L96 _groupshared_ `groupshared uint GroupPartitionIndex;` _[#if !(defined(INIT_SHADER))]_
- L97 _groupshared_ `groupshared WORK_TYPE GroupExclusivePrefix;` _[#if !(defined(INIT_SHADER))]_
- L98 _groupshared_ `groupshared WORK_TYPE LocalPrefix[PARTITION_SIZE];` — Wave-local prefixes for each element of the partition (before adding the group's exclusive prefix) _[#if !(defined(INIT_SHADER))]_
- L99 _groupshared_ `groupshared WORK_TYPE WaveAggregate[THREADGROUP_SIZE / MIN_WAVE_LANES];` — Wave-wide aggregates (also group-local) to speed up reduction phase _[#if !(defined(INIT_SHADER))]_

#### Functions (14)

- L102-105 _function_ `inline WORK_TYPE GetScanInput(uint IdxWithinAxis, uint ScanStartGlobalIdx)` _[#if !(defined(INIT_SHADER))]_
- L107-110 _function_ `inline void SetScanOutput(uint IdxWithinAxis, WORK_TYPE Value, uint ScanStartGlobalIdx)` _[#if !(defined(INIT_SHADER))]_
- L112-115 _function_ `inline uint GetWaveIndex(uint GroupThreadID)` _[#if !(defined(INIT_SHADER))]_
- L117-120 _function_ `inline uint PartitionOffset(uint PartitionIndex)` _[#if !(defined(INIT_SHADER))]_
- L122-125 _function_ `inline uint WavePartitionOffset(uint GroupThreadID)` _[#if !(defined(INIT_SHADER))]_
- L132-154 _function_ `inline void WaveScanReduce(uint GroupThreadID, uint PartitionIndex, uint ScanStartGlobalIdx, bool bPartial)` — Performs a wave-local prefix scan (and reduction) of VALUES_PER_THREAD elements per thread, for each wave. Scan results are stored in groupshared memory array LocalPrefix. The aggregated value for each wave is stored in groupshared memory array WaveAggregate. _[#if !(defined(INIT_SHADER))]_
- L159-181 _function_ `inline void ScanWaveAggregate(uint GroupThreadID)` — Performs a group-local prefix scan of the wave aggregates in groupshared memory. _[#if !(defined(INIT_SHADER))]_
- L184-190 _function_ `inline void ReservePartitionIndex(uint GroupThreadID, uint ScanID)` _[#if !(defined(INIT_SHADER))]_
- L192-197 _function_ `inline void SetPartitionInclusivePrefix(uint PDIdx, WORK_TYPE Value)` _[#if !(defined(INIT_SHADER))]_
- L199-204 _function_ `inline void SetPartitionAggregate(uint PDIdx, WORK_TYPE Value)` _[#if !(defined(INIT_SHADER))]_
- L206-209 _function_ `inline uint GetPDIdx(uint PartitionIndex, uint ScanID)` _[#if !(defined(INIT_SHADER))]_
- L213-228 _function_ `inline void BroadcastGroupAggregate(uint GroupThreadID, uint PartitionIndex, uint ScanID)` — Updates the current group's partition descriptor in device memory once the partition aggregate has been computed. _[#if !(defined(INIT_SHADER))]_
- L233-267 _function_ `inline void DecoupledLookback(uint PartitionIndex, uint ScanID)` — Computes the partition exclusive prefix by recursively summing up prefixes/aggregates of previous partitions in backward order. Also computes and sets (broadcasts) the inclusive prefix of the partition once the exclusive prefix is available. _[#if !(defined(INIT_SHADER))]_
- L271-281 _function_ `void SeededWaveScan(uint GroupThreadID, uint PartitionIndex, WORK_TYPE ExclusivePrefix, uint ScanStartGlobalIdx, bool bPartial)` — Computes the final prefix scan by adding wave-local prefixes to wave-wise exclusive prefixes. _[#if !(defined(INIT_SHADER))]_

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersElementWiseBinary.usf` (Private)

- lines: 62; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Entry points (1)

- L38-61 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void ElementWiseBinary(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TElementWiseBinaryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersElementWiseBinaryCS.cpp:58)

#### Global resources (textures / buffers / samplers) (3)

- L6 _resource_ `Buffer<float> LHSInput;`
- L7 _resource_ `Buffer<float> RHSInput;`
- L8 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (3)

- L9 _parameter_ `uint4 TensorInfo[NUM_DIMENSIONS];`
- L10 _parameter_ `uint Num;`
- L11 _parameter_ `uint ThreadCountX;`

#### Functions (2)

- L14-17 _function_ `float prelu(float x, float slope)` — See https://github.com/onnx/onnx/blob/main/docs/Operators.md#prelu
- L19-36 _function_ `float safe_pow(float base, float xp)`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersElementWiseUnary.usf` (Private)

- lines: 154; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L145-153 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void ElementWiseUnary(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TElementWiseUnaryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersElementWiseUnaryCS.cpp:97)

#### Global resources (textures / buffers / samplers) (4)

- L5 _resource_ `Buffer<float> Input;`
- L6 _resource_ `RWBuffer<float> Output;`
- L10 _resource_ `Buffer<float> AlphaTensor;`
- L12 _resource_ `Buffer<float> BetaTensor;`

#### Global parameters (uniforms) (5)

- L7 _parameter_ `uint Num;`
- L8 _parameter_ `uint ThreadCountX;`
- L9 _parameter_ `float Alpha;`
- L11 _parameter_ `float Beta;`
- L13 _parameter_ `float Gamma;`

#### Functions (17)

- L15-22 _function_ `float GetAlpha()`
- L24-31 _function_ `float GetBeta()`
- L34-37 _function_ `float relu(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#Relu
- L40-45 _function_ `float selu(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#Selu
- L48-51 _function_ `float sigmoid(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#sigmoid
- L54-57 _function_ `float softplus(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#softplus
- L60-63 _function_ `float softsign(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#softsign
- L66-72 _function_ `float acosh(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#acosh
- L75-79 _function_ `float asinh(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#asinh
- L82-86 _function_ `float atanh(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#atanh
- L89-94 _function_ `float elu(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#elu
- L97-110 _function_ `float erf(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#erf
- L112-115 _function_ `float hardSigmoid(float x, float alpha, float beta)`
- L118-121 _function_ `float hardSigmoid(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#hardSigmoid
- L124-127 _function_ `float hardSwish(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#hardSwish
- L130-133 _function_ `float leakyRelu(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#leakyRelu
- L137-142 _function_ `float clipOp(float x)` — see https://github.com/onnx/onnx/blob/main/docs/Operators.md#clip

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersElementWiseVariadic.usf` (Private)

- lines: 66; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 1)

- L6 `#define BUFFER_TYPE float`

#### Entry points (1)

- L19-65 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void ElementWiseVariadic(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TElementWiseVariadicCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersElementWiseVariadicCS.cpp:47)

#### Global resources (textures / buffers / samplers) (5)

- L8 _resource_ `Buffer<BUFFER_TYPE> Input0;`
- L9 _resource_ `Buffer<BUFFER_TYPE> Input1;`
- L10 _resource_ `Buffer<BUFFER_TYPE> Input2;`
- L11 _resource_ `Buffer<BUFFER_TYPE> Input3;`
- L12 _resource_ `RWBuffer<BUFFER_TYPE> Output;`

#### Global parameters (uniforms) (5)

- L13 _parameter_ `uint4 InputTensorInfo[NUM_DIMENSIONS];`
- L14 _parameter_ `uint4 OutputTensorInfo[NUM_DIMENSIONS];`
- L15 _parameter_ `uint Num;`
- L16 _parameter_ `uint ThreadCountX;`
- L17 _parameter_ `float Scale;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersGather.usf` (Private)

- lines: 82; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersTypeHelper.ush`

#### Entry points (1)

- L29-82 _entry_ `[numthreads(NUM_GROUP_THREADS, 1, 1)] void Gather(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TGatherCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersGatherCS.cpp:84)

#### Global resources (textures / buffers / samplers) (3)

- L14 _resource_ `Buffer<float> Data;`
- L15 _resource_ `Buffer<int> Indices;`
- L16 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (6)

- L6 _parameter_ `int Axis;`
- L7 _parameter_ `int OutputSize;`
- L8 _parameter_ `int NumDataDimensions;`
- L9 _parameter_ `int NumIndicesDimensions;`
- L10 _parameter_ `int4 DataStride_IndicesStride_OutputStride_DataSizes[MAX_NUM_DIMENSIONS];`
- L11 _parameter_ `float4 OneDivDataStride_OneDivIndicesStride_OneDivOutputStride[MAX_NUM_DIMENSIONS];`

#### Functions (2)

- L18-21 _function_ `uint NormalizeIdx(int Idx, uint DimSize)`
- L24-27 _function_ `int CastInt64ToInt32(uint LSW, int MSW)` — int64_t is only available from SM 6.0, therefore here we need to manually cast to int32.

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersGatherElements.usf` (Private)

- lines: 52; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersTypeHelper.ush`

#### Entry points (1)

- L17-51 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void GatherElements(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FGatherElementsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShaderGatherElementsCS.cpp:17)

#### Global resources (textures / buffers / samplers) (3)

- L6 _resource_ `Buffer<float> Input;`
- L7 _resource_ `Buffer<int> Indices;`
- L8 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (6)

- L10 _parameter_ `int Axis;`
- L11 _parameter_ `int AxisSize;`
- L12 _parameter_ `int OutputSize;`
- L13 _parameter_ `uint ThreadCountX;`
- L14 _parameter_ `float4 OneDivOutputStrides[NUM_DIMENSIONS];`
- L15 _parameter_ `int4 Input_OutputStrides[NUM_DIMENSIONS];`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersGemm.usf` (Private)

- lines: 448; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 31)

- L5 `#define WORK_TYPE float`
- L6 `#define BUFFER_TYPE float`
- L7 `#define READ(x) x`
- L8 `#define WRITE(x) x`
- L153 `#define GROUP_SIZE 8` _[#if !(ALGORITHM < 4) && ALGORITHM < 7 && ALGORITHM == 4]_
- L155 `#define GROUP_SIZE 16` _[#if !(ALGORITHM < 4) && ALGORITHM < 7 && !(ALGORITHM == 4) && ALGORITHM == 5]_
- L157 `#define GROUP_SIZE 32` _[#if !(ALGORITHM < 4) && ALGORITHM < 7 && !(ALGORITHM == 4) && !(ALGORITHM == 5) && ALGORITHM == 6]_
- L261 `#define GROUP_SIZE_X 16` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && ALGORITHM == 7]_
- L262 `#define GROUP_SIZE_Y 1` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && ALGORITHM == 7]_
- L263 `#define LOAD_PER_THREAD 16` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && ALGORITHM == 7]_
- L265 `#define GROUP_SIZE_X 16` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && ALGORITHM == 8]_
- L266 `#define GROUP_SIZE_Y 2` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && ALGORITHM == 8]_
- L267 `#define LOAD_PER_THREAD 8` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && ALGORITHM == 8]_
- L269 `#define GROUP_SIZE_X 32` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && ALGORITHM == 9]_
- L270 `#define GROUP_SIZE_Y 1` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && ALGORITHM == 9]_
- L271 `#define LOAD_PER_THREAD 32` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && ALGORITHM == 9]_
- L273 `#define GROUP_SIZE_X 32` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && ALGORITHM == 10]_
- L274 `#define GROUP_SIZE_Y 2` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && ALGORITHM == 10]_
- L275 `#define LOAD_PER_THREAD 16` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && ALGORITHM == 10]_
- L277 `#define GROUP_SIZE_X 32` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && ALGORITHM == 11]_
- L278 `#define GROUP_SIZE_Y 4` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && ALGORITHM == 11]_
- L279 `#define LOAD_PER_THREAD 8` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && ALGORITHM == 11]_
- L281 `#define GROUP_SIZE_X 64` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && ALGORITHM == 12]_
- L282 `#define GROUP_SIZE_Y 2` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && ALGORITHM == 12]_
- L283 `#define LOAD_PER_THREAD 32` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && ALGORITHM == 12]_
- L285 `#define GROUP_SIZE_X 64` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && !(ALGORITHM == 12) && ALGORITHM == 13]_
- L286 `#define GROUP_SIZE_Y 4` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && !(ALGORITHM == 12) && ALGORITHM == 13]_
- L287 `#define LOAD_PER_THREAD 16` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && !(ALGORITHM == 12) && ALGORITHM == 13]_
- L289 `#define GROUP_SIZE_X 64` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && !(ALGORITHM == 12) && !(ALGORITHM == 13) && ALGORI...]_
- L290 `#define GROUP_SIZE_Y 8` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && !(ALGORITHM == 12) && !(ALGORITHM == 13) && ALGORI...]_
- L291 `#define LOAD_PER_THREAD 8` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7) && !(ALGORITHM == 7) && !(ALGORITHM == 8) && !(ALGORITHM == 9) && !(ALGORITHM == 10) && !(ALGORITHM == 11) && !(ALGORITHM == 12) && !(ALGORITHM == 13) && ALGORI...]_

#### Entry points (3)

- L94-148 _entry_ `[numthreads(8, 8, 1)] [numthreads(16, 16, 1)] [numthreads(32, 32, 1)] [numthreads(256, 1, 1)] void Gemm(in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `TGemmCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersGemmCS.cpp:195) _[#if ALGORITHM < 4 && ALGORITHM == 0]_
- L163-256 _entry_ `[numthreads(GROUP_SIZE, GROUP_SIZE, 1)] void Gemm(in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupThreadID : SV_GroupThreadID, in const uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `TGemmCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersGemmCS.cpp:195) _[#if !(ALGORITHM < 4) && ALGORITHM < 7]_
- L299-445 _entry_ `[numthreads(GROUP_SIZE_X, GROUP_SIZE_Y, 1)] void Gemm(in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupThreadID : SV_GroupThreadID, in const uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `TGemmCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersGemmCS.cpp:195) _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7)]_

#### Global resources (textures / buffers / samplers) (4)

- L25 _resource_ `Buffer<BUFFER_TYPE> A;`
- L26 _resource_ `Buffer<BUFFER_TYPE> B;`
- L27 _resource_ `Buffer<BUFFER_TYPE> C;`
- L28 _resource_ `RWBuffer<BUFFER_TYPE> Y;`

#### Global parameters (uniforms) (14)

- L10 _parameter_ `WORK_TYPE Alpha;`
- L11 _parameter_ `WORK_TYPE Beta;`
- L12 _parameter_ `int TransA;`
- L13 _parameter_ `int TransB;`
- L14 _parameter_ `uint M;`
- L15 _parameter_ `uint N;`
- L16 _parameter_ `uint K;`
- L17 _parameter_ `uint MxK;`
- L18 _parameter_ `uint KxN;`
- L19 _parameter_ `uint MxN;`
- L20 _parameter_ `uint CWidth;`
- L21 _parameter_ `uint CHeight;`
- L23 _parameter_ `WORK_TYPE CScalar;`
- L34 _parameter_ `uint4 StackShapeA_StackShapeB_StackStrideA_StackStrideB[MAX_NUM_STACK_DIMENSIONS];` — x: StackShapeA[0], ..., StackShapeA[NUM_STACK_DIMENSIONS - 1] y: StackShapeB[0], ..., StackShapeB[NUM_STACK_DIMENSIONS - 1] z: StackStrideA[0], ..., StackStrideA[NUM_STACK_DIMENSIONS - 1] w: StackStrideB[0], ..., StackStrideB[NUM_STACK_DIMENSIONS - 1]

#### groupshared (4)

- L160 _groupshared_ `groupshared WORK_TYPE SharedMemoryA[GROUP_SIZE * GROUP_SIZE];` _[#if !(ALGORITHM < 4) && ALGORITHM < 7]_
- L161 _groupshared_ `groupshared WORK_TYPE SharedMemoryB[GROUP_SIZE * GROUP_SIZE];` _[#if !(ALGORITHM < 4) && ALGORITHM < 7]_
- L296 _groupshared_ `groupshared WORK_TYPE SharedMemoryA[GROUP_SIZE_X * GROUP_SIZE_X];` — Use the larger of group sizes to define the shared memory size Threads will do multiple loads over the smaller dimension to fill the memory completely _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7)]_
- L297 _groupshared_ `groupshared WORK_TYPE SharedMemoryB[GROUP_SIZE_X * GROUP_SIZE_X];` _[#if !(ALGORITHM < 4) && !(ALGORITHM < 7)]_

#### Functions (2)

- L36-76 _function_ `uint3 GetMatrixStackOffsets(const uint3 GroupID)`
- L78-88 _function_ `WORK_TYPE GetBetaTimesC(const uint3 DispatchThreadID)`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersInstanceNormalization.usf` (Private)

- lines: 36; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 4)

- L5 `#define WORK_TYPE float`
- L6 `#define BUFFER_TYPE float`
- L7 `#define READ(x) x`
- L8 `#define WRITE(x) x`

#### Entry points (1)

- L21-36 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void InstanceNormalization(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TInstanceNormalizationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersInstanceNormalizationCS.cpp:14)

#### Global resources (textures / buffers / samplers) (6)

- L10 _resource_ `Buffer<WORK_TYPE> Input;`
- L11 _resource_ `Buffer<WORK_TYPE> InputScale;`
- L12 _resource_ `Buffer<WORK_TYPE> InputBias;`
- L13 _resource_ `Buffer<WORK_TYPE> InputMean;`
- L14 _resource_ `Buffer<WORK_TYPE> InputInvStdDev;`
- L15 _resource_ `RWBuffer<WORK_TYPE> Output;`

#### Global parameters (uniforms) (4)

- L16 _parameter_ `uint Num;`
- L17 _parameter_ `uint ThreadCountX;`
- L18 _parameter_ `uint InstanceSize;`
- L19 _parameter_ `uint ChannelSize;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersLayerNormalization.usf` (Private)

- lines: 79; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 6)

- L6 `#define WORK_TYPE float`
- L7 `#define BUFFER_TYPE float`
- L8 `#define READ(x) x`
- L9 `#define WRITE(x) x`
- L27 `#define STRIDE_IDX 0`
- L29 `#define STATIC_LOOP(Var, From, To) [unroll] for(uint Var = From; Var < To; ++Var)` (3 lines)

#### Entry points (1)

- L55-78 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void LayerNormalization(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TLayerNormalizationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersLayerNormalizationCS.cpp:32)

#### Global resources (textures / buffers / samplers) (6)

- L11 _resource_ `Buffer<BUFFER_TYPE> Input;`
- L13 _resource_ `Buffer<BUFFER_TYPE> InputScale;`
- L15 _resource_ `Buffer<BUFFER_TYPE> InputBias;`
- L17 _resource_ `Buffer<WORK_TYPE> InputMean;`
- L18 _resource_ `Buffer<WORK_TYPE> InputInvStdDev;`
- L19 _resource_ `RWBuffer<BUFFER_TYPE> Output;`

#### Global parameters (uniforms) (8)

- L12 _parameter_ `uint4 InputTensorInfo[NUM_DIMENSIONS];`
- L14 _parameter_ `uint4 ScaleTensorInfo[NUM_DIMENSIONS];`
- L16 _parameter_ `uint4 BiasTensorInfo[NUM_DIMENSIONS];`
- L21 _parameter_ `float Epsilon;`
- L22 _parameter_ `int Axis;`
- L23 _parameter_ `uint ThreadCountX;`
- L24 _parameter_ `uint LayerSize;`
- L25 _parameter_ `uint Num;`

#### Functions (2)

- L33-42 _function_ `void GetDimIterator(const uint GlobalIdx, const uint4 TensorInfo[NUM_DIMENSIONS], out uint DimIterator[NUM_DIMENSIONS])`
- L44-52 _function_ `uint GetInnerIdx(const uint DimIterator[NUM_DIMENSIONS], const uint4 TensorInfo[NUM_DIMENSIONS], const uint Axis)`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersPad.usf` (Private)

- lines: 94; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 8)

- L13 `#define INPUT_STRIDE 0`
- L14 `#define OUTPUT_STRIDE 1`
- L15 `#define INPUT_SIZE 2`
- L16 `#define PRE_PAD 3`
- L19 `#define CONSTANT_MODE 0`
- L20 `#define REFLECT_MODE 1`
- L21 `#define EDGE_MODE 2`
- L23 `#define STATIC_LOOP(Var, From, To) [unroll] for(uint Var = From; Var < To; ++Var)` (3 lines)

#### Entry points (1)

- L48-93 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Pad(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FPadCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersPadCS.cpp:25)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Buffer<float> Input;`
- L7 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (4)

- L8 _parameter_ `uint4 TensorInfo[NUM_DIMENSIONS];`
- L9 _parameter_ `float Value;`
- L10 _parameter_ `uint Num;`
- L11 _parameter_ `uint ThreadCountX;`

#### Functions (2)

- L27-36 _function_ `void GetOutputDimIterator(const uint GlobalIdx, out uint DimIterator[NUM_DIMENSIONS])`
- L38-46 _function_ `uint GetInputGlobalIdx(const uint DimIterator[NUM_DIMENSIONS])`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersPool.usf` (Private)

- lines: 129; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 10)

- L6 `#define NUM_DIMENSION (NUM_SPATIAL_DIMENSIONS+2)`
- L16 `#define OUTPUT_STRIDE 0`
- L17 `#define INPUT_STRIDE 1`
- L18 `#define INPUT_SIZE 2`
- L20 `#define SPATIAL_STRIDE 0`
- L21 `#define SPATIAL_KERNEL 1`
- L22 `#define SPATIAL_PAD_START 2`
- L23 `#define SPATIAL_DILATION 3`
- L25 `#define MAX_POOL 0`
- L26 `#define AVERAGE_POOL 1`

#### Entry points (1)

- L28-128 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Pool(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FPoolCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersPoolCS.cpp:17)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Buffer<float> Input;`
- L9 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (5)

- L10 _parameter_ `uint4 TensorInfo[NUM_DIMENSION];`
- L11 _parameter_ `uint4 SpatialInfo[NUM_SPATIAL_DIMENSIONS];`
- L12 _parameter_ `uint Num;`
- L13 _parameter_ `uint ThreadCountX;`
- L14 _parameter_ `uint KernelVolume;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersReduce.usf` (Private)

- lines: 222; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 14)

- L5 `#define WORK_TYPE float`
- L6 `#define BUFFER_TYPE float`
- L7 `#define READ(x) x`
- L8 `#define WRITE(x) x`
- L20 `#define TYPE_AVERAGE 0`
- L21 `#define TYPE_L1 1`
- L22 `#define TYPE_L2 2`
- L23 `#define TYPE_LOGSUMEXP 3`
- L24 `#define TYPE_MAX 4`
- L25 `#define TYPE_MIN 5`
- L26 `#define TYPE_PROD 6`
- L27 `#define TYPE_SUM 7`
- L28 `#define TYPE_SUMEXP 8`
- L29 `#define TYPE_AVERAGEINVSTDDEV 9`

#### Entry points (1)

- L131-222 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void Reduce(in const uint3 DispatchThreadID : SV_DispatchThreadID, in const uint3 GroupThreadID : SV_GroupThreadID)` — stage: **compute** — C++: `TReduceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersReduceCS.cpp:88)

#### Global resources (textures / buffers / samplers) (3)

- L10 _resource_ `Buffer<WORK_TYPE> Input;`
- L11 _resource_ `RWBuffer<WORK_TYPE> Output;`
- L12 _resource_ `RWBuffer<BUFFER_TYPE> Output2;`

#### Global parameters (uniforms) (5)

- L13 _parameter_ `int NumElemBeforeAxis;`
- L14 _parameter_ `int AxisSize;`
- L15 _parameter_ `int NumElemAfterAxis;`
- L16 _parameter_ `uint4 DispatchIdxAndStride;`
- L17 _parameter_ `float Epsilon;`

#### groupshared (4)

- L32 _groupshared_ `groupshared WORK_TYPE SharedMemoryMean[THREADGROUP_SIZE];` _[#if REDUCE_OPERATOR_TYPE == TYPE_AVERAGEINVSTDDEV]_
- L33 _groupshared_ `groupshared WORK_TYPE SharedMemoryMean2[THREADGROUP_SIZE];` _[#if REDUCE_OPERATOR_TYPE == TYPE_AVERAGEINVSTDDEV]_
- L34 _groupshared_ `groupshared WORK_TYPE SharedMemoryCount[THREADGROUP_SIZE];` _[#if REDUCE_OPERATOR_TYPE == TYPE_AVERAGEINVSTDDEV]_
- L36 _groupshared_ `groupshared WORK_TYPE SharedMemory[THREADGROUP_SIZE];` _[#if !(REDUCE_OPERATOR_TYPE == TYPE_AVERAGEINVSTDDEV)]_

#### Functions (4)

- L38-59 _function_ `WORK_TYPE InitValue(WORK_TYPE FirstValue)` _[#if !(REDUCE_OPERATOR_TYPE == TYPE_AVERAGEINVSTDDEV)]_
- L61-82 _function_ `WORK_TYPE ElementOp(WORK_TYPE Value)` _[#if !(REDUCE_OPERATOR_TYPE == TYPE_AVERAGEINVSTDDEV)]_
- L84-105 _function_ `WORK_TYPE CombineOp(WORK_TYPE ValueA, WORK_TYPE ValueB)` _[#if !(REDUCE_OPERATOR_TYPE == TYPE_AVERAGEINVSTDDEV)]_
- L107-128 _function_ `WORK_TYPE FinalOp(WORK_TYPE Value)` _[#if !(REDUCE_OPERATOR_TYPE == TYPE_AVERAGEINVSTDDEV)]_

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersResize.usf` (Private)

- lines: 213; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`, L5 `/Engine/Private/DoubleFloat.ush`

#### Macros (#define, 21)

- L17 `#define STRIDE_IDX 0`
- L18 `#define SIZE_IDX 1`
- L19 `#define ADJUSTMENT_IDX 2`
- L20 `#define SCALES_IDX 0`
- L21 `#define ROI_START_IDX 2`
- L22 `#define ROI_END_IDX 3`
- L25 `#define COORD_TRANS_HALF_PIXEL 0`
- L26 `#define COORD_TRANS_HALF_PIXEL_SYMMETRIC 1`
- L27 `#define COORD_TRANS_PYTORCH_HALF_PIXEL 2`
- L28 `#define COORD_TRANS_ALIGN_CORNERS 3`
- L29 `#define COORD_TRANS_ASYMMETRIC 4`
- L30 `#define COORD_TRANS_TF_HALF_PIXEL_FOR_NN 5`
- L31 `#define COORD_TRANS_TF_CROP_AND_RESIZE 6`
- L34 `#define NEAREST_MODE_ROUND_PREFER_FLOOR 0`
- L35 `#define NEAREST_MODE_ROUND_PREFER_CEIL 1`
- L36 `#define NEAREST_MODE_FLOOR 2`
- L37 `#define NEAREST_MODE_CEIL 3`
- L40 `#define MODE_NEAREST 0`
- L41 `#define MODE_LINEAR 1`
- L42 `#define MODE_CUBIC 2`
- L44 `#define STATIC_LOOP(Var, From, To) [unroll] for(uint Var = From; Var < To; ++Var)` (3 lines)

#### Entry points (2)

- L132-148 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Resize(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FResizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersResizeCS.cpp:72) _[#if MODE == MODE_NEAREST]_
- L152-210 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Resize(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FResizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersResizeCS.cpp:72) _[#if !(MODE == MODE_NEAREST) && MODE == MODE_LINEAR]_

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `Buffer<float> Input;`
- L11 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (5)

- L10 _parameter_ `uint4 InputTensorInfo[NUM_DIMENSIONS];`
- L12 _parameter_ `uint4 OutputTensorInfo[NUM_DIMENSIONS];`
- L13 _parameter_ `float4 ScalesData[NUM_DIMENSIONS];`
- L14 _parameter_ `uint Num;`
- L15 _parameter_ `uint ThreadCountX;`

#### static const (1)

- L7 _static_const_ `static const uint NumPointsLinear = pow(2,NUM_DIMENSIONS);`

#### Functions (4)

- L48-57 _function_ `void FromIdxToIterator(const uint Idx, const uint4 TensorInfo[NUM_DIMENSIONS], out uint Iterator[NUM_DIMENSIONS])`
- L59-67 _function_ `uint FromIteratorToIdx(const uint4 TensorInfo[NUM_DIMENSIONS], const uint Iterator[NUM_DIMENSIONS])`
- L69-99 _function_ `float TransformCoord(float Resized, uint DimIdx)`
- L101-128 _function_ `void GetNearestInput(uint OutputIndex, out uint Iterator[NUM_DIMENSIONS])`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersScatterND.usf` (Private)

- lines: 113; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 12)

- L6 `#define WORK_TYPE float`
- L7 `#define BUFFER_TYPE float`
- L8 `#define READ(x) x`
- L9 `#define WRITE(x) x`
- L21 `#define STRIDE_IDX 0`
- L22 `#define SIZE_IDX 1`
- L25 `#define TYPE_NONE 0`
- L26 `#define TYPE_ADD 1`
- L27 `#define TYPE_MUL 2`
- L28 `#define TYPE_MAX 3`
- L29 `#define TYPE_MIN 4`
- L42 `#define STATIC_LOOP(Var, From, To) [unroll] for(uint Var = From; Var < To; ++Var)` (3 lines)

#### Entry points (1)

- L83-112 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ScatterND(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FScatterNDCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersScatterNDCS.cpp:28)

#### Global resources (textures / buffers / samplers) (3)

- L11 _resource_ `Buffer<int> InputIndices;`
- L12 _resource_ `Buffer<BUFFER_TYPE> InputUpdates;`
- L13 _resource_ `RWBuffer<BUFFER_TYPE> Output;`

#### Global parameters (uniforms) (5)

- L14 _parameter_ `uint4 DataTensorInfo[NUM_DIMENSIONS];`
- L16 _parameter_ `uint Num;`
- L17 _parameter_ `uint ThreadCountX;`
- L18 _parameter_ `uint PartialIndexRank;` — k
- L19 _parameter_ `uint SliceSize;` — Obtained by multiplying elements in data.shape[k:r-1]

#### Functions (5)

- L31-34 _function_ `uint NormalizeIdx(int Idx, uint DimSize)`
- L37-40 _function_ `int CastInt64ToInt32(uint LSW, int MSW)` — int64_t is only available from SM 6.0, therefore here we need to manually cast to int32.
- L46-55 _function_ `void FromIdxToIterator(const uint Idx, const uint4 TensorInfo[NUM_DIMENSIONS], out uint Iterator[NUM_DIMENSIONS])`
- L57-65 _function_ `uint FromIteratorToIdx(const uint4 TensorInfo[NUM_DIMENSIONS], const uint Iterator[NUM_DIMENSIONS])`
- L67-80 _function_ `void ApplyReduction(const uint OutputIdx, const uint UpdatesIdx)`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersSlice.usf` (Private)

- lines: 40; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 4)

- L12 `#define INPUT_STRIDE 0`
- L13 `#define OUTPUT_STRIDE 1`
- L14 `#define INPUT_STARTS 2`
- L15 `#define INPUT_STEPS 3`

#### Entry points (1)

- L17-39 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Slice(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FSliceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersSliceCS.cpp:17)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Buffer<float> Input;`
- L7 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (3)

- L8 _parameter_ `uint4 TensorInfo[NUM_DIMENSIONS];`
- L9 _parameter_ `uint Num;`
- L10 _parameter_ `uint ThreadCountX;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersSoftmax.usf` (Private)

- lines: 42; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 6)

- L5 `#define WORK_TYPE float`
- L6 `#define BUFFER_TYPE float`
- L7 `#define READ(x) x`
- L8 `#define WRITE(x) x`
- L18 `#define SOFTMAX_TYPE 0`
- L19 `#define LOG_SOFTMAX_TYPE 1`

#### Entry points (1)

- L21-42 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Softmax(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `TSoftmaxCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersSoftmaxCS.cpp:17)

#### Global resources (textures / buffers / samplers) (3)

- L10 _resource_ `Buffer<WORK_TYPE> Input;`
- L11 _resource_ `Buffer<WORK_TYPE> InputSumExp;`
- L12 _resource_ `RWBuffer<WORK_TYPE> Output;`

#### Global parameters (uniforms) (4)

- L13 _parameter_ `uint Num;`
- L14 _parameter_ `uint ThreadCountX;`
- L15 _parameter_ `uint AxisSize;`
- L16 _parameter_ `uint AfterAxisSize;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersSplit.usf` (Private)

- lines: 131; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 5)

- L10 `#define TEMPLATE_BUFFERS(TPrefix) TPrefix##_0; TPrefix##_1; TPrefix##_2; TPrefix##_3; TPrefix##_4; TPrefix##_5; TPrefix##_6; TPrefix##_7;` (9 lines)
- L28 `#define STRIDE_IDX 0`
- L29 `#define SIZE_IDX 1`
- L31 `#define STATIC_LOOP(Var, From, To) [unroll] for(uint Var = From; Var < To; ++Var)` (3 lines)
- L100 `#define WRITE_BUFFER_ARRAY(Idx) if(OutputIterator.TensorIdx == Idx) { Output_##Idx[GetOutputGlobalIdx(DimIterator, Idx)] = Input[Index]; }` (5 lines)

#### Entry points (1)

- L83-130 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Split(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FSplitCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersSplitCS.cpp:31)

#### Structs / classes (1)

- L46-50 _struct_ **`FOutputIterator`** `struct FOutputIterator`
  - L48 _member_ `uint TensorIdx;`
  - L49 _member_ `uint AxisIterator;`

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Buffer<float> Input;`

#### Global parameters (uniforms) (4)

- L22 _parameter_ `uint4 InputTensorInfo[MAX_NUM_DIMENSIONS];`
- L23 _parameter_ `uint4 OutputTensorInfo[MAX_NUM_SPLITS * MAX_NUM_DIMENSIONS];`
- L25 _parameter_ `uint Num;`
- L26 _parameter_ `uint ThreadCountX;`

#### Functions (3)

- L35-44 _function_ `void GetInputDimIterator(const uint GlobalIdx, out uint DimIterator[RANK])`
- L52-71 _function_ `FOutputIterator GetOutputIterator(const uint InputAxisIterator)`
- L73-81 _function_ `uint GetOutputGlobalIdx(const uint DimIterator[RANK], const uint OutputTensorIdx)`

#### Top-level macro invocations (1)

- L20 _macro_call_ `TEMPLATE_BUFFERS(RWBuffer<float> Output)`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersTranspose.usf` (Private)

- lines: 37; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 2)

- L12 `#define OUTPUT_STRIDE 0`
- L13 `#define INPUT_STRIDE_TRANSPOSED 2`

#### Entry points (1)

- L15-36 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Transpose(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTransposeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersTransposeCS.cpp:17)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Buffer<float> Input;`
- L7 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (3)

- L8 _parameter_ `uint4 TensorInfo[NUM_DIMENSIONS];`
- L9 _parameter_ `uint Num;`
- L10 _parameter_ `uint ThreadCountX;`

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersTypeHelper.ush` (Private)

- lines: 17; parse: all-branches
- L3 #pragma `once`

#### Functions (1)

- L9-16 _function_ `int GetInt32IndexFromBuffer(Buffer<int> IndexBuffer, int Index)` — Fetches the low 32 bits of the 64 bit two's complement number at Index and ignores the upper 32 bits. This works, assuming the value is representable as a 32 bit number, since expanding a 32 bit value to 64 bit involves copying the sign bit to the upper 32 bits and therefore bit 63 == bit 31

### `Plugins/Experimental/NNERuntimeRDG/Shaders/Private/NNEHlslShaders/NNEHlslShadersUpsample.usf` (Private)

- lines: 209; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `NNEHlslShadersBroadcastHelper.ush`

#### Macros (#define, 4)

- L12 `#define INPUT_STRIDE 0`
- L13 `#define OUTPUT_STRIDE 1`
- L14 `#define INPUT_SIZE 2`
- L15 `#define SCALES_DIV 3`

#### Entry points (3)

- L19-43 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Upsample(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpsampleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersUpsampleCS.cpp:34) _[#if MODE == 0]_
- L47-111 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Upsample(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpsampleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersUpsampleCS.cpp:34) _[#if !(MODE == 0) && MODE == 1]_
- L115-207 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void Upsample(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpsampleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NNERuntimeRDG/Source/NNEHlslShaders/Private/NNEHlslShadersUpsampleCS.cpp:34) _[#if !(MODE == 0) && !(MODE == 1)]_

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Buffer<float> Input;`
- L7 _resource_ `RWBuffer<float> Output;`

#### Global parameters (uniforms) (3)

- L8 _parameter_ `uint4 TensorInfo[NUM_DIMENSIONS];`
- L9 _parameter_ `uint Num;`
- L10 _parameter_ `uint ThreadCountX;`
