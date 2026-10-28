# Plugins / WebMMedia

- module root: `Plugins/Media/WebMMedia/Source/WebMMedia`
- headers: 11; symbols: 295
- symbol kinds: class=11, delegate=3, enum=3, enumerator=11, function=25, macro=3, member=121, prototype=110, struct=8
- PrivateDependencyModuleNames: Core, Engine, RHI, RenderCore, WebMMediaFactory
- PublicDependencyModuleNames: LibVpx, LibWebM, Media, MediaUtils, UEOgg, Vorbis, libOpus

### `Plugins/Media/WebMMedia/Source/WebMMedia/Private/Player/MkvFileReader.h` (Private)


#### class `FMkvFileReader`  
`class FMkvFileReader : public mkvparser::IMkvReader`  
_L15-29_
- inherits: `mkvparser::IMkvReader`
- L18 _public prototype_ `bool Open(const TCHAR* Filename);`
- L20 _public prototype_ `static FTimespan GetVideoFrameDuration(const mkvparser::VideoTrack& track);`
- L24 _public prototype_ `virtual int Read(long long Position, long Lenght, unsigned char* Buffer) override;` — IMkvReader interface
- L25 _public prototype_ `virtual int Length(long long* Total, long long* Available) override;`
- L28 _private member_ `TUniquePtr<IFileHandle> m_file;`

### `Plugins/Media/WebMMedia/Source/WebMMedia/Private/Player/WebMMediaPlayer.h` (Private)


#### class `FWebMMediaPlayer`  
`class FWebMMediaPlayer : public IMediaPlayer , public IWebMSamplesSink , protected IMediaCache , protected IMediaControls , protected IMediaTracks , protected IMediaView`  
_L33-186_
- inherits: `IMediaPlayer,IWebMSamplesSink,IMediaCache,IMediaControls,IMediaTracks,IMediaView`
- L42 _public prototype_ `FWebMMediaPlayer(IMediaEventSink& InEventSink);`
- L43 _public prototype_ `virtual ~FWebMMediaPlayer();`
- L47 _public prototype_ `virtual void AddVideoSampleFromDecodingThread(TSharedRef<FWebMMediaTextureSample, ESPMode::ThreadSafe> Sample) override;`
- L48 _public prototype_ `virtual void AddAudioSampleFromDecodingThread(TSharedRef<FWebMMediaAudioSample, ESPMode::ThreadSafe> Sample) override;`
- L49 _public prototype_ `virtual void ReportVideoDecodingError(FString InErrorMessage) override;`
- L50 _public prototype_ `virtual void ReportAudioDecodingError(FString InErrorMessage) override;`
- L54 _public prototype_ `virtual void Close() override;`
- L55 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L56 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L57 _public prototype_ `virtual FString GetInfo() const override;`
- L58 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L59 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L60 _public prototype_ `virtual FString GetStats() const override;`
- L61 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L62 _public prototype_ `virtual FString GetUrl() const override;`
- L63 _public prototype_ `virtual IMediaView& GetView() override;`
- L64 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L65 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L66 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L70 _protected prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L71 _protected prototype_ `virtual FTimespan GetDuration() const override;`
- L72 _protected prototype_ `virtual float GetRate() const override;`
- L73 _protected prototype_ `virtual EMediaState GetState() const override;`
- L74 _protected prototype_ `virtual EMediaStatus GetStatus() const override;`
- L75 _protected prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L76 _protected prototype_ `virtual FTimespan GetTime() const override;`
- L77 _protected prototype_ `virtual bool IsLooping() const override;`
- L78 _protected function_ `virtual bool Seek(const FTimespan& Time) override`
- L80 _protected prototype_ `virtual bool Seek(const FTimespan& InNewTime, const FMediaSeekParams& InAdditionalParams) override;`
- L81 _protected prototype_ `virtual bool SetLooping(bool Looping) override;`
- L82 _protected prototype_ `virtual bool SetRate(float Rate) override;`
- L83 _protected prototype_ `virtual bool GetPlayerFeatureFlag(EFeatureFlag InFlag) const override;`
- L84 _protected prototype_ `virtual bool FlushOnSeekStarted() const override;`
- L85 _protected prototype_ `virtual bool FlushOnSeekCompleted() const override;`
- L89 _protected prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L90 _protected prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L91 _protected prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L92 _protected prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L93 _protected prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L94 _protected prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L95 _protected prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L96 _protected prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L97 _protected prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L98 _protected prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L99 _protected prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L124 _private prototype_ `static ETrackCodec GetCodecFromMKVTrack(const char* InMKVCodecName);`
- L125 _private prototype_ `static FString GetMKVCodec(ETrackCodec InCodec);`
- L126 _private prototype_ `void TickInternal();`
- L127 _private prototype_ `void ReturnVideoSample(const FWebMMediaTextureSample* InSample);`
- L128 _private prototype_ `void ReturnAudioSample(const FWebMMediaAudioSample* InSample);`
- L129 _private prototype_ `void Resume();`
- L130 _private prototype_ `void Pause();`
- L131 _private prototype_ `bool MkvRead();`
- L132 _private prototype_ `void MkvSeekToNextValidBlock();`
- L133 _private prototype_ `void MkvSeekToTime(const FTimespan& Time);`
- L136 _private member_ `IMediaEventSink& EventSink;`
- L137 _private member_ `FCriticalSection MediaSamplesLock;`
- L138 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> Samples;`
- L139 _private member_ `TArray<EMediaEvent> OutEvents;`
- L140 _private member_ `uint32 CurrentDecoderIndex { 0 };`
- L141 _private member_ `FString MediaUrl;`
- L142 _private member_ `TArray<const mkvparser::VideoTrack*> VideoTracks;`
- L143 _private member_ `TArray<const mkvparser::AudioTrack*> AudioTracks;`
- L144 _private member_ `TUniquePtr<FWebMVideoDecoder> VideoDecoder;`
- L145 _private member_ `TUniquePtr<FWebMAudioDecoder> AudioDecoder;`
- L146 _private member_ `TUniquePtr<FMkvFileReader> MkvReader;`
- L147 _private member_ `TUniquePtr<mkvparser::Segment> MkvSegment;`
- L148 _private member_ `const mkvparser::Cluster* MkvCurrentCluster { };`
- L149 _private member_ `const mkvparser::BlockEntry* MkvCurrentBlockEntry { };`
- L150 _private member_ `EMediaState CurrentState { EMediaState::Closed };`
- L151 _private member_ `TOptional<ETrackCodec> NewPendingVideoCodec;`
- L152 _private member_ `TOptional<ETrackCodec> NewPendingAudioCodec;`
- L153 _private member_ `int32 SelectedVideoTrack { INDEX_NONE };`
- L154 _private member_ `int32 SelectedAudioTrack { INDEX_NONE };`
- L155 _private member_ `bool bPendingVideoTrackChange { false };`
- L156 _private member_ `bool bPendingAudioTrackChange { false };`
- L157 _private member_ `FTimespan CurrentTime;`
- L158 _private member_ `TOptional<FTimespan> SeekToTime;`
- L159 _private member_ `FSeekTo SeekTo;`
- L161 _private member_ `int32 CurrentSeekIndex { 0 };`
- L162 _private member_ `int32 CurrentLoopIndex { 0 };`
- L163 _private member_ `bool bFileReachedEOS { false };`
- L164 _private member_ `bool bFileError { false };`
- L165 _private member_ `bool bDecodeError { false };`
- L166 _private member_ `bool bLooping { false} ;`
- L168 _private member_ `TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>> VideoFramesReadyForDecode;`
- L169 _private member_ `TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>> AudioFramesReadyForDecode;`
- L170 _private member_ `TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>> LoadedVideoFrames;`
- L171 _private member_ `TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>> LoadedAudioFrames;`
- L172 _private member_ `FTimespan MovieDuration;`
- L173 _private member_ `FFrameRate VideoFrameRate {0,0};`
- L174 _private member_ `bool bRecalculateFrameRate = false;`
- L175 _private member_ `FCriticalSection TimeLock;`
- L176 _private member_ `TOptional<FTimespan> CurrentVideoTime;`
- L177 _private member_ `TOptional<FTimespan> CurrentAudioTime;`
- L179 _private member_ `FCriticalSection DecodedSamplesLock;`
- L180 _private member_ `std::atomic<int32> NumDecodingEnqueuedVideoFrames;`
- L181 _private member_ `std::atomic<int32> NumDecodingEnqueuedAudioFrames;`
- L182 _private member_ `TArray<TSharedPtr<FWebMMediaTextureSample, ESPMode::ThreadSafe>> DecodedVideoFrames;`
- L183 _private member_ `TArray<TSharedPtr<FWebMMediaAudioSample, ESPMode::ThreadSafe>> DecodedAudioFrames;`
- L184 _private member_ `FWebMMediaTextureSample::FShutdownPoolableDlg VideoFrameDoneDelegate;`
- L185 _private member_ `FWebMMediaAudioSample::FShutdownPoolableDlg AudioFrameDoneDelegate;`

#### enum `FWebMMediaPlayer::ETrackCodec`  
`enum class ETrackCodec`  
_L102-109_
- L104 _public enumerator_ `Undefined`
- L105 _public enumerator_ `VP8`
- L106 _public enumerator_ `VP9`
- L107 _public enumerator_ `Vorbis`
- L108 _public enumerator_ `Opus`

#### struct `FWebMMediaPlayer::FSeekTo`  
`struct FSeekTo`  
_L111-122_
- L113 _public member_ `FTimespan TargetTime;`
- L114 _public member_ `bool bAwaitTime = false;`
- L115 _public member_ `bool bGotVideoKeyframe = false;`
- L116 _public function_ `void Reset()`

### `Plugins/Media/WebMMedia/Source/WebMMedia/Private/WebMMediaPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebMMedia, Log, All);` — Log category for the WebMMedia module.
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebMMedia, Log, All);` — Log category for the WebMMedia module.

### `Plugins/Media/WebMMedia/Source/WebMMedia/Public/IWebMMediaModule.h` (Public)


#### class `IWebMMediaModule`  
`class IWebMMediaModule : public IModuleInterface`  
_L14-31_
- inherits: `IModuleInterface`
- desc: Interface for the WebMMedia module.
- L25 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create a WebM based media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L30 _public function_ `virtual ~IWebMMediaModule()` — Virtual destructor.

### `Plugins/Media/WebMMedia/Source/WebMMedia/Public/WebMAudioDecoder.h` (Public)


#### class `FWebMAudioDecoder`  
`class FWebMAudioDecoder`  
_L17-56_
- L20 _public prototype_ `FWebMAudioDecoder(IWebMSamplesSink& InSamples);`
- L21 _public prototype_ `~FWebMAudioDecoder();`
- L24 _public prototype_ `bool Initialize(const char* InCodec, int32 InSampleRate, int32 InChannels, const uint8* CodecPrivateData, size_t CodecPrivateDataSize);`
- L25 _public prototype_ `void DecodeAudioFramesAsync(const TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>>& AudioFrames);`
- L26 _public prototype_ `bool IsBusy() const;`
- L37 _private member_ `TArray<uint8> CodecSpecificData;`
- L38 _private member_ `TUniquePtr<FWebMMediaAudioSamplePool> AudioSamplePool;`
- L39 _private member_ `TUniquePtr<FVorbisDecoder> VorbisDecoder;`
- L40 _private member_ `FGraphEventRef AudioDecodingTask;`
- L41 _private member_ `TArray<uint8> DecodeBuffer;`
- L42 _private member_ `IWebMSamplesSink& Samples;`
- L43 _private member_ `OpusDecoder* OpusDecoder { };`
- L44 _private member_ `ECodec Codec { ECodec::Undefined };`
- L45 _private member_ `int64 CurrentSequenceIndex { };`
- L46 _private member_ `int32 FrameSize { };`
- L47 _private member_ `int32 SampleRate { };`
- L48 _private member_ `int32 Channels { };`
- L50 _private prototype_ `bool InitializeInternal(FString InCodec, int32 InSampleRate, int32 InChannels, TConstArrayView<uint8> InCodecPrivate);`
- L51 _private prototype_ `void InitializeOpus();`
- L52 _private prototype_ `bool InitializeVorbis(const uint8* CodecPrivateData, size_t CodecPrivateDataSize);`
- L53 _private prototype_ `void DoDecodeAudioFrames(const TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>>& AudioFrames);`
- L54 _private prototype_ `int32 DecodeOpus(const TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>& AudioFrame);`
- L55 _private prototype_ `int32 DecodeVorbis(const TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>& AudioFrame);`

#### enum `FWebMAudioDecoder::ECodec`  
`enum ECodec`  
_L29-34_
- L31 _public enumerator_ `Undefined`
- L32 _public enumerator_ `Opus`
- L33 _public enumerator_ `Vorbis`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WEBMMEDIA_API`

### `Plugins/Media/WebMMedia/Source/WebMMedia/Public/WebMContainer.h` (Public)


#### struct `FWebMAudioTrackInfo`  
`struct FWebMAudioTrackInfo`  
_L13-21_
- L15 _public member_ `const char* CodecName;`
- L16 _public member_ `const uint8* CodecPrivateData;`
- L17 _public member_ `size_t CodecPrivateDataSize;`
- L18 _public member_ `int32 SampleRate;`
- L19 _public member_ `int32 NumOfChannels;`
- L20 _public member_ `bool bIsValid;`

#### struct `FWebMVideoTrackInfo`  
`struct FWebMVideoTrackInfo`  
_L23-27_
- L25 _public member_ `const char* CodecName;`
- L26 _public member_ `bool bIsValid;`

#### class `FWebMContainer`  
`class FWebMContainer`  
_L31-52_
- L34 _public prototype_ `FWebMContainer();`
- L35 _public prototype_ `virtual ~FWebMContainer();`
- L37 _public prototype_ `bool Open(const FString& File);`
- L38 _public prototype_ `void ReadFrames(FTimespan AmountOfTimeToRead, TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>>& AudioFrames, TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>>& VideoFrames);`
- L39 _public prototype_ `FWebMAudioTrackInfo GetCurrentAudioTrackInfo() const;`
- L40 _public prototype_ `FWebMVideoTrackInfo GetCurrentVideoTrackInfo() const;`
- L44 _private member_ `TUniquePtr<FMkvFileReader> MkvReader;`
- L45 _private member_ `TUniquePtr<FMkvFileState> MkvFile;`
- L46 _private member_ `FTimespan CurrentTime;`
- L47 _private member_ `int32 SelectedAudioTrack;`
- L48 _private member_ `int32 SelectedVideoTrack;`
- L49 _private member_ `bool bNoMoreToRead;`
- L51 _private prototype_ `void SeekToNextValidBlock();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WEBMMEDIA_API`

### `Plugins/Media/WebMMedia/Source/WebMMedia/Public/WebMMediaAudioSample.h` (Public)


#### class `FWebMMediaAudioSample`  
`class FWebMMediaAudioSample : public IMediaAudioSample , public IMediaPoolable`  
_L17-143_
- inherits: `IMediaAudioSample,IMediaPoolable`
- desc: Implements a media audio sample for WebMMedia.
- L24 _public function_ `FWebMMediaAudioSample() : Channels(0) , Duration(FTimespan::Zero()) , SampleRate(0) , Time(FTimespan::Zero()) , DecoderIndex(0)` — Default constructor.
- L33 _public function_ `virtual ~FWebMMediaAudioSample()` — Virtual destructor.
- L48 _public function_ `void Initialize( const uint8* InBuffer, uint32 InSize, uint32 InChannels, uint32 InSampleRate, FMediaTimeStamp InTime, FTimespan InDuration, uint32 InDecoderIndex)` — Initialize the sample. @param InBuffer The sample's data buffer. @param InSize The size of the sample buffer (in bytes). @param InChannels The number of channels @param InSampleRate Sampling rate @param InTime The sample time (relative to presentation clock). @param InDuration The duration for which the sample is valid. @param InDecoderIndex Opaque value identifying the producing decoder
- L69 _public prototype_ `DECLARE_DELEGATE_OneParam(FShutdownPoolableDlg, const FWebMMediaAudioSample*);`
- L70 _public function_ `void SetShutdownPoolableDelegate(FShutdownPoolableDlg InDelegate)`
- L77 _public function_ `virtual const void* GetBuffer() override`
- L82 _public function_ `virtual uint32 GetChannels() const override`
- L87 _public function_ `virtual FTimespan GetDuration() const override`
- L92 _public function_ `virtual EMediaAudioSampleFormat GetFormat() const override`
- L97 _public function_ `virtual uint32 GetFrames() const override`
- L102 _public function_ `virtual uint32 GetSampleRate() const override`
- L107 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L112 _public function_ `const TArray<uint8>& GetDataBuffer() const`
- L118 _public function_ `virtual void ShutdownPoolable() override`
- L121 _public function_ `uint32 GetDecoderIndex() const`
- L124 _private member_ `FShutdownPoolableDlg ShutdownDelegate;`
- L127 _private member_ `TArray<uint8> Buffer;` — The sample's data buffer.
- L130 _private member_ `uint32 Channels;` — Number of audio channels.
- L133 _private member_ `FTimespan Duration;` — The duration for which the sample is valid.
- L136 _private member_ `uint32 SampleRate;` — Audio sample rate (in samples per second).
- L139 _private member_ `FMediaTimeStamp Time;` — Presentation time for which the sample was generated.
- L142 _private member_ `uint32 DecoderIndex;` — An identifier of the decoder that produced this sample

#### class `FWebMMediaAudioSamplePool`  
`class FWebMMediaAudioSamplePool : public TMediaObjectPool<FWebMMediaAudioSample>`  
_L147-147_
- inherits: `TMediaObjectPool<FWebMMediaAudioSample>`
- desc: Implements a pool for WebM audio sample objects.

#### Free symbols / members of external scopes

- L69 _delegate_ `DECLARE_DELEGATE_OneParam(FShutdownPoolableDlg, const FWebMMediaAudioSample*);`

### `Plugins/Media/WebMMedia/Source/WebMMedia/Public/WebMMediaFrame.h` (Public)


#### struct `FWebMFrameInfo`  
`struct FWebMFrameInfo`  
_L7-13_
- L9 _public member_ `FTimespan Time;`
- L10 _public member_ `FTimespan Duration;`
- L11 _public member_ `int64 SequenceIndex = 0;`
- L12 _public member_ `uint32 DecoderIndex = 0;`

#### struct `FWebMFrame`  
`struct FWebMFrame : public FWebMFrameInfo`  
_L15-24_
- inherits: `FWebMFrameInfo`
- L17 _public member_ `bool bIsKeyframe = false;`
- L18 _public member_ `TArray<uint8> Data;`
- L20 _public member_ `FString CodecName;` — If codec name is set then a new decoder of this format is needed.
- L21 _public member_ `TArray<uint8> CodecSpecificData;`
- L22 _public member_ `int32 NumChannels = 0;`
- L23 _public member_ `int32 SamplingRate = 0;`

### `Plugins/Media/WebMMedia/Source/WebMMedia/Public/WebMMediaTextureSample.h` (Public)


#### class `FWebMMediaTextureSample`  
`class FWebMMediaTextureSample : public IMediaTextureSample , public IMediaTextureSampleConverter , public IMediaPoolable`  
_L16-117_
- inherits: `IMediaTextureSample,IMediaTextureSampleConverter,IMediaPoolable`
- L22 _public prototype_ `FWebMMediaTextureSample();`
- L48 _public prototype_ `void Initialize(const FSourceImageDesc& InSourcePlanes, FIntPoint InDisplaySize, FMediaTimeStamp InTime, FTimespan InDuration, uint32 InDecoderIndex);`
- L51 _public prototype_ `const void* GetBuffer() override;`
- L52 _public prototype_ `FIntPoint GetDim() const override;`
- L53 _public prototype_ `FTimespan GetDuration() const override;`
- L54 _public prototype_ `EMediaTextureSampleFormat GetFormat() const override;`
- L55 _public prototype_ `FIntPoint GetOutputDim() const override;`
- L56 _public prototype_ `uint32 GetStride() const override;`
- L57 _public prototype_ `FRHITexture* GetTexture() const override;`
- L58 _public prototype_ `FMediaTimeStamp GetTime() const override;`
- L59 _public prototype_ `bool IsCacheable() const override;`
- L60 _public prototype_ `bool IsOutputSrgb() const override;`
- L61 _public prototype_ `IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override;`
- L64 _public prototype_ `uint32 GetConverterInfoFlags() const override;`
- L65 _public prototype_ `bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) override;`
- L68 _public prototype_ `DECLARE_DELEGATE_OneParam(FShutdownPoolableDlg, const FWebMMediaTextureSample*);`
- L69 _public function_ `void SetShutdownPoolableDelegate(FShutdownPoolableDlg InDelegate)`
- L71 _public function_ `uint32 GetDecoderIndex() const`
- L75 _public prototype_ `virtual void ShutdownPoolable() override;`
- L77 _public prototype_ `TRefCountPtr<FRHITexture> GetTextureRef() const;`
- L109 _private member_ `FShutdownPoolableDlg ShutdownDelegate;`
- L110 _private member_ `FImagePlanes ImagePlanes;`
- L111 _private member_ `TRefCountPtr<FRHITexture> Texture;`
- L112 _private member_ `FMediaTimeStamp Time;`
- L113 _private member_ `FTimespan Duration;`
- L114 _private member_ `FIntPoint DisplaySize;`
- L115 _private member_ `uint32 DecoderIndex = 0;`
- L116 _private member_ `bool bFormatChanged = true;`

#### struct `FWebMMediaTextureSample::FImagePlaneDesc`  
`struct FImagePlaneDesc`  
_L24-42_
- L27 _public member_ `FIntPoint Dimensions[4];` — 0=Y, 1=U, 2=V, 3=Alpha (not used)
- L28 _public member_ `uint32 Stride[4] {};`
- L29 _public member_ `uint8 BytesPerPixel[4] {1,1,1,1};`
- L30 _public member_ `uint8 VpxColorSpace {2};`
- L31 _public member_ `uint8 VpxFullRange {0};`
- L32 _public function_ `bool operator==(const FImagePlaneDesc&rhs) const`
- L40 _public function_ `bool operator!=(const FImagePlaneDesc&rhs) const`

#### struct `FWebMMediaTextureSample::FSourceImageDesc`  
`struct FSourceImageDesc : public FImagePlaneDesc`  
_L43-46_
- inherits: `FImagePlaneDesc`
- L45 _public member_ `void* SrcData[4] {};`

#### struct `FWebMMediaTextureSample::FImagePlanes`  
`struct FImagePlanes : public FImagePlaneDesc`  
_L80-107_
- inherits: `FImagePlaneDesc`
- L82 _public function_ `FImagePlanes& operator= (const FImagePlaneDesc& rhs)`
- L87 _public member_ `TRefCountPtr<FRHITexture> SrcPlaneTexture[4];`
- L88 _public member_ `void* Data[4] {};`
- L89 _public member_ `uint32 AllocatedDataSize[4] {};`
- L90 _public function_ `~FImagePlanes()`
- L94 _public function_ `void Reset()`

#### class `FWebMMediaTextureSamplePool`  
`class FWebMMediaTextureSamplePool : public TMediaObjectPool<FWebMMediaTextureSample>`  
_L119-119_
- inherits: `TMediaObjectPool<FWebMMediaTextureSample>`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API WEBMMEDIA_API`
- L68 _delegate_ `DECLARE_DELEGATE_OneParam(FShutdownPoolableDlg, const FWebMMediaTextureSample*);`

### `Plugins/Media/WebMMedia/Source/WebMMedia/Public/WebMSamplesSink.h` (Public)


#### class `IWebMSamplesSink`  
`class IWebMSamplesSink`  
_L11-20_
- L14 _public prototype_ `virtual void AddVideoSampleFromDecodingThread(TSharedRef<FWebMMediaTextureSample, ESPMode::ThreadSafe> Sample) = 0;`
- L15 _public prototype_ `virtual void AddAudioSampleFromDecodingThread(TSharedRef<FWebMMediaAudioSample, ESPMode::ThreadSafe> Sample) = 0;`
- L16 _public prototype_ `virtual void ReportVideoDecodingError(FString InErrorMessage) = 0;`
- L17 _public prototype_ `virtual void ReportAudioDecodingError(FString InErrorMessage) = 0;`
- L19 _public function_ `virtual ~IWebMSamplesSink()`

### `Plugins/Media/WebMMedia/Source/WebMMedia/Public/WebMVideoDecoder.h` (Public)


#### class `FWebMVideoDecoder`  
`class FWebMVideoDecoder`  
_L21-55_
- L24 _public prototype_ `FWebMVideoDecoder(IWebMSamplesSink& InSamples);`
- L25 _public prototype_ `~FWebMVideoDecoder();`
- L28 _public prototype_ `bool Initialize(const char* CodecName);`
- L29 _public prototype_ `void DecodeVideoFramesAsync(const TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>>& VideoFrames);`
- L30 _public prototype_ `bool IsBusy() const;`
- L40 _private member_ `vpx_codec_ctx_t Context;`
- L41 _private member_ `vpx_codec_dec_cfg_t CodecConfig {};`
- L42 _private member_ `TUniquePtr<FWebMMediaTextureSamplePool> VideoSamplePool;`
- L43 _private member_ `TArray<FWebMFrameInfo*> PendingFrameInfos;`
- L44 _private member_ `FGraphEventRef VideoDecodingTask;`
- L45 _private member_ `IWebMSamplesSink& Samples;`
- L46 _private member_ `ECodec Codec;`
- L47 _private member_ `int64 CurrentSequenceIndex;`
- L48 _private member_ `bool bTexturesCreated;`
- L49 _private member_ `bool bIsInitialized;`
- L51 _private prototype_ `bool InitializeInternal(FString InCodecName);`
- L52 _private prototype_ `void DoDecodeVideoFrames(const TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>>& VideoFrames);`
- L53 _private prototype_ `void Close();`
- L54 _private prototype_ `void FlushPendingFrameInfos();`

#### enum `FWebMVideoDecoder::ECodec`  
`enum class ECodec`  
_L33-38_
- L35 _public enumerator_ `Unknown`
- L36 _public enumerator_ `VP8`
- L37 _public enumerator_ `VP9`
