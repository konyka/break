# Runtime / VorbisAudioDecoder

- module root: `Source/Runtime/VorbisAudioDecoder/Module`
- headers: 1; symbols: 48
- symbol kinds: class=1, externvar=1, function=6, macro=2, member=15, namespace=1, prototype=21, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/VorbisAudioDecoder/Module/Public/Decoders/VorbisAudioInfo.h` (Public)


#### class `FVorbisAudioInfo`  
`class FVorbisAudioInfo : public ICompressedAudioInfo`  
_L42-134_
- inherits: `ICompressedAudioInfo`
- desc: Helper class to parse ogg vorbis data
- L45 _public prototype_ `FVorbisAudioInfo( void );`
- L46 _public prototype_ `virtual ~FVorbisAudioInfo( void );`
- L48 _public prototype_ `size_t ReadMemory( void *ptr, uint32 size );` — Emulate read from memory functionality
- L49 _public prototype_ `int SeekMemory( uint32 offset, int whence );`
- L50 _public prototype_ `int CloseMemory( void );`
- L51 _public prototype_ `long TellMemory( void );`
- L54 _public prototype_ `size_t ReadStreaming( void *ptr, uint32 size );` — Emulate read from streaming functionality
- L55 _public prototype_ `int CloseStreaming( void );`
- L59 _public prototype_ `bool GetCompressedInfoCommon(void* Callbacks, FSoundQualityInfo* QualityInfo);` — Can't use ov_callbacks here so we have to pass in a void* for the callbacks instead
- L66 _public prototype_ `virtual bool ReadCompressedInfo( const uint8* InSrcBufferData, uint32 InSrcBufferDataSize, struct FSoundQualityInfo* QualityInfo ) override;` — Reads the header information of an ogg vorbis file @param	Resource		Info about vorbis data
- L76 _public prototype_ `virtual bool ReadCompressedData( uint8* InDestination, bool bLooping, uint32 BufferSize ) override;` — Decompresses ogg data to raw PCM data. @param	Destination	where to place the decompressed sound @param	bLooping	whether to loop the sound by seeking to the start, or pad the buffer with zeroes @param	BufferSize	number of bytes of PCM data to create @return	bool		true if the end of the data was reached (for both single shot and looping sounds)
- L77 _public prototype_ `virtual void SeekToTime( const float SeekTime ) override;`
- L78 _public prototype_ `virtual void SeekToFrame(const uint32 SeekFrame) override;`
- L82 _public prototype_ `virtual void ExpandFile( uint8* DstBuffer, struct FSoundQualityInfo* QualityInfo ) override;` — Decompress an entire ogg data file to a TArray
- L88 _public prototype_ `virtual void EnableHalfRate( bool HalfRate ) override;` — Sets ogg to decode to half-rate @param	Resource		Info about vorbis data
- L89 _public function_ `virtual uint32 GetSourceBufferSize() const override`
- L91 _public function_ `virtual bool UsesVorbisChannelOrdering() const override`
- L92 _public function_ `virtual int GetStreamBufferSize() const override`
- L95 _public function_ `virtual bool SupportsStreaming() const override` — Additional overrides for streaming
- L96 _public prototype_ `virtual bool StreamCompressedData(uint8* InDestination, bool bLooping, uint32 BufferSize, int32& OutNumBytesStreamed) override;`
- L97 _public function_ `virtual int32 GetCurrentChunkIndex() const override`
- L98 _public function_ `virtual int32 GetCurrentChunkOffset() const override`
- L99 _public prototype_ `virtual bool HasError() const override;`
- L103 _protected prototype_ `virtual bool StreamCompressedInfoInternal(const TSharedRef<const FSoundWaveData>& InWaveData, struct FSoundQualityInfo* QualityInfo) override;`
- L106 _protected prototype_ `int32 GetAudioDataStartOffset() const;`
- L108 _private typedef_ `using Super = ICompressedAudioInfo;`
- L109 _private prototype_ `const uint8* GetLoadedChunk(const TSharedRef<const FSoundWaveData>& InSoundWaveData, uint32 ChunkIndex, uint32& OutChunkSize);`
- L111 _private member_ `struct FVorbisFileWrapper* VFWrapper;`
- L112 _private member_ `const uint8* SrcBufferData;`
- L113 _private member_ `uint32 SrcBufferDataSize;`
- L114 _private member_ `uint32 BufferOffset;`
- L115 _private member_ `uint32 CurrentBufferChunkOffset;`
- L119 _private member_ `int32 TimesLoopedWithoutDecompressedAudio;` — In case Ogg Vorbis fails to return any compressed audio for an asset, we use this counter to exit out of the decoder's while loop early.
- L122 _private member_ `mutable FCriticalSection VorbisCriticalSection;` — Critical section used to prevent multiple threads accessing same ogg-vorbis file handles at the same time
- L124 _private member_ `uint8 const* CurrentStreamingChunkData;`
- L125 _private member_ `int32 CurrentStreamingChunkIndex;`
- L126 _private member_ `int32 NextStreamingChunkIndex;`
- L127 _private member_ `uint32 CurrentStreamingChunksSize;`
- L128 _private member_ `bool bHeaderParsed;`
- L129 _private member_ `bool bHasError = false;`
- L130 _private member_ `int32 LastErrorCode = 0;`
- L133 _private member_ `FAudioChunkHandle CurCompressedChunkHandle;` — This handle is used to ensure that a chunk currently being decoded isn't evicted until we are done with it.

#### Free symbols / members of external scopes

- L17 _macro_ `#define WITH_OGGVORBIS 0`
- L24 _macro_ `#define WITH_OGGVORBIS_DLL (PLATFORM_WINDOWS)`
- L28 _namespace_ `namespace VorbisChannelInfo`
- L30 _externvar_ `extern const int32 Order[8][8];` (scope `VorbisChannelInfo`)
- L36 _prototype_ `void LoadVorbisLibraries();` — Loads vorbis dlls
