# Plugins / PreLoadScreenMoviePlayer

- module root: `Plugins/Runtime/PreLoadScreenMoviePlayer/Source/PreLoadScreenMoviePlayer`
- headers: 4; symbols: 60
- symbol kinds: class=3, enum=1, enumerator=4, function=12, member=15, prototype=24, struct=1
- PrivateDependencyModuleNames: Analytics, AnalyticsET, ApplicationCore, BuildPatchServices, Core, CoreUObject, Engine, HTTP, InputCore, Json, MoviePlayer, PreLoadScreen, Projects, RHI, RenderCore, Slate, SlateCore

### `Plugins/Runtime/PreLoadScreenMoviePlayer/Source/PreLoadScreenMoviePlayer/Public/MoviePlayerAttributes.h` (Public)


#### enum `EMovieScreenPlaybackType`  
`enum EMovieScreenPlaybackType : int`  
_L11-20_
- reflection: `UENUM()`
- L14 _public enumerator_ `MT_MS_Normal UMETA(DisplayName = "Normal Playback")` — Normal playback mode.  Play each movie in the play list a single time
- L16 _public enumerator_ `MT_MS_Looped UMETA(DisplayName = "Looped Playback")` — Looped playback mode.  Play all movies in the play list in order then start over until manually canceled
- L18 _public enumerator_ `MT_MS_LoadingLoop UMETA(DisplayName = "Looped Last Playback")` — Alternate Looped mode.  Play all of the movies in the play list and loop just the last movie until loading is finished.
- L19 _public enumerator_ `MT_MS_MAX UMETA(Hidden)`

#### struct `FPreLoadMovieAttributes`  
`struct FPreLoadMovieAttributes`  
_L23-52_
- desc: Struct of all the attributes a loading screen will have.
- L25 _public function_ `FPreLoadMovieAttributes() : MinimumLoadingScreenDisplayTime(-1.0f) , bAutoCompleteWhenLoadingCompletes(true) , bMoviesAreSkippable(true) , bWaitForManualStop(false) , PlaybackType(EMovieScreenPlaybackType::MT_MS_Normal)`
- L33 _public member_ `TArray<FString> MoviePaths;` — The movie paths local to the game's Content/Movies/ directory we will play.
- L36 _public member_ `float MinimumLoadingScreenDisplayTime;` — The minimum time that a loading screen should be opened for.
- L39 _public member_ `bool bAutoCompleteWhenLoadingCompletes;` — If true, the loading screen will disappear as soon as all movies are played and loading is done.
- L42 _public member_ `bool bMoviesAreSkippable;` — If true, movies can be skipped by clicking the loading screen as long as loading is done.
- L45 _public member_ `bool bWaitForManualStop;` — If true, movie playback continues until Stop is called.
- L48 _public member_ `TEnumAsByte<EMovieScreenPlaybackType> PlaybackType;` — Should we just play back, loop, etc.  NOTE: if the playback type is MT_LoopLast, then bAutoCompleteWhenLoadingCompletes will be togged on when the last movie is hit
- L51 _public function_ `bool IsValid() const` — True if any movie paths.

### `Plugins/Runtime/PreLoadScreenMoviePlayer/Source/PreLoadScreenMoviePlayer/Public/PreLoadMoviePlayerModule.h` (Public)


#### class `IPreLoadMoviePlayerScreenModule`  
`class IPreLoadMoviePlayerScreenModule : public IModuleInterface`  
_L14-47_
- inherits: `IModuleInterface`
- desc: Module interface for handling any PreLoad Movie Player Screens. Mainly used to play movies before/during engine load.
- L23 _public function_ `static inline IPreLoadMoviePlayerScreenModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L42 _public function_ `static inline const FName GetModuleName()` — Simple Getter for the static name of this module @return The Module Name as const FName

### `Plugins/Runtime/PreLoadScreenMoviePlayer/Source/PreLoadScreenMoviePlayer/Public/PreLoadMoviePlayerModuleBase.h` (Public)


#### class `FPreLoadMoviePlayerScreenModuleBase`  
`class FPreLoadMoviePlayerScreenModuleBase : public IPreLoadMoviePlayerScreenModule`  
_L8-27_
- inherits: `IPreLoadMoviePlayerScreenModule`
- L13 _public prototype_ `virtual void StartupModule() override;` — IPreLoadMoviePlayerScreenModule Interface
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public function_ `virtual bool IsGameModule() const override`
- L21 _public prototype_ `virtual void RegisterMovieStreamer(TSharedPtr<class IMovieStreamer, ESPMode::ThreadSafe> InMovieStreamer);`
- L22 _public prototype_ `virtual void UnRegisterMovieStreamer(TSharedPtr<class IMovieStreamer, ESPMode::ThreadSafe> InMovieStreamer);`
- L23 _public prototype_ `virtual void CleanUpMovieStreamer();`
- L26 _private member_ `TSharedPtr<FPreLoadMoviePlayerScreenBase> MoviePreLoadScreen;`

### `Plugins/Runtime/PreLoadScreenMoviePlayer/Source/PreLoadScreenMoviePlayer/Public/PreLoadMoviePlayerScreenBase.h` (Public)


#### class `FPreLoadMoviePlayerScreenBase`  
`class FPreLoadMoviePlayerScreenBase : public FPreLoadScreenBase`  
_L15-76_
- inherits: `FPreLoadScreenBase`
- L19 _public prototype_ `virtual void OnPlay(TWeakPtr<SWindow> TargetWindow) override;`
- L20 _public prototype_ `virtual void OnStop() override;`
- L21 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L22 _public prototype_ `virtual void RenderTick(FRHICommandListImmediate& RHICmdList, float DeltaTime) override;`
- L24 _public prototype_ `virtual void Init() override;`
- L26 _public function_ `virtual TSharedPtr<SWidget> GetWidget() override`
- L27 _public function_ `virtual const TSharedPtr<const SWidget> GetWidget() const override`
- L29 _public prototype_ `virtual void CleanUp() override;`
- L31 _public function_ `virtual void SetMovieAttributes(const FPreLoadMovieAttributes& MovieAttributesIn)`
- L34 _public function_ `virtual bool IsDone() const override` — Default behavior is just to see if we have an active widget. Should really overload with our own behavior to see if we are done displaying
- L36 _public prototype_ `virtual bool MovieStreamingIsPrepared() const;`
- L37 _public prototype_ `virtual FReply OnLoadingScreenMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& PointerEvent);`
- L38 _public prototype_ `virtual FReply OnLoadingScreenKeyDown(const FGeometry& Geometry, const FKeyEvent& KeyEvent);`
- L41 _public prototype_ `virtual FVector2D GetMovieSize() const;` — Callbacks for movie viewport
- L42 _public prototype_ `virtual FOptionalSize GetMovieWidth() const;`
- L43 _public prototype_ `virtual FOptionalSize GetMovieHeight() const;`
- L44 _public prototype_ `virtual EVisibility GetSlateBackgroundVisibility() const;`
- L45 _public prototype_ `virtual EVisibility GetViewportVisibility() const;`
- L47 _public prototype_ `virtual bool IsMovieStreamingFinished() const;`
- L49 _public function_ `FPreLoadMoviePlayerScreenBase()`
- L50 _public function_ `virtual ~FPreLoadMoviePlayerScreenBase() override`
- L52 _public prototype_ `virtual void InitSettingsFromConfig(const FString& ConfigFileName) override;`
- L54 _public prototype_ `virtual void RegisterMovieStreamer(TSharedPtr<IMovieStreamer, ESPMode::ThreadSafe> MovieStreamerIn);`
- L57 _protected prototype_ `FReply OnAnyDown();`
- L60 _protected member_ `double LastPlayTime;` — The last time a movie was started
- L63 _protected member_ `FPreLoadMovieAttributes MovieAttributes;` — Attributes of the loading screen we are currently displaying
- L65 _protected member_ `TSharedPtr<IMovieStreamer, ESPMode::ThreadSafe> MovieStreamer;`
- L66 _protected member_ `TSharedPtr<SViewport> MovieViewport;`
- L67 _protected member_ `TSharedPtr<SWidget> MoviePlayerContents;`
- L70 _protected member_ `FThreadSafeCounter MovieStreamingIsDone;` — True if all movies have successfully streamed and completed
- L73 _protected member_ `bool bUserCalledFinish;` — User has called finish (needed if LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes is off)
- L75 _protected member_ `bool bInitialized;`

#### Free symbols / members of external scopes

- L11 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogPreloadMoviePlayer, Log, All);`
