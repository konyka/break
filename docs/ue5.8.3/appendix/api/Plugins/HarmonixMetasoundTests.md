# Plugins / HarmonixMetasoundTests

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundTests`
- headers: 3; symbols: 91
- symbol kinds: class=11, delegate=1, function=7, member=36, namespace=1, prototype=34, struct=1
- PrivateDependencyModuleNames: AudioExtensions, Core, CoreUObject, Engine, FunctionalTesting, HarmonixDsp, HarmonixMetasound, HarmonixMidi, MetasoundEngine, MetasoundEngineTest, MetasoundFrontend, MetasoundGenerator, MetasoundGraphCore, MetasoundStandardNodes, Projects, SignalProcessing, UnrealEd

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundTests/Private/HarmonixFunctionalTestAction.h` (Private)


#### class `UHarmonixFunctionalTestAction`  
`class UHarmonixFunctionalTestAction : public UObject`  
_L13-65_
- reflection: `UCLASS(Blueprintable, EditInlineNew, CollapseCategories, HideCategories=(Object), Abstract)`
- inherits: `UObject`
- L19 _public function_ `virtual void Prepare_Implementation(AFunctionalTest* Test)`
- L21 _public function_ `virtual void OnStart_Implementation(AFunctionalTest* Test)`
- L23 _public function_ `virtual void OnFinished_Implementation()`
- L25 _public function_ `virtual void Tick_Implementation(AFunctionalTest* Test, float DeltaSeconds)`
- L27 _public function_ `bool ShouldContinue() const`
- L33 _public prototype_ `void Prepare(AFunctionalTest* Test);` — `UFUNCTION(BlueprintNativeEvent, Category="Functional Testing")`
- L36 _public prototype_ `void OnStart(AFunctionalTest* Test);` — `UFUNCTION(BlueprintNativeEvent, Category="Functional Testing")`
- L39 _public prototype_ `void OnFinished();` — `UFUNCTION(BlueprintNativeEvent, Category="Functional Testing")`
- L42 _public prototype_ `void Tick(AFunctionalTest* Test, float DeltaSeconds);` — `UFUNCTION(BlueprintNativeEvent, Category = "Functional Testing")`
- L46 _public function_ `void Finish(bool bContinue = true)` — `UFUNCTION(BlueprintCallable, Category = "Functional Testing")` — called by the user when finished with the step
- L59 _public function_ `bool IsFinished() const` — `UFUNCTION(BlueprintPure, Category = "Functional Testing")`
- L63 _private member_ `bool bIsFinished = false;`
- L64 _private member_ `bool bShouldContinue = false;`

#### class `UHarmonixFunctionalTestActionSequence`  
`class UHarmonixFunctionalTestActionSequence : public UHarmonixFunctionalTestAction`  
_L68-92_
- reflection: `UCLASS(Blueprintable, meta=(DisplayName = "Action Sequence"))`
- inherits: `UHarmonixFunctionalTestAction`
- L74 _public prototype_ `virtual void Prepare_Implementation(AFunctionalTest* Test) override;`
- L76 _public prototype_ `virtual void OnStart_Implementation(AFunctionalTest* Test) override;`
- L78 _public prototype_ `virtual void Tick_Implementation(AFunctionalTest* Test, float DeltaSeconds) override;`
- L80 _public prototype_ `virtual void OnFinished_Implementation() override;`
- L83 _public member_ `TArray<TObjectPtr<UHarmonixFunctionalTestAction>> ActionSequence;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Functional Testing")`
- L88 _private member_ `TArray<TObjectPtr<UHarmonixFunctionalTestAction>> ActionStack;` — `UPROPERTY(Transient)`
- L91 _private member_ `TObjectPtr<UHarmonixFunctionalTestAction> CurrentAction;` — `UPROPERTY(Transient)`

#### class `UHarmonixFunctionalTestActionParallel`  
`class UHarmonixFunctionalTestActionParallel : public UHarmonixFunctionalTestAction`  
_L95-118_
- reflection: `UCLASS(Blueprintable, meta=(DisplayName = "Parallel Actions"))`
- inherits: `UHarmonixFunctionalTestAction`
- L101 _public prototype_ `virtual void Prepare_Implementation(AFunctionalTest* Test) override;`
- L103 _public prototype_ `virtual void OnStart_Implementation(AFunctionalTest* Test) override;`
- L105 _public prototype_ `virtual void Tick_Implementation(AFunctionalTest* Test, float DeltaSeconds) override;`
- L107 _public prototype_ `virtual void OnFinished_Implementation() override;`
- L110 _public member_ `TArray<TObjectPtr<UHarmonixFunctionalTestAction>> ParallelActions;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Functional Testing")`
- L114 _private prototype_ `void FinishAllActions(bool bContinue);`
- L117 _private member_ `TArray<TObjectPtr<UHarmonixFunctionalTestAction>> ActionStack;` — `UPROPERTY(Transient)`

#### class `UHarmonixFunctionalTestActionDelay`  
`class UHarmonixFunctionalTestActionDelay final : public UHarmonixFunctionalTestAction`  
_L121-137_
- reflection: `UCLASS(NotBlueprintable, meta=(DisplayName="Delay"))`
- inherits: `UHarmonixFunctionalTestAction`
- L127 _public prototype_ `virtual void OnStart_Implementation(AFunctionalTest* Test) override;`
- L129 _public prototype_ `virtual void Tick_Implementation(AFunctionalTest* Test, float DeltaSeconds) override;`
- L132 _public member_ `float DelaySeconds = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")`
- L136 _private member_ `float TotalTime = 0.0f;`

#### class `UHarmonixFunctionalTestActionWaitForTimeout`  
`class UHarmonixFunctionalTestActionWaitForTimeout final : public UHarmonixFunctionalTestAction`  
_L140-143_
- reflection: `UCLASS(NotBlueprintable, meta=(DisplayName="Wait For Timeout"))`
- inherits: `UHarmonixFunctionalTestAction`

#### class `UHarmonixFunctionalTestActionFinishTest`  
`class UHarmonixFunctionalTestActionFinishTest : public UHarmonixFunctionalTestAction`  
_L146-160_
- reflection: `UCLASS(NotBlueprintable, meta=(DisplayName="Finish Test"))`
- inherits: `UHarmonixFunctionalTestAction`
- L152 _public prototype_ `virtual void OnStart_Implementation(AFunctionalTest* Test) override;`
- L155 _public member_ `EFunctionalTestResult Result = EFunctionalTestResult::Default;` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")`
- L158 _public member_ `FString Message = TEXT("Fin` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundTests/Private/HarmonixMetasoundFunctionalTest.h` (Private)


#### class `UHarmonixMetasoundFunctionalTestLibrary`  
`class UHarmonixMetasoundFunctionalTestLibrary final : public UBlueprintFunctionLibrary`  
_L23-42_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L29 _public prototype_ `static bool AddOutputLogger(UMetasoundGeneratorHandle* GeneratorHandle, FName OutputName, EAudioParameterType Type);` — `UFUNCTION(BlueprintCallable, Category="Harmonix Metasound", Meta=(ExpandBoolAsExecs="ReturnValue"))`
- L32 _public prototype_ `static bool AddMidiStreamLogger(UMetasoundGeneratorHandle* GeneratorHandle, FName OutputName);` — `UFUNCTION(BlueprintCallable, Category="Harmonix Metasound", Meta=(ExpandBoolAsExecs="ReturnValue"))`
- L34 _public prototype_ `static FString WriteAudioToFile(const FString& Filename, int32 SampleRate, int32 NumChannels, const Audio::FAlignedFloatBuffer& Audio);`
- L41 _public prototype_ `static bool ReadAudioFromFile(const FString& Filepath, Audio::FAlignedFloatBuffer& OutAudio, int32& OutSampleRate, int32& OutNumFrames, int32& OutNumChannels, uint16& OutFormatTag);` — absolute filepath reads audio data from audio file, converting audio to float audio is interleaved in the OutAudio buffer for multi-channel audio OutFormatTag is the format the audio file was saved in

#### class `AHarmonixMetasoundFunctionalTest`  
`class AHarmonixMetasoundFunctionalTest : public AFunctionalTest`  
_L45-106_
- reflection: `UCLASS(Blueprintable)`
- inherits: `AFunctionalTest`
- L50 _public prototype_ `AHarmonixMetasoundFunctionalTest(const FObjectInitializer& ObjectInitializer);`
- L53 _public member_ `TObjectPtr<USoundBase> TestSound;` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")`
- L56 _public member_ `FName AudioOutName = "Au` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")`
- L59 _public member_ `bool AudioAutoStart = true;` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")`
- L64 _public member_ `FString WavFilename_Expected;` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")` — name of wave file with the expected audio output. (searches the Content/Tests/AudioSource directory)
- L68 _public member_ `FString WavFilename_Output;` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")` — optionally write the output to a file
- L71 _public member_ `TArray<TObjectPtr<UHarmonixFunctionalTestAction>> FunctionalTestActions;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Functional Testing")`
- L73 _public prototype_ `virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message) override;`
- L75 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L79 _protected prototype_ `virtual void PrepareTest() override;`
- L81 _protected prototype_ `virtual void StartTest() override;`
- L83 _protected prototype_ `virtual bool IsReady_Implementation() override;`
- L85 _protected prototype_ `void CompareResults();`
- L88 _protected prototype_ `void OnTestFinishedEvent();` — `UFUNCTION()`
- L91 _protected member_ `TObjectPtr<UAudioComponent> AudioComponent;` — `UPROPERTY()`
- L94 _protected member_ `TObjectPtr<UMetasoundGeneratorHandle> GeneratorHandle;` — `UPROPERTY(Transient)`
- L97 _protected member_ `TObjectPtr<UHarmonixFunctionalTestActionSequence> ActionSequence;` — `UPROPERTY(Transient)`
- L100 _protected member_ `Audio::FAlignedFloatBuffer AudioCaptureOutput;` — the audio captured from the metasound
- L101 _protected member_ `float AudioCaptureSampleRate = 0.0f;`
- L103 _protected member_ `Metasound::Frontend::FAnalyzerAddress AudioOutAnalyzerAddress;`
- L105 _protected member_ `FTimerHandle TimerHandle;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixMetasoundTests, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixMetasoundTests, Log, All);`
- L14 _namespace_ `namespace Audio`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundTests/Private/HarmonixMetasoundFunctionalTestAction.h` (Private)


#### class `UHarmonixMetasoundFunctionalTestActionSetAudioParameter`  
`class UHarmonixMetasoundFunctionalTestActionSetAudioParameter : public UHarmonixFunctionalTestAction`  
_L13-21_
- reflection: `UCLASS(NotBlueprintable, Meta=(DisplayName="Set Audio Parameter"))`
- inherits: `UHarmonixFunctionalTestAction`
- L17 _public prototype_ `virtual void OnStart_Implementation(AFunctionalTest* Test) override;`
- L20 _public member_ `FAudioParameter AudioParameter;` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")`

#### class `UHarmonixMetasoundFunctionalTestActionSetWaitForAudioFinished`  
`class UHarmonixMetasoundFunctionalTestActionSetWaitForAudioFinished : public UHarmonixFunctionalTestAction`  
_L24-32_
- reflection: `UCLASS(NotBlueprintable, Meta=(DisplayName="Wait For Audio Finished"))`
- inherits: `UHarmonixFunctionalTestAction`
- L28 _public prototype_ `virtual void OnStart_Implementation(AFunctionalTest* Test) override;`
- L31 _protected prototype_ `void OnAudioFinished();` — `UFUNCTION()`

#### class `UHarmonixMetasoundFunctonalTestActionRecordClockOutput`  
`class UHarmonixMetasoundFunctonalTestActionRecordClockOutput : public UHarmonixFunctionalTestAction`  
_L35-67_
- reflection: `UCLASS(NotBlueprintable, meta=(DisplayName="Record Clock Output"))`
- inherits: `UHarmonixFunctionalTestAction`
- L40 _public prototype_ `virtual void Tick_Implementation(AFunctionalTest* Test, float DeltaSeconds) override;`
- L42 _public prototype_ `virtual void OnFinished_Implementation() override;`
- L45 _public member_ `float RecordTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Functional Testing", meta=(ClampMin="0.0", UIMin="0.0"))`
- L49 _public member_ `FString OutputFilename = FString("Clo` — `UPROPERTY(EditAnywhere, Category = "Functional Testing")` — optionally write the output to a file
- L53 _private member_ `float TotalTime = 0.0f;`
- L54 _private member_ `float StartTime = 0.0f;`
- L55 _private member_ `bool bClockStarted = false;`
- L66 _private member_ `TArray<FClockFrameData> ClockFrameData;`

#### struct `UHarmonixMetasoundFunctonalTestActionRecordClockOutput::FClockFrameData`  
`struct FClockFrameData`  
_L57-64_
- L59 _public member_ `float Time = 0.0f;`
- L60 _public member_ `FMidiSongPos SongPos;`
- L61 _public member_ `float BarDuration = 0.0f;`
- L62 _public member_ `float BeatDuration = 0.0f;`
- L63 _public member_ `EMusicClockState ClockState;`
