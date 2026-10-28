# Runtime / RadAudioDecoder

- module root: `Source/Runtime/RadAudioCodec/Module`
- headers: 1; symbols: 17
- symbol kinds: class=1, member=4, prototype=11, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/RadAudioCodec/Module/Public/RadAudioInfo.h` (Public)


#### class `FRadAudioInfo`  
`class FRadAudioInfo : public IStreamedCompressedInfo`  
_L12-39_
- inherits: `IStreamedCompressedInfo`
- desc: Decoder thunk to the RAD Audio libraries. Also manages file parsing for the cooked data.
- L15 _public prototype_ `FRadAudioInfo();`
- L16 _public prototype_ `virtual ~FRadAudioInfo();`
- L19 _public prototype_ `virtual bool ParseHeader(const uint8* InSrcBufferData, uint32 InSrcBufferDataSize, FSoundQualityInfo* QualityInfo) override;`
- L20 _public prototype_ `virtual int32 GetFrameSize() override;`
- L21 _public prototype_ `virtual uint32 GetMaxFrameSizeSamples() const override;`
- L22 _public prototype_ `virtual bool CreateDecoder() override;`
- L23 _public prototype_ `virtual void SeekToTime(const float SeekToTimeSeconds) override;`
- L24 _public prototype_ `virtual void SeekToFrame(const uint32 SeekTimeFrames) override;`
- L25 _public prototype_ `virtual void PrepareToLoop() override;`
- L26 _public prototype_ `virtual FDecodeResult Decode(const uint8* CompressedData, const int32 CompressedDataSize, uint8* OutPCMData, const int32 OutputPCMDataSize) override;`
- L27 _public prototype_ `virtual bool HasError() const override;`
- L31 _protected typedef_ `using Super = IStreamedCompressedInfo;`
- L35 _protected member_ `TArray<uint8> OutputReservoir;` — This is allocated on demand so that streaming sources can avoid allocating the memory. These are all int16 but left as uint8 so we can use SampleStride.
- L36 _protected member_ `struct RadAudioDecoder* Decoder = 0;`
- L37 _protected member_ `TArray<uint8> RawMemory;`
- L38 _protected member_ `bool bErrorStateLatch = false;`
