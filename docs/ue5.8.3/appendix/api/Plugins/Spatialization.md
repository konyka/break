# Plugins / Spatialization

- module root: `Plugins/Runtime/Spatialization/Source/Spatialization`
- headers: 3; symbols: 39
- symbol kinds: class=4, function=4, member=11, prototype=19, struct=1
- PrivateDependencyModuleNames: AudioExtensions, CoreUObject, Engine, SignalProcessing
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/Spatialization/Source/Spatialization/Public/ITDSpatializationSourceSettings.h` (Public)


#### class `UITDSpatializationSourceSettings`  
`class UITDSpatializationSourceSettings : public USpatializationPluginSourceSettingsBase`  
_L11-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USpatializationPluginSourceSettingsBase`
- L19 _public member_ `bool bEnableILD;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = SpatializationSettings, meta = (DisplayName = "Enable Level Panning"))` — Whether we should use any level difference between the left and right channel in our spatialization algorithm.
- L23 _public member_ `FRuntimeFloatCurve PanningIntensityOverDistance;` — `UPROPERTY(GlobalConfig, EditAnywhere, BlueprintReadWrite, Category = SpatializationSettings)` — This curve will map the intensity of panning (y-axis, 0.0-1.0) as a factor of distance (in Unreal Units)

### `Plugins/Runtime/Spatialization/Source/Spatialization/Public/ITDSpatializer.h` (Public)


#### struct `FSourceSpatializer`  
`struct FSourceSpatializer`  
_L10-40_
- L12 _public prototype_ `FSourceSpatializer(float InSampleRate);`
- L13 _public prototype_ `~FSourceSpatializer();`
- L15 _public prototype_ `void ProcessSource(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData);`
- L18 _public prototype_ `void ZeroOut();` — Zeros out all delay lines.
- L20 _public prototype_ `void SetILDCurve(const FRuntimeFloatCurve& InCurve);`
- L23 _private prototype_ `FSourceSpatializer();`
- L25 _private prototype_ `void EvaluateGainDestinations(const FAudioPluginSourceInputData& InputData);`
- L26 _private prototype_ `void EvaluateDelayDestinations(const FAudioPluginSourceInputData& InputData);`
- L27 _private prototype_ `void EvaluateDelayDestinationForInputChannel(int32 ChannelIndex, float X, float Y);`
- L31 _private member_ `TArray<Audio::FDelay> LeftDelays;` — Each input channel requires a separate delay line for the left and right output channels:
- L32 _private member_ `TArray<Audio::FDelay> RightDelays;`
- L34 _private member_ `Audio::FExponentialEase LeftGain;`
- L35 _private member_ `Audio::FExponentialEase RightGain;`
- L37 _private member_ `FCriticalSection DestructorCriticalSection;`
- L39 _private member_ `FRuntimeFloatCurve CurrentILDCurve;`

#### class `FITDSpatialization`  
`class FITDSpatialization : public IAudioSpatialization`  
_L42-60_
- inherits: `IAudioSpatialization`
- L45 _public prototype_ `FITDSpatialization();`
- L46 _public prototype_ `~FITDSpatialization();`
- L49 _public prototype_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;` — IAudioSpatialization implementation
- L50 _public prototype_ `virtual void Shutdown() override;`
- L51 _public prototype_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USpatializationPluginSourceSettingsBase* InSettings) override;`
- L52 _public prototype_ `virtual void OnReleaseSource(const uint32 SourceId) override;`
- L53 _public prototype_ `virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData);`
- L57 _private member_ `TArray<FSourceSpatializer> Sources;`
- L59 _private member_ `float SampleRate;`

#### class `FITDSpatializationPluginFactory`  
`class FITDSpatializationPluginFactory : public IAudioSpatializationFactory`  
_L62-88_
- inherits: `IAudioSpatializationFactory`
- L65 _public function_ `virtual FString GetDisplayName() override`
- L71 _public function_ `virtual bool SupportsPlatform(const FString& PlatformName) override`
- L76 _public function_ `virtual TAudioSpatializationPtr CreateNewSpatializationPlugin(FAudioDevice* OwningDevice) override`
- L81 _public function_ `virtual int32 GetMaxSupportedChannels() override`
- L86 _public prototype_ `virtual UClass* GetCustomSpatializationSettingsClass() const override;`

### `Plugins/Runtime/Spatialization/Source/Spatialization/Public/SpatializationModule.h` (Public)


#### class `FSpatializationModule`  
`class FSpatializationModule : public IModuleInterface`  
_L10-19_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `FITDSpatializationPluginFactory PluginFactory;`
