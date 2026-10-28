# Plugins / AudioWidgets

- module root: `Plugins/Runtime/AudioWidgets/Source/AudioWidgets`
- headers: 70; symbols: 2317
- symbol kinds: class=70, delegate=47, enum=19, enumerator=48, function=238, macro=49, member=914, namespace=17, prototype=865, struct=48, typedef=2
- PrivateDependencyModuleNames: AdvancedWidgets, AppFramework, AudioMixer, CoreUObject, Engine, InputCore, SignalProcessing, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: AudioAnalyzer, AudioSynesthesia, AudioWidgetsCore, Core, UMG

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Private/AudioAnalyzerRackUnitRegistry.h` (Private)


#### class `AudioWidgets::FAudioAnalyzerRackUnitRegistry`  
`class FAudioAnalyzerRackUnitRegistry`  
_L8-23_
- L11 _public prototype_ `static FAudioAnalyzerRackUnitRegistry& Get();`
- L12 _public prototype_ `static void TearDown();`
- L14 _public prototype_ `void RegisterRackUnitType(const FAudioAnalyzerRackUnitTypeInfo* RackUnitTypeInfo);`
- L16 _public prototype_ `TSharedRef<IAudioAnalyzerRackUnit> MakeRackUnit(FName RackUnitTypeName, const FAudioAnalyzerRackUnitConstructParams& Params);`
- L18 _public prototype_ `void GetRegisteredRackUnitTypes(TArray<const FAudioAnalyzerRackUnitTypeInfo*>& OutArray) const;`
- L19 _public prototype_ `void GetRegisteredRackUnitTypeNames(TArray<FName>& OutArray) const;`
- L22 _private member_ `TMap<FName, const FAudioAnalyzerRackUnitTypeInfo*> RegisteredRackUnitTypes;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace AudioWidgets`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioAnalyzerRack.h` (Public)


#### struct `AudioWidgets::FAudioBusInfo`  
`struct FAudioBusInfo`  
_L17-25_
- desc: FAudioBusInfo encapsulates the required info that describes the audio bus that is to be analyzed.
- L19 _public member_ `static constexpr Audio::FDeviceId InvalidAudioDeviceId = static_cast<Audio::FDeviceId>(INDEX_NONE);`
- L21 _public member_ `Audio::FDeviceId AudioDeviceId = InvalidAudioDeviceId;`
- L22 _public member_ `TObjectPtr<UAudioBus> AudioBus = nullptr;`
- L24 _public function_ `int32 GetNumChannels() const`

#### class `AudioWidgets::IAudioAnalyzerRackUnit`  
`class IAudioAnalyzerRackUnit : public TSharedFromThis<IAudioAnalyzerRackUnit>`  
_L30-46_
- inherits: `TSharedFromThis<IAudioAnalyzerRackUnit>`
- desc: Interface for something that can be used in an analyzer rack.
- L33 _public prototype_ `virtual ~IAudioAnalyzerRackUnit() = default;`
- L36 _public prototype_ `virtual void SetAudioBusInfo(const FAudioBusInfo& AudioBusInfo) = 0;` — If the Audio Bus to analyze changes (due to channel count change), handle this here.
- L39 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args) const = 0;` — Spawn the actual analyzer Widget in a DockTab.
- L42 _public function_ `virtual void StartProcessing()` — Be notified of request to start processing.
- L45 _public function_ `virtual void StopProcessing()` — Be notified of request to stop processing.

#### struct `AudioWidgets::FAudioAnalyzerRackUnitConstructParams`  
`struct FAudioAnalyzerRackUnitConstructParams`  
_L51-56_
- desc: Parameters for the FOnMakeAudioAnalyzerRackUnit delegate.
- L53 _public member_ `FAudioBusInfo AudioBusInfo;`
- L54 _public member_ `const ISlateStyle* StyleSet = nullptr;`
- L55 _public member_ `const UClass* EditorSettingsClass = nullptr;`

#### struct `AudioWidgets::FAudioAnalyzerRackUnitTypeInfo`  
`struct FAudioAnalyzerRackUnitTypeInfo`  
_L63-70_
- desc: Static type descriptor data for a rack unit type.
- L65 _public member_ `FName TypeName;`
- L66 _public member_ `FText DisplayName;`
- L67 _public member_ `FSlateIcon Icon;`
- L68 _public member_ `FOnMakeAudioAnalyzerRackUnit OnMakeAudioAnalyzerRackUnit;`
- L69 _public member_ `float VerticalSizeCoefficient;`

#### class `AudioWidgets::FAudioAnalyzerRack`  
`class FAudioAnalyzerRack : public TSharedFromThis<FAudioAnalyzerRack>`  
_L75-128_
- inherits: `TSharedFromThis<FAudioAnalyzerRack>`
- desc: Manages display of audio analyzer rack units. Rack units can be shown, hidden, and reordered by the user.
- L93 _public prototype_ `FAudioAnalyzerRack(const FRackConstructParams& Params);`
- L94 _public prototype_ `virtual ~FAudioAnalyzerRack();`
- L96 _public prototype_ `void Init(int32 InNumChannels, Audio::FDeviceId InAudioDeviceId);`
- L97 _public prototype_ `void DestroyAnalyzers();`
- L99 _public prototype_ `TSharedRef<SWidget> CreateWidget(TSharedRef<SDockTab> DockTab, const FSpawnTabArgs& SpawnTabArgs);`
- L101 _public prototype_ `UAudioBus* GetAudioBus() const;`
- L103 _public prototype_ `void StartProcessing();`
- L104 _public prototype_ `void StopProcessing();`
- L107 _protected prototype_ `virtual TSharedRef<FTabManager::FArea> CreatePrimaryArea(const TArray<const FAudioAnalyzerRackUnitTypeInfo*>& RackUnitTypes);`
- L110 _private prototype_ `static TSharedRef<SWidget> MakeVisibleAnalyzersMenu(TSharedRef<FUICommandList> InCommandList, TWeakPtr<FWorkspaceItem> InWorkspaceGroup, TWeakPtr<FTabManager> InTabManager);`
- L112 _private prototype_ `static void SaveTabLayout(const TSharedRef<FTabManager::FLayout>& InLayout);`
- L113 _private prototype_ `TSharedRef<FTabManager::FLayout> LoadTabLayout();`
- L114 _private prototype_ `TSharedRef<FTabManager::FLayout> GetDefaultTabLayout();`
- L116 _private prototype_ `TSharedRef<IAudioAnalyzerRackUnit> MakeRackUnit(FName RackUnitTypeName);`
- L118 _private member_ `FName TabManagerLayoutName;`
- L119 _private member_ `TSet<FName> ExcludedRackUnitTypes;`
- L121 _private member_ `TStrongObjectPtr<UAudioBus> AudioBus;`
- L122 _private member_ `FAudioAnalyzerRackUnitConstructParams RackUnitConstructParams;`
- L124 _private member_ `TMap<FName, TSharedRef<IAudioAnalyzerRackUnit>> RackUnits;`
- L125 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L127 _private member_ `bool bIsProcessingStarted = false;`

#### struct `AudioWidgets::FAudioAnalyzerRack::FRackConstructParams`  
`struct FRackConstructParams`  
_L78-91_
- L81 _public member_ `FName TabManagerLayoutName;` — The rack layout can be saved using the given name.
- L84 _public member_ `const ISlateStyle* StyleSet = nullptr;` — An ISlateStyle can be provided to override AudioWidgetsStyle.
- L87 _public member_ `const UClass* EditorSettingsClass = nullptr;` — An Editor Settings class can be provided for rack units that require one for saving settings.
- L90 _public member_ `TSet<FName> ExcludedRackUnitTypes;` — Rack unit type names to exclude from the rack (they won't appear in the menu or layout).

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L12 _namespace_ `namespace AudioWidgets`
- L58 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<IAudioAnalyzerRackUnit>, FOnMakeAudioAnalyzerRackUnit, const FAudioAnalyzerRackUnitConstructParams&);`
- L58 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<IAudioAnalyzerRackUnit>, FOnMakeAudioAnalyzerRackUnit, const FAudioAnalyzerRackUnitConstructParams&);` (scope `AudioWidgets`)

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioColorMapper.h` (Public)


#### enum `EAudioColorGradient`  
`enum class EAudioColorGradient : uint8`  
_L10-14_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `BlackToWhite`
- L13 _public enumerator_ `WhiteToBlack`

#### class `FAudioColorMapper`  
`class FAudioColorMapper`  
_L19-39_
- desc: Helper class for normalizing and applying a colormapping to unnormalized data.
- L22 _public function_ `FAudioColorMapper(const float InMinValue, const float InMaxValue, const EAudioColorGradient InColorMap) : ValueScaling(1.0f / (InMaxValue - InMinValue)) , MinValue(InMinValue) , ColorMap(InColorMap)`
- L30 _public prototype_ `FColor GetColorFromValue(const float Value) const;`
- L32 _public prototype_ `static FColor ColorMapBlackToWhite(const float T);`
- L33 _public prototype_ `static FColor ColorMapWhiteToBlack(const float T);`
- L36 _private member_ `const float ValueScaling;`
- L37 _private member_ `const float MinValue;`
- L38 _private member_ `const EAudioColorGradient ColorMap;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioLoudnessMeter.h` (Public)


#### struct `AudioWidgets::FAudioLoudnessMeterParams`  
`struct FAudioLoudnessMeterParams`  
_L17-22_
- desc: Constructor parameters for the analyzer.
- L19 _public member_ `int32 NumChannels = 1;`
- L20 _public member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L21 _public member_ `TObjectPtr<UAudioBus> ExternalAudioBus = nullptr;`

#### class `AudioWidgets::FAudioLoudnessMeter`  
`class FAudioLoudnessMeter : public IAudioAnalyzerRackUnit`  
_L28-107_
- inherits: `IAudioAnalyzerRackUnit`
- desc: Owns an analyzer and a corresponding Slate widget for displaying the loudness stats. Can either create an Audio Bus to analyze, or analyze the given Bus.
- L31 _public member_ `static const FAudioAnalyzerRackUnitTypeInfo RackUnitTypeInfo;`
- L33 _public prototype_ `FAudioLoudnessMeter(const FAudioLoudnessMeterParams& Params);`
- L34 _public prototype_ `~FAudioLoudnessMeter();`
- L37 _public prototype_ `virtual void SetAudioBusInfo(const FAudioBusInfo& AudioBusInfo) override;`
- L38 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args) const override;`
- L49 _private prototype_ `static TSharedRef<IAudioAnalyzerRackUnit> MakeRackUnit(const FAudioAnalyzerRackUnitConstructParams& Params);`
- L51 _private prototype_ `void Init(int32 InNumChannels, Audio::FDeviceId InAudioDeviceId, TObjectPtr<UAudioBus> InExternalAudioBus);`
- L52 _private prototype_ `void Teardown();`
- L54 _private prototype_ `void CreateLKFSAnalyzer();`
- L55 _private prototype_ `void ReleaseLKFSAnalyzer();`
- L56 _private prototype_ `void ResetLKFSAnalyzer();`
- L58 _private prototype_ `void CreateTruePeakAnalyzer();`
- L59 _private prototype_ `void ReleaseTruePeakAnalyzer();`
- L60 _private prototype_ `void ResetTruePeakAnalyzer();`
- L62 _private prototype_ `void InitLoudnessMeterWidgetView(const FAudioAnalyzerRackUnitConstructParams& Params);`
- L64 _private prototype_ `void OnLoudnessOutput(ULKFSAnalyzer* InLKFSAnalyzer, const FLKFSResults& InLoudnessResults);`
- L65 _private prototype_ `void OnTruePeakOutput(UMeterAnalyzer* InMeterAnalyzer, int32 InChannelIndex, const TArray<FMeterResults>& InMeterResultsArray);`
- L67 _private prototype_ `FTimespan GetAnalysisTime() const;`
- L68 _private prototype_ `FReply HandleResetButtonClicked();`
- L71 _private member_ `AudioWidgetsCore::FLoudnessMeterWidgetView LoudnessMeterWidgetView;` — Creates the meters widget
- L74 _private member_ `TStrongObjectPtr<ULKFSAnalyzer> LKFSAnalyzer;` — Loudness analyzer object.
- L77 _private member_ `TStrongObjectPtr<ULKFSSettings> LKFSSettings;` — Loudness analyzer settings.
- L80 _private member_ `FDelegateHandle LatestOverallLKFSResultsDelegateHandle;` — Handle for results delegate for loudness analyzer.
- L83 _private member_ `TOptional<FLKFSResults> LatestLoudnessResults;` — Most recent results from the loudness analyzer.
- L86 _private member_ `TStrongObjectPtr<UMeterAnalyzer> TruePeakAnalyzer;` — True peak analyzer object.
- L89 _private member_ `TStrongObjectPtr<UMeterSettings> TruePeakSettings;` — True peak analyzer settings.
- L92 _private member_ `FDelegateHandle PerChannelMeterResultsNativeDelegateHandle;` — Handle for results delegate for true peak analyzer.
- L95 _private member_ `TOptional<FMeterResults> LatestTruePeakResults;` — Most recent results from the true peak analyzer.
- L98 _private member_ `FLoudnessMeterMaxResults LoudnessMeterMaxResults;` — Loudness meter max results (only for short term loudness, momentary loudness and true peak).
- L100 _private member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L102 _private member_ `FTSTicker::FDelegateHandle WidgetRefreshTicker;`
- L105 _private member_ `TStrongObjectPtr<UAudioBus> AudioBus;` — The audio bus used for analysis.
- L106 _private member_ `bool bUseExternalAudioBus = false;`

#### struct `AudioWidgets::FAudioLoudnessMeter::FLoudnessMeterMaxResults`  
`struct FLoudnessMeterMaxResults`  
_L42-47_
- L44 _public member_ `float ShortTermLoudness = MIN_VOLUME_DECIBELS;`
- L45 _public member_ `float MomentaryLoudness = MIN_VOLUME_DECIBELS;`
- L46 _public member_ `float TruePeakDb = MIN_VOLUME_DECIBELS;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L12 _namespace_ `namespace AudioWidgets`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/AudioMaterialButton.h` (Public)


#### class `UAudioMaterialButton`  
`class UAudioMaterialButton : public UWidget`  
_L27-96_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A simple widget that shows a button Button is rendered by using material instead of texture. * No Children
- L33 _public prototype_ `UAudioMaterialButton();`
- L37 _public member_ `FAudioMaterialButtonStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Style", ShowOnlyInnerProperties))` — The button's style
- L41 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L46 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget
- L50 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual
- L55 _public prototype_ `bool GetIsPressed() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Button")` — Gets the current value of the slider.
- L59 _public prototype_ `void SetIsPressed(bool InPressed);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Button")` — Sets the current value of the slider. InValue is Clamped between 0.f - 1.f
- L65 _public member_ `FOnButtonPressedChangedEvent OnButtonPressedChangedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when the value is changed by button.
- L69 _public member_ `FOnButtonMouseCaptureBeginEvent OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when mouse capture begins.
- L73 _public member_ `FOnButtonMouseCaptureEndEvent OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when mouse capture ends (mouse release or any other capture loss).
- L78 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget
- L81 _protected prototype_ `void HandleOnPressedValueChanged(bool InPressedSate);`
- L82 _protected prototype_ `void HandleOnMouseCaptureBegin();`
- L83 _protected prototype_ `void HandleOnMouseCaptureEnd();`
- L89 _private member_ `bool bIsPressed = false;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetIsPressed, BlueprintGetter = GetIsPressed, Category = "Appearance")` — Default Value of the button
- L94 _private member_ `TSharedPtr<SAudioMaterialButton> Button;` — Native Slate Widget

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonMouseCaptureBeginEvent);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonMouseCaptureBeginEvent);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonMouseCaptureEndEvent);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonMouseCaptureEndEvent);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressedChangedEvent, bool, bIsPressed);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressedChangedEvent, bool, bIsPressed);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/AudioMaterialEnvelope.h` (Public)


#### class `UAudioMaterialEnvelope`  
`class UAudioMaterialEnvelope : public UWidget`  
_L22-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A simple widget that shows a envelope curve Depending on given AudioMaterialEnvelopeSetings Rendered by using material instead of texture. * No Children
- L28 _public prototype_ `UAudioMaterialEnvelope();`
- L32 _public member_ `FAudioMaterialEnvelopeStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Style", ShowOnlyInnerProperties))` — The Envelope's style
- L36 _public member_ `FAudioMaterialEnvelopeSettings EnvelopeSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")` — Envelope settings
- L41 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L45 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget
- L49 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual
- L55 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget
- L61 _private member_ `TSharedPtr<SAudioMaterialEnvelope> EnvelopeCurve;` — Native Slate Widget

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/AudioMaterialEnvelopeSettings.h` (Public)


#### enum `EAudioMaterialEnvelopeType`  
`enum class EAudioMaterialEnvelopeType : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- desc: Envelope curve types A: Attack D: Decay S: Sustain R: Release
- L17 _public enumerator_ `AD`
- L18 _public enumerator_ `ADSR`

#### struct `FAudioMaterialEnvelopeSettings`  
`struct FAudioMaterialEnvelopeSettings`  
_L22-90_
- reflection: `USTRUCT(BlueprintType)`
- L32 _public member_ `EAudioMaterialEnvelopeType EnvelopeType = EAudioMaterialEnvelopeType::ADSR;` — `UPROPERTY(EditAnywhere, Category = "Envelope|Type")` — The Type of the envelope curve.
- L39 _public member_ `float AttackCurve = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Envelope|Attack")` — Curve of the envelopes attack stage. Attack is the time taken for the rise of the level from zero to a given value.
- L46 _public member_ `float AttackValue = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Envelope|Attack")` — Value of the envelopes attack stage. Attack is the time taken for the rise of the level from zero to a given value.
- L53 _public member_ `float AttackTime = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Envelope|Attack")` — Time the Value reaches the Attack stage. Attack is the time taken for the rise of the level from zero to a given value.
- L60 _public member_ `float DecayCurve = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Envelope|Decay")` — Curve of the envelopes Decay stage. Decay is the time taken for the level to reduce from the attack level to the sustain level.
- L67 _public member_ `float DecayTime = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Envelope|Decay")` — Time that takes to reach the level of the Sustain stage. Decay is the time taken for the level to reduce from the attack level to the sustain level.
- L74 _public member_ `float SustainValue = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "EnvelopeType==EAudioMaterialEnvelopeType::ADSR", EditConditionHides), Category = "Envelope|Sustain")` — Value of the envelopes Sustain stage. Sustain is the level maintained until release stage.
- L81 _public member_ `float ReleaseCurve = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "EnvelopeType==EAudioMaterialEnvelopeType::ADSR", EditConditionHides), Category = "Envelope|Release")` — Curve of the envelopes Release stage. Release is the time taken for the level to decay from sustain to zero.
- L88 _public member_ `float ReleaseTime = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "EnvelopeType==EAudioMaterialEnvelopeType::ADSR", EditConditionHides), Category = "Envelope|Release")` — Time that takes to reach zero level Release is the time taken for the level to decay from sustain to zero.

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/AudioMaterialKnob.h` (Public)


#### class `UAudioMaterialKnob`  
`class UAudioMaterialKnob : public UWidget`  
_L26-155_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A simple widget that shows a turning Knob that allows you to control the value between 0..1. Knob is rendered by using material instead of texture. * No Children
- L32 _public prototype_ `UAudioMaterialKnob(const FObjectInitializer& ObjectInitializer);`
- L36 _public member_ `FAudioMaterialKnobStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Style", ShowOnlyInnerProperties))` — The button's style
- L40 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L44 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget
- L48 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual
- L53 _public prototype_ `float GetValue();` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Knob")` — Get the current value of the knob.
- L57 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Knob")` — Set the current value of the knob. InValue is Clamped between 0.f - 1.f
- L61 _public prototype_ `void SetTuneSpeed(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Knob")` — Set the knobs tune speed. InValue is Clamped between 0.f - 1.f
- L65 _public prototype_ `float GetTuneSpeed() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Knob")` — Get the Knobs tune speed
- L69 _public prototype_ `void SetFineTuneSpeed(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Knob")` — Set the knobs fine-tune speed. InValue is Clamped between 0.f - 1.f
- L73 _public prototype_ `float GetFineTuneSpeed() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Knob")` — Get the Knobs fine-tune speed
- L77 _public prototype_ `void SetLocked(bool InLocked);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Knob")` — Set the knob to be interactive or fixed
- L81 _public prototype_ `bool GetIsLocked() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Knob")` — Get whether the knob is interactive or fixed.
- L85 _public prototype_ `void SetMouseUsesStep(bool InUsesStep);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Knob")` — Set the knob to use steps when turning On Mouse move
- L89 _public prototype_ `bool GetMouseUsesStep() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Knob")` — Get whether the knob uses steps when tuning On Mouse move
- L93 _public prototype_ `void SetStepSize(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Knob")` — Set the amount to adjust the value when using steps
- L97 _public prototype_ `float GetStepSize() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Knob")` — Get Step Size
- L103 _public member_ `FOnKnobValueChangedEvent OnKnobValueChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when the value is changed by knob.
- L107 _public member_ `FOnKnobMouseCaptureBeginEvent OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when mouse capture begins.
- L111 _public member_ `FOnKnobMouseCaptureEndEvent OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when mouse capture ends (mouse release or any other capture loss).
- L116 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget
- L119 _protected prototype_ `void HandleOnKnobValueChanged(float InValue);`
- L125 _private member_ `float Value = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetValue, BlueprintGetter = GetValue, Category = "Appearance", meta = (UIMin = "0", UIMax = "1"))` — Default Value of the Knob
- L129 _private member_ `float TuneSpeed;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetTuneSpeed, BlueprintGetter = GetTuneSpeed, Category = Appearance, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — The tune speed of the knob
- L133 _private member_ `float FineTuneSpeed;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetFineTuneSpeed, BlueprintGetter = GetFineTuneSpeed, Category = Appearance, AdvancedDisplay, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — The tune speed when fine-tuning the knob
- L137 _private member_ `bool bLocked;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetLocked, BlueprintGetter = GetIsLocked, Category = Appearance, AdvancedDisplay)` — Whether the knob is interactive or fixed.
- L141 _private member_ `bool bMouseUsesStep;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetMouseUsesStep, BlueprintGetter = GetMouseUsesStep, Category = Appearance, AdvancedDisplay)` — Sets new value if mouse position is greater/less than half the step size.
- L145 _private member_ `float StepSize;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetStepSize, BlueprintGetter = GetStepSize, Category = Appearance, AdvancedDisplay, meta = (UIMin = "0", UIMax = "1"))` — The amount to adjust the value by, when using steps
- L149 _private prototype_ `void HandleOnKnobCaptureBegin();`
- L150 _private prototype_ `void HandleOnKnobCaptureEnd();`
- L153 _private member_ `TSharedPtr<SAudioMaterialKnob> Knob;` — Native Slate Widget

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKnobMouseCaptureBeginEvent);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKnobMouseCaptureBeginEvent);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKnobMouseCaptureEndEvent);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKnobMouseCaptureEndEvent);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKnobValueChangedEvent, float, Value);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKnobValueChangedEvent, float, Value);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/AudioMaterialMeter.h` (Public)


#### class `UAudioMaterialMeter`  
`class UAudioMaterialMeter : public UWidget`  
_L23-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: Meter is rendered by using material instead of texture. * No Children
- L29 _public prototype_ `UAudioMaterialMeter();`
- L33 _public member_ `FAudioMaterialMeterStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Style", ShowOnlyInnerProperties))` — The meter's style
- L37 _public member_ `TEnumAsByte<EOrientation> Orientation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The Meter's orientation.
- L42 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L46 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget
- L50 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual
- L55 _public prototype_ `TArray<FMeterChannelInfo> GetMeterChannelInfo() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Meter")` — Gets the current linear values of the meter.
- L59 _public prototype_ `void SetMeterChannelInfo(const TArray<FMeterChannelInfo>& InMeterChannelInfo);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Meter")` — Sets the current meter values.
- L63 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<FMeterChannelInfo>, FGetMeterChannelInfo);`
- L67 _public member_ `FGetMeterChannelInfo MeterChannelInfoDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the meter
- L72 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget
- L75 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(TArray<FMeterChannelInfo>, MeterChannelInfo);`
- L80 _private member_ `TSharedPtr<SAudioMaterialMeter> Meter;` — Native Slate Widget
- L84 _private member_ `TArray<FMeterChannelInfo> MeterChannelInfo;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetMeterChannelInfo, BlueprintGetter = GetMeterChannelInfo, Category = MeterValues)` — The current meter value to display.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L63 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<FMeterChannelInfo>, FGetMeterChannelInfo);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/AudioMaterialSlateTypes.h` (Public)


#### struct `FAudioMaterialWidgetStyle`  
`struct FAudioMaterialWidgetStyle : public FSlateWidgetStyle`  
_L19-39_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Base for the appearance of an Audio Material Slates
- L25 _public prototype_ `FAudioMaterialWidgetStyle();`
- L29 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = 0), Category = "Style")` — Material used to render the Slate
- L33 _public member_ `FVector2f DesiredSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayPriority = 1), Category = "Style")` — Desired Draw size of the rendered material
- L37 _public prototype_ `virtual UMaterialInstanceDynamic* CreateDynamicMaterial(UObject* InOuter) const;`

#### struct `FAudioMaterialButtonStyle`  
`struct FAudioMaterialButtonStyle : public FAudioMaterialWidgetStyle`  
_L45-95_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMaterialWidgetStyle`
- desc: Represents the appearance of an Audio Material Button
- L49 _public prototype_ `FAudioMaterialButtonStyle();`
- L52 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;` — FSlateWidgetStyle
- L53 _public member_ `static const FName TypeName;`
- L54 _public function_ `virtual const FName GetTypeName() const override`
- L55 _public prototype_ `static const FAudioMaterialButtonStyle& GetDefault();`
- L56 _public prototype_ `virtual UMaterialInstanceDynamic* CreateDynamicMaterial(UObject* InOuter) const override;`
- L58 _public function_ `FAudioMaterialButtonStyle& SetMaterial(UMaterialInterface* InMaterialInterface)`
- L62 _public member_ `FLinearColor ButtonMainColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Button")` — The button's Main color value.
- L63 _public function_ `FAudioMaterialButtonStyle& SetButtonMainColor(const FLinearColor& InColor)`
- L67 _public member_ `FLinearColor ButtonMainColorTint_1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Button")` — The button color's Tint value covering one half of the gradient.
- L68 _public function_ `FAudioMaterialButtonStyle& SetButtonMainColorTint_1(const FLinearColor& InColor)`
- L72 _public member_ `FLinearColor ButtonMainColorTint_2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Button")` — The button color's Tint value covering the other half of the gradient.
- L73 _public function_ `FAudioMaterialButtonStyle& SetButtonMainColorTint_2(const FLinearColor& InColor)`
- L77 _public member_ `FLinearColor ButtonAccentColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Button")` — The button's Accent color value.
- L78 _public function_ `FAudioMaterialButtonStyle& SetButtonAccentColor(const FLinearColor& InColor)`
- L82 _public member_ `FLinearColor ButtonShadowColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Button")` — The button's Shadow color value.
- L83 _public function_ `FAudioMaterialButtonStyle& SetButtonShadowColor(const FLinearColor& InColor)`
- L87 _public member_ `FLinearColor ButtonUnpressedOutlineColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Button")` — The button's Outline color value when Unpressed.
- L88 _public function_ `FAudioMaterialButtonStyle& SetButtonUnpressedOutlineColor(const FLinearColor& InColor)`
- L92 _public member_ `FLinearColor ButtonPressedOutlineColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Button")` — The button's Outline color value when Pressed.
- L93 _public function_ `FAudioMaterialButtonStyle& SetButtonPressedOutlineColor(const FLinearColor& InColor)`

#### struct `FAudioMaterialSliderStyle`  
`struct FAudioMaterialSliderStyle : public FAudioMaterialWidgetStyle`  
_L101-146_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMaterialWidgetStyle`
- desc: Represents the appearance of an Audio Material Slider
- L105 _public prototype_ `FAudioMaterialSliderStyle();`
- L108 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;` — FSlateWidgetStyle
- L109 _public member_ `static const FName TypeName;`
- L110 _public function_ `virtual const FName GetTypeName() const override`
- L111 _public prototype_ `static const FAudioMaterialSliderStyle& GetDefault();`
- L112 _public prototype_ `virtual UMaterialInstanceDynamic* CreateDynamicMaterial(UObject* InOuter) const override;`
- L114 _public function_ `FAudioMaterialSliderStyle& SetMaterial(UMaterialInterface* InMaterialInterface)`
- L118 _public member_ `FLinearColor SliderBackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Slider")` — The slider Bar's Background color value.
- L119 _public function_ `FAudioMaterialSliderStyle& SetSliderBarBackgroundColor(const FLinearColor& InColor)`
- L123 _public member_ `FLinearColor SliderBackgroundAccentColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Slider")` — The slider Bar's Background Accent color value. Can be thought as the slider's Inner Shadow color value.
- L124 _public function_ `FAudioMaterialSliderStyle& SetSliderBarBackgroundAccentColor(const FLinearColor& InColor)`
- L128 _public member_ `FLinearColor SliderValueMainColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Slider")` — The slider's Color value representing the slider's Output Value amount.
- L129 _public function_ `FAudioMaterialSliderStyle& SetSliderBarValueMainColor(const FLinearColor& InColor)`
- L133 _public member_ `FLinearColor SliderHandleMainColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Slider")` — The slider Handle's Main color value.
- L134 _public function_ `FAudioMaterialSliderStyle& SetSliderHandleMainColor(const FLinearColor& InColor)`
- L138 _public member_ `FLinearColor SliderHandleOutlineColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Slider")` — The slider Handle's Outline color value.
- L139 _public function_ `FAudioMaterialSliderStyle& SetSliderHandleOutlineColor(const FLinearColor& InColor)`
- L143 _public member_ `FAudioTextBoxStyle TextBoxStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Label")` — The style to use for the audio text box widget.
- L144 _public function_ `FAudioMaterialSliderStyle& SetTextBoxStyle(const FAudioTextBoxStyle& InTextBoxStyle)`

#### struct `FAudioMaterialKnobStyle`  
`struct FAudioMaterialKnobStyle : public FAudioMaterialWidgetStyle`  
_L152-232_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMaterialWidgetStyle`
- desc: Represents the appearance of an Audio Material Knob
- L156 _public prototype_ `FAudioMaterialKnobStyle();`
- L159 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;` — FSlateWidgetStyle
- L160 _public member_ `static const FName TypeName;`
- L161 _public function_ `virtual const FName GetTypeName() const override`
- L162 _public prototype_ `static const FAudioMaterialKnobStyle& GetDefault();`
- L163 _public prototype_ `virtual UMaterialInstanceDynamic* CreateDynamicMaterial(UObject* InOuter) const override;`
- L165 _public function_ `FAudioMaterialKnobStyle& SetMaterial(UMaterialInterface* InMaterialInterface)`
- L169 _public member_ `FLinearColor KnobMainColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob's Main color value.
- L170 _public function_ `FAudioMaterialKnobStyle& SetKnobMainColor(const FLinearColor& InColor)`
- L174 _public member_ `FLinearColor KnobAccentColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob's Accent color value.
- L175 _public function_ `FAudioMaterialKnobStyle& SetKnobAccentColor(const FLinearColor& InColor)`
- L179 _public member_ `FLinearColor KnobShadowColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob's Shadow color value.
- L180 _public function_ `FAudioMaterialKnobStyle& SetKnobShadowColor(const FLinearColor& InColor)`
- L184 _public member_ `FLinearColor KnobSmoothBevelColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob's Smooth Bevel color value.
- L185 _public function_ `FAudioMaterialKnobStyle& SetSmoothBevelColor(const FLinearColor& InColor)`
- L189 _public member_ `FLinearColor KnobIndicatorDotColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob's Indicator Dot color value.
- L190 _public function_ `FAudioMaterialKnobStyle& SetKnobIndicatorColor(const FLinearColor& InColor)`
- L194 _public member_ `FLinearColor KnobEdgeFillColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob's Edge Fill color value.
- L195 _public function_ `FAudioMaterialKnobStyle& SetKnobEdgeFillColor(const FLinearColor& InColor)`
- L199 _public member_ `FLinearColor KnobBarColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob Bar's Color value.
- L200 _public function_ `FAudioMaterialKnobStyle& SetKnobBarColor(const FLinearColor& InColor)`
- L204 _public member_ `FLinearColor KnobBarShadowColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob Bar's Shadow color value.
- L205 _public function_ `FAudioMaterialKnobStyle& SetKnobBarShadowColor(const FLinearColor& InColor)`
- L209 _public member_ `FLinearColor KnobBarFillMinColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob Bar's Fill color value representing the Starting section of the fill.
- L210 _public function_ `FAudioMaterialKnobStyle& SetKnobBarFillMinColor(const FLinearColor& InColor)`
- L214 _public member_ `FLinearColor KnobBarFillMidColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob Bar's Fill color value representing the Middle section of the fill.
- L215 _public function_ `FAudioMaterialKnobStyle& SetKnobFillMidColor(const FLinearColor& InColor)`
- L219 _public member_ `FLinearColor KnobBarFillMaxColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob Bar's Fill color value representing the Ending section of the fill.
- L220 _public function_ `FAudioMaterialKnobStyle& SetKnobBarFillMaxColor(const FLinearColor& InColor)`
- L224 _public member_ `FLinearColor KnobBarFillTintColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Knob")` — The knob Bar Fill color's Tint value.
- L225 _public function_ `FAudioMaterialKnobStyle& SetKnobBarFillTintColor(const FLinearColor& InColor)`
- L229 _public member_ `FAudioTextBoxStyle TextBoxStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style | Label")` — The style to use for the audio text box widget.
- L230 _public function_ `void SetTextBoxStyle(const FAudioTextBoxStyle& InTextBoxStyle)`

#### struct `FAudioMaterialMeterStyle`  
`struct FAudioMaterialMeterStyle : public FAudioMaterialWidgetStyle`  
_L238-340_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMaterialWidgetStyle`
- desc: Represents the appearance of an Audio Material Meter
- L242 _public prototype_ `FAudioMaterialMeterStyle();`
- L245 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;` — FSlateWidgetStyle
- L246 _public member_ `static const FName TypeName;`
- L247 _public function_ `virtual const FName GetTypeName() const override`
- L248 _public prototype_ `static const FAudioMaterialMeterStyle& GetDefault();`
- L249 _public prototype_ `virtual UMaterialInstanceDynamic* CreateDynamicMaterial(UObject* InOuter) const override;`
- L251 _public function_ `FAudioMaterialMeterStyle& SetMaterial(UMaterialInterface* InMaterialInterface)`
- L255 _public member_ `FLinearColor MeterFillMinColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")` — The meter's Fill color value representing the Starting section of the fill.
- L256 _public function_ `FAudioMaterialMeterStyle& SetMeterFillMinColor(const FLinearColor& InColor)`
- L260 _public member_ `FLinearColor MeterFillMidColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")` — The meter's Fill color value representing the Middle section of the fill.
- L261 _public function_ `FAudioMaterialMeterStyle& SetMeterFillMidColor(const FLinearColor& InColor)`
- L265 _public member_ `FLinearColor MeterFillMaxColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")` — The meter's Fill color value representing the Ending section of the fill.
- L266 _public function_ `FAudioMaterialMeterStyle& SetMeterFillMaxColor(const FLinearColor& InColor)`
- L270 _public member_ `FLinearColor MeterFillBackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")` — The meter's Background Fill color value.
- L271 _public function_ `FAudioMaterialMeterStyle& SetMeterOffFillColor(const FLinearColor& InColor)`
- L275 _public member_ `FVector2D MeterPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — How much padding to add around the meter
- L276 _public function_ `FAudioMaterialMeterStyle& SetMeterpadding(const FVector2D InPadding)`
- L280 _public member_ `FVector2D ValueRangeDb;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The minimum and maximum value to display in dB (values are clamped in this range)
- L281 _public function_ `FAudioMaterialMeterStyle& SetValueRangeDb(const FVector2D& InValueRangeDb)`
- L285 _public member_ `bool bShowScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Whether or not to show the decibel scale alongside the meter
- L286 _public function_ `FAudioMaterialMeterStyle& SetShowScale(bool bInShowScale)`
- L290 _public member_ `bool bScaleSide;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Which side to show the scale. If vertical, true means left side, false means right side. If horizontal, true means above, false means below.
- L291 _public function_ `FAudioMaterialMeterStyle& SetScaleSide(bool bInScaleSide)`
- L295 _public member_ `float ScaleHashOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Offset for the hashes
- L296 _public function_ `FAudioMaterialMeterStyle& SetScaleHashOffset(float InScaleHashOffset)`
- L300 _public member_ `float ScaleHashWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The width of each hash mark
- L301 _public function_ `FAudioMaterialMeterStyle& SetScaleHashWidth(float InScaleHashWidth)`
- L305 _public member_ `float ScaleHashHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The height of each hash mark
- L306 _public function_ `FAudioMaterialMeterStyle& SetScaleHashHeight(float InScaleHashHeight)`
- L310 _public member_ `int32 DecibelsPerHash;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance, meta = (UIMin = "3", ClampMin = "3", UIMax = "10"))` — How wide to draw the decibel scale, if it's enabled
- L311 _public function_ `FAudioMaterialMeterStyle& SetDecibelsPerHash(float InDecibelsPerHash)`
- L315 _public member_ `FSlateFontInfo Font;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Font family and size to be used when displaying the meter scale.
- L316 _public function_ `FAudioMaterialMeterStyle& SetFont(const FSlateFontInfo& InFont)`
- L317 _public function_ `FAudioMaterialMeterStyle& SetFont(TSharedPtr<const FCompositeFont> InCompositeFont, const int32 InSize, const FName& InTypefaceFontName = NAME_None)`
- L318 _public function_ `FAudioMaterialMeterStyle& SetFont(const UObject* InFontObject, const int32 InSize, const FName& InTypefaceFontName = NAME_None)`
- L321 _public prototype_ `FAudioMaterialMeterStyle& SetFont(const FName& InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L323 _public prototype_ `FAudioMaterialMeterStyle& SetFont(const FString& InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L325 _public prototype_ `FAudioMaterialMeterStyle& SetFont(const WIDECHAR* InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L327 _public prototype_ `FAudioMaterialMeterStyle& SetFont(const ANSICHAR* InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L329 _public prototype_ `FAudioMaterialMeterStyle& SetFontName(const FName& InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L331 _public prototype_ `FAudioMaterialMeterStyle& SetFontName(const FString& InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L333 _public prototype_ `FAudioMaterialMeterStyle& SetFontName(const WIDECHAR* InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L335 _public prototype_ `FAudioMaterialMeterStyle& SetFontName(const ANSICHAR* InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L337 _public function_ `FAudioMaterialMeterStyle& SetFontSize(uint16 InSize)`
- L338 _public function_ `FAudioMaterialMeterStyle& SetTypefaceFontName(const FName& InTypefaceFontName)`

#### struct `FAudioMaterialEnvelopeStyle`  
`struct FAudioMaterialEnvelopeStyle : public FAudioMaterialWidgetStyle`  
_L346-373_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMaterialWidgetStyle`
- desc: Represents the appearance of an Audio Material Envelope
- L350 _public prototype_ `FAudioMaterialEnvelopeStyle();`
- L353 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;` — FSlateWidgetStyle
- L354 _public member_ `static const FName TypeName;`
- L355 _public function_ `virtual const FName GetTypeName() const override`
- L356 _public prototype_ `static const FAudioMaterialEnvelopeStyle& GetDefault();`
- L357 _public prototype_ `virtual UMaterialInstanceDynamic* CreateDynamicMaterial(UObject* InOuter) const override;`
- L359 _public function_ `FAudioMaterialEnvelopeStyle& SetMaterial(UMaterialInterface* InMaterialInterface)`
- L362 _public member_ `FLinearColor CurveColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`
- L363 _public function_ `FAudioMaterialEnvelopeStyle& SetEnvelopeCurveColor(const FLinearColor& InColor)`
- L366 _public member_ `FLinearColor BackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`
- L367 _public function_ `FAudioMaterialEnvelopeStyle& SetEnvelopeBackgroundColor(const FLinearColor& InColor)`
- L370 _public member_ `FLinearColor OutlineColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")`
- L371 _public function_ `FAudioMaterialEnvelopeStyle& SetEnvelopeOutlineColor(const FLinearColor& InColor)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/AudioMaterialSlider.h` (Public)


#### class `UAudioMaterialSlider`  
`class UAudioMaterialSlider : public UWidget`  
_L25-157_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, CustomFieldNotify)`
- inherits: `UWidget`
- desc: A simple widget that shows a sliding bar with a handle that allows you to control the value between 0..1. Slider is rendered by using material instead of texture. * No Children
- L31 _public prototype_ `UAudioMaterialSlider(const FObjectInitializer& ObjectInitializer);`
- L35 _public member_ `FAudioMaterialSliderStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style", meta = (DisplayName = "Style", ShowOnlyInnerProperties))` — The slider's style
- L40 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L44 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget
- L48 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual
- L53 _public prototype_ `float GetValue() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Slider")` — Gets the current value of the slider.
- L57 _public prototype_ `void SetValue(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Slider")` — Sets the current value of the slider. InValue is Clamped between 0.f - 1.f
- L61 _public prototype_ `void SetTuneSpeed(const float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Slider")` — Set the tune speed of the slider. InValue is Clamped between 0.f - 1.f
- L65 _public prototype_ `float GetTuneSpeed() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Slider")` — Get slider tune speed
- L69 _public prototype_ `void SetFineTuneSpeed(const float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Slider")` — Set the fine-tune speed of the slider. InValue is Clamped between 0.f - 1.f
- L73 _public prototype_ `float GetFineTuneSpeed() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Slider")` — Get slider fine-tune speed
- L77 _public prototype_ `void SetLocked(bool bInLocked);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Slider")` — Set the slider to be interactive or fixed
- L81 _public prototype_ `bool GetIsLocked() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Slider")` — Get whether the slider is interactive or fixed.
- L85 _public prototype_ `void SetMouseUsesStep(bool bInUsesStep);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Slider")` — Sets the slider to use steps when turning On Mouse move
- L89 _public prototype_ `bool GetMouseUsesStep() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Slider")` — Get whether the slider uses steps when turning On Mouse move
- L93 _public prototype_ `void SetStepSize(float InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Material Slider")` — Sets the amount to adjust the value when using steps
- L97 _public prototype_ `float GetStepSize() const;` — `UFUNCTION(BlueprintPure, Category = "Audio Widgets| Audio Material Slider")` — Get Step Size
- L103 _public member_ `FOnSliderFloatValueChangedEvent OnValueChanged;` — `UPROPERTY(BlueprintAssignable, FieldNotify, Category = "Widget Event")` — Called when the value is changed by slider.
- L107 _public member_ `FOnSliderMouseCaptureBeginEvent OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when mouse capture begins.
- L111 _public member_ `FOnSliderMouseCaptureEndEvent OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when mouse capture ends (mouse release or any other capture loss).
- L116 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget
- L119 _protected prototype_ `void HandleOnValueChanged(float InValue);`
- L120 _protected prototype_ `void HandleOnMouseCaptureBegin();`
- L121 _protected prototype_ `void HandleOnMouseCaptureEnd();`
- L127 _private member_ `float Value = 1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, FieldNotify, Setter = SetValue, Getter = GetValue, Category = "Appearance", meta = (UIMin = "0", UIMax = "1", AllowPrivateAccess))` — Default Value of the slider
- L131 _private member_ `TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Horizontal;` — `UPROPERTY(EditAnywhere, Category = "Appearance")` — Orientation of the slider
- L135 _private member_ `float TuneSpeed;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetTuneSpeed, BlueprintGetter = GetTuneSpeed, Category = Appearance, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — The tune speed of the slider On Mouse move
- L139 _private member_ `float FineTuneSpeed;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetFineTuneSpeed, BlueprintGetter = GetFineTuneSpeed, Category = Appearance, AdvancedDisplay, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — The tune speed of the slider when fine-tuning the slider On Mouse move && Left-Shift pressed
- L143 _private member_ `bool bLocked;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetLocked, BlueprintGetter = GetIsLocked, Category = Appearance, AdvancedDisplay)` — Whether the slider is interactive or fixed.
- L147 _private member_ `bool bMouseUsesStep;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetMouseUsesStep, BlueprintGetter = GetMouseUsesStep, Category = Appearance, AdvancedDisplay)` — Sets new value if mouse position is greater/less than half the step size.
- L151 _private member_ `float StepSize;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetStepSize, BlueprintGetter = GetStepSize, Category = Appearance, AdvancedDisplay, meta = (UIMin = "0", UIMax = "1"))` — The amount to adjust the value by, when using steps
- L156 _private member_ `TSharedPtr<SAudioMaterialSlider> Slider;` — Native Slate Widget

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSliderMouseCaptureBeginEvent);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSliderMouseCaptureBeginEvent);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSliderMouseCaptureEndEvent);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSliderMouseCaptureEndEvent);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderFloatValueChangedEvent, float, Value);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderFloatValueChangedEvent, float, Value);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/AudioMaterialStyleContainers.h` (Public)


#### class `UAudioMaterialKnobWidgetStyle`  
`class UAudioMaterialKnobWidgetStyle : public USlateWidgetStyleContainerBase`  
_L11-25_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `USlateWidgetStyleContainerBase`
- L19 _public member_ `FAudioMaterialKnobStyle KnobStyle;` — `UPROPERTY(Category = Appearance, EditAnywhere, meta = (ShowOnlyInnerProperties))` — The actual data describing the AudioMaterialKnob appearance.
- L21 _public function_ `virtual const struct FSlateWidgetStyle* const GetStyle() const override`

#### class `UAudioMaterialMeterWidgetStyle`  
`class UAudioMaterialMeterWidgetStyle : public USlateWidgetStyleContainerBase`  
_L28-42_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `USlateWidgetStyleContainerBase`
- L36 _public member_ `FAudioMaterialMeterStyle MeterStyle;` — `UPROPERTY(Category = Appearance, EditAnywhere, meta = (ShowOnlyInnerProperties))` — The actual data describing the AudioMaterialMeter appearance.
- L38 _public function_ `virtual const struct FSlateWidgetStyle* const GetStyle() const override`

#### class `UAudioMaterialButtonWidgetStyle`  
`class UAudioMaterialButtonWidgetStyle : public USlateWidgetStyleContainerBase`  
_L45-59_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `USlateWidgetStyleContainerBase`
- L53 _public member_ `FAudioMaterialButtonStyle ButtonStyle;` — `UPROPERTY(Category = Appearance, EditAnywhere, meta = (ShowOnlyInnerProperties))` — The actual data describing the AudioMaterialButton appearance.
- L55 _public function_ `virtual const struct FSlateWidgetStyle* const GetStyle() const override`

#### class `UAudioMaterialSliderWidgetStyle`  
`class UAudioMaterialSliderWidgetStyle : public USlateWidgetStyleContainerBase`  
_L62-76_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `USlateWidgetStyleContainerBase`
- L70 _public member_ `FAudioMaterialSliderStyle SliderStyle;` — `UPROPERTY(Category = Appearance, EditAnywhere, meta = (ShowOnlyInnerProperties))` — The actual data describing the AudioMaterialSlider appearance.
- L72 _public function_ `virtual const struct FSlateWidgetStyle* const GetStyle() const override`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/SAudioMaterialButton.h` (Public)


#### class `SAudioMaterialButton`  
`class SAudioMaterialButton : public SLeafWidget`  
_L21-101_
- inherits: `SLeafWidget`
- desc: A simple slate that renders button in single material and modifies the material on pressed state change.
- L24 _public function_ `SLATE_BEGIN_ARGS(SAudioMaterialButton) : _AudioMaterialButtonStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioMaterialButtonStyle>("AudioMaterialButton.Style"))`
- L29 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UObject>, Owner) SLATE_ATTRIBUTE(bool, bIsPressedAttribute) SLATE_STYLE_ARGUMENT(FAudioMaterialButtonStyle, AudioMaterialButtonStyle) SLATE_EVENT(FOnBooleanValueChanged, OnBooleanValueChanged) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The owner object
- L52 _public prototype_ `void SetPressedState(bool InPressedState);` — Press the button
- L55 _public prototype_ `UMaterialInstanceDynamic* ApplyNewMaterial();` — Apply new material to be used to render the Slate.
- L58 _public prototype_ `void SetDesiredSizeOverride(const FVector2D InSize);` — Set desired size of the Slate
- L62 _public member_ `FOnBooleanValueChanged OnBooleanValueChanged;`
- L65 _public member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L68 _public member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when mouse capture ends.
- L73 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget overrides
- L74 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L75 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L76 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L77 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L82 _private prototype_ `void CommitNewState(bool InPressedState);` — Commits new state
- L87 _private member_ `TWeakObjectPtr<UObject> Owner;` — Holds the owner of the Slate
- L90 _private member_ `mutable TWeakObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;` — Holds the Modifiable Material that represent the Button
- L93 _private member_ `const FAudioMaterialButtonStyle* AudioMaterialButtonStyle = nullptr;` — Holds the style for the Slate
- L96 _private member_ `TAttribute<bool> bIsPressedAttribute = false;` — Current pressed state of this button
- L99 _private member_ `TAttribute<TOptional<FVector2D>> DesiredSizeOverride;` — Holds the optional desired size for the Slate

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/SAudioMaterialEnvelope.h` (Public)


#### class `SAudioMaterialEnvelope`  
`class SAudioMaterialEnvelope : public SLeafWidget`  
_L18-61_
- inherits: `SLeafWidget`
- desc: A simple slate that renders envelope curve in a single material and modifies the material on value change.
- L21 _public function_ `SLATE_BEGIN_ARGS(SAudioMaterialEnvelope)`
- L25 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UObject>, Owner) SLATE_ARGUMENT(FAudioMaterialEnvelopeSettings*, EnvelopeSettings) SLATE_STYLE_ARGUMENT(FAudioMaterialEnvelopeStyle, AudioMaterialEnvelopeStyle) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The owner object
- L41 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget overrides
- L42 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L45 _public prototype_ `UMaterialInstanceDynamic* ApplyNewMaterial();` — Apply new material to be used to render the Slate.
- L50 _private member_ `TWeakObjectPtr<UObject> Owner;` — Holds the owner of the Slate
- L53 _private member_ `const FAudioMaterialEnvelopeStyle* AudioMaterialEnvelopeStyle = nullptr;` — Holds the style for the Slate
- L56 _private member_ `mutable TWeakObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;` — Holds the Modifiable Material that represent the Envelope
- L59 _private member_ `const FAudioMaterialEnvelopeSettings* EnvelopeSettings = nullptr;` — Holds the current Envelope settings

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/SAudioMaterialKnob.h` (Public)


#### class `SAudioMaterialKnob`  
`class SAudioMaterialKnob : public SLeafWidget`  
_L20-200_
- inherits: `SLeafWidget`
- desc: A simple slate that renders a knob in single material and modifies the material on value change.
- L23 _public function_ `SLATE_BEGIN_ARGS(SAudioMaterialKnob) : _TuneSpeed(0.2f) , _FineTuneSpeed(0.05f) , _IsFocusable(true) , _Locked(false) , _MouseUsesStep(false) , _StepSize(0.01f) , _AudioMaterialKnobStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioMaterialKnobStyle>("AudioMaterialKnob.Style"))`
- L34 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UObject>, Owner) SLATE_ATTRIBUTE(float, Value) SLATE_ATTRIBUTE(float, TuneSpeed) SLATE_ATTRIBUTE(float, FineTuneSpeed) SLATE_ATTRIBUTE(bool, IsFocusable) SLATE_ATTRIBUTE(bool, Locked) SLATE_ATTRIBUTE(bool, MouseUsesStep) SLATE_ATTRIBUTE(float, StepSize) SLATE_STYLE_ARGUMENT(FAudioMaterialKnobStyle, AudioMaterialKnobStyle) SLATE_EVENT(FOnFloatValueChanged, OnFloatValueChanged) SLATE_EVENT(FOnFloatValueChanged, OnValueCommitted) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_END_ARGS()` — The owner object
- L78 _public prototype_ `void SetValue(const TAttribute<float>& InValueAttribute);` — Set the Value attribute
- L81 _public prototype_ `void SetTuneSpeed(const float InMouseSpeed);` — Set the TuneSpeed attribute
- L84 _public prototype_ `void SetFineTuneSpeed(const float InMouseFineTuneSpeed);` — Set the FineTuneSpeed attribute
- L87 _public prototype_ `void SetLocked(const bool InLocked);` — Set the bLocked attribute
- L90 _public prototype_ `void SetMouseUsesStep(const bool InUsesStep);` — See the bMouseUsesStep attribute
- L93 _public prototype_ `void SetStepSize(const float InStepSize);` — Set the StepSize attribute
- L96 _public prototype_ `bool IsLocked() const;` — @return Is the knob interaction locked or not?
- L99 _public prototype_ `UMaterialInstanceDynamic* ApplyNewMaterial();` — Apply new material to be used to render the Slate.
- L101 _public prototype_ `const float GetOutputValue(const float InSliderValue);`
- L102 _public prototype_ `const float GetSliderValue(const float OutputValue);`
- L105 _public prototype_ `void SetOutputRange(const FVector2D Range);` — Set the output range of the Knob
- L108 _public prototype_ `void SetDesiredSizeOverride(const FVector2D Size);` — Set desired size of the Slate
- L113 _public member_ `FOnFloatValueChanged OnValueChanged;` — Holds a delegate that is executed when the knob's value changes.
- L116 _public member_ `FOnFloatValueChanged OnValueCommitted;` — Holds a delegate that is executed when the knob's value is committed (mouse capture ends).
- L119 _public member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L122 _public member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when mouse capture ends.
- L127 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget
- L128 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L129 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L130 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L131 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L132 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L133 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L134 _protected prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L135 _protected prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L136 _protected prototype_ `virtual bool IsInteractable() const override;`
- L142 _protected member_ `FVector2D OutputRange = FVector2D(0.0f, 1.0f);` — Range for output
- L143 _protected member_ `const FVector2D NormalizedLinearSliderRange = FVector2D(0.0f, 1.0f);`
- L148 _private member_ `TAttribute<TOptional<FVector2D>> DesiredSizeOverride;` — Holds the optional style for the Slate
- L151 _private prototype_ `void CommitValue(float NewValue);` — Commits new value
- L156 _private member_ `TWeakObjectPtr<UObject> Owner;` — Holds the owner of the Slate
- L159 _private member_ `const FAudioMaterialKnobStyle* AudioMaterialKnobStyle = nullptr;` — Holds the style for the Slate
- L162 _private member_ `mutable TWeakObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;` — Holds the Modifiable Material that represent the Knob
- L165 _private member_ `TAttribute<float> ValueAttribute = 1.0;` — Holds the knobs current Value
- L168 _private member_ `TAttribute<float> TuneSpeed;` — Holds the amount to adjust the knob On Mouse move
- L171 _private member_ `TAttribute<float> FineTuneSpeed;` — Holds the amount to adjust the knob On Mouse move & FineTuning
- L174 _private member_ `TAttribute<bool> bIsFocusable;` — Holds a flag indicating whether knob will be keyboard focusable.
- L177 _private member_ `TAttribute<bool> bLocked;` — Holds a flag indicating whether the knob is locked.
- L180 _private member_ `TAttribute<bool> bMouseUsesStep;` — Holds a flag indicating whether the knob uses steps when roating on Mouse move.
- L183 _private member_ `TAttribute<float> StepSize;` — Holds the amount to adjust the value when steps are used
- L186 _private member_ `FVector2D MouseDownPosition;` — The position of the mouse when it pushed down and started rotating the knob
- L189 _private member_ `float MouseDownValue = 0.f;` — the value when the mouse was pushed down
- L192 _private member_ `EMouseCursor::Type CachedCursor;` — Holds the initial cursor in case a custom cursor has been specified, so we can restore it after dragging the slider
- L195 _private member_ `int32 PixelDelta = 50;` — the max pixels to go to min or max value (clamped to 0 or 1) in one drag period
- L198 _private member_ `bool bIsFineTune;` — Whether or not we're in fine-tune mode

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/SAudioMaterialLabeledKnob.h` (Public)


#### class `SAudioMaterialLabeledKnob`  
`class SAudioMaterialLabeledKnob : public SAudioInputWidget`  
_L23-132_
- inherits: `SAudioInputWidget`
- desc: Wraps SAudioMaterialKnob and adds Label text that will show a value text.
- L26 _public function_ `SLATE_BEGIN_ARGS(SAudioMaterialLabeledKnob)`
- L30 _public prototype_ `SLATE_ATTRIBUTE(float, Value) SLATE_ARGUMENT(TWeakObjectPtr<UObject>, Owner) SLATE_ARGUMENT(EAudioUnitsValueType, AudioUnitsValueType) SLATE_ARGUMENT(bool, bUseLinearOutput) SLATE_STYLE_ARGUMENT(FAudioMaterialKnobStyle, Style) SLATE_EVENT(FOnFloatValueChanged, OnValueChanged) SLATE_EVENT(FOnFloatValueChanged, OnValueTextCommitted) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — A value representing the normalized linear (0 - 1) knobs value position.
- L62 _public prototype_ `void SetValue(float InValueAttribute);` — Set the Value attribute
- L65 _public prototype_ `virtual const float GetOutputValue(const float InSliderValue) override;` — SAudioInputWidget
- L66 _public prototype_ `virtual const float GetSliderValue(const float OutputValue) override;`
- L67 _public prototype_ `virtual const float GetOutputValueForText(const float InSliderValue);`
- L68 _public prototype_ `virtual const float GetSliderValueForText(const float OutputValue);`
- L73 _public prototype_ `virtual void SetSliderValue(float InSliderValue) override;` — Set the knob's linear (0-1 normalized) value.
- L74 _public prototype_ `virtual void SetOutputRange(const FVector2D InRange) override;`
- L75 _public prototype_ `virtual void SetDesiredSizeOverride(const FVector2D Size) override;`
- L76 _public prototype_ `virtual void SetLabelBackgroundColor(FSlateColor InColor) override;`
- L77 _public prototype_ `virtual void SetUnitsText(const FText Units) override;`
- L78 _public prototype_ `virtual void SetUnitsTextReadOnly(const bool bIsReadOnly) override;`
- L79 _public prototype_ `virtual void SetShowUnitsText(const bool bShowUnitsText) override;`
- L85 _public member_ `FOnFloatValueChanged OnValueChanged;` — Holds a delegate that is executed when the knob's value changes.
- L88 _public member_ `FOnFloatValueChanged OnValueTextCommitted;` — Holds a delegate that is executed when the value is committed from label's text field
- L91 _public member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L94 _public member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when the mouse is let up and a capture ends.
- L99 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget
- L104 _private member_ `TAttribute<TOptional<FVector2D>> DesiredSizeOverride;`
- L107 _private member_ `TWeakObjectPtr<UObject> Owner;` — Holds the owner of the Slate
- L110 _private member_ `const FAudioMaterialKnobStyle* Style = nullptr;` — Holds the style for the Slate
- L113 _private member_ `TAttribute<float> ValueAttribute = 1.0f;` — Holds the knobs current Value
- L116 _private member_ `TAttribute<EAudioUnitsValueType> AudioUnitsValueType;` — Holds the knob's unit value type
- L119 _private member_ `TSharedPtr<SAudioMaterialKnob> Knob;` — Widget components
- L120 _private member_ `TSharedPtr<SAudioTextBox> Label;`
- L123 _private member_ `TSharedPtr<SVerticalBox> VerticalLayotWidget;` — verticalBox that holds the widgets
- L126 _private member_ `FVector2D OutputRange = FVector2D(0.0f, 1.0f);` — Range for output
- L127 _private member_ `const FVector2D NormalizedLinearSliderRange = FVector2D(0.0f, 1.0f);`
- L130 _private member_ `TSharedPtr<FAudioUnitProcessor> AudioUnitProcessor;` — Hold the ref to the current Unit processor

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/SAudioMaterialLabeledSlider.h` (Public)


#### class `SAudioMaterialLabeledSlider`  
`class SAudioMaterialLabeledSlider : public SAudioInputWidget`  
_L23-131_
- inherits: `SAudioInputWidget`
- desc: Wraps SAudioMaterialSlider and adds Label text that will show a value text.
- L27 _public function_ `SLATE_BEGIN_ARGS(SAudioMaterialLabeledSlider) : _Style(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioMaterialSliderStyle>("AudioMaterialSlider.Style"))`
- L32 _public prototype_ `SLATE_STYLE_ARGUMENT(FAudioMaterialSliderStyle, Style) SLATE_ARGUMENT(TWeakObjectPtr<UObject>, Owner) SLATE_ATTRIBUTE(float, SliderValue) SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ARGUMENT(EAudioUnitsValueType, AudioUnitsValueType) SLATE_ARGUMENT(bool , bUseLinearOutput) SLATE_ATTRIBUTE(TOptional<FVector2D>, DesiredSizeOverride) SLATE_EVENT(FOnFloatValueChanged, OnValueChanged) SLATE_EVENT(FOnFloatValueChanged, OnValueCommitted) SLATE_END_ARGS()` — The style used to draw the slider.
- L64 _public member_ `FOnFloatValueChanged OnValueCommitted;` — Holds a delegate that is executed when the slider's value is committed (mouse capture ends).
- L69 _public prototype_ `virtual void Construct(const SAudioMaterialLabeledSlider::FArguments& InArgs);` — Construct the widget.
- L70 _public prototype_ `virtual const float GetOutputValue(const float InSliderValue) override;`
- L71 _public prototype_ `virtual const float GetSliderValue(const float OutputValue) override;`
- L72 _public prototype_ `virtual const float GetOutputValueForText(const float InSliderValue);`
- L73 _public prototype_ `virtual const float GetSliderValueForText(const float OutputValue);`
- L79 _public prototype_ `virtual void SetSliderValue(float InSliderValue) override;` — Set the slider's linear (0-1 normalized) value.
- L80 _public prototype_ `FVector2D ComputeDesiredSize(float) const;`
- L81 _public prototype_ `virtual void SetDesiredSizeOverride(const FVector2D DesiredSize) override;`
- L83 _public prototype_ `void SetOrientation(EOrientation InOrientation);`
- L84 _public prototype_ `virtual void SetOutputRange(const FVector2D InRange) override;`
- L87 _public prototype_ `void SetLabelBackgroundColor(FSlateColor InColor) override;` — Text label functions
- L88 _public prototype_ `void SetUnitsText(const FText Units) override;`
- L89 _public prototype_ `void SetUnitsTextReadOnly(const bool bIsReadOnly) override;`
- L90 _public prototype_ `void SetValueTextReadOnly(const bool bIsReadOnly);`
- L91 _public prototype_ `void SetShowLabelOnlyOnHover(const bool bShowLabelOnlyOnHover);`
- L92 _public prototype_ `void SetShowUnitsText(const bool bShowUnitsText) override;`
- L98 _private member_ `const FAudioMaterialSliderStyle* Style;` — Holds the style for the Slider
- L101 _private member_ `TAttribute<float> SliderValueAttribute;` — Holds the slider's current linear value
- L104 _private member_ `TAttribute<EOrientation> Orientation;` — Holds the slider's orientation
- L107 _private member_ `TAttribute<EAudioUnitsValueType> AudioUnitsValueType;` — Holds the slider's unit value type
- L110 _private member_ `TAttribute<TOptional<FVector2D>> DesiredSizeOverride;` — Optional override for desired size
- L113 _private member_ `TAttribute<FSlateColor> LabelBackgroundColor;` — Label text bg color
- L116 _private member_ `TSharedPtr<SAudioMaterialSlider> Slider;` — Widget components
- L117 _private member_ `TSharedPtr<SAudioTextBox> Label;`
- L120 _private member_ `FVector2D OutputRange = FVector2D(0.0f, 1.0f);` — Range for output
- L123 _private member_ `TSharedPtr<SWidgetSwitcher> LayoutWidgetSwitcher;` — Switches between the vertical and horizontal views
- L126 _private member_ `TSharedPtr<FAudioUnitProcessor> AudioUnitProcessor;` — Hold the ref to the current Unit processor
- L130 _private prototype_ `TSharedRef<SWidgetSwitcher> CreateWidgetLayout();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/SAudioMaterialMeter.h` (Public)


#### class `SAudioMaterialMeter`  
`class SAudioMaterialMeter : public SAudioMeterBase`  
_L22-88_
- inherits: `SAudioMeterBase`
- desc: A simple slate that renders the meter in single material and modifies the material on value change.
- L25 _public function_ `SLATE_BEGIN_ARGS(SAudioMaterialMeter) : _Orientation(EOrientation::Orient_Vertical) , _AudioMaterialMeterStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioMaterialMeterStyle>("AudioMaterialMeter.Style"))`
- L31 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ARGUMENT(TWeakObjectPtr<UObject>, Owner) SLATE_STYLE_ARGUMENT(FAudioMaterialMeterStyle, AudioMaterialMeterStyle) SLATE_ATTRIBUTE(TArray<FMeterChannelInfo>, MeterChannelInfo) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The meter's orientation.
- L50 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget
- L51 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L55 _public prototype_ `void SetOrientation(EOrientation InOrientation);` — Set the Orientation attribute
- L58 _public prototype_ `TArray<TWeakObjectPtr<UMaterialInstanceDynamic>> ApplyNewMaterial();` — Apply new material to be used to render the Meter.
- L61 _public prototype_ `void SetMeterChannelInfo(const TAttribute<TArray<FMeterChannelInfo>>& InMeterChannelInfo) override;` — Set the MeterChannelInfo attribute
- L64 _public prototype_ `TArray<FMeterChannelInfo> GetMeterChannelInfo() const override;` — Get the MeterChannelInfo attribute
- L69 _private prototype_ `float GetScaleWidth() const;` — Returns the scale width based off font size and hash width
- L74 _private member_ `TWeakObjectPtr<UObject> Owner;` — Holds the owner of the Slate
- L77 _private member_ `const FAudioMaterialMeterStyle* Style = nullptr;` — Holds the style for the Slate
- L80 _private member_ `mutable TArray<TWeakObjectPtr<UMaterialInstanceDynamic>> DynamicMaterials;` — Holds the Modifiable Materials that represent the Meters
- L83 _private member_ `EOrientation Orientation;` — Holds the Meter's orientation.
- L86 _private member_ `TAttribute<TArray<FMeterChannelInfo>> MeterChannelInfoAttribute;` — Holds the MeterChannelInfoAttributes

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMaterialSlate/SAudioMaterialSlider.h` (Public)


#### class `SAudioMaterialSlider`  
`class SAudioMaterialSlider : public SLeafWidget`  
_L19-197_
- inherits: `SLeafWidget`
- desc: A simple slate that renders slider in single material and modifies the material on value change.
- L22 _public function_ `SLATE_BEGIN_ARGS(SAudioMaterialSlider) : _TuneSpeed(0.2f) , _FineTuneSpeed(0.05f) , _IsFocusable(true) , _Locked(false) , _MouseUsesStep(false) , _StepSize(0.01f)`
- L32 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UObject>, Owner) SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ATTRIBUTE(float, TuneSpeed) SLATE_ATTRIBUTE(float, FineTuneSpeed) SLATE_ATTRIBUTE(bool, IsFocusable) SLATE_ATTRIBUTE(bool, Locked) SLATE_ATTRIBUTE(bool, MouseUsesStep) SLATE_ATTRIBUTE(float, StepSize) SLATE_STYLE_ARGUMENT(FAudioMaterialSliderStyle, AudioMaterialSliderStyle) SLATE_ATTRIBUTE(float, ValueAttribute) SLATE_EVENT(FOnFloatValueChanged, OnValueChanged) SLATE_EVENT(FOnFloatValueChanged, OnValueCommitted) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd)` — The owner object
- L81 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget overrides
- L82 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L85 _public prototype_ `void SetValue(TAttribute<float> InValueAttribute);` — Set the Value attribute
- L88 _public prototype_ `void SetTuneSpeed(const float InMouseTuneSpeed);` — Set the TuneSpeed attribute
- L91 _public prototype_ `void SetFineTuneSpeed(const float InMouseFineTuneSpeed);` — Set the FineTuneSpeed attribute
- L94 _public prototype_ `void SetMouseUsesStep(const bool InUsesStep);` — See the bMouseUsesStep attribute
- L97 _public prototype_ `void SetStepSize(const float InStepSize);` — Set the StepSize attribute
- L100 _public prototype_ `void SetLocked(const bool bInLocked);` — Set the bLocked attribute
- L103 _public prototype_ `bool IsLocked() const;` — @return Is the knob interaction locked or not?
- L106 _public prototype_ `void ApplyNewMaterial();` — Apply new material to be used to render the Slate.
- L109 _public prototype_ `void SetOrientation(EOrientation InOrientation);` — Set the orientation of the slider
- L112 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget
- L113 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L114 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L115 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L116 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L117 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L118 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L119 _public prototype_ `virtual bool IsInteractable() const override;`
- L125 _public member_ `FOnFloatValueChanged OnValueChanged;` — Holds a delegate that is executed when the slider's value changed.
- L128 _public member_ `FOnFloatValueChanged OnValueCommitted;` — Holds a delegate that is executed when the slider's value is committed (mouse capture ends).
- L131 _public member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L134 _public member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when mouse capture ends.
- L143 _private prototype_ `void CommitValue(float NewValue);` — Commits the specified slider value. @param NewValue The value to commit.
- L148 _private member_ `TAttribute<TOptional<FVector2D>> DesiredSizeOverride;` — Optional override for desired size
- L151 _private member_ `EOrientation Orientation;` — Holds the slider's orientation
- L154 _private member_ `TWeakObjectPtr<UObject> Owner;` — Holds the owner of the Slate
- L157 _private member_ `const FAudioMaterialSliderStyle* AudioMaterialSliderStyle = nullptr;` — Holds the style for the Slate
- L160 _private member_ `mutable TWeakObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;` — Holds the Modifiable Material that represent the slider
- L163 _private member_ `TAttribute<float> ValueAttribute = 0.f;` — Holds the current value
- L166 _private member_ `TAttribute<float> TuneSpeed;` — Holds the amount to adjust the slider On Mouse move
- L169 _private member_ `TAttribute<float> FineTuneSpeed;` — Holds the amount to adjust the slider On Mouse move & FineTuning
- L172 _private member_ `TAttribute<bool> bIsFocusable;` — Holds a flag indicating whether slider will be keyboard focusable.
- L175 _private member_ `TAttribute<bool> bLocked;` — Holds a flag indicating whether the slider is locked.
- L178 _private member_ `TAttribute<bool> bMouseUsesStep;` — Holds a flag indicating whether the slider uses steps when roating on Mouse move.
- L181 _private member_ `TAttribute<float> StepSize;` — Holds the amount to adjust the value when steps are used
- L184 _private member_ `int32 PixelDelta = 50;` — the max pixels to go to min or max value (clamped to 0 or 1) in one drag period
- L187 _private member_ `bool bIsFineTune = false;` — Whether or not we're in fine-tune mode
- L190 _private member_ `FVector2D MouseDownStartPosition;` — The position of the mouse when it pushed down and started moving the slider
- L193 _private member_ `float MouseDownValue = 0.f;` — the value when the mouse was pushed down
- L196 _private member_ `EMouseCursor::Type CachedCursor = EMouseCursor::None;` — Holds the initial cursor in case a custom cursor has been specified, so we can restore it after dragging the slider

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMeter.h` (Public)


#### struct `FAudioMeterDefaultColorStyle`  
`struct FAudioMeterDefaultColorStyle : public FAudioMeterDefaultColorWidgetStyle`  
_L37-46_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMeterDefaultColorWidgetStyle`
- L41 _public prototype_ `static const FAudioMeterDefaultColorStyle& GetDefault();`
- L43 _public function_ `virtual const FName GetTypeName() const override`
- L45 _public member_ `inline static const FName TypeName = "FA`

#### class `UAudioMeter`  
`class UAudioMeter: public UWidget`  
_L59-172_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: An audio meter widget. Supports displaying a slower moving peak-hold value as well as the current meter value. A clipping value is also displayed which shows a customizable color to indicate clipping. Internal values are stored and interacted with as linear volume values.
- L65 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<FMeterChannelInfo>, FGetMeterChannelInfo);`
- L69 _public member_ `TArray<FMeterChannelInfo> MeterChannelInfo;` — `UPROPERTY(EditAnywhere, Category = MeterValues)` — The current meter value to display.
- L73 _public member_ `FGetMeterChannelInfo MeterChannelInfoDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the meter
- L79 _public member_ `FAudioMeterStyle WidgetStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=( DisplayName="Style" ))` — The audio meter style
- L83 _public member_ `TEnumAsByte<EOrientation> Orientation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)` — The slider's orientation.
- L87 _public member_ `FLinearColor BackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The color to draw the background.
- L91 _public member_ `FLinearColor MeterBackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Appearance)` — The color to draw the meter background.
- L95 _public member_ `FLinearColor MeterValueColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The color to draw the meter value.
- L99 _public member_ `FLinearColor MeterPeakColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The color to draw the meter peak value.
- L103 _public member_ `FLinearColor MeterClippingColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The color to draw the meter clipping value.
- L107 _public member_ `FLinearColor MeterScaleColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The color to draw the meter scale hashes.
- L111 _public member_ `FLinearColor MeterScaleLabelColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The color to draw the meter scale label.
- L117 _public prototype_ `TArray<FMeterChannelInfo> GetMeterChannelInfo() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Gets the current linear value of the meter.
- L121 _public prototype_ `void SetMeterChannelInfo(const TArray<FMeterChannelInfo>& InMeterChannelInfo);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Sets the current meter values.
- L125 _public prototype_ `void SetBackgroundColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Sets the background color
- L129 _public prototype_ `void SetMeterBackgroundColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Sets the meter background color
- L133 _public prototype_ `void SetMeterValueColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Sets the meter value color
- L137 _public prototype_ `void SetMeterPeakColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Sets the meter peak color
- L141 _public prototype_ `void SetMeterClippingColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Sets the meter clipping color
- L145 _public prototype_ `void SetMeterScaleColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Sets the meter scale color
- L149 _public prototype_ `void SetMeterScaleLabelColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Meter")` — Sets the meter scale color
- L152 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L156 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L160 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L165 _protected member_ `TSharedPtr<SAudioMeter> MyAudioMeter;` — Native Slate Widget
- L168 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L171 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(TArray<FMeterChannelInfo>, MeterChannelInfo);`

#### class `AudioWidgets::FAudioMeter`  
`class FAudioMeter : public IAudioAnalyzerRackUnit`  
_L176-243_
- inherits: `IAudioAnalyzerRackUnit`
- L179 _public member_ `static const FAudioAnalyzerRackUnitTypeInfo RackUnitTypeInfo;`
- L182 _public prototype_ `FAudioMeter(int32 InNumChannels, UWorld& InWorld, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr);` — `UE_DEPRECATED(5.4, "Use the FAudioMeter constructor that uses Audio::FDeviceId.")`
- L185 _public prototype_ `FAudioMeter(const int32 InNumChannels, const Audio::FDeviceId InAudioDeviceId, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr, const FAudioMeterDefaultColorStyle* AudioMeterColorStyle = nullptr);` — /  OPTIONAL PARAM InExternalAudioBus: An audio meter can be constructed from this audio bus.
- L188 _public prototype_ `FAudioMeter(const int32 InNumChannels, const Audio::FDeviceId InAudioDeviceId, const FAudioMaterialMeterStyle& AudioMaterialMeterStyle, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr);` — /  Constructs the Meter using AudioMaterialMeter with the given style. OPTIONAL PARAM InExternalAudioBus: An audio meter can be constructed from this audio bus.
- L190 _public prototype_ `~FAudioMeter();`
- L192 _public prototype_ `UAudioBus* GetAudioBus() const;`
- L194 _public prototype_ `TSharedRef<SAudioMeter> GetWidget() const;`
- L197 _public function_ `template<class T> TSharedRef<T> GetWidget() const`
- L203 _public prototype_ `void Init(int32 InNumChannels, UWorld& InWorld, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr);` — `UE_DEPRECATED(5.4, "Use the Init method that uses Audio::FDeviceId.")`
- L205 _public prototype_ `void Init(const int32 InNumChannels, const Audio::FDeviceId InAudioDeviceId, TObjectPtr<UAudioBus> InExternalAudioBus);`
- L208 _public function_ `virtual void SetAudioBusInfo(const FAudioBusInfo& AudioBusInfo) override`
- L213 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args) const override;`
- L217 _protected prototype_ `void OnMeterOutput(UMeterAnalyzer* InMeterAnalyzer, int32 ChannelIndex, const FMeterResults& InMeterResults);`
- L220 _private prototype_ `static TSharedRef<IAudioAnalyzerRackUnit> MakeRackUnit(const FAudioAnalyzerRackUnitConstructParams& Params);`
- L222 _private prototype_ `void Teardown();`
- L225 _private member_ `TStrongObjectPtr<UMeterAnalyzer> Analyzer;` — Metasound analyzer object.
- L228 _private member_ `TStrongObjectPtr<UAudioBus> AudioBus;` — The audio bus used for analysis.
- L231 _private member_ `TArray<FMeterChannelInfo> ChannelInfo;` — Cached channel info for the meter.
- L234 _private member_ `FDelegateHandle ResultsDelegateHandle;` — Handle for results delegate for MetaSound meter analyzer.
- L237 _private member_ `TStrongObjectPtr<UMeterSettings> Settings;` — Meter settings.
- L240 _private member_ `TSharedPtr<SAudioMeterBase> Widget;` — MetaSound Output Meter widget
- L242 _private member_ `bool bUseExternalAudioBus = false;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L65 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<FMeterChannelInfo>, FGetMeterChannelInfo);`
- L174 _namespace_ `namespace AudioWidgets`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMeterStyle.h` (Public)


#### struct `FAudioMeterStyle`  
`struct FAudioMeterStyle : public FAudioMeterWidgetStyle`  
_L15-43_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMeterWidgetStyle`
- desc: Represents the appearance of an SAudioMeter
- L19 _public prototype_ `static const FAudioMeterStyle& GetDefault();`
- L21 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;`
- L23 _public function_ `virtual const FName GetTypeName() const override`
- L25 _public member_ `inline static const FName TypeName = "FA`
- L28 _public prototype_ `FAudioMeterStyle& SetFont(const FName& InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L30 _public prototype_ `FAudioMeterStyle& SetFont(const FString& InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L32 _public prototype_ `FAudioMeterStyle& SetFont(const WIDECHAR* InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L34 _public prototype_ `FAudioMeterStyle& SetFont(const ANSICHAR* InFontName, uint16 InSize);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L36 _public prototype_ `FAudioMeterStyle& SetFontName(const FName& InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L38 _public prototype_ `FAudioMeterStyle& SetFontName(const FString& InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L40 _public prototype_ `FAudioMeterStyle& SetFontName(const WIDECHAR* InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`
- L42 _public prototype_ `FAudioMeterStyle& SetFontName(const ANSICHAR* InFontName);` — `UE_DEPRECATED(5.6, "Use SetFont using FSlateFontInfo instead. FSlateFontInfo's constructors using a FontName are deprecated.")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioMeterTypes.h` (Public)


#### struct `FMeterChannelInfo`  
`struct FMeterChannelInfo : public FAudioMeterChannelInfo`  
_L10-13_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAudioMeterChannelInfo`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioOscilloscope.h` (Public)


#### class `AudioWidgets::FAudioOscilloscope`  
`class FAudioOscilloscope : public IAudioAnalyzerRackUnit`  
_L22-70_
- inherits: `IAudioAnalyzerRackUnit`
- L25 _public member_ `static const FAudioAnalyzerRackUnitTypeInfo RackUnitTypeInfo;`
- L27 _public prototype_ `FAudioOscilloscope(Audio::FDeviceId InAudioDeviceId, const uint32 InNumChannels, const float InTimeWindowMs, const float InMaxTimeWindowMs, const float InAnalysisPeriodMs, const EAudioPanelLayoutType InPanelLayoutType, const FAudioOscilloscopePanelStyle* InOscilloscopePanelStyle = nullptr, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr);`
- L36 _public prototype_ `void CreateAudioBus(const uint32 InNumChannels);`
- L38 _public prototype_ `void CreateDataProvider(Audio::FDeviceId InAudioDeviceId, const float InTimeWindowMs, const float InMaxTimeWindowMs, const float InAnalysisPeriodMs, const EAudioPanelLayoutType InPanelLayoutType);`
- L44 _public prototype_ `void CreateOscilloscopeWidget(const uint32 InNumChannels, const EAudioPanelLayoutType InPanelLayoutType, const FAudioOscilloscopePanelStyle* InOscilloscopePanelStyle = nullptr);`
- L46 _public prototype_ `virtual void StartProcessing() override;`
- L47 _public prototype_ `virtual void StopProcessing() override;`
- L49 _public prototype_ `UAudioBus* GetAudioBus() const;`
- L50 _public prototype_ `TSharedRef<SWidget> GetPanelWidget() const;`
- L53 _public prototype_ `virtual void SetAudioBusInfo(const FAudioBusInfo& AudioBusInfo) override;`
- L54 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args) const override;`
- L58 _private prototype_ `static TSharedRef<IAudioAnalyzerRackUnit> MakeRackUnit(const FAudioAnalyzerRackUnitConstructParams& Params);`
- L59 _private member_ `static constexpr float RackUnitTimeWindowMs = 10.0f;`
- L60 _private member_ `static constexpr float RackUnitMaxTimeWindowMs = 10.0f;`
- L61 _private member_ `static constexpr float RackUnitAnalysisPeriodMs = 10.0f;`
- L62 _private member_ `static constexpr EAudioPanelLayoutType RackUnitPanelLayoutType = EAudioPanelLayoutType::Basic;`
- L64 _private member_ `FAudioOscilloscopePanelStyle OscilloscopePanelStyle;`
- L66 _private member_ `TSharedPtr<FWaveformAudioSamplesDataProvider> AudioSamplesDataProvider = nullptr;`
- L67 _private member_ `TSharedPtr<SAudioOscilloscopePanelWidget> OscilloscopePanelWidget = nullptr;`
- L69 _private member_ `TStrongObjectPtr<UAudioBus> AudioBus = nullptr;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L18 _namespace_ `namespace AudioWidgets`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioOscilloscopeEnums.h` (Public)


#### enum `EAudioOscilloscopeTriggerMode`  
`enum class EAudioOscilloscopeTriggerMode : uint8`  
_L8-13_
- reflection: `UENUM(BlueprintType)`
- L10 _public enumerator_ `None UMETA(DisplayName = "None")`
- L11 _public enumerator_ `Rising UMETA(DisplayName = "Rising")`
- L12 _public enumerator_ `Falling UMETA(DisplayName = "Falling")`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioOscilloscopePanelStyle.h` (Public)


#### struct `FAudioOscilloscopePanelStyle`  
`struct FAudioOscilloscopePanelStyle : public FSlateWidgetStyle`  
_L24-87_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an SAudioOscilloscopePanelWidget
- L28 _public function_ `FAudioOscilloscopePanelStyle()`
- L57 _public prototype_ `virtual ~FAudioOscilloscopePanelStyle() = default;`
- L59 _public function_ `virtual const FName GetTypeName() const override`
- L60 _public function_ `static const FAudioOscilloscopePanelStyle& GetDefault()`
- L64 _public member_ `FFixedSampleSequenceRulerStyle TimeRulerStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The time rule style.
- L65 _public function_ `FAudioOscilloscopePanelStyle& SetTimeRulerStyle(const FFixedSampleSequenceRulerStyle& InTimeRulerStyle)`
- L69 _public member_ `FSampledSequenceValueGridOverlayStyle ValueGridStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The value grid style.
- L70 _public function_ `FAudioOscilloscopePanelStyle& SetValueGridStyle(const FSampledSequenceValueGridOverlayStyle& InValueGridStyle)`
- L74 _public member_ `FSampledSequenceViewerStyle WaveViewerStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The waveform view style.
- L75 _public function_ `FAudioOscilloscopePanelStyle& SetWaveViewerStyle(const FSampledSequenceViewerStyle& InWaveViewerStyle)`
- L79 _public member_ `FTriggerThresholdLineStyle TriggerThresholdLineStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The triggerthreshold line style.
- L80 _public function_ `FAudioOscilloscopePanelStyle& SetTriggerThresholdLineStyle(const FTriggerThresholdLineStyle& InTriggerThresholdLineStyle)`
- L82 _public member_ `inline static FName TypeName = FName("FAu`
- L84 _public member_ `static FOnNewTimeRulerStyle OnNewTimeRulerStyle;`
- L85 _public member_ `static FOnNewValueGridOverlayStyle OnNewValueGridOverlayStyle;`
- L86 _public member_ `static FOnNewWaveformViewerStyle OnNewWaveformViewerStyle;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewTimeRulerStyle, FFixedSampleSequenceRulerStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewValueGridOverlayStyle, FSampledSequenceValueGridOverlayStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWaveformViewerStyle, FSampledSequenceViewerStyle) USTRUCT(BlueprintType) struct FAudioOscilloscopePanelStyle : public FSlateWidgetStyle { GENERATED_USTRUCT_BODY() FAudioOscilloscopePanelStyle() { TimeRulerStyle = FFixedSampleSequenceRulerStyle() .SetHandleColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)) .SetTicksColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)) .SetTicksTextColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)) .SetHandleColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)) .SetFontSize(10); ValueGridStyle = FSampledSequenceValueGridOverlayStyle() .SetGridColor(FLinearColor(0.05f, 0.05f, 0.05f, 0.5f)) .SetGridThickness(1.0f) .SetLabelTextColor(FLinearColor(0.442708f, 0.442708f, 0.442708f, 1.0f)) .SetLabelTextFontSize(10.0f); WaveViewerStyle = FSampledSequenceViewerStyle() .SetSequenceColor(FLinearColor(0.1f, 1.0f, 0.55f, 1.0f)) .SetBackgroundColor(FLinearColor(0.01f, 0.01f, 0.01f, 1.0f)) .SetSequenceLineThickness(2.0f) .SetSampleMarkersSize(0.0f) .SetMajorGridLineColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.0f)) .SetMinorGridLineColor(FLinearColor(0.05f, 0.05f, 0.05f, 1.0f)) .SetZeroCrossingLineColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)) .SetZeroCrossingLineThickness(1.0f); TriggerThresholdLineStyle = FTriggerThresholdLineStyle() .SetLineColor(FLinearColor(1.0f, 0.`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewValueGridOverlayStyle, FSampledSequenceValueGridOverlayStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWaveformViewerStyle, FSampledSequenceViewerStyle) USTRUCT(BlueprintType) struct FAudioOscilloscopePanelStyle : public FSlateWidgetStyle { GENERATED_USTRUCT_BODY() FAudioOscilloscopePanelStyle() { TimeRulerStyle = FFixedSampleSequenceRulerStyle() .SetHandleColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)) .SetTicksColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)) .SetTicksTextColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)) .SetHandleColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)) .SetFontSize(10); ValueGridStyle = FSampledSequenceValueGridOverlayStyle() .SetGridColor(FLinearColor(0.05f, 0.05f, 0.05f, 0.5f)) .SetGridThickness(1.0f) .SetLabelTextColor(FLinearColor(0.442708f, 0.442708f, 0.442708f, 1.0f)) .SetLabelTextFontSize(10.0f); WaveViewerStyle = FSampledSequenceViewerStyle() .SetSequenceColor(FLinearColor(0.1f, 1.0f, 0.55f, 1.0f)) .SetBackgroundColor(FLinearColor(0.01f, 0.01f, 0.01f, 1.0f)) .SetSequenceLineThickness(2.0f) .SetSampleMarkersSize(0.0f) .SetMajorGridLineColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.0f)) .SetMinorGridLineColor(FLinearColor(0.05f, 0.05f, 0.05f, 1.0f)) .SetZeroCrossingLineColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)) .SetZeroCrossingLineThickness(1.0f); TriggerThresholdLineStyle = FTriggerThresholdLineStyle() .SetLineColor(FLinearColor(1.0f, 0.91f, 0.34f)); }`
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewWaveformViewerStyle, FSampledSequenceViewerStyle) USTRUCT(BlueprintType) struct FAudioOscilloscopePanelStyle : public FSlateWidgetStyle { GENERATED_USTRUCT_BODY() FAudioOscilloscopePanelStyle() { TimeRulerStyle = FFixedSampleSequenceRulerStyle() .SetHandleColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)) .SetTicksColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)) .SetTicksTextColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)) .SetHandleColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f)) .SetFontSize(10); ValueGridStyle = FSampledSequenceValueGridOverlayStyle() .SetGridColor(FLinearColor(0.05f, 0.05f, 0.05f, 0.5f)) .SetGridThickness(1.0f) .SetLabelTextColor(FLinearColor(0.442708f, 0.442708f, 0.442708f, 1.0f)) .SetLabelTextFontSize(10.0f); WaveViewerStyle = FSampledSequenceViewerStyle() .SetSequenceColor(FLinearColor(0.1f, 1.0f, 0.55f, 1.0f)) .SetBackgroundColor(FLinearColor(0.01f, 0.01f, 0.01f, 1.0f)) .SetSequenceLineThickness(2.0f) .SetSampleMarkersSize(0.0f) .SetMajorGridLineColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.0f)) .SetMinorGridLineColor(FLinearColor(0.05f, 0.05f, 0.05f, 1.0f)) .SetZeroCrossingLineColor(FLinearColor(0.3f, 0.3f, 0.3f, 1.0f)) .SetZeroCrossingLineThickness(1.0f); TriggerThresholdLineStyle = FTriggerThresholdLineStyle() .SetLineColor(FLinearColor(1.0f, 0.91f, 0.34f)); } virtual ~FAudioOscilloscopePanelStyle() = default;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioOscilloscopeUMG.h` (Public)


#### class `UAudioOscilloscope`  
`class UAudioOscilloscope: public UWidget`  
_L29-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: An oscilloscope UMG widget. Supports displaying waveforms from incoming audio samples.
- L34 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<float>, FGetOscilloscopeAudioSamples);`
- L37 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget overrides
- L38 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L41 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L46 _public prototype_ `void StartProcessing();` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Oscilloscope")` — Starts the oscilloscope processing.
- L50 _public prototype_ `void StopProcessing();` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Oscilloscope")` — Stops the oscilloscope processing.
- L54 _public member_ `FAudioOscilloscopePanelStyle OscilloscopeStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Style", meta=(DisplayName="Style"))` — The oscilloscope panel style
- L58 _public member_ `TObjectPtr<UAudioBus> AudioBus = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values", meta = (DesignerRebuild = "True"))` — The audio bus used to obtain audio samples for the oscilloscope
- L62 _public member_ `float MaxTimeWindowMs = 5000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values", meta = (UIMin = 10.0, UIMax = 5000.0, ClampMin = 10.0, ClampMax = 5000.0))` — The max time window in milliseconds.
- L66 _public member_ `float TimeWindowMs = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values", meta = (UIMin = 10.0, ClampMin = 10.0))` — The time window in milliseconds.
- L70 _public member_ `float AnalysisPeriodMs = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values", meta = (UIMin = 10, UIMax = 1000, ClampMin = 10, ClampMax = 1000))` — The analysis period in milliseconds.
- L74 _public member_ `bool bShowTimeGrid = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values")` — Show/Hide the time grid.
- L78 _public member_ `EXAxisLabelsUnit TimeGridLabelsUnit = EXAxisLabelsUnit::Samples;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values")` — Define the time grid labels unit.
- L82 _public member_ `bool bShowAmplitudeGrid = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values")` — Show/Hide the amplitude grid.
- L86 _public member_ `bool bShowAmplitudeLabels = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values")` — Show/Hide the amplitude labels.
- L90 _public member_ `EYAxisLabelsUnit AmplitudeGridLabelsUnit = EYAxisLabelsUnit::Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values")` — Define the amplitude grid labels unit.
- L94 _public member_ `EAudioOscilloscopeTriggerMode TriggerMode = EAudioOscilloscopeTriggerMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values", meta = (EditCondition = "CanTriggeringBeSet()", EditConditionHides))` — The trigger detection behavior.
- L98 _public member_ `float TriggerThreshold = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values", meta = (UIMin = -1, UIMax = 1, ClampMin = -1, ClampMax = 1, EditCondition = "CanTriggeringBeSet() && TriggerMode != EAudioOscilloscopeTriggerMode::None", EditConditionHides))` — The trigger threshold position in the Y axis.
- L102 _public member_ `EAudioPanelLayoutType PanelLayoutType = EAudioPanelLayoutType::Basic;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values", meta = (DesignerRebuild = "True"))` — Show/Hide advanced panel layout.
- L106 _public member_ `int32 ChannelToAnalyze = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Oscilloscope Values", meta = (EditCondition = "PanelLayoutType == EAudioPanelLayoutType::Advanced", EditConditionHides))` — The channel to analyze with the oscilloscope (only available if PanelLayoutType is set to "Advanced").
- L109 _private prototype_ `void CreateDummyOscilloscopeWidget();`
- L110 _private prototype_ `void CreateDataProvider();`
- L111 _private prototype_ `void CreateOscilloscopeWidget();`
- L114 _private prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget overrides
- L117 _private prototype_ `bool CanTriggeringBeSet();` — `UFUNCTION()`
- L120 _private member_ `TSharedPtr<AudioWidgets::FWaveformAudioSamplesDataProvider> AudioSamplesDataProvider;` — The underlying audio samples data provider
- L123 _private member_ `TSharedPtr<SAudioOscilloscopePanelWidget> OscilloscopePanelWidget;` — Native Slate Widget
- L126 _private member_ `static constexpr uint32 DummySampleRate = 48000;` — Dummy waveform data to display if audio bus is not set
- L127 _private member_ `static constexpr int32 DummyMaxNumSamples = DummySampleRate * 5;`
- L128 _private member_ `static constexpr int32 DummyNumChannels = 1;`
- L130 _private member_ `int32 NumChannels = DummyNumChannels;`
- L132 _private member_ `TArray<float> DummyAudioSamples;`
- L133 _private member_ `FFixedSampledSequenceView DummyDataView;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L18 _namespace_ `namespace AudioWidgets`
- L34 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<float>, FGetOscilloscopeAudioSamples);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioRadialSlider.h` (Public)


#### class `UAudioRadialSlider`  
`class UAudioRadialSlider : public UWidget`  
_L22-187_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: An audio radial slider widget.
- L29 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, Category = Appearance, meta = (UIMin = "0", UIMax = "1"))` — The normalized linear (0 - 1) slider value position.
- L33 _public member_ `FGetFloat ValueDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the widget
- L37 _public member_ `TEnumAsByte<EAudioRadialSliderLayout> WidgetLayout;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The layout of the widget (position of text label).
- L41 _public member_ `FLinearColor CenterBackgroundColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the widget background.
- L45 _public member_ `FLinearColor SliderProgressColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the slider progress bar in.
- L49 _public member_ `FLinearColor SliderBarColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the slider bar in.
- L53 _public member_ `FVector2D HandStartEndRatio;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Start and end of the hand as a ratio to the slider radius (so 0.0 to 1.0 is from the slider center to the handle).
- L57 _public member_ `FText UnitsText;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The text label units
- L61 _public member_ `FLinearColor TextLabelBackgroundColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the text label background.
- L65 _public member_ `bool ShowLabelOnlyOnHover;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — If true, show text label only on hover; if false always show label.
- L69 _public member_ `bool ShowUnitsText;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Whether to show the units part of the text label.
- L73 _public member_ `bool IsUnitsTextReadOnly;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Whether to set the units part of the text label read only.
- L77 _public member_ `bool IsValueTextReadOnly;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Whether to set the value part of the text label read only.
- L81 _public member_ `float SliderThickness;` — `UPROPERTY(EditAnywhere, Category = Appearance, meta = (ClampMin = "0.0"))` — The slider thickness.
- L85 _public member_ `FVector2D OutputRange;` — `UPROPERTY(EditAnywhere, Category = Behavior)` — Output range
- L89 _public member_ `FOnAudioRadialSliderValueChangedEvent OnValueChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when the value is changed by slider or typing.
- L93 _public member_ `FOnAudioRadialSliderMouseCaptureBeginEvent OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when a mouse drag begins.
- L97 _public member_ `FOnAudioRadialSliderMouseCaptureEndEvent OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when a mouse drag ends.
- L102 _public prototype_ `float GetOutputValue(const float InSliderValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Get output value from normalized linear (0 - 1) based on internal lin to output mapping.
- L106 _public prototype_ `float GetSliderValue(const float OutputValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Get normalized linear (0 - 1) slider value from output based on internal lin to output mapping.
- L110 _public prototype_ `void SetWidgetLayout(EAudioRadialSliderLayout InLayout);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the widget layout
- L114 _public prototype_ `void SetCenterBackgroundColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the label background color
- L118 _public prototype_ `void SetSliderProgressColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the slider progress color
- L122 _public prototype_ `void SetSliderBarColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the slider bar color
- L126 _public prototype_ `void SetHandStartEndRatio(const FVector2D InHandStartEndRatio);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the start and end of the hand as a ratio to the slider radius (so 0.0 to 1.0 is from the slider center to the handle).
- L130 _public prototype_ `void SetTextLabelBackgroundColor(FSlateColor InColor);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the label background color
- L134 _public prototype_ `void SetUnitsText(const FText Units);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the units text
- L138 _public prototype_ `void SetUnitsTextReadOnly(const bool bIsReadOnly);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets whether the units text is read only
- L142 _public prototype_ `void SetValueTextReadOnly(const bool bIsReadOnly);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets whether the value text is read only
- L146 _public prototype_ `void SetShowLabelOnlyOnHover(const bool bShowLabelOnlyOnHover);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — If true, show text label only on hover; if false always show label.
- L150 _public prototype_ `void SetShowUnitsText(const bool bShowUnitsText);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets whether to show the units text
- L154 _public prototype_ `void SetSliderThickness(const float InThickness);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the slider thickness
- L158 _public prototype_ `void SetOutputRange(const FVector2D InOutputRange);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Radial Slider")` — Sets the output range
- L161 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L165 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L169 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L173 _protected member_ `FAudioRadialSliderStyle WidgetStyle;`
- L176 _protected member_ `TSharedPtr<SAudioRadialSlider> MyAudioRadialSlider;` — Native Slate Widget
- L178 _protected prototype_ `void HandleOnValueChanged(float InValue);`
- L179 _protected prototype_ `void HandleOnMouseCaptureBegin();`
- L180 _protected prototype_ `void HandleOnMouseCaptureEnd();`
- L183 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget();` — UWidget interface
- L185 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(float, Value);`

#### class `UAudioVolumeRadialSlider`  
`class UAudioVolumeRadialSlider : public UAudioRadialSlider`  
_L193-199_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioRadialSlider`
- desc: An audio slider widget, for use with volume.
- L198 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`

#### class `UAudioFrequencyRadialSlider`  
`class UAudioFrequencyRadialSlider : public UAudioRadialSlider`  
_L205-211_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioRadialSlider`
- desc: An audio slider widget, for use with frequency.
- L210 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioRadialSliderMouseCaptureBeginEvent);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioRadialSliderMouseCaptureBeginEvent);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioRadialSliderMouseCaptureEndEvent);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioRadialSliderMouseCaptureEndEvent);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioRadialSliderValueChangedEvent, float, Value);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioRadialSliderValueChangedEvent, float, Value);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioSlider.h` (Public)


#### class `UAudioSliderBase`  
`class UAudioSliderBase: public UWidget`  
_L20-194_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UWidget`
- desc: An audio slider widget.
- L27 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, Category = Appearance, meta = (UIMin = "0", UIMax = "1"))` — The normalized linear (0 - 1) slider value.
- L31 _public member_ `FText UnitsText;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The text label units
- L35 _public member_ `FLinearColor TextLabelBackgroundColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the text label background.
- L39 _public member_ `FGetLinearColor TextLabelBackgroundColorDelegate;` — `UPROPERTY()` — A bindable delegate for the TextLabelBackgroundColor.
- L43 _public member_ `bool ShowLabelOnlyOnHover;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — If true, show text label only on hover; if false always show label.
- L47 _public member_ `bool ShowUnitsText;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Whether to show the units part of the text label.
- L51 _public member_ `bool IsUnitsTextReadOnly;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Whether to set the units part of the text label read only.
- L55 _public member_ `bool IsValueTextReadOnly;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Whether to set the value part of the text label read only.
- L59 _public member_ `FGetFloat ValueDelegate;` — `UPROPERTY()` — A bindable delegate to allow logic to drive the value of the widget
- L63 _public member_ `FLinearColor SliderBackgroundColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the slider background.
- L67 _public member_ `FGetLinearColor SliderBackgroundColorDelegate;` — `UPROPERTY()` — A bindable delegate for the SliderBackgroundColor.
- L71 _public member_ `FLinearColor SliderBarColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the slider bar.
- L75 _public member_ `FGetLinearColor SliderBarColorDelegate;` — `UPROPERTY()` — A bindable delegate for the SliderBarColor.
- L79 _public member_ `FLinearColor SliderThumbColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the slider thumb.
- L83 _public member_ `FGetLinearColor SliderThumbColorDelegate;` — `UPROPERTY()` — A bindable delegate for the SliderThumbColor.
- L87 _public member_ `FLinearColor WidgetBackgroundColor;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — The color to draw the widget background.
- L91 _public member_ `FGetLinearColor WidgetBackgroundColorDelegate;` — `UPROPERTY()` — A bindable delegate for the WidgetBackgroundColor.
- L96 _public prototype_ `float GetOutputValue(const float InSliderValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Get output value from normalized linear (0 - 1) based on internal lin to output mapping.
- L100 _public prototype_ `float GetLinValue(const float OutputValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider", meta=(DeprecatedFunction, DeprecationMessage="5.1 - GetLinValue is deprecated, please use GetSliderValue instead."))` — Get normalized linear (0 - 1) value from output based on internal lin to output mapping.
- L104 _public prototype_ `float GetSliderValue(const float OutputValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Get normalized linear (0 - 1) slider value from output based on internal lin to output mapping.
- L108 _public prototype_ `void SetTextLabelBackgroundColor(FSlateColor InColor);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets the label background color
- L112 _public prototype_ `void SetUnitsText(const FText Units);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets the units text
- L116 _public prototype_ `void SetUnitsTextReadOnly(const bool bIsReadOnly);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets whether the units text is read only
- L120 _public prototype_ `void SetValueTextReadOnly(const bool bIsReadOnly);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets whether the value text is read only
- L124 _public prototype_ `void SetShowLabelOnlyOnHover(const bool bShowLabelOnlyOnHover);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — If true, show text label only on hover; if false always show label.
- L128 _public prototype_ `void SetShowUnitsText(const bool bShowUnitsText);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets whether to show the units text
- L132 _public prototype_ `void SetSliderBackgroundColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets the slider background color
- L136 _public prototype_ `void SetSliderBarColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets the slider bar color
- L140 _public prototype_ `void SetSliderThumbColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets the slider thumb color
- L144 _public prototype_ `void SetWidgetBackgroundColor(FLinearColor InValue);` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Audio Slider")` — Sets the widget background color
- L148 _public member_ `TEnumAsByte<EOrientation> Orientation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)` — The slider's orientation.
- L152 _public member_ `FOnFloatValueChangedEvent OnValueChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when the value is changed by slider or typing.
- L156 _public member_ `FOnMouseCaptureBeginEvent OnMouseCaptureBegin;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when a mouse drag begins.
- L160 _public member_ `FOnMouseCaptureEndEvent OnMouseCaptureEnd;` — `UPROPERTY(BlueprintAssignable, Category = "Widget Event")` — Called when a mouse drag ends.
- L163 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget interface
- L167 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual interface
- L171 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L175 _protected member_ `FAudioSliderStyle WidgetStyle;`
- L178 _protected member_ `TSharedPtr<SAudioSliderBase> MyAudioSlider;` — Native Slate Widget
- L180 _protected prototype_ `void HandleOnValueChanged(float InValue);`
- L181 _protected prototype_ `void HandleOnMouseCaptureBegin();`
- L182 _protected prototype_ `void HandleOnMouseCaptureEnd();`
- L185 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget();` — UWidget interface
- L188 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(float, Value);`
- L189 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FLinearColor, TextLabelBackgroundColor);`
- L190 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FLinearColor, SliderBackgroundColor);`
- L191 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FLinearColor, SliderBarColor);`
- L192 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FLinearColor, SliderThumbColor);`
- L193 _protected prototype_ `PROPERTY_BINDING_IMPLEMENTATION(FLinearColor, WidgetBackgroundColor);`

#### class `UAudioSlider`  
`class UAudioSlider : public UAudioSliderBase`  
_L200-214_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioSliderBase`
- desc: An audio slider widget with customizable curves.
- L206 _private member_ `TWeakObjectPtr<const UCurveFloat> LinToOutputCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")` — Curves for mapping linear to output values.
- L209 _private member_ `TWeakObjectPtr <const UCurveFloat> OutputToLinCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")`
- L212 _protected prototype_ `virtual void SynchronizeProperties() override;`
- L213 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`

#### class `UAudioVolumeSlider`  
`class UAudioVolumeSlider : public UAudioSlider`  
_L220-225_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioSlider`
- desc: An audio slider widget with default customizable curves for volume (dB).
- L224 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`

#### class `UAudioFrequencySlider`  
`class UAudioFrequencySlider : public UAudioSliderBase`  
_L231-240_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioSliderBase`
- desc: An audio slider widget, for use with frequency.
- L237 _private member_ `FVector2D OutputRange = FVector2D(MIN_FILTER_FREQUENCY, MAX_FILTER_FREQUENCY);` — `UPROPERTY(EditAnywhere, Category = Behavior)` — Frequency output range
- L239 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioSpectrogram.h` (Public)


#### struct `AudioWidgets::FAudioSpectrogramParams`  
`struct FAudioSpectrogramParams`  
_L17-38_
- desc: Constructor parameters for the analyzer.
- L19 _public member_ `int32 NumChannels = 1;`
- L20 _public member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L21 _public member_ `TObjectPtr<UAudioBus> ExternalAudioBus = nullptr;`
- L23 _public member_ `TAttribute<EAudioSpectrumAnalyzerType> AnalyzerType = EAudioSpectrumAnalyzerType::FFT;`
- L24 _public member_ `TAttribute<EFFTSize> FFTAnalyzerFFTSize = EFFTSize::Max;`
- L25 _public member_ `TAttribute<EConstantQFFTSizeEnum> CQTAnalyzerFFTSize = EConstantQFFTSizeEnum::XXLarge;`
- L26 _public member_ `TAttribute<EAudioSpectrogramFrequencyAxisPixelBucketMode> FrequencyAxisPixelBucketMode = EAudioSpectrogramFrequencyAxisPixelBucketMode::Average;`
- L27 _public member_ `TAttribute<EAudioSpectrogramFrequencyAxisScale> FrequencyAxisScale = EAudioSpectrogramFrequencyAxisScale::Logarithmic;`
- L28 _public member_ `TAttribute<EAudioColorGradient> ColorMap = EAudioColorGradient::BlackToWhite;`
- L29 _public member_ `TAttribute<EOrientation> Orientation = EOrientation::Orient_Horizontal;`
- L31 _public member_ `FOnAnalyzerTypeMenuEntryClicked OnAnalyzerTypeMenuEntryClicked;`
- L32 _public member_ `FOnFFTAnalyzerFFTSizeMenuEntryClicked OnFFTAnalyzerFFTSizeMenuEntryClicked;`
- L33 _public member_ `FOnCQTAnalyzerFFTSizeMenuEntryClicked OnCQTAnalyzerFFTSizeMenuEntryClicked;`
- L34 _public member_ `FOnSpectrogramFrequencyAxisPixelBucketModeMenuEntryClicked OnFrequencyAxisPixelBucketModeMenuEntryClicked;`
- L35 _public member_ `FOnSpectrogramFrequencyAxisScaleMenuEntryClicked OnFrequencyAxisScaleMenuEntryClicked;`
- L36 _public member_ `FOnSpectrogramColorMapMenuEntryClicked OnColorMapMenuEntryClicked;`
- L37 _public member_ `FOnSpectrogramOrientationMenuEntryClicked OnOrientationMenuEntryClicked;`

#### class `AudioWidgets::FAudioSpectrogram`  
`class FAudioSpectrogram : public IAudioAnalyzerRackUnit`  
_L44-122_
- inherits: `IAudioAnalyzerRackUnit`
- desc: Owns an analyzer and a corresponding Slate widget for displaying the resulting spectra. Can either create an Audio Bus to analyze, or analyze the given Bus.
- L47 _public member_ `static const FAudioAnalyzerRackUnitTypeInfo RackUnitTypeInfo;`
- L49 _public prototype_ `FAudioSpectrogram(const FAudioSpectrogramParams& Params);`
- L50 _public prototype_ `~FAudioSpectrogram();`
- L52 _public prototype_ `UAudioBus* GetAudioBus() const;`
- L54 _public prototype_ `TSharedRef<SWidget> GetWidget() const;`
- L56 _public prototype_ `void Init(int32 InNumChannels, Audio::FDeviceId InAudioDeviceId, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr);`
- L59 _public function_ `virtual void SetAudioBusInfo(const FAudioBusInfo& AudioBusInfo) override`
- L64 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args) const override;`
- L68 _protected prototype_ `void StartAnalyzing(const EAudioSpectrumAnalyzerType InAnalyzerType);`
- L69 _protected prototype_ `void StopAnalyzing();`
- L71 _protected prototype_ `void OnSpectrumResults(USynesthesiaSpectrumAnalyzer* InSpectrumAnalyzer, int32 ChannelIndex, const TArray<FSynesthesiaSpectrumResults>& InSpectrumResultsArray);`
- L72 _protected prototype_ `void OnConstantQResults(UConstantQAnalyzer* InSpectrumAnalyzer, int32 ChannelIndex, const TArray<FConstantQResults>& InSpectrumResultsArray);`
- L74 _protected prototype_ `void ExtendSpectrumPlotContextMenu(FMenuBuilder& MenuBuilder);`
- L75 _protected prototype_ `void BuildAnalyzerTypeSubMenu(FMenuBuilder& SubMenu);`
- L76 _protected prototype_ `void BuildFFTSizeSubMenu(FMenuBuilder& SubMenu);`
- L78 _protected prototype_ `EActiveTimerReturnType Update(double InCurrentTime, float InDeltaTime);`
- L81 _private prototype_ `static TSharedRef<IAudioAnalyzerRackUnit> MakeRackUnit(const FAudioAnalyzerRackUnitConstructParams& Params);`
- L83 _private prototype_ `void CreateSynesthesiaSpectrumAnalyzer();`
- L84 _private prototype_ `void ReleaseSynesthesiaSpectrumAnalyzer();`
- L86 _private prototype_ `void CreateConstantQAnalyzer();`
- L87 _private prototype_ `void ReleaseConstantQAnalyzer();`
- L89 _private prototype_ `void Teardown();`
- L92 _private member_ `TStrongObjectPtr<USynesthesiaSpectrumAnalyzer> SpectrumAnalyzer;` — Audio analyzer objects.
- L93 _private member_ `TStrongObjectPtr<UConstantQAnalyzer> ConstantQAnalyzer;`
- L96 _private member_ `TStrongObjectPtr<UAudioBus> AudioBus;` — The audio bus used for analysis.
- L99 _private member_ `FDelegateHandle SpectrumResultsDelegateHandle;` — Handles for results delegate for analyzers.
- L100 _private member_ `FDelegateHandle ConstantQResultsDelegateHandle;`
- L103 _private member_ `TStrongObjectPtr<USynesthesiaSpectrumAnalysisSettings> SpectrumAnalysisSettings;` — Analyzer settings.
- L104 _private member_ `TStrongObjectPtr<UConstantQSettings> ConstantQSettings;`
- L107 _private member_ `TSharedPtr<SAudioSpectrogram> Widget;` — Slate widget for spectrum display
- L108 _private member_ `TSharedPtr<const FExtensionBase> ContextMenuExtension;`
- L109 _private member_ `TSharedPtr<FActiveTimerHandle> ActiveTimer;`
- L111 _private member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L112 _private member_ `bool bUseExternalAudioBus = false;`
- L114 _private member_ `TOptional<EAudioSpectrumAnalyzerType> ActiveAnalyzerType;`
- L115 _private member_ `TAttribute<EAudioSpectrumAnalyzerType> AnalyzerType;`
- L116 _private member_ `TAttribute<EFFTSize> FFTAnalyzerFFTSize;`
- L117 _private member_ `TAttribute<EConstantQFFTSizeEnum> CQTAnalyzerFFTSize;`
- L119 _private member_ `FOnAnalyzerTypeMenuEntryClicked OnAnalyzerTypeMenuEntryClicked;`
- L120 _private member_ `FOnFFTAnalyzerFFTSizeMenuEntryClicked OnFFTAnalyzerFFTSizeMenuEntryClicked;`
- L121 _private member_ `FOnCQTAnalyzerFFTSizeMenuEntryClicked OnCQTAnalyzerFFTSizeMenuEntryClicked;`

#### struct `FSpectrogramRackUnitSettings`  
`struct FSpectrogramRackUnitSettings`  
_L126-150_
- reflection: `USTRUCT()`
- L131 _public member_ `EAudioSpectrumAnalyzerType AnalyzerType = EAudioSpectrumAnalyzerType::FFT;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram)`
- L134 _public member_ `EFFTSize FFTAnalyzerFFTSize = EFFTSize::Max;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram, meta = (DisplayName = "FFT Size (FFT Analyzer)"))`
- L137 _public member_ `EConstantQFFTSizeEnum CQTAnalyzerFFTSize = EConstantQFFTSizeEnum::XXLarge;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram, meta = (DisplayName = "FFT Size (CQT Analyzer)"))`
- L140 _public member_ `EAudioSpectrogramFrequencyAxisPixelBucketMode PixelPlotMode = EAudioSpectrogramFrequencyAxisPixelBucketMode::Average;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram)`
- L143 _public member_ `EAudioSpectrogramFrequencyAxisScale FrequencyScale = EAudioSpectrogramFrequencyAxisScale::Logarithmic;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram)`
- L146 _public member_ `EAudioColorGradient ColorMap = EAudioColorGradient::BlackToWhite;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram)`
- L149 _public member_ `TEnumAsByte<EOrientation> Orientation = EOrientation::Orient_Horizontal;` — `UPROPERTY(EditAnywhere, config, Category = Spectrogram)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L12 _namespace_ `namespace AudioWidgets`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioSpectrogramViewport.h` (Public)


#### enum `EAudioSpectrogramFrequencyAxisScale`  
`enum class EAudioSpectrogramFrequencyAxisScale : uint8`  
_L14-18_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Linear`
- L17 _public enumerator_ `Logarithmic`

#### enum `EAudioSpectrogramFrequencyAxisPixelBucketMode`  
`enum class EAudioSpectrogramFrequencyAxisPixelBucketMode : uint8`  
_L21-26_
- reflection: `UENUM(BlueprintType)`
- L23 _public enumerator_ `Sample UMETA(ToolTip = "Plot one data point per frequency axis pixel bucket only, choosing the data point nearest the pixel center.")`
- L24 _public enumerator_ `Peak UMETA(ToolTip = "Plot one data point per frequency axis pixel bucket only, choosing the data point with the highest sound level.")`
- L25 _public enumerator_ `Average UMETA(ToolTip = "Plot the average of the data points in each frequency axis pixel bucket.")`

#### struct `FAudioSpectrogramViewportRenderParams`  
`struct FAudioSpectrogramViewportRenderParams`  
_L31-42_
- desc: Parameters for the spectrogram viewport.
- L33 _public member_ `int NumRows = 0;`
- L34 _public member_ `int NumPixelsPerRow = 0;`
- L35 _public member_ `float ViewMinFrequency = 0.0f;`
- L36 _public member_ `float ViewMaxFrequency = 0.0f;`
- L37 _public member_ `float ColorMapMinSoundLevel = 0.0f;`
- L38 _public member_ `float ColorMapMaxSoundLevel = 0.0f;`
- L39 _public member_ `EAudioColorGradient ColorMap = EAudioColorGradient::BlackToWhite;`
- L40 _public member_ `EAudioSpectrogramFrequencyAxisScale FrequencyAxisScale = EAudioSpectrogramFrequencyAxisScale::Logarithmic;`
- L41 _public member_ `EAudioSpectrogramFrequencyAxisPixelBucketMode FrequencyAxisPixelBucketMode = EAudioSpectrogramFrequencyAxisPixelBucketMode::Average;`

#### struct `FAudioSpectrogramFrameData`  
`struct FAudioSpectrogramFrameData`  
_L47-54_
- desc: Struct for passing spectrum data for one frame of the spectrogram
- L49 _public member_ `TConstArrayView<float> SpectrumValues;`
- L50 _public member_ `EAudioSpectrumType SpectrumType = EAudioSpectrumType::PowerSpectrum;`
- L51 _public member_ `float MinFrequency = 0.0f;`
- L52 _public member_ `float MaxFrequency = 0.0f;`
- L53 _public member_ `bool bLogSpacedFreqencies = false;`

#### class `FAudioSpectrogramViewport`  
`class FAudioSpectrogramViewport : public ISlateViewport, public TSharedFromThis<FAudioSpectrogramViewport>`  
_L59-142_
- inherits: `ISlateViewport,TSharedFromThis<FAudioSpectrogramViewport>`
- desc: Maintains a history of spectrogram frames, and presents their visualization by implementing ISlateViewport.
- L62 _public prototype_ `FAudioSpectrogramViewport();`
- L63 _public prototype_ `~FAudioSpectrogramViewport();`
- L66 _public prototype_ `virtual FIntPoint GetSize() const override;` — ISlateViewport interface
- L67 _public function_ `virtual class FSlateShaderResource* GetViewportRenderTargetTexture() const override`
- L68 _public function_ `virtual bool RequiresVsync() const override`
- L69 _public function_ `virtual bool AllowScaling() const override`
- L72 _public prototype_ `void SetRenderParams(const FAudioSpectrogramViewportRenderParams& InRenderParams);` — The render params must be set before the FAudioSpectrogramViewport will do anything.
- L75 _public prototype_ `void AddFrame(const FAudioSpectrogramFrameData& SpectrogramFrameData);` — Add the given spectrum frame data to the history buffer.
- L79 _private prototype_ `void UpdateTextureData(const bool bInvalidateCachedPixelData = false);` — If row data or render params have changed, we must update the texture data. If render params change, we must also invalidate any previously cached pixel data for all rows.
- L138 _private member_ `FAudioSpectrogramViewportRenderParams RenderParams;`
- L139 _private member_ `TRingBuffer<FHistoryFrameData> History;`
- L140 _private member_ `FSlateUpdatableTexture* UpdatableTexture = nullptr;`
- L141 _private member_ `EPixelFormat UpdatableTexturePixelFormat = PF_Unknown;`

#### class `FAudioSpectrogramViewport::FHistoryFrameData`  
`class FHistoryFrameData : public FNoncopyable`  
_L84-136_
- inherits: `FNoncopyable`
- desc: Stores one frame of spectrogram data. Also generates the visual representation of this data as colored pixels, according to the given render params.
- L88 _public prototype_ `FHistoryFrameData(const FAudioSpectrogramFrameData& SpectrogramFrameData, const EAudioSpectrogramFrequencyAxisPixelBucketMode InFrequencyAxisPixelBucketMode = EAudioSpectrogramFrequencyAxisPixelBucketMode::Sample);` — Construct a history row to store the given spectrum data. Optionally also specify the pixel bucket mode to pre-allocate space for mips if required.
- L91 _public prototype_ `FHistoryFrameData(FHistoryFrameData&& Other);` — Include a move constructor due to being non-copyable.
- L94 _public prototype_ `void UpdateCachedPixels(const FAudioSpectrogramViewportRenderParams& InRenderParams);` — Generate pixel data for this frame according to the given render params.
- L97 _public function_ `TConstArrayView<FColor> GetCachedPixels() const` — Read the last generated pixel data.
- L101 _private prototype_ `void SetMipChainLengthUninitialized(const EAudioSpectrogramFrequencyAxisPixelBucketMode InFrequencyAxisPixelBucketMode);` — Allocate the necessary space for the mip chain if required.
- L104 _private prototype_ `void UpdateMipChain(const EAudioSpectrogramFrequencyAxisPixelBucketMode InFrequencyAxisPixelBucketMode);` — Generates mip maps if required.
- L107 _private function_ `bool HasMips() const` — We have mips if the mip chain is larger than mip zero.
- L110 _private prototype_ `TConstArrayView<float> GetMipFromMipSize(const int MipSize) const;` — Get a read-only view of the mip data for the given mip size.
- L113 _private prototype_ `float GetMipInterpolatedSoundLevel(const float DesiredMipSize, const float NormalizedDataPos) const;` — Sample a fully interpolated value from possibly between two mips, at the given normalized read position.
- L116 _private prototype_ `static float GetInterpolatedSoundLevel(const TConstArrayView<float> MipData, const float NormalizedDataPos);` — Helper function for sampling from the given mip data at the given normalized read position. Data is linearly interpolated.
- L119 _private prototype_ `static void ArrayMagnitudeToDecibel(TConstArrayView<float> InValues, TArrayView<float> OutValues, float InMinimumDb);` — Convert magnitude values to decibel values. db = 20 * log10(val)
- L122 _private prototype_ `static void ArrayPowerToDecibel(TConstArrayView<float> InValues, TArrayView<float> OutValues, float InMinimumDb);` — Convert power values to decibel values. db = 10 * log10(val)
- L125 _private member_ `const int32 NumSoundLevels;` — Immutable data describing this spectrogram frame:
- L126 _private member_ `const float SpectrumDataMinFrequency;`
- L127 _private member_ `const float SpectrumDataMaxFrequency;`
- L128 _private member_ `const bool bSpectrumDataHasLogSpacedFreqencies;`
- L131 _private member_ `TArray<float> SoundLevelsMipChain;` — The first NumSoundLevels values are the full resolution spectrogram data for this frame, and considered immutable. Following that may also be lower resolution mips generated for the given current pixel bucket mode.
- L132 _private member_ `EAudioSpectrogramFrequencyAxisPixelBucketMode SoundLevelsMipChainPixelBucketMode;`
- L135 _private member_ `TArray<FColor> CachedPixels;` — The most recently generated pixel data.

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioSpectrumAnalyzer.h` (Public)


#### enum `EAudioSpectrumAnalyzerBallistics`  
`enum class EAudioSpectrumAnalyzerBallistics : uint8`  
_L17-21_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Analog`
- L20 _public enumerator_ `Digital`

#### enum `EAudioSpectrumAnalyzerType`  
`enum class EAudioSpectrumAnalyzerType : uint8`  
_L24-28_
- reflection: `UENUM(BlueprintType)`
- L26 _public enumerator_ `FFT UMETA(ToolTip = "Fast Fourier Transform")`
- L27 _public enumerator_ `CQT UMETA(ToolTip = "Constant-Q Transform")`

#### struct `AudioWidgets::FAudioSpectrumAnalyzerParams`  
`struct FAudioSpectrumAnalyzerParams`  
_L40-67_
- desc: Constructor parameters for the analyzer.
- L42 _public member_ `int32 NumChannels = 1;`
- L43 _public member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L44 _public member_ `TObjectPtr<UAudioBus> ExternalAudioBus = nullptr;`
- L46 _public member_ `TAttribute<EAudioSpectrumAnalyzerBallistics> Ballistics = EAudioSpectrumAnalyzerBallistics::Digital;`
- L47 _public member_ `TAttribute<EAudioSpectrumAnalyzerType> AnalyzerType = EAudioSpectrumAnalyzerType::CQT;`
- L48 _public member_ `TAttribute<EFFTSize> FFTAnalyzerFFTSize = EFFTSize::Max;`
- L49 _public member_ `TAttribute<EConstantQFFTSizeEnum> CQTAnalyzerFFTSize = EConstantQFFTSizeEnum::XXLarge;`
- L50 _public member_ `TAttribute<float> TiltExponent = 0.0f;`
- L51 _public member_ `TAttribute<EAudioSpectrumPlotFrequencyAxisPixelBucketMode> FrequencyAxisPixelBucketMode = EAudioSpectrumPlotFrequencyAxisPixelBucketMode::Average;`
- L52 _public member_ `TAttribute<EAudioSpectrumPlotFrequencyAxisScale> FrequencyAxisScale = EAudioSpectrumPlotFrequencyAxisScale::Logarithmic;`
- L53 _public member_ `TAttribute<bool> bDisplayFrequencyAxisLabels = false;`
- L54 _public member_ `TAttribute<bool> bDisplaySoundLevelAxisLabels = false;`
- L56 _public member_ `FOnBallisticsMenuEntryClicked OnBallisticsMenuEntryClicked;`
- L57 _public member_ `FOnAnalyzerTypeMenuEntryClicked OnAnalyzerTypeMenuEntryClicked;`
- L58 _public member_ `FOnFFTAnalyzerFFTSizeMenuEntryClicked OnFFTAnalyzerFFTSizeMenuEntryClicked;`
- L59 _public member_ `FOnCQTAnalyzerFFTSizeMenuEntryClicked OnCQTAnalyzerFFTSizeMenuEntryClicked;`
- L60 _public member_ `FOnTiltSpectrumMenuEntryClicked OnTiltSpectrumMenuEntryClicked;`
- L61 _public member_ `FOnFrequencyAxisPixelBucketModeMenuEntryClicked OnFrequencyAxisPixelBucketModeMenuEntryClicked;`
- L62 _public member_ `FOnFrequencyAxisScaleMenuEntryClicked OnFrequencyAxisScaleMenuEntryClicked;`
- L63 _public member_ `FOnDisplayAxisLabelsButtonToggled OnDisplayFrequencyAxisLabelsButtonToggled;`
- L64 _public member_ `FOnDisplayAxisLabelsButtonToggled OnDisplaySoundLevelAxisLabelsButtonToggled;`
- L66 _public member_ `const FAudioSpectrumPlotStyle* PlotStyle = nullptr;`

#### class `AudioWidgets::FAudioSpectrumAnalyzer`  
`class FAudioSpectrumAnalyzer : public IAudioAnalyzerRackUnit`  
_L74-168_
- inherits: `IAudioAnalyzerRackUnit`
- desc: Owns an analyzer and a corresponding Slate widget for displaying the resulting spectrum. Exponential time-smoothing is applied to the spectrum. Can either create an Audio Bus to analyze, or analyze the given Bus.
- L77 _public member_ `static const FAudioAnalyzerRackUnitTypeInfo RackUnitTypeInfo;`
- L79 _public prototype_ `FAudioSpectrumAnalyzer(const FAudioSpectrumAnalyzerParams& Params);`
- L80 _public prototype_ `FAudioSpectrumAnalyzer(int32 InNumChannels, Audio::FDeviceId InAudioDeviceId, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr);`
- L81 _public prototype_ `~FAudioSpectrumAnalyzer();`
- L83 _public prototype_ `UAudioBus* GetAudioBus() const;`
- L85 _public prototype_ `TSharedRef<SWidget> GetWidget() const;`
- L87 _public prototype_ `void Init(int32 InNumChannels, Audio::FDeviceId InAudioDeviceId, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr);`
- L90 _public function_ `virtual void SetAudioBusInfo(const FAudioBusInfo& AudioBusInfo) override`
- L95 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args) const override;`
- L99 _protected prototype_ `void StartAnalyzing(const EAudioSpectrumAnalyzerType InAnalyzerType);`
- L100 _protected prototype_ `void StopAnalyzing();`
- L102 _protected prototype_ `void OnSpectrumResults(USynesthesiaSpectrumAnalyzer* InSpectrumAnalyzer, int32 ChannelIndex, const TArray<FSynesthesiaSpectrumResults>& InSpectrumResultsArray);`
- L103 _protected prototype_ `void OnConstantQResults(UConstantQAnalyzer* InSpectrumAnalyzer, int32 ChannelIndex, const TArray<FConstantQResults>& InSpectrumResultsArray);`
- L104 _protected prototype_ `void UpdateARSmoothing(const float TimeStamp, TConstArrayView<float> SquaredMagnitudes);`
- L106 _protected prototype_ `FAudioPowerSpectrumData GetAudioSpectrumData();`
- L108 _protected prototype_ `void ExtendSpectrumPlotContextMenu(FMenuBuilder& MenuBuilder);`
- L109 _protected prototype_ `void BuildBallisticsSubMenu(FMenuBuilder& SubMenu);`
- L110 _protected prototype_ `void BuildAnalyzerTypeSubMenu(FMenuBuilder& SubMenu);`
- L111 _protected prototype_ `void BuildFFTSizeSubMenu(FMenuBuilder& SubMenu);`
- L113 _protected prototype_ `void UpdateAnalyzerSettings();`
- L116 _private prototype_ `static TSharedRef<IAudioAnalyzerRackUnit> MakeRackUnit(const FAudioAnalyzerRackUnitConstructParams& Params);`
- L118 _private prototype_ `void CreateSynesthesiaSpectrumAnalyzer();`
- L119 _private prototype_ `void ReleaseSynesthesiaSpectrumAnalyzer();`
- L121 _private prototype_ `void CreateConstantQAnalyzer();`
- L122 _private prototype_ `void ReleaseConstantQAnalyzer();`
- L124 _private prototype_ `void Teardown();`
- L127 _private member_ `TStrongObjectPtr<USynesthesiaSpectrumAnalyzer> SpectrumAnalyzer;` — Audio analyzer objects.
- L128 _private member_ `TStrongObjectPtr<UConstantQAnalyzer> ConstantQAnalyzer;`
- L131 _private member_ `TStrongObjectPtr<UAudioBus> AudioBus;` — The audio bus used for analysis.
- L134 _private member_ `TArray<float> CenterFrequencies;` — Meaning of spectrum data.
- L137 _private member_ `TArray<float> ARSmoothedSquaredMagnitudes;` — Cached spectrum data, with AR smoothing applied.
- L140 _private member_ `FDelegateHandle SpectrumResultsDelegateHandle;` — Handles for results delegate for analyzers.
- L141 _private member_ `FDelegateHandle ConstantQResultsDelegateHandle;`
- L144 _private member_ `TStrongObjectPtr<USynesthesiaSpectrumAnalysisSettings> SpectrumAnalysisSettings;` — Analyzer settings.
- L145 _private member_ `TStrongObjectPtr<UConstantQSettings> ConstantQSettings;`
- L148 _private member_ `TSharedPtr<SAudioSpectrumPlot> Widget;` — Slate widget for spectrum display
- L149 _private member_ `TSharedPtr<const FExtensionBase> ContextMenuExtension;`
- L151 _private member_ `Audio::FDeviceId AudioDeviceId = INDEX_NONE;`
- L152 _private member_ `bool bUseExternalAudioBus = false;`
- L154 _private member_ `TOptional<EAudioSpectrumAnalyzerType> ActiveAnalyzerType;`
- L155 _private member_ `TOptional<float> PrevTimeStamp;`
- L156 _private member_ `float WindowCompensationPowerGain = 1.0f;`
- L157 _private member_ `float AttackTimeMsec = 300.0f;`
- L158 _private member_ `float ReleaseTimeMsec = 300.0f;`
- L159 _private member_ `TAttribute<EAudioSpectrumAnalyzerBallistics> Ballistics;`
- L160 _private member_ `TAttribute<EAudioSpectrumAnalyzerType> AnalyzerType;`
- L161 _private member_ `TAttribute<EFFTSize> FFTAnalyzerFFTSize;`
- L162 _private member_ `TAttribute<EConstantQFFTSizeEnum> CQTAnalyzerFFTSize;`
- L164 _private member_ `FOnBallisticsMenuEntryClicked OnBallisticsMenuEntryClicked;`
- L165 _private member_ `FOnAnalyzerTypeMenuEntryClicked OnAnalyzerTypeMenuEntryClicked;`
- L166 _private member_ `FOnFFTAnalyzerFFTSizeMenuEntryClicked OnFFTAnalyzerFFTSizeMenuEntryClicked;`
- L167 _private member_ `FOnCQTAnalyzerFFTSizeMenuEntryClicked OnCQTAnalyzerFFTSizeMenuEntryClicked;`

#### struct `FSpectrumAnalyzerRackUnitSettings`  
`struct FSpectrumAnalyzerRackUnitSettings`  
_L172-202_
- reflection: `USTRUCT()`
- L177 _public member_ `EAudioSpectrumAnalyzerBallistics Ballistics = EAudioSpectrumAnalyzerBallistics::Digital;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer)`
- L180 _public member_ `EAudioSpectrumAnalyzerType AnalyzerType = EAudioSpectrumAnalyzerType::CQT;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer)`
- L183 _public member_ `EFFTSize FFTAnalyzerFFTSize = EFFTSize::Max;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer, meta = (DisplayName = "FFT Size (FFT Analyzer)"))`
- L186 _public member_ `EConstantQFFTSizeEnum CQTAnalyzerFFTSize = EConstantQFFTSizeEnum::XXLarge;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer, meta = (DisplayName = "FFT Size (CQT Analyzer)"))`
- L189 _public member_ `EAudioSpectrumPlotTilt TiltSpectrum = EAudioSpectrumPlotTilt::NoTilt;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer)`
- L192 _public member_ `EAudioSpectrumPlotFrequencyAxisPixelBucketMode PixelPlotMode = EAudioSpectrumPlotFrequencyAxisPixelBucketMode::Average;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer)`
- L195 _public member_ `EAudioSpectrumPlotFrequencyAxisScale FrequencyScale = EAudioSpectrumPlotFrequencyAxisScale::Logarithmic;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer)`
- L198 _public member_ `bool bDisplayFrequencyAxisLabels = false;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer)`
- L201 _public member_ `bool bDisplaySoundLevelAxisLabels = false;` — `UPROPERTY(EditAnywhere, config, Category = SpectrumAnalyzer)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBallisticsMenuEntryClicked, EAudioSpectrumAnalyzerBallistics);`
- L30 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBallisticsMenuEntryClicked, EAudioSpectrumAnalyzerBallistics);`
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAnalyzerTypeMenuEntryClicked, EAudioSpectrumAnalyzerType);`
- L31 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAnalyzerTypeMenuEntryClicked, EAudioSpectrumAnalyzerType);`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFFTAnalyzerFFTSizeMenuEntryClicked, EFFTSize);`
- L32 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFFTAnalyzerFFTSizeMenuEntryClicked, EFFTSize);`
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCQTAnalyzerFFTSizeMenuEntryClicked, EConstantQFFTSizeEnum);`
- L33 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCQTAnalyzerFFTSizeMenuEntryClicked, EConstantQFFTSizeEnum);`
- L35 _namespace_ `namespace AudioWidgets`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioSpectrumPlotStyle.h` (Public)


#### struct `FAudioSpectrumPlotStyle`  
`struct FAudioSpectrumPlotStyle : public FSlateWidgetStyle`  
_L17-57_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an SAudioSpectrumPlot
- L21 _public prototype_ `FAudioSpectrumPlotStyle();`
- L23 _public prototype_ `virtual ~FAudioSpectrumPlotStyle() = default;`
- L25 _public member_ `static const FName TypeName;`
- L26 _public function_ `virtual const FName GetTypeName() const override`
- L28 _public prototype_ `static const FAudioSpectrumPlotStyle& GetDefault();`
- L31 _public member_ `FSlateColor BackgroundColor = FStyleColors::Background;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L32 _public function_ `FAudioSpectrumPlotStyle& SetBackgroundColor(const FSlateColor& InBackgroundColor)`
- L35 _public member_ `FSlateColor GridColor = FMath::Lerp(FStyleColors::Background.GetSpecifiedColor(), FStyleColors::Foreground.GetSpecifiedColor(), 0.1f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L36 _public function_ `FAudioSpectrumPlotStyle& SetGridColor(const FSlateColor& InGridColor)`
- L39 _public member_ `FSlateColor AxisLabelColor = FStyleColors::Foreground;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L40 _public function_ `FAudioSpectrumPlotStyle& SetAxisLabelColor(const FSlateColor& InAxisLabelColor)`
- L43 _public member_ `FSlateFontInfo AxisLabelFont = FStyleDefaults::GetFontInfo(5);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L44 _public function_ `FAudioSpectrumPlotStyle& SetAxisLabelFont(const FSlateFontInfo& InAxisLabelFont)`
- L47 _public member_ `FSlateColor SpectrumColor = FStyleColors::Foreground;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L48 _public function_ `FAudioSpectrumPlotStyle& SetSpectrumColor(const FSlateColor& InSpectrumColor)`
- L51 _public member_ `FSlateColor CrosshairColor = FStyleColors::Foreground;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L52 _public function_ `FAudioSpectrumPlotStyle& SetCrosshairColor(const FSlateColor& InCrosshairColor)`
- L55 _public member_ `FSlateFontInfo CrosshairLabelFont = FStyleDefaults::GetFontInfo(8);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L56 _public function_ `FAudioSpectrumPlotStyle& SetCrosshairLabelFont(const FSlateFontInfo& InCrosshairLabelFont)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioVectorscope.h` (Public)


#### class `AudioWidgets::FAudioVectorscope`  
`class FAudioVectorscope : public IAudioAnalyzerRackUnit`  
_L21-63_
- inherits: `IAudioAnalyzerRackUnit`
- L24 _public member_ `static const FAudioAnalyzerRackUnitTypeInfo RackUnitTypeInfo;`
- L26 _public prototype_ `FAudioVectorscope(Audio::FDeviceId InAudioDeviceId, const uint32 InNumChannels, const float InTimeWindowMs, const float InMaxTimeWindowMs, const float InAnalysisPeriodMs, const EAudioPanelLayoutType InPanelLayoutType, const FAudioVectorscopePanelStyle* PanelStyle = nullptr, TObjectPtr<UAudioBus> InExternalAudioBus = nullptr);`
- L35 _public prototype_ `void CreateAudioBus(const uint32 InNumChannels);`
- L36 _public prototype_ `void CreateDataProvider(Audio::FDeviceId InAudioDeviceId, const float InTimeWindowMs, const float InMaxTimeWindowMs, const float InAnalysisPeriodMs);`
- L37 _public prototype_ `void CreateVectorscopeWidget(const EAudioPanelLayoutType InPanelLayoutType, const FAudioVectorscopePanelStyle* PanelStyle = nullptr);`
- L39 _public prototype_ `virtual void StartProcessing() override;`
- L40 _public prototype_ `virtual void StopProcessing() override;`
- L42 _public prototype_ `UAudioBus* GetAudioBus() const;`
- L43 _public prototype_ `TSharedRef<SWidget> GetPanelWidget() const;`
- L46 _public prototype_ `virtual void SetAudioBusInfo(const FAudioBusInfo& AudioBusInfo) override;`
- L47 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args) const override;`
- L51 _private prototype_ `static TSharedRef<IAudioAnalyzerRackUnit> MakeRackUnit(const FAudioAnalyzerRackUnitConstructParams& Params);`
- L52 _private member_ `static constexpr float RackUnitTimeWindowMs = 30.0f;`
- L53 _private member_ `static constexpr float RackUnitMaxTimeWindowMs = 30.0f;`
- L54 _private member_ `static constexpr float RackUnitAnalysisPeriodMs = 10.0f;`
- L55 _private member_ `static constexpr EAudioPanelLayoutType RackUnitPanelLayoutType = EAudioPanelLayoutType::Basic;`
- L57 _private member_ `FAudioVectorscopePanelStyle VectorscopePanelStyle;`
- L59 _private member_ `TSharedPtr<FWaveformAudioSamplesDataProvider> AudioSamplesDataProvider = nullptr;`
- L60 _private member_ `TSharedPtr<SAudioVectorscopePanelWidget> VectorscopePanelWidget = nullptr;`
- L62 _private member_ `TStrongObjectPtr<UAudioBus> AudioBus = nullptr;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L17 _namespace_ `namespace AudioWidgets`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioVectorscopePanelStyle.h` (Public)


#### struct `FAudioVectorscopePanelStyle`  
`struct FAudioVectorscopePanelStyle : public FSlateWidgetStyle`  
_L20-55_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an SAudioVectorscopePanelWidget
- L24 _public function_ `FAudioVectorscopePanelStyle()`
- L36 _public prototype_ `virtual ~FAudioVectorscopePanelStyle() = default;`
- L38 _public function_ `virtual const FName GetTypeName() const override`
- L39 _public function_ `static const FAudioVectorscopePanelStyle& GetDefault()`
- L43 _public member_ `FSampledSequenceValueGridOverlayStyle ValueGridStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The value grid style.
- L44 _public function_ `FAudioVectorscopePanelStyle& SetValueGridStyle(const FSampledSequenceValueGridOverlayStyle& InValueGridStyle)`
- L48 _public member_ `FSampledSequenceVectorViewerStyle VectorViewerStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The vector view style.
- L49 _public function_ `FAudioVectorscopePanelStyle& SetVectorViewerStyle(const FSampledSequenceVectorViewerStyle& InVectorViewerStyle)`
- L51 _public member_ `inline static FName TypeName = FName("FAu`
- L53 _public member_ `static FOnNewValueGridOverlayStyle OnNewValueGridOverlayStyle;`
- L54 _public member_ `static FOnNewVectorViewerStyle OnNewVectorViewerStyle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewValueGridOverlayStyle, FSampledSequenceValueGridOverlayStyle) DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewVectorViewerStyle, FSampledSequenceVectorViewerStyle) USTRUCT(BlueprintType) struct FAudioVectorscopePanelStyle : public FSlateWidgetStyle { GENERATED_USTRUCT_BODY() FAudioVectorscopePanelStyle() { ValueGridStyle = FSampledSequenceValueGridOverlayStyle() .SetGridColor(FLinearColor(0.05f, 0.05f, 0.05f, 0.5f)) .SetGridThickness(1.0f); VectorViewerStyle = FSampledSequenceVectorViewerStyle() .SetBackgroundColor(FLinearColor(0.00273f, 0.00478f, 0.00368f, 1.0f)) .SetLineColor(FLinearColor(0.0075f, 0.57758f, 0.05448f, 1.0f)) .SetLineThickness(2.5f); } virtual ~FAudioVectorscopePanelStyle() = default; virtual const FName GetTypeName() const override { return TypeName; } static const FAudioVectorscopePanelStyle& GetDefault() { static FAudioVectorscopePanelStyle Default; return Default; } UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance) FSampledSequenceValueGridOverlayStyle ValueGridStyle; FAudioVectorscopePanelStyle& SetValueGridStyle(const FSampledSequenceValueGridOverlayStyle& InValueGridStyle) { ValueGridStyle = InValueGridStyle; return *this; } UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance) FSampledSequenceVectorViewerStyle VectorViewerStyle; FAudioVectorscopePanelStyle& SetVectorViewerStyle(const FSampledSequenceVectorViewerStyle& InVectorViewerStyle) { VectorViewerStyle = InVectorViewerStyle; retur`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewVectorViewerStyle, FSampledSequenceVectorViewerStyle) USTRUCT(BlueprintType) struct FAudioVectorscopePanelStyle : public FSlateWidgetStyle { GENERATED_USTRUCT_BODY() FAudioVectorscopePanelStyle() { ValueGridStyle = FSampledSequenceValueGridOverlayStyle() .SetGridColor(FLinearColor(0.05f, 0.05f, 0.05f, 0.5f)) .SetGridThickness(1.0f); VectorViewerStyle = FSampledSequenceVectorViewerStyle() .SetBackgroundColor(FLinearColor(0.00273f, 0.00478f, 0.00368f, 1.0f)) .SetLineColor(FLinearColor(0.0075f, 0.57758f, 0.05448f, 1.0f)) .SetLineThickness(2.5f); } virtual ~FAudioVectorscopePanelStyle() = default; virtual const FName GetTypeName() const override { return TypeName; } static const FAudioVectorscopePanelStyle& GetDefault() { static FAudioVectorscopePanelStyle Default; return Default; } UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance) FSampledSequenceValueGridOverlayStyle ValueGridStyle; FAudioVectorscopePanelStyle& SetValueGridStyle(const FSampledSequenceValueGridOverlayStyle& InValueGridStyle) { ValueGridStyle = InValueGridStyle; return *this; } UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance) FSampledSequenceVectorViewerStyle VectorViewerStyle; FAudioVectorscopePanelStyle& SetVectorViewerStyle(const FSampledSequenceVectorViewerStyle& InVectorViewerStyle) { VectorViewerStyle = InVectorViewerStyle; return *this; } inline static FName TypeName = FName("FAudioVectorscopePanelStyle"); static FOnNewValueGridOv`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioVectorscopeUMG.h` (Public)


#### class `UAudioVectorscope`  
`class UAudioVectorscope: public UWidget`  
_L25-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: A vectorscope UMG widget. Supports displaying waveforms in 2D (Left channel X axis, Right channel Y axis) from incoming audio samples.
- L30 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<float>, FGetVectorscopeAudioSamples);`
- L33 _public prototype_ `virtual void SynchronizeProperties() override;` — UWidget overrides
- L34 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L37 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L42 _public prototype_ `void StartProcessing();` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Vectorscope")` — Starts the vectorscope processing.
- L46 _public prototype_ `void StopProcessing();` — `UFUNCTION(BlueprintCallable, Category = "Audio Widgets| Vectorscope")` — Stops the vectorscope processing.
- L50 _public member_ `FAudioVectorscopePanelStyle VectorscopeStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Style", meta=(DisplayName="Style"))` — The vectorscope panel style
- L54 _public member_ `TObjectPtr<UAudioBus> AudioBus = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vectorscope Values", meta = (DesignerRebuild = "True"))` — The audio bus used to obtain audio samples for the vectorscope
- L58 _public member_ `bool bShowGrid = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vectorscope Values")` — Show/Hide the vectorscope grid.
- L62 _public member_ `int32 GridDivisions = 2;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vectorscope Values", meta = (UIMin = 1, UIMax = 6, ClampMin = 1, ClampMax = 6))` — The number of grid divisions.
- L66 _public member_ `float MaxDisplayPersistenceMs = 500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vectorscope Values", meta = (UIMin = 10.0, UIMax = 500.0, ClampMin = 10.0, ClampMax = 500.0))` — The max where the audio samples should persist in the screen (in milliseconds).
- L70 _public member_ `float DisplayPersistenceMs = 60.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vectorscope Values", meta = (UIMin = 10.0, ClampMin = 10.0))` — For how long the audio samples should persist in the screen (in milliseconds).
- L74 _public member_ `float Scale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vectorscope Values", meta = (UIMin = 0.0, UIMax = 1.0, ClampMin = 0.0, ClampMax = 1.0))` — The scale for the displayed audio samples.
- L78 _public member_ `EAudioPanelLayoutType PanelLayoutType = EAudioPanelLayoutType::Basic;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vectorscope Values", meta = (DesignerRebuild = "True"))` — Show/Hide advanced panel layout.
- L81 _private prototype_ `void CreateDummyVectorscopeWidget();`
- L82 _private prototype_ `void CreateDataProvider();`
- L83 _private prototype_ `void CreateVectorscopeWidget();`
- L86 _private prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget overrides
- L88 _private member_ `static constexpr float AnalysisPeriodMs = 10.0f;`
- L91 _private member_ `TSharedPtr<AudioWidgets::FWaveformAudioSamplesDataProvider> AudioSamplesDataProvider;` — The underlying audio samples data provider
- L94 _private member_ `TSharedPtr<SAudioVectorscopePanelWidget> VectorscopePanelWidget;` — Native Slate Widget
- L97 _private member_ `TArray<float> DummyAudioSamples;` — Dummy waveform data to display if audio bus is not set
- L98 _private member_ `FFixedSampledSequenceView DummyDataView;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L15 _namespace_ `namespace AudioWidgets`
- L30 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal(TArray<float>, FGetVectorscopeAudioSamples);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioWidgets.h` (Public)


#### class `FAudioWidgetsModule`  
`class FAudioWidgetsModule : public IModuleInterface`  
_L12-22_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `void RegisterAudioAnalyzerRackUnitType(const AudioWidgets::FAudioAnalyzerRackUnitTypeInfo* RackUnitTypeInfo);` — Register a custom audio analyzer rack unit type

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AudioWidgets`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioWidgetsEnums.h` (Public)


#### enum `EAudioPanelLayoutType`  
`enum class EAudioPanelLayoutType : uint8`  
_L8-12_
- reflection: `UENUM(BlueprintType)`
- L10 _public enumerator_ `Basic UMETA(DisplayName = "Basic")`
- L11 _public enumerator_ `Advanced UMETA(DisplayName = "Advanced")`

#### enum `EAudioUnitsValueType`  
`enum class EAudioUnitsValueType : uint8`  
_L15-20_
- reflection: `UENUM()`
- L17 _public enumerator_ `Linear`
- L18 _public enumerator_ `Frequency UMETA(DisplayName = "Frequency (Log)")`
- L19 _public enumerator_ `Volume`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioWidgetsLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioWidgets, Log, All);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioWidgetsSlateTypes.h` (Public)


#### struct `FAudioTextBoxStyle`  
`struct FAudioTextBoxStyle : public FSlateWidgetStyle`  
_L16-49_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an Audio Text Box
- L20 _public prototype_ `FAudioTextBoxStyle();`
- L22 _public prototype_ `virtual ~FAudioTextBoxStyle() = default;`
- L24 _public prototype_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;`
- L26 _public member_ `static const FName TypeName;`
- L27 _public function_ `virtual const FName GetTypeName() const override`
- L29 _public prototype_ `static const FAudioTextBoxStyle& GetDefault();`
- L33 _public member_ `FSlateBrush BackgroundImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image for the label border
- L34 _public function_ `FAudioTextBoxStyle& SetBackgroundImage(const FSlateBrush& InBackgroundImage)`
- L38 _public member_ `FSlateColor BackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Color used to draw the label background
- L39 _public function_ `FAudioTextBoxStyle& SetBackgroundColor(const FSlateColor& InBackgroundColor)`
- L45 _public function_ `void UnlinkColors()` — Unlinks all colors in this style. @see FSlateColor::Unlink

#### struct `FAudioSliderStyle`  
`struct FAudioSliderStyle : public FSlateWidgetStyle`  
_L55-123_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an Audio Slider
- L59 _public prototype_ `FAudioSliderStyle();`
- L61 _public prototype_ `virtual ~FAudioSliderStyle() = default;`
- L63 _public prototype_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;`
- L65 _public member_ `static const FName TypeName;`
- L66 _public function_ `virtual const FName GetTypeName() const override`
- L68 _public prototype_ `static const FAudioSliderStyle& GetDefault();`
- L72 _public member_ `FSliderStyle SliderStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The style to use for the underlying SSlider.
- L73 _public function_ `FAudioSliderStyle& SetSliderStyle(const FSliderStyle& InSliderStyle)`
- L77 _public member_ `FAudioTextBoxStyle TextBoxStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The style to use for the audio text box widget.
- L78 _public function_ `FAudioSliderStyle& SetTextBoxStyle(const FAudioTextBoxStyle& InTextBoxStyle)`
- L82 _public member_ `FSlateBrush WidgetBackgroundImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Image for the widget background
- L83 _public function_ `FAudioSliderStyle& SetWidgetBackgroundImage(const FSlateBrush& InWidgetBackgroundImage)`
- L87 _public member_ `FSlateColor SliderBackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Color used to draw the slider background
- L88 _public function_ `FAudioSliderStyle& SetSliderBackgroundColor(const FSlateColor& InSliderBackgroundColor)`
- L92 _public member_ `FVector2D SliderBackgroundSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Size of the slider background (slider default is vertical)
- L93 _public function_ `FAudioSliderStyle& SetSliderBackgroundSize(const FVector2D& InSliderBackgroundSize)`
- L97 _public member_ `float LabelPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Size of the padding between the label and the slider
- L98 _public function_ `FAudioSliderStyle& SetLabelPadding(const float& InLabelPadding)`
- L102 _public member_ `FSlateColor SliderBarColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Color used to draw the slider bar
- L103 _public function_ `FAudioSliderStyle& SetSliderBarColor(const FSlateColor& InSliderBarColor)`
- L107 _public member_ `FSlateColor SliderThumbColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Color used to draw the slider thumb (handle)
- L108 _public function_ `FAudioSliderStyle& SetSliderThumbColor(const FSlateColor& InSliderThumbColor)`
- L112 _public member_ `FSlateColor WidgetBackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Color used to draw the widget background
- L113 _public function_ `FAudioSliderStyle& SetWidgetBackgroundColor(const FSlateColor& InWidgetBackgroundColor)`
- L119 _public function_ `void UnlinkColors()` — Unlinks all colors in this style. @see FSlateColor::Unlink

#### struct `FAudioRadialSliderStyle`  
`struct FAudioRadialSliderStyle : public FSlateWidgetStyle`  
_L130-174_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an Audio Radial Slider
- L134 _public prototype_ `FAudioRadialSliderStyle();`
- L136 _public prototype_ `virtual ~FAudioRadialSliderStyle() = default;`
- L138 _public function_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override`
- L140 _public member_ `static const FName TypeName;`
- L141 _public function_ `virtual const FName GetTypeName() const override`
- L143 _public prototype_ `static const FAudioRadialSliderStyle& GetDefault();`
- L147 _public member_ `FAudioTextBoxStyle TextBoxStyle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The style to use for the audio text box widget.
- L148 _public function_ `FAudioRadialSliderStyle& SetTextBoxStyle(const FAudioTextBoxStyle& InTextBoxStyle)`
- L152 _public member_ `FSlateColor CenterBackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Color used to draw the slider center background
- L153 _public function_ `FAudioRadialSliderStyle& SetCenterBackgroundColor(const FSlateColor& InCenterBackgroundColor)`
- L157 _public member_ `FSlateColor SliderBarColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Color used to draw the unprogressed slider bar
- L158 _public function_ `FAudioRadialSliderStyle& SetSliderBarColor(const FSlateColor& InSliderBarColor)`
- L162 _public member_ `FSlateColor SliderProgressColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Color used to draw the progress bar
- L163 _public function_ `FAudioRadialSliderStyle& SetSliderProgressColor(const FSlateColor& InSliderProgressColor)`
- L167 _public member_ `float LabelPadding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Size of the padding between the label and the slider
- L168 _public function_ `FAudioRadialSliderStyle& SetLabelPadding(const float& InLabelPadding)`
- L172 _public member_ `float DefaultSliderRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — Default size of the slider itself (not including label)
- L173 _public function_ `FAudioRadialSliderStyle& SetDefaultSliderRadius(const float& InDefaultSliderRadius)`

#### struct `FSampledSequenceViewerStyle`  
`struct FSampledSequenceViewerStyle : public FSlateWidgetStyle`  
_L180-235_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of a Sampled Sequence Viewer
- L184 _public prototype_ `FSampledSequenceViewerStyle();`
- L186 _public prototype_ `static const FSampledSequenceViewerStyle& GetDefault();`
- L187 _public function_ `virtual const FName GetTypeName() const override`
- L188 _public prototype_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;`
- L190 _public member_ `static const FName TypeName;`
- L193 _public member_ `FSlateColor SequenceColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L194 _public function_ `FSampledSequenceViewerStyle& SetSequenceColor(const FSlateColor InSequenceColor)`
- L197 _public member_ `float SequenceLineThickness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L198 _public function_ `FSampledSequenceViewerStyle& SetSequenceLineThickness(const float InSequenceLineThickness)`
- L201 _public member_ `FSlateColor MajorGridLineColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L202 _public function_ `FSampledSequenceViewerStyle& SetMajorGridLineColor(const FSlateColor InMajorGridLineColor)`
- L205 _public member_ `FSlateColor MinorGridLineColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L206 _public function_ `FSampledSequenceViewerStyle& SetMinorGridLineColor(const FSlateColor InMinorGridLineColor)`
- L209 _public member_ `FSlateColor ZeroCrossingLineColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L210 _public function_ `FSampledSequenceViewerStyle& SetZeroCrossingLineColor(const FSlateColor InZeroCrossingLineColor)`
- L213 _public member_ `float ZeroCrossingLineThickness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L214 _public function_ `FSampledSequenceViewerStyle& SetZeroCrossingLineThickness(const float InZeroCrossingLineThickness)`
- L217 _public member_ `float SampleMarkersSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L218 _public function_ `FSampledSequenceViewerStyle& SetSampleMarkersSize(const float InSampleMarkersSize)`
- L221 _public member_ `FSlateColor SequenceBackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L222 _public function_ `FSampledSequenceViewerStyle& SetBackgroundColor(const FSlateColor InBackgroundColor)`
- L225 _public member_ `FSlateBrush BackgroundBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L226 _public function_ `FSampledSequenceViewerStyle& SetBackgroundBrush(const FSlateBrush InBackgroundBrush)`
- L229 _public member_ `float DesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L230 _public function_ `FSampledSequenceViewerStyle& SetDesiredWidth(const float InDesiredWidth)`
- L233 _public member_ `float DesiredHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L234 _public function_ `FSampledSequenceViewerStyle& SetDesiredHeight(const float InDesiredHeight)`

#### struct `FPlayheadOverlayStyle`  
`struct FPlayheadOverlayStyle : public FSlateWidgetStyle`  
_L241-267_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of a Waveform Viewer Overlay style
- L245 _public prototype_ `FPlayheadOverlayStyle();`
- L247 _public prototype_ `static const FPlayheadOverlayStyle& GetDefault();`
- L248 _public function_ `virtual const FName GetTypeName() const override`
- L250 _public member_ `static const FName TypeName;`
- L253 _public member_ `FSlateColor PlayheadColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L254 _public function_ `FPlayheadOverlayStyle& SetPlayheadColor(const FSlateColor InPlayheadColor)`
- L257 _public member_ `float PlayheadWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L258 _public function_ `FPlayheadOverlayStyle& SetPlayheadWidth(const float InPlayheadWidth)`
- L261 _public member_ `float DesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L262 _public function_ `FPlayheadOverlayStyle& SetDesiredWidth(const float InDesiredWidth)`
- L265 _public member_ `float DesiredHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L266 _public function_ `FPlayheadOverlayStyle& SetDesiredHeight(const float InDesiredHeight)`

#### struct `FFixedSampleSequenceRulerStyle`  
`struct FFixedSampleSequenceRulerStyle : public FSlateWidgetStyle`  
_L273-329_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of a Sampled Sequence Time Ruler
- L277 _public prototype_ `FFixedSampleSequenceRulerStyle();`
- L279 _public prototype_ `static const FFixedSampleSequenceRulerStyle& GetDefault();`
- L280 _public function_ `virtual const FName GetTypeName() const override`
- L281 _public prototype_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override;`
- L283 _public member_ `static const FName TypeName;`
- L286 _public member_ `float HandleWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L287 _public function_ `FFixedSampleSequenceRulerStyle& SetHandleWidth(const float InHandleWidth)`
- L290 _public member_ `FSlateColor HandleColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L291 _public function_ `FFixedSampleSequenceRulerStyle& SetHandleColor(const FSlateColor& InHandleColor)`
- L294 _public member_ `FSlateBrush HandleBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L295 _public function_ `FFixedSampleSequenceRulerStyle& SetHandleBrush(const FSlateBrush& InHandleBrush)`
- L298 _public member_ `FSlateColor TicksColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L299 _public function_ `FFixedSampleSequenceRulerStyle& SetTicksColor(const FSlateColor& InTicksColor)`
- L302 _public member_ `FSlateColor TicksTextColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L303 _public function_ `FFixedSampleSequenceRulerStyle& SetTicksTextColor(const FSlateColor& InTicksTextColor)`
- L306 _public member_ `FSlateFontInfo TicksTextFont;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L307 _public function_ `FFixedSampleSequenceRulerStyle& SetTicksTextFont(const FSlateFontInfo& InTicksTextFont)`
- L308 _public function_ `FFixedSampleSequenceRulerStyle& SetFontSize(const float InFontSize)`
- L311 _public member_ `float TicksTextOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L312 _public function_ `FFixedSampleSequenceRulerStyle& SetTicksTextOffset(const float InTicksTextOffset)`
- L315 _public member_ `FSlateColor BackgroundColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L316 _public function_ `FFixedSampleSequenceRulerStyle& SetBackgroundColor(const FSlateColor& InBackgroundColor)`
- L319 _public member_ `FSlateBrush BackgroundBrush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L320 _public function_ `FFixedSampleSequenceRulerStyle& SetBackgroundBrush(const FSlateBrush& InBackgroundBrush)`
- L323 _public member_ `float DesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L324 _public function_ `FFixedSampleSequenceRulerStyle& SetDesiredWidth(const float InDesiredWidth)`
- L327 _public member_ `float DesiredHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L328 _public function_ `FFixedSampleSequenceRulerStyle& SetDesiredHeight(const float InDesiredHeight)`

#### struct `FSampledSequenceValueGridOverlayStyle`  
`struct FSampledSequenceValueGridOverlayStyle : public FSlateWidgetStyle`  
_L335-371_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of a Sampled Sequence Value Grid Overlay
- L339 _public prototype_ `FSampledSequenceValueGridOverlayStyle();`
- L341 _public prototype_ `static const FSampledSequenceValueGridOverlayStyle& GetDefault();`
- L342 _public function_ `virtual const FName GetTypeName() const override`
- L344 _public member_ `static const FName TypeName;`
- L347 _public member_ `FSlateColor GridColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L348 _public function_ `FSampledSequenceValueGridOverlayStyle& SetGridColor(const FSlateColor InGridColor)`
- L351 _public member_ `float GridThickness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L352 _public function_ `FSampledSequenceValueGridOverlayStyle& SetGridThickness(const float InGridThickness)`
- L355 _public member_ `FSlateColor LabelTextColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L356 _public function_ `FSampledSequenceValueGridOverlayStyle& SetLabelTextColor(const FSlateColor& InLabelTextColor)`
- L359 _public member_ `FSlateFontInfo LabelTextFont;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L360 _public function_ `FSampledSequenceValueGridOverlayStyle& SetLabelTextFont(const FSlateFontInfo& InLabelTextFont)`
- L361 _public function_ `FSampledSequenceValueGridOverlayStyle& SetLabelTextFontSize(const float InFontSize)`
- L364 _public member_ `float DesiredWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L365 _public function_ `FSampledSequenceValueGridOverlayStyle& SetDesiredWidth(const float InDesiredWidth)`
- L368 _public member_ `float DesiredHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L369 _public function_ `FSampledSequenceValueGridOverlayStyle& SetDesiredHeight(const float InDesiredHeight)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioWidgetsStyle.h` (Public)


#### class `FAudioWidgetsStyle`  
`class FAudioWidgetsStyle : public FSlateStyleSet`  
_L12-28_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for audio widgets
- L17 _public member_ `static FName StyleName;`
- L20 _public prototype_ `static FAudioWidgetsStyle& Get();` — Access the singleton instance for this style set
- L23 _private prototype_ `void SetResources();`
- L24 _private prototype_ `void SetupStyles();`
- L26 _private prototype_ `FAudioWidgetsStyle();`
- L27 _private prototype_ `~FAudioWidgetsStyle();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/AudioWidgetsUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AudioWidgetsUtils`
- L9 _typedef_ `typedef FReply(SWidget::* WidgetMouseInputFunction)(const FGeometry&, const FPointerEvent&);` (scope `AudioWidgetsUtils`)
- L16 _prototype_ `FReply RouteMouseInput(WidgetMouseInputFunction InputFunction, const FPointerEvent& MouseEvent, TArrayView<TSharedPtr<SWidget>> WidgetsStack, const bool bReverse = false);` (scope `AudioWidgetsUtils`) — Propagates mouse input through an array of widget until that input is handled or all the elements have been iterated
- L22 _prototype_ `FCursorReply RouteCursorQuery(const FPointerEvent& CursorEvent, TArrayView<const TSharedPtr<SWidget>> WidgetsStack, const bool bReverse = false);` (scope `AudioWidgetsUtils`) — Propagates a cursor query through an array of widget until that input is handled or all the elements have been iterated

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/FixedSampledSequenceGridData.h` (Public)


#### class `FFixedSampledSequenceGridData`  
`class FFixedSampledSequenceGridData : public IFixedSampledSequenceGridService`  
_L16-46_
- inherits: `IFixedSampledSequenceGridService`
- L19 _public prototype_ `explicit FFixedSampledSequenceGridData(const uint32 InTotalFrames, const uint32 InSampleRateHz, const FSlateFontInfo& InTicksTimeFont, const float InGridSizePixels = 1.f);`
- L22 _public prototype_ `explicit FFixedSampledSequenceGridData(const uint32 InTotalFrames, const uint32 InSampleRateHz, const float InGridSizePixels = 1.f, const FSlateFontInfo* InTicksTimeFont = nullptr);` — `UE_DEPRECATED(5.4, "Constructor taking a const FSlateFontInfo* is deprecated, use the one taking a refrence instead")`
- L25 _public prototype_ `void UpdateDisplayRange(const TRange<uint32> InDisplayRange);`
- L26 _public prototype_ `bool UpdateGridMetrics(const float InGridSizePixels);`
- L27 _public prototype_ `virtual const FFixedSampledSequenceGridMetrics GetGridMetrics() const override;`
- L28 _public prototype_ `void SetTicksTimeFont(const FSlateFontInfo& InNewFont);`
- L31 _public prototype_ `void SetTicksTimeFont(const FSlateFontInfo* InNewFont);` — `UE_DEPRECATED(5.4, "SetTicksTimeFont taking a const FSlateFontInfo* is deprecated, use the one taking a refrence instead")`
- L34 _public prototype_ `const float SnapPositionToClosestFrame(const float InPixelPosition) const;`
- L36 _public member_ `FOnWaveformEditorGridUpdated OnGridMetricsUpdated;`
- L39 _private member_ `FFixedSampledSequenceGridMetrics GridMetrics;`
- L40 _private member_ `uint32 TotalFrames = 0;`
- L41 _private member_ `TRange<uint32> DisplayRange;`
- L43 _private member_ `float GridSizePixels = 0.f;`
- L44 _private member_ `FSlateFontInfo TicksTimeFont;`
- L45 _private member_ `FFrameRate GridFrameRate;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWaveformEditorGridUpdated) class FFixedSampledSequenceGridData : public IFixedSampledSequenceGridService { public: explicit FFixedSampledSequenceGridData(const uint32 InTotalFrames, const uint32 InSampleRateHz, const FSlateFontInfo& InTicksTimeFont, const float InGridSizePixels = 1.f); UE_DEPRECATED(5.4, "Constructor taking a const FSlateFontInfo* is deprecated, use the one taking a refrence instead") explicit FFixedSampledSequenceGridData(const uint32 InTotalFrames, const uint32 InSampleRateHz, const float InGridSizePixels = 1.f, const FSlateFontInfo* InTicksTimeFont = nullptr); void UpdateDisplayRange(const TRange<uint32> InDisplayRange); bool UpdateGridMetrics(const float InGridSizePixels); virtual const FFixedSampledSequenceGridMetrics GetGridMetrics() const override; void SetTicksTimeFont(const FSlateFontInfo& InNewFont); UE_DEPRECATED(5.4, "SetTicksTimeFont taking a const FSlateFontInfo* is deprecated, use the one taking a refrence instead") void SetTicksTimeFont(const FSlateFontInfo* InNewFont); const float SnapPositionToClosestFrame(const float InPixelPosition) const; FOnWaveformEditorGridUpdated OnGridMetricsUpdated; private: FFixedSampledSequenceGridMetrics GridMetrics; uint32 TotalFrames = 0; TRange<uint32> DisplayRange; float GridSizePixels = 0.f; FSlateFontInfo TicksTimeFont; FFrameRate GridFrameRate; };`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/FixedSampledSequenceView.h` (Public)


#### struct `FFixedSampledSequenceView`  
`struct FFixedSampledSequenceView`  
_L7-12_
- L9 _public member_ `TArrayView<const float> SampleData;`
- L10 _public member_ `uint32 NumDimensions = 0;`
- L11 _public member_ `uint32 SampleRate = 0;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/IFixedSampledSequenceGridService.h` (Public)


#### struct `FFixedSampledSequenceGridMetrics`  
`struct FFixedSampledSequenceGridMetrics`  
_L7-15_
- L9 _public member_ `int32 NumMinorGridDivisions = 0;`
- L10 _public member_ `uint32 SampleRate = 0;`
- L11 _public member_ `uint32 StartFrame = 0;`
- L12 _public member_ `double PixelsPerFrame = 0;`
- L13 _public member_ `double FirstMajorTickX = 0;`
- L14 _public member_ `double MajorGridXStep = 0;`

#### class `IFixedSampledSequenceGridService`  
`class IFixedSampledSequenceGridService`  
_L17-23_
- L20 _public prototype_ `virtual ~IFixedSampledSequenceGridService() = default;`
- L21 _public prototype_ `virtual const FFixedSampledSequenceGridMetrics GetGridMetrics() const = 0;`
- L22 _public prototype_ `virtual const float SnapPositionToClosestFrame(const float InPixelPosition) const = 0;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/IFixedSampledSequenceViewProvider.h` (Public)


#### class `IFixedSampledSequenceViewProvider`  
`class IFixedSampledSequenceViewProvider`  
_L8-13_
- L11 _public prototype_ `virtual ~IFixedSampledSequenceViewProvider() = default;`
- L12 _public prototype_ `virtual FFixedSampledSequenceView RequestSequenceView(const TRange<double> DataRatioRange) = 0;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/IFixedSampledSequenceViewReceiver.h` (Public)


#### class `IFixedSampledSequenceViewReceiver`  
`class IFixedSampledSequenceViewReceiver`  
_L7-18_
- L10 _public prototype_ `virtual ~IFixedSampledSequenceViewReceiver() = default;`
- L17 _public prototype_ `virtual void ReceiveSequenceView(const FFixedSampledSequenceView InView, const uint32 FirstSampleIndex = 0) = 0;` — Receives and handles a sequence view. @param InView Received view for a Fixed Sampled Sequence @param FirstSampleIndex the index of the first sample shown by the view

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/ISparseSampledSequenceTransportCoordinator.h` (Public)


#### class `ISparseSampledSequenceTransportCoordinator`  
`class ISparseSampledSequenceTransportCoordinator`  
_L7-23_
- L10 _public prototype_ `virtual ~ISparseSampledSequenceTransportCoordinator() = default;`
- L12 _public prototype_ `virtual const TRange<double> GetDisplayRange() const = 0;`
- L13 _public prototype_ `virtual const double GetFocusPoint() const = 0;`
- L14 _public prototype_ `virtual void ScrubFocusPoint(const float InTargetFocusPoint, const bool bIsMoving) = 0;`
- L15 _public prototype_ `virtual const bool IsScrubbing() const = 0;`
- L17 _public prototype_ `virtual void SetProgressRatio(const float NewRatio) = 0;`
- L18 _public prototype_ `virtual void SetZoomRatio(const float NewRatio) = 0;`
- L20 _public prototype_ `virtual float ConvertAbsoluteRatioToZoomed(const float InAbsoluteRatio) const = 0;`
- L21 _public prototype_ `virtual float ConvertZoomedRatioToAbsolute(const float InZoomedRatio) const = 0;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/LoudnessMeterRackUnitSettings.h` (Public)


#### struct `FLoudnessMetricDisplayOptions`  
`struct FLoudnessMetricDisplayOptions : public FLoudnessMeterDisplayOptions`  
_L10-13_
- reflection: `USTRUCT()`
- inherits: `FLoudnessMeterDisplayOptions`

#### struct `FLoudnessMeterRackUnitSettings`  
`struct FLoudnessMeterRackUnitSettings : public FLoudnessMeterSettings`  
_L16-19_
- reflection: `USTRUCT()`
- inherits: `FLoudnessMeterSettings`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioInputWidget.h` (Public)


#### class `SAudioInputWidget`  
`class SAudioInputWidget : public SCompoundWidget`  
_L13-31_
- inherits: `SCompoundWidget`
- desc: todo make this an audio value display widget that inherits from swidget include textbox and widget ref
- L17 _public prototype_ `virtual const float GetOutputValue(const float InSliderValue) = 0;`
- L18 _public prototype_ `virtual const float GetSliderValue(const float OutputValue) = 0;`
- L23 _public prototype_ `virtual void SetSliderValue(float InSliderValue) = 0;` — Set the slider's linear (0-1 normalized) value.
- L24 _public prototype_ `virtual void SetOutputRange(const FVector2D Range) = 0;`
- L26 _public prototype_ `virtual void SetLabelBackgroundColor(FSlateColor InColor) = 0;`
- L27 _public prototype_ `virtual void SetUnitsText(const FText Units) = 0;`
- L28 _public prototype_ `virtual void SetUnitsTextReadOnly(const bool bIsReadOnly) = 0;`
- L29 _public prototype_ `virtual void SetShowUnitsText(const bool bShowUnitsText) = 0;`
- L30 _public prototype_ `virtual void SetDesiredSizeOverride(const FVector2D DesiredSize) = 0;`

#### struct `FAudioUnitProcessor`  
`struct FAudioUnitProcessor`  
_L37-66_
- desc: Processor to allow output and display of different Audio Units. This is because what is shown for the user and what the output is might not be the same. For example, when using the linear output option for volume, Volume is displayed as dB, but the output value will still be 0.0-1.0f.
- L42 _public function_ `virtual const FText GetUnitsText()` — Get the units that the processor will output
- L45 _public prototype_ `virtual const float GetOutputValue(const FVector2D OutputRange, const float InSliderValue);` — Get the OutputValue. This is where to calculate what the processor will actually output
- L48 _public prototype_ `virtual const float GetOutputValueForText(const FVector2D OutputRange, const float InSliderValue);` — Get the OutputValue that will be shown as text. This might be different then OutputValue depending on the type
- L51 _public prototype_ `virtual const float GetSliderValue(const FVector2D OutputRange, const float OutputValue);` — Get the Value for the slider. This should be clamped to be inside the given slider range
- L54 _public prototype_ `virtual const float GetSliderValueForText(const FVector2D OutputRange, const float OutputValue);` — Get the Slider value for the text. option to override what would be returned when value is set directly to the text field. The value in the text field might differ from the slider value because the slider is usally just between 0-1
- L57 _public function_ `virtual const FVector2D GetDefaultOutputRange()` — Get the default Output range for the processor. This will be used when Slate is created, and default values are set.
- L60 _public function_ `virtual const FVector2D GetOutputRange(FVector2D InRange)` — Get the OutputRange. Possibility to modify the output range. Currently only used for Volume
- L64 _protected member_ `static const FVector2D NormalizedLinearSliderRange;`

#### struct `FVolumeProcessor`  
`struct FVolumeProcessor : FAudioUnitProcessor`  
_L68-100_
- inherits: `FAudioUnitProcessor`
- L71 _public function_ `FVolumeProcessor(bool bInUseLinearOutput)`
- L73 _public prototype_ `virtual const FText GetUnitsText() override;`
- L74 _public prototype_ `virtual const FVector2D GetDefaultOutputRange() override;`
- L76 _public prototype_ `virtual const float GetOutputValue(const FVector2D OutputRange, const float InSliderValue) override;`
- L77 _public prototype_ `virtual const float GetOutputValueForText(const FVector2D OutputRange, const float InSliderValue) override;`
- L78 _public prototype_ `virtual const float GetSliderValue(const FVector2D OutputRange, const float OutputValue) override;`
- L79 _public prototype_ `virtual const float GetSliderValueForText(const FVector2D OutputRange, const float OutputValue) override;`
- L80 _public prototype_ `virtual const FVector2D GetOutputRange(const FVector2D InRange) override;`
- L87 _private prototype_ `const float GetDbValueFromSliderValue(const FVector2D OutputRange, const float InSliderValue);` — Convert the given SliderValue to dB within the given range
- L90 _private prototype_ `const float GetSliderValueFromDb(const FVector2D OutputRange, const float DbValue);` — Convert decibels to linear 0-1 space
- L95 _private member_ `static const float MinDbValue;` — Min/max possible values for output range, derived to avoid Audio::ConvertToLinear/dB functions returning NaN
- L96 _private member_ `static const float MaxDbValue;`
- L99 _private member_ `bool bUseLinearOutput;` — Use linear (converted from dB, not normalized) output value. Only applies to the output value reported by GetOutputValue(); the text displayed will still be in decibels.

#### struct `FFrequencyProcessor`  
`struct FFrequencyProcessor : FAudioUnitProcessor`  
_L102-109_
- inherits: `FAudioUnitProcessor`
- L104 _public prototype_ `virtual const FText GetUnitsText() override;`
- L105 _public prototype_ `virtual const FVector2D GetDefaultOutputRange() override;`
- L107 _public prototype_ `virtual const float GetOutputValue(const FVector2D OutputRange, const float InSliderValue) override;`
- L108 _public prototype_ `virtual const float GetSliderValue(const FVector2D OutputRange, const float OutputValue) override;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioMeter.h` (Public)


#### class `SAudioMeterBase`  
`class SAudioMeterBase : public SLeafWidget`  
_L18-35_
- inherits: `SLeafWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SAudioMeterBase)`
- L25 _public prototype_ `SLATE_END_ARGS() bool bIsActiveTimerRegistered = false;`
- L32 _public prototype_ `virtual void SetMeterChannelInfo(const TAttribute<TArray<FMeterChannelInfo>>& InMeterChannelInfo) = 0;`
- L33 _public prototype_ `virtual TArray<FMeterChannelInfo> GetMeterChannelInfo() const = 0;`

#### class `SAudioMeter`  
`class SAudioMeter : public SAudioMeterBase`  
_L40-128_
- inherits: `SAudioMeterBase`
- desc: A widget that displays audio channel's levels.
- L45 _public function_ `SLATE_BEGIN_ARGS(SAudioMeter) : _Orientation(EOrientation::Orient_Horizontal) , _BackgroundColor(FLinearColor::Black) , _MeterBackgroundColor(FLinearColor::Gray) , _MeterValueColor(FLinearColor::Green) , _MeterPeakColor(FLinearColor::Blue) , _MeterClippingColor(FLinearColor::Transparent) , _MeterScaleColor(FLinearColor::White) , _MeterScaleLabelColor(FLinearColor::Gray) , _Style(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioMeterStyle>("AudioMeter.Style"))`
- L59 _public prototype_ `SLATE_ATTRIBUTE(bool, IndentHandle) SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ATTRIBUTE(FSlateColor, BackgroundColor) SLATE_ATTRIBUTE(FSlateColor, MeterBackgroundColor) SLATE_ATTRIBUTE(FSlateColor, MeterValueColor) SLATE_ATTRIBUTE(FSlateColor, MeterPeakColor) SLATE_ATTRIBUTE(FSlateColor, MeterClippingColor) SLATE_ATTRIBUTE(FSlateColor, MeterScaleColor) SLATE_ATTRIBUTE(FSlateColor, MeterScaleLabelColor) SLATE_STYLE_ARGUMENT(FAudioMeterStyle, Style) SLATE_ATTRIBUTE(TArray<FMeterChannelInfo>, MeterChannelInfo) SLATE_END_ARGS() void Construct(const SAudioMeter::FArguments& InDeclaration);` — Whether the slidable area should be indented to fit the handle.
- L100 _public prototype_ `void SetMeterChannelInfo(const TAttribute<TArray<FMeterChannelInfo>>& InMeterChannelInfo) override;`
- L101 _public prototype_ `TArray<FMeterChannelInfo> GetMeterChannelInfo() const override;`
- L104 _public prototype_ `void SetOrientation(EOrientation InOrientation);` — Set the Orientation attribute
- L106 _public prototype_ `void SetBackgroundColor(FSlateColor InBackgroundColor);`
- L107 _public prototype_ `void SetMeterBackgroundColor(FSlateColor InMeterBackgroundColor);`
- L108 _public prototype_ `void SetMeterValueColor(FSlateColor InMeterValueColor);`
- L109 _public prototype_ `void SetMeterPeakColor(FSlateColor InMeterPeakColor);`
- L110 _public prototype_ `void SetMeterClippingColor(FSlateColor InMeterPeakColor);`
- L111 _public prototype_ `void SetMeterScaleColor(FSlateColor InMeterScaleColor);`
- L112 _public prototype_ `void SetMeterScaleLabelColor(FSlateColor InMeterScaleLabelColor);`
- L118 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L119 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L120 _public prototype_ `virtual bool ComputeVolatility() const override;`
- L125 _protected prototype_ `float GetScaleHeight() const;` — Returns the scale height based off font size and hash height
- L127 _protected member_ `TSharedPtr<class SAudioMeterWidget> AudioMeterWidget;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioOscilloscopePanelWidget.h` (Public)


#### enum `EXAxisLabelsUnit`  
`enum class EXAxisLabelsUnit : uint8`  
_L36-40_
- reflection: `UENUM(BlueprintType)`
- L38 _public enumerator_ `Samples UMETA(DisplayName = "Samples")`
- L39 _public enumerator_ `Seconds UMETA(DisplayName = "Seconds")`

#### enum `EYAxisLabelsUnit`  
`enum class EYAxisLabelsUnit : uint8`  
_L43-47_
- reflection: `UENUM(BlueprintType)`
- L45 _public enumerator_ `Linear UMETA(DisplayName = "Linear")`
- L46 _public enumerator_ `Db UMETA(DisplayName = "dB")`

#### class `SAudioOscilloscopePanelWidget`  
`class SAudioOscilloscopePanelWidget : public SCompoundWidget, public IFixedSampledSequenceViewReceiver`  
_L49-207_
- inherits: `SCompoundWidget,IFixedSampledSequenceViewReceiver`
- L52 _public function_ `SLATE_BEGIN_ARGS(SAudioOscilloscopePanelWidget) : _HideSequenceGrid(false) , _HideSequenceRuler(false) , _HideValueGrid(false) , _HideTriggerThresholdLine(true) , _YAxisLabelsUnit(EYAxisLabelsUnit::Linear) , _ValueGridMaxDivisionParameter(2) , _SequenceRulerDisplayUnit(EXAxisLabelsUnit::Samples) , _PanelLayoutType(EAudioPanelLayoutType::Basic) , _PanelStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioOscilloscopePanelStyle>("AudioOscilloscope.PanelStyle"))`
- L64 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, InArgs) SLATE_ATTRIBUTE(bool, HideSequenceGrid) SLATE_ATTRIBUTE(bool, HideSequenceRuler) SLATE_ATTRIBUTE(bool, HideValueGrid) SLATE_ATTRIBUTE(bool, HideTriggerThresholdLine) SLATE_ATTRIBUTE(EYAxisLabelsUnit, YAxisLabelsUnit) SLATE_ARGUMENT(uint32, ValueGridMaxDivisionParameter) SLATE_ARGUMENT(EXAxisLabelsUnit, SequenceRulerDisplayUnit) SLATE_ARGUMENT(EAudioPanelLayoutType, PanelLayoutType) SLATE_STYLE_ARGUMENT(FAudioOscilloscopePanelStyle, PanelStyle) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FFixedSampledSequenceView& InData, const int32 InNumChannels);`
- L97 _public prototype_ `void BuildWidget(const FFixedSampledSequenceView& InData, const int32 InNumChannels, const EAudioPanelLayoutType InPanelLayoutType);`
- L100 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget methods overrides
- L103 _public prototype_ `virtual void ReceiveSequenceView(const FFixedSampledSequenceView InData, const uint32 FirstSampleIndex) override;` — IFixedSampledSequenceViewReceiver Interface
- L105 _public prototype_ `void SetSequenceRulerDisplayUnit(const EXAxisLabelsUnit InDisplayUnit);`
- L106 _public prototype_ `void SetXAxisGridVisibility(const bool InbIsVisible);`
- L108 _public prototype_ `void SetValueGridOverlayDisplayUnit(const EYAxisLabelsUnit InDisplayUnit);`
- L109 _public prototype_ `void SetYAxisGridVisibility(const bool InbIsVisible);`
- L110 _public prototype_ `void SetYAxisLabelsVisibility(const bool InbIsVisible);`
- L112 _public prototype_ `void SetMaxTimeWindowMs(const float InMaxTimeWindowMs);`
- L114 _public prototype_ `void SetChannelToAnalyze(const int32 InChannelToAnalyze);`
- L115 _public prototype_ `void SetTriggerMode(const EAudioOscilloscopeTriggerMode InTriggerMode);`
- L116 _public prototype_ `void SetTriggerThreshold(const float InTriggerThreshold);`
- L117 _public prototype_ `void SetTimeWindow(const float InTimeWindow);`
- L118 _public prototype_ `void SetAnalysisPeriod(const float InAnalysisPeriod);`
- L120 _public prototype_ `void UpdateSequenceRulerStyle(const FFixedSampleSequenceRulerStyle UpdatedRulerStyle);`
- L121 _public prototype_ `void UpdateValueGridOverlayStyle(const FSampledSequenceValueGridOverlayStyle UpdatedValueGridOverlayStyle);`
- L122 _public prototype_ `void UpdateSequenceViewerStyle(const FSampledSequenceViewerStyle UpdatedSequenceViewerStyle);`
- L123 _public prototype_ `void UpdateTriggerThresholdStyle(const FTriggerThresholdLineStyle UpdatedStyle);`
- L125 _public function_ `EAudioPanelLayoutType GetPanelLayoutType()`
- L127 _public member_ `FOnSelectedChannelChanged OnSelectedChannelChanged;`
- L128 _public member_ `FOnTriggerModeChanged OnTriggerModeChanged;`
- L129 _public member_ `FOnTriggerThresholdChanged OnTriggerThresholdChanged;`
- L130 _public member_ `FOnTimeWindowValueChanged OnTimeWindowValueChanged;`
- L131 _public member_ `FOnAnalysisPeriodChanged OnAnalysisPeriodChanged;`
- L134 _private prototype_ `void CreateLayout();`
- L136 _private prototype_ `void CreateGridData(const FFixedSampleSequenceRulerStyle& RulerStyle);`
- L139 _private prototype_ `void CreateSequenceRuler(TSharedRef<FFixedSampledSequenceGridData> InGridData, const FFixedSampleSequenceRulerStyle& RulerStyle);` — Basic panel methods
- L140 _private prototype_ `void CreateBackground(const FSampledSequenceViewerStyle& ViewerStyle);`
- L141 _private prototype_ `void CreateValueGridOverlay(const uint32 MaxDivisionParameter, const SampledSequenceValueGridOverlay::EGridDivideMode DivideMode, const EYAxisLabelsUnit InValueGridOverlayDisplayUnit, const FSampledSequenceValueGridOverlayStyle& ValueGridStyle);`
- L142 _private prototype_ `void CreateSequenceViewer(TSharedRef<FFixedSampledSequenceGridData> InGridData, const FFixedSampledSequenceView& InData, const FSampledSequenceViewerStyle& ViewerStyle);`
- L143 _private prototype_ `void CreateTriggerThresholdLine(const FTriggerThresholdLineStyle& TriggerThresholdLineStyle);`
- L146 _private prototype_ `void CreateChannelCombobox();` — Advanced panel methods
- L147 _private prototype_ `void CreateTriggerModeCombobox();`
- L148 _private prototype_ `void CreateTriggerThresholdKnob();`
- L149 _private prototype_ `void CreateTimeWindowKnob();`
- L150 _private prototype_ `void CreateAnalysisPeriodKnob();`
- L151 _private prototype_ `void CreateOscilloscopeControls();`
- L153 _private member_ `const FAudioOscilloscopePanelStyle* PanelStyle = nullptr;`
- L156 _private member_ `TSharedPtr<FFixedSampledSequenceGridData> SequenceGridData;` — Basic panel widgets
- L157 _private member_ `TSharedPtr<SBorder> BackgroundBorder;`
- L158 _private member_ `TSharedPtr<SFixedSampledSequenceRuler> SequenceRuler;`
- L159 _private member_ `TSharedPtr<SFixedSampledSequenceViewer> SequenceViewer;`
- L160 _private member_ `TSharedPtr<SSampledSequenceValueGridOverlay> ValueGridOverlay;`
- L161 _private member_ `TSharedPtr<STriggerThresholdLineWidget> TriggerThresholdLineWidget;`
- L164 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ChannelCombobox;` — Advanced panel widgets
- L165 _private member_ `TArray<TSharedPtr<FString>> ChannelComboboxOptionsSource;`
- L166 _private member_ `TSharedPtr<FString> SelectedChannelPtr;`
- L168 _private member_ `TSharedPtr<SComboBox<TSharedPtr<EAudioOscilloscopeTriggerMode>>> TriggerModeCombobox;`
- L169 _private member_ `TArray<TSharedPtr<EAudioOscilloscopeTriggerMode>> TriggerModeComboboxOptionsSource;`
- L170 _private member_ `TSharedPtr<EAudioOscilloscopeTriggerMode> SelectedTriggerModePtr;`
- L172 _private member_ `TSharedPtr<SAudioRadialSlider> TriggerThresholdKnob;`
- L173 _private member_ `TSharedPtr<SAudioRadialSlider> TimeWindowKnob;`
- L174 _private member_ `TSharedPtr<SAudioRadialSlider> AnalysisPeriodKnob;`
- L176 _private member_ `inline static const FVector2D TriggerThresholdKnobOutputRange = { -1.0, 1.0 };`
- L177 _private member_ `inline static const FVector2D AnalysisPeriodKnobOutputRange = { 10.0, 1000.0 };`
- L179 _private member_ `FVector2D TimeWindowKnobOutputRange = { 10.0, 5000.0 };`
- L181 _private member_ `EAudioPanelLayoutType PanelLayoutType = EAudioPanelLayoutType::Basic;`
- L183 _private member_ `uint32 NumChannels = 0;`
- L185 _private member_ `bool bIsInputWidgetTransacting = false;`
- L187 _private member_ `float TriggerThresholdValue = 0.0f;`
- L188 _private member_ `float TimeWindowValue = 0.0f;`
- L189 _private member_ `float AnalysisPeriodValue = 0.0f;`
- L191 _private member_ `float CachedPixelWidth = 0.0f;`
- L192 _private member_ `float OscilloscopeViewProportion = 1.0f;`
- L194 _private member_ `EXAxisLabelsUnit SequenceRulerDisplayUnit;`
- L195 _private member_ `EYAxisLabelsUnit ValueGridOverlayDisplayUnit;`
- L197 _private member_ `uint32 ValueGridMaxDivisionParameter = 2;`
- L199 _private member_ `FFixedSampledSequenceView DataView;`
- L200 _private member_ `SampledSequenceDrawingUtils::FSampledSequenceDrawingParams DrawingParams;`
- L202 _private member_ `bool bHideSequenceGrid = false;`
- L203 _private member_ `bool bHideSequenceRuler = false;`
- L204 _private member_ `bool bHideValueGrid = false;`
- L206 _private member_ `bool bHideTriggerThresholdLine = true;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedChannelChanged, const int32 ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTriggerModeChanged, const EAudioOscilloscopeTriggerMode ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTriggerThresholdChanged, const float ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeWindowValueChanged, const float ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnalysisPeriodChanged, const float ) UENUM(BlueprintType) enum class EXAxisLabelsUnit : uint8 { Samples UMETA(DisplayName = "Samples"), Seconds UMETA(DisplayName = "Seconds") };`
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTriggerModeChanged, const EAudioOscilloscopeTriggerMode ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTriggerThresholdChanged, const float ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeWindowValueChanged, const float ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnalysisPeriodChanged, const float ) UENUM(BlueprintType) enum class EXAxisLabelsUnit : uint8 { Samples UMETA(DisplayName = "Samples"), Seconds UMETA(DisplayName = "Seconds") };`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTriggerThresholdChanged, const float ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeWindowValueChanged, const float ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnalysisPeriodChanged, const float ) UENUM(BlueprintType) enum class EXAxisLabelsUnit : uint8 { Samples UMETA(DisplayName = "Samples"), Seconds UMETA(DisplayName = "Seconds") };`
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeWindowValueChanged, const float ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnalysisPeriodChanged, const float ) UENUM(BlueprintType) enum class EXAxisLabelsUnit : uint8 { Samples UMETA(DisplayName = "Samples"), Seconds UMETA(DisplayName = "Seconds") };`
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnalysisPeriodChanged, const float ) UENUM(BlueprintType) enum class EXAxisLabelsUnit : uint8 { Samples UMETA(DisplayName = "Samples"), Seconds UMETA(DisplayName = "Seconds") };`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioRadialSlider.h` (Public)


#### enum `EAudioRadialSliderLayout`  
`enum EAudioRadialSliderLayout : int`  
_L22-32_
- reflection: `UENUM()`
- L25 _public enumerator_ `Layout_LabelTop UMETA(DisplayName = "Label Top")` — Label above radial slider.
- L28 _public enumerator_ `Layout_LabelCenter UMETA(DisplayName = "Label Center")` — Label in the center of the radial slider.
- L31 _public enumerator_ `Layout_LabelBottom UMETA(DisplayName = "Label Bottom")` — Label below radial slider.

#### class `SAudioRadialSlider`  
`class SAudioRadialSlider : public SAudioInputWidget`  
_L38-158_
- inherits: `SAudioInputWidget`
- desc: Slate audio radial sliders that wrap SRadialSlider and provides additional audio specific functionality. This is a nativized version of the previous Audio Knob Small/Large widgets.
- L42 _public function_ `SLATE_BEGIN_ARGS(SAudioRadialSlider)`
- L59 _public prototype_ `SLATE_STYLE_ARGUMENT(FAudioRadialSliderStyle, Style) SLATE_ATTRIBUTE(float, SliderValue) SLATE_ATTRIBUTE(EAudioRadialSliderLayout, WidgetLayout) SLATE_ATTRIBUTE(FSlateColor, SliderProgressColor) SLATE_ATTRIBUTE(FSlateColor, SliderBarColor) SLATE_ATTRIBUTE(FSlateColor, CenterBackgroundColor) SLATE_ATTRIBUTE(FVector2D, HandStartEndRatio) SLATE_ARGUMENT(FRuntimeFloatCurve, SliderCurve) SLATE_ATTRIBUTE(TOptional<FVector2D>, DesiredSizeOverride) SLATE_EVENT(FOnFloatValueChanged, OnValueChanged) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_END_ARGS() SAudioRadialSlider();` — The style used to draw the audio radial slider.
- L97 _public prototype_ `virtual ~SAudioRadialSlider() = default;`
- L100 _public member_ `FOnFloatValueChanged OnValueChanged;` — Holds a delegate that is executed when the slider's value changed.
- L103 _public member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L106 _public member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when the mouse is let up and a capture ends.
- L108 _public prototype_ `void SetCenterBackgroundColor(FSlateColor InColor);`
- L109 _public prototype_ `void SetSliderProgressColor(FSlateColor InColor);`
- L110 _public prototype_ `void SetSliderBarColor(FSlateColor InColor);`
- L111 _public prototype_ `void SetHandStartEndRatio(const FVector2D InHandStartEndRatio);`
- L112 _public prototype_ `void SetSliderThickness(const float Thickness);`
- L113 _public prototype_ `void SetWidgetLayout(EAudioRadialSliderLayout InLayout);`
- L114 _public prototype_ `FVector2D ComputeDesiredSize(float) const;`
- L115 _public prototype_ `void SetDesiredSizeOverride(const FVector2D DesiredSize);`
- L117 _public prototype_ `virtual void Construct(const SAudioRadialSlider::FArguments& InArgs);`
- L118 _public prototype_ `void SetSliderValue(float InSliderValue);`
- L119 _public prototype_ `virtual const float GetOutputValue(const float InSliderValue);`
- L120 _public prototype_ `virtual const float GetSliderValue(const float OutputValue);`
- L121 _public prototype_ `virtual const float GetOutputValueForText(const float InSliderValue);`
- L122 _public prototype_ `virtual const float GetSliderValueForText(const float OutputValue);`
- L123 _public prototype_ `virtual void SetOutputRange(const FVector2D Range);`
- L126 _public prototype_ `void SetLabelBackgroundColor(FSlateColor InColor);` — Text label functions
- L127 _public prototype_ `void SetUnitsText(const FText Units);`
- L128 _public prototype_ `void SetUnitsTextReadOnly(const bool bIsReadOnly);`
- L129 _public prototype_ `void SetValueTextReadOnly(const bool bIsReadOnly);`
- L130 _public prototype_ `void SetShowLabelOnlyOnHover(const bool bShowLabelOnlyOnHover);`
- L131 _public prototype_ `void SetShowUnitsText(const bool bShowUnitsText);`
- L134 _protected member_ `const FAudioRadialSliderStyle* Style;`
- L135 _protected member_ `TAttribute<float> SliderValue;`
- L136 _protected member_ `FRuntimeFloatCurve SliderCurve;`
- L138 _protected member_ `TAttribute<FSlateColor> CenterBackgroundColor;`
- L139 _protected member_ `TAttribute<FSlateColor> SliderProgressColor;`
- L140 _protected member_ `TAttribute<FSlateColor> SliderBarColor;`
- L141 _protected member_ `TAttribute<FSlateColor> LabelBackgroundColor;`
- L142 _protected member_ `TAttribute<FVector2D> HandStartEndRatio;`
- L143 _protected member_ `TAttribute<EAudioRadialSliderLayout> WidgetLayout;`
- L144 _protected member_ `TAttribute<TOptional<FVector2D>> DesiredSizeOverride;`
- L146 _protected member_ `TSharedPtr<SRadialSlider> RadialSlider;`
- L147 _protected member_ `TSharedPtr<SImage> CenterBackgroundImage;`
- L148 _protected member_ `TSharedPtr<SImage> OuterBackgroundImage;`
- L149 _protected member_ `TSharedPtr<SAudioTextBox> Label;`
- L151 _protected member_ `TSharedPtr<SWidgetSwitcher> LayoutWidgetSwitcher;` — Overall widget layout
- L154 _protected member_ `FVector2D OutputRange = FVector2D(0.0f, 1.0f);` — Range for output
- L155 _protected member_ `static const FVector2D NormalizedLinearSliderRange;`
- L157 _protected prototype_ `TSharedRef<SWidgetSwitcher> CreateLayoutWidgetSwitcher();`

#### class `SAudioVolumeRadialSlider`  
`class SAudioVolumeRadialSlider : public SAudioRadialSlider`  
_L163-185_
- inherits: `SAudioRadialSlider`
- desc: An Audio Radial Slider widget with default conversion for volume (dB).
- L167 _public prototype_ `SAudioVolumeRadialSlider();`
- L168 _public prototype_ `void Construct(const SAudioRadialSlider::FArguments& InArgs);`
- L169 _public prototype_ `const float GetOutputValue(const float InSliderValue) override;`
- L170 _public prototype_ `const float GetSliderValue(const float OutputValue) override;`
- L171 _public prototype_ `const float GetOutputValueForText(const float InSliderValue) override;`
- L172 _public prototype_ `const float GetSliderValueForText(const float OutputValue) override;`
- L173 _public prototype_ `void SetUseLinearOutput(bool InUseLinearOutput);`
- L174 _public prototype_ `void SetOutputRange(const FVector2D Range) override;`
- L177 _public member_ `static const float MinDbValue;` — Min/max possible values for output range, derived to avoid Audio::ConvertToLinear/dB functions returning NaN
- L178 _public member_ `static const float MaxDbValue;`
- L181 _private member_ `bool bUseLinearOutput = true;` — Use linear (converted from dB, not normalized) output value. Only applies to the output value reported by GetOutputValue(); the text displayed will still be in decibels.
- L183 _private prototype_ `const float GetDbValueFromSliderValue(const float InSliderValue);`
- L184 _private prototype_ `const float GetSliderValueFromDb(const float DbValue);`

#### class `SAudioFrequencyRadialSlider`  
`class SAudioFrequencyRadialSlider : public SAudioRadialSlider`  
_L190-198_
- inherits: `SAudioRadialSlider`
- desc: An Audio Radial Slider widget with default logarithmic conversion intended to be used for frequency (Hz).
- L194 _public prototype_ `SAudioFrequencyRadialSlider();`
- L195 _public prototype_ `void Construct(const SAudioRadialSlider::FArguments& InArgs);`
- L196 _public prototype_ `const float GetOutputValue(const float InSliderValue);`
- L197 _public prototype_ `const float GetSliderValue(const float OutputValue);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioSlider.h` (Public)


#### class `SAudioSliderBase`  
`class SAudioSliderBase : public SAudioInputWidget`  
_L24-166_
- inherits: `SAudioInputWidget`
- desc: Slate audio sliders that wrap SSlider and provides additional audio specific functionality. This is a nativized version of the previous Audio Fader widget.
- L28 _public function_ `SLATE_BEGIN_ARGS(SAudioSliderBase)`
- L44 _public prototype_ `SLATE_STYLE_ARGUMENT(FAudioSliderStyle, Style) SLATE_ATTRIBUTE(float, SliderValue) SLATE_ATTRIBUTE(bool, AlwaysShowLabel) SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ATTRIBUTE(FSlateColor, SliderBackgroundColor) SLATE_ATTRIBUTE(FSlateColor, SliderBarColor) SLATE_ATTRIBUTE(FSlateColor, SliderThumbColor) SLATE_ATTRIBUTE(FSlateColor, WidgetBackgroundColor) SLATE_ATTRIBUTE(TOptional<FVector2D>, DesiredSizeOverride) SLATE_EVENT(FOnFloatValueChanged, OnValueChanged) SLATE_EVENT(FOnFloatValueChanged, OnValueCommitted) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureBegin) SLATE_EVENT(FSimpleDelegate, OnMouseCaptureEnd) SLATE_END_ARGS()` — The style used to draw the audio slider.
- L85 _public prototype_ `virtual ~SAudioSliderBase() = default;`
- L88 _public member_ `FOnFloatValueChanged OnValueChanged;` — Holds a delegate that is executed when the slider's value changed.
- L91 _public member_ `FOnFloatValueChanged OnValueCommitted;` — Holds a delegate that is executed when the slider's value is committed (mouse capture ends).
- L94 _public member_ `FSimpleDelegate OnMouseCaptureBegin;` — Holds a delegate that is executed when the mouse is pressed and a capture begins.
- L97 _public member_ `FSimpleDelegate OnMouseCaptureEnd;` — Holds a delegate that is executed when mouse capture ends.
- L104 _public prototype_ `virtual void Construct(const SAudioSliderBase::FArguments& InDeclaration);` — Construct the widget. @param InDeclaration A declaration from which to construct the widget.
- L105 _public prototype_ `virtual const float GetOutputValue(const float InSliderValue);`
- L106 _public prototype_ `virtual const float GetSliderValue(const float OutputValue);`
- L107 _public prototype_ `virtual const float GetOutputValueForText(const float InSliderValue);`
- L108 _public prototype_ `virtual const float GetSliderValueForText(const float OutputValue);`
- L113 _public prototype_ `void SetSliderValue(float InSliderValue);` — Set the slider's linear (0-1 normalized) value.
- L114 _public prototype_ `void SetSliderValue(TAttribute<float> InSliderValue);`
- L115 _public prototype_ `FVector2D ComputeDesiredSize(float) const;`
- L116 _public prototype_ `void SetDesiredSizeOverride(const FVector2D DesiredSize);`
- L118 _public prototype_ `void SetOrientation(EOrientation InOrientation);`
- L119 _public prototype_ `void SetSliderBackgroundColor(FSlateColor InSliderBackgroundColor);`
- L120 _public prototype_ `void SetSliderBarColor(FSlateColor InSliderBarColor);`
- L121 _public prototype_ `void SetSliderThumbColor(FSlateColor InSliderThumbColor);`
- L122 _public prototype_ `void SetWidgetBackgroundColor(FSlateColor InWidgetBackgroundColor);`
- L123 _public prototype_ `virtual void SetOutputRange(const FVector2D Range);`
- L126 _public prototype_ `void SetLabelBackgroundColor(FSlateColor InColor);` — Text label functions
- L127 _public prototype_ `void SetUnitsText(const FText Units);`
- L128 _public prototype_ `void SetUnitsTextReadOnly(const bool bIsReadOnly);`
- L129 _public prototype_ `void SetValueTextReadOnly(const bool bIsReadOnly);`
- L130 _public prototype_ `void SetShowLabelOnlyOnHover(const bool bShowLabelOnlyOnHover);`
- L131 _public prototype_ `void SetShowUnitsText(const bool bShowUnitsText);`
- L134 _protected member_ `const FAudioSliderStyle* Style;`
- L137 _protected member_ `TAttribute<float> SliderValueAttribute;` — Holds the slider's current linear value, from 0.0 - 1.0f
- L139 _protected member_ `TAttribute<EOrientation> Orientation;` — Holds the slider's orientation
- L141 _protected member_ `TAttribute<TOptional<FVector2D>> DesiredSizeOverride;` — Optional override for desired size
- L144 _protected member_ `TAttribute<FSlateColor> LabelBackgroundColor;` — Various colors
- L145 _protected member_ `TAttribute<FSlateColor> SliderBackgroundColor;`
- L146 _protected member_ `TAttribute<FSlateColor> SliderBarColor;`
- L147 _protected member_ `TAttribute<FSlateColor> SliderThumbColor;`
- L148 _protected member_ `TAttribute<FSlateColor> WidgetBackgroundColor;`
- L151 _protected member_ `TSharedPtr<SSlider> Slider;` — Widget components
- L152 _protected member_ `TSharedPtr<SAudioTextBox> Label;`
- L153 _protected member_ `TSharedPtr<SImage> SliderBackgroundImage;`
- L154 _protected member_ `TSharedPtr<SImage> WidgetBackgroundImage;`
- L157 _protected member_ `FVector2D OutputRange = FVector2D(0.0f, 1.0f);` — Range for output, currently only used for frequency sliders and sliders without curves
- L158 _protected member_ `static const FVector2D NormalizedLinearSliderRange;`
- L160 _private member_ `FSlateBrush SliderBackgroundBrush;`
- L161 _private member_ `FVector2D SliderBackgroundSize;`
- L163 _private member_ `TSharedPtr<SWidgetSwitcher> LayoutWidgetSwitcher;` — Switches between the vertical and horizontal views
- L165 _private prototype_ `TSharedRef<SWidgetSwitcher> CreateWidgetLayout();`

#### class `SAudioSlider`  
`class SAudioSlider : public SAudioSliderBase`  
_L171-189_
- inherits: `SAudioSliderBase`
- desc: An Audio Slider widget with customizable curves.
- L175 _public prototype_ `SAudioSlider();`
- L176 _public prototype_ `virtual ~SAudioSlider() = default;`
- L177 _public prototype_ `virtual void Construct(const SAudioSliderBase::FArguments& InDeclaration);`
- L178 _public prototype_ `void SetLinToOutputCurve(const TWeakObjectPtr<const UCurveFloat> LinToOutputCurve);`
- L179 _public prototype_ `void SetOutputToLinCurve(const TWeakObjectPtr<const UCurveFloat> OutputToLinCurve);`
- L180 _public prototype_ `const TWeakObjectPtr<const UCurveFloat> GetOutputToLinCurve();`
- L181 _public prototype_ `const TWeakObjectPtr<const UCurveFloat> GetLinToOutputCurve();`
- L182 _public prototype_ `const float GetOutputValue(const float InSliderValue);`
- L183 _public prototype_ `const float GetSliderValue(const float OutputValue);`
- L187 _protected member_ `TWeakObjectPtr<const UCurveFloat> LinToOutputCurve = nullptr;` — Curves for mapping linear (0.0 - 1.0) to output (ex. dB for volume)
- L188 _protected member_ `TWeakObjectPtr<const UCurveFloat> OutputToLinCurve = nullptr;`

#### class `SAudioVolumeSlider`  
`class SAudioVolumeSlider : public SAudioSliderBase`  
_L194-218_
- inherits: `SAudioSliderBase`
- desc: An Audio Slider widget intended to be used for volume output, with output decibel range but no customizable curves.
- L198 _public prototype_ `SAudioVolumeSlider();`
- L199 _public prototype_ `void Construct(const SAudioSlider::FArguments& InDeclaration);`
- L201 _public prototype_ `const float GetOutputValue(const float InSliderValue);`
- L202 _public prototype_ `const float GetSliderValue(const float OutputValue);`
- L203 _public prototype_ `const float GetOutputValueForText(const float InSliderValue) override;`
- L204 _public prototype_ `const float GetSliderValueForText(const float OutputValue) override;`
- L205 _public prototype_ `void SetUseLinearOutput(bool InUseLinearOutput);`
- L206 _public prototype_ `void SetOutputRange(const FVector2D Range) override;`
- L210 _private member_ `static const float MinDbValue;` — Min/max possible values for output range, derived to avoid Audio::ConvertToLinear/dB functions returning NaN
- L211 _private member_ `static const float MaxDbValue;`
- L214 _private member_ `bool bUseLinearOutput = true;` — Use linear (converted from dB, not normalized) output value. Only applies to the output value reported by GetOutputValue(); the text displayed will still be in decibels.
- L216 _private prototype_ `const float GetDbValueFromSliderValue(const float InSliderValue);`
- L217 _private prototype_ `const float GetSliderValueFromDb(const float DbValue);`

#### class `SAudioFrequencySlider`  
`class SAudioFrequencySlider : public SAudioSliderBase`  
_L223-231_
- inherits: `SAudioSliderBase`
- desc: An Audio Slider widget intended to be used for frequency output, with output frequency range but no customizable curves.
- L227 _public prototype_ `SAudioFrequencySlider();`
- L228 _public prototype_ `void Construct(const SAudioSlider::FArguments& InDeclaration);`
- L229 _public prototype_ `const float GetOutputValue(const float InSliderValue);`
- L230 _public prototype_ `const float GetSliderValue(const float OutputValue);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioSpectrogram.h` (Public)


#### class `SAudioSpectrogram`  
`class SAudioSpectrogram : public SCompoundWidget`  
_L24-117_
- inherits: `SCompoundWidget`
- desc: Slate Widget for rendering a time-frequency representation of a series of audio power spectra.
- L27 _public function_ `SLATE_BEGIN_ARGS(SAudioSpectrogram) : _ViewMinFrequency(20.0f) , _ViewMaxFrequency(20000.0f) , _ColorMapMinSoundLevel(-84.0f) , _ColorMapMaxSoundLevel(12.0f) , _ColorMap(EAudioColorGradient::BlackToWhite) , _FrequencyAxisScale(EAudioSpectrogramFrequencyAxisScale::Logarithmic) , _FrequencyAxisPixelBucketMode(EAudioSpectrogramFrequencyAxisPixelBucketMode::Average) , _Orientation(EOrientation::Orient_Horizontal) , _AllowContextMenu(true) , _FillBackground(false)`
- L39 _public prototype_ `SLATE_ATTRIBUTE(float, ViewMinFrequency) SLATE_ATTRIBUTE(float, ViewMaxFrequency) SLATE_ATTRIBUTE(float, ColorMapMinSoundLevel) SLATE_ATTRIBUTE(float, ColorMapMaxSoundLevel) SLATE_ATTRIBUTE(EAudioColorGradient, ColorMap) SLATE_ATTRIBUTE(EAudioSpectrogramFrequencyAxisScale, FrequencyAxisScale) SLATE_ATTRIBUTE(EAudioSpectrogramFrequencyAxisPixelBucketMode, FrequencyAxisPixelBucketMode) SLATE_ATTRIBUTE(EOrientation, Orientation) SLATE_ATTRIBUTE(bool, AllowContextMenu) SLATE_ATTRIBUTE(bool, FillBackground) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FOnSpectrogramFrequencyAxisPixelBucketModeMenuEntryClicked, OnFrequencyAxisPixelBucketModeMenuEntryClicked) SLATE_EVENT(FOnSpectrogramFrequencyAxisScaleMenuEntryClicked, OnFrequencyAxisScaleMenuEntryClicked) SLATE_EVENT(FOnSpectrogramColorMapMenuEntryClicked, OnColorMapMenuEntryClicked) SLATE_EVENT(FOnSpectrogramOrientationMenuEntryClicked, OnOrientationMenuEntryClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L60 _public prototype_ `void AddFrame(const FAudioSpectrogramFrameData& SpectrogramFrameData);` — Add the data for one spectrum frame to the spectrogram display
- L63 _public prototype_ `void AddFrame(const FSynesthesiaSpectrumResults& SpectrumResults, const EAudioSpectrumType SpectrumType, const float SampleRate);` — Add the data for one spectrum frame to the spectrogram display (convenience helper for when using USynesthesiaSpectrumAnalyzer)
- L66 _public prototype_ `void AddFrame(const FConstantQResults& ConstantQResults, const float StartingFrequencyHz, const float NumBandsPerOctave, const EAudioSpectrumType SpectrumType);` — Add the data for one spectrum frame to the spectrogram display (convenience helper for when using UConstantQAnalyzer)
- L68 _public function_ `void SetViewMinFrequency(const float InViewMinFrequency)`
- L69 _public function_ `void SetViewMaxFrequency(const float InViewMaxFrequency)`
- L70 _public function_ `void SetColorMapMinSoundLevel(const float InColorMapMinSoundLevel)`
- L71 _public function_ `void SetColorMapMaxSoundLevel(const float InColorMapMaxSoundLevel)`
- L72 _public function_ `void SetColorMap(const EAudioColorGradient InColorMap)`
- L73 _public function_ `void SetFrequencyAxisScale(const EAudioSpectrogramFrequencyAxisScale InFrequencyAxisScale)`
- L74 _public function_ `void SetFrequencyAxisPixelBucketMode(const EAudioSpectrogramFrequencyAxisPixelBucketMode InFrequencyAxisPixelBucketMode)`
- L75 _public function_ `void SetOrientation(const EOrientation InOrientation)`
- L76 _public function_ `void SetAllowContextMenu(bool bInAllowContextMenu)`
- L78 _public prototype_ `TSharedRef<const FExtensionBase> AddContextMenuExtension(EExtensionHook::Position HookPosition, const TSharedPtr<FUICommandList>& CommandList, const FMenuExtensionDelegate& MenuExtensionDelegate);`
- L79 _public prototype_ `void RemoveContextMenuExtension(const TSharedRef<const FExtensionBase>& Extension);`
- L82 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L83 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L88 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L91 _private prototype_ `TSharedRef<SWidget> BuildDefaultContextMenu();`
- L92 _private prototype_ `void BuildColorMapSubMenu(FMenuBuilder& SubMenu);`
- L93 _private prototype_ `void BuildFrequencyAxisScaleSubMenu(FMenuBuilder& SubMenu);`
- L94 _private prototype_ `void BuildFrequencyAxisPixelBucketModeSubMenu(FMenuBuilder& SubMenu);`
- L95 _private prototype_ `void BuildOrientationSubMenu(FMenuBuilder& SubMenu);`
- L97 _private member_ `static FName ContextMenuExtensionHook;`
- L98 _private member_ `TSharedPtr<FExtender> ContextMenuExtender;`
- L100 _private member_ `TAttribute<float> ViewMinFrequency;`
- L101 _private member_ `TAttribute<float> ViewMaxFrequency;`
- L102 _private member_ `TAttribute<float> ColorMapMinSoundLevel;`
- L103 _private member_ `TAttribute<float> ColorMapMaxSoundLevel;`
- L104 _private member_ `TAttribute<EAudioColorGradient> ColorMap;`
- L105 _private member_ `TAttribute<EAudioSpectrogramFrequencyAxisScale> FrequencyAxisScale;`
- L106 _private member_ `TAttribute<EAudioSpectrogramFrequencyAxisPixelBucketMode> FrequencyAxisPixelBucketMode;`
- L107 _private member_ `TAttribute<EOrientation> Orientation;`
- L108 _private member_ `TAttribute<bool> bAllowContextMenu;`
- L109 _private member_ `TAttribute<bool> bFillBackground;`
- L110 _private member_ `FOnContextMenuOpening OnContextMenuOpening;`
- L111 _private member_ `FOnSpectrogramFrequencyAxisPixelBucketModeMenuEntryClicked OnFrequencyAxisPixelBucketModeMenuEntryClicked;`
- L112 _private member_ `FOnSpectrogramFrequencyAxisScaleMenuEntryClicked OnFrequencyAxisScaleMenuEntryClicked;`
- L113 _private member_ `FOnSpectrogramColorMapMenuEntryClicked OnColorMapMenuEntryClicked;`
- L114 _private member_ `FOnSpectrogramOrientationMenuEntryClicked OnOrientationMenuEntryClicked;`
- L116 _private member_ `TSharedPtr<FAudioSpectrogramViewport> SpectrogramViewport;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSpectrogramFrequencyAxisPixelBucketModeMenuEntryClicked, EAudioSpectrogramFrequencyAxisPixelBucketMode);`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSpectrogramFrequencyAxisPixelBucketModeMenuEntryClicked, EAudioSpectrogramFrequencyAxisPixelBucketMode);`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSpectrogramFrequencyAxisScaleMenuEntryClicked, EAudioSpectrogramFrequencyAxisScale);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSpectrogramFrequencyAxisScaleMenuEntryClicked, EAudioSpectrogramFrequencyAxisScale);`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSpectrogramColorMapMenuEntryClicked, EAudioColorGradient);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSpectrogramColorMapMenuEntryClicked, EAudioColorGradient);`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSpectrogramOrientationMenuEntryClicked, EOrientation);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSpectrogramOrientationMenuEntryClicked, EOrientation);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioSpectrumPlot.h` (Public)


#### enum `EAudioSpectrumPlotTilt`  
`enum class EAudioSpectrumPlotTilt : uint8`  
_L17-24_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `NoTilt UMETA(ToolTip = "0 dB/octave slope (white noise is flat).")`
- L20 _public enumerator_ `Plus1_5dBPerOctave UMETA(DisplayName = "1.5 dB/octave", ToolTip = "1.5 dB/octave slope.")`
- L21 _public enumerator_ `Plus3dBPerOctave UMETA(DisplayName = "3 dB/octave", ToolTip = "3 dB/octave slope (pink noise is flat).")`
- L22 _public enumerator_ `Plus4_5dBPerOctave UMETA(DisplayName = "4.5 dB/octave", ToolTip = "4.5 dB/octave slope.")`
- L23 _public enumerator_ `Plus6dBPerOctave UMETA(DisplayName = "6 dB/octave", ToolTip = "6 dB/octave slope (Brownian noise is flat).")`

#### enum `EAudioSpectrumPlotFrequencyAxisScale`  
`enum class EAudioSpectrumPlotFrequencyAxisScale : uint8`  
_L27-31_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Linear`
- L30 _public enumerator_ `Logarithmic`

#### enum `EAudioSpectrumPlotFrequencyAxisPixelBucketMode`  
`enum class EAudioSpectrumPlotFrequencyAxisPixelBucketMode : uint8`  
_L34-39_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `Sample UMETA(ToolTip = "Plot one data point per frequency axis pixel bucket only, choosing the data point nearest the pixel center.")`
- L37 _public enumerator_ `Peak UMETA(ToolTip = "Plot one data point per frequency axis pixel bucket only, choosing the data point with the highest sound level.")`
- L38 _public enumerator_ `Average UMETA(ToolTip = "Plot the average of the data points in each frequency axis pixel bucket.")`

#### class `FAudioSpectrumPlotScaleInfo`  
`class FAudioSpectrumPlotScaleInfo`  
_L44-111_
- desc: Utility class for converting between spectrum data and local/absolute screen space.
- L47 _public function_ `FAudioSpectrumPlotScaleInfo(const FVector2f InWidgetSize, EAudioSpectrumPlotFrequencyAxisScale InFrequencyAxisScale, float InViewMinFrequency, float InViewMaxFrequency, float InViewMinSoundLevel, float InViewMaxSoundLevel) : WidgetSize(InWidgetSize) , FrequencyAxisScale(InFrequencyAxisScale) , TransformedViewMinFrequency(ForwardTransformFrequency(InViewMinFrequency)) , TransformedViewMaxFrequency(ForwardTransformFrequency(InViewMaxFrequency)) , TransformedViewFrequencyRange(TransformedViewMaxFrequency - TransformedViewMinFrequency) , PixelsPerTransformedHz((TransformedViewFrequencyRange > 0.0f) ? (InWidgetSize.X / TransformedViewFrequencyRange) : 0.0f) , ViewMinSoundLevel(InViewMinSoundLevel) , ViewMaxSoundLevel(InViewMaxSoundLevel) , ViewSoundLevelRange(InViewMaxSoundLevel - InViewMinSoundLevel) , PixelsPerDecibel((ViewSoundLevelRange > 0.0f) ? (InWidgetSize.Y / ViewSoundLevelRange) : 0.0f)`
- L62 _public function_ `float LocalXToFrequency(float ScreenX) const`
- L68 _public function_ `float FrequencyToLocalX(float Frequency) const`
- L73 _public function_ `float LocalYToSoundLevel(float ScreenY) const`
- L78 _public function_ `float SoundLevelToLocalY(float SoundLevel) const`
- L83 _public function_ `FVector2f ToLocalPos(const FVector2f& FrequencyAndSoundLevel) const`
- L89 _private function_ `float ForwardTransformFrequency(float Frequency) const`
- L94 _private function_ `float InverseTransformFrequency(float TransformedFrequency) const`
- L99 _private member_ `const FVector2f WidgetSize;`
- L101 _private member_ `const EAudioSpectrumPlotFrequencyAxisScale FrequencyAxisScale;`
- L102 _private member_ `const float TransformedViewMinFrequency;`
- L103 _private member_ `const float TransformedViewMaxFrequency;`
- L104 _private member_ `const float TransformedViewFrequencyRange;`
- L105 _private member_ `const float PixelsPerTransformedHz;`
- L107 _private member_ `const float ViewMinSoundLevel;`
- L108 _private member_ `const float ViewMaxSoundLevel;`
- L109 _private member_ `const float ViewSoundLevelRange;`
- L110 _private member_ `const float PixelsPerDecibel;`

#### struct `FAudioPowerSpectrumData`  
`struct FAudioPowerSpectrumData`  
_L121-125_
- desc: The audio spectrum data to plot.
- L123 _public member_ `TConstArrayView<float> CenterFrequencies;`
- L124 _public member_ `TConstArrayView<float> SquaredMagnitudes;`

#### class `SAudioSpectrumPlot`  
`class SAudioSpectrumPlot : public SCompoundWidget`  
_L132-286_
- inherits: `SCompoundWidget`
- desc: Slate Widget for plotting an audio power spectrum, with linear or log frequency scale, and decibels sound levels.
- L135 _public function_ `SLATE_BEGIN_ARGS(SAudioSpectrumPlot) : _Style(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioSpectrumPlotStyle>("AudioSpectrumPlot.Style")) , _ViewMinFrequency(20.0f) , _ViewMaxFrequency(20000.0f) , _ViewMinSoundLevel(-60.0f) , _ViewMaxSoundLevel(12.0f) , _TiltExponent(0.0f) , _TiltPivotFrequency(24000.0f) , _DisplayCrosshair(false) , _DisplayFrequencyAxisLabels(true) , _DisplaySoundLevelAxisLabels(true) , _DisplayFrequencyGridLines(true) , _DisplaySoundLevelGridLines(true) , _FrequencyAxisScale(EAudioSpectrumPlotFrequencyAxisScale::Logarithmic) , _FrequencyAxisPixelBucketMode(EAudioSpectrumPlotFrequencyAxisPixelBucketMode::Average) , _BackgroundColor(FSlateColor::UseStyle()) , _GridColor(FSlateColor::UseStyle()) , _AxisLabelColor(FSlateColor::UseStyle()) , _CrosshairColor(FSlateColor::UseStyle()) , _SpectrumColor(FSlateColor::UseStyle()) , _AllowContextMenu(true)`
- L157 _public prototype_ `SLATE_STYLE_ARGUMENT(FAudioSpectrumPlotStyle, Style) SLATE_ATTRIBUTE(float, ViewMinFrequency) SLATE_ATTRIBUTE(float, ViewMaxFrequency) SLATE_ATTRIBUTE(float, ViewMinSoundLevel) SLATE_ATTRIBUTE(float, ViewMaxSoundLevel) SLATE_ATTRIBUTE(float, TiltExponent) SLATE_ATTRIBUTE(float, TiltPivotFrequency) SLATE_ATTRIBUTE(TOptional<float>, SelectedFrequency) SLATE_ATTRIBUTE(bool, DisplayCrosshair) SLATE_ATTRIBUTE(bool, DisplayFrequencyAxisLabels) SLATE_ATTRIBUTE(bool, DisplaySoundLevelAxisLabels) SLATE_ATTRIBUTE(bool, DisplayFrequencyGridLines) SLATE_ATTRIBUTE(bool, DisplaySoundLevelGridLines) SLATE_ATTRIBUTE(EAudioSpectrumPlotFrequencyAxisScale, FrequencyAxisScale) SLATE_ATTRIBUTE(EAudioSpectrumPlotFrequencyAxisPixelBucketMode, FrequencyAxisPixelBucketMode) SLATE_ATTRIBUTE(FSlateColor, BackgroundColor) SLATE_ATTRIBUTE(FSlateColor, GridColor) SLATE_ATTRIBUTE(FSlateColor, AxisLabelColor) SLATE_ATTRIBUTE(FSlateColor, CrosshairColor) SLATE_ATTRIBUTE(FSlateColor, SpectrumColor) SLATE_ATTRIBUTE(bool, AllowContextMenu) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FOnTiltSpectrumMenuEntryClicked, OnTiltSpectrumMenuEntryClicked) SLATE_EVENT(FOnFrequencyAxisPixelBucketModeMenuEntryClicked, OnFrequencyAxisPixelBucketModeMenuEntryClicked) SLATE_EVENT(FOnFrequencyAxisScaleMenuEntryClicked, OnFrequencyAxisScaleMenuEntryClicked) SLATE_EVENT(FOnDisplayAxisLabelsButtonToggled, OnDisplayFrequencyAxisLabelsButtonToggled) SLATE_EVENT(FOnDisplayAxisLabelsButtonToggled, OnDisplaySo ...`
- L190 _public function_ `void SetViewMinFrequency(float InViewMinFrequency)`
- L191 _public function_ `void SetViewMaxFrequency(float InViewMaxFrequency)`
- L192 _public function_ `void SetViewMinSoundLevel(float InViewMinSoundLevel)`
- L193 _public function_ `void SetViewMaxSoundLevel(float InViewMaxSoundLevel)`
- L194 _public function_ `void SetTiltExponent(float InTiltExponent)`
- L195 _public function_ `void SetTiltPivotFrequency(float InTiltPivotFrequency)`
- L196 _public function_ `void SetSelectedFrequency(TOptional<float> InSelectedFrequency)`
- L197 _public function_ `void SetDisplayCrosshair(bool bInDisplayCrosshair)`
- L198 _public function_ `void SetDisplayFrequencyAxisLabels(bool bInDisplayFrequencyAxisLabels)`
- L199 _public function_ `void SetDisplaySoundLevelAxisLabels(bool bInDisplaySoundLevelAxisLabels)`
- L200 _public function_ `void SetDisplayFrequencyGridLines(bool bInDisplayFrequencyGridLines)`
- L201 _public function_ `void SetDisplaySoundLevelGridLines(bool bInDisplaySoundLevelGridLines)`
- L202 _public function_ `void SetFrequencyAxisScale(EAudioSpectrumPlotFrequencyAxisScale InFrequencyAxisScale)`
- L203 _public function_ `void SetFrequencyAxisPixelBucketMode(EAudioSpectrumPlotFrequencyAxisPixelBucketMode InFrequencyAxisPixelBucketMode)`
- L204 _public function_ `void SetAllowContextMenu(bool bInAllowContextMenu)`
- L206 _public prototype_ `TSharedRef<const FExtensionBase> AddContextMenuExtension(EExtensionHook::Position HookPosition, const TSharedPtr<FUICommandList>& CommandList, const FMenuExtensionDelegate& MenuExtensionDelegate);`
- L207 _public prototype_ `void RemoveContextMenuExtension(const TSharedRef<const FExtensionBase>& Extension);`
- L210 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L211 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L212 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L213 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L216 _public function_ `void UnbindOnGetAudioSpectrumData()`
- L218 _public prototype_ `FAudioSpectrumPlotScaleInfo GetScaleInfo() const;`
- L220 _public prototype_ `static float GetTiltExponentValue(const EAudioSpectrumPlotTilt InTilt);`
- L224 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L227 _private prototype_ `int32 DrawSolidBackgroundRectangle(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle) const;`
- L229 _private prototype_ `int32 DrawGrid(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, const FAudioSpectrumPlotScaleInfo& ScaleInfo) const;`
- L230 _private prototype_ `void GetGridLineSoundLevels(TArray<float>& GridLineSoundLevels) const;`
- L231 _private prototype_ `void GetGridLineFrequencies(TArray<float>& AllGridLineFrequencies, TArray<float>& MajorGridLineFrequencies) const;`
- L233 _private prototype_ `int32 DrawPowerSpectrum(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, const FAudioSpectrumPlotScaleInfo& ScaleInfo) const;`
- L234 _private prototype_ `FAudioPowerSpectrumData GetPowerSpectrum() const;`
- L236 _private prototype_ `int32 DrawCrosshairAndAxisLabels(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, const FAudioSpectrumPlotScaleInfo& ScaleInfo, TConstArrayView<FVector2f> LinePoints) const;`
- L240 _private prototype_ `static void GetSpectrumLinePoints(TArray<FVector2f>& OutLinePoints, TConstArrayView<FVector2f> DataPoints, const FAudioSpectrumPlotScaleInfo& ScaleInfo, TFunctionRef<float(const FVector2f& DataPoint)> CostFunction);` — This is a function to reduce the given array of data points to a possibly shorter array of points that will form the line to be plotted. Where multiple data points map to the same frequency axis pixel bucket, the given 'cost function' will be used to select the best data point (the data point with the lowest 'cost').
- L242 _private prototype_ `FLinearColor GetBackgroundColor(const FWidgetStyle& InWidgetStyle) const;`
- L243 _private prototype_ `FLinearColor GetGridColor(const FWidgetStyle& InWidgetStyle) const;`
- L244 _private prototype_ `FLinearColor GetAxisLabelColor(const FWidgetStyle& InWidgetStyle) const;`
- L245 _private prototype_ `FLinearColor GetCrosshairColor(const FWidgetStyle& InWidgetStyle) const;`
- L246 _private prototype_ `FLinearColor GetSpectrumColor(const FWidgetStyle& InWidgetStyle) const;`
- L248 _private prototype_ `TSharedRef<SWidget> BuildDefaultContextMenu();`
- L249 _private prototype_ `void BuildTiltSpectrumSubMenu(FMenuBuilder& SubMenu);`
- L250 _private prototype_ `void BuildFrequencyAxisScaleSubMenu(FMenuBuilder& SubMenu);`
- L251 _private prototype_ `void BuildFrequencyAxisPixelBucketModeSubMenu(FMenuBuilder& SubMenu);`
- L253 _private member_ `static const float ClampMinSoundLevel;`
- L255 _private member_ `static FName ContextMenuExtensionHook;`
- L256 _private member_ `TSharedPtr<FExtender> ContextMenuExtender;`
- L258 _private member_ `const FAudioSpectrumPlotStyle* Style;`
- L259 _private member_ `TAttribute<float> ViewMinFrequency;`
- L260 _private member_ `TAttribute<float> ViewMaxFrequency;`
- L261 _private member_ `TAttribute<float> ViewMinSoundLevel;`
- L262 _private member_ `TAttribute<float> ViewMaxSoundLevel;`
- L263 _private member_ `TAttribute<float> TiltExponent;`
- L264 _private member_ `TAttribute<float> TiltPivotFrequency;`
- L265 _private member_ `TAttribute<TOptional<float>> SelectedFrequency;`
- L266 _private member_ `TAttribute<bool> bDisplayCrosshair;`
- L267 _private member_ `TAttribute<bool> bDisplayFrequencyAxisLabels;`
- L268 _private member_ `TAttribute<bool> bDisplaySoundLevelAxisLabels;`
- L269 _private member_ `TAttribute<bool> bDisplayFrequencyGridLines;`
- L270 _private member_ `TAttribute<bool> bDisplaySoundLevelGridLines;`
- L271 _private member_ `TAttribute<EAudioSpectrumPlotFrequencyAxisScale> FrequencyAxisScale;`
- L272 _private member_ `TAttribute<EAudioSpectrumPlotFrequencyAxisPixelBucketMode> FrequencyAxisPixelBucketMode;`
- L273 _private member_ `TAttribute<FSlateColor> BackgroundColor;`
- L274 _private member_ `TAttribute<FSlateColor> GridColor;`
- L275 _private member_ `TAttribute<FSlateColor> AxisLabelColor;`
- L276 _private member_ `TAttribute<FSlateColor> CrosshairColor;`
- L277 _private member_ `TAttribute<FSlateColor> SpectrumColor;`
- L278 _private member_ `TAttribute<bool> bAllowContextMenu;`
- L279 _private member_ `FOnContextMenuOpening OnContextMenuOpening;`
- L280 _private member_ `FOnTiltSpectrumMenuEntryClicked OnTiltSpectrumMenuEntryClicked;`
- L281 _private member_ `FOnFrequencyAxisPixelBucketModeMenuEntryClicked OnFrequencyAxisPixelBucketModeMenuEntryClicked;`
- L282 _private member_ `FOnFrequencyAxisScaleMenuEntryClicked OnFrequencyAxisScaleMenuEntryClicked;`
- L283 _private member_ `FOnDisplayAxisLabelsButtonToggled OnDisplayFrequencyAxisLabelsButtonToggled;`
- L284 _private member_ `FOnDisplayAxisLabelsButtonToggled OnDisplaySoundLevelAxisLabelsButtonToggled;`
- L285 _private member_ `FGetAudioSpectrumData OnGetAudioSpectrumData;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L113 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTiltSpectrumMenuEntryClicked, EAudioSpectrumPlotTilt);`
- L113 _prototype_ `DECLARE_DELEGATE_OneParam(FOnTiltSpectrumMenuEntryClicked, EAudioSpectrumPlotTilt);`
- L114 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFrequencyAxisPixelBucketModeMenuEntryClicked, EAudioSpectrumPlotFrequencyAxisPixelBucketMode);`
- L114 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFrequencyAxisPixelBucketModeMenuEntryClicked, EAudioSpectrumPlotFrequencyAxisPixelBucketMode);`
- L115 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFrequencyAxisScaleMenuEntryClicked, EAudioSpectrumPlotFrequencyAxisScale);`
- L115 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFrequencyAxisScaleMenuEntryClicked, EAudioSpectrumPlotFrequencyAxisScale);`
- L116 _delegate_ `DECLARE_DELEGATE(FOnDisplayAxisLabelsButtonToggled);`
- L116 _prototype_ `DECLARE_DELEGATE(FOnDisplayAxisLabelsButtonToggled);`
- L127 _delegate_ `DECLARE_DELEGATE_RetVal(FAudioPowerSpectrumData, FGetAudioSpectrumData);`
- L127 _prototype_ `DECLARE_DELEGATE_RetVal(FAudioPowerSpectrumData, FGetAudioSpectrumData);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioTextBox.h` (Public)


#### struct `FVariablePrecisionNumericInterface`  
`struct FVariablePrecisionNumericInterface : public TDefaultNumericTypeInterface<float>`  
_L22-48_
- inherits: `TDefaultNumericTypeInterface<float>`
- desc: FVariablePrecisionNumericInterface Taken from PropertyEditor/VariablePrecisionNumericInterface.h Allow more precision as the numbers get closer to zero
- L24 _public function_ `FVariablePrecisionNumericInterface()`
- L26 _public function_ `virtual FString ToString(const float& Value) const override`

#### class `SAudioTextBox`  
`class SAudioTextBox : public SCompoundWidget`  
_L50-106_
- inherits: `SCompoundWidget`
- L53 _private function_ `SLATE_BEGIN_ARGS(SAudioTextBox)`
- L80 _public prototype_ `virtual void Construct(const SAudioTextBox::FArguments& InArgs);`
- L81 _public prototype_ `void SetLabelBackgroundColor(FSlateColor InColor);`
- L82 _public prototype_ `void SetUnitsText(const FText Units);`
- L83 _public prototype_ `void SetValueText(const float OutputValue);`
- L84 _public prototype_ `void SetUnitsTextReadOnly(const bool bIsReadOnly);`
- L85 _public prototype_ `void SetValueTextReadOnly(const bool bIsReadOnly);`
- L86 _public prototype_ `void SetShowLabelOnlyOnHover(const bool bShowLabelOnlyOnHover);`
- L87 _public prototype_ `void SetShowUnitsText(const bool bShowUnitsText);`
- L88 _public prototype_ `void UpdateValueTextWidth(const FVector2D OutputRange);`
- L91 _protected member_ `const FAudioTextBoxStyle* Style;`
- L92 _protected member_ `TSharedPtr<SEditableText> ValueText;`
- L93 _protected member_ `TSharedPtr<SEditableText> UnitsText;`
- L94 _protected member_ `TSharedPtr<SBorder> LabelBorder;`
- L95 _protected member_ `SHorizontalBox::FSlot* ValueTextSlot = nullptr;`
- L97 _protected member_ `TAttribute<bool> ShowLabelOnlyOnHover;`
- L98 _protected member_ `TAttribute<bool> ShowUnitsText;`
- L99 _protected member_ `TAttribute<FSlateColor> LabelBackgroundColor;`
- L100 _protected member_ `FOnTextCommitted OnValueTextCommitted;`
- L102 _protected member_ `FVector2D OutputRange = FVector2D(0.0f, 1.0f);`
- L105 _protected member_ `static const FVariablePrecisionNumericInterface NumericInterface;` — Used to convert and format value text strings

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SAudioVectorscopePanelWidget.h` (Public)


#### class `SAudioVectorscopePanelWidget`  
`class SAudioVectorscopePanelWidget : public SCompoundWidget, public IFixedSampledSequenceViewReceiver`  
_L23-118_
- inherits: `SCompoundWidget,IFixedSampledSequenceViewReceiver`
- L26 _public function_ `SLATE_BEGIN_ARGS(SAudioVectorscopePanelWidget) : _HideGrid(false) , _ValueGridMaxDivisionParameter(2) , _PanelLayoutType(EAudioPanelLayoutType::Basic) , _PanelStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioVectorscopePanelStyle>("AudioVectorscope.PanelStyle"))`
- L33 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, InArgs) SLATE_ATTRIBUTE(bool, HideGrid) SLATE_ARGUMENT(uint32, ValueGridMaxDivisionParameter) SLATE_ARGUMENT(EAudioPanelLayoutType, PanelLayoutType) SLATE_STYLE_ARGUMENT(FAudioVectorscopePanelStyle, PanelStyle) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FFixedSampledSequenceView& InData);`
- L51 _public prototype_ `void BuildWidget(const FFixedSampledSequenceView& InData, const EAudioPanelLayoutType InPanelLayoutType);`
- L54 _public prototype_ `virtual void ReceiveSequenceView(const FFixedSampledSequenceView InData, const uint32 FirstSampleIndex) override;` — IFixedSampledSequenceViewReceiver Interface
- L56 _public prototype_ `void SetGridVisibility(const bool InbIsVisible);`
- L57 _public prototype_ `void SetValueGridOverlayMaxNumDivisions(const uint32 InGridMaxNumDivisions);`
- L59 _public prototype_ `void SetMaxDisplayPersistence(const float InMaxDisplayPersistenceInMs);`
- L61 _public prototype_ `void SetDisplayPersistence(const float InDisplayPersistenceInMs);`
- L62 _public prototype_ `void SetVectorViewerScaleFactor(const float InScaleFactor);`
- L64 _public prototype_ `void UpdateValueGridOverlayStyle(const FSampledSequenceValueGridOverlayStyle UpdatedValueGridOverlayStyle);`
- L65 _public prototype_ `void UpdateSequenceVectorViewerStyle(const FSampledSequenceVectorViewerStyle UpdatedSequenceVectorViewerStyle);`
- L67 _public function_ `EAudioPanelLayoutType GetPanelLayoutType()`
- L69 _public member_ `FOnTimeWindowValueChanged OnDisplayPersistenceValueChanged;`
- L72 _private prototype_ `void CreateLayout();`
- L75 _private prototype_ `void CreateBackground(const FSampledSequenceVectorViewerStyle& VectorViewerStyle);` — Basic panel methods
- L77 _private prototype_ `TSharedPtr<SSampledSequenceValueGridOverlay> CreateValueGridOverlay(const uint32 MaxDivisionParameter, const SampledSequenceValueGridOverlay::EGridDivideMode DivideMode, const FSampledSequenceValueGridOverlayStyle& ValueGridStyle, const SampledSequenceDrawingUtils::ESampledSequenceDrawOrientation GridOrientation);`
- L82 _private prototype_ `void CreateSequenceVectorViewer(const FFixedSampledSequenceView& InData, const FSampledSequenceVectorViewerStyle& VectorViewerStyle);`
- L85 _private prototype_ `void CreateDisplayPersistenceKnob();` — Advanced panel methods
- L86 _private prototype_ `void CreateScaleKnob();`
- L87 _private prototype_ `void CreateVectorscopeControls();`
- L89 _private member_ `const FAudioVectorscopePanelStyle* PanelStyle;`
- L92 _private member_ `TSharedPtr<SBorder> BackgroundBorder;` — Basic panel widgets
- L93 _private member_ `TSharedPtr<SFixedSampledSequenceVectorViewer> SequenceVectorViewer;`
- L94 _private member_ `TSharedPtr<SSampledSequenceValueGridOverlay> ValueGridOverlayXAxis;`
- L95 _private member_ `TSharedPtr<SSampledSequenceValueGridOverlay> ValueGridOverlayYAxis;`
- L98 _private member_ `TSharedPtr<SAudioRadialSlider> DisplayPersistenceKnob;` — Advanced panel widgets
- L99 _private member_ `TSharedPtr<SAudioRadialSlider> ScaleKnob;`
- L101 _private member_ `FVector2D DisplayPersistenceKnobOutputRange = { 10.0, 500.0 };`
- L102 _private member_ `inline static const FVector2D ScaleFactorOutputKnobRange = { 0.0, 1.0 };`
- L104 _private member_ `EAudioPanelLayoutType PanelLayoutType = EAudioPanelLayoutType::Basic;`
- L106 _private member_ `uint32 ValueGridMaxDivisionParameter = 2;`
- L108 _private member_ `bool bIsInputWidgetTransacting = false;`
- L110 _private member_ `float DisplayPersistenceValue = 0.0f;`
- L111 _private member_ `float ScaleValue = 0.0f;`
- L113 _private member_ `float VectorscopeViewProportion = 1.0f;`
- L115 _private member_ `FFixedSampledSequenceView DataView;`
- L117 _private member_ `bool bHideValueGrid = false;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeWindowValueChanged, const float ) class SAudioVectorscopePanelWidget : public SCompoundWidget, public IFixedSampledSequenceViewReceiver { public: SLATE_BEGIN_ARGS(SAudioVectorscopePanelWidget) : _HideGrid(false) , _ValueGridMaxDivisionParameter(2) , _PanelLayoutType(EAudioPanelLayoutType::Basic) , _PanelStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle<FAudioVectorscopePanelStyle>("AudioVectorscope.PanelStyle")) {} SLATE_DEFAULT_SLOT(FArguments, InArgs) SLATE_ATTRIBUTE(bool, HideGrid) SLATE_ARGUMENT(uint32, ValueGridMaxDivisionParameter) SLATE_ARGUMENT(EAudioPanelLayoutType, PanelLayoutType) SLATE_STYLE_ARGUMENT(FAudioVectorscopePanelStyle, PanelStyle) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FFixedSampledSequenceView& InData); void BuildWidget(const FFixedSampledSequenceView& InData, const EAudioPanelLayoutType InPanelLayoutType);`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SFixedSampledSequenceRuler.h` (Public)


#### class `SFixedSampledSequenceRuler`  
`class SFixedSampledSequenceRuler : public SCompoundWidget`  
_L17-80_
- inherits: `SCompoundWidget`
- L19 _private function_ `SLATE_BEGIN_ARGS(SFixedSampledSequenceRuler) : _DisplayUnit(ESampledSequenceDisplayUnit::Seconds)`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IFixedSampledSequenceGridService> InGridService);`
- L35 _public prototype_ `void UpdateGridMetrics();`
- L36 _public prototype_ `void UpdateDisplayUnit(const ESampledSequenceDisplayUnit InDisplayUnit);`
- L37 _public prototype_ `void SetPlayheadPosition(const float InNewPosition);`
- L38 _public prototype_ `void OnStyleUpdated(const FFixedSampleSequenceRulerStyle UpdatedStyle);`
- L39 _public prototype_ `FReply LaunchContextMenu();`
- L41 _public prototype_ `void SetPlayheadVisible(bool Enable);`
- L44 _public member_ `FOnTimeUnitMenuSelection OnTimeUnitMenuSelection;` — Delegate sent when the user selects a new display unit from the RMB menu
- L47 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L48 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L50 _private prototype_ `void DrawPlayheadHandle(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId) const;`
- L51 _private prototype_ `void DrawRulerTicks(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId) const;`
- L52 _private prototype_ `void DrawTickTimeString(uint32 TickFrame, const double TickX, const double TickY, FSlateWindowElementList& OutDrawElements, int32& LayerId, const FGeometry& AllottedGeometry) const;`
- L54 _private prototype_ `TSharedRef<SWidget> MakeContextMenu();`
- L55 _private prototype_ `void MakeTimeUnitsSubMenu(FMenuBuilder& SubMenuBuilder);`
- L56 _private prototype_ `void NotifyTimeUnitMenuSelection(const ESampledSequenceDisplayUnit SelectedDisplayUnit) const;`
- L58 _private member_ `FFixedSampledSequenceGridMetrics GridMetrics;`
- L60 _private member_ `FSlateColor BackgroundColor = FLinearColor::Black;`
- L61 _private member_ `FSlateBrush BackgroundBrush;`
- L62 _private member_ `FSlateBrush HandleBrush;`
- L63 _private member_ `FSlateColor HandleColor = FLinearColor(255.f, 0.1f, 0.2f, 1.f);`
- L64 _private member_ `FSlateColor TicksColor = FLinearColor(1.f, 1.f, 1.f, 0.9f);`
- L65 _private member_ `FSlateColor TicksTextColor = FLinearColor(1.f, 1.f, 1.f, 0.9f);`
- L67 _private member_ `float DesiredHeight = 0.f;`
- L68 _private member_ `float DesiredWidth = 0.f;`
- L69 _private member_ `float HandleWidth = 15.f;`
- L70 _private member_ `float TicksTextOffset = 5.f;`
- L71 _private member_ `float PlayheadPosition = 0.f;`
- L73 _private member_ `FSlateFontInfo TicksTextFont;`
- L75 _private member_ `TSharedPtr<IFixedSampledSequenceGridService> GridService = nullptr;`
- L77 _private member_ `ESampledSequenceDisplayUnit DisplayUnit;`
- L79 _private member_ `bool bDisplayPlayhead = true;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeUnitMenuSelection, const ESampledSequenceDisplayUnit );`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeUnitMenuSelection, const ESampledSequenceDisplayUnit );`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SFixedSampledSequenceVectorViewer.h` (Public)


#### class `SFixedSampledSequenceVectorViewer`  
`class SFixedSampledSequenceVectorViewer : public SLeafWidget`  
_L14-61_
- inherits: `SLeafWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SFixedSampledSequenceVectorViewer) : _ScaleFactor(1.0f)`
- L22 _public prototype_ `SLATE_ARGUMENT(SampledSequenceDrawingUtils::FSampledSequenceDrawingParams, SequenceDrawingParams) SLATE_ARGUMENT(float, ScaleFactor) SLATE_STYLE_ARGUMENT(FSampledSequenceVectorViewerStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TArrayView<const float> InSampleData, const uint8 InNumChannels);`
- L32 _public prototype_ `void UpdateView(TArrayView<const float> InSampleData, const uint8 InNumChannels);`
- L33 _public prototype_ `void SetScaleFactor(const float InScaleFactor);`
- L34 _public prototype_ `void OnStyleUpdated(const FSampledSequenceVectorViewerStyle UpdatedStyle);`
- L37 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L45 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L47 _private member_ `bool bForceRedraw = false;`
- L49 _private member_ `TArrayView<const float> SampleData;`
- L50 _private member_ `SampledSequenceDrawingUtils::FSampledSequenceDrawingParams DrawingParams;`
- L52 _private member_ `uint8 NumChannels = 0;`
- L54 _private member_ `float DesiredHeight = 720.0f;`
- L55 _private member_ `float DesiredWidth = 720.0f;`
- L57 _private member_ `FLinearColor LineColor = FLinearColor::White;`
- L58 _private member_ `float LineThickness = 1.0f;`
- L60 _private member_ `float ScaleFactor = 1.0f;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SFixedSampledSequenceViewer.h` (Public)


#### class `SFixedSampledSequenceViewer`  
`class SFixedSampledSequenceViewer : public SLeafWidget`  
_L19-89_
- inherits: `SLeafWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SFixedSampledSequenceViewer) : _HideBackground(false) , _HideGrid(false)`
- L29 _public prototype_ `SLATE_ARGUMENT(SampledSequenceDrawingUtils::FSampledSequenceDrawingParams, SequenceDrawingParams) SLATE_ARGUMENT(bool, HideBackground) SLATE_ARGUMENT(bool, HideGrid) SLATE_STYLE_ARGUMENT(FSampledSequenceViewerStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TArrayView<const float> InSampleData, const uint8 InNumChannels, TSharedRef<IFixedSampledSequenceGridService> InGridService);`
- L40 _public prototype_ `void UpdateView(TArrayView<const float> InSampleData, const uint8 InNumChannels);`
- L42 _public prototype_ `void OnStyleUpdated(const FSampledSequenceViewerStyle UpdatedStyle);`
- L44 _public prototype_ `void UpdateGridMetrics();`
- L46 _public prototype_ `void SetHideGrid(const bool InHideGrid);`
- L49 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L50 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L51 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L53 _private prototype_ `void DrawGridLines(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32& LayerId) const;`
- L55 _private member_ `bool bForceRedraw = false;`
- L57 _private member_ `TArrayView<const float> SampleData;`
- L58 _private member_ `uint8 NumChannels = 0;`
- L59 _private member_ `float DurationInSeconds = 0.f;`
- L61 _private member_ `TSharedPtr<IFixedSampledSequenceGridService> GridService = nullptr;`
- L62 _private member_ `FFixedSampledSequenceGridMetrics GridMetrics;`
- L64 _private member_ `FSlateBrush BackgroundBrush;`
- L65 _private member_ `FSlateColor BackgroundColor = FLinearColor(0.02f, 0.02f, 0.02f, 1.f);`
- L66 _private member_ `FSlateColor SequenceColor = FLinearColor::White;`
- L67 _private member_ `FSlateColor MajorGridLineColor = FLinearColor::Black;`
- L68 _private member_ `FSlateColor MinorGridLineColor = FLinearColor(0.f, 0.f, 0.f, 0.5f);`
- L69 _private member_ `FSlateColor ZeroCrossingLineColor = FLinearColor::Black;`
- L70 _private member_ `float ZeroCrossingLineThickness = 1.f;`
- L71 _private member_ `float DesiredHeight = 0.f;`
- L72 _private member_ `float DesiredWidth = 0.f;`
- L73 _private member_ `float SampleMarkersSize = 2.5f;`
- L74 _private member_ `float SequenceLineThickness = 1.f;`
- L75 _private member_ `bool bHideBackground = false;`
- L76 _private member_ `bool bHideGrid = false;`
- L78 _private member_ `uint32 CachedPixelWidth = 0;`
- L79 _private member_ `float CachedPixelHeight = 0.f;`
- L80 _private member_ `TArray<SampledSequenceViewerWidget::SampleRange> CachedPeaks;`
- L81 _private member_ `TArray<SampledSequenceDrawingUtils::F2DLineCoordinates> CachedBinsDrawCoordinates;`
- L82 _private member_ `SampledSequenceDrawingUtils::FSampledSequenceDrawingParams DrawingParams;`
- L83 _private member_ `TArray<FVector2D> CachedSampleDrawCoordinates;`
- L88 _private member_ `} SequenceDrawMode;`

#### enum `SFixedSampledSequenceViewer::ESequenceDrawMode`  
`enum class ESequenceDrawMode`  
_L85-88_
- L86 _public enumerator_ `BinnedPeaks = 0`
- L87 _public enumerator_ `SequenceLine`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L14 _namespace_ `namespace SampledSequenceViewerWidget`
- L16 _typedef_ `typedef TRange<float> SampleRange;` (scope `SampledSequenceViewerWidget`)

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SFixedSampledSequenceViewerPanel.h` (Public)


#### class `SFixedSampledSequenceViewerPanel`  
`class SFixedSampledSequenceViewerPanel : public SCompoundWidget, public IFixedSampledSequenceViewReceiver`  
_L23-131_
- inherits: `SCompoundWidget,IFixedSampledSequenceViewReceiver`
- L27 _public function_ `SLATE_BEGIN_ARGS(SFixedSampledSequenceViewerPanel) : _HidePlayhead(false) , _HideSamplesGrid(false) , _HideSamplesRuler(false) , _HideValueGrid(false) , _ValueGridDivideMode(SampledSequenceValueGridOverlay::EGridDivideMode::MidSplit) , _ValueGridMaxDivisionParameter(2) , _SequenceDrawingParams(SampledSequenceDrawingUtils::FSampledSequenceDrawingParams()) , _SamplesRulerDisplayUnit(ESampledSequenceDisplayUnit::Seconds) , _SequenceViewerStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle< FSampledSequenceViewerStyle >("SampledSequenceViewer.Style")) , _SamplesRulerStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle< FFixedSampleSequenceRulerStyle >("FixedSampledSequenceRuler.Style")) , _PlayheadOverlayStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle< FPlayheadOverlayStyle >("PlayheadOverlay.Style")) , _ValueGridStyle(&FAudioWidgetsStyle::Get().GetWidgetStyle< FSampledSequenceValueGridOverlayStyle >("ValueGridOverlay.Style"))`
- L42 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, InArgs) SLATE_ATTRIBUTE(bool, HidePlayhead) SLATE_ATTRIBUTE(bool, HideSamplesGrid) SLATE_ATTRIBUTE(bool, HideSamplesRuler) SLATE_ATTRIBUTE(bool, HideValueGrid) SLATE_ARGUMENT(SampledSequenceValueGridOverlay::EGridDivideMode, ValueGridDivideMode) SLATE_ARGUMENT(uint32, ValueGridMaxDivisionParameter) SLATE_ARGUMENT(TFunction<FText(const double)>, ValueGridLabelGenerator) SLATE_ARGUMENT(SampledSequenceDrawingUtils::FSampledSequenceDrawingParams, SequenceDrawingParams) SLATE_ARGUMENT(ESampledSequenceDisplayUnit, SamplesRulerDisplayUnit) SLATE_STYLE_ARGUMENT(FSampledSequenceViewerStyle, SequenceViewerStyle) SLATE_STYLE_ARGUMENT(FFixedSampleSequenceRulerStyle, SamplesRulerStyle) SLATE_STYLE_ARGUMENT(FPlayheadOverlayStyle, PlayheadOverlayStyle) SLATE_STYLE_ARGUMENT(FSampledSequenceValueGridOverlayStyle, ValueGridStyle)`
- L87 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L90 _public prototype_ `virtual void ReceiveSequenceView(const FFixedSampledSequenceView InData, const uint32 FirstSampleIndex) override;` — IFixedSampledSequenceViewReceiver Interface
- L92 _public prototype_ `void SetPlayheadRatio(const float InRatio);`
- L94 _public prototype_ `void UpdateSequenceViewerStyle(const FSampledSequenceViewerStyle UpdatedStyle);`
- L95 _public prototype_ `void UpdateRulerStyle(const FFixedSampleSequenceRulerStyle UpdatedStyle);`
- L96 _public prototype_ `void UpdatePlayheadOverlayStyle(const FPlayheadOverlayStyle UpdatedStyle);`
- L97 _public prototype_ `void UpdateValueGridOverlayStyle(const FSampledSequenceValueGridOverlayStyle UpdatedStyle);`
- L100 _private prototype_ `virtual void CreateLayout();`
- L102 _private member_ `TSharedPtr<FFixedSampledSequenceGridData> SamplesGridData;`
- L103 _private member_ `TSharedPtr<SBorder> BackgroundBorder;`
- L104 _private member_ `TSharedPtr<SFixedSampledSequenceRuler> SamplesRuler;`
- L105 _private member_ `TSharedPtr<SFixedSampledSequenceViewer> SequenceViewer;`
- L106 _private member_ `TSharedPtr<SPlayheadOverlay> PlayheadOverlay;`
- L107 _private member_ `TSharedPtr<SSampledSequenceValueGridOverlay> ValueGridOverlay;`
- L110 _private prototype_ `void CreateGridData(const FFixedSampleSequenceRulerStyle* RulerStyle);`
- L111 _private prototype_ `void CreatePlayheadOverlay(const FPlayheadOverlayStyle* PlayheadOverlayStyle);`
- L112 _private prototype_ `void CreateValueGridOverlay(const uint32 MaxDivisionParameter, const SampledSequenceValueGridOverlay::EGridDivideMode DivideMode, const TFunction<FText(const double)>& LabelGenerator, const FSampledSequenceValueGridOverlayStyle* ValueGridStyle);`
- L113 _private prototype_ `void CreateSamplesRuler(TSharedRef<FFixedSampledSequenceGridData> InGridData, const FFixedSampleSequenceRulerStyle* RulerStyle);`
- L114 _private prototype_ `void CreateSequenceViewer(TSharedRef<FFixedSampledSequenceGridData> InGridData, const FFixedSampledSequenceView& InData, const FSampledSequenceViewerStyle* ViewerStyle);`
- L115 _private prototype_ `void CreateBackground(const FSampledSequenceViewerStyle* ViewerStyle);`
- L117 _private prototype_ `void UpdateSamplesRulerDisplayUnit(const ESampledSequenceDisplayUnit InDisplayUnit);`
- L118 _private prototype_ `void UpdatePlayheadPosition(const float PaintedWidth);`
- L120 _private member_ `float CachedPixelWidth = 0.f;`
- L122 _private member_ `ESampledSequenceDisplayUnit SamplesRulerDisplayUnit;`
- L123 _private member_ `FFixedSampledSequenceView DataView;`
- L124 _private member_ `SampledSequenceDrawingUtils::FSampledSequenceDrawingParams DrawingParams;`
- L126 _private member_ `float CachedPlayheadRatio = 0.f;`
- L127 _private member_ `bool bHidePlayhead = false;`
- L128 _private member_ `bool bHideSamplesGrid = false;`
- L129 _private member_ `bool bHideSamplesRuler = false;`
- L130 _private member_ `bool bHideValueGrid = false;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SPlayheadOverlay.h` (Public)


#### class `SPlayheadOverlay`  
`class SPlayheadOverlay : public SLeafWidget`  
_L12-44_
- inherits: `SLeafWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SPlayheadOverlay)`
- L19 _public prototype_ `SLATE_STYLE_ARGUMENT(FPlayheadOverlayStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _public prototype_ `void SetPlayheadPosition(const float InNewPosition);`
- L25 _public prototype_ `void OnStyleUpdated(const FPlayheadOverlayStyle UpdatedStyle);`
- L27 _public prototype_ `void SetPlayheadVisible(bool Enable);`
- L30 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L31 _private prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L33 _private prototype_ `int32 DrawPlayhead(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L35 _private member_ `const FPlayheadOverlayStyle* Style = nullptr;`
- L37 _private member_ `FSlateColor PlayheadColor = FLinearColor(255.f, 0.1f, 0.2f, 1.f);`
- L38 _private member_ `float PlayheadWidth = 1.0;`
- L39 _private member_ `float DesiredWidth = 0.f;`
- L40 _private member_ `float DesiredHeight = 0.f;`
- L42 _private member_ `float PlayheadPosition = 0.f;`
- L43 _private member_ `bool bIsVisible = true;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SSampledSequenceValueGridOverlay.h` (Public)


#### enum `SampledSequenceValueGridOverlay::EGridDivideMode`  
`enum class EGridDivideMode`  
_L15-20_
- L17 _public enumerator_ `EvenSplit = 0`
- L18 _public enumerator_ `MidSplit`
- L19 _public enumerator_ `COUNT`

#### class `SSampledSequenceValueGridOverlay`  
`class SSampledSequenceValueGridOverlay : public SLeafWidget`  
_L23-106_
- inherits: `SLeafWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SSampledSequenceValueGridOverlay) : _DivideMode(SampledSequenceValueGridOverlay::EGridDivideMode::EvenSplit) , _NumDimensions(1) , _HideLabels(false) , _HideGrid(false) , _MaxDivisionParameter(2)`
- L35 _public prototype_ `SLATE_ARGUMENT(SampledSequenceValueGridOverlay::EGridDivideMode, DivideMode) SLATE_ARGUMENT(uint32, NumDimensions) SLATE_ARGUMENT(bool, HideLabels) SLATE_ARGUMENT(bool, HideGrid) SLATE_ARGUMENT(uint32, MaxDivisionParameter) SLATE_ARGUMENT(SampledSequenceDrawingUtils::FSampledSequenceDrawingParams, SequenceDrawingParams) SLATE_ARGUMENT(TFunction<FText(const double)>, ValueGridLabelGenerator) SLATE_STYLE_ARGUMENT(FSampledSequenceValueGridOverlayStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L55 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L56 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L57 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L58 _public prototype_ `void OnStyleUpdated(const FSampledSequenceValueGridOverlayStyle UpdatedStyle);`
- L60 _public prototype_ `void SetLabelGenerator(TFunction<FText(const double)> InLabelGenerator);`
- L61 _public prototype_ `void SetMaxDivisionParameter(const uint32 InDivisionParameter);`
- L62 _public prototype_ `void SetHideLabels(const bool InHideLabels);`
- L63 _public prototype_ `void SetHideGrid(const bool InHideGrid);`
- L65 _public prototype_ `void ForceRedraw();`
- L68 _private prototype_ `void CacheDrawElements(const FGeometry& AllottedGeometry, const uint32 InDivisionParameter);`
- L70 _private prototype_ `void GenerateVerticalGridLabels(const uint32 InDivisionParameter, const FGeometry& AllottedGeometry);`
- L71 _private prototype_ `void GenerateHorizontalGridLabels(const uint32 InDivisionParameter, const FGeometry& AllottedGeometry);`
- L74 _private member_ `SampledSequenceValueGridOverlay::EGridDivideMode GridSplitMode;`
- L75 _private member_ `uint32 MaxDivisionParameter;`
- L76 _private member_ `uint32 NumDimensions;`
- L77 _private member_ `TFunction<FText(const double)> OnValueGridLabel;`
- L78 _private member_ `SampledSequenceDrawingUtils::FSampledSequenceDrawingParams DrawingParams;`
- L79 _private member_ `FVector2D CachedLocalSize;`
- L80 _private member_ `bool bForceRedraw = false;`
- L81 _private member_ `bool bHideLabels = false;`
- L82 _private member_ `bool bHideGrid = false;`
- L84 _private member_ `TArray<SampledSequenceDrawingUtils::FGridData> CachedGridSlotData;`
- L85 _private member_ `FNumberFormattingOptions ValueGridFormatOptions;`
- L86 _private member_ `const float LabelToGridPixelDistance = 2;`
- L88 _private member_ `const FSampledSequenceValueGridOverlayStyle* Style = nullptr;`
- L90 _private member_ `FSlateColor GridColor;`
- L91 _private member_ `FSlateColor LabelTextColor;`
- L92 _private member_ `FSlateFontInfo LabelTextFont;`
- L93 _private member_ `float DesiredWidth;`
- L94 _private member_ `float DesiredHeight;`
- L95 _private member_ `float GridThickness;`
- L104 _private member_ `TArray<FGridLabelData> CachedLabelData;`

#### struct `SSampledSequenceValueGridOverlay::FGridLabelData`  
`struct FGridLabelData`  
_L98-102_
- L100 _public member_ `TArray<FText> LabelTexts;`
- L101 _public member_ `TArray<FVector2D> LabelCoordinates;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L13 _namespace_ `namespace SampledSequenceValueGridOverlay`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/STriggerThresholdLineWidget.h` (Public)


#### class `STriggerThresholdLineWidget`  
`class STriggerThresholdLineWidget : public SLeafWidget`  
_L17-52_
- inherits: `SLeafWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(STriggerThresholdLineWidget) : _TriggerThreshold(0.0f) , _Style(&FAudioWidgetsStyle::Get().GetWidgetStyle<FTriggerThresholdLineStyle>("TriggerThresholdLine.Style"))`
- L25 _public prototype_ `SLATE_ARGUMENT(float, TriggerThreshold) SLATE_ARGUMENT(SampledSequenceDrawingUtils::FSampledSequenceDrawingParams, SequenceDrawingParams) SLATE_STYLE_ARGUMENT(FTriggerThresholdLineStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L41 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L43 _public prototype_ `void OnStyleUpdated(const FTriggerThresholdLineStyle UpdatedStyle);`
- L45 _public prototype_ `void SetTriggerThreshold(float InTriggerThreshold);`
- L48 _private member_ `float TriggerThreshold;`
- L49 _private member_ `FLinearColor LineColor;`
- L50 _private member_ `SampledSequenceDrawingUtils::FSampledSequenceDrawingParams DrawingParams;`
- L51 _private member_ `const FTriggerThresholdLineStyle* Style = nullptr;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOWIDGETS_API`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SampledSequenceDisplayUnit.h` (Public)


#### enum `ESampledSequenceDisplayUnit`  
`enum class ESampledSequenceDisplayUnit`  
_L5-9_
- L7 _public enumerator_ `Samples`
- L8 _public enumerator_ `Seconds`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SampledSequenceDrawingUtils.h` (Public)


#### enum `SampledSequenceDrawingUtils::ESampledSequenceDrawOrientation`  
`enum class ESampledSequenceDrawOrientation`  
_L108-113_
- L110 _public enumerator_ `Horizontal = 0`
- L111 _public enumerator_ `Vertical`
- L112 _public enumerator_ `COUNT`

#### struct `SampledSequenceDrawingUtils::FSampledSequenceDrawingParams`  
`struct FSampledSequenceDrawingParams`  
_L116-125_
- L118 _public member_ `double MaxDisplayedValue = 1;`
- L119 _public member_ `float DimensionSlotMargin = 2.f;`
- L120 _public member_ `float MaxSequenceHeightRatio = 0.95f;`
- L121 _public member_ `float MinSequenceHeightRatio = 0.1f;`
- L122 _public member_ `float MinScaledBinValue = 0.1f;`
- L123 _public member_ `float VerticalZoomFactor = 1.f;`
- L124 _public member_ `ESampledSequenceDrawOrientation Orientation = ESampledSequenceDrawOrientation::Horizontal;`

#### struct `SampledSequenceDrawingUtils::FDimensionSlot`  
`struct FDimensionSlot`  
_L130-138_
- desc: Represents a dimensional slot in which samples, sample bins or a grid can be drawn
- L132 _public prototype_ `explicit FDimensionSlot(const uint16 DimensionToDraw, const uint16 TotalNumDimensions, const FGeometry& InAllottedGeometry, const FSampledSequenceDrawingParams& Params);`
- L134 _public member_ `float Top;`
- L135 _public member_ `float Center;`
- L136 _public member_ `float Bottom;`
- L137 _public member_ `float Height;`

#### struct `SampledSequenceDrawingUtils::F2DLineCoordinates`  
`struct F2DLineCoordinates`  
_L140-144_
- L142 _public member_ `FVector2D A;`
- L143 _public member_ `FVector2D B;`

#### struct `SampledSequenceDrawingUtils::FGridData`  
`struct FGridData`  
_L150-154_
- desc: DrawCoordinates: Coordinates of different grid lines PositionRatios: the Ratio of each grid line position in relationship to the main axis length
- L152 _public member_ `TArray<F2DLineCoordinates> DrawCoordinates;`
- L153 _public member_ `TArray<float> PositionRatios;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L13 _namespace_ `namespace SampledSequenceDrawingUtils`
- L29 _function_ `template<typename SamplesType> void GroupInterleavedSamplesIntoMinMaxBins(TArray<TRange<SamplesType>>& OutBins, const uint32 NumDesiredBins, const SamplesType* RawDataPtr, const uint32 TotalNumSamples, const uint16 NDimensions = 1, const double StartRatio = 0.0, double EndRatio = 1.0)` (scope `SampledSequenceDrawingUtils`) — Groups samples evenly into a number of desired bins. Each bin contains the min and max values of the grouped samples. @param OutBins			TArray where the bins will be written to @param NumDesiredBins		Number of output bins @param RawDataPtr			Ptr to the beginning of the samples @param TotalNumSamples	The total number of samples of the input time series @param NDimensions		Number of interleaved dimensions in the time series @param StartRatio			The ratio of the total number of frames (in a range of 0-1) at which grouping should start @param EndRatio			The ratio of the total number of frames (in a range of 0-1) at which grouping should end.
- L89 _function_ `template<typename SamplesType> void GroupInterleavedSampledTSIntoMinMaxBins(TArray<TRange<SamplesType>>& OutBins, const uint32 NumDesiredBins, const SamplesType* RawDataPtr, const uint32 TotalNumSamples, const uint32 SampleRate, const uint16 NDimensions = 1, const float StartTime = 0.f, float EndTime = -1.f)` (scope `SampledSequenceDrawingUtils`) — Groups samples of a time series into an equal number of desired bins. Each bin contains the min and max values of the grouped samples. @param OutBins			TArray where the bins will be written to @param NumDesiredBins		Number of output bins @param RawDataPtr			Ptr to the beginning of the samples @param TotalNumSamples	The total number of samples of the input time series @param SampleRate			SampleRate of the time series @param NDimensions		Number of interleaved dimensions in the time series @param StartTime			The time at which grouping should start @param EndTime 			The time at which grouping should end. Note: With a negative EndTime, the method will calculate automatically the EndTime by doing TotalNumSamples / (SampleRate * NDimensions)
- L166 _prototype_ `void GenerateSampleBinsCoordinatesForGeometry(TArray<F2DLineCoordinates>& OutDrawCoordinates, const FGeometry& InAllottedGeometry, const TArray<TRange<float>>& InSampleBins, const uint16 NDimensions, const FSampledSequenceDrawingParams Params = FSampledSequenceDrawingParams());` (scope `SampledSequenceDrawingUtils`) — Generates an array of coordinates to draw binned samples as vertical lines. Coordinates will be generated for an horizontal view @param OutDrawCoordinates			The generated coordinates @param InAllottedGeometry			The geometry to draw into @param InSampleBins				The bins to draw @param NDimensions				Number of interleaved dimensions in the time series @param Params						Drawing Params
- L178 _prototype_ `void GenerateSequencedSamplesCoordinatesForGeometry(TArray<FVector2D>& OutDrawCoordinates, TArrayView<const float> InSampleData, const FGeometry& InAllottedGeometry, const uint16 NDimensions, const FFixedSampledSequenceGridMetrics InGridMetrics, const FSampledSequenceDrawingParams Params = FSampledSequenceDrawingParams());` (scope `SampledSequenceDrawingUtils`) — Generates an array of coordinates to draw single samples in succession horizontally. @param OutDrawCoordinates			The generated coordinates @param InSampleData				The samples to draw @param InAllottedGeometry			The geometry to draw into @param NDimensions				Number of interleaved dimensions in the time series @param InGridMetrics				GridMetrics followed to lay down the samples @param Params						Drawing Params
- L189 _prototype_ `void GenerateEvenlySplitGridForGeometry(TArray<FGridData>& OutGridData, const FGeometry& InAllottedGeometry, const uint16 NDimensions, const uint32 NumGridDivisions , const FSampledSequenceDrawingParams Params = FSampledSequenceDrawingParams());` (scope `SampledSequenceDrawingUtils`) — Generates an evenly divided grid from a given geometry, following the orientation provided in the Params struct argument. @param OutGridData			The generated grid coordinates and ratios per each dimension @param InAllottedGeometry		The geometry the grid will be drawn into @param NDimensions			Dimensions to account for in the given geometry @param NumGridDivisions		Number of divisions the grid should be split into @param Params					Drawing Params
- L191 _prototype_ `void GenerateEvenlySplitGridForLine(TArray<double>& OutDrawCoordinates, TArray<float>& OutLinePositionRatios, const float LineLength, const uint32 NumGridDivisions , bool bEmptyOutArrays = true);` (scope `SampledSequenceDrawingUtils`)
- L203 _prototype_ `void GenerateMidpointSplitGridForGeometry(TArray<FGridData>& OutGridData, const FGeometry& InAllottedGeometry, const uint16 NDimensions, const uint32 DivisionDepth = 3, const FSampledSequenceDrawingParams Params = FSampledSequenceDrawingParams());` (scope `SampledSequenceDrawingUtils`) — Generates a midline divided grid from a given geometry, following the orientation provided in the Params struct argument. The grid space will be divided in half, with the resulting halves being divided again and so on until the desired Division Depth is reached. @param OutGridData			The generated grid coordinates and ratios per each dimension @param InAllottedGeometry		The geometry the grid will be drawn into @param NDimensions			Dimensions to account for in the given geometry @param DivisionDepth			Number of divisions that should be run @param Params					Drawing Params
- L205 _prototype_ `void GenerateMidpointSplitGridForLine(TArray<double>& OutDrawCoordinates, TArray<float>& OutLinePositionRatios, const float LineLength, const uint32 DivisionDepth = 3, bool bEmptyOutArrays = true);` (scope `SampledSequenceDrawingUtils`)

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SampledSequenceVectorViewerStyle.h` (Public)


#### struct `FSampledSequenceVectorViewerStyle`  
`struct FSampledSequenceVectorViewerStyle : public FSlateWidgetStyle`  
_L15-45_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of a trigger threshold line
- L19 _public function_ `FSampledSequenceVectorViewerStyle()`
- L21 _public function_ `virtual const FName GetTypeName() const override`
- L22 _public function_ `static const FSampledSequenceVectorViewerStyle& GetDefault()`
- L23 _public function_ `virtual void GetResources(TArray< const FSlateBrush* >& OutBrushes) const override`
- L27 _public member_ `FSlateColor BackgroundColor = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The background color.
- L28 _public function_ `FSampledSequenceVectorViewerStyle& SetBackgroundColor(const FSlateColor InBackgroundColor)`
- L31 _public member_ `FSlateBrush BackgroundBrush = FSlateColorBrush(FLinearColor::White);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)`
- L32 _public function_ `FSampledSequenceVectorViewerStyle& SetBackgroundBrush(const FSlateBrush InBackgroundBrush)`
- L36 _public member_ `FLinearColor LineColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The vector view line color.
- L37 _public function_ `FSampledSequenceVectorViewerStyle& SetLineColor(const FLinearColor InLineColor)`
- L41 _public member_ `float LineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The vector view line thickness.
- L42 _public function_ `FSampledSequenceVectorViewerStyle& SetLineThickness(const float InLineThickness)`
- L44 _public member_ `inline static FName TypeName = FName("FSa`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/SparseSampledSequenceTransportCoordinator.h` (Public)


#### class `FSparseSampledSequenceTransportCoordinator`  
`class FSparseSampledSequenceTransportCoordinator : public ISparseSampledSequenceTransportCoordinator`  
_L14-65_
- inherits: `ISparseSampledSequenceTransportCoordinator`
- L17 _public prototype_ `FSparseSampledSequenceTransportCoordinator() = default;`
- L18 _public prototype_ `virtual ~FSparseSampledSequenceTransportCoordinator() = default;`
- L21 _public member_ `FOnFocusPointMoved OnFocusPointMoved;` — Called when the focus point is set to a new location
- L24 _public member_ `FOnFocusPointScrubUpdate OnFocusPointScrubUpdate;` — Called when the focus point is scrubbed
- L27 _public member_ `FOnDisplayRangeUpdated OnDisplayRangeUpdated;` — Called when the display range is updated
- L30 _public prototype_ `const TRange<double> GetDisplayRange() const;` — ISparseSampledSequenceTransportCoordinator interface
- L31 _public prototype_ `const double GetFocusPoint() const override;`
- L32 _public prototype_ `void ScrubFocusPoint(const float InTargetFocusPoint, const bool bIsMoving) override;`
- L33 _public prototype_ `const bool IsScrubbing() const;`
- L34 _public prototype_ `const bool IsScrolling() const;`
- L35 _public prototype_ `void SetScrolling(const bool bInIsScrolling);`
- L36 _public prototype_ `void SetProgressRatio(const float NewRatio) override;`
- L37 _public prototype_ `void SetZoomRatio(const float NewRatio) override;`
- L38 _public prototype_ `float ConvertAbsoluteRatioToZoomed(const float InAbsoluteRatio) const override;`
- L39 _public prototype_ `float ConvertZoomedRatioToAbsolute(const float InZoomedRatio) const override;`
- L40 _public prototype_ `double GetPlayBackRatioFromFocusPoint(const double InFocusPoint) const;`
- L41 _public prototype_ `void UpdatePlaybackRange(const TRange<double>& NewRange);`
- L42 _public prototype_ `void Stop();`
- L44 _public prototype_ `void MoveWaveformView(float MoveAmount);`
- L47 _private prototype_ `inline void MoveFocusPoint(const double InFocusPoint);`
- L48 _private prototype_ `void UpdateZoomRatioAndDisplayRange(const float NewZoomRatio);`
- L50 _private prototype_ `void UpdateDisplayRange(const double MinValue, const double MaxValue);`
- L51 _private prototype_ `bool IsRatioWithinDisplayRange(const double Ratio) const;`
- L53 _private member_ `double FocusPointLockPosition = 0.95f;`
- L54 _private member_ `double FocusPoint = 0;`
- L55 _private member_ `float ZoomRatio = 1.f;`
- L58 _private member_ `TRange<double> DisplayRange = TRange<double>::Inclusive(0, 1);` — The currently displayed render data range
- L61 _private member_ `TRange<double> ProgressRange = TRange<double>::Inclusive(0, 1);` — Progress range to scale the incoming progress ratio with
- L63 _private member_ `bool bIsScrubbing = false;`
- L64 _private member_ `bool bIsScrolling = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisplayRangeUpdated, const TRange<double> );`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisplayRangeUpdated, const TRange<double> );`
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusPointMoved, const double );`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusPointMoved, const double );`
- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFocusPointScrubUpdate, const float , const bool );`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnFocusPointScrubUpdate, const float , const bool );`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/TriggerThresholdLineStyle.h` (Public)


#### struct `FTriggerThresholdLineStyle`  
`struct FTriggerThresholdLineStyle : public FSlateWidgetStyle`  
_L17-32_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of a trigger threshold line
- L21 _public function_ `FTriggerThresholdLineStyle()`
- L23 _public function_ `virtual const FName GetTypeName() const override`
- L24 _public function_ `static const FTriggerThresholdLineStyle& GetDefault()`
- L28 _public member_ `FLinearColor LineColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Appearance)` — The trigger threshold line color.
- L29 _public function_ `FTriggerThresholdLineStyle& SetLineColor(const FLinearColor InLineColor)`
- L31 _public member_ `inline static FName TypeName = FName("FTr`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgets/Public/WaveformAudioSamplesDataProvider.h` (Public)


#### class `AudioWidgets::FWaveformAudioSamplesDataProvider`  
`class FWaveformAudioSamplesDataProvider : public IFixedSampledSequenceViewProvider, public TSharedFromThis<FWaveformAudioSamplesDataProvider>`  
_L29-98_
- inherits: `IFixedSampledSequenceViewProvider,TSharedFromThis<FWaveformAudioSamplesDataProvider>`
- L33 _public prototype_ `FWaveformAudioSamplesDataProvider(const Audio::FDeviceId InAudioDeviceId, UAudioBus* InAudioBus, const uint32 InNumChannelToProvide, const float InTimeWindowMs, const float InMaxTimeWindowMs, const float InAnalysisPeriodMs);`
- L40 _public prototype_ `virtual ~FWaveformAudioSamplesDataProvider();`
- L42 _public prototype_ `void ResetAudioBuffers();`
- L44 _public prototype_ `void StartProcessing();`
- L45 _public prototype_ `void StopProcessing();`
- L47 _public function_ `FFixedSampledSequenceView GetDataView() const`
- L48 _public function_ `uint32 GetNumChannels() const`
- L49 _public function_ `const UAudioBus* GetAudioBus() const`
- L51 _public function_ `float GetMaxTimeWindowMs() const`
- L52 _public prototype_ `void SetMaxTimeWindowMs(const float InMaxTimeWindowMs);`
- L54 _public prototype_ `void SetChannelToAnalyze(const int32 InChannel);`
- L55 _public prototype_ `void SetTriggerMode(const EAudioOscilloscopeTriggerMode InTriggerMode);`
- L56 _public prototype_ `void SetTriggerThreshold(const float InTriggerThreshold);`
- L57 _public prototype_ `void SetTimeWindow(const float InTimeWindowMs);`
- L58 _public prototype_ `void SetAnalysisPeriod(const float InAnalysisPeriodMs);`
- L60 _public prototype_ `virtual FFixedSampledSequenceView RequestSequenceView(const TRange<double> DataRatioRange) override;`
- L62 _public member_ `FOnDataViewGenerated OnDataViewGenerated;`
- L65 _private prototype_ `void PushAudioSamplesToCircularBuffer();`
- L66 _private prototype_ `bool Tick(float DeltaTime);`
- L68 _private member_ `FTSTicker::FDelegateHandle TickerHandle = nullptr;`
- L70 _private member_ `uint32 NumChannelsToProvide = 0;`
- L71 _private member_ `uint32 NumChannels = 0;`
- L72 _private member_ `uint32 SampleRate = 0;`
- L74 _private member_ `float MaxTimeWindowMs = 0.0f;`
- L76 _private member_ `const Audio::FMixerDevice* MixerDevice = nullptr;`
- L78 _private member_ `UAudioBus* AudioBus = nullptr;`
- L79 _private member_ `Audio::FPatchOutputStrongPtr PatchOutput = nullptr;`
- L81 _private member_ `TArray<float> TempAudioBuffer;`
- L82 _private member_ `Audio::TCircularAudioBuffer<float> AudioSamplesCircularBuffer;`
- L83 _private member_ `TArray<float> AudioSamplesForView;`
- L84 _private member_ `FFixedSampledSequenceView DataView;`
- L86 _private member_ `int32 ChannelIndexToAnalyze = 0;`
- L88 _private member_ `EAudioOscilloscopeTriggerMode TriggerMode = EAudioOscilloscopeTriggerMode::None;`
- L89 _private member_ `float TriggerThreshold = 0.0f;`
- L91 _private member_ `uint32 TimeWindowSamples = 0;`
- L92 _private member_ `uint32 AnalysisPeriodSamples = 0;`
- L94 _private member_ `bool bIsProcessing = false;`
- L95 _private member_ `bool bHasTriggered = false;`
- L97 _private member_ `uint32 NumSamplesPushedToCircularBuffer = 0;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API AUDIOWIDGETS_API`
- L16 _namespace_ `namespace Audio`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDataViewGenerated, FFixedSampledSequenceView , const uint32 ) namespace AudioWidgets { class FWaveformAudioSamplesDataProvider : public IFixedSampledSequenceViewProvider, public TSharedFromThis<FWaveformAudioSamplesDataProvider> { public: FWaveformAudioSamplesDataProvider(const Audio::FDeviceId InAudioDeviceId, UAudioBus* InAudioBus, const uint32 InNumChannelToProvide, const float InTimeWindowMs, const float InMaxTimeWindowMs, const float InAnalysisPeriodMs); virtual ~FWaveformAudioSamplesDataProvider(); void ResetAudioBuffers(); void StartProcessing(); void StopProcessing(); FFixedSampledSequenceView GetDataView() const { return DataView; }; uint32 GetNumChannels() const { return NumChannels; } const UAudioBus* GetAudioBus() const { return AudioBus; } float GetMaxTimeWindowMs() const { return MaxTimeWindowMs; } void SetMaxTimeWindowMs(const float InMaxTimeWindowMs); void SetChannelToAnalyze(const int32 InChannel); void SetTriggerMode(const EAudioOscilloscopeTriggerMode InTriggerMode); void SetTriggerThreshold(const float InTriggerThreshold); void SetTimeWindow(const float InTimeWindowMs); void SetAnalysisPeriod(const float InAnalysisPeriodMs); virtual FFixedSampledSequenceView RequestSequenceView(const TRange<double> DataRatioRange) override; FOnDataViewGenerated OnDataViewGenerated; private:`
- L27 _namespace_ `namespace AudioWidgets`
