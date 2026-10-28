# Editor / MovieSceneCaptureDialog

- module root: `Source/Editor/MovieSceneCaptureDialog`
- headers: 1; symbols: 62
- symbol kinds: class=1, delegate=1, enum=1, enumerator=4, function=11, macro=1, member=18, prototype=21, struct=4
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, InputCore, Json, JsonUtilities, MovieScene, MovieSceneCapture, MovieSceneTools, PropertyEditor, SessionServices, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: 

### `Source/Editor/MovieSceneCaptureDialog/Public/MovieSceneCaptureDialogModule.h` (Public)


#### enum `ECaptureStatus`  
`enum class ECaptureStatus`  
_L18-24_
- L20 _public enumerator_ `Pending`
- L21 _public enumerator_ `Success`
- L22 _public enumerator_ `Failure`
- L23 _public enumerator_ `Unknown`

#### class `IMovieSceneCaptureDialogModule`  
`class IMovieSceneCaptureDialogModule : public IModuleInterface`  
_L26-41_
- inherits: `IModuleInterface`
- L29 _public function_ `static IMovieSceneCaptureDialogModule& Get()`
- L34 _public prototype_ `virtual void OpenDialog(const TSharedRef<class FTabManager>& TabManager, UMovieSceneCapture* CaptureObject, TSharedPtr<INumericTypeInterface<double>> InNumericTypeInterface) = 0;`
- L37 _public prototype_ `virtual UWorld* GetCurrentlyRecordingWorld() = 0;` — Get the world we're currently recording from, if an in process record is happening
- L39 _public prototype_ `virtual TSharedPtr<FMovieSceneCaptureBase> GetCurrentCapture() const = 0;`
- L40 _public prototype_ `virtual void StartCapture(UMovieSceneCapture* InCaptureSettings) = 0;`

#### struct `FCaptureState`  
`struct FCaptureState`  
_L44-60_
- desc: Stores the Capture State for display in the UI. Combines both capture status and any additional context information.
- L47 _public function_ `explicit FCaptureState(ECaptureStatus InState = ECaptureStatus::Unknown) : Status(InState) , Code(0)` — Construction from an enum
- L51 _public function_ `explicit FCaptureState(int32 InCode) : Status(InCode == 0 ? ECaptureStatus::Success : ECaptureStatus::Failure) , Code(InCode)` — Construction from a process exit code
- L56 _public prototype_ `FText GetDetailText() const;` — Get any additional detailed text
- L58 _public member_ `ECaptureStatus Status;`
- L59 _public member_ `int32 Code;`

#### struct `FMovieSceneCaptureBase`  
`struct FMovieSceneCaptureBase : TSharedFromThis<FMovieSceneCaptureBase>`  
_L62-91_
- inherits: `TSharedFromThis<FMovieSceneCaptureBase>`
- L65 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FCaptureStateStopped, bool);`
- L67 _public prototype_ `virtual ~FMovieSceneCaptureBase() = default;`
- L68 _public function_ `virtual void OnCaptureStarted()`
- L69 _public prototype_ `virtual void OnCaptureFinished(bool bSuccess);`
- L70 _public function_ `virtual UWorld* GetWorld() const`
- L71 _public function_ `virtual void Start()`
- L72 _public function_ `virtual void Cancel()`
- L73 _public function_ `virtual FCaptureState GetCaptureState() const`
- L80 _public member_ `FCaptureStateStopped CaptureStoppedDelegate;` — Multicast Delegate for when capture is stopped. Returns true if the capture was completed successfully.
- L84 _protected member_ `TSharedPtr<SNotificationItem> InProgressCaptureNotification;` — Pointer to the capture notification pop up.
- L87 _protected member_ `UMovieSceneCapture* CaptureObject;` — Cached copy of our capture object.
- L90 _protected member_ `TFunction<void(bool)> OnFinishedCallback;` — Callback to call when we finish capturing.

#### struct `FInEditorCapture`  
`struct FInEditorCapture : FMovieSceneCaptureBase`  
_L93-139_
- inherits: `FMovieSceneCaptureBase`
- L95 _public function_ `FInEditorCapture(UMovieSceneCapture* InCaptureObject, const TFunction<void(bool)>& InOnFinishedCallback)`
- L103 _public function_ `virtual UWorld* GetWorld() const override` — FMovieSceneCaptureBase interface
- L108 _public prototype_ `virtual void OnCaptureStarted() override;`
- L109 _public prototype_ `virtual void Start() override;`
- L110 _public prototype_ `virtual void Cancel() override;`
- L111 _public prototype_ `virtual FCaptureState GetCaptureState() const override;`
- L116 _private prototype_ `void OverridePlaySettings(class ULevelEditorPlaySettings* PlayInEditorSettings);` — Overrides the Level Editor Play settings to specifically disable some things (such as audio playback)
- L118 _private prototype_ `void OnPIEViewportStarted();` — Called when the PIE Viewport is created.
- L120 _private prototype_ `void Shutdown();` — Shuts down the capture setup , called when PIE is closed by the user or the sequence finishes playing.
- L122 _private prototype_ `void OnEndPIE(bool bIsSimulating);` — Called when the user closes the PIE instance window.
- L124 _private prototype_ `void OnLevelSequenceFinished();` — Called when the Sequence finishes playing to the end.
- L127 _private member_ `UWorld* CapturingFromWorld;`
- L129 _private member_ `bool bScreenMessagesWereEnabled;`
- L130 _private member_ `float TransientPrimaryVolume;`
- L131 _private member_ `int32 BackedUpStreamingPoolSize;`
- L132 _private member_ `int32 BackedUpUseFixedPoolSize;`
- L133 _private member_ `int32 BackedUpTextureStreaming;`
- L134 _private member_ `TArray<uint8> BackedUpPlaySettings;`
- L136 _private member_ `bool CachedPathTracingMode = false;`
- L137 _private member_ `struct FEngineShowFlags* CachedEngineShowFlags = nullptr;`
- L138 _private member_ `TSubclassOf<AGameModeBase> CachedGameMode;`

#### struct `FNewProcessCapture`  
`struct FNewProcessCapture : FMovieSceneCaptureBase`  
_L141-163_
- inherits: `FMovieSceneCaptureBase`
- L144 _public function_ `FNewProcessCapture(UMovieSceneCapture* InCaptureObject, const FString& InMapNameToLoad, const TFunction<void(bool)>& InOnFinishedCallback)`
- L154 _public prototype_ `virtual void Start() override;` — FMovieSceneCaptureBase
- L155 _public prototype_ `virtual void Cancel() override;`
- L156 _public prototype_ `virtual void OnCaptureStarted() override;`
- L157 _public prototype_ `virtual FCaptureState GetCaptureState() const override;`
- L161 _protected member_ `TSharedPtr<FProcHandle> SharedProcHandle;`
- L162 _protected member_ `FString MapNameToLoad;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENECAPTUREDIALOG_API`
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FCaptureStateStopped, bool);`
