# Runtime / AudioAnalyzer

- module root: `Source/Runtime/AudioAnalyzer`
- headers: 9; symbols: 163
- symbol kinds: class=19, delegate=3, function=18, macro=1, member=38, namespace=4, prototype=73, struct=2, typedef=5
- PrivateDependencyModuleNames: AudioMixer, CoreUObject, Engine
- PublicDependencyModuleNames: Core, SignalProcessing

### `Source/Runtime/AudioAnalyzer/Classes/AudioAnalyzer.h` (Public)


#### class `UAudioAnalyzerSettings`  
`class UAudioAnalyzerSettings : public UAudioAnalyzerAssetBase`  
_L25-28_
- reflection: `UCLASS(Abstract, EditInlineNew, BlueprintType, MinimalAPI)`
- inherits: `UAudioAnalyzerAssetBase`
- desc: UAudioAnalyzerSettings UAudioAnalyzerSettings provides a way to store and reuse existing analyzer settings across multiple analyzers.

#### class `FAudioAnalyzeTask`  
`class FAudioAnalyzeTask : public FNonAbandonableTask`  
_L32-61_
- inherits: `FNonAbandonableTask`
- L35 _public prototype_ `FAudioAnalyzeTask(TUniquePtr<Audio::FAnalyzerFacade>& InAnalyzerFacade, int32 InSampleRate, int32 InNumChannels);`
- L38 _public prototype_ `void SetAnalyzerControls(TSharedPtr<Audio::IAnalyzerControls> InControls);` — Set in the task the current state of the analyzer controls
- L41 _public prototype_ `void SetAudioBuffer(TArray<float>&& InAudioData);` — Give the task the audio data to analyze
- L44 _public function_ `TArray<float>&& GetAudioBuffer()` — Move the audio buffer back out
- L47 _public prototype_ `void DoWork();` — Does the task work
- L49 _public function_ `inline TStatId GetStatId() const`
- L52 _public function_ `TUniquePtr<Audio::IAnalyzerResult> GetResults()` — Get the results from the task
- L55 _private member_ `TUniquePtr<Audio::FAnalyzerFacade> AnalyzerFacade;`
- L56 _private member_ `int32 SampleRate = 0;`
- L57 _private member_ `int32 NumChannels = 0;`
- L58 _private member_ `TArray<float> AudioData;`
- L59 _private member_ `TUniquePtr<Audio::IAnalyzerResult> Results;`
- L60 _private member_ `TSharedPtr<Audio::IAnalyzerControls> AnalyzerControls;`

#### class `UAudioAnalyzer`  
`class UAudioAnalyzer : public UObject`  
_L74-183_
- reflection: `UCLASS(Abstract, EditInlineNew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: UAudioAnalyzer UAudioAnalyzer performs analysis on an audio bus using specific settings and exposes the results via blueprints. Subclasses of UAudioAnalyzer must implement GetAnalyzerFactoryName() to associate the UAudioAnalyzer asset with an IAudioAnalyzerFactory implementation. To support blueprint access, subclasses can implement UFUNCTIONs to expose the data returned by GetResult().
- L85 _public typedef_ `typedef int32 FResultId;` — ID to keep track of results. Useful for tracking most recent result when performing asynchronous processing.
- L88 _public typedef_ `typedef TSharedPtr<Audio::IAnalyzerResult, ESPMode::ThreadSafe> FResultSharedPtr;` — Thread safe shared point to result object.
- L92 _public member_ `TObjectPtr<UAudioBus> AudioBus;` — `UPROPERTY(Transient)` — The UAudioBus which is analyzed in real-time.
- L96 _public prototype_ `void StartAnalyzing(const UObject* WorldContextObject, UAudioBus* AudioBusToAnalyze);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioAnalyzer, meta = (WorldContext = "WorldContextObject"))` — Starts analyzing audio from the given audio bus. Optionally override the audio bus desired to analyze.
- L100 _public prototype_ `void StartAnalyzing(UWorld* InWorld, UAudioBus* AudioBusToAnalyze);` — `UE_DEPRECATED(5.4, "Use the StartAnalyzing method that uses Audio::FDeviceId.")` — Starts analyzing using the given world.
- L102 _public prototype_ `void StartAnalyzing(const Audio::FDeviceId InAudioDeviceId, UAudioBus* AudioBusToAnalyze);`
- L106 _public prototype_ `void StopAnalyzing(const UObject* WorldContextObject = nullptr);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioAnalyzer, meta = (WorldContext = "WorldContextObject"))` — Stops analyzing audio.
- L112 _public prototype_ `virtual TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const;` — Implementations can override this method to create settings objects specific for their analyzer.
- L118 _public prototype_ `virtual TSharedPtr<Audio::IAnalyzerControls> GetAnalyzerControls() const;` — Implementations can override this method to create controls objects specific for their analyzer.
- L121 _public function_ `virtual void BroadcastResults()` — Function to broadcast results.
- L124 _public prototype_ `virtual void BeginDestroy() override;`
- L129 _private prototype_ `bool IsReadyForAnalysis() const;` — Returns if this audio analyzer has enough audio queued up and is ready for analysis.
- L132 _private prototype_ `bool DoAnalysis();` — Does the actual analysis and casts the results to the derived classes type. Returns true if there results to broadcast.
- L137 _protected function_ `template<class ResultType> TUniquePtr<ResultType> GetResults()`
- L143 _protected prototype_ `virtual FName GetAnalyzerFactoryName() const PURE_VIRTUAL(UAudioAnalyzer::GetAnalyzerFactoryName, return FName(););` — Subclasses must override this method in order to inform this object which AnalyzerFactory to use for analysis
- L146 _protected member_ `int32 NumFramesPerBufferToAnalyze = 1024;` — How many frames of audio to wait before analyzing the audio.
- L151 _private prototype_ `UAudioAnalyzerSettings* GetSettingsFromProperty(FProperty* Property);` — Returns UAudioAnalyzerSettings* if property points to a valid UAudioAnalyzerSettings, otherwise returns nullptr.
- L155 _private member_ `TObjectPtr<UAudioAnalyzerSubsystem> AudioAnalyzerSubsystem;` — `UPROPERTY(Transient)` — Audio analysis subsystem used with this audio analyzer
- L158 _private member_ `Audio::FPatchOutputStrongPtr PatchOutputStrongPtr;` — Output patch for retrieving audio from audio bus for analysis
- L161 _private member_ `TSharedPtr<FAsyncTask<FAudioAnalyzeTask>> AnalysisTask;` — Analysis task
- L164 _private member_ `TUniquePtr<Audio::FAnalyzerFacade> AnalyzerFacade;` — The analyzer facade used for async tasks
- L167 _private member_ `TUniquePtr<Audio::IAnalyzerResult> ResultsInternal;` — Cached results of previous analysis task. Can be invalid.
- L170 _private member_ `TSharedPtr<Audio::IAnalyzerControls> AnalyzerControls;` — The analyzer controls that can be modified real-time
- L173 _private member_ `TArray<float> AnalysisBuffer;` — Scratch buffer used for copying data from patch output and fed to analysis task
- L176 _private member_ `int32 AudioMixerSampleRate = 0;` — The sample of the audio renderer
- L179 _private member_ `int32 NumBusChannels = 0;` — The number of channels for the audio bus
- L182 _private member_ `Audio::IAnalyzerFactory* AnalyzerFactory = nullptr;` — The analyzer factory to use

#### Free symbols / members of external scopes

- L30 _typedef_ `typedef TSharedPtr<Audio::IAnalyzerResult, ESPMode::ThreadSafe> FAnalyzerResultSharedPtr;`

### `Source/Runtime/AudioAnalyzer/Classes/AudioAnalyzerAsset.h` (Public)


#### class `UAudioAnalyzerAssetBase`  
`class UAudioAnalyzerAssetBase : public UObject`  
_L17-42_
- reflection: `UCLASS(Abstract, EditInlineNew, MinimalAPI)`
- inherits: `UObject`
- desc: UAudioAnalyzerAssetBase UAudioAnalyzerAssetBase provides the base interface for controlling asset actions within the editor.
- L24 _public function_ `virtual bool HasAssetActions() const`
- L29 _public prototype_ `virtual FText GetAssetActionName() const PURE_VIRTUAL(UAudioAnalyzerAsset::GetAssetActionName, return FText(););` — GetAssetActionName() returns the FText displayed in the editor.
- L34 _public prototype_ `virtual UClass* GetSupportedClass() const PURE_VIRTUAL(UAudioAnalyzerAsset::GetSupportedClass, return nullptr;);` — GetSupportedClass() returns the class which should be associated with these asset actions.
- L39 _public function_ `virtual FColor GetTypeColor() const` — GetTypeColor() returns the color used to display asset icons within the editor.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE(FAnalyzeAudioDelegate);`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE(FAnalyzeAudioDelegate);`

### `Source/Runtime/AudioAnalyzer/Classes/AudioAnalyzerNRT.h` (Public)


#### class `UAudioAnalyzerNRTSettings`  
`class UAudioAnalyzerNRTSettings : public UAudioAnalyzerAssetBase`  
_L24-49_
- reflection: `UCLASS(Abstract, EditInlineNew, BlueprintType, MinimalAPI)`
- inherits: `UAudioAnalyzerAssetBase`
- desc: UAudioAnalyzerNRTSettings UAudioAnalyzerNRTSettings provides a way to store and reuse existing analyzer settings across multiple analyzers. This class provides the interface and functionality to automatically trigger reanalysis of audio across all analyzers associated with this setting when when a UPROPERTY in this setting object is edited.
- L32 _public member_ `FAnalyzeAudioDelegate AnalyzeAudioDelegate;`
- L40 _public prototype_ `void PostEditChangeProperty (struct FPropertyChangedEvent & PropertyChangedEvent) override;` — Called when a UPROPERTY of this class is edited. Triggers reanalysis of audio. This determines whether to trigger analysis by calling ShouldEventTriggerAnalysis(...)
- L46 _public prototype_ `virtual bool ShouldEventTriggerAnalysis(struct FPropertyChangedEvent & PropertyChangeEvent);` — This returns true when the PropertyChangeEvent is due to update a setting property. Override this method in order to customize this behavior.

#### class `UAudioAnalyzerNRT`  
`class UAudioAnalyzerNRT : public UAudioAnalyzerAssetBase`  
_L66-208_
- reflection: `UCLASS(Abstract, EditInlineNew, BlueprintType, MinimalAPI)`
- inherits: `UAudioAnalyzerAssetBase`
- desc: UAudioAnalyzerNRT UAudioAnalyzerNRT applies an analyzer to a sound using specific settings, stores the results and exposes them via blueprints. Subclasses of UAudioAnalyzerNRT must implement GetAnalyzerNRTFactoryName() to associate the UAudioAnalyzerNRT with an IAudioAnalyzerNRTFactory implementation. To support blueprint access, subclasses can implement UFUNCTIONs to expose the data returned by GetResult().
- L75 _public typedef_ `typedef int32 FResultId;` — ID to keep track of results. Useful for tracking most recent result when performing asynchronous processing.
- L78 _public typedef_ `typedef TSharedPtr<Audio::IAnalyzerNRTResult, ESPMode::ThreadSafe> FResultSharedPtr;` — Thread safe shared point to result object.
- L84 _public member_ `TObjectPtr<USoundWave> Sound;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta=(DisallowedClasses="/Script/MetasoundEngine.MetaSoundSource, /Script/Engine.SoundSourceBus"))` — The USoundWave which is analyzed.
- L88 _public member_ `float DurationInSeconds;` — `UPROPERTY(BlueprintReadOnly, Category=AudioAnalyzer)` — The duration of the analyzed audio in seconds.
- L92 _public prototype_ `void SetSound(USoundWave* InSound);` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")`
- L101 _public function_ `template<class ResultType> TSharedPtr<ResultType, ESPMode::ThreadSafe> GetResult()` — Returns the result object generated by the associated IAudioAnalyzerNRTFactory. The template argument must be the IAudioAnalyzerNRTResult subclass returned by the associated IAudioAnalyzerNRTFactory.
- L117 _public function_ `template<class ResultType> TSharedPtr<const ResultType, ESPMode::ThreadSafe> GetResult() const` — Returns the result object generated by the associated IAudioAnalyzerNRTFactory. The template argument must be the IAudioAnalyzerNRTResult subclass returned by the associated IAudioAnalyzerNRTFactory.
- L131 _public prototype_ `virtual TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const;` — Implementations can override this method to create settings objects specific for their analyzer.
- L136 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Performs serialization of results.
- L140 _public prototype_ `void SetResult(FResultSharedPtr NewResult);`
- L143 _public prototype_ `void SetResultIfLatest(FResultSharedPtr NewResult, FResultId InResultId);` — This will only store the result if the passed InResultId matches the CurrentResultId.
- L150 _public prototype_ `void PreEditChange(FProperty* PropertyAboutToChange) override;` — Called before a UPROPERTY of this class is edited. This checks to see if the UPROPERTY is a UAudioAnalyzerNRTSettings. If so, the previous settings' AnalyzeAudioDelegate will be unbound from this object's AnalyzeAudio()
- L159 _public prototype_ `void PostEditChangeProperty (struct FPropertyChangedEvent & PropertyChangedEvent) override;` — Called when a UPROPERTY of this class is edited. Triggering reanalysis of audio when appropriate and binds new settings if the UPROPERTY is a UAudioAnalyzerNRTSettings derived object. This determines whether to trigger analysis by calling ShouldEventTriggerAnalysis(...)
- L164 _public prototype_ `virtual bool ShouldEventTriggerAnalysis(struct FPropertyChangedEvent & PropertyChangeEvent);` — Returns true when the PropertyChangeEvent is due to update SoundWave or Settings.
- L168 _public prototype_ `void AnalyzeAudio();` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Performs the analaysis of the audio
- L174 _public member_ `FOnAudioAnalyzerNRTAnalysisComplete OnAnalysisComplete;` — `UPROPERTY(BlueprintAssignable, Category="Audio Analyzer")` — Delegate to receive all meter results, per-channel, since last delegate call.
- L183 _protected prototype_ `void SetSettingsDelegate(UAudioAnalyzerNRTSettings* InSettings);` — This sets the AnalyzeAudio callback to the delegate in settings.
- L186 _protected prototype_ `void RemoveSettingsDelegate(UAudioAnalyzerNRTSettings* InSettings);` — This removes the existing delegate handle from the current settings object
- L190 _protected prototype_ `virtual FName GetAnalyzerNRTFactoryName() const PURE_VIRTUAL(UAudioAnalyzerNRT::GetAnalyzerNRTFactoryName, return FName(););` — Subclasses must override this method in order to inform this object which AnalyzerNRTFactory to use for analysis
- L195 _private prototype_ `UAudioAnalyzerNRTSettings* GetSettingsFromProperty(FProperty* Property);` — Returns UAudioAnalyzerNRTSettings* if property points to a valid UAudioAnalyzerNRTSettings, otherwise returns nullptr.
- L197 _private member_ `TSharedPtr<Audio::IAnalyzerNRTResult, ESPMode::ThreadSafe> Result;`
- L200 _private member_ `mutable FCriticalSection ResultCriticalSection;` — Critical section is mutable so it can still be locked within const methods.
- L203 _private member_ `TAtomic<FResultId> CurrentResultId;` — Result id of the current result.
- L206 _private member_ `TMap<UAudioAnalyzerNRTSettings*, FDelegateHandle> AnalyzeAudioDelegateHandles;`

#### Free symbols / members of external scopes

- L52 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioAnalyzerNRTAnalysisComplete);` — Delegate to receive all meter results per channel (time-stamped in an array) since last delegate call.
- L52 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioAnalyzerNRTAnalysisComplete);` — Delegate to receive all meter results per channel (time-stamped in an array) since last delegate call.

### `Source/Runtime/AudioAnalyzer/Classes/AudioAnalyzerSubsystem.h` (Public)


#### class `UAudioAnalyzerSubsystem`  
`class UAudioAnalyzerSubsystem : public UEngineSubsystem`  
_L17-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- desc: Class manages querying analysis results from various audio analyzers.
- L22 _public prototype_ `UAudioAnalyzerSubsystem();`
- L23 _public prototype_ `~UAudioAnalyzerSubsystem();`
- L25 _public prototype_ `bool Tick(float DeltaTime);`
- L28 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L29 _public prototype_ `virtual void Deinitialize() override;`
- L32 _public prototype_ `void RegisterAudioAnalyzer(UAudioAnalyzer* InAnalyzer);`
- L33 _public prototype_ `void UnregisterAudioAnalyzer(UAudioAnalyzer* InAnalyzer);`
- L35 _public prototype_ `static UAudioAnalyzerSubsystem* Get();`
- L40 _private member_ `TArray<TObjectPtr<UAudioAnalyzer>> AudioAnalyzers;` — `UPROPERTY(Transient)`
- L42 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`

### `Source/Runtime/AudioAnalyzer/Public/AudioAnalyzerFacade.h` (Public)


#### class `Audio::FAnalyzerFacade`  
`class FAnalyzerFacade`  
_L21-41_
- desc: FAnalyzer FAnalyzer provides a simplified interface for performing analysis on audio buffers from the same AudioAnalyzer.
- L27 _public prototype_ `FAnalyzerFacade(TUniquePtr<IAnalyzerSettings> InSettings, IAnalyzerFactory* InFactory);` — Create an FAnalyzerBatch with the analyzer settings and factory name.
- L32 _public prototype_ `TUniquePtr<IAnalyzerResult> AnalyzeAudioBuffer(const TArray<float>& InAudioBuffer, int32 InNumChannels, float InSampleRate, TSharedPtr<IAnalyzerControls> InControls);` — Analyze the audio buffer.
- L36 _private member_ `TUniquePtr<IAnalyzerSettings> Settings;`
- L37 _private member_ `TUniquePtr<IAnalyzerWorker> Worker;`
- L39 _private member_ `IAnalyzerFactory* Factory;`
- L40 _private member_ `FName FactoryName;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`
- L15 _prototype_ `IAnalyzerFactory* GetAnalyzerFactory(FName InFactoryName);` (scope `Audio`)

### `Source/Runtime/AudioAnalyzer/Public/AudioAnalyzerModule.h` (Public)


#### class `FAudioAnalyzerModule`  
`class FAudioAnalyzerModule : public IModuleInterface`  
_L16-22_
- inherits: `IModuleInterface`
- L20 _public prototype_ `void StartupModule();` — IModuleInterface implementation
- L21 _public prototype_ `void ShutdownModule();`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioAnalyzer, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioAnalyzer, Log, All);`
- L14 _macro_ `#define AUDIO_ANALYSIS_LLM_SCOPE LLM_SCOPE_BYTAG(Audio_Analysis);` — Convenience macro for Audio_Analysis LLM scope to avoid misspells.

### `Source/Runtime/AudioAnalyzer/Public/AudioAnalyzerNRTFacade.h` (Public)


#### class `Audio::FAnalyzerNRTFacade`  
`class FAnalyzerNRTFacade`  
_L22-39_
- desc: FAnalyzerNRTFacade FAnalyzerNRTFacade provides a simplified interface for running analyzer factories over complete audio resources.
- L28 _public prototype_ `FAnalyzerNRTFacade(TUniquePtr<IAnalyzerNRTSettings> InSettings, const FName& InFactoryName);` — Create an FAnalyzerNRTFacade with the analyzer settings and factory name.
- L33 _public prototype_ `TUniquePtr<IAnalyzerNRTResult> AnalyzePCM16Audio(const TArray<uint8>& InRawWaveData, int32 InNumChannels, float InSampleRate);` — Analyze an entire PCM16 encoded audio object.  Audio for the entire sound should be contained within InRawWaveData.
- L37 _private member_ `TUniquePtr<IAnalyzerNRTSettings> Settings;`
- L38 _private member_ `FName FactoryName;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`
- L15 _prototype_ `IAnalyzerNRTFactory* GetAnalyzerNRTFactory(FName InFactoryName);` (scope `Audio`)

### `Source/Runtime/AudioAnalyzer/Public/IAudioAnalyzerInterface.h` (Public)


#### struct `Audio::FAnalyzerParameters`  
`struct FAnalyzerParameters`  
_L15-25_
- desc: FAnalyzerParameters These parameters are pass to an IAnalyzerFactory when creating a new IAnalyzerWorker or IAnalyzerResult
- L18 _public member_ `int32 SampleRate;`
- L19 _public member_ `int32 NumChannels;`
- L21 _public function_ `FAnalyzerParameters(int32 InSampleRate = 0, int32 InNumChannels = 0) : SampleRate(InSampleRate) , NumChannels(InNumChannels)`

#### class `Audio::IAnalyzerSettings`  
`class IAnalyzerSettings`  
_L32-36_
- desc: IAnalyzerSettings This interface defines the required methods for real-time analyzer settings.
- L35 _public prototype_ `virtual ~IAnalyzerSettings() = default;`

#### class `Audio::IAnalyzerResult`  
`class IAnalyzerResult`  
_L43-47_
- desc: IAnalyzerResult This interface defines the required methods for real-time analyzer results.
- L46 _public prototype_ `virtual ~IAnalyzerResult() = default;`

#### class `Audio::IAnalyzerControls`  
`class IAnalyzerControls`  
_L54-58_
- desc: IAnalyzerControls This interface defines the controls we want to link to the analyzer in order to do real-time parameter changes
- L57 _public prototype_ `virtual ~IAnalyzerControls() = default;`

#### class `Audio::IAnalyzerWorker`  
`class IAnalyzerWorker`  
_L61-70_
- desc: An audio analyzer worker
- L64 _public prototype_ `virtual ~IAnalyzerWorker() = default;`
- L66 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerResult* OutResult) = 0;`
- L68 _public function_ `virtual void SetControls(TSharedPtr<IAnalyzerControls> InAnalyzerControls)`
- L69 _public function_ `virtual void ClearControls()`

#### class `Audio::IAnalyzerFactory`  
`class IAnalyzerFactory : public IModularFeature`  
_L73-106_
- inherits: `IModularFeature`
- desc: Audio analyzer factory. Primarily used for creating a worker.
- L76 _public prototype_ `virtual ~IAnalyzerFactory() = default;`
- L80 _public function_ `static FName GetModularFeatureName()` — Supplied unique name of IAnalyzerFactory to enable querying of added analyzer factories
- L87 _public prototype_ `virtual FName GetName() const = 0;` — Name of specific analyzer type.
- L90 _public prototype_ `virtual FString GetTitle() const = 0;` — Human readable name of analyzer.
- L93 _public prototype_ `virtual TUniquePtr<IAnalyzerResult> NewResult() const = 0;` — Create a new result.
- L97 _public function_ `template<ESPMode Mode = ESPMode::ThreadSafe> TSharedPtr<IAnalyzerResult, Mode> NewResultShared() const` — Convenience function to create a new shared result by calling NewResult.
- L105 _public prototype_ `virtual TUniquePtr<IAnalyzerWorker> NewWorker(const FAnalyzerParameters& InParams, const IAnalyzerSettings* InSettings) const = 0;` — Create a new worker.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/AudioAnalyzer/Public/IAudioAnalyzerNRTInterface.h` (Public)


#### struct `Audio::FAnalyzerNRTParameters`  
`struct FAnalyzerNRTParameters`  
_L20-30_
- desc: FAnalyzerNRTParameters These parameters are pass to an IAnalyzerNRTFactory when creating a new IAnalyzerNRTWorker or IAnalyzerNRTResult
- L23 _public member_ `float SampleRate;`
- L24 _public member_ `int32 NumChannels;`
- L26 _public function_ `FAnalyzerNRTParameters(float InSampleRate=0.0f, int32 InNumChannels=0) : SampleRate(InSampleRate) , NumChannels(InNumChannels)`

#### class `Audio::IAnalyzerNRTSettings`  
`class IAnalyzerNRTSettings`  
_L37-41_
- desc: IAnalyzerNRTSettings This interface defines the required methods for non-real-time analyzer settings.
- L40 _public prototype_ `virtual ~IAnalyzerNRTSettings() = default;`

#### class `Audio::IAnalyzerNRTResult`  
`class IAnalyzerNRTResult`  
_L48-68_
- desc: IAnalyzerNRTResult This interface defines the required methods for non-real-time analyzer results.
- L51 _public prototype_ `virtual ~IAnalyzerNRTResult() = default;`
- L54 _public prototype_ `virtual void Serialize(FArchive& Archive) = 0;` — This is used to define how to serialize this instance of results for remote profiling.
- L58 _public function_ `virtual void CopyFrom(IAnalyzerNRTResult* SourceResult)` — This virtual can be overridden to provide a faster copying scheme than full serialization when analyzing non-remote targets. If not overridden, this function will use the Serialize call.
- L67 _public prototype_ `virtual float GetDurationInSeconds() const = 0;` — This must be overridden to return the duration of the original audio analyzed.

#### class `Audio::IAnalyzerNRTWorker`  
`class IAnalyzerNRTWorker`  
_L75-90_
- desc: IAnalyzerNRTWorker This interface is used to define a class that will handle actual analysis of a singular audio asset.
- L78 _public prototype_ `virtual ~IAnalyzerNRTWorker() = default;`
- L84 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerNRTResult* OutResult) = 0;` — Perform analysis of an audio stream. This method may be called multiple times with audio from the same source.
- L89 _public prototype_ `virtual void Finalize(IAnalyzerNRTResult* OutResult) = 0;` — Called when analysis of audio asset is complete.

#### class `Audio::IAnalyzerNRTFactory`  
`class IAnalyzerNRTFactory : public IModularFeature`  
_L96-129_
- inherits: `IModularFeature`
- desc: IAnalyzerNRTFactory This is used to define a non real-time analyzer.
- L99 _public prototype_ `virtual ~IAnalyzerNRTFactory() = default;`
- L103 _public function_ `static FName GetModularFeatureName()` — Supplied unique name of IAnalyzerNRTFactory to enable querying of added analyzer factories
- L110 _public prototype_ `virtual FName GetName() const = 0;` — Name of specific analyzer type.
- L113 _public prototype_ `virtual FString GetTitle() const = 0;` — Human readable name of analyzer.
- L116 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTResult> NewResult() const = 0;` — Create a new result.
- L120 _public function_ `template<ESPMode Mode = ESPMode::ThreadSafe> TSharedPtr<IAnalyzerNRTResult, Mode> NewResultShared() const` — Convenience function to create a new shared result by calling NewResult.
- L128 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTWorker> NewWorker(const FAnalyzerNRTParameters& InParams, const IAnalyzerNRTSettings* InSettings) const = 0;` — Create a new worker.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`
