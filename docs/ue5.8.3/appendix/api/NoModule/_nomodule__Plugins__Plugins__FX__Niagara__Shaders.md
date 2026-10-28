# NoModule / _nomodule__Plugins__Plugins__FX__Niagara__Shaders

- module root: `.`
- headers: 3; symbols: 77
- symbol kinds: enum=2, enumerator=16, function=22, macro=22, member=8, struct=5, typedef=2

### `Plugins/FX/Niagara/Shaders/Shared/NiagaraRibbonShared.h` (Other)


#### struct `FRibbonAccumulationValues`  
`struct FRibbonAccumulationValues`  
_L10-20_
- L12 _public member_ `float RibbonDistance;`
- L13 _public member_ `uint SegmentCount;`
- L14 _public member_ `uint MultiRibbonCount;` — Only valid when HAS_RIBBON_ID
- L15 _public member_ `float TessTotalLength;` — Only valid when RibbonWantsAutomaticTessellation()
- L16 _public member_ `float TessAvgSegmentLength;` — Only valid when RibbonWantsAutomaticTessellation()
- L17 _public member_ `float TessAvgSegmentAngle;` — Only valid when RibbonWantsAutomaticTessellation()
- L18 _public member_ `float TessTwistAvgAngle;` — Only valid when RibbonWantsAutomaticTessellation() && RibbonHasTwist()
- L19 _public member_ `float TessTwistAvgWidth;` — Only valid when RibbonWantsAutomaticTessellation() && RibbonHasTwist()

#### struct `ENiagaraGpuTessellationMode`  
`struct ENiagaraGpuTessellationMode`  
_L22-30_

#### enum `ENiagaraGpuTessellationMode::Type`  
`enum Type`  
_L24-29_
- L26 _public enumerator_ `Disabled`
- L27 _public enumerator_ `Automatic`
- L28 _public enumerator_ `Constant`

#### Free symbols / members of external scopes

- L7 _macro_ `#define uint uint32`
- L32 _macro_ `#define NIAGARA_RIBBON_TESSELLATION_FULL_STATS_NUM_ELEMENTS 5`
- L33 _macro_ `#define NIAGARA_RIBBON_TESSELLATION_NO_TWIST_STATS_NUM_ELEMENTS 3`
- L35 _macro_ `#define VERTEX_GEN_OUTPUT_DATA_AUTO_TESSELLATION_NUM_ELEMENTS 15`
- L36 _macro_ `#define VERTEX_GEN_OUTPUT_DATA_NUM_ELEMENTS 5`

### `Plugins/FX/Niagara/Shaders/Shared/NiagaraStatelessBuiltDistribution.h` (Other)


#### struct `FNiagaraStatelessBuiltDistribution`  
`struct FNiagaraStatelessBuiltDistribution`  
_L30-180_
- L55 _public function_ `static bool IsValid(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L57 _public function_ `static bool IsUniformRandomEnabled(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L58 _public function_ `static bool IsAddressModeWrap(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L59 _public function_ `static bool IsInterpolationModeLinear(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L60 _public function_ `static bool IsBufferReadModeStatic(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L61 _public function_ `static bool IsLookupValueModeRandom(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L63 _public function_ `static uint GetBufferOffset(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L64 _public function_ `static uint GetTableLength(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L65 _public function_ `static uint GetLookupValueMode(FNiagaraStatelessBuiltDistributionTypeIn BuiltData)`
- L67 _public function_ `static void ConvertRandomToLookup(FNiagaraStatelessBuiltDistributionTypeIn BuiltData, float Random, UEOutParam(uint) OutIndexA, UEOutParam(uint) OutIndexB, UEOutParam(float) OutInterp)`
- L85 _public function_ `static void ConvertTimeToLookup(FNiagaraStatelessBuiltDistributionTypeIn BuiltData, float Time, UEOutParam(uint) OutIndexA, UEOutParam(uint) OutIndexB, UEOutParam(float) OutInterp)`
- L109 _public function_ `static FNiagaraStatelessBuiltDistributionType GetDefault()`
- L111 _public function_ `static void SetInterpolationMode(FNiagaraStatelessBuiltDistributionType& BuiltData, bool bLinearInterpolation)`
- L117 _public function_ `static void SetAddressMode(FNiagaraStatelessBuiltDistributionType& BuiltData, bool bClampAddress)`
- L123 _public function_ `static void SetBufferReadMode(FNiagaraStatelessBuiltDistributionType& BuiltData, bool bStaticBuffer)`
- L129 _public function_ `static void SetLookupValueMode(FNiagaraStatelessBuiltDistributionType& BuiltData, uint8 ValueMode)`
- L143 _public function_ `static void SetUniformRandom(FNiagaraStatelessBuiltDistributionType& BuiltData, bool bEnabled)`
- L148 _public function_ `static void SetTimeScaleBias(FNiagaraStatelessBuiltDistributionType& BuiltData, float TimeScale, float TimeBias)`
- L154 _public function_ `static void SetLookupParameters(FNiagaraStatelessBuiltDistributionType& BuiltData, uint BufferOffset, uint TableLength)`
- L168 _public function_ `static void SetLookupParameters(FNiagaraStatelessBuiltDistributionType& BuiltData, uint BufferOffset, uint TableLength, float MinTime, float MaxTime)`

#### struct `FNiagaraStatelessBuiltDistribution::EFlags`  
`struct EFlags`  
_L32-53_

#### enum `FNiagaraStatelessBuiltDistribution::EFlags::(anonymous)`  
``  
_L35-52_

#### Free symbols / members of external scopes

- L5 _macro_ `#define uint uint32`
- L6 _typedef_ `typedef FUintVector3 FNiagaraStatelessBuiltDistributionType;`
- L7 _typedef_ `typedef const FUintVector3& FNiagaraStatelessBuiltDistributionTypeIn;`
- L9 _macro_ `#define UEAsFloat(X) reinterpret_cast<const float&>(X);`
- L10 _macro_ `#define UEMin(X, Y) FMath::Min(X, Y)`
- L11 _macro_ `#define UEMax(X, Y) FMath::Max(X, Y)`
- L12 _macro_ `#define UEFrac(X) FMath::Fractional(X)`
- L13 _macro_ `#define UERoundToInt(X) FMath::RoundToInt(X)`
- L14 _macro_ `#define UEOutParam(X) X&`
- L17 _macro_ `#define FNiagaraStatelessBuiltDistributionType uint3` — typedef uint3			FNiagaraStatelessBuiltDistributionType;
- L18 _macro_ `#define FNiagaraStatelessBuiltDistributionTypeIn uint3`
- L20 _macro_ `#define UEAsFloat(X) asfloat(X)`
- L21 _macro_ `#define UEMin(X, Y) min(X, Y)`
- L22 _macro_ `#define UEMax(X, Y) max(X, Y)`
- L23 _macro_ `#define UEFrac(X) frac(X)`
- L24 _macro_ `#define UERoundToInt(X) uint(round(X))`
- L25 _macro_ `#define UEOutParam(X) out X`
- L36 _enumerator_ `BufferOffsetShift = 0u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — Offset in the buffer where the data is stored
- L37 _enumerator_ `BufferOffsetBits = 17u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — 128k max offset
- L38 _enumerator_ `BufferOffsetMask = (1u << BufferOffsetBits) - 1u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`)
- L40 _enumerator_ `TableLengthShift = 17u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — Length of the table data minus 1
- L41 _enumerator_ `TableLengthBits = 9u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — 512 entries max
- L42 _enumerator_ `TableLengthMask = (1u << TableLengthBits) - 1u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`)
- L44 _enumerator_ `LookupValueModeShift = 26u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — Lookup Value Mode where all bits set is assumed to be random internally
- L45 _enumerator_ `LookupValueModeBits = 2u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — The caller must decide how to interpret this data
- L46 _enumerator_ `LookupValueModeMask = (1u << LookupValueModeBits) - 1u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`)
- L48 _enumerator_ `UniformRandom = 1u << 28u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — When true random will be uniform when interpolating vs non-uniform
- L49 _enumerator_ `AddressModeWrap = 1u << 29u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — The address mode, when 0 clamp, when 1 wrap
- L50 _enumerator_ `InterpolationModeLinear = 1u << 30u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — The interpolation mode, when 0 none, when 1 linear
- L51 _enumerator_ `BufferReadModeStatic = 1u << 31u` (scope `FNiagaraStatelessBuiltDistribution::EFlags::__anon252f5d560103`) — The buffer read mode, when 0 dynamic, when 1 static

### `Plugins/FX/Niagara/Shaders/Shared/NiagaraStatelessDefinitions.h` (Other)


#### struct `FNiagaraStatelessDefinitions`  
`struct FNiagaraStatelessDefinitions`  
_L10-14_
- desc: Core random functionality
- L12 _public function_ `static uint4 MakeRandomSeed(uint EmitterSeed, uint UniqueID, uint ModuleOffset, uint CallOffset)`
- L13 _public function_ `static uint4 OffsetRandomSeedForCall(uint4 Seed, uint CallOffset)`

#### Free symbols / members of external scopes

- L5 _macro_ `#define uint uint32`
- L6 _macro_ `#define uint4 FUintVector4`
