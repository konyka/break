# Plugins / SoundUtilities

- module root: `Plugins/Runtime/SoundUtilities/Source/SoundUtilities`
- headers: 3; symbols: 36
- symbol kinds: class=3, delegate=1, function=1, macro=1, member=6, prototype=23, struct=1
- PublicDependencyModuleNames: AudioMixer, Core, CoreUObject, Engine, InputCore, Projects, Slate, SlateCore, UMG

### `Plugins/Runtime/SoundUtilities/Source/SoundUtilities/Public/SoundSimple.h` (Public)


#### struct `FSoundVariation`  
`struct FSoundVariation`  
_L14-41_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `TObjectPtr<USoundWave> SoundWave;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundVariation")` — The sound wave asset to use for this variation
- L24 _public member_ `float ProbabilityWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The probability weight to use for this variation
- L28 _public member_ `FVector2D VolumeRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The volume range to use for this variation
- L32 _public member_ `FVector2D PitchRange;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synth|Preset")` — The pitch range to use for this variation
- L34 _public function_ `FSoundVariation() : SoundWave(nullptr) , ProbabilityWeight(1.0f) , VolumeRange(1.0f, 1.0f) , PitchRange(1.0f, 1.0f)`

#### class `USoundSimple`  
`class USoundSimple : public USoundBase`  
_L45-74_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Sound, meta = (BlueprintSpawnableComponent))`
- inherits: `USoundBase`
- desc: Class which contains a simple list of sound wave variations
- L53 _public member_ `TArray<FSoundVariation> Variations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variations")` — List of variations for the simple sound
- L56 _public prototype_ `virtual void PostLoad() override;`
- L57 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L61 _public prototype_ `virtual bool IsPlayable() const override;`
- L62 _public prototype_ `virtual void Parse(class FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances) override;`
- L63 _public prototype_ `virtual float GetMaxDistance() const override;`
- L64 _public prototype_ `virtual float GetDuration() const override;`
- L68 _protected prototype_ `void ChooseSoundWave();`
- L69 _protected prototype_ `void CacheValues();`
- L73 _protected member_ `TObjectPtr<USoundWave> SoundWave;` — `UPROPERTY(transient)` — The current chosen sound wave

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SOUNDUTILITIES_API`

### `Plugins/Runtime/SoundUtilities/Source/SoundUtilities/Public/SoundUtilities.h` (Public)


#### class `USoundUtilitiesBPFunctionLibrary`  
`class USoundUtilitiesBPFunctionLibrary : public UBlueprintFunctionLibrary`  
_L12-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Sound Utilities Blueprint Function Library A library of Sound related functions for use in Blueprints
- L18 _private prototype_ `static float GetBeatTempo(float BeatsPerMinute = 120.0f, int32 BeatMultiplier = 1, int32 DivisionsOfWholeNote = 4);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Calculates a beat time in seconds from the given BPM, beat multiplier and divisions of a whole note.
- L26 _private prototype_ `static float GetFrequencyFromMIDIPitch(const int32 MidiNote);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Calculates Frequency values based on MIDI Pitch input @param MidiNote	The MIDI note to calculate the frequency of @return			The frequency in Hz that corresponds to the MIDI input
- L34 _private prototype_ `static int32 GetMIDIPitchFromFrequency(const float Frequency);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Calculates MIDI Pitch values based on frequency input @param Frequency		The frequency in Hz to convert into MIDI @return				The MIDI note closest to the inputted frequency
- L44 _private prototype_ `static float GetPitchScaleFromMIDIPitch(const int32 BaseMidiNote, const int32 TargetMidiNote);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Calculates Pitch Scalar based on starting frequency and desired MIDI Pitch output @param BaseMidiNote		The MIDI note corresponding to the starting frequency @param TargetMidiNote	The MIDI note corresponding to the desired final frequency @return					The amount to scale the pitch of the base note by, in order for its pitch to match the target MIDI note
- L52 _private prototype_ `static float GetGainFromMidiVelocity(int InVelocity);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Given a velocity value [0,127], return the linear gain @param InVelocity	The MIDI velocity value to calculate the gain of @return				The gain corresponding to the MIDI value
- L61 _private prototype_ `static float ConvertLinearToDecibels(const float InLinear, const float InFloor);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary", meta = (AdvancedDisplay = 1))` — Converts linear scale volume to decibels @param InLinear					The linear scalar value to convert to decibels @param InFloor					The floor value to check against @return							The decibel value of the inputted linear scale
- L69 _private prototype_ `static float ConvertDecibelsToLinear(const float InDecibels);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Converts decibel to linear scale @param InDecibels	The decibels to convert to a linear gain scalar @return				The resulting linear gain
- L79 _private prototype_ `static float GetLogFrequencyClamped(const float InValue, const FVector2D& InDomain, const FVector2D& InRange);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Returns the log frequency of the input value. Maps linear domain and range values to log output (good for linear slider controlling frequency) @param InValue					The linear value to convert to logarithmic frequency @param InDomain					The domain to use when converting between linear and logarithmic scales @param InRange					The range to use when converting between linear and logarithmic scales @return							The log frequency of the given input
- L90 _private prototype_ `static float GetLinearFrequencyClamped(const float InValue, const FVector2D& InDomain, const FVector2D& InRange);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Returns the linear frequency of the input value. Maps log domain and range values to linear output (good for linear slider representation/visualization of log frequency). Reverse of GetLogFrequencyClamped. @param InValue					The logarithmic value to convert to linear frequency @param InDomain					The domain to use when converting between linear and logarithmic scales @param InRange					The range to use when converting between linear and logarithmic scales @return							The linear frequency of the given logarithmic input
- L98 _private prototype_ `static float GetFrequencyMultiplierFromSemitones(const float InPitchSemitones);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Returns the frequency multiplier to scale a base frequency given the input semitones @param InPitchSemitones	The amount of semitones to alter a frequency by @return					The frequency multiplier that corresponds to the given change in semitones
- L106 _private prototype_ `static float GetBandwidthFromQ(const float InQ);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary")` — Helper function to get bandwidth from Q @param InQ	The Q value to convert to bandwidth @return		The bandwidth value that corresponds to the given Q value
- L114 _private prototype_ `static float GetQFromBandwidth(const float InBandwidth);` — `UFUNCTION(BlueprintCallable, Category = "SoundUtilitiesBPLibrary", DisplayName = "Get Q From Bandwidth")` — Helper function to get Q from bandwidth @param InBandwidth	The bandwidth value to convert to Q @return				The Q value that corresponds to the given bandwidth value

### `Plugins/Runtime/SoundUtilities/Source/SoundUtilities/Public/SoundUtilitiesModule.h` (Public)


#### class `FSoundUtilitiesModule`  
`class FSoundUtilitiesModule: public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L16 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSoundUtilities, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSoundUtilities, Log, All);`
