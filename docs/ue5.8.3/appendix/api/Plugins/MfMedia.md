# Plugins / MfMedia

- module root: `Plugins/Media/MfMedia/Source/MfMedia`
- headers: 12; symbols: 272
- symbol kinds: class=12, delegate=1, function=34, macro=4, member=95, namespace=1, prototype=118, struct=4, variable=3
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: Core, MediaUtils, RenderCore
- PrivateIncludePathModuleNames: Media

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Mf/IMfMediaSourceReaderSink.h` (Private)


#### class `IMfMediaSourceReaderSink`  
`class IMfMediaSourceReaderSink`  
_L21-54_
- desc: Interface for objects that receive media source reader callbacks. @see FMfMediaSourceReaderCallback
- L32 _public prototype_ `virtual void ReceiveSourceReaderEvent(MediaEventType Event) = 0;` — Receive the given source reader event. @param Event The event to receive. @note Implementors must be thread-safe as this method may be called from arbitrary worker threads. @see ReceiveSourceReaderSample, ReceiveSourceReaderFlush
- L40 _public prototype_ `virtual void ReceiveSourceReaderFlush() = 0;` — Receive a source reader flush notification. @note Implementors must be thread-safe as this method may be called from arbitrary worker threads. @see ReceiveSourceReaderEvent, ReceiveSourceReaderSample
- L53 _public prototype_ `virtual void ReceiveSourceReaderSample(IMFSample* Sample, HRESULT Status, DWORD StreamFlags, DWORD StreamIndex, FTimespan Time) = 0;` — Receive the given media sample. @param Sample The sample to receive. @param Status The sample's status code. @param StreamFlags The stream flags. @param StreamIndex The index of the stream that generated the sample. @param Timestamp The sample's time stamp. @note Implementors must be thread-safe as this method may be called from arbitrary worker threads. @see ReceiveSourceReaderEvent, ReceiveSourceReaderFlush

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Mf/MfMediaByteStream.h` (Private)


#### class `FMfMediaByteStream`  
`class FMfMediaByteStream : public IMFAsyncCallback , public IMFByteStream`  
_L22-104_
- inherits: `IMFAsyncCallback,IMFByteStream`
- desc: Implements a wrapper for media source data that is played from memory.
- L33 _public prototype_ `FMfMediaByteStream(const TSharedRef<FArchive, ESPMode::ThreadSafe>& InArchive);` — Creates and initializes a new instance from the specified buffer. @param InArchive The archive to stream from.
- L39 _public prototype_ `STDMETHODIMP_(ULONG) AddRef();`
- L40 _public prototype_ `STDMETHODIMP GetParameters(unsigned long*, unsigned long*);`
- L41 _public prototype_ `STDMETHODIMP Invoke(IMFAsyncResult* AsyncResult);`
- L42 _public prototype_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object);`
- L43 _public prototype_ `STDMETHODIMP_(ULONG) Release();`
- L49 _public prototype_ `STDMETHODIMP BeginRead(BYTE* pb, ULONG cb, IMFAsyncCallback* pCallback, IUnknown* punkState);`
- L50 _public prototype_ `STDMETHODIMP BeginWrite(const BYTE* pb, ULONG cb, IMFAsyncCallback* pCallback, IUnknown* punkState);`
- L51 _public prototype_ `STDMETHODIMP Close();`
- L52 _public prototype_ `STDMETHODIMP EndRead(IMFAsyncResult* pResult, ULONG* pcbRead);`
- L53 _public prototype_ `STDMETHODIMP EndWrite(IMFAsyncResult* pResult, ULONG* pcbWritten);`
- L54 _public prototype_ `STDMETHODIMP Flush();`
- L55 _public prototype_ `STDMETHODIMP GetCapabilities(DWORD* pdwCapabilities);`
- L56 _public prototype_ `STDMETHODIMP GetCurrentPosition(QWORD* pqwPosition);`
- L57 _public prototype_ `STDMETHODIMP GetLength(QWORD* pqwLength);`
- L58 _public prototype_ `STDMETHODIMP IsEndOfStream(BOOL* pfEndOfStream);`
- L59 _public prototype_ `STDMETHODIMP Read(BYTE* pb, ULONG cb, ULONG* pcbRead);`
- L60 _public prototype_ `STDMETHODIMP Seek(MFBYTESTREAM_SEEK_ORIGIN SeekOrigin, LONGLONG qwSeekOffset, DWORD dwSeekFlags, QWORD* pqwCurrentPosition);`
- L61 _public prototype_ `STDMETHODIMP SetLength(QWORD qwLength);`
- L62 _public prototype_ `STDMETHODIMP SetCurrentPosition(QWORD qwPosition);`
- L63 _public prototype_ `STDMETHODIMP Write(const BYTE* pb, ULONG cb, ULONG* pcbWritten);`
- L68 _protected prototype_ `virtual ~FMfMediaByteStream() = default;` — Hidden destructor.
- L80 _protected prototype_ `bool OpenArchive(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl);` — Open media source from a byte stream. @param Archive The archive holding the media data. @param OriginalUrl The original URL of the media that was loaded into the buffer. @return true if the media was opened, false otherwise. @see OpenUrl
- L89 _protected prototype_ `bool OpenUrl(const FString& Url);` — Open media source from a file or internet URL. @param Url The URL of the media to open (file name or web address). @return true if the media was opened, false otherwise. @see OpenArchive
- L94 _private member_ `bool AsyncReadInProgress;` — Whether the stream is currently being read asynchronously.
- L97 _private member_ `TSharedRef<FArchive, ESPMode::ThreadSafe> Archive;` — Holds the archive to stream from.
- L100 _private member_ `mutable FCriticalSection CriticalSection;` — Critical section for locking access to this class.
- L103 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Mf/MfMediaReadState.h` (Private)


#### class `FMfMediaReadState`  
`class FMfMediaReadState : public IUnknown`  
_L21-140_
- inherits: `IUnknown`
- desc: Implements the state information for asynchronous reads of byte buffer sources. The @see FMfByteStream class uses this class to store the state for asynchronous read requests that are initiated with @see FMfByteStream.BeginRead and completed with @see FMfByteStream.EndRead
- L32 _public function_ `FMfMediaReadState(BYTE* InReadBuffer, ULONG InReadBufferSize) : BytesRead(0) , ReadBuffer(InReadBuffer) , ReadBufferSize(InReadBufferSize) , RefCount(0)` — Creates and initializes a new instance. @param InReadBuffer The buffer that receives the read data. @param InReadBufferSize The size of the read buffer.
- L46 _public function_ `void AddBytesRead(uint64 BytesToAdd)` — Adds the specified number of bytes read. @param BytesToAdd The number of bytes to add.
- L56 _public function_ `BYTE* GetReadBuffer() const` — Gets a pointer to the buffer being read from. @return The buffer.
- L66 _public function_ `ULONG GetReadBufferSize() const` — Gets the size of the buffer being read from. @return The size of the buffer (in bytes).
- L76 _public function_ `uint64 GetBytesRead() const` — Gets the actual number of bytes read. @return Bytes read count.
- L85 _public function_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object)`
- L105 _public function_ `STDMETHODIMP_(ULONG) AddRef()`
- L110 _public function_ `STDMETHODIMP_(ULONG) Release()`
- L125 _protected prototype_ `virtual ~FMfMediaReadState() = default;` — Hidden destructor.
- L130 _private member_ `uint64 BytesRead;` — Number of bytes read.
- L133 _private member_ `BYTE* ReadBuffer;` — The buffer that receives the read data.
- L136 _private member_ `ULONG ReadBufferSize;` — The size of the read buffer.
- L139 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Mf/MfMediaSourceReaderCallback.h` (Private)


#### class `FMfMediaSourceReaderCallback`  
`class FMfMediaSourceReaderCallback : public IMFSourceReaderCallback`  
_L22-62_
- inherits: `IMFSourceReaderCallback`
- desc: Callback handler for Media Framework source readers.
- L32 _public prototype_ `FMfMediaSourceReaderCallback(IMfMediaSourceReaderSink& InSink);` — Create and initialize a new instance. @param InSink The object that receives the callbacks.
- L38 _public prototype_ `STDMETHODIMP OnEvent(DWORD, IMFMediaEvent* Event);`
- L39 _public prototype_ `STDMETHODIMP OnFlush(DWORD);`
- L40 _public prototype_ `STDMETHODIMP OnReadSample(HRESULT Status, DWORD StreamIndex, DWORD StreamFlags, LONGLONG Timestamp, IMFSample* Sample);`
- L46 _public prototype_ `STDMETHODIMP_(ULONG) AddRef();`
- L47 _public prototype_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object);`
- L48 _public prototype_ `STDMETHODIMP_(ULONG) Release();`
- L53 _protected prototype_ `virtual ~FMfMediaSourceReaderCallback();` — Hidden destructor (life time is managed by COM).
- L58 _private member_ `int32 RefCount;` — Holds a reference counter for this instance.
- L61 _private member_ `IMfMediaSourceReaderSink& Sink;` — The object that receives the callbacks.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Mf/MfMediaUtils.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace MfMedia`
- L29 _prototype_ `TComPtr<IMFMediaType> CreateOutputType(const GUID& MajorType, const GUID& SubType, bool AllowNonStandardCodecs);` (scope `MfMedia`) — Create an output media type for the given input media type. @param MajorType The output's major type, i.e. audio or video. @param SubType The output's sub type, i.e. PCM or RGB32. @param AllowNonStandardCodecs Whether non-standard codecs should be allowed. @return The output type, or NULL on error.
- L37 _prototype_ `FString FourccToString(unsigned long Fourcc);` (scope `MfMedia`) — Convert a FOURCC code to string. @param Fourcc The code to convert. @return The corresponding string.
- L45 _prototype_ `FString GuidToString(const GUID& Guid);` (scope `MfMedia`) — Convert a Windows GUID to string. @param Guid The GUID to convert. @return The corresponding string.
- L53 _prototype_ `FString MajorTypeToString(const GUID& MajorType);` (scope `MfMedia`) — Convert a media major type to string. @param MajorType The major type GUID to convert. @return The corresponding string.
- L61 _prototype_ `FString MediaEventToString(MediaEventType Event);` (scope `MfMedia`) — Convert a media event to string. @param Event The event code to convert. @return The corresponding string.
- L71 _prototype_ `TComPtr<IMFMediaSource> ResolveMediaSource(TSharedPtr<FArchive, ESPMode::ThreadSafe> Archive, const FString& Url, bool Precache);` (scope `MfMedia`) — Resolve a media source from an archive or URL. @param Archive The archive to read media data from (optional). @param Url The media source URL. @param Precache Whether to precache media into RAM if URL is a local file. @return The media source object, or NULL if it couldn't be resolved.
- L79 _prototype_ `FString ResultToString(HRESULT Result);` (scope `MfMedia`) — Convert an WMF HRESULT code to string. @param Result The result code to convert. @return The corresponding string.
- L87 _prototype_ `FString SubTypeToString(const GUID& SubType);` (scope `MfMedia`) — Convert a media sub-type to string. @param SubType The sub-type GUID to convert. @return The corresponding string.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/MfMediaPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define MFMEDIA_SUPPORTED_PLATFORM (PLATFORM_WINDOWS && !UE_SERVER)`
- L9 _macro_ `#define MFMEDIA_NEED_PLATFORM_PRIVATE 0`
- L12 _macro_ `#define MFMEDIA_NEED_PLATFORM_PRIVATE 1`
- L29 _variable_ `const GUID FORMAT_VideoInfo = { 0x05589f80, 0xc356, 0x11ce, { 0xbf, 0x01, 0x00, 0xaa, 0x00, 0x55, 0x59, 0x5a } };`
- L30 _variable_ `const GUID FORMAT_VideoInfo2 = { 0xf72a76A0, 0xeb0a, 0x11d0, { 0xac, 0xe4, 0x00, 0x00, 0xc0, 0xcc, 0x16, 0xba } };`
- L33 _variable_ `const GUID MF_LOW_LATENCY = { 0x9c27891a, 0xed7a, 0x40e1, { 0x88, 0xe8, 0xb2, 0x27, 0x27, 0xa0, 0x24, 0xee } };`
- L52 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMfMedia, Log, All);` — Log category for the MfMedia module.
- L52 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMfMedia, Log, All);` — Log category for the MfMedia module.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Player/MfMediaAudioSample.h` (Private)


#### class `FMfMediaAudioSample`  
`class FMfMediaAudioSample : public IMediaAudioSample , public IMediaPoolable , protected FMfMediaSample`  
_L23-155_
- inherits: `IMediaAudioSample,IMediaPoolable,FMfMediaSample`
- desc: Audio sample generated by MfMedia player.
- L31 _public function_ `FMfMediaAudioSample() : BytesPerSample(0) , NumChannels(0) , SampleRate(0)` — Default constructor.
- L38 _public prototype_ `virtual ~FMfMediaAudioSample() = default;` — Virtual destructor.
- L48 _public function_ `bool Initialize(IMFMediaType& InMediaType, IMFSample& InSample, uint32 InNumChannels, uint32 InSampleRate)` — Initialize the sample. @param InMediaType The sample's media type. @param InSample The WMF sample.
- L107 _public function_ `virtual const void* GetBuffer() override`
- L112 _public function_ `virtual uint32 GetChannels() const override`
- L117 _public function_ `virtual FTimespan GetDuration() const override`
- L122 _public function_ `virtual EMediaAudioSampleFormat GetFormat() const override`
- L127 _public function_ `virtual uint32 GetFrames() const override`
- L132 _public function_ `virtual uint32 GetSampleRate() const override`
- L137 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L145 _private member_ `uint32 BytesPerSample;` — Number of bytes per audio sample.
- L148 _private member_ `TArray<uint8> Data;` — The sample's data buffer.
- L151 _private member_ `uint32 NumChannels;` — Number of audio channels.
- L154 _private member_ `uint32 SampleRate;` — Audio sample rate (in samples per second).

#### class `FMfMediaAudioSamplePool`  
`class FMfMediaAudioSamplePool : public TMediaObjectPool<FMfMediaAudioSample>`  
_L159-159_
- inherits: `TMediaObjectPool<FMfMediaAudioSample>`
- desc: Implements a pool for MF audio samples.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Player/MfMediaPlayer.h` (Private)


#### class `FMfMediaPlayer`  
`class FMfMediaPlayer : public IMediaPlayer , protected IMediaCache , protected IMediaControls , protected IMediaView , protected IMfMediaSourceReaderSink`  
_L33-183_
- inherits: `IMediaPlayer,IMediaCache,IMediaControls,IMediaView,IMfMediaSourceReaderSink`
- desc: Implements a media player using the Windows Media Foundation framework.
- L47 _public prototype_ `FMfMediaPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L50 _public prototype_ `virtual ~FMfMediaPlayer();` — Virtual destructor.
- L56 _public prototype_ `virtual void Close() override;`
- L57 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L58 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L59 _public prototype_ `virtual FString GetInfo() const override;`
- L60 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L61 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L62 _public prototype_ `virtual FString GetStats() const override;`
- L63 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L64 _public prototype_ `virtual FString GetUrl() const override;`
- L65 _public prototype_ `virtual IMediaView& GetView() override;`
- L66 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L67 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options, const FMediaPlayerOptions* PlayerOptions) override;`
- L68 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L69 _public prototype_ `virtual void TickAudio() override;`
- L70 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L71 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L80 _protected prototype_ `bool CommitTime(FTimespan Time);` — Commit the specified play position. @param Time The play position to commit.
- L90 _protected prototype_ `bool InitializePlayer(const TSharedPtr<FArchive, ESPMode::ThreadSafe>& Archive, const FString& Url, bool Precache, const FMediaPlayerOptions* PlayerOptions);` — Initialize the native AvPlayer instance. @param Archive The archive being used as a media source (optional). @param Url The media URL being opened. @param Precache Whether to precache media into RAM if InURL is a local file. @return true on success, false otherwise.
- L93 _protected prototype_ `void UpdateCharacteristics();` — Get the latest characteristics from the current media source.
- L99 _protected prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L100 _protected prototype_ `virtual FTimespan GetDuration() const override;`
- L101 _protected prototype_ `virtual float GetRate() const override;`
- L102 _protected prototype_ `virtual EMediaState GetState() const override;`
- L103 _protected prototype_ `virtual EMediaStatus GetStatus() const override;`
- L104 _protected prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L105 _protected prototype_ `virtual FTimespan GetTime() const override;`
- L106 _protected prototype_ `virtual bool IsLooping() const override;`
- L107 _protected prototype_ `virtual bool Seek(const FTimespan& Time) override;`
- L108 _protected prototype_ `virtual bool SetLooping(bool Looping) override;`
- L109 _protected prototype_ `virtual bool SetRate(float Rate) override;`
- L115 _protected prototype_ `virtual void ReceiveSourceReaderEvent(MediaEventType Event) override;`
- L116 _protected prototype_ `virtual void ReceiveSourceReaderFlush() override;`
- L117 _protected prototype_ `virtual void ReceiveSourceReaderSample(IMFSample* Sample, HRESULT Status, DWORD StreamFlags, DWORD StreamIndex, FTimespan Time) override;`
- L122 _private member_ `ULONG Characteristics;` — Cached media characteristics (capabilities).
- L125 _private member_ `FTimespan CurrentDuration;` — The duration of the currently loaded media.
- L128 _private member_ `float CurrentRate;` — The current playback rate.
- L131 _private member_ `EMediaState CurrentState;` — The current playback state.
- L134 _private member_ `EMediaStatus CurrentStatus;` — Current status flags.
- L137 _private member_ `FTimespan CurrentTime;` — Current playback time.
- L140 _private member_ `IMediaEventSink& EventSink;` — The media event handler.
- L143 _private member_ `TComPtr<IMFMediaSource> MediaSource;` — The currently opened media.
- L146 _private member_ `FString MediaUrl;` — The URL of the currently opened media.
- L149 _private member_ `bool PlaybackRestarted;` — If playback just restarted from the Stopped state.
- L152 _private member_ `TComPtr<IMFPresentationDescriptor> PresentationDescriptor;` — The presentation descriptor of the currently opened media.
- L155 _private member_ `TComPtr<IMFRateControl> RateControl;` — Optional interface for controlling playback rates.
- L158 _private member_ `TComPtr<IMFRateSupport> RateSupport;` — Optional interface for querying supported playback rates.
- L161 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> Samples;` — Media sample collection.
- L164 _private member_ `bool ShouldLoop;` — Whether playback should loop to the beginning.
- L167 _private member_ `TComPtr<IMFSourceReader> SourceReader;` — The source reader to use.
- L170 _private member_ `bool SourceReaderError;` — Whether an error occurred in the source reader.
- L173 _private member_ `TComPtr<FMfMediaSourceReaderCallback> SourceReaderCallback;` — The source reader callback object.
- L176 _private member_ `TRangeSet<float> ThinnedRates;` — The thinned play rates that the current media session supports.
- L179 _private member_ `TSharedPtr<FMfMediaTracks, ESPMode::ThreadSafe> Tracks;` — Track collection.
- L182 _private member_ `TRangeSet<float> UnthinnedRates;` — The unthinned play rates that the current media session supports.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Player/MfMediaSample.h` (Private)


#### class `FMfMediaSample`  
`class FMfMediaSample`  
_L11-82_
- desc: Abstract base class for MF media samples.
- L15 _protected function_ `FMfMediaSample() : Duration(FTimespan::Zero()) , Time(FTimespan::Zero())`
- L28 _protected function_ `bool InitializeSample(IMFSample& InSample)` — Initialize this sample. @param InSample The WMF sample. @return true on success, false otherwise.
- L75 _protected member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L78 _protected member_ `DWORD Flags;` — Sample flags.
- L81 _protected member_ `FTimespan Time;` — Presentation time for which the sample was generated.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Player/MfMediaTextureSample.h` (Private)


#### class `FMfMediaTextureSample`  
`class FMfMediaTextureSample : public IMediaTextureSample , public IMediaPoolable , protected FMfMediaSample`  
_L23-323_
- inherits: `IMediaTextureSample,IMediaPoolable,FMfMediaSample`
- desc: Texture sample generated by MfMedia player.
- L31 _public function_ `FMfMediaTextureSample() : Dim(FIntPoint::ZeroValue) , OutputDim(FIntPoint::ZeroValue) , SampleFormat(EMediaTextureSampleFormat::Undefined) , Stride(0)` — Default constructor.
- L39 _public prototype_ `virtual ~FMfMediaTextureSample() = default;` — Virtual destructor.
- L51 _public function_ `bool Initialize(IMFMediaType& InMediaType, IMFSample& InSample, const FIntPoint& InBufferDim, uint32 InBufferStride, const FIntPoint& InOutputDim, bool InSlow)` — Initialize the sample from a WMF media sample. @param InMediaType The sample's media type. @param InSample The WMF sample. @param InOutputDim @param InSlow
- L158 _public function_ `virtual const void* GetBuffer() override`
- L163 _public function_ `virtual FIntPoint GetDim() const override`
- L168 _public function_ `virtual FTimespan GetDuration() const override`
- L173 _public function_ `virtual EMediaTextureSampleFormat GetFormat() const override`
- L178 _public function_ `virtual FIntPoint GetOutputDim() const override`
- L183 _public function_ `virtual uint32 GetStride() const override`
- L189 _public function_ `virtual FRHITexture* GetTexture() const override`
- L195 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L200 _public function_ `virtual bool IsCacheable() const override`
- L205 _public function_ `virtual bool IsOutputSrgb() const override`
- L212 _protected function_ `bool InitializeBuffer(IMFSample& InSample)`
- L304 _private member_ `FIntPoint Dim;` — Width and height of the texture sample.
- L307 _private member_ `TArray<uint8> Frame;` — The sample's data buffer.
- L310 _private member_ `FIntPoint OutputDim;` — Width and height of the output.
- L313 _private member_ `TComPtr<IMFSample> Sample;` — The WMF sample object.
- L316 _private member_ `EMediaTextureSampleFormat SampleFormat;` — The sample format.
- L319 _private member_ `uint32 Stride;` — Number of bytes per pixel row.
- L322 _private member_ `GUID SubType;` — Sub-type of the output media format.

#### class `FMfMediaTextureSamplePool`  
`class FMfMediaTextureSamplePool : public TMediaObjectPool<FMfMediaTextureSample>`  
_L327-327_
- inherits: `TMediaObjectPool<FMfMediaTextureSample>`
- desc: Implements a pool for MF texture samples.

### `Plugins/Media/MfMedia/Source/MfMedia/Private/Player/MfMediaTracks.h` (Private)


#### class `FMfMediaTracks`  
`class FMfMediaTracks : public IMediaTracks`  
_L40-380_
- inherits: `IMediaTracks`
- desc: Track collection for Media Foundation based media players.
- L85 _public prototype_ `FMfMediaTracks();` — Default constructor.
- L88 _public prototype_ `virtual ~FMfMediaTracks();` — Virtual destructor.
- L97 _public prototype_ `void AppendStats(FString &OutStats) const;` — Append track statistics information to the given string. @param OutStats The string to append the statistics to.
- L104 _public prototype_ `void ClearFlags();` — Clear the streams flags. @see GetFlags
- L112 _public prototype_ `FTimespan GetDuration() const;` — Get the total duration of the current media source. @return Media duration. @see GetInfo, Initialize
- L121 _public prototype_ `void GetFlags(bool& OutMediaSourceChanged, bool& OutSelectionChanged) const;` — Get the current flags. @param OutMediaSourceChanged Will indicate whether the media source changed. @param OutSelectionChanged Will indicate whether the track selection changed. @see ClearFlags
- L129 _public function_ `const FString& GetInfo() const` — Get the information string for the currently loaded media source. @return Info string. @see GetDuration, GetSamples
- L140 _public prototype_ `IMFMediaSource* GetMediaSource();` — Get the current media source object. @return The media source, or nullptr if not initialized. @see GetSourceReader
- L148 _public prototype_ `IMFSourceReader* GetSourceReader();` — Get the current source reader object. @return The source reader, or nullptr if not initialized. @see GetMediaSource
- L158 _public prototype_ `void Initialize(IMFMediaSource* InMediaSource, IMFSourceReaderCallback* InSourceReaderCallback, const TSharedRef<FMediaSamples, ESPMode::ThreadSafe>& InSamples, const FMediaPlayerOptions* PlayerOptions);` — Initialize the track collection. @param InMediaSource The media source object. @param InSourceReaderCallback The player's source reader callback. @param InSamples The sample collection that receives output samples. @see IsInitialized, Shutdown
- L166 _public function_ `bool IsInitialized() const` — Whether this object has been initialized. @return true if initialized, false otherwise. @see Initialize, Shutdown
- L176 _public prototype_ `void ProcessSample(IMFSample* Sample, HRESULT Status, DWORD StreamFlags, DWORD StreamIndex, FTimespan Time);` — Process a media sample from the source reader callback. @param ReaderSample The sample to process.
- L179 _public prototype_ `void Restart();` — Restart stream sampling.
- L186 _public prototype_ `void Shutdown();` — Shut down the track collection. @see Initialize, IsInitialized
- L195 _public prototype_ `void TickAudio(float Rate, FTimespan Time);` — Tick audio sample processing. @param Rate The current playback rate. @param Time The current presentation time. @see TickVideo
- L204 _public prototype_ `void TickInput(float Rate, FTimespan Time);` — Tick caption & video sample processing. @param Rate The current playback rate. @param Time The current presentation time. @see TickAudio
- L210 _public prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L211 _public prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L212 _public prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L213 _public prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L214 _public prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L215 _public prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L216 _public prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L217 _public prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L218 _public prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L219 _public prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L220 _public prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L231 _protected prototype_ `bool AddStreamToTracks(uint32 StreamIndex, FString& OutInfo);` — Adds the specified stream to the track collection. @param StreamIndex The index number of the stream in the presentation descriptor. @param OutInfo String to append debug information to. @return true on success, false otherwise.
- L241 _protected prototype_ `const FFormat* GetAudioFormat(int32 TrackIndex, int32 FormatIndex) const;` — Get the specified audio format. @param TrackIndex Index of the audio track that contains the format. @param FormatIndex Index of the format to return. @return Pointer to format, or nullptr if not found. @see GetVideoFormat
- L250 _protected prototype_ `const FTrack* GetTrack(EMediaTrackType TrackType, int32 TrackIndex) const;` — Get the specified track information. @param TrackType The type of track. @param TrackIndex Index of the track to return. @return Pointer to track, or nullptr if not found.
- L260 _protected prototype_ `const FFormat* GetVideoFormat(int32 TrackIndex, int32 FormatIndex) const;` — Get the specified video format. @param TrackIndex Index of the video track that contains the format. @param FormatIndex Index of the format to return. @return Pointer to format, or nullptr if not found. @see GetAudioFormat
- L268 _protected prototype_ `bool RequestSample(DWORD StreamIndex);` — Request a new media sample for the specified stream. @param StreamIndex The index of the stream to request a sample for. @return true if a sample was requested, false otherwise.
- L275 _protected prototype_ `void UpdateAudio();` — Request more audio samples, if needed. @see UpdateCaptions, UpdateVideo
- L282 _protected prototype_ `void UpdateCaptions();` — Request more caption samples, if needed. @see UpdateAudio, UpdateVideo
- L289 _protected prototype_ `void UpdateVideo();` — Request more video samples, if needed. @see UpdateAudio, UpdateCaptions
- L295 _protected prototype_ `void PlatformInitialize();`
- L301 _private member_ `bool AudioDone;` — Whether the audio track has reached the end.
- L304 _private member_ `bool AudioSamplePending;` — Whether the next audio sample has been requested.
- L307 _private member_ `FMfMediaAudioSamplePool* AudioSamplePool;` — Audio sample object pool.
- L310 _private member_ `TRange<FTimespan> AudioSampleRange;` — Time range of audio samples to be requested.
- L313 _private member_ `TArray<FTrack> AudioTracks;` — The available audio tracks.
- L316 _private member_ `bool CaptionDone;` — Whether the caption track has reached the end.
- L319 _private member_ `bool CaptionSamplePending;` — Whether the next caption sample has been requested.
- L322 _private member_ `TRange<FTimespan> CaptionSampleRange;` — Time range of caption samples to be requested.
- L325 _private member_ `TArray<FTrack> CaptionTracks;` — The available caption tracks.
- L328 _private member_ `mutable FCriticalSection CriticalSection;` — Synchronizes write access to track arrays, selections & sinks.
- L331 _private member_ `FString Info;` — Media information string.
- L334 _private member_ `FTimespan LastAudioSampleTime;` — Timestamp of the last processed audio sample.
- L337 _private member_ `FTimespan LastCaptionSampleTime;` — Timestamp of the last processed caption sample.
- L340 _private member_ `FTimespan LastVideoSampleTime;` — Timestamp of the last processed video sample.
- L343 _private member_ `TComPtr<IMFMediaSource> MediaSource;` — The currently opened media.
- L346 _private member_ `bool MediaSourceChanged;` — Whether the media source has changed.
- L349 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> Samples;` — Media sample collection that receives the output.
- L352 _private member_ `int32 SelectedAudioTrack;` — Index of the selected audio track.
- L355 _private member_ `int32 SelectedCaptionTrack;` — Index of the selected caption track.
- L358 _private member_ `int32 SelectedVideoTrack;` — Index of the selected video track.
- L361 _private member_ `bool SelectionChanged;` — Whether the track selection changed.
- L364 _private member_ `TComPtr<IMFSourceReader> SourceReader;` — The source reader to use.
- L367 _private member_ `bool VideoDone;` — Whether the video track has reached the end.
- L370 _private member_ `bool VideoSamplePending;` — Whether the next video sample has been requested.
- L373 _private member_ `FMfMediaTextureSamplePool* VideoSamplePool;` — Video sample object pool.
- L376 _private member_ `TRange<FTimespan> VideoSampleRange;` — Time range of video samples to be requested.
- L379 _private member_ `TArray<FTrack> VideoTracks;` — The available video tracks.

#### struct `FMfMediaTracks::FFormat`  
`struct FFormat`  
_L43-69_
- L45 _public member_ `TComPtr<IMFMediaType> InputType;`
- L46 _public member_ `TComPtr<IMFMediaType> OutputType;`
- L47 _public member_ `FString TypeName;`
- L55 _public member_ `Audio;`
- L68 _public member_ `Video;`

#### struct `FMfMediaTracks::FFormat::(anonymous)`  
``  
_L50-54_

#### struct `FMfMediaTracks::FFormat::(anonymous)`  
``  
_L58-67_

#### struct `FMfMediaTracks::FTrack`  
`struct FTrack`  
_L71-80_
- L73 _public member_ `FText DisplayName;`
- L74 _public member_ `TArray<FFormat> Formats;`
- L75 _public member_ `FString Language;`
- L76 _public member_ `FString Name;`
- L77 _public member_ `bool Protected;`
- L78 _public member_ `int32 SelectedFormat;`
- L79 _public member_ `int32 StreamIndex;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define MFMEDIATRACKS_HAS_PLATFORM_INITIALIZE 0`
- L51 _member_ `uint32 BitsPerSample;` (scope `FMfMediaTracks::FFormat::__anona8baa0110108`)
- L52 _member_ `uint32 NumChannels;` (scope `FMfMediaTracks::FFormat::__anona8baa0110108`)
- L53 _member_ `uint32 SampleRate;` (scope `FMfMediaTracks::FFormat::__anona8baa0110108`)
- L59 _member_ `uint32 BitRate;` (scope `FMfMediaTracks::FFormat::__anona8baa0110208`)
- L60 _member_ `FIntPoint BufferDim;` (scope `FMfMediaTracks::FFormat::__anona8baa0110208`)
- L61 _member_ `uint32 BufferStride;` (scope `FMfMediaTracks::FFormat::__anona8baa0110208`)
- L62 _member_ `GUID FormatType;` (scope `FMfMediaTracks::FFormat::__anona8baa0110208`)
- L63 _member_ `float FrameRate;` (scope `FMfMediaTracks::FFormat::__anona8baa0110208`)
- L64 _member_ `TRange<float> FrameRates;` (scope `FMfMediaTracks::FFormat::__anona8baa0110208`)
- L65 _member_ `FIntPoint OutputDim;` (scope `FMfMediaTracks::FFormat::__anona8baa0110208`)
- L66 _member_ `EMediaTextureSampleFormat SampleFormat;` (scope `FMfMediaTracks::FFormat::__anona8baa0110208`)

### `Plugins/Media/MfMedia/Source/MfMedia/Public/IMfMediaModule.h` (Public)


#### class `IMfMediaModule`  
`class IMfMediaModule : public IModuleInterface`  
_L15-32_
- inherits: `IModuleInterface`
- desc: Interface for the MfMedia module.
- L26 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create an Xbox One Media Foundation based media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L31 _public prototype_ `virtual ~IMfMediaModule() = default;` — Virtual destructor.
