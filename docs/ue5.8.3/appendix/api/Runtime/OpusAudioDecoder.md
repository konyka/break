# Runtime / OpusAudioDecoder

- module root: `Source/Runtime/OpusAudioDecoder/Module`
- headers: 1; symbols: 30
- symbol kinds: class=1, function=2, member=15, prototype=11, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/OpusAudioDecoder/Module/Public/Decoders/OpusAudioInfo.h` (Public)


#### class `FOpusAudioInfo`  
`class FOpusAudioInfo : public IStreamedCompressedInfo`  
_L18-89_
- inherits: `IStreamedCompressedInfo`
- desc: Helper class to parse opus data
- L21 _public prototype_ `FOpusAudioInfo();`
- L22 _public prototype_ `virtual ~FOpusAudioInfo();`
- L24 _public prototype_ `bool ParseHeader(const uint8* InSrcBufferData, uint32 InSrcBufferDataSize, FSoundQualityInfo* QualityInfo) override;`
- L25 _public prototype_ `int32 GetFrameSize() override;`
- L26 _public prototype_ `uint32 GetMaxFrameSizeSamples() const override;`
- L27 _public prototype_ `bool CreateDecoder() override;`
- L28 _public prototype_ `FDecodeResult Decode(const uint8* CompressedData, const int32 CompressedDataSize, uint8* OutPCMData, const int32 OutputPCMDataSize) override;`
- L29 _public prototype_ `void PrepareToLoop() override;`
- L30 _public prototype_ `void SeekToTime(const float SeekTime) override;`
- L31 _public prototype_ `void SeekToFrame(const uint32 SeekFrame) override;`
- L76 _public prototype_ `static bool ParseHeader(FHeader& OutHeader, uint32& OutNumRead, const uint8* InSrcBufferData, uint32 InSrcBufferDataSize);`
- L79 _protected member_ `FOpusDecoderWrapper* OpusDecoderWrapper;` — Wrapper around Opus-specific decoding state and APIs
- L82 _protected member_ `FHeader Header;` — The currently active header.
- L85 _protected member_ `int32 NumRemainingSamplesToSkip = 0;` — The number of decoded samples that need to be skipped over.
- L88 _protected member_ `TArray<uint8> PreviousDecodedUnusedSamples;` — Samples that are left over from the previous Decode() call that did not fit into the receive buffer.

#### struct `FOpusAudioInfo::FHeader`  
`struct FHeader`  
_L33-75_
- L35 _public member_ `char Identifier[8];`
- L36 _public member_ `uint8 Version = 0;`
- L37 _public member_ `uint8 NumChannels = 0;`
- L38 _public member_ `uint32 SampleRate = 0;`
- L39 _public member_ `uint32 EncodedSampleRate = 0;`
- L40 _public member_ `uint64 ActiveSampleCount = 0;`
- L41 _public member_ `uint32 NumEncodedFrames = 0;`
- L42 _public member_ `int32 NumPreSkipSamples = 0;`
- L43 _public member_ `int32 NumSilentSamplesAtBeginning = 0;`
- L44 _public member_ `int32 NumSilentSamplesAtEnd = 0;`
- L46 _public function_ `void Reset()`
- L60 _public member_ `static inline const char OPUS_ID[8] {'U','E','O','P','U','S','\0','\0'};`
- L61 _public function_ `static constexpr int32 HeaderSize()`
