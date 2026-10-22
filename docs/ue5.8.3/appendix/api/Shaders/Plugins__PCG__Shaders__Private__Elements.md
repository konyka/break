# Shaders / Plugins/PCG/Shaders/Private/Elements

- files: 7; lines: 714
- record kinds: define=8, entry=7

### `Plugins/PCG/Shaders/Private/Elements/PCGCopyPoints.usf` (Private)

- lines: 172; parse: all-branches

#### Entry points (1)

- L3-171 _entry_ `[numthreads(64, 1, 1)] void PCGCopyPointsCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

### `Plugins/PCG/Shaders/Private/Elements/PCGCopyPointsAnalysis.usf` (Private)

- lines: 62; parse: all-branches

#### Entry points (1)

- L3-61 _entry_ `[numthreads(64, 1, 1)] void PCGCopyPointsAnalysisCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

### `Plugins/PCG/Shaders/Private/Elements/PCGCullPointsOutsideActorBounds.usf` (Private)

- lines: 42; parse: all-branches

#### Entry points (1)

- L3-41 _entry_ `[numthreads(64, 1, 1)] void PCGCullPointsOutsideActorBoundsCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

### `Plugins/PCG/Shaders/Private/Elements/PCGMetadataPartition.usf` (Private)

- lines: 31; parse: all-branches

#### Entry points (1)

- L5-30 _entry_ `[numthreads(64, 1, 1)] void PCGMetadataPartitionCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

### `Plugins/PCG/Shaders/Private/Elements/PCGNormalToDensity.usf` (Private)

- lines: 85; parse: all-branches

#### Macros (#define, 7)

- L4 `#define NORMAL_TO_DENSITY_MODE_Set 0`
- L5 `#define NORMAL_TO_DENSITY_MODE_Minimum 1`
- L6 `#define NORMAL_TO_DENSITY_MODE_Maximum 2`
- L7 `#define NORMAL_TO_DENSITY_MODE_Add 3`
- L8 `#define NORMAL_TO_DENSITY_MODE_Subtract 4`
- L9 `#define NORMAL_TO_DENSITY_MODE_Multiply 5`
- L10 `#define NORMAL_TO_DENSITY_MODE_Divide 6`

#### Entry points (1)

- L12-84 _entry_ `[numthreads(64, 1, 1)] void PCGNormalToDensityCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

### `Plugins/PCG/Shaders/Private/Elements/PCGStaticMeshSpawner.usf` (Private)

- lines: 164; parse: all-branches

#### Macros (#define, 1)

- L8 `#define PCG_PRODUCE_OUTPUT_POINTS {ProduceOutputPoints}`
- L163 #undef `PCG_PRODUCE_OUTPUT_POINTS`

#### Entry points (1)

- L10-161 _entry_ `[numthreads(64, 1, 1)] void PCGStaticMeshSpawnerCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**

### `Plugins/PCG/Shaders/Private/Elements/PCGTransformPoints.usf` (Private)

- lines: 158; parse: all-branches

#### Entry points (1)

- L3-157 _entry_ `[numthreads(64, 1, 1)] void PCGTransformPointsCS(uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute**
