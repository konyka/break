# Plugins / WebMMoviePlayer

- module root: `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer`
- headers: 8; symbols: 77
- symbol kinds: class=3, delegate=1, enum=2, enumerator=4, function=11, member=22, prototype=32, typedef=2
- PrivateDependencyModuleNames: Core, Engine, MediaUtils, MoviePlayer, RHI, RenderCore, SDL3, Slate, SlateCore, WebMMedia

### `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer/Private/Audio/Linux/LinuxWebMAudioBackendDefines.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `using FWebMAudioBackend = FWebMAudioBackendSDL;`

### `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer/Private/Audio/Mac/MacWebMAudioBackendDefines.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer/Private/Audio/Null/WebMAudioBackend.h` (Private)


#### class `FWebMAudioBackendNull`  
`class FWebMAudioBackendNull`  
_L9-28_
- L19 _public function_ `bool InitializePlatform()`
- L20 _public function_ `void ShutdownPlatform()`
- L21 _public function_ `bool StartStreaming(int32 SampleRate, int32 NumOfChannels, EStreamState StreamState)`
- L22 _public function_ `void StopStreaming()`
- L23 _public function_ `bool SendAudio(const FTimespan& Timespan, const uint8* Buffer, size_t BufferSize)`
- L25 _public function_ `void Pause(bool bPause)`
- L26 _public function_ `bool IsPaused() const`
- L27 _public function_ `void Tick(float DeltaTime)`

#### enum `FWebMAudioBackendNull::EStreamState`  
`enum class EStreamState`  
_L13-17_
- L15 _public enumerator_ `NewMovie`
- L16 _public enumerator_ `ResumeAfterPause`

### `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer/Private/Audio/Null/WebMAudioBackendDefines.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `using FWebMAudioBackend = FWebMAudioBackendNull;`

### `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer/Private/Audio/Unix/WebMAudioBackend.h` (Private)


#### class `FWebMAudioBackendSDL`  
`class FWebMAudioBackendSDL`  
_L15-46_
- L25 _public prototype_ `FWebMAudioBackendSDL();`
- L26 _public prototype_ `virtual ~FWebMAudioBackendSDL();`
- L29 _public prototype_ `virtual bool InitializePlatform();`
- L30 _public prototype_ `virtual void ShutdownPlatform();`
- L31 _public prototype_ `virtual bool StartStreaming(int32 SampleRate, int32 NumOfChannels, EStreamState StreamState);`
- L32 _public prototype_ `virtual void StopStreaming();`
- L33 _public prototype_ `virtual bool SendAudio(const FTimespan& Timespan, const uint8* Buffer, size_t BufferSize);`
- L35 _public prototype_ `virtual void Pause(bool bPause);`
- L36 _public prototype_ `virtual bool IsPaused() const;`
- L37 _public prototype_ `virtual void Tick(float DeltaTime);`
- L38 _public prototype_ `virtual FString GetDefaultDeviceName();`
- L41 _protected member_ `SDL_AudioStream* AudioStream;`
- L42 _protected member_ `bool bSDLInitialized;`
- L45 _protected member_ `bool bPaused;` — Whether we're pausing playing back sound.

#### enum `FWebMAudioBackendSDL::EStreamState`  
`enum class EStreamState`  
_L19-23_
- L21 _public enumerator_ `NewMovie`
- L22 _public enumerator_ `ResumeAfterPause`

### `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer/Private/Audio/Windows/WindowsWebMAudioBackendDefines.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer/Private/WebMMovieCommon.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebMMoviePlayer, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWebMMoviePlayer, Log, All);`

### `Plugins/Runtime/WebMMoviePlayer/Source/WebMMoviePlayer/Private/WebMMovieStreamer.h` (Private)


#### class `FWebMMovieStreamer`  
`class FWebMMovieStreamer : public IMovieStreamer, public IWebMSamplesSink`  
_L20-95_
- inherits: `IMovieStreamer,IWebMSamplesSink`
- L23 _public prototype_ `FWebMMovieStreamer();`
- L24 _public prototype_ `~FWebMMovieStreamer();`
- L27 _public prototype_ `virtual void AddVideoSampleFromDecodingThread(TSharedRef<FWebMMediaTextureSample, ESPMode::ThreadSafe> Sample) override;`
- L28 _public prototype_ `virtual void AddAudioSampleFromDecodingThread(TSharedRef<FWebMMediaAudioSample, ESPMode::ThreadSafe> Sample) override;`
- L29 _public function_ `virtual void ReportVideoDecodingError(FString InErrorMessage) override`
- L30 _public function_ `virtual void ReportAudioDecodingError(FString InErrorMessage) override`
- L33 _public prototype_ `virtual bool Init(const TArray<FString>& InMoviePaths, TEnumAsByte<EMoviePlaybackType> InPlaybackType) override;`
- L34 _public prototype_ `virtual void ForceCompletion() override;`
- L35 _public prototype_ `virtual bool Tick(FRHICommandListBase& RHICmdList, float InDeltaTime) override;`
- L36 _public prototype_ `virtual TSharedPtr<class ISlateViewport> GetViewportInterface() override;`
- L37 _public prototype_ `virtual float GetAspectRatio() const override;`
- L38 _public prototype_ `virtual FString GetMovieName() override;`
- L39 _public prototype_ `virtual bool IsLastMovieInPlaylist() override;`
- L40 _public prototype_ `virtual void Cleanup() override;`
- L41 _public prototype_ `virtual FTextureRHIRef GetTexture() override;`
- L43 _public member_ `FOnCurrentMovieClipFinished OnCurrentMovieClipFinishedDelegate;`
- L44 _public function_ `virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() override`
- L47 _private member_ `TArray<FString> MovieQueue;`
- L48 _private member_ `TQueue<TArray<TSharedPtr<FWebMFrame, ESPMode::ThreadSafe>>> VideoFramesToDecodeLater;`
- L49 _private member_ `FString MovieName;`
- L50 _private member_ `TUniquePtr<FWebMVideoDecoder> VideoDecoder;`
- L51 _private member_ `TUniquePtr<FWebMAudioDecoder> AudioDecoder;`
- L52 _private member_ `TUniquePtr<FWebMContainer> Container;`
- L53 _private member_ `TUniquePtr<FWebMAudioBackend> AudioBackend;`
- L54 _private member_ `TSharedPtr<FMediaSamples, ESPMode::ThreadSafe> Samples;`
- L55 _private member_ `TSharedPtr<FMovieViewport> Viewport;`
- L56 _private member_ `TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe> SlateVideoTexture;`
- L59 _private member_ `int32 VideoFramesCurrentlyProcessing;` — Limits amount of frames being processed to save video memory used by the player
- L62 _private member_ `double StartTime;` — Movie start time
- L64 _private member_ `double TimeAtEnteringBackground;` — Timestamp when we entered background
- L66 _private member_ `bool bPlaying;` — Whether a movie is being played
- L68 _private member_ `bool bPaused;` — We can be paused e.g. while in background
- L75 _private member_ `int32 TicksLeftToWaitPostCompletion;` — Number of ticks to wait after the movie is complete before moving on to the next one. This allows us to defer texture deletion while it is being displayed.
- L77 _private prototype_ `bool StartNextMovie();`
- L78 _private prototype_ `void ReleaseAcquiredResources();`
- L79 _private prototype_ `bool DisplayFrames(float InDeltaTime);`
- L80 _private prototype_ `bool SendAudio(float InDeltaTime);`
- L81 _private prototype_ `bool ReadMoreFrames();`
- L84 _private prototype_ `void HandleApplicationHasEnteredForeground();` — Callback for when the application resumed in the foreground.
- L87 _private prototype_ `void HandleApplicationWillEnterBackground();` — Callback for when the application is being paused in the background.
- L90 _private member_ `FDelegateHandle PauseHandle;` — Foreground/background delegate for pause.
- L93 _private member_ `FDelegateHandle ResumeHandle;` — Foreground/background delegate for resume.
