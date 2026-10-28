# Runtime / BinkAudioDecoder

- module root: `Source/Runtime/BinkAudioDecoder/Module`
- headers: 1; symbols: 19
- symbol kinds: class=1, member=6, prototype=11, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/BinkAudioDecoder/Module/Public/BinkAudioInfo.h` (Public)


#### class `FBinkAudioInfo`  
`class FBinkAudioInfo : public IStreamedCompressedInfo`  
_L12-44_
- inherits: `IStreamedCompressedInfo`
- desc: Decoder thunk to the Bink Audio libraries. Also manages file parsing for the cooked data.
- L15 _public prototype_ `FBinkAudioInfo();`
- L16 _public prototype_ `virtual ~FBinkAudioInfo();`
- L19 _public prototype_ `virtual bool ParseHeader(const uint8* InSrcBufferData, uint32 InSrcBufferDataSize, FSoundQualityInfo* QualityInfo) override;`
- L20 _public prototype_ `virtual int32 GetFrameSize() override;`
- L21 _public prototype_ `virtual uint32 GetMaxFrameSizeSamples() const override;`
- L22 _public prototype_ `virtual bool CreateDecoder() override;`
- L23 _public prototype_ `virtual void SeekToTime(const float SeekToTimeSeconds) override;`
- L24 _public prototype_ `virtual void SeekToFrame(const uint32 SeekTimeFrames) override;`
- L25 _public prototype_ `virtual FDecodeResult Decode(const uint8* CompressedData, const int32 CompressedDataSize, uint8* OutPCMData, const int32 OutputPCMDataSize) override;`
- L26 _public prototype_ `virtual bool HasError() const override;`
- L30 _protected typedef_ `using Super = IStreamedCompressedInfo;`
- L32 _protected prototype_ `void NotifySeek();`
- L35 _protected member_ `uint32 MaxCompSpaceNeeded;` — copied from header during ParseHeader
- L36 _protected member_ `uint32 SampleRate;`
- L40 _protected member_ `TArray<uint8, TAlignedHeapAllocator<16>> OutputReservoir;` — we lazy init this because the general use case (streaming) should always be able to decode directly to the output buffer.
- L41 _protected member_ `struct BinkAudioDecoder* Decoder = 0;`
- L42 _protected member_ `TArray<uint8, TAlignedHeapAllocator<16>> RawMemory;`
- L43 _protected member_ `bool bErrorStateLatch = false;`
