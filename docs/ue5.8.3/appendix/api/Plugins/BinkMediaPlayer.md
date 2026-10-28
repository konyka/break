# Plugins / BinkMediaPlayer

- module root: `Plugins/Media/BinkMedia/Source/BinkMediaPlayer`
- headers: 10; symbols: 273
- symbol kinds: class=5, delegate=7, enum=5, enumerator=30, externvar=4, function=20, macro=9, member=100, prototype=90, struct=3
- PrivateDependencyModuleNames: DesktopPlatform, EditorStyle, PropertyEditor, RHI, RenderCore, Renderer, Slate, SlateCore, SourceControl, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DesktopWidgets, Engine, InputCore, MoviePlayer, Projects, Slate, SlateCore

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Private/Assets/BinkMediaTextureResource.h` (Private)


#### struct `FBinkMediaTextureResource`  
`struct FBinkMediaTextureResource : FTextureResource, FRenderTarget, FDeferredUpdateResource`  
_L9-25_
- inherits: `FTextureResource,FRenderTarget,FDeferredUpdateResource`
- L11 _public function_ `FBinkMediaTextureResource(const UBinkMediaTexture* InOwner, EPixelFormat fmt) : Owner(InOwner), PixelFormat(fmt)`
- L16 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;`
- L17 _public prototype_ `virtual void ReleaseRHI() override;`
- L18 _public function_ `virtual FIntPoint GetSizeXY() const override`
- L19 _public prototype_ `virtual void UpdateDeferredResource(FRHICommandListImmediate& RHICmdList, bool bClearRenderTarget = true) override;`
- L21 _public prototype_ `void Clear();`
- L23 _public member_ `const UBinkMediaTexture* Owner;`
- L24 _public member_ `EPixelFormat PixelFormat;`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Private/BinkMediaPlayerPrivate.h` (Private)


#### struct `FBinkOverlayJob`  
`struct FBinkOverlayJob`  
_L47-51_
- desc: Per-frame overlay draw request, populated during UBinkMediaPlayer::Tick and consumed by UBinkFunctionLibrary::Bink_DrawOverlays on the same game thread tick.
- L49 _public member_ `class UBinkMediaPlayer* Player;`
- L50 _public member_ `float ulx, uly, lrx, lry;`
- L50 _public member_ `float ulx, uly, lrx, lry;`
- L50 _public member_ `float ulx, uly, lrx, lry;`
- L50 _public member_ `float ulx, uly, lrx, lry;`

#### Free symbols / members of external scopes

- L23 _externvar_ `extern EPixelFormat bink_force_pixel_format;`
- L24 _prototype_ `extern FString BinkUE4CookOnTheFlyPath(FString path, const TCHAR *filename);`
- L25 _prototype_ `extern bool BinkInitialize();`
- L27 _function_ `static int GetNumSpeakers()`
- L43 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBink, Log, All);`
- L43 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBink, Log, All);`
- L53 _externvar_ `extern TArray<FBinkOverlayJob> PendingBinkOverlays;`
- L62 _prototype_ `void BinkGetHDRSettings(int32& OutTonemap, int32& OutNits);` — Queries HDR CVars on the render thread and returns tonemap mode + output nits. Call from the render thread only.
- L66 _prototype_ `void BinkCloseOnRenderThread(struct BINK*& InOutBnk, struct FBinkTextures*& InOutTextures);` — Closes a Bink handle and frees its textures on the render thread. Nulls out both pointers. Safe to call from the game thread.
- L77 _externvar_ `extern FCriticalSection GBinkHLProcessLock;` — Serializes the BinkHLOpen -> BinkHLRegisterTextureBuffers window against BinkHLProcess. BinkHLOpen publishes the new Bink to the global HL list with NULL plane buffers (BINKNOFRAMEBUFFERS); if the render thread runs BinkHLProcess before the texture buffers are registered, the async decode workers write frame data through those NULL pointers. The HL API assumes a single-threaded pump, but the plugin opens on the game thread while the render thread pumps BinkHLProcess, so this lock provides that serialization. Hold it around any BinkHLOpen+RegisterTextureBuffers sequence and around every BinkHLProcess call.
- L81 _prototype_ `FString BinkGetAndroidAPKPath();` — Retrieves the APK code path via JNI. Returns empty string on failure.

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Private/BinkMoviePlayerSettings.h` (Private)


#### enum `EBinkMoviePlayerBinkBufferModes`  
`enum EBinkMoviePlayerBinkBufferModes : int`  
_L14-26_
- reflection: `UENUM()`
- desc: Enumerates available bink buffering modes.
- L17 _public enumerator_ `MP_Bink_Stream UMETA(DisplayName="Stream")` — Stream the movie off the media during playback (caches about 1 second of video).
- L20 _public enumerator_ `MP_Bink_PreloadAll UMETA(DisplayName="Preload All")` — Loads the whole movie into memory at Open time (will block).
- L23 _public enumerator_ `MP_Bink_StreamUntilResident UMETA(DisplayName="Stream Until Resident")` — Streams the movie into a memory buffer as big as the movie, so it will be preloaded eventually).
- L25 _public enumerator_ `MP_Bink_MAX`

#### enum `EBinkMoviePlayerBinkSoundTrack`  
`enum EBinkMoviePlayerBinkSoundTrack : int`  
_L32-56_
- reflection: `UENUM()`
- desc: Enumerates available used to specify the sounds to open at playback w/ bink movies.
- L35 _public enumerator_ `MP_Bink_Sound_None UMETA(DisplayName="None")` — Don't open any sound tracks snd_track_start not used.
- L38 _public enumerator_ `MP_Bink_Sound_Simple UMETA(DisplayName="Simple")` — Based on filename, OR simply mono or stereo sound in track snd_track_start (default speaker spread).
- L41 _public enumerator_ `MP_Bink_Sound_LanguageOverride UMETA(DisplayName="Language Override")` — Mono or stereo sound in track 0, language track at snd_track_start.
- L44 _public enumerator_ `MP_Bink_Sound_51 UMETA(DisplayName="5.1 Surround")` — 6 mono tracks in tracks snd_track_start[0..5]
- L47 _public enumerator_ `MP_Bink_Sound_51LanguageOverride UMETA(DisplayName="5.1 Surround, Language Override")` — 6 mono tracks in tracks 0..5, center language track at snd_track_start
- L50 _public enumerator_ `MP_Bink_Sound_71 UMETA(DisplayName="7.1 Surround")` — 8 mono tracks in tracks snd_track_start[0..7]
- L53 _public enumerator_ `MP_Bink_Sound_71LanguageOverride UMETA(DisplayName="7.1 Surround, Language Override")` — 8 mono tracks in tracks 0..7, center language track at snd_track_start
- L55 _public enumerator_ `MP_Bink_Sound_MAX`

#### class `UBinkMoviePlayerSettings`  
`class UBinkMoviePlayerSettings : public UObject`  
_L62-92_
- reflection: `UCLASS(config=Game, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the Windows target platform.
- L71 _public member_ `TEnumAsByte<EBinkMoviePlayerBinkBufferModes> BinkBufferMode;` — `UPROPERTY(globalconfig, EditAnywhere, Category="BinkMovies")` — Used to specify the how the video should be buffered.
- L75 _public member_ `TEnumAsByte<EBinkMoviePlayerBinkSoundTrack> BinkSoundTrack;` — `UPROPERTY(globalconfig, EditAnywhere, Category="BinkMovies")` — Used to specify the sounds to open at playback.
- L79 _public member_ `int32 BinkSoundTrackStart;` — `UPROPERTY(globalconfig, EditAnywhere, Category="BinkMovies")` — Used to specify the sounds to open at playback.
- L83 _public member_ `FVector2D BinkDestinationUpperLeft;` — `UPROPERTY(globalconfig, EditAnywhere, Category="BinkMovies")` — Used to specify the render destination rectangle.
- L87 _public member_ `FVector2D BinkDestinationLowerRight;` — `UPROPERTY(globalconfig, EditAnywhere, Category="BinkMovies")` — Used to specify the render destination rectangle.
- L91 _public member_ `TEnumAsByte<EPixelFormat> BinkPixelFormat;` — `UPROPERTY(globalconfig, EditAnywhere, Category="BinkMovies")` — Used to specify the render destination rectangle.

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Private/BinkMovieStreamer.h` (Private)


#### class `FBinkMovieStreamer`  
`class FBinkMovieStreamer : public IMovieStreamer`  
_L14-47_
- inherits: `IMovieStreamer`
- L17 _public prototype_ `FBinkMovieStreamer();`
- L18 _public prototype_ `virtual ~FBinkMovieStreamer();`
- L20 _public prototype_ `virtual bool Init(const TArray<FString>& MoviePaths, TEnumAsByte<EMoviePlaybackType> inPlaybackType) override;`
- L21 _public prototype_ `virtual void ForceCompletion() override;`
- L22 _public prototype_ `virtual bool Tick(FRHICommandListBase& RHICmdList, float DeltaTime) override;`
- L23 _public function_ `virtual TSharedPtr<class ISlateViewport> GetViewportInterface() override`
- L24 _public function_ `virtual float GetAspectRatio() const override`
- L25 _public prototype_ `virtual FString GetMovieName() override;`
- L26 _public prototype_ `virtual bool IsLastMovieInPlaylist() override;`
- L27 _public prototype_ `virtual void Cleanup() override;`
- L28 _public function_ `virtual FTextureRHIRef GetTexture() override`
- L30 _public member_ `FOnCurrentMovieClipFinished OnCurrentMovieClipFinishedDelegate;`
- L31 _public function_ `virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() override`
- L33 _public prototype_ `bool OpenNextMovie();`
- L34 _public prototype_ `void CloseMovie();`
- L36 _public member_ `TArray<FString> StoredMoviePaths;`
- L38 _public member_ `TSharedPtr<FMovieViewport> MovieViewport;`
- L39 _public member_ `TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe> Texture;`
- L40 _public member_ `TArray<TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe>> TextureFreeList;`
- L42 _public member_ `TEnumAsByte<EMoviePlaybackType> PlaybackType;`
- L43 _public member_ `int32 MovieIndex;`
- L45 _public member_ `struct BINK* bnk;` — HBINK handle
- L46 _public member_ `FBinkTextures* bink_textures;` — render-thread GPU texture state (lazily created)

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBinkMoviePlayer, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBinkMoviePlayer, Log, All);`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Private/BinkRHI.h` (Private)


#### struct `FBinkTextures`  
`struct FBinkTextures`  
_L14-81_
- desc: Bink GPU texture state — owns the CPU decode buffers and GPU textures for a single playing Bink video. Created by CreateCPU() or Create(), destroyed by Destroy(). All draw methods must be called on the render thread.
- L19 _public prototype_ `static FBinkTextures* Create(HBINK bink, void* user_ptr = nullptr);` — Full creation (CPU + GPU). Must be called on the render thread.
- L24 _public prototype_ `static FBinkTextures* CreateCPU(HBINK bink, void* user_ptr = nullptr);` — Creates only the CPU-side decode buffers and registers them with BinkHL. Safe to call from the game thread. GPU textures are created lazily on the render thread the first time Draw() is called.
- L27 _public prototype_ `void Destroy();` — Frees all GPU + CPU resources.
- L31 _public prototype_ `void SetRenderTarget(FRHITexture* rt, ERenderTargetLoadAction load_action);`
- L32 _public prototype_ `void SetDrawPosition(float x0, float y0, float x1, float y1);`
- L33 _public prototype_ `void SetDrawCorners(float Ax, float Ay, float Bx, float By, float Cx, float Cy);`
- L34 _public prototype_ `void SetSourceRect(float u0, float v0, float u1, float v1);`
- L35 _public prototype_ `void SetAlphaSettings(float alpha, int32 draw_flags);`
- L36 _public prototype_ `void SetHDRSettings(int32 tonemap, float exposure, int32 out_nits);`
- L39 _public prototype_ `void Draw();` — Draws the current Bink frame to the previously-set render target.
- L43 _public member_ `void* user_ptr = nullptr;`
- L44 _public member_ `S32 video_width = 0, video_height = 0;`
- L44 _public member_ `S32 video_width = 0, video_height = 0;`
- L45 _public member_ `HBINK bink = nullptr;`
- L47 _public member_ `U32 YABufferWidth = 0, YABufferHeight = 0;`
- L47 _public member_ `U32 YABufferWidth = 0, YABufferHeight = 0;`
- L48 _public member_ `U32 ChBufferWidth = 0, ChBufferHeight = 0;`
- L48 _public member_ `U32 ChBufferWidth = 0, ChBufferHeight = 0;`
- L49 _public member_ `S32 NeedAlpha = 0;`
- L50 _public member_ `S32 NeedHDR = 0;`
- L52 _public member_ `U8* Luma[BINKMAXFRAMEBUFFERS] = {};`
- L53 _public member_ `U8* cR[BINKMAXFRAMEBUFFERS] = {};`
- L54 _public member_ `U8* cB[BINKMAXFRAMEBUFFERS] = {};`
- L55 _public member_ `U8* Alpha[BINKMAXFRAMEBUFFERS] = {};`
- L56 _public member_ `U8* HDR[BINKMAXFRAMEBUFFERS] = {};`
- L58 _public member_ `S32 bGpuTexturesCreated = 0;`
- L60 _public member_ `F32 Ax = 0, Ay = 0, Bx = 0, By = 0, Cx = 0, Cy = 0;`
- L60 _public member_ `F32 Ax = 0, Ay = 0, Bx = 0, By = 0, Cx = 0, Cy = 0;`
- L60 _public member_ `F32 Ax = 0, Ay = 0, Bx = 0, By = 0, Cx = 0, Cy = 0;`
- L60 _public member_ `F32 Ax = 0, Ay = 0, Bx = 0, By = 0, Cx = 0, Cy = 0;`
- L60 _public member_ `F32 Ax = 0, Ay = 0, Bx = 0, By = 0, Cx = 0, Cy = 0;`
- L60 _public member_ `F32 Ax = 0, Ay = 0, Bx = 0, By = 0, Cx = 0, Cy = 0;`
- L61 _public member_ `F32 alpha = 0;`
- L62 _public member_ `S32 draw_type = 0;`
- L63 _public member_ `S32 draw_flags = 0;`
- L64 _public member_ `F32 u0 = 0, v0 = 0, u1 = 0, v1 = 0;`
- L64 _public member_ `F32 u0 = 0, v0 = 0, u1 = 0, v1 = 0;`
- L64 _public member_ `F32 u0 = 0, v0 = 0, u1 = 0, v1 = 0;`
- L64 _public member_ `F32 u0 = 0, v0 = 0, u1 = 0, v1 = 0;`
- L66 _public member_ `FTextureRHIRef Ytexture[BINKMAXFRAMEBUFFERS];`
- L67 _public member_ `FTextureRHIRef cRtexture[BINKMAXFRAMEBUFFERS];`
- L68 _public member_ `FTextureRHIRef cBtexture[BINKMAXFRAMEBUFFERS];`
- L69 _public member_ `FTextureRHIRef Atexture[BINKMAXFRAMEBUFFERS];`
- L70 _public member_ `FTextureRHIRef Htexture[BINKMAXFRAMEBUFFERS];`
- L72 _public member_ `S32 tonemap = 0;`
- L73 _public member_ `F32 exposure = 0;`
- L74 _public member_ `F32 out_luma = 0;`
- L76 _public member_ `FRHITexture* RenderTarget = nullptr;`
- L77 _public member_ `ERenderTargetLoadAction RenderTargetLoadAction = ERenderTargetLoadAction::EClear;`
- L80 _private prototype_ `void EnsureGpuTextures();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define BINKMAXFRAMEBUFFERS 2`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Public/BinkFunctionLibrary.h` (Public)


#### class `UBinkFunctionLibrary`  
`class UBinkFunctionLibrary : public UBlueprintFunctionLibrary`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L16 _public prototype_ `static void Bink_DrawOverlays();` — `UFUNCTION(BlueprintCallable, Category = "Bink")`
- L19 _public prototype_ `static FTimespan BinkLoadingMovie_GetDuration();` — `UFUNCTION(BlueprintCallable, Category = "Bink")`
- L22 _public prototype_ `static FTimespan BinkLoadingMovie_GetTime();` — `UFUNCTION(BlueprintCallable, Category = "Bink")`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Public/BinkMediaPlayer.h` (Public)


#### enum `EBinkMediaPlayerBinkBufferModes`  
`enum EBinkMediaPlayerBinkBufferModes : int`  
_L22-34_
- reflection: `UENUM()`
- desc: Enumerates available bink buffering modes.
- L25 _public enumerator_ `BMASM_Bink_Stream UMETA(DisplayName="Stream")` — Stream the movie off the media during playback (caches about 1 second of video).
- L28 _public enumerator_ `BMASM_Bink_PreloadAll UMETA(DisplayName="Preload All")` — Loads the whole movie into memory at Open time (will block).
- L31 _public enumerator_ `BMASM_Bink_StreamUntilResident UMETA(DisplayName="Stream Until Resident")` — Streams the movie into a memory buffer as big as the movie, so it will be preloaded eventually).
- L33 _public enumerator_ `BMASM_Bink_MAX`

#### enum `EBinkMediaPlayerBinkSoundTrack`  
`enum EBinkMediaPlayerBinkSoundTrack : int`  
_L40-64_
- reflection: `UENUM()`
- desc: Enumerates available used to specify the sounds to open at playback w/ bink movies.
- L43 _public enumerator_ `BMASM_Bink_Sound_None UMETA(DisplayName="None")` — Don't open any sound tracks snd_track_start not used.
- L46 _public enumerator_ `BMASM_Bink_Sound_Simple UMETA(DisplayName="Simple")` — Based on filename, OR simply mono or stereo sound in track snd_track_start (default speaker spread).
- L49 _public enumerator_ `BMASM_Bink_Sound_LanguageOverride UMETA(DisplayName="Language Override")` — Mono or stereo sound in track 0, language track at snd_track_start.
- L52 _public enumerator_ `BMASM_Bink_Sound_51 UMETA(DisplayName="5.1 Surround")` — 6 mono tracks in tracks snd_track_start[0..5]
- L55 _public enumerator_ `BMASM_Bink_Sound_51LanguageOverride UMETA(DisplayName="5.1 Surround, Language Override")` — 6 mono tracks in tracks 0..5, center language track at snd_track_start
- L58 _public enumerator_ `BMASM_Bink_Sound_71 UMETA(DisplayName="7.1 Surround")` — 8 mono tracks in tracks snd_track_start[0..7]
- L61 _public enumerator_ `BMASM_Bink_Sound_71LanguageOverride UMETA(DisplayName="7.1 Surround, Language Override")` — 8 mono tracks in tracks 0..7, center language track at snd_track_start
- L63 _public enumerator_ `BMASM_Bink_Sound_MAX`

#### enum `EBinkMediaPlayerBinkDrawStyle`  
`enum EBinkMediaPlayerBinkDrawStyle : int`  
_L70-88_
- reflection: `UENUM()`
- desc: Enumerates available bink buffering modes.
- L73 _public enumerator_ `BMASM_Bink_DS_RenderToTexture UMETA(DisplayName="Render to Texture")` — Renders movie to the destination texture (default UE4 functionality)
- L76 _public enumerator_ `BMASM_Bink_DS_OverlayFillScreenWithAspectRatio UMETA(DisplayName="Overlay Fill Screen with Aspect Ratio")` — Renders movie in an overlay (UE4 bypass) and corrects for movie aspect ratio.
- L79 _public enumerator_ `BMASM_Bink_DS_OverlayOriginalMovieSize UMETA(DisplayName="Overlay Fill Original Movie Size")` — Renders movie in an overlay (UE4 bypass), displaying the original movie size and not stretching to fill frame
- L82 _public enumerator_ `BMASM_Bink_DS_OverlayFillScreen UMETA(DisplayName="Overlay Fill Screen")` — Renders movie in an overlay (UE4 bypass), filling the entire destination rectangle
- L85 _public enumerator_ `BMASM_Bink_DS_OverlaySpecificDestinationRectangle UMETA(DisplayName="Overlay Specific Destination Rectangle")` — Renders movie in an overlay (UE4 bypass), rendering to the specific rectangle specified (same as FillScreen)
- L87 _public enumerator_ `BMASM_Bink_DS_MAX`

#### class `UBinkMediaPlayer`  
`class UBinkMediaPlayer : public UObject, public FTickableGameObject`  
_L109-487_
- reflection: `UCLASS(BlueprintType, hidecategories=(Object))`
- inherits: `UObject,FTickableGameObject`
- desc: Implements a media player asset that can play movies and other media. This class is represents a media URL along with a corresponding media player for exposing media playback functionality to the Engine and to Blueprints.
- L122 _public prototype_ `bool CanPause() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether media playback can be paused right now. Playback can be paused if the media supports pausing and if it is currently playing. @return true if pausing playback can be paused, false otherwise. @see CanPlay, Pause
- L131 _public prototype_ `bool CanPlay() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether media playback can be started right now. @return true if playback can be started, false otherwise. @see CanPause, Play
- L140 _public prototype_ `FTimespan GetDuration() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Gets the media's duration. @return A time span representing the duration. @see GetTime, Seek
- L149 _public prototype_ `float GetRate() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Gets the media's current playback rate. @return The playback rate. @see SetRate, SupportsRate
- L158 _public prototype_ `FTimespan GetTime() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Gets the media's current playback time. @return Playback time. @see GetDuration, Seek
- L167 _public prototype_ `const FString& GetUrl() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Gets the URL of the currently loaded media, if any. @return Media URL, or empty string if no media was loaded. @see OpenUrl
- L176 _public prototype_ `bool IsLooping() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether playback is looping. @return true if looping, false otherwise. @see SetLooping
- L185 _public prototype_ `bool IsPaused() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether playback is currently paused. @return true if playback is paused, false otherwise. @see CanPause, IsPlaying, IsStopped, Pause
- L194 _public prototype_ `bool IsPlaying() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether playback has started. @return true if playback has started, false otherwise. @see CanPlay, IsPaused, IsStopped, Play
- L203 _public prototype_ `bool IsStopped() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether playback has stopped. @return true if playback has stopped, false otherwise. @see IsPaused, IsPlaying, Stop
- L212 _public prototype_ `bool IsGotoing() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether playback is "GoTo'ing". @return true if playback is gotoing, false otherwise. @see IsPaused, IsPlaying, Stop
- L222 _public prototype_ `bool OpenUrl( const FString& NewUrl );` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Opens the specified media URL. @param NewUrl The URL to open. @return true on success, false otherwise. @see GetUrl
- L232 _public prototype_ `void CloseUrl();` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Closes the specified media URL. @param NewUrl The URL to open. @return true on success, false otherwise. @see GetUrl
- L243 _public prototype_ `bool Pause();` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Pauses media playback. This is the same as setting the playback rate to 0.0. @return true if playback is being paused, false otherwise. @see CanPause, Play, Rewind, Seek, SetRate
- L254 _public prototype_ `bool Play();` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Starts media playback. This is the same as setting the playback rate to 1.0. @return true if playback is starting, false otherwise. @see CanPlay, Pause, Rewind, Seek, SetRate
- L265 _public prototype_ `bool Rewind();` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Rewinds the media to the beginning. This is the same as seeking to zero time. @return true if rewinding, false otherwise. @see GetTime, Pause, Play, Seek
- L275 _public prototype_ `bool Seek( const FTimespan& InTime );` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Seeks to the specified playback time. @param InTime The playback time to set. @return true on success, false otherwise. @see GetTime, Rewind
- L285 _public prototype_ `bool SetLooping( bool InLooping );` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Enables or disables playback looping. @param Looping Whether playback should be looped. @return true on success, false otherwise. @see IsLooping
- L295 _public prototype_ `bool SetRate( float Rate );` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Changes the media's playback rate. @param Rate The playback rate to set. @return true on success, false otherwise. @see GetRate, SupportsRate
- L303 _public prototype_ `void SetVolume( float Rate );` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Changes the media's volume @param Rate The playback volume to set. 0 to 1
- L312 _public function_ `void Stop()` — `UFUNCTION(BlueprintCallable, Category = "Media|BinkMediaPlayer")` — Stops playback and unloads the video from memory. If you want to start the video again you'll need to call InitializePlayer. MediaEvent will broadcast EMediaEvent::MediaClosed. @return true on success, false otherwise. @see InitializePlayer, IsStopped, Play
- L322 _public prototype_ `bool SupportsRate( float Rate, bool Unthinned ) const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether the specified playback rate is supported. @param Rate The playback rate to check. @param Unthinned Whether no frames should be dropped at the given rate. @see SupportsScrubbing, SupportsSeeking
- L331 _public prototype_ `bool SupportsScrubbing() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether the currently loaded media supports scrubbing. @return true if scrubbing is supported, false otherwise. @see SupportsRate, SupportsSeeking
- L340 _public prototype_ `bool SupportsSeeking() const;` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether the currently loaded media can jump to a certain position. @return true if seeking is supported, false otherwise. @see SupportsRate, SupportsScrubbing
- L349 _public function_ `bool IsInitialized() const` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Checks whether this player has been initialized with a media source. @return true if a media source is associated with this player. @see OpenUrl
- L355 _public prototype_ `void Draw(UTexture *texture, bool tonemap=false, int out_nits=10000, float alpha=1, bool srgb_decode=false, bool hdr=false);` — `UFUNCTION(BlueprintCallable, Category="Media|BinkMediaPlayer")` — Draws this bink to the specified texture
- L358 _public prototype_ `DECLARE_EVENT(UBinkMediaPlayer, FOnMediaChanged) FOnMediaChanged& OnMediaChanged();` — Gets an event delegate that is invoked when media has been opened or closed.
- L363 _public member_ `FOnBinkMediaPlayerMediaClosed OnMediaClosed;` — `UPROPERTY(BlueprintAssignable, Category="Media|BinkMediaPlayer")` — Holds a delegate that is invoked when a media source has been closed.
- L367 _public member_ `FOnBinkMediaPlayerMediaOpened OnMediaOpened;` — `UPROPERTY(BlueprintAssignable, Category="Media|BinkMediaPlayer")` — Holds a delegate that is invoked when a media source has been opened.
- L371 _public member_ `FOnBinkMediaPlayerMediaReachedEnd OnMediaReachedEnd;` — `UPROPERTY(BlueprintAssignable, Category="Media|BinkMediaPlayer")` — Holds a delegate that is invoked when a media source has been opened.
- L375 _public member_ `FOnBinkMediaPlayerMediaEvent OnPlaybackSuspended;` — `UPROPERTY(BlueprintAssignable, Category = "Media|BinkMediaPlayer", meta = (HideInDetailPanel))` — A delegate that is invoked when media playback has been suspended.
- L384 _public prototype_ `virtual void BeginDestroy() override;`
- L385 _public prototype_ `virtual FString GetDesc() override;`
- L386 _public prototype_ `virtual void PostLoad() override;`
- L389 _public prototype_ `virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;`
- L393 _public prototype_ `void InitializePlayer();` — Initializes the media player.
- L397 _public member_ `uint32 Looping:1;` — `UPROPERTY(EditAnywhere, Category=Playback)` — Whether playback should loop when it reaches the end.
- L401 _public member_ `uint32 StartImmediately:1;` — `UPROPERTY(EditAnywhere, Category=Playback)` — Whether playback start immediately, or wait for blueprint to start it.
- L405 _public member_ `uint32 DelayedOpen:1;` — `UPROPERTY(EditAnywhere, Category=Playback)` — To reduce memory use, don't immediately open the bink until it is first played.
- L409 _public member_ `FVector2D BinkDestinationUpperLeft;` — `UPROPERTY(EditAnywhere, Category=Playback)` — Used to specify the sounds to open at playback.
- L413 _public member_ `FVector2D BinkDestinationLowerRight;` — `UPROPERTY(EditAnywhere, Category=Playback)` — Used to specify the sounds to open at playback.
- L417 _public member_ `FString URL;` — `UPROPERTY(EditAnywhere, Category=Source)` — The path or URL to the media file to be played.
- L421 _public member_ `TEnumAsByte<EBinkMediaPlayerBinkBufferModes> BinkBufferMode;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Source)` — Used to specify the how the video should be buffered.
- L425 _public member_ `TEnumAsByte<EBinkMediaPlayerBinkSoundTrack> BinkSoundTrack;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Source)` — Used to specify the sounds to open at playback.
- L429 _public member_ `int32 BinkSoundTrackStart;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Source)` — Used to specify the sounds to open at playback.
- L433 _public member_ `TEnumAsByte<EBinkMediaPlayerBinkDrawStyle> BinkDrawStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Source)` — Used to specify how the movie is drawn.
- L437 _public member_ `int32 BinkLayerDepth;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Source)` — Used to specify the render order.
- L440 _public member_ `TEnumAsByte<EBinkMediaPlayerBinkBufferModes> CurrentBinkBufferMode;` — Holds the bink buffer mode of the currently loaded media source.
- L443 _public member_ `TEnumAsByte<EBinkMediaPlayerBinkSoundTrack> CurrentBinkSoundTrack;` — Holds the bink sound track of the currently loaded media source.
- L446 _public member_ `int32 CurrentBinkSoundTrackStart;` — Holds the bink sound track start of the currently loaded media source.
- L449 _public prototype_ `void HandleMediaPlayerMediaClosed();` — Callback for when the media player has closed a media source.
- L452 _public prototype_ `void HandleMediaPlayerMediaOpened( FString OpenedUrl );` — Callback for when the media player has opened a new media source.
- L455 _public member_ `FString CurrentUrl;` — Note - not serialized.
- L456 _public member_ `EBinkMediaPlayerBinkDrawStyle CurrentDrawStyle;`
- L457 _public member_ `int32 CurrentLayerDepth;`
- L458 _public member_ `int32 CurrentHasSubtitles;`
- L461 _public member_ `FOnMediaChanged MediaChangedEvent;` — Holds a delegate that is executed when media has been opened or closed.
- L467 _public prototype_ `void Tick(float DeltaTime);`
- L468 _public function_ `bool IsTickableInEditor() const`
- L469 _public function_ `TStatId GetStatId() const`
- L470 _public function_ `bool IsTickable() const`
- L472 _public prototype_ `bool Open(const FString& Url);`
- L473 _public prototype_ `void Close();`
- L474 _public function_ `bool IsReady() const`
- L475 _public prototype_ `void UpdateTexture(const UTexture* tex, FRHICommandListImmediate &RHICmdList, FTextureRHIRef ref, void *nativePtr, int width, int height, bool isEditor, bool tonemap, int output_nits, float alpha, bool srgb_decode, bool is_hdr);`
- L478 _public prototype_ `FIntPoint GetDimensions() const;`
- L479 _public prototype_ `float GetFrameRate() const;`
- L481 _public member_ `struct BINK *bnk;` — HBINK handle (struct BINK* as defined in binktiny.h)
- L482 _public member_ `FBinkTextures *bink_textures;` — render-thread GPU texture state (lazily created)
- L483 _public member_ `bool paused;`
- L484 _public member_ `bool reached_end;`
- L485 _public member_ `FDelegateHandle overlayHook;`

#### Free symbols / members of external scopes

- L15 _externvar_ `extern EPixelFormat bink_force_pixel_format;`
- L16 _prototype_ `extern FString BinkUE4CookOnTheFlyPath(FString path, const TCHAR *filename);`
- L91 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBinkMediaPlayerMediaClosed);` — Multicast delegate that is invoked when a media player's media has been closed.
- L91 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBinkMediaPlayerMediaClosed);` — Multicast delegate that is invoked when a media player's media has been closed.
- L94 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBinkMediaPlayerMediaOpened, FString, OpenedUrl);` — Multicast delegate that is invoked when a media player's media has been opened.
- L94 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBinkMediaPlayerMediaOpened, FString, OpenedUrl);` — Multicast delegate that is invoked when a media player's media has been opened.
- L97 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBinkMediaPlayerMediaReachedEnd);` — Multicast delegate that is invoked when a media player's media has finished playing.
- L97 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBinkMediaPlayerMediaReachedEnd);` — Multicast delegate that is invoked when a media player's media has finished playing.
- L100 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBinkMediaPlayerMediaEvent);` — Multicast delegate that is invoked when a media event occurred in the player.
- L100 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBinkMediaPlayerMediaEvent);` — Multicast delegate that is invoked when a media event occurred in the player.
- L358 _delegate_ `DECLARE_EVENT(UBinkMediaPlayer, FOnMediaChanged) FOnMediaChanged& OnMediaChanged();` — Gets an event delegate that is invoked when media has been opened or closed.

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Public/BinkMediaTexture.h` (Public)


#### class `UBinkMediaTexture`  
`class UBinkMediaTexture : public UTexture`  
_L22-103_
- reflection: `UCLASS(hidecategories=(Compression, LevelOfDetail, Object))`
- inherits: `UTexture`
- desc: Implements a texture asset for rendering video tracks from UBinkMediaPlayer assets. note: derives directly from UTexture, not from UTexture2D or UTexture2DDynamic maybe should have been UTexture2DDynamic?
- L28 _private member_ `TEnumAsByte<TextureAddress> AddressX;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MediaTexture, AssetRegistrySearchable)` — The addressing mode to use for the X axis.
- L32 _private member_ `TEnumAsByte<TextureAddress> AddressY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MediaTexture, AssetRegistrySearchable)` — The addressing mode to use for the Y axis.
- L34 _private prototype_ `~UBinkMediaTexture();`
- L38 _private prototype_ `virtual FTextureResource* CreateResource() override;`
- L39 _private function_ `virtual EMaterialValueType GetMaterialType() const override`
- L40 _private function_ `virtual float GetSurfaceWidth() const override`
- L41 _private function_ `virtual float GetSurfaceHeight() const override`
- L42 _private function_ `virtual float GetSurfaceDepth() const override`
- L43 _private function_ `virtual uint32 GetSurfaceArraySize() const override`
- L44 _private function_ `virtual ETextureClass GetTextureClass() const`
- L48 _private prototype_ `virtual void BeginDestroy() override;`
- L49 _private prototype_ `virtual void FinishDestroy() override;`
- L50 _private prototype_ `virtual FString GetDesc() override;`
- L51 _private function_ `virtual bool IsReadyForFinishDestroy() override`
- L52 _private prototype_ `virtual void PostLoad() override;`
- L55 _private prototype_ `virtual void PreEditChange( FProperty* PropertyAboutToChange ) override;`
- L56 _private prototype_ `virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;`
- L65 _private prototype_ `void SetMediaPlayer( UBinkMediaPlayer* InMediaPlayer );` — `UFUNCTION(BlueprintCallable, Category="Media|MediaTexture")` — Sets the media player asset to be used for this texture. @param InMediaPlayer The asset to set.
- L71 _private prototype_ `void Clear();` — `UFUNCTION(BlueprintCallable, Category="Media|MediaTexture")` — Clears this texture to transparent-black.
- L76 _private member_ `TObjectPtr<UBinkMediaPlayer> MediaPlayer;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MediaPlayer)` — The MediaPlayer asset to stream video from.
- L80 _private member_ `TEnumAsByte<EPixelFormat> PixelFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MediaPlayer)` — The Pixel Format for the texture.
- L84 _private member_ `bool Tonemap;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MediaPlayer)` — Whether to enable tonemaping for the video.
- L88 _private member_ `float OutputNits;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MediaPlayer)` — When tonemapping, set this for to desired output nits capability for the current display. Typically 80 for SDR, or 2000 for HDR.
- L92 _private member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MediaPlayer)` — alpha_value is just a constant blend value for entire video frame. 1 (default) opaque, 0 fully transparent.
- L96 _private member_ `bool DecodeSRGB;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=MediaPlayer)` — Enable decoding of sRGB to Linear inside Bink when drawing to this texture. You could use this when rendering to a texture format which doesn't support sRGB for example.
- L98 _private prototype_ `void InitializeTrack();`
- L99 _private prototype_ `void HandleMediaPlayerMediaChanged();`
- L100 _private member_ `FIntPoint CachedDimensions;`
- L101 _private member_ `UBinkMediaPlayer *CurrentMediaPlayer;`
- L102 _private member_ `FRenderCommandFence* ReleasePlayerFence;`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Public/BinkUE.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define BINKPLUGIN_UE4_H`
- L11 _macro_ `#define BINKCONTENTPATH FPaths::ProjectContentDir()`
- L15 _macro_ `#define BINKMOVIEPATH BINKCONTENTPATH + TEXT("Movies/")`
- L19 _macro_ `#define BINKTEMPPATH FPaths::ProjectSavedDir() + TEXT("Bink/")`

### `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Public/binkplugin_ue4.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define BINKPLUGIN_UE4_H`
- L11 _macro_ `#define BINKCONTENTPATH FPaths::ProjectContentDir()`
- L15 _macro_ `#define BINKMOVIEPATH BINKCONTENTPATH + TEXT("Movies/")`
- L19 _macro_ `#define BINKTEMPPATH FPaths::ProjectSavedDir() + TEXT("Bink/")`
