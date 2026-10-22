# Plugins / SpeechAnimationSolver

- module root: `Plugins/Animation/AudioDrivenAnimation/StreamingADA/Source/SpeechAnimationSolver`
- headers: 4; symbols: 88
- symbol kinds: class=3, enum=1, enumerator=13, macro=3, member=41, namespace=4, prototype=21, struct=2
- PrivateDependencyModuleNames: AudioPlatformConfiguration, Core, CoreUObject, NNE
- PublicDependencyModuleNames: 

### `Plugins/Animation/AudioDrivenAnimation/StreamingADA/Source/SpeechAnimationSolver/Public/ISpeechAnimationSolver.h` (Public)


#### class `ISpeechAnimationSolver`  
`class ISpeechAnimationSolver`  
_L18-40_
- L21 _public prototype_ `virtual ~ISpeechAnimationSolver() = default;`
- L24 _public prototype_ `virtual bool Initialize() = 0;` — Initialize the solver
- L27 _public prototype_ `virtual void ClearCache() = 0;` — Clear the solver data cache to avoid having to restart it between multiple uses
- L30 _public prototype_ `virtual bool SolveAudioFrame(const FSpeechAnimationAudioFrame& InAudioFrame, FSpeechAnimationFrameData& OutFrameData) = 0;` — Solve the given audio frame to control rig channels and/or regular curves
- L33 _public prototype_ `virtual int32 GetNumCurves() = 0;` — @returns the number of control rig curves to expect
- L36 _public prototype_ `virtual const TArray<FName>& GetCurveNames() const = 0;` — @returns the name of the control rig curve channels to expect
- L39 _public prototype_ `static FString GetLatestModelAssetPath();` — @returns the asset path of the most up to date model

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SPEECHANIMATIONSOLVER_API`

### `Plugins/Animation/AudioDrivenAnimation/StreamingADA/Source/SpeechAnimationSolver/Public/SpeechAnimationSolverTypes.h` (Public)


#### enum `EAudioDrivenAnimationMood`  
`enum class EAudioDrivenAnimationMood : uint8`  
_L13-29_
- reflection: `UENUM(BlueprintType)`
- desc: The Speech Animation mood options.
- L15 _public enumerator_ `AutoDetect = 255 UMETA(DisplayName = "Auto Detect")`
- L17 _public enumerator_ `Neutral = 0 UMETA(DisplayName = "Neutral")`
- L18 _public enumerator_ `Happiness = 1 UMETA(DisplayName = "Happy")`
- L19 _public enumerator_ `Sadness = 2 UMETA(DisplayName = "Sad")`
- L20 _public enumerator_ `Disgust = 3 UMETA(DisplayName = "Disgust")`
- L21 _public enumerator_ `Anger = 4 UMETA(DisplayName = "Anger")`
- L22 _public enumerator_ `Surprise = 5 UMETA(DisplayName = "Surprise")`
- L23 _public enumerator_ `Fear = 6 UMETA(DisplayName = "Fear")`
- L24 _public enumerator_ `Confidence = 10 UMETA(DisplayName = "Confident")`
- L25 _public enumerator_ `Excitement = 14 UMETA(DisplayName = "Excited")`
- L26 _public enumerator_ `Boredom = 15 UMETA(DisplayName = "Bored")`
- L27 _public enumerator_ `Playfulness = 17 UMETA(DisplayName = "Playful")`
- L28 _public enumerator_ `Confusion = 19 UMETA(DisplayName = "Confused")`

#### struct `FSpeechAnimationAudioFrame`  
`struct FSpeechAnimationAudioFrame`  
_L35-78_
- reflection: `USTRUCT(BlueprintType)`
- desc: The Speech Animation solver's input frame data.
- L41 _public member_ `TArray<float> AudioSamples;` — `UPROPERTY(BlueprintReadWrite, Category = "Speech Animation")` — The audio sample to solve
- L45 _public member_ `int32 SamplesCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The number of audio samples for this frame of audio
- L49 _public member_ `int32 SampleRate = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The sample rate of this frame of audio
- L53 _public member_ `int32 NumChannels = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The number of channels for this frame of audio
- L57 _public member_ `bool bContiguous = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — Whether this audio sample is contiguous with the last audio
- L61 _public member_ `EAudioDrivenAnimationMood Mood = EAudioDrivenAnimationMood::Neutral;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The mood for this audio
- L65 _public member_ `float MoodIntensity = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The mood intensity for this audio
- L69 _public member_ `int32 Lookahead = 80;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The lookahead for this audio
- L73 _public member_ `double ArrivalTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The timecode associated to this audio sample
- L77 _public member_ `FGuid FrameId;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speech Animation")` — The id for this audio frame

#### struct `FSpeechAnimationFrameData`  
`struct FSpeechAnimationFrameData`  
_L84-103_
- reflection: `USTRUCT(BlueprintType)`
- desc: The Speech Animation solver's output frame data.
- L90 _public member_ `TArray<FName> CurveNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The name of the curves that were solved onto
- L94 _public member_ `TArray<float> CurveValues;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The values of the curves that were solved
- L98 _public member_ `FSpeechAnimationAudioFrame AudioFrame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The audio frame that was solved
- L102 _public member_ `double SolvedTime = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speech Animation")` — The time at which the frame was actually solved

### `Plugins/Animation/AudioDrivenAnimation/StreamingADA/Source/SpeechAnimationSolver/Public/SpeechAnimationSolverV3.h` (Public)


#### class `FSpeechAnimationSolverV3`  
`class FSpeechAnimationSolverV3 : public ISpeechAnimationSolver`  
_L18-52_
- inherits: `ISpeechAnimationSolver`
- L22 _public prototype_ `FSpeechAnimationSolverV3(const TObjectPtr<class UNNEModelData> InModelData, const FString& InNNEBackend);`
- L25 _public prototype_ `bool Initialize() override;` — ISpeechAnimationSolver
- L26 _public prototype_ `void ClearCache() override;`
- L27 _public prototype_ `bool SolveAudioFrame(const FSpeechAnimationAudioFrame& InAudioFrame, FSpeechAnimationFrameData& OutFrameData) override;`
- L28 _public prototype_ `int32 GetNumCurves() override;`
- L29 _public prototype_ `const TArray<FName>& GetCurveNames() const override;`
- L34 _private member_ `TObjectPtr<class UNNEModelData> ModelData;`
- L35 _private member_ `FString NNEBackend;`
- L37 _private member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> Model = nullptr;`
- L39 _private member_ `TArray<float, TAlignedHeapAllocator<64>> AudioBuffer;` — IREE case requires 64 byte alignment
- L40 _private member_ `TArray<float, TAlignedHeapAllocator<64>> CurveValues;`
- L41 _private member_ `TArray<int64, TAlignedHeapAllocator<64>> Step;`
- L43 _private member_ `TArray<float> InputBuffer;`
- L44 _private member_ `TArray<float> FrameBuffer;`
- L46 _private member_ `FSpeechAnimationFrameData AnimOut;`
- L48 _private prototype_ `bool ReformatAudio(const FSpeechAnimationAudioFrame& InAudioFrame, const FSpeechAnimationAudioFrame*& OutAudioFramePtr);`
- L49 _private member_ `FSpeechAnimationAudioFrame AudioFrameReformatted;`
- L50 _private member_ `Audio::FResampler Resampler;`
- L51 _private member_ `bool bResamplerInitialized = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SPEECHANIMATIONSOLVER_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNE` (scope `UE`)

### `Plugins/Animation/AudioDrivenAnimation/StreamingADA/Source/SpeechAnimationSolver/Public/SpeechAnimationSolverV4.h` (Public)


#### class `FSpeechAnimationSolverV4`  
`class FSpeechAnimationSolverV4 : public ISpeechAnimationSolver`  
_L18-55_
- inherits: `ISpeechAnimationSolver`
- L22 _public prototype_ `FSpeechAnimationSolverV4(const TObjectPtr<class UNNEModelData> InModelData, const FString& InNNEBackend);`
- L25 _public prototype_ `bool Initialize() override;` — ISpeechAnimationSolver
- L26 _public prototype_ `void ClearCache() override;`
- L27 _public prototype_ `bool SolveAudioFrame(const FSpeechAnimationAudioFrame& InAudioFrame, FSpeechAnimationFrameData& OutFrameData) override;`
- L28 _public prototype_ `int32 GetNumCurves() override;`
- L29 _public prototype_ `const TArray<FName>& GetCurveNames() const override;`
- L34 _private member_ `TObjectPtr<class UNNEModelData> ModelData;`
- L35 _private member_ `FString NNEBackend;`
- L37 _private member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> Model = nullptr;`
- L39 _private member_ `TArray<float, TAlignedHeapAllocator<64>> AudioBuffer;` — IREE case requires 64 byte alignment
- L40 _private member_ `TArray<float, TAlignedHeapAllocator<64>> CurveValues;`
- L41 _private member_ `TArray<float, TAlignedHeapAllocator<64>> MoodState;`
- L42 _private member_ `TArray<int64, TAlignedHeapAllocator<64>> BlinkBound;`
- L43 _private member_ `TArray<int64, TAlignedHeapAllocator<64>> BlinkSel;`
- L44 _private member_ `TArray<int64, TAlignedHeapAllocator<64>> Step;`
- L46 _private member_ `TArray<float> InputBuffer;`
- L47 _private member_ `TArray<float> FrameBuffer;`
- L49 _private member_ `FSpeechAnimationFrameData AnimOut;`
- L51 _private prototype_ `bool ReformatAudio(const FSpeechAnimationAudioFrame& InAudioFrame, const FSpeechAnimationAudioFrame*& OutAudioFramePtr);`
- L52 _private member_ `FSpeechAnimationAudioFrame AudioFrameReformatted;`
- L53 _private member_ `Audio::FResampler Resampler;`
- L54 _private member_ `bool bResamplerInitialized = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SPEECHANIMATIONSOLVER_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNE` (scope `UE`)
