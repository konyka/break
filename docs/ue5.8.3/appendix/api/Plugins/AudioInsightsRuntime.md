# Plugins / AudioInsightsRuntime

- module root: `Plugins/AudioInsightsRuntime/Source/AudioInsightsRuntime`
- headers: 2; symbols: 16
- symbol kinds: class=2, macro=1, namespace=3, prototype=10
- PrivateDependencyModuleNames: AudioMixerCore, CoreUObject, Engine, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/AudioInsightsRuntime/Source/AudioInsightsRuntime/Private/AudioInsightsRuntimeModule.h` (Private)


#### class `UE::Audio::Insights::FAudioInsightsRuntimeModule`  
`class FAudioInsightsRuntimeModule final : public IModuleInterface`  
_L8-21_
- inherits: `IModuleInterface`
- L11 _public prototype_ `FAudioInsightsRuntimeModule() = default;`
- L12 _public prototype_ `virtual ~FAudioInsightsRuntimeModule() = default;`
- L14 _public prototype_ `FAudioInsightsRuntimeModule(const FAudioInsightsRuntimeModule&) = delete;`
- L15 _public prototype_ `FAudioInsightsRuntimeModule& operator=(const FAudioInsightsRuntimeModule&) = delete;`
- L16 _public prototype_ `FAudioInsightsRuntimeModule(FAudioInsightsRuntimeModule&&) = delete;`
- L17 _public prototype_ `FAudioInsightsRuntimeModule& operator=(FAudioInsightsRuntimeModule&&) = delete;`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Audio` (scope `UE`)
- L6 _namespace_ `namespace Insights` (scope `UE::Audio`)

### `Plugins/AudioInsightsRuntime/Source/AudioInsightsRuntime/Public/AudioInsightsBlueprintLibrary.h` (Public)


#### class `UAudioInsightsBlueprintLibrary`  
`class UAudioInsightsBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L17-43_
- reflection: `UCLASS(meta = (ScriptName = "AudioInsightsBlueprintLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Static class with useful gameplay utility functions that can be called from both Blueprint and C++
- L31 _public prototype_ `static void LogAudioInsightsEvent(const UObject* WorldContextObject, const FString& EventName, const USoundBase* SoundAsset = nullptr, const AActor* Actor = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Audio|AudioInsights", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "2"))` — Send an event message to the Audio Insights event log. The filter category for the event can be added in the Audio Insights editor preferences Requires the Audio Insights plug-in to be enabled. @param EventName - the name that will appear in the event log for this event. @param SoundAsset (optional) - the sound asset associated with this event. @param Actor (optional) - the actor associated with this event.
- L41 _public prototype_ `static void LogAudioInsightsEventForAudioComponent(const UObject* WorldContextObject, const FString& EventName, const class UAudioComponent* AudioComponent);` — `UFUNCTION(BlueprintCallable, Category = "Audio|AudioInsights", meta = (WorldContext = "WorldContextObject"))` — Send an event message to the Audio Insights event log for a given AudioComponent. The filter category for the event can be added in the Audio Insights editor preferences Requires the Audio Insights plug-in to be enabled. @param EventName - the name that will appear in the event log for this event @param AudioComponent - the AudioComponent associated with this event

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API AUDIOINSIGHTSRUNTIME_API`
