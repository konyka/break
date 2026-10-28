# Plugins / ElectraPlayerRuntime

- module root: `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime`
- headers: 97; symbols: 7518
- symbol kinds: class=223, delegate=16, enum=118, enumerator=604, externvar=1, function=1529, macro=18, member=2483, namespace=112, prototype=2013, struct=246, typedef=49, variable=106
- PrivateDependencyModuleNames: Core, ElectraBase, ElectraCDM, ElectraCodecFactory, ElectraDecoders, ElectraHTTPStream, ElectraSamples, ElectraSubtitles, Engine, HTTP, Json, MP4Boxes, MP4Utilities, Media, MediaUtils, MetalRHI, RHI, RenderCore, SoundTouchZ, XmlParser
- PublicDependencyModuleNames: DirectX

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/ElectraPlayer.h` (Private)


#### class `FElectraPlayer`  
`class FElectraPlayer : public IMediaPlayer , public IMediaCache , public IMediaControls , public IMediaTracks , public IMediaView , public IAdaptiveStreamingPlayerMetrics , public TSharedFromThis<FElectraPlayer, ESPMode::ThreadSafe>`  
_L48-784_
- inherits: `IMediaPlayer,IMediaCache,IMediaControls,IMediaTracks,IMediaView,IAdaptiveStreamingPlayerMetrics,TSharedFromThis<FElectraPlayer,ESPMode::ThreadSafe>`
- L58 _public prototype_ `FElectraPlayer(IMediaEventSink& InEventSink, FElectraPlayerSendAnalyticMetricsDelegate& InSendAnalyticMetricsDelegate, FElectraPlayerSendAnalyticMetricsPerMinuteDelegate& InSendAnalyticMetricsPerMinuteDelegate, FElectraPlayerReportVideoStreamingErrorDelegate& InReportVideoStreamingErrorDelegate, FElectraPlayerReportSubtitlesMetricsDelegate& InReportSubtitlesFileMetricsDelegate);`
- L63 _public prototype_ `virtual ~FElectraPlayer();`
- L68 _public prototype_ `void Close() override;` — Methods from IMediaPlayer
- L69 _public function_ `IMediaCache& GetCache() override`
- L71 _public function_ `IMediaControls& GetControls() override`
- L73 _public prototype_ `FString GetInfo() const override;`
- L74 _public prototype_ `FGuid GetPlayerPluginGUID() const override;`
- L75 _public prototype_ `IMediaSamples& GetSamples() override;`
- L76 _public prototype_ `FString GetStats() const override;`
- L77 _public function_ `IMediaTracks& GetTracks() override`
- L79 _public prototype_ `FString GetUrl() const override;`
- L80 _public function_ `IMediaView& GetView() override`
- L82 _public prototype_ `bool Open(const FString& InUrl, const IMediaOptions* InOptions) override;`
- L83 _public prototype_ `bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& InArchive, const FString& InOriginalUrl, const IMediaOptions* InOptions) override;`
- L84 _public prototype_ `bool Open(const FString& InUrl, const IMediaOptions* InOptions, const FMediaPlayerOptions* InPlayerOptions) override;`
- L85 _public prototype_ `FVariant GetMediaInfo(FName InInfoName) const override;`
- L86 _public prototype_ `TSharedPtr<TMap<FString, TArray<TUniquePtr<IMediaMetadataItem>>>, ESPMode::ThreadSafe> GetMediaMetadata() const override;`
- L87 _public prototype_ `void SetGuid(const FGuid& InGuid) override;`
- L88 _public prototype_ `void TickInput(FTimespan InDeltaTime, FTimespan InTimecode) override;`
- L89 _public prototype_ `bool FlushOnSeekStarted() const override;`
- L90 _public prototype_ `bool FlushOnSeekCompleted() const override;`
- L91 _public prototype_ `bool GetPlayerFeatureFlag(EFeatureFlag InFlag) const override;`
- L92 _public prototype_ `bool SetAsyncResourceReleaseNotification(IAsyncResourceReleaseNotificationRef InAsyncDestructNotification) override;`
- L93 _public prototype_ `uint32 GetNewResourcesOnOpen() const override;`
- L98 _public prototype_ `bool QueryCacheState(EMediaCacheState InState, TRangeSet<FTimespan>& OutTimeRanges) const override;` — Methods from IMediaCache
- L103 _public prototype_ `bool CanControl(EMediaControl InControl) const override;` — Methods from IMediaControls
- L104 _public prototype_ `FTimespan GetDuration() const override;`
- L105 _public prototype_ `float GetRate() const override;`
- L106 _public prototype_ `EMediaState GetState() const override;`
- L107 _public prototype_ `EMediaStatus GetStatus() const override;`
- L108 _public prototype_ `TRangeSet<float> GetSupportedRates(EMediaRateThinning InThinning) const override;`
- L109 _public prototype_ `FTimespan GetTime() const override;`
- L110 _public prototype_ `bool IsLooping() const override;`
- L111 _public function_ `bool Seek(const FTimespan& InTime) override`
- L113 _public prototype_ `bool SetLooping(bool bInLooping) override;`
- L114 _public prototype_ `bool SetRate(float InRate) override;`
- L115 _public prototype_ `bool Seek(const FTimespan& InNewTime, const FMediaSeekParams& InAdditionalParams) override;`
- L116 _public prototype_ `TRange<FTimespan> GetPlaybackTimeRange(EMediaTimeRangeType InRangeToGet) const override;`
- L117 _public prototype_ `bool SetPlaybackTimeRange(const TRange<FTimespan>& InTimeRange) override;`
- L122 _public prototype_ `bool GetAudioTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaAudioTrackFormat& OutFormat) const override;` — Methods from IMediaTracks
- L123 _public prototype_ `int32 GetNumTracks(EMediaTrackType InTrackType) const override;`
- L124 _public prototype_ `int32 GetNumTrackFormats(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L125 _public prototype_ `int32 GetSelectedTrack(EMediaTrackType InTrackType) const override;`
- L126 _public prototype_ `FText GetTrackDisplayName(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L127 _public prototype_ `int32 GetTrackFormat(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L128 _public prototype_ `FString GetTrackLanguage(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L129 _public prototype_ `FString GetTrackName(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L130 _public prototype_ `bool GetVideoTrackFormat(int32 InTrackIndex, int32 InFormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L131 _public prototype_ `bool SelectTrack(EMediaTrackType InTrackType, int32 InTrackIndex) override;`
- L132 _public prototype_ `bool SetTrackFormat(EMediaTrackType InTrackType, int32 InTrackIndex, int32 InFormatIndex) override;`
- L133 _public prototype_ `bool SetVideoTrackFrameRate(int32 InTrackIndex, int32 InFormatIndex, float InFrameRate) override;`
- L134 _public prototype_ `TOptional<FTimespan> GetTrackDuration(EMediaTrackType InTrackType, int32 InTrackIndex) const override;`
- L139 _public prototype_ `void ReportOpenSource(const FString& InURL) override;` — Methods from IAdaptiveStreamingPlayerMetrics
- L140 _public prototype_ `void ReportReceivedMainPlaylist(const FString& InEffectiveURL) override;`
- L141 _public prototype_ `void ReportReceivedPlaylists() override;`
- L142 _public prototype_ `void ReportTracksChanged() override;`
- L143 _public prototype_ `void ReportPlaylistDownload(const Metrics::FPlaylistDownloadStats& InPlaylistDownloadStats) override;`
- L144 _public prototype_ `void ReportBufferingStart(Metrics::EBufferingReason InBufferingReason) override;`
- L145 _public prototype_ `void ReportBufferingEnd(Metrics::EBufferingReason InBufferingReason) override;`
- L146 _public prototype_ `void ReportBandwidth(int64 InEffectiveBps, int64 InThroughputBps, double InLatencyInSeconds) override;`
- L147 _public prototype_ `void ReportBufferUtilization(const Metrics::FBufferStats& InBufferStats) override;`
- L148 _public prototype_ `void ReportSegmentDownload(const Metrics::FSegmentDownloadStats& InSegmentDownloadStats) override;`
- L149 _public prototype_ `void ReportLicenseKey(const Metrics::FLicenseKeyStats& InLicenseKeyStats) override;`
- L150 _public prototype_ `void ReportDataAvailabilityChange(const Metrics::FDataAvailabilityChange& InDataAvailability) override;`
- L151 _public prototype_ `void ReportVideoQualityChange(int32 InNewBitrate, int32 InPreviousBitrate, bool bInIsDrasticDownswitch) override;`
- L152 _public prototype_ `void ReportAudioQualityChange(int32 InNewBitrate, int32 InPreviousBitrate, bool bInIsDrasticDownswitch) override;`
- L153 _public prototype_ `void ReportDecodingFormatChange(const FStreamCodecInformation& InNewDecodingFormat) override;`
- L154 _public prototype_ `void ReportPrerollStart() override;`
- L155 _public prototype_ `void ReportPrerollEnd() override;`
- L156 _public prototype_ `void ReportPlaybackStart() override;`
- L157 _public prototype_ `void ReportPlaybackPaused() override;`
- L158 _public prototype_ `void ReportPlaybackResumed() override;`
- L159 _public prototype_ `void ReportPlaybackEnded() override;`
- L160 _public prototype_ `void ReportJumpInPlayPosition(const FTimeValue& InToNewTime, const FTimeValue& InFromTime, Metrics::ETimeJumpReason InTimejumpReason) override;`
- L161 _public prototype_ `void ReportPlaybackStopped() override;`
- L162 _public prototype_ `void ReportSeekCompleted() override;`
- L163 _public prototype_ `void ReportMediaMetadataChanged(TSharedPtrTS<Electra::FMetadataParser> InMetadata) override;`
- L164 _public prototype_ `void ReportError(const FString& InErrorReason) override;`
- L165 _public prototype_ `void ReportLogMessage(IInfoLog::ELevel InLogLevel, const FString& InLogMessage, int64 InPlayerWallclockMilliseconds) override;`
- L166 _public prototype_ `void ReportVideoFrameStats(const Metrics::FFrameStats& InFrameStats) override;`
- L167 _public prototype_ `void ReportAudioFrameStats(const Metrics::FFrameStats& InFrameStats) override;`
- L173 _public prototype_ `void PlatformSuspendOrResumeDecoders(bool bInSuspend, const Electra::FParamDict& InOptions);` — Implementation methods
- L175 _public prototype_ `void SendAnalyticMetrics(const TSharedPtr<IAnalyticsProviderET>& InAnalyticsProvider, const FGuid& InPlayerGuid);`
- L176 _public prototype_ `void SendAnalyticMetricsPerMinute(const TSharedPtr<IAnalyticsProviderET>& InAnalyticsProvider);`
- L177 _public prototype_ `void SendPendingAnalyticMetrics(const TSharedPtr<IAnalyticsProviderET>& InAnalyticsProvider);`
- L178 _public prototype_ `void ReportVideoStreamingError(const FGuid& InPlayerGuid, const FString& InLastError);`
- L179 _public prototype_ `void ReportSubtitlesMetrics(const FGuid& InPlayerGuid, const FString& InURL, double InResponseTime, const FString& InLastError);`
- L183 _private prototype_ `void ClearToDefaultState();`
- L184 _private prototype_ `void SendMediaSinkEvent(EMediaEvent InEventToSend);`
- L185 _private prototype_ `bool OpenInternal(const FString& InUrl, const IMediaOptions* InOptions, const FMediaPlayerOptions* InPlayerOptions);`
- L186 _private prototype_ `void CloseInternal();`
- L187 _private prototype_ `void TickInternal(FTimespan InDeltaTime, FTimespan InTimecode);`
- L188 _private prototype_ `void TriggerFirstSeekIfNecessary();`
- L189 _private prototype_ `void CalculateTargetSeekTime(FTimespan& OutTargetTime, const FTimespan& InTime);`
- L190 _private prototype_ `bool IsLive();`
- L191 _private prototype_ `TSharedPtr<FTrackMetadata, ESPMode::ThreadSafe> GetTrackStreamMetadata(EMediaTrackType InTrackType, int32 InTrackIndex) const;`
- L192 _private prototype_ `void AddCommonAnalyticsAttributes(TArray<FAnalyticsEventAttribute>& InOutParamArray);`
- L193 _private prototype_ `TSharedPtr<FAnalyticsEvent> CreateAnalyticsEvent(FString InEventName);`
- L194 _private prototype_ `void EnqueueAnalyticsEvent(TSharedPtr<FAnalyticsEvent> InAnalyticEvent);`
- L195 _private prototype_ `void UpdateAnalyticsCustomValues();`
- L196 _private prototype_ `void UpdatePlayEndStatistics();`
- L197 _private prototype_ `void LogStatistics();`
- L198 _private prototype_ `void OnMediaPlayerEventReceived(TSharedPtr<IAdaptiveStreamingPlayerAEMSEvent, ESPMode::ThreadSafe> InEvent, IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode InDispatchMode);`
- L199 _private prototype_ `void HandleDeferredPlayerEvents();`
- L200 _private prototype_ `void HandlePlayerEventOpenSource(const FString& InURL);`
- L201 _private prototype_ `void HandlePlayerEventReceivedMainPlaylist(const FString& InEffectiveURL);`
- L202 _private prototype_ `void HandlePlayerEventReceivedPlaylists();`
- L203 _private prototype_ `void HandlePlayerEventTracksChanged();`
- L204 _private prototype_ `void HandlePlayerEventPlaylistDownload(const Metrics::FPlaylistDownloadStats& InPlaylistDownloadStats);`
- L205 _private prototype_ `void HandlePlayerEventBufferingStart(Metrics::EBufferingReason InBufferingReason);`
- L206 _private prototype_ `void HandlePlayerEventBufferingEnd(Metrics::EBufferingReason InBufferingReason);`
- L207 _private prototype_ `void HandlePlayerEventBandwidth(int64 InEffectiveBps, int64 InThroughputBps, double InLatencyInSeconds);`
- L208 _private prototype_ `void HandlePlayerEventBufferUtilization(const Metrics::FBufferStats& InBufferStats);`
- L209 _private prototype_ `void HandlePlayerEventSegmentDownload(const Metrics::FSegmentDownloadStats& InSegmentDownloadStats);`
- L210 _private prototype_ `void HandlePlayerEventLicenseKey(const Metrics::FLicenseKeyStats& InLicenseKeyStats);`
- L211 _private prototype_ `void HandlePlayerEventDataAvailabilityChange(const Metrics::FDataAvailabilityChange& InDataAvailability);`
- L212 _private prototype_ `void HandlePlayerEventVideoQualityChange(int32 InNewBitrate, int32 InPreviousBitrate, bool bInIsDrasticDownswitch);`
- L213 _private prototype_ `void HandlePlayerEventAudioQualityChange(int32 InNewBitrate, int32 InPreviousBitrate, bool bInIsDrasticDownswitch);`
- L214 _private prototype_ `void HandlePlayerEventCodecFormatChange(const Electra::FStreamCodecInformation& InNewDecodingFormat);`
- L215 _private prototype_ `void HandlePlayerEventPrerollStart();`
- L216 _private prototype_ `void HandlePlayerEventPrerollEnd();`
- L217 _private prototype_ `void HandlePlayerEventPlaybackStart();`
- L218 _private prototype_ `void HandlePlayerEventPlaybackPaused();`
- L219 _private prototype_ `void HandlePlayerEventPlaybackResumed();`
- L220 _private prototype_ `void HandlePlayerEventPlaybackEnded();`
- L221 _private prototype_ `void HandlePlayerEventJumpInPlayPosition(const FTimeValue& InToNewTime, const FTimeValue& InFromTime, Metrics::ETimeJumpReason InTimejumpReason);`
- L222 _private prototype_ `void HandlePlayerEventPlaybackStopped();`
- L223 _private prototype_ `void HandlePlayerEventSeekCompleted();`
- L224 _private prototype_ `void HandlePlayerMediaMetadataChanged(const TSharedPtrTS<Electra::FMetadataParser>& InMetadata);`
- L225 _private prototype_ `void HandlePlayerEventError(const FString& InErrorReason);`
- L226 _private prototype_ `void HandlePlayerEventLogMessage(IInfoLog::ELevel InLogLevel, const FString& InLogMessage, int64 InPlayerWallclockMilliseconds);`
- L227 _private prototype_ `void HandlePlayerEventDroppedVideoFrame(const Metrics::FFrameStats& InFrameStats);`
- L228 _private prototype_ `void HandlePlayerEventDroppedAudioFrame(const Metrics::FFrameStats& InFrameStats);`
- L229 _private prototype_ `void MediaStateOnPreparingFinished();`
- L230 _private prototype_ `bool MediaStateOnPlay();`
- L231 _private prototype_ `bool MediaStateOnPause();`
- L232 _private prototype_ `void MediaStateOnEndReached();`
- L233 _private prototype_ `void MediaStateOnSeekFinished();`
- L237 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnMediaPlayerEventReceivedDelegate, TSharedPtrTS<IAdaptiveStreamingPlayerAEMSEvent> , IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode );`
- L704 _private member_ `IMediaEventSink* EventSink = nullptr;` — Media event sink
- L707 _private member_ `FElectraPlayerSendAnalyticMetricsDelegate& SendAnalyticMetricsDelegate;` — Metric delegates
- L708 _private member_ `FElectraPlayerSendAnalyticMetricsPerMinuteDelegate& SendAnalyticMetricsPerMinuteDelegate;`
- L709 _private member_ `FElectraPlayerReportVideoStreamingErrorDelegate& ReportVideoStreamingErrorDelegate;`
- L710 _private member_ `FElectraPlayerReportSubtitlesMetricsDelegate& ReportSubtitlesMetricsDelegate;`
- L713 _private member_ `TUniquePtr<FMediaSamples> EmptyMediaSamples;` — Empty sample queue
- L716 _private member_ `TWeakPtr<IElectraSafeMediaOptionInterface, ESPMode::ThreadSafe> OptionInterface;` — Option interface
- L719 _private member_ `mutable TSharedPtr<TMap<FString, TArray<TUniquePtr<IMediaMetadataItem>>>, ESPMode::ThreadSafe> CurrentMetadata;` — Current player stream metadata
- L720 _private member_ `mutable bool bMetadataChanged = false;`
- L723 _private member_ `TSharedPtr<FElectraTextureSamplePool, ESPMode::ThreadSafe> OutputTexturePool;` — Output sample pools
- L724 _private member_ `int64 OutputTexturePoolDecoderID = 0;`
- L725 _private member_ `TSharedPtr<FElectraAudioSamplePool, ESPMode::ThreadSafe> OutputAudioSamplePool;`
- L726 _private member_ `bool bRetainPoolsForReuse = false;`
- L729 _private member_ `TSharedPtr<Electra::FApplicationTerminationHandler, ESPMode::ThreadSafe> AppTerminationHandler;` — Application system event handler
- L732 _private member_ `FGuid PlayerGuid;` — Media player Guid
- L733 _private member_ `uint32 PlayerUniqueID = 0;`
- L734 _private member_ `static std::atomic<uint32> NextPlayerUniqueID;`
- L737 _private member_ `TQueue<TSharedPtr<FAnalyticsEvent>> QueuedAnalyticEvents;` — Analytics
- L738 _private member_ `FString AnalyticsCustomValues[8];`
- L739 _private member_ `FString AnalyticsOSVersion;`
- L740 _private member_ `FString AnalyticsGPUType;`
- L741 _private member_ `FString AnalyticsInstanceGuid;`
- L742 _private member_ `uint32 AnalyticsInstanceEventCount;`
- L743 _private member_ `std::atomic<int32> NumQueuedAnalyticEvents { 0 };`
- L746 _private member_ `FCriticalSection StatisticsLock;` — Statistics
- L747 _private member_ `FStatistics Statistics;`
- L750 _private member_ `TSharedPtr<FAdaptiveStreamingPlayerResourceProvider, ESPMode::ThreadSafe> StaticResourceProvider;` — External resource provider.
- L753 _private member_ `FPlaystartOptions PlaystartOptions;` — Internal states.
- L754 _private member_ `FString MediaUrl;`
- L755 _private member_ `TOptional<bool> bFrameAccurateSeeking;`
- L756 _private member_ `TOptional<bool> bEnableLooping;`
- L758 _private member_ `TQueue<TSharedPtrTS<FPlayerMetricEventBase>> DeferredPlayerEvents;`
- L759 _private member_ `TQueue<EMediaEvent> DeferredMediaEvents;`
- L760 _private member_ `mutable FCriticalSection VideoFormatLock;`
- L761 _private member_ `FVideoStreamFormat CurrentlyActiveVideoStreamFormat;`
- L762 _private member_ `int32 NumTracksAudio = 0;`
- L763 _private member_ `int32 NumTracksVideo = 0;`
- L764 _private member_ `int32 NumTracksSubtitle = 0;`
- L765 _private member_ `int32 SelectedQuality = 0;`
- L766 _private member_ `mutable int32 SelectedVideoTrackIndex = -1;`
- L767 _private member_ `mutable int32 SelectedAudioTrackIndex = -1;`
- L768 _private member_ `mutable int32 SelectedSubtitleTrackIndex = -1;`
- L769 _private member_ `mutable bool bVideoTrackIndexDirty = true;`
- L770 _private member_ `mutable bool bAudioTrackIndexDirty = true;`
- L771 _private member_ `mutable bool bSubtitleTrackIndexDirty = true;`
- L772 _private member_ `bool bInitialSeekPerformed = false;`
- L773 _private member_ `bool bIsFirstBuffering = true;`
- L774 _private member_ `TSharedPtr<TMap<FString, TArray<TUniquePtr<IMediaMetadataItem>>>, ESPMode::ThreadSafe> CurrentStreamMetadata;`
- L776 _private member_ `TSharedPtr<FInternalPlayerImpl, ESPMode::ThreadSafe> CurrentPlayer;`
- L777 _private member_ `TSharedPtr<FAEMSEventReceiver, ESPMode::ThreadSafe> MediaPlayerEventReceiver;`
- L778 _private member_ `TSharedPtr<IAsyncResourceReleaseNotification, ESPMode::ThreadSafe> AsyncResourceReleaseNotification;`
- L780 _private member_ `TRange<FTimespan> CurrentPlaybackRange;`
- L781 _private member_ `FPlayerState PlayerState;`
- L782 _private member_ `bool bHasPendingError = false;`
- L783 _private member_ `bool bHasClosedDueToError = false;`

#### class `FElectraPlayer::FAEMSEventReceiver`  
`class FAEMSEventReceiver : public IAdaptiveStreamingPlayerAEMSReceiver`  
_L238-248_
- inherits: `IAdaptiveStreamingPlayerAEMSReceiver`
- L241 _public prototype_ `virtual ~FAEMSEventReceiver() = default;`
- L242 _public function_ `FOnMediaPlayerEventReceivedDelegate& GetEventReceivedDelegate()`
- L245 _private function_ `virtual void OnMediaPlayerEventReceived(TSharedPtrTS<IAdaptiveStreamingPlayerAEMSEvent> InEvent, IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode InDispatchMode) override`
- L247 _private member_ `FOnMediaPlayerEventReceivedDelegate EventReceivedDelegate;`

#### class `FElectraPlayer::FAdaptiveStreamingPlayerResourceProvider`  
`class FAdaptiveStreamingPlayerResourceProvider : public IAdaptiveStreamingPlayerResourceProvider`  
_L250-265_
- inherits: `IAdaptiveStreamingPlayerResourceProvider`
- L253 _public function_ `FAdaptiveStreamingPlayerResourceProvider(TWeakPtr<IElectraSafeMediaOptionInterface, ESPMode::ThreadSafe> InOptionInterface)`
- L255 _public prototype_ `virtual ~FAdaptiveStreamingPlayerResourceProvider() = default;`
- L257 _public prototype_ `virtual void ProvideStaticPlaybackDataForURL(TSharedPtr<IAdaptiveStreamingPlayerResourceRequest, ESPMode::ThreadSafe> InOutRequest) override;`
- L259 _public prototype_ `void ProcessPendingStaticResourceRequests();`
- L260 _public prototype_ `void ClearPendingRequests();`
- L262 _private member_ `TWeakPtr<IElectraSafeMediaOptionInterface, ESPMode::ThreadSafe> OptionInterface;`
- L264 _private member_ `TQueue<TSharedPtr<IAdaptiveStreamingPlayerResourceRequest, ESPMode::ThreadSafe>, EQueueMode::Mpsc> PendingStaticResourceRequests;` — Requests for static resource fetches we want to perform on the main thread

#### class `FElectraPlayer::FInternalPlayerImpl`  
`class FInternalPlayerImpl`  
_L267-274_
- L271 _public member_ `TSharedPtr<IAdaptiveStreamingPlayer, ESPMode::ThreadSafe> AdaptivePlayer;` — The media player itself
- L273 _public prototype_ `static void DoCloseAsync(TSharedPtr<FInternalPlayerImpl, ESPMode::ThreadSafe>&& InPlayer, uint32 InPlayerID, TSharedPtr<IAsyncResourceReleaseNotification, ESPMode::ThreadSafe> InAsyncResourceReleaseNotification, bool bReleasePools, int64 TexturePoolDecoderID);`

#### struct `FElectraPlayer::FPlaystartOptions`  
`struct FPlaystartOptions`  
_L276-295_
- L278 _public function_ `void Reset()`
- L288 _public member_ `TOptional<FTimespan> TimeOffset;`
- L289 _public member_ `FStreamSelectionAttributes InitialVideoTrackAttributes;`
- L290 _public member_ `FStreamSelectionAttributes InitialAudioTrackAttributes;`
- L291 _public member_ `FStreamSelectionAttributes InitialSubtitleTrackAttributes;`
- L292 _public member_ `TOptional<int32> MaxVerticalStreamResolution;`
- L293 _public member_ `TOptional<int32> MaxBandwidthForStreaming;`
- L294 _public member_ `bool bDoNotPreload = false;`

#### struct `FElectraPlayer::FVideoStreamFormat`  
`struct FVideoStreamFormat`  
_L297-308_
- L299 _public function_ `void Reset()`
- L305 _public member_ `FIntPoint Resolution {};`
- L306 _public member_ `double FrameRate = 0.0;`
- L307 _public member_ `int32 Bitrate = 0;`

#### struct `FElectraPlayer::FPlayerState`  
`struct FPlayerState`  
_L310-332_
- L312 _public function_ `FPlayerState()`
- L314 _public member_ `TOptional<float> IntendedPlayRate;`
- L315 _public member_ `float CurrentPlayRate;`
- L316 _public member_ `EMediaState State;`
- L317 _public member_ `EMediaStatus Status;`
- L319 _public function_ `void Reset()`
- L327 _public prototype_ `float GetRate() const;`
- L328 _public prototype_ `EMediaState GetState() const;`
- L329 _public prototype_ `EMediaStatus GetStatus() const;`
- L330 _public prototype_ `void SetIntendedPlayRate(float InIntendedRate);`
- L331 _public prototype_ `void SetPlayRateFromPlayer(float InCurrentPlayerPlayRate);`

#### struct `FElectraPlayer::FPlayerMetricEventBase`  
`struct FPlayerMetricEventBase`  
_L335-372_
- L369 _public function_ `FPlayerMetricEventBase(EType InType) : Type(InType)`
- L370 _public prototype_ `virtual ~FPlayerMetricEventBase() = default;`
- L371 _public member_ `EType Type;`

#### enum `FElectraPlayer::FPlayerMetricEventBase::EType`  
`enum class EType`  
_L337-368_
- L339 _public enumerator_ `OpenSource`
- L340 _public enumerator_ `ReceivedMainPlaylist`
- L341 _public enumerator_ `ReceivedPlaylists`
- L342 _public enumerator_ `TracksChanged`
- L343 _public enumerator_ `PlaylistDownload`
- L344 _public enumerator_ `BufferingStart`
- L345 _public enumerator_ `BufferingEnd`
- L346 _public enumerator_ `Bandwidth`
- L347 _public enumerator_ `BufferUtilization`
- L348 _public enumerator_ `SegmentDownload`
- L349 _public enumerator_ `LicenseKey`
- L350 _public enumerator_ `DataAvailabilityChange`
- L351 _public enumerator_ `VideoQualityChange`
- L352 _public enumerator_ `AudioQualityChange`
- L353 _public enumerator_ `CodecFormatChange`
- L354 _public enumerator_ `PrerollStart`
- L355 _public enumerator_ `PrerollEnd`
- L356 _public enumerator_ `PlaybackStart`
- L357 _public enumerator_ `PlaybackPaused`
- L358 _public enumerator_ `PlaybackResumed`
- L359 _public enumerator_ `PlaybackEnded`
- L360 _public enumerator_ `JumpInPlayPosition`
- L361 _public enumerator_ `PlaybackStopped`
- L362 _public enumerator_ `SeekCompleted`
- L363 _public enumerator_ `MediaMetadataChanged`
- L364 _public enumerator_ `Error`
- L365 _public enumerator_ `LogMessage`
- L366 _public enumerator_ `DroppedVideoFrame`
- L367 _public enumerator_ `DroppedAudioFrame`

#### struct `FElectraPlayer::FPlayerMetricEvent_OpenSource`  
`struct FPlayerMetricEvent_OpenSource : public FPlayerMetricEventBase`  
_L373-377_
- inherits: `FPlayerMetricEventBase`
- L375 _public function_ `FPlayerMetricEvent_OpenSource(const FString& InURL) : FPlayerMetricEventBase(EType::OpenSource), URL(InURL)`
- L376 _public member_ `FString URL;`

#### struct `FElectraPlayer::FPlayerMetricEvent_ReceivedMainPlaylist`  
`struct FPlayerMetricEvent_ReceivedMainPlaylist : public FPlayerMetricEventBase`  
_L378-382_
- inherits: `FPlayerMetricEventBase`
- L380 _public function_ `FPlayerMetricEvent_ReceivedMainPlaylist(const FString& InEffectiveURL) : FPlayerMetricEventBase(EType::ReceivedMainPlaylist), EffectiveURL(InEffectiveURL)`
- L381 _public member_ `FString EffectiveURL;`

#### struct `FElectraPlayer::FPlayerMetricEvent_PlaylistDownload`  
`struct FPlayerMetricEvent_PlaylistDownload : public FPlayerMetricEventBase`  
_L383-387_
- inherits: `FPlayerMetricEventBase`
- L385 _public function_ `FPlayerMetricEvent_PlaylistDownload(const Metrics::FPlaylistDownloadStats& InPlaylistDownloadStats) : FPlayerMetricEventBase(EType::PlaylistDownload), PlaylistDownloadStats(InPlaylistDownloadStats)`
- L386 _public member_ `Metrics::FPlaylistDownloadStats PlaylistDownloadStats;`

#### struct `FElectraPlayer::FPlayerMetricEvent_BufferingStart`  
`struct FPlayerMetricEvent_BufferingStart : public FPlayerMetricEventBase`  
_L388-392_
- inherits: `FPlayerMetricEventBase`
- L390 _public function_ `FPlayerMetricEvent_BufferingStart(Metrics::EBufferingReason InBufferingReason) : FPlayerMetricEventBase(EType::BufferingStart), BufferingReason(InBufferingReason)`
- L391 _public member_ `Metrics::EBufferingReason BufferingReason;`

#### struct `FElectraPlayer::FPlayerMetricEvent_BufferingEnd`  
`struct FPlayerMetricEvent_BufferingEnd : public FPlayerMetricEventBase`  
_L393-397_
- inherits: `FPlayerMetricEventBase`
- L395 _public function_ `FPlayerMetricEvent_BufferingEnd(Metrics::EBufferingReason InBufferingReason) : FPlayerMetricEventBase(EType::BufferingEnd), BufferingReason(InBufferingReason)`
- L396 _public member_ `Metrics::EBufferingReason BufferingReason;`

#### struct `FElectraPlayer::FPlayerMetricEvent_Bandwidth`  
`struct FPlayerMetricEvent_Bandwidth : public FPlayerMetricEventBase`  
_L398-404_
- inherits: `FPlayerMetricEventBase`
- L400 _public function_ `FPlayerMetricEvent_Bandwidth(int64 InEffectiveBps, int64 InThroughputBps, double InLatencyInSeconds) : FPlayerMetricEventBase(EType::Bandwidth), EffectiveBps(InEffectiveBps), ThroughputBps(InThroughputBps), LatencyInSeconds(InLatencyInSeconds)`
- L401 _public member_ `int64 EffectiveBps;`
- L402 _public member_ `int64 ThroughputBps;`
- L403 _public member_ `double LatencyInSeconds;`

#### struct `FElectraPlayer::FPlayerMetricEvent_BufferUtilization`  
`struct FPlayerMetricEvent_BufferUtilization : public FPlayerMetricEventBase`  
_L405-409_
- inherits: `FPlayerMetricEventBase`
- L407 _public function_ `FPlayerMetricEvent_BufferUtilization(const Metrics::FBufferStats& InBufferStats) : FPlayerMetricEventBase(EType::BufferUtilization), BufferStats(InBufferStats)`
- L408 _public member_ `Metrics::FBufferStats BufferStats;`

#### struct `FElectraPlayer::FPlayerMetricEvent_SegmentDownload`  
`struct FPlayerMetricEvent_SegmentDownload : public FPlayerMetricEventBase`  
_L410-414_
- inherits: `FPlayerMetricEventBase`
- L412 _public function_ `FPlayerMetricEvent_SegmentDownload(const Metrics::FSegmentDownloadStats& InSegmentDownloadStats) : FPlayerMetricEventBase(EType::SegmentDownload), SegmentDownloadStats(InSegmentDownloadStats)`
- L413 _public member_ `Metrics::FSegmentDownloadStats SegmentDownloadStats;`

#### struct `FElectraPlayer::FPlayerMetricEvent_LicenseKey`  
`struct FPlayerMetricEvent_LicenseKey : public FPlayerMetricEventBase`  
_L415-419_
- inherits: `FPlayerMetricEventBase`
- L417 _public function_ `FPlayerMetricEvent_LicenseKey(const Metrics::FLicenseKeyStats& InLicenseKeyStats) : FPlayerMetricEventBase(EType::LicenseKey), LicenseKeyStats(InLicenseKeyStats)`
- L418 _public member_ `Metrics::FLicenseKeyStats LicenseKeyStats;`

#### struct `FElectraPlayer::FPlayerMetricEvent_DataAvailabilityChange`  
`struct FPlayerMetricEvent_DataAvailabilityChange : public FPlayerMetricEventBase`  
_L420-424_
- inherits: `FPlayerMetricEventBase`
- L422 _public function_ `FPlayerMetricEvent_DataAvailabilityChange(const Metrics::FDataAvailabilityChange& InDataAvailability) : FPlayerMetricEventBase(EType::DataAvailabilityChange), DataAvailability(InDataAvailability)`
- L423 _public member_ `Metrics::FDataAvailabilityChange DataAvailability;`

#### struct `FElectraPlayer::FPlayerMetricEvent_VideoQualityChange`  
`struct FPlayerMetricEvent_VideoQualityChange : public FPlayerMetricEventBase`  
_L425-431_
- inherits: `FPlayerMetricEventBase`
- L427 _public function_ `FPlayerMetricEvent_VideoQualityChange(int32 InNewBitrate, int32 InPreviousBitrate, bool bInIsDrasticDownswitch) : FPlayerMetricEventBase(EType::VideoQualityChange), NewBitrate(InNewBitrate), PreviousBitrate(InPreviousBitrate), bIsDrasticDownswitch(bInIsDrasticDownswitch)`
- L428 _public member_ `int32 NewBitrate;`
- L429 _public member_ `int32 PreviousBitrate;`
- L430 _public member_ `bool bIsDrasticDownswitch;`

#### struct `FElectraPlayer::FPlayerMetricEvent_AudioQualityChange`  
`struct FPlayerMetricEvent_AudioQualityChange : public FPlayerMetricEventBase`  
_L432-438_
- inherits: `FPlayerMetricEventBase`
- L434 _public function_ `FPlayerMetricEvent_AudioQualityChange(int32 InNewBitrate, int32 InPreviousBitrate, bool bInIsDrasticDownswitch) : FPlayerMetricEventBase(EType::AudioQualityChange), NewBitrate(InNewBitrate), PreviousBitrate(InPreviousBitrate), bIsDrasticDownswitch(bInIsDrasticDownswitch)`
- L435 _public member_ `int32 NewBitrate;`
- L436 _public member_ `int32 PreviousBitrate;`
- L437 _public member_ `bool bIsDrasticDownswitch;`

#### struct `FElectraPlayer::FPlayerMetricEvent_CodecFormatChange`  
`struct FPlayerMetricEvent_CodecFormatChange : public FPlayerMetricEventBase`  
_L439-443_
- inherits: `FPlayerMetricEventBase`
- L441 _public function_ `FPlayerMetricEvent_CodecFormatChange(const FStreamCodecInformation& InNewDecodingFormat) : FPlayerMetricEventBase(EType::CodecFormatChange), NewDecodingFormat(InNewDecodingFormat)`
- L442 _public member_ `FStreamCodecInformation NewDecodingFormat;`

#### struct `FElectraPlayer::FPlayerMetricEvent_JumpInPlayPosition`  
`struct FPlayerMetricEvent_JumpInPlayPosition : public FPlayerMetricEventBase`  
_L444-450_
- inherits: `FPlayerMetricEventBase`
- L446 _public function_ `FPlayerMetricEvent_JumpInPlayPosition(const FTimeValue& InToNewTime, const FTimeValue& InFromTime, Metrics::ETimeJumpReason InTimejumpReason) : FPlayerMetricEventBase(EType::JumpInPlayPosition), ToNewTime(InToNewTime), FromTime(InFromTime), TimejumpReason(InTimejumpReason)`
- L447 _public member_ `FTimeValue ToNewTime;`
- L448 _public member_ `FTimeValue FromTime;`
- L449 _public member_ `Metrics::ETimeJumpReason TimejumpReason;`

#### struct `FElectraPlayer::FPlayerMetricEvent_MediaMetadataChange`  
`struct FPlayerMetricEvent_MediaMetadataChange : public FPlayerMetricEventBase`  
_L451-455_
- inherits: `FPlayerMetricEventBase`
- L453 _public function_ `FPlayerMetricEvent_MediaMetadataChange(const TSharedPtrTS<Electra::FMetadataParser>& InMetadata) : FPlayerMetricEventBase(EType::MediaMetadataChanged), NewMetadata(InMetadata)`
- L454 _public member_ `TSharedPtrTS<Electra::FMetadataParser> NewMetadata;`

#### struct `FElectraPlayer::FPlayerMetricEvent_Error`  
`struct FPlayerMetricEvent_Error : public FPlayerMetricEventBase`  
_L456-460_
- inherits: `FPlayerMetricEventBase`
- L458 _public function_ `FPlayerMetricEvent_Error(const FString& InErrorReason) : FPlayerMetricEventBase(EType::Error), ErrorReason(InErrorReason)`
- L459 _public member_ `FString ErrorReason;`

#### struct `FElectraPlayer::FPlayerMetricEvent_LogMessage`  
`struct FPlayerMetricEvent_LogMessage : public FPlayerMetricEventBase`  
_L461-467_
- inherits: `FPlayerMetricEventBase`
- L463 _public function_ `FPlayerMetricEvent_LogMessage(IInfoLog::ELevel InLogLevel, const FString& InLogMessage, int64 InPlayerWallclockMilliseconds) : FPlayerMetricEventBase(EType::LogMessage), LogLevel(InLogLevel), LogMessage(InLogMessage), PlayerWallclockMilliseconds(InPlayerWallclockMilliseconds)`
- L464 _public member_ `IInfoLog::ELevel LogLevel;`
- L465 _public member_ `FString LogMessage;`
- L466 _public member_ `int64 PlayerWallclockMilliseconds;`

#### struct `FElectraPlayer::FPlayerMetricEvent_DroppedFrame`  
`struct FPlayerMetricEvent_DroppedFrame : public FPlayerMetricEventBase`  
_L468-472_
- inherits: `FPlayerMetricEventBase`
- L470 _public function_ `FPlayerMetricEvent_DroppedFrame(EType InType, const Metrics::FFrameStats& InFrameStats) : FPlayerMetricEventBase(InType), FrameStats(InFrameStats)`
- L471 _public member_ `Metrics::FFrameStats FrameStats;`

#### struct `FElectraPlayer::FAnalyticsEvent`  
`struct FAnalyticsEvent`  
_L476-480_
- desc: Analytics event
- L478 _public member_ `FString EventName;`
- L479 _public member_ `TArray<FAnalyticsEventAttribute> ParamArray;`

#### class `FElectraPlayer::FAverageValue`  
`class FAverageValue`  
_L483-532_
- L486 _public function_ `FAverageValue() : Samples(nullptr) , NumSamples(0) , MaxSamples(0)`
- L492 _public function_ `~FAverageValue()`
- L496 _public function_ `void SetNumSamples(int32 InMaxSamples)`
- L504 _public function_ `void AddValue(double Value)`
- L509 _public function_ `void Reset()`
- L513 _public function_ `double GetAverage() const`
- L529 _private member_ `double* Samples;`
- L530 _private member_ `int32 NumSamples;`
- L531 _private member_ `int32 MaxSamples;`

#### struct `FElectraPlayer::FStatistics`  
`struct FStatistics`  
_L534-700_
- L570 _public function_ `FStatistics()`
- L574 _public function_ `void Reset()`
- L636 _public prototype_ `void AddMessageToHistory(FString InMessage);`
- L639 _public typedef_ `using FQualityPercentages = TSortedMap<int32, int32, FDefaultAllocator, TGreater<int32>>;` — n elements by descending bitrate holding a percentage of this bitrate being used
- L641 _public member_ `FString InitialURL;`
- L642 _public member_ `FString CurrentlyActivePlaylistURL;`
- L643 _public member_ `FString LastError;`
- L644 _public member_ `FString LastState;` — "Empty", "Opening", "Preparing", "Buffering", "Idle", "Ready", "Playing", "Paused", "Seeking", "Rebuffering", "Ended"
- L645 _public member_ `double TimeAtOpen;`
- L646 _public member_ `double TimeToLoadMainPlaylist;`
- L647 _public member_ `double TimeToLoadStreamPlaylists;`
- L648 _public member_ `double InitialBufferingDuration;`
- L649 _public member_ `int32 InitialVideoStreamBitrate;`
- L650 _public member_ `int32 InitialAudioStreamBitrate;`
- L651 _public member_ `double TimeAtPrerollBegin;`
- L652 _public member_ `double TimeForInitialPreroll;`
- L653 _public member_ `int32 NumTimesRebuffered;`
- L654 _public member_ `int32 NumTimesForwarded;`
- L655 _public member_ `int32 NumTimesRewound;`
- L656 _public member_ `int32 NumTimesLooped;`
- L657 _public member_ `double TimeAtBufferingBegin;`
- L658 _public member_ `double TotalRebufferingDuration;`
- L659 _public member_ `double LongestRebufferingDuration;`
- L660 _public member_ `double PlayPosAtStart;`
- L661 _public member_ `double PlayPosAtEnd;`
- L662 _public member_ `int32 NumVideoQualityUpswitches;`
- L663 _public member_ `int32 NumVideoQualityDownswitches;`
- L664 _public member_ `int32 NumVideoQualityDrasticDownswitches;`
- L665 _public member_ `int32 NumAudioQualityUpswitches;`
- L666 _public member_ `int32 NumAudioQualityDownswitches;`
- L667 _public member_ `int32 NumAudioQualityDrasticDownswitches;`
- L668 _public member_ `int64 NumVideoDatabytesStreamed;`
- L669 _public member_ `int64 NumAudioDatabytesStreamed;`
- L670 _public member_ `int32 NumSegmentDownloadsAborted;`
- L671 _public member_ `int32 CurrentlyActiveResolutionWidth;`
- L672 _public member_ `int32 CurrentlyActiveResolutionHeight;`
- L673 _public member_ `TMap<int32, uint32> VideoSegmentBitratesStreamed;` — key=video stream bitrate, value=number of segments loaded at this rate
- L674 _public member_ `TMap<int32, uint32> AudioSegmentBitratesStreamed;` — key=audio stream bitrate, value=number of segments loaded at this rate
- L675 _public member_ `FQualityPercentages VideoQualityPercentages;`
- L676 _public member_ `FQualityPercentages AudioQualityPercentages;`
- L677 _public member_ `uint32 NumVideoSegmentsStreamed;`
- L678 _public member_ `uint32 NumAudioSegmentsStreamed;`
- L679 _public member_ `FBandwidth InitialBufferingBandwidth;`
- L680 _public member_ `bool bIsInitiallyDownloading;`
- L681 _public member_ `bool bDidPlaybackEnd;`
- L682 _public member_ `FTimeRange MediaTimelineAtStart;`
- L683 _public member_ `FTimeRange MediaTimelineAtEnd;`
- L684 _public member_ `double MediaDuration;`
- L685 _public member_ `TArray<FHistoryEntry> MessageHistoryBuffer;`
- L686 _public member_ `uint32 NumErr404;`
- L687 _public member_ `uint32 NumErr4xx;`
- L688 _public member_ `uint32 NumErr5xx;`
- L689 _public member_ `uint32 NumErrTimeouts;`
- L690 _public member_ `uint32 NumErrConnDrops;`
- L691 _public member_ `uint32 NumErrOther;`
- L692 _public member_ `uint64 NumTotalAddedVideoFrames;`
- L693 _public member_ `uint64 NumTotalDroppedVideoFrames;`
- L694 _public member_ `uint32 AvgVideoDropsPerInterval;`
- L695 _public member_ `uint32 MinVideoDropsPerInterval;`
- L696 _public member_ `uint32 MaxVideoDropsPerInterval;`
- L697 _public member_ `uint32 VideoDropIntervalMs;`
- L698 _public member_ `uint32 VideoNumIntervals;`
- L699 _public member_ `uint32 VideoNumIntervalsWithDrops;`

#### struct `FElectraPlayer::FStatistics::FBandwidth`  
`struct FBandwidth`  
_L536-564_
- L538 _public function_ `FBandwidth()`
- L544 _public function_ `void Reset()`
- L549 _public function_ `void AddSample(double InBytesPerSecond, double InLatency)`
- L554 _public function_ `double GetAverageBandwidth() const`
- L558 _public function_ `double GetAverageLatency() const`
- L562 _public member_ `FAverageValue Bandwidth;`
- L563 _public member_ `FAverageValue Latency;`

#### struct `FElectraPlayer::FStatistics::FHistoryEntry`  
`struct FHistoryEntry`  
_L565-569_
- L567 _public member_ `double TimeSinceStart = 0.0;`
- L568 _public member_ `FString Message;`

#### Free symbols / members of external scopes

- L43 _typedef_ `using IMetaDataDecoderOutputPtr = TSharedPtr<IMetaDataDecoderOutput, ESPMode::ThreadSafe>;`
- L237 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMediaPlayerEventReceivedDelegate, TSharedPtrTS<IAdaptiveStreamingPlayerAEMSEvent> , IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode );`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/ElectraPlayerPrivate.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/BufferedDataReader.h` (Private)


#### class `Electra::IGenericDataReader`  
`class IGenericDataReader`  
_L12-54_
- L15 _public prototype_ `virtual ~IGenericDataReader() = default;`
- L27 _public prototype_ `virtual int64 ReadData(void* InDestinationBuffer, int64 InNumBytesToRead, int64 InFromOffset) = 0;` — Read n bytes of data starting at offset o into the provided buffer. Reading must return the number of bytes asked to get, if necessary by blocking. If a read error prevents reading the number of bytes -1 must be returned. @param IntoBuffer Buffer into which to store the data bytes. If nullptr is passed the data must be skipped over. @param NumBytesToRead The number of bytes to read. Must not read more bytes and should be no less than requested. @return The number of bytes read or -1 on a read error. If the read would go beyond the size of the file then returning fewer bytes than requested is permitted in this case ONLY.
- L32 _public prototype_ `virtual int64 GetCurrentOffset() const = 0;` — Returns the current internal read offset.
- L39 _public prototype_ `virtual int64 GetTotalSize() const = 0;` — Returns the total size of the file. The size should be available at least after the first call to ReadData(). If the total length is not known, return -1.
- L46 _public prototype_ `virtual bool HasReadBeenAborted() const = 0;` — Checks if reading of the file and therefore parsing has been aborted. @return true if reading/parsing has been aborted, false otherwise.
- L53 _public prototype_ `virtual bool HasReachedEOF() const = 0;` — Checks if the data source has reached the End Of File (EOF) and cannot provide any additional data. @return If EOF has been reached returns true, otherwise false.

#### class `Electra::FBufferedDataReader`  
`class FBufferedDataReader`  
_L58-153_
- L73 _public function_ `FBufferedDataReader(IDataProvider* InDataProvider) : DataProvider(InDataProvider)`
- L77 _public function_ `bool Failed() const`
- L81 _public function_ `FErrorDetail GetLastError() const`
- L86 _public function_ `int64 GetCurrentOffset() const`
- L91 _public function_ `int64 GetTotalDataSize() const`
- L96 _public prototype_ `bool PrepareToRead(int64 NumBytes);`
- L97 _public prototype_ `bool ReadU8(uint8& OutValue);`
- L98 _public prototype_ `bool ReadU16LE(uint16& OutValue);`
- L99 _public prototype_ `bool ReadU32LE(uint32& OutValue);`
- L100 _public prototype_ `bool ReadU64LE(uint64& OutValue);`
- L101 _public prototype_ `bool ReadU16BE(uint16& OutValue);`
- L102 _public prototype_ `bool ReadU32BE(uint32& OutValue);`
- L103 _public prototype_ `bool ReadU64BE(uint64& OutValue);`
- L104 _public prototype_ `bool PeekU8(uint8& OutValue);`
- L105 _public prototype_ `bool PeekU16LE(uint16& OutValue);`
- L106 _public prototype_ `bool PeekU32LE(uint32& OutValue);`
- L107 _public prototype_ `bool PeekU64LE(uint64& OutValue);`
- L108 _public prototype_ `bool PeekU16BE(uint16& OutValue);`
- L109 _public prototype_ `bool PeekU32BE(uint32& OutValue);`
- L110 _public prototype_ `bool PeekU64BE(uint64& OutValue);`
- L111 _public prototype_ `bool SkipOver(int64 NumBytes);`
- L112 _public prototype_ `bool ReadByteArray(TArray<uint8>& OutValue, int64 NumBytes);`
- L113 _public prototype_ `bool SeekTo(int64 AbsolutePosition);`
- L114 _public prototype_ `bool IsAtEOS();`
- L133 _protected prototype_ `FArea* FindAreaForOffset(int64 Offset);`
- L134 _protected prototype_ `void CreateNewArea(int64 NumBytes, int64 FromOffset);`
- L135 _protected prototype_ `bool EnlargeCurrentAreaBy(int64 NumBytesToAdd);`
- L137 _protected function_ `void UpdateReadDataPointer()`
- L142 _protected member_ `IDataProvider* DataProvider = nullptr;`
- L143 _protected member_ `FErrorDetail LastError;`
- L145 _protected member_ `TArray<TUniquePtr<FArea>> Areas;`
- L146 _protected member_ `int64 TotalDataSize = -1;`
- L148 _protected member_ `FArea* CurrentArea = nullptr;`
- L149 _protected member_ `int64 BytesRemainingInArea = 0;`
- L151 _protected member_ `int64 CurrentOffset = 0;`
- L152 _protected member_ `const uint8* ReadDataPointer = nullptr;`

#### class `Electra::FBufferedDataReader::IDataProvider`  
`class IDataProvider`  
_L61-71_
- L70 _public prototype_ `virtual int64 OnReadAssetData(void* Destination, int64 NumBytes, int64 FromOffset, int64* OutTotalSize) = 0;`

#### enum `Electra::FBufferedDataReader::IDataProvider::EError`  
`enum class EError`  
_L64-69_
- L66 _public enumerator_ `Failed = -1`
- L67 _public enumerator_ `EOS = -2`
- L68 _public enumerator_ `Aborted = -3`

#### enum `Electra::FBufferedDataReader::(anonymous)`  
``  
_L117-119_

#### struct `Electra::FBufferedDataReader::FArea`  
`struct FArea`  
_L121-131_
- L123 _public function_ `~FArea()`
- L127 _public member_ `const uint8* Data = nullptr;`
- L128 _public member_ `int64 Size = 0;`
- L129 _public member_ `int64 StartOffset = 0;`
- L130 _public member_ `bool bEOS = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`
- L118 _enumerator_ `kDefaultReadSize = 65536` (scope `Electra::FBufferedDataReader::__anon746f43550103`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Decoder/AudioDecoder.h` (Private)


#### class `Electra::IAudioDecoder`  
`class IAudioDecoder : public IDecoderBase, public IAccessUnitBufferInterface, public IDecoderAUBufferDiags, public IDecoderReadyBufferDiags`  
_L17-62_
- inherits: `IDecoderBase,IAccessUnitBufferInterface,IDecoderAUBufferDiags,IDecoderReadyBufferDiags`
- L20 _public prototype_ `static bool CanDecodeStream(const FStreamCodecInformation& InCodecInfo);`
- L22 _public prototype_ `static IAudioDecoder* Create();`
- L24 _public prototype_ `virtual ~IAudioDecoder() = default;`
- L26 _public prototype_ `virtual void SetOutputHandler(TSharedPtr<FOutputHandlerAudio, ESPMode::ThreadSafe> InOutputHandler) = 0;`
- L28 _public prototype_ `virtual void SetPlayerSessionServices(IPlayerSessionServices* SessionServices) = 0;`
- L30 _public prototype_ `virtual void Open(TSharedPtrTS<FAccessUnit::CodecData> InCodecData) = 0;`
- L31 _public prototype_ `virtual void Close() = 0;`
- L32 _public prototype_ `virtual void DrainForCodecChange() = 0;`
- L38 _public prototype_ `virtual void SuspendOrResumeDecoder(bool bSuspend, const FParamDict& InOptions) = 0;` — Methods from IDecoderBase
- L44 _public prototype_ `virtual void AUdataPushAU(FAccessUnit* AccessUnit) = 0;` — Methods from IAccessUnitBufferInterface Pushes an access unit to the decoder. Ownership of the access unit is transferred to the decoder.
- L46 _public prototype_ `virtual void AUdataPushEOD() = 0;` — Notifies the decoder that there will be no further access units.
- L48 _public prototype_ `virtual void AUdataClearEOD() = 0;` — Notifies the decoder that there may be further access units.
- L50 _public prototype_ `virtual void AUdataFlushEverything() = 0;` — Instructs the decoder to flush all pending input and all already decoded output.
- L56 _public prototype_ `virtual void SetAUInputBufferListener(IAccessUnitBufferListener* Listener) = 0;` — Methods from IDecoderAUBufferDiags Registers an AU input buffer listener.
- L61 _public prototype_ `virtual void SetReadyBufferListener(IDecoderOutputBufferListener* Listener) = 0;` — Methods from IDecoderReadyBufferDiags

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Decoder/DecoderBase.h` (Private)


#### class `Electra::IDecoderBase`  
`class IDecoderBase`  
_L34-39_
- L37 _public prototype_ `virtual ~IDecoderBase() = default;`

#### class `Electra::IDecoderAUBufferDiags`  
`class IDecoderAUBufferDiags`  
_L45-50_
- L48 _public prototype_ `virtual ~IDecoderAUBufferDiags() = default;`
- L49 _public prototype_ `virtual void SetAUInputBufferListener(IAccessUnitBufferListener* Listener) = 0;`

#### class `Electra::IDecoderReadyBufferDiags`  
`class IDecoderReadyBufferDiags`  
_L56-61_
- L59 _public prototype_ `virtual ~IDecoderReadyBufferDiags() = default;`
- L60 _public prototype_ `virtual void SetReadyBufferListener(IDecoderOutputBufferListener* Listener) = 0;`

#### class `Electra::FDecoderMessage`  
`class FDecoderMessage : public IPlayerMessage`  
_L66-123_
- inherits: `IPlayerMessage`
- L74 _public function_ `static TSharedPtrTS<IPlayerMessage> Create(EReason InReason, IDecoderBase* InDecoderInstance, EStreamType InStreamType, FStreamCodecInformation::ECodec InCodec=FStreamCodecInformation::ECodec::Unknown)`
- L80 _public function_ `static const FString& Type()`
- L86 _public function_ `virtual const FString& GetType() const`
- L91 _public function_ `EReason GetReason() const`
- L96 _public function_ `IDecoderBase* GetDecoderInstance() const`
- L101 _public function_ `EStreamType GetStreamType() const`
- L106 _public function_ `FStreamCodecInformation::ECodec GetCodec() const`
- L112 _private function_ `FDecoderMessage(EReason InReason, IDecoderBase* InDecoderInstance, EStreamType InStreamType, FStreamCodecInformation::ECodec InCodec) : Codec(InCodec) , DecoderInstance(InDecoderInstance) , StreamType(InStreamType) , Reason(InReason)`
- L119 _private member_ `FStreamCodecInformation::ECodec Codec;`
- L120 _private member_ `IDecoderBase* DecoderInstance;`
- L121 _private member_ `EStreamType StreamType;`
- L122 _private member_ `EReason Reason;`

#### enum `Electra::FDecoderMessage::EReason`  
`enum class EReason`  
_L69-72_
- L71 _public enumerator_ `DrainingFinished`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Electra`
- L14 _namespace_ `namespace DecoderConfig` (scope `Electra`)
- L17 _variable_ `static const bool bCheckForDTSTimejump = true;` (scope `Electra::DecoderConfig`) — Should we check if the DTS of the input AU jumps?
- L19 _variable_ `static const int64 BackwardsTimejumpThresholdHNS = 10 * 1000 * 500;` (scope `Electra::DecoderConfig`) — When checking the AU DTS, how much does it need to jump back before triggering a decoder drain?
- L21 _variable_ `static const bool bDrainDecoderOnDetectedBackwardsTimejump = false;` (scope `Electra::DecoderConfig`) — Drain the decoder when a timejump is being detected?
- L23 _variable_ `static const int64 ForwardTimejumpThresholdHNS = 10 * 1000 * 500;` (scope `Electra::DecoderConfig`) — When checking the AU DTS, how much does it need to jump forward before logging a warning?
- L27 _variable_ `static const int64 RemovalOfOldDecoderInputThresholdHNS = 10 * 1000 * 1000 * 10;` (scope `Electra::DecoderConfig`) — After what time decoder inputs are to be flushed in case some decoder implementation drops output which we would otherwise keep the source AU around for.

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Decoder/SubtitleDecoder.h` (Private)


#### class `Electra::ISubtitleDecoder`  
`class ISubtitleDecoder : public IAccessUnitBufferInterface`  
_L20-56_
- inherits: `IAccessUnitBufferInterface`
- desc: Generic subtitle decoder
- L23 _public prototype_ `static bool IsSupported(const FString& MimeType, const FString& Codec);`
- L25 _public prototype_ `static ISubtitleDecoder* Create(FAccessUnit* AccessUnit);`
- L27 _public prototype_ `virtual ~ISubtitleDecoder() = default;`
- L32 _public prototype_ `virtual void SetPlayerSessionServices(IPlayerSessionServices* SessionServices) = 0;` — State methods
- L33 _public prototype_ `virtual void SetMediaSamples(TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> InMediaSamples) = 0;`
- L34 _public prototype_ `virtual void Open(const FParamDict& Options) = 0;`
- L35 _public prototype_ `virtual void Close() = 0;`
- L36 _public prototype_ `virtual void Start() = 0;`
- L37 _public prototype_ `virtual void Stop() = 0;`
- L38 _public prototype_ `virtual void UpdatePlaybackPosition(FTimeValue InAbsolutePosition, FTimeValue InLocalPosition) = 0;`
- L42 _public prototype_ `virtual FTimeValue GetStreamedDeliveryTimeOffset() = 0;` — Returns a time offset at which streamed subtitles should be delivered ahead of their actual timestamp (if they are available earlier)
- L49 _public prototype_ `virtual void AUdataPushAU(FAccessUnit* AccessUnit) = 0;` — Methods from IAccessUnitBufferInterface Pushes an access unit to the decoder. Ownership of the access unit is transferred to the decoder.
- L51 _public prototype_ `virtual void AUdataPushEOD() = 0;` — Notifies the decoder that there will be no further access units.
- L53 _public prototype_ `virtual void AUdataClearEOD() = 0;` — Notifies the decoder that there may be further access units.
- L55 _public prototype_ `virtual void AUdataFlushEverything() = 0;` — Instructs the decoder to flush all pending input and all already decoded output.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Decoder/VideoDecoder.h` (Private)


#### class `Electra::IVideoDecoder`  
`class IVideoDecoder : public IDecoderBase, public IAccessUnitBufferInterface, public IDecoderAUBufferDiags, public IDecoderReadyBufferDiags`  
_L17-62_
- inherits: `IDecoderBase,IAccessUnitBufferInterface,IDecoderAUBufferDiags,IDecoderReadyBufferDiags`
- L20 _public prototype_ `static bool CanDecodeStream(const FStreamCodecInformation& InCodecInfo);`
- L22 _public prototype_ `static IVideoDecoder* Create();`
- L24 _public prototype_ `virtual ~IVideoDecoder() = default;`
- L26 _public prototype_ `virtual void SetOutputHandler(TSharedPtr<FOutputHandlerVideo, ESPMode::ThreadSafe> InOutputHandler) = 0;`
- L28 _public prototype_ `virtual void SetPlayerSessionServices(IPlayerSessionServices* SessionServices) = 0;`
- L30 _public prototype_ `virtual void Open(TSharedPtrTS<FAccessUnit::CodecData> InCodecData, FParamDict&& InAdditionalOptions, const FStreamCodecInformation* InMaxStreamConfiguration) = 0;`
- L31 _public prototype_ `virtual bool Reopen(TSharedPtrTS<FAccessUnit::CodecData> InCodecData, const FParamDict& InAdditionalOptions, const FStreamCodecInformation* InMaxStreamConfiguration) = 0;`
- L32 _public prototype_ `virtual void Close() = 0;`
- L33 _public prototype_ `virtual void DrainForCodecChange() = 0;`
- L38 _public prototype_ `virtual void SuspendOrResumeDecoder(bool bSuspend, const FParamDict& InOptions) = 0;` — Methods from IDecoderBase
- L44 _public prototype_ `virtual void AUdataPushAU(FAccessUnit* AccessUnit) = 0;` — Methods from IAccessUnitBufferInterface Pushes an access unit to the decoder. Ownership of the access unit is transferred to the decoder.
- L46 _public prototype_ `virtual void AUdataPushEOD() = 0;` — Notifies the decoder that there will be no further access units.
- L48 _public prototype_ `virtual void AUdataClearEOD() = 0;` — Notifies the decoder that there may be further access units.
- L50 _public prototype_ `virtual void AUdataFlushEverything() = 0;` — Instructs the decoder to flush all pending input and all already decoded output.
- L56 _public prototype_ `virtual void SetAUInputBufferListener(IAccessUnitBufferListener* Listener) = 0;` — Methods from IDecoderAUBufferDiags Registers an AU input buffer listener.
- L61 _public prototype_ `virtual void SetReadyBufferListener(IDecoderOutputBufferListener* Listener) = 0;` — Methods from IDecoderReadyBufferDiags

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Demuxer/ParserISO13818-1.h` (Private)


#### class `Electra::IParserISO13818_1`  
`class IParserISO13818_1`  
_L25-159_
- desc: Interface for parsing an MPEG transport stream (ISO/IEC 13818-1)
- L28 _public prototype_ `virtual ~IParserISO13818_1() = default;`
- L30 _public prototype_ `static TSharedPtrTS<IParserISO13818_1> CreateParser();`
- L84 _public prototype_ `virtual EParseState BeginParsing(IPlayerSessionServices* InPlayerSession, IGenericDataReader* InDataReader, EParserFlags InParseFlags, const FSourceInfo& InSourceInfo) = 0;`
- L95 _public prototype_ `virtual EParseState Parse(IPlayerSessionServices* InPlayerSession, IGenericDataReader* InDataReader) = 0;` — Call this method to demultiplex the transport stream and get program information and PES packets. Internally this method keeps reading transport stream packets until it has assembled the program map and program mapping table, after which it returns `NewProgram`. You then need to call GetCurrentProgramTable() followed by SelectProgramStreams() to select the elementary streams you wish to demultiplex, then continue calling Parse(). When the state returns `HavePESPacket` a new packet can be retrieved by calling GetPESPacket(). Repeat this process until `Failed` or `EOS` is returned.
- L102 _public prototype_ `virtual TSharedPtrTS<const FProgramTable> GetCurrentProgramTable() = 0;` — Returns the current program table as defined by the transport stream. Do this when the parse state returns `NewProgram`, then enable the elementary streams you want to demultiplex by calling SelectProgramStreams().
- L112 _public prototype_ `virtual void SelectProgramStreams(int32 InProgramNumber, const TArray<int32>& InProgramStreamPIDsToEnable) = 0;` — Selects the program's individual elementary streams to demultiplex. Do this *ONLY* when the parse state returns `NewProgram` and you get the program table by calling GetCurrentProgramTable(). Then select the streams you wish to demultiplex and receive the PES packets for. All streams whose PID is NOT in the list will be discarded. While you could call this method at any time on a running stream it is not recommended.
- L130 _public prototype_ `virtual TSharedPtrTS<FPESData> GetPESPacket() = 0;` — Call this to obtain the most recently demultiplexed PES packet when the parse state returns `HavePESPacket`. If you do not get the packet and continue to call Parse() the packet will be dropped.
- L135 _public prototype_ `virtual FErrorDetail GetLastError() const = 0;` — Returns the last error.
- L156 _public prototype_ `virtual EPESPacketResult ParsePESPacket(TArray<FESPacket>& OutPackets, TSharedPtrTS<FPESData> InPESPacket) = 0;`
- L158 _public prototype_ `virtual bool ParseCSD(FStreamCodecInformation& OutParsedCSD, const FESPacket& InFromPESPacket) = 0;`

#### enum `Electra::IParserISO13818_1::EParserFlags`  
`enum class EParserFlags : uint8`  
_L32-37_
- L34 _public enumerator_ `ParseFlag_Default = 0`
- L36 _public enumerator_ `ParseFlag_IgnoreProgramStream = 1 << 0` — Ignore PAT/PMT from the actual stream and rely on info from the init segment (if present)

#### struct `Electra::IParserISO13818_1::FSourceInfo`  
`struct FSourceInfo`  
_L39-45_
- L41 _public member_ `TSharedPtr<const TArray<uint8>, ESPMode::ThreadSafe> InitSegmentData;`
- L42 _public member_ `int64 InFirstFileByteOffset = -1;`
- L43 _public member_ `int64 InLastFileByteOffset = -1;`
- L44 _public member_ `uint64 TimestampOffset = 0;`

#### enum `Electra::IParserISO13818_1::EParseState`  
`enum class EParseState`  
_L47-61_
- L50 _public enumerator_ `Continue` — Continue parsing. Need more input data.
- L52 _public enumerator_ `NewProgram` — A new program was activated.
- L54 _public enumerator_ `HavePESPacket` — A new PES packet has been assembled. Call to get it.
- L56 _public enumerator_ `Failed` — Failed
- L58 _public enumerator_ `ReadError` — Read error
- L60 _public enumerator_ `EOS` — Reached the end of the stream.

#### struct `Electra::IParserISO13818_1::FProgramStreamInfo`  
`struct FProgramStreamInfo`  
_L63-70_
- L67 _public member_ `FStreamCodecInformation CodecInfo;` — The program stream codec information is filled only _very_ rudimentary. There are no details on the codec (like profile, level, resolution, sample rate, etc.) given in the program table.
- L69 _public member_ `uint8 StreamType = 0;` — The ISO 13818-1 / ITU Rec H.220.0 `stream_type` value from Table 2-34

#### struct `Electra::IParserISO13818_1::FProgramStream`  
`struct FProgramStream`  
_L72-76_
- L75 _public member_ `TSortedMap<int32, FProgramStreamInfo> StreamTable;` — This is a map of the program with the elementary stream PID as key and the stream type as value.

#### struct `Electra::IParserISO13818_1::FProgramTable`  
`struct FProgramTable`  
_L78-82_
- L81 _public member_ `TMap<int32, FProgramStream> ProgramTable;` — This is a map with the program number as key and the program stream information as value.

#### struct `Electra::IParserISO13818_1::FPESData`  
`struct FPESData`  
_L114-123_
- L116 _public member_ `int32 PID;`
- L117 _public member_ `TSharedPtrTS<TArray<uint8>> PacketData;`
- L118 _public member_ `TOptional<uint64> PCR;`
- L120 _public member_ `bool bRandomAccessIndicator = false;` — The `random_access_indicator` flag from the adaptation_field. This may or may not be set.
- L122 _public member_ `uint8 StreamType = 0;` — The ISO 13818-1 / ITU Rec H.220.0 `stream_type` value from Table 2-34

#### enum `Electra::IParserISO13818_1::EPESPacketResult`  
`enum class EPESPacketResult`  
_L138-144_
- L140 _public enumerator_ `Ok`
- L141 _public enumerator_ `Invalid`
- L142 _public enumerator_ `Truncated`
- L143 _public enumerator_ `NotSupported`

#### struct `Electra::IParserISO13818_1::FESPacket`  
`struct FESPacket`  
_L146-155_
- L148 _public member_ `TOptional<uint64> DTS;`
- L149 _public member_ `TOptional<uint64> PTS;`
- L150 _public member_ `TSharedPtrTS<TArray<uint8>> CSD;`
- L151 _public member_ `TSharedPtrTS<TArray<uint8>> Data;`
- L152 _public member_ `int32 SubPacketNum = 0;`
- L153 _public member_ `bool bIsSyncFrame = false;`
- L154 _public member_ `uint8 StreamType = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Electra`
- L160 _prototype_ `ENUM_CLASS_FLAGS(IParserISO13818_1::EParserFlags);` (scope `Electra`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Demuxer/ParserISO14496-12.h` (Private)


#### class `Electra::IParserISO14496_12`  
`class IParserISO14496_12`  
_L28-309_
- desc: Interface for parsing an ISO/IEC 14496-12 file, commonly referred to as an "mp4" file.
- L31 _public prototype_ `virtual ~IParserISO14496_12() = default;`
- L34 _public typedef_ `typedef uint32 FBoxType;` — Box type is a 32 bit value in an mp4 file.
- L47 _public member_ `static const FBoxType BoxType_ftyp = MAKE_BOX_ATOM('f', 't', 'y', 'p');`
- L48 _public member_ `static const FBoxType BoxType_styp = MAKE_BOX_ATOM('s', 't', 'y', 'p');`
- L49 _public member_ `static const FBoxType BoxType_moov = MAKE_BOX_ATOM('m', 'o', 'o', 'v');`
- L50 _public member_ `static const FBoxType BoxType_sidx = MAKE_BOX_ATOM('s', 'i', 'd', 'x');`
- L51 _public member_ `static const FBoxType BoxType_prft = MAKE_BOX_ATOM('p', 'r', 'f', 't');`
- L52 _public member_ `static const FBoxType BoxType_moof = MAKE_BOX_ATOM('m', 'o', 'o', 'f');`
- L53 _public member_ `static const FBoxType BoxType_mdat = MAKE_BOX_ATOM('m', 'd', 'a', 't');`
- L54 _public member_ `static const FBoxType BoxType_free = MAKE_BOX_ATOM('f', 'r', 'e', 'e');`
- L93 _public prototype_ `static TSharedPtrTS<IParserISO14496_12> CreateParser();`
- L98 _public prototype_ `virtual UEMediaError ParseHeader(IGenericDataReader* DataReader, IBoxCallback* BoxParseCallback, IPlayerSessionServices* PlayerSession, const IParserISO14496_12* OptionalInitSegment) = 0;` — Parses the header boxes (all non-MDAT boxes).
- L102 _public typedef_ `typedef uint32 FBrandType;` — A brand is a 32 bit value in an mp4 file.
- L104 _public member_ `static const FBrandType BrandType_emsg = MAKE_MP4_BRAND('e', 'm', 's', 'g');`
- L105 _public member_ `static const FBrandType BrandType_lmsg = MAKE_MP4_BRAND('l', 'm', 's', 'g');`
- L107 _public prototype_ `virtual int32 GetNumberOfBrands() const = 0;`
- L108 _public prototype_ `virtual FBrandType GetBrandByIndex(int32 Index) const = 0;`
- L109 _public prototype_ `virtual bool HasBrand(const FBrandType InBrand) const = 0;`
- L116 _public prototype_ `virtual UEMediaError PrepareTracks(IPlayerSessionServices* PlayerSession, TSharedPtrTS<const IParserISO14496_12> OptionalMP4InitSegment) = 0;`
- L119 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);` — Cancellation delegate for potentially slow tasks.
- L120 _public prototype_ `virtual UEMediaError ResolveTimecodeTracks(IPlayerSessionServices* InPlayerSession, FCancellationCheckDelegate InCancellationCheckDelegate) = 0;`
- L122 _public prototype_ `virtual TMediaOptionalValue<FTimeFraction> GetMovieDuration() const = 0;`
- L124 _public prototype_ `virtual int32 GetNumberOfTracks() const = 0;`
- L126 _public prototype_ `virtual int32 GetNumberOfSegmentIndices() const = 0;`
- L128 _public prototype_ `virtual int32 GetNumberOfEventMessages() const = 0;`
- L297 _public prototype_ `virtual const IMetadata* GetMetadata(EBaseBoxType InFromBox) const = 0;`
- L299 _public prototype_ `virtual TSharedPtrTS<IAllTrackIterator> CreateAllTrackIteratorByFilePos(int64 InFromFilePos) const = 0;`
- L301 _public prototype_ `virtual TSharedPtrTS<IAllTrackIterator> CreateAllTrackIteratorForTrackIDs(const TArray<uint32>& InTrackIDs) const = 0;`
- L303 _public prototype_ `virtual const ITrack* GetTrackByIndex(int32 Index) const = 0;`
- L304 _public prototype_ `virtual const ITrack* GetTrackByTrackID(int32 TrackID) const = 0;`
- L306 _public prototype_ `virtual const ISegmentIndex* GetSegmentIndexByIndex(int32 Index) const = 0;`
- L308 _public prototype_ `virtual const IEventMessage* GetEventMessageByIndex(int32 Index) const = 0;`

#### class `Electra::IParserISO14496_12::IBoxCallback`  
`class IBoxCallback`  
_L61-90_
- desc: Interface for receiving parse notifications
- L64 _public prototype_ `virtual ~IBoxCallback() = default;`
- L88 _public prototype_ `virtual EParseContinuation OnFoundBox(FBoxType Box, int64 BoxSizeInBytes, int64 FileDataOffset, int64 BoxDataOffset) = 0;` — Notifies the caller of the start/end of a new box. The caller may continue to parse this box or ask to stop parsing. @param Box Type of the box that will be parsed next. @param BoxSizeInBytes Size of the box in bytes. @param FileDataOffset Offset of the box within the file. This points to the first byte of the box length field. @param BoxDataOffset Offset of the box' data. This points to the first payload byte of the box. @return Whether or not to continue parsing thix box.
- L89 _public prototype_ `virtual EParseContinuation OnEndOfBox(FBoxType Box, int64 BoxSizeInBytes, int64 FileDataOffset, int64 BoxDataOffset) = 0;`

#### enum `Electra::IParserISO14496_12::IBoxCallback::EParseContinuation`  
`enum class EParseContinuation`  
_L69-75_
- desc: Choices for continued parsing.
- L72 _public enumerator_ `Continue` — Continue parsing
- L74 _public enumerator_ `Stop` — Stop parsing

#### class `Electra::IParserISO14496_12::IMetadata`  
`class IMetadata`  
_L130-139_
- L133 _public prototype_ `virtual uint32 GetHandler() const = 0;`
- L134 _public prototype_ `virtual uint32 GetReserved(int32 InIndex0to2) const = 0;`
- L135 _public prototype_ `virtual int32 GetNumChildBoxes() const = 0;`
- L136 _public prototype_ `virtual uint32 GetChildBoxType(int32 InChildIndex) const = 0;`
- L137 _public prototype_ `virtual uint32 GetChildBoxDataSize(int32 InChildIndex) const = 0;`
- L138 _public prototype_ `virtual const void* GetChildBoxData(int32 InChildIndex) const = 0;`

#### class `Electra::IParserISO14496_12::ITrackIterator`  
`class ITrackIterator`  
_L141-174_
- L144 _public prototype_ `virtual ~ITrackIterator() = default;`
- L153 _public prototype_ `virtual UEMediaError StartAtTime(const FTimeValue& AtTime, ESearchMode SearchMode, bool bNeedSyncSample) = 0;`
- L154 _public prototype_ `virtual UEMediaError StartAtFirst(bool bNeedSyncSample) = 0;`
- L155 _public prototype_ `virtual UEMediaError Next() = 0;`
- L157 _public prototype_ `virtual bool IsAtEOS() const = 0;`
- L158 _public prototype_ `virtual const ITrack* GetTrack() const = 0;`
- L159 _public prototype_ `virtual int64 GetBaseMediaDecodeTime() const = 0;`
- L160 _public prototype_ `virtual uint32 GetSampleNumber() const = 0;`
- L161 _public prototype_ `virtual int64 GetDTS() const = 0;`
- L162 _public prototype_ `virtual int64 GetPTS() const = 0;`
- L163 _public prototype_ `virtual int64 GetDuration() const = 0;`
- L164 _public prototype_ `virtual uint32 GetTimescale() const = 0;`
- L165 _public prototype_ `virtual bool IsSyncSample() const = 0;`
- L166 _public prototype_ `virtual int64 GetSampleSize() const = 0;`
- L167 _public prototype_ `virtual int64 GetSampleFileOffset() const = 0;`
- L168 _public prototype_ `virtual int64 GetRawDTS() const = 0;`
- L169 _public prototype_ `virtual int64 GetRawPTS() const = 0;`
- L170 _public prototype_ `virtual int64 GetCompositionTimeEdit() const = 0;`
- L171 _public prototype_ `virtual int64 GetEmptyEditOffset() const = 0;`
- L173 _public prototype_ `virtual bool GetEncryptionInfo(ElectraCDM::FMediaCDMSampleInfo& OutSampleEncryptionInfo) const = 0;`

#### enum `Electra::IParserISO14496_12::ITrackIterator::ESearchMode`  
`enum class ESearchMode`  
_L146-151_
- L148 _public enumerator_ `Before`
- L149 _public enumerator_ `After`
- L150 _public enumerator_ `Closest`

#### class `Electra::IParserISO14496_12::ITrack`  
`class ITrack`  
_L176-234_
- L217 _public prototype_ `virtual ~ITrack() = default;`
- L219 _public prototype_ `virtual uint32 GetID() const = 0;`
- L220 _public prototype_ `virtual FString GetName() const = 0;`
- L221 _public prototype_ `virtual FString GetNameFromHandler() const = 0;`
- L222 _public prototype_ `virtual FTimeFraction GetDuration() const = 0;`
- L224 _public prototype_ `virtual ITrackIterator* CreateIterator() const = 0;`
- L226 _public prototype_ `virtual const TArray<uint8> GetCodecSpecificData() const = 0;`
- L227 _public prototype_ `virtual const TArray<uint8> GetCodecSpecificDataRAW() const = 0;`
- L228 _public prototype_ `virtual const FStreamCodecInformation GetCodecInformation() const = 0;`
- L229 _public prototype_ `virtual const FBitrateInfo GetBitrateInfo() const = 0;`
- L230 _public prototype_ `virtual const BCP47::FLanguageTag& GetLanguageTag() const = 0;`
- L231 _public prototype_ `virtual bool GetEncryptionInfo(FEncryptionInfo& OutEncryptionInfo) const = 0;`
- L232 _public prototype_ `virtual void GetPSSHBoxes(TArray<TArray<uint8>>& OutBoxes, bool bFromMOOV, bool bFromMOOF) const = 0;`
- L233 _public prototype_ `virtual void GetPRFTBoxes(TArray<FProducerReferenceTime>& OutBoxes) const = 0;`

#### struct `Electra::IParserISO14496_12::ITrack::FBitrateInfo`  
`struct FBitrateInfo`  
_L180-185_
- desc: Bitrate box from either 'btrt' or the 'esds' DecoderConfigDescriptor
- L182 _public member_ `uint32 BufferSizeDB = 0;`
- L183 _public member_ `uint32 MaxBitrate = 0;`
- L184 _public member_ `uint32 AvgBitrate = 0;`

#### struct `Electra::IParserISO14496_12::ITrack::FProducerReferenceTime`  
`struct FProducerReferenceTime`  
_L188-200_
- desc: Producer reference time box ('prft') applicable to this track.
- L197 _public member_ `uint64 NtpTimestamp = 0;`
- L198 _public member_ `uint64 MediaTime = 0;`
- L199 _public member_ `EReferenceType Reference = EReferenceType::Undefined;`

#### enum `Electra::IParserISO14496_12::ITrack::FProducerReferenceTime::EReferenceType`  
`enum class EReferenceType`  
_L190-196_
- L192 _public enumerator_ `Undefined`
- L193 _public enumerator_ `Captured`
- L194 _public enumerator_ `Encoder`
- L195 _public enumerator_ `Application`

#### struct `Electra::IParserISO14496_12::ITrack::FEncryptionInfo`  
`struct FEncryptionInfo`  
_L202-215_
- L204 _public member_ `TArray<uint8> DefaultKID;`
- L205 _public member_ `TArray<uint8> DefaultIV;`
- L206 _public member_ `int32 DefaultIVSize = 0;`
- L207 _public member_ `uint32 Scheme = 0;`
- L214 _public member_ `TArray<FCDMInfo> CDMInfos;`

#### struct `Electra::IParserISO14496_12::ITrack::FEncryptionInfo::FCDMInfo`  
`struct FCDMInfo`  
_L208-213_
- L210 _public member_ `TArray<uint8> SystemID;`
- L211 _public member_ `TArray<TArray<uint8>> KIDs;`
- L212 _public member_ `TArray<uint8> Data;`

#### class `Electra::IParserISO14496_12::IAllTrackIterator`  
`class IAllTrackIterator`  
_L237-251_
- L240 _public prototype_ `virtual ~IAllTrackIterator() = default;`
- L242 _public prototype_ `virtual const ITrackIterator* Current() const = 0;` — Returns the iterator at the current file position.
- L244 _public prototype_ `virtual bool Next() = 0;` — Advance iterator to point to the next sample in sequence. Returns false if there are no more samples.
- L246 _public prototype_ `virtual void GetNewEOSTracks(TArray<const ITrackIterator*>& OutTracksThatNewlyReachedEOS) const = 0;` — Returns a list of all tracks iterators that reached EOS while iterating since the most recent call to ClearNewEOSTracks().
- L248 _public prototype_ `virtual void ClearNewEOSTracks() = 0;` — Clears the list of track iterators that have reached EOS.
- L250 _public prototype_ `virtual void GetAllIterators(TArray<const ITrackIterator*>& OutIterators) const = 0;` — Returns list of all iterators.

#### class `Electra::IParserISO14496_12::ISegmentIndex`  
`class ISegmentIndex`  
_L254-274_
- L267 _public prototype_ `virtual ~ISegmentIndex() = default;`
- L268 _public prototype_ `virtual uint64 GetEarliestPresentationTime() const = 0;`
- L269 _public prototype_ `virtual uint64 GetFirstOffset() const = 0;`
- L270 _public prototype_ `virtual uint32 GetReferenceID() const = 0;`
- L271 _public prototype_ `virtual uint32 GetTimescale() const = 0;`
- L272 _public prototype_ `virtual int32 GetNumEntries() const = 0;`
- L273 _public prototype_ `virtual const FEntry& GetEntry(int32 Index) const = 0;`

#### struct `Electra::IParserISO14496_12::ISegmentIndex::FEntry`  
`struct FEntry`  
_L257-265_
- L259 _public member_ `uint32 SubSegmentDuration;`
- L260 _public member_ `uint32 IsReferenceType : 1;`
- L261 _public member_ `uint32 Size : 31;`
- L262 _public member_ `uint32 StartsWithSAP : 1;`
- L263 _public member_ `uint32 SAPType : 3;`
- L264 _public member_ `uint32 SAPDeltaTime : 28;`

#### class `Electra::IParserISO14496_12::IEventMessage`  
`class IEventMessage`  
_L276-289_
- L279 _public prototype_ `virtual ~IEventMessage() = default;`
- L280 _public prototype_ `virtual int32 GetVersion() const = 0;`
- L281 _public prototype_ `virtual const FString& GetSchemeIdUri() const = 0;`
- L282 _public prototype_ `virtual const FString& GetValue() const = 0;`
- L283 _public prototype_ `virtual uint32 GetTimescale() const = 0;`
- L284 _public prototype_ `virtual uint32 GetPresentationTimeDelta() const = 0;`
- L285 _public prototype_ `virtual uint64 GetPresentationTime() const = 0;`
- L286 _public prototype_ `virtual uint32 GetEventDuration() const = 0;`
- L287 _public prototype_ `virtual uint32 GetID() const = 0;`
- L288 _public prototype_ `virtual const TArray<uint8>& GetMessageData() const = 0;`

#### enum `Electra::IParserISO14496_12::EBaseBoxType`  
`enum class EBaseBoxType`  
_L291-295_
- L293 _public enumerator_ `Moov`
- L294 _public enumerator_ `Moof`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Electra`
- L46 _macro_ `#define MAKE_BOX_ATOM(a,b,c,d) (IParserISO14496_12::FBoxType)((uint32)a << 24) | ((uint32)b << 16) | ((uint32)c << 8) | ((uint32)d)` — static inline constexpr FBoxType MakeBoxType(unsigned char v1, unsigned char v2, unsigned char v3, unsigned char v4) { return ((uint32)v1 << 24) | ((uint32)v2 << 16) | ((uint32)v3 << 8) | (uint32)v4; }
- L103 _macro_ `#define MAKE_MP4_BRAND(a,b,c,d) (IParserISO14496_12::FBrandType)((uint32)a << 24) | ((uint32)b << 16) | ((uint32)c << 8) | ((uint32)d)`
- L119 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);` — Cancellation delegate for potentially slow tasks.

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Demuxer/ParserISO14496-12_Utils.h` (Private)


#### class `Electra::FMP4StaticDataReader`  
`class FMP4StaticDataReader : public IGenericDataReader`  
_L13-68_
- inherits: `IGenericDataReader`
- L16 _public prototype_ `FMP4StaticDataReader() = default;`
- L17 _public prototype_ `virtual ~FMP4StaticDataReader() = default;`
- L18 _public function_ `virtual void SetParseData(TSharedPtrTS<FWaitableBuffer> InResponseBuffer)`
- L25 _public function_ `virtual bool HaveParseData() const`
- L33 _private function_ `int64 ReadData(void* IntoBuffer, int64 NumBytesToRead, int64 InFromOffset) override` — Methods from IGenericDataReader
- L46 _private function_ `bool HasReachedEOF() const override`
- L50 _private function_ `bool HasReadBeenAborted() const override`
- L54 _private function_ `int64 GetCurrentOffset() const override`
- L58 _private function_ `int64 GetTotalSize() const override`
- L64 _private member_ `TSharedPtrTS<FWaitableBuffer> ResponseBuffer;`
- L65 _private member_ `const uint8* Data = nullptr;`
- L66 _private member_ `int64 DataSize = 0;`
- L67 _private member_ `int64 CurrentOffset = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Demuxer/ParserMKV.h` (Private)


#### class `Electra::IParserMKV`  
`class IParserMKV`  
_L24-213_
- desc: Interface for parsing a Matroska or WebM file.
- L27 _public prototype_ `virtual ~IParserMKV() = default;`
- L29 _public prototype_ `static TSharedPtrTS<IParserMKV> CreateParser(IPlayerSessionServices* PlayerSession);`
- L42 _public prototype_ `virtual FErrorDetail ParseHeader(IGenericDataReader* DataReader, EParserFlags ParseFlags) = 0;` — Parses the header boxes.
- L48 _public prototype_ `virtual FErrorDetail PrepareTracks() = 0;`
- L50 _public prototype_ `virtual FTimeValue GetDuration() const = 0;`
- L52 _public prototype_ `virtual int32 GetNumberOfTracks() const = 0;`
- L193 _public prototype_ `virtual const ITrack* GetTrackByIndex(int32 Index) const = 0;`
- L194 _public prototype_ `virtual const ITrack* GetTrackByTrackID(uint64 TrackID) const = 0;`
- L207 _public prototype_ `virtual TSharedPtrTS<IClusterParser> CreateClusterParser(IGenericDataReader* DataReader, const TArray<uint64>& TrackIDsToParse, EClusterParseFlags ParseFlags) const = 0;` — Create a cluster parser. The data reader MUST start reading on a Matroska cluster.
- L212 _public prototype_ `virtual void AddCue(int64 InCueTimestamp, uint64 InTrackID, int64 InCueRelativePosition, uint64 InCueBlockNumber, int64 InClusterPosition) = 0;` — Adds a cue of it does not exist yet. This may be called during cluster parsing for sync samples since not all sync samples may have been added as cues in the multiplexing process. NOTE: This should only be called for video samples.

#### enum `Electra::IParserMKV::EParserFlags`  
`enum EParserFlags`  
_L31-37_
- L33 _public enumerator_ `ParseFlag_Default = 0`
- L34 _public enumerator_ `ParseFlag_OnlyTracks = 1 << 0`
- L35 _public enumerator_ `ParseFlag_OnlyEssentialLevel1 = 1 << 1`
- L36 _public enumerator_ `ParseFlag_SuppressCueWarning = 1 << 2`

#### class `Electra::IParserMKV::ICueIterator`  
`class ICueIterator`  
_L54-81_
- L57 _public prototype_ `virtual ~ICueIterator() = default;`
- L66 _public prototype_ `virtual UEMediaError StartAtTime(const FTimeValue& AtTime, ESearchMode SearchMode) = 0;`
- L67 _public prototype_ `virtual UEMediaError StartAtFirst() = 0;`
- L68 _public prototype_ `virtual UEMediaError StartAtUniqueID(uint32 CueUniqueID) = 0;`
- L69 _public prototype_ `virtual UEMediaError Next() = 0;`
- L70 _public prototype_ `virtual bool IsAtEOS() const = 0;`
- L72 _public prototype_ `virtual const ITrack* GetTrack() const = 0;`
- L73 _public prototype_ `virtual FTimeValue GetTimestamp() const = 0;`
- L74 _public prototype_ `virtual int64 GetClusterFileOffset() const = 0;`
- L75 _public prototype_ `virtual int64 GetClusterFileSize() const = 0;`
- L76 _public prototype_ `virtual FTimeValue GetClusterDuration() const = 0;`
- L77 _public prototype_ `virtual bool IsLastCluster() const = 0;`
- L79 _public prototype_ `virtual uint32 GetUniqueID() const = 0;`
- L80 _public prototype_ `virtual uint32 GetNextUniqueID() const = 0;`

#### enum `Electra::IParserMKV::ICueIterator::ESearchMode`  
`enum class ESearchMode`  
_L59-64_
- L61 _public enumerator_ `Before`
- L62 _public enumerator_ `After`
- L63 _public enumerator_ `Closest`

#### class `Electra::IParserMKV::IClusterParser`  
`class IClusterParser`  
_L83-174_
- L86 _public prototype_ `virtual ~IClusterParser() = default;`
- L148 _public prototype_ `virtual EParseAction NextParseAction() = 0;` — Performs parsing the cluster content or current frame, returning the next action to take. Returns the action to perform next.
- L153 _public prototype_ `virtual FErrorDetail GetLastError() const = 0;` — Returns the error which resulted in returning the next action `Failure`
- L161 _public prototype_ `virtual const IAction* GetAction() const = 0;` — Returns the base class pointer of the next action to perform. Must be cast to the action indicated by the next action. The action is owned by the parser and must not be destroyed!
- L167 _public prototype_ `virtual int64 GetClusterPosition() const = 0;` — Returns the start offset of the current cluster. This is needed for retries.
- L173 _public prototype_ `virtual int64 GetClusterBlockPosition() const = 0;` — Returns the offset of the current block (simple or group) in the cluster. This is needed for retries.

#### enum `Electra::IParserMKV::IClusterParser::EParseAction`  
`enum class EParseAction`  
_L88-97_
- L90 _public enumerator_ `SkipOver` — Skip over the next n bytes. GetAction() returns an IActionSkipOver action.
- L91 _public enumerator_ `PrependData` — Prepend the frame data with constant data. GetAction() returns an IActionPrependData action.
- L92 _public enumerator_ `ReadFrameData` — Read the next n bytes as frame data. GetAction() returns an IActionReadFrameData action.
- L93 _public enumerator_ `DecryptData` — Decrypt the frame data. GetAction() returns an IActionDecryptData action.
- L94 _public enumerator_ `FrameDone` — Finished this frame data, continue with the next frame. GetAction() returns an IActionFrameDone action. All values (ie timestamps) are valid only now.
- L95 _public enumerator_ `EndOfData` — All cluster input consumed or skipped over. GetAction() returns nullptr.
- L96 _public enumerator_ `Failure` — An error occurred. GetAction() returns nullptr.

#### class `Electra::IParserMKV::IClusterParser::IAction`  
`class IAction`  
_L99-111_
- L102 _public prototype_ `virtual ~IAction() = default;`
- L103 _public prototype_ `virtual uint64 GetTrackID() const = 0;`
- L104 _public prototype_ `virtual FTimeValue GetPTS() const = 0;`
- L105 _public prototype_ `virtual FTimeValue GetDTS() const = 0;`
- L106 _public prototype_ `virtual FTimeValue GetDuration() const = 0;`
- L107 _public prototype_ `virtual bool IsKeyFrame() const = 0;`
- L108 _public prototype_ `virtual int64 GetTimestamp() const = 0;`
- L109 _public prototype_ `virtual int64 GetSegmentRelativePosition() const = 0;`
- L110 _public prototype_ `virtual int64 GetClusterPosition() const = 0;`

#### class `Electra::IParserMKV::IClusterParser::IActionSkipOver`  
`class IActionSkipOver : public IAction`  
_L113-117_
- inherits: `IAction`
- L116 _public prototype_ `virtual int64 GetNumBytesToSkip() const = 0;`

#### class `Electra::IParserMKV::IClusterParser::IActionPrependData`  
`class IActionPrependData : public IAction`  
_L119-123_
- inherits: `IAction`
- L122 _public prototype_ `virtual const TArray<uint8>& GetPrependData() const = 0;`

#### class `Electra::IParserMKV::IClusterParser::IActionReadFrameData`  
`class IActionReadFrameData : public IAction`  
_L125-129_
- inherits: `IAction`
- L128 _public prototype_ `virtual int64 GetNumBytesToRead() const = 0;`

#### class `Electra::IParserMKV::IClusterParser::IActionDecryptData`  
`class IActionDecryptData : public IAction`  
_L131-135_
- inherits: `IAction`
- L134 _public prototype_ `virtual void GetDecryptionInfo(ElectraCDM::FMediaCDMSampleInfo& OutSampleDecryptionInfo) const = 0;`

#### class `Electra::IParserMKV::IClusterParser::IActionFrameDone`  
`class IActionFrameDone : public IAction`  
_L137-141_
- inherits: `IAction`
- L140 _public prototype_ `virtual const TMap<uint64, TArray<uint8>>& GetBlockAdditionalData() const = 0;`

#### class `Electra::IParserMKV::ITrack`  
`class ITrack`  
_L177-190_
- L180 _public prototype_ `virtual ~ITrack() = default;`
- L182 _public prototype_ `virtual uint64 GetID() const = 0;`
- L183 _public prototype_ `virtual FString GetName() const = 0;`
- L184 _public prototype_ `virtual const TArray<uint8>& GetCodecSpecificData() const = 0;`
- L185 _public prototype_ `virtual const FStreamCodecInformation& GetCodecInformation() const = 0;`
- L186 _public prototype_ `virtual const FString GetLanguage() const = 0;`
- L187 _public prototype_ `virtual const BCP47::FLanguageTag GetLanguageTag() const = 0;`
- L189 _public prototype_ `virtual ICueIterator* CreateCueIterator() const = 0;`

#### enum `Electra::IParserMKV::EClusterParseFlags`  
`enum EClusterParseFlags`  
_L196-201_
- L198 _public enumerator_ `ClusterParseFlag_Default = 0`
- L200 _public enumerator_ `ClusterParseFlag_AllowFullDocument = 1 << 0` — Allow the data to be a full EBML document instead of just a cluster.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Demuxer/ParserMKV_Utils.h` (Private)


#### class `Electra::FMKVStaticDataReader`  
`class FMKVStaticDataReader : public IGenericDataReader`  
_L14-58_
- inherits: `IGenericDataReader`
- L17 _public prototype_ `FMKVStaticDataReader() = default;`
- L18 _public prototype_ `virtual ~FMKVStaticDataReader() = default;`
- L19 _public function_ `virtual void SetParseData(TSharedPtrTS<FWaitableBuffer> InResponseBuffer)`
- L27 _private function_ `int64 ReadData(void* InDestinationBuffer, int64 InNumBytesToRead, int64 InFromOffset) override`
- L45 _private function_ `int64 GetCurrentOffset() const override`
- L47 _private function_ `int64 GetTotalSize() const override`
- L49 _private function_ `bool HasReadBeenAborted() const override`
- L51 _private function_ `bool HasReachedEOF() const override`
- L54 _private member_ `TSharedPtrTS<FWaitableBuffer> ResponseBuffer;`
- L55 _private member_ `const uint8* Data = nullptr;`
- L56 _private member_ `int64 DataSize = 0;`
- L57 _private member_ `int64 CurrentOffset = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/ErrorDetail.h` (Private)


#### class `Electra::FErrorDetail`  
`class FErrorDetail`  
_L12-134_
- L15 _public function_ `FErrorDetail() : Error(UEMEDIA_ERROR_OK), Component(Facility::EFacility::Unknown), Code(0)`
- L20 _public function_ `void Clear()`
- L29 _public function_ `bool IsTryAgain() const`
- L34 _public function_ `bool IsSet() const`
- L39 _public function_ `bool IsOK() const`
- L45 _public function_ `bool WasAborted() const`
- L50 _public function_ `bool IsError() const`
- L55 _public function_ `FErrorDetail& SetTryAgain()`
- L61 _public function_ `FErrorDetail& SetError(UEMediaError InError)`
- L67 _public function_ `UEMediaError GetError() const`
- L72 _public function_ `FErrorDetail& SetFacility(Facility::EFacility InFacility)`
- L78 _public function_ `Facility::EFacility GetFacility() const`
- L83 _public function_ `FErrorDetail& SetCode(uint16 InCode)`
- L89 _public function_ `uint16 GetCode() const`
- L94 _public function_ `FErrorDetail& SetMessage(const FString& InDetailMessage)`
- L100 _public function_ `const FString& GetMessage() const`
- L105 _public function_ `FErrorDetail& SetPlatformMessage(const FString& InPlatformMessage)`
- L111 _public function_ `const FString& GetPlatformMessage() const`
- L116 _public function_ `FString GetPrintable() const`
- L129 _private member_ `FString DetailMessage;`
- L130 _private member_ `FString PlatformMessage;`
- L131 _private member_ `UEMediaError Error;`
- L132 _private member_ `Facility::EFacility Component;`
- L133 _private member_ `uint16 Code;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Electra`
- L136 _macro_ `#define ELECTRA_IMPL_DEFAULT_ERROR_METHODS(ErrorFacility) \`
- L169 _macro_ `#define ELECTRA_CLASS_DEFAULT_ERROR_METHODS(SessionService, ErrorFacility) \`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/HTTP/HTTPManager.h` (Private)


#### enum `Electra::HTTP::EStatusErrorCode`  
`enum EStatusErrorCode`  
_L26-35_
- L28 _public enumerator_ `ERRCODE_OK = 0`
- L29 _public enumerator_ `ERRCODE_HTTP_CONNECTION_TIMEOUT = 1`
- L30 _public enumerator_ `ERRCODE_HTTP_RETURNED_ERROR = 2`
- L31 _public enumerator_ `ERRCODE_WRITE_ERROR = 3`
- L32 _public enumerator_ `ERRCODE_HTTP_RANGE_ERROR = 4`
- L33 _public enumerator_ `ERRCODE_HTTP_FILE_COULDNT_READ_FILE = 5`
- L34 _public enumerator_ `ERRCODE_HTTPMODULE_FAILURE = 100`

#### struct `Electra::HTTP::FStatusInfo`  
`struct FStatusInfo`  
_L37-58_
- L39 _public function_ `void Empty()`
- L50 _public member_ `FErrorDetail ErrorDetail;`
- L51 _public member_ `FTimeValue OccurredAtUTC;`
- L52 _public member_ `int32 HTTPStatus = 0;`
- L53 _public member_ `int32 ErrorCode = 0;`
- L54 _public member_ `int32 ConnectionTimeoutAfterMilliseconds = 0;`
- L55 _public member_ `int32 NoDataTimeoutAfterMilliseconds = 0;`
- L56 _public member_ `bool bRedirectionError = false;`
- L57 _public member_ `bool bReadError = false;`

#### struct `Electra::HTTP::FHTTPHeader`  
`struct FHTTPHeader : public FElectraHTTPStreamHeader`  
_L60-81_
- inherits: `FElectraHTTPStreamHeader`
- L62 _public prototype_ `FHTTPHeader() = default;`
- L63 _public function_ `FHTTPHeader(const FString& InHeader, const FString& InValue)`
- L68 _public function_ `void SetFromString(const FString& InString)`
- L77 _public function_ `static void ParseFromString(FHTTPHeader& OutHeader, const FString& InString)`

#### struct `Electra::HTTP::FConnectionInfo`  
`struct FConnectionInfo`  
_L83-163_
- L85 _public member_ `TArray<FHTTPHeader> ResponseHeaders;` — Response headers
- L86 _public member_ `FString EffectiveURL;` — Effective URL after all redirections
- L87 _public member_ `FString ContentType;` — Content-Type header
- L88 _public member_ `FString ContentRangeHeader;`
- L89 _public member_ `FString ContentLengthHeader;`
- L90 _public member_ `FTimeValue RequestStartTime;` — Time at which the request was started
- L91 _public member_ `FTimeValue RequestEndTime;` — Time at which the request ended
- L92 _public member_ `double TimeForDNSResolve = 0.0;` — Time it took to resolve DNS
- L93 _public member_ `double TimeUntilConnected = 0.0;` — Time it took until connected to the server
- L94 _public member_ `double TimeUntilFirstByte = 0.0;` — Time it took until received the first response data byte
- L95 _public member_ `int64 ContentLength = -1;` — Content length, if known. Chunked transfers may have no length (set to -1). Compressed file will store compressed size here!
- L96 _public member_ `int64 BytesReadSoFar = 0;` — Number of bytes read so far.
- L97 _public member_ `int32 NumberOfRedirections = 0;` — Number of redirections performed
- L98 _public member_ `int32 HTTPVersionReceived = 0;` — Version of HTTP header received (10 = 1.0, 11=1.1, 20=2.0)
- L99 _public member_ `bool bIsConnected = false;` — true once connected to the server
- L100 _public member_ `bool bHaveResponseHeaders = false;` — true when response headers have been received
- L101 _public member_ `bool bIsChunked = false;` — true if response is received in chunks
- L102 _public member_ `bool bWasAborted = false;` — true if transfer was aborted.
- L103 _public member_ `bool bHasFinished = false;` — true once the connection is closed regardless of state.
- L104 _public member_ `bool bResponseNotRanged = false;` — true if the response is not a range as was requested.
- L105 _public member_ `bool bIsCachedResponse = false;` — true if the response came from the cache.
- L106 _public member_ `FStatusInfo StatusInfo;`
- L108 _public member_ `mutable FCriticalSection Lock;`
- L109 _public member_ `TArray<IElectraHTTPStreamResponse::FTimingTrace> TimingTraces;`
- L111 _public function_ `void GetTimingTraces(TArray<IElectraHTTPStreamResponse::FTimingTrace>& OutTimingTraces) const`
- L117 _public prototype_ `FConnectionInfo() = default;`
- L119 _public function_ `FConnectionInfo(const FConnectionInfo& rhs)`
- L124 _public function_ `FConnectionInfo& operator = (const FConnectionInfo& rhs)`
- L134 _private function_ `FConnectionInfo& CopyFrom(const FConnectionInfo& rhs)`

#### class `Electra::IElectraHttpManager`  
`class IElectraHttpManager`  
_L168-259_
- L171 _public prototype_ `static TSharedPtrTS<IElectraHttpManager> Create();`
- L173 _public prototype_ `static FString GetDefaultUserAgent();`
- L175 _public prototype_ `virtual ~IElectraHttpManager() = default;`
- L256 _public prototype_ `virtual void AddRequest(TSharedPtrTS<FRequest> Request, bool bAutoRemoveWhenComplete) = 0;`
- L257 _public prototype_ `virtual void RemoveRequest(TSharedPtrTS<FRequest> Request, bool bDoNotWaitForRemoval) = 0;`

#### struct `Electra::IElectraHttpManager::FProgressListener`  
`struct FProgressListener`  
_L179-214_
- L181 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FProgressDelegate, const FRequest*);`
- L182 _public prototype_ `DECLARE_DELEGATE_OneParam(FCompletionDelegate, const FRequest*);`
- L184 _public function_ `~FProgressListener()`
- L188 _public function_ `void Clear()`
- L194 _public function_ `int32 CallProgressDelegate(const FRequest* Request)`
- L203 _public function_ `void CallCompletionDelegate(const FRequest* Request)`
- L211 _public member_ `FCriticalSection Lock;`
- L212 _public member_ `FProgressDelegate ProgressDelegate;`
- L213 _public member_ `FCompletionDelegate CompletionDelegate;`

#### struct `Electra::IElectraHttpManager::FParams`  
`struct FParams`  
_L216-242_
- L218 _public function_ `void AddFromHeaderList(const TArray<FString>& InHeaderList)`
- L228 _public member_ `FString URL;` — URL
- L229 _public member_ `FString Verb;` — GET (default if not set), HEAD, OPTIONS,....
- L230 _public member_ `TMediaOptionalValue<FString> UserAgent;` — Custom user agent string
- L231 _public member_ `ElectraHTTPStream::FHttpRange Range;` — Optional request range
- L232 _public member_ `TArray<HTTP::FHTTPHeader> RequestHeaders;` — Request headers
- L233 _public member_ `TMediaOptionalValue<FString> AcceptEncoding;` — Optional accepted encoding
- L234 _public member_ `FTimeValue ConnectTimeout;` — Optional timeout for connecting to the server
- L235 _public member_ `FTimeValue NoDataTimeout;` — Optional timeout when no data is being received
- L236 _public member_ `TArray<uint8> PostData;` — Data for POST
- L237 _public member_ `bool bCollectTimingTraces = false;` — Whether or not to collect download timing traces.
- L239 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L240 _public member_ `int32 QualityIndex = 0;`
- L241 _public member_ `int32 MaxQualityIndex = 0;`

#### struct `Electra::IElectraHttpManager::FRequest`  
`struct FRequest`  
_L245-254_
- L247 _public member_ `FParams Parameters;`
- L248 _public member_ `FParamDict Options;`
- L249 _public member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L250 _public member_ `TWeakPtrTS<FWaitableBuffer> ReceiveBuffer;`
- L251 _public member_ `TWeakPtrTS<FProgressListener> ProgressListener;`
- L252 _public member_ `TSharedPtrTS<IHTTPResponseCache> ResponseCache;`
- L253 _public member_ `bool bAutoRemoveWhenComplete = false;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraHTTPManager, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraHTTPManager, Log, All);`
- L20 _namespace_ `namespace Electra`
- L24 _namespace_ `namespace HTTP` (scope `Electra`)
- L181 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FProgressDelegate, const FRequest*);`
- L182 _delegate_ `DECLARE_DELEGATE_OneParam(FCompletionDelegate, const FRequest*);`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/HTTP/HTTPResponseCache.h` (Private)


#### class `Electra::IHTTPResponseCache`  
`class IHTTPResponseCache`  
_L16-76_
- L35 _public prototype_ `static TSharedPtrTS<IHTTPResponseCache> Create(int64 InMaxByteCapacity, int32 InMaxEntries, TSharedPtr<IElectraPlayerDataCache, ESPMode::ThreadSafe> ExternalCache);`
- L37 _public prototype_ `virtual ~IHTTPResponseCache() = default;`
- L42 _public prototype_ `virtual void Disable() = 0;` — Call this to disable the cache. Caching makes no sense for Live video streams.
- L47 _public prototype_ `virtual void HandleEntityExpiration() = 0;` — Call this periodically to handle expiration times of cached entities.
- L52 _public prototype_ `virtual void CacheEntity(TSharedPtrTS<FCacheItem> EntityToAdd) = 0;` — Add an entity to the cache.
- L70 _public prototype_ `virtual EScatterResult GetScatteredCacheEntity(TSharedPtrTS<FCacheItem>& OutScatteredCachedEntity, const FString& URL, const ElectraHTTPStream::FHttpRange& Range, const FQualityInfo& ForQuality) = 0;` — Returns the first cached portion of a request. This is used to create responses for which partially cached data already exist and break the request apart to fetch the next portion that is not cached yet. Returns false to indicate that the range specified in the (otherwise empty) cached response must be requested from the origin. Returns true if a - possibly partial - cached response exists. The range that is cached is given in the cache item.
- L73 _protected prototype_ `IHTTPResponseCache() = default;`
- L74 _protected prototype_ `IHTTPResponseCache(const IHTTPResponseCache& other) = delete;`
- L75 _protected prototype_ `IHTTPResponseCache& operator = (const IHTTPResponseCache& other) = delete;`

#### struct `Electra::IHTTPResponseCache::FQualityInfo`  
`struct FQualityInfo`  
_L19-24_
- L21 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L22 _public member_ `int32 QualityIndex = 0;`
- L23 _public member_ `int32 MaxQualityIndex = 0;`

#### struct `Electra::IHTTPResponseCache::FCacheItem`  
`struct FCacheItem`  
_L25-33_
- L27 _public member_ `FString RequestedURL;`
- L28 _public member_ `FString EffectiveURL;`
- L29 _public member_ `ElectraHTTPStream::FHttpRange Range;`
- L30 _public member_ `FTimeValue ExpiresAtUTC;`
- L31 _public member_ `IElectraHTTPStreamResponsePtr Response;`
- L32 _public member_ `FQualityInfo Quality;`

#### enum `Electra::IHTTPResponseCache::EScatterResult`  
`enum EScatterResult`  
_L55-60_
- L57 _public enumerator_ `FullHit` — The entire request is present in the cache
- L58 _public enumerator_ `PartialHit` — Partial data is present in the cache
- L59 _public enumerator_ `Miss` — No part of the request is present in the cache

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/InfoLog.h` (Private)


#### class `Electra::IInfoLog`  
`class IInfoLog`  
_L16-44_
- L28 _public function_ `static const TCHAR* GetLevelName(ELevel InLevel)`

#### enum `Electra::IInfoLog::ELevel`  
`enum ELevel`  
_L19-27_
- L23 _public enumerator_ `Verbose = 1 << 0` — This is a bit mask to allow filtering on exact level (like: Info and Error (but not Warning)) A single event is only exactly one of those however!
- L24 _public enumerator_ `Info = 1 << 1`
- L25 _public enumerator_ `Warning = 1 << 2`
- L26 _public enumerator_ `Error = 1 << 3`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/MediaStreamMetadata.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L11 _typedef_ `using FMetadataParser = MP4Utilities::FMP4MetadataParser;` (scope `Electra`) — We use the mp4 metadata parser as-is for now.

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/OptionalValue.h` (Private)


#### struct `TMediaOptionalValue`  
`template<typename T> struct TMediaOptionalValue`  
_L12-27_
- desc: "Optional" value. Includes a boolean to indicate whether or not it is set.
- L14 _public function_ `TMediaOptionalValue() : bValueIsSet(false)`
- L15 _public function_ `TMediaOptionalValue(const T& v) : OptionalValue(v), bValueIsSet(true)`
- L16 _public function_ `void Set(const T& v)`
- L17 _public function_ `void SetIfNot(const T& v)`
- L18 _public function_ `bool IsSet() const`
- L19 _public function_ `const T& Value() const`
- L20 _public function_ `T GetWithDefault(const T& Default) const`
- L21 _public function_ `void Reset()`
- L24 _private function_ `TMediaOptionalValue& operator = (const T& v)` — Hide assignment from public view
- L25 _private member_ `T OptionalValue;`
- L26 _private member_ `bool bValueIsSet;`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/OutputHandler.h` (Private)


#### class `Electra::IOutputHandlerBase`  
`class IOutputHandlerBase`  
_L22-61_
- L25 _public prototype_ `virtual ~IOutputHandlerBase() = default;`
- L27 _public function_ `virtual void SetMediaSamples(TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> InMediaSamples)`
- L32 _public prototype_ `virtual bool PreparePool(const FParamDict& InParameters) = 0;`
- L33 _public prototype_ `virtual void ClosePool() = 0;`
- L34 _public prototype_ `virtual const FParamDict& GetPoolProperties() = 0;`
- L36 _public prototype_ `virtual void SetClock(TSharedPtr<IMediaRenderClock, ESPMode::ThreadSafe> InClock) = 0;`
- L38 _public prototype_ `virtual void StartOutput() = 0;`
- L39 _public prototype_ `virtual void StopOutput() = 0;`
- L40 _public prototype_ `virtual void Flush() = 0;`
- L56 _public prototype_ `virtual FTimespan GetEnqueuedSampleDuration() = 0;`
- L57 _public prototype_ `virtual void GetEnqueuedSampleInfo(TArray<FEnqueuedSampleInfo>& OutOptionalSampleInfos) = 0;`
- L60 _protected member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> CurrentMediaSamples;`

#### enum `Electra::IOutputHandlerBase::EBufferResult`  
`enum class EBufferResult`  
_L42-46_
- L44 _public enumerator_ `Ok`
- L45 _public enumerator_ `NoBuffer`

#### struct `Electra::IOutputHandlerBase::FEnqueuedSampleInfo`  
`struct FEnqueuedSampleInfo`  
_L48-54_
- L50 _public member_ `FMediaTimeStamp Timestamp;`
- L51 _public member_ `FTimespan Duration;`
- L52 _public member_ `uint64 SampleID;`
- L53 _public member_ `bool bIsDummy;`

#### class `Electra::FOutputHandlerVideo`  
`class FOutputHandlerVideo : public IOutputHandlerBase, public TSharedFromThis<FOutputHandlerVideo, ESPMode::ThreadSafe>`  
_L64-129_
- inherits: `IOutputHandlerBase,TSharedFromThis<FOutputHandlerVideo,ESPMode::ThreadSafe>`
- L67 _public prototype_ `FOutputHandlerVideo();`
- L68 _public prototype_ `virtual ~FOutputHandlerVideo();`
- L71 _public prototype_ `void SetOutputTexturePool(TSharedPtr<FElectraTextureSamplePool, ESPMode::ThreadSafe> InOutputTexturePool);` — Sets the texture pool from where ObtainBuffer() will get an output sample.
- L73 _public prototype_ `bool PreparePool(const FParamDict& InParameters) override;`
- L74 _public prototype_ `void ClosePool() override;`
- L75 _public prototype_ `const FParamDict& GetPoolProperties() override;`
- L77 _public prototype_ `void SetClock(TSharedPtr<IMediaRenderClock, ESPMode::ThreadSafe> InClock) override;`
- L78 _public prototype_ `void StartOutput() override;`
- L79 _public prototype_ `void StopOutput() override;`
- L80 _public prototype_ `void Flush() override;`
- L82 _public prototype_ `FTimespan GetEnqueuedSampleDuration() override;`
- L83 _public prototype_ `void GetEnqueuedSampleInfo(TArray<FEnqueuedSampleInfo>& OutOptionalSampleInfos) override;`
- L85 _public prototype_ `bool CanReceiveOutputSample();`
- L86 _public prototype_ `EBufferResult ObtainOutputSample(FElectraTextureSamplePtr& OutTextureSample);`
- L94 _public prototype_ `void ReturnOutputSample(FElectraTextureSamplePtr InTextureSampleToReturn, EReturnSampleType InSendToOutputQueueType);`
- L97 _public prototype_ `uint64 GetTotalAddedSamples();` — Returns the total number of video samples added to the queue.
- L99 _public prototype_ `uint64 GetTotalNumDroppedSamples();` — Returns the total number of samples that were dropped from the queue.
- L101 _public prototype_ `uint64 GetNewlyNumDroppedSamples(bool bInClear);` — Returns the number of dropped samples since the last time this methods was called.
- L104 _private prototype_ `void ReleaseSampleToPool(IElectraTextureSampleBase* InTextureSampleToReturn, uint64 InSampleID);`
- L105 _private prototype_ `void SendAllPendingSamples();`
- L107 _private member_ `TSharedPtr<FElectraTextureSamplePool, ESPMode::ThreadSafe> OutputTexturePool;`
- L108 _private member_ `TSharedPtr<IMediaRenderClock, ESPMode::ThreadSafe> Clock;`
- L115 _private member_ `FCriticalSection PendingOutputSamplesLock;`
- L116 _private member_ `TArray<FPendingSample> PendingOutputSamples;`
- L117 _private member_ `FParamDict PoolProperties;`
- L118 _private member_ `std::atomic<uint64> NumTotalSamplesAdded { 0 };`
- L119 _private member_ `std::atomic<uint64> NumTotalSamplesDropped { 0 };`
- L120 _private member_ `std::atomic<uint64> TotalSamplesDroppedAtLastCall { 0 };`
- L121 _private member_ `int32 NumOutputSamples = 0;`
- L122 _private member_ `bool bSendOutput = false;`
- L123 _private member_ `bool bDidSendFirst = false;`
- L125 _private member_ `FCriticalSection EnqueuedSampleInfosLock;`
- L126 _private member_ `TArray<FEnqueuedSampleInfo> EnqueuedSampleInfos;`
- L127 _private member_ `FTimespan EnqueuedSampleDuration;`
- L128 _private member_ `uint64 NextSampleID = 0;`

#### enum `Electra::FOutputHandlerVideo::EReturnSampleType`  
`enum class EReturnSampleType`  
_L87-92_
- L89 _public enumerator_ `SendToQueue`
- L90 _public enumerator_ `DontSendToQueue`
- L91 _public enumerator_ `DummySample`

#### struct `Electra::FOutputHandlerVideo::FPendingSample`  
`struct FPendingSample`  
_L110-114_
- L112 _public member_ `FEnqueuedSampleInfo SampleInfo;`
- L113 _public member_ `FElectraTextureSamplePtr Sample;`

#### class `Electra::FOutputHandlerAudio`  
`class FOutputHandlerAudio : public IOutputHandlerBase, public TSharedFromThis<FOutputHandlerAudio, ESPMode::ThreadSafe>`  
_L132-205_
- inherits: `IOutputHandlerBase,TSharedFromThis<FOutputHandlerAudio,ESPMode::ThreadSafe>`
- L135 _public prototype_ `FOutputHandlerAudio();`
- L136 _public prototype_ `virtual ~FOutputHandlerAudio();`
- L139 _public prototype_ `void SetOutputAudioSamplePool(TSharedPtr<FElectraAudioSamplePool, ESPMode::ThreadSafe> InOutputAudioSamplePool);` — Sets the sample pool from where ObtainBuffer() will get an output sample.
- L141 _public prototype_ `bool PreparePool(const FParamDict& InParameters) override;`
- L142 _public prototype_ `void ClosePool() override;`
- L143 _public prototype_ `const FParamDict& GetPoolProperties() override;`
- L145 _public prototype_ `void SetClock(TSharedPtr<IMediaRenderClock, ESPMode::ThreadSafe> InClock) override;`
- L146 _public prototype_ `void StartOutput() override;`
- L147 _public prototype_ `void StopOutput() override;`
- L148 _public prototype_ `void Flush() override;`
- L150 _public prototype_ `FTimespan GetEnqueuedSampleDuration() override;`
- L151 _public prototype_ `void GetEnqueuedSampleInfo(TArray<FEnqueuedSampleInfo>& OutOptionalSampleInfos) override;`
- L153 _public prototype_ `bool CanReceiveOutputSample();`
- L154 _public prototype_ `EBufferResult ObtainOutputSample(FElectraAudioSamplePtr& OutTextureSample);`
- L162 _public prototype_ `void ReturnOutputSample(FElectraAudioSamplePtr InTextureSampleToReturn, EReturnSampleType InSendToOutputQueueType);`
- L164 _public prototype_ `void SetPlaybackRate(double InCurrentPlaybackRate, double InIntendedPlaybackRate, bool bInCurrentlyPaused);`
- L165 _public prototype_ `FTimeRange GetSupportedRenderRateScale();`
- L166 _public prototype_ `void SetPlayRateScale(double InNewScale);`
- L167 _public prototype_ `double GetPlayRateScale();`
- L171 _private member_ `const uint32 NumInterpolationSamplesAt48kHz = 60;` — Constants used for time stretching
- L172 _private member_ `const double MinPlaybackSpeed = 0.8;`
- L173 _private member_ `const double MaxPlaybackSpeed = 1.5;`
- L174 _private member_ `const double MinResampleSpeed = 0.98;`
- L175 _private member_ `const double MaxResampleSpeed = 1.02;`
- L177 _private prototype_ `void ProcessSampleBlock(TArray<FElectraAudioSamplePtr>& OutProcessedSampleBlocks, FElectraAudioSamplePtr InSampleBlock, double InRate);`
- L178 _private prototype_ `void ReleaseSampleToPool(FElectraAudioSample* InTextureSampleToReturn, uint64 InSampleID);`
- L179 _private prototype_ `void SendPendingSamples();`
- L181 _private member_ `TSharedPtr<FElectraAudioSamplePool, ESPMode::ThreadSafe> OutputAudioSamplePool;`
- L182 _private member_ `TSharedPtr<IMediaRenderClock, ESPMode::ThreadSafe> Clock;`
- L189 _private member_ `FCriticalSection PendingOutputSamplesLock;`
- L190 _private member_ `TArray<FPendingSample> PendingOutputSamples;`
- L191 _private member_ `FParamDict PoolProperties;`
- L192 _private member_ `int32 NumOutputSamples = 0;`
- L193 _private member_ `bool bSendOutput = false;`
- L195 _private member_ `double CurrentPlaybackRate = 0.0;`
- L196 _private member_ `double IntendedPlaybackRate = 0.0;`
- L198 _private member_ `FCriticalSection EnqueuedSampleInfosLock;`
- L199 _private member_ `TArray<FEnqueuedSampleInfo> EnqueuedSampleInfos;`
- L200 _private member_ `FTimespan EnqueuedSampleDuration;`
- L201 _private member_ `uint64 NextSampleID = 0;`
- L204 _private member_ `TPimplPtr<FAudioVars> AudioVars;`

#### enum `Electra::FOutputHandlerAudio::EReturnSampleType`  
`enum class EReturnSampleType`  
_L155-160_
- L157 _public enumerator_ `SendToQueue`
- L158 _public enumerator_ `DontSendToQueue`
- L159 _public enumerator_ `DummySample`

#### struct `Electra::FOutputHandlerAudio::FPendingSample`  
`struct FPendingSample`  
_L184-188_
- L186 _public member_ `FEnqueuedSampleInfo SampleInfo;`
- L187 _public member_ `FElectraAudioSamplePtr Sample;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Electra`
- L208 _namespace_ `namespace OutputHandlerOptionKeys` (scope `Electra`)
- L210 _variable_ `static const FName NumBuffers(TEXT("num_` (scope `Electra::OutputHandlerOptionKeys`)
- L211 _variable_ `static const FName PTS(TEXT("pts"` (scope `Electra::OutputHandlerOptionKeys`)
- L212 _variable_ `static const FName Duration(TEXT("dura` (scope `Electra::OutputHandlerOptionKeys`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/ABRRules/ABRFixedStream.h` (Private)


#### class `Electra::IABRFixedStream`  
`class IABRFixedStream : public IABRRule`  
_L10-15_
- inherits: `IABRRule`
- L13 _public prototype_ `static IABRFixedStream* Create(IABRInfoInterface* InIInfo, EMediaFormatType InFormatType, EABRPresentationType InPresentationType);`
- L14 _public prototype_ `virtual ~IABRFixedStream() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/ABRRules/ABRInternal.h` (Private)


#### enum `Electra::EABRPresentationType`  
`enum class EABRPresentationType`  
_L9-14_
- L11 _public enumerator_ `OnDemand`
- L12 _public enumerator_ `Live`
- L13 _public enumerator_ `LowLatency`

#### struct `Electra::FABRStreamInformation`  
`struct FABRStreamInformation`  
_L16-42_
- L33 _public member_ `FString AdaptationSetUniqueID;`
- L34 _public member_ `FString RepresentationUniqueID;`
- L36 _public member_ `FStreamHealth Health;`
- L38 _public member_ `FStreamCodecInformation::FResolution Resolution;` — Set for convenience.
- L39 _public member_ `int32 Bitrate = 0;`
- L40 _public member_ `int32 QualityIndex = 0;`
- L41 _public member_ `bool bLowLatencyEnabled = false;`

#### struct `Electra::FABRStreamInformation::FStreamHealth`  
`struct FStreamHealth`  
_L18-31_
- L20 _public function_ `FStreamHealth()`
- L24 _public function_ `void Reset()`
- L29 _public member_ `FTimeValue BecomesAvailableAgainAtUTC;`
- L30 _public member_ `Metrics::FSegmentDownloadStats LastDownloadStats;`

#### class `Electra::IABRInfoInterface`  
`class IABRInfoInterface : public IPlayerABRLiveControl`  
_L44-57_
- inherits: `IPlayerABRLiveControl`
- L47 _public prototype_ `virtual ~IABRInfoInterface() = default;`
- L48 _public prototype_ `virtual bool HaveOptionValue(const FName& InOption) = 0;`
- L49 _public prototype_ `virtual const FVariantValue GetOptionValue(const FName& InOption) = 0;`
- L51 _public prototype_ `virtual TSharedPtrTS<FABRStreamInformation> GetStreamInformation(const Metrics::FSegmentDownloadStats& FromDownloadStats) = 0;`
- L52 _public prototype_ `virtual const TArray<TSharedPtrTS<FABRStreamInformation>>& GetStreamInformations(EStreamType InForStreamType) = 0;`
- L53 _public prototype_ `virtual FStreamCodecInformation::FResolution GetMaxStreamResolution() = 0;`
- L54 _public prototype_ `virtual int32 GetBandwidthCeiling() = 0;`
- L56 _public prototype_ `virtual void LogMessage(IInfoLog::ELevel Level, const FString& Message) = 0;`

#### class `Electra::IABRRule`  
`class IABRRule`  
_L60-91_
- L63 _public prototype_ `virtual ~IABRRule() = default;`
- L66 _public prototype_ `virtual FABRDownloadProgressDecision ReportDownloadProgress(const Metrics::FSegmentDownloadStats& SegmentDownloadStats) = 0;` — Same as the ones from IAdaptiveStreamingPlayerMetrics
- L67 _public prototype_ `virtual void ReportDownloadEnd(const Metrics::FSegmentDownloadStats& SegmentDownloadStats) = 0;`
- L68 _public prototype_ `virtual void ReportBufferingStart(Metrics::EBufferingReason BufferingReason) = 0;`
- L69 _public prototype_ `virtual void ReportBufferingEnd(Metrics::EBufferingReason BufferingReason) = 0;`
- L70 _public prototype_ `virtual void ReportPlaybackPaused() = 0;`
- L71 _public prototype_ `virtual void ReportPlaybackResumed() = 0;`
- L72 _public prototype_ `virtual void ReportPlaybackEnded() = 0;`
- L74 _public prototype_ `virtual FTimeValue GetMinBufferTimeForPlayback(IAdaptiveStreamSelector::EMinBufferType InBufferingType, FTimeValue InDefaultMBT) = 0;`
- L75 _public prototype_ `virtual IAdaptiveStreamSelector::FRebufferAction GetRebufferAction() = 0;`
- L76 _public prototype_ `virtual IAdaptiveStreamSelector::EHandlingAction PeriodicHandle() = 0;`
- L77 _public prototype_ `virtual void DebugPrint(void* pThat, void (*pPrintFN)(void* pThat, const char *pFmt, ...)) = 0;`
- L79 _public prototype_ `virtual void RepresentationsChanged(EStreamType InStreamType, TSharedPtrTS<IManifest::IPlayPeriod> InCurrentPlayPeriod) = 0;`
- L80 _public prototype_ `virtual void SetBandwidth(int64 bitsPerSecond) = 0;`
- L81 _public prototype_ `virtual void SetForcedNextBandwidth(int64 bitsPerSecond, double minBufferTimeBeforePlayback) = 0;`
- L82 _public prototype_ `virtual int64 GetLastBandwidth() = 0;`
- L83 _public prototype_ `virtual int64 GetAverageBandwidth() = 0;`
- L84 _public prototype_ `virtual int64 GetAverageThroughput() = 0;`
- L85 _public prototype_ `virtual double GetAverageLatency() = 0;`
- L87 _public prototype_ `virtual void PrepareStreamCandidateList(TArray<TSharedPtrTS<FABRStreamInformation>>& OutCandidates, EStreamType StreamType, const TSharedPtrTS<IManifest::IPlayPeriod>& CurrentPlayPeriod, const FTimeValue& TimeNow) = 0;`
- L88 _public prototype_ `virtual IAdaptiveStreamSelector::ESegmentAction EvaluateForError(TArray<TSharedPtrTS<FABRStreamInformation>>& InOutCandidates, EStreamType StreamType, FTimeValue& OutDelay, const TSharedPtrTS<IManifest::IPlayPeriod>& CurrentPlayPeriod, const TSharedPtrTS<const IStreamSegment>& CurrentSegment, const FTimeValue& TimeNow) = 0;`
- L89 _public prototype_ `virtual IAdaptiveStreamSelector::ESegmentAction EvaluateForQuality(TArray<TSharedPtrTS<FABRStreamInformation>>& InOutCandidates, EStreamType StreamType, FTimeValue& OutDelay, const TSharedPtrTS<IManifest::IPlayPeriod>& CurrentPlayPeriod, const TSharedPtrTS<const IStreamSegment>& CurrentSegment, const FTimeValue& TimeNow) = 0;`
- L90 _public prototype_ `virtual IAdaptiveStreamSelector::ESegmentAction PerformSelection(const TArray<TSharedPtrTS<FABRStreamInformation>>& InCandidates, EStreamType StreamType, FTimeValue& OutDelay, const TSharedPtrTS<IManifest::IPlayPeriod>& CurrentPlayPeriod, const TSharedPtrTS<const IStreamSegment>& CurrentSegment, const FTimeValue& TimeNow) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/ABRRules/ABRLiveStream.h` (Private)


#### class `Electra::IABRLiveStream`  
`class IABRLiveStream : public IABRRule`  
_L10-15_
- inherits: `IABRRule`
- L13 _public prototype_ `static IABRLiveStream* Create(IABRInfoInterface* InIInfo, EMediaFormatType InFormatType, EABRPresentationType InPresentationType);`
- L14 _public prototype_ `virtual ~IABRLiveStream() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/ABRRules/ABROptionKeynames.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L9 _namespace_ `namespace ABR` (scope `Electra`)
- L15 _variable_ `const FName OptionKeyABR_CDNSegmentDenyHTTPStatus(TEXT("abr:` (scope `Electra::ABR`) — (int) HTTP status code if returned by CDN for any segment request will take that stream permanently offline.

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/ABRRules/ABRStatisticTypes.h` (Private)


#### class `Electra::TRollingAverage`  
`template <typename T> class TRollingAverage`  
_L13-70_
- L16 _public function_ `TRollingAverage()`
- L19 _public function_ `void Reset()`
- L25 _public function_ `T AddValue(T InNewValue)`
- L46 _public function_ `T GetAverage() const`
- L51 _public function_ `T GetMin() const`
- L56 _public function_ `T GetMax() const`
- L61 _public function_ `int32 GetNumSamples() const`
- L66 _private member_ `T Avg;`
- L67 _private member_ `T Min;`
- L68 _private member_ `T Max;`
- L69 _private member_ `int32 N;`

#### class `Electra::TSimpleMovingAverage`  
`template <typename T> class TSimpleMovingAverage`  
_L74-199_
- L77 _public function_ `TSimpleMovingAverage(int32 maxNumSMASamples = kMaxSMASamples) : MaxSamples(maxNumSMASamples)`
- L84 _public function_ `TSimpleMovingAverage(const TSimpleMovingAverage& Other)`
- L89 _public function_ `void Resize(int32 maxSMASamples)`
- L97 _public function_ `void Reset()`
- L103 _public function_ `void InitializeTo(const T& v)`
- L111 _public function_ `void AddValue(const T& value)` — Adds a sample to the mean.
- L129 _public function_ `T GetLastSample(T V=T(0)) const` — Returns the sample value that was added last, if one exists
- L139 _public function_ `T GetSMA(T V=T(0)) const` — Returns the simple moving average from all the collected history samples. See: https://en.wikipedia.org/wiki/Moving_average#Simple_moving_average
- L153 _public function_ `T GetAverage(T V=T(0)) const`
- L162 _public function_ `T GetWMA(T V=T(0)) const` — Returns the weighted moving average from all the collected history samples. See: https://en.wikipedia.org/wiki/Moving_average#Weighted_moving_average
- L184 _private function_ `void InternalCopy(const TSimpleMovingAverage& Other)`
- L195 _private member_ `mutable FCriticalSection CriticalSection;`
- L196 _private member_ `TMediaQueueNoLock<T> SimpleMovingAverage;` — Simple moving average
- L197 _private member_ `T LastSample;` — The last sample that was added.
- L198 _private member_ `int32 MaxSamples;` — Limit number of SMA samples (0 < mMaxSMASamples <= kMaxSMASamples)

#### enum `Electra::TSimpleMovingAverage::(anonymous)`  
``  
_L180-182_

#### class `Electra::TValueHistory`  
`template <typename T> class TValueHistory`  
_L205-356_
- L208 _public function_ `TValueHistory(int32 InMaxSamples = 5)`
- L216 _public function_ `TValueHistory(const TValueHistory& Other)`
- L222 _public function_ `void Resize(int32 InMaxSamples)`
- L232 _public function_ `void Reset()`
- L240 _public function_ `void InitializeTo(const T& v)`
- L247 _public function_ `void AddValue(const T& value)`
- L265 _public function_ `T GetWeightedMax(T V=T(0)) const`
- L272 _public function_ `T GetSMA(T V=T(0)) const`
- L288 _public function_ `T GetWMA(T V=T(0)) const`
- L307 _private function_ `void InternalCopy(const TValueHistory& Other)`
- L318 _private function_ `T InternalWMA(T V=T(0)) const`
- L333 _private function_ `void SortByIndex() const`
- L342 _private function_ `void SortByValueDescending() const`
- L351 _private member_ `mutable FCriticalSection Lock;`
- L352 _private member_ `mutable TArray<FSample> Samples;`
- L353 _private member_ `mutable ESortOrder CurrentSortOrder = ESortOrder::Index;`
- L354 _private member_ `int64 NextIndex = 0;`
- L355 _private member_ `int32 MaxSamples = 0;`

#### struct `Electra::TValueHistory::FSample`  
`struct FSample`  
_L296-300_
- L298 _public member_ `T Value;`
- L299 _public member_ `uint64 Index;`

#### enum `Electra::TValueHistory::ESortOrder`  
`enum class ESortOrder`  
_L301-305_
- L303 _public enumerator_ `Index`
- L304 _public enumerator_ `Value`

#### class `Electra::FChunkedDownloadBandwidthCalculator`  
`class FChunkedDownloadBandwidthCalculator`  
_L361-542_
- L364 _public function_ `FChunkedDownloadBandwidthCalculator(const Metrics::FSegmentDownloadStats& InSegmentStats) : SegmentStats(InSegmentStats)`
- L368 _public function_ `double Calculate()`
- L524 _private function_ `int32 GetDownloadChunkIndexForPos(int64 InByteOffset, int32 InStartAtTrace)`
- L539 _private member_ `const Metrics::FSegmentDownloadStats& SegmentStats;`
- L540 _private member_ `int64 LastAvailByteCount = 0;`
- L541 _private member_ `double TimeUntilFirstByte = 0.0;`

#### struct `Electra::FChunkedDownloadBandwidthCalculator::Calculate::FE`  
`struct FE`  
_L370-376_
- L372 _public member_ `double T;`
- L373 _public member_ `double Bps;`
- L374 _public function_ `const double GetY() const`

#### class `Electra::FChunkedDownloadBandwidthCalculator::Calculate::FInterquartileRange`  
`class FInterquartileRange`  
_L432-467_
- L435 _public function_ `void Apply(TArray<FE>& Out, const TArray<FE>& In)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L181 _enumerator_ `kMaxSMASamples = 5` (scope `Electra::TSimpleMovingAverage::__anonfcf743320103`) — Default amount of SMA samples
- L338 _function_ `Samples.Sort([](const FSample& a, const FSample&b) { return a.Index < b.Index; });` (scope `Electra::TValueHistory::SortByIndex`)
- L347 _function_ `Samples.Sort([](const FSample& a, const FSample&b) { return b.Value < a.Value; });` (scope `Electra::TValueHistory::SortByValueDescending`)
- L441 _function_ `Out.Sort([](const FE& e1, const FE& e2) { return e1.GetY() < e2.GetY(); });` (scope `Electra::FChunkedDownloadBandwidthCalculator::Calculate::FInterquartileRange::Apply`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/ABRRules/ABRVoDPlus.h` (Private)


#### class `Electra::IABROnDemandPlus`  
`class IABROnDemandPlus : public IABRRule`  
_L10-15_
- inherits: `IABRRule`
- L13 _public prototype_ `static IABROnDemandPlus* Create(IABRInfoInterface* InIInfo, EMediaFormatType InFormatType, EABRPresentationType InPresentationType);`
- L14 _public prototype_ `virtual ~IABROnDemandPlus() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptivePlayerMetadataKeynames.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L9 _variable_ `const FName MediaInfoStartTimecodeValue(TEXT("Star` (scope `Electra`) — String
- L10 _variable_ `const FName MediaInfoStartTimecodeFrameRate(TEXT("Star` (scope `Electra`) — String
- L11 _variable_ `const FName MediaInfoVideoDecoderProvider(TEXT("Vide` (scope `Electra`) — String
- L12 _variable_ `const FName MediaInfoAudioDecoderProvider(TEXT("Audi` (scope `Electra`) — String
- L15 _variable_ `const FLazyName MediaInfoVideoBitrateCurrent(TEXT("Vide` (scope `Electra`) — Bitrate of video currently being displayed.
- L17 _variable_ `const FLazyName MediaInfoVideoBitrateBuffering(TEXT("Vide` (scope `Electra`) — Bitrate of video currently being buffered ahead of time.
- L20 _variable_ `const FLazyName MediaInfoAudioBitrateCurrent(TEXT("Audi` (scope `Electra`) — Bitrate of audio currently being heard.
- L22 _variable_ `const FLazyName MediaInfoAudioBitrateBuffering(TEXT("Audi` (scope `Electra`) — Bitrate of audio currently being buffered ahead of time.

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptivePlayerOptionKeynames.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L10 _variable_ `const FName OptionKeyContentID(TEXT("cont` (scope `Electra`) — (FString) An ID uniquely identifying the content. Must not exceed 64 characters.
- L13 _variable_ `const FName OptionKeySessionID(TEXT("sess` (scope `Electra`) — (FString) A session ID, in UUID format. Limited to 64 characters if not UUID format.
- L16 _variable_ `const FName OptionKeyOutputTexturePoolID(TEXT("outp` (scope `Electra`) — (int64) ID of the platform specific output texture pool registered with the decoder platform resources.
- L19 _variable_ `const FName OptionKeyWorkerThreads(TEXT("work` (scope `Electra`) — (FString) Use of worker threads. ("shared", "worker" or "worker_and_events")
- L22 _variable_ `const FName OptionKeyMimeType(TEXT("mime` (scope `Electra`) — (FString) mime type of URL to load
- L25 _variable_ `const FName OptionKeyMaxVerticalResolution(TEXT("max_` (scope `Electra`) — (int64) value indicating the maximum vertical resolution to be used for any video stream.
- L28 _variable_ `const FName OptionKeyMaxVerticalResolutionAbove30fps(TEXT("max_` (scope `Electra`) — (int64) value indicating the maximum vertical resolution to be used for video streams of more than 30fps.
- L31 _variable_ `const FName OptionKeyInitialBitrate(TEXT("init` (scope `Electra`) — (int64) value indicating the bitrate to start playback with (initial start).
- L34 _variable_ `const FName OptionKeySeekStartBitrate(TEXT("seek` (scope `Electra`) — (int64) value indicating the bitrate to start buffering with when seeking (not at playback start)
- L37 _variable_ `const FName OptionKeyRebufferStartBitrate(TEXT("rebu` (scope `Electra`) — (int64) value indicating the bitrate to start rebuffering with
- L40 _variable_ `const FName OptionKeyLiveSeekableEndOffset(TEXT("seek` (scope `Electra`) — (FTimeValue) value specifying how many seconds away from the Live media timeline the seekable range should end.
- L43 _variable_ `const FName OptionRebufferingContinuesLoading(TEXT("rebu` (scope `Electra`) — (bool) true to just finish the currently loading segment when rebuffering. false to start over with.
- L46 _variable_ `const FName OptionThrowErrorWhenRebuffering(TEXT("thro` (scope `Electra`) — (bool) true to throw a playback error when rebuffering occurs, false to continue normally.
- L49 _variable_ `const FName OptionKeyFrameAccurateSeek(TEXT("fram` (scope `Electra`) — (bool) true to perform frame accurate seeks (slow as decoding and discarding data from a preceeding keyframe is required)
- L52 _variable_ `const FName OptionKeyDoNotTruncateAtPresentationEnd(TEXT("do_n` (scope `Electra`) — (bool) true to not truncate the media segment access units at the end of the presentation. Must only be used without a set playback range end!
- L54 _variable_ `const FName OptionKeyCurrentAvgStartingVideoBitrate(TEXT("curr` (scope `Electra`)
- L56 _variable_ `const FName OptionKeyExcludedCodecsVideo(TEXT("excl` (scope `Electra`)
- L57 _variable_ `const FName OptionKeyExcludedCodecsAudio(TEXT("excl` (scope `Electra`)
- L58 _variable_ `const FName OptionKeyExcludedCodecsSubtitles(TEXT("excl` (scope `Electra`)
- L60 _variable_ `const FName OptionKeyPreferredCodecsVideo(TEXT("pref` (scope `Electra`)
- L61 _variable_ `const FName OptionKeyPreferredCodecsAudio(TEXT("pref` (scope `Electra`)
- L62 _variable_ `const FName OptionKeyPreferredCodecsSubtitles(TEXT("pref` (scope `Electra`)
- L64 _variable_ `const FName OptionKeyResponseCacheMaxEntries(TEXT("http` (scope `Electra`)
- L65 _variable_ `const FName OptionKeyResponseCacheMaxByteSize(TEXT("http` (scope `Electra`)
- L67 _variable_ `const FName OptionKeyParseTimecodeInfo(TEXT("pars` (scope `Electra`)
- L69 _variable_ `const FName OptionKeyPlaylistProperties(TEXT("play` (scope `Electra`)
- L71 _variable_ `const FName OptionKeyCMCDConfiguration(TEXT("cmcd` (scope `Electra`)
- L73 _variable_ `const FName OptionKeyFrameStatInterval(TEXT("fram` (scope `Electra`)
- L75 _namespace_ `namespace CustomOptions` (scope `Electra`)
- L77 _variable_ `const TCHAR* const Custom_EpicStaticStart = TEXT("Epi` (scope `Electra::CustomOptions`)
- L78 _variable_ `const TCHAR* const Custom_EpicDynamicStart = TEXT("Epi` (scope `Electra::CustomOptions`)
- L79 _variable_ `const TCHAR* const Custom_EpicUTCUrl = TEXT("Epi` (scope `Electra::CustomOptions`)
- L80 _variable_ `const TCHAR* const Custom_EpicUTCNow = TEXT("Epi` (scope `Electra::CustomOptions`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptiveStreamingPlayer.h` (Private)


#### class `Electra::IAdaptiveStreamingPlayer`  
`class IAdaptiveStreamingPlayer : public TMediaNoncopyable<IAdaptiveStreamingPlayer>`  
_L26-366_
- inherits: `TMediaNoncopyable<IAdaptiveStreamingPlayer>`
- desc: This class declares the adaptive streaming player.
- L44 _public prototype_ `static TSharedPtr<IAdaptiveStreamingPlayer, ESPMode::ThreadSafe> Create(const FCreateParam& InCreateParameters);`
- L51 _public prototype_ `virtual void SetStaticResourceProviderCallback(const TSharedPtr<IAdaptiveStreamingPlayerResourceProvider, ESPMode::ThreadSafe>& InStaticResourceProvider) = 0;` — Various resource providers/delegates These must be set prior to calling `Initialize()` and MUST NOT be changed until player destruction.
- L57 _public prototype_ `virtual void AddMetricsReceiver(IAdaptiveStreamingPlayerMetrics* InMetricsReceiver) = 0;` — Metric event listener
- L58 _public prototype_ `virtual void RemoveMetricsReceiver(IAdaptiveStreamingPlayerMetrics* InMetricsReceiver) = 0;`
- L64 _public prototype_ `virtual void AddAEMSReceiver(TWeakPtrTS<IAdaptiveStreamingPlayerAEMSReceiver> InReceiver, FString InForSchemeIdUri, FString InForValue, IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode InDispatchMode) = 0;` — Application Event or Metadata Stream (AEMS) receiver Please refer to ISO/IEC 23009-1:2019/DAM 1:2020(E)
- L65 _public prototype_ `virtual void RemoveAEMSReceiver(TWeakPtrTS<IAdaptiveStreamingPlayerAEMSReceiver> InReceiver, FString InForSchemeIdUri, FString InForValue, IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode InDispatchMode) = 0;`
- L71 _public prototype_ `virtual void Initialize(const FParamDict& InOptions) = 0;` — Initializes the player. Options may be passed in to affect behaviour.
- L76 _public prototype_ `virtual void ModifyOptions(const FParamDict& InOptionsToSetOrChange, const FParamDict& InOptionsToClear) = 0;` — Modifies options. Not all options are modifiable during playback.
- L81 _public prototype_ `virtual FVariantValue GetMediaInfo(FName InKey) const = 0;` — Returns a player option value.
- L91 _public prototype_ `virtual void SetInitialStreamAttributes(EStreamType StreamType, FStreamSelectionAttributes InitialSelection) = 0;` — Sets the attributes for the stream to start buffering for and playing. This must be set before calling SeekTo() or LoadManifest() to have an immediate effect. A best effort to match a stream with the given attributes will be made. If there is no exact match the player will make an educated guess. Any later call to SelectTrackByMetadata() internally overwrites these initial attributes with those of the explicitly selected track.
- L105 _public prototype_ `virtual void EnableFrameAccurateSeeking(bool bEnabled) = 0;` — Enables or disables frame accurate seeking. Frame accurate positioning may require internal decoding and discarding of video and audio from an earlier keyframe up to the intended time, which may make seeking significantly slower. This also affects looping which implicitly seeks back to the loop point when the end is reached. Frame accurate seeking is enabled by default. This method is intended mostly to disable frame accurate seeking on this player instance. This should be called prior to SeekTo() and should only be called once on the player instance to disable or re-enable frame accurate seeking. Calling this during playback may have undesired results.
- L111 _public prototype_ `virtual TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> GetMediaSamples() = 0;` — Interfacing functions
- L118 _public prototype_ `virtual void LoadManifest(const FString& ManifestURL) = 0;` — Manifest loading functions Issue a load and parse of the manifest/main playlist file. Make initial stream selection choice by calling SetInitialStreamAttributes() beforehand.
- L166 _public prototype_ `virtual void SeekTo(const FSeekParam& NewPosition) = 0;` — Seek to a new position and play from there. This includes first playstart. Playback is initially paused on first player use and must be resumed to begin. Query the seekable range (GetSeekableRange()) to get the valid time range. If the seek-to time is not set the seek will start at the beginning for on-demand presentations and on the Live edge for Live presentations. Seeks can be issued while a seek is already executing. The seek parameters control behaviour. If seeking is performed for scrubbing any new seek will be performed only when the previous seek has completed, otherwise the current seek will be canceled in favor of the new. If the new position being seeked to is within the specified distance to the last completed seek a new seek will not be performed. If new seeks are performed in rapid succession (as in scrubbing) not every new position will be seeked to. Seek commands are aggregated and the position set with the most recent call will be used as soon as any previous seek completes. As a result you will NOT receive a ReportSeekCompleted() notification for every seek requested, only for those that were executed and allowed to complete.
- L169 _public prototype_ `virtual void Pause() = 0;` — Pauses playback.
- L172 _public prototype_ `virtual void Resume() = 0;` — Resumes playback.
- L175 _public prototype_ `virtual void Stop() = 0;` — Stops playback. Playback cannot be resumed. Final player events will be sent to registered listeners.
- L205 _public prototype_ `virtual void SetPlaybackRange(const FPlaybackRange& InPlaybackRange) = 0;` — Constrains playback to the specified time range, which should be a subset of GetTimelineRange(). The playback range can be specified via URL fragment parameters on the URL given to LoadManifest() if the mime type allows for it. If you set the playback range before calling LoadManifest() the URL parameter will not be used. Otherwise the URL parameters set the playback range if they are specified. You can query the playback range set by URL parameters as soon as HaveMetadata() returns true. Setting a playback range through this method overrides URL parameters. To set or change only the start or end of the playback range, set only the corresponding TOptional<> and leave the other unset. To disable either start or end set the value to FTimeValue::GetInvalid(). If you only set start or end, the other value may be set by the respective URL parameter. To fully disable any playback range that may be present on the URL you should set the range to invalid values once HaveMetadata() returns true. Setting a playback range during playback will result in an immediate seek to the current playback position. Frame accurate seeking is recommended.
- L206 _public prototype_ `virtual void GetPlaybackRange(FPlaybackRange& OutPlaybackRange) = 0;`
- L223 _public prototype_ `virtual void SetLooping(const FLoopParam& InLoopParams) = 0;` — Puts playback into loop mode if possible. Live streams cannot be made to loop as they have infinite duration. Looping is constrained to the playback range, if one is set.
- L254 _public prototype_ `virtual TRangeSet<double> GetSupportedRates(EPlaybackRateType InForPlayRateType) = 0;` — Returns ranges the playback rate can be set to. There are two types, one `Unthinned`, where (ideally) no frames will be dropped and `Thinned`, where frames will be dropped to maintain the playback rate. Either way, the player will not resample audio or generate interpolated frames of video. Decoded samples will be delivered to the renderer as they are. It is also up to the renderers to consume the data at a faster or slower rate to actually realize the desired playback rate. The range of supported rates depends on the type of media and the decoder capability to decode faster than realtime. If the media allows for adaptive bitrate selection the player will choose the stream to play back accordingly. In thinned mode it will need to drop and not decode samples, so the renderer will not receive all the possible data. Live streams will only allow for rates of 0.0 (pause) and 1.0 (real time play forward).
- L259 _public prototype_ `virtual void SetPlayRate(double InDesiredPlayRate, const FTrickplayParams& InParameters) = 0;`
- L260 _public prototype_ `virtual double GetPlayRate() const = 0;`
- L267 _public prototype_ `virtual FErrorDetail GetError() const = 0;` — Error related functions Returns the error that has caused playback issues.
- L274 _public prototype_ `virtual bool HaveMetadata() const = 0;` — State functions Returns whether or not a manifest has been loaded and assigned yet.
- L276 _public prototype_ `virtual FTimeValue GetDuration() const = 0;` — Returns the duration of the video. Returns invalid time when there is nothing to play. Returns positive infinite for live streams.
- L278 _public prototype_ `virtual FTimeValue GetPlayPosition() const = 0;` — Returns the current play position. Returns invalid time when there is nothing to play.
- L280 _public prototype_ `virtual void GetSeekableRange(FTimeRange& OutRange) const = 0;` — Returns the seekable range.
- L282 _public prototype_ `virtual void GetTimelineRange(FTimeRange& OutRange) const = 0;` — Returns the timeline range.
- L284 _public prototype_ `virtual bool HasEnded() const = 0;` — Returns true when playback has finished.
- L286 _public prototype_ `virtual bool IsBuffering() const = 0;` — Returns true when data is being buffered/rebuffered, false otherwise.
- L288 _public prototype_ `virtual bool IsSeeking() const = 0;` — Returns true when seeking is in progress. False if not.
- L290 _public prototype_ `virtual bool IsPlaying() const = 0;` — Returns true when playing back, false if not.
- L292 _public prototype_ `virtual bool IsPaused() const = 0;` — Returns true when paused, false if not.
- L301 _public prototype_ `virtual void GetLoopState(FLoopState& OutLoopState) const = 0;` — Returns the current loop state.
- L304 _public prototype_ `virtual void GetTrackMetadata(TArray<FTrackMetadata>& OutTrackMetadata, EStreamType StreamType) const = 0;` — Returns track metadata of the currently active play period.
- L307 _public prototype_ `virtual void GetSelectedTrackAttributes(FStreamSelectionAttributes& OutAttributes, EStreamType StreamType) const = 0;` — Returns attributes of the currently selected track.
- L315 _public prototype_ `virtual void GetReplayEventState(FEventReplayState& OutReplayEventState) const = 0;` — Returns if the media is set to be a replay (configured via URL fragment parameters)
- L323 _public prototype_ `virtual void SetBitrateCeiling(int32 HighestSelectableBitrate) = 0;` — Sets the highest bitrate when selecting a candidate stream.
- L327 _public prototype_ `virtual void SetMaxResolution(int32 MaxWidth, int32 MaxHeight) = 0;` — Sets the maximum resolution to use. Set both to 0 to disable, set only one to limit widht or height only. Setting both will limit on either width or height, whichever limits first.
- L331 _public prototype_ `virtual void SelectTrackByAttributes(EStreamType StreamType, const FStreamSelectionAttributes& Attributes) = 0;` — Selects a track based on given attributes (which can be constructed from one of the array members returned by GetTrackMetadata()). This selection will explicitly override the initial stream attributes set by SetInitialStreamAttributes() and be applied automatically for upcoming periods.
- L334 _public prototype_ `virtual void DeselectTrack(EStreamType StreamType) = 0;` — Deselect track. The stream may continue to stream to allow for immediate selection/activation but no data will be fed to the decoder.
- L337 _public prototype_ `virtual bool IsTrackDeselected(EStreamType StreamType) = 0;` — Returns true if the track stream of the specified type has beed deselected through DeselectTrack().
- L350 _public prototype_ `virtual void QueryStreamBufferInfo(FStreamBufferInfo& OutStreamBufferInfo, EStreamType InStreamType) = 0;`
- L356 _public prototype_ `virtual void SuspendOrResumeDecoders(bool bSuspend, const FParamDict& InOptions) = 0;` — Special functions needed for application suspend & resume.
- L362 _public prototype_ `static void DebugHandle(void* pPlayer, void (*debugDrawPrintf)(void* pPlayer, const char *pFmt, ...));` — Debug functions
- L365 _protected prototype_ `virtual ~IAdaptiveStreamingPlayer() = default;`

#### struct `Electra::IAdaptiveStreamingPlayer::FCreateParam`  
`struct FCreateParam`  
_L29-42_
- L31 _public member_ `TSharedPtr<FElectraTextureSamplePool, ESPMode::ThreadSafe> OutputTexturePool;`
- L32 _public member_ `TSharedPtr<FElectraAudioSamplePool, ESPMode::ThreadSafe> OutputAudioSamplePool;`
- L34 _public member_ `FGuid ExternalPlayerGUID;`
- L41 _public member_ `EWorkerThreads WorkerThreads = EWorkerThreads::Shared;`

#### enum `Electra::IAdaptiveStreamingPlayer::FCreateParam::EWorkerThreads`  
`enum class EWorkerThreads`  
_L35-40_
- L37 _public enumerator_ `Shared`
- L38 _public enumerator_ `DedicatedWorker`
- L39 _public enumerator_ `DedicatedWorkerAndEventDispatch`

#### struct `Electra::IAdaptiveStreamingPlayer::FSeekParam`  
`struct FSeekParam`  
_L124-144_
- desc: Playback related functions
- L126 _public function_ `FSeekParam()`
- L130 _public function_ `void Reset()`
- L137 _public member_ `FTimeValue Time;` — Time to seek to.
- L139 _public member_ `TOptional<int32> NewSequenceIndex;` — New sequence index to associate with the newly decoded samples.
- L141 _public member_ `TOptional<int32> StartingBitrate;` — Maximum stream bitrate to use when seeking.
- L143 _public member_ `TOptional<bool> bOptimizeForScrubbing;` — Optimize for frame scrubbing (faster display of frame at target time)?

#### struct `Electra::IAdaptiveStreamingPlayer::FPlaybackRange`  
`struct FPlaybackRange`  
_L178-182_
- L180 _public member_ `TOptional<FTimeValue> Start;`
- L181 _public member_ `TOptional<FTimeValue> End;`

#### struct `Electra::IAdaptiveStreamingPlayer::FLoopParam`  
`struct FLoopParam`  
_L209-220_
- L211 _public function_ `FLoopParam()`
- L215 _public function_ `void Reset()`
- L219 _public member_ `bool bEnableLooping;`

#### enum `Electra::IAdaptiveStreamingPlayer::EPlaybackRateType`  
`enum class EPlaybackRateType`  
_L229-235_
- desc: "Trickplay" related functions
- L232 _public enumerator_ `Unthinned` — Smooth playback, not dropping any frames.
- L234 _public enumerator_ `Thinned` — Dropping frames

#### struct `Electra::IAdaptiveStreamingPlayer::FTrickplayParams`  
`struct FTrickplayParams`  
_L256-258_

#### struct `Electra::IAdaptiveStreamingPlayer::FLoopState`  
`struct FLoopState`  
_L294-298_
- L296 _public member_ `int64 Count = 0;` — Number of times playback jumped back to loop. 0 on first playthrough, 1 on first loop, etc.
- L297 _public member_ `bool bIsEnabled = false;` — true if looping is enabled, false if not.

#### struct `Electra::IAdaptiveStreamingPlayer::FEventReplayState`  
`struct FEventReplayState`  
_L309-313_
- L311 _public member_ `FTimeValue ProposedJoinTime;`
- L312 _public member_ `bool bIsReplayEvent = false;`

#### struct `Electra::IAdaptiveStreamingPlayer::FStreamBufferInfo`  
`struct FStreamBufferInfo`  
_L343-349_
- desc: Buffer related functions
- L345 _public member_ `TArray<FTimeRange> TimeAvailable;` — Time range currently available in the buffer
- L346 _public member_ `TArray<FTimeRange> TimeRequested;` — Time range requested for download.
- L347 _public member_ `TArray<FTimeRange> TimeEnqueued;` — Time range already enqueued with the renderer.
- L348 _public member_ `bool bIsBufferActive = false;` — true if the buffer is active, false if not (eg. track not selected)

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptiveStreamingPlayerABR.h` (Private)


#### class `Electra::IPlayerABRLiveControl`  
`class IPlayerABRLiveControl`  
_L17-70_
- L20 _public prototype_ `virtual ~IPlayerABRLiveControl() = default;`
- L23 _public prototype_ `virtual FTimeValue ABRGetPlayPosition() const = 0;` — Provides the current playback position.
- L26 _public prototype_ `virtual FTimeRange ABRGetTimeline() const = 0;` — Provides the current full media timeline, not adjusted for seeking.
- L29 _public prototype_ `virtual FTimeValue ABRGetWallclockTime() const = 0;` — Provides the current wallclock time (server real time).
- L32 _public prototype_ `virtual bool ABRIsLive() const = 0;` — Returns true if this is a Live presentation, false for VoD.
- L35 _public prototype_ `virtual bool ABRShouldPlayOnLiveEdge() const = 0;` — Returns true if playback should be on the Live edge. false if the user intentionally seeked away from the edge.
- L38 _public prototype_ `virtual TSharedPtrTS<const FLowLatencyDescriptor> ABRGetLowLatencyDescriptor() const = 0;` — Provides the current low latency descriptor if low latency playback is active. Returns nullptr if not.
- L41 _public prototype_ `virtual FTimeValue ABRGetDesiredLiveEdgeLatency() const = 0;` — Provides the desired latency to the live edge for both low-latency and normal live playback.
- L44 _public prototype_ `virtual FTimeValue ABRGetLatency() const = 0;` — Provides the currently measured latency to the live edge.
- L47 _public prototype_ `virtual FTimeValue ABRGetPlaySpeed() const = 0;` — Provides the current playback speed.
- L56 _public prototype_ `virtual void ABRGetStreamBufferStats(FABRBufferStats& OutBufferStats, EStreamType ForStream) = 0;`
- L58 _public prototype_ `virtual FTimeRange ABRGetSupportedRenderRateScale() = 0;`
- L59 _public prototype_ `virtual void ABRSetRenderRateScale(double InRenderRateScale) = 0;`
- L60 _public prototype_ `virtual double ABRGetRenderRateScale() const = 0;`
- L67 _public prototype_ `virtual void ABRTriggerClockSync(EClockSyncType InClockSyncType) = 0;`
- L69 _public prototype_ `virtual void ABRTriggerPlaylistRefresh() = 0;`

#### struct `Electra::IPlayerABRLiveControl::FABRBufferStats`  
`struct FABRBufferStats`  
_L50-55_
- desc: Returns the current stream access unit buffer stats.
- L52 _public member_ `FTimeValue PlayableContentDuration;`
- L53 _public member_ `bool bReachedEnd = false;`
- L54 _public member_ `bool bEndOfTrack = false;`

#### enum `Electra::IPlayerABRLiveControl::EClockSyncType`  
`enum class EClockSyncType`  
_L62-66_
- L64 _public enumerator_ `Recommended`
- L65 _public enumerator_ `Required`

#### class `Electra::IAdaptiveStreamSelector`  
`class IAdaptiveStreamSelector : public IAdaptiveStreamingPlayerMetrics`  
_L73-178_
- inherits: `IAdaptiveStreamingPlayerMetrics`
- L77 _public prototype_ `static TSharedPtrTS<IAdaptiveStreamSelector> Create(IPlayerSessionServices* PlayerSessionServices);` — Create an instance of this class
- L78 _public prototype_ `virtual ~IAdaptiveStreamSelector() = default;`
- L80 _public prototype_ `virtual void SetFormatType(EMediaFormatType FormatType) = 0;`
- L83 _public prototype_ `virtual void SetCurrentPlaybackPeriod(EStreamType InStreamType, TSharedPtrTS<IManifest::IPlayPeriod> CurrentPlayPeriod) = 0;` — Sets the manifest from which to select streams.
- L86 _public prototype_ `virtual void SetBandwidth(int64 bitsPerSecond) = 0;` — Sets the initial bandwidth, either from guessing, past history or a current measurement.
- L89 _public prototype_ `virtual void SetForcedNextBandwidth(int64 bitsPerSecond, double minBufferTimeBeforePlayback) = 0;` — Sets a forced bitrate for the next segment fetches until the given duration of playable content has been received.
- L97 _public prototype_ `virtual FTimeValue GetMinBufferTimeForPlayback(EMinBufferType InBufferingType, FTimeValue InDefaultMBT) = 0;`
- L105 _public prototype_ `virtual EHandlingAction PeriodicHandle() = 0;`
- L122 _public prototype_ `virtual FRebufferAction GetRebufferAction() = 0;` — Call when rebuffering occurs to get the recommended action. This implies that rebuffering has actually occurred. The ABR may take internal action to switch quality when this is called!
- L138 _public prototype_ `virtual void MarkStreamAsUnavailable(const FDenylistedStream& DenylistedStream) = 0;`
- L139 _public prototype_ `virtual void MarkStreamAsAvailable(const FDenylistedStream& NoLongerDenylistedStream) = 0;`
- L141 _public prototype_ `virtual void PathwayChanged(const FString& InNewPathway) = 0;`
- L143 _public prototype_ `virtual FABRDownloadProgressDecision ReportDownloadProgress(const Metrics::FSegmentDownloadStats& SegmentDownloadStats) = 0;`
- L144 _public prototype_ `virtual void ReportDownloadEnd(const Metrics::FSegmentDownloadStats& SegmentDownloadStats) = 0;`
- L148 _public prototype_ `virtual int64 GetLastBandwidth() = 0;` — Returns the last measured bandwidth sample in bps.
- L151 _public prototype_ `virtual int64 GetAverageBandwidth() = 0;` — Returns the average measured bandwidth in bps.
- L154 _public prototype_ `virtual int64 GetAverageThroughput() = 0;` — Returns the average measured throughput in bps.
- L157 _public prototype_ `virtual double GetAverageLatency() = 0;` — Returns the average measured latency in seconds.
- L160 _public prototype_ `virtual void SetBandwidthCeiling(int32 HighestManifestBitrate) = 0;` — Sets a highest bandwidth limit. Call with 0 to disable.
- L163 _public prototype_ `virtual void SetMaxVideoResolution(int32 MaxWidth, int32 MaxHeight) = 0;` — Limits video resolution.
- L174 _public prototype_ `virtual ESegmentAction SelectSuitableStreams(FTimeValue& OutDelay, TSharedPtrTS<const IStreamSegment> CurrentSegment) = 0;` — Selects a feasible stream from the stream set to fetch the next fragment from.
- L177 _public prototype_ `virtual void DebugPrint(void* pThat, void (*pPrintFN)(void* pThat, const char *pFmt, ...)) = 0;`

#### enum `Electra::IAdaptiveStreamSelector::EMinBufferType`  
`enum class EMinBufferType`  
_L91-96_
- L93 _public enumerator_ `Initial`
- L94 _public enumerator_ `Seeking`
- L95 _public enumerator_ `Rebuffering`

#### enum `Electra::IAdaptiveStreamSelector::EHandlingAction`  
`enum class EHandlingAction`  
_L99-103_
- L101 _public enumerator_ `None`
- L102 _public enumerator_ `SeekToLive`

#### struct `Electra::IAdaptiveStreamSelector::FRebufferAction`  
`struct FRebufferAction`  
_L107-118_
- L116 _public member_ `EAction Action = EAction::Restart;`
- L117 _public member_ `int32 SuggestedRestartBitrate = 0;`

#### enum `Electra::IAdaptiveStreamSelector::FRebufferAction::EAction`  
`enum class EAction`  
_L109-115_
- L111 _public enumerator_ `Restart`
- L112 _public enumerator_ `ContinueLoading`
- L113 _public enumerator_ `GoToLive`
- L114 _public enumerator_ `ThrowError`

#### struct `Electra::IAdaptiveStreamSelector::FDenylistedStream`  
`struct FDenylistedStream`  
_L124-137_
- L126 _public member_ `FString AssetUniqueID;`
- L127 _public member_ `FString AdaptationSetUniqueID;`
- L128 _public member_ `FString RepresentationUniqueID;`
- L129 _public member_ `FString CDN;`
- L130 _public function_ `bool operator == (const FDenylistedStream& rhs) const`

#### enum `Electra::IAdaptiveStreamSelector::ESegmentAction`  
`enum class ESegmentAction`  
_L165-171_
- L167 _public enumerator_ `FetchNext` — Fetch the next segment normally.
- L168 _public enumerator_ `Retry` — Retry the same segment. Another quality or CDN may have been picked out already.
- L169 _public enumerator_ `Fill` — Fill the segment's duration worth with dummy data.
- L170 _public enumerator_ `Fail` — Abort playback

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptiveStreamingPlayerABR_State.h` (Private)


#### struct `Electra::FABRDownloadProgressDecision`  
`struct FABRDownloadProgressDecision`  
_L10-30_
- L12 _public function_ `FABRDownloadProgressDecision() : Flags(EDecisionFlags::eABR_Continue)`
- L16 _public function_ `void Reset()`
- L28 _public member_ `EDecisionFlags Flags;`
- L29 _public member_ `FString Reason;`

#### enum `Electra::FABRDownloadProgressDecision::EDecisionFlags`  
`enum EDecisionFlags`  
_L21-27_
- L23 _public enumerator_ `eABR_Continue = 0`
- L24 _public enumerator_ `eABR_AbortDownload = 1 << 0`
- L25 _public enumerator_ `eABR_EmitPartialData = 1 << 1`
- L26 _public enumerator_ `eABR_InsertFillerData = 1 << 2`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptiveStreamingPlayerEvents.h` (Private)


#### class `Electra::IAdaptiveStreamingPlayerAEMSEvent`  
`class IAdaptiveStreamingPlayerAEMSEvent`  
_L11-43_
- L21 _public prototype_ `virtual ~IAdaptiveStreamingPlayerAEMSEvent() = default;`
- L24 _public prototype_ `virtual EOrigin GetOrigin() const = 0;` — Returns where the event originated from.
- L27 _public prototype_ `virtual FString GetSchemeIdUri() const = 0;` — Returns the event's scheme id URI
- L30 _public prototype_ `virtual FString GetValue() const = 0;` — Returns the event's value.
- L33 _public prototype_ `virtual FString GetID() const = 0;` — Returns the event's ID.
- L36 _public prototype_ `virtual FTimeValue GetPresentationTime() const = 0;` — Returns the event's presentation time.
- L39 _public prototype_ `virtual FTimeValue GetDuration() const = 0;` — Returns the event's duration. If the event has no defined duration the return value will be invalid.
- L42 _public prototype_ `virtual const TArray<uint8>& GetMessageData() const = 0;` — Returns the event's message data.

#### enum `Electra::IAdaptiveStreamingPlayerAEMSEvent::EOrigin`  
`enum class EOrigin`  
_L14-19_
- L16 _public enumerator_ `EventStream`
- L17 _public enumerator_ `InbandEventStream`
- L18 _public enumerator_ `TimedMetadata`

#### class `Electra::IAdaptiveStreamingPlayerAEMSReceiver`  
`class IAdaptiveStreamingPlayerAEMSReceiver`  
_L57-69_
- desc: Client side event receiver. As per ISO/IEC 23009-1:2019/DAM 1 event receivers subscribing to "on_receive" will receive the event the instant it is received by the player. Handling of the event is the sole responsibility of the receiver. Events will be received at any time and the same event can be received multiple times. Events will also be received in no particular order and events may also already be outdated when received. This happens with events contained inside the playlist every time the playlist is updated on the server and reloaded by the client.
- L60 _public prototype_ `virtual ~IAdaptiveStreamingPlayerAEMSReceiver() = default;`
- L68 _public prototype_ `virtual void OnMediaPlayerEventReceived(TSharedPtrTS<IAdaptiveStreamingPlayerAEMSEvent> InEvent, EDispatchMode InDispatchMode) = 0;`

#### enum `Electra::IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode`  
`enum class EDispatchMode`  
_L62-66_
- L64 _public enumerator_ `OnReceive`
- L65 _public enumerator_ `OnStart`

#### class `Electra::IAdaptiveStreamingPlayerAEMSHandler`  
`class IAdaptiveStreamingPlayerAEMSHandler`  
_L74-108_
- L77 _public prototype_ `static IAdaptiveStreamingPlayerAEMSHandler* Create();`
- L78 _public prototype_ `virtual ~IAdaptiveStreamingPlayerAEMSHandler() = default;`
- L81 _public prototype_ `virtual void ExecutePendingEvents(FTimeValue CurrentPlaybackTime) = 0;` — Call periodically to dispatch pending events.
- L83 _public prototype_ `virtual void FlushEverything() = 0;` — Unconditionally flushes all events from the queue.
- L85 _public prototype_ `virtual void FlushDynamic() = 0;` — Informs that playback has moved to a new position in either direction. This may discard dynamic events from streams but keep period events from the playlist.
- L87 _public prototype_ `virtual void NewUpcomingPeriod(FString NewPeriodID, FTimeRange NewPeriodTimeRange) = 0;` — Informs that a new playback period is coming up. This is to truncate period events that would extend over their originating period.
- L89 _public prototype_ `virtual void PlaybackStartingUp() = 0;` — Informs that playback is starting up.
- L91 _public prototype_ `virtual void PlaybackPeriodTransition(FString NewPeriodID, FTimeRange NewPeriodTimeRange) = 0;` — Informs that playback has moved forward into another period. Events of an earlier period that are outside its associated periods time range will not fire.
- L93 _public prototype_ `virtual void PlaybackReachedEnd(FTimeValue CurrentPlaybackTime) = 0;` — Informs that playback has ended.
- L102 _public prototype_ `virtual void AddEvent(TSharedPtrTS<IAdaptiveStreamingPlayerAEMSEvent> InNewEvent, FString InPeriodID, EEventAddMode InAddMode) = 0;` — Enqueues an event. Checks if the new event ID (GetID()) for the given scheme/value has already been added earlier and either adds, updates or ignores the event based on the given InAddMode.
- L106 _public prototype_ `virtual void AddAEMSReceiver(TWeakPtrTS<IAdaptiveStreamingPlayerAEMSReceiver> InReceiver, FString InForSchemeIdUri, FString InForValue, IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode InDispatchMode, bool bIsAppReceiver) = 0;` — Adds/removes event receivers.
- L107 _public prototype_ `virtual void RemoveAEMSReceiver(TWeakPtrTS<IAdaptiveStreamingPlayerAEMSReceiver> InReceiver, FString InForSchemeIdUri, FString InForValue, IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode InDispatchMode) = 0;`

#### enum `Electra::IAdaptiveStreamingPlayerAEMSHandler::EEventAddMode`  
`enum class EEventAddMode`  
_L95-99_
- L97 _public enumerator_ `AddIfNotExists`
- L98 _public enumerator_ `UpdateIfExists`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptiveStreamingPlayerInternal.h` (Private)


#### class `Electra::FMediaRenderClock`  
`class FMediaRenderClock : public IMediaRenderClock`  
_L69-178_
- inherits: `IMediaRenderClock`
- L72 _public function_ `FMediaRenderClock() : bIsPaused(true)`
- L77 _public prototype_ `virtual ~FMediaRenderClock() = default;`
- L79 _public function_ `void SetCurrentTime(ERendererType ForRenderer, const FTimeValue& CurrentRenderTime) override`
- L92 _public function_ `FTimeValue GetInterpolatedRenderTime(ERendererType FromRenderer) override`
- L107 _public function_ `void Start()`
- L121 _public function_ `void Stop()`
- L136 _public function_ `bool IsRunning() const`
- L154 _private function_ `FClock* GetClock(ERendererType ForRenderer)`
- L175 _private member_ `FCriticalSection Lock;`
- L176 _private member_ `FClock Clock[3];`
- L177 _private member_ `bool bIsPaused;`

#### struct `Electra::FMediaRenderClock::FClock`  
`struct FClock`  
_L142-152_
- L144 _public function_ `FClock()`
- L149 _public member_ `FTimeValue RenderTime;`
- L150 _public member_ `FTimeValue LastSystemBaseTime;`
- L151 _public member_ `FTimeValue RunningTimeOffset;`

#### struct `Electra::FDroppedFrameStats`  
`struct FDroppedFrameStats`  
_L182-203_
- L188 _public function_ `void Clear()`
- L196 _public member_ `TArray<FEntry> Entries;`
- L197 _public member_ `TRollingAverage<int64> AverageDropsPerInterval;`
- L198 _public member_ `int64 LastProcessedTime = -1;`
- L199 _public member_ `int64 PausedDelta = -1;`
- L200 _public member_ `int64 ReportingIntervalMs = -1;`
- L201 _public member_ `uint32 NumIntervals = 0;`
- L202 _public member_ `uint32 NumIntervalsWithDrops = 0;`

#### struct `Electra::FDroppedFrameStats::FEntry`  
`struct FEntry`  
_L184-187_
- L186 _public member_ `uint64 DropCount;`

#### struct `Electra::FPlaybackState`  
`struct FPlaybackState`  
_L211-644_
- desc: Interchange structure between the player worker thread and the public API to avoid mutex locks all over the place.
- L213 _public function_ `FPlaybackState()`
- L217 _public function_ `void Reset()`
- L248 _public member_ `mutable FCriticalSection Lock;`
- L249 _public member_ `FTimeRange SeekableRange;`
- L250 _public member_ `FTimeRange TimelineRange;`
- L251 _public member_ `FTimeValue Duration;`
- L252 _public member_ `FTimeValue CurrentPlayPosition;`
- L253 _public member_ `FTimeValue EncoderLatency;`
- L254 _public member_ `FTimeValue CurrentLiveLatency;`
- L255 _public member_ `FTimeValue EndPlaybackAtTime;`
- L256 _public member_ `IAdaptiveStreamingPlayer::FLoopState LoopState;`
- L257 _public member_ `FTimeRange ActivePlaybackRange;`
- L258 _public member_ `FTimeRange NewPlaybackRange;`
- L259 _public member_ `TRangeSet<double> UnthinnedPlaybackRates;`
- L260 _public member_ `TRangeSet<double> ThinnedPlaybackRates;`
- L261 _public member_ `double CurrentPlaybackRate;`
- L262 _public member_ `double DesiredPlaybackRate;`
- L263 _public member_ `bool bHaveMetadata;`
- L264 _public member_ `bool bHasEnded;`
- L265 _public member_ `bool bIsSeeking;`
- L266 _public member_ `bool bIsBuffering;`
- L267 _public member_ `bool bIsPlaying;`
- L268 _public member_ `bool bIsPaused;`
- L269 _public member_ `bool bPlayrangeHasChanged;`
- L270 _public member_ `bool bLoopStateHasChanged;`
- L271 _public member_ `bool bShouldPlayOnLiveEdge;`
- L272 _public member_ `TUniquePtr<IAdaptiveStreamingPlayer::FLoopParam> PendingLoopParams;`
- L273 _public member_ `TArray<FTrackMetadata> VideoTracks;`
- L274 _public member_ `TArray<FTrackMetadata> AudioTracks;`
- L275 _public member_ `TArray<FTrackMetadata> SubtitleTracks;`
- L276 _public member_ `FTimeRange CurrentSegmentDownloadTimeRange[4];` — 0=video, 1=audio, 2=subtitiles, 3=UNSUPPORTED
- L279 _public function_ `void SetSeekableRange(const FTimeRange& TimeRange)`
- L284 _public function_ `void GetSeekableRange(FTimeRange& OutRange) const`
- L290 _public function_ `void SetTimelineRange(const FTimeRange& TimeRange)`
- L295 _public function_ `void GetTimelineRange(FTimeRange& OutRange) const`
- L301 _public function_ `void SetDuration(const FTimeValue& InDuration)`
- L306 _public function_ `FTimeValue GetDuration() const`
- L312 _public function_ `void SetPlayPosition(const FTimeValue& InPosition)`
- L317 _public function_ `FTimeValue GetPlayPosition() const`
- L323 _public function_ `void SetEncoderLatency(const FTimeValue& InEncoderLatency)`
- L328 _public function_ `FTimeValue GetEncoderLatency() const`
- L334 _public function_ `void SetCurrentLiveLatency(const FTimeValue& InCurrentLiveLatency)`
- L339 _public function_ `FTimeValue GetCurrentLiveLatency() const`
- L345 _public function_ `void SetShouldPlayOnLiveEdge(bool bInShouldPlayOnLiveEdge)`
- L350 _public function_ `bool GetShouldPlayOnLiveEdge() const`
- L356 _public function_ `void SetHaveMetadata(bool bInHaveMetadata)`
- L361 _public function_ `bool GetHaveMetadata() const`
- L367 _public function_ `void SetHasEnded(bool bInHasEnded)`
- L372 _public function_ `bool GetHasEnded() const`
- L378 _public function_ `void SetIsSeeking(bool bInIsSeeking)`
- L383 _public function_ `bool GetIsSeeking() const`
- L389 _public function_ `void SetIsBuffering(bool bInIsBuffering)`
- L394 _public function_ `bool GetIsBuffering() const`
- L400 _public function_ `void SetIsPlaying(bool bInIsPlaying)`
- L405 _public function_ `bool GetIsPlaying() const`
- L411 _public function_ `void SetIsPaused(bool bInIsPaused)`
- L416 _public function_ `bool GetIsPaused() const`
- L422 _public function_ `void SetPausedAndPlaying(bool bInIsPaused, bool bInIsPlaying)`
- L436 _public function_ `bool SetTrackMetadata(const TArray<FTrackMetadata> &InVideoTracks, const TArray<FTrackMetadata>& InAudioTracks, const TArray<FTrackMetadata>& InSubtitleTracks)`
- L462 _public function_ `void GetTrackMetadata(TArray<FTrackMetadata> &OutVideoTracks, TArray<FTrackMetadata>& OutAudioTracks, TArray<FTrackMetadata>& OutSubtitleTracks) const`
- L469 _public function_ `void HaveTrackMetadata(bool& bOutHaveVideo, bool& bOutHaveAudio, bool& bOutHaveSubtitle) const`
- L477 _public function_ `void SetLoopState(const IAdaptiveStreamingPlayer::FLoopState& InLoopState)`
- L482 _public function_ `void GetLoopState(IAdaptiveStreamingPlayer::FLoopState& OutLoopState) const`
- L493 _public function_ `void SetLoopStateEnable(bool bEnable)`
- L499 _public function_ `void SetPlayRange(const IAdaptiveStreamingPlayer::FPlaybackRange& InNewRange)`
- L511 _public function_ `void SetPlayRange(const FTimeRange& InNewRange)`
- L520 _public function_ `FTimeRange GetPlayRange()`
- L525 _public function_ `void GetPlayRange(IAdaptiveStreamingPlayer::FPlaybackRange& OutRange)`
- L539 _public function_ `void ActivateNewPlayRange(const FTimeRange* InTimeRange)`
- L545 _public function_ `FTimeRange GetActivePlayRange()`
- L550 _public function_ `bool GetPlayRangeHasChanged()`
- L556 _public function_ `void SetPlaybackRates(IAdaptiveStreamingPlayer::EPlaybackRateType InForType, const TRangeSet<double>& InRates)`
- L568 _public function_ `TRangeSet<double> GetPlaybackRates(IAdaptiveStreamingPlayer::EPlaybackRateType InForType)`
- L574 _public function_ `void SetDesiredPlayRate(double InDesiredPlayRate, const IAdaptiveStreamingPlayer::FTrickplayParams& )`
- L579 _public function_ `double GetDesiredPlayRate() const`
- L584 _public function_ `void SetCurrentPlayRate(double InRate)`
- L589 _public function_ `double GetCurrentPlayRate() const`
- L596 _public function_ `void RequestLooping(const IAdaptiveStreamingPlayer::FLoopParam& InLoopParams)`
- L601 _public function_ `TUniquePtr<IAdaptiveStreamingPlayer::FLoopParam> GetPendingLoopRequest()`
- L606 _public function_ `void SetLoopStateHasChanged(bool bWasChanged)`
- L611 _public function_ `bool GetLoopStateHasChanged()`
- L617 _public function_ `void SetPlaybackEndAtTime(const FTimeValue& InAtTime)`
- L622 _public function_ `FTimeValue GetPlaybackEndAtTime() const`
- L628 _public function_ `FTimeRange GetCurrentDownloadRequestTimeRange(EStreamType InStreamType)`
- L633 _public function_ `void SetCurrentDownloadRequestTimeRange(EStreamType InStreamType, const FTimeRange& InRange)`
- L638 _public function_ `void ClearCurrentDownloadRequestTimeRange(EStreamType InStreamType)`

#### struct `Electra::FMetricEvent`  
`struct FMetricEvent`  
_L651-949_
- L738 _public member_ `EType Type;`
- L739 _public member_ `FParam Param;`
- L740 _public member_ `TWeakPtr<FAdaptiveStreamingPlayer, ESPMode::ThreadSafe> Player;`
- L741 _public member_ `FMediaEvent *EventSignal = nullptr;`
- L743 _public function_ `static TSharedPtrTS<FMetricEvent> ReportOpenSource(const FString& URL)`
- L750 _public function_ `static TSharedPtrTS<FMetricEvent> ReportReceivedMainPlaylist(const FString& EffectiveURL)`
- L757 _public function_ `static TSharedPtrTS<FMetricEvent> ReportReceivedPlaylists()`
- L763 _public function_ `static TSharedPtrTS<FMetricEvent> ReportTracksChanged()`
- L769 _public function_ `static TSharedPtrTS<FMetricEvent> ReportBufferingStart(Metrics::EBufferingReason BufferingReason)`
- L776 _public function_ `static TSharedPtrTS<FMetricEvent> ReportBufferingEnd(Metrics::EBufferingReason BufferingReason)`
- L783 _public function_ `static TSharedPtrTS<FMetricEvent> ReportBandwidth(int64 EffectiveBps, int64 ThroughputBps, double LatencyInSeconds)`
- L792 _public function_ `static TSharedPtrTS<FMetricEvent> ReportBufferUtilization(const Metrics::FBufferStats& BufferStats)`
- L799 _public function_ `static TSharedPtrTS<FMetricEvent> ReportPlaylistDownload(const Metrics::FPlaylistDownloadStats& PlaylistDownloadStats)`
- L806 _public function_ `static TSharedPtrTS<FMetricEvent> ReportSegmentDownload(const Metrics::FSegmentDownloadStats& SegmentDownloadStats)`
- L813 _public function_ `static TSharedPtrTS<FMetricEvent> ReportLicenseKey(const Metrics::FLicenseKeyStats& LicenseKeyStats)`
- L820 _public function_ `static TSharedPtrTS<FMetricEvent> ReportDataAvailabilityChange(const Metrics::FDataAvailabilityChange& DataAvailability)`
- L827 _public function_ `static TSharedPtrTS<FMetricEvent> ReportVideoQualityChange(int32 NewBitrate, int32 PreviousBitrate, bool bIsDrasticDownswitch)`
- L836 _public function_ `static TSharedPtrTS<FMetricEvent> ReportAudioQualityChange(int32 NewBitrate, int32 PreviousBitrate, bool bIsDrasticDownswitch)`
- L845 _public function_ `static TSharedPtrTS<FMetricEvent> ReportCodecFormatChange(const FStreamCodecInformation& NewDecodingFormat)`
- L852 _public function_ `static TSharedPtrTS<FMetricEvent> ReportPrerollStart()`
- L858 _public function_ `static TSharedPtrTS<FMetricEvent> ReportPrerollEnd()`
- L864 _public function_ `static TSharedPtrTS<FMetricEvent> ReportPlaybackStart()`
- L870 _public function_ `static TSharedPtrTS<FMetricEvent> ReportPlaybackPaused()`
- L876 _public function_ `static TSharedPtrTS<FMetricEvent> ReportPlaybackResumed()`
- L882 _public function_ `static TSharedPtrTS<FMetricEvent> ReportPlaybackEnded()`
- L888 _public function_ `static TSharedPtrTS<FMetricEvent> ReportJumpInPlayPosition(const FTimeValue& ToNewTime, const FTimeValue& FromTime, Metrics::ETimeJumpReason TimejumpReason)`
- L897 _public function_ `static TSharedPtrTS<FMetricEvent> ReportPlaybackStopped()`
- L903 _public function_ `static TSharedPtrTS<FMetricEvent> ReportSeekCompleted(bool bWasAlreadyThere=false)`
- L910 _public function_ `static TSharedPtrTS<FMetricEvent> ReportMediaMetadataChanged(const TSharedPtrTS<FMetadataParser>& InNextMetadata)`
- L917 _public function_ `static TSharedPtrTS<FMetricEvent> ReportError(const FErrorDetail& ErrorDetail)`
- L924 _public function_ `static TSharedPtrTS<FMetricEvent> ReportLogMessage(IInfoLog::ELevel inLogLevel, const FString& LogMessage, int64 PlayerWallclockMilliseconds)`
- L933 _public function_ `static TSharedPtrTS<FMetricEvent> ReportVideoFrameStats(uint64 InNumTotalFrames, uint64 InNumTotalDroppedFrames, uint64 InNumNewDroppedFrames, const FDroppedFrameStats& InDropStats)`

#### enum `Electra::FMetricEvent::EType`  
`enum class EType`  
_L653-683_
- L655 _public enumerator_ `OpenSource`
- L656 _public enumerator_ `ReceivedMainPlaylist`
- L657 _public enumerator_ `ReceivedPlaylists`
- L658 _public enumerator_ `TracksChanged`
- L659 _public enumerator_ `BufferingStart`
- L660 _public enumerator_ `BufferingEnd`
- L661 _public enumerator_ `Bandwidth`
- L662 _public enumerator_ `BufferUtilization`
- L663 _public enumerator_ `PlaylistDownload`
- L664 _public enumerator_ `SegmentDownload`
- L665 _public enumerator_ `DataAvailabilityChange`
- L666 _public enumerator_ `VideoQualityChange`
- L667 _public enumerator_ `AudioQualityChange`
- L668 _public enumerator_ `CodecFormatChange`
- L669 _public enumerator_ `PrerollStart`
- L670 _public enumerator_ `PrerollEnd`
- L671 _public enumerator_ `PlaybackStart`
- L672 _public enumerator_ `PlaybackPaused`
- L673 _public enumerator_ `PlaybackResumed`
- L674 _public enumerator_ `PlaybackEnded`
- L675 _public enumerator_ `PlaybackJumped`
- L676 _public enumerator_ `PlaybackStopped`
- L677 _public enumerator_ `SeekCompleted`
- L678 _public enumerator_ `MediaMetadataChanged`
- L679 _public enumerator_ `LicenseKey`
- L680 _public enumerator_ `Errored`
- L681 _public enumerator_ `LogMessage`
- L682 _public enumerator_ `VideoFrameStats`

#### struct `Electra::FMetricEvent::FParam`  
`struct FParam`  
_L685-736_
- L720 _public member_ `FString URL;`
- L721 _public member_ `Metrics::EBufferingReason BufferingReason;`
- L722 _public member_ `Metrics::FBufferStats BufferStats;`
- L723 _public member_ `Metrics::FPlaylistDownloadStats PlaylistStats;`
- L724 _public member_ `Metrics::FSegmentDownloadStats SegmentStats;`
- L725 _public member_ `Metrics::FLicenseKeyStats LicenseKeyStats;`
- L726 _public member_ `Metrics::FDataAvailabilityChange DataAvailability;`
- L727 _public member_ `Metrics::FFrameStats FrameStats;`
- L728 _public member_ `FBandwidth Bandwidth;`
- L729 _public member_ `FQualityChange QualityChange;`
- L730 _public member_ `FStreamCodecInformation CodecFormatChange;`
- L731 _public member_ `FTimeJumped TimeJump;`
- L732 _public member_ `FSeekComplete SeekComplete;`
- L733 _public member_ `FMediaMedataDataChanged MediaMetadataChange;`
- L734 _public member_ `FErrorDetail ErrorDetail;`
- L735 _public member_ `FLogMessage LogMessage;`

#### struct `Electra::FMetricEvent::FParam::FBandwidth`  
`struct FBandwidth`  
_L687-692_
- L689 _public member_ `int64 EffectiveBps;`
- L690 _public member_ `int64 ThroughputBps;`
- L691 _public member_ `double Latency;`

#### struct `Electra::FMetricEvent::FParam::FQualityChange`  
`struct FQualityChange`  
_L693-698_
- L695 _public member_ `int32 NewBitrate;`
- L696 _public member_ `int32 PrevBitrate;`
- L697 _public member_ `bool bIsDrastic;`

#### struct `Electra::FMetricEvent::FParam::FLogMessage`  
`struct FLogMessage`  
_L699-704_
- L701 _public member_ `FString Message;`
- L702 _public member_ `IInfoLog::ELevel Level;`
- L703 _public member_ `int64 AtMillis;`

#### struct `Electra::FMetricEvent::FParam::FTimeJumped`  
`struct FTimeJumped`  
_L705-711_
- L707 _public member_ `FTimeValue ToNewTime;`
- L708 _public member_ `FTimeValue FromTime;`
- L709 _public member_ `Metrics::ETimeJumpReason Reason;`

#### struct `Electra::FMetricEvent::FParam::FSeekComplete`  
`struct FSeekComplete`  
_L712-715_
- L714 _public member_ `bool bWasAlreadyThere;`

#### struct `Electra::FMetricEvent::FParam::FMediaMedataDataChanged`  
`struct FMediaMedataDataChanged`  
_L716-719_
- L718 _public member_ `TSharedPtrTS<FMetadataParser> NewMetadata;`

#### class `Electra::FAdaptiveStreamingPlayerWorkerThread`  
`class FAdaptiveStreamingPlayerWorkerThread`  
_L953-1001_
- L956 _public prototype_ `static TSharedPtrTS<FAdaptiveStreamingPlayerWorkerThread> Create(bool bUseSharedWorkerThread);`
- L958 _public function_ `void AddPlayerInstance(FAdaptiveStreamingPlayer* Instance)`
- L963 _public function_ `void RemovePlayerInstance(FAdaptiveStreamingPlayer* Instance)`
- L974 _public function_ `void TriggerWork()`
- L979 _public prototype_ `virtual ~FAdaptiveStreamingPlayerWorkerThread();`
- L981 _private prototype_ `void StartWorkerThread();`
- L982 _private prototype_ `void StopWorkerThread();`
- L983 _private prototype_ `void WorkerThreadFN();`
- L991 _private member_ `FMediaThread WorkerThread;`
- L992 _private member_ `TQueue<FAdaptiveStreamingPlayer*, EQueueMode::Mpsc> InstancesToAdd;`
- L993 _private member_ `TQueue<FInstanceToRemove, EQueueMode::Mpsc> InstancesToRemove;`
- L994 _private member_ `TArray<FAdaptiveStreamingPlayer*> PlayerInstances;`
- L995 _private member_ `FMediaEvent HaveWorkSignal;`
- L996 _private member_ `bool bTerminate = false;`
- L997 _private member_ `bool bIsDedicatedWorker = false;`
- L999 _private member_ `static TWeakPtrTS<FAdaptiveStreamingPlayerWorkerThread> SingletonSelf;`
- L1000 _private member_ `static FCriticalSection SingletonLock;`

#### struct `Electra::FAdaptiveStreamingPlayerWorkerThread::FInstanceToRemove`  
`struct FInstanceToRemove`  
_L985-989_
- L987 _public member_ `FAdaptiveStreamingPlayer* Player = nullptr;`
- L988 _public member_ `FMediaEvent* DoneSignal = nullptr;`

#### class `Electra::FAdaptiveStreamingPlayerEventHandler`  
`class FAdaptiveStreamingPlayerEventHandler`  
_L1004-1021_
- L1007 _public prototype_ `static TSharedPtrTS<FAdaptiveStreamingPlayerEventHandler> Create(bool bUseSharedWorkerThread);`
- L1009 _public prototype_ `void DispatchEvent(TSharedPtrTS<FMetricEvent> InEvent);`
- L1011 _public prototype_ `virtual ~FAdaptiveStreamingPlayerEventHandler();`
- L1013 _private prototype_ `void StartWorkerThread();`
- L1014 _private prototype_ `void StopWorkerThread();`
- L1015 _private prototype_ `void WorkerThreadFN();`
- L1017 _private member_ `FMediaThread WorkerThread;`
- L1018 _private member_ `TMediaMessageQueueDynamicNoTimeout<TSharedPtrTS<FMetricEvent>> EventQueue;`
- L1019 _private member_ `static TWeakPtrTS<FAdaptiveStreamingPlayerEventHandler> SingletonSelf;`
- L1020 _private member_ `static FCriticalSection SingletonLock;`

#### class `Electra::FAdaptiveStreamingPlayerPlaylistPropertyHandler`  
`class FAdaptiveStreamingPlayerPlaylistPropertyHandler`  
_L1025-1093_
- L1028 _public prototype_ `FAdaptiveStreamingPlayerPlaylistPropertyHandler() = default;`
- L1029 _public prototype_ `~FAdaptiveStreamingPlayerPlaylistPropertyHandler() = default;`
- L1030 _public function_ `bool ConfigureFromJSON(const FString& InJSONConfig)`
- L1039 _public function_ `bool WantProperty(FName& OutAsName, const FString& InProtocol, const FString& InProperty)`
- L1092 _private member_ `TSharedPtr<FJsonObject> Config;`

#### class `Electra::FAdaptiveStreamingPlayer`  
`class FAdaptiveStreamingPlayer : public IAdaptiveStreamingPlayer , public IPlayerSessionServices , public IStreamReader::StreamReaderEventListener , public IAccessUnitMemoryProvider , public IPlayerStreamFilter , public TSharedFromThis<FAdaptiveStreamingPlayer, ESPMode::ThreadSafe> , public IPlayerABRLiveControl`  
_L1096-2439_
- inherits: `IAdaptiveStreamingPlayer,IPlayerSessionServices,IStreamReader::StreamReaderEventListener,IAccessUnitMemoryProvider,IPlayerStreamFilter,TSharedFromThis<FAdaptiveStreamingPlayer,ESPMode::ThreadSafe>,IPlayerABRLiveControl`
- L1118 _public prototype_ `FAdaptiveStreamingPlayer(const IAdaptiveStreamingPlayer::FCreateParam& InCreateParameters);`
- L1119 _public prototype_ `virtual ~FAdaptiveStreamingPlayer();`
- L1121 _public prototype_ `void SetStaticResourceProviderCallback(const TSharedPtr<IAdaptiveStreamingPlayerResourceProvider, ESPMode::ThreadSafe>& InStaticResourceProvider) override;`
- L1123 _public prototype_ `void AddMetricsReceiver(IAdaptiveStreamingPlayerMetrics* InMetricsReceiver) override;`
- L1124 _public prototype_ `void RemoveMetricsReceiver(IAdaptiveStreamingPlayerMetrics* InMetricsReceiver) override;`
- L1126 _public prototype_ `void HandleOnce();`
- L1129 _public function_ `void LockMetricsReceivers()` — Metrics receiver accessor for event dispatcher thread.
- L1133 _public function_ `void UnlockMetricsReceivers()`
- L1137 _public function_ `const TArray<IAdaptiveStreamingPlayerMetrics*, TInlineAllocator<4>>& GetMetricsReceivers()`
- L1141 _public prototype_ `void FireSyncEvent(TSharedPtrTS<FMetricEvent> Event);`
- L1144 _public prototype_ `void AddAEMSReceiver(TWeakPtrTS<IAdaptiveStreamingPlayerAEMSReceiver> InReceiver, FString InForSchemeIdUri, FString InForValue, IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode InDispatchMode) override;`
- L1145 _public prototype_ `void RemoveAEMSReceiver(TWeakPtrTS<IAdaptiveStreamingPlayerAEMSReceiver> InReceiver, FString InForSchemeIdUri, FString InForValue, IAdaptiveStreamingPlayerAEMSReceiver::EDispatchMode InDispatchMode) override;`
- L1147 _public prototype_ `void Initialize(const FParamDict& Options) override;`
- L1148 _public prototype_ `void ModifyOptions(const FParamDict& InOptionsToSetOrChange, const FParamDict& InOptionsToClear) override;`
- L1149 _public prototype_ `FVariantValue GetMediaInfo(FName InKey) const override;`
- L1151 _public prototype_ `void SetInitialStreamAttributes(EStreamType StreamType, FStreamSelectionAttributes InitialSelection) override;`
- L1152 _public prototype_ `void EnableFrameAccurateSeeking(bool bEnabled) override;`
- L1153 _public prototype_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> GetMediaSamples() override;`
- L1154 _public prototype_ `void LoadManifest(const FString& manifestURL) override;`
- L1156 _public prototype_ `void SeekTo(const FSeekParam& NewPosition) override;`
- L1157 _public prototype_ `void Pause() override;`
- L1158 _public prototype_ `void Resume() override;`
- L1159 _public prototype_ `void Stop() override;`
- L1160 _public prototype_ `void SetPlaybackRange(const FPlaybackRange& InPlaybackRange) override;`
- L1161 _public prototype_ `void GetPlaybackRange(FPlaybackRange& OutPlaybackRange) override;`
- L1162 _public prototype_ `void SetLooping(const FLoopParam& InLoopParams) override;`
- L1163 _public prototype_ `TRangeSet<double> GetSupportedRates(EPlaybackRateType InForPlayRateType) override;`
- L1164 _public prototype_ `void SetPlayRate(double InDesiredPlayRate, const FTrickplayParams& InParameters) override;`
- L1165 _public prototype_ `double GetPlayRate() const override;`
- L1167 _public prototype_ `FErrorDetail GetError() const override;`
- L1169 _public prototype_ `bool HaveMetadata() const override;`
- L1170 _public prototype_ `FTimeValue GetDuration() const override;`
- L1171 _public prototype_ `FTimeValue GetPlayPosition() const override;`
- L1172 _public prototype_ `void GetTimelineRange(FTimeRange& OutRange) const override;`
- L1173 _public prototype_ `void GetSeekableRange(FTimeRange& OutRange) const override;`
- L1174 _public prototype_ `bool HasEnded() const override;`
- L1175 _public prototype_ `bool IsSeeking() const override;`
- L1176 _public prototype_ `bool IsBuffering() const override;`
- L1177 _public prototype_ `bool IsPlaying() const override;`
- L1178 _public prototype_ `bool IsPaused() const override;`
- L1180 _public prototype_ `void GetLoopState(FLoopState& OutLoopState) const override;`
- L1181 _public prototype_ `void GetTrackMetadata(TArray<FTrackMetadata>& OutTrackMetadata, EStreamType StreamType) const override;`
- L1183 _public prototype_ `void GetSelectedTrackAttributes(FStreamSelectionAttributes& OutAttributes, EStreamType StreamType) const override;` — void GetSelectedTrackMetadata(TOptional<FTrackMetadata>& OutSelectedTrackMetadata, EStreamType StreamType) const override;
- L1184 _public prototype_ `void GetReplayEventState(FEventReplayState& OutReplayEventState) const override;`
- L1186 _public prototype_ `void SetBitrateCeiling(int32 highestSelectableBitrate) override;`
- L1187 _public prototype_ `void SetMaxResolution(int32 MaxWidth, int32 MaxHeight) override;`
- L1190 _public prototype_ `void SelectTrackByAttributes(EStreamType StreamType, const FStreamSelectionAttributes& Attributes) override;` — void SelectTrackByMetadata(EStreamType StreamType, const FTrackMetadata& StreamMetadata) override;
- L1191 _public prototype_ `void DeselectTrack(EStreamType StreamType) override;`
- L1192 _public prototype_ `bool IsTrackDeselected(EStreamType StreamType) override;`
- L1194 _public prototype_ `void QueryStreamBufferInfo(FStreamBufferInfo& OutStreamBufferInfo, EStreamType InStreamType) override;`
- L1196 _public prototype_ `void SuspendOrResumeDecoders(bool bSuspend, const FParamDict& InOptions) override;`
- L1198 _public prototype_ `void DebugPrint(void* pPlayer, void (*debugDrawPrintf)(void* pPlayer, const char *pFmt, ...));`
- L1199 _public prototype_ `static void DebugHandle(void* pPlayer, void (*debugDrawPrintf)(void* pPlayer, const char *pFmt, ...));`
- L1203 _private prototype_ `void PostError(const FErrorDetail& Error) override;` — Methods from IPlayerSessionServices
- L1204 _private prototype_ `void PostLog(Facility::EFacility FromFacility, IInfoLog::ELevel LogLevel, const FString& Message) override;`
- L1205 _private prototype_ `void SendMessageToPlayer(TSharedPtrTS<IPlayerMessage> PlayerMessage) override;`
- L1206 _private prototype_ `void GetExternalGuid(FGuid& OutExternalGuid) override;`
- L1207 _private prototype_ `ISynchronizedUTCTime* GetSynchronizedUTCTime() override;`
- L1208 _private prototype_ `TSharedPtr<IAdaptiveStreamingPlayerResourceProvider, ESPMode::ThreadSafe> GetStaticResourceProvider() override;`
- L1209 _private prototype_ `TSharedPtrTS<IElectraHttpManager> GetHTTPManager() override;`
- L1210 _private prototype_ `TSharedPtrTS<IAdaptiveStreamSelector> GetStreamSelector() override;`
- L1211 _private prototype_ `IPlayerABRLiveControl* GetPlayerARBControl() override;`
- L1212 _private prototype_ `IPlayerStreamFilter* GetStreamFilter() override;`
- L1213 _private prototype_ `const FCodecSelectionPriorities& GetCodecSelectionPriorities(EStreamType ForStream) override;`
- L1214 _private prototype_ `TSharedPtrTS<IPlaylistReader> GetManifestReader() override;`
- L1215 _private prototype_ `TSharedPtrTS<FContentSteeringHandler> GetContentSteeringHandler() override;`
- L1216 _private prototype_ `TSharedPtrTS<FCMCDHandler> GetCMCDHandler() override;`
- L1217 _private prototype_ `TSharedPtrTS<IPlayerEntityCache> GetEntityCache() override;`
- L1218 _private prototype_ `TSharedPtrTS<IHTTPResponseCache> GetHTTPResponseCache() override;`
- L1219 _private prototype_ `IAdaptiveStreamingPlayerAEMSHandler* GetAEMSEventHandler() override;`
- L1220 _private prototype_ `FParamDictTS& GetMediaInfoDictionary() override;`
- L1221 _private prototype_ `FParamDictTS& GetMutableOptions() override;`
- L1222 _private prototype_ `bool HaveOptionValue(const FName& InOption) override;`
- L1223 _private prototype_ `const FVariantValue GetOptionValue(const FName& InOption) override;`
- L1224 _private prototype_ `TSharedPtrTS<FDRMManager> GetDRMManager() override;`
- L1225 _private prototype_ `void SetPlaybackEnd(const FTimeValue& InEndAtTime, IPlayerSessionServices::EPlayEndReason InEndingReason, TSharedPtrTS<IPlayerSessionServices::IPlayEndReason> InCustomManifestObject) override;`
- L1226 _private prototype_ `ECustomPropertyResult ValidateMainPlaylistCustomProperty(const FString& InProtocol, const FString& InPlaylistURL, const TArray<FElectraHTTPStreamHeader>& InPlaylistFetchResponseHeaders, const FPlaylistProperty& InProperty) override;`
- L1229 _private prototype_ `bool CanDecodeStream(const FStreamCodecInformation& InStreamCodecInfo) const override;` — Methods from IPlayerStreamFilter
- L1230 _private prototype_ `bool CanDecodeSubtitle(const FString& MimeType, const FString& Codec) const override;`
- L1234 _private prototype_ `FTimeValue ABRGetPlayPosition() const override;` — Methods from IPlayerABRLiveControl
- L1235 _private prototype_ `FTimeRange ABRGetTimeline() const override;`
- L1236 _private prototype_ `FTimeValue ABRGetWallclockTime() const override;`
- L1237 _private prototype_ `bool ABRIsLive() const override;`
- L1238 _private prototype_ `bool ABRShouldPlayOnLiveEdge() const override;`
- L1239 _private prototype_ `TSharedPtrTS<const FLowLatencyDescriptor> ABRGetLowLatencyDescriptor() const override;`
- L1240 _private prototype_ `FTimeValue ABRGetDesiredLiveEdgeLatency() const override;`
- L1241 _private prototype_ `FTimeValue ABRGetLatency() const override;`
- L1242 _private prototype_ `FTimeValue ABRGetPlaySpeed() const override;`
- L1243 _private prototype_ `void ABRGetStreamBufferStats(IPlayerABRLiveControl::FABRBufferStats& OutBufferStats, EStreamType ForStream) override;`
- L1244 _private prototype_ `FTimeRange ABRGetSupportedRenderRateScale() override;`
- L1245 _private prototype_ `void ABRSetRenderRateScale(double InRenderRateScale) override;`
- L1246 _private prototype_ `double ABRGetRenderRateScale() const override;`
- L1247 _private prototype_ `void ABRTriggerClockSync(IPlayerABRLiveControl::EClockSyncType InClockSyncType) override;`
- L1248 _private prototype_ `void ABRTriggerPlaylistRefresh() override;`
- L1264 _private function_ `static const char* GetPlayerStateName(EPlayerState s)`
- L1287 _private function_ `static const char* GetDecoderStateName(EDecoderState s)`
- L1303 _private function_ `static const char* GetPipelineStateName(EPipelineState s)`
- L1319 _private function_ `static const char* GetStreamStateName(EStreamState s)`
- L2152 _private prototype_ `void InternalLoadManifest(const FString& URL, const FString& MimeType);`
- L2153 _private prototype_ `void InternalCancelLoadManifest();`
- L2154 _private prototype_ `void InternalCloseManifestReader();`
- L2155 _private prototype_ `bool SelectManifest();`
- L2156 _private prototype_ `void UpdateManifest();`
- L2157 _private prototype_ `void OnManifestGetMimeTypeComplete(TSharedPtrTS<FHTTPResourceRequest> InRequest);`
- L2159 _private prototype_ `void VideoDecoderInputNeeded(const IAccessUnitBufferListener::FBufferStats& currentInputBufferStats);`
- L2160 _private prototype_ `void VideoDecoderOutputReady(const IDecoderOutputBufferListener::FDecodeReadyStats& currentReadyStats);`
- L2162 _private prototype_ `void AudioDecoderInputNeeded(const IAccessUnitBufferListener::FBufferStats& currentInputBufferStats);`
- L2163 _private prototype_ `void AudioDecoderOutputReady(const IDecoderOutputBufferListener::FDecodeReadyStats& currentReadyStats);`
- L2165 _private prototype_ `void StartWorkerThread();`
- L2166 _private prototype_ `void StopWorkerThread();`
- L2168 _private prototype_ `int32 CreateRenderers();`
- L2169 _private prototype_ `void DestroyRenderers();`
- L2171 _private prototype_ `int32 CreateDecoder(EStreamType type);`
- L2172 _private prototype_ `void DestroyDecoders();`
- L2173 _private prototype_ `bool GetHighestVideoProfileResolution(FStreamCodecInformation& OutStreamInfo, TSharedPtrTS<const FBufferSourceInfo> InBufferSource, const FTimeValue& AtTime, const FStreamCodecInformation& InForCodec);`
- L2174 _private prototype_ `void UpdateStreamResolutionLimit();`
- L2175 _private prototype_ `void AddUpcomingPeriod(TSharedPtrTS<IManifest::IPlayPeriod> InUpcomingPeriod);`
- L2176 _private prototype_ `void RequestNewPeriodStreams(EStreamType InType, FPendingSegmentRequest& InOutCurrentRequest);`
- L2177 _private prototype_ `void UpdatePeriodStreamBufferSourceInfo(TSharedPtrTS<IManifest::IPlayPeriod> InForPeriod, EStreamType InStreamType, TSharedPtrTS<FBufferSourceInfo> InBufferSourceInfo);`
- L2178 _private prototype_ `TSharedPtrTS<FBufferSourceInfo> GetStreamBufferInfoAtTime(bool& bOutHavePeriods, bool& bOutFoundTime, EStreamType InStreamType, const FTimeValue& InAtTime) const;`
- L2182 _private prototype_ `void* AUAllocate(IAccessUnitMemoryProvider::EDataType type, SIZE_T size, SIZE_T alignment) override;` — AU memory / generic stream reader memory
- L2183 _private prototype_ `void AUDeallocate(IAccessUnitMemoryProvider::EDataType type, void *pAddr) override;`
- L2186 _private prototype_ `void OnFragmentOpen(TSharedPtrTS<IStreamSegment> pRequest) override;` — Stream reader events
- L2187 _private prototype_ `bool OnFragmentAccessUnitReceived(FAccessUnit* pAccessUnit) override;`
- L2188 _private prototype_ `void OnFragmentReachedEOS(EStreamType InStreamType, TSharedPtr<const FBufferSourceInfo, ESPMode::ThreadSafe> InStreamSourceInfo) override;`
- L2189 _private prototype_ `void OnFragmentClose(TSharedPtrTS<IStreamSegment> pRequest) override;`
- L2191 _private prototype_ `void Deprecate_InternalInitializeDecoderLimits();`
- L2192 _private prototype_ `bool Deprecate_InternalStreamAllowedAsPerLimits(const FStreamCodecInformation& InStreamCodecInfo) const;`
- L2194 _private prototype_ `void InternalInitialize();`
- L2195 _private prototype_ `void InternalHandleOnce();`
- L2196 _private prototype_ `bool InternalHandleThreadMessages();`
- L2197 _private prototype_ `void InternalHandleManifestReader();`
- L2198 _private prototype_ `void InternalHandlePendingStartRequest(const FTimeValue& CurrentTime);`
- L2199 _private prototype_ `void InternalHandlePendingFirstSegmentRequest(const FTimeValue& CurrentTime);`
- L2200 _private prototype_ `void InternalHandleCompletedSegmentRequests(const FTimeValue& CurrentTime);`
- L2201 _private prototype_ `void InternalHandleSegmentTrackChanges(const FTimeValue& CurrentTime);`
- L2202 _private prototype_ `void InternalStartoverAtCurrentPosition();`
- L2203 _private prototype_ `void InternalStartoverAtLiveEdge();`
- L2205 _private prototype_ `void UpdateDiagnostics();`
- L2206 _private prototype_ `void UpdateFrameStats(bool bFinal);`
- L2207 _private prototype_ `void HandleNewBufferedData();`
- L2208 _private prototype_ `void HandleNewOutputData();`
- L2209 _private prototype_ `void HandleSessionMessage(TSharedPtrTS<IPlayerMessage> SessionMessage);`
- L2210 _private prototype_ `void HandlePlayStateChanges();`
- L2211 _private prototype_ `void HandleSeeking();`
- L2212 _private prototype_ `void HandlePendingMediaSegmentRequests();`
- L2213 _private prototype_ `void CancelPendingMediaSegmentRequests(EStreamType StreamType);`
- L2214 _private prototype_ `void HandleDeselectedBuffers();`
- L2215 _private prototype_ `void HandleDecoderChanges();`
- L2216 _private prototype_ `void HandleSubtitleDecoder();`
- L2217 _private prototype_ `void HandleMetadataChanges();`
- L2218 _private prototype_ `void HandleAEMSEvents();`
- L2220 _private prototype_ `void CheckForStreamEnd();`
- L2222 _private prototype_ `void CheckForErrors();`
- L2224 _private prototype_ `FTimeValue CalculateCurrentLiveLatency(bool bViaLatencyElement);`
- L2225 _private prototype_ `double GetMinBufferTimeBeforePlayback();`
- L2226 _private prototype_ `bool HaveEnoughBufferedDataToStartPlayback();`
- L2227 _private prototype_ `void PrepareForPrerolling();`
- L2229 _private prototype_ `void SetPlaystartOptions(FPlayStartOptions& OutOptions);`
- L2230 _private prototype_ `void ClampStartRequestTime(FTimeValue& InOutTimeToClamp);`
- L2231 _private prototype_ `FTimeValue ClampTimeToCurrentRange(const FTimeValue& InTime, bool bClampToStart, bool bClampToEnd);`
- L2233 _private function_ `TSharedPtrTS<FMultiTrackAccessUnitBuffer> GetStreamBuffer(EStreamType InStreamType, const TSharedPtrTS<FStreamDataBuffers>& InFromStreamBuffers)`
- L2253 _private function_ `TSharedPtrTS<FMultiTrackAccessUnitBuffer> GetCurrentOutputStreamBuffer(EStreamType InStreamType)`
- L2259 _private function_ `TSharedPtrTS<FMultiTrackAccessUnitBuffer> GetCurrentReceiveStreamBuffer(EStreamType InStreamType)`
- L2265 _private prototype_ `bool IsExpectedToStreamNow(EStreamType InType);`
- L2267 _private prototype_ `bool IsSeamlessBufferSwitchPossible(EStreamType InStreamType, const TSharedPtrTS<FStreamDataBuffers>& InFromStreamBuffers);`
- L2269 _private prototype_ `void GetStreamBufferUtilization(FAccessUnitBufferInfo& OutInfo, EStreamType BufferType);`
- L2270 _private prototype_ `void GetStreamBufferUtilization(FAccessUnitBufferInfo& OutInfo, const FAccessUnit* InForThis);`
- L2272 _private prototype_ `void FeedDecoder(EStreamType Type, IAccessUnitBufferInterface* Decoder, bool bHandleUnderrun);`
- L2273 _private prototype_ `void ClearAllDecoderEODs();`
- L2275 _private prototype_ `void InternalStartAt(const FSeekParam& NewPosition, const FTimeRange* InTimeRange);`
- L2276 _private prototype_ `void InternalPause();`
- L2277 _private prototype_ `void InternalResume();`
- L2278 _private prototype_ `void InternalRebuffer();`
- L2279 _private prototype_ `void InternalStop(bool bHoldCurrentFrame);`
- L2280 _private prototype_ `void InternalClose();`
- L2281 _private prototype_ `void InternalHandlePendingLoopRequest();`
- L2282 _private prototype_ `void InternalSetPlaybackEnded();`
- L2283 _private prototype_ `void InternalDeselectStream(EStreamType StreamType);`
- L2285 _private prototype_ `void DispatchEvent(TSharedPtrTS<FMetricEvent> Event);`
- L2286 _private prototype_ `void DispatchBufferingEvent(bool bBegin, EPlayerState Reason);`
- L2287 _private prototype_ `void DispatchBufferUtilizationEvent(EStreamType BufferType);`
- L2289 _private prototype_ `void UpdateDataAvailabilityState(Metrics::FDataAvailabilityChange& DataAvailabilityState, Metrics::FDataAvailabilityChange::EAvailability NewAvailability);`
- L2291 _private prototype_ `void StartRendering();`
- L2292 _private prototype_ `void StopRendering();`
- L2297 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> CurrentMediaSamples;` — Member variables
- L2298 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> EmptyMediaSamples;`
- L2299 _private member_ `FGuid ExternalPlayerGUID;`
- L2301 _private member_ `TWeakPtr<IAdaptiveStreamingPlayerResourceProvider, ESPMode::ThreadSafe> StaticResourceProvider;`
- L2303 _private member_ `TSharedPtrTS<FAdaptiveStreamingPlayerEventHandler> EventDispatcher;`
- L2304 _private member_ `TSharedPtrTS<FAdaptiveStreamingPlayerWorkerThread> SharedWorkerThread;`
- L2305 _private member_ `FWorkerThreadMessages WorkerThread;`
- L2306 _private member_ `IAdaptiveStreamingPlayer::FCreateParam::EWorkerThreads UseSharedWorkerThreads;`
- L2308 _private member_ `FParamDictTS MediaInfoDictionary;`
- L2309 _private member_ `FParamDictTS PlayerOptions;`
- L2310 _private member_ `FPlaybackState PlaybackState;`
- L2311 _private member_ `ISynchronizedUTCTime* SynchronizedUTCTime;`
- L2312 _private member_ `IAdaptiveStreamingPlayerAEMSHandler* AEMSEventHandler;`
- L2314 _private member_ `TSharedPtrTS<FMediaRenderClock> RenderClock;`
- L2316 _private member_ `TSharedPtrTS<IElectraHttpManager> HttpManager;`
- L2317 _private member_ `TSharedPtrTS<IPlayerEntityCache> EntityCache;`
- L2318 _private member_ `TSharedPtrTS<IHTTPResponseCache> HttpResponseCache;`
- L2320 _private member_ `TSharedPtrTS<FDRMManager> DrmManager;`
- L2322 _private member_ `TMediaQueueDynamic<TSharedPtrTS<FErrorDetail>> ErrorQueue;`
- L2324 _private member_ `FString ManifestURL;`
- L2325 _private member_ `TSharedPtrTS<IManifest> Manifest;`
- L2326 _private member_ `TSharedPtrTS<IPlaylistReader> ManifestReader;`
- L2327 _private member_ `TSharedPtrTS<FHTTPResourceRequest> ManifestMimeTypeRequest;`
- L2328 _private member_ `FAdaptiveStreamingPlayerPlaylistPropertyHandler PlaylistPropertyHandler;`
- L2329 _private member_ `Playlist::FReplayEventParams EventReplayParams;`
- L2332 _private member_ `IStreamReader* StreamReaderHandler;`
- L2333 _private member_ `bool bStreamingHasStarted;`
- L2335 _private member_ `FCriticalSection DataBuffersCriticalSection;`
- L2336 _private member_ `TArray<TSharedPtrTS<FStreamDataBuffers>> NextDataBuffers;`
- L2337 _private member_ `TSharedPtrTS<FStreamDataBuffers> CurrentDataReceiveBuffers;`
- L2338 _private member_ `TSharedPtrTS<FStreamDataBuffers> ActiveDataOutputBuffers;`
- L2339 _private member_ `bool bIsVideoDeselected;`
- L2340 _private member_ `bool bIsAudioDeselected;`
- L2341 _private member_ `bool bIsTextDeselected;`
- L2343 _private member_ `Metrics::FDataAvailabilityChange DataAvailabilityStateVid;`
- L2344 _private member_ `Metrics::FDataAvailabilityChange DataAvailabilityStateAud;`
- L2345 _private member_ `Metrics::FDataAvailabilityChange DataAvailabilityStateTxt;`
- L2347 _private member_ `FStreamSelectionAttributes StreamSelectionAttributesVid;`
- L2348 _private member_ `FStreamSelectionAttributes StreamSelectionAttributesAud;`
- L2349 _private member_ `FStreamSelectionAttributes StreamSelectionAttributesTxt;`
- L2351 _private member_ `FInternalStreamSelectionAttributes SelectedStreamAttributesVid;`
- L2352 _private member_ `FInternalStreamSelectionAttributes SelectedStreamAttributesAud;`
- L2353 _private member_ `FInternalStreamSelectionAttributes SelectedStreamAttributesTxt;`
- L2355 _private member_ `TSharedPtrTS<FStreamSelectionAttributes> PendingTrackSelectionVid;`
- L2356 _private member_ `TSharedPtrTS<FStreamSelectionAttributes> PendingTrackSelectionAud;`
- L2357 _private member_ `TSharedPtrTS<FStreamSelectionAttributes> PendingTrackSelectionTxt;`
- L2359 _private member_ `TArray<FString> ExcludedVideoDecoderPrefixes;`
- L2360 _private member_ `TArray<FString> ExcludedAudioDecoderPrefixes;`
- L2361 _private member_ `TArray<FString> ExcludedSubtitleDecoderPrefixes;`
- L2362 _private member_ `FCodecSelectionPriorities CodecPrioritiesVideo;`
- L2363 _private member_ `FCodecSelectionPriorities CodecPrioritiesAudio;`
- L2364 _private member_ `FCodecSelectionPriorities CodecPrioritiesSubtitles;`
- L2366 _private member_ `EPlayerState CurrentState;`
- L2367 _private member_ `EPipelineState PipelineState;`
- L2368 _private member_ `EDecoderState DecoderState;`
- L2369 _private member_ `EStreamState StreamState;`
- L2371 _private member_ `FPrerollVars PrerollVars;`
- L2372 _private member_ `FPostrollVars PostrollVars;`
- L2373 _private member_ `FSeekVars SeekVars;`
- L2374 _private member_ `EPlayerState LastBufferingState;`
- L2375 _private member_ `double RenderRateScale;`
- L2376 _private member_ `FTimeValue RebufferDetectedAtPlayPos;`
- L2377 _private member_ `ERebufferCause RebufferCause;`
- L2378 _private member_ `bool bIsClosing;`
- L2380 _private member_ `TSharedPtrTS<FContentSteeringHandler> ContentSteeringHandler;`
- L2381 _private member_ `TSharedPtrTS<FCMCDHandler> CMCDHandler;`
- L2383 _private member_ `TSharedPtrTS<IAdaptiveStreamSelector> StreamSelector;`
- L2384 _private member_ `int32 BitrateCeiling;`
- L2385 _private member_ `int32 VideoResolutionLimitWidth;`
- L2386 _private member_ `int32 VideoResolutionLimitHeight;`
- L2388 _private member_ `FStreamBitrateInfo CurrentVideoStreamBitrate;`
- L2389 _private member_ `FStreamBitrateInfo CurrentAudioStreamBitrate;`
- L2391 _private member_ `bool bShouldBePaused;`
- L2392 _private member_ `bool bShouldBePlaying;`
- L2394 _private member_ `FInternalLoopState CurrentLoopState;`
- L2395 _private member_ `FLoopParam CurrentLoopParam;`
- L2396 _private member_ `TQueue<FInternalLoopState> NextLoopStates;`
- L2398 _private member_ `mutable FCriticalSection ActivePeriodCriticalSection;`
- L2399 _private member_ `TArray<FPeriodInformation> ActivePeriods;`
- L2400 _private member_ `TArray<FPeriodInformation> UpcomingPeriods;`
- L2401 _private member_ `FMetadataHandlingState MetadataHandlingState;`
- L2402 _private member_ `FMediaMetadataUpdate MediaMetadataUpdates;`
- L2403 _private member_ `TSharedPtrTS<IManifest::IPlayPeriod> InitialPlayPeriod;`
- L2404 _private member_ `TSharedPtrTS<IManifest::IPlayPeriod> CurrentPlayPeriodVideo;`
- L2405 _private member_ `TSharedPtrTS<IManifest::IPlayPeriod> CurrentPlayPeriodAudio;`
- L2406 _private member_ `TSharedPtrTS<IManifest::IPlayPeriod> CurrentPlayPeriodText;`
- L2407 _private member_ `TSharedPtrTS<FPendingStartRequest> PendingStartRequest;`
- L2408 _private member_ `TSharedPtrTS<IStreamSegment> PendingFirstSegmentRequest;`
- L2409 _private member_ `TUniqueObj<TQueue<FPendingSegmentRequest>> NextPendingSegmentRequests;`
- L2410 _private member_ `TUniqueObj<TQueue<TSharedPtrTS<IStreamSegment>>> ReadyWaitingSegmentRequests;`
- L2411 _private member_ `TMultiMap<EStreamType, TSharedPtrTS<IStreamSegment>> CompletedSegmentRequests;`
- L2412 _private member_ `bool bFirstSegmentRequestIsForLooping;`
- L2414 _private member_ `FPlayerSequenceState CurrentPlaybackSequenceState;`
- L2416 _private member_ `uint32 CurrentPlaybackSequenceID[4];` — 0=video, 1=audio, 2=subtitiles, 3=UNSUPPORTED
- L2417 _private member_ `FTimeRange CurrentSegmentDownloadTimeRange[4];`
- L2419 _private member_ `FVideoOutput VideoOutput;`
- L2420 _private member_ `FAudioOutput AudioOutput;`
- L2421 _private member_ `FVideoDecoder VideoDecoder;`
- L2422 _private member_ `FAudioDecoder AudioDecoder;`
- L2423 _private member_ `FSubtitleDecoder SubtitleDecoder;`
- L2425 _private member_ `FCriticalSection MetricListenerCriticalSection;`
- L2426 _private member_ `TArray<IAdaptiveStreamingPlayerMetrics*, TInlineAllocator<4>> MetricListeners;`
- L2428 _private member_ `mutable FCriticalSection DiagnosticsCriticalSection;`
- L2429 _private member_ `FBufferStats VideoBufferStats;`
- L2430 _private member_ `FBufferStats AudioBufferStats;`
- L2431 _private member_ `FBufferStats TextBufferStats;`
- L2432 _private member_ `FErrorDetail LastErrorDetail;`
- L2434 _private member_ `FDroppedFrameStats DroppedFrameStats;`
- L2436 _private member_ `AdaptiveStreamingPlayerConfig::FConfiguration PlayerConfig;`
- L2438 _private member_ `static FAdaptiveStreamingPlayer* PointerToLatestPlayer;`

#### class `Electra::FAdaptiveStreamingPlayer::TDeleter`  
`class TDeleter`  
_L1105-1116_
- L1108 _public function_ `void operator()(FAdaptiveStreamingPlayer* InInstanceToDelete)`

#### enum `Electra::FAdaptiveStreamingPlayer::EPlayerState`  
`enum class EPlayerState`  
_L1251-1263_
- L1253 _public enumerator_ `eState_Idle`
- L1254 _public enumerator_ `eState_ParsingManifest`
- L1255 _public enumerator_ `eState_PreparingStreams`
- L1256 _public enumerator_ `eState_Ready`
- L1257 _public enumerator_ `eState_Buffering` — Initial buffering at start or after a seek (an expected buffering)
- L1258 _public enumerator_ `eState_Playing` — <
- L1259 _public enumerator_ `eState_Paused` — <
- L1260 _public enumerator_ `eState_Rebuffering` — Rebuffering due to buffer underrun. Temporary state only.
- L1261 _public enumerator_ `eState_Seeking` — Seeking. Temporary state only.
- L1262 _public enumerator_ `eState_Error`

#### enum `Electra::FAdaptiveStreamingPlayer::EDecoderState`  
`enum class EDecoderState`  
_L1282-1286_
- L1284 _public enumerator_ `eDecoder_Paused`
- L1285 _public enumerator_ `eDecoder_Running`

#### enum `Electra::FAdaptiveStreamingPlayer::EPipelineState`  
`enum class EPipelineState`  
_L1297-1302_
- L1299 _public enumerator_ `ePipeline_Stopped`
- L1300 _public enumerator_ `ePipeline_Prerolling`
- L1301 _public enumerator_ `ePipeline_Running`

#### enum `Electra::FAdaptiveStreamingPlayer::EStreamState`  
`enum class EStreamState`  
_L1314-1318_
- L1316 _public enumerator_ `eStream_Running`
- L1317 _public enumerator_ `eStream_ReachedEnd`

#### enum `Electra::FAdaptiveStreamingPlayer::ERebufferCause`  
`enum class ERebufferCause`  
_L1329-1334_
- L1331 _public enumerator_ `None`
- L1332 _public enumerator_ `Underrun`
- L1333 _public enumerator_ `TrackswitchUnderrun`

#### struct `Electra::FAdaptiveStreamingPlayer::FVideoOutput`  
`struct FVideoOutput`  
_L1336-1370_
- L1338 _public function_ `void Close()`
- L1346 _public function_ `void Flush(bool bHoldCurrentFrame)`
- L1353 _public function_ `uint64 GetTotalAddedSamples()`
- L1357 _public function_ `uint64 GetTotalNumDroppedSamples()`
- L1361 _public function_ `uint64 GetNewlyNumDroppedSamples()`
- L1365 _public function_ `uint64 PeekNewlyNumDroppedSamples()`
- L1369 _public member_ `TSharedPtr<FOutputHandlerVideo, ESPMode::ThreadSafe> OutputHandler;`

#### struct `Electra::FAdaptiveStreamingPlayer::FAudioOutput`  
`struct FAudioOutput`  
_L1372-1390_
- L1374 _public function_ `void Close()`
- L1382 _public function_ `void Flush()`
- L1389 _public member_ `TSharedPtr<FOutputHandlerAudio, ESPMode::ThreadSafe> OutputHandler;`

#### struct `Electra::FAdaptiveStreamingPlayer::FVideoDecoder`  
`struct FVideoDecoder : public IAccessUnitBufferListener, public IDecoderOutputBufferListener`  
_L1392-1459_
- inherits: `IAccessUnitBufferListener,IDecoderOutputBufferListener`
- L1394 _public function_ `void Close()`
- L1406 _public function_ `void Flush()`
- L1413 _public function_ `void ClearEOD()`
- L1420 _public function_ `void SuspendOrResume(bool bInSuspend, const FParamDict& InOptions)`
- L1428 _public function_ `void CheckIfNewDecoderMustBeSuspendedImmediately()`
- L1435 _public function_ `virtual void DecoderInputNeeded(const IAccessUnitBufferListener::FBufferStats& currentInputBufferStats)`
- L1443 _public function_ `virtual void DecoderOutputReady(const IDecoderOutputBufferListener::FDecodeReadyStats& currentReadyStats)`
- L1451 _public member_ `FStreamCodecInformation CurrentCodecInfo;`
- L1452 _public member_ `TSharedPtrTS<FAccessUnit::CodecData> LastSentAUCodecData;`
- L1453 _public member_ `TSharedPtrTS<const FBufferSourceInfo> LastBufferSourceInfo;`
- L1454 _public member_ `FAdaptiveStreamingPlayer* Parent = nullptr;`
- L1455 _public member_ `IVideoDecoder* Decoder = nullptr;`
- L1456 _public member_ `bool bDrainingForCodecChange = false;`
- L1457 _public member_ `bool bDrainingForCodecChangeDone = false;`
- L1458 _public member_ `bool bSuspended = false;`

#### struct `Electra::FAdaptiveStreamingPlayer::FAudioDecoder`  
`struct FAudioDecoder : public IAccessUnitBufferListener, public IDecoderOutputBufferListener`  
_L1461-1524_
- inherits: `IAccessUnitBufferListener,IDecoderOutputBufferListener`
- L1463 _public function_ `void Close()`
- L1474 _public function_ `void Flush()`
- L1481 _public function_ `void ClearEOD()`
- L1488 _public function_ `void SuspendOrResume(bool bInSuspend, const FParamDict& InOptions)`
- L1496 _public function_ `void CheckIfNewDecoderMustBeSuspendedImmediately()`
- L1503 _public function_ `virtual void DecoderInputNeeded(const IAccessUnitBufferListener::FBufferStats& currentInputBufferStats)`
- L1511 _public function_ `virtual void DecoderOutputReady(const IDecoderOutputBufferListener::FDecodeReadyStats& currentReadyStats)`
- L1519 _public member_ `FStreamCodecInformation CurrentCodecInfo;`
- L1520 _public member_ `TSharedPtrTS<FAccessUnit::CodecData> LastSentAUCodecData;`
- L1521 _public member_ `FAdaptiveStreamingPlayer* Parent = nullptr;`
- L1522 _public member_ `IAudioDecoder* Decoder = nullptr;`
- L1523 _public member_ `bool bSuspended = false;`

#### struct `Electra::FAdaptiveStreamingPlayer::FSubtitleDecoder`  
`struct FSubtitleDecoder`  
_L1526-1584_
- L1528 _public function_ `void Close()`
- L1540 _public function_ `void Flush()`
- L1547 _public function_ `void ClearEOD()`
- L1555 _public function_ `void Start()`
- L1567 _public function_ `void Stop()`
- L1579 _public member_ `FStreamCodecInformation CurrentCodecInfo;`
- L1580 _public member_ `TSharedPtrTS<FAccessUnit::CodecData> LastSentAUCodecData;`
- L1581 _public member_ `ISubtitleDecoder* Decoder = nullptr;`
- L1582 _public member_ `bool bIsRunning = false;`
- L1583 _public member_ `bool bRequireCodecChange = false;`

#### class `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages`  
`class FWorkerThreadMessages`  
_L1586-1831_
- L1589 _public function_ `~FWorkerThreadMessages()`
- L1593 _public function_ `void SetSharedWorkerThread(TSharedPtrTS<FAdaptiveStreamingPlayerWorkerThread> InSharedWorkerThread)`
- L1688 _public function_ `void Enqueue(FMessage::EType type, const TSharedPtrTS<IStreamSegment>& InRequest)`
- L1696 _public function_ `void Enqueue(FMessage::EType type, FMediaEvent* InEventSignal)`
- L1705 _public function_ `void EnqueueBufferUnderrun()`
- L1711 _public function_ `void SendInitializeMessage()`
- L1717 _public function_ `void SendOptionChangeMessage(const FParamDict& InOptionsToSetOrChange, const FParamDict& InOptionsToClear)`
- L1725 _public function_ `void SendLoadManifestMessage(const FString& InURL, const FString& InMimeType)`
- L1733 _public function_ `void SendPauseMessage()`
- L1739 _public function_ `void SendResumeMessage()`
- L1745 _public function_ `void SendCloseMessage(FMediaEvent* InEventSignal)`
- L1754 _public function_ `void SendBitrateMessage(EStreamType , int32 InValue, int32 )`
- L1762 _public function_ `void SendPlayerSessionMessage(const TSharedPtrTS<IPlayerMessage>& InMessage)`
- L1770 _public function_ `void SendResolutionMessage(int32 InWidth, int32 InHeight)`
- L1778 _public function_ `void SendTrackSelectByMetadataMessage(EStreamType InStreamType, const FTrackMetadata& InTrackMetadata)`
- L1786 _public function_ `void SendTrackSelectByAttributeMessage(EStreamType InStreamType, const FStreamSelectionAttributes& InTrackAttributes)`
- L1795 _public function_ `void SendTrackDeselectMessage(EStreamType InStreamType)`
- L1803 _public function_ `void SendPlaybackEndMessage(const FTimeValue& InEndAtTime, IPlayerSessionServices::EPlayEndReason InEndingReason, const TSharedPtrTS<IPlayerSessionServices::IPlayEndReason>& InCustomManifestObject)`
- L1812 _public function_ `void TriggerSharedWorkerThread(FMessage Mesg)`
- L1821 _public function_ `void TriggerSharedWorkerThread()`
- L1829 _public member_ `TSharedPtrTS<FAdaptiveStreamingPlayerWorkerThread> SharedWorkerThread;`
- L1830 _public member_ `TQueue<FMessage, EQueueMode::Mpsc> WorkMessages;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage`  
`struct FMessage`  
_L1598-1686_
- L1684 _public member_ `EType Type;`
- L1685 _public member_ `TVariant<FLoadManifest, FLoadBlob, FOptionChange, FStreamReader, FEvent, FLoop, FBitrate, FSession, FResolution, FInitialStreamSelect, FMetadataTrackSelection, FEndPlaybackAt> Data;`

#### enum `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::EType`  
`enum class EType`  
_L1600-1622_
- L1603 _public enumerator_ `Initialize` — Commands
- L1604 _public enumerator_ `ChangeOptions`
- L1605 _public enumerator_ `LoadManifest`
- L1606 _public enumerator_ `Pause`
- L1607 _public enumerator_ `Resume`
- L1608 _public enumerator_ `Close`
- L1609 _public enumerator_ `ChangeBitrate`
- L1610 _public enumerator_ `LimitResolution`
- L1611 _public enumerator_ `SelectTrackByMetadata`
- L1612 _public enumerator_ `SelectTrackByAttributes`
- L1613 _public enumerator_ `DeselectTrack`
- L1614 _public enumerator_ `EndPlaybackAt`
- L1616 _public enumerator_ `PlayerSession` — Player session message
- L1618 _public enumerator_ `FragmentOpen` — Fragment reader messages
- L1619 _public enumerator_ `FragmentClose`
- L1621 _public enumerator_ `BufferUnderrun` — Decoder buffer messages

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FLoadManifest`  
`struct FLoadManifest`  
_L1624-1628_
- L1626 _public member_ `FString URL;`
- L1627 _public member_ `FString MimeType;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FLoadBlob`  
`struct FLoadBlob`  
_L1629-1632_
- L1631 _public member_ `TSharedPtrTS<FHTTPResourceRequest> BlobLoadRequest;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FOptionChange`  
`struct FOptionChange`  
_L1633-1637_
- L1635 _public member_ `FParamDict OptionsToSetOrChange;`
- L1636 _public member_ `FParamDict OptionsToClear;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FStreamReader`  
`struct FStreamReader`  
_L1638-1643_
- L1640 _public member_ `TSharedPtrTS<IStreamSegment> Request;`
- L1641 _public member_ `EStreamType AUType = EStreamType::Unsupported;`
- L1642 _public member_ `SIZE_T AUSize = 0;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FEvent`  
`struct FEvent`  
_L1644-1647_
- L1646 _public member_ `FMediaEvent* Event = nullptr;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FLoop`  
`struct FLoop`  
_L1648-1652_
- L1650 _public member_ `FLoopParam Loop;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FBitrate`  
`struct FBitrate`  
_L1653-1656_
- L1655 _public member_ `int32 Value = 0;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FSession`  
`struct FSession`  
_L1657-1660_
- L1659 _public member_ `TSharedPtrTS<IPlayerMessage> PlayerMessage;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FResolution`  
`struct FResolution`  
_L1661-1665_
- L1663 _public member_ `int32 Width = 0;`
- L1664 _public member_ `int32 Height = 0;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FInitialStreamSelect`  
`struct FInitialStreamSelect`  
_L1666-1670_
- L1668 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L1669 _public member_ `FStreamSelectionAttributes InitialSelection;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FMetadataTrackSelection`  
`struct FMetadataTrackSelection`  
_L1671-1676_
- L1673 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L1674 _public member_ `FTrackMetadata TrackMetadata;`
- L1675 _public member_ `FStreamSelectionAttributes TrackAttributes;`

#### struct `Electra::FAdaptiveStreamingPlayer::FWorkerThreadMessages::FMessage::FEndPlaybackAt`  
`struct FEndPlaybackAt`  
_L1677-1682_
- L1679 _public member_ `FTimeValue EndAtTime;`
- L1680 _public member_ `IPlayerSessionServices::EPlayEndReason EndingReason = IPlayerSessionServices::EPlayEndReason::EndAll;`
- L1681 _public member_ `TSharedPtrTS<IPlayerSessionServices::IPlayEndReason> CustomManifestObject;`

#### struct `Electra::FAdaptiveStreamingPlayer::FPendingStartRequest`  
`struct FPendingStartRequest`  
_L1833-1846_
- L1841 _public member_ `FPlayStartPosition StartAt;`
- L1842 _public member_ `TOptional<int32> StartingBitrate;`
- L1843 _public member_ `IManifest::ESearchType SearchType = IManifest::ESearchType::Closest;`
- L1844 _public member_ `FTimeValue RetryAtTime;`
- L1845 _public member_ `EStartType StartType = EStartType::PlayStart;`

#### enum `Electra::FAdaptiveStreamingPlayer::FPendingStartRequest::EStartType`  
`enum class EStartType`  
_L1835-1840_
- L1837 _public enumerator_ `PlayStart`
- L1838 _public enumerator_ `LoopPoint`
- L1839 _public enumerator_ `Seeking`

#### struct `Electra::FAdaptiveStreamingPlayer::FBufferStats`  
`struct FBufferStats`  
_L1848-1910_
- L1891 _public function_ `void Clear()`
- L1898 _public function_ `void UpdateStalledDuration(int64 tNowMillisec)`
- L1902 _public function_ `int64 GetStalledDurationMillisec() const`
- L1906 _public member_ `FAccessUnitBufferInfo StreamBuffer;`
- L1907 _public member_ `IAccessUnitBufferListener::FBufferStats DecoderInputBuffer;`
- L1908 _public member_ `IDecoderOutputBufferListener::FDecodeReadyStats DecoderOutputBuffer;`
- L1909 _public member_ `FStallMonitor DecoderOutputStalledMonitor;`

#### struct `Electra::FAdaptiveStreamingPlayer::FBufferStats::FStallMonitor`  
`struct FStallMonitor`  
_L1850-1889_
- L1852 _public member_ `int64 DurationMillisec;`
- L1853 _public member_ `int64 PreviousCheckTime;`
- L1854 _public member_ `bool bPreviousState;`
- L1855 _public function_ `FStallMonitor()`
- L1859 _public function_ `void Clear()`
- L1865 _public function_ `void Update(int64 tNowMillisec, bool bInCurrentStallState)`
- L1885 _public function_ `int64 GetStalledDurationMillisec() const`

#### struct `Electra::FAdaptiveStreamingPlayer::FPrerollVars`  
`struct FPrerollVars`  
_L1912-1933_
- L1914 _public function_ `FPrerollVars()`
- L1919 _public function_ `void Clear()`
- L1927 _public member_ `int64 StartTime;`
- L1928 _public member_ `bool bHaveEnoughVideo;`
- L1929 _public member_ `bool bHaveEnoughAudio;`
- L1930 _public member_ `bool bHaveEnoughText;`
- L1931 _public member_ `bool bIsVeryFirstStart;`
- L1932 _public member_ `bool bIsMidSequencePreroll;`

#### struct `Electra::FAdaptiveStreamingPlayer::FPostrollVars`  
`struct FPostrollVars`  
_L1935-1965_
- L1952 _public function_ `FPostrollVars()`
- L1957 _public function_ `void Clear()`
- L1963 _public member_ `FRenderState Video;`
- L1964 _public member_ `FRenderState Audio;`

#### struct `Electra::FAdaptiveStreamingPlayer::FPostrollVars::FRenderState`  
`struct FRenderState`  
_L1937-1950_
- L1939 _public function_ `FRenderState()`
- L1943 _public function_ `void Clear()`
- L1948 _public member_ `int64 LastCheckTime;`
- L1949 _public member_ `int32 LastBufferCount;`

#### struct `Electra::FAdaptiveStreamingPlayer::FSeekVars`  
`struct FSeekVars`  
_L1967-2005_
- L1969 _public function_ `void ClearWorkVars()`
- L1974 _public function_ `void Reset()`
- L1985 _public function_ `void SetFinished()`
- L1990 _public function_ `bool HasPendingSeek()`
- L1996 _public member_ `bool bPrerollDone = false;`
- L1997 _public member_ `bool bIsPlayStart = true;`
- L1999 _public member_ `TOptional<FSeekParam> ActiveRequest;`
- L2001 _public member_ `mutable FCriticalSection Lock;`
- L2003 _public member_ `TOptional<FSeekParam> PendingRequest;` — The pending request must be accessed under lock since it is written to by the main thread and read from the worker thread!
- L2004 _public member_ `FTimeRange PlayrangeOnRequest;`

#### struct `Electra::FAdaptiveStreamingPlayer::FStreamBitrateInfo`  
`struct FStreamBitrateInfo`  
_L2007-2020_
- L2009 _public function_ `FStreamBitrateInfo()`
- L2013 _public function_ `void Clear()`
- L2018 _public member_ `int32 Bitrate;`
- L2019 _public member_ `int32 QualityLevel;`

#### struct `Electra::FAdaptiveStreamingPlayer::FPendingSegmentRequest`  
`struct FPendingSegmentRequest`  
_L2022-2032_
- L2024 _public member_ `TSharedPtrTS<IStreamSegment> Request;`
- L2025 _public member_ `FTimeValue AtTime;`
- L2026 _public member_ `TSharedPtrTS<IManifest::IPlayPeriod> Period;` — Set if transitioning between periods. This is the new period that needs to be readied.
- L2027 _public member_ `bool bStartOver = false;` — True when switching tracks within an ongoing period
- L2028 _public member_ `bool bPlayPosAutoReselect = false;` — True when trying to re-select a stream at the start of a new period when it was not available before.
- L2029 _public member_ `bool bDidRequestNewPeriodStreams = false;`
- L2030 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L2031 _public member_ `FPlayStartPosition StartoverPosition;`

#### struct `Electra::FAdaptiveStreamingPlayer::FPeriodInformation`  
`struct FPeriodInformation`  
_L2034-2045_
- L2036 _public member_ `TSharedPtrTS<ITimelineMediaAsset> Period;`
- L2037 _public member_ `FString ID;`
- L2038 _public member_ `FTimeRange TimeRange;`
- L2039 _public member_ `int64 LoopCount = 0;`
- L2042 _public member_ `TSharedPtrTS<FBufferSourceInfo> BufferSourceInfoVid;` — Currently selected buffer source per stream type in this period.
- L2043 _public member_ `TSharedPtrTS<FBufferSourceInfo> BufferSourceInfoAud;`
- L2044 _public member_ `TSharedPtrTS<FBufferSourceInfo> BufferSourceInfoTxt;`

#### struct `Electra::FAdaptiveStreamingPlayer::FInternalStreamSelectionAttributes`  
`struct FInternalStreamSelectionAttributes : public FStreamSelectionAttributes`  
_L2048-2058_
- inherits: `FStreamSelectionAttributes`
- L2050 _public function_ `bool IsDeselected() const`
- L2052 _public function_ `void Select()`
- L2054 _public function_ `void Deselect()`
- L2057 _private member_ `bool bIsSelected = true;`

#### struct `Electra::FAdaptiveStreamingPlayer::FStreamDataBuffers`  
`struct FStreamDataBuffers`  
_L2062-2077_
- L2064 _public member_ `TSharedPtrTS<FMultiTrackAccessUnitBuffer> VidBuffer;`
- L2065 _public member_ `TSharedPtrTS<FMultiTrackAccessUnitBuffer> AudBuffer;`
- L2066 _public member_ `TSharedPtrTS<FMultiTrackAccessUnitBuffer> TxtBuffer;`
- L2067 _public function_ `TSharedPtrTS<FMultiTrackAccessUnitBuffer> GetBuffer(EStreamType InStreamType)`

#### struct `Electra::FAdaptiveStreamingPlayer::FInternalLoopState`  
`struct FInternalLoopState : public FLoopState`  
_L2080-2084_
- inherits: `FLoopState`
- L2082 _public member_ `FTimeValue From;`
- L2083 _public member_ `FTimeValue To;`

#### struct `Electra::FAdaptiveStreamingPlayer::FMediaMetadataUpdate`  
`struct FMediaMetadataUpdate`  
_L2087-2135_
- L2089 _public function_ `FMediaMetadataUpdate()`
- L2093 _public function_ `void Reset()`
- L2099 _public function_ `void AddEntry(const FTimeValue& InValidFrom, const TSharedPtrTS<FMetadataParser>& InMetadata, bool bInTriggerInternalRefresh)`
- L2120 _public prototype_ `EResult Handle(const FTimeValue& InAtTime);`
- L2121 _public function_ `TSharedPtrTS<FMetadataParser> GetActive() const`
- L2132 _public member_ `TArray<FEntry> NextEntries;`
- L2133 _public member_ `TSharedPtrTS<FMetadataParser> ActiveMetadata;`
- L2134 _public member_ `FTimeValue ActiveSince;`

#### enum `Electra::FAdaptiveStreamingPlayer::FMediaMetadataUpdate::EResult`  
`enum class EResult`  
_L2114-2119_
- L2116 _public enumerator_ `NoChange`
- L2117 _public enumerator_ `Changed`
- L2118 _public enumerator_ `ChangedAndUpdate`

#### struct `Electra::FAdaptiveStreamingPlayer::FMediaMetadataUpdate::FEntry`  
`struct FEntry`  
_L2126-2131_
- L2128 _public member_ `FTimeValue ValidFrom;`
- L2129 _public member_ `TSharedPtrTS<FMetadataParser> Metadata;`
- L2130 _public member_ `bool bTriggerInternalRefresh = false;`

#### struct `Electra::FAdaptiveStreamingPlayer::FMetadataHandlingState`  
`struct FMetadataHandlingState`  
_L2137-2150_
- L2139 _public function_ `FMetadataHandlingState()`
- L2143 _public function_ `void Reset()`
- L2148 _public member_ `FString LastSentPeriodID;`
- L2149 _public member_ `FTimeValue LastHandlingTime;`

#### Free symbols / members of external scopes

- L45 _macro_ `#define INTERR_ALL_STREAMS_HAVE_FAILED 1`
- L46 _macro_ `#define INTERR_UNSUPPORTED_FORMAT 2`
- L47 _macro_ `#define INTERR_COULD_NOT_LOCATE_START_SEGMENT 3`
- L48 _macro_ `#define INTERR_COULD_NOT_LOCATE_START_PERIOD 4`
- L49 _macro_ `#define INTERR_UNSUPPORTED_CODEC 5`
- L50 _macro_ `#define INTERR_CODEC_CHANGE_NOT_SUPPORTED 6`
- L51 _macro_ `#define INTERR_NO_STREAM_INFORMATION 7`
- L52 _macro_ `#define INTERR_GENERAL_FAILURE 8`
- L53 _macro_ `#define INTERR_FRAGMENT_NOT_AVAILABLE 0x101`
- L54 _macro_ `#define INTERR_FRAGMENT_READER_REQUEST 0x102`
- L55 _macro_ `#define INTERR_CREATE_FRAGMENT_READER 0x103`
- L56 _macro_ `#define INTERR_REBUFFER_SHALL_THROW_ERROR 0x200`
- L61 _macro_ `#define NOTIFY_DATA_AVAILABILITY_AT_START_AND_END 0` — Set this to `1` to signal no data availability right at the start of a seek (and initial playback) and at the end. Set to `0` to only notify about mid-playback state changes.
- L64 _namespace_ `namespace Electra`
- L441 _function_ `` (scope `Electra::FPlaybackState::SetTrackMetadata`)
- L1111 _function_ `` (scope `Electra::FAdaptiveStreamingPlayer::TDeleter::operator ()`)
- L2106 _function_ `` (scope `Electra::FAdaptiveStreamingPlayer::FMediaMetadataUpdate::AddEntry`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptiveStreamingPlayerInternalConfig.h` (Private)


#### struct `Electra::AdaptiveStreamingPlayerConfig::FConfiguration`  
`struct FConfiguration`  
_L11-59_
- L13 _public function_ `FConfiguration()`
- L45 _public member_ `FAccessUnitBuffer::FConfiguration StreamBufferConfigVideo;`
- L46 _public member_ `FAccessUnitBuffer::FConfiguration StreamBufferConfigAudio;`
- L47 _public member_ `FAccessUnitBuffer::FConfiguration StreamBufferConfigAudioOnly;`
- L48 _public member_ `FAccessUnitBuffer::FConfiguration StreamBufferConfigText;`
- L50 _public member_ `bool bHoldLastFrameDuringSeek;`
- L52 _public member_ `double InitialBufferMinTimeAvailBeforePlayback;`
- L53 _public member_ `double SeekBufferMinTimeAvailBeforePlayback;`
- L54 _public member_ `double RebufferMinTimeAvailBeforePlayback;`
- L57 _public member_ `FVideoDecoderLimit H264LimitUpto30fps;` — Deprecate these soon
- L58 _public member_ `FVideoDecoderLimit H264LimitAbove30fps;`

#### struct `Electra::AdaptiveStreamingPlayerConfig::FConfiguration::FVideoDecoderLimit`  
`struct FVideoDecoderLimit`  
_L32-42_
- L40 _public member_ `FStreamCodecInformation::FResolution MaxResolution;`
- L41 _public member_ `FTierProfileLevel MaxTierProfileLevel;`

#### struct `Electra::AdaptiveStreamingPlayerConfig::FConfiguration::FVideoDecoderLimit::FTierProfileLevel`  
`struct FTierProfileLevel`  
_L34-39_
- L36 _public member_ `int32 Tier = 0;`
- L37 _public member_ `int32 Profile = 0;`
- L38 _public member_ `int32 Level = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L9 _namespace_ `namespace AdaptiveStreamingPlayerConfig` (scope `Electra`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptiveStreamingPlayerMetrics.h` (Private)


#### enum `Electra::Metrics::ESegmentType`  
`enum class ESegmentType`  
_L19-26_
- L21 _public enumerator_ `Undefined`
- L22 _public enumerator_ `Init`
- L23 _public enumerator_ `Media`
- L24 _public enumerator_ `Sideloaded`
- L25 _public enumerator_ `PlaylistElement`

#### enum `Electra::Metrics::EBufferingReason`  
`enum class EBufferingReason`  
_L55-60_
- L57 _public enumerator_ `Initial`
- L58 _public enumerator_ `Seeking`
- L59 _public enumerator_ `Rebuffering`

#### enum `Electra::Metrics::ETimeJumpReason`  
`enum class ETimeJumpReason`  
_L75-81_
- L77 _public enumerator_ `UserSeek`
- L78 _public enumerator_ `FellOffTimeline`
- L79 _public enumerator_ `FellBehindWallclock`
- L80 _public enumerator_ `Looping`

#### struct `Electra::Metrics::FBufferStats`  
`struct FBufferStats`  
_L98-111_
- L100 _public function_ `FBufferStats()`
- L107 _public member_ `EStreamType BufferType;`
- L108 _public member_ `double MaxDurationInSeconds;`
- L109 _public member_ `double DurationInUse;`
- L110 _public member_ `int64 BytesInUse;`

#### struct `Electra::Metrics::FPlaylistDownloadStats`  
`struct FPlaylistDownloadStats`  
_L113-124_
- L115 _public member_ `FMediaURL Url;`
- L116 _public member_ `FString FailureReason;` — Human readable failure reason. Only for display purposes.
- L117 _public member_ `Playlist::EListType ListType = Playlist::EListType::Main;`
- L118 _public member_ `Playlist::ELoadType LoadType = Playlist::ELoadType::Initial;`
- L119 _public member_ `int32 HTTPStatusCode = 0;` — HTTP status code (0 if not connected to server yet)
- L120 _public member_ `int32 RetryNumber = 0;`
- L121 _public member_ `bool bWasSuccessful = false;`
- L122 _public member_ `bool bDidTimeout = false;`
- L123 _public member_ `bool bWasAborted = false;`

#### struct `Electra::Metrics::FSegmentDownloadStats`  
`struct FSegmentDownloadStats`  
_L126-224_
- L140 _public member_ `EStreamType StreamType;` — Inputs from stream request
- L141 _public member_ `ESegmentType SegmentType;` — Type of segment (init or media)
- L142 _public member_ `FMediaURL URL;` — Effective URL used to download from
- L143 _public member_ `FString Range;` — Range used to download
- L144 _public member_ `FString MediaAssetID;`
- L145 _public member_ `FString AdaptationSetID;`
- L146 _public member_ `FString RepresentationID;`
- L147 _public member_ `double PresentationTime;` — Presentation time on media timeline
- L148 _public member_ `double Duration;` — Duration of segment as specified in manifest
- L149 _public member_ `int64 SteeringID;` — ID from the content steering handler for this request.
- L150 _public member_ `int32 Bitrate;` — Stream bitrate as specified in manifest
- L151 _public member_ `int32 QualityIndex;` — Quality index of this segment
- L152 _public member_ `int32 HighestQualityIndex;` — The highest quality index that could be had.
- L153 _public member_ `int32 RetryNumber;`
- L154 _public member_ `bool bWaitingForRemoteRetryElement;`
- L157 _public member_ `uint32 StatsID;` — Outputs from stream reader
- L158 _public member_ `FString FailureReason;` — Human readable failure reason. Only for display purposes.
- L159 _public member_ `double AvailibilityDelay;` — Time the download had to wait for the segment to enter its availability window.
- L160 _public member_ `double DurationDownloaded;` — Duration of content successfully downloaded. May be less than Duration in case of errors.
- L161 _public member_ `double DurationDelivered;` — Duration of content delivered to buffer. If larger than DurationDownloaded indicates dummy data was inserted into buffer.
- L162 _public member_ `double TimeToFirstByte;` — Time in seconds until first data byte was received
- L163 _public member_ `double TimeToDownload;` — Total time in seconds for entire download
- L164 _public member_ `int64 ByteSize;` — Content-Length, may be -1 if unknown (either on error or chunked transfer)
- L165 _public member_ `int64 NumBytesDownloaded;` — Number of bytes successfully downloaded.
- L166 _public member_ `int32 HTTPStatusCode;` — HTTP status code (0 if not connected to server yet)
- L167 _public member_ `bool bWasSuccessful;` — true if download was successful, false if not
- L168 _public member_ `bool bWasAborted;` — true if download was aborted by ABR (not by playback!)
- L169 _public member_ `bool bDidTimeout;` — true if a timeout occurred. Only set if timeouts are enabled. Usually the ABR will monitor and abort.
- L170 _public member_ `bool bParseFailure;` — true if the segment could not be parsed
- L171 _public member_ `bool bIsMissingSegment;` — true if the segment was not actually downloaded because it is missing on the timeline.
- L172 _public member_ `bool bWasSkipped;` — true if the segment was skipped over due to internal timestamps being less than expected
- L173 _public member_ `bool bWasFalloffSegment;` — true if the segment was no longer present on the timeline.
- L174 _public member_ `bool bInsertedFillerData;`
- L175 _public member_ `bool bIsCachedResponse;`
- L176 _public member_ `TArray<IElectraHTTPStreamResponse::FTimingTrace> TimingTraces;`
- L177 _public member_ `TArray<FMovieChunkInfo> MovieChunkInfos;`
- L179 _public function_ `FSegmentDownloadStats()`
- L181 _public function_ `void Reset()`
- L200 _public function_ `void ResetOutput()`

#### struct `Electra::Metrics::FSegmentDownloadStats::FMovieChunkInfo`  
`struct FMovieChunkInfo`  
_L129-137_
- desc: Chunk timing
- L131 _public member_ `int64 HeaderOffset = 0;`
- L132 _public member_ `int64 PayloadStartOffset = 0;`
- L133 _public member_ `int64 PayloadEndOffset = 0;`
- L134 _public member_ `int64 NumKeyframeBytes = 0;`
- L135 _public member_ `FTimeValue ContentDuration;`
- L136 _public function_ `FMovieChunkInfo()`

#### struct `Electra::Metrics::FLicenseKeyStats`  
`struct FLicenseKeyStats`  
_L226-235_
- L228 _public function_ `FLicenseKeyStats()`
- L232 _public member_ `FString URL;`
- L233 _public member_ `FString FailureReason;` — Human readable failure reason. Only for display purposes.
- L234 _public member_ `bool bWasSuccessful;`

#### struct `Electra::Metrics::FDataAvailabilityChange`  
`struct FDataAvailabilityChange`  
_L237-250_
- L244 _public function_ `FDataAvailabilityChange() : StreamType(EStreamType::Unsupported), Availability(EAvailability::DataNotAvailable)`
- L248 _public member_ `EStreamType StreamType;` — Type of stream
- L249 _public member_ `EAvailability Availability;`

#### enum `Electra::Metrics::FDataAvailabilityChange::EAvailability`  
`enum class EAvailability`  
_L239-243_
- L241 _public enumerator_ `DataAvailable`
- L242 _public enumerator_ `DataNotAvailable`

#### struct `Electra::Metrics::FFrameStats`  
`struct FFrameStats`  
_L252-263_
- L254 _public member_ `uint64 NumTotal = 0;`
- L255 _public member_ `uint64 NumDropped = 0;`
- L256 _public member_ `uint32 NumNewDrops = 0;`
- L257 _public member_ `uint32 AvgDropsPerInterval = 0;`
- L258 _public member_ `uint32 MinDropsPerInterval = 0;`
- L259 _public member_ `uint32 MaxDropsPerInterval = 0;`
- L260 _public member_ `uint32 DropIntervalMs = 0;`
- L261 _public member_ `uint32 NumIntervals = 0;`
- L262 _public member_ `uint32 NumIntervalsWithDrops = 0;`

#### class `Electra::IAdaptiveStreamingPlayerMetrics`  
`class IAdaptiveStreamingPlayerMetrics`  
_L271-431_
- L274 _public prototype_ `virtual ~IAdaptiveStreamingPlayerMetrics() = default;`
- L283 _public prototype_ `virtual void ReportOpenSource(const FString& URL) = 0;` — Called when the source will be opened.
- L288 _public prototype_ `virtual void ReportReceivedMainPlaylist(const FString& EffectiveURL) = 0;` — Called when the source's main playlist has beed loaded successfully.
- L293 _public prototype_ `virtual void ReportReceivedPlaylists() = 0;` — Called when the dependent child playlists have been loaded successfully.
- L298 _public prototype_ `virtual void ReportTracksChanged() = 0;` — Called when the available tracks or their properties have changed.
- L303 _public prototype_ `virtual void ReportPlaylistDownload(const Metrics::FPlaylistDownloadStats& PlaylistDownloadStats) = 0;` — Called at the end of every downloaded playlist.
- L308 _public prototype_ `virtual void ReportBufferingStart(Metrics::EBufferingReason BufferingReason) = 0;` — Called when buffering of data begins.
- L315 _public prototype_ `virtual void ReportBufferingEnd(Metrics::EBufferingReason BufferingReason) = 0;` — Called when buffering of data ends. This does not necessarily coincide with a segment download as buffering ends as soon as sufficient data has been received to start/resume playback.
- L321 _public prototype_ `virtual void ReportBandwidth(int64 EffectiveBps, int64 ThroughputBps, double LatencyInSeconds) = 0;` — Called at the end of each downloaded video segment. The order will be ReportSegmentDownload() followed by ReportBandwidth()
- L326 _public prototype_ `virtual void ReportBufferUtilization(const Metrics::FBufferStats& BufferStats) = 0;` — Called before and after a segment download.
- L331 _public prototype_ `virtual void ReportSegmentDownload(const Metrics::FSegmentDownloadStats& SegmentDownloadStats) = 0;` — Called at the end of each downloaded segment.
- L336 _public prototype_ `virtual void ReportLicenseKey(const Metrics::FLicenseKeyStats& LicenseKeyStats) = 0;` — Called for license key events.
- L342 _public prototype_ `virtual void ReportVideoQualityChange(int32 NewBitrate, int32 PreviousBitrate, bool bIsDrasticDownswitch) = 0;` — Called when a new video stream segment is fetched at a different bitrate than before. A drastic change is one where quality _drops_ more than _one_ level.
- L348 _public prototype_ `virtual void ReportAudioQualityChange(int32 NewBitrate, int32 PreviousBitrate, bool bIsDrasticDownswitch) = 0;` — Called when a new audio stream segment is fetched at a different bitrate than before. A drastic change is one where quality _drops_ more than _one_ level.
- L353 _public prototype_ `virtual void ReportDataAvailabilityChange(const Metrics::FDataAvailabilityChange& DataAvailability) = 0;` — Called when stream data availability changes when feeding the decoder.
- L358 _public prototype_ `virtual void ReportDecodingFormatChange(const FStreamCodecInformation& NewDecodingFormat) = 0;` — Called when the format of the stream being decoded changes in some way.
- L363 _public prototype_ `virtual void ReportPrerollStart() = 0;` — Called when decoders start to decode first data to pre-roll the pipeline.
- L368 _public prototype_ `virtual void ReportPrerollEnd() = 0;` — Called when enough initial data has been decoded to pre-roll the pipeline.
- L375 _public prototype_ `virtual void ReportPlaybackStart() = 0;` — Called when playback starts for the first time. This is not called after resuming a paused playback. If playback has ended(!) and is then begun again by seeking back to an earlier point in time this callback will be triggered again. Seeking during playback will not cause this callback.
- L380 _public prototype_ `virtual void ReportPlaybackPaused() = 0;` — Called when the player enters pause mode, either through user request or an internal state change.
- L385 _public prototype_ `virtual void ReportPlaybackResumed() = 0;` — Called when the player resumes from pause mode, either through user request or an internal state change.
- L390 _public prototype_ `virtual void ReportPlaybackEnded() = 0;` — Called when playback has reached the end. See ReportPlaybackStart().
- L396 _public prototype_ `virtual void ReportJumpInPlayPosition(const FTimeValue& ToNewTime, const FTimeValue& FromTime, Metrics::ETimeJumpReason TimejumpReason) = 0;` — Called when the play position jumps either because of a user induced seek or because the play position fell off the timeline or because a wallclock synchronized Live playback fell too far behind the actual time.
- L401 _public prototype_ `virtual void ReportPlaybackStopped() = 0;` — Called when playback is terminally stopped.
- L407 _public prototype_ `virtual void ReportSeekCompleted() = 0;` — Called when a seek has completed such that the first new data is ready. Future data may still be buffering.
- L412 _public prototype_ `virtual void ReportMediaMetadataChanged(TSharedPtrTS<FMetadataParser> Metadata) = 0;` — Called when the media metadata has changed.
- L417 _public prototype_ `virtual void ReportError(const FString& ErrorReason) = 0;` — Called when an error occurs. Errors always result in termination of playback.
- L422 _public prototype_ `virtual void ReportLogMessage(IInfoLog::ELevel LogLevel, const FString& LogMessage, int64 PlayerWallclockMilliseconds) = 0;` — Called to output a log message. The log level is a player internal level.
- L429 _public prototype_ `virtual void ReportVideoFrameStats(const Metrics::FFrameStats& InFrameStats) = 0;`
- L430 _public prototype_ `virtual void ReportAudioFrameStats(const Metrics::FFrameStats& InFrameStats) = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Electra`
- L17 _namespace_ `namespace Metrics` (scope `Electra`)
- L27 _function_ `static const TCHAR * const GetSegmentTypeString(ESegmentType SegmentType)` (scope `Electra::Metrics`)
- L61 _function_ `static const TCHAR * const GetBufferingReasonString(EBufferingReason BufferingReason)` (scope `Electra::Metrics`)
- L82 _function_ `static const TCHAR * const GetTimejumpReasonString(ETimeJumpReason TimejumpReason)` (scope `Electra::Metrics`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/AdaptiveStreamingPlayerResourceRequest.h` (Private)


#### class `Electra::IAdaptiveStreamingPlayerResourceRequest`  
`class IAdaptiveStreamingPlayerResourceRequest : public TSharedFromThis<IAdaptiveStreamingPlayerResourceRequest, ESPMode::ThreadSafe>`  
_L16-40_
- inherits: `TSharedFromThis<IAdaptiveStreamingPlayerResourceRequest,ESPMode::ThreadSafe>`
- L26 _public prototype_ `virtual ~IAdaptiveStreamingPlayerResourceRequest() = default;`
- L29 _public prototype_ `virtual EPlaybackResourceType GetResourceType() const = 0;` — Returns the type of the requested resource.
- L31 _public prototype_ `virtual FString GetResourceURL() const = 0;` — Returns the URL of the requested resource.
- L36 _public prototype_ `virtual void SetPlaybackData(TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> PlaybackData, int64 TotalResourceSize) = 0;` — Sets the binary resource data. If data can not be provided do not set anything (or a nullptr) For a request of `BinaryData` you need to set `TotalResourceSize` to the total size of the file so the reader will know how big the file is. This is true even for `NumBytesToRead` set to 0.
- L39 _public prototype_ `virtual void SignalDataReady() = 0;` — Signal request completion. Must be called with or without data being set.

#### enum `Electra::IAdaptiveStreamingPlayerResourceRequest::EPlaybackResourceType`  
`enum class EPlaybackResourceType`  
_L19-24_
- L21 _public enumerator_ `Empty`
- L22 _public enumerator_ `Playlist`
- L23 _public enumerator_ `LicenseKey`

#### class `Electra::IAdaptiveStreamingPlayerResourceProvider`  
`class IAdaptiveStreamingPlayerResourceProvider`  
_L44-49_
- L47 _public prototype_ `virtual ~IAdaptiveStreamingPlayerResourceProvider() = default;`
- L48 _public prototype_ `virtual void ProvideStaticPlaybackDataForURL(TSharedPtr<IAdaptiveStreamingPlayerResourceRequest, ESPMode::ThreadSafe> InOutRequest) = 0;`

#### class `Electra::IHTTPResourceRequestObject`  
`class IHTTPResourceRequestObject : public TSharedFromThis<IHTTPResourceRequestObject, ESPMode::ThreadSafe>`  
_L54-58_
- inherits: `TSharedFromThis<IHTTPResourceRequestObject,ESPMode::ThreadSafe>`
- L57 _public prototype_ `virtual ~IHTTPResourceRequestObject() = default;`

#### class `Electra::FHTTPResourceRequestCompletionSignal`  
`class FHTTPResourceRequestCompletionSignal : public TSharedFromThis<FHTTPResourceRequestCompletionSignal, ESPMode::ThreadSafe>`  
_L62-88_
- inherits: `TSharedFromThis<FHTTPResourceRequestCompletionSignal,ESPMode::ThreadSafe>`
- L65 _public function_ `static TSharedPtr<FHTTPResourceRequestCompletionSignal, ESPMode::ThreadSafe> Create()`
- L67 _public function_ `virtual ~FHTTPResourceRequestCompletionSignal()`
- L69 _public function_ `virtual void CompletionCallback(TSharedPtrTS<FHTTPResourceRequest> InRequest)`
- L72 _public function_ `void Wait()`
- L74 _public function_ `void WaitAndReset()`
- L76 _public function_ `void Signal()`
- L78 _public function_ `void Reset()`
- L80 _public function_ `bool IsSignaled() const`
- L82 _public function_ `bool WaitTimeout(int64 MicroSeconds)`
- L84 _public function_ `bool WaitTimeoutAndReset(int64 MicroSeconds)`
- L87 _private member_ `FMediaEvent Sig;`

#### class `Electra::FHTTPResourceRequest`  
`class FHTTPResourceRequest : public TSharedFromThis<FHTTPResourceRequest, ESPMode::ThreadSafe>`  
_L93-270_
- inherits: `TSharedFromThis<FHTTPResourceRequest,ESPMode::ThreadSafe>`
- L96 _public prototype_ `FHTTPResourceRequest();`
- L97 _public prototype_ `virtual ~FHTTPResourceRequest();`
- L99 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRequestCompletedCallback, TSharedPtrTS<FHTTPResourceRequest> );`
- L101 _public prototype_ `virtual bool SetFromJSON(const FString& InJSONParams);`
- L103 _public function_ `virtual FHTTPResourceRequest& URL(const FString& InURL)`
- L106 _public function_ `virtual FHTTPResourceRequest& Verb(const FString& InVerb)`
- L109 _public function_ `virtual FHTTPResourceRequest& UserAgent(const FString& InUserAgent)`
- L112 _public function_ `virtual FHTTPResourceRequest& PostData(TArray<uint8> InPostData)`
- L115 _public function_ `virtual FHTTPResourceRequest& Range(const FString& InRange)`
- L118 _public function_ `virtual FHTTPResourceRequest& Headers(const TArray<HTTP::FHTTPHeader>& InHeaders)`
- L121 _public function_ `virtual FHTTPResourceRequest& Headers(const TArray<FString>& InHeaders)`
- L124 _public function_ `virtual FHTTPResourceRequest& AcceptEncoding(const FString& InAcceptEncoding)`
- L127 _public function_ `virtual FHTTPResourceRequest& ConnectionTimeout(const FTimeValue& InTimeoutAfter)`
- L130 _public function_ `virtual FHTTPResourceRequest& NoDataTimeout(const FTimeValue& InTimeoutAfter)`
- L133 _public function_ `virtual FHTTPResourceRequest& AllowStaticQuery(IAdaptiveStreamingPlayerResourceRequest::EPlaybackResourceType InStaticQueryType)`
- L136 _public function_ `virtual FHTTPResourceRequest& Object(TSharedPtrTS<IHTTPResourceRequestObject> InUserObject)`
- L139 _public function_ `virtual FHTTPResourceRequest& StreamTypeAndQuality(EStreamType InStreamType, int32 InQualityIndex, int32 InMaxQualityIndex)`
- L142 _public function_ `virtual FHTTPResourceRequest& CompletionSignal(const TSharedPtr<FHTTPResourceRequestCompletionSignal, ESPMode::ThreadSafe>& InSig)`
- L145 _public function_ `virtual FOnRequestCompletedCallback& Callback()`
- L148 _public prototype_ `virtual void StartGet(IPlayerSessionServices* InPlayerSessionServices);`
- L149 _public prototype_ `virtual void Cancel();`
- L152 _public function_ `virtual int32 GetError() const`
- L155 _public function_ `virtual FString GetErrorString() const`
- L167 _public function_ `virtual bool GetHasFinished() const`
- L170 _public function_ `virtual bool GetWasCanceled() const`
- L173 _public function_ `virtual FString GetURL() const`
- L176 _public function_ `virtual FTimeValue GetConnectionTimeout() const`
- L179 _public function_ `virtual FTimeValue GetNoDataTimeout() const`
- L182 _public function_ `virtual IAdaptiveStreamingPlayerResourceRequest::EPlaybackResourceType GetStaticQuery() const`
- L185 _public function_ `virtual TSharedPtrTS<IHTTPResourceRequestObject> GetObject() const`
- L188 _public function_ `virtual TSharedPtrTS<FWaitableBuffer> GetResponseBuffer() const`
- L191 _public function_ `virtual const HTTP::FConnectionInfo* GetConnectionInfo() const`
- L194 _public function_ `virtual TSharedPtrTS<IElectraHttpManager::FRequest> GetRequest() const`
- L250 _private prototype_ `int32 HTTPProgressCallback(const IElectraHttpManager::FRequest* Request);`
- L251 _private prototype_ `void HTTPCompletionCallback(const IElectraHttpManager::FRequest* Request);`
- L252 _private function_ `void SetStaticDataReady()`
- L254 _private prototype_ `void StaticDataReady();`
- L255 _private member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L256 _private member_ `TSharedPtrTS<IElectraHttpManager::FRequest> Request;`
- L257 _private member_ `TSharedPtrTS<FWaitableBuffer> ReceiveBuffer;`
- L258 _private member_ `TSharedPtrTS<IElectraHttpManager::FProgressListener> ProgressListener;`
- L259 _private member_ `FOnRequestCompletedCallback CompletedCallback;`
- L260 _private member_ `TWeakPtrTS<IHTTPResourceRequestObject> UserObject;`
- L261 _private member_ `TWeakPtrTS<IElectraHttpManager> HTTPManager;`
- L262 _private member_ `TMediaOptionalValue<IAdaptiveStreamingPlayerResourceRequest::EPlaybackResourceType> StaticQueryType;`
- L263 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L264 _private member_ `bool bWasAdded = false;`
- L265 _private member_ `bool bWasCanceled = false;`
- L266 _private member_ `bool bHasFinished = false;`
- L267 _private member_ `bool bStaticDataReady = false;`
- L268 _private member_ `bool bInCallback = false;`
- L269 _private member_ `int32 Error = 0;`

#### class `Electra::FHTTPResourceRequest::FStaticResourceRequest`  
`class FStaticResourceRequest : public IAdaptiveStreamingPlayerResourceRequest`  
_L199-247_
- inherits: `IAdaptiveStreamingPlayerResourceRequest`
- L202 _public function_ `FStaticResourceRequest(TWeakPtrTS<FHTTPResourceRequest> InOwner) : Owner(InOwner)`
- L203 _public prototype_ `virtual ~FStaticResourceRequest() = default;`
- L205 _public function_ `EPlaybackResourceType GetResourceType() const override`
- L211 _public function_ `FString GetResourceURL() const override`
- L217 _public function_ `void SetPlaybackData(TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> PlaybackData, int64 TotalResourceSize) override`
- L237 _public function_ `void SignalDataReady() override` — Signal request completion. Must be called with or without data being set.
- L246 _private member_ `TWeakPtrTS<FHTTPResourceRequest> Owner;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`
- L99 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRequestCompletedCallback, TSharedPtrTS<FHTTPResourceRequest> );`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/CMCDHandler.h` (Private)


#### class `Electra::FCMCDHandler`  
`class FCMCDHandler : public IAdaptiveStreamingPlayerMetrics`  
_L36-428_
- inherits: `IAdaptiveStreamingPlayerMetrics`
- desc: Common Media Client Data (CMCD) Handler This handler implements v1 of CTA-5004. Version 2 is still under development and changes often. We recognize elements here but do not process them yet.
- L39 _public prototype_ `FCMCDHandler(IPlayerSessionServices* InPlayerSessionServices);`
- L40 _public prototype_ `virtual ~FCMCDHandler();`
- L100 _public function_ `static const TCHAR* IncludeInRequests_Segment()`
- L101 _public function_ `static const TCHAR* IncludeInRequests_FirstPlaylist()`
- L102 _public function_ `static const TCHAR* IncludeInRequests_Playlist()`
- L103 _public function_ `static const TCHAR* IncludeInRequests_Steering()`
- L104 _public function_ `static const TCHAR* IncludeInRequests_Other()`
- L105 _public function_ `static const TCHAR* IncludeInRequests_DRM()`
- L107 _public function_ `static const TCHAR* Key_CmcdArray()`
- L108 _public function_ `static const TCHAR* Key_ContentId()`
- L109 _public function_ `static const TCHAR* Key_SessionId()`
- L110 _public function_ `static const TCHAR* Key_Type()`
- L111 _public function_ `static const TCHAR* Key_Version()`
- L112 _public function_ `static const TCHAR* Key_IncludeInRequests()`
- L113 _public function_ `static const TCHAR* Key_CDNs()`
- L114 _public function_ `static const TCHAR* Key_Mode()`
- L115 _public function_ `static const TCHAR* Key_Keys()`
- L121 _public prototype_ `bool IsEnabled();` — Returns true if CMCD is enabled for this session, false if not.
- L126 _public prototype_ `void PeriodicHandle();`
- L131 _public prototype_ `void Initialize(const FString& InContentID, const FString& InSessionID, const FString& InConfiguration);` — Initialize the CMCD handler after creating it.
- L140 _public prototype_ `bool UseParametersFromPlaylist();` — Returns `true` when the initial configuration, either implicitly or by stream format defaults, allows to use parameters provided by the playlist. In that case construct a configuration structure from the parameters in the playlist and update the configuration.
- L147 _public prototype_ `FString UsePlaylistParametersFromKey();` — If `UseParametersFromPlaylist()` returns `true` and the streaming format does not have a standardized way of conveying CMCD parameters, see if the playlist has a user data element of the name returned by this function and if so, assume it contains the CMCD configuration.
- L152 _public prototype_ `void UpdateParameters(const FString& InUpdatedConfiguration);` — Update the initial configuration with this new config.
- L160 _public prototype_ `void SetStreamingFormat(EStreamingFormat InStreamingFormat);` — Set the streaming format. This should be done at least once before or after calling `Initialize()`. If the precise sub-format is only known after loading the playlist, call this method again with the final determined format.
- L166 _public prototype_ `void SetStreamType(EStreamType InStreamType);` — Set the stream type. This is not bound to change during playback (but it could, if Live turns into VoD) and it is simpler to set it once instead of providing it in every `FRequestObjectInfo` (see below).
- L172 _public prototype_ `void SetPlayableBitrateRange(Electra::EStreamType InStreamType, int32 InLowestBitrate, int32 InHighestBitrate);` — Sets the lowest and highest bitrates of a media type this platform is allowed to play. Used for the `tb` (in v1; and later for v2 `tpb`, `lb`, `tab` and `lab`)
- L245 _public prototype_ `void SetupRequestObject(ERequestType InRequestType, EObjectType InObject , FString& InOutRequestURL, TArray<HTTP::FHTTPHeader>& InOutRequestHeaders, const FString& InCDNId, const FRequestObjectInfo& InObjectInfo);` — Modifies the request headers or URL of the given request to include the CMCD metrics.
- L250 _public prototype_ `FString RemoveParamsFromURL(FString InURL);` — Removes a `CMCD` query parameter from the URL.
- L253 _private prototype_ `void ReportOpenSource(const FString& InURL) override;`
- L254 _private prototype_ `void ReportReceivedMainPlaylist(const FString& InEffectiveURL) override;`
- L255 _private prototype_ `void ReportReceivedPlaylists() override;`
- L256 _private prototype_ `void ReportTracksChanged() override;`
- L257 _private prototype_ `void ReportPlaylistDownload(const Metrics::FPlaylistDownloadStats& InPlaylistDownloadStats) override;`
- L258 _private prototype_ `void ReportBufferingStart(Metrics::EBufferingReason InBufferingReason) override;`
- L259 _private prototype_ `void ReportBufferingEnd(Metrics::EBufferingReason InBufferingReason) override;`
- L260 _private prototype_ `void ReportBandwidth(int64 InEffectiveBps, int64 InThroughputBps, double InLatencyInSeconds) override;`
- L261 _private prototype_ `void ReportBufferUtilization(const Metrics::FBufferStats& InBufferStats) override;`
- L262 _private prototype_ `void ReportSegmentDownload(const Metrics::FSegmentDownloadStats& InSegmentDownloadStats) override;`
- L263 _private prototype_ `void ReportLicenseKey(const Metrics::FLicenseKeyStats& InLicenseKeyStats) override;`
- L264 _private prototype_ `void ReportVideoQualityChange(int32 InNewBitrate, int32 InPreviousBitrate, bool bInIsDrasticDownswitch) override;`
- L265 _private prototype_ `void ReportAudioQualityChange(int32 InNewBitrate, int32 InPreviousBitrate, bool bInIsDrasticDownswitch) override;`
- L266 _private prototype_ `void ReportDataAvailabilityChange(const Metrics::FDataAvailabilityChange& InDataAvailability) override;`
- L267 _private prototype_ `void ReportDecodingFormatChange(const FStreamCodecInformation& InNewDecodingFormat) override;`
- L268 _private prototype_ `void ReportPrerollStart() override;`
- L269 _private prototype_ `void ReportPrerollEnd() override;`
- L270 _private prototype_ `void ReportPlaybackStart() override;`
- L271 _private prototype_ `void ReportPlaybackPaused() override;`
- L272 _private prototype_ `void ReportPlaybackResumed() override;`
- L273 _private prototype_ `void ReportPlaybackEnded() override;`
- L274 _private prototype_ `void ReportJumpInPlayPosition(const FTimeValue& InToNewTime, const FTimeValue& InFromTime, Metrics::ETimeJumpReason InTimejumpReason) override;`
- L275 _private prototype_ `void ReportPlaybackStopped() override;`
- L276 _private prototype_ `void ReportSeekCompleted() override;`
- L277 _private prototype_ `void ReportMediaMetadataChanged(TSharedPtrTS<FMetadataParser> InMetadata) override;`
- L278 _private prototype_ `void ReportError(const FString& InErrorReason) override;`
- L279 _private prototype_ `void ReportLogMessage(IInfoLog::ELevel InLogLevel, const FString& InLogMessage, int64 InPlayerWallclockMilliseconds) override;`
- L280 _private prototype_ `void ReportVideoFrameStats(const Metrics::FFrameStats& InFrameStats) override;`
- L281 _private prototype_ `void ReportAudioFrameStats(const Metrics::FFrameStats& InFrameStats) override;`
- L363 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L364 _private member_ `FString ContentID;`
- L365 _private member_ `FString SessionID;`
- L366 _private member_ `FString PlatformID;`
- L367 _private member_ `FString PlaylistParamImportKey;`
- L368 _private member_ `bool bApplyPlaylistParams = true;`
- L369 _private member_ `bool bInitOk = false;`
- L371 _private member_ `EStreamingFormat StreamingFormat = EStreamingFormat::Undefined;`
- L372 _private member_ `EStreamType StreamType = EStreamType::Undefined;`
- L373 _private member_ `TArray<FReportElement> ReportElements;`
- L374 _private member_ `FString PlatformKey;`
- L375 _private member_ `TMap<Electra::EStreamType, FBandwidths> Bandwidths;`
- L383 _private member_ `FVars Vars;`
- L393 _private prototype_ `const TCHAR* GetOT(EObjectType InObject);`
- L400 _private prototype_ `bool InitializeInternal(EInitFrom InInitFrom, const FString& InConfiguration);`
- L402 _private prototype_ `void ApplyManifestOrPlaylist(FReqHeaders& OutHeaders, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);`
- L403 _private prototype_ `void ApplyGeneric(FReqHeaders& OutHeaders, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);`
- L404 _private prototype_ `void ApplyInitSegment(FReqHeaders& OutHeaders, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);`
- L405 _private prototype_ `void ApplyMediaSegment(FReqHeaders& OutHeaders, EObjectType InObject, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo, const FURL_RFC3986& InRequestHost);`
- L407 _private prototype_ `void ApplyReport(FURL_RFC3986& InOutRequestHost, const FReportElement& InParams, ERequestType InRequestType, EObjectType InObject, FString& InOutRequestURL, TArray<HTTP::FHTTPHeader>& InOutRequestHeaders, const FRequestObjectInfo& InObjectInfo);`
- L409 _private prototype_ `void Add_br(FReqHeaders& OutHeaders, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);`
- L410 _private prototype_ `void Add_bl(FReqHeaders& OutHeaders, const FReportElement& InParams, int32 InBufferLength);`
- L411 _private prototype_ `void Add_bs(FReqHeaders& OutHeaders, EObjectType InObject, const FReportElement& InParams);`
- L412 _private prototype_ `void Add_cid(FReqHeaders& OutHeaders, const FReportElement& InParams);`
- L413 _private prototype_ `void Add_d(FReqHeaders& OutHeaders, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);`
- L415 _private prototype_ `void Add_mtp(FReqHeaders& OutHeaders, const FReportElement& InParams, int32 InMeasuredThroughput);` — void Add_dl(FReqHeaders& OutHeaders, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);
- L416 _private prototype_ `void Add_nornrr(FReqHeaders& OutHeaders, const FURL_RFC3986& InRequestHost, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);`
- L417 _private prototype_ `void Add_ot(FReqHeaders& OutHeaders, const FReportElement& InParams, const TCHAR* InOT);`
- L418 _private prototype_ `void Add_pr(FReqHeaders& OutHeaders, const FReportElement& InParams, double InPlayRate);`
- L420 _private prototype_ `void Add_sf(FReqHeaders& OutHeaders, const FReportElement& InParams);` — void Add_rtp(FReqHeaders& OutHeaders, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);
- L421 _private prototype_ `void Add_sid(FReqHeaders& OutHeaders, const FReportElement& InParams);`
- L422 _private prototype_ `void Add_st(FReqHeaders& OutHeaders, const FReportElement& InParams);`
- L423 _private prototype_ `void Add_su(FReqHeaders& OutHeaders, const FReportElement& InParams);`
- L424 _private prototype_ `void Add_tb(FReqHeaders& OutHeaders, const FReportElement& InParams, const FRequestObjectInfo& InObjectInfo);`
- L425 _private prototype_ `void Add_v(FReqHeaders& OutHeaders, const FReportElement& InParams);`
- L426 _private prototype_ `void Add_platform(FReqHeaders& OutHeaders, const FReportElement& InParams);`

#### enum `Electra::FCMCDHandler::EStreamingFormat`  
`enum class EStreamingFormat`  
_L42-59_
- L48 _public enumerator_ `Undefined` — CMCD v1 defines HLS, DASH and SmoothStreaming, while CMCD v2 also adds low latency flavors. Upon requesting the main playlist it is not clear however if the stream will be low latency or not, so the `ot=m` type can't reflect the low latency version without externally provided means.
- L49 _public enumerator_ `HLS`
- L50 _public enumerator_ `DASH`
- L51 _public enumerator_ `SmoothStreaming` — not supported
- L53 _public enumerator_ `HESP` — v2
- L54 _public enumerator_ `LowLatencyDASH`
- L55 _public enumerator_ `LowLatencyLowDelayDASH`
- L56 _public enumerator_ `LowLatencyHLS`
- L58 _public enumerator_ `Other`

#### enum `Electra::FCMCDHandler::EStreamType`  
`enum class EStreamType`  
_L61-66_
- L63 _public enumerator_ `Undefined`
- L64 _public enumerator_ `VOD`
- L65 _public enumerator_ `Live`

#### enum `Electra::FCMCDHandler::EObjectType`  
`enum class EObjectType`  
_L68-80_
- L70 _public enumerator_ `Undefined` — not known, used as a placeholder to omit the object type in requests
- L71 _public enumerator_ `ManifestOrPlaylist` — 'm'
- L72 _public enumerator_ `AudioOnly` — 'a'
- L73 _public enumerator_ `VideoOnly` — 'v'
- L74 _public enumerator_ `MuxedAudioAndVideo` — 'av'
- L75 _public enumerator_ `InitSegment` — 'i'		(probably also to be used for the index segment)
- L76 _public enumerator_ `CaptionOrSubtitle` — 'c'
- L77 _public enumerator_ `TimedTextTrack` — 'tt'
- L78 _public enumerator_ `CryptoKeyLicenseOrCert` — 'k'
- L79 _public enumerator_ `Other` — 'o'

#### enum `Electra::FCMCDHandler::ERequestType`  
`enum class ERequestType`  
_L82-98_
- L85 _public enumerator_ `InitSegment` — filtered by `@includeInRequests`: "segment"
- L86 _public enumerator_ `IndexSegment`
- L87 _public enumerator_ `Segment`
- L89 _public enumerator_ `FirstPlaylist` — filtered by `@includeInRequests`: "playlist"
- L90 _public enumerator_ `Playlist`
- L91 _public enumerator_ `PlaylistUpdate`
- L93 _public enumerator_ `Steering` — filtered by `@includeInRequests`: "steering"
- L95 _public enumerator_ `Other` — filtered by `@includeInRequests`: "other"
- L97 _public enumerator_ `DRM` — filtered by `@includeInRequests`: "drm"

#### struct `Electra::FCMCDHandler::FRequestObjectInfo`  
`struct FRequestObjectInfo`  
_L211-238_
- L220 _public member_ `TOptional<Electra::EStreamType> MediaStreamType;` — Internal media stream type for index and init segment where the `ot` is only `i` and not `a`,`v` or `av`.
- L223 _public member_ `TOptional<int32> EncodedBitrate;` — v1
- L224 _public member_ `TOptional<int32> ObjectDuration;` — `d`
- L225 _public member_ `TOptional<int32> Deadline;` — `dl`
- L226 _public member_ `TArray<FNextObjectRequest> NextObjectRequest;` — `nor` and `nrr`
- L227 _public member_ `TOptional<int32> RequestedMaximumThroughput;` — `rtp`

#### struct `Electra::FCMCDHandler::FRequestObjectInfo::FNextObjectRequest`  
`struct FNextObjectRequest`  
_L213-217_
- L215 _public member_ `FString URL;`
- L216 _public member_ `FString Range;`

#### enum `Electra::FCMCDHandler::EV1Keys`  
`enum class EV1Keys : uint8`  
_L283-303_
- L285 _public enumerator_ `k_br`
- L286 _public enumerator_ `k_bl`
- L287 _public enumerator_ `k_bs`
- L288 _public enumerator_ `k_d`
- L289 _public enumerator_ `k_cid`
- L290 _public enumerator_ `k_dl`
- L291 _public enumerator_ `k_mtp`
- L292 _public enumerator_ `k_nor`
- L293 _public enumerator_ `k_nrr`
- L294 _public enumerator_ `k_ot`
- L295 _public enumerator_ `k_pr`
- L296 _public enumerator_ `k_rtp`
- L297 _public enumerator_ `k_sf`
- L298 _public enumerator_ `k_sid`
- L299 _public enumerator_ `k_st`
- L300 _public enumerator_ `k_su`
- L301 _public enumerator_ `k_tb`
- L302 _public enumerator_ `k_v`

#### struct `Electra::FCMCDHandler::FReportElement`  
`struct FReportElement`  
_L306-355_
- L320 _public member_ `EType Type = EType::Undefined;`
- L321 _public member_ `int32 Version = 0;`
- L322 _public member_ `TArray<FString> Hosts;`
- L323 _public member_ `TArray<FString> CDNs;`
- L324 _public member_ `TArray<TUniquePtr<FRegexPattern>> HostRegexPatterns;`
- L325 _public member_ `FString ContentID;`
- L326 _public member_ `FString SessionID;`
- L327 _public member_ `EMode Mode = EMode::Undefined;`
- L328 _public member_ `int32 EnabledKeys = 0;`
- L329 _public member_ `int32 EnabledRequestTypes = 0;`
- L330 _public function_ `void EnableKey(EV1Keys InKey)`
- L334 _public function_ `void DisableKey(EV1Keys InKey)`
- L338 _public function_ `bool IsKeyEnabled(EV1Keys InKey) const`
- L343 _public function_ `void EnableRequestType(ERequestType InType)`
- L347 _public function_ `void DisableRequestType(ERequestType InType)`
- L351 _public function_ `bool IsRequestTypeEnabled(ERequestType InType) const`

#### enum `Electra::FCMCDHandler::FReportElement::EType`  
`enum class EType`  
_L308-313_
- L310 _public enumerator_ `Undefined`
- L311 _public enumerator_ `Request`
- L312 _public enumerator_ `Event`

#### enum `Electra::FCMCDHandler::FReportElement::EMode`  
`enum EMode`  
_L314-319_
- L316 _public enumerator_ `Undefined`
- L317 _public enumerator_ `Headers`
- L318 _public enumerator_ `Query`

#### struct `Electra::FCMCDHandler::FBandwidths`  
`struct FBandwidths`  
_L357-361_
- L359 _public member_ `int32 Lowest = 0;`
- L360 _public member_ `int32 Highest = 0;`

#### struct `Electra::FCMCDHandler::FVars`  
`struct FVars`  
_L377-382_
- L379 _public member_ `bool bIsStartup = true;`
- L380 _public member_ `bool bVideoStarved = false;`
- L381 _public member_ `bool bAudioStarved = false;`

#### struct `Electra::FCMCDHandler::FReqHeaders`  
`struct FReqHeaders`  
_L385-391_
- L387 _public member_ `TArray<FString> Request;`
- L388 _public member_ `TArray<FString> Object;`
- L389 _public member_ `TArray<FString> Status;`
- L390 _public member_ `TArray<FString> Session;`

#### enum `Electra::FCMCDHandler::EInitFrom`  
`enum class EInitFrom`  
_L395-399_
- L397 _public enumerator_ `GlobalConfig`
- L398 _public enumerator_ `Playlist`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/ContentSteeringHandler.h` (Private)


#### class `Electra::FContentSteeringHandler`  
`class FContentSteeringHandler`  
_L26-276_
- L29 _public prototype_ `FContentSteeringHandler(IPlayerSessionServices* InPlayerSessionServices);`
- L30 _public prototype_ `virtual ~FContentSteeringHandler();`
- L68 _public prototype_ `bool InitialSetup(EStreamingProtocol InStreamProtocol, const FInitialParams& InInitialParams);` — Perform initial setup according to parameters provided in the main playlist. Can be done just once. Returns true if successful, false if already configured.
- L73 _public function_ `bool IsDVBDash() const` — Returns whether or not content steering was initialized to handle DVB DASH or not.
- L80 _public prototype_ `int64 GetCurrentRequestID();` — Returns the current internal request ID to associate the next steered HTTP request with. This helps track of actively used CDNs when reporting back where a completed request was made on.
- L92 _public prototype_ `void FinishedDownloadRequestOn(const Metrics::FSegmentDownloadStats& InDownloadStats, const FStreamParams& InStreamParams);`
- L98 _public prototype_ `bool NeedToObtainNewSteeringManifestNow();` — Call this periodically to check if a new steering manifest needs to be retrieved. Returns true if one is needed, false if not.
- L107 _public prototype_ `FString GetBaseSteeringServerRequestURL();` — Returns the URL to perform the next steering manifest request against. This returns the base URL only without any query parameters applied. You may append query parameters of your own on this URL before calling GetFinalSteeringServerRequestURL() to obtain the final URL to perform the request against.
- L114 _public prototype_ `FString GetFinalSteeringServerRequestURL(const FString& InBaseURL);` — Call this to prepare the base URL you got from GetBaseSteeringServerRequestURL() to which you may have appended your own query parameters with the query parameters necessary to make the steering server manifest request.
- L122 _public prototype_ `void SetSteeringServerRequestIsPending();` — Call this to set a flag that you are performing a steering manifest retrieval. This will temporarily cause `NeedToObtainNewSteeringManifestNow()` to return false to avoid making repeated requests. This internal flag is cleared on the next `UpdateWithSteeringServerResponse()` call.
- L127 _public prototype_ `void UpdateWithSteeringServerResponse(const FString& InResponse, int32 InHTTPStatusCode, const TArray<HTTP::FHTTPHeader>& InResponseHeaders);` — Call this to provide the steering server response.
- L134 _public prototype_ `void ReachedStableBuffer();` — To be called when the player has reached a stable buffer for the first time. This is used when the steering manifest is not queried before start in which case it is to be queried when the player buffers have become stable.
- L139 _public prototype_ `void PeriodicHandle();` — Call this every so often to handle internal state.
- L141 _public prototype_ `void PenalizeCDN(const FString& InCDN, int32 InDVBPriority, int32 InForSeconds);`
- L171 _public prototype_ `FSelectedCandidateURL SelectBestCandidateFrom(FString& OutMessage, ESelectFor InForType, const TArray<FCandidateURL>& InFromCandidates);`
- L176 _public prototype_ `void SetCurrentlyActivePathway(const FString& InCurrentPathway);` — Used by HLS to select the chosen pathway.
- L192 _public prototype_ `TArray<FPathwayCloneEntry> GetCurrentCloneEntries();` — Returns the current list of to-be-cloned pathways.
- L198 _public prototype_ `void CreatedClone(const FString& InClonedPathwayId);` — Notifies that a clone has been created. This removes the entry from the clone list and prevents it from being added to the list again in future steering manifest updates since we assume a clone can be created only once.
- L205 _public prototype_ `FString GetCurrentCDNListForDisplay();` — Returns the current list of prioritized CDN pathways to be used. Penalized CDNs are not included in this list.
- L206 _public prototype_ `FString GetPenalizedCDNListForDisplay();`
- L207 _public prototype_ `FString GetRecentlyAccessedCDNListForDisplay();`
- L231 _private prototype_ `void RebuildAvailableCDNList();`
- L233 _private prototype_ `bool IsValidPathway(const FString& InPathway) const;`
- L235 _private prototype_ `FSelectedCandidateURL SelectBestHLSCandidateFrom(FString& OutMessage, ESelectFor InForType, const TArray<FCandidateURL>& InFromCandidates);`
- L236 _private prototype_ `FSelectedCandidateURL SelectBestDASHCandidateFrom(FString& OutMessage, ESelectFor InForType, const TArray<FCandidateURL>& InFromCandidates);`
- L237 _private prototype_ `FSelectedCandidateURL SelectBestDVBDASHCandidateFrom(FString& OutMessage, ESelectFor InForType, const TArray<FCandidateURL>& InFromCandidates);`
- L239 _private prototype_ `void AddDynamicDASHClonesToCandidateList(TArray<FSelectedCandidateURL>& InOutFromCandidates);`
- L241 _private member_ `FCriticalSection Lock;`
- L242 _private member_ `FRandomStream RandomStream;`
- L243 _private member_ `IPlayerSessionServices* PlayerSessionService = nullptr;`
- L244 _private member_ `bool bIsSetup = false;`
- L245 _private member_ `bool bIsConfigured = false;`
- L246 _private member_ `EStreamingProtocol StreamingProtocol = EStreamingProtocol::Other;`
- L247 _private member_ `FInitialParams InitialParams;`
- L248 _private member_ `TArray<FString> CurrentCDNPriorities;`
- L249 _private member_ `FString CurrentlySelectedHLSPathway;`
- L250 _private member_ `FString CurrentlyChosenDVBCDNForType[2];`
- L251 _private member_ `bool bIsInitiallyChosenCDNLocked = false;`
- L253 _private member_ `TArray<FString> AvailableCDNs;`
- L255 _private member_ `FTimeValue TimeForNextUpdate;`
- L256 _private member_ `bool bNewManifestNeeded = false;`
- L257 _private member_ `bool bManifestRequestIsPending = false;`
- L258 _private member_ `FString NextServerRequestURL;`
- L259 _private member_ `FString ProxyURL;`
- L260 _private member_ `bool bIsFirstSteeringRequest = true;`
- L261 _private member_ `bool bDoFirstUpdateOnStableBuffer = false;`
- L262 _private member_ `int64 SteeringRequestID = 0;`
- L263 _private member_ `int32 LastTTL = 0;`
- L264 _private member_ `TArray<FPathwayCloneEntry> CurrentCloneEntries;`
- L265 _private member_ `TArray<FString> AlreadyClonePathways;`
- L266 _private member_ `TOptional<int64> SteeringRequestIDWhenNoCandidatesMatched;`
- L268 _private member_ `TArray<FPenalizedCDN> PenalizedCDNList;`
- L270 _private member_ `TArray<FString> ReferencedCDNsSinceLastUpdate;`
- L271 _private member_ `TMap<FString, FCDNThroughput> ObservedBandwidths;`
- L272 _private member_ `bool bNeedUpdateOfReferencedList = false;`
- L274 _private member_ `FString CDNPriorityDisplay;`
- L275 _private member_ `FString CDNAccessDisplay;`

#### enum `Electra::FContentSteeringHandler::EStreamingProtocol`  
`enum class EStreamingProtocol`  
_L32-37_
- L34 _public enumerator_ `HLS`
- L35 _public enumerator_ `DASH`
- L36 _public enumerator_ `Other`

#### struct `Electra::FContentSteeringHandler::FInitialParams`  
`struct FInitialParams`  
_L38-61_
- L41 _public member_ `FString RootDocumentURL;` — The URL of the main playlist in case the first steering manifest URL is relative.
- L43 _public member_ `FString FirstSteeringURL;` — First URL to request a steering manifest from
- L45 _public member_ `FString InitialDefaultCDN;` — The DASH @defaultServiceLocation or HLS PATHWAY-ID attribute provided in the first playlist.
- L47 _public member_ `FString ProxyURL;` — Used with DASH content steering only, the DASH-IF proposed @proxyServerURL attribute.
- L49 _public member_ `FString CustomFirstCDNPrioritization;` — A custom attribute with priority values to randomize the first CDN to use.
- L52 _public member_ `bool bQueryBeforeStart = false;` — Whether or not the steering server must be contacted before requesting anything else. This is not relevant to the operation of this handler and purely informational.
- L54 _public member_ `bool bHasContentSteering = false;` — True if actual content steering is conveyed in the playlist. False if we use custom prioritization.
- L58 _public member_ `bool bUseDVBPriorities = false;` — For use with DASH only, if the MPD is using a DVB profile and CDN selection should be made according to the <BaseURL>@priority/@weight attributes. If content steering is explicitly enabled (`FirstSteeringURL` is not empty) the DVB method will not be used.
- L60 _public member_ `bool bAllowAnyPathwayNames = false;` — True to not validate the pathway names so synthesized ones can be used.

#### struct `Electra::FContentSteeringHandler::FStreamParams`  
`struct FStreamParams`  
_L86-91_
- desc: To be called on every steered completed HTTP request. This tracks the CDN being used and the throughput observed.
- L88 _public member_ `bool bActiveVideo = false;`
- L89 _public member_ `bool bActiveAudio = false;`
- L90 _public member_ `bool bActiveSubtitles = false;`

#### struct `Electra::FContentSteeringHandler::FCandidateURL`  
`struct FCandidateURL`  
_L146-150_
- desc: Input candidate for selection.
- L148 _public member_ `FMediaURL MediaURL;`
- L149 _public member_ `FParamDict AdditionalParams;`

#### struct `Electra::FContentSteeringHandler::FSelectedCandidateURL`  
`struct FSelectedCandidateURL : FCandidateURL`  
_L155-165_
- inherits: `FCandidateURL`
- desc: Output candidate from selection.
- L157 _public prototype_ `FSelectedCandidateURL() = default;`
- L158 _public function_ `FSelectedCandidateURL(const FCandidateURL& InCandidate, int64 InSteeringID, bool bInWasCloned) : FCandidateURL(InCandidate), SteeringID(InSteeringID), bWasDynamicallyCloned(bInWasCloned)`
- L162 _public member_ `int64 SteeringID = 0;` — ID of the steering manifest at the time of selection.
- L164 _public member_ `bool bWasDynamicallyCloned = false;` — Indicates if this candidate has been dynamically cloned.

#### enum `Electra::FContentSteeringHandler::ESelectFor`  
`enum class ESelectFor`  
_L166-170_
- L168 _public enumerator_ `Playlist`
- L169 _public enumerator_ `Segment`

#### struct `Electra::FContentSteeringHandler::FPathwayCloneEntry`  
`struct FPathwayCloneEntry`  
_L182-190_
- desc: Structure to create a clone from an existing pathway.
- L184 _public member_ `FString BaseId;`
- L185 _public member_ `FString Id;`
- L186 _public member_ `FString Host;` — new hostname
- L187 _public member_ `TArray<FURL_RFC3986::FQueryParam> Params;` — new query parameters
- L188 _public member_ `TMap<FString, FString> PerVariantURIs;`
- L189 _public member_ `TMap<FString, FString> PerRenditionURIs;`

#### struct `Electra::FContentSteeringHandler::FInitialCDNChoice`  
`struct FInitialCDNChoice`  
_L210-214_
- L212 _public member_ `FString CDN;`
- L213 _public member_ `int32 Probability = 0;`

#### struct `Electra::FContentSteeringHandler::FPenalizedCDN`  
`struct FPenalizedCDN`  
_L216-221_
- L218 _public member_ `FString CDN;`
- L219 _public member_ `FTimeValue Until;`
- L220 _public member_ `int32 DVBpriority = 0;`

#### struct `Electra::FContentSteeringHandler::FCDNThroughput`  
`struct FCDNThroughput`  
_L223-229_
- L225 _public member_ `TSimpleMovingAverage<int64> Bandwidth;`
- L226 _public member_ `FString CDN;`
- L227 _public member_ `FTimeValue ExpiresAt;`
- L228 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/MPDElementsDASH.h` (Private)


#### class `Electra::IDashMPDXMLElementBuilder`  
`class IDashMPDXMLElementBuilder`  
_L22-44_
- desc: DASH MPD helper class to build an element from the XML document.
- L25 _public prototype_ `virtual ~IDashMPDXMLElementBuilder() = default;`
- L26 _public prototype_ `virtual bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) = 0;`
- L27 _public prototype_ `virtual bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) = 0;`
- L28 _public prototype_ `virtual bool ProcessClose(FManifestParserDASH* Builder, const TCHAR* ElementName) = 0;`
- L30 _public prototype_ `virtual const FString& GetName() const = 0;`
- L32 _public function_ `void SetXMLLineNumber(int32 XMLLineNumber)`
- L36 _public function_ `int32 GetXMLLineNumber() const`
- L40 _public prototype_ `FErrorDetail AddNamespace(const TCHAR* Name, const TCHAR* URI);`
- L42 _protected member_ `int32 InXMLLineNumber = 0;`
- L43 _protected member_ `TMap<FString, FString> Namespaces;`

#### class `Electra::IDashMPDElement`  
`class IDashMPDElement : public TSharedFromThis<IDashMPDElement, ESPMode::ThreadSafe>, public IDashMPDXMLElementBuilder`  
_L54-197_
- inherits: `TSharedFromThis<IDashMPDElement,ESPMode::ThreadSafe>,IDashMPDXMLElementBuilder`
- desc: DASH MPD element base class. Every MPD element derives from this class.
- L145 _public function_ `IDashMPDElement(const TCHAR* InName, const TCHAR* InData) : Name(InName), Data(InData)`
- L147 _public prototype_ `virtual ~IDashMPDElement() = default;`
- L148 _public prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L149 _public prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L150 _public prototype_ `bool ProcessClose(FManifestParserDASH* Builder, const TCHAR* ElementName) override;`
- L151 _public prototype_ `virtual EType GetElementType() const = 0;`
- L153 _public function_ `const FString& GetName() const override`
- L156 _public function_ `TSharedPtrTS<IDashMPDElement> GetParentElement() const`
- L157 _public function_ `const FString& GetData() const`
- L158 _public function_ `const TArray<FXmlAttribute>& GetOtherAttributes() const`
- L159 _public function_ `const TArray<TSharedPtrTS<FDashMPD_OtherType>>& GetOtherChildren() const`
- L161 _public prototype_ `virtual FString GetDocumentURL() const;`
- L163 _public prototype_ `virtual const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetEssentialProperties() const;`
- L164 _public prototype_ `virtual const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetSupplementalProperties() const;`
- L166 _public prototype_ `virtual const TArray<TSharedPtrTS<FDashMPD_BaseURLType>>& GetBaseURLs() const;`
- L168 _public prototype_ `virtual FXLink& GetXLink();`
- L173 _public prototype_ `virtual int32 ReplaceChildElementWithRemoteEntities(TSharedPtrTS<IDashMPDElement> Element, const FDashMPD_RootEntities& NewRootEntities, int64 OldResolveID, int64 NewResolveID);` — This is to be called to replace the given child element with one or more remote elements.
- L180 _public function_ `void SetParentElement(const TSharedPtrTS<IDashMPDElement>& InParentElement)` — Sets the parent element of this element which is used in traversing the hierarchy upwards in finding attributes of a parent element.
- L185 _protected prototype_ `bool NoChildElementAllowed(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber);`
- L186 _protected prototype_ `bool HandleXLink(FXLink& OutXLink, FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue);`
- L188 _protected member_ `FString Name;`
- L190 _protected member_ `TWeakPtrTS<IDashMPDElement> ParentElement;` — Weak pointer to the parent element.
- L192 _protected member_ `FString Data;` — Element data string
- L194 _protected member_ `TArray<FXmlAttribute> OtherAttributes;` — An array containing attributes not explicitly parsed into element members.
- L196 _protected member_ `TArray<TSharedPtrTS<FDashMPD_OtherType>> OtherChildren;` — An array of children that were not explicitly parsed.

#### enum `Electra::IDashMPDElement::EType`  
`enum class EType`  
_L57-102_
- L59 _public enumerator_ `MPD`
- L60 _public enumerator_ `Period`
- L61 _public enumerator_ `AdaptationSet`
- L62 _public enumerator_ `Representation`
- L63 _public enumerator_ `URLType`
- L64 _public enumerator_ `BaseURL`
- L65 _public enumerator_ `Location`
- L66 _public enumerator_ `ProgramInformation`
- L67 _public enumerator_ `Descriptor`
- L68 _public enumerator_ `Event`
- L69 _public enumerator_ `EventStream`
- L70 _public enumerator_ `SegmentBase`
- L71 _public enumerator_ `MultipleSegmentBase`
- L72 _public enumerator_ `SegmentList`
- L73 _public enumerator_ `SegmentTemplate`
- L74 _public enumerator_ `SegmentTimeline`
- L75 _public enumerator_ `SegmentURL`
- L76 _public enumerator_ `ContentComponent`
- L77 _public enumerator_ `SubRepresentation`
- L78 _public enumerator_ `Subset`
- L79 _public enumerator_ `URLQueryInfo`
- L80 _public enumerator_ `InitializationSet`
- L81 _public enumerator_ `Preselection`
- L82 _public enumerator_ `FailoverContent`
- L83 _public enumerator_ `Switching`
- L84 _public enumerator_ `RandomAccess`
- L85 _public enumerator_ `Label`
- L86 _public enumerator_ `ProducerReferenceTime`
- L87 _public enumerator_ `LeapSecondInformation`
- L88 _public enumerator_ `ContentPopularityRate`
- L89 _public enumerator_ `ContentPopularityRate_PR`
- L90 _public enumerator_ `UIntVWithID`
- L91 _public enumerator_ `UIntPairsWithID`
- L92 _public enumerator_ `OperatingBandwidth`
- L93 _public enumerator_ `OperatingQuality`
- L94 _public enumerator_ `PlaybackRate`
- L95 _public enumerator_ `Latency`
- L96 _public enumerator_ `ServiceDescription`
- L97 _public enumerator_ `Resync`
- L98 _public enumerator_ `ContentSteering`
- L99 _public enumerator_ `ClientDataReporting`
- L100 _public enumerator_ `CMCDParameters`
- L101 _public enumerator_ `Other`

#### struct `Electra::IDashMPDElement::FXmlAttribute`  
`struct FXmlAttribute`  
_L104-111_
- L106 _public function_ `const FString& GetName() const`
- L107 _public function_ `const FString& GetValue() const`
- L109 _public member_ `FString Name;`
- L110 _public member_ `FString Value;`

#### struct `Electra::IDashMPDElement::FXLink`  
`struct FXLink`  
_L113-134_
- L115 _public function_ `bool IsSet() const`
- L118 _public function_ `void Clear()`
- L125 _public function_ `const FString& GetHref() const`
- L126 _public function_ `const FString& GetActuate() const`
- L128 _public member_ `FString Href;`
- L129 _public member_ `FString Actuate;`
- L131 _public member_ `TSharedPtrTS<FMPDLoadRequestDASH> LoadRequest;`
- L132 _public member_ `int64 LastResolveID = 0;`
- L133 _public member_ `bool bWasRemoteEntity = false;`

#### struct `Electra::IDashMPDElement::FBoolUInt64`  
`struct FBoolUInt64`  
_L139-143_
- desc: Used by a few elements to either be a boolean (default false) or an optional integer
- L141 _public member_ `bool bBoolean = false;`
- L142 _public member_ `TMediaOptionalValue<uint64> Number;`

#### class `Electra::FDashMPD_OtherType`  
`class FDashMPD_OtherType : public IDashMPDElement`  
_L203-211_
- inherits: `IDashMPDElement`
- desc: An MPD element we do not care about but need to parse over.
- L205 _private typedef_ `typedef IDashMPDElement Super;`
- L207 _public function_ `FDashMPD_OtherType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L209 _public function_ `EType GetElementType() const override`

#### class `Electra::FDashMPD_BaseURLType`  
`class FDashMPD_BaseURLType : public IDashMPDElement`  
_L217-249_
- inherits: `IDashMPDElement`
- desc: 5.6.2 - BaseURLType
- L219 _private typedef_ `typedef IDashMPDElement Super;`
- L221 _public function_ `FDashMPD_BaseURLType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L223 _public prototype_ `virtual ~FDashMPD_BaseURLType() = default;`
- L224 _public function_ `EType GetElementType() const override`
- L228 _public function_ `const FString& GetURL() const` — Convenience method to get the URL.
- L230 _public function_ `const FString& GetServiceLocation() const`
- L231 _public function_ `const FString& GetByteRange() const`
- L232 _public function_ `const FTimeValue& GetAvailabilityTimeOffset() const`
- L233 _public function_ `const TMediaOptionalValue<bool>& GetAvailabilityTimeComplete() const`
- L234 _public function_ `const FTimeValue& GetTimeShiftBufferDepth() const`
- L235 _public function_ `const TMediaOptionalValue<int64> GetDVBPriority() const`
- L236 _public function_ `const TMediaOptionalValue<int64> GetDVBWeight() const`
- L239 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L240 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L242 _private member_ `FString ServiceLocation;`
- L243 _private member_ `FString ByteRange;`
- L244 _private member_ `FTimeValue AvailabilityTimeOffset = FTimeValue::GetZero();`
- L245 _private member_ `TMediaOptionalValue<bool> bAvailabilityTimeComplete;`
- L246 _private member_ `FTimeValue TimeShiftBufferDepth;`
- L247 _private member_ `TMediaOptionalValue<int64> DVBPriority;`
- L248 _private member_ `TMediaOptionalValue<int64> DVBWeight;`

#### class `Electra::FDashMPD_URLType`  
`class FDashMPD_URLType : public IDashMPDElement`  
_L255-273_
- inherits: `IDashMPDElement`
- desc: 5.3.9.2 (Table 17) - URLType
- L257 _private typedef_ `typedef IDashMPDElement Super;`
- L259 _public function_ `FDashMPD_URLType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L261 _public prototype_ `virtual ~FDashMPD_URLType() = default;`
- L262 _public function_ `EType GetElementType() const override`
- L265 _public function_ `const FString& GetSourceURL() const`
- L266 _public function_ `const FString& GetRange() const`
- L269 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L271 _private member_ `FString SourceURL;`
- L272 _private member_ `FString Range;`

#### class `Electra::FDashMPD_SegmentURLType`  
`class FDashMPD_SegmentURLType : public IDashMPDElement`  
_L279-301_
- inherits: `IDashMPDElement`
- desc: 5.3.9.2 (Table 18) - SegmentURLType
- L281 _private typedef_ `typedef IDashMPDElement Super;`
- L283 _public function_ `FDashMPD_SegmentURLType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L285 _public prototype_ `virtual ~FDashMPD_SegmentURLType() = default;`
- L286 _public function_ `EType GetElementType() const override`
- L289 _public function_ `const FString& GetMedia() const`
- L290 _public function_ `const FString& GetMediaRange() const`
- L291 _public function_ `const FString& GetIndex() const`
- L292 _public function_ `const FString& GetIndexRange() const`
- L295 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L297 _private member_ `FString Media;`
- L298 _private member_ `FString MediaRange;`
- L299 _private member_ `FString Index;`
- L300 _private member_ `FString IndexRange;`

#### class `Electra::FDashMPD_UrlQueryInfoType`  
`class FDashMPD_UrlQueryInfoType : public IDashMPDElement`  
_L310-352_
- inherits: `IDashMPDElement`
- desc: Annex I.2 - UrlQueryInfoType Annex I.3 - ExtendedUrlInfoType For simplicity both these types are merged into a single type.
- L312 _private typedef_ `typedef IDashMPDElement Super;`
- L320 _public function_ `FDashMPD_UrlQueryInfoType(const TCHAR* Name, const TCHAR* Data, EExtendedUrlInfoType InExtendedUrlInfoType=EExtendedUrlInfoType::ExtUrlQueryInfo) : Super(Name, Data), ExtendedUrlInfoType(InExtendedUrlInfoType)`
- L326 _public prototype_ `virtual ~FDashMPD_UrlQueryInfoType() = default;`
- L327 _public function_ `EType GetElementType() const override`
- L330 _public function_ `const FString& GetQueryTemplate() const`
- L331 _public function_ `bool GetUseMPDUrlQuery() const`
- L332 _public function_ `const FString& GetQueryString() const`
- L333 _public function_ `FXLink& GetXLink() override`
- L335 _public function_ `EExtendedUrlInfoType GetExtendedUrlInfoType() const`
- L336 _public function_ `const TArray<FString>& GetIncludeInRequests() const`
- L337 _public function_ `const TArray<FString>& GetHeaderParamSources() const`
- L338 _public function_ `bool GetSameOriginOnly() const`
- L341 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L343 _protected member_ `FString QueryTemplate;`
- L344 _protected member_ `bool bUseMPDUrlQuery = false;`
- L345 _protected member_ `FString QueryString;`
- L346 _protected member_ `FXLink XLink;`
- L348 _protected member_ `EExtendedUrlInfoType ExtendedUrlInfoType;`
- L349 _protected member_ `TArray<FString> IncludeInRequests;`
- L350 _protected member_ `TArray<FString> HeaderParamSources;`
- L351 _protected member_ `bool bSameOriginOnly = false;`

#### enum `Electra::FDashMPD_UrlQueryInfoType::EExtendedUrlInfoType`  
`enum class EExtendedUrlInfoType`  
_L314-318_
- L316 _public enumerator_ `ExtUrlQueryInfo`
- L317 _public enumerator_ `ExtHttpHeaderInfo`

#### class `Electra::FDashMPD_DescriptorType`  
`class FDashMPD_DescriptorType : public IDashMPDElement`  
_L358-398_
- inherits: `IDashMPDElement`
- desc: 5.8.2 - DescriptorType
- L360 _private typedef_ `typedef IDashMPDElement Super;`
- L362 _public function_ `FDashMPD_DescriptorType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L364 _public prototype_ `virtual ~FDashMPD_DescriptorType() = default;`
- L365 _public function_ `EType GetElementType() const override`
- L368 _public function_ `const FString& GetSchemeIdUri() const`
- L369 _public function_ `const FString& GetValue() const`
- L370 _public function_ `const FString& GetID() const`
- L372 _public function_ `const TArray<TSharedPtrTS<IDashMPDElement>>& GetWellKnownDescriptors() const`
- L377 _public function_ `const FString& GetCustomElementAndAttributeJSON() const` — Non-DASH attributes and other XML elements as JSON. Used for <ContentProtection> elements where these elements need to be passed to a CDM system.
- L379 _public function_ `void SetCustomElementAndAttributeJSON(const FString& InCustomElementAndAttributeJSON)`
- L382 _public function_ `void SetSchemeIdUri(const FString& InSchemeIdUri)`
- L383 _public function_ `void SetValue(const FString& InValue)`
- L384 _public function_ `void SetID(const FString& InID)`
- L387 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L388 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L389 _private prototype_ `int32 ReplaceChildElementWithRemoteEntities(TSharedPtrTS<IDashMPDElement> Element, const FDashMPD_RootEntities& NewRootEntities, int64 OldResolveID, int64 NewResolveID) override;`
- L391 _private member_ `TArray<TSharedPtrTS<IDashMPDElement>> WellKnownDescriptors;`
- L393 _private member_ `FString SchemeIdUri;`
- L394 _private member_ `FString Value;`
- L395 _private member_ `FString ID;`
- L397 _private member_ `FString CustomElementAndAttributeJSON;`

#### class `Electra::FDashMPD_ProgramInformationType`  
`class FDashMPD_ProgramInformationType : public IDashMPDElement`  
_L404-429_
- inherits: `IDashMPDElement`
- desc: 5.7.2 - ProgramInformationType
- L406 _private typedef_ `typedef IDashMPDElement Super;`
- L408 _public function_ `FDashMPD_ProgramInformationType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L410 _public prototype_ `virtual ~FDashMPD_ProgramInformationType() = default;`
- L411 _public function_ `EType GetElementType() const override`
- L414 _public function_ `TSharedPtrTS<FDashMPD_OtherType> GetTitle() const`
- L415 _public function_ `TSharedPtrTS<FDashMPD_OtherType> GetSource() const`
- L416 _public function_ `TSharedPtrTS<FDashMPD_OtherType> GetCopyright() const`
- L417 _public function_ `const FString& GetLanguage() const`
- L418 _public function_ `const FString& GetMoreInformationURL() const`
- L421 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L422 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L424 _private member_ `TSharedPtrTS<FDashMPD_OtherType> Title;`
- L425 _private member_ `TSharedPtrTS<FDashMPD_OtherType> Source;`
- L426 _private member_ `TSharedPtrTS<FDashMPD_OtherType> Copyright;`
- L427 _private member_ `FString Language;`
- L428 _private member_ `FString MoreInformationURL;`

#### class `Electra::FDashMPD_EventType`  
`class FDashMPD_EventType : public IDashMPDElement`  
_L435-461_
- inherits: `IDashMPDElement`
- desc: 5.10.2.2 (Table 35) - EventType
- L437 _private typedef_ `typedef IDashMPDElement Super;`
- L439 _public function_ `FDashMPD_EventType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L441 _public prototype_ `virtual ~FDashMPD_EventType() = default;`
- L442 _public function_ `EType GetElementType() const override`
- L445 _public function_ `uint64 GetPresentationTime() const`
- L446 _public function_ `const TMediaOptionalValue<uint64>& GetDuration() const`
- L447 _public function_ `const TMediaOptionalValue<uint64>& GetID() const`
- L448 _public function_ `const FString& GetContentEncoding() const`
- L449 _public function_ `const FString& GetMessageData() const`
- L452 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L456 _private member_ `uint64 PresentationTime = 0;` — Attributes
- L457 _private member_ `TMediaOptionalValue<uint64> Duration;`
- L458 _private member_ `TMediaOptionalValue<uint64> ID;`
- L459 _private member_ `FString ContentEncoding;`
- L460 _private member_ `FString MessageData;`

#### class `Electra::FDashMPD_EventStreamType`  
`class FDashMPD_EventStreamType : public IDashMPDElement`  
_L467-498_
- inherits: `IDashMPDElement`
- desc: 5.10.2.2 (Table 34) - EventStreamType
- L469 _private typedef_ `typedef IDashMPDElement Super;`
- L471 _public function_ `FDashMPD_EventStreamType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L473 _public prototype_ `virtual ~FDashMPD_EventStreamType() = default;`
- L474 _public function_ `EType GetElementType() const override`
- L477 _public function_ `const TArray<TSharedPtrTS<FDashMPD_EventType>>& GetEvents() const`
- L479 _public function_ `const FString& GetSchemeIdUri() const`
- L480 _public function_ `const FString& GetValue() const`
- L481 _public function_ `const TMediaOptionalValue<uint32>& GetTimescale() const`
- L482 _public function_ `const TMediaOptionalValue<uint64>& GetPresentationTimeOffset() const`
- L483 _public function_ `FXLink& GetXLink() override`
- L486 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L487 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L490 _private member_ `TArray<TSharedPtrTS<FDashMPD_EventType>> Events;`
- L493 _private member_ `FString SchemeIdUri;` — Attributes
- L494 _private member_ `FString Value;`
- L495 _private member_ `TMediaOptionalValue<uint32> Timescale;`
- L496 _private member_ `TMediaOptionalValue<uint64> PresentationTimeOffset;`
- L497 _private member_ `FXLink XLink;`

#### class `Electra::FDashMPD_ContentComponentType`  
`class FDashMPD_ContentComponentType : public IDashMPDElement`  
_L504-543_
- inherits: `IDashMPDElement`
- desc: 5.3.4.2 - ContentComponentType
- L506 _private typedef_ `typedef IDashMPDElement Super;`
- L508 _public function_ `FDashMPD_ContentComponentType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L510 _public prototype_ `virtual ~FDashMPD_ContentComponentType() = default;`
- L511 _public function_ `EType GetElementType() const override`
- L514 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetAccessibilities() const`
- L515 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetRoles() const`
- L516 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetRatings() const`
- L517 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetViewpoints() const`
- L519 _public function_ `const FString& GetID_AsStr() const`
- L520 _public function_ `const uint64& GetID() const`
- L521 _public function_ `const FString& GetLanguage() const`
- L522 _public function_ `const FString& GetContentType() const`
- L523 _public function_ `const FTimeFraction& GetPAR() const`
- L524 _public function_ `const FString& GetTag() const`
- L527 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L528 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L531 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Accessibilities;`
- L532 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Roles;`
- L533 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Ratings;`
- L534 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Viewpoints;`
- L537 _private member_ `FString ID_AsStr;` — Attributes
- L538 _private member_ `uint64 ID = 0;`
- L539 _private member_ `FString Language;`
- L540 _private member_ `FString ContentType;`
- L541 _private member_ `FTimeFraction PAR;`
- L542 _private member_ `FString Tag;`

#### class `Electra::FDashMPD_SegmentTimelineType`  
`class FDashMPD_SegmentTimelineType : public IDashMPDElement`  
_L549-594_
- inherits: `IDashMPDElement`
- desc: 5.3.9.6.2 - SegmentTimelineType
- L551 _private typedef_ `typedef IDashMPDElement Super;`
- L578 _public function_ `FDashMPD_SegmentTimelineType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L580 _public prototype_ `virtual ~FDashMPD_SegmentTimelineType() = default;`
- L581 _public function_ `EType GetElementType() const override`
- L584 _public function_ `const TChunkedArray<FSElement, 20480>& GetS_Elements() const`
- L587 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L588 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L589 _protected prototype_ `bool ProcessClose(FManifestParserDASH* Builder, const TCHAR* ElementName) override;`
- L593 _private member_ `TChunkedArray<FSElement, 20480> S_Elements;` — At 40 bytes per 'S' entry we get 512 per chunk.

#### struct `Electra::FDashMPD_SegmentTimelineType::FSElement`  
`struct FSElement`  
_L556-576_
- desc: An <S> element within the SegmentTimelineType
- L558 _public function_ `FSElement()`
- L566 _public member_ `uint64 T = 0;`
- L567 _public member_ `uint64 N = 0;`
- L568 _public member_ `uint64 D = 0;`
- L569 _public member_ `uint64 K = 0;`
- L570 _public member_ `int32 R = 0;`
- L571 _public member_ `uint8 HaveT : 1;`
- L572 _public member_ `uint8 HaveN : 1;`
- L573 _public member_ `uint8 HaveD : 1;`
- L574 _public member_ `uint8 HaveR : 1;`
- L575 _public member_ `uint8 HaveK : 1;`

#### class `Electra::FDashMPD_FailoverContentType`  
`class FDashMPD_FailoverContentType : public IDashMPDElement`  
_L600-641_
- inherits: `IDashMPDElement`
- desc: 5.3.9.7.2 - FailoverContentType
- L602 _private typedef_ `typedef IDashMPDElement Super;`
- L620 _public function_ `FDashMPD_FailoverContentType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L622 _public prototype_ `virtual ~FDashMPD_FailoverContentType() = default;`
- L623 _public function_ `EType GetElementType() const override`
- L626 _public function_ `const TChunkedArray<FFCSElement, 3072>& GetFCS_Elements() const`
- L628 _public function_ `bool GetValid() const`
- L631 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L632 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L633 _protected prototype_ `bool ProcessClose(FManifestParserDASH* Builder, const TCHAR* ElementName) override;`
- L637 _private member_ `TChunkedArray<FFCSElement, 3072> FCS_Elements;` — At 24 bytes per 'FCS' entry we get 128 per chunk.
- L640 _private member_ `bool bValid = true;` — Attributes

#### struct `Electra::FDashMPD_FailoverContentType::FFCSElement`  
`struct FFCSElement`  
_L607-618_
- desc: An <FCS> element within the FailoverContentType
- L609 _public function_ `FFCSElement()`
- L614 _public member_ `uint64 T = 0;`
- L615 _public member_ `uint64 D = 0;`
- L616 _public member_ `uint8 HaveT : 1;`
- L617 _public member_ `uint8 HaveD : 1;`

#### class `Electra::FDashMPD_SegmentBaseType`  
`class FDashMPD_SegmentBaseType : public IDashMPDElement`  
_L647-691_
- inherits: `IDashMPDElement`
- desc: 5.3.9.2.3 - SegmentBaseType
- L649 _private typedef_ `typedef IDashMPDElement Super;`
- L651 _public function_ `FDashMPD_SegmentBaseType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L653 _public prototype_ `virtual ~FDashMPD_SegmentBaseType() = default;`
- L654 _public function_ `EType GetElementType() const override`
- L657 _public function_ `TSharedPtrTS<FDashMPD_URLType> GetInitialization() const`
- L658 _public function_ `TSharedPtrTS<FDashMPD_URLType> GetRepresentationIndex() const`
- L659 _public function_ `TSharedPtrTS<FDashMPD_FailoverContentType> GetFailoverContent() const`
- L661 _public function_ `const TMediaOptionalValue<uint32>& GetTimescale() const`
- L662 _public function_ `const TMediaOptionalValue<uint64>& GetPresentationTimeOffset() const`
- L663 _public function_ `const TMediaOptionalValue<int32>& GetEptDelta() const`
- L665 _public function_ `const TMediaOptionalValue<uint64>& GetPresentationDuration() const`
- L666 _public function_ `const FTimeValue& GetTimeShiftBufferDepth() const`
- L667 _public function_ `const FString& GetIndexRange() const`
- L668 _public function_ `bool GetIndexRangeExact() const`
- L669 _public function_ `const FTimeValue& GetAvailabilityTimeOffset() const`
- L670 _public function_ `const TMediaOptionalValue<bool>& GetAvailabilityTimeComplete() const`
- L673 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L674 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L677 _private member_ `TSharedPtrTS<FDashMPD_URLType> Initialization;`
- L678 _private member_ `TSharedPtrTS<FDashMPD_URLType> RepresentationIndex;`
- L679 _private member_ `TSharedPtrTS<FDashMPD_FailoverContentType> FailoverContent;`
- L682 _private member_ `TMediaOptionalValue<uint32> Timescale;` — Attributes
- L683 _private member_ `TMediaOptionalValue<uint64> PresentationTimeOffset;`
- L684 _private member_ `TMediaOptionalValue<int32> EptDelta;`
- L685 _private member_ `TMediaOptionalValue<uint64> PresentationDuration;`
- L686 _private member_ `FTimeValue TimeShiftBufferDepth;`
- L687 _private member_ `FString IndexRange;`
- L688 _private member_ `bool bIndexRangeExact = false;`
- L689 _private member_ `FTimeValue AvailabilityTimeOffset = FTimeValue::GetZero();`
- L690 _private member_ `TMediaOptionalValue<bool> bAvailabilityTimeComplete;`

#### class `Electra::FDashMPD_MultipleSegmentBaseType`  
`class FDashMPD_MultipleSegmentBaseType : public FDashMPD_SegmentBaseType`  
_L697-726_
- inherits: `FDashMPD_SegmentBaseType`
- desc: 5.3.9.2.2 (Table 16) - MultipleSegmentBaseType
- L699 _private typedef_ `typedef FDashMPD_SegmentBaseType Super;`
- L701 _public function_ `FDashMPD_MultipleSegmentBaseType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L703 _public prototype_ `virtual ~FDashMPD_MultipleSegmentBaseType() = default;`
- L704 _public function_ `EType GetElementType() const override`
- L707 _public function_ `TSharedPtrTS<FDashMPD_SegmentTimelineType> GetSegmentTimeline() const`
- L708 _public function_ `TSharedPtrTS<FDashMPD_URLType> GetBitstreamSwitching() const`
- L710 _public function_ `const TMediaOptionalValue<uint32>& GetDuration() const`
- L711 _public function_ `const TMediaOptionalValue<uint32>& GetStartNumber() const`
- L712 _public function_ `const TMediaOptionalValue<uint32>& GetEndNumber() const`
- L715 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L716 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L719 _private member_ `TSharedPtrTS<FDashMPD_SegmentTimelineType> SegmentTimeline;`
- L720 _private member_ `TSharedPtrTS<FDashMPD_URLType> BitstreamSwitching;`
- L723 _private member_ `TMediaOptionalValue<uint32> Duration;` — Attributes
- L724 _private member_ `TMediaOptionalValue<uint32> StartNumber;`
- L725 _private member_ `TMediaOptionalValue<uint32> EndNumber;`

#### class `Electra::FDashMPD_SegmentListType`  
`class FDashMPD_SegmentListType : public FDashMPD_MultipleSegmentBaseType`  
_L732-755_
- inherits: `FDashMPD_MultipleSegmentBaseType`
- desc: 5.3.9.3.2 - SegmentListType
- L734 _private typedef_ `typedef FDashMPD_MultipleSegmentBaseType Super;`
- L736 _public function_ `FDashMPD_SegmentListType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L738 _public prototype_ `virtual ~FDashMPD_SegmentListType() = default;`
- L739 _public function_ `EType GetElementType() const override`
- L742 _public function_ `const TArray<TSharedPtrTS<FDashMPD_SegmentURLType>>& GetSegmentURLs() const`
- L744 _public function_ `FXLink& GetXLink() override`
- L747 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L748 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L751 _private member_ `TArray<TSharedPtrTS<FDashMPD_SegmentURLType>> SegmentURLs;`
- L754 _private member_ `FXLink XLink;` — Attributes

#### class `Electra::FDashMPD_SegmentTemplateType`  
`class FDashMPD_SegmentTemplateType : public FDashMPD_MultipleSegmentBaseType`  
_L761-787_
- inherits: `FDashMPD_MultipleSegmentBaseType`
- desc: 5.3.9.4.2 - SegmentTemplateType
- L763 _private typedef_ `typedef FDashMPD_MultipleSegmentBaseType Super;`
- L765 _public function_ `FDashMPD_SegmentTemplateType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L767 _public prototype_ `virtual ~FDashMPD_SegmentTemplateType() = default;`
- L768 _public function_ `EType GetElementType() const override`
- L773 _public function_ `const FString& GetMediaTemplate() const` — The following accessors are suffixed 'Template' to differentiate the method from the inherited methods that do not return a template string but an URLType.
- L774 _public function_ `const FString& GetIndexTemplate() const`
- L775 _public function_ `const FString& GetInitializationTemplate() const`
- L776 _public function_ `const FString& GetBitstreamSwitchingTemplate() const`
- L779 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L783 _private member_ `FString Media;` — Attributes
- L784 _private member_ `FString Index;`
- L785 _private member_ `FString Initialization;`
- L786 _private member_ `FString BitstreamSwitching;`

#### class `Electra::FDashMPD_SubsetType`  
`class FDashMPD_SubsetType : public IDashMPDElement`  
_L793-813_
- inherits: `IDashMPDElement`
- desc: 5.3.8.2 - SubsetType
- L795 _private typedef_ `typedef IDashMPDElement Super;`
- L797 _public function_ `FDashMPD_SubsetType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L799 _public prototype_ `virtual ~FDashMPD_SubsetType() = default;`
- L800 _public function_ `EType GetElementType() const override`
- L803 _public function_ `const TArray<uint64>& GetContains() const`
- L804 _public function_ `const FString& GetID() const`
- L807 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L808 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L811 _private member_ `TArray<uint64> Contains;` — Attributes
- L812 _private member_ `FString ID;`

#### class `Electra::FDashMPD_SwitchingType`  
`class FDashMPD_SwitchingType : public IDashMPDElement`  
_L819-839_
- inherits: `IDashMPDElement`
- desc: 5.3.3.4 - SwitchingType
- L821 _private typedef_ `typedef IDashMPDElement Super;`
- L823 _public function_ `FDashMPD_SwitchingType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L825 _public prototype_ `virtual ~FDashMPD_SwitchingType() = default;`
- L826 _public function_ `EType GetElementType() const override`
- L829 _public function_ `uint64 GetInterval() const`
- L830 _public function_ `const FString& GetType() const`
- L833 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L834 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L837 _private member_ `uint64 Interval = 0;` — Attributes
- L838 _private member_ `FString Type;` — "media" or "bitstream"

#### class `Electra::FDashMPD_RandomAccessType`  
`class FDashMPD_RandomAccessType : public IDashMPDElement`  
_L845-869_
- inherits: `IDashMPDElement`
- desc: 5.3.5.5 - RandomAccessType
- L847 _private typedef_ `typedef IDashMPDElement Super;`
- L849 _public function_ `FDashMPD_RandomAccessType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L851 _public prototype_ `virtual ~FDashMPD_RandomAccessType() = default;`
- L852 _public function_ `EType GetElementType() const override`
- L855 _public function_ `uint64 GetInterval() const`
- L856 _public function_ `const FString& GetType() const`
- L857 _public function_ `const FTimeValue& GetMinBufferTime() const`
- L858 _public function_ `const TMediaOptionalValue<uint64>& GetBandwidth() const`
- L861 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L862 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L865 _private member_ `uint64 Interval = 0;` — Attributes
- L866 _private member_ `FString Type = TEXT("clo` — "closed", "open" or "gradual"
- L867 _private member_ `FTimeValue MinBufferTime;`
- L868 _private member_ `TMediaOptionalValue<uint64> Bandwidth;`

#### class `Electra::FDashMPD_LabelType`  
`class FDashMPD_LabelType : public IDashMPDElement`  
_L875-895_
- inherits: `IDashMPDElement`
- desc: 5.3.10.2 - LabelType
- L877 _private typedef_ `typedef IDashMPDElement Super;`
- L879 _public function_ `FDashMPD_LabelType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L881 _public prototype_ `virtual ~FDashMPD_LabelType() = default;`
- L882 _public function_ `EType GetElementType() const override`
- L885 _public function_ `uint64 GetID() const`
- L886 _public function_ `const FString& GetLanguage() const`
- L889 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L890 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L893 _private member_ `uint64 ID = 0;` — Attributes
- L894 _private member_ `FString Language;`

#### class `Electra::FDashMPD_ProducerReferenceTimeType`  
`class FDashMPD_ProducerReferenceTimeType : public IDashMPDElement`  
_L901-933_
- inherits: `IDashMPDElement`
- desc: 5.12.2 - ProducerReferenceTimeType
- L903 _private typedef_ `typedef IDashMPDElement Super;`
- L905 _public function_ `FDashMPD_ProducerReferenceTimeType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L907 _public prototype_ `virtual ~FDashMPD_ProducerReferenceTimeType() = default;`
- L908 _public function_ `EType GetElementType() const override`
- L911 _public function_ `TSharedPtrTS<FDashMPD_DescriptorType> GetUTCTiming() const`
- L913 _public function_ `uint32 GetID() const`
- L914 _public function_ `bool GetInband() const`
- L915 _public function_ `const FString& GetType() const`
- L916 _public function_ `const FString& GetApplicationScheme() const`
- L917 _public function_ `const FString& GetWallclockTime() const`
- L918 _public function_ `uint64 GetPresentationTime() const`
- L921 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L922 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L924 _private member_ `TSharedPtrTS<FDashMPD_DescriptorType> UTCTiming;`
- L927 _private member_ `uint64 ID = 0;` — Attributes
- L928 _private member_ `bool bInband = false;`
- L929 _private member_ `FString Type = TEXT("enc` — one of "encoder", "captured" or "application"
- L930 _private member_ `FString ApplicationScheme;`
- L931 _private member_ `FString WallclockTime;`
- L932 _private member_ `uint64 PresentationTime = 0;`

#### class `Electra::FDashMPD_LeapSecondInformationType`  
`class FDashMPD_LeapSecondInformationType : public IDashMPDElement`  
_L939-960_
- inherits: `IDashMPDElement`
- desc: 5.13.1 - LeapSecondInformationType
- L941 _private typedef_ `typedef IDashMPDElement Super;`
- L943 _public function_ `FDashMPD_LeapSecondInformationType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L945 _public prototype_ `virtual ~FDashMPD_LeapSecondInformationType() = default;`
- L946 _public function_ `EType GetElementType() const override`
- L949 _public function_ `int64 GetAvailabilityStartLeapOffset() const`
- L950 _public function_ `const TMediaOptionalValue<int64>& GetNextAvailabilityStartLeapOffset() const`
- L951 _public function_ `const FTimeValue& GetNextLeapChangeTime() const`
- L954 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L957 _private member_ `int64 AvailabilityStartLeapOffset = 0;` — Attributes
- L958 _private member_ `TMediaOptionalValue<int64> NextAvailabilityStartLeapOffset;`
- L959 _private member_ `FTimeValue NextLeapChangeTime;`

#### class `Electra::FDashMPD_UIntVWithIDType`  
`class FDashMPD_UIntVWithIDType : public IDashMPDElement`  
_L966-993_
- inherits: `IDashMPDElement`
- desc: 5.3.1.3 - UIntVWithIDType
- L968 _private typedef_ `typedef IDashMPDElement Super;`
- L970 _public function_ `FDashMPD_UIntVWithIDType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L972 _public prototype_ `virtual ~FDashMPD_UIntVWithIDType() = default;`
- L973 _public function_ `EType GetElementType() const override`
- L976 _public function_ `const TArray<uint32>& GetElements() const`
- L978 _public function_ `uint64 GetID() const`
- L979 _public function_ `const TArray<FString>& GetProfiles() const`
- L980 _public function_ `const FString& GetContentType() const`
- L983 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L984 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L985 _private prototype_ `bool ProcessClose(FManifestParserDASH* Builder, const TCHAR* ElementName) override;`
- L987 _private member_ `TArray<uint32> Elements;`
- L990 _private member_ `uint64 ID = 0;` — Attributes
- L991 _private member_ `TArray<FString> Profiles;`
- L992 _private member_ `FString ContentType;`

#### class `Electra::FDashMPD_UIntPairsWithIDType`  
`class FDashMPD_UIntPairsWithIDType : public IDashMPDElement`  
_L999-1022_
- inherits: `IDashMPDElement`
- desc: K.4.2.1 - UIntPairsWithIDType
- L1001 _private typedef_ `typedef IDashMPDElement Super;`
- L1003 _public function_ `FDashMPD_UIntPairsWithIDType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1005 _public prototype_ `virtual ~FDashMPD_UIntPairsWithIDType() = default;`
- L1006 _public function_ `EType GetElementType() const override`
- L1009 _public function_ `const TArray<uint32>& GetElements() const`
- L1011 _public function_ `const FString& GetType() const`
- L1014 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1015 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1016 _private prototype_ `bool ProcessClose(FManifestParserDASH* Builder, const TCHAR* ElementName) override;`
- L1018 _private member_ `TArray<uint32> Elements;`
- L1021 _private member_ `FString Type;` — Attributes

#### class `Electra::FDashMPD_OperatingBandwidthType`  
`class FDashMPD_OperatingBandwidthType : public IDashMPDElement`  
_L1028-1052_
- inherits: `IDashMPDElement`
- desc: K.4.2.1 - OperatingBandwidthType
- L1030 _private typedef_ `typedef IDashMPDElement Super;`
- L1032 _public function_ `FDashMPD_OperatingBandwidthType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1034 _public prototype_ `virtual ~FDashMPD_OperatingBandwidthType() = default;`
- L1035 _public function_ `EType GetElementType() const override`
- L1038 _public function_ `const FString& GetMediaType() const`
- L1039 _public function_ `const TMediaOptionalValue<uint64>& GetMin() const`
- L1040 _public function_ `const TMediaOptionalValue<uint64>& GetMax() const`
- L1041 _public function_ `const TMediaOptionalValue<uint64>& GetTarget() const`
- L1044 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1045 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1048 _private member_ `FString MediaType;` — Attributes
- L1049 _private member_ `TMediaOptionalValue<uint64> Min;`
- L1050 _private member_ `TMediaOptionalValue<uint64> Max;`
- L1051 _private member_ `TMediaOptionalValue<uint64> Target;`

#### class `Electra::FDashMPD_OperatingQualityType`  
`class FDashMPD_OperatingQualityType : public IDashMPDElement`  
_L1058-1086_
- inherits: `IDashMPDElement`
- desc: K.4.2.1 - OperatingQualityType
- L1060 _private typedef_ `typedef IDashMPDElement Super;`
- L1062 _public function_ `FDashMPD_OperatingQualityType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1064 _public prototype_ `virtual ~FDashMPD_OperatingQualityType() = default;`
- L1065 _public function_ `EType GetElementType() const override`
- L1068 _public function_ `const FString& GetMediaType() const`
- L1069 _public function_ `const TMediaOptionalValue<uint64>& GetMin() const`
- L1070 _public function_ `const TMediaOptionalValue<uint64>& GetMax() const`
- L1071 _public function_ `const TMediaOptionalValue<uint64>& GetTarget() const`
- L1072 _public function_ `const FString& GetType() const`
- L1073 _public function_ `const TMediaOptionalValue<uint64>& GetMaxDifference() const`
- L1076 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1077 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1080 _private member_ `FString MediaType;` — Attributes
- L1081 _private member_ `TMediaOptionalValue<uint64> Min;`
- L1082 _private member_ `TMediaOptionalValue<uint64> Max;`
- L1083 _private member_ `TMediaOptionalValue<uint64> Target;`
- L1084 _private member_ `FString Type;`
- L1085 _private member_ `TMediaOptionalValue<uint64> MaxDifference;`

#### class `Electra::FDashMPD_PlaybackRateType`  
`class FDashMPD_PlaybackRateType : public IDashMPDElement`  
_L1092-1112_
- inherits: `IDashMPDElement`
- desc: K.4.2.1 - PlaybackRateType
- L1094 _private typedef_ `typedef IDashMPDElement Super;`
- L1096 _public function_ `FDashMPD_PlaybackRateType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1098 _public prototype_ `virtual ~FDashMPD_PlaybackRateType() = default;`
- L1099 _public function_ `EType GetElementType() const override`
- L1102 _public function_ `const FTimeValue& GetMin() const`
- L1103 _public function_ `const FTimeValue& GetMax() const`
- L1106 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1107 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1110 _private member_ `FTimeValue Min;` — Attributes
- L1111 _private member_ `FTimeValue Max;`

#### class `Electra::FDashMPD_LatencyType`  
`class FDashMPD_LatencyType : public IDashMPDElement`  
_L1118-1146_
- inherits: `IDashMPDElement`
- desc: K.4.2.1 - LatencyType
- L1120 _private typedef_ `typedef IDashMPDElement Super;`
- L1122 _public function_ `FDashMPD_LatencyType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1124 _public prototype_ `virtual ~FDashMPD_LatencyType() = default;`
- L1125 _public function_ `EType GetElementType() const override`
- L1128 _public function_ `const TArray<TSharedPtrTS<FDashMPD_UIntPairsWithIDType>>& GetQualityLatencies() const`
- L1130 _public function_ `const TMediaOptionalValue<uint64>& GetReferenceID() const`
- L1131 _public function_ `const TMediaOptionalValue<uint64>& GetTarget() const`
- L1132 _public function_ `const TMediaOptionalValue<uint64>& GetMax() const`
- L1133 _public function_ `const TMediaOptionalValue<uint64>& GetMin() const`
- L1136 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1137 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1139 _private member_ `TArray<TSharedPtrTS<FDashMPD_UIntPairsWithIDType>> QualityLatencies;`
- L1142 _private member_ `TMediaOptionalValue<uint64> ReferenceID;` — Attributes
- L1143 _private member_ `TMediaOptionalValue<uint64> Target;`
- L1144 _private member_ `TMediaOptionalValue<uint64> Max;`
- L1145 _private member_ `TMediaOptionalValue<uint64> Min;`

#### class `Electra::FDashMPD_ContentPopularityRateType`  
`class FDashMPD_ContentPopularityRateType : public IDashMPDElement`  
_L1152-1204_
- inherits: `IDashMPDElement`
- desc: 5.4.12 - ContentPopularityRateType
- L1154 _private typedef_ `typedef IDashMPDElement Super;`
- L1183 _public function_ `FDashMPD_ContentPopularityRateType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1185 _public prototype_ `virtual ~FDashMPD_ContentPopularityRateType() = default;`
- L1186 _public function_ `EType GetElementType() const override`
- L1189 _public function_ `const TArray<TSharedPtrTS<FPRElement>>& GetPR_Elements() const`
- L1191 _public function_ `const FString& GetSource() const`
- L1192 _public function_ `const FString& GetSource_Description() const`
- L1195 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1196 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1199 _private member_ `TArray<TSharedPtrTS<FPRElement>> PR_Elements;`
- L1202 _private member_ `FString Source;` — Attributes
- L1203 _private member_ `FString Source_Description;`

#### class `Electra::FDashMPD_ContentPopularityRateType::FPRElement`  
`class FPRElement : public IDashMPDElement`  
_L1159-1181_
- inherits: `IDashMPDElement`
- desc: A <PR> element
- L1161 _private typedef_ `typedef IDashMPDElement Super;`
- L1163 _public function_ `FPRElement(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1165 _public prototype_ `virtual ~FPRElement() = default;`
- L1166 _public function_ `EType GetElementType() const override`
- L1169 _public function_ `uint64 GetPopularityRate() const`
- L1170 _public function_ `const TMediaOptionalValue<uint64>& GetStart() const`
- L1171 _public function_ `int32 GetR() const`
- L1174 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1178 _private member_ `uint64 PopularityRate = 0;` — Attributes
- L1179 _private member_ `TMediaOptionalValue<uint64> Start;`
- L1180 _private member_ `int32 R = 0;`

#### class `Electra::FDashMPD_ContentSteeringType`  
`class FDashMPD_ContentSteeringType : public IDashMPDElement`  
_L1211-1235_
- inherits: `IDashMPDElement`
- desc: DASH-IF CTS 00XX V0.9.0 / ETSI TS 103 998 V1.1.1 - ContentSteeringType
- L1213 _private typedef_ `typedef IDashMPDElement Super;`
- L1215 _public function_ `FDashMPD_ContentSteeringType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1217 _public prototype_ `virtual ~FDashMPD_ContentSteeringType() = default;`
- L1218 _public function_ `EType GetElementType() const override`
- L1221 _public function_ `const FString& GetContentSteeringServer() const`
- L1222 _public function_ `const FString& GetProxyServerURL() const`
- L1223 _public function_ `const FString& GetDefaultServiceLocation() const`
- L1224 _public function_ `bool QueryBeforeStart() const`
- L1225 _public function_ `bool ClientRequirement() const`
- L1228 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1231 _private member_ `FString ProxyServerURL;` — Attributes
- L1232 _private member_ `FString DefaultServiceLocation;`
- L1233 _private member_ `bool bQueryBeforeStart = false;`
- L1234 _private member_ `bool bClientRequirement = false;`

#### class `Electra::FDashMPD_CMCDParametersType`  
`class FDashMPD_CMCDParametersType : public IDashMPDElement`  
_L1242-1274_
- inherits: `IDashMPDElement`
- desc: DASH-IF proposed CMCD reporting type
- L1244 _private typedef_ `typedef IDashMPDElement Super;`
- L1246 _public function_ `FDashMPD_CMCDParametersType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1253 _public prototype_ `virtual ~FDashMPD_CMCDParametersType() = default;`
- L1254 _public function_ `EType GetElementType() const override`
- L1257 _public function_ `int32 GetVersion() const`
- L1258 _public function_ `const TArray<FString>& GetIncludeInRequests() const`
- L1259 _public function_ `const TArray<FString>& GetKeys() const`
- L1260 _public function_ `const FString& GetMode() const`
- L1261 _public function_ `const FString& GetContentID() const`
- L1262 _public function_ `const FString& GetSessionID() const`
- L1263 _public function_ `const FString& GetSchemeIdUri() const`
- L1265 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1267 _private member_ `TArray<FString> Keys;` — Attributes
- L1268 _private member_ `TArray<FString> IncludeInRequests;`
- L1269 _private member_ `FString Mode;`
- L1270 _private member_ `FString SchemeIdUri;`
- L1271 _private member_ `FString ContentID;`
- L1272 _private member_ `FString SessionID;`
- L1273 _private member_ `int32 Version = 1;`

#### class `Electra::FDashMPD_ClientDataReportingType`  
`class FDashMPD_ClientDataReportingType : public IDashMPDElement`  
_L1276-1297_
- inherits: `IDashMPDElement`
- L1278 _private typedef_ `typedef IDashMPDElement Super;`
- L1280 _public function_ `FDashMPD_ClientDataReportingType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1282 _public prototype_ `virtual ~FDashMPD_ClientDataReportingType() = default;`
- L1283 _public function_ `EType GetElementType() const override`
- L1286 _public function_ `const TArray<FString>& GetServiceLocations() const`
- L1287 _public function_ `const TArray<FString>& GetAdaptationSets() const`
- L1289 _public function_ `const TArray<TSharedPtrTS<FDashMPD_CMCDParametersType>>& GetCMCDParameters_Elements() const`
- L1291 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1292 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1293 _private member_ `TArray<TSharedPtrTS<FDashMPD_CMCDParametersType>> CMCDParameters_Elements;`
- L1295 _private member_ `TArray<FString> ServiceLocations;` — Attributes
- L1296 _private member_ `TArray<FString> AdaptationSets;`

#### class `Electra::FDashMPD_ServiceDescriptionType`  
`class FDashMPD_ServiceDescriptionType : public IDashMPDElement`  
_L1304-1339_
- inherits: `IDashMPDElement`
- desc: K.4.2.1 - ServiceDescriptionType
- L1306 _private typedef_ `typedef IDashMPDElement Super;`
- L1308 _public function_ `FDashMPD_ServiceDescriptionType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1310 _public prototype_ `virtual ~FDashMPD_ServiceDescriptionType() = default;`
- L1311 _public function_ `EType GetElementType() const override`
- L1314 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetScopes() const`
- L1315 _public function_ `const TArray<TSharedPtrTS<FDashMPD_LatencyType>>& GetLatencies() const`
- L1316 _public function_ `const TArray<TSharedPtrTS<FDashMPD_PlaybackRateType>>& GetPlaybackRates() const`
- L1317 _public function_ `const TArray<TSharedPtrTS<FDashMPD_OperatingQualityType>>& GetOperatingQualities() const`
- L1318 _public function_ `const TArray<TSharedPtrTS<FDashMPD_OperatingBandwidthType>>& GetOperatingBandwidths() const`
- L1319 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ContentSteeringType>>& GetContentSteerings() const`
- L1320 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ClientDataReportingType>>& GetClientDataReportings() const`
- L1322 _public function_ `uint32 GetID() const`
- L1325 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1326 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1329 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Scopes;`
- L1330 _private member_ `TArray<TSharedPtrTS<FDashMPD_LatencyType>> Latencies;`
- L1331 _private member_ `TArray<TSharedPtrTS<FDashMPD_PlaybackRateType>> PlaybackRates;`
- L1332 _private member_ `TArray<TSharedPtrTS<FDashMPD_OperatingQualityType>> OperatingQualities;`
- L1333 _private member_ `TArray<TSharedPtrTS<FDashMPD_OperatingBandwidthType>> OperatingBandwidths;`
- L1334 _private member_ `TArray<TSharedPtrTS<FDashMPD_ContentSteeringType>> ContentSteerings;`
- L1335 _private member_ `TArray<TSharedPtrTS<FDashMPD_ClientDataReportingType>> ClientDataReportings;`
- L1338 _private member_ `uint64 ID = 0;` — Attributes

#### class `Electra::FDashMPD_ResyncType`  
`class FDashMPD_ResyncType : public IDashMPDElement`  
_L1345-1375_
- inherits: `IDashMPDElement`
- desc: 5.3.12 - ResyncType
- L1347 _private typedef_ `typedef IDashMPDElement Super;`
- L1349 _public function_ `FDashMPD_ResyncType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1351 _public prototype_ `virtual ~FDashMPD_ResyncType() = default;`
- L1352 _public function_ `EType GetElementType() const override`
- L1355 _public function_ `int32 GetType() const`
- L1356 _public function_ `TMediaOptionalValue<uint32> GetdT() const`
- L1357 _public function_ `TMediaOptionalValue<double> GetdIMax() const`
- L1358 _public function_ `double GetdIMin() const`
- L1359 _public function_ `bool GetMarker() const`
- L1360 _public function_ `bool GetRangeAccess() const`
- L1361 _public function_ `const FString& GetIndex() const`
- L1364 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1365 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1368 _private member_ `int32 Type = 0;` — Attributes
- L1369 _private member_ `TMediaOptionalValue<uint32> dT;`
- L1370 _private member_ `TMediaOptionalValue<double> dIMax;`
- L1371 _private member_ `double dIMin = 0.0;`
- L1372 _private member_ `bool bMarker = false;`
- L1373 _private member_ `bool bRangeAccess = false;`
- L1374 _private member_ `FString Index;`

#### class `Electra::FDashMPD_RepresentationBaseType`  
`class FDashMPD_RepresentationBaseType : public IDashMPDElement`  
_L1381-1457_
- inherits: `IDashMPDElement`
- desc: 5.3.7.2 - RepresentationBaseType
- L1383 _private typedef_ `typedef IDashMPDElement Super;`
- L1385 _public function_ `FDashMPD_RepresentationBaseType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1387 _public prototype_ `virtual ~FDashMPD_RepresentationBaseType() = default;`
- L1389 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetFramePackings() const`
- L1390 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetAudioChannelConfigurations() const`
- L1391 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetContentProtections() const`
- L1392 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetEssentialProperties() const override`
- L1393 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetSupplementalProperties() const override`
- L1394 _public function_ `const TArray<TSharedPtrTS<FDashMPD_EventStreamType>>& GetInbandEventStreams() const`
- L1395 _public function_ `const TArray<TSharedPtrTS<FDashMPD_SwitchingType>>& GetSwitchings() const`
- L1396 _public function_ `const TArray<TSharedPtrTS<FDashMPD_RandomAccessType>>& GetRandomAccesses() const`
- L1397 _public function_ `const TArray<TSharedPtrTS<FDashMPD_LabelType>>& GetGroupLabels() const`
- L1398 _public function_ `const TArray<TSharedPtrTS<FDashMPD_LabelType>>& GetLabels() const`
- L1399 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ProducerReferenceTimeType>>& GetProducerReferenceTimes() const`
- L1400 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ContentPopularityRateType>>& GetContentPopularityRates() const`
- L1401 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ResyncType>>& GetResyncs() const`
- L1403 _public function_ `const TArray<FString>& GetProfiles() const`
- L1404 _public function_ `const TMediaOptionalValue<uint64>& GetWidth() const`
- L1405 _public function_ `const TMediaOptionalValue<uint64>& GetHeight() const`
- L1406 _public function_ `const FTimeFraction& GetSAR() const`
- L1407 _public function_ `const FTimeFraction& GetFrameRate() const`
- L1408 _public function_ `const TArray<uint64>& GetAudioSamplingRate() const`
- L1409 _public function_ `const FString& GetMimeType() const`
- L1410 _public function_ `const TArray<FString>& GetSegmentProfiles() const`
- L1411 _public function_ `const TArray<FString>& GetCodecs() const`
- L1412 _public function_ `const FTimeValue& GetMaximumSAPPeriod() const`
- L1413 _public function_ `int64 GetStartWithSAP() const`
- L1414 _public function_ `const FTimeValue& GetMaxPlayoutRate() const`
- L1415 _public function_ `const TMediaOptionalValue<bool>& GetCodingDependency() const`
- L1416 _public function_ `const FString& GetScanType() const`
- L1417 _public function_ `uint64 GetSelectionPriority() const`
- L1418 _public function_ `const FString& GetTag() const`
- L1421 _protected prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1422 _protected prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1423 _protected prototype_ `int32 ReplaceChildElementWithRemoteEntities(TSharedPtrTS<IDashMPDElement> Element, const FDashMPD_RootEntities& NewRootEntities, int64 OldResolveID, int64 NewResolveID) override;`
- L1426 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> FramePackings;`
- L1427 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> AudioChannelConfigurations;`
- L1428 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> ContentProtections;`
- L1429 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> EssentialProperties;`
- L1430 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> SupplementalProperties;`
- L1431 _private member_ `TArray<TSharedPtrTS<FDashMPD_EventStreamType>> InbandEventStreams;`
- L1432 _private member_ `TArray<TSharedPtrTS<FDashMPD_SwitchingType>> Switchings;`
- L1433 _private member_ `TArray<TSharedPtrTS<FDashMPD_RandomAccessType>> RandomAccesses;`
- L1434 _private member_ `TArray<TSharedPtrTS<FDashMPD_LabelType>> GroupLabels;`
- L1435 _private member_ `TArray<TSharedPtrTS<FDashMPD_LabelType>> Labels;`
- L1436 _private member_ `TArray<TSharedPtrTS<FDashMPD_ProducerReferenceTimeType>> ProducerReferenceTimes;`
- L1437 _private member_ `TArray<TSharedPtrTS<FDashMPD_ContentPopularityRateType>> ContentPopularityRates;`
- L1438 _private member_ `TArray<TSharedPtrTS<FDashMPD_ResyncType>> Resyncs;`
- L1441 _private member_ `TArray<FString> Profiles;` — Attributes
- L1442 _private member_ `TMediaOptionalValue<uint64> Width;`
- L1443 _private member_ `TMediaOptionalValue<uint64> Height;`
- L1444 _private member_ `FTimeFraction SAR;`
- L1445 _private member_ `FTimeFraction FrameRate;`
- L1446 _private member_ `TArray<uint64> AudioSamplingRate;`
- L1447 _private member_ `FString MimeType;`
- L1448 _private member_ `TArray<FString> SegmentProfiles;`
- L1449 _private member_ `TArray<FString> Codecs;`
- L1450 _private member_ `FTimeValue MaximumSAPPeriod;`
- L1451 _private member_ `int64 StartWithSAP = 0;`
- L1452 _private member_ `FTimeValue MaxPlayoutRate;`
- L1453 _private member_ `TMediaOptionalValue<bool> bCodingDependency;`
- L1454 _private member_ `FString ScanType;`
- L1455 _private member_ `uint64 SelectionPriority = 1;`
- L1456 _private member_ `FString Tag;`

#### class `Electra::FDashMPD_SubRepresentationType`  
`class FDashMPD_SubRepresentationType : public FDashMPD_RepresentationBaseType`  
_L1463-1481_
- inherits: `FDashMPD_RepresentationBaseType`
- desc: 5.3.6.2 - SubRepresentationType
- L1465 _private typedef_ `typedef FDashMPD_RepresentationBaseType Super;`
- L1467 _public function_ `FDashMPD_SubRepresentationType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1469 _public prototype_ `virtual ~FDashMPD_SubRepresentationType() = default;`
- L1470 _public function_ `EType GetElementType() const override`
- L1474 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1477 _private member_ `TMediaOptionalValue<uint64> Level;` — Attributes
- L1478 _private member_ `TArray<uint64> DependencyLevels;`
- L1479 _private member_ `TMediaOptionalValue<uint64> Bandwidth;`
- L1480 _private member_ `TArray<FString> ContentComponents;`

#### class `Electra::FDashMPD_InitializationSetType`  
`class FDashMPD_InitializationSetType : public FDashMPD_RepresentationBaseType`  
_L1487-1532_
- inherits: `FDashMPD_RepresentationBaseType`
- desc: 5.3.12.2 - InitializationSetType
- L1489 _private typedef_ `typedef FDashMPD_RepresentationBaseType Super;`
- L1491 _public function_ `FDashMPD_InitializationSetType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1493 _public prototype_ `virtual ~FDashMPD_InitializationSetType() = default;`
- L1494 _public function_ `EType GetElementType() const override`
- L1497 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetAccessibilities() const`
- L1498 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetRoles() const`
- L1499 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetRatings() const`
- L1500 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetViewpoints() const`
- L1503 _public function_ `uint64 GetID() const` — Attributes
- L1504 _public function_ `bool GetInAllPeriods() const`
- L1505 _public function_ `const FString& GetContentType() const`
- L1506 _public function_ `const FTimeFraction& GetPAR() const`
- L1507 _public function_ `const TMediaOptionalValue<uint64>& GetMaxWidth() const`
- L1508 _public function_ `const TMediaOptionalValue<uint64>& GetMaxHeight() const`
- L1509 _public function_ `const FTimeFraction& GetMaxFrameRate() const`
- L1510 _public function_ `const FString& GetInitialization() const`
- L1511 _public function_ `FXLink& GetXLink() override`
- L1514 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1515 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1517 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Accessibilities;`
- L1518 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Roles;`
- L1519 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Ratings;`
- L1520 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Viewpoints;`
- L1523 _private member_ `uint64 ID = 0;` — Attributes
- L1524 _private member_ `bool bInAllPeriods = true;`
- L1525 _private member_ `FString ContentType;`
- L1526 _private member_ `FTimeFraction PAR;`
- L1527 _private member_ `TMediaOptionalValue<uint64> MaxWidth;`
- L1528 _private member_ `TMediaOptionalValue<uint64> MaxHeight;`
- L1529 _private member_ `FTimeFraction MaxFrameRate;`
- L1530 _private member_ `FString Initialization;`
- L1531 _private member_ `FXLink XLink;`

#### class `Electra::FDashMPD_PreselectionType`  
`class FDashMPD_PreselectionType : public FDashMPD_RepresentationBaseType`  
_L1538-1572_
- inherits: `FDashMPD_RepresentationBaseType`
- desc: 5.3.11.3 - PreselectionType
- L1540 _private typedef_ `typedef FDashMPD_RepresentationBaseType Super;`
- L1542 _public function_ `FDashMPD_PreselectionType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1544 _public prototype_ `virtual ~FDashMPD_PreselectionType() = default;`
- L1545 _public function_ `EType GetElementType() const override`
- L1548 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetAccessibilities() const`
- L1549 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetRoles() const`
- L1550 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetRatings() const`
- L1551 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetViewpoints() const`
- L1553 _public function_ `const FString& GetI() const`
- L1554 _public function_ `const TArray<FString>& GetPreselectionComponents() const`
- L1555 _public function_ `const FString& GetLanguage() const`
- L1556 _public function_ `const FString& GetOrder() const`
- L1559 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1560 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1562 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Accessibilities;`
- L1563 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Roles;`
- L1564 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Ratings;`
- L1565 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Viewpoints;`
- L1568 _private member_ `FString ID = TEXT("1")` — Attributes
- L1569 _private member_ `TArray<FString> PreselectionComponents;`
- L1570 _private member_ `FString Language;`
- L1571 _private member_ `FString Order = TEXT("und`

#### class `Electra::FDashMPD_RepresentationType`  
`class FDashMPD_RepresentationType : public FDashMPD_RepresentationBaseType`  
_L1578-1622_
- inherits: `FDashMPD_RepresentationBaseType`
- desc: 5.3.5.2 - RepresentationType
- L1580 _private typedef_ `typedef FDashMPD_RepresentationBaseType Super;`
- L1582 _public function_ `FDashMPD_RepresentationType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1584 _public prototype_ `virtual ~FDashMPD_RepresentationType() = default;`
- L1585 _public function_ `EType GetElementType() const override`
- L1588 _public function_ `const TArray<TSharedPtrTS<FDashMPD_BaseURLType>>& GetBaseURLs() const override`
- L1589 _public function_ `const TArray<TSharedPtrTS<FDashMPD_SubRepresentationType>>& GetSubRepresentations() const`
- L1590 _public function_ `TSharedPtrTS<FDashMPD_SegmentBaseType> GetSegmentBase() const`
- L1591 _public function_ `TSharedPtrTS<FDashMPD_SegmentListType> GetSegmentList() const`
- L1592 _public function_ `TSharedPtrTS<FDashMPD_SegmentTemplateType> GetSegmentTemplate() const`
- L1595 _public function_ `const FString& GetID() const` — Attributes
- L1596 _public function_ `uint64 GetBandwidth() const`
- L1597 _public function_ `const TMediaOptionalValue<uint64>& GetQualityRanking() const`
- L1598 _public function_ `const TArray<FString>& GetDependencyIDs() const`
- L1599 _public function_ `const TArray<FString>& GetAssociationIDs() const`
- L1600 _public function_ `const TArray<FString>& GetAssociationTypes() const`
- L1601 _public function_ `const TArray<FString>& GetMediaStreamStructureIDs() const`
- L1604 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1605 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1606 _private prototype_ `int32 ReplaceChildElementWithRemoteEntities(TSharedPtrTS<IDashMPDElement> Element, const FDashMPD_RootEntities& NewRootEntities, int64 OldResolveID, int64 NewResolveID) override;`
- L1608 _private member_ `TArray<TSharedPtrTS<FDashMPD_BaseURLType>> BaseURLs;`
- L1609 _private member_ `TArray<TSharedPtrTS<FDashMPD_SubRepresentationType>> SubRepresentations;`
- L1610 _private member_ `TSharedPtrTS<FDashMPD_SegmentBaseType> SegmentBase;`
- L1611 _private member_ `TSharedPtrTS<FDashMPD_SegmentListType> SegmentList;`
- L1612 _private member_ `TSharedPtrTS<FDashMPD_SegmentTemplateType> SegmentTemplate;`
- L1615 _private member_ `FString ID;` — Attributes
- L1616 _private member_ `uint64 Bandwidth = 0;`
- L1617 _private member_ `TMediaOptionalValue<uint64> QualityRanking;`
- L1618 _private member_ `TArray<FString> DependencyIDs;`
- L1619 _private member_ `TArray<FString> AssociationIDs;`
- L1620 _private member_ `TArray<FString> AssociationTypes;`
- L1621 _private member_ `TArray<FString> MediaStreamStructureIDs;`

#### class `Electra::FDashMPD_AdaptationSetType`  
`class FDashMPD_AdaptationSetType : public FDashMPD_RepresentationBaseType`  
_L1628-1708_
- inherits: `FDashMPD_RepresentationBaseType`
- desc: 5.3.3.2 - AdaptationSetType
- L1630 _private typedef_ `typedef FDashMPD_RepresentationBaseType Super;`
- L1632 _public function_ `FDashMPD_AdaptationSetType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1634 _public prototype_ `virtual ~FDashMPD_AdaptationSetType() = default;`
- L1635 _public function_ `EType GetElementType() const override`
- L1639 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetAccessibilities() const`
- L1640 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetRoles() const`
- L1641 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetRatings() const`
- L1642 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetViewpoints() const`
- L1643 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ContentComponentType>>& GetContentComponents() const`
- L1644 _public function_ `const TArray<TSharedPtrTS<FDashMPD_BaseURLType>>& GetBaseURLs() const override`
- L1645 _public function_ `TSharedPtrTS<FDashMPD_SegmentBaseType> GetSegmentBase() const`
- L1646 _public function_ `TSharedPtrTS<FDashMPD_SegmentListType> GetSegmentList() const`
- L1647 _public function_ `TSharedPtrTS<FDashMPD_SegmentTemplateType> GetSegmentTemplate() const`
- L1648 _public function_ `const TArray<TSharedPtrTS<FDashMPD_RepresentationType>>& GetRepresentations() const`
- L1650 _public function_ `const FString& GetID_AsStr() const`
- L1651 _public function_ `uint64 GetID() const`
- L1652 _public function_ `const TMediaOptionalValue<uint64>& GetGroup() const`
- L1653 _public function_ `const FString& GetLanguage() const`
- L1654 _public function_ `const FString& GetContentType() const`
- L1655 _public function_ `const FTimeFraction& GetPAR() const`
- L1656 _public function_ `const TMediaOptionalValue<uint64>& GetMinBandwidth() const`
- L1657 _public function_ `const TMediaOptionalValue<uint64>& GetMaxBandwidth() const`
- L1658 _public function_ `const TMediaOptionalValue<uint64>& GetMinWidth() const`
- L1659 _public function_ `const TMediaOptionalValue<uint64>& GetMaxWidth() const`
- L1660 _public function_ `const TMediaOptionalValue<uint64>& GetMinHeight() const`
- L1661 _public function_ `const TMediaOptionalValue<uint64>& GetMaxHeight() const`
- L1662 _public function_ `const FTimeFraction& GetMinFrameRate() const`
- L1663 _public function_ `const FTimeFraction& GetMaxFrameRate() const`
- L1664 _public function_ `const FBoolUInt64& GetSegmentAlignment() const`
- L1665 _public function_ `const FBoolUInt64& GetSubsegmentAlignment() const`
- L1666 _public function_ `int64 GetSubsegmentStartsWithSAP() const`
- L1667 _public function_ `const TMediaOptionalValue<bool>& GetBitstreamSwitching() const`
- L1668 _public function_ `const TArray<uint64>& GetInitializationSetRefs() const`
- L1669 _public function_ `FXLink& GetXLink() override`
- L1672 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1673 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1674 _private prototype_ `int32 ReplaceChildElementWithRemoteEntities(TSharedPtrTS<IDashMPDElement> Element, const FDashMPD_RootEntities& NewRootEntities, int64 OldResolveID, int64 NewResolveID) override;`
- L1676 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Accessibilities;`
- L1677 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Roles;`
- L1678 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Ratings;`
- L1679 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> Viewpoints;`
- L1680 _private member_ `TArray<TSharedPtrTS<FDashMPD_ContentComponentType>> ContentComponents;`
- L1681 _private member_ `TArray<TSharedPtrTS<FDashMPD_BaseURLType>> BaseURLs;`
- L1682 _private member_ `TSharedPtrTS<FDashMPD_SegmentBaseType> SegmentBase;`
- L1683 _private member_ `TSharedPtrTS<FDashMPD_SegmentListType> SegmentList;`
- L1684 _private member_ `TSharedPtrTS<FDashMPD_SegmentTemplateType> SegmentTemplate;`
- L1685 _private member_ `TArray<TSharedPtrTS<FDashMPD_RepresentationType>> Representations;`
- L1688 _private member_ `FString ID_AsStr;` — Attributes
- L1689 _private member_ `uint64 ID = 0;`
- L1690 _private member_ `TMediaOptionalValue<uint64> Group;`
- L1691 _private member_ `FString Language;`
- L1692 _private member_ `FString ContentType;` — One of: "text", "image", "audio", "video", "application" and "font"
- L1693 _private member_ `FTimeFraction PAR;`
- L1694 _private member_ `TMediaOptionalValue<uint64> MinBandwidth;`
- L1695 _private member_ `TMediaOptionalValue<uint64> MaxBandwidth;`
- L1696 _private member_ `TMediaOptionalValue<uint64> MinWidth;`
- L1697 _private member_ `TMediaOptionalValue<uint64> MaxWidth;`
- L1698 _private member_ `TMediaOptionalValue<uint64> MinHeight;`
- L1699 _private member_ `TMediaOptionalValue<uint64> MaxHeight;`
- L1700 _private member_ `FTimeFraction MinFrameRate;`
- L1701 _private member_ `FTimeFraction MaxFrameRate;`
- L1702 _private member_ `FBoolUInt64 bSegmentAlignment;`
- L1703 _private member_ `FBoolUInt64 bSubsegmentAlignment;`
- L1704 _private member_ `int64 SubsegmentStartsWithSAP = 0;`
- L1705 _private member_ `TMediaOptionalValue<bool> bBitstreamSwitching;`
- L1706 _private member_ `TArray<uint64> InitializationSetRefs;`
- L1707 _private member_ `FXLink XLink;`

#### class `Electra::FDashMPD_PeriodType`  
`class FDashMPD_PeriodType : public IDashMPDElement`  
_L1714-1778_
- inherits: `IDashMPDElement`
- desc: 5.3.2.2 - PeriodType
- L1716 _private typedef_ `typedef IDashMPDElement Super;`
- L1718 _public function_ `FDashMPD_PeriodType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1720 _public prototype_ `virtual ~FDashMPD_PeriodType() = default;`
- L1721 _public function_ `EType GetElementType() const override`
- L1724 _public function_ `const TArray<TSharedPtrTS<FDashMPD_BaseURLType>>& GetBaseURLs() const override`
- L1725 _public function_ `TSharedPtrTS<FDashMPD_SegmentBaseType> GetSegmentBase() const`
- L1726 _public function_ `TSharedPtrTS<FDashMPD_SegmentListType> GetSegmentList() const`
- L1727 _public function_ `TSharedPtrTS<FDashMPD_SegmentTemplateType> GetSegmentTemplate() const`
- L1728 _public function_ `TSharedPtrTS<FDashMPD_DescriptorType> GetAssetIdentifier() const`
- L1729 _public function_ `const TArray<TSharedPtrTS<FDashMPD_EventStreamType>>& GetEventStreams() const`
- L1730 _public function_ `const TArray<TSharedPtrTS<FDashMPD_AdaptationSetType>>& GetAdaptationSets() const`
- L1731 _public function_ `const TArray<TSharedPtrTS<FDashMPD_SubsetType>>& GetSubsets() const`
- L1732 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetSupplementalProperties() const override`
- L1733 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ServiceDescriptionType>>& GetServiceDescriptions() const`
- L1734 _public function_ `const TArray<TSharedPtrTS<FDashMPD_AdaptationSetType>>& GetEmptyAdaptationSets() const`
- L1735 _public function_ `const TArray<TSharedPtrTS<FDashMPD_LabelType>>& GetGroupLabels() const`
- L1736 _public function_ `const TArray<TSharedPtrTS<FDashMPD_PreselectionType>>& GetPreselections() const`
- L1738 _public function_ `const FString& GetID() const`
- L1739 _public function_ `const FTimeValue& GetStart() const`
- L1740 _public function_ `const FTimeValue& GetDuration() const`
- L1741 _public function_ `const TMediaOptionalValue<bool>& GetBitstreamSwitching() const`
- L1742 _public function_ `FXLink& GetXLink() override`
- L1745 _public function_ `void SetDuration(const FTimeValue& NewDuration)` — Methods to manipulate the presentation type.
- L1751 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1752 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1753 _private prototype_ `int32 ReplaceChildElementWithRemoteEntities(TSharedPtrTS<IDashMPDElement> Element, const FDashMPD_RootEntities& NewRootEntities, int64 OldResolveID, int64 NewResolveID) override;`
- L1755 _private member_ `TArray<TSharedPtrTS<FDashMPD_BaseURLType>> BaseURLs;`
- L1757 _private member_ `TSharedPtrTS<FDashMPD_SegmentBaseType> SegmentBase;`
- L1758 _private member_ `TSharedPtrTS<FDashMPD_SegmentListType> SegmentList;`
- L1759 _private member_ `TSharedPtrTS<FDashMPD_SegmentTemplateType> SegmentTemplate;`
- L1761 _private member_ `TSharedPtrTS<FDashMPD_DescriptorType> AssetIdentifier;`
- L1762 _private member_ `TArray<TSharedPtrTS<FDashMPD_EventStreamType>> EventStreams;`
- L1763 _private member_ `TArray<TSharedPtrTS<FDashMPD_AdaptationSetType>> AdaptationSets;`
- L1764 _private member_ `TArray<TSharedPtrTS<FDashMPD_SubsetType>> Subsets;`
- L1765 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> SupplementalProperties;`
- L1767 _private member_ `TArray<TSharedPtrTS<FDashMPD_ServiceDescriptionType>> ServiceDescriptions;`
- L1768 _private member_ `TArray<TSharedPtrTS<FDashMPD_AdaptationSetType>> EmptyAdaptationSets;`
- L1769 _private member_ `TArray<TSharedPtrTS<FDashMPD_LabelType>> GroupLabels;`
- L1770 _private member_ `TArray<TSharedPtrTS<FDashMPD_PreselectionType>> Preselections;`
- L1773 _private member_ `FString ID;` — Attributes
- L1774 _private member_ `FTimeValue Start;`
- L1775 _private member_ `FTimeValue Duration;`
- L1776 _private member_ `TMediaOptionalValue<bool> bBitstreamSwitching;`
- L1777 _private member_ `FXLink XLink;`

#### class `Electra::FDashMPD_MPDType`  
`class FDashMPD_MPDType : public IDashMPDElement`  
_L1784-1917_
- inherits: `IDashMPDElement`
- desc: 5.3.1.2 - MPDType
- L1786 _private typedef_ `typedef IDashMPDElement Super;`
- L1788 _public function_ `FDashMPD_MPDType(const TCHAR* Name, const TCHAR* Data) : Super(Name, Data)`
- L1790 _public prototype_ `virtual ~FDashMPD_MPDType() = default;`
- L1791 _public function_ `EType GetElementType() const override`
- L1794 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ProgramInformationType>>& GetProgramInformations() const`
- L1795 _public function_ `const TArray<TSharedPtrTS<FDashMPD_BaseURLType>>& GetBaseURLs() const override`
- L1796 _public function_ `const TArray<TSharedPtrTS<FDashMPD_OtherType>>& GetLocations() const`
- L1797 _public function_ `const TArray<TSharedPtrTS<FDashMPD_PeriodType>>& GetPeriods() const`
- L1798 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetEssentialProperties() const override`
- L1799 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetSupplementalProperties() const override`
- L1800 _public function_ `const TArray<TSharedPtrTS<FDashMPD_DescriptorType>>& GetUTCTimings() const`
- L1801 _public function_ `const TArray<TSharedPtrTS<FDashMPD_ServiceDescriptionType>>& GetServiceDescriptions() const`
- L1802 _public function_ `const TArray<TSharedPtrTS<FDashMPD_InitializationSetType>>& GetInitializationSets() const`
- L1803 _public function_ `const TArray<TSharedPtrTS<FDashMPD_UIntVWithIDType>>& GetInitializationGroups() const`
- L1804 _public function_ `const TArray<TSharedPtrTS<FDashMPD_UIntVWithIDType>>& GetInitializationPresentations() const`
- L1805 _public function_ `TSharedPtrTS<FDashMPD_LeapSecondInformationType> GetLeapSecondInformation() const`
- L1806 _public function_ `TSharedPtrTS<FDashMPD_ContentSteeringType> GetContentSteering() const`
- L1808 _public function_ `const FString& GetID() const`
- L1809 _public function_ `const TArray<FString>& GetProfiles()`
- L1810 _public function_ `const FString& GetType() const`
- L1811 _public function_ `const FTimeValue& GetAvailabilityStartTime() const`
- L1812 _public function_ `const FTimeValue& GetAvailabilityEndTime() const`
- L1813 _public function_ `const FTimeValue& GetPublishTime() const`
- L1814 _public function_ `const FTimeValue& GetMediaPresentationDuration() const`
- L1815 _public function_ `const FTimeValue& GetMinimumUpdatePeriod() const`
- L1816 _public function_ `const FTimeValue& GetMinBufferTime() const`
- L1817 _public function_ `const FTimeValue& GetTimeShiftBufferDepth() const`
- L1818 _public function_ `const FTimeValue& GetSuggestedPresentationDelay() const`
- L1819 _public function_ `const FTimeValue& GetMaxSegmentDuration() const`
- L1820 _public function_ `const FTimeValue& GetMaxSubsegmentDuration() const`
- L1822 _public function_ `FString GetDocumentURL() const override`
- L1823 _public function_ `void SetDocumentURL(const FString& InDocumentURL)`
- L1824 _public function_ `const FTimeValue& GetFetchTime() const`
- L1825 _public function_ `void SetFetchTime(const FTimeValue& InFetchTime)`
- L1826 _public function_ `FString GetETag() const`
- L1827 _public function_ `void SetETag(const FString& InETag)`
- L1828 _public function_ `void RemoveUTCTimingElement(TSharedPtrTS<FDashMPD_DescriptorType> TimingElement)`
- L1833 _public function_ `void AddUTCTimingElement(const FString& InData, const FString& InScheme, const FString& InID, const FString& InValue)`
- L1842 _public function_ `void SetDVBDash(bool bInDVBDash)`
- L1843 _public function_ `bool IsDVBDash() const`
- L1846 _public function_ `void LockAccess()` — Methods to manipulate the presentation type.
- L1847 _public function_ `void UnlockAccess()`
- L1848 _public function_ `void SetType(const FString& InType)`
- L1849 _public function_ `void SetPublishTime(const FTimeValue& InPUBT)`
- L1850 _public function_ `void SetAvailabilityStartTime(const FTimeValue& InAST)`
- L1851 _public function_ `void SetAvailabilityEndTime(const FTimeValue& InAET)`
- L1852 _public function_ `void SetMediaPresentationDuration(const FTimeValue& InPD)`
- L1853 _public function_ `void SetMinimumUpdatePeriod(const FTimeValue& InMUP)`
- L1854 _public function_ `void SetTimeShiftBufferDepth(const FTimeValue& InTSB)`
- L1855 _public function_ `void SetSuggestedPresentationDelay(const FTimeValue& InSPD)`
- L1858 _private prototype_ `bool ProcessElement(FManifestParserDASH* Builder, const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;`
- L1859 _private prototype_ `bool ProcessAttribute(FManifestParserDASH* Builder, const TCHAR* AttributeName, const TCHAR* AttributeValue) override;`
- L1860 _private prototype_ `int32 ReplaceChildElementWithRemoteEntities(TSharedPtrTS<IDashMPDElement> Element, const FDashMPD_RootEntities& NewRootEntities, int64 OldResolveID, int64 NewResolveID) override;`
- L1865 _private member_ `mutable FCriticalSection UpdateLock;` — The MPD is not expected to get modified after being built except for potential XLink changes and extending the validity if an MPD update returned a 304 on a conditional GET. For these occurrences we need to lock access to the document on occasion.
- L1868 _private member_ `FString DocumentURL;` — The URL from which this MPD was loaded. Provided for convenience.
- L1871 _private member_ `FString ETag;` — Optional ETag for conditional GET update requests.
- L1874 _private member_ `bool bIsDVBDash = false;` — Set if the MPD is specifying a DVB-DASH profile.
- L1877 _private member_ `FTimeValue FetchTime;` — Time the MPD load request was started.
- L1880 _private member_ `TArray<TSharedPtrTS<FDashMPD_ProgramInformationType>> ProgramInformations;` — Program information.
- L1883 _private member_ `TArray<TSharedPtrTS<FDashMPD_BaseURLType>> BaseURLs;` — Base URLs.
- L1886 _private member_ `TArray<TSharedPtrTS<FDashMPD_OtherType>> Locations;` — Locations where the MPD can be found.
- L1889 _private member_ `TArray<TSharedPtrTS<FDashMPD_PeriodType>> Periods;` — Periods in order as they appear in the MPD.
- L1891 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> EssentialProperties;`
- L1892 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> SupplementalProperties;`
- L1893 _private member_ `TArray<TSharedPtrTS<FDashMPD_DescriptorType>> UTCTimings;`
- L1895 _private member_ `TArray<TSharedPtrTS<FDashMPD_ServiceDescriptionType>> ServiceDescriptions;`
- L1896 _private member_ `TArray<TSharedPtrTS<FDashMPD_InitializationSetType>> InitializationSets;`
- L1897 _private member_ `TArray<TSharedPtrTS<FDashMPD_UIntVWithIDType>> InitializationGroups;`
- L1898 _private member_ `TArray<TSharedPtrTS<FDashMPD_UIntVWithIDType>> InitializationPresentations;`
- L1899 _private member_ `TSharedPtrTS<FDashMPD_LeapSecondInformationType> LeapSecondInformation;`
- L1900 _private member_ `TSharedPtrTS<FDashMPD_ContentSteeringType> ContentSteering;`
- L1904 _private member_ `FString ID;` — Attributes of this MPD element.
- L1905 _private member_ `TArray<FString> Profiles;`
- L1906 _private member_ `FString Type = TEXT("sta`
- L1907 _private member_ `FTimeValue AvailabilityStartTime;`
- L1908 _private member_ `FTimeValue AvailabilityEndTime;`
- L1909 _private member_ `FTimeValue PublishTime;`
- L1910 _private member_ `FTimeValue MediaPresentationDuration;`
- L1911 _private member_ `FTimeValue MinimumUpdatePeriod;`
- L1912 _private member_ `FTimeValue MinBufferTime;`
- L1913 _private member_ `FTimeValue TimeShiftBufferDepth;`
- L1914 _private member_ `FTimeValue SuggestedPresentationDelay;`
- L1915 _private member_ `FTimeValue MaxSegmentDuration;`
- L1916 _private member_ `FTimeValue MaxSubsegmentDuration;`

#### class `Electra::FDashMPD_RootEntities`  
`class FDashMPD_RootEntities`  
_L1924-1934_
- desc: This is merely a container into which the XML parser adds root elements as it finds them. We need this when resolving remote xlink entities that bring in elements not within a root <MPD> element.
- L1927 _public member_ `TArray<TSharedPtrTS<FDashMPD_MPDType>> MPDs;`
- L1928 _public member_ `TArray<TSharedPtrTS<FDashMPD_PeriodType>> Periods;`
- L1929 _public member_ `TArray<TSharedPtrTS<FDashMPD_AdaptationSetType>> AdaptationSets;`
- L1930 _public member_ `TArray<TSharedPtrTS<FDashMPD_UrlQueryInfoType>> UrlQueries;`
- L1931 _public member_ `TArray<TSharedPtrTS<FDashMPD_InitializationSetType>> InitializationSets;`
- L1932 _public member_ `TArray<TSharedPtrTS<FDashMPD_EventStreamType>> EventStreams;`
- L1933 _public member_ `TArray<TSharedPtrTS<FDashMPD_SegmentListType>> SegmentLists;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/ManifestBuilderDASH.h` (Private)


#### class `Electra::IManifestBuilderDASH`  
`class IManifestBuilderDASH`  
_L18-37_
- L21 _public prototype_ `static IManifestBuilderDASH* Create(IPlayerSessionServices* PlayerSessionServices);`
- L23 _public prototype_ `virtual ~IManifestBuilderDASH() = default;`
- L36 _public prototype_ `virtual FErrorDetail BuildFromMPD(TSharedPtrTS<FManifestDASHInternal>& OutMPD, TCHAR* InOutMPDXML, const FString& EffectiveURL, const FString& ETag, const TArray<FElectraHTTPStreamHeader>& InResponseHeaders) = 0;` — Builds a new internal manifest from a DASH MPD @param OutMPD @param InOutMPDXML @param EffectiveURL @param ETag @param InResponseHeaders @return

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/ManifestDASH.h` (Private)


#### class `Electra::FManifestDASH`  
`class FManifestDASH : public IManifest`  
_L14-63_
- inherits: `IManifest`
- L17 _public prototype_ `static TSharedPtrTS<FManifestDASH> Create(IPlayerSessionServices* SessionServices, TSharedPtrTS<FManifestDASHInternal> Manifest);`
- L18 _public prototype_ `void UpdateInternalManifest(TSharedPtrTS<FManifestDASHInternal> UpdatedManifest);`
- L20 _public prototype_ `virtual ~FManifestDASH();`
- L21 _public prototype_ `EMediaFormatType GetMediaFormatType() const override;`
- L22 _public prototype_ `bool ReloadsPlaylistPeriodically() const override;`
- L23 _public prototype_ `bool SupportsMultipleTracksPerKind() const override;`
- L24 _public prototype_ `bool OrderOfTracksCanChangeDynamically() const override;`
- L25 _public prototype_ `EType GetPresentationType() const override;`
- L26 _public prototype_ `EReplayEventType GetReplayType() const override;`
- L27 _public prototype_ `TSharedPtrTS<const FLowLatencyDescriptor> GetLowLatencyDescriptor() const override;`
- L28 _public prototype_ `FTimeValue CalculateCurrentLiveLatency(const FTimeValue& InCurrentPlaybackPosition, const FTimeValue& InEncoderLatency, bool bViaLatencyElement) const override;`
- L29 _public prototype_ `FTimeValue GetAnchorTime() const override;`
- L30 _public prototype_ `FTimeRange GetTotalTimeRange() const override;`
- L31 _public prototype_ `FTimeRange GetSeekableTimeRange() const override;`
- L32 _public prototype_ `FTimeRange GetPlaybackRange(EPlaybackRangeType InRangeType) const override;`
- L33 _public prototype_ `FTimeValue GetDuration() const override;`
- L34 _public prototype_ `FTimeValue GetDefaultStartTime() const override;`
- L35 _public prototype_ `void ClearDefaultStartTime() override;`
- L36 _public prototype_ `FTimeValue GetDefaultEndTime() const override;`
- L37 _public prototype_ `void ClearDefaultEndTime() override;`
- L38 _public prototype_ `FTimeValue GetMinBufferTime() const override;`
- L39 _public prototype_ `FTimeValue GetDesiredLiveLatency() const override;`
- L40 _public prototype_ `ELiveEdgePlayMode GetLiveEdgePlayMode() const override;`
- L41 _public prototype_ `TRangeSet<double> GetPossiblePlaybackRates(EPlayRateType InForType) const override;`
- L42 _public prototype_ `TSharedPtrTS<IProducerReferenceTimeInfo> GetProducerReferenceTimeInfo(int64 ID) const override;`
- L43 _public prototype_ `void GetTrackMetadata(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override;`
- L44 _public prototype_ `void UpdateRunningMetaData(TSharedPtrTS<FMetadataParser> InUpdatedMetaData) override;`
- L45 _public prototype_ `void UpdateDynamicRefetchCounter() override;`
- L46 _public prototype_ `void PrepareForLooping(int32 InNumLoopsToAdd) override;`
- L47 _public prototype_ `void TriggerClockSync(IManifest::EClockSyncType InClockSyncType) override;`
- L48 _public prototype_ `void TriggerPlaylistRefresh() override;`
- L49 _public prototype_ `void ReachedStableBuffer() override;`
- L50 _public prototype_ `IStreamReader* CreateStreamReaderHandler() override;`
- L52 _public prototype_ `FResult FindPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L53 _public prototype_ `FResult FindNextPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, TSharedPtrTS<const IStreamSegment> CurrentSegment) override;`
- L56 _private prototype_ `ELECTRA_IMPL_DEFAULT_ERROR_METHODS(DASHManifest);`
- L58 _private prototype_ `FManifestDASH(IPlayerSessionServices* SessionServices, TSharedPtrTS<FManifestDASHInternal> Manifest);`
- L60 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L61 _private member_ `TSharedPtrTS<FManifestDASHInternal> CurrentManifest;`
- L62 _private member_ `int64 CurrentPeriodAndAdaptationXLinkResolveID = 1;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/ManifestParserDASH.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Electra`
- L14 _namespace_ `namespace IManifestParserDASH` (scope `Electra`)
- L16 _prototype_ `FErrorDetail BuildFromMPD(FDashMPD_RootEntities& OutRootEntities, TArray<TWeakPtrTS<IDashMPDElement>>& OutXLinkElements, TCHAR* InOutMPDXML, const TCHAR* InExpectedRootElement, IPlayerSessionServices* InPlayerSessionServices);` (scope `Electra::IManifestParserDASH`)
- L18 _prototype_ `void BuildJSONFromCustomElement(FString& OutJSON, TSharedPtrTS<IDashMPDElement> InElement, bool bIncludeStartElement, bool bRemoveNamespaces, bool bForce1ElementArrays, bool bTerseObjects, const TCHAR* AttributePrefix, const TCHAR* TextPropertyName);` (scope `Electra::IManifestParserDASH`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/OptionKeynamesDASH.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L9 _namespace_ `namespace DASH` (scope `Electra`)
- L12 _variable_ `const FName OptionKeyMPDLoadConnectTimeout(TEXT("mpd_` (scope `Electra::DASH`) — (FTimeValue) value specifying connection timeout fetching the MPD
- L13 _variable_ `const FName OptionKeyMPDLoadNoDataTimeout(TEXT("mpd_` (scope `Electra::DASH`) — (FTimeValue) value specifying no-data timeout fetching the MPD
- L14 _variable_ `const FName OptionKeyMPDReloadConnectTimeout(TEXT("mpd_` (scope `Electra::DASH`) — (FTimeValue) value specifying connection timeout fetching the MPD repeatedly
- L15 _variable_ `const FName OptionKeyMPDReloadNoDataTimeout(TEXT("mpd_` (scope `Electra::DASH`) — (FTimeValue) value specifying no-data timeout fetching the MPD repeatedly
- L17 _variable_ `const FName OptionKeyInitSegmentConnectTimeout(TEXT("init` (scope `Electra::DASH`) — (FTimeValue) value specifying connection timeout fetching an init segment
- L18 _variable_ `const FName OptionKeyInitSegmentNoDataTimeout(TEXT("init` (scope `Electra::DASH`) — (FTimeValue) value specifying no-data timeout fetching an init segment
- L19 _variable_ `const FName OptionKeyMediaSegmentConnectTimeout(TEXT("medi` (scope `Electra::DASH`) — (FTimeValue) value specifying connection timeout fetching a media segment
- L20 _variable_ `const FName OptionKeyMediaSegmentNoDataTimeout(TEXT("medi` (scope `Electra::DASH`) — (FTimeValue) value specifying no-data timeout fetching a media segment
- L22 _variable_ `const FName OptionKey_MinTimeBetweenMPDUpdates(TEXT("dash` (scope `Electra::DASH`) — (FTimeValue) value limiting the time between MPD updates unless these are required updates.
- L24 _variable_ `const FName OptionKey_CurrentCDN(TEXT("dash` (scope `Electra::DASH`) — A string giving the currently selected CDN to be used with <BaseURL@serviceLocation> elements.
- L26 _variable_ `const FName OptionKey_LatencyReferenceId(TEXT("dash` (scope `Electra::DASH`) — The Id of the <ProducerReferenceTime> element used by <ServiceDescription><Latency>
- L28 _variable_ `const FString HTTPHeaderOptionName(TEXT("MPEG` (scope `Electra::DASH`) — HTTP request header name carrying optional DASH specific parameters.

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/PlayerEventDASH.h` (Private)


#### class `Electra::DASH::FPlayerEvent`  
`class FPlayerEvent : public IAdaptiveStreamingPlayerAEMSEvent`  
_L16-86_
- inherits: `IAdaptiveStreamingPlayerAEMSEvent`
- L19 _public prototype_ `virtual ~FPlayerEvent() = default;`
- L22 _public function_ `void SetOrigin(EOrigin InOrigin)`
- L24 _public function_ `void SetSchemeIdUri(FString InSchemeIdUri)`
- L26 _public function_ `void SetValue(FString InValue)`
- L28 _public function_ `void SetID(FString InID)`
- L30 _public function_ `void SetPresentationTime(FTimeValue InPresentationTime)`
- L32 _public function_ `void SetDuration(FTimeValue InDuration)`
- L34 _public function_ `void SetMessageData(const FString& InData, bool bDecodeBase64)`
- L48 _public function_ `void SetMessageData(TConstArrayView<uint8> InData)`
- L53 _public function_ `void SetPeriodID(const FString& InPeriodID)`
- L57 _public function_ `FString GetPeriodID() const`
- L62 _public function_ `virtual EOrigin GetOrigin() const override`
- L64 _public function_ `virtual FString GetSchemeIdUri() const override`
- L66 _public function_ `virtual FString GetValue() const override`
- L68 _public function_ `virtual FString GetID() const override`
- L70 _public function_ `virtual FTimeValue GetPresentationTime() const override`
- L72 _public function_ `virtual FTimeValue GetDuration() const override`
- L74 _public function_ `virtual const TArray<uint8>& GetMessageData() const override`
- L78 _private member_ `EOrigin Origin;`
- L79 _private member_ `FString SchemeIdUri;`
- L80 _private member_ `FString Value;`
- L81 _private member_ `FString ID;`
- L82 _private member_ `FTimeValue PresentationTime;`
- L83 _private member_ `FTimeValue Duration;`
- L84 _private member_ `TArray<uint8> MessageData;`
- L85 _private member_ `FString PeriodID;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`
- L13 _namespace_ `namespace DASH` (scope `Electra`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/PlayerEventDASH_Internal.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L10 _namespace_ `namespace DASH` (scope `Electra`)
- L13 _namespace_ `namespace Schemes` (scope `Electra::DASH`)
- L16 _namespace_ `namespace TimingSources` (scope `Electra::DASH::Schemes`)
- L18 _variable_ `const TCHAR* const Scheme_urn_mpeg_dash_utc_httphead2014 = TEXT("urn` (scope `Electra::DASH::Schemes::TimingSources`)
- L19 _variable_ `const TCHAR* const Scheme_urn_mpeg_dash_utc_httpxsdate2014 = TEXT("urn` (scope `Electra::DASH::Schemes::TimingSources`)
- L20 _variable_ `const TCHAR* const Scheme_urn_mpeg_dash_utc_httpiso2014 = TEXT("urn` (scope `Electra::DASH::Schemes::TimingSources`)
- L21 _variable_ `const TCHAR* const Scheme_urn_mpeg_dash_utc_direct2014 = TEXT("urn` (scope `Electra::DASH::Schemes::TimingSources`)
- L29 _namespace_ `namespace ManifestEvents` (scope `Electra::DASH::Schemes`)
- L31 _variable_ `const TCHAR* const Scheme_urn_mpeg_dash_event_2012 = TEXT("urn` (scope `Electra::DASH::Schemes::ManifestEvents`)
- L32 _variable_ `const TCHAR* const Scheme_urn_mpeg_dash_event_callback_2015 = TEXT("urn` (scope `Electra::DASH::Schemes::ManifestEvents`)
- L33 _variable_ `const TCHAR* const Scheme_urn_mpeg_dash_event_ttfn_2016 = TEXT("urn` (scope `Electra::DASH::Schemes::ManifestEvents`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/PlaylistReaderDASH.h` (Private)


#### class `Electra::IPlaylistReaderDASH`  
`class IPlaylistReaderDASH : public IPlaylistReader`  
_L18-72_
- inherits: `IPlaylistReader`
- L21 _public prototype_ `static TSharedPtrTS<IPlaylistReader> Create(IPlayerSessionServices* PlayerSessionServices);`
- L23 _public prototype_ `virtual ~IPlaylistReaderDASH() = default;`
- L31 _public prototype_ `virtual void LoadAndParse(const FString& InURL, const Playlist::FReplayEventParams& InReplayEventParams) = 0;` — Loads and parses the MPD. @param URL URL of the playlist to load @param InReplayEventParams URL fragments pertaining to replay event which have been removed from the source URL
- L38 _public prototype_ `virtual FString GetURL() const = 0;` — Returns the URL from which the MPD was loaded (or supposed to be loaded). @return The MPD URL
- L45 _public prototype_ `virtual void AddElementLoadRequests(const TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& RemoteElementLoadRequests) = 0;` — Adds load requests for additional elements. @param RemoteElementLoadRequests
- L56 _public prototype_ `virtual void RequestMPDUpdate(EMPDRequestType InRequestType) = 0;`
- L61 _public prototype_ `virtual void RequestClockResync() = 0;` — Requests a resync of the player clock with the server clock.
- L66 _public prototype_ `virtual TSharedPtrTS<FManifestDASHInternal> GetCurrentMPD() = 0;` — Access the current internal MPD
- L71 _public prototype_ `virtual void SetStreamInbandEventUsage(EStreamType InStreamType, bool bUsesInbandDASHEvents) = 0;` — Informs whether or not a currently playing stream is using inband events.

#### enum `Electra::IPlaylistReaderDASH::EMPDRequestType`  
`enum class EMPDRequestType`  
_L50-55_
- desc: Requests an MPD update.
- L52 _public enumerator_ `MinimumUpdatePeriod` — Triggered through MPD@minimumUpdatePeriod
- L53 _public enumerator_ `GetLatestSegment` — Locating the segment in the Live period
- L54 _public enumerator_ `EventMessage` — Triggered through an event message

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DASH/PlaylistReaderDASH_Internal.h` (Private)


#### struct `Electra::FMPDLoadRequestDASH`  
`struct FMPDLoadRequestDASH : public IHTTPResourceRequestObject`  
_L25-112_
- inherits: `IHTTPResourceRequestObject`
- L27 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnRequestCompleted, TSharedPtrTS<FMPDLoadRequestDASH> , bool );`
- L47 _public function_ `const TCHAR* const GetRequestTypeName() const`
- L69 _public function_ `ELoadType GetLoadType() const`
- L74 _public function_ `FMPDLoadRequestDASH() : LoadType(ELoadType::MPD)`
- L75 _public member_ `FMediaURL Url;` — For xlink requests this could be "urn:mpeg:dash:resolve-to-zero:2013" indicating removal of the element.
- L76 _public member_ `int64 SteeringID = -1;`
- L77 _public member_ `FString Range;`
- L78 _public member_ `FString Range2;`
- L79 _public member_ `FString Verb;`
- L80 _public member_ `TArray<HTTP::FHTTPHeader> Headers;`
- L81 _public member_ `FTimeValue ExecuteAtUTC;`
- L83 _public member_ `FOnRequestCompleted CompleteCallback;`
- L85 _public member_ `ELoadType LoadType;`
- L87 _public member_ `TWeakPtrTS<IDashMPDElement> XLinkElement;` — XLink specific information to which the remote element applies.
- L90 _public member_ `TWeakPtrTS<FManifestDASHInternal> OwningManifest;` — The manifest for which this request is made. Not set for an initial MPD fetch but set for everything else. This allows checking if - after a dynamic MPD update - the requesting MPD is still valid and in use.
- L92 _public member_ `EStreamType SegmentStreamType = EStreamType::Unsupported;`
- L93 _public member_ `int32 SegmentQualityIndex = 0;`
- L94 _public member_ `int32 SegmentQualityIndexMax = 0;`
- L95 _public member_ `int32 Bitrate = 0;`
- L97 _public member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L98 _public member_ `TSharedPtrTS<FHTTPResourceRequest> Request;`
- L99 _public member_ `int32 Attempt = 0;`
- L101 _public member_ `TArray<TSharedPtrTS<FMPDLoadRequestDASH>> CompletedRequestChain;`
- L102 _public member_ `int32 NumRemainingInChain = 0;`
- L104 _public function_ `const HTTP::FConnectionInfo* GetConnectionInfo() const`
- L108 _public function_ `FString GetErrorDetail() const`

#### enum `Electra::FMPDLoadRequestDASH::ELoadType`  
`enum class ELoadType`  
_L29-46_
- L31 _public enumerator_ `MPD`
- L32 _public enumerator_ `MPDUpdate`
- L33 _public enumerator_ `XLink_Period`
- L34 _public enumerator_ `XLink_AdaptationSet`
- L35 _public enumerator_ `XLink_EventStream`
- L36 _public enumerator_ `XLink_SegmentList`
- L37 _public enumerator_ `XLink_URLQuery`
- L38 _public enumerator_ `XLink_InitializationSet`
- L39 _public enumerator_ `Callback`
- L40 _public enumerator_ `Segment`
- L41 _public enumerator_ `IndexSegment`
- L42 _public enumerator_ `InitSegment`
- L43 _public enumerator_ `TimeSync`
- L44 _public enumerator_ `Sideload`
- L45 _public enumerator_ `Steering`

#### struct `Electra::DASHUrlHelpers::FDASHMediaURL`  
`struct FDASHMediaURL : FMediaURL`  
_L123-128_
- inherits: `FMediaURL`
- L125 _public member_ `FString ByteRange;`
- L126 _public member_ `FTimeValue ATO {FTimeValue::GetZero()};`
- L127 _public member_ `TMediaOptionalValue<bool> ATOComplete;`

#### enum `Electra::DASHUrlHelpers::EUrlQueryRequestType`  
`enum class EUrlQueryRequestType`  
_L133-142_
- L135 _public enumerator_ `Segment`
- L136 _public enumerator_ `Xlink`
- L137 _public enumerator_ `Mpd`
- L138 _public enumerator_ `Callback`
- L139 _public enumerator_ `Chaining`
- L140 _public enumerator_ `Fallback`
- L141 _public enumerator_ `Steering`

#### class `Electra::FManifestDASHInternal`  
`class FManifestDASHInternal`  
_L153-913_
- L716 _public prototype_ `FErrorDetail Build(IPlayerSessionServices* InPlayerSessionServices, TSharedPtr<FDashMPD_MPDType, ESPMode::ThreadSafe> InMPDRoot, TArray<TWeakPtrTS<IDashMPDElement>> InXLinkElements);`
- L718 _public prototype_ `FErrorDetail BuildAfterInitialRemoteElementDownload();`
- L720 _public function_ `void GetRemoteElementLoadRequests(TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& OutRemoteElementLoadRequests)`
- L725 _public prototype_ `FErrorDetail ResolveInitialRemoteElementRequest(TSharedPtrTS<FMPDLoadRequestDASH> RequestResponse, FString XMLResponse, bool bSuccess);`
- L727 _public function_ `EPresentationType GetPresentationType() const`
- L732 _public function_ `bool IsEpicEvent() const`
- L737 _public function_ `bool IsDynamicEpicEvent() const`
- L742 _public function_ `const TArray<TSharedPtrTS<FPeriod>>& GetPeriods() const`
- L747 _public function_ `TSharedPtrTS<FManifestDASHInternal::FPeriod> GetPeriodByUniqueID(const FString& InUniqueID) const`
- L759 _public function_ `bool HasFollowingRegularPeriod(TSharedPtrTS<FPeriod> InPeriod) const`
- L776 _public function_ `TSharedPtrTS<const FDashMPD_MPDType> GetMPDRoot() const`
- L781 _public function_ `TSharedPtrTS<FDashMPD_MPDType> GetMPDRoot()`
- L786 _public prototype_ `void PreparePeriodAdaptationSets(TSharedPtrTS<FPeriod> InPeriod, bool bRequestXlink);`
- L788 _public prototype_ `void SendEventsFromAllPeriodEventStreams(TSharedPtrTS<FPeriod> InPeriod);`
- L790 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents() const`
- L795 _public function_ `void SetURLFragmentComponents(TArray<FURL_RFC3986::FQueryParam> InURLFragmentComponents)`
- L800 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents()`
- L805 _public function_ `void SetReplayEventParams(const Playlist::FReplayEventParams& InEventReplayParams)`
- L810 _public function_ `const Playlist::FReplayEventParams& GetReplayEventParams()`
- L815 _public prototype_ `void InjectEpicTimingSources();`
- L816 _public prototype_ `void TransformIntoEpicEvent();`
- L817 _public prototype_ `void PrepareEpicEventForLooping(int32 InNumLoopsToAdd);`
- L819 _public prototype_ `ELECTRA_IMPL_DEFAULT_ERROR_METHODS(DASHManifest);`
- L822 _public function_ `TSharedPtrTS<const FLowLatencyDescriptor> GetLowLatencyDescriptor() const`
- L826 _public function_ `TSharedPtrTS<FProducerReferenceTimeInfo> GetProducerReferenceTimeElement(int64 InID) const`
- L831 _public function_ `FTimeValue GetSegmentFetchDelay() const`
- L835 _public function_ `void SetSegmentFetchDelay(const FTimeValue& InNewFetchDelay)`
- L840 _public prototype_ `FTimeValue GetAnchorTime() const;`
- L841 _public prototype_ `FTimeRange GetTotalTimeRange() const;`
- L842 _public prototype_ `FTimeRange GetSeekableTimeRange() const;`
- L843 _public prototype_ `FTimeValue GetDuration() const;`
- L844 _public prototype_ `void PrepareDefaultStartTime();`
- L845 _public prototype_ `FTimeValue GetDefaultStartTime() const;`
- L846 _public prototype_ `void ClearDefaultStartTime();`
- L847 _public prototype_ `FTimeValue GetDefaultEndTime() const;`
- L848 _public prototype_ `void ClearDefaultEndTime();`
- L849 _public prototype_ `FTimeRange GetPlayTimesFromURI(IManifest::EPlaybackRangeType InRangeType) const;`
- L850 _public prototype_ `FTimeValue GetDesiredLiveLatency() const;`
- L852 _public prototype_ `FTimeValue GetMPDValidityEndTime() const;`
- L853 _public prototype_ `FTimeValue GetLastPeriodEndTime(bool bForTimeline) const;`
- L854 _public prototype_ `FTimeValue GetMinimumUpdatePeriod() const;`
- L855 _public prototype_ `bool AreUpdatesExpected() const;`
- L856 _public prototype_ `bool IsStaticType() const;`
- L857 _public prototype_ `bool UsesAST() const;`
- L858 _public prototype_ `bool HasInjectedTimingSources() const;`
- L860 _public prototype_ `FTimeValue GetAvailabilityEndTime() const;`
- L861 _public prototype_ `FTimeValue GetTimeshiftBufferDepth() const;`
- L863 _public prototype_ `void EndPresentationAt(const FTimeValue& EndsAt, const FString& InPeriod);`
- L872 _private prototype_ `FErrorDetail PrepareRemoteElementLoadRequest(TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& OutRemoteElementLoadRequests, TWeakPtrTS<IDashMPDElement> ElementWithXLink, int64 RequestID);`
- L874 _private prototype_ `int32 ReplaceElementWithRemoteEntities(TSharedPtrTS<IDashMPDElement> Element, const FDashMPD_RootEntities& NewRootEntities, int64 OldResolveID, int64 NewResolveID);`
- L876 _private prototype_ `FTimeValue CalculateDistanceToLiveEdge() const;`
- L878 _private prototype_ `bool CanUseEncryptedAdaptation(const TSharedPtrTS<FAdaptationSet>& InAdaptationSet);`
- L880 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L882 _private member_ `TArray<TWeakPtrTS<IDashMPDElement>> RemoteElementsToResolve;`
- L883 _private member_ `TArray<TWeakPtrTS<FMPDLoadRequestDASH>> PendingRemoteElementLoadRequests;`
- L886 _private member_ `TSharedPtrTS<FDashMPD_MPDType> MPDRoot;` — The parsed MPD.
- L889 _private member_ `TArray<FURL_RFC3986::FQueryParam> URLFragmentComponents;` — The MPD URL fragment components
- L890 _private member_ `Playlist::FReplayEventParams ReplayEventParams;`
- L893 _private member_ `EPresentationType PresentationType;` — Type of the presentation.
- L894 _private member_ `EEpicEventType EpicEventType = EEpicEventType::None;`
- L895 _private member_ `FTimeValue OriginalPresentationDuration;`
- L897 _private member_ `TArray<TSharedPtrTS<FPeriod>> Periods;`
- L899 _private member_ `TMap<uint32, TSharedPtrTS<FProducerReferenceTimeInfo>> ProducerReferenceTimeElements;`
- L900 _private member_ `TSharedPtrTS<FLowLatencyDescriptor> LowLatencyDescriptor;`
- L902 _private member_ `FTimeValue SegmentFetchDelay;`
- L904 _private member_ `mutable FTimeValue CalculatedLiveDistance;`
- L906 _private member_ `mutable FTimeRange TotalTimeRange;`
- L907 _private member_ `mutable FTimeRange SeekableTimeRange;`
- L908 _private member_ `FTimeValue DefaultStartTime;`
- L909 _private member_ `FTimeValue DefaultEndTime;`
- L910 _private member_ `mutable bool bWarnedAboutTooSmallSuggestedPresentationDelay = false;`
- L912 _private member_ `bool bDidInjectUTCTimingElements = false;`

#### enum `Electra::FManifestDASHInternal::EPresentationType`  
`enum class EPresentationType`  
_L156-160_
- L158 _public enumerator_ `Static`
- L159 _public enumerator_ `Dynamic`

#### struct `Electra::FManifestDASHInternal::FSegmentSearchOption`  
`struct FSegmentSearchOption`  
_L162-175_
- L164 _public member_ `FTimeValue PeriodLocalTime;` — Time local in the period to search a segment for.
- L165 _public member_ `FTimeValue PeriodDuration;` — Duration of the period. Needed to determine the number of segments in the period.
- L166 _public member_ `FTimeValue PeriodPresentationEnd;` — End time of the presetation in period local time, if not set to invalid or infinity.
- L167 _public member_ `IManifest::ESearchType SearchType = IManifest::ESearchType::Closest;`
- L168 _public member_ `int64 RequestID = 0;` — Sequential request ID across all segments during playback, needed to re-resolve potential UrlQueryInfo xlinks.
- L169 _public member_ `bool bHasFollowingPeriod = false;` — true if we know for sure there is another period following.
- L170 _public member_ `bool bFrameAccurateSearch = false;` — true to prepare segments for frame-accurate decoding and rendering
- L171 _public member_ `bool bInitSegmentSetupOnly = false;` — true to get the initialization segment information only.
- L172 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L173 _public member_ `int32 QualityIndex = 0;`
- L174 _public member_ `int32 MaxQualityIndex = 0;`

#### struct `Electra::FManifestDASHInternal::FLabelElement`  
`struct FLabelElement`  
_L177-182_
- L179 _public member_ `FString LabelText;`
- L180 _public member_ `FString Language;`
- L181 _public member_ `uint64 ID = 0;`

#### class `Electra::FManifestDASHInternal::FRepresentation`  
`class FRepresentation : public IPlaybackAssetRepresentation, public TSharedFromThis<FRepresentation, ESPMode::ThreadSafe>`  
_L184-289_
- inherits: `IPlaybackAssetRepresentation,TSharedFromThis<FRepresentation,ESPMode::ThreadSafe>`
- L187 _public prototype_ `FRepresentation() = default;`
- L188 _public prototype_ `virtual ~FRepresentation() = default;`
- L199 _public prototype_ `ESearchResult FindSegment(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& OutSegmentInfo, TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& OutRemoteElementLoadRequests, const FSegmentSearchOption& InSearchOptions);`
- L201 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const TSharedPtrTS<IPlaybackAssetAdaptationSet>& AdaptationSet);`
- L203 _public function_ `int32 GetSelectionPriority() const`
- L205 _public function_ `bool IsSideloadedSubtitle() const`
- L210 _public function_ `FString GetUniqueIdentifier() const override` — Methods from IPlaybackAssetRepresentation
- L214 _public function_ `const FStreamCodecInformation& GetCodecInformation() const override`
- L218 _public function_ `int32 GetBitrate() const override`
- L222 _public function_ `int32 GetQualityIndex() const override`
- L226 _public function_ `bool CanBePlayed() const override`
- L237 _public function_ `EStreamContainerType GetStreamContainerType() const`
- L243 _private prototype_ `ESearchResult PrepareSegmentIndex(IPlayerSessionServices* PlayerSessionServices, const TArray<TSharedPtrTS<FDashMPD_SegmentBaseType>>& SegmentBase, TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& OutRemoteElementLoadRequests, const FSegmentSearchOption& InSearchOptions);`
- L245 _private prototype_ `ESearchResult FindSegment_Base_MP4(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& OutSegmentInfo, TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& OutRemoteElementLoadRequests, const FSegmentSearchOption& InSearchOptions, const TSharedPtrTS<FDashMPD_RepresentationType>& MPDRepresentation, const TArray<TSharedPtrTS<FDashMPD_SegmentBaseType>>& SegmentBase);`
- L246 _private prototype_ `ESearchResult FindSegment_Base_MKV(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& OutSegmentInfo, TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& OutRemoteElementLoadRequests, const FSegmentSearchOption& InSearchOptions, const TSharedPtrTS<FDashMPD_RepresentationType>& MPDRepresentation, const TArray<TSharedPtrTS<FDashMPD_SegmentBaseType>>& SegmentBase);`
- L247 _private prototype_ `ESearchResult FindSegment_Template(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& OutSegmentInfo, TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& OutRemoteElementLoadRequests, const FSegmentSearchOption& InSearchOptions, const TSharedPtrTS<FDashMPD_RepresentationType>& MPDRepresentation, const TArray<TSharedPtrTS<FDashMPD_SegmentTemplateType>>& SegmentTemplate);`
- L248 _private prototype_ `ESearchResult FindSegment_Timeline(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& OutSegmentInfo, TArray<TWeakPtrTS<FMPDLoadRequestDASH>>& OutRemoteElementLoadRequests, const FSegmentSearchOption& InSearchOptions, const TSharedPtrTS<FDashMPD_RepresentationType>& MPDRepresentation, const TArray<TSharedPtrTS<FDashMPD_SegmentTemplateType>>& SegmentTemplate, const TSharedPtrTS<FDashMPD_SegmentTimelineType>& SegmentTimeline);`
- L249 _private prototype_ `ESearchResult SetupSideloadedFile(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& OutSegmentInfo, const FSegmentSearchOption& InSearchOptions, const TSharedPtrTS<FDashMPD_RepresentationType>& MPDRepresentation);`
- L251 _private prototype_ `void PrepareSteeringCandidates(TArray<FContentSteeringHandler::FCandidateURL>& OutSteeringCandidates, IPlayerSessionServices* InPlayerSessionServices, const FString& InDocumentURL, const TArray<DASHUrlHelpers::FDASHMediaURL>& InCandidateURLs, const TArray<TSharedPtrTS<FDashMPD_UrlQueryInfoType>>& InUrlQueries, const FString& InTemplateURL);`
- L252 _private prototype_ `bool PrepareDownloadURLs(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& InOutSegmentInfo, const TArray<TSharedPtrTS<FDashMPD_SegmentBaseType>>& SegmentBase);`
- L253 _private prototype_ `bool PrepareDownloadURLs(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& InOutSegmentInfo, const TArray<TSharedPtrTS<FDashMPD_SegmentTemplateType>>& SegmentTemplate);`
- L254 _private prototype_ `FString ApplyTemplateStrings(FString TemplateURL, int64 InNumber, int64 InTime, int64 InSubIndex);`
- L255 _private prototype_ `void CollectInbandEventStreams(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& InOutSegmentInfo);`
- L256 _private prototype_ `void SetupProducerReferenceTimeInfo(IPlayerSessionServices* PlayerSessionServices, FSegmentInformationCommon& InOutSegmentInfo);`
- L258 _private prototype_ `void SegmentIndexDownloadComplete(TSharedPtrTS<FMPDLoadRequestDASH> Request, bool bSuccess);`
- L260 _private member_ `TWeakPtrTS<FDashMPD_RepresentationType> Representation;`
- L261 _private member_ `FStreamCodecInformation CodecInfo;`
- L262 _private member_ `FString ID;`
- L263 _private member_ `int32 Bitrate = MAX_int32;`
- L264 _private member_ `int32 QualityIndex = -1;`
- L265 _private member_ `int32 SelectionPriority = 1;`
- L266 _private member_ `bool bIsUsable = false;`
- L267 _private member_ `bool bIsEnabled = true;`
- L268 _private member_ `TMediaOptionalValue<bool> bAvailableAsLowLatency;`
- L269 _private member_ `bool bWarnedAboutTimelineStartGap = false;`
- L270 _private member_ `bool bWarnedAboutTimelineNoTAfterNegativeR = false;`
- L271 _private member_ `bool bWarnedAboutTimelineNumberOverflow = false;`
- L272 _private member_ `bool bWarnedAboutInconsistentNumbering = false;`
- L273 _private member_ `bool bWarnedAboutTimelineOverlap = false;`
- L274 _private member_ `bool bWarnedAboutTimescale = false;`
- L275 _private member_ `bool bWarnedAboutInconsistentAvailabilityTimeComplete = false;`
- L277 _private member_ `bool bNeedsSegmentIndex = true;`
- L278 _private member_ `TSharedPtr<MP4Boxes::FMP4BoxSIDX, ESPMode::ThreadSafe> SIDXBox;`
- L279 _private member_ `TSharedPtrTS<const IParserMKV> SegmentMKV;`
- L280 _private member_ `int64 SegmentIndexRangeStart = 0;`
- L281 _private member_ `int64 SegmentIndexRangeSize = 0;`
- L282 _private member_ `TSharedPtrTS<FMPDLoadRequestDASH> PendingSegmentIndexLoadRequest;`
- L283 _private member_ `FString StreamMimeType;`
- L284 _private member_ `EStreamContainerType StreamContainerType = EStreamContainerType::Undefined;`
- L286 _private member_ `bool bIsSideloadedSubtitle = false;`
- L288 _private member_ `TArray<FProducerReferenceTimeInfo> ProducerReferenceTimeInfos;`

#### enum `Electra::FManifestDASHInternal::FRepresentation::ESearchResult`  
`enum ESearchResult`  
_L190-197_
- L192 _public enumerator_ `Found` — Found
- L193 _public enumerator_ `PastEOS` — Media is shorter than the period and no segment exists for the specified local time.
- L194 _public enumerator_ `NeedElement` — An additional element is needed that must be loaded first. Execute all returned load requests and try again later.
- L195 _public enumerator_ `BadType` — Representation is bad for some reason, most likely because it uses <SegmentList> addressing which is not supported.
- L196 _public enumerator_ `Gone` — Underlying MPD Representation (held by a weak pointer) has gone and the representation is no longer accessible.

#### enum `Electra::FManifestDASHInternal::FRepresentation::EStreamContainerType`  
`enum class EStreamContainerType`  
_L231-236_
- L233 _public enumerator_ `Undefined`
- L234 _public enumerator_ `ISO14496_12`
- L235 _public enumerator_ `Matroska`

#### class `Electra::FManifestDASHInternal::FAdaptationSet`  
`class FAdaptationSet : public IPlaybackAssetAdaptationSet`  
_L291-548_
- inherits: `IPlaybackAssetAdaptationSet`
- L294 _public prototype_ `FAdaptationSet() = default;`
- L295 _public prototype_ `virtual ~FAdaptationSet() = default;`
- L297 _public function_ `const FStreamCodecInformation& GetCodec() const`
- L298 _public function_ `const TArray<TSharedPtrTS<FRepresentation>>& GetRepresentations() const`
- L299 _public function_ `const TArray<FString>& GetRoles() const`
- L300 _public function_ `const TArray<FString>& GetAccessibilities() const`
- L301 _public function_ `const FTimeFraction& GetPAR() const`
- L302 _public function_ `int32 GetMaxBandwidth() const`
- L303 _public function_ `int32 GetSelectionPriority() const`
- L304 _public function_ `bool GetIsUsable() const`
- L305 _public function_ `bool GetIsInSwitchGroup() const`
- L306 _public function_ `bool GetIsSwitchGroup() const`
- L307 _public function_ `const TArray<FLabelElement>& GetLabels() const`
- L309 _public function_ `TSharedPtrTS<FRepresentation> GetRepresentationByUniqueID(const FString& UniqueIdentifier) const`
- L322 _public function_ `void MapRoleAccessibilityToHTML5(FTrackMetadata& InOutMetadata, EStreamType StreamType) const`
- L431 _public function_ `void GetMetaData(FTrackMetadata& OutMetadata, EStreamType StreamType) const`
- L464 _public function_ `FString GetMimeType()`
- L469 _public function_ `FString GetMimeTypeWithCodecs()`
- L478 _public function_ `const TArray<FContentProtection>& GetPossibleContentProtections() const`
- L479 _public function_ `const FString& GetCommonEncryptionScheme() const`
- L480 _public function_ `const FString& GetDefaultKID() const`
- L482 _public function_ `const TArray<FString>& GetSwitchToSetIDs() const`
- L483 _public function_ `const TArray<FString>& GetSwitchedFromSetIDs() const`
- L488 _public function_ `FString GetUniqueIdentifier() const override` — Methods from IPlaybackAssetAdaptationSet
- L492 _public function_ `FString GetListOfCodecs() const override`
- L496 _public function_ `const BCP47::FLanguageTag& GetLanguageTag() const override`
- L500 _public function_ `int32 GetNumberOfRepresentations() const override`
- L504 _public function_ `bool IsLowLatencyEnabled() const override`
- L508 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByIndex(int32 RepresentationIndex) const override`
- L516 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByUniqueIdentifier(const FString& UniqueIdentifier) const override`
- L522 _private member_ `TWeakPtrTS<FDashMPD_AdaptationSetType> AdaptationSet;`
- L523 _private member_ `FStreamCodecInformation Codec;`
- L524 _private member_ `TArray<TSharedPtrTS<FRepresentation>> Representations;`
- L525 _private member_ `TArray<FString> Roles;`
- L526 _private member_ `TArray<FString> Accessibilities;`
- L527 _private member_ `TArray<FLabelElement> Labels;`
- L528 _private member_ `FTimeFraction PAR;`
- L529 _private member_ `BCP47::FLanguageTag LanguageTag;`
- L530 _private member_ `int32 MaxBandwidth = 0;`
- L531 _private member_ `int32 SelectionPriority = 1;`
- L532 _private member_ `int32 UniqueSequentialSetIndex = 0;`
- L533 _private member_ `bool bIsUsable = false;`
- L534 _private member_ `bool bIsEnabled = true;`
- L535 _private member_ `TMediaOptionalValue<bool> bAvailableAsLowLatency;`
- L538 _private member_ `TArray<FContentProtection> PossibleContentProtections;` — Encryption related
- L539 _private member_ `FString CommonEncryptionScheme;`
- L540 _private member_ `FString DefaultKID;`
- L542 _private member_ `TArray<FString> SwitchToSetIDs;` — Switching related
- L543 _private member_ `TArray<FString> SwitchedFromSetIDs;`
- L544 _private member_ `bool bIsInSwitchGroup = false;`
- L545 _private member_ `bool bIsSwitchGroup = false;`
- L547 _private member_ `bool bWarnedAboutInconsistentAvailabilityTimeComplete = false;` — Warnings

#### struct `Electra::FManifestDASHInternal::FAdaptationSet::FContentProtection`  
`struct FContentProtection`  
_L458-463_
- L460 _public member_ `TSharedPtrTS<FDashMPD_DescriptorType> Descriptor;`
- L461 _public member_ `FString DefaultKID;`
- L462 _public member_ `FString CommonScheme;`

#### class `Electra::FManifestDASHInternal::FPeriod`  
`class FPeriod : public ITimelineMediaAsset`  
_L550-714_
- inherits: `ITimelineMediaAsset`
- L553 _public prototype_ `FPeriod() = default;`
- L554 _public prototype_ `virtual ~FPeriod() = default;`
- L556 _public function_ `bool GetHasBeenPrepared() const`
- L560 _public function_ `void SetHasBeenPrepared(bool bPrepared)`
- L565 _public function_ `bool GetHasFollowingPeriod() const`
- L569 _public function_ `void SetHasFollowingPeriod(bool bInHasFollowing)`
- L574 _public function_ `const FString& GetID() const`
- L575 _public function_ `const FTimeValue& GetStart() const`
- L576 _public function_ `const FTimeValue& GetEnd() const`
- L577 _public function_ `bool GetIsEarlyPeriod() const`
- L578 _public function_ `const TArray<TSharedPtrTS<FAdaptationSet>>& GetAdaptationSets() const`
- L580 _public function_ `TSharedPtrTS<FAdaptationSet> GetAdaptationSetByUniqueID(const FString& UniqueID) const`
- L592 _public function_ `TSharedPtrTS<FAdaptationSet> GetAdaptationSetByMPDID(const FString& MPDID) const`
- L606 _public function_ `void EndPresentationAt(const FTimeValue& EndsAt)`
- L632 _public function_ `TSharedPtrTS<FDashMPD_PeriodType> GetMPDPeriod()` — TSharedPtrTS<FRepresentation> GetRepresentationFromAdaptationSetIDs(const FString& AdaptationSetID, const FString& RepresentationID) const { TSharedPtrTS<FAdaptationSet> Adapt = GetAdaptationSetByUniqueID(AdaptationSetID); if (Adapt.IsValid()) { return Adapt->GetRepresentationByUniqueID(RepresentationID); } return nullptr; }
- L637 _public function_ `FTimeRange GetTimeRange() const override` — Methods from ITimelineMediaAsset
- L642 _public function_ `FTimeValue GetDuration() const override`
- L646 _public function_ `FString GetAssetIdentifier() const override`
- L651 _public function_ `FString GetUniqueIdentifier() const override`
- L655 _public function_ `int32 GetNumberOfAdaptationSets(EStreamType OfStreamType) const override`
- L667 _public function_ `TSharedPtrTS<IPlaybackAssetAdaptationSet> GetAdaptationSetByTypeAndIndex(EStreamType OfStreamType, int32 AdaptationSetIndex) const override`
- L683 _public function_ `void GetMetaData(TArray<FTrackMetadata>& OutMetadata, EStreamType OfStreamType) const override`
- L698 _public function_ `void UpdateRunningMetaData(const FString& InKindOfValue, const FVariant& InNewValue) override`
- L703 _private member_ `TArray<TSharedPtrTS<FAdaptationSet>> AdaptationSets;`
- L704 _private member_ `TWeakPtrTS<FDashMPD_PeriodType> Period;`
- L705 _private member_ `FString ID;`
- L706 _private member_ `FTimeValue Start;`
- L707 _private member_ `FTimeValue End;`
- L708 _private member_ `FTimeValue StartAST;`
- L709 _private member_ `FTimeValue EndAST;`
- L710 _private member_ `FTimeValue Duration;`
- L711 _private member_ `bool bIsEarlyPeriod = false;`
- L712 _private member_ `bool bHasFollowingPeriod = false;`
- L713 _private member_ `bool bHasBeenPrepared = false;`

#### enum `Electra::FManifestDASHInternal::EEpicEventType`  
`enum class EEpicEventType`  
_L866-871_
- L868 _public enumerator_ `None`
- L869 _public enumerator_ `Static`
- L870 _public enumerator_ `Dynamic`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Electra`
- L27 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRequestCompleted, TSharedPtrTS<FMPDLoadRequestDASH> , bool );`
- L116 _namespace_ `namespace DASHUrlHelpers` (scope `Electra`)
- L118 _variable_ `const FName SteerOption_ByteRange(TEXT("Byte` (scope `Electra::DASHUrlHelpers`)
- L119 _variable_ `const FName SteerOption_ATO(TEXT("ATO"` (scope `Electra::DASHUrlHelpers`)
- L120 _variable_ `const FName SteerOption_ATOComplete(TEXT("ATOC` (scope `Electra::DASHUrlHelpers`)
- L121 _variable_ `const FName SteerOption_AnnexIRequestHeader(TEXT("Anne` (scope `Electra::DASHUrlHelpers`)
- L129 _prototype_ `bool GetAllCandidateBaseURLs(TArray<FDASHMediaURL>& OutCandidateURLs, TSharedPtrTS<const IDashMPDElement> StartingAt, const FDASHMediaURL& InMPDUrl, bool bIsDVBDash);` (scope `Electra::DASHUrlHelpers`)
- L131 _prototype_ `bool IsAbsoluteURL(const FString& URL);` (scope `Electra::DASHUrlHelpers`)
- L132 _prototype_ `void GetAllHierarchyBaseURLs(IPlayerSessionServices* InPlayerSessionServices, TArray<TSharedPtrTS<const FDashMPD_BaseURLType>>& OutBaseURLs, TSharedPtrTS<const IDashMPDElement> StartingAt);` (scope `Electra::DASHUrlHelpers`)
- L143 _prototype_ `void GetAllHierarchyUrlQueries(TArray<TSharedPtrTS<FDashMPD_UrlQueryInfoType>>& OutUrlQueries, TSharedPtrTS<const IDashMPDElement> StartingAt, EUrlQueryRequestType ForRequestType, bool bInclude2014);` (scope `Electra::DASHUrlHelpers`)
- L144 _prototype_ `FErrorDetail ApplyUrlQueries(IPlayerSessionServices* PlayerSessionServices, const FString& InMPDUrl, FString& InOutURL, FString& OutRequestHeader, const TArray<TSharedPtrTS<FDashMPD_UrlQueryInfoType>>& UrlQueries);` (scope `Electra::DASHUrlHelpers`)
- L145 _prototype_ `bool BuildAbsoluteElementURL(FString& OutURL, FTimeValue& ATO, TMediaOptionalValue<bool>& bATOComplete, const FString& DocumentURL, const TArray<TSharedPtrTS<const FDashMPD_BaseURLType>>& BaseURLs, const FString& ElementURL);` (scope `Electra::DASHUrlHelpers`)
- L146 _prototype_ `FString ApplyAnnexEByteRange(FString InURL, FString InRange, const TArray<TSharedPtrTS<const FDashMPD_BaseURLType>>& OutBaseURLs);` (scope `Electra::DASHUrlHelpers`)
- L147 _prototype_ `FString ApplyAnnexEByteRange(FString InURL, FString InRange, FString InByteRangeParam);` (scope `Electra::DASHUrlHelpers`)
- L329 _function_ `` (scope `Electra::FManifestDASHInternal::FAdaptationSet::MapRoleAccessibilityToHTML5`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/DRM/DRMManager.h` (Private)


#### class `Electra::FDRMManager`  
`class FDRMManager : public TSharedFromThis<FDRMManager, ESPMode::ThreadSafe>, public ElectraCDM::IMediaCDMEventListener`  
_L16-54_
- inherits: `TSharedFromThis<FDRMManager,ESPMode::ThreadSafe>,ElectraCDM::IMediaCDMEventListener`
- L19 _public prototype_ `static TSharedPtrTS<FDRMManager> Create(IPlayerSessionServices* InPlayerSessionServices);`
- L20 _public prototype_ `void Tick();`
- L21 _public prototype_ `void Close();`
- L23 _public prototype_ `FDRMManager(IPlayerSessionServices* InPlayerSessionServices);`
- L24 _public prototype_ `virtual ~FDRMManager();`
- L26 _public prototype_ `void GetCDMCustomJSONPrefixes(const FString& InCDMScheme, const FString& InValue, FString& OutAttributePrefix, FString& OutTextPropertyName, bool& bOutNoNamespaces);`
- L27 _public prototype_ `TSharedPtr<ElectraCDM::IMediaCDMCapabilities, ESPMode::ThreadSafe> GetCDMCapabilitiesForScheme(const FString& InCDMScheme, const FString& InValue, const FString& InAdditionalElements);`
- L29 _public prototype_ `ElectraCDM::ECDMError CreateDRMClient(TSharedPtr<ElectraCDM::IMediaCDMClient, ESPMode::ThreadSafe>& OutClient, const TArray<ElectraCDM::IMediaCDM::FCDMCandidate>& InCandidates);`
- L31 _public prototype_ `virtual void OnCDMEvent(ElectraCDM::IMediaCDMEventListener::ECDMEventType InEventType, TSharedPtr<ElectraCDM::IMediaCDMClient, ESPMode::ThreadSafe> InDrmClient, void* InEventId, const TArray<uint8>& InCustomData) override;`
- L33 _public prototype_ `static FString MakeHexStringFromArray(const TArray<uint8>& InArray);`
- L34 _public prototype_ `static FString MakePrintableStringFromUint32(uint32 InUint32);`
- L47 _private prototype_ `void OnHTTPResourceRequestComplete(TSharedPtrTS<FHTTPResourceRequest> InRequest);`
- L49 _private member_ `FCriticalSection Lock;`
- L50 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L51 _private member_ `ElectraCDM::IMediaCDM::IPlayerSession* Session = nullptr;`
- L52 _private member_ `TArray<TSharedPtrTS<FDRMAsyncRequest>> PendingRequests;`
- L53 _private member_ `TArray<TSharedPtrTS<FDRMAsyncRequest>> CompletedRequests;`

#### struct `Electra::FDRMManager::FDRMAsyncRequest`  
`struct FDRMAsyncRequest : public IHTTPResourceRequestObject`  
_L38-45_
- inherits: `IHTTPResourceRequestObject`
- L40 _public member_ `ElectraCDM::IMediaCDMEventListener::ECDMEventType Event;`
- L41 _public member_ `TWeakPtr<ElectraCDM::IMediaCDMClient, ESPMode::ThreadSafe> Client;`
- L42 _public member_ `TArray<uint8> CustomData;`
- L43 _public member_ `void* EventId = nullptr;`
- L44 _public member_ `TSharedPtrTS<FHTTPResourceRequest> Request;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/HLS/PlaylistHLS.h` (Private)


#### struct `Electra::FServerControlHLS`  
`struct FServerControlHLS`  
_L42-49_
- L44 _public member_ `FTimeValue CanSkipUntil;`
- L45 _public member_ `FTimeValue HoldBack;`
- L46 _public member_ `FTimeValue PartHoldBack;`
- L47 _public member_ `bool bCanSkipDateRanges = false;`
- L48 _public member_ `bool bCanBlockReload = false;`

#### struct `Electra::FStartTimeHLS`  
`struct FStartTimeHLS`  
_L51-55_
- L53 _public member_ `FTimeValue Offset;`
- L54 _public member_ `bool bPrecise = false;`

#### struct `Electra::FMultiVariantPlaylistHLS`  
`struct FMultiVariantPlaylistHLS`  
_L57-274_
- L262 _public member_ `TArray<FPlaylistParserHLS::FVariableSubstitution> VariableSubstitutions;` — Variable names are case sensitive so we use an array instead of a map.
- L263 _public member_ `TArray<FRenditionGroup> RenditionGroupsOfType[4];`
- L264 _public member_ `TArray<TSharedPtrTS<FPathwayStreamInfs>> PathwayStreamInfs;`
- L265 _public member_ `FString URL;`
- L266 _public member_ `FURL_RFC3986 ParsedURL;`
- L268 _public member_ `FServerControlHLS ServerControl;`
- L269 _public member_ `FStartTimeHLS StartTime;`
- L270 _public member_ `FContentSteeringParams ContentSteeringParams;`
- L273 _public member_ `TArray<FStreamInf> InitialStreamInfs;` — Initial bucket for all #EXT-X-STREAM-INF's before grouping into their respective PATHWAY-IDs

#### class `Electra::FMultiVariantPlaylistHLS::FPlaybackAssetRepresentation`  
`class FPlaybackAssetRepresentation : public IPlaybackAssetRepresentation`  
_L59-77_
- inherits: `IPlaybackAssetRepresentation`
- L62 _public prototype_ `virtual ~FPlaybackAssetRepresentation() = default;`
- L63 _public function_ `FString GetUniqueIdentifier() const override`
- L65 _public function_ `const FStreamCodecInformation& GetCodecInformation() const override`
- L67 _public function_ `int32 GetBitrate() const override`
- L69 _public function_ `int32 GetQualityIndex() const override`
- L71 _public function_ `bool CanBePlayed() const override`
- L73 _public member_ `FStreamCodecInformation StreamCodecInformation;`
- L74 _public member_ `FString ID;`
- L75 _public member_ `int32 Bandwidth = 0;`
- L76 _public member_ `int32 QualityIndex = 0;`

#### class `Electra::FMultiVariantPlaylistHLS::FPlaybackAssetAdaptationSet`  
`class FPlaybackAssetAdaptationSet : public IPlaybackAssetAdaptationSet`  
_L79-111_
- inherits: `IPlaybackAssetAdaptationSet`
- L82 _public prototype_ `virtual ~FPlaybackAssetAdaptationSet() = default;`
- L83 _public function_ `FString GetUniqueIdentifier() const override`
- L85 _public function_ `FString GetListOfCodecs() const override`
- L87 _public function_ `const BCP47::FLanguageTag& GetLanguageTag() const override`
- L89 _public function_ `int32 GetNumberOfRepresentations() const override`
- L91 _public function_ `bool IsLowLatencyEnabled() const override`
- L93 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByIndex(int32 InRepresentationIndex) const override`
- L95 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByUniqueIdentifier(const FString& InUniqueIdentifier) const override`
- L107 _public member_ `TArray<TSharedPtrTS<FPlaybackAssetRepresentation>> Representations;`
- L108 _public member_ `BCP47::FLanguageTag LanguageTag;`
- L109 _public member_ `FString ID;`
- L110 _public member_ `FString ListOfCodecs;`

#### struct `Electra::FMultiVariantPlaylistHLS::FRendition`  
`struct FRendition`  
_L114-133_
- L117 _public member_ `FStreamCodecInformation ParsedCodecFromStreamInf;` — Sadly there is no explicit codec. We *TRY* to associate it with a codec from the EXT-X-STREAM-INF, if present.
- L118 _public member_ `FString CodecNameFromStreamInf;`
- L120 _public member_ `FString Name;` — NAME
- L121 _public member_ `BCP47::FLanguageTag LanguageRFC5646;` — LANGUAGE
- L122 _public member_ `BCP47::FLanguageTag AssocLanguageRFC5646;` — ASSOC-LANGUAGE
- L123 _public member_ `FString StableRenditionId;` — STABLE-RENDITION-ID
- L124 _public member_ `FString URI;` — URI
- L125 _public member_ `FString InstreamId;` — INSTREAM-ID
- L126 _public member_ `FString Characteristics;` — CHARACTERISTICS
- L127 _public member_ `int32 SampleRate = 0;` — SAMPLE-RATE
- L128 _public member_ `int32 Channels = 0;` — CHANNELS (first channel count part only)
- L129 _public member_ `int32 BitDepth = 0;` — BIT-DEPTH
- L130 _public member_ `bool bDefault = false;` — DEFAULT
- L131 _public member_ `bool bAutoSelect = false;` — AUTOSELECT
- L132 _public member_ `bool bForced = false;` — FORCED

#### struct `Electra::FMultiVariantPlaylistHLS::FRenditionGroup`  
`struct FRenditionGroup`  
_L135-147_
- L137 _public member_ `TArray<FRendition> Renditions;`
- L138 _public member_ `FString GroupID;` — GROUP-ID
- L139 _public member_ `bool bIsReferenced = false;` — true if referenced by a variant stream, false if not (an orphaned group)
- L142 _public member_ `TArray<FStreamCodecInformation> ParsedCodecsFromStreamInf;` — The CODEC strings applicable to this type of group from the referencing EXT-X-STREAM-INF
- L143 _public member_ `TArray<FString> CodecNamesFromStreamInf;`
- L145 _public function_ `bool operator == (const FString& InGroupID) const`

#### enum `Electra::FMultiVariantPlaylistHLS::ERenditionGroupType`  
`enum class ERenditionGroupType : int32`  
_L148-155_
- L150 _public enumerator_ `Invalid = -1`
- L151 _public enumerator_ `Video = 0`
- L152 _public enumerator_ `Audio = 1`
- L153 _public enumerator_ `Subtitles = 2`
- L154 _public enumerator_ `ClosedCaptions = 3`

#### struct `Electra::FMultiVariantPlaylistHLS::FStreamInf`  
`struct FStreamInf`  
_L157-186_
- L159 _public member_ `TArray<FStreamCodecInformation> ParsedCodecs;`
- L160 _public member_ `TArray<FString> Codecs;` — CODECS
- L161 _public member_ `TArray<FString> SupplementalCodecs;` — SUPPLEMENTAL-CODECS
- L162 _public member_ `FString VideoRange {TEXT("SDR"` — VIDEO-RANGE
- L163 _public member_ `FString URI;` — The associated URI
- L164 _public member_ `FString VideoGroup;` — VIDEO
- L165 _public member_ `FString AudioGroup;` — AUDIO
- L166 _public member_ `FString SubtitleGroup;` — SUBTITLES
- L167 _public member_ `FString ClosedCaptionGroup;` — CLOSED-CAPTIONS
- L168 _public member_ `FString StableVariantId;` — STABLE-VARIANT-ID
- L169 _public member_ `FString PathwayId;` — PATHWAY-ID
- L170 _public member_ `FTimeFraction FrameRate;` — FRAME-RATE
- L171 _public member_ `int64 Bandwidth = -1;` — BANDWIDTH
- L172 _public member_ `int32 ResolutionW = 0;` — RESOLUTION (width)
- L173 _public member_ `int32 ResolutionH = 0;` — RESOLUTION (height)
- L174 _public member_ `float Score = -1.0f;` — SCORE
- L176 _public member_ `int32 NumVideoCodec = 0;` — Number of parsed codecs per type.
- L177 _public member_ `int32 NumAudioCodec = 0;`
- L178 _public member_ `int32 NumSubtitleCodec = 0;`
- L180 _public member_ `FString ID;` — Generated ID
- L182 _public member_ `int32 IndexOfSelfInArray = -1;` — Generated indices
- L183 _public member_ `int32 QualityIndex = 0;`
- L185 _public member_ `bool bReferencesAudioRenditionWithoutCodec = false;` — Temp check

#### struct `Electra::FMultiVariantPlaylistHLS::FVideoVariantGroup`  
`struct FVideoVariantGroup`  
_L188-195_
- L190 _public member_ `TArray<FStreamCodecInformation> ParsedCodecs;`
- L191 _public member_ `TArray<FString> BaseSupplementalCodecs;`
- L192 _public member_ `FString VideoRange;`
- L193 _public member_ `TArray<int32> StreamInfIndices;`
- L194 _public member_ `TArray<int32> SameAsVideoVariantGroupIndex;`

#### struct `Electra::FMultiVariantPlaylistHLS::FAudioVariantGroup`  
`struct FAudioVariantGroup`  
_L197-201_
- L199 _public member_ `TArray<FStreamCodecInformation> ParsedCodecs;`
- L200 _public member_ `TArray<int32> StreamInfIndices;`

#### struct `Electra::FMultiVariantPlaylistHLS::FInternalTrackMetadata`  
`struct FInternalTrackMetadata`  
_L203-235_
- L205 _public member_ `FTrackMetadata Meta;`
- L211 _public member_ `TOptional<FRendition> Rendition;` — If set this is the rendition this has been sourced from. If not set this is generated from a variant.
- L219 _public member_ `bool bIsVariant = false;` — If `true` this indicates that this track is being sourced from a variant and not a rendition. If `false` the track may be sourced from a separate rendition if the URI in the rendition is set, otherwise it is included in the variant.
- L226 _public member_ `int32 AudioVariantGroupIndex = -1;` — Used only when there are audio-only variant streams AND video-only variant streams, in which case this gives the index of the audio-only group we have associated with the video. `bIsVariant` will be `true` when this is set.
- L234 _public member_ `TArray<FString> VideoVariantBaseIDs;` — Used only when there are multiple video groups, aka "angles". Each "angle" is one video track, with the streams in the track metadata being the different quality levels of that "angle". This array contains the variant IDs that correspond to the respective quality level.

#### struct `Electra::FMultiVariantPlaylistHLS::FPathwayStreamInfs`  
`struct FPathwayStreamInfs`  
_L237-250_
- L239 _public member_ `FString PathwayID;`
- L240 _public member_ `TArray<FStreamInf> StreamInfs;`
- L241 _public member_ `TArray<FVideoVariantGroup> VideoVariantGroups;`
- L242 _public member_ `TArray<FAudioVariantGroup> AudioOnlyVariantGroups;`
- L244 _public member_ `TArray<FInternalTrackMetadata> VideoTracks;` — Generated metadata
- L245 _public member_ `TArray<FInternalTrackMetadata> AudioTracks;`
- L246 _public member_ `TArray<FInternalTrackMetadata> SubtitleTracks;`
- L247 _public member_ `TArray<TSharedPtrTS<FPlaybackAssetAdaptationSet>> VideoAdaptationSets;`
- L248 _public member_ `TArray<TSharedPtrTS<FPlaybackAssetAdaptationSet>> AudioAdaptationSets;`
- L249 _public member_ `TArray<TSharedPtrTS<FPlaybackAssetAdaptationSet>> SubtitleAdaptationSets;`

#### struct `Electra::FMultiVariantPlaylistHLS::FContentSteeringParams`  
`struct FContentSteeringParams`  
_L252-259_
- L254 _public member_ `FString PrimaryPathwayId;`
- L255 _public member_ `FString SteeringURI;`
- L256 _public member_ `FString CustomInitialSelectionPriority;`
- L257 _public member_ `bool bQueryBeforeStart = false;`
- L258 _public member_ `bool bHaveContentSteering = false;`

#### struct `Electra::FMediaEncryptionHLS`  
`struct FMediaEncryptionHLS`  
_L277-288_
- L287 _public member_ `TArray<FKeyInfo> KeyInfos;`

#### struct `Electra::FMediaEncryptionHLS::FKeyInfo`  
`struct FKeyInfo`  
_L279-286_
- L281 _public member_ `FString Method;`
- L282 _public member_ `FString URI;`
- L283 _public member_ `FString IV;`
- L284 _public member_ `FString KeyFormat;`
- L285 _public member_ `FString KeyFormatVersions;`

#### struct `Electra::FMediaByteRangeHLS`  
`struct FMediaByteRangeHLS`  
_L290-302_
- L292 _public member_ `int64 NumBytes = -1;`
- L293 _public member_ `int64 Offset = -1;`
- L294 _public function_ `FString GetForHTTP() const`

#### struct `Electra::FMediaInitSegment`  
`struct FMediaInitSegment`  
_L304-309_
- L306 _public member_ `TSharedPtr<FMediaEncryptionHLS, ESPMode::ThreadSafe> Encryption;`
- L307 _public member_ `FString URL;`
- L308 _public member_ `FMediaByteRangeHLS ByteRange;`

#### struct `Electra::FMediaSegmentHLS`  
`struct FMediaSegmentHLS`  
_L311-323_
- L313 _public member_ `TSharedPtr<FMediaInitSegment, ESPMode::ThreadSafe> InitSegment;`
- L314 _public member_ `TSharedPtr<FMediaEncryptionHLS, ESPMode::ThreadSafe> Encryption;`
- L315 _public member_ `FString URL;`
- L316 _public member_ `FMediaByteRangeHLS ByteRange;`
- L317 _public member_ `FTimeValue Duration;`
- L318 _public member_ `FTimeValue ProgramDateTime;`
- L319 _public member_ `int64 MediaSequence = 0;`
- L320 _public member_ `int64 DiscontinuitySequence = 0;`
- L321 _public member_ `uint8 bDiscontinuity : 1 = 0;`
- L322 _public member_ `uint8 bGap : 1 = 0;`

#### struct `Electra::FMediaPlaylistHLS`  
`struct FMediaPlaylistHLS`  
_L325-342_
- L327 _public member_ `FServerControlHLS ServerControl;`
- L328 _public member_ `FStartTimeHLS StartTime;`
- L329 _public member_ `FTimeValue FirstProgramDateTime;`
- L330 _public member_ `FTimeValue TargetDuration;`
- L331 _public member_ `FTimeValue Duration;`
- L332 _public member_ `int64 NextMediaSequence = 0;`
- L333 _public member_ `int64 NextDiscontinuitySequence = 0;`
- L334 _public member_ `FPlaylistParserHLS::EPlaylistType PlaylistType = FPlaylistParserHLS::EPlaylistType::Live;`
- L335 _public member_ `TArray<FMediaSegmentHLS> MediaSegments;`
- L336 _public member_ `bool bHasEndList = false;`
- L337 _public member_ `bool bHasProgramDateTime = false;`
- L339 _public member_ `TArray<FPlaylistParserHLS::FVariableSubstitution> VariableSubstitutions;`
- L340 _public member_ `FString URL;`
- L341 _public member_ `FURL_RFC3986 ParsedURL;`

#### struct `Electra::FMediaPlaylistInformationHLS`  
`struct FMediaPlaylistInformationHLS`  
_L345-360_
- L347 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L348 _public member_ `FString AssetID;`
- L349 _public member_ `FString AdaptationSetID;`
- L350 _public member_ `FString RepresentationID;`
- L351 _public member_ `FString PathwayID;`
- L352 _public member_ `int32 RepresentationBandwidth = 0;`
- L353 _public function_ `bool Equals(const FMediaPlaylistInformationHLS& InOther) const`

#### struct `Electra::FMediaPlaylistAndStateHLS`  
`struct FMediaPlaylistAndStateHLS`  
_L362-455_
- L379 _public member_ `FString URL;` — Media playlist URL as given in the multivariant playlist. This is not necessarily the effective URL.
- L380 _public member_ `TArray<FURL_RFC3986::FQueryParam> MultiVariantURLFragmentComponents;`
- L381 _public member_ `Playlist::FReplayEventParams ReplayEventParams;`
- L384 _public member_ `EPlaylistState PlaylistState = EPlaylistState::NotLoaded;` — Current state of the playlist.
- L386 _public member_ `FTimeValue ResponseDateHeaderTime;` — Time at which the response was received, from the Date HTTP response header
- L388 _public member_ `FTimeValue TimeAtWhichToReload;` — Time at which the playlist needs to be reloaded, if at all.
- L390 _public member_ `bool bIsPrimaryPlaylist = false;` — Whether or not this is the primary variant playlist.
- L392 _public member_ `ELiveUpdateState LiveUpdateState = ELiveUpdateState::Normal;` — State of Live updates
- L394 _public member_ `FMediaPlaylistInformationHLS PlaylistInfo;`
- L396 _public function_ `bool ActivateIsReady()`
- L415 _public function_ `TSharedPtr<FMediaPlaylistHLS, ESPMode::ThreadSafe> GetPlaylist()`
- L421 _public prototype_ `void SetPlaylist(IPlayerSessionServices* InPlayerSessionServices, TSharedPtr<FMediaPlaylistHLS, ESPMode::ThreadSafe> InPlaylist, FTimeValue InNow);`
- L422 _public function_ `void ClearPlaylist()`
- L431 _public function_ `void LoadFailed()`
- L441 _public function_ `FTimeValue GetTimeWhenLoaded() const`
- L448 _private member_ `TSharedPtr<FMediaPlaylistHLS, ESPMode::ThreadSafe> Playlist;` — The loaded playlist.
- L450 _private member_ `FTimeValue TimeWhenLoaded;` — The time when the playlist was loaded and processed.
- L452 _private member_ `int32 ReloadCount = 0;` — Number of times we had to reload before new media segments showed up.
- L454 _private member_ `FCriticalSection PlaylistLock;`

#### enum `Electra::FMediaPlaylistAndStateHLS::EPlaylistState`  
`enum class EPlaylistState`  
_L364-370_
- L366 _public enumerator_ `NotLoaded`
- L367 _public enumerator_ `Requested`
- L368 _public enumerator_ `Loaded`
- L369 _public enumerator_ `Invalid`

#### enum `Electra::FMediaPlaylistAndStateHLS::ELiveUpdateState`  
`enum class ELiveUpdateState`  
_L371-377_
- L373 _public enumerator_ `Normal`
- L374 _public enumerator_ `NotUpdating`
- L375 _public enumerator_ `ReachedEnd`
- L376 _public enumerator_ `Stopped`

#### struct `Electra::FLoadRequestHLSPlaylist`  
`struct FLoadRequestHLSPlaylist`  
_L458-493_
- L460 _public function_ `~FLoadRequestHLSPlaylist()`
- L478 _public member_ `ELoadType LoadType = ELoadType::Undefined;`
- L479 _public member_ `TSharedPtr<FHTTPResourceRequest, ESPMode::ThreadSafe> ResourceRequest;`
- L480 _public member_ `FTimeValue ExecuteAtUTC;`
- L481 _public member_ `int32 Attempt = 1;`
- L482 _public member_ `bool bIsPrimaryPlaylist = false;`
- L483 _public member_ `bool bIsPreStartSteering = false;`
- L484 _public member_ `bool bAddedCMCDParameters = false;`
- L486 _public member_ `FMediaPlaylistInformationHLS PlaylistInfo;`
- L489 _public member_ `TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe> UpdateRequestFor;` — Which previous playlist this is an update request for, if any.
- L492 _public member_ `FTimeValue ResponseDateHeaderTime;` — Time at which the response was received, from the Date HTTP response header

#### enum `Electra::FLoadRequestHLSPlaylist::ELoadType`  
`enum class ELoadType`  
_L469-476_
- L471 _public enumerator_ `Undefined`
- L472 _public enumerator_ `Main`
- L473 _public enumerator_ `Steering`
- L474 _public enumerator_ `Variant`
- L475 _public enumerator_ `InitialVariant`

#### class `Electra::FDRMClientCacheHLS`  
`class FDRMClientCacheHLS`  
_L497-515_
- L500 _public function_ `FDRMClientCacheHLS() : Cache(32)`
- L512 _public prototype_ `FErrorDetail GetClient(FEntry& OutDrmClient, const TSharedPtr<FMediaEncryptionHLS, ESPMode::ThreadSafe>& InEncryption, IPlayerSessionServices* InPlayerSessionServices, const FURL_RFC3986& InPlaylistURL);`
- L514 _private member_ `TLruCache<TSharedPtr<FMediaEncryptionHLS, ESPMode::ThreadSafe>, FEntry> Cache;`

#### struct `Electra::FDRMClientCacheHLS::FEntry`  
`struct FEntry`  
_L504-510_
- L506 _public member_ `TSharedPtr<ElectraCDM::IMediaCDMClient, ESPMode::ThreadSafe> DrmClient;`
- L507 _public member_ `FString DrmMimeType;`
- L508 _public member_ `TArray<uint8> DrmIV;`
- L509 _public member_ `TArray<uint8> DrmKID;`

#### class `Electra::FActiveHLSPlaylist`  
`class FActiveHLSPlaylist : public IManifest`  
_L520-741_
- inherits: `IManifest`
- L523 _public prototype_ `FActiveHLSPlaylist();`
- L524 _public prototype_ `~FActiveHLSPlaylist();`
- L525 _public prototype_ `FErrorDetail Create(TArray<TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe>>& OutPlaylistLoadRequests, IPlayerSessionServices* InPlayerSessionServices, TSharedPtr<FMultiVariantPlaylistHLS, ESPMode::ThreadSafe> InFromMultiVariantPlaylist);`
- L526 _public prototype_ `void UpdateWithMediaPlaylist(TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe> InMediaPlaylist, bool bIsPrimary, bool bIsUpdate);`
- L527 _public prototype_ `void GetNewMediaPlaylistLoadRequests(TArray<TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe>>& OutPlaylistLoadRequests);`
- L528 _public prototype_ `void GetActiveMediaPlaylists(TArray<TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe>>& OutActivePlaylists, const FTimeValue& InNow);`
- L529 _public prototype_ `void GetAllMediaPlaylistLoadRequests(TArray<TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe>>& OutPlaylistLoadRequests, EStreamType InForType);`
- L530 _public prototype_ `void CheckForPathwaySwitch();`
- L532 _public prototype_ `EMediaFormatType GetMediaFormatType() const override;`
- L533 _public prototype_ `bool ReloadsPlaylistPeriodically() const override;`
- L534 _public prototype_ `bool SupportsMultipleTracksPerKind() const override;`
- L535 _public prototype_ `bool OrderOfTracksCanChangeDynamically() const override;`
- L536 _public prototype_ `EType GetPresentationType() const override;`
- L537 _public prototype_ `EReplayEventType GetReplayType() const override;`
- L538 _public prototype_ `TSharedPtrTS<const FLowLatencyDescriptor> GetLowLatencyDescriptor() const override;`
- L539 _public prototype_ `FTimeValue CalculateCurrentLiveLatency(const FTimeValue& InCurrentPlaybackPosition, const FTimeValue& InEncoderLatency, bool bViaLatencyElement) const override;`
- L540 _public prototype_ `FTimeValue GetAnchorTime() const override;`
- L541 _public prototype_ `FTimeRange GetTotalTimeRange() const override;`
- L542 _public prototype_ `FTimeRange GetSeekableTimeRange() const override;`
- L543 _public prototype_ `FTimeRange GetPlaybackRange(EPlaybackRangeType InRangeType) const override;`
- L544 _public prototype_ `FTimeValue GetDuration() const override;`
- L545 _public prototype_ `FTimeValue GetDefaultStartTime() const override;`
- L546 _public prototype_ `void ClearDefaultStartTime() override;`
- L547 _public prototype_ `FTimeValue GetDefaultEndTime() const override;`
- L548 _public prototype_ `void ClearDefaultEndTime() override;`
- L549 _public prototype_ `FTimeValue GetMinBufferTime() const override;`
- L550 _public prototype_ `FTimeValue GetDesiredLiveLatency() const override;`
- L551 _public prototype_ `ELiveEdgePlayMode GetLiveEdgePlayMode() const override;`
- L552 _public prototype_ `TRangeSet<double> GetPossiblePlaybackRates(EPlayRateType InForType) const override;`
- L553 _public prototype_ `TSharedPtrTS<IProducerReferenceTimeInfo> GetProducerReferenceTimeInfo(int64 InID) const override;`
- L554 _public prototype_ `void GetTrackMetadata(TArray<FTrackMetadata>& OutMetadata, EStreamType InStreamType) const override;`
- L555 _public prototype_ `void UpdateRunningMetaData(TSharedPtrTS<FMetadataParser> InUpdatedMetaData) override;`
- L556 _public prototype_ `void UpdateDynamicRefetchCounter() override;`
- L557 _public prototype_ `void PrepareForLooping(int32 InNumLoopsToAdd) override;`
- L558 _public prototype_ `void TriggerClockSync(EClockSyncType InClockSyncType) override;`
- L559 _public prototype_ `void TriggerPlaylistRefresh() override;`
- L560 _public prototype_ `void ReachedStableBuffer() override;`
- L561 _public prototype_ `IStreamReader *CreateStreamReaderHandler() override;`
- L562 _public prototype_ `FResult FindPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L563 _public prototype_ `FResult FindNextPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, TSharedPtrTS<const IStreamSegment> CurrentSegment) override;`
- L565 _public prototype_ `static FErrorDetail DeterminePathwayToUse(IPlayerSessionServices* InPlayerSessionServices, FString& OutPathway, const FString& InCurrentPathway, const TSharedPtr<FMultiVariantPlaylistHLS, ESPMode::ThreadSafe>& InFromMultiVariantPlaylist);`
- L566 _public prototype_ `FErrorDetail PreparePathway(TSharedPtrTS<FMultiVariantPlaylistHLS::FPathwayStreamInfs>& InOutPathway, TSharedPtr<FMultiVariantPlaylistHLS, ESPMode::ThreadSafe> InFromMultiVariantPlaylist);`
- L568 _private prototype_ `ELECTRA_IMPL_DEFAULT_ERROR_METHODS(HLSPlaylistBuilder);`
- L573 _private prototype_ `FErrorDetail CreateTrackMetadata(IPlayerSessionServices* InPlayerSessionServices, TSharedPtrTS<FMultiVariantPlaylistHLS::FPathwayStreamInfs>& InPathway, TSharedPtr<FMultiVariantPlaylistHLS, ESPMode::ThreadSafe> InFromMultiVariantPlaylist, const FInternalBuilder* InBuilder);`
- L574 _private prototype_ `FErrorDetail GetInitialVariantPlaylistLoadRequests(TArray<TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe>>& OutPlaylistLoadRequests, IPlayerSessionServices* InPlayerSessionServices);`
- L736 _private member_ `FCriticalSection RequestedPeriodsLock;`
- L737 _private member_ `TArray<TWeakPtrTS<FPlayPeriod>> RequestedPeriods;`
- L739 _private member_ `TSharedPtr<FTimelineMediaAsset, ESPMode::ThreadSafe> TimelineMediaAsset;`
- L740 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`

#### class `Electra::FActiveHLSPlaylist::FTimelineMediaAsset`  
`class FTimelineMediaAsset : public ITimelineMediaAsset`  
_L576-734_
- inherits: `ITimelineMediaAsset`
- L579 _public prototype_ `virtual ~FTimelineMediaAsset();`
- L580 _public prototype_ `FTimeRange GetTimeRange() const override;`
- L581 _public prototype_ `FTimeValue GetDuration() const override;`
- L582 _public prototype_ `FString GetAssetIdentifier() const override;`
- L583 _public prototype_ `FString GetUniqueIdentifier() const override;`
- L584 _public prototype_ `int32 GetNumberOfAdaptationSets(EStreamType InStreamType) const override;`
- L585 _public prototype_ `TSharedPtrTS<IPlaybackAssetAdaptationSet> GetAdaptationSetByTypeAndIndex(EStreamType InStreamType, int32 InAdaptationSetIndex) const override;`
- L586 _public prototype_ `void GetMetaData(TArray<FTrackMetadata>& OutMetadata, EStreamType InStreamType) const override;`
- L587 _public prototype_ `void UpdateRunningMetaData(const FString& InKindOfValue, const FVariant& InNewValue) override;`
- L589 _public prototype_ `FErrorDetail GetVariantPlaylist(TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe>& OutPlaylistLoadRequest, IPlayerSessionServices* InPlayerSessionServices, EStreamType InStreamType, const TSharedPtrTS<FMultiVariantPlaylistHLS::FPathwayStreamInfs>& InPathway, int32 InTrackIndex, int32 InStreamIndex, int32 InMainTrackIndex, int32 InMainStreamIndex);`
- L590 _public prototype_ `void UpdateWithMediaPlaylist(TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe> InMediaPlaylist, bool bIsPrimary, bool bIsUpdate);`
- L591 _public prototype_ `void GetNewMediaPlaylistLoadRequests(TArray<TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe>>& OutPlaylistLoadRequests);`
- L592 _public prototype_ `void AddNewMediaPlaylistLoadRequests(const TArray<TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe>>& InNewPlaylistLoadRequests);`
- L593 _public prototype_ `void UpdateActiveMediaPlaylists(const TArray<TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe>>& InActiveMediaPlaylist, const FTimeValue& InNow);`
- L595 _public prototype_ `TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe> GetExistingMediaPlaylistFromLoadRequest(TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe> InPlaylistLoadRequest);`
- L596 _public prototype_ `FTimeRange GetPlaybackRangeFromURL(EPlaybackRangeType InRangeType) const;`
- L597 _public prototype_ `FTimeValue CalculatePlaylistTimeOffset(const TSharedPtr<FMediaPlaylistHLS, ESPMode::ThreadSafe>& InPlaylist);`
- L598 _public prototype_ `FTimeValue CalculateStartTime(const TSharedPtr<FMediaPlaylistHLS, ESPMode::ThreadSafe>& InPlaylist);`
- L599 _public prototype_ `FTimeValue GetDesiredLiveLatency() const;`
- L600 _public prototype_ `FTimeRange GetSeekableTimeRange() const;`
- L601 _public prototype_ `FTimeValue CalculateCurrentLiveLatency(const FTimeValue& InCurrentPlaybackPosition, const FTimeValue& InEncoderLatency);`
- L602 _public prototype_ `void UpdateTimelineFromMediaSegment(TSharedPtrTS<FStreamSegmentRequestCommon> InSegment);`
- L603 _public prototype_ `void ResetInternalTimeline();`
- L604 _public prototype_ `void TransformIntoReplayEvent();`
- L605 _public prototype_ `void PrepareReplayEventForLooping(int32 InNumLoopsToAdd);`
- L607 _public function_ `TSharedPtrTS<FMultiVariantPlaylistHLS::FPathwayStreamInfs> GetCurrentPathway() const`
- L611 _public function_ `void SetCurrentPathway(const TSharedPtrTS<FMultiVariantPlaylistHLS::FPathwayStreamInfs>& InNewPathway)`
- L638 _public prototype_ `ESegSearchResult FindSegment(TSharedPtrTS<FStreamSegmentRequestCommon>& OutSegment, FTimeValue& OutTryLater, IPlayerSessionServices* InPlayerSessionServices, const TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe>& InPlaylist, const FSegSearchParam& InParam);`
- L640 _public function_ `FErrorDetail GetLastError() const`
- L643 _public prototype_ `const FMultiVariantPlaylistHLS::FInternalTrackMetadata* GetInternalTrackMetadata(const FString& InForID) const;`
- L644 _public prototype_ `TSharedPtrTS<FMultiVariantPlaylistHLS::FPlaybackAssetAdaptationSet> GetAdaptationSet(const FString& InForID) const;`
- L649 _public function_ `bool GetInitialMediaPlaylistHadEndOfList() const` — Returns `true` if the very first media playlist loaded already had an EXT-X-ENDLIST If this is an EVENT or a Live presentation and it did not, we can tell that if it appears in a playlist reload that we are transitioning from Live to VOD.
- L653 _public member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L655 _public member_ `TSharedPtr<FMultiVariantPlaylistHLS, ESPMode::ThreadSafe> MultiVariantPlaylist;`
- L658 _public member_ `FServerControlHLS ServerControl;` — Metadata from the primary media playlist
- L659 _public member_ `FTimeValue FirstProgramDateTime;`
- L660 _public member_ `FTimeValue InitialFirstProgramDateTime;`
- L661 _public member_ `FTimeValue TargetDuration;`
- L662 _public member_ `FTimeValue Duration;`
- L663 _public member_ `FPlaylistParserHLS::EPlaylistType PlaylistType = FPlaylistParserHLS::EPlaylistType::Live;`
- L664 _public member_ `FPlaylistParserHLS::EPlaylistType InitialPlaylistType = FPlaylistParserHLS::EPlaylistType::Live;`
- L665 _public member_ `bool bHasEndList = false;`
- L666 _public member_ `bool bInitialHasEndList = false;`
- L667 _public member_ `bool bHasProgramDateTime = false;`
- L668 _public member_ `TArray<FURL_RFC3986::FQueryParam> MultiVariantURLFragmentComponents;`
- L669 _public member_ `Playlist::FReplayEventParams ReplayEventParams;`
- L670 _public member_ `FTimeRange DefaultStartAndEndTime;`
- L673 _public member_ `FTimeValue BaseTimeOffset;` — A one-time only established base time to shift the playlist timeline around.
- L675 _public member_ `FTimeValue TimePlaylistTransitionedToStatic;` — The time at which a live playlist was turned into a static one.
- L677 _public member_ `mutable FTimeRange LastKnownTimeRange;` — Holds the last generated time range to be used when a Live presentation transitions to static.
- L704 _public member_ `mutable FInternalMediaTimeline InternalMediaTimeline;`
- L705 _public member_ `mutable FCriticalSection InternalMediaTimelineLock;`
- L708 _public member_ `FCriticalSection MediaPlaylistsLock;`
- L709 _public member_ `TArray<TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe>> MediaPlaylists;`
- L710 _public member_ `TArray<TSharedPtr<FLoadRequestHLSPlaylist, ESPMode::ThreadSafe>> NewMediaPlaylistLoadRequests;`
- L711 _public member_ `FDRMClientCacheHLS LicenseKeyCache;`
- L712 _public member_ `FErrorDetail LastError;`
- L714 _public member_ `TSharedPtrTS<FMultiVariantPlaylistHLS::FPathwayStreamInfs> CurrentPathway;` — The currently active pathway
- L715 _public member_ `FString CurrentPathwayId;`
- L733 _public member_ `FReplayEvent ReplayEvent;`

#### struct `Electra::FActiveHLSPlaylist::FTimelineMediaAsset::FSegSearchParam`  
`struct FSegSearchParam`  
_L616-628_
- L618 _public member_ `IManifest::ESearchType SearchType = IManifest::ESearchType::Closest;`
- L619 _public member_ `FPlayStartPosition Start;`
- L620 _public member_ `int32 QualityIndex = 0;`
- L621 _public member_ `int32 MaxQualityIndex = 0;`
- L622 _public member_ `FTimeValue LastPTS;`
- L623 _public member_ `bool bFrameAccurateSearch = false;`
- L624 _public member_ `FPlayerSequenceState SequenceState;`
- L625 _public member_ `int64 MediaSequenceIndex = -1;`
- L626 _public member_ `int64 DiscontinuityIndex = -1;`
- L627 _public member_ `int32 LocalPosition = -1;`

#### enum `Electra::FActiveHLSPlaylist::FTimelineMediaAsset::ESegSearchResult`  
`enum class ESegSearchResult`  
_L629-637_
- L631 _public enumerator_ `Failed`
- L632 _public enumerator_ `Found`
- L633 _public enumerator_ `PastEOS`
- L634 _public enumerator_ `BeforeStart`
- L635 _public enumerator_ `Ended`
- L636 _public enumerator_ `UnsupportedDRM`

#### struct `Electra::FActiveHLSPlaylist::FTimelineMediaAsset::FInternalMediaTimeline`  
`struct FInternalMediaTimeline`  
_L680-703_
- desc: Timestamps from the media segment, used with non-PDT Live streams
- L682 _public function_ `void ResyncNeeded()`
- L692 _public member_ `FTimeValue MediaSegmentBaseTime;` — Running values as received with every media segment (if reporting is enabled)
- L693 _public member_ `FTimeValue AvailableDurationUntilEnd;`
- L694 _public member_ `FTimeValue TimeWhenLoaded;`
- L697 _public member_ `FTimeValue InitialMediaSegmentBaseTime;` — Initial one-time set values after a seek.
- L698 _public member_ `FTimeValue InitialAvailableDurationUntilEnd;`
- L699 _public member_ `FTimeValue InitialTimeWhenLoaded;`
- L700 _public member_ `FTimeValue InitialOffsetFromNow;`
- L701 _public member_ `bool bNeedResync = false;`
- L702 _public member_ `bool bLockInitial = true;`

#### struct `Electra::FActiveHLSPlaylist::FTimelineMediaAsset::FReplayEvent`  
`struct FReplayEvent`  
_L717-732_
- L719 _public member_ `FTimeValue BaseStartTime;`
- L720 _public member_ `FTimeValue OriginalBaseTimeOffset;`
- L721 _public member_ `FTimeValue SuggestedPresentationDelay;`
- L722 _public member_ `bool bIsReplay = false;`
- L723 _public member_ `bool bIsStaticEvent = false;`
- L724 _public function_ `void Reset()`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Electra`
- L25 _namespace_ `namespace HLS` (scope `Electra`)
- L27 _variable_ `const FName OptionKeyPlaylistLoadConnectTimeout(TEXT("play` (scope `Electra::HLS`)
- L28 _variable_ `const FName OptionKeyPlaylistLoadNoDataTimeout(TEXT("play` (scope `Electra::HLS`)
- L29 _variable_ `const FName OptionKeyPlaylistReloadConnectTimeout(TEXT("play` (scope `Electra::HLS`)
- L30 _variable_ `const FName OptionKeyPlaylistReloadNoDataTimeout(TEXT("play` (scope `Electra::HLS`)
- L32 _variable_ `const FTimeValue kProgramDateTimeGapThreshold(0.5);` (scope `Electra::HLS`)
- L34 _variable_ `const int32 ERRCODE_MAIN_PLAYLIST_DOWNLOAD_FAILED = 1;` (scope `Electra::HLS`)
- L35 _variable_ `const int32 ERRCODE_PLAYLIST_PARSING_FAILED = 2;` (scope `Electra::HLS`)
- L36 _variable_ `const int32 ERRCODE_PLAYLIST_SETUP_FAILED = 3;` (scope `Electra::HLS`)
- L37 _variable_ `const int32 ERRCODE_PLAYLIST_NO_SUPPORTED_DRM = 4;` (scope `Electra::HLS`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/HLS/PlaylistHandlerHLS.h` (Private)


#### class `Electra::IPlaylistHandlerHLS`  
`class IPlaylistHandlerHLS : public IPlaylistReader`  
_L13-19_
- inherits: `IPlaylistReader`
- L16 _public prototype_ `static TSharedPtrTS<IPlaylistReader> Create(IPlayerSessionServices* PlayerSessionServices);`
- L18 _public prototype_ `virtual ~IPlaylistHandlerHLS() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/HLS/PlaylistParserHLS.h` (Private)


#### class `Electra::FPlaylistParserHLS`  
`class FPlaylistParserHLS`  
_L14-262_
- L17 _public prototype_ `FPlaylistParserHLS() = default;`
- L18 _public prototype_ `FErrorDetail Parse(const FString& InM3U8, const FString& InEffectiveURL, const TArray<FElectraHTTPStreamHeader>& InResponseHeaders);`
- L27 _public function_ `const FString& GetURL() const`
- L30 _public function_ `const TArray<FElectraHTTPStreamHeader>& GetResponseHeaders() const`
- L33 _public function_ `bool IsMultiVariantPlaylist() const`
- L36 _public function_ `bool IsVariantPlaylist() const`
- L39 _public function_ `EPlaylistType GetPlaylistType() const`
- L42 _public function_ `bool HasEndList() const`
- L45 _public function_ `bool HasProgramDateTime() const`
- L48 _public function_ `bool UsesContentSteering() const`
- L151 _public function_ `const TArray<TUniquePtr<FElement>>& GetElements() const`
- L154 _public function_ `bool GetQueryParam(FString& OutValue, const FString& InParam) const`
- L168 _public prototype_ `bool Validate_EXT_X_DEFINE(FErrorDetail& OutError, const TUniquePtr<FElement>& InElement);` — Validation methods
- L171 _private function_ `static bool IsNewline(const StringHelpers::FStringIterator& InOutIt)`
- L175 _private function_ `static bool SkipWhitespace(StringHelpers::FStringIterator& InOutIt)`
- L183 _private function_ `static bool SkipWhitespaceAndEOL(StringHelpers::FStringIterator& InOutIt)`
- L191 _private function_ `static bool SkipUntilEOL(StringHelpers::FStringIterator& InOutIt)`
- L214 _private prototype_ `EParseState ParseEXT(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L215 _private prototype_ `EParseState ParseEXTINF(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L216 _private prototype_ `EParseState ParseEXT_X_PLAYLIST_TYPE(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L217 _private prototype_ `EParseState ParseEXT_X_ENDLIST(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L218 _private prototype_ `EParseState ParseEXT_X_MEDIA(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L219 _private prototype_ `EParseState ParseEXT_X_TARGETDURATION(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L220 _private prototype_ `EParseState ParseEXT_X_MEDIA_SEQUENCE(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L221 _private prototype_ `EParseState ParseEXT_X_DISCONTINUITY_SEQUENCE(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L222 _private prototype_ `EParseState ParseEXT_X_MAP(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L223 _private prototype_ `EParseState ParseEXT_X_PROGRAM_DATE_TIME(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L224 _private prototype_ `EParseState ParseEXT_X_STREAM_INF(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L225 _private prototype_ `EParseState ParseEXT_X_DISCONTINUITY(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L226 _private prototype_ `EParseState ParseEXT_X_BYTERANGE(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L227 _private prototype_ `EParseState ParseEXT_X_KEY(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L228 _private prototype_ `EParseState ParseEXT_X_I_FRAME_STREAM_INF(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L229 _private prototype_ `EParseState ParseEXT_X_START(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L230 _private prototype_ `EParseState ParseEXT_X_DEFINE(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L231 _private prototype_ `EParseState ParseEXT_X_GAP(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L232 _private prototype_ `EParseState ParseEXT_X_SESSION_KEY(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L233 _private prototype_ `EParseState ParseEXT_X_CONTENT_STEERING(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L234 _private prototype_ `EParseState ParseEXT_X_SERVER_CONTROL(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L235 _private prototype_ `EParseState ParseEXT_X_SESSION_DATA(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L236 _private prototype_ `EParseState ParseEXTOther(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt);`
- L243 _private prototype_ `EParseState ParseEXT_X_Common(FErrorDetail& OutErr, StringHelpers::FStringIterator& InOutIt, EAttrType AttributeType, EExtTag InTag, EPlaylistTagType InTagType);`
- L245 _private prototype_ `bool ParseOneAttribute(FErrorDetail& OutErr, FString& OutValue, bool& bOutWasQuoted, TArray<FString>* OutSubstitutions, StringHelpers::FStringIterator& InOutIt);`
- L246 _private prototype_ `bool ParseAttributes(FErrorDetail& OutErr, TUniquePtr<FElement>& InOutElement, StringHelpers::FStringIterator& InOutIt);`
- L247 _private prototype_ `bool ParseElementValue(FErrorDetail& OutErr, TUniquePtr<FElement>& InOutElement, StringHelpers::FStringIterator& InOutIt);`
- L250 _private member_ `TArray<Electra::FURL_RFC3986::FQueryParam> QueryParameters;` — The query parameters from the playlist URL. Use an array over a map to maintain case!
- L251 _private member_ `TArray<FElectraHTTPStreamHeader> ResponseHeaders;`
- L252 _private member_ `FString PlaylistURL;`
- L254 _private member_ `TArray<TUniquePtr<FElement>> Elements;`
- L255 _private member_ `bool bHaveMultiVariantTag = false;`
- L256 _private member_ `bool bHaveVariantTag = false;`
- L257 _private member_ `bool bHaveEndList = false;`
- L258 _private member_ `bool bHaveProgramDateTime = false;`
- L259 _private member_ `bool bHaveDefine = false;`
- L260 _private member_ `bool bHaveContentSteering = false;`
- L261 _private member_ `EPlaylistType PlaylistType = EPlaylistType::Live;`

#### enum `Electra::FPlaylistParserHLS::EPlaylistType`  
`enum class EPlaylistType`  
_L20-25_
- L22 _public enumerator_ `VOD`
- L23 _public enumerator_ `Event`
- L24 _public enumerator_ `Live`

#### enum `Electra::FPlaylistParserHLS::EExtTag`  
`enum class EExtTag`  
_L51-83_
- L53 _public enumerator_ `EXTINF`
- L54 _public enumerator_ `EXT_X_PLAYLIST_TYPE`
- L55 _public enumerator_ `EXT_X_ENDLIST`
- L56 _public enumerator_ `EXT_X_MEDIA`
- L57 _public enumerator_ `EXT_X_TARGETDURATION`
- L58 _public enumerator_ `EXT_X_MEDIA_SEQUENCE`
- L59 _public enumerator_ `EXT_X_DISCONTINUITY_SEQUENCE`
- L60 _public enumerator_ `EXT_X_MAP`
- L61 _public enumerator_ `EXT_X_PROGRAM_DATE_TIME`
- L62 _public enumerator_ `EXT_X_STREAM_INF`
- L63 _public enumerator_ `EXT_X_DISCONTINUITY`
- L64 _public enumerator_ `EXT_X_BYTERANGE`
- L65 _public enumerator_ `EXT_X_KEY`
- L66 _public enumerator_ `EXT_X_I_FRAME_STREAM_INF`
- L67 _public enumerator_ `EXT_X_INDEPENDENT_SEGMENTS`
- L68 _public enumerator_ `EXT_X_START`
- L69 _public enumerator_ `EXT_X_DEFINE`
- L70 _public enumerator_ `EXT_X_GAP`
- L71 _public enumerator_ `EXT_X_I_FRAMES_ONLY`
- L72 _public enumerator_ `EXT_X_PART_INF`
- L73 _public enumerator_ `EXT_X_SERVER_CONTROL`
- L74 _public enumerator_ `EXT_X_BITRATE`
- L75 _public enumerator_ `EXT_X_PART`
- L76 _public enumerator_ `EXT_X_DATERANGE`
- L77 _public enumerator_ `EXT_X_SKIP`
- L78 _public enumerator_ `EXT_X_PRELOAD_HINT`
- L79 _public enumerator_ `EXT_X_RENDITION_REPORT`
- L80 _public enumerator_ `EXT_X_SESSION_DATA`
- L81 _public enumerator_ `EXT_X_SESSION_KEY`
- L82 _public enumerator_ `EXT_X_CONTENT_STEERING`

#### struct `Electra::FPlaylistParserHLS::FVariableSubstitution`  
`struct FVariableSubstitution`  
_L85-91_
- L87 _public member_ `FString Name;`
- L88 _public member_ `FString Value;`
- L89 _public function_ `bool operator == (const FString& InName) const`

#### struct `Electra::FPlaylistParserHLS::FAttribute`  
`struct FAttribute`  
_L93-127_
- L95 _public member_ `FString Name;`
- L96 _public member_ `FString Value;`
- L97 _public member_ `bool bWasQuoted = false;`
- L98 _public member_ `TArray<FString> VariableSubstitutions;`
- L100 _public function_ `const FString& GetValue() const`
- L104 _public function_ `bool GetValue(FString& OutValue, const TArray<FPlaylistParserHLS::FVariableSubstitution>& InVariableValues) const`

#### struct `Electra::FPlaylistParserHLS::FElement`  
`struct FElement`  
_L129-149_
- L131 _public function_ `FElement(EExtTag InTag) : Tag(InTag)`
- L132 _public member_ `EExtTag Tag;`
- L133 _public member_ `TArray<FAttribute> AttributeList;`
- L134 _public member_ `FAttribute ElementValue;`
- L135 _public member_ `FAttribute URI;`
- L136 _public member_ `FString FullLineAfterTag;`
- L137 _public member_ `bool bHaveDuplicateAttribute = false;`
- L138 _public function_ `const FAttribute* GetAttribute(const TCHAR* const InAttributeName)`

#### enum `Electra::FPlaylistParserHLS::EPlaylistTagType`  
`enum class EPlaylistTagType`  
_L200-205_
- L202 _public enumerator_ `MultiVariantOnly`
- L203 _public enumerator_ `VariantOnly`
- L204 _public enumerator_ `Either`

#### enum `Electra::FPlaylistParserHLS::EParseState`  
`enum class EParseState`  
_L207-212_
- L209 _public enumerator_ `Begin`
- L210 _public enumerator_ `SearchEXT`
- L211 _public enumerator_ `Failed`

#### enum `Electra::FPlaylistParserHLS::EAttrType`  
`enum class EAttrType`  
_L237-242_
- L239 _public enumerator_ `List`
- L240 _public enumerator_ `Element`
- L241 _public enumerator_ `None`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/Manifest.h` (Private)


#### enum `Electra::EMediaFormatType`  
`enum class EMediaFormatType`  
_L20-28_
- L22 _public enumerator_ `Unknown`
- L23 _public enumerator_ `ISOBMFF` — mp4
- L24 _public enumerator_ `HLS` — Apple HLS (HTTP Live Streaming)
- L25 _public enumerator_ `DASH` — MPEG DASH
- L26 _public enumerator_ `MKV` — Matroska / WebM
- L27 _public enumerator_ `MPEGAudio` — MPEG audio (eg .mp3)

#### struct `Electra::FPlayStartOptions`  
`struct FPlayStartOptions`  
_L31-40_
- L33 _public function_ `FPlayStartOptions()`
- L38 _public member_ `FTimeRange PlaybackRange;`
- L39 _public member_ `bool bFrameAccuracy = false;`

#### struct `Electra::FPlayStartPosition`  
`struct FPlayStartPosition`  
_L42-46_
- L44 _public member_ `FTimeValue Time;`
- L45 _public member_ `FPlayStartOptions Options;`

#### struct `Electra::FLowLatencyDescriptor`  
`struct FLowLatencyDescriptor`  
_L48-75_
- L62 _public member_ `FLatency Latency;`
- L63 _public member_ `FPlayRate PlayRate;`
- L65 _public function_ `FTimeValue GetLatencyMin() const`
- L67 _public function_ `FTimeValue GetLatencyMax() const`
- L69 _public function_ `FTimeValue GetLatencyTarget() const`
- L71 _public function_ `FTimeValue GetPlayrateMin() const`
- L73 _public function_ `FTimeValue GetPlayrateMax() const`

#### struct `Electra::FLowLatencyDescriptor::FLatency`  
`struct FLatency`  
_L50-56_
- L52 _public member_ `int64 ReferenceID = -1;`
- L53 _public member_ `FTimeValue Target;`
- L54 _public member_ `FTimeValue Min;`
- L55 _public member_ `FTimeValue Max;`

#### struct `Electra::FLowLatencyDescriptor::FPlayRate`  
`struct FPlayRate`  
_L57-61_
- L59 _public member_ `FTimeValue Min;`
- L60 _public member_ `FTimeValue Max;`

#### struct `Electra::IProducerReferenceTimeInfo`  
`struct IProducerReferenceTimeInfo`  
_L77-89_
- L84 _public prototype_ `virtual FTimeValue GetWallclockTime() const = 0;`
- L85 _public prototype_ `virtual uint64 GetPresentationTime() const = 0;`
- L86 _public prototype_ `virtual uint32 GetID() const = 0;`
- L87 _public prototype_ `virtual EType GetType() const = 0;`
- L88 _public prototype_ `virtual bool GetIsInband() const = 0;`

#### enum `Electra::IProducerReferenceTimeInfo::EType`  
`enum class EType`  
_L79-83_
- L81 _public enumerator_ `Encoder`
- L82 _public enumerator_ `Captured`

#### class `Electra::IStreamSegment`  
`class IStreamSegment : public TSharedFromThis<IStreamSegment, ESPMode::ThreadSafe>`  
_L93-146_
- inherits: `TSharedFromThis<IStreamSegment,ESPMode::ThreadSafe>`
- L96 _public prototype_ `virtual ~IStreamSegment() = default;`
- L102 _public prototype_ `virtual void SetPlaybackSequenceID(uint32 PlaybackSequenceID) = 0;` — Sets a playback sequence ID. This is useful to check the ID later in asynchronously received messages to validate the request still being valid or having become outdated.
- L106 _public prototype_ `virtual uint32 GetPlaybackSequenceID() const = 0;` — Returns the playback sequence ID. See SetPlaybackSequenceID()
- L108 _public prototype_ `virtual void SetExecutionDelay(const FTimeValue& UTCNow, const FTimeValue& ExecutionDelay) = 0;`
- L110 _public prototype_ `virtual FTimeValue GetExecuteAtUTCTime() const = 0;`
- L112 _public prototype_ `virtual EStreamType GetType() const = 0;`
- L117 _public prototype_ `virtual void GetDependentStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutDependentStreams) const = 0;` — Returns a list of dependent streams.
- L123 _public prototype_ `virtual void GetRequestedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutRequestedStreams) = 0;` — Returns a list of requested streams. This must be the initial request that has a list of all the segments of the streams selected for playback.
- L128 _public prototype_ `virtual void GetEndedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutAlreadyEndedStreams) = 0;` — Returns a list of streams, primary or dependent, that are already at EOS in this request.
- L133 _public prototype_ `virtual FTimeValue GetFirstPTS() const = 0;` — Returns the first PTS value as indicated by the media timeline. This should correspond to the actual absolute PTS of the sample.
- L138 _public prototype_ `virtual FTimeRange GetTimeRange() const = 0;` — Returns the time range this request covers.
- L140 _public prototype_ `virtual int32 GetQualityIndex() const = 0;`
- L141 _public prototype_ `virtual int32 GetBitrate() const = 0;`
- L143 _public prototype_ `virtual void GetDownloadStats(Metrics::FSegmentDownloadStats& OutStats) const = 0;`
- L145 _public prototype_ `virtual bool GetStartupDelay(FTimeValue& OutStartTime, FTimeValue& OutTimeIntoSegment, FTimeValue& OutSegmentDuration) const = 0;`

#### class `Electra::IManifest`  
`class IManifest : public TMediaNoncopyable<IManifest>`  
_L150-607_
- inherits: `TMediaNoncopyable<IManifest>`
- L274 _public prototype_ `virtual ~IManifest() = default;`
- L281 _public prototype_ `virtual EMediaFormatType GetMediaFormatType() const = 0;` — Returns the media format of this presentation.
- L283 _public prototype_ `virtual bool ReloadsPlaylistPeriodically() const = 0;` — Returns true if the media playlist will be updated periodically, false if not.
- L285 _public prototype_ `virtual bool SupportsMultipleTracksPerKind() const = 0;` — Returns true if there could be more than one track per kind to switch between.
- L287 _public prototype_ `virtual bool OrderOfTracksCanChangeDynamically() const = 0;` — Returns true if during playback the order of tracks can change (like in DASH period transitions).
- L290 _public prototype_ `virtual EType GetPresentationType() const = 0;` — Returns the type of this presentation, either on-demand or live.
- L293 _public prototype_ `virtual EReplayEventType GetReplayType() const = 0;` — Returns the type of replay event.
- L296 _public prototype_ `virtual TSharedPtrTS<const FLowLatencyDescriptor> GetLowLatencyDescriptor() const = 0;` — Returns the low-latency descriptor, if any. May return nullptr if there is none.
- L299 _public prototype_ `virtual FTimeValue CalculateCurrentLiveLatency(const FTimeValue& InCurrentPlaybackPosition, const FTimeValue& InEncoderLatency, bool bViaLatencyElement) const = 0;` — Calculates the live latency given the current playback position and optional encoder latency.
- L314 _public prototype_ `virtual FTimeValue GetAnchorTime() const = 0;` — Returns the time value the timeline is anchored at. Usually this is a UTC timestamp at which the presentation began but it could literally be anything. All time values are absolute and have this anchor added in. @return The time this presentation timeline is anchored at.
- L322 _public prototype_ `virtual FTimeRange GetTotalTimeRange() const = 0;` — Returns the total time range of the timeline, including the end time of the last sample to which the player will not be able to seek to. @return Time range of assets on the timeline.
- L331 _public prototype_ `virtual FTimeRange GetSeekableTimeRange() const = 0;` — Returns the seekable range of the timeline, which is a subset of the total time range. Playback can start at any point in the seekable range with additional constraints imposed by the format. @return Time range in which playback can start.
- L355 _public prototype_ `virtual FTimeRange GetPlaybackRange(EPlaybackRangeType InRangeType) const = 0;` — Returns the playback range on the timeline, which is a subset of the total time range. This may be set through manifest internal means or by URL fragment parameters where permissable (eg. example.mp4#t=22,50). If start or end are not specified they will be set to invalid. @return Optionally set time range to which playback is restricted.
- L364 _public prototype_ `virtual FTimeValue GetDuration() const = 0;` — Returns the duration of the assets on the timeline. Typically this is the difference of the end and start values of the total time range unless this is a Live presentation for which the duration will be set to infinite. @return Duration of the timeline.
- L370 _public prototype_ `virtual FTimeValue GetDefaultStartTime() const = 0;` — Returns the playback start time as defined by the presentation itself. If the presentation has no preferred start time an invalid value is returned.
- L375 _public prototype_ `virtual void ClearDefaultStartTime() = 0;` — Clears the internal default start time so it will not be used again.
- L381 _public prototype_ `virtual FTimeValue GetDefaultEndTime() const = 0;` — Returns the playback end time as defined by the presentation itself. If the presentation has no preferred end time an invalid value is returned.
- L386 _public prototype_ `virtual void ClearDefaultEndTime() = 0;` — Clears the internal default end time so it will not be used again.
- L389 _public prototype_ `virtual void GetTrackMetadata(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const = 0;` — Returns track metadata. For period based presentations the streams can be different per period in which case the metadata of the first period is returned.
- L392 _public prototype_ `virtual void UpdateRunningMetaData(TSharedPtrTS<FMetadataParser> InUpdatedMetaData) = 0;` — Updates long term playback metadata (mostly for audio casts)
- L395 _public prototype_ `virtual FTimeValue GetMinBufferTime() const = 0;`
- L398 _public prototype_ `virtual TSharedPtrTS<IProducerReferenceTimeInfo> GetProducerReferenceTimeInfo(int64 ID) const = 0;`
- L400 _public prototype_ `virtual FTimeValue GetDesiredLiveLatency() const = 0;`
- L411 _public prototype_ `virtual ELiveEdgePlayMode GetLiveEdgePlayMode() const = 0;`
- L419 _public prototype_ `virtual TRangeSet<double> GetPossiblePlaybackRates(EPlayRateType InForType) const = 0;`
- L424 _public prototype_ `virtual void UpdateDynamicRefetchCounter() = 0;` — Needs to be called when the user has explicitly triggered a seek, including a programmatic loop back to the beginning. For presentations with dynamic content changes (eg. DASH xlink:onRequest Periods) the content may need to be updated again. This is different to internal seeking for retry purposes where content will not be re-resolved.
- L431 _public prototype_ `virtual void PrepareForLooping(int32 InNumLoopsToAdd) = 0;` — Prepares the manifest for looping. This does not normally do anything except for when this is a replay, in which case the internal timestamps may be modified such that the entire presentation is shifted into the future by one presentation duration.
- L438 _public prototype_ `virtual void TriggerClockSync(EClockSyncType InClockSyncType) = 0;`
- L440 _public prototype_ `virtual void TriggerPlaylistRefresh() = 0;`
- L442 _public prototype_ `virtual void ReachedStableBuffer() = 0;`
- L448 _public prototype_ `virtual IStreamReader* CreateStreamReaderHandler() = 0;` — Stream fragment reader Create a stream reader handler suitable for streams from this manifest.
- L603 _public prototype_ `virtual FResult FindPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, const FPlayStartPosition& StartPosition, ESearchType SearchType) = 0;` — Finds the playback period the specified start time falls into.
- L606 _public prototype_ `virtual FResult FindNextPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, TSharedPtrTS<const IStreamSegment> CurrentSegment) = 0;` — Locates the period following the given segment.

#### enum `Electra::IManifest::EType`  
`enum class EType`  
_L153-157_
- L155 _public enumerator_ `OnDemand` — An on-demand presentation
- L156 _public enumerator_ `Live` — A live presentation

#### enum `Electra::IManifest::EReplayEventType`  
`enum class EReplayEventType`  
_L159-163_
- L161 _public enumerator_ `NoReplay`
- L162 _public enumerator_ `IsReplay`

#### enum `Electra::IManifest::ESearchType`  
`enum class ESearchType`  
_L165-173_
- L167 _public enumerator_ `Closest` — Find closest match
- L168 _public enumerator_ `After` — Find match only for fragment times >= target time
- L169 _public enumerator_ `Before` — Find match only for fragment times <= target time
- L170 _public enumerator_ `StrictlyAfter` — Match must be strictly after (>). Used to locate the next segment.
- L171 _public enumerator_ `StrictlyBefore` — Match must be strictly before (<). Used to locate the previous segment.
- L172 _public enumerator_ `Same` — Match must be for the same fragment

#### class `Electra::IManifest::FResult`  
`class FResult`  
_L175-270_
- L188 _public function_ `FResult(EType InType = EType::NotFound) : Type(InType)`
- L192 _public function_ `FResult& RetryAfterMilliseconds(int32 Milliseconds)`
- L198 _public function_ `FResult& RetryAfter(const FTimeValue& InAfter)`
- L207 _public function_ `FResult& SetErrorDetail(const FErrorDetail& InErrorDetail)`
- L212 _public function_ `EType GetType() const`
- L216 _public function_ `bool IsSuccess() const`
- L220 _public function_ `const FTimeValue& GetRetryAgainAtTime() const`
- L224 _public function_ `const FErrorDetail& GetErrorDetail() const`
- L228 _public function_ `static const TCHAR* GetTypeName(EType s)`
- L267 _protected member_ `EType Type;`
- L268 _protected member_ `FTimeValue RetryAgainAtTime;`
- L269 _protected member_ `FErrorDetail ErrorDetail;`

#### enum `Electra::IManifest::FResult::EType`  
`enum class EType`  
_L178-187_
- L180 _public enumerator_ `Found` — Found
- L181 _public enumerator_ `NotFound` — Not found
- L182 _public enumerator_ `PastEOS` — Time is beyond the duration
- L183 _public enumerator_ `BeforeStart` — Time is before the start time
- L184 _public enumerator_ `TryAgainLater` — Not found at the moment. Playlist load may be pending
- L185 _public enumerator_ `NotLoaded` — Not loaded (playlist has not been requested)
- L186 _public enumerator_ `Error` — An unrecoverable error

#### enum `Electra::IManifest::EPlaybackRangeType`  
`enum class EPlaybackRangeType`  
_L333-346_
- L339 _public enumerator_ `TemporaryPlaystartRange` — Initial playback range as may be defined using `#t=s,e` URL fragment parameter. This is used only on first playstart and is canceled when a Seek() is performed.
- L345 _public enumerator_ `LockedPlaybackRange` — Fixed playback range that may be defined using `#r=s,e` URL fragment parameter. This is a non-standard parameter. The specified range will be locked in place and any Seek() can only be performed inside this range.

#### enum `Electra::IManifest::ELiveEdgePlayMode`  
`enum class ELiveEdgePlayMode`  
_L402-410_
- L405 _public enumerator_ `Never` — Never play on the Live edge.
- L407 _public enumerator_ `Default` — Play on Live edge on start, disable when a Pause() or Seek() is issued unless it's a seek to Live edge.
- L409 _public enumerator_ `Always` — Always play on the Live edge (stream can't or should not be paused)

#### enum `Electra::IManifest::EPlayRateType`  
`enum class EPlayRateType`  
_L414-418_
- L416 _public enumerator_ `UnthinnedRate`
- L417 _public enumerator_ `ThinnedRate`

#### enum `Electra::IManifest::EClockSyncType`  
`enum class EClockSyncType`  
_L433-437_
- L435 _public enumerator_ `Recommended`
- L436 _public enumerator_ `Required`

#### class `Electra::IManifest::IPlayPeriod`  
`class IPlayPeriod : private TMediaNoncopyable<IPlayPeriod>`  
_L455-600_
- inherits: `TMediaNoncopyable<IPlayPeriod>`
- desc: Interface to a playback period.
- L458 _public prototype_ `virtual ~IPlayPeriod() = default;`
- L460 _public prototype_ `virtual void SetStreamPreferences(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) = 0;`
- L470 _public prototype_ `virtual EReadyState GetReadyState() = 0;`
- L471 _public prototype_ `virtual void Load() = 0;`
- L472 _public prototype_ `virtual void PrepareForPlay() = 0;`
- L475 _public prototype_ `virtual int64 GetDefaultStartingBitrate() const = 0;` — Returns the bitrate of the default stream (usually the first one specified).
- L483 _public prototype_ `virtual TSharedPtrTS<FBufferSourceInfo> GetSelectedStreamBufferSourceInfo(EStreamType StreamType) = 0;` — Returns the selected stream's buffer source information for the specified stream type after setting the stream preferences via SetStreamPreferences() and a following PrepareToPlay(). Valid only when GetReadyState() returns IsReady. If a nullptr is returned there is no stream for this type.
- L485 _public prototype_ `virtual FString GetSelectedAdaptationSetID(EStreamType StreamType) = 0;`
- L503 _public prototype_ `virtual ETrackChangeResult ChangeTrackStreamPreference(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) = 0;` — Changes the specified track over to one of the passed attributes. If Changed is returned the new selection has been made active and the new FBufferSourceInfo can be fetched with GetSelectedStreamBufferSourceInfo(). If NotChanged is returned no change has been made, either because the track is already selected or no (better) match could be made. If NewPeriodNeeded is returned this play period cannot perform track changing on the fly and a new period with new stream preferences must be created instead.
- L510 _public prototype_ `virtual TSharedPtrTS<ITimelineMediaAsset> GetMediaAsset() const = 0;` — Returns the media asset for this play period. @return Pointer to the media asset.
- L518 _public prototype_ `virtual void SelectStream(const FString& AdaptationSetID, const FString& RepresentationID, int32 QualityIndex, int32 MaxQualityIndex) = 0;` — Selects a specific stream to be used for all next segment downloads. @param AdaptationSetID @param RepresentationID
- L530 _public prototype_ `virtual void TriggerInitSegmentPreload(const TArray<FInitSegmentPreload>& InitSegmentsToPreload) = 0;` — Triggers pre-loading of initialization segments. This may be called multiple times with different streams. The implementation needs to keep track of which init segments have already been loaded.
- L543 _public prototype_ `virtual FResult GetStartingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) = 0;` — Sets up a starting segment request to begin playback at the specified time. The streams selected through SelectStream() will be used. @param OutSegment @param InSequenceState @param StartPosition @param SearchType @return
- L550 _public prototype_ `virtual FResult GetContinuationSegment(TSharedPtrTS<IStreamSegment>& OutSegment, EStreamType StreamType, const FPlayerSequenceState& SequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) = 0;` — Same as GetStartingSegment() except this is for a specific stream (video, audio, ...) only. To be used when a track (language) change is made and a new segment is needed at the current playback position.
- L563 _public prototype_ `virtual FResult GetLoopingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) = 0;` — Sets up a starting segment request to loop playback to. The streams selected through SelectStream() will be used. @param OutSegment @param InSequenceState @param StartPosition @param SearchType @return
- L574 _public prototype_ `virtual FResult GetNextSegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options) = 0;` — Gets the segment request for the segment following the specified earlier request. @param OutSegment @param CurrentSegment @param Options @return
- L586 _public prototype_ `virtual FResult GetRetrySegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options, bool bReplaceWithFillerData) = 0;` — Gets the segment request for the same segment on a different quality level or CDN. @param OutSegment @param CurrentSegment @param Options @param bReplaceWithFillerData @return
- L594 _public prototype_ `virtual void IncreaseSegmentFetchDelay(const FTimeValue& IncreaseAmount) = 0;` — Called by the ABR to increase the delay in fetching the next segment in case the segment returned a 404 when fetched at the announced availability time. This may reduce 404's on the next segment fetches. @param IncreaseAmount
- L599 _public prototype_ `virtual void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID) = 0;` — Returns the average segment duration.

#### enum `Electra::IManifest::IPlayPeriod::EReadyState`  
`enum class EReadyState`  
_L462-469_
- L464 _public enumerator_ `NotLoaded`
- L465 _public enumerator_ `Loading`
- L466 _public enumerator_ `Loaded`
- L467 _public enumerator_ `Preparing`
- L468 _public enumerator_ `IsReady`

#### enum `Electra::IManifest::IPlayPeriod::ETrackChangeResult`  
`enum class ETrackChangeResult`  
_L487-493_
- L489 _public enumerator_ `Changed`
- L490 _public enumerator_ `NotChanged`
- L491 _public enumerator_ `NewPeriodNeeded`
- L492 _public enumerator_ `StartOver`

#### struct `Electra::IManifest::IPlayPeriod::FInitSegmentPreload`  
`struct FInitSegmentPreload`  
_L520-524_
- L522 _public member_ `FString AdaptationSetID;`
- L523 _public member_ `FString RepresentationID;`

#### class `Electra::FPlaylistMetadataUpdateMessage`  
`class FPlaylistMetadataUpdateMessage : public IPlayerMessage`  
_L613-657_
- inherits: `IPlayerMessage`
- desc: Playlist metadata changed.
- L616 _public function_ `static TSharedPtrTS<IPlayerMessage> Create(FTimeValue InValidFrom, TSharedPtrTS<FMetadataParser> InMetadata, bool bInTriggerInternalRefresh)`
- L622 _public function_ `static const FString& Type()`
- L628 _public function_ `virtual const FString& GetType() const`
- L633 _public function_ `FTimeValue GetValidFrom() const`
- L638 _public function_ `TSharedPtrTS<FMetadataParser> GetMetadata() const`
- L643 _public function_ `bool GetTriggerInternalRefresh() const`
- L649 _private function_ `FPlaylistMetadataUpdateMessage(FTimeValue InValidFrom, TSharedPtrTS<FMetadataParser> InMetadata, bool bInTriggerInternalRefresh) : ValidFrom(InValidFrom) , Metadata(MoveTemp(InMetadata)) , bTriggerInternalRefresh(bInTriggerInternalRefresh)`
- L654 _private member_ `FTimeValue ValidFrom;`
- L655 _private member_ `TSharedPtrTS<FMetadataParser> Metadata;`
- L656 _private member_ `bool bTriggerInternalRefresh;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/PlaybackTimeline.h` (Private)


#### class `Electra::IPlaybackAssetRepresentation`  
`class IPlaybackAssetRepresentation`  
_L11-25_
- L14 _public prototype_ `virtual ~IPlaybackAssetRepresentation() = default;`
- L16 _public prototype_ `virtual FString GetUniqueIdentifier() const = 0;`
- L18 _public prototype_ `virtual const FStreamCodecInformation& GetCodecInformation() const = 0;`
- L20 _public prototype_ `virtual int32 GetBitrate() const = 0;`
- L22 _public prototype_ `virtual int32 GetQualityIndex() const = 0;`
- L24 _public prototype_ `virtual bool CanBePlayed() const = 0;`

#### class `Electra::IPlaybackAssetAdaptationSet`  
`class IPlaybackAssetAdaptationSet`  
_L27-52_
- L30 _public prototype_ `virtual ~IPlaybackAssetAdaptationSet() = default;`
- L39 _public prototype_ `virtual FString GetUniqueIdentifier() const = 0;` — Returns a unique identifier for this adaptation set. This may be a value from the manifest or an internally generated one. NOTE: The identifier is unique only within the owning media asset! @return Unique identifier for this adaptation set with the owning media asset.
- L41 _public prototype_ `virtual FString GetListOfCodecs() const = 0;`
- L43 _public prototype_ `virtual const BCP47::FLanguageTag& GetLanguageTag() const = 0;`
- L45 _public prototype_ `virtual int32 GetNumberOfRepresentations() const = 0;`
- L47 _public prototype_ `virtual bool IsLowLatencyEnabled() const = 0;`
- L49 _public prototype_ `virtual TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByIndex(int32 RepresentationIndex) const = 0;`
- L51 _public prototype_ `virtual TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByUniqueIdentifier(const FString& UniqueIdentifier) const = 0;`

#### class `Electra::ITimelineMediaAsset`  
`class ITimelineMediaAsset`  
_L55-131_
- L58 _public prototype_ `virtual ~ITimelineMediaAsset() = default;`
- L66 _public prototype_ `virtual FTimeRange GetTimeRange() const = 0;` — Returns the time range of this asset on the playback timeline. The timeline anchor time is included in this range. @return Time range of this asset on the playback timeline.
- L75 _public prototype_ `virtual FTimeValue GetDuration() const = 0;` — Returns the duration of this asset, which is typically the difference between the end and start value of GetTimeRange() unless it is last asset of a Live presentation timeline for which the duration is infinite. @return Duration of this asset.
- L82 _public prototype_ `virtual FString GetAssetIdentifier() const = 0;` — Returns the asset identifier, if present in the manifest, for this asset. @return Asset identifier as it appears in the manifest.
- L91 _public prototype_ `virtual FString GetUniqueIdentifier() const = 0;` — Returns a unique identifier for this asset. This may be a value from the manifest or an internally generated one. @return Unique identifier for this asset.
- L106 _public prototype_ `virtual int32 GetNumberOfAdaptationSets(EStreamType OfStreamType) const = 0;` — Returns the number of "adaptation sets" for a particular type of stream. An adaptation set is defined as a group of streams representing the same content at different quality levels to dynamically switch between. Streams are further grouped by language and codec (there will not be a mix of either in a single adaptation set). @param OfStreamType Type of elementary stream for which to the the number of available adaptation sets. @return Number of adaptation sets for the specified type.
- L118 _public prototype_ `virtual TSharedPtrTS<IPlaybackAssetAdaptationSet> GetAdaptationSetByTypeAndIndex(EStreamType OfStreamType, int32 AdaptationSetIndex) const = 0;` — Returns the media asset's adaptation set by index. @param OfStreamType Type of elementary stream for which to get the adaptation set. @param AdaptationSetIndex Index of the adaptation set to return. @return Shared pointer to the requested adaptation set.
- L125 _public prototype_ `virtual void GetMetaData(TArray<FTrackMetadata>& OutMetadata, EStreamType OfStreamType) const = 0;` — Returns "track" metadata for the specified type of stream. This is essentially the adaptation sets per type with their individual representations.
- L130 _public prototype_ `virtual void UpdateRunningMetaData(const FString& InKindOfValue, const FVariant& InNewValue) = 0;` — Updates asset metadata on long running Livestreams.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/PlayerEntityCache.h` (Private)


#### class `Electra::IPlayerEntityCache`  
`class IPlayerEntityCache`  
_L20-77_
- L44 _public prototype_ `static TSharedPtrTS<IPlayerEntityCache> Create(IPlayerSessionServices* SessionServices);`
- L46 _public prototype_ `virtual ~IPlayerEntityCache() = default;`
- L51 _public prototype_ `virtual void HandleEntityExpiration() = 0;` — Call this periodically to handle expiration times of cached entities.
- L56 _public prototype_ `virtual void SetRecentResponseHeaders(EEntityType InForEntity, const FString& InURL, const TArray<HTTP::FHTTPHeader>& InResponseHeaders) = 0;` — Sets the HTTP response headers of the most recently made entity request.
- L61 _public prototype_ `virtual void GetRecentResponseHeaders(FString& OutURL, TArray<HTTP::FHTTPHeader>& OutResponseHeaders, EEntityType InForEntity) const = 0;` — Returns the HTTP response headers of the most recently made entity request.
- L66 _public prototype_ `virtual void CacheEntity(const FCacheItem& EntityToAdd) = 0;` — Add an entity to the cache.
- L71 _public prototype_ `virtual bool GetCachedEntity(FCacheItem& OutCachedEntity, const FString& URL, const FString& Range) = 0;` — Return a cached entity. Returns true if found, false if not.
- L74 _protected prototype_ `IPlayerEntityCache() = default;`
- L75 _protected prototype_ `IPlayerEntityCache(const IPlayerEntityCache& other) = delete;`
- L76 _protected prototype_ `IPlayerEntityCache& operator = (const IPlayerEntityCache& other) = delete;`

#### enum `Electra::IPlayerEntityCache::EEntityType`  
`enum class EEntityType`  
_L23-30_
- L25 _public enumerator_ `Document`
- L26 _public enumerator_ `Segment`
- L27 _public enumerator_ `XLink`
- L28 _public enumerator_ `Callback`
- L29 _public enumerator_ `Other`

#### struct `Electra::IPlayerEntityCache::FCacheItem`  
`struct FCacheItem`  
_L32-42_
- L34 _public member_ `FString URL;`
- L35 _public member_ `FString Range;`
- L36 _public member_ `FTimeValue ExpiresAtUTC;`
- L37 _public member_ `TSharedPtr<MP4Boxes::FMP4BoxBase, ESPMode::ThreadSafe> ISOBMFFBox;`
- L38 _public member_ `TSharedPtr<FParsedMOOVCommon, ESPMode::ThreadSafe> ParsedMOOV;`
- L39 _public member_ `TSharedPtrTS<const IParserISO14496_12> Parsed14496_12Data;`
- L40 _public member_ `TSharedPtrTS<const IParserMKV> ParsedMatroskaData;`
- L41 _public member_ `TSharedPtrTS<const TArray<uint8>> RawPayloadData;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/PlayerLicenseKey.h` (Private)


#### class `Electra::FLicenseKeyMessage`  
`class FLicenseKeyMessage : public IPlayerMessage`  
_L14-69_
- inherits: `IPlayerMessage`
- L23 _public function_ `static TSharedPtrTS<IPlayerMessage> Create(EReason Reason, const FErrorDetail& PlayerResult, const HTTP::FConnectionInfo* ConnectionInfo)`
- L29 _public function_ `static const FString& Type()`
- L35 _public function_ `virtual const FString& GetType() const`
- L40 _public function_ `EReason GetReason() const`
- L45 _public function_ `const FErrorDetail& GetResult() const`
- L50 _public function_ `const HTTP::FConnectionInfo& GetConnectionInfo() const`
- L56 _private function_ `FLicenseKeyMessage(EReason InReason, const FErrorDetail& PlayerResult, const HTTP::FConnectionInfo* InConnectionInfo) : Result(PlayerResult) , Reason(InReason)`
- L66 _private member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L67 _private member_ `FErrorDetail Result;`
- L68 _private member_ `EReason Reason;`

#### enum `Electra::FLicenseKeyMessage::EReason`  
`enum class EReason`  
_L17-21_
- L19 _public enumerator_ `LicenseKeyDownload`
- L20 _public enumerator_ `LicenseKeyData`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/PlayerSessionServices.h` (Private)


#### class `Electra::IPlayerMessage`  
`class IPlayerMessage`  
_L30-35_
- L33 _public prototype_ `virtual ~IPlayerMessage() = default;`
- L34 _public prototype_ `virtual const FString& GetType() const = 0;`

#### class `Electra::IPlayerSessionServices`  
`class IPlayerSessionServices`  
_L38-212_
- L41 _public prototype_ `virtual ~IPlayerSessionServices() = default;`
- L48 _public prototype_ `virtual void PostError(const FErrorDetail& Error) = 0;` — Post an error. Playback will be halted. @param Error  Error that occurred.
- L58 _public prototype_ `virtual void PostLog(Facility::EFacility FromFacility, IInfoLog::ELevel LogLevel, const FString& Message) = 0;` — Posts a message to the log. @param FromFacility @param LogLevel @param Message
- L66 _public prototype_ `virtual void SendMessageToPlayer(TSharedPtrTS<IPlayerMessage> PlayerMessage) = 0;` — Sends a message to the player worker thread. @param PlayerMessage
- L71 _public prototype_ `virtual void GetExternalGuid(FGuid& OutExternalGuid) = 0;` — Returns the external GUID identifying this player and its associated external texture.
- L78 _public prototype_ `virtual ISynchronizedUTCTime* GetSynchronizedUTCTime() = 0;` — Returns the synchronized UTC clock instance associated with this player instance. @return Pointer to the synchronized clock.
- L85 _public prototype_ `virtual TSharedPtr<IAdaptiveStreamingPlayerResourceProvider, ESPMode::ThreadSafe> GetStaticResourceProvider() = 0;` — Returns the static resource provider, if any. @return Pointer to the static resource provider.
- L92 _public prototype_ `virtual TSharedPtrTS<IElectraHttpManager> GetHTTPManager() = 0;` — Returns the HTTP manager instance serving all HTTP requests of this player instance. @return Pointer to the HTTP manager.
- L99 _public prototype_ `virtual TSharedPtrTS<IAdaptiveStreamSelector> GetStreamSelector() = 0;` — Returns the ABR stream selector instance. @return Pointer to the ABR stream selector.
- L104 _public prototype_ `virtual IPlayerABRLiveControl* GetPlayerARBControl() = 0;` — Returns the player ABR control interface.
- L110 _public prototype_ `virtual IPlayerStreamFilter* GetStreamFilter() = 0;` — Returns the stream filter interface used by playlist readers to determine whether or not a stream can be used on the platform.
- L115 _public prototype_ `virtual const FCodecSelectionPriorities& GetCodecSelectionPriorities(EStreamType ForStream) = 0;` — Returns user configured codec selection priorities.
- L120 _public prototype_ `virtual TSharedPtrTS<IPlayerEntityCache> GetEntityCache() = 0;` — Returns the entity cache of this player.
- L125 _public prototype_ `virtual TSharedPtrTS<IHTTPResponseCache> GetHTTPResponseCache() = 0;` — Returns the HTTP response cache of this player.
- L131 _public prototype_ `virtual TSharedPtrTS<IPlaylistReader> GetManifestReader() = 0;` — Returns the manifest reader instance. The reader is responsible for reading additionally required resources when needed. Requests can be enqueued through this.
- L136 _public prototype_ `virtual TSharedPtrTS<FContentSteeringHandler> GetContentSteeringHandler() = 0;` — Returns the content steering handler for this player instance.
- L141 _public prototype_ `virtual TSharedPtrTS<FCMCDHandler> GetCMCDHandler() = 0;` — Returns the CMCD handler for this player instance.
- L146 _public prototype_ `virtual IAdaptiveStreamingPlayerAEMSHandler* GetAEMSEventHandler() = 0;` — Returns the "Application Event or Metadata Streams" (AEMS) handler.
- L152 _public prototype_ `virtual FParamDictTS& GetMediaInfoDictionary() = 0;` — Returns the dictionary used in queries via GetMediaInfo(). This is used to expose metadata through the IMediaPlayer interface.
- L158 _public prototype_ `virtual FParamDictTS& GetMutableOptions() = 0;` — Returns the mutable player option dictionary. Other than initial options this serves as an interface to pass values between internal sub systems.
- L163 _public prototype_ `virtual bool HaveOptionValue(const FName& InOption) = 0;` — Checks if a certain player option has been set.
- L168 _public prototype_ `virtual const FVariantValue GetOptionValue(const FName& InOption) = 0;` — Returns a player option value.
- L173 _public prototype_ `virtual TSharedPtrTS<FDRMManager> GetDRMManager() = 0;` — Returns the DRM manager, if any.
- L186 _public prototype_ `virtual void SetPlaybackEnd(const FTimeValue& InEndAtTime, EPlayEndReason InEndingReason, TSharedPtrTS<IPlayEndReason> InCustomManifestObject) = 0;`
- L211 _public prototype_ `virtual ECustomPropertyResult ValidateMainPlaylistCustomProperty(const FString& InProtocol, const FString& InPlaylistURL, const TArray<FElectraHTTPStreamHeader>& InPlaylistFetchResponseHeaders, const FPlaylistProperty& InProperty) = 0;`

#### enum `Electra::IPlayerSessionServices::EPlayEndReason`  
`enum class EPlayEndReason`  
_L175-180_
- L177 _public enumerator_ `EndAll`
- L178 _public enumerator_ `NextItem`
- L179 _public enumerator_ `ErrorCondition`

#### class `Electra::IPlayerSessionServices::IPlayEndReason`  
`class IPlayEndReason`  
_L181-185_
- L184 _public prototype_ `virtual ~IPlayEndReason() = default;`

#### enum `Electra::IPlayerSessionServices::ECustomPropertyResult`  
`enum class ECustomPropertyResult`  
_L197-205_
- desc: Called when a non-standard property is encountered in the main playlist (not a variant playlist!). This may be passed on to registered listeners to evaluate if the playlist meets certain custom requirements. Even if there are no such properties in the playlist this method is called at least once with an empty property to signal the end of the property list, which is useful if playback must be rejected when no custom properties are present (if they have been removed by some playlist transformation service).
- L200 _public enumerator_ `Default` — Default handling, depending on where the property occurs.
- L202 _public enumerator_ `Accept` — Property accepted, continue.
- L204 _public enumerator_ `Reject` — Property rejected, fail!

#### struct `Electra::IPlayerSessionServices::FPlaylistProperty`  
`struct FPlaylistProperty`  
_L206-210_
- L208 _public member_ `FString Tag;`
- L209 _public member_ `FString Value;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/PlayerStreamFilter.h` (Private)


#### class `Electra::IPlayerStreamFilter`  
`class IPlayerStreamFilter`  
_L12-20_
- L15 _public prototype_ `virtual ~IPlayerStreamFilter() = default;`
- L17 _public prototype_ `virtual bool CanDecodeStream(const FStreamCodecInformation& InStreamCodecInfo) const = 0;`
- L19 _public prototype_ `virtual bool CanDecodeSubtitle(const FString& MimeType, const FString& Codec) const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/PlayerStreamReader.h` (Private)


#### class `Electra::IStreamReader`  
`class IStreamReader : private TMediaNoncopyable<IStreamReader>`  
_L22-66_
- inherits: `TMediaNoncopyable<IStreamReader>`
- desc: Base class for reading fragments from a stream. Specialized versions for particular container formats shall derive from this class.
- L25 _public prototype_ `virtual ~IStreamReader() = default;`
- L44 _public prototype_ `virtual UEMediaError Create(IPlayerSessionServices* PlayerSessionService, const CreateParam& createParam) = 0;` — Creates the instance internally based on the creation parameters.
- L47 _public prototype_ `virtual bool LoadsMultiplexedTracksSequentially() = 0;` — Returns true if data from all multiplexed tracks is read at the same time in a single sequential read.
- L50 _public prototype_ `virtual void Close() = 0;` — Cancels all pending requests and stops processing. The instance can no longer be used after that!
- L59 _public prototype_ `virtual EAddResult AddRequest(uint32 CurrentPlaybackSequenceID, TSharedPtrTS<IStreamSegment> Request) = 0;` — Adds a request to read from a stream
- L62 _public prototype_ `virtual void CancelRequest(EStreamType StreamType, bool bSilent) = 0;` — Cancels any ongoing requests of the given stream type. Silent cancellation will not notify OnFragmentClose() or OnFragmentReachedEOS().
- L65 _public prototype_ `virtual void CancelRequests() = 0;` — Cancels all pending requests.

#### class `Electra::IStreamReader::StreamReaderEventListener`  
`class StreamReaderEventListener`  
_L27-35_
- L30 _public prototype_ `virtual ~StreamReaderEventListener() = default;`
- L31 _public prototype_ `virtual bool OnFragmentAccessUnitReceived(FAccessUnit* pAccessUnit) = 0;`
- L32 _public prototype_ `virtual void OnFragmentReachedEOS(EStreamType InStreamType, TSharedPtr<const FBufferSourceInfo, ESPMode::ThreadSafe> InStreamSourceInfo) = 0;`
- L33 _public prototype_ `virtual void OnFragmentOpen(TSharedPtrTS<IStreamSegment> pRequest) = 0;`
- L34 _public prototype_ `virtual void OnFragmentClose(TSharedPtrTS<IStreamSegment> pRequest) = 0;`

#### struct `Electra::IStreamReader::CreateParam`  
`struct CreateParam`  
_L37-41_
- L39 _public member_ `IAccessUnitMemoryProvider* MemoryProvider = nullptr;`
- L40 _public member_ `StreamReaderEventListener* EventListener = nullptr;`

#### enum `Electra::IStreamReader::EAddResult`  
`enum class EAddResult`  
_L52-57_
- L54 _public enumerator_ `Added`
- L55 _public enumerator_ `TryAgainLater`
- L56 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/Playlist.h` (Private)


#### class `Electra::Playlist::FReplayEventParams`  
`class FReplayEventParams`  
_L14-83_
- L17 _public function_ `void SetLoopingAtStart(bool bInIsLoopEnabledAtStart)`
- L19 _public function_ `bool IsLoopingAtStartEnabled() const`
- L22 _public function_ `bool HaveReplayParams() const`
- L26 _public function_ `bool ParseFromURL(const FString& InURL)` — Parse URL fragment parameters
- L72 _public function_ `FString GetSourceURL() const`
- L74 _public function_ `FString GetCleanedURL() const`
- L76 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetUrlFragmentParams() const`
- L79 _private member_ `FString SourceURL;`
- L80 _private member_ `FString CleanedURL;`
- L81 _private member_ `TArray<FURL_RFC3986::FQueryParam> UrlFragmentParams;`
- L82 _private member_ `bool bIsLoopEnabledAtStart = false;`

#### enum `Electra::Playlist::EListType`  
`enum class EListType`  
_L86-90_
- L88 _public enumerator_ `Main`
- L89 _public enumerator_ `Variant`

#### enum `Electra::Playlist::ELoadType`  
`enum class ELoadType`  
_L109-113_
- L111 _public enumerator_ `Initial`
- L112 _public enumerator_ `Update`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`
- L12 _namespace_ `namespace Playlist` (scope `Electra`)
- L92 _function_ `static const TCHAR* const GetPlaylistTypeString(EListType InListType)` (scope `Electra::Playlist`)
- L115 _function_ `static const TCHAR* const GetPlaylistLoadTypeString(ELoadType InLoadType)` (scope `Electra::Playlist`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/PlaylistReader.h` (Private)


#### class `Electra::IPlaylistReader`  
`class IPlaylistReader`  
_L20-170_
- L23 _public prototype_ `virtual ~IPlaylistReader() = default;`
- L28 _public prototype_ `virtual EMediaFormatType GetMediaFormatType() const = 0;` — Returns the media format this reader handles.
- L34 _public prototype_ `virtual void Close() = 0;` — Must call Close() before dropping any TShared..<> of this to allow for any internally used TWeak..<> to still be valid if used by AsShared().
- L39 _public prototype_ `virtual void HandleOnce() = 0;` — Called every so often by the player's worker thread to handle this class.
- L44 _public prototype_ `virtual const FString& GetPlaylistType() const = 0;` — Returns the type of the playlist (eg. "hls", "dash", etc.)
- L52 _public prototype_ `virtual void LoadAndParse(const FString& InURL, const Playlist::FReplayEventParams& InReplayEventParams) = 0;` — Loads and parses the playlist. @param URL URL of the playlist to load @param InReplayEventParams URL fragments pertaining to replay event which have been removed from the source URL
- L59 _public prototype_ `virtual FString GetURL() const = 0;` — Returns the URL from which the playlist was loaded (or supposed to be loaded). @return The playlist URL
- L67 _public prototype_ `virtual TSharedPtrTS<IManifest> GetManifest() = 0;` — Returns the manifest interface to access the playlist in a uniform way. @return

#### class `Electra::IPlaylistReader::PlaylistDownloadMessage`  
`class PlaylistDownloadMessage : public IPlayerMessage`  
_L70-115_
- inherits: `IPlayerMessage`
- L73 _public function_ `static TSharedPtrTS<IPlayerMessage> Create(const HTTP::FConnectionInfo* ConnectionInfo, Playlist::EListType InListType, Playlist::ELoadType InLoadType, int32 InAttempts)`
- L79 _public function_ `static const FString& Type()`
- L85 _public function_ `virtual const FString& GetType() const`
- L88 _public function_ `Playlist::EListType GetListType() const`
- L91 _public function_ `Playlist::ELoadType GetLoadType() const`
- L94 _public function_ `int32 GetAttempts() const`
- L97 _public function_ `const HTTP::FConnectionInfo& GetConnectionInfo() const`
- L101 _private function_ `PlaylistDownloadMessage(const HTTP::FConnectionInfo* InConnectionInfo, Playlist::EListType InListType, Playlist::ELoadType InLoadType, int32 InAttempts) : ListType(InListType) , LoadType(InLoadType) , Attempts(InAttempts)`
- L111 _private member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L112 _private member_ `Playlist::EListType ListType;`
- L113 _private member_ `Playlist::ELoadType LoadType;`
- L114 _private member_ `int32 Attempts;`

#### class `Electra::IPlaylistReader::PlaylistLoadedMessage`  
`class PlaylistLoadedMessage : public IPlayerMessage`  
_L118-168_
- inherits: `IPlayerMessage`
- L121 _public function_ `static TSharedPtrTS<IPlayerMessage> Create(const FErrorDetail& PlayerResult, const HTTP::FConnectionInfo* ConnectionInfo, Playlist::EListType InListType, Playlist::ELoadType InLoadType, int32 InAttempts)`
- L127 _public function_ `static const FString& Type()`
- L133 _public function_ `virtual const FString& GetType() const`
- L136 _public function_ `const FErrorDetail& GetResult() const`
- L139 _public function_ `Playlist::EListType GetListType() const`
- L142 _public function_ `Playlist::ELoadType GetLoadType() const`
- L145 _public function_ `int32 GetAttempts() const`
- L148 _public function_ `const HTTP::FConnectionInfo& GetConnectionInfo() const`
- L152 _private function_ `PlaylistLoadedMessage(const FErrorDetail& PlayerResult, const HTTP::FConnectionInfo* InConnectionInfo, Playlist::EListType InListType, Playlist::ELoadType InLoadType, int32 InAttempts) : Result(PlayerResult) , ListType(InListType) , LoadType(InLoadType) , Attempts(InAttempts)`
- L163 _private member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L164 _private member_ `FErrorDetail Result;`
- L165 _private member_ `Playlist::EListType ListType;`
- L166 _private member_ `Playlist::ELoadType LoadType;`
- L167 _private member_ `int32 Attempts;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/StreamSegmentReaderCommon.h` (Private)


#### class `Electra::FParsedMOOVCommon`  
`class FParsedMOOVCommon`  
_L30-142_
- L33 _public prototype_ `virtual ~FParsedMOOVCommon() = default;`
- L45 _public function_ `bool Parse(TConstArrayView<uint8> InInitSegmentData)`
- L78 _public function_ `bool Parse(TSharedPtr<MP4Boxes::FMP4BoxMOOV, ESPMode::ThreadSafe> InMOOV)`
- L126 _public function_ `const TMap<uint32, FTrackInfo>& GetTrackMap() const`
- L129 _public function_ `TSharedPtr<MP4Boxes::FMP4BoxMVEX, ESPMode::ThreadSafe> GetMVEXBox() const`
- L132 _public function_ `TSharedPtr<MP4Boxes::FMP4BoxMETA, ESPMode::ThreadSafe> GetMETABox() const`
- L134 _public function_ `const TArray<TSharedPtr<MP4Boxes::FMP4BoxPSSH, ESPMode::ThreadSafe>>& GetPSSHBoxes() const`
- L137 _private member_ `TSharedPtr<MP4Boxes::FMP4BoxMOOV, ESPMode::ThreadSafe> MoovBox;`
- L138 _private member_ `TSharedPtr<MP4Boxes::FMP4BoxMVEX, ESPMode::ThreadSafe> MvexBox;`
- L139 _private member_ `TSharedPtr<MP4Boxes::FMP4BoxMETA, ESPMode::ThreadSafe> MetaBox;`
- L140 _private member_ `TArray<TSharedPtr<MP4Boxes::FMP4BoxPSSH, ESPMode::ThreadSafe>> PsshBoxes;`
- L141 _private member_ `TMap<uint32, FTrackInfo> TrackMap;`

#### struct `Electra::FParsedMOOVCommon::FTrackInfo`  
`struct FTrackInfo`  
_L35-43_
- L37 _public member_ `TSharedPtr<MP4Boxes::FMP4BoxTRAK, ESPMode::ThreadSafe> TrakBox;`
- L38 _public member_ `FCodecTypeFormat CodecFormat;`
- L39 _public member_ `FDRMTypeFormat DrmFormat;`
- L40 _public member_ `FDecoderInformation DecoderInformation;`
- L41 _public member_ `uint32 TrackID = 0;`
- L42 _public member_ `uint32 TrackTimescale = 0;`

#### struct `Electra::FProducerReferenceTimeInfo`  
`struct FProducerReferenceTimeInfo : public IProducerReferenceTimeInfo`  
_L146-163_
- inherits: `IProducerReferenceTimeInfo`
- L148 _public member_ `FTimeValue WallclockTime;`
- L149 _public member_ `uint64 PresentationTime = 0;`
- L150 _public member_ `uint32 ID = 0;`
- L151 _public member_ `EType Type = EType::Encoder;`
- L152 _public member_ `bool bInband = false;`
- L153 _public function_ `FTimeValue GetWallclockTime() const override`
- L155 _public function_ `uint64 GetPresentationTime() const override`
- L157 _public function_ `uint32 GetID() const override`
- L159 _public function_ `EType GetType() const override`
- L161 _public function_ `bool GetIsInband() const override`

#### struct `Electra::FSegmentInformationCommon`  
`struct FSegmentInformationCommon`  
_L165-262_
- L192 _public member_ `FURL InitializationURL;`
- L193 _public member_ `FURL MediaURL;`
- L194 _public member_ `TArray<FURL> NextMediaURLS;`
- L195 _public member_ `TArray<FCMCDNextSegNumberTimes> NextMediaCMCDNumberTimes;`
- L196 _public member_ `FTimeValue ATO;`
- L197 _public member_ `int64 Time = 0;` — Time value T in timescale units
- L198 _public member_ `int64 PTO = 0;` — PresentationTimeOffset
- L199 _public member_ `int64 EPTdelta = 0;`
- L200 _public member_ `int64 Duration = 0;` — Duration of the segment. Not necessarily exact if <SegmentTemplate> is used).
- L201 _public member_ `int64 Number = 0;` — Index of the segment.
- L202 _public member_ `int64 SubIndex = 0;` — Subsegment index
- L203 _public member_ `int64 MediaLocalFirstAUTime = 0;` — Time of the first AU to use in this segment in media local time
- L204 _public member_ `int64 MediaLocalLastAUTime = 0;` — Time at which the last AU to use in thie segment ends in media local time
- L205 _public member_ `int64 MediaLocalFirstPTS = 0;`
- L206 _public member_ `uint32 Timescale = 0;` — Local media timescale
- L207 _public member_ `bool bLowLatencyChunkedEncodingExpected = false;`
- L208 _public member_ `bool bFrameAccuracyRequired = false;` — true if the segment was located for frame accurate seeking.
- L209 _public member_ `bool bIsSideload = false;` — true if this is a side-loaded resource to be fetched and cached.
- L210 _public member_ `bool bIsLastInPeriod = false;` — true if known to be the last segment in the period.
- L211 _public member_ `bool bMayBeMissing = false;` — true if the last segment in <SegmentTemplate> that might not exist.
- L212 _public member_ `TArray<FInbandEventStream> InbandEventStreams;`
- L213 _public member_ `TArray<FProducerReferenceTimeInfo> ProducerReferenceTimeInfos;`
- L214 _public member_ `int64 MeasureLatencyViaReferenceTimeInfoID = -1;`
- L217 _public member_ `bool bIsMissing = false;` — Out
- L218 _public member_ `bool bSawLMSG = false;` — Will be set to true by the stream reader if the 'lmsg' brand was found.
- L221 _public member_ `EContainerType ContainerType = EContainerType::ISO14496_12;` — Misc
- L222 _public member_ `int64 NumberOfBytes = 0;`
- L223 _public member_ `int64 FirstByteOffset = 0;`
- L225 _public function_ `FTimeValue CalculateASAST(const FTimeValue& AST, const FTimeValue& PeriodStart, bool bIsStatic)`
- L241 _public function_ `FTimeValue CalculateSAET(const FTimeValue& AST, const FTimeValue& PeriodStart, const FTimeValue& MPDAET, const FTimeValue& TSB, bool bIsStatic)`

#### struct `Electra::FSegmentInformationCommon::FURL`  
`struct FURL`  
_L167-173_
- L169 _public member_ `FMediaURL Url;`
- L170 _public member_ `FString Range;`
- L171 _public member_ `FString CustomHeader;`
- L172 _public member_ `int64 SteeringID = 0;`

#### struct `Electra::FSegmentInformationCommon::FInbandEventStream`  
`struct FInbandEventStream`  
_L174-180_
- L176 _public member_ `FString SchemeIdUri;`
- L177 _public member_ `FString Value;`
- L178 _public member_ `int64 PTO = 0;`
- L179 _public member_ `uint32 Timescale = 0;`

#### enum `Electra::FSegmentInformationCommon::EContainerType`  
`enum class EContainerType`  
_L181-186_
- L183 _public enumerator_ `ISO14496_12`
- L184 _public enumerator_ `ISO13818_1`
- L185 _public enumerator_ `Matroska`

#### struct `Electra::FSegmentInformationCommon::FCMCDNextSegNumberTimes`  
`struct FCMCDNextSegNumberTimes`  
_L187-191_
- L189 _public member_ `int64 Number = -1;`
- L190 _public member_ `int64 Time = -1;`

#### class `Electra::FStreamSegmentRequestCommon`  
`class FStreamSegmentRequestCommon : public IStreamSegment`  
_L265-440_
- inherits: `IStreamSegment`
- L268 _public prototype_ `FStreamSegmentRequestCommon();`
- L269 _public prototype_ `virtual ~FStreamSegmentRequestCommon();`
- L271 _public prototype_ `void SetPlaybackSequenceID(uint32 PlaybackSequenceID) override;`
- L272 _public prototype_ `uint32 GetPlaybackSequenceID() const override;`
- L274 _public prototype_ `void SetExecutionDelay(const FTimeValue& UTCNow, const FTimeValue& ExecutionDelay) override;`
- L275 _public prototype_ `FTimeValue GetExecuteAtUTCTime() const override;`
- L277 _public prototype_ `EStreamType GetType() const override;`
- L279 _public prototype_ `void GetDependentStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutDependentStreams) const override;`
- L280 _public prototype_ `void GetRequestedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutRequestedStreams) override;`
- L281 _public prototype_ `void GetEndedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutAlreadyEndedStreams) override;`
- L283 _public prototype_ `FTimeValue GetFirstPTS() const override;`
- L284 _public prototype_ `FTimeRange GetTimeRange() const override;`
- L286 _public prototype_ `int32 GetQualityIndex() const override;`
- L287 _public prototype_ `int32 GetBitrate() const override;`
- L289 _public prototype_ `void GetDownloadStats(Metrics::FSegmentDownloadStats& OutStats) const override;`
- L290 _public prototype_ `bool GetStartupDelay(FTimeValue& OutStartTime, FTimeValue& OutTimeIntoSegment, FTimeValue& OutSegmentDuration) const override;`
- L339 _public member_ `FHLSSpecific HLS;`
- L386 _public prototype_ `DECLARE_DELEGATE_OneParam(FFirstTimestampReceivedDelegate, TSharedPtrTS<FStreamSegmentRequestCommon>);`
- L391 _public member_ `EStreamingProtocol StreamingProtocol = EStreamingProtocol::Undefined;` — Streaming protocol for which this segment is requested.
- L394 _public member_ `EContainerFormat ExpectedContainerFormat = EContainerFormat::Undefined;` — The container format that is expected to be used. Not necessarily what it will be!
- L395 _public member_ `EStreamType StreamType = EStreamType::Unsupported;` — Type of stream (video, audio, etc.)
- L396 _public member_ `int32 QualityIndex = 0;`
- L397 _public member_ `int32 MaxQualityIndex = 0;`
- L398 _public member_ `TSharedPtrTS<ITimelineMediaAsset> Period;` — The period the adaptation set belongs to.
- L399 _public member_ `TSharedPtrTS<IPlaybackAssetAdaptationSet> AdaptationSet;` — The adaptation set the representation belongs to.
- L400 _public member_ `TSharedPtrTS<IPlaybackAssetRepresentation> Representation;` — The representation this request belongs to.
- L401 _public member_ `FStreamCodecInformation CodecInfo[4];` — Partial codec info as can be collected from the MPD.
- L402 _public member_ `FSegmentInformationCommon Segment;` — Segment information (URLs and timing values)
- L403 _public member_ `TArray<TSharedPtrTS<FStreamSegmentRequestCommon>> DependentStreams;` — Streams this segment depends on. Currently only used to hold the set of requests for the initial playback start.
- L404 _public member_ `bool bIsFalloffSegment = false;` — true if this segment no longer exists on the timeline and is used only to skip ahead.
- L405 _public member_ `bool bIsGapSegment = false;` — true if segment information is given, but the segment is known to be missing and not to be loaded.
- L406 _public member_ `bool bIsEOSSegment = false;` — true if this is not an actual request but a stream-has-already-ended request.
- L407 _public member_ `bool bIsInitialStartRequest = false;` — true if this is the initial playback start request.
- L408 _public member_ `FTimeValue PeriodStart;` — Value to add to all DTS & PTS to map them into the Period timeline
- L409 _public member_ `FTimeValue AST = FTimeValue::GetZero();` — Value of AST to add to all time to generate wallclock time
- L410 _public member_ `FTimeValue AdditionalAdjustmentTime = FTimeValue::GetZero();` — Sum of any other time corrections
- L411 _public member_ `bool bInsertFillerData = false;` — true to insert empty access units into the buffer instead of reading actual data.
- L412 _public member_ `int64 TimestampSequenceIndex = 0;` — Sequence index to set in all timestamp values of the decoded access unit.
- L413 _public member_ `FTimeValue FrameAccurateStartTime;` — If set, the start time as was requested in a Seek() (not in media local time)
- L416 _public member_ `FEncryption DrmInit;` — Encryption
- L417 _public member_ `FEncryption DrmMedia;`
- L420 _public member_ `bool bIsMultiplex = false;` — Muxed stream types to ignore (only used with HLS for now)
- L421 _public member_ `bool bIgnoreVideo = false;`
- L422 _public member_ `bool bIgnoreAudio = false;`
- L423 _public member_ `bool bIgnoreSubtitles = false;`
- L426 _public member_ `FTimeValue ASAST;` — UTC wallclock times during which this segment can be fetched;
- L427 _public member_ `FTimeValue SAET;`
- L428 _public member_ `FTimeValue DownloadDelayTime;`
- L432 _public member_ `TSharedPtrTS<FBufferSourceInfo> SourceBufferInfo[4];` — Internal work variables
- L433 _public member_ `int32 NumOverallRetries = 0;` — Number of retries for this _segment_ across all possible quality levels and CDNs.
- L434 _public member_ `uint32 CurrentPlaybackSequenceID = ~0U;` — Set by the player before adding the request to the stream reader.
- L435 _public member_ `Metrics::FSegmentDownloadStats DownloadStats;`
- L436 _public member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L437 _public member_ `bool bWarnedAboutTimescale = false;`
- L438 _public member_ `FTimestampVars TimestampVars;`
- L439 _public member_ `FFirstTimestampReceivedDelegate FirstTimestampReceivedDelegate;` — Optional notification callback to invoke when the first AU timestamp is parsed

#### enum `Electra::FStreamSegmentRequestCommon::EStreamingProtocol`  
`enum class EStreamingProtocol`  
_L293-301_
- L296 _public enumerator_ `Undefined` — Not an actual type, used to signify that the protocol has not been set.
- L298 _public enumerator_ `DASH` — MPEG DASH, ISO 23009-1
- L300 _public enumerator_ `HLS` — Apple HLS, RFC 8216

#### enum `Electra::FStreamSegmentRequestCommon::EContainerFormat`  
`enum class EContainerFormat`  
_L303-317_
- L306 _public enumerator_ `Undefined` — Not an actual type, used to signify that the format has not been set.
- L308 _public enumerator_ `ISO_14496_12` — ".mp4" container
- L310 _public enumerator_ `ISO_13818_1` — ".ts" container
- L312 _public enumerator_ `Matroska_WebM` — ".mkv" or ".webm" container
- L314 _public enumerator_ `ID3_Raw` — ".mp3" or ".aac" raw file with an ID3 tag
- L316 _public enumerator_ `WebVTT_Raw` — ".vtt" Raw WebVTT

#### struct `Electra::FStreamSegmentRequestCommon::FEncryption`  
`struct FEncryption`  
_L320-326_
- desc: Encryption
- L322 _public member_ `TSharedPtrTS<ElectraCDM::IMediaCDMClient> DrmClient;`
- L323 _public member_ `FString DrmMimeType;`
- L324 _public member_ `TArray<uint8> DrmIV;`
- L325 _public member_ `TArray<uint8> DrmKID;`

#### struct `Electra::FStreamSegmentRequestCommon::FHLSSpecific`  
`struct FHLSSpecific`  
_L329-338_
- desc: HLS specific information carried to locate the next segment.
- L331 _public member_ `FTimeValue DurationDistanceToEnd;`
- L332 _public member_ `FTimeValue TimeWhenLoaded;`
- L333 _public member_ `TSharedPtr<FMediaPlaylistAndStateHLS, ESPMode::ThreadSafe> Playlist;`
- L334 _public member_ `int64 DiscontinuitySequence = -1;`
- L335 _public member_ `int32 LocalIndex = -1;`
- L336 _public member_ `bool bNoPDTMapping = false;`
- L337 _public member_ `bool bHasDiscontinuity = false;`

#### struct `Electra::FStreamSegmentRequestCommon::FTimestampVars`  
`struct FTimestampVars`  
_L342-384_
- desc: Timestamp information and adjustment
- L346 _public member_ `bool bGetAndAdjustByFirstTimestamp = false;` — If set the first timestamp (DTS) is stored for reference and subtracted from all DTS and PTS timestamps in this and future requests (this structure is passed from request to request).
- L380 _public member_ `FInternal Internal;`
- L382 _public member_ `FSegmentTimes Local;`
- L383 _public member_ `FNextExpectedStartTimes Next;`

#### struct `Electra::FStreamSegmentRequestCommon::FTimestampVars::FSegmentTimes`  
`struct FSegmentTimes`  
_L349-360_
- L352 _public member_ `FTimeValue First[4];` — Per stream type first DTS values in the segment.
- L353 _public function_ `void Reset()`

#### struct `Electra::FStreamSegmentRequestCommon::FTimestampVars::FNextExpectedStartTimes`  
`struct FNextExpectedStartTimes`  
_L361-366_
- L363 _public member_ `FTimeValue ExpectedLargerThan[4];` — time must be larger than this
- L364 _public member_ `bool bCheck = false;`
- L365 _public member_ `bool bFailed = false;`

#### struct `Electra::FStreamSegmentRequestCommon::FTimestampVars::FInternal`  
`struct FInternal`  
_L368-379_
- L370 _public member_ `FTimeValue SegmentBaseTime {(int64)0};`
- L371 _public member_ `TOptional<uint64> RawAdjustmentValue;`
- L377 _public member_ `FRollover Rollover[4];`
- L378 _public member_ `TOptional<uint64> PrevRawID3StartPTS;`

#### struct `Electra::FStreamSegmentRequestCommon::FTimestampVars::FInternal::FRollover`  
`struct FRollover`  
_L372-376_
- L374 _public member_ `uint64 RawDTSOffset = 0;`
- L375 _public member_ `uint64 RawPTSOffset = 0;`

#### class `Electra::FStreamSegmentReaderCommon`  
`class FStreamSegmentReaderCommon : public IStreamReader`  
_L447-788_
- inherits: `IStreamReader`
- L450 _public prototype_ `FStreamSegmentReaderCommon();`
- L451 _public prototype_ `virtual ~FStreamSegmentReaderCommon();`
- L453 _public prototype_ `UEMediaError Create(IPlayerSessionServices* PlayerSessionService, const CreateParam& InCreateParam) override;`
- L454 _public prototype_ `bool LoadsMultiplexedTracksSequentially() override;`
- L455 _public prototype_ `void Close() override;`
- L458 _public prototype_ `EAddResult AddRequest(uint32 CurrentPlaybackSequenceID, TSharedPtrTS<IStreamSegment> Request) override;` — Adds a request to read from a stream
- L461 _public prototype_ `void CancelRequest(EStreamType StreamType, bool bSilent) override;` — Cancels any ongoing requests of the given stream type. Silent cancellation will not notify OnFragmentClose() or OnFragmentReachedEOS().
- L464 _public prototype_ `void CancelRequests() override;` — Cancels all pending requests.
- L467 _private prototype_ `ELECTRA_IMPL_DEFAULT_ERROR_METHODS(CommonSegmentReader);`
- L784 _private member_ `FStreamHandler StreamHandlers[3];` — 0 = video, 1 = audio, 2 = subtitle
- L785 _private member_ `FErrorDetail ErrorDetail;`
- L786 _private member_ `IPlayerSessionServices* PlayerSessionService = nullptr;`
- L787 _private member_ `bool bIsStarted = false;`

#### struct `Electra::FStreamSegmentReaderCommon::FStreamHandler`  
`struct FStreamHandler : public FMediaThread, public IGenericDataReader`  
_L469-782_
- inherits: `FMediaThread,IGenericDataReader`
- L697 _public prototype_ `FStreamHandler();`
- L698 _public prototype_ `virtual ~FStreamHandler();`
- L699 _public prototype_ `void Cancel(bool bSilent);`
- L700 _public prototype_ `void SignalWork();`
- L701 _public prototype_ `void WorkerThread();`
- L702 _public prototype_ `EHandleResult SetError(const FString& InMessage, uint16 InCode);`
- L703 _public prototype_ `bool HasErrored() const;`
- L704 _public prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L705 _public prototype_ `int32 HTTPProgressCallback(const IElectraHttpManager::FRequest* Request);`
- L706 _public prototype_ `void HTTPCompletionCallback(const IElectraHttpManager::FRequest* Request);`
- L707 _public prototype_ `void HTTPUpdateStats(const FTimeValue& CurrentTime, const IElectraHttpManager::FRequest* Request);`
- L709 _public prototype_ `void HandleRequest();`
- L710 _public prototype_ `void SetupSegmentDownloadStatsFromConnectionInfo(const HTTP::FConnectionInfo& ci);`
- L711 _public prototype_ `bool FetchInitSegment(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L712 _public prototype_ `EMediaSegmentTriggerResult TriggerMediaSegmentDownload(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L713 _public prototype_ `void HandleCommonMediaBegin(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L714 _public prototype_ `void HandleCommonMediaEnd(EHandleResult InSegmentResult, TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L715 _public prototype_ `EHandleResult HandleMP4Media(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L716 _public prototype_ `EHandleResult HandleMP4MediaLegacy(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L717 _public prototype_ `EHandleResult HandleMKVMedia(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L718 _public prototype_ `EHandleResult HandleTSMedia(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L719 _public prototype_ `EHandleResult HandleID3RawMedia(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest, int32 InID3HeaderSize);`
- L720 _public prototype_ `EHandleResult HandleSideloadedMedia(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L721 _public prototype_ `EHandleResult HandleRawSubtitleMedia(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L722 _public prototype_ `EHandleResult HandleFillerDataSetup(TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L723 _public prototype_ `void InsertFillerData(TSharedPtrTS<FActiveTrackData> InActiveTrackData, TSharedPtrTS<FStreamSegmentRequestCommon> InRequest);`
- L724 _public prototype_ `void CheckForInbandDASHEvents(const TSharedPtrTS<FStreamSegmentRequestCommon>& InRequest);`
- L725 _public prototype_ `void HandleMP4Metadata(const TSharedPtrTS<FStreamSegmentRequestCommon>& InRequest, const TSharedPtr<MP4Boxes::FMP4BoxMETA, ESPMode::ThreadSafe>& InMoovMetaBox, const TSharedPtr<MP4Boxes::FMP4BoxMETA, ESPMode::ThreadSafe>& InMoofMetaBox);`
- L726 _public prototype_ `void HandleMP4EventMessages(const TSharedPtrTS<FStreamSegmentRequestCommon>& InRequest, const TSharedPtr<MP4Boxes::FMP4BoxSIDX, ESPMode::ThreadSafe>& InSidxBox, const TArray<TSharedPtr<MP4Boxes::FMP4BoxEMSG, ESPMode::ThreadSafe>>& InEventMessageBoxes);`
- L727 _public prototype_ `void HandleMP4MetadataLegacy(const TSharedPtrTS<FStreamSegmentRequestCommon>& InRequest, const TSharedPtrTS<IParserISO14496_12>& InMP4Parser, const TSharedPtrTS<const IParserISO14496_12>& InMP4InitSegment, const FTimeValue& InBaseTime);`
- L728 _public prototype_ `void HandleMP4EventMessagesLegacy(const TSharedPtrTS<FStreamSegmentRequestCommon>& InRequest, const TSharedPtrTS<IParserISO14496_12>& InMP4Parser);`
- L730 _public prototype_ `void SelectPrimaryTrackData(const TSharedPtrTS<FStreamSegmentRequestCommon>& InRequest);`
- L731 _public prototype_ `EEmitResult EmitSamples(EEmitType InEmitType);`
- L734 _public prototype_ `int64 ReadData(void* IntoBuffer, int64 NumBytesToRead, int64 InFromOffset) override;` — Methods from IGenericDataReader
- L735 _public prototype_ `bool HasReachedEOF() const override;`
- L736 _public prototype_ `bool HasReadBeenAborted() const override;`
- L737 _public prototype_ `int64 GetCurrentOffset() const override;`
- L738 _public prototype_ `int64 GetTotalSize() const override;`
- L740 _public function_ `static bool IsWebVTTHeader(const uint8* InData, int32 InSize)`
- L746 _public member_ `IStreamReader::CreateParam Parameters;`
- L747 _public member_ `TSharedPtrTS<FStreamSegmentRequestCommon> CurrentRequest;`
- L748 _public member_ `FMediaSemaphore WorkSignal;`
- L749 _public member_ `FMediaEvent IsIdleSignal;`
- L750 _public member_ `volatile bool bTerminate = false;`
- L751 _public member_ `volatile bool bWasStarted = false;`
- L752 _public member_ `volatile bool bRequestCanceled = false;`
- L753 _public member_ `volatile bool bSilentCancellation = false;`
- L754 _public member_ `volatile bool bHasErrored = false;`
- L755 _public member_ `bool bAbortedByABR = false;`
- L756 _public member_ `bool bAllowEarlyEmitting = false;`
- L757 _public member_ `bool bFillRemainingDuration = false;`
- L758 _public member_ `bool bAddedCMCDQueryToMediaURL = false;`
- L760 _public member_ `IPlayerSessionServices* PlayerSessionService = nullptr;`
- L761 _public member_ `FReadBuffer ReadBuffer;`
- L762 _public member_ `TArray<TSharedPtrTS<DASH::FPlayerEvent>> SegmentEventsFound;`
- L764 _public member_ `FCriticalSection MetricUpdateLock;`
- L765 _public member_ `int32 ProgressReportCount = 0;`
- L766 _public member_ `TSharedPtrTS<IAdaptiveStreamSelector> StreamSelector;`
- L767 _public member_ `FString ABRAbortReason;`
- L770 _public member_ `TVariant<FNoInitSegmentData, TSharedPtrTS<FParsedMOOVCommon>, TSharedPtrTS<const IParserISO14496_12>, TSharedPtrTS<const IParserMKV>, TSharedPtrTS<const TArray<uint8>>> InitSegmentData;`
- L771 _public member_ `Metrics::FSegmentDownloadStats DownloadStats;`
- L772 _public member_ `HTTP::FConnectionInfo CurrentConnectionInfo;`
- L773 _public member_ `TSharedPtrTS<IElectraHttpManager::FProgressListener> ProgressListener;`
- L774 _public member_ `TSharedPtrTS<IElectraHttpManager::FRequest> HTTPRequest;`
- L775 _public member_ `FErrorDetail SegmentError;`
- L776 _public member_ `TSortedMap<uint64, TSharedPtrTS<FActiveTrackData>> TrackDataMap;`
- L777 _public member_ `TSharedPtrTS<FActiveTrackData> CurrentlyActiveTrackData;`
- L778 _public member_ `TSharedPtrTS<FActiveTrackData> PrimaryTrackData;`
- L779 _public member_ `TSharedPtr<ElectraCDM::IMediaCDMDecrypter, ESPMode::ThreadSafe> Decrypter;`
- L781 _public member_ `static uint32 UniqueDownloadID;`

#### enum `Electra::FStreamSegmentReaderCommon::FStreamHandler::EMediaSegmentTriggerResult`  
`enum class EMediaSegmentTriggerResult`  
_L471-477_
- L473 _public enumerator_ `Started`
- L474 _public enumerator_ `IsFiller`
- L475 _public enumerator_ `IsSideloaded`
- L476 _public enumerator_ `DontHandle`

#### enum `Electra::FStreamSegmentReaderCommon::FStreamHandler::EHandleResult`  
`enum class EHandleResult`  
_L479-486_
- L481 _public enumerator_ `DontHandle`
- L482 _public enumerator_ `Finished`
- L483 _public enumerator_ `Skipped`
- L484 _public enumerator_ `Aborted`
- L485 _public enumerator_ `Failed`

#### enum `Electra::FStreamSegmentReaderCommon::FStreamHandler::EEmitType`  
`enum class EEmitType`  
_L488-491_
- L490 _public enumerator_ `UntilBlocked`

#### enum `Electra::FStreamSegmentReaderCommon::FStreamHandler::EEmitResult`  
`enum class EEmitResult`  
_L493-497_
- L495 _public enumerator_ `HaveRemaining`
- L496 _public enumerator_ `SentEverything`

#### struct `Electra::FStreamSegmentReaderCommon::FStreamHandler::FReadBuffer`  
`struct FReadBuffer`  
_L499-546_
- L501 _public function_ `FReadBuffer()`
- L503 _public function_ `~FReadBuffer()`
- L506 _public function_ `void Reset()`
- L524 _public function_ `bool DidDecryptionFail() const`
- L526 _public prototype_ `bool WaitUntilSizeAvailable(int64 SizeNeeded, int32 TimeoutMicroseconds);`
- L527 _public prototype_ `FCriticalSection* GetLock();`
- L528 _public prototype_ `const uint8* GetLinearReadData() const;`
- L529 _public prototype_ `uint8* GetLinearReadData();`
- L530 _public prototype_ `int64 GetLinearReadSize() const;`
- L531 _public prototype_ `bool GetEOD() const;`
- L532 _public prototype_ `bool WasAborted() const;`
- L535 _public member_ `FWaitableBuffer DecryptedDataBuffer;`
- L536 _public member_ `TArray<uint8> BlockDecrypterIV;`
- L537 _public member_ `TArray<uint8> BlockDecrypterKID;`
- L538 _public member_ `TSharedPtr<ElectraCDM::IMediaCDMDecrypter, ESPMode::ThreadSafe> BlockDecrypter;`
- L539 _public member_ `TSharedPtrTS<FWaitableBuffer> ReceiveBuffer;`
- L540 _public member_ `ElectraCDM::IMediaCDMDecrypter::IStreamDecryptHandle* BlockDecrypterHandle = nullptr;`
- L541 _public member_ `int64 ParsePos = 0;`
- L542 _public member_ `int32 BlockDecrypterBlockSize = 0;`
- L543 _public member_ `bool bIsEncrypted = false;`
- L544 _public member_ `bool bDecrypterReady = false;`
- L545 _public member_ `bool bIsDecrypterGood = false;`

#### struct `Electra::FStreamSegmentReaderCommon::FStreamHandler::FProducerTime`  
`struct FProducerTime`  
_L548-552_
- L550 _public member_ `FTimeValue Base;`
- L551 _public member_ `int64 Media = 0;`

#### struct `Electra::FStreamSegmentReaderCommon::FStreamHandler::FActiveTrackData`  
`struct FActiveTrackData`  
_L554-670_
- L556 _public function_ `void Reset()`
- L610 _public function_ `void AddAccessUnit(FAccessUnit* InAU)`
- L641 _public member_ `TArray<FSample> AccessUnitFIFO;`
- L642 _public member_ `TArray<FSample> SortedAccessUnitFIFO;`
- L643 _public member_ `FTimeValue DurationSuccessfullyRead {(int64)0};`
- L644 _public member_ `FTimeValue DurationSuccessfullyDelivered {(int64)0};`
- L645 _public member_ `FTimeValue AverageDuration {(int64)0};`
- L646 _public member_ `FTimeValue SmallestPTS;`
- L647 _public member_ `FTimeValue LargestPTS;`
- L648 _public member_ `FTimeValue LargestDTS;`
- L649 _public member_ `FTimeValue TimeMappingOffset;`
- L650 _public member_ `TSharedPtrTS<FAccessUnit::CodecData> CSD;`
- L651 _public member_ `TSharedPtrTS<FBufferSourceInfo> BufferSourceInfo;`
- L652 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L653 _public member_ `uint32 NumAddedTotal = 0;`
- L654 _public member_ `int32 Bitrate = 0;`
- L655 _public member_ `bool bIsFirstInSequence = true;`
- L656 _public member_ `bool bReadPastLastPTS = false;`
- L657 _public member_ `bool bTaggedLastSample = false;`
- L658 _public member_ `bool bGotAllSamples = false;`
- L659 _public member_ `bool bNeedToRecalculateDurations = false;`
- L661 _public member_ `int64 MediaLocalFirstAUTime = 0;` — Track local time values
- L662 _public member_ `int64 MediaLocalLastAUTime = TNumericLimits<int64>::Max();`
- L663 _public member_ `int64 PTO = 0;`
- L664 _public member_ `FProducerTime ProducerTime;`
- L666 _public member_ `FTimeValue DefaultDurationFromCSD;` — Calculated values
- L668 _public member_ `int64 PrevPTS90k = 0;` — TS specific for DTS/PTR rollover detection
- L669 _public member_ `int64 PrevDTS90k = 0;`

#### struct `Electra::FStreamSegmentReaderCommon::FStreamHandler::FActiveTrackData::FSample`  
`struct FSample`  
_L584-608_
- L586 _public member_ `FTimeValue PTS;`
- L587 _public member_ `FAccessUnit* AU = nullptr;`
- L588 _public member_ `uint32 SequentialIndex = 0;`
- L589 _public function_ `FSample(FAccessUnit* InAU, uint32 InSequentialIndex) : PTS(InAU->PTS), AU(InAU), SequentialIndex(InSequentialIndex)`
- L590 _public function_ `FSample(const FSample& rhs)`
- L599 _public function_ `void Release()`
- L604 _public function_ `~FSample()`

#### class `Electra::FStreamSegmentReaderCommon::FStreamHandler::FBoxDataLoader`  
`class FBoxDataLoader : public MP4Utilities::IMP4DataReaderBase, public TSharedFromThis<FBoxDataLoader, ESPMode::ThreadSafe>`  
_L672-695_
- inherits: `MP4Utilities::IMP4DataReaderBase,TSharedFromThis<FBoxDataLoader,ESPMode::ThreadSafe>`
- L675 _public function_ `FBoxDataLoader(IGenericDataReader* InGenericReader) : GenericReader(InGenericReader)`
- L678 _public prototype_ `virtual ~FBoxDataLoader() = default;`
- L679 _public function_ `int64 ReadData(void* InOutBuffer, int64 InNumBytes, int64 InFromOffset, FCancellationCheckDelegate InCheckCancellationDelegate) override`
- L685 _public function_ `int64 GetTotalFileSize() override`
- L687 _public function_ `int64 GetCurrentFileOffset() override`
- L689 _public function_ `bool HasReachedEOF() override`
- L691 _public function_ `FString GetLastError() override`
- L694 _private member_ `IGenericDataReader* GenericReader = nullptr;`

#### struct `Electra::FStreamSegmentReaderCommon::FStreamHandler::FNoInitSegmentData`  
`struct FNoInitSegmentData`  
_L769-769_
- L769 _public member_ `struct FNoInitSegmentData {int32 Zero=0;};`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Electra`
- L23 _namespace_ `namespace Stream` (scope `Electra`)
- L25 _externvar_ `extern TAutoConsoleVariable<bool> CVarElectraStreamUseLegacyMP4;` (scope `Electra::Stream`)
- L386 _delegate_ `DECLARE_DELEGATE_OneParam(FFirstTimestampReceivedDelegate, TSharedPtrTS<FStreamSegmentRequestCommon>);`
- L618 _function_ `SortedAccessUnitFIFO.Sort([](const FActiveTrackData::FSample& a, const FActiveTrackData::FSample& b){return a.PTS < b.PTS;});` (scope `Electra::FStreamSegmentReaderCommon::FStreamHandler::FActiveTrackData::AddAccessUnit`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/isobmff/OptionKeynamesISOBMFF.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Electra`
- L11 _namespace_ `namespace ISOBMFF` (scope `Electra`)
- L14 _variable_ `const FName OptionKeyISOBMFFLoadConnectTimeout(TEXT("isob` (scope `Electra::ISOBMFF`) — (FTimeValue) value specifying connection timeout
- L15 _variable_ `const FName OptionKeyISOBMFFLoadNoDataTimeout(TEXT("isob` (scope `Electra::ISOBMFF`) — (FTimeValue) value specifying no-data timeout
- L17 _variable_ `const FName OptionKeyISOBMFFTruncateToShortestTrack(TEXT("isob` (scope `Electra::ISOBMFF`) — (bool) whether or not to truncate the movie duration to the shortest track

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/isobmff/PlaylistISOBMFF.h` (Private)


#### class `Electra::FManifestISOBMFFInternal`  
`class FManifestISOBMFFInternal : public IManifest, public TSharedFromThis<FManifestISOBMFFInternal, ESPMode::ThreadSafe>`  
_L24-440_
- inherits: `IManifest,TSharedFromThis<FManifestISOBMFFInternal,ESPMode::ThreadSafe>`
- desc: This class represents the internal "playlist" of an mp4 file. All metadata of the tracks it is composed of are maintained by this class.
- L49 _public prototype_ `FManifestISOBMFFInternal(IPlayerSessionServices* InPlayerSessionServices);`
- L50 _public prototype_ `virtual ~FManifestISOBMFFInternal();`
- L52 _public prototype_ `FErrorDetail Build(TArray<TSharedPtr<MP4Boxes::FMP4BoxBase>>&& InParsedRootBoxes, const FString& URL, TSharedPtr<FMP4DataLoader, ESPMode::ThreadSafe> InDataLoader, FMP4DataLoader::FCancellationCheckDelegate InCancelCheck);`
- L55 _public function_ `EMediaFormatType GetMediaFormatType() const override`
- L57 _public function_ `bool ReloadsPlaylistPeriodically() const override`
- L59 _public function_ `bool SupportsMultipleTracksPerKind() const override`
- L61 _public function_ `bool OrderOfTracksCanChangeDynamically() const override`
- L63 _public function_ `EType GetPresentationType() const override`
- L65 _public function_ `EReplayEventType GetReplayType() const override`
- L67 _public function_ `TSharedPtrTS<const FLowLatencyDescriptor> GetLowLatencyDescriptor() const override`
- L69 _public function_ `FTimeValue CalculateCurrentLiveLatency(const FTimeValue& InCurrentPlaybackPosition, const FTimeValue& InEncoderLatency, bool bViaLatencyElement) const override`
- L71 _public function_ `FTimeValue GetAnchorTime() const override`
- L73 _public function_ `FTimeRange GetTotalTimeRange() const override`
- L75 _public function_ `FTimeRange GetSeekableTimeRange() const override`
- L77 _public prototype_ `FTimeRange GetPlaybackRange(EPlaybackRangeType InRangeType) const override;`
- L78 _public function_ `FTimeValue GetDuration() const override`
- L80 _public function_ `FTimeValue GetDefaultStartTime() const override`
- L82 _public function_ `void ClearDefaultStartTime() override`
- L84 _public function_ `FTimeValue GetDefaultEndTime() const override`
- L86 _public function_ `void ClearDefaultEndTime() override`
- L88 _public prototype_ `void GetTrackMetadata(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override;`
- L89 _public function_ `void UpdateRunningMetaData(TSharedPtrTS<FMetadataParser> InUpdatedMetaData) override`
- L91 _public prototype_ `FTimeValue GetMinBufferTime() const override;`
- L92 _public function_ `FTimeValue GetDesiredLiveLatency() const override`
- L94 _public function_ `ELiveEdgePlayMode GetLiveEdgePlayMode() const override`
- L96 _public prototype_ `TRangeSet<double> GetPossiblePlaybackRates(EPlayRateType InForType) const override;`
- L97 _public prototype_ `TSharedPtrTS<IProducerReferenceTimeInfo> GetProducerReferenceTimeInfo(int64 ID) const override;`
- L98 _public function_ `void UpdateDynamicRefetchCounter() override`
- L100 _public function_ `void PrepareForLooping(int32 InNumLoopsToAdd) override`
- L102 _public function_ `void TriggerClockSync(EClockSyncType InClockSyncType) override`
- L104 _public function_ `void TriggerPlaylistRefresh() override`
- L106 _public function_ `void ReachedStableBuffer() override`
- L109 _public prototype_ `IStreamReader* CreateStreamReaderHandler() override;`
- L110 _public prototype_ `FResult FindPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L111 _public prototype_ `FResult FindNextPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, TSharedPtrTS<const IStreamSegment> CurrentSegment) override;`
- L422 _public prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L424 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents() const`
- L427 _public function_ `void SetURLFragmentComponents(TArray<FURL_RFC3986::FQueryParam> InURLFragmentComponents)`
- L430 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents()`
- L434 _public member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L435 _public member_ `TSharedPtrTS<FTimelineAssetISOBMFF> MediaAsset;`
- L437 _public member_ `TArray<FURL_RFC3986::FQueryParam> URLFragmentComponents;` — The URL fragment components
- L438 _public member_ `FTimeValue DefaultStartTime;`
- L439 _public member_ `FTimeValue DefaultEndTime;`

#### struct `Electra::FManifestISOBMFFInternal::FTrackInfo`  
`struct FTrackInfo`  
_L27-46_
- L29 _public member_ `TSharedPtr<MP4Boxes::FMP4Track::FFragmentInfo, ESPMode::ThreadSafe> FragmentInfo;`
- L30 _public member_ `TSharedPtr<MP4Boxes::FMP4Track, ESPMode::ThreadSafe> MP4Track;`
- L32 _public member_ `FCodecTypeFormat CodecFormat;`
- L33 _public member_ `FDRMTypeFormat DrmFormat;`
- L34 _public member_ `FDecoderInformation DecoderInformation;`
- L35 _public member_ `uint32 TrackID = 0;`
- L36 _public member_ `uint32 TrackTimescale = 0;`
- L44 _public member_ `TOptional<FFirstSampleTimecode> FirstSampleTimecode;`
- L45 _public member_ `TOptional<uint32> ReferencedTimecodeTrackID;`

#### struct `Electra::FManifestISOBMFFInternal::FTrackInfo::FFirstSampleTimecode`  
`struct FFirstSampleTimecode`  
_L38-43_
- L40 _public member_ `FString Timecode;`
- L41 _public member_ `FString Framerate;`
- L42 _public member_ `uint32 TimecodeValue = 0;`

#### class `Electra::FManifestISOBMFFInternal::FRepresentationISOBMFF`  
`class FRepresentationISOBMFF : public IPlaybackAssetRepresentation`  
_L114-142_
- inherits: `IPlaybackAssetRepresentation`
- L117 _public prototype_ `virtual ~FRepresentationISOBMFF() = default;`
- L119 _public prototype_ `void CreateFrom(TSharedPtr<FTrackInfo, ESPMode::ThreadSafe> InTrack, const FStreamCodecInformation& InCodecInfo);`
- L121 _public function_ `FString GetUniqueIdentifier() const override`
- L123 _public function_ `const FStreamCodecInformation& GetCodecInformation() const override`
- L125 _public function_ `int32 GetBitrate() const override`
- L127 _public function_ `int32 GetQualityIndex() const override`
- L129 _public function_ `bool CanBePlayed() const override`
- L132 _public function_ `const FString& GetName() const`
- L134 _public function_ `TSharedPtr<FTrackInfo, ESPMode::ThreadSafe> GetTrackInfo() const`
- L137 _private member_ `TSharedPtr<FTrackInfo, ESPMode::ThreadSafe> Track;`
- L138 _private member_ `FStreamCodecInformation CodecInformation;`
- L139 _private member_ `FString UniqueIdentifier;`
- L140 _private member_ `FString Name;`
- L141 _private member_ `int32 Bitrate;`

#### class `Electra::FManifestISOBMFFInternal::FAdaptationSetISOBMFF`  
`class FAdaptationSetISOBMFF : public IPlaybackAssetAdaptationSet`  
_L144-181_
- inherits: `IPlaybackAssetAdaptationSet`
- L147 _public prototype_ `virtual ~FAdaptationSetISOBMFF() = default;`
- L149 _public prototype_ `void CreateFrom(TSharedPtr<FTrackInfo, ESPMode::ThreadSafe> InTrack, const FStreamCodecInformation& InCodecInfo, int32 InSequentialIndex, int32 InIndexOfType);`
- L151 _public function_ `FString GetUniqueIdentifier() const override`
- L153 _public function_ `FString GetListOfCodecs() const override`
- L155 _public function_ `const BCP47::FLanguageTag& GetLanguageTag() const override`
- L157 _public function_ `int32 GetNumberOfRepresentations() const override`
- L159 _public function_ `bool IsLowLatencyEnabled() const override`
- L161 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByIndex(int32 RepresentationIndex) const override`
- L163 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByUniqueIdentifier(const FString& InUniqueIdentifier) const override`
- L165 _public function_ `TSharedPtrTS<FRepresentationISOBMFF> GetRepresentation() const`
- L167 _public function_ `FString GetTrackKind() const`
- L169 _public function_ `int32 GetInternalTrackIndex() const`
- L171 _public function_ `FTimespan GetInternalTrackDuration() const`
- L174 _private member_ `TSharedPtrTS<FRepresentationISOBMFF> Representation;`
- L175 _private member_ `BCP47::FLanguageTag LanguageTag;`
- L176 _private member_ `FString CodecRFC6381;`
- L177 _private member_ `FString KindOfTrack;`
- L178 _private member_ `FString UniqueIdentifier;`
- L179 _private member_ `FTimespan Duration;`
- L180 _private member_ `int32 InternalTrackIndex = -1;`

#### class `Electra::FManifestISOBMFFInternal::FTimelineAssetISOBMFF`  
`class FTimelineAssetISOBMFF : public ITimelineMediaAsset, public TSharedFromThis<FTimelineAssetISOBMFF, ESPMode::ThreadSafe>`  
_L183-366_
- inherits: `ITimelineMediaAsset,TSharedFromThis<FTimelineAssetISOBMFF,ESPMode::ThreadSafe>`
- L186 _public function_ `FTimelineAssetISOBMFF() : PlayerSessionServices(nullptr)`
- L190 _public prototype_ `virtual ~FTimelineAssetISOBMFF() = default;`
- L192 _public prototype_ `FErrorDetail Build(IPlayerSessionServices* InPlayerSessionServices, TArray<TSharedPtr<MP4Boxes::FMP4BoxBase, ESPMode::ThreadSafe>>&& InParsedRootBoxes, const FString& InURL, TSharedPtr<FMP4DataLoader, ESPMode::ThreadSafe> InDataLoader, FMP4DataLoader::FCancellationCheckDelegate InCancelCheck);`
- L195 _public function_ `FTimeRange GetTimeRange() const override`
- L203 _public function_ `FTimeValue GetDuration() const override`
- L206 _public function_ `FString GetAssetIdentifier() const override`
- L208 _public function_ `FString GetUniqueIdentifier() const override`
- L210 _public function_ `int32 GetNumberOfAdaptationSets(EStreamType OfStreamType) const override`
- L232 _public function_ `TSharedPtrTS<IPlaybackAssetAdaptationSet> GetAdaptationSetByTypeAndIndex(EStreamType OfStreamType, int32 AdaptationSetIndex) const override`
- L252 _public function_ `void GetMetaData(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override`
- L288 _public function_ `void UpdateRunningMetaData(const FString& InKindOfValue, const FVariant& InNewValue) override`
- L291 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID);`
- L292 _public function_ `const FString& GetMediaURL() const`
- L297 _public function_ `TSharedPtrTS<FAdaptationSetISOBMFF> GetAdaptationSetByTypeAndID(EStreamType InStreamType, const FString& InID) const`
- L332 _public function_ `ELoaderType GetLoaderType() const`
- L335 _public function_ `TSharedPtrTS<ElectraCDM::IMediaCDMClient> GetDrmClient() const`
- L352 _private prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L353 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L354 _private member_ `FString MediaURL;`
- L355 _private member_ `bool bIsLocalFile { false };`
- L356 _private member_ `ELoaderType LoaderType { ELoaderType::Chunks };`
- L357 _private member_ `FTimeValue OverallTrackDuration;`
- L358 _private member_ `TArray<TSharedPtr<MP4Boxes::FMP4BoxBase>> ParsedRootBoxes;`
- L359 _private member_ `TArray<TSharedPtrTS<FAdaptationSetISOBMFF>> VideoAdaptationSets;`
- L360 _private member_ `TArray<TSharedPtrTS<FAdaptationSetISOBMFF>> AudioAdaptationSets;`
- L361 _private member_ `TArray<TSharedPtrTS<FAdaptationSetISOBMFF>> SubtitleAdaptationSets;`
- L362 _private member_ `FPlayRangeEndInfo PlayRangeEndInfo;`
- L364 _private member_ `TSharedPtrTS<FMetadataParser> MediaMetadata;` — Metadata from the 'meta' box, if any.
- L365 _private member_ `TSharedPtrTS<ElectraCDM::IMediaCDMClient> DrmClient;`

#### enum `Electra::FManifestISOBMFFInternal::FTimelineAssetISOBMFF::ELoaderType`  
`enum class ELoaderType`  
_L326-331_
- L328 _public enumerator_ `Chunks`
- L329 _public enumerator_ `Muxed`
- L330 _public enumerator_ `Fragmented`

#### struct `Electra::FManifestISOBMFFInternal::FTimelineAssetISOBMFF::FPlayRangeEndInfo`  
`struct FPlayRangeEndInfo`  
_L339-350_
- L341 _public function_ `void Clear()`
- L347 _public member_ `FTimeValue Time;`
- L348 _public member_ `TArray<int64> FileOffsetsPerTrackID;`
- L349 _public member_ `int64 TotalFileEndOffset = -1;`

#### class `Electra::FManifestISOBMFFInternal::FPlayPeriodISOBMFF`  
`class FPlayPeriodISOBMFF : public IManifest::IPlayPeriod`  
_L369-420_
- inherits: `IManifest::IPlayPeriod`
- L372 _public prototype_ `FPlayPeriodISOBMFF(TSharedPtrTS<FTimelineAssetISOBMFF> InMediaAsset);`
- L373 _public prototype_ `virtual ~FPlayPeriodISOBMFF();`
- L374 _public prototype_ `void SetStreamPreferences(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) override;`
- L375 _public prototype_ `EReadyState GetReadyState() override;`
- L376 _public prototype_ `void Load() override;`
- L377 _public prototype_ `void PrepareForPlay() override;`
- L378 _public prototype_ `int64 GetDefaultStartingBitrate() const override;`
- L379 _public prototype_ `TSharedPtrTS<FBufferSourceInfo> GetSelectedStreamBufferSourceInfo(EStreamType StreamType) override;`
- L380 _public prototype_ `FString GetSelectedAdaptationSetID(EStreamType StreamType) override;`
- L381 _public prototype_ `ETrackChangeResult ChangeTrackStreamPreference(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) override;`
- L382 _public prototype_ `TSharedPtrTS<ITimelineMediaAsset> GetMediaAsset() const override;`
- L383 _public prototype_ `void SelectStream(const FString& AdaptationSetID, const FString& RepresentationID, int32 QualityIndex, int32 MaxQualityIndex) override;`
- L384 _public prototype_ `void TriggerInitSegmentPreload(const TArray<FInitSegmentPreload>& InitSegmentsToPreload) override;`
- L385 _public prototype_ `FResult GetStartingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L386 _public prototype_ `FResult GetContinuationSegment(TSharedPtrTS<IStreamSegment>& OutSegment, EStreamType InStreamType, const FPlayerSequenceState& InLoopState, const FPlayStartPosition& InStartPosition, ESearchType InSearchType) override;`
- L387 _public prototype_ `FResult GetNextSegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options) override;`
- L388 _public prototype_ `FResult GetRetrySegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options, bool bReplaceWithFillerData) override;`
- L389 _public prototype_ `FResult GetLoopingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L390 _public prototype_ `void IncreaseSegmentFetchDelay(const FTimeValue& IncreaseAmount) override;`
- L391 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID) override;`
- L394 _private prototype_ `void SelectInitialStream(EStreamType StreamType);`
- L395 _private prototype_ `TSharedPtrTS<FTrackMetadata> SelectMetadataForAttributes(EStreamType StreamType, const FStreamSelectionAttributes& InAttributes);`
- L396 _private prototype_ `void MakeBufferSourceInfoFromMetadata(EStreamType StreamType, TSharedPtrTS<FBufferSourceInfo>& OutBufferSourceInfo, TSharedPtrTS<FTrackMetadata> InMetadata);`
- L397 _private prototype_ `void AggregateChunkSamples(TSharedPtr<IStreamSegment, ESPMode::ThreadSafe> InOutRequest, const FTimespan& InMinDuration);`
- L404 _private prototype_ `void AdjustMuxedDownload(TSharedPtr<IStreamSegment, ESPMode::ThreadSafe> InOutRequest, const FTimespan& InMinDuration, EAdjustMuxType InType);`
- L406 _private member_ `TWeakPtrTS<FTimelineAssetISOBMFF> MediaAsset;`
- L407 _private member_ `FStreamSelectionAttributes VideoPreferences;`
- L408 _private member_ `FStreamSelectionAttributes AudioPreferences;`
- L409 _private member_ `FStreamSelectionAttributes SubtitlePreferences;`
- L410 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedVideoMetadata;`
- L411 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedAudioMetadata;`
- L412 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedSubtitleMetadata;`
- L413 _private member_ `TSharedPtrTS<FBufferSourceInfo> VideoBufferSourceInfo;`
- L414 _private member_ `TSharedPtrTS<FBufferSourceInfo> AudioBufferSourceInfo;`
- L415 _private member_ `TSharedPtrTS<FBufferSourceInfo> SubtitleBufferSourceInfo;`
- L416 _private member_ `EReadyState CurrentReadyState;`
- L417 _private member_ `FTimelineAssetISOBMFF::ELoaderType LoaderType;`
- L418 _private member_ `FTimespan AggregateMinChunkDuration;`
- L419 _private member_ `FTimespan MuxedSegmentDuration;`

#### enum `Electra::FManifestISOBMFFInternal::FPlayPeriodISOBMFF::EAdjustMuxType`  
`enum class EAdjustMuxType`  
_L398-403_
- L400 _public enumerator_ `FirstStart`
- L401 _public enumerator_ `Continuation`
- L402 _public enumerator_ `Retry`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Electra`
- L322 _function_ `auto Adpt = (*AdSet).FindByPredicate([InID](const TSharedPtrTS<FAdaptationSetISOBMFF>& e) {return e->GetUniqueIdentifier().Equals(InID);});` (scope `Electra::FManifestISOBMFFInternal::FTimelineAssetISOBMFF::GetAdaptationSetByTypeAndID`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/isobmff/PlaylistReaderISOBMFF.h` (Private)


#### class `Electra::IPlaylistReaderISOBMFF`  
`class IPlaylistReaderISOBMFF : public IPlaylistReader`  
_L12-18_
- inherits: `IPlaylistReader`
- L15 _public prototype_ `static TSharedPtrTS<IPlaylistReader> Create(IPlayerSessionServices* PlayerSessionServices);`
- L17 _public prototype_ `virtual ~IPlaylistReaderISOBMFF() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/isobmff/StreamReaderISOBMFF.h` (Private)


#### class `Electra::FStreamSegmentRequestISOBMFF`  
`class FStreamSegmentRequestISOBMFF : public IStreamSegment`  
_L26-112_
- inherits: `IStreamSegment`
- L29 _public prototype_ `FStreamSegmentRequestISOBMFF() = default;`
- L30 _public prototype_ `virtual ~FStreamSegmentRequestISOBMFF() = default;`
- L32 _public function_ `void SetPlaybackSequenceID(uint32 InPlaybackSequenceID) override`
- L34 _public function_ `uint32 GetPlaybackSequenceID() const override`
- L36 _public function_ `void SetExecutionDelay(const FTimeValue& UTCNow, const FTimeValue& ExecutionDelay) override`
- L38 _public function_ `FTimeValue GetExecuteAtUTCTime() const override`
- L40 _public function_ `EStreamType GetType() const override`
- L43 _public prototype_ `void GetDependentStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutDependentStreams) const override;`
- L44 _public prototype_ `void GetRequestedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutRequestedStreams) override;`
- L45 _public prototype_ `void GetEndedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutAlreadyEndedStreams) override;`
- L47 _public function_ `FTimeValue GetFirstPTS() const override`
- L53 _public prototype_ `FTimeRange GetTimeRange() const override;`
- L55 _public function_ `int32 GetQualityIndex() const override`
- L57 _public function_ `int32 GetBitrate() const override`
- L60 _public function_ `void GetDownloadStats(Metrics::FSegmentDownloadStats& OutStats) const override`
- L62 _public function_ `bool GetStartupDelay(FTimeValue& OutStartTime, FTimeValue& OutTimeIntoSegment, FTimeValue& OutSegmentDuration) const override`
- L78 _public member_ `TSharedPtrTS<ITimelineMediaAsset> MediaAsset;`
- L79 _public member_ `ELoaderType LoaderType { ELoaderType::Chunks };`
- L80 _public member_ `FString AssetID;`
- L81 _public member_ `FString AdaptationSetID;`
- L82 _public member_ `FString RepresentationID;`
- L83 _public member_ `int32 AdaptationSetTrackIndex { 0 };`
- L84 _public member_ `FString MediaURL;`
- L85 _public member_ `BCP47::FLanguageTag LanguageTag;`
- L86 _public member_ `FString KindOfTrack;`
- L87 _public member_ `TArray<TSharedPtrTS<FStreamSegmentRequestISOBMFF>> DependentStreams;`
- L88 _public member_ `FTrack Track;`
- L89 _public member_ `FTimeValue FirstDTS;`
- L90 _public member_ `FTimeValue EarliestPTS;`
- L91 _public member_ `FTimeValue LastPTS;`
- L92 _public member_ `FTimeValue SegmentDuration;`
- L93 _public member_ `EStreamType StreamType {EStreamType::Unsupported};`
- L94 _public member_ `int64 TimestampSequenceIndex { 0 };`
- L95 _public member_ `uint32 PlaybackSequenceID { ~0U };`
- L96 _public member_ `int32 Bitrate { 0 };`
- L97 _public member_ `int32 NumOverallRetries { 0 };`
- L98 _public member_ `bool bIsLastSegment { false };`
- L101 _public member_ `int64 PrimarySampleFileOffsetStart { -1 };` — File offsets when reading sequentially all track data in the multiplex
- L102 _public member_ `int64 PrimarySampleFileOffsetEnd { -1 };`
- L103 _public member_ `int32 ReportingIndexInMux { -1 };`
- L104 _public member_ `bool bWasSelectedAtStart { false };`
- L107 _public member_ `TSharedPtrTS<ElectraCDM::IMediaCDMClient> DrmClient;` — Encryption
- L110 _public member_ `Metrics::FSegmentDownloadStats DownloadStats;` — Download stats that are set during and after download.
- L111 _public member_ `HTTP::FConnectionInfo ConnectionInfo;`

#### struct `Electra::FStreamSegmentRequestISOBMFF::FTrack`  
`struct FTrack`  
_L65-70_
- L67 _public member_ `TSharedPtr<FManifestISOBMFFInternal::FTrackInfo, ESPMode::ThreadSafe> TrackInfo;`
- L68 _public member_ `TSharedPtr<MP4Boxes::FMP4Track::FIterator, ESPMode::ThreadSafe> TrackIterator;`
- L69 _public member_ `MP4Boxes::FMP4Track::FIterator::FChunkInfo TrackChunkSampleInfo;`

#### enum `Electra::FStreamSegmentRequestISOBMFF::ELoaderType`  
`enum class ELoaderType`  
_L71-76_
- L73 _public enumerator_ `Chunks`
- L74 _public enumerator_ `Muxed`
- L75 _public enumerator_ `Fragmented`

#### class `Electra::FStreamReaderISOBMFF`  
`class FStreamReaderISOBMFF : public IStreamReader`  
_L118-173_
- inherits: `IStreamReader`
- desc: This class implements an interface to read from an mp4 file.
- L121 _public prototype_ `FStreamReaderISOBMFF() = default;`
- L122 _public prototype_ `virtual ~FStreamReaderISOBMFF();`
- L123 _public prototype_ `void SetLoaderType(FStreamSegmentRequestISOBMFF::ELoaderType InLoaderType);`
- L124 _public prototype_ `UEMediaError Create(IPlayerSessionServices* PlayerSessionService, const CreateParam &createParam) override;`
- L125 _public prototype_ `bool LoadsMultiplexedTracksSequentially() override;`
- L126 _public prototype_ `void Close() override;`
- L127 _public prototype_ `EAddResult AddRequest(uint32 CurrentPlaybackSequenceID, TSharedPtrTS<IStreamSegment> Request) override;`
- L128 _public prototype_ `void CancelRequest(EStreamType StreamType, bool bSilent) override;`
- L129 _public prototype_ `void CancelRequests() override;`
- L132 _private prototype_ `ELECTRA_IMPL_DEFAULT_ERROR_METHODS(ISOBMFFStreamReader);`
- L168 _private member_ `FStreamSegmentRequestISOBMFF::ELoaderType LoaderType { FStreamSegmentRequestISOBMFF::ELoaderType::Chunks };`
- L169 _private member_ `FStreamHandler StreamHandlers[3];` — 0 = video (or multiplexed), 1 = audio, 2 = subtitle
- L170 _private member_ `FErrorDetail ErrorDetail;`
- L171 _private member_ `IPlayerSessionServices* PlayerSessionService = nullptr;`
- L172 _private member_ `bool bIsStarted = false;`

#### struct `Electra::FStreamReaderISOBMFF::FStreamHandler`  
`struct FStreamHandler : public FMediaThread`  
_L134-165_
- inherits: `FMediaThread`
- L136 _public prototype_ `FStreamHandler() = default;`
- L137 _public prototype_ `virtual ~FStreamHandler() = default;`
- L138 _public prototype_ `void Cancel(bool bSilent);`
- L139 _public prototype_ `void SignalWork();`
- L140 _public prototype_ `void WorkerThread();`
- L141 _public prototype_ `void SetError(const FString& InMessage, uint16 InCode);`
- L142 _public prototype_ `bool HasErrored() const;`
- L143 _public prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L144 _public prototype_ `int32 HTTPProgressCallback(const IElectraHttpManager::FRequest* Request);`
- L145 _public prototype_ `void HTTPCompletionCallback(const IElectraHttpManager::FRequest* Request);`
- L146 _public prototype_ `void HTTPUpdateStats(const FTimeValue& CurrentTime, const IElectraHttpManager::FRequest* Request);`
- L147 _public prototype_ `void HandleMuxedRequest();`
- L148 _public prototype_ `void HandleChunkOrFragmentRequest();`
- L149 _public prototype_ `bool HasBeenAborted() const;`
- L151 _public member_ `IStreamReader::CreateParam Parameters;`
- L152 _public member_ `FMediaSemaphore WorkSignal;`
- L153 _public member_ `FMediaEvent IsIdleSignal;`
- L154 _public member_ `TSharedPtrTS<FStreamSegmentRequestISOBMFF> CurrentRequest;`
- L155 _public member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L156 _public member_ `volatile bool bTerminate = false;`
- L157 _public member_ `volatile bool bWasStarted = false;`
- L158 _public member_ `volatile bool bRequestCanceled = false;`
- L159 _public member_ `volatile bool bSilentCancellation = false;`
- L160 _public member_ `volatile bool bHasErrored = false;`
- L162 _public member_ `TSharedPtrTS<FWaitableBuffer> ReceiveBuffer;`
- L164 _public member_ `static std::atomic<uint32> UniqueDownloadID;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mkv/ManifestMKV.h` (Private)


#### class `Electra::FManifestMKVInternal`  
`class FManifestMKVInternal : public IManifest, public TSharedFromThis<FManifestMKVInternal, ESPMode::ThreadSafe>`  
_L25-342_
- inherits: `IManifest,TSharedFromThis<FManifestMKVInternal,ESPMode::ThreadSafe>`
- desc: This class represents the internal "manifest" or "playlist" of an mkv file. All metadata of the tracks it is composed of are maintained by this class.
- L28 _public prototype_ `FManifestMKVInternal(IPlayerSessionServices* InPlayerSessionServices);`
- L29 _public prototype_ `virtual ~FManifestMKVInternal();`
- L31 _public prototype_ `FErrorDetail Build(TSharedPtrTS<IParserMKV> MP4Parser, const FString& URL, const HTTP::FConnectionInfo& InConnectionInfo);`
- L33 _public prototype_ `EMediaFormatType GetMediaFormatType() const override;`
- L34 _public prototype_ `bool ReloadsPlaylistPeriodically() const override;`
- L35 _public prototype_ `bool SupportsMultipleTracksPerKind() const override;`
- L36 _public prototype_ `bool OrderOfTracksCanChangeDynamically() const override;`
- L37 _public prototype_ `EType GetPresentationType() const override;`
- L38 _public function_ `EReplayEventType GetReplayType() const override`
- L40 _public function_ `TSharedPtrTS<const FLowLatencyDescriptor> GetLowLatencyDescriptor() const override`
- L42 _public function_ `FTimeValue CalculateCurrentLiveLatency(const FTimeValue& InCurrentPlaybackPosition, const FTimeValue& InEncoderLatency, bool bViaLatencyElement) const override`
- L44 _public function_ `FTimeValue GetAnchorTime() const override`
- L46 _public function_ `FTimeRange GetTotalTimeRange() const override`
- L48 _public function_ `FTimeRange GetSeekableTimeRange() const override`
- L53 _public prototype_ `FTimeRange GetPlaybackRange(EPlaybackRangeType InRangeType) const override;`
- L54 _public function_ `FTimeValue GetDuration() const override`
- L56 _public function_ `FTimeValue GetDefaultStartTime() const override`
- L58 _public function_ `void ClearDefaultStartTime() override`
- L60 _public function_ `FTimeValue GetDefaultEndTime() const override`
- L62 _public function_ `void ClearDefaultEndTime() override`
- L64 _public prototype_ `void GetTrackMetadata(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override;`
- L65 _public prototype_ `void UpdateRunningMetaData(TSharedPtrTS<FMetadataParser> InUpdatedMetaData) override;`
- L66 _public prototype_ `FTimeValue GetMinBufferTime() const override;`
- L67 _public function_ `FTimeValue GetDesiredLiveLatency() const override`
- L69 _public function_ `ELiveEdgePlayMode GetLiveEdgePlayMode() const override`
- L71 _public prototype_ `TRangeSet<double> GetPossiblePlaybackRates(EPlayRateType InForType) const override;`
- L72 _public prototype_ `TSharedPtrTS<IProducerReferenceTimeInfo> GetProducerReferenceTimeInfo(int64 ID) const override;`
- L73 _public prototype_ `void UpdateDynamicRefetchCounter() override;`
- L74 _public function_ `void PrepareForLooping(int32 InNumLoopsToAdd) override`
- L76 _public prototype_ `void TriggerClockSync(EClockSyncType InClockSyncType) override;`
- L77 _public prototype_ `void TriggerPlaylistRefresh() override;`
- L78 _public function_ `void ReachedStableBuffer() override`
- L81 _public prototype_ `IStreamReader* CreateStreamReaderHandler() override;`
- L82 _public prototype_ `FResult FindPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L83 _public prototype_ `FResult FindNextPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, TSharedPtrTS<const IStreamSegment> CurrentSegment) override;`
- L321 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents() const`
- L326 _public function_ `void SetURLFragmentComponents(TArray<FURL_RFC3986::FQueryParam> InURLFragmentComponents)`
- L331 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents()`
- L336 _public member_ `IPlayerSessionServices* PlayerSessionServices;`
- L337 _public member_ `TSharedPtrTS<FTimelineAssetMKV> MediaAsset;`
- L338 _public member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L339 _public member_ `TArray<FURL_RFC3986::FQueryParam> URLFragmentComponents;`
- L340 _public member_ `FTimeValue DefaultStartTime;`
- L341 _public member_ `FTimeValue DefaultEndTime;`

#### class `Electra::FManifestMKVInternal::FRepresentationMKV`  
`class FRepresentationMKV : public IPlaybackAssetRepresentation`  
_L86-112_
- inherits: `IPlaybackAssetRepresentation`
- L89 _public prototype_ `virtual ~FRepresentationMKV() = default;`
- L91 _public prototype_ `FErrorDetail CreateFrom(const IParserMKV::ITrack* InTrack, const FString& URL);`
- L93 _public function_ `FString GetUniqueIdentifier() const override`
- L95 _public function_ `const FStreamCodecInformation& GetCodecInformation() const override`
- L97 _public function_ `int32 GetBitrate() const override`
- L99 _public function_ `int32 GetQualityIndex() const override`
- L101 _public function_ `bool CanBePlayed() const override`
- L104 _public function_ `const FString& GetName() const`
- L107 _private member_ `FStreamCodecInformation CodecInformation;`
- L108 _private member_ `FString UniqueIdentifier;`
- L109 _private member_ `FString Name;`
- L110 _private member_ `int32 Bitrate;`
- L111 _private member_ `TArray<uint8> CodecSpecificData;`

#### class `Electra::FManifestMKVInternal::FAdaptationSetMKV`  
`class FAdaptationSetMKV : public IPlaybackAssetAdaptationSet`  
_L114-141_
- inherits: `IPlaybackAssetAdaptationSet`
- L117 _public prototype_ `virtual ~FAdaptationSetMKV() = default;`
- L119 _public prototype_ `FErrorDetail CreateFrom(const IParserMKV::ITrack* InTrack, const FString& URL);`
- L121 _public function_ `FString GetUniqueIdentifier() const override`
- L123 _public function_ `FString GetListOfCodecs() const override`
- L125 _public function_ `const BCP47::FLanguageTag& GetLanguageTag() const override`
- L128 _public function_ `int32 GetNumberOfRepresentations() const override`
- L130 _public function_ `bool IsLowLatencyEnabled() const override`
- L132 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByIndex(int32 RepresentationIndex) const override`
- L134 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByUniqueIdentifier(const FString& InUniqueIdentifier) const override`
- L137 _private member_ `TSharedPtrTS<FRepresentationMKV> Representation;`
- L138 _private member_ `BCP47::FLanguageTag LanguageTag;`
- L139 _private member_ `FString CodecRFC6381;`
- L140 _private member_ `FString UniqueIdentifier;`

#### class `Electra::FManifestMKVInternal::FTimelineAssetMKV`  
`class FTimelineAssetMKV : public ITimelineMediaAsset, public TSharedFromThis<FTimelineAssetMKV, ESPMode::ThreadSafe>`  
_L143-276_
- inherits: `ITimelineMediaAsset,TSharedFromThis<FTimelineAssetMKV,ESPMode::ThreadSafe>`
- L146 _public function_ `FTimelineAssetMKV() : PlayerSessionServices(nullptr)`
- L150 _public prototype_ `virtual ~FTimelineAssetMKV() = default;`
- L152 _public prototype_ `FErrorDetail Build(IPlayerSessionServices* InPlayerSessionServices, TSharedPtrTS<IParserMKV> InMKVParser, const FString& InURL);`
- L154 _public function_ `virtual FTimeRange GetTimeRange() const override`
- L162 _public function_ `virtual FTimeValue GetDuration() const override`
- L167 _public function_ `virtual FString GetAssetIdentifier() const override`
- L169 _public function_ `virtual FString GetUniqueIdentifier() const override`
- L171 _public function_ `virtual int32 GetNumberOfAdaptationSets(EStreamType OfStreamType) const override`
- L193 _public function_ `virtual TSharedPtrTS<IPlaybackAssetAdaptationSet> GetAdaptationSetByTypeAndIndex(EStreamType OfStreamType, int32 AdaptationSetIndex) const override`
- L217 _public function_ `virtual void GetMetaData(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override`
- L252 _public function_ `void UpdateRunningMetaData(const FString& InKindOfValue, const FVariant& InNewValue) override`
- L255 _public prototype_ `FResult GetStartingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, FString InSelectedStreamID, const FPlayStartPosition& StartPosition, ESearchType SearchType, int64 AtAbsoluteFilePos);`
- L256 _public prototype_ `FResult GetNextSegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options);`
- L257 _public prototype_ `FResult GetRetrySegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options, bool bReplaceWithFillerData);`
- L258 _public prototype_ `FResult GetLoopingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, FString SelectedStreamID, const FPlayStartPosition& StartPosition, ESearchType SearchType);`
- L260 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID);`
- L261 _public prototype_ `TSharedPtrTS<IParserMKV> GetMKVParser();`
- L262 _public function_ `const FString& GetMediaURL() const`
- L268 _private member_ `IPlayerSessionServices* PlayerSessionServices;`
- L269 _private member_ `FString MediaURL;`
- L270 _private member_ `FTimeValue MovieDuration;`
- L271 _private member_ `TSharedPtrTS<IParserMKV> MKVParser;`
- L272 _private member_ `TArray<TSharedPtrTS<FAdaptationSetMKV>> VideoAdaptationSets;`
- L273 _private member_ `TArray<TSharedPtrTS<FAdaptationSetMKV>> AudioAdaptationSets;`
- L274 _private member_ `TArray<TSharedPtrTS<FAdaptationSetMKV>> SubtitleAdaptationSets;`
- L275 _private member_ `TArray<uint64> UsableTrackIDs;`

#### class `Electra::FManifestMKVInternal::FPlayPeriodMKV`  
`class FPlayPeriodMKV : public IManifest::IPlayPeriod`  
_L279-319_
- inherits: `IManifest::IPlayPeriod`
- L282 _public prototype_ `FPlayPeriodMKV(TSharedPtrTS<FTimelineAssetMKV> InMediaAsset);`
- L283 _public prototype_ `virtual ~FPlayPeriodMKV();`
- L284 _public prototype_ `void SetStreamPreferences(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) override;`
- L285 _public prototype_ `EReadyState GetReadyState() override;`
- L286 _public prototype_ `void Load() override;`
- L287 _public prototype_ `void PrepareForPlay() override;`
- L288 _public prototype_ `int64 GetDefaultStartingBitrate() const override;`
- L289 _public prototype_ `TSharedPtrTS<FBufferSourceInfo> GetSelectedStreamBufferSourceInfo(EStreamType StreamType) override;`
- L290 _public prototype_ `FString GetSelectedAdaptationSetID(EStreamType StreamType) override;`
- L291 _public prototype_ `ETrackChangeResult ChangeTrackStreamPreference(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) override;`
- L292 _public prototype_ `TSharedPtrTS<ITimelineMediaAsset> GetMediaAsset() const override;`
- L293 _public prototype_ `void SelectStream(const FString& AdaptationSetID, const FString& RepresentationID, int32 QualityIndex, int32 MaxQualityIndex) override;`
- L294 _public prototype_ `void TriggerInitSegmentPreload(const TArray<FInitSegmentPreload>& InitSegmentsToPreload) override;`
- L295 _public prototype_ `FResult GetStartingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L296 _public prototype_ `FResult GetContinuationSegment(TSharedPtrTS<IStreamSegment>& OutSegment, EStreamType StreamType, const FPlayerSequenceState& LoopState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L297 _public prototype_ `FResult GetNextSegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options) override;`
- L298 _public prototype_ `FResult GetRetrySegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options, bool bReplaceWithFillerData) override;`
- L299 _public prototype_ `FResult GetLoopingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L300 _public prototype_ `void IncreaseSegmentFetchDelay(const FTimeValue& IncreaseAmount) override;`
- L301 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID) override;`
- L304 _private prototype_ `void SelectInitialStream(EStreamType StreamType);`
- L305 _private prototype_ `TSharedPtrTS<FTrackMetadata> SelectMetadataForAttributes(EStreamType StreamType, const FStreamSelectionAttributes& InAttributes);`
- L306 _private prototype_ `void MakeBufferSourceInfoFromMetadata(EStreamType StreamType, TSharedPtrTS<FBufferSourceInfo>& OutBufferSourceInfo, TSharedPtrTS<FTrackMetadata> InMetadata);`
- L308 _private member_ `TWeakPtrTS<FTimelineAssetMKV> MediaAsset;`
- L309 _private member_ `FStreamSelectionAttributes VideoPreferences;`
- L310 _private member_ `FStreamSelectionAttributes AudioPreferences;`
- L311 _private member_ `FStreamSelectionAttributes SubtitlePreferences;`
- L312 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedVideoMetadata;`
- L313 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedAudioMetadata;`
- L314 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedSubtitleMetadata;`
- L315 _private member_ `TSharedPtrTS<FBufferSourceInfo> VideoBufferSourceInfo;`
- L316 _private member_ `TSharedPtrTS<FBufferSourceInfo> AudioBufferSourceInfo;`
- L317 _private member_ `TSharedPtrTS<FBufferSourceInfo> SubtitleBufferSourceInfo;`
- L318 _private member_ `EReadyState CurrentReadyState;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mkv/OptionKeynamesMKV.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L9 _namespace_ `namespace MKV` (scope `Electra`)
- L12 _variable_ `const FName OptionKeyMKVLoadConnectTimeout(TEXT("mkv_` (scope `Electra::MKV`) — (FTimeValue) value specifying connection timeout fetching the MKV
- L13 _variable_ `const FName OptionKeyMKVLoadNoDataTimeout(TEXT("mkv_` (scope `Electra::MKV`) — (FTimeValue) value specifying no-data timeout fetching the MKV

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mkv/PlaylistReaderMKV.h` (Private)


#### class `Electra::IPlaylistReaderMKV`  
`class IPlaylistReaderMKV : public IPlaylistReader`  
_L13-19_
- inherits: `IPlaylistReader`
- L16 _public prototype_ `static TSharedPtrTS<IPlaylistReader> Create(IPlayerSessionServices* PlayerSessionServices);`
- L18 _public prototype_ `virtual ~IPlaylistReaderMKV() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mkv/StreamReaderMKV.h` (Private)


#### class `Electra::FStreamSegmentRequestMKV`  
`class FStreamSegmentRequestMKV : public IStreamSegment`  
_L20-98_
- inherits: `IStreamSegment`
- L23 _public prototype_ `FStreamSegmentRequestMKV() = default;`
- L24 _public prototype_ `virtual ~FStreamSegmentRequestMKV() = default;`
- L26 _public prototype_ `void SetPlaybackSequenceID(uint32 InPlaybackSequenceID) override;`
- L27 _public prototype_ `uint32 GetPlaybackSequenceID() const override;`
- L29 _public prototype_ `void SetExecutionDelay(const FTimeValue& UTCNow, const FTimeValue& ExecutionDelay) override;`
- L30 _public prototype_ `FTimeValue GetExecuteAtUTCTime() const override;`
- L32 _public prototype_ `EStreamType GetType() const override;`
- L34 _public prototype_ `void GetDependentStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutDependentStreams) const override;`
- L35 _public prototype_ `void GetRequestedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutRequestedStreams) override;`
- L36 _public prototype_ `void GetEndedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutAlreadyEndedStreams) override;`
- L38 _public prototype_ `FTimeValue GetFirstPTS() const override;`
- L39 _public prototype_ `FTimeRange GetTimeRange() const override;`
- L41 _public prototype_ `int32 GetQualityIndex() const override;`
- L42 _public prototype_ `int32 GetBitrate() const override;`
- L44 _public prototype_ `void GetDownloadStats(Metrics::FSegmentDownloadStats& OutStats) const override;`
- L45 _public function_ `bool GetStartupDelay(FTimeValue& OutStartTime, FTimeValue& OutTimeIntoSegment, FTimeValue& OutSegmentDuration) const override`
- L50 _public member_ `TArray<uint64> EnabledTrackIDs;` — Which tracks are enabled and will be extracted.
- L53 _public member_ `TSharedPtrTS<ITimelineMediaAsset> MediaAsset;` — The generated MKV asset
- L55 _public member_ `TSharedPtrTS<IParserMKV> MKVParser;` — MKV parser instance
- L58 _public member_ `FTimeValue FirstPTS;` — The PTS of the first sample
- L59 _public member_ `FTimeValue SegmentDuration;`
- L62 _public member_ `FTimeValue EarliestPTS;` — PTS of the first sample to be presented.
- L64 _public member_ `FTimeValue LastPTS;` — PTS at which no further samples are to be presented.
- L66 _public member_ `int64 TimestampSequenceIndex = 0;` — Sequence index to set in all timestamp values of the decoded access unit.
- L69 _public member_ `EStreamType PrimaryStreamType = EStreamType::Unsupported;` — Type of the stream for which the request was generated
- L71 _public member_ `int64 FileStartOffset = -1;` — Where to start in the file
- L73 _public member_ `int64 FileEndOffset = -1;` — Where to end in the file (for HTTP range GET requests)
- L75 _public member_ `int64 RetryBlockOffset = -1;` — Where to skip to on a retry.
- L77 _public member_ `uint64 PrimaryTrackID = 0;`
- L78 _public member_ `uint32 CueUniqueID = ~0U;`
- L79 _public member_ `uint32 NextCueUniqueID = ~0U;`
- L80 _public member_ `uint32 PlaybackSequenceID = ~0U;`
- L83 _public member_ `int64 FailedClusterFileOffset = -1;` — Offset of the cluster in which an error occurred.
- L84 _public member_ `int64 FailedClusterDataOffset = -1;`
- L86 _public member_ `int32 NumOverallRetries = 0;` — Number of retries
- L88 _public member_ `int32 Bitrate = 0;`
- L90 _public member_ `bool bIsFirstSegment = false;` — true if this segment is the first to start with or the first after a seek.
- L92 _public member_ `bool bIsLastSegment = false;` — true if this segment is the last.
- L94 _public member_ `bool bIsEOSSegment = false;` — true if this segment it beyond the end of the stream.
- L96 _public member_ `Metrics::FSegmentDownloadStats DownloadStats;`
- L97 _public member_ `HTTP::FConnectionInfo ConnectionInfo;`

#### class `Electra::FStreamReaderMKV`  
`class FStreamReaderMKV : public IStreamReader, public FMediaThread, IGenericDataReader`  
_L104-275_
- inherits: `IStreamReader,FMediaThread,IGenericDataReader`
- desc: This class implements an interface to read from an mkv/webm file.
- L107 _public prototype_ `FStreamReaderMKV() = default;`
- L108 _public prototype_ `virtual ~FStreamReaderMKV();`
- L109 _public prototype_ `UEMediaError Create(IPlayerSessionServices* PlayerSessionService, const CreateParam &createParam) override;`
- L110 _public prototype_ `bool LoadsMultiplexedTracksSequentially() override;`
- L111 _public prototype_ `void Close() override;`
- L112 _public prototype_ `EAddResult AddRequest(uint32 CurrentPlaybackSequenceID, TSharedPtrTS<IStreamSegment> Request) override;`
- L113 _public prototype_ `void CancelRequest(EStreamType StreamType, bool bSilent) override;`
- L114 _public prototype_ `void CancelRequests() override;`
- L117 _public prototype_ `int64 ReadData(void* InDestinationBuffer, int64 InNumBytesToRead, int64 InFromOffset) override;` — Methods from IGenericDataReader
- L118 _public prototype_ `int64 GetCurrentOffset() const override;`
- L119 _public prototype_ `int64 GetTotalSize() const override;`
- L120 _public prototype_ `bool HasReadBeenAborted() const override;`
- L121 _public prototype_ `bool HasReachedEOF() const override;`
- L124 _private prototype_ `void WorkerThread();`
- L125 _private prototype_ `int32 HTTPProgressCallback(const IElectraHttpManager::FRequest* InRequest);`
- L126 _private prototype_ `void HTTPCompletionCallback(const IElectraHttpManager::FRequest* InRequest);`
- L127 _private prototype_ `void HTTPUpdateStats(const FTimeValue& CurrentTime, const IElectraHttpManager::FRequest* Request);`
- L128 _private prototype_ `void HandleRequest();`
- L142 _private prototype_ `EEmitResult EmitSamples(EEmitType InEmitType, const TSharedPtrTS<FStreamSegmentRequestMKV>& InRequest);`
- L144 _private prototype_ `bool HasBeenAborted() const;`
- L145 _private prototype_ `bool HasErrored() const;`
- L260 _private member_ `CreateParam Parameters;`
- L261 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L262 _private member_ `bool bIsStarted = false;`
- L263 _private member_ `bool bTerminate = false;`
- L264 _private member_ `bool bRequestCanceled = false;`
- L265 _private member_ `bool bHasErrored = false;`
- L266 _private member_ `FErrorDetail ErrorDetail;`
- L268 _private member_ `TSharedPtrTS<FStreamSegmentRequestMKV> CurrentRequest;`
- L269 _private member_ `TSharedPtrTS<IElectraHttpManager::FRequest> HTTPRequest;`
- L270 _private member_ `FMediaEvent WorkSignal;`
- L271 _private member_ `FReadBuffer ReadBuffer;`
- L272 _private member_ `FCriticalSection MetricUpdateLock;`
- L273 _private member_ `TMap<uint64, FSelectedTrackData> ActiveTrackMap;`
- L274 _private member_ `static uint32 UniqueDownloadID;`

#### enum `Electra::FStreamReaderMKV::EEmitType`  
`enum class EEmitType`  
_L130-135_
- L132 _public enumerator_ `One`
- L133 _public enumerator_ `AllRemaining`
- L134 _public enumerator_ `KnownDurationOnly`

#### enum `Electra::FStreamReaderMKV::EEmitResult`  
`enum class EEmitResult`  
_L136-141_
- L138 _public enumerator_ `SentNothing`
- L139 _public enumerator_ `Sent`
- L140 _public enumerator_ `AllReachedEOS`

#### struct `Electra::FStreamReaderMKV::FReadBuffer`  
`struct FReadBuffer`  
_L147-206_
- L149 _public function_ `FReadBuffer()`
- L153 _public function_ `void Reset()`
- L162 _public function_ `void SetStartOffset(int64 InPos)`
- L166 _public function_ `int64 GetStartOffset() const`
- L170 _public function_ `void SetEndOffset(int64 InPos)`
- L174 _public function_ `void SetCurrentOffset(int64 InPos)`
- L178 _public function_ `int64 GetCurrentOffset() const`
- L182 _public function_ `int64 GetTotalSize() const`
- L186 _public function_ `void Abort()`
- L195 _public function_ `void SetHasErrored()`
- L199 _public prototype_ `int32 ReadTo(void* ToBuffer, int64 NumBytes);`
- L200 _public member_ `TSharedPtrTS<FWaitableBuffer> ReceiveBuffer;`
- L201 _public member_ `int64 StartOffset = 0;`
- L202 _public member_ `int64 EndOffset = 0;`
- L203 _public member_ `int64 CurrentOffset = 0;`
- L204 _public member_ `bool bAbort = false;`
- L205 _public member_ `bool bHasErrored = false;`

#### struct `Electra::FStreamReaderMKV::FSelectedTrackData`  
`struct FSelectedTrackData`  
_L208-258_
- L210 _public function_ `void Clear()`
- L245 _public member_ `TSharedPtrTS<FAccessUnit::CodecData> CSD;`
- L246 _public member_ `TSharedPtrTS<FBufferSourceInfo> BufferSourceInfo;`
- L247 _public member_ `FTimeValue DurationSuccessfullyRead {(int64)0};`
- L248 _public member_ `FTimeValue DurationSuccessfullyDelivered {(int64)0};`
- L249 _public member_ `EStreamType StreamType = EStreamType::Unsupported;`
- L250 _public member_ `int32 Bitrate = 0;`
- L251 _public member_ `bool bIsFirstInSequence = true;`
- L252 _public member_ `bool bReadPastLastPTS = false;`
- L253 _public member_ `TArray<FSample> AccessUnitFIFO;`
- L254 _public member_ `TArray<FSample> SortedAccessUnitFIFO;`
- L255 _public member_ `bool bGotAllSamples = false;`
- L256 _public member_ `bool bNeedToRecalculateDurations = false;`
- L257 _public member_ `bool bReachedEndOfKnownDuration = false;`

#### struct `Electra::FStreamReaderMKV::FSelectedTrackData::FSample`  
`struct FSample`  
_L221-243_
- L223 _public member_ `FTimeValue PTS;`
- L224 _public member_ `FAccessUnit* AU = nullptr;`
- L225 _public function_ `FSample(FAccessUnit* InAU) : PTS(InAU->PTS), AU(InAU)`
- L226 _public function_ `FSample(const FSample& rhs)`
- L234 _public function_ `void Release()`
- L239 _public function_ `~FSample()`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mp4/ManifestMP4.h` (Private)


#### class `Electra::FManifestMP4Internal`  
`class FManifestMP4Internal : public IManifest, public TSharedFromThis<FManifestMP4Internal, ESPMode::ThreadSafe>`  
_L25-347_
- inherits: `IManifest,TSharedFromThis<FManifestMP4Internal,ESPMode::ThreadSafe>`
- desc: This class represents the internal "manifest" or "playlist" of an mp4 file. All metadata of the tracks it is composed of are maintained by this class.
- L28 _public prototype_ `FManifestMP4Internal(IPlayerSessionServices* InPlayerSessionServices);`
- L29 _public prototype_ `virtual ~FManifestMP4Internal();`
- L31 _public prototype_ `FErrorDetail Build(TSharedPtrTS<IParserISO14496_12> MP4Parser, const FString& URL, const HTTP::FConnectionInfo& InConnectionInfo);`
- L33 _public prototype_ `EMediaFormatType GetMediaFormatType() const override;`
- L34 _public prototype_ `bool ReloadsPlaylistPeriodically() const override;`
- L35 _public prototype_ `bool SupportsMultipleTracksPerKind() const override;`
- L36 _public prototype_ `bool OrderOfTracksCanChangeDynamically() const override;`
- L37 _public prototype_ `EType GetPresentationType() const override;`
- L38 _public function_ `EReplayEventType GetReplayType() const override`
- L40 _public function_ `TSharedPtrTS<const FLowLatencyDescriptor> GetLowLatencyDescriptor() const override`
- L42 _public function_ `FTimeValue CalculateCurrentLiveLatency(const FTimeValue& InCurrentPlaybackPosition, const FTimeValue& InEncoderLatency, bool bViaLatencyElement) const override`
- L44 _public function_ `FTimeValue GetAnchorTime() const override`
- L46 _public function_ `FTimeRange GetTotalTimeRange() const override`
- L48 _public function_ `FTimeRange GetSeekableTimeRange() const override`
- L53 _public prototype_ `FTimeRange GetPlaybackRange(EPlaybackRangeType InRangeType) const override;`
- L54 _public function_ `FTimeValue GetDuration() const override`
- L56 _public function_ `FTimeValue GetDefaultStartTime() const override`
- L58 _public function_ `void ClearDefaultStartTime() override`
- L60 _public function_ `FTimeValue GetDefaultEndTime() const override`
- L62 _public function_ `void ClearDefaultEndTime() override`
- L64 _public prototype_ `void GetTrackMetadata(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override;`
- L65 _public prototype_ `void UpdateRunningMetaData(TSharedPtrTS<FMetadataParser> InUpdatedMetaData) override;`
- L66 _public prototype_ `FTimeValue GetMinBufferTime() const override;`
- L67 _public function_ `FTimeValue GetDesiredLiveLatency() const override`
- L69 _public function_ `ELiveEdgePlayMode GetLiveEdgePlayMode() const override`
- L71 _public prototype_ `TRangeSet<double> GetPossiblePlaybackRates(EPlayRateType InForType) const override;`
- L72 _public prototype_ `TSharedPtrTS<IProducerReferenceTimeInfo> GetProducerReferenceTimeInfo(int64 ID) const override;`
- L73 _public prototype_ `void UpdateDynamicRefetchCounter() override;`
- L74 _public function_ `void PrepareForLooping(int32 InNumLoopsToAdd) override`
- L76 _public prototype_ `void TriggerClockSync(EClockSyncType InClockSyncType) override;`
- L77 _public prototype_ `void TriggerPlaylistRefresh() override;`
- L78 _public function_ `void ReachedStableBuffer() override`
- L81 _public prototype_ `IStreamReader* CreateStreamReaderHandler() override;`
- L82 _public prototype_ `FResult FindPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L83 _public prototype_ `FResult FindNextPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, TSharedPtrTS<const IStreamSegment> CurrentSegment) override;`
- L323 _public prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L325 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents() const`
- L330 _public function_ `void SetURLFragmentComponents(TArray<FURL_RFC3986::FQueryParam> InURLFragmentComponents)`
- L335 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents()`
- L341 _public member_ `IPlayerSessionServices* PlayerSessionServices;`
- L342 _public member_ `TSharedPtrTS<FTimelineAssetMP4> MediaAsset;`
- L344 _public member_ `TArray<FURL_RFC3986::FQueryParam> URLFragmentComponents;` — The MPD URL fragment components
- L345 _public member_ `FTimeValue DefaultStartTime;`
- L346 _public member_ `FTimeValue DefaultEndTime;`

#### class `Electra::FManifestMP4Internal::FRepresentationMP4`  
`class FRepresentationMP4 : public IPlaybackAssetRepresentation`  
_L86-114_
- inherits: `IPlaybackAssetRepresentation`
- L89 _public prototype_ `virtual ~FRepresentationMP4() = default;`
- L91 _public prototype_ `FErrorDetail CreateFrom(const IParserISO14496_12::ITrack* InTrack, const FString& URL);`
- L93 _public function_ `FString GetUniqueIdentifier() const override`
- L95 _public function_ `const FStreamCodecInformation& GetCodecInformation() const override`
- L97 _public function_ `int32 GetBitrate() const override`
- L99 _public function_ `int32 GetQualityIndex() const override`
- L101 _public function_ `bool CanBePlayed() const override`
- L104 _public function_ `const FString& GetName() const`
- L107 _private member_ `FStreamCodecInformation CodecInformation;`
- L108 _private member_ `FString UniqueIdentifier;`
- L109 _private member_ `FString Name;`
- L110 _private member_ `int32 Bitrate;`
- L112 _private member_ `TArray<uint8> CodecSpecificData;`
- L113 _private member_ `TArray<uint8> CodecSpecificDataRAW;`

#### class `Electra::FManifestMP4Internal::FAdaptationSetMP4`  
`class FAdaptationSetMP4 : public IPlaybackAssetAdaptationSet`  
_L116-142_
- inherits: `IPlaybackAssetAdaptationSet`
- L119 _public prototype_ `virtual ~FAdaptationSetMP4() = default;`
- L121 _public prototype_ `FErrorDetail CreateFrom(const IParserISO14496_12::ITrack* InTrack, const FString& URL);`
- L123 _public function_ `FString GetUniqueIdentifier() const override`
- L125 _public function_ `FString GetListOfCodecs() const override`
- L127 _public function_ `const BCP47::FLanguageTag& GetLanguageTag() const override`
- L129 _public function_ `int32 GetNumberOfRepresentations() const override`
- L131 _public function_ `bool IsLowLatencyEnabled() const override`
- L133 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByIndex(int32 RepresentationIndex) const override`
- L135 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByUniqueIdentifier(const FString& InUniqueIdentifier) const override`
- L138 _private member_ `TSharedPtrTS<FRepresentationMP4> Representation;`
- L139 _private member_ `BCP47::FLanguageTag LanguageTag;`
- L140 _private member_ `FString CodecRFC6381;`
- L141 _private member_ `FString UniqueIdentifier;`

#### class `Electra::FManifestMP4Internal::FTimelineAssetMP4`  
`class FTimelineAssetMP4 : public ITimelineMediaAsset, public TSharedFromThis<FTimelineAssetMP4, ESPMode::ThreadSafe>`  
_L144-278_
- inherits: `ITimelineMediaAsset,TSharedFromThis<FTimelineAssetMP4,ESPMode::ThreadSafe>`
- L147 _public function_ `FTimelineAssetMP4() : PlayerSessionServices(nullptr)`
- L151 _public prototype_ `virtual ~FTimelineAssetMP4() = default;`
- L153 _public prototype_ `FErrorDetail Build(IPlayerSessionServices* InPlayerSessionServices, TSharedPtrTS<IParserISO14496_12> MP4Parser, const FString& URL);`
- L155 _public function_ `virtual FTimeRange GetTimeRange() const override`
- L163 _public function_ `virtual FTimeValue GetDuration() const override`
- L168 _public function_ `virtual FString GetAssetIdentifier() const override`
- L170 _public function_ `virtual FString GetUniqueIdentifier() const override`
- L172 _public function_ `virtual int32 GetNumberOfAdaptationSets(EStreamType OfStreamType) const override`
- L186 _public function_ `virtual TSharedPtrTS<IPlaybackAssetAdaptationSet> GetAdaptationSetByTypeAndIndex(EStreamType OfStreamType, int32 AdaptationSetIndex) const override`
- L200 _public function_ `virtual void GetMetaData(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override`
- L235 _public function_ `void UpdateRunningMetaData(const FString& InKindOfValue, const FVariant& InNewValue) override`
- L238 _public prototype_ `FResult GetStartingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType, int64 AtAbsoluteFilePos);`
- L239 _public prototype_ `FResult GetNextSegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options);`
- L240 _public prototype_ `FResult GetRetrySegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options, bool bReplaceWithFillerData);`
- L241 _public prototype_ `FResult GetLoopingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType);`
- L243 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID);`
- L244 _public prototype_ `TSharedPtrTS<IParserISO14496_12> GetMoovBoxParser();`
- L245 _public function_ `const FString& GetMediaURL() const`
- L264 _private prototype_ `void UpdatePlayRangeEndInfo(const FTimeValue& PlayRangeEndTime);`
- L265 _private prototype_ `void LimitSegmentDownloadSize(TSharedPtrTS<IStreamSegment>& InOutSegment);`
- L266 _private prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L267 _private member_ `IPlayerSessionServices* PlayerSessionServices;`
- L268 _private member_ `FString MediaURL;`
- L269 _private member_ `FTimeValue LongestTrackDuration;`
- L270 _private member_ `TSharedPtrTS<IParserISO14496_12> MoovBoxParser;`
- L271 _private member_ `TArray<TSharedPtrTS<FAdaptationSetMP4>> VideoAdaptationSets;`
- L272 _private member_ `TArray<TSharedPtrTS<FAdaptationSetMP4>> AudioAdaptationSets;`
- L273 _private member_ `TArray<TSharedPtrTS<FAdaptationSetMP4>> SubtitleAdaptationSets;`
- L274 _private member_ `FPlayRangeEndInfo PlayRangeEndInfo;`
- L276 _private member_ `TSharedPtrTS<FMetadataParser> MediaMetadata;` — Metadata from the 'meta' box, if any.
- L277 _private member_ `TSharedPtrTS<ElectraCDM::IMediaCDMClient> DrmClient;`

#### struct `Electra::FManifestMP4Internal::FTimelineAssetMP4::FPlayRangeEndInfo`  
`struct FPlayRangeEndInfo`  
_L251-262_
- L253 _public function_ `void Clear()`
- L259 _public member_ `FTimeValue Time;`
- L260 _public member_ `TArray<int64> FileOffsetsPerTrackID;`
- L261 _public member_ `int64 TotalFileEndOffset = -1;`

#### class `Electra::FManifestMP4Internal::FPlayPeriodMP4`  
`class FPlayPeriodMP4 : public IManifest::IPlayPeriod`  
_L281-321_
- inherits: `IManifest::IPlayPeriod`
- L284 _public prototype_ `FPlayPeriodMP4(TSharedPtrTS<FTimelineAssetMP4> InMediaAsset);`
- L285 _public prototype_ `virtual ~FPlayPeriodMP4();`
- L286 _public prototype_ `void SetStreamPreferences(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) override;`
- L287 _public prototype_ `EReadyState GetReadyState() override;`
- L288 _public prototype_ `void Load() override;`
- L289 _public prototype_ `void PrepareForPlay() override;`
- L290 _public prototype_ `int64 GetDefaultStartingBitrate() const override;`
- L291 _public prototype_ `TSharedPtrTS<FBufferSourceInfo> GetSelectedStreamBufferSourceInfo(EStreamType StreamType) override;`
- L292 _public prototype_ `FString GetSelectedAdaptationSetID(EStreamType StreamType) override;`
- L293 _public prototype_ `ETrackChangeResult ChangeTrackStreamPreference(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) override;`
- L294 _public prototype_ `TSharedPtrTS<ITimelineMediaAsset> GetMediaAsset() const override;`
- L295 _public prototype_ `void SelectStream(const FString& AdaptationSetID, const FString& RepresentationID, int32 QualityIndex, int32 MaxQualityIndex) override;`
- L296 _public prototype_ `void TriggerInitSegmentPreload(const TArray<FInitSegmentPreload>& InitSegmentsToPreload) override;`
- L297 _public prototype_ `FResult GetStartingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L298 _public prototype_ `FResult GetContinuationSegment(TSharedPtrTS<IStreamSegment>& OutSegment, EStreamType StreamType, const FPlayerSequenceState& LoopState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L299 _public prototype_ `FResult GetNextSegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options) override;`
- L300 _public prototype_ `FResult GetRetrySegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options, bool bReplaceWithFillerData) override;`
- L301 _public prototype_ `FResult GetLoopingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L302 _public prototype_ `void IncreaseSegmentFetchDelay(const FTimeValue& IncreaseAmount) override;`
- L303 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID) override;`
- L306 _private prototype_ `void SelectInitialStream(EStreamType StreamType);`
- L307 _private prototype_ `TSharedPtrTS<FTrackMetadata> SelectMetadataForAttributes(EStreamType StreamType, const FStreamSelectionAttributes& InAttributes);`
- L308 _private prototype_ `void MakeBufferSourceInfoFromMetadata(EStreamType StreamType, TSharedPtrTS<FBufferSourceInfo>& OutBufferSourceInfo, TSharedPtrTS<FTrackMetadata> InMetadata);`
- L310 _private member_ `TWeakPtrTS<FTimelineAssetMP4> MediaAsset;`
- L311 _private member_ `FStreamSelectionAttributes VideoPreferences;`
- L312 _private member_ `FStreamSelectionAttributes AudioPreferences;`
- L313 _private member_ `FStreamSelectionAttributes SubtitlePreferences;`
- L314 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedVideoMetadata;`
- L315 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedAudioMetadata;`
- L316 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedSubtitleMetadata;`
- L317 _private member_ `TSharedPtrTS<FBufferSourceInfo> VideoBufferSourceInfo;`
- L318 _private member_ `TSharedPtrTS<FBufferSourceInfo> AudioBufferSourceInfo;`
- L319 _private member_ `TSharedPtrTS<FBufferSourceInfo> SubtitleBufferSourceInfo;`
- L320 _private member_ `EReadyState CurrentReadyState;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mp4/OptionKeynamesMP4.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L9 _namespace_ `namespace MP4` (scope `Electra`)
- L12 _variable_ `const FName OptionKeyMP4LoadConnectTimeout(TEXT("mp4_` (scope `Electra::MP4`) — (FTimeValue) value specifying connection timeout fetching the MP4
- L13 _variable_ `const FName OptionKeyMP4LoadNoDataTimeout(TEXT("mp4_` (scope `Electra::MP4`) — (FTimeValue) value specifying no-data timeout fetching the MP4

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mp4/PlaylistReaderMP4.h` (Private)


#### class `Electra::IPlaylistReaderMP4`  
`class IPlaylistReaderMP4 : public IPlaylistReader`  
_L13-19_
- inherits: `IPlaylistReader`
- L16 _public prototype_ `static TSharedPtrTS<IPlaylistReader> Create(IPlayerSessionServices* PlayerSessionServices);`
- L18 _public prototype_ `virtual ~IPlaylistReaderMP4() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mp4/StreamReaderMP4.h` (Private)


#### class `Electra::FStreamSegmentRequestMP4`  
`class FStreamSegmentRequestMP4 : public IStreamSegment`  
_L26-88_
- inherits: `IStreamSegment`
- L29 _public prototype_ `FStreamSegmentRequestMP4();`
- L30 _public prototype_ `virtual ~FStreamSegmentRequestMP4();`
- L32 _public prototype_ `void SetPlaybackSequenceID(uint32 InPlaybackSequenceID) override;`
- L33 _public prototype_ `uint32 GetPlaybackSequenceID() const override;`
- L35 _public prototype_ `void SetExecutionDelay(const FTimeValue& UTCNow, const FTimeValue& ExecutionDelay) override;`
- L36 _public prototype_ `FTimeValue GetExecuteAtUTCTime() const override;`
- L38 _public prototype_ `EStreamType GetType() const override;`
- L40 _public prototype_ `void GetDependentStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutDependentStreams) const override;`
- L41 _public prototype_ `void GetRequestedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutRequestedStreams) override;`
- L42 _public prototype_ `void GetEndedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutAlreadyEndedStreams) override;`
- L44 _public prototype_ `FTimeValue GetFirstPTS() const override;`
- L45 _public prototype_ `FTimeRange GetTimeRange() const override;`
- L47 _public prototype_ `int32 GetQualityIndex() const override;`
- L48 _public prototype_ `int32 GetBitrate() const override;`
- L50 _public prototype_ `void GetDownloadStats(Metrics::FSegmentDownloadStats& OutStats) const override;`
- L51 _public function_ `bool GetStartupDelay(FTimeValue& OutStartTime, FTimeValue& OutTimeIntoSegment, FTimeValue& OutSegmentDuration) const override`
- L56 _public member_ `TSharedPtrTS<ITimelineMediaAsset> MediaAsset;` — The entire mp4 asset
- L57 _public member_ `TSharedPtrTS<IParserISO14496_12::ITrackIterator> PrimaryTrackIterator;`
- L58 _public member_ `TArray<EStreamType> DependentStreamTypes;`
- L60 _public member_ `FTimeValue FirstPTS;` — The PTS of the first sample
- L61 _public member_ `FTimeValue SegmentDuration;`
- L63 _public member_ `FTimeValue EarliestPTS;` — PTS of the first sample to be presented.
- L64 _public member_ `FTimeValue LastPTS;` — PTS at which no further samples are to be presented.
- L66 _public member_ `EStreamType PrimaryStreamType;`
- L67 _public member_ `int64 FileStartOffset;` — Where to start in the file
- L68 _public member_ `int64 FileEndOffset;` — Where to end in the file (for HTTP range GET requests)
- L69 _public member_ `int64 SegmentInternalSize;` — Size of the segment as defined by internal structures.
- L70 _public member_ `uint32 PlaybackSequenceID;`
- L71 _public member_ `int32 Bitrate;`
- L72 _public member_ `bool bStartingOnMOOF;` — when using the 'sidx' a segment is expected to start on a 'moof', otherwise inside an 'mdat'.
- L73 _public member_ `bool bIsFirstSegment;` — true if this segment is the first to start with or the first after a seek.
- L74 _public member_ `bool bIsLastSegment;` — true if this segment is the last.
- L76 _public member_ `bool bAllTracksAtEOS;`
- L78 _public member_ `int64 TimestampSequenceIndex;` — Sequence index to set in all timestamp values of the decoded access unit.
- L79 _public member_ `int32 NumOverallRetries;` — Number of retries
- L81 _public member_ `Metrics::FSegmentDownloadStats DownloadStats;`
- L82 _public member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L83 _public member_ `int64 CurrentIteratorBytePos;`
- L86 _public member_ `TSharedPtrTS<ElectraCDM::IMediaCDMClient> DrmClient;` — Encryption
- L87 _public member_ `FString DrmMimeType;`

#### class `Electra::FStreamReaderMP4`  
`class FStreamReaderMP4 : public IStreamReader, public FMediaThread`  
_L94-193_
- inherits: `IStreamReader,FMediaThread`
- desc: This class implements an interface to read from an mp4 file.
- L97 _public prototype_ `FStreamReaderMP4();`
- L98 _public prototype_ `virtual ~FStreamReaderMP4();`
- L99 _public prototype_ `UEMediaError Create(IPlayerSessionServices* PlayerSessionService, const CreateParam &createParam) override;`
- L100 _public prototype_ `bool LoadsMultiplexedTracksSequentially() override;`
- L101 _public prototype_ `void Close() override;`
- L102 _public prototype_ `EAddResult AddRequest(uint32 CurrentPlaybackSequenceID, TSharedPtrTS<IStreamSegment> Request) override;`
- L103 _public prototype_ `void CancelRequest(EStreamType StreamType, bool bSilent) override;`
- L104 _public prototype_ `void CancelRequests() override;`
- L107 _private prototype_ `void WorkerThread();`
- L108 _private prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L109 _private prototype_ `int32 HTTPProgressCallback(const IElectraHttpManager::FRequest* InRequest);`
- L110 _private prototype_ `void HTTPCompletionCallback(const IElectraHttpManager::FRequest* InRequest);`
- L111 _private prototype_ `void HandleRequest();`
- L113 _private prototype_ `bool HasBeenAborted() const;`
- L114 _private prototype_ `bool HasErrored() const;`
- L178 _private member_ `CreateParam Parameters;`
- L179 _private member_ `IPlayerSessionServices* PlayerSessionServices;`
- L180 _private member_ `bool bIsStarted;`
- L181 _private member_ `bool bTerminate;`
- L182 _private member_ `bool bRequestCanceled;`
- L183 _private member_ `bool bHasErrored;`
- L184 _private member_ `FErrorDetail ErrorDetail;`
- L186 _private member_ `TSharedPtrTS<FStreamSegmentRequestMP4> CurrentRequest;`
- L187 _private member_ `FMediaEvent WorkSignal;`
- L188 _private member_ `FReadBuffer ReadBuffer;`
- L190 _private member_ `TMap<uint32, FSelectedTrackData> ActiveTrackMap;`
- L192 _private member_ `static uint32 UniqueDownloadID;`

#### struct `Electra::FStreamReaderMP4::FReadBuffer`  
`struct FReadBuffer`  
_L116-157_
- L118 _public function_ `FReadBuffer()`
- L122 _public function_ `void Reset()`
- L130 _public function_ `void SetCurrentPos(int64 InPos)`
- L134 _public function_ `int64 GetCurrentPos()`
- L138 _public function_ `void Abort()`
- L147 _public function_ `void SetHasErrored()`
- L151 _public prototype_ `int32 ReadTo(void* ToBuffer, int64 NumBytes);`
- L152 _public member_ `TSharedPtrTS<FWaitableBuffer> ReceiveBuffer;`
- L153 _public member_ `int64 CurrentPos;`
- L154 _public member_ `int64 ParsePos;`
- L155 _public member_ `bool bAbort;`
- L156 _public member_ `bool bHasErrored;`

#### struct `Electra::FStreamReaderMP4::FSelectedTrackData`  
`struct FSelectedTrackData`  
_L159-176_
- L161 _public function_ `FSelectedTrackData() : StreamType(EStreamType::Video), Bitrate(0), bIsSelectedTrack(false), bIsFirstInSequence(true), bReadPastLastPTS(false)`
- L167 _public member_ `TSharedPtrTS<FAccessUnit::CodecData> CSD;`
- L168 _public member_ `TSharedPtrTS<FBufferSourceInfo> BufferSourceInfo;`
- L169 _public member_ `EStreamType StreamType;`
- L170 _public member_ `int32 Bitrate;`
- L171 _public member_ `bool bIsSelectedTrack;`
- L172 _public member_ `bool bIsFirstInSequence;`
- L173 _public member_ `bool bReadPastLastPTS;`
- L174 _public member_ `FTimeValue DurationSuccessfullyRead;`
- L175 _public member_ `FTimeValue DurationSuccessfullyDelivered;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mpegaudio/ManifestMPEGAudio.h` (Private)


#### struct `Electra::FMPEGAudioInfoHeader`  
`struct FMPEGAudioInfoHeader`  
_L21-69_
- L29 _public member_ `TSharedPtrTS<MPEG::FID3V2Metadata> ID3v2;`
- L30 _public member_ `EType Type = EType::Unknown;`
- L31 _public member_ `uint32 MPEGHeaderMask = 0;`
- L32 _public member_ `uint32 MPEGHeaderExpectedValue = 0;`
- L33 _public member_ `int32 MPEGVersion = 0;`
- L34 _public member_ `int32 MPEGLayer = 0;`
- L35 _public member_ `int32 SampleRate = 0;`
- L36 _public member_ `int32 NumChannels = 0;`
- L37 _public member_ `bool bIsVBR = false;`
- L38 _public member_ `int32 Bitrate = 0;`
- L39 _public member_ `int32 AverageBitrate = 0;`
- L40 _public member_ `int32 CBRFrameSize = 0;`
- L41 _public member_ `int32 SamplesPerFrame = 0;`
- L42 _public member_ `uint32 NumFrames = 0;`
- L43 _public member_ `int32 EncoderDelayStart = 0;`
- L44 _public member_ `int32 EncoderDelayEnd = 0;`
- L45 _public member_ `int64 FirstDataByte = -1;`
- L46 _public member_ `int64 LastDataByte = -1;`
- L47 _public member_ `bool bIsLive = false;`
- L48 _public member_ `bool bHaveTOC = false;`
- L49 _public member_ `TArray<uint8> TOC;`
- L50 _public member_ `int32 FramesPerSeekTableEntry = 0;`
- L51 _public member_ `TSharedPtrTS<TArray<uint32>> SeekTable;`
- L62 _public member_ `TSharedPtrTS<FMLLT> MLLT;`
- L64 _public member_ `FStreamCodecInformation CodecInfo;` — Generated codec info from above values.
- L66 _public member_ `FTimeValue EstimatedDuration;` — Estimated duration
- L68 _public member_ `TMultiMap<FString, FString> HTTPResponseHeaders;` — HTTP response headers

#### enum `Electra::FMPEGAudioInfoHeader::EType`  
`enum class EType`  
_L23-28_
- L25 _public enumerator_ `Unknown`
- L26 _public enumerator_ `ISO_11172_3` — MPEG1/2 layer 1,2 and 3
- L27 _public enumerator_ `ISO_14496_3` — AAC

#### struct `Electra::FMPEGAudioInfoHeader::FMLLT`  
`struct FMLLT`  
_L52-61_
- L59 _public member_ `uint32 FramesBetweenReferences = 0;`
- L60 _public member_ `TArray<FTimeAndOffset> TimeAndOffsets;`

#### struct `Electra::FMPEGAudioInfoHeader::FMLLT::FTimeAndOffset`  
`struct FTimeAndOffset`  
_L54-58_
- L56 _public member_ `uint32 Offset = 0;`
- L57 _public member_ `uint32 Milliseconds = 0;`

#### class `Electra::FManifestMPEGAudioInternal`  
`class FManifestMPEGAudioInternal : public IManifest, public TSharedFromThis<FManifestMPEGAudioInternal, ESPMode::ThreadSafe>`  
_L74-361_
- inherits: `IManifest,TSharedFromThis<FManifestMPEGAudioInternal,ESPMode::ThreadSafe>`
- desc: This class represents the internal "manifest" or "playlist" of an MPEG audio file.
- L77 _public prototype_ `FManifestMPEGAudioInternal(IPlayerSessionServices* InPlayerSessionServices);`
- L78 _public prototype_ `virtual ~FManifestMPEGAudioInternal();`
- L80 _public prototype_ `FErrorDetail Build(const FMPEGAudioInfoHeader& InHeader, const FString& URL);`
- L82 _public prototype_ `EMediaFormatType GetMediaFormatType() const override;`
- L83 _public prototype_ `bool ReloadsPlaylistPeriodically() const override;`
- L84 _public prototype_ `bool SupportsMultipleTracksPerKind() const override;`
- L85 _public prototype_ `bool OrderOfTracksCanChangeDynamically() const override;`
- L86 _public prototype_ `EType GetPresentationType() const override;`
- L87 _public function_ `EReplayEventType GetReplayType() const override`
- L89 _public prototype_ `TSharedPtrTS<const FLowLatencyDescriptor> GetLowLatencyDescriptor() const override;`
- L90 _public prototype_ `FTimeValue CalculateCurrentLiveLatency(const FTimeValue& InCurrentPlaybackPosition, const FTimeValue& InEncoderLatency, bool bViaLatencyElement) const override;`
- L91 _public function_ `FTimeValue GetAnchorTime() const override`
- L93 _public function_ `FTimeRange GetTotalTimeRange() const override`
- L95 _public function_ `FTimeRange GetSeekableTimeRange() const override`
- L97 _public prototype_ `FTimeRange GetPlaybackRange(EPlaybackRangeType InRangeType) const override;`
- L98 _public function_ `FTimeValue GetDuration() const override`
- L100 _public function_ `FTimeValue GetDefaultStartTime() const override`
- L102 _public function_ `void ClearDefaultStartTime() override`
- L104 _public function_ `FTimeValue GetDefaultEndTime() const override`
- L106 _public function_ `void ClearDefaultEndTime() override`
- L108 _public prototype_ `void GetTrackMetadata(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override;`
- L109 _public prototype_ `void UpdateRunningMetaData(TSharedPtrTS<FMetadataParser> InUpdatedMetaData) override;`
- L110 _public prototype_ `FTimeValue GetMinBufferTime() const override;`
- L111 _public prototype_ `FTimeValue GetDesiredLiveLatency() const override;`
- L112 _public prototype_ `ELiveEdgePlayMode GetLiveEdgePlayMode() const override;`
- L114 _public prototype_ `TRangeSet<double> GetPossiblePlaybackRates(EPlayRateType InForType) const override;`
- L115 _public prototype_ `TSharedPtrTS<IProducerReferenceTimeInfo> GetProducerReferenceTimeInfo(int64 ID) const override;`
- L116 _public prototype_ `void UpdateDynamicRefetchCounter() override;`
- L117 _public function_ `void PrepareForLooping(int32 InNumLoopsToAdd) override`
- L119 _public prototype_ `void TriggerClockSync(EClockSyncType InClockSyncType) override;`
- L120 _public prototype_ `void TriggerPlaylistRefresh() override;`
- L121 _public function_ `void ReachedStableBuffer() override`
- L124 _public prototype_ `IStreamReader* CreateStreamReaderHandler() override;`
- L125 _public prototype_ `FResult FindPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L126 _public prototype_ `FResult FindNextPlayPeriod(TSharedPtrTS<IPlayPeriod>& OutPlayPeriod, TSharedPtrTS<const IStreamSegment> CurrentSegment) override;`
- L337 _public prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L339 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents() const`
- L344 _public function_ `void SetURLFragmentComponents(TArray<FURL_RFC3986::FQueryParam> InURLFragmentComponents)`
- L349 _public function_ `const TArray<FURL_RFC3986::FQueryParam>& GetURLFragmentComponents()`
- L354 _public member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L355 _public member_ `TSharedPtrTS<FTimelineAssetMPEGAudio> MediaAsset;`
- L356 _public member_ `TArray<FURL_RFC3986::FQueryParam> URLFragmentComponents;`
- L357 _public member_ `FTimeValue DefaultStartTime;`
- L358 _public member_ `FTimeValue DefaultEndTime;`
- L359 _public member_ `FMPEGAudioInfoHeader MPEGInfoHeader;`
- L360 _public member_ `TSharedPtrTS<FLowLatencyDescriptor> LatencyDescriptor;`

#### class `Electra::FManifestMPEGAudioInternal::FRepresentationMPEGAudio`  
`class FRepresentationMPEGAudio : public IPlaybackAssetRepresentation`  
_L128-159_
- inherits: `IPlaybackAssetRepresentation`
- L131 _public prototype_ `virtual ~FRepresentationMPEGAudio() = default;`
- L133 _public prototype_ `FErrorDetail CreateFrom(const FMPEGAudioInfoHeader& InHeader, const FString& URL);`
- L135 _public function_ `FString GetUniqueIdentifier() const override`
- L137 _public function_ `const FStreamCodecInformation& GetCodecInformation() const override`
- L139 _public function_ `int32 GetBitrate() const override`
- L141 _public function_ `int32 GetQualityIndex() const override`
- L143 _public function_ `bool CanBePlayed() const override`
- L145 _public function_ `const FString& GetName() const`
- L147 _public function_ `void SetName(const FString& InNewName)`
- L149 _public function_ `const FString& GetLanguage() const`
- L151 _public function_ `void SetLanguage(const FString& InNewName)`
- L154 _private member_ `FStreamCodecInformation CodecInformation;`
- L155 _private member_ `FString UniqueIdentifier;`
- L156 _private member_ `FString Name;`
- L157 _private member_ `FString Language639_2;`
- L158 _private member_ `int32 Bitrate = 0;`

#### class `Electra::FManifestMPEGAudioInternal::FAdaptationSetMPEGAudio`  
`class FAdaptationSetMPEGAudio : public IPlaybackAssetAdaptationSet`  
_L161-187_
- inherits: `IPlaybackAssetAdaptationSet`
- L164 _public prototype_ `virtual ~FAdaptationSetMPEGAudio() = default;`
- L166 _public prototype_ `FErrorDetail CreateFrom(const FMPEGAudioInfoHeader& InHeader, const FString& URL);`
- L168 _public function_ `FString GetUniqueIdentifier() const override`
- L170 _public function_ `FString GetListOfCodecs() const override`
- L172 _public function_ `const BCP47::FLanguageTag& GetLanguageTag() const override`
- L174 _public function_ `int32 GetNumberOfRepresentations() const override`
- L176 _public prototype_ `bool IsLowLatencyEnabled() const override;`
- L177 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByIndex(int32 RepresentationIndex) const override`
- L179 _public function_ `TSharedPtrTS<IPlaybackAssetRepresentation> GetRepresentationByUniqueIdentifier(const FString& InUniqueIdentifier) const override`
- L182 _private member_ `TSharedPtrTS<FRepresentationMPEGAudio> Representation;`
- L183 _private member_ `BCP47::FLanguageTag LanguageTag;`
- L184 _private member_ `FString CodecRFC6381;`
- L185 _private member_ `FString UniqueIdentifier;`
- L186 _private member_ `bool bIsLivecast = false;`

#### class `Electra::FManifestMPEGAudioInternal::FTimelineAssetMPEGAudio`  
`class FTimelineAssetMPEGAudio : public ITimelineMediaAsset, public TSharedFromThis<FTimelineAssetMPEGAudio, ESPMode::ThreadSafe>`  
_L189-298_
- inherits: `ITimelineMediaAsset,TSharedFromThis<FTimelineAssetMPEGAudio,ESPMode::ThreadSafe>`
- L192 _public function_ `FTimelineAssetMPEGAudio() : PlayerSessionServices(nullptr)`
- L196 _public prototype_ `virtual ~FTimelineAssetMPEGAudio() = default;`
- L198 _public prototype_ `FErrorDetail Build(IPlayerSessionServices* InPlayerSessionServices, const FMPEGAudioInfoHeader& InHeader, const FString& URL);`
- L200 _public function_ `FTimeRange GetTimeRange() const override`
- L208 _public function_ `FTimeValue GetDuration() const override`
- L213 _public function_ `FString GetAssetIdentifier() const override`
- L215 _public function_ `FString GetUniqueIdentifier() const override`
- L217 _public function_ `int32 GetNumberOfAdaptationSets(EStreamType OfStreamType) const override`
- L221 _public function_ `TSharedPtrTS<IPlaybackAssetAdaptationSet> GetAdaptationSetByTypeAndIndex(EStreamType OfStreamType, int32 AdaptationSetIndex) const override`
- L226 _public function_ `void GetMetaData(TArray<FTrackMetadata>& OutMetadata, EStreamType StreamType) const override`
- L259 _public function_ `void UpdateRunningMetaData(const FString& InKindOfValue, const FVariant& InNewValue) override`
- L283 _public prototype_ `FResult GetStartingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType, int64 AtAbsoluteFilePos);`
- L284 _public prototype_ `FResult GetNextSegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options);`
- L285 _public prototype_ `FResult GetRetrySegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options, bool bReplaceWithFillerData);`
- L286 _public prototype_ `FResult GetLoopingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType);`
- L288 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID);`
- L289 _public function_ `const FString& GetMediaURL() const`
- L293 _private prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L294 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L295 _private member_ `FString MediaURL;`
- L296 _private member_ `TArray<TSharedPtrTS<FAdaptationSetMPEGAudio>> AudioAdaptationSets;`
- L297 _private member_ `FMPEGAudioInfoHeader MPEGInfoHeader;`

#### class `Electra::FManifestMPEGAudioInternal::FPlayPeriodMPEGAudio`  
`class FPlayPeriodMPEGAudio : public IManifest::IPlayPeriod`  
_L301-335_
- inherits: `IManifest::IPlayPeriod`
- L304 _public prototype_ `FPlayPeriodMPEGAudio(TSharedPtrTS<FTimelineAssetMPEGAudio> InMediaAsset);`
- L305 _public prototype_ `virtual ~FPlayPeriodMPEGAudio();`
- L306 _public prototype_ `void SetStreamPreferences(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) override;`
- L307 _public prototype_ `EReadyState GetReadyState() override;`
- L308 _public prototype_ `void Load() override;`
- L309 _public prototype_ `void PrepareForPlay() override;`
- L310 _public prototype_ `int64 GetDefaultStartingBitrate() const override;`
- L311 _public prototype_ `TSharedPtrTS<FBufferSourceInfo> GetSelectedStreamBufferSourceInfo(EStreamType StreamType) override;`
- L312 _public prototype_ `FString GetSelectedAdaptationSetID(EStreamType StreamType) override;`
- L313 _public prototype_ `ETrackChangeResult ChangeTrackStreamPreference(EStreamType ForStreamType, const FStreamSelectionAttributes& StreamAttributes) override;`
- L314 _public prototype_ `TSharedPtrTS<ITimelineMediaAsset> GetMediaAsset() const override;`
- L315 _public prototype_ `void SelectStream(const FString& AdaptationSetID, const FString& RepresentationID, int32 QualityIndex, int32 MaxQualityIndex) override;`
- L316 _public prototype_ `void TriggerInitSegmentPreload(const TArray<FInitSegmentPreload>& InitSegmentsToPreload) override;`
- L317 _public prototype_ `FResult GetStartingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L318 _public prototype_ `FResult GetContinuationSegment(TSharedPtrTS<IStreamSegment>& OutSegment, EStreamType StreamType, const FPlayerSequenceState& LoopState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L319 _public prototype_ `FResult GetNextSegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options) override;`
- L320 _public prototype_ `FResult GetRetrySegment(TSharedPtrTS<IStreamSegment>& OutSegment, TSharedPtrTS<const IStreamSegment> CurrentSegment, const FPlayStartOptions& Options, bool bReplaceWithFillerData) override;`
- L321 _public prototype_ `FResult GetLoopingSegment(TSharedPtrTS<IStreamSegment>& OutSegment, const FPlayerSequenceState& InSequenceState, const FPlayStartPosition& StartPosition, ESearchType SearchType) override;`
- L322 _public prototype_ `void IncreaseSegmentFetchDelay(const FTimeValue& IncreaseAmount) override;`
- L323 _public prototype_ `void GetAverageSegmentDuration(FTimeValue& OutAverageSegmentDuration, const FString& AdaptationSetID, const FString& RepresentationID) override;`
- L326 _private prototype_ `void SelectInitialStream(EStreamType StreamType);`
- L327 _private prototype_ `TSharedPtrTS<FTrackMetadata> SelectMetadataForAttributes(EStreamType StreamType, const FStreamSelectionAttributes& InAttributes);`
- L328 _private prototype_ `void MakeBufferSourceInfoFromMetadata(EStreamType StreamType, TSharedPtrTS<FBufferSourceInfo>& OutBufferSourceInfo, TSharedPtrTS<FTrackMetadata> InMetadata);`
- L330 _private member_ `TWeakPtrTS<FTimelineAssetMPEGAudio> MediaAsset;`
- L331 _private member_ `FStreamSelectionAttributes AudioPreferences;`
- L332 _private member_ `TSharedPtrTS<FTrackMetadata> SelectedAudioMetadata;`
- L333 _private member_ `TSharedPtrTS<FBufferSourceInfo> AudioBufferSourceInfo;`
- L334 _private member_ `EReadyState CurrentReadyState;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mpegaudio/OptionKeynamesMPEGAudio.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L10 _namespace_ `namespace MPEGAudio` (scope `Electra`)
- L12 _variable_ `const FName OptionKeyMPEGAudioLoadConnectTimeout(TEXT("mpeg` (scope `Electra::MPEGAudio`)
- L13 _variable_ `const FName OptionKeyMPEGAudioLoadNoDataTimeout(TEXT("mpeg` (scope `Electra::MPEGAudio`)
- L14 _variable_ `const FName OptionKeyMPEGAudioLoadTimeout(TEXT("mpeg` (scope `Electra::MPEGAudio`)
- L15 _variable_ `const FName OptionKeyMPEGAudioMaxPreloadBufferDuration(TEXT("mpeg` (scope `Electra::MPEGAudio`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mpegaudio/PlaylistReaderMPEGAudio.h` (Private)


#### class `Electra::IPlaylistReaderMPEGAudio`  
`class IPlaylistReaderMPEGAudio : public IPlaylistReader`  
_L12-18_
- inherits: `IPlaylistReader`
- L15 _public prototype_ `static TSharedPtrTS<IPlaylistReader> Create(IPlayerSessionServices* PlayerSessionServices);`
- L17 _public prototype_ `virtual ~IPlaylistReaderMPEGAudio() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Player/mpegaudio/StreamReaderMPEGAudio.h` (Private)


#### class `Electra::FStreamSegmentRequestMPEGAudio`  
`class FStreamSegmentRequestMPEGAudio : public IStreamSegment`  
_L22-97_
- inherits: `IStreamSegment`
- L25 _public prototype_ `virtual ~FStreamSegmentRequestMPEGAudio() = default;`
- L27 _public function_ `void SetPlaybackSequenceID(uint32 InPlaybackSequenceID) override`
- L29 _public function_ `uint32 GetPlaybackSequenceID() const override`
- L31 _public function_ `void SetExecutionDelay(const FTimeValue& UTCNow, const FTimeValue& ExecutionDelay) override`
- L33 _public function_ `FTimeValue GetExecuteAtUTCTime() const override`
- L35 _public function_ `EStreamType GetType() const override`
- L37 _public function_ `void GetDependentStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutDependentStreams) const override`
- L39 _public prototype_ `void GetRequestedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutRequestedStreams) override;`
- L40 _public prototype_ `void GetEndedStreams(TArray<TSharedPtrTS<IStreamSegment>>& OutAlreadyEndedStreams) override;`
- L41 _public function_ `FTimeValue GetFirstPTS() const override`
- L47 _public prototype_ `FTimeRange GetTimeRange() const override;`
- L49 _public function_ `int32 GetQualityIndex() const override`
- L51 _public function_ `int32 GetBitrate() const override`
- L53 _public function_ `void GetDownloadStats(Metrics::FSegmentDownloadStats& OutStats) const override`
- L55 _public function_ `bool GetStartupDelay(FTimeValue& OutStartTime, FTimeValue& OutTimeIntoSegment, FTimeValue& OutSegmentDuration) const override`
- L59 _public member_ `TSharedPtrTS<ITimelineMediaAsset> MediaAsset;`
- L61 _public member_ `FTimeValue FirstPTS;`
- L62 _public member_ `FTimeValue EarliestPTS;` — PTS of the first sample to be presented.
- L63 _public member_ `FTimeValue LastPTS;` — PTS at which no further samples are to be presented.
- L64 _public member_ `int64 FileStartOffset = -1;` — Where to start in the file
- L65 _public member_ `int64 FileEndOffset = -1;` — Where to end in the file (for HTTP range GET requests)
- L71 _public member_ `ECastType CastType = ECastType::None;`
- L73 _public member_ `uint32 MPEGHeaderMask = 0;`
- L74 _public member_ `uint32 MPEGHeaderExpectedValue = 0;`
- L75 _public member_ `int32 CBRFrameSize = 0;`
- L76 _public member_ `bool bIsAAC = false;`
- L77 _public member_ `bool bIsVBR = false;`
- L78 _public member_ `bool bIsLive = false;`
- L79 _public member_ `bool bIsEOSRequest = false;`
- L80 _public member_ `double Duration = 0.0;`
- L81 _public member_ `FStreamCodecInformation CodecInfo;`
- L83 _public member_ `uint32 PlaybackSequenceID = ~0U;`
- L84 _public member_ `int32 Bitrate = 0;`
- L85 _public member_ `bool bIsContinuationSegment = false;` — true if this segment continues where the previous left off and no sync samples should be expected.
- L86 _public member_ `bool bIsFirstSegment = false;` — true if this segment is the first to start with or the first after a seek.
- L87 _public member_ `bool bIsLastSegment = false;` — true if this segment is the last.
- L89 _public member_ `int64 TimestampSequenceIndex = 0;` — Sequence index to set in all timestamp values of the decoded access unit.
- L90 _public member_ `int32 NumOverallRetries = 0;` — Number of retries
- L92 _public member_ `int64 LastSuccessfullyUsedBytePos = -1;`
- L93 _public member_ `FTimeValue LastSuccessfullyUsedPTS;`
- L95 _public member_ `Metrics::FSegmentDownloadStats DownloadStats;`
- L96 _public member_ `HTTP::FConnectionInfo ConnectionInfo;`

#### enum `Electra::FStreamSegmentRequestMPEGAudio::ECastType`  
`enum class ECastType`  
_L66-70_
- L68 _public enumerator_ `None`
- L69 _public enumerator_ `IcyCast`

#### class `Electra::FStreamReaderMPEGAudio`  
`class FStreamReaderMPEGAudio : public IStreamReader, public FMediaThread`  
_L100-137_
- inherits: `IStreamReader,FMediaThread`
- L103 _public prototype_ `FStreamReaderMPEGAudio();`
- L104 _public prototype_ `virtual ~FStreamReaderMPEGAudio();`
- L105 _public prototype_ `UEMediaError Create(IPlayerSessionServices* PlayerSessionService, const CreateParam &createParam) override;`
- L106 _public prototype_ `bool LoadsMultiplexedTracksSequentially() override;`
- L107 _public prototype_ `void Close() override;`
- L108 _public prototype_ `EAddResult AddRequest(uint32 CurrentPlaybackSequenceID, TSharedPtrTS<IStreamSegment> Request) override;`
- L109 _public prototype_ `void CancelRequest(EStreamType StreamType, bool bSilent) override;`
- L110 _public prototype_ `void CancelRequests() override;`
- L113 _private prototype_ `void WorkerThread();`
- L114 _private prototype_ `void LogMessage(IInfoLog::ELevel Level, const FString& Message);`
- L115 _private prototype_ `int32 HTTPProgressCallback(const IElectraHttpManager::FRequest* InRequest);`
- L116 _private prototype_ `void HTTPCompletionCallback(const IElectraHttpManager::FRequest* InRequest);`
- L117 _private prototype_ `void HandleRequest();`
- L119 _private prototype_ `bool HasBeenAborted() const;`
- L120 _private prototype_ `bool HasErrored() const;`
- L122 _private member_ `CreateParam Parameters;`
- L123 _private member_ `IPlayerSessionServices* PlayerSessionServices = nullptr;`
- L124 _private member_ `bool bIsStarted = false;`
- L125 _private member_ `bool bTerminate = false;`
- L126 _private member_ `bool bRequestCanceled = false;`
- L127 _private member_ `bool bHasErrored = false;`
- L128 _private member_ `FErrorDetail ErrorDetail;`
- L131 _private member_ `TSharedPtrTS<FLiveRequest> LiveRequest;`
- L132 _private member_ `TSharedPtrTS<FStreamSegmentRequestMPEGAudio> CurrentRequest;`
- L133 _private member_ `TSharedPtrTS<FWaitableBuffer> ReceiveBuffer;`
- L134 _private member_ `FMediaEvent WorkSignal;`
- L136 _private member_ `static uint32 UniqueDownloadID;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/PlayerClock.h` (Private)


#### class `Electra::IMediaRenderClock`  
`class IMediaRenderClock`  
_L10-42_
- L13 _public prototype_ `virtual ~IMediaRenderClock() = default;`
- L30 _public prototype_ `virtual void SetCurrentTime(ERendererType ForRenderer, const FTimeValue& CurrentRenderTime) = 0;` — Called by the renderer to set the time of the most sample that has been output most recently. @param ForRenderer Identifies the type of renderer from which the time is set. @param CurrentRenderTime The time of the sample most recently output.
- L41 _public prototype_ `virtual FTimeValue GetInterpolatedRenderTime(ERendererType FromRenderer) = 0;` — Gets the current _interpolated_ sample output time from the last time SetCurrentTime() was called plus the elapsed time since then. @param FromRenderer Identifies the type of renderer for which to get the time. @return Interpolated render time

#### enum `Electra::IMediaRenderClock::ERendererType`  
`enum class ERendererType`  
_L15-20_
- L17 _public enumerator_ `Video`
- L18 _public enumerator_ `Audio`
- L19 _public enumerator_ `Subtitles`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/PlayerCore.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/PlayerFacility.h` (Private)


#### enum `Electra::Facility::EFacility`  
`enum class EFacility`  
_L14-56_
- L16 _public enumerator_ `Unknown`
- L17 _public enumerator_ `Utility`
- L18 _public enumerator_ `Player`
- L19 _public enumerator_ `ABR`
- L20 _public enumerator_ `HTTPReader`
- L21 _public enumerator_ `BufferedDataReader`
- L22 _public enumerator_ `HLSPlaylistHandler`
- L23 _public enumerator_ `HLSParser`
- L24 _public enumerator_ `HLSPlaylistBuilder`
- L25 _public enumerator_ `MP4Parser`
- L26 _public enumerator_ `VideoRenderer`
- L27 _public enumerator_ `AudioRenderer`
- L28 _public enumerator_ `SubtitleRenderer`
- L29 _public enumerator_ `MP4PlaylistReader`
- L30 _public enumerator_ `MP4Playlist`
- L31 _public enumerator_ `MP4StreamReader`
- L32 _public enumerator_ `ISOBMFFPlaylistReader`
- L33 _public enumerator_ `ISOBMFFPlaylist`
- L34 _public enumerator_ `ISOBMFFStreamReader`
- L35 _public enumerator_ `MKVPlaylistReader`
- L36 _public enumerator_ `MKVPlaylist`
- L37 _public enumerator_ `MKVStreamReader`
- L38 _public enumerator_ `MKVParser`
- L39 _public enumerator_ `MPEGTSParser`
- L40 _public enumerator_ `LicenseKey`
- L41 _public enumerator_ `DASHMPDReader`
- L42 _public enumerator_ `DASHMPDParser`
- L43 _public enumerator_ `DASHMPDBuilder`
- L44 _public enumerator_ `DASHManifest`
- L45 _public enumerator_ `DASHStreamReader`
- L46 _public enumerator_ `MPEGAudioPlaylistReader`
- L47 _public enumerator_ `MPEGAudioPlaylist`
- L48 _public enumerator_ `MPEGAudioStreamReader`
- L49 _public enumerator_ `CommonSegmentReader`
- L50 _public enumerator_ `EntityCache`
- L51 _public enumerator_ `DRM`
- L52 _public enumerator_ `SubtitleDecoder`
- L53 _public enumerator_ `AudioDecoder`
- L54 _public enumerator_ `VideoDecoder`
- L55 _public enumerator_ `LastEntry = 255`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L11 _namespace_ `namespace Facility` (scope `Electra`)
- L58 _function_ `static const TCHAR* GetName(EFacility InFacility)` (scope `Electra::Facility`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/PlayerPlatform.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L10 _namespace_ `namespace Platform` (scope `Electra`)
- L12 _prototype_ `FString GetPlatformID();` (scope `Electra::Platform`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/PlayerRuntimeGlobal.h` (Private)


#### struct `Electra::Configuration`  
`struct Configuration`  
_L10-13_
- L12 _public member_ `TMap<FString, bool> EnabledAnalyticsEvents;`

#### struct `Electra::FApplicationTerminationHandler`  
`struct FApplicationTerminationHandler`  
_L36-39_
- desc: Application termination
- L38 _public member_ `TFunction<void()> Terminate;`

#### struct `Electra::FFGBGNotificationHandlers`  
`struct FFGBGNotificationHandlers`  
_L44-48_
- desc: Background / foreground handling
- L46 _public member_ `TFunction<void()> WillEnterBackground;`
- L47 _public member_ `TFunction<void()> HasEnteredForeground;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L16 _prototype_ `bool Startup(const Configuration& Configuration);` (scope `Electra`) — Initializes core service functionality. Memory hooks must have been registered before calling this function.
- L19 _prototype_ `void Shutdown();` (scope `Electra`) — Shuts down core services.
- L22 _prototype_ `bool WaitForAllPlayersToHaveTerminated();` (scope `Electra`) — Waits until all player instances have terminated, which may happen asynchronously.
- L25 _prototype_ `void AddActivePlayerInstance();` (scope `Electra`)
- L26 _prototype_ `void RemoveActivePlayerInstance();` (scope `Electra`)
- L29 _prototype_ `bool IsAnalyticsEventEnabled(const FString& AnalyticsEventName);` (scope `Electra`) — Check if an analytics event is enabled
- L33 _prototype_ `bool MustSuspendDecodersInBackground(bool bInDecoderPreference);` (scope `Electra`) — Returns if all decoders must be suspended when the application goes into background mode, either because of platform requirements or because of ini settings.
- L40 _prototype_ `void AddTerminationNotificationHandler(TSharedPtrTS<FApplicationTerminationHandler> InHandler);` (scope `Electra`)
- L41 _prototype_ `void RemoveTerminationNotificationHandler(TSharedPtrTS<FApplicationTerminationHandler> InHandler);` (scope `Electra`)
- L49 _prototype_ `bool AddBGFGNotificationHandler(TSharedPtrTS<FFGBGNotificationHandlers> InHandlers);` (scope `Electra`)
- L50 _prototype_ `void RemoveBGFGNotificationHandler(TSharedPtrTS<FFGBGNotificationHandlers> InHandlers);` (scope `Electra`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/StreamAccessUnitBuffer.h` (Private)


#### class `Electra::IAccessUnitMemoryProvider`  
`class IAccessUnitMemoryProvider`  
_L22-35_
- L31 _public prototype_ `virtual ~IAccessUnitMemoryProvider() = default;`
- L33 _public prototype_ `virtual void* AUAllocate(EDataType type, SIZE_T size, SIZE_T alignment = 0) = 0;`
- L34 _public prototype_ `virtual void AUDeallocate(EDataType type, void* pAddr) = 0;`

#### enum `Electra::IAccessUnitMemoryProvider::EDataType`  
`enum class EDataType`  
_L25-30_
- L27 _public enumerator_ `AU`
- L28 _public enumerator_ `Payload`
- L29 _public enumerator_ `GenericData`

#### struct `Electra::FBufferSourceInfo`  
`struct FBufferSourceInfo`  
_L42-58_
- desc: Information into which buffer the AU data needs to be placed.
- L45 _public member_ `FString PeriodID;` — The period the data comes from. Necessary to track period transitions.
- L47 _public member_ `FString PeriodAdaptationSetID;` — Identifies the period and track (adaptation set) this data is originating from.
- L49 _public member_ `BCP47::FLanguageTag LanguageTag;` — Partial track metadata. See FTrackMetadata.
- L50 _public member_ `FString Kind;`
- L51 _public member_ `FString Codec;`
- L54 _public member_ `int32 HardIndex = -1;` — Internal hard index, used for multiplexed streams.
- L57 _public member_ `uint32 PlaybackSequenceID = 0;` — To which playback sequence this belongs.

#### struct `Electra::FAccessUnit`  
`struct FAccessUnit`  
_L60-183_
- L69 _public member_ `TSharedPtrTS<CodecData> AUCodecData;` — If set, points to constant sideband data for this access unit.
- L70 _public member_ `TSharedPtrTS<const FBufferSourceInfo> BufferSourceInfo;`
- L71 _public member_ `TUniquePtr<TMap<FName, TArray<uint8>>> DynamicSidebandData;` — If set, contains a map of dynamically changing sideband data for just this access unit.
- L72 _public member_ `EStreamType ESType;` — Type of elementary stream this is an access unit of.
- L73 _public member_ `FTimeValue PTS;` — PTS
- L74 _public member_ `FTimeValue DTS;` — DTS
- L75 _public member_ `FTimeValue Duration;` — Duration
- L76 _public member_ `FTimeValue EarliestPTS;` — Earliest PTS at which to present samples. If this is larger than PTS the sample is not to be presented.
- L77 _public member_ `FTimeValue LatestPTS;` — Latest PTS at which to present samples. If this is less than PTS the sample is not to be presented.
- L78 _public member_ `FTimeValue ProducerReferenceTime;` — If set, the wallclock time of the producer when this AU was encoded or captured
- L79 _public member_ `int64 SequenceIndex;`
- L80 _public member_ `void* AUData;` — Access unit data
- L81 _public member_ `uint32 AUSize;` — Size of this access unit
- L82 _public member_ `bool bIsFirstInSequence;` — true for the first AU in a segment
- L83 _public member_ `bool bIsLastInPeriod;` — true if this is the last AU in the playing period.
- L84 _public member_ `bool bIsSyncSample;` — true if this is a sync sample (keyframe)
- L85 _public member_ `bool bIsDummyData;` — True if this is not actual data but empty filler data due to some segment problem.
- L86 _public member_ `bool bTrackChangeDiscontinuity;` — True if this is the first AU after a track change.
- L87 _public member_ `bool bIsSideloaded;` — True if the payload is not streamed but loaded from a sidecar file.
- L90 _public function_ `static FAccessUnit* Create(IAccessUnitMemoryProvider* MemProvider)`
- L98 _public function_ `int64 TotalMemSize() const`
- L103 _public function_ `void AddRef()`
- L108 _public function_ `void SetCodecSpecificData(const TArray<uint8>& Csd)`
- L114 _public function_ `void SetCodecSpecificData(const TSharedPtrTS<CodecData>& Csd)`
- L119 _public function_ `void* AllocatePayloadBuffer(SIZE_T Num)`
- L125 _public function_ `void AdoptNewPayloadBuffer(void* Buffer, SIZE_T Num)`
- L135 _public function_ `static void Release(FAccessUnit* AccessUnit)`
- L150 _private member_ `IAccessUnitMemoryProvider* AUMemoryProvider;` — Interface to use to delete the allocated AU
- L151 _private member_ `uint32 RefCount;`
- L153 _private function_ `FAccessUnit()`
- L174 _private function_ `~FAccessUnit()`

#### struct `Electra::FAccessUnit::CodecData`  
`struct CodecData`  
_L62-67_
- L64 _public member_ `TArray<uint8> CodecSpecificData;`
- L65 _public member_ `TArray<uint8> RawCSD;`
- L66 _public member_ `FStreamCodecInformation ParsedInfo;`

#### struct `Electra::FAccessUnitBufferInfo`  
`struct FAccessUnitBufferInfo`  
_L190-218_
- L192 _public function_ `FAccessUnitBufferInfo()`
- L196 _public function_ `void Clear()`
- L209 _public member_ `FTimeValue FrontDTS;`
- L210 _public member_ `FTimeValue SmallestPTS;`
- L211 _public member_ `FTimeValue LargestPTSPlusDur;`
- L212 _public member_ `FTimeValue PlayableDuration;`
- L213 _public member_ `int64 CurrentMemInUse;`
- L214 _public member_ `int64 NumCurrentAccessUnits;`
- L215 _public member_ `bool bEndOfData;`
- L216 _public member_ `bool bEndOfTrack;`
- L217 _public member_ `bool bLastPushWasBlocked;`

#### class `Electra::FAccessUnitBuffer`  
`class FAccessUnitBuffer`  
_L224-612_
- desc: This class implements a decoder input data FIFO.
- L241 _public function_ `FAccessUnitBuffer() : FrontDTS(FTimeValue::GetInvalid()) , SmallestPTS(FTimeValue::GetInvalid()) , LargestPTSPlusDur(FTimeValue::GetInvalid()) , PlayableDuration(FTimeValue::GetZero()) , CurrentMemInUse(0) , bEndOfData(false) , bEndOfTrack(false) , bLastPushWasBlocked(false)`
- L253 _public function_ `~FAccessUnitBuffer()`
- L262 _public function_ `int64 Num() const` — Returns the number of access units currently in the FIFO.
- L269 _public function_ `int64 AllocatedSize() const` — Returns the amount of memory currently allocated.
- L276 _public function_ `void GetStats(FAccessUnitBufferInfo& OutStats) const` — Returns all vital statistics.
- L291 _public function_ `bool Push(FAccessUnit*& AU, const FConfiguration* Limit = nullptr, const FExternalBufferInfo* ExternalInfo = nullptr)` — Adds an access unit to the FIFO. Returns true if successful, false if the FIFO has insufficient free space.
- L338 _public function_ `void PushEndOfData()` — "Pushes" an end-of-data marker signaling that no further data will be pushed. May be called more than once. Flushing or pushing new data clears the flag.
- L343 _public function_ `void SetEndOfTrack()`
- L347 _public function_ `void ClearEndOfTrack()`
- L351 _public function_ `bool IsEndOfTrack() const`
- L357 _public function_ `bool Pop(FAccessUnit*& OutAU)` — Removes and returns the oldest access unit from the FIFO. Returns false if the FIFO is empty.
- L429 _public function_ `bool PeekAndAddRef(FAccessUnit*& OutAU)`
- L446 _public function_ `bool ContainsPTS(const FTimeValue& InPTS) const`
- L456 _public function_ `bool ContainsFuturePTS(const FTimeValue& InPTS) const`
- L468 _public function_ `void DiscardUntil(const FTimeValue& NextValidDTS, const FTimeValue& NextValidPTS, FTimeValue& OutPoppedDTS, FTimeValue& OutPoppedPTS)` — Discards data that has both its DTS and PTS less than the provided ones.
- L510 _public function_ `bool WaitForData(int64 waitForMicroseconds = -1)` — Waits for data to arrive. Returns true if data is present. False if not and timeout expired.
- L521 _public function_ `void Flush()` — Removes all elements from the FIFO
- L538 _public function_ `bool IsEndOfData() const` — Checks if the buffer has reached the end-of-data marker (marker is set and no more data is in the buffer).
- L545 _public function_ `bool IsEODFlagSet() const` — Checks if the end-of-data flag has been set. There may still be data in the buffer though!
- L552 _public function_ `bool WasLastPushBlocked() const` — Was the last push blocked because the buffer limits were reached?
- L579 _private function_ `bool CanPush(const FAccessUnit* AU, const FConfiguration* Limit, const FExternalBufferInfo* ExternalInfo)` — Checks if an access unit can be pushed to the FIFO. Returns true if successful, false if the FIFO has insufficient free space.
- L600 _private member_ `mutable FCriticalSection AccessLock;`
- L601 _private member_ `FExternalBufferInfo ZeroExternalInfo;`
- L602 _private member_ `TMediaQueueDynamicNoLock<FAccessUnit*> AccessUnits;`
- L603 _private member_ `FMediaSemaphore NumInSemaphore;`
- L604 _private member_ `FTimeValue FrontDTS;`
- L605 _private member_ `FTimeValue SmallestPTS;`
- L606 _private member_ `FTimeValue LargestPTSPlusDur;`
- L607 _private member_ `FTimeValue PlayableDuration;`
- L608 _private member_ `int64 CurrentMemInUse = 0;`
- L609 _private member_ `bool bEndOfData = false;`
- L610 _private member_ `bool bEndOfTrack = false;`
- L611 _private member_ `bool bLastPushWasBlocked = false;`

#### struct `Electra::FAccessUnitBuffer::FConfiguration`  
`struct FConfiguration`  
_L227-234_
- L229 _public function_ `FConfiguration(double InMaxSeconds = 0.0)`
- L233 _public member_ `FTimeValue MaxDuration;`

#### struct `Electra::FAccessUnitBuffer::FExternalBufferInfo`  
`struct FExternalBufferInfo`  
_L236-239_
- L238 _public member_ `FTimeValue Duration = FTimeValue::GetZero();`

#### class `Electra::FAccessUnitBuffer::FScopedLock`  
`class FScopedLock`  
_L558-575_
- desc: Helper class to lock the AU buffer
- L561 _public function_ `explicit FScopedLock(const FAccessUnitBuffer& owner) : mOwner(owner)`
- L566 _public function_ `~FScopedLock()`
- L571 _private prototype_ `FScopedLock() = delete;`
- L572 _private prototype_ `FScopedLock(const FScopedLock&) = delete;`
- L573 _private prototype_ `FScopedLock& operator= (const FScopedLock&) = delete;`
- L574 _private member_ `const FAccessUnitBuffer& mOwner;`

#### class `Electra::FMultiTrackAccessUnitBuffer`  
`class FMultiTrackAccessUnitBuffer : public TSharedFromThis<FMultiTrackAccessUnitBuffer, ESPMode::ThreadSafe>`  
_L621-718_
- inherits: `TSharedFromThis<FMultiTrackAccessUnitBuffer,ESPMode::ThreadSafe>`
- desc: A multi-track access unit buffer keeps access units from several tracks in individual buffers, one of which is selected to return AUs to the decoder from. The other unselected tracks will discard their AUs as the play position progresses.
- L624 _public prototype_ `FMultiTrackAccessUnitBuffer(EStreamType InForType);`
- L625 _public prototype_ `~FMultiTrackAccessUnitBuffer();`
- L626 _public prototype_ `void SetParallelTrackMode();`
- L627 _public prototype_ `void SelectTrackWhenAvailable(uint32 PlaybackSequenceID, TSharedPtrTS<FBufferSourceInfo> InBufferSourceInfo);`
- L628 _public prototype_ `bool Push(FAccessUnit*& AU, const FAccessUnitBuffer::FConfiguration* BufferConfiguration, const FAccessUnitBuffer::FExternalBufferInfo* InCurrentTotalBufferUtilization);`
- L629 _public prototype_ `void PushEndOfDataFor(TSharedPtrTS<const FBufferSourceInfo> InStreamSourceInfo);`
- L630 _public prototype_ `void PushEndOfDataAll();`
- L631 _public prototype_ `void SetEndOfTrackFor(TSharedPtrTS<const FBufferSourceInfo> InStreamSourceInfo);`
- L632 _public prototype_ `void SetEndOfTrackAll();`
- L633 _public prototype_ `void Flush();`
- L634 _public prototype_ `void GetStats(FAccessUnitBufferInfo& OutStats);`
- L635 _public prototype_ `FTimeValue GetLastPoppedDTS();`
- L636 _public prototype_ `FTimeValue GetLastPoppedPTS();`
- L637 _public prototype_ `FTimeValue GetPlayableDurationPushedSinceEOT();`
- L660 _public prototype_ `TSharedPtrTS<FAccessUnitBuffer> FindBufferFor(const TSharedPtrTS<const FBufferSourceInfo>& InBufferInfo);`
- L662 _public prototype_ `bool PeekAndAddRef(FAccessUnit*& OutAU);`
- L663 _public prototype_ `bool Pop(FAccessUnit*& OutAU);`
- L664 _public prototype_ `void PopDiscardUntil(FTimeValue UntilTime);`
- L665 _public prototype_ `bool IsEODFlagSet();`
- L666 _public prototype_ `bool IsEndOfTrack();`
- L667 _public prototype_ `int32 Num();`
- L668 _public prototype_ `bool WasLastPushBlocked();`
- L669 _public prototype_ `bool HasPendingTrackSwitch();`
- L692 _private prototype_ `void Clear();`
- L694 _private prototype_ `TSharedPtrTS<FAccessUnitBuffer> CreateNewBuffer();`
- L695 _private prototype_ `TSharedPtrTS<FAccessUnitBuffer> FindOrCreateBufferFor(TSharedPtrTS<const FBufferSourceInfo>& OutBufferSourceInfo, const TSharedPtrTS<const FBufferSourceInfo>& InBufferInfo, bool bCreateIfNotExist);`
- L696 _private prototype_ `void ActivateInitialBuffer();`
- L697 _private prototype_ `void HandlePendingSwitch();`
- L698 _private prototype_ `void RemoveOutdatedBuffers();`
- L700 _private prototype_ `TSharedPtrTS<FAccessUnitBuffer> GetSelectedTrackBuffer();`
- L702 _private member_ `FCriticalSection AccessLock;`
- L703 _private member_ `EStreamType Type;`
- L704 _private member_ `TArray<FBufferByInfoType> BufferList;`
- L705 _private member_ `FSwitchToBuffer PendingBufferSwitch;`
- L706 _private member_ `TSharedPtrTS<FAccessUnitBuffer> EmptyBuffer;`
- L707 _private member_ `TSharedPtrTS<FAccessUnitBuffer> ActiveBuffer;`
- L708 _private member_ `TSharedPtrTS<const FBufferSourceInfo> ActiveOutputBufferInfo;`
- L709 _private member_ `TSharedPtrTS<const FBufferSourceInfo> LastPoppedBufferInfo;`
- L710 _private member_ `FTimeValue LastPoppedDTS;`
- L711 _private member_ `FTimeValue LastPoppedPTS;`
- L712 _private member_ `FTimeValue PlayableDurationPushedSinceEOT;`
- L713 _private member_ `bool bEndOfData;`
- L714 _private member_ `bool bEndOfTrack;`
- L715 _private member_ `bool bLastPushWasBlocked;`
- L716 _private member_ `bool bPopAsDummyUntilSyncFrame;`
- L717 _private member_ `bool bIsParallelTrackMode;`

#### class `Electra::FMultiTrackAccessUnitBuffer::FScopedLock`  
`class FScopedLock`  
_L640-658_
- desc: Helper class to lock the AU buffer
- L643 _public function_ `explicit FScopedLock(TSharedPtrTS<FMultiTrackAccessUnitBuffer> Self) : LockedSelf(MoveTemp(Self))`
- L648 _public function_ `~FScopedLock()`
- L653 _private prototype_ `FScopedLock();`
- L654 _private prototype_ `FScopedLock(const FScopedLock&) = delete;`
- L655 _private prototype_ `FScopedLock& operator= (const FScopedLock&) = delete;`
- L657 _private member_ `TSharedPtrTS<FMultiTrackAccessUnitBuffer> LockedSelf;`

#### struct `Electra::FMultiTrackAccessUnitBuffer::FSwitchToBuffer`  
`struct FSwitchToBuffer`  
_L673-684_
- L675 _public function_ `void Reset()`
- L679 _public function_ `bool IsSet() const`
- L683 _public member_ `TSharedPtrTS<FBufferSourceInfo> BufferInfo;`

#### struct `Electra::FMultiTrackAccessUnitBuffer::FBufferByInfoType`  
`struct FBufferByInfoType`  
_L686-690_
- L688 _public member_ `TSharedPtrTS<const FBufferSourceInfo> Info;`
- L689 _public member_ `TSharedPtrTS<FAccessUnitBuffer> Buffer;`

#### class `Electra::IAccessUnitBufferInterface`  
`class IAccessUnitBufferInterface`  
_L728-741_
- desc: Base class for any decoder receiving data in "access units". An access unit (AU) is considered a data packet that can be sent into a decoder without the decoder stalling. For a h.264 decoder this is usually a single NALU.
- L731 _public prototype_ `virtual ~IAccessUnitBufferInterface() = default;`
- L734 _public prototype_ `virtual void AUdataPushAU(FAccessUnit* AccessUnit) = 0;` — Pushes an access unit to the decoder. Ownership of the access unit is transferred to the decoder.
- L736 _public prototype_ `virtual void AUdataPushEOD() = 0;` — Notifies the decoder that there will be no further access units.
- L738 _public prototype_ `virtual void AUdataClearEOD() = 0;` — Notifies the decoder that there may be further access units.
- L740 _public prototype_ `virtual void AUdataFlushEverything() = 0;` — Instructs the decoder to flush all pending input and all already decoded output.

#### class `Electra::IAccessUnitBufferListener`  
`class IAccessUnitBufferListener`  
_L752-774_
- desc: A decoder input buffer listener callback to monitor the current state of decoder input buffer levels. The decoder will invoke this listener right before it wants to get an access unit from its input buffer, whether the buffer already contains data or is empty.
- L755 _public prototype_ `virtual ~IAccessUnitBufferListener() = default;`
- L773 _public prototype_ `virtual void DecoderInputNeeded(const FBufferStats& CurrentInputBufferStats) = 0;` — Called right before the decoder wants to get an access unit from its input buffer, regardless if it already has data or not.

#### struct `Electra::IAccessUnitBufferListener::FBufferStats`  
`struct FBufferStats`  
_L757-770_
- L759 _public function_ `FBufferStats()`
- L763 _public function_ `void Clear()`
- L768 _public member_ `bool bEODSignaled;` — Set after PushEndOfData() has been called
- L769 _public member_ `bool bEODReached;` — Set after PushEndOfData() has been called AND the last AU was taken from the buffer.

#### class `Electra::IDecoderOutputBufferListener`  
`class IDecoderOutputBufferListener`  
_L785-812_
- desc: A decoder ready listener callback to monitor the decoder activity. The decoder will invoke this listener right before it needs a buffer from its output buffer prior to decoding. This is called whether or not the output buffer has room for new decoded data or not.
- L788 _public prototype_ `virtual ~IDecoderOutputBufferListener() = default;`
- L811 _public prototype_ `virtual void DecoderOutputReady(const FDecodeReadyStats& CurrentReadyStats) = 0;`

#### struct `Electra::IDecoderOutputBufferListener::FDecodeReadyStats`  
`struct FDecodeReadyStats`  
_L790-809_
- L792 _public function_ `FDecodeReadyStats()`
- L796 _public function_ `void Clear()`
- L804 _public member_ `FTimeRange InDecoderTimeRangePTS;` — Time range of elements in the decoder pipeline by PTS.
- L805 _public member_ `int64 OutputBufferPoolSize;` — Maximum number of decoded elements the output pool can hold.
- L806 _public member_ `int64 NumElementsInDecoder;` — Number of elements currently in the decoder pipeline.
- L807 _public member_ `bool bOutputStalled;` — true if the output is full and decoding is delayed until there's room again.
- L808 _public member_ `bool bEODreached;` — true when the final decoded element has been passed on (but may still be in the queue).

#### class `Electra::TAccessUnitQueue`  
`template <typename T> class TAccessUnitQueue`  
_L819-933_
- L822 _public prototype_ `TAccessUnitQueue() = default;`
- L824 _public function_ `~TAccessUnitQueue()`
- L829 _public function_ `void Enqueue(const T& InElement)`
- L835 _public function_ `void Enqueue(T&& InElement)`
- L841 _public function_ `int32 Num()`
- L846 _public function_ `bool IsEmpty()`
- L851 _public function_ `void Empty()`
- L860 _public function_ `bool Wait(int64 InWaitForMicroseconds)`
- L874 _public function_ `bool Dequeue(T& OutElement)`
- L889 _public function_ `bool Dequeue(T& OutElement, int64 InWaitForMicroseconds)`
- L904 _public function_ `void SetEOD()`
- L909 _public function_ `void ClearEOD()`
- L916 _public function_ `bool GetEOD() const`
- L921 _public function_ `bool ReachedEOD() const`
- L926 _private prototype_ `TAccessUnitQueue(const TAccessUnitQueue&) = delete;`
- L927 _private prototype_ `TAccessUnitQueue& operator = (const TAccessUnitQueue&) = delete;`
- L929 _private member_ `FMediaSemaphore AvailSema;`
- L930 _private member_ `TQueue<T> Elements;`
- L931 _private member_ `volatile bool bIsEOD = false;`
- L932 _private member_ `volatile bool bReachedEOD = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Electra`
- L15 _namespace_ `namespace DynamicSidebandData` (scope `Electra`)
- L17 _variable_ `const FName ITU_T_35(TEXT("itu-` (scope `Electra::DynamicSidebandData`)
- L18 _variable_ `const FName VPxAlpha(TEXT("vpx-` (scope `Electra::DynamicSidebandData`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/StreamDataBuffer.h` (Private)


#### class `Electra::FWaitableBuffer`  
`class FWaitableBuffer`  
_L12-389_
- desc: A buffer with waiting capability.
- L15 _public prototype_ `FWaitableBuffer() = default;`
- L16 _public prototype_ `FWaitableBuffer(const FWaitableBuffer&) = delete;`
- L17 _public prototype_ `FWaitableBuffer& operator=(const FWaitableBuffer&) = delete;`
- L19 _public function_ `~FWaitableBuffer()`
- L25 _public function_ `void SetExternalBuffer(uint8* InExternalBuffer, int64 InExternalBufferSize)`
- L34 _public function_ `bool Reserve(int64 InNumBytes)` — Allocates buffer of the specified capacity, destroying any previous buffer.
- L51 _public function_ `bool EnlargeTo(int64 InNewNumBytes)` — Enlarges the buffer to the new capacity, retaining the current content.
- L67 _public function_ `void Reset()` — Clears the buffer
- L81 _public function_ `int64 Capacity() const` — Returns the buffer capacity
- L88 _public function_ `int64 Num() const` — Returns the number of bytes in the buffer
- L95 _public function_ `int64 Avail() const` — Returns the number of free bytes in the buffer (amount that can be pushed)
- L102 _public function_ `bool IsEmpty() const` — Checks if the buffer is empty.
- L108 _public function_ `bool IsFull() const` — Checks if the buffer is full.
- L114 _public function_ `bool IsEndOfData() const` — Checks if the buffer has reached the end-of-data marker (marker is set and no more data is in the buffer).
- L120 _public function_ `bool GetEOD() const` — Checks if the end-of-data flag has been set. There may still be data in the buffer though!
- L130 _public function_ `bool WaitUntilSizeAvailable(int64 SizeNeeded, int32 TimeoutMicroseconds)` — Waits until the specified number of bytes has arrived in the buffer. Note: This method is somewhat dangerous in that there is no guarantee the required amount will ever arrive. You must also never wait for more data than is the capcacity of the buffer!
- L166 _public function_ `bool PushData(const uint8* InData, int64 NumElements)` — Inserts elements into the buffer. Returns true if successful, false if there is no room.
- L196 _public function_ `void SetEOD()` — "Pushes" an end-of-data marker signaling that no further data will be pushed. May be called more than once. Buffer must be Reset() before next use.
- L204 _public function_ `void RemoveFromBeginning(int64 InNumBytesToRemove)`
- L220 _public function_ `void Lock()`
- L225 _public function_ `void Unlock()`
- L231 _public function_ `FCriticalSection* GetLock()` — For use with an external FScopeLock
- L236 _public function_ `int64 GetLinearReadSize() const`
- L242 _public function_ `void SetLinearReadSize(int64 InNewSize)`
- L249 _public function_ `const uint8* GetLinearReadData() const` — Must control Lock()/Unlock() externally!
- L253 _public function_ `uint8* GetLinearReadData()`
- L258 _public function_ `uint8* GetLinearWriteData(int64 InNumBytesToAppend)`
- L269 _public function_ `void AppendedNewData(int64 InNumAppended)`
- L283 _public function_ `void SetExternalData(TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> InExternalBuffer)`
- L299 _public function_ `void Abort()`
- L306 _public function_ `bool WasAborted() const`
- L311 _public function_ `void SetHasErrored()`
- L316 _public function_ `bool HasErrored() const`
- L322 _protected function_ `uint8* GetBufferBase() const`
- L327 _protected function_ `bool Allocate(int64 InSize)`
- L344 _protected function_ `void Deallocate()`
- L352 _protected function_ `bool InternalGrowTo(int64 InNewNumBytes)`
- L362 _protected function_ `void CopyData(uint8* CopyTo, const uint8* CopyFrom, int64 NumElements)`
- L370 _protected member_ `mutable FCriticalSection AccessLock;`
- L372 _protected member_ `FMediaEvent SizeAvailableSignal;` — Signal which gets set when at least `WaitingForSize` amount of data is present
- L374 _protected member_ `TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> Buffer;` — The buffer
- L376 _protected member_ `uint64 DataSize = 0;` — Allocated buffer size
- L378 _protected member_ `uint64 WritePos = 0;` — Offset into buffer where to add new data
- L380 _protected member_ `uint64 WaitingForSize = 0;` — Amount of data necessary to be present for `SizeAvailableSignal` to get set.
- L382 _protected member_ `uint8* ExternalBuffer = nullptr;` — If set a buffer is provided externally to read into directly.
- L384 _protected member_ `volatile bool bEOD = false;` — Flag indicating that no additional data will be added to the buffer.
- L386 _protected member_ `volatile bool bWasAborted = false;` — Flag indicating that reading into the buffer has been aborted.
- L388 _protected member_ `volatile bool bHasErrored = false;` — Flag indicating that filling the buffer from the source has encountered an error.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/StreamTypes.h` (Private)


#### enum `Electra::EStreamType`  
`enum class EStreamType`  
_L16-22_
- L18 _public enumerator_ `Unsupported`
- L19 _public enumerator_ `Video`
- L20 _public enumerator_ `Audio`
- L21 _public enumerator_ `Subtitle`

#### class `Electra::FStreamCodecInformation`  
`class FStreamCodecInformation`  
_L60-711_
- L63 _public function_ `FStreamCodecInformation()`
- L67 _public prototype_ `explicit FStreamCodecInformation(const FCodecTypeFormat& InFromCodecTypeFormat);`
- L68 _public prototype_ `FCodecTypeFormat ToCodecTypeFormat() const;`
- L90 _public function_ `EStreamType GetStreamType() const`
- L95 _public function_ `void SetMimeType(const FString& InMimeType)`
- L99 _public prototype_ `FString GetMimeType() const;`
- L100 _public prototype_ `FString GetMimeTypeWithCodec() const;`
- L101 _public prototype_ `FString GetMimeTypeWithCodecAndFeatures() const;`
- L103 _public prototype_ `bool ParseFromRFC6381(const FString& CodecOTI);`
- L105 _public function_ `void SetStreamType(EStreamType InStreamType)`
- L110 _public function_ `uint32 GetCodec4CC() const`
- L115 _public function_ `void SetCodec4CC(uint32 In4CC)`
- L121 _public function_ `ECodec GetCodec() const`
- L126 _public function_ `void SetCodec(ECodec InCodec)`
- L132 _public prototype_ `FString GetCodecName() const;`
- L134 _public prototype_ `void UpdateFromExtraBoxes();`
- L136 _public function_ `bool IsVideoCodec() const`
- L149 _public function_ `bool IsAudioCodec() const`
- L163 _public function_ `bool IsSubtitleCodec() const`
- L177 _public function_ `bool IsCodec(EStreamType InType) const`
- L197 _public function_ `const FString& GetCodecSpecifierRFC6381() const`
- L202 _public function_ `void SetCodecSpecifierRFC6381(const FString& InCodecSpecifier)`
- L208 _public prototype_ `const FString& GetHumanReadableCodecName() const;`
- L210 _public function_ `void SetHumanReadableCodecName(const FString& InHumanReadableCodecName)`
- L261 _public function_ `const FResolution& GetResolution() const`
- L266 _public function_ `void SetResolution(const FResolution& InResolution)`
- L307 _public function_ `const FTranslation& GetTranslation() const`
- L312 _public function_ `void SetTranslation(const FTranslation& InTranslation)`
- L379 _public function_ `const FCrop& GetCrop() const`
- L384 _public function_ `void SetCrop(const FCrop& InCrop)`
- L389 _public function_ `const FAspectRatio& GetAspectRatio() const`
- L394 _public function_ `void SetAspectRatio(const FAspectRatio& InAspectRatio)`
- L399 _public function_ `const FTimeFraction& GetFrameRate() const`
- L404 _public function_ `void SetFrameRate(const FTimeFraction& InFrameRate)`
- L413 _public function_ `void SetProfileSpace(int32 InProfileSpace)`
- L419 _public function_ `int32 GetProfileSpace() const`
- L424 _public function_ `void SetProfile(int32 InProfile)`
- L430 _public function_ `int32 GetProfile() const`
- L435 _public function_ `void SetProfileLevel(int32 InLevel)`
- L441 _public function_ `int32 GetProfileLevel() const`
- L446 _public function_ `void SetProfileCompatibilityFlags(uint32 InCompatibilityFlags)`
- L452 _public function_ `uint32 GetProfileCompatibilityFlags() const`
- L457 _public function_ `void SetProfileConstraints(uint64 InConstraints)`
- L463 _public function_ `uint64 GetProfileConstraints() const`
- L468 _public function_ `void SetProfileTier(int32 InTier)`
- L474 _public function_ `int32 GetProfileTier() const`
- L479 _public function_ `void SetSamplingRate(int32 InSamplingRate)`
- L485 _public function_ `int32 GetSamplingRate() const`
- L490 _public function_ `void SetNumberOfChannels(int32 InNumberOfChannels)`
- L496 _public function_ `int32 GetNumberOfChannels() const`
- L501 _public function_ `void SetChannelConfiguration(uint32 InChannelConfiguration)`
- L507 _public function_ `uint32 GetChannelConfiguration() const`
- L512 _public function_ `void SetAudioDecodingComplexity(int InAudioDecodingComplexity)`
- L518 _public function_ `int32 GetAudioDecodingComplexity() const`
- L523 _public function_ `void SetAudioAccessibility(int32 InAudioAccessibility)`
- L529 _public function_ `int32 GetAudioAccessibility() const`
- L534 _public function_ `void SetNumberOfAudioObjects(int32 InNumberOfAudioObjects)`
- L540 _public function_ `int32 GetNumberOfAudioObjects() const`
- L545 _public function_ `void SetStreamLanguageTag(const BCP47::FLanguageTag& InStreamLanguageTag)`
- L550 _public function_ `void SetCodecSpecificData(const TArray<uint8>& InCSD)`
- L555 _public function_ `const TArray<uint8>& GetCodecSpecificData() const`
- L560 _public function_ `void SetDecoderConfigRecord(const TArray<uint8>& InDCR)`
- L565 _public function_ `const TArray<uint8>& GetDecoderConfigRecord() const`
- L570 _public function_ `void SetBitrate(int32 InBitrate)`
- L575 _public function_ `int32 GetBitrate() const`
- L580 _public function_ `FParamDict& GetExtras()`
- L585 _public function_ `const FParamDict& GetExtras() const`
- L590 _public function_ `void Clear()`
- L617 _public function_ `bool Equals(const FStreamCodecInformation& Other) const`
- L649 _private function_ `void ResetHumanReadableCodecName()`
- L653 _private prototype_ `bool TryConstructHumanReadableCodecName() const;`
- L688 _private member_ `EStreamType StreamType;`
- L689 _private member_ `FString CodecSpecifier;` — Codec specifier as per RFC 6381
- L690 _private member_ `FString MimeType;` — Explicitly set mime type if it cannot be inferred.
- L691 _private member_ `ECodec Codec;`
- L692 _private member_ `FResolution Resolution;` — Resolution, if this is a video stream
- L693 _private member_ `FCrop Crop;` — Cropping, if this is a video stream
- L694 _private member_ `FTranslation Translation;` — Top-left corner offset for subtitles
- L695 _private member_ `FAspectRatio AspectRatio;` — Aspect ratio, if this is a video stream
- L696 _private member_ `FTimeFraction FrameRate;` — Frame rate, if this is a video stream
- L697 _private member_ `FProfileLevel ProfileLevel;`
- L698 _private member_ `BCP47::FLanguageTag StreamLanguageTag;`
- L699 _private member_ `int32 Bitrate;`
- L700 _private member_ `int32 SampleRate;` — Decoded sample rate, if this is an audio stream.
- L701 _private member_ `int32 NumChannels;` — Number of decoded channels, if this is an audio stream.
- L702 _private member_ `uint32 ChannelConfiguration;` — Format specific audio channel configuration
- L703 _private member_ `int32 AudioDecodingComplexity;` — Format specific audio decoding complexity
- L704 _private member_ `int32 AudioAccessibility;` — Format specific audio accessibility
- L705 _private member_ `int32 NumberOfAudioObjects;` — Format specific number of audio objects
- L706 _private member_ `uint32 Codec4CC;`
- L707 _private member_ `FParamDict Extras;` — Additional details/properties, depending on playlist.
- L708 _private member_ `TArray<uint8> CSD;` — Codec specific data, if available.
- L709 _private member_ `TArray<uint8> DCR;` — Decoder configuration record, if available.
- L710 _private member_ `mutable FString HumanReadableCodecName;`

#### enum `Electra::FStreamCodecInformation::ECodec`  
`enum class ECodec`  
_L70-88_
- L73 _public enumerator_ `Unknown = 0` — --- Unknown ---
- L75 _public enumerator_ `H264 = 1` — --- Video ---
- L76 _public enumerator_ `H265`
- L77 _public enumerator_ `Video4CC`
- L79 _public enumerator_ `AAC = 100` — --- Audio ---
- L80 _public enumerator_ `EAC3`
- L81 _public enumerator_ `AC3`
- L82 _public enumerator_ `Audio4CC`
- L84 _public enumerator_ `WebVTT = 200` — --- Subtitle / Caption ---
- L85 _public enumerator_ `TTML`
- L86 _public enumerator_ `TX3G`
- L87 _public enumerator_ `OtherSubtitle`

#### struct `Electra::FStreamCodecInformation::FResolution`  
`struct FResolution`  
_L215-259_
- L217 _public function_ `FResolution(int32 w = 0, int32 h = 0) : Width(w) , Height(h)`
- L222 _public function_ `void Clear()`
- L226 _public function_ `bool IsSet() const`
- L230 _public function_ `bool ExceedsLimit(int32 LimitWidth, int32 LimitHeight) const`
- L242 _public function_ `bool ExceedsLimit(const FResolution& Limit) const`
- L247 _public function_ `bool operator == (const FResolution& rhs) const`
- L252 _public function_ `bool operator != (const FResolution& rhs) const`
- L257 _public member_ `int32 Width;`
- L258 _public member_ `int32 Height;`

#### struct `Electra::FStreamCodecInformation::FTranslation`  
`struct FTranslation`  
_L273-305_
- L275 _public function_ `FTranslation(int32 x = 0, int32 y = 0) : Left(x) , Top(y)`
- L280 _public function_ `void Clear()`
- L284 _public function_ `int32 GetX() const`
- L288 _public function_ `int32 GetY() const`
- L293 _public function_ `bool operator == (const FTranslation& rhs) const`
- L298 _public function_ `bool operator != (const FTranslation& rhs) const`
- L303 _public member_ `int32 Left;`
- L304 _public member_ `int32 Top;`

#### struct `Electra::FStreamCodecInformation::FAspectRatio`  
`struct FAspectRatio`  
_L318-346_
- L320 _public function_ `FAspectRatio(int32 w = 0, int32 h = 0) : Width(w) , Height(h)`
- L325 _public function_ `void Clear()`
- L329 _public function_ `bool IsSet() const`
- L334 _public function_ `bool operator == (const FAspectRatio& rhs) const`
- L339 _public function_ `bool operator != (const FAspectRatio& rhs) const`
- L344 _public member_ `int32 Width;`
- L345 _public member_ `int32 Height;`

#### struct `Electra::FStreamCodecInformation::FCrop`  
`struct FCrop`  
_L348-377_
- L350 _public function_ `FCrop(int32 InLeft = 0, int32 InTop = 0, int32 InRight = 0, int32 InBottom = 0) : Left(InLeft) , Top(InTop) , Right(InRight) , Bottom(InBottom)`
- L358 _public function_ `void Clear()`
- L363 _public function_ `bool operator == (const FCrop& rhs) const`
- L368 _public function_ `bool operator != (const FCrop& rhs) const`
- L373 _public member_ `int32 Left;`
- L374 _public member_ `int32 Top;`
- L375 _public member_ `int32 Right;`
- L376 _public member_ `int32 Bottom;`

#### struct `Electra::FStreamCodecInformation::FProfileLevel`  
`struct FProfileLevel`  
_L655-686_
- L657 _public function_ `FProfileLevel()`
- L661 _public function_ `void Clear()`
- L670 _public member_ `int32 ProfileSpace;`
- L671 _public member_ `int32 Profile;`
- L672 _public member_ `int32 Level;`
- L673 _public member_ `uint32 CompatibilityFlags;`
- L674 _public member_ `uint64 Constraints;`
- L675 _public member_ `int32 Tier;`
- L677 _public function_ `bool operator == (const FProfileLevel& rhs) const`
- L682 _public function_ `bool operator != (const FProfileLevel& rhs) const`

#### struct `Electra::FStreamMetadata`  
`struct FStreamMetadata`  
_L737-747_
- desc: Metadata of an elementary stream as specified by the playlist/manifest. This is only as correct as the information in the manifest. If any part is not listed there the information in here will be incomplete.
- L739 _public member_ `FStreamCodecInformation CodecInformation;` — Stream codec information
- L740 _public member_ `FString ID;` — ID of this stream
- L741 _public member_ `int32 Bandwidth;` — Bandwidth required for this stream in bits per second
- L742 _public member_ `int32 QualityIndex = 0;`
- L743 _public function_ `bool Equals(const FStreamMetadata& Other) const`

#### struct `Electra::FTrackMetadata`  
`struct FTrackMetadata`  
_L757-787_
- desc: Metadata per track type. See: https://dev.w3.org/html5/html-sourcing-inband-tracks/ While this may not represent every possible "role" the presentation format may offer this is a representation that covers most of the use cases and can be applied to a variety of formats.
- L759 _public member_ `BCP47::FLanguageTag LanguageTagRFC5646;`
- L760 _public member_ `FString ID;`
- L761 _public member_ `FString Kind;`
- L762 _public member_ `FString Label;`
- L763 _public member_ `TOptional<FTimespan> Duration;`
- L765 _public member_ `TArray<FStreamMetadata> StreamDetails;`
- L766 _public member_ `FStreamCodecInformation HighestBandwidthCodec;`
- L767 _public member_ `int32 HighestBandwidth = 0;`
- L768 _public function_ `bool Equals(const FTrackMetadata& Other) const`

#### struct `Electra::FStreamSelectionAttributes`  
`struct FStreamSelectionAttributes`  
_L794-884_
- desc: Stream selection attributes. See FTrackMetadata comments.
- L798 _public member_ `TOptional<FString> Language_RFC4647;` — Used for video, audio and subtitles or captions. This is a comma separated string of RFC-4647 language ranges to match the RFC-5646 language tag provided by the stream metadata.
- L801 _public member_ `TOptional<FString> Kind;` — Primarily used for audio selection. Should typically be set to "main" or left unset.
- L805 _public member_ `TOptional<FString> Codec;` — Preferred codec. Typically set to ensure the same track remains selected after a seek in case the same content is provided with different formats. See GetCodecName()
- L809 _public member_ `TOptional<int32> OverrideIndex;` — Rarely used. Unconditionally selects a track by its index where the index is a sequential numbering from [0..n) of the tracks as they are found. If the index is invalid the selection rules for kind and language are applied.
- L811 _public function_ `bool IsSet() const`
- L816 _public function_ `bool IsCompatibleWith(const FStreamSelectionAttributes& Other)`
- L838 _public function_ `void Reset()`
- L845 _public function_ `void UpdateWith(const FString& InKind, const BCP47::FLanguageTag& InLanguageTag, const FString& InCodec, int32 InOverrideIndex)`
- L870 _public function_ `void UpdateIfOverrideSet(const FString& InKind, const BCP47::FLanguageTag& InLanguageTag, const FString& InCodec)`
- L880 _public function_ `void ClearOverrideIndex()`

#### class `Electra::FCodecSelectionPriorities`  
`class FCodecSelectionPriorities`  
_L888-935_
- L918 _public prototype_ `bool Initialize(const FString& ConfigurationString);` — Initializes this selector with a priority string in the following FORMAT: FORMAT = CLASSPRIO 0*[COMMA CLASSPRIO] COMMA = , EQ = = PRIO = 1*DIGIT PREFIX = 1*VCHAR    ; except , = { } CLASS = PREFIX CODECPRIO = CLASS EQ PRIO CLASSWITHPRIO = CODECPRIO 0*[ { CODECPRIO 0*[ COMMA CODECPRIO ] } ] CLASSWITHOUTPRIO = CLASS 1*[ { CODECPRIO 0*[ COMMA CODECPRIO ] } ] CLASSPRIO = CLASSWITHPRIO / CLASSWITHOUTPRIO Examples: hvc=2,hev=2,avc=1 mp4a{mp4a.40.5=0,mp4a.40.2=1} First codec priorities are given for an entire codec class (eg. "hvc"). Within each class, where it makes sense, individual streams can be prioritized. Say within a class "mp4a" there are two AAC streams. One LC and one HE. To use the LC over the HE stream the "mp4a" class gives more detailed codec prefixes and their priorities like the above example. If used with DASH streams the class priority can be thought of the priority of an AdaptationSet and the stream priority of that of a Representation. User defined priorities override the @selectionPriority attribute of a DASH AdaptationSet or Representation.
- L919 _public prototype_ `int32 GetClassPriority(const FString& CodecSpecifierRFC6381) const;`
- L920 _public prototype_ `int32 GetStreamPriority(const FString& CodecSpecifierRFC6381) const;`
- L922 _private prototype_ `bool ParseInternal(const FString& ConfigurationString);`
- L934 _private member_ `TArray<FClassPriority> ClassPriorities;`

#### struct `Electra::FCodecSelectionPriorities::FStreamPriority`  
`struct FStreamPriority`  
_L923-927_
- L925 _public member_ `FString Prefix;`
- L926 _public member_ `int32 Priority = -1;`

#### struct `Electra::FCodecSelectionPriorities::FClassPriority`  
`struct FClassPriority`  
_L928-933_
- L930 _public member_ `FString Prefix;`
- L931 _public member_ `int32 Priority = -1;`
- L932 _public member_ `TArray<FStreamPriority> StreamPriorities;`

#### struct `Electra::FPlayerSequenceState`  
`struct FPlayerSequenceState`  
_L939-963_
- L941 _public function_ `FPlayerSequenceState()`
- L945 _public function_ `void Reset()`
- L950 _public function_ `int64 GetSequenceIndex() const`
- L954 _public function_ `void SetSequenceIndex(int64 SequenceIndex)`
- L961 _public member_ `int32 PrimaryIndex;`
- L962 _public member_ `int32 SecondaryIndex;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Electra`
- L24 _function_ `static inline const TCHAR* GetStreamTypeName(EStreamType StreamType)` (scope `Electra`)
- L40 _function_ `static inline constexpr int32 StreamTypeToArrayIndex(EStreamType StreamType)` (scope `Electra`)
- L47 _function_ `static inline constexpr int32 StreamTypeToArrayIndex0(EStreamType StreamType)` (scope `Electra`)
- L53 _function_ `static inline constexpr EStreamType StreamArrayIndexToType(int32 InIndex)` (scope `Electra`)
- L714 _namespace_ `namespace StreamCodecInformationOptions` (scope `Electra`)
- L716 _variable_ `static const FName DecoderConfigurationRecord(TEXT("dcr"` (scope `Electra::StreamCodecInformationOptions`)
- L717 _variable_ `static const FName VPccBox(TEXT("vpcC` (scope `Electra::StreamCodecInformationOptions`)
- L718 _variable_ `static const FName AV1cBox(TEXT("av1C` (scope `Electra::StreamCodecInformationOptions`)
- L719 _variable_ `static const FName ColrBox(TEXT("colr` (scope `Electra::StreamCodecInformationOptions`)
- L720 _variable_ `static const FName DOpsBox(TEXT("dOps` (scope `Electra::StreamCodecInformationOptions`)
- L721 _variable_ `static const FName ChanBox(TEXT("chan` (scope `Electra::StreamCodecInformationOptions`)
- L722 _variable_ `static const FName SamplesPerBlock(TEXT("samp` (scope `Electra::StreamCodecInformationOptions`)
- L723 _variable_ `static const FName FormatSpecificFlags(TEXT("Form` (scope `Electra::StreamCodecInformationOptions`)
- L724 _variable_ `static const FName SampleSize(TEXT("Samp` (scope `Electra::StreamCodecInformationOptions`)
- L725 _variable_ `static const FName ConstBytesPerAudioPacket(TEXT("Cons` (scope `Electra::StreamCodecInformationOptions`)
- L726 _variable_ `static const FName ConstLPCMFramesPerAudioPacket(TEXT("Cons` (scope `Electra::StreamCodecInformationOptions`)
- L727 _variable_ `static const FName PresentationTimeOffset(TEXT("Pres` (scope `Electra::StreamCodecInformationOptions`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/SynchronizedClock.h` (Private)


#### class `Electra::ISynchronizedUTCTime`  
`class ISynchronizedUTCTime`  
_L14-36_
- desc: This implements a UTC clock synchronized to an external time source.
- L17 _public prototype_ `static ISynchronizedUTCTime* Create();`
- L18 _public prototype_ `virtual ~ISynchronizedUTCTime() = default;`
- L23 _public prototype_ `virtual void SetTime(const FTimeValue& TimeNow) = 0;` — Establishes a relationship between the current local system time and actual UTC time.
- L25 _public prototype_ `virtual void SetTime(const FTimeValue& LocalTime, const FTimeValue& UTCTime) = 0;`
- L30 _public prototype_ `virtual FTimeValue GetTime() = 0;` — Gets the current system time as synchronized UTC time.
- L35 _public prototype_ `virtual FTimeValue MapToSyncTime(const FTimeValue& InTimeToMap) = 0;` — Returns the synchronized UTC time for a given time.

#### class `Electra::MEDIAutcTime`  
`class MEDIAutcTime`  
_L42-50_
- desc: System wallclock time (UTC)
- L45 _public function_ `static Electra::FTimeValue Current()`
- L49 _public prototype_ `static int64 CurrentMSec();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Utilities/HashFunctions.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L9 _namespace_ `namespace HashFunctions` (scope `Electra`)
- L12 _namespace_ `namespace CRC` (scope `Electra::HashFunctions`)
- L14 _prototype_ `uint32 Update32(uint32 InitialCrc, const void* Data, int64 NumBytes);` (scope `Electra::HashFunctions::CRC`)
- L15 _prototype_ `uint32 Calc32(const void* Data, int64 NumBytes);` (scope `Electra::HashFunctions::CRC`)
- L17 _prototype_ `uint64 Update64(uint64 InitialCrc, const void* Data, int64 NumBytes);` (scope `Electra::HashFunctions::CRC`)
- L18 _prototype_ `uint64 Calc64(const void* Data, int64 NumBytes);` (scope `Electra::HashFunctions::CRC`)

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Utilities/MP4Helpers.h` (Private)


#### class `Electra::FMP4DataLoader`  
`class FMP4DataLoader : public MP4Utilities::IMP4DataReaderBase, public TSharedFromThis<FMP4DataLoader, ESPMode::ThreadSafe>`  
_L15-62_
- inherits: `MP4Utilities::IMP4DataReaderBase,TSharedFromThis<FMP4DataLoader,ESPMode::ThreadSafe>`
- L18 _public function_ `static TSharedPtr<FMP4DataLoader, ESPMode::ThreadSafe> Create()`
- L20 _public prototype_ `virtual ~FMP4DataLoader();`
- L30 _public prototype_ `void Open(const FString& InURL, const FHttpParams& InHttpParams);`
- L31 _public prototype_ `void Close();`
- L34 _public prototype_ `int64 ReadData(void* InOutBuffer, int64 InNumBytes, int64 InFromOffset, FCancellationCheckDelegate InCheckCancellationDelegate) override;` — Methods from MP4Utilities::IMP4DataReaderBase
- L35 _public function_ `int64 GetTotalFileSize() override`
- L37 _public function_ `int64 GetCurrentFileOffset() override`
- L39 _public prototype_ `bool HasReachedEOF() override;`
- L40 _public function_ `FString GetLastError() override`
- L43 _public function_ `const HTTP::FConnectionInfo& GetConnectionInfo() const`
- L47 _private prototype_ `FMP4DataLoader() = default;`
- L48 _private prototype_ `void HTTPCompletionHandle(const IElectraHttpManager::FRequest* InRequest);`
- L49 _private member_ `FHttpParams HttpParams;`
- L50 _private member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L51 _private member_ `FString URL;`
- L52 _private member_ `FString LastError;`
- L53 _private member_ `FMediaEvent ReadCompleted;`
- L54 _private member_ `TSharedPtr<IElectraHttpManager::FProgressListener, ESPMode::ThreadSafe> ProgressListener;`
- L55 _private member_ `FArchive* Archive = nullptr;`
- L56 _private member_ `int64 FileSize = -1;`
- L57 _private member_ `int64 CurrentOffset = 0;`
- L58 _private member_ `int64 CurrentEndOffsetIncluding = -1;`
- L59 _private member_ `bool bIsFirstRead = true;`
- L60 _private member_ `volatile bool bHasErrored = false;`
- L61 _private member_ `volatile bool bWasAborted = false;`

#### struct `Electra::FMP4DataLoader::FHttpParams`  
`struct FHttpParams`  
_L22-29_
- L24 _public member_ `TSharedPtr<IElectraHttpManager, ESPMode::ThreadSafe> HTTPManager;`
- L25 _public member_ `TSharedPtr<IHTTPResponseCache, ESPMode::ThreadSafe> HTTPResponseCache;`
- L26 _public member_ `TArray<HTTP::FHTTPHeader> RequestHeaders;`
- L27 _public member_ `int32 ConnectTimeoutMillis = 8000;`
- L28 _public member_ `int32 NoDataTimeoutMillis = 6000;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Private/Runtime/Utilities/UtilsMP4.h` (Private)


#### class `Electra::UtilsMP4`  
`class UtilsMP4`  
_L11-71_

#### class `Electra::UtilsMP4::FMP4RootBoxLocator`  
`class FMP4RootBoxLocator`  
_L15-45_
- L26 _public prototype_ `FMP4RootBoxLocator() = default;`
- L27 _public prototype_ `~FMP4RootBoxLocator();`
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);`
- L29 _public prototype_ `bool LocateRootBoxes(TArray<FBoxInfo>& OutBoxInfos, const TSharedPtrTS<IElectraHttpManager>& InHTTPManager, const FString& InURL, const TArray<HTTP::FHTTPHeader>& InRequestHeaders, const TArray<uint32>& InFirstBoxes, const TArray<uint32>& InStopAfterBoxes, const TArray<uint32>& InReadDataOfBoxes, FCancellationCheckDelegate InCheckCancellationDelegate);`
- L31 _public function_ `int64 GetFileSize() const`
- L33 _public function_ `bool DidDownloadFail() const`
- L35 _public function_ `const HTTP::FConnectionInfo& GetConnectionInfo() const`
- L38 _public function_ `const FString& GetErrorMessage() const`
- L41 _private member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L42 _private member_ `FString ErrorMsg;`
- L43 _private member_ `int64 FileSize = -1;`
- L44 _private member_ `volatile bool bHasErrored = false;`

#### struct `Electra::UtilsMP4::FMP4RootBoxLocator::FBoxInfo`  
`struct FBoxInfo`  
_L18-25_
- L20 _public member_ `int64 Size = 0;`
- L21 _public member_ `int64 Offset = 0;`
- L22 _public member_ `uint32 Type = 0;`
- L23 _public member_ `uint8 UUID[16] {};`
- L24 _public member_ `TSharedPtrTS<FWaitableBuffer> DataBuffer;`

#### class `Electra::UtilsMP4::FMP4ChunkLoader`  
`class FMP4ChunkLoader`  
_L47-70_
- L50 _public prototype_ `FMP4ChunkLoader() = default;`
- L51 _public prototype_ `~FMP4ChunkLoader() = default;`
- L53 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);`
- L54 _public prototype_ `TSharedPtrTS<FWaitableBuffer> LoadChunk(const int64 InOffset, const int64 InSize, const TSharedPtrTS<IElectraHttpManager>& InHTTPManager, const TSharedPtrTS<IHTTPResponseCache>& InHttpResponseCache, const FString& InURL, FCancellationCheckDelegate InCheckCancellationDelegate);`
- L56 _public function_ `int64 GetFileSize() const`
- L58 _public function_ `bool DidDownloadFail() const`
- L60 _public function_ `const HTTP::FConnectionInfo& GetConnectionInfo() const`
- L63 _public function_ `const FString& GetErrorMessage() const`
- L66 _private member_ `HTTP::FConnectionInfo ConnectionInfo;`
- L67 _private member_ `FString ErrorMsg;`
- L68 _private member_ `int64 FileSize = -1;`
- L69 _private member_ `volatile bool bHasErrored = false;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);`
- L53 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/Android/ElectraPlayerResourceDelegate.h` (Public)


#### class `IElectraPlayerResourceDelegate`  
`class IElectraPlayerResourceDelegate`  
_L8-14_
- L11 _public prototype_ `virtual ~IElectraPlayerResourceDelegate() = default;`
- L13 _public prototype_ `virtual jobject GetCodecSurface() = 0;`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/Apple/ElectraPlayerResourceDelegate.h` (Public)


#### class `IElectraPlayerResourceDelegate`  
`class IElectraPlayerResourceDelegate`  
_L4-8_
- L7 _public function_ `virtual ~IElectraPlayerResourceDelegate()`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/ElectraPlayerMisc.h` (Public)


#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraPlayer, Log, All);` — Log category for the ElectraPlayer module.
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraPlayerStats, Log, All);`
- L18 _delegate_ `DECLARE_STATS_GROUP(TEXT("ElectraPlayer"), STATGROUP_ElectraPlayer, STATC` — UE Profiler

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/IElectraPlayerDataCache.h` (Public)


#### class `IElectraPlayerDataCache`  
`class IElectraPlayerDataCache : public TSharedFromThis<IElectraPlayerDataCache, ESPMode::ThreadSafe>`  
_L6-106_
- inherits: `TSharedFromThis<IElectraPlayerDataCache,ESPMode::ThreadSafe>`
- L9 _public prototype_ `virtual ~IElectraPlayerDataCache() = default;`
- L76 _public typedef_ `using FCacheDataPtr = TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe>;`
- L87 _public prototype_ `virtual void AddElementToCache(const FItemInfo& ItemInfoToCache, FCacheDataPtr DataToCache) = 0;` — Asks to add an item to the cache. Whether or not the item gets added is under the purview of the cache implementation. As such, this method has no return value to indicate success. This method should not block to wait until the cache has been updated. It should merely schedule an asynchronous update and defer writing the data to the storage to some asynchronous task.
- L97 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FCachedDataReadCompleted, ECacheResult , FItemInfo , FCacheDataPtr );`
- L105 _public prototype_ `virtual void GetElementFromCache(const FItemInfo& ItemToGetFromCache, FCachedDataReadCompleted CompletionDelegate) = 0;` — Asks to get an item from the cache. The item to get is described by `InItemToGetFromCache`, with the exception of the `.Range.TotalSize` member which is not known ahead of time. If the cache fulfills the request the `OutCachedItemInfo` is expected to be set up, including the `.Range.TotalSize` member.

#### struct `IElectraPlayerDataCache::FItemInfo`  
`struct FItemInfo`  
_L11-74_
- L46 _public member_ `FString URI;` — Unique resource identifier. Typically a URL.
- L54 _public member_ `FRange Range;` — Possible sub-range within the resource. Will be set when adding to the cache. When asking the cache for a hit the `TotalSize` member will not be set (-1) but is expected to be filled in when returning the cached element with the value that was provided when adding the entry to the cache.
- L59 _public member_ `EStreamType StreamType = EStreamType::Other;` — Type of elementary stream this request is for.
- L66 _public member_ `int32 QualityIndex = 0;` — The quality index of this stream. Zero indicates the "worst" (or only) quality. If this is the highest quality that is available this value will be the same as `MaxQualityIndex`.
- L73 _public member_ `int32 MaxQualityIndex = 0;` — The maximum quality index of this stream. Zero indicates this is the only available quality level. This can be used to cache only the highest quality stream, or any other.

#### struct `IElectraPlayerDataCache::FItemInfo::FRange`  
`struct FRange`  
_L13-34_
- L18 _public member_ `int64 Start = -1;` — Offset to the first byte in the resource.
- L25 _public member_ `int64 EndIncluding = -1;` — Offset to the last byte, including. A range of `Start` = 0, `EndIncluding` = 0 describes one byte at offset 0.
- L33 _public member_ `int64 TotalSize = -1;` — The total size of the resource. This _may_ be set when adding to the cache but is not required as there are cases where the total resource size is unknown. This does not describe the number of bytes between `Start` and `EndIncluding`, but the total size of the resource of which the range is a part of.

#### enum `IElectraPlayerDataCache::FItemInfo::EStreamType`  
`enum class EStreamType`  
_L36-41_
- L38 _public enumerator_ `Video`
- L39 _public enumerator_ `Audio`
- L40 _public enumerator_ `Other`

#### enum `IElectraPlayerDataCache::ECacheResult`  
`enum class ECacheResult`  
_L89-95_
- L92 _public enumerator_ `Miss` — Element not available in the cache.
- L94 _public enumerator_ `Hit` — Element available in the cache.

#### Free symbols / members of external scopes

- L97 _delegate_ `DECLARE_DELEGATE_ThreeParams(FCachedDataReadCompleted, ECacheResult , FItemInfo , FCacheDataPtr );`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/IElectraPlayerInterface.h` (Public)


#### class `IElectraSafeMediaOptionInterface`  
`class IElectraSafeMediaOptionInterface : public IMediaOptions::FDataContainer`  
_L39-69_
- inherits: `IMediaOptions::FDataContainer`
- desc: This class is used to get safe access to an IMediaOptions interface. When passing IMediaOptions through media framework as a POD pointer there is the risk that it is actually from a derived class like UMediaSource which is subject to GC. Thus it is not safe to keep the POD IMediaOptions around. This class is intended to be derived and instantiated from and stored as a TSharedPtr in a derived UMediaSource class. Then, as the media player is opened and the POD IMediaOptions is passed along, a GetMediaOption("GetSafeMediaOptions") query will be made on it to get this instance. If future access to the IMediaOptions is needed it will be made through this class by first locking, getting and using the IMediaOptions pointer returned here if it not null and unlocking afterwards.
- L42 _public prototype_ `virtual ~IElectraSafeMediaOptionInterface() = default;`
- L43 _public prototype_ `virtual void Lock() = 0;`
- L44 _public prototype_ `virtual void Unlock() = 0;`
- L45 _public prototype_ `virtual IMediaOptions* GetMediaOptionInterface() = 0;`

#### class `IElectraSafeMediaOptionInterface::FScopedLock`  
`class FScopedLock`  
_L47-68_
- L50 _public function_ `FScopedLock(const TSharedPtr<IElectraSafeMediaOptionInterface, ESPMode::ThreadSafe>& InSafeMediaOptionInterface) : SafeMediaOptionInterface(InSafeMediaOptionInterface)`
- L58 _public function_ `~FScopedLock()`
- L67 _private member_ `TSharedPtr<IElectraSafeMediaOptionInterface, ESPMode::ThreadSafe> SafeMediaOptionInterface;`

#### class `FElectraSafeMediaOptionInterface`  
`class FElectraSafeMediaOptionInterface : public IElectraSafeMediaOptionInterface`  
_L75-108_
- inherits: `IElectraSafeMediaOptionInterface`
- desc: A ready to use implementation of the IElectraSafeMediaOptionInterface
- L78 _public function_ `FElectraSafeMediaOptionInterface(IMediaOptions* InOwner) : Owner(InOwner) , OwnerObject(InOwner ? InOwner->ToUObject() : nullptr)`
- L82 _public function_ `virtual ~FElectraSafeMediaOptionInterface()`
- L86 _public function_ `void ClearOwner()`
- L92 _public function_ `virtual void Lock() override`
- L96 _public function_ `virtual void Unlock() override`
- L100 _public function_ `virtual IMediaOptions* GetMediaOptionInterface() override`
- L105 _private member_ `FCriticalSection OwnerLock;`
- L106 _private member_ `IMediaOptions* Owner = nullptr;`
- L107 _private member_ `FWeakObjectPtr OwnerObject;`

#### class `FElectraSeekablePositions`  
`class FElectraSeekablePositions : public IMediaOptions::FDataContainer`  
_L113-120_
- inherits: `IMediaOptions::FDataContainer`
- desc: Data type for use with media options interface
- L116 _public function_ `FElectraSeekablePositions(const TArray<FTimespan>& InData) : Data(InData)`
- L117 _public prototype_ `virtual ~FElectraSeekablePositions() = default;`
- L119 _public member_ `TArray<FTimespan> Data;`

#### class `FElectraPlayerRuntimeFactory`  
`class FElectraPlayerRuntimeFactory`  
_L123-131_
- L126 _public prototype_ `static TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& InEventSink, FElectraPlayerSendAnalyticMetricsDelegate& InSendAnalyticMetricsDelegate, FElectraPlayerSendAnalyticMetricsPerMinuteDelegate& InSendAnalyticMetricsPerMinuteDelegate, FElectraPlayerReportVideoStreamingErrorDelegate& InReportVideoStreamingErrorDelegate, FElectraPlayerReportSubtitlesMetricsDelegate& InReportSubtitlesFileMetricsDelegate);`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API ELECTRAPLAYERRUNTIME_API`
- L20 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FElectraPlayerSendAnalyticMetricsDelegate, const TSharedPtr<IAnalyticsProviderET>& , const FGuid& );`
- L20 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FElectraPlayerSendAnalyticMetricsDelegate, const TSharedPtr<IAnalyticsProviderET>& , const FGuid& );`
- L21 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FElectraPlayerSendAnalyticMetricsPerMinuteDelegate, const TSharedPtr<IAnalyticsProviderET>& );`
- L21 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FElectraPlayerSendAnalyticMetricsPerMinuteDelegate, const TSharedPtr<IAnalyticsProviderET>& );`
- L22 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FElectraPlayerReportVideoStreamingErrorDelegate, const FGuid& , const FString& );`
- L22 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FElectraPlayerReportVideoStreamingErrorDelegate, const FGuid& , const FString& );`
- L23 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_FourParams(FElectraPlayerReportSubtitlesMetricsDelegate, const FGuid& , const FString& , double , const FString& );`
- L23 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_FourParams(FElectraPlayerReportSubtitlesMetricsDelegate, const FGuid& , const FString& , double , const FString& );`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/IElectraPlayerRuntimeModule.h` (Public)


#### class `IElectraPlayerRuntimeModule`  
`class IElectraPlayerRuntimeModule : public IModuleInterface`  
_L11-23_
- inherits: `IModuleInterface`
- desc: Interface for the ElectraPlayerRuntime module.
- L20 _public prototype_ `virtual bool IsInitialized() const = 0;` — Is the ElectraPlayerRuntime module initialized? @return True if the module is initialized.
- L22 _public prototype_ `virtual ~IElectraPlayerRuntimeModule() = default;`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/Linux/ElectraPlayerResourceDelegate.h` (Public)


#### class `IElectraPlayerResourceDelegate`  
`class IElectraPlayerResourceDelegate`  
_L4-8_
- L7 _public prototype_ `virtual ~IElectraPlayerResourceDelegate() = default;`

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/Unix/ElectraPlayerResourceDelegate.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraPlayer/Source/ElectraPlayerRuntime/Public/Windows/ElectraPlayerResourceDelegate.h` (Public)


#### class `IElectraPlayerResourceDelegate`  
`class IElectraPlayerResourceDelegate`  
_L8-14_
- L11 _public prototype_ `virtual ~IElectraPlayerResourceDelegate() = default;`
- L13 _public prototype_ `virtual void ExecuteCodeWithCopyCommandQueueUsage(TFunction<void(ID3D12CommandQueue*)>&& CodeToRun) = 0;`
