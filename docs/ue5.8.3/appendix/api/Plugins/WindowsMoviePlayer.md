# Plugins / WindowsMoviePlayer

- module root: `Plugins/Runtime/WindowsMoviePlayer/Source/WindowsMoviePlayer`
- headers: 2; symbols: 80
- symbol kinds: class=3, delegate=1, function=20, member=27, prototype=28, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, MoviePlayer, RHI, RenderCore, Slate, SlateCore
- PrivateIncludePathModuleNames: HeadMountedDisplay, Media

### `Plugins/Runtime/WindowsMoviePlayer/Source/WindowsMoviePlayer/Private/WindowsMovieStreamer.h` (Private)


#### class `FMediaFoundationMovieStreamer`  
`class FMediaFoundationMovieStreamer : public IMovieStreamer`  
_L20-88_
- inherits: `IMovieStreamer`
- desc: The Movie Streamer is what is registered to the global movie player for Windows
- L23 _public prototype_ `FMediaFoundationMovieStreamer();`
- L24 _public prototype_ `~FMediaFoundationMovieStreamer();`
- L27 _public prototype_ `virtual bool Init(const TArray<FString>& MoviePaths, TEnumAsByte<EMoviePlaybackType> inPlaybackType) override;` — IMovieStreamer interface
- L28 _public prototype_ `virtual void ForceCompletion() override;`
- L29 _public prototype_ `virtual bool Tick(FRHICommandListBase& RHICmdList, float DeltaTime) override;`
- L30 _public function_ `virtual TSharedPtr<class ISlateViewport> GetViewportInterface() override`
- L34 _public function_ `virtual float GetAspectRatio() const override`
- L38 _public prototype_ `virtual void Cleanup() override;`
- L40 _public prototype_ `virtual FString GetMovieName() override;`
- L41 _public prototype_ `virtual bool IsLastMovieInPlaylist() override;`
- L43 _public member_ `FOnCurrentMovieClipFinished OnCurrentMovieClipFinishedDelegate;`
- L44 _public function_ `virtual FOnCurrentMovieClipFinished& OnCurrentMovieClipFinished() override`
- L46 _public function_ `virtual FTextureRHIRef GetTexture() override`
- L50 _private prototype_ `bool OpenNextMovie();` — Opens up the next movie in the movie path queue
- L52 _private prototype_ `void CloseMovie();` — Closes the currently running video
- L54 _private prototype_ `void CleanupRenderingResources();` — Cleans up rendering resources once movies are done playing
- L56 _private prototype_ `void ConvertSample(FRHICommandList& RHICmdList);` — Use shader to generate final image
- L60 _private member_ `TArray<FString> StoredMoviePaths;` — A list of all the stored movie paths we have enqueued for playing
- L63 _private member_ `TEnumAsByte<EMoviePlaybackType> PlaybackType;` — if true, this sequence will loop when finsihed
- L66 _private member_ `int32 MovieIndex;` — The index in to the playlist (StoredMoviePaths) that is currently playing
- L69 _private member_ `TArray<uint8> TextureData;` — Texture and viewport data for displaying to Slate
- L70 _private member_ `TSharedPtr<FMovieViewport> MovieViewport;`
- L71 _private member_ `TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe> Texture;`
- L77 _private member_ `TArray<TSharedPtr<FSlateTexture2DRHIRef, ESPMode::ThreadSafe>> TextureFreeList;` — List of textures pending deletion, need to keep this list because we can't immediately destroy them since they could be getting used on the main thread
- L80 _private member_ `TRefCountPtr<FRHITexture> InputTarget;` — Input texture for conversion shader
- L83 _private member_ `class FVideoPlayer* VideoPlayer;` — The video player and sample grabber for use of Media Foundation
- L84 _private member_ `class FSampleGrabberCallback* SampleGrabberCallback;`
- L87 _private member_ `bool bUseSound;` — Defaults to true, modified to false if video fails to play allowing a retry without sound

#### struct `FMovieTrackFormat`  
`struct FMovieTrackFormat`  
_L91-106_
- desc: Video track details
- L94 _public function_ `FMovieTrackFormat() : BufferDim(FIntPoint(0, 0)), BufferStride(0), OutputDim(FIntPoint(0, 0)), SampleFormat(EMediaTextureSampleFormat::Undefined)`
- L102 _public member_ `FIntPoint BufferDim;`
- L103 _public member_ `uint32 BufferStride;`
- L104 _public member_ `FIntPoint OutputDim;`
- L105 _public member_ `EMediaTextureSampleFormat SampleFormat;`

#### class `FVideoPlayer`  
`class FVideoPlayer : public IMFAsyncCallback`  
_L109-180_
- inherits: `IMFAsyncCallback`
- desc: The video player is the class which handles all the loading and playing of videos
- L112 _public function_ `FVideoPlayer() : RefCount(1) , MediaSession(NULL) , MediaSource(NULL) , MovieIsFinished(0) , CloseIsPosted(0) , bFailedToCreateMediaSink(false)`
- L122 _public function_ `virtual ~FVideoPlayer()`
- L129 _public prototype_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object);` — IUnknown interface
- L130 _public prototype_ `STDMETHODIMP_(ULONG) AddRef();`
- L131 _public prototype_ `STDMETHODIMP_(ULONG) Release();`
- L134 _public function_ `STDMETHODIMP GetParameters(unsigned long*, unsigned long*)` — IMFAsyncCallback interface
- L135 _public prototype_ `STDMETHODIMP Invoke(IMFAsyncResult* AsyncResult);`
- L138 _public prototype_ `FIntPoint OpenFile(const FString& FilePath, class FSampleGrabberCallback* SampleGrabberCallback, bool bUseSound);` — Opens the specified file, and returns the video dimensions
- L140 _public prototype_ `void StartPlayback();` — Starts the video player playback
- L142 _public prototype_ `void Shutdown();` — Shuts the video player down, destroying all threads with it
- L145 _public function_ `bool MovieIsRunning() const` — True if the movie is still playing and rendering frames
- L147 _public function_ `const FMovieTrackFormat& GetVideoTrackFormat() const`
- L150 _public function_ `bool FailedToCreateMediaSink() const` — True when there was an error related to creating a media sink (MESessionTopologySet event received with status MF_E_CANNOT_CREATE_SINK)
- L154 _private prototype_ `FIntPoint SetPlaybackTopology(class FSampleGrabberCallback* SampleGrabberCallback, bool bUseSound);` — Sets up the topology of all the nodes in the media session, returning the video dimensions
- L156 _private prototype_ `FIntPoint AddStreamToTopology(IMFTopology* Topology, IMFPresentationDescriptor* PresentationDesc, IMFStreamDescriptor* StreamDesc, class FSampleGrabberCallback* SampleGrabberCallback, bool bUseSound);` — Adds a single audio or video stream to the passed in topology, returning video dimensions if applicable
- L160 _private member_ `int32 RefCount;` — Media Foundation boilerplate
- L163 _private member_ `IMFMediaSession* MediaSession;` — The media session which handles all playback
- L165 _private member_ `IMFMediaSource* MediaSource;` — The source, which reads in the data from the file
- L168 _private member_ `FThreadSafeCounter MovieIsFinished;` — This counter lets the ticking thread know that the current movie finished
- L170 _private member_ `FThreadSafeCounter CloseIsPosted;` — This counter locks the ticking thread while all Media Foundation threads shutdown
- L173 _private member_ `FMovieTrackFormat VideoTrackFormat;` — Format of video track
- L176 _private member_ `FString HMDAudioOutputDevice;` — Caches the audio device from the HMD.
- L179 _private member_ `bool bFailedToCreateMediaSink;` — True when there was an error related to creating a media sink (MESessionTopologySet event received with status MF_E_CANNOT_CREATE_SINK)

#### class `FSampleGrabberCallback`  
`class FSampleGrabberCallback : public IMFSampleGrabberSinkCallback`  
_L184-231_
- inherits: `IMFSampleGrabberSinkCallback`
- desc: The sample grabber callback is for pulling frames off the video stream to render to texture
- L187 _public function_ `FSampleGrabberCallback(TArray<uint8>& InTextureData) : RefCount(1) , TextureData(InTextureData)`
- L193 _public function_ `virtual ~FSampleGrabberCallback()`
- L199 _public prototype_ `STDMETHODIMP QueryInterface(REFIID RefID, void** Object);` — IUnknown interface
- L200 _public prototype_ `STDMETHODIMP_(ULONG) AddRef();`
- L201 _public prototype_ `STDMETHODIMP_(ULONG) Release();`
- L204 _public function_ `STDMETHODIMP OnClockStart(MFTIME SystemTime, LONGLONG llClockStartOffset)` — IMFClockStateSink interface
- L205 _public function_ `STDMETHODIMP OnClockStop(MFTIME SystemTime)`
- L206 _public function_ `STDMETHODIMP OnClockPause(MFTIME SystemTime)`
- L207 _public function_ `STDMETHODIMP OnClockRestart(MFTIME SystemTime)`
- L208 _public function_ `STDMETHODIMP OnClockSetRate(MFTIME SystemTime, float flRate)`
- L211 _public function_ `STDMETHODIMP OnSetPresentationClock(IMFPresentationClock* Clock)` — IMFSampleGrabberSinkCallback interface
- L212 _public prototype_ `STDMETHODIMP OnProcessSample(REFGUID MajorMediaType, DWORD SampleFlags, LONGLONG SampleTime, LONGLONG SampleDuration, const BYTE* SampleBuffer, DWORD SampleSize);`
- L215 _public function_ `STDMETHODIMP OnShutdown()`
- L218 _public prototype_ `bool GetIsSampleReadyToUpdate() const;` — True if we have a new sample for readback
- L221 _public prototype_ `void SetNeedNewSample();` — Tells this callback that we need a new sample to read back
- L225 _private member_ `int32 RefCount;` — Media Foundation boilerplate
- L228 _private member_ `FThreadSafeCounter VideoSampleReady;` — Counter which determines when a sample can be safely read back
- L230 _private member_ `TArray<uint8>& TextureData;` — The texture data sample we read back to

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWindowsMoviePlayer, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWindowsMoviePlayer, Log, All);`

### `Plugins/Runtime/WindowsMoviePlayer/Source/WindowsMoviePlayer/Public/WindowsMoviePlayer.h` (Public)
_(no declarations extracted)_
