# Plugins / ADMSpatialization

- module root: `Plugins/Runtime/ADM/Source/ADMSpatialization`
- headers: 5; symbols: 87
- symbol kinds: class=8, delegate=1, function=10, member=19, namespace=9, prototype=40
- PrivateDependencyModuleNames: AudioMixer, AudioMixerCore, SignalProcessing
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, DeveloperSettings, Engine, Networking, OSC

### `Plugins/Runtime/ADM/Source/ADMSpatialization/Private/ADMDirectOutChannel.h` (Private)


#### class `UE::ADM::Spatialization::FSourceDirectOut`  
`class FSourceDirectOut`  
_L13-40_
- L16 _public prototype_ `FSourceDirectOut() = delete;`
- L17 _public prototype_ `FSourceDirectOut(const int32 InChannelIndex, const uint32 InNumSamples, Audio::IAudioMixerPlatformInterface* InMixerPlatform);`
- L18 _public prototype_ `~FSourceDirectOut();`
- L20 _public prototype_ `void ProcessDirectOut(const FAudioPluginSourceInputData& InInputData);`
- L21 _public prototype_ `void ProcessSilence();`
- L23 _public function_ `void SetIsActive(const bool bInIsActive)`
- L24 _public function_ `bool GetIsActive() const`
- L26 _public function_ `void SetSourceId(const int32 InSourceId)`
- L27 _public function_ `int32 GetSourceId() const`
- L30 _private member_ `static TUniquePtr<Audio::FAlignedFloatBuffer> SilienceBuffer;`
- L32 _private member_ `FCriticalSection DestructorCriticalSection;`
- L34 _private member_ `bool bIsActive = false;`
- L35 _private member_ `Audio::IAudioMixerPlatformInterface* MixerPlatform = nullptr;`
- L36 _private member_ `int32 SourceId = INDEX_NONE;`
- L37 _private member_ `int32 ChannelIndex = INDEX_NONE;`
- L39 _private prototype_ `void InitializeTempBuffers(const uint32 InNumSamples);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ADM` (scope `UE`)
- L11 _namespace_ `namespace Spatialization` (scope `UE::ADM`)

### `Plugins/Runtime/ADM/Source/ADMSpatialization/Private/ADMSpatialization.h` (Private)


#### class `UADMSpatializationSourceSettings`  
`class UADMSpatializationSourceSettings : public USpatializationPluginSourceSettingsBase`  
_L22-28_
- reflection: `UCLASS()`
- inherits: `USpatializationPluginSourceSettingsBase`
- L27 _public prototype_ `UADMSpatializationSourceSettings() = default;`

#### class `UADMEngineSubsystem`  
`class UADMEngineSubsystem : public UAudioEngineSubsystem`  
_L31-44_
- reflection: `UCLASS()`
- inherits: `UAudioEngineSubsystem`
- L36 _private function_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override`
- L37 _private function_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override`
- L38 _private function_ `virtual void Deinitialize() override`
- L43 _private prototype_ `void SetSendIPAddress(const FString& IPAddress, int32 Port);` — `UFUNCTION(BlueprintCallable, Category = "ADM|OSC", meta = (DisplayName = "Set Send IP Address", Keywords = "osc adm message"))` — Set the IP Address to communicate ADM updates over OSC to

#### class `UE::ADM::Spatialization::FADMSpatializationFactory`  
`class FADMSpatializationFactory : public IAudioSpatializationFactory`  
_L49-78_
- inherits: `IAudioSpatializationFactory`
- L52 _public prototype_ `FADMSpatializationFactory() = default;`
- L53 _public prototype_ `~FADMSpatializationFactory() = default;`
- L55 _public prototype_ `virtual FString GetDisplayName() override;`
- L56 _public prototype_ `virtual bool SupportsPlatform(const FString& PlatformName) override;`
- L57 _public prototype_ `virtual TAudioSpatializationPtr CreateNewSpatializationPlugin(FAudioDevice* OwningDevice) override;`
- L58 _public prototype_ `virtual UClass* GetCustomSpatializationSettingsClass() const override;`
- L59 _public prototype_ `virtual bool IsExternalSend() override;`
- L60 _public prototype_ `virtual int32 GetMaxSupportedChannels() override;`
- L62 _public function_ `void SetSendIPEndpoint(const FIPv4Endpoint& InIPEndpoint)`
- L68 _public function_ `const FIPv4Endpoint& GetSendIPEndpoint() const`
- L75 _private member_ `mutable FCriticalSection ClientIPCritSec;`
- L77 _private member_ `FIPv4Endpoint IPEndpoint;`

#### class `UE::ADM::Spatialization::FADMClient`  
`class FADMClient`  
_L81-115_
- L84 _public prototype_ `FADMClient() = default;`
- L85 _public prototype_ `FADMClient(const FIPv4Endpoint& InEndpoint, const int32 InObjectIndexOffset = 0);`
- L87 _public prototype_ `void InitObjectIndex(int32 InObjIndex, bool bCartesian = true);`
- L88 _public prototype_ `bool IsSet() const;`
- L90 _public prototype_ `void SetPosition(int32 InObjIndex, const FVector& InPosition);`
- L93 _private member_ `TUniquePtr<UE::OSC::IClientProxy> ClientProxy;`
- L94 _private member_ `int32 ObjectIndexOffset = 0;`
- L96 _private prototype_ `int32 GetObjectIndexOffset() const;`
- L98 _private prototype_ `FOSCAddress CreateConfigAddress(int32 InObjIndex, FString InMethod) const;`
- L99 _private prototype_ `FOSCAddress CreatePositionAddress(int32 InObjIndex, FString InMethod) const;`
- L101 _private function_ `FORCEINLINE FVector UnrealToADMCoordinates(const FVector& InPosition)`

#### class `UE::ADM::Spatialization::FADMSpatialization`  
`class FADMSpatialization : public IAudioSpatialization`  
_L118-144_
- inherits: `IAudioSpatialization`
- L121 _public prototype_ `FADMSpatialization() = default;`
- L122 _public prototype_ `~FADMSpatialization() = default;`
- L124 _public prototype_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;`
- L125 _public prototype_ `virtual bool IsSpatializationEffectInitialized() const override;`
- L126 _public prototype_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, USpatializationPluginSourceSettingsBase* InSettings) override;`
- L127 _public prototype_ `virtual void OnReleaseSource(const uint32 SourceId) override;`
- L128 _public prototype_ `virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData) override;`
- L129 _public prototype_ `virtual void OnAllSourcesProcessed() override;`
- L130 _public prototype_ `virtual void Shutdown () override;`
- L132 _public prototype_ `void SetClient(FADMClient&& InClient);`
- L135 _private member_ `int32 NumBedChannels = 0;`
- L136 _private member_ `int32 NumSources = 0;`
- L137 _private member_ `float SampleRate = 0.f;`
- L139 _private member_ `TArray<FSourceDirectOut> DirectOuts;`
- L141 _private member_ `TMap<int32, int32> SourceIdChannelMap;` — Maps Source ID to Channel index
- L143 _private member_ `FADMClient Client;`

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace ADM` (scope `UE`)
- L47 _namespace_ `namespace Spatialization` (scope `UE::ADM`)

### `Plugins/Runtime/ADM/Source/ADMSpatialization/Private/ADMSpatializationLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogADMSpatialization, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogADMSpatialization, Log, All);`

### `Plugins/Runtime/ADM/Source/ADMSpatialization/Private/ADMSpatializationModule.h` (Private)


#### class `UE::ADM::Spatialization::FModule`  
`class FModule : public IModuleInterface`  
_L10-20_
- inherits: `IModuleInterface`
- L13 _public prototype_ `FADMSpatializationFactory& GetFactory();`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `FADMSpatializationFactory SpatializationFactory;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ADM` (scope `UE`)
- L8 _namespace_ `namespace Spatialization` (scope `UE::ADM`)

### `Plugins/Runtime/ADM/Source/ADMSpatialization/Private/ADMSpatializationSettings.h` (Private)


#### class `UADMSpatializationSettings`  
`class UADMSpatializationSettings : public UDeveloperSettings`  
_L12-35_
- reflection: `UCLASS(config = ADM, defaultconfig, meta = (DisplayName = "ADM Spatialization Settings"))`
- inherits: `UDeveloperSettings`
- L21 _public member_ `FString IPAddress;` — `UPROPERTY(config, EditAnywhere, Category = ADM, meta = (DisplayName = "OSC IP Address"))` — If set to a valid IP address, enables ADM Spatialization and sends source data to the given IP Address using the OSC network protocol. Can be overridden via console variable "au.OSC.ADM.SendAddress" for configuring on stand-alone client.
- L26 _public member_ `int32 IPPort = 4001;` — `UPROPERTY(config, EditAnywhere, Category = ADM, meta = (DisplayName = "OSC IP Port"))` — The IP port used in conjunction with the given IP Address. Default value of 4001 per the ADM-OSC spec.
- L31 _public prototype_ `void ADMConnect();` — `UFUNCTION(CallInEditor, Category = ADM, meta = (DisplayName = "Connect ADM OSC Client"))` — Initializes (or reinitializes) the ADM client with the given settings.
- L33 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
