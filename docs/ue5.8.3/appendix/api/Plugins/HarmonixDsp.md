# Plugins / HarmonixDsp

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixDsp`
- headers: 72; symbols: 2550
- symbol kinds: class=54, delegate=12, enum=32, enumerator=204, externvar=1, function=641, macro=27, member=781, namespace=75, prototype=587, struct=59, typedef=20, union=2, variable=55
- PrivateDependencyModuleNames: AssetRegistry, SignalProcessing, UnrealEd
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, DeveloperSettings, Engine, Harmonix, HarmonixMidi

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/AudioData/StreamingAudioRendererV2.h` (Private)


#### class `FStreamingAudioRendererV2`  
`class FStreamingAudioRendererV2 : public IAudioDataRenderer`  
_L25-96_
- inherits: `IAudioDataRenderer`
- L29 _public typedef_ `using FAlignedInt16Buffer = TArray<int16, Audio::FAudioBufferAlignedAllocator>;`
- L31 _public prototype_ `FStreamingAudioRendererV2();`
- L32 _public prototype_ `~FStreamingAudioRendererV2();`
- L34 _public prototype_ `virtual void Reset() override;`
- L35 _public prototype_ `virtual void SetSoundWaveData(const TSharedRef<const FSoundWaveData>& InSoundWaveData, const FSettings& InSettings) override;`
- L36 _public prototype_ `virtual TSharedPtr<const FSoundWaveData> GetSoundWaveData() const override;`
- L38 _public prototype_ `virtual void MigrateToSampler(const FFusionSampler* InSampler) override;`
- L40 _public prototype_ `virtual void SetFrame(uint32 InFrameNum) override;`
- L42 _public prototype_ `virtual double Render(TAudioBuffer<float>& OutBuffer, double InPos, int32 InMaxFrame, double InResampleInc, double InPitchShift, double InSpeed, bool MaintainPitchWhenSpeedChanges, const FGainMatrix& InGain) override;`
- L45 _public prototype_ `double RenderInternal(TAudioBuffer<float>& OutBuffer, double Pos, int32 MaxFrame, double Inc, const FGainMatrix& Gain);`
- L47 _public prototype_ `virtual double RenderUnshifted(TAudioBuffer<float>& OutBuffer, double InPos, int32 InMaxFrame, double InInc, const FGainMatrix& InGain) override;`
- L50 _public prototype_ `void GenerateSourceAudio(uint32 StartFrame, Audio::FAlignedFloatBuffer& OutAudio);`
- L54 _private prototype_ `void RenderSimpleUnshifted(TAudioBuffer<float>& OutBuffer, const FLerpData* LerpArray, uint32 InNumFrames, const FGainMatrix& InGain, double InInc);`
- L55 _private prototype_ `void RenderMultiChannelUnshifted(TAudioBuffer<float>& OutBuffer, const FLerpData* LerpArray, uint32 InNumFrames, const FGainMatrix& InGain, double InInc);`
- L56 _private prototype_ `void RenderMultiChannelRoutedUnshifted(TAudioBuffer<float>& OutBuffer, const FLerpData* LerpArray, uint32 InNumFrames, const FGainMatrix& InGain, double InInc);`
- L58 _private prototype_ `void SeekSourceAudioToFrame(uint32 FrameIdx);`
- L59 _private prototype_ `void DecodeSourceAudio(Audio::TCircularAudioBuffer<float>& OutBuffer);`
- L60 _private prototype_ `void GenerateSourceAudioInternal(uint32 StartFrameIndex, TArrayView<float> OutAudio);`
- L62 _private prototype_ `uint32 GetSourceAudioFrameIndex();`
- L64 _private prototype_ `static TUniquePtr<FSoundWaveProxyPlayer> CreateWavePlayer(const TSharedRef<const FSoundWaveData>& WaveData);`
- L66 _private prototype_ `bool HasLoopSection() const;`
- L67 _private prototype_ `uint32 GetLoopStartFrame() const;`
- L68 _private prototype_ `uint32 GetLoopEndFrame() const;`
- L70 _private member_ `const FFusionSampler* MySampler = nullptr;`
- L71 _private member_ `const TArray<FTrackChannelInfo>* TrackChannelInfo = nullptr;`
- L72 _private member_ `TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> Shifter;`
- L77 _private member_ `TSharedPtr<const FSoundWaveData> SoundWaveData;` — Ref to the actual streaming audio data this data is a shared instance of audio data it will get loaded on construction
- L79 _private member_ `TUniquePtr<FSoundWaveProxyPlayer> WavePlayer;`
- L81 _private member_ `Audio::FAlignedFloatBuffer DecodeBuffer;`
- L82 _private member_ `Audio::TCircularAudioBuffer<float> InterleavedCircularBuffer;`
- L84 _private member_ `Audio::FAlignedFloatBuffer WorkBuffer;`
- L86 _private member_ `int32 NumDeinterleaveChannels;`
- L87 _private member_ `Audio::FAlignedFloatBuffer LastLoopFrameCache;`
- L88 _private member_ `bool bLastLoopFrameCached = false;`
- L92 _private member_ `static constexpr int32 DeinterleaveBlockSizeInFrames = 256;` — needs to be small enough to avoid audio artifacts and syncing issues but also large enough that we're decoding multiple times per block
- L93 _private member_ `static constexpr uint32 MaxDecodeSizeInFrames = 1024;`
- L95 _private prototype_ `int32 CalculateNumFramesNeeded(const FLerpData* LerpData, int32 NumPoints);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HARMONIXDSP_API`
- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixStreamingAudioRendererV2, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixStreamingAudioRendererV2, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/Conversions.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixDsp`
- L16 _variable_ `const float kFloatingTo1Dot15Fixed = (float)((uint64)(1 << 15));` (scope `HarmonixDsp`) — this is an asymmetrical mapping from [-32768, 32767] to [-1, 0.999969482421875] in this scenario, the floating point number 1.0f is out of the range of numbers representable by 1.15 fixed, although -1.0 is representable so if you are synthesizing floating point audio data to be converted to 1.15 fixed point, be careful to deal with numbers less than -1.0f and greater OR EQUAL to 1.0f.
- L17 _variable_ `const float k1Dot15FixedToFloating = 1.0f / (float)((uint64)(1 << 15));` (scope `HarmonixDsp`)
- L19 _variable_ `const float kMax1Dot15AsFloat = (float)MAX_int16 * k1Dot15FixedToFloating;` (scope `HarmonixDsp`)
- L22 _variable_ `const float kFloatingTo1Dot31Fixed = (float)((uint64)(1 << 31));` (scope `HarmonixDsp`) — also asymmetrical
- L25 _variable_ `const float kFloatingTo8Dot24Fixed = (float)((uint64)(1 << 24) - 1);` (scope `HarmonixDsp`) — the -1 makes sure that numbers on the range [-1,1] map symmetrically
- L27 _prototype_ `uint32 GetNumInputSamplesRequiredForSRC( uint32 NumOutputSamplesRequired, double StartPos, double Increment);` (scope `HarmonixDsp`)
- L32 _prototype_ `double SampleRateConvert( const float* Input, uint32 NumInputSamples, double StartPos, double Increment, float* Output, uint32 NumOutputSamples, float gain = 1.0f, bool Accumulate = false);` (scope `HarmonixDsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/FusionSampler/FusionPatchCustomVersion.h` (Private)


#### struct `FFusionPatchCustomVersion`  
`struct FFusionPatchCustomVersion`  
_L8-36_
- L31 _public member_ `static const FGuid GUID;`
- L35 _private function_ `FFusionPatchCustomVersion()`

#### enum `FFusionPatchCustomVersion::Type`  
`enum Type`  
_L10-29_
- L12 _public enumerator_ `BeforeCustomVersionWasAdded = 0`
- L14 _public enumerator_ `KeyzonesUseMappedParameters = 1`
- L16 _public enumerator_ `PitchShifterNameRedirects = 2`
- L18 _public enumerator_ `PanImportingFromDTAFixed = 3`
- L20 _public enumerator_ `DeprecatedPresets = 4`
- L22 _public enumerator_ `DeprecatedUnusedEffectsSettings = 5`
- L24 _public enumerator_ `DeprecateTypedSettingsArray = 6`
- L27 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L28 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/Math/Complex.h` (Private)


#### class `TComplex`  
`template<typename T> class TComplex`  
_L7-138_
- L11 _public function_ `TComplex() : Real(0), Imag(0)`
- L15 _public function_ `TComplex(T X, T Y) : Real(X), Imag(Y)` — X is real part Y is imaginary part
- L19 _public function_ `TComplex(T X) : Real(X), Imag(0)` — X is real part imaginary part is 0
- L21 _public function_ `TComplex operator*(const TComplex& Z) const`
- L26 _public function_ `TComplex operator*(T S) const`
- L31 _public function_ `TComplex operator+(const TComplex& Z) const`
- L36 _public function_ `TComplex operator-(const TComplex& Z) const`
- L41 _public function_ `TComplex operator-() const`
- L46 _public function_ `TComplex operator/(const TComplex& Z) const`
- L51 _public function_ `TComplex& SetRect(T X, T Y)`
- L58 _public function_ `TComplex& SetPolar(T R, T Theta)`
- L63 _public function_ `TComplex Conjugate() const`
- L68 _public function_ `TComplex Inverse() const`
- L75 _public function_ `TComplex Sqrt() const`
- L94 _public function_ `T GetReal() const`
- L95 _public function_ `T GetImag() const`
- L96 _public function_ `T X() const`
- L97 _public function_ `T Y() const`
- L99 _public function_ `T Magnitude() const`
- L100 _public function_ `T Angle() const`
- L124 _public function_ `bool operator==(const TComplex& Other) const`
- L129 _public function_ `bool operator !=(const TComplex& Other) const`
- L136 _private member_ `T Real;`
- L137 _private member_ `T Imag;`

#### Free symbols / members of external scopes

- L141 _function_ `template<typename T> TComplex<T> operator*(T S, const TComplex<T>& Z)`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/Math/Interp.h` (Private)


#### class `FInterp`  
`class FInterp`  
_L7-39_
- L10 _public function_ `float operator()(float Alpha)`
- L14 _public prototype_ `virtual float Eval(float Alpha) const = 0;` — returns the interpolation result based on a value between 0 and 1 accepts values outside of the range 0 and 1 and will extrapolate
- L18 _public prototype_ `virtual float Inverse(float Value) const = 0;` — returns the inverse of the interpolation given a value between the Min and Max range accepts values outside of the Min and Max range and will extrapolate
- L22 _public function_ `virtual float EvalClamped(float Alpha) const` — clamps the result to the Min and Max value of the range for values of Alpha is outside the range 0 and 1
- L29 _public function_ `virtual float InverseClamped(float Value) const` — clamps the result between 0 and 1 for values outside the Min and Max range
- L35 _protected member_ `float MinValue = 0.0f;`
- L36 _protected member_ `float MaxValue = 0.0f;`
- L37 _protected member_ `float MinAlpha = 0.0f;`
- L38 _protected member_ `float MaxAlpha = 1.0f;`

#### class `FLerp`  
`class FLerp : public FInterp`  
_L41-60_
- inherits: `FInterp`
- L45 _public function_ `FLerp(float A, float B)`
- L51 _public function_ `virtual float Eval(float Alpha) const override`
- L56 _public function_ `virtual float Inverse(float Value) const override`

#### class `FInterpEaseIn`  
`class FInterpEaseIn : public FInterp`  
_L65-92_
- inherits: `FInterp`
- desc: easing function = Pow(Alpha, Exp) (B - A) + A previously known as ExpInterpolate changed names to correspond to UE version
- L69 _public function_ `FInterpEaseIn(float A, float B, float InExp)`
- L76 _public function_ `virtual float Eval(float Alpha) const`
- L82 _public function_ `virtual float Inverse(float Value) const`
- L91 _private member_ `float Exp;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/Math/Polynomial.h` (Private)


#### Free symbols / members of external scopes

- L24 _namespace_ `namespace FPolynomial`
- L26 _function_ `inline int32 ComputeRootsOfQuadratic(TComplex<double> InA, TComplex<double> InB, TComplex<double> InC, TComplex<double>& OutX1, TComplex<double>& OutX2)` (scope `FPolynomial`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/Stretchers/ConsoleCommands.h` (Private)


#### struct `Harmonix::Dsp::ConsoleCommands::FPitchShifter`  
`struct FPitchShifter`  
_L9-25_
- L11 _public prototype_ `static void EnableAll();`
- L12 _public prototype_ `static void DisableAll();`
- L14 _public prototype_ `static bool Enable(FName Name);`
- L16 _public prototype_ `static bool Disable(FName Name);`
- L18 _public prototype_ `static bool IsEnabled(FName Name);`
- L22 _private member_ `static TArray<FName> DisabledPitchShifters;`
- L24 _private function_ `FPitchShifter()`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Harmonix`
- L7 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L7 _namespace_ `namespace ConsoleCommands` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/Stretchers/SmbPitchShifter.h` (Private)


#### class `FSmbPitchShifter`  
`class FSmbPitchShifter : public IStretcherAndPitchShifter`  
_L82-186_
- inherits: `IStretcherAndPitchShifter`
- L86 _public prototype_ `FSmbPitchShifter(FName InFactoryName);`
- L87 _public prototype_ `FSmbPitchShifter(FName InFactoryName, float InSampleRate);`
- L89 _public prototype_ `FSmbPitchShifter();`
- L90 _public prototype_ `FSmbPitchShifter(float InSampleRate);`
- L92 _public prototype_ `virtual ~FSmbPitchShifter();`
- L94 _public prototype_ `static void Init();`
- L96 _public function_ `void Configure()`
- L97 _public prototype_ `void Configure(int32 InNumChannels, int32 InWindowSize, int32 InOverlapFactor);`
- L98 _public prototype_ `void Configure(int32 InNumChannels, int32 InWindowSize, int32 InOverlapFactor, int32 MaxInputSamplesToCache);`
- L100 _public prototype_ `virtual int32 GetLatencySamples() const override;`
- L102 _public prototype_ `void SetMonoCutoff(float FreqHz);`
- L103 _public prototype_ `virtual void SetSampleRateAndReset(float InSampleRate) override;`
- L104 _public function_ `virtual int32 GetInputFramesNeeded(int32 InNumOutFramesNeeded, float PitchShift, float SpeedShift) override`
- L105 _public prototype_ `virtual void StereoPitchShift(float InPitchShift, int32 InNumSampsToProcess, float* InLeftData, float* InRightData, float* OutLeftData, float* OutRightData) override;`
- L109 _public prototype_ `virtual double Render(TAudioBuffer<float>& OutputData, double Pos, int32 MaxFrame, double ResampleInc, double PitchShift, double Speed, bool MaintainPitchWhenSpeedChanges, const FGainMatrix& Gain) override;`
- L111 _public prototype_ `virtual bool TakeInput(TAudioBuffer<float>& InBuffer) override;`
- L112 _public prototype_ `virtual bool InputSilence(int32 NumFrames) override;`
- L113 _public prototype_ `virtual void StereoPitchShift(float InPitchShift, int32 InNumOutputFrame, float* OutLeftData, float* OutRightData) override;`
- L115 _public prototype_ `void PitchShift(float InPitchShift, int32 InNumSampsToProcess, float* InData, float* OutData, int32 ChannelIndex, int32 Stride);`
- L117 _public prototype_ `virtual void PitchShift(float InPitchShift, float InSpeed, TAudioBuffer<float>& OutBuffer) override;`
- L119 _public member_ `static const int32 kDefaultNumChannels = 2;`
- L120 _public member_ `static const int32 kDefaultOverlapFactor = 4;`
- L122 _public function_ `virtual size_t GetMemoryUsage() const override`
- L124 _public function_ `virtual void Cleanup() override`
- L127 _protected prototype_ `virtual void SetupAndResetImpl(const FTimeStretchConfig* ShifterSettings) override;`
- L143 _private member_ `int32 NumChannels = 0;`
- L144 _private member_ `FChannelBuffer* ChannelBuffers = nullptr;`
- L148 _private member_ `float MeasuredBinFreq[EWindowSize::Max];` — Some scratch buffers we don't want to new and delete every time we need them...
- L149 _private member_ `float MeasuredBinMagnitude[EWindowSize::Max];`
- L150 _private member_ `float SynthesizedBinFreq[EWindowSize::Max];`
- L151 _private member_ `float SynthesizedBinMagnitude[EWindowSize::Max];`
- L153 _private member_ `int32 FftFrameSize;`
- L154 _private member_ `int32 HalfFftFrameSize;`
- L155 _private member_ `int32 OverlapFactor;`
- L156 _private member_ `int32 StepSize;`
- L157 _private member_ `int32 InFifoLatency;`
- L158 _private member_ `double ExpectedPhaseDifferent;`
- L159 _private member_ `double FreqPerFftBin;`
- L160 _private member_ `float* Window;`
- L161 _private member_ `int32 BottomStereoBin;`
- L162 _private member_ `float SampleRate;`
- L163 _private member_ `size_t MemoryUsed = 0;`
- L165 _private member_ `TAudioBuffer<float> InputBuffer;`
- L166 _private member_ `int32 InputFrameOffset = 0;`
- L168 _private member_ `static float Window128[EWindowSize::k128];`
- L169 _private member_ `static float Window256[EWindowSize::k256];`
- L170 _private member_ `static float Window512[EWindowSize::k512];`
- L171 _private member_ `static float Window1024[EWindowSize::k1024];`
- L172 _private member_ `static float Window2048[EWindowSize::k2048];`
- L173 _private member_ `static float Window4096[EWindowSize::k4096];`
- L174 _private member_ `static bool WindowsInitialized;`
- L176 _private prototype_ `void InitializeWindows();`
- L177 _private prototype_ `void Reset();`
- L185 _private prototype_ `void Fft(float* FftBuffer, int32 Sign);` — The function Fft is a Fast Fourier Transform (FFT) implementation. It takes an array of floats FftBuffer representing the time-domain input signal, and an integer sign indicating whether the FFT should be performed in the forward or inverse direction. The function modifies the input array FftBuffer to store the output frequency-domain signal.

#### struct `FSmbPitchShifter::FChannelBuffer`  
`struct FChannelBuffer`  
_L131-142_
- desc: A bunch of stereo buffers...
- L133 _public member_ `float InPCMBuffer[EWindowSize::Max];`
- L134 _public member_ `float OutPCMBuffer[EWindowSize::Max];`
- L135 _public member_ `float FftBuffer[EWindowSize::MaxImag];`
- L136 _public member_ `float LastPhase[EWindowSize::MaxReal];`
- L137 _public member_ `float SummedPhase[EWindowSize::MaxReal];`
- L138 _public member_ `float OutputAccumulator[EWindowSize::MaxImag];`
- L139 _public member_ `int32 OutWriteIndex;`
- L141 _public prototype_ `void Reset();`

#### Free symbols / members of external scopes

- L59 _macro_ `#define UE_API HARMONIXDSP_API`
- L61 _namespace_ `namespace EWindowSize`
- L63 _variable_ `static constexpr int32 k128 = 128;` (scope `EWindowSize`)
- L64 _variable_ `static constexpr int32 k256 = 256;` (scope `EWindowSize`)
- L65 _variable_ `static constexpr int32 k512 = 512;` (scope `EWindowSize`)
- L66 _variable_ `static constexpr int32 k1024 = 1024;` (scope `EWindowSize`)
- L67 _variable_ `static constexpr int32 k2048 = 2048;` (scope `EWindowSize`)
- L68 _variable_ `static constexpr int32 k4096 = 4096;` (scope `EWindowSize`)
- L70 _variable_ `static constexpr int32 Max = k4096;` (scope `EWindowSize`)
- L71 _variable_ `static constexpr int32 Default = k1024;` (scope `EWindowSize`)
- L73 _variable_ `static const int32 MaxImag = Max * 2;` (scope `EWindowSize`)
- L74 _variable_ `static const int32 MaxReal = (Max / 2) + 1;` (scope `EWindowSize`)
- L76 _function_ `static constexpr bool IsValid(int32 Size)` (scope `EWindowSize`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/Stretchers/SmbPitchShifterConfig.h` (Private)


#### class `USmbPitchShifterConfig`  
`class USmbPitchShifterConfig : public UStretcherAndPitchShifterConfig`  
_L11-69_
- reflection: `UCLASS(meta = (DisplayName = "SMB Pitch Shifter Settings"))`
- inherits: `UStretcherAndPitchShifterConfig`
- L19 _public member_ `bool bAllowPoolGrowthInEditor = false;` — `UPROPERTY(config, EditAnywhere, Category = "Pool Config")` — If true, allows the stretcher pool to grow beyond DefaultAllocatedStretchers in the editor.
- L22 _public member_ `uint32 DefaultAllocatedStretchers = 12;` — `UPROPERTY(config, EditAnywhere, Category = "Pool Config")`
- L25 _public member_ `uint32 SwitchAllocatedStretchers = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Pool Config")`
- L28 _public member_ `uint32 PS4AllocatedStretchers = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Pool Config")`
- L31 _public member_ `uint32 PS5AllocatedStretchers = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Pool Config")`
- L34 _public member_ `uint32 XboxOneAllocatedStretchers = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Pool Config")`
- L37 _public member_ `uint32 XSXAllocatedStretchers = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Pool Config")`
- L40 _public member_ `uint32 AndroidAllocatedStretchers = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Pool Config")`
- L42 _public function_ `uint32 GetNumAllocatedStretchersForPlatform() const`
- L61 _public function_ `bool ShouldAllowPoolGrowth() const`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Private/HarmonixDsp/Stretchers/SmbPitchShifterFactory.h` (Private)


#### class `FSmbPitchShifterFactory`  
`class FSmbPitchShifterFactory : public IStretcherAndPitchShifterFactory`  
_L9-36_
- inherits: `IStretcherAndPitchShifterFactory`
- L12 _public member_ `static const FName Name;`
- L14 _public prototype_ `virtual const TArray<FName>& GetFactoryNames() const override;`
- L16 _public prototype_ `virtual TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> GetFreePitchShifter(const FTimeStretchConfig& InConfig) override;`
- L18 _public prototype_ `virtual void ReleasePitchShifter(TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> InShifter) override;`
- L20 _public prototype_ `virtual bool HasFreePitchShifters(const FTimeStretchConfig& InConfig) const override;`
- L22 _public prototype_ `virtual size_t GetMemoryUsedByPool() const override;`
- L25 _protected prototype_ `virtual void OnClientAdded(void* Client, float SampleRate) override;`
- L27 _protected prototype_ `virtual void OnClientRemoved(void* Client) override;`
- L30 _private typedef_ `using FShifterPool = Harmonix::TDynamicObjectPool<IStretcherAndPitchShifter>;`
- L31 _private member_ `FShifterPool PitchShifterPool;`
- L33 _private member_ `float FactorySampleRate = 0;`
- L35 _private prototype_ `static TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> CreateStretcherAndPitchShifter(float InSampleRate);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioAnalysis/AnalysisUtilities.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Harmonix`
- L10 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L10 _namespace_ `namespace AudioAnalysis` (scope `Harmonix::Dsp`)
- L20 _prototype_ `float SmoothEnergy( float TargetEnergyLinear, float PreviousEnergyLinear, float ElapsedMs, const FHarmonixAudioAnalyzerOutputSettings& Settings);` (scope `Harmonix::Dsp::AudioAnalysis`) — @brief Smooth a value based on some input settings @param TargetEnergyLinear - The current target should be an energy rather than amplitude (squared and non-negative) @param PreviousEnergyLinear - The previous energy @param ElapsedMs - The amount of time elapsed since the last call to this function @param Settings - The settings to use for the scaling and smoothing @return The smoothed value
- L35 _function_ `template <typename T> float CalculatePSNR(const T* InterleavedInA, const T* InterleavedInB, const int32 NumChannels, const int32 NumSampleFrames)` (scope `Harmonix::Dsp::AudioAnalysis`) — @brief Calculates the signal to noise. 96dB is perfect... no noise, all signal.	Big numbers good, small numbers bad @param InterleavedInA - Pointer to the first sample in the first buffer. If multichannel, the channels must be interleaved @param InterleavedInB - Pointer to the first sample in the second buffer. If multichannel, the channels must be interleaved @param NumnChannels - Number of interleaved channels per sample frame @param NumSampleFrames - Number of samples frames @return Classic PSNR in dB. 96dB is perfect match. Smaller values indicate bigger difference.

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioAnalysis/FFTAnalyzer.h` (Public)


#### struct `FHarmonixFFTAnalyzerSettings`  
`struct FHarmonixFFTAnalyzerSettings`  
_L19-40_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `int32 FFTSize = 512;` — `UPROPERTY(EditAnywhere, Category="Settings")`
- L27 _public member_ `float MinFrequencyHz = 20.0f;` — `UPROPERTY(EditAnywhere, Category="Settings")`
- L30 _public member_ `float MaxFrequencyHz = 5500.0f;` — `UPROPERTY(EditAnywhere, Category="Settings")`
- L33 _public member_ `bool MelScaleBinning = false;` — `UPROPERTY(EditAnywhere, Category="Settings")`
- L36 _public member_ `int32 NumResultBins = 256;` — `UPROPERTY(EditAnywhere, Category="Settings")`
- L39 _public member_ `FHarmonixAudioAnalyzerOutputSettings OutputSettings;` — `UPROPERTY(EditAnywhere, Category="Settings")`

#### struct `FHarmonixFFTAnalyzerResults`  
`struct FHarmonixFFTAnalyzerResults`  
_L43-54_
- reflection: `USTRUCT(BlueprintType)`
- L48 _public member_ `TArray<float> Spectrum;` — `UPROPERTY(BlueprintReadOnly, Category="Results")`

#### class `Harmonix::Dsp::AudioAnalysis::FFFTAnalyzer`  
`class FFFTAnalyzer`  
_L58-115_
- L61 _public member_ `inline static constexpr int32 MinFFTSize = 64;`
- L63 _public member_ `inline static constexpr int32 MaxFFTSize = 2048;`
- L65 _public member_ `inline static constexpr int32 MaxBins = MaxFFTSize / 2;`
- L67 _public member_ `inline static constexpr float MinFrequency = 20.0f;`
- L68 _public member_ `inline static constexpr float MaxFrequency = 20000.0f;`
- L70 _public member_ `inline static constexpr float MinSmoothingTime = 0.0f;`
- L71 _public member_ `inline static constexpr float MaxSmoothingTime = 10000.0f;`
- L73 _public prototype_ `explicit FFFTAnalyzer(float InSampleRate);`
- L79 _public prototype_ `void SetSettings(const FHarmonixFFTAnalyzerSettings& InSettings);` — @brief Set the settings for this analyzer @param InSettings - The settings to use
- L84 _public prototype_ `void Reset();` — @brief Reset the analyzer to its initial state
- L91 _public prototype_ `void Process(const Audio::FAlignedFloatBuffer& InBuffer, FHarmonixFFTAnalyzerResults& InOutResults);` — @brief Process a buffer and get the analyzer results @param InBuffer - The audio buffer to analyze @param InOutResults - The results from the analysis
- L94 _private member_ `const float SampleRate;`
- L96 _private member_ `FCriticalSection SettingsGuard;`
- L97 _private member_ `FHarmonixFFTAnalyzerSettings Settings;`
- L98 _private member_ `bool NeedsRecalculate = true;`
- L112 _private member_ `FState State;`
- L114 _private prototype_ `static void Recalculate(float SampleRate, FHarmonixFFTAnalyzerSettings& InOutSettings, FState& InOutState);`

#### struct `Harmonix::Dsp::AudioAnalysis::FFFTAnalyzer::FState`  
`struct FState`  
_L100-111_
- L102 _public member_ `TUniquePtr<Audio::IFFTAlgorithm> FFT;`
- L103 _public member_ `TUniquePtr<Audio::TSlidingBuffer<float>> SlidingBuffer;`
- L104 _public member_ `TUniquePtr<Audio::FWindow> Window;`
- L105 _public member_ `TArray<float> WindowedBuffer;`
- L106 _public member_ `Audio::AlignedFloatBuffer FFTOutput;`
- L107 _public member_ `Audio::AlignedFloatBuffer RawSpectrumOutput;`
- L108 _public member_ `TArray<float> RiseTargets;`
- L109 _public member_ `TArray<float> BinRanges;`
- L110 _public member_ `float FFTScaling = 0.0f;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXDSP_API`
- L13 _namespace_ `namespace Audio`
- L50 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FHarmonixFFTAnalyzerResults& InAnalyzerResults)`
- L56 _namespace_ `namespace Harmonix`
- L56 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L56 _namespace_ `namespace AudioAnalysis` (scope `Harmonix::Dsp`)
- L62 _prototype_ `static_assert(FMath::IsPowerOfTwo(MinFFTSize), "Min` (scope `Harmonix::Dsp::AudioAnalysis::FFFTAnalyzer::FMath`)
- L64 _prototype_ `static_assert(FMath::IsPowerOfTwo(MaxFFTSize), "Max` (scope `Harmonix::Dsp::AudioAnalysis::FFFTAnalyzer::FMath`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioAnalysis/OutputSettings.h` (Public)


#### struct `FHarmonixAudioAnalyzerOutputSettings`  
`struct FHarmonixAudioAnalyzerOutputSettings`  
_L8-23_
- reflection: `USTRUCT(BlueprintType)`
- L13 _public member_ `float RiseMs = 50.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(UIMin = 0, ClampMin = "0", UIMax = 1000, ClampMax = "1000"))`
- L16 _public member_ `float FallMs = 250.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(UIMin = 0, ClampMin = "0", UIMax = 4000, ClampMax = "4000"))`
- L19 _public member_ `float MaxDecibels = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(UIMin = -96, ClampMin = "-96", UIMax = 0, ClampMax = "0"))`
- L22 _public member_ `float RangeDecibels = 30.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta=(UIMin = 3, ClampMin = "3", UIMax = 96, ClampMax = "96"))`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioAnalysis/WaveFileComparison.h` (Public)


#### class `Harmonix::Dsp::AudioAnalysis::FWaveFileComparison`  
`class FWaveFileComparison`  
_L13-34_
- L16 _public prototype_ `bool LoadForCompare(const FString& Wave1FilePath, const FString& Wave2FilePath);`
- L17 _public prototype_ `bool LoadForCompare(FArchive& Wave1Archive, FArchive& Wave2Archive);`
- L19 _public prototype_ `float GetPSNR(bool bCommonSizeOnly = true) const;`
- L30 _private member_ `FOneWaveFile Wave1;`
- L31 _private member_ `FOneWaveFile Wave2;`
- L33 _private member_ `bool bOk = false;`

#### struct `Harmonix::Dsp::AudioAnalysis::FWaveFileComparison::FOneWaveFile`  
`struct FOneWaveFile`  
_L22-28_
- L24 _public member_ `FWaveModInfo Info;`
- L25 _public member_ `TArray<uint8> BulkData;`
- L27 _public prototype_ `bool Load(FArchive& Archive);`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API HARMONIXDSP_API`
- L11 _namespace_ `namespace Harmonix`
- L11 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L11 _namespace_ `namespace AudioAnalysis` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioBuffer.h` (Public)


#### enum `EAudioBufferCleanupMode`  
`enum class EAudioBufferCleanupMode : uint8`  
_L34-38_
- L36 _public enumerator_ `Delete`
- L37 _public enumerator_ `DontDelete`

#### class `TAudioBuffer`  
`template <typename DataType> class TAudioBuffer`  
_L41-1478_
- L45 _public function_ `TAudioBuffer()`
- L50 _public function_ `void Initialize()`
- L71 _public function_ `void Reset()` — Clears the buffer and deletes the data if CleanupMode == EAudioBufferCleanupMode::Delete
- L91 _public function_ `void Configure(int32 InNumChannels, int32 InNumFrames, EAudioBufferCleanupMode InCleanupMode, float InSampleRate = 0.0f, bool InInterleaved = false)`
- L96 _public function_ `void Configure(EAudioBufferChannelLayout InChannelLayout, int32 InNumFrames, EAudioBufferCleanupMode InCleanupMode, float InSampleRate = 0.0f, bool InInterleaved = false)`
- L101 _public function_ `void Configure(FAudioBufferConfig InConfig, EAudioBufferCleanupMode InCleanupMode)`
- L171 _public function_ `void SetSampleRate(float InSampleRateHz)`
- L176 _public function_ `bool CheckIntegrity()`
- L189 _public function_ `TAudioBuffer(FAudioBufferConfig InConfig, EAudioBufferCleanupMode InCleanupMode)`
- L195 _public function_ `TAudioBuffer(int32 InNumChannels, int32 InNumFrames, EAudioBufferCleanupMode InCleanupMode)`
- L201 _public function_ `TAudioBuffer(EAudioBufferChannelLayout InChannelLayout, int32 InNumFrames, EAudioBufferCleanupMode InCleanupMode)`
- L207 _public function_ `~TAudioBuffer()`
- L212 _public function_ `bool GetIsSilent() const`
- L213 _public function_ `void SetIsSilent(bool InIsSilent)`
- L215 _public function_ `bool GetIsInterleaved() const`
- L217 _public function_ `int32 GetFreeableSize() const`
- L227 _public function_ `int32 GetNumValidBytes() const`
- L232 _public function_ `static int32 GetBytesPerSample()`
- L238 _public function_ `int32 GetFirstFrame() const` — frame position assigns a frame number to the first sample in the buffer
- L239 _public function_ `void SetFirstFrame(int32 InFirstFrame)`
- L247 _public function_ `int32 GetLengthInFrames() const` — because this buffer could hold multiple frames in a single channel (aka interleaved data) then the channel size does not necessarily represent the number of frames
- L248 _public function_ `void SetLengthInFrames(int32 InLength)`
- L254 _public function_ `size_t GetLastFrame() const`
- L256 _public function_ `EAudioBufferCleanupMode GetCleanupMode() const`
- L258 _public function_ `FORCEINLINE bool ContainsFrame(int32 InFrameNumber)`
- L263 _public function_ `void ZeroValidFrames()`
- L279 _public function_ `void ZeroData()`
- L285 _public function_ `void FillValidFrames(char InChr)`
- L300 _public function_ `void Fill(DataType InValue)`
- L323 _public function_ `void FillData(char InChr)`
- L344 _public function_ `void FillWithWhiteNoise(float InGain = 1.0f)` — fill the buffer with white noise this function only works for buffers of floats. @param InGain (optional) the InGain to apply to the white noise. defaults to 1 (0 dBFS). @returns description of the return type
- L353 _public function_ `DataType GetPeak(int32 ChannelIndex) const`
- L388 _public function_ `DataType GetPeak() const`
- L402 _public function_ `void ComputeOverview(uint32 InFramesPerOverviewSample, TAudioBuffer<DataType>& OutOverviewMax, TAudioBuffer<DataType>& OutOverviewMin) const`
- L443 _public function_ `void SwapEndianness()`
- L467 _public function_ `bool Saturate(DataType MinValue, DataType MaxValue)`
- L517 _public function_ `bool SaturateWithNANCheck(DataType MinValue, DataType MaxValue)`
- L577 _public function_ `void Scale(float InFactor)`
- L598 _public function_ `void SetChannelData(int32 InChannelIndex, const DataType* InData)`
- L610 _public function_ `void SetAliasedChannelData(DataType** InData, int32 InNumChannels)`
- L617 _public function_ `void AdvanceAliasedDataPointers(int32 InNumFrames)`
- L634 _public function_ `DataType* GetValidChannelData(int32 InChannelIndex)`
- L642 _public function_ `const DataType* GetValidChannelData(int32 ChanneIdx) const`
- L649 _public function_ `DataType* GetRawChannelData(int32 ChanneIdx)`
- L657 _public function_ `const DataType* GetRawChannelData(int32 ChanneIdx) const`
- L664 _public function_ `TDynamicStridePtr<DataType> GetStridingChannelDataPointer(int32 InChannelIdx) const`
- L677 _public function_ `void Alias(const TAudioBuffer<DataType>& Other, int32 InFrameOffset = 0)`
- L687 _public function_ `void Alias(const DataType* RawData, int32 InNumFrames, int32 InNumChannels, float SampleRate = 0.0f, bool IsInterleaved = false)`
- L700 _public function_ `void AliasChannelDataPointers( const TAudioBuffer<DataType>& Other, int32 InFirstChannel = 0, int32 InNumChannels = MAX_int32)`
- L721 _public function_ `void AliasChannelDataPointers( const FAudioBufferConfig& NewValidConfig, DataType** DataPtrs)`
- L741 _public function_ `void IncrementChannelDataPointers(int32 InIncrementSize)`
- L756 _public function_ `DataType** GetData()`
- L757 _public function_ `DataType* const* GetData() const`
- L758 _public function_ `const FAudioBufferConfig& GetMaxConfig() const`
- L760 _public function_ `FAudioBufferConfig GetValidConfig() const`
- L765 _public function_ `int32 GetMaxNumChannels() const`
- L766 _public function_ `int32 GetMaxNumFrames() const`
- L768 _public function_ `int32 GetNumValidChannels() const`
- L769 _public function_ `void SetNumValidChannels(int32 InNumChannels)`
- L775 _public function_ `EAudioBufferChannelLayout GetChannelLayout() const`
- L776 _public function_ `void SetChannelLayout(EAudioBufferChannelLayout InChannelLayout)`
- L781 _public function_ `uint16 GetChannelMask() const`
- L782 _public function_ `void SetChannelMask(uint16 InMask)`
- L787 _public function_ `int32 GetNumValidFrames() const`
- L788 _public function_ `void SetNumValidFrames(int32 InNumFrames)`
- L794 _public function_ `uint32 GetNumTotalValidSamples() const`
- L801 _public function_ `void Deinterleave(const TAudioBuffer<DataType>& Other)` — deinterleave the Other data set into this one. this one ends up deinterleaved.
- L828 _public function_ `void Deinterleave(const TAudioBuffer<DataType>& Other, float InGain, DataType InMin, DataType InMax)`
- L852 _public function_ `void Interleave(const TAudioBuffer<DataType>& Other)` — interleave the Other data set into this one. this one ends up interleaved.
- L878 _public function_ `void Interleave(const TAudioBuffer<DataType>& Other, float InGain, DataType InMin, DataType InMax)`
- L901 _public function_ `bool EqualWithTolerance(int32 ThisChannelIdx, const TAudioBuffer<DataType>& Other, int32 OtherChannelIdx, DataType Tolerance) const`
- L930 _public function_ `bool FindFirstDiff(const TAudioBuffer<DataType>& Other, int32& OutChannelIndex, int32& OutFrameIndex, DataType InTolerance) const`
- L960 _public function_ `bool EqualWithTolerance(const TAudioBuffer<DataType>& Other, DataType InTolerance) const`
- L975 _public function_ `void AssertEqualWithTolerance(const TAudioBuffer<DataType>& Other, DataType InTolerance) const`
- L1001 _public function_ `bool operator==(const TAudioBuffer<DataType>& Other) const`
- L1006 _public function_ `bool operator!=(const TAudioBuffer<DataType>& Other) const`
- L1011 _public function_ `TAudioBuffer<DataType>& operator*=(const TAudioBuffer<DataType>& Other)`
- L1043 _public function_ `void Copy(const TAudioBuffer<DataType>& Other)`
- L1116 _public function_ `void Copy(const TAudioBuffer<DataType>& Other, int32 InNumFrames, int32 InOffset)`
- L1170 _public function_ `void Copy(const TAudioBuffer<DataType>& Other, float InGain, DataType InMin, DataType InMax)`
- L1227 _public function_ `DataType* operator[](int32 Index)`
- L1233 _public function_ `void Accumulate(const TAudioBuffer<DataType>& Other)`
- L1305 _public function_ `void Accumulate(DataType** Input, int32 InNumChannels, int32 InNumFrames)`
- L1352 _public function_ `void MultiplyAccumulate(const TAudioBuffer<DataType>& Other, DataType InGain, DataType InGainDelta)` — merge the Other to this buffer, and apply the specified InGain, which will change by the delta each sample.
- L1432 _public function_ `void DebugLog(uint32 InChannel) const`
- L1440 _private function_ `static constexpr bool _UseSIMD()`
- L1442 _private function_ `bool _SaturateSIMD(DataType InMinValue, DataType InMaxValue)`
- L1445 _private function_ `void _ScaleSIMD(float InFactor)` — works for all data
- L1448 _private function_ `void _CopySIMD(const TAudioBuffer<DataType>& Other, float InGain, DataType InMin, DataType InMax)` — only optimized if this->IsInterleaved() == Other.IsInterleaved()
- L1451 _private function_ `void _AccumulateSIMD(DataType** InData, int32 InNumChannels, int32 InNumFrames)` — works for all data
- L1454 _private function_ `void _MultiplyAccumulateSIMD(const TAudioBuffer<DataType>& Other, DataType InGain, DataType InGainDelta)` — only optimized if both buffers are NOT Interleaved
- L1456 _private member_ `EAudioBufferCleanupMode CleanupMode;`
- L1457 _private member_ `DataType* MyData[FAudioBufferConfig::kMaxAudioBufferChannels];`
- L1459 _private member_ `FAudioBufferConfig MaxConfig;` — maximum channel size, initial num valid channels
- L1462 _private member_ `int32 NumValidChannels;` — these should never be larger than what MaxConfig reports
- L1463 _private member_ `EAudioBufferChannelLayout ChannelLayout;`
- L1464 _private member_ `int32 NumValidFrames;`
- L1465 _private member_ `uint16 ChannelMask = 0xFFFF;`
- L1468 _private member_ `int32 FirstFrame;` — the frame position this buffer is associated with
- L1469 _private member_ `int32 NumFrames;`
- L1470 _private member_ `int32 LastFrame;`
- L1472 _private member_ `bool IsSilent;`
- L1474 _private member_ `static constexpr int32 kAudioBufferStompDetector = 0xFEEDF00D;`
- L1476 _private prototype_ `TAudioBuffer(const TAudioBuffer& Other);`
- L1477 _private prototype_ `void operator=(const TAudioBuffer& Other);`
- L1508 _function_ `template<> constexpr bool TAudioBuffer<float>::_UseSIMD()`
- L1514 _function_ `template<> FORCEINLINE bool TAudioBuffer<float>::_SaturateSIMD(float InMinValue, float InMaxValue)`
- L1583 _function_ `template<> FORCEINLINE void TAudioBuffer<float>::_ScaleSIMD(float InFactor)`
- L1601 _function_ `template<> FORCEINLINE void TAudioBuffer<float>::_CopySIMD(const TAudioBuffer<float>& Other, float InGain, float InMin, float InMax)`
- L1647 _function_ `template<> FORCEINLINE void TAudioBuffer<float>::_AccumulateSIMD(float** InputData, int32 InNumChannels, int32 InNumFrames)`
- L1670 _function_ `template<> FORCEINLINE void TAudioBuffer<float>::_MultiplyAccumulateSIMD(const TAudioBuffer<float>& Other, float InGain, float InGainDelta)`

#### class `TConsumableAudioBuffer`  
`template <typename DataType> class TConsumableAudioBuffer : public TAudioBuffer<DataType>`  
_L1490-1505_
- inherits: `TAudioBuffer<DataType>`
- L1494 _public function_ `TConsumableAudioBuffer() : DataReady(false)`
- L1498 _public function_ `void MarkReady()`
- L1499 _public function_ `void MarkConsumed()`
- L1500 _public function_ `bool IsDataReady()`
- L1504 _private member_ `bool DataReady = false;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioBuffer, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioBuffer, Log, All);`
- L25 _namespace_ `namespace HarmonixDsp`
- L27 _namespace_ `namespace FAudioBuffer` (scope `HarmonixDsp`)
- L29 _prototype_ `void DebugLog(const int16* InData, uint64 InNumSamples);` (scope `HarmonixDsp::FAudioBuffer`)
- L30 _prototype_ `void DebugLog(const float* InData, uint64 InNumSamples);` (scope `HarmonixDsp::FAudioBuffer`)
- L1480 _namespace_ `namespace HarmonixDsp`
- L1482 _namespace_ `namespace FAudioBuffer` (scope `HarmonixDsp`)
- L1484 _prototype_ `void Convert(const TAudioBuffer<float>& Source, TAudioBuffer<int16>& Destination);` (scope `HarmonixDsp::FAudioBuffer`)
- L1485 _prototype_ `void Convert(const TAudioBuffer<int16>& Source, TAudioBuffer<float>& Destination);` (scope `HarmonixDsp::FAudioBuffer`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioBufferConfig.h` (Public)


#### struct `FAudioBufferConfig`  
`struct FAudioBufferConfig`  
_L17-58_
- L20 _public member_ `static const uint32 kMaxAudioBufferChannels = 8;`
- L22 _public prototype_ `FAudioBufferConfig();`
- L23 _public prototype_ `FAudioBufferConfig(int32 InNumChannels, int32 InNumFrames, float InSampleRate = 0.0f, bool InInterleaved = false);`
- L24 _public prototype_ `FAudioBufferConfig(EAudioBufferChannelLayout InChannelLayout, int32 InNumFrames, float InSampleRate = 0.0f, bool InInterleaved = false);`
- L25 _public prototype_ `FAudioBufferConfig(EAudioBufferChannelLayout InChannelLayout, int32 InNumChannels, int32 InNumFrames, float InSampleRate = 0.0f, bool InInterleaved = false);`
- L27 _public prototype_ `int32 GetNumTotalSamples() const;`
- L28 _public prototype_ `float GetSampleRate() const;`
- L29 _public prototype_ `void SetSampleRate(float InSamplesPerSecond);`
- L31 _public function_ `FORCEINLINE int32 GetNumChannels() const`
- L32 _public prototype_ `void SetNumChannels(int32 InNumChannels);`
- L34 _public function_ `FORCEINLINE int32 GetNumFrames() const`
- L35 _public prototype_ `void SetNumFrames(int32 InNumFrames);`
- L37 _public prototype_ `FAudioBufferConfig GetInterleavedConfig() const;`
- L39 _public prototype_ `FAudioBufferConfig GetDeinterleavedConfig() const;`
- L41 _public function_ `FORCEINLINE bool GetIsInterleaved() const`
- L43 _public function_ `FORCEINLINE EAudioBufferChannelLayout GetChannelLayout() const`
- L44 _public prototype_ `void SetChannelLayout(EAudioBufferChannelLayout InChannelLayout);`
- L46 _public function_ `FORCEINLINE uint32 GetChannelMask() const`
- L47 _public prototype_ `void SetChannelMask(uint32 InChannelMask);`
- L49 _public prototype_ `bool operator==(const FAudioBufferConfig&) const;`
- L52 _private member_ `float SampleRate;`
- L53 _private member_ `int32 NumChannels;`
- L54 _private member_ `int32 NumFrames;`
- L55 _private member_ `uint32 ChannelMask;`
- L56 _private member_ `bool Interleaved;`
- L57 _private member_ `EAudioBufferChannelLayout ChannelLayout;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API HARMONIXDSP_API`
- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioBufferConfig, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioBufferConfig, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioBufferConstants.h` (Public)


#### enum `EAudioBufferChannelLayout`  
`enum class EAudioBufferChannelLayout : uint8`  
_L10-24_
- L12 _public enumerator_ `Raw`
- L13 _public enumerator_ `Mono`
- L14 _public enumerator_ `Stereo`
- L15 _public enumerator_ `StereoPointOne`
- L16 _public enumerator_ `Quad`
- L17 _public enumerator_ `QuadPointOne`
- L18 _public enumerator_ `Five`
- L19 _public enumerator_ `FivePointOne`
- L20 _public enumerator_ `SevenPointOne`
- L21 _public enumerator_ `AmbisonicOrderOne`
- L22 _public enumerator_ `Num`
- L23 _public enumerator_ `UnsupportedFormat`

#### enum `ESpeakerChannelAssignment`  
`enum class ESpeakerChannelAssignment : uint8`  
_L27-50_
- reflection: `UENUM()`
- L29 _public enumerator_ `LeftFront`
- L30 _public enumerator_ `RightFront`
- L31 _public enumerator_ `Center`
- L32 _public enumerator_ `LFE`
- L33 _public enumerator_ `LeftSurround`
- L34 _public enumerator_ `RightSurround`
- L35 _public enumerator_ `LeftRear`
- L36 _public enumerator_ `RightRear`
- L37 _public enumerator_ `FrontPair`
- L38 _public enumerator_ `CenterAndLFE`
- L39 _public enumerator_ `SurroundPair`
- L40 _public enumerator_ `RearPair`
- L41 _public enumerator_ `AmbisonicW`
- L42 _public enumerator_ `AmbisonicX`
- L43 _public enumerator_ `AmbisonicY`
- L44 _public enumerator_ `AmbisonicZ`
- L45 _public enumerator_ `AmbisonicWXPair`
- L46 _public enumerator_ `AmbisonicYZPair`
- L47 _public enumerator_ `UnspecifiedMono`
- L48 _public enumerator_ `Num UMETA(Hidden)`
- L49 _public enumerator_ `Invalid UMETA(Hidden)`

#### enum `ESpeakerMask::Type`  
`enum Type`  
_L58-92_
- L60 _public enumerator_ `LeftFront = 1 << (uint32)ESpeakerChannelAssignment::LeftFront`
- L61 _public enumerator_ `RightFront = 1 << (uint32)ESpeakerChannelAssignment::RightFront`
- L62 _public enumerator_ `Center = 1 << (uint32)ESpeakerChannelAssignment::Center`
- L63 _public enumerator_ `LFE = 1 << (uint32)ESpeakerChannelAssignment::LFE`
- L64 _public enumerator_ `LeftSurround = 1 << (uint32)ESpeakerChannelAssignment::LeftSurround`
- L65 _public enumerator_ `RightSurround = 1 << (uint32)ESpeakerChannelAssignment::RightSurround`
- L66 _public enumerator_ `LeftRear = 1 << (uint32)ESpeakerChannelAssignment::LeftRear`
- L67 _public enumerator_ `RightRear = 1 << (uint32)ESpeakerChannelAssignment::RightRear`
- L68 _public enumerator_ `AmbisonicWAssigned = 1 << (uint32)ESpeakerChannelAssignment::AmbisonicW`
- L69 _public enumerator_ `AmbisonicXAssigned = 1 << (uint32)ESpeakerChannelAssignment::AmbisonicX`
- L70 _public enumerator_ `AmbisonicYAssigned = 1 << (uint32)ESpeakerChannelAssignment::AmbisonicY`
- L71 _public enumerator_ `AmbisonicZAssigned = 1 << (uint32)ESpeakerChannelAssignment::AmbisonicZ`
- L74 _public enumerator_ `AmbisonicWRemapped = 1 << (uint32)ESpeakerChannelAssignment::LeftFront` — -- NOTE: Ambisonics live in the first 4 channels of an audio buffer, so here we play a game with the mask!
- L76 _public enumerator_ `AmbisonicXRemapped = 1 << (uint32)ESpeakerChannelAssignment::RightFront` — -- NOTE: Ambisonics live in the first 4 channels of an audio buffer, so here we play a game with the mask!
- L78 _public enumerator_ `AmbisonicYRemapped = 1 << (uint32)ESpeakerChannelAssignment::Center` — -- NOTE: Ambisonics live in the first 4 channels of an audio buffer, so here we play a game with the mask!
- L80 _public enumerator_ `AmbisonicZRemapped = 1 << (uint32)ESpeakerChannelAssignment::LFE` — -- NOTE: Ambisonics live in the first 4 channels of an audio buffer, so here we play a game with the mask!
- L82 _public enumerator_ `UnspecifiedMono = 1 << (uint32)ESpeakerChannelAssignment::UnspecifiedMono`
- L83 _public enumerator_ `Stereo = LeftFront | RightFront`
- L84 _public enumerator_ `AmbisonicAssigned = AmbisonicWAssigned | AmbisonicXAssigned | AmbisonicYAssigned | AmbisonicZAssigned`
- L85 _public enumerator_ `AmbisonicRemapped = AmbisonicWRemapped | AmbisonicXRemapped | AmbisonicYRemapped | AmbisonicZRemapped`
- L86 _public enumerator_ `FourDotZero = LeftFront | RightFront | LeftSurround | RightSurround`
- L87 _public enumerator_ `FourDotOne = LeftFront | RightFront | LFE | LeftSurround | RightSurround`
- L88 _public enumerator_ `FiveDotZero = LeftFront | Center | RightFront | LeftSurround | RightSurround`
- L89 _public enumerator_ `FiveDotOne = LeftFront | Center | RightFront | LFE | LeftSurround | RightSurround`
- L90 _public enumerator_ `SevenDotOne = LeftFront | Center | RightFront | LFE | LeftSurround | RightSurround | LeftRear | RightRear`
- L91 _public enumerator_ `AllSpeakers = 0xFFFFFFFF`

#### Free symbols / members of external scopes

- L56 _namespace_ `namespace ESpeakerMask`
- L95 _namespace_ `namespace HarmonixDsp`
- L97 _namespace_ `namespace FAudioBuffer` (scope `HarmonixDsp`)
- L99 _variable_ `static const uint32 kMaxChannelsInAudioBuffer = 8;` (scope `HarmonixDsp::FAudioBuffer`)
- L101 _function_ `FORCEINLINE constexpr int32 GetNumChannelsInChannelLayout(EAudioBufferChannelLayout ChannelLayout)` (scope `HarmonixDsp::FAudioBuffer`)
- L119 _function_ `FORCEINLINE constexpr EAudioBufferChannelLayout GetDefaultChannelLayoutForChannelCount(uint32 ChannelCount)` (scope `HarmonixDsp::FAudioBuffer`)
- L136 _function_ `FORCEINLINE constexpr ESpeakerMask::Type GetChannelMaskForNumChannels(uint32 NumChannels)` (scope `HarmonixDsp::FAudioBuffer`)
- L154 _variable_ `const uint32 kLayoutHasSpeakerMasks[] = {` (scope `HarmonixDsp::FAudioBuffer`)
- L186 _variable_ `static const uint8 ChannelAssignmentSpeakerToMappedChannel[] = {` (scope `HarmonixDsp::FAudioBuffer`)
- L211 _variable_ `static const uint32 ChannelAssignmentSpeakerToMappedMasks[] = {` (scope `HarmonixDsp::FAudioBuffer`)
- L233 _variable_ `const float kLeftSpeakerPos_Stereo = UE_HALF_PI;` (scope `HarmonixDsp::FAudioBuffer`)
- L234 _variable_ `const float kLeftSpeakerPos_Quad = UE_HALF_PI / 2.0f;` (scope `HarmonixDsp::FAudioBuffer`)
- L235 _variable_ `const float kLeftSpeakerPos_Five = 0.523598775598f;` (scope `HarmonixDsp::FAudioBuffer`) — 30 degrees
- L236 _variable_ `const float kLeftSpeakerPos_Seven = 0.523598775598f;` (scope `HarmonixDsp::FAudioBuffer`) — 30 degrees
- L237 _variable_ `const float kRightSpeakerPos_Stereo = (2.0f * UE_PI) - kLeftSpeakerPos_Stereo;` (scope `HarmonixDsp::FAudioBuffer`)
- L238 _variable_ `const float kRightSpeakerPos_Quad = (2.0f * UE_PI) - kLeftSpeakerPos_Quad;` (scope `HarmonixDsp::FAudioBuffer`)
- L239 _variable_ `const float kRightSpeakerPos_Five = (2.0f * UE_PI) - kLeftSpeakerPos_Five;` (scope `HarmonixDsp::FAudioBuffer`) — -30 degrees
- L240 _variable_ `const float kRightSpeakerPos_Seven = (2.0f * UE_PI) - kLeftSpeakerPos_Seven;` (scope `HarmonixDsp::FAudioBuffer`) — -30 degrees
- L242 _variable_ `const float kLeftSurroundSpeakerPos_Stereo = kLeftSpeakerPos_Stereo;` (scope `HarmonixDsp::FAudioBuffer`)
- L243 _variable_ `const float kLeftSurroundSpeakerPos_Quad = UE_HALF_PI + (UE_HALF_PI / 2.0f);` (scope `HarmonixDsp::FAudioBuffer`)
- L244 _variable_ `const float kLeftSurroundSpeakerPos_Five = 1.9198621771f;` (scope `HarmonixDsp::FAudioBuffer`) — 110 degrees
- L245 _variable_ `const float kLeftSurroundSpeakerPos_Seven = 1.5707963268f;` (scope `HarmonixDsp::FAudioBuffer`) — 90 degrees
- L246 _variable_ `const float kRightSurroundSpeakerPos_Stereo = (2.0f * UE_PI) - kLeftSurroundSpeakerPos_Stereo;` (scope `HarmonixDsp::FAudioBuffer`)
- L247 _variable_ `const float kRightSurroundSpeakerPos_Quad = (2.0f * UE_PI) - kLeftSurroundSpeakerPos_Quad;` (scope `HarmonixDsp::FAudioBuffer`)
- L248 _variable_ `const float kRightSurroundSpeakerPos_Five = (2.0f * UE_PI) - kLeftSurroundSpeakerPos_Five;` (scope `HarmonixDsp::FAudioBuffer`) — -110 degrees
- L249 _variable_ `const float kRightSurroundSpeakerPos_Seven = (2.0f * UE_PI) - kLeftSurroundSpeakerPos_Seven;` (scope `HarmonixDsp::FAudioBuffer`) — -90 degrees
- L251 _variable_ `const float kLeftRearSpeakerPos_Stereo = kLeftSurroundSpeakerPos_Stereo;` (scope `HarmonixDsp::FAudioBuffer`)
- L252 _variable_ `const float kLeftRearSpeakerPos_Quad = 2.617993878f;` (scope `HarmonixDsp::FAudioBuffer`) — 150 degrees
- L253 _variable_ `const float kLeftRearSpeakerPos_Five = 2.617993878f;` (scope `HarmonixDsp::FAudioBuffer`) — "
- L254 _variable_ `const float kLeftRearSpeakerPos_Seven = 2.617993878f;` (scope `HarmonixDsp::FAudioBuffer`) — "
- L255 _variable_ `const float kRightRearSpeakerPos_Stereo = (2.0f * UE_PI) - kLeftRearSpeakerPos_Stereo;` (scope `HarmonixDsp::FAudioBuffer`)
- L256 _variable_ `const float kRightRearSpeakerPos_Quad = (2.0f * UE_PI) - kLeftRearSpeakerPos_Quad;` (scope `HarmonixDsp::FAudioBuffer`) — -150 degrees
- L257 _variable_ `const float kRightRearSpeakerPos_Five = (2.0f * UE_PI) - kLeftRearSpeakerPos_Five;` (scope `HarmonixDsp::FAudioBuffer`) — "
- L258 _variable_ `const float kRightRearSpeakerPos_Seven = (2.0f * UE_PI) - kLeftRearSpeakerPos_Seven;` (scope `HarmonixDsp::FAudioBuffer`) — "
- L260 _variable_ `const float kDefaultSpeakerAzimuths[(uint8)EAudioBufferChannelLayout::Num][8] = { { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, { kLeftSpeakerPos_Stereo, kRightSpeakerPos_Stereo, 0.0f, 0.0f, kLeftSurroundSpeakerPos_Stereo, kRightSurroundSpeakerPos_Stereo, kLeftRearSpeakerPos_Stereo, kRightRearSpeakerPos_Stereo }, { kLeftSpeakerPos_Stereo, kRightSpeakerPos_Stereo, 0.0f,` (scope `HarmonixDsp::FAudioBuffer`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioDataRenderer.h` (Public)


#### class `IAudioDataRenderer`  
`class IAudioDataRenderer : public TSharedFromThis<IAudioDataRenderer>`  
_L20-72_
- inherits: `TSharedFromThis<IAudioDataRenderer>`
- L33 _public prototype_ `virtual ~IAudioDataRenderer() = default;`
- L36 _public function_ `virtual void SetAudioData(TSharedRef<FSoundWaveProxy> SoundWaveProxy, const FSettings& InSettings)` — `UE_DEPRECATED(5.8, "Mutable get/set is deprecated, please call SetSoundWaveData() instead")`
- L39 _public function_ `virtual const TSharedPtr<FSoundWaveProxy> GetAudioData() const` — `UE_DEPRECATED(5.8, "Mutable get/set is deprecated, please call GetSoundWaveData() instead")`
- L41 _public prototype_ `virtual void SetSoundWaveData(const TSharedRef<const FSoundWaveData>& InSoundWaveData, const FSettings& InSettings);`
- L42 _public prototype_ `virtual TSharedPtr<const FSoundWaveData> GetSoundWaveData() const;`
- L44 _public prototype_ `virtual void Reset() = 0;`
- L47 _public prototype_ `virtual void MigrateToSampler(const FFusionSampler* InSampler) = 0;`
- L49 _public prototype_ `virtual void SetFrame(uint32 InFrameNum) = 0;`
- L51 _public prototype_ `virtual double Render(TAudioBuffer<float>& OutBuffer, double InPos, int32 InMaxFrame, double InResampleInc, double InPitchShift, double InSpeed, bool MaintainPitchWhenSpeedChanges, const FGainMatrix& InGain) = 0;`
- L54 _public prototype_ `virtual double RenderUnshifted(TAudioBuffer<float>& OutBuffer, double InPos, int32 InMaxFrame, double InInc, const FGainMatrix& InGain) = 0;`
- L71 _protected prototype_ `double CalculateLerpData(FLerpData* LerpArray, int32 InNumPoints, uint32 InNumOutFrames, double InPos, int32 InMaxFrame, double Inc) const;`

#### struct `IAudioDataRenderer::FSettings`  
`struct FSettings`  
_L25-31_
- desc: Settings for a AudioDataRenderer.
- L27 _public member_ `TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> Shifter = nullptr;`
- L28 _public member_ `const FTimeStretchConfig* ShifterSettings = nullptr;`
- L29 _public member_ `const TArray<FTrackChannelInfo>* TrackChannelInfo = nullptr;`
- L30 _public member_ `const FFusionSampler* Sampler = nullptr;`

#### struct `IAudioDataRenderer::FLerpData`  
`struct FLerpData`  
_L58-69_
- L60 _public member_ `uint32 PosA;`
- L61 _public member_ `uint32 PosB;`
- L64 _public member_ `uint32 PosARelative;` — pos a and b Relative to start position, and never loop
- L65 _public member_ `uint32 PosBRelative;`
- L67 _public member_ `float WeightA;`
- L68 _public member_ `float WeightB;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixAudioDataRenderer, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixAudioDataRenderer, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/AudioUtility.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace AudioRendering`
- L9 _variable_ `static const int32 kFramesPerRenderBuffer = 128;` (scope `AudioRendering`)
- L10 _variable_ `static const int32 kMicroSliceSize = 4;` (scope `AudioRendering`) — TODO HX_AUDIO_MICRO_SLICE_SIZE
- L11 _variable_ `static const float kMicroFadeMs = 25.0f;` (scope `AudioRendering`)
- L12 _variable_ `static const float kMicroFadeSec = kMicroFadeMs / 1000.0f;` (scope `AudioRendering`)
- L15 _namespace_ `namespace HarmonixDsp`
- L18 _variable_ `static const float kDbMin = -10000.0f;` (scope `HarmonixDsp`) — ridiculously small minimum:
- L20 _variable_ `static const float kDbSilence = -96.0f;` (scope `HarmonixDsp`) — reasonable minimum value for volume in Db
- L22 _variable_ `static const float kDbMax = 12.0f;` (scope `HarmonixDsp`) — reasonable maximum value for volume in Db
- L24 _variable_ `const float kCentsPerOctave = 1200.0f;` (scope `HarmonixDsp`)
- L25 _variable_ `const float kOctavesPerCent = 1.0f / kCentsPerOctave;` (scope `HarmonixDsp`)
- L32 _variable_ `const float kTinyGain = 0.00001f;` (scope `HarmonixDsp`) — TODO? SMALL_NUMBER = 1.e-8f; KINDA_SMALL_NUMBER = 1.e-4f; kTinyGain = 1.e-5f though... could we use either of these?
- L34 _function_ `inline float Log10(float Value)` (scope `HarmonixDsp`)
- L39 _function_ `inline double Log10(double Value)` (scope `HarmonixDsp`)
- L44 _function_ `inline float ClampDB(float dB)` (scope `HarmonixDsp`)
- L49 _function_ `inline float DBToLinear(float dB)` (scope `HarmonixDsp`)
- L54 _function_ `inline int8 DBToMidiLinear(float dB)` (scope `HarmonixDsp`)
- L60 _function_ `inline float LinearToDB(float Gain)` (scope `HarmonixDsp`)
- L70 _function_ `inline float MidiLinearToDB(int8 Level ) { if (Level == 0) { return kDbSilence; } const float Max = static_cast<float>(MAX_int8); return 40.0f * Log10((float)Level / Max); } inline float Midi14BitLinearToDB(int32 Level ) { if (Level == 0) { return kDbSilence; } const float Max = static_cast<float>(MAX_int16 / 2); return 40.0f * Log10((float)Level / Max); }` (scope `HarmonixDsp`)
- L80 _function_ `inline float Midi14BitLinearToDB(int32 Level ) { if (Level == 0) { return kDbSilence; } const float Max = static_cast<float>(MAX_int16 / 2); return 40.0f * Log10((float)Level / Max); }` (scope `HarmonixDsp`)
- L91 _function_ `inline float dBFS(float Linear)` (scope `HarmonixDsp`) — decibels relative to full scale
- L109 _function_ `inline float FRandSample()` (scope `HarmonixDsp`)
- L117 _function_ `inline void PanToGainsConstantPower(float Pan, float& OutLeftGain, float& OutRightGain)` (scope `HarmonixDsp`)
- L133 _prototype_ `float MapLinearToDecibelRange(float ValueLinear, float MaxDecibels, float RangeDecibels);` (scope `HarmonixDsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Containers/TypedParameter.h` (Public)


#### enum `EParameterType`  
`enum class EParameterType : uint8`  
_L18-35_
- reflection: `UENUM()`
- desc: constrain the types allowed for TypedVariant simplify the blueprint customization and ui/ux
- L20 _public enumerator_ `Bool UMETA(DisplayName = "bool")`
- L21 _public enumerator_ `Double UMETA(DisplayName = "double")`
- L22 _public enumerator_ `Float UMETA(DisplayName = "float")`
- L23 _public enumerator_ `Int8 UMETA(DisplayName = "int8")`
- L24 _public enumerator_ `Int16 UMETA(DisplayName = "int16")`
- L25 _public enumerator_ `Int32 UMETA(DisplayName = "int32")`
- L26 _public enumerator_ `Int64 UMETA(DisplayName = "int64")`
- L27 _public enumerator_ `Name UMETA(DisplayName = "FName")`
- L28 _public enumerator_ `String UMETA(DisplayName = "FString")`
- L29 _public enumerator_ `UInt8 UMETA(DisplayName = "uint8")`
- L30 _public enumerator_ `UInt16 UMETA(DisplayName = "uint16")`
- L31 _public enumerator_ `UInt32 UMETA(DisplayName = "uint32")`
- L32 _public enumerator_ `UInt64 UMETA(DisplayName = "uint64")`
- L33 _public enumerator_ `Num UMETA(Hidden)`
- L34 _public enumerator_ `Invalid UMETA(Hidden)`

#### struct `FTypedParameter`  
`struct FTypedParameter`  
_L50-181_
- reflection: `USTRUCT()`
- desc: Wrapper for FVariant, an extensible union of multiple types exposed to blueprints as a "Type Parameter", which in blueprints: - allows the user to select the type the parameter represents - assign the value for the type We can then retrieve the underlying value by checking what type is stored and reading the value accordingly Serializes as an FVariant, which serializes the value as a byte array.
- L55 _public function_ `FTypedParameter() : Value(FVariant(int(0)))` — default to int type
- L58 _public function_ `template<typename T> FTypedParameter(T InValue)`
- L71 _public function_ `template<typename T> T GetValue() const` — Template method for getting the stored value asserts that value type is valid and matches @return Value as type T
- L87 _public function_ `template<typename T> void SetValue(T InValue)` — Template method for setting the stored value asserts that the value type is supported overwrites current value type with new value type @param InValue new value to assign
- L101 _public function_ `template<typename T> bool IsType() const` — Template method to check type matches @return whether the type T matches the type represented by this parameter
- L112 _public function_ `bool IsType(EParameterType InType) const` — Same as this->GetType() == InType; @return whether the EParameterType matches the type represented by this parameter
- L118 _public function_ `template<typename T> void SetType()`
- L131 _public prototype_ `void SetType(EParameterType Type);` — Set the type this Parameter represents will reset the value to the default for the type only if the type is different @param Type - the new type
- L136 _public prototype_ `EParameterType GetType() const;` — Gets the type this parameter represents
- L139 _public prototype_ `bool Serialize(FArchive& Ar);` — custom struct serialization
- L142 _public function_ `template<typename T> static bool FindMappedValue(const TMap<FName, FTypedParameter>& ParameterMap, FName Name, T& OutValue)`
- L157 _private function_ `static constexpr EParameterType FromVariantType(EVariantTypes VariantType)`
- L178 _private member_ `FVariant Value;`
- L180 _private member_ `static const uint8 kVersion = 0;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTypedParameter> : public TStructOpsTypeTraitsBase2<FTypedParameter>`  
_L184-190_
- inherits: `TStructOpsTypeTraitsBase2<FTypedParameter>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L187-189_

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXDSP_API`
- L188 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anone435ddf70103`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/BiquadFilter.h` (Public)


#### class `Harmonix::Dsp::Effects::FBiquadFilterCoefs`  
`class FBiquadFilterCoefs`  
_L33-145_
- desc: coefficients for difference function y(n) = B0*x(n)+B1*x(n-1)+B2*x(n-2) -A1*y(n-1)-A2*y(n-2) or in the z domain Y(z)    B0 + B1*z^-1 + B2*z^-2 H(z) = ---- =  ---------------------- X(x)     1 + A1*z^-1 + A2*z^-2 a0 is assumed to be 1.0.
- L37 _public function_ `FBiquadFilterCoefs(float B0Gain = 1.0f) : B0(B0Gain) , B1(0.0f) , B2(0.0f) , A1(0.0f) , A2(0.0f) , SR(1.0f)`
- L46 _public function_ `FBiquadFilterCoefs(const FBiquadFilterSettings& InSettings, float Fs)`
- L52 _public prototype_ `void GetMagnitudeResponse(float const* InFrequencies, int32 InNumFreq, float* OutResopnse);`
- L53 _public prototype_ `void MakeFromSettings(const FBiquadFilterSettings& InSettings);`
- L54 _public function_ `void MakeFromSettings(const FBiquadFilterSettings& InSettings, float Fs)`
- L60 _public function_ `void Flatten()`
- L69 _public function_ `bool IsNoop() const`
- L74 _public function_ `bool operator==(const FBiquadFilterCoefs& Other) const`
- L84 _public function_ `bool operator!=(const FBiquadFilterCoefs& Other) const`
- L89 _public function_ `FBiquadFilterCoefs operator+(const FBiquadFilterCoefs& Other) const`
- L100 _public function_ `FBiquadFilterCoefs operator-(const FBiquadFilterCoefs& Other) const`
- L111 _public function_ `FBiquadFilterCoefs operator*(double Scale) const`
- L123 _public prototype_ `bool IsStable() const;`
- L126 _public member_ `double B0;` — feedforward
- L127 _public member_ `double B1;`
- L128 _public member_ `double B2;`
- L131 _public member_ `double A1;` — feedback;
- L132 _public member_ `double A2;`
- L134 _public member_ `double SR;`
- L137 _private prototype_ `void GetPoles(TComplex<double>& OutP1, TComplex<double>& OutP2) const;`
- L139 _private prototype_ `void MakeLowPassCoefs(float F0, float Q);`
- L140 _private prototype_ `void MakeHighPassCoefs(float F0, float Q);`
- L141 _private prototype_ `void MakeBandPassCoefs(float F0, float Q);`
- L142 _private prototype_ `void MakePeakingCoefs(float F0, float dbGain, float Q);`
- L143 _private prototype_ `void MakeLowShelfCoefs(float F0, float dbGain, float Q);`
- L144 _private prototype_ `void MakeHighShelfCoefs(float F0, float dbGain, float Q);`

#### struct `Harmonix::Dsp::Effects::TBiquadFilter`  
`template<typename T> struct TBiquadFilter`  
_L148-300_
- L150 _public function_ `TBiquadFilter()`
- L151 _public prototype_ `virtual ~TBiquadFilter() = default;`
- L153 _public function_ `void ResetState()`
- L159 _public function_ `float Filter(float In, const FBiquadFilterCoefs& InCoefs)`
- L180 _public function_ `void Process(float const* input, float* output, uint32 InNumSamples, const FBiquadFilterCoefs& InCoefs, double InGain = 1.0)`
- L218 _public function_ `void ProcessTransposed(float const* input, float* output, uint32 InNumSamples, const FBiquadFilterCoefs& InCoefs, double InGain = 1.0)`
- L253 _public function_ `void ProcessInterleaved(TDynamicStridePtr<float>& input, TDynamicStridePtr<float>& output, int32 InNumSamples, const FBiquadFilterCoefs& InCoefs, double InGain = 1.0)`
- L298 _private member_ `T FF1;` — we should keep around the state for each filter that is the stuff that makes it distinct from other filters typedef float T; typedef double T;
- L299 _private member_ `T FF2;`

#### class `Harmonix::Dsp::Effects::TMultipassBiquadFilter`  
`template<typename T, int32 Num> class TMultipassBiquadFilter`  
_L306-443_
- L310 _public function_ `TMultipassBiquadFilter()`
- L311 _public prototype_ `~TMultipassBiquadFilter() = default;`
- L313 _public function_ `void ResetState()`
- L318 _public function_ `void Process(float const* input, float* output, uint32 InNumSamples, const FBiquadFilterCoefs& InCoefs, double InGain = 1.0, int32 InNumPasses = Num)`
- L380 _public function_ `void ProcessInterleaved(TDynamicStridePtr<float>& input, TDynamicStridePtr<float>& output, int32 InNumSamples, const FBiquadFilterCoefs& InCoefs, double InGain = 1.0, int32 InNumPasses = Num)`
- L442 _private member_ `T History[2 * Num];`

#### class `Harmonix::Dsp::Effects::TMultiChannelBiquadFilter`  
`template<typename T, int32 COUNT> class TMultiChannelBiquadFilter : public TBiquadFilter<T>`  
_L450-711_
- inherits: `TBiquadFilter<T>`
- L453 _public function_ `TMultiChannelBiquadFilter()`
- L459 _public prototype_ `virtual ~TMultiChannelBiquadFilter() = default;`
- L462 _public function_ `void Prepare(float InSampleRate, float InRampTimeMs = -1.0f, float InRampCallsPerSec = -1.0f, bool InAdjustRampTimeByOctaves = false)` — this prepares a filter to the default settings not default coefs...
- L496 _public function_ `void ProcessInterleaved(float* input, float* output, int32 NumSamples, int32 NumChannels, int32 NumActiveChannels, float InGain = 1.0f)`
- L525 _public function_ `void ProcessInterleavedInPlace(float* InOutData, int32 NumSamples, int32 NumChannels, int32 NumActiveChannels, float InGain = 1.0f)`
- L552 _public function_ `void SnapSettings()`
- L560 _public function_ `void Flatten(bool Snap)`
- L575 _public function_ `void ResetState()`
- L584 _public function_ `const FBiquadFilterSettings& GetSettings() const`
- L586 _public function_ `void SetTargetGain(float InGain, bool Snap)`
- L607 _public function_ `void SetFreqTarget(float InTarget)`
- L625 _public function_ `void SetQTarget(float InTarget)`
- L642 _public function_ `void SetEnabled(bool InEnabled)`
- L643 _public function_ `void SetType(EBiquadFilterType InType)`
- L644 _public function_ `float GetGainTarget()`
- L645 _public function_ `float GetFreqTarget()`
- L646 _public function_ `float GetQTarget()`
- L647 _public function_ `bool GetIsEnabled()`
- L648 _public function_ `EBiquadFilterType GetType()`
- L651 _public function_ `void UpdateCoefsFromSettings()`
- L657 _public function_ `void SetSettingsTarget(const FBiquadFilterSettings& InTarget)`
- L670 _private function_ `void ApplySettingsFromRampers()`
- L677 _private function_ `void RampSettings()`
- L689 _private member_ `float SampleRate = 44100.0f;`
- L690 _private member_ `float MaxFreq = 20000.0f;`
- L691 _private member_ `int32 FramesPerRamp;`
- L692 _private member_ `float RampTimePerOctave;`
- L693 _private member_ `bool AdjustRampTimeByOctaves;`
- L694 _private member_ `float TrueRPS;`
- L695 _private member_ `bool IsFirstTimeThrough = true;`
- L696 _private member_ `TBiquadFilter<T> FilterStates[COUNT];`
- L698 _private member_ `TLinearRamper<float> FreqRamper;`
- L699 _private member_ `TLinearRamper<float> QRamper;`
- L700 _private member_ `TLinearRamper<float> GainRamper;`
- L701 _private member_ `FBiquadFilterSettings Settings;`
- L703 _private member_ `FBiquadFilterCoefs Coefs;`
- L706 _private member_ `const float kDefaultRampsPerSec = 4800.0f;` — 20 samples at 48k
- L709 _private member_ `const float kDefaultRampTimeMs = 80.0f;` — 120 increments at 48k
- L710 _private member_ `const float kMinFreq = 20.0f;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Harmonix`
- L17 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L17 _namespace_ `namespace Effects` (scope `Harmonix::Dsp`)
- L303 _typedef_ `typedef TBiquadFilter<float> FBiquadFilter;` (scope `Harmonix::Dsp::Effects`) — declare FBiquadFilter for compatibility reasons. And saves some typing

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/Delay.h` (Public)


#### class `Harmonix::Dsp::Effects::FDelay`  
`class FDelay`  
_L21-226_
- L29 _public member_ `inline static constexpr int32 AbsoluteMaxChannels = 12;` — The max number of channels we expect to support with the delay
- L31 _public prototype_ `FDelay();`
- L33 _public prototype_ `void Prepare(float InSampleRate, uint32 InMaxChannels, float InMaxDelayTimeMs);`
- L35 _public prototype_ `void Unprepare();`
- L37 _public prototype_ `virtual ~FDelay();`
- L39 _public function_ `void Clear()`
- L51 _public function_ `void SetParamsToTargets()`
- L83 _public prototype_ `void Process(Audio::FMultichannelBufferView& InOutBuffer);`
- L85 _public prototype_ `float CalculateSecsToIdle();`
- L87 _public function_ `float GetSampleRate() const`
- L90 _public prototype_ `void SetDelaySeconds(float Seconds);` — units are either seconds or beats, depending on beat-sync setting
- L91 _public function_ `float GetDelaySeconds() const`
- L95 _public prototype_ `void SetTimeSyncOption(ETimeSyncOption Option);` — in beat-sync mode, delays are specified in beats, not seconds, and the delay must be notified when the tempo changes.
- L96 _public function_ `ETimeSyncOption GetTimeSyncOption() const`
- L98 _public prototype_ `void SetTempo(float Bpm);`
- L99 _public function_ `float GetTempo() const`
- L101 _public prototype_ `void SetSpeed(float Speed);`
- L102 _public function_ `float GetSpeed() const`
- L104 _public function_ `float GetOutputGain() const`
- L105 _public function_ `void SetOutputGain(const float InGain)`
- L107 _public prototype_ `void SetFeedbackGain(float Gain);`
- L108 _public prototype_ `float GetFeedbackGain() const;`
- L110 _public prototype_ `void SetWetGain(float Gain);`
- L111 _public prototype_ `float GetWetGain() const;`
- L113 _public prototype_ `void SetDryGain(float Gain);`
- L114 _public prototype_ `float GetDryGain() const;`
- L116 _public prototype_ `void SetWetFilterEnabled(bool Enabled);`
- L117 _public function_ `bool GetWetFilterEnabled() const`
- L119 _public prototype_ `void SetFeedbackFilterEnabled(bool Enabled);`
- L120 _public function_ `bool GetFeedbackFilterEnabled() const`
- L122 _public prototype_ `void SetFilterFreq(float Freq);`
- L123 _public function_ `float GetFilterFreq() const`
- L125 _public prototype_ `void SetFilterQ(float Q);`
- L126 _public function_ `float GetFilterQ() const`
- L128 _public prototype_ `void SetFilterType(EDelayFilterType Type);`
- L129 _public prototype_ `void SetFilterType(EBiquadFilterType Type);`
- L130 _public function_ `EBiquadFilterType GetFilterType() const`
- L132 _public prototype_ `void SetLfoEnabled(bool bEnabled);`
- L133 _public function_ `bool GetLfoEnabled() const`
- L135 _public prototype_ `void SetLfoTimeSyncOption(ETimeSyncOption Option);`
- L136 _public function_ `ETimeSyncOption GetLfoTimeSyncOption() const`
- L138 _public prototype_ `void SetLfoFreq(float Freq);`
- L139 _public function_ `float GetLfoFreq() const`
- L141 _public prototype_ `void SetLfoDepth(float InDepth);`
- L142 _public prototype_ `float GetLfoDepth() const;`
- L144 _public prototype_ `void SetStereoSpreadLeft(float Spread);`
- L145 _public function_ `float GetStereoSpreadLeft() const`
- L147 _public prototype_ `void SetStereoSpreadRight(float Spread);`
- L148 _public function_ `float GetStereoSpreadRight() const`
- L150 _public prototype_ `void SetStereoType(EDelayStereoType Type);`
- L151 _public function_ `EDelayStereoType GetStereoType() const`
- L161 _private prototype_ `void FreeUpMemory();`
- L163 _private prototype_ `void ApplyNewParams();`
- L165 _private prototype_ `void RampValues(int32 FrameNum);`
- L166 _private prototype_ `int32 GetPongCh(int32 ChannelIndex, int32 NumChannels) const;`
- L168 _private prototype_ `FORCEINLINE void ProcessInternal(float const X, const TDynamicStridePtr<float>& DelayLinePtr, FDelayOutput& OutDelay) const;`
- L170 _private member_ `int32 MaxChannels = 0;`
- L171 _private member_ `int32 ActiveChannels = 0;`
- L172 _private member_ `int32 SampleRate = 44100;`
- L174 _private member_ `uint32 MaxBlockSize = 0;`
- L176 _private member_ `uint32 Length = 0;`
- L177 _private member_ `Audio::FAlignedFloatBuffer DelayLineInterleaved;`
- L178 _private member_ `Audio::FAlignedFloatBuffer WetChannelInterleaved;`
- L179 _private member_ `uint32 DelayPos = 0;`
- L180 _private member_ `uint32 PosMask;`
- L182 _private member_ `float FeedbackGain = 0.0f;`
- L184 _private member_ `float WetGain = 1.0f;` — also known as feedforward
- L185 _private member_ `float DryGain = 1.0f;`
- L186 _private member_ `float DelayTimeSeconds = 0.5f;`
- L188 _private member_ `ETimeSyncOption TimeSyncOption = ETimeSyncOption::None;`
- L189 _private member_ `ETimeSyncOption LfoSyncOption = ETimeSyncOption::None;`
- L191 _private member_ `TLinearRamper<float> WetRamper;`
- L192 _private member_ `TLinearRamper<float> DryRamper;`
- L193 _private member_ `TLinearRamper<float> FeedbackRamper;`
- L194 _private member_ `TLinearRamper<float> DelayRamper;`
- L196 _private member_ `TMultiChannelBiquadFilter<double, 8> WetFilters;`
- L197 _private member_ `TMultiChannelBiquadFilter<double, 8> FeedbackFilters;`
- L199 _private member_ `TLinearRamper<float> DelaySpreadLeft;`
- L200 _private member_ `TLinearRamper<float> DelaySpreadRight;`
- L201 _private member_ `EDelayStereoType DelayType = EDelayStereoType::Default;`
- L203 _private member_ `Harmonix::Dsp::Modulators::FLfo Lfo;`
- L204 _private member_ `FLfoSettings LfoSettings;`
- L205 _private member_ `float LfoBaseFrequency = UE_SMALL_NUMBER;`
- L210 _private member_ `int32 FiveOneSurroundRotation[6] = { 1, 5, -1, -1, 0, 4 };` — info for bouncing between speakers belongs here rather than GainTable.cpp because this is specific to the ping pong delay effect
- L211 _private member_ `int32 SevenOneSurroundRotation[8] = { 1, 5, -1, -1, 0, 7, 4, 6 };`
- L212 _private member_ `int32 SevenOneFourSurroundRotation[12] = { 8, 9, -1, -1, -1, -1, 10, 11, 1, 7, 6, 0 };`
- L213 _private member_ `int32 FiveOneSurroundLRForce[6] = { 1, 0, -1, -1, 5, 4 };`
- L214 _private member_ `int32 SevenOneSurroundLRForce[8] = { 1, 0, -1, -1, 5, 4, 7, 6 };`
- L215 _private member_ `int32 SevenOneFourSurroundLRForce[12] = { 1, 0, -1, -1, 5, 4, 7, 6, 9, 8, 11, 10 };`
- L217 _private member_ `float MaxDelayInSamples{};`
- L218 _private member_ `float MaxDelayInMs{};`
- L219 _private member_ `float DelayInSamples{};`
- L220 _private member_ `float OutputGain{ 1.f };`
- L221 _private member_ `float TempoBpm{ 120.f };`
- L222 _private member_ `float Speed{ 1.f };`
- L223 _private member_ `bool CanSlamParams{ true };`
- L225 _private member_ `static constexpr int32 HopNum = 32;`

#### struct `Harmonix::Dsp::Effects::FDelay::FDelayOutput`  
`struct FDelayOutput`  
_L155-159_
- L157 _public member_ `float Delay;`
- L158 _public member_ `float Feedback;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Harmonix`
- L13 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L13 _namespace_ `namespace Effects` (scope `Harmonix::Dsp`)
- L16 _namespace_ `namespace Delay` (scope `Harmonix::Dsp::Effects`)
- L16 _namespace_ `namespace Tests` (scope `Harmonix::Dsp::Effects::Delay`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/DistortionV2.h` (Public)


#### class `Harmonix::Dsp::Effects::FDistortionV2`  
`class FDistortionV2`  
_L17-98_
- L20 _public prototype_ `FDistortionV2(uint32 SampleRate = 48000, uint32 MaxRenderBufferSize = 128);`
- L21 _public prototype_ `void Setup(uint32 SampleRate, uint32 MaxRenderBufferSize);`
- L22 _public prototype_ `virtual ~FDistortionV2() = default;`
- L24 _public prototype_ `void Process(const TArray<TArrayView<const float>>& InBuffer, const TArray<TArrayView<float>>& OutBuffer);`
- L26 _public prototype_ `void SetInputGainDb(float InGainDb, bool Snap = false);`
- L27 _public prototype_ `float GetInputGainDb() const;`
- L29 _public prototype_ `void SetInputGain(float InGain, bool Snap = false);`
- L30 _public function_ `float GetInputGain() const`
- L32 _public prototype_ `void SetOutputGainDb(float InGainDb, bool Snap = false);`
- L33 _public prototype_ `float GetOutputGainDb() const;`
- L35 _public prototype_ `void SetOutputGain(float InGain, bool Snap = false);`
- L36 _public function_ `float GetOutputGain() const`
- L38 _public prototype_ `void SetDryGainDb(float InGainDb, bool Snap = false);`
- L39 _public prototype_ `float GetDryGainDb() const;`
- L41 _public prototype_ `void SetDryGain(float InGain, bool Snap = false);`
- L42 _public function_ `float GetDryGain() const`
- L44 _public prototype_ `void SetWetGainDb(float InGainDb, bool Snap = false);`
- L45 _public prototype_ `float GetWetGainDb() const;`
- L47 _public prototype_ `void SetWetGain(float InGain, bool Snap = false);`
- L48 _public function_ `float GetWetGain() const`
- L50 _public prototype_ `void SetMix(float Mix, bool Snap = false);`
- L51 _public prototype_ `void SetDCOffset(float Offset, bool Snap = false);`
- L53 _public function_ `float GetDCOffset() const`
- L54 _public prototype_ `void SetType(uint8 InType);`
- L55 _public prototype_ `void SetType(EDistortionTypeV2 Type);`
- L56 _public function_ `EDistortionTypeV2 GetType() const`
- L57 _public prototype_ `void SetupFilter(int32 Index, const FDistortionFilterSettings& InSettings);`
- L58 _public function_ `int32 GetFilterPasses(int32 Index)`
- L59 _public prototype_ `void SetOversample(bool Oversample, int32 RenderBufferSizeFrames);`
- L60 _public function_ `bool GetOversample() const`
- L61 _public prototype_ `void SetSampleRate(uint32 SampleRate);`
- L63 _public prototype_ `void Setup(const FDistortionSettingsV2& Settings, uint32 SampleRate, uint32 RenderBufferSizeFrames, bool Snap);`
- L65 _public prototype_ `void Reset();`
- L67 _public member_ `static const int32 kMaxChannels = 8;`
- L68 _public member_ `static const int32 kMaxFilterPasses = 3;`
- L69 _public member_ `static const int32 kRampHops = 16;`
- L72 _private member_ `EDistortionTypeV2 Type;`
- L73 _private member_ `TLinearRamper<float> InputGain;`
- L74 _private member_ `TLinearRamper<float> OutputGain;`
- L75 _private member_ `TLinearRamper<float> DCAdjust;`
- L76 _private member_ `TLinearRamper<float> DryGain;`
- L77 _private member_ `TLinearRamper<float> WetGain;`
- L78 _private member_ `bool FilterPreClip[FDistortionSettingsV2::kNumFilters];`
- L79 _private member_ `FBiquadFilterSettings FilterSettings[FDistortionSettingsV2::kNumFilters];`
- L80 _private member_ `TLinearRamper<float> FilterGain[FDistortionSettingsV2::kNumFilters];`
- L82 _private member_ `TLinearRamper<FBiquadFilterCoefs> FilterCoefs[FDistortionSettingsV2::kNumFilters];`
- L84 _private member_ `uint32 FilterPasses[kMaxFilterPasses];`
- L86 _private member_ `TMultipassBiquadFilter<double, kMaxFilterPasses> Filter[FDistortionSettingsV2::kNumFilters][kMaxChannels];`
- L88 _private member_ `FFirFilter32 OversampleFilterUp[kMaxChannels];`
- L89 _private member_ `FFirFilter32 OversampleFilterDown[kMaxChannels];`
- L90 _private member_ `bool DoOversampling;`
- L91 _private member_ `Audio::FAlignedFloatBuffer UpsampleBuffer;`
- L92 _private member_ `uint32 SampleRate;`
- L94 _private member_ `static const uint32 kNumFilterTaps = 32;`
- L95 _private member_ `static const float kOversamplingFilterTaps[kNumFilterTaps];`
- L97 _private member_ `mutable FCriticalSection SettingsLock;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXDSP_API`
- L14 _namespace_ `namespace Harmonix`
- L14 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L14 _namespace_ `namespace Effects` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/DjFilter.h` (Public)


#### class `Harmonix::Dsp::Effects::FDjFilter`  
`class FDjFilter`  
_L16-69_
- desc: @brief A filter that cross-fades between a low-pass filter, the dry signal, and a high-pass filter on one "knob".
- L25 _public member_ `Parameters::TParameter<float> Amount{ -1.0f, 1.0f, 0.0f };` — @brief The knob position. -1 to the dead zone will low-pass the signal. Dead zone to 1 will high-pass the signal. Within the dead zone will fade to dry.
- L30 _public member_ `Parameters::TParameter<float> Resonance{ 0.01f, 10.0f, 1.0f };` — @brief The filters' resonance
- L35 _public member_ `Parameters::TParameter<float> LowPassMinFrequency{ 20.0f, 20000.0f, 20.0f };` — @brief The frequency the low-pass will be at when Amount is set to -1
- L40 _public member_ `Parameters::TParameter<float> LowPassMaxFrequency{ 20.0f, 20000.0f, 10000.0f };` — @brief The frequency the low-pass will be at when Amount is set to -DeadZoneSize
- L45 _public member_ `Parameters::TParameter<float> HighPassMinFrequency{ 20.0f, 20000.0f, 20.0f };` — @brief The frequency the high-pass will be at when Amount is set to DeadZoneSize
- L50 _public member_ `Parameters::TParameter<float> HighPassMaxFrequency{ 20.0f, 20000.0f, 10000.0f };` — @brief The frequency the high-pass will be at when Amount is set to 1
- L55 _public member_ `Parameters::TParameter<float> DeadZoneSize{ 0.01f, 0.5f, 0.1f };` — @brief The portion of the Amount that will cross-fade between the filtered signal and the dry signal
- L57 _public prototype_ `explicit FDjFilter(float InSampleRate);`
- L59 _public prototype_ `void Reset(float InSampleRate);`
- L61 _public prototype_ `void Process(const Audio::FAlignedFloatBuffer& InBuffer, Audio::FAlignedFloatBuffer& OutBuffer);`
- L64 _private member_ `Audio::FStateVariableFilter Filter;`
- L65 _private member_ `float LastFrequency;`
- L66 _private member_ `float LastQ;`
- L67 _private member_ `float LastDryGain;`
- L68 _private member_ `float LastWetGain;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXDSP_API`
- L11 _namespace_ `namespace Harmonix`
- L11 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L11 _namespace_ `namespace Effects` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/FirFilter.h` (Public)


#### class `Harmonix::Dsp::Effects::FFirFilter`  
`class FFirFilter`  
_L14-73_
- desc: Finite Impulse Response filter, or (FIR) Filter, that can be used to perform filtering and other signal processing operations. The filter is defined by a set of "taps" which are coefficients that determine the shape of the filter's frequency response.
- L17 _public prototype_ `FFirFilter();`
- L19 _public prototype_ `virtual ~FFirFilter();`
- L35 _public prototype_ `virtual void Init(const float* InTaps, int32 InTapCount, bool InCopyTaps);` — Initializes the filter with the specified taps, which must have InTapCount elements. If InCopyTaps is true, the taps will be copied into a new buffer owned by the filter; otherwise, the filter will simply store a pointer to the input array. Any existing tap or history buffers will be freed. @param InTaps			the array of filter taps @param InTapCount		the number of filter taps @param InCopyTaps		whether to copy the taps into a new buffer
- L45 _public prototype_ `virtual void AddData(float* Input, int32 InCount);` — Adds the specified input data to the filter's history buffer. InCount elements will be added to the buffer, starting at the current history index. @param Input			the input data to add @param InCount		the number of input samples to add
- L53 _public prototype_ `virtual void AddData(float Input);` — Adds a single data point to the FIR filter, starting at the current history index @param Input			the input data to add
- L60 _public prototype_ `virtual float GetSample();` — Computes a filtered sample using the FIR filter. @return the filtered sample
- L65 _public prototype_ `void Reset();` — Resets the FIR filter.
- L68 _protected member_ `const float* Taps;`
- L69 _protected member_ `int32 TapCount;`
- L70 _protected member_ `bool OwnTaps;`
- L71 _protected member_ `float* History;`
- L72 _protected member_ `uint32 HistoryIndex;`

#### class `Harmonix::Dsp::Effects::FFirFilter32`  
`class FFirFilter32 : public FFirFilter`  
_L78-105_
- inherits: `FFirFilter`
- desc: A FIR Filter optimized for 32-tap coefficients.
- L89 _public prototype_ `virtual void Init(const float* InTaps, int32 InTapCount, bool InCopyTaps) override;` — Initializes the 32-tap FIR filter with the given taps. @param InTaps			the filter taps @param InTapCount		the number of filter taps (must be 32) @param InCopyTaps		whether to copy the taps or not
- L91 _public prototype_ `virtual void AddData(float* Input, int32 InCount) override;`
- L93 _public prototype_ `virtual void AddData(float Input) override;`
- L95 _public prototype_ `virtual float GetSample() override;`
- L104 _public prototype_ `void Upsample4x(float InSample, float* OutSamples);` — Inserts a new input sample to the filter, and generates 4 up-sampled output samples @param InSample		the new input sample to insert to the filter @param OutSamples		an array of length 4 to store the generated output samples

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Harmonix`
- L6 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L6 _namespace_ `namespace Effects` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/FourBiquads.h` (Public)


#### class `Harmonix::Dsp::Effects::FFourBiquads`  
`class FFourBiquads`  
_L14-140_
- L17 _public function_ `FFourBiquads() : B0(VectorSetFloat1(1.0f)) , B1(VectorSetFloat1(0.0f)) , B2(VectorSetFloat1(0.0f)) , A1(VectorSetFloat1(0.0f)) , A2(VectorSetFloat1(0.0f)) , S1(VectorSetFloat1(0.0f)) , S2(VectorSetFloat1(0.0f))`
- L28 _public function_ `void SetFilter( uint32 Index, float InB0, float InB1, float InB2, float InA1, float InA2 )`
- L50 _public function_ `VectorRegister4Float ProcessOne(VectorRegister4Float Sample)`
- L64 _public function_ `void Process(TArray<VectorRegister4Float>& Samples)`
- L95 _public function_ `void Process(const float* Input, int32 FrameCount, float** Output)`
- L123 _private function_ `void SetComponent(VectorRegister4Float& OutVector, uint32 Index, float Value)`
- L133 _private member_ `VectorRegister4Float B0;`
- L134 _private member_ `VectorRegister4Float B1;`
- L135 _private member_ `VectorRegister4Float B2;`
- L136 _private member_ `VectorRegister4Float A1;`
- L137 _private member_ `VectorRegister4Float A2;`
- L138 _private member_ `VectorRegister4Float S1;`
- L139 _private member_ `VectorRegister4Float S2;`

#### union `Harmonix::Dsp::Effects::FFourBiquads::Process::(anonymous)`  
``  
_L99-102_

#### Free symbols / members of external scopes

- L9 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogHarmonixFourBiquads, Log, All);`
- L11 _namespace_ `namespace Harmonix`
- L11 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L11 _namespace_ `namespace Effects` (scope `Harmonix::Dsp`)
- L100 _member_ `VectorRegister4Float Y;` (scope `Harmonix::Dsp::Effects::FFourBiquads::Process::__anon8590607f010a`)
- L101 _member_ `float YComponents[4];` (scope `Harmonix::Dsp::Effects::FFourBiquads::Process::__anon8590607f010a`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/Settings/BiquadFilterSettings.h` (Public)


#### enum `EBiquadFilterType`  
`enum class EBiquadFilterType`  
_L7-17_
- reflection: `UENUM()`
- L9 _public enumerator_ `LowPass UMETA(Json="low-pass")`
- L10 _public enumerator_ `HighPass UMETA(Json="high-pass")`
- L11 _public enumerator_ `BandPass UMETA(Json="band-pass")`
- L12 _public enumerator_ `Peaking UMETA(Json="peaking")`
- L13 _public enumerator_ `LowShelf UMETA(Json="low-shelf")`
- L14 _public enumerator_ `HighShelf UMETA(Json="high-shelf")`
- L15 _public enumerator_ `Num UMETA(Hidden)`
- L16 _public enumerator_ `None UMETA(Hidden)`

#### struct `FBiquadFilterSettings`  
`struct FBiquadFilterSettings`  
_L20-74_
- reflection: `USTRUCT()`
- L24 _public typedef_ `typedef int16 BFSPad;`
- L27 _public member_ `bool IsEnabled = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L30 _public member_ `EBiquadFilterType Type = EBiquadFilterType::LowPass;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L34 _public member_ `BFSPad Pad = 0;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")` — what's this?
- L37 _public member_ `float Freq = 630.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", DisplayName = "Freq (Hz)", Meta = (ClampMin = "20", ClampMax = "20000", UIMin = "20", UIMax = "20000"))`
- L40 _public member_ `float Q = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "0", ClampMax = "10", UIMin = "0", UIMax = "10"))`
- L43 _public member_ `float DesignedDBGain = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "-96", ClampMax = "12", UIMin = "-96", UIMax = "12"))`
- L45 _public function_ `FBiquadFilterSettings()`
- L46 _public function_ `FBiquadFilterSettings(EBiquadFilterType InType, float InFreq, float InQ, float InGain = 1.0f, bool InEnabled = true) : IsEnabled(InEnabled) , Type(InType) , Freq(InFreq) , Q(InQ) , DesignedDBGain(InGain)`
- L55 _public function_ `void ResetToDefaults()`
- L64 _public prototype_ `void GetMagnitudeResponse(float const* FrequenciesOfInterest, int32 NumFrequencies, float* OutMagnitudeResponse, float Fs);`
- L66 _public function_ `bool operator==(const FBiquadFilterSettings& Other)`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/Settings/BitCrusherSettings.h` (Public)


#### struct `FBitCrusherSettings`  
`struct FBitCrusherSettings`  
_L7-29_
- reflection: `USTRUCT()`
- L13 _public member_ `bool IsEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP")`
- L16 _public member_ `float InputGain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1"))`
- L19 _public member_ `float OutputGain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1"))`
- L22 _public member_ `float WetGain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1"))`
- L25 _public member_ `uint16 Crush = 4;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", DisplayName="Crush (Bit Depth)", Meta=(ClampMin="0", ClampMax = "15", UIMin="0", UIMax="15"))`
- L28 _public member_ `uint16 SampleHoldFactor = 5;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (ClampMin = "0", ClampMax = "16", UIMin = "0", UIMax = "16"))`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/Settings/DelaySettings.h` (Public)


#### enum `EDelayStereoType`  
`enum class EDelayStereoType : uint8`  
_L9-17_
- reflection: `UENUM()`
- L11 _public enumerator_ `Default`
- L12 _public enumerator_ `CustomSpread`
- L13 _public enumerator_ `PingPongForceLR`
- L14 _public enumerator_ `PingPongSum`
- L15 _public enumerator_ `PingPongIndividual`
- L16 _public enumerator_ `Num UMETA(Hidden)`

#### enum `EDelayFilterType`  
`enum class EDelayFilterType : uint8`  
_L20-26_
- reflection: `UENUM()`
- L22 _public enumerator_ `LowPass`
- L23 _public enumerator_ `HighPass`
- L24 _public enumerator_ `BandPass`
- L25 _public enumerator_ `Num UMETA(Hidden)`

#### struct `FDelaySettings`  
`struct FDelaySettings`  
_L29-87_
- reflection: `USTRUCT()`
- L35 _public member_ `bool IsEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L38 _public member_ `ETimeSyncOption TimeSyncOption = ETimeSyncOption::None;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L41 _public member_ `float TimeSeconds = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))`
- L44 _public member_ `float Tempo = 120.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "1", ClampMax = "240", UIMin = "0", UIMax = "240"))`
- L47 _public member_ `float DryGain = 0.5f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))`
- L50 _public member_ `float WetGain = 0.5f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))`
- L53 _public member_ `float FeedbackGain = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))`
- L56 _public member_ `bool EQEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L59 _public member_ `EDelayFilterType EQType = EDelayFilterType::LowPass;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L62 _public member_ `float EQFreq = 600.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", DisplayName = "EQ Freq (Hz)", Meta = (ClampMin = "20", ClampMax = "20000", UIMin = "20", UIMax = "20000"))`
- L65 _public member_ `float EQQ = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "0", ClampMax = "10", UIMin = "0", UIMax = "10"))`
- L68 _public member_ `bool LfoEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L71 _public member_ `ETimeSyncOption LfoTimeSyncOption = ETimeSyncOption::None;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L74 _public member_ `float LfoRate = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", DisplayName = "LFO Rate (Hz)", Meta = (ClampMin = "0.01", ClampMax = "40", UIMin = "0.01", UIMax = "40"))`
- L77 _public member_ `float LfoDepth = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", DisplayName = "LFO Depth", Meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))`
- L80 _public member_ `EDelayStereoType StereoType = EDelayStereoType::Default;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L83 _public member_ `float PanLeft = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", DisplayName = "Pan Left (%)", Meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))`
- L86 _public member_ `float PanRight = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", DisplayName = "Pan Right (%)", Meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/Settings/DistortionSettings.h` (Public)


#### struct `FDistortionFilterSettings`  
`struct FDistortionFilterSettings`  
_L9-21_
- reflection: `USTRUCT()`
- L14 _public member_ `bool FilterPreClip = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L17 _public member_ `FBiquadFilterSettings Filter;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L20 _public member_ `int32 NumPasses = 0;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "1", UIMax = "3", ClampMin = "1", ClampMax = "3"))`

#### enum `EDistortionTypeV1`  
`enum class EDistortionTypeV1`  
_L24-32_
- reflection: `UENUM()`
- L26 _public enumerator_ `Clean`
- L27 _public enumerator_ `Warm`
- L28 _public enumerator_ `Dirty`
- L29 _public enumerator_ `Soft`
- L30 _public enumerator_ `Asymmetric`
- L31 _public enumerator_ `Num UMETA(Hidden)`

#### struct `FDistortionSettingsV1`  
`struct FDistortionSettingsV1`  
_L35-63_
- reflection: `USTRUCT()`
- L41 _public member_ `static const uint32 kNumFilters = 3;`
- L44 _public member_ `bool IsEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L47 _public member_ `float InputGainDb = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta =(UIMin="-96.0", UIMax="12.0", ClampMin="-96.0", ClampMax="12"))`
- L50 _public member_ `float OutputGainDb = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "-96.0", UIMax = "12.0", ClampMin = "-96.0", ClampMax="12"))`
- L53 _public member_ `float DCAdjust = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "-1.0", UIMax = "1.0", ClampMin = "-1.0", ClampMax="1.0"))`
- L56 _public member_ `EDistortionTypeV1 Type = EDistortionTypeV1::Clean;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L59 _public member_ `bool Oversample = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L62 _public member_ `FDistortionFilterSettings Filters[kNumFilters];` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`

#### enum `EDistortionTypeV2`  
`enum class EDistortionTypeV2`  
_L66-77_
- reflection: `UENUM()`
- L68 _public enumerator_ `Clean`
- L69 _public enumerator_ `Warm`
- L70 _public enumerator_ `Clip`
- L71 _public enumerator_ `Soft`
- L72 _public enumerator_ `Asymmetric`
- L73 _public enumerator_ `Cruncher`
- L74 _public enumerator_ `CaptCrunch`
- L75 _public enumerator_ `Rectifier`
- L76 _public enumerator_ `Num UMETA(Hidden)`

#### struct `FDistortionSettingsV2`  
`struct FDistortionSettingsV2`  
_L80-114_
- reflection: `USTRUCT()`
- L86 _public member_ `static const uint32 kNumFilters = 3;`
- L89 _public member_ `bool IsEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L92 _public member_ `float InputGainDb = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "-96.0", UIMax = "12.0", ClampMin = "-96.0", ClampMax = "12"))`
- L95 _public member_ `float OutputGainDb = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "-96.0", UIMax = "12.0", ClampMin = "-96.0", ClampMax = "12"))`
- L98 _public member_ `float DryGain = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "0.0", UIMax = "0.0", ClampMin = "0.0", ClampMax = "1"))`
- L101 _public member_ `float WetGain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1"))`
- L104 _public member_ `float DCAdjust = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "-1.0", UIMax = "1.0", ClampMin = "-1.0", ClampMax = "1.0"))`
- L107 _public member_ `EDistortionTypeV2 Type = EDistortionTypeV2::Clean;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L110 _public member_ `bool Oversample = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L113 _public member_ `FDistortionFilterSettings Filters[kNumFilters];` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/Settings/VocoderSettings.h` (Public)


#### enum `EVocoderBandConfig`  
`enum class EVocoderBandConfig : uint8`  
_L7-18_
- reflection: `UENUM()`
- L9 _public enumerator_ `k4 = 0 UMETA(DisplayName = "4")`
- L10 _public enumerator_ `k8 UMETA(DisplayName = "8")`
- L11 _public enumerator_ `k16 UMETA(DisplayName = "16")`
- L12 _public enumerator_ `k32 UMETA(DisplayName = "32")`
- L13 _public enumerator_ `k64 UMETA(DisplayName = "64")`
- L14 _public enumerator_ `k128 UMETA(DisplayName = "128")`
- L15 _public enumerator_ `k256 UMETA(DisplayName = "256")`
- L16 _public enumerator_ `Num UMETA(Hidden)`
- L17 _public enumerator_ `None UMETA(Hidden)`

#### struct `FVocoderBandConfig`  
`struct FVocoderBandConfig`  
_L21-57_
- reflection: `USTRUCT()`
- L26 _public member_ `int32 BandCount = 0;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L29 _public member_ `float FrequencyRatio = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L32 _public member_ `FName Name;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L34 _public function_ `FVocoderBandConfig()`
- L36 _public function_ `FVocoderBandConfig(int32 InBandCount, float InFrequencyRatio, FName InName) : BandCount(InBandCount) , FrequencyRatio(InFrequencyRatio) , Name(InName)`
- L43 _public function_ `static const FVocoderBandConfig& Get(uint8 Index)`
- L49 _public function_ `static const FVocoderBandConfig& Get(EVocoderBandConfig BandConfig)`
- L56 _public member_ `static const FVocoderBandConfig sBandConfigs[(uint8)EVocoderBandConfig::Num];`

#### struct `FVocoderBand`  
`struct FVocoderBand`  
_L62-71_
- reflection: `USTRUCT()`
- L67 _public member_ `float Gain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", UIMax = "1", ClampMin="0", ClampMax="1"))`
- L70 _public member_ `bool Solo = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP")`

#### struct `FVocoderSettings`  
`struct FVocoderSettings`  
_L74-132_
- reflection: `USTRUCT()`
- L78 _public prototype_ `FVocoderSettings();`
- L81 _public member_ `bool IsEnabled = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP")`
- L84 _public member_ `int32 ModulatorIndex = 0;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", ClampMin = "0"))`
- L87 _public member_ `int32 ChannelCount = 1;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "1", ClampMin = "1", UIMax = "8", ClampMax = "8"))`
- L90 _public member_ `float SampleRate = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "40000", ClampMin = "40000", UIMax = "200000", ClampMax = "200000"))`
- L93 _public member_ `EVocoderBandConfig BandConfig = EVocoderBandConfig::k64;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP")`
- L96 _public member_ `bool Soloing = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP")`
- L99 _public member_ `int32 FrameCount = 0;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", ClampMin = "0"))`
- L102 _public member_ `float CarrierGain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L105 _public member_ `float ModulatorGain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L108 _public member_ `float CarrierThin = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L111 _public member_ `float ModulatorThin = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L114 _public member_ `float Attack = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", ClampMin = "0"))`
- L117 _public member_ `float Release = 0.0008f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", ClampMin = "0"))`
- L120 _public member_ `float HighEmphasis = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP")`
- L123 _public member_ `float Wet = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L126 _public member_ `float OutputGain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))`
- L129 _public member_ `TArray<FVocoderBand> Bands;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP")`
- L131 _public function_ `const FVocoderBandConfig& GetBandConfig() const`

#### Free symbols / members of external scopes

- L59 _macro_ `#define VOCODER_DEFAULT_BAND_CONFIG EVocoderBandConfig::k64;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Effects/TapeSS.h` (Public)


#### class `Harmonix::Dsp::Effects::FTapeStopStart`  
`class FTapeStopStart`  
_L9-70_
- L27 _public prototype_ `FTapeStopStart();`
- L29 _public prototype_ `void Prepare(float SampleRate, int32 MaxNumChannels, float MaxDecelerationSeconds);`
- L31 _public function_ `void Clear()`
- L38 _public prototype_ `EPhase Process(const TArray<const float*>& InChannelData, const TArray<float*>& OutChannelData, const int32 NumFrames);`
- L40 _public prototype_ `void SnapState(EState State);`
- L41 _public prototype_ `void SetState(EState State, float DurationSeconds);`
- L42 _public function_ `EState GetState() const`
- L43 _public function_ `float GetSpeed() const`
- L46 _private prototype_ `void CheckForStateUpdates();`
- L47 _private prototype_ `void SpeedUp(int32& FrameIndex, const TArray<const float*>& InChannelData, const TArray<float*>& OutChannelData, const int32 NumFrames);`
- L48 _private prototype_ `void SlowDown(int32& FrameIndex, const TArray<const float*>& InChannelData, const TArray<float*>& OutChannelData, const int32 NumFrames);`
- L50 _private member_ `int32 MaxNumChannels;`
- L51 _private member_ `int32 ActiveNumChannels;`
- L52 _private member_ `float SampleRate;`
- L54 _private member_ `TAudioBuffer<float> Buffer;`
- L55 _private member_ `int32 BufferWritePos;`
- L56 _private member_ `float BufferReadPos;`
- L58 _private member_ `int32 NumSamplesInFullRamp;`
- L59 _private member_ `int32 RampProgressInSamples;`
- L60 _private member_ `TArray<float> CrossfadeFloor;`
- L62 _private member_ `TLinearRamper<float> SRRamper;`
- L64 _private member_ `EState CurrentState;`
- L65 _private member_ `EState DesiredState;`
- L66 _private member_ `float RampTimeSeconds;`
- L68 _private member_ `static const int32 kHopNum = 4;`
- L69 _private member_ `static const int32 kCrossfadeSamps = 512;`

#### enum `Harmonix::Dsp::Effects::FTapeStopStart::EState`  
`enum class EState`  
_L13-17_
- L15 _public enumerator_ `Play`
- L16 _public enumerator_ `Stop`

#### enum `Harmonix::Dsp::Effects::FTapeStopStart::EPhase`  
`enum class EPhase`  
_L19-25_
- L21 _public enumerator_ `SpeedingUp`
- L22 _public enumerator_ `Playing`
- L23 _public enumerator_ `Stopped`
- L24 _public enumerator_ `SlowingDown`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Harmonix`
- L7 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L7 _namespace_ `namespace Effects` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/AliasFusionVoice.h` (Public)


#### class `FAliasFusionVoice`  
`class FAliasFusionVoice : public FFusionVoice`  
_L8-83_
- inherits: `FFusionVoice`
- L22 _public prototype_ `FAliasFusionVoice(FSingletonFusionVoicePool* InPool);`
- L23 _public prototype_ `FAliasFusionVoice(const FAliasFusionVoice& Other);`
- L25 _public prototype_ `virtual TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> GetPitchShifter() const override;`
- L27 _public prototype_ `virtual Harmonix::Dsp::Modulators::EAdsrStage GetAdsrStage() const override;`
- L28 _public prototype_ `virtual void SetPitchOffset(double InNumCents) override;`
- L30 _public prototype_ `virtual void AttackWithTargetNote( uint8 MidiNoteNumber, float InGain, int32 InEventTick, int32 InTriggerTick, double InStartPointMs = 0.0f, const char* InFilePath = nullptr) override;`
- L38 _public prototype_ `virtual void AttackWithTargetNote( uint8 MidiNoteNumber, float InGain, int32 InEventTick, int32 InTriggerTick, double InStartPointMs = 0.0f) override;`
- L46 _public prototype_ `virtual uint32 Process( uint32 SliceIndex, uint32 SubsliceIndex, float** Output, uint32 InNumChannels, uint32 InMaxNumSamples, float InSpeed = 1.0f, float InTempoBPM = 120.0f, bool MaintainPitchWhenSpeedChanges = false) override;`
- L55 _public function_ `virtual bool IsInUse() const override`
- L56 _public prototype_ `virtual void Release() override;`
- L57 _public prototype_ `virtual void FastRelease() override;`
- L58 _public prototype_ `virtual void Kill() override;`
- L59 _public prototype_ `virtual bool MatchesIDs(const FFusionSampler* InSampler, FMidiVoiceId InVoiceID, const FKeyzoneSettings* keyzone = nullptr) override;`
- L60 _public prototype_ `virtual bool UsesKeyzone(const FKeyzoneSettings* keyzone) const override;`
- L61 _public prototype_ `virtual void SetupLfo(uint8 Index, const FLfoSettings& InSettings) override;`
- L63 _public function_ `bool IsStartingOrRunning() const`
- L64 _public function_ `EState GetState() const`
- L66 _public prototype_ `void Activate(FFusionSampler* InSampler, FMidiVoiceId InVoiceID, FFusionVoice* InRealVoice, FRelinquishHandler Handler);`
- L68 _public function_ `FFusionVoice* GetRealVoice() const`
- L69 _public function_ `void ClearVoice()`
- L72 _public function_ `virtual bool IsAlias() const override`
- L73 _public function_ `virtual bool IsRendererForAlias() const override`
- L74 _public function_ `virtual bool HasBeenRelinquished() const override`
- L78 _private member_ `EState State = EState::Idle;`
- L79 _private member_ `FSingletonFusionVoicePool* VoicePool = nullptr;`
- L81 _private member_ `FFusionVoice* MyVoice = nullptr;` — Real voice doing the rendering
- L82 _private member_ `FFusionVoice::FRelinquishHandler RelinquishHandler;`

#### enum `FAliasFusionVoice::EState`  
`enum class EState`  
_L12-18_
- L14 _public enumerator_ `Idle`
- L15 _public enumerator_ `Starting`
- L16 _public enumerator_ `Running`
- L17 _public enumerator_ `Released`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/FusionPatch.h` (Public)


#### struct `FFusionPatchUserData`  
`struct FFusionPatchUserData`  
_L19-25_
- desc: Empty base class for data that will be passed along to the sampler
- L21 _public function_ `virtual ~FFusionPatchUserData()`
- L23 _public function_ `virtual void OnSamplerConnected(const FFusionSampler* Sampler)`
- L24 _public function_ `virtual void OnSamplerDisconnected(const FFusionSampler* Sampler)`

#### struct `FFusionPatchData`  
`struct FFusionPatchData`  
_L29-58_
- reflection: `USTRUCT(BlueprintType)`
- desc: User facing data of FusionPatch
- L38 _public function_ `FFusionPatchData()`
- L39 _public function_ `const TArray<FKeyzoneSettings>& GetKeyzones() const`
- L40 _public function_ `const FFusionPatchSettings& GetSettings() const`
- L41 _public prototype_ `void InitProxyData(const Audio::FProxyDataInitParams& InitParams);`
- L43 _public prototype_ `void ConnectSampler(const FFusionSampler* Sampler);`
- L44 _public prototype_ `void DisconnectSampler(const FFusionSampler* Sampler);`
- L49 _private member_ `TArray<FKeyzoneSettings> Keyzones;` — `UPROPERTY(EditAnywhere, Category="Keyzones")`
- L52 _private member_ `FFusionPatchSettings Settings;` — `UPROPERTY(EditAnywhere, Category="Settings")`
- L55 _private member_ `TArray<FFusionPatchSettings> Presets_DEPRECATED;` — `UPROPERTY()`
- L57 _private member_ `TSharedPtr<FFusionPatchUserData> UserData;`

#### enum `EFusionPatchAudioLoadResult`  
`enum class EFusionPatchAudioLoadResult : uint8`  
_L66-71_
- reflection: `UENUM(BlueprintType)`
- L68 _public enumerator_ `Success`
- L69 _public enumerator_ `Fail`
- L70 _public enumerator_ `Cancelled`

#### class `UFusionPatch`  
`class UFusionPatch : public UObject, public IAudioProxyDataFactory`  
_L79-151_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "Fusion Patch"))`
- inherits: `UObject,IAudioProxyDataFactory`
- L85 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams);` — IAudioProxyDataFactory
- L87 _public member_ `static const int32 kVoicePriorityNoSteal = 0;`
- L89 _public prototype_ `UFusionPatch();`
- L91 _public prototype_ `void UpdatePatch(const FFusionPatchData& InPatchData);`
- L93 _public function_ `const FFusionPatchSettings& GetSettings() const`
- L94 _public prototype_ `void UpdateSettings(const FFusionPatchSettings& InSettings);`
- L96 _public function_ `const TArray<FKeyzoneSettings>& GetKeyzones() const`
- L97 _public function_ `int32 GetNumKeyzones() const`
- L98 _public prototype_ `void UpdateKeyzones(const TArray<FKeyzoneSettings>& NewKeyzones);`
- L100 _public function_ `TSharedPtr<FFusionPatchUserData> GetUserData()`
- L101 _public prototype_ `void SetUserData(TSharedRef<FFusionPatchUserData> UserData);`
- L106 _public member_ `TObjectPtr<class UAssetImportData> AssetImportData;` — `UPROPERTY(VisibleAnywhere, Instanced, Category = ImportSettings)`
- L110 _public member_ `FString SamplesImportDir;` — `UPROPERTY()` — save off the samples dir used when importing samples
- L113 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L114 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L115 _public prototype_ `virtual void PostInitProperties() override;`
- L116 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L121 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L125 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L126 _public prototype_ `virtual void PostLoad() override;`
- L131 _protected member_ `FFusionPatchData FusionPatchData;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Fusion Patch")`
- L140 _private member_ `TSharedPtr<FFusionPatchDataProxy::QueueType, ESPMode::ThreadSafe> RenderableFusionPatchData;` — Notice here that we cache a pointer the Proxy's "Queue" so we can... 1 - Supply it to all instances of Metasound nodes rendering this data. How? CreateNewProxyData instantiates a NEW unique ptr to an FFusionPatchDataProxy every time it is called. All of those unique proxy instances refer to the same queue... this one that we have cached. 2 - Modify that data in response to changes to this class's UPROPERTIES so that we can hear data changes reflected in the rendered audio.
- L142 _private prototype_ `void UpdateRenderableForNonTrivialChange();`
- L150 _private member_ `ELoadingState LoadingState = ELoadingState::None;`

#### enum `UFusionPatch::ELoadingState`  
`enum class ELoadingState`  
_L144-148_
- L146 _public enumerator_ `None`
- L147 _public enumerator_ `Loading`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API HARMONIXDSP_API`
- L76 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnFusionPatchLoadComplete, const class UFusionPatch*, LoadedFusionPatch, EFusionPatchAudioLoadResult, LoadResult);` — Called when a load request for a sound has completed.
- L76 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnFusionPatchLoadComplete, const class UFusionPatch*, LoadedFusionPatch, EFusionPatchAudioLoadResult, LoadResult);` — Called when a load request for a sound has completed.

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/FusionSampler.h` (Public)


#### class `FFusionSampler`  
`class FFusionSampler : public FVirtualInstrument`  
_L31-381_
- inherits: `FVirtualInstrument`
- desc: Make Fusion Sampler derive directly from virtual instrument
- L34 _public prototype_ `FFusionSampler(float InSampleRate, bool InUsePitchShifters = false);`
- L35 _public prototype_ `virtual ~FFusionSampler();`
- L37 _public prototype_ `void ResetPatchRelatedState();`
- L40 _public prototype_ `virtual void Prepare(float InSampleRateHz, EAudioBufferChannelLayout InChannelLayout, uint32 InMaxSamples, bool bInAllocateBuffer = true) override;` — configure this patch
- L41 _public prototype_ `void SetGainTable(const FGainTable* GainTable);`
- L42 _public function_ `const FGainTable* GetGainTable()`
- L47 _public prototype_ `virtual void NoteOn(FMidiVoiceId InVoiceId, int8 InMidiNoteNumber, int8 InVelocity, int8 InMidiChannel = 0, int32 InEventTick = 0, int32 InCurrentTick = 0, float InOffsetMs = 0.0f) override;` — These are overrides from VirtualInstrument that deal with MIDI message handling...
- L48 _public prototype_ `virtual void NoteOnWithFrameOffset(FMidiVoiceId InVoiceId, int8 InMidiNoteNumber, int8 InVelocity, int8 InMidiChannel = 0, int32 InNumFrames = 0) override;`
- L49 _public prototype_ `virtual bool NoteIsOn(int8 InMidiNoteNumber, int8 InMidiChannel = 0) override;`
- L50 _public prototype_ `virtual void NoteOff(FMidiVoiceId InVoiceId, int8 InMidiNoteNumber, int8 InMidiChannel = 0) override;`
- L51 _public prototype_ `virtual void NoteOffWithFrameOffset(FMidiVoiceId InVoiceId, int8 InMidiNoteNumber, int8 InMidiChannel = 0, int32 InNumFrames = 0) override;`
- L52 _public prototype_ `virtual void SetExtraPitchBend(float Semitones, int8 InMidiChannel = 0) override;`
- L53 _public prototype_ `virtual float GetPitchBend(int8 InMidiChannel = 0) const override;`
- L54 _public prototype_ `virtual void SetPitchBend(float Value, int8 InMidiChannel = 0) override;`
- L55 _public prototype_ `virtual void GetController(Harmonix::Midi::Constants::EControllerID InController, int8& OutMsb, int8& OutLsb, int8 InMidiChannel = 0) const override;`
- L58 _public prototype_ `virtual void SetMidiChannelVolume(float InVolume, float InSeconds = 0.0f, int8 InMidiChannel = 0) override;` — Mix Volume (dB) and associated linear gain (0,1]
- L59 _public prototype_ `virtual float GetMidiChannelVolume(int8 InMidiChannel = 0) const override;`
- L60 _public prototype_ `virtual void SetMidiChannelGain(float InGain, float InSeconds = 0.0f, int8 InMidiChannel = 0) override;`
- L61 _public prototype_ `virtual float GetMidiChannelGain(int8 InMidiChannel = 0) const override;`
- L62 _public prototype_ `virtual void SetMidiChannelMute(bool InMute, int8 InMidiChannel = 0) override;`
- L63 _public function_ `virtual bool GetMidiChannelMute(int8 InMidiChannel = 0) const override`
- L65 _public prototype_ `virtual int32 GetMaxNumVoices() const override;`
- L66 _public function_ `virtual int32 GetNumVoicesInUse() const override`
- L67 _public prototype_ `virtual int32 GetNumVoicesInUse(FFusionVoice** vArray) const;`
- L68 _public prototype_ `virtual void KillAllVoices() override;`
- L69 _public prototype_ `virtual void AllNotesOff() override;`
- L70 _public prototype_ `virtual void AllNotesOffWithFrameOffset(int32 InNumFrames = 0) override;`
- L73 _public prototype_ `virtual void SetSpeed(float Speed, bool MaintainPitch = false) override;` — Sets modulation and sample playback speed when maintainPitch is false. Otherwise it's 1.0.
- L76 _public function_ `virtual float GetSpeed(bool* MaintainPitchOut = nullptr) override` — Gets the current speed
- L85 _public prototype_ `virtual void SetTempo(float BPM) override;`
- L86 _public prototype_ `virtual void SetQuarterNote(float QuarterNote) override;`
- L87 _public function_ `float GetQuarterNote() const`
- L89 _public function_ `float GetSubtsreamGain(int32 Index)`
- L99 _public prototype_ `virtual void SetSampleRate(float InSampleRateHz) override;`
- L101 _public function_ `float GetSubstreamGain(int32 Index) const`
- L111 _public prototype_ `TSet<int32> GetActiveKeyzones();`
- L114 _public function_ `virtual void SetRawTransposition(int32 SemiTones) override`
- L115 _public function_ `virtual int32 GetRawTransposition() const override`
- L116 _public function_ `virtual void SetRawPitchMultiplier(float RawPitch) override`
- L117 _public function_ `virtual float GetRawPitchMultiplier() const override`
- L119 _public function_ `void SetTicksPerQuarterNote(int32 InTicksPerQuarterNote)`
- L120 _public function_ `int32 GetTicksPerQuarterNote() const`
- L126 _protected prototype_ `virtual void ResetInstrumentStateImpl() override;` — These are overrides from VirtualInstrument
- L127 _protected prototype_ `virtual void ResetMidiStateImpl() override;`
- L128 _protected prototype_ `virtual void Set7BitControllerImpl(Harmonix::Midi::Constants::EControllerID InController, int8 Value, int8 InMidiChannel = 0) override;`
- L129 _protected prototype_ `virtual void Set14BitControllerImpl(Harmonix::Midi::Constants::EControllerID InController, int16 Value, int8 InMidiChannel = 0) override;`
- L134 _protected prototype_ `void SetController(Harmonix::Midi::Constants::EControllerID InController, float InValue);` — NOTE: This next function's InValue is NOT some standard midi value. By the time it is called it is assumed the units and range of InValue are correct for the given controller id. So, for example, if InController is MidiConstants::LFO0Frequency than InValue is treated as Hz!
- L136 _protected prototype_ `void SetVoicePool(FSharedFusionVoicePoolPtr InPool, bool NoCallbacks);`
- L137 _protected function_ `FSharedFusionVoicePoolPtr GetVoicePool() const`
- L138 _protected prototype_ `void VoicePoolWillDestruct(const FFusionVoicePool* InPool);`
- L140 _protected prototype_ `virtual void Process(uint32 InSliceIndex, uint32 InSubSliceIndex, TAudioBuffer<float>& OutBuffer) override;`
- L141 _protected function_ `bool CanProcessFromWorkerThread() const override`
- L143 _protected prototype_ `void SetPatch(FFusionPatchDataProxy::NodePtr PatchData);`
- L145 _protected prototype_ `FString GetPatchPath() const;`
- L149 _protected prototype_ `void ApplyPatchSettings();` — apply all settings from the patch. call whenever the patch is set
- L151 _protected prototype_ `void SetFineTuneCents(float cents);`
- L152 _protected prototype_ `float GetFineTuneCents() const;`
- L161 _private prototype_ `void SetPortamentoMode(EPortamentoMode InMode);`
- L162 _private prototype_ `EPortamentoMode GetPortamentoMode() const;`
- L163 _private prototype_ `void SetIsPortamentoEnabled(bool InEnabled);`
- L164 _private function_ `bool GetIsPortamentoEnabled() const`
- L165 _private prototype_ `void SetPortamentoTime(float InTimeSec);`
- L167 _private prototype_ `float GetPortamentoTime() const;` — returns time in seconds
- L168 _private prototype_ `float GetCurrentPortamentoPitch() const;`
- L170 _private prototype_ `void SetStartPointMs(float InStartPointOffsetMs);`
- L171 _private prototype_ `float GetStartPointMs() const;`
- L174 _private prototype_ `void SetMaxNumVoices(int32);` — This is a soft limit, so old voices will be released instead of killed
- L175 _private prototype_ `bool RelinquishVoice(FFusionVoice* InVoice);`
- L177 _private function_ `virtual bool ProcessCallWillProduceSilence() const override`
- L179 _private prototype_ `void SetPan(const FPannerDetails& pan);`
- L180 _private prototype_ `const FPannerDetails& GetPan() const;`
- L185 _private prototype_ `float GetMinPitchBendCents() const;`
- L186 _private prototype_ `void SetMinPitchBendCents(float Value);`
- L187 _private prototype_ `float GetMaxPitchBendCents() const;`
- L188 _private prototype_ `void SetMaxPitchBendCents(float Value);`
- L192 _private prototype_ `float GetPitchBendFactor() const;` — returns the multiplicative factor used to change the rate of sample frame increment to hit the current pitch bend settings
- L194 _private function_ `float GetMidiChannelMuteGain() const`
- L196 _private prototype_ `float GetTrimVolume() const;`
- L197 _private prototype_ `void SetTrimVolume(float Value);`
- L198 _private prototype_ `float GetTrimGain() const;`
- L200 _private function_ `float GetRampedExpression() const`
- L201 _private function_ `float GetRampedPitchBend() const`
- L203 _private prototype_ `void SetMidiExpressionGain(float InGain, float InSeconds = 0.0f, int8 InMidiChannel = 0);`
- L206 _private prototype_ `void PrepareToProcess(uint32 numSamples);` — Updates time-based state.
- L208 _private prototype_ `void UpdatePitchBendFactor();`
- L209 _private prototype_ `void UpdateVoiceLfos();`
- L212 _private prototype_ `void ProcessNoteActions(int32 InNumFrames);` — Pending note actions...
- L213 _private prototype_ `void ResetNoteActions(bool ClearNotes);`
- L214 _private prototype_ `void ResetNoteStatus();`
- L218 _private prototype_ `int32 GatherMatchingKeyzones(uint8 TransposedNote, uint8 InVelocity, bool IsNoteOn, const TArray<FKeyzoneSettings>& InKeyzones, uint16* InMatchingZones);` — internal note on/off functions only called on audio thread
- L219 _private prototype_ `int32 StartNote(FMidiVoiceId InVoiceId, uint8 InMidiNoteNumber, uint8 InVelocity, bool IsNoteOn, int32 InEventTick, int32 InTriggerTick, float InOffsetMs);`
- L221 _private prototype_ `TArray<uint8> StopNote(FMidiVoiceId InVoiceId, uint8 LastVelocity);` — Note: StopNote returns a TArray of midi notes that where stopped so the called can check to see if there are any key-off keyzoned that need to be triggered
- L223 _private prototype_ `bool TryKeyOnZone(FMidiVoiceId InVoiceId, uint8 InTriggeredNote, uint8 InTransposedNote, uint8 InVelocity, int32 InEventTick, int32 InTriggerTick, float InOffsetMs, const FKeyzoneSettings* keyzone);`
- L227 _private member_ `float RampCallRateHz = 375.0f;`
- L229 _private member_ `float Speed = 1.0f;`
- L230 _private member_ `bool MaintainPitchWhenSpeedChanges = false;`
- L231 _private member_ `float CurrentQuarterNote = 0.0f;`
- L237 _private member_ `float MidiChannelVolume = 0.0f;` — channel's mix setting... persists independently of the patch
- L238 _private member_ `TLinearRamper<float> MidiChannelGainRamper;`
- L241 _private member_ `bool MidiChannelMuted = false;` — channel's mute setting... persists independently of the patch
- L244 _private member_ `TLinearRamper<float> MidiChannelMuteGainRamper;` — ramper to smooth muting
- L247 _private member_ `float TrimVolume = 0.0f;` — the patch's trim setting... read-only outside of patch editor.
- L248 _private member_ `float TrimGain = 1.0f;`
- L251 _private member_ `float ExpressionGain = 1.0f;` — the CC 11 expression value [0,1]
- L254 _private member_ `TLinearRamper<float> ExpressionGainRamper;` — expression [0,1] mapped to linear gain (a la the MIDI recommendations)
- L256 _private member_ `FPannerDetails PanSettings;`
- L260 _private member_ `bool IsPortamentoEnabled = false;` — PORTAMENTO
- L262 _private member_ `EPortamentoMode PortamentoMode = EPortamentoMode::None;`
- L263 _private member_ `float PortamentoTimeMs = 300.0f;`
- L266 _private member_ `bool IsPortamentoActive = false;` — True if the portmanto pitch should be considered (false before any note ons for example)
- L269 _private member_ `TLinearRamper<float> PortamentoPitchRamper;` — midi note number (fractional) that represents the actual pitch of sounding notes
- L275 _private member_ `TLinearRamper<float> PitchBendRamper;` — on range [-1, 1]
- L278 _private member_ `float ExtraPitchBend = 0.0f;` — extra pitch bend in semitones
- L279 _private member_ `float PitchBendFactor = 1.0f;`
- L281 _private member_ `float FineTuneCents = 0.0f;`
- L283 _private member_ `float StartPointMs = 0.0f;`
- L285 _private member_ `FBiquadFilterSettings FilterSettings;`
- L290 _private member_ `FAdsrSettings AdsrVolumeSettings;` — Modulators
- L291 _private member_ `FAdsrSettings AdsrAssignableSettings;`
- L292 _private member_ `static constexpr int32 kNumLfos = 2;`
- L293 _private member_ `FLfoSettings LfoSettings[kNumLfos];`
- L294 _private member_ `Harmonix::Dsp::Modulators::FLfo Lfos[kNumLfos];`
- L295 _private member_ `static constexpr int32 kNumModulators = 2;`
- L296 _private member_ `FModulatorSettings RandomizerSettings[kNumModulators];`
- L297 _private member_ `FModulatorSettings VelocityModulatorSettings[kNumModulators];`
- L300 _private member_ `uint32 MaxNumVoices = 100;` — soft limit, may be over max if some voices are in release stage
- L302 _private member_ `TDoubleLinkedList<FFusionVoice*> ActiveVoices;`
- L304 _private member_ `float MinPitchBendCents = -200.0f;`
- L305 _private member_ `float MaxPitchBendCents = 200.0f;`
- L307 _private member_ `FSharedFusionVoicePoolPtr VoicePool;`
- L308 _private member_ `const bool bUsePitchShifters;`
- L314 _private member_ `FCriticalSection sNoteActionCritSec;` — if we get note-ons or note-offs on the main thread, or if we get multiple requests for the same note number, then this data helps us track and filter these requests
- L315 _private member_ `FCriticalSection sNoteStatusCritSec;`
- L316 _private member_ `static const int8 kNoteIgnore = -1;`
- L317 _private member_ `static const int8 kNoteOff = 0;`
- L318 _private member_ `static const int32 kMaxLayersPerNote = 128;`
- L340 _private member_ `TArray<FPendingNoteAction> PendingNoteActions;`
- L341 _private member_ `FMIDINoteStatus NoteStatus[Harmonix::Midi::Constants::GMaxNumNotes];`
- L343 _private member_ `FFusionPatchDataProxy::NodePtr FusionPatchData = nullptr;`
- L345 _private member_ `int8 LastStartLayerSelect[Harmonix::Midi::Constants::GMaxNumNotes];`
- L346 _private member_ `int8 LastStopLayerSelect[Harmonix::Midi::Constants::GMaxNumNotes];`
- L347 _private member_ `int8 LastVelocity[Harmonix::Midi::Constants::GMaxNumNotes];`
- L350 _private member_ `static const int32 kScratchBufferFrames = 2048;` — "scratch pad" used during process to get each voice's output audio
- L351 _private member_ `static const int32 kScratchBufferChannels = FAudioBufferConfig::kMaxAudioBufferChannels;`
- L352 _private member_ `static const int32 kScratchBufferSamples = (kScratchBufferFrames * kScratchBufferChannels);`
- L353 _private member_ `static const int32 kScratchBufferBytes = (kScratchBufferSamples * sizeof(float));`
- L356 _private member_ `float VoiceWorkBuffer[kScratchBufferSamples + 4];` — +4 because we can't count on 'alignas' because we allocate an array of these classes. That type of allocation ignores the alignas attribute :-(
- L357 _private member_ `float* VoiceWorkBufferChannels[kScratchBufferChannels];`
- L363 _protected member_ `float CurrentTempoBPM = 120.0f;` — we'll keep track of the 'current tempo' as it is needed by any 'beat sync' effects...
- L365 _protected member_ `float RawPitchMultiplier = 0.0f;`
- L366 _protected member_ `int32 Transposition = 0;`
- L368 _protected member_ `EKeyzoneSelectMode KeyzoneSelectMode = EKeyzoneSelectMode::Layers;`
- L371 _private member_ `int16 TimeStretchEnvelopeOverride = -1;`
- L372 _private prototype_ `void UpdateVoicesForEnvelopeOrderChange();`
- L374 _private member_ `static const int32 kMaxSubstreams = 8;`
- L375 _private member_ `float SubstreamGain[kMaxSubstreams];`
- L376 _private prototype_ `void SetSubstreamMidiGain(int32 InIndex, uint8 InMidiGain);`
- L378 _private member_ `int32 TicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt;`
- L380 _private member_ `const FGainTable* GainTable = nullptr;`

#### struct `FFusionSampler::FPendingNoteAction`  
`struct FPendingNoteAction`  
_L320-329_
- L322 _public member_ `int8 MidiNote = 0;`
- L323 _public member_ `int8 Velocity = 0;`
- L324 _public member_ `int32 EventTick = 0;`
- L325 _public member_ `int32 TriggerTick = 0;`
- L326 _public member_ `float OffsetMs = 0.0f;`
- L327 _public member_ `int32 FrameOffset = 0;`
- L328 _public member_ `FMidiVoiceId VoiceId;`

#### struct `FFusionSampler::FMIDINoteStatus`  
`struct FMIDINoteStatus`  
_L331-338_
- L334 _public member_ `bool KeyedOn = false;` — is the key pressed down?
- L337 _public member_ `int32 NumActiveVoices = 0;` — is there any sound coming out of this note? (release could mean key off but voices active)

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API HARMONIXDSP_API`
- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionSampler, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionSampler, Log, All);`
- L28 _typedef_ `using FSharedFusionVoicePoolPtr = TSharedPtr<FFusionVoicePool, ESPMode::ThreadSafe>;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/FusionSamplerConfig.h` (Public)


#### class `UFusionSamplerConfig`  
`class UFusionSamplerConfig : public UHarmonixDeveloperSettings`  
_L13-26_
- reflection: `UCLASS(MinimalAPI, Config = Engine, defaultconfig, meta = (DisplayName = "Fusion Sampler Settings"))`
- inherits: `UHarmonixDeveloperSettings`
- L20 _public member_ `FFusionVoiceConfig DefaultVoicePoolConfig;` — `UPROPERTY(config, EditDefaultsOnly, Category = "Voice Pools")`
- L23 _public member_ `TMap<FName, FFusionVoiceConfig> VoicePoolConfigs;` — `UPROPERTY(config, EditDefaultsOnly, Category = "Voice Pools")`
- L25 _public prototype_ `FFusionVoiceConfig GetVoiceConfigForPoolName(FName PoolName) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/FusionVoice.h` (Public)


#### class `FFusionVoiceFixLayout`  
`class FFusionVoiceFixLayout`  
_L31-35_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L34 _public prototype_ `virtual ~FFusionVoiceFixLayout() = default;`

#### class `FFusionVoice`  
`class alignas(16) FFusionVoice : FFusionVoiceFixLayout`  
_L37-231_
- inherits: `FFusionVoiceFixLayout`
- L41 _public prototype_ `FFusionVoice();`
- L42 _public prototype_ `virtual ~FFusionVoice() = default;`
- L44 _public prototype_ `void Init(FFusionVoicePool* InOwner, uint32 InDebugID);`
- L46 _public member_ `static const double kMaxPitchOffsetCents;`
- L48 _public member_ `static const uint32 kInvalidId = 0xffffffff;`
- L50 _public prototype_ `bool IsWaitingForAttack() const;`
- L52 _public prototype_ `virtual bool IsInUse() const;`
- L54 _public typedef_ `using FRelinquishHandler = TFunction<bool(FFusionVoice*)>;`
- L56 _public prototype_ `bool AssignIDs(FFusionSampler* InSampler, const FKeyzoneSettings* KeyZone, FMidiVoiceId NoteID, FRelinquishHandler Handler, TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> Shifter = nullptr);`
- L58 _public function_ `virtual TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> GetPitchShifter() const`
- L60 _public function_ `virtual Harmonix::Dsp::Modulators::EAdsrStage GetAdsrStage() const`
- L62 _public function_ `uint32 GetAge() const`
- L63 _public function_ `FMidiVoiceId GetVoiceID() const`
- L64 _public function_ `uint8 GetTriggeredMidiNote() const`
- L66 _public function_ `double GetPlaybackPos() const`
- L67 _public function_ `double GetEndOfSampleData() const`
- L68 _public function_ `void SetRelinquishHandler(FRelinquishHandler handler)`
- L75 _public prototype_ `virtual void SetPitchOffset(double numCents);` — offset the pitch of this voice by a (fractional) number of cents call this only before calling attack. @param numCents number of cents to move pitch
- L78 _public prototype_ `virtual void AttackWithTargetNote(uint8 InMidiNoteNumber, float InGain, int32 InEventTick, int32 InTriggerTick, double InStartPointMs = 0.0f, const char* InFilePath = nullptr);`
- L80 _public prototype_ `virtual void AttackWithTargetNote(uint8 InMidiNoteNumber, float InGain, int32 InEventTick, int32 InTriggerTick, double InStartPointMs = 0.0f);`
- L83 _public prototype_ `void PlaySampleSlice(float start, float end, float seconds);`
- L86 _public prototype_ `virtual uint32 Process(uint32 sliceIndex, uint32 subsliceIndex, float** output, uint32 numChannels, uint32 maxNumSamples, float speed = 1.0f, float tempo = 120.0f, bool MaintainPitchWhenSpeedChanges = false);` — this function is called on the audio thread to have the voice fill up the given buffer
- L91 _public prototype_ `virtual void Release();` — puts the voice into release stage, which lets it ramp down. the processor will free up this voice after ramp down is complete.
- L95 _public prototype_ `virtual void FastRelease();` — ramps down using a microfade to free up the voice as soon as possible without an audible pop
- L101 _public prototype_ `virtual void Kill();` — kill (and free up) the voice immediately with no ramp down. this should only be called if the voice is known to be silent anyway, or you ran out of sample data, or you have no other choice.
- L104 _public prototype_ `virtual bool MatchesIDs(const FFusionSampler* InSampler, FMidiVoiceId InVoiceID, const FKeyzoneSettings* keyzone = nullptr);` — if keyzone is NULL (or not passed in), then all voices with the channel and note id will match
- L105 _public function_ `int32 GetTargetMidiNote()`
- L107 _public function_ `bool UsesSampler(const FFusionSampler* InSampler) const`
- L111 _public function_ `FFusionSampler* GetSampler()`
- L112 _public function_ `virtual bool UsesKeyzone(const FKeyzoneSettings* InKeyzone) const`
- L116 _public function_ `virtual const FKeyzoneSettings* GetKeyzone() const`
- L118 _public function_ `float GetCombinedAudioLevel()`
- L120 _public prototype_ `virtual void SetupLfo(uint8 Index, const FLfoSettings& InSettings);`
- L122 _public function_ `uint8 Priority()`
- L129 _public prototype_ `void SetSampler(FFusionSampler* InSampler);` — used by the voice aliasing system if this real voice is passed around amoung virtual voices...
- L131 _public prototype_ `void SetPitchShiftForMidiNote(uint8 InNote);`
- L133 _public function_ `virtual bool IsAlias() const`
- L134 _public function_ `virtual bool IsRendererForAlias() const`
- L135 _public function_ `void SetIsRendererForAlias(bool InIsRenderer)`
- L136 _public function_ `virtual bool HasBeenRelinquished() const`
- L140 _protected member_ `FMidiVoiceId VoiceID;`
- L141 _protected member_ `float TargetMidiNote = 0.0f;`
- L142 _protected member_ `FFusionSampler* MySampler = nullptr;`
- L143 _protected member_ `bool bIsRendererForAlias = false;`
- L144 _protected member_ `uint8 TriggeredMidiNote = 0;`
- L148 _private prototype_ `void SetSampleRate(double InSampleRate);`
- L150 _private prototype_ `void PrepareWithPitchOffsetAndGain(double InPitchOffsetCents, float InGain);`
- L151 _private prototype_ `void ApplyModsToFilter(bool forceSet);`
- L152 _private prototype_ `void AggregatePansSetTargetAndRamp(float InTotalGain, bool InSnap = false);`
- L154 _private prototype_ `float ComputeOctaveShift();` — the number of octaves to shuft the filter frequency
- L157 _private prototype_ `void Attack();` — start the note (call after preparing the voice)
- L159 _private prototype_ `static void UpdateFilterSettings(void* thisPointer);`
- L160 _private prototype_ `static void RestoreFilterGain(void* thisPointer);`
- L162 _private prototype_ `void BuildGainMatrix(bool InSnap);`
- L164 _private member_ `bool bWaitingForAttack = false;`
- L165 _private member_ `bool bHasRenderedAnySamples = false;`
- L168 _private member_ `uint32 DebugID;` — just for debugging
- L170 _private member_ `float VelocityGain = 0.0f;`
- L171 _private member_ `float MaxAudioLevel = 0.0f;`
- L173 _private member_ `const FKeyzoneSettings* KeyZone = nullptr;`
- L175 _private member_ `TSharedPtr<IAudioDataRenderer, ESPMode::ThreadSafe> ActiveRenderer = nullptr;`
- L177 _private member_ `TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> PitchShifter = nullptr;`
- L179 _private member_ `Harmonix::Dsp::Modulators::FAdsr AdsrVolume;`
- L180 _private member_ `Harmonix::Dsp::Modulators::FAdsr AdsrAssignable;`
- L181 _private member_ `static const int32 kNumLfos = 2;`
- L182 _private member_ `Harmonix::Dsp::Modulators::FLfo Lfo[kNumLfos];`
- L184 _private member_ `FPanner Panner;`
- L186 _private member_ `Harmonix::Dsp::Effects::FBiquadFilter Filters[FAudioBufferConfig::kMaxAudioBufferChannels];`
- L187 _private member_ `TLinearRamper<Harmonix::Dsp::Effects::FBiquadFilterCoefs> FilterCoefsRamper;`
- L188 _private member_ `float CachedFilterFrequency = 0.0f;`
- L189 _private member_ `FBiquadFilterSettings ModulatedFilterSettings;`
- L195 _private member_ `float OctaveShift = 0.0f;` — this is the number we use to modulate the filter frequency. we would call this "frequency", but we want the units to be "octaves" so it can be linear. the actual frequency is  20*(2^octave)
- L196 _private member_ `Harmonix::Dsp::Modulators::FModulatorTarget FilterOctaveTarget;`
- L198 _private member_ `TLinearRamper<float> FilterGainRamper;`
- L200 _private member_ `TAudioBuffer<float> OutputBuffer;`
- L202 _private member_ `double FileToOutputSampleRatio = 0.0;`
- L204 _private member_ `double SamplesPerSecond = 0.0;`
- L205 _private member_ `double SecondsPerSample = 0.0;`
- L208 _private member_ `double SamplePos = 0.0;`
- L209 _private member_ `double PitchShift = 0.0;`
- L210 _private member_ `double ResampleRate = 0.0;`
- L212 _private member_ `double PitchOffsetCents = 0.0;`
- L213 _private member_ `double PitchModulation = 0.0;`
- L215 _private member_ `double EndOfSampleData = 0.0;`
- L217 _private member_ `FFusionVoicePool* VoicePool = nullptr;`
- L220 _private member_ `float StartQuarterNote = 0.0f;` — needed for tempo sync'd keyzones...
- L221 _private member_ `float CurrentVso = 0.0f;`
- L222 _private member_ `double LastVsoPos = 0.0f;`
- L223 _private member_ `double StartPos = 0.0f;`
- L225 _private member_ `FRelinquishHandler RelinquishHandler;`
- L228 _private member_ `bool bProfiling{false};`
- L229 _private member_ `FString ProfileString;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionVoice, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionVoice, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/FusionVoicePool.h` (Public)


#### struct `FFusionVoiceConfig`  
`struct FFusionVoiceConfig`  
_L24-54_
- reflection: `USTRUCT()`
- L29 _public member_ `uint32 NumTotalVoices = 32;` — `UPROPERTY(EditAnywhere, Category = "Voice Pool")`
- L32 _public member_ `uint32 SoftVoiceLimit = 24;` — `UPROPERTY(EditAnywhere, Category = "Voice Pool")`
- L35 _public member_ `float FormantDbCorrectionPerHalfStepUp = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Pitch Shifter")`
- L38 _public member_ `float FormantDbCorrectionPerHalfStepDown = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Pitch Shifter")`
- L41 _public member_ `float FormantDbCorrectionMaxUp = 12.0f;` — `UPROPERTY(EditAnywhere, Category = "Pitch Shifter")`
- L44 _public member_ `float FormantDbCorrectionMaxDown = -12.0f;` — `UPROPERTY(EditAnywhere, Category = "Pitch Shifter")`
- L46 _public function_ `FFusionVoiceConfig()`
- L48 _public function_ `FFusionVoiceConfig( uint32 InNumTotalVoices, uint32 InSoftVoiceLimit) : NumTotalVoices(InNumTotalVoices) , SoftVoiceLimit(InSoftVoiceLimit)`

#### class `FFusionVoicePool`  
`class FFusionVoicePool`  
_L56-213_
- L60 _public prototype_ `static FSharedFusionVoicePoolPtr GetDefault(float InSampleRate);`
- L61 _public prototype_ `static FSharedFusionVoicePoolPtr GetNamedPool(FName InPoolName, float InSampleRate);`
- L62 _public prototype_ `static FSharedFusionVoicePoolPtr Create(const FFusionVoiceConfig& InConfig, float InSampleRate);`
- L64 _public function_ `FFusionVoicePool(float InSampleRate) : Voices(nullptr) , NumAllocatedVoices(0) , NumVoicesSetting(kDefaultPoolSize) , SoftVoiceLimit(kDefaultPoolSize) , PeakVoiceUsage(0) , SampleRate(InSampleRate)`
- L73 _public prototype_ `virtual ~FFusionVoicePool();`
- L75 _public prototype_ `void HardAllocatateVoices();`
- L76 _public prototype_ `void ReleaseHardAllocation();`
- L78 _public prototype_ `void SetIsMultithreading(bool InIsMultithreaded);`
- L81 _public prototype_ `void AddClient(FFusionSampler* InSampler);` — let the FusionVoicePool know that you will need voices
- L84 _public prototype_ `void RemoveClient(FFusionSampler* InSampler);` — let the FusionVoicePool know that you no longer need voices
- L87 _public member_ `static const uint32 kMinPoolSize = 1;` — Global Voice Pool
- L88 _public member_ `static const uint32 kMaxPoolSize = 256;`
- L89 _public member_ `static const uint32 kDefaultPoolSize = 16;`
- L92 _public prototype_ `uint32 GetNumVoicesInUse();`
- L100 _public function_ `uint32 GetNumVoicesAvailable()` — The number of voices allocated. May be different than the hard limit if voices have not been allocated yet (or if there are no clients for this voice pool) @returns the number of voices currently allocated.
- L102 _public prototype_ `bool HasVoice(FFusionSampler* InOwner, FMidiVoiceId InVoiceId);`
- L108 _public prototype_ `void SetHardVoiceLimit(uint32 InLimit);` — The number of voices to allocate for this pool. @param limit the maximum number of voices that this pool can handle. (the number of voices to allocate)
- L113 _public function_ `uint32 GetHardVoiceLimit() const` — @returns the maximum number of voices this pool can handle.
- L119 _public prototype_ `void SetSoftVoiceLimit(uint32 InLimit);` — The number of voices to allow before automatically releasing excess voices. @param limit the maximum number of voices to allow before fast-releasing
- L124 _public function_ `uint32 GetSoftVoiceLimit() const` — @returns the maximum number of voices this pool will allow before automatically releasing voices.
- L126 _public prototype_ `void SetFormantVolumeCorrection(float dBperHalfStepUp, float dBperHalfStepDown, float dBMaxUp, float dBMaxDown);`
- L128 _public function_ `uint32 GetPeakVoiceUsage()`
- L134 _public function_ `void ResetPeakVoiceUsage()`
- L147 _public prototype_ `FFusionVoice* GetFreeVoice( FFusionSampler* InSampler, FMidiVoiceId InVoiceID, const FKeyzoneSettings* InKeyzone, TFunction<bool(FFusionVoice*)> Handler, IStretcherAndPitchShifterFactory* PitchShifterFactory, bool AllowAlias = true, bool IsRendererForAlias = false);` — THIS PROBABLY SHOULD BE PRIVATE. IT IS USED BY NOTE ON. NOT AN IDEAL ARGUMENT SIGNATURE FOR PUBLIC CONSUMPTION. pass in a channel and note id to assign to the voice. also pass in the keyzone that the voice should use. any active voices with a matching set of IDs will be put into release stage. a voice might get killed (stopped instantly) if there are not enough free voices. returns null if there is no patch assigned to the channel.
- L156 _public prototype_ `void ReleaseShifter(TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> InShifter);`
- L166 _public prototype_ `uint32 FastReleaseExcessVoices(FFusionSampler* InSampler = nullptr);` — Fast releases voices that have exceeded the soft limit for the pool (or the channel). If no channel is specified, then voices assigned to any channel are candidates for being fast-released. If a specific channel is specified, then only voices being used by that channel may be fast released. @param channel (optional) restrict the voice candidates for release to the ones uses by a specific channel. @returns the number of voices currently being used by the pool (or by the specified channel)
- L169 _public prototype_ `void KillVoices();` — instantly stops all voices with no release stage
- L171 _public prototype_ `void KillVoices(const FFusionSampler* InSampler, bool NoCallbacks);` — void KillVoices(const MultiInstrument*);
- L172 _public prototype_ `void KillVoices(const FKeyzoneSettings* InKeyzoneSettings);`
- L174 _public prototype_ `FFusionVoice* GetVoice(uint32 VoiceIdx);`
- L176 _public function_ `float GetSampleRate() const`
- L177 _public prototype_ `void SetSampleRate(float InSampleRate);`
- L179 _public prototype_ `void Lock();`
- L180 _public prototype_ `void Unlock();`
- L186 _private typedef_ `using FPoolMapKey = TTuple<FName, int32>;` — Key is a tuple of PoolName and SampleRate Value is a weak ptr, but shared ptrs are returned so it gets automatically destroyed when nothing references it anymore
- L187 _private typedef_ `using FPoolMap = TMap<FPoolMapKey, TWeakPtr<FFusionVoicePool, ESPMode::ThreadSafe>>;`
- L188 _private member_ `static FPoolMap GVoicePools;`
- L190 _private member_ `FFusionVoice* Voices;`
- L192 _private member_ `uint32 NumAllocatedVoices = 0;`
- L193 _private member_ `uint32 NumVoicesSetting = 0;`
- L195 _private member_ `uint32 SoftVoiceLimit = 0;`
- L197 _private member_ `uint32 PeakVoiceUsage = 0;`
- L199 _private prototype_ `void AllocVoices();`
- L200 _private prototype_ `void CreateVoices(uint16 InMaxPolyphony);`
- L201 _private prototype_ `void CreateShifters();`
- L202 _private prototype_ `void FreeVoices();`
- L204 _private member_ `TArray<FFusionSampler*> ClientSamplers;`
- L206 _private member_ `FCriticalSection PoolLock;`
- L208 _private member_ `float SampleRate = 0.0f;`
- L210 _private member_ `bool DynamicAllocAndFree = true;`
- L212 _private member_ `bool IsMultithreading = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXDSP_API`
- L19 _typedef_ `using FSharedFusionVoicePoolPtr = TSharedPtr<FFusionVoicePool, ESPMode::ThreadSafe>;`
- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionVoicePool, Log, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionVoicePool, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/Settings/FusionPatchSettings.h` (Public)


#### enum `EKeyzoneSelectMode`  
`enum class EKeyzoneSelectMode : uint8`  
_L23-31_
- reflection: `UENUM()`
- L25 _public enumerator_ `Layers UMETA(Json="layers")`
- L26 _public enumerator_ `Random UMETA(Json="random")`
- L27 _public enumerator_ `RandomWithRepetition UMETA(Json="random_with_repititon")`
- L28 _public enumerator_ `Cycle UMETA(Json="cycle")`
- L29 _public enumerator_ `Num UMETA(Hidden)`
- L30 _public enumerator_ `Invalid UMETA(Hidden)`

#### struct `FFusionPatchSettings`  
`struct FFusionPatchSettings`  
_L34-100_
- reflection: `USTRUCT()`
- L40 _public prototype_ `FFusionPatchSettings();`
- L43 _public member_ `float VolumeDb = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "-96", ClampMax = "12", UIMin = "-96", UIMax = "12"))`
- L46 _public member_ `FPannerDetails PannerDetails;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L49 _public member_ `float DownPitchBendCents = -200.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "-2400", ClampMax = "-200", UIMin = "-2400", UIMax = "-200"))`
- L52 _public member_ `float UpPitchBendCents = 200.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "200", ClampMax = "2400", UIMin = "200", UIMax = "2400"))`
- L55 _public member_ `float FineTuneCents = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "-100", ClampMax = "100", UIMin = "-100", UIMax = "100"))`
- L58 _public member_ `float StartPointOffsetMs = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", DisplayName = "Start Point Offset (Ms)", Meta = (ClampMin = "0", ClampMax = "1000", UIMin = "0", UIMax = "1000"))`
- L61 _public member_ `int32 MaxVoices = 32;` — `UPROPERTY()`
- L64 _public member_ `EKeyzoneSelectMode KeyzoneSelectMode = EKeyzoneSelectMode::Layers;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L67 _public member_ `FPortamentoSettings Portamento;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L70 _public member_ `FBiquadFilterSettings Filter;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L72 _public member_ `static constexpr int32 kNumAdsrs = 2;`
- L74 _public member_ `FAdsrSettings Adsr[kNumAdsrs];` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L76 _public member_ `static constexpr int32 kNumLfos = 2;`
- L78 _public member_ `FLfoSettings Lfo[kNumLfos];` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L80 _public member_ `static constexpr int32 kNumRandomizers = 2;`
- L82 _public member_ `FModulatorSettings Randomizer[kNumRandomizers];` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L84 _public member_ `static constexpr int32 kNumModulators = 2;`
- L86 _public member_ `FModulatorSettings VelocityModulator[kNumModulators];` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L89 _public member_ `FAdsrSettingsArray Adsrs_DEPRECATED;` — `UPROPERTY()`
- L92 _public member_ `FLfoSettingsArray Lfos_DEPRECATED;` — `UPROPERTY()`
- L95 _public member_ `FModulatorSettingsArray Randomizers_DEPRECATED;` — `UPROPERTY()`
- L98 _public member_ `FModulatorSettingsArray VelocityModulators_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/Settings/KeyzoneSettings.h` (Public)


#### struct `FKeyzoneArgs`  
`struct FKeyzoneArgs`  
_L22-36_
- L24 _public member_ `FString SamplePath;`
- L25 _public member_ `int8 RootNote = 60;`
- L26 _public member_ `int8 MinNote = 0;`
- L27 _public member_ `int8 MaxNote = 127;`
- L28 _public member_ `int8 MinVelocity = 0;`
- L29 _public member_ `int8 MaxVelocity = 127;`
- L30 _public member_ `bool bUnpitched = false;`
- L31 _public member_ `bool bVelocityToVolume = true;`
- L32 _public member_ `bool bMaintainTime = false;`
- L33 _public member_ `FName PitchShifter;`
- L34 _public member_ `bool bSyncTempo = false;`
- L35 _public member_ `float OriginalTempo = 120.0f;`

#### struct `FKeyzoneSettings`  
`struct FKeyzoneSettings`  
_L39-157_
- reflection: `USTRUCT()`
- L45 _public prototype_ `FKeyzoneSettings();`
- L47 _public function_ `FKeyzoneSettings(const FKeyzoneArgs& InArgs)`
- L52 _public prototype_ `~FKeyzoneSettings();`
- L54 _public function_ `void ApplyArgs(const FKeyzoneArgs& InArgs)`
- L73 _public member_ `TObjectPtr<USoundWave> SoundWave;` — `UPROPERTY(EditDefaultsOnly, Category = "Audio Sample")` — Not null when this keyzone is not being proxied
- L75 _public member_ `TSharedPtr<const FSoundWaveData> SoundWaveData;`
- L79 _public member_ `int8 RootNote = 60;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin=0, UIMax=127, ClampMin=0, ClampMax=127))`
- L82 _public member_ `int8 MinNote = 0;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = 0, UIMax = 127, ClampMin = 0, ClampMax = 127))`
- L85 _public member_ `int8 MaxNote = 127;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = 0, UIMax = 127, ClampMin = 0, ClampMax = 127))`
- L88 _public member_ `int8 MinVelocity = 0;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = 0, UIMax = 127, ClampMin = 0, ClampMax = 127))`
- L91 _public member_ `int8 MaxVelocity = 127;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = 0, UIMax = 127, ClampMin = 0, ClampMax = 127))`
- L95 _public member_ `uint8 SampleIndex = 0;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")` — on disk this is the index into the sample file name table
- L98 _public member_ `uint8 Priority = 50;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L101 _public member_ `FPannerDetails Pan;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L104 _public member_ `bool bOverrideAdsr = false;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L107 _public member_ `FAdsrSettings Adsr;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", meta=(EditCondition="bOverrideAdsr", EditConditionHides=true))`
- L110 _public member_ `float FineTuneCents = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = -100, UIMax = 100, ClampMin = -100, ClampMax = 100))`
- L113 _public member_ `float Gain = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta=(PostEditType="Trivial", UIMin="0.0", UIMax="1.0", ClampMin="0.0", ClampMax="1.0"))`
- L116 _public member_ `bool bUnpitched = false;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L119 _public member_ `bool bVelocityToGain = true;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L122 _public member_ `FTimeStretchConfig TimeStretchConfig;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L125 _public member_ `bool bIsNoteOffZone = false;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L128 _public member_ `float RandomWeight = 50.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = 0, UIMax = 100, ClampMin = 0, ClampMax = 100))`
- L131 _public member_ `int32 SampleStartOffset = -1;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = -1, ClampMin = -1))`
- L134 _public member_ `int32 SampleEndOffset = -1;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = -1, ClampMin = -1))`
- L137 _public member_ `TArray<FTrackChannelInfo> TrackMap;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L140 _public member_ `bool UseSingletonVoicePool = false;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L142 _public member_ `TSharedPtr<FSingletonFusionVoicePool> SingletonFusionVoicePool = nullptr;`
- L144 _public prototype_ `bool ContainsNoteAndVelocity(uint8 InNote, uint8 InVelocity) const;`
- L145 _public prototype_ `void SetVolumeDb(float Db);`
- L146 _public prototype_ `float GetVolumeDb() const;`
- L147 _public function_ `bool IsSingleton() const`
- L148 _public function_ `bool IsNoteOnZone() const`
- L150 _public prototype_ `void InitProxyData(const Audio::FProxyDataInitParams& InitParams);`
- L154 _public member_ `FString SamplePath;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta=(EditCondition="false"))`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HARMONIXDSP_API`
- L20 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogKeyzoneSettings, Log, All);`
- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogKeyzoneSettings, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/Settings/PortamentoSettings.h` (Public)


#### enum `EPortamentoMode`  
`enum class EPortamentoMode : uint8`  
_L7-13_
- reflection: `UENUM()`
- L9 _public enumerator_ `Legato UMETA(Json="legato")`
- L10 _public enumerator_ `Persistent UMETA(Json="persistent")`
- L11 _public enumerator_ `Num UMETA(Hidden)`
- L12 _public enumerator_ `None UMETA(Hidden)`

#### struct `FPortamentoSettings`  
`struct FPortamentoSettings`  
_L16-30_
- reflection: `USTRUCT()`
- L23 _public member_ `bool IsEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L26 _public member_ `EPortamentoMode Mode = EPortamentoMode::Legato;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L29 _public member_ `float Seconds = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (ClampMin = "0", ClampMax = "10", UIMin = "0", UIMax = "10"))`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/SingletonFusionVoicePool.h` (Public)


#### class `FSingletonFusionVoicePool`  
`class FSingletonFusionVoicePool`  
_L28-133_
- L31 _public member_ `static const int32 kMaxSingletonAliases;`
- L33 _public prototype_ `FSingletonFusionVoicePool(int32 InMaxInstances, FKeyzoneSettings& InKeyzoneRef);`
- L34 _public prototype_ `~FSingletonFusionVoicePool() = default;`
- L36 _public prototype_ `FFusionVoice* AllocateAlias( FFusionVoicePool* InPool, FFusionSampler* InSampler, FMidiVoiceId InVoiceID, TFunction<bool(FFusionVoice*)> Handler, IStretcherAndPitchShifterFactory* PitchShifterFactory);`
- L42 _public function_ `bool IsDriver(FAliasFusionVoice* InVoice) const`
- L44 _public prototype_ `void SamplerDisconnecting(const FFusionSampler* Sampler);`
- L46 _public function_ `const FKeyzoneSettings& GetKeyzone() const`
- L48 _public prototype_ `TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> GetPitchShifter() const;`
- L50 _public prototype_ `Harmonix::Dsp::Modulators::EAdsrStage GetAdsrStage(const FAliasFusionVoice* Requestor) const;`
- L51 _public prototype_ `void SetPitchOffset(FAliasFusionVoice* Requestor, double NumCents);`
- L54 _public prototype_ `void AttackWithTragetNote( FAliasFusionVoice* Requestor, uint8 MidiNoteNumber, float InGain, int32 InEventTick, int32 InTriggerTick, double StartPointMs = 0.0f, const char* FilePath = nullptr) #else void AttackWithTargetNote( FAliasFusionVoice* Requestor, uint8 MidiNoteNumber, float InGain, int32 InEventTick, int32 InTriggerTick, double StartPointMs = 0.0f);`
- L73 _public prototype_ `void FastRelease(FAliasFusionVoice* Requestor);`
- L74 _public prototype_ `void Kill(FAliasFusionVoice* Requestor);`
- L75 _public prototype_ `bool MatchesIDs( const FFusionSampler* InSampler, FMidiVoiceId InVoiceID, const FKeyzoneSettings* InKeyzone = nullptr);`
- L80 _public prototype_ `bool UsesKeyzone(const FKeyzoneSettings* InKeyzone) const;`
- L82 _public prototype_ `void SetupLfo(const FAliasFusionVoice* Requestor, int32 Index, const FLfoSettings& InSettings);`
- L83 _public prototype_ `uint32 Process( FAliasFusionVoice* Requestor, uint32 SliceIndex, uint32 SubsliceIndex, float** Output, uint32 InNumChannels, uint32 InMaxNumSamples, float InSpeed = 1.0f, float InTempoBPM = 120.0f, bool MaintainPitchWhenSpeedChanges = false);`
- L94 _public function_ `FCriticalSection& GetLock()`
- L98 _private member_ `mutable FCriticalSection PoolLock;`
- L123 _private member_ `FCachedVoiceTracker PrimaryTracker;`
- L124 _private member_ `FCachedVoiceTracker ReleasingTracker;`
- L125 _private member_ `FKeyzoneSettings& KeyzoneRef;`
- L126 _private member_ `TArray<FAliasFusionVoice> Aliases;`
- L128 _private member_ `FAliasFusionVoice* DriverVoice = nullptr;`
- L130 _private member_ `int32 NumActiveAliases = 0;`
- L132 _private prototype_ `bool Relinquish(FFusionVoice* InVoice);`

#### struct `FSingletonFusionVoicePool::FCachedVoiceTracker`  
`struct FCachedVoiceTracker`  
_L100-121_
- L102 _public member_ `FFusionVoice* Voice = nullptr;`
- L105 _public member_ `uint32 SliceIndex = std::numeric_limits<uint32>::max();` — the last rendered frame info
- L106 _public member_ `uint32 SubsliceIndex = std::numeric_limits<uint32>::max();`
- L108 _public member_ `uint32 NumFramesLastRendered = 0;`
- L111 _public member_ `TAudioBuffer<float> CachedBuffer;` — cached rendered audio
- L113 _public function_ `FCachedVoiceTracker& operator=(const FCachedVoiceTracker& Other)`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/GainMatrix.h` (Public)


#### class `FGainMatrix`  
`class alignas(16) FGainMatrix`  
_L17-328_
- L21 _public prototype_ `static void Init();`
- L23 _public function_ `FGainMatrix()`
- L29 _public function_ `FGainMatrix(EAudioBufferChannelLayout layout) : ChannelMask(0)`
- L34 _public function_ `FGainMatrix(EAudioBufferChannelLayout layout, float InGain)`
- L41 _public function_ `FGainMatrix(int32 InNumInChannels, int32 InNumOutChannels, EAudioBufferChannelLayout InChannelLayout)`
- L47 _public function_ `FGainMatrix(int32 InNumInChannels, int32 InNumOutChannels, EAudioBufferChannelLayout InChannelLayout, uint32 InChannelMask)`
- L53 _public function_ `FGainMatrix(int32 InNumInChannels, int32 InNumOutChannels, EAudioBufferChannelLayout InChannelLayout, float InGain)`
- L59 _public function_ `FGainMatrix(int32 InNumInChannels, int32 InNumOutChannels, EAudioBufferChannelLayout InChannelLayout, uint32 InChannelMask, float InGain)`
- L65 _public function_ `int32 GetNumInChannels() const`
- L66 _public function_ `int32 GetNumOutChannels() const`
- L67 _public function_ `uint32 GetChannelMask() const`
- L68 _public function_ `EAudioBufferChannelLayout GetChannelLayout() const`
- L71 _public prototype_ `void SetFromMinusOneToOneSurroundPan(float InGain, float InPan, const FGainTable* InGainTable = nullptr);` — pan -1 to 1
- L72 _public prototype_ `void SetFromPolarDegrees(float InGain, float InPan, const FGainTable* InGainTable = nullptr);`
- L74 _public prototype_ `void Set(float InGain, float InPanValue, const FGainTable* InGainTable = nullptr);` — pan in radians
- L76 _public prototype_ `void SetFromLegacyStereo(float InGain, float InPan);` — pan -1 to 1
- L77 _public prototype_ `void SetFromNewStereo(float InGain, float InPan, float InMax, const FGainTable* InGainTable = nullptr);`
- L78 _public prototype_ `void Set(float InGain, ESpeakerChannelAssignment InChannelAssignment, const FGainTable* InGainTable = nullptr);`
- L79 _public prototype_ `void Set(float InGain, const FPannerDetails& InPannerDetails, const FGainTable* InGainTable = nullptr);`
- L81 _public function_ `static const FGainMatrix& Unity()`
- L83 _public function_ `void Configure(int32 InNumInChannels, const TAudioBuffer<float>& OutputBuffer)`
- L91 _public function_ `void ConfigureForOutputBuffer(const TAudioBuffer<float>& OutputBuffer)`
- L98 _public function_ `void ApplyToBuffer(float* src, int32 inChannel, float* dest, int32 outChannel, int32 numFrames, bool clear = false) const`
- L125 _public function_ `void ApplyAndAccumulateToBuffer(float* src, int32 InChannel, float* dest, int32 OutChannel, int32 InNumFrames) const`
- L152 _public function_ `void PanSample(float sample, int32 InChannel, float* out, int32 InNumOutChannels)`
- L166 _public function_ `FGainMatrix& Set(int32 InNumInChannels, int32 InNumOutChannels, EAudioBufferChannelLayout layout, uint32 InChannelMask, float InGain)`
- L180 _public function_ `FGainMatrix(const FGainMatrix& start, const FGainMatrix& end, float lerpPos)`
- L185 _public function_ `FGainMatrix& Lerp(const FGainMatrix& start, const FGainMatrix& end, float lerpPos)`
- L213 _public function_ `FGainMatrix operator*(const FGainMatrix& Other) const`
- L228 _public function_ `FGainMatrix operator*(const float& m) const`
- L250 _public function_ `FGainMatrix& operator*=(float gain)`
- L271 _public function_ `FGainMatrix& operator=(float gain)`
- L293 _public function_ `const FChannelGains& operator[](int32 index) const`
- L299 _public function_ `FChannelGains& operator[](int32 index)`
- L305 _public prototype_ `static bool SpeakerChannelAssignmentMapsToOneSpeaker(ESpeakerChannelAssignment InChannelrAssignment, EAudioBufferChannelLayout InChannelLayout);`
- L306 _public prototype_ `static int32 SpeakerChannelAssignmentToChannelIndex(ESpeakerChannelAssignment InChannelAssignment, EAudioBufferChannelLayout InChannelLayout);`
- L310 _private member_ `alignas(16) FChannelGains GainsArray[HarmonixDsp::FAudioBuffer::kMaxChannelsInAudioBuffer] = {};`
- L312 _private member_ `static FGainMatrix* sUnity;`
- L314 _private member_ `uint8 NumInChannels = HarmonixDsp::FAudioBuffer::kMaxChannelsInAudioBuffer;`
- L315 _private member_ `uint8 NumOutChannels = HarmonixDsp::FAudioBuffer::kMaxChannelsInAudioBuffer;`
- L317 _private member_ `EAudioBufferChannelLayout ChannelLayout = EAudioBufferChannelLayout::Raw;`
- L319 _private member_ `uint32 ChannelMask = ESpeakerMask::AllSpeakers;`
- L321 _private prototype_ `static int32 SpeakerToStereo(ESpeakerChannelAssignment InChannelAssignment);`
- L322 _private prototype_ `static int32 SpeakerToStereoPointOne(ESpeakerChannelAssignment InChannelAssignment);`
- L323 _private prototype_ `static int32 SpeakerToQuad(ESpeakerChannelAssignment InChannelAssignment);`
- L324 _private prototype_ `static int32 SpeakerToQuadPointOne(ESpeakerChannelAssignment InChannelAssignment);`
- L325 _private prototype_ `static int32 SpeakerToFive(ESpeakerChannelAssignment InChannelAssignment);`
- L326 _private prototype_ `static int32 SpeakerToFivePointOne(ESpeakerChannelAssignment InChannelAssignment);`
- L327 _private prototype_ `static int32 SpeakerToSevenPointOne(ESpeakerChannelAssignment InChannelAssignment);`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGainMatrix, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGainMatrix, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/GainTable.h` (Public)


#### class `FGainTable`  
`class FGainTable`  
_L24-55_
- L27 _public prototype_ `static void Init(EAudioBufferChannelLayout ChannelLayout = EAudioBufferChannelLayout::Stereo);`
- L28 _public prototype_ `static void SetupPrimaryGainTable(EAudioBufferChannelLayout ChannelLayout);`
- L30 _public prototype_ `static FORCEINLINE FGainTable& Get();`
- L32 _public prototype_ `FGainTable();`
- L34 _public prototype_ `void SetChannelLayout(EAudioBufferChannelLayout ChannelLayout);`
- L36 _public prototype_ `const FChannelGains& GetGains(float PolarAngle) const;`
- L37 _public prototype_ `void PanSample(float InSample, float PolarAngle, FChannelGains& OutGains) const;`
- L39 _public prototype_ `FORCEINLINE float GetDirectChannelAzimuthInCurrentLayout(ESpeakerChannelAssignment ChannelAssignment) const;`
- L41 _public prototype_ `FORCEINLINE void GetGainsForDirectAssignment(ESpeakerChannelAssignment ChannelAssignment, FChannelGains& OutGains) const;`
- L44 _private member_ `EAudioBufferChannelLayout CurrentLayout = EAudioBufferChannelLayout::UnsupportedFormat;`
- L45 _private member_ `int32 SpeakerCount = 0;`
- L46 _private member_ `uint32 SpeakerMask = 0;`
- L48 _private member_ `static const uint32 kGainTableSize = 1024;`
- L49 _private member_ `FChannelGains Entries[kGainTableSize];`
- L51 _private prototype_ `void BuildPanEntriesFromPannableSpeakerAzimuths(int32 NumSpeakers, const float* SpeakerAzimuths, const uint8* InRemap);`
- L52 _private prototype_ `bool CurrentLayoutHasSpeaker(ESpeakerChannelAssignment ChannelAssignment) const;`
- L54 _private member_ `static FGainTable* gGainTable;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGainTable, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGainTable, Log, All);`
- L13 _namespace_ `namespace Harmonix`
- L13 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L13 _namespace_ `namespace GainTable` (scope `Harmonix::Dsp`)
- L15 _variable_ `static const int32 kMaxSpeakers = 8;` (scope `Harmonix::Dsp::GainTable`)
- L18 _typedef_ `using FChannelGains = MS_ALIGN(16) union { VectorRegister4Float simd[Harmonix::Dsp::GainTable::kMaxSpeakers / 4]; float f[Harmonix::Dsp::GainTable::kMaxSpeakers]; } GCC_ALIGN(16);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/GainTable.inl` (Public)


#### Free symbols / members of external scopes

- L6 _externvar_ `extern FGainTable* gGainTable;`
- L8 _function_ `FORCEINLINE FGainTable& FGainTable::Get()` (scope `FGainTable`)
- L14 _function_ `FORCEINLINE float FGainTable::GetDirectChannelAzimuthInCurrentLayout(ESpeakerChannelAssignment InChannelAssignment) const` (scope `FGainTable`)
- L25 _function_ `FORCEINLINE const FChannelGains& FGainTable::GetGains(float PolarAngle) const` (scope `FGainTable`)
- L42 _function_ `FORCEINLINE void FGainTable::PanSample(float InSample, float PolarAngle, FChannelGains& OutGains) const` (scope `FGainTable`)
- L50 _function_ `FORCEINLINE void FGainTable::GetGainsForDirectAssignment(ESpeakerChannelAssignment InChannelAssignment, FChannelGains& OutGains) const` (scope `FGainTable`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Generate.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace HarmonixDsp`
- L9 _prototype_ `void GenerateA220Sawtooth(float* Output, uint32 NumFrames, uint32 SampleRate);` (scope `HarmonixDsp`) — This function is stateful. Doesn't really work for multi channels
- L18 _prototype_ `void GenerateWhiteNoise(float* Output, uint32 NumFrames, float Gain = 1.0f);` (scope `HarmonixDsp`) — fill an output buffer with random sample samples are in the range [-gain, gain] @param output the buffer of floating point samples to write to @param numFrames the number of samples to write @param gain (optional) the upper range of the samples. defaults to one.
- L19 _prototype_ `void GenerateWhiteNoise(int16* Output, uint32 NumFrames, float Gain = 1.0f);` (scope `HarmonixDsp`)
- L22 _function_ `template<class T> void GenerateWhiteNoiseEq(T* Output, uint32 NumFrames, float Gain)` (scope `HarmonixDsp`)
- L35 _prototype_ `void GenerateSine( float* Output, uint32 NumFrames, float Frequency, float SampleRate, float& Phase);` (scope `HarmonixDsp`) — Fill a mono output buffer with a sine wave @param Output - The output buffer @param NumFrames - The number of sample frames to generate @param Frequency - The frequency of the sine wave @param SampleRate - The sample rate at which to generate the sine wave @param Phase - The phase to start (and to use for future calls if desired)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/HarmonixMeterData.h` (Public)


#### class `FHarmonixMeterData`  
`class FHarmonixMeterData`  
_L9-107_
- L12 _public function_ `FHarmonixMeterData(double InMin = 0.0)`
- L28 _public function_ `void GetLatest(double& OutCurrent, double& OutPeak) const` — Get the metering data on the main thread. returns the current value, and the peak. @param current the current data @param peak the peak value since the last cal to ClearPeak @see ClearPeak
- L43 _public function_ `void PeekAtLatest(double& OutCurrent, double& OutPeak) const` — Get the metering data on the main thread without triggering a data clearing returns the current value, and the peak. @param current the current data @param peak the peak value since the last cal to ClearPeak @see ClearPeak
- L59 _public function_ `void ClearPeak()` — Clears the peak data. On the next call to get latest, peak will match current
- L68 _public function_ `void Merge(double InNewData)` — Merge in new data on the audio thread. @param newData the newData to merge into the existing data
- L89 _public function_ `FORCEINLINE void MergeMinimum()` — Merge in the data to minimum on the audio thread. This happens without taking a lock.
- L101 _private member_ `static FCriticalSection sAudioMeterLock;`
- L103 _private member_ `mutable bool bShouldClearDataBeforeNextMerge;`
- L104 _private member_ `double MinimumData;`
- L105 _private member_ `double CurrentData;`
- L106 _private member_ `mutable double PeakData;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Instruments/VirtualInstrument.h` (Public)


#### class `FVirtualInstrument`  
`class FVirtualInstrument : public FMusicalAudioBus`  
_L13-151_
- inherits: `FMusicalAudioBus`
- L17 _public function_ `FVirtualInstrument(FName InName = NAME_None)`
- L23 _public prototype_ `virtual ~FVirtualInstrument() = default;`
- L35 _public function_ `virtual void CallPreProcessCallbacks(int32 NumSamples, float SampleRateHz, int32 SliceIndex, int32 Subslice, bool LastSubslice)`
- L38 _public function_ `virtual bool ProcessCallWillProduceSilence() const` — override this (as an optimization) if calling process may only produce zero samples
- L42 _public prototype_ `void ResetInstrumentState();` — Pure virtuals that deal with instrument state and MIDI message handling...
- L43 _public prototype_ `void ResetMidiState();`
- L44 _public prototype_ `virtual void NoteOn(FMidiVoiceId InVoiceId, int8 MidiNoteNumber, int8 Velocity, int8 MidiChannel = 0, int32 EventTick = 0, int32 CurrentTick = 0, float MsOffset = 0.0f) = 0;`
- L45 _public prototype_ `virtual void NoteOnWithFrameOffset(FMidiVoiceId InVoiceId, int8 MidiNoteNumber, int8 Velocity, int8 MidiChannel = 0, int32 NumFrames = 0) = 0;`
- L46 _public prototype_ `virtual bool NoteIsOn(int8 MidiNoteNumber, int8 MidiChannel = 0) = 0;`
- L47 _public prototype_ `virtual void NoteOff(FMidiVoiceId InVoiceId, int8 MidiNoteNumber, int8 MidiChannel = 0) = 0;`
- L48 _public prototype_ `virtual void NoteOffWithFrameOffset(FMidiVoiceId InVoiceId, int8 MidiNoteNumber, int8 MidiChannel = 0, int32 NumFrames = 0) = 0;`
- L49 _public function_ `virtual void PolyPressure(FMidiVoiceId InVoiceId, int8 InData1, int8 InData2, int8 InChannel = 0)`
- L50 _public function_ `virtual void ChannelPressure(int8 InData1, int8 InData2, int8 InChannel = 0)`
- L53 _public function_ `virtual void SetExtraPitchBend(float Semitones, int8 MidiChannel = 0)` — code-driven pitch bend, in semitones
- L56 _public prototype_ `virtual void SetPitchBend(float InValue, int8 InMidiChannel = 0) = 0;` — pitch bend value, on range [-1.0, 1.0]
- L59 _public prototype_ `virtual float GetPitchBend(int8 InMidiChannel = 0) const = 0;` — pitch bend value, on range [-1.0, 1.0]
- L61 _public prototype_ `virtual void SetRawTransposition(int32 SemiTones) = 0;`
- L62 _public prototype_ `virtual int32 GetRawTransposition() const = 0;`
- L63 _public prototype_ `virtual void SetRawPitchMultiplier(float RawPitch) = 0;`
- L64 _public prototype_ `virtual float GetRawPitchMultiplier() const = 0;`
- L66 _public prototype_ `void Set7BitController(Harmonix::Midi::Constants::EControllerID InController, int8 InByteValue, int8 InMidiChannel = 0);`
- L67 _public prototype_ `void Set14BitController(Harmonix::Midi::Constants::EControllerID InController, int16 InByteValue, int8 InMidiChannel = 0);`
- L69 _public prototype_ `virtual void GetController(Harmonix::Midi::Constants::EControllerID InController, int8& InMsb, int8& InLsb, int8 InMidiChannel = 0) const = 0;`
- L70 _public prototype_ `void SetController(Harmonix::Midi::Constants::EControllerID InController, float InValue, int8 InMidiChannel = 0);`
- L71 _public prototype_ `void SetHighOrLowControllerByte(Harmonix::Midi::Constants::EControllerID InController, int8 InValue, int8 InMidiChannel = 0);`
- L73 _public function_ `virtual float GetController(Harmonix::Midi::Constants::EControllerID InController, int8 InMidiChannel = 0)`
- L81 _public prototype_ `virtual void KillAllVoices() = 0;`
- L82 _public prototype_ `virtual void AllNotesOff() = 0;`
- L83 _public prototype_ `virtual void AllNotesOffWithFrameOffset(int32 InNumFrames = 0) = 0;`
- L85 _public prototype_ `virtual void SetSpeed(float InSpeed, bool MaintainPitch = false) = 0;`
- L86 _public prototype_ `virtual float GetSpeed(bool* MaintainPitch = nullptr) = 0;`
- L89 _public function_ `virtual void SetQuarterNote(float QuarterNote)` — update the effect with the current beat/tempo
- L90 _public function_ `virtual void SetTempo(float Bpm)`
- L92 _public prototype_ `virtual void SetSampleRate(float InSampleRateHz) = 0;`
- L94 _public prototype_ `virtual void HandleMidiMessage(FMidiVoiceId InVoiceId, int8 InStatus, int8 InData1, int8 InData2, int32 InEventTick = 0, int32 InCurrentTick = 0, float InMsOffset = 0.0f);`
- L102 _public function_ `virtual int32 GetMaxNumVoices() const` — get the max number of note-ons this baby can handle before auto-release. note that the actual number of in-use voices may go over this max when voices are in release stage @returns the maximum number of voices this instrument can play before auto-releasing voices @see GetNumVoicesInUse
- L103 _public prototype_ `virtual int32 GetNumVoicesInUse() const = 0;`
- L104 _public function_ `void GetVoiceUsage(int32& OutCurrent, int32& OutPeak) const`
- L112 _public function_ `void ClearPeakVoiceUsage()`
- L114 _public function_ `static bool ShouldPrintMidiActivity()`
- L115 _public function_ `static void SetShouldPrintMidiActivity(bool bInShouldPrint)`
- L117 _public function_ `void SetName(FName InName)`
- L118 _public function_ `FName GetName() const`
- L120 _public function_ `void GetProcessingTimeMs(double& OutCurrent, double& OutPeak) const`
- L121 _public function_ `void ClearPeakProcessingTime()`
- L122 _public function_ `double PeekAtPeakProcessingTime() const`
- L124 _public prototype_ `virtual void SetMidiChannelVolume(float InVolume, float InSeconds = 0.0f, int8 InMidiChannel = 0) = 0;`
- L125 _public prototype_ `virtual float GetMidiChannelVolume(int8 InMidiChannel = 0) const = 0;`
- L126 _public prototype_ `virtual void SetMidiChannelGain(float InGain, float InSeconds = 0.0f, int8 InMidiChannel = 0) = 0;`
- L127 _public prototype_ `virtual float GetMidiChannelGain(int8 InMidiChannel = 0) const = 0;`
- L128 _public prototype_ `virtual void SetMidiChannelMute(bool InMute, int8 InMidiChannel = 0) = 0;`
- L129 _public prototype_ `virtual bool GetMidiChannelMute(int8 InMidiChannel = 0) const = 0;`
- L131 _public prototype_ `static bool IsHighResController(Harmonix::Midi::Constants::EControllerID ControllerId, bool& bIsHighResLowByte);`
- L132 _public prototype_ `static bool GetMsbLsbIndexes(Harmonix::Midi::Constants::EControllerID ControllerId, int& InMsb, int& InLsb);`
- L135 _protected prototype_ `virtual void Set7BitControllerImpl(Harmonix::Midi::Constants::EControllerID InController, int8 InValue, int8 InMidiChannel = 0) = 0;`
- L136 _protected prototype_ `virtual void Set14BitControllerImpl(Harmonix::Midi::Constants::EControllerID InController, int16 InValue, int8 InMidiChannel = 0) = 0;`
- L137 _protected prototype_ `virtual void ResetInstrumentStateImpl() = 0;` — heavy weight! should completely resets the instrument.
- L138 _protected prototype_ `virtual void ResetMidiStateImpl() = 0;` — less heavy weight. should do all notes off, reset pitch bend, etc.
- L141 _protected prototype_ `static float ConvertCCValue(Harmonix::Midi::Constants::EControllerID InController, uint8 InValue);` — convert a value in [0,127] to the range expected by SetController
- L143 _protected member_ `FName Name;`
- L144 _protected member_ `FHarmonixMeterData TimingData;`
- L145 _protected member_ `FHarmonixMeterData VoiceUsage;`
- L146 _protected member_ `static bool bShouldPrintMidiActivity;`
- L148 _protected member_ `FCriticalSection BusLock;`
- L149 _protected member_ `int8 LastCcVals[16][128];`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Modulators/Adsr.h` (Public)


#### enum `Harmonix::Dsp::Modulators::EAdsrStage`  
`enum class EAdsrStage`  
_L11-19_
- L13 _public enumerator_ `Attack`
- L14 _public enumerator_ `Decay`
- L15 _public enumerator_ `Sustain`
- L16 _public enumerator_ `Release`
- L17 _public enumerator_ `Idle`
- L18 _public enumerator_ `Setup`

#### enum `Harmonix::Dsp::Modulators::EAdsrMode`  
`enum class EAdsrMode`  
_L21-26_
- L23 _public enumerator_ `MinUp`
- L24 _public enumerator_ `MaxDown`
- L25 _public enumerator_ `SustainOut`

#### struct `Harmonix::Dsp::Modulators::FAdsr`  
`struct FAdsr`  
_L28-178_
- L32 _public function_ `FAdsr()`
- L39 _public function_ `void UseSettings(const FAdsrSettings* InSettings, bool Reset = true)`
- L50 _public function_ `void Prepare(float InSamplesPerSecond)`
- L55 _public function_ `const FAdsrSettings* GetSettings() const`
- L60 _public prototype_ `float GetValue() const;`
- L61 _public function_ `EAdsrStage GetStage() const`
- L62 _public function_ `uint32 GetAge() const`
- L64 _public prototype_ `void Advance(uint32 InNumSamples);`
- L66 _public function_ `void Attack()`
- L111 _public function_ `void Release()`
- L131 _public function_ `void FastRelease()`
- L150 _public function_ `void Kill()`
- L162 _private member_ `const FAdsrSettings* Settings = nullptr;`
- L164 _private member_ `float SamplesPerSecond = 0.0f;`
- L165 _private member_ `float Gain = 0.0f;`
- L166 _private member_ `EAdsrStage Stage = EAdsrStage::Idle;`
- L167 _private member_ `uint32 Age = 0.0f;`
- L168 _private member_ `float CurveAge = 0.0f;`
- L170 _private member_ `float AttackIncrement = 0.0f;`
- L171 _private member_ `float DecayDecrement = 0.0f;`
- L172 _private member_ `float ReleaseDecrement = 0.0f;`
- L174 _private member_ `bool bIsFastRelease = false;`
- L175 _private member_ `float ReleaseStartingGain = 0.0f;`
- L177 _private member_ `EAdsrMode Mode = EAdsrMode::MinUp;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API HARMONIXDSP_API`
- L8 _namespace_ `namespace Harmonix`
- L8 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L8 _namespace_ `namespace Modulators` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Modulators/Lfo.h` (Public)


#### enum `Harmonix::Dsp::Modulators::ELfoMode`  
`enum class ELfoMode : uint8`  
_L12-17_
- L14 _public enumerator_ `MinUp`
- L15 _public enumerator_ `MaxDown`
- L16 _public enumerator_ `CenterOut`

#### struct `Harmonix::Dsp::Modulators::FWaveShape`  
`struct FWaveShape`  
_L19-46_
- L21 _public typedef_ `typedef float (*FWaveShapeFunction)(float);`
- L24 _public prototype_ `static float Sine(float x);`
- L25 _public prototype_ `static float Square(float x);`
- L26 _public prototype_ `static float SawtoothUp(float x);`
- L27 _public prototype_ `static float SawtoothDown(float x);`
- L28 _public prototype_ `static float Triangle(float x);`
- L29 _public prototype_ `static float Noise(float x);`
- L31 _public function_ `static FWaveShapeFunction GetFunction(EWaveShape WaveShape)`
- L38 _public function_ `static float Apply(EWaveShape WaveShape, float x)`
- L45 _private member_ `static FWaveShapeFunction sWaveShapeTable[(uint8)EWaveShape::Num];`

#### struct `Harmonix::Dsp::Modulators::FLfo`  
`struct FLfo`  
_L53-103_
- desc: this low-frequency oscillator (LFO) class is considered low-frequency because it doesn't do anything about aliasing, which is audible if the frequency is in the audible range. infrasonic frequencies are the target for this implementation.
- L57 _public prototype_ `FLfo();`
- L59 _public prototype_ `void Prepare(float InSampleRate);`
- L62 _public typedef_ `typedef float (*FWaveShapeFunction)(float);` — input is [0,1], returns [0,1]
- L64 _public prototype_ `void UseSettings(const FLfoSettings* InSettings);`
- L66 _public function_ `const FLfoSettings* GetSettings() const`
- L71 _public prototype_ `void SetPhase(double InPhase);`
- L73 _public prototype_ `double GetPhase() const;`
- L77 _public prototype_ `void Retrigger();` — sets phase to the initial phase indicated by the user setting (and possibly by the shape)
- L79 _public prototype_ `TInterval<float> GetRange() const;`
- L80 _public prototype_ `void SetRangeAndMode(const TInterval<float>& InRange, ELfoMode InMode);`
- L83 _public prototype_ `void Advance(uint32 InNumSamples);` — advances the phase of the oscillator
- L85 _public prototype_ `float GetValue() const;`
- L87 _private prototype_ `void ComputeCyclesPerSample();`
- L89 _private member_ `double Phase;`
- L92 _private member_ `TInterval<float> Range;`
- L93 _private member_ `ELfoMode Mode;`
- L98 _private member_ `const FLfoSettings* Settings;` — patch-level settings used as long as these settings are not overridden by and ADSR.
- L100 _private member_ `double CyclesPerSample;`
- L101 _private member_ `float SecondsPerSample;`
- L102 _private member_ `float TempoWhenCalculated;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixDsp_Lfo, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixDsp_Lfo, Log, All);`
- L9 _namespace_ `namespace Harmonix`
- L9 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L9 _namespace_ `namespace Modulators` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Modulators/Modulator.h` (Public)


#### class `Harmonix::Dsp::Modulators::FModulator`  
`class FModulator`  
_L11-67_
- L15 _public prototype_ `FModulator();`
- L25 _public prototype_ `void SetTarget(const FModulatorTarget* InTarget);` — Set the modulator target. This class does not take ownership of the modulator target, and will never delete it. @param target the target to modulate when Modulate is called. @returns description of the retumrn type @see Modulate()
- L31 _public prototype_ `const FModulatorTarget* GetTarget() const;` — Get the modulator target. @returns description of the return type
- L37 _public prototype_ `float GetDepth() const;` — gets the depth (efficacy) of the randomization effect. @returns the depth on the range [0,1]
- L44 _public prototype_ `void SetDepth(float InDepth);` — set the depth (efficacy) of the randomization effect @param depth a value on in the range [0,1] that describes the degree to which randomization occurs @returns description of the return type
- L46 _public prototype_ `void SetRangeMagnitude(float Magnitude);`
- L47 _public prototype_ `float GetRangeMagnitude() const;`
- L53 _public prototype_ `void Reset();` — resets to defaults.
- L59 _public prototype_ `void Modulate(float InputNorm);` — modulates the target value based on the input value @param normalized number in range [0,1] to map to range and to modulate the target
- L63 _protected member_ `const FModulatorTarget* Target;`
- L64 _protected member_ `float Depth;`
- L65 _protected member_ `float RangeMagnitude;`
- L66 _protected member_ `TInterval<float> Range;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Harmonix`
- L6 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L6 _namespace_ `namespace Modulators` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Modulators/ModulatorTarget.h` (Public)


#### enum `Harmonix::Dsp::Modulators::EDepthMode`  
`enum class EDepthMode : uint8`  
_L9-19_
- L12 _public enumerator_ `MinUp` — Modulate to the minimum end of the range for 0% depth
- L15 _public enumerator_ `MaxDown` — Modulate to the maximum end of the range for 0% depth
- L18 _public enumerator_ `CenterOut` — Modulate to the center of the range for 0% depth

#### struct `Harmonix::Dsp::Modulators::FModulatorTarget`  
`struct FModulatorTarget`  
_L25-69_
- desc: a struct that contains data about a modulator target. including its name, range of modulation, etc.
- L29 _public member_ `static const FName kStartPointName;`
- L30 _public member_ `static const FName kPitchName;`
- L33 _public function_ `FModulatorTarget()`
- L34 _public prototype_ `FModulatorTarget(FName InName, float InDefaultRangeMag, const FString& InUnits, EDepthMode DepthMode, float* ValueToTarget);`
- L42 _public prototype_ `float ApplyDepthToNormalizedValue(float x, float depth) const;` — take a number on [0,1] and transform it based on a depth @param x the number to map @param depth the depth to use in mapping @returns a transformed version of x mapped to the target's range
- L44 _public function_ `FName GetName() const`
- L45 _public function_ `const FString& GetUnits() const`
- L46 _public function_ `float GetDefaultRangeMagnitude() const`
- L47 _public prototype_ `TInterval<float> GetRangeWithMagnitude(float InMagnitude) const;`
- L49 _public function_ `float* GetTargetFloat() const`
- L51 _public member_ `static FModulatorTarget kDummyTarget;`
- L56 _private member_ `FName Name;` — Name of the modulator target
- L59 _private member_ `float DefaultRangeMag = 0.0f;` — hint for reasonable range
- L62 _private member_ `FString Units;` — units the range is expressed in
- L65 _private member_ `float* TargetFloat = nullptr;` — reference to the value to modulate
- L68 _private member_ `EDepthMode DepthMode = EDepthMode::MinUp;` — how to apply a depth of less than 100%

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Harmonix`
- L6 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L6 _namespace_ `namespace Modulators` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Modulators/MorphingLfo.h` (Public)


#### class `Harmonix::Dsp::Modulators::FMorphingLFO`  
`class FMorphingLFO`  
_L17-92_
- desc: @brief A clock-sync-able LFO with a morphing waveform
- L20 _public prototype_ `explicit FMorphingLFO(float InSampleRate);`
- L22 _public prototype_ `float GetSampleRate() const;`
- L27 _public member_ `Parameters::TParameter<ETimeSyncOption> SyncType{ ETimeSyncOption::None, ETimeSyncOption::SpeedScale, ETimeSyncOption::None };` — @brief Determines how the frequency parameter behaves
- L32 _public member_ `Parameters::TParameter<float> Frequency{ UE_SMALL_NUMBER, 40.0f, 1.0f };` — @brief If LfoSyncType is TempoSync, the unit is cycles per quarter note. Otherwise, it's Hz.
- L37 _public member_ `Parameters::TParameter<bool> Invert{ false, true, false };` — @brief If set, the output will be inverted
- L42 _public member_ `Parameters::TParameter<float> Shape{ 0.0f, 2.0f, 1.0f };` — @brief Determines the shape of the output 0.0-1.0 morphs from square to triangle, 1.0-2.0 morphs from triangle to sawtooth
- L48 _public prototype_ `void Reset(float InSampleRate);` — @brief Reset the LFO to its initial state @param InSampleRate - The sample rate
- L67 _public prototype_ `void Advance(const int32 DeltaFrames, float& Output, const FMusicTimingInfo* MusicTimingInfo = nullptr);` — @brief Advance and output the last value @param DeltaFrames - The amount of time in audio frames to advance @param Output - The LFO output @param MusicTimingInfo - (optional) The music timing info to use if appropriate
- L75 _public prototype_ `void Advance(float* OutputBuffer, int32 NumFrames, const FMusicTimingInfo* MusicTimingInfo = nullptr);` — @brief Advance and output a buffer of LFO values @param OutputBuffer - The buffer of LFO outputs @param NumFrames - The number of frames to advance, which should match the size of the buffer @param MusicTimingInfo - (optional) The music timing info to use if appropriate
- L83 _public prototype_ `static float GetValue(const float Shape, const float Phase);` — @brief Get the LFO value for a given shape and phase. @param Shape - The shape of the LFO, range [0.0, 2.0]. See Shape field for more info. @param Phase - The current phase, range [0.0, 1.0] @return
- L86 _private prototype_ `static float GetFrequencyHz(const ETimeSyncOption SyncType, const float Frequency, const float Tempo, const float Speed);`
- L87 _private prototype_ `static float GetClockSyncedPhase(const float CyclesPerQuarter, const FMusicTimingInfo& MusicTimingInfo);`
- L89 _private member_ `float SampleRate;`
- L90 _private member_ `float Phase;`
- L91 _private member_ `float LastFrequency ;`

#### struct `Harmonix::Dsp::Modulators::FMorphingLFO::FMusicTimingInfo`  
`struct FMusicTimingInfo`  
_L53-59_
- desc: @brief Contains the information necessary to do music clock sync
- L55 _public member_ `FMusicTimestamp Timestamp;`
- L56 _public member_ `FTimeSignature TimeSignature;`
- L57 _public member_ `float Tempo = 0;`
- L58 _public member_ `float Speed = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXDSP_API`
- L12 _namespace_ `namespace Harmonix`
- L12 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L12 _namespace_ `namespace Modulators` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Modulators/Settings/AdsrSettings.h` (Public)


#### enum `EAdsrTarget`  
`enum class EAdsrTarget : uint8`  
_L9-15_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `Volume UMETA(Json="volume")`
- L12 _public enumerator_ `FilterFreq UMETA(Json="filter_freq")`
- L13 _public enumerator_ `Num UMETA(Hidden)`
- L14 _public enumerator_ `Invalid UMETA(Hidden)`

#### struct `FAdsrSettings`  
`struct FAdsrSettings`  
_L18-167_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public member_ `static const float kMinTimeSec;`
- L26 _public member_ `EAdsrTarget Target = EAdsrTarget::Volume;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L29 _public member_ `bool IsEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category="Settings")`
- L32 _public member_ `float AttackTime = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", DisplayName = "Attack (Seconds)", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10"))`
- L35 _public member_ `float DecayTime = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", DisplayName = "Decay (Seconds)", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10"))`
- L38 _public member_ `float SustainLevel = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin="0", UIMax="1", ClampMin="0", ClampMax="1"))`
- L41 _public member_ `float ReleaseTime = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", DisplayName = "Release (Seconds)", Meta = (UIMin = "0", UIMax = "10", ClampMin = "0", ClampMax = "10"))`
- L44 _public member_ `float Depth = 0.5f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", Meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1"))`
- L53 _public member_ `float AttackCurve = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", DisplayName = "Attack Curve", Meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))` — Control the shape of the attack curve: 0: Linear <0: Exponential >0: Logarithmic
- L62 _public member_ `float DecayCurve = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", DisplayName = "Decay Curve", Meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))` — Control the shape of the attack curve: 0: Linear <0: Exponential >0: Logarithmic
- L71 _public member_ `float ReleaseCurve = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category="Settings", DisplayName = "Release Curve", Meta = (UIMin = "-1", UIMax = "1", ClampMin = "-1", ClampMax = "1"))` — Control the shape of the attack curve: 0: Linear <0: Exponential >0: Logarithmic
- L73 _public member_ `static const uint32 kCurveTableSize = 20;`
- L75 _public member_ `float AttackUsedForTable = -1.0f;`
- L76 _public member_ `float AttackCurveTable[kCurveTableSize];`
- L78 _public member_ `float DecayUsedForTable = -1.0f;`
- L79 _public member_ `float DecayCurveTable[kCurveTableSize];`
- L81 _public member_ `float ReleaseUsedForTable = -1.0f;`
- L82 _public member_ `float ReleaseCurveTable[kCurveTableSize];`
- L84 _public function_ `FAdsrSettings()`
- L86 _public function_ `void ResetToDefaults()`
- L104 _public function_ `void Calculate()`
- L111 _public function_ `void CopySettings(const FAdsrSettings& Other)`
- L124 _public prototype_ `void CopyCurveTables(const FAdsrSettings& Other);`
- L126 _public function_ `bool HasDecayStage() const`
- L128 _public function_ `bool IsAttackLinear() const`
- L129 _public function_ `bool IsDecayLinear() const`
- L130 _public function_ `bool IsReleaseLinear() const`
- L131 _public function_ `bool IsCurveLinear(float InCurve) const`
- L133 _public function_ `void BuildAttackTable()`
- L141 _public function_ `void BuildDecayTable()`
- L150 _public function_ `void BuildReleaseTable()`
- L159 _public function_ `float LerpAttackCurve(float index) const`
- L160 _public function_ `float LerpDecayCurve(float index) const`
- L161 _public function_ `float LerpReleaseCurve(float index) const`
- L162 _public prototype_ `float LerpCurve(float index, bool down, const float* curve) const;`
- L166 _private prototype_ `void BuildCurveTable(float curve, bool down, float* table);`

#### struct `FAdsrSettingsArray`  
`struct FAdsrSettingsArray`  
_L170-176_
- reflection: `USTRUCT()`
- L175 _public member_ `FAdsrSettings Array[2];` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Modulators/Settings/LfoSettings.h` (Public)


#### enum `EWaveShape`  
`enum class EWaveShape : uint8`  
_L7-17_
- reflection: `UENUM(BlueprintType)`
- L9 _public enumerator_ `Sine UMETA(Json="sine")`
- L10 _public enumerator_ `Square UMETA(Json="square")`
- L11 _public enumerator_ `SawUp UMETA(Json="saw_up")`
- L12 _public enumerator_ `SawDown UMETA(Json="saw_down")`
- L13 _public enumerator_ `Triangle UMETA(Json="triangle")`
- L14 _public enumerator_ `Random UMETA(Json="random")`
- L15 _public enumerator_ `Num UMETA(Hidden)`
- L16 _public enumerator_ `None UMETA(Hidden)`

#### enum `ELfoTarget`  
`enum class ELfoTarget : uint8`  
_L20-27_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `Pan UMETA(Json="pan")`
- L23 _public enumerator_ `Pitch UMETA(Json="pitch")`
- L24 _public enumerator_ `FilterFreq UMETA(Json="filter_freq")`
- L25 _public enumerator_ `Num UMETA(Hidden)`
- L26 _public enumerator_ `None UMETA(Hidden)`

#### struct `FLfoSettings`  
`struct FLfoSettings`  
_L30-102_
- reflection: `USTRUCT(BlueprintType)`
- L37 _public member_ `ELfoTarget Target = ELfoTarget::None;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L40 _public member_ `bool IsEnabled = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L43 _public member_ `EWaveShape Shape = EWaveShape::Sine;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L46 _public member_ `bool ShouldRetrigger = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L49 _public member_ `bool BeatSync = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L52 _public member_ `float Freq = 4.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", DisplayName = "Freq (Hz)", Meta = (UIMin = "0.01", UIMax = "40.0", ClampMin = "0.01", ClampMax = "40.0"))`
- L55 _public member_ `float Depth = 0.5f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))`
- L58 _public member_ `float InitialPhase = 0.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "0.0", UIMax = "0.99", ClampMin = "0.0", ClampMax = "0.99"))`
- L61 _public member_ `float TempoBPM = 120.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = "1", UIMax = "240", ClampMin = "1", ClampMax = "240"))`
- L63 _public function_ `FLfoSettings()`
- L64 _public function_ `FLfoSettings(ELfoTarget InTarget) : Target(InTarget)`
- L77 _public function_ `void ResetToDefaults()`
- L90 _public function_ `void CopySettings(const FLfoSettings& Other)`

#### struct `FLfoSettingsArray`  
`struct FLfoSettingsArray`  
_L105-111_
- reflection: `USTRUCT()`
- L110 _public member_ `FLfoSettings Array[2];` — `UPROPERTY()`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Modulators/Settings/ModulatorSettings.h` (Public)


#### enum `EModulatorTarget`  
`enum class EModulatorTarget : uint8`  
_L11-17_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `StartPoint UMETA(Json = "Start Point")`
- L14 _public enumerator_ `Pitch UMETA(Json = "Pitch")`
- L15 _public enumerator_ `Num UMETA(Hidden)`
- L16 _public enumerator_ `None UMETA(Hidden, Json = "None")`

#### struct `FModulatorSettings`  
`struct FModulatorSettings`  
_L20-35_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public prototype_ `FModulatorSettings();`
- L28 _public member_ `EModulatorTarget Target = EModulatorTarget::None;` — `UPROPERTY(EditDefaultsOnly, Category="Harmonix|DSP")`
- L31 _public member_ `float Range = 1.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0.0", UIMax = "1000000.0", ClampMin = "0.0", ClampMax = "1000000.0"))`
- L34 _public member_ `float Depth = 0.5f;` — `UPROPERTY(EditDefaultsOnly, Category = "Harmonix|DSP", Meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))`

#### struct `FModulatorSettingsArray`  
`struct FModulatorSettingsArray`  
_L38-44_
- reflection: `USTRUCT()`
- L43 _public member_ `FModulatorSettings Array[2];` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/MusicalAudioBus.h` (Public)


#### class `IMusicalAudioBusOwner`  
`class IMusicalAudioBusOwner`  
_L14-20_
- desc: virtual interface for owners of musical audio buses
- L17 _public prototype_ `virtual ~IMusicalAudioBusOwner() = default;`
- L19 _public prototype_ `virtual void BusWillDestruct(const class FMusicalAudioBus*) = 0;`

#### class `FMusicalAudioBus`  
`class FMusicalAudioBus`  
_L22-77_
- L25 _public prototype_ `FMusicalAudioBus();`
- L26 _public prototype_ `virtual ~FMusicalAudioBus();`
- L28 _public function_ `void SetOwner(class IMusicalAudioBusOwner* InOwner)`
- L30 _public prototype_ `virtual void Prepare(float InSampleRateHz, uint32 InNumChannels, uint32 InMaxSamples, bool bInAllocateBuffer = true);`
- L31 _public prototype_ `virtual void Prepare(float InSampleRateHz, EAudioBufferChannelLayout InChannelLayout, uint32 InMaxSamples, bool bInAllocateBuffer = true);`
- L32 _public prototype_ `virtual void Prepare(float InSampleRateHz, uint32 InNumChannels, EAudioBufferChannelLayout InChannelLayout, uint32 InMaxSamples, bool bInAllocateBuffer = true);`
- L33 _public prototype_ `virtual void SetSampleRate(float InSampleRateHz);`
- L35 _public prototype_ `virtual void Process(uint32 InSliceIndex, uint32 InSubsliceIndex, TAudioBuffer<float>& OutBuffer) = 0;`
- L37 _public function_ `virtual void LockBus()`
- L38 _public function_ `virtual bool TryLockBus()`
- L39 _public function_ `virtual void UnlockBus()`
- L40 _public function_ `virtual FCriticalSection& GetBusLock()`
- L42 _public function_ `virtual void TearDown()`
- L44 _public function_ `virtual bool CanProcessFromWorkerThread() const`
- L46 _public function_ `double GetSamplesPerSecond() const`
- L47 _public function_ `double GetSecondsPerSample() const`
- L48 _public function_ `int32 GetMaxFramesPerProcessCall() const`
- L50 _public function_ `int32 GetNumAudioOutputChannels() const`
- L51 _public function_ `EAudioBufferChannelLayout GetChannelLayout() const`
- L53 _public function_ `float GetAudioLevel() const`
- L60 _protected member_ `TAudioBuffer<float> BusBuffer;`
- L64 _private member_ `float AudioLevel;`
- L65 _private member_ `float AudioLevelDecay;`
- L67 _private member_ `int32 MaxSamples;`
- L68 _private member_ `int32 NumAudioOutputChannels;`
- L69 _private member_ `EAudioBufferChannelLayout ChannelLayout;`
- L71 _private member_ `double SamplesPerSecond;`
- L72 _private member_ `double SecondsPerSample;`
- L74 _private member_ `IMusicalAudioBusOwner* Owner;`
- L76 _private member_ `FCriticalSection BusLock;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/ObjectPool.h` (Public)


#### class `Harmonix::TDynamicObjectPool`  
`template<typename TObject> class TDynamicObjectPool`  
_L23-219_
- desc: A generic pool used to dynamically allocate objects Objects are stored as SharedPtrs Objects are returned as SharedPtrs So resetting the pool won't auto-delete items created by the pool Implemented to be thread safe
- L27 _public typedef_ `using FSharedObjectPtr = TSharedPtr<TObject, ESPMode::ThreadSafe>;`
- L28 _public typedef_ `using FWeakObjectPtr = TWeakPtr<TObject, ESPMode::ThreadSafe>;`
- L37 _public function_ `FORCEINLINE int32 TryAllocate(int32 Num, TFunction<FSharedObjectPtr()> InFactoryMethod, bool bInAllowGrowth = false)` — Attempts to allocate Num number of objects, given a factory method Allows the FactoryMethod to return a nullptr, which will get culled from the pool. This means the number of instances allocated can be less than the number requested. @return	number of instances successfully created and pooled. Can be fewer than Num requested.
- L66 _public function_ `void Allocate(int32 Num, TFunction<FSharedObjectPtr()> InFactoryMethod, bool bInAllowGrowth = false)` — allocates Num number of objects, given a factory method
- L93 _public function_ `void Reset()` — Resets the internal storage to no longer track allocated objects This does not immediately delete the allocated objects Deletion is managed by the SharedPtrs
- L108 _public function_ `FSharedObjectPtr GetFreeShared()` — Get a "free" object from the pool, that isn't in use return value is TSharedPtr, so it'll stay valid even after the pool resets return null if there is no free instance.
- L140 _public function_ `FWeakObjectPtr GetFreeWeak()` — Get a "free" object from the pool, that isn't in use return value is TWeakPtr, so it's not guaranteed to be valid after the pool resets return null if there is no free instance.
- L145 _public function_ `void ReturnToPool(TSharedPtr<TObject> Object)`
- L170 _public function_ `bool IsInitialized() const`
- L177 _public function_ `bool CanGrow() const`
- L182 _public function_ `int32 GetNumAllocated() const`
- L189 _public function_ `int32 GetNumInUse() const`
- L196 _public function_ `int32 GetNumFree() const`
- L203 _public function_ `void ForEachObject(TUniqueFunction<void(FSharedObjectPtr)> DoWork) const`
- L213 _private member_ `mutable FCriticalSection PoolLock;`
- L215 _private member_ `int32 NumInUse = 0;`
- L216 _private member_ `bool bAllowGrowth = false;`
- L217 _private member_ `TArray<FSharedObjectPtr> Objects;`
- L218 _private member_ `TFunction<FSharedObjectPtr()> FactoryMethod;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Harmonix`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Panner.h` (Public)


#### struct `FPanner`  
`struct alignas(16) FPanner`  
_L11-173_
- L14 _public function_ `FPanner() : AggregatedPanRamper((float)(-UE_PI), (float)UE_PI)`
- L22 _public function_ `void Reset()`
- L30 _public function_ `void Setup(const FPannerDetails& InPannerDetails, int32 InNumInChannels, int32 InNumOutChannels, EAudioBufferChannelLayout InChannelLayout, uint32 InChannelMask, float InitialGain, const FGainTable* InGainTable = nullptr)`
- L45 _public function_ `void SetupSimpleMonoPanner(const FPannerDetails& InPannerDetails, int32 InNumOutChannels, EAudioBufferChannelLayout InChannelLayout, const FGainTable* InGainTable = nullptr)`
- L52 _public function_ `void SetStartingPan(const FPannerDetails& InPannerDetails, float InGain, bool bInSnap)`
- L66 _public function_ `const FPannerDetails& GetOriginalPannerDetails() const`
- L68 _public function_ `void SetRampTimeMs(float InNumCallsPerSec, float InRampTimeMs)`
- L74 _public function_ `void SetPanOffset_Radians(float rad)`
- L79 _public function_ `void SetPanOffsetTarget_Radians(float rad)`
- L84 _public function_ `float GetAggregatedPan_Radians() const`
- L88 _public function_ `void SetPanOffset_Degrees(float deg)`
- L94 _public function_ `void SetPanOffsetTarget_Degrees(float deg)`
- L99 _public function_ `float GetAggregatedPan_Degrees() const`
- L103 _public prototype_ `void SetPanOffset_Stereo(float minusOneToOne);`
- L104 _public prototype_ `void SetPanOffsetTarget_Stereo(float minusOneToOne);`
- L105 _public function_ `void SetEdgeProximityOffset(float ep)`
- L110 _public function_ `void SetEdgeProximityOffsetTarget(float ep)`
- L115 _public function_ `float GetCurrentEdgeProximityOffset() const`
- L121 _public function_ `void SetOverallGain(float gain)`
- L129 _public function_ `float GetOverallGain() const`
- L131 _public function_ `void Ramp()`
- L141 _public function_ `void ConfigureForOutputBuffer(const TAudioBuffer<float>& buff)`
- L145 _public function_ `void Configure(int32 inChCount, const TAudioBuffer<float>& buff)`
- L149 _public function_ `const FGainMatrix& GetCurrentGainMatrix()`
- L153 _private member_ `alignas(16) FGainMatrix CurrentGainMatrix;`
- L154 _private member_ `FPannerDetails OriginalPannerDetails;`
- L155 _private member_ `float StartingPolarPan = 0.0f;`
- L156 _private member_ `float StartingEdgeProximity = 1.0f;`
- L157 _private member_ `float OffsetPan = 0.0f;`
- L158 _private member_ `float OffsetEdgeProximity = 1.0f;`
- L159 _private member_ `float OverallGain = 1.0f;`
- L160 _private member_ `TLinearCircularRamper<float> AggregatedPanRamper;`
- L161 _private member_ `TLinearRamper<float> EdgeProximityRamper;`
- L162 _private member_ `const FGainTable* GainTable = nullptr;`
- L164 _private function_ `void UpdateRampers(bool bInSnap)`
- L169 _private prototype_ `void UpdatePanRamper(bool bInSnap);`
- L170 _private prototype_ `void UpdateEdgeProximityRamper(bool bInSnap);`
- L171 _private prototype_ `void UpdateGainMatrix();`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/PannerDetails.h` (Public)


#### enum `EPannerMode`  
`enum class EPannerMode : uint8`  
_L16-25_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `LegacyStereo UMETA(Json="legacy_stereo")`
- L19 _public enumerator_ `Stereo UMETA(Json="stereo")`
- L20 _public enumerator_ `Surround UMETA(Json="surround")`
- L21 _public enumerator_ `PolarSurround UMETA(Json="polar")`
- L22 _public enumerator_ `DirectAssignment UMETA(Json="direct_assign")`
- L23 _public enumerator_ `Num UMETA(Hidden)`
- L24 _public enumerator_ `Invalid UMETA(Hidden)`

#### struct `FPannerDetails`  
`struct FPannerDetails`  
_L28-181_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `static const uint8 kVersion = 0;`
- L50 _public prototype_ `bool Serialize(FArchive& Ar);`
- L52 _public member_ `EPannerMode Mode;`
- L54 _public member_ `FDetail Detail;`
- L56 _public function_ `FPannerDetails() : Mode(EPannerMode::LegacyStereo)`
- L62 _public function_ `FPannerDetails(float InPan) : Mode(EPannerMode::LegacyStereo)`
- L69 _public function_ `FPannerDetails(ESpeakerChannelAssignment InChannelAssignment) : Mode(EPannerMode::DirectAssignment)`
- L74 _public function_ `FPannerDetails(float InPan, float InEdgeProximity) : Mode(EPannerMode::Surround)`
- L80 _public function_ `FPannerDetails(EPannerMode InMode, float InPan, float InEdgeProximity) : Mode(InMode)`
- L87 _public function_ `void Reset()`
- L93 _public function_ `float GetBasicPan()`
- L102 _public function_ `bool operator==(const FPannerDetails& Other) const`
- L115 _public function_ `bool operator!=(const FPannerDetails& Other) const`
- L120 _public function_ `bool IsCircular() const`
- L127 _public function_ `bool IsPannable() const`
- L136 _public function_ `void ToPolarRadiansAndEdgeProximity(float& OutRadians, float& OutMinRadians, float& OutMaxRadians, float& OutEdgeProximity) const`

#### struct `FPannerDetails::FDetail`  
`struct FDetail`  
_L33-45_
- L40 _public function_ `void Reset()`

#### union `FPannerDetails::FDetail::(anonymous)`  
`union`  
_L35-38_

#### struct `FPannerDetails::FDetail::__anon941c2215010a::(anonymous)`  
`struct`  
_L36-36_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPannerDetails> : public TStructOpsTypeTraitsBase2<FPannerDetails>`  
_L184-190_
- inherits: `TStructOpsTypeTraitsBase2<FPannerDetails>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L187-189_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXDSP_API`
- L36 _member_ `struct { float Pan; float EdgeProximity; };` (scope `FPannerDetails::FDetail::__anon941c2215010a::__anon941c22150208`)
- L36 _member_ `struct { float Pan; float EdgeProximity; };` (scope `FPannerDetails::FDetail::__anon941c2215010a::__anon941c22150208`)
- L37 _member_ `ESpeakerChannelAssignment ChannelAssignment;` (scope `FPannerDetails::FDetail::__anon941c2215010a`)
- L188 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon941c22150303`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Parameters/Parameter.h` (Public)


#### struct `Harmonix::Dsp::Parameters::TIsBoolean`  
`template<typename T> struct TIsBoolean`  
_L12-12_
- desc: helpers to avoid some compile errors and to optimize bool parameters
- L12 _public member_ `template<typename T> struct TIsBoolean { static const bool Value = false; };` — helpers to avoid some compile errors and to optimize bool parameters
- L15 _public member_ `template<> struct TIsBoolean<bool> { static const bool Value = true; };`

#### struct `Harmonix::Dsp::Parameters::TIsBoolean`  
`template<> struct TIsBoolean<bool>`  
_L15-15_
- L12 _public member_ `template<typename T> struct TIsBoolean { static const bool Value = false; };` — helpers to avoid some compile errors and to optimize bool parameters
- L15 _public member_ `template<> struct TIsBoolean<bool> { static const bool Value = true; };`

#### class `Harmonix::Dsp::Parameters::TParameter`  
`template<typename T> class TParameter`  
_L22-160_
- desc: An atomic config value for something that needs configuring @tparam T The underlying type of the parameter.
- L25 _public function_ `TParameter(T Min, T Max, T Default, T Step = static_cast<T>(0)) : Min(FMath::Min(Min, Max)), Max(FMath::Max(Min, Max)), Default(FMath::Clamp(Default, this->Min, this->Max)), Step(Step), Value(this->Default)`
- L35 _public function_ `TParameter(T Min, T Max) : TParameter(Min, Max, Min)` — constructor for simple parameter with min, max, and step = 0; Default value is set to Min
- L39 _public member_ `const T Min;`
- L40 _public member_ `const T Max;`
- L41 _public member_ `const T Default;`
- L42 _public member_ `const T Step;`
- L44 _public function_ `void Set(T InValue)`
- L69 _public function_ `T Get() const`
- L75 _public function_ `TParameter(const TParameter& Other) : Min(Other.Min), Max(Other.Max), Default(Other.Default), Step(Other.Step)` — copy constructor
- L82 _public function_ `TParameter& operator=(const TParameter& Other)` — assignment operator
- L88 _public function_ `bool operator==(const TParameter& Other) const`
- L93 _public function_ `bool operator!=(const TParameter& Other) const`
- L98 _public function_ `bool operator<(const TParameter& Other) const`
- L103 _public function_ `bool operator>(const TParameter& Other) const`
- L108 _public function_ `bool operator<=(const TParameter& Other) const`
- L113 _public function_ `bool operator>=(const TParameter& Other) const`
- L118 _public function_ `inline TParameter& operator=(const T& InValue)`
- L124 _public function_ `TParameter& operator+=(const T& InValue)`
- L130 _public function_ `TParameter& operator-=(const T& InValue)`
- L136 _public function_ `TParameter& operator*=(const T& InValue)`
- L142 _public function_ `TParameter& operator/=(const T& InValue)`
- L148 _public function_ `operator T() const`
- L153 _public function_ `bool operator==(const T& InValue) const`
- L159 _private member_ `std::atomic<T> Value;`

#### class `Harmonix::Dsp::Parameters::FBoolParameter`  
`class FBoolParameter : public TParameter<bool>`  
_L163-168_
- inherits: `TParameter<bool>`
- desc: Helper to make bool parameters easier to work with
- L166 _public function_ `explicit FBoolParameter(const bool Default) : TParameter(false, true, Default, true)`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Harmonix`
- L8 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L8 _namespace_ `namespace Parameters` (scope `Harmonix::Dsp`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/PitchShifterName.h` (Public)


#### struct `FPitchShifterName`  
`struct FPitchShifterName`  
_L12-31_
- reflection: `USTRUCT()`
- desc: struct with detail customization for drop down selection of registered factories
- L16 _public function_ `FPitchShifterName(const FName& InName) : Name(InName)`
- L17 _public function_ `FPitchShifterName() : Name(NAME_None)`
- L20 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Pitch Shifter")`
- L22 _public function_ `operator FName() const`
- L23 _public function_ `FPitchShifterName& operator=(const FName& InName)`
- L29 _public function_ `bool operator==(const FName& InName) const`
- L30 _public function_ `bool operator!=(const FName& InName) const`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Ramper.h` (Public)


#### enum `ERamperMode`  
`enum class ERamperMode : uint8`  
_L9-14_
- L11 _public enumerator_ `Linear`
- L12 _public enumerator_ `Log`
- L13 _public enumerator_ `Exp`

#### class `FRamper`  
`class FRamper`  
_L16-336_
- L20 _public typedef_ `typedef void (*FCallback)(void*);`
- L21 _public typedef_ `typedef float Type;`
- L23 _public function_ `FRamper(float InNumRampCallsPerSecond = 1.0f) : Current(0.0f) , NumRampCallsPerSecond(InNumRampCallsPerSecond) , Callback(nullptr)`
- L34 _public function_ `void SetRampTimeMs(float InNumRampCallsPerSecond, float InRampTimeMs, ERamperMode InMode)`
- L42 _public function_ `float GetRampTimeMs() const`
- L47 _public function_ `void SetTarget(Type InTarget, FCallback InCallback = nullptr, void* InData = nullptr)`
- L66 _public function_ `void SnapTo(Type InValue)`
- L72 _public function_ `Type GetCurrent() const`
- L73 _public function_ `Type GetTarget() const`
- L75 _public function_ `void Ramp()`
- L93 _public function_ `void SnapToTarget()`
- L120 _private function_ `void SetTargetLinear(Type InTarget, FCallback InCallback, void* InData)`
- L139 _private function_ `void LinearRamp()`
- L182 _private function_ `void SetTargetLog(Type InTarget, FCallback InCallback, void* InData)`
- L205 _private function_ `void LogRamp()`
- L248 _private function_ `void SetTargetExponential(float InTarget, FCallback InCallback = nullptr, void* InData = nullptr)`
- L275 _private function_ `void ExponentialRamp()`
- L322 _private member_ `Type Current;`
- L323 _private member_ `Type Target;`
- L324 _private member_ `ERamperMode Mode;`
- L326 _private member_ `Type Increment;`
- L327 _private member_ `Type NormalIncrement;`
- L329 _private member_ `Type Multiplier;`
- L331 _private member_ `float NumRampCallsPerSecond;`
- L332 _private member_ `volatile bool IsSettingTarget;`
- L334 _private member_ `FCallback Callback;`
- L335 _private member_ `void* Data;`

#### class `TRamper`  
`template<typename T> class TRamper`  
_L344-444_
- L349 _public function_ `TRamper(float InNumRampCallsPerSecond = 1.0f) : ProgressPct(1.0f) , NumRampCallsPerSecond(InNumRampCallsPerSecond) , IsSettingTarget(false) , Callback(nullptr)`
- L359 _public function_ `void SetRampTimeMs(float InRampTimeMs)`
- L371 _public function_ `void SetRampTimeMs(float InNumRampCallsPerSecond, float InRampTimeMs)`
- L377 _public function_ `float GetRampTimeMs() const`
- L387 _public function_ `const T& GetCurrent() const`
- L388 _public function_ `const T& GetTarget() const`
- L390 _public function_ `operator T() const`
- L392 _public function_ `bool IsAtTarget() const`
- L397 _public function_ `float GetProgressPct() const`
- L402 _public function_ `void SnapToTarget()`
- L428 _protected function_ `void InitData()`
- L430 _protected member_ `T CurrentValue;`
- L431 _protected member_ `T TargetValue;`
- L432 _protected member_ `T Increment;`
- L434 _protected member_ `float NormalIncrement;` — the increment to use if the difference between the target and current value is 1.0f
- L436 _protected member_ `float ProgressPct;` — in range [0.0f, 1.0f]
- L438 _protected member_ `float NumRampCallsPerSecond;`
- L439 _protected member_ `volatile bool IsSettingTarget;`
- L442 _protected member_ `FRamper::FCallback Callback;` — wonder if I should use an event here instead :thinking:
- L443 _protected member_ `void* Data;`
- L447 _function_ `template<> FORCEINLINE void TRamper<float>::InitData()`
- L449 _function_ `template<> FORCEINLINE void TRamper<int32>::InitData()`
- L451 _function_ `template<> FORCEINLINE void TRamper<int64>::InitData()`
- L453 _function_ `template<> FORCEINLINE void TRamper<uint32>::InitData()`
- L455 _function_ `template<> FORCEINLINE void TRamper<uint16>::InitData()`

#### class `TLinearRamper`  
`template<typename T> class TLinearRamper : public TRamper<T>`  
_L458-517_
- inherits: `TRamper<T>`
- L462 _public function_ `explicit TLinearRamper(float InNumRampCallsPerSecond = 1.0f) : TRamper<T>(InNumRampCallsPerSecond)`
- L466 _public function_ `void SetTarget(T InTarget, FRamper::FCallback InCallback = nullptr, void* InData = nullptr)`
- L488 _public function_ `bool Ramp()`
- L506 _public function_ `void SnapTo(const T& InValue)`
- L512 _public function_ `TLinearRamper<T>& operator=(const T InValue)`

#### class `TLinearCircularRamper`  
`template<typename T> class TLinearCircularRamper : public TRamper<T>`  
_L520-654_
- inherits: `TRamper<T>`
- L523 _public function_ `TLinearCircularRamper(T InMin, T InMax, float InNumRampCallsPerSecond = 1.0f) : TRamper<T>(InNumRampCallsPerSecond)`
- L530 _public function_ `void SetMinMax(T InMin, T InMax, bool bCircular)`
- L537 _public function_ `void SetTarget(T InTarget, bool bCircular, FRamper::FCallback InCallback = nullptr, void* InData = nullptr)`
- L598 _public function_ `bool Ramp()`
- L626 _public function_ `void SnapTo(T InValue, bool Circular)`
- L648 _public function_ `T GetMin() const`
- L649 _public function_ `T GetMax() const`
- L652 _private member_ `T Min;`
- L653 _private member_ `T Max;`

#### class `TTimeBasedRamper`  
`template <typename T> class TTimeBasedRamper`  
_L657-788_
- L661 _public function_ `TTimeBasedRamper() : Callback(nullptr)`
- L669 _public function_ `void SetRampTimeMs(float InRampTimeMs)`
- L679 _public function_ `float GetRampTimeMs() const`
- L684 _public function_ `void SetTarget(T InTarget, FRamper::FCallback InCallback = nullptr, void* InData = nullptr)`
- L689 _public function_ `void SnapTo(T InValue)`
- L695 _public function_ `const T& GetCurrent() const`
- L696 _public function_ `const T& GetTarget() const`
- L698 _public function_ `bool Ramp(float InMs)`
- L703 _public function_ `bool IsAtTarget() const`
- L708 _public function_ `float GetProgressPct() const`
- L713 _public function_ `void SnapToTarget()`
- L737 _private function_ `void SetTargetLinear(T InTarget, FRamper::FCallback InCallback, void* InData)`
- L753 _private function_ `bool LinearRamp(float InMs)`
- L777 _private member_ `T StartValue;`
- L778 _private member_ `T CurrentValue;`
- L779 _private member_ `T TargetValue;`
- L780 _private member_ `float DurationMs;`
- L781 _private member_ `float ProgressPct;`
- L782 _private member_ `float PassedMs;`
- L784 _private member_ `volatile bool IsSettingTarget;`
- L786 _private member_ `FRamper::FCallback Callback;`
- L787 _private member_ `void* Data;`

#### Free symbols / members of external scopes

- L338 _namespace_ `namespace Harmonix`
- L338 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L338 _namespace_ `namespace Ramper` (scope `Harmonix::Dsp`)
- L338 _namespace_ `namespace Tests` (scope `Harmonix::Dsp::Ramper`)

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Streaming/StandardStream.h` (Public)


#### struct `FStreamingChannelParams`  
`struct FStreamingChannelParams`  
_L12-46_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `int32 StreamIndex;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L21 _public member_ `float Gain;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L24 _public member_ `FPannerDetails Pan;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L27 _public function_ `FStreamingChannelParams() : StreamIndex(-1) , Gain(1.0f)`
- L31 _public function_ `FStreamingChannelParams(int32 InIndex, float InGain, float InPan) : StreamIndex(InIndex) , Gain(InGain) , Pan(InPan)`
- L36 _public function_ `FStreamingChannelParams(int32 InIndex, float InGain, ESpeakerChannelAssignment ChannelAssignment) : StreamIndex(InIndex) , Gain(InGain) , Pan(ChannelAssignment)`
- L41 _public function_ `FStreamingChannelParams(int32 InIndex, float InGain, float InPan, float InEdgeProximity) : StreamIndex(InIndex) , Gain(InGain) , Pan(InPan, InEdgeProximity)`

#### struct `FStreamingTrackParams`  
`struct FStreamingTrackParams`  
_L49-83_
- reflection: `USTRUCT()`
- L53 _public member_ `float Pan;`
- L54 _public member_ `float SlipSpeed;`
- L55 _public member_ `bool Slipped;`
- L56 _public member_ `float CurrentSlipOffsetMs;`
- L57 _public member_ `float PushSlipOffset;`
- L58 _public member_ `int32 ChannelReadOffset;`
- L60 _public member_ `float Gain;`
- L61 _public member_ `float GainRampMs;`
- L62 _public member_ `bool Muted;`
- L64 _public function_ `FStreamingTrackParams()`
- L66 _public member_ `TArray<FStreamingChannelParams> ChannelParams;`
- L69 _public function_ `void Reset()`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/Streaming/TrackChannelInfo.h` (Public)


#### struct `FStreamingChannelParamsArray`  
`struct FStreamingChannelParamsArray`  
_L12-29_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `TArray<FStreamingChannelParams> ChannelParams;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L21 _public function_ `FStreamingChannelParamsArray()`
- L22 _public function_ `FStreamingChannelParamsArray(const TArray<FStreamingChannelParams>& InChannelParams) : ChannelParams(InChannelParams)`
- L27 _public function_ `FStreamingChannelParams& operator[](int32 Index)`
- L28 _public function_ `const FStreamingChannelParams& operator[](int32 Index) const`

#### struct `FTrackChannelInfo`  
`struct FTrackChannelInfo`  
_L32-82_
- reflection: `USTRUCT(BlueprintType)`
- L39 _public member_ `int32 RealTrackIndex = -1;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = -1, ClampMin = -1))`
- L42 _public member_ `FName Name;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L45 _public member_ `FName Routing;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L48 _public member_ `TArray<FStreamingChannelParams> Channels;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L51 _public member_ `TMap<FName, FStreamingChannelParamsArray> PresetChannels;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L53 _public prototype_ `FTrackChannelInfo();`
- L54 _public prototype_ `FTrackChannelInfo(int32 InRealIndex);`
- L55 _public prototype_ `FTrackChannelInfo(FTrackChannelInfo&& Other);`
- L56 _public prototype_ `FTrackChannelInfo(const FTrackChannelInfo& Other);`
- L58 _public function_ `FTrackChannelInfo& operator=(const FTrackChannelInfo& Other)`
- L68 _public prototype_ `int32 GetNumChannels() const;`
- L69 _public prototype_ `int32 GetStreamChannelIndex(int32 ChannelIndex) const;`
- L70 _public prototype_ `bool GetStreamIndexesPan(int32 StreamIndex, FPannerDetails& OutPan) const;`
- L71 _public prototype_ `bool GetStreamIndexesGain(int32 StreamIndex, float& OutGain) const;`
- L72 _public prototype_ `bool GetStreamIndexesPresetGain(FName PresetName, int32 StreamIndex, float& OutGain, bool DefaultIfNotFound = true) const;`
- L73 _public prototype_ `bool SetStreamIndexesPan(int32 StreamIndex, float Pan);`
- L74 _public prototype_ `bool SetStreamIndexesPan(int32 StreamIndex, const FPannerDetails& InPan);`
- L75 _public prototype_ `bool SetStreamIndexesGain(int32 StreamIndex, float InGain);`
- L76 _public prototype_ `bool SetStreamIndexesPresetGain(FName presetName, int32 StreamIndex, float InGain);`
- L80 _private prototype_ `const FStreamingChannelParams* FindStreamingChannelParams(int32 StreamIndex) const;`
- L81 _private prototype_ `FStreamingChannelParams* FindStreamingChannelParams(int32 StreamIndex);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/StretcherAndPitchShifter.h` (Public)


#### struct `FTimeStretchConfig`  
`struct FTimeStretchConfig`  
_L18-38_
- reflection: `USTRUCT()`
- L25 _public member_ `bool bMaintainTime = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L28 _public member_ `FPitchShifterName PitchShifter;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L31 _public member_ `TMap<FName, FTypedParameter> PitchShifterOptions;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L34 _public member_ `bool bSyncTempo = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings")`
- L37 _public member_ `float OriginalTempo = 120.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Settings", Meta = (UIMin = 1, UIMax = 240, ClampMin = 1, ClampMax = 240))`

#### class `IStretcherAndPitchShifter`  
`class IStretcherAndPitchShifter`  
_L40-111_
- L43 _public function_ `IStretcherAndPitchShifter(FName InFactoryName) : MyFactoryName(InFactoryName)`
- L46 _public prototype_ `virtual ~IStretcherAndPitchShifter() = default;`
- L49 _public function_ `FName GetFactoryName() const`
- L51 _public function_ `virtual void UpdateOptions(const TMap<FName, FTypedParameter>& Options)`
- L53 _public prototype_ `virtual int32 GetInputFramesNeeded(int32 NumOutFramesNeeded, float PitchShift, float SpeedShift) = 0;`
- L54 _public function_ `virtual bool HandlesSpeedCorrection() const`
- L55 _public function_ `virtual void SetSampleRateAndReset(float InSampleRate)`
- L56 _public function_ `virtual int32 GetLatencySamples() const`
- L57 _public function_ `virtual bool HasCurrentSampleFrame() const`
- L58 _public function_ `virtual int32 GetCurrentSampleFrame() const`
- L61 _public function_ `void SetSampleSourceReset(const TSharedRef<const FSoundWaveData> InSoundWaveData, TSharedPtr<IAudioDataRenderer, ESPMode::ThreadSafe> InAudioRenderer, const FTimeStretchConfig* ShifterSettings)`
- L71 _public function_ `void SetSampleSourceReset(TSharedPtr<FSoundWaveProxy> InSoundWave, TSharedPtr<IAudioDataRenderer, ESPMode::ThreadSafe> InAudioRenderer, const FTimeStretchConfig* ShifterSettings)` — `UE_DEPRECATED(5.8, "Please use the TSharedRef<const FSoundWaveData> overload instead")`
- L86 _public prototype_ `virtual double Render(TAudioBuffer<float>& OutputData, double Pos, int32 MaxFrame, double ResampleInc, double PitchShift, double Speed, bool MaintainPitchWhenSpeedChanges, const FGainMatrix& Gain) = 0;`
- L88 _public prototype_ `virtual void StereoPitchShift(float InPitchShift, int32 NumSampsToProcess, float* InLeftData, float* InRightData, float* OutLeftData, float* OutRightData) = 0;`
- L90 _public prototype_ `virtual bool TakeInput(TAudioBuffer<float>& InBuffer) = 0;`
- L91 _public prototype_ `virtual bool InputSilence(int32 NumFrames) = 0;`
- L92 _public prototype_ `virtual void StereoPitchShift(float InPitchShift, int32 NumOutputFrame, float* OutLeftData, float* OutRightData) = 0;`
- L93 _public prototype_ `virtual void PitchShift(float Pitch, float Speed, TAudioBuffer<float>& OutBuffer) = 0;`
- L95 _public prototype_ `virtual size_t GetMemoryUsage() const = 0;`
- L97 _public prototype_ `virtual void Cleanup() = 0;`
- L99 _protected member_ `TSharedPtr<const FSoundWaveData> MySoundWaveData;`
- L102 _protected member_ `TSharedPtr<FSoundWaveProxy> MyAudioData;` — `UE_DEPRECATED(5.8, "Please use MySoundWaveData instead")`
- L104 _protected member_ `TSharedPtr<IAudioDataRenderer, ESPMode::ThreadSafe> MyAudioRenderer;`
- L106 _protected function_ `virtual void SetupAndResetImpl(const FTimeStretchConfig* ShifterSettings)`
- L110 _private member_ `const FName MyFactoryName;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/StretcherAndPitchShifterConfig.h` (Public)


#### class `UStretcherAndPitchShifterConfig`  
`class UStretcherAndPitchShifterConfig : public UObject`  
_L11-14_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, CollapseCategories, Config = Engine, defaultconfig)`
- inherits: `UObject`
- desc: base class for all Stretcher and Pitch Shifter config settings allows configuration to appear in the "Pitch Shifter Settings" along with any other pitch shifter settings

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/StretcherAndPitchShifterFactory.h` (Public)


#### class `IStretcherAndPitchShifterFactory`  
`class IStretcherAndPitchShifterFactory : public IModularFeature`  
_L16-146_
- inherits: `IModularFeature`
- L20 _protected prototype_ `IStretcherAndPitchShifterFactory();`
- L24 _public prototype_ `virtual ~IStretcherAndPitchShifterFactory();`
- L30 _public prototype_ `virtual const TArray<FName>& GetFactoryNames() const = 0;` — Gets the name of this factory type. This will uniquely identity itself, so it can be found by the FindFactory call below @return Name of factory
- L36 _public function_ `virtual void SetFormantVolumeCorrection(float DBPerHalfStepUp, float DBPerHalfStepDown, float DBMaxUp, float DBMaxDown)` — Update the pitch shifters formant and volume correction settings for this factory TODO: Need to rethink how we expose pitch shifter settings
- L42 _public prototype_ `virtual TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe> GetFreePitchShifter(const FTimeStretchConfig& InConfig) = 0;` — The factory has the ability to pool pitch shifters @return Instance of an available pitch shifter
- L48 _public prototype_ `virtual void ReleasePitchShifter(TSharedPtr<IStretcherAndPitchShifter, ESPMode::ThreadSafe>) = 0;` — The factory has the ability to pool pitch shifters. Make sure to call this method with a pitch shifter you retrieved from GetFreePitchShifter
- L54 _public prototype_ `virtual bool HasFreePitchShifters(const FTimeStretchConfig& InConfig) const = 0;` — The factory has the ability to pool pitch shifters. This let's you know if GetFreePitchShifter will return a valid pitch shifter
- L59 _public prototype_ `virtual size_t GetMemoryUsedByPool() const = 0;` — Should return number of bytes used by all of the shifters in the pool.
- L67 _protected prototype_ `virtual void OnClientAdded(IFeatureClient* Client, float SampleRate) = 0;` — Override this method to do custom setup when a client is added Clients are added statically and managed by the IStretcherAndPitchShifterFactory
- L73 _protected prototype_ `virtual void OnClientRemoved(IFeatureClient* Client) = 0;` — Override this method to do custom teardown when a client is removed Clients are added statically and managed by the IStretcherAndPitchShifterFactory
- L81 _public prototype_ `static FName GetModularFeatureName();` — Get the name of all StretcherAndPitchShifter factories in the Modular Features registry. @return "StretcherAndPitchShifter Factory"
- L89 _public prototype_ `static void AddClient(IFeatureClient* Client, float SampleRate);` — Statically adds a client to the factory module (if it hasn't already beed added) lets each instance of the factory module know about the client allowing them to do any necessary setup
- L97 _public prototype_ `static void RemoveClient(IFeatureClient* Client);` — Statically removes a client from the factory module (if it hasn't already been removed) lets each instance know about the removed client allowing them to do any shut down if necessary
- L102 _public prototype_ `static bool HasClient(IFeatureClient* Client);` — @return whether the in "Client" has been added as a client to this factory module
- L107 _public prototype_ `static int32 GetNumClients();` — @return the number of unique clients added to the factory module
- L113 _public prototype_ `static TArray<IStretcherAndPitchShifterFactory*> GetAllRegisteredFactories();` — Gets all registered factory instances. @return Array of all factories.
- L120 _public prototype_ `static TArray<FName> GetAllRegisteredFactoryNames();` — Gets all registered factory names @return Array of all factory names
- L126 _public prototype_ `static IStretcherAndPitchShifterFactory* FindBestFactory(const FTimeStretchConfig& InConfig);` — Finds a factory with available pitch shifters @return IStretcherAndPitchShifterFactory* instance
- L133 _public prototype_ `static IStretcherAndPitchShifterFactory* FindFactory(const FName InFactoryName);` — Returns the instance of the factory with the registered name null if a factory has not been registerred with the given name @return IStretcherAndPitchShifterFactory* instance
- L137 _private prototype_ `static void ResetMemoryUsageBytes(uint64 MemoryUsageBytes);`
- L139 _private member_ `static FCriticalSection ClientLock;`
- L141 _private member_ `static TArray<IFeatureClient*> Clients;`
- L143 _private member_ `static size_t TotalMemoryUsed;`
- L145 _private member_ `static FAudioStreamCacheMemoryHandle MemoryHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXDSP_API`
- L13 _typedef_ `using IFeatureClient = void;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/StretcherAndPitchShifterFactoryConfig.h` (Public)


#### struct `FPitchShifterNameRedirect`  
`struct FPitchShifterNameRedirect`  
_L13-29_
- reflection: `USTRUCT()`
- L17 _public function_ `FPitchShifterNameRedirect()`
- L20 _public function_ `FPitchShifterNameRedirect(FName OldName, FName NewName) : OldName(OldName), NewName(NewName)`
- L25 _public member_ `FName OldName;` — `UPROPERTY(EditDefaultsOnly, Category = "Factory")`
- L28 _public member_ `FName NewName;` — `UPROPERTY(EditDefaultsOnly, Category = "Factory")`

#### class `UStretcherAndPitchShifterFactoryConfig`  
`class UStretcherAndPitchShifterFactoryConfig : public UHarmonixDeveloperSettings`  
_L32-66_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, meta = (DisplayName = "Pitch Shifter Settings"))`
- inherits: `UHarmonixDeveloperSettings`
- L37 _public prototype_ `UStretcherAndPitchShifterFactoryConfig();`
- L40 _public member_ `TArray<FName> FactoryPriority;` — `UPROPERTY(config, EditDefaultsOnly, Category = "Factory")`
- L43 _public member_ `FPitchShifterName DefaultFactory;` — `UPROPERTY(config, EditDefaultsOnly, Category = "Factory")`
- L45 _public prototype_ `void AddFactoryNameRedirect(FName OldName, FName NewName);`
- L47 _public prototype_ `const FPitchShifterNameRedirect* FindFactoryNameRedirect(FName OldName) const;`
- L53 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L57 _public prototype_ `virtual void PostInitProperties() override;`
- L61 _private prototype_ `void PruneDuplicatesAndAddMissingNames(TArray<FName>& InOutNames);`
- L65 _private member_ `TArray<FPitchShifterNameRedirect> FactoryNameRedirects;` — `UPROPERTY(config, EditDefaultsOnly, Category = "Factory", Meta=(EditCondition="false"))` — visible in editor, but not editable

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXDSP_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/StridePointer.h` (Public)


#### class `TFixedStridePtr`  
`template<typename DataType, int32 Stride> class TFixedStridePtr`  
_L8-117_
- L11 _public function_ `TFixedStridePtr() : MyPointer(nullptr)`
- L12 _public function_ `TFixedStridePtr(const TFixedStridePtr& Other) : MyPointer(Other.MyPointer)`
- L16 _public function_ `TFixedStridePtr& operator =(DataType* InPtr)`
- L22 _public function_ `TFixedStridePtr& operator =(const TFixedStridePtr& Other)`
- L28 _public function_ `operator DataType* ()`
- L33 _public function_ `DataType* operator +(int32 Offset)`
- L38 _public function_ `DataType* operator -(int32 Offset)`
- L43 _public function_ `TFixedStridePtr& operator +=(int32 Offset)`
- L49 _public function_ `TFixedStridePtr& operator -=(int32 Offset)`
- L56 _public function_ `TFixedStridePtr& operator ++()` — prefix...
- L63 _public function_ `DataType* operator ++(int32)` — postfix...
- L71 _public function_ `TFixedStridePtr& operator --()` — prefix...
- L78 _public function_ `DataType* operator --(int32)` — postfix...
- L85 _public function_ `bool operator ==(const TFixedStridePtr& Other)`
- L90 _public function_ `bool operator ==(const DataType* Other)`
- L95 _public function_ `bool operator !=(const TFixedStridePtr& Other)`
- L100 _public function_ `bool operator !=(const DataType* Other)`
- L105 _public function_ `DataType& operator [](int32 Other)`
- L110 _public function_ `DataType& operator *()`
- L116 _private member_ `DataType* MyPointer;`

#### class `TDynamicStridePtr`  
`template <typename DataType> class TDynamicStridePtr`  
_L124-261_
- L127 _public function_ `TDynamicStridePtr() : Stride(0) , MyPointer(nullptr)`
- L132 _public function_ `TDynamicStridePtr(DataType* InPointer, int32 InStride) : Stride(InStride) , MyPointer(InPointer)`
- L137 _public function_ `TDynamicStridePtr(int32 InStride) : Stride(InStride) , MyPointer(nullptr)`
- L142 _public function_ `TDynamicStridePtr(const TDynamicStridePtr& Other) : Stride(Other.Stride) , MyPointer(Other.MyPointer)`
- L147 _public function_ `void Init(const TDynamicStridePtr& Other)`
- L153 _public function_ `TDynamicStridePtr& operator =(DataType* InPtr)`
- L159 _public function_ `TDynamicStridePtr& operator =(const TDynamicStridePtr& Other)`
- L166 _public function_ `operator DataType* ()`
- L171 _public function_ `DataType* operator +(int32 Offset)`
- L176 _public function_ `DataType* operator -(int32 Offset)`
- L181 _public function_ `TDynamicStridePtr& operator +=(int32 Offset)`
- L187 _public function_ `TDynamicStridePtr& operator -=(int32 Offset)`
- L194 _public function_ `TDynamicStridePtr& operator ++()` — prefix...
- L201 _public function_ `DataType* operator ++(int32)` — postfix...
- L209 _public function_ `TDynamicStridePtr& operator --()` — prefix...
- L216 _public function_ `DataType* operator --(int32)` — postfix...
- L223 _public function_ `bool operator ==(const TDynamicStridePtr& Other) const`
- L228 _public function_ `bool operator ==(const DataType* Other) const`
- L233 _public function_ `bool operator !=(const TDynamicStridePtr& Other) const`
- L238 _public function_ `bool operator !=(const DataType* Other) const`
- L243 _public function_ `const DataType& operator [](int32 Offset) const`
- L248 _public function_ `DataType& operator [](int32 Offset)`
- L253 _public function_ `DataType& operator *()`
- L259 _private member_ `int32 Stride;`
- L260 _private member_ `DataType* MyPointer;`

#### Free symbols / members of external scopes

- L119 _typedef_ `typedef TFixedStridePtr<float, 2> FInterleavedStereoFloatChannelPtr;`
- L120 _typedef_ `typedef TFixedStridePtr<float, 6> FInterleaved51FloatChannelPtr;`
- L121 _typedef_ `typedef TFixedStridePtr<float, 8> FInterleaved71FloatChannelPtr;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/TimeSyncOption.h` (Public)


#### enum `ETimeSyncOption`  
`enum class ETimeSyncOption : uint8`  
_L8-17_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `None = 0` — Time setting will always be as authored
- L13 _public enumerator_ `TempoSync UMETA(Json="TempoSync")` — Time setting is interpreted as a multiple of quarter note(s) and kept in sync with the current tempo.
- L15 _public enumerator_ `SpeedScale UMETA(Json="SpeedScale")` — Time setting is multiplied by the current music playback speed.
- L16 _public enumerator_ `Num UMETA(Hidden)`

### `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDspModule.h` (Public)


#### class `FHarmonixDspModule`  
`class FHarmonixDspModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule();`
- L11 _public prototype_ `virtual void ShutdownModule();`
