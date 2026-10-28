# Plugins / AudioCaptureTimecodeProvider

- module root: `Plugins/Media/AudioCaptureTimecodeProvider/Source/AudioCaptureTimecodeProvider`
- headers: 2; symbols: 16
- symbol kinds: class=1, delegate=1, function=1, member=6, prototype=7
- PublicDependencyModuleNames: AudioCapture, AudioCaptureCore, Core, CoreUObject, Engine, LinearTimecode, TimeManagement

### `Plugins/Media/AudioCaptureTimecodeProvider/Source/AudioCaptureTimecodeProvider/Public/AudioCaptureTimecodeProvider.h` (Public)


#### class `UAudioCaptureTimecodeProvider`  
`class UAudioCaptureTimecodeProvider : public UGenlockedTimecodeProvider`  
_L16-65_
- reflection: `UCLASS(Blueprintable, editinlinenew)`
- inherits: `UGenlockedTimecodeProvider`
- desc: Read the LTC from the audio capture device.
- L26 _public member_ `bool bDetectFrameRate;` — `UPROPERTY(EditAnywhere, Category = TimecodeProvider)` — Detect the frame rate from the audio source. It may takes some extra time before the frame rate is properly detected.
- L30 _public member_ `bool bAssumeDropFrameFormat;` — `UPROPERTY(EditAnywhere, Category = TimecodeProvider, meta = (EditCondition = "bDetectFrameRate"))` — When detecting the frame rate. Assume the frame rate is a drop frame format.
- L36 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(EditAnywhere, Category = TimecodeProvider, meta = (EditCondition = "!bDetectFrameRate"))` — Frame expected from the audio source.
- L42 _public member_ `int32 AudioChannel;` — `UPROPERTY(EditAnywhere, Category = TimecodeProvider, meta = (ClampMin = 1))` — Index of the Channel to used for the capture.
- L46 _public prototype_ `virtual bool FetchTimecode(FQualifiedFrameTime& OutFrameTime) override;`
- L47 _public function_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override`
- L48 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L49 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L52 _public prototype_ `virtual void BeginDestroy() override;`
- L55 _private prototype_ `FTimecode GetTimecodeInternal() const;`
- L56 _private prototype_ `FFrameRate GetFrameRateInternal() const;`
- L61 _private member_ `FLinearTimecodeAudioCaptureCustomTimeStepImplementation* Implementation;`
- L64 _private member_ `ETimecodeProviderSynchronizationState SynchronizationState;` — The current SynchronizationState of the TimecodeProvider

### `Plugins/Media/AudioCaptureTimecodeProvider/Source/AudioCaptureTimecodeProvider/Public/AudioCaptureTimecodeProviderModule.h` (Public)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioCaptureTimecodeProvider, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioCaptureTimecodeProvider, Log, All);`
