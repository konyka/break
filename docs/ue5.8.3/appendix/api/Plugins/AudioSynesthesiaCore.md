# Plugins / AudioSynesthesiaCore

- module root: `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore`
- headers: 25; symbols: 667
- symbol kinds: class=47, delegate=1, enum=3, enumerator=8, function=16, macro=10, member=323, namespace=39, prototype=193, struct=27
- PrivateDependencyModuleNames: AudioMixerCore
- PublicDependencyModuleNames: Core, CoreUObject, SignalProcessing
- PublicIncludePathModuleNames: AudioAnalyzer

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Private/AudioSynesthesiaCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioSynesthesiaCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioSynesthesiaCore, Log, All);`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Private/AudioSynesthesiaCustomVersion.h` (Private)


#### struct `FAudioSynesthesiaCustomVersion`  
`struct FAudioSynesthesiaCustomVersion`  
_L9-25_
- desc: Custom serialization version for all packages containing AudioSynesthesia asset types
- L22 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L24 _public prototype_ `FAudioSynesthesiaCustomVersion() = delete;`

#### enum `FAudioSynesthesiaCustomVersion::Type`  
`enum Type`  
_L11-19_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the module
- L17 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L18 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/AudioSynesthesiaCoreModule.h` (Public)


#### class `Audio::IAudioSynesthesiaCoreModule`  
`class IAudioSynesthesiaCoreModule : public IModuleInterface`  
_L9-11_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/AutoCorrelationPitchDetector.h` (Public)


#### struct `Audio::FAutoCorrelationPitchDetectorSettings`  
`struct FAutoCorrelationPitchDetectorSettings`  
_L17-31_
- desc: Settings for creating an autocorrelation pitch detector.
- L20 _public member_ `float AnalysisHopSeconds = 0.01f;` — Time (in seconds) between analysis windows.
- L23 _public member_ `float MinimumFrequency = 20.f;` — Minimum frequency of pitch result.
- L26 _public member_ `float MaximumFrequency = 10000.f;` — Maximum frequency of pitch result.
- L30 _public member_ `float Sensitivity = 0.5f;` — Sensitivity of peak detection. Valid values are between 0.0 and 1.0. 0.0 results in the least amount of pitches, while 1.0 result in the most pitches.

#### class `Audio::FAutoCorrelationPitchDetector`  
`class FAutoCorrelationPitchDetector : public IPitchDetector`  
_L38-73_
- inherits: `IPitchDetector`
- desc: Pitch detector based on autocorrelation. Note that autocorrelation pitch detectors give more accurate frequency results for low frequencies, but have issues with octave errors. Generally, it will produce erroneous frequency observations in octaves _below_ the true pitch frequency.
- L42 _public prototype_ `FAutoCorrelationPitchDetector(const FAutoCorrelationPitchDetectorSettings& InSettings, float InSampleRate);` — Create an auto correlation pitch detector with settings and a sample rate.
- L44 _public prototype_ `virtual ~FAutoCorrelationPitchDetector();`
- L51 _public prototype_ `virtual void DetectPitches(const FAlignedFloatBuffer& InMonoAudio, TArray<FPitchInfo>& OutPitches) override;` — Detect pitches in the audio. This can be called repeatedly with new audio. @param InMonoAudio - A mono audio buffer of any length. @param OutPitches - This array is filled with pitch observations.
- L54 _public prototype_ `virtual void Finalize(TArray<FPitchInfo>& OutPitches) override;` — Resets internal audio buffers. This pitch detector does not produce any more pitches on Finalize.
- L58 _private member_ `FAutoCorrelationPitchDetectorSettings Settings;`
- L60 _private member_ `float SampleRate;`
- L61 _private member_ `int32 MinAutoCorrBin;`
- L62 _private member_ `int32 MaxAutoCorrBin;`
- L63 _private member_ `int32 WindowCounter;`
- L65 _private member_ `TSlidingBuffer<float> SlidingBuffer;`
- L66 _private member_ `FAlignedFloatBuffer WindowBuffer;`
- L67 _private member_ `FAlignedFloatBuffer AutoCorrBuffer;`
- L68 _private member_ `TUniquePtr<FBlockCorrelator> Correlator;`
- L70 _private member_ `TArray<int32> PeakIndices;`
- L71 _private member_ `TUniquePtr<FPeakPicker> PeakPicker;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L11 _namespace_ `namespace Audio`
- L12 _namespace_ `namespace Audio`
- L14 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/ConstantQAnalyzer.h` (Public)


#### enum `Audio::EConstantQScaling`  
`enum class EConstantQScaling : uint8`  
_L15-22_
- desc: Denotes which magnitude scaling to apply to output
- L18 _public enumerator_ `Linear` — CQT spectrum values conform to ESpectrumType, either magnitude or power.
- L21 _public enumerator_ `Decibel` — CQT spectrum values are in decibels.

#### struct `Audio::FConstantQAnalyzerSettings`  
`struct FConstantQAnalyzerSettings : public FPseudoConstantQKernelSettings`  
_L28-48_
- inherits: `FPseudoConstantQKernelSettings`
- desc: FConstantQAnalyzerSettings Settings for the Constant Q Analyzer.
- L31 _public member_ `int32 FFTSize;` — Size of FFT describe in number of samples
- L34 _public member_ `EWindowType WindowType;` — Type of window to be applied to input audio
- L37 _public member_ `ESpectrumType SpectrumType;` — Type of spectrum to use.
- L40 _public member_ `EConstantQScaling Scaling;` — Type of scaling to use.
- L42 _public function_ `FConstantQAnalyzerSettings() : FFTSize(1024) , WindowType(EWindowType::Blackman) , SpectrumType(ESpectrumType::PowerSpectrum) , Scaling(EConstantQScaling::Decibel)`

#### class `Audio::FConstantQAnalyzer`  
`class FConstantQAnalyzer`  
_L57-99_
- desc: FConstantQAnalyzer The Constant Q Analyzer computs a pseudo constant q transform of the input audio. ConstantQ transforms produce frequency strength at logarithmically spaced frequency intervals (as opposed to the linearly spaced intervals of the FFT). Logarithmically spaced frequency intervals map nicely to musical scales.
- L66 _public prototype_ `FConstantQAnalyzer(const FConstantQAnalyzerSettings& InSettings, const float InSampleRate);` — Construct a FConstantQAnalyzer InSettings contains the parameters used to configure the analyzer. InSampleRate is the sample rate of the input audio.
- L73 _public prototype_ `void CalculateCQT(const float* InSamples, TArray<float>& OutCQT);` — Calcualte Constant Q Transform of input audio. InSamples is an array of input audio. It must be of length GetSettings().FFTSize. OutCQT will be populated with the constants q transform values. It will have GetSettings().NumBands values.
- L76 _public prototype_ `const FConstantQAnalyzerSettings& GetSettings() const;` — Returns a reference to the settings used in this analyzer
- L80 _private member_ `const FConstantQAnalyzerSettings Settings;`
- L82 _private member_ `const float SampleRate;`
- L84 _private member_ `int32 ActualFFTSize;`
- L87 _private member_ `int32 NumUsefulFFTBins;` — Only the first (FFTSize / 2) + 1 FFT bins are used since FFT of real values is conjugate symmetric.
- L90 _private member_ `FWindow Window;` — Scale factor to normalize between different FFT Sizes
- L92 _private member_ `FAlignedFloatBuffer WindowedSamples;`
- L93 _private member_ `FAlignedFloatBuffer ComplexSpectrum;`
- L94 _private member_ `FAlignedFloatBuffer RealSpectrum;`
- L96 _private member_ `TUniquePtr<IFFTAlgorithm> FFT;`
- L98 _private member_ `TUniquePtr<FContiguousSparse2DKernelTransform> CQTTransform;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L10 _namespace_ `namespace Audio`
- L12 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/ConstantQFactory.h` (Public)


#### struct `Audio::FConstantQSettings`  
`struct FConstantQSettings : public IAnalyzerSettings, public FConstantQAnalyzerSettings`  
_L17-29_
- inherits: `IAnalyzerSettings,FConstantQAnalyzerSettings`
- desc: FConstantQSettings Settings for the Constant Q Non-Real-Time Factory.
- L21 _public member_ `float AnalysisPeriodInSeconds = 0.01f;` — Time, in seconds, between constant Q frames.
- L28 _public member_ `bool bDownmixToMono = false;` — If true, all channels are mixed together with equal power before analysis. Only one channel is produced at channel index 0. If false, then each channel is analyzed separately.

#### class `Audio::FConstantQResult`  
`class FConstantQResult : public IAnalyzerResult`  
_L34-51_
- inherits: `IAnalyzerResult`
- desc: FLoudnessResult contains the temporal evolution of loudness for the last buffer of audio analyzed.
- L38 _public function_ `FConstantQResult()`
- L41 _public prototype_ `void AddFrame(const int32 InChannelIndex, const float InTimestamp, TArrayView<const float> InSpectrum);` — Add a single frame of CQT data
- L44 _public prototype_ `const TArray<FConstantQFrame>& GetFramesForChannel(const int32 ChannelIdx) const;` — Returns const reference to FLoudnessDatum array for individual channel.
- L47 _public prototype_ `int32 GetNumChannels() const;` — Returns the number of channels.
- L50 _private member_ `TMap<int32, TArray<FConstantQFrame> > ChannelCQTFrames;`

#### class `Audio::FConstantQWorker`  
`class FConstantQWorker : public IAnalyzerWorker`  
_L57-103_
- inherits: `IAnalyzerWorker`
- desc: FConstantQWorker FConstantQWorker computes a FConstantQResult from audio samples.
- L66 _public prototype_ `FConstantQWorker(const FAnalyzerParameters& InParams, const FConstantQSettings& InAnalyzerSettings);` — Constructor InParams are the parameters which describe characteristics of the input audio. InAnalyzerSettings are the settings which control various aspects of the algorithm.
- L74 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerResult* OutResult) override;` — Analyze audio and put results into results pointer. InAudio is an array view of audio. OutResult is a pointer to a valid FConstantQResult
- L78 _private prototype_ `void AnalyzeMultichannel(TArrayView<const float> InAudio, IAnalyzerResult* OutResult, const bool bDoFlush);` — Analyze audio with multiple channels interleaved.
- L81 _private prototype_ `void AnalyzeWindow(const FAlignedFloatBuffer& InWindow, const int32 InChannelIndex, FConstantQResult& OutResult);` — Analyze a single window of audio from a single channel
- L83 _private member_ `int32 NumChannels = 0;`
- L84 _private member_ `int32 NumBuffers = 0;`
- L85 _private member_ `float SampleRate = 0.0f;`
- L86 _private member_ `int32 NumHopFrames = 0;`
- L87 _private member_ `int32 NumHopSamples = 0;`
- L88 _private member_ `int32 NumWindowFrames = 0;`
- L89 _private member_ `int32 NumWindowSamples = 0;`
- L91 _private member_ `float MonoScaling = 1.0f;`
- L93 _private member_ `FAlignedFloatBuffer HopBuffer;`
- L94 _private member_ `FAlignedFloatBuffer ChannelBuffer;`
- L95 _private member_ `FAlignedFloatBuffer MonoBuffer;`
- L97 _private member_ `TArray<float> CQTSpectrum;`
- L99 _private member_ `TUniquePtr<TSlidingBuffer<float> > SlidingBuffer;`
- L100 _private member_ `TUniquePtr<FConstantQAnalyzer> ConstantQAnalyzer;`
- L102 _private member_ `bool bDownmixToMono = false;`

#### class `Audio::FConstantQFactory`  
`class FConstantQFactory : public IAnalyzerFactory`  
_L109-127_
- inherits: `IAnalyzerFactory`
- desc: FConstantQFactory Factory for creating FConstantQ workers and results
- L114 _public prototype_ `virtual FName GetName() const override;` — Name of this analyzer type.
- L117 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of this analyzer.
- L120 _public prototype_ `virtual TUniquePtr<IAnalyzerResult> NewResult() const override;` — Create a new FConstantQResult.
- L126 _public prototype_ `virtual TUniquePtr<IAnalyzerWorker> NewWorker(const FAnalyzerParameters& InParams, const IAnalyzerSettings* InSettings) const override;` — Create a new FConstantQWorker InSettings must be a pointer to FConstantQSetting

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/ConstantQNRTFactory.h` (Public)


#### class `Audio::FConstantQNRTSettings`  
`class FConstantQNRTSettings : public IAnalyzerNRTSettings, public FConstantQAnalyzerSettings`  
_L16-34_
- inherits: `IAnalyzerNRTSettings,FConstantQAnalyzerSettings`
- desc: FConstantQNRTSettings Settings for the Constant Q Non-Real-Time Factory.
- L21 _public member_ `float AnalysisPeriod;` — Time, in seconds, between constant Q frames.
- L28 _public member_ `bool bDownmixToMono;` — If true, all channels are mixed together with equal power before analysis. Only one channel is produced at channel index 0. If false, then each channel is analyzed separately.
- L30 _public function_ `FConstantQNRTSettings() : AnalysisPeriod(0.01f) , bDownmixToMono(false)`

#### struct `Audio::FConstantQFrame`  
`struct FConstantQFrame`  
_L41-62_
- desc: FConstantQFrame Contains Constant Q data relating to one audio window.
- L44 _public member_ `int32 Channel;` — Audio channel which produced the data.
- L47 _public member_ `float Timestamp;` — Timestamp in seconds referring to the center of the audio window.
- L50 _public member_ `TArray<float> Spectrum;` — Output spectral data
- L52 _public function_ `FConstantQFrame() : Channel(0) , Timestamp(0.f)`
- L57 _public function_ `FConstantQFrame(int32 InChannelIndex, float InTimestamp, TArrayView<const float> InSpectrum) : Channel(InChannelIndex) , Timestamp(InTimestamp) , Spectrum(InSpectrum.GetData(), InSpectrum.Num())`

#### class `Audio::FConstantQNRTResult`  
`class FConstantQNRTResult : public IAnalyzerNRTResult`  
_L71-117_
- inherits: `IAnalyzerNRTResult`
- desc: FConstantQNRTResult FConstantQNRTResult is a container for the output of the FConstantQNRTWorker.
- L75 _public prototype_ `FConstantQNRTResult();`
- L78 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — Serialize or unserialize object
- L81 _public prototype_ `void AddFrame(int32 InChannelIndex, float InTimestamp, TArrayView<const float> InSpectrum);` — Add a single frame of CQT data
- L84 _public prototype_ `bool ContainsChannel(int32 InChannelIndex) const;` — Returns true if this result contains data for the given channel index.
- L87 _public prototype_ `const TArray<FConstantQFrame>& GetFramesForChannel(int32 InChannelIndex) const;` — Retrieve the array of frames for a single channel of audio.
- L90 _public prototype_ `FFloatInterval GetChannelConstantQInterval(int32 InChannelIdx) const;` — Retrieve the difference between the maximum and minimum value in the spectrum.
- L93 _public prototype_ `void GetChannels(TArray<int32>& OutChannels) const;` — Retrieve an array of channel indices which exist in this result.
- L96 _public prototype_ `virtual float GetDurationInSeconds() const override;` — Returns the duration of the analyzed audio in seconds
- L99 _public prototype_ `void SetDurationInSeconds(float InDuration);` — Sets the duration of the analyzed audio in seconds
- L102 _public prototype_ `bool IsSortedChronologically() const;` — Returns true if FConstantQFrame arrays are sorted in chronologically ascending order via their timestamp.
- L105 _public prototype_ `void SortChronologically();` — Sorts FConstantQFrame arrays in chronologically ascnding order via their timestamp.
- L110 _private member_ `float DurationInSeconds;`
- L112 _private member_ `TMap<int32, TArray<FConstantQFrame> > ChannelCQTFrames;`
- L114 _private member_ `TMap<int32, FFloatInterval> ChannelCQTIntervals;`
- L116 _private member_ `bool bIsSortedChronologically;`

#### class `Audio::FConstantQNRTWorker`  
`class FConstantQNRTWorker : public IAnalyzerNRTWorker`  
_L123-178_
- inherits: `IAnalyzerNRTWorker`
- desc: FConstantQNRTWorker FConstantQNRTWorker computes a FConstantQNRTResult from audio samples.
- L132 _public prototype_ `FConstantQNRTWorker(const FAnalyzerNRTParameters& InParams, const FConstantQNRTSettings& InAnalyzerSettings);` — Constructor InParams are the parameters which describe characteristics of the input audio. InAnalyzerSettings are the settings which control various aspects of the algorithm.
- L140 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerNRTResult* OutResult) override;` — Analyze audio and put results into results pointer. InAudio is an array view of audio. OutResult is a pointer to a valid FConstantQNRTResult
- L147 _public prototype_ `virtual void Finalize(IAnalyzerNRTResult* OutResult) override;` — Call when analysis of audio asset is complete. OutResult must be a pointer to a valid FConstantQNRTResult.
- L152 _private prototype_ `void AnalyzeMultichannel(TArrayView<const float> InAudio, IAnalyzerNRTResult* OutResult, bool bDoFlush);` — Analyze audio with multiple channels interleaved.
- L155 _private prototype_ `void AnalyzeWindow(const FAlignedFloatBuffer& InWindow, int32 InChannelIndex, FConstantQNRTResult& OutResult);` — Analyze a single window of audio from a single channel
- L157 _private member_ `int32 NumFrames;`
- L158 _private member_ `int32 NumChannels;`
- L159 _private member_ `int32 NumBuffers;`
- L160 _private member_ `float SampleRate;`
- L161 _private member_ `int32 NumHopFrames;`
- L162 _private member_ `int32 NumHopSamples;`
- L163 _private member_ `int32 NumWindowFrames;`
- L164 _private member_ `int32 NumWindowSamples;`
- L166 _private member_ `float MonoScaling;`
- L168 _private member_ `FAlignedFloatBuffer HopBuffer;`
- L169 _private member_ `FAlignedFloatBuffer ChannelBuffer;`
- L170 _private member_ `FAlignedFloatBuffer MonoBuffer;`
- L172 _private member_ `TArray<float> CQTSpectrum;`
- L174 _private member_ `TUniquePtr<TSlidingBuffer<float> > SlidingBuffer;`
- L175 _private member_ `TUniquePtr<FConstantQAnalyzer> ConstantQAnalyzer;`
- L177 _private member_ `bool bDownmixToMono;`

#### class `Audio::FConstantQNRTFactory`  
`class FConstantQNRTFactory : public IAnalyzerNRTFactory`  
_L184-202_
- inherits: `IAnalyzerNRTFactory`
- desc: FConstantQNRTFactory Factory for creating FConstantQNRT workers and results
- L189 _public prototype_ `virtual FName GetName() const override;` — Name of this analyzer type.
- L192 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of this analyzer.
- L195 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTResult> NewResult() const override;` — Create a new FConstantQNRTResult.
- L201 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTWorker> NewWorker(const FAnalyzerNRTParameters& InParams, const IAnalyzerNRTSettings* InSettings) const override;` — Create a new FConstantQNRTWorker InSettings must be a pointer to FConstantQNRTSetting

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L10 _namespace_ `namespace Audio`
- L65 _prototype_ `FArchive &operator <<(FArchive& Ar, FConstantQFrame& Frame);` (scope `Audio`) — Serialize FConstantQFrame

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/FFTPeakPitchDetector.h` (Public)


#### struct `Audio::FFFTPeakPitchDetectorSettings`  
`struct FFFTPeakPitchDetectorSettings`  
_L17-40_
- desc: Settings for FFT base pitch detection
- L20 _public member_ `int32 Log2FFTSize = 13;` — Log 2 size of the FFT
- L23 _public member_ `float AnalysisWindowSeconds = 0.1f;` — Number of seconds represented in each analysis window.
- L26 _public member_ `float AnalysisHopSeconds = 0.01f;` — Number of seconds between analysis windows.
- L29 _public member_ `float MinimumFrequency = 20.f;` — Minimum frequency of detected pitches.
- L32 _public member_ `float MaximumFrequency = 10000.f;` — Maximum frequency of detected pitches.
- L36 _public member_ `float Sensitivity = 0.5f;` — Sensitivity of peak detection. Valid values are between 0.0 and 1.0. 0.0 results in the least amount of pitches, while 1.0 result in the most pitches.
- L39 _public member_ `float MaxStrengthSNRDecibels = 20.f;` — Reference SNR for calculating strength of signal.

#### class `Audio::FFFTPeakPitchDetector`  
`class FFFTPeakPitchDetector : public IPitchDetector`  
_L43-79_
- inherits: `IPitchDetector`
- desc: FFT based pitch detector accel at detecting pitches at higher frequencies.
- L47 _public prototype_ `FFFTPeakPitchDetector(const FFFTPeakPitchDetectorSettings& InSettings, float InSampleRate);` — Create an fft pitch detector with settings and a sample rate.
- L49 _public prototype_ `virtual ~FFFTPeakPitchDetector();`
- L56 _public prototype_ `virtual void DetectPitches(const FAlignedFloatBuffer& InMonoAudio, TArray<FPitchInfo>& OutPitches) override;` — Detect pitches in the audio. This can be called repeatedly with new audio. @param InMonoAudio - A mono audio buffer of any length. @param OutPitches - This array is filled with pitch observations.
- L59 _public prototype_ `virtual void Finalize(TArray<FPitchInfo>& OutPitches) override;` — Resets internal audio buffers. This pitch detector does not produce any more pitches on Finalize.
- L62 _private member_ `FFFTPeakPitchDetectorSettings Settings;`
- L64 _private member_ `float SampleRate;`
- L65 _private member_ `int32 FFTSize;`
- L66 _private member_ `int32 MinFFTBin;`
- L67 _private member_ `int32 MaxFFTBin;`
- L68 _private member_ `float FFTScaling;`
- L69 _private member_ `int32 WindowCounter;`
- L71 _private member_ `TUniquePtr<IFFTAlgorithm> FFTAlgorithm;`
- L72 _private member_ `TUniquePtr<FPeakPicker> PeakPicker;`
- L74 _private member_ `TSlidingBuffer<float> SlidingBuffer;`
- L75 _private member_ `FAlignedFloatBuffer WindowBuffer;`
- L76 _private member_ `FAlignedFloatBuffer ZeroPaddedAnalysisBuffer;`
- L77 _private member_ `FAlignedFloatBuffer ComplexSpectrumBuffer;`
- L78 _private member_ `FAlignedFloatBuffer PowerSpectrumBuffer;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L11 _namespace_ `namespace Audio`
- L12 _namespace_ `namespace Audio`
- L14 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/FindNearestByTimestamp.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`
- L21 _function_ `template<typename ElementType> ElementType* FindNearestByTimestamp(TArrayView<ElementType> InArray, float InTimestamp)` (scope `Audio`) — FindNearestByTimestamp Returns a pointer to the element with the timestamp nearest to InTimestamp in absolute terms.. ElementType must be a type with a "float Timestamp;" member. InArray is a array of ElementTypes which are sorted in ascending order via the Timestamp member. InTimestamp is the query timestamp.
- L29 _function_ `int32 UpperIndex = Algo::UpperBoundBy(InArray, InTimestamp, [](const ElementType& Datum) { return Datum.Timestamp; });` (scope `Audio::FindNearestByTimestamp`) — Get upper and lower array indices with FLoudnessData closest to the query timestamp.

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/InterpolateSorted.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L22 _function_ `template<typename ElementType> void GetInterpolationParametersAtTimestamp(TArrayView<const ElementType> InArray, float InTimestamp, int32& OutLowerIndex, int32& OutUpperIndex, float& OutAlpha)` (scope `Audio`) — GetInterpolationParametersAtTimestamp Calculates the indices and alpha parameter for interpolating between to elements in the array. ElementType must be a type with a "float Timestamp;" member. InArray is a array of ElementTypes which are sorted in ascending order via the Timestamp member. InTimestamp is the query timestamp. OutLowerIndex is populated with the index of the last element in InArray with a Timestamp less than or equal to InTimestamp. On error, this is set to INDEX_NONE OutUpperIndex is populated with the index of the first element in InArray with a Timestamp greater than InTimestamp. On error, this is set to INDEX_NONE OutAlpha is a number between 0.f and 1.f which describes the blending between the lower and upper indices. 0.f refers OutLowerIndex and 1.f to OutUpperIndex.
- L33 _function_ `OutUpperIndex = Algo::UpperBoundBy(InArray, InTimestamp, [](const ElementType& Datum) { return Datum.Timestamp; });` (scope `Audio::GetInterpolationParametersAtTimestamp`) — Get upper and lower array indices with FLoudnessData closest to the query timestamp.

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/LKFSFactory.h` (Public)


#### struct `FLKFSResults`  
`struct FLKFSResults`  
_L16-52_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data representing the instantaneous loudness of a audio.
- L23 _public member_ `int32 Channel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The audio channel index which produced this result. If -1, then the data was produced by combining all other audio channels
- L27 _public member_ `float Timestamp = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Time in seconds of the source audio which corresponds to the loudness measurements.
- L31 _public member_ `float Energy = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The instantaneous, perceptually weighted energy relative to full scale.
- L35 _public member_ `float Loudness = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The instantaneous, perceptually weighted loudness in dB.
- L39 _public member_ `float ShortTermLoudness = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The average loudness over a short term window of time in dB.
- L43 _public member_ `float IntegratedLoudness = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The average loudness over a long term window of time in dB.
- L47 _public member_ `float GatedLoudness = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The average gated loudness over a long term window of time in dB.
- L51 _public member_ `TOptional<FFloatInterval> LoudnessRange;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Loudness Range (LRA), as defined in EBU Tech 3342.

#### class `Audio::FLKFSSettings`  
`class FLKFSSettings : public IAnalyzerSettings, public FLKFSAnalyzerSettings`  
_L60-62_
- inherits: `IAnalyzerSettings,FLKFSAnalyzerSettings`
- desc: Contains settings for loudness analyzer.

#### class `Audio::FLKFSAnalyzerResult`  
`class FLKFSAnalyzerResult : public IAnalyzerResult`  
_L66-88_
- inherits: `IAnalyzerResult`
- desc: FLKFSResult contains the temporal evolution of loudness.
- L70 _public member_ `inline static const int32 ChannelIndexOverall = -1;` — Denotes the overall loudness channel index as opposed individual channel indices.
- L72 _public prototype_ `FLKFSAnalyzerResult() = default;`
- L75 _public prototype_ `int32 GetNumChannels() const;` — The number of individual channels available in the result.
- L78 _public prototype_ `void Add(FLKFSResults InResults);` — Add to the result.
- L81 _public prototype_ `const TArray<FLKFSResults>& GetChannelLoudnessResults(int32 ChannelIdx) const;` — Returns const reference to FLKFSResults array for individual channel.
- L84 _public prototype_ `const TArray<FLKFSResults>& GetLoudnessResults() const;` — Returns const reference to FLKFSResults array associated with overall loudness.
- L87 _private member_ `TSortedMap<int32, TArray<FLKFSResults>> ChannelResults;`

#### class `Audio::FLKFSWorker`  
`class FLKFSWorker : public IAnalyzerWorker`  
_L93-107_
- inherits: `IAnalyzerWorker`
- desc: FLKFSWorker performs loudness analysis on input sample buffers.
- L97 _public prototype_ `FLKFSWorker(const FAnalyzerParameters& InParams, const FLKFSSettings& InAnalyzerSettings);` — Construct a worker
- L102 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerResult* OutResult) override;` — Analyzes input sample buffer and updates result.
- L105 _private member_ `int32 NumChannels = 0;`
- L106 _private member_ `FLKFSAnalyzer LKFSAnalyzer;`

#### class `Audio::FLKFSFactory`  
`class FLKFSFactory : public IAnalyzerFactory`  
_L112-127_
- inherits: `IAnalyzerFactory`
- desc: Defines the LKFS analyzer and creates related classes.
- L117 _public prototype_ `virtual FName GetName() const override;` — Name of specific analyzer type.
- L120 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of analyzer.
- L123 _public prototype_ `virtual TUniquePtr<IAnalyzerResult> NewResult() const override;` — Creates a new FLKFSAnalyzerResult
- L126 _public prototype_ `virtual TUniquePtr<IAnalyzerWorker> NewWorker(const FAnalyzerParameters& InParams, const IAnalyzerSettings* InSettings) const override;` — Creates a new FLKFSWorker. This expects IAnalyzerSettings to be a valid pointer to a FLKFSSettings object.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`
- L55 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/LKFSNRTFactory.h` (Public)


#### struct `FLKFSNRTResults`  
`struct FLKFSNRTResults`  
_L17-41_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data representing the instantaneous loudness of a audio.
- L24 _public member_ `int32 Channel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The audio channel index which produced this result. If -1, then the data was produced by combining all other audio channels
- L28 _public member_ `float Timestamp = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — Time in seconds of the source audio which corresponds to the loudness measurements.
- L32 _public member_ `float Energy = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The instantaneous, perceptually weighted energy.
- L36 _public member_ `float Loudness = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The instantaneous, perceptually weighted loudness.
- L40 _public member_ `float ShortTermLoudness = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The average loudness over a short term window of time.

#### struct `FLKFSNRTAggregateStats`  
`struct FLKFSNRTAggregateStats`  
_L45-58_
- reflection: `USTRUCT(BlueprintType)`
- desc: The loudness data associated with an entire file.
- L49 _public member_ `static constexpr float InvalidLoudness = TNumericLimits<float>::Min();`
- L53 _public member_ `float IntegratedLoudness = InvalidLoudness;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The average loudness over the entire sound.
- L57 _public member_ `float GatedLoudness = InvalidLoudness;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AudioAnalyzer)` — The gated loudness aggregated over the entire sound.

#### struct `FLKFSNRTChannelData`  
`struct FLKFSNRTChannelData`  
_L61-73_
- reflection: `USTRUCT()`
- L66 _public member_ `FLKFSNRTAggregateStats AggregateStats;` — `UPROPERTY()`
- L69 _public member_ `TArray<FLKFSNRTResults> LoudnessArray;` — `UPROPERTY()`
- L72 _public member_ `FFloatInterval LoudnessInterval;` — `UPROPERTY()`

#### struct `FLKFSNRTWaveData`  
`struct FLKFSNRTWaveData`  
_L76-88_
- reflection: `USTRUCT()`
- L81 _public member_ `bool bIsSortedChronologically = false;` — `UPROPERTY()`
- L84 _public member_ `float DurationInSeconds = 0.f;` — `UPROPERTY()`
- L87 _public member_ `TMap<int32, FLKFSNRTChannelData> ChannelData;` — `UPROPERTY()`

#### class `Audio::FLKFSNRTSettings`  
`class FLKFSNRTSettings : public IAnalyzerNRTSettings`  
_L95-117_
- inherits: `IAnalyzerNRTSettings`
- desc: Contains settings for loudness analyzer.
- L98 _public member_ `static constexpr float DefaultShortTermLoudnessDuration = 3.f;`
- L100 _public member_ `FLoudnessAnalyzerSettings LoudnessAnalyzerSettings = { .FFTSize = 4096, .WindowType = EWindowType::None, .LoudnessCurveType = ELoudnessCurveType::K, .MinAnalysisFrequency = 20.f, .MaxAnalysisFrequency = 24000.f, .ScalingMethod = ELoudnessAnalyzerScalingMethod::Corrected };`
- L110 _public member_ `float AnalysisPeriod = 0.1f;` — Number of seconds between loudness measurements
- L113 _public member_ `float AnalysisWindowDuration = 0.4f;` — Number of seconds of audio analyzed for each loudness measurements
- L116 _public member_ `float ShortTermLoudnessDuration = DefaultShortTermLoudnessDuration;` — Duration of audio analyzed for short term loudness.

#### class `Audio::FLKFSNRTResult`  
`class FLKFSNRTResult : public IAnalyzerNRTResult`  
_L121-176_
- inherits: `IAnalyzerNRTResult`
- desc: FLKFSNRTResult contains the temporal evolution of loudness.
- L125 _public member_ `static const int32 ChannelIndexOverall;` — Denotes the overall loudness channel index as opposed individual channel indices.
- L127 _public prototype_ `FLKFSNRTResult();`
- L130 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — Defines how to serialize result.
- L133 _public prototype_ `void AddChannel(int32 InChannelIndex);` — Initialize a channel if it does not already exist.
- L136 _public prototype_ `void Add(const FLKFSNRTResults& InDatum);` — Appends an FLKFSNRTResults to the container.
- L139 _public prototype_ `bool ContainsChannel(int32 InChannelIndex) const;` — Returns true if this object data for the given channel index
- L142 _public prototype_ `TArrayView<const FLKFSNRTResults> GetChannelLoudnessArray(int32 ChannelIdx) const;` — Returns const reference to FLKFSNRTResults array for individual channel.
- L148 _public prototype_ `TArrayView<FLKFSNRTResults> GetMutableChannelLoudnessArray(int32 ChannelIdx);` — Returns array view to FLKFSNRTResults array for individual channel. If a caller modifies the timestamps of data, they may need to resort the data by calling SortChronologically().
- L151 _public prototype_ `TArrayView<const FLKFSNRTResults> GetLoudnessArray() const;` — Returns const reference to FLKFSNRTResults array associated with overall loudness.
- L154 _public prototype_ `const FLKFSNRTAggregateStats* FindAggregateLoudnessStats(int32 InChannelIdx) const;` — Return the aggregate stats associated with a specific channel
- L157 _public prototype_ `void SetAggregateLoudnessStats(int32 InChannelIdx, FLKFSNRTAggregateStats InStats);` — Sets the aggregated loudness stats for a given channel
- L160 _public prototype_ `void GetChannels(TArray<int32>& OutChannels) const;` — Returns the channel indices available in result.
- L163 _public prototype_ `virtual float GetDurationInSeconds() const override;` — Gets the duration of the analyzed audio.
- L166 _public prototype_ `void SetDurationInSeconds(float InDuration);` — Sets the duration of the analyzed audio.
- L169 _public prototype_ `bool IsSortedChronologically() const;` — Returns true if FLKFSNRTResults arrays are sorted in chronologically ascending order via their timestamp.
- L172 _public prototype_ `void SortChronologically();` — Sorts FLKFSNRTResults arrays in chronologically ascending order via their timestamp.
- L175 _private member_ `FLKFSNRTWaveData Data;`

#### class `Audio::FLKFSNRTWorker`  
`class FLKFSNRTWorker : public IAnalyzerNRTWorker`  
_L181-220_
- inherits: `IAnalyzerNRTWorker`
- desc: FLKFSNRTWorker performs loudness analysis on input sample buffers.
- L185 _public prototype_ `FLKFSNRTWorker(const FAnalyzerNRTParameters& InParams, const FLKFSNRTSettings& InAnalyzerSettings);` — Construct a worker
- L190 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerNRTResult* OutResult) override;` — Analyzes input sample buffer and updates result.
- L195 _public prototype_ `virtual void Finalize(IAnalyzerNRTResult* OutResult) override;` — Call when all audio data has been analyzed.
- L200 _private prototype_ `void AnalyzeSlidingWindow(TAutoSlidingWindow<float>& InSlidingWindow, FLKFSNRTResult& OutResult);`
- L201 _private prototype_ `void AnalyzeWindow(TArrayView<const float> InWindow, FLKFSNRTResult& OutResult);`
- L203 _private prototype_ `void AddCurrentLoudnessDataToResult(FLKFSNRTResult& OutResult);`
- L204 _private prototype_ `void CalculateAggregateLoudnessStats(FLKFSNRTResult& InOutResult) const;`
- L205 _private prototype_ `void FinalizeChannels(FLKFSNRTResult& OutResult);`
- L207 _private member_ `int32 NumChannels = 0;`
- L208 _private member_ `int32 NumAnalyzedBuffers = 0;`
- L209 _private member_ `int32 NumSlidingWindowHopFrames = 0;`
- L210 _private member_ `int32 NumFrames = 0;`
- L211 _private member_ `float SampleRate = 0.f;`
- L212 _private member_ `float ShortTermLoudnessDuration = 0.f;`
- L213 _private member_ `int32 NumAnalysisHopWindows = 1;`
- L214 _private member_ `int32 NumAnalysisWindows = 1;`
- L215 _private member_ `TArray<float> ChannelPerceptualEnergy;`
- L216 _private member_ `TArray<float> OverallPerceptualEnergy;`
- L217 _private member_ `TArray<float> InternalWindow;`
- L218 _private member_ `TUniquePtr<TSlidingBuffer<float>> InternalBuffer;`
- L219 _private member_ `TUniquePtr<FMultichannelLoudnessAnalyzer> Analyzer;`

#### class `Audio::FLKFSNRTFactory`  
`class FLKFSNRTFactory : public IAnalyzerNRTFactory`  
_L225-240_
- inherits: `IAnalyzerNRTFactory`
- desc: Defines the LKFSNRT analyzer and creates related classes.
- L230 _public prototype_ `virtual FName GetName() const override;` — Name of specific analyzer type.
- L233 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of analyzer.
- L236 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTResult> NewResult() const override;` — Creates a new FLKFSNRTResult
- L239 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTWorker> NewWorker(const FAnalyzerNRTParameters& InParams, const IAnalyzerNRTSettings* InSettings) const override;` — Creates a new FLKFSNRTWorker. This expects IAnalyzerNRTSettings to be a valid pointer to a FLKFSNRTSettings object.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Audio`
- L90 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/LoudnessAnalyzer.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/LoudnessFactory.h` (Public)


#### class `Audio::FLoudnessSettings`  
`class FLoudnessSettings : public IAnalyzerSettings, public FLoudnessAnalyzerSettings`  
_L15-20_
- inherits: `IAnalyzerSettings,FLoudnessAnalyzerSettings`
- desc: Contains settings for loudness analyzer.
- L19 _public member_ `float AnalysisPeriod = 0.01f;` — Number of seconds between loudness measurements

#### struct `Audio::FLoudnessEntry`  
`struct FLoudnessEntry`  
_L25-31_
- desc: Holds the loudness values per a time step.
- L27 _public member_ `int32 Channel = 0;`
- L28 _public member_ `float Timestamp = 0.f;`
- L29 _public member_ `float Energy = 0.f;`
- L30 _public member_ `float Loudness = 0.f;`

#### class `Audio::FLoudnessResult`  
`class FLoudnessResult : public IAnalyzerResult`  
_L36-60_
- inherits: `IAnalyzerResult`
- desc: FLoudnessResult contains the temporal evolution of loudness for the last buffer of audio analyzed.
- L42 _public member_ `static const int32 ChannelIndexOverall;` — Denotes the overall loudness as opposed individual channel indices.
- L44 _public function_ `FLoudnessResult()`
- L47 _public prototype_ `void Add(const FLoudnessEntry& InDatum);` — Appends an FLoudnessDatum to the container.
- L50 _public prototype_ `const TArray<FLoudnessEntry>& GetChannelLoudnessArray(int32 ChannelIdx) const;` — Returns const reference to FLoudnessDatum array for individual channel.
- L53 _public prototype_ `const TArray<FLoudnessEntry>& GetLoudnessArray() const;` — Returns const reference to FLoudnessDatum array associated with overall loudness.
- L56 _public prototype_ `int32 GetNumChannels() const;` — Returns the number of channels.
- L59 _private member_ `TMap<int32, TArray<FLoudnessEntry> > ChannelLoudnessArrays;`

#### class `Audio::FLoudnessWorker`  
`class FLoudnessWorker : public IAnalyzerWorker`  
_L65-86_
- inherits: `IAnalyzerWorker`
- desc: FLoudnessWorker performs loudness analysis on input sample buffers.
- L69 _public prototype_ `FLoudnessWorker(const FAnalyzerParameters& InParams, const FLoudnessSettings& InAnalyzerSettings);` — Construct a worker
- L72 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerResult* OutResult) override;` — Analyzes input sample buffer and updates result.
- L77 _private prototype_ `void AnalyzeWindow(TArrayView<const float> InWindow, FLoudnessResult& OutResult);` — Analyze a single window.
- L79 _private member_ `int32 NumChannels = 0;`
- L80 _private member_ `int32 NumAnalyzedBuffers = 0;`
- L81 _private member_ `int32 NumHopFrames = 0;`
- L82 _private member_ `int32 SampleRate = 0;`
- L83 _private member_ `TArray<float> InternalWindow;`
- L84 _private member_ `TUniquePtr<TSlidingBuffer<float>> InternalBuffer;`
- L85 _private member_ `TUniquePtr<FMultichannelLoudnessAnalyzer> Analyzer;`

#### class `Audio::FLoudnessFactory`  
`class FLoudnessFactory : public IAnalyzerFactory`  
_L91-106_
- inherits: `IAnalyzerFactory`
- desc: Defines the Loudness analyzer and creates related classes.
- L96 _public prototype_ `virtual FName GetName() const override;` — Name of specific analyzer type.
- L99 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of analyzer.
- L102 _public prototype_ `virtual TUniquePtr<IAnalyzerResult> NewResult() const override;` — Creates a new FLoudnessNRTResult
- L105 _public prototype_ `virtual TUniquePtr<IAnalyzerWorker> NewWorker(const FAnalyzerParameters& InParams, const IAnalyzerSettings* InSettings) const override;` — Creates a new FLoudnessWorker. This expects IAnalyzerNRTSettings to be a valid pointer to a FLoudnessSettings object.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L10 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/LoudnessNRTFactory.h` (Public)


#### class `Audio::FLoudnessNRTSettings`  
`class FLoudnessNRTSettings : public IAnalyzerNRTSettings, public FLoudnessAnalyzerSettings`  
_L15-24_
- inherits: `IAnalyzerNRTSettings,FLoudnessAnalyzerSettings`
- desc: Contains settings for loudness analyzer.
- L19 _public member_ `float AnalysisPeriod;` — Number of seconds between loudness measurements
- L21 _public function_ `FLoudnessNRTSettings() : AnalysisPeriod(0.01f)`

#### struct `Audio::FLoudnessDatum`  
`struct FLoudnessDatum`  
_L30-36_
- desc: Holds the loudness values per a time step.
- L32 _public member_ `int32 Channel = 0;`
- L33 _public member_ `float Timestamp = 0.f;`
- L34 _public member_ `float Energy = 0.f;`
- L35 _public member_ `float Loudness = 0.f;`

#### class `Audio::FLoudnessNRTResult`  
`class FLoudnessNRTResult : public IAnalyzerNRTResult`  
_L42-91_
- inherits: `IAnalyzerNRTResult`
- desc: FLoudnessNRTResult contains the temporal evolution of loudness.
- L46 _public member_ `static const int32 ChannelIndexOverall;` — Denotes the overall loudness channel index as opposed individual channel indices.
- L48 _public prototype_ `FLoudnessNRTResult();`
- L51 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — Defines how to serialize result.
- L54 _public prototype_ `void Add(const FLoudnessDatum& InDatum);` — Appends an FLoudnessDatum to the container.
- L57 _public prototype_ `bool ContainsChannel(int32 InChannelIndex) const;` — Returns true if this object data for the given channel index
- L60 _public prototype_ `const TArray<FLoudnessDatum>& GetChannelLoudnessArray(int32 ChannelIdx) const;` — Returns const reference to FLoudnessDatum array for individual channel.
- L63 _public prototype_ `const TArray<FLoudnessDatum>& GetLoudnessArray() const;` — Returns const reference to FLoudnessDatum array associated with overall loudness.
- L66 _public prototype_ `float GetLoudnessRange(float InNoiseFloor) const;` — Returns range in dB of overall loudness result given the noise floor.
- L69 _public prototype_ `float GetChannelLoudnessRange(int32 InChannelIdx, float InNoiseFloor) const;` — Returns range in dB of loudness result given the noise floor.
- L72 _public prototype_ `void GetChannels(TArray<int32>& OutChannels) const;` — Returns the channel indices available in result.
- L75 _public prototype_ `virtual float GetDurationInSeconds() const override;` — Gets the duration of the analyzed audio.
- L78 _public prototype_ `void SetDurationInSeconds(float InDuration);` — Sets the duration of the analyzed audio.
- L81 _public prototype_ `bool IsSortedChronologically() const;` — Returns true if FLoudnessDatum arrays are sorted in chronologically ascending order via their timestamp.
- L84 _public prototype_ `void SortChronologically();` — Sorts FLoudnessDatum arrays in chronologically ascending order via their timestamp.
- L87 _private member_ `float DurationInSeconds;`
- L88 _private member_ `TMap<int32, TArray<FLoudnessDatum> > ChannelLoudnessArrays;`
- L89 _private member_ `TMap<int32, FFloatInterval> ChannelLoudnessIntervals;`
- L90 _private member_ `bool bIsSortedChronologically;`

#### class `Audio::FLoudnessNRTWorker`  
`class FLoudnessNRTWorker : public IAnalyzerNRTWorker`  
_L96-125_
- inherits: `IAnalyzerNRTWorker`
- desc: FLoudnessNRTWorker performs loudness analysis on input sample buffers.
- L100 _public prototype_ `FLoudnessNRTWorker(const FAnalyzerNRTParameters& InParams, const FLoudnessNRTSettings& InAnalyzerSettings);` — Construct a worker
- L105 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerNRTResult* OutResult) override;` — Analyzes input sample buffer and updates result.
- L110 _public prototype_ `virtual void Finalize(IAnalyzerNRTResult* OutResult) override;` — Call when all audio data has been analyzed.
- L115 _private prototype_ `void AnalyzeWindow(TArrayView<const float> InWindow, FLoudnessNRTResult& OutResult);` — Analyze a single window
- L117 _private member_ `int32 NumChannels;`
- L118 _private member_ `int32 NumAnalyzedBuffers;`
- L119 _private member_ `int32 NumHopFrames;`
- L120 _private member_ `int32 NumFrames;`
- L121 _private member_ `float SampleRate;`
- L122 _private member_ `TArray<float> InternalWindow;`
- L123 _private member_ `TUniquePtr<TSlidingBuffer<float>> InternalBuffer;`
- L124 _private member_ `TUniquePtr<FMultichannelLoudnessAnalyzer> Analyzer;`

#### class `Audio::FLoudnessNRTFactory`  
`class FLoudnessNRTFactory : public IAnalyzerNRTFactory`  
_L130-145_
- inherits: `IAnalyzerNRTFactory`
- desc: Defines the LoudnessNRT analyzer and creates related classes.
- L135 _public prototype_ `virtual FName GetName() const override;` — Name of specific analyzer type.
- L138 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of analyzer.
- L141 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTResult> NewResult() const override;` — Creates a new FLoudnessNRTResult
- L144 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTWorker> NewWorker(const FAnalyzerNRTParameters& InParams, const IAnalyzerNRTSettings* InSettings) const override;` — Creates a new FLoudnessNRTWorker. This expects IAnalyzerNRTSettings to be a valid pointer to a FLoudnessNRTSettings object.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L10 _namespace_ `namespace Audio`
- L39 _prototype_ `FArchive &operator <<(FArchive& Ar, FLoudnessDatum& Datum);` (scope `Audio`) — De/Serialize single loudness datum into archive.

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/MaxStrengthPitchTracker.h` (Public)


#### struct `Audio::FMaxStrengthPitchTrackerSettings`  
`struct FMaxStrengthPitchTrackerSettings`  
_L13-20_
- desc: Settings for FMaxStrengthPitchTracker
- L16 _public member_ `float MinimumStrength = 0.1f;` — Minimum strength of pitch to be included in pitch track.
- L19 _public member_ `float MaximumFrequencyRatioDeviation = 0.05f;` — Maximum deviation of ratio between two freuqencies to consider them part of the same pitch track.

#### class `Audio::FMaxStrengthPitchTracker`  
`class FMaxStrengthPitchTracker : public IPitchTracker`  
_L23-42_
- inherits: `IPitchTracker`
- desc: Track the maximum strength pitch.
- L27 _public prototype_ `FMaxStrengthPitchTracker(const FMaxStrengthPitchTrackerSettings& InSettings, TUniquePtr<IPitchDetector> InDetector);` — Constructor accepts settings and a unique pointer to the pitch detector.
- L29 _public prototype_ `virtual ~FMaxStrengthPitchTracker();`
- L32 _public prototype_ `virtual void TrackPitches(const FAlignedFloatBuffer& InMonoAudio, TArray<FPitchTrackInfo>& OutPitchTracks) override;` — Append pitch tracks to processed audio.
- L35 _public prototype_ `virtual void Finalize(TArray<FPitchTrackInfo>& OutPitchTracks) override;` — Call when all audio has been processed. Appends pitch tracks to OutPitchTracks.
- L38 _private member_ `FMaxStrengthPitchTrackerSettings Settings;`
- L39 _private member_ `TUniquePtr<IPitchDetector> PitchDetector;`
- L41 _private member_ `TArray<FPitchInfo> Observations;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L10 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/MeterAnalyzer.h` (Public)


#### struct `Audio::FMeterAnalyzerSettings`  
`struct FMeterAnalyzerSettings`  
_L11-29_
- L14 _public member_ `EPeakMode::Type MeterPeakMode = EPeakMode::RootMeanSquared;` — Envelope follower mode
- L17 _public member_ `int32 MeterAttackTime = 300;` — Envelope follower attack time in milliseconds
- L20 _public member_ `int32 MeterReleaseTime = 300;` — Envelope follower release time in milliseconds
- L23 _public member_ `int32 PeakHoldTime = 100;` — Peak detector hold time in milliseconds
- L26 _public member_ `float ClippingThreshold = 1.0f;` — The volume threshold to detect clipping
- L28 _public member_ `bool bIsAnalog = true;`

#### struct `Audio::FMeterAnalyzerResults`  
`struct FMeterAnalyzerResults`  
_L32-39_
- desc: Per-channel analyzer results
- L34 _public member_ `float TimeSec = 0.0f;`
- L35 _public member_ `TArray<float> MeterValues;`
- L36 _public member_ `TArray<float> PeakValues;`
- L37 _public member_ `TArray<float> ClippingValues;`
- L38 _public member_ `TArray<int32> NumSamplesClipping;`

#### class `Audio::FMeterAnalyzer`  
`class FMeterAnalyzer`  
_L41-92_
- L46 _public prototype_ `FMeterAnalyzer(float InSampleRate, int32 NumChannels, const FMeterAnalyzerSettings& InSettings);` — Construct analyzer
- L51 _public prototype_ `FMeterAnalyzerResults ProcessAudio(TArrayView<const float> InSampleView);` — Calculate the meter results for the input samples.  Will return the current meter and the current peak value of the analyzer.
- L56 _public prototype_ `const FMeterAnalyzerSettings& GetSettings() const;` — Return const reference to settings used inside this analyzer.
- L60 _protected member_ `FEnvelopeFollower EnvelopeFollower;` — Envelope follower per channel
- L61 _protected member_ `FAlignedFloatBuffer EnvelopeBuffer;`
- L70 _protected member_ `TArray<FClippingData> ClippingDataPerChannel;`
- L84 _protected member_ `TArray<FEnvelopeData> EnvelopeDataPerChannel;` — Per-channel peak data
- L87 _protected member_ `FMeterAnalyzerSettings Settings;`
- L88 _protected member_ `float SampleRate = 0.0f;`
- L89 _protected member_ `int32 NumChannels = 0;`
- L90 _protected member_ `int32 PeakHoldFrames = 0;`
- L91 _protected member_ `int64 FrameCounter = 0;`

#### struct `Audio::FMeterAnalyzer::FClippingData`  
`struct FClippingData`  
_L64-69_
- desc: Per-channel clipping data
- L67 _public member_ `int32 NumSamplesClipping = 0;` — How many samples we've been clipping
- L68 _public member_ `float ClippingValue = 0.0f;`

#### struct `Audio::FMeterAnalyzer::FEnvelopeData`  
`struct FEnvelopeData`  
_L73-82_
- desc: State to track the peak data
- L75 _public member_ `float MaxEnvelopeValue = 0.f;`
- L76 _public member_ `float PeakValue = 0.0f;`
- L77 _public member_ `int32 FramesUntilPeakReset = 0;`
- L80 _public member_ `float PriorEnvelopeValue = 0.f;` — Current slope of the envelope
- L81 _public member_ `bool bPriorEnvelopeSlopeIsPositive = false;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L9 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/MeterFactory.h` (Public)


#### class `Audio::FMeterSettings`  
`class FMeterSettings : public IAnalyzerSettings, public FMeterAnalyzerSettings`  
_L15-20_
- inherits: `IAnalyzerSettings,FMeterAnalyzerSettings`
- desc: Contains settings for meter  analyzer.
- L19 _public member_ `float AnalysisPeriod = 0.01f;` — Number of seconds between loudness measurements

#### struct `Audio::FMeterEntry`  
`struct FMeterEntry`  
_L25-33_
- desc: Holds the meter results per a time step for each channel
- L27 _public member_ `int32 Channel = 0;`
- L28 _public member_ `float Timestamp = 0.0f;`
- L29 _public member_ `float MeterValue = 0.0f;`
- L30 _public member_ `float PeakValue = 0.0f;`
- L31 _public member_ `float ClippingValue = 0.0f;`
- L32 _public member_ `int32 NumSamplesClipping = 0;`

#### class `Audio::FMeterResult`  
`class FMeterResult : public IAnalyzerResult`  
_L38-63_
- inherits: `IAnalyzerResult`
- desc: FMeterResult contains the temporal evolution of loudness for the last buffer of audio analyzed.
- L44 _public member_ `static const int32 ChannelIndexOverall;` — Denotes the overall loudness as opposed individual channel indices.
- L46 _public function_ `FMeterResult()`
- L49 _public prototype_ `void Add(const FMeterEntry& InEntry);` — Appends an FMeterEntry to the container.
- L52 _public prototype_ `const TArray<FMeterEntry>& GetChannelMeterArray(int32 ChannelIdx) const;` — Returns const reference to FMeterEntry array for individual channel.
- L55 _public prototype_ `const TArray<FMeterEntry>& GetMeterArray() const;` — Returns const reference to FMeterEntry array associated with overall loudness.
- L58 _public prototype_ `int32 GetNumChannels() const;` — Returns the number of channels.
- L61 _private member_ `float DurationInSeconds = 0.0f;`
- L62 _private member_ `TMap<int32, TArray<FMeterEntry> > ChannelMeterArrays;`

#### class `Audio::FMeterWorker`  
`class FMeterWorker : public IAnalyzerWorker`  
_L68-86_
- inherits: `IAnalyzerWorker`
- desc: FMeterWorker performs meter analysis on input sample buffers.
- L72 _public prototype_ `FMeterWorker(const FAnalyzerParameters& InParams, const FMeterSettings& InAnalyzerSettings);` — Construct a worker
- L75 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerResult* OutResult) override;` — Analyzes input sample buffer and updates result.
- L79 _private member_ `int32 NumChannels = 0;`
- L80 _private member_ `int32 NumAnalyzedBuffers = 0;`
- L81 _private member_ `int32 NumHopFrames = 0;`
- L82 _private member_ `int32 SampleRate = 0;`
- L83 _private member_ `TArray<float> InternalWindow;`
- L84 _private member_ `TUniquePtr<TSlidingBuffer<float>> InternalBuffer;`
- L85 _private member_ `TUniquePtr<FMeterAnalyzer> MeterAnalyzer;`

#### class `Audio::FMeterFactory`  
`class FMeterFactory : public IAnalyzerFactory`  
_L91-105_
- inherits: `IAnalyzerFactory`
- desc: Defines the meter analyzer and creates related classes.
- L95 _public prototype_ `virtual FName GetName() const override;` — Name of specific analyzer type.
- L98 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of analyzer.
- L101 _public prototype_ `virtual TUniquePtr<IAnalyzerResult> NewResult() const override;` — Creates a new FLoudnessNRTResult
- L104 _public prototype_ `virtual TUniquePtr<IAnalyzerWorker> NewWorker(const FAnalyzerParameters& InParams, const IAnalyzerSettings* InSettings) const override;` — Creates a new FLoudnessWorker. This expects IAnalyzerNRTSettings to be a valid pointer to a FLoudnessSettings object.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L10 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/OnsetAnalyzer.h` (Public)


#### struct `Audio::FOnsetStrengthSettings`  
`struct FOnsetStrengthSettings`  
_L17-39_
- desc: Onset strength settings
- L20 _public member_ `int32 NumHopFrames = 1024;` — Number of frames between strength windows
- L23 _public member_ `int32 NumWindowFrames = 4096;` — Number of frames used to represent one audio window
- L26 _public member_ `int32 ComparisonLag = 4;` — Number of windows to lag when calculating window difference.
- L29 _public member_ `int32 FFTSize = 4096;` — Size of FFT. Must be greater than or equal to NumWindowFrames.
- L32 _public member_ `EWindowType WindowType = EWindowType::Blackman;` — Type of analysis window to apply to audio.
- L35 _public member_ `float NoiseFloorDb = -60.f;` — Decibel level considered to be silence.
- L38 _public member_ `FMelSpectrumKernelSettings MelSettings;` — Settings for converting FFT to mel spectrum.

#### class `Audio::FOnsetStrengthAnalyzer`  
`class FOnsetStrengthAnalyzer`  
_L52-95_
- desc: FOnsetStrengthAnalyzer FOnsetStrengthAnalyzer calculates the onset strength from audio. Onset strength is calculated as the half wave rectificed difference between two spectral frames. This onset strength onset analyzer uses the following approach. [audio]->[fft]->[mel spectrum]->[diff]->[half wave rectify]->[mean]->[onset strength] |           | >-[lag]-----|
- L55 _public prototype_ `FOnsetStrengthAnalyzer(const FOnsetStrengthSettings& InSettings, float InSampleRate);`
- L58 _public prototype_ `void CalculateOnsetStrengths(TArrayView<const float> InSamples, TArray<float>& OutOnsetStrengths);` — Calculates onset strengths from audio and fills OutOnsetStrengths with generated onset strengths
- L61 _public prototype_ `void FlushAudio(TArray<float>& OutEnvelopeStrengths);` — Call when done processing audio for an audio analyzer
- L64 _public prototype_ `void Reset();` — Call to reset internal counters and lag spectra.
- L67 _public prototype_ `static float GetTimestampForIndex(const FOnsetStrengthSettings& InSettings, float InSampleRate, int32 InIndex);` — Converts an onset strength index into a timestamp.
- L71 _private prototype_ `void AnalyzeAudio(TArrayView<const float> InSamples, TArray<float>& OutEnvelopeStrengths, bool bDoFlush = false);`
- L74 _private prototype_ `float GetNextOnsetStrength(TArrayView<const float> InSamples);` — Processes single audio window
- L76 _private member_ `FOnsetStrengthSettings Settings;`
- L77 _private member_ `int32 LagSpectraIndex;`
- L78 _private member_ `int32 ActualFFTSize;`
- L80 _private member_ `TSlidingBuffer<float> SlidingBuffer;`
- L81 _private member_ `FAlignedFloatBuffer WorkingBuffer;`
- L82 _private member_ `FAlignedFloatBuffer WindowedSamples;`
- L83 _private member_ `FAlignedFloatBuffer ComplexSpectrum;`
- L84 _private member_ `FAlignedFloatBuffer RealSpectrum;`
- L87 _private member_ `TArray<FAlignedFloatBuffer> PreviousMelSpectra;` — Array of arrays to hold lag spectra.
- L89 _private member_ `TArray<float> MelSpectrum;`
- L90 _private member_ `TArray<float> MelSpectrumDifference;`
- L92 _private member_ `FWindow Window;`
- L93 _private member_ `TUniquePtr<FContiguousSparse2DKernelTransform> MelTransform;`
- L94 _private member_ `TUniquePtr<IFFTAlgorithm> FFT;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L11 _namespace_ `namespace Audio`
- L12 _namespace_ `namespace Audio`
- L14 _namespace_ `namespace Audio`
- L104 _prototype_ `void OnsetExtractIndices(const FPeakPickerSettings& InSettings, TArrayView<const float> InOnsetEnvelope, TArray<int32>& OutOnsetIndices);` (scope `Audio`) — Extract onset indicies from an onset strength envelope. InSettings is the peak picker settings used to pick onset peaks from an onset strength envelope. InOnsetEnvelop is an onset strength envelope generated using the FOnsetStrengthAnalyzer. OutOnsetIndices contains the indices where onsets occur.
- L110 _prototype_ `void OnsetBacktrackIndices(TArrayView<const float> InOnsetEnvelope, TArrayView<const int32> InOnsetIndices, TArray<int32>& OutBacktrackedOnsetIndices);` (scope `Audio`) — Backtracks onset indices to the beginning of the onset attack. This is useful when generating splice points which retain the onset attack.

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/OnsetNRTFactory.h` (Public)


#### class `Audio::FOnsetNRTSettings`  
`class FOnsetNRTSettings : public IAnalyzerNRTSettings`  
_L19-37_
- inherits: `IAnalyzerNRTSettings`
- desc: FOnsetNRTSettings Settings for the Constant Q Non-Real-Time Factory.
- L23 _public member_ `FOnsetStrengthSettings OnsetStrengthSettings;`
- L25 _public member_ `FPeakPickerSettings PeakPickerSettings;`
- L32 _public member_ `bool bDownmixToMono;` — If true, all channels are mixed together with equal power before analysis. Only one channel is produced at channel index 0. If false, then each channel is analyzed separately.
- L34 _public function_ `FOnsetNRTSettings() : bDownmixToMono(false)`

#### struct `Audio::FOnset`  
`struct FOnset`  
_L44-65_
- desc: FOnset Contains data relating to one onset.
- L47 _public member_ `int32 Channel;` — Audio channel which produced the data.
- L50 _public member_ `float Timestamp;` — Timestamp in seconds referring to the center of the audio window.
- L52 _public member_ `float Strength;`
- L54 _public function_ `FOnset() : Channel(0) , Timestamp(0.f) , Strength(0.f)`
- L60 _public function_ `FOnset(int32 InChannelIndex, float InTimestamp, float InStrength) : Channel(InChannelIndex) , Timestamp(InTimestamp) , Strength(InStrength)`

#### class `Audio::FOnsetNRTResult`  
`class FOnsetNRTResult : public IAnalyzerNRTResult`  
_L74-122_
- inherits: `IAnalyzerNRTResult`
- desc: FOnsetNRTResult FOnsetNRTResult is a container for the output of the FOnsetNRTWorker.
- L78 _public prototype_ `FOnsetNRTResult();`
- L81 _public prototype_ `virtual void Serialize(FArchive& Archive) override;` — Serialize or unserialize object
- L84 _public prototype_ `void AddOnset(int32 InChannelIndex, float InTimestamp, float InStrength);` — Add a single frame of CQT data
- L87 _public prototype_ `void AddChannel(int32 InChannelIndex);` — Adds an empty channel. Useful if a channel exists without any onsets.
- L90 _public prototype_ `bool ContainsChannel(int32 InChannelIndex) const;` — Returns true if this result contains the channel index.
- L93 _public prototype_ `const TArray<FOnset>& GetOnsetsForChannel(int32 InChannelIndex) const;` — Retrieve the array of frames for a single channel of audio.
- L96 _public prototype_ `FFloatInterval GetChannelOnsetInterval(int32 InChannelIdx) const;` — Retrieve the interval of the maximum and minimum strengths of all onsets in channel.
- L99 _public prototype_ `void GetChannels(TArray<int32>& OutChannels) const;` — Retrieve the channels available in the result.
- L102 _public prototype_ `virtual float GetDurationInSeconds() const override;` — Returns the duration of the analyzed audio in seconds
- L105 _public prototype_ `void SetDurationInSeconds(float InDuration);` — Sets the duration of the analyzed audio in seconds
- L108 _public prototype_ `bool IsSortedChronologically() const;` — Returns true if FOnset arrays are sorted in chronologically ascending order via their timestamp.
- L111 _public prototype_ `void SortChronologically();` — Sorts FOnset arrays in chronologically ascnding order via their timestamp.
- L115 _private member_ `float DurationInSeconds;`
- L117 _private member_ `TMap<int32, TArray<FOnset> > ChannelOnsets;`
- L119 _private member_ `TMap<int32, FFloatInterval> ChannelOnsetStrengthIntervals;`
- L121 _private member_ `bool bIsSortedChronologically;`

#### class `Audio::FOnsetNRTWorker`  
`class FOnsetNRTWorker : public IAnalyzerNRTWorker`  
_L128-184_
- inherits: `IAnalyzerNRTWorker`
- desc: FOnsetNRTWorker FOnsetNRTWorker computes a FOnsetNRTResult from audio samples.
- L137 _public prototype_ `FOnsetNRTWorker(const FAnalyzerNRTParameters& InParams, const FOnsetNRTSettings& InAnalyzerSettings);` — Constructor InParams are the parameters which describe characteristics of the input audio. InAnalyzerSettings are the settings which control various aspects of the algorithm.
- L145 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerNRTResult* OutResult) override;` — Analyze audio and put results into results pointer. InAudio is an array view of audio. OutResult is a pointer to a valid FOnsetNRTResult
- L152 _public prototype_ `virtual void Finalize(IAnalyzerNRTResult* OutResult) override;` — Call when analysis of audio asset is complete. OutResult must be a pointer to a valid FOnsetNRTResult.
- L157 _private prototype_ `void AnalyzeMultichannel(TArrayView<const float> InAudio, IAnalyzerNRTResult* OutResult, bool bDoFlush);` — Analyze audio with multiple channels interleaved.
- L159 _private prototype_ `void AnalyzeWindow(const FAlignedFloatBuffer& InWindow, int32 InChannelIndex, FOnsetNRTResult& OutResult);`
- L161 _private prototype_ `void ExtractOnsetsFromOnsetStrengths(FOnsetNRTResult& OutResult);`
- L163 _private prototype_ `void Reset();`
- L165 _private member_ `FOnsetNRTSettings Settings;`
- L167 _private member_ `int32 NumFrames;`
- L168 _private member_ `int32 NumChannels;`
- L169 _private member_ `float SampleRate;`
- L170 _private member_ `int32 NumWindowFrames;`
- L171 _private member_ `int32 NumWindowSamples;`
- L172 _private member_ `float MonoScaling;`
- L174 _private member_ `FAlignedFloatBuffer HopBuffer;`
- L175 _private member_ `FAlignedFloatBuffer ChannelBuffer;`
- L176 _private member_ `FAlignedFloatBuffer MonoBuffer;`
- L178 _private member_ `TUniquePtr<TSlidingBuffer<float> > SlidingBuffer;`
- L180 _private member_ `TArray< TUniquePtr<FOnsetStrengthAnalyzer> > OnsetStrengthAnalyzers;`
- L182 _private member_ `TArray< TArray<float> > OnsetStrengths;`

#### class `Audio::FOnsetNRTFactory`  
`class FOnsetNRTFactory : public IAnalyzerNRTFactory`  
_L190-208_
- inherits: `IAnalyzerNRTFactory`
- desc: FOnsetNRTFactory Factory for creating FOnsetNRT workers and results
- L195 _public prototype_ `virtual FName GetName() const override;` — Name of this analyzer type.
- L198 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of this analyzer.
- L201 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTResult> NewResult() const override;` — Create a new FOnsetNRTResult.
- L207 _public prototype_ `virtual TUniquePtr<IAnalyzerNRTWorker> NewWorker(const FAnalyzerNRTParameters& InParams, const IAnalyzerNRTSettings* InSettings) const override;` — Create a new FOnsetNRTWorker InSettings must be a pointer to FOnsetNRTSetting

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L11 _namespace_ `namespace Audio`
- L13 _namespace_ `namespace Audio`
- L68 _prototype_ `FArchive &operator <<(FArchive& Ar, FOnset& Frame);` (scope `Audio`) — Serialize FOnset

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/PeakPicker.h` (Public)


#### struct `Audio::FPeakPickerSettings`  
`struct FPeakPickerSettings`  
_L11-19_
- L13 _public member_ `int32 NumPreMax = 1440;`
- L14 _public member_ `int32 NumPostMax = 1;`
- L15 _public member_ `int32 NumPreMean = 4800;`
- L16 _public member_ `int32 NumPostMean = 4801;`
- L17 _public member_ `int32 NumWait = 1440;`
- L18 _public member_ `float MeanDelta = 0.07f;`

#### class `Audio::FPeakPicker`  
`class FPeakPicker`  
_L21-32_
- L24 _public prototype_ `FPeakPicker(const FPeakPickerSettings& InSettings);`
- L26 _public prototype_ `void PickPeaks(TArrayView<const float> InView, TArray<int32>& OutPeakIndices);`
- L29 _private member_ `FPeakPickerSettings Settings;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L9 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/PitchTracker.h` (Public)


#### struct `Audio::FPitchInfo`  
`struct FPitchInfo`  
_L10-21_
- desc: Contains information about a pitch observation.
- L13 _public member_ `float Frequency = 0.f;` — The frequency (in Hz) of the observed pitch.
- L17 _public member_ `float Strength = 0.f;` — The strength of the pitch.  The exact interpretation of this value will be dependent upon the specific pitch detector.
- L20 _public member_ `double Timestamp = 0.f;` — The timestamp (in seconds) of the pitch observation.

#### class `Audio::IPitchDetector`  
`class IPitchDetector`  
_L28-49_
- desc: Pitch Detector Interface A pitch detector identifies pitch information from a stream of input audio.  The pitch detector should support multiple calls to `DetectPitches(...)` originating from the same audio source.
- L31 _public prototype_ `virtual ~IPitchDetector() = default;`
- L38 _public prototype_ `virtual void DetectPitches(const FAlignedFloatBuffer& InMonoAudio, TArray<FPitchInfo>& OutPitches) = 0;` — Detect pitches from stream of audio. @param InMonoAudio - The most recent input buffer from a stream of audio. @param OutPitches - The pitches detected during this call to `DetectPitches` are appended to this array.
- L48 _public prototype_ `virtual void Finalize(TArray<FPitchInfo>& OutPitches) = 0;` — Mark the end of an audio stream. Pitch detectors which need to know when an audio stream is finished can overload this method to handle the end of an audio stream. @param OutPitches - The pitches detected during this call to `Finalize` are appended to this array.

#### struct `Audio::FPitchTrackInfo`  
`struct FPitchTrackInfo`  
_L52-56_
- desc: Contains information about a pitch track observation.
- L55 _public member_ `TArray<FPitchInfo> Observations;` — The array of observations associated with the pitch track.

#### class `Audio::IPitchTracker`  
`class IPitchTracker`  
_L63-83_
- desc: Pitch Tracker Interface. A pitch tracker idenities multiple pitch tracks from a stream of input audio. The pitch tracker should support multiple calls to `TrackPitches(...)` originating from the same audio source.
- L66 _public prototype_ `virtual ~IPitchTracker() = default;`
- L73 _public prototype_ `virtual void TrackPitches(const FAlignedFloatBuffer& InMonoAudio, TArray<FPitchTrackInfo>& OutPitchTracks) = 0;` — Detect pitche tracks from stream of audio. @param InMonoAudio - The most recent input buffer from a stream of audio. @param OutPitchTracks - The pitch tracks detected during this call to `TrackPitches` are appended to this array.
- L82 _public prototype_ `virtual void Finalize(TArray<FPitchTrackInfo>& OutPitchTracks) = 0;` — Mark the end of an audio stream. Pitch trackers which need to know when an audio stream is finished can overload this method to handle the end of an audio stream. @param OutPitchTracks - The pitch tracks detected during this call to `Finalize` are added to this array.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/SynesthesiaSpectrumAnalysisFactory.h` (Public)


#### class `Audio::FSynesthesiaSpectrumAnalysisSettings`  
`class FSynesthesiaSpectrumAnalysisSettings : public IAnalyzerSettings, public FSynesthesiaSpectrumAnalyzerSettings`  
_L15-20_
- inherits: `IAnalyzerSettings,FSynesthesiaSpectrumAnalyzerSettings`
- desc: Contains settings for Spectrum analyzer.
- L19 _public member_ `float AnalysisPeriod = 0.01f;` — Number of seconds between spectrum measurements

#### struct `Audio::FSynesthesiaSpectrumEntry`  
`struct FSynesthesiaSpectrumEntry`  
_L25-30_
- desc: Holds the spectrum results per a time step for each channel
- L27 _public member_ `int32 Channel = 0;`
- L28 _public member_ `float Timestamp = 0.0f;`
- L29 _public member_ `TArray<float> SpectrumValues;`

#### class `Audio::FSynesthesiaSpectrumResult`  
`class FSynesthesiaSpectrumResult : public IAnalyzerResult`  
_L35-52_
- inherits: `IAnalyzerResult`
- desc: FSynesthesiaSpectrumResult contains the temporal evolution of loudness for the last buffer of audio analyzed.
- L38 _public function_ `FSynesthesiaSpectrumResult()`
- L41 _public prototype_ `void Add(FSynesthesiaSpectrumEntry&& InEntry);` — Appends an FSynesthesiaSpectrumEntry to the container.
- L44 _public prototype_ `const TArray<FSynesthesiaSpectrumEntry>& GetChannelSpectrumArray(int32 ChannelIdx) const;` — Returns const reference to FSynesthesiaSpectrumEntry array for individual channel.
- L47 _public prototype_ `int32 GetNumChannels() const;` — Returns the number of channels.
- L50 _private member_ `float DurationInSeconds = 0.0f;`
- L51 _private member_ `TMap<int32, TArray<FSynesthesiaSpectrumEntry>> ChannelSpectrumArrays;`

#### class `Audio::FSynesthesiaSpectrumAnalysisWorker`  
`class FSynesthesiaSpectrumAnalysisWorker : public IAnalyzerWorker`  
_L57-83_
- inherits: `IAnalyzerWorker`
- desc: FSynesthesiaSpectrumWorker performs Spectrum analysis on input sample buffers.
- L61 _public prototype_ `FSynesthesiaSpectrumAnalysisWorker(const FAnalyzerParameters& InParams, const FSynesthesiaSpectrumAnalysisSettings& InAnalyzerSettings);` — Construct a worker
- L64 _public prototype_ `virtual void Analyze(TArrayView<const float> InAudio, IAnalyzerResult* OutResult) override;` — Analyzes input sample buffer and updates result.
- L68 _private member_ `int32 NumChannels = 0;`
- L69 _private member_ `bool bDownmixToMono = true;`
- L70 _private member_ `int32 NumOutputFrames = 0;`
- L71 _private member_ `int32 NumWindowFrames = 0;`
- L72 _private member_ `int32 NumWindowSamples = 0;`
- L73 _private member_ `int32 NumHopFrames = 0;`
- L74 _private member_ `int32 SampleRate = 0;`
- L75 _private member_ `int64 FrameCounter = 0;`
- L77 _private member_ `FAlignedFloatBuffer MonoBuffer;`
- L78 _private member_ `FAlignedFloatBuffer ChannelBuffer;`
- L80 _private member_ `TArray<float> InternalWindow;`
- L81 _private member_ `TUniquePtr<TSlidingBuffer<float>> InternalBuffer;`
- L82 _private member_ `TUniquePtr<FSynesthesiaSpectrumAnalyzer> SpectrumAnalyzer;`

#### class `Audio::FSynesthesiaSpectrumAnalysisFactory`  
`class FSynesthesiaSpectrumAnalysisFactory : public IAnalyzerFactory`  
_L88-103_
- inherits: `IAnalyzerFactory`
- desc: Defines the Spectrum analyzer and creates related classes.
- L93 _public prototype_ `virtual FName GetName() const override;` — Name of specific analyzer type.
- L96 _public prototype_ `virtual FString GetTitle() const override;` — Human readable name of analyzer.
- L99 _public prototype_ `virtual TUniquePtr<IAnalyzerResult> NewResult() const override;` — Creates a new FSynesthesiaSpectrumResult
- L102 _public prototype_ `virtual TUniquePtr<IAnalyzerWorker> NewWorker(const FAnalyzerParameters& InParams, const IAnalyzerSettings* InSettings) const override;` — Creates a new FSynesthesiaSpectrumAnalysisWorker. This expects IAnalyzerNRTSettings to be a valid pointer to a FSynesthesiaSpectrumAnalysisSettings object.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L10 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/SynesthesiaSpectrumAnalyzer.h` (Public)


#### enum `Audio::ESynesthesiaSpectrumType`  
`enum class ESynesthesiaSpectrumType : uint8`  
_L13-23_
- L16 _public enumerator_ `MagnitudeSpectrum` — Spectrum frequency values are equal to magnitude of frequency.
- L19 _public enumerator_ `PowerSpectrum` — Spectrum frequency values are equal to magnitude squared.
- L22 _public enumerator_ `Decibel` — Returns decibels with a noise floor of -90

#### struct `Audio::FSynesthesiaSpectrumAnalyzerSettings`  
`struct FSynesthesiaSpectrumAnalyzerSettings`  
_L25-34_
- L27 _public member_ `int32 FFTSize = 512;`
- L29 _public member_ `ESynesthesiaSpectrumType SpectrumType = ESynesthesiaSpectrumType::PowerSpectrum;`
- L31 _public member_ `EWindowType WindowType = EWindowType::None;`
- L33 _public member_ `bool bDownmixToMono = true;`

#### class `Audio::FSynesthesiaSpectrumAnalyzer`  
`class FSynesthesiaSpectrumAnalyzer`  
_L36-62_
- L41 _public prototype_ `FSynesthesiaSpectrumAnalyzer(float InSampleRate, const FSynesthesiaSpectrumAnalyzerSettings& InSettings);` — Construct analyzer
- L46 _public prototype_ `void ProcessAudio(TArrayView<const float> InSampleView, TArrayView<float> OutSpectrum);` — Calculate the spectrum values for the input samples. OutSpectrum should have (num input samples / 2) + 1 values.
- L51 _public prototype_ `const FSynesthesiaSpectrumAnalyzerSettings& GetSettings() const;` — Return const reference to settings used inside this analyzer.
- L54 _protected member_ `FSynesthesiaSpectrumAnalyzerSettings Settings;`
- L55 _protected member_ `float SampleRate = 0.0f;`
- L56 _protected member_ `float FFTScaling = 0.0f;`
- L58 _protected member_ `FWindow Window;`
- L59 _protected member_ `Audio::FAlignedFloatBuffer WindowedBuffer;`
- L60 _protected member_ `Audio::FAlignedFloatBuffer FFTOutput;`
- L61 _protected member_ `TUniquePtr<IFFTAlgorithm> FFT;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L9 _namespace_ `namespace Audio`
- L11 _namespace_ `namespace Audio`

### `Plugins/Runtime/AudioSynesthesia/Source/AudioSynesthesiaCore/Public/YINPitchDetector.h` (Public)


#### struct `Audio::FYINPitchDetectorSettings`  
`struct FYINPitchDetectorSettings`  
_L15-30_
- desc: Settings for creating a YIN pitch detector.
- L18 _public member_ `float AnalysisHopSeconds = 0.01f;` — Time (in seconds) between analysis windows.
- L21 _public member_ `float MinimumFrequency = 80.f;` — Minimum detectable frequency (Hz). Determines window size — lower values require larger windows.
- L24 _public member_ `float MaximumFrequency = 2000.f;` — Maximum detectable frequency (Hz).
- L29 _public member_ `float Threshold = 0.15f;` — Voiced/unvoiced threshold applied to the cumulative mean normalized difference function. Lower values are stricter (fewer detections); higher values are more permissive. Typical range: 0.05 – 0.25. Default (0.15) is appropriate for clean vocal input.

#### class `Audio::FYINPitchDetector`  
`class FYINPitchDetector : public IPitchDetector`  
_L45-101_
- inherits: `IPitchDetector`
- desc: Pitch detector based on the YIN algorithm (de Cheveigné & Kawahara, 2002). YIN computes a cumulative mean normalized difference function (CMND) over each analysis window and finds the first lag below a voiced/unvoiced threshold. Compared to plain autocorrelation (FAutoCorrelationPitchDetector), YIN strongly suppresses sub-harmonic octave errors and provides a natural voiced/unvoiced decision via the threshold. Strength is reported as (1 - CMND(τ)), where τ is the chosen lag. A value near 1.0 indicates high periodicity; values near 0.0 indicate noise or an unvoiced frame. Only one pitch is emitted per analysis window (the fundamental), making this suitable for monophonic sources such as a singing voice in a karaoke context.
- L49 _public prototype_ `FYINPitchDetector(const FYINPitchDetectorSettings& InSettings, float InSampleRate);` — Create a YIN pitch detector with the given settings and sample rate.
- L51 _public prototype_ `virtual ~FYINPitchDetector();`
- L59 _public prototype_ `virtual void DetectPitches(const FAlignedFloatBuffer& InMonoAudio, TArray<FPitchInfo>& OutPitches) override;` — Detect pitches in the audio. May be called repeatedly with consecutive buffers. @param InMonoAudio - A mono audio buffer of any length. @param OutPitches  - Detected pitch observations are appended to this array. At most one entry is appended per analysis window.
- L62 _public prototype_ `virtual void Finalize(TArray<FPitchInfo>& OutPitches) override;` — Resets internal buffers. No additional pitches are emitted on Finalize.
- L69 _private prototype_ `void ComputeDifferenceFunction(const FAlignedFloatBuffer& InWindow);` — Compute the difference function d(τ) = m₁ + m₂(τ) - 2r(τ) via FFT-based cross-correlation. r(τ) = Σ_{t=0}^{W/2-1} x[t]·x[t+τ]  is computed with FBlockCorrelator (O(N log N)). m₁ = r(0), and m₂(τ) is updated with a O(1) sliding sum of squares per lag.
- L72 _private prototype_ `void NormalizeDifferenceFunction();` — Normalize d(τ) in-place to the cumulative mean normalized difference d'(τ).
- L76 _private prototype_ `bool FindFundamentalLag(float& OutLag, float& OutStrength) const;` — Find the best lag via threshold + parabolic refinement. @return true if a voiced lag was found, writing its sub-sample value to OutLag.
- L78 _private member_ `FYINPitchDetectorSettings Settings;`
- L80 _private member_ `float SampleRate;`
- L81 _private member_ `int32 WindowNumSamples;`
- L82 _private member_ `int32 HalfWindowNumSamples;`
- L83 _private member_ `int32 MinLagBin;`
- L84 _private member_ `int32 MaxLagBin;`
- L85 _private member_ `int64 WindowCounter;`
- L87 _private member_ `TSlidingBuffer<float> SlidingBuffer;`
- L88 _private member_ `FAlignedFloatBuffer WindowBuffer;`
- L91 _private member_ `TArray<float> DiffBuffer;` — Difference function buffer d(τ), length == HalfWindowNumSamples + 1.
- L94 _private member_ `TUniquePtr<FBlockCorrelator> Correlator;` — FFT-based cross-correlator. Input size = WindowNumSamples, no window, no normalization.
- L97 _private member_ `FAlignedFloatBuffer AutoCorrBuffer;` — Cross-correlation output buffer. Positive lags r(τ) are in [0..HalfWindowNumSamples].
- L100 _private member_ `FAlignedFloatBuffer FirstHalfBuffer;` — First half of the analysis window zero-padded to WindowNumSamples, reused each frame.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOSYNESTHESIACORE_API`
- L10 _namespace_ `namespace Audio`
- L12 _namespace_ `namespace Audio`
