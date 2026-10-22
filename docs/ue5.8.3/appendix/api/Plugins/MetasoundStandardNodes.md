# Plugins / MetasoundStandardNodes

- module root: `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes`
- headers: 20; symbols: 451
- symbol kinds: class=22, enum=4, enumerator=15, externvar=17, function=182, macro=11, member=73, namespace=29, prototype=54, struct=19, typedef=25
- PrivateDependencyModuleNames: CoreUObject, MetasoundGraphCore
- PublicDependencyModuleNames: AudioExtensions, Core, MetasoundFrontend, Serialization, SignalProcessing

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Private/MetasoundOscillators.h` (Private)


#### enum `Metasound::ELfoWaveshapeType`  
`enum class ELfoWaveshapeType`  
_L12-18_
- L14 _public enumerator_ `Sine`
- L15 _public enumerator_ `Saw`
- L16 _public enumerator_ `Triangle`
- L17 _public enumerator_ `Square`

#### struct `Metasound::Generators::FGeneratorArgs`  
`struct FGeneratorArgs`  
_L30-39_
- desc: Standard params passed to the Generate Block templates below
- L32 _public member_ `float SampleRate = 0.f;`
- L33 _public member_ `float FrequencyHz = 0.f;`
- L34 _public member_ `float GlideEaseFactor = 0.0f;`
- L35 _public member_ `float PulseWidth = 0.f;`
- L36 _public member_ `bool BiPolar = true;`
- L37 _public member_ `TArrayView<float> AlignedBuffer;`
- L38 _public member_ `TArrayView<const float> FM;`

#### struct `Metasound::Generators::FWrapPhase`  
`struct FWrapPhase`  
_L42-56_
- desc: Functor used when we need to wrap the phase of some of the oscillators. Sinf for example does not care
- L44 _public function_ `FORCEINLINE void operator()(float& InPhase) const`

#### struct `Metasound::Generators::FPhaseLetClimb`  
`struct FPhaseLetClimb`  
_L59-62_
- desc: Functor that does nothing to the phase and lets it climb indefinitely
- L61 _public function_ `FORCEINLINE void operator()(const float&) const`

#### struct `Metasound::Generators::TGenerateBlock`  
`struct TGenerateBlock`  
_L95-190_
- L97 _public member_ `float Phase = 0.f;`
- L98 _public member_ `Oscillator Osc;`
- L99 _public member_ `PhaseWrap Wrap;`
- L100 _public member_ `float CurrentFreq = -1.f;`
- L102 _public function_ `void operator()(const FGeneratorArgs& InArgs)`

#### struct `Metasound::Generators::TGenerateBlockFM`  
`struct TGenerateBlockFM`  
_L198-304_
- L200 _public member_ `float Phase = 0.f;`
- L201 _public member_ `Oscillator Osc;`
- L202 _public member_ `PhaseWrap Wrap;`
- L204 _public member_ `float CurrentFreq = -1.f;`
- L206 _public function_ `void operator()(const FGeneratorArgs& InArgs)`

#### struct `Metasound::Generators::FSinfGenerator`  
`struct FSinfGenerator`  
_L307-313_
- desc: Sine types and generators.
- L309 _public function_ `FORCEINLINE float operator()(float InPhase, float, const FGeneratorArgs&)`

#### struct `Metasound::Generators::FBhaskaraGenerator`  
`struct FBhaskaraGenerator`  
_L314-323_
- L316 _public function_ `FORCEINLINE float operator()(float InPhase, float, const FGeneratorArgs&) const`

#### struct `Metasound::Generators::FSineWaveTableGenerator`  
`struct FSineWaveTableGenerator`  
_L324-359_
- L326 _public function_ `static const TArray<float>& GetWaveTable()`
- L347 _public function_ `float operator()(float InPhase, float, const FGeneratorArgs&) const`

#### struct `Metasound::Generators::F2DRotatorGenerateBlock`  
`struct F2DRotatorGenerateBlock`  
_L361-375_
- L363 _public member_ `Audio::FSinOsc2DRotation Rotator;`
- L364 _public function_ `F2DRotatorGenerateBlock(float InStartingLinearPhase) : Rotator`
- L367 _public function_ `void operator()(const FGeneratorArgs& Args)`

#### struct `Metasound::Generators::FSawGenerator`  
`struct FSawGenerator`  
_L387-393_
- desc: Saws.
- L389 _public function_ `FORCEINLINE float operator()(float InPhase, float, const FGeneratorArgs&)`

#### struct `Metasound::Generators::FSawPolySmoothGenerator`  
`struct FSawPolySmoothGenerator`  
_L394-405_
- L396 _public function_ `FORCEINLINE float operator()(float InPhase, float InPhaseDelta, const FGeneratorArgs&)`

#### struct `Metasound::Generators::FSquareGenerator`  
`struct FSquareGenerator`  
_L414-422_
- desc: Square.
- L416 _public function_ `FORCEINLINE float operator()(float InPhase, float InPhaseDelta, const FGeneratorArgs& InArgs)`

#### struct `Metasound::Generators::FSquarePolysmoothGenerator`  
`struct FSquarePolysmoothGenerator`  
_L423-469_
- L425 _public function_ `float operator()(float InPhase, float InPhaseDelta, const FGeneratorArgs& InArgs)`

#### struct `Metasound::Generators::FTriangleGenerator`  
`struct FTriangleGenerator`  
_L478-486_
- desc: Triangle.
- L480 _public function_ `FORCEINLINE float operator()(float InPhase, float InPhaseDelta, const FGeneratorArgs& InArgs)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L27 _namespace_ `namespace Generators` (scope `Metasound`)
- L67 _function_ `FORCEINLINE float PolySmoothSaw(const float InPhase, const float InPhaseDelta)` (scope `Metasound::Generators`) — Smooth out the edges of the saw based on its current frequency using a polynomial to smooth it at the discontinuity. This limits aliasing by avoiding the infinite frequency at the discontinuity.
- L329 _function_ `` (scope `Metasound::Generators::FSineWaveTableGenerator::GetWaveTable`)
- L377 _typedef_ `using FSinf = TGenerateBlock<FSinfGenerator>;` (scope `Metasound::Generators`)
- L378 _typedef_ `using FSinfWithFm = TGenerateBlockFM<FSinfGenerator>;` (scope `Metasound::Generators`)
- L380 _typedef_ `using FBhaskara = TGenerateBlock<FBhaskaraGenerator>;` (scope `Metasound::Generators`)
- L381 _typedef_ `using FBhaskaraWithFm = TGenerateBlockFM<FBhaskaraGenerator>;` (scope `Metasound::Generators`)
- L383 _typedef_ `using FSineWaveTable = TGenerateBlock<FSineWaveTableGenerator>;` (scope `Metasound::Generators`)
- L384 _typedef_ `using FSineWaveTableWithFm = TGenerateBlockFM<FSineWaveTableGenerator>;` (scope `Metasound::Generators`)
- L407 _typedef_ `using FSaw = TGenerateBlock<FSawGenerator>;` (scope `Metasound::Generators`)
- L408 _typedef_ `using FSawWithFm = TGenerateBlockFM<FSawGenerator>;` (scope `Metasound::Generators`)
- L410 _typedef_ `using FSawPolysmooth = TGenerateBlock<FSawPolySmoothGenerator>;` (scope `Metasound::Generators`)
- L411 _typedef_ `using FSawPolysmoothWithFm = TGenerateBlockFM<FSawPolySmoothGenerator>;` (scope `Metasound::Generators`)
- L471 _typedef_ `using FSquare = TGenerateBlock<FSquareGenerator>;` (scope `Metasound::Generators`)
- L472 _typedef_ `using FSquareWithFm = TGenerateBlockFM<FSquareGenerator>;` (scope `Metasound::Generators`)
- L474 _typedef_ `using FSquarePolysmooth = TGenerateBlock<FSquarePolysmoothGenerator>;` (scope `Metasound::Generators`)
- L475 _typedef_ `using FSquarePolysmoothWithFm = TGenerateBlockFM<FSquarePolysmoothGenerator>;` (scope `Metasound::Generators`)
- L488 _typedef_ `using FTriangle = TGenerateBlock<FTriangleGenerator>;` (scope `Metasound::Generators`)
- L489 _typedef_ `using FTriangleWithFm = TGenerateBlockFM<FTriangleGenerator>;` (scope `Metasound::Generators`)
- L492 _typedef_ `using FTrianglePolysmooth = TGenerateBlock<FTriangleGenerator>;` (scope `Metasound::Generators`) — TODO: make a true polysmooth version
- L493 _typedef_ `using FTrianglePolysmoothWithFm = TGenerateBlockFM<FTriangleGenerator>;` (scope `Metasound::Generators`)

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundAudioFormats.h` (Public)


#### class `Metasound::FMultichannelAudioFormat`  
`class FMultichannelAudioFormat : public IAudioDataType`  
_L23-115_
- inherits: `IAudioDataType`
- desc: FMultichannelAudioFormat FMultichannelAudioFormat represents deinterleaved multichannel audio which supports a constant number of channels for the lifetime of the object. The audio buffers in FMultichannelAudioFormat are shared data references which can be accessed outside of the FMultichannelAudioFormat. All audio buffers within a FMultichannelAudioFormat object must contain the same number of audio frames.
- L26 _public prototype_ `FMultichannelAudioFormat();`
- L33 _public prototype_ `FMultichannelAudioFormat(int32 InNumFrames, int32 InNumChannels);` — FMultichannelAudioFormat Constructor. @param InNumFrames - The number of frames per an audio buffer. @param InNumChannels - The number of audio channels.
- L41 _public prototype_ `explicit FMultichannelAudioFormat(const FOperatorSettings& InSettings, int32 InNumChannels);` — FMultichannelAudioFormat Constructor used by the metasound frontend. @param InSettings - Operator Settings passed in on construction. @param InNumChannels - initial number of audio channels.
- L50 _public prototype_ `FMultichannelAudioFormat(TArrayView<const FAudioBufferWriteRef> InWriteRefs);` — FMultichannelAudioFormat Constructor. This constructor accepts an array of writable audio buffer references. Each buffer in the array must contain equal number of frames. @param InWriteRefs - An array of writable audio buffer references.
- L53 _public prototype_ `FMultichannelAudioFormat(const FMultichannelAudioFormat& InOther) = default;` — Enable the copy constructor.
- L59 _public prototype_ `FMultichannelAudioFormat& operator=(const FMultichannelAudioFormat& Other) = delete;` — Disable equal operator so channel count does not change
- L65 _public function_ `int32 GetNumChannels() const` — Return the number of audio channels.
- L68 _public function_ `int32 GetMaxNumChannels() const` — Return the maximum number of channels. Multichannel audio buffers cannot be resized after construction.
- L74 _public function_ `const TArrayView<const FAudioBufferReadRef> GetBuffers() const` — Return an array view of the readable buffer references. This array will have GetNumChannels() elements.
- L80 _public function_ `const TArrayView<const FAudioBufferWriteRef> GetBuffers()` — Return an array view of the writable buffer references. This array will have GetNumChannels() elements.
- L86 _public function_ `const TArray<FAudioBufferReadRef>& GetStorage() const` — Return an array of the readable buffer reference storage. This array will have GetNumChannels() elements.
- L92 _public function_ `const TArray<FAudioBufferWriteRef>& GetStorage()` — Return an array of the writable buffer reference storage. This array will have GetNumChannels() elements.
- L106 _private prototype_ `FMultichannelAudioFormat(TArrayView<const FAudioBufferReadRef> InReadRefs);` — Construct a FMultichannelAudioFormat with an array of readable buffers. This constructor should only be used when it can be assured that the constructed object will not provide writable access to the passed in audio buffers.
- L108 _private member_ `int32 NumChannels;`
- L110 _private member_ `TArrayView<const FAudioBufferWriteRef> WritableBuffers;`
- L111 _private member_ `TArrayView<const FAudioBufferReadRef> ReadableBuffers;`
- L113 _private member_ `TArray<FAudioBufferWriteRef> WritableBufferStorage;`
- L114 _private member_ `TArray<FAudioBufferReadRef> ReadableBufferStorage;`

#### class `Metasound::TStaticChannelAudioFormat`  
`template<int32 TNumChannels> class TStaticChannelAudioFormat : public IAudioDataType`  
_L128-256_
- inherits: `IAudioDataType`
- desc: A TStaticChannelAudioFormat represents deinterleaved multichannel audio where the number of channels is known at compile time. This is primarily useful to define such cases as Stereo, Mono, Qaud, 5.1, etc. The audio buffers in FMultichannelAudioFormat are shared data references which can be accessed outside of the FMultichannelAudioFormat. All audio buffers within a FMultichannelAudioFormat object must contain the same number of audio frames.
- L131 _public member_ `static constexpr int32 NumChannels = TNumChannels;`
- L137 _public function_ `TStaticChannelAudioFormat(int32 InNumFrames)` — TStaticChannelAudioFormat Constructor @param InNumFrames - The number of frames per an audio buffer.
- L156 _public function_ `TStaticChannelAudioFormat(const FOperatorSettings& InOperatorSettings) : TStaticChannelAudioFormat(InOperatorSettings.GetNumFramesPerBlock())`
- L163 _public function_ `int32 GetNumChannels() const` — Return the number of audio channels.
- L169 _public function_ `int32 GetMaxNumChannels() const` — Return the maximum number of channels. static channel audio buffers cannot be resized after construction.
- L173 _public function_ `template<int32 ChannelIndex> FAudioBufferReadRef GetBuffer() const` — Return an readable buffer reference for a specific channel.
- L183 _public function_ `template<int32 ChannelIndex> FAudioBufferWriteRef GetBuffer()` — Return an writable buffer reference for a specific channel.
- L195 _public function_ `const TArrayView<FAudioBufferReadRef> GetBuffers() const` — Return an array view of the readable buffer references. This array will have GetNumChannels() elements.
- L204 _public function_ `const TArrayView<FAudioBufferWriteRef> GetBuffers()` — Return an array view of the writable buffer references. This array will have GetNumChannels() elements.
- L213 _public function_ `const TArray<FAudioBufferReadRef> GetStorage() const` — Return an array of the readable buffer references. This array will have GetNumChannels() elements.
- L222 _public function_ `const TArray<FAudioBufferWriteRef> GetStorage()` — Return an array of the writable buffer references. This array will have GetNumChannels() elements.
- L230 _protected function_ `TStaticChannelAudioFormat(const FAudioBufferWriteRef(&InBuffers)[NumChannels])` — TStaticChannelAudioFormat constructor with an array of writable buffers.
- L251 _private member_ `TArrayView<FAudioBufferWriteRef> WritableBuffers;`
- L252 _private member_ `TArrayView<FAudioBufferReadRef> ReadableBuffers;`
- L254 _private member_ `TArray<FAudioBufferWriteRef> WritableBufferStorage;`
- L255 _private member_ `TArray<FAudioBufferReadRef> ReadableBufferStorage;`

#### class `Metasound::FMonoAudioFormat`  
`class FMonoAudioFormat : public TStaticChannelAudioFormat<1>`  
_L263-287_
- inherits: `TStaticChannelAudioFormat<1>`
- desc: FMonoAudioFormat represents mono audio containing one channel of audio. The audio buffer is a shared data references which can be accessed outside of the FMonoAudioFormat.
- L266 _public typedef_ `using Super = TStaticChannelAudioFormat<1>;`
- L277 _public function_ `FMonoAudioFormat(const FAudioBufferWriteRef& InAudio) : Super({InAudio})` — FMonoAudioFormat Construtor Construct with a single writable audio buffer reference. @param InAudio - A writable audio buffer reference.
- L283 _public function_ `FAudioBufferWriteRef GetCenter()` — Return writable audio buffer reference of center channel.
- L286 _public function_ `FAudioBufferReadRef GetCenter() const` — Return readable audio buffer reference of center channel.

#### class `Metasound::FStereoAudioFormat`  
`class FStereoAudioFormat : public TStaticChannelAudioFormat<2>`  
_L296-327_
- inherits: `TStaticChannelAudioFormat<2>`
- desc: FStereoAudioFormat represents stereo audio containing two channels of audio. The audio buffers are shared data references which can be accessed outside of the FStereoAudioFormat.
- L299 _public typedef_ `using Super = TStaticChannelAudioFormat<2>;`
- L311 _public function_ `FStereoAudioFormat(const FAudioBufferWriteRef& InLeftAudio, const FAudioBufferWriteRef& InRightAudio) : Super({InLeftAudio, InRightAudio})` — FStereoAudioFormat Construtor Construct with a two writable audio buffer reference. @param InLeftAudio - A writable audio buffer reference for the left channel. @param InRightAudio - A writable audio buffer reference for the right channel.
- L317 _public function_ `FAudioBufferWriteRef GetLeft()` — Return writable audio buffer reference of left channel.
- L320 _public function_ `FAudioBufferReadRef GetLeft() const` — Return readable audio buffer reference of left channel.
- L323 _public function_ `FAudioBufferWriteRef GetRight()` — Return writable audio buffer reference of right channel.
- L326 _public function_ `FAudioBufferReadRef GetRight() const` — Return readable audio buffer reference of right channel.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDSTANDARDNODES_API`
- L12 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundBPMToSecondsNode.h` (Public)


#### class `Metasound::FBPMToSecondsNode`  
`class FBPMToSecondsNode : public FNodeFacade`  
_L16-27_
- inherits: `FNodeFacade`
- desc: FBPMToSecondsNode Calculates a beat time in seconds from the given BPM, beat multiplier and divisions of a whole note.
- L22 _public prototype_ `FBPMToSecondsNode(const FNodeInitData& InitData);` — Constructor used by the Metasound Frontend.
- L24 _public prototype_ `FBPMToSecondsNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata);`
- L26 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDSTANDARDNODES_API`
- L10 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundEnvelopeFollowerNode.h` (Public)


#### class `Metasound::FEnvelopeFollowerNode`  
`class FEnvelopeFollowerNode : public FNodeFacade`  
_L16-27_
- inherits: `FNodeFacade`
- desc: FEnvelopeFollowerNode Delays an audio buffer by a specified amount.
- L22 _public prototype_ `FEnvelopeFollowerNode(const FNodeInitData& InitData);` — Constructor used by the Metasound Frontend.
- L24 _public prototype_ `FEnvelopeFollowerNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata);`
- L26 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDSTANDARDNODES_API`
- L10 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundEnvelopeFollowerTypes.h` (Public)


#### enum `Metasound::EEnvelopePeakMode`  
`enum class EEnvelopePeakMode`  
_L11-16_
- L13 _public enumerator_ `Peak = 0`
- L14 _public enumerator_ `MeanSquared`
- L15 _public enumerator_ `RootMeanSquared`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundGain.h` (Public)


#### enum `Metasound::EGainRepresentation`  
`enum class UE_DEPRECATED(5.6, "EGainRepresentation is not used and will be removed") EGainRepresentation : uint8`  
_L11-18_
- desc: Representation of a gain
- L14 _public enumerator_ `Linear` — Gain in linear scale
- L17 _public enumerator_ `Decibels` — Gain is in decibels

#### class `Metasound::FGain`  
`class UE_DEPRECATED(5.6, "FGain is not used and will be removed") FGain`  
_L24-123_
- desc: FGain represents a gain value. It provides clearly defined getters and setters as well as several convenience functions for converting gain to decibels.
- L27 _public member_ `static constexpr const float DefaultGain = 1.0f;`
- L30 _public function_ `FGain() : LinearGain(DefaultGain)` — Construct gain of 1
- L42 _public function_ `FGain(float InValue, EGainRepresentation InRep) : LinearGain(DefaultGain)` — Construct a Gain with a given value and representation. @param InValue - The value of the gain at the given representation. @param InRep - The representation of the given value.
- L62 _public function_ `FGain(float InValue) : FGain(InValue, EGainRepresentation::Linear)` — FGain constructor used to pass in float literals from the metasound frontend.
- L68 _public function_ `operator float() const` — Implicit operator used for math operations.
- L73 _public function_ `FGain& operator+=(const FGain& InOther)`
- L79 _public function_ `FGain& operator-=(const FGain& InOther)`
- L85 _public function_ `FGain& operator*=(const FGain& InOther)`
- L91 _public function_ `FGain& operator/=(const FGain& InOther)`
- L98 _public function_ `void SetDecibels(float InDecibels)` — Set the gain in decibels
- L104 _public function_ `float GetDecibels() const` — Get the gain in decibels
- L110 _public function_ `void SetLinear(float InLinearScale)` — Set the gain in LinearScale
- L116 _public function_ `float GetLinear() const` — Return the gain in LinearScale.
- L122 _private member_ `float LinearGain = DefaultGain;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundNoiseGenerator.h` (Public)


#### class `Metasound::FNoiseNode`  
`class FNoiseNode : public FNodeFacade`  
_L13-25_
- inherits: `FNodeFacade`
- L16 _public prototype_ `FNoiseNode(const FVertexName& InName, const FGuid& InInstanceID, int32 InDefaultSeed);`
- L17 _public prototype_ `FNoiseNode(const FNodeInitData& InInitData);`
- L18 _public prototype_ `FNoiseNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata);`
- L21 _public function_ `int32 GetDefaultSeed() const` — `UE_DEPRECATED(5.6, "The default seed is stored on the vertex interface of the node")`
- L23 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METASOUNDSTANDARDNODES_API`
- L11 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundOscillatorNodes.h` (Public)


#### class `Metasound::FOscilatorNodeBase`  
`class FOscilatorNodeBase : public FBasicNode`  
_L22-65_
- inherits: `FBasicNode`
- L25 _protected prototype_ `FOscilatorNodeBase(const FVertexName& InInstanceName, const FGuid& InInstanceID, const FNodeClassMetadata& InInfo, const TSharedRef<IOperatorFactory, ESPMode::ThreadSafe>& InFactory, float InDefaultFrequency, float InDefaultGlideTime, bool bInDefaultEnablement);`
- L26 _protected prototype_ `FOscilatorNodeBase(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InClassMetadata, TSharedRef<IOperatorFactory> InFactory);`
- L29 _protected function_ `float GetDefaultPhaseOffset() const` — `UE_DEPRECATED(5.6, "This function should not be used")`
- L35 _protected function_ `float GetDefaultFrequency() const` — `UE_DEPRECATED(5.6, "This function should not be used")`
- L41 _protected function_ `float GetDefaultGlideFactor() const` — `UE_DEPRECATED(5.6, "This function should not be used")`
- L47 _protected function_ `bool GetDefaultEnablement() const` — `UE_DEPRECATED(5.6, "This function should not be used")`
- L52 _protected function_ `FOperatorFactorySharedRef GetDefaultOperatorFactory() const override`
- L57 _protected member_ `TSharedRef<IOperatorFactory, ESPMode::ThreadSafe> Factory;`
- L58 _protected member_ `FVertexInterface VertexInterface;`
- L61 _private member_ `float DefaultPhaseOffset = 0.f;`
- L62 _private member_ `float DefaultFrequency = 440.f;`
- L63 _private member_ `float DefaultGlideFactor = 0.0f;`
- L64 _private member_ `bool bDefaultEnablement = true;`

#### class `Metasound::FSineOscilatorNode`  
`class FSineOscilatorNode : public FOscilatorNodeBase`  
_L67-79_
- inherits: `FOscilatorNodeBase`
- L73 _public prototype_ `FSineOscilatorNode(const FVertexName& InInstanceName, const FGuid& InInstanceID, float InDefaultFrequency, float InDefautlGlideTime, bool bInDefaultEnablement);` — `UE_DEPRECATED(5.6, "Do not construct oscillators with this function")`
- L75 _public prototype_ `FSineOscilatorNode(const FNodeInitData& InInitData);`
- L76 _public prototype_ `FSineOscilatorNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InMetadata);`
- L78 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### class `Metasound::FSawOscilatorNode`  
`class FSawOscilatorNode : public FOscilatorNodeBase`  
_L81-92_
- inherits: `FOscilatorNodeBase`
- L86 _public prototype_ `FSawOscilatorNode(const FVertexName& InInstanceName, const FGuid& InInstanceID, float InDefaultFrequency, float InDefautlGlideTime, bool bInDefaultEnablement);` — `UE_DEPRECATED(5.6, "Do not construct oscillators with this function")`
- L88 _public prototype_ `FSawOscilatorNode(const FNodeInitData& InInitData);`
- L89 _public prototype_ `FSawOscilatorNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InMetadata);`
- L91 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### class `Metasound::FTriangleOscilatorNode`  
`class FTriangleOscilatorNode : public FOscilatorNodeBase`  
_L94-104_
- inherits: `FOscilatorNodeBase`
- L99 _public prototype_ `FTriangleOscilatorNode(const FVertexName& InInstanceName, const FGuid& InInstanceID, float InDefaultFrequency, float InDefautlGlideTime, bool bInDefaultEnablement);` — `UE_DEPRECATED(5.6, "Do not construct oscillators with this function")`
- L100 _public prototype_ `FTriangleOscilatorNode(const FNodeInitData& InInitData);`
- L101 _public prototype_ `FTriangleOscilatorNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InMetadata);`
- L103 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### class `Metasound::FSquareOscilatorNode`  
`class FSquareOscilatorNode : public FOscilatorNodeBase`  
_L106-116_
- inherits: `FOscilatorNodeBase`
- L111 _public prototype_ `FSquareOscilatorNode(const FVertexName& InInstanceName, const FGuid& InInstanceID, float InDefaultFrequency, float InDefautlGlideTime, bool bInDefaultEnablement);` — `UE_DEPRECATED(5.6, "Do not construct oscillators with this function")`
- L112 _public prototype_ `FSquareOscilatorNode(const FNodeInitData& InInitData);`
- L113 _public prototype_ `FSquareOscilatorNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InMetadata);`
- L115 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### class `Metasound::FLfoNode`  
`class FLfoNode : public FNodeFacade`  
_L118-126_
- inherits: `FNodeFacade`
- L121 _public prototype_ `FLfoNode(const FNodeInitData& InInitData);`
- L122 _public prototype_ `FLfoNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InMetadata);`
- L123 _public prototype_ `virtual ~FLfoNode() = default;`
- L125 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API METASOUNDSTANDARDNODES_API`
- L20 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundRandomNode.h` (Public)


#### struct `Metasound::TRandomNodeSpecialization`  
`template<typename ValueType> struct TRandomNodeSpecialization`  
_L36-39_
- L38 _public member_ `bool bSupported = false;`
- L44 _public function_ `static FName GetClassName()`
- L49 _public function_ `static FText GetDisplayName()`
- L54 _public function_ `static FText GetDescription()`
- L59 _public function_ `static bool HasRange()`
- L64 _public function_ `static int32 GetDefaultMin()`
- L69 _public function_ `static int32 GetDefaultMax()`
- L74 _public function_ `static int32 GetNextValue(FRandomStream& InStream, int32 InMin, int32 InMax)`
- L79 _public function_ `static TDataReadReference<int32> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L85 _public function_ `static TDataReadReference<int32> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L115 _public function_ `static float GetDefaultMin()`
- L120 _public function_ `static float GetDefaultMax()`
- L125 _public function_ `static float GetNextValue(FRandomStream& InStream, float InMin, float InMax)`
- L130 _public function_ `static TDataReadReference<float> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L136 _public function_ `static TDataReadReference<float> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L166 _public function_ `static bool GetDefaultMin()`
- L171 _public function_ `static bool GetDefaultMax()`
- L176 _public function_ `static bool GetNextValue(FRandomStream& InStream, bool, bool)`
- L181 _public function_ `static TDataReadReference<bool> CreateMinValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L186 _public function_ `static TDataReadReference<bool> CreateMaxValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L226 _public function_ `static FTime GetNextValue(FRandomStream& InStream, FTime InMin, FTime InMax)`
- L232 _public function_ `static TDataReadReference<FTime> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L238 _public function_ `static TDataReadReference<FTime> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`

#### struct `Metasound::TRandomNodeSpecialization`  
`template<> struct TRandomNodeSpecialization<int32>`  
_L42-90_
- L38 _public member_ `bool bSupported = false;`
- L44 _public function_ `static FName GetClassName()`
- L49 _public function_ `static FText GetDisplayName()`
- L54 _public function_ `static FText GetDescription()`
- L59 _public function_ `static bool HasRange()`
- L64 _public function_ `static int32 GetDefaultMin()`
- L69 _public function_ `static int32 GetDefaultMax()`
- L74 _public function_ `static int32 GetNextValue(FRandomStream& InStream, int32 InMin, int32 InMax)`
- L79 _public function_ `static TDataReadReference<int32> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L85 _public function_ `static TDataReadReference<int32> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L115 _public function_ `static float GetDefaultMin()`
- L120 _public function_ `static float GetDefaultMax()`
- L125 _public function_ `static float GetNextValue(FRandomStream& InStream, float InMin, float InMax)`
- L130 _public function_ `static TDataReadReference<float> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L136 _public function_ `static TDataReadReference<float> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L166 _public function_ `static bool GetDefaultMin()`
- L171 _public function_ `static bool GetDefaultMax()`
- L176 _public function_ `static bool GetNextValue(FRandomStream& InStream, bool, bool)`
- L181 _public function_ `static TDataReadReference<bool> CreateMinValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L186 _public function_ `static TDataReadReference<bool> CreateMaxValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L226 _public function_ `static FTime GetNextValue(FRandomStream& InStream, FTime InMin, FTime InMax)`
- L232 _public function_ `static TDataReadReference<FTime> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L238 _public function_ `static TDataReadReference<FTime> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`

#### struct `Metasound::TRandomNodeSpecialization`  
`template<> struct TRandomNodeSpecialization<float>`  
_L93-141_
- L38 _public member_ `bool bSupported = false;`
- L44 _public function_ `static FName GetClassName()`
- L49 _public function_ `static FText GetDisplayName()`
- L54 _public function_ `static FText GetDescription()`
- L59 _public function_ `static bool HasRange()`
- L64 _public function_ `static int32 GetDefaultMin()`
- L69 _public function_ `static int32 GetDefaultMax()`
- L74 _public function_ `static int32 GetNextValue(FRandomStream& InStream, int32 InMin, int32 InMax)`
- L79 _public function_ `static TDataReadReference<int32> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L85 _public function_ `static TDataReadReference<int32> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L115 _public function_ `static float GetDefaultMin()`
- L120 _public function_ `static float GetDefaultMax()`
- L125 _public function_ `static float GetNextValue(FRandomStream& InStream, float InMin, float InMax)`
- L130 _public function_ `static TDataReadReference<float> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L136 _public function_ `static TDataReadReference<float> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L166 _public function_ `static bool GetDefaultMin()`
- L171 _public function_ `static bool GetDefaultMax()`
- L176 _public function_ `static bool GetNextValue(FRandomStream& InStream, bool, bool)`
- L181 _public function_ `static TDataReadReference<bool> CreateMinValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L186 _public function_ `static TDataReadReference<bool> CreateMaxValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L226 _public function_ `static FTime GetNextValue(FRandomStream& InStream, FTime InMin, FTime InMax)`
- L232 _public function_ `static TDataReadReference<FTime> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L238 _public function_ `static TDataReadReference<FTime> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`

#### struct `Metasound::TRandomNodeSpecialization`  
`template<> struct TRandomNodeSpecialization<bool>`  
_L144-190_
- L38 _public member_ `bool bSupported = false;`
- L44 _public function_ `static FName GetClassName()`
- L49 _public function_ `static FText GetDisplayName()`
- L54 _public function_ `static FText GetDescription()`
- L59 _public function_ `static bool HasRange()`
- L64 _public function_ `static int32 GetDefaultMin()`
- L69 _public function_ `static int32 GetDefaultMax()`
- L74 _public function_ `static int32 GetNextValue(FRandomStream& InStream, int32 InMin, int32 InMax)`
- L79 _public function_ `static TDataReadReference<int32> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L85 _public function_ `static TDataReadReference<int32> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L115 _public function_ `static float GetDefaultMin()`
- L120 _public function_ `static float GetDefaultMax()`
- L125 _public function_ `static float GetNextValue(FRandomStream& InStream, float InMin, float InMax)`
- L130 _public function_ `static TDataReadReference<float> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L136 _public function_ `static TDataReadReference<float> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L166 _public function_ `static bool GetDefaultMin()`
- L171 _public function_ `static bool GetDefaultMax()`
- L176 _public function_ `static bool GetNextValue(FRandomStream& InStream, bool, bool)`
- L181 _public function_ `static TDataReadReference<bool> CreateMinValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L186 _public function_ `static TDataReadReference<bool> CreateMaxValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L226 _public function_ `static FTime GetNextValue(FRandomStream& InStream, FTime InMin, FTime InMax)`
- L232 _public function_ `static TDataReadReference<FTime> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L238 _public function_ `static TDataReadReference<FTime> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`

#### struct `Metasound::TRandomNodeSpecialization`  
`template<> struct TRandomNodeSpecialization<FTime>`  
_L193-243_
- L38 _public member_ `bool bSupported = false;`
- L44 _public function_ `static FName GetClassName()`
- L49 _public function_ `static FText GetDisplayName()`
- L54 _public function_ `static FText GetDescription()`
- L59 _public function_ `static bool HasRange()`
- L64 _public function_ `static int32 GetDefaultMin()`
- L69 _public function_ `static int32 GetDefaultMax()`
- L74 _public function_ `static int32 GetNextValue(FRandomStream& InStream, int32 InMin, int32 InMax)`
- L79 _public function_ `static TDataReadReference<int32> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L85 _public function_ `static TDataReadReference<int32> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L115 _public function_ `static float GetDefaultMin()`
- L120 _public function_ `static float GetDefaultMax()`
- L125 _public function_ `static float GetNextValue(FRandomStream& InStream, float InMin, float InMax)`
- L130 _public function_ `static TDataReadReference<float> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L136 _public function_ `static TDataReadReference<float> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L166 _public function_ `static bool GetDefaultMin()`
- L171 _public function_ `static bool GetDefaultMax()`
- L176 _public function_ `static bool GetNextValue(FRandomStream& InStream, bool, bool)`
- L181 _public function_ `static TDataReadReference<bool> CreateMinValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L186 _public function_ `static TDataReadReference<bool> CreateMaxValueRef(const FInputVertexInterfaceData&, const FOperatorSettings&)`
- L226 _public function_ `static FTime GetNextValue(FRandomStream& InStream, FTime InMin, FTime InMax)`
- L232 _public function_ `static TDataReadReference<FTime> CreateMinValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`
- L238 _public function_ `static TDataReadReference<FTime> CreateMaxValueRef(const FInputVertexInterfaceData& InputData, const FOperatorSettings& InOperatorSettings)`

#### class `Metasound::TRandomNodeOperator`  
`template<typename ValueType> class TRandomNodeOperator : public TExecutableOperator<TRandomNodeOperator<ValueType>>`  
_L248-497_
- inherits: `TExecutableOperator<TRandomNodeOperator<ValueType>>`
- L251 _public member_ `static constexpr int32 DefaultSeed = -1;`
- L253 _public function_ `static const FVertexInterface& GetDefaultInterface()`
- L295 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L317 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L342 _public function_ `TRandomNodeOperator(const FOperatorSettings& InSettings, TDataReadReference<FTrigger> InNextTrigger, TDataReadReference<FTrigger> InResetTrigger, TDataReadReference<int32> InSeedValue, TDataReadReference<ValueType> InMinValue, TDataReadReference<ValueType> InMaxValue) : NextTrigger(InNextTrigger) , ResetTrigger(InResetTrigger) , SeedValue(InSeedValue) , MinValue(InMinValue) , MaxValue(InMaxValue) , TriggerOutOnNext(FTriggerWriteRef::CreateNew(InSettings)) , TriggerOutOnReset(FTriggerWriteRef::CreateNew(InSettings)) , OutputValue(TDataWriteReferenceFactory<ValueType>::CreateAny(InSettings)) , bIsDefaultSeeded(*SeedValue == DefaultSeed) , bIsRandomStreamInitialized(false)`
- L362 _public function_ `TRandomNodeOperator(const FOperatorSettings& InSettings, TDataReadReference<FTrigger> InNextTrigger, TDataReadReference<FTrigger> InResetTrigger, TDataReadReference<int32> InSeedValue) : NextTrigger(InNextTrigger) , ResetTrigger(InResetTrigger) , SeedValue(InSeedValue) , MinValue(TDataReadReference<ValueType>::CreateNew())`
- L380 _public prototype_ `virtual ~TRandomNodeOperator() = default;`
- L383 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L400 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L408 _public function_ `void Execute()`
- L441 _public function_ `void Reset(const IOperator::FResetParams& InParams)` — Externally visible initialize function
- L447 _private function_ `void ResetInternal()`
- L461 _private function_ `void EvaluateSeedChanges()`
- L484 _private member_ `FTriggerReadRef NextTrigger;`
- L485 _private member_ `FTriggerReadRef ResetTrigger;`
- L486 _private member_ `FInt32ReadRef SeedValue;`
- L487 _private member_ `TDataReadReference<ValueType> MinValue;`
- L488 _private member_ `TDataReadReference<ValueType> MaxValue;`
- L490 _private member_ `FTriggerWriteRef TriggerOutOnNext;`
- L491 _private member_ `FTriggerWriteRef TriggerOutOnReset;`
- L492 _private member_ `TDataWriteReference<ValueType> OutputValue;`
- L494 _private member_ `FRandomStream RandomStream;`
- L495 _private member_ `bool bIsDefaultSeeded = false;`
- L496 _private member_ `bool bIsRandomStreamInitialized = false;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundStandardNodes"`
- L20 _namespace_ `namespace Metasound`
- L22 _namespace_ `namespace RandomNodeNames` (scope `Metasound`)
- L298 _function_ `` (scope `Metasound::TRandomNodeOperator::GetNodeInfo`)
- L415 _function_ `` (scope `Metasound::TRandomNodeOperator::Execute`)
- L504 _typedef_ `template<typename ValueType> using TRandomNode = TNodeFacade<TRandomNodeOperator<ValueType>>;` (scope `Metasound`) — TRandomNode Generates a random float value when triggered.

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundSampleCounter.h` (Public)


#### class `Metasound::FSampleCounter`  
`class FSampleCounter`  
_L15-335_
- L18 _private member_ `FSampleCount NumSamples = 0;`
- L21 _private member_ `FSampleRate SampleRate = 1;` — Must be non-zero
- L24 _public function_ `FSampleCounter()`
- L28 _public function_ `FSampleCounter(const FSampleCounter& InSampleCounter) : NumSamples(InSampleCounter.NumSamples) , SampleRate(InSampleCounter.SampleRate)`
- L34 _public function_ `FSampleCounter(FSampleCount InNumSamples, FSampleRate InSampleRate) : NumSamples(InNumSamples) , SampleRate(InSampleRate)`
- L47 _public function_ `static FSampleCounter FromTime(const FTime& InTime, FSampleRate InSampleRate)` — Construct a sample counter with a sample count, time resolution, and sample rate. @param InTime - The initial time value. @param InSampleRate - The sample rate associated with this time object.
- L56 _public function_ `void SetSampleRate(FSampleRate InSampleRate)` — Set the sample rate of this object without changing the number of samples. This will result in the object representing a different amount of time.
- L67 _public function_ `FSampleRate GetSampleRate() const` — Returns sample rate
- L72 _public function_ `FTime ToTime() const`
- L78 _public function_ `FSampleCount GetNumSamples() const` — Return the number of samples.
- L89 _public function_ `FSampleCount GetNumSamples(FSampleRate InOtherSampleRate) const` — Return the number of samples which represent this time duration using a different sample rate. @param InOtherSampleRate - Sample rate to use when calculating the number of samples.
- L102 _public function_ `void SetNumSamples(const FTime& InTime)` — Set the number of samples from time value (This is functionally discretization and will result in loss of precision)
- L108 _public function_ `void SetNumSamples(FSampleCount InNumSamples)` — Set the number of samples.
- L113 _public function_ `FSampleCounter& operator=(const FSampleCounter& InRHS)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L12 _typedef_ `using FSampleCount = int64;` (scope `Metasound`)
- L120 _function_ `friend FSampleCounter& operator+=(FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L126 _function_ `friend FSampleCounter& operator+=(FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L132 _function_ `friend FSampleCounter& operator-=(FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L138 _function_ `friend FSampleCounter& operator-=(FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L144 _function_ `friend FSampleCounter operator+(const FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L149 _function_ `friend FSampleCounter operator+(const FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L154 _function_ `friend FSampleCounter operator-(const FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L159 _function_ `friend FSampleCounter operator-(const FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L165 _function_ `template<typename IntegralType> friend FSampleCounter operator+(const FSampleCounter& InLHS, const IntegralType& InRHS)` (scope `Metasound`)
- L172 _function_ `template<typename IntegralType> friend FSampleCounter operator-(const FSampleCounter& InLHS, const IntegralType& InRHS)` (scope `Metasound`)
- L179 _function_ `template<typename ArithmeticType> friend FSampleCounter operator*(const FSampleCounter& InLHS, const ArithmeticType& InRHS)` (scope `Metasound`)
- L186 _function_ `template<typename ArithmeticType> friend FSampleCounter operator*(const ArithmeticType& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L193 _function_ `template<typename ArithmeticType> friend FSampleCounter operator/(const FSampleCounter& InLHS, ArithmeticType InRHS)` (scope `Metasound`)
- L200 _function_ `template<typename ArithmeticType> friend ArithmeticType& operator/(ArithmeticType InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L207 _function_ `template<typename ArithmeticType> friend FSampleCounter& operator*=(FSampleCounter& InLHS, ArithmeticType InRHS)` (scope `Metasound`)
- L215 _function_ `template<typename ArithmeticType> friend FSampleCounter& operator/=(FSampleCounter& InLHS, ArithmeticType InRHS)` (scope `Metasound`)
- L223 _function_ `template<typename ArithmeticType> friend ArithmeticType& operator/=(ArithmeticType& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L231 _function_ `template<typename IntegralType> friend FSampleCounter operator+=(FSampleCounter& InLHS, const IntegralType& InRHS)` (scope `Metasound`)
- L239 _function_ `template<typename IntegralType> friend FSampleCounter& operator-=(FSampleCounter& InLHS, const IntegralType& InRHS)` (scope `Metasound`)
- L246 _function_ `friend bool operator<(const FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L251 _function_ `friend bool operator<(const FTime& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L256 _function_ `friend bool operator<(const FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L261 _function_ `friend bool operator>(const FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L266 _function_ `friend bool operator>(const FTime& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L271 _function_ `friend bool operator>(const FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L276 _function_ `friend bool operator<=(const FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L281 _function_ `friend bool operator<=(const FTime& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L286 _function_ `friend bool operator<=(const FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L291 _function_ `friend bool operator>=(const FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L296 _function_ `friend bool operator>=(const FTime& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L301 _function_ `friend bool operator>=(const FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L306 _function_ `friend bool operator==(const FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L311 _function_ `friend bool operator==(const FTime& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L316 _function_ `friend bool operator==(const FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L321 _function_ `friend bool operator!=(const FSampleCounter& InLHS, const FTime& InRHS)` (scope `Metasound`)
- L326 _function_ `friend bool operator!=(const FTime& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)
- L331 _function_ `friend bool operator!=(const FSampleCounter& InLHS, const FSampleCounter& InRHS)` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundScaleEnums.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundStandardNodesCategories.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`
- L8 _namespace_ `namespace NodeCategories` (scope `Metasound`)
- L10 _externvar_ `extern const FText Debug;` (scope `Metasound::NodeCategories`)
- L11 _externvar_ `extern const FText Delays;` (scope `Metasound::NodeCategories`)
- L12 _externvar_ `extern const FText Dynamics;` (scope `Metasound::NodeCategories`)
- L13 _externvar_ `extern const FText Envelopes;` (scope `Metasound::NodeCategories`)
- L14 _externvar_ `extern const FText Filters;` (scope `Metasound::NodeCategories`)
- L15 _externvar_ `extern const FText Generators;` (scope `Metasound::NodeCategories`)
- L16 _externvar_ `extern const FText Io;` (scope `Metasound::NodeCategories`)
- L17 _externvar_ `extern const FText Math;` (scope `Metasound::NodeCategories`)
- L18 _externvar_ `extern const FText Mix;` (scope `Metasound::NodeCategories`)
- L19 _externvar_ `extern const FText Music;` (scope `Metasound::NodeCategories`)
- L20 _externvar_ `extern const FText RandomUtils;` (scope `Metasound::NodeCategories`)
- L21 _externvar_ `extern const FText Spatialization;` (scope `Metasound::NodeCategories`)
- L22 _externvar_ `extern const FText Trigger;` (scope `Metasound::NodeCategories`)
- L23 _externvar_ `extern const FText WaveTables;` (scope `Metasound::NodeCategories`)
- L24 _externvar_ `extern const FText Reverbs;` (scope `Metasound::NodeCategories`)

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundStandardNodesNames.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace StandardNodes` (scope `Metasound`)
- L11 _externvar_ `extern const FLazyName Namespace;` (scope `Metasound::StandardNodes`)
- L12 _externvar_ `extern const FLazyName AudioVariant;` (scope `Metasound::StandardNodes`)

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundTriggerAccumulatorNode.h` (Public)


#### class `Metasound::TTriggerAccumulatorOperator`  
`template<uint32 NumInputs> class TTriggerAccumulatorOperator : public TExecutableOperator<TTriggerAccumulatorOperator<NumInputs>>`  
_L31-190_
- inherits: `TExecutableOperator<TTriggerAccumulatorOperator<NumInputs>>`
- L34 _public function_ `static const FVertexInterface& GetDefaultInterface()`
- L59 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L75 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L92 _public function_ `TTriggerAccumulatorOperator(const FOperatorSettings& InSettings, const FBoolReadRef& bInAutoReset, const TArray<FTriggerReadRef>&& InInputTriggers) : bAutoReset(bInAutoReset) , InputTriggers(InInputTriggers) , OutputTrigger(FTriggerWriteRef::CreateNew(InSettings))`
- L102 _public prototype_ `virtual ~TTriggerAccumulatorOperator() = default;`
- L105 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L116 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L123 _public function_ `void TriggerOutputIfReady(int32 InStartFrame)`
- L145 _public function_ `void ResetTriggerState()`
- L152 _public function_ `void Execute()`
- L176 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L184 _private member_ `FBoolReadRef bAutoReset;`
- L185 _private member_ `TArray<FTriggerReadRef> InputTriggers;`
- L186 _private member_ `FTriggerWriteRef OutputTrigger;`
- L188 _private member_ `TArray<bool> bInputWasTriggered;`
- L189 _private member_ `bool bOutputTriggered = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_AccumulatorNode"`
- L16 _namespace_ `namespace Metasound`
- L18 _namespace_ `namespace MetasoundTriggerAccumulatorNodePrivate` (scope `Metasound`)
- L20 _prototype_ `FNodeClassMetadata CreateNodeClassMetadata(const FName& InOperatorName, const FText& InDisplayName, const FText& InDescription, const FVertexInterface& InDefaultInterface);` (scope `Metasound::MetasoundTriggerAccumulatorNodePrivate`)
- L23 _namespace_ `namespace TriggerAccumulatorVertexNames` (scope `Metasound`)
- L39 _function_ `` (scope `Metasound::TTriggerAccumulatorOperator::GetDefaultInterface`)
- L62 _function_ `` (scope `Metasound::TTriggerAccumulatorOperator::GetNodeInfo`)
- L165 _function_ `` (scope `Metasound::TTriggerAccumulatorOperator::Execute`)
- L197 _typedef_ `template<uint32 NumInputs> using TTriggerAccumulatorNode = TNodeFacade<TTriggerAccumulatorOperator<NumInputs>>;` (scope `Metasound`) — TTriggerAccumulatorNode Routes values from multiple input pins to a single output pin based on trigger inputs.

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundTriggerCompareNode.h` (Public)


#### enum `Metasound::ETriggerComparisonType`  
`enum class ETriggerComparisonType`  
_L40-48_
- L42 _public enumerator_ `Equals`
- L43 _public enumerator_ `NotEquals`
- L44 _public enumerator_ `LessThan`
- L45 _public enumerator_ `GreaterThan`
- L46 _public enumerator_ `LessThanOrEquals`
- L47 _public enumerator_ `GreaterThanOrEquals`

#### class `Metasound::TTriggerCompareNodeOperator`  
`template<typename ValueType> class TTriggerCompareNodeOperator : public TExecutableOperator<TTriggerCompareNodeOperator<ValueType>>`  
_L54-210_
- inherits: `TExecutableOperator<TTriggerCompareNodeOperator<ValueType>>`
- L57 _public function_ `static const FVertexInterface& GetDefaultInterface()`
- L78 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L95 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L111 _public function_ `TTriggerCompareNodeOperator( const FOperatorSettings& InSettings, const FTriggerReadRef& InOnCompareTrigger, const TDataReadReference<ValueType>& InValueA, const TDataReadReference<ValueType>& InValueB, const FEnumTriggerComparisonTypeReadRef& InTriggerComparisonType) : OnCompareTrigger(InOnCompareTrigger) , ValueA(InValueA) , ValueB(InValueB) , TriggerComparisonType(InTriggerComparisonType) , TriggerOutOnTrue(FTriggerWriteRef::CreateNew(InSettings)) , TriggerOutOnFalse(FTriggerWriteRef::CreateNew(InSettings))`
- L126 _public prototype_ `virtual ~TTriggerCompareNodeOperator() = default;`
- L128 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L138 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L146 _public function_ `void Execute()`
- L195 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L203 _private member_ `FTriggerReadRef OnCompareTrigger;`
- L204 _private member_ `TDataReadReference<ValueType> ValueA;`
- L205 _private member_ `TDataReadReference<ValueType> ValueB;`
- L206 _private member_ `FEnumTriggerComparisonTypeReadRef TriggerComparisonType;`
- L208 _private member_ `FTriggerWriteRef TriggerOutOnTrue;`
- L209 _private member_ `FTriggerWriteRef TriggerOutOnFalse;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_CompareNode"`
- L23 _namespace_ `namespace Metasound`
- L25 _namespace_ `namespace TriggerCompareVertexNames` (scope `Metasound`)
- L35 _namespace_ `namespace MetasoundTriggerCompareNodePrivate` (scope `Metasound`)
- L37 _prototype_ `FNodeClassMetadata CreateNodeClassMetadata(const FName& InDataTypeName, const FName& InOperatorName, const FText& InDisplayName, const FText& InDescription, const FVertexInterface& InDefaultInterface);` (scope `Metasound::MetasoundTriggerCompareNodePrivate`)
- L81 _function_ `` (scope `Metasound::TTriggerCompareNodeOperator::GetNodeInfo`)
- L153 _function_ `` (scope `Metasound::TTriggerCompareNodeOperator::Execute`)
- L217 _typedef_ `template<typename ValueType> using TTriggerCompareNode = TNodeFacade<TTriggerCompareNodeOperator<ValueType>>;` (scope `Metasound`) — TTriggerCompareNode Compares two inputs against enumerated comparison types.

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundTriggerOnThresholdNode.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundTriggerRepeatNode.h` (Public)


#### class `Metasound::FTriggerRepeatNode`  
`class FTriggerRepeatNode : public FNodeFacade`  
_L21-30_
- inherits: `FNodeFacade`
- L24 _public prototype_ `FTriggerRepeatNode(const FNodeInitData& InInitData);`
- L25 _public prototype_ `FTriggerRepeatNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InMetadata);`
- L27 _public prototype_ `virtual ~FTriggerRepeatNode() = default;`
- L29 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METASOUNDSTANDARDNODES_API`
- L19 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundTriggerToggleNode.h` (Public)


#### class `Metasound::FTriggerToggleNode`  
`class FTriggerToggleNode : public FNodeFacade`  
_L21-31_
- inherits: `FNodeFacade`
- L24 _public prototype_ `FTriggerToggleNode(const FNodeInitData& InInitData);`
- L26 _public prototype_ `FTriggerToggleNode(FNodeData InNodeData, TSharedRef<const FNodeClassMetadata> InMetadata);`
- L28 _public prototype_ `virtual ~FTriggerToggleNode() = default;`
- L30 _public prototype_ `static FNodeClassMetadata CreateNodeClassMetadata();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METASOUNDSTANDARDNODES_API`
- L19 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/MetasoundValueNode.h` (Public)


#### class `Metasound::TValueOperator`  
`template<typename ValueType> class TValueOperator : public TExecutableOperator<TValueOperator<ValueType>>`  
_L36-195_
- inherits: `TExecutableOperator<TValueOperator<ValueType>>`
- L39 _public function_ `static const FVertexInterface& GetDefaultInterface()`
- L60 _public function_ `static const FNodeClassMetadata& GetNodeInfo()`
- L77 _public function_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)`
- L92 _public function_ `TValueOperator(const FOperatorSettings& InSettings, const FTriggerReadRef& InSetTrigger, const FTriggerReadRef& InResetTrigger, const TDataReadReference<ValueType>& InInitValue, const TDataReadReference<ValueType>& InTargetValue) : SetTrigger(InSetTrigger) , ResetTrigger(InResetTrigger) , InitValue(InInitValue) , TargetValue(InTargetValue) , OutputValue(TDataWriteReferenceFactory<ValueType>::CreateAny(InSettings)) , TriggerOnSet(FTriggerWriteRef::CreateNew(InSettings)) , TriggerOnReset(FTriggerWriteRef::CreateNew(InSettings))`
- L104 _public prototype_ `virtual ~TValueOperator() = default;`
- L107 _public function_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override`
- L116 _public function_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override`
- L124 _public function_ `virtual FDataReferenceCollection GetInputs() const override`
- L132 _public function_ `virtual FDataReferenceCollection GetOutputs() const override`
- L142 _public function_ `void Execute()`
- L179 _public function_ `void Reset(const IOperator::FResetParams& InParams)`
- L188 _private member_ `TDataReadReference<FTrigger> SetTrigger;`
- L189 _private member_ `TDataReadReference<FTrigger> ResetTrigger;`
- L190 _private member_ `TDataReadReference<ValueType> InitValue;`
- L191 _private member_ `TDataReadReference<ValueType> TargetValue;`
- L192 _private member_ `TDataWriteReference<ValueType> OutputValue;`
- L193 _private member_ `TDataWriteReference<FTrigger> TriggerOnSet;`
- L194 _private member_ `TDataWriteReference<FTrigger> TriggerOnReset;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_ValueNode"`
- L17 _namespace_ `namespace Metasound`
- L19 _namespace_ `namespace MetasoundValueNodePrivate` (scope `Metasound`)
- L21 _prototype_ `FNodeClassMetadata CreateNodeClassMetadata(const FName& InDataTypeName, const FName& InOperatorName, const FText& InDisplayName, const FText& InDescription, const FVertexInterface& InDefaultInterface);` (scope `Metasound::MetasoundValueNodePrivate`)
- L24 _namespace_ `namespace ValueVertexNames` (scope `Metasound`)
- L63 _function_ `` (scope `Metasound::TValueOperator::GetNodeInfo`)
- L159 _function_ `` (scope `Metasound::TValueOperator::Execute`)
- L202 _typedef_ `template<typename ValueType> using TValueNode = TNodeFacade<TValueOperator<ValueType>>;` (scope `Metasound`) — TValueNode Generates a random float value when triggered.

### `Plugins/Runtime/Metasound/Source/MetasoundStandardNodes/Public/NumberedFileCache.h` (Public)


#### class `Metasound::FNumberedFileCache`  
`class FNumberedFileCache`  
_L12-70_
- L15 _public member_ `static const FString Separator;`
- L17 _public function_ `FNumberedFileCache(const FString& InRootPath, const FString& InExt, IFileManager& InFileSystem) : RootPath`
- L23 _public function_ `FString GenerateNextNumberedFilename(const FString& InPrefix)`
- L36 _private function_ `void CacheFilenames()` — Slow directory search of the root path for filenames.
- L65 _private member_ `FCriticalSection Cs;`
- L66 _private member_ `FString RootPath;`
- L67 _private member_ `FString FileExtention;`
- L68 _private member_ `TMap<FString, uint32> FileIndexMap;`
- L69 _private member_ `IFileManager& FileSystem;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
