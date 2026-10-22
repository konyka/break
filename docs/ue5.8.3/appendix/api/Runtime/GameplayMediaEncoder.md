# Runtime / GameplayMediaEncoder

- module root: `Source/Runtime/GameplayMediaEncoder`
- headers: 3; symbols: 157
- symbol kinds: class=3, delegate=2, enum=1, enumerator=6, externvar=1, function=9, macro=2, member=58, prototype=68, struct=6, typedef=1
- PrivateDependencyModuleNames: AVEncoder, ApplicationCore, Core, CoreUObject, Engine, HTTP, Json, RHI, RenderCore, Slate, SlateCore

### `Source/Runtime/GameplayMediaEncoder/Private/GameplayMediaEncoderCommon.h` (Private)


#### struct `FMemoryCheckpoint`  
`struct FMemoryCheckpoint`  
_L37-43_
- L39 _public member_ `FString Name;`
- L40 _public member_ `float UsedPhysicalMB;`
- L41 _public member_ `float DeltaMB;`
- L42 _public member_ `float AccumulatedMB;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define LIVESTREAMING 0` — Macros to control some things during development
- L32 _macro_ `#define WMFMEDIA_SUPPORTED_PLATFORM (PLATFORM_WINDOWS && (WINVER >= 0x0600 /*Vista*/) && !UE_SERVER)`
- L35 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(GameplayMediaEncoder, Log, VeryVerbose);`
- L35 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(GameplayMediaEncoder, Log, VeryVerbose);`
- L44 _externvar_ `extern TArray<FMemoryCheckpoint> gMemoryCheckpoints;`
- L45 _prototype_ `uint64 MemoryCheckpoint(const FString& Name);`
- L46 _prototype_ `void LogMemoryCheckpoints(const FString& Name);`

### `Source/Runtime/GameplayMediaEncoder/Private/IbmLiveStreaming.h` (Private)


#### class `FIbmLiveStreaming`  
`class FIbmLiveStreaming final : private IGameplayMediaEncoderListener`  
_L29-209_
- inherits: `IGameplayMediaEncoderListener`
- L32 _public typedef_ `using FBandwidthProbeCallback = TFunction<void(uint32, bool)>;`
- L34 _public prototype_ `FIbmLiveStreaming();`
- L35 _public prototype_ `~FIbmLiveStreaming();`
- L37 _public prototype_ `static FIbmLiveStreaming* Get();`
- L42 _public prototype_ `bool Start();` — Starts streaming, using best guess settings
- L46 _public prototype_ `bool Start(const FString& ClientId, const FString& ClientSecret, const FString& Channel, uint32 AudioSampleRate, uint32 AudioNumChannels, uint32 AudioBitrate);` — Starts streaming, using explicit settings
- L50 _public prototype_ `void Stop();` — Stops streaming
- L52 _public function_ `static void StartCmd()`
- L58 _public function_ `static void StopCmd()`
- L120 _private prototype_ `void OnMediaSample(const FGameplayMediaEncoderSample& Sample) override;` — IGameplayMediaEncoderListener interface
- L128 _private prototype_ `void OnProcessRequestComplete(FHttpRequestPtr SourceHttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);` — Callback from HTTP library when a request has completed @param HttpRequest The request object @param HttpResponse The response from the server @param bSucceeded Whether a response was successfully received
- L130 _private prototype_ `static bool GetJsonField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FString& DestStr);`
- L131 _private prototype_ `static bool GetJsonField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, const TSharedPtr<FJsonObject>*& DestObj);`
- L133 _private prototype_ `void Connect();`
- L137 _private prototype_ `void FinishStopOnGameThread();` — Called to finalize a previous call to `Stop()`.  This is called once the IBM library tells us the stream stopped and was deleted
- L138 _private prototype_ `void StopFromSocketThread();`
- L143 _private prototype_ `static void OnConnectionError(RTMPModuleConnect* Module, RTMPEvent Evt, void* RejectInfoObj);` — Callbacks for IBM RTMP C Ingest
- L144 _private prototype_ `static void OnConnectionSuccess(RTMPModuleConnect* Module);`
- L145 _private prototype_ `static void OnStreamPublished(RTMPModuleBroadcaster* Module);`
- L146 _private prototype_ `static void OnStreamDeleted(RTMPModuleBroadcaster* Module);`
- L147 _private prototype_ `static void OnStreamError(RTMPModuleBroadcaster* Module);`
- L148 _private prototype_ `static void OnStopPublish(RTMPModuleBroadcaster* Module);`
- L149 _private prototype_ `static void OnStreamBandwidthChanged(RTMPModuleBroadcaster* Module, unsigned long Bandwidth, int32 QueueWasEmpty);`
- L150 _private prototype_ `void OnConnectionErrorImpl(RTMPModuleConnect* Module, RTMPEvent Evt, void* RejectInfoObj);`
- L151 _private prototype_ `void OnConnectionSuccessImpl(RTMPModuleConnect* Module);`
- L152 _private prototype_ `void OnStreamPublishedImpl(RTMPModuleBroadcaster* Module);`
- L153 _private prototype_ `void OnStreamDeletedImpl(RTMPModuleBroadcaster* Module);`
- L154 _private prototype_ `void OnStreamErrorImpl(RTMPModuleBroadcaster* Module);`
- L155 _private prototype_ `void OnStopPublishImpl(RTMPModuleBroadcaster* Module);`
- L156 _private prototype_ `void OnStreamBandwidthChangedImpl(RTMPModuleBroadcaster* Module, uint32 Bandwidth, bool bQueueWasEmpty);`
- L158 _private prototype_ `static RawData* GetAvccHeader(const TArrayView<uint8>& DataView, const uint8** OutPpsEnd);`
- L159 _private prototype_ `static RawData* GetVideoPacket(const TArrayView<uint8>& Data, bool bVideoKeyframe, const uint8* DataBegin);`
- L161 _private prototype_ `void InjectVideo(uint32 TimestampMs, const TArrayView<uint8>& DataView, bool bIsKeyFrame);`
- L162 _private prototype_ `void InjectAudio(uint32 TimestampMs, const TArrayView<uint8>& DataView);`
- L165 _private function_ `template<typename T> static const uint8* Bytes(T& t)`
- L171 _private prototype_ `static void CustomLogMsg(const char* Msg);` — Custom log function for the IBM librayr
- L174 _private prototype_ `bool CheckState(const wchar_t* FuncName, EState ExpectedState);` — Utility functions to log an error if we are in the wrong state
- L175 _private prototype_ `bool CheckState(const wchar_t* FuncName, EState ExpectedStateMin, EState ExpectedStateMax);`
- L177 _private member_ `static FIbmLiveStreaming* Singleton;`
- L188 _private member_ `} Config;`
- L190 _private member_ `FIngest Ingest;`
- L192 _private member_ `TAtomic<EState> State = EState::None;`
- L193 _private member_ `TAtomic<uint32> AudioPacketsSent = 0;`
- L194 _private member_ `TAtomic<uint32> VideoPacketsSent = 0;`
- L195 _private member_ `FTimespan LiveStreamStartTimespan;`
- L196 _private member_ `uint32 FpsCalculationStartVideoPackets = 0;`
- L197 _private member_ `double FpsCalculationStartTime = 0;`
- L204 _private member_ `} Ctx;`
- L205 _private member_ `FCriticalSection CtxMutex;`
- L208 _private prototype_ `void QueueFrame(RTMPContentType FrameType, RawData* Pkt, uint32 TimestampMs);` — Helper function that locks Ctx and make the IBM call

#### enum `FIbmLiveStreaming::EState`  
`enum class EState`  
_L67-75_
- L69 _public enumerator_ `None`
- L70 _public enumerator_ `GettingAccessToken` — See https://developers.video.ibm.com/channel-api/getting-started.html#token-endpoint_8
- L71 _public enumerator_ `GettingIngestSettings` — See https://developers.video.ibm.com/channel-api/channel.html#ingest-settings_77
- L72 _public enumerator_ `Connecting`
- L73 _public enumerator_ `Connected`
- L74 _public enumerator_ `Stopping`

#### struct `FIbmLiveStreaming::FRtmpUrl`  
`struct FRtmpUrl`  
_L77-85_
- L79 _public member_ `FString Host;`
- L80 _public member_ `FString Application;`
- L81 _public member_ `FString Channel;`
- L82 _public member_ `FString ApplicationName;`
- L83 _public member_ `FString StreamName;`
- L84 _public member_ `FString StreamNamePrefix;`

#### struct `FIbmLiveStreaming::FIngest`  
`struct FIngest`  
_L87-91_
- L89 _public member_ `FString StreamingKey;`
- L90 _public member_ `FRtmpUrl RtmpUrl;`

#### struct `FIbmLiveStreaming::FFormData`  
`struct FFormData`  
_L93-117_
- L96 _public prototype_ `FFormData();`
- L97 _public prototype_ `void AddField(const FString& Name, const FString& Value);`
- L101 _public function_ `template<typename T1, typename T2> TSharedRef<IHttpRequest> CreateHttpPostRequest(const FString& URL, T1&& TargetObj, T2&& TargetObjHandler)` — Call this in the end, to generate the HttpRequest
- L109 _private prototype_ `static TArray<uint8> FStringToUint8(const FString& InString);`
- L111 _private member_ `FString BoundaryLabel;`
- L112 _private member_ `FString BoundaryBegin;`
- L113 _private member_ `FString BoundaryEnd;`
- L114 _private member_ `FString Data;`
- L116 _private prototype_ `TSharedRef<IHttpRequest> CreateHttpPostRequestImpl(const FString& URL);`

#### struct `FIbmLiveStreaming::(anonymous)`  
``  
_L181-188_

#### struct `FIbmLiveStreaming::(anonymous)`  
``  
_L200-204_

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(IbmLiveStreaming, Log, All);`
- L27 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(IbmLiveStreaming, Log, All);`
- L182 _member_ `FString ClientId;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0108`)
- L183 _member_ `FString ClientSecret;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0108`)
- L184 _member_ `FString Channel;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0108`)
- L185 _member_ `uint32 AudioSampleRate;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0108`)
- L186 _member_ `uint32 AudioNumChannels;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0108`)
- L187 _member_ `uint32 AudioBitrate;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0108`)
- L201 _member_ `RTMPClient* Client = nullptr;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0208`)
- L202 _member_ `RTMPModuleBroadcaster* BroadcasterModule = nullptr;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0208`)
- L203 _member_ `RTMPModuleConnect* ConnectModule = nullptr;` (scope `FIbmLiveStreaming::__anonfb5ab4ba0208`)

### `Source/Runtime/GameplayMediaEncoder/Public/GameplayMediaEncoder.h` (Public)


#### class `IGameplayMediaEncoderListener`  
`class IGameplayMediaEncoderListener`  
_L33-39_
- L37 _public prototype_ `virtual void OnMediaSample(const AVEncoder::FMediaPacket& Sample) = 0;`

#### class `FGameplayMediaEncoder`  
`class UE_DEPRECATED(5.4, "GameplayMediaEncoder will move to a plugin in a future Unreal Engine release.") FGameplayMediaEncoder final : public ISubmixBufferListener, public AVEncoder::IAudioEncoderListener PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L42-175_
- inherits: `ISubmixBufferListener,AVEncoder::IAudioEncoderListenerPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L50 _public prototype_ `static FGameplayMediaEncoder* Get();` — Get the singleton
- L52 _public prototype_ `~FGameplayMediaEncoder();`
- L54 _public prototype_ `bool RegisterListener(IGameplayMediaEncoderListener* Listener);`
- L55 _public prototype_ `void UnregisterListener(IGameplayMediaEncoderListener* Listener);`
- L57 _public prototype_ `void SetVideoBitrate(uint32 Bitrate);`
- L58 _public prototype_ `void SetVideoFramerate(uint32 Framerate);`
- L66 _public prototype_ `bool Initialize();`
- L67 _public prototype_ `void Shutdown();`
- L68 _public prototype_ `bool Start();`
- L69 _public prototype_ `void Stop();`
- L71 _public function_ `static void InitializeCmd()`
- L77 _public function_ `static void ShutdownCmd()`
- L83 _public function_ `static void StartCmd()`
- L89 _public function_ `static void StopCmd()`
- L96 _public prototype_ `AVEncoder::FAudioConfig GetAudioConfig() const;`
- L97 _public function_ `AVEncoder::FVideoConfig GetVideoConfig() const`
- L105 _private prototype_ `FGameplayMediaEncoder();` — Private to control how our single instance is created
- L108 _private prototype_ `FTimespan GetMediaTimestamp() const;` — Returns how long it has been recording for.
- L111 _private prototype_ `void OnFrameBufferReady(SWindow& SlateWindow, ISlateViewportProvider& ViewportProvider);` — Back buffer capture
- L114 _private prototype_ `const FString& GetListenerName() const override;` — ISubmixBufferListener interface
- L115 _private prototype_ `void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 NumSamples, int32 NumChannels, const int32 SampleRate, double AudioClock) override;`
- L117 _private prototype_ `void ProcessAudioFrame(const float* AudioData, int32 NumSamples, int32 NumChannels, int32 SampleRate);`
- L118 _private prototype_ `void ProcessVideoFrame(const FTextureRHIRef& FrameBuffer);`
- L120 _private prototype_ `void UpdateVideoConfig();`
- L123 _private prototype_ `void OnEncodedAudioFrame(const AVEncoder::FMediaPacket& Packet) override;`
- L124 _private prototype_ `void OnEncodedVideoFrame(uint32 LayerIndex, const TSharedPtr<AVEncoder::FVideoEncoderInputFrame> Frame, const AVEncoder::FCodecPacket& Packet);`
- L126 _private prototype_ `TSharedPtr<AVEncoder::FVideoEncoderInputFrame> ObtainInputFrame();`
- L128 _private prototype_ `void CopyTexture(const FTextureRHIRef& SourceTexture, FTextureRHIRef& DestinationTexture) const;`
- L130 _private prototype_ `void FloatToPCM16(float const* floatSamples, int32 numSamples, TArray<int16>& out) const;`
- L132 _private member_ `FCriticalSection ListenersCS;`
- L133 _private member_ `TArray<IGameplayMediaEncoderListener*> Listeners;`
- L135 _private member_ `FCriticalSection AudioProcessingCS;`
- L136 _private member_ `FCriticalSection VideoProcessingCS;`
- L139 _private member_ `TUniquePtr<AVEncoder::FAudioEncoder> AudioEncoder;`
- L141 _private member_ `AVEncoder::FVideoConfig VideoConfig;`
- L143 _private member_ `TUniquePtr<AVEncoder::FVideoEncoder> VideoEncoder;`
- L144 _private member_ `TSharedPtr<AVEncoder::FVideoEncoderInput> VideoEncoderInput;`
- L147 _private member_ `uint64 NumCapturedFrames = 0;`
- L148 _private member_ `FTimespan StartTime = 0;`
- L153 _private member_ `double AudioClock = 0;` — Instead of using the AudioClock parameter ISubmixBufferListener::OnNewSubmixBuffer gives us, we calculate our own, by advancing it as we receive more data. This is so that we can adjust the clock if things get out of sync, such as if we break into the debugger.
- L155 _private member_ `FTimespan LastVideoInputTimestamp = 0;`
- L157 _private member_ `bool bAudioFormatChecked = false;`
- L158 _private member_ `bool bDoFrameSkipping = false;`
- L161 _private member_ `static TSharedPtr<FGameplayMediaEncoder, ESPMode::ThreadSafe> Singleton;`
- L164 _private member_ `TAtomic<uint32> NewVideoBitrate{ 0 };` — live streaming: quality adaptation to available uplink b/w
- L165 _private member_ `FThreadSafeBool bChangeBitrate = false;`
- L166 _private member_ `TAtomic<uint32> NewVideoFramerate{ 0 };`
- L167 _private member_ `FThreadSafeBool bChangeFramerate = false;`
- L169 _private member_ `TArray<int16> PCM16;`
- L171 _private member_ `TMap<TSharedPtr<AVEncoder::FVideoEncoderInputFrame>, FTextureRHIRef> BackBuffers;`
- L174 _private member_ `bool bIsInDestructor = false;`
