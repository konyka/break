# Plugins / AndroidMedia

- module root: `Plugins/Media/AndroidMedia/Source/AndroidMedia`
- headers: 4; symbols: 106
- symbol kinds: class=4, delegate=1, function=27, member=28, prototype=46
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: AndroidMediaFactory, Core, Engine, MediaUtils, RenderCore
- PrivateIncludePathModuleNames: Media

### `Plugins/Media/AndroidMedia/Source/AndroidMedia/Private/AndroidMediaPrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidMedia, Log, All);` — Log category for the AndroidMedia module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAndroidMedia, Log, All);` — Log category for the AndroidMedia module.

### `Plugins/Media/AndroidMedia/Source/AndroidMedia/Private/Player/AndroidMediaPlayer.h` (Private)


#### class `FAndroidMediaPlayer`  
`class FAndroidMediaPlayer : public IMediaPlayer , protected IMediaCache , protected IMediaControls , protected IMediaTracks , protected IMediaView`  
_L27-173_
- inherits: `IMediaPlayer,IMediaCache,IMediaControls,IMediaTracks,IMediaView`
- desc: Implements media playback using the Android MediaPlayer interface.
- L41 _public prototype_ `FAndroidMediaPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L44 _public prototype_ `virtual ~FAndroidMediaPlayer();` — Virtual destructor.
- L50 _public prototype_ `virtual void Close() override;`
- L51 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L52 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L53 _public prototype_ `virtual FString GetInfo() const override;`
- L54 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L55 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L56 _public prototype_ `virtual FString GetStats() const override;`
- L57 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L58 _public prototype_ `virtual FString GetUrl() const override;`
- L59 _public prototype_ `virtual IMediaView& GetView() override;`
- L60 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L61 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L62 _public prototype_ `virtual void SetGuid(const FGuid& Guid) override;`
- L63 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L64 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L73 _protected prototype_ `bool InitializePlayer();` — Initialize the media player. @return true on success, false otherwise.
- L79 _protected prototype_ `virtual bool CanControl(EMediaControl Control) const override;`
- L80 _protected prototype_ `virtual FTimespan GetDuration() const override;`
- L81 _protected prototype_ `virtual float GetRate() const override;`
- L82 _protected prototype_ `virtual EMediaState GetState() const override;`
- L83 _protected prototype_ `virtual EMediaStatus GetStatus() const override;`
- L84 _protected prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L85 _protected prototype_ `virtual FTimespan GetTime() const override;`
- L86 _protected prototype_ `virtual bool IsLooping() const override;`
- L87 _protected prototype_ `virtual bool Seek(const FTimespan& Time) override;`
- L88 _protected prototype_ `virtual bool SetLooping(bool Looping) override;`
- L89 _protected prototype_ `virtual bool SetRate(float Rate) override;`
- L90 _protected prototype_ `virtual bool SetNativeVolume(float Volume) override;`
- L96 _protected prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;`
- L97 _protected prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L98 _protected prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L99 _protected prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L100 _protected prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L101 _protected prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L102 _protected prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L103 _protected prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L104 _protected prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L105 _protected prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L106 _protected prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L111 _private prototype_ `void HandleApplicationHasEnteredForeground();` — Callback for when the application resumed in the foreground.
- L114 _private prototype_ `void HandleApplicationWillEnterBackground();` — Callback for when the application is being paused in the background.
- L119 _private member_ `TArray<FJavaAndroidMediaPlayer::FAudioTrack> AudioTracks;` — Audio track descriptors.
- L122 _private member_ `TArray<FJavaAndroidMediaPlayer::FCaptionTrack> CaptionTracks;` — Caption track descriptors.
- L125 _private member_ `TArray<FJavaAndroidMediaPlayer::FVideoTrack> VideoTracks;` — Video track descriptors.
- L130 _private member_ `EMediaState CurrentState;` — Current player state.
- L133 _private member_ `bool bLooping;` — Current state of looping.
- L136 _private member_ `IMediaEventSink& EventSink;` — The media event handler.
- L139 _private member_ `FString Info;` — Media information string.
- L142 _private member_ `TSharedPtr<FJavaAndroidMediaPlayer, ESPMode::ThreadSafe> JavaMediaPlayer;` — The Java side media interface.
- L145 _private member_ `FString MediaUrl;` — Currently opened media.
- L148 _private member_ `FGuid PlayerGuid;` — Media player Guid
- L151 _private member_ `FDelegateHandle PauseHandle;` — Foreground/background delegate for pause.
- L154 _private member_ `FDelegateHandle ResumeHandle;` — Foreground/background delegate for resume.
- L157 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> Samples;` — The media sample queue.
- L160 _private member_ `int32 SelectedAudioTrack;` — Index of the selected audio track.
- L163 _private member_ `int32 SelectedCaptionTrack;` — Index of the selected audio track.
- L166 _private member_ `int32 SelectedVideoTrack;` — Index of the selected video track.
- L169 _private member_ `FAndroidMediaTextureSamplePool* VideoSamplePool;` — Video sample object pool.
- L172 _private member_ `bool bEnterBackground;` — Device enters background.

### `Plugins/Media/AndroidMedia/Source/AndroidMedia/Private/Player/AndroidMediaTextureSample.h` (Private)


#### class `FAndroidMediaTextureSample`  
`class FAndroidMediaTextureSample : public IMediaTextureSample , public IMediaTextureSampleConverter , public IMediaPoolable`  
_L28-375_
- inherits: `IMediaTextureSample,IMediaTextureSampleConverter,IMediaPoolable`
- desc: Texture sample generated by AndroidMedia player.
- L36 _public function_ `FAndroidMediaTextureSample() : Buffer(nullptr) , BufferSize(0) , ExternalTexture(false) , Dim(FIntPoint::ZeroValue) , Duration(FTimespan::Zero()) , Time(FTimespan::Zero()) , ScaleRotation(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)) , Offset(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f))` — Default constructor.
- L48 _public function_ `virtual ~FAndroidMediaTextureSample()` — Virtual destructor.
- L65 _public function_ `void* GetMutableBuffer()` — Get a writable pointer to the sample buffer. @return Sample buffer.
- L77 _public function_ `bool Initialize(const FIntPoint& InDim, FTimespan InDuration)` — Initialize the sample. @param InDim The sample buffer's width and height (in pixels). @param InDuration The duration for which the sample is valid. @return true on success, false otherwise.
- L95 _public function_ `void InitializeExternalTexture(FTimespan InTime)` — Initialize the sample as an external image reference.
- L109 _public function_ `void InitializeBuffer(void* InBuffer, FTimespan InTime, bool Copy)` — Initialize the sample with a memory buffer. @param InBuffer The buffer containing the sample data. @param InTime The sample time (in the player's local clock). @param Copy Whether the buffer should be copied (true) or referenced (false). @see InitializeTexture
- L154 _public function_ `FRHITexture* InitializeTexture(FRHICommandListBase& RHICmdList, FTimespan InTime)` — Initialize the sample with a texture resource. @param RHICmdList the command list used to create the texture. @param InTime The sample time (in the player's local clock). @return The texture resource object that will hold the sample data. @note This method must be called on the render thread. @see InitializeBuffer
- L185 _public function_ `void InitializeMediaFrameData(jobject InFrameData, FTimespan InTime)` — Initialize the sample with a java frame data object. @param InFrameData holds the jobject of the frame data. @param InTime The sample time (in the player's local clock). @note This method must be called on the render thread. @see InitializeBuffer, InitializeTexture
- L198 _public function_ `void SetScaleRotationOffset(FVector4& InScaleRotation, FVector4& InOffset)` — Set the sample Scale, Rotation, Offset. @param InScaleRotation The sample scale and rotation transform (2x2). @param InOffset The sample offset.
- L208 _public function_ `virtual const void* GetBuffer() override`
- L213 _public function_ `virtual FIntPoint GetDim() const override`
- L218 _public function_ `virtual FTimespan GetDuration() const override`
- L223 _public function_ `virtual EMediaTextureSampleFormat GetFormat() const override`
- L228 _public function_ `virtual FIntPoint GetOutputDim() const override`
- L233 _public function_ `virtual uint32 GetStride() const override`
- L240 _public function_ `virtual FRHITexture* GetTexture() const override`
- L247 _public function_ `virtual FMediaTimeStamp GetTime() const override`
- L252 _public function_ `virtual bool IsExternalImage() const override`
- L257 _public function_ `void UpdateTimeDuration(FTimespan InTime, FTimespan InDuration)`
- L263 _public function_ `virtual bool IsCacheable() const override`
- L272 _public function_ `virtual bool IsOutputSrgb() const override`
- L277 _public function_ `virtual FLinearColor GetScaleRotation() const override`
- L282 _public function_ `virtual FLinearColor GetOffset() const override`
- L287 _public function_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override`
- L298 _public function_ `virtual bool IsReadyForReuse() override`
- L307 _public function_ `virtual void ShutdownPoolable() override`
- L325 _private function_ `virtual bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) override`
- L343 _private member_ `FAndroidJavaMediaFrameData MediaFrameData;` — The sample's java frame data from BitmapRendererImageReader.
- L346 _private member_ `void* Buffer;` — The sample's data buffer.
- L349 _private member_ `SIZE_T BufferSize;` — Current allocation size of Buffer.
- L352 _private member_ `bool ExternalTexture;` — Flag indicating if this is an external image reference.
- L355 _private member_ `FIntPoint Dim;` — Width and height of the texture sample.
- L358 _private member_ `FTimespan Duration;` — Duration for which the sample is valid.
- L361 _private member_ `FTimespan Time;` — Sample time.
- L364 _private member_ `FLinearColor ScaleRotation;` — ScaleRotation for the sample.
- L367 _private member_ `FLinearColor Offset;` — Offset for the sample.
- L372 _private member_ `TRefCountPtr<FRHITexture> Texture;` — Texture resource.

#### class `FAndroidMediaTextureSamplePool`  
`class FAndroidMediaTextureSamplePool : public TMediaObjectPool<FAndroidMediaTextureSample>`  
_L379-379_
- inherits: `TMediaObjectPool<FAndroidMediaTextureSample>`
- desc: Implements a pool for Android texture sample objects.

### `Plugins/Media/AndroidMedia/Source/AndroidMedia/Public/IAndroidMediaModule.h` (Public)


#### class `IAndroidMediaModule`  
`class IAndroidMediaModule : public IModuleInterface`  
_L15-32_
- inherits: `IModuleInterface`
- desc: Interface for the AndroidMedia module.
- L26 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create a Android based media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.
- L31 _public prototype_ `virtual ~IAndroidMediaModule() = default;` — Virtual destructor.
