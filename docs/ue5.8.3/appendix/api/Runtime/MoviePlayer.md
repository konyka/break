# Runtime / MoviePlayer

- module root: `Source/Runtime/MoviePlayer`
- headers: 5; symbols: 252
- symbol kinds: class=8, delegate=6, enum=1, enumerator=4, function=60, member=65, prototype=107, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, HTTP, HeadMountedDisplay, InputCore, MoviePlayerProxy, RHI, RenderCore, Slate, SlateCore
- PublicDependencyModuleNames: ApplicationCore, Engine

### `Source/Runtime/MoviePlayer/Private/DefaultGameMoviePlayer.h` (Private)


#### class `FMoviePlayerWidgetRenderer`  
`class FMoviePlayerWidgetRenderer`  
_L24-53_
- L27 _public prototype_ `FMoviePlayerWidgetRenderer(TSharedPtr<SWindow> InMainWindow, TSharedPtr<SVirtualWindow> InVirtualRenderWindowWindow, FSlateRenderer* InRenderer);`
- L34 _public prototype_ `void EnableDPIScale(bool bShouldEnable);` — Call this enable or disable DPI scale. * @param bInIsEanbled True to apply a DPI scale.
- L35 _public prototype_ `void DrawWindow(float DeltaTime);`
- L40 _private member_ `SWindow* MainWindow;` — Note: This is raw as we SWindows registered with SlateApplication are not thread safe
- L43 _private member_ `TSharedRef<class SVirtualWindow> VirtualRenderWindow;` — Virtual window that we render to instead of the main slate window (for thread safety).  Shares only the same backbuffer as the main window
- L45 _private member_ `TSharedPtr<FHittestGrid> HittestGrid;`
- L47 _private member_ `FSlateRenderer* SlateRenderer;`
- L49 _private member_ `FViewportRHIRef ViewportRHI;`
- L52 _private member_ `bool bIsDPIScaleEnabled;` — If true then apply a DPI scale.

#### class `FDefaultGameMoviePlayer`  
`class FDefaultGameMoviePlayer : public FTickableObjectRenderThread, public IGameMoviePlayer, public IMoviePlayerProxyServer, public TSharedFromThis<FDefaultGameMoviePlayer>`  
_L56-249_
- inherits: `FTickableObjectRenderThread,IGameMoviePlayer,IMoviePlayerProxyServer,TSharedFromThis<FDefaultGameMoviePlayer>`
- desc: An implementation of the movie player/loading screen we will use
- L60 _public function_ `static void Create()`
- L68 _public function_ `static void Destroy()`
- L74 _public prototype_ `static FDefaultGameMoviePlayer* Get();`
- L75 _public prototype_ `~FDefaultGameMoviePlayer();`
- L78 _public prototype_ `virtual void RegisterMovieStreamer(TSharedPtr<IMovieStreamer, ESPMode::ThreadSafe> InMovieStreamer) override;` — IGameMoviePlayer Interface
- L79 _public prototype_ `virtual void Initialize(FSlateRenderer& InSlateRenderer, TSharedPtr<SWindow> TargetRenderWindow = nullptr) override;`
- L80 _public prototype_ `virtual void Shutdown() override;`
- L81 _public prototype_ `virtual void PassLoadingScreenWindowBackToGame() const override;`
- L82 _public prototype_ `virtual void SetupLoadingScreen(const FLoadingScreenAttributes& LoadingScreenAttributes) override;`
- L83 _public prototype_ `virtual bool HasEarlyStartupMovie() const override;`
- L84 _public prototype_ `virtual bool PlayEarlyStartupMovies() override;`
- L85 _public prototype_ `virtual bool PlayMovie() override;`
- L86 _public prototype_ `virtual void StopMovie() override;`
- L87 _public prototype_ `virtual void WaitForMovieToFinish(bool bAllowEngineTick = false) override;`
- L88 _public prototype_ `virtual bool IsLoadingFinished() const override;`
- L89 _public prototype_ `virtual bool IsMovieCurrentlyPlaying() const override;`
- L90 _public prototype_ `virtual bool LoadingScreenIsPrepared() const override;`
- L91 _public prototype_ `virtual void SetupLoadingScreenFromIni() override;`
- L92 _public prototype_ `virtual void SetViewportDPIScale(float InViewportDPIScale) override;`
- L94 _public function_ `bool IsInitialized() const override`
- L97 _public function_ `virtual bool IsStartupMoviePlaying() const override` — Check if the initial movie(s) is still playing
- L99 _public function_ `virtual FOnPrepareLoadingScreen& OnPrepareLoadingScreen() override`
- L100 _public function_ `virtual FOnMoviePlaybackStarted& OnMoviePlaybackStarted() override`
- L101 _public function_ `virtual FOnMoviePlaybackTick& OnMoviePlaybackTick() override`
- L102 _public function_ `virtual FOnMoviePlaybackFinished& OnMoviePlaybackFinished() override`
- L103 _public function_ `virtual FOnMovieClipFinished& OnMovieClipFinished() override`
- L106 _public prototype_ `virtual void BlockingStarted() override;` — IMoviePlayerProxyServer interface.
- L107 _public prototype_ `virtual void BlockingTick() override;`
- L108 _public prototype_ `virtual void BlockingFinished() override;`
- L109 _public prototype_ `virtual void SetIsSlateThreadAllowed(bool bInIsSlateThreadAllowed) override;`
- L112 _public prototype_ `virtual void Tick( FRHICommandListImmediate& RHICmdList, float DeltaTime ) override;` — FTickableObjectRenderThread interface
- L113 _public prototype_ `virtual TStatId GetStatId() const override;`
- L114 _public prototype_ `virtual bool IsTickable() const override;`
- L117 _public prototype_ `FReply OnLoadingScreenMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& PointerEvent);` — Callback for clicking on the viewport
- L118 _public prototype_ `FReply OnLoadingScreenKeyDown(const FGeometry& Geometry, const FKeyEvent& KeyEvent);`
- L120 _public prototype_ `virtual void SetSlateOverlayWidget(TSharedPtr<SWidget> NewOverlayWidget) override;`
- L122 _public prototype_ `virtual bool WillAutoCompleteWhenLoadFinishes() override;`
- L124 _public prototype_ `virtual FString GetMovieName() override;`
- L125 _public prototype_ `virtual bool IsLastMovieInPlaylist() override;`
- L127 _public prototype_ `virtual void ForceCompletion() override;`
- L128 _public prototype_ `virtual void Suspend() override;`
- L129 _public prototype_ `virtual void Resume() override;`
- L131 _public prototype_ `virtual void SetIsPlayOnBlockingEnabled(bool bIsEnabled) override;`
- L133 _public prototype_ `float GetViewportDPIScale() const;`
- L135 _public prototype_ `void OnMainWindowClosed(const TSharedRef<SWindow>& Window);`
- L140 _private prototype_ `void TickStreamer(FRHICommandListImmediate& RHICmdList, float DeltaTime);` — Ticks the underlying MovieStreamer.  Must be done exactly once before each DrawWindows call.
- L143 _private prototype_ `bool MovieStreamingIsPrepared() const;` — True if we have both a registered movie streamer and movies to stream
- L146 _private prototype_ `bool IsMovieStreamingFinished() const;` — True if movie streamer has finished streaming all the movies it wanted to
- L149 _private prototype_ `FVector2D GetMovieSize() const;` — Callbacks for movie sizing for the movie viewport
- L150 _private prototype_ `FOptionalSize GetMovieWidth() const;`
- L151 _private prototype_ `FOptionalSize GetMovieHeight() const;`
- L152 _private prototype_ `EVisibility GetSlateBackgroundVisibility() const;`
- L153 _private prototype_ `EVisibility GetViewportVisibility() const;`
- L156 _private prototype_ `void OnPreLoadMap(const FString& LevelName);` — Called via a delegate in the engine when maps start to load
- L159 _private prototype_ `void OnPostLoadMap(UWorld* LoadedWorld);` — Called via a delegate in the engine when maps finish loading
- L162 _private prototype_ `bool CanPlayMovie() const;` — Check if the device can render on a parallel thread on the initial loading
- L164 _private prototype_ `FDefaultGameMoviePlayer();`
- L166 _private prototype_ `FReply OnAnyDown();`
- L169 _private member_ `TArray<TSharedPtr<IMovieStreamer, ESPMode::ThreadSafe>> MovieStreamers;` — The movie streaming systems that will be used by us
- L170 _private member_ `TSharedPtr<IMovieStreamer, ESPMode::ThreadSafe> ActiveMovieStreamer;`
- L173 _private member_ `TWeakPtr<class SWindow> MainWindow;` — The window that the loading screen resides in
- L175 _private member_ `TSharedPtr<class SWidget> LoadingScreenContents;` — The widget which includes all contents of the loading screen, widgets and movie player and all
- L177 _private member_ `TSharedPtr<class SBorder> UserWidgetHolder;` — The widget which holds the loading screen widget passed in via the FLoadingScreenAttributes
- L179 _private member_ `TSharedPtr<class SVirtualWindow> VirtualRenderWindow;` — Virtual window that we render to instead of the main slate window (for thread safety).  Shares only the same backbuffer as the main window
- L181 _private member_ `TWeakPtr<class SViewport> MovieViewportWeakPtr;` — Viewport responsible for displaying the movie player render target
- L184 _private member_ `class FSlateLoadingSynchronizationMechanism* SyncMechanism;` — The threading mechanism with which we handle running slate on another thread
- L187 _private member_ `FThreadSafeCounter MovieStreamingIsDone;` — True if all movies have successfully streamed and completed
- L190 _private member_ `FThreadSafeCounter LoadingIsDone;` — True if the game thread has finished loading
- L193 _private member_ `bool IsMoviePlaying;` — True if the movie player is not yet finished
- L196 _private member_ `bool bUserCalledFinish;` — User has called finish (needed if LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes is off)
- L199 _private member_ `TAtomic<bool> bMainWindowClosed;` — Main window has closed, stop movie playback
- L202 _private member_ `FLoadingScreenAttributes LoadingScreenAttributes;` — Attributes of the loading screen we are currently displaying
- L205 _private member_ `FOnPrepareLoadingScreen OnPrepareLoadingScreenDelegate;` — Called before a movie is queued up to play to configure the movie player accordingly.
- L207 _private member_ `FOnMoviePlaybackStarted OnMoviePlaybackStartedDelegate;`
- L210 _private member_ `FOnMoviePlaybackTick OnMoviePlaybackTickDelegate;` — Called periodically when the game thread is blocked and a movie is playing.
- L212 _private member_ `FOnMoviePlaybackFinished OnMoviePlaybackFinishedDelegate;`
- L214 _private member_ `FOnMovieClipFinished OnMovieClipFinishedDelegate;`
- L217 _private member_ `double LastPlayTime;` — The last time a movie was started
- L220 _private member_ `bool bInitialized;` — True if the movie player has been initialized
- L223 _private member_ `bool bIsPlayOnBlockingEnabled;` — If true then play movie when blocking starts, if false then play movie on loadmap.
- L225 _private member_ `bool bIsSlateThreadAllowed;` — If true then we can use the Slate thread.
- L228 _private member_ `FCriticalSection SyncMechanismCriticalSection;` — Critical section to allow the slate loading thread and the render thread to safely utilize the synchronization mechanism for ticking Slate.
- L231 _private member_ `TSharedPtr<FMoviePlayerWidgetRenderer, ESPMode::ThreadSafe> WidgetRenderer;` — Widget renderer used to tick and paint windows in a thread safe way
- L234 _private member_ `TSharedPtr<class SDPIScaler> UserWidgetDPIScaler;` — DPIScaler parented to the UserWidgetHolder to ensure correct scaling
- L237 _private member_ `float ViewportDPIScale;` — Scale used by UserWidgetDPIScaler.
- L240 _private member_ `int32 BlockingRefCount;` — Counts blocking starts - blocking finishes.
- L242 _private member_ `double LastBlockingTickTime;` — Last time we were able to tick during blocking.
- L244 _private member_ `FDelegateHandle OnAsyncLoadingFlushUpdateDelegateHandle;` — Handle to our async loading update function.
- L248 _private member_ `static TSharedPtr<FDefaultGameMoviePlayer> MoviePlayer;` — Singleton handle

### `Source/Runtime/MoviePlayer/Private/MoviePlayerThreading.h` (Private)


#### class `FSlateLoadingSynchronizationMechanism`  
`class FSlateLoadingSynchronizationMechanism`  
_L16-72_
- desc: This class will handle all the nasty bits about running Slate on a separate thread and then trying to sync it up with the game thread and the render thread simultaneously
- L19 _public prototype_ `FSlateLoadingSynchronizationMechanism( TSharedPtr<FMoviePlayerWidgetRenderer, ESPMode::ThreadSafe> InWidgetRenderer, const TSharedPtr<IMovieStreamer, ESPMode::ThreadSafe>& InMovieStreamer);`
- L22 _public prototype_ `~FSlateLoadingSynchronizationMechanism();`
- L25 _public prototype_ `void Initialize();` — Sets up the locks in their proper initial state for running
- L28 _public prototype_ `void DestroySlateThread();` — Cleans up the slate thread
- L31 _public prototype_ `bool IsSlateDrawPassEnqueued();` — Handles the strict alternation of the slate drawing passes
- L32 _public prototype_ `void SetSlateDrawPassEnqueued();`
- L33 _public prototype_ `void ResetSlateDrawPassEnqueued();`
- L36 _public prototype_ `bool IsSlateMainLoopRunning();` — Handles the counter to determine if the slate thread should keep running
- L37 _public prototype_ `void SetSlateMainLoopRunning();`
- L38 _public prototype_ `void ResetSlateMainLoopRunning();`
- L41 _public prototype_ `void SlateThreadRunMainLoop();` — The main loop to be run from the Slate thread
- L43 _public prototype_ `void SlateThreadInitFailed();` — The main loop could not be initialized
- L48 _private member_ `TAtomic<bool> bMainLoopRunning;` — Used as a spin lock when we're running the primary loading loop, so that we can shutdown safely.
- L53 _private member_ `FThreadSafeCounter IsRunningSlateMainLoop;` — This counter handles running the main loop of the slate thread
- L58 _private member_ `FThreadSafeCounter IsSlateDrawEnqueued;` — This counter handles strict alternation between the slate thread and the render thread for passing Slate render draw passes between each other.
- L63 _private member_ `static FThreadSafeCounter LoadingThreadInstanceCounter;` — This counter is used to generate a unique id for each new instance of the loading thread
- L66 _private member_ `FRunnableThread* SlateLoadingThread;` — The worker thread that will become the Slate thread
- L67 _private member_ `FRunnable* SlateRunnableTask;`
- L69 _private member_ `TSharedPtr<FMoviePlayerWidgetRenderer, ESPMode::ThreadSafe> WidgetRenderer;`
- L71 _private member_ `TSharedPtr<IMovieStreamer, ESPMode::ThreadSafe> MovieStreamer;` — Holds the current MovieStreamer.

### `Source/Runtime/MoviePlayer/Private/NullMoviePlayer.h` (Private)


#### class `FNullGameMoviePlayer`  
`class FNullGameMoviePlayer : public IGameMoviePlayer, public TSharedFromThis<FNullGameMoviePlayer>`  
_L9-75_
- inherits: `IGameMoviePlayer,TSharedFromThis<FNullGameMoviePlayer>`
- desc: An placeholder implementation of the movie player for the editor
- L13 _public function_ `static void Create()`
- L21 _public function_ `static void Destroy()`
- L28 _public function_ `static FNullGameMoviePlayer* Get()`
- L34 _public function_ `virtual void RegisterMovieStreamer(TSharedPtr<class IMovieStreamer, ESPMode::ThreadSafe> InMovieStreamer) override` — IGameMoviePlayer Interface
- L35 _public function_ `virtual void Initialize(class FSlateRenderer& InSlateRenderer, TSharedPtr<SWindow> RenderTarget = nullptr) override`
- L36 _public function_ `virtual void Shutdown() override`
- L37 _public function_ `virtual void PassLoadingScreenWindowBackToGame() const override`
- L38 _public function_ `virtual void SetupLoadingScreen(const FLoadingScreenAttributes& InLoadingScreenAttributes) override`
- L39 _public function_ `virtual bool HasEarlyStartupMovie() const override`
- L40 _public function_ `virtual bool IsInitialized() const override`
- L41 _public function_ `virtual bool PlayEarlyStartupMovies() override`
- L42 _public function_ `virtual bool PlayMovie() override`
- L43 _public function_ `virtual void StopMovie() override`
- L44 _public function_ `virtual void WaitForMovieToFinish(bool bAllowEngineTick = false) override`
- L45 _public function_ `virtual bool IsLoadingFinished() const override`
- L46 _public function_ `virtual bool IsMovieCurrentlyPlaying() const override`
- L47 _public function_ `virtual bool LoadingScreenIsPrepared() const override`
- L48 _public function_ `virtual void SetupLoadingScreenFromIni() override`
- L49 _public function_ `virtual FOnPrepareLoadingScreen& OnPrepareLoadingScreen() override`
- L50 _public function_ `virtual FOnMoviePlaybackStarted& OnMoviePlaybackStarted() override`
- L51 _public function_ `virtual FOnMoviePlaybackTick& OnMoviePlaybackTick() override`
- L52 _public function_ `virtual FOnMoviePlaybackFinished& OnMoviePlaybackFinished() override`
- L53 _public function_ `virtual FOnMovieClipFinished& OnMovieClipFinished() override`
- L54 _public function_ `virtual void SetSlateOverlayWidget(TSharedPtr<SWidget> NewOverlayWidget) override`
- L55 _public function_ `virtual bool WillAutoCompleteWhenLoadFinishes() override`
- L56 _public function_ `virtual FString GetMovieName() override`
- L57 _public function_ `virtual bool IsLastMovieInPlaylist() override`
- L61 _private function_ `FNullGameMoviePlayer()`
- L65 _private member_ `static TSharedPtr<FNullGameMoviePlayer> MoviePlayer;` — Singleton handle
- L68 _private member_ `FOnPrepareLoadingScreen OnPrepareLoadingScreenDelegate;` — Called before a movie is queued up to play to configure the movie player accordingly.
- L70 _private member_ `FOnMoviePlaybackStarted OnMoviePlaybackStartedDelegate;`
- L71 _private member_ `FOnMoviePlaybackTick OnMoviePlaybackTickDelegate;`
- L72 _private member_ `FOnMoviePlaybackFinished OnMoviePlaybackFinishedDelegate;`
- L73 _private member_ `FOnMovieClipFinished OnMovieClipFinishedDelegate;`

### `Source/Runtime/MoviePlayer/Public/MoviePlayer.h` (Public)


#### enum `EMoviePlaybackType`  
`enum EMoviePlaybackType : int`  
_L18-27_
- reflection: `UENUM()`
- L21 _public enumerator_ `MT_Normal UMETA(DisplayName="Normal Playback")` — Normal playback mode.  Play each movie in the play list a single time
- L23 _public enumerator_ `MT_Looped UMETA(DisplayName = "Looped Playback")` — Looped playback mode.  Play all movies in the play list in order then start over until manually canceled
- L25 _public enumerator_ `MT_LoadingLoop UMETA(DisplayName = "Looped Last Playback")` — Alternate Looped mode.  Play all of the movies in the play list and loop just the last movie until loading is finished.
- L26 _public enumerator_ `MT_MAX UMETA(Hidden)`

#### class `FMovieViewport`  
`class FMovieViewport : public ISlateViewport, public TSharedFromThis<FMovieViewport>`  
_L30-69_
- inherits: `ISlateViewport,TSharedFromThis<FMovieViewport>`
- desc: This viewport is a simple interface for the loading to use to display the video textures.
- L33 _public function_ `FMovieViewport() : DefaultSize(ForceInitToZero)`
- L34 _public prototype_ `~FMovieViewport() = default;`
- L37 _public function_ `virtual FIntPoint GetSize() const override` — ISlateViewport interface.
- L43 _public function_ `virtual class FSlateShaderResource* GetViewportRenderTargetTexture() const override`
- L48 _public function_ `virtual bool RequiresVsync() const override`
- L53 _public function_ `void SetTexture(TWeakPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe> InTexture)`
- L59 _public function_ `void SetDefaultSize(FIntPoint InSize)` — Sets the size to use when there is no texture.
- L65 _private member_ `TWeakPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe> SlateTexture;`
- L68 _private member_ `FIntPoint DefaultSize;` — Size to use when we don't have a texture.

#### class `IMovieStreamer`  
`class IMovieStreamer`  
_L73-127_
- desc: Interface for creating a movie streaming player. Should be one instance per platform.
- L81 _public prototype_ `virtual bool Init(const TArray<FString>& MoviePaths, TEnumAsByte<EMoviePlaybackType> inPlaybackType) = 0;`
- L84 _public function_ `virtual void PreviousViewportInterface(const TSharedPtr<ISlateViewport>& PreviousViewportInterface)` — Tells the movie streamer about the viewport interface that was active before us.
- L87 _public prototype_ `virtual void ForceCompletion() = 0;` — Forces the movie streamer to cancel what it's streaming and close.
- L90 _public prototype_ `virtual bool Tick(FRHICommandListBase& RHICmdList, float DeltaTime) = 0;` — Code run every tick for any additional per tick handling of playing the movie. Returns true if done.
- L93 _public prototype_ `virtual TSharedPtr<class ISlateViewport> GetViewportInterface() = 0;` — Gets a viewport interface which will be used to draw the movie.
- L96 _public prototype_ `virtual float GetAspectRatio() const = 0;` — Gets the aspect ratio of the movie frames being streamed.
- L99 _public prototype_ `virtual FString GetMovieName() = 0;` — returns the name of the movie currently being played
- L102 _public prototype_ `virtual bool IsLastMovieInPlaylist() = 0;` — returns true if the movie being played in the last one in the play list
- L105 _public prototype_ `virtual void Cleanup() = 0;` — Called to allow the movie streamer to cleanup any resources once there are no movies left to play.
- L107 _public function_ `virtual FTextureRHIRef GetTexture()`
- L109 _public prototype_ `virtual ~IMovieStreamer() = default;`
- L111 _public prototype_ `DECLARE_EVENT_OneParam(IMovieStreamer, FOnCurrentMovieClipFinished, const FString&) virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() = 0;`
- L114 _public function_ `void BroadcastCurrentMovieClipFinished(const FString& MovieClipThatFinished)`
- L117 _public function_ `virtual void Suspend()` — Called by the engine on suspend/resume
- L118 _public function_ `virtual void Resume()`
- L122 _public function_ `virtual void TickPreEngine()` — Called before the engine tick.
- L124 _public function_ `virtual void TickPostEngine()` — Called after the engine ticks.
- L126 _public function_ `virtual void TickPostRender()` — Called after rendering is finished.

#### struct `FLoadingScreenAttributes`  
`struct FLoadingScreenAttributes`  
_L132-175_
- desc: Struct of all the attributes a loading screen will have.
- L134 _public function_ `FLoadingScreenAttributes() : MinimumLoadingScreenDisplayTime(-1.0f) , bAutoCompleteWhenLoadingCompletes(true) , bMoviesAreSkippable(true) , bWaitForManualStop(false) , bAllowInEarlyStartup(false) , bAllowEngineTick(false) , PlaybackType(EMoviePlaybackType::MT_Normal)`
- L144 _public member_ `TSharedPtr<class SWidget> WidgetLoadingScreen;` — The widget to be displayed on top of the movie or simply standalone if there is no movie.
- L147 _public member_ `TArray<FString> MoviePaths;` — The movie paths local to the game's Content/Movies/ directory we will play.
- L150 _public member_ `float MinimumLoadingScreenDisplayTime;` — The minimum time that a loading screen should be opened for.
- L153 _public member_ `bool bAutoCompleteWhenLoadingCompletes;` — If true, the loading screen will disappear as soon as all movies are played and loading is done.
- L156 _public member_ `bool bMoviesAreSkippable;` — If true, movies can be skipped by clicking the loading screen as long as loading is done.
- L159 _public member_ `bool bWaitForManualStop;` — If true, movie playback continues until Stop is called.
- L162 _public member_ `bool bAllowInEarlyStartup;` — If true loading screens here cannot have any uobjects of any kind or use any engine features at all. This will start the movies very early as a result on platforms that support it
- L165 _public member_ `bool bAllowEngineTick;` — If true, this will call the engine tick while the game thread is stalled waiting for a loading movie to finish. This only works for post-startup load screens and is potentially unsafe
- L168 _public member_ `TEnumAsByte<EMoviePlaybackType> PlaybackType;` — Should we just play back, loop, etc.  NOTE: if the playback type is MT_LoopLast, then bAutoCompleteWhenLoadingCompletes will be togged on when the last movie is hit
- L171 _public prototype_ `bool IsValid() const;` — True if there is either a standalone widget or any movie paths or both.
- L174 _public prototype_ `static TSharedRef<class SWidget> NewTestLoadingScreenWidget();` — Creates a simple test loading screen widget.

#### class `IGameMoviePlayer`  
`class IGameMoviePlayer`  
_L179-285_
- desc: An interface to the movie player we will use for loading screens and gameplay movies
- L183 _public prototype_ `virtual void RegisterMovieStreamer(TSharedPtr<IMovieStreamer, ESPMode::ThreadSafe> InMovieStreamer) = 0;` — Registers a movie streamer with the movie player. Set in the preloading screen stage.
- L186 _public prototype_ `virtual void Initialize(class FSlateRenderer& InSlateRenderer, TSharedPtr<SWindow> RenderTarget = nullptr) = 0;` — Initializes this movie player, creating the startup window and hiding the splash screen. To be called in the launch engine loop.
- L189 _public prototype_ `virtual void Shutdown() = 0;` — Shutsdown the movie player.
- L192 _public prototype_ `virtual void PassLoadingScreenWindowBackToGame() const = 0;` — Passes the loading screen window back to the game to use. For use by the launch engine loop only.
- L195 _public prototype_ `virtual void SetupLoadingScreen(const FLoadingScreenAttributes& InLoadingScreenAttributes) = 0;` — Passes in a slate loading screen UI, movie paths, and any additional data.
- L198 _public prototype_ `DECLARE_EVENT(IGameMoviePlayer, FOnPrepareLoadingScreen) virtual FOnPrepareLoadingScreen& OnPrepareLoadingScreen() = 0;` — Called before playing a movie if the loading screen has not been prepared.
- L204 _public prototype_ `virtual bool HasEarlyStartupMovie() const = 0;` — @return true if the movie player has been set up with an early startup movie
- L211 _public prototype_ `virtual bool PlayEarlyStartupMovies() = 0;` — Play any early start up movies that have been set up @return true if a movie started playing
- L216 _public prototype_ `virtual bool IsInitialized() const = 0;` — @return true if Initialize was called
- L222 _public prototype_ `virtual bool PlayMovie() = 0;` — Starts playing the movie given the last FLoadingScreenAttributes passed in @return true of a movie started playing.
- L227 _public prototype_ `virtual void StopMovie() = 0;` — Stops the currently playing movie, if any.
- L230 _public prototype_ `virtual void WaitForMovieToFinish(bool bAllowEngineTick = false) = 0;` — Call only on the game thread. Spins this thread until the movie stops. If bAllowEngineTick is true, the engine tick may run inside here
- L233 _public prototype_ `virtual bool IsLoadingFinished() const = 0;` — Called from to check if the game thread is finished loading.
- L236 _public prototype_ `virtual bool IsMovieCurrentlyPlaying() const = 0;` — True if the loading screen is currently running (i.e. PlayMovie but no WaitForMovieToFinish has been called).
- L239 _public prototype_ `virtual bool LoadingScreenIsPrepared() const = 0;` — True if we have either slate widgets or a movie to show.
- L242 _public prototype_ `virtual void SetupLoadingScreenFromIni() = 0;` — Sets up an FLoadingScreenAttributes from the game's engine.ini, then calls the virtual SetupLoadingScreen.
- L245 _public prototype_ `virtual FString GetMovieName() = 0;` — returns the name of the movie currently being played
- L248 _public prototype_ `virtual bool IsLastMovieInPlaylist() = 0;` — returns true if the movie being played in the last one in the play list
- L251 _public prototype_ `DECLARE_EVENT(IGameMoviePlayer, FOnMoviePlaybackStarted) virtual FOnMoviePlaybackStarted& OnMoviePlaybackStarted() = 0;` — Callback for when the LoadingScreen setup above in WidgetLoadingScreen is displayed
- L255 _public prototype_ `DECLARE_EVENT_OneParam(IGameMoviePlayer, FOnMoviePlaybackTick, float DeltaTime) virtual FOnMoviePlaybackTick& OnMoviePlaybackTick() = 0;` — Callback for when the game thread is blocked but you want to do some ticking.
- L258 _public prototype_ `DECLARE_EVENT(IGameMoviePlayer, FOnMoviePlaybackFinished) virtual FOnMoviePlaybackFinished& OnMoviePlaybackFinished() = 0;`
- L261 _public prototype_ `DECLARE_EVENT_OneParam(IGameMoviePlayer, FOnMovieClipFinished, const FString&) virtual FOnMovieClipFinished& OnMovieClipFinished() = 0;`
- L265 _public prototype_ `virtual void SetSlateOverlayWidget(TSharedPtr<SWidget> NewOverlayWidget) = 0;` — Allows for a slate overlay widget to be set after playback.
- L267 _public function_ `virtual void SetViewportDPIScale(float InViewportDPIScale)` — Allows for a DPI scale to be set.
- L269 _public function_ `void BroadcastMoviePlaybackFinished()`
- L270 _public function_ `void BroadcastMovieClipFinished(const FString& MovieClipThatFinished)`
- L273 _public prototype_ `virtual bool WillAutoCompleteWhenLoadFinishes() = 0;` — This function shouild return true if the movie will auto-complete the sequence when background loading has finished
- L275 _public prototype_ `virtual ~IGameMoviePlayer() = default;`
- L278 _public function_ `virtual bool IsStartupMoviePlaying() const` — Check if the initial movie(s) is still playing
- L279 _public function_ `virtual void ForceCompletion()`
- L280 _public function_ `virtual void Suspend()`
- L281 _public function_ `virtual void Resume()`
- L284 _public function_ `virtual void SetIsPlayOnBlockingEnabled(bool bIsEnabled)` — Call this to have the MoviePlayer play in blocking sections and not loadmap.

#### Free symbols / members of external scopes

- L111 _delegate_ `DECLARE_EVENT_OneParam(IMovieStreamer, FOnCurrentMovieClipFinished, const FString&) virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() = 0;`
- L198 _delegate_ `DECLARE_EVENT(IGameMoviePlayer, FOnPrepareLoadingScreen) virtual FOnPrepareLoadingScreen& OnPrepareLoadingScreen() = 0;` — Called before playing a movie if the loading screen has not been prepared.
- L251 _delegate_ `DECLARE_EVENT(IGameMoviePlayer, FOnMoviePlaybackStarted) virtual FOnMoviePlaybackStarted& OnMoviePlaybackStarted() = 0;` — Callback for when the LoadingScreen setup above in WidgetLoadingScreen is displayed
- L255 _delegate_ `DECLARE_EVENT_OneParam(IGameMoviePlayer, FOnMoviePlaybackTick, float DeltaTime) virtual FOnMoviePlaybackTick& OnMoviePlaybackTick() = 0;` — Callback for when the game thread is blocked but you want to do some ticking.
- L258 _delegate_ `DECLARE_EVENT(IGameMoviePlayer, FOnMoviePlaybackFinished) virtual FOnMoviePlaybackFinished& OnMoviePlaybackFinished() = 0;`
- L261 _delegate_ `DECLARE_EVENT_OneParam(IGameMoviePlayer, FOnMovieClipFinished, const FString&) virtual FOnMovieClipFinished& OnMovieClipFinished() = 0;`
- L288 _prototype_ `void CreateMoviePlayer();` — Creates the movie player
- L291 _prototype_ `void DestroyMoviePlayer();` — Destroys the movie player
- L294 _prototype_ `IGameMoviePlayer* GetMoviePlayer();` — Gets the movie player singleton for the engine.
- L296 _prototype_ `IGameMoviePlayer& GetMoviePlayerRef();`
- L299 _prototype_ `bool IsMoviePlayerEnabled();` — Returns true if the movie player is enabled.

### `Source/Runtime/MoviePlayer/Public/MoviePlayerSettings.h` (Public)


#### class `UMoviePlayerSettings`  
`class UMoviePlayerSettings : public UObject`  
_L19-37_
- reflection: `UCLASS(config=Game, defaultconfig, MinimalAPI)`
- inherits: `UObject`
- desc: Implements the settings for the Windows target platform.
- L28 _public member_ `bool bWaitForMoviesToComplete;` — `UPROPERTY(globalconfig, EditAnywhere, Category="Movies")` — If enabled, The game waits for startup movies to complete even if loading has finished.
- L32 _public member_ `bool bMoviesAreSkippable;` — `UPROPERTY(globalconfig, EditAnywhere, Category="Movies")` — If enabled, Startup movies can be skipped by the user when a mouse button is pressed.
- L36 _public member_ `TArray<FString> StartupMovies;` — `UPROPERTY(globalconfig, EditAnywhere, Category="Movies")` — Movies to play on startup. Note that these must be in your game's Game/Content/Movies directory.
