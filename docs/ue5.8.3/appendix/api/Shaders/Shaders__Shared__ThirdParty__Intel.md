# Shaders / Shaders/Shared/ThirdParty/Intel

- files: 2; lines: 639
- record kinds: define=37, function=59, member=24, prototype=4, struct=2

### `Shaders/Shared/ThirdParty/Intel/IntelExtensions.h` (Shared)

- lines: 460; parse: all-branches

#### Macros (#define, 28)

- L38 `#define INTEL_EXT_WAVE_SHUFFLE 17`
- L39 `#define INTEL_EXT_WAVE_LANEINDEX 18`
- L40 `#define INTEL_EXT_WAVE_WAVEACTIVEBALLOT 19`
- L41 `#define INTEL_EXT_WAVE_WAVEPREFIXOP 20`
- L42 `#define INTEL_EXT_WAVE_WAVEALL 21`
- L43 `#define INTEL_EXT_SIMDSIZE 22`
- L73 `#define INTEL_EXT_WAVEOPS_SUM 0`
- L74 `#define INTEL_EXT_WAVEOPS_PROD 1`
- L75 `#define INTEL_EXT_WAVEOPS_UMIN 2`
- L76 `#define INTEL_EXT_WAVEOPS_UMAX 3`
- L77 `#define INTEL_EXT_WAVEOPS_IMIN 4`
- L78 `#define INTEL_EXT_WAVEOPS_IMAX 5`
- L79 `#define INTEL_EXT_WAVEOPS_OR 6`
- L80 `#define INTEL_EXT_WAVEOPS_XOR 7`
- L81 `#define INTEL_EXT_WAVEOPS_AND 8`
- L82 `#define INTEL_EXT_WAVEOPS_FSUM 9`
- L83 `#define INTEL_EXT_WAVEOPS_FPROD 10`
- L84 `#define INTEL_EXT_WAVEOPS_FMIN 11`
- L85 `#define INTEL_EXT_WAVEOPS_FMAX 12`
- L87 `#define INTEL_EXT_UINT64_ATOMIC 24`
- L89 `#define INTEL_EXT_ATOMIC_ADD 0`
- L90 `#define INTEL_EXT_ATOMIC_MIN 1`
- L91 `#define INTEL_EXT_ATOMIC_MAX 2`
- L92 `#define INTEL_EXT_ATOMIC_CMPXCHG 3`
- L93 `#define INTEL_EXT_ATOMIC_XCHG 4`
- L94 `#define INTEL_EXT_ATOMIC_AND 5`
- L95 `#define INTEL_EXT_ATOMIC_OR 6`
- L96 `#define INTEL_EXT_ATOMIC_XOR 7`

#### Structs / classes (1)

- L16-33 _struct_ **`IntelExtensionStruct`** `struct IntelExtensionStruct` — Intel extension buffer structure, generic interface for 0-operand extensions (e.g. sync opcodes) 1-operand unary operations (e.g. render target writes) 2-operand binary operations (future extensions) 3-operand ternary operations (future extensions)
  - L18 _member_ `uint opcode;` — opcode to execute
  - L19 _member_ `uint rid;` — resource ID
  - L20 _member_ `uint sid;` — sampler ID
  - L22 _member_ `float4 src0f;` — float source operand  0
  - L23 _member_ `float4 src1f;` — float source operand  0
  - L24 _member_ `float4 src2f;` — float source operand  0
  - L25 _member_ `float4 dst0f;` — float destination operand
  - L27 _member_ `uint4 src0u;`
  - L28 _member_ `uint4 src1u;`
  - L29 _member_ `uint4 src2u;`
  - L30 _member_ `uint4 dst0u;`
  - L32 _member_ `float pad[181];` — total lenght 864

#### Functions (50)

- L64-68 _function_ `void IntelExt_Init()` — Initialize Intel HSLS Extensions This method should be called before any other extension function
- L98-105 _function_ `float IntelExt_WaveReadLaneAt(float input, uint lane)`
- L107-114 _function_ `int IntelExt_WaveReadLaneAt(int input, uint lane)`
- L116-121 _function_ `uint IntelExt_WaveGetLaneIndex()`
- L123-127 _function_ `float IntelExt_QuadReadAcrossDiagonal(float localValue)`
- L129-133 _function_ `int IntelExt_QuadReadAcrossDiagonal(int localValue)`
- L135-139 _function_ `float IntelExt_QuadReadLaneAt(float sourceValue, uint quadLaneID)`
- L141-145 _function_ `int IntelExt_QuadReadLaneAt(int sourceValue, uint quadLaneID)`
- L147-151 _function_ `float IntelExt_QuadReadAcrossX(float localValue)`
- L153-157 _function_ `int IntelExt_QuadReadAcrossX(int localValue)`
- L159-163 _function_ `float IntelExt_QuadReadAcrossY(float localValue)`
- L165-169 _function_ `int IntelExt_QuadReadAcrossY(int localValue)`
- L171-177 _function_ `uint4 IntelExt_WaveActiveBallot(bool localValue)`
- L179-183 _function_ `float IntelExt_WaveReadLaneFirst(float input)`
- L185-189 _function_ `int IntelExt_WaveReadLaneFirst(int input)`
- L191-194 _function_ `bool IntelExt_WaveActiveAllTrue(bool expr)`
- L196-199 _function_ `bool IntelExt_WaveActiveAllEqual(float localValue)`
- L201-204 _function_ `bool IntelExt_WaveActiveAllEqual(int localValue)`
- L206-213 _function_ `float IntelExt_WaveAll(float localValue, uint opType)`
- L215-222 _function_ `int IntelExt_WaveAll(int localValue, uint opType)`
- L224-227 _function_ `int IntelExt_WaveActiveBitAnd(int localValue)`
- L229-232 _function_ `int IntelExt_WaveActiveBitOr(int localValue)`
- L234-237 _function_ `int IntelExt_WaveActiveBitXor(int localValue)`
- L239-242 _function_ `uint IntelExt_WaveActiveCountBits(bool bBit)`
- L244-247 _function_ `float IntelExt_WaveActiveMax(float localValue)`
- L249-252 _function_ `int IntelExt_WaveActiveMax(int localValue)`
- L254-257 _function_ `uint IntelExt_WaveActiveMax(uint localValue)`
- L259-262 _function_ `float IntelExt_WaveActiveMin(float localValue)`
- L264-267 _function_ `int IntelExt_WaveActiveMin(int localValue)`
- L269-272 _function_ `uint IntelExt_WaveActiveMin(uint localValue)`
- L274-277 _function_ `float IntelExt_WaveActiveProduct(float localValue)`
- L279-282 _function_ `int IntelExt_WaveActiveProduct(int localValue)`
- L284-287 _function_ `float IntelExt_WaveActiveSum(float localValue)`
- L289-292 _function_ `int IntelExt_WaveActiveSum(int localValue)`
- L294-297 _function_ `bool IntelExt_WaveActiveAnyTrue(bool expr)`
- L299-304 _function_ `uint IntelExt_WaveGetLaneCount()`
- L306-311 _function_ `bool IntelExt_WaveIsFirstLane()`
- L313-318 _function_ `uint IntelExt_WavePrefixCountBits(bool bBit)`
- L320-327 _function_ `float IntelExt_WavePrefixProduct(float value)`
- L329-336 _function_ `int IntelExt_WavePrefixProduct(int value)`
- L338-345 _function_ `float IntelExt_WavePrefixSum(float value)`
- L347-354 _function_ `int IntelExt_WavePrefixSum(int value)`
- L358-368 _function_ `uint2 IntelExt_InterlockedMaxUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — uint64 typed atomics Interlocked max
- L371-381 _function_ `uint2 IntelExt_InterlockedMinUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked Min
- L384-394 _function_ `uint2 IntelExt_InterlockedAndUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked and
- L397-407 _function_ `uint2 IntelExt_InterlockedOrUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked or
- L410-420 _function_ `uint2 IntelExt_InterlockedAddUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked add
- L423-433 _function_ `uint2 IntelExt_InterlockedXorUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked xor
- L436-446 _function_ `uint2 IntelExt_InterlockedExchangeUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked exchange
- L449-460 _function_ `uint2 IntelExt_InterlockedCompareExchangeUint64(RWTexture2D<uint2> uav, uint2 address, uint2 cmp_value, uint2 xchg_value)` — Interlocked compare exchange

#### Prototypes (2)

- L54 _prototype_ `RWStructuredBuffer<IntelExtensionStruct> g_IntelExt : register( INTEL_SHADER_EXT_UAV_SLOT )` _[#if defined(INTEL_SHADER_EXT_UAV_SLOT)]_
- L56 _prototype_ `RWStructuredBuffer<IntelExtensionStruct> g_IntelExt : register( u63 )` _[#if !(defined(INTEL_SHADER_EXT_UAV_SLOT))]_

### `Shaders/Shared/ThirdParty/Intel/IntelExtensions12.h` (Shared)

- lines: 179; parse: all-branches

#### Macros (#define, 9)

- L52 `#define INTEL_EXT_UINT64_ATOMIC 24`
- L54 `#define INTEL_EXT_ATOMIC_ADD 0`
- L55 `#define INTEL_EXT_ATOMIC_MIN 1`
- L56 `#define INTEL_EXT_ATOMIC_MAX 2`
- L57 `#define INTEL_EXT_ATOMIC_CMPXCHG 3`
- L58 `#define INTEL_EXT_ATOMIC_XCHG 4`
- L59 `#define INTEL_EXT_ATOMIC_AND 5`
- L60 `#define INTEL_EXT_ATOMIC_OR 6`
- L61 `#define INTEL_EXT_ATOMIC_XOR 7`

#### Structs / classes (1)

- L16-33 _struct_ **`IntelExtensionStruct`** `struct IntelExtensionStruct` — Intel extension buffer structure, generic interface for 0-operand extensions (e.g. sync opcodes) 1-operand unary operations (e.g. render target writes) 2-operand binary operations (future extensions) 3-operand ternary operations (future extensions)
  - L18 _member_ `uint opcode;` — opcode to execute
  - L19 _member_ `uint rid;` — resource ID
  - L20 _member_ `uint sid;` — sampler ID
  - L22 _member_ `float4 src0f;` — float source operand  0
  - L23 _member_ `float4 src1f;` — float source operand  0
  - L24 _member_ `float4 src2f;` — float source operand  0
  - L25 _member_ `float4 dst0f;` — float destination operand
  - L27 _member_ `uint4 src0u;`
  - L28 _member_ `uint4 src1u;`
  - L29 _member_ `uint4 src2u;`
  - L30 _member_ `uint4 dst0u;`
  - L32 _member_ `float pad[181];` — total length 864

#### Functions (9)

- L68-72 _function_ `void IntelExt_Init()` — Initialize Intel HLSL Extensions This method should be called before any other extension function
- L77-87 _function_ `uint2 IntelExt_InterlockedMaxUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — uint64 typed atomics Interlocked max
- L90-100 _function_ `uint2 IntelExt_InterlockedMinUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked min
- L103-113 _function_ `uint2 IntelExt_InterlockedAndUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked and
- L116-126 _function_ `uint2 IntelExt_InterlockedOrUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked or
- L129-139 _function_ `uint2 IntelExt_InterlockedAddUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked add
- L142-152 _function_ `uint2 IntelExt_InterlockedXorUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked xor
- L155-165 _function_ `uint2 IntelExt_InterlockedExchangeUint64(RWTexture2D<uint2> uav, uint2 address, uint2 value)` — Interlocked xor
- L168-179 _function_ `uint2 IntelExt_InterlockedCompareExchangeUint64(RWTexture2D<uint2> uav, uint2 address, uint2 cmp_value, uint2 xchg_value)` — Interlocked compare exchange

#### Prototypes (2)

- L47 _prototype_ `RWStructuredBuffer<IntelExtensionStruct> g_IntelExt : register( INTEL_SHADER_EXT_UAV_SLOT )` _[#if defined(INTEL_SHADER_EXT_UAV_SLOT)]_
- L49 _prototype_ `RWStructuredBuffer<IntelExtensionStruct> g_IntelExt : register( u63 )` _[#if !(defined(INTEL_SHADER_EXT_UAV_SLOT))]_
