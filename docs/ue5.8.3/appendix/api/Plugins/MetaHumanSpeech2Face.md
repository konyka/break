# Plugins / MetaHumanSpeech2Face

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSpeech2Face`
- headers: 6; symbols: 86
- symbol kinds: class=4, delegate=1, enum=1, enumerator=2, function=2, macro=1, member=27, namespace=7, prototype=30, struct=5, typedef=2, variable=4
- PrivateDependencyModuleNames: AssetRegistry, AudioPlatformConfiguration, ContentBrowser, CoreUObject, Engine, Json, JsonUtilities, LevelSequence, MetaHumanCore, MetaHumanCoreTech, MovieScene, MovieSceneTracks, NNE, Projects, SignalProcessing, Slate, SlateCore, SpeechAnimationSolver, ToolMenus, UnrealEd
- PublicDependencyModuleNames: ControlRig, Core

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSpeech2Face/Private/AudioDrivenAnimationCustomizations.h` (Private)


#### class `UE::MetaHuman::Private::FAudioSolveOverridesPropertyTypeCustomization`  
`class FAudioSolveOverridesPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L15-22_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MetaHuman` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSpeech2Face/Private/DataDefs.h` (Private)


#### struct `RigControlLimits`  
`struct RigControlLimits`  
_L9-13_
- L11 _public member_ `float Min;`
- L12 _public member_ `float Max;`

#### struct `RigControlInfo`  
`struct RigControlInfo`  
_L15-20_
- L17 _public member_ `FString Name;`
- L18 _public member_ `RigControlLimits ModelLimits;`
- L19 _public member_ `RigControlLimits RigLimits;`

#### Free symbols / members of external scopes

- L22 _variable_ `static inline const TArray<FString> BlinkRigControlNames = { "CTRL_L_eye_blink.ty", "CTRL_R_eye_blink.ty" };`
- L27 _variable_ `static inline const TArray<FString> RigControlNames = { "CTRL_L_brow_down.ty", "CTRL_R_brow_down.ty", "CTRL_L_brow_lateral.ty", "CTRL_R_brow_lateral.ty", "CTRL_L_brow_raiseIn.ty", "CTRL_R_brow_raiseIn.ty", "CTRL_L_brow_raiseOut.ty", "CTRL_R_brow_raiseOut.ty", "CTRL_L_eye_blink.ty", "CTRL_R_eye_blink.ty", "CTRL_L_eye_squintInner.ty", "CTRL_R_eye_squintInner.ty", "CTRL_L_eye_cheekRaise.ty", "CTRL_R_eye_cheekRaise.ty", "CTRL_L_nose.ty", "CTRL_R_nose.ty", "CTRL_L_nose.tx", "CTRL_R_nose.tx", "CTRL_L_nose_nasolabialDeepen.ty", "CTRL_R_nose_nasolabialDeepen.ty", "CTRL_C_mouth.tx", "CTRL_L_mouth_upperLipRaise.ty", "CTRL_R_mouth_upperLipRaise.ty", "CTRL_L_mouth_lowerLipDepress.ty", "CTRL_R_mouth_lowerLipDepress.ty", "CTRL_L_mouth_cornerPull.ty", "CTRL_R_mouth_cornerPull.ty", "CTRL_L_mouth_stretch.ty", "CTRL_R_mouth_stretch.ty", "CTRL_L_mouth_dimple.ty", "CTRL_R_mouth_dimple.ty", "CTRL_L_mouth_cornerDepress.ty", "CTRL_R_mouth_cornerDepress.ty", "CTRL_L_mouth_purseU.ty", "CTRL_R_mouth_purseU.ty", "CTRL_L_mouth_purseD.ty", "CTRL_R_mouth_purseD.ty", "CTRL_L_mouth_towardsU.ty", "CTRL_R_mouth_towardsU.ty",`
- L111 _namespace_ `namespace UE`
- L111 _namespace_ `namespace MetaHuman` (scope `UE`)
- L113 _variable_ `static const TMap<FString, FString> HeadControlsGuiToRawLookupTable = []() { TMap<FString, FString> Table; Table.Add(TEXT("HeadTranslationX"), TEXT("mha_head_ik_ctrl.tx")); Table.Add(TEXT("HeadTranslationY"), TEXT("mha_head_ik_ctrl.ty")); Table.Add(TEXT("HeadTranslationZ"), TEXT("mha_head_ik_ctrl.tz")); Table.Add(TEXT("HeadRoll"), TEXT("mha_head_ik_ctrl.rx")); Table.Add(TEXT("HeadPitch"), TEXT("mha_head_ik_ctrl.ry")); Table.Add(TEXT("HeadYaw"), TEXT("mha_head_ik_ctrl.rz")); return Table; }();` (scope `UE::MetaHuman`)
- L114 _function_ `` (scope `UE::MetaHuman`)
- L128 _variable_ `static const TSet<FString> MouthOnlyRawControls = { TEXT("CTRL_expressions_jawChinCompressL"), TEXT("CTRL_expressions_jawChinCompressR"), TEXT("CTRL_expressions_jawChinRaiseDL"), TEXT("CTRL_expressions_jawChinRaiseDR"), TEXT("CTRL_expressions_jawChinRaiseUL"), TEXT("CTRL_expressions_jawChinRaiseUR"), TEXT("CTRL_expressions_jawClenchL"), TEXT("CTRL_expressions_jawClenchR"), TEXT("CTRL_expressions_jawFwd"), TEXT("CTRL_expressions_jawLeft"), TEXT("CTRL_expressions_jawOpen"), TEXT("CTRL_expressions_jawOpenExtreme"), TEXT("CTRL_expressions_mouthCheekBlowL"), TEXT("CTRL_expressions_mouthCheekBlowR"), TEXT("CTRL_expressions_mouthCornerDepressL"), TEXT("CTRL_expressions_mouthCornerDepressR"), TEXT("CTRL_expressions_mouthCornerPullL"), TEXT("CTRL_expressions_mouthCornerPullR"), TEXT("CTRL_expressions_mouthCornerSharpenDL"), TEXT("CTRL_expressions_mouthCornerSharpenDR"), TEXT("CTRL_expressions_mouthCornerSharpenUL"), TEXT("CTRL_expressions_mouthCornerSharpenUR"), TEXT("CTRL_expressions_mouthCornerUpL"), TEXT("CTRL_expressions_mouthCornerUpR"), TEXT("CTRL_expressions_mouthCornerWideL"), TEXT("CTRL_expressions_mouthCornerWideR"), TEXT("CTRL_expressions_mouthDimpleL"), TEXT("CTRL_expressions_mouthDimpleR"), TEXT("CTRL_expressions_mouthFunnelDL"), TEXT("CTRL_expressions_mouthFunnelDR"), TEXT("CTRL_expressions_mouthFunnelUL"), TEXT("CTRL_expressions_mouthFunnelUR"), TEXT("CTRL_expressions_mouthLeft"), TEXT("CTRL_expressions_mouthLipsBlowL"), TEXT("CTRL_expressions_mouthLipsBlowR"), TEXT("CT ...` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSpeech2Face/Private/MetaHumanSpeech2FaceModule.h` (Private)


#### class `FMetaHumanSpeech2FaceModule`  
`class FMetaHumanSpeech2FaceModule : public IModuleInterface`  
_L7-18_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _private member_ `FName AudioDrivenAnimationSolveOverridesName;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSpeech2Face/Private/Speech2FaceInternal.h` (Private)


#### class `FSpeech2FaceInternal`  
`class FSpeech2FaceInternal final`  
_L15-81_
- L17 _public prototype_ `static TUniquePtr<FSpeech2FaceInternal> Create(const FAudioDrivenAnimationModels& InModels);`
- L19 _public prototype_ `bool GenerateFaceAnimation(const FSpeech2Face::FAudioParams& InAudioParams, float InOutputAnimationFps, bool bInGenerateBlinks, TFunction<bool()> InShouldCancelCallback, TArray<FSpeech2Face::FAnimationFrame>& OutAnimation, TArray<FSpeech2Face::FAnimationFrame>& OutHeadAnimation) const;`
- L26 _public prototype_ `void SetMood(const EAudioDrivenAnimationMood& InMood);`
- L27 _public prototype_ `void SetMoodIntensity(float InMoodIntensity);`
- L31 _public member_ `static constexpr float RigLogicPredictorOutputFps = 50.0f;` — Predictor generates animation at 50fps
- L34 _private typedef_ `using FloatSamples = Audio::VectorOps::FAlignedFloatBuffer;`
- L36 _private prototype_ `FSpeech2FaceInternal();`
- L37 _private prototype_ `bool Init(const FAudioDrivenAnimationModels& InModels);`
- L38 _private prototype_ `TSharedPtr<UE::NNE::IModelInstanceCPU> TryLoadModelData(const FSoftObjectPath& InModelAssetPath);`
- L40 _private prototype_ `static bool GetFloatSamples(const TWeakObjectPtr<const USoundWave>& SoundWave, const TArray<uint8>& PcmData, uint32 SampleRate, bool bDownmixChannels, uint32 ChannelToUse, float SecondsToSkip, FloatSamples& OutSamples);`
- L41 _private prototype_ `static bool ResampleAudio(FloatSamples InSamples, int32 InSampleRate, int32 InResampleRate, FloatSamples& OutResampledSamples);`
- L42 _private prototype_ `static bool ExtractAudioFeatures(const FloatSamples& Samples, const TSharedPtr<UE::NNE::IModelInstanceCPU>& AudioExtractor, TArray<float>& OutAudioData);`
- L44 _private prototype_ `bool RunPredictor( uint32 ControlNum, uint32 BlinkControlNum, uint32 SamplesNum, const TArray<float>& AudioData, TArray<float>& OutRigLogicValues, TArray<float>& OutRigLogicBlinkValues, TArray<float>& OutRigLogicHeadValues ) const;`
- L55 _private prototype_ `static TArray<FSpeech2Face::FAnimationFrame> ResampleAnimation(TArrayView<const float> InRawAnimation, TArrayView<const FString> InRigControlNames, uint32 ControlNum, float InOutputFps);`
- L56 _private prototype_ `int32 GetModelMoodIndex() const;`
- L60 _private member_ `static constexpr uint32 AudioEncoderSampleRateHz = 16000;` — The model is expecting to process audio sampled at 16kHz
- L62 _private member_ `static constexpr float RigLogicPredictorMaxAudioSamples = AudioEncoderSampleRateHz * 30;` — The model does not allow processing of more than 30 seconds of audio
- L63 _private member_ `static constexpr float RigLogicPredictorFrameDuration = 1.f / RigLogicPredictorOutputFps;`
- L64 _private member_ `static constexpr float SamplesPerFrame = AudioEncoderSampleRateHz * RigLogicPredictorFrameDuration;`
- L66 _private member_ `TSharedPtr<UE::NNE::IModelInstanceCPU> AudioExtractor;`
- L67 _private member_ `TSharedPtr<UE::NNE::IModelInstanceCPU> RigLogicPredictor;`
- L70 _private member_ `const TArray<FString> ModelHeadControls = { TEXT("HeadTranslationY"), TEXT("HeadTranslationZ"), TEXT("HeadRoll"), TEXT("HeadPitch"), TEXT("HeadYaw"), };` — The order of these controls is specific and keyed to the model output, so this is not just a list of GUI controls for the head
- L79 _private member_ `EAudioDrivenAnimationMood DesiredMood = EAudioDrivenAnimationMood::Neutral;` — We default to safe (netural) mood values to ensure nodes which derive from FSpeechToAnimNode have sensible baseline behaviour
- L80 _private member_ `float DesiredMoodIntensity = 1.0f;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpeech2FaceSolver, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSpeech2FaceSolver, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSpeech2Face/Public/AudioDrivenAnimationConfig.h` (Public)


#### struct `FAudioDrivenAnimationModels`  
`struct FAudioDrivenAnimationModels`  
_L13-26_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public prototype_ `FAudioDrivenAnimationModels();`
- L21 _public member_ `FSoftObjectPath AudioEncoder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties, meta = (AllowedClasses = "/Script/NNE.NNEModelData"))` — The model which will be used for audio encoding
- L25 _public member_ `FSoftObjectPath AnimationDecoder;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties, meta = (AllowedClasses = "/Script/NNE.NNEModelData"))` — The model which will be used for decoding the animation

#### enum `EAudioDrivenAnimationOutputControls`  
`enum class EAudioDrivenAnimationOutputControls : uint8`  
_L29-33_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `FullFace UMETA(DisplayName = "Default (Full Face)")`
- L32 _public enumerator_ `MouthOnly`

#### struct `FAudioDrivenAnimationSolveOverrides`  
`struct FAudioDrivenAnimationSolveOverrides`  
_L36-45_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public member_ `EAudioDrivenAnimationMood Mood = EAudioDrivenAnimationMood::AutoDetect;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)`
- L44 _public member_ `float MoodIntensity = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties, Meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0, Delta = 0.01))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANSPEECH2FACE_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanSpeech2Face/Public/Speech2Face.h` (Public)


#### class `FSpeech2Face`  
`class FSpeech2Face final`  
_L20-92_
- desc: Class for generating face animation for animating RigLogic rigs using the provided speech recording.
- L36 _public typedef_ `using FAnimationFrame = TMap<FString, float>;`
- L38 _public member_ `static constexpr float AudioEncoderOutputFps = 100.0f;`
- L39 _public member_ `static constexpr float AudioEncoderWarmUpSec = 0.;`
- L41 _public prototype_ `~FSpeech2Face();`
- L49 _public prototype_ `static TUniquePtr<FSpeech2Face> Create();` — Creates a FSpeech2Face instance. The instance can be reused and can be used to generate different animation in parallel. The necessary neural network models are loaded during creation. @return Returns the instance of FSpeech2Face if successful, nullptr otherwise.
- L57 _public prototype_ `static TUniquePtr<FSpeech2Face> Create(const FAudioDrivenAnimationModels& InModels);` — Creates a FSpeech2Face instance, using the specified models. The instance can be reused and can be used to generate different animation in parallel. The necessary neural network models are loaded during creation. @return Returns the instance of FSpeech2Face if successful, nullptr otherwise.
- L62 _public prototype_ `void SetMood(const EAudioDrivenAnimationMood& InMood);` — Sets the desired mood for the resulting animation.
- L67 _public prototype_ `void SetMoodIntensity(float InMoodIntensity);` — Sets the desired mood intensity for the resulting animation.
- L81 _public prototype_ `bool GenerateFaceAnimation(const FAudioParams& InAudioParams, float InOutputAnimationFps, bool bInGenerateBlinks, TFunction<bool()> InShouldCancelCallback, TArray<FAnimationFrame>& OutAnimation, TArray<FAnimationFrame>& OutHeadAnimation);` — Generates RigLogic face animation based on the input audio. Generated animation uses the so called "face board" rig controls. Raw animation is generated at 50 FPS which is then resampled to the specified FPS using the nearest neighbour algorithm. @param InAudioParams Parameters for the audio - USoundWave asset, start offset and channel from the asset that should be used. @param InOutputAnimationFps The FPS that the output animation should have. @param bInGenerateBlinks Option to generate blink animation @param OutAnimation Generated animation. Each AnimationFrame is map that maps a rig control to it's value for that frame. @param OutHeadAnimation Generated animation for the head pose. Each AnimationFrame is map that maps a rig control to it's value for that frame. @return Returns true if the operation was successful and false otherwise.
- L90 _private prototype_ `FSpeech2Face(TUniquePtr<FSpeech2FaceInternal> InPimpl);`
- L91 _private member_ `TUniquePtr<FSpeech2FaceInternal> Pimpl;`

#### struct `FSpeech2Face::FAudioParams`  
`struct FAudioParams`  
_L23-34_
- L25 _public function_ `explicit FAudioParams(TWeakObjectPtr<const USoundWave> InSpeechRecording, float InAudioStartOffsetSec = 0, bool bInMixChannels = true, int32 InAudioChannelIndex = 0) : SpeechRecording(MoveTemp(InSpeechRecording)), AudioStartOffsetSec(InAudioStartOffsetSec), bDownmixChannels(bInMixChannels), AudioChannelIndex(InAudioChannelIndex)`
- L30 _public member_ `TWeakObjectPtr<const USoundWave> SpeechRecording;`
- L31 _public member_ `float AudioStartOffsetSec = 0;`
- L32 _public member_ `bool bDownmixChannels = true;`
- L33 _public member_ `int32 AudioChannelIndex = 0;`

#### Free symbols / members of external scopes

- L96 _namespace_ `namespace UE`
- L96 _namespace_ `namespace MetaHuman` (scope `UE`)
- L100 _prototype_ `void ReplaceHeadGuiControlsWithRaw(TMap<FString, float>& OutControlMap);` (scope `UE::MetaHuman`)
- L103 _prototype_ `TSet<FString> GetMouthOnlyRawControls();` (scope `UE::MetaHuman`)
- L106 _prototype_ `FTransform GetHeadPoseTransformFromRawControls(const TMap<FString, float>& InAnimationData);` (scope `UE::MetaHuman`)
