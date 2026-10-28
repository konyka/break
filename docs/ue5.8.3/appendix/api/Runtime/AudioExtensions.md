# Runtime / AudioExtensions

- module root: `Source/Runtime/AudioExtensions`
- headers: 19; symbols: 795
- symbol kinds: class=65, delegate=3, enum=5, enumerator=28, function=178, macro=5, member=168, namespace=11, prototype=278, struct=31, typedef=22, variable=1
- PublicDependencyModuleNames: AudioMixerCore, Core, CoreUObject, SignalProcessing
- PublicIncludePathModuleNames: AudioMixer

### `Source/Runtime/AudioExtensions/Private/AudioExtentionsModule.h` (Private)


#### class `FAudioExtensionsModule`  
`class FAudioExtensionsModule final : public IModuleInterface`  
_L6-12_
- inherits: `IModuleInterface`
- L9 _public prototype_ `static FAudioExtensionsModule* Get();`
- L11 _public prototype_ `virtual void StartupModule() override;`

### `Source/Runtime/AudioExtensions/Public/AudioExtensionsLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioExtensions, Display, All);`

### `Source/Runtime/AudioExtensions/Public/AudioParameter.h` (Public)


#### struct `Audio::FParameterPath`  
`struct FParameterPath`  
_L28-37_
- L30 _public member_ `static const FString NamespaceDelimiter;`
- L33 _public prototype_ `static FName CombineNames(FName InLeft, FName InRight);` — Combines names using the namespace delimiter
- L36 _public prototype_ `static void SplitName(FName InFullName, FName& OutNamespace, FName& OutParameterName);` — Splits name into namespace & parameter name

#### enum `EAudioParameterType`  
`enum class EAudioParameterType : uint8`  
_L41-88_
- reflection: `UENUM()`
- L48 _public enumerator_ `None UMETA(DisplayName = "Default")` — 'Default' results in behavior that is resolved based on the system interpreting it.  To support legacy implementation, SoundCues cache all typed values associated with a given parameter name. For MetaSounds, use a specific Type instead of this one.
- L51 _public enumerator_ `Boolean` — Boolean value
- L54 _public enumerator_ `Integer` — Integer value
- L57 _public enumerator_ `Float` — Float value
- L60 _public enumerator_ `String` — String value (not supported by legacy SoundCue system)
- L63 _public enumerator_ `Object` — Object value (types other than SoundWave not supported by legacy SoundCue system)
- L67 _public enumerator_ `NoneArray UMETA(Hidden, DisplayName = "Default (Array)")` — Array of default initialized values (not supported by legacy SoundCue system) Hidden for now as no parameter types exist that support default construction
- L70 _public enumerator_ `BooleanArray UMETA(DisplayName = "Boolean (Array)")` — Array of boolean values (not supported by legacy SoundCue system)
- L73 _public enumerator_ `IntegerArray UMETA(DisplayName = "Integer (Array)")` — Array of integer values (not supported by legacy SoundCue system)
- L76 _public enumerator_ `FloatArray UMETA(DisplayName = "Float (Array)")` — Array of float values (not supported by legacy SoundCue system)
- L79 _public enumerator_ `StringArray UMETA(DisplayName = "String (Array)")` — Array of string values (not supported by legacy SoundCue system)
- L82 _public enumerator_ `ObjectArray UMETA(DisplayName = "Object (Array)")` — Array of object values (not supported by legacy SoundCue system)
- L85 _public enumerator_ `Trigger` — Trigger value
- L87 _public enumerator_ `COUNT UMETA(Hidden)`

#### struct `FAudioParameter`  
`struct FAudioParameter`  
_L92-344_
- reflection: `USTRUCT(BlueprintType)`
- L96 _public prototype_ `FAudioParameter() = default;`
- L98 _public function_ `FAudioParameter(FName InName) : ParamName(InName)`
- L103 _public function_ `FAudioParameter(FName InName, float InValue) : ParamName(InName) , FloatParam(InValue) , ParamType(EAudioParameterType::Float)`
- L110 _public function_ `FAudioParameter(FName InName, bool InValue) : ParamName(InName) , BoolParam(InValue) , ParamType(EAudioParameterType::Boolean)`
- L117 _public function_ `FAudioParameter(FName InName, int32 InValue) : ParamName(InName) , IntParam(InValue) , ParamType(EAudioParameterType::Integer)`
- L124 _public function_ `FAudioParameter(FName InName, UObject* InValue) : ParamName(InName) , ObjectParam(InValue) , ParamType(EAudioParameterType::Object)`
- L131 _public function_ `FAudioParameter(FName InName, const FString& InValue) : ParamName(InName) , StringParam(InValue) , ParamType(EAudioParameterType::String)`
- L138 _public function_ `FAudioParameter(FName InName, const TArray<float>& InValue) : ParamName(InName) , ArrayFloatParam(InValue) , ParamType(EAudioParameterType::FloatArray)`
- L145 _public function_ `FAudioParameter(FName InName, TArray<float>&& InValue) : ParamName(InName) , ArrayFloatParam(MoveTemp(InValue)) , ParamType(EAudioParameterType::FloatArray)`
- L152 _public function_ `FAudioParameter(FName InName, const TArray<bool>& InValue) : ParamName(InName) , ArrayBoolParam(InValue) , ParamType(EAudioParameterType::BooleanArray)`
- L159 _public function_ `FAudioParameter(FName InName, TArray<bool>&& InValue) : ParamName(InName) , ArrayBoolParam(MoveTemp(InValue)) , ParamType(EAudioParameterType::BooleanArray)`
- L166 _public function_ `FAudioParameter(FName InName, const TArray<int32>& InValue) : ParamName(InName) , ArrayIntParam(InValue) , ParamType(EAudioParameterType::IntegerArray)`
- L173 _public function_ `FAudioParameter(FName InName, TArray<int32>&& InValue) : ParamName(InName) , ArrayIntParam(MoveTemp(InValue)) , ParamType(EAudioParameterType::IntegerArray)`
- L180 _public function_ `FAudioParameter(FName InName, const TArray<UObject*>& InValue) : ParamName(InName) , ArrayObjectParam(InValue) , ParamType(EAudioParameterType::ObjectArray)`
- L197 _public function_ `FAudioParameter(FName InName, const TArray<FString>& InValue) : ParamName(InName) , ArrayStringParam(InValue) , ParamType(EAudioParameterType::StringArray)`
- L204 _public function_ `FAudioParameter(FName InName, TArray<FString>&& InValue) : ParamName(InName) , ArrayStringParam(MoveTemp(InValue)) , ParamType(EAudioParameterType::StringArray)`
- L211 _public function_ `FAudioParameter(FName InName, EAudioParameterType Type) : ParamName(InName) , ParamType(Type)`
- L222 _public function_ `static FAudioParameter CreateDefaultArray(FName InName, int32 InNum)` — Static function to avoid int32 constructor collision
- L233 _public prototype_ `void Merge(const FAudioParameter& InParameter, bool bInTakeName = true, bool bInTakeType = true, bool bInMergeArrayTypes = false);` — Sets values specified by type field of the given parameter on this parameter. If the provided parameter is set to type 'None', takes all values of the given parameter. bInTakeName = Take the name of the provided parameter. bInTakeType = Take the type of the provided parameter. bInMergeArrayTypes - Appends array(s) for specified type if true, else swaps the local value with that of the provided parameter if false.
- L239 _public prototype_ `static void Merge(TArray<FAudioParameter>&& InParams, TArray<FAudioParameter>& OutParams);` — Moves InParams to OutParams that are not already included. For backward compatibility (i.e. SoundCues), if a param is already in OutParams, attempts to merge param values together, but assigns the param the incoming param's type. Currently existing OutParam values left if new value of the same type is provided by InParam.
- L241 _public prototype_ `FAudioParameter(FAudioParameter&& InParameter) = default;`
- L242 _public prototype_ `FAudioParameter(const FAudioParameter& InParameter) = default;`
- L244 _public prototype_ `FAudioParameter& operator=(const FAudioParameter& InParameter) = default;`
- L245 _public prototype_ `FAudioParameter& operator=(FAudioParameter&& InParameter) = default;`
- L249 _public member_ `FName ParamName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName="Name"), Category = AudioParameter)` — Name of the parameter
- L253 _public member_ `float FloatParam = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (Float)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::None || ParamType == EAudioParameterType::Float"), Category = AudioParameter)` — Float value of parameter
- L257 _public member_ `bool BoolParam = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (Bool)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::None || ParamType == EAudioParameterType::Boolean"), Category = AudioParameter)` — Boolean value of parameter
- L261 _public member_ `int32 IntParam = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (Int)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::None || ParamType == EAudioParameterType::Integer || ParamType == EAudioParameterType::NoneArray"), Category = AudioParameter)` — Integer value of parameter. If set to 'Default Construct', value is number of array items to construct.
- L265 _public member_ `TObjectPtr<UObject> ObjectParam = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (Object)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::None || ParamType == EAudioParameterType::Object"), Category = AudioParameter)` — Object value of parameter
- L269 _public member_ `FString StringParam;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (String)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::String"), Category = AudioParameter)` — String value of parameter
- L273 _public member_ `TArray<float> ArrayFloatParam;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (Float Array)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::FloatArray"), Category = AudioParameter)` — Array Float value of parameter
- L277 _public member_ `TArray<bool> ArrayBoolParam;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (Bool Array)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::BooleanArray"), Category = AudioParameter)` — Boolean value of parameter
- L281 _public member_ `TArray<int32> ArrayIntParam;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (Int Array)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::IntegerArray"), Category = AudioParameter)` — Integer value of parameter
- L285 _public member_ `TArray<TObjectPtr<UObject>> ArrayObjectParam;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (Object Array)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::ObjectArray"), Category = AudioParameter)` — Object value of parameter
- L289 _public member_ `TArray<FString> ArrayStringParam;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Value (String Array)", DisplayAfter = "ParamType", EditConditionHides, EditCondition = "ParamType == EAudioParameterType::StringArray"), Category = AudioParameter)` — String value of parameter
- L292 _public member_ `EAudioParameterType ParamType = EAudioParameterType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Type"), Category = AudioParameter)`
- L296 _public member_ `FName TypeName;` — `UPROPERTY()` — Optional TypeName used to describe what constructed type this parameter should be initializing.
- L299 _public member_ `TArray<TSharedPtr<Audio::IProxyData>> ObjectProxies;` — Object proxies to be generated when parameter is passed to the AudioThread to represent ObjectParam/ArrayObjectParam safely
- L302 _public function_ `static const FAudioParameter* FindParam(const TArray<FAudioParameter>& InParams, FName InParamName)` — Common find algorithm for default/legacy parameter system
- L319 _public function_ `static FAudioParameter* FindOrAddParam(TArray<FAudioParameter>& OutParams, FName InParamName)` — Common find & add algorithm for default/legacy parameter system.

#### Free symbols / members of external scopes

- L21 _macro_ `#define AUDIO_PARAMETER_NAMESPACE_PATH_DELIMITER "."`
- L24 _macro_ `#define AUDIO_PARAMETER_INTERFACE_MEMBER_DEFINE(Name) (AUDIO_PARAMETER_INTERFACE_NAMESPACE AUDIO_PARAMETER_NAMESPACE_PATH_DELIMITER Name)` — Convenience macro for statically declaring an interface member's FName. AUDIO_PARAMETER_INTERFACE_NAMESPACE must be defined.
- L26 _namespace_ `namespace Audio`

### `Source/Runtime/AudioExtensions/Public/AudioParameterControllerInterface.h` (Public)


#### class `UAudioParameterControllerInterface`  
`class UAudioParameterControllerInterface : public UInterface`  
_L25-28_
- reflection: `UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint), MinimalAPI)`
- inherits: `UInterface`

#### class `IAudioParameterControllerInterface`  
`class IAudioParameterControllerInterface : public IInterface`  
_L31-109_
- inherits: `IInterface`
- desc: Base interface for any object implementing parameter control for a given sound instance controller.
- L38 _public prototype_ `virtual void ResetParameters() = 0;` — `UFUNCTION(BlueprintCallable, Category = "Audio|Parameter")` — Resets all parameters to their original values.
- L45 _public prototype_ `virtual void SetTriggerParameter(FName InName) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Trigger Parameter"), Category = "Audio|Parameter")` — Executes a named trigger.  Does *not* cache trigger value, so only executes if the sound is already playing.  If the intent is for the trigger to execute immediately (if playing) and be called on initialization for all future instances, call 'SetBoolParameter' with the intended initial trigger behavior (true if trigger desired on initialization, false if not).
- L49 _public prototype_ `virtual void SetBoolParameter(FName InName, bool InBool) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Boolean Parameter"), Category = "Audio|Parameter")` — Sets a named Boolean
- L53 _public prototype_ `virtual void SetBoolArrayParameter(FName InName, const TArray<bool>& InValue) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Boolean Array Parameter"), Category = "Audio|Parameter")` — Sets a named Boolean Array
- L57 _public prototype_ `virtual void SetIntParameter(FName InName, int32 InInt) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Integer Parameter"), Category = "Audio|Parameter")` — Sets a named Int32
- L61 _public prototype_ `virtual void SetIntArrayParameter(FName InName, const TArray<int32>& InValue) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Integer Array Parameter"), Category = "Audio|Parameter")` — Sets a named Int32 Array
- L65 _public prototype_ `virtual void SetFloatParameter(FName InName, float InFloat) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Float Parameter"), Category = "Audio|Parameter")` — Sets a named Float
- L69 _public prototype_ `virtual void SetFloatArrayParameter(FName InName, const TArray<float>& InValue) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Float Array Parameter"), Category = "Audio|Parameter")` — Sets a named Float Array
- L73 _public prototype_ `virtual void SetStringParameter(FName InName, const FString& InValue) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set String Parameter"), Category = "Audio|Parameter")` — Sets a named String
- L77 _public prototype_ `virtual void SetStringArrayParameter(FName InName, const TArray<FString>& InValue) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set String Array Parameter"), Category = "Audio|Parameter")` — Sets a named String Array
- L81 _public prototype_ `virtual void SetObjectParameter(FName InName, UObject* InValue) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Object Parameter"), Category = "Audio|Parameter")` — Sets a named UObject
- L85 _public prototype_ `virtual void SetObjectArrayParameter(FName InName, const TArray<UObject*>& InValue) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Object Array Parameter"), Category = "Audio|Parameter")` — Sets a named UObject Array
- L89 _public prototype_ `virtual void SetParameters_Blueprint(const TArray<FAudioParameter>& InParameters) = 0;` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Parameters"), Category = "Audio|Parameter")` — Sets an array of parameters as a batch
- L92 _public prototype_ `virtual void SetParameter(FAudioParameter&& InValue) = 0;` — Sets a named parameter to the given parameter structure value
- L95 _public prototype_ `virtual void SetParameters(TArray<FAudioParameter>&& InValues) = 0;` — Sets an array of parameters as a batch
- L98 _public prototype_ `template<typename DataType> void SetParameter(FName InName, DataType&&) = delete;` — Template Specialization for non-script clients.
- L99 _public function_ `template<typename DataType> void SetParameter(FName InName, DataType&&) = delete;` — Template Specialization for non-script clients.
- L102 _public function_ `template<> void SetParameter(FName InName, bool&& InBool)`
- L103 _public function_ `template<> void SetParameter(FName InName, float&& InFloat)`
- L104 _public function_ `template<> void SetParameter(FName InName, int32&& InInteger)`
- L105 _public function_ `template<> void SetParameter(FName InName, FString&& InString)`
- L106 _public function_ `template<> void SetParameter(FName InName, UObject*&& InObject)`
- L107 _public function_ `template<> void SetParameter(FName InName, TArray<bool>&& InBools)`
- L108 _public function_ `template<> void SetParameter(FName InName, TArray<float>&& InFloats)`

### `Source/Runtime/AudioExtensions/Public/AudioPropertiesSheetAssetBase.h` (Public)


#### class `UAudioPropertiesSheetAssetUserInterface`  
`class UAudioPropertiesSheetAssetUserInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalApi, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IAudioPropertiesSheetAssetUserInterface`  
`class IAudioPropertiesSheetAssetUserInterface`  
_L27-37_
- desc: IAudioPropertiesSheetAssetUserInterface Target objects can implement this interface to bypass parsing coming from a property sheet. Allow/Ignore Property Parsing can be used to set a local property bypass - e.g. from a details view. ShouldParseProperty can be used by a parser to determine if a property should be parsed or not.
- L33 _public prototype_ `virtual void AllowPropertyParsing(const FProperty& TargetProperty) = 0;`
- L34 _public prototype_ `virtual void IgnorePropertyParsing(const FProperty& PropertyToIgnore) = 0;`
- L35 _public prototype_ `virtual bool ShouldParseProperty(const FProperty& TargetProperty) const = 0;`

#### class `UAudioPropertiesSheetAssetBase`  
`class UAudioPropertiesSheetAssetBase : public UObject`  
_L40-52_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L47 _public function_ `virtual bool CopyToObjectProperties(UObject* TargetObject) const` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="AudioProperties")`
- L49 _public function_ `virtual FDelegateHandle BindPropertiesCopyToSheetChanges(UObject* TargetObject)`
- L50 _public function_ `virtual void UnbindCopyFromPropertySheetChanges(UObject* ObjectToUnbind)`

### `Source/Runtime/AudioExtensions/Public/AudioUnknown.h` (Public)


#### struct `Audio::IUnknown`  
`struct IUnknown`  
_L13-21_
- desc: IUnknown like interface for querying unknown data objects of their interfaces. https://en.wikipedia.org/wiki/IUnknown
- L15 _public prototype_ `virtual ~IUnknown() = default;`
- L16 _public function_ `virtual const void* QueryInterface(const FName InInterfaceName) const`
- L20 _public prototype_ `virtual void* QueryInterface(const FName InInterfaceName) = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L30 _function_ `template <CHasInterfaceIdFunction TInterface> const TInterface* QueryInterface(const IUnknown* InUnknown)` (scope `Audio`)
- L40 _function_ `template <CHasInterfaceIdFunction TInterface> TInterface* QueryInterface(IUnknown* InUnknown)` (scope `Audio`)

### `Source/Runtime/AudioExtensions/Public/IAudioDecoderOverride.h` (Public)


#### class `IAudioDecoderOverride`  
`class UE_EXPERIMENTAL(5.8, "Decoder overrides are experimental and the API may be altered or removed") IAudioDecoderOverride`  
_L12-23_
- desc: Allows you to define a factory that can provide an alternative audio file decoder at runtime.
- L16 _public prototype_ `virtual ICompressedAudioInfo* CreateOverrideDecoder(const FName SoundAssetName) = 0;` — Returns an overriden decoder for this sound, or nullptr to allow the default decoder to be created.
- L19 _public prototype_ `virtual bool WantToOverrideDecoder(const FName SoundAssetName) = 0;` — Test if an overriden decoder will be created for this sound.
- L22 _protected prototype_ `virtual ~IAudioDecoderOverride() = default;`

### `Source/Runtime/AudioExtensions/Public/IAudioEndpoint.h` (Public)


#### class `IAudioEndpointSettingsProxy`  
`class IAudioEndpointSettingsProxy`  
_L42-46_
- desc: This interface should be used to provide a non-uclass version of the data described in your implementation of UAudioEndpointSettingsBase.
- L45 _public prototype_ `virtual ~IAudioEndpointSettingsProxy() = default;`

#### class `UAudioEndpointSettingsBase`  
`class UAudioEndpointSettingsBase : public UObject`  
_L53-59_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This opaque class should be used for specifying settings for how audio should be send to an external endpoint.
- L58 _public prototype_ `virtual TUniquePtr<IAudioEndpointSettingsProxy> GetProxy() const PURE_VIRTUAL(UAudioEndpointSettingsBase::GetProxy, return nullptr;);`

#### class `FDummyEndpointSettingsProxy`  
`class FDummyEndpointSettingsProxy : public IAudioEndpointSettingsProxy`  
_L62-64_
- inherits: `IAudioEndpointSettingsProxy`
- desc: A blank class for when unimplemented endpoint types are returned

#### class `UDummyEndpointSettings`  
`class UDummyEndpointSettings : public UAudioEndpointSettingsBase`  
_L67-73_
- reflection: `UCLASS()`
- inherits: `UAudioEndpointSettingsBase`
- L72 _public prototype_ `virtual TUniquePtr<IAudioEndpointSettingsProxy> GetProxy() const override;`

#### class `IAudioEndpoint`  
`class IAudioEndpoint`  
_L80-193_
- desc: Class that allows audio to be sent to an arbitrary locale. This can be used for multi-device rendering, haptics systems, etc. Note that this only for interleaved audio buffers with no metadata for object-based or soundfield-based rendering. For those, see
- L83 _public prototype_ `virtual ~IAudioEndpoint() = default;`
- L97 _public prototype_ `Audio::FPatchInput PatchNewInput(float ExpectedDurationPerRender, float& OutSampleRate, int32& OutNumChannels);` — Create a new patch point for this endpoint. Please see MultithreadedPatching.h to see how to use the FPatchInput class. @param [in] ExpectedDurationPerRender The worst-case amount of time expected between render callbacks. This is used to determined how much to allocate for this input. @param [out] OutSampleRate. The sample rate expected to be pushed to the returned FPatchInput. If you need to resample your input, please see Audio::FResampler. @param [out] OutNumChannels. The number of channels expected to be pushed to the returned FPatchInput. If you need to downmix or upmix your input, try using the following: TArray<float> MixdownGainsMap; Audio::FMixerDevice::Get2DChannelMap(false, NumInputChannels, NumOutputChannels, false, MixdownGainsMap); Audio::DownmixBuffer(NumInputChannels, NumOutputChannels, InputAudio, OutputAudio, MixdownGainsMap.GetData()); @returns a new Audio::FPatchInput. The FPatchInput may be disconnected if this endpoint's sample rate or channel count changes, in which case you will need to reconnect by calling this again.
- L104 _public prototype_ `void SetNewSettings(TUniquePtr<IAudioEndpointSettingsProxy>&& InNewSettings);` — Post new settings for this endpoint. There is no type safety on this call, so make sure that you are using the correct implementation of IAudioEndpointSettingsProxy for this implementation of IAudioEndpoint.
- L109 _public prototype_ `void ProcessAudioIfNeccessary();` — If this audio endpoint hasn't spawned a seperate callback thread but requires a callback, this should be executed somewhere.
- L114 _public prototype_ `virtual bool IsImplemented();` — Whether this endpoint is of an implemented type
- L121 _protected prototype_ `virtual float GetSampleRate() const;` — This should return the sample rate we should be sending to this endpoint. If the sample rate changes, please call DisconnectAllInputs().
- L124 _protected prototype_ `virtual int32 GetNumChannels() const;` — This should return the number of channels we should be sending to this endpoint. If the number of channels changes, please call DisconnectAllInputs.
- L132 _protected function_ `virtual bool EndpointRequiresCallback() const` — For endpoints that do not explicitly fire a timed callback to poll audio data, this should be overridden to return true, and  OnAudioCallback and GetDesiredNumFrames should be overridden.
- L133 _protected function_ `virtual int32 GetDesiredNumFrames() const`
- L140 _protected function_ `virtual bool OnAudioCallback(const TArrayView<const float>& InAudio, const int32& NumChannels, const IAudioEndpointSettingsProxy* InSettings)` — For endpoints that override EndpointRequiresCallback to return true, this callback will be called every (GetDesiredNumFrames() / GetSampleRate()) seconds. @returns whether the endpoint is still valid. If this returns false, DisconnectAllInputs will be called automatically.
- L152 _protected prototype_ `int32 PopAudio(float* OutAudio, int32 NumSamples);` — This is used by the IAudioEndpoint implementation to poll buffered audio to process or send to the endpoint. Note that this is NOT thread safe if EndpointRequiresCallback() is overridden to return true. If that is the case, use an override of OnAudioCallback instead. @param [in] OutAudio: Pointer to already allocated buffer of floats, at least NumSamples long. This will be filled with interleaved audio based on GetNumChannels(). @param [in] NumSamples: The number of samples to fill OutAudio with. @returns [out] the number of samples polled from this thing.
- L160 _protected prototype_ `void PollSettings(TFunctionRef<void(const IAudioEndpointSettingsProxy*)> NewSettingsRetrieved);` — Use this as a thread safe way to use the current settings posted to this IAudioEndpoint. Locks with IAudioEndpoint::SetSettings. @param[in] NewSettingsRetrieved lambda used to work with the retrieved settings. This lambda is called immediately and synchronously, but is used to safely scope usage of the IAudioEndpointSettingsProxy pointer.
- L166 _protected prototype_ `void DisconnectAllInputs();` — Thread safe function to disconnect everything from this endpoint. Anything that owns an Audio::FPatchInput will be notified and will have to call PatchNewInput() again to reconnect.
- L171 _protected prototype_ `void StartRunningAsyncCallback();` — If EndpointRequiresCallback() returns true, this can be used to spawn an async thread and begin calling OnAudioCallback.
- L172 _protected prototype_ `void StopRunningAsyncCallback();`
- L177 _protected prototype_ `void RunCallbackSynchronously();` — If EndpointRequiresCallback() returns true, this can be used to manually run the callback.
- L182 _private member_ `TUniquePtr<Audio::FMixerNullCallback> RenderCallback;` — Owns a scoped thread and runs OnAudioCallback when StartRunningCallback() is called.
- L185 _private member_ `Audio::FAlignedFloatBuffer BufferForRenderCallback;` — If we have a render callback, we pop audio from the PatchMixer to this buffer before calling OnAudioCallback.
- L188 _private member_ `TUniquePtr<IAudioEndpointSettingsProxy> CurrentSettings;` — Owns the current settings for this endpoint.
- L189 _private member_ `FCriticalSection CurrentSettingsCriticalSection;`
- L192 _private member_ `Audio::FPatchMixer PatchMixer;` — Object used to mix all inputs together. Polled when OnAudioCallback is executed or when PollAudio is called.

#### class `IAudioEndpointFactory`  
`class IAudioEndpointFactory : public IModularFeature`  
_L201-254_
- inherits: `IModularFeature`
- desc: This factory is used to expose Endpoint types to the editor. Once a factory is constructed and RegisterEndpointType is called, it will be exposed as a type of endpoint That a submix in the submix graph could be constructed with.
- L205 _public prototype_ `virtual ~IAudioEndpointFactory() = default;` — Virtual destructor
- L208 _public prototype_ `virtual FName GetEndpointTypeName();` — Get the name for the endpoint type that this factory produces.
- L211 _public prototype_ `static FName GetTypeNameForDefaultEndpoint();` — This is a special cased name for endpoint submixes that render directly to the default audio device in Audio::FMixerDevice::OnProcessAudioStream.
- L217 _public prototype_ `static FName GetModularFeatureName();` — This is used when calling IModularFeatures::Get().RegisterModularFeature for IAudioEndpointFactory implementations. It's not needed if one uses RegisterEndpointType() to register IAudioEndpointFactory implementations.
- L223 _public prototype_ `static void RegisterEndpointType(IAudioEndpointFactory* InFactory);` — This needs to be called to make a soundfield format usable by the engine. It can be called from a ISoundfieldFactory subclass' constructor
- L229 _public prototype_ `static void UnregisterEndpointType(IAudioEndpointFactory* InFactory);` — This needs to be called it an implementation of ISoundfieldFactory is about to be destroyed. It can be called from the destructor of an implementation of ISoundfieldFactory.
- L234 _public prototype_ `static IAudioEndpointFactory* Get(const FName& InName);` — Get a registered endpoint factory by name.
- L236 _public prototype_ `static TArray<FName> GetAvailableEndpointTypes();`
- L239 _public prototype_ `virtual TUniquePtr<IAudioEndpoint> CreateNewEndpointInstance(const FAudioPluginInitializationParams& InitInfo, const IAudioEndpointSettingsProxy& InitialSettings);` — Called for every new endpoint submix created with this factory's endpoint type.
- L244 _public prototype_ `virtual UClass* GetCustomSettingsClass() const;` — Should return the StaticClass of this factory's implementation of UAudioEndpointSettingsBase.
- L249 _public prototype_ `virtual const UAudioEndpointSettingsBase* GetDefaultSettings() const;` — return the settings an endpoint should use
- L251 _public member_ `bool bIsImplemented = false;`
- L253 _public prototype_ `static IAudioEndpointFactory* GetDummyFactory();`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioEndpoints, Display, All);`
- L29 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioEndpoints, Display, All);`

### `Source/Runtime/AudioExtensions/Public/IAudioExtensionPlugin.h` (Public)


#### enum `EAudioPlugin`  
`enum class EAudioPlugin : uint8`  
_L39-48_
- desc: Enumeration of audio plugin types
- L41 _public enumerator_ `SPATIALIZATION = 0`
- L42 _public enumerator_ `REVERB = 1`
- L43 _public enumerator_ `OCCLUSION = 2`
- L44 _public enumerator_ `MODULATION = 3`
- L45 _public enumerator_ `SOURCEDATAOVERRIDE = 4`
- L47 _public enumerator_ `COUNT = 5`

#### struct `FSpatializationParams`  
`struct FSpatializationParams`  
_L68-124_
- desc: FSpatializationParams Struct for retrieving parameters needed for computing spatialization and occlusion plugins.
- L71 _public member_ `FVector ListenerPosition;` — The listener position (is likely at the origin).
- L74 _public member_ `FQuat ListenerOrientation;` — The listener orientation.
- L77 _public member_ `FVector EmitterPosition;` — The emitter position relative to listener.
- L80 _public member_ `FVector EmitterWorldPosition;` — The emitter world position.
- L83 _public member_ `FQuat EmitterWorldRotation;` — The emitter world rotation.
- L86 _public member_ `FQuat LastEmitterWorldRotation;` — The emitter world rotation on callback ago.
- L89 _public member_ `FVector LeftChannelPosition;` — The left channel position.
- L92 _public member_ `FVector RightChannelPosition;` — The right channel position.
- L95 _public member_ `float Distance;` — The distance between listener and emitter.
- L98 _public member_ `float AttenuationDistance;` — The distance used to compute attenuation. Maybe different from the distance between listener and emitter if it's overridden.
- L101 _public member_ `float NormalizedOmniRadius;` — Deprecated
- L104 _public member_ `float NonSpatializedAmount;` — The amount of non-spatialized this source is. 1.0 means fully 2D, 0.0 means fully 3D.
- L107 _public member_ `double AudioClock;` — The time when this spatialization params was built.
- L109 _public function_ `FSpatializationParams() : ListenerPosition(FVector::ZeroVector) , ListenerOrientation(FQuat::Identity) , EmitterPosition(FVector::ZeroVector) , EmitterWorldPosition(FVector::ZeroVector) , EmitterWorldRotation(FQuat::Identity) , LastEmitterWorldRotation(FQuat::Identity) , LeftChannelPosition(FVector::ZeroVector) , RightChannelPosition(FVector::ZeroVector) , Distance(0.0f) , AttenuationDistance(0.0f) , NormalizedOmniRadius(0.0f) , NonSpatializedAmount(0.0f) , AudioClock(0.0)`

#### struct `FAudioPluginInitializationParams`  
`struct FAudioPluginInitializationParams`  
_L126-153_
- L129 _public member_ `uint32 NumSources;` — Maximum number of sources that can play simultaneously.
- L132 _public member_ `uint32 NumOutputChannels;` — Number of output channels.
- L135 _public member_ `uint32 SampleRate;` — Sample rate.
- L138 _public member_ `uint32 BufferLength;` — Buffer length used for each callback.
- L143 _public member_ `FAudioDevice* AudioDevicePtr;` — Pointer to audio device owning this audio plugin. IMPORTANT: This will be deprecated once the AudioMixer is taken out of the experimental branch.
- L145 _public function_ `FAudioPluginInitializationParams() : NumSources(0) , NumOutputChannels(0) , SampleRate(0) , BufferLength(0) , AudioDevicePtr(nullptr)`

#### struct `FAudioPluginSourceInputData`  
`struct FAudioPluginSourceInputData`  
_L155-174_
- L158 _public member_ `int32 SourceId;` — The index of the source voice. Guaranteed to be between 0 and the max number of sources rendered.
- L161 _public member_ `uint64 AudioComponentId;` — The ID of the audio component associated with the wave instance.
- L164 _public member_ `Audio::FAlignedFloatBuffer* AudioBuffer;` — The audio input buffer
- L167 _public member_ `int32 NumChannels;` — Number of channels of the source audio buffer.
- L170 _public member_ `FQuat ListenerOrientation;` — The listener orientation.
- L173 _public member_ `const FSpatializationParams* SpatializationParams;` — Spatialization parameters.

#### struct `FAudioPluginSourceOutputData`  
`struct FAudioPluginSourceOutputData`  
_L176-180_
- L179 _public member_ `Audio::FAlignedFloatBuffer AudioBuffer;` — The audio output buffer

#### class `USpatializationPluginSourceSettingsBase`  
`class USpatializationPluginSourceSettingsBase : public UObject`  
_L184-187_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This is a class which should be overridden to provide users with settings to use for individual sounds

#### class `IAudioPluginFactory`  
`class IAudioPluginFactory`  
_L195-238_
- desc: /
- L206 _public function_ `virtual FString GetDisplayName()` — Returns human-readable string representing the display name of this plugin. This is the name that will be used in settings and .ini files. If multiple IAudioPlugin implementations are found that return identical strings here, The first one of these loaded will be used. @return FString of the display name of this plugin.
- L217 _public prototype_ `virtual bool SupportsPlatform(const FString& PlatformName) = 0;` — Returns whether this plugin supports use on the specified platform. @param Platform an enumerated platform (i.e. Windows, Playstation4, etc.) @return true if this plugin supports use on Platform, false otherwise.
- L226 _public function_ `virtual bool IsExternalSend()` — Returns whether this plugin sends audio to an external renderer. if this returns true, the audio engine will not mix the result of the audio process callback from the plugin into the audio output. @return true only if the plugin will handle sending audio to the DAC itself.
- L234 _public function_ `virtual bool ReturnsToSubmixGraph() const` — @return true if the plugin returns from its external submix to a submix in the plugin.

#### class `IAudioSpatializationFactory`  
`class IAudioSpatializationFactory : public IAudioPluginFactory, public IModularFeature`  
_L245-287_
- inherits: `IAudioPluginFactory,IModularFeature`
- desc: /
- L249 _public prototype_ `virtual ~IAudioSpatializationFactory() = default;` — Virtual destructor
- L252 _public function_ `static FName GetModularFeatureName()` — IModularFeature
- L259 _public function_ `virtual FString GetDisplayName() override` — Begin IAudioPluginWithMetadata implementation
- L270 _public function_ `virtual int32 GetMaxSupportedChannels()` — @return the max amount of channels your plugin supports. For example, override this to return 2 to support spatializing mono and stereo sources.
- L278 _public prototype_ `virtual TAudioSpatializationPtr CreateNewSpatializationPlugin(FAudioDevice* OwningDevice) = 0;` — @return a new instance of your spatialization plugin, owned by a shared pointer.
- L283 _public function_ `virtual UClass* GetCustomSpatializationSettingsClass() const` — @return the UClass type of your settings for spatialization. This allows us to only pass in user settings for your plugin.

#### class `IAudioSpatialization`  
`class IAudioSpatialization`  
_L298-388_
- desc: IAudioSpatialization This class represents instances of a plugin that will process spatialization for a stream of audio. Currently used to process a mono-stream through an HRTF spatialization algorithm into a stereo stream. This algorithm contains an audio effect assigned to every VoiceId (playing sound instance). It assumes the effect is updated in the audio engine update loop with new position information.
- L302 _public prototype_ `virtual ~IAudioSpatialization() = default;` — Virtual destructor
- L308 _public function_ `virtual void Shutdown()` — Shuts down the audio plugin.
- L312 _public function_ `virtual void OnDeviceShutdown(FAudioDevice* AudioDevice)`
- L317 _public function_ `virtual void SetSpatializationParameters(uint32 SourceId, const FSpatializationParams& Params)` — DEPRECATED: sets the spatialization effect parameters.
- L322 _public function_ `virtual void GetSpatializationParameters(uint32 SourceId, FSpatializationParams& OutParams)` — DEPRECATED: Gets the spatialization effect parameters.
- L327 _public function_ `virtual void InitializeSpatializationEffect(uint32 BufferLength)` — DEPRECATED: Initializes the spatialization effect with the given buffer length.
- L332 _public function_ `virtual void ProcessSpatializationForVoice(uint32 SourceId, float* InSamples, float* OutSamples, const FVector& Position)` — DEPRECATED: Uses the given HRTF algorithm to spatialize a mono audio stream.
- L337 _public function_ `virtual void ProcessSpatializationForVoice(uint32 SourceId, float* InSamples, float* OutSamples)` — DEPRECATED: Uses the given HRTF algorithm to spatialize a mono audio stream, assumes the parameters have already been set before processing.
- L342 _public function_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USpatializationPluginSourceSettingsBase* InSettings)` — Called when a source is assigned to a voice.
- L346 _public function_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, USpatializationPluginSourceSettingsBase* InSettings)`
- L352 _public function_ `virtual void OnReleaseSource(const uint32 SourceId)` — Called when a source is done playing and is released.
- L357 _public function_ `virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)` — Processes audio with the given input and output data structs.
- L362 _public function_ `virtual void OnAllSourcesProcessed()` — Called when all sources have finished processing.
- L367 _public function_ `virtual bool IsSpatializationEffectInitialized() const` — Returns whether or not the spatialization effect has been initialized
- L373 _public function_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams)` — Initializes the spatialization plugin with the given buffer length.
- L378 _public function_ `virtual bool CreateSpatializationEffect(uint32 SourceId)` — Creates an audio spatialization effect.
- L384 _public function_ `virtual void* GetSpatializationEffect(uint32 SourceId)` — Returns the spatialization effect for the given voice id.

#### class `USourceDataOverridePluginSourceSettingsBase`  
`class USourceDataOverridePluginSourceSettingsBase : public UObject`  
_L393-396_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This is a class which should be overridden to provide users with settings to use for individual sounds

#### class `IAudioSourceDataOverrideFactory`  
`class IAudioSourceDataOverrideFactory : public IAudioPluginFactory, public IModularFeature`  
_L403-436_
- inherits: `IAudioPluginFactory,IModularFeature`
- desc: /
- L407 _public prototype_ `virtual ~IAudioSourceDataOverrideFactory() = default;` — Virtual destructor
- L410 _public function_ `static FName GetModularFeatureName()` — IModularFeature
- L417 _public function_ `virtual FString GetDisplayName() override` — Begin IAudioPluginWithMetadata implementation
- L427 _public function_ `virtual UClass* GetCustomSourceDataOverrideSettingsClass() const` — @return the UClass type of your settings for source data overrides. This allows us to only pass in user settings for your plugin.
- L435 _public prototype_ `virtual TAudioSourceDataOverridePtr CreateNewSourceDataOverridePlugin(FAudioDevice* OwningDevice) = 0;` — @return a new instance of your source data override plugin, owned by a shared pointer.

#### class `IAudioSourceDataOverride`  
`class IAudioSourceDataOverride`  
_L440-470_
- desc: Interface to allow a plugin to override a sound's actual position and simulate propagation (e.g. traversal around corners, etc).
- L444 _public prototype_ `virtual ~IAudioSourceDataOverride() = default;` — Virtual destructor
- L447 _public function_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams)` — Initializes the source data override plugin with the given buffer length.
- L452 _public function_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USourceDataOverridePluginSourceSettingsBase* InSettings)` — Called when a source is assigned to a voice.
- L457 _public function_ `virtual void OnReleaseSource(const uint32 SourceId)` — Called when a source is done playing and is released.
- L462 _public function_ `virtual void GetSourceDataOverrides(const uint32 SourceId, const FTransform& InListenerTransform, FWaveInstance* InOutWaveInstance)` — Allows this plugin to override any source data. Called per audio source before any other parameters are updated on sound sources.
- L467 _public function_ `virtual void OnAllSourcesProcessed()` — Called when all sources have finished processing.

#### class `UOcclusionPluginSourceSettingsBase`  
`class UOcclusionPluginSourceSettingsBase : public UObject`  
_L474-477_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This is a class which should be overridden to provide users with settings to use for individual sounds

#### class `IAudioOcclusionFactory`  
`class IAudioOcclusionFactory : public IAudioPluginFactory, public IModularFeature`  
_L483-513_
- inherits: `IAudioPluginFactory,IModularFeature`
- desc: /
- L487 _public prototype_ `virtual ~IAudioOcclusionFactory() = default;` — Virtual destructor
- L490 _public function_ `static FName GetModularFeatureName()` — IModularFeature
- L497 _public function_ `virtual FString GetDisplayName() override` — Begin IAudioPluginWithMetadata implementation
- L504 _public prototype_ `virtual TAudioOcclusionPtr CreateNewOcclusionPlugin(FAudioDevice* OwningDevice) = 0;`
- L509 _public function_ `virtual UClass* GetCustomOcclusionSettingsClass() const` — @return the UClass type of your settings for occlusion. This allows us to only pass in user settings for your plugin.

#### class `IAudioOcclusion`  
`class IAudioOcclusion`  
_L515-548_
- L519 _public prototype_ `virtual ~IAudioOcclusion() = default;` — Virtual destructor
- L522 _public function_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams)` — Initialize the occlusion plugin with the same rate and number of sources.
- L530 _public function_ `virtual void Shutdown()` — Shuts down the audio plugin.
- L535 _public function_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, UOcclusionPluginSourceSettingsBase* InSettings)` — Called when a source is assigned to a voice.
- L540 _public function_ `virtual void OnReleaseSource(const uint32 SourceId)` — Called when a source is done playing and is released.
- L545 _public function_ `virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)` — Processes audio with the given input and output data structs.

#### class `IAudioModulationFactory`  
`class IAudioModulationFactory : public IModularFeature`  
_L554-578_
- inherits: `IModularFeature`
- desc: /
- L558 _public prototype_ `virtual ~IAudioModulationFactory() = default;` — Virtual destructor
- L561 _public function_ `static FName GetModularFeatureName()` — IModularFeature
- L567 _public prototype_ `virtual const FName& GetDisplayName() const = 0;`
- L569 _public prototype_ `virtual TAudioModulationPtr CreateNewModulationPlugin(FAudioDevice* OwningDevice) = 0;`
- L574 _public function_ `virtual UClass* GetCustomModulationSettingsClass() const` — @return the UClass type of your settings for modulation. This allows us to only pass in user settings for your plugin.

#### class `UReverbPluginSourceSettingsBase`  
`class UReverbPluginSourceSettingsBase : public UObject`  
_L583-586_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This is a class which should be overridden to provide users with settings to use for individual sounds

#### class `IAudioReverbFactory`  
`class IAudioReverbFactory : public IAudioPluginFactory, public IModularFeature`  
_L588-618_
- inherits: `IAudioPluginFactory,IModularFeature`
- L592 _public prototype_ `virtual ~IAudioReverbFactory() = default;` — Virtual destructor
- L595 _public function_ `static FName GetModularFeatureName()` — IModularFeature
- L602 _public function_ `virtual FString GetDisplayName() override` — Begin IAudioPluginWithMetadata implementation
- L609 _public prototype_ `virtual TAudioReverbPtr CreateNewReverbPlugin(FAudioDevice* OwningDevice) = 0;`
- L614 _public function_ `virtual UClass* GetCustomReverbSettingsClass() const` — @return the UClass type of your settings for reverb. This allows us to only pass in user settings for your plugin.

#### class `IAudioReverb`  
`class IAudioReverb`  
_L620-664_
- L624 _public prototype_ `virtual ~IAudioReverb() = default;` — Virtual destructor
- L627 _public function_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams)` — Initialize the reverb plugin with the same rate and number of sources.
- L635 _public function_ `virtual void Shutdown()` — Shuts down the audio plugin.
- L639 _public function_ `virtual void OnDeviceShutdown(FAudioDevice* AudioDevice)`
- L644 _public prototype_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, UReverbPluginSourceSettingsBase* InSettings) = 0;` — Called when a source is assigned to a voice.
- L647 _public prototype_ `virtual void OnReleaseSource(const uint32 SourceId) = 0;` — Called when a source is done playing and is released.
- L650 _public prototype_ `virtual FSoundEffectSubmixPtr GetEffectSubmix() = 0;` — Returns the plugin-managed effect submix instance
- L652 _public function_ `virtual USoundSubmix* LoadSubmix()`
- L658 _public prototype_ `virtual USoundSubmix* GetSubmix() = 0;` — Returns the plugin-managed effect submix
- L661 _public function_ `virtual void ProcessSourceAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData)` — Processes audio with the given input and output data structs.

#### class `IAudioPluginListener`  
`class IAudioPluginListener`  
_L673-708_
- desc: /
- L676 _public prototype_ `virtual ~IAudioPluginListener() = default;`
- L678 _public function_ `virtual void OnDeviceShutdown(FAudioDevice* AudioDevice)`
- L685 _public function_ `virtual void OnListenerInitialize(FAudioDevice* AudioDevice, UWorld* ListenerWorld)` — This function is called when a game world initializes a listener with an audio device this IAudioPluginListener is registered to. Please note that it is possible to miss this event if you register this IAudioPluginListener after the listener is initialized.
- L690 _public function_ `virtual void OnTick(UWorld* InWorld, const int32 ViewportIndex, const FTransform& ListenerTransform, const float InDeltaSeconds)` — This is overridable for any actions a plugin manager may need to do on the game thread.
- L695 _public function_ `virtual void OnWorldChanged(FAudioDevice* AudioDevice, UWorld* InWorld)` — This is overridable for any actions a plugin manager may need to do on a level change.
- L700 _public function_ `virtual void OnListenerUpdated(FAudioDevice* AudioDevice, const int32 ViewportIndex, const FTransform& ListenerTransform, const float InDeltaSeconds)` — Called when the listener is updated on the given audio device.
- L705 _public function_ `virtual void OnListenerShutdown(FAudioDevice* AudioDevice)` — Called when the listener is shutdown.

#### Free symbols / members of external scopes

- L33 _macro_ `#define AUDIO_SPATIALIZATION_PLUGIN_LLM_SCOPE LLM_SCOPE_BYTAG(Audio_SpatializationPlugins);` — Convenience macro for Audio_SpatializationPlugins LLM scope to avoid misspells.
- L52 _typedef_ `using FSoundEffectSubmixPtr = TSharedPtr<FSoundEffectSubmix, ESPMode::ThreadSafe>;` — Deprecated in favor of TSoundEffectSubmixPtr
- L54 _typedef_ `using TSoundEffectPtr = TSharedPtr<FSoundEffectBase, ESPMode::ThreadSafe>;`
- L55 _typedef_ `using TSoundEffectSourcePtr = TSharedPtr<FSoundEffectSource, ESPMode::ThreadSafe>;`
- L56 _typedef_ `using TSoundEffectSubmixPtr = TSharedPtr<FSoundEffectSubmix, ESPMode::ThreadSafe>;`
- L57 _typedef_ `using TAudioSpatializationPtr = TSharedPtr<IAudioSpatialization, ESPMode::ThreadSafe>;`
- L58 _typedef_ `using TAudioSourceDataOverridePtr = TSharedPtr<IAudioSourceDataOverride, ESPMode::ThreadSafe>;`
- L59 _typedef_ `using TAudioModulationPtr = TSharedPtr<IAudioModulationManager, ESPMode::ThreadSafe>;`
- L60 _typedef_ `using TAudioOcclusionPtr = TSharedPtr<IAudioOcclusion, ESPMode::ThreadSafe>;`
- L61 _typedef_ `using TAudioReverbPtr = TSharedPtr<IAudioReverb, ESPMode::ThreadSafe>;`
- L62 _typedef_ `using TAudioPluginListenerPtr = TSharedPtr<IAudioPluginListener, ESPMode::ThreadSafe>;`

### `Source/Runtime/AudioExtensions/Public/IAudioModulation.h` (Public)


#### struct `Audio::FModulationParameter`  
`struct FModulationParameter`  
_L51-102_
- L53 _public prototype_ `FModulationParameter();`
- L54 _public prototype_ `FModulationParameter(const FModulationParameter& InParam) = default;`
- L55 _public prototype_ `FModulationParameter(FModulationParameter&& InParam) = default;`
- L57 _public prototype_ `FModulationParameter& operator=(FModulationParameter&& InParam) = default;`
- L58 _public prototype_ `FModulationParameter& operator=(const FModulationParameter& InParam) = default;`
- L60 _public member_ `FName ParameterName;`
- L63 _public member_ `float DefaultValue = 1.0f;` — Default value of parameter in unit space
- L66 _public member_ `float MinValue = 0.0f;` — Default minimum value of parameter in unit space
- L69 _public member_ `float MaxValue = 1.0f;` — Default minimum value of parameter in unit space
- L72 _public member_ `bool bRequiresConversion = false;` — Whether or not unit conversion is required
- L75 _public member_ `bool bClampToNormalizedRange = true;` — Whether or not to clamp normalized values to [0,1] when using this parameter.
- L77 _public member_ `uint32 TypeHash = INDEX_NONE;`
- L80 _public member_ `FText UnitDisplayName;`
- L82 _public member_ `FName ClassName;`
- L86 _public member_ `FModulationMixFunction MixFunction;` — Function used to mix normalized values together.
- L89 _public member_ `FModulationUnitConversionFunction UnitFunction;` — Function used to convert value buffer from normalized, unitless space [0.0f, 1.0f] to unit space.
- L92 _public member_ `FModulationNormalizedConversionFunction NormalizedFunction;` — Function used to convert value buffer from unit space to normalized, unitless [0.0f, 1.0f] space.
- L94 _public prototype_ `static const FModulationMixFunction& GetDefaultMixFunction();`
- L95 _public prototype_ `static const FModulationUnitConversionFunction& GetDefaultUnitConversionFunction();`
- L96 _public prototype_ `static const FModulationNormalizedConversionFunction& GetDefaultNormalizedConversionFunction();`

#### class `Audio::IModulatorSettings`  
`class IModulatorSettings`  
_L132-142_
- desc: Interface for cached off Modulator UObject data used as default settings to be converted to instanced proxy data per AudioDevice on the AudioRenderThread. If proxy is already active, implementation is expected to ignore register call and return existing modulator proxy's type Id & set parameter accordingly.
- L135 _public prototype_ `virtual ~IModulatorSettings() = default;`
- L136 _public prototype_ `virtual TUniquePtr<IModulatorSettings> Clone() const = 0;`
- L137 _public prototype_ `virtual FModulatorId GetModulatorId() const = 0;`
- L138 _public prototype_ `virtual const Audio::FModulationParameter& GetOutputParameter() const = 0;`
- L139 _public prototype_ `virtual Audio::FModulatorTypeId Register( Audio::FModulatorHandleId HandleId, IAudioModulationManager& InModulation) const = 0;`

#### struct `Audio::FModulatorHandle`  
`struct FModulatorHandle`  
_L147-189_
- desc: Handle to a modulator which interacts with the modulation API to manage lifetime of modulator proxy objects internal to modulation plugin implementation.
- L149 _public prototype_ `FModulatorHandle() = default;`
- L150 _public prototype_ `FModulatorHandle(Audio::FModulationParameter&& InParameter);`
- L151 _public prototype_ `FModulatorHandle(IAudioModulationManager& InModulation, const Audio::IModulatorSettings& InModulatorSettings, Audio::FModulationParameter&& InParameter);`
- L152 _public prototype_ `FModulatorHandle(const FModulatorHandle& InOther);`
- L153 _public prototype_ `FModulatorHandle(FModulatorHandle&& InOther);`
- L155 _public prototype_ `~FModulatorHandle();`
- L157 _public prototype_ `FModulatorHandle& operator=(const FModulatorHandle& InOther);`
- L158 _public prototype_ `FModulatorHandle& operator=(FModulatorHandle&& InOther);`
- L160 _public prototype_ `FModulatorId GetModulatorId() const;`
- L161 _public prototype_ `const FModulationParameter& GetParameter() const;`
- L162 _public prototype_ `FModulatorTypeId GetTypeId() const;`
- L163 _public prototype_ `FModulatorHandleId GetHandleId() const;`
- L164 _public prototype_ `bool GetValue(float& OutValue) const;`
- L165 _public prototype_ `bool GetValueThreadSafe(float& OutValue) const;`
- L166 _public prototype_ `bool IsValid() const;`
- L173 _public function_ `inline bool operator==(const FModulatorHandle& Other) const`
- L178 _public function_ `inline bool operator!=(const FModulatorHandle& Other) const`
- L184 _private member_ `FModulationParameter Parameter;`
- L185 _private member_ `FModulatorHandleId HandleId = (FModulatorHandleId)INDEX_NONE;`
- L186 _private member_ `FModulatorTypeId ModulatorTypeId = (FModulatorTypeId)INDEX_NONE;`
- L187 _private member_ `FModulatorId ModulatorId = (FModulatorId)INDEX_NONE;`
- L188 _private member_ `TWeakPtr<IAudioModulationManager> Modulation;`

#### class `IAudioModulationManager`  
`class IAudioModulationManager : public TSharedFromThis<IAudioModulationManager>`  
_L192-234_
- inherits: `TSharedFromThis<IAudioModulationManager>`
- L196 _public prototype_ `virtual ~IAudioModulationManager() = default;` — Virtual destructor
- L199 _public prototype_ `virtual void Initialize(const FAudioPluginInitializationParams& InitializationParams) = 0;` — Initialize the modulation plugin with the same rate and number of sources
- L201 _public prototype_ `virtual void OnAuditionEnd() = 0;`
- L203 _public prototype_ `virtual void GetControlBusAssetPath(TArray<FTopLevelAssetPath>& OutClassNames) = 0;`
- L207 _public prototype_ `virtual bool OnPostHelp(FCommonViewportClient* ViewportClient, const TCHAR* Stream) = 0;` — Request to post help from active plugin (non-shipping builds only)
- L210 _public prototype_ `virtual int32 OnRenderStat(FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const UFont& Font, const FVector* ViewLocation, const FRotator* ViewRotation) = 0;` — Render stats pertaining to modulation (non-shipping builds only)
- L213 _public prototype_ `virtual bool OnToggleStat(FCommonViewportClient* ViewportClient, const TCHAR* Stream) = 0;` — Toggle showing render stats pertaining to modulation (non-shipping builds only)
- L217 _public prototype_ `virtual void ProcessModulators(const double InElapsed) = 0;` — Processes all modulators Run on the audio render thread prior to processing audio
- L220 _public prototype_ `virtual void UpdateModulator(const USoundModulatorBase& InModulator) = 0;` — Updates modulator definition on the AudioRender Thread with that provided by the UObject representation
- L223 _protected prototype_ `virtual void RegisterModulator(uint32 InHandleId, Audio::FModulatorId InModulatorId) = 0;`
- L226 _protected prototype_ `virtual bool GetModulatorValue(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const = 0;` — Get the modulator value from the AudioRender Thread
- L229 _protected prototype_ `virtual bool GetModulatorValueThreadSafe(const Audio::FModulatorHandle& ModulatorHandle, float& OutValue) const = 0;` — Get the modulator value from any thread.
- L231 _protected prototype_ `virtual void UnregisterModulator(const Audio::FModulatorHandle& InHandle) = 0;`

#### class `USoundModulatorBase`  
`class USoundModulatorBase : public UObject, public IAudioProxyDataFactory`  
_L240-250_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject,IAudioProxyDataFactory`
- desc: Base class for all modulators
- L245 _public prototype_ `virtual const Audio::FModulationParameter& GetOutputParameter() const;`
- L247 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L249 _public prototype_ `virtual TUniquePtr<Audio::IModulatorSettings> CreateProxySettings() const;`

#### class `FSoundModulatorAssetProxy`  
`class FSoundModulatorAssetProxy : public Audio::TProxyData<FSoundModulatorAssetProxy>, public TSharedFromThis<FSoundModulatorAssetProxy, ESPMode::ThreadSafe>`  
_L255-289_
- inherits: `Audio::TProxyData<FSoundModulatorAssetProxy>,TSharedFromThis<FSoundModulatorAssetProxy,ESPMode::ThreadSafe>`
- desc: Proxy to modulator, allowing for modulator to be referenced by the Audio Render Thread independently from the implementing modulation plugin (ex. for MetaSound implementation).
- L258 _public prototype_ `IMPL_AUDIOPROXY_CLASS(FSoundModulatorAssetProxy);`
- L260 _public function_ `FSoundModulatorAssetProxy(const FSoundModulatorAssetProxy& InAssetProxy) : Parameter(InAssetProxy.Parameter) , ModulatorSettings(InAssetProxy.ModulatorSettings.IsValid() ? InAssetProxy.ModulatorSettings->Clone() : nullptr)`
- L266 _public function_ `FSoundModulatorAssetProxy(const USoundModulatorBase& InModulatorBase) : Parameter(InModulatorBase.GetOutputParameter()) , ModulatorSettings(InModulatorBase.CreateProxySettings())`
- L272 _public function_ `virtual Audio::FModulatorHandle CreateModulatorHandle(IAudioModulationManager& InModulation) const`
- L280 _public function_ `virtual Audio::FModulatorId GetModulatorId() const`
- L287 _protected member_ `Audio::FModulationParameter Parameter;`
- L288 _protected member_ `TUniquePtr<Audio::IModulatorSettings> ModulatorSettings;`

#### class `FSoundModulationParameterAssetProxy`  
`class FSoundModulationParameterAssetProxy : public Audio::TProxyData<FSoundModulationParameterAssetProxy>, public TSharedFromThis<FSoundModulationParameterAssetProxy, ESPMode::ThreadSafe>`  
_L295-307_
- inherits: `Audio::TProxyData<FSoundModulationParameterAssetProxy>,TSharedFromThis<FSoundModulationParameterAssetProxy,ESPMode::ThreadSafe>`
- desc: Proxy to modulator, allowing for modulator to be referenced by the Audio Render Thread independently from the implementing modulation plugin (ex. for MetaSound implementation).
- L298 _public prototype_ `IMPL_AUDIOPROXY_CLASS(FSoundModulationParameterAssetProxy);`
- L300 _public function_ `virtual const Audio::FModulationParameter& GetParameter() const`
- L306 _protected member_ `Audio::FModulationParameter Parameter;`

#### class `ISoundModulatable`  
`class ISoundModulatable`  
_L313-337_
- desc: Interface to sound that is modulatable, allowing for certain specific behaviors to be controlled on the sound level by the modulation system.
- L316 _public prototype_ `virtual ~ISoundModulatable() = default;`
- L321 _public prototype_ `virtual uint32 GetObjectId() const = 0;` — Gets the object definition id of the given playing sound's instance
- L326 _public prototype_ `virtual int32 GetPlayCount() const = 0;` — Returns number of actively instances of sound playing (including virtualized instances)
- L331 _public prototype_ `virtual bool IsPreviewSound() const = 0;` — Returns whether or not sound is an editor preview sound
- L336 _public prototype_ `virtual void Stop() = 0;` — Stops sound.

#### Free symbols / members of external scopes

- L40 _namespace_ `namespace Audio`
- L42 _typedef_ `using FModulatorId = uint32;` (scope `Audio`)
- L43 _typedef_ `using FModulatorTypeId = uint32;` (scope `Audio`)
- L44 _typedef_ `using FModulatorHandleId = uint32;` (scope `Audio`)
- L46 _typedef_ `using FModulationUnitConversionFunction = TFunction<void(float& )>;` (scope `Audio`)
- L47 _typedef_ `using FModulationNormalizedConversionFunction = TFunction<void(float& )>;` (scope `Audio`)
- L48 _typedef_ `using FModulationMixFunction = TFunction<void(float& , float )>;` (scope `Audio`)
- L98 _function_ `friend inline uint32 GetTypeHash(const FModulationParameter& InModulationParameter)` (scope `Audio`)
- L104 _prototype_ `bool IsModulationParameterRegistered(FName InName);` (scope `Audio`)
- L105 _prototype_ `void RegisterModulationParameter(FName InName, FModulationParameter&& InParameter);` (scope `Audio`)
- L106 _prototype_ `bool UnregisterModulationParameter(FName InName);` (scope `Audio`)
- L107 _prototype_ `void UnregisterAllModulationParameters();` (scope `Audio`)
- L108 _prototype_ `const FModulationParameter* GetModulationParameterPtr(FName InName);` (scope `Audio`)
- L109 _prototype_ `const FModulationParameter& GetDefaultModulationParameter();` (scope `Audio`)
- L112 _prototype_ `void SetModulationParameterClampOverride(FName InName, bool bClamp);` (scope `Audio`)
- L115 _prototype_ `void ClearModulationParameterClampOverride(FName InName);` (scope `Audio`)
- L118 _prototype_ `void ClearAllModulationParameterClampOverrides();` (scope `Audio`)
- L122 _prototype_ `bool GetModulationParameterClampValue(const FName& ParameterName, bool& bClampOut);` (scope `Audio`) — Returns false if parameter is not registered
- L125 _prototype_ `const FModulationParameter& GetModulationParameter(FName InName);` (scope `Audio`) — `UE_DEPRECATED(5.6, "Please use the version of GetModulationParameter which returns a pointer instead of a reference, and check that it is valid in your code.")`
- L168 _function_ `friend inline uint32 GetTypeHash(const FModulatorHandle& InModulatorHandle)` (scope `Audio`)
- L290 _typedef_ `using FSoundModulatorAssetProxyPtr = TSharedPtr<FSoundModulatorAssetProxy, ESPMode::ThreadSafe>;`
- L308 _typedef_ `using FSoundModulationParameterAssetProxyPtr = TSharedPtr<FSoundModulationParameterAssetProxy, ESPMode::ThreadSafe>;`

### `Source/Runtime/AudioExtensions/Public/IAudioParameterInterfaceRegistry.h` (Public)


#### struct `Audio::FParameterInterface`  
`struct FParameterInterface`  
_L29-187_
- desc: Interface for parameterizing data provided to or coming from an executable audio unit (ex. Sound like a MetaSoundSource, arbitrary DSP graph like a MetaSoundPatch, etc.). Can be used generically for processing either logically at a control or Game Thread tick rate (ex. SoundCues), or by an underlying DSP operation via the Audio Render Thread or delegated task (ex. MetaSounds, custom SoundGenerator, etc.)
- L137 _public prototype_ `FParameterInterface() = default;`
- L140 _public prototype_ `FParameterInterface(FName InName, const FVersion& InVersion);` — Constructor used for parameter interface not limited to any particular UClass types
- L143 _public prototype_ `FParameterInterface(FName InName, const FVersion& InVersion, const UClass& InClass);` — `UE_DEPRECATED(5.3, "Set UClassOptions to determine what options apply for a given UClass (if any).")`
- L146 _public prototype_ `FName GetName() const;` — Returns name of interface
- L149 _public prototype_ `const FVersion& GetVersion() const;` — Returns version of interface
- L152 _public prototype_ `const UClass& GetType() const;` — `UE_DEPRECATED(5.3, "Use FParameterInterface::FindSupportedUClasses instead")`
- L154 _public prototype_ `TArray<const UClass*> FindSupportedUClasses() const;`
- L158 _public prototype_ `const TArray<FClassOptions>& GetUClassOptions() const;` — If specified, options used to restrict a corresponding UClass that interface may be applied to.  If unspecified, interface is assumed to be applicable to any arbitrary UClass.
- L161 _public prototype_ `const TArray<FInput>& GetInputs() const;` — Returns read-only array of inputs
- L164 _public prototype_ `const TArray<FOutput>& GetOutputs() const;` — Returns read-only array of outputs
- L167 _public prototype_ `const TArray<FEnvironmentVariable>& GetEnvironment() const;` — Returns read-only array of environment variables
- L171 _public prototype_ `const FText& GetDescription() const;` — Description to be displayed in editor or tools
- L175 _private member_ `FName NamePrivate;`
- L176 _private member_ `FVersion VersionPrivate;`
- L179 _protected member_ `TArray<FInput> Inputs;`
- L180 _protected member_ `TArray<FOutput> Outputs;`
- L181 _protected member_ `TArray<FEnvironmentVariable> Environment;`
- L182 _protected member_ `TArray<FClassOptions> UClassOptions;`
- L185 _protected member_ `FText Description;`

#### struct `Audio::FParameterInterface::FVersion`  
`struct FVersion`  
_L32-36_
- desc: Version of interface (higher numbers are more recent)
- L34 _public member_ `const int32 Major = 1;`
- L35 _public member_ `const int32 Minor = 0;`

#### struct `Audio::FParameterInterface::FInput`  
`struct FInput`  
_L39-66_
- desc: Input of interface
- L42 _public member_ `const FText DisplayName;` — Name to be displayed in editor or tools
- L45 _public member_ `const FText Description;` — Description to be displayed in editor or tools
- L53 _public member_ `const FName DataType;` — FName describing the type of the data.  May be interpreted solely by a plugin or implementation (ex. MetaSounds).  If blank, type is assumed to be that described by the InitValue AudioParameter's corresponding ParamType. If provided, DataType must be constructible using the InitValue.
- L56 _public member_ `const FAudioParameter InitValue;` — Initial value of the given parameter
- L61 _public member_ `const FText RequiredText;` — Text to display in the editor or tools if the consuming system of the given input parameter is not implemented (to avoid passing data using the parameter system when not operated on).
- L65 _public member_ `const int32 SortOrderIndex = 0;` — Visual sort order of the given input with respect to other inputs either within the given interface or listed among other unrelated inputs.

#### struct `Audio::FParameterInterface::FOutput`  
`struct FOutput`  
_L69-97_
- desc: Output of interface
- L72 _public member_ `const FText DisplayName;` — Name to be displayed in editor or tools
- L75 _public member_ `const FText Description;` — Description to be displayed in editor or tools
- L81 _public member_ `const FName DataType;` — FName describing the type of the data.  May be interpreted solely by a plugin or implementation (ex. MetaSounds).  If blank, type is assumed to be that described by ParamType.
- L84 _public member_ `const FName ParamName;` — Name of output parameter used as a runtime identifier
- L89 _public member_ `const FText RequiredText = FText();` — Text to display in the editor or tools if the consuming system of the given input parameter is not implemented (to avoid passing data using the parameter system when not operated on).
- L92 _public member_ `const EAudioParameterType ParamType = EAudioParameterType::None;` — Type of output parameter used as a runtime identifier if unspecified by the DataType.
- L96 _public member_ `const int32 SortOrderIndex = 0;` — Visual sort order of the given input with respect to other outputs either within the given interface or listed among other unrelated outputs.

#### struct `Audio::FParameterInterface::FEnvironmentVariable`  
`struct FEnvironmentVariable`  
_L101-120_
- desc: Read-only variable that cannot be modified by the sound instance, and maybe shared amongst instances.
- L104 _public member_ `const FText DisplayName;` — Name to be displayed in editor or tools
- L107 _public member_ `const FText Description;` — Description to be displayed in editor or tools
- L113 _public member_ `const FName DataType;` — FName describing the type of the data.  May be interpreted solely by a plugin or implementation (ex. MetaSounds).  If blank, type is assumed to be that described by ParamType.
- L116 _public member_ `const FName ParamName;` — Name of variable used as a runtime identifier
- L119 _public member_ `const EAudioParameterType ParamType = EAudioParameterType::None;` — Type of variable used as a runtime identifier if unspecified by the DataType.

#### struct `Audio::FParameterInterface::FClassOptions`  
`struct FClassOptions`  
_L123-135_
- desc: Options used to restrict a corresponding UClass that interface may be applied to.
- L126 _public member_ `const FTopLevelAssetPath ClassPath;` — Path to restricted UClass
- L130 _public member_ `const bool bIsModifiable = true;` — Whether or not the class may be directly modifiable on an asset implementing the given interface (added, removed, etc.)
- L134 _public member_ `const bool bIsDefault = false;` — Whether or not the interface should be immediately added to the given class type on creation.

#### class `Audio::IAudioParameterInterfaceRegistry`  
`class IAudioParameterInterfaceRegistry`  
_L193-214_
- desc: Registry of engine-defined audio parameter interfaces, used to parameterize data provided to or coming from an executable audio unit (ex. Sound like a MetaSoundSource, arbitrary DSP graph like a MetaSoundPatch, etc.).
- L195 _private member_ `static TUniquePtr<IAudioParameterInterfaceRegistry> Instance;`
- L198 _public prototype_ `static IAudioParameterInterfaceRegistry& Get();`
- L200 _public prototype_ `virtual ~IAudioParameterInterfaceRegistry() = default;`
- L203 _public prototype_ `virtual void IterateInterfaces(TFunction<void(FParameterInterfacePtr)> InFunction) const = 0;` — Iterate all registered interfaces
- L206 _public prototype_ `virtual void OnRegistration(TUniqueFunction<void(FParameterInterfacePtr)>&& InFunction) = 0;` — Execute a given function when an interface is registered
- L209 _public prototype_ `virtual void RegisterInterface(FParameterInterfacePtr InInterface) = 0;` — Registers an interface
- L212 _protected member_ `TSet<FParameterInterfacePtr> Interfaces;`
- L213 _protected member_ `TUniqueFunction<void(FParameterInterfacePtr)> RegistrationFunction;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Audio`
- L188 _typedef_ `using FParameterInterfacePtr = TSharedPtr<FParameterInterface, ESPMode::ThreadSafe>;` (scope `Audio`)

### `Source/Runtime/AudioExtensions/Public/IAudioParameterTransmitter.h` (Public)


#### struct `Audio::FParameterTransmitterInitParams`  
`struct FParameterTransmitterInitParams`  
_L21-34_
- desc: Data passed to CreateParameterTransmitter.
- L24 _public member_ `uint64 InstanceID = uint64(INDEX_NONE);` — Unique ID for this audio instance.
- L27 _public member_ `float SampleRate = 0.0f;` — Audio sample rate.
- L29 _public member_ `TArray<FAudioParameter> DefaultParams;`
- L32 _public member_ `DeviceID AudioDeviceID = DeviceID(INDEX_NONE);` — Audio device ID

#### class `Audio::ILegacyParameterTransmitter`  
`class ILegacyParameterTransmitter`  
_L42-51_
- desc: Reference collector functionality for legacy parameter system (i.e. backwards compatibility with the SoundCue system). None of this should be used by future assets supporting parameters (ex. MetaSounds) as object pointers within parameters should NOT be cached on threads other than the GameThread, utilizing a proxy methodology like MetaSounds that copies UObject data when and where necessary.
- L45 _public prototype_ `virtual ~ILegacyParameterTransmitter() = default;`
- L48 _public prototype_ `virtual TArray<const TObjectPtr<UObject>*> GetReferencedObjects() const;` — `UE_DEPRECATED(5.6, "Use AddReferencedObjects(...) instead")`
- L50 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector);`

#### class `Audio::IParameterTransmitter`  
`class IParameterTransmitter : public ILegacyParameterTransmitter`  
_L57-90_
- inherits: `ILegacyParameterTransmitter`
- desc: Interface for a audio instance transmitter. An audio instance transmitter ushers control parameters to a single audio object instance.
- L60 _public member_ `static const FName RouterName;`
- L62 _public prototype_ `virtual ~IParameterTransmitter() = default;`
- L65 _public function_ `virtual void ResetParameters()` — Reset parameters which stored on the transmitter.
- L69 _public function_ `virtual void OnDeleteActiveSound()` — Called when the active sound is deleted due to the sound finishing, being stopped, or being virtualized.
- L73 _public prototype_ `virtual bool GetParameter(FName InName, FAudioParameter& OutParam) const = 0;` — Return the cached parameter with the given name if it exists @return False if param not found, true if found.
- L77 _public prototype_ `virtual const TArray<FAudioParameter>& GetParameters() const = 0;` — `UE_DEPRECATED(5.6, "Access to internal parameters is no longer supported")` — Return reference to the cached parameter array.
- L79 _public prototype_ `virtual void CopyParameters(TArray<FAudioParameter>& OutParameters) const = 0;`
- L82 _public prototype_ `virtual bool SetParameters(TArray<FAudioParameter>&& InParameters) = 0;` — Parameter Setters
- L85 _public function_ `virtual void OnVirtualizeActiveSound()` — Called when the active sound is virtualized
- L89 _public function_ `virtual void OnRealizeVirtualizedActiveSound(TArray<FAudioParameter>&& InParameters)` — Called when the virtualized active sound is realized @param Parameters to set

#### class `Audio::FParameterTransmitterBase`  
`class FParameterTransmitterBase : public IParameterTransmitter`  
_L95-126_
- inherits: `IParameterTransmitter`
- desc: Base implementation for the parameter transmitter, which caches parameters and provides implementer to add additional logic to route parameter data accordingly.
- L98 _public prototype_ `FParameterTransmitterBase(TArray<FAudioParameter> InDefaultParams);`
- L99 _public prototype_ `virtual ~FParameterTransmitterBase();`
- L101 _public prototype_ `virtual bool GetParameter(FName InName, FAudioParameter& OutParam) const override;`
- L102 _public prototype_ `virtual void ResetParameters() override;`
- L105 _public prototype_ `virtual const TArray<FAudioParameter>& GetParameters() const override;` — `UE_DEPRECATED(5.6, "Access to internal parameter storage is no longer supported. Use CopyParameters(...) instead")`
- L107 _public prototype_ `virtual void CopyParameters(TArray<FAudioParameter>& OutParameters) const override;`
- L109 _public prototype_ `virtual bool SetParameters(TArray<FAudioParameter>&& InParameters) override;`
- L111 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L113 _public prototype_ `virtual void OnVirtualizeActiveSound() override;`
- L114 _public prototype_ `virtual void OnRealizeVirtualizedActiveSound(TArray<FAudioParameter>&& InParameters);`
- L115 _public prototype_ `bool IsVirtualized() const;`
- L119 _protected prototype_ `void AddReferencedObjectsFromParameters(FReferenceCollector& InCollector, TArrayView<FAudioParameter> InParameters) const;`
- L122 _protected member_ `TArray<FAudioParameter> AudioParameters;` — `UE_DEPRECATED(5.6, "Subclasses of FParameterTransmitterBase should not access AudioParameters member directly. These will be moved to private visibility soon.")`
- L124 _protected member_ `bool bIsVirtualized;` — `UE_DEPRECATED(5.6, "Subclasses of FParameterTransmitterBase should not access bIsVirtualized member directly. These will be moved to private visibility soon.")`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Audio`
- L18 _typedef_ `using DeviceID = uint32;` (scope `Audio`)

### `Source/Runtime/AudioExtensions/Public/IAudioPropertiesDetailsInjector.h` (Public)


#### class `IAudioPropertiesDetailsInjector`  
`class IAudioPropertiesDetailsInjector : public TSharedFromThis<IAudioPropertiesDetailsInjector>`  
_L19-27_
- inherits: `TSharedFromThis<IAudioPropertiesDetailsInjector>`
- L22 _public prototype_ `virtual ~IAudioPropertiesDetailsInjector();`
- L24 _public prototype_ `virtual void CustomizeInjectedPropertiesDetails(IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> PropertySheetPropertyHandle) = 0;`
- L25 _public prototype_ `virtual void BindDetailCustomizationToPropertySheetChanges(IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> PropertySheetPropertyHandle) = 0;`
- L26 _public prototype_ `virtual void UnbindFromPropertySheetChanges() = 0;`

#### class `IAudioPropertiesDetailsInjectorBuilder`  
`class IAudioPropertiesDetailsInjectorBuilder : public TSharedFromThis<IAudioPropertiesDetailsInjectorBuilder>, public IModularFeature`  
_L29-35_
- inherits: `TSharedFromThis<IAudioPropertiesDetailsInjectorBuilder>,IModularFeature`
- L32 _public prototype_ `virtual ~IAudioPropertiesDetailsInjectorBuilder();`
- L34 _public prototype_ `virtual IAudioPropertiesDetailsInjector* CreateAudioPropertiesDetailsInjector() = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOEXTENSIONS_API`
- L13 _namespace_ `namespace AudioPropertiesDetailsInjector`
- L15 _variable_ `static const FLazyName BuilderModularFeatureName = TEXT("Aud` (scope `AudioPropertiesDetailsInjector`)

### `Source/Runtime/AudioExtensions/Public/IAudioProxyInitializer.h` (Public)


#### class `TDataSnapshot`  
`template <typename T> class TDataSnapshot`  
_L21-85_
- L24 _public prototype_ `TDataSnapshot() = delete;`
- L26 _public function_ `TDataSnapshot(TWeakPtr<const TDataSnapshotProducer<T>> InWeakProducer, TSharedPtr<T> InPublishedData) : WeakProducer(InWeakProducer) , DataSnapshot(InPublishedData)`
- L31 _public function_ `operator TSharedPtr<T>() const`
- L36 _public function_ `bool IsValid() const`
- L41 _public function_ `explicit operator bool() const`
- L46 _public function_ `T* operator->() const`
- L51 _public function_ `bool IsUpdateAvailable() const`
- L61 _public function_ `bool GetLatest()`
- L83 _private member_ `TWeakPtr<const TDataSnapshotProducer<T>> WeakProducer;`
- L84 _private member_ `TSharedPtr<T> DataSnapshot;`

#### class `TDataSnapshotProducer`  
`template <typename T> class TDataSnapshotProducer : public TSharedFromThis<TDataSnapshotProducer<T>>`  
_L88-156_
- inherits: `TSharedFromThis<TDataSnapshotProducer<T>>`
- L91 _public function_ `operator TSharedPtr<T>() const`
- L96 _public function_ `bool IsValid() const`
- L101 _public function_ `explicit operator bool() const`
- L106 _public function_ `T* operator->() const`
- L111 _public function_ `void Fork()`
- L120 _public function_ `void Publish()` — note: there are still some things the USoundWave will potentially update on existing proxies (i.e. certain flags). Letting these pointers alias after "Publish()" is intentional for now.
- L126 _public function_ `TDataSnapshot<T> GetSnapshot() const`
- L131 _public function_ `bool IsSnapshotUpdateAvailable(const TSharedPtr<T>& InSnapshot) const`
- L145 _private function_ `TSharedPtr<T> GetData() const`
- L151 _private member_ `TSharedPtr<T> PublishedData;`
- L152 _private member_ `TSharedPtr<T> WorkingData = MakeShared<T>();`
- L153 _private member_ `mutable FRWLock DataLock;`

#### class `Audio::IProxyData`  
`class IProxyData : public IUnknown`  
_L195-244_
- inherits: `IUnknown`
- desc: Base class that allows us to typecheck proxy data before downcasting it in debug builds.
- L198 _private member_ `FName ProxyTypeName;`
- L200 _public prototype_ `virtual ~IProxyData() = default;`
- L204 _public function_ `virtual void* QueryInterface(const FName InterfaceId) override`
- L209 _public function_ `FName GetProxyTypeName() const`
- L215 _public function_ `template<typename ProxyType> ProxyType& GetAs()`
- L224 _public function_ `template<typename ProxyType> const ProxyType& GetAs() const`
- L233 _public function_ `template<typename ProxyType> bool CheckTypeCast() const`
- L238 _public function_ `IProxyData(FName InProxyTypeName) : ProxyTypeName(InProxyTypeName)`
- L243 _public function_ `virtual TUniquePtr<IProxyData> Clone() const` — `UE_DEPRECATED(5.2, "Proxy data is stored in a TSharedPtr<> and no longer requires cloning")`

#### class `Audio::TProxyData`  
`template <typename Type> class TProxyData : public IProxyData`  
_L251-262_
- inherits: `IProxyData`
- desc: This class can be implemented to create a custom, threadsafe instance of a given UObject. This is a CRTP class, and should always be subclassed with the name of the subclass.
- L254 _protected member_ `static constexpr bool bWasAudioProxyClassImplemented = false;`
- L257 _public function_ `TProxyData() : IProxyData(Type::GetAudioProxyTypeName())`

#### struct `Audio::FProxyDataInitParams`  
`struct FProxyDataInitParams`  
_L264-267_
- L266 _public member_ `FName NameOfFeatureRequestingProxy;`

#### class `IAudioProxyDataFactory`  
`class IAudioProxyDataFactory`  
_L273-280_
- desc: This can be subclassed to make a UClass an audio proxy factory.
- L277 _public prototype_ `virtual TUniquePtr<Audio::IProxyData> CreateNewProxyData(const Audio::FProxyDataInitParams& InitParams);` — `UE_DEPRECATED(5.2, "Call TSharedPtr<Audio::IProxyData> CreateProxyData(...) instead of a TUniquePtr<Audio::IProxyData> CreateNewProxyData(...).")`
- L279 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams);`

#### Free symbols / members of external scopes

- L166 _macro_ `#define IMPL_AUDIOPROXY_CLASS(FClassName) \`
- L186 _namespace_ `namespace Audio`
- L190 _typedef_ `using IProxyDataPtr UE_DEPRECATED(5.2, "Replace IProxyDataPtr with TSharedP` (scope `Audio`)
- L282 _namespace_ `namespace Audio`
- L285 _function_ `template <typename UClassToUse> IAudioProxyDataFactory* CastToProxyDataFactory(UObject* InObject)` (scope `Audio`)

### `Source/Runtime/AudioExtensions/Public/ISoundWaveCloudStreaming.h` (Public)


#### class `Audio::ISoundWaveCloudStreamingFeature`  
`class ISoundWaveCloudStreamingFeature : public IModularFeature`  
_L21-42_
- inherits: `IModularFeature`
- L24 _public function_ `static FName GetModularFeatureName()`
- L25 _public prototype_ `virtual ~ISoundWaveCloudStreamingFeature() = default;`
- L28 _public prototype_ `virtual FGuid GetPluginGUID() const = 0;` — Returns the GUID of this plugin.
- L31 _public prototype_ `virtual bool CanOverrideFormat(const USoundWave* InWaveToOverride) = 0;` — Checks if the given sound wave can be turned into cloud streamable.
- L34 _public prototype_ `virtual FName GetOverrideFormatName(const USoundWave* InWaveToOverride) = 0;` — Gets the format name to use when overriding the given sound wave for cloud streaming.
- L37 _public prototype_ `virtual FString GetOverrideParameterDDCHash(const USoundWave* InWaveToOverride) = 0;` — Gets a hash of the parameters for the DDC.
- L40 _public prototype_ `virtual bool AddCustomizationCloudStreamingPlatformDetails(IDetailLayoutBuilder& InDetailLayoutBuilder) = 0;` — Add editor customization for an instance.

#### enum `ESoundWaveCloudStreamingPlatformProjectEnableType`  
`enum class ESoundWaveCloudStreamingPlatformProjectEnableType : uint8`  
_L49-56_
- reflection: `UENUM()`
- desc: Platform specific enabling of Sound Wave cloud streaming.
- L52 _public enumerator_ `Enabled` — Enabled for this platform.
- L55 _public enumerator_ `Disabled` — Disabled for this platform.

#### struct `FSoundWaveCloudStreamingPlatformProjectSettings`  
`struct FSoundWaveCloudStreamingPlatformProjectSettings`  
_L60-77_
- reflection: `USTRUCT()`
- desc: Platform specific settings for Sound Wave cloud streaming.
- L64 _public function_ `FSoundWaveCloudStreamingPlatformProjectSettings()`
- L69 _public function_ `bool IsDefault() const`
- L76 _public member_ `ESoundWaveCloudStreamingPlatformProjectEnableType EnablementSetting;` — `UPROPERTY(EditAnywhere, Category = Platforms)` — Overrides whether to use cloud streaming on this platform.

#### enum `ESoundWaveCloudStreamingPlatformEnableType`  
`enum class ESoundWaveCloudStreamingPlatformEnableType : uint8`  
_L83-93_
- reflection: `UENUM()`
- desc: Platform specific enabling of Sound Wave cloud streaming.
- L86 _public enumerator_ `Inherited` — Use Sound Wave setting.
- L89 _public enumerator_ `Disabled` — Disables Sound Wave cloud streaming for this platform.
- L92 _public enumerator_ `SWC_MultipleValues UMETA(Hidden, DisplayName="Multiple values")` — Used in Slate widget configuration to indicate multiple selected objects have different values.

#### struct `FSoundWaveCloudStreamingPlatformSettings`  
`struct FSoundWaveCloudStreamingPlatformSettings`  
_L97-114_
- reflection: `USTRUCT()`
- desc: Platform specific settings for Sound Wave cloud streaming.
- L101 _public function_ `FSoundWaveCloudStreamingPlatformSettings()`
- L106 _public function_ `bool IsDefault() const`
- L113 _public member_ `ESoundWaveCloudStreamingPlatformEnableType EnablementSetting;` — `UPROPERTY(EditAnywhere, Category = Platforms)` — Overrides whether to use cloud streaming on this platform.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Audio`

### `Source/Runtime/AudioExtensions/Public/ISoundfieldEndpoint.h` (Public)


#### class `ISoundfieldEndpointSettingsProxy`  
`class ISoundfieldEndpointSettingsProxy`  
_L40-44_
- desc: This interface should be used to provide a non-uclass version of the data described in your implementation of USoundfieldEndpointSettingsBase.
- L43 _public prototype_ `virtual ~ISoundfieldEndpointSettingsProxy() = default;`

#### class `USoundfieldEndpointSettingsBase`  
`class USoundfieldEndpointSettingsBase : public UObject`  
_L51-57_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This opaque class should be used for specifying settings for how audio should be send to an external endpoint.
- L56 _public prototype_ `virtual TUniquePtr<ISoundfieldEndpointSettingsProxy> GetProxy() const PURE_VIRTUAL(USoundfieldEndpointSettingsBase::GetProxy, return nullptr;);`

#### class `ISoundfieldEndpoint`  
`class ISoundfieldEndpoint`  
_L63-158_
- desc: Class that allows soundfield-encoded audio to be sent to an arbitrary locale. For endpoint types that support receiving our downmixed interleaved audio data directly, implement IAudioEndpoint instead.
- L69 _public prototype_ `ISoundfieldEndpoint(int32 NumRenderCallbacksToBuffer);` — @param [NumRenderCallbacksToBuffer] Maximum number of ISoundfieldPackets that should be buffered.
- L71 _public prototype_ `virtual ~ISoundfieldEndpoint() = default;`
- L76 _public prototype_ `bool PushAudio(TUniquePtr<ISoundfieldAudioPacket>&& InPacket);` — Push a soundfield packet to the buffer.
- L83 _public prototype_ `void SetNewSettings(TUniquePtr<ISoundfieldEndpointSettingsProxy>&& InNewSettings);` — Post new settings for this endpoint. There is no type safety on this call, so make sure that you are using the correct implementation of IAudioEndpointSettingsProxy for this implementation of IAudioEndpoint.
- L86 _public prototype_ `int32 GetNumPacketsBuffer();` — Returns the amount of ISoundfieldAudioPackets currently buffered for this endpoint.
- L89 _public prototype_ `int32 GetRemainderInPacketBuffer();` — Returns the amount of ISoundfieldAudioPackets that can be buffered for this endpoint before reaching capacity.
- L94 _public prototype_ `void ProcessAudioIfNecessary();` — If this endpoint hasn't created it's own async callback thread but still requires an explicit callback, this should be called.
- L104 _protected function_ `virtual bool EndpointRequiresCallback() const` — For endpoints that do not explicitly fire a timed callback to poll audio data, this should be overridden to return true, and  OnAudioCallback and GetDesiredCallbackFrequency should be overridden.
- L109 _protected function_ `virtual float GetDesiredCallbackPeriodicity() const` — For endpoints that return true for EndpointRequiresCallback, this should return the duration between OnAudioCallback calls in seconds.
- L117 _protected function_ `virtual void OnAudioCallback(TUniquePtr<ISoundfieldAudioPacket>&& InPacket, const ISoundfieldEndpointSettingsProxy* InSettings)` — For endpoints that override EndpointRequiresCallback to return true, this callback will be called every (GetDesiredNumFrames() / GetSampleRate()) seconds. @param [in] InPacket the next buffer of audio. Can be nullptr if PushAudio hasn't been called in a while and the buffer is starved. @param [in] InSettings is the most recent soundfield settings for this endpoint. Can be null.
- L127 _protected prototype_ `TUniquePtr<ISoundfieldAudioPacket> PopAudio();` — This is used by the IAudioEndpoint implementation to poll buffered audio to process or send to the endpoint. Note that this is NOT thread safe if EndpointRequiresCallback() is overridden to return true. If that is the case, use an override of OnAudioCallback instead.
- L136 _protected prototype_ `void PollSettings(TFunctionRef<void(const ISoundfieldEndpointSettingsProxy*)> SettingsCallback);` — Use this as a thread safe way to use the current settings posted to this IAudioEndpoint. Locks with IAudioEndpoint::SetSettings. @param[in] NewSettingsRetrieved lambda used to work with the retrieved settings. This lambda is called immediately and synchronously, but is used to safely scope usage of the IAudioEndpointSettingsProxy pointer. Note that the resulting ISoundfieldEndpointSettingsProxy can be null.
- L141 _protected prototype_ `void StartRunningCallback();` — If EndpointRequiresCallback() returns true, this will be used to spawn an async thread and begin calling OnAudioCallback.
- L142 _protected prototype_ `void StopRunningCallback();`
- L144 _protected prototype_ `void RunCallbackSynchronously();`
- L148 _private member_ `TUniquePtr<Audio::FMixerNullCallback> RenderCallback;` — Owns a scoped thread and runs OnAudioCallback when StartRunningCallback() is called.
- L151 _private member_ `TArray<TUniquePtr<ISoundfieldAudioPacket>> AudioPacketBuffer;` — This array is used as a non-copying circular buffer for ISoundfieldAudioPackets.
- L152 _private member_ `FThreadSafeCounter ReadCounter;`
- L153 _private member_ `FThreadSafeCounter WriteCounter;`
- L156 _private member_ `TUniquePtr<ISoundfieldEndpointSettingsProxy> CurrentSettings;` — Owns the current settings for this endpoint.
- L157 _private member_ `FCriticalSection CurrentSettingsCriticalSection;`

#### class `ISoundfieldEndpointFactory`  
`class ISoundfieldEndpointFactory : public ISoundfieldFactory`  
_L167-252_
- inherits: `ISoundfieldFactory`
- desc: This factory is used to expose Soundfield Endpoint types to the editor. Once a factory is constructed and RegisterEndpointType is called, it will be exposed as a type of endpoint That a submix in the submix graph could be constructed with. Also note that an implementation of ISoundfieldDecoder is not necessary for soundfield formats that are only used for soundfield endpoints.
- L171 _public prototype_ `virtual ~ISoundfieldEndpointFactory() = default;` — Virtual destructor
- L174 _public prototype_ `virtual FName GetEndpointTypeName() = 0;` — Get the name for the endpoint type that this factory produces.
- L177 _public function_ `static FName GetModularFeatureName()` — This is the FName used to register Soundfield Endpoint factories with the modular feature system.
- L187 _public function_ `static void RegisterEndpointType(ISoundfieldEndpointFactory* InFactory)` — This needs to be called to make a soundfield format usable by the engine. It can be called from a ISoundfieldFactory subclass' constructor
- L196 _public function_ `static void UnregisterEndpointType(ISoundfieldEndpointFactory* InFactory)` — This needs to be called it an implementation of ISoundfieldFactory is about to be destroyed. It can be called from the destructor of an implementation of ISoundfieldFactory.
- L204 _public prototype_ `static ISoundfieldEndpointFactory* Get(const FName& InName);` — Get a registered endpoint factory by name.
- L206 _public prototype_ `static TArray<FName> GetAllSoundfieldEndpointTypes();`
- L213 _public prototype_ `static FName DefaultSoundfieldEndpointName();` — This is the default name used when a user creates a soundfield endpoint submix. Soundfied Endpoint submixes with this type will send their audio to the default output with no encoding.
- L216 _public prototype_ `TUniquePtr<ISoundfieldDecoderStream> CreateDecoderStream(const FAudioPluginInitializationParams& InitInfo, const ISoundfieldEncodingSettingsProxy& InitialSettings) override;` — This function is not necessary to override, since audio sent to an endpoint does not need to be decoded to interleaved audio buffers.
- L232 _public prototype_ `virtual TUniquePtr<ISoundfieldEndpoint> CreateNewEndpointInstance(const FAudioPluginInitializationParams& InitInfo, const ISoundfieldEndpointSettingsProxy& InitialSettings) = 0;` — Called for every new endpoint submix created with this factory's endpoint type.
- L238 _public function_ `virtual UClass* GetCustomEndpointSettingsClass() const` — Should return the StaticClass of this factory's implementation of USoundfieldEndpointSettingsBase.
- L246 _public prototype_ `virtual USoundfieldEndpointSettingsBase* GetDefaultEndpointSettings() = 0;` — return the settings an endpoint should use if a soundfield endpoint submix did not have their settings specified.
- L248 _public function_ `bool IsEndpointFormat() override`
- L250 _public prototype_ `virtual FName GetSoundfieldFormatName() override;`
- L251 _public prototype_ `virtual bool CanTranscodeToSoundfieldFormat(FName DestinationFormat, const ISoundfieldEncodingSettingsProxy& DestinationEncodingSettings) override;`

### `Source/Runtime/AudioExtensions/Public/ISoundfieldFormat.h` (Public)


#### struct `Audio::FChannelPositionInfo`  
`struct FChannelPositionInfo`  
_L60-76_
- L62 _public member_ `EAudioMixerChannel::Type Channel = EAudioMixerChannel::DefaultChannel;`
- L67 _public member_ `float Azimuth = 0.0f;` — Horizontal angle of the position of this channel, in radians. Increases as the channel moves clockwise about the listener. Goes from -PI to PI.
- L71 _public member_ `float Elevation = 0.0f;` — Vertical angle of the position of this channel, in radians. Increases as the height of the channel increases proportional to the channel's distance from the listener. Goes from -PI to PI.
- L75 _public member_ `float Radius = 1.0f;` — distance from the listener. By default, channels are typically on the unit sphere and have a radius of 1.0f. For spatialized inputs, this radius will be expressed in Unreal Units.

#### class `ISoundfieldEncodingSettingsProxy`  
`class ISoundfieldEncodingSettingsProxy`  
_L103-116_
- desc: This interface should be used to provide a non-uclass version of the data described in your implementation of USoundfieldEncodingSettingsBase. We will then pass this proxy object to the soundfield stream classes.
- L106 _public prototype_ `virtual ~ISoundfieldEncodingSettingsProxy() = default;`
- L112 _public prototype_ `virtual uint32 GetUniqueId() const = 0;` — This should return a unique This is used so that we don't call the same encode operation multiple times for a single source being sent to identical submixes.
- L115 _public prototype_ `virtual TUniquePtr<ISoundfieldEncodingSettingsProxy> Duplicate() const = 0;` — This should return a new, identical encoding settings.

#### class `USoundfieldEncodingSettingsBase`  
`class USoundfieldEncodingSettingsBase : public UObject`  
_L123-129_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This opaque class should be used for specifying settings for how audio should be encoded to your soundfield format for a given submix or file.
- L128 _public prototype_ `virtual TUniquePtr<ISoundfieldEncodingSettingsProxy> GetProxy() const PURE_VIRTUAL(USoundfieldEncodingSettingsBase::GetProxy, return nullptr;);`

#### class `ISoundfieldAudioPacket`  
`class ISoundfieldAudioPacket`  
_L136-155_
- desc: This interface represents all encoded soundfield audio from a single render callback.
- L139 _public prototype_ `virtual ~ISoundfieldAudioPacket() = default;`
- L144 _public prototype_ `virtual void Serialize(FArchive& Ar) = 0;` — Read or write this packet to a byte buffer.
- L149 _public prototype_ `virtual TUniquePtr<ISoundfieldAudioPacket> Duplicate() const = 0;` — Create a new version of this packet.
- L154 _public prototype_ `virtual void Reset() = 0;` — Zero out the contents of this packet.

#### struct `FSoundfieldSpeakerPositionalData`  
`struct FSoundfieldSpeakerPositionalData`  
_L160-169_
- desc: Positional data for each channel.
- L162 _public member_ `int32 NumChannels = 0;`
- L164 _public member_ `const TArray<Audio::FChannelPositionInfo>* ChannelPositions = nullptr;`
- L168 _public member_ `FQuat Rotation = FQuat::Identity;` — For encoding, this is the rotation of the emitter source relative to the world. For decoding, this is the rotation of the listener relative to the output speaker bed.

#### struct `FSoundfieldEncoderInputData`  
`struct FSoundfieldEncoderInputData`  
_L174-190_
- desc: All input parameters for a single Encode operation.
- L179 _public member_ `Audio::FAlignedFloatBuffer& AudioBuffer;` — Input buffer of interleaved floats. Each channel of the interleaved AudioBuffer corresponds to a channel index in PositionalData.
- L182 _public member_ `int32 NumChannels;` — Number of channels of the source audio buffer.
- L187 _public member_ `ISoundfieldEncodingSettingsProxy& InputSettings;` — if the input audio was already encoded to ambisonics, this will point to the settings the audio was encoded with. Otherwise, this will be a null pointer.
- L189 _public member_ `FSoundfieldSpeakerPositionalData& PositionalData;`

#### class `ISoundfieldEncoderStream`  
`class ISoundfieldEncoderStream`  
_L192-199_
- L195 _public prototype_ `virtual ~ISoundfieldEncoderStream() = default;`
- L197 _public prototype_ `virtual void Encode(const FSoundfieldEncoderInputData& InputData, ISoundfieldAudioPacket& OutputData) = 0;`
- L198 _public prototype_ `virtual void EncodeAndMixIn(const FSoundfieldEncoderInputData& InputData, ISoundfieldAudioPacket& OutputData) = 0;`

#### struct `FSoundfieldDecoderInputData`  
`struct FSoundfieldDecoderInputData`  
_L201-210_
- L203 _public member_ `ISoundfieldAudioPacket& SoundfieldBuffer;`
- L206 _public member_ `FSoundfieldSpeakerPositionalData& PositionalData;` — The positions of the channels we will output FSoundfieldDecoderOutputData::AudioBuffer to.
- L208 _public member_ `int32 NumFrames;`
- L209 _public member_ `float SampleRate;`

#### struct `FSoundfieldDecoderOutputData`  
`struct FSoundfieldDecoderOutputData`  
_L212-215_
- L214 _public member_ `Audio::FAlignedFloatBuffer& AudioBuffer;`

#### class `ISoundfieldDecoderStream`  
`class ISoundfieldDecoderStream`  
_L217-224_
- L220 _public prototype_ `virtual ~ISoundfieldDecoderStream() = default;`
- L222 _public prototype_ `virtual void Decode(const FSoundfieldDecoderInputData& InputData, FSoundfieldDecoderOutputData& OutputData) = 0;`
- L223 _public prototype_ `virtual void DecodeAndMixIn(const FSoundfieldDecoderInputData& InputData, FSoundfieldDecoderOutputData& OutputData) = 0;`

#### class `ISoundfieldTranscodeStream`  
`class ISoundfieldTranscodeStream`  
_L226-233_
- L229 _public prototype_ `virtual ~ISoundfieldTranscodeStream() = default;`
- L231 _public prototype_ `virtual void Transcode(const ISoundfieldAudioPacket& InputData, const ISoundfieldEncodingSettingsProxy& InputSettings, ISoundfieldAudioPacket& OutputData, const ISoundfieldEncodingSettingsProxy& OutputSettings) = 0;`
- L232 _public prototype_ `virtual void TranscodeAndMixIn(const ISoundfieldAudioPacket& InputData, const ISoundfieldEncodingSettingsProxy& InputSettings, ISoundfieldAudioPacket& PacketToMixTo, const ISoundfieldEncodingSettingsProxy& OutputSettings) = 0;`

#### struct `FSoundfieldMixerInputData`  
`struct FSoundfieldMixerInputData`  
_L235-243_
- L238 _public member_ `const ISoundfieldAudioPacket& InputPacket;` — Packet that should be mixed into the output.
- L240 _public member_ `const ISoundfieldEncodingSettingsProxy& EncodingSettings;` — settings used to encode both the input packet than the packet we are mixing to.
- L242 _public member_ `float SendLevel;` — The amount, in linear gain, to

#### class `ISoundfieldMixerStream`  
`class ISoundfieldMixerStream`  
_L245-251_
- L248 _public prototype_ `virtual ~ISoundfieldMixerStream() = default;`
- L250 _public prototype_ `virtual void MixTogether(const FSoundfieldMixerInputData& InputData, ISoundfieldAudioPacket& PacketToMixInto) = 0;`

#### class `ISoundfieldFactory`  
`class ISoundfieldFactory : public IModularFeature`  
_L253-340_
- inherits: `IModularFeature`
- L257 _public prototype_ `virtual ~ISoundfieldFactory() = default;` — Virtual destructor
- L260 _public prototype_ `static FName GetFormatNameForNoEncoding();` — When a submix has this format name, it is using interleaved, floating point audio with no metadata.
- L263 _public prototype_ `static FName GetFormatNameForInheritedEncoding();` — When a submix has this format name, it derives its format from the submix it sends audio to.
- L266 _public prototype_ `static FName GetModularFeatureName();` — This is the FName used to register Soundfield Format factories with the modular feature system.
- L272 _public prototype_ `static void RegisterSoundfieldFormat(ISoundfieldFactory* InFactory);` — This needs to be called to make a soundfield format usable by the engine. It can be called from a ISoundfieldFactory subclass' constructor
- L278 _public prototype_ `static void UnregisterSoundfieldFormat(ISoundfieldFactory* InFactory);` — This needs to be called it an implementation of ISoundfieldFactory is about to be destroyed. It can be called from the destructor of an implementation of ISoundfieldFactory.
- L283 _public prototype_ `static ISoundfieldFactory* Get(const FName& InName);` — Get a registered soundfield format factory by name.
- L285 _public prototype_ `static TArray<FName> GetAvailableSoundfieldFormats();`
- L288 _public prototype_ `virtual FName GetSoundfieldFormatName() = 0;` — Get soundfield format name
- L291 _public prototype_ `virtual TUniquePtr<ISoundfieldEncoderStream> CreateEncoderStream(const FAudioPluginInitializationParams& InitInfo, const ISoundfieldEncodingSettingsProxy& InitialSettings) = 0;` — Called when a stream is opened.
- L292 _public prototype_ `virtual TUniquePtr<ISoundfieldDecoderStream> CreateDecoderStream(const FAudioPluginInitializationParams& InitInfo, const ISoundfieldEncodingSettingsProxy& InitialSettings) = 0;`
- L296 _public prototype_ `virtual TUniquePtr<ISoundfieldTranscodeStream> CreateTranscoderStream(const FName SourceFormat, const ISoundfieldEncodingSettingsProxy& InitialSourceSettings, const FName DestinationFormat, const ISoundfieldEncodingSettingsProxy& InitialDestinationSettings, const FAudioPluginInitializationParams& InitInfo) = 0;` — Transcoder streams are fed a soundfield audio packet with either a different format entirely, or the same format and different settings. Specifying and returns a Transcoder Stream is not necessary if CanTranscodeSoundfieldFormat and ShouldReencodeBetween always returns false.
- L297 _public prototype_ `virtual TUniquePtr<ISoundfieldMixerStream> CreateMixerStream(const ISoundfieldEncodingSettingsProxy& InitialSettings) = 0;`
- L298 _public prototype_ `virtual TUniquePtr<ISoundfieldAudioPacket> CreateEmptyPacket() = 0;`
- L305 _public function_ `virtual bool IsTranscodeRequiredBetweenSettings(const ISoundfieldEncodingSettingsProxy& SourceSettings, const ISoundfieldEncodingSettingsProxy& DestinationSettings)` — Override this function to determine whether an incoming ISoundfieldPacket would need to be explicitly operated on between two submixes with the same format, but potentially different encoding settings. If this returns true, a new transcoder will be created. if this returns false, then the source submix's ISoundfieldPacket will be passed down directly.
- L313 _public prototype_ `virtual bool CanTranscodeFromSoundfieldFormat(FName SourceFormat, const ISoundfieldEncodingSettingsProxy& SourceEncodingSettings) = 0;` — Override this function to decide whether this soundfield format can read and convert from a source format.
- L314 _public prototype_ `virtual bool CanTranscodeToSoundfieldFormat(FName DestinationFormat, const ISoundfieldEncodingSettingsProxy& DestinationEncodingSettings) = 0;`
- L320 _public function_ `virtual bool ShouldEncodeAllStreamsIndependently(const ISoundfieldEncodingSettingsProxy& EncodingSettings)` — If this is overridden to true, we will set up a separate encoding stream for every submix plugged into this soundfield submix. Otherwise, we mix all non-soundfield submixes plugged into this soundfield submix together and use one encoding stream.
- L328 _public function_ `virtual UClass* GetCustomEncodingSettingsClass() const` — Should return the StaticClass of your implementation of USoundfieldEncodingSettingsBase.
- L333 _public prototype_ `virtual const USoundfieldEncodingSettingsBase* GetDefaultEncodingSettings() = 0;`
- L339 _public function_ `virtual bool IsEndpointFormat()` — This is overridden to return true for soundfield formats that are only used for sending audio externally. Rather than overriding this, consider implementing ISoundfieldEndpointFactory.

#### class `ISoundfieldEffectSettingsProxy`  
`class ISoundfieldEffectSettingsProxy`  
_L342-346_
- L345 _public prototype_ `virtual ~ISoundfieldEffectSettingsProxy() = default;`

#### class `USoundfieldEffectSettingsBase`  
`class USoundfieldEffectSettingsBase : public UObject`  
_L349-363_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L354 _protected prototype_ `virtual TUniquePtr<ISoundfieldEffectSettingsProxy> GetNewProxy() const PURE_VIRTUAL(USoundfieldEffectSettingsBase::GetProxy, return nullptr;);`
- L358 _private function_ `TUniquePtr<ISoundfieldEffectSettingsProxy> PrivateGetProxy() const` — This is called by any engine system that is explicitly marked as a friend.

#### class `ISoundfieldEffectInstance`  
`class ISoundfieldEffectInstance`  
_L368-374_
- desc: Single instance that actually processes the soundfield.
- L371 _public prototype_ `virtual ~ISoundfieldEffectInstance() = default;`
- L373 _public prototype_ `virtual void ProcessAudio(ISoundfieldAudioPacket& InOutPacket, const ISoundfieldEncodingSettingsProxy& EncodingSettings, const ISoundfieldEffectSettingsProxy& ProcessorSettings) = 0;`

#### class `USoundfieldEffectBase`  
`class USoundfieldEffectBase : public UObject`  
_L381-423_
- reflection: `UCLASS(config = Engine, abstract, editinlinenew, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This opaque class should be used for specifying settings for how audio should be encoded to your soundfield format for a given submix or file.
- L391 _public member_ `TObjectPtr<USoundfieldEffectSettingsBase> Settings;` — `UPROPERTY(EditAnywhere, Category = EffectPreset)` — TODO: Filter classes settable on here by GetSettingsClass.
- L397 _protected prototype_ `virtual bool SupportsFormat(const FName& InFormat) const PURE_VIRTUAL(USoundfieldEncodingSettingsBase::SupportsFormat, return false;);` — Get the implementation of USoundfieldProcessorSettingsBase that is used for this processor's settings. Will always be called on the CDO.
- L402 _protected prototype_ `virtual const UClass* GetSettingsClass() const PURE_VIRTUAL(USoundfieldEncodingSettingsBase::GetSettingsClass, return nullptr;);` — Get the implementation of USoundfieldProcessorSettingsBase that is used for this processor's settings. Will always be called on the CDO.
- L407 _protected prototype_ `virtual const USoundfieldEffectSettingsBase* GetDefaultSettings() const PURE_VIRTUAL(USoundfieldEncodingSettingsBase::GetDefaultSettings, return nullptr;);` — return the default processor settings we should use when none is provided. Will always be called on the CDO.
- L412 _protected prototype_ `virtual TUniquePtr<ISoundfieldEffectInstance> GetNewProcessor(const ISoundfieldEncodingSettingsProxy& EncodingSettings) const PURE_VIRTUAL(USoundfieldEncodingSettingsBase::GetProxy, return nullptr;);` — Spawn a new instance of this processor.
- L416 _private function_ `const USoundfieldEffectSettingsBase* PrivateGetDefaultSettings() const`
- L417 _private function_ `TUniquePtr<ISoundfieldEffectInstance> PrivateGetNewProcessor(const ISoundfieldEncodingSettingsProxy& EncodingSettings) const`

#### struct `FSoundfieldEncodingKey`  
`struct FSoundfieldEncodingKey`  
_L426-452_
- desc: This is used in FMixerSourceVoice to make sure we only encode sources once for each type of stream.
- L428 _public member_ `FName SoundfieldFormat;`
- L429 _public member_ `int32 EncodingSettingsID;`
- L431 _public function_ `FSoundfieldEncodingKey() : SoundfieldFormat(ISoundfieldFactory::GetFormatNameForNoEncoding()) , EncodingSettingsID(0)`
- L437 _public function_ `FSoundfieldEncodingKey(ISoundfieldFactory* Factory, ISoundfieldEncodingSettingsProxy& InSettings) : SoundfieldFormat(Factory ? Factory->GetSoundfieldFormatName() : ISoundfieldFactory::GetFormatNameForNoEncoding()) , EncodingSettingsID(InSettings.GetUniqueId())`
- L443 _public function_ `inline bool operator==(const FSoundfieldEncodingKey& Other) const`

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace Audio`
- L85 _function_ `template<typename ToType, typename FromType> ToType& DowncastSoundfieldRef(FromType& InRef)` — This helper function is used to downcast abstract objects during callbacks. Since implementing this API requires frequent downcasting of opaque data, and RTTI is not enabled by default in our codebase, This is useful for avoiding programmer error.
- L448 _function_ `friend inline uint32 GetTypeHash(const FSoundfieldEncodingKey& Value)`

### `Source/Runtime/AudioExtensions/Public/IWaveformTransformation.h` (Public)


#### struct `Audio::FWaveformTransformationWaveInfo`  
`struct FWaveformTransformationWaveInfo`  
_L22-29_
- desc: information about the current state of the wave file we are transforming
- L24 _public member_ `float SampleRate = 0.f;`
- L25 _public member_ `int32 NumChannels = 0;`
- L26 _public member_ `Audio::FAlignedFloatBuffer* Audio = nullptr;`
- L27 _public member_ `int32 StartSampleOffset = 0;`
- L28 _public member_ `int32 NumEditedSamples = 0;`

#### enum `Audio::ETransformationPriority`  
`enum class ETransformationPriority : uint8`  
_L31-36_
- L33 _public enumerator_ `None = 0`
- L34 _public enumerator_ `Low`
- L35 _public enumerator_ `High`

#### class `Audio::IWaveTransformation`  
`class IWaveTransformation`  
_L44-56_
- desc: Base class for the object that processes waveform data Pass tweakable variables from its paired settings UObject in the constructor in UWaveformTransformationBase::CreateTransformation note: WaveTransformation vs WaveformTransformation is to prevent UHT class name conflicts without having to namespace everything - remember this in derived classes!
- L49 _public function_ `virtual void ProcessAudio(FWaveformTransformationWaveInfo& InOutWaveInfo) const` — Applies the transformation to the waveform and modifies WaveInfo with the resulting changes
- L51 _public function_ `virtual bool SupportsRealtimePreview() const`
- L52 _public function_ `virtual constexpr ETransformationPriority FileChangeLengthPriority() const`
- L53 _public function_ `virtual bool CanChangeChannelCount() const`
- L55 _public prototype_ `virtual ~IWaveTransformation() = default;`

#### struct `FSoundWaveCuePoint`  
`struct FSoundWaveCuePoint`  
_L63-113_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct defining a cue point in a sound wave asset
- L69 _public member_ `int32 CuePointID = INDEX_NONE;` — `UPROPERTY(Category = Info, VisibleAnywhere, BlueprintReadOnly)` — Unique identifier for the wave cue point
- L73 _public member_ `FString Label;` — `UPROPERTY(Category = Info, EditAnywhere, BlueprintReadOnly)` — The label for the cue point
- L77 _public member_ `int64 FramePosition = 0;` — `UPROPERTY(Category = Info, EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0))` — The frame position of the cue point
- L81 _public member_ `int64 FrameLength = 0;` — `UPROPERTY(Category = Info, EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0))` — The frame length of the cue point (non-zero if it's a region)
- L83 _public function_ `bool IsLoopRegion() const`
- L84 _public function_ `void SetLoopRegion(bool value)`
- L86 _public function_ `const bool operator==(const FSoundWaveCuePoint& Other) const`
- L95 _public function_ `const bool operator!=(const FSoundWaveCuePoint& Other) const`
- L98 _public function_ `void ScaleFrameValues(float Factor)`
- L112 _protected member_ `bool bIsLoopRegion = false;` — `UPROPERTY(Category = Info, EditAnywhere, BlueprintReadOnly)` — intentionally kept private. only USoundFactory should modify this value on import

#### struct `FWaveTransformUObjectConfiguration`  
`struct FWaveTransformUObjectConfiguration`  
_L116-135_
- desc: Information about the the wave file we are transforming for Transformation UObjects
- L118 _public member_ `int32 NumChannels = 0;`
- L119 _public member_ `float SampleRate = 0;`
- L120 _public member_ `float StartTime = 0.f;`
- L121 _public member_ `float EndTime = -1.f;`
- L122 _public member_ `TArray<FSoundWaveCuePoint> WaveCues;` — List of cues parsed from the wave file
- L123 _public member_ `bool bIsPreviewingLoopRegion = false;`
- L124 _public member_ `bool bCachedSoundWaveLoopState = false;`
- L127 _protected member_ `int64 OriginalNumFrames = 0;`
- L130 _public function_ `void SetOriginalNumFrames(const int64 InOriginalNumFrames)`
- L131 _public function_ `const int64 GetOriginalNumFrames() const`
- L133 _public function_ `int64 GetStartFrameOffset() const`
- L134 _public prototype_ `int64 GetEndFrameOffset() const;`

#### struct `FWaveformTransformationInfo`  
`struct FWaveformTransformationInfo`  
_L139-143_
- desc: Information to be retrieved from each transformation (Add members as needed)
- L141 _public member_ `TArray<FSoundWaveCuePoint> AllCuePoints;` — Cue Points and Loop Regions
- L142 _public member_ `TArray<FSoundWaveCuePoint> AllCuePointsRelativeToStartTime;` — Cue Points and Loop Regions offset by start time

#### class `UWaveformTransformationBase`  
`class UWaveformTransformationBase : public UObject`  
_L148-197_
- reflection: `UCLASS(Abstract, EditInlineNew, MinimalAPI)`
- inherits: `UObject`
- desc: Base class to hold editor configurable properties for an arbitrary transformation of audio waveform data
- L153 _public function_ `virtual Audio::FTransformationPtr CreateTransformation() const`
- L154 _public function_ `virtual void UpdateConfiguration(FWaveTransformUObjectConfiguration& InOutConfiguration)`
- L155 _public function_ `virtual void OverwriteTransformation()`
- L156 _public function_ `virtual constexpr Audio::ETransformationPriority GetTransformationPriority() const`
- L159 _public function_ `static void SortTransformationsArray(TArray<TObjectPtr<UWaveformTransformationBase>>& InOutTransformations)` — Sort to ensure proper order of operation for audio processing
- L177 _public function_ `virtual void OverwriteSoundWaveData(USoundWave& InOutSoundWave)`
- L178 _public function_ `virtual void GetTransformationInfo(FWaveformTransformationInfo& InOutTransformationInfo) const`
- L179 _public prototype_ `virtual FString GetTransformationHash() const PURE_VIRTUAL(UWaveformTransformationBase::GetTransformationHash, return FString(););`
- L181 _public prototype_ `virtual void PostEditUndo() override;`
- L182 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L184 _public prototype_ `void NotifyPropertyChange(FProperty* Property);`
- L187 _public function_ `virtual bool IsEditorOnly() const override`
- L191 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnTransformationChanged, bool);` — Execute when the soundwave needs a recook to apply new transformation changes, bool flag if it should mark the file dirty
- L192 _public member_ `FOnTransformationChanged OnTransformationChanged;`
- L195 _public prototype_ `DECLARE_DELEGATE(FOnTransformationRenderChanged);` — Execute when only the rendering needs to be updated, but can wait for a recook
- L196 _public member_ `FOnTransformationRenderChanged OnTransformationRenderChanged;`

#### class `UWaveformTransformationChain`  
`class UWaveformTransformationChain : public UObject`  
_L201-212_
- reflection: `UCLASS(EditInlineNew, MinimalAPI)`
- inherits: `UObject`
- desc: Object that holds an ordered list of transformations to perform on a sound wave
- L207 _public member_ `TArray<TObjectPtr<UWaveformTransformationBase>> Transformations;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Transformations")`
- L209 _public function_ `virtual bool IsEditorOnly() const override`
- L211 _public prototype_ `TArray<Audio::FTransformationPtr> CreateTransformations() const;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Audio`
- L58 _typedef_ `using FTransformationPtr = TUniquePtr<Audio::IWaveTransformation>;` (scope `Audio`)
- L162 _function_ `` (scope `UWaveformTransformationBase::SortTransformationsArray`)
- L191 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTransformationChanged, bool);` — Execute when the soundwave needs a recook to apply new transformation changes, bool flag if it should mark the file dirty
- L195 _delegate_ `DECLARE_DELEGATE(FOnTransformationRenderChanged);` — Execute when only the rendering needs to be updated, but can wait for a recook

### `Source/Runtime/AudioExtensions/Public/SoundGeneratorOutput.h` (Public)


#### struct `FSoundGeneratorOutput`  
`struct FSoundGeneratorOutput`  
_L13-20_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base class for generators that have outputs that can be exposed to other game code. NOTE: This is not widely supported and should be considered experimental.
- L19 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, Category = SoundGeneratorOutput)` — The output's name
