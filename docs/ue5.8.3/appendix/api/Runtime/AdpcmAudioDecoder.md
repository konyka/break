# Runtime / AdpcmAudioDecoder

- module root: `Source/Runtime/AdpcmAudioDecoder/Module`
- headers: 3; symbols: 129
- symbol kinds: class=3, function=34, macro=4, member=52, namespace=3, prototype=30, struct=3
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/AdpcmAudioDecoder/Module/Private/Adpcm.h` (Private)


#### struct `ADPCMPrivate::SignExtend::(anonymous)`  
`struct`  
_L23-23_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ADPCM`
- L10 _prototype_ `bool DecodeBlock(const uint8* EncodedADPCMBlock, const int32 BlockSize, int16* DecodedPCMData, const int32 DecodedPCMSize);` (scope `ADPCM`) — Returns true if successful, false if there was an error in decoding
- L11 _prototype_ `bool DecodeBlock(const uint8* EncodedADPCMBlock, const int32 BlockSize, int16* DecodedPCMData);` (scope `ADPCM`)
- L14 _namespace_ `namespace ADPCMPrivate`
- L21 _function_ `template <typename T, uint32 B> inline T SignExtend(const T ValueToExtend)` (scope `ADPCMPrivate`)
- L23 _member_ `struct { T ExtendedValue : B; } SignExtender;` (scope `ADPCMPrivate::SignExtend::__anon041f941f0108`)
- L28 _function_ `template <typename T> inline T ReadFromByteStream(const uint8* ByteStream, int32& ReadIndex, bool bLittleEndian = true)` (scope `ADPCMPrivate`)
- L59 _function_ `template <typename T> inline void WriteToByteStream(T Value, uint8* ByteStream, int32& WriteIndex, bool bLittleEndian = true)` (scope `ADPCMPrivate`)
- L86 _function_ `template <typename T> inline T ReadFromArray(const T* ElementArray, int32& ReadIndex, int32 NumElements, int32 IndexStride = 1)` (scope `ADPCMPrivate`)

### `Source/Runtime/AdpcmAudioDecoder/Module/Private/PcmAudioInfoHybrid.h` (Private)


#### class `FPcmAudioInfoHybrid`  
`class FPcmAudioInfoHybrid : public IStreamedCompressedInfo`  
_L8-115_
- inherits: `IStreamedCompressedInfo`
- L11 _public prototype_ `FPcmAudioInfoHybrid() = default;`
- L12 _public prototype_ `virtual ~FPcmAudioInfoHybrid() override = default;`
- L48 _protected prototype_ `virtual bool ParseHeader(const uint8* InSrcBufferData, uint32 InSrcBufferDataSize, FSoundQualityInfo* QualityInfo) override;` — Parse the header information from the input source buffer data. This is dependent on compression format.
- L51 _protected function_ `virtual bool CreateDecoder() override` — Create the compression format dependent decoder object.
- L53 _protected function_ `virtual void PrepareToLoop() override`
- L57 _protected function_ `virtual int32 GetFrameSize() override`
- L61 _protected function_ `virtual uint32 GetMaxFrameSizeSamples() const override`
- L65 _protected function_ `virtual void SeekToFrame(const uint32 InSeekFrame) override`
- L69 _protected function_ `virtual void SeekToTime(const float InSeekTime) override`
- L73 _protected function_ `virtual FDecodeResult Decode(const uint8* CompressedData, const int32 CompressedDataSize, uint8* OutPCMData, const int32 OutputPCMDataSize) override`
- L79 _public function_ `bool IsStreaming() const`
- L83 _public prototype_ `void SeekToAbs(const uint64 InAbsPosition, const uint64 InSeekFrame);`
- L84 _public function_ `void SetErrorFlag() const`
- L86 _public function_ `uint32 GetAudioDataOffset() const`
- L87 _public function_ `uint32 GetSrcBufferOffset() const`
- L88 _public function_ `uint32 GetSrcBufferDataSize() const`
- L91 _private prototype_ `TUniquePtr<FHybridImpl> CreateImpl(const uint8 InFormatId, const int32 InNumChannels, const uint32 InSampleRate);`
- L92 _private prototype_ `bool AbsPositionToChunkIndexAndOffset(const uint64 AbsPosition, uint32& ChunkIndex, uint32& ChunkOffset) const;`
- L94 _private function_ `void SetSeekBlockIndex(const uint32 InStreamSeekBlockIndex)`
- L102 _private function_ `void SetSeekBlockOffset(const int32 InStreamSeekBlockOffset)`
- L106 _private function_ `void SetCurrentSampleCount(const uint32 InSampleCount)`
- L107 _private function_ `void SetSrcBufferOffset(const uint32 InSrcBufferOffset)`
- L114 _private member_ `TUniquePtr<FHybridImpl> Impl;`

#### class `FPcmAudioInfoHybrid::FHybridImpl`  
`class FHybridImpl`  
_L14-43_
- L19 _public function_ `FHybridImpl(FPcmAudioInfoHybrid* InOwner, const int32 InNumChannels, const uint32 InSampleRate) : Owner(InOwner) , NumChannels(InNumChannels) , SampleRate(InSampleRate)`
- L25 _public prototype_ `virtual ~FHybridImpl() = default;`
- L26 _public function_ `virtual void PrepareToLoop()`
- L27 _public prototype_ `virtual bool ParseWaveHeader(const FWaveModInfo& WaveInfo, const WaveFormatHeader* FormatHeader, const uint32 HeaderSize) = 0;`
- L28 _public prototype_ `virtual int32 GetFrameSize() = 0;`
- L29 _public prototype_ `virtual uint32 GetMaxFrameSizeSamples() const = 0;`
- L30 _public prototype_ `virtual void SeekToFrame(const uint32 InSeekFrame) = 0;`
- L31 _public prototype_ `virtual void SeekToTime(const float InSeekTime);`
- L32 _public prototype_ `virtual FDecodeResult Decode(const uint8* CompressedData, const int32 CompressedDataSize, uint8* OutPCMData, const int32 OutputPCMDataSize) = 0;`
- L34 _public function_ `uint32 GetTotalDecodedSize() const`
- L35 _public function_ `uint32 GetTotalSamplesPerChannel() const`
- L38 _protected member_ `FPcmAudioInfoHybrid* Owner = nullptr;`
- L39 _protected member_ `int32 NumChannels = 0;`
- L40 _protected member_ `uint32 TotalDecodedSize = 0;`
- L41 _protected member_ `uint32 SampleRate = 0;`
- L42 _protected member_ `uint32 TotalSamplesPerChannel = 0;` — Number of samples per channel, used to detect when an audio waveform has ended

### `Source/Runtime/AdpcmAudioDecoder/Module/Public/Decoders/ADPCMAudioInfo.h` (Public)


#### struct `WaveFormatHeader`  
`struct WaveFormatHeader`  
_L26-35_
- L28 _public member_ `uint16 wFormatTag;` — Format type: 1 = PCM, 2 = ADPCM
- L29 _public member_ `uint16 nChannels;` — Number of channels (i.e. mono, stereo...).
- L30 _public member_ `uint32 nSamplesPerSec;` — Sample rate. 44100 or 22050 or 11025  Hz.
- L31 _public member_ `uint32 nAvgBytesPerSec;` — For buffer estimation  = sample rate * BlockAlign.
- L32 _public member_ `uint16 nBlockAlign;` — Block size of data = Channels times BYTES per sample.
- L33 _public member_ `uint16 wBitsPerSample;` — Number of bits per sample of mono data.
- L34 _public member_ `uint16 cbSize;` — The count in bytes of the size of extra information (after cbSize).

#### struct `ADPCM::ADPCMFormatHeader`  
`struct ADPCMFormatHeader`  
_L63-85_
- L65 _public member_ `WaveFormatHeader BaseFormat;`
- L66 _public member_ `uint16 wSamplesPerBlock;`
- L67 _public member_ `uint16 wNumCoef;`
- L68 _public member_ `int16 aCoef[2 * NUM_ADAPTATION_COEFF];`
- L69 _public member_ `uint32 SamplesPerChannel;` — This is the exact samples per channel for sample precise looping
- L71 _public function_ `ADPCMFormatHeader()`

#### class `FADPCMAudioInfo`  
`class FADPCMAudioInfo : public ICompressedAudioInfo`  
_L92-189_
- inherits: `ICompressedAudioInfo`
- L95 _public prototype_ `FADPCMAudioInfo(void);`
- L96 _public prototype_ `virtual ~FADPCMAudioInfo(void);`
- L98 _public prototype_ `virtual bool ReadCompressedInfo(const uint8* InSrcBufferData, uint32 InSrcBufferDataSize, struct FSoundQualityInfo* QualityInfo);` — ICompressedAudioInfo Interface
- L99 _public prototype_ `virtual bool ReadCompressedData(uint8* Destination, bool bLooping, uint32 BufferSize);`
- L100 _public prototype_ `virtual void SeekToTime(const float SeekTime);`
- L101 _public prototype_ `virtual void SeekToFrame(const uint32 SeekFrame);`
- L102 _public prototype_ `virtual void ExpandFile(uint8* DstBuffer, struct FSoundQualityInfo* QualityInfo);`
- L103 _public function_ `virtual void EnableHalfRate(bool HalfRate)`
- L104 _public function_ `virtual uint32 GetSourceBufferSize() const`
- L105 _public function_ `virtual bool UsesVorbisChannelOrdering() const`
- L106 _public prototype_ `virtual int GetStreamBufferSize() const;`
- L109 _public function_ `virtual bool SupportsStreaming() const override` — Additional overrides for streaming
- L110 _public prototype_ `virtual bool StreamCompressedInfoInternal(const TSharedRef<const FSoundWaveData>& InWaveData, struct FSoundQualityInfo* QualityInfo) override;`
- L111 _public prototype_ `virtual bool StreamCompressedData(uint8* Destination, bool bLooping, uint32 BufferSize, int32& OutNumBytesStreamed) override;`
- L112 _public function_ `virtual int32 GetCurrentChunkIndex() const override`
- L116 _public function_ `virtual int32 GetCurrentChunkOffset() const override`
- L117 _public prototype_ `virtual bool ReleaseStreamChunk(bool bBlockUntilReleased) override;`
- L120 _public function_ `uint16 GetFormatTag()`
- L132 _public function_ `int32 GetNumChannels()`
- L142 _private prototype_ `const uint8* GetLoadedChunk(const FSoundWaveData& InSoundWaveData, uint32 ChunkIndex, uint32& OutChunkSize);` — Wrapper function that returns a pointer to the currently used compressed data. If a non-zero chunk is requested, this function also aquires a reference to that chunk until we move on to a different chunk.
- L144 _private member_ `int32 NumConsecutiveReadFailiures;`
- L146 _private member_ `FWaveModInfo WaveInfo;`
- L147 _private member_ `const uint8* SrcBufferData;`
- L148 _private member_ `uint32 SrcBufferDataSize;`
- L150 _private member_ `uint32 UncompressedBlockSize;`
- L151 _private member_ `uint32 CompressedBlockSize;`
- L152 _private member_ `uint32 BlockSize;`
- L153 _private member_ `int32 StreamBufferSize;`
- L154 _private member_ `uint32 TotalDecodedSize;`
- L155 _private member_ `int32 NumChannels;`
- L156 _private member_ `int32 Format;`
- L158 _private member_ `uint32 PreviouslyRequestedChunkIndex;`
- L160 _private member_ `uint8* UncompressedBlockData;` — This holds the current block of compressed data for all channels
- L161 _private member_ `uint32 CurrentUncompressedBlockSampleIndex;` — This is the sample index within the current uncompressed block data
- L162 _private member_ `uint32 CurrentChunkIndex;` — This is the index that is currently being used, needed by streaming engine to make sure it stays loaded and the next chunk gets preloaded
- L163 _private member_ `uint32 CurrentChunkBufferOffset;` — This is this byte offset within the current chunk, used by streaming engine to prioritize a load if more then half way through current chunk
- L164 _private member_ `uint32 CurrentChunkDataSize;` — The size of the current chunk, the first chunk is bigger to accommodate the header info
- L165 _private member_ `uint32 TotalSamplesStreamed;` — The number of samples streamed so far (per channel)
- L166 _private member_ `uint32 TotalSamplesPerChannel;` — Number of samples per channel, used to detect when an audio waveform has ended
- L167 _private member_ `uint32 SamplesPerBlock;` — The number of samples per block
- L168 _private member_ `uint32 FirstChunkSampleDataOffset;` — The size of the header in the first chunk, used to skip over it when looping or starting the sample over
- L169 _private member_ `uint32 FirstChunkSampleDataIndex;`
- L170 _private member_ `const uint8* CurCompressedChunkData;` — A pointer to the current chunk of data
- L171 _private member_ `FAudioChunkHandle CurCompressedChunkHandle;` — Shared reference to the current chunk of data.
- L172 _private member_ `FCriticalSection CurCompressedChunkHandleCriticalSection;`
- L173 _private member_ `bool bDecompressorReleased;` — When the chunk is released, we raise this to true, then early exit on future decodes.
- L175 _private member_ `uint32 CurrentCompressedBlockIndex;` — For non disk streaming - the current compressed block in the compressed source data
- L176 _private member_ `uint32 TotalCompressedBlocksPerChannel;` — For non disk streaming - the total number of compressed blocks per channel
- L177 _private member_ `uint8 bNewSeekRequest : 1;` — Whether or not there is a new seek request to be processed
- L178 _private member_ `uint8 bSeekPendingRead : 1;` — Whether or not a requested seek is pending a read
- L179 _private member_ `uint8 bSeekedFowardToNextChunk : 1;` — If this is true, we have already seeked forward to the next chunk while waiting for the current chunk of audio to load.
- L182 _private prototype_ `void ProcessSeekRequest();`
- L183 _private prototype_ `void SeekToFrameInternal(const uint32 InSeekFrame);`
- L184 _private prototype_ `void ResetSeekState();`
- L186 _private member_ `std::atomic<uint32> TargetSeekFrame;`
- L188 _private member_ `FCriticalSection StreamSeekCriticalSection;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define NUM_ADAPTATION_TABLE 16`
- L16 _macro_ `#define NUM_ADAPTATION_COEFF 7`
- L18 _macro_ `#define WAVE_FORMAT_LPCM 1`
- L20 _macro_ `#define WAVE_FORMAT_ADPCM 2`
- L40 _namespace_ `namespace ADPCM`
- L44 _function_ `template <typename T> static void GetAdaptationCoefficients(T(& OutAdaptationCoefficient1)[NUM_ADAPTATION_COEFF], T(& OutAdaptationCoefficient2)[NUM_ADAPTATION_COEFF])` (scope `ADPCM`)
