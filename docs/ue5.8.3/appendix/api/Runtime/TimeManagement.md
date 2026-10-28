# Runtime / TimeManagement

- module root: `Source/Runtime/TimeManagement`
- headers: 26; symbols: 399
- symbol kinds: class=21, delegate=4, enum=4, enumerator=27, function=77, macro=3, member=101, namespace=11, prototype=136, struct=13, typedef=2
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore

### `Source/Runtime/TimeManagement/Public/CatchupFixedRateCustomTimeStep.h` (Public)


#### class `UCatchupFixedRateCustomTimeStep`  
`class UCatchupFixedRateCustomTimeStep : public UFixedFrameRateCustomTimeStep, public IClockedTimeStep`  
_L22-66_
- reflection: `UCLASS(Blueprintable, editinlinenew, meta = (DisplayName = "Catchup Fixed Rate"), MinimalAPI)`
- inherits: `UFixedFrameRateCustomTimeStep,IClockedTimeStep`
- desc: Control the Engine TimeStep via a fixed frame rate that catches up with real time. - Stays in sync with platform time. - Blocks to prevent getting ahead of real time. - Does not block when it needs to catch up - If it falls behind too much, it will increase simulation delta times.
- L29 _public prototype_ `virtual bool Initialize(UEngine* InEngine) override;`
- L30 _public prototype_ `virtual void Shutdown(UEngine* InEngine) override;`
- L31 _public prototype_ `virtual bool UpdateTimeStep(UEngine* InEngine) override;`
- L32 _public prototype_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override;`
- L33 _public prototype_ `virtual FFrameRate GetFixedFrameRate() const override;`
- L37 _public prototype_ `virtual TOptional<double> GetUnderlyingClockTime_AnyThread() override;`
- L43 _private prototype_ `void BlockUntilPlatformSeconds(const double TargetPlatformSeconds) const;` — Blocks until platform time reaches the given time
- L49 _private prototype_ `double CalculateDeltaSeconds(const double CurrentSimulationSeconds, const double CurrentPlatformSeconds) const;` — Calculates the delta time to apply for the current frame based on the difference between simulation time and platform time. Adjusts the simulation delta time to account for systemic fall-behind, allowing the simulation to catch up smoothly.
- L55 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(EditAnywhere, Category = "Timing")` — Desired simulation frame rate
- L59 _public member_ `double MaxCatchupSeconds = 16;` — `UPROPERTY(EditAnywhere, Category = "Timing", meta = (ClampMin = "2"))` — Maximum catchup time in seconds. Simulation will catch up instantly if it falls behind beyond this time with respect to platform time
- L64 _private member_ `double SimulationSeconds = 0;` — Keeps track of our simulation time, which is intentionally kept close to platform time

### `Source/Runtime/TimeManagement/Public/CommonFrameRates.h` (Public)


#### enum `ECommonFrameRate`  
`enum class ECommonFrameRate : uint8`  
_L11-29_
- L13 _public enumerator_ `FPS_12`
- L14 _public enumerator_ `FPS_15`
- L15 _public enumerator_ `FPS_24`
- L16 _public enumerator_ `FPS_25`
- L17 _public enumerator_ `FPS_30`
- L18 _public enumerator_ `FPS_48`
- L19 _public enumerator_ `FPS_50`
- L20 _public enumerator_ `FPS_60`
- L21 _public enumerator_ `FPS_100`
- L22 _public enumerator_ `FPS_120`
- L23 _public enumerator_ `FPS_240`
- L24 _public enumerator_ `NTSC_24`
- L25 _public enumerator_ `NTSC_30`
- L26 _public enumerator_ `NTSC_60`
- L28 _public enumerator_ `Private_Num`

#### struct `FCommonFrameRateInfo`  
`struct FCommonFrameRateInfo`  
_L31-36_
- L33 _public member_ `FFrameRate FrameRate;`
- L34 _public member_ `FText DisplayName;`
- L35 _public member_ `FText Description;`

#### struct `FCommonFrameRates`  
`struct FCommonFrameRates`  
_L38-77_
- L40 _public typedef_ `typedef __underlying_type(ECommonFrameRate) NumericType;`
- L42 _public function_ `inline static FFrameRate FPS_12()`
- L43 _public function_ `inline static FFrameRate FPS_15()`
- L44 _public function_ `inline static FFrameRate FPS_24()`
- L45 _public function_ `inline static FFrameRate FPS_25()`
- L46 _public function_ `inline static FFrameRate FPS_30()`
- L47 _public function_ `inline static FFrameRate FPS_48()`
- L48 _public function_ `inline static FFrameRate FPS_50()`
- L49 _public function_ `inline static FFrameRate FPS_60()`
- L50 _public function_ `inline static FFrameRate FPS_100()`
- L51 _public function_ `inline static FFrameRate FPS_120()`
- L52 _public function_ `inline static FFrameRate FPS_240()`
- L54 _public function_ `inline static FFrameRate NTSC_24()`
- L55 _public function_ `inline static FFrameRate NTSC_30()`
- L56 _public function_ `inline static FFrameRate NTSC_60()`
- L58 _public prototype_ `static TArrayView<const FCommonFrameRateInfo> GetAll();`
- L60 _public function_ `static bool Contains(FFrameRate FrameRateToCheck)`
- L65 _public prototype_ `static const FCommonFrameRateInfo* Find(FFrameRate InFrameRate);`
- L73 _public prototype_ `static const FCommonFrameRateInfo* Find(const double InFrameRateAsDecimal, const double Tolerance = UE_DOUBLE_KINDA_SMALL_NUMBER);` — Find a common frame rate that matches the given frame rate as a decimal number of frames per second. @param InFrameRateAsDecimal: Frame rate (in frames per second) to search for. @param Tolerance: Numerical tolerance to use when searching for a frame rate match. @return: a pointer to the matching common frame rate if a match was found, or nullptr otherwise.
- L76 _private member_ `static const FCommonFrameRateInfo AllFrameRates[(int32)ECommonFrameRate::Private_Num];`

### `Source/Runtime/TimeManagement/Public/Estimation/IClockedTimeStep.h` (Public)


#### class `UClockedTimeStep`  
`class UClockedTimeStep : public UInterface`  
_L9-12_
- reflection: `UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IClockedTimeStep`  
`class IClockedTimeStep`  
_L18-28_
- desc: Intended to be implemented by UEngineCustomTimeStep implementations that have an underlying clock they synchronize to. This is used, e.g. by UTimecodeRegressionProvider to estimate the timecode when the engine hitches.
- L27 _public prototype_ `virtual TOptional<double> GetUnderlyingClockTime_AnyThread() = 0;` — @return The latest / immediate value of the clock. The clock is what the implementation uses to determine the DeltaTime in UpdateTimeStep. If the current time is not available (e.g. still setting up a remote protocol) then this returns unset.

### `Source/Runtime/TimeManagement/Public/Estimation/TimecodeEstimator.h` (Public)


#### struct `UE::TimeManagement::TimecodeEstimation::FFetchAndUpdateStats`  
`struct FFetchAndUpdateStats`  
_L19-23_
- desc: Misc information about how the timecode estimation was updated.
- L22 _public member_ `FQualifiedFrameTime UnderlyingFrameTime;` — The frame time that was sampled from the underlying timecode provider.

#### class `UE::TimeManagement::TimecodeEstimation::FTimecodeEstimator`  
`class FTimecodeEstimator`  
_L67-160_
- desc: Estimates the current timecode based on an IClockedTimeStep implementation, which is designed to be an UEngineCustomTimeStep. The engine starts each frame by calling UEngineCustomTimeStep::UpdateTimeStep. Then, using UTimecodeProvider::FetchAndUpdate, the engine calls FApp::SetCurrentFrameTime with the result of UTimecodeProvider::GetQualifiedFrameTime. Workflow: - FTimecodeEstimator: FetchAndUpdate samples the time code and tags it using the underlying clock's actual time (platform time, PTP, etc.), which is retrieved using IClockedTimeStep. - FTimecodeEstimator::GetQualifiedFrameTime estimates the current frame's time code by using the FApp::CurrentTime for linear regression of the sampled time codes. For this to work, FApp::CurrentTime is expected to be accumulation of all past delta times the UCustomTimeStep step has issued, which is sometimes called "game time" or "simulation time". If coupled with a UEngineCustomTimeStep that implements a fixed engine step rate, we can effectively handle hitching game frames, i.e. when frames take longer than the frame rate dedicated by the time code provider. Some systems, like Live Link, are used for querying external data; for the look-up, we use the frame's time code of the frame. However, when a frame takes longer, the subsequent frame needs to use the timecode value that was intended for that frame. The previous engine behaviour was to use FPlatformTime::Seconds() to determine the timecode the frame should have, which can cause th
- L76 _public prototype_ `explicit FTimecodeEstimator( SIZE_T InNumSamples, UTimecodeProvider& InTimecode UE_LIFETIMEBOUND, IClockedTimeStep& InEngineCustomTimeStep UE_LIFETIMEBOUND );` — @param InNumSamples The number of samples to used for linear regression. @param InTimecode The timecoder provider for which we estimate the current frame's time. Caller ensures this outlives the constructed FTimecodeEstimator. @param InEngineCustomTimeStep The provider of the current clock time. Caller ensures this outlives the constructed FTimecodeEstimator.
- L87 _public prototype_ `TOptional<FFetchAndUpdateStats> FetchAndUpdate();` — Samples the current timecode and associates it with the underlying clock value. @return Metadata about how update has occured, e.g. the "real", frame time sampled from the timecode provider. Unset if the custom time step's clock could not be read.
- L93 _public prototype_ `FQualifiedFrameTime EstimateFrameTime() const;` — Gets the current (cached) estimated frame time. If this is called before FetchAndUpdate() call then no cached timecode will be available and thus it will use the base timecode implementation to query the estimated frame time.
- L100 _private prototype_ `void CalculateEstimatedFrameTime();` — Calculate the next qualified frame time based on the samples store in our regression estimator.  This is called on FetchAndUpdate() and updates the internal cached frametime value.
- L107 _private prototype_ `FFrameTime RoundFrameOrResetEstimator(const FFrameTime& UnroundedEstimatedTime);` — Uses the previous frame time to determine the correct way to round the computed regression value to the correct TC value. This function may reset the regressor if a negative step was detected.  This could happen in TC rollover or bad data from the underlying provider.
- L112 _private prototype_ `void Reset();` — Reset the estimator back to the startup state.  This is necessary when rollover or negative regression estimate is detected.
- L126 _private member_ `TOptional<double> StartClockTime;` — The clock time when we were initialized. This is subtracted from IClockedTimeStep::GetUnderlyingClockTime_AnyThread when used. Clock times are subtracted with this value before they are passed to LinearRegression. This effectively makes all values relative to the start time. For example, in the linear regression input time 0.0 -> 00:09:15.009, time 0.4 -> 00:09:15.014, etc. The reason for this is minimize double precision issues. E.g. FPlatformTime::Seconds() adds 16777216.0 to the result, which when tested caused a lot of numerical instability for the linear regression. Doubles are more accurate the closer you are at 0 so we want to measure as close to that as possible.
- L129 _private member_ `UTimecodeProvider& TimecodeProvider;` — Provides the actual time code.
- L132 _private member_ `IClockedTimeStep& EngineCustomTimeStep;` — Provides the current clock time.
- L135 _private member_ `FLinearFunction LinearRegressionFunction;` — Linear function that is used for predicting timecode (Y, dependent variable) based on clock time (X, independent variable)
- L138 _private member_ `TOptional<FQualifiedFrameTime> CachedEstimatedFrameTime;` — Currently cached estimated frame time.
- L144 _private member_ `TOptional<FQualifiedFrameTime> PreviousEstimatedFrameTime;` — Previously calculated estimated frame time used to analyze which boundary we are on for the "next" timecode.  It helps resolve the staircase problem when sampling from a linear regression to a discrete timecode value.
- L146 _private typedef_ `using FClockTimecodeSample = FVector2d;` — X = clock time, Y = timecode converted using FFrameRate::AsSeconds.
- L153 _private member_ `FCachedLinearRegressionSums ClockToTimecodeSamples;` — Used for computing the TimecodeLinearRegression based on frame time (Y, dependent variable) based on clock time (X, independent variable). - Clock time is already a double. - The frame time is timecode, i.e. the format 00:09:15.009. To do linear math with it, we must convert it to a number. For this we use FFrameRate::AsSeconds.
- L159 _private member_ `FFrameRate LastFrameRate;` — The last frame rate reported by the time code provider. Used to convert timecode to a double for linear regression. If the value changes, the linear regression sampling buffer needs to be cleared.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TIMEMANAGEMENT_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TimeManagement` (scope `UE`)
- L16 _namespace_ `namespace TimecodeEstimation` (scope `UE::TimeManagement`)

### `Source/Runtime/TimeManagement/Public/Estimation/TimecodeRegressionProvider.h` (Public)


#### class `UTimecodeRegressionProvider`  
`class UTimecodeRegressionProvider : public UTimecodeProvider`  
_L23-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTimecodeProvider`
- desc: Estimates the current timecode based on the clock of the engine's current UCustomTimeStep. @see FTimecodeEstimator for a detailed explanation. This class is intended to be used for wrapping a UTimecodeProvider that was previously set using UEngine::SetTimecodeProvider. We probably want the engine to always run with UTimecodeRegressionProvider since otherwise frame hitches cause the timecode to be evaluated incorrectly. However, making that kind code change is risky so for now, we make systems that require it opt-in. In the future, we can refactor UEngine to use FTimecodeEstimator directly and then we can remove UTimecodeRegressionProvider.
- L36 _public member_ `int32 NumSampledFrames = 60;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 1, ClampMax = 65536, UIMin = 1, UIMax = 65536))` — Determines the number of samples to use for linear regression. You'd want to set this number in relation to your target frame rate. Example: If targeting a fixed frame rate of 24 then setting this to 24 would cause linear regression to effectively use 1s worth frames. If you were targeting 60 FPS and wanted 1s worth of frames, you'd set this value to 60.
- L39 _public prototype_ `static bool SupportsTimestep(UEngineCustomTimeStep* InTimestep);` — @return Whether InTimestep is supported for timecode regression (non-null & implements the IClockedTimeStep interface).
- L42 _public prototype_ `void SetTimecodeImplementation(UTimecodeProvider* InTimecodeImpl);` — Sets the actual time code provider. You must call this before registering with the engine, i.e. before Initialize() is called.
- L45 _public prototype_ `TOptional<FQualifiedFrameTime> GetLastSampledFrameTime() const;` — @return Gets the frame time that was last appended to the linear regression.
- L48 _public function_ `UTimecodeProvider* GetUnderlyingTimecodeProvider() const` — @return The timecode provider which we sample and use to estimate timecode.
- L54 _public function_ `virtual bool FetchTimecode(FQualifiedFrameTime& OutFrameTime) override`
- L58 _public prototype_ `virtual void FetchAndUpdate() override;`
- L59 _public prototype_ `virtual FQualifiedFrameTime GetQualifiedFrameTime() const override;`
- L60 _public prototype_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override;`
- L61 _public prototype_ `virtual bool Initialize(UEngine* InEngine) override;`
- L62 _public prototype_ `virtual void Shutdown(UEngine* InEngine) override;`
- L63 _public function_ `virtual bool SupportsAutoDetected() const override`
- L67 _public function_ `virtual void SetIsAutoDetected(bool bInIsAutoDetected) override`
- L71 _public function_ `virtual bool IsAutoDetected() const override`
- L81 _private member_ `TObjectPtr<UEngine> OwningEngine;` — `UPROPERTY()` — The UEngine that called Initialize() on us. Used to respond to the custom time step changing.
- L84 _private member_ `TObjectPtr<UTimecodeProvider> TimecodeImpl;` — `UPROPERTY()` — The real timecode provider, which this class is wrapping.
- L102 _private member_ `TOptional<FTimecodeEstimationState> EstimationState;` — Data set while we're estimating timecode.
- L105 _private function_ `bool IsInitialized() const` — @return Whether Initialize has been called.
- L111 _private function_ `void OnCustomTimeStepChanged()` — When the time step changes, the underlying clock may have changed: thus we should regenerate the sampled data.
- L114 _private prototype_ `void ReinitRegressionBuffer();` — Clears the buffer if there is no custom time step.

#### struct `UTimecodeRegressionProvider::FTimecodeEstimationState`  
`struct FTimecodeEstimationState`  
_L87-100_
- desc: Data valid for the lifetime of the FTimecodeEstimator.
- L90 _public member_ `UE::TimeManagement::TimecodeEstimation::FTimecodeEstimator TimecodeEstimator;` — Estimates the timecode based on FApp::CurrentTime.
- L93 _public member_ `TOptional<UE::TimeManagement::TimecodeEstimation::FFetchAndUpdateStats> LastUpdateStats;` — Result from last TimecodeEstimator.FetchAndUpdate call.
- L95 _public function_ `explicit FTimecodeEstimationState( SIZE_T InNumSamples, UTimecodeProvider& InTimecode UE_LIFETIMEBOUND, IClockedTimeStep& InEngineCustomTimeStep UE_LIFETIMEBOUND ) : TimecodeEstimator(InNumSamples, InTimecode, InEngineCustomTimeStep)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TIMEMANAGEMENT_API`

### `Source/Runtime/TimeManagement/Public/FixedFrameRateCustomTimeStep.h` (Public)


#### class `UFixedFrameRateCustomTimeStep`  
`class UFixedFrameRateCustomTimeStep : public UEngineCustomTimeStep`  
_L22-40_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UEngineCustomTimeStep`
- desc: Class to control the Engine TimeStep via a FixedFrameRate
- L28 _public prototype_ `virtual FString GetDisplayName() const override;`
- L32 _public prototype_ `virtual FFrameRate GetFixedFrameRate() const PURE_VIRTUAL(UFixedFrameRateCustomTimeStep::GetFixedFrameRate, return GetFixedFrameRate_PureVirtual(););` — Get The fixed FrameRate
- L36 _protected prototype_ `void WaitForFixedFrameRate() const;` — Default behavior of the engine. Used FixedFrameRate
- L39 _private prototype_ `FFrameRate GetFixedFrameRate_PureVirtual() const;`

### `Source/Runtime/TimeManagement/Public/FrameNumberDisplayFormat.h` (Public)


#### enum `EFrameNumberDisplayFormats`  
`enum class EFrameNumberDisplayFormats : uint8`  
_L9-24_
- reflection: `UENUM()`
- L12 _public enumerator_ `NonDropFrameTimecode UMETA(DisplayName="NDF Timecode")` — Non-Drop Frame Timecode
- L15 _public enumerator_ `DropFrameTimecode UMETA(DisplayName="DF Timecode")` — Drop Frame Timecode
- L17 _public enumerator_ `Seconds`
- L19 _public enumerator_ `Frames`
- L21 _public enumerator_ `Custom UMETA(Hidden)`
- L23 _public enumerator_ `MAX_Count UMETA(Hidden)`

### `Source/Runtime/TimeManagement/Public/FrameNumberNumericInterface.h` (Public)


#### struct `FFrameNumberInterface`  
`struct FFrameNumberInterface : public INumericTypeInterface<double>`  
_L30-245_
- inherits: `INumericTypeInterface<double>`
- desc: A large portion of the Sequencer UI is built around using SpinBox and NumericBox because the framerate used to be stored in (float) seconds. This creates a convenient UI as it allows the users to type in numbers (for frames or seconds), or to drag the mouse to change the time. When Sequencer was converted to using integer based frames and frame rates (expressed as numerator/denominator) the spinbox-based UI became an issue as SpinBox and NumericBox internally convert to a double to perform various calculations. This is an issue if your Spinbox type (ie: FQualifiedFrameTime) is not implicitly convertible to double, which the new Sequencer types are not (due to accidental type coercion when using outside the UI). To solve this, the Spinboxes will still use double as their type, but double now means frame number and not time. A double can store the entire range of int32 (which backs FFrameNumber) without precision loss, and we can execute callbacks to find out what framerate the sequence is running at. This allows us to display in Timecode, Time or Frames and convert back and forth to double for the UI, and from double into the backing FFrameNumber for the sequence.
- L32 _public function_ `FFrameNumberInterface(const TAttribute<EFrameNumberDisplayFormats>& InDisplayFormatAttr, const TAttribute<uint8>& InOnGetZeroPadFrameNumber, const TAttribute<FFrameRate>& InTickResolutionAttr, const TAttribute<FFrameRate>& InDisplayRateAttr) : DisplayFormatAttr(InDisplayFormatAttr) , TickResolutionAttr(InTickResolutionAttr) , DisplayRateAttr(InDisplayRateAttr) , ZeroPadFramesAttr(InOnGetZeroPadFrameNumber) , SubframeIndicator(TEXT("*"))`
- L45 _public function_ `virtual int32 GetMinFractionalDigits() const override` — Gets the minimum and maximum fractional digits.
- L49 _public function_ `virtual int32 GetMaxFractionalDigits() const override`
- L55 _public function_ `virtual void SetMinFractionalDigits(const TAttribute<TOptional<int32>>& NewValue) override` — Sets the minimum and maximum fractional digits - A minimum greater than 0 will always have that many trailing zeros
- L57 _public function_ `virtual void SetMaxFractionalDigits(const TAttribute<TOptional<int32>>& NewValue) override`
- L60 _public function_ `virtual bool IsCharacterValid(TCHAR InChar) const override` — Check whether the typed character is valid
- L74 _public function_ `virtual FString ToString(const double& Value) const override`
- L124 _public function_ `virtual TOptional<double> FromString(const FString& InString, const double& InExistingValue) override`
- L215 _public function_ `FString GetSubframeIndicator() const` — Gets the string suffix used when a stringified value represents a time between whole frames.
- L221 _public function_ `void SetSubframeIndicator(const FString& InSubframeIndicator)` — Sets the string suffix to use when a stringified value represents a time between whole frames.
- L226 _public function_ `void DisplayFormatChanged()`
- L231 _public function_ `virtual FOnSettingChanged* GetOnSettingChanged() override`
- L237 _private member_ `TAttribute<EFrameNumberDisplayFormats> DisplayFormatAttr;`
- L238 _private member_ `TAttribute<FFrameRate> TickResolutionAttr;`
- L239 _private member_ `TAttribute<FFrameRate> DisplayRateAttr;`
- L240 _private member_ `TAttribute<uint8> ZeroPadFramesAttr;`
- L242 _private member_ `FString SubframeIndicator;`
- L244 _private member_ `FOnSettingChanged OnSettingChangedEvent;`

#### Free symbols / members of external scopes

- L63 _function_ `` (scope `FFrameNumberInterface::IsCharacterValid`)

### `Source/Runtime/TimeManagement/Public/FrameNumberTimeEvaluator.h` (Public)


#### struct `FFrameNumberTimeEvaluator`  
`struct FFrameNumberTimeEvaluator`  
_L24-43_
- L27 _public prototype_ `FFrameNumberTimeEvaluator();` — Constructor that sets up the parser's lexer and compiler
- L30 _public prototype_ `TValueOrError<FFrameTime, FExpressionError> EvaluateTimecode(const TCHAR* InExpression, const FFrameRate& InDisplayFrameRate, const FFrameRate& InTickResolution, bool& OutDirectlyParsed) const;` — Evaluate the given expression, resulting in either a double value, or an error
- L31 _public prototype_ `TValueOrError<FFrameTime, FExpressionError> EvaluateFrame(const TCHAR* InExpression, const FFrameRate& InDisplayFrameRate, const FFrameRate& InTickResolution, bool& OutDirectlyParsed) const;`
- L32 _public prototype_ `TValueOrError<FFrameTime, FExpressionError> EvaluateTime(const TCHAR* InExpression, FFrameRate InFrameRate, bool& OutDirectlyParsed) const;`
- L34 _public member_ `FTokenDefinitions TimecodeTokenDefinitions;`
- L35 _public member_ `FTokenDefinitions FrameTokenDefinitions;`
- L36 _public member_ `FTokenDefinitions TimeTokenDefinitions;`
- L38 _public member_ `FExpressionGrammar FrameGrammar;`
- L39 _public member_ `FExpressionGrammar TimecodeGrammar;`
- L40 _public member_ `FExpressionGrammar TimeGrammar;`
- L42 _public member_ `FOperatorJumpTable TimeJumpTable;`

### `Source/Runtime/TimeManagement/Public/GenlockedCustomTimeStep.h` (Public)


#### class `UGenlockedCustomTimeStep`  
`class UGenlockedCustomTimeStep : public UFixedFrameRateCustomTimeStep`  
_L21-64_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UFixedFrameRateCustomTimeStep`
- desc: Class to control the Engine Timestep from a Genlock signal.
- L28 _protected prototype_ `virtual bool WaitForSync() PURE_VIRTUAL(UGenlockedCustomTimeStep::WaitForSync, return false;);` — Blocks until it gets a sync signal. Returns false if unsuccessful
- L31 _protected prototype_ `void UpdateAppTimes(const double& TimeBeforeSync, const double& TimeAfterSync) const;` — Update FApp CurrentTime, IdleTime and DeltaTime
- L35 _public prototype_ `virtual FFrameRate GetFixedFrameRate() const PURE_VIRTUAL(UGenlockedCustomTimeStep::GetFixedFrameRate, return FFrameRate(24,1););`
- L38 _public function_ `virtual FFrameRate GetSyncRate() const` — Get the sync rate (not always the same as the fixed frame rate)
- L41 _public prototype_ `virtual uint32 GetLastSyncCountDelta() const PURE_VIRTUAL(UGenlockedCustomTimeStep::GetLastSyncCountDelta, return 1;);` — Returns how many syncs occurred since the last tick
- L44 _public prototype_ `virtual bool IsLastSyncDataValid() const PURE_VIRTUAL(UGenlockedCustomTimeStep::IsLastSyncDataValid, return false;);` — Returns true if the Sync related functions will return valid data
- L47 _public prototype_ `virtual uint32 GetExpectedSyncCountDelta() const;` — Returns how many sync counts are expected between ticks
- L50 _public function_ `virtual bool SupportsFormatAutoDetection() const` — Whether automatic format detection is supported.
- L54 _public member_ `bool bAutoDetectFormat = false;` — `UPROPERTY()` — Whether this custom time step should autodetect the video format if supported.
- L57 _public member_ `static TAutoConsoleVariable<int32> CVarExperimentalFieldFlipFix;` — Experimental fix for interlace field flipping issue.
- L63 _public member_ `bool bWaitForBothFields = false;` — `UPROPERTY(EditAnywhere, Category = "Genlock Options")` — When using interlace video as a custom time step, enabling this option will force the engine to wait for both fields to be received before ticking.

### `Source/Runtime/TimeManagement/Public/GenlockedFixedRateCustomTimeStep.h` (Public)


#### class `UGenlockedFixedRateCustomTimeStep`  
`class UGenlockedFixedRateCustomTimeStep : public UGenlockedCustomTimeStep`  
_L33-68_
- reflection: `UCLASS(Blueprintable, editinlinenew, meta = (DisplayName = "Genlocked Fixed Rate"), MinimalAPI)`
- inherits: `UGenlockedCustomTimeStep`
- desc: Control the Engine TimeStep via a fixed frame rate. Philosophy: * Quantized increments but keeping up with platform time. * FApp::GetDeltaTime - Forced to a multiple of the desired FrameTime. * FApp::GetCurrentTime - Incremented in multiples of the desired FrameTime. - Corresponds to platform time minus any fractional FrameTime.
- L39 _public prototype_ `virtual bool Initialize(UEngine* InEngine) override;`
- L40 _public prototype_ `virtual void Shutdown(UEngine* InEngine) override;`
- L41 _public prototype_ `virtual bool UpdateTimeStep(UEngine* InEngine) override;`
- L42 _public prototype_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override;`
- L43 _public prototype_ `virtual FFrameRate GetFixedFrameRate() const override;`
- L46 _public prototype_ `virtual uint32 GetLastSyncCountDelta() const override;`
- L47 _public prototype_ `virtual bool IsLastSyncDataValid() const override;`
- L48 _public prototype_ `virtual bool WaitForSync() override;`
- L54 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(EditAnywhere, Category = "Timing")` — Desired frame rate
- L58 _public member_ `bool bShouldBlock;` — `UPROPERTY(EditAnywhere, Category = "Timing")` — Indicates that this custom time step should block to enforce the specified frame rate. Set to false if this is enforced elsewhere.
- L62 _public member_ `bool bForceSingleFrameDeltaTime;` — `UPROPERTY(EditAnywhere, Category = "Timing")` — When true, delta time will always be 1/FrameRate, regardless of how much real time has elapsed
- L65 _private member_ `uint32 LastSyncCountDelta;`
- L66 _private member_ `double QuantizedCurrentTime;`
- L67 _private member_ `double LastIdleTime;`

### `Source/Runtime/TimeManagement/Public/GenlockedTimecodeProvider.h` (Public)


#### class `UGenlockedTimecodeProvider`  
`class UGenlockedTimecodeProvider : public UTimecodeProvider`  
_L15-40_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UTimecodeProvider`
- desc: This timecode provider base class will try to use the engine genlock sync to adjust its count.
- L23 _public member_ `bool bUseGenlockToCount = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Settings")` — Use Genlock Sync to update Timecode count
- L26 _public prototype_ `virtual void FetchAndUpdate() override;`
- L27 _public prototype_ `virtual FQualifiedFrameTime GetQualifiedFrameTime() const override;`
- L33 _protected prototype_ `virtual FQualifiedFrameTime CorrectFromGenlock(FQualifiedFrameTime& InFrameTime, const UGenlockedCustomTimeStep* Genlock);` — Corrects given timecode with Genlock provider
- L36 _protected member_ `FQualifiedFrameTime LastFrameTime;` — Cache current frame time
- L39 _protected member_ `FQualifiedFrameTime LastFetchedFrameTime;` — Cache last fetched frame time (raw from hardware)

### `Source/Runtime/TimeManagement/Public/ITimeManagementModule.h` (Public)


#### class `ITimeManagementModule`  
`class ITimeManagementModule : public IModuleInterface`  
_L16-46_
- inherits: `IModuleInterface`
- L24 _public function_ `static inline ITimeManagementModule& Get()` — Singleton-like access to ITimeManagementModule @return Returns ITimeManagementModule singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L39 _public prototype_ `virtual FTimedDataInputCollection& GetTimedDataInputCollection() = 0;` — Get the collection of the ITimedDataInput and ITimedDataInputGroups.
- L42 _public prototype_ `virtual TArrayView<const struct FCommonFrameRateInfo> GetAllCommonFrameRates() = 0;` — Returns all stored common frame rates
- L45 _public prototype_ `virtual TSharedRef<SFrameRatePicker> CreateFrameRatePicker(SFrameRatePicker::FArguments Arguments) = 0;` — Returns a widget allowing for the user to pick a specific frame rate

#### Free symbols / members of external scopes

- L10 _macro_ `#define TIMEMANAGEMENT_MODULE_NAME TEXT("TimeManagement")`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTimeManagement, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTimeManagement, Log, All);`

### `Source/Runtime/TimeManagement/Public/ITimedDataInput.h` (Public)


#### enum `ETimedDataInputEvaluationType`  
`enum class ETimedDataInputEvaluationType : uint8`  
_L25-33_
- reflection: `UENUM()`
- L28 _public enumerator_ `None` — There is no special evaluation type for that input.
- L30 _public enumerator_ `Timecode` — The input is evaluated from the engine's timecode.
- L32 _public enumerator_ `PlatformTime` — The input is evaluated from the engine's time. Note that the engine's time is relative to FPlatformTime::Seconds.

#### enum `ETimedDataInputState`  
`enum class ETimedDataInputState : uint8`  
_L36-44_
- reflection: `UENUM()`
- L39 _public enumerator_ `Connected` — The input is connected.
- L41 _public enumerator_ `Unresponsive` — The input is connected but no data is available.
- L43 _public enumerator_ `Disconnected` — The input is not connected.

#### struct `FTimedDataChannelSampleTime`  
`struct FTimedDataChannelSampleTime`  
_L48-62_
- reflection: `USTRUCT(BlueprintType)`
- L52 _public prototype_ `FTimedDataChannelSampleTime() = default;`
- L53 _public function_ `FTimedDataChannelSampleTime(double InPlatformSeconds, const FQualifiedFrameTime& InTimecode) : PlatformSecond(InPlatformSeconds), Timecode(InTimecode)`
- L57 _public member_ `double PlatformSecond = 0.0;` — The time is relative to FPlatformTime::Seconds.
- L59 _public member_ `FQualifiedFrameTime Timecode;` — Timecode value of the sample
- L61 _public function_ `double AsSeconds(ETimedDataInputEvaluationType EvaluationType) const`

#### struct `FTimedDataInputEvaluationData`  
`struct FTimedDataInputEvaluationData`  
_L66-81_
- reflection: `USTRUCT(BlueprintType)`
- L74 _public member_ `float DistanceToNewestSampleSeconds = 0.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Evaluation", meta=(Units=s))` — Distance between evaluation time and newest sample in seconds
- L80 _public member_ `float DistanceToOldestSampleSeconds = 0.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "Evaluation", meta = (Units = s))` — Distance between evaluation time and newest sample in seconds

#### class `ITimedDataInput`  
`class ITimedDataInput`  
_L87-156_
- desc: Interface for data sources that can be synchronized with time
- L90 _public member_ `static FFrameRate UnknownFrameRate;`
- L92 _public prototype_ `static double ConvertSecondOffsetInFrameOffset(double Seconds, FFrameRate Rate);`
- L93 _public prototype_ `static double ConvertFrameOffsetInSecondOffset(double Frames, FFrameRate Rate);`
- L96 _public prototype_ `virtual ~ITimedDataInput() = default;`
- L99 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Get the name used when displayed.
- L102 _public prototype_ `virtual TArray<ITimedDataInputChannel*> GetChannels() const = 0;` — Get a list of the channel this input has.
- L105 _public prototype_ `virtual ETimedDataInputEvaluationType GetEvaluationType() const = 0;` — Get how the input is evaluated.
- L108 _public prototype_ `virtual void SetEvaluationType(ETimedDataInputEvaluationType Evaluation) = 0;` — Set how the input is evaluated.
- L111 _public prototype_ `virtual double GetEvaluationOffsetInSeconds() const = 0;` — Get the offset in seconds used at evaluation.
- L114 _public prototype_ `virtual void SetEvaluationOffsetInSeconds(double Offset) = 0;` — Set the offset in seconds used at evaluation.
- L117 _public prototype_ `virtual FFrameRate GetFrameRate() const = 0;` — Get the frame rate at which the samples are produced.
- L120 _public prototype_ `virtual bool IsDataBufferSizeControlledByInput() const = 0;` — Does channel from this input support a different buffer size than it's input.
- L123 _public function_ `virtual int32 GetDataBufferSize() const` — If the input does supported it, get the size of the buffer used by the input.
- L126 _public function_ `virtual void SetDataBufferSize(int32 BufferSize)` — If the input does supported it, set the size of the buffer used by the input.
- L129 _public prototype_ `virtual void AddChannel(ITimedDataInputChannel* Channel) = 0;` — Add a channel belonging to this input
- L132 _public prototype_ `virtual void RemoveChannel(ITimedDataInputChannel* Channel) = 0;` — Remove channel from the input
- L135 _public function_ `virtual bool SupportsSubFrames() const` — Whether this input supports sub frames.
- L141 _public prototype_ `double ConvertSecondOffsetInFrameOffset(double Seconds) const;` — Convert second offset to frame offset using this input's framerate.
- L144 _public prototype_ `double ConvertFrameOffsetInSecondOffset(double Frames) const;` — Convert frame offset to second offset using this input's framerate.
- L147 _public function_ `virtual UObject* GetSettingsObject() const` — Get the UObject that owns the settings for this input, for saving purposes.
- L154 _public prototype_ `virtual const FSlateBrush* GetDisplayIcon() const = 0;` — Get the icon that represent the input.

#### class `ITimedDataInputChannel`  
`class ITimedDataInputChannel`  
_L162-209_
- desc: Interface for data tracked produced by an input.
- L166 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Get the channel's display name.
- L169 _public prototype_ `virtual ETimedDataInputState GetState() const = 0;` — Get the current state of the channel.
- L172 _public prototype_ `virtual FTimedDataChannelSampleTime GetOldestDataTime() const = 0;` — Get the time of the oldest data sample available.
- L175 _public prototype_ `virtual FTimedDataChannelSampleTime GetNewestDataTime() const = 0;` — Get the time of the newest data sample available.
- L178 _public prototype_ `virtual TArray<FTimedDataChannelSampleTime> GetDataTimes() const = 0;` — Get the time of all the data samples available.
- L181 _public prototype_ `virtual int32 GetNumberOfSamples() const = 0;` — Get the number of data samples available.
- L184 _public function_ `virtual int32 GetDataBufferSize() const` — If the channel does support it, get the current maximum sample count of channel.
- L187 _public function_ `virtual void SetDataBufferSize(int32 BufferSize)` — If the channel does support it, set the maximum sample count of the channel.
- L190 _public prototype_ `virtual bool IsBufferStatsEnabled() const = 0;` — Is tracking of stats enabled for this input
- L193 _public prototype_ `virtual void SetBufferStatsEnabled(bool bEnable) = 0;` — Enables or disables stats tracking for this input
- L196 _public prototype_ `virtual int32 GetBufferUnderflowStat() const = 0;` — Return buffer underflow count detected by this input
- L199 _public prototype_ `virtual int32 GetBufferOverflowStat() const = 0;` — Return buffer overflow count detected by this input
- L202 _public prototype_ `virtual int32 GetFrameDroppedStat() const = 0;` — Return frame dropped count detected by this input
- L205 _public prototype_ `virtual void GetLastEvaluationData(FTimedDataInputEvaluationData& OutEvaluationData) const = 0;` — Get data about last evaluation. Samples used, expected, number of samples.
- L208 _public prototype_ `virtual void ResetBufferStats() = 0;` — Resets internal stat counters

### `Source/Runtime/TimeManagement/Public/Misc/CachedLinearRegressionSums.h` (Public)


#### struct `UE::TimeManagement::FCachedLinearRegressionSums`  
`struct FCachedLinearRegressionSums`  
_L16-31_
- desc: Data structure for building a FLinearFunction based on linear regression. Caches the sums required for linear regression: when an old sample is replaced, the old value is subtracted and the new value added. This effectively avoids the summing all elements whenever the a new sample is added.
- L19 _public member_ `TModuloCircularBuffer<FVector2d> Samples;` — Holds the samples based off of which the samples are created.
- L22 _public member_ `FLinearRegressionArgs CachedSums;` — Caches the sums of the samples. Whenever a sample is replaced, the old value is subtracted and the new value added to the respective sums.
- L24 _public function_ `explicit FCachedLinearRegressionSums(SIZE_T InNumSamples) : Samples(InNumSamples)`
- L27 _public function_ `bool IsEmpty() const` — @return Whether no samples have been added.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TimeManagement` (scope `UE`)
- L34 _prototype_ `void AddSampleAndUpdateSums(const FVector2d& InSample, TModuloCircularBuffer<FVector2d>& InSamples, FLinearRegressionArgs& InCachedArguments);` (scope `UE::TimeManagement`) — Adds a sample and updates the associated sums.
- L36 _function_ `inline void AddSampleAndUpdateSums(const FVector2d& InSample, FCachedLinearRegressionSums& InCachedSums)` (scope `UE::TimeManagement`)

### `Source/Runtime/TimeManagement/Public/Misc/LinearFunction.h` (Public)


#### struct `UE::TimeManagement::FLinearFunction`  
`struct FLinearFunction`  
_L8-20_
- desc: Represents a linear function: f(x) = a*x + b
- L11 _public member_ `double Slope = 1;` — The a in "f(x) = a*x + b"
- L13 _public member_ `double Offset = 0;` — The b in "f(x) = a*x + b"
- L16 _public function_ `double Evaluate(double X) const` — Computes the function value using X as input.

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace TimeManagement` (scope `UE`)

### `Source/Runtime/TimeManagement/Public/Misc/LinearRegression.h` (Public)


#### struct `UE::TimeManagement::FLinearRegressionArgs`  
`struct FLinearRegressionArgs`  
_L12-24_
- desc: The input arguments required to compute linear regression.
- L15 _public member_ `double SumX = 0.0;` — The sum of all X
- L17 _public member_ `double SumY = 0.0;` — The sum of all Y
- L19 _public member_ `double SumXxY = 0.0;` — The sum of each X multiplied with its Y.
- L21 _public member_ `double SumOfSquaredXes = 0.0;` — The sum of all squared X values
- L23 _public member_ `SIZE_T Num = 0;` — The number of samples

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TimeManagement` (scope `UE`)
- L30 _prototype_ `FLinearRegressionArgs ComputeLinearRegressionInputArgs(const TConstArrayView<FVector2d>& InBuffer);` (scope `UE::TimeManagement`) — @return The arguments required to compute linear regression based off of InBuffer. FVector2d::X is the independent variable, and FVector2d::Y the associated dependent variable value for the X.
- L40 _prototype_ `bool ComputeLinearRegressionSlopeAndOffset( const FLinearRegressionArgs& InArgs, double& OutSlope, double& OutOffset );` (scope `UE::TimeManagement`) — Computes the coefficients for a linear function by using linear regression. @param InArgs The arguments required to compute linear regression @param OutSlope The slope for the linear regression. The a in "f(x) = a*x + b". @param OutOffset The offset for the linear regression. The b in "f(x) = a*x + b". @return True if the function was defined. False if the linear regression function was not defined, i.e. was no correlation. @note Sets OutSlope and OutOffset to 0 when the function is not defined.
- L46 _function_ `inline bool ComputeLinearRegressionSlopeAndOffset(const FLinearRegressionArgs& InArgs, FLinearFunction& OutFunction)` (scope `UE::TimeManagement`) — Util that puts the sets the values of the linear function.

### `Source/Runtime/TimeManagement/Public/Misc/ModuloCircularBuffer.h` (Public)


#### class `UE::TimeManagement::TModuloCircularBuffer`  
`template<typename T, typename TAllocator = FDefaultAllocator> class TModuloCircularBuffer`  
_L17-74_
- desc: A circular buffer of any size (opposed to TCircularBuffer which requires power of 2). The next index is computed using the modulo operation: NextIndexToInsert = (NextIndexToInsert + 1) % Data.Num(). It's less performant than bitmasking, which TCircularBuffer uses, but does not require any specific element count.
- L21 _public function_ `explicit TModuloCircularBuffer(SIZE_T InNumSamples)`
- L24 _public function_ `void Add(const T& InItem)` — Adds an item to the buffer. If the buffer is full, the oldest item is replaced.
- L32 _public function_ `const T* GetNextReplacedItem() const` — @return Pointer to the item that is replaced with the next Add call. If no item is replaced, then
- L38 _public function_ `SIZE_T Capacity() const` — @return The number of items that can be stored in this buffer.
- L44 _public function_ `SIZE_T Num() const` — @return The number of items in the buffer so far.
- L49 _public function_ `bool IsEmpty() const` — @return Whether nothing has ever been added.
- L55 _public function_ `bool IsFull() const` — @return Whether the buffer is full, i.e. add an item will override an item.
- L61 _public function_ `TConstArrayView<T> AsUnorderedView() const` — @return A view into the data. Unordered here it does not represent the order in which items were added. This is useful if you want to sum up all entries, etc.
- L68 _private member_ `TArray<T, TAllocator> Data;`
- L71 _private member_ `bool bIsBufferFull = false;` — When recalculating, tells us how to sum up the samples. If false, we'll only sum of the first NextIndexToInsert elements of Samples. Otherwise all.
- L73 _private member_ `SIZE_T NextIndexToInsert = 0;` — The next item will be added to this index. Once bIsBufferFull == true, this points to the oldest data sample.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TimeManagement` (scope `UE`)

### `Source/Runtime/TimeManagement/Public/MusicalTimeFunctionLibrary.h` (Public)


#### class `UMusicalTimeFunctionLibrary`  
`class UMusicalTimeFunctionLibrary : public UBlueprintFunctionLibrary`  
_L20-37_
- reflection: `UCLASS(meta = (BlueprintThreadSafe, ScriptName = "MusicalTimeFunctionLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Expose FMusicalTime methods to blueprints
- L27 _public prototype_ `static bool IsValid(const FMusicalTime& InMusicalTime);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Valid Musical Time"), Category = "Utilities|Musical Time")`
- L30 _public prototype_ `static float FractionalBeatsInBar(const FMusicalTime& InMusicalTime);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Fractional Beat In Bar"), Category = "Utilities|Musical Time")`
- L33 _public prototype_ `static float FractionalBars(const FMusicalTime& InMusicalTime);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Fractional Bar"), Category = "Utilities|Musical Time")`
- L36 _public prototype_ `static void BarAndBeat(const FMusicalTime& InMusicalTime, int& Bar, float& Beat);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Bar & Beat"), Category = "Utilities|Musical Time")`

### `Source/Runtime/TimeManagement/Public/TimeManagementBlueprintLibrary.h` (Public)


#### class `UTimeManagementBlueprintLibrary`  
`class UTimeManagementBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L28-113_
- reflection: `UCLASS(meta = (BlueprintThreadSafe, ScriptName = "TimeManagementLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L36 _public prototype_ `static float Conv_FrameRateToSeconds(const FFrameRate& InFrameRate);` — `UE_DEPRECATED(5.3, "Conv_FrameRateToSeconds has been deprecated, use Conv_FrameRateToInterval instead")` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameRate To Seconds", BlueprintAutocast, DeprecatedFunction, DeprecationMessage = "FrameRateToInterval replaces this function, which returns the expected result of seconds per frame, rather than (incorrectly) frames per second."), Category = "Utilities|Time Management")` — Converts an FrameRate to a float ie: 1/30 returns 0.0333333
- L40 _public prototype_ `static float Conv_FrameRateToInterval(const FFrameRate InFrameRate);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameRate To Interval", BlueprintAutocast), Category = "Utilities|Time Management")` — Converts a FrameRate to an interval float representing the frame time in seconds ie: 1/30 returns 0.0333333
- L44 _public prototype_ `static float Conv_QualifiedFrameTimeToSeconds(const FQualifiedFrameTime& InFrameTime);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "QualifiedFrameTime To Seconds", BlueprintAutocast), Category = "Utilities|Time Management")` — Converts an QualifiedFrameTime to seconds.
- L48 _public prototype_ `static FFrameTime Multiply_SecondsFrameRate(float TimeInSeconds, const FFrameRate& FrameRate);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Seconds * FrameRate", CompactNodeTitle = "*"), Category = "Utilities|Time Management")` — Multiplies a value in seconds against a FrameRate to get a new FrameTime.
- L52 _public prototype_ `static FString Conv_TimecodeToString(const FTimecode& InTimecode, bool bForceSignDisplay = false);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Timecode To String", BlueprintAutocast), Category = "Utilities|Time Management")` — Converts an Timecode to a string (hh:mm:ss:ff). If bForceSignDisplay then the number sign will always be prepended instead of just when expressing a negative time.
- L56 _public prototype_ `static bool IsValid_Framerate(const FFrameRate& InFrameRate);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Valid Frame Rate"), Category = "Utilities|Time Management")` — Verifies that this is a valid framerate with a non-zero denominator.
- L60 _public prototype_ `static bool IsValid_MultipleOf(const FFrameRate& InFrameRate, const FFrameRate& OtherFramerate);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Is Multiple Of"), Category = "Utilities|Time Management")` — Checks if this framerate is an even multiple of another framerate, ie: 60 is a multiple of 30, but 59.94 is not.
- L64 _public prototype_ `static FFrameTime TransformTime(const FFrameTime& SourceTime, const FFrameRate& SourceRate, const FFrameRate& DestinationRate);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Transform Frame Time"), Category = "Utilities|Time Management")` — Converts the specified time from one framerate to another framerate. This is useful for converting between tick resolution and display rate.
- L68 _public prototype_ `static FFrameTime SnapFrameTimeToRate(const FFrameTime& SourceTime, const FFrameRate& SourceRate, const FFrameRate& SnapToRate);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "Snap Frame Time"), Category = "Utilities|Time Management")` — Snaps the given SourceTime to the nearest frame in the specified Destination Framerate. Useful for determining the nearest frame for another resolution. Returns the frame time in the destination frame rate.
- L72 _public prototype_ `static FFrameNumber Add_FrameNumberFrameNumber(FFrameNumber A, FFrameNumber B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameNumber + FrameNumber", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true", ScriptMethod, ScriptMethodSelfReturn, ScriptOperator = "+;+="), Category = "Utilities|Time Management")` — Addition (FrameNumber A + FrameNumber B)
- L76 _public prototype_ `static FFrameNumber Subtract_FrameNumberFrameNumber(FFrameNumber A, FFrameNumber B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameNumber - FrameNumber", CompactNodeTitle = "-", Keywords = "- subtract minus", ScriptMethod, ScriptMethodSelfReturn, ScriptOperator = "-;-="), Category = "Utilities|Time Management")` — Subtraction (FrameNumber A - FrameNumber B)
- L80 _public prototype_ `static FFrameNumber Add_FrameNumberInteger(FFrameNumber A, int32 B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameNumber + Int", CompactNodeTitle = "+", Keywords = "+ add plus", ScriptMethod, ScriptMethodSelfReturn, ScriptOperator = "+;+="), Category = "Utilities|Time Management")` — Addition (FrameNumber A + int B)
- L84 _public prototype_ `static FFrameNumber Subtract_FrameNumberInteger(FFrameNumber A, int32 B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameNumber - Int", CompactNodeTitle = "-", Keywords = "- subtract minus", ScriptMethod, ScriptMethodSelfReturn, ScriptOperator = "-;-="), Category = "Utilities|Time Management")` — Subtraction (FrameNumber A - int B)
- L88 _public prototype_ `static FFrameNumber Multiply_FrameNumberInteger(FFrameNumber A, int32 B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameNumber * Int", CompactNodeTitle = "*", Keywords = "* multiply", ScriptMethod, ScriptMethodSelfReturn, ScriptOperator = "*;*="), Category = "Utilities|Time Management")` — Multiply (FrameNumber A * B)
- L92 _public prototype_ `static FFrameNumber Divide_FrameNumberInteger(FFrameNumber A, int32 B);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameNumber / FrameNumber", CompactNodeTitle = "/", Keywords = "/ divide", ScriptMethod, ScriptMethodSelfReturn, ScriptOperator = "/;/="), Category = "Utilities|Time Management")` — Divide (FrameNumber A / B)
- L96 _public prototype_ `static int32 Conv_FrameNumberToInteger(const FFrameNumber& InFrameNumber);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "FrameNumber to Integer", ScriptName="FrameNumberToInteger", BlueprintAutocast), Category = "Utilities|Time Management")` — Converts a FrameNumber to an int32 for use in functions that take int32 frame counts for convenience.
- L100 _public prototype_ `static FTimecode GetTimecode();` — `UFUNCTION(BlueprintPure, Category = "Utilities|Time Management")` — Get the current timecode of the engine.
- L104 _public prototype_ `static FFrameRate GetTimecodeFrameRate();` — `UFUNCTION(BlueprintPure, Category = "Utilities|Time Management")` — Gets the current timecode frame rate.
- L108 _public prototype_ `static UEngineCustomTimeStep* GetEngineCustomTimeStep();` — `UFUNCTION(BlueprintPure, Category="Utilities|Engine Time", meta=(DisplayName="Get Engine Custom Time Step"))` — Returns the active custom time step. Requires a UFixedFrameRateCustomTimeStep; returns null otherwise.
- L112 _public prototype_ `static FFrameRate GetCustomTimeStepFrameRate();` — `UFUNCTION(BlueprintPure, Category="Utilities|Engine Time", meta=(DisplayName="Get Custom Time Step Frame Rate"))` — Returns the frame rate of the active custom time step. Requires a UFixedFrameRateCustomTimeStep; returns FFrameRate() otherwise.

### `Source/Runtime/TimeManagement/Public/TimeSynchronizationSource.h` (Public)


#### struct `FTimeSynchronizationOpenData`  
`struct FTimeSynchronizationOpenData`  
_L21-32_
- L24 _public member_ `FFrameRate SynchronizationFrameRate;` — Frame rate that will be used as the base for synchronization.
- L31 _public member_ `TOptional<FFrameTime> RolloverFrame;` — The frame on which rollover occurs (i.e., the modulus value of rollover). This is relative to the SynchronizationFrameRate. Not set if rollover is not used.

#### struct `FTimeSynchronizationStartData`  
`struct FTimeSynchronizationStartData`  
_L35-42_
- desc: Values that will be sent to sources when synchronization has been successfully started.
- L41 _public member_ `FFrameTime StartFrame;` — The frame on which synchronization was established. This is relative to SynchronizationFrameRate in FTimecodeSynchronizationOpenData.

#### class `UTimeSynchronizationSource`  
`class UTimeSynchronizationSource : public UObject`  
_L53-199_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for sources to be used for time synchronization. Subclasses don't need to directly contain data, nor provide access to the data in any way (although they may). Currently, Synchronization does not work on the subframe level.
- L61 _public member_ `bool bUseForSynchronization;` — `UPROPERTY(EditAnywhere, Category = Synchronization)` — Whether or not this source should be considered when establishing synchronization.
- L69 _public member_ `int32 FrameOffset;` — `UPROPERTY(EditAnywhere, Category = Synchronization)` — An additional offset in frames (relative to this source's frame rate) that should used. This is mainly useful to help correct discrepancies between the reported Sample Times and how the samples actually line up relative to other sources.
- L75 _public prototype_ `virtual TSharedRef<SWidget> GetVisualWidget() const;` — Get Visual Widget of this source to display in UI
- L121 _public function_ `inline static bool IsFrameBetweenWithRolloverModulus(const FFrameTime& ToCheck, const FFrameTime& LowerBound, const FFrameTime& UpperBound, const FFrameTime& RolloverModulus)` — Checks to see whether or not the given frame is between the Lower and Upper bounds. It's assumed the bounds are in appropriate order (i.e., LowerBound <= UpperBound, unless they span across a rollover boundary, in which case LowerBound > UpperBound). It's assumed the value to check is also valid (between 0 and the rollover modulus). @param ToCheck			The value to check. @param LowerBound		The lower bound of times to check. @param UpperBound		The upper bound of times to check. @param RolloverModulus	Rollover frame value.
- L134 _public function_ `inline static FTimecode ConvertFrameTimeToTimecode(const FFrameTime& FrameTime, const FFrameRate& FrameRate)` — Convenience method to convert a FrameTime and FrameRate to a timecode value.
- L147 _public function_ `inline static FFrameTime AddOffsetWithRolloverModulus(const FFrameTime& FrameTime, const int32 Offset, const FFrameTime& RolloverModulus)` — Adds an integer offset (representing frames) to the given FrameTime. It's expected the offset's magnitude will be less than the rollover modulus. @param FrameTime			The base frame time. @param Offset			The offset to add. @param RolloverModulus	Rollover frame value.
- L164 _public function_ `static int32 FindDistanceBetweenFramesWithRolloverModulus(const FFrameTime& StartFrameTime, const FFrameTime& EndFrameTime, const TOptional<FFrameTime>& RolloverModulus, bool& bDidRollover)` — Calculates the distance between two frames. This method accounts for rollover (when used), and assumes the frames will always be relatively close together. This is also a convenient method to use to check whether or not a rollover has happened within a range of frames. @param StartFrameTime	The start time in the range. @param EndFrameTime		The end time in the range. @param RolloverModulus	Rollover frame value. Unset if rollover isn't used. @param bDidRollover		[out] Whether or not a rollover occurred in the input range.

### `Source/Runtime/TimeManagement/Public/TimecodeCustomTimeStep.h` (Public)


#### class `UTimecodeCustomTimeStep`  
`class UTimecodeCustomTimeStep : public UFixedFrameRateCustomTimeStep`  
_L18-70_
- reflection: `UCLASS(Blueprintable, editinlinenew, MinimalAPI, meta = (DisplayName = "Timecode Custom Time Step"))`
- inherits: `UFixedFrameRateCustomTimeStep`
- desc: Control the engine's time step via the engine's TimecodeProvider. Will sleep and wake up the engine when a new frame is available.
- L24 _public prototype_ `virtual bool Initialize(UEngine* InEngine) override;`
- L25 _public prototype_ `virtual void Shutdown(UEngine* InEngine) override;`
- L26 _public prototype_ `virtual bool UpdateTimeStep(UEngine* InEngine) override;`
- L27 _public function_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override`
- L28 _public function_ `virtual FFrameRate GetFixedFrameRate() const override`
- L33 _public member_ `bool bErrorIfFrameAreNotConsecutive = false;` — `UPROPERTY(EditAnywhere, Category = "CustomTimeStep")` — If true, stop the CustomTimeStep if the new timecode value doesn't follow the previous timecode value.
- L37 _public member_ `bool bErrorIfTimecodeProviderChanged = false;` — `UPROPERTY(EditAnywhere, Category = "CustomTimeStep")` — If true, stop the CustomTimeStep if the engine's TimeProvider changed since last frame.
- L41 _public member_ `float MaxDeltaTime = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "CustomTimeStep")` — If the timecode doesn't change after that amount of time, stop the CustomTimeStep.
- L48 _public member_ `bool bIgnoreSubframes = true;` — `UPROPERTY(EditAnywhere, Category = "CustomTimeStep")` — If true, the subframe frame portion of timecode will be ignored when comparing the current and previous timecode sample Set to true if you wish to sample an overriden timecode rate rather than the rate data is received at eg. Live Link Timecode from a 120fps system but with timecode of 24. Defaults to = true
- L51 _private prototype_ `bool InitializeFirstStep(UEngine* InEngine);`
- L53 _private prototype_ `void OnTimecodeProviderChanged();`
- L57 _private member_ `ECustomTimeStepSynchronizationState State = ECustomTimeStepSynchronizationState::Closed;` — The current SynchronizationState of the CustomTimeStep.
- L60 _private member_ `FTimecode PreviousTimecode;` — The last timecode of the TimecodeProvider.
- L63 _private member_ `FFrameRate PreviousFrameRate;` — The last frame rate of the TimecodeProvider.
- L66 _private member_ `double InitializedSeconds = 0.0;` — The time at initialization.
- L69 _private member_ `bool bWarnAboutSynchronizationState = false;` — Only warn once about the synchronization state.

### `Source/Runtime/TimeManagement/Public/TimedDataInputCollection.h` (Public)


#### class `FTimedDataInputCollection`  
`class FTimedDataInputCollection`  
_L14-78_
- desc: A list of all the timed data input.
- L19 _public function_ `void Add(ITimedDataInput* Input)` — Add an timed input to the collection.
- L29 _public function_ `void Remove(ITimedDataInput* Input)` — Remove an input from the collection.
- L38 _public function_ `const TArray<ITimedDataInput*>& GetInputs() const` — The list of inputs from the collection.
- L44 _public function_ `void Add(ITimedDataInputChannel* Channel)` — Add an input channel to the collection.
- L54 _public function_ `void Remove(ITimedDataInputChannel* Input)` — Remove an input channel from the collection.
- L63 _public function_ `const TArray<ITimedDataInputChannel*>& GetChannels() const` — The list of input channels from the collection.
- L69 _public function_ `FSimpleMulticastDelegate& OnCollectionChanged()` — When an element is added or removed to the collection.
- L75 _private member_ `FSimpleMulticastDelegate CollectionChanged;`
- L76 _private member_ `TArray<ITimedDataInput*> Inputs;`
- L77 _private member_ `TArray<ITimedDataInputChannel*> Channels;`

### `Source/Runtime/TimeManagement/Public/Widgets/SFrameRateEntryBox.h` (Public)


#### class `SFrameRateEntryBox`  
`class SFrameRateEntryBox : public SCompoundWidget`  
_L16-62_
- inherits: `SCompoundWidget`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FFrameRate);`
- L21 _public function_ `SLATE_BEGIN_ARGS(SFrameRateEntryBox) : _Style(&FCoreStyle::Get().GetWidgetStyle< FEditableTextBoxStyle >("NormalEditableTextBox"))`
- L26 _public prototype_ `SLATE_ATTRIBUTE(FFrameRate, Value) SLATE_EVENT(FOnValueChanged, OnValueChanged) SLATE_ATTRIBUTE(bool, HasMultipleValues) SLATE_STYLE_ARGUMENT( FEditableTextBoxStyle, Style ) SLATE_ATTRIBUTE( FSlateFontInfo, Font ) SLATE_ATTRIBUTE( FSlateColor, ForegroundColor ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Attribute used to retrieve the current value.
- L52 _private prototype_ `FText GetValueText() const;`
- L54 _private prototype_ `void ValueTextComitted(const FText& InNewText, ETextCommit::Type InTextCommit);`
- L57 _private member_ `TAttribute<FFrameRate> ValueAttribute;`
- L58 _private member_ `FOnValueChanged OnValueChangedDelegate;`
- L59 _private member_ `TAttribute<bool> HasMultipleValuesAttribute;`
- L61 _private member_ `TSharedPtr<IErrorReportingWidget> ErrorReporting;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FFrameRate);`

### `Source/Runtime/TimeManagement/Public/Widgets/SFrameRatePicker.h` (Public)


#### class `SFrameRatePicker`  
`class SFrameRatePicker : public SCompoundWidget`  
_L18-109_
- inherits: `SCompoundWidget`
- desc: A widget which allows the user to enter a digit or choose a number from a drop down menu.
- L21 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FFrameRate);`
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsPresetRecommended, FFrameRate);`
- L24 _public function_ `SLATE_BEGIN_ARGS(SFrameRatePicker) : _ComboButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FComboButtonStyle >("ComboButton")) , _ButtonStyle(nullptr) , _ForegroundColor(FSlateColor::UseForeground()) , _ContentPadding(FMargin(2.f, 0.f)) , _HasMultipleValues(false) , _PresetValues() , _Font()`
- L35 _public prototype_ `SLATE_STYLE_ARGUMENT(FComboButtonStyle, ComboButtonStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_ATTRIBUTE(FSlateColor, ForegroundColor) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ATTRIBUTE(FFrameRate, Value) SLATE_EVENT(FOnValueChanged, OnValueChanged) SLATE_ATTRIBUTE(bool, HasMultipleValues) SLATE_ARGUMENT(TArray<FCommonFrameRateInfo>, PresetValues) SLATE_ATTRIBUTE(FText, RecommendedText) SLATE_ATTRIBUTE(FText, NotRecommendedText) SLATE_ATTRIBUTE(FText, NotRecommendedToolTip) SLATE_EVENT(FIsPresetRecommended, IsPresetRecommended) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_END_ARGS()` — The visual style of the combo button
- L83 _public prototype_ `FFrameRate GetCurrentValue() const;` — Access the current value of this picker
- L87 _private prototype_ `FText GetValueText() const;`
- L89 _private prototype_ `TSharedRef<SWidget> BuildMenu();`
- L90 _private prototype_ `void PopulateNotRecommendedMenu(FMenuBuilder& MenuBuilder);`
- L92 _private prototype_ `void SetValue(FFrameRate InValue);`
- L97 _private member_ `TArray<FCommonFrameRateInfo> PresetValues;`
- L99 _private member_ `TAttribute<FFrameRate> ValueAttribute;`
- L100 _private member_ `FOnValueChanged OnValueChangedDelegate;`
- L102 _private member_ `TAttribute<bool> HasMultipleValuesAttribute;`
- L104 _private member_ `TAttribute<FText> RecommendedText;`
- L105 _private member_ `TAttribute<FText> NotRecommendedText;`
- L106 _private member_ `TAttribute<FText> NotRecommendedToolTip;`
- L108 _private member_ `FIsPresetRecommended IsPresetRecommendedDelegate;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FFrameRate);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsPresetRecommended, FFrameRate);`

### `Source/Runtime/TimeManagement/Public/Widgets/STimecode.h` (Public)


#### class `STimecode`  
`class STimecode : public SLeafWidget`  
_L16-74_
- inherits: `SLeafWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(STimecode) : _TimecodeColor(FLinearColor::White) , _DisplayLabel(true) , _LabelColor(FLinearColor::Gray)`
- L30 _public prototype_ `SLATE_ATTRIBUTE(FTimecode, Timecode) SLATE_ATTRIBUTE(FSlateFontInfo, TimecodeFont) SLATE_ATTRIBUTE(FSlateColor, TimecodeColor) SLATE_ATTRIBUTE(bool, DisplayLabel) SLATE_ATTRIBUTE(FSlateFontInfo, LabelFont) SLATE_ATTRIBUTE(FSlateColor, LabelColor) SLATE_ARGUMENT(bool, bDisplaySubframes) SLATE_END_ARGS() STimecode();` — The timecode to display
- L52 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget @param	InArgs	The declaration data for this widget
- L56 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget overrides
- L57 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScale) const override;`
- L58 _protected prototype_ `virtual bool ComputeVolatility() const override;`
- L61 _private member_ `TAttribute<FTimecode> Timecode;`
- L62 _private member_ `TAttribute<FSlateFontInfo> TimecodeFont;`
- L63 _private member_ `TAttribute<FSlateColor> TimecodeColor;`
- L65 _private member_ `TAttribute<bool> bDisplayLabel;`
- L66 _private member_ `TAttribute<FSlateFontInfo> LabelFont;`
- L67 _private member_ `TAttribute<FSlateColor> LabelColor;`
- L70 _private member_ `bool bDisplaySubframes = true;` — Whether to display subframes.
- L73 _private member_ `TUniquePtr<FSlateTextBlockLayout> TextLayoutCache;` — Test layout cache used to correctly compute the text size for the timecode text.
