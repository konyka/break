# Plugins / AudioGameplay

- module root: `Plugins/AudioGameplay/Source/AudioGameplay`
- headers: 17; symbols: 240
- symbol kinds: class=17, delegate=8, enum=1, enumerator=3, function=21, macro=8, member=36, namespace=7, prototype=131, struct=4, typedef=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AudioMixerCore, CoreUObject, Engine
- PublicDependencyModuleNames: AudioExtensions, Core, GameplayTags

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioAssetUserData.h` (Public)


#### class `UAudioAssetUserData`  
`class UAudioAssetUserData : public UAssetUserData`  
_L15-38_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UAssetUserData`
- desc: UAudioAssetUserData - Base class for user data being attached to audio assets
- L22 _public member_ `FGameplayTagContainer MetadataTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")`
- L26 _public prototype_ `static FGameplayTagContainer GetAllTags(USoundBase* InSound);` — `UFUNCTION(BlueprintPure, Category = "Audio AssetUserData Tags")` — Gather all AudioAssetUserData tags for this sound and its sound class.
- L30 _public prototype_ `static bool HasTag(USoundBase* InSound, FGameplayTag InTag, bool bExactMatch = false);` — `UFUNCTION(BlueprintPure, Category = "Audio AssetUserData Tags")` — Whether the sound or its sound class have the supplied (possibly exact) tag .
- L34 _public prototype_ `static FGameplayTagContainer GetFilteredTags(USoundBase* InSound, FGameplayTag InTag);` — `UFUNCTION(BlueprintPure, Category = "Audio AssetUserData Tags")` — Gather all AudioAssetUserData tags for this sound and its sound class, that match the supplied tag.
- L37 _public prototype_ `static UAudioAssetUserData* Get(UObject* InObject);` — If the supplied object has a UAudioAssetUserData asset user data attached, gets it. Returns nullptr otherwise.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOGAMEPLAY_API`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioComponentGroup.h` (Public)


#### class `UAudioComponentGroup`  
`class UAudioComponentGroup : public USceneComponent, public IAudioParameterControllerInterface`  
_L27-201_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DefaultToInstanced)`
- inherits: `USceneComponent,IAudioParameterControllerInterface`
- desc: Automatic Handler for voices and parameters across any number of AudioComponents
- L33 _public prototype_ `UAudioComponentGroup(const FObjectInitializer& ObjectInitializer);`
- L35 _public prototype_ `virtual ~UAudioComponentGroup() = default;`
- L38 _public prototype_ `static UAudioComponentGroup* StaticGetOrCreateComponentGroup(AActor* Actor);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L40 _public prototype_ `virtual void BeginPlay() override;`
- L44 _public prototype_ `void StopSound(USoundBase* Sound, const float FadeTime = 0.f);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)` — Stop all instances of this Sound on any internal or external components
- L47 _public prototype_ `bool IsPlayingAny() const;` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = AudioComponentGroup)`
- L50 _public function_ `bool IsVirtualized() const` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = AudioComponentGroup)`
- L53 _public prototype_ `void BroadcastStopAll();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L56 _public prototype_ `void BroadcastKill();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L59 _public prototype_ `void BroadcastEvent(const FName EventName);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L62 _public prototype_ `UAudioComponent* GetNextAvailableComponent();` — Component interaction
- L64 _public prototype_ `UAudioComponent* AddComponent();`
- L65 _public prototype_ `UAudioComponent* ResetComponent(UAudioComponent* Component) const;`
- L66 _public prototype_ `void RemoveComponent(const UAudioComponent* InComponent);`
- L70 _public prototype_ `void AddExternalComponent(UAudioComponent* ComponentToAdd);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)` — Allow an externally created AudioComponent to share parameters with this SoundGroup
- L73 _public prototype_ `void RemoveExternalComponent(UAudioComponent* ComponentToRemove);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L76 _public prototype_ `void EnableVirtualization();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L79 _public prototype_ `void DisableVirtualization();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L82 _public function_ `void SetVolumeMultiplier(const float InVolume)` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L85 _public function_ `void SetPitchMultiplier(const float InPitch)` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L88 _public function_ `void SetLowPassFilter(const float InFrequency)` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L90 _public function_ `const TArray<FAudioParameter>& GetParams()`
- L93 _public prototype_ `void AddExtension(TScriptInterface<IAudioComponentGroupExtension> NewExtension);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L96 _public prototype_ `void RemoveExtension(TScriptInterface<IAudioComponentGroupExtension> NewExtension);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L98 _public prototype_ `void UpdateExtensions(const float DeltaTime);`
- L100 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L103 _public prototype_ `float GetFloatParamValue(const FName ParamName) const;` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = AudioComponentGroup)`
- L106 _public prototype_ `bool GetBoolParamValue(const FName ParamName) const;` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = AudioComponentGroup)`
- L109 _public prototype_ `FString GetStringParamValue(const FName ParamName) const;` — `UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = AudioComponentGroup)`
- L112 _public prototype_ `void SubscribeToStringParam(const FName ParamName, FStringParamCallback Delegate);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L115 _public prototype_ `void SubscribeToEvent(const FName EventName, FSoundCallback Delegate);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L118 _public prototype_ `void SubscribeToBool(const FName ParamName, FBoolParamCallback Delegate);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)`
- L122 _public prototype_ `void UnsubscribeObject(const UObject* Object);` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = AudioComponentGroup)` — remove any string, event, and bool subscriptions that are bound to this object
- L125 _public prototype_ `virtual void ResetParameters() override;`
- L127 _public prototype_ `virtual void SetTriggerParameter(FName InName) override;`
- L128 _public prototype_ `virtual void SetBoolParameter(FName InName, bool InBool) override;`
- L129 _public prototype_ `virtual void SetBoolArrayParameter(FName InName, const TArray<bool>& InValue) override;`
- L130 _public prototype_ `virtual void SetIntParameter(FName InName, int32 InInt) override;`
- L131 _public prototype_ `virtual void SetIntArrayParameter(FName InName, const TArray<int32>& InValue) override;`
- L132 _public prototype_ `virtual void SetFloatParameter(FName InName, float InFloat) override;`
- L133 _public prototype_ `virtual void SetFloatArrayParameter(FName InName, const TArray<float>& InValue) override;`
- L134 _public prototype_ `virtual void SetStringParameter(FName InName, const FString& InValue) override;`
- L135 _public prototype_ `virtual void SetStringArrayParameter(FName InName, const TArray<FString>& InValue) override;`
- L136 _public prototype_ `virtual void SetObjectParameter(FName InName, UObject* InValue) override;`
- L137 _public prototype_ `virtual void SetObjectArrayParameter(FName InName, const TArray<UObject*>& InValue) override;`
- L139 _public prototype_ `virtual void SetParameter(FAudioParameter&& InValue) override;`
- L140 _public prototype_ `virtual void SetParameters(TArray<FAudioParameter>&& InValues) override;`
- L141 _public prototype_ `virtual void SetParameters_Blueprint(const TArray<FAudioParameter>& InParameters) override;`
- L145 _public member_ `FSoundGroupChanged OnStopped;` — `UPROPERTY(BlueprintAssignable)`
- L148 _public member_ `FSoundGroupChanged OnKilled;` — `UPROPERTY(BlueprintAssignable)`
- L151 _public member_ `FSoundGroupChanged OnVirtualized;` — `UPROPERTY(BlueprintAssignable)`
- L154 _public member_ `FSoundGroupChanged OnUnvirtualized;` — `UPROPERTY(BlueprintAssignable)`
- L156 _public prototype_ `void IterateComponents(const TFunction<void(UAudioComponent*)> OnIterate);`
- L160 _protected prototype_ `void ApplyParams(UAudioComponent* Component) const;`
- L161 _protected prototype_ `void ApplyModifiers(UAudioComponent* Component, const FAudioComponentModifier& Modifier) const;`
- L163 _protected prototype_ `void UpdateComponentParameters();`
- L165 _protected prototype_ `float GetComponentVolume() const;`
- L167 _protected prototype_ `void ExecuteStringParamSubscriptions(const FAudioParameter& StringParam);`
- L168 _protected prototype_ `void ExecuteBoolParamSubscriptions(const FAudioParameter& BoolParam);`
- L169 _protected prototype_ `void ExecuteEventSubscriptions(const FName EventName);`
- L171 _protected prototype_ `const FAudioParameter* GetParamInternal(const FName ParamName) const;`
- L174 _protected member_ `TArray<TObjectPtr<UAudioComponent>> Components;` — `UPROPERTY(VisibleAnywhere, Category = AudioComponentGroup)`
- L177 _protected member_ `TArray<FAudioParameter> ParamsToSet;` — `UPROPERTY(Transient)`
- L180 _protected member_ `TArray<FAudioParameter> PersistentParams;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AudioComponentGroup)`
- L183 _protected member_ `TArray<TScriptInterface<IAudioComponentGroupExtension>> Extensions;` — `UPROPERTY(Transient)`
- L186 _protected member_ `FAudioComponentModifier GroupModifier;` — Modifier set externally via BP functions
- L189 _protected member_ `FAudioComponentModifier CachedModifier;` — final values set last update
- L192 _protected member_ `TArray<TWeakObjectPtr<UAudioComponent>> ExternalComponents;` — Components managed externally that won't be used in the pool, but can still share parameters
- L194 _protected member_ `TMap<FName, TArray<FStringParamCallback>> StringSubscriptions;`
- L195 _protected member_ `TMap<FName, TArray<FSoundCallback>> EventSubscriptions;`
- L196 _protected member_ `TMap<FName, TArray<FBoolParamCallback>> BoolSubscriptions;`
- L198 _protected member_ `bool bIsVirtualized = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOGAMEPLAY_API`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoundGroupChanged);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoundGroupChanged);`
- L19 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FSoundCallback, const FName&, EventName);`
- L19 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FSoundCallback, const FName&, EventName);`
- L20 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FBoolParamCallback, const bool, ParamValue);`
- L20 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FBoolParamCallback, const bool, ParamValue);`
- L21 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FStringParamCallback, const FString&, Value);`
- L21 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FStringParamCallback, const FString&, Value);`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioComponentGroupDebug.h` (Public)


#### class `FAudioComponentGroupDebug`  
`class FAudioComponentGroupDebug`  
_L13-33_
- L17 _public prototype_ `static void DebugPrint(const UAudioComponentGroup* ComponentGroup);` — Print debug info above the component group's owner, depending on which console variables are enabled
- L20 _public prototype_ `static FString DebugPrintParams(const UAudioComponentGroup* ComponentGroup);` — print the names and values of parameters set on this component group
- L23 _public prototype_ `static FString GetDebugParamString(const FAudioParameter& Param);` — return a string with the name and value of an audio parameter, depending on which underlying type is held by the parameter
- L26 _public prototype_ `static FColor GetDebugStringColor(const bool bVirtualized);` — green, or yellow if the component group is virtualized
- L29 _public prototype_ `static FString DebugPrintActiveSounds(const UAudioComponentGroup* ComponentGroup);` — print a list of all playing sounds on the component group
- L32 _public prototype_ `static void PrintDebugString(const FString& InString, AActor* Owner, const FColor DrawColor);` — print the final debug string above the target actor

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioComponentGroupExtension.h` (Public)


#### struct `FAudioComponentModifier`  
`struct FAudioComponentModifier`  
_L12-37_
- L14 _public member_ `float Volume = 1.f;`
- L15 _public member_ `float Pitch = 1.f;`
- L16 _public member_ `float LowPassFrequency = MAX_FILTER_FREQUENCY;`
- L18 _public function_ `void Combine(const FAudioComponentModifier& Other)`
- L25 _public function_ `bool IsNearlyEqual(const FAudioComponentModifier& Other) const`
- L32 _public function_ `static FAudioComponentModifier& Default()`

#### class `UAudioComponentGroupExtension`  
`class UAudioComponentGroupExtension : public UInterface`  
_L40-43_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`

#### class `IAudioComponentGroupExtension`  
`class IAudioComponentGroupExtension : public IInterface`  
_L45-56_
- inherits: `IInterface`
- L51 _public function_ `virtual void Update(const float DeltaTime, UAudioComponentGroup* Group, FAudioComponentModifier& OutModifier)`
- L53 _public function_ `virtual void OnAddedToGroup(UAudioComponentGroup* NewGroup)`
- L55 _public function_ `virtual void OnComponentAdded(UAudioComponent* NewComponent)`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioGameplayComponent.h` (Public)


#### class `UAudioGameplayComponent`  
`class UAudioGameplayComponent : public UActorComponent`  
_L14-38_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Config = Game, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L20 _public typedef_ `using PayloadFlags = AudioGameplay::EComponentPayload;`
- L22 _public prototype_ `virtual ~UAudioGameplayComponent() = default;`
- L25 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L26 _public prototype_ `virtual void Deactivate() override;`
- L27 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L30 _public prototype_ `virtual bool HasPayloadType(PayloadFlags InType) const;`
- L34 _protected prototype_ `virtual void Enable();`
- L35 _protected prototype_ `virtual void Disable();`
- L37 _protected member_ `PayloadFlags PayloadType = PayloadFlags::AGCP_None;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOGAMEPLAY_API`
- L11 _namespace_ `namespace EEndPlayReason`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioGameplayFlags.h` (Public)


#### enum `AudioGameplay::EComponentPayload`  
`enum class EComponentPayload : uint8`  
_L10-20_
- L13 _public enumerator_ `AGCP_None = 0x00` — No payload
- L16 _public enumerator_ `AGCP_Listener = 0x01` — Payload affects audio listeners
- L19 _public enumerator_ `AGCP_ActiveSound = 0x02` — Payload affects Active Sound playback

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AudioGameplay`
- L23 _prototype_ `ENUM_CLASS_FLAGS(AudioGameplay::EComponentPayload);`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioGameplayLogs.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AudioGameplayLog, Log, All);`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioGameplayModule.h` (Public)


#### class `FAudioGameplayModule`  
`class FAudioGameplayModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- desc: FAudioGameplayModule
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioGameplayRequirements.h` (Public)


#### class `UAudioRequirementPreset`  
`class UAudioRequirementPreset : public UDataAsset`  
_L16-29_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: UAudioRequirementPreset - A reusable GameplayTagQuery for audio
- L22 _public prototype_ `~UAudioRequirementPreset() = default;`
- L25 _public member_ `FGameplayTagQuery Query;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Tag Query")`
- L28 _public prototype_ `bool Matches(const FGameplayTagContainer& Tags) const;` — Returns true if the query is not empty and matches the provided tags

#### struct `FAudioGameplayRequirements`  
`struct FAudioGameplayRequirements`  
_L35-49_
- reflection: `USTRUCT(BlueprintType)`
- desc: AudioGameplayRequirements - A set of requirements for audio gameplay features.
- L41 _public member_ `TObjectPtr<UAudioRequirementPreset> Preset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")` — An optional requirement preset tested against a collection of tags to determine a match.  Ignored if null.
- L45 _public member_ `FGameplayTagQuery Custom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Requirements")` — An optional custom query tested against a collection of tags to determine a match.  Ignored if empty.
- L48 _public prototype_ `bool Matches(const FGameplayTagContainer& Tags) const;` — Returns true if the preset and the custom query match the provided tags; ignores preset or custom query if they are empty.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOGAMEPLAY_API`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioGameplayShuffle.h` (Public)


#### struct `UE::Audio::FShuffleUtil`  
`struct FShuffleUtil`  
_L15-30_
- desc: FShuffleUtil - Utility to provide a fast random index in an array without replacement ie, all elements will be returned from GetNextIndex exactly once before repeating
- L18 _public prototype_ `void Initialize(int32 ArraySize);` — Initializes the Shuffle Array
- L21 _public prototype_ `uint8 GetNextIndex();` — Returns next valid index, or INDEX_NONE if not initialized. Shuffles array if needed
- L25 _protected member_ `uint8 ShuffleMarker = 0;`
- L26 _protected member_ `TArray<uint8> ShuffleArray;`
- L29 _protected prototype_ `void Shuffle();` — Shuffles the internal array

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API AUDIOGAMEPLAY_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Audio` (scope `UE`)

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioGameplayTagCacheSubsystem.h` (Public)


#### class `UAudioGameplayTagCacheSubsystem`  
`class UAudioGameplayTagCacheSubsystem : public UWorldSubsystem`  
_L19-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: UAudioGameplayTagCacheSubsystem - Per world subsystem used to persist gameplay tags that are expensive to construct dynamically from parts
- L25 _public prototype_ `UAudioGameplayTagCacheSubsystem() = default;`
- L26 _public prototype_ `virtual ~UAudioGameplayTagCacheSubsystem() = default;`
- L29 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L30 _public prototype_ `virtual void Deinitialize() override;`
- L33 _public prototype_ `static UAudioGameplayTagCacheSubsystem* Get(const UWorld* WorldContext);`
- L35 _public function_ `FGameplayTagMap& GetTagCache()`
- L42 _protected member_ `FGameplayTagMap GameplayTagCache;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOGAMEPLAY_API`
- L13 _typedef_ `using FGameplayTagMap = UE::AudioGameplay::TMapAnyKey<FGameplayTag>;`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioParameterComponent.h` (Public)


#### class `UAudioParameterComponent`  
`class UAudioParameterComponent : public UAudioGameplayComponent, public IAudioParameterControllerInterface, public IActorSoundParameterInterface`  
_L26-75_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories=(Object, ActorComponent, Physics, Rendering, Mobility, LOD), meta=(BlueprintSpawnableComponent))`
- inherits: `UAudioGameplayComponent,IAudioParameterControllerInterface,IActorSoundParameterInterface`
- desc: UAudioParameterComponent - Can be used to set/store audio parameters and automatically dispatch them (through ActorSoundParameterInterface) to any sounds played by the component's Owner Actor
- L35 _public function_ `const TArray<FAudioParameter>& GetParameters() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = Parameters)`
- L38 _public prototype_ `virtual void GetActorSoundParams_Implementation(TArray<FAudioParameter>& Params) const override;` — Begin IActorSoundParameterInterface
- L42 _public prototype_ `virtual void ResetParameters() override;` — Begin IAudioParameterControllerInterface
- L43 _public prototype_ `virtual void SetTriggerParameter(FName InName) override;`
- L44 _public prototype_ `virtual void SetBoolParameter(FName InName, bool InValue) override;`
- L45 _public prototype_ `virtual void SetBoolArrayParameter(FName InName, const TArray<bool>& InValue) override;`
- L46 _public prototype_ `virtual void SetIntParameter(FName InName, int32 InInt) override;`
- L47 _public prototype_ `virtual void SetIntArrayParameter(FName InName, const TArray<int32>& InValue) override;`
- L48 _public prototype_ `virtual void SetFloatParameter(FName InName, float InValue) override;`
- L49 _public prototype_ `virtual void SetFloatArrayParameter(FName InName, const TArray<float>& InValue) override;`
- L50 _public prototype_ `virtual void SetStringParameter(FName InName, const FString& InValue) override;`
- L51 _public prototype_ `virtual void SetStringArrayParameter(FName InName, const TArray<FString>& InValue) override;`
- L52 _public prototype_ `virtual void SetObjectParameter(FName InName, UObject* InValue) override;`
- L53 _public prototype_ `virtual void SetObjectArrayParameter(FName InName, const TArray<UObject*>& InValue) override;`
- L54 _public prototype_ `virtual void SetParameters_Blueprint(const TArray<FAudioParameter>& InParameters) override;`
- L55 _public prototype_ `virtual void SetParameter(FAudioParameter&& InValue) override;`
- L56 _public prototype_ `virtual void SetParameters(TArray<FAudioParameter>&& InValues) override;`
- L61 _public member_ `FOnParameterChanged OnParameterChanged;` — `UPROPERTY(BlueprintAssignable)`
- L66 _private prototype_ `void SetParameterInternal(FAudioParameter&& InParam);`
- L67 _private prototype_ `void GetAllAudioComponents(TArray<UAudioComponent*>& Components) const;`
- L68 _private prototype_ `void LogParameter(FAudioParameter& InParam);`
- L71 _private member_ `TArray<TWeakObjectPtr<UAudioComponent>> ActiveComponents;` — `UPROPERTY(Transient)`
- L74 _private member_ `TArray<FAudioParameter> Parameters;` — `UPROPERTY(EditDefaultsOnly, Category = "Parameters")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOGAMEPLAY_API`
- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioParameterComponent, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioParameterComponent, Log, All);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParameterChanged, const FAudioParameter&, Parameter);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParameterChanged, const FAudioParameter&, Parameter);`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/FilteredGameplayTagContainer.h` (Public)


#### class `FFilteredGameplayTagContainer`  
`class FFilteredGameplayTagContainer`  
_L26-88_
- desc: A container of FGameplayTag associated to a FGameplayTagQuery. Tags will only be added if the accompanying query is satisfied. Whenever a tag is added or removed, the tags in the container are "Filtered": i.e. their query is checked to see if they should still remain in the array. Note: Tags are unique Filtering is evaluated from last to first element in the array
- L39 _public prototype_ `bool AddTagFiltered(const FilteredGPTContainer::FGPTagQueryPair& InPair);` — Adds a tag to the container if the query matches. If the tag is added, proceeds to evaluate the conditions on the contained tags to check if they should remain or not. @param InPair			The tag and query to try and add to this container @return True if tag was added
- L51 _public prototype_ `bool AddTagFiltered(const FGameplayTag& InTag, const FGameplayTagQuery& InQuery = FGameplayTagQuery());` — Adds a tag to the container if the query matches. If the tag is added, proceeds to evaluate the conditions on the contained tags to check if they should be kept or not. @param InTag			The tag to try add to this container @param InQuery		The query to determine if this tag should be added to the container @return True if tag was added
- L59 _public prototype_ `bool RemoveTagFiltered(const FGameplayTag& InTag);` — Removes a tag from the container, then proceeds to evaluate the conditions on the contained tags to check if they should be kept or not. @return True if tag was removed
- L61 _public function_ `inline int32 Find(const FilteredGPTContainer::FGPTagQueryPair& EventToFind) const`
- L66 _public function_ `inline int32 Num() const`
- L71 _public function_ `inline bool IsEmpty() const`
- L76 _public member_ `FOnFilteredGameplayTagAdded OnGameplayTagAdded;`
- L77 _public member_ `FOnFilteredGameplayTagRemoved OnGameplayTagRemoved;`
- L81 _private prototype_ `bool AddTagToContainers(const FilteredGPTContainer::FGPTagQueryPair& InPair);`
- L82 _private prototype_ `bool RemoveTagFromContainers(const FGameplayTag& Tag);`
- L83 _private prototype_ `void FilterTags();`
- L84 _private prototype_ `void CheckContainersConsistency();`
- L86 _private member_ `TArray<FilteredGPTContainer::FGPTagQueryPair> GPTagQueryPairContainer;`
- L87 _private member_ `FGameplayTagContainer TagContainer;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API AUDIOGAMEPLAY_API`
- L8 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilteredGameplayTagAdded, const FGameplayTag) DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilteredGameplayTagRemoved, const FGameplayTag) namespace FilteredGPTContainer { typedef TPair<FGameplayTag, FGameplayTagQuery> FGPTagQueryPair; } class FFilteredGameplayTagContainer { public: bool AddTagFiltered(const FilteredGPTContainer::FGPTagQueryPair& InPair); /** * Adds a tag to the container if the query matches. * If the tag is added, proceeds to evaluate the conditions on the contained tags to check * if they should be kept or not. * * @param InTag The tag to try add to this container * @param InQuery The query to determine if this tag should be added to the container`
- L9 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFilteredGameplayTagRemoved, const FGameplayTag) namespace FilteredGPTContainer { typedef TPair<FGameplayTag, FGameplayTagQuery> FGPTagQueryPair; } class FFilteredGameplayTagContainer { public: bool AddTagFiltered(const FilteredGPTContainer::FGPTagQueryPair& InPair); /** * Adds a tag to the container if the query matches. * If the tag is added, proceeds to evaluate the conditions on the contained tags to check * if they should be kept or not. * * @param InTag The tag to try add to this container * @param InQuery The query to determine if this tag should be added to the container *`
- L11 _namespace_ `namespace FilteredGPTContainer`
- L13 _typedef_ `typedef TPair<FGameplayTag, FGameplayTagQuery> FGPTagQueryPair;` (scope `FilteredGPTContainer`)

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/Interfaces/IAudioGameplayCondition.h` (Public)


#### class `UAudioGameplayCondition`  
`class UAudioGameplayCondition : public UInterface`  
_L20-23_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for implementing conditions for the audio toggle system. Make a component or actor implement this interface to provide its Audio Toggle component set in Arbitrary condition mode a way to compute its On/Off state. If the actor implements it, the Audio Toggle will abide by the implementation on the actor. If any component on the same actor implements it, the Audio Toggle will abide by the implementation on the *first* of these components. See: Audio Toggle component (UAudioGameplayVolumeComponent)

#### class `IAudioGameplayCondition`  
`class IAudioGameplayCondition`  
_L25-53_
- L38 _public prototype_ `bool ConditionMet() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AudioGameplayCondition")` — Generic condition check, whatever the toggle is being evaluated for (Audio Listener, Active sound,...) @returns true if toggle state should be On, false otherwise
- L39 _public function_ `virtual bool ConditionMet_Implementation() const`
- L51 _public prototype_ `bool ConditionMet_Position(const FVector& Position) const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AudioGameplayCondition")` — Allows testing a condition against a provided position. This position can be that of the Audio Listener, of the Active Sound,... for which the toggle is being evaluated. @param Position - The location to be considered @returns true if toggle state should be On for this entity's position, false otherwise
- L52 _public function_ `virtual bool ConditionMet_Position_Implementation(const FVector& Position) const`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/Interfaces/IAudioGameplayVolumeInteraction.h` (Public)


#### class `UAudioGameplayVolumeInteraction`  
`class UAudioGameplayVolumeInteraction : public UInterface`  
_L21-24_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI, meta = (DisplayName = "Audio Toggle Interaction"))`
- inherits: `UInterface`
- desc: Interface for interacting with the audio toggle system. Make a component implement this interface to receive notifications when the toggle is active for at least one listener or inactive for all. The owning actor must have an Audio Toggle component for other components of this actor implementing this interface to receive the notifications. Instead of implementing this interface, you can also just bind to the "On Toggled On" and "On Toggled Off" events of the Audio Toggle component directly.

#### class `IAudioGameplayVolumeInteraction`  
`class IAudioGameplayVolumeInteraction`  
_L26-45_
- L36 _public prototype_ `void OnListenerEnter();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AudioGameplayVolume", meta = (DisplayName = "On Toggled On"))` — Called when the Audio Toggle on the same actor switches to ON.
- L37 _public function_ `virtual void OnListenerEnter_Implementation()`
- L43 _public prototype_ `void OnListenerExit();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AudioGameplayVolume", meta = (DisplayName = "On Toggled Off"))` — Called when the Audio Toggle on the same actor switches to OFF.
- L44 _public function_ `virtual void OnListenerExit_Implementation()`

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/MapAnyKey.h` (Public)


#### class `UE::AudioGameplay::TMapAnyKey`  
`template <typename ValueType> class TMapAnyKey : public TMap<uint32, ValueType>`  
_L12-42_
- inherits: `TMap<uint32,ValueType>`
- desc: Variant of TMap that allows multiple key types within the same map instance. Key types must be hash-able, as with a regular map.
- L14 _private typedef_ `using Super = TMap<uint32, ValueType>;`
- L27 _public function_ `template <typename AnyKeyType> ValueType& FindOrAdd(AnyKeyType Key, bool& bHadKey)` — Find the value associated with a specified key, or if none exists, add a value using the default constructor. @param Key The key to search for. @param bHadKey True if found, false if added. @return A reference to the value associated with the specified key.

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace AudioGameplay` (scope `UE`)

### `Plugins/AudioGameplay/Source/AudioGameplay/Public/SoundHandleSubsystem.h` (Public)


#### class `USoundHandleSubsystem`  
`class USoundHandleSubsystem : public UAudioEngineSubsystem , public IActiveSoundUpdateInterface , public ISoundHandleSystem`  
_L18-55_
- reflection: `UCLASS()`
- inherits: `UAudioEngineSubsystem,IActiveSoundUpdateInterface,ISoundHandleSystem`
- desc: An implementation of ISoundHandleSystem using AudioEngineSubsystem
- L25 _public prototype_ `virtual ~USoundHandleSubsystem() override = default;`
- L28 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L29 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L30 _public prototype_ `virtual void Deinitialize() override;`
- L34 _public prototype_ `virtual void NotifyActiveSoundDeleting(const FActiveSound& ActiveSound) override;`
- L35 _public prototype_ `virtual void NotifyVirtualizedSoundDeleting(const FActiveSound& ActiveSound) override;`
- L39 _public prototype_ `virtual Audio::FSoundHandleID CreateSoundHandle(USoundBase* Sound, ISoundHandleOwner* Owner) override;`
- L40 _public prototype_ `virtual void SetTransform(Audio::FSoundHandleID ID, const FTransform& Transform) override;`
- L41 _public prototype_ `virtual Audio::EResult Play(Audio::FSoundHandleID ID) override;`
- L42 _public prototype_ `virtual void Stop(Audio::FSoundHandleID ID) override;`
- L51 _protected member_ `TMap<Audio::FSoundHandleID, FSoundHandle> ActiveHandles;`
- L52 _protected member_ `TMap<Audio::FSoundHandleID, ISoundHandleOwner*> Owners;`
- L54 _protected prototype_ `void NotifySoundDeleting(const FActiveSound& ActiveSound);`

#### struct `USoundHandleSubsystem::FSoundHandle`  
`struct FSoundHandle`  
_L46-49_
- L48 _public member_ `FActiveSound ActiveSound;`
