# Plugins / TimedDataMonitor

- module root: `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitor`
- headers: 4; symbols: 217
- symbol kinds: class=2, delegate=3, enum=4, enumerator=25, function=14, macro=2, member=63, prototype=91, struct=13
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject, StageDataCore, TimeManagement

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitor/Private/TimedDataMonitorPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTimedDataMonitor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTimedDataMonitor, Log, All);`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitor/Public/TimedDataMonitorCalibration.h` (Public)


#### enum `ETimedDataMonitorCalibrationReturnCode`  
`enum class ETimedDataMonitorCalibrationReturnCode : uint8`  
_L18-40_
- reflection: `UENUM()`
- L21 _public enumerator_ `Succeeded` — Success. The values were synchronized.
- L23 _public enumerator_ `Failed_NoTimecode` — Failed. The timecode provider doesn't have a proper timecode value.
- L25 _public enumerator_ `Failed_UnresponsiveInput` — Failed. At least one input is unresponsive.
- L27 _public enumerator_ `Failed_InvalidEvaluationType` — Failed. At least one input has an evaluation type that is not timecode.
- L29 _public enumerator_ `Failed_InvalidFrameRate` — Failed. At least one input doesn't have a defined frame rate.
- L31 _public enumerator_ `Failed_NoDataBuffered` — Failed. At least one input doesn't have data buffered.
- L33 _public enumerator_ `Failed_BufferCouldNotBeResize` — Failed. A resize was requested but it was not able to do so.
- L35 _public enumerator_ `Failed_Reset` — Failed. The calibration was manually reset.
- L37 _public enumerator_ `Retry_NotEnoughData` — Retry. The buffer size is correct but they do not contain enough data to calibrate.
- L39 _public enumerator_ `Retry_IncreaseBufferSize` — Retry. No interval could be found. Increase the buffer size.

#### struct `FTimedDataMonitorCalibrationResult`  
`struct FTimedDataMonitorCalibrationResult`  
_L44-53_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `ETimedDataMonitorCalibrationReturnCode ReturnCode = ETimedDataMonitorCalibrationReturnCode::Succeeded;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Result")`
- L52 _public member_ `TArray<FTimedDataMonitorInputIdentifier> FailureInputIdentifiers;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Result")`

#### struct `FTimedDataMonitorCalibrationParameters`  
`struct FTimedDataMonitorCalibrationParameters`  
_L57-92_
- reflection: `USTRUCT(BlueprintType)`
- L63 _public member_ `int32 NumberOfRetries = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters", meta = (ClampMin = 0, ClampMax = 100))` — When needed, how many retry is allowed.
- L67 _public member_ `bool bBufferResizeAllowed = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters")` — If no calibration is possible, are we allowed to increase the size of the buffer.
- L71 _public member_ `bool bBufferShrinkAllowed = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters")` — When resizing buffer, do we allow shrinking them.
- L75 _public member_ `bool bFailedIfBufferCantBeResize = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters")` — When resizing buffer, failed the calibration if a buffer couldn't be resize.
- L79 _public member_ `bool bUseStandardDeviation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters")` — When calibrating, ensure that the evaluation is included inside the STD.
- L83 _public member_ `int32 NumberOfStandardDeviation = 3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters", meta = (EditCondition = "bUseStandardDeviation", ClampMin = 0, ClampMax = 5))` — When using STD, how many should we use.
- L87 _public member_ `bool bResetStatisticsBeforeUsingStandardDeviation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters", meta = (EditCondition = "bUseStandardDeviation"))` — Before calibration, allow to reset the statistics.
- L91 _public member_ `float AmountOfSecondsToWaitAfterStatisticReset = 2.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters", meta = (EditCondition = "bUseStandardDeviation"))` — Before calibration, allow to reset the statistics.

#### enum `ETimedDataMonitorTimeCorrectionReturnCode`  
`enum class ETimedDataMonitorTimeCorrectionReturnCode : uint8`  
_L96-114_
- reflection: `UENUM()`
- L99 _public enumerator_ `Succeeded` — Success. The values were synchronized.
- L101 _public enumerator_ `Failed_InvalidInput` — Failed. The provided input doesn't exist.
- L103 _public enumerator_ `Failed_NoTimecode` — Failed. The timecode provider was not existing or not synchronized.
- L105 _public enumerator_ `Failed_UnresponsiveInput` — Failed. At least one channel is unresponsive.
- L107 _public enumerator_ `Failed_NoDataBuffered` — Failed. The channel doesn't have any data in it's buffer to synchronized with.
- L109 _public enumerator_ `Failed_BufferCouldNotBeResize` — Failed. A resize was requested but it was not able to do so.
- L111 _public enumerator_ `Retry_NotEnoughData` — Retry. The buffer size is correct but they do not contain enough data to to the time correction.
- L113 _public enumerator_ `Retry_IncreaseBufferSize` — Retry. No interval could be found. Increase the buffer size.

#### struct `FTimedDataMonitorTimeCorrectionResult`  
`struct FTimedDataMonitorTimeCorrectionResult`  
_L117-126_
- reflection: `USTRUCT(BlueprintType)`
- L122 _public member_ `ETimedDataMonitorTimeCorrectionReturnCode ReturnCode = ETimedDataMonitorTimeCorrectionReturnCode::Succeeded;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Result")`
- L125 _public member_ `TArray<FTimedDataMonitorChannelIdentifier> FailureChannelIdentifiers;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Result")`

#### struct `FTimedDataMonitorTimeCorrectionParameters`  
`struct FTimedDataMonitorTimeCorrectionParameters`  
_L130-153_
- reflection: `USTRUCT(BlueprintType)`
- L136 _public member_ `bool bBufferResizeAllowed = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters")` — If no calibration is possible, are we allowed to increase the size of the buffer.
- L140 _public member_ `bool bBufferShrinkAllowed = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters")` — When resizing buffer, do we allow shrinking them.
- L144 _public member_ `bool bFailedIfBufferCantBeResize = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters")` — When resizing buffer, failed the calibration if a buffer couldn't be resize.
- L148 _public member_ `bool bUseStandardDeviation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters", meta = (InlineEditConditionToggle = true))` — When calibrating, ensure that the evaluation is included inside the STD.
- L152 _public member_ `int32 NumberOfStandardDeviation = 3;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration Parameters", meta = (EditCondition = "bUseStandardDeviation", ClampMin = 0, ClampMax = 5))` — When using STD, how many should we use.

#### class `FTimedDataMonitorCalibration`  
`class FTimedDataMonitorCalibration`  
_L158-181_
- L161 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCalibrationCompletedSignature, FTimedDataMonitorCalibrationResult);`
- L164 _public prototype_ `~FTimedDataMonitorCalibration();`
- L166 _public prototype_ `void Reset();`
- L167 _public prototype_ `bool IsRunning() const;`
- L168 _public prototype_ `void CalibrateWithTimecode(const FTimedDataMonitorCalibrationParameters& Parameters, FOnCalibrationCompletedSignature OnCompleted);`
- L170 _public prototype_ `static FTimedDataMonitorCalibrationResult CalibrateWithTimecode(const FTimedDataMonitorCalibrationParameters& CalibrationParameters);`
- L171 _public prototype_ `static FTimedDataMonitorTimeCorrectionResult ApplyTimeCorrection(const FTimedDataMonitorInputIdentifier& Identifier, const FTimedDataMonitorTimeCorrectionParameters& TimeCorrectionParameters);`
- L174 _private prototype_ `bool RunCalibrateWithTimecode(float);`
- L175 _private prototype_ `bool RunCalibrateWithTimecode_CheckForReset(float);`
- L177 _private member_ `int32 NumberOfRetry = 0;`
- L178 _private member_ `FTimedDataMonitorCalibrationParameters CalibrationParameters;`
- L179 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L180 _private member_ `FOnCalibrationCompletedSignature OnCalibrationCompleted;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TIMEDDATAMONITOR_API`
- L161 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCalibrationCompletedSignature, FTimedDataMonitorCalibrationResult);`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitor/Public/TimedDataMonitorSubsystem.h` (Public)


#### enum `ETimedDataMonitorInputEnabled`  
`enum class ETimedDataMonitorInputEnabled : uint8`  
_L19-24_
- reflection: `UENUM()`
- L21 _public enumerator_ `Disabled`
- L22 _public enumerator_ `Enabled`
- L23 _public enumerator_ `MultipleValues`

#### enum `ETimedDataMonitorEvaluationState`  
`enum class ETimedDataMonitorEvaluationState : uint8`  
_L28-34_
- reflection: `UENUM()`
- L30 _public enumerator_ `NoSample = 0`
- L31 _public enumerator_ `OutsideRange = 1`
- L32 _public enumerator_ `InsideRange = 2`
- L33 _public enumerator_ `Disabled = 3`

#### struct `FTimedDataMonitorChannelConnectionStateEvent`  
`struct FTimedDataMonitorChannelConnectionStateEvent : public FStageProviderEventMessage`  
_L37-62_
- reflection: `USTRUCT(meta = (DisplayName = "TimedSourcesConnectionEvent"))`
- inherits: `FStageProviderEventMessage`
- L42 _public prototype_ `FTimedDataMonitorChannelConnectionStateEvent() = default;`
- L43 _public function_ `FTimedDataMonitorChannelConnectionStateEvent(ETimedDataInputState InNewState, const FString& InInputName, const FString& InChannelName) : NewState(InNewState) , InputName(InInputName) , ChannelName(InChannelName)`
- L49 _public prototype_ `virtual FString ToString() const;`
- L53 _public member_ `ETimedDataInputState NewState = ETimedDataInputState::Connected;` — `UPROPERTY(VisibleAnywhere, Category = "Timed Data State")` — New state of the channel
- L57 _public member_ `FString InputName;` — `UPROPERTY(VisibleAnywhere, Category = "Timed Data State")` — Input owning that channel
- L61 _public member_ `FString ChannelName;` — `UPROPERTY(VisibleAnywhere, Category = "Timed Data State")` — Channel which had a state change

#### struct `FTimedDataMonitorChannelEvaluationStateEvent`  
`struct FTimedDataMonitorChannelEvaluationStateEvent : public FStageProviderEventMessage`  
_L65-90_
- reflection: `USTRUCT(meta = (DisplayName = "TimedSourcesEvaluationEvent"))`
- inherits: `FStageProviderEventMessage`
- L70 _public prototype_ `FTimedDataMonitorChannelEvaluationStateEvent() = default;`
- L71 _public function_ `FTimedDataMonitorChannelEvaluationStateEvent(ETimedDataMonitorEvaluationState InNewState, const FString& InInputName, const FString& InChannelName) : NewState(InNewState) , InputName(InInputName) , ChannelName(InChannelName)`
- L77 _public prototype_ `virtual FString ToString() const;`
- L81 _public member_ `ETimedDataMonitorEvaluationState NewState = ETimedDataMonitorEvaluationState::NoSample;` — `UPROPERTY(VisibleAnywhere, Category = "Timed Data State")` — New state of the channel
- L85 _public member_ `FString InputName;` — `UPROPERTY(VisibleAnywhere, Category = "Timed Data State")` — Input owning that channel
- L89 _public member_ `FString ChannelName;` — `UPROPERTY(VisibleAnywhere, Category = "Timed Data State")` — Channel which had a state change

#### struct `FExponentialMeanVarianceTracker`  
`struct FExponentialMeanVarianceTracker`  
_L95-122_
- desc: Exponential running mean calculator. Gives better result than incremental running mean when parameters change
- L97 _public function_ `FExponentialMeanVarianceTracker()`
- L102 _public prototype_ `void Reset();`
- L103 _public prototype_ `void Update(float NewValue, float MeanOffset);`
- L106 _public member_ `int32 SampleCount = 0;` — Current number of samples used for the running average and variance
- L109 _public member_ `float LastValue = 0.0f;` — Last sample value used for statistics
- L112 _public member_ `float CurrentMean = 0.0f;` — Current running mean
- L115 _public member_ `float CurrentVariance = 0.0f;` — Current running variance
- L118 _public member_ `float CurrentSTD = 0.0f;` — Current standard deviation
- L121 _public member_ `float Alpha = 0.0f;` — Weight given to new samples. A bigger value means new data will weight more in the calculation. Won't filter if data oscillates a lot.

#### struct `FTimedDataChannelEvaluationStatistics`  
`struct FTimedDataChannelEvaluationStatistics`  
_L127-147_
- desc: Structure to facilitate calculating running mean and variance of evaluation distance to buffered samples for a channel
- L129 _public prototype_ `void CacheSettings(ETimedDataInputEvaluationType EvaluationType, float TimeOffset, int32 BufferSize);`
- L130 _public prototype_ `void Update(float DistanceToOldest, float DistanceToNewest);`
- L131 _public prototype_ `void Reset();`
- L133 _public member_ `FExponentialMeanVarianceTracker NewestSampleDistanceTracker;`
- L134 _public member_ `FExponentialMeanVarianceTracker OldestSampleDistanceTracker;`
- L137 _public member_ `ETimedDataInputEvaluationType CachedEvaluationType;` — Last evaluation type of our input
- L140 _public member_ `float CachedOffset = 0.0f;` — Last Offset associated with this channel
- L143 _public member_ `int32 CachedBufferSize = 0;` — Last buffer size associated with this channel
- L146 _public member_ `float NextTickOffset = 0.0f;` — Offset to be applied for the next tick. Used to feedforward mean tracker

#### class `UTimedDataMonitorSubsystem`  
`class UTimedDataMonitorSubsystem : public UEngineSubsystem`  
_L158-477_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- L190 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L191 _public prototype_ `virtual void Deinitialize() override;`
- L195 _public prototype_ `void BeginFrameCallback();` — Used to cache global (Engine TimecodeProvider) frame delay for the current frame.
- L198 _public prototype_ `void EndFrameCallback();` — Used to update statistics once all TimedData are processed. i.e. MediaIO is processed after tickables.
- L203 _public member_ `FTimedDataIdentifierListChangedSignature OnIdentifierListChanged_Dynamic;` — `UPROPERTY(BlueprintAssignable, Category = "Timed Data Monitor", meta=(DisplayName="OnSourceIdentifierListChanged"))` — Delegate of when an element is added or removed.
- L207 _public function_ `FSimpleMulticastDelegate& OnIdentifierListChanged()` — Delegate of when an element is added or removed.
- L210 _public prototype_ `ITimedDataInput* GetTimedDataInput(const FTimedDataMonitorInputIdentifier& Identifier);` — Get the interface for a specific input identifier.
- L213 _public prototype_ `ITimedDataInputChannel* GetTimedDataChannel(const FTimedDataMonitorChannelIdentifier& Identifier);` — Get the interface for a specific channel identifier.
- L216 _public prototype_ `float GetEvaluationTimeOffsetInSeconds(ETimedDataInputEvaluationType EvaluationType);` — Get offset applied to global evaluation time. Only works when a Timecode Provider is used
- L219 _public prototype_ `static double GetEvaluationTime(ETimedDataInputEvaluationType EvaluationType);` — Get the current evaluation time.
- L224 _public prototype_ `TArray<FTimedDataMonitorInputIdentifier> GetAllInputs();` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor")` — Get the list of all the inputs.
- L228 _public prototype_ `TArray<FTimedDataMonitorChannelIdentifier> GetAllChannels();` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor")` — Get the list of all the channels.
- L232 _public prototype_ `TArray<FTimedDataMonitorChannelIdentifier> GetAllEnabledChannels();` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor")` — Get the list of all the channels that are enabled.
- L236 _public prototype_ `void CalibrateLatent(UObject* WorldContextObject, FLatentActionInfo LatentInfo, const FTimedDataMonitorCalibrationParameters& CalibrationParameters, FTimedDataMonitorCalibrationResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor", meta = (DisplayName = "Calibrate", Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject"))` — Change the Timecode Provider offset to align all inputs and channels.
- L240 _public prototype_ `FTimedDataMonitorTimeCorrectionResult ApplyTimeCorrection(const FTimedDataMonitorInputIdentifier& Identifier, const FTimedDataMonitorTimeCorrectionParameters& TimeCorrectionParameters);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor")` — Assume all data samples were produce at the same time and align them with the current platform's time
- L244 _public prototype_ `void ResetAllBufferStats();` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor")` — Reset the stat of all the inputs.
- L248 _public prototype_ `ETimedDataMonitorEvaluationState GetEvaluationState();` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor")` — Get the worst evaluation state of all the inputs.
- L252 _public prototype_ `bool DoesInputExist(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Return true if the identifier is a valid input.
- L256 _public prototype_ `ETimedDataMonitorInputEnabled GetInputEnabled(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Is the input enabled in the monitor.
- L260 _public prototype_ `void SetInputEnabled(const FTimedDataMonitorInputIdentifier& Identifier, bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Set all channels for the input enabled in the monitor.
- L264 _public prototype_ `FText GetInputDisplayName(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Return the display name of an input.
- L268 _public prototype_ `TArray<FTimedDataMonitorChannelIdentifier> GetInputChannels(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Return the list of all channels that are part of the input.
- L272 _public prototype_ `ETimedDataInputEvaluationType GetInputEvaluationType(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get how the input is evaluated type.
- L276 _public prototype_ `void SetInputEvaluationType(const FTimedDataMonitorInputIdentifier& Identifier, ETimedDataInputEvaluationType Evaluation);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Set how the input is evaluated type.
- L280 _public prototype_ `float GetInputEvaluationOffsetInSeconds(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get the offset in seconds or frames (see GetEvaluationType) used at evaluation.
- L284 _public prototype_ `void SetInputEvaluationOffsetInSeconds(const FTimedDataMonitorInputIdentifier& Identifier, float Seconds);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Set the offset in seconds or frames (see GetEvaluationType) used at evaluation.
- L288 _public prototype_ `float GetInputEvaluationOffsetInFrames(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get the offset in frames (see GetEvaluationType) used at evaluation.
- L292 _public prototype_ `void SetInputEvaluationOffsetInFrames(const FTimedDataMonitorInputIdentifier& Identifier, float Frames);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Set the offset in frames (see GetEvaluationType) used at evaluation.
- L296 _public prototype_ `FFrameRate GetInputFrameRate(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get the frame rate at which the samples is produce.
- L300 _public prototype_ `FTimedDataChannelSampleTime GetInputOldestDataTime(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get the oldest sample time of all the channel in this input.
- L304 _public prototype_ `FTimedDataChannelSampleTime GetInputNewestDataTime(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get the latest sample time of all the channel in this input.
- L308 _public prototype_ `bool IsDataBufferSizeControlledByInput(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Does the channel support a different buffer size than it's input.
- L312 _public prototype_ `int32 GetInputDataBufferSize(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get the size of the buffer used by the input.
- L316 _public prototype_ `void SetInputDataBufferSize(const FTimedDataMonitorInputIdentifier& Identifier, int32 BufferSize);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Set the size of the buffer used by the input.
- L320 _public prototype_ `ETimedDataInputState GetInputConnectionState(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get the worst state of all the channels of that input.
- L324 _public prototype_ `ETimedDataMonitorEvaluationState GetInputEvaluationState(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Get the worst evaluation state of all the channels of that input.
- L328 _public prototype_ `float GetInputEvaluationDistanceToNewestSampleMean(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Returns the max average distance, in seconds, between evaluation time and newest sample
- L332 _public prototype_ `float GetInputEvaluationDistanceToOldestSampleMean(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Returns the min average distance, in seconds, between evaluation time and oldest sample
- L336 _public prototype_ `float GetInputEvaluationDistanceToNewestSampleStandardDeviation(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Returns the standard deviation of the distance, in seconds, between evaluation time and newest sample
- L340 _public prototype_ `float GetInputEvaluationDistanceToOldestSampleStandardDeviation(const FTimedDataMonitorInputIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Input")` — Returns the standard deviation of the distance, in seconds, between evaluation time and oldest sample
- L344 _public prototype_ `bool DoesChannelExist(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Return true if the identifier is a valid channel.
- L348 _public prototype_ `bool IsChannelEnabled(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Is the channel enabled in the monitor.
- L355 _public prototype_ `void SetChannelEnabled(const FTimedDataMonitorChannelIdentifier& Identifier, bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Enable or disable an input from the monitor. The input will still be evaluated but stats will not be tracked and the will not be used for calibration.
- L359 _public prototype_ `FTimedDataMonitorInputIdentifier GetChannelInput(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Return the input of this channel.
- L363 _public prototype_ `FText GetChannelDisplayName(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Return the display name of an input.
- L367 _public prototype_ `ETimedDataInputState GetChannelConnectionState (const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Get the state the channel.
- L371 _public prototype_ `ETimedDataMonitorEvaluationState GetChannelEvaluationState(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Get the evaluation state of the channel.
- L375 _public prototype_ `FTimedDataChannelSampleTime GetChannelOldestDataTime(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Get the channel oldest sample time.
- L379 _public prototype_ `FTimedDataChannelSampleTime GetChannelNewestDataTime(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Get the channel latest sample time.
- L383 _public prototype_ `TArray<FTimedDataChannelSampleTime> GetChannelFrameDataTimes(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Get the sample times for every frame in the channel
- L387 _public prototype_ `int32 GetChannelNumberOfSamples(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Get the number of data samples available.
- L391 _public prototype_ `int32 GetChannelDataBufferSize(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — If the channel does support it, get the current maximum sample count of channel.
- L395 _public prototype_ `void SetChannelDataBufferSize(const FTimedDataMonitorChannelIdentifier& Identifier, int32 BufferSize);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — If the channel does support it, set the maximum sample count of the channel.
- L399 _public prototype_ `int32 GetChannelBufferUnderflowStat(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Returns the number of buffer underflows detected by that input since the last reset.
- L403 _public prototype_ `int32 GetChannelBufferOverflowStat(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Returns the number of buffer overflows detected by that input since the last reset.
- L407 _public prototype_ `int32 GetChannelFrameDroppedStat(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Returns the number of frames dropped by that input since the last reset.
- L414 _public prototype_ `void GetChannelLastEvaluationDataStat(const FTimedDataMonitorChannelIdentifier& Identifier, FTimedDataInputEvaluationData& Result);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Retrieves information about last evaluation Returns true if identifier was found
- L418 _public prototype_ `float GetChannelEvaluationDistanceToNewestSampleMean(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Returns the average distance, in seconds, between evaluation time and newest sample
- L422 _public prototype_ `float GetChannelEvaluationDistanceToOldestSampleMean(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Returns the average distance, in seconds, between evaluation time and oldest sample
- L426 _public prototype_ `float GetChannelEvaluationDistanceToNewestSampleStandardDeviation(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Returns the standard deviation of the distance, in seconds, between evaluation time and newest sample
- L430 _public prototype_ `float GetChannelEvaluationDistanceToOldestSampleStandardDeviation(const FTimedDataMonitorChannelIdentifier& Identifier);` — `UFUNCTION(BlueprintCallable, Category = "Timed Data Monitor|Channel")` — Returns the standard deviation of the distance, in seconds, between evaluation time and oldest sample
- L433 _private prototype_ `void BuildSourcesListIfNeeded();`
- L435 _private prototype_ `void OnTimedDataSourceCollectionChanged();`
- L438 _private prototype_ `void CacheEvaluationState();` — Caches state with regards to evaluation of registered inputs
- L441 _private prototype_ `void CacheConnectionState();` — Caches connection state of each inputs
- L444 _private prototype_ `void CacheChannelEvaluationState(FTimeDataChannelItem& Identifier);` — Caches the current evaluation state for a channel
- L447 _private prototype_ `void UpdateEvaluationStatistics();` — Update internal statistics for each enabled channel
- L450 _private prototype_ `void UpdateStatFileLoggingState();` — Starts logging stats for each channel to be dumped in a file
- L453 _private prototype_ `void AddStatisticLogEntry(const TPair<FTimedDataMonitorChannelIdentifier, FTimeDataChannelItem>& ChannelEntry);` — Adds a log entry for a given channel
- L456 _private member_ `bool bRequestSourceListRebuilt = false;`
- L457 _private member_ `TMap<FTimedDataMonitorInputIdentifier, FTimeDataInputItem> InputMap;`
- L458 _private member_ `TMap<FTimedDataMonitorChannelIdentifier, FTimeDataChannelItem> ChannelMap;`
- L459 _private member_ `FSimpleMulticastDelegate OnIdentifierListChanged_Delegate;`
- L460 _private member_ `float CachedTimecodeProviderFrameDelayInSeconds = 0.0f;`
- L463 _private member_ `ETimedDataMonitorEvaluationState CachedEvaluationState = ETimedDataMonitorEvaluationState::Disabled;` — Cached system state for evaluation and connection based on each input / channel and source that caused last change
- L464 _private member_ `ETimedDataInputState CachedConnectionState = ETimedDataInputState::Disconnected;`
- L474 _private member_ `bool bHasStatFileLoggingStarted = false;`
- L475 _private member_ `TMap<FTimedDataMonitorChannelIdentifier, FChannelStatisticLogging> StatLoggingMap;`

#### struct `UTimedDataMonitorSubsystem::FTimeDataInputItem`  
`struct FTimeDataInputItem`  
_L164-173_
- L166 _public member_ `ITimedDataInput* Input = nullptr;`
- L167 _public member_ `TArray<FTimedDataMonitorChannelIdentifier> ChannelIdentifiers;`
- L168 _public member_ `ETimedDataInputState CachedConnectionState;`
- L169 _public member_ `ETimedDataMonitorEvaluationState CachedEvaluationState;`
- L172 _public prototype_ `void ResetValue();`

#### struct `UTimedDataMonitorSubsystem::FTimeDataChannelItem`  
`struct FTimeDataChannelItem`  
_L175-186_
- L177 _public member_ `ITimedDataInputChannel* Channel = nullptr;`
- L178 _public member_ `bool bEnabled = true;`
- L179 _public member_ `FTimedDataMonitorInputIdentifier InputIdentifier;`
- L180 _public member_ `FTimedDataChannelEvaluationStatistics Statistics;`
- L181 _public member_ `ETimedDataInputState CachedConnectionState;`
- L182 _public member_ `ETimedDataMonitorEvaluationState CachedEvaluationState;`
- L185 _public prototype_ `void ResetValue();`

#### struct `UTimedDataMonitorSubsystem::FChannelStatisticLogging`  
`struct FChannelStatisticLogging`  
_L468-472_
- L470 _public member_ `FString ChannelName;`
- L471 _public member_ `TArray<FString> Entries;`

#### Free symbols / members of external scopes

- L150 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimedDataIdentifierListChangedSignature);`
- L150 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimedDataIdentifierListChangedSignature);`

### `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitor/Public/TimedDataMonitorTypes.h` (Public)


#### struct `FTimedDataMonitorInputIdentifier`  
`struct FTimedDataMonitorInputIdentifier`  
_L14-32_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- L20 _private member_ `FGuid Identifier;` — `UPROPERTY()`
- L23 _public prototype_ `static FTimedDataMonitorInputIdentifier NewIdentifier();`
- L25 _public function_ `bool IsValid() const`
- L27 _public function_ `bool operator== (const FTimedDataMonitorInputIdentifier& Other) const`
- L28 _public function_ `bool operator!= (const FTimedDataMonitorInputIdentifier& Other) const`
- L29 _public function_ `bool operator< (const FTimedDataMonitorInputIdentifier& Other) const`

#### struct `FTimedDataMonitorChannelIdentifier`  
`struct FTimedDataMonitorChannelIdentifier`  
_L36-54_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- L42 _private member_ `FGuid Identifier;` — `UPROPERTY()`
- L45 _public prototype_ `static FTimedDataMonitorChannelIdentifier NewIdentifier();`
- L47 _public function_ `bool IsValid() const`
- L49 _public function_ `bool operator== (const FTimedDataMonitorChannelIdentifier& Other) const`
- L50 _public function_ `bool operator!= (const FTimedDataMonitorChannelIdentifier& Other) const`
- L51 _public function_ `bool operator< (const FTimedDataMonitorChannelIdentifier& Other) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TIMEDDATAMONITOR_API`
- L31 _function_ `friend uint32 GetTypeHash(const FTimedDataMonitorInputIdentifier& InIdentifier)`
- L53 _function_ `friend uint32 GetTypeHash(const FTimedDataMonitorChannelIdentifier& InIdentifier)`
