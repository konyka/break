# Plugins / AppleMoviePlayer

- module root: `Plugins/Runtime/AppleMoviePlayer/Source/AppleMoviePlayer`
- headers: 2; symbols: 46
- symbol kinds: class=1, enum=1, enumerator=4, function=1, member=21, prototype=18
- PrivateDependencyModuleNames: SlateCore
- PublicDependencyModuleNames: ApplicationCore, Core, CoreUObject, Engine, MetalRHI, MoviePlayer, RHI, RenderCore, Slate

### `Plugins/Runtime/AppleMoviePlayer/Source/AppleMoviePlayer/Private/AppleMovieStreamer.h` (Private)


#### class `FAVPlayerMovieStreamer`  
`class FAVPlayerMovieStreamer : public IMovieStreamer`  
_L19-100_
- inherits: `IMovieStreamer`
- desc: The actual streamer class
- L22 _public prototype_ `FAVPlayerMovieStreamer();`
- L23 _public prototype_ `virtual ~FAVPlayerMovieStreamer();`
- L25 _public prototype_ `virtual bool Init(const TArray<FString>& MoviePaths, TEnumAsByte<EMoviePlaybackType> inPlaybackType) override;`
- L26 _public prototype_ `virtual void ForceCompletion() override;`
- L27 _public prototype_ `virtual bool Tick(FRHICommandListBase& RHICmdList, float DeltaTime) override;`
- L28 _public prototype_ `virtual TSharedPtr<class ISlateViewport> GetViewportInterface() override;`
- L29 _public prototype_ `virtual float GetAspectRatio() const override;`
- L30 _public prototype_ `virtual void Cleanup() override;`
- L32 _public prototype_ `virtual FString GetMovieName() override;`
- L33 _public prototype_ `virtual bool IsLastMovieInPlaylist() override;`
- L34 _public prototype_ `virtual void Suspend() override;`
- L35 _public prototype_ `virtual void Resume() override;`
- L37 _public member_ `FOnCurrentMovieClipFinished OnCurrentMovieClipFinishedDelegate;`
- L38 _public function_ `virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() override`
- L51 _private member_ `TSharedPtr<FMovieViewport> MovieViewport;` — Texture and viewport data for displaying to Slate
- L53 _private member_ `TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe> SlateTexture;`
- L56 _private member_ `TArray<FString> MovieQueue;` — The list of pending movies
- L59 _private member_ `AVAudioPlayer* AudioPlayer;` — Current Movie
- L60 _private member_ `AVURLAsset* AVMovie;`
- L61 _private member_ `AVAssetReader* AVReader;`
- L62 _private member_ `AVAssetReaderTrackOutput* AVVideoOutput;`
- L63 _private member_ `AVAssetTrack* AVVideoTrack;`
- L64 _private member_ `CMSampleBufferRef LatestSamples;`
- L66 _private member_ `FString MovieName;`
- L69 _private member_ `float VideoRate;` — AV Synchronization
- L70 _private member_ `int SyncStatus;`
- L71 _private member_ `double StartTime;`
- L72 _private member_ `double Cursor;`
- L74 _private member_ `bool bVideoTracksLoaded;`
- L75 _private member_ `bool bWasActive;`
- L77 _private member_ `bool bIsMovieInterrupted;`
- L78 _private member_ `CMTime ResumeTime;`
- L80 _private member_ `FCriticalSection VideoTracksLoadingLock;`
- L82 _private member_ `CVMetalTextureCacheRef MetalTextureCache;`
- L89 _private prototype_ `bool StartNextMovie();` — Sets up and starts playback on the next movie in the queue
- L91 _private prototype_ `bool FinishLoadingTracks();`
- L93 _private prototype_ `void TeardownPlayback();`
- L95 _private prototype_ `bool CheckForNextFrameAndCopy(FRHICommandListBase& RHICmdList);`
- L97 _private prototype_ `void ReleaseMovie();`
- L99 _private prototype_ `bool LoadMovieAsync(FString MovieName);`

#### enum `FAVPlayerMovieStreamer::ESyncStatus`  
`enum ESyncStatus`  
_L42-48_
- L44 _public enumerator_ `Default` — Starting state
- L45 _public enumerator_ `Ahead` — Frame is ahead of playback cursor.
- L46 _public enumerator_ `Behind` — Frame is behind playback cursor.
- L47 _public enumerator_ `Ready` — Frame is within tolerance of playback cursor.

### `Plugins/Runtime/AppleMoviePlayer/Source/AppleMoviePlayer/Public/AppleMoviePlayer.h` (Public)
_(no declarations extracted)_
