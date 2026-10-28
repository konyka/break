# Plugins / MediaMovieStreamer

- module root: `Plugins/Media/MediaMovieStreamer/Source/MediaMovieStreamer`
- headers: 4; symbols: 64
- symbol kinds: class=4, delegate=2, function=1, member=19, prototype=38
- PrivateDependencyModuleNames: CoreUObject, Engine, Media, MediaAssets, MoviePlayer, RHI, RenderCore, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Media/MediaMovieStreamer/Source/MediaMovieStreamer/Private/MediaMovieAssets.h` (Private)


#### class `UMediaMovieAssets`  
`class UMediaMovieAssets : public UObject`  
_L20-82_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Keeps assets alive during level loading so they don't get garbage collected while we are using them. Also handles other UObject functionality like hooking into the UMediaPlayer callbacks which require a UObject.
- L25 _public prototype_ `UMediaMovieAssets();`
- L26 _public prototype_ `~UMediaMovieAssets();`
- L34 _public prototype_ `void SetMediaPlayer(UMediaPlayer* InMediaPlayer, FMediaMovieStreamer* InMovieStreamer);` — Sets which media player we are using. @param InMediaPlayer @param InMovieStreamer Movie streamer that is using the media player.
- L41 _public prototype_ `void SetMediaSoundComponent(UMediaSoundComponent* InMediaSoundComponent);` — Sets what media sound component we are using. @param InMediaSoundComponent Media sound component to use.
- L48 _public prototype_ `void SetMediaSource(UMediaSource* InMediaSource);` — Sets what media source we are using. @param InMediaSource Media source to play.
- L55 _public prototype_ `void SetMediaTexture(UMediaTexture* InMediaTexture);` — Sets what media texture we are using. @param InMediaTexture Media texture to use.
- L62 _private prototype_ `void OnMediaEnd();` — `UFUNCTION()` — Called by the media player when the video ends.
- L66 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — `UPROPERTY()` — Holds the player we are using.
- L70 _private member_ `TObjectPtr<UMediaSoundComponent> MediaSoundComponent;` — `UPROPERTY()` — Holds the media sound component we are using.
- L74 _private member_ `TObjectPtr<UMediaSource> MediaSource;` — `UPROPERTY()` — Holds the media source we are using.
- L78 _private member_ `TObjectPtr<UMediaTexture> MediaTexture;` — `UPROPERTY()` — Holds the media texture we are using.
- L81 _private member_ `FMediaMovieStreamer* MovieStreamer;` — Holds the movie streamer.

### `Plugins/Media/MediaMovieStreamer/Source/MediaMovieStreamer/Private/MediaMovieTimeSource.h` (Private)


#### class `FMediaMovieTimeSource`  
`class FMediaMovieTimeSource : public IMediaTimeSource`  
_L13-26_
- inherits: `IMediaTimeSource`
- desc: Implements the a media time source that derives its time from the application's global time.
- L19 _public prototype_ `virtual ~FMediaMovieTimeSource() = default;` — Virtual destructor.
- L25 _public prototype_ `virtual FTimespan GetTimecode() override;`

### `Plugins/Media/MediaMovieStreamer/Source/MediaMovieStreamer/Public/MediaMovieStreamer.h` (Public)


#### class `FMediaMovieStreamer`  
`class FMediaMovieStreamer : public IMovieStreamer`  
_L24-130_
- inherits: `IMovieStreamer`
- desc: Movie streamer that allows you to use MediaFramework during level loading, etc.
- L27 _public prototype_ `FMediaMovieStreamer();`
- L28 _public prototype_ `~FMediaMovieStreamer();`
- L40 _public prototype_ `void SetIsMediaControlledExternally(bool bInIsMediaControlledExternally);` — If you do not want FMediaMovieStreamer to play automatically, but want to control the media yourself, then call this with true. This also means that FMediaMovieStreamer will no longer clean up the assets when it is done. You will have to call SetMediaPlayer, SetMediaSoundComponent, etc with nullptr when you are done so FMediaMovieStreamer will no longer keep its hold on them. @param bIsMediaControlledExternally True if you want to control the media.
- L47 _public prototype_ `void SetMediaPlayer(UMediaPlayer* InMediaPlayer);` — Sets which media player should be playing. @param InMediaPlayer
- L54 _public prototype_ `void SetMediaSoundComponent(UMediaSoundComponent* InMediaSoundComponent);` — Sets what media sound component we are using. @param InMediaSoundComponent Media sound component that is being used.
- L59 _public function_ `UMediaSoundComponent* GetMediaSoundComponent()` — Returns the current MediaSoundComponent
- L66 _public prototype_ `void SetMediaSource(UMediaSource* InMediaSource);` — Sets what to play. @param InMediaSource Media source to play.
- L73 _public prototype_ `void SetMediaTexture(UMediaTexture* InMediaTexture);` — Sets what media texture we are using. @param InMediaSource Media source to play.
- L75 _public member_ `FMovieStreamerExternalTick MovieStreamerPostEngineTick;`
- L76 _public member_ `FMovieStreamerExternalTick MovieStreamerPreEngineTick;`
- L77 _public member_ `FMovieStreamerExternalTick MovieStreamerPostRenderTick;`
- L82 _public prototype_ `void OnMediaEnd();` — Called from UMediaMovieAssets when the media ends.
- L85 _public prototype_ `virtual bool Init(const TArray<FString>& InMoviePaths, TEnumAsByte<EMoviePlaybackType> InPlaybackType) override;` — IMovieStreamer interface
- L86 _public prototype_ `virtual void PreviousViewportInterface(const TSharedPtr<ISlateViewport>& PreviousViewportInterface) override;`
- L87 _public prototype_ `virtual void ForceCompletion() override;`
- L88 _public prototype_ `virtual bool Tick(FRHICommandListBase& RHICmdList, float DeltaTime) override;`
- L89 _public prototype_ `virtual TSharedPtr<class ISlateViewport> GetViewportInterface() override;`
- L90 _public prototype_ `virtual float GetAspectRatio() const override;`
- L91 _public prototype_ `virtual FString GetMovieName() override;`
- L92 _public prototype_ `virtual bool IsLastMovieInPlaylist() override;`
- L93 _public prototype_ `virtual void Cleanup() override;`
- L94 _public prototype_ `virtual FTextureRHIRef GetTexture() override;`
- L95 _public prototype_ `virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() override;`
- L97 _public prototype_ `virtual void TickPreEngine() override;`
- L98 _public prototype_ `virtual void TickPostEngine() override;`
- L99 _public prototype_ `virtual void TickPostRender() override;`
- L103 _private member_ `FOnCurrentMovieClipFinished OnCurrentMovieClipFinishedDelegate;` — Delegate for when the movie is finished.
- L106 _private member_ `TSharedPtr<FMovieViewport> MovieViewport;` — Viewport data for displaying to Slate.
- L108 _private member_ `TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe> Texture;` — Texture displaying to Slate.
- L111 _private member_ `TWeakObjectPtr<UMediaPlayer> MediaPlayer;` — Holds the player we are using.
- L113 _private member_ `TWeakObjectPtr<UMediaSoundComponent> MediaSoundComponent;` — Holds the media sound component we are using.
- L115 _private member_ `TWeakObjectPtr<UMediaSource> MediaSource;` — Holds the media source we are using.
- L117 _private member_ `TWeakObjectPtr<UMediaTexture> MediaTexture;` — Holds the media texture we are using.
- L120 _private prototype_ `IMediaModule* GetMediaModule();` — Gets the media module to interface with MediaFramework.
- L123 _private member_ `bool bIsPlaying;` — True if the media is still playing.
- L126 _private member_ `bool bIsMediaControlledExternally;` — True if somethiing else is controlling the media.
- L129 _private member_ `TSharedPtr<IMediaTimeSource, ESPMode::ThreadSafe> PreviousTimeSource;` — Stores the previous time source so we can restore it when we are done.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaMovieStreamer, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMediaMovieStreamer, Log, All);`
- L19 _delegate_ `DECLARE_EVENT(FMediaMovieStreamer, FMovieStreamerExternalTick);`
- L19 _prototype_ `DECLARE_EVENT(FMediaMovieStreamer, FMovieStreamerExternalTick);`

### `Plugins/Media/MediaMovieStreamer/Source/MediaMovieStreamer/Public/MediaMovieStreamerModule.h` (Public)


#### class `FMediaMovieStreamerModule`  
`class FMediaMovieStreamerModule : public IModuleInterface`  
_L11-30_
- inherits: `IModuleInterface`
- L17 _public prototype_ `static UMediaMovieAssets* GetMovieAssets();` — Call this to get the MovieAssets.
- L22 _public prototype_ `static const TSharedPtr<FMediaMovieStreamer, ESPMode::ThreadSafe> GetMovieStreamer();` — Call this to get the MovieStreamer.
- L25 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _private member_ `static bool bStartedModule;`
