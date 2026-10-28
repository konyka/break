# Shaders / Plugins/PCG/Shaders/Private/BuiltInKernels

- files: 5; lines: 485
- record kinds: define=7, entry=5, function=2, static_const=1

### `Plugins/PCG/Shaders/Private/BuiltInKernels/PCGCountUniqueAttributeValues.usf` (Private)

- lines: 88; parse: all-branches

#### Macros (#define, 1)

- L5 `#define PCG_OUTPUT_TO_RAW_BUFFER {RawDataOutputEnabled}`
- L87 #undef `PCG_OUTPUT_TO_RAW_BUFFER`

#### Entry points (1)

- L27-85 _entry_ `[numthreads(64, 1, 1)] void PCGCountUniqueAttributeValuesCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

#### Functions (1)

- L11-25 _function_ `void InitializeValueKey(uint InDataIndex, uint InValueKey)`

### `Plugins/PCG/Shaders/Private/BuiltInKernels/PCGDataNum.usf` (Private)

- lines: 25; parse: all-branches

#### Entry points (1)

- L4-24 _entry_ `[numthreads(64, 1, 1)] void PCGDataNumCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — Returns the total data count

### `Plugins/PCG/Shaders/Private/BuiltInKernels/PCGPostRayTrace.usf` (Private)

- lines: 98; parse: all-branches

#### Entry points (1)

- L5-97 _entry_ `[numthreads(64, 1, 1)] void PCGPostRayTraceCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

### `Plugins/PCG/Shaders/Private/BuiltInKernels/PCGPreRayTrace.usf` (Private)

- lines: 112; parse: all-branches

#### Macros (#define, 5)

- L5 `#define PCG_END_POINTS_ENABLED {EndPointsEnabled}`
- L7 `#define PCG_RAYCAST_MODE_INFINITE 0`
- L8 `#define PCG_RAYCAST_MODE_SCALED_VECTOR 1`
- L9 `#define PCG_RAYCAST_MODE_NORMALIZED_WITH_LENGTH 2`
- L10 `#define PCG_RAYCAST_MODE_SEGMENTS 3`

#### Entry points (1)

- L12-111 _entry_ `[numthreads(64, 1, 1)] void PCGPreRayTraceCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

### `Plugins/PCG/Shaders/Private/BuiltInKernels/PCGSMSpawnerAnalysis.usf` (Private)

- lines: 162; parse: all-branches

#### Macros (#define, 1)

- L6 `#define PCG_OUTPUT_TO_RAW_BUFFER {RawDataOutputEnabled}`
- L161 #undef `PCG_OUTPUT_TO_RAW_BUFFER`

#### Entry points (1)

- L32-159 _entry_ `[numthreads(64, 1, 1)] void PCGSMSpawnerAnalysisCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

#### static const (1)

- L13 _static_const_ `static const uint CullingCellMinMaxPositionScaleStride = 6;` — Number of uint32 entries per (primitive, culling cell) in the CullingCellMinMaxPositions buffer: 3 inv-min position, 3 max position.

#### Functions (1)

- L15-30 _function_ `void InitializeValueKey(uint InDataIndex, uint InValueKey, uint InCullingCellIndex)`
