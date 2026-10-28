# Plugins / AudioGameplayVolume

- module root: `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume`
- headers: 14; symbols: 327
- symbol kinds: class=23, delegate=2, function=38, macro=9, member=110, prototype=136, struct=5, typedef=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AudioGameplay, CoreUObject, Engine
- PublicDependencyModuleNames: Core

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AttenuationVolumeComponent.h` (Public)


#### class `FProxyMutator_Attenuation`  
`class FProxyMutator_Attenuation : public FProxyVolumeMutator`  
_L13-31_
- inherits: `FProxyVolumeMutator`
- desc: FProxyMutator_Attenuation - An audio thread representation of occlusion settings (volume attenuation)
- L17 _public prototype_ `FProxyMutator_Attenuation();`
- L18 _public prototype_ `virtual ~FProxyMutator_Attenuation() = default;`
- L20 _public member_ `float ExteriorVolume = 1.0f;`
- L21 _public member_ `float ExteriorTime = 0.5f;`
- L22 _public member_ `float InteriorVolume = 1.0f;`
- L23 _public member_ `float InteriorTime = 0.5f;`
- L25 _public prototype_ `virtual void Apply(FInteriorSettings& InteriorSettings) const override;`
- L26 _public prototype_ `virtual void Apply(FAudioProxyActiveSoundParams& Params) const override;`
- L30 _protected member_ `constexpr static const TCHAR MutatorAttenuationName[] = TEXT("Att`

#### class `UAttenuationVolumeComponent`  
`class UAttenuationVolumeComponent : public UAudioGameplayVolumeMutator`  
_L39-81_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Config = Game, ClassGroup = ("AudioGameplayVolume"), meta = (BlueprintSpawnableComponent, DisplayName = "Interior-Exterior Attenuation"))`
- inherits: `UAudioGameplayVolumeMutator`
- desc: Component driving the volume of sounds playing inside or outside the associated AGV according to where the audio listener lays relative to this spatial volume. Note: This component is only compatible with Audio Toggles using a "Listener in Primitives" or "Listener in Range" condition.
- L45 _public prototype_ `virtual ~UAttenuationVolumeComponent() = default;`
- L48 _public prototype_ `void SetExteriorVolume(float Volume, float InterpolateTime);` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")`
- L50 _public function_ `float GetExteriorVolume() const`
- L51 _public function_ `float GetExteriorTime() const`
- L54 _public prototype_ `void SetInteriorVolume(float Volume, float InterpolateTime);` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")`
- L56 _public function_ `float GetInteriorVolume() const`
- L57 _public function_ `float GetInteriorTime() const`
- L62 _private prototype_ `virtual TSharedPtr<FProxyVolumeMutator> FactoryMutator() const override;`
- L63 _private prototype_ `virtual void CopyAudioDataToMutator(TSharedPtr<FProxyVolumeMutator>& Mutator) const override;`
- L68 _private member_ `float ExteriorVolume = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VolumeAttenuation", meta = (AllowPrivateAccess = "true"))` — The desired volume of sounds outside the volume when the player is inside the volume
- L72 _private member_ `float ExteriorTime = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VolumeAttenuation", meta = (AllowPrivateAccess = "true"))` — The time over which to interpolate from the current volume to the desired volume of sounds outside the volume when the player enters the volume
- L76 _private member_ `float InteriorVolume = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VolumeAttenuation", meta = (AllowPrivateAccess = "true"))` — The desired volume of sounds inside the volume when the player is outside the volume
- L80 _private member_ `float InteriorTime = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VolumeAttenuation", meta = (AllowPrivateAccess = "true"))` — The time over which to interpolate from the current volume to the desired volume of sounds inside the volume when the player enters the volume

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolume.h` (Public)


#### class `AAudioGameplayVolume`  
`class AAudioGameplayVolume : public AVolume`  
_L28-94_
- reflection: `UCLASS(MinimalAPI, hidecategories = (Advanced, Attachment, Collision, Volume))`
- inherits: `AVolume`
- desc: AudioGameplayVolume - A spatial volume used to notify audio gameplay systems when the nearest audio listener enters or exits the volume. Additionally, these volumes can influence audio sources depending on the relative position of the listener. NOTE: Will only impact audio sources that have "apply ambient volumes" set on their sound class.
- L36 _private member_ `TObjectPtr<UAudioGameplayVolumeComponent> AGVComponent = nullptr;` — `UPROPERTY(Transient)` — A representation of this volume for the audio thread
- L41 _private member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_bEnabled, Category = "AudioGameplay", Meta = (AllowPrivateAccess = "true"))` — Whether this volume is currently enabled.  Disabled volumes will not have a volume proxy, and therefore will not be considered for intersection checks.
- L45 _public function_ `bool GetEnabled() const`
- L49 _public prototype_ `void SetEnabled(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")` — Sets whether the volume is enabled
- L53 _public prototype_ `void OnListenerEnter();` — `UFUNCTION(BlueprintNativeEvent, Category = Events)` — Blueprint event for listener enter
- L57 _public prototype_ `void OnListenerExit();` — `UFUNCTION(BlueprintNativeEvent, Category = Events)` — Blueprint event for listener exit
- L60 _public member_ `FAudioGameplayVolumeEvent OnListenerEnterEvent;` — `UPROPERTY(BlueprintAssignable, Category = Events)`
- L63 _public member_ `FAudioGameplayVolumeEvent OnListenerExitEvent;` — `UPROPERTY(BlueprintAssignable, Category = Events)`
- L67 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L68 _public function_ `virtual bool ShouldCheckCollisionComponentForErrors() const override`
- L70 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L74 _public prototype_ `virtual void PostInitializeComponents() override;`
- L75 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L76 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L80 _public prototype_ `void OnComponentDataChanged();` — Called by a child component to notify our proxy may need updating
- L82 _public prototype_ `bool CanSupportProxy() const;`
- L87 _protected prototype_ `virtual void OnRep_bEnabled();` — `UFUNCTION()`
- L89 _protected prototype_ `void TransformUpdated(USceneComponent* InRootComponent, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);`
- L91 _protected prototype_ `void AddProxy() const;`
- L92 _protected prototype_ `void RemoveProxy() const;`
- L93 _protected prototype_ `void UpdateProxy() const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAudioGameplayVolumeEvent);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAudioGameplayVolumeEvent);`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeComponent.h` (Public)


#### class `UAudioGameplayVolumeComponent`  
`class UAudioGameplayVolumeComponent final : public UAudioGameplayComponent`  
_L29-85_
- reflection: `UCLASS(MinimalAPI, Config = Game, ClassGroup = ("AudioGameplay"), meta = (BlueprintSpawnableComponent, IsBlueprintBase = false, DisplayName = "Audio Toggle"))`
- inherits: `UAudioGameplayComponent`
- desc: Component used to drive interaction with AudioGameplayVolumeSubsystem ("Audio Toggle" subsystem). This is the component that makes the owning actor behave like an Audio Toggle, and where you can configure how a toggle can be active or inactive (through its Toggle Condition). Blueprints can bind arbitrary effects to the toggle becoming On or Off through this component's "On Toggled On" and "On Toggled Off" events. But you will usually want to add Audio NOTE: Do not inherit from this class, use UAudioGameplayVolumeComponentBase or UAudioGameplayVolumeMutator to create extendable functionality.
- L35 _public prototype_ `virtual ~UAudioGameplayVolumeComponent() = default;`
- L37 _public prototype_ `void SetProxy(UAudioGameplayVolumeProxy* NewProxy);`
- L38 _public function_ `UAudioGameplayVolumeProxy* GetProxy() const`
- L41 _public prototype_ `void OnComponentDataChanged();` — Called by a component on same actor to notify our proxy may need updating
- L44 _public prototype_ `void EnterProxy() const;` — Called when the proxy is 'entered' - This is when the proxy goes from zero listeners to at least one.
- L47 _public prototype_ `void ExitProxy() const;` — Called when the proxy is 'exited' - This is when the proxy goes from at least one listeners to zero.
- L51 _public member_ `FOnAudioGameplayVolumeProxyStateChange OnProxyEnter;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Toggled On"))` — Blueprint event for proxy enter
- L55 _public member_ `FOnAudioGameplayVolumeProxyStateChange OnProxyExit;` — `UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Toggled Off"))` — Blueprint event for proxy exit
- L64 _protected member_ `TObjectPtr<UAudioGameplayVolumeProxy> Proxy = nullptr;` — `UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "AudioGameplay", Meta = (ShowOnlyInnerProperties, AllowPrivateAccess = "true", DisplayName = "Toggle Condition"))` — The kind of condition that this Audio Toggle uses to evaluate its On/Off state. See the tooltip for each choice to see how they work and can be further configured.
- L67 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L71 _protected prototype_ `virtual void OnRegister() override;`
- L72 _protected prototype_ `virtual void OnUnregister() override;`
- L76 _protected prototype_ `virtual void Enable() override;`
- L77 _protected prototype_ `virtual void Disable() override;`
- L80 _protected prototype_ `void AddProxy() const;`
- L81 _protected prototype_ `void RemoveProxy() const;`
- L82 _protected prototype_ `void UpdateProxy() const;`
- L84 _protected prototype_ `UAudioGameplayVolumeSubsystem* GetSubsystem() const;`

#### class `UAudioGameplayVolumeComponentBase`  
`class UAudioGameplayVolumeComponentBase : public UAudioGameplayComponent , public IAudioGameplayVolumeInteraction`  
_L92-100_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = ("AudioGameplay"), hidecategories = (Tags, Collision), meta = (BlueprintSpawnableComponent))`
- inherits: `UAudioGameplayComponent,IAudioGameplayVolumeInteraction`
- desc: UAudioGameplayVolumeComponentBase - Blueprintable component used to craft custom functionality with AudioGameplayVolumes. NOTE: Inherit from this class to get easy access to OnListenerEnter and OnListenerExit Blueprint Events
- L99 _public prototype_ `virtual ~UAudioGameplayVolumeComponentBase() = default;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioGameplayVolumeProxyStateChange);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioGameplayVolumeProxyStateChange);`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeListener.h` (Public)


#### class `FInterpolatedInteriorSettings`  
`class FInterpolatedInteriorSettings`  
_L14-64_
- desc: FInterpolatedInteriorSettings
- L18 _public prototype_ `FInterpolatedInteriorSettings() = default;`
- L21 _public prototype_ `void Apply(const FInteriorSettings& NewSettings);` — Set a new interior settings target
- L24 _public prototype_ `float Interpolate(double CurrentTime, double EndTime) const;` — Interpolates between the source and end
- L27 _public prototype_ `void UpdateInteriorValues();` — Updates the current state of the interior settings
- L29 _public function_ `inline void SetInteriorStartTime(double InTime)`
- L31 _public function_ `inline double GetInteriorStartTime() const`
- L33 _public function_ `inline float GetInteriorVolume() const`
- L34 _public function_ `inline float GetInteriorVolumeInterp() const`
- L36 _public function_ `inline float GetExteriorVolume() const`
- L37 _public function_ `inline float GetExteriorVolumeInterp() const`
- L39 _public function_ `inline float GetInteriorLPF() const`
- L40 _public function_ `inline float GetInteriorLPFInterp() const`
- L42 _public function_ `inline float GetExteriorLPF() const`
- L43 _public function_ `inline float GetExteriorLPFInterp() const`
- L45 _public function_ `inline bool IsWorldSettings() const`
- L49 _protected member_ `double InteriorStartTime = 0.0;`
- L51 _protected member_ `double InteriorEndTime = 0.0;`
- L52 _protected member_ `double ExteriorEndTime = 0.0;`
- L54 _protected member_ `double InteriorLPFEndTime = 0.0;`
- L55 _protected member_ `double ExteriorLPFEndTime = 0.0;`
- L57 _protected member_ `float InteriorVolumeInterp = 0.f;`
- L58 _protected member_ `float ExteriorVolumeInterp = 0.f;`
- L60 _protected member_ `float InteriorLPFInterp = 0.f;`
- L61 _protected member_ `float ExteriorLPFInterp = 0.f;`
- L63 _protected member_ `FInteriorSettings InteriorSettings;`

#### class `FAudioGameplayVolumeListener`  
`class FAudioGameplayVolumeListener`  
_L69-99_
- desc: FAudioGameplayVolumeListener
- L73 _public prototype_ `FAudioGameplayVolumeListener() = default;`
- L75 _public prototype_ `void Update(const FAudioProxyMutatorSearchResult& Result, const FVector& InPosition, uint32 InDeviceId);`
- L77 _public function_ `const TSet<uint32>& GetCurrentProxies() const`
- L79 _public function_ `uint32 GetOwningDeviceId() const`
- L81 _public function_ `bool GetAffectedByLegacySystem() const`
- L82 _public function_ `void SetAffectedByLegacySystem(bool bIsAffected)`
- L84 _public function_ `const FInterpolatedInteriorSettings& GetInteriorSettings() const`
- L88 _protected member_ `FInterpolatedInteriorSettings InteriorSettings;`
- L90 _protected member_ `uint32 OwningDeviceId = INDEX_NONE;`
- L91 _protected member_ `FVector Position = FVector::ZeroVector;`
- L93 _protected member_ `bool bAffectedByLegacySystem = false;`
- L95 _protected member_ `TSet<uint32> CurrentProxies;`
- L96 _protected member_ `TSet<uint32> PreviousProxies;`
- L98 _protected member_ `TArray<TSharedPtr<FProxyVolumeMutator>> ActiveMutators;`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeLogs.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AudioGameplayVolumeLog, Log, All);`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeModule.h` (Public)


#### class `FAudioGameplayVolumeModule`  
`class FAudioGameplayVolumeModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- desc: FAudioGameplayVolumeModule
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeMutator.h` (Public)


#### struct `FAudioProxyActiveSoundParams`  
`struct FAudioProxyActiveSoundParams`  
_L21-43_
- desc: FAudioProxyActiveSoundParams - Helper struct for collecting info about the active sound from affecting proxy mutators
- L23 _public prototype_ `FAudioProxyActiveSoundParams() = delete;`
- L24 _public prototype_ `FAudioProxyActiveSoundParams(const FAudioGameplayActiveSoundInfo& SoundInfo, const FAudioGameplayVolumeListener& InListener);`
- L26 _public member_ `float SourceInteriorVolume = 1.f;`
- L28 _public member_ `float SourceInteriorLPF = MAX_FILTER_FREQUENCY;`
- L30 _public member_ `bool bAllowSpatialization = false;`
- L31 _public member_ `bool bUsingWorldSettings = false;`
- L32 _public member_ `bool bListenerInVolume = false;`
- L34 _public member_ `bool bAffectedByAttenuation = false;`
- L35 _public member_ `bool bAffectedByFilter = false;`
- L37 _public member_ `const FAudioGameplayVolumeListener& Listener;`
- L38 _public member_ `const FAudioGameplayActiveSoundInfo& Sound;`
- L40 _public member_ `TArray<FSoundSubmixSendInfo> SoundSubmixSends;`
- L42 _public prototype_ `void UpdateInteriorValues();`

#### class `FProxyVolumeMutator`  
`class FProxyVolumeMutator : public TSharedFromThis<FProxyVolumeMutator>`  
_L48-77_
- inherits: `TSharedFromThis<FProxyVolumeMutator>`
- desc: FProxyVolumeMutator - An audio thread representation of the payload for an AudioGameplayVolumeComponent.
- L52 _public prototype_ `FProxyVolumeMutator();`
- L53 _public prototype_ `virtual ~FProxyVolumeMutator() = default;`
- L55 _public typedef_ `using PayloadFlags = AudioGameplay::EComponentPayload;`
- L57 _public prototype_ `virtual void Apply(FInteriorSettings& InteriorSettings) const;`
- L58 _public function_ `virtual void Apply(FAudioProxyActiveSoundParams& Params) const`
- L59 _public function_ `virtual void Apply(FAudioGameplayVolumeListener& Listener) const`
- L61 _public function_ `virtual void Remove(FAudioProxyActiveSoundParams& Params) const`
- L62 _public function_ `virtual void Remove(FAudioGameplayVolumeListener& Listener) const`
- L64 _public prototype_ `bool HasPayloadType(PayloadFlags InType) const;`
- L66 _public member_ `int32 Priority = INDEX_NONE;`
- L67 _public member_ `uint32 VolumeID = INDEX_NONE;`
- L68 _public member_ `uint32 WorldID = INDEX_NONE;`
- L70 _public member_ `FName MutatorName;`
- L72 _public member_ `PayloadFlags PayloadType;`
- L76 _protected member_ `constexpr static const TCHAR MutatorBaseName[] = TEXT("Mut`

#### class `UAudioGameplayVolumeMutator`  
`class UAudioGameplayVolumeMutator : public UAudioGameplayComponent`  
_L85-130_
- reflection: `UCLASS(MinimalAPI, Abstract, HideDropdown, meta = (IsBlueprintBase = false))`
- inherits: `UAudioGameplayComponent`
- desc: UAudioGameplayVolumeMutator - These components are used for more complex interactions with AudioGameplayVolumes. Currently, components inheriting this base can affect interior settings as well as active sounds or the audio listener(s) inside the volume. See also: FilterVolumeComponent, AttenuationVolumeComponent, SubmixSendComponent, SubmixOverrideVolumeComponent, and ReverbVolumeComponent
- L91 _public prototype_ `virtual ~UAudioGameplayVolumeMutator() = default;`
- L94 _public prototype_ `void SetPriority(int32 InPriority);` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")`
- L96 _public function_ `int32 GetPriority() const`
- L99 _public prototype_ `virtual TSharedPtr<FProxyVolumeMutator> CreateMutator() const final;` — Create and fill the appropriate proxy mutator for this component
- L103 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L110 _protected prototype_ `virtual void Enable() override;`
- L114 _protected prototype_ `virtual TSharedPtr<FProxyVolumeMutator> FactoryMutator() const;` — Create this component's type of mutator
- L117 _protected function_ `virtual void CopyAudioDataToMutator(TSharedPtr<FProxyVolumeMutator>& Mutator) const` — Override in child classes to copy additional data needed to mutators
- L120 _protected prototype_ `void NotifyDataChanged() const;` — Notify our parent volume our proxy may need updating
- L124 _protected member_ `int32 Priority = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AudioGameplay", Meta = (AllowPrivateAccess = "true"))` — The priority of this component.  In the case of overlapping volumes or multiple affecting components, the highest priority is chosen.
- L129 _private prototype_ `void CopyAudioDataToMutatorBase(TSharedPtr<FProxyVolumeMutator>& Mutator) const;` — Called for you during mutator creation. See CopyAudioDataToMutator for adding data to derived classes

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeProxy.h` (Public)


#### class `UAudioGameplayVolumeProxy`  
`class UAudioGameplayVolumeProxy : public UObject`  
_L29-70_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, HideDropdown)`
- inherits: `UObject`
- desc: Abstract condition type for Audio Toggles (UAudioGameplayVolumeComponent). The way Audio Toggles evaluate to On or Off is implemented in child classes by overriding the ContainsPosition function (because toggles were originally only implemented as the audio listener being inside or outside some 3D area (or "volume")).
- L35 _public typedef_ `using PayloadFlags = AudioGameplay::EComponentPayload;`
- L36 _public typedef_ `using ProxyMutatorList = TArray<TSharedPtr<FProxyVolumeMutator>>;`
- L38 _public prototype_ `virtual ~UAudioGameplayVolumeProxy() = default;`
- L40 _public prototype_ `virtual bool ContainsPosition(const FVector& Position) const;`
- L41 _public prototype_ `virtual void InitFromComponent(const UAudioGameplayVolumeComponent* Component);`
- L43 _public prototype_ `void CollectMutators(ProxyMutatorList& OutMutators) const;`
- L45 _public prototype_ `void AddPayloadType(PayloadFlags InType);`
- L46 _public prototype_ `bool HasPayloadType(PayloadFlags InType) const;`
- L48 _public prototype_ `uint32 GetVolumeID() const;`
- L49 _public prototype_ `uint32 GetWorldID() const;`
- L52 _public function_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)` — Used for debug visualization of UAudioGameplayVolumeProxy in the editor
- L56 _protected member_ `ProxyMutatorList ProxyVolumeMutators;`
- L58 _protected member_ `uint32 VolumeID = INDEX_NONE;`
- L59 _protected member_ `uint32 WorldID = INDEX_NONE;`
- L60 _protected member_ `PayloadFlags PayloadType = PayloadFlags::AGCP_None;`
- L64 _public prototype_ `FName GetOwnerName() const;`
- L68 _private member_ `FObjectKey AGVOwnerKey;` — Only for profiling use

#### class `UAGVPrimitiveComponentProxy`  
`class UAGVPrimitiveComponentProxy : public UAudioGameplayVolumeProxy`  
_L80-95_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Audio Listener in Primitives"))`
- inherits: `UAudioGameplayVolumeProxy`
- desc: Sets the Audio Toggle to On if the audio listener is in any of the primitives (as in, Primitive Components) of the owning actor, sets to Off otherwise. Note: The primitive components must have some physics enabled (for instance, OverlapAll - Primitives with the NoCollision profile are ignored).
- L86 _public prototype_ `virtual ~UAGVPrimitiveComponentProxy() = default;`
- L88 _public prototype_ `virtual bool ContainsPosition(const FVector& Position) const override;`
- L89 _public prototype_ `virtual void InitFromComponent(const UAudioGameplayVolumeComponent* Component) override;`
- L94 _protected member_ `TArray<TObjectPtr<UPrimitiveComponent>> Primitives;` — `UPROPERTY(Transient)`

#### class `UAGVConditionProxy`  
`class UAGVConditionProxy : public UAudioGameplayVolumeProxy`  
_L107-122_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Arbitrary"))`
- inherits: `UAudioGameplayVolumeProxy`
- desc: Sets the Audio Toggle state according to some arbitrary condition, regularly re-evaluated. If the owner actor implements IAudioGameplayCondition, sets the Audio Toggle to On when either ConditionMet or ConditionMet_Position is true, and sets it to Off when they are both false. If the owner actor does not implement it, looks for the first component on the actor found implementing IAudioGameplayCondition, then follows the same rules as above.
- L113 _public prototype_ `virtual ~UAGVConditionProxy() = default;`
- L115 _public prototype_ `virtual bool ContainsPosition(const FVector& Position) const override;`
- L116 _public prototype_ `virtual void InitFromComponent(const UAudioGameplayVolumeComponent* Component) override;`
- L121 _protected member_ `TObjectPtr<const UObject> ObjectPtr;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeProxyMutator.h` (Public)
_(no declarations extracted)_

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeSubsystem.h` (Public)


#### struct `FAudioGameplayActiveSoundInfo`  
`struct FAudioGameplayActiveSoundInfo`  
_L22-37_
- desc: FAudioGameplayActiveSoundInfo - Helper struct for caching active sound data
- L25 _public member_ `FInterpolatedInteriorSettings InteriorSettings;` — Interior settings & interpolation values
- L26 _public member_ `double LastUpdateTime = 0.0;`
- L29 _public member_ `float CurrentInteriorVolume = 1.f;` — Current interior values
- L30 _public member_ `float SourceInteriorVolume = 1.f;`
- L31 _public member_ `float CurrentInteriorLPF = MAX_FILTER_FREQUENCY;`
- L32 _public member_ `float SourceInteriorLPF = MAX_FILTER_FREQUENCY;`
- L34 _public member_ `TArray<TSharedPtr<FProxyVolumeMutator>> CurrentMutators;`
- L36 _public prototype_ `void Update(double ListenerInteriorStartTime);`

#### struct `FAudioGameplayProxyUpdateResult`  
`struct FAudioGameplayProxyUpdateResult`  
_L42-46_
- desc: FAudioGameplayProxyUpdateResult - Helper struct for updating game thread proxies
- L44 _public member_ `TSet<uint32> EnteredProxies;`
- L45 _public member_ `TSet<uint32> ExitedProxies;`

#### struct `FAudioProxyMutatorSearchResult`  
`struct FAudioProxyMutatorSearchResult`  
_L51-65_
- desc: FAudioProxyMutatorSearchResult - Results from a audio proxy mutator search (see below).
- L53 _public member_ `TSet<uint32> VolumeSet;`
- L54 _public member_ `TArray<TSharedPtr<FProxyVolumeMutator>> MatchingMutators;`
- L55 _public member_ `FReverbSettings ReverbSettings;`
- L56 _public member_ `FInteriorSettings InteriorSettings;`
- L58 _public function_ `void Reset()`

#### struct `FAudioProxyMutatorSearchObject`  
`struct FAudioProxyMutatorSearchObject`  
_L70-85_
- desc: FAudioProxyMutatorSearchObject - Used for searching through proxy volumes to find relevant proxy mutators
- L72 _public typedef_ `using PayloadFlags = AudioGameplay::EComponentPayload;`
- L75 _public member_ `uint32 WorldID = INDEX_NONE;` — Search parameters
- L76 _public member_ `FVector Location = FVector::ZeroVector;`
- L77 _public member_ `PayloadFlags PayloadType = PayloadFlags::AGCP_None;`
- L78 _public member_ `FAudioDeviceHandle AudioDeviceHandle;`
- L79 _public member_ `bool bAffectedByLegacySystem = false;`
- L80 _public member_ `bool bFilterPayload = true;`
- L81 _public member_ `bool bCollectMutators = true;`
- L82 _public member_ `bool bGetDefaultAudioSettings = true;`
- L84 _public prototype_ `void SearchVolumes(const TArray<UAudioGameplayVolumeProxy*>& ProxyVolumes, FAudioProxyMutatorSearchResult& OutResult);`

#### class `FAudioGameplayVolumeProxyInfo`  
`class FAudioGameplayVolumeProxyInfo`  
_L90-111_
- desc: FAudioGameplayVolumeProxyInfo - Holds information relating to which volumes our listeners are inside of
- L94 _public prototype_ `FAudioGameplayVolumeProxyInfo() = default;`
- L97 _public prototype_ `void Update(const TArray<FAudioGameplayVolumeListener>& VolumeListeners, FAudioGameplayProxyUpdateResult& OutResult);` — Aggregate proxies from all listeners into a single world list
- L100 _public prototype_ `void AddListenerIndex(int32 ListenerIndex);` — Add a listener's index to be checked on the next Update call
- L103 _public prototype_ `bool IsVolumeInCurrentList(uint32 VolumeID) const;` — Returns true if the volume contains at least one listener
- L107 _protected member_ `TSet<uint32> CurrentProxies;`
- L108 _protected member_ `TSet<uint32> PreviousProxies;`
- L110 _protected member_ `TArray<int32> ListenerIndexes;`

#### class `UAudioGameplayVolumeSubsystem`  
`class UAudioGameplayVolumeSubsystem : public UAudioEngineSubsystem , public IActiveSoundUpdateInterface`  
_L117-205_
- reflection: `UCLASS()`
- inherits: `UAudioEngineSubsystem,IActiveSoundUpdateInterface`
- desc: UAudioGameplayVolumeSubsystem
- L124 _public prototype_ `virtual ~UAudioGameplayVolumeSubsystem() = default;`
- L127 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L128 _public prototype_ `virtual void Deinitialize() override;`
- L132 _public prototype_ `virtual void Update() override;`
- L136 _public prototype_ `virtual void GatherInteriorData(const FActiveSound& ActiveSound, FSoundParseParameters& ParseParams) override;`
- L137 _public prototype_ `virtual void ApplyInteriorSettings(const FActiveSound& ActiveSound, FSoundParseParameters& ParseParams) override;`
- L138 _public prototype_ `virtual void NotifyActiveSoundDeleting(const FActiveSound& ActiveSound) override;`
- L142 _public prototype_ `void AddVolumeComponent(const UAudioGameplayVolumeComponent* VolumeComponent);` — Add a volume to the system
- L145 _public prototype_ `void UpdateVolumeComponent(const UAudioGameplayVolumeComponent* VolumeComponent);` — Update an existing volume in the system
- L148 _public prototype_ `void RemoveVolumeComponent(const UAudioGameplayVolumeComponent* VolumeComponent);` — Remove a volume from the system
- L153 _protected prototype_ `bool DoesSupportWorld(UWorld* World) const;` — Returns true if we allow volumes from the world's type
- L156 _protected prototype_ `bool AddProxy(uint32 AudioGameplayVolumeID, uint32 WorldID);` — (Audio Thread Only) Add, Update, Remove ProxyVolumes
- L157 _protected prototype_ `bool UpdateProxy(uint32 AudioGameplayVolumeID);`
- L158 _protected prototype_ `bool RemoveProxy(uint32 AudioGameplayVolumeID);`
- L161 _protected prototype_ `bool IsAnyListenerInVolume(uint32 WorldID, uint32 VolumeID) const;` — Returns true if a listener associated with WorldID is inside the volume (by ID)
- L164 _protected prototype_ `void UpdateComponentsFromProxyInfo(const FAudioGameplayProxyUpdateResult& ProxyResults) const;` — Update the components driven by proxies on the game thread
- L167 _protected prototype_ `void UpdateFromListeners();` — Update our representation of audio listeners on the audio thread
- L170 _protected prototype_ `void GenerateVolumeProxyList();` — Generate a list of volume proxies from our component list
- L173 _protected member_ `TArray<TObjectPtr<UAudioGameplayVolumeProxy>> TransientProxyList;` — `UPROPERTY(Transient)`
- L177 _protected member_ `TMap<uint32, TObjectPtr<const UAudioGameplayVolumeComponent>> AGVComponents;` — `UPROPERTY(Transient)` — Components in our system. This map should only be modified by the game thread.
- L180 _protected member_ `FCriticalSection AGVComponentsCriticalSection;` — Used to protect concurrent access to the AGVComponents map.
- L183 _protected member_ `TArray<uint32> KnownProxyIDs;` — List of Component IDs (for proxies) the audio thread is tracking
- L186 _protected member_ `TArray<FAudioGameplayVolumeListener> AGVListeners;` — Audio thread representation of Listeners
- L189 _protected member_ `TMap<uint32, FAudioGameplayActiveSoundInfo> ActiveSoundData;` — A collection of data about currently playing active sounds, indexed by the sound's unique ID
- L192 _protected member_ `TMap<uint32, FAudioGameplayVolumeProxyInfo> WorldProxyLists;` — A collection of listener & volume intersection data, by worldID
- L195 _protected member_ `float TimeSinceUpdate = 0.f;` — Time since last update call, in seconds
- L198 _protected member_ `float NextUpdateDeltaTime = 0.f;` — Time when next update happens relative to last update
- L201 _protected member_ `int32 PreviousProxyCount = 0;` — The number of proxy volumes from the previous update
- L204 _protected member_ `bool bHasStaleProxy = false;` — Force an enter / exit of a volume to handle data changing while a proxy is active

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/FilterVolumeComponent.h` (Public)


#### class `FProxyMutator_Filter`  
`class FProxyMutator_Filter : public FProxyVolumeMutator`  
_L13-31_
- inherits: `FProxyVolumeMutator`
- desc: FProxyMutator_Filter - An audio thread representation of occlusion settings (volume filter)
- L17 _public prototype_ `FProxyMutator_Filter();`
- L18 _public prototype_ `virtual ~FProxyMutator_Filter() = default;`
- L20 _public member_ `float ExteriorLPF = MAX_FILTER_FREQUENCY;`
- L21 _public member_ `float ExteriorLPFTime = 0.5f;`
- L22 _public member_ `float InteriorLPF = MAX_FILTER_FREQUENCY;`
- L23 _public member_ `float InteriorLPFTime = 0.5f;`
- L25 _public prototype_ `virtual void Apply(FInteriorSettings& InteriorSettings) const override;`
- L26 _public prototype_ `virtual void Apply(FAudioProxyActiveSoundParams& Params) const override;`
- L30 _protected member_ `constexpr static const TCHAR MutatorFilterName[] = TEXT("Fil`

#### class `UFilterVolumeComponent`  
`class UFilterVolumeComponent : public UAudioGameplayVolumeMutator`  
_L37-79_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Config = Game, ClassGroup = ("AudioGameplayVolume"), meta = (BlueprintSpawnableComponent, DisplayName = "Filter"))`
- inherits: `UAudioGameplayVolumeMutator`
- desc: UFilterVolumeComponent - Audio Gameplay Volume component for occlusion settings (volume filter)
- L43 _public prototype_ `virtual ~UFilterVolumeComponent() = default;`
- L46 _public prototype_ `void SetExteriorLPF(UPARAM(DisplayName = "Frequency") float Volume, float Interpol` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")`
- L48 _public function_ `float GetExteriorLPF() const`
- L49 _public function_ `float GetExteriorLPFTime() const`
- L52 _public prototype_ `void SetInteriorLPF(UPARAM(DisplayName = "Frequency") float Volume, float Interpol` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")`
- L54 _public function_ `float GetInteriorLPF() const`
- L55 _public function_ `float GetInteriorLPFTime() const`
- L60 _private prototype_ `virtual TSharedPtr<FProxyVolumeMutator> FactoryMutator() const override;`
- L61 _private prototype_ `virtual void CopyAudioDataToMutator(TSharedPtr<FProxyVolumeMutator>& Mutator) const override;`
- L66 _private member_ `float ExteriorLPF = MAX_FILTER_FREQUENCY;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VolumeFilter", meta = (AllowPrivateAccess = "true"))` — The desired LPF frequency cutoff (in hertz) of sounds outside the volume when the player is inside the volume
- L70 _private member_ `float ExteriorLPFTime = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VolumeFilter", meta = (AllowPrivateAccess = "true"))` — The time over which to interpolate from the current LPF to the desired LPF of sounds outside the volume when the player enters the volume
- L74 _private member_ `float InteriorLPF = MAX_FILTER_FREQUENCY;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VolumeFilter", meta = (AllowPrivateAccess = "true"))` — The desired LPF frequency cutoff (in hertz) of sounds inside the volume when the player is outside the volume
- L78 _private member_ `float InteriorLPFTime = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VolumeFilter", meta = (AllowPrivateAccess = "true"))` — The time over which to interpolate from the current LPF to the desired LPF of sounds inside the volume when the player enters the volume

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/ReverbVolumeComponent.h` (Public)


#### class `FProxyMutator_Reverb`  
`class FProxyMutator_Reverb : public FProxyVolumeMutator`  
_L14-29_
- inherits: `FProxyVolumeMutator`
- desc: FProxyMutator_Reverb - An audio thread representation of the reverb volume component
- L18 _public prototype_ `FProxyMutator_Reverb();`
- L19 _public prototype_ `virtual ~FProxyMutator_Reverb() = default;`
- L21 _public member_ `FReverbSettings ReverbSettings;`
- L23 _public prototype_ `virtual void Apply(FAudioGameplayVolumeListener& Listener) const override;`
- L24 _public prototype_ `virtual void Remove(FAudioGameplayVolumeListener& Listener) const override;`
- L28 _protected member_ `constexpr static const TCHAR MutatorReverbName[] = TEXT("Rev`

#### class `UReverbVolumeComponent`  
`class UReverbVolumeComponent : public UAudioGameplayVolumeMutator`  
_L35-60_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Config = Game, ClassGroup = ("AudioGameplayVolume"), meta = (BlueprintSpawnableComponent, DisplayName = "Reverb"))`
- inherits: `UAudioGameplayVolumeMutator`
- desc: UReverbVolumeComponent - Audio Gameplay Volume component for reverb settings
- L41 _public prototype_ `virtual ~UReverbVolumeComponent() = default;`
- L44 _public prototype_ `void SetReverbSettings(const FReverbSettings& NewReverbSettings);` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")`
- L46 _public function_ `const FReverbSettings& GetReverbSettings() const`
- L53 _private prototype_ `virtual TSharedPtr<FProxyVolumeMutator> FactoryMutator() const override;`
- L54 _private prototype_ `virtual void CopyAudioDataToMutator(TSharedPtr<FProxyVolumeMutator>& Mutator) const override;`
- L59 _private member_ `FReverbSettings ReverbSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Reverb, meta = (AllowPrivateAccess = "true"))` — Reverb settings to use with this component

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/SubmixOverrideVolumeComponent.h` (Public)


#### class `FProxyMutator_SubmixOverride`  
`class FProxyMutator_SubmixOverride : public FProxyVolumeMutator`  
_L14-29_
- inherits: `FProxyVolumeMutator`
- desc: FProxyMutator_SubmixOverride - An audio thread representation of Submix Overrides
- L18 _public prototype_ `FProxyMutator_SubmixOverride();`
- L19 _public prototype_ `virtual ~FProxyMutator_SubmixOverride() = default;`
- L21 _public member_ `TArray<FAudioVolumeSubmixOverrideSettings> SubmixOverrideSettings;`
- L23 _public prototype_ `virtual void Apply(FAudioGameplayVolumeListener& Listener) const override;`
- L24 _public prototype_ `virtual void Remove(FAudioGameplayVolumeListener& Listener) const override;`
- L28 _protected member_ `constexpr static const TCHAR MutatorSubmixOverrideName[] = TEXT("Sub`

#### class `USubmixOverrideVolumeComponent`  
`class USubmixOverrideVolumeComponent : public UAudioGameplayVolumeMutator`  
_L35-58_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Config = Game, ClassGroup = ("AudioGameplayVolume"), meta = (BlueprintSpawnableComponent, DisplayName = "Submix Override"))`
- inherits: `UAudioGameplayVolumeMutator`
- desc: USubmixOverrideVolumeComponent - Audio Gameplay Volume component for submix effect chain overrides
- L41 _public prototype_ `virtual ~USubmixOverrideVolumeComponent() = default;`
- L44 _public prototype_ `void SetSubmixOverrideSettings(const TArray<FAudioVolumeSubmixOverrideSettings>& NewSubmixOverrideSettings);` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")`
- L46 _public function_ `const TArray<FAudioVolumeSubmixOverrideSettings>& GetSubmixOverrideSettings() const`
- L51 _private prototype_ `virtual TSharedPtr<FProxyVolumeMutator> FactoryMutator() const override;`
- L52 _private prototype_ `virtual void CopyAudioDataToMutator(TSharedPtr<FProxyVolumeMutator>& Mutator) const override;`
- L57 _private member_ `TArray<FAudioVolumeSubmixOverrideSettings> SubmixOverrideSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Submixes, meta = (AllowPrivateAccess = "true"))` — Submix effect chain override settings. Will override the effect chains on the given submixes

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/SubmixSendVolumeComponent.h` (Public)


#### class `FProxyMutator_SubmixSend`  
`class FProxyMutator_SubmixSend : public FProxyVolumeMutator`  
_L14-28_
- inherits: `FProxyVolumeMutator`
- desc: FProxyMutator_SubmixSend - An audio thread representation of Submix Sends
- L18 _public prototype_ `FProxyMutator_SubmixSend();`
- L19 _public prototype_ `virtual ~FProxyMutator_SubmixSend() = default;`
- L21 _public member_ `TArray<FAudioVolumeSubmixSendSettings> SubmixSendSettings;`
- L23 _public prototype_ `virtual void Apply(FAudioProxyActiveSoundParams& Params) const override;`
- L27 _protected member_ `constexpr static const TCHAR MutatorSubmixSendName[] = TEXT("Sub`

#### class `USubmixSendVolumeComponent`  
`class USubmixSendVolumeComponent : public UAudioGameplayVolumeMutator`  
_L34-57_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Config = Game, ClassGroup = ("AudioGameplayVolume"), meta = (BlueprintSpawnableComponent, DisplayName = "Submix Send"))`
- inherits: `UAudioGameplayVolumeMutator`
- desc: USubmixSendVolumeComponent - Audio Gameplay Volume component for submix sends
- L40 _public prototype_ `virtual ~USubmixSendVolumeComponent() = default;`
- L43 _public prototype_ `void SetSubmixSendSettings(const TArray<FAudioVolumeSubmixSendSettings>& NewSubmixSendSettings);` — `UFUNCTION(BlueprintCallable, Category = "AudioGameplay")`
- L45 _public function_ `const TArray<FAudioVolumeSubmixSendSettings>& GetSubmixSendSettings() const`
- L50 _private prototype_ `virtual TSharedPtr<FProxyVolumeMutator> FactoryMutator() const override;`
- L51 _private prototype_ `virtual void CopyAudioDataToMutator(TSharedPtr<FProxyVolumeMutator>& Mutator) const override;`
- L56 _private member_ `TArray<FAudioVolumeSubmixSendSettings> SubmixSendSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Submixes, meta = (AllowPrivateAccess = "true"))` — Submix send settings to use for this component. Allows audio to dynamically send to submixes based on source and listener locations (relative to parent volume.)

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOGAMEPLAYVOLUME_API`
