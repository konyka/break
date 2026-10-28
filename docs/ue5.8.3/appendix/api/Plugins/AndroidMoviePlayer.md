# Plugins / AndroidMoviePlayer

- module root: `Plugins/Runtime/AndroidMoviePlayer/Source/AndroidMoviePlayer`
- headers: 2; symbols: 22
- symbol kinds: class=1, function=1, member=8, prototype=12
- PrivateDependencyModuleNames: OpenGL
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MoviePlayer, OpenGLDrv, RHI, RenderCore, Slate

### `Plugins/Runtime/AndroidMoviePlayer/Source/AndroidMoviePlayer/Private/AndroidMovieStreamer.h` (Private)


#### class `FAndroidMediaPlayerStreamer`  
`class FAndroidMediaPlayerStreamer : public IMovieStreamer`  
_L11-61_
- inherits: `IMovieStreamer`
- desc: The actual streamer class
- L14 _public prototype_ `FAndroidMediaPlayerStreamer();`
- L15 _public prototype_ `virtual ~FAndroidMediaPlayerStreamer();`
- L17 _public prototype_ `virtual bool Init(const TArray<FString>& MoviePaths, TEnumAsByte<EMoviePlaybackType> inPlaybackType) override;`
- L18 _public prototype_ `virtual void ForceCompletion() override;`
- L19 _public prototype_ `virtual bool Tick(FRHICommandListBase& RHICmdList, float DeltaTime) override;`
- L20 _public prototype_ `virtual TSharedPtr<class ISlateViewport> GetViewportInterface() override;`
- L21 _public prototype_ `virtual float GetAspectRatio() const override;`
- L22 _public prototype_ `virtual void Cleanup() override;`
- L24 _public prototype_ `virtual FString GetMovieName() override;`
- L25 _public prototype_ `virtual bool IsLastMovieInPlaylist() override;`
- L27 _public member_ `FOnCurrentMovieClipFinished OnCurrentMovieClipFinishedDelegate;`
- L28 _public function_ `virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() override`
- L34 _private member_ `FCriticalSection MovieQueueCriticalSection;` — A list of all the stored movie paths we have enqueued for playing
- L35 _private member_ `TArray<FString> MovieQueue;`
- L40 _private member_ `TSharedPtr<FMovieViewport> MovieViewport;` — Texture and view-port data for displaying to Slate
- L41 _private member_ `TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe> Texture;`
- L47 _private member_ `TArray<TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe>> TexturesPendingDeletion;` — List of textures pending deletion, need to keep this list because we can't immediately destroy them since they could be getting used on the main thread
- L52 _private member_ `TSharedPtr<FJavaAndroidMediaPlayer, ESPMode::ThreadSafe> JavaMediaPlayer;` — Java side interface for MediaPlayer utility.
- L57 _private member_ `int32 CurrentPosition;` — Some state for the playing movie.
- L59 _private prototype_ `bool StartNextMovie();`
- L60 _private prototype_ `void CloseMovie();`

### `Plugins/Runtime/AndroidMoviePlayer/Source/AndroidMoviePlayer/Public/AndroidMoviePlayer.h` (Public)
_(no declarations extracted)_
