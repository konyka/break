# Plugins / AudioSynesthesia

- module root: `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia`
- headers: 13; symbols: 352
- symbol kinds: class=22, delegate=29, enum=5, enumerator=29, function=5, macro=10, member=113, namespace=1, prototype=134, struct=4
- PublicDependencyModuleNames: AudioAnalyzer, AudioMixer, AudioMixerCore, AudioSynesthesiaCore, Core, CoreUObject, Engine, SignalProcessing

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/AudioSynesthesia.h` (Public)


#### class `UAudioSynesthesiaSettings`  
`class UAudioSynesthesiaSettings : public UAudioAnalyzerSettings`  
_L12-22_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UAudioAnalyzerSettings`
- desc: UAudioSynesthesiaSettings Defines asset actions for derived UAudioSynthesiaSettings subclasses.
- L19 _public prototype_ `const TArray<FText>& GetAssetActionSubmenus() const;`
- L20 _public prototype_ `FColor GetTypeColor() const override;`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/AudioSynesthesiaNRT.h` (Public)


#### class `UAudioSynesthesiaNRTSettings`  
`class UAudioSynesthesiaNRTSettings : public UAudioAnalyzerNRTSettings`  
_L12-23_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalApi)`
- inherits: `UAudioAnalyzerNRTSettings`
- desc: UAudioSynesthesiaNRTSettings Defines asset actions for derived UAudioSynthesiaNRTSettings subclasses.
- L18 _public prototype_ `const TArray<FText>& GetAssetActionSubmenus() const;`
- L21 _public prototype_ `FColor GetTypeColor() const override;`

#### class `UAudioSynesthesiaNRT`  
`class UAudioSynesthesiaNRT : public UAudioAnalyzerNRT`  
_L30-41_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalApi)`
- inherits: `UAudioAnalyzerNRT`
- desc: UAudioSynesthesiaNRT Defines asset actions for derived UAudioSynthesiaNRT subclasses.
- L36 _public prototype_ `const TArray<FText>& GetAssetActionSubmenus() const;`
- L39 _public prototype_ `FColor GetTypeColor() const override;`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/ConstantQ.h` (Public)


#### class `UConstantQSettings`  
`class UConstantQSettings : public UAudioSynesthesiaSettings`  
_L17-76_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaSettings`
- desc: UConstantQSettings Settings for a UConstantQ analyzer.
- L22 _public function_ `UConstantQSettings()`
- L26 _public member_ `float StartingFrequencyHz = 40.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, DisplayName = "Starting Frequency (Hz)", meta = (ClampMin = "20.0", ClampMax = "20000"))` — Starting frequency for first bin of CQT
- L30 _public member_ `int32 NumBands = 48;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "1", ClampMax = "96"))` — Total number of resulting constant Q bands.
- L34 _public member_ `float NumBandsPerOctave = 12.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "1", ClampMax = "24"))` — Number of bands within an octave.
- L38 _public member_ `float AnalysisPeriodInSeconds = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, DisplayName = "Analysis Period (s)", meta = (ClampMin = "0.01", ClampMax = "1.0"))` — Number of seconds between cqt measurements
- L42 _public member_ `bool bDownmixToMono = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer)` — If true, multichannel audio is downmixed to mono with equal amplitude scaling. If false, each channel gets it's own CQT result.
- L46 _public member_ `EConstantQFFTSizeEnum FFTSize = EConstantQFFTSizeEnum::XLarge;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer)` — Size of FFT.
- L50 _public member_ `EFFTWindowType WindowType = EFFTWindowType::Blackman;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer)` — Type of window to be applied to input audio
- L54 _public member_ `EAudioSpectrumType SpectrumType = EAudioSpectrumType::PowerSpectrum;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer)` — Type of spectrum to use.
- L58 _public member_ `float BandWidthStretch = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "2.0"))` — Stretching factor to control overlap of adjacent bands.
- L62 _public member_ `EConstantQNormalizationEnum CQTNormalization = EConstantQNormalizationEnum::EqualEnergy;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer)` — Normalization scheme used to generate band windows.
- L66 _public member_ `float NoiseFloorDb = -60.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer, meta = (DisplayName = "Noise Floor (dB)", ClampMin = "-120.0", ClampMax = "0.0"))` — Noise floor to use when normalizing CQT
- L69 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const;` — Convert UConstantQSettings to FConstantQSettings
- L72 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L74 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### struct `FConstantQResults`  
`struct FConstantQResults`  
_L80-91_
- reflection: `USTRUCT(BlueprintType)`
- desc: The results of the ConstantQ analysis.
- L86 _public member_ `float TimeSeconds = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The time in seconds since analysis began of this ConstantQ analysis result
- L90 _public member_ `TArray<float> SpectrumValues;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The spectrum values from the FFT

#### class `UConstantQAnalyzer`  
`class UConstantQAnalyzer : public UAudioAnalyzer`  
_L111-149_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioAnalyzer`
- desc: UConstantQAnalyzer UConstantQAnalyzer calculates the temporal evolution of constant q transform for a given audio bus in real-time. ConstantQ is available for individual channels or the overall audio bus.
- L115 _public prototype_ `UConstantQAnalyzer();`
- L119 _public member_ `TObjectPtr<UConstantQSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioAnalyzer)` — The settings for the audio analyzer.
- L123 _public member_ `FOnConstantQResults OnConstantQResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive all Spectrum results, per-channel, since last delegate call. If bDownmixToMono setting is true, results will be in channel index 0.
- L125 _public member_ `FOnConstantQResultsNative OnConstantQResultsNative;`
- L129 _public member_ `FOnLatestConstantQResults OnLatestConstantQResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive the latest per-channel Spectrum results. If bDownmixToMono setting is true, results will be in channel index 0.
- L131 _public member_ `FOnLatestConstantQResultsNative OnLatestConstantQResultsNative;`
- L134 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const override;` — Convert UConstantQSettings to FConstantQSettings
- L137 _public prototype_ `void BroadcastResults() override;` — Broadcasts results to any delegates if hooked up.
- L140 _public prototype_ `void GetCenterFrequencies(UPARAM(DisplayName = "Center Frequencies") TArray<float>& OutC` — `UFUNCTION(BlueprintCallable, Category = "Audio Analyzer")`
- L143 _public prototype_ `UPARAM(DisplayName = "Num Center Frequencies") const int32 GetNumCent` — `UFUNCTION(BlueprintCallable, Category = "Audio Analyzer")`
- L148 _protected prototype_ `FName GetAnalyzerFactoryName() const override;` — Return the name of the IAudioAnalyzerFactory associated with this UAudioAnalyzer

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`
- L94 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConstantQResults, int32, ChannelIndex, const TArray<FConstantQResults>&, ConstantQResults);` — Delegate to receive all ConstantQ results per channel (time-stamped in an array) since last delegate call. If bDownmixToMono setting is true, results will be in channel index 0.
- L94 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConstantQResults, int32, ChannelIndex, const TArray<FConstantQResults>&, ConstantQResults);` — Delegate to receive all ConstantQ results per channel (time-stamped in an array) since last delegate call. If bDownmixToMono setting is true, results will be in channel index 0.
- L97 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConstantQResultsNative, UConstantQAnalyzer*, int32, const TArray<FConstantQResults>&);` — shadow delegate declaration for above
- L97 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConstantQResultsNative, UConstantQAnalyzer*, int32, const TArray<FConstantQResults>&);` — shadow delegate declaration for above
- L100 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestConstantQResults, int32, ChannelIndex, const FConstantQResults&, LatestConstantQResults);` — Delegate to receive only the most recent overall ConstantQ result per channel. If bDownmixToMono setting is true, results will be in channel index 0.
- L100 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestConstantQResults, int32, ChannelIndex, const FConstantQResults&, LatestConstantQResults);` — Delegate to receive only the most recent overall ConstantQ result per channel. If bDownmixToMono setting is true, results will be in channel index 0.
- L103 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLatestConstantQResultsNative, UConstantQAnalyzer*, int32, const FConstantQResults&);` — shadow delegate declaration for above
- L103 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLatestConstantQResultsNative, UConstantQAnalyzer*, int32, const FConstantQResults&);` — shadow delegate declaration for above

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/ConstantQNRT.h` (Public)


#### enum `EConstantQNormalizationEnum`  
`enum class EConstantQNormalizationEnum : uint8`  
_L18-28_
- reflection: `UENUM(BlueprintType)`
- desc: EConstantQNormalizationEnum Enumeration of available normalization schemes for ConstantQ frequency domain windows.
- L21 _public enumerator_ `EqualEuclideanNorm UMETA(DisplayName="Equal Euclidean Norm")` — Normalize bands by euclidean norm. Good when using magnitude spectrum.
- L24 _public enumerator_ `EqualEnergy UMETA(DisplayName="Equal Energy")` — Normalize bands by energy. Good when using power spectrum.
- L27 _public enumerator_ `EqualAmplitude UMETA(DisplayName="Equal Amplitude")` — Normalize bands by their maximum values. Will result in relatively strong high frequences because the upper constant Q bands have larger bandwidths.

#### enum `EConstantQFFTSizeEnum`  
`enum class EConstantQFFTSizeEnum : uint8`  
_L35-63_
- reflection: `UENUM(BlueprintType)`
- desc: EContantQFFTSizeEnum Enumeration of available FFT sizes in audio frames.
- L38 _public enumerator_ `Min UMETA(DisplayName = "64")` — 64
- L41 _public enumerator_ `XXSmall UMETA(DisplayName = "128")` — 128
- L44 _public enumerator_ `XSmall UMETA(DisplayName = "256")` — 256
- L47 _public enumerator_ `Small UMETA(DisplayName = "512")` — 512
- L50 _public enumerator_ `Medium UMETA(DisplayName = "1024")` — 1024
- L53 _public enumerator_ `Large UMETA(DisplayName = "2048")` — 2048
- L56 _public enumerator_ `XLarge UMETA(DisplayName = "4096")` — 4096
- L59 _public enumerator_ `XXLarge UMETA(DisplayName = "8192")` — 8192
- L62 _public enumerator_ `Max UMETA(DisplayName = "16384")` — 16384

#### class `UConstantQNRTSettings`  
`class UConstantQNRTSettings : public UAudioSynesthesiaNRTSettings`  
_L70-128_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaNRTSettings`
- desc: UConstantQNRTSettings Settings for a UConstantQNRT analyzer.
- L75 _public prototype_ `UConstantQNRTSettings();`
- L79 _public member_ `float StartingFrequency;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "20.0", ClampMax = "20000"))` — Starting frequency for first bin of CQT
- L83 _public member_ `int32 NumBands;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "1", ClampMax = "96"))` — Total number of resulting constant Q bands.
- L87 _public member_ `float NumBandsPerOctave;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "1", ClampMax = "24"))` — Number of bands within an octave.
- L90 _public member_ `float AnalysisPeriod;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "1.0"))` — Number of seconds between cqt measurements
- L94 _public member_ `bool bDownmixToMono;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer)` — If true, multichannel audio is downmixed to mono with equal amplitude scaling. If false, each channel gets it's own CQT result.
- L98 _public member_ `EConstantQFFTSizeEnum FFTSize;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer)` — Size of FFT.
- L102 _public member_ `EFFTWindowType WindowType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer)` — Type of window to be applied to input audio
- L106 _public member_ `EAudioSpectrumType SpectrumType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer)` — Type of spectrum to use.
- L110 _public member_ `float BandWidthStretch;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "2.0"))` — Stretching factor to control overlap of adjacent bands.
- L114 _public member_ `EConstantQNormalizationEnum CQTNormalization;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer)` — Normalization scheme used to generate band windows.
- L118 _public member_ `float NoiseFloorDb;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = AudioAnalyzer, meta = (DisplayName = "Noise Floor (dB)", ClampMin = "-120.0", ClampMax = "0.0"))` — Noise floor to use when normalizing CQT
- L121 _public prototype_ `TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const;` — Convert UConstantQNRTSettings to FConstantQNRTSettings
- L124 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L126 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### class `UConstantQNRT`  
`class UConstantQNRT : public UAudioSynesthesiaNRT`  
_L137-173_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaNRT`
- desc: UConstantQNRT UConstantQNRT calculates the temporal evolution of constant q transform for a given sound. ConstantQ is available for individual channels or the overall sound asset.
- L143 _public prototype_ `UConstantQNRT();`
- L147 _public member_ `TObjectPtr<UConstantQNRTSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer)` — The settings for the audio analyzer.
- L151 _public prototype_ `void GetChannelConstantQAtTime(const float InSeconds, const int32 InChannel, TArray<float>& OutConstantQ) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get a specific channel cqt of the analyzed sound at a given time.
- L155 _public prototype_ `void GetNormalizedChannelConstantQAtTime(const float InSeconds, const int32 InChannel, TArray<float>& OutConstantQ) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get a specific channel cqt of the analyzed sound at a given time.
- L158 _public prototype_ `virtual TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const override;` — Convert ULoudnessNRTSettings to FLoudnessNRTSettings
- L161 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L163 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L165 _public prototype_ `virtual bool ShouldEventTriggerAnalysis(FPropertyChangedEvent& PropertyChangeEvent) override;`
- L171 _protected prototype_ `virtual FName GetAnalyzerNRTFactoryName() const override;` — Return the name of the IAudioAnalyzerNRTFactory associated with this UAudioAnalyzerNRT

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/LKFS.h` (Public)


#### class `ULKFSSettings`  
`class ULKFSSettings : public UAudioSynesthesiaSettings`  
_L17-62_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaSettings`
- desc: ULKFSSettings Settings for a ULKFSAnalyzer.
- L22 _public function_ `ULKFSSettings()`
- L26 _public member_ `float AnalysisPeriod = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "1.00"))` — Number of seconds between loudness measurements. The standard is 0.1 seconds.
- L30 _public member_ `float AnalysisWindowDuration = 0.4f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "0.10", ClampMax = "1.00"))` — Number of seconds of audio analyzed for each loudness measurements. The standard is 0.4 seconds.
- L34 _public member_ `float ShortTermLoudnessDuration = Audio::FLKFSSettings::StandardShortTermLoudnessDuration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "1.00", ClampMax = "30.00"))` — Duration of audio analyzed for short term loudness. The standard is 3.0 seconds.
- L38 _public member_ `float IntegratedLoudnessAnalysisPeriod = Audio::FLKFSSettings::StandardIntegratedLoudnessAnalysisPeriod;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "0.1", ClampMax = "10.00"))` — Number of seconds between long term (integrated and gated) loudness updates.  The standard is 1.0 seconds.
- L44 _public member_ `float IntegratedLoudnessDuration = Audio::FLKFSSettings::DefaultIntegratedLoudnessDuration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "10.00", ClampMax = "3600.00"))` — Duration of audio analyzed for long term (integrated and gated) loudness. The real time LKFS analyzer performs integrated loudness duration over a large window instead of performing calculations over the entire audio stream.
- L48 _public member_ `bool bCalculatePerChannelLoudnessRange = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Should the Loudness Range (LRA) statistic be calculated for each channel?
- L52 _public member_ `bool bCalculateOverallLoudnessRange = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Should the overall Loudness Range (LRA) statistic be calculated?
- L55 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const;` — Convert ULKFSSettings to IAnalyzerSettings
- L58 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L60 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### class `ULKFSAnalyzer`  
`class ULKFSAnalyzer : public UAudioAnalyzer`  
_L94-140_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioAnalyzer`
- desc: ULKFSAnalyzer ULKFSAnalyzer calculates the current amplitude of an audio bus in real-time.
- L100 _public prototype_ `ULKFSAnalyzer();`
- L104 _public member_ `TObjectPtr<ULKFSSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioAnalyzer)` — The settings for the meter audio analyzer.
- L108 _public member_ `FOnOverallLKFSResults OnOverallLKFSResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive all overall meter results since last delegate call.
- L110 _public member_ `FOnOverallLKFSResultsNative OnOverallLKFSResultsNative;`
- L114 _public member_ `FOnPerChannelLKFSResults OnPerChannelLKFSResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive all meter results, per-channel, since last delegate call.
- L116 _public member_ `FOnPerChannelLKFSResultsNative OnPerChannelLKFSResultsNative;`
- L120 _public member_ `FOnLatestOverallLKFSResults OnLatestOverallLKFSResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive the latest overall meter results.
- L122 _public member_ `FOnLatestOverallLKFSResultsNative OnLatestOverallLKFSResultsNative;`
- L126 _public member_ `FOnLatestPerChannelLKFSResults OnLatestPerChannelLKFSResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive the latest per-channel meter results.
- L128 _public member_ `FOnLatestPerChannelLKFSResultsNative OnLatestPerChannelLKFSResultsNative;`
- L131 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const override;` — Convert ULKFSSettings to IAnalyzerSettings
- L134 _public prototype_ `void BroadcastResults() override;` — Broadcasts results to any delegates if hooked up.
- L139 _protected prototype_ `FName GetAnalyzerFactoryName() const override;` — Return the name of the IAudioAnalyzerFactory associated with this UAudioAnalyzer

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`
- L65 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverallLKFSResults, const TArray<FLKFSResults>&, LKFSResults);` — Delegate to receive all overall loudness results (time-stamped in an array) since last delegate call.
- L65 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverallLKFSResults, const TArray<FLKFSResults>&, LKFSResults);` — Delegate to receive all overall loudness results (time-stamped in an array) since last delegate call.
- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallLKFSResultsNative, ULKFSAnalyzer*, TArrayView<const FLKFSResults>);` — shadow delegate declaration for above
- L68 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallLKFSResultsNative, ULKFSAnalyzer*, TArrayView<const FLKFSResults>);` — shadow delegate declaration for above
- L71 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLatestOverallLKFSResults, const FLKFSResults&, LatestOverallLKFSResults);` — Delegate to receive only the most recent overall meter results.
- L71 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLatestOverallLKFSResults, const FLKFSResults&, LatestOverallLKFSResults);` — Delegate to receive only the most recent overall meter results.
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLatestOverallLKFSResultsNative, ULKFSAnalyzer*, const FLKFSResults&);` — shadow delegate declaration for above
- L74 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLatestOverallLKFSResultsNative, ULKFSAnalyzer*, const FLKFSResults&);` — shadow delegate declaration for above
- L77 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerChannelLKFSResults, int32, ChannelIndex, const TArray<FLKFSResults>&, LKFSResults);` — Delegate to receive all meter results per channel (time-stamped in an array) since last delegate call.
- L77 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerChannelLKFSResults, int32, ChannelIndex, const TArray<FLKFSResults>&, LKFSResults);` — Delegate to receive all meter results per channel (time-stamped in an array) since last delegate call.
- L80 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPerChannelLKFSResultsNative, ULKFSAnalyzer*, int32, TArrayView<const FLKFSResults>);` — shadow delegate declaration for above
- L80 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPerChannelLKFSResultsNative, ULKFSAnalyzer*, int32, TArrayView<const FLKFSResults>);` — shadow delegate declaration for above
- L83 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestPerChannelLKFSResults, int32, ChannelIndex, const FLKFSResults&, LatestLKFSResults);` — Delegate to receive only the most recent overall meter result per channel.
- L83 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestPerChannelLKFSResults, int32, ChannelIndex, const FLKFSResults&, LatestLKFSResults);` — Delegate to receive only the most recent overall meter result per channel.
- L86 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLatestPerChannelLKFSResultsNative, ULKFSAnalyzer*, int32, const FLKFSResults&);` — shadow delegate declaration for above
- L86 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLatestPerChannelLKFSResultsNative, ULKFSAnalyzer*, int32, const FLKFSResults&);` — shadow delegate declaration for above

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/LKFSNRT.h` (Public)


#### class `ULKFSNRTSettings`  
`class ULKFSNRTSettings : public UAudioSynesthesiaNRTSettings`  
_L17-44_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaNRTSettings`
- desc: ULKFSNRTSettings Settings for a ULKFSNRT analyzer.
- L22 _public prototype_ `ULKFSNRTSettings();`
- L26 _public member_ `float AnalysisPeriod = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "1.00"))` — Number of seconds between loudness measurements
- L30 _public member_ `float AnalysisWindowDuration = 0.4f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "0.10", ClampMax = "1.00"))` — Number of seconds of audio analyzed for a single window of measurement
- L34 _public member_ `float ShortTermLoudnessDuration = Audio::FLKFSNRTSettings::DefaultShortTermLoudnessDuration;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "1.00", ClampMax = "30.00"))` — Number of seconds of audio analyzed when determining short term loudness.
- L37 _public prototype_ `virtual TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const;` — Convert ULKFSNRTSettings to FLKFSNRTSettings
- L40 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L42 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### class `ULKFSNRT`  
`class ULKFSNRT : public UAudioSynesthesiaNRT`  
_L54-122_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaNRT`
- desc: ULKFSNRT ULKFSNRT calculates the temporal evolution of perceptual loudness for a given sound.
- L60 _public prototype_ `ULKFSNRT();`
- L64 _public member_ `TObjectPtr<ULKFSNRTSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ExposeOnSpawn))` — The settings for the audio analyzer.
- L68 _public prototype_ `void GetLoudnessAtTime(const float InSeconds, float& OutLoudness) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get the overall loudness of the analyzed sound at a given time.
- L72 _public prototype_ `void GetChannelLoudnessAtTime(const float InSeconds, const int32 InChannel, float& OutLoudness) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get a specific channel loudness of the analyzed sound at a given time.
- L76 _public prototype_ `TArray<FLKFSNRTResults> GetLoudnessDataForChannel(int32 InChannel) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Return the entire array of loudness data for a specific audio channel.
- L80 _public prototype_ `TArray<FLKFSNRTResults> GetLoudnessData() const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Return the entire array of loudness data for the combination of all audio channels.
- L84 _public prototype_ `FLKFSNRTResults GetLoudnessDataForChannelAtTime(const float InSeconds, int32 InChannel) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Return the instantaneous loudness data for a specific time and audio channel.
- L88 _public prototype_ `FLKFSNRTResults GetLoudnessDataAtTime(const float InSeconds) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Return the instantaneous loudness data for the combination of all audio channels at a specific time.
- L92 _public prototype_ `float GetIntegratedLoudnessForChannel(int32 InChannel) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Return the integrated (average) loudness for a specific audio channel.
- L96 _public prototype_ `float GetIntegratedLoudness() const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Return the integrated (average) loudness for the combination of all audio channels.
- L100 _public prototype_ `float GetGatedLoudnessForChannel(int32 InChannel) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Return the gated loudness for a specific audio channel.
- L104 _public prototype_ `float GetGatedLoudness() const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Return the gated loudness for the combination of all audio channels.
- L107 _public prototype_ `TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const override;` — Convert ULKFSNRTSettings to FLKFSNRTSettings
- L110 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L112 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L114 _public prototype_ `virtual bool ShouldEventTriggerAnalysis(FPropertyChangedEvent& PropertyChangeEvent) override;`
- L120 _protected prototype_ `FName GetAnalyzerNRTFactoryName() const override;` — Return the name of the IAudioAnalyzerNRTFactory associated with this UAudioAnalyzerNRT

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/Loudness.h` (Public)


#### enum `ELoudnessCurveTypeEnum`  
`enum class ELoudnessCurveTypeEnum : uint8`  
_L15-29_
- reflection: `UENUM(BlueprintType)`
- desc: ELoudnessCurveTypeEnum Enumeration of available equal loudness curves. Loudness curves based on IEC 61672-1:2013 Electroacoustics - Sound level meters - Part 1: Specifications.
- L18 _public enumerator_ `A UMETA(DisplayName = "A")` — Loudness Curve A Weighting. Commonly used in environmental sound measurements. Best for low level sounds.
- L20 _public enumerator_ `B UMETA(DisplayName = "B")` — Loudness Curve B Weighting. Relative to "A", gives more precedence to frequencies below 1kHz.
- L22 _public enumerator_ `C UMETA(DisplayName = "C")` — Loudness Curve C Weighting. Relative to "A" and "B", gives more precedence to frequencies below 1kHz.
- L24 _public enumerator_ `D UMETA(DisplayName = "D")` — Loudness Curve D Weighting. Similar to "B" but with an emphasis on presence in the 2kHz-6KHz frequency range.
- L26 _public enumerator_ `K UMETA(DisplayName = "K")` — Loudness Curve K Weighting. Correlates with subjective perception of recorded broadcast content.
- L28 _public enumerator_ `None UMETA(DisplayName = "None")` — No loudness curve weighting.

#### class `ULoudnessSettings`  
`class ULoudnessSettings : public UAudioSynesthesiaSettings`  
_L37-76_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaSettings`
- desc: ULoudnessSettings Settings for a ULoudness analyzer.
- L42 _public function_ `ULoudnessSettings()`
- L46 _public member_ `float AnalysisPeriod = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "0.25"))` — Number of seconds between loudness measurements
- L50 _public member_ `float MinimumFrequency = 20.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "20.0", ClampMax = "20000"))` — Minimum analysis frequency for calculating loudness.
- L54 _public member_ `float MaximumFrequency = 20000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "20.0", ClampMax = "20000"))` — Maximum analysis frequency for calculating loudness.
- L58 _public member_ `ELoudnessCurveTypeEnum CurveType = ELoudnessCurveTypeEnum::D;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Type of equal loudness curve used in calculations
- L62 _public member_ `float NoiseFloorDb = -60.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = AudioAnalyzer, meta = (ClampMin = "-100.0", ClampMax = "0"))` — dB level to denote silence.  Used when calculating normalized loudness.
- L66 _public member_ `float ExpectedMaxLoudness = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = AudioAnalyzer, meta = (ClampMin = "-100.0", ClampMax = "0"))` — dB level to denote silence.  Used when calculating normalized loudness.
- L69 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const;` — Convert ULoudnessSettings to FLoudnessSettings
- L72 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L74 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### struct `FLoudnessResults`  
`struct FLoudnessResults`  
_L80-99_
- reflection: `USTRUCT(BlueprintType)`
- desc: The results of the loudness analyis.
- L86 _public member_ `float Loudness = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The raw loudness value in dB
- L90 _public member_ `float NormalizedLoudness = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The normalized loudness
- L94 _public member_ `float PerceptualEnergy = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The normalized loudness
- L98 _public member_ `float TimeSeconds = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The time in seconds since analysis began

#### class `ULoudnessAnalyzer`  
`class ULoudnessAnalyzer : public UAudioAnalyzer`  
_L121-159_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioAnalyzer`
- desc: ULoudnessAnalyzer ULoudnessAnalyzer calculates the temporal evolution of perceptual loudness for a given audio bus in real-time. Loudness is available for individual channels or the overall audio bus. Normalized loudness values convert the range to 0.0 to 1.0 where 0.0 is the noise floor and 1.0 is the maximum loudness of the particular sound.
- L127 _public prototype_ `ULoudnessAnalyzer();`
- L131 _public member_ `TObjectPtr<ULoudnessSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioAnalyzer, meta = (ExposeOnSpawn))` — The settings for the audio analyzer.
- L135 _public member_ `FOnOverallLoudnessResults OnOverallLoudnessResults;` — `UPROPERTY(BlueprintAssignable, Category = AudioAnalyzer)` — Delegate to receive all overall loudness results since last delegate call.
- L139 _public member_ `FOnPerChannelLoudnessResults OnPerChannelLoudnessResults;` — `UPROPERTY(BlueprintAssignable, Category = AudioAnalyzer)` — Delegate to receive all loudness results, per-channel, since last delegate call.
- L143 _public member_ `FOnLatestOverallLoudnessResults OnLatestOverallLoudnessResults;` — `UPROPERTY(BlueprintAssignable, Category = AudioAnalyzer)` — Delegate to receive the latest overall loudness results.
- L147 _public member_ `FOnLatestPerChannelLoudnessResults OnLatestPerChannelLoudnessResults;` — `UPROPERTY(BlueprintAssignable, Category = AudioAnalyzer)` — Delegate to receive the latest per-channel loudness results.
- L150 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const override;` — Convert ULoudnessSettings to FLoudnessSettings
- L153 _public prototype_ `void BroadcastResults() override;` — Broadcasts results to any delegates if hooked up.
- L158 _protected prototype_ `FName GetAnalyzerFactoryName() const override;` — Return the name of the IAudioAnalyzerFactory associated with this UAudioAnalyzer

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`
- L102 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverallLoudnessResults, const TArray<FLoudnessResults>&, OverallLoudnessResults);` — Delegate to receive all overall loudness results (time-stamped in an array) since last delegate call.
- L102 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverallLoudnessResults, const TArray<FLoudnessResults>&, OverallLoudnessResults);` — Delegate to receive all overall loudness results (time-stamped in an array) since last delegate call.
- L105 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLatestOverallLoudnessResults, const FLoudnessResults&, LatestOverallLoudnessResults);` — Delegate to receive only the most recent overall loudness result.
- L105 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLatestOverallLoudnessResults, const FLoudnessResults&, LatestOverallLoudnessResults);` — Delegate to receive only the most recent overall loudness result.
- L108 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerChannelLoudnessResults, int32, ChannelIndex, const TArray<FLoudnessResults>&, LoudnessResults);` — Delegate to receive all loudness results per channel (time-stamped in an array) since last delegate call.
- L108 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerChannelLoudnessResults, int32, ChannelIndex, const TArray<FLoudnessResults>&, LoudnessResults);` — Delegate to receive all loudness results per channel (time-stamped in an array) since last delegate call.
- L111 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestPerChannelLoudnessResults, int32, ChannelIndex, const FLoudnessResults&, LatestLoudnessResults);` — Delegate to receive only the most recent overall loudness result per channel.
- L111 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestPerChannelLoudnessResults, int32, ChannelIndex, const FLoudnessResults&, LatestLoudnessResults);` — Delegate to receive only the most recent overall loudness result per channel.

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/LoudnessNRT.h` (Public)


#### enum `ELoudnessNRTCurveTypeEnum`  
`enum class ELoudnessNRTCurveTypeEnum : uint8`  
_L15-29_
- reflection: `UENUM(BlueprintType)`
- desc: ELoudnessNRTCurveTypeEnum Enumeration of available equal loudness curves. Loudness curves based on IEC 61672-1:2013 Electroacoustics - Sound level meters - Part 1: Specifications.
- L18 _public enumerator_ `A UMETA(DisplayName="A")` — Loudness Curve A Weighting. Commonly used in environmental sound measurements. Best for low level sounds.
- L20 _public enumerator_ `B UMETA(DisplayName="B")` — Loudness Curve B Weighting. Relative to "A", gives more precedence to frequencies below 1kHz.
- L22 _public enumerator_ `C UMETA(DisplayName="C")` — Loudness Curve C Weighting. Relative to "A" and "B", gives more precedence to frequencies below 1kHz.
- L24 _public enumerator_ `D UMETA(DisplayName="D")` — Loudness Curve D Weighting. Similar to "B" but with an emphasis on presence in the 2kHz-6KHz frequency range.
- L26 _public enumerator_ `K UMETA(DisplayName = "K")` — Loudness Curve K Weighting. Correlates with subjective perception of recorded broadcast content.
- L28 _public enumerator_ `None UMETA(DisplayName="None")` — No loudness curve weighting.

#### class `ULoudnessNRTSettings`  
`class ULoudnessNRTSettings : public UAudioSynesthesiaNRTSettings`  
_L36-71_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaNRTSettings`
- desc: ULoudnessNRTSettings Settings for a ULoudnessNRT analyzer.
- L41 _public prototype_ `ULoudnessNRTSettings();`
- L45 _public member_ `float AnalysisPeriod;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "0.25"))` — Number of seconds between loudness measurements
- L49 _public member_ `float MinimumFrequency;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "20.0", ClampMax = "20000"))` — Minimum analysis frequency for calculating loudness.
- L53 _public member_ `float MaximumFrequency;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "20.0", ClampMax = "20000"))` — Maximum analysis frequency for calculating loudness.
- L57 _public member_ `ELoudnessNRTCurveTypeEnum CurveType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer)` — Type of equal loudness curve used in calculations
- L61 _public member_ `float NoiseFloorDb;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category=AudioAnalyzer, meta = (ClampMin = "-100.0", ClampMax="0"))` — dB level to denote silence.  Used when calculating normalized loudness.
- L64 _public prototype_ `TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const;` — Convert ULoudnessNRTSettings to FLoudnessNRTSettings
- L67 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L69 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### class `ULoudnessNRT`  
`class ULoudnessNRT : public UAudioSynesthesiaNRT`  
_L82-134_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaNRT`
- desc: ULoudnessNRT ULoudnessNRT calculates the temporal evolution of perceptual loudness for a given sound. Loudness is available for individual channels or the overall sound asset. Normalized loudness values convert the range to 0.0 to 1.0 where 0.0 is the noise floor and 1.0 is the maximum loudness of the particular sound.
- L88 _public prototype_ `ULoudnessNRT();`
- L92 _public member_ `TObjectPtr<ULoudnessNRTSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ExposeOnSpawn))` — The settings for the audio analyzer.
- L96 _public prototype_ `void GetLoudnessAtTime(const float InSeconds, float& OutLoudness) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get the overall loudness of the analyzed sound at a given time.
- L100 _public prototype_ `void GetChannelLoudnessAtTime(const float InSeconds, const int32 InChannel, float& OutLoudness) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get a specific channel loudness of the analyzed sound at a given time.
- L108 _public prototype_ `void GetNormalizedLoudnessAtTime(const float InSeconds, float& OutLoudness) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get the normalized overall loudness of the analyzed sound at a given time. Normalized loudness is always between 0.0 to 1.0. 0.0 refers to the noise floor while 1.0 refers to the maximum loudness in the sound.
- L116 _public prototype_ `void GetNormalizedChannelLoudnessAtTime(const float InSeconds, const int32 InChannel, float& OutLoudness) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get a specific channel normalized loudness of the analyzed sound at a given time. Normalized loudness is always between 0.0 to 1.0. 0.0 refers to the noise floor while 1.0 refers to the maximum loudness in the sound.
- L119 _public prototype_ `TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const override;` — Convert ULoudnessNRTSettings to FLoudnessNRTSettings
- L122 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L124 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L126 _public prototype_ `virtual bool ShouldEventTriggerAnalysis(FPropertyChangedEvent& PropertyChangeEvent) override;`
- L132 _protected prototype_ `FName GetAnalyzerNRTFactoryName() const override;` — Return the name of the IAudioAnalyzerNRTFactory associated with this UAudioAnalyzerNRT

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/Meter.h` (Public)


#### enum `EMeterPeakType`  
`enum class EMeterPeakType : uint8`  
_L13-20_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `MeanSquared`
- L16 _public enumerator_ `RootMeanSquared`
- L17 _public enumerator_ `Peak`
- L18 _public enumerator_ `TruePeak`
- L19 _public enumerator_ `Count UMETA(Hidden)`

#### class `UMeterSettings`  
`class UMeterSettings : public UAudioSynesthesiaSettings`  
_L27-70_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaSettings`
- desc: UMeterSettings Settings for a UMeterAnalyzer.
- L32 _public function_ `UMeterSettings()`
- L36 _public member_ `float AnalysisPeriod = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "0.25"))` — Number of seconds between meter measurements
- L40 _public member_ `EMeterPeakType PeakMode = EMeterPeakType::RootMeanSquared;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Meter envelope type type
- L44 _public member_ `int32 MeterAttackTime = 300;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "0"))` — Meter attack time, in milliseconds
- L48 _public member_ `int32 MeterReleaseTime = 300;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "0"))` — Meter release time, in milliseconds.
- L52 _public member_ `int32 PeakHoldTime = 100;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "0"))` — Peak hold time, in milliseconds
- L56 _public member_ `float ClippingThreshold = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "0.0"))` — What volume threshold to throw clipping detection notifications.
- L60 _public member_ `bool bIsAnalog = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Analog response.
- L63 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const;` — Convert UMeterSettings to IAnalyzerSettings
- L66 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L68 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### struct `FMeterResults`  
`struct FMeterResults`  
_L74-97_
- reflection: `USTRUCT(BlueprintType)`
- desc: The results of the meter analysis.
- L80 _public member_ `float TimeSeconds = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The time in seconds since analysis began of this meter analysis result
- L84 _public member_ `float MeterValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The meter value
- L88 _public member_ `float PeakValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The peak value
- L92 _public member_ `int32 NumSamplesClipping = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The number of samples in the period which were above the clipping threshold. Will be 0 if no clipping was detected.
- L96 _public member_ `float ClippingValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The value (if non-zero) if clipping was detected above the clipping threshold

#### class `UMeterAnalyzer`  
`class UMeterAnalyzer : public UAudioAnalyzer`  
_L129-175_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioAnalyzer`
- desc: UMeterAnalyzer UMeterAnalyzer calculates the current amplitude of an audio bus in real-time.
- L135 _public prototype_ `UMeterAnalyzer();`
- L139 _public member_ `TObjectPtr<UMeterSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioAnalyzer)` — The settings for the meter audio analyzer.
- L143 _public member_ `FOnOverallMeterResults OnOverallMeterResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive all overall meter results since last delegate call.
- L145 _public member_ `FOnOverallMeterResultsNative OnOverallMeterResultsNative;`
- L149 _public member_ `FOnPerChannelMeterResults OnPerChannelMeterResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive all meter results, per-channel, since last delegate call.
- L151 _public member_ `FOnPerChannelMeterResultsNative OnPerChannelMeterResultsNative;`
- L155 _public member_ `FOnLatestOverallMeterResults OnLatestOverallMeterResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive the latest overall meter results.
- L157 _public member_ `FOnLatestOverallMeterResultsNative OnLatestOverallMeterResultsNative;`
- L161 _public member_ `FOnLatestPerChannelMeterResults OnLatestPerChannelMeterResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive the latest per-channel meter results.
- L163 _public member_ `FOnLatestPerChannelMeterResultsNative OnLatestPerChannelMeterResultsNative;`
- L166 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const override;` — Convert UMeterSettings to IAnalyzerSettings
- L169 _public prototype_ `void BroadcastResults() override;` — Broadcasts results to any delegates if hooked up.
- L174 _protected prototype_ `FName GetAnalyzerFactoryName() const override;` — Return the name of the IAudioAnalyzerFactory associated with this UAudioAnalyzer

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`
- L100 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverallMeterResults, const TArray<FMeterResults>&, MeterResults);` — Delegate to receive all overall loudness results (time-stamped in an array) since last delegate call.
- L100 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverallMeterResults, const TArray<FMeterResults>&, MeterResults);` — Delegate to receive all overall loudness results (time-stamped in an array) since last delegate call.
- L103 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallMeterResultsNative, UMeterAnalyzer*, const TArray<FMeterResults>&);` — shadow delegate declaration for above
- L103 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallMeterResultsNative, UMeterAnalyzer*, const TArray<FMeterResults>&);` — shadow delegate declaration for above
- L106 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLatestOverallMeterResults, const FMeterResults&, LatestOverallMeterResults);` — Delegate to receive only the most recent overall meter results.
- L106 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLatestOverallMeterResults, const FMeterResults&, LatestOverallMeterResults);` — Delegate to receive only the most recent overall meter results.
- L109 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLatestOverallMeterResultsNative, UMeterAnalyzer*, const FMeterResults&);` — shadow delegate declaration for above
- L109 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLatestOverallMeterResultsNative, UMeterAnalyzer*, const FMeterResults&);` — shadow delegate declaration for above
- L112 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerChannelMeterResults, int32, ChannelIndex, const TArray<FMeterResults>&, MeterResults);` — Delegate to receive all meter results per channel (time-stamped in an array) since last delegate call.
- L112 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerChannelMeterResults, int32, ChannelIndex, const TArray<FMeterResults>&, MeterResults);` — Delegate to receive all meter results per channel (time-stamped in an array) since last delegate call.
- L115 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPerChannelMeterResultsNative, UMeterAnalyzer*, int32, const TArray<FMeterResults>&);` — shadow delegate declaration for above
- L115 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPerChannelMeterResultsNative, UMeterAnalyzer*, int32, const TArray<FMeterResults>&);` — shadow delegate declaration for above
- L118 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestPerChannelMeterResults, int32, ChannelIndex, const FMeterResults&, LatestMeterResults);` — Delegate to receive only the most recent overall meter result per channel.
- L118 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestPerChannelMeterResults, int32, ChannelIndex, const FMeterResults&, LatestMeterResults);` — Delegate to receive only the most recent overall meter result per channel.
- L121 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLatestPerChannelMeterResultsNative, UMeterAnalyzer*, int32, const FMeterResults&);` — shadow delegate declaration for above
- L121 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLatestPerChannelMeterResultsNative, UMeterAnalyzer*, int32, const FMeterResults&);` — shadow delegate declaration for above

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/OnsetNRT.h` (Public)


#### class `UOnsetNRTSettings`  
`class UOnsetNRTSettings : public UAudioSynesthesiaNRTSettings`  
_L15-50_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaNRTSettings`
- desc: UOnsetNRTSettings Settings for a UOnsetNRT analyzer.
- L20 _public prototype_ `UOnsetNRTSettings();`
- L24 _public member_ `bool bDownmixToMono;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer)` — If true, multichannel audio is downmixed to mono with equal amplitude scaling. If false, each channel gets it's own onset result.
- L28 _public member_ `float GranularityInSeconds;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "0.005", ClampMax = "0.25"))` — Onset timestamp granularity onsets. Lower granularity takes longer to compute.
- L32 _public member_ `float Sensitivity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Sensitivity of onset detector. Higher sensitivity will find more onsets.
- L36 _public member_ `float MinimumFrequency;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "20.0", ClampMax = "20000"))` — Starting frequency for onset anlaysis.
- L40 _public member_ `float MaximumFrequency;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer, meta = (ClampMin = "20.0", ClampMax = "20000"))` — Starting frequency for onset anlaysis.
- L43 _public prototype_ `TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const;` — Convert UOnsetNRTSettings to FOnsetNRTSettings
- L46 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L48 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### class `UOnsetNRT`  
`class UOnsetNRT : public UAudioSynesthesiaNRT`  
_L59-94_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaNRT`
- desc: UOnsetNRT UOnsetNRT calculates the temporal evolution of constant q transform for a given sound. Onset is available for individual channels or the overall sound asset.
- L65 _public prototype_ `UOnsetNRT();`
- L69 _public member_ `TObjectPtr<UOnsetNRTSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AudioAnalyzer)` — The settings for the audio analyzer.
- L73 _public prototype_ `void GetChannelOnsetsBetweenTimes(const float InStartSeconds, const float InEndSeconds, const int32 InChannel, TArray<float>& OutOnsetTimestamps, TArray<float>& OutOnsetStrengths) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Returns onsets which occured between start and end timestamps.
- L77 _public prototype_ `void GetNormalizedChannelOnsetsBetweenTimes(const float InStartSeconds, const float InEndSeconds, const int32 InChannel, TArray<float>& OutOnsetTimestamps, TArray<float>& OutOnsetStrengths) const;` — `UFUNCTION(BlueprintCallable, Category="Audio Analyzer")` — Get a specific channel cqt of the analyzed sound at a given time.
- L80 _public prototype_ `virtual TUniquePtr<Audio::IAnalyzerNRTSettings> GetSettings(const float InSampleRate, const int32 InNumChannels) const override;` — Convert ULoudnessNRTSettings to FLoudnessNRTSettings
- L83 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L85 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L87 _public prototype_ `virtual bool ShouldEventTriggerAnalysis(FPropertyChangedEvent& PropertyChangeEvent) override;`
- L92 _protected prototype_ `virtual FName GetAnalyzerNRTFactoryName() const override;` — Return the name of the IAudioAnalyzerNRTFactory associated with this UAudioAnalyzerNRT

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Classes/SynesthesiaSpectrumAnalysis.h` (Public)


#### class `USynesthesiaSpectrumAnalysisSettings`  
`class USynesthesiaSpectrumAnalysisSettings : public UAudioSynesthesiaSettings`  
_L18-53_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioSynesthesiaSettings`
- desc: USynesthesiaSpectrumAnalysisSettings Settings for a USynesthesiaSpectrumAnalysisAnalyzer.
- L23 _public function_ `USynesthesiaSpectrumAnalysisSettings()`
- L27 _public member_ `float AnalysisPeriod = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer, meta = (ClampMin = "0.01", ClampMax = "0.25"))` — Number of seconds between SynesthesiaSpectrumAnalysis measurements
- L31 _public member_ `EFFTSize FFTSize = EFFTSize::DefaultSize;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Size of FFT.
- L35 _public member_ `EAudioSpectrumType SpectrumType = EAudioSpectrumType::PowerSpectrum;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Type of spectrum to use.
- L39 _public member_ `EFFTWindowType WindowType = EFFTWindowType::Hann;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Type of window to use.
- L43 _public member_ `bool bDownmixToMono = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — If true, multichannel audio is downmixed to mono with equal amplitude scaling. If false, each channel gets its own FFT result.
- L46 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const;` — Convert USynesthesiaSpectrumAnalysisSettings to IAnalyzerSettings
- L49 _public prototype_ `virtual FText GetAssetActionName() const override;`
- L51 _public prototype_ `virtual UClass* GetSupportedClass() const override;`

#### struct `FSynesthesiaSpectrumResults`  
`struct FSynesthesiaSpectrumResults`  
_L57-68_
- reflection: `USTRUCT(BlueprintType)`
- desc: The results of the spectrum analysis.
- L63 _public member_ `float TimeSeconds = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The time in seconds since analysis began of this SynesthesiaSpectrumAnalysis analysis result
- L67 _public member_ `TArray<float> SpectrumValues;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The spectrum values from the FFT

#### class `USynesthesiaSpectrumAnalyzer`  
`class USynesthesiaSpectrumAnalyzer : public UAudioAnalyzer`  
_L88-128_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAudioAnalyzer`
- desc: USynesthesiaSpectrumAnalysisAnalyzer USynesthesiaSpectrumAnalysisAnalyzer calculates the current amplitude of an audio bus in real-time.
- L94 _public prototype_ `USynesthesiaSpectrumAnalyzer();`
- L98 _public member_ `TObjectPtr<USynesthesiaSpectrumAnalysisSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioAnalyzer)` — The settings for the SynesthesiaSpectrumAnalysis audio analyzer.
- L102 _public member_ `FOnSpectrumResults OnSpectrumResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive all Spectrum results, per-channel, since last delegate call. If bDownmixToMono setting is true, results will be in channel index 0.
- L104 _public member_ `FOnSpectrumResultsNative OnSpectrumResultsNative;`
- L108 _public member_ `FOnLatestSpectrumResults OnLatestSpectrumResults;` — `UPROPERTY(BlueprintAssignable)` — Delegate to receive the latest per-channel Spectrum results. If bDownmixToMono setting is true, results will be in channel index 0.
- L110 _public member_ `FOnLatestSpectrumResultsNative OnLatestSpectrumResultsNative;`
- L113 _public prototype_ `TUniquePtr<Audio::IAnalyzerSettings> GetSettings(const int32 InSampleRate, const int32 InNumChannels) const override;` — Convert USynesthesiaSpectrumAnalysisSettings to IAnalyzerSettings
- L116 _public prototype_ `void BroadcastResults() override;` — Broadcasts results to any delegates if hooked up.
- L119 _public prototype_ `void GetCenterFrequencies(UPARAM(DisplayName = "Sample Rate") const float InSampleRate, UPARAM(DisplayName = "Center Frequencies") TArray<f` — `UFUNCTION(BlueprintCallable, Category = "Audio Analyzer")`
- L122 _public prototype_ `UPARAM(DisplayName = "Num Center Frequencies") const int32 GetNumCent` — `UFUNCTION(BlueprintCallable, Category = "Audio Analyzer")`
- L127 _protected prototype_ `FName GetAnalyzerFactoryName() const override;` — Return the name of the IAudioAnalyzerFactory associated with this UAudioAnalyzer

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`
- L71 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpectrumResults, int32, ChannelIndex, const TArray<FSynesthesiaSpectrumResults>&, SpectrumResults);` — Delegate to receive all spectrum results per channel (time-stamped in an array) since last delegate call. If bDownmixToMono setting is true, results will be in channel index 0.
- L71 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpectrumResults, int32, ChannelIndex, const TArray<FSynesthesiaSpectrumResults>&, SpectrumResults);` — Delegate to receive all spectrum results per channel (time-stamped in an array) since last delegate call. If bDownmixToMono setting is true, results will be in channel index 0.
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSpectrumResultsNative, USynesthesiaSpectrumAnalyzer*, int32, const TArray<FSynesthesiaSpectrumResults>&);` — shadow delegate declaration for above
- L74 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSpectrumResultsNative, USynesthesiaSpectrumAnalyzer*, int32, const TArray<FSynesthesiaSpectrumResults>&);` — shadow delegate declaration for above
- L77 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestSpectrumResults, int32, ChannelIndex, const FSynesthesiaSpectrumResults&, LatestSpectrumResults);` — Delegate to receive only the most recent overall spectrum result per channel. If bDownmixToMono setting is true, results will be in channel index 0.
- L77 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLatestSpectrumResults, int32, ChannelIndex, const FSynesthesiaSpectrumResults&, LatestSpectrumResults);` — Delegate to receive only the most recent overall spectrum result per channel. If bDownmixToMono setting is true, results will be in channel index 0.
- L80 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLatestSpectrumResultsNative, USynesthesiaSpectrumAnalyzer*, int32, const FSynesthesiaSpectrumResults&);` — shadow delegate declaration for above
- L80 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnLatestSpectrumResultsNative, USynesthesiaSpectrumAnalyzer*, int32, const FSynesthesiaSpectrumResults&);` — shadow delegate declaration for above

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Private/AudioSynesthesiaLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioSynesthesia, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioSynesthesia, Log, All);`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesia/Public/AudioSynesthesiaModule.h` (Public)


#### class `Audio::FAudioSynesthesiaModule`  
`class FAudioSynesthesiaModule : public IModuleInterface`  
_L14-26_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private member_ `FLoudnessNRTFactory LoudnessFactory;`
- L24 _private member_ `FConstantQNRTFactory ConstantQFactory;`
- L25 _private member_ `FOnsetNRTFactory OnsetFactory;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOSYNESTHESIA_API`
- L12 _namespace_ `namespace Audio`
