# Plugins / WaveformTransformations

- module root: `Plugins/Editor/WaveformEditor/Source/WaveformTransformations`
- headers: 11; symbols: 278
- symbol kinds: class=27, delegate=3, enum=3, enumerator=21, function=52, macro=7, member=69, namespace=1, prototype=93, struct=2
- PublicDependencyModuleNames: AudioExtensions, AudioSynesthesiaCore, Core, CoreUObject, Engine, InputCore, PropertyEditor, SignalProcessing, UnrealEd

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Private/WaveformTransformationFadeCustomization.h` (Private)


#### class `FWaveformTransformationFadeCustomization`  
`class FWaveformTransformationFadeCustomization : public IPropertyTypeCustomization`  
_L9-18_
- inherits: `IPropertyTypeCustomization`
- desc: Using IPropertyTypeCustomization to edit the details view of the Fade transformation and remove unneeded information in the waveform editor
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L16 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Private/WaveformTransformationMarkersObjectCustomization.h` (Private)


#### class `FWaveformTransformationMarkersObjectCustomization`  
`class FWaveformTransformationMarkersObjectCustomization : public IPropertyTypeCustomization`  
_L9-18_
- inherits: `IPropertyTypeCustomization`
- desc: Using IPropertyTypeCustomization to edit the details view of the markers transformation and remove unneeded information in the waveform editor
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L16 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Private/WaveformTransformationTrimFadeCustomization.h` (Private)


#### class `FWaveformTransformationTrimFadeCustomization`  
`class FWaveformTransformationTrimFadeCustomization : public IPropertyTypeCustomization`  
_L9-18_
- inherits: `IPropertyTypeCustomization`
- desc: Using IPropertyTypeCustomization to edit the details view of the TrimFade transformation and remove unneeded information in the waveform editor
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L16 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Public/WaveformAudioAnalysisFunctions.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONS_API`
- L9 _namespace_ `namespace WaveformAudioAnalysis`
- L11 _prototype_ `float GetRMSPeak(const Audio::FAlignedFloatBuffer& InputAudio, float SampleRate, int32 NumChannels);` (scope `WaveformAudioAnalysis`)
- L13 _prototype_ `float GetLoudnessPeak(const Audio::FAlignedFloatBuffer& InputAudio, float SampleRate, int32 NumChannels);` (scope `WaveformAudioAnalysis`)
- L15 _prototype_ `float GetPeakSampleValue(const Audio::FAlignedFloatBuffer& InputAudio);` (scope `WaveformAudioAnalysis`)
- L18 _prototype_ `float GetLUFS(const Audio::FAlignedFloatBuffer& InputAudio, float SampleRate, int32 NumChannels);` (scope `WaveformAudioAnalysis`) — Gated Loudness K-Weighted relative to Full Scale (Not-Real-Time)

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Public/WaveformTransformationEffectChain.h` (Public)


#### class `FWaveTransformationEffectChain`  
`class UE_DEPRECATED(5.8, "WaveTransformationEffectChain has been deprecated") FWaveTransformationEffectChain : public Audio::IWaveTransformation`  
_L13-25_
- inherits: `Audio::IWaveTransformation`
- L16 _public prototype_ `FWaveTransformationEffectChain(TArray<TObjectPtr<class USoundEffectSourcePreset>>& InEffectPresets);`
- L18 _public prototype_ `virtual void ProcessAudio(Audio::FWaveformTransformationWaveInfo& InOutWaveInfo) const override;`
- L20 _public function_ `virtual bool SupportsRealtimePreview() const override`
- L21 _public function_ `virtual constexpr Audio::ETransformationPriority FileChangeLengthPriority() const override`
- L24 _private member_ `TArray<TStrongObjectPtr<class USoundEffectSourcePreset>> Presets;`

#### class `UWaveformTransformationEffectChain`  
`class UE_DEPRECATED(5.8, "WaveformTransformationEffectChain has been deprecated") UWaveformTransformationEffectChain : public UWaveformTransformationBase`  
_L31-45_
- reflection: `UCLASS(MinimalAPI, hidden)`
- inherits: `UWaveformTransformationBase`
- desc: USoundEffectPresets need diff tag hashes ONLY IF linked to waveform transformations. Removing their connection to waveform transformations is sufficient to avoid the need for cook diff tag support for USoundEffectSourcePresets. This done by deprecating WaveformTransformationEffectChain.
- L36 _private member_ `TObjectPtr<class USoundEffectSourcePresetChain> EffectChain;` — `UPROPERTY(EditAnywhere, Category = "Trim")`
- L39 _private member_ `TArray<TObjectPtr<class USoundEffectSourcePreset>> InlineEffects;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Trim")`
- L43 _public prototype_ `virtual Audio::FTransformationPtr CreateTransformation() const override;`
- L44 _public function_ `virtual FString GetTransformationHash() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONS_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Public/WaveformTransformationFade.h` (Public)


#### class `UTransformationFadeFunction`  
`class UTransformationFadeFunction : public UObject`  
_L13-26_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories, NotBlueprintable)`
- inherits: `UObject`
- L18 _public function_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const`
- L19 _public function_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const`
- L22 _public member_ `float Duration = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Fade", BlueprintReadWrite, meta = (ClampMin = 0.0, DisplayName = "Fade Duration"))`
- L25 _public member_ `int64 FrameOffset = 0;` — `UPROPERTY(EditAnywhere, Category = "Fade", BlueprintReadWrite, meta = (ClampMin = 0.0, DisplayName = "Fade Frame Offset"))`

#### class `UTransformationFadeCurveFunction`  
`class UTransformationFadeCurveFunction : public UTransformationFadeFunction`  
_L29-44_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories, NotBlueprintable)`
- inherits: `UTransformationFadeFunction`
- L34 _public function_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override`
- L35 _public function_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override`
- L37 _public function_ `virtual void SetFadeCurve(const float InFadeCurve)`
- L38 _public function_ `virtual const float GetFadeCurve() const`
- L39 _public function_ `virtual const FText GetFadeCurvePropertyName() const`
- L42 _protected function_ `virtual const float GetFadeCurveMin() const`
- L43 _protected function_ `virtual const float GetFadeCurveMax() const`

#### class `UTransformationFadeFunctionLinear`  
`class UTransformationFadeFunctionLinear : public UTransformationFadeFunction`  
_L47-54_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Linear"))`
- inherits: `UTransformationFadeFunction`
- L52 _public prototype_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override;`
- L53 _public prototype_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override;`

#### class `UTransformationFadeCurveFunctionExponential`  
`class UTransformationFadeCurveFunctionExponential : public UTransformationFadeCurveFunction`  
_L57-75_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Exponential"))`
- inherits: `UTransformationFadeCurveFunction`
- L62 _public prototype_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override;`
- L63 _public prototype_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override;`
- L65 _public function_ `virtual void SetFadeCurve(const float InFadeCurve) override`
- L66 _public function_ `virtual const float GetFadeCurve() const override`
- L67 _public function_ `virtual const FText GetFadeCurvePropertyName() const override`
- L70 _public member_ `float FadeCurve = 3.f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 1, ClampMax = 10.0, DisplayName = "Fade Curve"))`
- L73 _protected function_ `virtual const float GetFadeCurveMin() const override`
- L74 _protected function_ `virtual const float GetFadeCurveMax() const override`

#### class `UTransformationFadeCurveFunctionLogarithmic`  
`class UTransformationFadeCurveFunctionLogarithmic : public UTransformationFadeCurveFunction`  
_L78-92_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Logarithmic"))`
- inherits: `UTransformationFadeCurveFunction`
- L83 _public prototype_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override;`
- L84 _public prototype_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override;`
- L86 _public function_ `virtual void SetFadeCurve(const float InFadeCurve) override`
- L87 _public function_ `virtual const float GetFadeCurve() const override`
- L88 _public function_ `virtual const FText GetFadeCurvePropertyName() const override`
- L91 _public member_ `float FadeCurve = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 0.0, ClampMax = 1, DisplayName = "Fade Curve"))`

#### class `UTransformationFadeCurveFunctionSigmoid`  
`class UTransformationFadeCurveFunctionSigmoid : public UTransformationFadeCurveFunction`  
_L95-109_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Sigmoid"))`
- inherits: `UTransformationFadeCurveFunction`
- L100 _public prototype_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override;`
- L101 _public prototype_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override;`
- L103 _public function_ `virtual void SetFadeCurve(const float InFadeCurve) override`
- L104 _public function_ `virtual const float GetFadeCurve() const override`
- L105 _public function_ `virtual const FText GetFadeCurvePropertyName() const override`
- L108 _public member_ `float SigmoidFadeCurve = 0.6f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 0.0, ClampMax = 1, DisplayName = "S-Fade Curve"))`

#### struct `FTransformationFadeFunctionData`  
`struct FTransformationFadeFunctionData`  
_L112-124_
- reflection: `USTRUCT()`
- L117 _public member_ `TObjectPtr<UTransformationFadeFunction> FadeIn;` — `UPROPERTY(EditAnywhere, Category = "Fade", Instanced, meta = (DisplayName = "Fade In Type"))`
- L120 _public member_ `TObjectPtr<UTransformationFadeFunction> FadeOut;` — `UPROPERTY(EditAnywhere, Category = "Fade", Instanced, meta = (DisplayName = "Fade Out Type"))`
- L123 _public member_ `bool bLinkDurations = false;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (DisplayName = "Link Fade Durations"))`

#### enum `EWaveEditorTransformationFadeMode`  
`enum class EWaveEditorTransformationFadeMode : uint8`  
_L127-133_
- reflection: `UENUM()`
- L129 _public enumerator_ `Linear = 0`
- L130 _public enumerator_ `Exponential`
- L131 _public enumerator_ `Logarithmic`
- L132 _public enumerator_ `Sigmoid`

#### class `FWaveTransformationFade`  
`class FWaveTransformationFade : public Audio::IWaveTransformation`  
_L135-146_
- inherits: `Audio::IWaveTransformation`
- L138 _public prototype_ `explicit FWaveTransformationFade(const TArray<FTransformationFadeFunctionData>& InFadeRegions, const int64 InStartFrameOffset, const int64 InEndFrameOffset);`
- L139 _public prototype_ `virtual void ProcessAudio(Audio::FWaveformTransformationWaveInfo& InOutWaveInfo) const override;`
- L143 _private member_ `TArray<FTransformationFadeFunctionData> FadeRegions;`
- L144 _private member_ `int64 StartFrameOffset = 0;`
- L145 _private member_ `int64 EndFrameOffset = 0;`

#### class `UWaveformTransformationFade`  
`class UWaveformTransformationFade final : public UWaveformTransformationBase`  
_L152-200_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWaveformTransformationBase`
- desc: Maintains an array of fade regions that can be placed in any location on the waveform. Each region has a start and end fade with optional offsets from the start and end of the waveform This transformation can be used in other transformation (ex. TrimFade)
- L157 _public prototype_ `UWaveformTransformationFade(const FObjectInitializer& ObjectInitializer);`
- L160 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L162 _public prototype_ `virtual FString GetTransformationHash() const override;`
- L165 _public member_ `static const TMap<EWaveEditorTransformationFadeMode, TSubclassOf<UTransformationFadeFunction>> FadeModeToFadeFunctionMap;`
- L167 _public prototype_ `virtual Audio::FTransformationPtr CreateTransformation() const override;`
- L169 _public prototype_ `void UpdateConfiguration(FWaveTransformUObjectConfiguration& InOutConfiguration) override;`
- L171 _public function_ `const float GetSampleRate() const`
- L173 _public function_ `const int32 GetFadeRegionsNum() const`
- L174 _public function_ `const TArray<FTransformationFadeFunctionData>& GetFadeRegions() const`
- L175 _public function_ `TArray<FTransformationFadeFunctionData>& GetMutableFadeRegions()`
- L179 _public prototype_ `void LimitFadeRegionsToOne();` — Remove all fade regions other than the first one. Logs a warning if it removes any fade regions
- L181 _public function_ `static FName GetFadeRegionsPropertyName()`
- L188 _protected member_ `TArray<FTransformationFadeFunctionData> FadeRegions;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (DisplayName = "Fade Regions"))`
- L193 _private prototype_ `void UpdateDurationProperties(const float InAvailableDuration);`
- L194 _private member_ `float AvailableWaveformDuration = -1.f;`
- L195 _private member_ `float SampleRate = 0.f;`
- L197 _private member_ `int64 StartFrameOffset = 0;`
- L198 _private member_ `int64 EndFrameOffset = 0;`
- L199 _private member_ `int64 OriginalNumFrames = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONS_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Public/WaveformTransformationLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONS_API`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWaveformTransformation, Log, All);`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Public/WaveformTransformationMarkers.h` (Public)


#### enum `ELoopModificationControls`  
`enum class ELoopModificationControls : uint8`  
_L14-29_
- L16 _public enumerator_ `None = 0`
- L17 _public enumerator_ `LeftHandleIncrement`
- L18 _public enumerator_ `LeftHandleDecrement`
- L19 _public enumerator_ `RightHandleIncrement`
- L20 _public enumerator_ `RightHandleDecrement`
- L21 _public enumerator_ `IncreaseIncrement`
- L22 _public enumerator_ `DecreaseIncrement`
- L23 _public enumerator_ `SelectNextLoop`
- L24 _public enumerator_ `SelectPreviousLoop`
- L25 _public enumerator_ `LeftHandleNextZeroCrossing`
- L26 _public enumerator_ `LeftHandlePreviousZeroCrossing`
- L27 _public enumerator_ `RightHandleNextZeroCrossing`
- L28 _public enumerator_ `RightHandlePreviousZeroCrossing`

#### class `UWaveCueArray`  
`class UWaveCueArray : public UObject`  
_L33-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DefaultToInstanced)`
- inherits: `UObject`
- desc: Used to make CuePoints work with PropertyHandles
- L38 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _public prototype_ `void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L44 _public prototype_ `void InitMarkersIfNotSet(const TArray<FSoundWaveCuePoint>& InMarkers);` — If uninitialized, init Marker array
- L46 _public prototype_ `void Reset();` — Uninitialize and empty Marker array
- L48 _public prototype_ `void EnableLoopRegion(FSoundWaveCuePoint* OutSoundWaveCue, bool bSetLoopRegion = true);`
- L51 _public member_ `TArray<FSoundWaveCuePoint> CuesAndLoops;` — `UPROPERTY(EditAnywhere, Category = "Markers")`
- L52 _public member_ `int32 SelectedCue = INDEX_NONE;`
- L57 _public prototype_ `DECLARE_DELEGATE_OneParam(ModifyMarkerLoopRegionDelegate, ELoopModificationControls);` — `UE_DEPRECATED(5.7, "ModifyMarkerLoopRegionDelegate has been deprecated.")`
- L59 _public member_ `ModifyMarkerLoopRegionDelegate ModifyMarkerLoop;` — `UE_DEPRECATED(5.7, "ModifyMarkerLoop has been deprecated.")`
- L62 _public prototype_ `DECLARE_DELEGATE_OneParam(CycleMarkerLoopRegionDelegate, ELoopModificationControls);` — `UE_DEPRECATED(5.7, "CycleMarkerLoopRegionDelegate has been deprecated.")`
- L64 _public member_ `CycleMarkerLoopRegionDelegate CycleMarkerLoop;` — `UE_DEPRECATED(5.7, "CycleMarkerLoop has been deprecated.")`
- L69 _public member_ `static constexpr int64 MinLoopSize = 10;` — To minimize complexity while supporting all common editing cases, loops have a min length of 10 frames
- L71 _public prototype_ `DECLARE_DELEGATE(OnCueChange);`
- L72 _public member_ `OnCueChange CueChanged;`
- L76 _private member_ `bool bIsInitialized = false;` — `UPROPERTY()`

#### class `FWaveTransformationMarkers`  
`class FWaveTransformationMarkers : public Audio::IWaveTransformation`  
_L79-90_
- inherits: `Audio::IWaveTransformation`
- L82 _public prototype_ `explicit FWaveTransformationMarkers(double InStartLoopTime, double InEndLoopTime);`
- L83 _public prototype_ `virtual void ProcessAudio(Audio::FWaveformTransformationWaveInfo& InOutWaveInfo) const override;`
- L85 _public function_ `virtual constexpr Audio::ETransformationPriority FileChangeLengthPriority() const override`
- L88 _private member_ `double StartLoopTime = 0.0;`
- L89 _private member_ `double EndLoopTime = 0.0;`

#### class `UWaveformTransformationMarkers`  
`class UWaveformTransformationMarkers final : public UWaveformTransformationBase`  
_L93-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWaveformTransformationBase`
- L97 _public prototype_ `UWaveformTransformationMarkers(const FObjectInitializer& ObjectInitializer);`
- L100 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L102 _public prototype_ `virtual void PostEditUndo() override;`
- L106 _public member_ `TObjectPtr<UWaveCueArray> Markers;` — `UPROPERTY(VisibleAnywhere, Category = "Markers")`
- L110 _public member_ `double StartLoopTime = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Loop Preview", meta = (ClampMin = 0.0))` — These properties are hidden in editor by an IPropertyTypeCustomization
- L113 _public member_ `double EndLoopTime = -1.0;` — `UPROPERTY(EditAnywhere, Category = "Loop Preview")` — When EndLoopTime is < 0 it skips processing the audio in FWaveTransformationMarkers::ProcessAudio
- L116 _protected member_ `bool bIsPreviewingLoopRegion = false;` — `UPROPERTY(EditAnywhere, Category = "Loop Preview")`
- L118 _public prototype_ `virtual Audio::FTransformationPtr CreateTransformation() const override;`
- L120 _public prototype_ `void UpdateConfiguration(FWaveTransformUObjectConfiguration& InOutConfiguration) override;`
- L121 _public prototype_ `void OverwriteTransformation() override;`
- L124 _public prototype_ `void ModifyMarkerLoopRegion(ELoopModificationControls Modification) const;` — `UE_DEPRECATED(5.7, "ModifyMarkerLoopRegion const has been deprecated, use the non-const version")`
- L126 _public prototype_ `void CycleMarkerLoopRegion(ELoopModificationControls Modification) const;` — `UE_DEPRECATED(5.7, "CycleMarkerLoopRegion const has been deprecated, use the non-const version")`
- L129 _public prototype_ `void ModifyMarkerLoopRegion(ELoopModificationControls Modification, const TArray<float> &PCMArray, float NoiseThreshold = 0.01f);` — Shift marker and loop region bounds with toolkit commands bound in the waveform editor
- L131 _public prototype_ `void CycleMarkerLoopRegion(ELoopModificationControls Modification);` — Set SelectedCue by cycling through cues and loops with toolkit commands bound in the waveform editor
- L133 _public prototype_ `static int64 GetFramesToNextZeroCrossing(int64 StartFrame, int64 EndFrame, const TArray<float>& PCMArray, bool bCheckIncrementing, float NoiseThreshold, int ChannelCount);`
- L134 _public prototype_ `static int64 CheckZeroCrossingFrame(int64 CurrentSample, const TArray<float>& PCMArray, bool& bAllSamplesPositiveLastHighNoise, bool& bAllSamplesNegativeLastHighNoise, float NoiseThreshold, int ChannelCount);`
- L136 _public prototype_ `bool IsLoopRegionActive() const;`
- L137 _public prototype_ `void SetLoopPreviewing();`
- L140 _public prototype_ `bool ResetLoopPreviewing();` — Returns true if reset
- L142 _public prototype_ `bool AdjustLoopPreviewIfNotAligned();` — Returns true if reset
- L145 _public prototype_ `virtual void OverwriteSoundWaveData(USoundWave& InOutSoundWave) override;`
- L146 _public prototype_ `virtual void GetTransformationInfo(FWaveformTransformationInfo& InOutTransformationInfo) const override;`
- L147 _public prototype_ `virtual FString GetTransformationHash() const override;`
- L150 _public prototype_ `FSoundWaveCuePoint* GetSelectedMarker() const;`
- L154 _private prototype_ `void PreviewSelectedLoop();`
- L155 _private prototype_ `void SetIsPreviewingLoopRegion(double InStartTime, double InEndTime, bool bIsPreviewing);`
- L156 _private prototype_ `void SelectLoopRegionByKeyboard(const FKey& PressedKey);`
- L158 _private member_ `int32 SelectedIncrement = 2;`
- L160 _private member_ `float SampleRate = 0.f;`
- L161 _private member_ `float AvailableWaveformDuration = -1.f;`
- L162 _private member_ `int32 NumChannels = 0;`
- L163 _private member_ `int64 NumAvailableSamples = 0;`
- L167 _private member_ `int64 StartFrameOffset = 0;` — `UPROPERTY()` — Made a UPROPERTY so that it is captured when the soundwave is duplicated during export
- L169 _private member_ `bool bCachedIsPreviewingLoopRegion = false;`
- L170 _private member_ `bool bCachedSoundWaveLoopState = false;`
- L172 _private member_ `bool bHasLoggedCutByLoop = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONS_API`
- L57 _delegate_ `DECLARE_DELEGATE_OneParam(ModifyMarkerLoopRegionDelegate, ELoopModificationControls);`
- L62 _delegate_ `DECLARE_DELEGATE_OneParam(CycleMarkerLoopRegionDelegate, ELoopModificationControls);`
- L71 _delegate_ `DECLARE_DELEGATE(OnCueChange);`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Public/WaveformTransformationNormalize.h` (Public)


#### enum `ENormalizationMode`  
`enum class ENormalizationMode : uint8`  
_L12-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `Peak`
- L15 _public enumerator_ `RMS`
- L16 _public enumerator_ `DWeightedLoudness`
- L17 _public enumerator_ `COUNT UMETA(Hidden)`

#### class `FWaveTransformationNormalize`  
`class FWaveTransformationNormalize : public Audio::IWaveTransformation`  
_L20-31_
- inherits: `Audio::IWaveTransformation`
- L23 _public prototype_ `FWaveTransformationNormalize(float InTarget, float InMaxGain, ENormalizationMode InMode);`
- L25 _public prototype_ `virtual void ProcessAudio(Audio::FWaveformTransformationWaveInfo& InOutWaveInfo) const override;`
- L28 _private member_ `float Target = 0.f;`
- L29 _private member_ `float MaxGain = 0.f;`
- L30 _private member_ `ENormalizationMode Mode = ENormalizationMode::Peak;`

#### class `UWaveformTransformationNormalize`  
`class UWaveformTransformationNormalize final : public UWaveformTransformationBase`  
_L34-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWaveformTransformationBase`
- L40 _private member_ `float Target = 0.f;` — `UPROPERTY(EditAnywhere, Category="Normalization", meta=(ClampMax = 0.0))` — Target maximum volume for this soundwave, in decibels
- L44 _private member_ `float MaxGain = 0.f;` — `UPROPERTY(EditAnywhere, Category="Normalization", meta=(ClampMin = 0.0))` — Will not apply more gain than this, even if the sound is very quiet
- L48 _private member_ `ENormalizationMode Mode;` — `UPROPERTY(EditAnywhere, Category="Normalization")` — what type of analysis to run to find the peak value
- L51 _public prototype_ `virtual Audio::FTransformationPtr CreateTransformation() const override;`
- L52 _public function_ `virtual constexpr Audio::ETransformationPriority GetTransformationPriority() const`
- L55 _public prototype_ `virtual FString GetTransformationHash() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONS_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Public/WaveformTransformationTrimFade.h` (Public)


#### class `UFadeFunction`  
`class UE_DEPRECATED(5.8, "UFadeFunction has been deprecated. Use UTransformationFadeFunction.") UFadeFunction : public UObject`  
_L14-24_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories, NotBlueprintable)`
- inherits: `UObject`
- L19 _public function_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const`
- L20 _public function_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const`
- L23 _public member_ `float Duration = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Fade", BlueprintReadWrite, meta = (ClampMin = 0.0, DisplayName = "Fade Duration"))`

#### class `UFadeCurveFunction`  
`class UE_DEPRECATED(5.8, "UFadeFunction has been deprecated. Use UTransformationFadeFunction.") UFadeCurveFunction : public UFadeFunction`  
_L28-43_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories, NotBlueprintable)`
- inherits: `UFadeFunction`
- L33 _public function_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override`
- L34 _public function_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override`
- L36 _public function_ `virtual void SetFadeCurve(const float InFadeCurve)`
- L37 _public function_ `virtual const float GetFadeCurve() const`
- L38 _public function_ `virtual const FText GetFadeCurvePropertyName() const`
- L41 _protected function_ `virtual const float GetFadeCurveMin() const`
- L42 _protected function_ `virtual const float GetFadeCurveMax() const`

#### class `UFadeFunctionLinear`  
`class UE_DEPRECATED(5.8, "UFadeFunction has been deprecated. Use UTransformationFadeFunction.") UFadeFunctionLinear : public UFadeFunction`  
_L46-53_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Linear"))`
- inherits: `UFadeFunction`
- L51 _public prototype_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override;`
- L52 _public prototype_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override;`

#### class `UFadeCurveFunctionExponential`  
`class UE_DEPRECATED(5.8, "UFadeFunction has been deprecated. Use UTransformationFadeFunction.") UFadeCurveFunctionExponential : public UFadeCurveFunction`  
_L56-74_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Exponential"))`
- inherits: `UFadeCurveFunction`
- L61 _public prototype_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override;`
- L62 _public prototype_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override;`
- L64 _public function_ `virtual void SetFadeCurve(const float InFadeCurve) override`
- L65 _public function_ `virtual const float GetFadeCurve() const override`
- L66 _public function_ `virtual const FText GetFadeCurvePropertyName() const override`
- L69 _public member_ `float FadeCurve = 3.f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 1, ClampMax = 10.0, DisplayName = "Fade Curve"))`
- L72 _protected function_ `virtual const float GetFadeCurveMin() const override`
- L73 _protected function_ `virtual const float GetFadeCurveMax() const override`

#### class `UFadeCurveFunctionLogarithmic`  
`class UE_DEPRECATED(5.8, "UFadeFunction has been deprecated. Use UTransformationFadeFunction.") UFadeCurveFunctionLogarithmic : public UFadeCurveFunction`  
_L77-91_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Logarithmic"))`
- inherits: `UFadeCurveFunction`
- L82 _public prototype_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override;`
- L83 _public prototype_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override;`
- L85 _public function_ `virtual void SetFadeCurve(const float InFadeCurve) override`
- L86 _public function_ `virtual const float GetFadeCurve() const override`
- L87 _public function_ `virtual const FText GetFadeCurvePropertyName() const override`
- L90 _public member_ `float FadeCurve = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 0.0, ClampMax = 1, DisplayName = "Fade Curve"))`

#### class `UFadeCurveFunctionSigmoid`  
`class UE_DEPRECATED(5.8, "UFadeFunction has been deprecated. Use UTransformationFadeFunction.") UFadeCurveFunctionSigmoid : public UFadeCurveFunction`  
_L94-108_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, meta = (DisplayName = "Sigmoid"))`
- inherits: `UFadeCurveFunction`
- L99 _public prototype_ `virtual const double GetFadeInCurveValue(const double FadeFraction) const override;`
- L100 _public prototype_ `virtual const double GetFadeOutCurveValue(const double FadeFraction) const override;`
- L102 _public function_ `virtual void SetFadeCurve(const float InFadeCurve) override`
- L103 _public function_ `virtual const float GetFadeCurve() const override`
- L104 _public function_ `virtual const FText GetFadeCurvePropertyName() const override`
- L107 _public member_ `float SFadeCurve = 0.6f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 0.0, ClampMax = 1, DisplayName = "S-Fade Curve"))`

#### struct `FFadeFunctionData`  
`struct UE_DEPRECATED(5.8, "UFadeFunction has been deprecated. Use UTransformationFadeFunction.") FFadeFunctionData`  
_L111-122_
- reflection: `USTRUCT()`
- L116 _public member_ `TObjectPtr<UFadeFunction> FadeIn;` — `UPROPERTY(EditAnywhere, Category = "Fade", Instanced)`
- L119 _public member_ `TObjectPtr<UFadeFunction> FadeOut;` — `UPROPERTY(EditAnywhere, Category = "Fade", Instanced)`
- L121 _public prototype_ `void MigrateToTransformationFadeFunction(const TObjectPtr<UWaveformTransformationFade> InFadeTransformation, FTransformationFadeFunctionData& NewFadeRegion);`

#### class `FWaveTransformationTrimFade`  
`class FWaveTransformationTrimFade : public Audio::IWaveTransformation`  
_L125-139_
- inherits: `Audio::IWaveTransformation`
- L128 _public prototype_ `explicit FWaveTransformationTrimFade(TObjectPtr<UWaveformTransformationFade> InFadeTransformation, double InStartTime, double InEndTime);`
- L129 _public prototype_ `virtual void ProcessAudio(Audio::FWaveformTransformationWaveInfo& InOutWaveInfo) const override;`
- L131 _public function_ `virtual constexpr Audio::ETransformationPriority FileChangeLengthPriority() const override`
- L135 _private member_ `TObjectPtr<UWaveformTransformationFade> FadeTransformation;`
- L137 _private member_ `double StartTime = 0.0;`
- L138 _private member_ `double EndTime = 0.0;`

#### class `UWaveformTransformationTrimFade`  
`class UWaveformTransformationTrimFade final : public UWaveformTransformationBase`  
_L142-228_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWaveformTransformationBase`
- L147 _public prototype_ `UWaveformTransformationTrimFade(const FObjectInitializer& ObjectInitializer);`
- L150 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L152 _public prototype_ `virtual FString GetTransformationHash() const override;`
- L155 _public prototype_ `virtual void PostLoad() override;`
- L158 _public member_ `double StartTime = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Trim", meta=(ClampMin = 0.0))`
- L161 _public member_ `double EndTime = -1.0;` — `UPROPERTY(EditAnywhere, Category = "Trim")`
- L164 _public member_ `TObjectPtr<UWaveformTransformationFade> FadeTransformation = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Fade", meta = (DisplayName = "Fade Functions"))`
- L169 _public member_ `FFadeFunctionData FadeFunctions;` — `UE_DEPRECATED(5.8, "UFadeFunction has been deprecated. Use UTransformationFadeFunction.")` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (DisplayName = "Fade Functions", EditCondition = "false", EditConditionHides))`
- L178 _public member_ `float StartFadeTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 0.0, DisplayName = "Fade-In Duration", EditCondition = "StartFadeTime != 0", EditConditionHides))` — Relative to StartTime Individual fade properties have been deprecated. Use UTransformationFadeFunction instead.
- L185 _public member_ `float StartFadeCurve = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta=(ClampMin = -0.1, ClampMax = 10.0, DisplayName = "Fade-In Curve", EditCondition = "StartFadeTime != 0", EditConditionHides))` — Individual fade properties have been deprecated. Use UTransformationFadeFunction instead.
- L192 _public member_ `float StartSCurveSharpness = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 0, ClampMax = 1.0, DisplayName = "S-Curve Sharpness", EditCondition = "StartFadeTime != 0 && StartFadeCurve < 0", EditConditionHides))` — Individual fade properties have been deprecated. Use UTransformationFadeFunction instead.
- L200 _public member_ `float EndFadeTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 0.0, DisplayName = "Fade-Out Duration", EditCondition = "EndFadeTime != 0", EditConditionHides))` — Relative to EndTime. Fade out starts at EndTime - EndFadeTime and ends at EndTime Individual fade properties have been deprecated. Use UTransformationFadeFunction instead.
- L207 _public member_ `float EndFadeCurve = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta=(ClampMin = -0.1, ClampMax = 10.0, DisplayName = "Fade-Out Curve", EditCondition = "EndFadeTime != 0", EditConditionHides))` — Individual fade properties have been deprecated. Use UTransformationFadeFunction instead.
- L214 _public member_ `float EndSCurveSharpness = 0.75;` — `UPROPERTY(EditAnywhere, Category = "Fade", meta = (ClampMin = 0, ClampMax = 1.0, DisplayName = "S-Curve Sharpness", EditCondition = "EndFadeTime != 0 && EndFadeCurve < 0", EditConditionHides))` — Individual fade properties have been deprecated. Use UTransformationFadeFunction instead.
- L216 _public prototype_ `virtual Audio::FTransformationPtr CreateTransformation() const override;`
- L218 _public prototype_ `void UpdateConfiguration(FWaveTransformUObjectConfiguration& InOutConfiguration) override;`
- L219 _public function_ `virtual constexpr Audio::ETransformationPriority GetTransformationPriority() const`
- L221 _public prototype_ `const FTransformationFadeFunctionData& GetFadeRegion() const;`
- L222 _public prototype_ `FTransformationFadeFunctionData& GetMutableFadeRegion() const;`
- L226 _private prototype_ `void UpdateDurationProperties(const float InAvailableDuration);`
- L227 _private member_ `float AvailableWaveformDuration = -1.f;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WAVEFORMTRANSFORMATIONS_API`

### `Plugins/Editor/WaveformEditor/Source/WaveformTransformations/Public/WaveformTransformationsModule.h` (Public)


#### class `FWaveformTransformationsModule`  
`class FWaveformTransformationsModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule() override;`
- L11 _public prototype_ `virtual void ShutdownModule() override;`
