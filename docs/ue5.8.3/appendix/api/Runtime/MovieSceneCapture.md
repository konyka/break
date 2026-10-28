# Runtime / MovieSceneCapture

- module root: `Source/Runtime/MovieSceneCapture`
- headers: 17; symbols: 468
- symbol kinds: class=24, delegate=1, enum=4, enumerator=17, function=81, member=134, prototype=189, struct=17, typedef=1
- DynamicallyLoadedModuleNames: ImageWrapper
- PrivateDependencyModuleNames: AVIWriter, AssetRegistry, AudioMixer, Core, CoreUObject, Engine, ImageWriteQueue, Json, JsonUtilities, RHI, RenderCore, Slate, SlateCore
- PublicIncludePathModuleNames: ImageWrapper

### `Source/Runtime/MovieSceneCapture/Private/ActiveMovieSceneCaptures.h` (Private)


#### class `FActiveMovieSceneCaptures`  
`class FActiveMovieSceneCaptures : public FGCObject, public FTickableGameObject`  
_L11-53_
- inherits: `FGCObject,FTickableGameObject`
- L15 _public prototype_ `static FActiveMovieSceneCaptures& Get();` — Singleton access to an instance of this class
- L18 _public prototype_ `void Add(UMovieSceneCapture* Capture);` — Add a capture to this class to ensure that it will get updated
- L21 _public prototype_ `void Remove(UMovieSceneCapture* Capture);` — Remove a capture from this class
- L24 _public prototype_ `void Shutdown();` — Shutdown this class, waiting for any currently active captures to finish capturing
- L27 _public function_ `const TArray<UMovieSceneCapture*>& GetActiveCaptures() const` — We use the pending array here, as it's the most up to date
- L32 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L33 _private prototype_ `virtual FString GetReferencerName() const override;`
- L37 _private function_ `virtual UWorld* GetTickableGameObjectWorld() const override` — FTickableGameObject interface
- L38 _private function_ `virtual bool IsTickableInEditor() const override`
- L39 _private function_ `virtual bool IsTickable() const override`
- L40 _private function_ `virtual bool IsTickableWhenPaused() const override`
- L41 _private function_ `virtual TStatId GetStatId() const override`
- L42 _private prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L46 _private function_ `FActiveMovieSceneCaptures()` — Private construction to enforce singleton use
- L49 _private member_ `TArray<TObjectPtr<UMovieSceneCapture>> ActiveCaptures;` — Array of active captures
- L52 _private member_ `static TUniquePtr<FActiveMovieSceneCaptures> Singleton;` — Class singleton

### `Source/Runtime/MovieSceneCapture/Public/ErrorCodes.h` (Public)


#### enum `EMovieSceneCaptureExitCode`  
`enum class EMovieSceneCaptureExitCode : uint32`  
_L8-13_
- desc: Process exit codes
- L10 _public enumerator_ `Base = 0xAC701000`
- L11 _public enumerator_ `AssetNotFound`
- L12 _public enumerator_ `WorldNotFound`

### `Source/Runtime/MovieSceneCapture/Public/FrameGrabber.h` (Public)


#### struct `FViewportSurfaceReader`  
`struct FViewportSurfaceReader`  
_L14-79_
- desc: A single, managed surface used as a render target resolution destination
- L17 _public prototype_ `FViewportSurfaceReader(EPixelFormat InPixelFormat, FIntPoint InBufferSize);` — Constructor
- L20 _public prototype_ `~FViewportSurfaceReader();` — Destructor
- L23 _public prototype_ `void Initialize();` — Initialize this reader so that it can be waited on.
- L26 _public prototype_ `void BlockUntilAvailable();` — Wait for this reader to become available, if it's currently in use
- L31 _public prototype_ `void Reset();` — Safely resets the state of the wait event. When doing latent surface reading sometimes we may want to just bail on reading a given frame. Should only be performed after flushing rendering commands.
- L39 _public prototype_ `void ResolveRenderTarget(FViewportSurfaceReader* RenderToReadback, const FTextureRHIRef& BackBuffer, TFunction<void(FColor*, int32, int32)> Callback);` — Resolve the specified viewport RHI, calling the specified callback with the result. @param	BackBuffer		The backbuffer to resolve @param	Callback 		Callback to call with the locked texture data. This will be called on an undefined thread.
- L42 _public prototype_ `FIntPoint GetCurrentSize() const;` — Get the current size of the texture
- L45 _public function_ `void SetCaptureRect(FIntRect InCaptureRect)` — Set the rectangle within which to read pixels
- L48 _public function_ `void SetWindowSize(FIntPoint InWindowSize)` — Set the window size that we expect from the BackBuffer
- L50 _public function_ `bool WasEverQueued() const`
- L55 _protected prototype_ `void Resize(uint32 Width, uint32 Height);` — Set up this surface to the specified width/height
- L58 _protected member_ `FThreadSafeBool bEnabled;` — Whether this surface reader is enabled or not
- L61 _protected member_ `FEvent* AvailableEvent;` — Optional event that is triggered when the surface is no longer in use
- L64 _protected member_ `FTextureRHIRef ReadbackTexture;` — Texture used to store the resolved render target
- L67 _protected member_ `FIntRect CaptureRect;` — The rectangle to read from the surface
- L70 _protected member_ `FIntPoint WindowSize;` — In windows mode, the size of the widget with the border
- L73 _protected member_ `EPixelFormat PixelFormat;` — The desired pixel format of the resolved textures
- L76 _protected member_ `bool bIsEnabled;` — Whether this reader is enabled or not.
- L78 _protected member_ `bool bQueuedForCapture;`

#### struct `IFramePayload`  
`struct IFramePayload`  
_L81-90_
- L83 _public prototype_ `virtual ~IFramePayload() = default;`
- L89 _public function_ `virtual bool OnFrameReady_RenderThread(FColor* ColorBuffer, FIntPoint BufferSize, FIntPoint TargetSize) const` — Called when the buffer is now available in CPU ram Return true if you would like to execute the default behavior. (If you return false, GetCapturedFrames will be empty).

#### struct `FCapturedFrameData`  
`struct FCapturedFrameData`  
_L95-117_
- desc: Structure representing a captured frame
- L97 _public function_ `FCapturedFrameData(FIntPoint InBufferSize, FFramePayloadPtr InPayload) : BufferSize(InBufferSize), Payload(MoveTemp(InPayload))`
- L99 _public function_ `FCapturedFrameData(FCapturedFrameData&& In) : ColorBuffer(MoveTemp(In.ColorBuffer)), BufferSize(In.BufferSize), Payload(MoveTemp(In.Payload))`
- L100 _public function_ `FCapturedFrameData& operator=(FCapturedFrameData&& In)`
- L103 _public function_ `template<typename T> T* GetPayload()`
- L106 _public member_ `TArray<FColor> ColorBuffer;` — The color buffer of the captured frame
- L109 _public member_ `FIntPoint BufferSize;` — The size of the resulting color buffer
- L112 _public member_ `FFramePayloadPtr Payload;` — Optional user-specified payload
- L115 _private prototype_ `FCapturedFrameData(const FCapturedFrameData& In);`
- L116 _private prototype_ `FCapturedFrameData& operator=(const FCapturedFrameData& In);`

#### class `FFrameGrabber`  
`class FFrameGrabber`  
_L125-229_
- desc: Class responsible for resolving render target data for a specific viewport in an efficient manner Internally, the class uses a fixed array of resolution surfaces, and dispatches rendering commands to resolve the viewport render target into a specific index into this array. This means we can resolve the render target data without having to wait, or flush rendering commands.
- L136 _public prototype_ `FFrameGrabber(TSharedRef<FSceneViewport> Viewport, FIntPoint DesiredBufferSize, EPixelFormat InPixelFormat = PF_B8G8R8A8, uint32 NumSurfaces = 3);` — Construct this frame grabber @param InViewport			The viewport we are to grab frames for @param DesiredBufferSize		The desired size of captured frames @param InPixelFormat			The desired pixel format to store captured frames as @param InNumSurfaces			The number of destination surfaces contained in our buffer
- L139 _public prototype_ `~FFrameGrabber();` — Destructor
- L144 _public prototype_ `void StartCapturingFrames();` — Instruct the frame grabber to start capturing frames
- L147 _public prototype_ `bool IsCapturingFrames() const;` — Check whether we're capturing frames or not
- L150 _public prototype_ `void CaptureThisFrame(FFramePayloadPtr Payload);` — Instruct the frame grabber capture this frame, when it receives an event from slate
- L153 _public prototype_ `void StopCapturingFrames();` — Stop capturing frames
- L156 _public prototype_ `void Shutdown();` — Shut down this grabber, ensuring that any threaded operations are finished
- L161 _public prototype_ `bool HasOutstandingFrames() const;` — Check whether we have any outstanding frames or not
- L164 _public prototype_ `TArray<FCapturedFrameData> GetCapturedFrames();` — Retrieve any frames we may have captured
- L169 _protected prototype_ `void OnBackBufferReadyToPresentCallback(SWindow& SlateWindow, ISlateViewportProvider& ViewportProvider);` — Callback for when a backbuffer is ready for reading (called on render thread)
- L172 _protected prototype_ `void OnFrameReady(int32 SurfaceIndex, FColor* ColorBuffer, int32 Width, int32 Height);` — Called when the specified surface index has been locked for reading with the render target data (called on render thread)
- L177 _private prototype_ `FFrameGrabber(const FFrameGrabber&);` — Non-copyable
- L178 _private prototype_ `FFrameGrabber& operator=(const FFrameGrabber&);`
- L185 _private member_ `void* TargetWindowPtr;` — Pointer to the window we want to capture. Only held for comparison inside OnBackBufferReadyToPresentCallback - never to be dereferenced or cast to an SWindow. Held as a raw pointer to ensure that no referenc counting occurs from the background thread in OnBackBufferReadyToPresentCallback.
- L188 _private member_ `FDelegateHandle OnBackBufferReadyToPresent;` — Delegate handle for the OnBackBufferReadyToPresent event
- L191 _private member_ `TArray<FCapturedFrameData> CapturedFrames;` — Array of captured frames
- L194 _private member_ `mutable FCriticalSection CapturedFramesMutex;` — Lock to protect the above array
- L204 _private member_ `TArray<FResolveSurface> Surfaces;`
- L207 _private member_ `int32 CurrentFrameIndex;` — Index into the above array to the next surface that we should use - only accessed on main thread
- L210 _private member_ `int32 SlateRenderIndex;` — The index that we should capture the next rendered slate window into
- L213 _private member_ `FThreadSafeCounter OutstandingFrameCount;` — The total number of frames we are currently waiting on
- L216 _private member_ `TArray<FFramePayloadPtr> RenderThread_PendingFramePayloads;` — Only to be accessed from the render thread - array of frame payloads to be captured from the rendered slate window sorted first to last.
- L218 _private member_ `int32 FrameGrabLatency;`
- L225 _private member_ `EFrameGrabberState State;`
- L228 _private member_ `FIntPoint TargetSize;` — The desired target size to resolve frames to

#### struct `FFrameGrabber::FResolveSurface`  
`struct FResolveSurface`  
_L197-203_
- desc: Array of surfaces that we resolve the viewport RHI to. Fixed allocation - should never be resized
- L199 _public function_ `FResolveSurface(EPixelFormat InPixelFormat, FIntPoint BufferSize) : Surface(InPixelFormat, BufferSize)`
- L201 _public member_ `FFramePayloadPtr Payload;`
- L202 _public member_ `FViewportSurfaceReader Surface;`

#### enum `FFrameGrabber::EFrameGrabberState`  
`enum class EFrameGrabberState`  
_L221-224_
- desc: The current state of the grabber
- L223 _public enumerator_ `Inactive`
- L223 _public enumerator_ `Inactive`
- L223 _public enumerator_ `Inactive`

#### Free symbols / members of external scopes

- L92 _typedef_ `typedef TSharedPtr<IFramePayload, ESPMode::ThreadSafe> FFramePayloadPtr;`

### `Source/Runtime/MovieSceneCapture/Public/IMovieSceneCapture.h` (Public)


#### class `UMovieSceneCaptureInterface`  
`class UMovieSceneCaptureInterface : public UInterface`  
_L15-19_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IMovieSceneCaptureInterface`  
`class IMovieSceneCaptureInterface`  
_L22-44_
- desc: Interface for a movie capture object
- L28 _public prototype_ `virtual void Initialize(TSharedPtr<FSceneViewport> Viewport, int32 PIEInstance = -1) = 0;` — Initialize this capture object by binding it to the specified viewport
- L31 _public prototype_ `virtual void StartCapturing() = 0;` — Instruct this capture to start capturing frames
- L34 _public prototype_ `virtual void Close() = 0;` — Shut down this movie capture
- L37 _public prototype_ `virtual FMovieSceneCaptureHandle GetHandle() const = 0;` — Get a unique handle to this object
- L40 _public prototype_ `virtual const FMovieSceneCaptureSettings& GetSettings() const = 0;` — Access specific movie scene capture settings
- L43 _public prototype_ `virtual const int32 GetFrameNumberOffset() const = 0;` — Access Frame Number Offset

### `Source/Runtime/MovieSceneCapture/Public/LevelCapture.h` (Public)


#### class `ULevelCapture`  
`class ULevelCapture : public UMovieSceneCapture`  
_L15-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneCapture`
- L18 _public prototype_ `ULevelCapture(const FObjectInitializer&);`
- L24 _public member_ `bool bAutoStartCapture;` — `UPROPERTY(EditAnywhere, Category=General)` — Specifies whether the capture should start immediately, or whether it will be invoked externally (through StartMovieCapture/StopMovieCapture exec commands)
- L27 _public prototype_ `void SetPrerequisiteActor(AActor* Prereq);` — Specify a prerequisite actor that must be set up before we start capturing
- L29 _public prototype_ `virtual void Initialize(TSharedPtr<FSceneViewport> InViewport, int32 PIEInstance = -1) override;`
- L30 _public prototype_ `virtual void OnTick(float DeltaSeconds) override;`
- L35 _private member_ `TWeakObjectPtr<AActor> PrerequisiteActor;` — Specify a prerequisite actor that must be set up before we start capturing
- L39 _private member_ `FGuid PrerequisiteActorId;` — `UPROPERTY()` — Copy of the ID from PrerequisiteActor. Required because JSON serialization exports the path of the object, rather that its GUID
- L42 _private member_ `int32 PIECaptureInstance;` — PIE instance index that we are capturing with

### `Source/Runtime/MovieSceneCapture/Public/MovieSceneCapture.h` (Public)


#### struct `FCachedMetrics`  
`struct FCachedMetrics`  
_L21-33_
- desc: Structure used to cache various metrics for our capture
- L23 _public function_ `FCachedMetrics() : Width(0), Height(0), Frame(0), ElapsedSeconds(0.f), PreviousFrame(INDEX_NONE)`
- L26 _public member_ `int32 Width, Height;` — The width/Height of the frame
- L26 _public member_ `int32 Width, Height;` — The width/Height of the frame
- L28 _public member_ `int32 Frame;` — The current frame number
- L30 _public member_ `float ElapsedSeconds;` — The number of seconds that have elapsed
- L32 _public member_ `int32 PreviousFrame;` — The previous frame number

#### class `UMovieSceneCapture`  
`class UMovieSceneCapture : public UObject, public IMovieSceneCaptureInterface, public ICaptureProtocolHost`  
_L37-219_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, PerObjectConfig, BlueprintType, MinimalAPI)`
- inherits: `UObject,IMovieSceneCaptureInterface,ICaptureProtocolHost`
- desc: Class responsible for capturing scene data
- L40 _public prototype_ `UMovieSceneCapture(const FObjectInitializer& Initializer);`
- L45 _public member_ `static const FName MovieSceneCaptureUIName;` — This name is used by the UI to save/load a specific instance of the settings from config that doesn't affect the CDO which would affect scripting environments.
- L47 _public prototype_ `virtual void PostInitProperties() override;`
- L52 _public prototype_ `virtual void Initialize(TSharedPtr<FSceneViewport> InSceneViewport, int32 PIEInstance = -1) override;`
- L53 _public function_ `virtual void StartCapturing()`
- L54 _public function_ `virtual void Close() override`
- L55 _public function_ `virtual FMovieSceneCaptureHandle GetHandle() const override`
- L56 _public function_ `const FMovieSceneCaptureSettings& GetSettings() const override`
- L57 _public function_ `const int32 GetFrameNumberOffset() const override`
- L61 _public prototype_ `virtual void LoadFromConfig();` — Load save from config helpers
- L62 _public prototype_ `virtual void SaveToConfig();`
- L65 _public prototype_ `void SerializeJson(FJsonObject& Object);` — Serialize additional json data for this capture
- L68 _public prototype_ `void DeserializeJson(const FJsonObject& Object);` — Deserialize additional json data for this capture
- L73 _protected function_ `virtual void SerializeAdditionalJson(FJsonObject& Object)` — Custom, additional json serialization
- L76 _protected function_ `virtual void DeserializeAdditionalJson(const FJsonObject& Object)` — Custom, additional json deserialization
- L79 _protected prototype_ `virtual bool IsAudioPassIfNeeded() const;` — Returns true if this is currently the audio pass, or if an audio pass is not needed. Shorthand for checking if we're in a state where we should finish capture.
- L84 _public member_ `FSoftClassPath ImageCaptureProtocolType;` — `UPROPERTY(config, EditAnywhere, NoClear, Category=CaptureSettings, DisplayName="Image Output Format", meta=(MetaClass="/Script/MovieSceneCapture.MovieSceneImageCaptureProtocolBase", HideViewOptions, ShowDisplayNames))` — The type of capture protocol to use for image data
- L88 _public member_ `FSoftClassPath AudioCaptureProtocolType;` — `UPROPERTY(config, EditAnywhere, NoClear, Category=CaptureSettings, DisplayName="Audio Output Format", meta=(MetaClass="/Script/MovieSceneCapture.MovieSceneAudioCaptureProtocolBase", HideViewOptions, ShowDisplayNames))` — The type of capture protocol to use for audio data.
- L92 _public member_ `TObjectPtr<UMovieSceneImageCaptureProtocolBase> ImageCaptureProtocol;` — `UPROPERTY(VisibleAnywhere, Category=CaptureSettings, Transient, Instanced)` — Capture protocol responsible for actually capturing frame data
- L95 _public member_ `TObjectPtr<UMovieSceneAudioCaptureProtocolBase> AudioCaptureProtocol;` — `UPROPERTY(VisibleAnywhere, Category = CaptureSettings, Transient, Instanced)`
- L99 _public member_ `FMovieSceneCaptureSettings Settings;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=CaptureSettings, meta=(ShowOnlyInnerProperties))` — Settings that define how to capture
- L103 _public member_ `bool bUseSeparateProcess;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, AdvancedDisplay)` — Whether to capture the movie in a separate process or not
- L107 _public member_ `bool bCloseEditorWhenCaptureStarts;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, AdvancedDisplay, meta=(EditCondition=bUseSeparateProcess))` — When enabled, the editor will shutdown when the capture starts
- L111 _public member_ `FString AdditionalCommandLineArguments;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, AdvancedDisplay, meta=(EditCondition=bUseSeparateProcess))` — Additional command line arguments to pass to the external process when capturing
- L115 _public member_ `FString InheritedCommandLineArguments;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, transient, Category=General, AdvancedDisplay, meta=(EditCondition=bUseSeparateProcess))` — Command line arguments inherited from this process
- L118 _public prototype_ `DECLARE_EVENT( UMovieSceneCapture, FOnCaptureFinished );` — Event that is fired after we've finished capturing
- L119 _public function_ `FOnCaptureFinished& OnCaptureFinished()`
- L124 _public function_ `const FCachedMetrics& GetMetrics() const` — Access this object's cached metrics
- L128 _public function_ `UMovieSceneCaptureProtocolBase* GetImageCaptureProtocol()` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Access the capture protocol we are using
- L130 _public function_ `UMovieSceneCaptureProtocolBase* GetAudioCaptureProtocol()` — `UFUNCTION(BlueprintCallable, Category=Capture)`
- L134 _public prototype_ `void SetImageCaptureProtocolType(TSubclassOf<UMovieSceneCaptureProtocolBase> ProtocolType);` — `UFUNCTION(BlueprintCallable, Category=Capture)`
- L136 _public prototype_ `void SetAudioCaptureProtocolType(TSubclassOf<UMovieSceneCaptureProtocolBase> ProtocolType);` — `UFUNCTION(BlueprintCallable, Category=Capture)`
- L142 _public prototype_ `void StartWarmup();` — Starts warming up.  May be optionally called before StartCapture().  This can be used to start rendering frames early, before any files are captured or written out
- L145 _public prototype_ `void StartCapture();` — Initialize the capture so that it is able to start capturing frames
- L148 _public prototype_ `void CaptureThisFrame(float DeltaSeconds);` — Indicate that this frame should be captured - must be called before the movie scene capture is ticked
- L151 _public prototype_ `void FinalizeWhenReady();` — Automatically finalizes the capture when all currently pending frames are dealt with
- L154 _public prototype_ `bool ShouldFinalize() const;` — Check whether we should automatically finalize this capture
- L157 _public prototype_ `void Finalize();` — Finalize the capturing process, assumes all frames have been processed.
- L162 _public prototype_ `void Tick(float DeltaSeconds);` — Called at the end of a frame, before a frame is presented by slate
- L166 _public prototype_ `FString ResolveFileFormat(const FString& Format, const FFrameMetrics& FrameMetrics) const;` — Resolve the specified format using the user supplied formatting rules.
- L169 _public function_ `double GetEstimatedCaptureDurationSeconds() const` — Estimate how long our duration is going to be for pre-allocation purposes.
- L172 _public function_ `virtual FFrameRate GetCaptureFrameRate() const`
- L173 _public function_ `virtual const ICaptureStrategy& GetCaptureStrategy() const`
- L178 _protected function_ `virtual void AddFormatMappings(TMap<FString, FStringFormatArg>& OutFormatMappings, const FFrameMetrics& FrameMetrics) const` — Add additional format mappings to be used when generating filenames
- L182 _protected prototype_ `void InitializeCaptureProtocols();` — Initialize the settings structure for the current capture type
- L184 _protected prototype_ `void ForciblyReinitializeCaptureProtocols();`
- L187 _protected function_ `virtual void OnTick(float DeltaSeconds)` — Called at the end of a frame, before a frame is presented by slate
- L191 _protected prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L196 _protected member_ `TSharedPtr<ICaptureStrategy> CaptureStrategy;` — Strategy used for capture (real-time/fixed-time-step)
- L198 _protected member_ `TOptional<FCaptureProtocolInitSettings> InitSettings;` — The settings we will use to set up the capture protocol
- L200 _protected member_ `bool bFinalizeWhenReady;` — Whether we should automatically attempt to capture frames every tick or not
- L202 _protected member_ `FMovieSceneCaptureHandle Handle;` — Our unique handle, used for external representation without having to link to the MovieSceneCapture module
- L204 _protected member_ `FCachedMetrics CachedMetrics;` — Cached metrics for this capture operation
- L206 _protected member_ `TMap<FString, FStringFormatArg> FormatMappings;` — Format mappings used for generating filenames
- L208 _protected member_ `bool bCapturing;` — Whether we have started capturing or not
- L210 _protected member_ `bool bIsAudioCapturePass;` — If we're currently doing an audio pass or not
- L214 _protected member_ `int32 FrameNumberOffset;` — Frame number index offset when saving out frames.  This is used to allow the frame numbers on disk to match what they would be in the authoring application, rather than a simple 0-based sequential index
- L216 _protected member_ `FOnCaptureFinished OnCaptureFinishedDelegate;` — Event that is triggered when capturing has finished
- L218 _protected member_ `Scalability::FQualityLevels CachedQualityLevels;` — Cached quality levels

#### struct `FFixedTimeStepCaptureStrategy`  
`struct FFixedTimeStepCaptureStrategy : ICaptureStrategy`  
_L222-233_
- inherits: `ICaptureStrategy`
- desc: A strategy that employs a fixed frame time-step, and as such never drops a frame. Potentially accelerated.
- L224 _public prototype_ `FFixedTimeStepCaptureStrategy(FFrameRate InFrameRate);`
- L226 _public prototype_ `virtual void OnInitialize() override;`
- L227 _public prototype_ `virtual void OnStop() override;`
- L228 _public prototype_ `virtual bool ShouldPresent(double CurrentTimeSeconds, uint32 FrameIndex) const override;`
- L229 _public prototype_ `virtual int32 GetDroppedFrames(double CurrentTimeSeconds, uint32 FrameIndex) const override;`
- L232 _private member_ `FFrameRate FrameRate;`

#### struct `FRealTimeCaptureStrategy`  
`struct FRealTimeCaptureStrategy : ICaptureStrategy`  
_L236-248_
- inherits: `ICaptureStrategy`
- desc: A capture strategy that captures in real-time, potentially dropping frames to maintain a stable constant framerate video.
- L238 _public prototype_ `FRealTimeCaptureStrategy(FFrameRate InFrameRate);`
- L240 _public prototype_ `virtual void OnInitialize() override;`
- L241 _public prototype_ `virtual void OnStop() override;`
- L242 _public function_ `virtual bool ShouldSynchronizeFrames() const override`
- L243 _public prototype_ `virtual bool ShouldPresent(double CurrentTimeSeconds, uint32 FrameIndex) const override;`
- L244 _public prototype_ `virtual int32 GetDroppedFrames(double CurrentTimeSeconds, uint32 FrameIndex) const override;`
- L247 _private member_ `double NextPresentTimeS, FrameLength;`
- L247 _private member_ `double NextPresentTimeS, FrameLength;`

#### Free symbols / members of external scopes

- L118 _delegate_ `DECLARE_EVENT( UMovieSceneCapture, FOnCaptureFinished );` — Event that is fired after we've finished capturing

### `Source/Runtime/MovieSceneCapture/Public/MovieSceneCaptureEnvironment.h` (Public)


#### class `UMovieSceneCaptureEnvironment`  
`class UMovieSceneCaptureEnvironment : public UObject`  
_L14-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _public prototype_ `static int32 GetCaptureFrameNumber();` — `UFUNCTION(BlueprintPure, Category="Cinematics|Capture")` — Get the frame number of the current capture
- L25 _public prototype_ `static float GetCaptureElapsedTime();` — `UFUNCTION(BlueprintPure, Category="Cinematics|Capture")` — Get the total elapsed time of the current capture in seconds
- L32 _public prototype_ `static bool IsCaptureInProgress();` — `UFUNCTION(BlueprintCallable, Category="Cinematics|Capture")` — Return true if there is any capture currently active (even in a warm-up state). Useful for checking whether to do certain operations in BeginPlay
- L38 _public prototype_ `static UMovieSceneImageCaptureProtocolBase* FindImageCaptureProtocol();` — `UFUNCTION(BlueprintCallable, Category="Cinematics|Capture")` — Attempt to locate a capture protocol - may not be in a capturing state
- L44 _public prototype_ `static UMovieSceneAudioCaptureProtocolBase* FindAudioCaptureProtocol();` — `UFUNCTION(BlueprintCallable, Category = "Cinematics|Capture")` — Attempt to locate a capture protocol - may not be in a capturing state

### `Source/Runtime/MovieSceneCapture/Public/MovieSceneCaptureHandle.h` (Public)


#### struct `FMovieSceneCaptureHandle`  
`struct FMovieSceneCaptureHandle`  
_L8-24_
- desc: A handle to a movie scene capture implementation
- L10 _public function_ `FMovieSceneCaptureHandle() : ID(0)`
- L19 _public function_ `bool IsValid() const` — Check if this handle is valid
- L23 _protected member_ `uint32 ID;` — Unique identifier for this handle

#### Free symbols / members of external scopes

- L13 _function_ `friend bool operator==(const FMovieSceneCaptureHandle& A, const FMovieSceneCaptureHandle& B)` — Equality operator
- L16 _function_ `friend bool operator!=(const FMovieSceneCaptureHandle& A, const FMovieSceneCaptureHandle& B)` — Inequality operator

### `Source/Runtime/MovieSceneCapture/Public/MovieSceneCaptureModule.h` (Public)


#### class `IMovieSceneCaptureModule`  
`class IMovieSceneCaptureModule : public IModuleInterface`  
_L15-33_
- inherits: `IModuleInterface`
- L18 _public function_ `static IMovieSceneCaptureModule& Get()`
- L24 _public prototype_ `virtual IMovieSceneCaptureInterface* InitializeFromCommandLine() = 0;`
- L25 _public prototype_ `virtual IMovieSceneCaptureInterface* CreateMovieSceneCapture(TSharedPtr<FSceneViewport> Viewport) = 0;`
- L26 _public prototype_ `virtual IMovieSceneCaptureInterface* GetFirstActiveMovieSceneCapture() = 0;`
- L28 _public prototype_ `virtual IMovieSceneCaptureInterface* RetrieveMovieSceneInterface(FMovieSceneCaptureHandle Handle) = 0;`
- L29 _public prototype_ `virtual void DestroyMovieSceneCapture(FMovieSceneCaptureHandle Handle) = 0;`
- L31 _public prototype_ `virtual void DestroyAllActiveCaptures() = 0;`
- L32 _public prototype_ `virtual bool IsStereoAllowed() = 0;`

#### Free symbols / members of external scopes

- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMovieSceneCapture, Log, All);`

### `Source/Runtime/MovieSceneCapture/Public/MovieSceneCaptureProtocolBase.h` (Public)


#### enum `EMovieSceneCaptureProtocolState`  
`enum class EMovieSceneCaptureProtocolState : uint8`  
_L19-29_
- reflection: `UENUM()`
- L22 _public enumerator_ `Idle` — The protocol is idle, and has not even been initialized
- L24 _public enumerator_ `Initialized` — The protocol has been initialized (and bound to a viewport) but is not capturing frames yet
- L26 _public enumerator_ `Capturing` — The protocol has been initialized, bound to a viewport and is capturing data
- L28 _public enumerator_ `Finalizing` — The protocol has finished capturing data, and is pending finalization

#### struct `FCaptureProtocolInitSettings`  
`struct FCaptureProtocolInitSettings`  
_L32-47_
- desc: Structure used to initialize a capture protocol
- L37 _public prototype_ `static FCaptureProtocolInitSettings FromSlateViewport(TSharedRef<FSceneViewport> InSceneViewport);` — Capture from a slate viewport, using the specified custom protocol settings
- L40 _public member_ `TSharedPtr<FSceneViewport> SceneViewport;` — The slate viewport we should capture from
- L42 _public member_ `FIntPoint DesiredSize;` — The desired size of the captured frames
- L46 _private function_ `FCaptureProtocolInitSettings()` — Private construction to ensure use of static init methods

#### class `UMovieSceneCaptureProtocolBase`  
`class UMovieSceneCaptureProtocolBase : public UObject`  
_L57-276_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, PerObjectConfig, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: A capture protocol responsible for dealing with captured frames using some custom method (writing out to disk, streaming, etc) A typical process for capture consits of the following process: Setup -> [ Warm up -> [ Capture Frame ] ] -> Begin Finalize -> [ HasFinishedProcessing ] -> Finalize
- L63 _public prototype_ `UMovieSceneCaptureProtocolBase(const FObjectInitializer& ObjInit);`
- L71 _public function_ `EMovieSceneCaptureProtocolState GetState() const` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Get the current state of this capture protocol
- L77 _public function_ `bool IsCapturing() const` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Check whether we can capture a frame from this protocol
- L85 _public prototype_ `bool Setup(const FCaptureProtocolInitSettings& InSettings, const ICaptureProtocolHost* Host);` — Setup this capture protocol @param InSettings		The initial initialization settings to use for the capture @param Host				The client that is initializing this protocol
- L92 _public prototype_ `virtual class UWorld* GetWorld() const override;` — Get the UWorld associated with this Capture Protocol. This is not valid until Setup has been called with a valid Slate viewport. Will return nullptr when the protocol has been created but the game world is not running (ie: in UI).
- L98 _public prototype_ `void PreTick();` — Called on the main thread before the movie capture itself is updated to reset per-frame state
- L103 _public prototype_ `void Tick();` — Called on the main thread to do any additional processing
- L108 _public prototype_ `void WarmUp();` — Start warming up this capture protocol - called any time the process enters a warming-up state
- L115 _public prototype_ `bool StartCapture();` — Called when this protocol should start capturing @return true if the operation was successful, false otherwise
- L123 _public prototype_ `void CaptureFrame(const FFrameMetrics& FrameMetrics);` — Instruct this protocol to capture a frame relating to the specified metrics @param FrameMetrics		Frame metrics relating to the current frame @param Host				The client that is initializing this protocol
- L128 _public prototype_ `void BeginFinalize();` — Called when we have finished capturing and we should start finalizing the capture
- L134 _public prototype_ `bool HasFinishedProcessing() const;` — Check whether this protocol has any processing left to do, or whether it should be finalized. Only called when the capture has been asked to end.
- L139 _public prototype_ `void Finalize();` — Called when this protocol should tear down and finalize all its processing. Only called if HasFinishedProcessing is true.
- L146 _public prototype_ `void AddFormatMappings(TMap<FString, FStringFormatArg>& FormatMappings) const;` — Called when generating formatting filename to add any additional format mappings @param FormatMappings	Map to add additional format rules to
- L151 _public prototype_ `void OnReleaseConfig(FMovieSceneCaptureSettings& InSettings);` — Called when this protocol has been released
- L156 _public prototype_ `void OnLoadConfig(FMovieSceneCaptureSettings& InSettings);` — Called when this protocol has been loaded
- L166 _public prototype_ `bool CanWriteToFile(const TCHAR* InFilename, bool bOverwriteExisting) const;` — Test whether this capture protocol thinks the file should be written to. Only called when we're not overwriting existing files. By default, we simply test for the file's existence, however this can be overridden to afford complex behaviour like writing out multiple video files for different file names @param InFilename 			The filename to test @param bOverwriteExisting	Whether we are allowed to overwrite existing files @return Whether we should deem this file writable or not
- L173 _protected function_ `virtual bool SetupImpl()` — Called once at the start of the capture process (before any warmup) to set up anything required for the capture.
- L181 _protected function_ `virtual void PreTickImpl()` — Called on the main thread before the movie capture itself is updated to reset per-frame state
- L186 _protected function_ `virtual void TickImpl()` — Called on the main thread to do any additional processing
- L191 _protected function_ `virtual void WarmUpImpl()` — Start warming up this capture protocol
- L198 _protected function_ `virtual bool StartCaptureImpl()` — Start capturing @return true if the operation was successful, false otherwise
- L208 _protected function_ `virtual void CaptureFrameImpl(const FFrameMetrics& FrameMetrics)` — Instruct this protocol to capture a frame relating to the specified metrics @param FrameMetrics		Frame metrics relating to the current frame
- L213 _protected function_ `virtual void PauseCaptureImpl()` — Pause capturing
- L218 _protected function_ `virtual void BeginFinalizeImpl()` — Called when we have finished capturing and we should start finalizing the capture
- L224 _protected function_ `virtual bool HasFinishedProcessingImpl() const` — Check whether this protocol has any processing left to do, or whether it should be finalized. Only called when the capture has been asked to end.
- L229 _protected function_ `virtual void FinalizeImpl()` — Called when we have finished capturing
- L236 _protected function_ `virtual void AddFormatMappingsImpl(TMap<FString, FStringFormatArg>& FormatMappings) const` — Called when generating formatting filename to add any additional format mappings @param FormatMappings	Map to add additional format rules to
- L241 _protected function_ `virtual void OnReleaseConfigImpl(FMovieSceneCaptureSettings& InSettings)` — Called when this protocol has been released
- L246 _protected function_ `virtual void OnLoadConfigImpl(FMovieSceneCaptureSettings& InSettings)` — Called when this protocol has been loaded
- L256 _protected prototype_ `virtual bool CanWriteToFileImpl(const TCHAR* InFilename, bool bOverwriteExisting) const;` — Test whether this capture protocol thinks the file should be written to. Only called when we're not overwriting existing files. By default, we simply test for the file's existence, however this can be overridden to afford complex behaviour like writing out multiple video files for different file names @param InFilename 			The filename to test @param bOverwriteExisting	Whether we are allowed to overwrite existing files @return Whether we should deem this file writable or not
- L257 _protected prototype_ `virtual FString GenerateFilenameImpl(const FFrameMetrics& FrameMetrics, const TCHAR* Extension, const FString* NameFormatString = nullptr) const;`
- L258 _protected prototype_ `void EnsureFileWritableImpl(const FString& File) const;`
- L263 _protected member_ `TOptional<FCaptureProtocolInitSettings> InitSettings;` — Initialization settings
- L266 _protected member_ `const ICaptureProtocolHost* CaptureHost;` — The capture host that is owns this protocol
- L272 _private member_ `EMovieSceneCaptureProtocolState State;` — `UPROPERTY(transient)` — The current state of the protocol
- L275 _private member_ `bool bFrameRequested[2];` — Double buffer of values tracking whether we are capturing changes based on GFrameCounter

#### class `UMovieSceneImageCaptureProtocolBase`  
`class UMovieSceneImageCaptureProtocolBase : public UMovieSceneCaptureProtocolBase`  
_L282-291_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, PerObjectConfig, Abstract, MinimalAPI)`
- inherits: `UMovieSceneCaptureProtocolBase`
- desc: A class to inherit from for image capture protocols. Used to filter the UI for protocols used on the image capture pass.
- L287 _public function_ `UMovieSceneImageCaptureProtocolBase(const FObjectInitializer& ObjInit) : UMovieSceneCaptureProtocolBase(ObjInit)`

#### class `UMovieSceneAudioCaptureProtocolBase`  
`class UMovieSceneAudioCaptureProtocolBase : public UMovieSceneCaptureProtocolBase`  
_L297-305_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, PerObjectConfig, Abstract, MinimalAPI)`
- inherits: `UMovieSceneCaptureProtocolBase`
- desc: A class to inherit from for audio capture protocols. Used to filter the UI for protocols used on the audio capture pass.
- L302 _public function_ `UMovieSceneAudioCaptureProtocolBase(const FObjectInitializer& ObjInit) : UMovieSceneCaptureProtocolBase(ObjInit)`

#### struct `FFrameMetrics`  
`struct FFrameMetrics`  
_L309-336_
- reflection: `USTRUCT(BlueprintType)`
- desc: Metrics that correspond to a particular frame
- L314 _public function_ `FFrameMetrics() : TotalElapsedTime(0), FrameDelta(0), FrameNumber(0), NumDroppedFrames(0)` — Default construction
- L316 _public function_ `FFrameMetrics(float InTotalElapsedTime, float InFrameDelta, int32 InFrameNumber, int32 InNumDroppedFrames) : TotalElapsedTime(InTotalElapsedTime), FrameDelta(InFrameDelta), FrameNumber(InFrameNumber), NumDroppedFrames(InNumDroppedFrames)`
- L323 _public member_ `float TotalElapsedTime;` — `UPROPERTY(BlueprintReadOnly, Category=Capture)` — The total amount of time, in seconds, since the capture started
- L327 _public member_ `float FrameDelta;` — `UPROPERTY(BlueprintReadOnly, Category=Capture)` — The total amount of time, in seconds, that this specific frame took to render (not accounting for dropped frames)
- L331 _public member_ `int32 FrameNumber;` — `UPROPERTY(BlueprintReadOnly, Category=Capture)` — The index of this frame from the start of the capture, including dropped frames
- L335 _public member_ `int32 NumDroppedFrames;` — `UPROPERTY(BlueprintReadOnly, Category=Capture)` — The number of frames we dropped in-between this frame, and the last one we captured

#### struct `ICaptureStrategy`  
`struct ICaptureStrategy`  
_L340-350_
- desc: Interface that defines when to capture or drop frames
- L342 _public prototype_ `virtual ~ICaptureStrategy()= default;`
- L344 _public prototype_ `virtual void OnInitialize() = 0;`
- L345 _public prototype_ `virtual void OnStop() = 0;`
- L346 _public function_ `virtual bool ShouldSynchronizeFrames() const`
- L348 _public prototype_ `virtual bool ShouldPresent(double CurrentTimeSeconds, uint32 FrameIndex) const = 0;`
- L349 _public prototype_ `virtual int32 GetDroppedFrames(double CurrentTimeSeconds, uint32 FrameIndex) const = 0;`

#### struct `ICaptureProtocolHost`  
`struct ICaptureProtocolHost`  
_L354-375_
- desc: Interface to be implemented by any class using an UMovieSceneCaptureProtocolBase instance
- L357 _public prototype_ `virtual const FMovieSceneCaptureSettings& GetSettings() const = 0;` — Get shared settings for the capture
- L360 _public prototype_ `virtual const int32 GetFrameNumberOffset() const = 0;` — Access Frame number index offset when saving out frames.
- L363 _public prototype_ `virtual FFrameRate GetCaptureFrameRate() const = 0;` — Get the capture frequency
- L366 _public prototype_ `virtual const ICaptureStrategy& GetCaptureStrategy() const = 0;` — Access the host's capture strategy
- L369 _public prototype_ `virtual FString ResolveFileFormat(const FString& Format, const FFrameMetrics& FrameMetrics) const = 0;` — Ask the host to resolve the format string for a file name.
- L374 _public prototype_ `virtual double GetEstimatedCaptureDurationSeconds() const = 0;` — Ask the host to inform us of how long the capture duration is expected to be. Should only be used as an estimate due to the possible complexities in calculating the duration due to handle frames, warmups, etc.

### `Source/Runtime/MovieSceneCapture/Public/MovieSceneCaptureSettings.h` (Public)


#### struct `FCaptureResolution`  
`struct FCaptureResolution`  
_L15-26_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure representing a capture resolution
- L17 _public function_ `FCaptureResolution(int32 InX = 0, int32 InY = 0) : ResX(InX), ResY(InY)`
- L22 _public member_ `int32 ResX;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Resolution, meta=(ClampMin = 16, ClampMax=7680))`
- L25 _public member_ `int32 ResY;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Resolution, meta=(ClampMin = 16, ClampMax=7680))`

#### struct `FMovieSceneCaptureSettings`  
`struct FMovieSceneCaptureSettings`  
_L30-138_
- reflection: `USTRUCT(BlueprintType)`
- desc: Common movie-scene capture settings
- L32 _public prototype_ `FMovieSceneCaptureSettings();`
- L38 _public member_ `FDirectoryPath OutputDirectory;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, meta=(RelativePath))` — The directory to output the captured file(s) in
- L42 _public member_ `TSubclassOf<class AGameModeBase> GameModeOverride;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, AdvancedDisplay)` — Optional game mode to override the map's default game mode with.  This can be useful if the game's normal mode displays UI elements or loading screens that you don't want captured.
- L62 _public member_ `FString OutputFormat;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, DisplayName="Filename Format")` — The format to use for the resulting filename. Extension will be added automatically. Any tokens of the form {token} will be replaced with the corresponding value: {fps}		- The captured framerate {frame}		- The current frame number (only relevant for image sequences) {width}		- The width of the captured frames {height}		- The height of the captured frames {world}		- The name of the current world {quality}	- The image compression quality setting {material}   - The material/render pass {shot}       - The name of the level sequence asset shot being played {sequence}   - The name of the level sequence asset being played {camera}     - The name of the current camera {date}       - The date in the format of {year}.{month}.{day} {year}       - The current year {month}      - The current month {day}        - The current day {time}       - The current time in the format of hours.minutes.seconds
- L66 _public member_ `bool bOverwriteExisting;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, AdvancedDisplay)` — Whether to overwrite existing files or not
- L70 _public member_ `bool bUseRelativeFrameNumbers;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, AdvancedDisplay)` — True if frame numbers in the output files should be relative to zero, rather than the actual frame numbers in the originating animation content.
- L74 _public member_ `int32 HandleFrames;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Sequence, AdvancedDisplay, meta=(ClampMin=0, UIMin=0))` — Number of frame handles to include for each shot
- L78 _public member_ `FString MovieExtension;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Sequence, AdvancedDisplay)` — Filename extension for movies referenced in the XMLs/EDLs
- L82 _public member_ `uint8 ZeroPadFrameNumbers;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=General, AdvancedDisplay, meta=(ClampMin=0, UIMin=0))` — How much to zero-pad frame numbers on filenames
- L86 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CaptureSettings, meta = (ClampMin = 1, UIMin = 1, ClampMax = 200, UIMax = 200))` — The sequence's frame rate at which to capture if "Use Custom Frame Rate" is not enabled
- L90 _public member_ `bool bUseCustomFrameRate;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=CaptureSettings)` — Specify using the custom frame rate as opposed to the sequence's display rate
- L94 _public member_ `FFrameRate CustomFrameRate;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=CaptureSettings, meta = (ClampMin = 1, UIMin = 1, ClampMax = 200, UIMax = 200, EditCondition=bUseCustomFrameRate))` — The custom frame rate at which to capture if "Use Custom Frame Rate" is enabled
- L98 _public member_ `FCaptureResolution Resolution;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=CaptureSettings, meta=(ShowOnlyInnerProperties))` — The resolution at which to capture
- L102 _public member_ `bool bEnableTextureStreaming;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=CaptureSettings, AdvancedDisplay)` — Whether to texture streaming should be enabled while capturing.  Turning off texture streaming may cause much more memory to be used, but also reduces the chance of blurry textures in your captured video.
- L106 _public member_ `bool bCinematicEngineScalability;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Cinematic)` — Whether to enable cinematic engine scalability settings
- L110 _public member_ `bool bCinematicMode;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Cinematic)` — Whether to enable cinematic mode whilst capturing
- L114 _public member_ `bool bAllowMovement;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Cinematic, AdvancedDisplay, meta=(EditCondition="bCinematicMode"))` — Whether to allow player movement whilst capturing
- L118 _public member_ `bool bAllowTurning;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Cinematic, AdvancedDisplay, meta=(EditCondition="bCinematicMode"))` — Whether to allow player rotation whilst capturing
- L122 _public member_ `bool bShowPlayer;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Cinematic, AdvancedDisplay, meta=(EditCondition="bCinematicMode"))` — Whether to show the local player whilst capturing
- L126 _public member_ `bool bShowHUD;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Cinematic, AdvancedDisplay, meta=(EditCondition="bCinematicMode"))` — Whether to show the in-game HUD whilst capturing
- L130 _public member_ `bool bUsePathTracer;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Cinematic, AdvancedDisplay)` — Whether to use the path tracer (if supported) to render the scene
- L134 _public member_ `int32 PathTracerSamplePerPixel;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Cinematic, AdvancedDisplay, meta = (EditCondition = "bUsePathTracer", ClampMin = 1, UIMin = 1, UIMax = 4096))` — Number of sampler per pixel to be used when rendering the scene with the path tracer (if supported)
- L137 _public function_ `FFrameRate GetFrameRate() const` — Get which frame rate to use

### `Source/Runtime/MovieSceneCapture/Public/Protocols/AudioCaptureProtocol.h` (Public)


#### class `UNullAudioCaptureProtocol`  
`class UNullAudioCaptureProtocol : public UMovieSceneAudioCaptureProtocolBase`  
_L19-22_
- reflection: `UCLASS(meta = (DisplayName = "No Audio", CommandLineID = "NullAudio"), MinimalAPI)`
- inherits: `UMovieSceneAudioCaptureProtocolBase`
- desc: This is a null audio capture implementation which skips capturing audio. The MovieSceneCapture is explicitly aware of this type and will skip processing an audio pass if this is specified.

#### class `UMasterAudioSubmixCaptureProtocol`  
`class UMasterAudioSubmixCaptureProtocol : public UMovieSceneAudioCaptureProtocolBase`  
_L31-137_
- reflection: `UCLASS(MinimalApi, meta = (DisplayName = "Master Audio Submix", CommandLineID = "MasterAudioSubmix"))`
- inherits: `UMovieSceneAudioCaptureProtocolBase`
- desc: This is an experimental audio capture implementation which captures the final output from the master submix. This requires that your sequence can be played back in real-time (when rendering is disabled). If the sequence evaluation hitches the audio will become desynchronized due to their being more time passed in real time (platform time) than in the sequence itself.
- L36 _public function_ `UMasterAudioSubmixCaptureProtocol(const FObjectInitializer& Init) : UMovieSceneAudioCaptureProtocolBase(Init) , TotalGameRecordingTime(0.0) , TotalPlatformRecordingTime(0.0) , GameRecordingStartTime(0.0) , PlatformRecordingStartTime(0.0) , bHasSetup(false)`
- L49 _public function_ `virtual bool SetupImpl() override` — ~ UMovieSceneCaptureProtocolBase Implementation
- L55 _public function_ `virtual bool StartCaptureImpl() override`
- L81 _public function_ `virtual void PauseCaptureImpl() override`
- L105 _public function_ `virtual void BeginFinalizeImpl() override`
- L130 _protected member_ `FString FileName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Audio Options")`
- L132 _protected member_ `double TotalGameRecordingTime;`
- L133 _protected member_ `double TotalPlatformRecordingTime;`
- L134 _protected member_ `double GameRecordingStartTime;`
- L135 _protected member_ `double PlatformRecordingStartTime;`
- L136 _protected member_ `bool bHasSetup;`

### `Source/Runtime/MovieSceneCapture/Public/Protocols/CompositionGraphCaptureProtocol.h` (Public)


#### enum `EHDRCaptureGamut`  
`enum EHDRCaptureGamut : int`  
_L19-28_
- reflection: `UENUM(BlueprintType)`
- desc: Used by UCompositionGraphCaptureSettings. Matches gamut order in EDisplayColorGamut
- L21 _public enumerator_ `HCGM_Rec709 UMETA(DisplayName = "Rec.709 / sRGB")`
- L22 _public enumerator_ `HCGM_P3DCI UMETA(DisplayName = "P3 D65")`
- L23 _public enumerator_ `HCGM_Rec2020 UMETA(DisplayName = "Rec.2020")`
- L24 _public enumerator_ `HCGM_ACES UMETA(DisplayName = "ACES")`
- L25 _public enumerator_ `HCGM_ACEScg UMETA(DisplayName = "ACEScg")`
- L26 _public enumerator_ `HCGM_Linear UMETA(DisplayName = "Linear")`
- L27 _public enumerator_ `HCGM_MAX`

#### struct `FCompositionGraphCapturePasses`  
`struct FCompositionGraphCapturePasses`  
_L40-47_
- reflection: `USTRUCT(BlueprintType)`
- L46 _public member_ `TArray<FString> Value;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Composition Graph Settings")` — List of passes to record by name.

#### class `UCompositionGraphCaptureProtocol`  
`class UCompositionGraphCaptureProtocol : public UMovieSceneImageCaptureProtocolBase`  
_L50-106_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Custom Render Passes", CommandLineID="CustomRenderPasses"), MinimalAPI)`
- inherits: `UMovieSceneImageCaptureProtocolBase`
- L55 _public function_ `UCompositionGraphCaptureProtocol(const FObjectInitializer& Init) : Super(Init) , bDisableScreenPercentage(true)`
- L62 _public member_ `FCompositionGraphCapturePasses IncludeRenderPasses;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category="Composition Graph Options")` — A list of render passes to include in the capture. Leave empty to export all available passes.
- L66 _public member_ `bool bCaptureFramesInHDR;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category="Composition Graph Options")` — Whether to capture the frames as HDR textures (*.exr format)
- L70 _public member_ `int32 HDRCompressionQuality;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category="Composition Graph Options", meta = (EditCondition = "bCaptureFramesInHDR", UIMin=0, ClampMin=0, UIMax=1, ClampMax=1))` — Compression Quality for HDR Frames (0 for no compression, 1 for default compression which can be slow)
- L78 _public member_ `FSoftObjectPath PostProcessingMaterial;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category="Composition Graph Options", meta=(AllowedClasses=""))` — Custom post processing material to use for rendering
- L82 _public member_ `bool bDisableScreenPercentage;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category="Composition Graph Options")` — Whether to disable screen percentage
- L87 _public prototype_ `virtual bool SetupImpl();` — ~ UMovieSceneCaptureProtocolBase implementation
- L88 _public prototype_ `virtual void CaptureFrameImpl(const FFrameMetrics& FrameMetrics);`
- L89 _public prototype_ `virtual void TickImpl() override;`
- L90 _public prototype_ `virtual void FinalizeImpl() override;`
- L91 _public prototype_ `virtual bool HasFinishedProcessingImpl() const override;`
- L92 _public prototype_ `virtual void OnReleaseConfigImpl(FMovieSceneCaptureSettings& InSettings) override;`
- L93 _public prototype_ `virtual void OnLoadConfigImpl(FMovieSceneCaptureSettings& InSettings) override;`
- L99 _private member_ `TObjectPtr<UMaterialInterface> PostProcessingMaterialPtr;` — `UPROPERTY(transient)`
- L102 _private member_ `TWeakPtr<FSceneViewport> SceneViewport;` — The viewport we are capturing from
- L105 _private member_ `TSharedPtr<FFrameCaptureViewExtension, ESPMode::ThreadSafe> ViewExtension;` — A view extension that we use to ensure we dump out the composition graph frames with the correct settings

### `Source/Runtime/MovieSceneCapture/Public/Protocols/FrameGrabberProtocol.h` (Public)


#### class `UFrameGrabberProtocol`  
`class UFrameGrabberProtocol : public UMovieSceneImageCaptureProtocolBase`  
_L14-67_
- reflection: `UCLASS(Abstract, config=EditorPerProjectUserSettings, MinimalAPI)`
- inherits: `UMovieSceneImageCaptureProtocolBase`
- L20 _public function_ `UFrameGrabberProtocol(const FObjectInitializer& ObjectInit) : Super(ObjectInit) , DesiredPixelFormat(PF_B8G8R8A8) , RingBufferSize(3)`
- L27 _public member_ `EPixelFormat DesiredPixelFormat;` — The pixel format we want to capture in
- L30 _public member_ `uint32 RingBufferSize;` — The size of the render-target resolution surface ring-buffer
- L35 _protected prototype_ `virtual bool HasFinishedProcessingImpl() const override;` — ~ UMovieSceneCaptureProtocolBase Implementation
- L36 _protected prototype_ `virtual bool SetupImpl() override;`
- L37 _protected prototype_ `virtual void CaptureFrameImpl(const FFrameMetrics& FrameMetrics);`
- L38 _protected prototype_ `virtual void TickImpl() override;`
- L39 _protected prototype_ `virtual void BeginFinalizeImpl() override;`
- L40 _protected prototype_ `virtual void FinalizeImpl() override;`

### `Source/Runtime/MovieSceneCapture/Public/Protocols/ImageSequenceProtocol.h` (Public)


#### class `UImageSequenceProtocol`  
`class UImageSequenceProtocol : public UFrameGrabberProtocol`  
_L17-60_
- reflection: `UCLASS(Abstract, config=EditorPerProjectUserSettings, MinimalAPI)`
- inherits: `UFrameGrabberProtocol`
- L23 _public prototype_ `UImageSequenceProtocol(const FObjectInitializer& ObjInit);`
- L28 _public prototype_ `virtual FFramePayloadPtr GetFramePayload(const FFrameMetrics& FrameMetrics);` — ~UFrameGrabberProtocol implementation
- L29 _public prototype_ `virtual void ProcessFrame(FCapturedFrameData Frame);`
- L33 _public prototype_ `virtual bool SetupImpl() override;` — ~ UMovieSceneCaptureProtocol implementation
- L34 _public prototype_ `virtual void AddFormatMappingsImpl(TMap<FString, FStringFormatArg>& FormatMappings) const override;`
- L35 _public prototype_ `virtual void BeginFinalizeImpl() override;`
- L36 _public prototype_ `virtual void FinalizeImpl() override;`
- L37 _public prototype_ `virtual bool HasFinishedProcessingImpl() const override;`
- L38 _public prototype_ `virtual void OnReleaseConfigImpl(FMovieSceneCaptureSettings& InSettings) override;`
- L39 _public prototype_ `virtual void OnLoadConfigImpl(FMovieSceneCaptureSettings& InSettings) override;`
- L45 _protected member_ `EImageFormat Format;` — The format of the image to write out
- L50 _private function_ `virtual int32 GetCompressionQuality() const`
- L53 _private member_ `TMap<FString, FStringFormatArg> StringFormatMap;` — Custom string format arguments for filenames
- L56 _private member_ `IImageWriteQueue* ImageWriteQueue;` — A pointer to the image write queue used for asynchronously writing images
- L59 _private member_ `TFuture<void> FinalizeFence;` — A future that is created on BeginFinalize from a fence in the image write queue that will be fulfilled when all currently pending tasks have been completed

#### class `UCompressedImageSequenceProtocol`  
`class UCompressedImageSequenceProtocol : public UImageSequenceProtocol`  
_L63-84_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, Abstract, MinimalAPI)`
- inherits: `UImageSequenceProtocol`
- L71 _public member_ `int32 CompressionQuality;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=ImageSettings, meta=(ClampMin=1, ClampMax=100))` — Level of compression to apply to the image, between 1 (worst quality, best compression) and 100 (best quality, worst compression)
- L73 _public function_ `UCompressedImageSequenceProtocol(const FObjectInitializer& ObjInit) : Super(ObjInit)`
- L81 _protected function_ `virtual int32 GetCompressionQuality() const override`
- L82 _protected prototype_ `virtual bool SetupImpl() override;`
- L83 _protected prototype_ `virtual void AddFormatMappingsImpl(TMap<FString, FStringFormatArg>& FormatMappings) const override;`

#### class `UImageSequenceProtocol_BMP`  
`class UImageSequenceProtocol_BMP : public UImageSequenceProtocol`  
_L87-98_
- reflection: `UCLASS(meta=(DisplayName="Image Sequence (bmp)", CommandLineID="BMP"), MinimalAPI)`
- inherits: `UImageSequenceProtocol`
- L93 _public function_ `UImageSequenceProtocol_BMP(const FObjectInitializer& ObjInit) : Super(ObjInit)`

#### class `UImageSequenceProtocol_PNG`  
`class UImageSequenceProtocol_PNG : public UCompressedImageSequenceProtocol`  
_L101-112_
- reflection: `UCLASS(meta=(DisplayName="Image Sequence (png)", CommandLineID="PNG"), MinimalAPI)`
- inherits: `UCompressedImageSequenceProtocol`
- L107 _public function_ `UImageSequenceProtocol_PNG(const FObjectInitializer& ObjInit) : Super(ObjInit)`

#### class `UImageSequenceProtocol_JPG`  
`class UImageSequenceProtocol_JPG : public UCompressedImageSequenceProtocol`  
_L115-126_
- reflection: `UCLASS(meta=(DisplayName="Image Sequence (jpg)", CommandLineID="JPG"), MinimalAPI)`
- inherits: `UCompressedImageSequenceProtocol`
- L121 _public function_ `UImageSequenceProtocol_JPG(const FObjectInitializer& ObjInit) : Super(ObjInit)`

#### class `UImageSequenceProtocol_EXR`  
`class UImageSequenceProtocol_EXR : public UImageSequenceProtocol`  
_L129-153_
- reflection: `UCLASS(meta=(DisplayName="Image Sequence (exr)", CommandLineID="EXR"), MinimalAPI)`
- inherits: `UImageSequenceProtocol`
- L137 _public member_ `bool bCompressed;` — `UPROPERTY(config, EditAnywhere, Category=ImageSettings)` — Whether to write out compressed or uncompressed EXRs
- L141 _public member_ `TEnumAsByte<EHDRCaptureGamut> CaptureGamut;` — `UPROPERTY(config, EditAnywhere, Category=ImageSettings)` — The color gamut to use when storing HDR captured data.
- L143 _public prototype_ `UImageSequenceProtocol_EXR(const FObjectInitializer& ObjInit);`
- L146 _private function_ `virtual int32 GetCompressionQuality() const override`
- L147 _private prototype_ `virtual bool SetupImpl() override;`
- L148 _private prototype_ `virtual void FinalizeImpl() override;`
- L149 _private prototype_ `virtual void AddFormatMappingsImpl(TMap<FString, FStringFormatArg>& FormatMappings) const override;`
- L151 _private member_ `EDisplayColorGamut RestoreColorGamut;`
- L152 _private member_ `EDisplayOutputFormat RestoreOutputDevice;`

### `Source/Runtime/MovieSceneCapture/Public/Protocols/UserDefinedCaptureProtocol.h` (Public)


#### struct `FCapturedPixelsID`  
`struct FCapturedPixelsID`  
_L19-29_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure used as an identifier for a particular buffer within a capture.
- L24 _public prototype_ `FString ToString() const;` — Convert this strream ID to a string
- L28 _public member_ `TMap<FName, FName> Identifiers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Capture)` — Map of identifiers to their values for this ID.

#### struct `FCapturedPixels`  
`struct FCapturedPixels`  
_L34-39_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public member_ `TSharedPtr<FImagePixelData, ESPMode::ThreadSafe> ImageData;`

#### class `UUserDefinedCaptureProtocol`  
`class UUserDefinedCaptureProtocol : public UMovieSceneImageCaptureProtocolBase`  
_L45-228_
- reflection: `UCLASS(Abstract, Blueprintable, meta=(DisplayName="Capture Protocol"), MinimalAPI)`
- inherits: `UMovieSceneImageCaptureProtocolBase`
- desc: A blueprintable capture protocol that defines how to capture frames from the engine
- L52 _public prototype_ `UUserDefinedCaptureProtocol(const FObjectInitializer& ObjInit);`
- L61 _protected prototype_ `void OnPreTick();` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called before the capture process itself is ticked, before each frame is set up for capture Useful for any pre-frame set up or resetting the previous frame's state
- L67 _protected prototype_ `void OnTick();` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called after the capture process itself is ticked, after the frame is set up for capture, but before most actors have ticked
- L74 _protected prototype_ `bool OnSetup();` — `UFUNCTION(BlueprintNativeEvent, Category=Capture)` — Called once at the start of the capture process, but before any warmup frames @return true if this protocol set up successfully, false otherwise
- L75 _protected function_ `virtual bool OnSetup_Implementation()`
- L81 _protected prototype_ `void OnWarmUp();` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called when the capture process is warming up. Protocols may transition from either an initialized, or capturing state to warm-up
- L87 _protected prototype_ `void OnStartCapture();` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called when this protocol should start capturing frames
- L93 _protected prototype_ `void OnCaptureFrame();` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called when this protocol should capture the current frame
- L99 _protected prototype_ `void OnPauseCapture();` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called when this protocol should temporarily stop capturing frames
- L105 _protected prototype_ `void OnBeginFinalize();` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called when this protocol is going to be shut down - should not capture any more frames
- L112 _protected prototype_ `bool OnCanFinalize() const;` — `UFUNCTION(BlueprintNativeEvent, Category=Capture)` — Called to check whether this protocol has finished any pending tasks, and can now be shut down
- L113 _protected function_ `virtual bool OnCanFinalize_Implementation() const`
- L120 _protected prototype_ `void OnFinalize();` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called to complete finalization of this protocol
- L127 _protected prototype_ `void OnPixelsReceived(const FCapturedPixels& Pixels, const FCapturedPixelsID& ID, FFrameMetrics FrameMetrics);` — `UFUNCTION(BlueprintImplementableEvent, Category=Capture)` — Called when pixels have been received for the specified stream name
- L139 _public prototype_ `void ResolveBuffer(UTexture* Buffer, const FCapturedPixelsID& BufferID);` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Resolve the specified buffer and pass it directly to the specified handler when done (does not pass to any bound streams) @param Buffer          The desired buffer to save @param BufferID        The ID of this buffer that is passed to the pixel handler (e.g. a composition pass name).
- L148 _public prototype_ `void StartCapturingFinalPixels(const FCapturedPixelsID& StreamID);` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Instruct this protocol to start capturing LDR final pixels (including slate widgets and burn-ins) @param StreamID        The identifier to use for the final pixels buffer
- L155 _public prototype_ `void StopCapturingFinalPixels();` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Instruct this protocol to stop capturing LDR final pixels
- L162 _public prototype_ `virtual FString GenerateFilename(const FFrameMetrics& InFrameMetrics) const;` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Generate a filename for the current frame
- L169 _public function_ `FFrameMetrics GetCurrentFrameMetrics() const` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Access this protocol's current frame metrics
- L179 _public prototype_ `void OnPixelsReceivedImpl(const FCapturedPixels& Pixels, const FCapturedPixelsID& StreamID, FFrameMetrics FrameMetrics);` — Called when image pixel data is ready to be processed
- L185 _public prototype_ `void ReportOutstandingWork(int32 NumNewOperations);` — INTERNAL: Report that the protocol is dispatching the specified number of asynchronous tasks that need to be completed before this protocol can be finalized
- L190 _protected prototype_ `virtual void PreTickImpl() override;` — ~ Begin UMovieSceneCaptureProtocolBase implementation
- L191 _protected prototype_ `virtual void TickImpl() override;`
- L192 _protected prototype_ `virtual bool SetupImpl() override;`
- L193 _protected prototype_ `virtual void WarmUpImpl() override;`
- L194 _protected prototype_ `virtual bool StartCaptureImpl() override;`
- L195 _protected prototype_ `virtual void CaptureFrameImpl(const FFrameMetrics& FrameMetrics) override;`
- L196 _protected prototype_ `virtual void BeginFinalizeImpl() override;`
- L197 _protected prototype_ `virtual bool HasFinishedProcessingImpl() const override;`
- L198 _protected prototype_ `virtual void FinalizeImpl() override;`
- L199 _protected prototype_ `virtual void AddFormatMappingsImpl(TMap<FString, FStringFormatArg>& FormatMappings) const override;`
- L203 _protected function_ `virtual UWorld* GetWorld() const override` — ~ Begin UObject implementation
- L210 _protected member_ `TObjectPtr<UWorld> World;` — `UPROPERTY(transient, BlueprintReadOnly, Category=Capture)` — World pointer assigned on Setup
- L215 _protected member_ `TUniquePtr<FFrameGrabber> FinalPixelsFrameGrabber;` — A frame grabber responsible for capturing LDR final pixels from the viewport when requested
- L218 _protected member_ `TAtomic<int32> NumOutstandingOperations;` — A running count of the number of currently pending async operations
- L221 _protected member_ `FFrameMetrics CachedFrameMetrics;` — Frame metrics cached for the current frame
- L224 _protected member_ `FCapturedPixelsID FinalPixelsID;` — The ID of the final pixel stream cached from StartCapturingFinalPixels
- L227 _protected member_ `const FCapturedPixelsID* CurrentStreamID;` — Transient stream ID used only during filename generation

#### class `UUserDefinedImageCaptureProtocol`  
`class UUserDefinedImageCaptureProtocol : public UUserDefinedCaptureProtocol`  
_L235-306_
- reflection: `UCLASS(Abstract, config=EditorPerProjectUserSettings, Blueprintable, meta=(DisplayName="Capture Protocol"), MinimalAPI)`
- inherits: `UUserDefinedCaptureProtocol`
- desc: A blueprintable capture protocol tailored to capturing and exporting frames as images
- L242 _public prototype_ `UUserDefinedImageCaptureProtocol(const FObjectInitializer& ObjInit);`
- L246 _public member_ `EDesiredImageFormat Format;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category=Capture)` — The image format to save as
- L250 _public member_ `bool bEnableCompression;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category=Capture, meta=(InlineEditConditionToggle))` — Whether to save images with compression or not. Not supported for bitmaps.
- L254 _public member_ `int32 CompressionQuality;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category=Capture, meta=(EditCondition=bEnableCompression))` — The compression quality for the image type. For EXRs, 0 = Default ZIP compression, 1 = No compression, PNGs and JPEGs expect a value between 0 and 100
- L267 _public prototype_ `FString GenerateFilenameForBuffer(UTexture* Buffer, const FCapturedPixelsID& StreamID);` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Generate a filename for the specified buffer using this protocol's file name formatter @param Buffer          The desired buffer to generate a filename for @param StreamID        The ID of the stream for this buffer (e.g. a composition pass name) @return A fully qualified file name
- L276 _public prototype_ `FString GenerateFilenameForCurrentFrame();` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Generate a filename for the current frame using this protocol's file name formatter @return A fully qualified file name for the current frame number
- L285 _public prototype_ `void WriteImageToDisk(const FCapturedPixels& PixelData, const FCapturedPixelsID& StreamID, const FFrameMetrics& FrameMetrics, bool bCopyImageData = false);` — `UFUNCTION(BlueprintCallable, Category=Capture)` — Generate a filename for the current frame using this protocol's file name formatter @return A fully qualified file name for the current frame number
- L290 _protected prototype_ `virtual void OnReleaseConfigImpl(FMovieSceneCaptureSettings& InSettings) override;` — ~ Begin UMovieSceneCaptureProtocolBase implementation
- L291 _protected prototype_ `virtual void OnLoadConfigImpl(FMovieSceneCaptureSettings& InSettings) override;`
- L299 _public prototype_ `void OnFileWritten();` — Called on the main thread when an async operation dispatched from this class has completed (either successfully or otherwise)
- L304 _private prototype_ `virtual FString GenerateFilename(const FFrameMetrics& InFrameMetrics) const override;` — ~ Begin UUserDefinedCaptureProtocol implementation

### `Source/Runtime/MovieSceneCapture/Public/Protocols/VideoCaptureProtocol.h` (Public)


#### class `UVideoCaptureProtocol`  
`class UVideoCaptureProtocol : public UFrameGrabberProtocol`  
_L15-47_
- reflection: `UCLASS(meta=(DisplayName="Video Sequence (avi)", CommandLineID="Video"), MinimalAPI)`
- inherits: `UFrameGrabberProtocol`
- L20 _public function_ `UVideoCaptureProtocol(const FObjectInitializer& Init) : Super(Init) , bUseCompression(true) , CompressionQuality(75)`
- L29 _public member_ `bool bUseCompression;` — `UPROPERTY(config, EditAnywhere, Category=VideoSettings)`
- L32 _public member_ `float CompressionQuality;` — `UPROPERTY(config, EditAnywhere, Category=VideoSettings, meta=(ClampMin=1, ClampMax=100, EditCondition=bUseCompression))`
- L35 _public prototype_ `virtual bool SetupImpl() override;`
- L36 _public prototype_ `virtual void FinalizeImpl() override;`
- L37 _public prototype_ `virtual FFramePayloadPtr GetFramePayload(const FFrameMetrics& FrameMetrics);`
- L38 _public prototype_ `virtual void ProcessFrame(FCapturedFrameData Frame);`
- L39 _public prototype_ `virtual bool CanWriteToFileImpl(const TCHAR* InFilename, bool bOverwriteExisting) const override;`
- L43 _protected prototype_ `void ConditionallyCreateWriter();`
- L46 _private member_ `TArray<TUniquePtr<FAVIWriter>> AVIWriters;`
