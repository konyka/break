# Plugins / RTSPMedia

- module root: `Plugins/Media/RTSPMedia/Source/RTSPMedia`
- headers: 20; symbols: 519
- symbol kinds: class=13, delegate=8, enum=6, enumerator=29, function=3, member=204, namespace=7, prototype=200, struct=11, typedef=1, variable=37
- PrivateDependencyModuleNames: CoreUObject, ElectraBase, ElectraCodecFactory, ElectraDecoders, ElectraSamples, Engine, Media, MediaIOCore, MediaUtils, Networking, RHI, RenderCore, Slate, SlateCore, Sockets, TimeManagement
- PublicDependencyModuleNames: Core, MediaAssets

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/Player/RtspMediaPlayer.h` (Private)


#### class `FRtspMediaPlayer`  
`class FRtspMediaPlayer : public FStreamingMediaPlayerBase , public TSharedFromThis<FRtspMediaPlayer, ESPMode::ThreadSafe>`  
_L17-81_
- inherits: `FStreamingMediaPlayerBase,TSharedFromThis<FRtspMediaPlayer,ESPMode::ThreadSafe>`
- L21 _private typedef_ `using Super = FStreamingMediaPlayerBase;`
- L24 _public prototype_ `FRtspMediaPlayer(IMediaEventSink& InEventSink);`
- L28 _public prototype_ `virtual void Close() override;`
- L29 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L30 _public prototype_ `virtual bool GetPlayerFeatureFlag(EFeatureFlag InFlag) const override;`
- L31 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L32 _public prototype_ `virtual FTimespan GetTime() const override;`
- L33 _public prototype_ `virtual bool Open(const FString& InUrl, const IMediaOptions* InOptions) override;`
- L34 _public prototype_ `virtual void TickInput(FTimespan InDeltaTime, FTimespan InTimecode) override;`
- L38 _public prototype_ `virtual bool GetVideoTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaVideoTrackFormat& OutFormat) const override;` — Overridden from FStreamingMediaPlayerBase
- L42 _private prototype_ `void HandleOnClientStateChanged(ERtspClientState InNewState, ERtspClientState InOldState);`
- L43 _private prototype_ `void HandleOnRtpPacketReceived(FRtpPacket InPacket);`
- L44 _private prototype_ `void HandleOnSdpSessionReceived(const FSdpSession& InSession);`
- L45 _private prototype_ `void HandleOnVideoDimensions(int32 InWidth, int32 InHeight);`
- L46 _private prototype_ `void HandleOnDecoderError();`
- L48 _private prototype_ `void ResetClient();`
- L49 _private prototype_ `void ResetDecoder();`
- L50 _private prototype_ `void ResetRestartState();`
- L52 _private prototype_ `void InitializeClient();`
- L53 _private prototype_ `void HandlePlayerError();`
- L54 _private prototype_ `void ScheduleRestart();`
- L57 _private member_ `TUniquePtr<FRtspClientConfiguration> RtspClientConfiguration;` — RTSP Networking
- L58 _private member_ `TUniquePtr<FRtspClient> RtspClient;`
- L61 _private member_ `int64 MaxFragmentBufferSizeMbOption = RtspMedia::Default::MaxFragmentBufferSizeMb;` — Decoding
- L62 _private member_ `int64 DecoderBufferSizeOption = RtspMedia::Default::DecoderBufferSize;`
- L63 _private member_ `int64 DecoderPollIntervalMsOption = RtspMedia::Default::DecoderPollIntervalMs;`
- L64 _private member_ `bool bProvideCpuBufferOption = RtspMedia::Default::bProvideCpuBuffer;`
- L65 _private member_ `TUniquePtr<FRtpDecoder> RtpDecoder;`
- L68 _private member_ `TUniquePtr<FMediaSamples> Samples;` — Media Player
- L69 _private member_ `int32 VideoFormatWidth = 0;`
- L70 _private member_ `int32 VideoFormatHeight = 0;`
- L73 _private member_ `bool bAutoRestart = RtspMedia::Default::bAutoReconnect;` — Auto Restart Configuration
- L74 _private member_ `float MinRestartDelaySeconds = RtspMedia::Default::MinReconnectDelaySeconds;`
- L75 _private member_ `float MaxRestartDelaySeconds = RtspMedia::Default::MaxReconnectDelaySeconds;`
- L76 _private member_ `int32 MaxRestartAttempts = RtspMedia::Default::MaxReconnectAttempts;`
- L79 _private member_ `int32 RestartAttempts = 0;` — Restart State
- L80 _private member_ `float RestartCountdownSeconds = 0.0f;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/Player/StreamingMediaPlayerBase.h` (Private)


#### class `FStreamingMediaPlayerBase`  
`class FStreamingMediaPlayerBase : public IMediaPlayer , public IMediaControls , public IMediaTracks , public IMediaCache , public IMediaView`  
_L13-80_
- inherits: `IMediaPlayer,IMediaControls,IMediaTracks,IMediaCache,IMediaView`
- L21 _public prototype_ `FStreamingMediaPlayerBase(IMediaEventSink &MediaEventSink);`
- L22 _public prototype_ `virtual ~FStreamingMediaPlayerBase() = default;`
- L24 _public prototype_ `virtual void Close() = 0;`
- L25 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const = 0;`
- L26 _public prototype_ `virtual IMediaSamples& GetSamples() = 0;`
- L27 _public prototype_ `virtual bool Open(const FString& InUrl, const IMediaOptions* InOptions) = 0;`
- L30 _public prototype_ `IMediaCache& GetCache() override;`
- L31 _public prototype_ `IMediaControls& GetControls() override;`
- L32 _public prototype_ `FString GetInfo() const override;`
- L33 _public prototype_ `FString GetStats() const override;`
- L34 _public prototype_ `IMediaTracks& GetTracks() override;`
- L35 _public prototype_ `FString GetUrl() const override;`
- L36 _public prototype_ `IMediaView& GetView() override;`
- L37 _public prototype_ `bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& InArchive, const FString& InOriginalUrl, const IMediaOptions* InOptions) override;`
- L41 _public prototype_ `bool CanControl(EMediaControl InControl) const override;`
- L42 _public prototype_ `FTimespan GetDuration() const override;`
- L43 _public prototype_ `float GetRate() const override;`
- L44 _public prototype_ `EMediaState GetState() const override;`
- L45 _public prototype_ `EMediaStatus GetStatus() const override;`
- L46 _public prototype_ `TRangeSet<float> GetSupportedRates(EMediaRateThinning InThinning) const override;`
- L47 _public prototype_ `bool IsLooping() const override;`
- L48 _public prototype_ `bool Seek(const FTimespan& InTime) override;`
- L49 _public prototype_ `bool SetLooping(bool bInLooping) override;`
- L50 _public prototype_ `bool SetRate(float InRate) override;`
- L54 _public prototype_ `bool GetAudioTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L55 _public prototype_ `int32 GetNumTracks(EMediaTrackType InTrackType) const override;`
- L56 _public prototype_ `int32 GetNumTrackFormats(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L57 _public prototype_ `int32 GetSelectedTrack(EMediaTrackType InTrackType) const override;`
- L58 _public prototype_ `FText GetTrackDisplayName(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L59 _public prototype_ `int32 GetTrackFormat(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L60 _public prototype_ `FString GetTrackLanguage(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L61 _public prototype_ `FString GetTrackName(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L62 _public prototype_ `bool GetVideoTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L63 _public prototype_ `bool SelectTrack(EMediaTrackType InTrackType, int32 InTrackIndex) override;`
- L64 _public prototype_ `bool SetTrackFormat(EMediaTrackType InTrackType, int32 InTrackIndex, int32 InFormatIndex) override;`
- L65 _public prototype_ `bool SetVideoTrackFrameRate(int32 InTrackIndex, int32 InFormatIndex, float InFrameRate) override;`
- L70 _protected prototype_ `void SetState(EMediaState InNewState);`
- L72 _protected member_ `FString CurrentUrl;`
- L73 _protected member_ `EMediaState CurrentState = EMediaState::Closed;`
- L74 _protected member_ `EMediaStatus CurrentStatus = EMediaStatus::None;`
- L75 _protected member_ `IMediaEventSink& EventSink;`
- L76 _protected member_ `int32 NumAudioTracks = 0;`
- L77 _protected member_ `int32 NumVideoTracks = 0;`
- L78 _protected member_ `int32 SelectedVideoTrack = INDEX_NONE;`
- L79 _protected member_ `int32 SelectedAudioTrack = INDEX_NONE;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpCpuBufferWorker.h` (Private)


#### struct `FCpuBufferWorkItem`  
`struct FCpuBufferWorkItem`  
_L18-22_
- desc: Work item handed from the decoder thread to the CPU-buffer worker. Holding the IElectraDecoderVideoOutput shared pointer is what keeps the underlying platform sample (e.g. IMFSample on Windows) alive past PollDecodedOutput.
- L20 _public member_ `TSharedPtr<FElectraTextureSample, ESPMode::ThreadSafe> TextureSample;`
- L21 _public member_ `TSharedPtr<IElectraDecoderVideoOutput, ESPMode::ThreadSafe> VideoOutput;`

#### class `FRtpCpuBufferWorker`  
`class FRtpCpuBufferWorker : public FRunnable`  
_L36-62_
- inherits: `FRunnable`
- desc: Dedicated worker thread that performs the GPU->system staging copy (RtspMedia::PopulateCpuBuffer) off the decoder thread and forwards the resulting sample to FMediaSamples. On Windows MFT the staging copy is the dominant per-frame cost (~8ms at 1080p NV12), so moving it here roughly doubles end-to-end throughput. Single-producer / single-consumer: the owning FRtpDecoder's decoder thread is the only producer; this thread is the only consumer. The owner must stop the decoder thread before tearing this worker down so no enqueues outlive the consumer.
- L39 _public prototype_ `FRtpCpuBufferWorker();`
- L40 _public prototype_ `virtual ~FRtpCpuBufferWorker();`
- L43 _public prototype_ `bool Start(FMediaSamples* InSamples);` — Starts the worker thread. Samples must outlive this worker.
- L47 _public prototype_ `void Enqueue(FCpuBufferWorkItem InItem);` — Enqueued from the decoder thread (single producer). Items are processed in order on the worker thread.
- L51 _private function_ `virtual bool Init() override`
- L52 _private prototype_ `virtual uint32 Run() override;`
- L53 _private prototype_ `virtual void Stop() override;`
- L56 _private member_ `std::atomic<bool> bStopping;`
- L57 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L58 _private member_ `FEvent* WaitEvent = nullptr;`
- L59 _private member_ `TQueue<FCpuBufferWorkItem, EQueueMode::Spsc> Queue;`
- L60 _private member_ `FMediaSamples* Samples = nullptr;`
- L61 _private member_ `bool bLoggedCpuBufferWarning = false;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpDecoder.h` (Private)


#### struct `FQueuedRtpPacket`  
`struct FQueuedRtpPacket`  
_L34-38_
- L36 _public member_ `FRtpPacket Packet;`
- L37 _public member_ `double EnqueueTimeSeconds = 0.0;`

#### class `FRtpDecoder`  
`class FRtpDecoder : public FRunnable`  
_L54-155_
- inherits: `FRunnable`
- desc: Uses a dedicated worker thread for: - Depacketizing H.264 NAL units - H.264 Decoder execution The Initialize, Start and Shutdown methods are all expected to be called from the game thread. EnqueuePacket is expected to be called from the RtspClient worker thread to avoid a hop to the game thread in order to minimise latency.
- L57 _public prototype_ `FRtpDecoder();`
- L58 _public prototype_ `virtual ~FRtpDecoder();`
- L60 _public prototype_ `bool Initialize( FMediaSamples* InSamples, const FSdpSession& InSession, int64 InMaxFragmentBufferSize, int64 InDecoderBufferSize, uint32 InDecoderPollIntervalMs, bool bInProvideCpuBuffer);`
- L68 _public prototype_ `bool Start();`
- L69 _public prototype_ `void Shutdown();`
- L70 _public prototype_ `void EnqueuePacket(FRtpPacket InPacket);`
- L72 _public prototype_ `double GetFrameRate() const;`
- L74 _public member_ `FOnVideoDimensions OnVideoDimensions;`
- L75 _public member_ `FOnDecoderError OnDecoderError;`
- L79 _private prototype_ `virtual bool Init() override;`
- L80 _private prototype_ `virtual uint32 Run() override;`
- L81 _private prototype_ `virtual void Stop() override;`
- L84 _private prototype_ `bool CreateElectraDecoder(const TArray<uint8>& InSequenceParameterSet, const TArray<uint8>& InPictureParameterSet);`
- L85 _private prototype_ `void HandleOnH264NalUnit(FRtpH264NalUnit InNalUnit);`
- L86 _private prototype_ `void HandleOnNalUnitSequenceGap();`
- L87 _private prototype_ `void PollDecodedOutput();`
- L91 _private prototype_ `void ResetIDRRecoveryState();` — Clears the partial access unit, pending bitstream info, and frame-timing state, and sets bWaitForIDRFrame. Does not touch the ElectraDecoder.
- L95 _private prototype_ `void BeginIDRRecovery();` — Resets recovery state and flushes the ElectraDecoder so the next IDR is decoded cleanly. Recreates the decoder if the flush itself fails.
- L100 _private prototype_ `bool TryRecreateDecoder();` — Tears down the existing ElectraDecoder and recreates it from the cached SPS/PPS. On failure, signals OnDecoderError and sets bStopping. Returns true on success.
- L102 _private prototype_ `void ResetFrameBuffer();`
- L103 _private prototype_ `void ResetPlatformVideoResource();`
- L105 _private member_ `TQueue<FQueuedRtpPacket, EQueueMode::Spsc> Queue;`
- L108 _private member_ `std::atomic<bool> bStopping;` — Thread Management
- L109 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L110 _private member_ `FEvent* WaitEvent;`
- L113 _private member_ `TSharedPtr<IElectraDecoderBitstreamProcessor, ESPMode::ThreadSafe> BitstreamProcessor;` — Decoding Tools
- L114 _private member_ `TSharedPtr<IElectraCodecFactory> CodecFactory;`
- L115 _private member_ `TSharedPtr<IElectraDecoder> ElectraDecoder;`
- L116 _private member_ `TUniquePtr<FRtpH264Depacketizer> H264Depacketizer;`
- L119 _private member_ `TArray<uint8> SequenceParameterSet;` — Decoding Configuration
- L120 _private member_ `TArray<uint8> PictureParameterSet;`
- L121 _private member_ `Electra::FCodecTypeFormat CodecTypeFormat;`
- L122 _private member_ `TMap<FString, FVariant> CodecOptions;`
- L123 _private member_ `int64 MaxFragmentBufferSize = RtspMedia::Default::MaxFragmentBufferSizeBytes;`
- L124 _private member_ `int64 DecoderBufferSize = RtspMedia::Default::DecoderBufferSize;`
- L125 _private member_ `uint32 DecoderPollIntervalMs = RtspMedia::Default::DecoderPollIntervalMs;`
- L126 _private member_ `bool bProvideCpuBuffer = RtspMedia::Default::bProvideCpuBuffer;`
- L132 _private member_ `TUniquePtr<FRtpCpuBufferWorker> CpuBufferWorker;` — Off-thread CPU-buffer staging. Created in Initialize when bProvideCpuBuffer is true. The decoder thread enqueues TextureSample/VideoOutput pairs; the worker performs the GPU->system staging copy (~8ms/frame at 1080p NV12 on Windows MFT) and forwards the sample to FMediaSamples.
- L135 _private member_ `TArray<uint8> FrameBuffer;` — Decoding State
- L136 _private member_ `TUniquePtr<FSdpSession> SdpSession;`
- L137 _private member_ `TQueue<TSharedPtr<IElectraDecoderBitstreamInfo, ESPMode::ThreadSafe>> BitstreamInfoQueue;`
- L138 _private member_ `uint32 VideoClockRate = 90000;`
- L139 _private member_ `bool bWaitForIDRFrame = true;`
- L140 _private member_ `bool bPendingCSDChange = false;`
- L143 _private member_ `int32 CurrentVideoWidth = 0;` — Texture Sample Generation
- L144 _private member_ `int32 CurrentVideoHeight = 0;`
- L145 _private member_ `FTimespan LastPresentationTimestamp;`
- L146 _private member_ `FElectraDecodersPlatformResources::IDecoderPlatformResource* PlatformResource = nullptr;`
- L147 _private member_ `TUniquePtr<FElectraTextureSamplePool> TextureSamplePool;`
- L148 _private member_ `int64 FrameDurationTicks = 333333;`
- L149 _private member_ `FMediaSamples* Samples = nullptr;`
- L152 _private member_ `std::atomic<double> FrameRate;` — Frame rate will be updated on the decoder thread and read by the game thread for UI display
- L153 _private member_ `double LastFrameRateUpdate = 0.0;`
- L154 _private member_ `int32 NumFramesSinceLastUpdate = 0;`

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnVideoDimensions, int32, int32);` — Provides Width and Height, executed on the decoder thread.
- L41 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnVideoDimensions, int32, int32);` — Provides Width and Height, executed on the decoder thread.
- L43 _delegate_ `DECLARE_DELEGATE(FOnDecoderError);`
- L43 _prototype_ `DECLARE_DELEGATE(FOnDecoderError);`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpDecoderCpuBuffer.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RtspMedia`
- L21 _prototype_ `void PopulateCpuBuffer(FElectraTextureSample* InTextureSample, const TSharedPtr<IElectraDecoderVideoOutput>& InVideoOutput);` (scope `RtspMedia`) — Populates FElectraTextureSample::Buffer with NV12 pixel data for CPU access. Called after SetupOutputTextureSample succeeds. The GPU rendering path is unaffected. Platform behavior: - macOS/iOS: Locks the CVPixelBuffer and copies Y + CbCr planes - Windows: Extracts MFSample via GetPlatformOutputHandle and copies via Lock2D - Linux: No-op (SetupOutputTextureSample already populates Buffer)

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpH264Depacketizer.h` (Private)


#### class `FRtpH264Depacketizer`  
`class FRtpH264Depacketizer`  
_L12-40_
- L15 _public prototype_ `void ProcessRtpPayload(TArray<uint8> InRtpPayload, uint16 InSequenceNumber, uint32 InTimestamp, bool bInMarker);`
- L16 _public prototype_ `void SetMaxFragmentBufferSize(int64 InMaxFragmentBufferSize);`
- L18 _public member_ `FOnH264NalUnit OnH264NalUnit;`
- L19 _public member_ `FOnNalUnitSequenceGap OnNalUnitSequenceGap;`
- L21 _private prototype_ `void HandleSingleUnit(TArrayView<const uint8> InPayload, uint32 InTimestamp, bool bInMarker);` — Complete NAL
- L22 _private prototype_ `void HandleAggregate(TArrayView<const uint8> InPayload, uint32 InTimestamp, bool bInMarker);` — STAP-A containing multiple NALs
- L23 _private prototype_ `void HandleFragment(TArrayView<const uint8> InPayload, uint32 InTimestamp, bool bInMarker);` — FU-A NAL fragment
- L25 _private prototype_ `void EmitNalUnit(TArrayView<const uint8> InNalUnit, uint32 InTimestamp, bool bInMarker);`
- L27 _private prototype_ `void ResetFragmentBuffer();`
- L29 _private prototype_ `TArrayView<const uint8> StripAnnexBStartCodes(TArrayView<const uint8> InNalData);`
- L32 _private member_ `TArray<uint8> FragmentBuffer;` — State for fragment reassembly
- L33 _private member_ `int64 MaxFragmentBufferSize = RtspMedia::Default::MaxFragmentBufferSizeBytes;`
- L34 _private member_ `bool bFragmentInProgress = false;`
- L35 _private member_ `uint32 FragmentTimestamp = 0;`
- L38 _private member_ `uint16 LastSequenceNumber = 0;` — Sequence tracking
- L39 _private member_ `bool bIsFirstPacket = true;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_OneParam(FOnH264NalUnit, FRtpH264NalUnit);`
- L9 _prototype_ `DECLARE_DELEGATE_OneParam(FOnH264NalUnit, FRtpH264NalUnit);`
- L10 _delegate_ `DECLARE_DELEGATE(FOnNalUnitSequenceGap);`
- L10 _prototype_ `DECLARE_DELEGATE(FOnNalUnitSequenceGap);`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpH264NalUnit.h` (Private)


#### struct `FRtpH264NalUnit`  
`struct FRtpH264NalUnit`  
_L7-17_
- L9 _public member_ `TArray<uint8> Data;` — AVCC-formatted NAL unit (for frame buffer)
- L10 _public member_ `TArray<uint8> SequenceParameterSet;` — Raw SPS bytes (non-empty only for NAL type 7)
- L11 _public member_ `TArray<uint8> PictureParameterSet;` — Raw PPS bytes (non-empty only for NAL type 8)
- L12 _public member_ `uint32 Timestamp = 0;`
- L13 _public member_ `uint8 NalType = 0;`
- L14 _public member_ `bool bIsIDRFrame = false;`
- L15 _public member_ `bool bIsMarkerBitSet = false;`
- L16 _public member_ `bool bIsSlice = false;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpJitterBuffer.h` (Private)


#### class `FRtpJitterBuffer`  
`class FRtpJitterBuffer`  
_L13-52_
- desc: The jitter buffer assumes that packets are enqueued in order. This holds true naturally when the TCP interleaved connection mode is used. For UDP transport packets must be ordered before they are added to the buffer.
- L16 _public prototype_ `bool Initialize(const uint32 InBufferDepthMs, const uint32 InClockRate);`
- L17 _public prototype_ `void EnqueuePacket(FRtpPacket InPacket);`
- L18 _public prototype_ `bool DequeueIfReady(FRtpPacket& OutPacket);`
- L19 _public prototype_ `void SetTargetBufferDepth(float InDepthSeconds);`
- L22 _private prototype_ `void CompactPacketBuffer();`
- L23 _private prototype_ `int32 NumQueuedPackets() const;`
- L24 _private prototype_ `void ResetBuffer();`
- L25 _private prototype_ `void ResetPacing();`
- L27 _private member_ `static constexpr float BufferLevelGain = 0.02f;`
- L30 _private member_ `uint32 ClockRate = 0;` — Configuration
- L31 _private member_ `bool bInitialized = false;`
- L32 _private member_ `float PacketBufferDepthSeconds = 0.0f;`
- L35 _private member_ `TArray<FRtpPacket> PacketBuffer;` — Buffer
- L36 _private member_ `int32 QueueIndex = 0;`
- L39 _private member_ `bool bFilling = true;` — Fill Phase
- L40 _private member_ `double FillStartTimeSeconds = 0.0;`
- L43 _private member_ `float EstimatedFrameIntervalSeconds = 0.0f;` — Frame Pacing
- L44 _private member_ `double NextReleaseTimeSeconds = 0.0;`
- L45 _private member_ `int32 QueuedFrameCount = 0;`
- L48 _private member_ `uint32 LastEnqueuedTimestamp = 0;` — Enqueue/Dequeue Tracking
- L49 _private member_ `bool bFirstPacketEnqueued = false;`
- L50 _private member_ `uint32 LastDequeuedTimestamp = 0;`
- L51 _private member_ `bool bFirstPacketDequeued = false;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpJitterEstimator.h` (Private)


#### class `FRtpJitterEstimator`  
`class FRtpJitterEstimator`  
_L26-49_
- desc: Observes RTP packet arrival timing to estimate the ideal jitter buffer depth. The estimator compares expected inter-frame intervals (derived from RTP timestamps) against actual wall-clock delivery intervals. The difference ("lateness") reflects network jitter. A baseline buffer depth is maintained that steps up immediately on spikes and steps down conservatively after sustained improvement over observation windows. Start at zero: baseline begins at 0 (passthrough). Clean networks stay at zero latency. Spikes drive the baseline up immediately. At window boundaries, baseline clamps down to the worst observed lateness in that window. Baseline values are rounded up to a 10ms granularity to avoid minor oscillations. GetTargetBufferDepthSeconds() returns the baseline with a headroom multiplier applied. During a stall, the buffer drains at the playback rate — without headroom the buffer empties right as the burst arrives, causing a visible stutter.
- L29 _public prototype_ `bool Initialize(uint32 InClockRate, float InObservationWindowSeconds);`
- L30 _public prototype_ `void RecordArrival(uint32 InRtpTimestamp);`
- L31 _public prototype_ `float GetTargetBufferDepthSeconds() const;`
- L35 _private prototype_ `static double CeilToGranularity(double InSeconds);` — Round up to the nearest 10ms. Returns 0 for values at or below 0.
- L37 _private member_ `static constexpr double GranularitySeconds = 0.01;`
- L38 _private member_ `static constexpr double HeadroomMultiplier = 2.0;`
- L40 _private member_ `uint32 ClockRate = 0;`
- L41 _private member_ `bool bInitialized = false;`
- L42 _private member_ `double BaselineSeconds = 0.0;`
- L43 _private member_ `float ObservationWindowSeconds = RtspMedia::Default::JitterBufferObservationWindowSeconds;`
- L44 _private member_ `double RecentMaxLatenessSeconds = 0.0;`
- L45 _private member_ `double WindowStartTimeSeconds = 0.0;`
- L46 _private member_ `uint32 LastTimestamp = 0;`
- L47 _private member_ `double LastArrivalTimeSeconds = 0.0;`
- L48 _private member_ `bool bFirstFrame = true;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpPacket.h` (Private)


#### struct `FRtpHeader`  
`struct FRtpHeader`  
_L7-38_
- L10 _public member_ `uint8 Version = 0;` — 2 bits - value should always be 2
- L13 _public member_ `bool bPadding = false;` — P bit
- L16 _public member_ `bool bExtension = false;` — X bit
- L21 _public member_ `uint8 CsrcCount = 0;` — 4 bits - Contributing source count Used when sources are mixed by a server Typically 0 in video streaming
- L24 _public member_ `bool bMarker = false;` — M bit - indicates last packet of frame
- L27 _public member_ `uint8 PayloadType = 0;` — 7 bits
- L30 _public member_ `uint16 SequenceNumber = 0;` — 2 bytes - for ordering
- L33 _public member_ `uint32 Timestamp = 0;` — 4 bytes - 90kHz clock
- L37 _public member_ `uint32 Ssrc = 0;` — 4 bytes - Synchronization source ID Random identifier

#### struct `FRtpPacket`  
`struct FRtpPacket`  
_L40-44_
- L42 _public member_ `FRtpHeader Header;`
- L43 _public member_ `TArray<uint8> Payload;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTP/RtpParser.h` (Private)


#### class `FRtpParser`  
`class FRtpParser`  
_L9-13_
- L12 _public prototype_ `static bool Parse(const TArrayView<const uint8> InData, FRtpHeader& OutHeader, TArrayView<const uint8>& OutPayload);`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTSP/RtspClient.h` (Private)


#### struct `FRtspClientConfiguration`  
`struct FRtspClientConfiguration`  
_L23-32_
- L25 _public member_ `bool bJitterBufferAutoAdjust = RtspMedia::Default::bJitterBufferAutoAdjust;`
- L26 _public member_ `uint32 JitterBufferDepthMs = RtspMedia::Default::JitterBufferDepthMs;`
- L27 _public member_ `float JitterBufferObservationWindowSeconds = RtspMedia::Default::JitterBufferObservationWindowSeconds;`
- L28 _public member_ `int32 SocketBufferSizeBytes = RtspMedia::Default::SocketBufferSizeBytes;`
- L29 _public member_ `float RequestTimeoutSeconds = RtspMedia::Default::RequestTimeoutSeconds;`
- L30 _public member_ `FRtspTransportConfiguration::TransportProtocol TransportProtocol = FRtspTransportConfiguration::TransportProtocol::TCP;`
- L31 _public member_ `FString Url;`

#### enum `ERtspClientState`  
`enum class ERtspClientState : uint8`  
_L34-44_
- L36 _public enumerator_ `Disconnected`
- L37 _public enumerator_ `Connecting`
- L38 _public enumerator_ `Connected`
- L39 _public enumerator_ `Ready`
- L40 _public enumerator_ `Described`
- L41 _public enumerator_ `Setup`
- L42 _public enumerator_ `Playing`
- L43 _public enumerator_ `Error`

#### class `FRtspClient`  
`class FRtspClient : public FRunnable`  
_L68-153_
- inherits: `FRunnable`
- desc: Uses a dedicated worker thread for: - Socket input and output - State tracking - RTSP message handling - RTP packet handling The public methods (Initialize, Disconnect) are expected be called on the game thread, and the state changed and SDP session received delegates are triggered on the game thread. The on RTP packet received delegate is executed on the worker thread to avoid a hop to the game thread before the packet is processed by the decoder (which has its own worker thread).
- L73 _public prototype_ `bool Initialize(const FRtspClientConfiguration& InConfiguration);`
- L74 _public prototype_ `void Disconnect();`
- L76 _public member_ `FOnRtspClientStateChanged OnStateChanged;`
- L77 _public member_ `FOnSdpSessionReceived OnSdpSessionReceived;`
- L79 _public member_ `FOnRtpPacketReceived OnRtpPacketReceived;`
- L82 _private prototype_ `virtual bool Init() override;`
- L83 _private prototype_ `virtual uint32 Run() override;`
- L84 _private prototype_ `virtual void Stop() override;`
- L86 _private prototype_ `static const TCHAR* StateToString(const ERtspClientState InState);`
- L88 _private prototype_ `ERtspClientState GetState() const;`
- L89 _private prototype_ `void SetState(ERtspClientState InNewState);`
- L91 _private prototype_ `void ProcessState();`
- L92 _private prototype_ `bool ProcessIncomingData();`
- L93 _private prototype_ `void ProcessInterleavedPacket();`
- L94 _private prototype_ `bool ProcessRtspMessage();`
- L96 _private prototype_ `bool HandleResponse(const FRtspMessage& InMessage);`
- L97 _private prototype_ `bool HandleRequest(const FRtspMessage& InRequest);`
- L99 _private prototype_ `bool HandleOptionsResponse(const int32 InStatusCodeValue, const bool bInSuccess, const FRtspMessage& InOriginalRequest);`
- L100 _private prototype_ `bool HandleDescribeResponse(const bool bInSuccess, const FRtspMessage& InResponse, const FRtspMessage& InOriginalRequest);`
- L101 _private prototype_ `bool HandleSetupResponse(const bool bInSuccess, const FRtspMessage& InResponse);`
- L103 _private prototype_ `bool InitializeJitterBuffer(const uint32 InClockRate);`
- L105 _private prototype_ `bool SendOptions();`
- L106 _private prototype_ `bool SendDescribe();`
- L107 _private prototype_ `bool SendSetup(const FString& InControlUrl, const int32 InTrackIndex);`
- L108 _private prototype_ `bool SendPlay();`
- L109 _private prototype_ `bool SendTeardown();`
- L110 _private prototype_ `bool SendKeepAlive();`
- L112 _private prototype_ `bool SendMessage(const FRtspMessage& InMessage);`
- L113 _private prototype_ `bool SendRequest(const FRtspMessage& InRequest);`
- L115 _private prototype_ `bool ParseUrl(const FString& InUrl, FString& OutHost, int32& OutPort, FString& OutPath);`
- L117 _private prototype_ `void TeardownConnection();`
- L118 _private prototype_ `int32 HandleRunError();`
- L120 _private member_ `FRtspClientConfiguration Configuration;`
- L122 _private member_ `FString Host;`
- L123 _private member_ `int32 Port = RtspMedia::Default::Port;`
- L124 _private member_ `FString Path;`
- L125 _private member_ `FString FullUrl;` — rtsp://host:port/path
- L127 _private member_ `TUniquePtr<FSocket> Socket;`
- L128 _private member_ `TArray<uint8> ReceiveBuffer;`
- L129 _private member_ `TArray<uint8> ProcessBuffer;`
- L131 _private member_ `ERtspClientState State = ERtspClientState::Disconnected;`
- L132 _private member_ `mutable FCriticalSection StateLock;`
- L135 _private member_ `int32 CommandId = 0;` — CSeq (Command Sequence) number incremented per request
- L137 _private member_ `FString SessionId;`
- L138 _private member_ `int32 SessionTimeoutSeconds = 60;`
- L140 _private member_ `double KeepAliveInterval = 30.0;`
- L141 _private member_ `double LastKeepAlive = 0.0;`
- L143 _private member_ `FRtspRequestTracker RequestTracker;`
- L145 _private member_ `TUniquePtr<FSdpSession> SdpSession;`
- L147 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L148 _private member_ `std::atomic<bool> bStopping{false};`
- L151 _private member_ `TUniquePtr<FRtpJitterBuffer> JitterBuffer;` — Network jitter handling
- L152 _private member_ `TUniquePtr<FRtpJitterEstimator> JitterEstimator;`

#### Free symbols / members of external scopes

- L47 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRtspClientStateChanged, ERtspClientState, ERtspClientState);` — Executed on the game thread
- L47 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnRtspClientStateChanged, ERtspClientState, ERtspClientState);` — Executed on the game thread
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSdpSessionReceived, const FSdpSession&);`
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSdpSessionReceived, const FSdpSession&);`
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRtpPacketReceived, FRtpPacket);` — Executed on the client worker thread to minimise latency
- L51 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRtpPacketReceived, FRtpPacket);` — Executed on the client worker thread to minimise latency

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTSP/RtspMessage.h` (Private)


#### struct `FCaseInsensitiveMapKeyMatch`  
`struct FCaseInsensitiveMapKeyMatch : TDefaultMapHashableKeyFuncs<FString, FString, false>`  
_L13-24_
- inherits: `TDefaultMapHashableKeyFuncs<FString,FString,false>`
- desc: We need to handle the possibility that incoming message header names are using the incorrect case (E.g. 'cseq' instead of 'CSeq'). This custom KeyFuncs implementation will allow us to match names in a case-insensitive fashion.
- L15 _public function_ `static FORCEINLINE bool Matches(const FString& InA, const FString& InB)`
- L20 _public function_ `static FORCEINLINE uint32 GetKeyHash(const FString& InKey)`

#### enum `ERtspMessageType`  
`enum class ERtspMessageType`  
_L26-31_
- L28 _public enumerator_ `Unknown`
- L29 _public enumerator_ `Request`
- L30 _public enumerator_ `Response`

#### enum `ERtspRequestMethod`  
`enum class ERtspRequestMethod`  
_L33-47_
- L35 _public enumerator_ `Unknown`
- L36 _public enumerator_ `Options`
- L37 _public enumerator_ `Describe`
- L38 _public enumerator_ `Announce`
- L39 _public enumerator_ `Setup`
- L40 _public enumerator_ `Play`
- L41 _public enumerator_ `Pause`
- L42 _public enumerator_ `Teardown`
- L43 _public enumerator_ `GetParameter`
- L44 _public enumerator_ `SetParameter`
- L45 _public enumerator_ `Redirect`
- L46 _public enumerator_ `Record`

#### enum `ERtspMessageParseResult`  
`enum class ERtspMessageParseResult : uint8`  
_L49-54_
- L51 _public enumerator_ `Incomplete`
- L52 _public enumerator_ `Complete`
- L53 _public enumerator_ `Error`

#### class `FRtspMessage`  
`class FRtspMessage`  
_L56-113_
- L59 _public prototype_ `static FRtspMessage Request(const ERtspRequestMethod InMethod, const FString& InUrl, const int32 InCommandId);`
- L60 _public prototype_ `static FRtspMessage Response(const int32 InStatusCode, const FString& InReason, const int32 InCommandId);`
- L61 _public prototype_ `static ERtspMessageParseResult Parse(TArrayView<const uint8> InData, FRtspMessage& OutMessage, int32& OutBytesConsumed);`
- L63 _public prototype_ `static FString RequestMethodToString(const ERtspRequestMethod InMethod);`
- L64 _public prototype_ `static ERtspRequestMethod StringToRequestMethod(const FString& InString);`
- L66 _public prototype_ `ERtspMessageType GetMessageType() const;`
- L68 _public prototype_ `TOptional<int32> GetCommandId() const;`
- L70 _public prototype_ `TOptional<ERtspRequestMethod> GetRequestMethod() const;`
- L71 _public prototype_ `TOptional<FString> GetRequestUrl() const;`
- L72 _public prototype_ `TOptional<int32> GetResponseStatusCode() const;`
- L73 _public prototype_ `TOptional<FString> GetResponseReason() const;`
- L74 _public prototype_ `TOptional<FString> GetContentBaseUrl() const;`
- L75 _public prototype_ `int32 GetContentLength() const;`
- L76 _public prototype_ `TOptional<FString> GetHeaderValue(const FString& InName) const;`
- L77 _public prototype_ `TOptional<FString> GetSessionId() const;`
- L78 _public prototype_ `TOptional<int32> GetSessionTimeout() const;`
- L79 _public prototype_ `const FString& GetBody() const;`
- L81 _public prototype_ `void SetMessageType(const ERtspMessageType InMessageType);`
- L82 _public prototype_ `void SetCommandId(const int32 InCommandId);`
- L83 _public prototype_ `void SetHeader(const FString& InName, const FString& InValue);`
- L84 _public prototype_ `void SetSession(const FString& InSessionId);`
- L85 _public prototype_ `void SetTransport(const FRtspTransportConfiguration& InConfiguration);`
- L86 _public prototype_ `void SetAccept(const FString& InMimeType);`
- L87 _public prototype_ `void SetBody(const FString& InBody);`
- L89 _public prototype_ `void SetRequestMethod(const ERtspRequestMethod InMethod);`
- L90 _public prototype_ `void SetRequestUrl(const FString& InUrl);`
- L91 _public prototype_ `void SetResponseStatusCode(const int32 InStatusCode);`
- L92 _public prototype_ `void SetResponseReason(const FString& InReason);`
- L94 _public prototype_ `FString ToString() const;`
- L97 _private prototype_ `static bool ParseStartLine(const FString& InLine, FRtspMessage& OutMessage);`
- L98 _private prototype_ `static void ParseHeaderLine(const FString& InLine, FRtspMessage& OutMessage);`
- L100 _private member_ `ERtspMessageType MessageType = ERtspMessageType::Unknown;`
- L103 _private member_ `TOptional<ERtspRequestMethod> RequestMethod;` — Requests
- L104 _private member_ `TOptional<FString> RequestUrl;`
- L107 _private member_ `TOptional<int32> ResponseStatusCode;` — Responses
- L108 _private member_ `TOptional<FString> ResponseReason;`
- L110 _private member_ `TMap<FString, FString, FDefaultSetAllocator, FCaseInsensitiveMapKeyMatch> Headers;`
- L112 _private member_ `FString Body;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTSP/RtspRequestTracker.h` (Private)


#### struct `FRtspPendingRequest`  
`struct FRtspPendingRequest`  
_L9-13_
- L11 _public member_ `FRtspMessage Request;`
- L12 _public member_ `double SentTimestamp = 0.0;`

#### class `FRtspRequestTracker`  
`class FRtspRequestTracker`  
_L15-25_
- L18 _public prototype_ `void AddPendingRequest(int32 InCommandId, const FRtspPendingRequest& InRequest);`
- L19 _public prototype_ `bool HasPendingRequests() const;`
- L20 _public prototype_ `bool TakePendingRequest(const int32 CommandId, FRtspPendingRequest& OutRequest);`
- L21 _public prototype_ `TArray<FRtspPendingRequest> GetExpiredRequests(const double TimeoutSeconds);`
- L22 _public prototype_ `void Clear();`
- L24 _private member_ `TMap<int32, FRtspPendingRequest> PendingRequests;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RTSP/RtspTransportConfiguration.h` (Private)


#### struct `FRtspTransportConfiguration`  
`struct FRtspTransportConfiguration`  
_L7-27_
- L15 _public member_ `TransportProtocol Protocol = TransportProtocol::TCP;`
- L17 _public member_ `int32 TcpInterleavedRtpChannel = 0;`
- L18 _public member_ `int32 TcpInterleavedRtcpChannel = 1;`
- L20 _public member_ `int32 UdpClientRtpPort = 0;`
- L21 _public member_ `int32 UdpClientRtcpPort = 0;`
- L23 _public prototype_ `static FRtspTransportConfiguration TcpInterleaved(int32 InRtpChannel, int32 InRtcpChannel);`
- L24 _public prototype_ `static FRtspTransportConfiguration Udp(int32 InClientRtpPort, int32 InClientRtcpPort);`
- L26 _public prototype_ `FString BuildHeader() const;`

#### enum `FRtspTransportConfiguration::TransportProtocol`  
`enum class TransportProtocol`  
_L9-13_
- L11 _public enumerator_ `TCP`
- L12 _public enumerator_ `UDP`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/RtspMediaConstants.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRtspMedia, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRtspMedia, Log, All);`
- L11 _namespace_ `namespace RtspMedia`
- L13 _variable_ `inline const FName PlayerName(TEXT("RTSP` (scope `RtspMedia`)
- L14 _variable_ `inline constexpr FGuid PlayerPluginGUID(0x690B0293, 0x4C784EBF, 0xAF4769FF, 0x104000BD);` (scope `RtspMedia`)
- L16 _namespace_ `namespace Option` (scope `RtspMedia`)
- L18 _variable_ `inline const FName AutoReconnect("Aut` (scope `RtspMedia::Option`)
- L19 _variable_ `inline const FName ProvideCpuBuffer("Pro` (scope `RtspMedia::Option`)
- L20 _variable_ `inline const FName DecoderBufferSize("Dec` (scope `RtspMedia::Option`)
- L21 _variable_ `inline const FName DecoderPollIntervalMs("Dec` (scope `RtspMedia::Option`)
- L22 _variable_ `inline const FName JitterBufferAutoAdjust("Jit` (scope `RtspMedia::Option`)
- L23 _variable_ `inline const FName JitterBufferDepthMs("Jit` (scope `RtspMedia::Option`)
- L24 _variable_ `inline const FName JitterBufferObservationWindowSeconds("Jit` (scope `RtspMedia::Option`)
- L25 _variable_ `inline const FName MaxFragmentBufferSize("Max` (scope `RtspMedia::Option`)
- L26 _variable_ `inline const FName MaxQueuedVideoSamples("Max` (scope `RtspMedia::Option`)
- L27 _variable_ `inline const FName MaxReconnectAttempts("Max` (scope `RtspMedia::Option`)
- L28 _variable_ `inline const FName MaxReconnectDelaySeconds("Max` (scope `RtspMedia::Option`)
- L29 _variable_ `inline const FName MinReconnectDelaySeconds("Min` (scope `RtspMedia::Option`)
- L30 _variable_ `inline const FName RequestTimeoutSeconds("Req` (scope `RtspMedia::Option`)
- L31 _variable_ `inline const FName SocketBufferSize("Soc` (scope `RtspMedia::Option`)
- L32 _variable_ `inline const FName TransportProtocol("Tra` (scope `RtspMedia::Option`)

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/SDP/SdpParser.h` (Private)


#### class `FSdpParser`  
`class FSdpParser`  
_L10-24_
- L13 _public prototype_ `static TUniquePtr<FSdpSession> Parse(const FString& InSdpBody, const FString& InContentBaseUrl);`
- L16 _private prototype_ `static bool ParseMediaLine(const FString& InMediaLine, FSdpMediaTrack& OutMediaTrack);`
- L17 _private prototype_ `static bool ParseAttributeLine(const FString& InAttributeLine, FSdpMediaTrack& InMediaTrack);`
- L18 _private prototype_ `static bool ParseRtpMap(const FString& InRtpMap, FSdpMediaTrack& InTrack);`
- L19 _private prototype_ `static bool ParseFormatParameters(const FString& InFormatParameters, FSdpMediaTrack& InTrack);`
- L20 _private prototype_ `static bool ParseH264StreamPropertyParameterSets(const FString& InH264StreamPropertyParameterSets, FSdpMediaTrack& InTrack);`
- L22 _private prototype_ `static bool Base64Decode(const FString& InBase64EncodedString, TArray<uint8>& OutBuffer);`
- L23 _private prototype_ `static bool HexDecode(const FString& InHexEncodedString, TArray<uint8>& OutBuffer);`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Private/SDP/SdpSession.h` (Private)


#### struct `FSdpMediaTrack`  
`struct FSdpMediaTrack`  
_L7-38_
- L11 _public member_ `FString MediaType;` — Media Description "m=video 0 RTP/AVP 96"
- L12 _public member_ `int32 Port = 0;`
- L13 _public member_ `FString Protocol;`
- L14 _public member_ `int32 PayloadType = 0;`
- L18 _public member_ `FString Codec;` — Codec (Attribute) "a=rtpmap:96 H264/90000"
- L19 _public member_ `uint32 ClockRate = 0;`
- L20 _public member_ `int32 Channels = 0;`
- L25 _public member_ `FString ControlUrl;` — Control URL (Attribute) "a=control:track1" (relative) "a=control:rtsp://host/path/track1" (absolute)
- L29 _public member_ `FString FormatParameters;` — Format Parameters (Attribute) "a=fmtp: <params>"
- L32 _public member_ `TArray<uint8> SequenceParameterSet;` — H.264 Specific Parameters
- L33 _public member_ `TArray<uint8> PictureParameterSet;`
- L34 _public member_ `int32 PacketizationMode = 0;`
- L37 _public member_ `TArray<uint8> AudioConfig;` — AAC Specific Parameters

#### struct `FSdpSession`  
`struct FSdpSession`  
_L40-60_
- L43 _public member_ `FString SessionName;` — "s=<session_name>"
- L46 _public member_ `FString SessionInfo;` — "i=<session_info>"
- L50 _public member_ `FString ContentBaseUrl;` — Provides the base URL of the stream content. A track may be located at <ContentBase>/trackID=0
- L52 _public member_ `TArray<FSdpMediaTrack> VideoTracks;`
- L53 _public member_ `TArray<FSdpMediaTrack> AudioTracks;`
- L55 _public prototype_ `bool HasVideo() const;`
- L56 _public prototype_ `bool HasAudio() const;`
- L57 _public prototype_ `const FSdpMediaTrack* GetFirstVideoTrack() const;`
- L58 _public prototype_ `const FSdpMediaTrack* GetFirstAudioTrack() const;`
- L59 _public prototype_ `FString ResolveControlUrl(const FString& InControlUrl) const;`

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Public/RtspMediaDefaults.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace RtspMedia`
- L7 _namespace_ `namespace Default` (scope `RtspMedia`)
- L9 _variable_ `inline constexpr bool bAutoReconnect = true;` (scope `RtspMedia::Default`)
- L10 _variable_ `inline constexpr bool bProvideCpuBuffer = true;` (scope `RtspMedia::Default`)
- L11 _variable_ `inline constexpr int32 DecoderBufferSize = 5;` (scope `RtspMedia::Default`)
- L12 _variable_ `inline constexpr int32 DecoderPollIntervalMs = 5;` (scope `RtspMedia::Default`)
- L13 _variable_ `inline constexpr int32 DecoderLagThresholdMs = 1000;` (scope `RtspMedia::Default`)
- L14 _variable_ `inline constexpr bool bJitterBufferAutoAdjust = true;` (scope `RtspMedia::Default`)
- L15 _variable_ `inline constexpr uint32 JitterBufferDepthMs = 1000;` (scope `RtspMedia::Default`)
- L16 _variable_ `inline constexpr float JitterBufferObservationWindowSeconds = 60.0f;` (scope `RtspMedia::Default`)
- L17 _variable_ `inline constexpr int32 MaxFragmentBufferSizeMb = 8;` (scope `RtspMedia::Default`)
- L18 _variable_ `inline constexpr int64 MaxFragmentBufferSizeBytes = MaxFragmentBufferSizeMb * 1024 * 1024;` (scope `RtspMedia::Default`)
- L19 _variable_ `inline constexpr int32 MaxQueuedVideoSamples = 4;` (scope `RtspMedia::Default`)
- L20 _variable_ `inline constexpr int32 MaxQueuedAudioSamples = 4;` (scope `RtspMedia::Default`)
- L21 _variable_ `inline constexpr int32 MaxReconnectAttempts = 0;` (scope `RtspMedia::Default`)
- L22 _variable_ `inline constexpr float MaxReconnectDelaySeconds = 30.0;` (scope `RtspMedia::Default`)
- L23 _variable_ `inline constexpr float MinReconnectDelaySeconds = 1.0;` (scope `RtspMedia::Default`)
- L24 _variable_ `inline constexpr int32 Port = 8554;` (scope `RtspMedia::Default`)
- L25 _variable_ `inline constexpr float RequestTimeoutSeconds = 5.0;` (scope `RtspMedia::Default`)
- L26 _variable_ `inline constexpr int32 SocketBufferSizeKb = 512;` (scope `RtspMedia::Default`)
- L27 _variable_ `inline constexpr int32 SocketBufferSizeBytes = SocketBufferSizeKb * 1024;` (scope `RtspMedia::Default`)

### `Plugins/Media/RTSPMedia/Source/RTSPMedia/Public/RtspMediaSource.h` (Public)


#### enum `ERtspMediaTransportProtocol`  
`enum class ERtspMediaTransportProtocol : uint8`  
_L12-16_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `TCP` — RTP packets are interleaved with RTSP control messages

#### class `URtspMediaSource`  
`class URtspMediaSource : public UBaseMediaSource`  
_L24-132_
- reflection: `UCLASS(BlueprintType, hideCategories=(Platforms, Object), meta=(DisplayName="RTSP Media Source"))`
- inherits: `UBaseMediaSource`
- L32 _public member_ `FString Host;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server")` — Host name or IP address of the RTSP server
- L36 _public member_ `int32 Port = RtspMedia::Default::Port;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server", meta=(ClampMin="1", ClampMax="65535"))` — Port number of the RTSP Server
- L40 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Server")` — Path to the stream on RTSP server
- L44 _public member_ `ERtspMediaTransportProtocol TransportProtocol = RtspMedia::Default::TransportProtocol;` — `UPROPERTY(BlueprintReadOnly, Category="Client", meta=(Hidden))` — Only TCP interleaved transport is supported
- L49 _public member_ `int32 SocketBufferSizeKb = RtspMedia::Default::SocketBufferSizeKb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Client", meta=(DisplayName="Socket Buffer Size (KB)", ClampMin="128", ClampMax="4096"))` — Socket buffer size for stream data in KB. Increase this setting for high bitrate streams (e.g. 4K)
- L54 _public member_ `float RequestTimeoutSeconds = RtspMedia::Default::RequestTimeoutSeconds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Client", meta=(DisplayName="Request Timeout (s)", ClampMin="1.0", ClampMax="30.0"))` — RTSP request timeout in seconds. Increase for slow or unreliable networks to avoid premature session failures
- L59 _public member_ `bool bAutoReconnect = RtspMedia::Default::bAutoReconnect;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Client")` — Automatically reconnect when the connection fails The player will begin reconnection attempts after the delay specified in Min Retry Delay
- L63 _public member_ `float MinReconnectDelaySeconds = RtspMedia::Default::MinReconnectDelaySeconds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Client", meta=(DisplayName="Min Reconnect Delay (s)", EditCondition="bAutoReconnect", ClampMin="1.0", ClampMax="60.0"))` — The minimum amount of time to wait before attempting to reconnect after a connection failure
- L68 _public member_ `float MaxReconnectDelaySeconds = RtspMedia::Default::MaxReconnectDelaySeconds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Client", meta=(DisplayName="Max Reconnect Delay (s)", EditCondition="bAutoReconnect", ClampMin="1.0", ClampMax="300.0"))` — The maximum amount of time to wait before attempting to reconnect after a connection failure The player will gradually increase the delay before each connection attempt but for no longer than this maximum
- L73 _public member_ `int32 MaxReconnectAttempts = RtspMedia::Default::MaxReconnectAttempts;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Client", meta=(EditCondition="bAutoReconnect", ClampMin="0", ClampMax="1000"))` — The maximum number of times the player will attempt to reconnect after a connection failure Set to 0 to retry indefinitely
- L79 _public member_ `bool bJitterBufferAutoAdjust = RtspMedia::Default::bJitterBufferAutoAdjust;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jitter Buffer", meta=(DisplayName="Auto Adjust"))` — The jitter buffer accounts for spikes in the network delivery of RTP packets in order to provide a steady stream of packets to the decoder. This setting automatically adjusts the jitter buffer depth based on network conditions. When disabled, the static Depth value is used.
- L84 _public member_ `int32 JitterBufferDepthMs = RtspMedia::Default::JitterBufferDepthMs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jitter Buffer", meta=(DisplayName="Depth (ms)", EditCondition="!bJitterBufferAutoAdjust", EditConditionHides, ClampMin="0", ClampMax="5000"))` — A higher buffer depth will absorb more network jitter at the cost of additional latency. On clean networks a low or zero value may be configured which will minimize the latency introduced by the buffer.
- L89 _public member_ `float JitterBufferObservationWindowSeconds = RtspMedia::Default::JitterBufferObservationWindowSeconds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jitter Buffer", meta=(DisplayName="Observation Window (s)", EditCondition="bJitterBufferAutoAdjust", EditConditionHides, ClampMin="30.0", ClampMax="300.0"))` — How long network conditions must remain stable before the jitter buffer depth is reduced. Longer windows provide more protection against intermittent spikes.
- L95 _public member_ `int32 MaxFragmentBufferSizeMb = RtspMedia::Default::MaxFragmentBufferSizeMb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Depacketization", meta=(DisplayName="Max Fragment Buffer Size (MB)", ClampMin="2", ClampMax="64"))` — Places a limit on how much memory is used for fragmented NAL unit reassembly NAL units will be dropped if this memory limit is exceeded Consider increasing this value for high bitrate streams
- L100 _public member_ `int32 DecoderBufferSize = RtspMedia::Default::DecoderBufferSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decoder", meta=(DisplayName="Buffer Size (frames)", ClampMin="1", ClampMax="16"))` — Decoder reorder buffer size. Use 1 for minimum latency (i.e. no B-frames) Increase if video frames appears out of order
- L105 _public member_ `int32 DecoderPollIntervalMs = RtspMedia::Default::DecoderPollIntervalMs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decoder", meta=(DisplayName="Poll Interval (ms)", ClampMin="1", ClampMax="10"))` — How frequently to poll the decoder for output frames (in milliseconds) Lower values reduce latency but increase CPU usage
- L110 _public member_ `int32 MaxQueuedVideoSamples = RtspMedia::Default::MaxQueuedVideoSamples;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Decoder", meta=(ClampMin="2", ClampMax="16"))` — Maximum decoded video frames to queue while waiting for game thread consumption Higher values reduce visible skips after game thread hitches at the cost of memory
- L115 _public member_ `bool bProvideCpuBuffer = RtspMedia::Default::bProvideCpuBuffer;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Decoder", meta=(DisplayName="Provide CPU Buffer"))` — Populate a CPU-accessible pixel buffer alongside the GPU texture Whether this is available depends on the underlying decoder implementation
- L118 _public prototype_ `virtual FString GetUrl() const override;`
- L119 _public prototype_ `virtual bool Validate() const override;`
- L123 _public prototype_ `virtual bool GetMediaOption(const FName& InKey, bool InDefaultValue) const override;`
- L124 _public prototype_ `virtual int64 GetMediaOption(const FName& InKey, int64 InDefaultValue) const override;`
- L125 _public prototype_ `virtual double GetMediaOption(const FName& InKey, double InDefaultValue) const override;`
- L126 _public prototype_ `virtual bool HasMediaOption(const FName& InKey) const override;`
- L130 _public prototype_ `virtual FName GetDesiredPlayerName() const override;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace RtspMedia`
- L18 _namespace_ `namespace Default` (scope `RtspMedia`)
- L20 _variable_ `inline constexpr ERtspMediaTransportProtocol TransportProtocol = ERtspMediaTransportProtocol::TCP;` (scope `RtspMedia::Default`)
