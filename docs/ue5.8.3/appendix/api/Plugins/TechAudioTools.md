# Plugins / TechAudioTools

- module root: `Plugins/Experimental/TechAudioTools/Source/TechAudioTools`
- headers: 5; symbols: 79
- symbol kinds: class=3, enum=5, enumerator=21, function=13, member=20, namespace=1, prototype=16
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core, ModelViewViewModel

### `Plugins/Experimental/TechAudioTools/Source/TechAudioTools/Public/TechAudioToolsFloatMapping.h` (Public)


#### class `UTechAudioToolsFloatMapping`  
`class UTechAudioToolsFloatMapping : public UObject`  
_L60-156_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, DefaultToInstanced, CollapseCategories, DisplayName = "TechAudioTools Float Mapping")`
- inherits: `UObject`
- desc: Base class for any float value mapping that translates between two domains: - Source domain: range used by an internal system (e.g. a MetaSound that uses linear gain or frequency multiplier). - Display domain: how that value is shown or edited in the UI (e.g. sliders or knobs that use decibels or semitones).
- L67 _public member_ `ETechAudioToolsFloatMappingType MappingType = ETechAudioToolsFloatMappingType::Default;` — `UPROPERTY(EditAnywhere, Category = "Range")` — Selects the mapping mode.
- L73 _public member_ `FFloatInterval Range { 0.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Range", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Default", EditConditionHides))` — Default min/max values.
- L79 _public member_ `FFloatInterval SourceRange { 0.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Range", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::MapRange", EditConditionHides))` — Range used by an internal system.
- L83 _public member_ `FFloatInterval DisplayRange { 0.f, 1.f };` — `UPROPERTY(EditAnywhere, Category = "Range", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::MapRange", EditConditionHides))` — Range displayed in a user interface.
- L87 _public member_ `ETechAudioToolsFloatUnit DisplayUnits = ETechAudioToolsFloatUnit::None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Map Range", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Default || MappingType == ETechAudioToolsFloatMappingType::MapRange", EditConditionHides))` — Units used to label the display range.
- L93 _public member_ `ETechAudioToolsVolumeUnit SourceVolumeUnits = ETechAudioToolsVolumeUnit::LinearGain;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Volume", EditConditionHides))` — Units of the internal volume value.
- L97 _public member_ `ETechAudioToolsVolumeUnit DisplayVolumeUnits = ETechAudioToolsVolumeUnit::Decibels;` — `UPROPERTY(EditAnywhere, Category = "Volume", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Volume", EditConditionHides))` — Units to show volume in a user interface.
- L101 _public member_ `FFloatInterval DisplayRange_Decibels { -60.f, 6.f };` — `UPROPERTY(EditAnywhere, Category = "Volume", DisplayName = "Display Decibel Range", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Volume && DisplayVolumeUnits == ETechAudioToolsVolumeUnit::Decibels", EditConditionHides, ClampMin = "-60", ClampMax = "24"))` — Range in decibels to display in a user interface.
- L105 _public member_ `FFloatInterval DisplayRange_LinearGain { 0.001f, 4.f };` — `UPROPERTY(EditAnywhere, Category = "Volume", DisplayName = "Display Linear Gain Range", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Volume && DisplayVolumeUnits == ETechAudioToolsVolumeUnit::LinearGain", EditConditionHides, ClampMin = "0.0", ClampMax = "8.0"))` — Range in linear gain to display in a user interface.
- L111 _public member_ `ETechAudioToolsPitchUnit SourcePitchUnits = ETechAudioToolsPitchUnit::Semitones;` — `UPROPERTY(EditAnywhere, Category = "Pitch", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Pitch", EditConditionHides))` — Units of the internal pitch value.
- L115 _public member_ `ETechAudioToolsPitchUnit DisplayPitchUnits = ETechAudioToolsPitchUnit::Semitones;` — `UPROPERTY(EditAnywhere, Category = "Pitch", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Pitch", EditConditionHides))` — Units to show pitch in a user interface.
- L119 _public member_ `FFloatInterval DisplayRange_Semitones { -12.f, 12.f };` — `UPROPERTY(EditAnywhere, Category = "Pitch", DisplayName = "Display Semitone Range", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Pitch && DisplayPitchUnits == ETechAudioToolsPitchUnit::Semitones", EditConditionHides, ClampMin = "-120", ClampMax = "120"))` — Range in semitones to display in a user interface.
- L123 _public member_ `FFloatInterval DisplayRange_FrequencyMultiplier { 0.5f, 2.f };` — `UPROPERTY(EditAnywhere, Category = "Pitch", DisplayName = "Display Frequency Multiplier Range", meta = (EditCondition = "MappingType == ETechAudioToolsFloatMappingType::Pitch && DisplayPitchUnits == ETechAudioToolsPitchUnit::FrequencyMultiplier", EditConditionHides, ClampMin = "0.125", ClampMax = "8"))` — Range in frequency multiplier to display in a user interface.
- L127 _public prototype_ `ETechAudioToolsFloatUnit GetUnits(ETechAudioToolsMappingEndpoint Endpoint) const;` — `UFUNCTION(BlueprintPure, Category = "Range")` — Returns the units used by the Source or Display endpoints.
- L131 _public function_ `float GetSourceMin() const` — `UFUNCTION(BlueprintPure, Category = "Range")` — Returns the range minimum of the source range.
- L135 _public function_ `float GetSourceMax() const` — `UFUNCTION(BlueprintPure, Category = "Range")` — Returns the range maximum of the source range.
- L139 _public function_ `float GetDisplayMin() const` — `UFUNCTION(BlueprintPure, Category = "Range")` — Returns the range minimum of the display range.
- L143 _public function_ `float GetDisplayMax() const` — `UFUNCTION(BlueprintPure, Category = "Range")` — Returns the range maximum of the display range.
- L145 _public prototype_ `float SourceToDisplay(float InSource) const;`
- L146 _public prototype_ `float DisplayToSource(float InDisplay) const;`
- L148 _public prototype_ `float NormalizedToSource(float InNormalized) const;`
- L149 _public prototype_ `float SourceToNormalized(float InSource) const;`
- L151 _public prototype_ `float NormalizedToDisplay(float InNormalized) const;`
- L152 _public prototype_ `float DisplayToNormalized(float InDisplay) const;`
- L155 _private prototype_ `FFloatInterval GetRange(const ETechAudioToolsMappingEndpoint Endpoint) const;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TechAudioTools`
- L13 _function_ `FORCEINLINE float ConvertUnit(const ETechAudioToolsVolumeUnit FromUnits, const ETechAudioToolsVolumeUnit ToUnits, const float Value)` (scope `TechAudioTools`) — Converts volume values between linear gain and decibels
- L24 _function_ `FORCEINLINE float ConvertUnit(const ETechAudioToolsPitchUnit FromUnits, const ETechAudioToolsPitchUnit ToUnits, const float Value)` (scope `TechAudioTools`) — Converts pitch values between semitones and frequency multiplier
- L35 _function_ `template <typename UnitT> FORCEINLINE FFloatInterval ConvertRange(UnitT FromUnits, UnitT ToUnits, FFloatInterval InputRange)` (scope `TechAudioTools`)

### `Plugins/Experimental/TechAudioTools/Source/TechAudioTools/Public/TechAudioToolsLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTechAudioTools, Log, All);`

### `Plugins/Experimental/TechAudioTools/Source/TechAudioTools/Public/TechAudioToolsTypes.h` (Public)


#### enum `ETechAudioToolsMappingEndpoint`  
`enum class ETechAudioToolsMappingEndpoint : uint8`  
_L9-13_
- reflection: `UENUM(BlueprintType)`
- desc: Identifies which side of a mapping a value belongs to.
- L11 _public enumerator_ `Source UMETA(DisplayName = "Source", ToolTip = "Refers to values intended to be used by an internal system (e.g. a MetaSound"), Display UMETA(DisplayName = "Display", ToolTip = "Refers to values intended to be displayed via a user interface (e.g. a MetaSound preset widget"), }; UENUM(BlueprintType) enum class ETechAudioToolsFloatUnit : uint8 {`
- L12 _public enumerator_ `Display UMETA(DisplayName = "Display", ToolTip = "Refers to values intended to be displayed via a user interface (e.g. a MetaSound preset widget"), }; UENUM(BlueprintType) enum class ETechAudioToolsFloatUnit : uint8 { None UMETA(DisplayName = "None"),`

#### enum `ETechAudioToolsFloatUnit`  
`enum class ETechAudioToolsFloatUnit : uint8`  
_L17-30_
- reflection: `UENUM(BlueprintType)`
- desc: Float unit types used primarily for formatting values.
- L19 _public enumerator_ `None UMETA(DisplayName = "None")`
- L20 _public enumerator_ `Multiplier UMETA(DisplayName = "Multiplier", ToolTip = "Linear multiplier (1.0 = unity)")`
- L21 _public enumerator_ `Decibels UMETA(DisplayName = "Decibels", ToolTip = "Amplitude in dB (0 dB = unity)")`
- L22 _public enumerator_ `Hertz UMETA(DisplayName = "Hertz", ToolTip = "Frequency in Hertz (e.g. 20-20,000)")`
- L23 _public enumerator_ `Semitones UMETA(DisplayName = "Semitones", ToolTip = "Pitch offset in semitones (-12 = one octave down)")`
- L24 _public enumerator_ `TimeSeconds UMETA(DisplayName = "Seconds", ToolTip = "Time in seconds")`
- L25 _public enumerator_ `TimeMilliseconds UMETA(DisplayName = "Milliseconds", ToolTip = "Time in ms")`
- L26 _public enumerator_ `Degrees UMETA(DisplayName = "Degrees", ToolTip = "Angle in degrees (0-360)")`
- L27 _public enumerator_ `Pan UMETA(DisplayName = "Pan", ToolTip = "Pan value: negative = L, 0 = C, positive = R")`
- L28 _public enumerator_ `BandwidthOct UMETA(DisplayName = "Bandwidth", ToolTip = "Filter bandwidth in octaves (1.0 = one octave)")`
- L29 _public enumerator_ `Tempo UMETA(DisplayName = "Tempo", ToolTip = "Tempo in beats per minute (BPM)")`

#### enum `ETechAudioToolsFloatMappingType`  
`enum class ETechAudioToolsFloatMappingType : uint8`  
_L34-40_
- reflection: `UENUM(BlueprintType)`
- desc: The mapping logic applied between source and display values.
- L36 _public enumerator_ `Default UMETA(DisplayName = "Default", ToolTip = "No mapping is applied. Display range is the same as the source range.")`
- L37 _public enumerator_ `MapRange UMETA(DisplayName = "Map Range", ToolTip = "Linear remap between the source and display ranges. Does not convert units (e.g. seconds will not be converted to milliseconds).")`
- L38 _public enumerator_ `Volume UMETA(DisplayName = "Volume", ToolTip = "Remaps a given volume range and converts between Linear Gain and Decibels if necessary.")`
- L39 _public enumerator_ `Pitch UMETA(DisplayName = "Pitch", ToolTip = "Remaps a given pitch range and converts between Semitones and Frequency Multiplier if necessary.")`

#### enum `ETechAudioToolsVolumeUnit`  
`enum class ETechAudioToolsVolumeUnit : uint8`  
_L44-48_
- reflection: `UENUM()`
- desc: Defines the units used when interpreting a float as volume.
- L46 _public enumerator_ `Decibels UMETA(DisplayName = "Decibels", ToolTip = "Decibels (logarithmic)")`
- L47 _public enumerator_ `LinearGain UMETA(DisplayName = "Linear Gain", ToolTip = "Linear gain multiplier")`

#### enum `ETechAudioToolsPitchUnit`  
`enum class ETechAudioToolsPitchUnit : uint8`  
_L52-56_
- reflection: `UENUM()`
- desc: Defines the units used when interpreting a float as pitch.
- L54 _public enumerator_ `Semitones UMETA(DisplayName = "Semitones", ToolTip = "Pitch offset in semitones")`
- L55 _public enumerator_ `FrequencyMultiplier UMETA(DisplayName = "Frequency Multiplier", ToolTip = "Frequency multiplier (2.0 = one octave up)")`

### `Plugins/Experimental/TechAudioTools/Source/TechAudioTools/Public/Viewmodels/AudioComponentViewModel.h` (Public)


#### class `UAudioComponentViewModel`  
`class UAudioComponentViewModel : public UMVVMViewModelBase`  
_L14-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DisplayName = "Audio Component Viewmodel")`
- inherits: `UMVVMViewModelBase`
- desc: Viewmodel for binding audio component state to widgets.
- L21 _private member_ `EAudioComponentPlayState PlayState = EAudioComponentPlayState::Stopped;` — `UPROPERTY(BlueprintReadOnly, Transient, FieldNotify, Getter = "GetPlayState", Category = "Audio Component", meta = (AllowPrivateAccess))` — Returns the enumerated play state of the audio component.
- L25 _private member_ `bool bIsPlaying = false;` — `UPROPERTY(BlueprintReadOnly, Transient, FieldNotify, Getter = "IsPlaying", Category = "Audio Component", meta = (AllowPrivateAccess))` — True if the audio component is playing.
- L29 _private member_ `bool bIsStopped = true;` — `UPROPERTY(BlueprintReadOnly, Transient, FieldNotify, Getter = "IsStopped", Category = "Audio Component", meta = (AllowPrivateAccess))` — True if the audio component is stopped.
- L33 _private member_ `bool bIsFadingIn = false;` — `UPROPERTY(BlueprintReadOnly, Transient, FieldNotify, Getter = "IsFadingIn", Category = "Audio Component", meta = (AllowPrivateAccess))` — True if the audio component is fading in.
- L37 _private member_ `bool bIsFadingOut = false;` — `UPROPERTY(BlueprintReadOnly, Transient, FieldNotify, Getter = "IsFadingOut", Category = "Audio Component", meta = (AllowPrivateAccess))` — True if the audio component is fading out.
- L41 _private member_ `bool bIsVirtualized = false;` — `UPROPERTY(BlueprintReadOnly, Transient, FieldNotify, Getter = "IsVirtualized", Category = "Audio Component", meta = (AllowPrivateAccess))` — True if the audio component is virtualized.
- L45 _protected member_ `TWeakObjectPtr<UAudioComponent> AudioComponent;` — `UPROPERTY(Transient)`
- L50 _public prototype_ `virtual void SetAudioComponent(UAudioComponent* InAudioComponent);` — `UFUNCTION(BlueprintCallable, Category = "TechAudioTools|Audio Component")` — Sets the audio component this viewmodel should bind to.
- L52 _public function_ `EAudioComponentPlayState GetPlayState() const`
- L53 _public function_ `bool IsPlaying() const`
- L54 _public function_ `bool IsStopped() const`
- L55 _public function_ `bool IsFadingIn() const`
- L56 _public function_ `bool IsFadingOut() const`
- L57 _public function_ `bool IsVirtualized() const`
- L59 _public prototype_ `virtual void BeginDestroy() override;`
- L62 _protected prototype_ `void BindDelegates();`
- L63 _protected prototype_ `void UnbindDelegates();`
- L66 _protected prototype_ `void OnAudioFinished();` — `UFUNCTION()`
- L69 _protected prototype_ `void OnVirtualizationChanged(bool bInIsVirtualized);` — `UFUNCTION()`
- L73 _private prototype_ `void SetPlayState(EAudioComponentPlayState NewPlayState);` — `UFUNCTION()`

### `Plugins/Experimental/TechAudioTools/Source/TechAudioTools/Public/Viewmodels/TechAudioToolsConversionFunctions.h` (Public)


#### class `UTechAudioToolsConversionFunctions`  
`class UTechAudioToolsConversionFunctions : public UBlueprintFunctionLibrary`  
_L10-15_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
