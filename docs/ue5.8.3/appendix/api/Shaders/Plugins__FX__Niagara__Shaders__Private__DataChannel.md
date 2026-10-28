# Shaders / Plugins/FX/Niagara/Shaders/Private/DataChannel

- files: 8; lines: 812
- record kinds: define=1, function=25, member=17, method=49, parameter=13, resource=8, struct=2

### `Plugins/FX/Niagara/Shaders/Private/DataChannel/NiagaraDataInterfaceDataChannelCommon.ush` (Private)

- lines: 242; parse: all-branches

#### Macros (#define, 1)

- L12 `#define NIAGARA_DATACHANNEL_BINDLESSBUFFERS 0`
- L3 #pragma `once`

#### Functions (18)

- L17-28 _function_ `void NiagaraDataChannelRead_Float(Buffer<float> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out float OutValue)`
- L30-34 _function_ `void NiagaraDataChannelRead_Float(Buffer<float> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out float2 OutValue)`
- L36-41 _function_ `void NiagaraDataChannelRead_Float(Buffer<float> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out float3 OutValue)`
- L43-49 _function_ `void NiagaraDataChannelRead_Float(Buffer<float> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out float4 OutValue)`
- L51-62 _function_ `void NiagaraDataChannelRead_Int32(Buffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out int OutValue)`
- L64-68 _function_ `void NiagaraDataChannelRead_Int32(Buffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out int2 OutValue)`
- L70-75 _function_ `void NiagaraDataChannelRead_Int32(Buffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out int3 OutValue)`
- L77-83 _function_ `void NiagaraDataChannelRead_Int32(Buffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out int4 OutValue)`
- L85-97 _function_ `void NiagaraDataChannelRead_Bool(Buffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, out bool OutValue)`
- L138-145 _function_ `void NiagaraDataChannelWrite_Float(RWBuffer<float> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, float InValue)`
- L147-151 _function_ `void NiagaraDataChannelWrite_Float(RWBuffer<float> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, float2 InValue)`
- L153-158 _function_ `void NiagaraDataChannelWrite_Float(RWBuffer<float> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, float3 InValue)`
- L160-166 _function_ `void NiagaraDataChannelWrite_Float(RWBuffer<float> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, float4 InValue)`
- L168-175 _function_ `void NiagaraDataChannelWrite_Int32(RWBuffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, int InValue)`
- L177-181 _function_ `void NiagaraDataChannelWrite_Int32(RWBuffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, int2 InValue)`
- L183-188 _function_ `void NiagaraDataChannelWrite_Int32(RWBuffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, int3 InValue)`
- L190-196 _function_ `void NiagaraDataChannelWrite_Int32(RWBuffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, int4 InValue)`
- L198-205 _function_ `void NiagaraDataChannelWrite_Bool(RWBuffer<int> InBuffer, uint Stride, in out uint RegisterIdx, uint ParticleIdx, bool InValue)`

### `Plugins/FX/Niagara/Shaders/Private/DataChannel/NiagaraDataInterfaceDataChannelTemplateCommon.ush` (Private)

- lines: 38; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L10 _resource_ `Buffer<uint> {ParameterName}_ParamOffsetTable;` — Offset of each parameter accessed by this script. Indices for accessing this table are embeded directly into the HLSL and we generate the table on the CPU accordingly. TODO: Can probably pack this into a single global buffer rather than one per DI.

#### Global parameters (uniforms) (3)

- L12 _parameter_ `int {ParameterName}_ParameterOffsetTableIndex;`
- L13 _parameter_ `int {ParameterName}_FloatStride;`
- L14 _parameter_ `int {ParameterName}_Int32Stride;`

#### Functions (1)

- L18-37 _function_ `bool GetParameterLayoutInfo_{ParameterName}(uint ParameterIndex, out uint OutFloatRegister, out uint OutInt32Register)` — Outputs the starting offset of each component in the channel data for a partiuclar parameter.

### `Plugins/FX/Niagara/Shaders/Private/DataChannel/NiagaraDataInterfaceDataChannelTemplateReadCommon.ush` (Private)

- lines: 268; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Structs / classes (1)

- L27-131 _struct_ **`FNDCAccessContext_{ParameterName}`** `struct FNDCAccessContext_{ParameterName}` — Helper struct with various info needed for reading that can be passed around more easily in generated code.
  - L29 _member_ `bool bValidParameter;`
  - L30 _member_ `bool bValidReadIndex;`
  - L33 _member_ `int ReadIndex;` — Index at which to read data.
  - L36 _member_ `int ParameterComponentStart_Float;` — Component start offests for the current parameter.
  - L37 _member_ `int ParameterComponentStart_Int32;`
  - L41 _member_ `int Register_Float;` — Current registe indices for each of the GPU write buffers
  - L42 _member_ `int Register_Int32;`
  - L45 _method_ `int GetFloatStride()`
  - L46 _method_ `int GetIntStride()`
  - L49 _method_ `Buffer<float> GetBuffer_Float()`
  - L50 _method_ `Buffer<int> GetBuffer_Int32()`
  - L54 _method_ `int GetInstanceCountOffset()` — Instance count used for the written number of elements in the NDC buffers.
  - L57 _method_ `int GetConsumeInstanceCountOffset()` — Instance count used to get a read index when calling Consume().
  - L60 _method_ `int GetBufferSize()` — Return the actual buffer size allocated.
  - L63 _method_ `int Num()` — Actual number of NDC items in the buffers. Must come from an indirect instance count instead of a uniform as the GPU could have written to this buffer.
  - L65 _method_ `int GetConsumeIndex()`
  - L90 _method_ `bool InitDirect(int InReadIndex)`
  - L97 _method_ `bool InitConsume()`
  - L104 _method_ `bool InitForParameter(int ParameterIndex)`
  - L115 _method_ `void Read_Float(out float Value)`
  - L116 _method_ `void Read_Float(out float2 Value)`
  - L117 _method_ `void Read_Float(out float3 Value)`
  - L118 _method_ `void Read_Float(out float4 Value)`
  - L120 _method_ `void Read_Int32(out int Value)`
  - L121 _method_ `void Read_Int32(out int2 Value)`
  - L122 _method_ `void Read_Int32(out int3 Value)`
  - L123 _method_ `void Read_Int32(out int4 Value)`
  - L125 _method_ `void Read_Bool(out bool Value)`

#### Global resources (textures / buffers / samplers) (3)

- L7 _resource_ `Buffer<float> {ParameterName}_DataFloat;`
- L8 _resource_ `Buffer<int> {ParameterName}_DataInt32;`
- L24 _resource_ `Buffer<int> {ParameterName}_NDCSpawnDataBuffer;` — Buffer containing back mapping from spawn particle exec index to the NDC index that spawned that particle. Arraged into power of two buckets so that we can avoid an entry per particle.

#### Global parameters (uniforms) (4)

- L13 _parameter_ `int {ParameterName}_InstanceCountOffset;` — Instance count offset for the buffer we're reading. Must be done via an instance count slot as data can come from CPU and GPU.
- L16 _parameter_ `int {ParameterName}_ConsumeInstanceCountOffset;` — Instance count offset for tracking consume calls.
- L18 _parameter_ `int {ParameterName}_BufferSize;`
- L20 _parameter_ `int {ParameterName}_NDCElementCountAtSpawn;`

#### Functions (2)

- L133-143 _function_ `void Num_{ParameterName}(out int OutNum)`
- L145-267 _function_ `void GetNDCSpawnData_{ParameterName}(NiagaraEmitterID InEmitterID, int InExecIndex, out int OutNDCIndex, out int OutNDCSpawnIndex, out int OutNDCSpawnCount)`

### `Plugins/FX/Niagara/Shaders/Private/DataChannel/NiagaraDataInterfaceDataChannelTemplateWriteCommon.ush` (Private)

- lines: 165; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Structs / classes (1)

- L34-165 _struct_ **`FNDCAccessContext_{ParameterName}`** `struct FNDCAccessContext_{ParameterName}` — Helper struct with various info needed for writing that can be passed around more easily in generated code.
  - L36 _member_ `bool bValidWriteIndex;`
  - L37 _member_ `bool bValidParameter;`
  - L40 _member_ `int WriteIndex;` — Indices we'll be writing to each buffer.
  - L42 _member_ `int WriteIndexCPU;`
  - L43 _member_ `int WriteIndexGPU;`
  - L46 _member_ `int ParameterComponentStart_Float;` — Component start offests for the current parameter.
  - L47 _member_ `int ParameterComponentStart_Int32;`
  - L51 _member_ `int CurrRegister_Float;` — Current register indices for each component buffer
  - L52 _member_ `int CurrRegister_Int32;`
  - L55 _member_ `bool bReadGPUOrCPU;`
  - L57 _method_ `int GetFloatStride()`
  - L58 _method_ `int GetInt32Stride()`
  - L61 _method_ `RWBuffer<float> GetGPUBuffer_Float()`
  - L62 _method_ `RWBuffer<int> GetGPUBuffer_Int32()`
  - L64 _method_ `int GetGPUInstanceCountOffset()` — TODO: Half Support \| RWBuffer<half> GetGPUBuffer_Half() { return TPLx0ParameterNamex0TPL_GPUBufferHalf; }
  - L65 _method_ `int GetGPUBufferSize()`
  - L67 _method_ `RWBuffer<float> GetCPUBuffer_Float()`
  - L68 _method_ `RWBuffer<int> GetCPUBuffer_Int32()`
  - L70 _method_ `int GetCPUInstanceCountOffset()` — TODO: Half Support \| RWBuffer<half> GetCPUBuffer_Half() { return TPLx0ParameterNamex0TPL_CPUBufferHalf; }
  - L71 _method_ `int GetCPUBufferSize()`
  - L73 _method_ `RWBuffer<float> GetCurrBuffer_Float()`
  - L74 _method_ `RWBuffer<int> GetCurrBuffer_Int32()`
  - L77 _method_ `bool ShouldWriteGPUData()`
  - L78 _method_ `bool ShouldWriteCPUData()`
  - L80 _method_ `int GetAppendIndex(int InstanceCountOffset, int BufferSize)`
  - L107 _method_ `bool InitAppend()` — Initialize our append indices. Called at the start of the append funciton.
  - L119 _method_ `bool InitForParameter(int ParameterIndex)` — Initialize for the given parameter index.
  - L126 _method_ `bool InitForGPUWrite()` — Initialize for wrting the current parameter to the GPU buffers
  - L138 _method_ `bool InitForCPUWrite()` — Initialize for wrting the current parameter to the "CPU" buffers
  - L149 _method_ `void Write_Float(float Value)`
  - L150 _method_ `void Write_Float(float2 Value)`
  - L151 _method_ `void Write_Float(float3 Value)`
  - L152 _method_ `void Write_Float(float4 Value)`
  - L154 _method_ `void Write_Int32(int Value)`
  - L155 _method_ `void Write_Int32(int2 Value)`
  - L156 _method_ `void Write_Int32(int3 Value)`
  - L157 _method_ `void Write_Int32(int4 Value)`
  - L159 _method_ `void Write_Bool(bool Value)`

#### Global resources (textures / buffers / samplers) (4)

- L9 _resource_ `RWBuffer<float> {ParameterName}_GPUBufferFloat;` — Data bound for other readers on the GPU is written into one large shared buffer We index into this using atomic ops on an instance count in RWCountsBuffer.
- L10 _resource_ `RWBuffer<int> {ParameterName}_GPUBufferInt32;`
- L21 _resource_ `RWBuffer<float> {ParameterName}_CPUBufferFloat;` — Data bounds back to the CPU for game and CPU sims is written into a separate specific buffer indexed directly by the thread index.
- L22 _resource_ `RWBuffer<int> {ParameterName}_CPUBufferInt32;`

#### Global parameters (uniforms) (6)

- L15 _parameter_ `int {ParameterName}_GPUInstanceCountOffset;` — Buffer and offset for our instance count value. We'll atomically update this accordingly if we're write/appending.
- L16 _parameter_ `int {ParameterName}_GPUBufferSize;`
- L27 _parameter_ `int {ParameterName}_CPUInstanceCountOffset;` — Buffer and offset for our instance count value. We'll atomically update this accordingly if we're write/appending.
- L28 _parameter_ `int {ParameterName}_CPUBufferSize;`
- L29 _parameter_ `int {ParameterName}_CPUFloatStride;`
- L30 _parameter_ `int {ParameterName}_CPUInt32Stride;`

### `Plugins/FX/Niagara/Shaders/Private/DataChannel/NiagaraDataInterfaceDataChannelTemplate_Append.ush` (Private)

- lines: 25; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (1)

- L8-25 _function_ `{PerParameterFunctionDefinitions} void {FunctionSymbol}(bool bEmit, {FunctionInputParameters}, out bool bOutSuccess)`

### `Plugins/FX/Niagara/Shaders/Private/DataChannel/NiagaraDataInterfaceDataChannelTemplate_Consume.ush` (Private)

- lines: 32; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (1)

- L8-30 _function_ `{PerParameterFunctionDefinitions} void {FunctionSymbol}(bool bInConsume, out bool bOutSuccess, out int OutIndex, {FunctionOutputParameters})`

### `Plugins/FX/Niagara/Shaders/Private/DataChannel/NiagaraDataInterfaceDataChannelTemplate_Read.ush` (Private)

- lines: 27; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (1)

- L8-25 _function_ `{PerParameterFunctionDefinitions} void {FunctionSymbol}(int ElementIndex, out bool bOutSuccess, {FunctionOutputParameters})`

### `Plugins/FX/Niagara/Shaders/Private/DataChannel/NiagaraDataInterfaceDataChannelTemplate_Write.ush` (Private)

- lines: 15; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (1)

- L8-15 _function_ `{PerParameterFunctionDefinitions} void {FunctionSymbol}(bool bEmit, int ElementIndex, {FunctionInputParameters}, out bool bOutSuccess)`
