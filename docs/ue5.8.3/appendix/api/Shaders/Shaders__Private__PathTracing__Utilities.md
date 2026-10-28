# Shaders / Shaders/Private/PathTracing/Utilities

- files: 2; lines: 415
- record kinds: define=8, function=19, include=1, member=4, method=11, method_proto=1, resource=1, struct=2, typedef=1

### `Shaders/Private/PathTracing/Utilities/PathTracingRIS.ush` (Private)

- lines: 46; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L12-38 _struct_ **`FRISContext`** `struct FRISContext`
  - L14 _member_ `float WeightSum;`
  - L15 _member_ `float RandSample;`
  - L17 _method_ `bool Accept(float Weight)`
  - L29 _method_ `bool HasSample()`
  - L34 _method_ `float GetNormalization()`

#### Functions (1)

- L40-45 _function_ `FRISContext InitRISContext(float RandSample)`

### `Shaders/Private/PathTracing/Utilities/PathTracingRandomSequence.ush` (Private)

- lines: 369; parse: all-branches
- includes: L9 `../../MortonCode.ush`

#### Macros (#define, 8)

- L11 `#define RANDSEQ_PURERANDOM 0`
- L12 `#define RANDSEQ_OWENSOBOL 1`
- L13 `#define RANDSEQ_LATTICE 2`
- L17 `#define RANDSEQ RANDSEQ_OWENSOBOL` _[#if !defined(RANDSEQ)]_
- L21 `#define RANDSEQ_RANDOMIZED 1` _[#if !defined(RANDSEQ_RANDOMIZED)]_
- L25 `#define RANDSEQ_ERROR_DIFFUSION 1` _[#if !defined(RANDSEQ_ERROR_DIFFUSION)]_
- L29 `#define RANDSEQ_UNROLL_SOBOL 1` _[#if !defined(RANDSEQ_UNROLL_SOBOL)]_
- L34 `#define RANDSEQ_SFC_TEXTURE 0` _[#if !defined(RANDSEQ_SFC_TEXTURE)]_
- L7 #pragma `once`

#### Structs / classes (1)

- L218-244 _struct_ **`FRandomSequence`** `struct FRandomSequence` — A simple struct that encapsulates a random number sequence (extensible in dimension) Once you create the struct, you can draw samples in the unit square (as either floats or bits) in any dimension from 1 to 4. If you need more dimensions, you can repeat the calls, which will be guaranteed to be statistically independent from the previous However the values from a single call (Get1D(), Get2D(), etc ...) should have nice stratification properties If you need to draw N samples for a pixel, you need to create the struct N times.
  - L220 _member_ `uint SampleIndex;` — index into the random sequence
  - L221 _member_ `uint SampleSeed;` — changes as we draw samples to reflect the change in dimension
  - L226 _method_ `uint Get1DBits()` — Return a random value in [0,2^32)^d All functions rely on the 4D variant and we rely on compiler to optimize out the dead code This also guarantees that the sequence will not "shift" if you change a call from one dimension to another because the seed will be changed in a consistent way in all cases
  - L227 _method_ `uint2 Get2DBits()`
  - L228 _method_ `uint3 Get3DBits()`
  - L229 _method_ `uint4 Get4DBits()`
  - L236 _method_ `float Get1D()` — Convert the random value in [0,2^32)^d to a uniformly distributed float in [0,1)^d, taking care not to skew the distribution due to the non-uniform spacing of floats. Use the upper 24 bits to preserve the good properties of low-discrenpancy samplers. The floating point constant is 2^-24 (would be more nicely expressed with hex-floats which are not yet supported in HLSL) The implicit int to float cast here is guaranteed to be lossless because float can represent integers up to 2^24 exactly
  - L237 _method_ `float2 Get2D()`
  - L238 _method_ `float3 Get3D()`
  - L239 _method_ `float4 Get4D()`
  - L243 _method_proto_ `FRandomSequence Split(uint Index, uint Num)` — Split the path into Num entries. The RandomSequence object returned can be used to keep sampling along the "Index" branch of the split Index must be a value in [0,Num), Num should be >0

#### Global resources (textures / buffers / samplers) (1)

- L112 _resource_ `Texture2D<uint> RandomSequenceSpaceFillingCurve;` _[#if RANDSEQ_SFC_TEXTURE == 1]_

#### typedef / using (1)

- L339 _typedef_ `typedef FRandomSequence RandomSequence;` — Legacy API - wrappers around the more convenient calls above, but kept for back-compatiblity Deprecated (5.7)

#### Functions (18)

- L38-50 _function_ `uint PerfectIntegerHash(uint x)` — This hash mixes bits at the theoretical bias limit
- L53-64 _function_ `uint StrongIntegerHash(uint x)` — High quality integer hash - this mixes bits almost perfectly
- L67-78 _function_ `float Halton(uint Index, uint Base)` — Base must be a prime number
- L80-101 _function_ `uint FastOwenScramblingCore(uint Index, uint Seed)`
- L103-109 _function_ `uint FastOwenScrambling(uint Index, uint Seed)`
- L116-120 _function_ `uint SFCInverse(uint X, uint Y, int NumBits)` _[#if RANDSEQ_SFC_TEXTURE == 1]_
- L126-138 _function_ `uint SFCInverse(uint X, uint Y, int NumBits)` — Given a point (X,Y) on the unit square [0,2^B)^2, return the index along the hilbert curve in [0,2^2B) Because this function only loops over the bits it uses, there is no need to mask out bits beyond the bit count, the pattern will simply tile. This is meant to be a fallback if you don't want/need to pass in the space filling curve texture. _[#if !(RANDSEQ_SFC_TEXTURE == 1)]_
- L141-148 _function_ `uint EvolveSobolSeed(inout uint Seed)`
- L150-211 _function_ `uint4 SamplerCore(uint SampleIndex, inout uint Seed)`
- L249-270 _function_ `FRandomSequence RandomSequenceCreate(uint PositionSeed, uint FrameIndex)` — This initializes a multi-dimensional sampler for a particular pixel. The FrameIndex parameter should be set such that it changes per sample. See the function below when you know how many samples you plan on taking for a particular integral.
- L276-320 _function_ `FRandomSequence RandomSequenceCreate(uint3 PixelCoordAndFrame, uint SampleIndex, uint MaxSamples)` — This is an alternative initialization to the method above when you know how many samples you are planning on taking. This incorporates the TimeSeed0 (this should usually be the frame number when using all samples in one frame, or should be the frame on which the first sample was taken if taking one sample per frame like the path tracer).
- L322-334 _function_ `FRandomSequence FRandomSequence::Split(uint Index, uint Num)` (scope `FRandomSequence`)
- L340-343 _function_ `void RandomSequence_Initialize(inout RandomSequence RandSequence, uint PositionSeed, uint FrameIndex)`
- L345-348 _function_ `void RandomSequence_Initialize(inout RandomSequence RandSequence, uint2 PixelCoord, uint SampleIndex, uint FrameIndex, uint MaxSamples)`
- L350-353 _function_ `float RandomSequence_GenerateSample1D(inout RandomSequence RandSequence)`
- L355-358 _function_ `float2 RandomSequence_GenerateSample2D(inout RandomSequence RandSequence)`
- L360-363 _function_ `float3 RandomSequence_GenerateSample3D(inout RandomSequence RandSequence)`
- L365-368 _function_ `float4 RandomSequence_GenerateSample4D(inout RandomSequence RandSequence)`
