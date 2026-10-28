# Plugins / AvfMediaCapture

- module root: `Plugins/Media/AvfMedia/Source/AvfMediaCapture`
- headers: 3; symbols: 67
- symbol kinds: class=1, delegate=1, enum=1, enumerator=6, member=12, prototype=46
- DynamicallyLoadedModuleNames: Media
- PrivateDependencyModuleNames: ApplicationCore, AvfMedia, Core, CoreUObject, Engine, MediaUtils, MetalRHI, RHI, RenderCore, UnrealEd
- PrivateIncludePathModuleNames: Media

### `Plugins/Media/AvfMedia/Source/AvfMediaCapture/Private/AvfMediaCapturePrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvfMediaCapture, Log, All);` — Log category for the AvfMediaCapture module.
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvfMediaCapture, Log, All);` — Log category for the AvfMediaCapture module.

### `Plugins/Media/AvfMedia/Source/AvfMediaCapture/Private/Player/AvfMediaCaptureHelper.h` (Private)


#### enum `EAvfMediaCaptureAuthStatus`  
`enum class EAvfMediaCaptureAuthStatus : uint32`  
_L18-29_
- L21 _public enumerator_ `NotDetermined = AVAuthorizationStatusNotDetermined` — Mapped Apple AVFoundation values
- L22 _public enumerator_ `Restricted = AVAuthorizationStatusRestricted`
- L23 _public enumerator_ `Denied = AVAuthorizationStatusDenied`
- L24 _public enumerator_ `Authorized = AVAuthorizationStatusAuthorized`
- L27 _public enumerator_ `MissingInfoPListEntry` — Extra Error values
- L28 _public enumerator_ `InvalidRequest`

### `Plugins/Media/AvfMedia/Source/AvfMediaCapture/Private/Player/AvfMediaCapturePlayer.h` (Private)


#### class `FAvfMediaCapturePlayer`  
`class FAvfMediaCapturePlayer : public IMediaPlayer , public IMediaTracks , protected IMediaCache , protected IMediaControls , protected IMediaView , public TSharedFromThis<FAvfMediaCapturePlayer>`  
_L23-122_
- inherits: `IMediaPlayer,IMediaTracks,IMediaCache,IMediaControls,IMediaView,TSharedFromThis<FAvfMediaCapturePlayer>`
- L33 _public prototype_ `FAvfMediaCapturePlayer(IMediaEventSink& InEventSink);`
- L34 _public prototype_ `virtual ~FAvfMediaCapturePlayer();`
- L38 _public prototype_ `virtual void Close() override;` — IMediaPlayer Interface
- L39 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L40 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L41 _public prototype_ `virtual FString GetInfo() const override;`
- L42 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L43 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L44 _public prototype_ `virtual FString GetStats() const override;`
- L45 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L46 _public prototype_ `virtual FString GetUrl() const override;`
- L47 _public prototype_ `virtual IMediaView& GetView() override;`
- L48 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L49 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L50 _public prototype_ `virtual FText GetMediaName() const override;`
- L51 _public prototype_ `virtual bool GetPlayerFeatureFlag(EFeatureFlag Flag) const override;`
- L54 _public prototype_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override;` — IMediaTracks Interface
- L55 _public prototype_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override;`
- L56 _public prototype_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L57 _public prototype_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override;`
- L58 _public prototype_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L59 _public prototype_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L60 _public prototype_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L61 _public prototype_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override;`
- L62 _public prototype_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override;`
- L63 _public prototype_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override;`
- L64 _public prototype_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override;`
- L69 _protected prototype_ `virtual bool CanControl(EMediaControl Control) const override;` — IMediaControls Interface
- L70 _protected prototype_ `virtual FTimespan GetDuration() const override;`
- L71 _protected prototype_ `virtual float GetRate() const override;`
- L72 _protected prototype_ `virtual EMediaState GetState() const override;`
- L73 _protected prototype_ `virtual EMediaStatus GetStatus() const override;`
- L74 _protected prototype_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override;`
- L75 _protected prototype_ `virtual FTimespan GetTime() const override;`
- L76 _protected prototype_ `virtual bool IsLooping() const override;`
- L77 _protected prototype_ `virtual bool Seek(const FTimespan& Time) override;`
- L78 _protected prototype_ `virtual bool SetLooping(bool Looping) override;`
- L79 _protected prototype_ `virtual bool SetRate(float Rate) override;`
- L83 _private prototype_ `void CreateCaptureSession(NSString* deviceIDString, AVMediaType MediaType);`
- L84 _private prototype_ `void CaptureSystemNotification(NSNotification* Notification);`
- L85 _private prototype_ `void HandleAuthStatusError(EAvfMediaCaptureAuthStatus AuthStatus, AVMediaType MediaType);`
- L87 _private prototype_ `FTimespan UpdateInternalTime(CMSampleBufferRef SampleBuffer, FTimespan const& ComputedBufferDuration);`
- L89 _private prototype_ `void NewSampleBufferAvailable(CMSampleBufferRef SampleBuffer);`
- L90 _private prototype_ `void ProcessSampleBufferVideo(CMSampleBufferRef SampleBuffer);`
- L91 _private prototype_ `void ProcessSampleBufferAudio(CMSampleBufferRef SampleBuffer);`
- L96 _private member_ `IMediaEventSink& EventSink;` — The media event handler.
- L99 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> MediaSamples;` — Media sample collection.
- L102 _private member_ `AvfMediaCaptureHelper* MediaCaptureHelper;` — Media capture AV Obj-C Helper
- L105 _private member_ `FAvfMediaAudioSamplePool AudioSamplePool;` — Reuse Sample Pool Objects
- L106 _private member_ `FAvfMediaTextureSamplePool VideoSamplePool;`
- L109 _private member_ `CVMetalTextureCacheRef MetalTextureCache;` — Internal CoreVideo Metal Texture cache to handle AVFoundation resource pooling and optimisations
- L112 _private member_ `float CurrentRate;` — Media Playback Info and Control data
- L113 _private member_ `FTimespan CurrentTime;`
- L114 _private member_ `FString URL;`
- L117 _private member_ `double ThrottleDuration;`
- L118 _private member_ `double LastConsumedTimeStamp;`
- L121 _private member_ `mutable FCriticalSection CriticalSection;`
