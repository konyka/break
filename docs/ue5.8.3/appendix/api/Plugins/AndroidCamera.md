# Plugins / AndroidCamera

- module root: `Plugins/Media/AndroidCamera/Source/AndroidCamera`
- headers: 5; symbols: 278
- symbol kinds: class=5, delegate=1, enum=2, enumerator=5, function=35, member=138, prototype=87, struct=5
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: AndroidCameraFactory, Core, Engine, Launch, MediaUtils, RenderCore
- PrivateIncludePathModuleNames: Media

### `Plugins/Media/AndroidCamera/Source/AndroidCamera/Private/AndroidCameraPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidCamera, Log, All);` — Log category for the AndroidCamera module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidCamera, Log, All);` — Log category for the AndroidCamera module.

### `Plugins/Media/AndroidCamera/Source/AndroidCamera/Private/Player/AndroidCameraPlayer.h` (Private)


#### class `FAndroidCameraPlayer`  
`class FAndroidCameraPlayer : public IMediaPlayer , protected IMediaCache , protected IMediaControls , protected IMediaTracks , protected IMediaView , public TSharedFromThis<FAndroidCameraPlayer>`  
_L28-195_
- inherits: `IMediaPlayer,IMediaCache,IMediaControls,IMediaTracks,IMediaView,TSharedFromThis<FAndroidCameraPlayer>`
- desc: Implements media playback using the Android MediaPlayer interface.
- L43 _public prototype_ `FAndroidCameraPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L46 _public prototype_ `virtual ~FAndroidCameraPlayer();` — Virtual destructor.
- L52 _public prototype_ `virtual void Close() override;`
- L53 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L54 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L55 _public prototype_ `virtual FString GetInfo() const override;`
- L56 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L57 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L58 _public prototype_ `virtual FString GetStats() const override;`
- L59 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L60 _public prototype_ `virtual FString GetUrl() const override;`
- L61 _public prototype_ `virtual IMediaView& GetView() override;`
- L62 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L63 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L64 _public prototype_ `virtual void SetGuid(const FGuid& Guid) override;`
- L65 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L66 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L75 _protected prototype_ `bool InitializePlayer();` — Initialize the media player. @return true on success, false otherwise.
- L81 _protected prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L82 _protected prototype_ `virtual FTimespan GetDuration() const override;`
- L83 _protected prototype_ `virtual float GetRate() const override;`
- L84 _protected prototype_ `virtual EMediaState GetState() const override;`
- L85 _protected prototype_ `virtual EMediaStatus GetStatus() const override;`
- L86 _protected prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L87 _protected prototype_ `virtual FTimespan GetTime() const override;`
- L88 _protected prototype_ `virtual bool IsLooping() const override;`
- L89 _protected prototype_ `virtual bool Seek(const FTimespan& Time) override;`
- L90 _protected prototype_ `virtual bool SetLooping(bool Looping) override;`
- L91 _protected prototype_ `virtual bool SetRate(float Rate) override;`
- L97 _protected prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L98 _protected prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L99 _protected prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L100 _protected prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L101 _protected prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L102 _protected prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L103 _protected prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L104 _protected prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L105 _protected prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L106 _protected prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L107 _protected prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L108 _protected prototype_ `virtual bool SetVideoTrackFrameRate(int32 TrackIndex, int32 FormatIndex, float FrameRate) override;`
- L113 _private prototype_ `void HandleApplicationHasEnteredForeground();` — Callback for when the application resumed in the foreground.
- L116 _private prototype_ `void HandleApplicationWillEnterBackground();` — Callback for when the application is being paused in the background.
- L121 _private member_ `TArray<FJavaAndroidCameraPlayer::FAudioTrack> AudioTracks;` — Audio track descriptors.
- L124 _private member_ `TArray<FJavaAndroidCameraPlayer::FCaptionTrack> CaptionTracks;` — Caption track descriptors.
- L127 _private member_ `TArray<FJavaAndroidCameraPlayer::FVideoTrack> VideoTracks;` — Video track descriptors.
- L132 _private member_ `TAtomic<EMediaState> CurrentState;` — Current player state.
- L135 _private member_ `FTimespan CurrentTime;` — The current time of the playback.
- L138 _private member_ `bool bLooping;` — Current state of looping.
- L141 _private member_ `IMediaEventSink& EventSink;` — The media event handler.
- L144 _private member_ `FString Info;` — Media information string.
- L147 _private member_ `TSharedPtr<FJavaAndroidCameraPlayer, ESPMode::ThreadSafe> JavaCameraPlayer;` — The Java side media interface.
- L150 _private member_ `FString MediaUrl;` — Currently opened media.
- L153 _private member_ `FGuid PlayerGuid;` — Media player Guid
- L156 _private member_ `FDelegateHandle PauseHandle;` — Foreground/background delegate for pause.
- L159 _private member_ `FDelegateHandle ResumeHandle;` — Foreground/background delegate for resume.
- L162 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> Samples;` — The media sample queue.
- L165 _private member_ `int32 SelectedAudioTrack;` — Index of the selected audio track.
- L168 _private member_ `int32 SelectedCaptionTrack;` — Index of the selected audio track.
- L171 _private member_ `int32 SelectedVideoTrack;` — Index of the selected video track.
- L174 _private member_ `FAndroidCameraTextureSamplePool* VideoSamplePool;` — Video sample object pool.
- L177 _private member_ `bool bOpenWithoutEvents;` — Whether or not the current open request should send events on completion.
- L180 _private member_ `bool IsInBackground;` — Identify the game is in background
- L190 _private member_ `pthread_t DeferredSetRateThread;` — The thread of delaying the SetRate until the camera is prepared
- L191 _private member_ `TAtomic<bool> IsSetRateThreadRunning;`
- L194 _private member_ `TAtomic<bool> StopSetRateThread;` — The flag for exiting the SetRate thread

#### struct `FAndroidCameraPlayer::SetRateThreadArg`  
`struct SetRateThreadArg`  
_L184-187_
- desc: The struct to pass a shared pointer of this object to DeferredSetRateThread
- L186 _public member_ `TSharedPtr<FAndroidCameraPlayer> ThisPtr;`

### `Plugins/Media/AndroidCamera/Source/AndroidCamera/Private/Player/AndroidCameraTextureSample.h` (Private)


#### class `FAndroidCameraTextureSample`  
`class FAndroidCameraTextureSample : public IMediaTextureSample , public IMediaTextureSampleConverter , public IMediaPoolable`  
_L29-452_
- inherits: `IMediaTextureSample,IMediaTextureSampleConverter,IMediaPoolable`
- desc: Texture sample generated by AndroidCamera player.
- L37 _public function_ `FAndroidCameraTextureSample() : Buffer(nullptr) , BufferSize(0) , Dim(FIntPoint::ZeroValue) , Duration(FTimespan::Zero()) , Time(FTimespan::Zero()) , ScaleRotation(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)) , Offset(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f))` — Default constructor.
- L48 _public function_ `virtual ~FAndroidCameraTextureSample()` — Virtual destructor.
- L60 _public function_ `void* GetMutableBuffer()` — Get a writable pointer to the sample buffer. @return Sample buffer.
- L72 _public function_ `bool Initialize(const FIntPoint& InDim, FTimespan InDuration)` — Initialize the sample. @param InDim The sample buffer's width and height (in pixels). @param InDuration The duration for which the sample is valid. @return true on success, false otherwise.
- L88 _public function_ `void InitializeExternalTexture(FTimespan InTime)` — Initialize the sample as an external image reference.
- L102 _public function_ `void InitializeBuffer(void* InBuffer, FTimespan InTime, bool Copy)` — Initialize the sample with a memory buffer. @param InBuffer The buffer containing the sample data. @param InTime The sample time (in the player's local clock). @param Copy Whether the buffer should be copied (true) or referenced (false). @see InitializeTexture
- L147 _public function_ `FRHITexture* InitializeTexture(FRHICommandListBase& RHICmdList, FTimespan InTime)` — Initialize the sample with a texture resource. @param RHICmdList the command list used to create the texture. @param InTime The sample time (in the player's local clock). @return The texture resource object that will hold the sample data. @note This method must be called on the render thread. @see InitializeBuffer
- L178 _public function_ `void InitializeMediaFrameData(jobject InFrameData, FTimespan InTime)` — Initialize the sample with a hardware buffer extract from MediaFrameData. @param InFrameData holds the jobject of the sample data. @param InTime The sample time (in the player's local clock). @note This method must be called on the render thread. @see InitializeBuffer, InitializeTexture
- L191 _public function_ `void SetScaleRotationOffset(FVector4& InScaleRotation, FVector4& InOffset)` — Set the sample Scale, Rotation, Offset. @param InScaleRotation The sample scale and rotation transform (2x2). @param InOffset The sample offset.
- L201 _public function_ `virtual const void* GetBuffer() override`
- L206 _public function_ `virtual FIntPoint GetDim() const override`
- L211 _public function_ `virtual FTimespan GetDuration() const override`
- L216 _public function_ `virtual EMediaTextureSampleFormat GetFormat() const override`
- L221 _public function_ `virtual FIntPoint GetOutputDim() const override`
- L226 _public function_ `virtual uint32 GetStride() const override`
- L233 _public function_ `virtual FRHITexture* GetTexture() const override`
- L240 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L245 _public function_ `virtual bool IsExternalImage() const override`
- L250 _public function_ `virtual bool IsCacheable() const override`
- L259 _public function_ `virtual bool IsOutputSrgb() const override`
- L264 _public function_ `virtual FLinearColor GetScaleRotation() const override`
- L269 _public function_ `virtual FLinearColor GetOffset() const override`
- L274 _public function_ `virtual EMediaOrientation GetOrientation() const override`
- L280 _public function_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override`
- L291 _public function_ `virtual bool IsReadyForReuse() override`
- L300 _public function_ `virtual void ShutdownPoolable() override`
- L317 _private function_ `bool RotateBinaryBufferTexture(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints)`
- L394 _private function_ `virtual bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) override`
- L420 _private member_ `FAndroidJavaMediaFrameData MediaFrameData;` — The sample's frame data from the java surface provider.
- L423 _private member_ `void* Buffer;` — The sample's data buffer.
- L426 _private member_ `SIZE_T BufferSize;` — Current allocation size of Buffer.
- L429 _private member_ `bool ExternalTexture;` — Flag indicating if this is an external image reference.
- L432 _private member_ `FIntPoint Dim;` — Width and height of the texture sample.
- L435 _private member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L438 _private member_ `FTimespan Time;` — Sample time.
- L441 _private member_ `FLinearColor ScaleRotation;` — ScaleRotation for the sample.
- L444 _private member_ `FLinearColor Offset;` — Offset for the sample.
- L449 _private member_ `TRefCountPtr<FRHITexture> Texture;` — Texture resource.

#### class `FAndroidCameraTextureSamplePool`  
`class FAndroidCameraTextureSamplePool : public TMediaObjectPool<FAndroidCameraTextureSample>`  
_L456-456_
- inherits: `TMediaObjectPool<FAndroidCameraTextureSample>`
- desc: Implements a pool for Android texture sample objects.

### `Plugins/Media/AndroidCamera/Source/AndroidCamera/Public/AndroidJavaCameraPlayer.h` (Public)


#### class `FJavaAndroidCameraPlayer`  
`class FJavaAndroidCameraPlayer : public FJavaClassObject`  
_L11-234_
- inherits: `FJavaClassObject`
- desc: Wrapper for com/epicgames/unreal/CameraPlayer*.java.
- L63 _public prototype_ `FJavaAndroidCameraPlayer(bool swizzlePixels, bool vulkanRenderer);`
- L64 _public prototype_ `virtual ~FJavaAndroidCameraPlayer();`
- L65 _public prototype_ `int32 GetDuration();`
- L66 _public prototype_ `bool IsActive();`
- L67 _public prototype_ `void Reset();`
- L68 _public prototype_ `void Stop();`
- L69 _public prototype_ `int32 GetCurrentPosition();`
- L70 _public prototype_ `bool IsLooping();`
- L71 _public prototype_ `bool IsPlaying();`
- L72 _public prototype_ `bool IsPrepared();`
- L73 _public prototype_ `bool DidComplete();`
- L74 _public prototype_ `bool SetDataSource(const FString & Url);`
- L75 _public prototype_ `FString GetDataSource();`
- L76 _public prototype_ `bool Prepare();`
- L77 _public prototype_ `bool PrepareAsync();`
- L78 _public prototype_ `void SeekTo(int32 Milliseconds);`
- L79 _public prototype_ `void SetLooping(bool Looping);`
- L80 _public prototype_ `bool RestoreCamera();`
- L81 _public prototype_ `void Release();`
- L82 _public prototype_ `int32 GetVideoHeight();`
- L83 _public prototype_ `int32 GetVideoWidth();`
- L84 _public prototype_ `float GetFrameRate();`
- L85 _public prototype_ `void SetVideoEnabled(bool enabled = true);`
- L86 _public prototype_ `void SetAudioEnabled(bool enabled = true);`
- L87 _public prototype_ `bool IsUsingBitmapRendererImageReader();`
- L88 _public prototype_ `jobject GetVideoLastMediaFrameData(int32& CurrentPosition, bool& bRegionChanged);`
- L89 _public prototype_ `bool GetVideoLastFrameData(void* & outPixels, int64 & outCount, int32 *CurrentPosition, bool *bRegionChanged);`
- L90 _public prototype_ `void Start();`
- L91 _public prototype_ `void Pause();`
- L92 _public prototype_ `bool GetVideoLastFrame(int32 destTexture);`
- L93 _public prototype_ `bool SelectTrack(int32 index);`
- L94 _public prototype_ `bool GetAudioTracks(TArray<FAudioTrack>& AudioTracks);`
- L95 _public prototype_ `bool GetCaptionTracks(TArray<FCaptionTrack>& CaptionTracks);`
- L96 _public prototype_ `bool GetVideoTracks(TArray<FVideoTrack>& VideoTracks);`
- L97 _public prototype_ `bool DidResolutionChange();`
- L98 _public prototype_ `int32 GetExternalTextureId();`
- L99 _public prototype_ `bool UpdateVideoFrame(int32 ExternalTextureId, int32 *CurrentPosition, bool *bRegionChanged);`
- L100 _public prototype_ `bool TakePicture(const FString& Filename);`
- L101 _public prototype_ `bool TakePicture(const FString& Filename, int32 Width, int32 Height);`
- L104 _private prototype_ `static FName GetClassName();`
- L106 _private member_ `FPlayerState PlayerState;`
- L108 _private member_ `bool bTrackInfoSupported;`
- L110 _private member_ `FJavaClassMethod GetDurationMethod;`
- L111 _private member_ `FJavaClassMethod ResetMethod;`
- L112 _private member_ `FJavaClassMethod StopMethod;`
- L113 _private member_ `FJavaClassMethod GetCurrentPositionMethod;`
- L114 _private member_ `FJavaClassMethod IsLoopingMethod;`
- L115 _private member_ `FJavaClassMethod IsPlayingMethod;`
- L116 _private member_ `FJavaClassMethod IsPreparedMethod;`
- L117 _private member_ `FJavaClassMethod DidCompleteMethod;`
- L118 _private member_ `FJavaClassMethod SetDataSourceURLMethod;`
- L119 _private member_ `FJavaClassMethod GetDataSourceURLMethod;`
- L120 _private member_ `FJavaClassMethod PrepareMethod;`
- L121 _private member_ `FJavaClassMethod PrepareAsyncMethod;`
- L122 _private member_ `FJavaClassMethod SeekToMethod;`
- L123 _private member_ `FJavaClassMethod SetLoopingMethod;`
- L124 _private member_ `FJavaClassMethod OpenCameraMethod;`
- L125 _private member_ `FJavaClassMethod ReleaseMethod;`
- L126 _private member_ `FJavaClassMethod GetVideoHeightMethod;`
- L127 _private member_ `FJavaClassMethod GetVideoWidthMethod;`
- L128 _private member_ `FJavaClassMethod GetFrameRateMethod;`
- L129 _private member_ `FJavaClassMethod SetVideoEnabledMethod;`
- L130 _private member_ `FJavaClassMethod SetAudioEnabledMethod;`
- L131 _private member_ `FJavaClassMethod GetVideoLastFrameDataMethod;`
- L132 _private member_ `FJavaClassMethod StartMethod;`
- L133 _private member_ `FJavaClassMethod PauseMethod;`
- L134 _private member_ `FJavaClassMethod GetVideoLastFrameMethod;`
- L135 _private member_ `FJavaClassMethod SelectTrackMethod;`
- L136 _private member_ `FJavaClassMethod GetAudioTracksMethod;`
- L137 _private member_ `FJavaClassMethod GetCaptionTracksMethod;`
- L138 _private member_ `FJavaClassMethod GetVideoTracksMethod;`
- L139 _private member_ `FJavaClassMethod DidResolutionChangeMethod;`
- L140 _private member_ `FJavaClassMethod GetExternalTextureIdMethod;`
- L141 _private member_ `FJavaClassMethod UpdateVideoFrameMethod;`
- L142 _private member_ `FJavaClassMethod TakePictureMethod;`
- L145 _private member_ `FJavaClassMethod SetUsingBitmapRendererImageReaderMethod;` — interfaces of getting video frame data through ImageReader
- L146 _private member_ `FJavaClassMethod GetVideoLastMediaFrameDataMethod;`
- L149 _private member_ `jclass FrameUpdateInfoClass;` — FrameUpdateInfo member field ids
- L150 _private member_ `jfieldID FrameUpdateInfo_Buffer;`
- L151 _private member_ `jfieldID FrameUpdateInfo_CurrentPosition;`
- L152 _private member_ `jfieldID FrameUpdateInfo_FrameReady;`
- L153 _private member_ `jfieldID FrameUpdateInfo_RegionChanged;`
- L154 _private member_ `jfieldID FrameUpdateInfo_ScaleRotation00;`
- L155 _private member_ `jfieldID FrameUpdateInfo_ScaleRotation01;`
- L156 _private member_ `jfieldID FrameUpdateInfo_ScaleRotation10;`
- L157 _private member_ `jfieldID FrameUpdateInfo_ScaleRotation11;`
- L158 _private member_ `jfieldID FrameUpdateInfo_UOffset;`
- L159 _private member_ `jfieldID FrameUpdateInfo_VOffset;`
- L160 _private member_ `jfieldID FrameUpdateInfo_BRFrameData;`
- L163 _private member_ `jclass AudioTrackInfoClass;` — AudioDeviceInfo member field ids
- L164 _private member_ `jfieldID AudioTrackInfo_Index;`
- L165 _private member_ `jfieldID AudioTrackInfo_MimeType;`
- L166 _private member_ `jfieldID AudioTrackInfo_DisplayName;`
- L167 _private member_ `jfieldID AudioTrackInfo_Language;`
- L168 _private member_ `jfieldID AudioTrackInfo_Channels;`
- L169 _private member_ `jfieldID AudioTrackInfo_SampleRate;`
- L172 _private member_ `jclass CaptionTrackInfoClass;` — AudioDeviceInfo member field ids
- L173 _private member_ `jfieldID CaptionTrackInfo_Index;`
- L174 _private member_ `jfieldID CaptionTrackInfo_MimeType;`
- L175 _private member_ `jfieldID CaptionTrackInfo_DisplayName;`
- L176 _private member_ `jfieldID CaptionTrackInfo_Language;`
- L179 _private member_ `jclass VideoTrackInfoClass;` — AudioDeviceInfo member field ids
- L180 _private member_ `jfieldID VideoTrackInfo_Index;`
- L181 _private member_ `jfieldID VideoTrackInfo_MimeType;`
- L182 _private member_ `jfieldID VideoTrackInfo_DisplayName;`
- L183 _private member_ `jfieldID VideoTrackInfo_Language;`
- L184 _private member_ `jfieldID VideoTrackInfo_BitRate;`
- L185 _private member_ `jfieldID VideoTrackInfo_Width;`
- L186 _private member_ `jfieldID VideoTrackInfo_Height;`
- L187 _private member_ `jfieldID VideoTrackInfo_FrameRate;`
- L188 _private member_ `jfieldID VideoTrackInfo_FrameRateLow;`
- L189 _private member_ `jfieldID VideoTrackInfo_FrameRateHigh;`
- L191 _private member_ `FTextureRHIRef VideoTexture;`
- L192 _private member_ `bool bVideoTextureValid;`
- L194 _private member_ `FVector4 ScaleRotation;`
- L195 _private member_ `FVector4 Offset;`
- L204 _private member_ `BitmapRendererSelection BRSelection;` — BR - BitmapRenderer
- L205 _private member_ `bool UsingVulkanRenderer;`
- L207 _private prototype_ `void SelectBitmapRenderer();`
- L208 _private prototype_ `void UpdateScaleRotationOffset();`
- L211 _public function_ `FTextureRHIRef GetVideoTexture()`
- L216 _public function_ `void SetVideoTexture(FTextureRHIRef Texture)`
- L221 _public function_ `void SetVideoTextureValid(bool Condition)`
- L226 _public function_ `bool IsVideoTextureValid()`
- L231 _public function_ `FVector4 GetScaleRotation()`
- L233 _public function_ `FVector4 GetOffset()`

#### enum `FJavaAndroidCameraPlayer::FPlayerState`  
`enum FPlayerState`  
_L14-18_
- L16 _public enumerator_ `Inactive`
- L17 _public enumerator_ `Active`

#### struct `FJavaAndroidCameraPlayer::FAudioTrack`  
`struct FAudioTrack`  
_L20-29_
- L22 _public member_ `int32 Index;`
- L23 _public member_ `FString MimeType;`
- L24 _public member_ `FString DisplayName;`
- L25 _public member_ `FString Language;`
- L26 _public member_ `FString Name;`
- L27 _public member_ `uint32 Channels;`
- L28 _public member_ `uint32 SampleRate;`

#### struct `FJavaAndroidCameraPlayer::FCaptionTrack`  
`struct FCaptionTrack`  
_L31-38_
- L33 _public member_ `int32 Index;`
- L34 _public member_ `FString MimeType;`
- L35 _public member_ `FString DisplayName;`
- L36 _public member_ `FString Language;`
- L37 _public member_ `FString Name;`

#### struct `FJavaAndroidCameraPlayer::FVideoFormat`  
`struct FVideoFormat`  
_L40-45_
- L42 _public member_ `FIntPoint Dimensions;`
- L43 _public member_ `float FrameRate;`
- L44 _public member_ `TRange<float> FrameRates;`

#### struct `FJavaAndroidCameraPlayer::FVideoTrack`  
`struct FVideoTrack`  
_L47-60_
- L49 _public member_ `int32 Index;`
- L50 _public member_ `FString MimeType;`
- L51 _public member_ `FString DisplayName;`
- L52 _public member_ `FString Language;`
- L53 _public member_ `FString Name;`
- L54 _public member_ `uint32 BitRate;`
- L55 _public member_ `FIntPoint Dimensions;`
- L56 _public member_ `float FrameRate;`
- L57 _public member_ `TRange<float> FrameRates;`
- L58 _public member_ `int32 Format;`
- L59 _public member_ `TArray<FVideoFormat> Formats;`

#### enum `FJavaAndroidCameraPlayer::BitmapRendererSelection`  
`enum BitmapRendererSelection`  
_L197-202_
- L199 _public enumerator_ `Unknown`
- L200 _public enumerator_ `Legacy`
- L201 _public enumerator_ `ImageReader`

### `Plugins/Media/AndroidCamera/Source/AndroidCamera/Public/IAndroidCameraModule.h` (Public)


#### class `IAndroidCameraModule`  
`class IAndroidCameraModule : public IModuleInterface`  
_L15-32_
- inherits: `IModuleInterface`
- desc: Interface for the AndroidCamera module.
- L26 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create a Android based camera player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L31 _public function_ `virtual ~IAndroidCameraModule()` — Virtual destructor.
