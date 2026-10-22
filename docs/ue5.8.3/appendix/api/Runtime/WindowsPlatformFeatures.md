# Runtime / WindowsPlatformFeatures

- module root: `Source/Runtime/Windows/WindowsPlatformFeatures`
- headers: 6; symbols: 105
- symbol kinds: class=5, delegate=3, enum=1, enumerator=3, function=13, macro=5, member=29, prototype=45, typedef=1
- PrivateDependencyModuleNames: AVEncoder, ApplicationCore, AudioMixer, Core, CoreUObject, Engine, GameplayMediaEncoder

### `Source/Runtime/Windows/WindowsPlatformFeatures/Private/HighlightRecorder.h` (Private)


#### class `FHighlightRecorder`  
`class FHighlightRecorder final : private IGameplayMediaEncoderListener`  
_L22-202_
- inherits: `IGameplayMediaEncoderListener`
- L25 _public prototype_ `FHighlightRecorder();`
- L26 _public prototype_ `~FHighlightRecorder();`
- L30 _public function_ `EState GetState() const`
- L33 _public prototype_ `bool Start(double RingBufferDurationSecs);`
- L34 _public prototype_ `bool Pause(bool bPause);`
- L35 _public prototype_ `void Stop();`
- L36 _public function_ `bool IsSaving() const`
- L41 _public typedef_ `using FDoneCallback = TFunction<void(bool , const FString& )>;`
- L42 _public prototype_ `bool SaveHighlight(const TCHAR* Filename, FDoneCallback DoneCallback, double MaxDurationSecs = 1.0 * 60 * 60);`
- L45 _private prototype_ `bool SaveHighlightInBackground(const FString& Filename, double MaxDurationSecs);`
- L46 _private prototype_ `bool SaveHighlightInBackgroundImpl(const FString& Filename, double MaxDurationSecs);`
- L47 _private prototype_ `bool InitialiseMp4Writer(const FString& Filename, bool bHasAudio);`
- L49 _private prototype_ `bool GetSavingStart(const TArray<AVEncoder::FMediaPacket>& Samples, FTimespan MaxDuration, int& OutStartIndex, FTimespan& OutStartTime) const;`
- L54 _private prototype_ `FTimespan GetRecordingTime() const;` — takes into account if we've been paused and shifts current time back to compensate paused state so all timestamps are continuous even over paused pieces
- L60 _private prototype_ `void OnMediaSample(const AVEncoder::FMediaPacket& Sample) override;` — IGameplayMediaEncoderListener implementation
- L64 _private member_ `TAtomic<EState> State{ EState::Stopped };`
- L66 _private member_ `TUniquePtr<FWmfMp4Writer> Mp4Writer;`
- L68 _private member_ `FWmfRingBuffer RingBuffer;`
- L72 _private member_ `uint64 NumPushedFrames = 0;`
- L74 _private member_ `FTimespan RecordingStartTime = 0;`
- L77 _private member_ `FTimespan PauseTimestamp = 0;` — if currently paused, when it happened
- L79 _private member_ `FTimespan TotalPausedDuration = 0;` — for how long recording has been paused since it's started
- L81 _private member_ `TUniquePtr<FThread> BackgroundSaving;`
- L82 _private member_ `FDoneCallback DoneCallback;`
- L83 _private member_ `FThreadSafeBool bSaving = false;`
- L85 _private member_ `DWORD AudioStreamIndex = 0;`
- L86 _private member_ `DWORD VideoStreamIndex = 0;`
- L90 _public function_ `static void Start(const TArray<FString>& Args, UWorld*, FOutputDevice& Output)`
- L113 _public function_ `static void StopCmd()`
- L125 _public function_ `static void PauseCmd()`
- L135 _public function_ `static void ResumeCmd()`
- L145 _public function_ `static void SaveCmd(const TArray<FString>& Args, UWorld*, FOutputDevice& Output)`
- L182 _private function_ `static bool CheckSingleton()`
- L195 _private function_ `static FHighlightRecorder* Get()`
- L200 _private member_ `static FHighlightRecorder* Singleton;`

#### enum `FHighlightRecorder::EState`  
`enum class EState`  
_L28-28_
- L28 _public enumerator_ `enum class EState { Stopped, Recording, Paused }; EState GetState() const { return State; } bool Start(double RingBufferDurationSecs); bool Pause(bool bPause); void Stop();`
- L28 _public enumerator_ `enum class EState { Stopped, Recording, Paused }; EState GetState() const { return State; } bool Start(double RingBufferDurationSecs); bool Pause(bool bPause); void Stop();`
- L28 _public enumerator_ `enum class EState { Stopped, Recording, Paused }; EState GetState() const { return State; } bool Start(double RingBufferDurationSecs); bool Pause(bool bPause); void Stop();`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(HighlightRecorder, Log, VeryVerbose);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(HighlightRecorder, Log, VeryVerbose);`
- L173 _function_ `` (scope `FHighlightRecorder::SaveCmd`)

### `Source/Runtime/Windows/WindowsPlatformFeatures/Private/WindowsVideoRecordingSystem.h` (Private)


#### class `FWindowsVideoRecordingSystem`  
`class FWindowsVideoRecordingSystem : public IVideoRecordingSystem PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L22-62_
- inherits: `IVideoRecordingSystemPRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L26 _public prototype_ `FWindowsVideoRecordingSystem();`
- L30 _public prototype_ `void EnableRecording(const bool bEnableRecording) override;` — IVideoRecordingSystem interface
- L31 _public prototype_ `bool IsEnabled() const override;`
- L32 _public prototype_ `bool NewRecording(const TCHAR* DestinationFileName, FVideoRecordingParameters Parameters = FVideoRecordingParameters()) override;`
- L33 _public prototype_ `void StartRecording() override;`
- L34 _public prototype_ `void PauseRecording() override;`
- L35 _public prototype_ `virtual uint64 GetMinimumRecordingSeconds() const override;`
- L36 _public prototype_ `virtual uint64 GetMaximumRecordingSeconds() const override;`
- L37 _public prototype_ `float GetCurrentRecordingSeconds() const override;`
- L38 _public prototype_ `void FinalizeRecording(const bool bSaveRecording, const FText& Title, const FText& Comment, const bool bStopAutoContinue = true) override;`
- L39 _public prototype_ `EVideoRecordingState GetRecordingState() const override;`
- L42 _private prototype_ `void NextRecording();`
- L43 _private prototype_ `void FinalizeCallbackOnGameThread(bool bSaved, bool bAutoContinue, FString Path, bool bBroadcast);`
- L45 _private member_ `TAtomic<EVideoRecordingState> RecordState{ EVideoRecordingState::None };`
- L47 _private member_ `FVideoRecordingParameters Parameters;`
- L49 _private member_ `FString BaseFilename;`
- L50 _private member_ `FString CurrentFilename;`
- L51 _private member_ `uint64 RecordingIndex = 0;`
- L52 _private member_ `uint64 CurrentStartRecordingCycles = 0;`
- L53 _private member_ `uint64 CyclesBeforePausing = 0;`
- L56 _private member_ `TUniquePtr<FHighlightRecorder> Recorder;` — If this is nullptr, then it means video recording is not enabled
- L58 _private member_ `bool bAudioFormatChecked = false;`
- L61 _private member_ `TUniquePtr<FWindowsScreenRecording> ScreenshotAndRecorderHandler;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(WindowsVideoRecordingSystem, VeryVerbose, VeryVerbose);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(WindowsVideoRecordingSystem, VeryVerbose, VeryVerbose);`

### `Source/Runtime/Windows/WindowsPlatformFeatures/Private/WmfMp4Writer.h` (Private)


#### class `FWmfMp4Writer`  
`class FWmfMp4Writer final`  
_L12-36_
- L15 _public prototype_ `bool Initialize(const TCHAR* Filename);`
- L21 _public prototype_ `TOptional<DWORD> CreateAudioStream(const FString& Codec, const AVEncoder::FAudioConfig& Config);` — Create an audio stream and return the its index on success
- L26 _public prototype_ `TOptional<DWORD> CreateVideoStream(const FString& Codec, const AVEncoder::FVideoConfig& Config);` — Create a video stream and return the its index on success
- L28 _public prototype_ `bool Write(const AVEncoder::FMediaPacket& InSample, DWORD StreamIndex);`
- L31 _public prototype_ `bool Start();`
- L32 _public prototype_ `bool Finalize();`
- L35 _private member_ `TRefCountPtr<IMFSinkWriter> Writer;`

### `Source/Runtime/Windows/WindowsPlatformFeatures/Private/WmfPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define WMFMEDIA_SUPPORTED_PLATFORM (PLATFORM_WINDOWS && !UE_SERVER)`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(WMF, Log, VeryVerbose);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(WMF, Log, VeryVerbose);`
- L24 _function_ `inline const FString GetComErrorDescription(HRESULT Res)`
- L47 _macro_ `#define CHECK_HR(COM_call)\` — macro to deal with COM calls inside a function that returns `false` on error
- L58 _macro_ `#define CHECK_HR_COM(COM_call)\` — macro to deal with COM calls inside COM method (that returns HRESULT)
- L69 _macro_ `#define CHECK_HR_VOID(COM_call)\` — macro to deal with COM calls inside COM method (that simply returns)
- L81 _macro_ `#define CHECK_HR_DEFAULT(COM_call)\` — macro to deal with COM calls inside a function and return `{}` on error This has the advantage of being able to return any type that can be initialized with `{}`

### `Source/Runtime/Windows/WindowsPlatformFeatures/Private/WmfRingBuffer.h` (Private)


#### class `FWmfRingBuffer`  
`class FWmfRingBuffer`  
_L10-46_
- L13 _public function_ `FTimespan GetMaxDuration() const`
- L18 _public function_ `void SetMaxDuration(FTimespan InMaxDuration)`
- L23 _public prototype_ `FTimespan GetDuration() const;`
- L25 _public prototype_ `void PauseCleanup(bool bPause);`
- L28 _public prototype_ `void Push(AVEncoder::FMediaPacket&& Sample);`
- L30 _public prototype_ `TArray<AVEncoder::FMediaPacket> GetCopy();`
- L33 _public prototype_ `void Reset();`
- L36 _private prototype_ `void Cleanup();`
- L39 _private member_ `FTimespan MaxDuration = 0;`
- L40 _private member_ `FCriticalSection Mutex;`
- L41 _private member_ `FThreadSafeBool bCleanupPaused = false;`
- L44 _private member_ `TArray<AVEncoder::FMediaPacket> Samples;`

### `Source/Runtime/Windows/WindowsPlatformFeatures/Public/WindowsPlatformFeatures.h` (Public)


#### class `FWindowsPlatformFeaturesModule`  
`class FWindowsPlatformFeaturesModule : public IPlatformFeaturesModule`  
_L8-25_
- inherits: `IPlatformFeaturesModule`
- L13 _public prototype_ `FWindowsPlatformFeaturesModule();` — Creates a new instance of the audio device implemented by the module.
- L15 _public prototype_ `virtual IVideoRecordingSystem* GetVideoRecordingSystem() override;`
- L16 _public prototype_ `virtual class ISaveGameSystem* GetSaveGameSystem() override;`
- L18 _public prototype_ `void RegisterVideoRecordingSystem(TSharedPtr<IVideoRecordingSystem> VideoRecordingSystem);`
- L21 _private prototype_ `void StartupModule() override;`
- L24 _private member_ `TSharedPtr<IVideoRecordingSystem> VideoRecordingSystem;`
